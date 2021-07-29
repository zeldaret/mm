#ifndef Z_EN_VM_H
#define Z_EN_VM_H

#include "global.h"

struct EnVm;

typedef void (*EnVmActionFunc)(struct EnVm* this, GlobalContext* globalCtx);

typedef struct EnVm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC8];
    /* 0x020C */ EnVmActionFunc actionFunc;
    /* 0x0210 */ char unk_210[0x14C];
} EnVm; // size = 0x35C

extern const ActorInit En_Vm_InitVars;

#endif // Z_EN_VM_H
