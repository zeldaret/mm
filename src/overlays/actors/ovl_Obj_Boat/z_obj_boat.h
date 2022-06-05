#ifndef Z_OBJ_BOAT_H
#define Z_OBJ_BOAT_H

#include "global.h"

struct ObjBoat;

typedef struct ObjBoat {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ u8 unk15C;
    /* 0x15D */ s8 unk15D;
    /* 0x15E */ u8 unk15E;                          /* inferred */
    /* 0x15F */ u8 unk15F;                          /* inferred */
    /* 0x160 */ s16 unk160;                         /* inferred */
    /* 0x162 */ char pad162[1];
    /* 0x163 */ s8 unk163;
    /* 0x164 */ Vec3s *unk164;
} ObjBoat;

extern const ActorInit Obj_Boat_InitVars;

#endif // Z_OBJ_BOAT_H
