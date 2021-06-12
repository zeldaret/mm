#ifndef Z_EN_ENCOUNT2_H
#define Z_EN_ENCOUNT2_H

#include <global.h>

struct EnEncount2;

typedef void (*EnEncount2ActionFunc)(struct EnEncount2*, GlobalContext*);

typedef struct EnEncount2Particle{
   /* 0x00 */ u8 enabled;
   /* 0x04 */ Vec3f pos;
   /* 0x10 */ UNK_TYPE4 unk10;
   /* 0x14 */ s16 alpha;
   /* 0x16 */ s16 alphaFadeDelay; // frame count before alpha fade starts
   /* 0x18 */ Vec3f vel;
   /* 0x24 */ Vec3f accel;
   /* 0x30 */ f32 scale;

} EnEncount2Particle; // size = 0x34

typedef struct EnEncount2 {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ EnEncount2ActionFunc actionFunc;
    /* 0x0160 */ s16 deathTimer;
    /* 0x0162 */ s16 isPopped;
    /* 0x0164 */ s16 switchFlag;
    /* 0x0168 */ f32 scale;
    /* 0x016C */ f32 oscillationAngle;
    /* 0x0170 */ ColliderJntSph collider;
    /* 0x0190 */ ColliderJntSphElement colElement;
    /* 0x01D0 */ EnEncount2Particle particles[200];
} EnEncount2; // size = 0x2A70

#define GET_ENCOUNT2_SWITCH_FLAG(actor) ((s16)(((Actor*)actor)->params & 0x7F))

extern const ActorInit En_Encount2_InitVars;

extern CollisionHeader D_06002420;

extern Gfx D_06000A00[];
extern Gfx D_06000D78[];

#endif // Z_EN_ENCOUNT2_H
