#ifndef Z_OBJ_HGDOOR_H
#define Z_OBJ_HGDOOR_H

#include <global.h>

struct ObjHgdoor;

typedef void (*ObjHgdoorActionFunc)(struct ObjHgdoor*, GlobalContext*);

#define OBJHGDOOR_IS_RIGHT_DOOR(thisx) \
    ((thisx)->params & 0x8000) // door on the right when looking at the cabinet

typedef struct ObjHgdoor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjHgdoorActionFunc actionFunc;
    /* 0x160 */ s16 cutscene;
    /* 0x162 */ s16 rotation;
    /* 0x164 */ s16 timer;
    /* 0x166 */ u16 unk166;
} ObjHgdoor; // size = 0x168

extern const ActorInit Obj_Hgdoor_InitVars;

#endif // Z_OBJ_HGDOOR_H
