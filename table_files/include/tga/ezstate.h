#ifndef _TGA_EZSTATE
#define _TGA_EZSTATE

#include "stdint.h"
#include "stdlib.h"
#include "celua.h"
#include "pattern.h"

/* Fromsoft types */

typedef struct _MenuJob {
    uint32_t unk00[4];
} MenuJob;

typedef struct _CSTalkInsActiveMenuJob {
    MenuJob menu_job;
    uint32_t maybe_job_id;
    struct _CSNpcTalkIns* parent_talk_ins;
} CSTalkInsActiveMenuJob;

typedef struct _UnkTalkEventField08 {
    uint8_t unk00[0x30];
    uint64_t unk_chr_ins_handle;
} UnkTalkEventField08;

typedef struct _CSNpcTalkIns {
    uint8_t unk000[0xc];
    uint32_t unk_talk_param_field_1; // spEffectId0, returnPos or motionId1
    uint32_t unk_talk_param_field_2; // eventId, spEffectId1 or reactionId
    uint8_t unk014[0x40 - 0x14];
    uint64_t chr_ins_handle;
    uint8_t unk048[0x98 - 0x48]; // This seems to be a bunch of wwise related fields
    CSTalkInsActiveMenuJob* active_menu_job;
} CSNpcTalkIns;

typedef struct _EzStateTalkEvent {
    void** vtable; // 0 = dtor, 1 = event dispatcher
    UnkTalkEventField08* unk08;
    CSNpcTalkIns* npc_talk_ins;
    uint32_t unk18_popup_menu_related;
} EzStateTalkEvent;

typedef enum _EzStateFuncArgType {
    Float = 1,
    Int32 = 2,
    Unk03 = 3,
} EzStateFuncArgType;

typedef struct _EzStateExternalFuncArg {
    union {
        float as_float;
        int as_int;
        uint64_t as_unk_u64;
    } value;
    EzStateFuncArgType type;
} EzStateExternalFuncArg;

typedef struct _EzStateExternalEventTemp_VMT {
    void (*dtor)(void* this);
    void (*unk08)(void* this);
    int (*event_id)(void* this);
    int (*arg_count)(void* this); // Note: Arg 0 is the event ID!
    EzStateExternalFuncArg* (*arg_at)(void* this, int index);
} EzStateExternalEventTemp_VMT;


typedef struct _EzStateExternalEventTemp {
    EzStateExternalEventTemp_VMT* vtable;
} EzStateExternalEventTemp;

// Populate this lazily via AOB scan
void (*EZSTATE_TALK_EVENT_DISPATCH)(EzStateTalkEvent*, EzStateExternalEventTemp*) = NULL;

/* Mocked types */

typedef struct _fake_ezstate_ext_event {
    EzStateExternalEventTemp_VMT* vtable;
    EzStateExternalFuncArg* args;
    int arg_count;
} fake_ezstate_ext_event;

void fake_ezstate_ext_event_stub(fake_ezstate_ext_event* this) {}

int fake_ezstate_ext_event_arg_count(fake_ezstate_ext_event* this) {
    return this->arg_count;
}
int fake_ezstate_ext_event_id(fake_ezstate_ext_event* this) {
    return this->arg_count ? this->args[0].value.as_int : 0;
}
EzStateExternalFuncArg* fake_ezstate_ext_event_arg_at(fake_ezstate_ext_event* this, int index) {
    return this->args + index;
}

EzStateExternalEventTemp_VMT FAKE_EZSTATE_EXT_EVENT_VTABLE = {
    .dtor = (void*)fake_ezstate_ext_event_stub,
    .unk08 = (void*)fake_ezstate_ext_event_stub,
    .event_id = (void*)fake_ezstate_ext_event_id,
    .arg_count = (void*)fake_ezstate_ext_event_arg_count,
    .arg_at = (void*)fake_ezstate_ext_event_arg_at
};

void init_ezstate_talk_event(EzStateTalkEvent* evt) {
    evt->vtable = 0;
    
    evt->unk08 = calloc(1, sizeof(*evt->unk08));
    evt->unk08->unk_chr_ins_handle = -1;
    
    evt->npc_talk_ins = calloc(1, sizeof(*evt->npc_talk_ins));
    evt->npc_talk_ins->chr_ins_handle = -1;
    evt->npc_talk_ins->active_menu_job = calloc(1, sizeof(*evt->npc_talk_ins->active_menu_job));
    evt->npc_talk_ins->active_menu_job->parent_talk_ins = evt->npc_talk_ins;
    
    evt->unk18_popup_menu_related = 0;
}

void destroy_ezstate_talk_event(EzStateTalkEvent* evt) {
    free(evt->unk08);
    if (evt->npc_talk_ins) {
        free(evt->npc_talk_ins->active_menu_job);
        free(evt->npc_talk_ins);
    }
    memset(evt, 0, sizeof(*evt));
}

void ezstate_execute_event(EzStateExternalFuncArg* args, int arg_count) {
    // TODO: Find via vtable scan instead (CS::CSEzStateTalkEvent)
    if (EZSTATE_TALK_EVENT_DISPATCH == NULL) {
        intptr_t aob_result = easy_aob_scan(NULL, ".text", "48 8B DA 4C 8B F1 33 FF 89 7D");
        if (aob_result == 0) {
            CELUA_ExecuteFunctionAsync("queue(function() print('Failed to find EzState event disptacher') end)", 0);
            return;
        }
        EZSTATE_TALK_EVENT_DISPATCH = (void*)(aob_result - 0x47);
    }
    
    EzStateTalkEvent talk_event;
    init_ezstate_talk_event(&talk_event);

    fake_ezstate_ext_event ext_event = {
        .vtable = &FAKE_EZSTATE_EXT_EVENT_VTABLE,
        .args = args,
        .arg_count = arg_count
    };

    EZSTATE_TALK_EVENT_DISPATCH(&talk_event, (EzStateExternalEventTemp*)&ext_event);
    destroy_ezstate_talk_event(&talk_event);
}

#endif