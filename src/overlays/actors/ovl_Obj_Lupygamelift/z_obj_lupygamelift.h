#ifndef Z_OBJ_LUPYGAMELIFT_H
#define Z_OBJ_LUPYGAMELIFT_H

#include "global.h"

#define OBJLUPYGAMELIFT_GET_PATH(thisx) ((thisx)->params & 0x7F)
#define OBJLUPYGAMELIFT_GET_7(thisx) (((thisx)->params >> 7) & 0x1F)
#define OBJLUPYGAMELIFT_GET_C(thisx) (((thisx)->params >> 0xC) & 1)

struct ObjLupygamelift;

typedef void (*ObjLupygameliftActionFunc)(struct ObjLupygamelift*, GlobalContext*);

typedef struct ObjLupygamelift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjLupygameliftActionFunc actionFunc;
    /* 0x160 */ f32 unk_160;
    /* 0x164 */ s32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ Vec3s* unk_16C;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ UNK_TYPE1 pad_172[2];
} ObjLupygamelift; /* size = 0x174 */

extern const ActorInit Obj_Lupygamelift_InitVars;

#endif // Z_OBJ_LUPYGAMELIFT_H
