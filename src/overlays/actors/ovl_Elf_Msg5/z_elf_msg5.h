#ifndef Z_ELF_MSG5_H
#define Z_ELF_MSG5_H

#include "z64actor.h"

#define ELFMSG5_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0x7F)
#define ELFMSG5_GET_FF(thisx) ((thisx)->params & 0xFF)

struct ElfMsg5;
struct PlayState;

typedef void (*ElfMsg5ActionFunc)(struct ElfMsg5*, struct PlayState*);

typedef struct ElfMsg5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ElfMsg5ActionFunc actionFunc;
} ElfMsg5; // size = 0x148

#endif // Z_ELF_MSG5_H
