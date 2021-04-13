#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include <global.h>

struct EnNiw;

typedef void (*EnNiwActionFunc)(struct EnNiw*, GlobalContext*);

typedef struct {
    /* 0x0000 */ u8 type;
    /* 0x0004 */ Vec3f pos;
    /* 0x0010 */ Vec3f vel;
    /* 0x001C */ Vec3f accel;
    /* 0x0028 */ s16 life;
    /* 0x002A */ s16 unk_2A;
    /* 0x002C */ f32 scale;
    /* 0x0030 */ f32 unk_30;
    /* 0x0034 */ u8 timer;
} EnNiwFeather; // size = 0x0038

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s limbDrawTbl[0x10];
    /* 0x1E8 */ Vec3s transitionDrawtable[0x10];
    /* 0x248 */ EnNiwActionFunc actionFunc;
    /* 0x24C */ s16 unk24C;// used in func_808922D0
    /* 0x24E */ s16 unk24E;
    /* 0x250 */ s16 unk250;
    /* 0x252 */ s16 unk252;// used by func_80892248
    /* 0x254 */ s16 unk254; // changed in func_808917F8 unsure
    /* 0x256 */ s16 sfxTimer1; 
    /* 0x258 */ s16 sfxTimer2;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;
    /* 0x260 */ s16 unk260;
    /* 0x262 */ s16 unk262;
    /* 0x264 */ f32 unk264[10]; 
    /* 0x28C */ s16 unk28C; // used in EnNiw_Update
    /* 0x28E */ s16 unk28E; // might not be signed
    /* 0x290 */ s16 unk290;
    /* 0x292 */ s16 unk292;
    /* 0x294 */ s16 unk294; // padd
    /* 0x296 */ s16 unk296; // func_80891320
    /* 0x298 */ s16 unk298; // func_8089262C 
    /* 0x29C */ s16 unk29A; // changed by func_808917F8
    /* 0x29C */ u16 unk29C; // changed by func_80892248
    /* 0x29E */ s16 unk29E; // func_80891D78 
    /* 0x2A0 */ s16 unk2A0; // func_808920A0
    /* 0x2A2 */ s16 paramsCopy;
    /* 0x2A4 */ Vec3f unk2A4; // this actors starting position
    /* 0x2B0 */ Vec3f unk2B0;// this actors starting position
    /* 0x2BC */ Vec3f unk2BC;
    /* 0x2C8 */ f32 unk2C8; //func_80891320
    /* 0x2CC */ f32 unk2CC; //func_80891320
    /* 0x2D0 */ f32 unk2D0; //func_80891320
    /* 0x2D4 */ f32 unk2D4; //func_80891320
    /* 0x2D8 */ f32 unk2D8; //func_80891320
    /* 0x2DC */ f32 unk2DC; //func_80891320
    /* 0x2E0 */ f32 unk2E0; //func_80891320
    /* 0x2E4 */ f32 unk2E4; //func_80891320
    /* 0x2E8 */ s16 unk2E8;
    /* 0x2EA */ s16 unk2EA; // func_808919E8
    /* 0x2EC */ u16 unk2EC; // used in func_80891D78 
    /* 0x2EE */ u8  unk2EE[0x6]; // pad
    /* 0x2F4 */ f32 unk2F4; // used func_808917F8
    /* 0x2F8 */ f32 unk2F8; // used func_808917F8
    /* 0x2FC */ f32 unk2FC; // used func_808917F8
    /* 0x300 */ f32 unk300; // used func_808917F8
    /* 0x304 */ f32 unk304; 
    /* 0x308 */ f32 unk308; // init 10f
    /* 0x30C */ s16 unk30C; //unused?
    /* 0x310 */ ColliderCylinder collider;
    /* 0x35C */ EnNiwFeather feathers[0x14];

} EnNiw; // size = 0x7BC

extern const ActorInit En_Niw_InitVars;

extern SkeletonHeader D_06002530;
extern AnimationHeader D_060000E8;

// feather display list?
extern void* D_060023B0;
extern void* D_06002428;


#endif // Z_EN_NIW_H
