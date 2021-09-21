#ifndef Z_OBJ_UM_H
#define Z_OBJ_UM_H

#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

struct ObjUm;

typedef void (*ObjUmActionFunc)(struct ObjUm*, GlobalContext*);

typedef struct ObjUm {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjUmActionFunc actionFunc;
    /* 0x160 */ SkelAnime unk_160;
    /* 0x1A4 */ Vec3s unk_1A4[0x16];
    /* 0x228 */ Vec3s unk_228[0x16];
    /* 0x2AC */ s16 unk_2AC;
    /* 0x2AE */ s16 unk_2AE;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B4 */ s32 unk_2B4;
    /* 0x2B8 */ EnHorse* unk_2B8;
    /* 0x2BC */ s32 unk_2BC;
    /* 0x2BE */ s32 unk_2BE;
    /* 0x2C4 */ Vec3f unk_2C4;
    /* 0x2D0 */ Vec3f unk_2D0;
    /* 0x2DC */ Vec3f unk_2DC;
    /* 0x2E8 */ Vec3f unk_2E8;
    /* 0x2F4 */ s32 unk_2F4;
    /* 0x2BC */ Vec3s unk_2F8;
    /* 0x2FE */ Vec3s unk_2FE;
    /* 0x304 */ s32 unk_304;
    /* 0x308 */ Vec3f unk_308;
    /* 0x314 */ s32 unk_314[3];
    /* 0x320 */ s32 unk_320[3];
    /* 0x32C */ Vec3f unk_32C[3];
    /* 0x350 */ s32 unk_350;
    /* 0x354 */ s32 unk_354;
    /* 0x358 */ EnHorse* unk_358;
    /* 0x35C */ EnHorse* unk_35C;
    /* 0x360 */ Vec3f unk_360[0x10];
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ ColliderCylinder unk_424[2]; // horses
    /* 0x4BC */ Vec3f unk_4BC;
    /* 0x4C8 */ u16 unk_4C8;
    /* 0x4CC */ s32 unk_4CC;
    /* 0x4D0 */ s32 unk_4D0;
    /* 0x4D4 */ s32 unk_4D4;
    /* 0x4D8 */ s32 unk_4D8;
    /* 0x4DC */ s32 unk_4DC;
    /* 0x4E0 */ s32 unk_4E0;
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

#endif // Z_OBJ_UM_H
