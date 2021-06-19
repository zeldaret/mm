#ifndef Z_OBJ_ENDING_H
#define Z_OBJ_ENDING_H

#include <global.h>

struct ObjEnding;

typedef struct {
    /* 0x0 */   UNK_TYPE4 unk0;
    /* 0x4 */   Gfx* dl;
    /* 0x8 */   AnimatedMaterial *texture;
} unkStruct; // size = 0xC

typedef struct ObjEnding {
    /* 0x000 */ Actor actor;
    /* 0x144 */ unkStruct* unk144;
    /* 0x148 */ AnimatedMaterial* texture;
} ObjEnding; // size = 0x14C

extern const ActorInit Obj_Ending_InitVars;

#endif // Z_OBJ_ENDING_H
