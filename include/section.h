#ifndef _SECTION_H_
#define _SECTION_H_

#include "PR/ultratypes.h"

extern u32 boot_text_start;
extern u32 boot_text_end;

extern u32 boot_data_start;
extern u32 boot_data_end;

extern u32 boot_rodata_start;
extern u32 boot_rodata_end;

extern u32 boot_bss_start;
extern u32 boot_bss_end;

extern u32 code_text_start;
extern u32 code_text_end;

extern u32 code_data_start;
extern u32 code_data_end;

extern u32 code_rodata_start;
extern u32 code_rodata_end;

extern u32 code_bss_start;
extern u32 code_bss_end;

#endif
