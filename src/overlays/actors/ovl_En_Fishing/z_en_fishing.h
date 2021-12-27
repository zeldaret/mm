#ifndef Z_EN_FISHING_H
#define Z_EN_FISHING_H

#include "global.h"

struct EnFishing;

typedef void (*EnFishingActionFunc)(struct EnFishing*, GlobalContext*);

typedef struct EnFishing {
    /* 0x000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x004];
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ u8 unk_149;
    /* 0x014A */ u8 unk_14A;
    /* 0x014C */ s16 unk_14C;
    /* 0x014E */ u8 unk_14E;
    /* 0x014F */ u8 unk_14F;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s16 unk_158;
    /* 0x015A */ s16 unk_15A;
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ s16 unk_164;
    /* 0x0166 */ s16 unk_166;
    /* 0x0168 */ s16 unk_168;
    /* 0x016A */ s16 unk_16A;
    /* 0x016C */ s16 unk_16C;
    /* 0x016E */ s16 unk_16E;
    /* 0x0170 */ s16 unk_170;
    /* 0x0172 */ s16 unk_172[4];
    /* 0x017C */ f32 unk_17C;
    /* 0x0180 */ f32 unk_180;
    /* 0x0184 */ f32 unk_184;
    /* 0x0188 */ f32 unk_188;
    /* 0x018C */ f32 unk_18C;
    /* 0x0190 */ f32 unk_190;
    /* 0x0194 */ f32 unk_194;
    /* 0x0198 */ s16 unk_198;
    /* 0x019A */ s16 unk_19A;
    /* 0x019C */ s16 unk_19C;
    /* 0x01A0 */ f32 unk_1A0;
    /* 0x01A4 */ f32 unk_1A4;
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ Vec3f unk_1AC;
    /* 0x01B8 */ Vec3f fishMouthPos;
    /* 0x01C4 */ s16 unk_1C4[3];
    /* 0x01CA */ u8 unk_1CA;
    /* 0x01CB */ u8 unk_1CB;
    /* 0x01CC */ u8 unk_1CC;
    /* 0x01CD */ u8 unk_1CD;
    /* 0x01D0 */ SkelAnime skelAnime;
    /* 0x0214 */ LightNode* lightNode;
    /* 0x0218 */ LightInfo lightInfo;
    /* 0x0228 */ ColliderJntSph collider;
    /* 0x0248 */ ColliderJntSphElement colliderElements[12];
} EnFishing; // size = 0x548

extern const ActorInit En_Fishing_InitVars;

#endif // Z_EN_FISHING_H
