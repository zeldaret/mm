#ifndef Z_EN_OWL_H
#define Z_EN_OWL_H

#include "global.h"

struct EnOwl;

typedef void (*EnOwlActionFunc)(struct EnOwl*, GlobalContext*);
typedef void (*EnOwlFunc)(struct EnOwl*);

#define ENOWL_GET_F000(thisx) (((thisx)->params & 0xF000) >> 0xC)
#define ENOWL_GET_Type(thisx) (((thisx)->params & 0xF80) >> 7)
#define ENOWL_GET_SwitchFlag(thisx) ((thisx)->params & 0x7F)

typedef enum {
    /* 0x001 */ ENOWL_GET_Type_1 = 1,
    /* 0x002 */ ENOWL_GET_Type_2,
    /* 0x003 */ ENOWL_GET_Type_3,
    /* 0x01E */ ENOWL_GET_Type_30 = 30,
    /* 0x3E8 */ ENOWL_GET_Type_1000 = 1000,
} EnOwlType;

typedef struct EnOwl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime1;
    /* 0x01D4 */ Vec3s jointTable1[21];
    /* 0x0252 */ Vec3s morphTable1[21];
    /* 0x02D0 */ SkelAnime skelAnime2;
    /* 0x0314 */ Vec3s jointTable2[16];
    /* 0x0374 */ Vec3s morphTable2[16];
    /* 0x03D4 */ SkelAnime* skelAnime3;
    /* 0x03D8 */ s16 unk_3D8;
    /* 0x03DA */ s16 unk_3DA;
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ s16 unk_3DE;
    /* 0x03E0 */ s16 eyeTexIndex;
    /* 0x03E2 */ s16 blinkTimer;
    /* 0x03E4 */ f32 unk_3E4;
    /* 0x03E8 */ u16 actionFlags;
    /* 0x03EA */ s16 unk_3EA;
    /* 0x03EC */ s16 unk_3EC;
    /* 0x03F0 */ f32 unk_3F0;
    /* 0x03F4 */ Path* path;
    /* 0x03F8 */ s32 unk_3F8;
    /* 0x03FC */ s32 unk_3FC;
    /* 0x0400 */ s16 unk_400[3];
    /* 0x0406 */ s16 unk_406;
    /* 0x0408 */ u8 unk_408;
    /* 0x0409 */ u8 unk_409;
    /* 0x040A */ u8 unk_40A;
    /* 0x040B */ u8 unk_40B;
    /* 0x040C */ u8 unk_40C;
    /* 0x040D */ u8 unk_40D;
    /* 0x0410 */ EnOwlActionFunc actionFunc;
    /* 0x0414 */ EnOwlFunc unk_414;
} EnOwl; // size = 0x418

extern const ActorInit En_Owl_InitVars;

#endif // Z_EN_OWL_H
