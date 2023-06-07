#ifndef Z_EN_MNK_H
#define Z_EN_MNK_H

#include "global.h"
#include "z64snap.h"

struct EnMnk;

typedef void (*EnMnkActionFunc)(struct EnMnk*, PlayState*);
typedef void (*EnMnkFunc)(PlayState*, struct EnMnk*);

#define GET_MONKEY_TYPE(this) ((((Actor*)(this))->params & 0x780) >> 7)
#define GET_MONKEY_7F(this) (((Actor*)(this))->params & 0x7F)
#define GET_MONKEY_F800(this) ((((Actor*)(this))->params & 0xF800) >> 11)

typedef enum {
    /*  0 */ MONKEY_0,
    /*  1 */ MONKEY_OUTSIDEWOODS,
    /*  2 */ MONKEY_BY_WITCH,
    /*  3 */ MONKEY_OUTSIDECHAMBER,
    /*  4 */ MONKEY_OUTSIDEPALACE,
    /*  5 */ MONKEY_TIED_UP,
    /*  6 */ MONKEY_HANGING,
    /*  7 */ MONKEY_WOODS_GUIDE,
    /*  8 */ MONKEY_8,
    /*  9 */ MONKEY_AFTER_SAVED,
    /* 10 */ MONKEY_10
} MonkeyType;

typedef enum {
    /* 0 */ TIEDUPMONKEY_ANIM_KICKAROUND,
    /* 1 */ TIEDUPMONKEY_ANIM_KICKUPANDDOWN,
    /* 2 */ TIEDUPMONKEY_ANIM_SHH,
    /* 3 */ TIEDUPMONKEY_ANIM_SING,
    /* 4 */ TIEDUPMONKEY_ANIM_SMALLCLAPFEET,
    /* 5 */ TIEDUPMONKEY_ANIM_LARGECLAPFEET,
    /* 6 */ TIEDUPMONKEY_ANIM_SHAKEHEAD,
    /* 7 */ TIEDUPMONKEY_ANIM_WAIT,
    /* 8 */ TIEDUPMONKEY_ANIM_CONFUSED,
} TiedUpMonkeyAnim;

typedef enum {
    /* 0 */ HANGINGMONKEY_ANIM_FREEZE,
    /* 1 */ HANGINGMONKEY_ANIM_RISE,
    /* 2 */ HANGINGMONKEY_ANIM_STRUGGLE
} HangingMonkeyAnim;

typedef enum {
    /* 0 */ FOLLOWPATH_RESULT_FOLLOWING,
    /* 1 */ FOLLOWPATH_RESULT_SHORTRANGE_REACHEDPOINT,
    /* 2 */ FOLLOWPATH_RESULT_SHORTRANGE_FINISHEDPATH,
    /* 3 */ FOLLOWPATH_RESULT_LONGRANGE_REACHEDPOINT,
    /* 4 */ FOLLOWPATH_RESULT_LONGRANGE_FINISHEDPATH
} FollowPathResult;

#define FOLLOWPATH_FLAGS_REACHNEXTPOINT (1 << 0)
#define FOLLOWPATH_FLAGS_LONGRANGE (1 << 1)

typedef struct EnMnk {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ Vec3s jointTable[23];
    /* 0x216 */ Vec3s morphTable[23];
    /* 0x2A0 */ SkelAnime propSkelAnime;
    /* 0x2E4 */ Vec3s propJointTable[5];
    /* 0x302 */ Vec3s propMorphTable[5];
    /* 0x320 */ ColliderCylinder collider;
    /* 0x36C */ MtxF unk_36C;
    /* 0x3AC */ Path* path;
    /* 0x3B0 */ s16 cutsceneIndices[6];
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3BE */ s16 curAnim;
    /* 0x3C0 */ s32 destPointIndex;
    /* 0x3C4 */ s32 nextPathIndex;
    /* 0x3C8 */ s32 unk_3C8;
    /* 0x3CC */ s16 unk_3CC; //beard x rot?
    /* 0x3CE */ s16 unk_3CE; //beard y rot?
    /* 0x3D0 */ s16 unk_3D0;
    /* 0x3D2 */ char unk_3D2[0x2];
    /* 0x3D4 */ u32 unk_3D4;
    /* 0x3D8 */ f32 approachPlayerRadius;
    /* 0x3DC */ s16 blinkFrame;
    /* 0x3DE */ s16 blinkTimer;
    /* 0x3E0 */ s32 unk_3E0;
    /* 0x3E4 */ u16 unk_3E4;
    /* 0x3E8 */ EnMnkActionFunc actionFunc;
} EnMnk; // size = 0x3EC

#endif // Z_EN_MNK_H
