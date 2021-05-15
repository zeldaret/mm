#ifndef Z_OBJ_ENDING_H
#define Z_OBJ_ENDING_H

#include <global.h>

struct ObjEnding;

typedef struct {
    /* 0x0 */   UNK_TYPE4 unk0;
    /* 0x4 */   Gfx* dl;
<<<<<<< HEAD
    /* 0x8 */   AnimatedTexture *texture;
=======
    /* 0x8 */   AnimatedMaterial *texture;
>>>>>>> upstream/master
} unkStruct; // size = 0xC

typedef struct ObjEnding {
    /* 0x000 */ Actor actor;
    /* 0x144 */ unkStruct* unk144;
<<<<<<< HEAD
    /* 0x148 */ AnimatedTexture* texture;
=======
    /* 0x148 */ AnimatedMaterial* texture;
>>>>>>> upstream/master
} ObjEnding; // size = 0x14C

extern const ActorInit Obj_Ending_InitVars;

#endif // Z_OBJ_ENDING_H
