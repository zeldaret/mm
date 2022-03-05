#ifndef Z_OBJ_NOZOKI_H
#define Z_OBJ_NOZOKI_H

#include "global.h"

struct ObjNozoki;

typedef void (*ObjNozokiActionFunc)(struct ObjNozoki*, GlobalContext*);

#define OBJNOZOKI_GET_SWITCHFLAG1(thisx) ((thisx)->params & 0x7F)
#define OBJNOZOKI_GET_180(thisx) (((thisx)->params >> 7) & 3)
#define OBJNOZOKI_GET_200(thisx) ((thisx)->params & 0x200)
#define OBJNOZOKI_GET_400(thisx) ((thisx)->params & 0x400)
#define OBJNOZOKI_GET_SWITCHFLAG2(thisx) (((thisx)->params >> 9) & 0x7F)

#define OBJNOZOKI_400 0x400

typedef struct ObjNozoki {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ u8 unk_15C;
    /* 0x015D */ u8 unk_15D;
    /* 0x015E */ s8 unk_15E;
    /* 0x015F */ s8 unk_15F;
    /* 0x0160 */ ObjNozokiActionFunc actionFunc;
} ObjNozoki; // size = 0x164

extern const ActorInit Obj_Nozoki_InitVars;

#endif // Z_OBJ_NOZOKI_H
