#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

#define OBJ_TOKEIDAI_TYPE(thisx) (((thisx)->params & 0xF000) >> 12)

struct ObjTokeidai;

typedef void (*ObjTokeidaiActionFunc)(struct ObjTokeidai*, GlobalContext*);

typedef struct ObjTokeidai {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ void* unk_144;
    /* 0x0148 */ void* unk_148;
    /* 0x014C */ s16 unk_14C;
    /* 0x014E */ s16 unk_14E;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s32 unk_158;
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ char unk_164[0x4];
    /* 0x0168 */ s32 unk_168;
    /* 0x016C */ s32 unk_16C;
    /* 0x0170 */ u16 unk_170;
    /* 0x0174 */ ObjTokeidaiActionFunc actionFunc;
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H
