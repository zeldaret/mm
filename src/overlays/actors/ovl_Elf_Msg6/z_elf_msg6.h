#ifndef Z_ELF_MSG6_H
#define Z_ELF_MSG6_H

#include "global.h"

struct ElfMsg6;

typedef void (*ElfMsg6ActionFunc)(struct ElfMsg6*, GlobalContext*);

#define ELFMSG6_GET_F(thisx) ((thisx)->params & 0xF)
#define ELFMSG6_GET_F0(thisx) (((thisx)->params & 0xF0) >> 4)
#define ELFMSG6_SWITCHFLAG(thisx) (((thisx)->params & 0xFE00) >> 9)

typedef struct ElfMsg6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsg6ActionFunc actionFunc;
} ElfMsg6; // size = 0x148

extern const ActorInit Elf_Msg6_InitVars;

#endif // Z_ELF_MSG6_H
