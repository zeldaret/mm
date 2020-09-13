#ifndef Z_EN_VM_H
#define Z_EN_VM_H

#include <global.h>

struct EnVm;

typedef struct EnVm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x218];
} EnVm; // size = 0x35C

extern const ActorInit En_Vm_InitVars;

#endif // Z_EN_VM_H
