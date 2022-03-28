#ifndef Z_EN_SUTTARI_H
#define Z_EN_SUTTARI_H

#include "global.h"
#include "overlays/actors/ovl_En_Fsn/z_en_fsn.h"

struct EnSuttari;

typedef void (*EnSuttariActionFunc)(struct EnSuttari*, GlobalContext*);

#define ENSUTTARI_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9)

typedef struct EnSuttari {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFsn* enFsn;
    /* 0x148 */ EnSuttariActionFunc actionFunc;
    /* 0x14C */ UNK_TYPE1 unk_14C[0x4];
    /* 0x150 */ SkelAnime skelAnime;
    /* 0x194 */ UNK_TYPE1 unk_194[0x4];
    /* 0x198 */ ColliderCylinder collider;
    /* 0x1E4 */ u16 flags1;
    /* 0x1E6 */ u16 flags2;
    /* 0x1E8 */ u16 textId;
    /* 0x1EA */ UNK_TYPE1 unk_1EA[0x2];
    /* 0x1EC */ Path* paths[2];
    /* 0x1F4 */ s32 unk1F4[2];
    /* 0x1FC */ UNK_TYPE1 unk_1FC[0x1A];
    /* 0x216 */ Vec3s jointTable[16];
    /* 0x276 */ Vec3s morphTable[16];
    /* 0x2D6 */ Vec3s unk2D6;
    /* 0x2DC */ Vec3s unk2DC;
    /* 0x2E2 */ Vec3s unk2E2;
    /* 0x2E8 */ UNK_TYPE1 unk_2E8[0x12];
    /* 0x2FA */ s16 unk2FA[16];
    /* 0x31A */ s16 unk31A[16];
    /* 0x33A */ UNK_TYPE1 unk_33A[0xB6];
    /* 0x3F0 */ s16 unk3F0;
    /* 0x3F2 */ s16 unk3F2;
    /* 0x3F4 */ s16 unk3F4;
    /* 0x3F6 */ s16 unk3F6;
    /* 0x3F8 */ Vec3f unk3F8;
    /* 0x404 */ Path* unk404;
    /* 0x408 */ Vec3f unk408;
    /* 0x414 */ f32 unk414;
    /* 0x418 */ s32 unk418;
    /* 0x41C */ s32 unk41C;
    /* 0x420 */ s32 unk420;
    /* 0x424 */ s32 unk424;
    /* 0x428 */ u8 unk428;
    /* 0x429 */ UNK_TYPE1 unk_429[0x1];
    /* 0x42A */ s16 unk42A;
    /* 0x42C */ s32 unk42C;
    /* 0x430 */ s32 unk430;
    /* 0x434 */ s16 unk434;
    /* 0x436 */ s16 unk436;
    /* 0x438 */ Vec3f unk438;
    /* 0x444 */ Vec3f unk444;
    /* 0x450 */ s32 animationIndex;
    /* 0x454 */ UNK_TYPE1 unk_454[0x2];
    /* 0x456 */ s16 cutscenes[2];
    /* 0x45A */ s16 cutsceneIdx;
} EnSuttari; // size = 0x45C

extern const ActorInit En_Suttari_InitVars;

#endif // Z_EN_SUTTARI_H
