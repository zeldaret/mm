#ifndef Z_OBJ_BOYO_H
#define Z_OBJ_BOYO_H

#include "global.h"

struct ObjBoyo;

typedef void (*BumperCollideActorFunc)(struct ObjBoyo*, void*);

typedef struct {
    /* 0x0 */ s16 id;
    /* 0x4 */ BumperCollideActorFunc actorCollideFunc;
} BumperCollideInfo; // size = 0x8

typedef struct ObjBoyo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ AnimatedMaterial* unk_190;
    /* 0x194 */ s16 unk_194;
    /* 0x196 */ s16 unk_196;
    /* 0x198 */ f32 unk_198;
    /* 0x19C */ f32 unk_19C;
    /* 0x1A0 */ f32 unk_1A0;
    /* 0x1A4 */ s16 unk_1A4;
    /* 0x1A6 */ s16 unk_1A6;
    /* 0x1A8 */ s16 unk_1A8;
    /* 0x1AA */ s16 unk_1AA;
    /* 0x1AC */ s16 unk_1AC;
} ObjBoyo; // size = 0x1B0

extern const ActorInit Obj_Boyo_InitVars;

#endif // Z_OBJ_BOYO_H
