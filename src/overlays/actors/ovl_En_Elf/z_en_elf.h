#ifndef Z_EN_ELF_H
#define Z_EN_ELF_H

#include "global.h"

struct EnElf;

typedef struct EnElf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
    /* 0x264 */ u16 unk264;
    /* 0x266 */ char unk_266[0xE];
} EnElf; // size = 0x274

extern const ActorInit En_Elf_InitVars;

#endif // Z_EN_ELF_H
