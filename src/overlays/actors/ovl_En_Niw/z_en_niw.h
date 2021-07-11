#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include <global.h>

struct EnNiw;

typedef void (*EnNiwActionFunc)(struct EnNiw*, GlobalContext*);

typedef struct {
    /* 0x0000 */ u8 isEnabled;
    /* 0x0004 */ Vec3f pos;
    /* 0x0010 */ Vec3f vel;
    /* 0x001C */ Vec3f accel;
    /* 0x0028 */ s16 life;
    /* 0x002A */ s16 zRotStart;
    /* 0x002C */ f32 scale;
    /* 0x0030 */ f32 zRot;
    /* 0x0034 */ u8 timer;
} EnNiwFeather; // size = 0x38

#define ENNIW_LIMBCOUNT 16
#define ENNIW_FEATHERCOUNT 20

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s limbDrawTbl[ENNIW_LIMBCOUNT];
    /* 0x1E8 */ Vec3s transitionDrawtable[ENNIW_LIMBCOUNT];
    /* 0x248 */ EnNiwActionFunc actionFunc;
    /* 0x24C */ s16 unkTimer24C;
    /* 0x24E */ s16 unkTimer24E;
    /* 0x250 */ s16 unkTimer250;
    /* 0x252 */ s16 unkTimer252;
    /* 0x254 */ s16 unkTimer254;
    /* 0x256 */ s16 sfxTimer1; 
    /* 0x258 */ s16 flutterSfxTimer;
    /* 0x25A */ s16 unusedTimer25A;
    /* 0x25C */ s16 yawTimer; // every 70 frames rechecks yawToPlayer
    /* 0x25E */ s16 unusedTimer25E;
    /* 0x260 */ s16 unkTimer260;
    /* 0x264 */ f32 unk264[10]; 
    /* 0x28C */ s16 unusedCounter28C;
    /* 0x28E */ s16 unknownState28E;
    /* 0x290 */ s16 unk290;
    /* 0x292 */ s16 unk292;
    /* 0x294 */ s16 pad294;
    /* 0x296 */ s16 unk296;
    /* 0x298 */ s16 unk298;
    /* 0x29C */ s16 unk29A;
    /* 0x29C */ u16 unk29C;
    /* 0x29E */ s16 unk29E;
    /* 0x2A0 */ s16 isStormActive;
    /* 0x2A2 */ s16 niwType;
    /* 0x2A4 */ Vec3f unk2A4;
    /* 0x2B0 */ Vec3f unk2B0;
    /* 0x2BC */ Vec3f unk2BC;
    /* 0x2C8 */ f32 limb7Rotz;
    /* 0x2CC */ f32 limb7Roty;
    /* 0x2D0 */ f32 limb7Rotx;
    /* 0x2D4 */ f32 limbBRotz;
    /* 0x2D8 */ f32 limbBRoty;
    /* 0x2DC */ f32 limbBRotx;
    /* 0x2E0 */ f32 limbDRot;
    /* 0x2E4 */ f32 limbFRot;
    /* 0x2E8 */ s16 yawTowardsPlayer;
    /* 0x2EA */ s16 unk2EA;
    /* 0x2EC */ s16 unk2EC;
    /* 0x2EE */ UNK_TYPE1  pad2EE[0x6];
    /* 0x2F4 */ f32 unusedFloat2F4;
    /* 0x2F8 */ f32 unusedFloat2F8;
    /* 0x2FC */ f32 unusedFloat2FC;
    /* 0x300 */ f32 unk300;
    /* 0x304 */ f32 unk304;
    /* 0x308 */ f32 unk308;
    /* 0x30C */ s32 pad30C;
    /* 0x310 */ ColliderCylinder collider;
    /* 0x35C */ EnNiwFeather feathers[ENNIW_FEATHERCOUNT];
} EnNiw; // size = 0x7BC

// in init, any value below zero becomes zero
//  however, in vanilla, only 0xFFFF (-1) exists
#define ENNIW_TYPE_VANILLA 0xFFFF
#define ENNIW_TYPE_REGULAR 0
#define ENNIW_TYPE_UNK1 1
#define ENNIW_TYPE_UNK2 2
// the attacking cuccos are not here, they are a different actor:
//  ovl_En_Attack_Niw

extern FlexSkeletonHeader D_06002530;
extern AnimationHeader D_060000E8;

// feather display list?
extern Gfx D_060023B0[];
extern Gfx D_06002428[];

#endif // Z_EN_NIW_H
