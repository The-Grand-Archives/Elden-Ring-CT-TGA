#ifndef _TGA_FD4_SINGLETON
#define _TGA_FD4_SINGLETON

#include "mem_region.h"
#include "pattern.h"
#include "string.h"

typedef struct _fd4_singleton_basic_info {
    intptr_t address;
    const char* full_name;
    const char* simple_name;
} fd4_singleton_basic_info;

extern size_t strnlen(const char* str, size_t max_len);
size_t find_fd4_singletons(fd4_singleton_basic_info* out_array, size_t out_array_size) {
    region text, data, rdata;
    region_from_module(&text, NULL, ".text");
    region_from_module(&data, NULL, ".data");
    region_from_module(&rdata, NULL, ".rdata");

    pattern null_check;
    bool s = pattern_init(&null_check,
        "48 8b ? ? ? ? ? "  //  0 MOV REG, [MEM]
        "48 85 ? "          //  7 TEST REG, REG
        "75 2e "            // 10 JNZ +2e
        "48 8d 0d ? ? ? ? " // 12 LEA RCX, [runtime_class_metadata]
        "e8 ? ? ? ? "       // 19 CALL get_singleton_name
        "4c 8b c8 "         // 24 MOV R9, RAX
        "4c 8d 05 ? ? ? ? " // 27 LEA R8, [%s:未初期化のシングルトンにアクセスしました]
        "ba ? ? 00 00 "     // 34 MOV EDX, 0x0000????
        "48 8d 0d ? ? ? ? " // 39 LEA RCX, [file_path]
        "e8 ? ? ? ?"        // 46 CALL log_thunk
    );
    if (!s) return 0;

    const size_t null_checks_size = 0x4000; // There should be a few thousand, this is overkill but w/e
    intptr_t* null_checks = calloc(null_checks_size, sizeof(uintptr_t));

    int num_null_checks = pattern_search(&text, 
        null_check.bytes, null_check.mask, null_check.size,
        null_checks, null_checks_size);

    int num_out = 0;
    for (int i = 0; i < num_null_checks; i++) {
        intptr_t candidate = null_checks[i];

        // Check if static address in data section
        intptr_t static_addr = candidate + 7 + *(int32_t*)(candidate + 3);
        if (!ptr_in_region(static_addr, &data)) continue;

        // Check if runtime_class_ptr is in range
        intptr_t runtime_class_ptr = candidate + 19 + *(int32_t*)(candidate + 15);
        if (!ptr_in_region(runtime_class_ptr, &data)) continue;

        // Check if get_singleton_name function is in range
        intptr_t get_singleton_name = candidate + 24 + *(int32_t*)(candidate + 20);
        if (!ptr_in_region(get_singleton_name, &text)) continue;

        // Check if FD4Singleton header path is there
        const char* filepath_ptr = (char*)(candidate + 46 + *(int32_t*)(candidate + 42));
        if (!ptr_in_region(filepath_ptr, &rdata)) continue;

        // Check if FD4Singleton path string ends with correct header name
        size_t filepath_len = strnlen(filepath_ptr, 256);
        if (filepath_len < 10 || filepath_len == 256) continue;
        if (strcmp(filepath_ptr + filepath_len - 14, "FD4Singleton.h")) continue;

        // Try to query the name
        const char* name = ((char*(*)(intptr_t))get_singleton_name)(runtime_class_ptr);
        if (!name) continue;

        // Remove namespace from the name, if any
        const char* simple_name = strrchr(name, ':') + 1;
        if (!(simple_name-1)) simple_name = name;

        // Check if address was already added, or we are out of space
        if (num_out == out_array_size) break;
        bool already_found = false;
        for (int j = 0; j < num_out; j++) {
            if (out_array[j].address != static_addr) continue;
            already_found = true;
            break; 
        }
        if (already_found) continue;

        out_array[num_out].address = static_addr;
        out_array[num_out].full_name = name;
        out_array[num_out].simple_name = simple_name;
        num_out++;
    }

    free(null_checks);
    pattern_destroy(&null_check);
    return num_out;
}

#endif