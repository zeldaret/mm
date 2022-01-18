#ifndef Z_EN_BOX_H
#define Z_EN_BOX_H

#include "global.h"

struct EnBox;
struct func_80867BDC_a0;

typedef void (*EnBoxActionFunc)(struct EnBox*, GlobalContext*);
typedef void (*EnBoxUnkFunc)(struct func_80867BDC_a0* arg0, GlobalContext* globalCtx);

typedef struct func_80867BDC_a0 {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ EnBoxUnkFunc unk_0C;
    /* 0x10 */ EnBoxUnkFunc unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} func_80867BDC_a0; //size 0x24

typedef enum {
    /*  0 */ ENBOX_TYPE_BIG,                    // big
    /*  1 */ ENBOX_TYPE_BIG_ROOM_CLEAR,         // appear on room clear, store temp clear as permanent clear
    /*  2 */ ENBOX_TYPE_BIG_ORNATE,             // boss key chest
    /*  3 */ ENBOX_TYPE_BIG_SWITCH_FLAG_FALL,   // falling, appear on switch flag set
    /*  4 */ ENBOX_TYPE_BIG_INVISIBLE,          // big, revealed with lens of truth or when opened
    /*  5 */ ENBOX_TYPE_SMALL,                  // small
    /*  6 */ ENBOX_TYPE_SMALL_INVISIBLE,        // small, revealed with lens of truth or when opened
    /*  7 */ ENBOX_TYPE_SMALL_ROOM_CLEAR,       // use room clear, store temp clear as perm clear
    /*  8 */ ENBOX_TYPE_SMALL_SWITCH_FLAG_FALL, // falling, appear on switch flag set
    /*  9 */ ENBOX_TYPE_BIG_SONG_ZELDAS_LULLABY,// NOT IMPLEMENTED, behaves like big chest
    /* 10 */ ENBOX_TYPE_BIG_SONG_SUNS,          // NOT IMPLEMENTED, behaves like big chest
    /* 11 */ ENBOX_TYPE_BIG_SWITCH_FLAG,        // big, appear on switch flag set
    /* 12 */ ENBOX_TYPE_SMALL_SWITCH_FLAG       // small, appear on switch flag set
} EnBoxType;

typedef struct EnBox {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ SkelAnime skelAnime;
    /* 0x01A0 */ s32 unk_1A0;
    /* 0x01A4 */ char unk_1A4[0x04];
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ EnBoxActionFunc actionFunc;
    /* 0x01B0 */ Vec3s jointTable[5];
    /* 0x01CE */ Vec3s morphTable[5];
    /* 0x01EC */ s16 unk_1EC;
    /* 0x01EE */ u8 movementFlags;
    /* 0x01EF */ u8 alpha;
    /* 0x01F0 */ u8 switchFlag;
    /* 0x01F1 */ u8 type;
    /* 0x01F2 */ u8 iceSmokeTimer;
    /* 0x01F3 */ s8 unk_1F3;
    /* 0x01F4 */ func_80867BDC_a0 unk_1F4;
    /* 0x0218 */ s16 cutsceneIdxA;
    /* 0x021A */ s16 cutsceneIdxB;
    /* 0x021C */ s32 getItem;
    /* 0x0220 */ s32 collectableFlag;
} EnBox; // size = 0x224

extern const ActorInit En_Box_InitVars;

#define ENBOX_GET_TYPE(thisx) (((thisx)->params >> 12) & 0xF)
#define ENBOX_GET_ITEM(thisx) (((thisx)->params >> 5) & 0x7F)
#define ENBOX_GET_CHEST_FLAG(thisx) ((thisx)->params & 0x1F)
#define ENBOX_GET_SWITCH_FLAG(thisx) ((thisx)->world.rot.z)

#endif // Z_EN_BOX_H
