#ifndef Z_EN_GURUGURU_H
#define Z_EN_GURUGURU_H

#include <global.h>

struct EnGuruguru;

typedef void (*EnGuruguruActionFunc)(struct EnGuruguru*, GlobalContext*);

typedef struct EnGuruguru {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTbl[16];
    /* 0x1E8 */ Vec3s transitionDrawTbl[16];
    /* 0x248 */ EnGuruguruActionFunc actionFunc;
    /* 0x24C */ s16 headZRot;
    /* 0x24E */ s16 headXRot;
    /* 0x250 */ char unk250[0x2];
    /* 0x252 */ s16 headZRotTarget;
    /* 0x254 */ s16 headXRotTarget;
    /* 0x256 */ char unk256[0xE];
    /* 0x264 */ s16 unusedTimer; // set to 6 and decremented, but never has any effect
    /* 0x266 */ s16 unk266;
    /* 0x268 */ s16 unk268;
    /* 0x26C */ f32 frameCount;
    /* 0x270 */ u8 unk270;
    /* 0x272 */ s16 unk272; // set, but never used
    /* 0x274 */ s16 textIDIndex;
    /* 0x276 */ s16 textureIndex;
    /* 0x278 */ ColliderCylinder collider;
} EnGuruguru; // size = 0x2C4

extern const ActorInit En_Guruguru_InitVars;

#endif // Z_EN_GURUGURU_H
