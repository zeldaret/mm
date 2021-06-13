#ifndef Z_EN_OSSAN_H
#define Z_EN_OSSAN_H

#include <global.h>

#include "../ovl_En_GirlA/z_en_girla.h"

struct EnOssan;

typedef void (*EnOssanActionFunc)(struct EnOssan*, GlobalContext*);
typedef void (*EnOssanUnkFunc)(struct EnOssan*);

typedef struct EnOssanUnkStruct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} EnOssanUnkStruct; // size = 0x8;

typedef struct {
    /* 0x00 */ u32 stickColorR;
    /* 0x04 */ u32 stickColorG;
    /* 0x08 */ u32 stickColorB;
    /* 0x0C */ u32 stickColorA;
    /* 0x10 */ f32 stickTexX;
    /* 0x14 */ f32 stickTexY;
    /* 0x18 */ u32 arrowColorR;
    /* 0x1C */ u32 arrowColorG;
    /* 0x20 */ u32 arrowColorB;
    /* 0x24 */ u32 arrowColorA;
    /* 0x28 */ f32 arrowTexX;
    /* 0x2C */ f32 arrowTexY;
    /* 0x30 */ f32 texZ; // Used for both stickTexZ and arrowTexZ
    /* 0x34 */ s32 isEnabled;
} StickDirectionPrompt; // size = 0x38

typedef struct EnOssan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnOssanActionFunc actionFunc;
    /* 0x18C */ EnOssanActionFunc actionFunc2;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ s16 unk1DC;
    /* 0x1DE */ s8 unk1DE;
    /* 0x1DF */ char unk1DF[0x1];
    /* 0x1E0 */ s16 unk1E0;
    /* 0x1E2 */ s16 unk1E2;
    /* 0x1E4 */ EnOssanUnkFunc unkFunc;
    /* 0x1E8 */ EnGirlA *shopItems[8];
    /* 0x208 */ s32 unk208;
    /* 0x20C */ s32 unk20C;
    /* 0x210 */ u8 unk210;
    /* 0x211 */ u8 unk211;
    /* 0x212 */ char unk212[0x2];
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ u32 unkColorR;
    /* 0x224 */ u32 unkColorG;
    /* 0x228 */ u32 unkColorB;
    /* 0x22C */ u32 unkColorA;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 unk234;
    /* 0x235 */ u8 unk235;
    /* 0x236 */ u8 unk236;
    /* 0x237 */ char unk237[0x1];
    /* 0x238 */ StickDirectionPrompt stickRightPrompt;
    /* 0x270 */ StickDirectionPrompt stickLeftPrompt;
    /* 0x2A8 */ f32 arrowAnimTween;
    /* 0x2AC */ f32 stickAnimTween;
    /* 0x2B0 */ u8 arrowAnimState;
    /* 0x2B1 */ u8 stickAnimState;
    /* 0x2B2 */ char unk2B2[0x2];
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ s16 unk2B8;
    /* 0x2BA */ s16 unk2BA;
    /* 0x2BC */ s16 unk2BC;
    /* 0x2BE */ s16 unk2BE;
    /* 0x2C0 */ s16 unk2C0;
    /* 0x2C2 */ s16 unk2C2;
    /* 0x2C4 */ u16 unk2C4;
    /* 0x2C6 */ Vec3s unk2C6;
    /* 0x2CC */ Vec3s unk2CC;
    /* 0x2D2 */ s16 unk2D2[0x13];
    /* 0x2F8 */ s16 unk2F8[0x13];
    /* 0x31E */ Vec3s limbDrawTbl[19];
    /* 0x390 */ Vec3s transitionDrawTbl[19];
    /* 0x402 */ s16 unk402;
    /* 0x404 */ s16 unk404;
    /* 0x406 */ s16 unk406;
    /* 0x408 */ char unk408[0x2];
    /* 0x40A */ u16 unk40A;
} EnOssan; // size = 0x40C

extern const ActorInit En_Ossan_InitVars;

#endif // Z_EN_OSSAN_H
