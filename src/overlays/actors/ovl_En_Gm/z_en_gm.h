#ifndef Z_EN_GM_H
#define Z_EN_GM_H

#include "global.h"

struct EnGm;

typedef void (*EnGmActionFunc)(struct EnGm*, GlobalContext*);
typedef s32 (*EnGmUnkFunc)(struct EnGm*, GlobalContext*);
typedef void (*EnGmUnkFunc2)(struct EnGm*, GlobalContext*);

typedef struct EnGm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnGmActionFunc actionFunc;
    /* 0x018C */ EnGmUnkFunc2 unk_18C;
    /* 0x0190 */ ColliderCylinder colliderCylinder;
    /* 0x01DC */ ColliderSphere colliderSphere;
    /* 0x0234 */ Path* unk_234;
    /* 0x0238 */ Vec3f unk_238;
    /* 0x0244 */ f32 unk_244;
    /* 0x0248 */ s32 unk_248;
    /* 0x024C */ s32 unk_24C;
    /* 0x0250 */ s32 unk_250;
    /* 0x0254 */ s32 unk_254;
    /* 0x0258 */ u8 unk_258;
    /* 0x0259 */ u8 unk_259;
    /* 0x025C */ s32 unk_25C;
    /* 0x0260 */ s8 unk_260;
    /* 0x0261 */ s8 unk_261;
    /* 0x0262 */ s8 unk_262;
    /* 0x0264 */ s32* unk_264;
    /* 0x0268 */ Actor* unk_268;
    /* 0x026C */ UNK_TYPE1 unk26C[0xC];
    /* 0x0278 */ Vec3f unk_278;
    /* 0x0284 */ Vec3f unk_284;
    /* 0x0290 */ Vec3f unk_290;
    /* 0x029C */ Vec3f unk_29C;
    /* 0x02A8 */ Vec3s unk_2A8;
    /* 0x02AE */ Vec3s unk_2AE;
    /* 0x02B4 */ Vec3s jointTable[20];
    /* 0x032C */ Vec3s morphTable[20];
    /* 0x03A4 */ u16 unk_3A4;
    /* 0x03A6 */ u16 unk_3A6;
    /* 0x03A8 */ f32 unk_3A8;
    /* 0x03AC */ f32 unk_3AC;
    /* 0x03B0 */ f32 unk_3B0;
    /* 0x03B4 */ f32 unk_3B4;
    /* 0x03B8 */ s16 unk_3B8;
    /* 0x03BA */ s16 unk_3BA;
    /* 0x03BC */ s16 unk_3BC;
    /* 0x03BE */ s16 unk_3BE;
    /* 0x03C0 */ s16 unk_3C0;
    /* 0x03C2 */ s16 unk_3C2;
    /* 0x03C4 */ s16 unk_3C4;
    /* 0x03C6 */ s16 unk_3C6;
    /* 0x03C8 */ s16 unk_3C8;
    /* 0x03CA */ s16 unk_3CA;
    /* 0x03CC */ s16 unk_3CC;
    /* 0x03CE */ s16 unk_3CE;
    /* 0x03D0 */ s16 unk_3D0;
    /* 0x03D2 */ s16 unk_3D2[3];
    /* 0x03D8 */ s16 unk_3D8[3];
    /* 0x03DE */ s16 unk_3DE;
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 unk_3E2;
    /* 0x03E4 */ EnGmUnkFunc unk_3E4;
    /* 0x03E8 */ s32 unk_3E8;
    /* 0x03EC */ UNK_TYPE1 unk3EC[0x4];
    /* 0x03F0 */ s32 unk_3F0;
    /* 0x03F4 */ s32 unk_3F4;
    /* 0x03F8 */ s32 unk_3F8;
    /* 0x03FC */ s32 unk_3FC;
    /* 0x0400 */ s32 unk_400;
} EnGm; // size = 0x404

extern const ActorInit En_Gm_InitVars;

#endif // Z_EN_GM_H
