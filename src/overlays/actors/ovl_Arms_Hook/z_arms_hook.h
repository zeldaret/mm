#ifndef _Z_ARMS_HOOK_H_
#define _Z_ARMS_HOOK_H_

#include <global.h>

struct ArmsHook;

typedef struct ArmsHook {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xCC];
} ArmsHook; // size = 0x210

extern const ActorInit Arms_Hook_InitVars;

#endif
