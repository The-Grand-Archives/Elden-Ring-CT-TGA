#ifndef _TGA_DBGHELP_H
#define _TGA_DBGHELP_H

#include <stdint.h>

typedef struct _MODULEINFO {
    void* lpBaseOfDll;
    uint32_t SizeOfImage;
    void* EntryPoint;
} MODULEINFO, *LPMODULEINFO;

extern uint32_t UnDecorateSymbolName(
    const char* name,
    char* outputString,
    uint32_t maxStringLength,
    uint32_t flags
);

#endif