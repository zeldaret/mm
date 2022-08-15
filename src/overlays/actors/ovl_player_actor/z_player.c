/*
 * File: z_player.c
 * Overlay: ovl_player_actor
 * Description: Player
 */

#include "global.h"
#include "z64rumble.h"

#include "overlays/actors/ovl_Arms_Hook/z_arms_hook.h"
#include "overlays/actors/ovl_Door_Spiral/z_door_spiral.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Boom/z_en_boom.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"
#include "overlays/actors/ovl_En_Ishi/z_en_ishi.h"
#include "overlays/actors/ovl_En_Test3/z_en_test3.h"
#include "overlays/actors/ovl_En_Test7/z_en_test7.h"
#include "overlays/actors/ovl_En_Torch2/z_en_torch2.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#include "objects/object_link_boy/object_link_boy.h"
#include "objects/object_link_goron/object_link_goron.h"
#include "objects/object_link_zora/object_link_zora.h"
#include "objects/object_link_nuts/object_link_nuts.h"
#include "objects/object_link_child/object_link_child.h"

#define THIS ((Player*)thisx)

void Player_Init(Actor* thisx, PlayState* play);
void Player_Destroy(Actor* thisx, PlayState* play);
void Player_Update(Actor* thisx, PlayState* play);
void Player_Draw(Actor* thisx, PlayState* play);

s32 Player_GrabPlayer(PlayState* play, Player* player);
s32 func_8085B28C(PlayState* play, Player* player, s32 mode);
void func_8085B384(Player* player, PlayState* play);
s32 Player_InflictDamage(PlayState* play, s32 damage);
void func_8085B460(PlayState* play, Actor* actor);
void func_8085B74C(PlayState* play);
void func_8085B820(PlayState* play, s16 arg1);
PlayerActionParam func_8085B854(PlayState* play, Player* player, ItemID itemId);
s32 func_8085B930(PlayState* play, LinkAnimationHeader* talkAnim, s32 animMode);

void Player_UpdateCommon(Player* player, PlayState* play, Input* input);
s32 Player_StartFishing(PlayState* play);
void func_8085B170(PlayState* play, Player* this);
s32 func_8083A658(PlayState* play, Player* this);
void func_8082F8BC(PlayState* play, Player* this, PlayerActionParam actionParam);

void func_80831990(PlayState* play, Player* this, ItemID item);

s32 func_80848BF4(Player* this, PlayState* play);

void func_80836988(Player* this, PlayState* play);

void func_808484F0(Player* this);

void func_80838A20(PlayState* play, Player* this);
void func_80839978(PlayState* play, Player* this);
void func_80839A10(PlayState* play, Player* this);

typedef enum AnimSfxType {
    /*  1 */ ANIMSFX_TYPE_1 = 1,
    /*  2 */ ANIMSFX_TYPE_2,
    /*  3 */ ANIMSFX_TYPE_3,
    /*  4 */ ANIMSFX_TYPE_VOICE,
    /*  5 */ ANIMSFX_TYPE_5, // does not use sfxId
    /*  6 */ ANIMSFX_TYPE_6, // does not use sfxId
    /*  7 */ ANIMSFX_TYPE_7, // does not use sfxId
    /*  8 */ ANIMSFX_TYPE_8, // does not use sfxId
    /*  9 */ ANIMSFX_TYPE_9, // does not use sfxId
    /* 10 */ ANIMSFX_TYPE_10,
} AnimSfxType;

#define ANIMSFX_SHIFT_TYPE(type) ((type) << 11)

#define ANIMSFX_CONTINUE (1)
#define ANIMSFX_STOP (0)

#define ANIMSFX_FLAGS(type, frame, cont) \
    (((ANIMSFX_##cont) == ANIMSFX_STOP ? -1 : 1) * (ANIMSFX_SHIFT_TYPE(type) | ((frame)&0x7FF)))

#define ANIMSFX(type, frame, sfxId, cont) \
    { (sfxId), ANIMSFX_FLAGS(type, frame, cont) }

#define ANIMSFX_GET_TYPE(data) ((data)&0x7800)
#define ANIMSFX_GET_FRAME(data) ((data)&0x7FF)

typedef struct AnimSfxEntry {
    /* 0x0 */ u16 sfxId;
    /* 0x2 */ s16 flags; // negative marks the end
} AnimSfxEntry;          // size = 0x4

/* action funcs */
void func_808496AC(Player* this, PlayState* play);
void func_808497A0(Player* this, PlayState* play);
void func_80849A9C(Player* this, PlayState* play);
void func_80849DD0(Player* this, PlayState* play);
void func_80849FE0(Player* this, PlayState* play);
void func_8084A26C(Player* this, PlayState* play);
void func_8084A5C0(Player* this, PlayState* play);
void func_8084A794(Player* this, PlayState* play);
void func_8084A884(Player* this, PlayState* play);
void func_8084A8E8(Player* this, PlayState* play);
void func_8084AB4C(Player* this, PlayState* play);
void func_8084AC84(Player* this, PlayState* play);
void func_8084AEEC(Player* this, PlayState* play);
void func_8084AF9C(Player* this, PlayState* play);
void func_8084B0EC(Player* this, PlayState* play);
void func_8084B288(Player* this, PlayState* play);
void func_8084B3B8(Player* this, PlayState* play);
void func_8084B4A8(Player* this, PlayState* play);
void func_8084B5C0(Player* this, PlayState* play);
void func_8084BAA4(Player* this, PlayState* play);
void func_8084BBF0(Player* this, PlayState* play);
void func_8084BC64(Player* this, PlayState* play);
void func_8084BE40(Player* this, PlayState* play);
void func_8084BF28(Player* this, PlayState* play);
void func_8084BFDC(Player* this, PlayState* play);
void func_8084C16C(Player* this, PlayState* play);
void func_8084C6EC(Player* this, PlayState* play);
void func_8084C94C(Player* this, PlayState* play);
void func_8084CA24(Player* this, PlayState* play);
void func_8084CB58(Player* this, PlayState* play);
void func_8084CCEC(Player* this, PlayState* play);
void func_8084CE84(Player* this, PlayState* play);
void func_8084D18C(Player* this, PlayState* play);
void func_8084D4EC(Player* this, PlayState* play);
void func_8084D770(Player* this, PlayState* play);
void func_8084D820(Player* this, PlayState* play);
void func_8084E034(Player* this, PlayState* play);
void func_8084E25C(Player* this, PlayState* play);
void func_8084E334(Player* this, PlayState* play);
void func_8084E434(Player* this, PlayState* play);
void func_8084E4E4(Player* this, PlayState* play);
void func_8084E58C(Player* this, PlayState* play);
void func_8084E65C(Player* this, PlayState* play);
void func_8084E724(Player* this, PlayState* play);
void func_8084E980(Player* this, PlayState* play);
void func_8084ED9C(Player* this, PlayState* play);
void func_8084EE50(Player* this, PlayState* play);
void func_8084EF9C(Player* this, PlayState* play);
void func_8084F1B8(Player* this, PlayState* play);
void func_8084F3DC(Player* this, PlayState* play);
void func_8084F4E8(Player* this, PlayState* play);
void func_8084FC0C(Player* this, PlayState* play);
void func_8084FE7C(Player* this, PlayState* play);
void func_808505D0(Player* this, PlayState* play);
void func_808508C8(Player* this, PlayState* play);
void func_80850B18(Player* this, PlayState* play);
void func_80850D68(Player* this, PlayState* play);
void func_808513EC(Player* this, PlayState* play);
void func_80851588(Player* this, PlayState* play);
void func_808516B4(Player* this, PlayState* play);
void func_808519FC(Player* this, PlayState* play);
void func_80851B58(Player* this, PlayState* play);
void func_80851BD4(Player* this, PlayState* play);
void func_8085269C(Player* this, PlayState* play);
void func_80852B28(Player* this, PlayState* play);
void func_80852C04(Player* this, PlayState* play);
void func_80852FD4(Player* this, PlayState* play);
void func_80853194(Player* this, PlayState* play);
void func_808534C0(Player* this, PlayState* play);
void func_80853754(Player* this, PlayState* play);
void func_80853850(Player* this, PlayState* play);
void func_80853A5C(Player* this, PlayState* play);
void func_80853CC0(Player* this, PlayState* play);
void func_80853D68(Player* this, PlayState* play);
void func_80854010(Player* this, PlayState* play);
void func_808540A0(Player* this, PlayState* play);
void func_80854118(Player* this, PlayState* play);
void func_8085421C(Player* this, PlayState* play);
void func_8085437C(Player* this, PlayState* play);
void func_8085439C(Player* this, PlayState* play);
void func_80854430(Player* this, PlayState* play);
void func_80854614(Player* this, PlayState* play);
void func_808546D0(Player* this, PlayState* play);
void func_80854800(Player* this, PlayState* play);
void func_808548B8(Player* this, PlayState* play);
void func_80854C70(Player* this, PlayState* play);
void func_808553F4(Player* this, PlayState* play);
void func_80855818(Player* this, PlayState* play);
void func_80855A7C(Player* this, PlayState* play);
void func_80855AF4(Player* this, PlayState* play);
void func_80855B9C(Player* this, PlayState* play);
void func_80855C28(Player* this, PlayState* play);
void func_80855E08(Player* this, PlayState* play);
void func_808561B0(Player* this, PlayState* play);
void func_80856918(Player* this, PlayState* play);
void func_808573A4(Player* this, PlayState* play);
void func_80857BE8(Player* this, PlayState* play);
void func_8085B08C(Player* this, PlayState* play);

s32 func_80839518(Player* this, PlayState* play);
s32 func_808365DC(Player* this, PlayState* play);
s32 func_8083D23C(Player* this, PlayState* play);
s32 func_8083CCB4(Player* this, PlayState* play);
s32 func_808391D8(Player* this, PlayState* play);
s32 func_8083DFC4(Player* this, PlayState* play);
s32 func_8083A114(Player* this, PlayState* play);
s32 func_80848570(Player* this, PlayState* play);
s32 func_8083A580(Player* this, PlayState* play);
s32 func_8083D78C(Player* this, PlayState* play);
s32 func_80839B18(Player* this, PlayState* play);
s32 func_8083A274(Player* this, PlayState* play);
s32 func_80834DFC(Player* this, PlayState* play);
s32 func_80838A90(Player* this, PlayState* play);
s32 func_8083A0CC(Player* this, PlayState* play);

s32 func_80848780(Player* this, PlayState* play);
s32 func_808487B8(Player* this, PlayState* play);
s32 func_80848B6C(Player* this, PlayState* play);
s32 func_808490B4(Player* this, PlayState* play);
s32 func_808491B4(Player* this, PlayState* play);
s32 func_80848808(Player* this, PlayState* play);
s32 func_8084894C(Player* this, PlayState* play);
s32 func_80848A0C(Player* this, PlayState* play);
s32 func_80848AB0(Player* this, PlayState* play);
s32 func_80848E4C(Player* this, PlayState* play);
s32 func_80849054(Player* this, PlayState* play);
s32 func_8084923C(Player* this, PlayState* play);
s32 func_808492C4(Player* this, PlayState* play);
s32 func_8084933C(Player* this, PlayState* play);
s32 func_80849570(Player* this, PlayState* play);
s32 func_80849620(Player* this, PlayState* play);

/* Init Mode functions */
void Player_InitMode_0(PlayState* play, Player* this);
void Player_InitMode_1(PlayState* play, Player* this);
void Player_InitMode_2(PlayState* play, Player* this);
void Player_InitMode_3(PlayState* play, Player* this);
void Player_InitMode_4(PlayState* play, Player* this);
void Player_InitMode_5(PlayState* play, Player* this);
void Player_InitMode_6(PlayState* play, Player* this);
void Player_InitMode_7(PlayState* play, Player* this);
void func_80841744(PlayState* play, Player* this);
void func_80841744(PlayState* play, Player* this);
void func_8083ADF0(PlayState* play, Player* this);
void Player_InitMode_B(PlayState* play, Player* this);
void Player_InitMode_Telescope(PlayState* play, Player* this);
void Player_InitMode_D(PlayState* play, Player* this);
void func_8083ADF0(PlayState* play, Player* this);
void Player_InitMode_F(PlayState* play, Player* this);

void func_80859F4C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859FCC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859FF4(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A120(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A144(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A19C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A1D4(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A24C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A2AC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A330(PlayState* play, Player* this, UNK_TYPE arg2);

void func_80859EBC(PlayState* play, Player* this, s32 arg2);

void func_80859414(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859AD0(PlayState* play, Player* this, void* arg2);
void func_80859B28(PlayState* play, Player* this, void* arg2);
void func_8085ADA0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085AACC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_808595B8(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859890(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859C60(PlayState* play, Player* this, void* arg2);
void func_8085A710(PlayState* play, Player* this, void* arg2);
void func_808595B8(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859D70(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A6C0(PlayState* play, Player* this, void* arg2);
void func_80859FF4(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A04C(PlayState* play, Player* this, void* arg);
void func_8085A144(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A1D4(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A364(PlayState* play, Player* this, void* arg2);
void func_808599DC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A40C(PlayState* play, Player* this, void* arg2);
void func_80859708(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A2AC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A940(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A4A4(PlayState* play, Player* this, void* arg2);
void func_8085A5DC(PlayState* play, Player* this, void* arg2);
void func_8085AA84(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A7C0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085AA10(PlayState* play, Player* this, UNK_TYPE arg2);
void func_808599DC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859AF8(PlayState* play, Player* this, void* arg2);
void func_80859A44(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859D44(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859EBC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859F4C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859F4C(PlayState* play, Player* this, UNK_TYPE arg2);

void func_8085A768(PlayState* play, Player* this, void* arg2);
void func_8085AA60(PlayState* play, Player* this, UNK_TYPE arg2);

void func_808594D0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_808594D0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085978C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859B54(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859CA0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_808594D0(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859CFC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A66C(PlayState* play, Player* this, void* arg2);
void func_80859FCC(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A120(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A19C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085968C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A24C(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A330(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A8C4(PlayState* play, Player* this, UNK_TYPE arg2);
void func_8085A530(PlayState* play, Player* this, void* arg2);
void func_8085A768(PlayState* play, Player* this, void* arg2);
void func_8085AA60(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859990(PlayState* play, Player* this, UNK_TYPE arg2);
void func_80859A10(PlayState* play, Player* this, UNK_TYPE arg2);

// ActionParams
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F5A4(PlayState* play, Player* this);
void func_8082F8A0(PlayState* play, Player* this);
void func_8082F5C0(PlayState* play, Player* this);
void func_8082F5C0(PlayState* play, Player* this);
void func_8082F5C0(PlayState* play, Player* this);
void func_8082F5C0(PlayState* play, Player* this);
void func_8082F7F4(PlayState* play, Player* this);
void func_8082F62C(PlayState* play, Player* this);
void func_8082F62C(PlayState* play, Player* this);
void func_8082F62C(PlayState* play, Player* this);
void func_8082F8A0(PlayState* play, Player* this);
void func_8082F5C0(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);
void func_8082F594(PlayState* play, Player* this);

void func_80858DB4(PlayState* play, Player* this, void* anim);
void func_80858DDC(PlayState* play, Player* this, void* anim);
void func_80858E40(PlayState* play, Player* this, void* anim);
void func_80858E60(PlayState* play, Player* this, void* anim);
void func_80858E80(PlayState* play, Player* this, void* anim);
void func_80858EA0(PlayState* play, Player* this, void* anim);
void func_80858EFC(PlayState* play, Player* this, void* anim);
void func_80858F1C(PlayState* play, Player* this, void* anim);
void func_80858F3C(PlayState* play, Player* this, void* anim);
void func_80858F5C(PlayState* play, Player* this, void* anim);
void func_80858FBC(PlayState* play, Player* this, void* anim);
void func_80859028(PlayState* play, Player* this, void* anim);
void func_808591BC(PlayState* play, Player* this, void* anim);
void func_80858DFC(PlayState* play, Player* this, void* anim);
void func_80858EC0(PlayState* play, Player* this, void* anim);
void func_80858F7C(PlayState* play, Player* this, void* anim);
void func_80858F9C(PlayState* play, Player* this, void* anim);
void func_80859168(PlayState* play, Player* this, void* anim);
void func_80859210(PlayState* play, Player* this, void* arg2);

typedef struct struct_8085C2A4 {
    /* 0x0 */ LinkAnimationHeader* unk_0;
    /* 0x4 */ LinkAnimationHeader* unk_4;
    /* 0x8 */ LinkAnimationHeader* unk_8;
} struct_8085C2A4; // size = 0xC

typedef struct BlureColors {
    u8 p1StartColor[4];
    u8 p2StartColor[4];
    u8 p1EndColor[4];
    u8 p2EndColor[4];
} BlureColors;

typedef void (*PlayerCueInterpretor)(PlayState*, Player*, CsCmdActorAction*);

typedef struct struct_8085DA94 {
    /* 0x0 */ s8 type;
    /* 0x4 */ union {
        void* ptr; // Do not use, required in the absence of designated initialisors
        LinkAnimationHeader* anim;
        PlayerCueInterpretor func;
    };
} struct_8085DA94; // size = 0x8

typedef struct struct_8085E368 {
    /* 0x0 */ Vec3s base;
    /* 0x6 */ Vec3s range;
} struct_8085E368; // size = 0xC

typedef struct struct_8085D910 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
    /* 0x3 */ u8 unk_3;
} struct_8085D910; // size = 0x4

typedef struct struct_8085D848_unk_00 {
    /* 0x00 */ s16 unk_00; /* inferred */
    /* 0x02 */ u8 unk_02;  /* inferred */
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
} struct_8085D848_unk_00; // size = 0x08

typedef struct struct_8085D848_unk_18 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x10 */ s16 unk_10;
} struct_8085D848_unk_18; // size = 0x14

typedef struct struct_8085D848 {
    /* 0x00 */ struct_8085D848_unk_00 unk_00[3];
    /* 0x18 */ struct_8085D848_unk_18 unk_18[3];
} struct_8085D848; // size = 0x54

typedef struct struct_8085D80C {
    /* 0x0 */ s16 actorId;
    /* 0x2 */ s16 params;
} struct_8085D80C; // size = 0x4

typedef struct struct_8085D798 {
    /* 0x0 */ s16 actorId;
    /* 0x2 */ s8 actorParams;
    /* 0x3 */ u8 itemId;
    /* 0x4 */ u8 actionParam;
    /* 0x5 */ u8 textId;
} struct_8085D798; // size = 0x6

typedef struct struct_8085D714 {
    /* 0x0 */ u8 unk_0;
    /* 0x4 */ LinkAnimationHeader* unk_4;
} struct_8085D714; // size = 0x8

typedef struct struct_8085D224 {
    /* 0x0 */ LinkAnimationHeader* anim;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_8085D224; // size = 0xC

typedef struct struct_8085D13C {
    /* 0x0 */ s8 damage;
    /* 0x1 */ u8 sourceIntensity;
    /* 0x2 */ u8 decayTimer;
    /* 0x3 */ u8 decayStep;
    /* 0x4 */ u16 sfxId;
} struct_8085D13C; // size = 0x6

typedef struct struct_8085CD30 {
    /* 0x00 */ LinkAnimationHeader* unk_0;
    /* 0x04 */ LinkAnimationHeader* unk_4;
    /* 0x08 */ LinkAnimationHeader* unk_8;
    /* 0x0C */ u8 unk_C;
    /* 0x0D */ u8 unk_D;
} struct_8085CD30; // size = 0x10

typedef struct struct_8085D09C {
    /* 0x0 */ s32 dmgFlags;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 unk_5;
    /* 0x6 */ u8 unk_6;
    /* 0x7 */ u8 unk_7;
} struct_8085D09C; // size = 0x8

typedef struct struct_8085CC88 {
    /* 0x0 */ LinkAnimationHeader* anim;
    /* 0x4 */ u8 frame;
} struct_8085CC88; // size = 0x8

typedef struct {
    /* 0x0 */ u8 itemId;
    /* 0x2 */ s16 actorId;
} struct_8085CD24; // size = 0x4

typedef struct {
    /* 0x0 */ Color_RGB8 unk_0;
    /* 0x3 */ Color_RGB8 unk_3;
    /* 0x6 */ Color_RGB8 unk_6;
    /* 0xA */ s16 unk_A;
    /* 0xC */ s16 unk_C;
} struct_8082F02C_arg1; // size = 0xE

#if 0
// OoT:
typedef struct GetItemEntry {
    /* 0x00 */ u8 itemId;
    /* 0x01 */ u8 field; // various bit-packed data
    /* 0x02 */ s8 gi;    // defines the draw id and chest opening animation
    /* 0x03 */ u8 textId;
    /* 0x04 */ u16 objectId;
} GetItemEntry; // size = 0x06
#endif

typedef struct GetItemEntry {
    /* 0x0 */ u8 itemId;
    /* 0x1 */ u8 field;
    /* 0x2 */ s8 unk_2;
    /* 0x3 */ u8 textId;
    /* 0x4 */ u16 objectId;
} GetItemEntry; // size = 0x6

typedef struct struct_8085D200 {
    /* 0x0 */ LinkAnimationHeader* unk_0;
    /* 0x4 */ LinkAnimationHeader* unk_4;
    /* 0x8 */ u8 unk_8;
    /* 0x9 */ u8 unk_9;
} struct_8085D200; // size = 0xC

// bss
#if 1
Vec3f D_80862AF0;
f32 D_80862AFC;
s16 D_80862B00;
s16 D_80862B02;
s32 D_80862B04;
s32 D_80862B08;
s32 D_80862B0C;
u32 D_80862B10;
s16 D_80862B14;
s16 D_80862B16;
f32 D_80862B18;
s32 D_80862B1C;
s32 D_80862B20;
s32 D_80862B24;
s16 D_80862B28;
s32 D_80862B2C;
Vec3f D_80862B30;
f32 D_80862B3C;
u32 D_80862B40;
Input* D_80862B44;
s32 D_80862B48;
s32 D_80862B4C;
EnvLightSettings D_80862B50;
s32 D_80862B6C;
#else
extern Vec3f D_80862AF0;
extern f32 D_80862AFC;
extern s16 D_80862B00;
extern s16 D_80862B02;
extern s32 D_80862B04;
extern s32 D_80862B08;
extern s32 D_80862B0C;
extern u32 D_80862B10;
extern s16 D_80862B14;
extern s16 D_80862B16;
extern f32 D_80862B18;
extern s32 D_80862B1C;
extern s32 D_80862B20;
extern s32 D_80862B24;
extern s16 D_80862B28;
extern s32 D_80862B2C;
extern Vec3f D_80862B30;
extern f32 D_80862B3C;
extern u32 D_80862B40;
extern Input* D_80862B44;
extern s32 D_80862B48;
extern s32 D_80862B4C;
extern EnvLightSettings D_80862B50;
extern s32 D_80862B6C;
#endif

s32 func_8082DA90(PlayState* play) {
    return (play->transitionTrigger != TRANS_TRIGGER_OFF) || (play->transitionMode != TRANS_MODE_OFF);
}

void func_8082DABC(Player* this) {
    this->linearVelocity = 0.0f;
    this->actor.speedXZ = 0.0f;
}

void func_8082DAD4(Player* this) {
    func_8082DABC(this);
    this->unk_AA5 = 0;
}

s32 func_8082DAFC(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return CHECK_FLAG_ALL(player->actor.flags, ACTOR_FLAG_100);
}

void Player_AnimationPlayOnce(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayOnce(play, &this->skelAnime, anim);
}

void Player_AnimationPlayLoop(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayLoop(play, &this->skelAnime, anim);
}

void func_8082DB60(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayLoopSetSpeed(play, &this->skelAnime, anim, 2.0f / 3.0f);
}

void func_8082DB90(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 2.0f / 3.0f);
}

void Player_AnimationPlayOnceReverse(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, -2.0f / 3.0f, Animation_GetLastFrame(anim), 0.0f, ANIMMODE_ONCE,
                         0.0f);
}

void func_8082DC28(Player* this) {
    this->skelAnime.jointTable[1].y = 0;
}

void func_8082DC38(Player* this) {
    this->stateFlags2 &= ~PLAYER_STATE2_20000;
    this->meleeWeaponState = PLAYER_MWA_FORWARD_SLASH_1H;
    this->meleeWeaponInfo[2].active = false;
    this->meleeWeaponInfo[1].active = false;
    this->meleeWeaponInfo[0].active = false;
}

void func_8082DC64(PlayState* play, Player* this) {
    if ((this->subCamId != CAM_ID_NONE) && (play->cameraPtrs[this->subCamId] != NULL)) {
        this->subCamId = CAM_ID_NONE;
    }

    this->stateFlags2 &= ~(PLAYER_STATE2_400 | PLAYER_STATE2_800);
}

void func_8082DCA0(PlayState* play, Player* this) {
    Actor* heldActor = this->heldActor;

    if (heldActor != NULL) {
        if (!Player_IsHoldingHookshot(this)) {
            this->actor.child = NULL;
            this->heldActor = NULL;
            this->interactRangeActor = NULL;
            heldActor->parent = NULL;
            this->stateFlags1 &= ~PLAYER_STATE1_800;
        }
    }

    if (Player_GetExplosiveHeld(this) >= 0) {
        func_8082F8BC(play, this, PLAYER_AP_NONE);
        this->heldItemId = ITEM_FE;
    }
}

void func_8082DD2C(PlayState* play, Player* this) {
    if ((this->stateFlags1 & PLAYER_STATE1_800) && (this->heldActor == NULL)) {
        if (this->interactRangeActor != NULL) {
            if (this->getItemId == GI_NONE) {
                this->stateFlags1 &= ~PLAYER_STATE1_800;
                this->interactRangeActor = NULL;
            }
        } else {
            this->stateFlags1 &= ~PLAYER_STATE1_800;
        }
    }

    func_8082DC38(this);
    this->unk_AA5 = 0;
    func_8082DC64(play, this);
    func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
    this->stateFlags1 &=
        ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000 | PLAYER_STATE1_200000);
    this->stateFlags2 &= ~(PLAYER_STATE2_10 | PLAYER_STATE2_80);
    this->unk_ADD = 0;
    this->unk_ADC = 0;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->unk_ABC = 0.0f;
    this->unk_AC0 = 0.0f;
}

s32 func_8082DE14(PlayState* play, Player* this) {
    if (this->itemActionParam > PLAYER_AP_LAST_USED) {
        func_80831990(play, this, ITEM_NONE);
        return true;
    }
    return false;
}

void func_8082DE50(PlayState* play, Player* this) {
    func_8082DD2C(play, this);
    func_8082DCA0(play, this);
}

s32 func_8082DE88(Player* this, s32 arg1, s32 arg2) {
    s16 temp_v0 = this->unk_D64 - D_80862B00;

    this->unk_AE8 += arg1 + (s16)(ABS_ALT(temp_v0) * fabsf(D_80862AFC) * (1.0f / 0x600F0));
    if (CHECK_BTN_ANY(D_80862B44->press.button, BTN_B | BTN_A)) {
        this->unk_AE8 += 5;
    }

    return this->unk_AE8 >= arg2;
}

void func_8082DF2C(PlayState* play) {
    if (play->actorCtx.freezeFlashTimer == 0) {
        play->actorCtx.freezeFlashTimer = 1;
    }
}

u8 D_8085B9F0[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    true,  // PLAYER_LIMB_UPPER_ROOT
    true,  // PLAYER_LIMB_HEAD
    true,  // PLAYER_LIMB_HAT
    true,  // PLAYER_LIMB_COLLAR
    true,  // PLAYER_LIMB_L_SHOULDER
    true,  // PLAYER_LIMB_L_FOREARM
    true,  // PLAYER_LIMB_L_HAND
    true,  // PLAYER_LIMB_R_SHOULDER
    true,  // PLAYER_LIMB_R_FOREARM
    true,  // PLAYER_LIMB_R_HAND
    true,  // PLAYER_LIMB_SHEATH
    true,  // PLAYER_LIMB_TORSO
};
u8 D_8085BA08[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    false, // PLAYER_LIMB_UPPER_ROOT
    false, // PLAYER_LIMB_HEAD
    false, // PLAYER_LIMB_HAT
    false, // PLAYER_LIMB_COLLAR
    true,  // PLAYER_LIMB_L_SHOULDER
    true,  // PLAYER_LIMB_L_FOREARM
    true,  // PLAYER_LIMB_L_HAND
    false, // PLAYER_LIMB_R_SHOULDER
    false, // PLAYER_LIMB_R_FOREARM
    false, // PLAYER_LIMB_R_HAND
    false, // PLAYER_LIMB_SHEATH
    false, // PLAYER_LIMB_TORSO
};
u8 D_8085BA20[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    false, // PLAYER_LIMB_UPPER_ROOT
    false, // PLAYER_LIMB_HEAD
    false, // PLAYER_LIMB_HAT
    false, // PLAYER_LIMB_COLLAR
    false, // PLAYER_LIMB_L_SHOULDER
    false, // PLAYER_LIMB_L_FOREARM
    false, // PLAYER_LIMB_L_HAND
    true,  // PLAYER_LIMB_R_SHOULDER
    true,  // PLAYER_LIMB_R_FOREARM
    true,  // PLAYER_LIMB_R_HAND
    false, // PLAYER_LIMB_SHEATH
    false, // PLAYER_LIMB_TORSO
};

void Player_RequestRumble(PlayState* play, Player* this, s32 sourceIntensity, s32 decayTimer, s32 decayStep,
                          s32 distSq) {
    if (this == GET_PLAYER(play)) {
        Rumble_Request(distSq, sourceIntensity, decayTimer, decayStep);
    }
}

// TODO: less dumb name
#define SFX_VOICE_BANK_SIZE 0x20

void func_8082DF8C(Player* this, u16 sfxId) {
    u16 sfxOffset;

    if (this->currentMask == PLAYER_MASK_GIANT) {
        func_8019F830(&this->actor.projectedPos, sfxId);
    } else if (this->actor.id == ACTOR_PLAYER) {
        if (this->currentMask == PLAYER_MASK_SCENTS) {
            sfxOffset = SFX_VOICE_BANK_SIZE * 7;
        } else {
            sfxOffset = this->ageProperties->unk_92;
        }

        func_800B8E58(this, sfxOffset + sfxId);
    }
}

// sAgeProperties
PlayerAgeProperties D_8085BA38[PLAYER_FORM_MAX] = {
    {
        // unk_00;
        84.0f,
        // unk_04;
        90.0f,
        // unk_08;
        1.5f,
        // unk_0C;
        166.5f,
        // unk_10;
        105.0f,
        // unk_14;
        119.100006f,
        // unk_18;
        88.5f,
        // unk_1C;
        61.5f,
        // unk_20;
        28.5f,
        // unk_24;
        54.0f,
        // unk_28;
        75.0f,
        // unk_2C;
        84.0f,
        // unk_30;
        102.0f,
        // unk_34; // height?
        70.0f,
        // unk_38;
        27.0f,
        // unk_3C;
        24.75f,
        // unk_40;
        105.0f,
        // unk_44
        { 9, 0x123F, 0x167 },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // u16 unk_92; // voice sfx offset?
        SFX_VOICE_BANK_SIZE * 0,
        // u16 unk_94;
        0x80,
        // f32 unk_98;
        33.0f,
        // f32 unk_9C;
        44.15145f,
        // LinkAnimationHeader* unk_A0;
        &gameplay_keep_Linkanim_00D540,
        // LinkAnimationHeader* unk_A4;
        &gameplay_keep_Linkanim_00D548,
        // LinkAnimationHeader* unk_A8;
        &gameplay_keep_Linkanim_00D660,
        // LinkAnimationHeader* unk_AC;
        &gameplay_keep_Linkanim_00DB90,
        // LinkAnimationHeader* unk_B0;
        &gameplay_keep_Linkanim_00DB98,
        {
            &gameplay_keep_Linkanim_00DBA0,
            &gameplay_keep_Linkanim_00DBA8,
            &gameplay_keep_Linkanim_00DAB0,
            &gameplay_keep_Linkanim_00DAB8,
        },
        { &gameplay_keep_Linkanim_00DA90, &gameplay_keep_Linkanim_00DA98 },
        { &gameplay_keep_Linkanim_00DB70, &gameplay_keep_Linkanim_00DB78 },
        { &gameplay_keep_Linkanim_00DB88, &gameplay_keep_Linkanim_00DB80 },
    },
    {
        // unk_00;
        70.0f,
        // unk_04;
        90.0f,
        // unk_08;
        0.74f,
        // unk_0C;
        111.0f,
        // unk_10;
        70.0f,
        // unk_14;
        79.4f,
        // unk_18;
        59.0f,
        // unk_1C;
        41.0f,
        // unk_20;
        19.0f,
        // unk_24;
        36.0f,
        // unk_28;
        50.0f,
        // unk_2C;
        56.0f,
        // unk_30;
        68.0f,
        // unk_34; // height?
        70.0f,
        // unk_38;
        19.5f,
        // unk_3C;
        18.2f,
        // unk_40;
        80.0f,
        // unk_44
        { 0x17, 0xF3B, 0xDF },
        {
            { 0x18, 0xF3B, 0xDF },
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0xF3B, 0xDF },
            { 0x17, 0x14CF, 0xDF },
        },
        {
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0x1AF2, 0xDF },
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0x1AF2, 0xDF },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // u16 unk_92; // voice sfx offset?
        SFX_VOICE_BANK_SIZE * 6,
        // u16 unk_94;
        0x150,
        // f32 unk_98;
        -25.0f,
        // f32 unk_9C;
        42.0f,
        // LinkAnimationHeader* unk_A0;
        &gameplay_keep_Linkanim_00E170,
        // LinkAnimationHeader* unk_A4;
        &gameplay_keep_Linkanim_00D548,
        // LinkAnimationHeader* unk_A8;
        &gameplay_keep_Linkanim_00D660,
        // LinkAnimationHeader* unk_AC;
        &gameplay_keep_Linkanim_00E198,
        // LinkAnimationHeader* unk_B0;
        &gameplay_keep_Linkanim_00E1A0,
        {
            &gameplay_keep_Linkanim_00E1A8,
            &gameplay_keep_Linkanim_00E1B0,
            &gameplay_keep_Linkanim_00E1A8,
            &gameplay_keep_Linkanim_00E1B0,
        },
        { &gameplay_keep_Linkanim_00DA90, &gameplay_keep_Linkanim_00DA98 },
        { &gameplay_keep_Linkanim_00E178, &gameplay_keep_Linkanim_00E180 },
        { &gameplay_keep_Linkanim_00E190, &gameplay_keep_Linkanim_00E188 },
    },
    {
        // unk_00;
        56.0f,
        // unk_04;
        90.0f,
        // unk_08;
        1.0f,
        // unk_0C;
        111.0f,
        // unk_10;
        70.0f,
        // unk_14;
        79.4f,
        // unk_18;
        59.0f,
        // unk_1C;
        41.0f,
        // unk_20;
        19.0f,
        // unk_24;
        36.0f,
        // unk_28;
        50.0f,
        // unk_2C;
        56.0f,
        // unk_30;
        68.0f,
        // unk_34; // height?
        70.0f,
        // unk_38;
        18.0f,
        // unk_3C;
        23.0f,
        // unk_40;
        70.0f,
        // unk_44
        { 0x17, 0x1323, -0x6D },
        {
            { 0x17, 0x1323, -0x58 },
            { 0x17, 0x18B7, -0x6D },
            { 0x17, 0x1323, -0x58 },
            { 0x17, 0x18B7, -0x6D },
        },
        {
            { 0x17, 0x18B7, -0x6D },
            { 0x18, 0x1EDA, -0x58 },
            { 0x17, 0x18B7, -0x6D },
            { 0x18, 0x1EDA, -0x58 },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // u16 unk_92; // voice sfx offset?
        SFX_VOICE_BANK_SIZE * 5,
        // u16 unk_94;
        0x120,
        // f32 unk_98;
        22.0f,
        // f32 unk_9C;
        36.0f,
        // LinkAnimationHeader* unk_A0;
        &gameplay_keep_Linkanim_00E300,
        // LinkAnimationHeader* unk_A4;
        &gameplay_keep_Linkanim_00D548,
        // LinkAnimationHeader* unk_A8;
        &gameplay_keep_Linkanim_00D660,
        // LinkAnimationHeader* unk_AC;
        &gameplay_keep_Linkanim_00E378,
        // LinkAnimationHeader* unk_B0;
        &gameplay_keep_Linkanim_00E380,
        {
            &gameplay_keep_Linkanim_00E388,
            &gameplay_keep_Linkanim_00E390,
            &gameplay_keep_Linkanim_00DAB0,
            &gameplay_keep_Linkanim_00DAB8,
        },
        { &gameplay_keep_Linkanim_00DA90, &gameplay_keep_Linkanim_00DA98 },
        { &gameplay_keep_Linkanim_00E358, &gameplay_keep_Linkanim_00E360 },
        { &gameplay_keep_Linkanim_00E370, &gameplay_keep_Linkanim_00E368 },
    },
    {
        // unk_00;
        35.0f,
        // unk_04;
        50.0f,
        // unk_08;
        0.3f,
        // unk_0C;
        71.0f,
        // unk_10;
        50.0f,
        // unk_14;
        49.0f,
        // unk_18;
        39.0f,
        // unk_1C;
        27.0f,
        // unk_20;
        19.0f,
        // unk_24;
        8.0f,
        // unk_28;
        13.6f,
        // unk_2C;
        24.0f,
        // unk_30;
        24.0f,
        // unk_34; // height?
        70.0f,
        // unk_38;
        14.0f,
        // unk_3C;
        12.0f,
        // unk_40;
        55.0f,
        // unk_44
        { -0x18, 0xDED, 0x36C },
        {
            { -0x18, 0xD92, 0x35E },
            { -0x18, 0x1371, 0x3A9 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { -0x18, 0x1371, 0x3A9 },
            { -0x18, 0x195F, 0x3A9 },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // u16 unk_92; // voice sfx offset?
        SFX_VOICE_BANK_SIZE * 4,
        // u16 unk_94;
        0xF0,
        // f32 unk_98;
        -21.0f,
        // f32 unk_9C;
        33.0f,
        // LinkAnimationHeader* unk_A0;
        &gameplay_keep_Linkanim_00E268,
        // LinkAnimationHeader* unk_A4;
        &gameplay_keep_Linkanim_00D548,
        // LinkAnimationHeader* unk_A8;
        &gameplay_keep_Linkanim_00D660,
        // LinkAnimationHeader* unk_AC;
        &gameplay_keep_Linkanim_00D1F8,
        // LinkAnimationHeader* unk_B0;
        &gameplay_keep_Linkanim_00D200,
        {
            &gameplay_keep_Linkanim_00D208,
            &gameplay_keep_Linkanim_00D210,
            &gameplay_keep_Linkanim_00DAB0,
            &gameplay_keep_Linkanim_00DAB8,
        },
        { &gameplay_keep_Linkanim_00DA90, &gameplay_keep_Linkanim_00DA98 },
        { &gameplay_keep_Linkanim_00D1D8, &gameplay_keep_Linkanim_00D1E0 },
        { &gameplay_keep_Linkanim_00D1F0, &gameplay_keep_Linkanim_00D1E8 },
    },
    {
        // unk_00;
        40.0f,
        // unk_04;
        60.0f,
        // unk_08;
        11.0f / 17.0f,
        // unk_0C;
        71.0f,
        // unk_10;
        50.0f,
        // unk_14;
        49.0f,
        // unk_18;
        39.0f,
        // unk_1C;
        27.0f,
        // unk_20;
        19.0f,
        // unk_24;
        22.0f,
        // unk_28;
        32.4f,
        // unk_2C;
        32.0f,
        // unk_30;
        48.0f,
        // unk_34; // height?
        11.0f / 17.0f * 70.0f,
        // unk_38;
        14.0f,
        // unk_3C;
        12.0f,
        // unk_40;
        55.0f,
        // unk_44
        { -0x18, 0xDED, 0x36C },
        {
            { -0x18, 0xD92, 0x35E },
            { -0x18, 0x1371, 0x3A9 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { -0x18, 0x1371, 0x3A9 },
            { -0x18, 0x195F, 0x3A9 },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // u16 unk_92; // voice sfx offset?
        SFX_VOICE_BANK_SIZE * 1,
        // u16 unk_94;
        0,
        // f32 unk_98;
        22.0f,
        // f32 unk_9C;
        29.4343f,
        // LinkAnimationHeader* unk_A0;
        &gameplay_keep_Linkanim_00D128,
        // LinkAnimationHeader* unk_A4;
        &gameplay_keep_Linkanim_00D170,
        // LinkAnimationHeader* unk_A8;
        &gameplay_keep_Linkanim_00D1B8,
        // LinkAnimationHeader* unk_AC;
        &gameplay_keep_Linkanim_00D1F8,
        // LinkAnimationHeader* unk_B0;
        &gameplay_keep_Linkanim_00D200,
        {
            &gameplay_keep_Linkanim_00D208,
            &gameplay_keep_Linkanim_00D210,
            &gameplay_keep_Linkanim_00DAB0,
            &gameplay_keep_Linkanim_00DAB8,
        },
        { &gameplay_keep_Linkanim_00DA90, &gameplay_keep_Linkanim_00DA98 },
        { &gameplay_keep_Linkanim_00D1D8, &gameplay_keep_Linkanim_00D1E0 },
        { &gameplay_keep_Linkanim_00D1F0, &gameplay_keep_Linkanim_00D1E8 },
    },
};

LinkAnimationHeader* D_8085BE84[PLAYER_ANIMGROUP_MAX][PLAYER_ANIMTYPE_MAX] = {
    // PLAYER_ANIMGROUP_0
    {
        &gameplay_keep_Linkanim_00DF28, // Default idle, looking forward
        &gameplay_keep_Linkanim_00DF20, // Default idle, looking forward, sword and shield
        &gameplay_keep_Linkanim_00DF20, // Default idle, looking forward, sword and shield
        &gameplay_keep_Linkanim_00D988, // Default idle, looking forward, two hand weapon
        &gameplay_keep_Linkanim_00DF28, // Default idle, looking forward
        &gameplay_keep_Linkanim_00DF28, // Default idle, looking forward
    },
    // PLAYER_ANIMGROUP_1
    {
        &gameplay_keep_Linkanim_00DF70,
        &gameplay_keep_Linkanim_00DF48,
        &gameplay_keep_Linkanim_00DF48,
        &gameplay_keep_Linkanim_00D9A0,
        &gameplay_keep_Linkanim_00DF70,
        &gameplay_keep_Linkanim_00DF70,
    },
    // PLAYER_ANIMGROUP_2
    {
        &gameplay_keep_Linkanim_00DE40, // Walking with empty hands
        &gameplay_keep_Linkanim_00D918, // Walking with Sword and Shield in hands
        &gameplay_keep_Linkanim_00DE38,
        &gameplay_keep_Linkanim_00D920, // Walking with Two handed weapon
        &gameplay_keep_Linkanim_00DE40, // Walking with empty hands
        &gameplay_keep_Linkanim_00DE40, // Walking with empty hands
    },
    // PLAYER_ANIMGROUP_3
    {
        &gameplay_keep_Linkanim_00DBB8,
        &gameplay_keep_Linkanim_00D808,
        &gameplay_keep_Linkanim_00DBB8,
        &gameplay_keep_Linkanim_00D810,
        &gameplay_keep_Linkanim_00DBB8,
        &gameplay_keep_Linkanim_00DBB8,
    },
    // PLAYER_ANIMGROUP_4
    {
        &gameplay_keep_Linkanim_00DF08,
        &gameplay_keep_Linkanim_00D468,
        &gameplay_keep_Linkanim_00D468,
        &gameplay_keep_Linkanim_00D970,
        &gameplay_keep_Linkanim_00DF08,
        &gameplay_keep_Linkanim_00DF08,
    },
    // PLAYER_ANIMGROUP_5
    {
        &gameplay_keep_Linkanim_00DF18,
        &gameplay_keep_Linkanim_00D480,
        &gameplay_keep_Linkanim_00D480,
        &gameplay_keep_Linkanim_00D980,
        &gameplay_keep_Linkanim_00DF18,
        &gameplay_keep_Linkanim_00DF18,
    },
    // PLAYER_ANIMGROUP_6
    {
        &gameplay_keep_Linkanim_00D960,
        &gameplay_keep_Linkanim_00DEE0,
        &gameplay_keep_Linkanim_00DEE0,
        &gameplay_keep_Linkanim_00D960,
        &gameplay_keep_Linkanim_00D960,
        &gameplay_keep_Linkanim_00D960,
    },
    // PLAYER_ANIMGROUP_7
    {
        &gameplay_keep_Linkanim_00DD98,
        &gameplay_keep_Linkanim_00D860,
        &gameplay_keep_Linkanim_00D860,
        &gameplay_keep_Linkanim_00DD98,
        &gameplay_keep_Linkanim_00DD98,
        &gameplay_keep_Linkanim_00DD98,
    },
    // PLAYER_ANIMGROUP_8
    {
        &gameplay_keep_Linkanim_00D578,
        &gameplay_keep_Linkanim_00D570,
        &gameplay_keep_Linkanim_00D570,
        &gameplay_keep_Linkanim_00D578,
        &gameplay_keep_Linkanim_00D578,
        &gameplay_keep_Linkanim_00D578,
    },
    // PLAYER_ANIMGROUP_9
    {
        &gameplay_keep_Linkanim_00D140,
        &gameplay_keep_Linkanim_00D140,
        &gameplay_keep_Linkanim_00D140,
        &gameplay_keep_Linkanim_00D140,
        &gameplay_keep_Linkanim_00D140,
        &gameplay_keep_Linkanim_00D140,
    },
    // PLAYER_ANIMGROUP_10
    {
        &gameplay_keep_Linkanim_00D588,
        &gameplay_keep_Linkanim_00D580,
        &gameplay_keep_Linkanim_00D580,
        &gameplay_keep_Linkanim_00D588,
        &gameplay_keep_Linkanim_00D588,
        &gameplay_keep_Linkanim_00D588,
    },
    // PLAYER_ANIMGROUP_11
    {
        &gameplay_keep_Linkanim_00D148,
        &gameplay_keep_Linkanim_00D148,
        &gameplay_keep_Linkanim_00D148,
        &gameplay_keep_Linkanim_00D148,
        &gameplay_keep_Linkanim_00D148,
        &gameplay_keep_Linkanim_00D148,
    },
    // PLAYER_ANIMGROUP_12
    {
        &gameplay_keep_Linkanim_00DB28, // Grabbing something from the floor
        &gameplay_keep_Linkanim_00DB20, &gameplay_keep_Linkanim_00DB20,
        &gameplay_keep_Linkanim_00DB28, // Grabbing something from the floor
        &gameplay_keep_Linkanim_00DB28, // Grabbing something from the floor
        &gameplay_keep_Linkanim_00DB28, // Grabbing something from the floor
    },
    // PLAYER_ANIMGROUP_13
    {
        &gameplay_keep_Linkanim_00DD18,
        &gameplay_keep_Linkanim_00DD10,
        &gameplay_keep_Linkanim_00DD10,
        &gameplay_keep_Linkanim_00DD18,
        &gameplay_keep_Linkanim_00DD18,
        &gameplay_keep_Linkanim_00DD18,
    },
    // PLAYER_ANIMGROUP_14
    {
        &gameplay_keep_Linkanim_00DE70,
        &gameplay_keep_Linkanim_00DE68,
        &gameplay_keep_Linkanim_00DE68,
        &gameplay_keep_Linkanim_00DE70,
        &gameplay_keep_Linkanim_00DE70,
        &gameplay_keep_Linkanim_00DE70,
    },
    // PLAYER_ANIMGROUP_15
    {
        &gameplay_keep_Linkanim_00DD28, // Rolling with nothing in hands
        &gameplay_keep_Linkanim_00DD20, // Rolling with sword and shield
        &gameplay_keep_Linkanim_00DD20, // Rolling with sword and shield
        &gameplay_keep_Linkanim_00D858, // Rolling with two hand weapon
        &gameplay_keep_Linkanim_00DD28, // Rolling with nothing in hands
        &gameplay_keep_Linkanim_00DD28, // Rolling with nothing in hands
    },
    // PLAYER_ANIMGROUP_16
    {
        &gameplay_keep_Linkanim_00DCC0, // Rolling bonk
        &gameplay_keep_Linkanim_00DCB8, // Rolling bonk swrod and shield
        &gameplay_keep_Linkanim_00DCB8, // Rolling bonk swrod and shield
        &gameplay_keep_Linkanim_00DCC8, // Rolling bonk two hand weapon
        &gameplay_keep_Linkanim_00DCC0, // Rolling bonk
        &gameplay_keep_Linkanim_00DCC0, // Rolling bonk
    },
    // PLAYER_ANIMGROUP_17
    {
        &gameplay_keep_Linkanim_00DF58,
        &gameplay_keep_Linkanim_00DF50,
        &gameplay_keep_Linkanim_00DF50,
        &gameplay_keep_Linkanim_00D990,
        &gameplay_keep_Linkanim_00DF58,
        &gameplay_keep_Linkanim_00DF58,
    },
    // PLAYER_ANIMGROUP_18
    {
        &gameplay_keep_Linkanim_00DF68,
        &gameplay_keep_Linkanim_00DF60,
        &gameplay_keep_Linkanim_00DF60,
        &gameplay_keep_Linkanim_00D998,
        &gameplay_keep_Linkanim_00DF68,
        &gameplay_keep_Linkanim_00DF68,
    },
    // PLAYER_ANIMGROUP_19
    {
        &gameplay_keep_Linkanim_00DBD8,
        &gameplay_keep_Linkanim_00DBC0,
        &gameplay_keep_Linkanim_00DBC0,
        &gameplay_keep_Linkanim_00DBD8,
        &gameplay_keep_Linkanim_00D510,
        &gameplay_keep_Linkanim_00DBD8,
    },
    // PLAYER_ANIMGROUP_20
    {
        &gameplay_keep_Linkanim_00DBF8,
        &gameplay_keep_Linkanim_00DBF0,
        &gameplay_keep_Linkanim_00DBF0,
        &gameplay_keep_Linkanim_00DBF8,
        &gameplay_keep_Linkanim_00D518,
        &gameplay_keep_Linkanim_00DBF8,
    },
    // PLAYER_ANIMGROUP_21
    {
        &gameplay_keep_Linkanim_00DBD0,
        &gameplay_keep_Linkanim_00DBC8,
        &gameplay_keep_Linkanim_00DBC8,
        &gameplay_keep_Linkanim_00DBD0,
        &gameplay_keep_Linkanim_00DBD0,
        &gameplay_keep_Linkanim_00DBD0,
    },
    // PLAYER_ANIMGROUP_22
    {
        &gameplay_keep_Linkanim_00DE90,
        &gameplay_keep_Linkanim_00DE88,
        &gameplay_keep_Linkanim_00DE88,
        &gameplay_keep_Linkanim_00D938,
        &gameplay_keep_Linkanim_00DE90,
        &gameplay_keep_Linkanim_00DE90,
    },
    // PLAYER_ANIMGROUP_23
    {
        &gameplay_keep_Linkanim_00DE78, // Side walking
        &gameplay_keep_Linkanim_00D448, // Side walking with sword and shield in hands
        &gameplay_keep_Linkanim_00D448, // Side walking with sword and shield in hands
        &gameplay_keep_Linkanim_00D928,
        &gameplay_keep_Linkanim_00DE78, // Side walking
        &gameplay_keep_Linkanim_00DE78, // Side walking
    },
    // PLAYER_ANIMGROUP_24
    {
        &gameplay_keep_Linkanim_00DE80,
        &gameplay_keep_Linkanim_00D450,
        &gameplay_keep_Linkanim_00D450,
        &gameplay_keep_Linkanim_00D930,
        &gameplay_keep_Linkanim_00DE80,
        &gameplay_keep_Linkanim_00DE80,
    },
    // PLAYER_ANIMGROUP_25
    {
        &gameplay_keep_Linkanim_00DA80,
        &gameplay_keep_Linkanim_00DA78,
        &gameplay_keep_Linkanim_00DA78,
        &gameplay_keep_Linkanim_00DA80,
        &gameplay_keep_Linkanim_00DA80,
        &gameplay_keep_Linkanim_00DA80,
    },
    // PLAYER_ANIMGROUP_26
    {
        &gameplay_keep_Linkanim_00DF00,
        &gameplay_keep_Linkanim_00DF00,
        &gameplay_keep_Linkanim_00DF00,
        &gameplay_keep_Linkanim_00D968,
        &gameplay_keep_Linkanim_00D968,
        &gameplay_keep_Linkanim_00D968,
    },
    // PLAYER_ANIMGROUP_27
    {
        &gameplay_keep_Linkanim_00DF10,
        &gameplay_keep_Linkanim_00DF10,
        &gameplay_keep_Linkanim_00DF10,
        &gameplay_keep_Linkanim_00D978,
        &gameplay_keep_Linkanim_00D978,
        &gameplay_keep_Linkanim_00D978,
    },
    // PLAYER_ANIMGROUP_28
    {
        &gameplay_keep_Linkanim_00DEB8,
        &gameplay_keep_Linkanim_00DEB0,
        &gameplay_keep_Linkanim_00DEB0,
        &gameplay_keep_Linkanim_00DEB8,
        &gameplay_keep_Linkanim_00DEB8,
        &gameplay_keep_Linkanim_00DEB8,
    },
    // PLAYER_ANIMGROUP_29
    {
        &gameplay_keep_Linkanim_00DE20,
        &gameplay_keep_Linkanim_00DE18,
        &gameplay_keep_Linkanim_00DE18,
        &gameplay_keep_Linkanim_00DE20,
        &gameplay_keep_Linkanim_00DE20,
        &gameplay_keep_Linkanim_00DE20,
    },
    // PLAYER_ANIMGROUP_30
    {
        &gameplay_keep_Linkanim_00DB08,
        &gameplay_keep_Linkanim_00DB08,
        &gameplay_keep_Linkanim_00DB08,
        &gameplay_keep_Linkanim_00DB08,
        &gameplay_keep_Linkanim_00DB08,
        &gameplay_keep_Linkanim_00DB08,
    },
    // PLAYER_ANIMGROUP_31
    {
        &gameplay_keep_Linkanim_00DB50,
        &gameplay_keep_Linkanim_00DB38,
        &gameplay_keep_Linkanim_00DB38,
        &gameplay_keep_Linkanim_00DB50,
        &gameplay_keep_Linkanim_00DB50,
        &gameplay_keep_Linkanim_00DB50,
    },
    // PLAYER_ANIMGROUP_32
    {
        &gameplay_keep_Linkanim_00DB60,
        &gameplay_keep_Linkanim_00DB58,
        &gameplay_keep_Linkanim_00DB58,
        &gameplay_keep_Linkanim_00DB60,
        &gameplay_keep_Linkanim_00DB60,
        &gameplay_keep_Linkanim_00DB60,
    },
    // PLAYER_ANIMGROUP_33
    {
        &gameplay_keep_Linkanim_00DB48,
        &gameplay_keep_Linkanim_00DB40,
        &gameplay_keep_Linkanim_00DB40,
        &gameplay_keep_Linkanim_00DB48,
        &gameplay_keep_Linkanim_00DB48,
        &gameplay_keep_Linkanim_00DB48,
    },
    // PLAYER_ANIMGROUP_34
    {
        &gameplay_keep_Linkanim_00DDD8,
        &gameplay_keep_Linkanim_00DDD0,
        &gameplay_keep_Linkanim_00DDD0,
        &gameplay_keep_Linkanim_00DDD8,
        &gameplay_keep_Linkanim_00DDD8,
        &gameplay_keep_Linkanim_00DDD8,
    },
    // PLAYER_ANIMGROUP_35
    {
        &gameplay_keep_Linkanim_00DDE8,
        &gameplay_keep_Linkanim_00DDE0,
        &gameplay_keep_Linkanim_00DDE0,
        &gameplay_keep_Linkanim_00DDE8,
        &gameplay_keep_Linkanim_00DDE8,
        &gameplay_keep_Linkanim_00DDE8,
    },
    // PLAYER_ANIMGROUP_36
    {
        &gameplay_keep_Linkanim_00DDC8,
        &gameplay_keep_Linkanim_00DDC0,
        &gameplay_keep_Linkanim_00DDC0,
        &gameplay_keep_Linkanim_00DDC8,
        &gameplay_keep_Linkanim_00DDC8,
        &gameplay_keep_Linkanim_00DDC8,
    },
    // PLAYER_ANIMGROUP_37
    {
        &gameplay_keep_Linkanim_00DC40,
        &gameplay_keep_Linkanim_00DC38,
        &gameplay_keep_Linkanim_00DC38,
        &gameplay_keep_Linkanim_00DC40,
        &gameplay_keep_Linkanim_00DC40,
        &gameplay_keep_Linkanim_00DC40,
    },
    // PLAYER_ANIMGROUP_38
    {
        &gameplay_keep_Linkanim_00DCE8,
        &gameplay_keep_Linkanim_00DCE0,
        &gameplay_keep_Linkanim_00DCE0,
        &gameplay_keep_Linkanim_00DCE8,
        &gameplay_keep_Linkanim_00DCE8,
        &gameplay_keep_Linkanim_00DCE8,
    },
    // PLAYER_ANIMGROUP_39
    {
        &gameplay_keep_Linkanim_00DD08,
        &gameplay_keep_Linkanim_00DD00,
        &gameplay_keep_Linkanim_00DD00,
        &gameplay_keep_Linkanim_00DD08,
        &gameplay_keep_Linkanim_00DD08,
        &gameplay_keep_Linkanim_00DD08,
    },
    // PLAYER_ANIMGROUP_40
    {
        &gameplay_keep_Linkanim_00DCF8,
        &gameplay_keep_Linkanim_00DCF0,
        &gameplay_keep_Linkanim_00DCF0,
        &gameplay_keep_Linkanim_00DCF8,
        &gameplay_keep_Linkanim_00DCF8,
        &gameplay_keep_Linkanim_00DCF8,
    },
    // PLAYER_ANIMGROUP_41
    {
        &gameplay_keep_Linkanim_00DC10,
        &gameplay_keep_Linkanim_00DC08,
        &gameplay_keep_Linkanim_00DC08,
        &gameplay_keep_Linkanim_00DC18,
        &gameplay_keep_Linkanim_00DC10,
        &gameplay_keep_Linkanim_00DC10,
    },
    // PLAYER_ANIMGROUP_42
    {
        &gameplay_keep_Linkanim_00DED0,
        &gameplay_keep_Linkanim_00DEC8,
        &gameplay_keep_Linkanim_00DEC8,
        &gameplay_keep_Linkanim_00DED8,
        &gameplay_keep_Linkanim_00DED0,
        &gameplay_keep_Linkanim_00DED0,
    },
    // PLAYER_ANIMGROUP_43
    {
        &gameplay_keep_Linkanim_00E450,
        &gameplay_keep_Linkanim_00E108,
        &gameplay_keep_Linkanim_00E108,
        &gameplay_keep_Linkanim_00E450,
        &gameplay_keep_Linkanim_00E450,
        &gameplay_keep_Linkanim_00E450,
    }
};

struct_8085C2A4 D_8085C2A4[] = {
    {
        &gameplay_keep_Linkanim_00D828,
        &gameplay_keep_Linkanim_00D838,
        &gameplay_keep_Linkanim_00D830,
    },
    {
        &gameplay_keep_Linkanim_00D770,
        &gameplay_keep_Linkanim_00D780,
        &gameplay_keep_Linkanim_00D778,
    },
    {
        &gameplay_keep_Linkanim_00D7F0,
        &gameplay_keep_Linkanim_00D800,
        &gameplay_keep_Linkanim_00D7F8,
    },
    {
        &gameplay_keep_Linkanim_00D7A8,
        &gameplay_keep_Linkanim_00D7B8,
        &gameplay_keep_Linkanim_00D7B0,
    },
    {
        &gameplay_keep_Linkanim_00DD50,
        &gameplay_keep_Linkanim_00DD58,
        &gameplay_keep_Linkanim_00DD58,
    },
    {
        &gameplay_keep_Linkanim_00DD60,
        &gameplay_keep_Linkanim_00DD68,
        &gameplay_keep_Linkanim_00DD68,
    },
};

// sCylinderInit
ColliderCylinderInit D_8085C2EC = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 12, 60, 0, { 0, 0, 0 } },
};

// sShieldCylinderInit
ColliderCylinderInit D_8085C318 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x02 },
        { 0xD7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 25, 60, 0, { 0, 0, 0 } },
};

// sMeleeWeaponQuadInit
ColliderQuadInit D_8085C344 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x01 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// sShieldQuadInit
ColliderQuadInit D_8085C394 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0xD7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

f32 D_8085C3E4 = 1.0f;
f32 D_8085C3E8 = 1.0f;

u16 D_8085C3EC[] = {
    NA_SE_VO_LI_SWEAT,
    NA_SE_VO_LI_SNEEZE,
    NA_SE_VO_LI_RELAX,
    NA_SE_VO_LI_FALL_L,
};

void func_8082E00C(Player* this) {
    s32 i;
    u16* sfxIdPtr = D_8085C3EC;

    for (i = 0; i < ARRAY_COUNT(D_8085C3EC); i++) {
        Audio_StopSfxById(*sfxIdPtr + this->ageProperties->unk_92);
        sfxIdPtr++;
    }
}

u16 func_8082E078(Player* this, u16 sfxId) {
    return sfxId + this->unk_B72;
}

void func_8082E094(Player* this, u16 sfxId) {
    func_800B8E58(this, func_8082E078(this, sfxId));
}

u16 func_8082E0CC(Player* this, u16 sfxId) {
    return sfxId + this->unk_B72 + this->ageProperties->unk_94;
}

void func_8082E0F4(Player* this, u16 sfxId) {
    func_800B8E58(this, func_8082E0CC(this, sfxId));
}

void func_8082E12C(Player* this, f32 arg1) {
    s32 sfxId;

    if (this->currentMask == PLAYER_MASK_GIANT) {
        sfxId = NA_SE_PL_GIANT_WALK;
    } else {
        sfxId = func_8082E0CC(this, NA_SE_PL_WALK_GROUND);
    }
    func_8019F638(&this->actor.projectedPos, sfxId, arg1);
}

void func_8082E188(Player* this) {
    func_800B8E58(this, func_8082E0CC(this, NA_SE_PL_JUMP_GROUND));
}

void func_8082E1BC(Player* this) {
    func_800B8E58(this, func_8082E0CC(this, NA_SE_PL_LAND_GROUND));
}

void func_8082E1F0(Player* this, u16 sfxId) {
    func_800B8E58(this, sfxId);
    this->stateFlags2 |= PLAYER_STATE2_8;
}

void Player_PlayAnimSfx(Player* this, AnimSfxEntry* entry) {
    s32 cond;

    do {
        s32 data = ABS_ALT(entry->flags);
        s32 type = ANIMSFX_GET_TYPE(data);

        if (LinkAnimation_OnFrame(&this->skelAnime, fabsf(ANIMSFX_GET_FRAME(data)))) {
            if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_1)) {
                func_800B8E58(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_2)) {
                func_8082E094(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_3)) {
                func_8082E0F4(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_VOICE)) {
                func_8082DF8C(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_5)) {
                func_8082E1BC(this);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_6)) {
                func_8082E12C(this, 6.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_7)) {
                func_8082E188(this);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_8)) {
                func_8082E12C(this, 0.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_9)) {
                func_8019F638(&this->actor.projectedPos, this->ageProperties->unk_94 + NA_SE_PL_WALK_LADDER, 0.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_10)) {
                func_800B8E58(this, entry->sfxId + this->ageProperties->unk_94);
            }
        }

        cond = entry->flags >= 0;
        entry++;
    } while (cond);
}

void func_8082E438(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                         -6.0f);
}

void func_8082E4A4(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                         -6.0f);
}

void func_8082E514(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f);
}

void func_8082E55C(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f);
}

void func_8082E5A8(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
}

void func_8082E5EC(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
}

void func_8082E634(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -16.0f);
}

s32 func_8082E67C(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, anim);
        return true;
    }
    return false;
}

void func_8082E6D0(Player* this) {
    this->skelAnime.prevTransl = this->skelAnime.baseTransl;
    this->skelAnime.prevRot = this->actor.shape.rot.y;
}

void func_8082E6F8(Player* this) {
    func_8082E6D0(this);
    this->skelAnime.prevTransl.x *= this->ageProperties->unk_08;
    this->skelAnime.prevTransl.y *= this->ageProperties->unk_08;
    this->skelAnime.prevTransl.z *= this->ageProperties->unk_08;
}

void func_8082E784(Player* this) {
    this->skelAnime.jointTable[1].y = 0;
}

void func_8082E794(Player* this) {
    if (this->skelAnime.moveFlags != 0) {
        func_8082DC28(this);
        this->skelAnime.jointTable->x = this->skelAnime.baseTransl.x;
        this->skelAnime.jointTable->z = this->skelAnime.baseTransl.z;

        if (this->skelAnime.moveFlags & 8) {
            if (this->skelAnime.moveFlags & 2) {
                this->skelAnime.jointTable->y = this->skelAnime.prevTransl.y;
            }
        } else {
            this->skelAnime.jointTable->y = this->skelAnime.baseTransl.y;
        }
        func_8082E6D0(this);
        this->skelAnime.moveFlags = 0;
    }
}

void func_8082E820(Player* this, s32 moveFlags) {
    Vec3f pos;

    this->skelAnime.moveFlags = moveFlags;
    this->skelAnime.prevTransl = this->skelAnime.baseTransl;
    SkelAnime_UpdateTranslation(&this->skelAnime, &pos, this->actor.shape.rot.y);

    if (moveFlags & 1) {
        pos.x *= this->ageProperties->unk_08;
        pos.z *= this->ageProperties->unk_08;
        this->actor.world.pos.x += pos.x * this->actor.scale.x;
        this->actor.world.pos.z += pos.z * this->actor.scale.z;
    }

    if (moveFlags & 2) {
        if (!(moveFlags & 4)) {
            pos.y *= this->ageProperties->unk_08;
        }
        this->actor.world.pos.y += pos.y * this->actor.scale.y;
    }

    func_8082DC28(this);
}

void func_8082E920(PlayState* play, Player* this, s32 moveFlags) {
    if (moveFlags & 0x200) {
        func_8082E6F8(this);
    } else if ((moveFlags & 0x100) || (this->skelAnime.moveFlags != 0)) {
        func_8082E6D0(this);
    } else {
        this->skelAnime.prevTransl = this->skelAnime.jointTable[0];
        this->skelAnime.prevRot = this->actor.shape.rot.y;
    }

    this->skelAnime.moveFlags = moveFlags;
    func_8082DABC(this);
    AnimationContext_DisableQueue(play);
}

void func_8082E9C8(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 moveFlags, f32 playSpeed) {
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, playSpeed);
    func_8082E920(play, this, moveFlags);
}

void func_8082EA10(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 arg3) {
    func_8082E9C8(play, this, anim, arg3, 3.0f / 3.0f);
}

void func_8082EA38(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 arg3) {
    func_8082E9C8(play, this, anim, arg3, 2.0f / 3.0f);
}

void func_8082EA60(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_8082EA38(play, this, anim, 0x20C);
}

void func_8082EA80(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 moveFlags, f32 playSpeed) {
    LinkAnimation_PlayLoopSetSpeed(play, &this->skelAnime, anim, playSpeed);
    func_8082E920(play, this, moveFlags);
}

void func_8082EAC8(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 moveFlags) {
    func_8082EA80(play, this, anim, moveFlags, 3.0f / 3.0f);
}

void func_8082EAF0(PlayState* play, Player* this, LinkAnimationHeader* anim, s32 arg3) {
    func_8082EA80(play, this, anim, arg3, 2.0f / 3.0f);
}

void func_8082EB18(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_8082EAF0(play, this, anim, 0x1C);
}

void func_8082EB38(PlayState* play, Player* this) {
    s8 var_v0;
    s8 var_v1;

    this->unk_D60 = D_80862AFC;
    this->unk_D64 = D_80862B00;
    func_800FF3A0(&D_80862AFC, &D_80862B00, D_80862B44);

    if (D_80862AFC < 8.0f) {
        D_80862AFC = 0.0f;
    }

    D_80862B02 = Camera_GetInputDirYaw(play->cameraPtrs[play->activeCamId]) + D_80862B00;
    this->unk_ADE = (this->unk_ADE + 1) % ARRAY_COUNT(this->unk_ADF);
    if (D_80862AFC < 55.0f) {
        var_v0 = -1;
        var_v1 = -1;
    } else {
        var_v1 = ((u16)(D_80862B00 + 0x2000)) >> 9;
        var_v0 = ((u16)(BINANG_SUB(D_80862B02, this->actor.shape.rot.y) + 0x2000)) >> 0xE;
    }
    this->unk_ADF[this->unk_ADE] = var_v1;
    this->unk_AE3[this->unk_ADE] = var_v0;
}

void func_8082EC9C(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, D_8085C3E4);
}

s32 func_8082ECCC(Player* this) {
    return this->stateFlags1 & PLAYER_STATE1_1000000;
}

// TODO: consider what to do with the NONEs: cannot use a zero-argument macro like OoT since the text id is involved.
#define GET_ITEM(itemId, objectId, drawId, textId, field, CHEST_ANIM) \
    { itemId, field, (CHEST_ANIM != CHEST_ANIM_SHORT ? 1 : -1) * (drawId + 1), textId, objectId }

#define CHEST_ANIM_SHORT 0
#define CHEST_ANIM_LONG 1

#define GIFIELD_GET_DROP_TYPE(field) ((field)&0x1F)
#define GIFIELD_20 (1 << 5)
#define GIFIELD_40 (1 << 6)
#define GIFIELD_NO_COLLECTIBLE (1 << 7)
/**
 * `flags` must be 0, GIFIELD_20, GIFIELD_40 or GIFIELD_NO_COLLECTIBLE (which can be or'ed together)
 * `dropType` must be either a value from the `Item00Type` enum or 0 if the `GIFIELD_NO_COLLECTIBLE` flag was used
 */
#define GIFIELD(flags, dropType) ((flags) | (dropType))

GetItemEntry sGetItemTable[GI_MAX - 1] = {
    /* 0x01 */ GET_ITEM(ITEM_RUPEE_GREEN, OBJECT_GI_RUPY, GID_RUPEE_GREEN, 0xC4, GIFIELD(0, ITEM00_RUPEE_GREEN),
                        CHEST_ANIM_SHORT),
    /* 0x02 */
    GET_ITEM(ITEM_RUPEE_BLUE, OBJECT_GI_RUPY, GID_RUPEE_BLUE, 0x2, GIFIELD(0, ITEM00_RUPEE_BLUE), CHEST_ANIM_SHORT),
    /* 0x03 */
    GET_ITEM(ITEM_RUPEE_10, OBJECT_GI_RUPY, GID_RUPEE_RED, 0x3, GIFIELD(0, ITEM00_RUPEE_RED), CHEST_ANIM_SHORT),
    /* 0x04 */
    GET_ITEM(ITEM_RUPEE_RED, OBJECT_GI_RUPY, GID_RUPEE_RED, 0x4, GIFIELD(0, ITEM00_RUPEE_RED), CHEST_ANIM_SHORT),
    /* 0x05 */
    GET_ITEM(ITEM_RUPEE_PURPLE, OBJECT_GI_RUPY, GID_RUPEE_PURPLE, 0x5, GIFIELD(0, ITEM00_RUPEE_PURPLE),
             CHEST_ANIM_SHORT),
    /* 0x06 */
    GET_ITEM(ITEM_RUPEE_SILVER, OBJECT_GI_RUPY, GID_RUPEE_SILVER, 0x6, GIFIELD(0, ITEM00_RUPEE_PURPLE),
             CHEST_ANIM_SHORT),
    /* 0x07 */
    GET_ITEM(ITEM_RUPEE_HUGE, OBJECT_GI_RUPY, GID_RUPEE_HUGE, 0x7, GIFIELD(0, ITEM00_RUPEE_HUGE), CHEST_ANIM_SHORT),
    /* 0x08 */
    GET_ITEM(ITEM_WALLET_ADULT, OBJECT_GI_PURSE, GID_WALLET_ADULT, 0x8, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x09 */
    GET_ITEM(ITEM_WALLET_GIANT, OBJECT_GI_PURSE, GID_WALLET_GIANT, 0x9, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x0A */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0xA, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x0B */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0xB,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x0C */
    GET_ITEM(ITEM_HEART_PIECE_2, OBJECT_GI_HEARTS, GID_HEART_PIECE, 0xC,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x0D */
    GET_ITEM(ITEM_HEART_CONTAINER, OBJECT_GI_HEARTS, GID_HEART_CONTAINER, 0xD,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x0E */
    GET_ITEM(ITEM_MAGIC_SMALL, OBJECT_GI_MAGICPOT, GID_MAGIC_SMALL, 0xE,
             GIFIELD(GIFIELD_20 | GIFIELD_40, ITEM00_MAGIC_SMALL), CHEST_ANIM_SHORT),
    /* 0x0F */
    GET_ITEM(ITEM_MAGIC_LARGE, OBJECT_GI_MAGICPOT, GID_MAGIC_LARGE, 0xF,
             GIFIELD(GIFIELD_20 | GIFIELD_40, ITEM00_MAGIC_LARGE), CHEST_ANIM_SHORT),
    /* 0x10 */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x10, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x11 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x11, 0, 0),
    /* 0x12 */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x12, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x13 */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x13, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x14 */
    GET_ITEM(ITEM_BOMB, OBJECT_GI_BOMB_1, GID_BOMB, 0x14, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    /* 0x15 */
    GET_ITEM(ITEM_BOMBS_5, OBJECT_GI_BOMB_1, GID_BOMB, 0x15, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    /* 0x16 */
    GET_ITEM(ITEM_BOMBS_10, OBJECT_GI_BOMB_1, GID_BOMB, 0x16, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    /* 0x17 */
    GET_ITEM(ITEM_BOMBS_20, OBJECT_GI_BOMB_1, GID_BOMB, 0x17, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    /* 0x18 */
    GET_ITEM(ITEM_BOMBS_30, OBJECT_GI_BOMB_1, GID_BOMB, 0x18, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    /* 0x19 */ GET_ITEM(ITEM_STICK, OBJECT_GI_STICK, GID_STICK, 0x19, GIFIELD(0, ITEM00_STICK), CHEST_ANIM_SHORT),
    /* 0x1A */
    GET_ITEM(ITEM_BOMBCHUS_10, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x1A, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x1B */
    GET_ITEM(ITEM_BOMB_BAG_20, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_20, 0x1B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x1C */
    GET_ITEM(ITEM_BOMB_BAG_30, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_30, 0x1C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x1D */
    GET_ITEM(ITEM_BOMB_BAG_40, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_40, 0x1D,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x1E */
    GET_ITEM(ITEM_ARROWS_10, OBJECT_GI_ARROW, GID_ARROWS_SMALL, 0x1E, GIFIELD(GIFIELD_40, ITEM00_ARROWS_30),
             CHEST_ANIM_SHORT),
    /* 0x1F */
    GET_ITEM(ITEM_ARROWS_30, OBJECT_GI_ARROW, GID_ARROWS_MEDIUM, 0x1F, GIFIELD(GIFIELD_40, ITEM00_ARROWS_40),
             CHEST_ANIM_SHORT),
    /* 0x20 */
    GET_ITEM(ITEM_ARROWS_40, OBJECT_GI_ARROW, GID_ARROWS_LARGE, 0x20, GIFIELD(GIFIELD_40, ITEM00_ARROWS_50),
             CHEST_ANIM_SHORT),
    /* 0x21 */
    GET_ITEM(ITEM_ARROWS_40, OBJECT_GI_ARROW, GID_ARROWS_LARGE, 0x21, GIFIELD(GIFIELD_40, ITEM00_ARROWS_50),
             CHEST_ANIM_SHORT),
    /* 0x22 */
    GET_ITEM(ITEM_BOW, OBJECT_GI_BOW, GID_BOW, 0x22, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x23 */
    GET_ITEM(ITEM_QUIVER_40, OBJECT_GI_ARROWCASE, GID_QUIVER_40, 0x23, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x24 */
    GET_ITEM(ITEM_QUIVER_50, OBJECT_GI_ARROWCASE, GID_QUIVER_50, 0x24, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x25 */
    GET_ITEM(ITEM_ARROW_FIRE, OBJECT_GI_M_ARROW, GID_ARROW_FIRE, 0x25, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x26 */
    GET_ITEM(ITEM_ARROW_ICE, OBJECT_GI_M_ARROW, GID_ARROW_ICE, 0x26, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x27 */
    GET_ITEM(ITEM_ARROW_LIGHT, OBJECT_GI_M_ARROW, GID_ARROW_LIGHT, 0x27,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x28 */ GET_ITEM(ITEM_NUT, OBJECT_GI_NUTS, GID_NUTS, 0x28, GIFIELD(0, ITEM00_NUTS_1), CHEST_ANIM_SHORT),
    /* 0x29 */ GET_ITEM(ITEM_NUTS_5, OBJECT_GI_NUTS, GID_NUTS, 0x29, GIFIELD(0, ITEM00_NUTS_1), CHEST_ANIM_SHORT),
    /* 0x2A */ GET_ITEM(ITEM_NUTS_10, OBJECT_GI_NUTS, GID_NUTS, 0x2A, GIFIELD(0, ITEM00_NUTS_1), CHEST_ANIM_SHORT),
    /* 0x2B */
    GET_ITEM(ITEM_NUT_UPGRADE_30, OBJECT_GI_NUTS, GID_NUTS, 0x2B, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x2C */
    GET_ITEM(ITEM_NUT_UPGRADE_30, OBJECT_GI_NUTS, GID_NUTS, 0x2C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x2D */
    GET_ITEM(ITEM_NUT_UPGRADE_40, OBJECT_GI_NUTS, GID_NUTS, 0x2D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x2E */
    GET_ITEM(ITEM_BOMBCHUS_20, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x2E, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x2F */
    GET_ITEM(ITEM_STICK_UPGRADE_20, OBJECT_GI_STICK, GID_STICK, 0x2F, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x30 */
    GET_ITEM(ITEM_STICK_UPGRADE_20, OBJECT_GI_STICK, GID_STICK, 0x30, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x31 */
    GET_ITEM(ITEM_STICK_UPGRADE_30, OBJECT_GI_STICK, GID_STICK, 0x31, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x32 */
    GET_ITEM(ITEM_SHIELD_HERO, OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, 0x32,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    /* 0x33 */
    GET_ITEM(ITEM_SHIELD_MIRROR, OBJECT_GI_SHIELD_3, GID_SHIELD_MIRROR, 0x33,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x34 */
    GET_ITEM(ITEM_POWDER_KEG, OBJECT_GI_BIGBOMB, GID_POWDER_KEG, 0x34, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x35 */
    GET_ITEM(ITEM_MAGIC_BEANS, OBJECT_GI_BEAN, GID_MAGIC_BEANS, 0x35, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x36 */
    GET_ITEM(ITEM_BOMBCHUS_1, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x36, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x37 */
    GET_ITEM(ITEM_SWORD_KOKIRI, OBJECT_GI_SWORD_1, GID_SWORD_KOKIRI, 0x37,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x38 */
    GET_ITEM(ITEM_SWORD_RAZOR, OBJECT_GI_SWORD_2, GID_SWORD_RAZOR, 0x38,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x39 */
    GET_ITEM(ITEM_SWORD_GILDED, OBJECT_GI_SWORD_3, GID_SWORD_GILDED, 0x39,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x3A */
    GET_ITEM(ITEM_BOMBCHUS_5, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x3A, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x3B */
    GET_ITEM(ITEM_SWORD_GREAT_FAIRY, OBJECT_GI_SWORD_4, GID_SWORD_GREAT_FAIRY, 0x3B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x3C */
    GET_ITEM(ITEM_KEY_SMALL, OBJECT_GI_KEY, GID_KEY_SMALL, 0x3C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x3D */
    GET_ITEM(ITEM_KEY_BOSS, OBJECT_GI_BOSSKEY, GID_KEY_BOSS, 0x3D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x3E */
    GET_ITEM(ITEM_DUNGEON_MAP, OBJECT_GI_MAP, GID_DUNGEON_MAP, 0x3E, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x3F */
    GET_ITEM(ITEM_COMPASS, OBJECT_GI_COMPASS, GID_COMPASS, 0x3F, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x40 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x40, 0, 0),
    /* 0x41 */
    GET_ITEM(ITEM_HOOKSHOT, OBJECT_GI_HOOKSHOT, GID_HOOKSHOT, 0x41, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x42 */
    GET_ITEM(ITEM_LENS, OBJECT_GI_GLASSES, GID_LENS, 0x42, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x43 */
    GET_ITEM(ITEM_PICTO_BOX, OBJECT_GI_CAMERA, GID_PICTO_BOX, 0x43, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x44 */ GET_ITEM(ITEM_PICTO_BOX, OBJECT_UNSET_0, GID_NONE, 0x44, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    /* 0x45 */
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x45, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x46 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x46, 0, 0),
    /* 0x47 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x47, 0, 0),
    /* 0x48 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x48, 0, 0),
    /* 0x49 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x49, 0, 0),
    /* 0x4A */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4A, 0, 0),
    /* 0x4B */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4B, 0, 0),
    /* 0x4C */
    GET_ITEM(ITEM_OCARINA, OBJECT_GI_OCARINA, GID_OCARINA, 0x4C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x4D */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4D, 0, 0),
    /* 0x4E */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4E, 0, 0),
    /* 0x4F */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4F, 0, 0),
    /* 0x50 */
    GET_ITEM(ITEM_BOMBERS_NOTEBOOK, OBJECT_GI_SCHEDULE, GID_BOMBERS_NOTEBOOK, 0x50, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x51 */
    GET_ITEM(ITEM_NONE, OBJECT_GI_MAP, GID_STONE_OF_AGONY, 0x51, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x52 */
    GET_ITEM(ITEM_SKULL_TOKEN, OBJECT_GI_SUTARU, GID_SKULL_TOKEN, 0x52, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    /* 0x53 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x53, 0, 0),
    /* 0x54 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x54, 0, 0),
    /* 0x55 */
    GET_ITEM(ITEM_REMAINS_ODOLWA, OBJECT_UNSET_0, GID_REMAINS_ODOLWA, 0x55, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x56 */
    GET_ITEM(ITEM_REMAINS_GOHT, OBJECT_UNSET_0, GID_REMAINS_GOHT, 0x56, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x57 */
    GET_ITEM(ITEM_REMAINS_GYORG, OBJECT_UNSET_0, GID_REMAINS_GYORG, 0x57, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x58 */
    GET_ITEM(ITEM_REMAINS_TWINMOLD, OBJECT_UNSET_0, GID_REMAINS_TWINMOLD, 0x58, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x59 */
    GET_ITEM(ITEM_LONGSHOT, OBJECT_GI_BOTTLE_RED, GID_57, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0),
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x5A */
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x5A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x5B */
    GET_ITEM(ITEM_POTION_RED, OBJECT_GI_LIQUID, GID_POTION_RED, 0x5B, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x5C */
    GET_ITEM(ITEM_POTION_GREEN, OBJECT_GI_LIQUID, GID_POTION_GREEN, 0x5C, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x5D */
    GET_ITEM(ITEM_POTION_BLUE, OBJECT_GI_LIQUID, GID_POTION_BLUE, 0x5D, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x5E */
    GET_ITEM(ITEM_FAIRY, OBJECT_GI_BOTTLE_04, GID_FAIRY, 0x5E, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x5F */
    GET_ITEM(ITEM_FAIRY, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x5F, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x60 */
    GET_ITEM(ITEM_MILK_BOTTLE, OBJECT_GI_MILK, GID_MILK, 0x60, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x61 */
    GET_ITEM(ITEM_MILK_HALF, OBJECT_GI_MILK, GID_MILK, 0x61, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x62 */ GET_ITEM(ITEM_FISH, OBJECT_GI_FISH, GID_FISH, 0x62, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x63 */ GET_ITEM(ITEM_BUG, OBJECT_GI_INSECT, GID_BUG, 0x63, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x64 */ GET_ITEM(ITEM_BLUE_FIRE, OBJECT_UNSET_0, GID_NONE, 0x64, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    /* 0x65 */
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x65, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x66 */
    GET_ITEM(ITEM_BIG_POE, OBJECT_GI_GHOST, GID_BIG_POE, 0x66, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x67 */ GET_ITEM(ITEM_SPRING_WATER, OBJECT_UNSET_0, GID_NONE, 0x67, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    /* 0x68 */ GET_ITEM(ITEM_HOT_SPRING_WATER, OBJECT_UNSET_0, GID_NONE, 0x68, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    /* 0x69 */
    GET_ITEM(ITEM_ZORA_EGG, OBJECT_GI_BOTTLE_15, GID_ZORA_EGG, 0x69, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x6A */
    GET_ITEM(ITEM_GOLD_DUST, OBJECT_GI_BOTTLE_16, GID_SEAHORSE, 0x6A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x6B */
    GET_ITEM(ITEM_MUSHROOM, OBJECT_GI_MAGICMUSHROOM, GID_MUSHROOM, 0x6B, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x6C */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x6C, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    /* 0x6D */
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x6D, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x6E */
    GET_ITEM(ITEM_SEAHORSE, OBJECT_GI_BOTTLE_16, GID_SEAHORSE, 0x6E, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x6F */
    GET_ITEM(ITEM_CHATEAU, OBJECT_GI_BOTTLE_21, GID_CHATEAU, 0x6F, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x70 */
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x70, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x71 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x71, 0, 0),
    /* 0x72 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x72, 0, 0),
    /* 0x73 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x73, 0, 0),
    /* 0x74 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x74, 0, 0),
    /* 0x75 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x75, 0, 0),
    /* 0x76 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x76, 0, 0),
    /* 0x77 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x77, 0, 0),
    /* 0x78 */
    GET_ITEM(ITEM_MASK_DEKU, OBJECT_GI_NUTSMASK, GID_MASK_DEKU, 0x78, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x79 */
    GET_ITEM(ITEM_MASK_GORON, OBJECT_GI_GOLONMASK, GID_MASK_GORON, 0x79,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x7A */
    GET_ITEM(ITEM_MASK_ZORA, OBJECT_GI_ZORAMASK, GID_MASK_ZORA, 0x7A, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x7B */
    GET_ITEM(ITEM_MASK_FIERCE_DEITY, OBJECT_GI_MASK03, GID_MASK_FIERCE_DEITY, 0x7B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x7C */
    GET_ITEM(ITEM_MASK_CAPTAIN, OBJECT_GI_MASK18, GID_MASK_CAPTAIN, 0x7C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x7D */
    GET_ITEM(ITEM_MASK_GIANT, OBJECT_GI_MASK23, GID_MASK_GIANT, 0x7D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x7E */
    GET_ITEM(ITEM_MASK_ALL_NIGHT, OBJECT_GI_MASK06, GID_MASK_ALL_NIGHT, 0x7E,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x7F */
    GET_ITEM(ITEM_MASK_BUNNY, OBJECT_GI_RABIT_MASK, GID_MASK_BUNNY, 0x7F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x80 */
    GET_ITEM(ITEM_MASK_KEATON, OBJECT_GI_KI_TAN_MASK, GID_MASK_KEATON, 0x80,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x81 */
    GET_ITEM(ITEM_MASK_GARO, OBJECT_GI_MASK09, GID_MASK_GARO, 0x81, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x82 */
    GET_ITEM(ITEM_MASK_ROMANI, OBJECT_GI_MASK10, GID_MASK_ROMANI, 0x82, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x83 */
    GET_ITEM(ITEM_MASK_CIRCUS_LEADER, OBJECT_GI_MASK11, GID_MASK_CIRCUS_LEADER, 0x83,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x84 */
    GET_ITEM(ITEM_MASK_POSTMAN, OBJECT_GI_MASK12, GID_MASK_POSTMAN, 0x84,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x85 */
    GET_ITEM(ITEM_MASK_COUPLE, OBJECT_GI_MASK13, GID_MASK_COUPLE, 0x85, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x86 */
    GET_ITEM(ITEM_MASK_GREAT_FAIRY, OBJECT_GI_MASK14, GID_MASK_GREAT_FAIRY, 0x86,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x87 */
    GET_ITEM(ITEM_MASK_GIBDO, OBJECT_GI_MASK15, GID_MASK_GIBDO, 0x87, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x88 */
    GET_ITEM(ITEM_MASK_DON_GERO, OBJECT_GI_MASK16, GID_MASK_DON_GERO, 0x88,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x89 */
    GET_ITEM(ITEM_MASK_KAMARO, OBJECT_GI_MASK17, GID_MASK_KAMARO, 0x89, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x8A */
    GET_ITEM(ITEM_MASK_TRUTH, OBJECT_GI_TRUTH_MASK, GID_MASK_TRUTH, 0x8A,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x8B */
    GET_ITEM(ITEM_MASK_STONE, OBJECT_GI_STONEMASK, GID_MASK_STONE, 0x8B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x8C */
    GET_ITEM(ITEM_MASK_BREMEN, OBJECT_GI_MASK20, GID_MASK_BREMEN, 0x8C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x8D */
    GET_ITEM(ITEM_MASK_BLAST, OBJECT_GI_MASK21, GID_MASK_BLAST, 0x8D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x8E */
    GET_ITEM(ITEM_MASK_SCENTS, OBJECT_GI_MASK22, GID_MASK_SCENTS, 0x8E, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x8F */
    GET_ITEM(ITEM_MASK_KAFEIS_MASK, OBJECT_GI_MASK05, GID_MASK_KAFEIS_MASK, 0x8F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x90 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x90, 0, 0),
    /* 0x91 */
    GET_ITEM(ITEM_CHATEAU_2, OBJECT_GI_BOTTLE_21, GID_CHATEAU, 0x91, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x92 */ GET_ITEM(ITEM_MILK, OBJECT_GI_MILK, GID_MILK, 0x92, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x93 */
    GET_ITEM(ITEM_GOLD_DUST_2, OBJECT_GI_GOLD_DUST, GID_GOLD_DUST, 0x93, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x94 */
    GET_ITEM(ITEM_HYLIAN_LOACH_2, OBJECT_GI_LOACH, GID_HYLIAN_LOACH, 0x94, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x95 */
    GET_ITEM(ITEM_SEAHORSE_CAUGHT, OBJECT_GI_SEAHORSE, GID_SEAHORSE_CAUGHT, 0x95, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x96 */
    GET_ITEM(ITEM_MOON_TEAR, OBJECT_GI_RESERVE00, GID_MOON_TEAR, 0x96, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x97 */
    GET_ITEM(ITEM_DEED_LAND, OBJECT_GI_RESERVE01, GID_DEED_LAND, 0x97, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x98 */
    GET_ITEM(ITEM_DEED_SWAMP, OBJECT_GI_RESERVE01, GID_DEED_SWAMP, 0x98, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x99 */
    GET_ITEM(ITEM_DEED_MOUNTAIN, OBJECT_GI_RESERVE01, GID_DEED_MOUNTAIN, 0x99, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x9A */
    GET_ITEM(ITEM_DEED_OCEAN, OBJECT_GI_RESERVE01, GID_DEED_OCEAN, 0x9A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0x9B */
    GET_ITEM(ITEM_SWORD_GREAT_FAIRY, OBJECT_GI_SWORD_4, GID_SWORD_GREAT_FAIRY, 0x9B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x9C */
    GET_ITEM(ITEM_SWORD_KOKIRI, OBJECT_GI_SWORD_1, GID_SWORD_KOKIRI, 0x9C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x9D */
    GET_ITEM(ITEM_SWORD_RAZOR, OBJECT_GI_SWORD_2, GID_SWORD_RAZOR, 0x9D,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x9E */
    GET_ITEM(ITEM_SWORD_GILDED, OBJECT_GI_SWORD_3, GID_SWORD_GILDED, 0x9E,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0x9F */
    GET_ITEM(ITEM_SHIELD_HERO, OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, 0x9F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    /* 0xA0 */
    GET_ITEM(ITEM_ROOM_KEY, OBJECT_GI_RESERVE_B_00, GID_ROOM_KEY, 0xA0, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xA1 */
    GET_ITEM(ITEM_LETTER_MAMA, OBJECT_GI_RESERVE_B_01, GID_LETTER_MAMA, 0xA1, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xA2 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA2, 0, 0),
    /* 0xA3 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA3, 0, 0),
    /* 0xA4 */
    GET_ITEM(ITEM_NONE, OBJECT_GI_KI_TAN_MASK, GID_MASK_KEATON, 0xA4, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xA5 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA5, 0, 0),
    /* 0xA6 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA6, 0, 0),
    /* 0xA7 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA7, 0, 0),
    /* 0xA8 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA8, 0, 0),
    /* 0xA9 */
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0xA9, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0xAA */
    GET_ITEM(ITEM_LETTER_TO_KAFEI, OBJECT_GI_RESERVE_C_00, GID_LETTER_TO_KAFEI, 0xAA,
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0xAB */
    GET_ITEM(ITEM_PENDANT_OF_MEMORIES, OBJECT_GI_RESERVE_C_01, GID_PENDANT_OF_MEMORIES, 0xAB,
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0xAC */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAC, 0, 0),
    /* 0xAD */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAD, 0, 0),
    /* 0xAE */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAE, 0, 0),
    /* 0xAF */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAF, 0, 0),
    /* 0xB0 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB0, 0, 0),
    /* 0xB1 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB1, 0, 0),
    /* 0xB2 */ GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB2, 0, 0),
    /* 0xB3 */
    GET_ITEM(ITEM_NONE, OBJECT_GI_MSSA, GID_MASK_SUN, 0xB3, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    /* 0xB4 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB4, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xB5 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB5, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xB6 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB6, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xB7 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB7, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xB8 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB8, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    /* 0xB9 */
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB9, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
};

void func_8082ECE0(Player* this) {
    GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

    this->unk_B2A = ABS_ALT(giEntry->unk_2);
}

LinkAnimationHeader* func_8082ED20(Player* this) {
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->actor.id != ACTOR_PLAYER)) {
        return &gameplay_keep_Linkanim_00E410;
    }
    if (this->transformation == PLAYER_FORM_GORON) {
        return &gameplay_keep_Linkanim_00E260;
    }
    if (this->currentMask == PLAYER_MASK_SCENTS) {
        return &gameplay_keep_Linkanim_00D0B0;
    }
    return D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType];
}

LinkAnimationHeader* sPlayerIdleAnimations[][2] = {
    { &gameplay_keep_Linkanim_00DF30, &gameplay_keep_Linkanim_00DEE8 },
    { &gameplay_keep_Linkanim_00DF40, &gameplay_keep_Linkanim_00DEF8 },
    { &gameplay_keep_Linkanim_00DF38, &gameplay_keep_Linkanim_00DEF0 },
    { &gameplay_keep_Linkanim_00DF38, &gameplay_keep_Linkanim_00DEF0 },
    { &gameplay_keep_Linkanim_00E100, &gameplay_keep_Linkanim_00E0C0 },
    { &gameplay_keep_Linkanim_00E100, &gameplay_keep_Linkanim_00E0C0 },
    { &gameplay_keep_Linkanim_00E100, &gameplay_keep_Linkanim_00E0C0 },
    { &gameplay_keep_Linkanim_00E0C8, &gameplay_keep_Linkanim_00E0A0 },
    { &gameplay_keep_Linkanim_00E0D0, &gameplay_keep_Linkanim_00E0A8 },
    { &gameplay_keep_Linkanim_00E0F0, &gameplay_keep_Linkanim_00E0F0 },
    { &gameplay_keep_Linkanim_00E0D8, &gameplay_keep_Linkanim_00E0B0 },
    { &gameplay_keep_Linkanim_00E0E0, &gameplay_keep_Linkanim_00E0B8 },
    { &gameplay_keep_Linkanim_00E0E8, &gameplay_keep_Linkanim_00E0E8 },
    { &gameplay_keep_Linkanim_00E0F8, &gameplay_keep_Linkanim_00E0F8 },
    { &gameplay_keep_Linkanim_00D0B0, &gameplay_keep_Linkanim_00D0B0 },
};

AnimSfxEntry D_8085C8C4[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 8, NA_SE_VO_LI_SNEEZE, STOP),
};
AnimSfxEntry D_8085C8C8[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 18, NA_SE_VO_LI_SWEAT, STOP),
};
AnimSfxEntry D_8085C8CC[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_BREATH_REST, STOP),
};
AnimSfxEntry D_8085C8D0[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 10, NA_SE_VO_LI_BREATH_REST, STOP),
};

AnimSfxEntry D_8085C8D4[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 44, NA_SE_PL_CALM_HIT, CONTINUE), ANIMSFX(ANIMSFX_TYPE_1, 48, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 52, NA_SE_PL_CALM_HIT, CONTINUE), ANIMSFX(ANIMSFX_TYPE_1, 56, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 60, NA_SE_PL_CALM_HIT, STOP),
};

AnimSfxEntry D_8085C8E8[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 25, 0, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 30, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 44, 0, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 48, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 52, 0, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 56, 0, STOP),
};

AnimSfxEntry D_8085C900[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 16, NA_SE_IT_SHIELD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 20, NA_SE_IT_SHIELD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 70, NA_SE_IT_SHIELD_SWING, STOP),
};

AnimSfxEntry D_8085C90C[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 10, NA_SE_IT_HAMMER_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 10, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 22, NA_SE_IT_SWORD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 22, NA_SE_VO_LI_SWORD_N, STOP),
};

AnimSfxEntry D_8085C91C[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 39, NA_SE_IT_SWORD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 39, NA_SE_VO_LI_SWORD_N, STOP),
};
AnimSfxEntry D_8085C924[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 20, NA_SE_VO_LI_RELAX, STOP),
};

AnimSfxEntry D_8085C928[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 4, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 12, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 30, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 61, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 68, NA_SE_VO_LI_POO_WAIT, STOP),
};

AnimSfxEntry* D_8085C93C[] = {
    D_8085C8C4, D_8085C8C8, D_8085C8CC, D_8085C8D0, D_8085C8D4, D_8085C8E8,
    D_8085C900, D_8085C90C, D_8085C91C, D_8085C924, D_8085C928, NULL,
};

// Used to index into D_8085C93C
u8 D_8085C96C[] = {
    0, 0, 1, 1, 2, 2, 2, 2, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 3, 3, 4, 4, 8, 8, 5, 5, 6, 6, 7, 7, 9, 9, 0xB, 0xB,
};

s32 func_8082ED94(Player* this) {
    LinkAnimationHeader** entry;
    s32 i;

    if ((this->skelAnime.animation != &gameplay_keep_Linkanim_00DD58) &&
        (this->skelAnime.animation != &gameplay_keep_Linkanim_00DD68) &&
        (((this->skelAnime.animation != func_8082ED20(this))) ||
         (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0B0))) {
        for (i = 0, entry = &sPlayerIdleAnimations[0][0]; i < ARRAY_COUNT_2D(sPlayerIdleAnimations); i++) {
            if (this->skelAnime.animation == *entry) {
                return i + 1;
            }
            entry++;
        }

        return 0;
    }

    return -1;
}

void func_8082EEA4(Player* this, s32 arg1) {
    u8 temp_v0 = D_8085C96C[arg1];

    if (temp_v0 != 0) {
        Player_PlayAnimSfx(this, D_8085C93C[temp_v0 - 1]);
    }
}

LinkAnimationHeader* func_8082EEE0(Player* this) {
    if (this->unk_B64 != 0) {
        return D_8085BE84[PLAYER_ANIMGROUP_3][this->modelAnimType];
    }
    return D_8085BE84[PLAYER_ANIMGROUP_2][this->modelAnimType];
}

s32 func_8082EF20(Player* this) {
    return func_8082ECCC(this) && this->unk_ACC != 0;
}

LinkAnimationHeader* func_8082EF54(Player* this) {
    if (func_8082EF20(this)) {
        return &gameplay_keep_Linkanim_00D490;
    }
    return D_8085BE84[PLAYER_ANIMGROUP_5][this->modelAnimType];
}

LinkAnimationHeader* func_8082EF9C(Player* this) {
    if (func_8082EF20(this)) {
        return &gameplay_keep_Linkanim_00D488;
    }
    return D_8085BE84[PLAYER_ANIMGROUP_4][this->modelAnimType];
}

LinkAnimationHeader* func_8082EFE4(Player* this) {
    if (func_800B7128(this)) {
        return &gameplay_keep_Linkanim_00D520;
    }
    return D_8085BE84[PLAYER_ANIMGROUP_22][this->modelAnimType];
}

void func_8082F02C(PlayState* play, struct_8082F02C_arg1* arg1, f32 arg2) {
    func_800FD59C(play, &arg1->unk_0, arg2);
    func_800FD5E0(play, &arg1->unk_3, arg2);
    func_800FD654(play, &arg1->unk_6, arg2);
    func_800FD698(play, arg1->unk_A, arg1->unk_C, arg2);
}

void func_8082F09C(Player* this) {
    this->cylinder.base.colType = 5;
    this->cylinder.base.atFlags = 0;
    this->cylinder.base.acFlags = 0x11;
    this->cylinder.base.ocFlags1 = 0x39;
    this->cylinder.info.elemType = 1;
    this->cylinder.info.toucher.dmgFlags = 0;
    this->cylinder.info.bumper.dmgFlags = 0xF7CFFFFF;
    this->cylinder.info.toucherFlags = 0;
    this->cylinder.dim.radius = 0xC;
}

void func_8082F0E4(Player* this, u32 dmgFlags, s32 damage, s32 radius) {
    this->cylinder.base.atFlags = 9;
    if (radius >= 0x1F) {
        this->cylinder.base.ocFlags1 = 0;
    } else {
        this->cylinder.base.ocFlags1 = 0x39;
    }

    this->cylinder.info.elemType = 2;
    this->cylinder.info.toucherFlags = 5;
    this->cylinder.dim.radius = radius;
    this->cylinder.info.toucher.dmgFlags = dmgFlags;
    this->cylinder.info.toucher.damage = damage;

    if (dmgFlags & 0x400) {
        this->cylinder.base.acFlags = 0;
    } else {
        this->cylinder.base.colType = 0xA;
        this->cylinder.info.bumper.dmgFlags = ~0x8300000;

        if (dmgFlags & 0x80000) {
            this->cylinder.base.acFlags = 0;
        } else {
            this->cylinder.base.acFlags = 0x11;
        }
    }
}

void func_8082F164(Player* this, u16 button) {
    if ((this->transformation == PLAYER_FORM_ZORA) && CHECK_BTN_ALL(D_80862B44->cur.button, button)) {
        this->stateFlags1 |= PLAYER_STATE1_10;
    }
}

struct_8082F02C_arg1 D_8085C98C = {
    { 0, 0, 0 }, { 0xFF, 0xFF, 0x9B }, { 0x14, 0x14, 0x32 }, 0x3AC, 0x1388,
};

void func_8082F1AC(PlayState* play, Player* this) {
    s32 sp4C = this->unk_B62;
    f32 temp;
    s16 sp46;
    s16 sp44;
    f32 sp40;
    f32 sp3C;
    s32 var_v0;

    if ((gSaveContext.save.playerData.magic != 0) && (this->stateFlags1 & PLAYER_STATE1_10)) {
        if (gSaveContext.unk_3F28 == 0) {
            // Magic_Consume
            func_80115DB4(play, 0, 5);
        }

        temp = 16.0f;
        if (gSaveContext.save.playerData.magic >= 16) {
            var_v0 = 0xFF;
        } else {
            var_v0 = (gSaveContext.save.playerData.magic / temp) * 255.0f;
        }
        Math_StepToS(&this->unk_B62, var_v0, 50);
    } else if ((Math_StepToS(&this->unk_B62, 0, 50) != 0) && (gSaveContext.unk_3F28 != 0)) {
        // Magic_Reset
        func_80115D5C(&play->state);
    }

    if ((this->unk_B62 != 0) || (sp4C != 0)) {
        f32 sp34;
        f32 new_var;

        sp46 = play->gameplayFrames * 7000;
        sp44 = play->gameplayFrames * 14000;
        func_8082F02C(play, &D_8085C98C, this->unk_B62 / 255.0f);

        sp34 = Math_SinS(sp44) * 40.0f;
        sp40 = Math_CosS(sp44) * 40.0f;
        sp3C = Math_SinS(sp46) * sp34;

        new_var = Math_CosS(sp46);
        Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x + sp40, this->actor.world.pos.y + sp3C,
                                  this->actor.world.pos.z + (new_var * sp34), 100, 200, 255, 600);

        func_800B8E58(this, NA_SE_PL_ZORA_SPARK_BARRIER - SFX_FLAG);
        func_800B648C(play, 1, 2, 100.0f, &this->actor.world.pos);
    }
}

void func_8082F43C(PlayState* play, Player* this, PlayerFuncAC4 arg2) {
    this->unk_AC4 = arg2;
    this->unk_ACE = 0;
    this->unk_AC8 = 0.0f;
    func_8082E00C(this);
}

#define GET_PLAYER_ANIM(group, type) ((LinkAnimationHeader**)D_8085BE84)[group * PLAYER_ANIMTYPE_MAX + type]

void func_8082F470(PlayState* play, Player* this, s32 arg2) {
    LinkAnimationHeader* current = this->skelAnime.animation;
    LinkAnimationHeader*(*iter)[PLAYER_ANIMTYPE_MAX] = (void*)&D_8085BE84[0][this->modelAnimType];
    s32 i;

    this->stateFlags1 &= ~(PLAYER_STATE1_8 | PLAYER_STATE1_1000000);

    for (i = 0; i < PLAYER_ANIMGROUP_MAX; i++) {
        if (current == **iter) {
            break;
        }
        iter++;
    }

    func_8082F8BC(play, this, arg2);
    if (i < PLAYER_ANIMGROUP_MAX) {
        this->skelAnime.animation = GET_PLAYER_ANIM(i, this->modelAnimType);
    }
}

// sItemActionParams
s8 D_8085C99C[] = {
    PLAYER_AP_OCARINA,                 // ITEM_OCARINA,
    PLAYER_AP_BOW,                     // ITEM_BOW,
    PLAYER_AP_BOW_FIRE,                // ITEM_ARROW_FIRE,
    PLAYER_AP_BOW_ICE,                 // ITEM_ARROW_ICE,
    PLAYER_AP_BOW_LIGHT,               // ITEM_ARROW_LIGHT,
    PLAYER_AP_PICTO_BOX,               // ITEM_OCARINA_FAIRY,
    PLAYER_AP_BOMB,                    // ITEM_BOMB,
    PLAYER_AP_BOMBCHU,                 // ITEM_BOMBCHU,
    PLAYER_AP_STICK,                   // ITEM_STICK,
    PLAYER_AP_NUT,                     // ITEM_NUT,
    PLAYER_AP_MAGIC_BEANS,             // ITEM_MAGIC_BEANS,
    PLAYER_AP_PICTO_BOX,               // ITEM_SLINGSHOT,
    PLAYER_AP_POWDER_KEG,              // ITEM_POWDER_KEG,
    PLAYER_AP_PICTO_BOX,               // ITEM_PICTO_BOX,
    PLAYER_AP_LENS,                    // ITEM_LENS,
    PLAYER_AP_HOOKSHOT,                // ITEM_HOOKSHOT,
    PLAYER_AP_SWORD_GREAT_FAIRY,       // ITEM_SWORD_GREAT_FAIRY,
    PLAYER_AP_PICTO_BOX,               // ITEM_LONGSHOT, // OoT Leftover
    PLAYER_AP_BOTTLE,                  // ITEM_BOTTLE,
    PLAYER_AP_BOTTLE_POTION_RED,       // ITEM_POTION_RED,
    PLAYER_AP_BOTTLE_POTION_GREEN,     // ITEM_POTION_GREEN,
    PLAYER_AP_BOTTLE_POTION_BLUE,      // ITEM_POTION_BLUE,
    PLAYER_AP_BOTTLE_FAIRY,            // ITEM_FAIRY,
    PLAYER_AP_BOTTLE_DEKU_PRINCESS,    // ITEM_DEKU_PRINCESS,
    PLAYER_AP_BOTTLE_MILK,             // ITEM_MILK_BOTTLE,
    PLAYER_AP_BOTTLE_MILK_HALF,        // ITEM_MILK_HALF,
    PLAYER_AP_BOTTLE_FISH,             // ITEM_FISH,
    PLAYER_AP_BOTTLE_BUG,              // ITEM_BUG,
    PLAYER_AP_BOTTLE_BUG,              // ITEM_BLUE_FIRE, // !
    PLAYER_AP_BOTTLE_POE,              // ITEM_POE,
    PLAYER_AP_BOTTLE_BIG_POE,          // ITEM_BIG_POE,
    PLAYER_AP_BOTTLE_SPRING_WATER,     // ITEM_SPRING_WATER,
    PLAYER_AP_BOTTLE_HOT_SPRING_WATER, // ITEM_HOT_SPRING_WATER,
    PLAYER_AP_BOTTLE_ZORA_EGG,         // ITEM_ZORA_EGG,
    PLAYER_AP_BOTTLE_GOLD_DUST,        // ITEM_GOLD_DUST,
    PLAYER_AP_BOTTLE_MUSHROOM,         // ITEM_MUSHROOM,
    PLAYER_AP_BOTTLE_SEAHORSE,         // ITEM_SEA_HORSE,
    PLAYER_AP_BOTTLE_CHATEAU,          // ITEM_CHATEAU,
    PLAYER_AP_BOTTLE_HYLIAN_LOACH,     // ITEM_HYLIAN_LOACH,
    PLAYER_AP_BOTTLE_POE,              // ITEM_OBABA_DRINK, // !
    PLAYER_AP_MOON_TEAR,               // ITEM_MOON_TEAR,
    PLAYER_AP_DEED_LAND,               // ITEM_DEED_LAND,
    PLAYER_AP_DEED_SWAMP,              // ITEM_DEED_SWAMP,
    PLAYER_AP_DEED_MOUNTAIN,           // ITEM_DEED_MOUNTAIN,
    PLAYER_AP_DEED_OCEAN,              // ITEM_DEED_OCEAN,
    PLAYER_AP_ROOM_KEY,                // ITEM_ROOM_KEY,
    PLAYER_AP_LETTER_MAMA,             // ITEM_LETTER_MAMA,
    PLAYER_AP_LETTER_TO_KAFEI,         // ITEM_LETTER_TO_KAFEI,
    PLAYER_AP_PENDANT_OF_MEMORIES,     // ITEM_PENDANT_MEMORIES,
    PLAYER_AP_38,                      // ITEM_TINGLE_MAP, // !
    PLAYER_AP_MASK_DEKU,               // ITEM_MASK_DEKU,
    PLAYER_AP_MASK_GORON,              // ITEM_MASK_GORON,
    PLAYER_AP_MASK_ZORA,               // ITEM_MASK_ZORA,
    PLAYER_AP_MASK_FIERCE_DEITY,       // ITEM_MASK_FIERCE_DEITY,
    PLAYER_AP_MASK_TRUTH,              // ITEM_MASK_TRUTH,
    PLAYER_AP_MASK_KAFEIS_MASK,        // ITEM_MASK_KAFEIS_MASK,
    PLAYER_AP_MASK_ALL_NIGHT,          // ITEM_MASK_ALL_NIGHT,
    PLAYER_AP_MASK_BUNNY,              // ITEM_MASK_BUNNY,
    PLAYER_AP_MASK_KEATON,             // ITEM_MASK_KEATON,
    PLAYER_AP_MASK_GARO,               // ITEM_MASK_GARO,
    PLAYER_AP_MASK_ROMANI,             // ITEM_MASK_ROMANI,
    PLAYER_AP_MASK_CIRCUS_LEADER,      // ITEM_MASK_CIRCUS_LEADER,
    PLAYER_AP_MASK_POSTMAN,            // ITEM_MASK_POSTMAN,
    PLAYER_AP_MASK_COUPLE,             // ITEM_MASK_COUPLE,
    PLAYER_AP_MASK_GREAT_FAIRY,        // ITEM_MASK_GREAT_FAIRY,
    PLAYER_AP_MASK_GIBDO,              // ITEM_MASK_GIBDO,
    PLAYER_AP_MASK_DON_GERO,           // ITEM_MASK_DON_GERO,
    PLAYER_AP_MASK_KAMARO,             // ITEM_MASK_KAMARO,
    PLAYER_AP_MASK_CAPTAIN,            // ITEM_MASK_CAPTAIN,
    PLAYER_AP_MASK_STONE,              // ITEM_MASK_STONE,
    PLAYER_AP_MASK_BREMEN,             // ITEM_MASK_BREMEN,
    PLAYER_AP_MASK_BLAST,              // ITEM_MASK_BLAST,
    PLAYER_AP_MASK_SCENTS,             // ITEM_MASK_SCENTS,
    PLAYER_AP_MASK_GIANT,              // ITEM_MASK_GIANT,
    PLAYER_AP_BOW_FIRE,                // ITEM_BOW_ARROW_FIRE,
    PLAYER_AP_BOW_ICE,                 // ITEM_BOW_ARROW_ICE,
    PLAYER_AP_BOW_LIGHT,               // ITEM_BOW_ARROW_LIGHT,
    PLAYER_AP_SWORD_KOKIRI,            // ITEM_SWORD_KOKIRI,
    PLAYER_AP_SWORD_RAZOR,             // ITEM_SWORD_RAZOR,
    PLAYER_AP_SWORD_GILDED,            // ITEM_SWORD_GILDED,
    PLAYER_AP_SWORD_GREAT_FAIRY,       // ITEM_SWORD_DEITY,
};

PlayerActionParam Player_ItemToActionParam(Player* this, ItemID item) {
    if (item >= ITEM_FD) {
        return PLAYER_AP_NONE;
    }
    if (item == ITEM_FC) {
        return PLAYER_AP_LAST_USED;
    }
    if (item == ITEM_FISHING_POLE) {
        return PLAYER_AP_FISHING_POLE;
    }
    if ((item == ITEM_SWORD_KOKIRI) && (this->transformation == PLAYER_FORM_ZORA)) {
        return PLAYER_AP_ZORA_FINS;
    }
    return D_8085C99C[item];
}

void func_8082F594(PlayState* play, Player* this) {
}

void func_8082F5A4(PlayState* play, Player* this) {
    this->unk_B28 = 0;
    this->unk_B08[1] = 1.0f;
}

void func_8082F5C0(PlayState* play, Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_8;

    if (this->itemActionParam == PLAYER_AP_NUT) {
        this->unk_B28 = -2;
    } else {
        this->unk_B28 = -1;
    }
    this->unk_ACC = 0;
}

PlayerFuncAC4 D_8085C9F0[PLAYER_AP_MAX] = {
    func_80848780, // PLAYER_AP_NONE
    func_80848780, // PLAYER_AP_LAST_USED
    func_80848780, // PLAYER_AP_FISHING_POLE
    func_808487B8, // PLAYER_AP_SWORD_KOKIRI
    func_808487B8, // PLAYER_AP_SWORD_RAZOR
    func_808487B8, // PLAYER_AP_SWORD_GILDED
    func_808487B8, // PLAYER_AP_SWORD_GREAT_FAIRY
    func_80848780, // PLAYER_AP_STICK
    func_80848780, // PLAYER_AP_ZORA_FINS
    func_80848B6C, // PLAYER_AP_BOW
    func_80848B6C, // PLAYER_AP_BOW_FIRE
    func_80848B6C, // PLAYER_AP_BOW_ICE
    func_80848B6C, // PLAYER_AP_BOW_LIGHT
    func_80848B6C, // PLAYER_AP_HOOKSHOT
    func_808490B4, // PLAYER_AP_BOMB
    func_808490B4, // PLAYER_AP_POWDER_KEG
    func_808490B4, // PLAYER_AP_BOMBCHU
    func_808491B4, // PLAYER_AP_11
    func_80848B6C, // PLAYER_AP_NUT
    func_80848780, // PLAYER_AP_PICTO_BOX
    func_80848780, // PLAYER_AP_OCARINA
    func_80848780, // PLAYER_AP_BOTTLE
    func_80848780, // PLAYER_AP_BOTTLE_FISH
    func_80848780, // PLAYER_AP_BOTTLE_SPRING_WATER
    func_80848780, // PLAYER_AP_BOTTLE_HOT_SPRING_WATER
    func_80848780, // PLAYER_AP_BOTTLE_ZORA_EGG
    func_80848780, // PLAYER_AP_BOTTLE_DEKU_PRINCESS
    func_80848780, // PLAYER_AP_BOTTLE_GOLD_DUST
    func_80848780, // PLAYER_AP_BOTTLE_1C
    func_80848780, // PLAYER_AP_BOTTLE_SEA_HORSE
    func_80848780, // PLAYER_AP_BOTTLE_MUSHROOM
    func_80848780, // PLAYER_AP_BOTTLE_HYLIAN_LOACH
    func_80848780, // PLAYER_AP_BOTTLE_BUG
    func_80848780, // PLAYER_AP_BOTTLE_POE
    func_80848780, // PLAYER_AP_BOTTLE_BIG_POE
    func_80848780, // PLAYER_AP_BOTTLE_POTION_RED
    func_80848780, // PLAYER_AP_BOTTLE_POTION_BLUE
    func_80848780, // PLAYER_AP_BOTTLE_POTION_GREEN
    func_80848780, // PLAYER_AP_BOTTLE_MILK
    func_80848780, // PLAYER_AP_BOTTLE_MILK_HALF
    func_80848780, // PLAYER_AP_BOTTLE_CHATEAU
    func_80848780, // PLAYER_AP_BOTTLE_FAIRY
    func_80848780, // PLAYER_AP_MOON_TEAR
    func_80848780, // PLAYER_AP_DEED_LAND
    func_80848780, // PLAYER_AP_ROOM_KEY
    func_80848780, // PLAYER_AP_LETTER_TO_KAFEI
    func_80848780, // PLAYER_AP_MAGIC_BEANS
    func_80848780, // PLAYER_AP_DEED_SWAMP
    func_80848780, // PLAYER_AP_DEED_MOUNTAIN
    func_80848780, // PLAYER_AP_DEED_OCEAN
    func_80848780, // PLAYER_AP_32
    func_80848780, // PLAYER_AP_LETTER_MAMA
    func_80848780, // PLAYER_AP_34
    func_80848780, // PLAYER_AP_35
    func_80848780, // PLAYER_AP_PENDANT_MEMORIES
    func_80848780, // PLAYER_AP_37
    func_80848780, // PLAYER_AP_38
    func_80848780, // PLAYER_AP_39
    func_80848780, // PLAYER_AP_MASK_TRUTH
    func_80848780, // PLAYER_AP_MASK_KAFEIS_MASK
    func_80848780, // PLAYER_AP_MASK_ALL_NIGHT
    func_80848780, // PLAYER_AP_MASK_BUNNY
    func_80848780, // PLAYER_AP_MASK_KEATON
    func_80848780, // PLAYER_AP_MASK_GARO
    func_80848780, // PLAYER_AP_MASK_ROMANI
    func_80848780, // PLAYER_AP_MASK_CIRCUS_LEADER
    func_80848780, // PLAYER_AP_MASK_POSTMAN
    func_80848780, // PLAYER_AP_MASK_COUPLE
    func_80848780, // PLAYER_AP_MASK_GREAT_FAIRY
    func_80848780, // PLAYER_AP_MASK_GIBDO
    func_80848780, // PLAYER_AP_MASK_DON_GERO
    func_80848780, // PLAYER_AP_MASK_KAMARO
    func_80848780, // PLAYER_AP_MASK_CAPTAIN
    func_80848780, // PLAYER_AP_MASK_STONE
    func_80848780, // PLAYER_AP_MASK_BREMEN
    func_80848780, // PLAYER_AP_MASK_BLAST
    func_80848780, // PLAYER_AP_MASK_SCENTS
    func_80848780, // PLAYER_AP_MASK_GIANT
    func_80848780, // PLAYER_AP_MASK_FIERCE_DEITY
    func_80848780, // PLAYER_AP_MASK_GORON
    func_80848780, // PLAYER_AP_MASK_ZORA
    func_80848780, // PLAYER_AP_MASK_DEKU
    func_80848780, // PLAYER_AP_LENS
};

void (*D_8085CB3C[PLAYER_AP_MAX])(PlayState*, Player*) = {
    func_8082F594, // PLAYER_AP_NONE
    func_8082F594, // PLAYER_AP_LAST_USED
    func_8082F594, // PLAYER_AP_FISHING_POLE
    func_8082F594, // PLAYER_AP_SWORD_KOKIRI
    func_8082F594, // PLAYER_AP_SWORD_RAZOR
    func_8082F594, // PLAYER_AP_SWORD_GILDED
    func_8082F594, // PLAYER_AP_SWORD_GREAT_FAIRY
    func_8082F5A4, // PLAYER_AP_STICK
    func_8082F8A0, // PLAYER_AP_ZORA_FINS
    func_8082F5C0, // PLAYER_AP_BOW
    func_8082F5C0, // PLAYER_AP_BOW_FIRE
    func_8082F5C0, // PLAYER_AP_BOW_ICE
    func_8082F5C0, // PLAYER_AP_BOW_LIGHT
    func_8082F7F4, // PLAYER_AP_HOOKSHOT
    func_8082F62C, // PLAYER_AP_BOMB
    func_8082F62C, // PLAYER_AP_POWDER_KEG
    func_8082F62C, // PLAYER_AP_BOMBCHU
    func_8082F8A0, // PLAYER_AP_11
    func_8082F5C0, // PLAYER_AP_NUT
    func_8082F594, // PLAYER_AP_PICTO_BOX
    func_8082F594, // PLAYER_AP_OCARINA
    func_8082F594, // PLAYER_AP_BOTTLE
    func_8082F594, // PLAYER_AP_BOTTLE_FISH
    func_8082F594, // PLAYER_AP_BOTTLE_SPRING_WATER
    func_8082F594, // PLAYER_AP_BOTTLE_HOT_SPRING_WATER
    func_8082F594, // PLAYER_AP_BOTTLE_ZORA_EGG
    func_8082F594, // PLAYER_AP_BOTTLE_DEKU_PRINCESS
    func_8082F594, // PLAYER_AP_BOTTLE_GOLD_DUST
    func_8082F594, // PLAYER_AP_BOTTLE_1C
    func_8082F594, // PLAYER_AP_BOTTLE_SEA_HORSE
    func_8082F594, // PLAYER_AP_BOTTLE_MUSHROOM
    func_8082F594, // PLAYER_AP_BOTTLE_HYLIAN_LOACH
    func_8082F594, // PLAYER_AP_BOTTLE_BUG
    func_8082F594, // PLAYER_AP_BOTTLE_POE
    func_8082F594, // PLAYER_AP_BOTTLE_BIG_POE
    func_8082F594, // PLAYER_AP_BOTTLE_POTION_RED
    func_8082F594, // PLAYER_AP_BOTTLE_POTION_BLUE
    func_8082F594, // PLAYER_AP_BOTTLE_POTION_GREEN
    func_8082F594, // PLAYER_AP_BOTTLE_MILK
    func_8082F594, // PLAYER_AP_BOTTLE_MILK_HALF
    func_8082F594, // PLAYER_AP_BOTTLE_CHATEAU
    func_8082F594, // PLAYER_AP_BOTTLE_FAIRY
    func_8082F594, // PLAYER_AP_MOON_TEAR
    func_8082F594, // PLAYER_AP_DEED_LAND
    func_8082F594, // PLAYER_AP_ROOM_KEY
    func_8082F594, // PLAYER_AP_LETTER_TO_KAFEI
    func_8082F594, // PLAYER_AP_MAGIC_BEANS
    func_8082F594, // PLAYER_AP_DEED_SWAMP
    func_8082F594, // PLAYER_AP_DEED_MOUNTAIN
    func_8082F594, // PLAYER_AP_DEED_OCEAN
    func_8082F594, // PLAYER_AP_32
    func_8082F594, // PLAYER_AP_LETTER_MAMA
    func_8082F594, // PLAYER_AP_34
    func_8082F594, // PLAYER_AP_35
    func_8082F594, // PLAYER_AP_PENDANT_MEMORIES
    func_8082F594, // PLAYER_AP_37
    func_8082F594, // PLAYER_AP_38
    func_8082F594, // PLAYER_AP_39
    func_8082F594, // PLAYER_AP_MASK_TRUTH
    func_8082F594, // PLAYER_AP_MASK_KAFEIS_MASK
    func_8082F594, // PLAYER_AP_MASK_ALL_NIGHT
    func_8082F594, // PLAYER_AP_MASK_BUNNY
    func_8082F594, // PLAYER_AP_MASK_KEATON
    func_8082F594, // PLAYER_AP_MASK_GARO
    func_8082F594, // PLAYER_AP_MASK_ROMANI
    func_8082F594, // PLAYER_AP_MASK_CIRCUS_LEADER
    func_8082F594, // PLAYER_AP_MASK_POSTMAN
    func_8082F594, // PLAYER_AP_MASK_COUPLE
    func_8082F594, // PLAYER_AP_MASK_GREAT_FAIRY
    func_8082F594, // PLAYER_AP_MASK_GIBDO
    func_8082F594, // PLAYER_AP_MASK_DON_GERO
    func_8082F594, // PLAYER_AP_MASK_KAMARO
    func_8082F594, // PLAYER_AP_MASK_CAPTAIN
    func_8082F594, // PLAYER_AP_MASK_STONE
    func_8082F594, // PLAYER_AP_MASK_BREMEN
    func_8082F594, // PLAYER_AP_MASK_BLAST
    func_8082F594, // PLAYER_AP_MASK_SCENTS
    func_8082F594, // PLAYER_AP_MASK_GIANT
    func_8082F594, // PLAYER_AP_MASK_FIERCE_DEITY
    func_8082F594, // PLAYER_AP_MASK_GORON
    func_8082F594, // PLAYER_AP_MASK_ZORA
    func_8082F594, // PLAYER_AP_MASK_DEKU
    func_8082F594, // PLAYER_AP_LENS
};

void func_8082F5FC(Player* this, Actor* actor) {
    this->heldActor = actor;
    this->interactRangeActor = actor;
    this->getItemId = GI_NONE;
    this->leftHandWorld.rot.y = actor->shape.rot.y - this->actor.shape.rot.y;
    this->stateFlags1 |= PLAYER_STATE1_800;
}

struct_8085CC88 D_8085CC88[] = {
    { &gameplay_keep_Linkanim_00DC70, 12 }, { &gameplay_keep_Linkanim_00DD90, 6 },
    { &gameplay_keep_Linkanim_00D9B8, 8 },  { &gameplay_keep_Linkanim_00DDA0, 8 },
    { &gameplay_keep_Linkanim_00D820, 8 },  { &gameplay_keep_Linkanim_00DC50, 10 },
    { &gameplay_keep_Linkanim_00D9A8, 7 },  { &gameplay_keep_Linkanim_00D9B0, 11 },
    { &gameplay_keep_Linkanim_00DC70, 12 }, { &gameplay_keep_Linkanim_00DD88, 4 },
    { &gameplay_keep_Linkanim_00DD48, 4 },  { &gameplay_keep_Linkanim_00DC58, 4 },
    { &gameplay_keep_Linkanim_00D3E0, 5 },  { &gameplay_keep_Linkanim_00DC68, 13 },
    { &gameplay_keep_Linkanim_00E350, 4 },
};

s8 D_8085CD00[PLAYER_ANIMTYPE_MAX][PLAYER_ANIMTYPE_MAX] = {
    { 8, -5, -3, -6, 8, 0xB }, { 5, 0, -1, 4, 5, 9 },     { 3, 1, 0, 2, 3, 9 },
    { 6, -4, -2, 7, 6, 0xA },  { 8, -5, -3, -6, 8, 0xB }, { 8, -5, -3, -6, 8, 0xB },
};

struct_8085CD24 D_8085CD24[] = {
    { ITEM_BOMB, ACTOR_EN_BOM },        // PLAYER_AP_BOMB
    { ITEM_POWDER_KEG, ACTOR_EN_BOM },  // PLAYER_AP_POWDER_KEG
    { ITEM_BOMBCHU, ACTOR_EN_BOM_CHU }, // PLAYER_AP_BOMBCHU
};

void func_8082F62C(PlayState* play, Player* this) {
    s32 explosiveType;
    struct_8085CD24* explosiveInfo;
    Actor* explosiveActor;

    if (this->stateFlags1 & PLAYER_STATE1_800) {
        func_8082DE14(play, this);
        return;
    }

    explosiveType = Player_GetExplosiveHeld(this);
    explosiveInfo = &D_8085CD24[explosiveType];
    if ((explosiveType == 1) && (gSaveContext.powderKegTimer == 0)) {
        gSaveContext.powderKegTimer = 0xC8;
    }

    explosiveActor = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, explosiveInfo->actorId,
                                        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                        explosiveType == 1 ? 1 : 0, this->actor.shape.rot.y, 0, 0);
    if (explosiveActor != NULL) {
        if ((explosiveType == 0) && (play->unk_1887E != 0)) {
            play->unk_1887E--;
            if (play->unk_1887E == 0) {
                play->unk_1887E = -1;
            }
        } else if ((explosiveType == 2) && (play->unk_1887D != 0)) {
            play->unk_1887D--;
            if (play->unk_1887D == 0) {
                play->unk_1887D = -1;
            }
        } else {
            Inventory_ChangeAmmo(explosiveInfo->itemId, -1);
        }
        func_8082F5FC(this, explosiveActor);
    } else if (explosiveType == 1) {
        gSaveContext.powderKegTimer = 0;
    }
}

void func_8082F7F4(PlayState* play, Player* this) {
    ArmsHook* armsHook;

    this->stateFlags1 |= 8;
    this->unk_B28 = -3;
    this->unk_B48 = 0.0f;

    this->heldActor =
        Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_ARMS_HOOK, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, 0);
    if (this->heldActor == NULL) {
        func_80831990(play, this, ITEM_NONE);
        return;
    }

    armsHook = (ArmsHook*)this->heldActor;
    armsHook->actor.objBankIndex = this->actor.objBankIndex;
    armsHook->unk_208 = this->transformation;
}

void func_8082F8A0(PlayState* play, Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_1000000;
}

void func_8082F8BC(PlayState* play, Player* this, PlayerActionParam actionParam) {
    this->heldItemActionParam = this->itemActionParam = actionParam;
    this->modelGroup = this->nextModelGroup;
    this->stateFlags1 &= ~(PLAYER_STATE1_1000000 | PLAYER_STATE1_8);
    this->unk_B08[0] = 0.0f;
    this->unk_B08[1] = 0.0f;
    this->unk_B28 = 0;
    D_8085CB3C[actionParam](play, this);
    Player_SetModelGroup(this, this->modelGroup);
}

// AttackAnimInfo sMeleeAttackAnimInfo
struct_8085CD30 D_8085CD30[PLAYER_MWA_MAX] = {
    // PLAYER_MWA_FORWARD_SLASH_1H
    { &gameplay_keep_Linkanim_00D868, &gameplay_keep_Linkanim_00D878, &gameplay_keep_Linkanim_00D870, 1, 4 },
    // PLAYER_MWA_FORWARD_SLASH_2H
    { &gameplay_keep_Linkanim_00D6E0, &gameplay_keep_Linkanim_00D6E8, &gameplay_keep_Linkanim_00D398, 1, 4 },
    // PLAYER_MWA_FORWARD_COMBO_1H
    { &gameplay_keep_Linkanim_00D880, &gameplay_keep_Linkanim_00D888, &gameplay_keep_Linkanim_00D428, 0, 5 },
    // PLAYER_MWA_FORWARD_COMBO_2H
    { &gameplay_keep_Linkanim_00D6F0, &gameplay_keep_Linkanim_00D6F8, &gameplay_keep_Linkanim_00D3A0, 1, 7 },
    // PLAYER_MWA_RIGHT_SLASH_1H
    { &gameplay_keep_Linkanim_00D788, &gameplay_keep_Linkanim_00D790, &gameplay_keep_Linkanim_00D3C0, 1, 4 },
    // PLAYER_MWA_RIGHT_SLASH_2H
    { &gameplay_keep_Linkanim_00D6A0, &gameplay_keep_Linkanim_00D6A8, &gameplay_keep_Linkanim_00D378, 0, 5 },
    // PLAYER_MWA_RIGHT_COMBO_1H
    { &gameplay_keep_Linkanim_00D798, &gameplay_keep_Linkanim_00D7A0, &gameplay_keep_Linkanim_00D3C8, 2, 8 },
    // PLAYER_MWA_RIGHT_COMBO_2H
    { &gameplay_keep_Linkanim_00D6B0, &gameplay_keep_Linkanim_00D6B8, &gameplay_keep_Linkanim_00D380, 3, 8 },
    // PLAYER_MWA_LEFT_SLASH_1H
    { &gameplay_keep_Linkanim_00D7C0, &gameplay_keep_Linkanim_00D7C8, &gameplay_keep_Linkanim_00D3D0, 0, 4 },
    // PLAYER_MWA_LEFT_SLASH_2H
    { &gameplay_keep_Linkanim_00D6C0, &gameplay_keep_Linkanim_00D6C8, &gameplay_keep_Linkanim_00D388, 0, 5 },
    // PLAYER_MWA_LEFT_COMBO_1H
    { &gameplay_keep_Linkanim_00D7D0, &gameplay_keep_Linkanim_00D7D8, &gameplay_keep_Linkanim_00D3D8, 0, 6 },
    // PLAYER_MWA_LEFT_COMBO_2H
    { &gameplay_keep_Linkanim_00D6D0, &gameplay_keep_Linkanim_00D6D8, &gameplay_keep_Linkanim_00D390, 1, 5 },
    // PLAYER_MWA_STAB_1H
    { &gameplay_keep_Linkanim_00D890, &gameplay_keep_Linkanim_00D898, &gameplay_keep_Linkanim_00D430, 0, 3 },
    // PLAYER_MWA_STAB_2H
    { &gameplay_keep_Linkanim_00D700, &gameplay_keep_Linkanim_00D708, &gameplay_keep_Linkanim_00D3A8, 0, 3 },
    // PLAYER_MWA_STAB_COMBO_1H
    { &gameplay_keep_Linkanim_00D8A0, &gameplay_keep_Linkanim_00D8A8, &gameplay_keep_Linkanim_00D438, 1, 9 },
    // PLAYER_MWA_STAB_COMBO_2H
    { &gameplay_keep_Linkanim_00D710, &gameplay_keep_Linkanim_00D718, &gameplay_keep_Linkanim_00D3B0, 1, 8 },
    // PLAYER_MWA_FLIPSLASH_START
    { &gameplay_keep_Linkanim_00D850, &gameplay_keep_Linkanim_00D840, &gameplay_keep_Linkanim_00D840, 7, 99 },
    // PLAYER_MWA_JUMPSLASH_START
    { &gameplay_keep_Linkanim_00D720, &gameplay_keep_Linkanim_00D730, &gameplay_keep_Linkanim_00D730, 7, 99 },
    // PLAYER_MWA_ZORA_JUMPKICK_START
    { &gameplay_keep_Linkanim_00E3F0, &gameplay_keep_Linkanim_00E3F8, &gameplay_keep_Linkanim_00E3F8, 8, 99 },
    // PLAYER_MWA_FLIPSLASH_FINISH
    { &gameplay_keep_Linkanim_00D840, &gameplay_keep_Linkanim_00D848, &gameplay_keep_Linkanim_00D848, 1, 2 },
    // PLAYER_MWA_JUMPSLASH_FINISH
    { &gameplay_keep_Linkanim_00D730, &gameplay_keep_Linkanim_00D728, &gameplay_keep_Linkanim_00D728, 1, 2 },
    // PLAYER_MWA_ZORA_JUMPKICK_FINISH
    { &gameplay_keep_Linkanim_00E3F8, &gameplay_keep_Linkanim_00E410, &gameplay_keep_Linkanim_00DF18, 1, 2 },
    // PLAYER_MWA_BACKSLASH_RIGHT
    { &gameplay_keep_Linkanim_00D950, &gameplay_keep_Linkanim_00D958, &gameplay_keep_Linkanim_00D958, 1, 5 },
    // PLAYER_MWA_BACKSLASH_LEFT
    { &gameplay_keep_Linkanim_00D940, &gameplay_keep_Linkanim_00D948, &gameplay_keep_Linkanim_00D948, 1, 4 },
    // PLAYER_MWA_GORON_PUNCH_LEFT
    { &gameplay_keep_Linkanim_00E218, &gameplay_keep_Linkanim_00E228, &gameplay_keep_Linkanim_00E220, 6, 8 },
    // PLAYER_MWA_GORON_PUNCH_RIGHT
    { &gameplay_keep_Linkanim_00E230, &gameplay_keep_Linkanim_00E240, &gameplay_keep_Linkanim_00E238, 12, 18 },
    // PLAYER_MWA_GORON_PUNCH_BUTT
    { &gameplay_keep_Linkanim_00E248, &gameplay_keep_Linkanim_00E258, &gameplay_keep_Linkanim_00E250, 8, 14 },
    // PLAYER_MWA_ZORA_PUNCH_LEFT
    { &gameplay_keep_Linkanim_00E308, &gameplay_keep_Linkanim_00E318, &gameplay_keep_Linkanim_00E310, 2, 5 },
    // PLAYER_MWA_ZORA_PUNCH_COMBO
    { &gameplay_keep_Linkanim_00E320, &gameplay_keep_Linkanim_00E330, &gameplay_keep_Linkanim_00E328, 3, 8 },
    // PLAYER_MWA_ZORA_PUNCH_KICK
    { &gameplay_keep_Linkanim_00E338, &gameplay_keep_Linkanim_00E348, &gameplay_keep_Linkanim_00E340, 3, 10 },
    // PLAYER_MWA_SPIN_ATTACK_1H
    { &gameplay_keep_Linkanim_00D908, &gameplay_keep_Linkanim_00D910, &gameplay_keep_Linkanim_00D440, 0, 12 },
    // PLAYER_MWA_SPIN_ATTACK_2H
    { &gameplay_keep_Linkanim_00D760, &gameplay_keep_Linkanim_00D768, &gameplay_keep_Linkanim_00D3B8, 0, 15 },
    // PLAYER_MWA_BIG_SPIN_1H
    { &gameplay_keep_Linkanim_00D7E0, &gameplay_keep_Linkanim_00D7E8, &gameplay_keep_Linkanim_00D440, 0, 16 },
    // PLAYER_MWA_BIG_SPIN_2H
    { &gameplay_keep_Linkanim_00D7E0, &gameplay_keep_Linkanim_00D7E8, &gameplay_keep_Linkanim_00D3B8, 0, 16 },
};

LinkAnimationHeader* D_8085CF50[] = {
    &gameplay_keep_Linkanim_00D8C8,
    &gameplay_keep_Linkanim_00D740,
};
LinkAnimationHeader* D_8085CF58[] = {
    &gameplay_keep_Linkanim_00D8C0,
    &gameplay_keep_Linkanim_00D740,
};
LinkAnimationHeader* D_8085CF60[] = {
    &gameplay_keep_Linkanim_00D8D0,
    &gameplay_keep_Linkanim_00D748,
};
LinkAnimationHeader* D_8085CF68[] = {
    &gameplay_keep_Linkanim_00D8D8,
    &gameplay_keep_Linkanim_00D750,
};
LinkAnimationHeader* D_8085CF70[] = {
    &gameplay_keep_Linkanim_00D8E0,
    &gameplay_keep_Linkanim_00D758,
};
LinkAnimationHeader* D_8085CF78[] = {
    &gameplay_keep_Linkanim_00D8B8,
    &gameplay_keep_Linkanim_00D738,
};

u8 D_8085CF80[] = {
    PLAYER_MWA_SPIN_ATTACK_1H,
    PLAYER_MWA_SPIN_ATTACK_2H,
};
u8 D_8085CF84[] = {
    PLAYER_MWA_BIG_SPIN_1H,
    PLAYER_MWA_BIG_SPIN_2H,
};

// sBlureColors
BlureColors D_8085CF88[] = {
    { { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 } },
    { { 165, 185, 255, 185 }, { 205, 225, 255, 50 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 } },
};

// Player_OverrideBlureColors
void func_8082F938(PlayState* play, Player* this, s32 colorType, s32 elemDuration) {
    EffectBlure* blure0 = Effect_GetByIndex(this->meleeWeaponEffectIndex[0]);
    EffectBlure* blure1 = Effect_GetByIndex(this->meleeWeaponEffectIndex[1]);
    s32 i;

    for (i = 0; i < 4; i++) {
        blure0->p1StartColor[i] = D_8085CF88[colorType].p1StartColor[i];
        blure0->p2StartColor[i] = D_8085CF88[colorType].p2StartColor[i];
        blure0->p1EndColor[i] = D_8085CF88[colorType].p1EndColor[i];
        blure0->p2EndColor[i] = D_8085CF88[colorType].p2EndColor[i];
        blure1->p1StartColor[i] = D_8085CF88[colorType].p1StartColor[i];
        blure1->p2StartColor[i] = D_8085CF88[colorType].p2StartColor[i];
        blure1->p1EndColor[i] = D_8085CF88[colorType].p1EndColor[i];
        blure1->p2EndColor[i] = D_8085CF88[colorType].p2EndColor[i];
    }

    if (this->transformation == PLAYER_FORM_DEKU) {
        elemDuration = 8;
    }
    blure0->elemDuration = elemDuration;
    blure1->elemDuration = elemDuration;
}

void func_8082FA5C(PlayState* play, Player* this, s32 meleeWeaponState) {
    u16 var_a2;
    u16 var_a1;

    if (this->meleeWeaponState == 0) {
        var_a2 = NA_SE_VO_LI_SWORD_N;
        if (this->transformation == PLAYER_FORM_GORON) {
            var_a1 = NA_SE_IT_GORON_PUNCH_SWING;
        } else {
            var_a1 = 0;
            if (this->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) {
                var_a2 = NA_SE_VO_LI_SWORD_L;
            } else if (this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_KICK) {
                var_a1 = NA_SE_IT_GORON_PUNCH_SWING;
            } else {
                var_a1 = NA_SE_IT_SWORD_SWING_HARD;
                if (this->unk_ADD >= 3) {
                    var_a2 = NA_SE_VO_LI_SWORD_L;
                } else {
                    var_a1 = (this->itemActionParam == PLAYER_AP_SWORD_GREAT_FAIRY) ? NA_SE_IT_HAMMER_SWING
                                                                                    : NA_SE_IT_SWORD_SWING;
                }
            }
        }

        if (var_a1 != 0) {
            func_8082E1F0(this, var_a1);
        }

        if (!((this->meleeWeaponAnimation >= PLAYER_MWA_FLIPSLASH_START) &&
              (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_JUMPKICK_FINISH))) {
            func_8082DF8C(this, var_a2);
        }

        func_8082F938(play, this, 0, 4);
    }

    this->meleeWeaponState = meleeWeaponState;
}

s32 func_8082FB68(Player* this) {
    if ((this->targetedActor != NULL) && CHECK_FLAG_ALL(this->targetedActor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_4)) {
        this->stateFlags3 |= PLAYER_STATE3_80000000;
        return true;
    }

    if (this->stateFlags3 & PLAYER_STATE3_80000000) {
        this->stateFlags3 &= ~PLAYER_STATE3_80000000;
        if (this->linearVelocity == 0.0f) {
            this->currentYaw = this->actor.shape.rot.y;
        }
    }

    return false;
}

s32 func_8082FBE8(Player* this) {
    return func_80123420(this) || func_80123434(this);
}

s32 func_8082FC24(Player* this) {
    return func_8082FB68(this) || func_80123434(this);
}

void func_8082FC60(Player* this) {
    this->unk_B44 = 0.0f;
    this->unk_B40 = 0.0f;
}

s32 func_8082FC78(Player* this, ItemID item) {
    if ((item < ITEM_FD) && (Player_ItemToActionParam(this, item) == this->heldItemActionParam)) {
        return true;
    }
    return false;
}

s32 func_8082FCC4(Player* this, ItemID item, PlayerActionParam actionParam) {
    if ((item < ITEM_FD) && (Player_ItemToActionParam(this, item) == actionParam)) {
        return true;
    }
    return false;
}

s32 func_8082FD0C(Player* this, PlayerActionParam actionParam) {
    s32 btn;

    for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
        if (func_8082FCC4(this, GET_CUR_FORM_BTN_ITEM(btn), actionParam)) {
            return btn;
        }
    }
    return -1;
}

u16 D_8085CFA8[] = {
    BTN_B,
    BTN_CLEFT,
    BTN_CDOWN,
    BTN_CRIGHT,
};

s32 func_8082FDC4(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8085CFA8); i++) {
        if (CHECK_BTN_ALL(D_80862B44->press.button, D_8085CFA8[i])) {
            break;
        }
    }

    return i;
}

void func_8082FE0C(Player* this, PlayState* play) {
    if (((this->stateFlags1 & (PLAYER_STATE1_800 | PLAYER_STATE1_20000000)) ||
         (this->stateFlags2 & PLAYER_STATE2_2000000) || (this->stateFlags3 & PLAYER_STATE3_20000000) ||
         func_801240DC(this))) {
        return;
    }

    if (this->transformation == PLAYER_FORM_HUMAN) {
        if (this->currentMask != PLAYER_MASK_NONE) {
            PlayerActionParam maskActionParam = this->currentMask + PLAYER_AP_MASK_TRUTH - 1;
            s32 btn;

            btn = func_8082FD0C(this, maskActionParam);

            if (btn < 0) {
                s32 maskIdMinusOne =
                    Player_ItemToActionParam(this, GET_CUR_FORM_BTN_ITEM(this->unk_154)) - PLAYER_AP_39 - 1;

                if ((maskIdMinusOne < PLAYER_MASK_TRUTH - 1) || (maskIdMinusOne >= PLAYER_MASK_MAX - 1)) {
                    maskIdMinusOne = this->currentMask - 1;
                }
                func_80831990(play, this, Player_MaskIdToItemId(maskIdMinusOne));
                return;
            } else {
                if ((this->currentMask == PLAYER_MASK_GIANT) && (gSaveContext.save.playerData.magic == 0)) {
                    func_80838A20(play, this);
                }

                this->unk_154 = btn;
            }
        }
    }

    if (((this->actor.id == ACTOR_PLAYER) && (this->heldItemActionParam >= PLAYER_AP_FISHING_POLE)) &&
        !(((func_80124148(this) == 0) || (gSaveContext.jinxTimer == 0)) &&
          (func_8082FC78(this, (IREG(1) != 0) ? ITEM_FISHING_POLE : Inventory_GetBtnBItem(play)) ||
           func_8082FC78(this, C_BTN_ITEM(EQUIP_SLOT_C_LEFT)) || func_8082FC78(this, C_BTN_ITEM(EQUIP_SLOT_C_DOWN)) ||
           func_8082FC78(this, C_BTN_ITEM(EQUIP_SLOT_C_RIGHT))))) {
        func_80831990(play, this, ITEM_NONE);
    } else {
        s32 pad;
        ItemID item;
        s32 i = func_8082FDC4();

        i = ((i >= 4) && (this->transformation == PLAYER_FORM_FIERCE_DEITY) &&
             (this->itemActionParam != PLAYER_AP_SWORD_GREAT_FAIRY))
                ? 0
                : i;

        item = func_8012364C(play, this, i);
        if (item >= ITEM_FD) {
            for (i = 0; i < ARRAY_COUNT(D_8085CFA8); i++) {
                if (CHECK_BTN_ALL(D_80862B44->cur.button, D_8085CFA8[i])) {
                    break;
                }
            }

            item = func_8012364C(play, this, i);
            if ((item < ITEM_FD) && (Player_ItemToActionParam(this, item) == this->itemActionParam)) {
                D_80862B4C = 1;
            }
        } else if (item == ITEM_F0) {
            if (this->unk_B60 == 0) {
                EnBom* temp_v0_7 = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.focus.pos.x,
                                                       this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 0);
                if (temp_v0_7 != NULL) {
                    temp_v0_7->timer = 0;
                    this->unk_B60 = 0x136;
                }
            }
        } else if (item == ITEM_F1) {
            func_80839978(play, this);
        } else if (item == ITEM_F2) {
            func_80839A10(play, this);
        } else if ((func_80124110(this, Player_ItemToActionParam(this, item)) != 0) && (gSaveContext.jinxTimer != 0)) {
            if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
                Message_StartTextbox(play, 0xF7, NULL);
            }
        } else {
            this->heldItemButton = i;
            func_80831990(play, this, item);
        }
    }
}

void func_808302CC(Player* this, PlayState* play) {
    LinkAnimationHeader* anim;
    s32 pad[3];
    u8 nextModelAnimType;
    s32 var_v1;
    s8 actionParam;
    s32 pad3;
    f32 startFrame;
    f32 endFrame;
    f32 frameSpeed;

    actionParam = Player_ItemToActionParam(this, this->heldItemId);
    func_8082F43C(play, this, func_80848808);

    nextModelAnimType = gPlayerModelTypes[this->nextModelGroup].modelAnimType;
    var_v1 = D_8085CD00[gPlayerModelTypes[this->modelGroup].modelAnimType][nextModelAnimType];

    if ((actionParam == PLAYER_AP_ZORA_FINS) || (this->itemActionParam == PLAYER_AP_ZORA_FINS)) {
        var_v1 = (actionParam == PLAYER_AP_NONE) ? -0xE : 0xE;
    } else if ((actionParam == PLAYER_AP_BOTTLE) || (actionParam == PLAYER_AP_11) ||
               ((actionParam == PLAYER_AP_NONE) &&
                ((this->itemActionParam == PLAYER_AP_BOTTLE) || (this->itemActionParam == PLAYER_AP_11)))) {
        var_v1 = (actionParam == PLAYER_AP_NONE) ? -0xD : 0xD;
    }

    this->unk_14E = ABS_ALT(var_v1);
    anim = D_8085CC88[this->unk_14E].anim;
    if ((anim == &gameplay_keep_Linkanim_00DC50) && (this->currentShield == PLAYER_SHIELD_NONE)) {
        anim = &gameplay_keep_Linkanim_00DC60;
    }
    endFrame = Animation_GetLastFrame(anim);
    if (var_v1 >= 0) {
        frameSpeed = 1.2f;
        startFrame = 0.0f;
    } else {
        frameSpeed = -1.2f;
        startFrame = endFrame;
        endFrame = 0.0f;
    }

    if (actionParam != PLAYER_AP_NONE) {
        frameSpeed *= 2.0f;
    }

    LinkAnimation_Change(play, &this->unk_284, anim, frameSpeed, startFrame, endFrame, ANIMMODE_ONCE, 0.0f);
    this->stateFlags3 &= ~PLAYER_STATE3_40000000;
}

void func_808304BC(Player* this, PlayState* play) {
    if ((this->actor.id == ACTOR_PLAYER) && !(this->stateFlags3 & PLAYER_STATE3_40000000)) {
        if ((this->itemActionParam == this->heldItemActionParam) || (this->stateFlags1 & PLAYER_STATE1_400000)) {
            if ((gSaveContext.save.playerData.health != 0) && (play->csCtx.state == CS_STATE_0)) {
                if ((this->csMode == PLAYER_CSMODE_0) && (play->unk_1887C == 0) && (play->activeCamId == 0)) {
                    if (!func_8082DA90(play) && (gSaveContext.unk_3DD0[4] != 5)) {
                        func_8082FE0C(this, play);
                    }
                }
            }
        }
    }

    if (this->stateFlags3 & PLAYER_STATE3_40000000) {
        func_808302CC(this, play);
    }
}

s32 func_808305BC(PlayState* play, Player* this, ItemID* item, s32* typeParam) {
    if (this->itemActionParam == PLAYER_AP_NUT) {
        *item = ITEM_NUT;
        *typeParam = (this->transformation == PLAYER_FORM_DEKU) ? 7 : 6;
    } else {
        *item = ITEM_BOW;
        *typeParam =
            (this->stateFlags1 & PLAYER_STATE1_800000) ? ENARROW_1 : this->itemActionParam - PLAYER_AP_BOW + ENARROW_2;
    }

    if (this->transformation == PLAYER_FORM_DEKU) {
        return ((gSaveContext.save.playerData.magic >= 2) ||
                ((gSaveContext.save.weekEventReg[8] & 1) && (play->sceneNum == SCENE_BOWLING)))
                   ? 1
                   : 0;
    }
    if (this->stateFlags3 & PLAYER_STATE3_400) {
        return 1;
    }
    if (gSaveContext.minigameState == 1) {
        return play->interfaceCtx.hbaAmmo;
    }
    if (play->unk_1887C != 0) {
        return play->unk_1887C;
    }

    return AMMO(*item);
}

u16 D_8085CFB0[] = {
    NA_SE_PL_BOW_DRAW,
    0,
    NA_SE_IT_HOOKSHOT_READY,
};

u8 sMagicArrowCosts[] = {
    4, // ENARROW_3
    4, // ENARROW_4
    8, // ENARROW_5
    2, // ENARROW_6
};

// Draw bow or hookshot / first person items?
s32 func_808306F8(Player* this, PlayState* play) {
    if ((this->itemActionParam >= PLAYER_AP_BOW_FIRE) && (this->itemActionParam <= PLAYER_AP_BOW_LIGHT) &&
        (gSaveContext.unk_3F28 != 0)) {
        play_sound(NA_SE_SY_ERROR);
    } else {
        func_8082F43C(play, this, func_80848BF4);

        this->stateFlags3 |= PLAYER_STATE3_40;
        this->unk_ACC = 14;

        if (this->unk_B28 >= 0) {
            s32 var_v1 = ABS_ALT(this->unk_B28);
            ItemID item;
            s32 arrowType;
            s32 magicArrowType;

            if (var_v1 != 2) {
                func_800B8E58(this, D_8085CFB0[var_v1 - 1]);
            }

            if (!Player_IsHoldingHookshot(this) && (func_808305BC(play, this, &item, &arrowType) > 0)) {
                if (this->unk_B28 >= 0) {
                    magicArrowType = arrowType - ENARROW_3;

                    if ((arrowType - ENARROW_3 >= ENARROW_3 - ENARROW_3) &&
                        (arrowType - ENARROW_3 <= ENARROW_5 - ENARROW_3)) {
                        if (((void)0, gSaveContext.save.playerData.magic) < sMagicArrowCosts[magicArrowType]) {
                            arrowType = ENARROW_2;
                            magicArrowType = -1;
                        }
                    } else if ((arrowType == ENARROW_7) &&
                               (!(gSaveContext.save.weekEventReg[8] & 1) || (play->sceneNum != SCENE_BOWLING))) {
                        magicArrowType = ENARROW_3;
                    } else {
                        magicArrowType = -1;
                    }

                    this->heldActor = Actor_SpawnAsChild(
                        &play->actorCtx, &this->actor, play, ACTOR_EN_ARROW, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, arrowType);

                    if ((this->heldActor != NULL) && (magicArrowType >= 0)) {
                        func_80115DB4(play, sMagicArrowCosts[magicArrowType], 0);
                    }
                }
            }
        }

        return true;
    }

    return false;
}

void func_808308DC(PlayState* play, Player* this) {
    s32 isGoronOrDeku = (this->transformation == PLAYER_FORM_GORON) || (this->transformation == PLAYER_FORM_DEKU);

    if ((this->itemActionParam != PLAYER_AP_NONE) && !isGoronOrDeku) {
        if (Player_ActionToSword(&this->actor, this->itemActionParam) >= 0) {
            func_8082E1F0(this, NA_SE_IT_SWORD_PUTAWAY);
        } else {
            func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
        }
    }

    func_80831990(play, this, this->heldItemId);
    if (!isGoronOrDeku) {
        if (Player_ActionToSword(&this->actor, this->itemActionParam) >= 0) {
            func_8082E1F0(this, NA_SE_IT_SWORD_PICKOUT);
        } else if (this->itemActionParam != PLAYER_AP_NONE) {
            func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
        }
    }
}

void func_808309CC(PlayState* play, Player* this) {
    if (func_80848808 == this->unk_AC4) {
        func_808308DC(play, this);
    }

    func_8082F43C(play, this, D_8085C9F0[this->itemActionParam]);
    this->unk_ACC = 0;
    this->unk_AA4 = 0;
    func_8082DCA0(play, this);
    this->stateFlags3 &= ~PLAYER_STATE3_40000000;
}

LinkAnimationHeader* D_8085CFBC[2] = {
    &gameplay_keep_Linkanim_00D470,
    &gameplay_keep_Linkanim_00D478,
};
LinkAnimationHeader* D_8085CFC4[2] = {
    &gameplay_keep_Linkanim_00D458,
    &gameplay_keep_Linkanim_00D460,
};
LinkAnimationHeader* D_8085CFCC[2] = {
    &gameplay_keep_Linkanim_00D400,
    &gameplay_keep_Linkanim_00D408,
};
LinkAnimationHeader* D_8085CFD4[2] = {
    &gameplay_keep_Linkanim_00D400,
    &gameplay_keep_Linkanim_00D410,
};
LinkAnimationHeader* D_8085CFDC[2] = {
    &gameplay_keep_Linkanim_00DBE0,
    &gameplay_keep_Linkanim_00D818,
};

LinkAnimationHeader* func_80830A58(PlayState* play, Player* this) {
    func_8082F43C(play, this, func_8084894C);
    func_8082DCA0(play, this);
    if (this->unk_B40 < 0.5f) {
        return D_8085CFBC[Player_IsHoldingTwoHandedWeapon(this)];
    }
    return D_8085CFC4[Player_IsHoldingTwoHandedWeapon(this)];
}

void func_80830AE8(Player* this) {
    s32 sfxId;

    if (this->transformation == PLAYER_FORM_GORON) {
        sfxId = NA_SE_PL_GORON_SQUAT;
    } else {
        s32 var_v1;

        if (this->transformation == PLAYER_FORM_DEKU) {
            var_v1 = NA_SE_PL_CHANGE_ARMS;
        } else {
            var_v1 = NA_SE_IT_SHIELD_SWING;
        }
        sfxId = var_v1;
    }

    func_800B8E58(this, sfxId);
}

void func_80830B38(Player* this) {
    s32 sfxId;

    if (this->transformation == PLAYER_FORM_GORON) {
        sfxId = NA_SE_PL_BALL_TO_GORON;
    } else {
        s32 var_v1;

        if (this->transformation == PLAYER_FORM_DEKU) {
            var_v1 = NA_SE_PL_TAKE_OUT_SHIELD;
        } else {
            var_v1 = NA_SE_IT_SHIELD_REMOVE;
        }
        sfxId = var_v1;
    }

    func_800B8E58(this, sfxId);
}

s32 func_80830B88(PlayState* play, Player* this) {
    if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_R)) {
        if (!(this->stateFlags1 & (PLAYER_STATE1_400000 | PLAYER_STATE1_800000 | PLAYER_STATE1_20000000))) {
            if (!(this->stateFlags1 & PLAYER_STATE1_8000000) ||
                ((this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) && (this->actor.bgCheckFlags & 1))) {
                if ((play->unk_1887C == 0) && (this->itemActionParam == this->heldItemActionParam)) {
                    if ((this->transformation == PLAYER_FORM_FIERCE_DEITY) ||
                        (!Player_IsGoronOrDeku(this) &&
                         ((((this->transformation == PLAYER_FORM_ZORA)) &&
                           !(this->stateFlags1 & PLAYER_STATE1_2000000)) ||
                          ((this->transformation == PLAYER_FORM_HUMAN) &&
                           (this->currentShield != PLAYER_SHIELD_NONE))) &&
                         func_8082FBE8(this))) {
                        LinkAnimationHeader* anim = func_80830A58(play, this);
                        f32 lastFrame;

                        lastFrame = Animation_GetLastFrame(anim);
                        LinkAnimation_Change(play, &this->unk_284, anim, 3.0f / 3.0f, lastFrame, lastFrame,
                                             ANIMMODE_ONCE, 0.0f);
                        func_80830AE8(this);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void func_80830CE8(PlayState* play, Player* this) {
    func_8082F43C(play, this, func_80848AB0);
    if (this->heldItemActionParam < 0) {
        func_80123C58(this);
    }
    Animation_Reverse(&this->unk_284);
    func_80830B38(this);
}

void func_80830D40(PlayState* play, Player* this) {
    struct_8085CC88* entry = &D_8085CC88[this->unk_14E];
    f32 frame;

    frame = entry->frame;
    if (this->unk_284.playSpeed < 0.0f) {
        frame -= 1.0f;
    }
    if (LinkAnimation_OnFrame(&this->unk_284, frame)) {
        func_808308DC(play, this);
    }
    func_8082FB68(this);
}

s32 func_80830DF0(Player* this, PlayState* play) {
    if (this->stateFlags3 & PLAYER_STATE3_40000000) {
        func_808302CC(this, play);
    } else {
        return false;
    }
    return true;
}

s32 func_80830E30(Player* this, PlayState* play) {
    if ((this->itemActionParam == PLAYER_AP_11) || (this->transformation == PLAYER_FORM_ZORA)) {
        func_8082F43C(play, this, func_8084923C);

        LinkAnimation_PlayOnce(play, &this->unk_284,
                               (this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_LEFT)
                                   ? &gameplay_keep_Linkanim_00E3A8
                                   : ((this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_COMBO)
                                          ? &gameplay_keep_Linkanim_00E3B0
                                          : &gameplay_keep_Linkanim_00E3B8));
        this->unk_ACC = 0xA;
    } else {
        if (!func_808306F8(this, play)) {
            return false;
        }

        LinkAnimation_PlayOnce(play, &this->unk_284,
                               (Player_IsHoldingHookshot(this))
                                   ? &gameplay_keep_Linkanim_00D9D8
                                   : ((this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2F8
                                                                                 : &gameplay_keep_Linkanim_00D4F0));
    }

    if (this->stateFlags1 & PLAYER_STATE1_800000) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00E050);
    } else if ((this->actor.bgCheckFlags & 1) && (this->transformation != PLAYER_FORM_ZORA)) {
        Player_AnimationPlayLoop(play, this, func_8082ED20(this));
    }

    return true;
}

s32 func_80830F9C(PlayState* play) {
    return play->unk_1887C > 0 && CHECK_BTN_ALL(D_80862B44->press.button, BTN_B);
}

s32 func_80830FD4(PlayState* play) {
    return play->unk_1887C != 0 &&
           (play->unk_1887C < 0 ||
            CHECK_BTN_ANY(D_80862B44->cur.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_B | BTN_A));
}

s32 func_80831010(Player* this, PlayState* play) {
    if ((this->unk_AA5 == 0) || (this->unk_AA5 == 3)) {
        if (func_8082FBE8(this) || (this->targetedActor != NULL) ||
            (func_800DF86C(Play_GetCamera(play, CAM_ID_MAIN), 0xD) == 0)) {
            return true;
        }
        this->unk_AA5 = 3;
    }
    return false;
}

s32 func_80831094(Player* this, PlayState* play) {
    if ((this->doorType == PLAYER_DOORTYPE_0) && !(this->stateFlags1 & PLAYER_STATE1_2000000)) {
        if ((D_80862B48 != 0) || func_80830F9C(play)) {
            if (func_80830E30(this, play)) {
                return func_80831010(this, play);
            }
        }
    }
    return false;
}

s32 func_80831124(PlayState* play, Player* this) {
    if (this->actor.child != NULL) {
        if (this->heldActor == NULL) {
            this->heldActor = this->actor.child;
            Player_RequestRumble(play, this, 255, 10, 250, SQ(0));
            func_800B8E58(this, NA_SE_IT_HOOKSHOT_RECEIVE);
        }
        return true;
    }
    return false;
}

s32 func_80831194(PlayState* play, Player* this) {
    if (this->heldActor != NULL) {
        if (!Player_IsHoldingHookshot(this)) {
            ItemID item;
            s32 sp30;

            func_808305BC(play, this, &item, &sp30);
            if ((this->transformation != PLAYER_FORM_DEKU) && !(this->stateFlags3 & PLAYER_STATE3_400)) {
                if (gSaveContext.minigameState == 1) {
                    if ((play->sceneNum != SCENE_SYATEKI_MIZU) && (play->sceneNum != SCENE_F01) &&
                        (play->sceneNum != SCENE_SYATEKI_MORI)) {
                        play->interfaceCtx.hbaAmmo -= 1;
                    }
                } else if (play->unk_1887C != 0) {
                    play->unk_1887C--;
                } else {
                    Inventory_ChangeAmmo(item, -1);
                }
            }

            if (play->unk_1887C == 1) {
                play->unk_1887C = -0xA;
            }

            Player_RequestRumble(play, this, 150, 10, 150, SQ(0));
        } else {
            Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
            this->unk_B48 = 0.0f;
        }

        this->unk_D57 = (this->transformation == PLAYER_FORM_DEKU) ? 0x14 : 4;

        this->heldActor->parent = NULL;
        this->actor.child = NULL;
        this->heldActor = NULL;
        return 1;
    }

    return 0;
}

void func_8083133C(Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_20000;

    if (!(this->skelAnime.moveFlags & 0x80) && (this->actor.bgCheckFlags & 0x200) && (D_80862B20 < 0x2000)) {
        this->currentYaw = this->actor.shape.rot.y = this->actor.wallYaw + 0x8000;
    }

    this->targetYaw = this->actor.shape.rot.y;
}

s32 func_808313A8(PlayState* play, Player* this, Actor* actor) {
    if (actor == NULL) {
        func_8082DE50(play, this);
        func_80836988(this, play);
        return true;
    }

    return false;
}

void func_808313F0(Player* this, PlayState* play) {
    if (!func_808313A8(play, this, this->heldActor)) {
        func_8082F43C(play, this, func_808490B4);
        LinkAnimation_PlayLoop(play, &this->unk_284, &gameplay_keep_Linkanim_00DB30);
    }
}

void func_80831454(Player* this) {
    if ((this->stateFlags3 & PLAYER_STATE3_20000000) || (this->stateFlags2 & PLAYER_STATE2_2000000)) {
        Audio_QueueSeqCmd(0x110000FF);
    }
}

s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    s32 i;
    f32* ptr;

    if (actionFunc == this->actionFunc) {
        return false;
    }

    play->actorCtx.unk5 &= ~4;

    if (this->actor.flags & ACTOR_FLAG_20000000) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
        this->actor.flags &= ~ACTOR_FLAG_20000000;
    } else if ((func_80857BE8 == this->actionFunc) || (func_808561B0 == this->actionFunc)) {
        this->actor.shape.shadowDraw = ActorShadow_DrawFeet;
        this->actor.shape.shadowScale = this->ageProperties->unk_04;
        this->unk_ABC = 0.0f;
        if (func_80857BE8 == this->actionFunc) {
            if (this->stateFlags3 & PLAYER_STATE3_80000) {
                func_80115D5C(&play->state);
            }
            func_8082DD2C(play, this);
            this->actor.shape.rot.x = 0;
            this->actor.shape.rot.z = 0;
            this->actor.bgCheckFlags &= ~0x0800;
        } else {
            Actor_SetScale(&this->actor, 0.01f);
        }
    } else if ((this->transformation == PLAYER_FORM_GORON) && (Player_GetMeleeWeaponHeld(this) != 0)) {
        func_80831990(play, this, ITEM_NONE);
    }

    func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
    this->actionFunc = actionFunc;

    if ((this->heldItemActionParam != this->itemActionParam) &&
        (!(arg3 & 1) || !(this->stateFlags1 & PLAYER_STATE1_400000))) {
        func_80123C58(this);
    }

    if (!(arg3 & 1) && !(this->stateFlags1 & PLAYER_STATE1_800)) {
        func_808309CC(play, this);
        LinkAnimation_PlayLoop(play, &this->unk_284, func_8082ED20(this));
        this->stateFlags1 &= ~PLAYER_STATE1_400000;
    }

    func_80831454(this);
    func_8082E794(this);

    this->stateFlags1 &= 0x4BFFFFBF;
    this->stateFlags2 &= 0xE577FFFF;
    this->stateFlags3 &= 0xDED05D75;

    this->unk_AE7 = 0;
    this->unk_AE8 = 0;
    this->unk_AA4 = 0;
    this->unk_B86[0] = 0;
    this->unk_B86[1] = 0;
    this->unk_B8A = 0;
    this->unk_B8C = 0;
    this->unk_B8E = 0;

    // TODO: Is there no other way to write this that works?
    i = 0;
    ptr = this->unk_B10;
    do {
        *ptr = 0.0f;
        ptr++;
        i++;
    } while (i < ARRAY_COUNT(this->unk_B10));

    this->actor.shape.rot.z = 0;

    func_8082F09C(this);
    func_8082E00C(this);

    return true;
}

void func_8083172C(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    s32 moveFlags = this->skelAnime.moveFlags;

    this->skelAnime.moveFlags = 0;
    Player_SetAction(play, this, actionFunc, arg3);
    this->skelAnime.moveFlags = moveFlags;
}

void func_80831760(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    if (this->heldItemActionParam >= 0) {
        s32 heldItemActionParam = this->heldItemActionParam;

        this->heldItemActionParam = this->itemActionParam;
        Player_SetAction(play, this, actionFunc, arg3);
        this->heldItemActionParam = heldItemActionParam;

        Player_SetModels(this, Player_ActionToModelGroup(this, this->heldItemActionParam));
    }
}

void func_808317C4(Player* this) {
    if (Player_IsHoldingHookshot(this)) {
        if (this->heldActor != NULL) {
            Actor_MarkForDeath(this->heldActor);
            this->actor.child = NULL;
            this->heldActor = NULL;
        }
    }
}

s32 func_80831814(Player* this, PlayState* play, s32 arg2) {
    if (!(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_800 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000))) {
        if (func_800DF86C(Play_GetCamera(play, CAM_ID_MAIN), 6) != 0) {
            if ((this->actor.bgCheckFlags & 1) ||
                (func_801242B4(this) && (this->actor.depthInWater < this->ageProperties->unk_2C))) {
                this->unk_AA5 = arg2;
                return true;
            }
        }
    }
    return false;
}

void func_808318C0(PlayState* play) {
    if (func_80115DB4(play, 0, 3) != 0) {
        if (play->actorCtx.unk3 != 0) {
            Actor_DisableLens(play);
        } else {
            play->actorCtx.unk3 = 1;
        }

        play_sound(play->actorCtx.unk3 != 0 ? NA_SE_SY_GLASSMODE_ON : NA_SE_SY_GLASSMODE_OFF);
    } else {
        play_sound(NA_SE_SY_ERROR);
    }
}

void func_80831944(PlayState* play, Player* this) {
    if (func_8012364C(play, this, func_8082FDC4()) == ITEM_LENS) {
        func_808318C0(play);
    }
}

void func_80831990(PlayState* play, Player* this, ItemID item) {
    PlayerActionParam actionParam = Player_ItemToActionParam(this, item);

    if ((((this->itemActionParam == this->heldItemActionParam) &&
          (!(this->stateFlags1 & PLAYER_STATE1_400000) || (Player_ActionToMeleeWeapon(actionParam) != 0) ||
           (actionParam == PLAYER_AP_NONE))) ||
         ((this->heldItemActionParam < PLAYER_AP_NONE) &&
          ((Player_ActionToMeleeWeapon(actionParam) != 0) || (actionParam == PLAYER_AP_NONE)))) &&
        ((actionParam == PLAYER_AP_NONE) || !(this->stateFlags1 & PLAYER_STATE1_8000000) ||
         (actionParam == PLAYER_AP_MASK_ZORA) ||
         ((this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) && (this->actor.bgCheckFlags & 1)))) {

        s32 var_v1 = ((actionParam >= PLAYER_AP_MASK_TRUTH) && (actionParam <= PLAYER_AP_MASK_DEKU) &&
                      ((this->transformation != PLAYER_FORM_HUMAN) || (actionParam >= PLAYER_AP_MASK_GIANT)));
        CollisionPoly* sp5C;
        s32 sp58;
        f32 sp54;
        s32 explAction;

        if (var_v1 || (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_100) && (actionParam != PLAYER_AP_NONE)) ||
            (actionParam == PLAYER_AP_OCARINA) ||
            ((actionParam > PLAYER_AP_BOTTLE) && actionParam < PLAYER_AP_MASK_TRUTH) ||
            ((actionParam == PLAYER_AP_PICTO_BOX) && (this->talkActor != NULL) &&
             (this->exchangeItemId > PLAYER_AP_NONE))) {
            if (var_v1) {
                s32 playerForm = (actionParam < PLAYER_AP_MASK_FIERCE_DEITY)
                                     ? PLAYER_FORM_HUMAN
                                     : actionParam - PLAYER_AP_MASK_FIERCE_DEITY;

                if (((this->currentMask != PLAYER_MASK_GIANT) && (actionParam == PLAYER_AP_MASK_GIANT) &&
                     ((gSaveContext.unk_3F28 != 0) || (gSaveContext.save.playerData.magic == 0))) ||
                    (!(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                     BgCheck_EntityCheckCeiling(&play->colCtx, &sp54, &this->actor.world.pos,
                                                D_8085BA38[playerForm].unk_00, &sp5C, &sp58, &this->actor))) {
                    play_sound(NA_SE_SY_ERROR);
                    return;
                }
            }
            if ((actionParam == PLAYER_AP_MAGIC_BEANS) &&
                (gSaveContext.save.inventory.ammo[gItemSlots[ITEM_MAGIC_BEANS]] == 0)) {
                play_sound(NA_SE_SY_ERROR);
            } else {
                this->heldItemActionParam = actionParam;
                this->unk_AA5 = 5;
            }
        } else if (((actionParam == PLAYER_AP_STICK) &&
                    (gSaveContext.save.inventory.ammo[gItemSlots[ITEM_STICK]] == 0)) ||
                   (((play->unk_1887D != 0) || (play->unk_1887E != 0)) &&
                    (play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].length >= 5)) ||
                   ((play->unk_1887D == 0) && (play->unk_1887E == 0) &&
                    ((explAction = Player_ActionToExplosive(this, actionParam)) >= 0) &&
                    ((gSaveContext.save.inventory.ammo[gItemSlots[D_8085CD24[explAction].itemId]] == 0) ||
                     (play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].length >= 3)))) {
            play_sound(NA_SE_SY_ERROR);
        } else if (actionParam == PLAYER_AP_LENS) {
            func_808318C0(play);
        } else if (actionParam == PLAYER_AP_PICTO_BOX) {
            if (!func_80831814(this, play, 2)) {
                play_sound(NA_SE_SY_ERROR);
            }
        } else if ((actionParam == PLAYER_AP_NUT) &&
                   ((this->transformation != PLAYER_FORM_DEKU) || (this->heldItemButton != 0))) {
            if (gSaveContext.save.inventory.ammo[gItemSlots[ITEM_NUT]] != 0) {
                func_8083A658(play, this);
            } else {
                play_sound(NA_SE_SY_ERROR);
            }
        } else if ((this->transformation == PLAYER_FORM_HUMAN) && (actionParam >= PLAYER_AP_MASK_TRUTH) &&
                   (actionParam < PLAYER_AP_MASK_GIANT)) {
            s32 maskId = actionParam - PLAYER_AP_39;

            this->prevMask = this->currentMask;
            if (maskId == this->currentMask) {
                this->currentMask = PLAYER_MASK_NONE;
                func_8082E1F0(this, NA_SE_PL_TAKE_OUT_SHIELD);
            } else {
                this->currentMask = maskId;
                func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
            }
            gSaveContext.save.equippedMask = this->currentMask;
        } else if ((actionParam != this->itemActionParam) ||
                   ((this->heldActor == NULL) && (Player_ActionToExplosive(this, actionParam) >= 0))) {
            u8 nextAnimType;

            this->nextModelGroup = Player_ActionToModelGroup(this, actionParam);
            nextAnimType = gPlayerModelTypes[this->nextModelGroup].modelAnimType;
            var_v1 = ((this->transformation != PLAYER_FORM_GORON) || (actionParam == PLAYER_AP_POWDER_KEG));

            if (var_v1 && (this->itemActionParam >= 0) && (item != this->heldItemId) &&
                (D_8085CD00[gPlayerModelTypes[this->modelGroup].modelAnimType][nextAnimType] != 0)) {
                this->heldItemId = item;
                this->stateFlags3 |= PLAYER_STATE3_40000000;
            } else {
                func_808317C4(this);
                func_8082DCA0(play, this);
                func_8082F470(play, this, actionParam);
                if (!var_v1) {
                    D_80862B48 = 1;
                    D_80862B4C = 1;
                }
            }
        } else {
            D_80862B48 = 1;
            D_80862B4C = 1;
        }
    }
}

void func_80831F34(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    s32 sp24;

    sp24 = func_801242B4(this);
    func_8082DE50(play, this);
    Player_SetAction(play, this, sp24 ? func_80851BD4 : func_8084BFDC, 0);
    Player_AnimationPlayOnce(play, this, anim);

    if (anim == &gameplay_keep_Linkanim_00D698) {
        this->skelAnime.endFrame = 84.0f;
    }

    this->stateFlags1 |= PLAYER_STATE1_80;
    func_8082DAD4(this);
    func_8082DF8C(this, NA_SE_VO_LI_DOWN);
    if (this == GET_PLAYER(play)) {
        this->unk_A86 = play->playerActorCsIds[6];
        func_801A0184();
        gSaveContext.powderKegTimer = 0;
        gSaveContext.unk_1014 = 0;
        gSaveContext.jinxTimer = 0;

        if (Inventory_ConsumeFairy(play) != 0) {
            play->gameOverCtx.state = 0x14;
            this->unk_AE7 = 1;
        } else {
            play->gameOverCtx.state = 1;
            func_801A41F8(0);
            func_801A3098(0x20);
            gSaveContext.seqIndex = 0xFF;
            gSaveContext.nightSeqIndex = 0xFF;
        }

        ShrinkWindow_SetLetterboxTarget(0x20);
    }
}

s32 func_80832090(Player* this) {
    return (((func_8084D770 == this->actionFunc) == 0) ||
            (((this->stateFlags3 & PLAYER_STATE3_40000000)) &&
             ((this->heldItemId == ITEM_FC) || (this->heldItemId == ITEM_NONE)))) &&
           (((func_80848808 == this->unk_AC4) == 0) ||
            Player_ItemToActionParam(this, this->heldItemId) == this->itemActionParam);
}

s32 func_8083213C(Player* this) {
    return func_8084AC84 == this->actionFunc || func_8084AEEC == this->actionFunc;
}

s32 func_8083216C(Player* this, PlayState* play) {
    if (!(this->stateFlags1 & PLAYER_STATE1_800000) && (this->actor.parent != NULL) && Player_IsHoldingHookshot(this)) {
        Player_SetAction(play, this, func_80855E08, 1);
        this->stateFlags3 |= PLAYER_STATE3_80;
        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00D9C8);
        func_8082E920(play, this, (1 | 2 | 8 | 0x10 | 0x80));
        func_8082DAD4(this);
        this->currentYaw = this->actor.shape.rot.y;
        this->actor.bgCheckFlags &= ~1;
        this->unk_AA6 |= 0x43;
        func_8082DF8C(this, NA_SE_VO_LI_LASH);
        return true;
    }

    if (func_80832090(this)) {
        func_808304BC(this, play);
        if (func_80852B28 == this->actionFunc) {
            return true;
        }
    }

    if (!this->unk_AC4(this, play)) {
        return false;
    }

    if (this->unk_AC8 != 0.0f) {
        if ((func_8082ED94(this) == 0) || (this->linearVelocity != 0.0f)) {
            AnimationContext_SetCopyFalse(play, this->skelAnime.limbCount, this->unk_284.jointTable,
                                          this->skelAnime.jointTable, D_8085B9F0);
        }
        if ((this->actor.bgCheckFlags & 1) && !(this->skelAnime.moveFlags & 8)) {
            Math_StepToF(&this->unk_AC8, 0.0f, 0.25f);
            AnimationContext_SetInterp(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                       this->unk_284.jointTable, 1.0f - this->unk_AC8);
        }
    } else if ((func_8082ED94(this) == 0) || (this->linearVelocity != 0.0f) || (this->skelAnime.moveFlags & 8)) {
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->unk_284.jointTable, D_8085B9F0);
    } else {
        AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                    this->unk_284.jointTable);
    }

    return true;
}

s32 func_808323C0(Player* this, s16 csIndex) {
    if ((csIndex >= 0) && (ActorCutscene_GetCurrentIndex() != csIndex)) {
        if (!ActorCutscene_GetCanPlayNext(csIndex)) {
            ActorCutscene_SetIntentToPlay(csIndex);

            return false;
        }
        ActorCutscene_Start(csIndex, &this->actor);
    }
    this->unk_A86 = csIndex;

    return true;
}

s32 func_80832444(Player* this);
s32 func_8083249C(Player* this);
s32 func_808324EC(PlayState* play, Player* this, void (*arg2)(PlayState*, Player*), s32 arg3);

s32 func_80832444(Player* this) {
    if (this->unk_A86 >= 0) {
        if (ActorCutscene_GetCanPlayNext(this->unk_A86) == 0) {
            ActorCutscene_SetIntentToPlay(this->unk_A86);
            return false;
        }

        ActorCutscene_Start(this->unk_A86, &this->actor);
    }
    return true;
}

s32 func_8083249C(Player* this) {
    if ((this->unk_A86 >= 0) && (ActorCutscene_GetCurrentIndex() != this->unk_A86)) {
        return func_80832444(this);
    }
    return true;
}

s32 func_808324EC(PlayState* play, Player* this, PlayerFuncD58 arg2, s32 arg3) {
    this->unk_D58 = arg2;
    this->unk_A86 = arg3;
    Player_SetAction(play, this, func_8084D770, 0);
    func_8083249C(this);
    this->stateFlags2 |= PLAYER_STATE2_40;
    return func_8082DE14(play, this);
}

s32 func_80832558(PlayState* play, Player* this, void (*arg2)(PlayState*, Player*)) {
    return func_808324EC(play, this, arg2, -1);
}

// To do with turning, related to targeting
void func_80832578(Player* this, PlayState* play) {
    s16 previousYaw = this->actor.shape.rot.y;

    if (!(this->stateFlags2 & (PLAYER_STATE2_20 | PLAYER_STATE2_40))) {
        Actor* targetedActor = this->targetedActor;

        if ((targetedActor != NULL) && ((play->actorCtx.targetContext.unk4B != 0) || (this != GET_PLAYER(play))) &&
            (targetedActor->id != ACTOR_OBJ_NOZOKI)) {
            Math_ScaledStepToS(&this->actor.shape.rot.y,
                               Math_Vec3f_Yaw(&this->actor.world.pos, &targetedActor->focus.pos), 0xFA0);
        } else if ((this->stateFlags1 & PLAYER_STATE1_20000) &&
                   !(this->stateFlags2 & (PLAYER_STATE2_20 | PLAYER_STATE2_40))) {
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->targetYaw, 0xFA0);
        }
    } else if (!(this->stateFlags2 & PLAYER_STATE2_40)) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->currentYaw, 0x7D0);
    }

    this->unk_B4C = this->actor.shape.rot.y - previousYaw;
}

s16 func_80832660(s16* pValue, s16 target, s16 step, s16 arg3, s16 arg4, s16 arg5) {
    s16 temp_v1;
    s16 var_v0;
    s32 temp;

    temp_v1 = var_v0 = arg4 - (*pValue);
    var_v0 = CLAMP(var_v0, -arg5, arg5);
    *pValue += (s16)(temp_v1 - var_v0);

    Math_ScaledStepToS(pValue, target, step);

    //! FAKE: redundant cast (?)
    temp = (s16)(s32)*pValue;
    if (*pValue < -arg3) {
        *pValue = -arg3;
    } else if (arg3 < *pValue) {
        *pValue = arg3;
    }
    return (temp - *pValue);
}

s16 func_80832754(Player* this, s32 arg1) {
    s16 sp36;
    s16 var_s1 = this->actor.shape.rot.y;

    if (arg1) {
        this->unk_AB2.x = this->actor.focus.rot.x;
        var_s1 = this->actor.focus.rot.y;
        this->unk_AA6 |= 0x41;
    } else {
        s16 temp = func_80832660(&this->unk_AAC.x, this->actor.focus.rot.x, 0x258, 0x2710, this->actor.focus.rot.x, 0);

        func_80832660(&this->unk_AB2.x, temp, 0xC8, 0xFA0, this->unk_AAC.x, 0x2710);

        sp36 = this->actor.focus.rot.y - var_s1;
        func_80832660(&sp36, 0, 0xC8, 0x5DC0, this->unk_AB2.y, 0x1F40);
        var_s1 = this->actor.focus.rot.y - sp36;
        func_80832660(&this->unk_AAC.y, (sp36 - this->unk_AB2.y), 0xC8, 0x1F40, sp36, 0x1F40);
        func_80832660(&this->unk_AB2.y, sp36, 0xC8, 0x1F40, this->unk_AAC.y, 0x1F40);
        this->unk_AA6 |= 0xD9;
    }

    return var_s1;
}

void func_80832888(Player* this, PlayState* play) {
    s32 var_v1 = 0;
    Actor* var_v1_2;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 var_a1;

    temp_v0 = CHECK_BTN_ALL(D_80862B44->cur.button, BTN_Z);
    if (temp_v0 == 0) {
        this->stateFlags1 &= ~PLAYER_STATE1_40000000;
    }

    if ((play->csCtx.state != CS_STATE_0) || (this->csMode != PLAYER_CSMODE_0) ||
        (this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) || (this->stateFlags3 & PLAYER_STATE3_80)) {
        this->unk_738 = 0;
    } else if ((temp_v0 != 0) || (this->stateFlags2 & PLAYER_STATE2_2000) || (this->unk_A78 != NULL)) {
        if (this->unk_738 <= 5) {
            this->unk_738 = 5;
        } else {
            this->unk_738--;
        }
    } else if (this->stateFlags1 & PLAYER_STATE1_20000) {
        this->unk_738 = 0;
    } else if (this->unk_738 != 0) {
        this->unk_738--;
    }

    if (this->unk_738 > 5) {
        var_v1 = 1;
    }

    temp_v0_3 = func_8082DAFC(play);
    if (temp_v0_3 || (this->unk_738 != 0) || (this->stateFlags1 & (PLAYER_STATE1_1000 | PLAYER_STATE1_2000000))) {
        if (!temp_v0_3) {
            if (!(this->stateFlags1 & PLAYER_STATE1_2000000) &&
                ((this->itemActionParam != PLAYER_AP_FISHING_POLE) || (this->unk_B28 == 0)) &&
                CHECK_BTN_ALL(D_80862B44->press.button, BTN_Z)) {
                var_v1_2 = (this == GET_PLAYER(play)) ? play->actorCtx.targetContext.arrowPointedActor
                                                      : &GET_PLAYER(play)->actor;
                var_a1 = gSaveContext.options.zTargetSetting != 0 || this != GET_PLAYER(play);
                this->stateFlags1 |= PLAYER_STATE1_8000;
                if ((this->currentMask != PLAYER_MASK_GIANT) && (var_v1_2 != NULL) &&
                    !(var_v1_2->flags & ACTOR_FLAG_8000000) &&
                    !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) {
                    if ((var_v1_2 == this->targetedActor) && (this == GET_PLAYER(play))) {
                        var_v1_2 = play->actorCtx.targetContext.unk_94;
                    }

                    if ((var_v1_2 != NULL) &&
                        (((var_v1_2 != this->targetedActor)) || (var_v1_2->flags & ACTOR_FLAG_80000))) {
                        var_v1_2->flags &= ~ACTOR_FLAG_80000;
                        if (var_a1 == 0) {
                            this->stateFlags2 |= PLAYER_STATE2_2000;
                        }
                        this->targetedActor = var_v1_2;
                        this->unk_738 = 0xF;
                        this->stateFlags2 &= ~(PLAYER_STATE2_2 | PLAYER_STATE2_200000);
                    } else if (var_a1 == 0) {
                        func_80123DA4(this);
                    }
                    this->stateFlags1 &= ~PLAYER_STATE1_40000000;
                } else if (!(this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) &&
                           (func_808573A4 != this->actionFunc)) {
                    func_8083133C(this);
                }
            }

            if (this->targetedActor != NULL) {
                if ((this == GET_PLAYER(play)) && (this->targetedActor != this->unk_A78) &&
                    func_800B83F8(this->targetedActor, this, var_v1)) {
                    func_80123DA4(this);
                    this->stateFlags1 |= PLAYER_STATE1_40000000;
                } else if (this->targetedActor != NULL) {
                    this->targetedActor->targetPriority = 0x28;
                }
            } else if (this->unk_A78 != NULL) {
                this->targetedActor = this->unk_A78;
            }
        }

        if ((this->targetedActor != NULL) && !(this->stateFlags3 & (PLAYER_STATE1_200 | PLAYER_STATE1_2000))) {
            this->stateFlags1 &= ~(PLAYER_STATE1_10000 | PLAYER_STATE1_20000);
            if ((this->stateFlags1 & PLAYER_STATE1_800) ||
                !CHECK_FLAG_ALL(this->targetedActor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_4)) {
                this->stateFlags1 |= PLAYER_STATE1_10000;
            }
        } else if (this->stateFlags1 & PLAYER_STATE1_20000) {
            this->stateFlags2 &= ~PLAYER_STATE1_2000;
        } else {
            func_80123DC0(this);
        }
    } else {
        func_80123DC0(this);
    }
}

s32 func_80832CAC(PlayState* play, Player* this, f32* arg2, s16* arg3, f32 arg4) {
    f32 new_var;
    f32 temp_fv0;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fa1_2;

    if ((this->unk_AA5 != 0) || (func_8082DA90(play) != 0) || (this->stateFlags1 & 1)) {
        *arg2 = 0.0f;
        *arg3 = this->actor.shape.rot.y;
    } else {
        *arg2 = D_80862AFC;
        *arg3 = D_80862B00;
        if (arg4 != 0.0f) {
            *arg2 -= 20.0f;
            if (*arg2 < 0.0f) {
                *arg2 = 0.0f;
            } else {
                temp_fv1_2 = 1.0f - Math_CosS(*arg2 * 450.0f);
                *arg2 = (SQ(temp_fv1_2) * 30.0f) + 7.0f;
            }
        } else {
            *arg2 *= 0.8f;
        }

        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            *arg2 *= 1.5f;
        }

        if (D_80862AFC != 0.0f) {
            temp_fv0 = Math_SinS(this->unk_B6C);

            var_fa0 = this->unk_B50;
            if (this->unk_AB8 != 0.0f) {
                if (this->targetedActor != NULL) {
                    var_fa1 = 0.002f;
                } else {
                    var_fa1 = 0.008f;
                }
                var_fa0 -= this->unk_AB8 * var_fa1;
                if (var_fa0 < 2.0f) {
                    var_fa0 = 2.0f;
                }
            }
            *arg2 = (*arg2 * 0.14f) - (8.0f * temp_fv0 * temp_fv0);

            if (*arg2 < 0.0f) {
                *arg2 = 0.0f;
                return 1;
            }

            //! FAKE
            if (var_fa0 < *arg2) {
                goto dummy_label_131731;
            dummy_label_131731:;
                var_fa1_2 = var_fa0;
            } else {
                new_var = *arg2;
                var_fa1_2 = new_var;
            }

            *arg2 = var_fa1_2;
            return 1;
        }
    }

    return 0;
}

s32 func_80832F24(Player* this) {
    return Math_StepToF(&this->linearVelocity, 0.0f, REG(43) / 100.0f);
}

s32 func_80832F78(Player* this, f32* arg1, s16* arg2, f32 arg3, PlayState* play) {
    if (func_80832CAC(play, this, arg1, arg2, arg3) == 0) {
        *arg2 = this->actor.shape.rot.y;

        if (this->targetedActor != NULL) {
            if ((play->actorCtx.targetContext.unk4B != 0) && !(this->stateFlags2 & PLAYER_STATE2_40)) {
                *arg2 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->targetedActor->focus.pos);
            }
        } else if (func_80123434(this)) {
            *arg2 = this->targetYaw;
        }

        return false;
    }

    *arg2 += Camera_GetInputDirYaw(play->cameraPtrs[play->activeCamId]);
    return true;
}

s8 D_8085CFE4[8] = { 0xD, 2, 4, 9, 0xA, 0xB, 8, -7 };
s8 D_8085CFEC[0xC] = { 0xD, 1, 2, 5, 3, 4, 9, 0xA, 0xB, 7, 8, -6 };
s8 D_8085CFF8[0xC] = { 0xD, 1, 2, 3, 4, 9, 0xA, 0xB, 8, 7, -6, 0 };
s8 D_8085D004[8] = { 0xD, 2, 4, 9, 0xA, 0xB, 8, -7 };
s8 D_8085D00C[0xC] = { 0xD, 2, 4, 9, 0xA, 0xB, 0xC, 8, -7, 0, 0, 0 };
s8 D_8085D018[4] = { -7, 0, 0, 0 };
s8 D_8085D01C[0xC] = { 0, 0xB, 1, 2, 3, 5, 4, 9, 8, 7, -6, 0 };
s8 D_8085D028[0xC] = { 0, 0xB, 1, 2, 3, 0xC, 5, 4, 9, 8, 7, -6 };
s8 D_8085D034[0x10] = { 0xD, 1, 2, 3, 0xC, 5, 4, 9, 0xA, 0xB, 8, 7, -6, 0, 0, 0 };
s8 D_8085D044[4] = { 0xA, 8, -7, 0 };
s8 D_8085D048[8] = { 0, 0xC, 5, 4, -0xE, 0, 0, 0 };
s8 D_8085D050[4] = { 0xD, 2, -4, 0 };

s32 (*D_8085D054[])(Player*, PlayState*) = {
    func_80839518, func_808365DC, func_8083D23C, func_8083CCB4, func_808391D8,
    func_8083DFC4, func_8083A114, func_80848570, func_8083A580, func_8083D78C,
    func_80839B18, func_8083A274, func_80834DFC, func_80838A90, func_8083A0CC,
};

s32 func_80833058(PlayState* play, Player* this, s8* arg2, s32 arg3) {
    if (!(this->stateFlags1 & (PLAYER_STATE1_1 | PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) && !func_8082DA90(play)) {
        if (arg3 != 0) {
            D_80862B04 = func_8083216C(this, play);
            if (func_80852B28 == this->actionFunc) {
                return true;
            }
        }

        if (func_801240DC(this)) {
            this->unk_AA6 |= 0x41;
            return true;
        }

        if (!(this->stateFlags3 & PLAYER_STATE3_40000000) && (func_80848808 != this->unk_AC4)) {
            s8 var_v0 = *arg2;

            while (var_v0 >= 0) {
                if (D_8085D054[var_v0](this, play) != 0) {
                    return true;
                }
                arg2++;
                var_v0 = *arg2;
            }

            if (D_8085D054[-var_v0](this, play) != 0) {
                return true;
            }
        }

        if (func_8083213C(this)) {
            return true;
        }
    } else if (this->stateFlags1 & PLAYER_STATE1_800) {
        func_8083216C(this, play);
    }

    return false;
}

s32 func_808331FC(PlayState* play, Player* this, SkelAnime* skelAnime, f32 frame) {
    if ((skelAnime->endFrame - frame) <= skelAnime->curFrame) {
        f32 sp24;
        s16 sp22;

        if (func_80833058(play, this, D_8085D01C, 1)) {
            return 0;
        }

        if ((D_80862B04 != 0) || func_80832F78(this, &sp24, &sp22, 0.018f, play)) {
            return 1;
        }
    }
    return -1;
}

void func_808332A0(PlayState* play, Player* this, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        this->unk_B08[0] = 0.0f;
    } else {
        this->unk_B08[0] = 0.5f;
    }

    this->stateFlags1 |= PLAYER_STATE1_1000;
    if ((this->actor.id == ACTOR_PLAYER) && ((arg3 != 0) || (this->transformation == PLAYER_FORM_HUMAN))) {
        s16 var_v1;
        Actor* actor;

        var_v1 = 0;
        if (arg3 != 0) {
            if (this->targetedActor != NULL) {
                var_v1 = Math_Vec3f_Pitch(this->bodyPartsPos, &this->targetedActor->focus.pos);
            }
            if (gSaveContext.save.playerData.magic == 0) {
                return;
            }
        }

        actor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_M_THUNDER, this->bodyPartsPos[0].x, this->bodyPartsPos[0].y,
                            this->bodyPartsPos[0].z, var_v1, 0, 0, (this->itemActionParam - 3) | arg2);

        if ((actor != NULL) && (arg3 != 0)) {
            func_80115DB4(play, 1, 7);
            this->unk_D57 = 4;
        }
    }
}

s32 func_808333CC(Player* this) {
    s8 sp24[4];
    s32 i;
    s32 j;
    s8 temp_a0;
    s8 temp_v1;
    s8* var_v0 = this->unk_ADF;
    s8* var_v1 = sp24;

    if (this->itemActionParam == PLAYER_AP_STICK) {
        return false;
    }

    i = 0;

    if (!this) {}

    while (true) {
        temp_a0 = *var_v0;
        i++;
        var_v0++;
        *var_v1 = temp_a0;
        if (temp_a0 < 0) {
            return false;
        }

        *var_v1 *= 2;
        var_v1++;

        if (i >= ARRAY_COUNT(this->unk_ADF)) {
            temp_v1 = sp24[0] - sp24[1];
            if (ABS_ALT(temp_v1) < 0xA) {
                return 0;
            }

            var_v1 = &sp24[1];
            j = 1;

            while (true) {
                j++;
                temp_a0 = var_v1[0] - var_v1[1];

                if ((ABS_ALT(temp_a0) < 0xA) || ((temp_a0 * temp_v1) < 0)) {
                    return false;
                }

                var_v1++;
                if (j == ARRAY_COUNT(sp24) - 1) {
                    return true;
                }
            }
        }
    }
}

void func_808334D4(PlayState* play, Player* this) {
    LinkAnimationHeader* anim;

    if ((this->meleeWeaponAnimation >= PLAYER_MWA_RIGHT_SLASH_1H) &&
        (this->meleeWeaponAnimation <= PLAYER_MWA_RIGHT_COMBO_2H)) {
        anim = D_8085CF58[Player_IsHoldingTwoHandedWeapon(this)];
    } else {
        anim = D_8085CF50[Player_IsHoldingTwoHandedWeapon(this)];
    }

    func_8082DC38(this);
    LinkAnimation_Change(play, &this->skelAnime, anim, 1.0f, 8.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE, -9.0f);
    func_808332A0(play, this, 0x200, 0);
}

void func_808335B0(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_8084CCEC, 1);
    func_808334D4(play, this);
}

s8 D_8085D090[] = {
    PLAYER_MWA_STAB_1H,
    PLAYER_MWA_RIGHT_SLASH_1H,
    PLAYER_MWA_RIGHT_SLASH_1H,
    PLAYER_MWA_LEFT_SLASH_1H,
};

s8 D_8085D094[][3] = {
    { PLAYER_MWA_ZORA_PUNCH_LEFT, PLAYER_MWA_ZORA_PUNCH_COMBO, PLAYER_MWA_ZORA_PUNCH_KICK },
    { PLAYER_MWA_GORON_PUNCH_LEFT, PLAYER_MWA_GORON_PUNCH_RIGHT, PLAYER_MWA_GORON_PUNCH_BUTT },
};

PlayerMeleeWeaponAnimation func_808335F4(Player* this) {
    s32 temp_a1;
    PlayerMeleeWeaponAnimation meleeWeaponAnimation;

    temp_a1 = this->unk_AE3[this->unk_ADE];
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_GORON)) {
        s32 requiredScopeTemp;

        // yikes
        meleeWeaponAnimation =
            ((this->transformation == PLAYER_FORM_ZORA) ? D_8085D094[0] : D_8085D094[1])[this->unk_ADD];

        if (this->unk_ADD != 0) {
            this->meleeWeaponAnimation = meleeWeaponAnimation;
            if (this->unk_ADD >= 2) {
                this->unk_ADD = -1;
            }
        }
    } else {
        if (func_808333CC(this)) {
            meleeWeaponAnimation = PLAYER_MWA_SPIN_ATTACK_1H;
        } else {
            if (temp_a1 < 0) {
                meleeWeaponAnimation = func_8082FBE8(this) ? PLAYER_MWA_FORWARD_SLASH_1H : PLAYER_MWA_RIGHT_SLASH_1H;
            } else {
                meleeWeaponAnimation = D_8085D090[temp_a1];
                if (meleeWeaponAnimation == PLAYER_MWA_STAB_1H) {
                    this->stateFlags2 |= PLAYER_STATE2_40000000;
                    if (!func_8082FBE8(this)) {
                        meleeWeaponAnimation = PLAYER_MWA_FORWARD_SLASH_1H;
                    }
                }
            }

            if (this->itemActionParam == PLAYER_AP_STICK) {
                meleeWeaponAnimation = PLAYER_MWA_FORWARD_SLASH_1H;
            }
        }

        if (Player_IsHoldingTwoHandedWeapon(this)) {
            meleeWeaponAnimation++;
        }
    }
    return meleeWeaponAnimation;
}

void func_80833728(Player* this, s32 index, u32 dmgFlags, s32 damage) {
    this->meleeWeaponQuads[index].info.toucher.dmgFlags = dmgFlags;
    this->meleeWeaponQuads[index].info.toucher.damage = damage;
    if (dmgFlags == 2) {
        this->meleeWeaponQuads[index].info.toucherFlags = (TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_WOOD);
    } else {
        this->meleeWeaponQuads[index].info.toucherFlags = (TOUCH_ON | TOUCH_NEAREST);
    }
}

struct_8085D09C D_8085D09C[] = {
    { 0x100, 2, 2, 0, 0 }, { 0x200, 4, 8, 1, 2 }, { 0x200, 4, 8, 2, 4 },    { 0x200, 4, 8, 3, 6 },
    { 0x200, 4, 8, 4, 8 }, { 2, 0, 0, 2, 4 },     { 0x800000, 1, 2, 0, 0 },
};

void func_8083375C(Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnimation) {
    struct_8085D09C* var_v0 = &D_8085D09C[0];
    s32 damage;

    if (this->actor.id == ACTOR_EN_TEST3) {
        meleeWeaponAnimation = PLAYER_MWA_GORON_PUNCH_LEFT;
        this->meleeWeaponAnimation = -1;
    } else {
        var_v0 = &D_8085D09C[(this->transformation == PLAYER_FORM_GORON) ? 0 : Player_GetMeleeWeaponHeld(this)];
    }

    damage = ((meleeWeaponAnimation >= PLAYER_MWA_FLIPSLASH_START) &&
              (meleeWeaponAnimation <= PLAYER_MWA_ZORA_JUMPKICK_FINISH))
                 ? ((this->transformation == PLAYER_FORM_HUMAN) ? var_v0->unk_7 : var_v0->unk_5)
                 : ((this->transformation == PLAYER_FORM_HUMAN) ? var_v0->unk_6 : var_v0->unk_4);

    func_80833728(this, 0, var_v0->dmgFlags, damage);
    func_80833728(this, 1, var_v0->dmgFlags, damage);
}

void func_80833864(PlayState* play, Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnimation) {
    func_8083375C(this, meleeWeaponAnimation);
    Player_SetAction(play, this, func_808548B8, 0);
    this->unk_AE8 = 0;

    if ((meleeWeaponAnimation < PLAYER_MWA_FLIPSLASH_FINISH) ||
        (meleeWeaponAnimation > PLAYER_MWA_ZORA_JUMPKICK_FINISH)) {
        func_8082DC38(this);
    }

    if ((meleeWeaponAnimation != this->meleeWeaponAnimation) || (this->unk_ADD >= 3)) {
        this->unk_ADD = 0;
    }

    this->unk_ADD++;
    if (this->unk_ADD >= 3) {
        meleeWeaponAnimation += 2;
    }

    this->meleeWeaponAnimation = meleeWeaponAnimation;
    func_8082DB90(play, this, D_8085CD30[meleeWeaponAnimation].unk_0);
    this->unk_ADC = this->skelAnime.animLength + 4.0f;

    if ((meleeWeaponAnimation < PLAYER_MWA_FLIPSLASH_START) ||
        (meleeWeaponAnimation > PLAYER_MWA_ZORA_JUMPKICK_START)) {
        func_8082E920(play, this, (1 | 8 | 0x10));
    }
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80833998(Player* this, s32 invincibilityTimer) {
    if (this->invincibilityTimer >= 0) {
        this->invincibilityTimer = invincibilityTimer;
        this->unk_B5F = 0;
    }
}

void func_808339B4(Player* this, s32 invincibilityTimer) {
    if (invincibilityTimer < this->invincibilityTimer) {
        this->invincibilityTimer = invincibilityTimer;
    }
    this->unk_B5F = 0;
}

s32 func_808339D4(PlayState* play, Player* this, s32 damage) {
    if ((this->invincibilityTimer != 0) || (this->stateFlags3 & PLAYER_STATE3_400000) ||
        (this->actor.id != ACTOR_PLAYER)) {
        return 1;
    }

    if (this->actor.category != ACTORCAT_PLAYER) {
        this->actor.colChkInfo.damage = -damage;
        return Actor_ApplyDamage(&this->actor);
    }

    if (this->currentMask == PLAYER_MASK_GIANT) {
        damage >>= 2;
    }

    return Health_ChangeBy(play, damage);
}

void func_80833A64(Player* this) {
    this->skelAnime.prevTransl = this->skelAnime.jointTable[0];
    func_8082E820(this, 3);
}

void func_80833AA0(Player* this, PlayState* play) {
    if (Player_SetAction(play, this, func_8084C16C, 0) != 0) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DD30);
        this->unk_AE8 = 1;
    }
    if (this->unk_AA5 != 4) {
        this->unk_AA5 = 0;
    }
}

LinkAnimationHeader* D_8085D0D4[] = {
    &gameplay_keep_Linkanim_00DCA0,
    &gameplay_keep_Linkanim_00DC98,
    &gameplay_keep_Linkanim_00DB00,
    &gameplay_keep_Linkanim_00DAF8,
};
LinkAnimationHeader* D_8085D0E4[] = {
    &gameplay_keep_Linkanim_00DC90,
    &gameplay_keep_Linkanim_00D418,
    &gameplay_keep_Linkanim_00DAE8,
    &gameplay_keep_Linkanim_00D3F0,
};

void func_80833B18(PlayState* play, Player* this, s32 arg2, f32 velocity, f32 yVelocity, s16 arg5,
                   s32 invincibilityTimer) {
    LinkAnimationHeader* anim = NULL;

    if (this->stateFlags1 & PLAYER_STATE1_2000) {
        func_80833A64(this);
    }

    this->unk_B64 = 0;
    func_800B8E58(this, NA_SE_PL_DAMAGE);

    if (func_808339D4(play, this, -this->actor.colChkInfo.damage) == 0) {
        this->stateFlags2 &= ~PLAYER_STATE2_80;
        if ((this->actor.bgCheckFlags & 1) || (this->stateFlags1 & PLAYER_STATE1_8000000)) {
            return;
        }
    }

    if (this->actor.colChkInfo.damage != 0) {
        func_80833998(this, invincibilityTimer);
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        return;
    }

    if (arg2 == 3) {
        Player_SetAction(play, this, func_808546D0, 0);
        anim = &gameplay_keep_Linkanim_00DCD0;
        func_8082DAD4(this);
        this->actor.velocity.y = 0.0f;

        Player_RequestRumble(play, this, 255, 10, 40, SQ(0));

        func_800B8E58(this, NA_SE_PL_FREEZE_S);
        func_8082DF8C(this, NA_SE_VO_LI_FREEZE);
    } else if (arg2 == 4) {
        Player_SetAction(play, this, func_80854800, 0);
        func_8082DB60(play, this, &gameplay_keep_Linkanim_00DC20);
        func_8082DAD4(this);
        this->unk_AE8 = 0x14;
        this->actor.velocity.y = 0.0f;

        Player_RequestRumble(play, this, 255, 80, 150, SQ(0));
    } else {
        arg5 -= this->actor.shape.rot.y;

        if (this->stateFlags1 & PLAYER_STATE1_8000000) {
            Player_SetAction(play, this, func_80851B58, 0);
            Player_RequestRumble(play, this, 180, 20, 50, SQ(0));

            if (arg2 == 1) {
                this->linearVelocity = velocity * 1.5f;
                this->actor.velocity.y = yVelocity * 0.7f;
            } else {
                this->linearVelocity = 4.0f;
                this->actor.velocity.y = 0.0f;
            }

            func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);
            anim = &gameplay_keep_Linkanim_00DFF8;
        } else if ((arg2 == 1) || (arg2 == 2) || !(this->actor.bgCheckFlags & 1) ||
                   (this->stateFlags1 &
                    (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000))) {
            Player_SetAction(play, this, func_8084BC64, 0);

            this->stateFlags3 |= PLAYER_STATE3_2;
            Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
            func_8082DAD4(this);

            if (arg2 == 2) {
                this->unk_AE8 = 4;
                this->actor.speedXZ = 3.0f;
                this->linearVelocity = 3.0f;
                this->actor.velocity.y = 6.0f;
                func_8082E5A8(play, this, D_8085BE84[PLAYER_ANIMGROUP_3][this->modelAnimType]);
                func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);
            } else {
                this->actor.speedXZ = velocity;
                this->linearVelocity = velocity;
                this->actor.velocity.y = yVelocity;

                if (ABS_ALT(arg5) > 0x4000) {
                    anim = &gameplay_keep_Linkanim_00DC78;
                } else {
                    anim = &gameplay_keep_Linkanim_00DAD0;
                }
                func_8082DF8C(this, NA_SE_VO_LI_FALL_L);
            }
            this->actor.bgCheckFlags &= ~1;
        } else if ((this->linearVelocity > 4.0f) && !func_80123420(this)) {
            this->unk_B64 = 0x14;
            Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
            func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);

            return;
        } else {
            LinkAnimationHeader** var_v1 = D_8085D0D4;

            Player_SetAction(play, this, func_8084BBF0, 0);
            func_8082FC60(this);

            if (this->actor.colChkInfo.damage < 5) {
                Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
            } else {
                Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
                this->linearVelocity = 23.0f;

                var_v1 = D_8085D0E4;
            }

            if (ABS_ALT(arg5) <= 0x4000) {
                var_v1 += 2;
            }

            if (func_80123420(this)) {
                var_v1++;
            }

            anim = *var_v1;
            func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);
        }

        this->actor.shape.rot.y += arg5;
        this->currentYaw = this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (ABS_ALT(arg5) > 0x4000) {
            this->actor.shape.rot.y += 0x8000;
        }
    }

    func_8082DE50(play, this);

    this->stateFlags1 |= PLAYER_STATE1_4000000;
    if (anim != NULL) {
        func_8082DB90(play, this, anim);
    }
}

s32 func_808340AC(s32 arg0) {
    s32 temp_v0 = arg0 - 2;

    if ((temp_v0 >= 0) && (temp_v0 <= 1)) {
        return temp_v0;
    }
    return -1;
}

s32 func_808340D4(s32 arg0) {
    return (arg0 == 4) || (arg0 == 7) || (arg0 == 12);
}

void func_80834104(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_8085421C, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000 | PLAYER_STATE1_80000000;
}

void func_80834140(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    if (!(this->stateFlags1 & PLAYER_STATE1_80)) {
        func_80834104(play, this);
        if (func_8082DA90(play)) {
            this->unk_AE8 = -30;
        }
        this->stateFlags1 |= PLAYER_STATE1_80;
        LinkAnimation_Change(play, &this->skelAnime, anim, 1.0f, 0.0f, 84.0f, ANIMMODE_ONCE, -6.0f);
        this->unk_AE7 = 1;
        this->linearVelocity = 0.0f;
    }
}

s32 func_808341F4(PlayState* play, Player* this) {
    f32 temp_fv0;
    f32 flameScale;
    f32 flameIntensity;
    s32 i;
    s32 timerStep;
    s32 spawnedFlame;
    s32 var_v0;
    s32 var_v1;
    u8* timerPtr;

    spawnedFlame = false;
    timerPtr = this->flameTimers;
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_DEKU)) {
        timerStep = 0;
        if (this->actor.bgCheckFlags & 1) {
            if (this->cylinder.base.ocFlags1 & 2) {
                Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
                this->linearVelocity = 0.0f;
            }
            func_80834140(play, this, &gameplay_keep_Linkanim_00D698);
        }
    } else {
        if (this->transformation == PLAYER_FORM_GORON) {
            var_v1 = 20;
        } else {
            var_v1 = (s32)(this->linearVelocity * 0.4f) + 1;
        }

        if (this->stateFlags2 & 8) {
            var_v0 = 100;
        } else {
            var_v0 = 0;
        }

        timerStep = var_v0 + var_v1;
    }

    for (i = 0; i < PLAYER_BODYPART_MAX; i++, timerPtr++) {
        if (*timerPtr <= timerStep) {
            *timerPtr = 0;
        } else {
            spawnedFlame = true;
            *timerPtr -= timerStep;
            if (*timerPtr > 20.0f) {
                temp_fv0 = (*timerPtr - 20.0f) * 0.01f;
                flameScale = CLAMP(temp_fv0, 0.19999999f, 0.2f);
            } else {
                flameScale = *timerPtr * 0.01f;
            }

            flameIntensity = (*timerPtr - 25.0f) * 0.02f;
            flameIntensity = CLAMP(flameIntensity, 0.0f, 1.0f);
            EffectSsFireTail_SpawnFlameOnPlayer(play, flameScale, i, flameIntensity);
        }
    }

    if (spawnedFlame) {
        func_800B8E58(this, NA_SE_EV_TORCH - SFX_FLAG);
        if ((play->gameplayFrames % 4) == 0) {
            Player_InflictDamage(play, -1);
        }
    } else {
        this->isBurning = false;
    }

    return this->stateFlags1 & PLAYER_STATE1_80;
}

s32 func_808344C0(PlayState* play, Player* this) {
    s32 i = 0;

    while (i < ARRAY_COUNT(this->flameTimers)) {
        this->flameTimers[i] = Rand_S16Offset(0, 200);
        i++;
    }

    this->isBurning = true;
    return func_808341F4(play, this);
}

s32 func_80834534(PlayState* play, Player* this) {
    func_8082DF8C(this, NA_SE_VO_LI_FALL_L);
    return func_808344C0(play, this);
}

s32 func_8083456C(PlayState* play, Player* this) {
    if (this->actor.colChkInfo.acHitEffect == 1) {
        return func_80834534(play, this);
    }
    return 0;
}

void func_808345A8(Player* this) {
    if ((this->invincibilityTimer > 0) && (this->invincibilityTimer < 20)) {
        this->invincibilityTimer = 20;
    }
}

void func_808345C8(void) {
    if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
        gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
    }
}

s32 func_80834600(Player* this, PlayState* play) {
    s32 pad74;
    s32 var_v0;

    if (this->unk_D6A != 0) {
        if (!Player_InBlockingCsMode(play, this)) {
            Player_InflictDamage(play, -0x10);
            this->unk_D6A = 0;
        }
    } else if ((var_v0 = ((Player_GetHeight(this) - 8.0f) < (this->unk_AB8 * this->actor.scale.y))) ||
               (this->actor.bgCheckFlags & 0x100) || (D_80862B08 == 9) || (this->stateFlags2 & 0x80000000)) {
        func_8082DF8C(this, 0x6805U);
        if (var_v0 != 0) {
            func_80169FDC(&play->state);
            func_808345C8();
            Scene_SetExitFade(play);
        } else {
            func_80169EFC(&play->state);
            func_808345C8();
        }
        func_8082DF8C(this, 0x680CU);
        play->unk_18845 = 1;
        play_sound(0x5801U);
    } else if ((this->unk_B75 != 0) && ((this->unk_B75 >= 3) || (this->invincibilityTimer == 0))) {
        u8 sp6C[] = { 0, 2, 1, 1 };
        if (func_8083456C(play, this) == 0) {

            if (this->unk_B75 == 4) {
                this->shockTimer = 40;
            }

            this->actor.colChkInfo.damage += this->unk_B74;
            func_80833B18(play, this, sp6C[this->unk_B75 - 1], this->unk_B78, this->unk_B7C, this->unk_B76, 0x14);
        }
    } else if ((this->shieldQuad.base.acFlags & 0x80) || (this->shieldCylinder.base.acFlags & 0x80) ||
               ((this->invincibilityTimer < 0) && (this->cylinder.base.acFlags & 2) &&
                (this->cylinder.info.acHitInfo != NULL) &&
                (this->cylinder.info.acHitInfo->toucher.dmgFlags != 0x20000000))) {
        LinkAnimationHeader* var_a2;
        s32 sp64;

        Player_RequestRumble(play, this, 0xB4, 0x14, 0x64, 0);
        if ((this->invincibilityTimer >= 0) && !Player_IsGoronOrDeku(this)) {
            sp64 = (func_8084B5C0 == this->actionFunc);
            if (func_801242B4(this) == 0) {
                Player_SetAction(play, this, func_8084BAA4, 0);
            }
            this->unk_AE7 = sp64;
            if ((s8)sp64 == 0) {
                func_8082F43C(play, this, func_80848A0C);
                var_a2 = (this->unk_B40 < 0.5f) ? D_8085CFD4[Player_IsHoldingTwoHandedWeapon(this)]
                                                : D_8085CFCC[Player_IsHoldingTwoHandedWeapon(this)];
                LinkAnimation_PlayOnce(play, &this->unk_284, var_a2);
            } else {
                Player_AnimationPlayOnce(play, this, D_8085CFDC[Player_IsHoldingTwoHandedWeapon(this)]);
            }
        }
        if (!(this->stateFlags1 & 0x206004)) {
            this->linearVelocity = -18.0f;
            this->currentYaw = this->actor.shape.rot.y;
        }
        return 0;
    } else if ((this->unk_D6B != 0) || (this->invincibilityTimer > 0) || (this->stateFlags1 & 0x04000000) ||
               (this->csMode != 0) || (this->meleeWeaponQuads[0].base.atFlags & 2) ||
               (this->meleeWeaponQuads[1].base.atFlags & 2) || (this->cylinder.base.atFlags & 2) ||
               (this->shieldCylinder.base.atFlags & 2)) {
        return 0;
    } else if (this->cylinder.base.acFlags & 2) {
        Actor* sp60 = this->cylinder.base.ac;
        s32 var_a2_2;

        if (sp60->flags & 0x01000000) {
            func_800B8E58(this, 0x83EU);
        }
        if (this->actor.colChkInfo.acHitEffect == 2) {
            var_a2_2 = 3;
        } else if (this->actor.colChkInfo.acHitEffect == 3) {
            var_a2_2 = 4;
        } else if (this->actor.colChkInfo.acHitEffect == 7) {
            var_a2_2 = 1;
            this->shockTimer = 40;
        } else if (this->actor.colChkInfo.acHitEffect == 9) {
            var_a2_2 = 1;
            if (func_80834534(play, this) != 0) {
                return 1;
            }
        } else if (((this->actor.colChkInfo.acHitEffect == 4) && (this->currentMask != 0x14)) ||
                   (this->stateFlags3 & 0x1000)) {
            var_a2_2 = 1;
        } else {
            var_a2_2 = 0;
            if (func_8083456C(play, this) != 0) {
                return 1;
            }
        }
        func_80833B18(play, this, var_a2_2, 4.0f, 5.0f, (s16)Actor_YawBetweenActors(sp60, &this->actor), 0x14);
    } else if (this->invincibilityTimer != 0) {
        return 0;
    } else {
        s32 sp58 = func_808340AC(D_80862B08);
        u32 sp54 = SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        s32 var_a1 = 0;
        s32 var_v1_2;
        s32 pad48;

        if ((sp58 < 0) || ((sp54 == 0) && (this->transformation == 1) && !(this->actor.depthInWater > 0.0f))) {
            var_a1 = (this->actor.wallPoly != NULL) &&
                     (SurfaceType_IsWallDamage(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId) != 0);
            if (var_a1 == 0) {
                goto label;
            }
        }
        var_v1_2 = (var_a1 != 0) ? this->actor.wallBgId : this->actor.floorBgId;
        if (((this->transformation == 3) || (this->transformation == 2)) &&
            ((sp58 >= 0) && (sp54 == 0) && !(this->stateFlags1 & 0x08000000) && (this->actor.bgCheckFlags & 1) &&
             (this->actor.depthInWater < -30.0f))) {
            func_80834534(play, this);
        } else {
            this->actor.colChkInfo.damage = 4;
            func_80833B18(play, this, (var_v1_2 == 0x32) ? 0 : 1, 4.0f, 5.0f,
                          (var_a1 != 0) ? this->actor.wallYaw : this->actor.shape.rot.y, 0x14);
            return 1;
        label:
            return 0;
        }
    }
    return 1;
}

void func_80834CD0(Player* this, f32 arg1, u16 sfxId) {
    this->actor.velocity.y = arg1 * D_8085C3E4;
    this->actor.bgCheckFlags &= ~1;

    if (sfxId != 0) {
        func_8082E188(this);
        func_8082DF8C(this, sfxId);
    }

    this->stateFlags1 |= PLAYER_STATE1_40000;
    this->fallStartHeight = this->actor.world.pos.y;
}

void func_80834D50(PlayState* play, Player* this, LinkAnimationHeader* anim, f32 arg3, u16 sfxId) {
    Player_SetAction(play, this, func_8084C16C, 1);
    if (anim != NULL) {
        func_8082DB90(play, this, anim);
    }
    func_80834CD0(this, arg3, sfxId);
}

void func_80834DB8(Player* this, LinkAnimationHeader* anim, f32 arg2, PlayState* play) {
    func_80834D50(play, this, anim, arg2, NA_SE_VO_LI_SWORD_N);
}

s32 func_80834DFC(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) &&
        ((this->transformation != PLAYER_FORM_DEKU) || func_801242B4(this) || (this->unk_B5C < 4)) &&
        !(this->stateFlags1 & PLAYER_STATE1_800) && (this->unk_B5C >= 2) &&
        (!(this->stateFlags1 & PLAYER_STATE1_8000000) || (this->wallHeight < this->ageProperties->unk_14))) {
        s32 var_v1 = false;
        LinkAnimationHeader* anim;
        f32 wallHeight;

        if (func_801242B4(this)) {
            f32 depth = (this->transformation == PLAYER_FORM_FIERCE_DEITY) ? 80.0f : 50.0f;

            if (this->actor.depthInWater < depth) {
                if ((this->unk_B5C < 2) || (this->ageProperties->unk_10 < this->wallHeight)) {
                    return false;
                }
            } else if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) || (this->unk_B5C >= 3)) {
                return false;
            }
        } else if (!(this->actor.bgCheckFlags & 1) ||
                   ((this->ageProperties->unk_14 <= this->wallHeight) && (this->stateFlags1 & PLAYER_STATE1_8000000))) {
            return false;
        }

        if ((this->actor.wallBgId != BGCHECK_SCENE) && (D_80862B0C & 0x40)) {
            if (this->unk_B5D >= 6) {
                this->stateFlags2 |= PLAYER_STATE2_4;
                if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                    var_v1 = true;
                }
            }
        } else if ((this->unk_B5D >= 6) || CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
            var_v1 = true;
        }

        if (var_v1) {
            Player_SetAction(play, this, func_8084D4EC, 0);
            wallHeight = this->wallHeight;

            if (this->ageProperties->unk_14 <= wallHeight) {
                anim = &gameplay_keep_Linkanim_00DA70;
                this->linearVelocity = 1.0f;
            } else {
                CollisionPoly* poly;
                s32 bgId;
                f32 wallPolyNormalX = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
                f32 wallPolyNormalZ = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);
                f32 var_fv1 = this->wallDistance + 0.5f; // wallDistance
                f32 yIntersect;
                s32 pad;

                this->stateFlags1 |= PLAYER_STATE1_4;

                if (func_801242B4(this)) {
                    wallHeight -= 60.0f * this->ageProperties->unk_08;
                    anim = &gameplay_keep_Linkanim_00DFC8;
                    this->stateFlags1 &= ~PLAYER_STATE1_8000000;
                } else if (this->ageProperties->unk_18 <= wallHeight) {
                    wallHeight -= 59.0f * this->ageProperties->unk_08;
                    anim = &gameplay_keep_Linkanim_00DA68;
                } else {
                    wallHeight -= 41.0f * this->ageProperties->unk_08;
                    anim = &gameplay_keep_Linkanim_00DA60;
                }

                this->unk_ABC -= wallHeight * 100.0f;

                this->actor.world.pos.x -= var_fv1 * wallPolyNormalX;
                this->actor.world.pos.y += this->wallHeight + 10.0f;
                this->actor.world.pos.z -= var_fv1 * wallPolyNormalZ;

                yIntersect =
                    BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &this->actor.world.pos);
                if ((this->actor.world.pos.y - yIntersect) <= 20.0f) {
                    this->actor.world.pos.y = yIntersect;
                    if (bgId != BGCHECK_SCENE) {
                        DynaPolyActor_SetRidingMovingStateByIndex(&play->colCtx, bgId);
                    }
                }

                func_8082DAD4(this);
                this->actor.velocity.y = 0.0f;
            }

            this->actor.bgCheckFlags |= 1;
            LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 1.3f);
            AnimationContext_DisableQueue(play);
            this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
            return true;
        }
    } else if ((this->actor.bgCheckFlags & 1) && (this->unk_B5C == 1) && (this->unk_B5D >= 3)) {
        f32 temp = (this->wallHeight * 0.08f) + 5.5f;

        func_80834DB8(this, &gameplay_keep_Linkanim_00DCD8, temp, play);
        this->linearVelocity = 2.5f;
        return true;
    }

    return false;
}

void func_80835324(PlayState* play, Player* this, f32 arg2, s16 arg3) {
    Player_SetAction(play, this, func_8084D820, 0);
    func_8082DD2C(play, this);
    this->unk_A86 = -1;
    this->unk_AE7 = 1;
    this->unk_AE8 = 1;
    this->unk_3A0.x = Math_SinS(arg3) * arg2 + this->actor.world.pos.x;
    this->unk_3A0.z = Math_CosS(arg3) * arg2 + this->actor.world.pos.z;
    Player_AnimationPlayOnce(play, this, func_8082ED20(this));
}

void func_808353DC(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_808508C8, 0);
    func_8082E634(play, this, &gameplay_keep_Linkanim_00E000);
}

s32 func_80835428(PlayState* play, Player* this) {
    if (!func_8082DA90(play) && (this->stateFlags1 & PLAYER_STATE1_80000000)) {
        func_80834104(play, this);
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DD30);
        func_8082DF8C(this, NA_SE_VO_LI_FALL_S);
        func_8019F128(NA_SE_OC_SECRET_WARP_IN);
        return true;
    }
    return false;
}

/**
 * The actual entrances each "return entrance" value can map to.
 * This is used by scenes that are shared between locations.
 *
 * This 1D array is split into groups of entrances.
 * The start of each group is indexed by `sReturnEntranceGroupIndices` values.
 * The resulting groups are then indexed by the spawn value.
 *
 * The spawn value (`PlayState.curSpawn`) is set to a different value depending on the entrance used to enter the
 * scene, which allows these dynamic "return entrances" to link back to the previous scene.
 *
 * Seems unused on MM
 */
u16 sReturnEntranceGroupData[] = {
    // 0xFE00
    /* 0 */ 0x1000,
};

/**
 * The values are indices into `sReturnEntranceGroupData` marking the start of each group
 */
u8 sReturnEntranceGroupIndices[] = {
    0, // 0xFE00
};

// subfunction of OoT's func_80839034
void func_808354A4(PlayState* play, s32 arg1, s32 arg2) {
    play->nextEntranceIndex = play->setupExitList[arg1];

    if (play->nextEntranceIndex == 0xFFFF) {
        gSaveContext.respawnFlag = 4;
        play->nextEntranceIndex = gSaveContext.respawn[RESPAWN_MODE_UNK_3].entranceIndex;
        play->transitionType = TRANS_TYPE_03;
        gSaveContext.nextTransitionType = TRANS_TYPE_03;
    } else if (play->nextEntranceIndex >= 0xFE00) {
        play->nextEntranceIndex =
            sReturnEntranceGroupData[sReturnEntranceGroupIndices[play->nextEntranceIndex - 0xFE00] + play->curSpawn];

        Scene_SetExitFade(play);
    } else {
        if (arg2) {
            gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = play->nextEntranceIndex;
            func_80169EFC(&play->state);
            gSaveContext.respawnFlag = -2;
        }

        gSaveContext.unk_3DBB = 1;
        Scene_SetExitFade(play);
    }

    play->transitionTrigger = TRANS_TRIGGER_START;
}

void func_808355D8(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_80833AA0(this, play);
    this->unk_AE8 = -2;
    func_8082E5EC(play, this, anim);
    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_CLOSE);
}

// related to grottos (?)
s32 func_8083562C(PlayState* play, Player* this, CollisionPoly* poly, s32 bgId) {
    u32 var_a3; // sp3C
    u32 temp_v0_3;
    s32 sp34;
    s32 sp30;

    if ((this == GET_PLAYER(play)) && !(this->stateFlags1 & PLAYER_STATE1_80) && !func_8082DA90(play) &&
        (this->csMode == PLAYER_CSMODE_0) && !(this->stateFlags1 & PLAYER_STATE1_1)) {
        var_a3 = 0;
        if (((poly != NULL) && (var_a3 = SurfaceType_GetSceneExitIndex(&play->colCtx, poly, bgId), (var_a3 != 0)) &&
             (((play->sceneNum != SCENE_GORONRACE) && (play->sceneNum != SCENE_DEKU_KING)) || ((s32)var_a3 < 3)) &&
             (((play->sceneNum != SCENE_20SICHITAI) && (play->sceneNum != SCENE_20SICHITAI2)) ||
              ((s32)var_a3 < 0x15)) &&
             ((play->sceneNum != SCENE_11GORONNOSATO) || ((s32)var_a3 < 6))) ||
            (func_808340D4(D_80862B08) && (this->unk_D5E == 0xC))) {
            sp34 = this->unk_D68 - (s32)this->actor.world.pos.y;
            if (!(this->stateFlags1 & (PLAYER_STATE1_800000 | PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
                !(this->actor.bgCheckFlags & 1) && (sp34 < 0x190) && (D_80862B18 > 100.0f)) {
                if ((this->unk_D5E != 5) && (this->unk_D5E != 0xC)) {
                    this->linearVelocity = 0.0f;
                }

                return false;
            } else {
                if (this->stateFlags3 & PLAYER_STATE3_1000000) {
                    func_808355D8(play, this, &gameplay_keep_Linkanim_00E2D8);
                }

                if (var_a3 == 0) {
                    func_80169EFC(&play->state);
                    Scene_SetExitFade(play);
                } else {
                    func_808354A4(play, var_a3 - 1, SurfaceType_GetSlope(&play->colCtx, poly, bgId) == 2);
                    if ((this->stateFlags1 & PLAYER_STATE1_8000000) && (this->unk_D5E == 5)) {
                        func_8019F128(NA_SE_OC_TUNAMI);
                        func_801A4058(5);
                        gSaveContext.seqIndex = 0xFF;
                        gSaveContext.nightSeqIndex = 0xFF;
                    } else if (!(this->actor.bgCheckFlags & 1) && (this->unk_D5E == 0xC)) {
                        func_8019F128(NA_SE_OC_SECRET_WARP_IN);
                    }

                    if (this->stateFlags1 & PLAYER_STATE1_800000) {
                        if (D_801BDAA0 != 0) {
                            D_801BDAA0 = 0;
                        } else {
                            D_801BDA9C = 1;
                        }
                    }
                }

                if (!(this->stateFlags1 & (PLAYER_STATE1_800000 | PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
                    (temp_v0_3 = func_800C99D4(&play->colCtx, poly, bgId), (temp_v0_3 != 0xA)) &&
                    ((sp34 < 0x64) || (this->actor.bgCheckFlags & 1))) {
                    if (temp_v0_3 == 0xB) {
                        func_8019F128(NA_SE_OC_SECRET_HOLE_OUT);
                        func_801A4058(5);
                        gSaveContext.seqIndex = 0xFF;
                        gSaveContext.nightSeqIndex = 0xFF;
                    } else {
                        func_8085B74C(play);
                    }
                } else if (!(this->actor.bgCheckFlags & 1)) {
                    func_8082DABC(this);
                }

                Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), 0x50);
                this->stateFlags1 |= PLAYER_STATE1_1 | PLAYER_STATE1_20000000;
                return true;
            }
        } else {
            if ((this->stateFlags1 & PLAYER_STATE1_8000000) && (this->actor.floorPoly == NULL)) {
                BgCheck_EntityRaycastFloor7(&play->colCtx, &this->actor.floorPoly, &sp30, &this->actor,
                                            &this->actor.world.pos);
                if (this->actor.floorPoly == NULL) {
                    func_80169EFC(&play->state);
                    return false;
                }
                //! FAKE
                if (0) {}
            }

            if (!(this->stateFlags1 & PLAYER_STATE1_80000000)) {
                if (((this->actor.world.pos.y < -4000.0f) ||
                     (((this->unk_D5E == 5) || (this->unk_D5E == 0xC) || (this->unk_D5E == 0xD)) &&
                      ((D_80862B18 < 100.0f) || (this->fallDistance > 400))))) {
                    if (this->actor.bgCheckFlags & 1) {
                        if (this->unk_D5E == 5) {
                            func_80169FDC(&play->state);
                            func_808345C8();
                        } else {
                            func_80169EFC(&play->state);
                        }
                        if (!SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
                            gSaveContext.respawnFlag = -5;
                        }

                        play->transitionType = TRANS_TYPE_04;
                        play_sound(NA_SE_OC_ABYSS);
                    } else {
                        if (this->stateFlags3 & PLAYER_STATE3_1000000) {
                            func_808355D8(play, this, &gameplay_keep_Linkanim_00E2D8);
                        }

                        if (this->unk_D5E == 0xD) {
                            Player_SetAction(play, this, func_808497A0, 0);
                            this->stateFlags1 |= PLAYER_STATE1_20000000;
                        } else {
                            func_80834104(play, this);
                            this->unk_AE8 = 0x270F;
                            if (this->unk_D5E == 5) {
                                this->unk_AE7 = -1;
                            } else {
                                this->unk_AE7 = 1;
                            }
                        }
                    }
                }
            }

            this->unk_D68 = this->actor.world.pos.y;
        }
    }

    return false;
}

void func_80835BC8(Player* this, Vec3f* translation, Vec3f* src, Vec3f* dst) {
    Lib_Vec3f_TranslateAndRotateY(translation, this->actor.shape.rot.y, src, dst);
}

void func_80835BF8(Vec3f* arg0, s16 arg1, f32 arg2, Vec3f* arg3) {
    arg3->x = Math_SinS(arg1) * arg2 + arg0->x;
    arg3->z = Math_CosS(arg1) * arg2 + arg0->z;
}

Actor* Player_SpawnFairy(PlayState* play, Player* this, Vec3f* translation, Vec3f* arg3, s32 elfParams) {
    Vec3f pos;

    func_80835BC8(this, translation, arg3, &pos);
    return Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELF, pos.x, pos.y, pos.z, 0, 0, 0, elfParams);
}

f32 func_80835CD8(PlayState* play, Player* this, Vec3f* arg2, Vec3f* pos, CollisionPoly** outPoly, s32* outBgId) {
    func_80835BC8(this, &this->actor.world.pos, arg2, pos);
    return BgCheck_EntityRaycastFloor5(&play->colCtx, outPoly, outBgId, &this->actor, pos);
}

f32 func_80835D2C(PlayState* play, Player* this, Vec3f* arg2, Vec3f* pos) {
    CollisionPoly* poly;
    s32 bgId;

    return func_80835CD8(play, this, arg2, pos, &poly, &bgId);
}

s32 func_80835D58(PlayState* play, Player* this, Vec3f* arg2, CollisionPoly** outPoly, s32* bgId, Vec3f* posResult) {
    Vec3f posA;
    Vec3f posB;

    posA.x = this->actor.world.pos.x;
    posA.y = this->actor.world.pos.y + arg2->y;
    posA.z = this->actor.world.pos.z;
    func_80835BC8(this, &this->actor.world.pos, arg2, &posB);

    return BgCheck_EntityLineTest2(&play->colCtx, &posA, &posB, posResult, outPoly, 1, 0, 0, 1, bgId, &this->actor);
}

Vec3f D_8085D100 = { 0.0f, 50.0f, 0.0f };

s32 func_80835DF8(PlayState* play, Player* this, CollisionPoly** outPoly, s32* outBgId) {
    Vec3f pos;
    f32 yIntersect = func_80835CD8(play, this, &D_8085D100, &pos, outPoly, outBgId);

    if ((*outBgId == BGCHECK_SCENE) && (fabsf(this->actor.world.pos.y - yIntersect) < 10.0f)) {
        func_800FAAB4(play, SurfaceType_GetLightSettingIndex(&play->colCtx, *outPoly, *outBgId));
        return true;
    }
    return false;
}

/**
 * PLAYER_DOORTYPE_STAIRCASE: DoorSpiral
 */
void func_80835EAC(PlayState* play, Player* this, Actor* door) {
    static Vec3f D_8085D10C = { 20.0f, 0.0f, 20.0f };
    DoorSpiral* doorStaircase = (DoorSpiral*)door;

    this->currentYaw = doorStaircase->actor.home.rot.y + 0x8000;
    this->actor.shape.rot.y = this->currentYaw;
    if (this->linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    }
    func_80835324(play, this, 50.0f, this->actor.shape.rot.y);

    this->unk_397 = this->doorType;
    this->unk_AE7 = 0;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    func_80835BF8(&doorStaircase->actor.world.pos, doorStaircase->actor.shape.rot.y, -140.0f, &this->unk_3A0);

    D_8085D10C.x = (this->doorDirection != 0) ? -400.0f : 400.0f;
    D_8085D10C.z = 200.0f;
    func_80835BC8(this, &this->unk_3A0, &D_8085D10C, &this->unk_3AC);

    doorStaircase->shouldClimb = true;
    func_8082DAD4(this);

    if (this->doorTimer != 0) {
        this->unk_AE8 = 0;
        func_8082E438(play, this, func_8082ED20(this));
        this->skelAnime.endFrame = 0.0f;
    } else {
        this->linearVelocity = 0.1f;
    }

    Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), 0x50);
    this->unk_3BA =
        play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&doorStaircase->actor)].sides[0].bgCamDataId;
    Actor_DisableLens(play);
    this->unk_B72 = NA_SE_PL_WALK_CONCRETE - SFX_FLAG;
}

/**
 * PLAYER_DOORTYPE_SLIDING: DoorShutter, BgOpenShutter
 */
void func_8083604C(PlayState* play, Player* this, Actor* door) {
    DoorSlidingActor* doorSliding = (DoorSlidingActor*)door;
    Vec3f sp38;

    this->currentYaw = doorSliding->dyna.actor.home.rot.y;
    if (this->doorDirection > 0) {
        this->currentYaw -= 0x8000;
    }
    this->actor.shape.rot.y = this->currentYaw;
    if (this->linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    }

    func_80835324(play, this, 50.0f, this->actor.shape.rot.y);
    this->unk_AE7 = 0;
    this->unk_397 = this->doorType;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    Actor_OffsetOfPointInActorCoords(&doorSliding->dyna.actor, &sp38, &this->actor.world.pos);

    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y,
                  (42.0f - fabsf(sp38.z)) * this->doorDirection, &this->actor.world.pos);
    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y, this->doorDirection * 20.0f,
                  &this->unk_3A0);
    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y, this->doorDirection * -120.0f,
                  &this->unk_3AC);

    doorSliding->unk_15C = 1;
    func_8082DAD4(this);

    if (this->doorTimer != 0) {
        this->unk_AE8 = 0;
        func_8082E438(play, this, func_8082ED20(this));
        this->skelAnime.endFrame = 0.0f;
    } else {
        this->linearVelocity = 0.1f;
    }

    if (doorSliding->dyna.actor.category == ACTORCAT_DOOR) {
        this->unk_3BA = (s16)play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&doorSliding->dyna.actor)]
                            .sides[this->doorDirection > 0 ? 0 : 1]
                            .bgCamDataId;
        Actor_DisableLens(play);
    }
}

LinkAnimationHeader* D_8085D118[] = {
    &gameplay_keep_Linkanim_00E1B8,
    &gameplay_keep_Linkanim_00E3C8,
    &gameplay_keep_Linkanim_00E280,
};
LinkAnimationHeader* D_8085D124[] = {
    &gameplay_keep_Linkanim_00E1C0,
    &gameplay_keep_Linkanim_00E3D0,
    &gameplay_keep_Linkanim_00E288,
};

/**
 * PLAYER_DOORTYPE_MINUS_1: EnDoor, EnDoorEtc, DoorShutter
 * PLAYER_DOORTYPE_0:
 * PLAYER_DOORTYPE_1: EnDoor
 * PLAYER_DOORTYPE_3:
 * PLAYER_DOORTYPE_5: EnDoor
 */
void func_80836258(PlayState* play, Player* this, Actor* door) {
    s32 temp = this->transformation - 1;
    LinkAnimationHeader* sp60;
    f32 temp_fv0; // sp5C
    DoorBaseActor* doorNormal = (DoorBaseActor*)door;
    CollisionPoly* sp54;
    s32 sp50;
    Vec3f sp44;
    s32 sp40;
    Camera* temp_a0_2;

    doorNormal->animIndex = this->transformation;

    if (this->doorDirection < 0) {
        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            sp60 = D_8085BE84[PLAYER_ANIMGROUP_8][this->modelAnimType];
        } else if (this->transformation == PLAYER_FORM_HUMAN) {
            sp60 = D_8085BE84[PLAYER_ANIMGROUP_9][this->modelAnimType];
        } else {
            sp60 = D_8085D118[temp];
        }
    } else {
        doorNormal->animIndex += 5;

        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            sp60 = D_8085BE84[PLAYER_ANIMGROUP_10][this->modelAnimType];
        } else if (this->transformation == PLAYER_FORM_HUMAN) {
            sp60 = D_8085BE84[PLAYER_ANIMGROUP_11][this->modelAnimType];
        } else {
            sp60 = D_8085D124[temp];
        }
    }

    Player_SetAction(play, this, func_8084E034, 0);
    this->stateFlags2 |= PLAYER_STATE2_800000;
    func_8082DE14(play, this);
    if (this->doorDirection < 0) {
        this->actor.shape.rot.y = doorNormal->dyna.actor.shape.rot.y;
    } else {
        this->actor.shape.rot.y = doorNormal->dyna.actor.shape.rot.y - 0x8000;
    }

    this->currentYaw = this->actor.shape.rot.y;
    temp_fv0 = this->doorDirection * 22.0f;
    func_80835BF8(&doorNormal->dyna.actor.world.pos, doorNormal->dyna.actor.shape.rot.y, temp_fv0,
                  &this->actor.world.pos);
    func_8082EC9C(play, this, sp60);

    if (this->doorTimer != 0) {
        this->skelAnime.endFrame = 0.0f;
    }

    func_8082DAD4(this);
    func_8082E920(play, this, 0x28F);
    doorNormal->unk_1A1 = 1;
    if (this->doorType != PLAYER_DOORTYPE_3) {
        sp40 = ENDOOR_GET_PARAMS_7(&doorNormal->dyna.actor);
        this->stateFlags1 |= PLAYER_STATE1_20000000;

        if (this->actor.category == ACTORCAT_PLAYER) {
            Actor_DisableLens(play);
            func_80835BF8(&doorNormal->dyna.actor.world.pos, doorNormal->dyna.actor.shape.rot.y, -temp_fv0, &sp44);
            sp44.y = doorNormal->dyna.actor.world.pos.y + 10.0f;
            BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &sp44);

            if (func_8083562C(play, this, sp54, 0x32)) {
                gSaveContext.entranceSpeed = 2.0f;
            } else if (sp40 != 7) {
                this->unk_AE7 = 38.0f * D_8085C3E8;
                temp_a0_2 = Play_GetCamera(play, 0);

                Camera_ChangeDoorCam(temp_a0_2, &doorNormal->dyna.actor,
                                     play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&doorNormal->dyna.actor)]
                                         .sides[(this->doorDirection > 0) ? 0 : 1]
                                         .bgCamDataId,
                                     0.0f, this->unk_AE7, 26.0f * D_8085C3E8, 10.0f * D_8085C3E8);
            }
        }
    }
}

// door stuff
s32 func_808365DC(Player* this, PlayState* play) {
    if ((gSaveContext.save.playerData.health != 0) && (this->doorType != PLAYER_DOORTYPE_0)) {
        if ((this->actor.category != ACTORCAT_PLAYER) ||
            ((((this->doorType < 0) && ActorCutscene_GetCanPlayNext(0x7C)) ||
              ((this->doorType > 0) && ActorCutscene_GetCanPlayNext(0x7D))) &&
             (!(this->stateFlags1 & PLAYER_STATE1_800) &&
              (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A) || (func_8085437C == this->actionFunc) ||
               (this->doorType == PLAYER_DOORTYPE_STAIRCASE) || (this->doorType == PLAYER_DOORTYPE_5))))) {
            Actor* doorActor = this->doorActor;
            Actor* var_v0_3;

            if (this->doorType < 0) {
                func_8085B460(play, doorActor);
                if (doorActor->textId == 0x1821) {
                    doorActor->flags |= ACTOR_FLAG_100;
                }
                return true;
            }

            gSaveContext.respawn[RESPAWN_MODE_DOWN].data = 0;

            if (this->doorType == PLAYER_DOORTYPE_STAIRCASE) {
                func_80835EAC(play, this, doorActor);
            } else if (this->doorType == PLAYER_DOORTYPE_SLIDING) {
                func_8083604C(play, this, doorActor);
            } else {
                func_80836258(play, this, doorActor);
            }

            if (this->actor.category == ACTORCAT_PLAYER) {
                this->unk_A86 = 0x7D;
                ActorCutscene_Start(this->unk_A86, &this->actor);
            }

            if (this->actor.category == ACTORCAT_PLAYER) {
                if ((this->doorType < PLAYER_DOORTYPE_3) && (doorActor->category == ACTORCAT_DOOR) &&
                    ((this->doorType != PLAYER_DOORTYPE_1) || (ENDOOR_GET_PARAMS_7(doorActor) != 7))) {
                    s8 roomNum = play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(doorActor)]
                                     .sides[(this->doorDirection > 0) ? 0 : 1]
                                     .room;

                    if ((roomNum >= 0) && (roomNum != play->roomCtx.currRoom.num)) {
                        Room_StartRoomTransition(play, &play->roomCtx, roomNum);
                    }
                }
            }

            doorActor->room = play->roomCtx.currRoom.num;
            if (((var_v0_3 = doorActor->child) != NULL) || ((var_v0_3 = doorActor->parent) != NULL)) {
                var_v0_3->room = play->roomCtx.currRoom.num;
            }
            return true;
        }
    }

    return false;
}

void func_80836888(Player* this, PlayState* play) {
    LinkAnimationHeader* anim;

    Player_SetAction(play, this, func_80849A9C, 1);

    if (this->unk_B40 < 0.5f) {
        anim = func_8082EF54(this);
        this->unk_B40 = 0.0f;
    } else {
        anim = func_8082EF9C(this);
        this->unk_B40 = 1.0f;
    }

    this->unk_B44 = this->unk_B40;
    Player_AnimationPlayLoop(play, this, anim);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_8083692C(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_80849DD0, 1);
    func_8082E438(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80836988(Player* this, PlayState* play) {
    if (func_80123420(this)) {
        func_80836888(this, play);
    } else if (func_80123434(this)) {
        func_8083692C(this, play);
    } else {
        func_8085B384(this, play);
    }
}

void func_808369F4(Player* this, PlayState* play) {
    void (*var_a2)(Player*, PlayState*);

    if (func_80123420(this)) {
        var_a2 = func_80849A9C;
    } else if (func_80123434(this)) {
        var_a2 = func_80849DD0;
    } else {
        var_a2 = func_80849FE0;
    }
    Player_SetAction(play, this, var_a2, 1);
}

void func_80836A5C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    if (func_80123420(this)) {
        this->unk_AE8 = 1;
    }
}

void func_80836A98(Player* this, LinkAnimationHeader* anim, PlayState* play) {
    func_80836A5C(this, play);
    func_8082EC9C(play, this, anim);
}

void func_80836AD8(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_80857BE8, 0);
    this->unk_B28 = 0;
    this->unk_B86[1] = 0;
    this->unk_AF0[0].x = 0.0f;
    this->unk_AF0[0].y = 0.0f;
    this->unk_AF0[0].z = 0.0f;
    this->unk_B08[0] = 0.0f;
    this->unk_B08[1] = 0.0f;
    func_800B8E58(this, NA_SE_PL_GORON_TO_BALL);
}

void func_80836B3C(PlayState* play, Player* this, f32 arg2) {
    this->currentYaw = this->actor.shape.rot.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->transformation == PLAYER_FORM_GORON) {
        func_80836AD8(play, this);
        LinkAnimation_Change(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_15][this->modelAnimType],
                             1.5f * D_8085C3E4, 0.0f, 6.0f, ANIMMODE_ONCE, 0.0f);
    } else {
        LinkAnimationHeader* anim;

        anim = D_8085BE84[PLAYER_ANIMGROUP_15][this->modelAnimType];
        Player_SetAction(play, this, func_8084C6EC, 0);
        LinkAnimation_Change(play, &this->skelAnime, anim, 1.25f * D_8085C3E4, arg2, Animation_GetLastFrame(anim),
                             ANIMMODE_ONCE, 0.0f);
    }
}

void func_80836C70(PlayState* play, Player* this, s32 bodyPartIndex) {
    static Vec3f D_8085D130 = { 0, 0, 0 };
    s32 i;

    for (i = 0; i < 4; i++) {
        Vec3f velocity;

        velocity.x = randPlusMinusPoint5Scaled(4.0f);
        velocity.y = Rand_ZeroFloat(2.0f);
        velocity.z = randPlusMinusPoint5Scaled(4.0f);
        D_8085D130.y = -0.2f;
        EffectSsHahen_Spawn(play, &this->bodyPartsPos[bodyPartIndex], &velocity, &D_8085D130, 0, 10, OBJECT_LINK_NUTS,
                            16, object_link_nuts_DL_008860);
    }
}

void func_80836D8C(Player* this) {
    this->actor.focus.rot.x = 0;
    this->actor.focus.rot.z = 0;
    this->unk_AAC.x = 0;
    this->unk_AAC.y = 0;
    this->unk_AAC.z = 0;
    this->unk_AB2.x = 0;
    this->unk_AB2.y = 0;
    this->unk_AB2.z = 0;
    this->actor.shape.rot.y = this->actor.focus.rot.y;
    this->currentYaw = this->actor.focus.rot.y;
}

s32 func_80836DC0(PlayState* play, Player* this) {
    if ((MREG(48) != 0) || func_800C9DDC(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        Player_SetAction(play, this, func_808561B0, 0);
        this->stateFlags1 &= ~(PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
        func_8082E438(play, this, &gameplay_keep_Linkanim_00E270);
        func_8082DABC(this);
        func_80836D8C(this);
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->unk_B48 = -2000.0f;
        this->actor.shape.shadowScale = 13.0f;
        func_8082E1F0(this, NA_SE_PL_DEKUNUTS_IN_GRD);
        return true;
    }

    return false;
}

void func_80836EA0(PlayState* play, u16 quakeSpeed, s16 verticalMag, s16 quakeCountdown) {
    s16 quake = Quake_Add(Play_GetCamera(play, CAM_ID_MAIN), 3);

    Quake_SetSpeed(quake, quakeSpeed);
    Quake_SetQuakeValues(quake, verticalMag, 0, 0, 0);
    Quake_SetCountdown(quake, quakeCountdown);
}

struct_8085D13C D_8085D13C[] = {
    { -8, 180, 40, 100, NA_SE_VO_LI_LAND_DAMAGE_S },
    { -16, 255, 140, 150, NA_SE_VO_LI_LAND_DAMAGE_S },
};

s32 func_80836F10(PlayState* play, Player* this) {
    s32 var_s0;

    if ((D_80862B08 == 6) || (D_80862B08 == 9) || (this->csMode != PLAYER_CSMODE_0)) {
        var_s0 = 0;
    } else {
        var_s0 = this->fallDistance;
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 1.0f);
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    if (var_s0 >= 400) {
        s32 index;
        struct_8085D13C* entry;

        if (this->fallDistance < 800) {
            index = 0;
        } else {
            index = 1;
        }

        func_800B8E58(this, NA_SE_PL_BODY_HIT);

        entry = &D_8085D13C[index];
        func_8082DF8C(this, entry->sfxId);

        if (Player_InflictDamage(play, entry->damage)) {
            return -1;
        }

        func_80833998(this, 40);
        func_80836EA0(play, 0x80C7, 2, 30);
        Player_RequestRumble(play, this, entry->sourceIntensity, entry->decayTimer, entry->decayStep, SQ(0));

        return index + 1;
    }

    if (var_s0 > 200) {
        var_s0 = var_s0 * 2;
        var_s0 = CLAMP_MAX(var_s0, 255);

        Player_RequestRumble(play, this, var_s0, var_s0 * 0.1f, var_s0, SQ(0));
        if (D_80862B08 == 6) {
            func_8082DF8C(this, NA_SE_VO_LI_CLIMB_END);
        }
    }

    func_8082E1BC(this);
    return 0;
}

s32 func_808370D4(PlayState* play, Player* this) {
    if ((this->fallDistance < 800) && (this->unk_AE3[this->unk_ADE] == 0) && !(this->stateFlags1 & PLAYER_STATE1_800)) {
        func_80836B3C(play, this, 0.0f);

        return true;
    }
    return false;
}

void func_80837134(PlayState* play, Player* this) {
    LinkAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_13][this->modelAnimType];
    s32 temp_v0_2; // sp28

    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    if (this->transformation == PLAYER_FORM_DEKU) {
        s32 var_v1 = false;

        if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00E2E8) ||
            (this->skelAnime.animation == &gameplay_keep_Linkanim_00E2D8)) {
            func_80836C70(play, this, 0xC);
            func_80836C70(play, this, 0xF);
            var_v1 = true;
        }

        if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A) && func_80836DC0(play, this)) {
            return;
        }

        if (var_v1) {
            func_80836A98(this, anim, play);
            func_8082E1BC(this);
            return;
        }
    } else if (this->stateFlags2 & PLAYER_STATE2_80000) {
        if (func_80123420(this)) {
            anim = D_8085C2A4[this->unk_AE7].unk_8;
        } else {
            anim = D_8085C2A4[this->unk_AE7].unk_4;
        }
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DE48) {
        anim = &gameplay_keep_Linkanim_00DE50;
    } else if (func_80123420(this)) {
        anim = &gameplay_keep_Linkanim_00D420;
        func_8082FC60(this);
    } else if (this->fallDistance <= 80) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_14][this->modelAnimType];
    } else if (func_808370D4(play, this)) {
        return;
    }

    temp_v0_2 = func_80836F10(play, this);
    if (temp_v0_2 > 0) {
        func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_13][this->modelAnimType], play);
        this->skelAnime.endFrame = 8.0f;

        if (temp_v0_2 == 1) {
            this->unk_AE8 = 0xA;
        } else {
            this->unk_AE8 = 0x14;
        }
    } else if (temp_v0_2 == 0) {
        func_80836A98(this, anim, play);
    }
}

void func_808373A4(PlayState* play, Player* this) {
    func_8082E438(play, this, &gameplay_keep_Linkanim_00E270);
    this->unk_B10[0] = 20000.0f;
    this->unk_B10[1] = 0x30000;
    func_800B8E58(this, NA_SE_PL_DEKUNUTS_ATTACK);
}

// related to Deku hopping
s32 func_808373F8(PlayState* play, Player* this, u16 sfxId) {
    LinkAnimationHeader* anim;
    f32 speed;
    s16 yawDiff = this->currentYaw - this->actor.shape.rot.y;

    if ((IREG(66) / 100.0f) < this->linearVelocity) {
        speed = IREG(67) / 100.0f;
    } else {
        speed = (IREG(68) / 100.0f + (IREG(69) * this->linearVelocity) / 1000.0f);

        if ((this->transformation == PLAYER_FORM_DEKU) && (speed < 8.0f)) {
            speed = 8.0f;
        } else if (speed < 5.0f) {
            speed = 5.0f;
        }
    }

    if ((ABS_ALT(yawDiff) >= 0x1000) || (this->linearVelocity <= 4.0f)) {
        anim = &gameplay_keep_Linkanim_00DCD8;
    } else {
        s32 var_v1;

        if ((this->transformation != PLAYER_FORM_DEKU) && (((D_80862B1C == 1)) || (D_80862B1C == 2))) {
            if (D_80862B1C == 1) {
                var_v1 = 4;
            } else {
                var_v1 = 5;
            }

            func_80834D50(play, this, D_8085C2A4[var_v1].unk_0, speed, ((var_v1 == 4) ? NA_SE_VO_LI_SWORD_N : sfxId));
            this->unk_AE8 = -1;
            this->stateFlags2 |= PLAYER_STATE2_80000;
            this->unk_AE7 = var_v1;
            return 1;
        }
        anim = &gameplay_keep_Linkanim_00DE48;
    }

    // Deku hopping
    if (this->transformation == PLAYER_FORM_DEKU) {
        speed *= 0.3f + ((5 - this->unk_B67) * 0.18f);
        if (speed < 4.0f) {
            speed = 4.0f;
        }

        if ((this->actor.depthInWater > 0.0f) && (this->unk_B67 != 0)) {
            this->actor.world.pos.y += this->actor.depthInWater;
            func_80834D50(play, this, anim, speed, 0);
            this->unk_AE8 = 1;
            this->stateFlags3 |= PLAYER_STATE3_200000;
            func_800B8E58(this, (NA_SE_PL_DEKUNUTS_JUMP5 + 1 - this->unk_B67));
            func_8082DF8C(this, sfxId);
            this->unk_B67--;
            if (this->unk_B67 == 0) {
                this->stateFlags2 |= PLAYER_STATE2_80000;
                func_808373A4(play, this);
            }
            return 1;
        }

        if (this->actor.velocity.y > 0.0f) {
            sfxId = 0;
        }
    }

    func_80834D50(play, this, anim, speed, sfxId);
    this->unk_AE8 = 1;

    return 1;
}

s32 func_80837730(PlayState* play, Player* this, f32 arg2, s32 arg3) {
    f32 sp3C = fabsf(arg2);

    if (sp3C > 2.0f) {
        WaterBox* sp38;
        f32 sp34;
        Vec3f sp28;

        Math_Vec3f_Copy(&sp28, this->bodyPartsPos);
        sp28.y += 20.0f;
        if (WaterBox_GetSurface1(play, &play->colCtx, sp28.x, sp28.z, &sp28.y, &sp38)) {
            sp34 = sp28.y - this->bodyPartsPos[6].y;
            if ((sp34 > -2.0f) && (sp34 < 100.0f)) {
                EffectSsGSplash_Spawn(play, &sp28, NULL, NULL, (sp3C <= 10.0f) ? 0 : 1, arg3);
                return true;
            }
        }
    }

    return false;
}

s32 func_8083784C(Player* this) {
    if (this->actor.velocity.y < 0.0f) {
        if ((this->actor.depthInWater > 0.0f) &&
            ((this->ageProperties->unk_2C - this->actor.depthInWater) < D_80862B18)) {
            if ((this->unk_B67 != 0) && (gSaveContext.save.playerData.health != 0) &&
                !(this->stateFlags1 & PLAYER_STATE1_4000000)) {
                if (((this->talkActor == NULL) || !(this->talkActor->flags & ACTOR_FLAG_10000))) {
                    return true;
                }
            }
        }
    }

    return false;
}

void func_808378FC(PlayState* play, Player* this) {
    if (!func_8082FC24(this)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
    }

    if (func_8083784C(this) && func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP)) {
        func_80837730(play, this, 20.0f, this->actor.velocity.y * 50.0f);
    }
}

s32 func_8083798C(Player* this) {
    return (this->interactRangeActor != NULL) && (this->heldActor == NULL) &&
           (this->transformation != PLAYER_FORM_DEKU);
}

void func_808379C0(PlayState* play, Player* this) {
    if (func_8083798C(this)) {
        Actor* interactRangeActor = this->interactRangeActor;
        LinkAnimationHeader* anim;

        if ((interactRangeActor->id == ACTOR_EN_ISHI) && (ENISHI_GET_1(interactRangeActor) != 0)) {
            Player_SetAction(play, this, func_8084E334, 0);
            anim = &gameplay_keep_Linkanim_00DF90;
        } else if (((interactRangeActor->id == ACTOR_EN_BOMBF) || (interactRangeActor->id == ACTOR_EN_KUSA) ||
                    (interactRangeActor->id == ACTOR_EN_KUSA2) || (interactRangeActor->id == ACTOR_OBJ_GRASS_CARRY)) &&
                   (Player_GetStrength() <= PLAYER_STRENGTH_DEKU)) {
            Player_SetAction(play, this, func_8084E4E4, 0);
            anim = &gameplay_keep_Linkanim_00DD70;

            this->actor.world.pos.x =
                (Math_SinS(interactRangeActor->yawTowardsPlayer) * 20.0f) + interactRangeActor->world.pos.x;
            this->actor.world.pos.z =
                (Math_CosS(interactRangeActor->yawTowardsPlayer) * 20.0f) + interactRangeActor->world.pos.z;

            this->currentYaw = this->actor.shape.rot.y = interactRangeActor->yawTowardsPlayer + 0x8000;
        } else {
            Player_SetAction(play, this, func_8084E25C, 0);
            anim = D_8085BE84[PLAYER_ANIMGROUP_12][this->modelAnimType];
        }

        Player_AnimationPlayOnce(play, this, anim);
    } else {
        func_80836988(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_800;
    }
}

void func_80837B60(PlayState* play, Player* this) {
    func_8083172C(play, this, func_8084E980, 0);

    this->exchangeItemId = PLAYER_AP_NONE;
    this->stateFlags1 |= (PLAYER_STATE1_40 | PLAYER_STATE1_20000000);
    if (this->actor.textId != 0) {
        Message_StartTextbox(play, this->actor.textId, this->talkActor);
    }
    this->targetedActor = this->talkActor;
}

void func_80837BD0(PlayState* play, Player* this) {
    func_8083172C(play, this, func_8084FE7C, 0);
}

void func_80837BF8(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_8084ED9C, 0);
}

void func_80837C20(PlayState* play, Player* this) {
    s32 sp1C = this->unk_AE8;
    s32 sp18 = this->unk_AE7;

    func_8083172C(play, this, func_8084F4E8, 0);
    this->actor.velocity.y = 0.0f;
    this->unk_AE8 = sp1C;
    this->unk_AE7 = sp18;
}

void func_80837C78(PlayState* play, Player* this) {
    func_8083172C(play, this, func_80852C04, 0);
    this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_20000000);

    if (this->getItemId == GI_HEART_CONTAINER) {
        this->unk_AE8 = 20;
    } else if (this->getItemId >= GI_NONE) {
        this->unk_AE8 = 1;
    } else {
        this->getItemId = -this->getItemId;
    }
}

void func_80837CEC(PlayState* play, Player* this, CollisionPoly* arg2, f32 arg3, LinkAnimationHeader* anim) {
    f32 sp24 = arg2->normal.x * SHT_MINV;
    f32 sp20 = arg2->normal.z * SHT_MINV;

    Player_SetAction(play, this, func_8084F1B8, 0);
    func_8082DE50(play, this);
    Player_AnimationPlayOnce(play, this, anim);

    this->actor.world.pos.x -= (arg3 + 1.0f) * sp24;
    this->actor.world.pos.z -= (arg3 + 1.0f) * sp20;
    this->actor.shape.rot.y = Math_FAtan2F(sp20, sp24);

    this->currentYaw = this->actor.shape.rot.y;
    func_8082DAD4(this);
    this->actor.velocity.y = 0.0f;
    func_8082E6D0(this);
}

s32 func_80837DEC(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) && (this->transformation != PLAYER_FORM_DEKU) &&
        (this->actor.depthInWater < -80.0f)) {
        if ((ABS_ALT(this->unk_B6C)) < 0xAAA && (ABS_ALT(this->unk_B6E) < 0xAAA)) {
            CollisionPoly* sp94;
            CollisionPoly* sp90;
            s32 sp8C;
            s32 sp88;
            Vec3f sp7C;
            Vec3f sp70;
            f32 temp_fv1_2;
            f32 entityNormalX;
            f32 entityNormalY;
            f32 entityNormalZ;
            f32 temp_fv0_2;
            f32 var_fv1;

            sp7C.x = this->actor.prevPos.x - this->actor.world.pos.x;
            sp7C.z = this->actor.prevPos.z - this->actor.world.pos.z;

            var_fv1 = sqrtf(SQ(sp7C.x) + SQ(sp7C.z));
            if (var_fv1 != 0.0f) {
                var_fv1 = 5.0f / var_fv1;
            } else {
                var_fv1 = 0.0f;
            }

            sp7C.x = this->actor.prevPos.x + (sp7C.x * var_fv1);
            sp7C.y = this->actor.world.pos.y;
            sp7C.z = this->actor.prevPos.z + (sp7C.z * var_fv1);

            if (BgCheck_EntityLineTest2(&play->colCtx, &this->actor.world.pos, &sp7C, &sp70, &sp94, 1, 0, 0, 1, &sp8C,
                                        &this->actor)) {
                if (ABS_ALT(sp94->normal.y) < 0x258) {
                    s32 var_v1_2; // sp54

                    entityNormalX = COLPOLY_GET_NORMAL(sp94->normal.x);
                    entityNormalY = COLPOLY_GET_NORMAL(sp94->normal.y);
                    entityNormalZ = COLPOLY_GET_NORMAL(sp94->normal.z);

                    temp_fv0_2 = Math3D_UDistPlaneToPos(entityNormalX, entityNormalY, entityNormalZ, sp94->dist,
                                                        &this->actor.world.pos);

                    sp70.x = this->actor.world.pos.x - ((temp_fv0_2 + 1.0f) * entityNormalX);
                    sp70.z = this->actor.world.pos.z - ((temp_fv0_2 + 1.0f) * entityNormalZ);
                    sp70.y = this->actor.world.pos.y + 26.800001f;

                    temp_fv1_2 = this->actor.world.pos.y -
                                 BgCheck_EntityRaycastFloor5(&play->colCtx, &sp90, &sp88, &this->actor, &sp70);
                    if ((temp_fv1_2 >= -11.0f) && (temp_fv1_2 <= 0.0f)) {
                        var_v1_2 = D_80862B1C == 6;
                        if (!var_v1_2) {
                            if (func_800C9A4C(&play->colCtx, sp94, sp8C) & 8) {
                                var_v1_2 = true;
                            }
                        }

                        func_80837CEC(play, this, sp94, temp_fv0_2,
                                      (var_v1_2) ? &gameplay_keep_Linkanim_00DAA8 : &gameplay_keep_Linkanim_00DC30);
                        if (var_v1_2) {
                            func_80832558(play, this, func_80837C20);

                            this->actor.shape.rot.y = this->currentYaw += 0x8000;
                            this->stateFlags1 |= PLAYER_STATE1_200000;
                            func_8082E920(play, this, 1 | 2 | 4 | 8 | 0x10 | 0x80);
                            this->unk_AE8 = -1;
                            this->unk_AE7 = var_v1_2;
                        } else {
                            this->stateFlags1 |= PLAYER_STATE1_2000;
                            this->stateFlags1 &= ~PLAYER_STATE1_20000;
                        }

                        func_800B8E58(this, NA_SE_PL_SLIPDOWN);
                        func_8082DF8C(this, NA_SE_VO_LI_HANG);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void func_808381A0(Player* this, LinkAnimationHeader* anim, PlayState* play) {
    Player_SetAction(play, this, func_8084F3DC, 0);
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 1.3f);
}

Vec3f D_8085D148 = { 0.0f, 50.0f, 0.0f };

s32 func_808381F8(PlayState* play, Player* this) {
    CollisionPoly* poly;
    s32 bgId;
    Vec3f pos;
    f32 yIntersect;

    func_80835BC8(this, &this->actor.prevPos, &D_8085D148, &pos);

    yIntersect = BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &pos);

    return fabsf(yIntersect - this->actor.world.pos.y) < 10.0f;
}

Vec3f D_8085D154 = { 0.0f, 0.0f, 100.0f };

void func_8083827C(Player* this, PlayState* play) {
    s32 temp_t0; // sp64
    CollisionPoly* sp60;
    s32 sp5C;
    WaterBox* sp58;
    Vec3f sp4C;
    f32 sp48;
    f32 sp44;

    this->fallDistance = this->fallStartHeight - (s32)this->actor.world.pos.y;
    if (!(this->stateFlags1 & (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
        ((this->stateFlags1 & PLAYER_STATE1_80000000) ||
         !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) &&
        !(this->actor.bgCheckFlags & 1)) {
        if (func_80835428(play, this)) {
            return;
        }

        if (D_80862B1C == 8) {
            this->actor.world.pos.x = this->actor.prevPos.x;
            this->actor.world.pos.z = this->actor.prevPos.z;
            return;
        }

        if ((this->stateFlags3 & PLAYER_STATE3_2) || (this->skelAnime.moveFlags & 0x80)) {
            return;
        }

        if ((func_8084C16C == this->actionFunc) || (func_8084C94C == this->actionFunc) ||
            (func_8084CA24 == this->actionFunc) || (func_80857BE8 == this->actionFunc) ||
            (func_808546D0 == this->actionFunc) || (func_80854800 == this->actionFunc)) {
            return;
        }

        if ((D_80862B1C == 7) || (this->meleeWeaponState != PLAYER_MWA_FORWARD_SLASH_1H) ||
            ((this->skelAnime.moveFlags & 8) && func_808381F8(play, this))) {
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
            if (this->linearVelocity > 0.0f) {
                func_8082DABC(this);
            }
            this->actor.bgCheckFlags |= 2;
            return;
        }

        temp_t0 = BINANG_SUB(this->currentYaw, this->actor.shape.rot.y);
        Player_SetAction(play, this, func_8084C16C, 1);
        func_8082DD2C(play, this);

        this->unk_B72 = this->unk_D66;
        if ((this->transformation != PLAYER_FORM_GORON) &&
            ((this->transformation != PLAYER_FORM_DEKU) || (this->unk_B67 != 0)) && (this->actor.bgCheckFlags & 4)) {
            if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
                if ((D_80862B1C != 6) && (D_80862B1C != 9) && (D_80862B18 > 20.0f) &&
                    (this->meleeWeaponState == PLAYER_MWA_FORWARD_SLASH_1H)) {
                    if ((ABS_ALT(temp_t0) < 0x2000) && (this->linearVelocity > 3.0f)) {
                        if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                            if (((this->transformation == PLAYER_FORM_ZORA) &&
                                 CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) ||
                                ((D_80862B1C == 0xB) && (this->transformation != PLAYER_FORM_GORON) &&
                                 (this->transformation != PLAYER_FORM_DEKU))) {
                                sp48 = func_80835CD8(play, this, &D_8085D154, &sp4C, &sp60, &sp5C);
                                sp44 = this->actor.world.pos.y;
                                if (WaterBox_GetSurface1(play, &play->colCtx, sp4C.x, sp4C.z, &sp44, &sp58) &&
                                    ((sp44 - sp48) > 50.0f)) {
                                    func_80834DB8(this, &gameplay_keep_Linkanim_00DE58, 6.0f, play);
                                    Player_SetAction(play, this, func_8084C94C, 0);
                                    return;
                                }
                            }
                        }
                        func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                        return;
                    }
                }
            }
        }

        // Checking if the ledge is tall enough for Player to hang from
        if ((D_80862B1C == 9) || (D_80862B18 <= this->ageProperties->unk_34) || !func_80837DEC(this, play)) {
            Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DD30);
        }
    } else {
        this->fallStartHeight = this->actor.world.pos.y;
        this->unk_B67 = 5;
    }
}

s32 func_8083868C(PlayState* play, Player* this) {
    s32 camMode;
    Camera* camera;

    if (this->unk_AA5 == 3) {
        if (func_800B7118(this)) {
            if (this->transformation == PLAYER_FORM_HUMAN) {
                camMode = CAM_MODE_SLINGSHOT;
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                camMode = CAM_MODE_DEKUSHOOT;
            } else {
                camMode = CAM_MODE_BOWARROW;
            }
        } else {
            camMode = CAM_MODE_ZORAFIN;
        }
    } else {
        camMode = CAM_MODE_FIRSTPERSON;
    }

    camera = (this->actor.id == ACTOR_PLAYER) ? Play_GetCamera(play, CAM_ID_MAIN)
                                              : Play_GetCamera(play, ((EnTest3*)this)->unk_D8E);

    return Camera_ChangeMode(camera, camMode);
}

void func_80838760(Player* this) {
    if (this->unk_A86 >= 0) {
        ActorCutscene_Stop(this->unk_A86);
        this->unk_A86 = -1;
    }
}

s32 func_808387A0(PlayState* play, Player* this) {
    if (this->unk_AA5 == 4) {
        func_80838760(this);
        this->actor.flags &= ~ACTOR_FLAG_100;
        Player_SetAction(play, this, func_8085B08C, 0);
        if (this->unk_3BA != 0) {
            this->stateFlags1 |= PLAYER_STATE1_20000000;
        }
        func_8082DC38(this);

        return true;
    }
    return false;
}

void func_80838830(Player* this, s16 objectId) {
    s32 pad[2];

    if (objectId != OBJECT_UNSET_0) {
        this->giObjectLoading = true;
        osCreateMesgQueue(&this->giObjectLoadQueue, &this->giObjectLoadMsg, 1);
        DmaMgr_SendRequestImpl(&this->giObjectDmaRequest, this->giObjectSegment, gObjectTable[objectId].vromStart,
                               gObjectTable[objectId].vromEnd - gObjectTable[objectId].vromStart, 0,
                               &this->giObjectLoadQueue, NULL);
    }
}

LinkAnimationHeader* D_8085D160[PLAYER_FORM_MAX] = {
    &gameplay_keep_Linkanim_00E400, &gameplay_keep_Linkanim_00E210, &gameplay_keep_Linkanim_00E400,
    &gameplay_keep_Linkanim_00E2E0, &gameplay_keep_Linkanim_00D0C8,
};

void func_808388B8(PlayState* play, Player* this, PlayerTransformation playerForm) {
    func_8082DE50(play, this);
    func_80831760(play, this, func_808553F4, 0);
    func_8082E4A4(play, this, D_8085D160[this->transformation]);
    gSaveContext.save.playerForm = playerForm;
    this->stateFlags1 |= PLAYER_STATE1_2;

    D_80862B50 = play->envCtx.lightSettings;
    this->actor.velocity.y = 0.0f;
    Actor_DisableLens(play);
}

void func_808389BC(PlayState* play, Player* this) {
    func_80831760(play, this, func_80855AF4, 0);
    func_8082E4A4(play, this, &gameplay_keep_Linkanim_00D0C8);
    this->stateFlags1 |= (PLAYER_STATE1_100 | PLAYER_STATE1_20000000);
    func_8082DAD4(this);
}

void func_80838A20(PlayState* play, Player* this) {
    func_80831760(play, this, func_80855B9C, 0);
    func_8082DB90(play, this, &gameplay_keep_Linkanim_00D0A8);
    this->currentMask = PLAYER_MASK_NONE;
    this->stateFlags1 |= (PLAYER_STATE1_100 | PLAYER_STATE1_20000000);
    func_8082DAD4(this);
    func_80115D5C(&play->state);
}

// sPlayerMass
u8 D_8085D174[PLAYER_FORM_MAX] = {
    100, // PLAYER_FORM_FIERCE_DEITY
    200, // PLAYER_FORM_GORON
    80,  // PLAYER_FORM_ZORA
    20,  // PLAYER_FORM_DEKU
    50,  // PLAYER_FORM_HUMAN
};

LinkAnimationHeader* D_8085D17C[PLAYER_FORM_MAX] = {
    &gameplay_keep_Linkanim_00DDB0, &gameplay_keep_Linkanim_00E1F8, &gameplay_keep_Linkanim_00E3E8,
    &gameplay_keep_Linkanim_00E2B0, &gameplay_keep_Linkanim_00DDB0,
};
LinkAnimationHeader* D_8085D190[PLAYER_FORM_MAX] = {
    &gameplay_keep_Linkanim_00DDB8, &gameplay_keep_Linkanim_00E1F0, &gameplay_keep_Linkanim_00E3E0,
    &gameplay_keep_Linkanim_00E2A8, &gameplay_keep_Linkanim_00DDB8,
};

u8 D_8085D1A4[PLAYER_AP_MAX] = {
    GI_NONE,                // PLAYER_AP_NONE
    GI_NONE,                // PLAYER_AP_LAST_USED
    GI_NONE,                // PLAYER_AP_FISHING_POLE
    GI_SWORD_KOKIRI,        // PLAYER_AP_SWORD_KOKIRI
    GI_SWORD_RAZOR,         // PLAYER_AP_SWORD_RAZOR
    GI_SWORD_GILDED,        // PLAYER_AP_SWORD_GILDED
    GI_SWORD_GREAT_FAIRY,   // PLAYER_AP_SWORD_GREAT_FAIRY
    GI_STICKS_1,            // PLAYER_AP_STICK
    GI_SWORD_KOKIRI,        // PLAYER_AP_ZORA_FINS
    GI_QUIVER_30,           // PLAYER_AP_BOW
    GI_ARROW_FIRE,          // PLAYER_AP_BOW_FIRE
    GI_ARROW_ICE,           // PLAYER_AP_BOW_ICE
    GI_ARROW_LIGHT,         // PLAYER_AP_BOW_LIGHT
    GI_HOOKSHOT,            // PLAYER_AP_HOOKSHOT
    GI_BOMBS_1,             // PLAYER_AP_BOMB
    GI_POWDER_KEG,          // PLAYER_AP_POWDER_KEG
    GI_BOMBCHUS_10,         // PLAYER_AP_BOMBCHU
    GI_40,                  // PLAYER_AP_11
    GI_NUTS_1,              // PLAYER_AP_NUT
    GI_PICTO_BOX,           // PLAYER_AP_PICTO_BOX
    GI_OCARINA,             // PLAYER_AP_OCARINA
    GI_BOTTLE,              // PLAYER_AP_BOTTLE
    GI_FISH,                // PLAYER_AP_BOTTLE_FISH
    GI_75,                  // PLAYER_AP_BOTTLE_SPRING_WATER
    GI_ICE_TRAP,            // PLAYER_AP_BOTTLE_HOT_SPRING_WATER
    GI_ZORA_EGG,            // PLAYER_AP_BOTTLE_ZORA_EGG
    GI_GOLD_DUST,           // PLAYER_AP_BOTTLE_DEKU_PRINCESS
    GI_6C,                  // PLAYER_AP_BOTTLE_GOLD_DUST
    GI_SEAHORSE,            // PLAYER_AP_BOTTLE_1C
    GI_MUSHROOM,            // PLAYER_AP_BOTTLE_SEAHORSE
    GI_70,                  // PLAYER_AP_BOTTLE_MUSHROOM
    GI_DEKU_PRINCESS,       // PLAYER_AP_BOTTLE_HYLIAN_LOACH
    GI_BUG,                 // PLAYER_AP_BOTTLE_BUG
    GI_POE,                 // PLAYER_AP_BOTTLE_POE
    GI_BIG_POE,             // PLAYER_AP_BOTTLE_BIG_POE
    GI_POTION_RED,          // PLAYER_AP_BOTTLE_POTION_RED
    GI_POTION_BLUE,         // PLAYER_AP_BOTTLE_POTION_BLUE
    GI_POTION_GREEN,        // PLAYER_AP_BOTTLE_POTION_GREEN
    GI_MILK_HALF,           // PLAYER_AP_BOTTLE_MILK
    GI_MILK_HALF,           // PLAYER_AP_BOTTLE_MILK_HALF
    GI_CHATEAU,             // PLAYER_AP_BOTTLE_CHATEAU
    GI_FAIRY,               // PLAYER_AP_BOTTLE_FAIRY
    GI_MOON_TEAR,           // PLAYER_AP_MOON_TEAR
    GI_DEED_LAND,           // PLAYER_AP_DEED_LAND
    GI_ROOM_KEY,            // PLAYER_AP_ROOM_KEY
    GI_LETTER_TO_KAFEI,     // PLAYER_AP_LETTER_TO_KAFEI
    GI_MAGIC_BEANS,         // PLAYER_AP_MAGIC_BEANS
    GI_DEED_SWAMP,          // PLAYER_AP_DEED_SWAMP
    GI_DEED_MOUNTAIN,       // PLAYER_AP_DEED_MOUNTAIN
    GI_DEED_OCEAN,          // PLAYER_AP_DEED_OCEAN
    GI_MOON_TEAR,           // PLAYER_AP_32
    GI_LETTER_TO_MAMA,      // PLAYER_AP_LETTER_MAMA
    GI_A7,                  // PLAYER_AP_34
    GI_A8,                  // PLAYER_AP_35
    GI_PENDANT_OF_MEMORIES, // PLAYER_AP_PENDANT_OF_MEMORIES
    GI_PENDANT_OF_MEMORIES, // PLAYER_AP_37
    GI_PENDANT_OF_MEMORIES, // PLAYER_AP_38
    GI_PENDANT_OF_MEMORIES, // PLAYER_AP_39
    GI_MASK_TRUTH,          // PLAYER_AP_MASK_TRUTH
    GI_MASK_KAFEIS_MASK,    // PLAYER_AP_MASK_KAFEIS_MASK
    GI_MASK_ALL_NIGHT,      // PLAYER_AP_MASK_ALL_NIGHT
    GI_MASK_BUNNY,          // PLAYER_AP_MASK_BUNNY
    GI_MASK_KEATON,         // PLAYER_AP_MASK_KEATON
    GI_MASK_GARO,           // PLAYER_AP_MASK_GARO
    GI_MASK_ROMANI,         // PLAYER_AP_MASK_ROMANI
    GI_MASK_CIRCUS_LEADER,  // PLAYER_AP_MASK_CIRCUS_LEADER
    GI_MASK_POSTMAN,        // PLAYER_AP_MASK_POSTMAN
    GI_MASK_COUPLE,         // PLAYER_AP_MASK_COUPLE
    GI_MASK_GREAT_FAIRY,    // PLAYER_AP_MASK_GREAT_FAIRY
    GI_MASK_GIBDO,          // PLAYER_AP_MASK_GIBDO
    GI_MASK_DON_GERO,       // PLAYER_AP_MASK_DON_GERO
    GI_MASK_KAMARO,         // PLAYER_AP_MASK_KAMARO
    GI_MASK_CAPTAIN,        // PLAYER_AP_MASK_CAPTAIN
    GI_MASK_STONE,          // PLAYER_AP_MASK_STONE
    GI_MASK_BREMEN,         // PLAYER_AP_MASK_BREMEN
    GI_MASK_BLAST,          // PLAYER_AP_MASK_BLAST
    GI_MASK_SCENTS,         // PLAYER_AP_MASK_SCENTS
    GI_MASK_GIANT,          // PLAYER_AP_MASK_GIANT
    GI_MASK_FIERCE_DEITY,   // PLAYER_AP_MASK_FIERCE_DEITY
    GI_MASK_GORON,          // PLAYER_AP_MASK_GORON
    GI_MASK_ZORA,           // PLAYER_AP_MASK_ZORA
    GI_MASK_DEKU,           // PLAYER_AP_MASK_DEKU
    GI_LENS,                // PLAYER_AP_LENS
};

LinkAnimationHeader* D_8085D1F8[] = {
    &gameplay_keep_Linkanim_00DCA8,
    &gameplay_keep_Linkanim_00DE98,
};

// TODO: standarize
#define BOTTLE_ACTION(item) ((item)-PLAYER_AP_BOTTLE)

s32 func_80838A90(Player* this, PlayState* play) {
    s32 bottleAction;

    if (this->unk_AA5 != 0) {
        if (!(this->actor.bgCheckFlags & 3) && !(this->stateFlags1 & PLAYER_STATE1_8000000) &&
            !(this->stateFlags1 & PLAYER_STATE1_800000) && !(this->stateFlags3 & PLAYER_STATE3_8) &&
            !(this->skelAnime.moveFlags & 8)) {
            func_80838760(this);
            func_80833AA0(this, play);
            return true;
        }
        if (!func_808387A0(play, this)) {
            if (this->unk_AA5 == 5) {
                if ((this->heldItemActionParam > PLAYER_AP_39) && (this->heldItemActionParam <= PLAYER_AP_MASK_DEKU)) {
                    s32 maskId = this->heldItemActionParam - PLAYER_AP_39;

                    this->prevMask = this->currentMask;
                    if ((!!(maskId == this->currentMask) != 0) || (this->heldItemActionParam < PLAYER_AP_MASK_GIANT) ||
                        ((this->heldItemActionParam == PLAYER_AP_MASK_GIANT) &&
                         (this->transformation != PLAYER_FORM_HUMAN))) {
                        if (maskId == this->currentMask) {
                            this->currentMask = PLAYER_MASK_NONE;
                        } else {
                            this->currentMask = maskId;
                        }
                        if (this->transformation == PLAYER_FORM_HUMAN) {
                            func_80838A20(play, this);
                            return true;
                        }
                        func_808388B8(play, this, PLAYER_FORM_HUMAN);
                    } else {
                        this->currentMask = maskId;
                        if ((u8)(maskId) == PLAYER_MASK_GIANT) { // u8 temp?
                            func_808389BC(play, this);
                            return true;
                        }
                        func_808388B8(play, this, this->heldItemActionParam - PLAYER_AP_MASK_FIERCE_DEITY);
                    }
                    gSaveContext.save.equippedMask = this->currentMask;
                } else if (((this->actor.flags & ACTOR_FLAG_100) == ACTOR_FLAG_100) ||
                           (this->heldItemActionParam == PLAYER_AP_PICTO_BOX) ||
                           ((this->heldItemActionParam != this->unk_B2B) &&
                            ((this->heldItemActionParam == PLAYER_AP_BOTTLE_BIG_POE) ||
                             ((this->heldItemActionParam >= PLAYER_AP_BOTTLE_ZORA_EGG) &&
                              (this->heldItemActionParam <= PLAYER_AP_BOTTLE_HYLIAN_LOACH)) ||
                             (this->heldItemActionParam > PLAYER_AP_BOTTLE_FAIRY) ||
                             ((this->talkActor != NULL) && (this->exchangeItemId > 0) &&
                              (((this->exchangeItemId == PLAYER_AP_MAGIC_BEANS) &&
                                (this->heldItemActionParam == PLAYER_AP_MAGIC_BEANS)) ||
                               ((this->exchangeItemId != PLAYER_AP_MAGIC_BEANS) &&
                                (Player_ActionToBottle(this, this->heldItemActionParam) > -1))))))) {
                    Actor* targetActor;
                    s32 heldItemTemp = this->heldItemActionParam;

                    func_80838760(this);
                    this->heldItemActionParam = PLAYER_AP_NONE;
                    func_80831760(play, this, func_80853A5C, 0);
                    targetActor = this->talkActor;
                    this->heldItemActionParam = heldItemTemp;
                    this->unk_A86 = -1;

                    if ((targetActor != NULL) && (((this->exchangeItemId == PLAYER_AP_MAGIC_BEANS) &&
                                                   (this->heldItemActionParam == PLAYER_AP_MAGIC_BEANS)) ||
                                                  ((this->exchangeItemId != PLAYER_AP_MAGIC_BEANS) &&
                                                   (this->exchangeItemId > PLAYER_AP_NONE)))) {
                        this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_40);
                        if (this->exchangeItemId == PLAYER_AP_MAGIC_BEANS) {
                            Inventory_ChangeAmmo(ITEM_MAGIC_BEANS, -1);
                            func_80831760(play, this, func_8084B4A8, 0);
                            this->currentYaw = targetActor->yawTowardsPlayer + 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            if (targetActor->xzDistToPlayer < 40.0f) {
                                func_8082DB90(play, this, &gameplay_keep_Linkanim_00DB10);
                                func_8082E920(play, this, 0x19);
                            } else {
                                func_8082E438(play, this, D_8085BE84[31][this->modelAnimType]);
                            }
                            this->stateFlags1 |= PLAYER_STATE1_20000000;
                            this->unk_AE8 = 80;
                            this->unk_AE7 = -1;
                            this->targetedActor = this->talkActor;
                        } else {
                            this->unk_A86 = 0x7C;
                        }
                        targetActor->flags |= ACTOR_FLAG_100;
                        this->actor.textId = 0;
                        this->targetedActor = this->talkActor;
                    } else {
                        this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_10000000 | PLAYER_STATE1_40);
                        this->unk_A86 = play->playerActorCsIds[3];
                        this->unk_AE7 = 1;
                        this->actor.textId = 0xFE;
                    }
                    this->actor.flags |= ACTOR_FLAG_100;
                    this->exchangeItemId = this->heldItemActionParam;
                    if (this->unk_AE7 >= 0) {
                        Player_AnimationPlayOnce(play, this, D_8085D1F8[this->unk_AE7]);
                    }
                    func_8082DAD4(this);
                    return true;
                } else {
                    bottleAction = Player_ActionToBottle(this, this->heldItemActionParam);

                    if (bottleAction > -1) {
                        func_80838760(this);
                        if (bottleAction >= BOTTLE_ACTION(PLAYER_AP_BOTTLE_FAIRY)) {
                            func_80831760(play, this, func_80853754, 0);
                            func_8082DB90(play, this, &gameplay_keep_Linkanim_00D4A8);
                        } else if ((bottleAction > BOTTLE_ACTION(PLAYER_AP_BOTTLE)) &&
                                   (bottleAction < BOTTLE_ACTION(PLAYER_AP_BOTTLE_POE))) {
                            func_80831760(play, this, func_80853850, 0);
                            func_8082DB90(play, this, &gameplay_keep_Linkanim_00D4D8);
                            this->unk_A86 = play->playerActorCsIds[2];
                        } else {
                            func_80831760(play, this, func_80853194, 0);
                            func_8082E4A4(play, this,
                                          (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2A0
                                                                                     : &gameplay_keep_Linkanim_00D4B8);
                        }
                    } else {
                        Actor* actorUnkA90 = this->unk_A90;

                        if ((actorUnkA90 == NULL) || (actorUnkA90->id == ACTOR_EN_ZOT) ||
                            (actorUnkA90->cutscene == -1)) {
                            if (!func_808323C0(this, play->playerActorCsIds[0])) {
                                return false;
                            }
                        } else {
                            this->unk_A86 = -1;
                        }
                        func_80831760(play, this, func_8085269C, 0);
                        if ((this->skelAnime.playSpeed < 0.0f) ||
                            ((this->skelAnime.animation != D_8085D17C[this->transformation]) &&
                             (this->skelAnime.animation != D_8085D190[this->transformation]))) {
                            func_8082DB90(play, this, D_8085D17C[this->transformation]);
                        }
                        this->stateFlags2 |= PLAYER_STATE2_8000000;
                        if (actorUnkA90 != NULL) {
                            this->actor.flags |= ACTOR_FLAG_20000000;
                            if (actorUnkA90->id == ACTOR_EN_ZOT) {
                                this->unk_A94 = -1.0f;
                            } else {
                                actorUnkA90->flags |= ACTOR_FLAG_20000000;
                            }
                        }
                    }
                }
            } else {
                if (func_8083868C(play, this) != CAM_MODE_NORMAL) {
                    func_80838760(this);
                    if (!(this->stateFlags1 & PLAYER_STATE1_800000)) {
                        Player_SetAction(play, this, func_8084E724, 1);
                        this->unk_AE8 = 13;
                        func_80836D8C(this);
                        if (this->unk_AA5 == 2) {
                            play->actorCtx.unk5 |= 4;
                        }
                    }
                    this->stateFlags1 |= PLAYER_STATE1_100000;
                    play_sound(NA_SE_SY_CAMERA_ZOOM_UP);
                    func_8082DABC(this);
                    return true;
                }
                this->unk_AA5 = 0;
                play_sound(NA_SE_SY_ERROR);
                return false;
            }
            this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_10000000);
            func_8082DAD4(this);
        }
        return true;
    }
    return false;
}

s32 func_808391D8(Player* this, PlayState* play) {
    if (gSaveContext.save.playerData.health != 0) {
        Actor* talkActor = this->talkActor;
        Actor* targetedActor = this->targetedActor;
        Actor* var_a1 = NULL;
        s32 var_t1 = false;
        s32 var_t2 = false;

        if (this->tatlActor != NULL) {
            var_t2 =
                (targetedActor != NULL) && (CHECK_FLAG_ALL(targetedActor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_40000) ||
                                            (targetedActor->hintId != 0xFF));

            if (var_t2 || (this->tatlTextId != 0)) {
                //! @bug ?
                var_t1 = (this->tatlTextId < 0) && ((ABS_ALT(this->tatlTextId) & 0xFF00) != 0x10000);

                if (var_t1 || !var_t2) {
                    var_a1 = this->tatlActor;
                    if (var_t1) {
                        targetedActor = NULL;
                        talkActor = NULL;
                    }
                } else {
                    var_a1 = targetedActor;
                }
            }
        }

        if ((talkActor != NULL) || (var_a1 != NULL)) {
            if ((targetedActor == NULL) || (targetedActor == talkActor) || (targetedActor == var_a1)) {
                if (!(this->stateFlags1 & PLAYER_STATE1_800) ||
                    ((this->heldActor != NULL) &&
                     (var_t1 || (talkActor == this->heldActor) || (var_a1 == this->heldActor) ||
                      ((talkActor != NULL) && (talkActor->flags & ACTOR_FLAG_10000))))) {
                    if (((this->actor.bgCheckFlags & 1) || (this->stateFlags1 & PLAYER_STATE1_800000) ||
                         func_801242B4(this))) {
                        if (talkActor != NULL) {
                            if ((targetedActor == NULL) || (targetedActor == talkActor)) {
                                this->stateFlags2 |= PLAYER_STATE2_2;
                            }

                            if (!ActorCutscene_GetCanPlayNext(0x7C)) {
                                return false;
                            }

                            if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A) ||
                                (talkActor->flags & ACTOR_FLAG_10000)) {
                                var_a1 = NULL;
                            } else if (var_a1 == NULL) {
                                return false;
                            }
                        }

                        if (var_a1 != NULL) {
                            if (!var_t1) {
                                this->stateFlags2 |= PLAYER_STATE2_200000;
                                if (!ActorCutscene_GetCanPlayNext(0x7C) ||
                                    !CHECK_BTN_ALL(D_80862B44->press.button, BTN_CUP)) {
                                    return false;
                                }
                            }

                            talkActor = var_a1;
                            this->talkActor = NULL;

                            if (var_t1 || !var_t2) {
                                var_a1->textId = ABS_ALT(this->tatlTextId);
                            } else if (var_a1->hintId != 0xFF) {
                                var_a1->textId = var_a1->hintId + 0x1900;
                            }
                        }

                        this->currentMask = D_80862B2C;
                        gSaveContext.save.equippedMask = this->currentMask;
                        func_8085B460(play, talkActor);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

s32 func_80839518(Player* this, PlayState* play) {
    if (this->unk_AA5 != 0) {
        func_80838A90(this, play);
        return true;
    } else if ((this->targetedActor != NULL) &&
               (CHECK_FLAG_ALL(this->targetedActor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_40000) ||
                (this->targetedActor->hintId != 0xFF))) {
        this->stateFlags2 |= PLAYER_STATE2_200000;
    } else if ((this->tatlTextId == 0) && !func_80123420(this) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_CUP) &&
               !func_80831814(this, play, 1)) {
        play_sound(NA_SE_SY_ERROR);
    }
    return false;
}

// Jumpslash/Jumpkick start
void func_808395F0(PlayState* play, Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnimation, f32 linearVelocity,
                   f32 yVelocity) {
    if (this->transformation == PLAYER_FORM_ZORA) {
        linearVelocity *= 1.1f;
        meleeWeaponAnimation = PLAYER_MWA_ZORA_JUMPKICK_START;
        yVelocity *= 0.9f;
    }

    func_80833864(play, this, meleeWeaponAnimation);
    Player_SetAction(play, this, func_8084CB58, 0);
    this->stateFlags3 |= PLAYER_STATE3_2;
    this->linearVelocity = linearVelocity;
    this->currentYaw = this->actor.shape.rot.y;
    this->actor.velocity.y = yVelocity;
    this->actor.bgCheckFlags &= ~1;
    func_8082E188(this);
    func_8082DF8C(this, NA_SE_VO_LI_SWORD_L);
}

s32 func_808396B8(PlayState* play, Player* this) {
    if (!(this->stateFlags1 & PLAYER_STATE1_400000) &&
        (((this->actor.id != ACTOR_PLAYER) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_B)) ||
         ((Player_GetMeleeWeaponHeld(this) != 0) &&
          ((this->transformation != PLAYER_FORM_GORON) || (this->actor.bgCheckFlags & 1)) &&
          ((this->transformation != PLAYER_FORM_ZORA) || !(this->stateFlags1 & PLAYER_STATE1_2000000)) &&
          (D_80862B48 != 0)))) {
        return true;
    }
    return false;
}

s32 func_80839770(Player* this, PlayState* play) {
    if (func_808396B8(play, this)) {
        if ((this->transformation != PLAYER_FORM_GORON) && (D_80862B08 != 7)) {
            func_808395F0(play, this,
                          (this->transformation == PLAYER_FORM_ZORA) ? PLAYER_MWA_ZORA_JUMPKICK_START
                                                                     : PLAYER_MWA_JUMPSLASH_START,
                          3.0f, 4.5f);
            return true;
        }
    }
    return false;
}

s32 func_80839800(Player* this, PlayState* play) {
    if ((this->unk_AE3[this->unk_ADE] == 0) && (D_80862B08 != 7)) {
        func_80836B3C(play, this, 0.0f);
        return true;
    }
    return false;
}

void func_80839860(Player* this, PlayState* play, s32 arg2) {
    s32 pad;
    f32 var_fv0;

    var_fv0 = (!(arg2 & 1) ? 5.8f : 3.5f);

    if (this->currentBoots == PLAYER_BOOTS_GIANT) {
        var_fv0 *= 0.5f;
    }

    //! FAKE
    if (arg2 == 2) {}

    func_80834D50(play, this, D_8085C2A4[arg2].unk_0, var_fv0, NA_SE_VO_LI_SWORD_N);

    this->unk_AE8 = 1;
    this->unk_AE7 = arg2;

    this->currentYaw = this->actor.shape.rot.y + (arg2 << 0xE);
    this->linearVelocity = !(arg2 & 1) ? 6.0f : 8.5f;

    this->stateFlags2 |= PLAYER_STATE2_80000;
    func_800B8E58(this, ((arg2 << 0xE) == 0x8000) ? NA_SE_PL_ROLL : NA_SE_PL_SKIP);
}

void func_80839978(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->heldItemActionParam = PLAYER_AP_OCARINA;
        func_80831760(play, this, func_8084AC84, 0);
        func_8082DB60(play, this, &gameplay_keep_Linkanim_00D228);
        func_8082E920(play, this, (4 | 0x200));
        this->stateFlags3 |= PLAYER_STATE3_20000000;
        this->unk_B48 = this->linearVelocity;
        func_801A3098(NA_BGM_BREMEN_MARCH);
    }
}

void func_80839A10(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->heldItemActionParam = PLAYER_AP_NONE;
        func_80831760(play, this, func_8084AEEC, 0);
        func_8082DB60(play, this, &gameplay_keep_Linkanim_00CF98);
        this->stateFlags2 |= PLAYER_STATE3_2000000;
        func_801A3098(NA_BGM_KAMARO_DANCE);
    }
}

s32 func_80839A84(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_DEKU) {
        if (func_80836DC0(play, this)) {
            return 1;
        }
    } else {
        return 0;
    }

    Player_SetAction(play, this, func_808573A4, 0);
    this->stateFlags1 &= ~(PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
    this->unk_ADC = 4;
    func_808373A4(play, this);
    return 1;
}

s32 func_80839B18(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A) && (play->roomCtx.currRoom.unk3 != 2) && (D_80862B08 != 7) &&
        (D_80862B40 != 1)) {
        s32 temp_a2 = this->unk_AE3[this->unk_ADE];

        if (temp_a2 <= 0) {
            if (func_8082FBE8(this)) {
                if (this->actor.category != ACTORCAT_PLAYER) {
                    if (temp_a2 < 0) {
                        func_80834DB8(this, &gameplay_keep_Linkanim_00DCD8, REG(69) / 100.0f, play);
                    } else {
                        func_80836B3C(play, this, 0.0f);
                    }
                } else if (!(this->stateFlags1 & 0x8000000) && (Player_GetMeleeWeaponHeld(this) != 0) &&
                           func_80832090(this) && (this->transformation != PLAYER_FORM_GORON)) {
                    func_808395F0(play, this, PLAYER_MWA_JUMPSLASH_START, 5.0f, 5.0f);
                } else if (func_80839A84(play, this) == 0) {
                    func_80836B3C(play, this, 0.0f);
                }

                return true;
            }
        } else {
            func_80839860(this, play, temp_a2);
            return true;
        }
    }

    return false;
}

void func_80839CD8(Player* this, PlayState* play) {
    LinkAnimationHeader* anim;
    f32 var_fv0 = this->unk_B38 - 3.0f;

    if (var_fv0 < 0.0f) {
        var_fv0 += 29.0f;
    }

    if (var_fv0 < 14.0f) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_17][this->modelAnimType];
        var_fv0 = 11.0f - var_fv0;
        if (var_fv0 < 0.0f) {
            var_fv0 = -var_fv0 * 1.375f;
        }
        var_fv0 = var_fv0 / 11.0f;
    } else {
        anim = D_8085BE84[PLAYER_ANIMGROUP_18][this->modelAnimType];
        var_fv0 = 26.0f - var_fv0;
        if (var_fv0 < 0.0f) {
            var_fv0 = -var_fv0 * 2;
        }
        var_fv0 = var_fv0 / 12.0f;
    }

    LinkAnimation_Change(play, &this->skelAnime, anim, 1.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                         4.0f * var_fv0);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80839E3C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    func_80839CD8(this, play);
}

void func_80839E74(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_80849FE0, 1);
    Player_AnimationPlayOnce(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80839ED0(Player* this, PlayState* play) {
    if (!(this->stateFlags3 & PLAYER_STATE3_80) && (func_80852B28 != this->actionFunc) && !func_8083213C(this)) {
        func_80836D8C(this);
        if (!(this->stateFlags1 & PLAYER_STATE1_40)) {
            if (func_801242B4(this)) {
                func_808353DC(play, this);
            } else {
                func_80836988(this, play);
            }
        }
        if (this->unk_AA5 < 5) {
            this->unk_AA5 = 0;
        }
    }
    this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000);
}

s32 func_80839F98(PlayState* play, Player* this) {
    if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
        if (this->linearVelocity != 0.0f) {
            func_80836B3C(play, this, 0.0f);
            return true;
        }
        func_80836AD8(play, this);
        LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E208, 2.0f / 3.0f, 0.0f, 7.0f,
                             ANIMMODE_ONCE, 0.0f);
        return true;
    }
    return false;
}

// Toggles swimming/walking underwater as Zora
void func_8083A04C(Player* this) {
    if (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) {
        if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
        }
        if (func_808508C8 == this->actionFunc) {
            this->unk_AE8 = 20;
        }
    } else {
        if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_B)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_UNDERWATER;
        }
    }
}

s32 func_8083A0CC(Player* this, PlayState* play) {
    if ((D_80862B04 == 0) && (this->transformation == PLAYER_FORM_ZORA)) {
        func_8083A04C(this);
    }
    return false;
}

s32 func_8083A114(Player* this, PlayState* play) {
    if ((D_80862B04 == 0) && !(this->stateFlags1 & PLAYER_STATE1_800000) && !func_8082FB68(this)) {
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->stateFlags1 & PLAYER_STATE1_8000000)) {
            func_8083A04C(this);
        } else if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A) && !func_8082FB68(this)) {
            if (this->transformation == PLAYER_FORM_GORON) {
                if (func_80839F98(play, this)) {
                    return true;
                }
            } else if (func_80839A84(play, this) || func_80839800(this, play)) {
                return true;
            }

            if ((this->putAwayCountdown == 0) && (this->itemActionParam >= PLAYER_AP_SWORD_KOKIRI) &&
                (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
                func_80831990(play, this, ITEM_NONE);
            } else {
                this->stateFlags2 ^= PLAYER_STATE2_100000;
            }
        }
    }

    return false;
}

s32 func_8083A274(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_R) && (this->unk_AA5 == 0) && (play->unk_1887C == 0)) {
        if (Player_IsGoronOrDeku(this) ||
            ((((this->transformation == PLAYER_FORM_ZORA) && !(this->stateFlags1 & PLAYER_STATE1_2000000)) ||
              ((this->transformation == PLAYER_FORM_HUMAN) && (this->currentShield != PLAYER_SHIELD_NONE))) &&
             !func_80123434(this) && (this->targetedActor == NULL))) {
            func_8082DC38(this);
            func_8082DCA0(play, this);
            if (Player_SetAction(play, this, func_8084B5C0, 0)) {
                this->stateFlags1 |= PLAYER_STATE1_400000;
                if (this->transformation != PLAYER_FORM_GORON) {
                    LinkAnimationHeader* anim;
                    f32 endFrame;

                    if (!Player_IsGoronOrDeku(this)) {
                        Player_SetModelsForHoldingShield(this);
                        anim = D_8085BE84[PLAYER_ANIMGROUP_19][this->modelAnimType];
                    } else {
                        anim = (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2C8
                                                                          : &gameplay_keep_Linkanim_00D218;
                    }

                    if (anim != this->skelAnime.animation) {
                        if (func_80123420(this)) {
                            this->unk_B3C = 1.0f;
                        } else {
                            this->unk_B3C = 0.0f;
                            func_8082FC60(this);
                        }
                        this->unk_AB2.x = 0;
                        this->unk_AB2.y = 0;
                        this->unk_AB2.z = 0;
                    }

                    endFrame = Animation_GetLastFrame(anim);
                    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f,
                                         (anim == &gameplay_keep_Linkanim_00E2C8) ? 0.0f : endFrame, endFrame,
                                         ANIMMODE_ONCE, 0.0f);
                }
                func_80830AE8(this);
            }

            return true;
        }
    }

    return false;
}

s32 func_8083A4A4(Player* this, f32* arg1, s16* arg2, f32 arg3) {
    s16 yaw = this->currentYaw - *arg2;

    if (ABS_ALT(yaw) > 0x6000) {
        if (Math_StepToF(&this->linearVelocity, 0.0f, arg3) != 0) {
            *arg1 = 0.0f;
            *arg2 = this->currentYaw;
        } else {
            return true;
        }
    }
    return false;
}

void func_8083A548(Player* this) {
    if ((this->unk_ADC > 0) && !CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
        this->unk_ADC = -this->unk_ADC;
    }
}

s32 func_8083A580(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
        if (!(this->stateFlags1 & PLAYER_STATE1_400000) && (Player_GetMeleeWeaponHeld(this) != 0)) {
            if ((this->unk_ADC > 0) && (((this->transformation == PLAYER_FORM_ZORA)) ||
                                        ((this->unk_ADC == 1) && (this->itemActionParam != PLAYER_AP_STICK)))) {
                if (this->transformation == PLAYER_FORM_ZORA) {
                    func_80830E30(this, play);
                } else {
                    func_808335B0(play, this);
                }
                return true;
            }
        }
    } else {
        func_8083A548(this);
    }
    return false;
}

s32 func_8083A658(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & 1) {
        Player_SetAction(play, this, func_80852B28, 0);
        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DD38);
        this->unk_AA5 = 0;
        return true;
    }
    return false;
}

struct_8085D200 D_8085D200[] = {
    { &gameplay_keep_Linkanim_00D4A0, &gameplay_keep_Linkanim_00D498, 2, 3 },
    { &gameplay_keep_Linkanim_00D4D0, &gameplay_keep_Linkanim_00D4C8, 5, 3 },
};

s32 func_8083A6C0(PlayState* play, Player* this) {
    if (D_80862B48 != 0) {
        if (Player_GetBottleHeld(this) >= 0) {
            Player_SetAction(play, this, func_808534C0, 0);
            if (this->actor.depthInWater > 12.0f) {
                this->unk_AE8 = 1;
            }
            func_8082DB90(play, this, D_8085D200[this->unk_AE8].unk_0);
            func_800B8E58(this, NA_SE_IT_SWORD_SWING);
            func_8082DF8C(this, NA_SE_VO_LI_AUTO_JUMP);
            return true;
        }
        return false;
    }
    return false;
}

void func_8083A794(Player* this, PlayState* play) {
    if ((func_8084AF9C != this->actionFunc) && (func_8084B0EC != this->actionFunc)) {
        this->unk_B70 = 0;
        this->unk_B34 = 0.0f;
        this->unk_B38 = 0.0f;
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_2][this->modelAnimType]);
    }

    Player_SetAction(play, this, func_8082FBE8(this) ? func_8084B0EC : func_8084AF9C, 1);
}

void func_8083A844(Player* this, PlayState* play, s16 currentYaw) {
    this->currentYaw = currentYaw;
    this->actor.shape.rot.y = this->currentYaw;
    func_8083A794(this, play);
}

s32 func_8083A878(PlayState* play, Player* this, f32 arg2) {
    WaterBox* waterBox;
    f32 ySurface = this->actor.world.pos.y;

    if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &ySurface,
                             &waterBox)) {
        ySurface -= this->actor.world.pos.y;
        if (this->ageProperties->unk_24 <= ySurface) {
            Player_SetAction(play, this, func_80850B18, 0);
            func_8082E634(play, this, &gameplay_keep_Linkanim_00DFD0);
            this->stateFlags1 |= (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000);
            this->unk_AE8 = 20;
            this->linearVelocity = 2.0f;
            func_80123140(play, this);
            return false;
        }
    }
    func_80835324(play, this, arg2, this->actor.shape.rot.y);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    return true;
}

/**
 * Update for using telescopes. SCENE_AYASHIISHOP acts quite differently: it has a different camera mode and cannot use
 * zooming.
 *
 * - Stick inputs move the view; shape.rot.y is used as a base position which cannot be looked too far away from. (This
 * is not necessarily the same as the original angle of the spawn.)
 * - A can be used to zoom (except in SCENE_AYASHIISHOP)
 * - B exits, using the RESPAWN_MODE_DOWN entrance
 */
void func_8083A98C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Player* this = THIS;
    s32 camMode;

    if (play->csCtx.state != CS_STATE_0) {
        return;
    }

    if (DECR(this->unk_AE8) != 0) {
        camMode = (play->sceneNum != SCENE_AYASHIISHOP) ? CAM_MODE_FIRSTPERSON : CAM_MODE_DEKUHIDE;

        // Show controls overlay. SCENE_AYASHIISHOP does not have Zoom, so has a different one.
        if (this->unk_AE8 == 1) {
            Message_StartTextbox(play, (play->sceneNum == SCENE_AYASHIISHOP) ? 0x2A00 : 0x5E6, NULL);
        }
    } else {
        D_80862B44 = play->state.input;
        if (play->view.fovy >= 25.0f) {
            s16 prevFocusX = thisx->focus.rot.x;
            s16 prevFocusY = thisx->focus.rot.y;
            s16 inputY;
            s16 inputX;
            s16 newYaw; // from base position shape.rot.y

            // Pitch:
            inputY = D_80862B44->rel.stick_y * 4;
            // Add input, clamped to prevent turning too fast
            thisx->focus.rot.x += CLAMP(inputY, -0x12C, 0x12C);
            // Prevent looking too far up or down
            thisx->focus.rot.x = CLAMP(thisx->focus.rot.x, -0x2EE0, 0x2EE0);

            // Yaw: shape.rot.y is used as a fixed starting position
            inputX = D_80862B44->rel.stick_x * -4;
            // Start from current position: no input -> no change
            newYaw = thisx->focus.rot.y - thisx->shape.rot.y;
            // Add input, clamped to prevent turning too fast
            newYaw += CLAMP(inputX, -0x12C, 0x12C);
            // Prevent looking too far left or right of base position
            newYaw = CLAMP(newYaw, -0x3E80, 0x3E80);
            thisx->focus.rot.y = thisx->shape.rot.y + newYaw;

            if (play->sceneNum == SCENE_00KEIKOKU) {
                f32 focusDeltaX = (s16)(thisx->focus.rot.x - prevFocusX);
                f32 focusDeltaY = (s16)(thisx->focus.rot.y - prevFocusY);

                func_8019FAD8(&gSfxDefaultPos, NA_SE_PL_TELESCOPE_MOVEMENT - SFX_FLAG,
                              sqrtf(SQ(focusDeltaX) + SQ(focusDeltaY)) / 300.0f);
            }
        }

        if (play->sceneNum == SCENE_AYASHIISHOP) {
            camMode = CAM_MODE_DEKUHIDE;
        } else if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) { // Zoom
            camMode = CAM_MODE_TARGET;
        } else {
            camMode = CAM_MODE_NORMAL;
        }

        // Exit
        if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_B)) {
            func_801477B4(play);

            if (play->sceneNum == SCENE_00KEIKOKU) {
                gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = 0x4C20;
            } else {
                u16 entrance;

                if (play->sceneNum == SCENE_AYASHIISHOP) {
                    entrance = 0xE30;
                } else {
                    entrance = 0x4080;
                }
                gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = entrance;
            }

            func_80169EFC(&play->state);
            gSaveContext.respawnFlag = -2;
            play->transitionType = TRANS_TYPE_21;
        }
    }

    Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), CAM_SET_TELESCOPE);
    Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), camMode);
}

// Set up using a telescope
void Player_InitMode_Telescope(PlayState* play, Player* this) {
    this->actor.update = func_8083A98C;
    this->actor.draw = NULL;
    if (play->sceneNum == SCENE_00KEIKOKU) {
        this->actor.focus.rot.x = 0xBD8;
        this->actor.focus.rot.y = -0x4D74;
        this->unk_AE8 = 20;
    } else if (play->sceneNum == SCENE_AYASHIISHOP) {
        this->actor.focus.rot.x = 0x9A6;
        this->actor.focus.rot.y = 0x2102;
        this->unk_AE8 = 2;
    } else {
        this->actor.focus.rot.x = 0x9A6;
        this->actor.focus.rot.y = 0x2102;
        this->unk_AE8 = 20;
    }
    play->actorCtx.unk5 |= 2;
}

void Player_InitMode_B(PlayState* play, Player* this) {
    func_8085B384(this, play);
}

void Player_InitMode_D(PlayState* play, Player* this) {
    if (func_8083A878(play, this, 180.0f)) {
        this->unk_AE8 = -20;
    }
}

// InitModes 0xA and 0xE
void func_8083ADF0(PlayState* play, Player* this) {
    this->linearVelocity = 2.0f;
    gSaveContext.entranceSpeed = 2.0f;

    if (func_8083A878(play, this, 120.0f)) {
        this->unk_AE8 = -15;
    }
}

void Player_InitMode_F(PlayState* play, Player* this) {
    if (gSaveContext.entranceSpeed < 0.1f) {
        gSaveContext.entranceSpeed = 0.1f;
    }

    this->linearVelocity = gSaveContext.entranceSpeed;
    if (func_8083A878(play, this, 800.0f)) {
        this->unk_AE8 = -80.0f / this->linearVelocity;
        if (this->unk_AE8 < -20) {
            this->unk_AE8 = -20;
        }
    }
}

void func_8083AECC(Player* this, s16 currentYaw, PlayState* play) {
    Player_SetAction(play, this, func_8084A5C0, 1);
    LinkAnimation_CopyJointToMorph(play, &this->skelAnime);
    this->unk_B38 = 0.0f;
    this->unk_B34 = 0.0f;
    this->currentYaw = currentYaw;
}

void func_8083AF30(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084A26C, 1);
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType]);
}

void func_8083AF8C(Player* this, s16 currentYaw, PlayState* play) {
    Player_SetAction(play, this, func_8084B288, 1);
    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00D3F8, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gameplay_keep_Linkanim_00D3F8), ANIMMODE_ONCE, -6.0f);
    this->linearVelocity = 8.0f;
    this->currentYaw = currentYaw;
}

void func_8083B030(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084A8E8, 1);
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_24][this->modelAnimType]);
    this->unk_B38 = 0.0f;
}

void func_8083B090(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084B3B8, 1);
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, &gameplay_keep_Linkanim_00D3E8, 6.0f / 3.0f);
}

void func_8083B0E4(PlayState* play, Player* this, s16 currentYaw) {
    this->currentYaw = currentYaw;
    Player_SetAction(play, this, func_8084AB4C, 1);
    this->unk_B4E = 1200;
    this->unk_B4E *= D_8085C3E4;
    LinkAnimation_Change(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType], 1.0f, 0.0f, 0.0f,
                         ANIMMODE_LOOP, -6.0f);
}

void func_8083B1A0(Player* this, PlayState* play) {
    LinkAnimationHeader* anim;

    Player_SetAction(play, this, func_80849FE0, 1);
    if (this->unk_B40 < 0.5f) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_27][this->modelAnimType];
    } else {
        anim = D_8085BE84[PLAYER_ANIMGROUP_26][this->modelAnimType];
    }
    Player_AnimationPlayOnce(play, this, anim);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_8083B23C(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_80849A9C, 1);
    func_8082E438(play, this, D_8085BE84[PLAYER_ANIMGROUP_6][this->modelAnimType]);
    this->unk_AE8 = 1;
}

void func_8083B29C(Player* this, PlayState* play) {
    if (this->linearVelocity != 0.0f) {
        func_8083A794(this, play);
    } else {
        func_8083B1A0(this, play);
    }
}

void func_8083B2E4(Player* this, PlayState* play) {
    if (this->linearVelocity != 0.0f) {
        func_8083A794(this, play);
    } else {
        func_80836988(this, play);
    }
}

void func_8083B32C(PlayState* play, Player* this, f32 arg2) {
    this->stateFlags1 |= PLAYER_STATE1_40000;
    this->stateFlags1 &= ~PLAYER_STATE1_8000000;
    func_8082DC64(play, this);

    if (func_80837730(play, this, arg2, 500)) {
        func_800B8E58(this, NA_SE_EV_JUMP_OUT_WATER);
    }
    func_80123140(play, this);
}

s32 func_8083B3B4(PlayState* play, Player* this, Input* input) {
    if ((!(this->stateFlags1 & PLAYER_STATE1_400) && !(this->stateFlags2 & PLAYER_STATE2_400) &&
         (this->transformation != PLAYER_FORM_ZORA)) &&
        ((input == NULL) ||
         ((((this->interactRangeActor == NULL) || (this->interactRangeActor->id != ACTOR_EN_ZOG)) &&
           CHECK_BTN_ALL(input->press.button, BTN_A)) &&
          ((ABS_ALT(this->unk_AAA) < 0x2EE0) && (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) &&
           ((s32)SurfaceType_GetConveyorSpeed(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId) < 2))))) {
        if (func_8085B08C != this->actionFunc) {
            Player_SetAction(play, this, func_808516B4, 0);
        }

        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DFE0);
        this->unk_AAA = 0;
        this->stateFlags2 |= PLAYER_STATE2_400;
        this->actor.velocity.y = 0.0f;
        if (input != NULL) {
            this->stateFlags2 |= PLAYER_STATE2_800;
            func_800B8E58(this, NA_SE_PL_DIVE_BUBBLE);
        }

        return true;
    }

    if ((this->transformation != PLAYER_FORM_DEKU) &&
        ((this->stateFlags1 & PLAYER_STATE1_400) ||
         ((this->stateFlags2 & PLAYER_STATE2_400) &&
          (((func_80850D68 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
           (this->unk_AAA < -0x1555)))) &&
        ((this->actor.depthInWater - this->actor.velocity.y) < this->ageProperties->unk_30)) {
        s32 temp_v0_3;
        s16 sp2A;
        f32 sp24;

        this->stateFlags2 &= ~PLAYER_STATE2_400;
        func_8082DC64(play, this);
        temp_v0_3 = func_80837730(play, this, this->actor.velocity.y, 0x1F4);
        if (this->stateFlags3 & PLAYER_STATE3_8000) {
            sp2A = this->unk_B86[1];
            sp24 = this->unk_B48 * 1.5f;
            Player_SetAction(play, this, func_8084CA24, 1);
            this->stateFlags3 |= PLAYER_STATE3_8000;
            this->stateFlags1 &= ~PLAYER_STATE1_8000000;
            sp24 = CLAMP_MAX(sp24, 13.5f);
            this->linearVelocity = Math_CosS(this->unk_AAA) * sp24;
            this->actor.velocity.y = -Math_SinS(this->unk_AAA) * sp24;
            this->unk_B86[1] = sp2A;
            func_800B8E58(this, NA_SE_EV_JUMP_OUT_WATER);
            return true;
        }

        if (temp_v0_3) {
            func_800B8E58(this, NA_SE_PL_FACE_UP);
        } else {
            func_800B8E58(this, NA_SE_PL_FACE_UP);
        }

        if (input != NULL) {
            Player_SetAction(play, this, func_808519FC, 1);
            if (this->stateFlags1 & PLAYER_STATE1_400) {
                this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
            }
            this->unk_AE8 = 2;
        }

        func_8082E438(play, this,
                      (this->stateFlags1 & PLAYER_STATE1_800) ? &gameplay_keep_Linkanim_00DFF0
                                                              : &gameplay_keep_Linkanim_00DFD8);
        return true;
    }

    return false;
}

void func_8083B73C(PlayState* play, Player* this, s16 currentYaw) {
    Player_SetAction(play, this, func_808513EC, 0);
    func_8082E634(play, this, &gameplay_keep_Linkanim_00DFD0);
    this->actor.shape.rot.y = currentYaw;
    this->currentYaw = currentYaw;
}

void func_8083B798(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_ZORA) {
        Player_SetAction(play, this, func_808513EC, 0);
        LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00DFD0, 1.0f,
                             Animation_GetLastFrame(&gameplay_keep_Linkanim_00DFD0), 0.0f, ANIMMODE_LOOP, 0.0f);
        this->unk_B48 = 2.0f;
    } else {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DFD0);
        this->unk_AE8 = 1;
    }

    this->unk_AAA = 0x3E80;
}

void func_8083B850(PlayState* play, Player* this) {
    this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
    this->prevBoots = PLAYER_BOOTS_ZORA_LAND;
    Player_SetAction(play, this, func_80850D68, 0);
    this->unk_B48 = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y));
    func_8082F938(play, this, 1, 8);
    this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
    this->prevBoots = PLAYER_BOOTS_ZORA_LAND;
}

void func_8083B8D0(PlayState* play, Player* this) {
    if (func_80837730(play, this, this->actor.velocity.y, 500)) {
        func_800B8E58(this, NA_SE_EV_DIVE_INTO_WATER);
        if (this->fallDistance > 800) {
            func_8082DF8C(this, NA_SE_VO_LI_CLIMB_END);
        }
    }
}

void func_8083B930(PlayState* play, Player* this) {
    LinkAnimationHeader* var_a2;

    if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) || !(this->actor.bgCheckFlags & 1) ||
        (func_80857BE8 == this->actionFunc)) {
        func_8082DE50(play, this);

        if (func_8084CA24 == this->actionFunc) {
            func_8083B850(play, this);
            this->stateFlags3 |= PLAYER_STATE3_8000;
        } else if ((this->transformation == PLAYER_FORM_ZORA) && (func_8084C94C == this->actionFunc)) {
            func_8083B850(play, this);
            this->stateFlags3 |= PLAYER_STATE3_8000;
            func_8082DB60(play, this, &gameplay_keep_Linkanim_00E3D8);
        } else if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) && (this->stateFlags2 & PLAYER_STATE2_400)) {
            this->stateFlags2 &= ~PLAYER_STATE2_400;
            func_8083B3B4(play, this, NULL);
            this->unk_AE7 = 1;
        } else if (func_8084C94C == this->actionFunc) {
            Player_SetAction(play, this, func_808516B4, 0);
            func_8083B798(play, this);
        } else {
            Player_SetAction(play, this, func_808508C8, 1);
            func_8082E438(play, this,
                          (this->actor.bgCheckFlags & 1) ? &gameplay_keep_Linkanim_00E008
                                                         : &gameplay_keep_Linkanim_00DFC0);
        }
    }
    if (!(this->stateFlags1 & PLAYER_STATE1_8000000) || (this->actor.depthInWater < this->ageProperties->unk_2C)) {
        func_8083B8D0(play, this);
    }

    this->stateFlags1 |= PLAYER_STATE1_8000000;
    this->stateFlags2 |= PLAYER_STATE2_400;
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    this->unk_AEC = 0.0f;
    func_80123140(play, this);
}

void func_8083BB4C(PlayState* play, Player* this) {
    f32 sp1C = this->actor.depthInWater - this->ageProperties->unk_2C;

    if (sp1C < 0.0f) {
        this->unk_AD8 = 0;
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->actor.bgCheckFlags & 1)) {
            this->currentBoots = 4;
        }
        func_801A3E38(0);
    } else {
        func_801A3E38(0x20);
        if ((this->transformation == PLAYER_FORM_ZORA) || (sp1C < 10.0f)) {
            this->unk_AD8 = 0;
        } else if (this->unk_AD8 < 300) {
            this->unk_AD8++;
        }
    }

    if ((this->actor.parent == NULL) && (func_8084D4EC != this->actionFunc) && (func_8084F3DC != this->actionFunc) &&
        ((func_8084CA24 != this->actionFunc) || (this->actor.velocity.y < -2.0f))) {
        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            if (this->transformation == PLAYER_FORM_GORON) {
                func_80834140(play, this, &gameplay_keep_Linkanim_00DFE8);
                func_808345C8();
                func_8083B8D0(play, this);
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                if (this->unk_B67 != 0) {
                    func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                } else {
                    if ((play->sceneNum == SCENE_20SICHITAI) && (this->unk_3CF == 0)) {
                        if (gSaveContext.eventInf[5] & 1) {
                            play->nextEntranceIndex = 0xA820;
                        } else {
                            play->nextEntranceIndex = 0xA810;
                        }
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_04;
                        this->stateFlags1 |= PLAYER_STATE1_200;
                        play_sound(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
                    } else if ((this->unk_3CF == 0) &&
                               ((play->sceneNum == SCENE_30GYOSON) || (play->sceneNum == SCENE_31MISAKI) ||
                                (play->sceneNum == SCENE_TORIDE))) {
                        func_80169EFC(&play->state);
                        func_808345C8();
                    } else {
                        Player_SetAction(play, this, func_808497A0, 0);
                        this->stateFlags1 |= PLAYER_STATE1_20000000;
                    }
                    func_8083B8D0(play, this);
                }
            } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) ||
                       (((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) || !(this->actor.bgCheckFlags & 1)) &&
                        (func_8084E724 != this->actionFunc) && (func_80851B58 != this->actionFunc) &&
                        (func_80851BD4 != this->actionFunc) && (func_808508C8 != this->actionFunc) &&
                        (func_808513EC != this->actionFunc) && (func_80851588 != this->actionFunc) &&
                        (func_808516B4 != this->actionFunc) && (func_808519FC != this->actionFunc) &&
                        (func_80850B18 != this->actionFunc) && (func_80850D68 != this->actionFunc))) {
                func_8083B930(play, this);
            }
        } else if ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                   (this->actor.depthInWater < this->ageProperties->unk_24) &&
                   (((func_80850D68 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
                    (this->actor.bgCheckFlags & 1))) {
            if (this->skelAnime.moveFlags == 0) {
                func_8083B0E4(play, this, this->actor.shape.rot.y);
            }
            func_8083B32C(play, this, this->actor.velocity.y);
        }
    }
}

void func_8083BF54(PlayState* play, Player* this) {
    Vec3f sp84;
    s32 temp_v0;
    s32 var_a2;

    this->actor.terminalVelocity = -20.0f;
    this->actor.gravity = REG(68) / 100.0f;

    var_a2 = false;
    temp_v0 = func_808340D4(D_80862B08);

    if (temp_v0 || (((var_a2 = (D_80862B08 == 0xE) || (D_80862B08 == 0xF))) || (D_80862B08 == 0xD))) {
        f32 temp_fv1_2;
        f32 var_fa1;
        f32 var_ft4;
        f32 var_fv0;
        u16 sfxId;

        var_ft4 = fabsf(this->linearVelocity + D_80862B3C) * 20.0f;
        if (temp_v0) {
            if (D_80862B08 == 4) {
                var_fa1 = 1300.0f;
            } else if (D_80862B08 == 7) {
                var_fa1 = 20000.0f;
                var_ft4 = 0.0f;
            } else {
                var_fa1 = 10000.0f;
                var_ft4 *= 1.6f;
            }
            sfxId = NA_SE_PL_SINK_ON_SAND - SFX_FLAG;
        } else if (var_a2) {
            if (D_80862B08 == 0xE) {
                var_fa1 = 400.0f;
                var_ft4 *= 10.0f;
            } else {
                var_fa1 = 1300.0f;
                var_ft4 = 0.0f;
            }
            sfxId = NA_SE_PL_SINK_ON_SNOW - SFX_FLAG;
        } else {
            var_fa1 = (this->transformation == PLAYER_FORM_GORON) ? 10000.0f : 1000.0f;
            var_ft4 = 0.0f;
            sfxId = NA_SE_PL_SINK_ON_SAND - SFX_FLAG;
        }

        var_fa1 = CLAMP_MIN(var_fa1, this->unk_AB8);

        var_fv0 = (D_80862B08 == 0xE) ? 200.0f : (var_fa1 - this->unk_AB8) * 0.02f;
        var_fv0 = CLAMP(var_fv0, 0.0f, 300.0f);

        temp_fv1_2 = this->unk_AB8;
        this->unk_AB8 += var_fv0 - var_ft4;
        this->unk_AB8 = CLAMP(this->unk_AB8, 0.0f, var_fa1);

        if ((this->linearVelocity == 0.0f) && (fabsf(this->unk_AB8 - temp_fv1_2) > 2.0f)) {
            func_800B8F98(&this->actor, sfxId);
        }

        this->actor.gravity -= this->unk_AB8 * 0.004f;
    } else {
        this->unk_AB8 = 0.0f;
    }

    if ((this->stateFlags3 & PLAYER_STATE3_10) && (this->actor.bgCheckFlags & 0x20)) {
        if (this->actor.depthInWater < 50.0f) {
            f32 temp_fv1_5;
            Vec3f* bodyPartsPos;
            f32 var_fa0_3;
            f32 var_ft4_2;

            var_ft4_2 = fabsf(this->bodyPartsPos[0].x - this->unk_D6C.x) +
                        fabsf(this->bodyPartsPos[0].y - this->unk_D6C.y) +
                        fabsf(this->bodyPartsPos[0].z - this->unk_D6C.z);
            var_ft4_2 = CLAMP_MAX(var_ft4_2, 4.0f);

            this->unk_AEC += var_ft4_2;
            if (this->unk_AEC > 15.0f) {
                this->unk_AEC = 0.0f;
                sp84.x = (Rand_ZeroOne() * 10.0f) + this->actor.world.pos.x;
                sp84.y = this->actor.world.pos.y + this->actor.depthInWater;
                sp84.z = (Rand_ZeroOne() * 10.0f) + this->actor.world.pos.z;

                EffectSsGRipple_Spawn(play, &sp84, 100, 500, 0);

                if ((this->linearVelocity > 4.0f) && !func_801242B4(this) &&
                    ((this->actor.world.pos.y + this->actor.depthInWater) < this->bodyPartsPos[0].y)) {
                    func_80837730(play, this, 20.0f,
                                  (fabsf(this->linearVelocity) * 50.0f) + (this->actor.depthInWater * 5.0f));
                } else if (this->stateFlags3 & PLAYER_STATE3_8000) {
                    s32 i;

                    var_fa0_3 = (this->actor.world.pos.y + this->actor.depthInWater) - 5.0f;
                    bodyPartsPos = this->bodyPartsPos;

                    for (i = 0; i < PLAYER_BODYPART_MAX; i++, bodyPartsPos++) {
                        temp_fv1_5 = bodyPartsPos->y - var_fa0_3;

                        if (temp_fv1_5 > 0.0f) {
                            func_80837730(play, this, 20.0f,
                                          fabsf(this->linearVelocity) * 20.0f + (temp_fv1_5 * 10.0f));
                        }
                    }
                }
            }
        }

        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            s32 numBubbles = 0;
            s32 i;
            f32 var_fv1;

            var_fv1 = (this->stateFlags1 & PLAYER_STATE3_4000000)
                          ? -fabsf(this->linearVelocity)
                          : ((func_80850D68 == this->actionFunc)
                                 ? (ABS_ALT(this->unk_B8A) * -0.004f) + (this->unk_B48 * -0.38f)
                                 : this->actor.velocity.y);

            if ((var_fv1 > -1.0f) || ((this->currentBoots == 5) && (this->actor.bgCheckFlags & 1))) {
                if (Rand_ZeroOne() < 0.2f) {
                    numBubbles = 1;
                }
            } else {
                numBubbles = var_fv1 * -0.3f;
                if (numBubbles >= 9) {
                    numBubbles = 8;
                }
            }

            for (i = 0; i < numBubbles; i++) {
                EffectSsBubble_Spawn(play, &this->actor.world.pos, 20.0f, 10.0f, 20.0f, 0.13f);
            }
        }
    }
}

s32 func_8083C62C(Player* this, s32 arg1) {
    Actor* targetedActor = this->targetedActor;
    Vec3f headPos;
    s16 pitchTarget;
    s16 yawTarget;

    headPos.x = this->actor.world.pos.x;
    headPos.y = this->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    headPos.z = this->actor.world.pos.z;

    pitchTarget = Math_Vec3f_Pitch(&headPos, &targetedActor->focus.pos);
    yawTarget = Math_Vec3f_Yaw(&headPos, &targetedActor->focus.pos);

    Math_SmoothStepToS(&this->actor.focus.rot.y, yawTarget, 4, 0x2710, 0);
    Math_SmoothStepToS(&this->actor.focus.rot.x, pitchTarget, 4, 0x2710, 0);

    this->unk_AA6 |= 2;

    return func_80832754(this, arg1);
}

Vec3f D_8085D218 = { 0.0f, 100.0f, 40.0f };

void func_8083C6E8(Player* this, PlayState* play) {
    if (this->targetedActor != NULL) {
        if (func_800B7128(this) || func_8082EF20(this)) {
            func_8083C62C(this, true);
        } else {
            func_8083C62C(this, false);
        }
        return;
    }

    if (D_80862B08 == 0xB) {
        Math_SmoothStepToS(&this->actor.focus.rot.x, -20000, 10, 4000, 800);
    } else {
        s16 sp46 = 0;
        f32 yIntersect;
        Vec3f pos;
        s16 temp_v0;

        yIntersect = func_80835D2C(play, this, &D_8085D218, &pos);
        if (yIntersect > BGCHECK_Y_MIN) {
            temp_v0 = Math_FAtan2F(40.0f, this->actor.world.pos.y - yIntersect);
            sp46 = CLAMP(temp_v0, -4000, 4000);
        }
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        Math_SmoothStepToS(&this->actor.focus.rot.x, sp46, 14, 4000, 30);
    }

    func_80832754(this, func_800B7128(this) || func_8082EF20(this));
}

void func_8083C85C(Player* this) {
    Math_ScaledStepToS(&this->unk_AB2.x, D_80862B3C * -500.0f, 900);
    this->unk_AAC.x = (-(f32)this->unk_AB2.x * 0.5f);
    this->unk_AA6 |= 0x48;
}

void func_8083C8E8(Player* this, PlayState* play) {
    if ((func_800B7128(this) == 0) && (func_8082EF20(this) == 0) &&
        ((this->linearVelocity > 5.0f) || (D_80862B3C != 0.0f))) {
        s16 temp1;
        s16 temp2;

        temp1 = this->linearVelocity * 200.0f;
        temp2 = BINANG_SUB(this->currentYaw, this->actor.shape.rot.y) * this->linearVelocity * 0.1f;

        temp1 = CLAMP(temp1, -0xFA0, 0xFA0);

        temp1 += (s16)(s32)(D_80862B3C * -500.0f);

        temp1 = CLAMP(temp1, -0x2EE0, 0x2EE0);

        temp2 = CLAMP(-temp2, -0xFA0, 0xFA0);

        Math_ScaledStepToS(&this->unk_AB2.x, temp1, 0x384);
        this->unk_AAC.x = -(f32)this->unk_AB2.x * 0.5f;
        Math_ScaledStepToS(&this->unk_AAC.z, temp2, 0x12C);
        Math_ScaledStepToS(&this->unk_AB2.z, temp2, 0xC8);
        this->unk_AA6 |= 0x168;
    } else {
        func_8083C6E8(this, play);
    }
}

void func_8083CB04(Player* this, f32 arg1, s16 arg2, f32 arg3, f32 arg4, s16 arg5) {
    Math_AsymStepToF(&this->linearVelocity, arg1, arg3, arg4);
    Math_ScaledStepToS(&this->currentYaw, arg2, arg5);
}

void func_8083CB58(Player* this, f32 arg1, s16 arg2) {
    func_8083CB04(this, arg1, arg2, REG(19) / 100.0f, 1.5f, REG(27));
}

s32 func_8083CBC4(Player* this, f32 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    s16 temp_v0 = this->currentYaw - arg2;

    if ((this->unk_B50 * 1.5f) < fabsf(this->linearVelocity)) {
        arg5 *= 4.0f;
        arg3 *= 4.0f;
    }

    if (ABS_ALT(temp_v0) > 0x6000) {
        if (Math_StepToF(&this->linearVelocity, 0.0f, arg3) == 0) {
            return false;
        }

        this->currentYaw = arg2;
    } else {
        Math_AsymStepToF(&this->linearVelocity, arg1, arg4, arg5);
        Math_ScaledStepToS(&this->currentYaw, arg2, arg6);
    }

    return true;
}

struct_8085D224 D_8085D224[][2] = {
    {
        { &gameplay_keep_Linkanim_00E068, 35.17f, 6.6099997f },
        { &gameplay_keep_Linkanim_00E078, -34.16f, 7.91f },
    },
    {
        { &gameplay_keep_Linkanim_00D0E8, 22.718237f, 2.3294117f },
        { &gameplay_keep_Linkanim_00D0F0, -22.0f, 1.9800001f },
    },
};

u16 D_8085D254[] = {
    0x1804, // PLAYER_FORM_GORON
    0x1805, // PLAYER_FORM_ZORA
    0x1806, // PLAYER_FORM_DEKU
    0x1806, // PLAYER_FORM_HUMAN
};

u16 D_8085D25C[] = {
    0x1804, // PLAYER_FORM_FIERCE_DEITY
    0x1804, // PLAYER_FORM_GORON
    0x1805, // PLAYER_FORM_ZORA
    0x1806, // PLAYER_FORM_DEKU
};

// Player_MountHorse
s32 func_8083CCB4(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;

    if (rideActor != NULL) {
        if ((rideActor->type != HORSE_TYPE_2) && (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
            if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                if (ActorCutscene_GetCanPlayNext(0x7C)) {
                    rideActor->actor.textId = D_8085D254[this->transformation - 1];
                    func_8085B460(play, &rideActor->actor);
                    return true;
                }
            }

            ActorCutscene_SetIntentToPlay(0x7C);
        } else if ((rideActor->type == HORSE_TYPE_2) && (this->transformation != PLAYER_FORM_HUMAN)) {
            if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                if (ActorCutscene_GetCanPlayNext(0x7C)) {
                    rideActor->actor.textId = D_8085D25C[this->transformation];
                    func_8085B460(play, &rideActor->actor);
                    return true;
                }
            }

            ActorCutscene_SetIntentToPlay(0x7C);
        } else {
            if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                s32 pad[2];
                f32 sp28 = Math_CosS(rideActor->actor.shape.rot.y);
                f32 sp24 = Math_SinS(rideActor->actor.shape.rot.y);
                struct_8085D224* entry;
                f32 temp_fv0;
                f32 temp_fv1;

                func_80832558(play, this, func_80837BD0);

                this->stateFlags1 |= PLAYER_STATE1_800000;
                this->actor.bgCheckFlags &= ~0x20;
                this->isBurning = false;

                if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
                    entry = D_8085D224[0];
                } else {
                    entry = D_8085D224[1];
                }
                if (this->mountSide >= 0) {
                    entry++;
                }

                temp_fv0 = entry->unk_4;
                temp_fv1 = entry->unk_8;
                this->actor.world.pos.x =
                    rideActor->actor.world.pos.x + rideActor->riderPos.x + ((temp_fv0 * sp28) + (temp_fv1 * sp24));
                this->actor.world.pos.z =
                    rideActor->actor.world.pos.z + rideActor->riderPos.z + ((temp_fv1 * sp28) - (temp_fv0 * sp24));
                this->unk_B48 = rideActor->actor.world.pos.y - this->actor.world.pos.y;

                this->currentYaw = this->actor.shape.rot.y = rideActor->actor.shape.rot.y;

                Actor_MountHorse(play, this, &rideActor->actor);
                Player_AnimationPlayOnce(play, this, entry->anim);
                func_8082E920(play, this, 1 | 2 | 8 | 0x10 | 0x80);
                this->actor.parent = this->rideActor;
                func_8082DAD4(this);
                Actor_DisableLens(play);

                return true;
            }
        }
    }

    return false;
}

LinkAnimationHeader* D_8085D264[] = {
    &gameplay_keep_Linkanim_00DC00,
    &gameplay_keep_Linkanim_00DEC0,
};

s32 func_8083CF68(PlayState* play, Player* this) {
    if (!Player_InBlockingCsMode(play, this) && !(this->cylinder.base.ocFlags1 & 2)) {
        if ((func_80853D68 != this->actionFunc) && (func_80857BE8 != this->actionFunc) && (D_80862B40 == 1)) {
            s16 sp56;
            Vec3f slopeNormal;
            s16 downwardSlopeYaw;
            s16 temp_v0_2;
            f32 temp_ft4;
            f32 temp_fv1;
            f32 var_fa1;
            f32 var_ft5;

            sp56 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
            Actor_GetSlopeDirection(this->actor.floorPoly, &slopeNormal, &downwardSlopeYaw);

            temp_v0_2 = downwardSlopeYaw - sp56;
            if (ABS_ALT(temp_v0_2) > 16000) {
                var_fa1 = (func_80857BE8 == this->actionFunc) ? Math_CosS(this->unk_B6C) : slopeNormal.y;
                temp_ft4 = (1.0f - var_fa1) * 40.0f;
                temp_fv1 = fabsf(this->actor.speedXZ) + temp_ft4;
                var_ft5 = temp_fv1 * temp_fv1 * 0.011f;
                var_ft5 = CLAMP_MIN(var_ft5, 2.2f);
                this->unk_B84 = downwardSlopeYaw;
                Math_StepToF(&this->unk_B80, temp_ft4, var_ft5);
            } else {
                Player_SetAction(play, this, func_80853D68, 0);
                func_8082DE50(play, this);
                func_8082E514(play, this, D_8085D264[this->unk_AE7]);
                this->linearVelocity = sqrtf(SQXZ(this->actor.velocity));
                this->currentYaw = downwardSlopeYaw;
                if (D_80862B28 >= 0) {
                    this->unk_AE7 = 1;
                    func_8082DF8C(this, NA_SE_VO_LI_HANG);
                }

                return true;
            }
        }
    }

    return false;
}

void func_8083D168(PlayState* play, Player* this, GetItemEntry* giEntry) {
    Item00Type dropType = GIFIELD_GET_DROP_TYPE(giEntry->field);

    if (!(giEntry->field & GIFIELD_NO_COLLECTIBLE)) {
        Item_DropCollectible(play, &this->actor.world.pos, dropType | 0x8000);

        if ((dropType == ITEM00_BOMBS_A) || (dropType == ITEM00_ARROWS_30) || (dropType == ITEM00_ARROWS_40) ||
            (dropType == ITEM00_ARROWS_50) || (dropType == ITEM00_RUPEE_GREEN) || (dropType == ITEM00_RUPEE_BLUE) ||
            (dropType == ITEM00_RUPEE_RED) || (dropType == ITEM00_RUPEE_PURPLE) || (dropType == ITEM00_RUPEE_HUGE)) {
            return;
        }
    }

    Item_Give(play, giEntry->itemId);
    play_sound((this->getItemId < 0) ? NA_SE_SY_GET_BOXITEM : NA_SE_SY_GET_ITEM);
}

s32 func_8083D23C(Player* this, PlayState* play) {
    if (gSaveContext.save.playerData.health != 0) {
        Actor* interactRangeActor = this->interactRangeActor;

        if (interactRangeActor != NULL) {
            if (this->getItemId > GI_NONE) {
                if (this->getItemId < GI_MAX) {
                    GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

                    interactRangeActor->parent = &this->actor;
                    if ((Item_CheckObtainability(giEntry->itemId) == ITEM_NONE) ||
                        ((s16)giEntry->objectId == OBJECT_GI_BOMB_2)) {
                        func_8082DCA0(play, this);
                        func_80838830(this, giEntry->objectId);

                        if (!(this->stateFlags2 & PLAYER_STATE2_400) ||
                            (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER)) {
                            func_80838760(this);
                            func_808324EC(play, this, func_80837C78, play->playerActorCsIds[1]);
                            func_8082DB90(play, this,
                                          (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2C0
                                                                                     : &gameplay_keep_Linkanim_00D5B0);
                        }

                        this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
                        func_8082DAD4(this);

                        return true;
                    }

                    func_8083D168(play, this, giEntry);
                    this->getItemId = GI_NONE;
                }
            } else if (this->csMode == PLAYER_CSMODE_0) {
                if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                    if (this->getItemId != GI_NONE) {
                        if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                            GetItemEntry* giEntry = &sGetItemTable[-this->getItemId - 1];
                            EnBox* chest = (EnBox*)interactRangeActor;

                            if ((giEntry->itemId != ITEM_NONE) &&
                                (((Item_CheckObtainability(giEntry->itemId) == ITEM_NONE) &&
                                  (giEntry->field & GIFIELD_40)) ||
                                 (((Item_CheckObtainability(giEntry->itemId) != ITEM_NONE)) &&
                                  (giEntry->field & GIFIELD_20)))) {
                                this->getItemId =
                                    (giEntry->itemId == ITEM_MASK_CAPTAIN) ? -GI_RECOVERY_HEART : -GI_RUPEE_BLUE;
                                giEntry = &sGetItemTable[-this->getItemId - 1];
                            }

                            func_80832558(play, this, func_80837C78);
                            this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
                            func_80838830(this, giEntry->objectId);

                            this->actor.world.pos.x =
                                interactRangeActor->world.pos.x -
                                (Math_SinS(interactRangeActor->shape.rot.y) * this->ageProperties->unk_9C);
                            this->actor.world.pos.z =
                                interactRangeActor->world.pos.z -
                                (Math_CosS(interactRangeActor->shape.rot.y) * this->ageProperties->unk_9C);
                            this->actor.world.pos.y = interactRangeActor->world.pos.y;
                            this->currentYaw = this->actor.shape.rot.y = interactRangeActor->shape.rot.y;

                            func_8082DAD4(this);
                            if ((giEntry->itemId != ITEM_NONE) && (giEntry->unk_2 >= 0) &&
                                (Item_CheckObtainability(giEntry->itemId) == ITEM_NONE)) {
                                this->unk_A86 = chest->cutsceneIdxB;
                                func_8082DB90(play, this, this->ageProperties->unk_A0);
                                func_8082E920(play, this, 1 | 2 | 4 | 8 | 0x10 | 0x80);
                                this->actor.bgCheckFlags &= ~0x20;
                                chest->unk_1EC = 1;
                            } else {
                                Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DB18);
                                chest->unk_1EC = -1;
                            }

                            return true;
                        }
                    } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                               (this->transformation != PLAYER_FORM_DEKU)) {
                        if ((this->heldActor == NULL) || Player_IsHoldingHookshot(this)) {
                            EnBom* bomb = (EnBom*)interactRangeActor;

                            if (((this->transformation != PLAYER_FORM_GORON) &&
                                 (((bomb->actor.id == ACTOR_EN_BOM) && bomb->isPowderKeg) ||
                                  ((interactRangeActor->id == ACTOR_EN_ISHI) && (interactRangeActor->params & 1)) ||
                                  (interactRangeActor->id == ACTOR_EN_MM)))) {
                                return false;
                            }

                            this->stateFlags2 |= PLAYER_STATE2_10000;
                            if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
                                func_80832558(play, this, func_808379C0);
                                func_8082DAD4(this);
                                this->stateFlags1 |= PLAYER_STATE1_800;

                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

void func_8083D6DC(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084E65C, 1);
    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_28][this->modelAnimType]);
}

s32 func_8083D738(Player* this, Actor* heldActor) {
    if ((heldActor != NULL) && !(heldActor->flags & ACTOR_FLAG_800000) &&
        ((this->linearVelocity < 1.1f) || (heldActor->id == ACTOR_EN_BOM_CHU))) {
        return false;
    }
    return true;
}

s32 func_8083D78C(Player* this, PlayState* play) {
    if (this->stateFlags1 & PLAYER_STATE1_800) {
        if ((this->heldActor != NULL) &&
            CHECK_BTN_ANY(D_80862B44->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
            if (!func_808313A8(play, this, this->heldActor)) {
                if (!func_8083D738(this, this->heldActor)) {
                    Player_SetAction(play, this, func_8084E58C, 1);
                    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_29][this->modelAnimType]);
                    return true;
                }
                func_8083D6DC(this, play);
            }

            return true;
        }
    }
    return false;
}

#ifdef NON_EQUIVALENT
s32 func_8083D860(Player* this, PlayState* play) {
    s32 var_t0;  // sp84
    s32 temp_t2; // sp80
    CollisionPoly* sp7C;
    f32 var_fa1; // sp78
    f32 var_ft4; // sp74

    f32 var_ft5; // sp6C
    Vec3f sp48[3];

    f32 sp40;
    Vec3f* sp3C;

    f32 sp34;
    f32 sp30;
    f32 temp_fv0_4;              // sp2C
    LinkAnimationHeader* var_a2; // sp28

    if ((this->wallHeight >= 79.0f) && ((!(this->stateFlags1 & 0x8000000)) || (this->currentBoots == 5) ||
                                        (this->actor.depthInWater < this->ageProperties->unk_2C))) {
        var_t0 = (D_80862B0C & 8) ? 2 : 0;

        temp_t2 = D_80862B0C & 2;
        if ((var_t0 != 0) || (temp_t2 != 0) ||
            (func_800C9AE4(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId) != 0)) {
            f32 var_fv0;
            f32 var_fv1;

            var_fv1 = 0.0f;
            var_ft5 = 0.0f;
            sp7C = this->actor.wallPoly;
            if (var_t0 != 0) {
                var_fa1 = this->actor.world.pos.x;
                var_ft4 = this->actor.world.pos.z;
            } else {
                s32 var_v1;
                f32 zMax; // var_fa0;
                f32 xMin; // var_fa1_2;
                f32 zMin; // var_ft4_2
                f32 yMin; // var_ft5_2
                f32 xMax; // var_fv1_2

                sp3C = sp48;
                CollisionPoly_GetVerticesByBgId(sp7C, this->actor.wallBgId, &play->colCtx, sp48);
                xMin = xMax = sp48[0].x;
                zMin = zMax = sp48[0].z;
                yMin = sp48[0].y;

                for (var_v1 = 1; var_v1 < ARRAY_COUNT(sp48); var_v1++) {
                    sp3C += 1;

                    if (sp3C->x < xMin) {
                        xMin = sp3C->x;
                    } else if (xMax < sp3C->x) {
                        xMax = sp3C->x;
                    }

                    if (sp3C->z < zMin) {
                        zMin = sp3C->z;
                    } else if (zMax < sp3C->z) {
                        zMax = sp3C->z;
                    }

                    if (sp3C->y < yMin) {
                        yMin = sp3C->y;
                    }
                }

                var_fa1 = (xMin + xMax) * 0.5f;
                var_ft4 = (zMin + zMax) * 0.5f;
                sp40 = this->actor.world.pos.y - yMin;

                // if (1) { }

                var_fv1 = fabsf(((this->actor.world.pos.x - var_fa1) * COLPOLY_GET_NORMAL(sp7C->normal.z)) -
                                ((this->actor.world.pos.z - var_ft4) * COLPOLY_GET_NORMAL(sp7C->normal.x)));
                var_ft5 = ((s32)((sp40 / 15.0f) + 0.5f) * 15.0f) - sp40;
            }

            if (var_fv1 < 8.0f) {
                sp34 = COLPOLY_GET_NORMAL(sp7C->normal.x);
                sp30 = COLPOLY_GET_NORMAL(sp7C->normal.z);
                temp_fv0_4 = this->wallDistance;
                func_80832558(play, this, func_80837C20);

                this->stateFlags1 |= PLAYER_STATE1_200000;
                this->stateFlags1 &= ~PLAYER_STATE1_8000000;

                if ((var_t0 != 0) || (temp_t2 != 0)) {
                    this->unk_AE7 = var_t0;

                    if (var_t0 != 0) {
                        var_a2 = (this->actor.bgCheckFlags & 1) ? &gameplay_keep_Linkanim_00DAA0
                                                                : &gameplay_keep_Linkanim_00DA88;
                        var_fv0 = (this->ageProperties->unk_3C + 4.0f) - temp_fv0_4;
                    } else {
                        var_a2 = this->ageProperties->unk_AC;
                        var_fv0 = 20.5f;
                    }

                    this->unk_AE8 = -2;
                    this->actor.world.pos.y += var_ft5;

                    this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
                } else {
                    var_a2 = this->ageProperties->unk_B0;
                    var_fv0 = (this->ageProperties->unk_38 - this->ageProperties->unk_3C) + 17.0f;

                    this->unk_AE8 = -4;
                    this->currentYaw = this->actor.shape.rot.y = this->actor.wallYaw;
                }

                this->actor.world.pos.x = (var_fv0 * sp34) + var_fa1;
                this->actor.world.pos.z = (var_fv0 * sp30) + var_ft4;
                func_8082DAD4(this);
                Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                Player_AnimationPlayOnce(play, this, var_a2);
                func_8082E920(play, this, 0x9F);
                return 1;
            }
        }
    }

    return 0;
}
#else
s32 func_8083D860(Player* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D860.s")
#endif

void func_8083DCC4(Player* this, LinkAnimationHeader* anim, PlayState* play) {
    func_8083172C(play, this, func_8084FC0C, 0);
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 4.0f / 3.0f);
}

s32 func_8083DD1C(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    CollisionPoly* wallPoly;
    s32 bgId;
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 cos = Math_CosS(this->actor.shape.rot.y);
    f32 sin = Math_SinS(this->actor.shape.rot.y);

    sp74.x = this->actor.world.pos.x + (arg5 * sin);
    sp74.z = this->actor.world.pos.z + (arg5 * cos);
    sp68.x = this->actor.world.pos.x + (arg4 * sin);
    sp68.z = this->actor.world.pos.z + (arg4 * cos);
    sp74.y = sp68.y = this->actor.world.pos.y + arg2;

    if (BgCheck_EntityLineTest2(&play->colCtx, &sp74, &sp68, &sp5C, &this->actor.wallPoly, 1, 0, 0, 1, &bgId,
                                &this->actor)) {
        f32 wallPolyNormalX;
        f32 wallPolyNormalZ;

        wallPoly = this->actor.wallPoly;
        this->actor.bgCheckFlags |= 0x200;
        this->actor.wallBgId = bgId;
        D_80862B0C = func_800C9A4C(&play->colCtx, wallPoly, bgId);

        wallPolyNormalX = COLPOLY_GET_NORMAL(wallPoly->normal.x);
        wallPolyNormalZ = COLPOLY_GET_NORMAL(wallPoly->normal.z);

        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_FAtan2F(-wallPolyNormalZ, -wallPolyNormalX), 0x320);

        this->currentYaw = this->actor.shape.rot.y;
        this->actor.world.pos.x = sp5C.x - (Math_SinS(this->actor.shape.rot.y) * arg3);
        this->actor.world.pos.z = sp5C.z - (Math_CosS(this->actor.shape.rot.y) * arg3);

        return true;
    }

    this->actor.bgCheckFlags &= ~0x200;
    return false;
}

void func_8083DEE4(PlayState* play, Player* this) {
    f32 temp_fv0 = this->ageProperties->unk_38;

    func_8083DD1C(play, this, 26.800001f, temp_fv0 + 5.0f, temp_fv0 + 15.0f, 0.0f);
}

void func_8083DF38(Player* this, LinkAnimationHeader* anim, PlayState* play) {
    if (!func_80832558(play, this, func_80837BF8)) {
        Player_SetAction(play, this, func_8084ED9C, 0);
    }

    Player_AnimationPlayOnce(play, this, anim);
    func_8082DAD4(this);

    this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
}

s32 func_8083DFC4(Player* this, PlayState* play) {
    if (!(this->stateFlags1 & PLAYER_STATE1_800) && (this->actor.bgCheckFlags & 0x200) && (D_80862B20 < 0x3000)) {
        if ((this->linearVelocity > 0.0f) && func_8083D860(this, play)) {
            return true;
        }

        if (!func_801242B4(this) && ((this->linearVelocity == 0.0f) || !(this->stateFlags2 & PLAYER_STATE2_4)) &&
            (D_80862B0C & 0x40) && (this->actor.bgCheckFlags & 1) && (this->wallHeight >= 39.0f)) {
            this->stateFlags2 |= PLAYER_STATE2_1;

            if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) {
                DynaPolyActor* dyna;

                if ((this->actor.wallBgId != BGCHECK_SCENE) &&
                    ((dyna = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId)) != NULL)) {
                    this->rightHandActor = &dyna->actor;
                } else {
                    this->rightHandActor = NULL;
                }

                func_8083DF38(this, &gameplay_keep_Linkanim_00DE00, play);
                return true;
            }
        }
    }

    return false;
}

s32 func_8083E14C(PlayState* play, Player* this) {
    if ((this->actor.bgCheckFlags & 0x200) &&
        ((this->stateFlags2 & PLAYER_STATE2_10) || CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A))) {
        DynaPolyActor* var_v1 = NULL;

        if (this->actor.wallBgId != BGCHECK_SCENE) {
            var_v1 = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);
        }

        if (&var_v1->actor == this->rightHandActor) {
            if (this->stateFlags2 & PLAYER_STATE2_10) {
                return true;
            }
            return false;
        }
    }

    func_808369F4(this, play);
    Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DE08);
    this->stateFlags2 &= ~PLAYER_STATE2_10;
    return true;
}

void func_8083E234(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084EE50, 0);
    Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DDF8);
    this->stateFlags2 |= PLAYER_STATE2_10;
}

void func_8083E28C(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084EF9C, 0);
    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_34][this->modelAnimType]);
    this->stateFlags2 |= PLAYER_STATE2_10;
}

void func_8083E2F4(Player* this, PlayState* play) {
    this->stateFlags1 &= ~(PLAYER_STATE1_200000 | PLAYER_STATE1_8000000);
    func_80833AA0(this, play);

    if (this->transformation == PLAYER_FORM_DEKU) {
        this->linearVelocity = -1.7f;
    } else {
        this->linearVelocity = -0.4f;
    }
}

s32 func_8083E354(Player* this, PlayState* play) {
    if (!CHECK_BTN_ALL(D_80862B44->press.button, BTN_A) && (this->actor.bgCheckFlags & 0x200)) {
        if ((D_80862B0C & 8) || (D_80862B0C & 2) ||
            func_800C9AE4(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
            return false;
        }
    }

    func_8083E2F4(this, play);
    func_8082DF8C(this, NA_SE_VO_LI_AUTO_JUMP);
    return true;
}

s32 func_8083E404(Player* this, f32 arg1, s16 arg2) {
    f32 sp1C = BINANG_SUB(arg2, this->actor.shape.rot.y);
    f32 temp_fv1;

    if (this->targetedActor != NULL) {
        func_8083C62C(this, func_800B7128(this) || func_8082EF20(this));
    }

    temp_fv1 = fabsf(sp1C) / 0x8000;
    if (((SQ(temp_fv1) * 50.0f) + 6.0f) < arg1) {
        return 1;
    }

    if ((((1.0f - temp_fv1) * 10.0f) + 6.8f) < arg1) {
        return -1;
    }
    return 0;
}

s32 func_8083E514(Player* this, f32* arg2, s16* arg3, PlayState* play) {
    s16 temp_v1 = *arg3 - this->targetYaw;
    u16 var_a2;

    var_a2 = ABS_ALT(temp_v1);

    if ((func_800B7128(this) || func_8082EF20(this)) && (this->targetedActor == NULL)) {
        *arg2 *= Math_SinS(var_a2);

        if (*arg2 != 0.0f) {
            *arg3 = (((temp_v1 >= 0) ? 1 : -1) * 0x4000) + this->actor.shape.rot.y;
        } else {
            *arg3 = this->actor.shape.rot.y;
        }

        if (this->targetedActor != NULL) {
            func_8083C62C(this, true);
        } else {
            Math_SmoothStepToS(&this->actor.focus.rot.x, (D_80862B44->rel.stick_y * 240.0f), 0xE, 0xFA0, 0x1E);
            func_80832754(this, true);
        }
    } else {
        if (this->targetedActor != NULL) {
            return func_8083E404(this, *arg2, *arg3);
        }

        func_8083C6E8(this, play);
        if ((*arg2 != 0.0f) && (var_a2 < 0x1770)) {
            return 1;
        }

        if ((Math_SinS(0x4000 - (var_a2 >> 1)) * 200.0f) < *arg2) {
            return -1;
        }
    }
    return 0;
}

s32 func_8083E758(Player* this, f32* arg1, s16* arg2) {
    f32 temp_fv0;
    u16 temp_v0;
    s16 var_v1;

    var_v1 = *arg2 - this->actor.shape.rot.y;
    temp_v0 = ABS_ALT(var_v1);
    temp_fv0 = Math_CosS(temp_v0);
    *arg1 *= temp_fv0;

    // Can't be (*arg1 != 0.0f)
    if (*arg1 != 0) {
        if (temp_fv0 > 0.0f) {
            return 1;
        }
        return -1;
    }
    return 0;
}

s32 func_8083E7F8(Player* this, f32* arg1, s16* arg2, PlayState* play) {
    func_8083C6E8(this, play);

    if ((*arg1 != 0.0f) || (ABS_ALT(this->unk_B4C) > 0x190)) {
        s16 temp_a0 = *arg2 - (u16)Camera_GetInputDirYaw(play->cameraPtrs[play->activeCamId]);
        u16 temp;

        temp = (ABS_ALT(temp_a0) - 0x2000);
        if ((temp < 0x4000) || (this->unk_B4C != 0)) {
            return -1;
        }
        return 1;
    }

    return 0;
}

void func_8083E8E0(Player* this, f32 arg1, s16 arg2) {
    s16 temp = arg2 - this->actor.shape.rot.y;

    if (arg1 > 0.0f) {
        if (temp < 0) {
            this->unk_B44 = 0.0f;
        } else {
            this->unk_B44 = 1.0f;
        }
    }

    Math_StepToF(&this->unk_B40, this->unk_B44, 0.3f);
}

void func_8083E958(PlayState* play, Player* this) {
    LinkAnimation_BlendToJoint(play, &this->skelAnime, func_8082EF54(this), this->unk_B38, func_8082EF9C(this),
                               this->unk_B38, this->unk_B40, this->blendTableBuffer);
}

s32 func_8083E9C4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;

    if ((arg3 == 0.0f) && (arg1 > 0.0f)) {
        arg3 = arg2;
    }
    temp_fv0 = (arg0 + arg1) - arg3;
    if (((temp_fv0 * arg1) >= 0.0f) && (((temp_fv0 - arg1) * arg1) < 0.0f)) {
        return true;
    }
    return false;
}

void func_8083EA44(Player* this, f32 arg1) {
    s32 sp24;
    f32 updateScale = R_UPDATE_RATE / 2.0f;

    arg1 *= updateScale;
    if (arg1 < -7.25f) {
        arg1 = -7.25f;
    } else if (arg1 > 7.25f) {
        arg1 = 7.25f;
    }

    sp24 = func_8083E9C4(this->unk_B38, arg1, 29.0f, 10.0f);

    if (sp24 || func_8083E9C4(this->unk_B38, arg1, 29.0f, 24.0f)) {
        func_8082E12C(this, this->linearVelocity);
        if (this->linearVelocity > 4.0f) {
            this->stateFlags2 |= 8;
        }
        this->actor.shape.unk_17 = sp24 ? 1 : 2;
    }

    this->unk_B38 += arg1;
    if (this->unk_B38 < 0.0f) {
        this->unk_B38 += 29.0f;
    } else if (this->unk_B38 >= 29.0f) {
        this->unk_B38 -= 29.0f;
    }
}

void Player_ChooseIdleAnim(PlayState* play, Player* this) {
    LinkAnimationHeader* anim;
    u32 healthIsCritical;
    LinkAnimationHeader** animPtr;
    s32 animIndex;
    s32 rand;
    f32 morphFrames;
    s16 lastFrame;

    if (((this->actor.id != ACTOR_PLAYER) && !(healthIsCritical = (this->actor.colChkInfo.health < 0x64))) ||
        ((this->actor.id == ACTOR_PLAYER) &&
         (((this->targetedActor != NULL) ||
           ((this->transformation != PLAYER_FORM_FIERCE_DEITY) && (this->transformation != PLAYER_FORM_HUMAN)) ||
           (this->currentMask == PLAYER_MASK_SCENTS)) ||
          (!(healthIsCritical = LifeMeter_IsCritical()) && (this->unk_AA4 = ((this->unk_AA4 + 1) & 1)))))) {
        this->stateFlags2 &= ~PLAYER_STATE2_10000000;
        anim = func_8082ED20(this);
    } else {
        this->stateFlags2 |= PLAYER_STATE2_10000000;

        if (this->stateFlags1 & PLAYER_STATE1_800) {
            anim = func_8082ED20(this);
        } else {
            animIndex = play->roomCtx.currRoom.unk2;

            if (healthIsCritical) {
                if (this->unk_AA4 >= 0) {
                    animIndex = 7;
                    this->unk_AA4 = -1;
                } else {
                    animIndex = 8;
                }
            } else {
                rand = Rand_ZeroOne() * 5.0f;
                if (rand < 4) {
                    if (((rand != 0) && (rand != 3)) || ((this->rightHandType == PLAYER_MODELTYPE_RH_SHIELD) &&
                                                         ((rand == 3) || (Player_GetMeleeWeaponHeld(this) != 0)))) {
                        if ((rand == 0) && Player_IsHoldingTwoHandedWeapon(this)) {
                            rand = 4;
                        }
                        animIndex = rand + 9;
                    }
                }
            }

            animPtr = &sPlayerIdleAnimations[animIndex][0];
            if (this->modelAnimType != PLAYER_ANIMTYPE_1) {
                animPtr = &sPlayerIdleAnimations[animIndex][1];
            }
            anim = *animPtr;
        }
    }

    lastFrame = Animation_GetLastFrame(anim);
    if ((this->skelAnime.animation == anim) || (this->skelAnime.animation == &gameplay_keep_Linkanim_00E318) ||
        (this->skelAnime.animation == &gameplay_keep_Linkanim_00E330) ||
        (this->skelAnime.animation == &gameplay_keep_Linkanim_00E348)) {
        morphFrames = 0.0f;
    } else {
        morphFrames = -6.0f;
    }

    LinkAnimation_Change(play, &this->skelAnime, anim, (2.0f / 3.0f) * D_8085C3E4, 0.0f, lastFrame, ANIMMODE_ONCE,
                         morphFrames);
}

void func_8083EE60(Player* this, PlayState* play) {
    f32 temp_fv0;
    f32 var_fs0;

    if (this->unk_B34 < 1.0f) {
        f32 temp_fs0 = R_UPDATE_RATE / 2.0f;

        func_8083EA44(this, REG(35) / 1000.0f);
        LinkAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                  this->unk_B38);
        this->unk_B34 += (1.0f * 1.0f) * temp_fs0;
        if (this->unk_B34 >= 1.0f) {
            this->unk_B34 = 1.0f;
        }
        var_fs0 = this->unk_B34;
    } else {
        temp_fv0 = this->linearVelocity - (REG(48) / 100.0f);

        if (temp_fv0 < 0.0f) {
            var_fs0 = 1.0f;
            func_8083EA44(this, ((REG(35)) / 1000.0f) + (((REG(36)) / 1000.0f) * this->linearVelocity));

            LinkAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                      this->unk_B38);
        } else {
            var_fs0 = (REG(37) / 1000.0f) * temp_fv0;
            if (var_fs0 < 1.0f) {
                func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            } else {
                var_fs0 = 1.0f;
                func_8083EA44(this, (REG(39) / 100.0f) + ((REG(38) / 1000.0f) * temp_fv0));
            }

            LinkAnimation_LoadToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                      this->unk_B38);
            LinkAnimation_LoadToJoint(play, &this->skelAnime, &gameplay_keep_Linkanim_00DAF0,
                                      this->unk_B38 * (16.0f / 29.0f));
        }
    }
    if (var_fs0 < 1.0f) {
        LinkAnimation_InterpJointMorph(play, &this->skelAnime, 1.0f - var_fs0);
    }
}

void func_8083F144(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084A794, 1);
    func_8082E438(play, this, &gameplay_keep_Linkanim_00DAC0);
}

s32 func_8083F190(Player* this, f32* arg1, s16* arg2, PlayState* play) {
    if (this->linearVelocity > 6.0f) {
        func_8083F144(this, play);
        return true;
    }

    if (*arg1 != 0.0f) {
        if (func_80832F24(this)) {
            *arg1 = 0.0f;
            *arg2 = this->currentYaw;
        } else {
            return true;
        }
    }
    return false;
}

void func_8083F230(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084A884, 1);
    Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DAC8);
}

void func_8083F27C(PlayState* play, Player* this) {
    f32 temp_fv0;
    LinkAnimationHeader* sp38;
    LinkAnimationHeader* sp34;

    sp38 = D_8085BE84[PLAYER_ANIMGROUP_23][this->modelAnimType];
    sp34 = D_8085BE84[PLAYER_ANIMGROUP_24][this->modelAnimType];

    this->skelAnime.animation = sp38;

    func_8083EA44(this, (REG(30) / 1000.0f) + ((REG(32) / 1000.0f) * this->linearVelocity));

    temp_fv0 = this->unk_B38 * (16.0f / 29.0f);
    LinkAnimation_BlendToJoint(play, &this->skelAnime, sp34, temp_fv0, sp38, temp_fv0, this->unk_B40,
                               this->blendTableBuffer);
}

void func_8083F358(Player* this, s32 arg1, PlayState* play) {
    LinkAnimationHeader* var_v0;
    f32 var_fv1;
    s16 var_a1;

    if (ABS_ALT(D_80862B28) < 0xE38) {
        var_a1 = 0;
    } else {
        var_a1 = CLAMP(D_80862B28, -0x2AAA, 0x2AAA);
    }

    Math_ScaledStepToS(&this->unk_B70, var_a1, 0x190);
    if ((this->modelAnimType == PLAYER_ANIMTYPE_3) || ((this->unk_B70 == 0) && (this->unk_AB8 <= 0.0f))) {
        if (arg1 == 0) {
            LinkAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                      this->unk_B38);
        } else {
            LinkAnimation_LoadToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                      this->unk_B38);
        }
        return;
    }

    if (this->unk_B70 != 0) {
        var_fv1 = this->unk_B70 / 10922.0f;
    } else {
        var_fv1 = this->unk_AB8 * 0.0006f;
    }

    var_fv1 *= fabsf(this->linearVelocity) * 0.5f;
    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    if (var_fv1 < 0.0f) {
        var_v0 = &gameplay_keep_Linkanim_00DB68;
        var_fv1 = -var_fv1;
    } else {
        var_v0 = &gameplay_keep_Linkanim_00DBB0;
    }

    if (arg1 == 0) {
        LinkAnimation_BlendToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                   this->unk_B38, var_v0, this->unk_B38, var_fv1, this->blendTableBuffer);
    } else {
        LinkAnimation_BlendToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                   this->unk_B38, var_v0, this->unk_B38, var_fv1, this->blendTableBuffer);
    }
}

void func_8083F57C(Player* this, PlayState* play) {
    f32 temp_fv0;
    f32 var_fs0;

    if (this->unk_B34 < 1.0f) {
        f32 temp_fs0;

        temp_fs0 = R_UPDATE_RATE / 2.0f;
        func_8083EA44(this, REG(35) / 1000.0f);
        LinkAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                  this->unk_B38);

        // required
        this->unk_B34 += 1 * temp_fs0;
        if (this->unk_B34 >= 1.0f) {
            this->unk_B34 = 1.0f;
        }
        var_fs0 = this->unk_B34;
    } else {
        temp_fv0 = (this->linearVelocity - (REG(48) / 100.0f));
        if (temp_fv0 < 0.0f) {
            var_fs0 = 1.0f;
            func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            func_8083F358(this, 0, play);
        } else {
            var_fs0 = (REG(37) / 1000.0f) * temp_fv0;
            if (var_fs0 < 1.0f) {
                func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            } else {
                var_fs0 = 1.0f;
                func_8083EA44(this, (REG(39) / 100.0f) + ((REG(38) / 1000.0f) * temp_fv0));
            }
            func_8083F358(this, 1, play);
            LinkAnimation_LoadToJoint(play, &this->skelAnime, func_8082EEE0(this), this->unk_B38 * (20.0f / 29.0f));
        }
    }

    if (var_fs0 < 1.0f) {
        LinkAnimation_InterpJointMorph(play, &this->skelAnime, 1.0f - var_fs0);
    }
}

void func_8083F828(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg1->x = randPlusMinusPoint5Scaled(arg3) + arg0->x;
    arg1->y = randPlusMinusPoint5Scaled(arg4) + (arg0->y + arg2);
    arg1->z = randPlusMinusPoint5Scaled(arg3) + arg0->z;
}

Color_RGBA8 D_8085D26C = { 255, 255, 255, 255 };
Vec3f D_8085D270 = { 0.0f, 0.04f, 0.0f };

s32 func_8083F8A8(PlayState* play, Player* this, f32 radius, s32 countMax, f32 randAccelWeight, s32 scale,
                  s32 scaleStep, s32 useLighting) {
    static Vec3f D_8085D27C = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_8085D288 = { 0.0f, 0.0f, 0.0f };

    if ((countMax < 0) || (this->unk_B72 == NA_SE_PL_WALK_SNOW - SFX_FLAG)) {
        s32 count = func_80173B48(&play->state) / 20000000;
        Vec3f pos;
        s32 i;

        count = (count >= ABS_ALT(countMax)) ? ABS_ALT(countMax) : count;
        for (i = 0; i < count; i++) {
            func_8083F828(&this->actor.world.pos, &pos, 0.0f, 40.0f, 10.0f);
            D_8085D27C.x = randPlusMinusPoint5Scaled(3.0f);
            D_8085D27C.z = randPlusMinusPoint5Scaled(3.0f);
            EffectSsDust_Spawn(play, 0, &pos, &D_8085D27C, &D_8085D270, &D_8085D26C, &D_8085D26C, scale, scaleStep, 42,
                               0);
        }

        return true;
    } else if ((this->unk_B72 == NA_SE_PL_WALK_GROUND - SFX_FLAG) || (this->unk_B72 == NA_SE_PL_WALK_SAND - SFX_FLAG)) {
        s32 count = func_80173B48(&play->state) / 12000000;

        if (count > 0) {
            Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos, radius,
                                     (count < countMax) ? count : countMax, randAccelWeight, scale, scaleStep,
                                     useLighting);

            return true;
        }
    } else if (this->unk_B72 == NA_SE_PL_WALK_GRASS - SFX_FLAG) {
        s32 count = func_80173B48(&play->state) / 12000000;
        Vec3f velocity;
        Vec3f pos;
        s32 i;

        count = (count >= countMax) ? countMax : count;
        for (i = 0; i < count; i++) {
            func_8083F828(&this->actor.world.pos, &pos, 0.0f, 20.0f, 20.0f);
            velocity.x = randPlusMinusPoint5Scaled(3.0f);
            velocity.y = Rand_ZeroFloat(2.0f);
            velocity.z = randPlusMinusPoint5Scaled(3.0f);
            D_8085D288.y = -0.1f;
            EffectSsHahen_Spawn(play, &pos, &velocity, &D_8085D288, 0, 0x96, 1, 0x10, gKakeraLeafTip);
        }
    }

    return false;
}

s32 func_8083FBC4(PlayState* play, Player* this) {
    if ((this->unk_B72 == NA_SE_PL_WALK_GROUND - SFX_FLAG) || (this->unk_B72 == NA_SE_PL_WALK_SAND - SFX_FLAG)) {
        Vec3f* feetPos = this->actor.shape.feetPos;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->actor.shape.feetPos); i++) {
            func_800B1210(play, feetPos, &gZeroVec3f, &gZeroVec3f, 50, 30);
            feetPos++;
        }

        return true;
    }

    if (this->unk_B72 == NA_SE_PL_WALK_SNOW - SFX_FLAG) {
        Vec3f* feetPos = this->actor.shape.feetPos;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->actor.shape.feetPos); i++) {
            EffectSsDust_Spawn(play, 0, feetPos, &gZeroVec3f, &D_8085D270, &D_8085D26C, &D_8085D26C, 100, 40, 17, 0);
            feetPos++;
        }

        return true;
    }

    return false;
}

s32 func_8083FCF0(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4) {
    if (arg4 < this->skelAnime.curFrame) {
        func_8082DC38(this);
    } else if (arg2 <= this->skelAnime.curFrame) {
        this->stateFlags3 |= PLAYER_STATE3_2000000;
        func_8082FA5C(play, this, (arg3 <= this->skelAnime.curFrame) ? 1 : -1);
        return true;
    }
    return false;
}

s32 func_8083FD80(Player* this, PlayState* play) {
    if (!Player_IsGoronOrDeku(this) && (Player_GetMeleeWeaponHeld(this) != 0) &&
        (this->transformation != PLAYER_FORM_ZORA) && (D_80862B48 != 0)) {
        func_8083375C(this, PLAYER_MWA_STAB_1H);
        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DBE8);
        this->unk_AE7 = 1;
        this->meleeWeaponAnimation = PLAYER_MWA_STAB_1H;
        this->currentYaw = this->actor.shape.rot.y + this->unk_AB2.y;
        this->unk_ADD = 0;
        return true;
    }
    return false;
}

s32 func_8083FE38(Player* this, PlayState* play) {
    return func_80838A90(this, play) || func_808391D8(this, play) || func_8083D23C(this, play);
}

void func_8083FE90(PlayState* play, Player* this, u16 sfxId) {
    func_80836EA0(play, 0x6C77, 7, 20);
    Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
    func_800B8E58(this, sfxId);
}

void func_8083FEF4(PlayState* play, Player* this) {
    Inventory_ChangeAmmo(ITEM_STICK, -1);
    func_80831990(play, this, ITEM_NONE);
}

s32 func_8083FF30(PlayState* play, Player* this) {
    if ((this->itemActionParam == PLAYER_AP_STICK) && (this->unk_B08[1] > 0.5f)) {
        if (AMMO(ITEM_STICK) != 0) {
            EffectSsStick_Spawn(play, &this->bodyPartsPos[0xF], BINANG_ADD(this->actor.shape.rot.y, 0x8000));
            this->unk_B08[1] = 0.5f;
            func_8083FEF4(play, this);
            func_800B8E58(this, NA_SE_IT_WOODSTICK_BROKEN);
        }
        return true;
    }

    return false;
}

// handles razor sword health and breaking
s32 func_8083FFEC(PlayState* play, Player* this) {
    if (this->itemActionParam == PLAYER_AP_SWORD_RAZOR) {
        if (gSaveContext.save.playerData.swordHealth > 0) {
            gSaveContext.save.playerData.swordHealth--;
            if (gSaveContext.save.playerData.swordHealth <= 0) {
                Item_Give(play, ITEM_SWORD_KOKIRI);
                func_80831990(play, this, ITEM_SWORD_KOKIRI);
                func_800B8E58(this, NA_SE_IT_MAJIN_SWORD_BROKEN);
                if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
                    Message_StartTextbox(play, 0xF9, NULL);
                }
            }
        }
        return true;
    }
    return false;
}

s32 func_80840094(PlayState* play, Player* this) {
    func_8083FF30(play, this);
    return func_8083FFEC(play, this);
}

LinkAnimationHeader* D_8085D294[] = {
    &gameplay_keep_Linkanim_00D8F0,
    &gameplay_keep_Linkanim_00D900,
    &gameplay_keep_Linkanim_00D8E8,
    &gameplay_keep_Linkanim_00D8F8,
};

void func_808400CC(PlayState* play, Player* this) {
    if (func_8084B5C0 != this->actionFunc) {
        func_8082DD2C(play, this);
        if ((this->transformation != PLAYER_FORM_HUMAN) && (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
            u8 moveFlags = this->skelAnime.moveFlags;
            s32 pad;

            this->skelAnime.moveFlags = 0;
            Player_SetAction(play, this, func_80854C70, 0);
            this->skelAnime.moveFlags = moveFlags;
        } else {
            s32 var_v1;
            s32 pad;

            Player_SetAction(play, this, func_80854C70, 0);
            if (func_80123420(this)) {
                var_v1 = 2;
            } else {
                var_v1 = 0;
            }
            func_8082DB90(play, this, D_8085D294[Player_IsHoldingTwoHandedWeapon(this) + var_v1]);
        }
    }

    Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
    this->linearVelocity = -18.0f;
    func_80840094(play, this);
}

s32 func_808401F4(PlayState* play, Player* this) {
    if (this->meleeWeaponState > 0) {
        s32 temp_v0_3;

        if (this->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H) {
            if (!(this->meleeWeaponQuads[0].base.atFlags & 4) && !(this->meleeWeaponQuads[1].base.atFlags & 4)) {
                if (this->skelAnime.curFrame >= 2.0f) {
                    CollisionPoly* poly;
                    s32 bgId;
                    Vec3f spC8;
                    Vec3f pos;
                    Vec3f spB0;
                    Vec3f* var_a1;
                    Vec3f* temp_a0 = &this->meleeWeaponInfo[0].tip;
                    f32 var_fv1;

                    if (this->linearVelocity >= 0.0f) {
                        var_a1 = &this->meleeWeaponInfo[0].base;
                        if ((this->transformation == PLAYER_FORM_GORON) || (this->actor.id == ACTOR_EN_TEST3)) {
                            var_a1 = &this->unk_AF0[1];
                        }

                        var_fv1 = Math_Vec3f_DistXYZAndStoreDiff(temp_a0, var_a1, &spB0);
                        if (var_fv1 != 0.0f) {
                            var_fv1 = (var_fv1 + 10.0f) / var_fv1;
                        }

                        spC8.x = temp_a0->x + (spB0.x * var_fv1);
                        spC8.y = temp_a0->y + (spB0.y * var_fv1);
                        spC8.z = temp_a0->z + (spB0.z * var_fv1);
                        if (BgCheck_EntityLineTest2(&play->colCtx, &spC8, temp_a0, &pos, &poly, 1, 0, 0, 1, &bgId,
                                                    &this->actor)) {
                            if (!SurfaceType_IsIgnoredByEntities(&play->colCtx, poly, bgId) &&
                                (func_800C99D4(&play->colCtx, poly, bgId) != 6) &&
                                !func_800B90AC(play, &this->actor, poly, bgId, &pos)) {
                                if (this->transformation == PLAYER_FORM_GORON) {
                                    MtxF sp64;
                                    Vec3s actorRot;
                                    DynaPolyActor* temp_v0;

                                    func_8082DF2C(play);
                                    func_8083FE90(play, this, NA_SE_IT_HAMMER_HIT);
                                    if (this->transformation == PLAYER_FORM_GORON) {
                                        func_800B648C(play, 2, 2, 100.0f, &this->actor.world.pos);
                                        func_800C0094(poly, pos.x, pos.y, pos.z, &sp64);
                                        Matrix_MtxFToYXZRot(&sp64, &actorRot, true);
                                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, pos.x, pos.y, pos.z,
                                                    actorRot.x, actorRot.y, actorRot.z, 500);
                                    }

                                    if (bgId != BGCHECK_SCENE) {
                                        temp_v0 = DynaPoly_GetActor(&play->colCtx, bgId);

                                        if ((((this->meleeWeaponQuads[0].base.atFlags & 2) != 0) &&
                                             (&temp_v0->actor == this->meleeWeaponQuads[0].base.at)) ||
                                            ((this->meleeWeaponQuads[1].base.atFlags & 2) &&
                                             (&temp_v0->actor == this->meleeWeaponQuads[1].base.at))) {
                                            return false;
                                        }
                                    }

                                    func_808400CC(play, this);
                                    if (this->transformation != PLAYER_FORM_GORON) {
                                        return true;
                                    }
                                    return false;
                                }

                                if (this->linearVelocity >= 0.0f) {
                                    u32 temp_v0_2 = func_800C9BB8(&play->colCtx, poly, bgId);

                                    if (temp_v0_2 == 0xA) {
                                        CollisionCheck_SpawnShieldParticlesWood(play, &pos, &this->actor.projectedPos);
                                    } else {
                                        pos.x += 8.0f * COLPOLY_GET_NORMAL(poly->normal.x);
                                        pos.y += 8.0f * COLPOLY_GET_NORMAL(poly->normal.y);
                                        pos.x += 8.0f * COLPOLY_GET_NORMAL(poly->normal.z);
                                        CollisionCheck_SpawnShieldParticles(play, &pos);

                                        if (temp_v0_2 == 0xB) {
                                            func_800B8E58(this, NA_SE_IT_WALL_HIT_SOFT);
                                        } else {
                                            func_800B8E58(this, NA_SE_IT_WALL_HIT_HARD);
                                        }
                                    }

                                    func_80840094(play, this);
                                    Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
                                    this->linearVelocity = -14.0f;
                                }
                            }
                        }
                    }
                }
            } else {
                func_808400CC(play, this);
                func_8082DF2C(play);
                return true;
            }
        }

        temp_v0_3 = (this->meleeWeaponQuads[0].base.atFlags & 2) != 0;
        if (temp_v0_3 || (this->meleeWeaponQuads[1].base.atFlags & 2)) {
            if ((this->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H) &&
                (this->transformation != PLAYER_FORM_GORON)) {
                Actor* temp_v1 = this->meleeWeaponQuads[temp_v0_3 ? 0 : 1].base.at;

                if ((temp_v1 != NULL) && (temp_v1->id != ACTOR_EN_KANBAN)) {
                    func_8082DF2C(play);
                }
            }

            if (!func_8083FF30(play, this)) {
                func_8083FFEC(play, this);
                if (this->actor.colChkInfo.atHitEffect == 1) {
                    this->actor.colChkInfo.damage = 8;
                    func_80833B18(play, this, 4, 0.0f, 0.0f, this->actor.shape.rot.y, 20);
                    return true;
                }
            }
        }
    }

    return false;
}

Vec3f D_8085D2A4 = { 0.0f, 0.0f, 5.0f };

void func_80840770(PlayState* play, Player* this) {
    if (this->unk_AE8 != 0) {
        if (this->unk_AE8 > 0) {
            this->unk_AE8--;
            if (this->unk_AE8 == 0) {
                if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E000, 1.0f, 0.0f,
                                         Animation_GetLastFrame(&gameplay_keep_Linkanim_00E000), ANIMMODE_ONCE, -16.0f);
                } else {
                    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00D698, 1.0f, 99.0f,
                                         Animation_GetLastFrame(&gameplay_keep_Linkanim_00D698), ANIMMODE_ONCE, 0.0f);
                }
                gSaveContext.healthAccumulator = 0xA0;
                this->unk_AE8 = -1;
            }
        } else if (gSaveContext.healthAccumulator == 0) {
            func_80838760(this);

            this->stateFlags1 &= ~PLAYER_STATE1_80;
            if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                func_808353DC(play, this);
            } else {
                func_8085B384(this, play);
            }

            this->unk_D6B = 0x14;
            func_808339B4(this, -20);
            func_801A01C4();
        }
    } else if (this->unk_AE7 != 0) {
        func_80838760(this);
        this->unk_A86 = play->playerActorCsIds[7];
        this->unk_AE8 = 60;
        Player_SpawnFairy(play, this, &this->actor.world.pos, &D_8085D2A4, 5);
        func_800B8E58(this, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
    } else if (play->gameOverCtx.state == 2) {
        play->gameOverCtx.state = 3;
    }
}

void func_80840980(Player* this, u16 sfxId) {
    func_8082DF8C(this, sfxId);
}

void func_808409A8(PlayState* play, Player* this, f32 speedXZ, f32 yVelocity) {
    Actor* heldActor = this->heldActor;

    if (!func_808313A8(play, this, heldActor)) {
        heldActor->world.rot.y = this->actor.shape.rot.y;
        heldActor->speedXZ = speedXZ;
        heldActor->velocity.y = yVelocity;
        func_808309CC(play, this);
        func_800B8E58(this, NA_SE_PL_THROW);
        func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
    }
}

// Check if bonked and if so, rumble, play sound, etc.
s32 func_80840A30(PlayState* play, Player* this, f32* arg2, f32 arg3) {
    Actor* cylinderOc = NULL;

    if (arg3 <= *arg2) {
        // If interacting with a wall and close to facing it
        if (((this->actor.bgCheckFlags & 0x200) && (D_80862B24 < 0x1C00)) ||
            // or, impacting something's cylinder
            (((this->cylinder.base.ocFlags1 & OC1_HIT) && (cylinderOc = this->cylinder.base.oc) != NULL) &&
             // and that something is a Beaver Race ring,
             ((cylinderOc->id == ACTOR_EN_TWIG) ||
              // or something is a tree and `this` is close to facing it (note the this actor's facing direction would
              // be antiparallel to the cylinder's actor's yaw if this was directly facing it)
              (((cylinderOc->id == ACTOR_EN_WOOD02) || (cylinderOc->id == ACTOR_EN_SNOWWD) ||
                (cylinderOc->id == ACTOR_OBJ_TREE)) &&
               (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, cylinderOc->yawTowardsPlayer)) > 0x6000))))) {

            if (!func_8082DA90(play)) {
                if (this->doorType == PLAYER_DOORTYPE_STAIRCASE) {
                    func_8085B384(this, play);
                    return true;
                }

                if (cylinderOc != NULL) {
                    cylinderOc->home.rot.y = 1;
                } else if (this->actor.wallBgId != BGCHECK_SCENE) { // i.e. was an actor
                    DynaPolyActor* wallPolyActor = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

                    // Large crates, barrels and palm trees
                    if ((wallPolyActor != NULL) &&
                        ((wallPolyActor->actor.id == ACTOR_OBJ_KIBAKO2) ||
                         (wallPolyActor->actor.id == ACTOR_OBJ_TARU) || (wallPolyActor->actor.id == ACTOR_OBJ_YASI))) {
                        wallPolyActor->actor.home.rot.z = 1;
                    }
                }

                if (!(this->stateFlags3 & PLAYER_STATE3_1000)) {
                    if ((this->stateFlags3 & PLAYER_STATE3_8000) && (func_8084CA24 != this->actionFunc)) {
                        Player_SetAction(play, this, func_80851B58, 0);
                        func_8082DB90(play, this, &gameplay_keep_Linkanim_00DFF8);
                        func_8082DD2C(play, this);
                        this->linearVelocity *= 0.2f;
                    } else {
                        Player_SetAction(play, this, func_8084C6EC, 0);
                        Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_16][this->modelAnimType]);
                        this->unk_AE8 = 1;
                    }
                }

                this->linearVelocity = -this->linearVelocity;
                func_80836EA0(play, 33267, 3, 12);
                Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
                func_800B648C(play, 2, 2, 100.0f, &this->actor.world.pos);
                func_800B8E58(this, NA_SE_PL_BODY_HIT);
                func_8082DF8C(this, NA_SE_VO_LI_CLIMB_END);
                return true;
            }
        }
    }
    return false;
}

s32 func_80840CD4(Player* this, PlayState* play) {
    if (func_808387A0(play, this)) {
        this->stateFlags2 |= PLAYER_STATE2_20000;
    } else if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
        PlayerMeleeWeaponAnimation meleeWeaponAnimation;

        if ((this->unk_B08[0] >= 0.85f) || func_808333CC(this)) {
            meleeWeaponAnimation = D_8085CF84[Player_IsHoldingTwoHandedWeapon(this)];
        } else {
            meleeWeaponAnimation = D_8085CF80[Player_IsHoldingTwoHandedWeapon(this)];
        }
        func_80833864(play, this, meleeWeaponAnimation);
        func_808339B4(this, -8);
        this->stateFlags2 |= PLAYER_STATE2_20000;
        if (this->unk_AE3[this->unk_ADE] == 0) {
            this->stateFlags2 |= PLAYER_STATE2_40000000;
        }
    } else {
        return false;
    }

    return true;
}

void func_80840DEC(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084CE84, 1);
}

void func_80840E24(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084D18C, 1);
}

void func_80840E5C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    func_8082DC38(this);
    func_8082E438(play, this, D_8085CF68[Player_IsHoldingTwoHandedWeapon(this)]);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80840EC0(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_8084CCEC, 1);
    Player_AnimationPlayLoop(play, this, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)]);
    this->unk_AE8 = 1;
    this->unk_B38 = 0.0f;
}

void func_80840F34(Player* this) {
    Math_StepToF(&this->unk_B08[0], (gSaveContext.save.weekEventReg[23] & 2) ? 1.0f : 0.5f, 0.02f);
}

s32 func_80840F90(PlayState* play, Player* this, CsCmdActorAction* playerAction, f32 arg3, s16 arg4, s32 arg5) {
    f32 temp_ft4; // sp34
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft5; // sp28
    s32 temp_v1;  // sp24
    f32 temp_fa1;
    f32 temp_fv1;
    s32 temp_ft1;

    if ((arg5 != 0) && (this->linearVelocity == 0.0f)) {
        return LinkAnimation_Update(play, &this->skelAnime);
    }

    if (arg5 != 2) {
        temp_ft4 = R_UPDATE_RATE / 2.0f;
        temp_fa1 = playerAction->endPos.x - this->actor.world.pos.x;
        temp_fa0 = playerAction->endPos.z - this->actor.world.pos.z;
        temp_v1 = (playerAction->endFrame - play->csCtx.frames) + 1;
        temp_ft5 = sqrtf(SQ(temp_fa1) + SQ(temp_fa0)) / temp_ft4;
        arg4 = Math_FAtan2F(temp_fa0, temp_fa1);
        if (arg5 == 1) {
            temp_fv1 = playerAction->endPos.x - playerAction->startPos.x;
            temp_fa0_2 = playerAction->endPos.z - playerAction->startPos.z;
            temp_ft1 = (((sqrtf(SQ(temp_fv1) + SQ(temp_fa0_2)) / temp_ft4) /
                         (playerAction->endFrame - playerAction->startFrame)) /
                        1.5f) *
                       4.0f;
            if (temp_ft1 >= temp_v1) {
                arg3 = 0.0f;
                arg4 = this->actor.shape.rot.y;
            } else {
                arg3 = temp_ft5 / ((temp_v1 - temp_ft1) + 1);
            }
        //! FAKE
        dummy_label_581070:;
        } else {
            arg3 = temp_ft5 / temp_v1;
        }
    }

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_8083F57C(this, play);
    func_8083CB58(this, arg3, arg4);
    if ((arg3 == 0.0f) && (this->linearVelocity == 0.0f)) {
        func_80839CD8(this, play);
    }

    return false;
}

s32 func_808411D4(PlayState* play, Player* this, f32* arg2, s32 arg3) {
    f32 xDiff = this->unk_3A0.x - this->actor.world.pos.x;
    f32 yDiff = this->unk_3A0.z - this->actor.world.pos.z;
    s32 sp2C;
    s32 pad2;
    s16 var_v1;

    sp2C = sqrtf(SQ(xDiff) + SQ(yDiff));
    var_v1 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_3A0);
    if (sp2C < arg3) {
        *arg2 = 0.0f;
        var_v1 = this->actor.shape.rot.y;
    }
    if (func_80840F90(play, this, NULL, *arg2, var_v1, 2)) {
        return 0;
    }
    return sp2C;
}

void Player_InitMode_0(PlayState* play, Player* this) {
    this->actor.update = func_801229EC;
    this->actor.draw = NULL;
}

void Player_InitMode_2(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_80854118, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00DF78, 2.0f / 3.0f, 0.0f, 24.0f,
                         ANIMMODE_ONCE, 0.0f);
    this->actor.world.pos.y += 800.0f;
}

u8 D_8085D2B0[] = {
    ITEM_SWORD_RAZOR,
    ITEM_SWORD_KOKIRI,
    ITEM_OCARINA,
    ITEM_OCARINA,
};

void func_80841358(PlayState* play, Player* this, s32 arg2) {
    ItemID item;
    PlayerActionParam actionParam;

    //! @bug OoB read if player is human
    item = D_8085D2B0[this->transformation];
    actionParam = D_8085C99C[item];
    func_808317C4(this);
    func_8082DCA0(play, this);
    this->heldItemId = item;
    this->nextModelGroup = Player_ActionToModelGroup(this, actionParam);
    func_8082F8BC(play, this, actionParam);
    func_808309CC(play, this);
    if (arg2) {
        func_800B8E58(this, NA_SE_IT_SWORD_PICKOUT);
    }
}

Vec3f D_8085D2B4 = { -1.0f, 69.0f, 20.0f };

void Player_InitMode_1(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_80852FD4, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    Math_Vec3f_Copy(&this->actor.world.pos, &D_8085D2B4);
    this->currentYaw = this->actor.shape.rot.y = -0x8000;
    LinkAnimation_Change(play, &this->skelAnime, this->ageProperties->unk_A8, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE,
                         0.0f);
    func_8082E920(play, this, (1 | 2 | 4 | 8 | 0x80 | 0x200));
    if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
        func_80841358(play, this, false);
    }
    this->unk_AE8 = 20;
}

void Player_InitMode_3(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_8085437C, 0);
    func_8082E920(play, this, (1 | 2 | 8 | 0x10 | 0x80));
}

void func_80834DB8(Player* this, LinkAnimationHeader* anim, f32 arg2, PlayState* play);

void Player_InitMode_4(PlayState* play, Player* this) {
    func_80834DB8(this, &gameplay_keep_Linkanim_00DCD8, 12.0f, play);
    Player_SetAction(play, this, func_8085439C, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    this->fallStartHeight = this->actor.world.pos.y;
}

void Player_InitMode_7(PlayState* play, Player* this) {
    func_80833B18(play, this, 1, 2.0f, 2.0f, this->actor.shape.rot.y + 0x8000, 0);
}

void Player_InitMode_5(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_808540A0, 0);
    this->actor.draw = NULL;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
}

void Player_InitMode_6(PlayState* play, Player* this) {
    if (gSaveContext.save.isOwlSave) {
        Player_SetAction(play, this, func_808496AC, 0);
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        this->unk_AE8 = 0x28;
        gSaveContext.save.isOwlSave = false;
    } else {
        Player_SetAction(play, this, func_80849FE0, 0);
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        this->stateFlags2 |= PLAYER_STATE2_20000000;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST7, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, ENTEST7_MINUS1);
    }
}

// InitModes 0x8 and 0x9
void func_80841744(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_80855C28, 0);
    if (PLAYER_GET_INITMODE(&this->actor) == PLAYER_INITMODE_8) {
        Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
        this->heldItemActionParam = PLAYER_AP_OCARINA;
        Player_SetModels(this, Player_ActionToModelGroup(this, this->heldItemActionParam));
    } else {
        func_8082DB60(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
    }
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    this->unk_ABC = -10000.0f;
    this->unk_AE8 = 0x2710;
    this->unk_B10[5] = 8.0f;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

Vec3s D_8085D2C4 = { -57, 3377, 0 };

void Player_InitCommon(Player* this, PlayState* play, FlexSkeletonHeader* skelHeader) {
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->currentYaw = this->actor.world.rot.y;

    if ((PLAYER_GET_INITMODE(&this->actor) != PLAYER_INITMODE_TELESCOPE) &&
        ((gSaveContext.respawnFlag != 2) ||
         (gSaveContext.respawn[RESPAWN_MODE_RETURN].playerParams != PLAYER_PARAMS(0xFF, PLAYER_INITMODE_TELESCOPE)))) {
        func_808309CC(play, this);
        SkelAnime_InitLink(play, &this->skelAnime, skelHeader, D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType],
                           1 | 8, this->jointTableBuffer, this->morphTableBuffer, PLAYER_LIMB_MAX);
        this->skelAnime.baseTransl = D_8085D2C4;

        SkelAnime_InitLink(play, &this->unk_284, skelHeader, func_8082ED20(this), 1 | 8, this->unk_929, this->unk_9C8,
                           PLAYER_LIMB_MAX);
        this->unk_284.baseTransl = D_8085D2C4;

        if (this->transformation == PLAYER_FORM_GORON) {
            SkelAnime_InitFlex(play, &this->unk_2C8, &object_link_goron_Skel_0177B8, &object_link_goron_Anim_0178D0,
                               this->jointTable, this->morphTable, OBJECT_LINK_GORON_1_LIMB_MAX);
        }

        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, this->ageProperties->unk_04);
    }

    this->subCamId = CAM_ID_NONE;
    Collider_InitAndSetCylinder(play, &this->cylinder, &this->actor, &D_8085C2EC);
    Collider_InitAndSetCylinder(play, &this->shieldCylinder, &this->actor, &D_8085C318);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[0], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[1], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->shieldQuad, &this->actor, &D_8085C394);
}

void func_80841A50(PlayState* play, Player* this) {
    if ((play->roomCtx.currRoom.num >= 0) && (play->roomCtx.prevRoom.num < 0)) {
        Math_Vec3f_Copy(&this->unk_3C0, &this->actor.world.pos);
        this->unk_3CC = this->actor.shape.rot.y;
        this->unk_3CE = play->roomCtx.currRoom.num;
        this->unk_3CF = 1;
    }
}

typedef void (*PlayerInitModeFunc)(PlayState*, Player*);

// Initialisation functions for various gameplay modes depending on spawn params. There may be at most 0x10 due to it
// using a single nybble.
// sInitModeFuncs
PlayerInitModeFunc D_8085D2CC[0x10] = {
    /* 0x0 */ Player_InitMode_0,
    /* 0x1 */ Player_InitMode_1,
    /* 0x2 */ Player_InitMode_2,
    /* 0x3 */ Player_InitMode_3,
    /* 0x4 */ Player_InitMode_4,
    /* 0x5 */ Player_InitMode_5,
    /* 0x6 */ Player_InitMode_6,
    /* 0x7 */ Player_InitMode_7,
    /* 0x8 */ func_80841744,
    /* 0x9 */ func_80841744,
    /* 0xA */ func_8083ADF0,
    /* 0xB */ Player_InitMode_B,
    /* 0xC */ Player_InitMode_Telescope, // Telescope
    /* 0xD */ Player_InitMode_D,
    /* 0xE */ func_8083ADF0,
    /* 0xF */ Player_InitMode_F,
};

// sBlureInit
EffectBlureInit2 D_8085D30C = {
    0, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 4,
    0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
};

// sTireMarkInit ?
EffectTireMarkInit D_8085D330 = { 0, 63, { 0, 0, 15, 100 } };

// sTireMarkGoronColor ?
Color_RGBA8 D_8085D338 = { 0, 0, 15, 100 };
// sTireMarkOtherColor ?
Color_RGBA8 D_8085D33C = { 0, 0, 0, 150 };
Vec3f D_8085D340 = { 0.0f, 50.0f, 0.0f };

void Player_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    Player* this = THIS;
    s8 objBankIndex;
    s32 respawnFlag;
    s32 var_a1;
    s32 initMode;

    play->playerInit = Player_InitCommon;
    play->playerUpdate = Player_UpdateCommon;
    play->unk_18770 = func_8085B170;
    play->startPlayerFishing = Player_StartFishing;
    play->grabPlayer = Player_GrabPlayer;
    play->startPlayerCutscene = func_8085B28C;
    play->func_18780 = func_8085B384;
    play->damagePlayer = Player_InflictDamage;
    play->talkWithPlayer = func_8085B460;
    play->unk_1878C = func_8085B74C;
    play->unk_18790 = func_8085B820;
    play->unk_18794 = func_8085B854;
    play->setPlayerTalkAnim = func_8085B930;
    gActorOverlayTable->initInfo->objectId = 1;

    this->actor.room = -1;
    this->unk_A86 = -1;

    if (this->actor.shape.rot.x != 0) {
        this->transformation = this->actor.shape.rot.x - 1;

        objBankIndex = Object_GetIndex(&play->objectCtx, gPlayerFormObjectIndices[this->transformation]);
        this->actor.objBankIndex = objBankIndex;
        if (objBankIndex < 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        Actor_SetObjectDependency(play, &this->actor);
    } else {
        this->transformation = gSaveContext.save.playerForm;
        if (this->transformation == PLAYER_FORM_HUMAN) {
            if (gSaveContext.save.equippedMask == PLAYER_MASK_GIANT) {
                gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
            }
            this->currentMask = gSaveContext.save.equippedMask;
        } else {
            this->currentMask = this->transformation + PLAYER_MASK_FIERCE_DEITY;
            gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
        }

        Inventory_UpdateDeitySwordEquip(play);

        this->unk_B28 = 0;
        this->unk_B90 = 0;
        this->unk_B92 = 0;
        this->unk_B94 = 0;
        this->unk_B96 = 0;
        this->stateFlags1 &= ~(PLAYER_STATE1_8 | PLAYER_STATE1_1000 | PLAYER_STATE1_1000000 | PLAYER_STATE1_2000000);
        this->stateFlags2 &= ~(PLAYER_STATE2_20000 | PLAYER_STATE2_1000000 | PLAYER_STATE2_40000000);
        this->stateFlags3 &=
            ~(PLAYER_STATE3_8 | PLAYER_STATE3_40 | PLAYER_STATE3_80 | PLAYER_STATE3_100 | PLAYER_STATE3_200 |
              PLAYER_STATE3_800 | PLAYER_STATE3_1000 | PLAYER_STATE3_2000 | PLAYER_STATE3_8000 | PLAYER_STATE3_10000 |
              PLAYER_STATE3_40000 | PLAYER_STATE3_80000 | PLAYER_STATE3_100000 | PLAYER_STATE3_200000 |
              PLAYER_STATE3_800000 | PLAYER_STATE3_1000000 | PLAYER_STATE3_2000000);
        this->unk_B08[0] = 0.0f;
        this->unk_B08[1] = 0.0f;
    }

    if (this->transformation == PLAYER_FORM_ZORA) {
        if (this->stateFlags1 & PLAYER_STATE1_8000000) {
            this->unk_B10[0] = 1.0f;
        } else {
            this->unk_B10[0] = 0.0f;
        }
    }

    this->actor.flags &= ~(ACTOR_FLAG_20000 | ACTOR_FLAG_4000000);
    if (this->transformation != PLAYER_FORM_DEKU) {
        this->actor.flags |= ACTOR_FLAG_4000000;
        if (this->transformation == PLAYER_FORM_GORON) {
            this->actor.flags |= ACTOR_FLAG_20000;
        }
    }

    this->ageProperties = &D_8085BA38[this->transformation];

    this->heldItemActionParam = PLAYER_AP_NONE;
    this->itemActionParam = PLAYER_AP_NONE;
    this->heldItemId = ITEM_NONE;

    func_80831990(play, this, ITEM_NONE);
    Player_SetEquipmentData(play, this);
    this->prevBoots = this->currentBoots;
    Player_InitCommon(this, play, gPlayerSkeletons[this->transformation]);

    if (this->actor.shape.rot.z != 0) {
        EffectTireMark* tireMark;

        this->actor.shape.rot.z = 0;
        func_8082F938(play, this, 0, 4);

        tireMark = Effect_GetByIndex(this->meleeWeaponEffectIndex[2]);
        if (this->transformation == PLAYER_FORM_GORON) {
            tireMark->color = D_8085D338;
        } else {
            tireMark->color = D_8085D33C;
        }

        if ((this->csMode == PLAYER_CSMODE_9) || (this->csMode == PLAYER_CSMODE_93)) {
            Player_SetAction(play, this, func_8085B08C, 0);
            this->stateFlags1 |= PLAYER_STATE1_20000000;
        } else {
            Player_SetAction(play, this, func_80855818, 0);
            this->actor.shape.rot.y = this->currentYaw;

            if (this->prevMask != PLAYER_MASK_NONE) {
                func_8082DB90(play, this, &gameplay_keep_Linkanim_00D0A8);
            } else if (this->transformation == PLAYER_FORM_HUMAN) {
                LinkAnimation_Change(play, &this->skelAnime, D_8085D160[this->transformation], -2.0f / 3.0f, 9.0f, 0.0f,
                                     ANIMMODE_ONCE, 0.0f);
            } else {
                func_8082DB60(play, this, &gameplay_keep_Linkanim_00D0D0);
            }

            this->stateFlags1 |= (PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000);
            this->stateFlags3 |= PLAYER_STATE3_20000;
            this->unk_B10[5] = 3.0f;
        }
        return;
    }

    this->prevMask = this->currentMask;

    Effect_Add(play, &this->meleeWeaponEffectIndex[0], EFFECT_BLURE2, 0, 0, &D_8085D30C);
    Effect_Add(play, &this->meleeWeaponEffectIndex[1], EFFECT_BLURE2, 0, 0, &D_8085D30C);

    func_8082F938(play, this, 0, 4);
    if (this->transformation == PLAYER_FORM_GORON) {
        D_8085D330.color = D_8085D338;
    } else {
        D_8085D330.color = D_8085D33C;
    }
    Effect_Add(play, &this->meleeWeaponEffectIndex[2], EFFECT_TIRE_MARK, 0, 0, &D_8085D330);

    if (this->actor.shape.rot.x != 0) {
        this->actor.shape.rot.x = 0;
        this->csMode = PLAYER_CSMODE_68;
        Player_SetAction(play, this, func_8085B08C, 0);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        return;
    }

    play->unk_1887C = 0;
    play->unk_1887D = 0;
    play->unk_1887E = 0;
    this->giObjectSegment = ZeldaArena_Malloc(0x2000);
    this->maskObjectSegment = ZeldaArena_Malloc(0x3800);

    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 0xFF, 0x80, 0, -1);
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Play_AssignPlayerActorCsIdsFromScene(&play->state, this->actor.cutscene);

    respawnFlag = gSaveContext.respawnFlag;
    if (respawnFlag != 0) {
        if (respawnFlag == -3) {
            this->actor.params = gSaveContext.respawn[RESPAWN_MODE_UNK_3].playerParams;
        } else {
            if ((respawnFlag == 1) || (respawnFlag == -1)) {
                this->unk_D6A = -2;
            }

            if (respawnFlag != -7) {
                s32 respawnIndex;

                if ((respawnFlag == -8) || (respawnFlag == -5) || (respawnFlag == -4)) {
                    respawnFlag = 1;
                }

                if ((respawnFlag < 0) && (respawnFlag != -1) && (respawnFlag != -6)) {
                    respawnIndex = RESPAWN_MODE_DOWN;
                } else {
                    respawnIndex = (respawnFlag < 0) ? RESPAWN_MODE_TOP : respawnFlag - 1;

                    Math_Vec3f_Copy(&this->actor.world.pos, &gSaveContext.respawn[respawnIndex].pos);
                    Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
                    Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);

                    this->fallStartHeight = this->actor.world.pos.y;

                    this->currentYaw = this->actor.shape.rot.y = gSaveContext.respawn[respawnIndex].yaw;
                    this->actor.params = gSaveContext.respawn[respawnIndex].playerParams;
                }

                play->actorCtx.flags.switches[2] = gSaveContext.respawn[respawnIndex].tempSwitchFlags;
                play->actorCtx.flags.collectible[1] = gSaveContext.respawn[respawnIndex].unk_18;
                play->actorCtx.flags.collectible[2] = gSaveContext.respawn[respawnIndex].tempCollectFlags;
            }
        }
    }

    var_a1 = ((respawnFlag == 4) || (gSaveContext.respawnFlag == -4)) ? 1 : 0;
    if (func_801226E0(play, var_a1) == 0) {
        gSaveContext.respawn[RESPAWN_MODE_DOWN].playerParams = PLAYER_PARAMS(thisx->params, PLAYER_INITMODE_D);
    }

    gSaveContext.respawn[RESPAWN_MODE_DOWN].data = 1;
    if (respawnFlag == 0) {
        gSaveContext.respawn[RESPAWN_MODE_TOP] = gSaveContext.respawn[RESPAWN_MODE_DOWN];
    }
    gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams =
        PLAYER_PARAMS(gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams, PLAYER_INITMODE_D);

    initMode = PLAYER_GET_INITMODE(&this->actor);
    if (((initMode == PLAYER_INITMODE_5) || (initMode == PLAYER_INITMODE_6)) &&
        (gSaveContext.save.cutscene >= 0xFFF0)) {
        initMode = PLAYER_INITMODE_D;
    }

    D_8085D2CC[initMode](play, this);

    if ((this->actor.draw != NULL) && gSaveContext.save.hasTatl &&
        ((gSaveContext.gameMode == 0) || (gSaveContext.gameMode == 3)) && (play->sceneNum != SCENE_SPOT00)) {
        this->tatlActor = Player_SpawnFairy(play, this, &this->actor.world.pos, &D_8085D340, 0);

        if (gSaveContext.dogParams != 0) {
            gSaveContext.dogParams |= 0x8000;
        }

        if (gSaveContext.powderKegTimer != 0) {
            this->nextModelGroup = Player_ActionToModelGroup(this, PLAYER_AP_POWDER_KEG);
            this->heldItemId = ITEM_POWDER_KEG;
            func_8082F8BC(play, this, PLAYER_AP_POWDER_KEG);
            func_808313F0(this, play);
        } else if (gSaveContext.unk_1014 != 0) {
            func_8082F5FC(this, Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_MM,
                                                   this->actor.world.pos.x, this->actor.world.pos.y,
                                                   this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, 0x8000));
            func_808313F0(this, play);
        }
    }

    Minimap_SavePlayerRoomInitInfo(play);
    func_80841A50(play, this);
    this->unk_3CF = 0;
    MREG(64) = 0;
}

void func_80842510(s16* arg0) {
    s16 temp_ft0;

    temp_ft0 = (ABS_ALT(*arg0) * 100.0f) / 1000.0f;
    temp_ft0 = CLAMP(temp_ft0, 0x190, 0xFA0);

    Math_ScaledStepToS(arg0, 0, temp_ft0);
}

void func_808425B4(Player* this) {
    if (!(this->unk_AA6 & 2)) {
        s16 sp26 = this->actor.focus.rot.y - this->actor.shape.rot.y;

        func_80842510(&sp26);
        this->actor.focus.rot.y = this->actor.shape.rot.y + sp26;
    }
    if (!(this->unk_AA6 & 1)) {
        func_80842510(&this->actor.focus.rot.x);
    }
    if (!(this->unk_AA6 & 8)) {
        func_80842510(&this->unk_AAC.x);
    }
    if (!(this->unk_AA6 & 0x40)) {
        func_80842510(&this->unk_AB2.x);
    }
    if (!(this->unk_AA6 & 4)) {
        func_80842510(&this->actor.focus.rot.z);
    }
    if (!(this->unk_AA6 & 0x10)) {
        func_80842510(&this->unk_AAC.y);
    }
    if (!(this->unk_AA6 & 0x20)) {
        func_80842510(&this->unk_AAC.z);
    }
    if (!(this->unk_AA6 & 0x80)) {
        if (this->unk_AA8 != 0) {
            func_80842510(&this->unk_AA8);
        } else {
            func_80842510(&this->unk_AB2.y);
        }
    }
    if (!(this->unk_AA6 & 0x100)) {
        func_80842510(&this->unk_AB2.z);
    }

    this->unk_AA6 = 0;
}

/**
 * Sets the DoAction for the interface A/B buttons, depending on a significant number of things
 */
void Player_SetDoAction(PlayState* play, Player* this) {
    DoAction doActionB;
    s32 sp38;

    if (this != GET_PLAYER(play)) {
        return;
    }

    doActionB = -1;
    sp38 = func_801242B4(this) || (func_8084CA24 == this->actionFunc);

    // Set B do action
    if (this->transformation == PLAYER_FORM_GORON) {
        if (this->stateFlags3 & PLAYER_STATE3_80000) {
            doActionB = DO_ACTION_NONE;
        } else if (this->stateFlags3 & PLAYER_STATE3_1000) {
            doActionB = DO_ACTION_POUND;
        } else {
            doActionB = DO_ACTION_PUNCH;
        }
    } else if (this->transformation == PLAYER_FORM_ZORA) {
        if ((!(this->stateFlags1 & PLAYER_STATE1_8000000)) || (!sp38 && (this->actor.bgCheckFlags & 1))) {
            doActionB = DO_ACTION_PUNCH;
        } else {
            doActionB = DO_ACTION_DIVE;
        }
    } else if (this->transformation == PLAYER_FORM_DEKU) {
        doActionB = DO_ACTION_SHOOT;
    } else { // PLAYER_FORM_HUMAN
        if (this->currentMask == PLAYER_MASK_BLAST) {
            doActionB = DO_ACTION_EXPLODE;
        } else if (this->currentMask == PLAYER_MASK_BREMEN) {
            doActionB = DO_ACTION_MARCH;
        } else if (this->currentMask == PLAYER_MASK_KAMARO) {
            doActionB = DO_ACTION_DANCE;
        }
    }

    if (doActionB > -1) {
        func_801155B4(play, doActionB);
    } else if (play->interfaceCtx.unk_21C != 0) {
        play->interfaceCtx.unk_21C = 0;
        play->interfaceCtx.bButtonDoAction = 0;
    }

    // Set A do action
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) ||
        ((play->msgCtx.currentTextId >= 0x100) && (play->msgCtx.currentTextId <= 0x200)) ||
        ((play->msgCtx.currentTextId >= 0x1BB2) && (play->msgCtx.currentTextId < 0x1BB7))) {
        Actor* heldActor = this->heldActor;                   // sp34
        Actor* interactRangeActor = this->interactRangeActor; // sp30
        s32 pad;
        s32 sp28 = this->unk_AE3[this->unk_ADE];
        s32 sp24;
        DoAction doActionA =
            ((this->transformation == PLAYER_FORM_GORON) && !(this->stateFlags1 & PLAYER_STATE1_400000))
                ? DO_ACTION_CURL
                : DO_ACTION_NONE;

        if (play->actorCtx.unk5 & 4) {
            doActionA = DO_ACTION_SNAP;
        } else if (Player_InBlockingCsMode(play, this) || (this->actor.flags & ACTOR_FLAG_20000000) ||
                   (this->stateFlags1 & PLAYER_STATE1_1000) || (this->stateFlags3 & PLAYER_STATE3_80000) ||
                   (func_80854430 == this->actionFunc)) {
            doActionA = DO_ACTION_NONE;
        } else if (this->stateFlags1 & PLAYER_STATE1_100000) {
            doActionA = DO_ACTION_RETURN;
        } else if ((this->itemActionParam == PLAYER_AP_FISHING_POLE) && (this->unk_B28 != 0)) {
            doActionA = (this->unk_B28 == 2) ? DO_ACTION_REEL : DO_ACTION_NONE;
            doActionA = (this->unk_B28 == 2) ? DO_ACTION_REEL : DO_ACTION_NONE; // required to match, maybe FAKE?
        } else if (this->stateFlags3 & PLAYER_STATE3_2000) {
            doActionA = DO_ACTION_DOWN;
        } else if ((this->doorType != PLAYER_DOORTYPE_0) && (this->doorType != PLAYER_DOORTYPE_STAIRCASE) &&
                   !(this->stateFlags1 & PLAYER_STATE1_800)) {
            doActionA = DO_ACTION_OPEN;
        } else if (this->stateFlags3 & PLAYER_STATE3_200000) {
            static u8 D_8085D34C[] = {
                DO_ACTION_1, DO_ACTION_2, DO_ACTION_3, DO_ACTION_4, DO_ACTION_5, DO_ACTION_6, DO_ACTION_7, DO_ACTION_8,
            };

            doActionA = D_8085D34C[this->unk_B67];
        } else if ((!(this->stateFlags1 & PLAYER_STATE1_800) || (heldActor == NULL)) && (interactRangeActor != NULL) &&
                   (this->getItemId < GI_NONE)) {
            doActionA = DO_ACTION_OPEN;
        } else if (!sp38 && (this->stateFlags2 & PLAYER_STATE2_1)) {
            doActionA = DO_ACTION_GRAB;
        } else if ((this->stateFlags2 & PLAYER_STATE2_4) ||
                   (!(this->stateFlags1 & PLAYER_STATE1_800000) && (this->rideActor != NULL))) {
            doActionA = DO_ACTION_CLIMB;
        } else if ((this->stateFlags1 & PLAYER_STATE1_800000) &&
                   (!EN_HORSE_CHECK_4((EnHorse*)this->rideActor) && (func_808505D0 != this->actionFunc))) {
            if ((this->stateFlags2 & PLAYER_STATE2_2) && (this->talkActor != NULL)) {
                if ((this->talkActor->category == ACTORCAT_NPC) || (this->talkActor->id == ACTOR_DM_CHAR08)) {
                    doActionA = DO_ACTION_SPEAK;
                } else {
                    doActionA = DO_ACTION_CHECK;
                }
            } else if (!func_8082DA90(play) && !func_800B7128(this) && !(this->stateFlags1 & PLAYER_STATE1_100000)) {
                doActionA = DO_ACTION_FASTER;
            } else {
                doActionA = DO_ACTION_NONE;
            }
        } else if ((this->stateFlags2 & PLAYER_STATE2_2) && (this->talkActor != NULL)) {
            if ((this->talkActor->category == ACTORCAT_NPC) || (this->talkActor->category == ACTORCAT_ENEMY) ||
                (this->talkActor->id == ACTOR_DM_CHAR08)) {
                doActionA = DO_ACTION_SPEAK;
            } else {
                doActionA = DO_ACTION_CHECK;
            }
        } else if ((this->stateFlags1 & (PLAYER_STATE1_2000 | PLAYER_STATE1_200000)) ||
                   ((this->stateFlags1 & PLAYER_STATE1_800000) && (this->stateFlags2 & PLAYER_STATE2_400000))) {
            doActionA = DO_ACTION_DOWN;
        } else if ((this->stateFlags1 & PLAYER_STATE1_800) && (this->getItemId == GI_NONE) && (heldActor != NULL)) {
            if ((this->actor.bgCheckFlags & 1) || (heldActor->id == ACTOR_EN_NIW)) {
                if (!func_8083D738(this, heldActor)) {
                    doActionA = DO_ACTION_DROP;
                } else {
                    doActionA = DO_ACTION_THROW;
                }
            } else {
                doActionA = DO_ACTION_NONE;
            }
        } else if (this->stateFlags2 & PLAYER_STATE2_10000) {
            doActionA = DO_ACTION_GRAB;
        } else if (this->stateFlags2 & PLAYER_STATE2_800) {
            static u8 D_8085D354[] = { DO_ACTION_1, DO_ACTION_2 };
            s32 var_v0;

            var_v0 = ((120.0f - this->actor.depthInWater) / 40.0f);
            var_v0 = CLAMP(var_v0, 0, ARRAY_COUNT(D_8085D354) - 1);

            doActionA = D_8085D354[var_v0];
        } else if (this->stateFlags3 & PLAYER_STATE3_100) {
            doActionA = DO_ACTION_JUMP;
        } else if (this->stateFlags3 & PLAYER_STATE3_1000) {
            doActionA = DO_ACTION_RETURN;
        } else if (!func_8082FBE8(this) && (this->stateFlags1 & PLAYER_STATE1_8000000) && !sp38) {
            doActionA = DO_ACTION_SURFACE;
        } else if (((this->transformation != PLAYER_FORM_DEKU) &&
                    (sp38 || ((this->stateFlags1 & PLAYER_STATE1_8000000) && !(this->actor.bgCheckFlags & 1)))) ||
                   ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.bgCheckFlags & 1) &&
                    func_800C9DDC(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
            doActionA = (this->transformation == PLAYER_FORM_ZORA) ? DO_ACTION_SWIM
                        : ((this->stateFlags1 & PLAYER_STATE1_8000000) && (interactRangeActor != NULL) &&
                           (interactRangeActor->id == ACTOR_EN_ZOG))
                            ? DO_ACTION_GRAB
                            : DO_ACTION_DIVE;
        } else {
            sp24 = func_8082FBE8(this);
            if ((sp24 && (this->transformation != PLAYER_FORM_DEKU)) || !(this->stateFlags1 & PLAYER_STATE1_400000) ||
                !Player_IsGoronOrDeku(this)) {
                if ((this->transformation != PLAYER_FORM_GORON) &&
                    !(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_4000)) && (sp28 <= 0) &&
                    ((func_80123420(this)) ||
                     ((D_80862B08 != 7) &&
                      ((func_80123434(this)) || ((play->roomCtx.currRoom.unk3 != 2) &&
                                                 !(this->stateFlags1 & PLAYER_STATE1_400000) && (sp28 == 0)))))) {
                    doActionA = DO_ACTION_ATTACK;
                } else if ((play->roomCtx.currRoom.unk3 != 2) && sp24 && (sp28 > 0)) {
                    doActionA = DO_ACTION_JUMP;
                } else if ((this->transformation == PLAYER_FORM_DEKU) && !(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                           (this->actor.bgCheckFlags & 1)) {
                    doActionA = DO_ACTION_ATTACK;
                } else if (((this->transformation == PLAYER_FORM_HUMAN) ||
                            (this->transformation == PLAYER_FORM_ZORA)) &&
                           ((this->itemActionParam >= PLAYER_AP_SWORD_KOKIRI) ||
                            ((this->stateFlags2 & PLAYER_STATE2_100000) &&
                             (play->actorCtx.targetContext.arrowPointedActor == NULL)))) {
                    doActionA = DO_ACTION_PUT_AWAY;

                    if (!play->msgCtx.currentTextId) {} //! FAKE
                }
            }
        }

        if (doActionA != DO_ACTION_PUT_AWAY) {
            this->putAwayCountdown = 20;
        } else if (this->putAwayCountdown != 0) {
            doActionA = DO_ACTION_NONE;
            this->putAwayCountdown--;
        }

        func_8011552C(play, doActionA);

        // Set Tatl state
        if (!Play_InCsMode(play) && (this->stateFlags2 & PLAYER_STATE2_200000) &&
            !(this->stateFlags3 & PLAYER_STATE3_100)) {
            if (this->targetedActor != NULL) {
                func_80115764(play, 0x2B);
            } else {
                func_80115764(play, 0x2A);
            }
            ActorCutscene_SetIntentToPlay(0x7C);
        } else {
            func_80115764(play, 0x2C);
        }
    }
}

s32 func_808430E0(Player* this) {
    if ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.bgCheckFlags & 1) && func_8083784C(this)) {
        this->actor.bgCheckFlags &= ~1;
    }
    if (this->actor.bgCheckFlags & 1) {
        return false;
    }

    if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
        D_80862B08 = 0;
    }
    this->unk_B6C = 0;
    this->unk_B6E = 0;
    D_80862B28 = 0;
    return true;
}

void func_80843178(PlayState* play, Player* this) {
    u8 spC7;
    CollisionPoly* spC0;
    f32 temp_fv0; // spBC
    f32 temp_fv0_3;
    f32 temp_fv1; // spB4
    u32 var_v1;   // spB0
    s32 spAC;

    spC7 = 0;
    spAC = (func_8084D820 == this->actionFunc) && (this->unk_397 == 4);
    D_80862B1C = this->unk_D5E;

    temp_fv0 = this->ageProperties->unk_38;
    temp_fv1 = this->ageProperties->unk_00;

    if (this->stateFlags1 & (PLAYER_STATE1_20000000 | PLAYER_STATE1_80000000)) {
        if ((!(this->stateFlags1 & PLAYER_STATE1_80) && !(this->stateFlags2 & PLAYER_STATE1_4000) &&
             (this->stateFlags1 & PLAYER_STATE1_80000000)) ||
            spAC) {
            var_v1 = 0x38;
            this->actor.bgCheckFlags &= ~1;
        } else {
            if ((this->stateFlags1 & 1) && (play->roomCtx.currRoom.unk3 != 1) &&
                ((this->unk_D68 - (s32)this->actor.world.pos.y) >= 0x64)) {
                var_v1 = 0x39;
            } else if (!(this->stateFlags1 & PLAYER_STATE1_1) &&
                       ((func_8084E034 == this->actionFunc) || (func_8084D820 == this->actionFunc))) {
                var_v1 = 0x3C;
                this->actor.bgCheckFlags &= ~(8 | 0x200);
            } else {
                var_v1 = 0x3F;
            }
        }
    } else {
        if (func_808561B0 == this->actionFunc) {
            var_v1 = 0x814;
        } else if ((this->stateFlags3 & (PLAYER_STATE3_1000 | PLAYER_STATE3_80000)) && (this->linearVelocity >= 8.0f)) {
            var_v1 = 0x337;
        } else {
            var_v1 = 0x3F;
        }
    }

    if (this->stateFlags3 & PLAYER_STATE3_1) {
        var_v1 &= ~6;
    }
    if (var_v1 & 4) {
        this->stateFlags3 |= PLAYER_STATE3_10;
    }

    if (func_801242B4(this)) {
        var_v1 &= ~0x18;
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 26.800001f, temp_fv0, temp_fv1, var_v1);

    this->unk_AC0 -= (this->actor.world.pos.y - this->actor.prevPos.y) / this->actor.scale.y;
    this->unk_AC0 = CLAMP(this->unk_AC0, -1000.0f, 1000.0f);

    if (this->actor.bgCheckFlags & 0x10) {
        this->actor.velocity.y = 0.0f;
    }

    D_80862B18 = this->actor.world.pos.y - this->actor.floorHeight;
    D_80862B10 = 0;
    spC0 = this->actor.floorPoly;

    if ((spC0 != NULL) && (var_v1 & 4)) {
        this->unk_D5E = func_800C9B40(&play->colCtx, spC0, this->actor.floorBgId);
        if (this == GET_PLAYER(play)) {
            func_801A3CF4(SurfaceType_GetEcho(&play->colCtx, spC0, this->actor.floorBgId));
            if (this->actor.floorBgId == 0x32) {
                func_800FAAB4(play, SurfaceType_GetLightSettingIndex(&play->colCtx, spC0, this->actor.floorBgId));
            } else {
                DynaPolyActor_SetRidingRotatingStateByIndex(&play->colCtx, this->actor.floorBgId);
            }
        }

        D_80862B10 = SurfaceType_GetConveyorSpeed(&play->colCtx, spC0, this->actor.floorBgId);
        if (D_80862B10 != 0) {
            D_80862B14 = SurfaceType_GetConveyorType(&play->colCtx, spC0, (s32)this->actor.floorBgId);
            if (((D_80862B14 == 0) && (this->actor.depthInWater > 20.0f)) ||
                ((D_80862B14 != 0) && (this->actor.bgCheckFlags & 1))) {
                D_80862B16 = SurfaceType_GetConveyorDirection(&play->colCtx, spC0, this->actor.floorBgId) << 0xA;
            } else {
                D_80862B10 = 0;
            }
        }
    }

    this->actor.bgCheckFlags &= ~0x200;
    if (this->actor.bgCheckFlags & 8) {
        static Vec3f D_8085D358 = { 0.0f, 0.0f, 0.0f };
        CollisionPoly* spA8;
        s32 spA4;
        s16 temp_v1_3; // spA2
        f32 sp9C;

        D_8085D358.y = 17.800001f;
        D_8085D358.z = this->ageProperties->unk_38 + 10.0f;
        if (func_80835D58(play, this, &D_8085D358, &spA8, &spA4, &D_80862B30) != 0) {
            this->actor.bgCheckFlags |= 0x200;
            if (spA8 != this->actor.wallPoly) {
                this->actor.wallPoly = spA8;
                this->actor.wallBgId = spA4;
                this->actor.wallYaw = Math_FAtan2F(spA8->normal.z, spA8->normal.x);
            }
        }

        temp_v1_3 = this->actor.shape.rot.y - BINANG_ADD(this->actor.wallYaw, 0x8000);
        D_80862B0C = func_800C9A4C(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId);
        D_80862B20 = ABS_ALT(temp_v1_3);
        temp_v1_3 = BINANG_SUB(this->currentYaw, BINANG_ADD(this->actor.wallYaw, 0x8000));
        D_80862B24 = ABS_ALT(temp_v1_3);

        temp_fv0_3 = D_80862B24 * 0.00008f;
        if (!(this->actor.bgCheckFlags & 1) || (temp_fv0_3 >= 1.0f)) {
            this->unk_B50 = REG(45) / 100.0f;
        } else {
            temp_fv1 = (REG(45) / 100.0f) * temp_fv0_3;

            this->unk_B50 = temp_fv1;
            if (temp_fv1 < 0.1f) {
                this->unk_B50 = 0.1f;
            }
        }

        if ((this->actor.bgCheckFlags & 0x200) && (D_80862B20 < 0x3000)) {
            CollisionPoly* sp98 = this->actor.wallPoly;

            if (ABS_ALT(sp98->normal.y) < 0x258) {
                f32 sp94;
                f32 sp90;
                f32 sp8C;
                f32 temp_fv1_3;
                CollisionPoly* sp84;
                CollisionPoly* sp80;
                s32 sp7C;
                Vec3f sp70;
                f32 temp_fv0_5; // sp6C
                f32 sp68;
                s32 temp_v1_6;

                sp94 = COLPOLY_GET_NORMAL(sp98->normal.x);
                sp90 = COLPOLY_GET_NORMAL(sp98->normal.y);
                sp8C = COLPOLY_GET_NORMAL(sp98->normal.z);

                this->wallDistance = Math3D_UDistPlaneToPos(sp94, sp90, sp8C, sp98->dist, &this->actor.world.pos);
                temp_fv1_3 = this->wallDistance + 10.0f;
                sp70.x = this->actor.world.pos.x - (temp_fv1_3 * sp94);
                sp70.z = this->actor.world.pos.z - (temp_fv1_3 * sp8C);
                sp70.y = this->actor.world.pos.y + this->ageProperties->unk_0C;
                temp_fv0_5 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp84, &sp7C, &this->actor, &sp70);

                this->wallHeight = temp_fv0_5 - this->actor.world.pos.y;
                if ((this->wallHeight < 17.800001f) ||
                    ((BgCheck_EntityCheckCeiling(&play->colCtx, &sp68, &this->actor.world.pos,
                                                 (temp_fv0_5 - this->actor.world.pos.y) + 20.0f, &sp80, &sp7C,
                                                 &this->actor) != 0))) {
                    this->wallHeight = 399.96002f;
                } else {
                    D_8085D358.y = (temp_fv0_5 + 5.0f) - this->actor.world.pos.y;

                    if ((func_80835D58(play, this, &D_8085D358, &sp80, &sp7C, &D_80862B30)) &&
                        (temp_v1_6 = this->actor.wallYaw - Math_FAtan2F(sp80->normal.z, sp80->normal.x),
                         ABS_ALT(temp_v1_6) < 0x4000) &&
                        !(func_800C9AB0(&play->colCtx, sp80, sp7C))) {
                        this->wallHeight = 399.96002f;
                    } else if (func_800C9A7C(&play->colCtx, sp98, this->actor.wallBgId) == 0) {
                        if (this->ageProperties->unk_1C <= this->wallHeight) {
                            if (ABS_ALT(sp84->normal.y) > 0x5DC0) {
                                if ((this->ageProperties->unk_14 <= this->wallHeight) || func_801242B4(this)) {
                                    spC7 = 4;
                                } else if (this->ageProperties->unk_18 <= this->wallHeight) {
                                    spC7 = 3;
                                } else {
                                    spC7 = 2;
                                }
                            }
                        } else {
                            spC7 = 1;
                        }
                    }
                }
            }
        }
    } else {
        this->unk_B50 = REG(45) / 100.0f;
        this->wallHeight = 0.0f;
        this->unk_B5D = 0;
    }

    if (spC7 == this->unk_B5C) {
        if (this->linearVelocity != 0.0f) {
            if (this->unk_B5D < 0x64) {
                this->unk_B5D++;
            }
        }
    } else {
        this->unk_B5C = spC7;
        this->unk_B5D = 0;
    }

    D_80862B08 = func_800C99D4(&play->colCtx, spC0, this->actor.floorBgId);
    if (this->actor.bgCheckFlags & 1) {
        f32 sp60;
        f32 sp5C;
        f32 sp58;
        f32 sp54;
        s32 pad;
        f32 sp4C;

        D_80862B40 = SurfaceType_GetSlope(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        if (func_808430E0(this) == 0) {
            sp5C = COLPOLY_GET_NORMAL(spC0->normal.y);

            if (this->actor.floorBgId != 0x32) {
                DynaPolyActor_SetRidingMovingStateByIndex(&play->colCtx, this->actor.floorBgId);
            } else if (!(this->actor.bgCheckFlags & 2) && (this->actor.depthInWater <= 24.0f) && (D_80862B40 != 1) &&
                       (D_80862B10 == 0) && (sp5C > 0.5f)) {
                if (ActorCutscene_GetCurrentIndex() != play->playerActorCsIds[8]) {
                    func_80841A50(play, this);
                }
            }

            sp60 = COLPOLY_GET_NORMAL(spC0->normal.x);
            sp5C = 1.0f / sp5C;
            sp58 = COLPOLY_GET_NORMAL(spC0->normal.z);

            sp54 = Math_SinS(this->currentYaw);
            sp4C = Math_CosS(this->currentYaw);
            this->unk_B6C = Math_FAtan2F(1.0f, (-(sp60 * sp54) - (sp58 * sp4C)) * sp5C);
            this->unk_B6E = Math_FAtan2F(1.0f, (-(sp60 * sp4C) - (sp58 * sp54)) * sp5C);
            sp54 = Math_SinS(this->actor.shape.rot.y);
            sp4C = Math_CosS(this->actor.shape.rot.y);
            D_80862B28 = Math_FAtan2F(1.0f, (-(sp60 * sp54) - (sp58 * sp4C)) * sp5C);
            func_8083CF68(play, this);
        }
    } else {
        func_808430E0(this);
        D_80862B40 = 0;
    }

    if (spC0 != NULL) {
        this->unk_D66 = this->unk_B72;
        if (spAC != 0) {
            this->unk_B72 = 2;
            return;
        }

        if (this->actor.bgCheckFlags & 0x20) {
            if (this->actor.depthInWater < 50.0f) {
                if (this->actor.depthInWater < 20.0f) {
                    this->unk_B72 = (D_80862B08 == 0xD) ? 3 : 4;
                } else {
                    this->unk_B72 = (D_80862B08 == 0xD) ? 13 : 5;
                }

                return;
            }
        }

        if (this->stateFlags2 & PLAYER_STATE2_200) {
            this->unk_B72 = 1;
        } else if (COLPOLY_GET_NORMAL(spC0->normal.y) > 0.5f) {
            this->unk_B72 = SurfaceType_GetSfx(&play->colCtx, spC0, this->actor.floorBgId);
        }
    }
}

void Player_UpdateCamAndSeqModes(PlayState* play, Player* this) {
    u8 seqMode;
    s32 pad[2];
    Camera* camera;
    s32 camMode;

    if (this == GET_PLAYER(play)) {
        seqMode = SEQ_MODE_DEFAULT;
        if (this->stateFlags1 & PLAYER_STATE1_100000) {
            seqMode = SEQ_MODE_STILL;
        } else if (this->csMode != PLAYER_CSMODE_0) {
            Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), CAM_MODE_NORMAL);
        } else {
            camera = (this->actor.id == ACTOR_PLAYER) ? Play_GetCamera(play, CAM_ID_MAIN)
                                                      : Play_GetCamera(play, ((EnTest3*)this)->unk_D8E);
            if ((this->actor.parent != NULL) && (this->stateFlags3 & PLAYER_STATE3_80)) {
                camMode = CAM_MODE_HOOKSHOT;
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->actor.parent);
            } else if (func_8084BC64 == this->actionFunc) {
                camMode = CAM_MODE_STILL;
            } else if (this->stateFlags3 & PLAYER_STATE3_8000) {
                if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                    camMode = CAM_MODE_GORONDASH;
                } else {
                    camMode = CAM_MODE_FREEFALL;
                }
            } else if (this->stateFlags3 & PLAYER_STATE3_80000) {
                if (this->actor.bgCheckFlags & 1) {
                    camMode = CAM_MODE_GORONDASH;
                } else {
                    camMode = CAM_MODE_GORONJUMP;
                }
            } else if (this->stateFlags2 & PLAYER_STATE2_100) {
                camMode = CAM_MODE_PUSHPULL;
            } else if (this->targetedActor != NULL) {
                if ((this->actor.flags & ACTOR_FLAG_100) == ACTOR_FLAG_100) {
                    camMode = CAM_MODE_TALK;
                } else if (this->stateFlags1 & PLAYER_STATE1_10000) {
                    if (this->stateFlags1 & PLAYER_STATE1_2000000) {
                        camMode = CAM_MODE_FOLLOWBOOMERANG;
                    } else {
                        camMode = CAM_MODE_FOLLOWTARGET;
                    }
                } else {
                    camMode = CAM_MODE_BATTLE;
                }
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->targetedActor);
            } else if (this->stateFlags1 & PLAYER_STATE1_1000) {
                camMode = CAM_MODE_CHARGE;
            } else if (this->stateFlags3 & PLAYER_STATE3_100) {
                camMode = CAM_MODE_DEKUHIDE;
            } else if (this->stateFlags1 & PLAYER_STATE1_2000000) {
                camMode = CAM_MODE_FOLLOWBOOMERANG;
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->boomerangActor);
            } else if (this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000)) {
                if (func_80123434(this)) {
                    camMode = CAM_MODE_HANGZ;
                } else {
                    camMode = CAM_MODE_HANG;
                }
            } else if ((this->stateFlags3 & PLAYER_STATE3_2000) && (this->actor.velocity.y < 0.0f)) {
                if (this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) {
                    camMode = CAM_MODE_DEKUFLYZ;
                } else {
                    camMode = CAM_MODE_DEKUFLY;
                }
            } else if (this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) {
                if (func_800B7128(this) || func_8082EF20(this)) {
                    camMode = CAM_MODE_BOWARROWZ;
                } else if (this->stateFlags1 & PLAYER_STATE1_200000) {
                    camMode = CAM_MODE_CLIMBZ;
                } else {
                    camMode = CAM_MODE_TARGET;
                }
            } else if ((this->stateFlags1 & PLAYER_STATE1_400000) && (this->transformation != 0)) {
                camMode = CAM_MODE_STILL;
            } else if (this->stateFlags1 & PLAYER_STATE1_40000) {
                camMode = CAM_MODE_JUMP;
            } else if (this->stateFlags1 & PLAYER_STATE1_200000) {
                camMode = CAM_MODE_CLIMB;
            } else if (this->stateFlags1 & PLAYER_STATE1_80000) {
                camMode = CAM_MODE_FREEFALL;
            } else if (((func_808548B8 == this->actionFunc) &&
                        (this->meleeWeaponAnimation >= PLAYER_MWA_FORWARD_SLASH_1H) &&
                        (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_PUNCH_KICK)) ||
                       (this->stateFlags3 & PLAYER_STATE3_8) ||
                       ((func_8084FE7C == this->actionFunc) && (this->unk_AE8 == 0)) ||
                       (func_808505D0 == this->actionFunc)) {
                camMode = CAM_MODE_STILL;
            } else {
                camMode = CAM_MODE_NORMAL;
                if ((this->linearVelocity == 0.0f) &&
                    (!(this->stateFlags1 & PLAYER_STATE1_800000) || (this->rideActor->speedXZ == 0.0f))) {
                    seqMode = SEQ_MODE_STILL;
                }
            }

            Camera_ChangeMode(camera, camMode);
        }

        if (play->actorCtx.targetContext.bgmEnemy != NULL) {
            seqMode = SEQ_MODE_ENEMY;
            Audio_SetBgmEnemyVolume(sqrtf(play->actorCtx.targetContext.bgmEnemy->xyzDistToPlayerSq));
        }

        Audio_SetSequenceMode(seqMode);
    }
}

Vec3f D_8085D364 = { 0.0f, 0.5f, 0.0f };
Vec3f D_8085D370 = { 0.0f, 0.5f, 0.0f };
Color_RGBA8 D_8085D37C = { 255, 255, 100, 255 };
Color_RGBA8 D_8085D380 = { 255, 50, 0, 0 };

void func_808442D8(PlayState* play, Player* this) {
    f32 var_fa0;
    f32 temp_fv1;

    if (this->unk_B08[1] == 0.0f) {
        func_80831990(play, this, ITEM_NONE);
        return;
    }

    var_fa0 = 1.0f;
    if (DECR(this->unk_B28) == 0) {
        Inventory_ChangeAmmo(ITEM_STICK, -1);
        this->unk_B28 = 1;
        this->unk_B08[1] = 0.0f;
        var_fa0 = 0.0f;
    } else if (this->unk_B28 >= 0xC9) {
        var_fa0 = (0xD2 - this->unk_B28) / 10.0f;
    } else if (this->unk_B28 < 0x14) {
        var_fa0 = this->unk_B28 / 20.0f;
        this->unk_B08[1] = var_fa0;
    }

    if (var_fa0 > 0.0f) {
        func_800B0EB0(play, &this->meleeWeaponInfo[0].tip, &D_8085D364, &D_8085D370, &D_8085D37C, &D_8085D380,
                      (var_fa0 * 200.0f), 0, 8);
        if (((play->roomCtx.currRoom.enablePosLights != 0)) || (MREG(93) != 0)) {
            temp_fv1 = (Rand_ZeroOne() * 30.0f) + 225.0f;
            Lights_PointSetColorAndRadius(&this->lightInfo, temp_fv1, temp_fv1 * 0.7f, 0, var_fa0 * 300.0f);
        }
    }
}

void func_808445C4(PlayState* play, Player* this) {
    this->shockTimer--;
    this->unk_B66 += this->shockTimer;
    if (this->unk_B66 > 20) {
        Vec3f pos;
        Vec3f* bodyPartsPos;
        s32 scale;
        s32 randIndex;

        this->unk_B66 -= 20;
        scale = this->shockTimer * 2;
        if (scale > 40) {
            scale = 40;
        }

        randIndex = Rand_ZeroFloat(PLAYER_BODYPART_MAX - 0.1f);
        bodyPartsPos = randIndex + this->bodyPartsPos;

        pos.x = (randPlusMinusPoint5Scaled(5.0f) + bodyPartsPos->x) - this->actor.world.pos.x;
        pos.y = (randPlusMinusPoint5Scaled(5.0f) + bodyPartsPos->y) - this->actor.world.pos.y;
        pos.z = (randPlusMinusPoint5Scaled(5.0f) + bodyPartsPos->z) - this->actor.world.pos.z;
        EffectSsFhgFlash_SpawnShock(play, &this->actor, &pos, scale, 1);
        func_800B8F98(&this->actor, NA_SE_PL_SPARK - SFX_FLAG);
    }
}

// controller rumble?
void func_808446F4(PlayState* play, Player* this) {
    f32 step = 200000.0f - (this->unk_AA0 * 5.0f);

    if (step < 0.0f) {
        step = 0.0f;
    }

    this->unk_A9C += step;
    if (this->unk_A9C > 4000000.0f) {
        this->unk_A9C = 0.0f;
        Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
    }
}

s8 D_8085D384[92] = {
    /*  0 */ PLAYER_CSMODE_0,
    /*  1 */ PLAYER_CSMODE_2,
    /*  2 */ PLAYER_CSMODE_2,
    /*  3 */ PLAYER_CSMODE_4,
    /*  4 */ PLAYER_CSMODE_3,
    /*  5 */ PLAYER_CSMODE_56,
    /*  6 */ PLAYER_CSMODE_8,
    /*  7 */ PLAYER_CSMODE_0,
    /*  8 */ PLAYER_CSMODE_0,
    /*  9 */ PLAYER_CSMODE_135,
    /* 10 */ PLAYER_CSMODE_21,
    /* 11 */ PLAYER_CSMODE_61,
    /* 12 */ PLAYER_CSMODE_62,
    /* 13 */ PLAYER_CSMODE_60,
    /* 14 */ PLAYER_CSMODE_63,
    /* 15 */ PLAYER_CSMODE_64,
    /* 16 */ PLAYER_CSMODE_65,
    /* 17 */ PLAYER_CSMODE_66,
    /* 18 */ PLAYER_CSMODE_70,
    /* 19 */ PLAYER_CSMODE_19,
    /* 20 */ PLAYER_CSMODE_71,
    /* 21 */ PLAYER_CSMODE_72,
    /* 22 */ PLAYER_CSMODE_67,
    /* 23 */ PLAYER_CSMODE_73,
    /* 24 */ PLAYER_CSMODE_74,
    /* 25 */ PLAYER_CSMODE_75,
    /* 26 */ PLAYER_CSMODE_68,
    /* 27 */ PLAYER_CSMODE_69,
    /* 28 */ PLAYER_CSMODE_76,
    /* 29 */ PLAYER_CSMODE_116,
    /* 30 */ PLAYER_CSMODE_0,
    /* 31 */ PLAYER_CSMODE_40,
    /* 32 */ PLAYER_CSMODE_0,
    /* 33 */ -PLAYER_CSMODE_52, // the only negative one
    /* 34 */ PLAYER_CSMODE_42,
    /* 35 */ PLAYER_CSMODE_43,
    /* 36 */ PLAYER_CSMODE_57,
    /* 37 */ PLAYER_CSMODE_81,
    /* 38 */ PLAYER_CSMODE_41,
    /* 39 */ PLAYER_CSMODE_53,
    /* 40 */ PLAYER_CSMODE_54,
    /* 41 */ PLAYER_CSMODE_44,
    /* 42 */ PLAYER_CSMODE_55,
    /* 43 */ PLAYER_CSMODE_45,
    /* 44 */ PLAYER_CSMODE_46,
    /* 45 */ PLAYER_CSMODE_47,
    /* 46 */ PLAYER_CSMODE_48,
    /* 47 */ PLAYER_CSMODE_49,
    /* 48 */ PLAYER_CSMODE_50,
    /* 49 */ PLAYER_CSMODE_51,
    /* 50 */ PLAYER_CSMODE_77,
    /* 51 */ PLAYER_CSMODE_78,
    /* 52 */ PLAYER_CSMODE_79,
    /* 53 */ PLAYER_CSMODE_80,
    /* 54 */ PLAYER_CSMODE_81,
    /* 55 */ PLAYER_CSMODE_82,
    /* 56 */ PLAYER_CSMODE_83,
    /* 57 */ PLAYER_CSMODE_84,
    /* 58 */ PLAYER_CSMODE_85,
    /* 59 */ PLAYER_CSMODE_86,
    /* 60 */ PLAYER_CSMODE_87,
    /* 61 */ PLAYER_CSMODE_88,
    /* 62 */ PLAYER_CSMODE_89,
    /* 63 */ PLAYER_CSMODE_90,
    /* 64 */ PLAYER_CSMODE_91,
    /* 65 */ PLAYER_CSMODE_92,
    /* 66 */ PLAYER_CSMODE_94,
    /* 67 */ PLAYER_CSMODE_95,
    /* 68 */ PLAYER_CSMODE_100,
    /* 69 */ PLAYER_CSMODE_101,
    /* 70 */ PLAYER_CSMODE_98,
    /* 71 */ PLAYER_CSMODE_99,
    /* 72 */ PLAYER_CSMODE_102,
    /* 73 */ PLAYER_CSMODE_103,
    /* 74 */ PLAYER_CSMODE_104,
    /* 75 */ PLAYER_CSMODE_112,
    /* 76 */ PLAYER_CSMODE_113,
    /* 77 */ PLAYER_CSMODE_117,
    /* 78 */ PLAYER_CSMODE_104,
    /* 79 */ PLAYER_CSMODE_104,
    /* 80 */ PLAYER_CSMODE_105,
    /* 81 */ PLAYER_CSMODE_106,
    /* 82 */ PLAYER_CSMODE_107,
    /* 83 */ PLAYER_CSMODE_108,
    /* 84 */ PLAYER_CSMODE_109,
    /* 85 */ PLAYER_CSMODE_110,
    /* 86 */ PLAYER_CSMODE_118,
    /* 87 */ PLAYER_CSMODE_119,
    /* 88 */ PLAYER_CSMODE_120,
    /* 89 */ PLAYER_CSMODE_114,
    /* 90 */ PLAYER_CSMODE_111,
    /* 91 */ PLAYER_CSMODE_122,
};

f32 D_8085D3E0[PLAYER_FORM_MAX] = {
    0.8f, 0.6f, 0.8f, 1.5f, 1.0f,
};

void func_80844784(PlayState* play, Player* this) {
    f32 var_fv0;
    s16 var_a3;
    f32 temp_ft4;
    s32 temp_ft2;
    f32 temp_fv1_2;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fa0;
    f32 temp_fa1;
    s16 temp_v0;
    f32 temp_fv0_2;

    if ((this->actor.bgCheckFlags & 1) && (D_80862B08 == 5) && (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER)) {
        var_a3 = this->currentYaw;
        var_fv0 = this->linearVelocity;
        temp_v0 = this->actor.world.rot.y - var_a3;

        if ((ABS_ALT(temp_v0) > 0x6000) && (this->actor.speedXZ != 0.0f)) {
            var_fv0 = 0.0f;
            var_a3 += 0x8000;
        }

        if ((Math_StepToF(&this->actor.speedXZ, var_fv0, 0.35f) != 0) && (var_fv0 == 0.0f)) {
            this->actor.world.rot.y = this->currentYaw;
        }

        if (this->linearVelocity != 0.0f) {
            temp_ft2 = (fabsf(this->linearVelocity) * 700.0f) - (fabsf(this->actor.speedXZ) * 100.0f);
            temp_ft2 = CLAMP(temp_ft2, 0, 0x546);

            Math_ScaledStepToS(&this->actor.world.rot.y, var_a3, temp_ft2);
        }
        if ((this->linearVelocity == 0.0f) && (this->actor.speedXZ != 0.0f)) {
            func_8019F780(&this->actor.projectedPos, func_8082E078(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG),
                          this->actor.speedXZ);
        }
    } else {
        this->actor.speedXZ = this->linearVelocity;
        this->actor.world.rot.y = this->currentYaw;
    }

    Actor_UpdateVelocityWithGravity(&this->actor);
    D_80862B3C = 0.0f;
    if ((gSaveContext.save.playerData.health != 0) &&
        ((this->unk_B80 != 0.0f) || (this->windSpeed != 0.0f) || (play->envCtx.windSpeed >= 50.0f)) &&
        (!Player_InCsMode(play)) && !(this->stateFlags1 & 0x206004) && !(this->stateFlags3 & 0x100) &&
        (func_8084D4EC != this->actionFunc) && (this->actor.id == ACTOR_PLAYER)) {
        this->actor.velocity.x += this->unk_B80 * Math_SinS(this->unk_B84);
        this->actor.velocity.z += this->unk_B80 * Math_CosS(this->unk_B84);
        temp_fv1_2 = 10.0f - this->actor.velocity.y;
        if (temp_fv1_2 > 0.0f) {
            sp58 = D_8085D3E0[this->transformation];
            sp54 = this->windSpeed * sp58;
            sp50 = Math_SinS(this->windAngleX) * sp54;
            sp4C = Math_CosS(this->windAngleX) * sp54;
            sp48 = Math_SinS(this->windAngleY) * sp4C;
            sp44 = Math_CosS(this->windAngleY) * sp4C;

            if ((sp50 > 0.0f) && (this->transformation == 3) && !(this->actor.bgCheckFlags & 1)) {
                if (Player_SetAction(play, this, func_80856918, 1)) {
                    this->stateFlags3 |= PLAYER_STATE3_2000 | PLAYER_STATE3_1000000;
                    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_OPEN);
                    func_8019FD90(4, 2);
                }

                this->unk_AE8 = 0x270F;
                Math_Vec3f_Copy(this->unk_AF0, &this->actor.world.pos);
            }

            if (play->envCtx.windSpeed >= 50.0f) {
                temp_fa0 = play->envCtx.windDir.x;
                temp_fa1 = play->envCtx.windDir.y;
                temp_ft4 = play->envCtx.windDir.z;

                temp_fv0_2 = sqrtf(SQ(temp_fa0) + SQ(temp_fa1) + SQ(temp_ft4));
                if (temp_fv0_2 != 0.0f) {
                    temp_fv0_2 = ((play->envCtx.windSpeed - 50.0f) * 0.1f * sp58) / temp_fv0_2;

                    sp48 -= temp_fa0 * temp_fv0_2;
                    sp50 -= temp_fa1 * temp_fv0_2;
                    sp44 -= temp_ft4 * temp_fv0_2;
                }
            }

            if (temp_fv1_2 < sp50) {
                temp_fv1_2 /= sp50;

                sp48 *= temp_fv1_2;
                sp50 *= temp_fv1_2;
                sp44 *= temp_fv1_2;
            }

            if (this->actor.bgCheckFlags & 1) {
                D_80862B3C = (sp44 * Math_CosS(this->currentYaw)) + (Math_SinS(this->currentYaw) * sp48);
                if (fabsf(D_80862B3C) > 4.0f) {
                    func_8083FBC4(play, this);
                }

                func_8019F780(&this->actor.projectedPos, func_8082E078(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG),
                              fabsf(D_80862B3C));
            }

            this->actor.velocity.x += sp48;
            this->actor.velocity.z += sp44;
            this->actor.velocity.y += sp50;
        }
    }

    Actor_UpdatePos(&this->actor);
}

Color_RGBA8 D_8085D3F4 = { 100, 255, 255, 0 };
Color_RGBA8 D_8085D3F8 = { 0, 100, 100, 0 };

void func_80844D80(PlayState* play, Player* this) {
    Vec3f pos;
    Vec3f spA0;
    Vec3f velocity;
    Vec3f accel;
    Vec3f sp7C;
    s32 i;

    Math_Vec3f_Diff(&this->meleeWeaponInfo[0].tip, &this->meleeWeaponInfo[0].base, &sp7C);
    Math_Vec3f_SumScaled(&this->meleeWeaponInfo[0].base, &sp7C, 0.3f, &spA0);

    for (i = 0; i < 2; i++) {
        Math_Vec3f_SumScaled(&this->meleeWeaponInfo[0].base, &sp7C, Rand_ZeroOne(), &pos);
        Math_Vec3f_AddRand(&pos, 15.0f, &pos);
        Math_Vec3f_DistXYZAndStoreNormDiff(&spA0, &pos, 1.7f, &velocity);
        Math_Vec3f_ScaleAndStore(&velocity, 0.01f, &accel);
        EffectSsKirakira_SpawnDispersed(play, &pos, &velocity, &accel, &D_8085D3F4, &D_8085D3F8,
                                        Rand_S16Offset(-20, -120), 15);
    }
}

f32 D_8085D3FC[] = { 0.005f, 0.05f };
f32 D_8085D404[] = { 2.0f, 4.0f, 11.0f };
f32 D_8085D410[] = { 0.5f, 1.0f, 3.0f };

void Player_UpdateCommon(Player* player, PlayState* play, Input* input) {
    f32 temp_fv0;
    f32 temp_fv1;

    D_80862B44 = input;
    if (player->unk_D6A < 0) {
        player->unk_D6A++;
        if (player->unk_D6A == 0) {
            player->unk_D6A = 1;
            play_sound(NA_SE_OC_REVENGE);
        }
    }

    Math_Vec3f_Copy(&player->actor.prevPos, &player->actor.home.pos);

    temp_fv1 = fabsf(player->linearVelocity) * (fabsf(Math_SinS(player->unk_B6C) * 800.0f) + 100.0f);

    Math_StepToF(&player->unk_AC0, 0.0f, CLAMP_MIN(temp_fv1, 300.0f));

    if (player->unk_D57 != 0) {
        player->unk_D57--;
    }

    if (player->unk_B5E != 0) {
        player->unk_B5E--;
    }

    if (player->unk_D6B != 0) {
        player->unk_D6B--;
    }

    if (player->invincibilityTimer < 0) {
        player->invincibilityTimer++;
    } else if (player->invincibilityTimer > 0) {
        player->invincibilityTimer--;
    }

    if (player->unk_B64 != 0) {
        player->unk_B64--;
    }

    if (player->unk_B60 != 0) {
        player->unk_B60--;
    }

    if (gSaveContext.jinxTimer != 0) {
        gSaveContext.jinxTimer--;
    }

    func_80122C20(play, &player->unk_3D0);
    if ((player->transformation == 0) && (func_8082FBE8(player) != 0)) {
        func_80844D80(play, player);
    }
    if (player->transformation == 2) {
        s32 var_v0 = (player->stateFlags1 & PLAYER_STATE1_8000000) ? 1 : 0;

        Math_StepToF(&player->unk_B10[0], var_v0, D_8085D3FC[var_v0]);
    }
    func_80832888(player, play);
    if (play->roomCtx.currRoom.enablePosLights != 0) {
        Lights_PointSetColorAndRadius(&player->lightInfo, 255, 255, 255, 60);
    } else {
        player->lightInfo.params.point.radius = -1;
    }

    if ((player->itemActionParam == PLAYER_AP_STICK) && (player->unk_B28 != 0)) {
        func_808442D8(play, player);
    } else if (player->itemActionParam == PLAYER_AP_FISHING_POLE) {
        if (player->unk_B28 < 0) {
            player->unk_B28++;
        }
    }

    if (player->shockTimer != 0) {
        func_808445C4(play, player);
    }
    if (player->isBurning) {
        func_808341F4(play, player);
    }

    if (player->stateFlags2 & PLAYER_STATE2_8000) {
        if (!(player->actor.bgCheckFlags & 1)) {
            func_8082DABC(player);
            Actor_MoveWithGravity(&player->actor);
        }
        func_80843178(play, player);
    } else {
        f32 temp_fa0;
        f32 var_fv1_2;
        s32 var_v1; // sp58
        s32 pad;

        if (player->currentBoots != player->prevBoots) {
            if (player->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) {
                if (player->stateFlags1 & PLAYER_STATE1_8000000) {
                    func_8082DC64(play, player);
                    if (player->ageProperties->unk_2C < player->actor.depthInWater) {
                        player->stateFlags2 |= PLAYER_STATE2_400;
                    }
                }
            } else if ((player->stateFlags1 & PLAYER_STATE1_8000000) &&
                       ((player->prevBoots == PLAYER_BOOTS_ZORA_UNDERWATER) || (player->actor.bgCheckFlags & 1))) {
                func_8083B930(play, player);
                player->stateFlags2 &= ~PLAYER_STATE2_400;
                if (func_808508C8 == player->actionFunc) {
                    player->unk_AE8 = 20;
                }
            }
            player->prevBoots = player->currentBoots;
        }
        if ((player->actor.parent == NULL) && (player->stateFlags1 & PLAYER_STATE1_800000)) {
            player->actor.parent = player->rideActor;
            func_80837BD0(play, player);
            player->unk_AE8 = -1;
            Player_AnimationPlayOnce(play, player, &gameplay_keep_Linkanim_00E088);
            func_8082E920(play, player, 1 | 2 | 8 | 0x10 | 0x80);
        }

        if (player->unk_ADC == 0) {
            player->unk_ADD = 0;
        } else if (player->unk_ADC < 0) {
            player->unk_ADC++;
        } else {
            player->unk_ADC--;
        }

        if (!(player->stateFlags3 & PLAYER_STATE3_2000)) {
            Math_ScaledStepToS(&player->unk_AAA, 0, 0x190);
        }

        if ((player->transformation >= PLAYER_FORM_GORON) && (player->transformation <= PLAYER_FORM_DEKU)) {
            func_800BBB74(&player->blinkInfo, 20, 80, 3);
        } else {
            func_800BBAC0(&player->blinkInfo, 20, 80, 6);
        }

        player->actor.shape.face = ((play->gameplayFrames & 0x20) ? 0 : 3) + player->blinkInfo.eyeTexIndex;
        if (player->currentMask == PLAYER_FORM_HUMAN) {
            func_80124420(player);
        }

        if (func_800B7118(player)) {
            func_808484F0(player);
        }

        if ((play->unk_18844 == 0) && !(player->skelAnime.moveFlags & 0x80)) {
            if (!(player->stateFlags1 & PLAYER_STATE1_2) && (player->actor.parent == NULL)) {
                func_80844784(play, player);
            }
            func_80843178(play, player);
        } else {
            D_80862B08 = 0;
            player->unk_D5E = 0;
            if (player->stateFlags1 & PLAYER_STATE1_800000) {
                player->actor.floorPoly = player->rideActor->floorPoly;
                player->actor.floorBgId = player->rideActor->floorBgId;
            }
            D_80862B10 = 0;
            player->unk_B80 = 0.0f;
        }

        func_8083562C(play, player, player->actor.floorPoly, player->actor.floorBgId);
        if (D_80862B10 != 0) {
            f32 var_fv1;
            s32 pad2;

            D_80862B10--;
            if (D_80862B14 == 0) {
                var_fv1 = D_8085D404[D_80862B10];
                if (!(player->stateFlags1 & PLAYER_STATE1_8000000)) {
                    var_fv1 /= 4.0f;
                }
            } else {
                var_fv1 = D_8085D410[D_80862B10];
            }

            Math_StepToF(&player->unk_B80, var_fv1, var_fv1 * 0.1f);
            Math_ScaledStepToS(&player->unk_B84, D_80862B16,
                               ((player->stateFlags1 & PLAYER_STATE1_8000000) ? 400.0f : 800.0f) * var_fv1);
        } else if (player->unk_B80 != 0.0f) {
            Math_StepToF(&player->unk_B80, 0.0f, (player->stateFlags1 & PLAYER_STATE1_8000000) ? 0.5f : 2.0f);
        }
        if (!(player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) &&
            !(player->stateFlags3 & PLAYER_STATE3_80) && (func_80854430 != player->actionFunc)) {
            func_8083BB4C(play, player);
            if (!Play_InCsMode(play)) {
                if ((player->actor.id == ACTOR_PLAYER) && !(player->stateFlags1 & PLAYER_STATE1_80000000) &&
                    (gSaveContext.save.playerData.health == 0) && func_808323C0(player, play->playerActorCsIds[6])) {
                    if (player->stateFlags3 & PLAYER_STATE3_1000000) {
                        func_808355D8(play, player, &gameplay_keep_Linkanim_00E2D8);
                    } else if (player->stateFlags1 &
                               (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000)) {
                        func_8082DD2C(play, player);
                        func_80833AA0(player, play);
                    } else if ((player->actor.bgCheckFlags & 1) || (player->stateFlags1 & PLAYER_STATE1_8000000)) {
                        func_80831F34(play, player,
                                      func_801242B4(player)
                                          ? &gameplay_keep_Linkanim_00DFE8
                                          : ((player->shockTimer != 0) ? &gameplay_keep_Linkanim_00DC28
                                                                       : &gameplay_keep_Linkanim_00D698));
                    }
                } else {
                    if ((player->actor.parent == NULL) &&
                        (func_8082DA90(play) || (player->unk_D6B != 0) || !func_80834600(player, play))) {
                        func_8083827C(player, play);
                    } else {
                        player->fallStartHeight = player->actor.world.pos.y;
                    }

                    func_808446F4(play, player);
                }
            }
        } else if (!(player->actor.bgCheckFlags & 1) && (func_8084D820 == player->actionFunc) &&
                   (player->unk_397 == 4)) {
            player->actor.world.pos.y = player->actor.prevPos.y;
        }

        if (play->csCtx.state != CS_STATE_0) {
            if ((player->csMode != PLAYER_CSMODE_5) && !(player->stateFlags1 & PLAYER_STATE1_800000)) {
                if (!(player->stateFlags2 & PLAYER_STATE2_80) && (player->actor.id == ACTOR_PLAYER)) {
                    if ((play->csCtx.playerAction != NULL) && (D_8085D384[play->csCtx.playerAction->action] != 0)) {
                        func_800B7298(play, NULL, PLAYER_CSMODE_5);
                        func_8082DABC(player);
                        // Can't be player->csMode == PLAYER_CSMODE_0
                    } else if ((!player->csMode) &&
                               !(player->stateFlags2 & (PLAYER_STATE2_400 | PLAYER_STATE2_8000000)) &&
                               (play->csCtx.state != CS_STATE_3)) {
                        func_800B7298(play, NULL, PLAYER_CSMODE_20);
                        func_8082DABC(player);
                    }
                }
            }
        }

        // Can't be != PLAYER_CSMODE_0
        if (player->csMode) {
            if ((player->csMode != PLAYER_CSMODE_6) ||
                !(player->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 |
                                         PLAYER_STATE1_200000 | PLAYER_STATE1_4000000))) {
                if (func_8085B08C != player->actionFunc) {
                    player->unk_AA5 = 4;
                    if (player->csMode == PLAYER_CSMODE_5) {
                        func_808387A0(play, player);
                        func_8082DAD4(player);
                    }
                }
            } else if (func_8085B08C != player->actionFunc) {
                func_8085AACC(play, player, 0);
            }
        } else {
            player->prevCsMode = PLAYER_CSMODE_0;
        }

        func_8083BF54(play, player);
        Lights_PointSetPosition(&player->lightInfo, player->actor.world.pos.x, player->actor.world.pos.y + 40.0f,
                                player->actor.world.pos.z);

        if (((player->targetedActor == NULL) || (player->targetedActor == player->talkActor) ||
             (player->targetedActor->hintId == 0xFF)) &&
            (player->tatlTextId == 0)) {
            player->stateFlags2 &= ~(PLAYER_STATE2_2 | PLAYER_STATE2_200000);
        }

        // TODO
        player->stateFlags1 &= ~0x401010;
        player->stateFlags2 &= ~0x441536D;
        player->stateFlags3 &= ~0x1E101950;
        func_808425B4(player);
        func_8082EB38(play, player);

        D_8085C3E4 = (player->stateFlags1 & PLAYER_STATE1_8000000) ? 0.5f : 1.0f;
        D_8085C3E8 = 1.0f / D_8085C3E4;

        D_80862B48 = D_80862B4C = 0;

        var_v1 = Play_InCsMode(play);
        D_80862B2C = player->currentMask;
        if (!(player->stateFlags3 & PLAYER_STATE3_4)) {
            player->actionFunc(player, play);
        }

        if (!var_v1) {
            Player_SetDoAction(play, player);
        }

        Player_UpdateCamAndSeqModes(play, player);

        if (player->skelAnime.moveFlags & 8) {
            AnimationContext_SetMoveActor(play, &player->actor, &player->skelAnime,
                                          (player->skelAnime.moveFlags & 4) ? 1.0f : player->ageProperties->unk_08);
        }

        func_80832578(player, play);
        if (player->actor.flags & ACTOR_FLAG_100) {
            player->talkActorDistance = 0.0f;
        } else {
            player->talkActor = NULL;
            player->exchangeItemId = 0;
            player->talkActorDistance = FLT_MAX;
        }
        if (!(player->actor.flags & ACTOR_FLAG_20000000) && (player->unk_AA5 != 5)) {
            player->unk_A90 = NULL;
            player->unk_A94 = FLT_MAX;
        }
        if (!(player->stateFlags1 & PLAYER_STATE1_800)) {
            player->interactRangeActor = NULL;
            player->getItemDirection = 0x6000;
        }
        if (player->actor.parent == NULL) {
            player->rideActor = NULL;
        }

        player->tatlTextId = 0;
        player->unk_B2B = -1;
        player->unk_AA0 = FLT_MAX;
        player->doorType = PLAYER_DOORTYPE_0;
        player->unk_B75 = 0;
        player->unk_A78 = NULL;

        Math_StepToF(&player->windSpeed, 0.0f, 0.5f);
        if ((player->unk_B62 != 0) || ((gSaveContext.unk_3F28 == 0) && (gSaveContext.save.playerData.magic != 0) &&
                                       (player->stateFlags1 & PLAYER_STATE1_10))) {
            func_8082F1AC(play, player);
        }

        temp_fv0 = player->actor.world.pos.y - player->actor.prevPos.y;
        var_fv1_2 = temp_fv0 + ((player->bodyPartsPos[6].y + player->bodyPartsPos[3].y) * 0.5f);
        temp_fv0 += player->bodyPartsPos[7].y + 10.0f;

        if (player->cylinder.info.toucher.dmgFlags == 0x80000) {
            player->cylinder.dim.height = 80;
            var_fv1_2 = ((temp_fv0 + var_fv1_2) * 0.5f) - 40.0f;
        } else {
            player->cylinder.dim.height = temp_fv0 - var_fv1_2;

            if (player->cylinder.dim.height < 0) {
                temp_fa0 = temp_fv0;
                temp_fv0 = var_fv1_2;
                var_fv1_2 = temp_fa0;
                player->cylinder.dim.height = -player->cylinder.dim.height;
            }
        }

        player->cylinder.dim.yShift = var_fv1_2 - player->actor.world.pos.y;

        if (player->unk_B62 != 0) {
            player->shieldCylinder.base.acFlags = 0;
            player->shieldCylinder.info.toucher.dmgFlags = 0x80000;
            player->shieldCylinder.info.toucherFlags = 1;
            player->shieldCylinder.info.bumperFlags = 0;
            player->shieldCylinder.dim.height = 80;
            player->shieldCylinder.dim.radius = 50;
            player->shieldCylinder.dim.yShift = ((temp_fv0 + var_fv1_2) * 0.5f - 40.0f) - player->actor.world.pos.y;

            Collider_UpdateCylinder(&player->actor, &player->shieldCylinder);
            CollisionCheck_SetAT(play, &play->colChkCtx, &player->shieldCylinder.base);
        } else if (player->stateFlags1 & PLAYER_STATE1_400000) {
            if ((player->transformation == PLAYER_FORM_GORON) || (player->transformation == PLAYER_FORM_DEKU)) {
                player->shieldCylinder.base.acFlags = 0x15;
                player->shieldCylinder.info.toucher.dmgFlags = 0x100000;
                player->shieldCylinder.info.toucherFlags = 0;
                player->shieldCylinder.info.bumperFlags = 1;

                if (player->transformation == 1) {
                    player->shieldCylinder.dim.height = 35;
                } else {
                    player->shieldCylinder.dim.height = 30;
                }

                if (player->transformation == 1) {
                    player->shieldCylinder.dim.radius = 30;
                } else {
                    player->shieldCylinder.dim.radius = 20;
                }

                player->shieldCylinder.dim.yShift = 0;
                Collider_UpdateCylinder(&player->actor, &player->shieldCylinder);
                CollisionCheck_SetAC(play, &play->colChkCtx, &player->shieldCylinder.base);
                player->cylinder.dim.yShift = 0;
                player->cylinder.dim.height = player->shieldCylinder.dim.height;
            } else {
                player->cylinder.dim.height = player->cylinder.dim.height * 0.8f;
            }
        }

        Collider_UpdateCylinder(&player->actor, &player->cylinder);
        if (!(player->stateFlags2 & PLAYER_STATE2_4000)) {
            if (!(player->stateFlags1 & (PLAYER_STATE3_4 | PLAYER_STATE3_80 | PLAYER_STATE3_2000 | PLAYER_STATE3_4000 |
                                         PLAYER_STATE3_800000)) &&
                !(player->stateFlags3 & PLAYER_STATE3_10000000)) {
                if ((func_808561B0 != player->actionFunc) && (func_80853D68 != player->actionFunc) &&
                    (player->actor.draw != NULL)) {
                    if ((player->actor.id != 0) && (player->csMode == PLAYER_CSMODE_110)) {
                        player->cylinder.dim.radius = 8;
                    }
                    CollisionCheck_SetOC(play, &play->colChkCtx, &player->cylinder.base);
                }
            }
            if (!(player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_4000000)) &&
                (player->invincibilityTimer <= 0)) {
                if ((func_808561B0 != player->actionFunc) &&
                    ((func_80857BE8 != player->actionFunc) || (player->unk_AE7 != 1))) {
                    if (player->cylinder.base.atFlags != 0) {
                        CollisionCheck_SetAT(play, &play->colChkCtx, &player->cylinder.base);
                    }
                    CollisionCheck_SetAC(play, &play->colChkCtx, &player->cylinder.base);
                }
            }
        }

        AnimationContext_SetNextQueue(play);
    }

    func_801229FC(player);
    Math_Vec3f_Copy(&player->actor.home.pos, &player->actor.world.pos);

    if ((player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000)) ||
        (player != GET_PLAYER(play))) {
        player->actor.colChkInfo.mass = MASS_IMMOVABLE;
    } else {
        player->actor.colChkInfo.mass = D_8085D174[player->transformation];
    }

    player->stateFlags3 &= ~(PLAYER_STATE3_4 | PLAYER_STATE3_400);
    Collider_ResetCylinderAC(play, &player->cylinder.base);
    Collider_ResetCylinderAC(play, &player->shieldCylinder.base);
    Collider_ResetCylinderAT(play, &player->shieldCylinder.base);
    Collider_ResetQuadAT(play, &player->meleeWeaponQuads[0].base);
    Collider_ResetQuadAT(play, &player->meleeWeaponQuads[1].base);
    Collider_ResetQuadAC(play, &player->shieldQuad.base);

    if (!(player->actor.bgCheckFlags & 1) || (player->actor.bgCheckFlags & 2) ||
        (player->actor.floorBgId != BGCHECK_SCENE)) {
        player->unk_AC0 = 0.0f;
    }
    player->actor.shape.yOffset = player->unk_ABC + player->unk_AC0;
}

Vec3f D_8085D41C = { 0.0f, 0.0f, -30.0f };

#ifdef NON_MATCHING
// in-function static bss
void Player_Update(Actor* thisx, PlayState* play) {
    static Vec3f D_80862AF0; // sDogSpawnPos
    Player* this = (Player*)thisx;
    s32 dogParams;
    s32 pad;
    Input input;
    s32 pad2;

    this->stateFlags3 &= ~PLAYER_STATE3_10;
    if (gSaveContext.dogParams < 0) {
        if (Object_GetIndex(&play->objectCtx, 0x132) < 0) {
            gSaveContext.dogParams = 0;
        } else {
            Actor* dog;

            gSaveContext.dogParams &= (u16)~0x8000;
            func_80835BC8(this, &this->actor.world.pos, &D_8085D41C, &D_80862AF0);

            dogParams = gSaveContext.dogParams;

            dog = Actor_Spawn(&play->actorCtx, play, 0xE2, D_80862AF0.x, D_80862AF0.y, D_80862AF0.z, 0,
                              this->actor.shape.rot.y, 0, dogParams | 0x8000);
            if (dog != NULL) {
                dog->room = -1;
            }
        }
    }

    if ((this->interactRangeActor != NULL) && (this->interactRangeActor->update == NULL)) {
        this->interactRangeActor = NULL;
    }

    if ((this->heldActor != NULL) && (this->heldActor->update == NULL)) {
        func_8082DCA0(play, this);
    }

    if ((play->actorCtx.unk268 != 0) && (this == GET_PLAYER(play))) {
        input = play->actorCtx.unk_26C;
    } else if ((this->csMode == PLAYER_CSMODE_5) || (this->stateFlags1 & 0x20000020) || (this != GET_PLAYER(play)) ||
               func_8082DA90(play) || (gSaveContext.save.playerData.health == 0)) {
        bzero(&input, sizeof(Input));
        this->fallStartHeight = this->actor.world.pos.y;
    } else {
        input = play->state.input[0];
        if (this->unk_B5E != 0) {
            input.cur.button &= ~0xC008;
            input.press.button &= ~0xC008;
        }
    }

    Player_UpdateCommon(this, play, &input);
    play->actorCtx.unk268 = 0;
    bzero(&play->actorCtx.unk_26C, sizeof(Input));

    MREG(52) = this->actor.world.pos.x;
    MREG(53) = this->actor.world.pos.y;
    MREG(54) = this->actor.world.pos.z;
    MREG(55) = this->actor.world.rot.y;
}
#else
#if 0
Vec3f D_80862AF0;
#endif
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Update.s")
#endif

void Player_DrawGameplay(PlayState* play, Player* this, s32 lod, Gfx* cullDList,
                         OverrideLimbDrawFlex overrideLimbDraw) {
    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0C, cullDList);
    gSPSegment(POLY_XLU_DISP++, 0x0C, cullDList);

    Player_DrawImpl(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, lod,
                    this->transformation, 0, this->actor.shape.face, overrideLimbDraw, func_80128BD0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80846460(Player* this) {
    Vec3f* pos;
    Vec3f* bodyPartsPos;
    s32 i;

    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.z = this->actor.world.pos.z;
    this->actor.focus.pos.y = this->actor.world.pos.y + 24.0f;

    pos = &this->actor.world.pos;
    bodyPartsPos = this->bodyPartsPos;
    for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
        Math_Vec3f_Copy(bodyPartsPos, pos);
        bodyPartsPos++;
    }

    this->bodyPartsPos[7].y = this->actor.world.pos.y + 24.0f;
    this->bodyPartsPos[0].y = this->actor.world.pos.y + 60.0f;
    Math_Vec3f_Copy(this->actor.shape.feetPos, pos);
    Math_Vec3f_Copy(&this->actor.shape.feetPos[1], pos);
}

struct_80124618 D_8085D428[] = {
    { 0, { 0, 0, 0 } },          { 1, { 0x50, 0xAA, 0x50 } }, { 3, { 0x64, 0x50, 0x64 } },
    { 7, { 0x64, 0x64, 0x64 } }, { 8, { 0x64, 0x64, 0x64 } },
};
struct_80124618 D_8085D450[] = {
    { 0, { 0, 0, 0 } },          { 1, { 0x50, 0xAA, 0x50 } }, { 3, { 0x64, 0x50, 0x64 } },
    { 7, { 0x64, 0x64, 0x64 } }, { 8, { 0x64, 0x64, 0x64 } },
};
struct_80124618 D_8085D478[] = {
    { 0, { 0, 0, 0 } },
    { 8, { 0, 0, 0 } },
};
struct_80124618 D_8085D488[] = {
    { 0, { 0x64, 0x64, 0x64 } }, { 1, { 0x64, 0x3C, 0x64 } }, { 3, { 0x64, 0x8C, 0x64 } },
    { 7, { 0x64, 0x50, 0x64 } }, { 9, { 0x64, 0x64, 0x64 } },
};
struct_80124618 D_8085D4B0[] = {
    { 0, { 0x64, 0x64, 0x64 } }, { 1, { 0x64, 0x46, 0x64 } }, { 3, { 0x64, 0x78, 0x64 } },
    { 6, { 0x64, 0x50, 0x64 } }, { 8, { 0x64, 0x64, 0x64 } }, { 9, { 0x64, 0x64, 0x64 } },
};
struct_80124618 D_8085D4E0[] = {
    { 0, { 0, 0, 0 } },          { 1, { 0, 0, 0 } },          { 3, { 0x64, 0x82, 0x64 } },
    { 5, { 0x82, 0x82, 0x82 } }, { 7, { 0x50, 0x5A, 0x50 } }, { 9, { 0x64, 0x64, 0x64 } },
};
struct_80124618 D_8085D510[] = {
    { 0, { 0, 0x32, 0 } },
    { 1, { 0, 0x32, 0 } },
};
struct_80124618 D_8085D520[] = {
    { 0, { 0x64, 0x78, 0x64 } },
    { 1, { 0x64, 0x78, 0x64 } },
};
struct_80124618 D_8085D530[] = {
    { 0, { 0xA0, 0x78, 0xA0 } },
    { 1, { 0xA0, 0x78, 0xA0 } },
};
struct_80124618 D_8085D540[] = {
    { 0, { 0, 0, 0 } },
    { 2, { 0x64, 0x64, 0x64 } },
};

struct_80124618* D_8085D550[3] = {
    D_8085D488,
    D_8085D4B0,
    D_8085D4E0,
};
struct_80124618* D_8085D55C[3] = {
    D_8085D428,
    D_8085D450,
    D_8085D478,
};
struct_80124618* D_8085D568[3] = {
    D_8085D510,
    D_8085D520,
    D_8085D530,
};

Gfx* D_8085D574[] = {
    object_link_nuts_DL_009C48,
    object_link_nuts_DL_009AB8,
    object_link_nuts_DL_009DB8,
};

Color_RGB8 D_8085D580 = { 255, 255, 255 };
Color_RGB8 D_8085D584 = { 80, 80, 200 };

void Player_Draw(Actor* thisx, PlayState* play) {
    Player* this = THIS;
    f32 one = 1.0f;
    s32 spEC = false;

    Math_Vec3f_Copy(&this->unk_D6C, this->bodyPartsPos);
    if (this->stateFlags3 & (PLAYER_STATE3_100 | PLAYER_STATE3_40000)) {
        struct_80124618** spE8 = D_8085D550;
        struct_80124618** spE4;
        f32 spE0;
        Gfx** spDC;
        s32 i;

        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Push();
        func_8012C268(play);
        spEC = true;
        if (this->stateFlags3 & PLAYER_STATE3_40000) {
            Matrix_SetTranslateRotateYXZ(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, &gZeroVec3s);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            spE8 = D_8085D568;
            spE0 = 0.0f;
        } else {
            Matrix_Translate(0.0f, -this->unk_ABC, 0.0f, MTXMODE_APPLY);
            spE0 = this->unk_AE8 - 6;
            if (spE0 < 0.0f) {
                spE8 = D_8085D55C;
                spE0 = this->unk_B86[0];
            }
        }

        spE4 = spE8;
        spDC = D_8085D574;

        for (i = 0; i < 3; i++, spE4++, spDC++) {
            Matrix_Push();
            func_80124618(*spE4, spE0, &this->unk_AF0[1]);
            Matrix_Scale(this->unk_AF0[1].x, this->unk_AF0[1].y, this->unk_AF0[1].z, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, *spDC);

            Matrix_Pop();
        }
        Matrix_Pop();

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (!(this->stateFlags2 & PLAYER_STATE2_20000000) && (this->unk_ABC > -3900.0f)) {
        OPEN_DISPS(play->state.gfxCtx);

        if (!spEC) {
            func_8012C268(play);
        }

        func_8012C2DC(play->state.gfxCtx);

        func_800B8050(&this->actor, play, 0);
        func_800B8118(&this->actor, play, 0);
        func_80122868(play, this);

        if (this->stateFlags3 & PLAYER_STATE3_1000) {
            Color_RGB8 spBC;
            f32 spB8 = this->unk_ABC + 1.0f;
            f32 spB4 = 1.0f - (this->unk_ABC * 0.5f);

            func_80846460(this);
            Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (1200.0f * this->actor.scale.y * spB8),
                             this->actor.world.pos.z, MTXMODE_NEW);

            if (this->unk_B86[0] != 0) {
                Matrix_RotateYS(this->unk_B28, MTXMODE_APPLY);
                Matrix_RotateXS(this->unk_B86[0], MTXMODE_APPLY);
                Matrix_RotateYS(-this->unk_B28, MTXMODE_APPLY);
            }

            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
            Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);

            Matrix_Scale(this->actor.scale.x * spB4 * 1.15f, this->actor.scale.y * spB8 * 1.15f,
                         CLAMP_MIN(spB8, spB4) * this->actor.scale.z * 1.15f, MTXMODE_APPLY);
            Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
            Scene_SetRenderModeXlu(play, 0, 1);
            Lib_LerpRGB(&D_8085D580, &D_8085D584, this->unk_B10[0], &spBC);

            gDPSetEnvColor(POLY_OPA_DISP++, spBC.r, spBC.g, spBC.b, 255);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gLinkGoronCurledDL);

            if (this->unk_B86[1] != 0) {
                if (this->unk_B86[1] < 3) {
                    func_80124618(D_8085D540, this->unk_B86[1], this->unk_AF0);
                    Matrix_Scale(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, MTXMODE_APPLY);
                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }

                gSPDisplayList(POLY_OPA_DISP++, object_link_goron_DL_00C540);
            }

            func_80122BA4(play, &this->unk_3D0, 1, 255);
            func_80122BA4(play, &this->unk_3D0, 2, 255);

            if (this->unk_B86[1] < 3) {
                if (this->unk_AE7 >= 5) {
                    f32 var_fa1;
                    u8 sp9B;

                    var_fa1 = (this->unk_AE7 - 4) * 0.02f;

                    if (this->unk_B86[1] != 0) {
                        sp9B = (-this->unk_B86[1] * 0x55) + 0xFF;
                    } else {
                        sp9B = (200.0f * var_fa1);
                    }

                    if (this->unk_B86[1] != 0) {
                        var_fa1 = 0.65f;
                    } else {
                        var_fa1 *= one;
                    }

                    Matrix_Scale(1.0f, var_fa1, var_fa1, MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_goron_Matanimheader_013138));
                    gDPSetEnvColor(POLY_XLU_DISP++, 155, 0, 0, sp9B);
                    gSPDisplayList(POLY_XLU_DISP++, object_link_goron_DL_0127B0);
                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_goron_Matanimheader_014684));
                    gSPDisplayList(POLY_XLU_DISP++, object_link_goron_DL_0134D0);
                }
            }
        } else if ((this->transformation == PLAYER_FORM_GORON) && (this->stateFlags1 & PLAYER_STATE1_400000)) {
            func_80846460(this);
            SkelAnime_DrawFlexOpa(play, this->unk_2C8.skeleton, this->unk_2C8.jointTable, this->unk_2C8.dListCount,
                                  NULL, NULL, NULL);
        } else {
            OverrideLimbDrawFlex sp84 = func_80125D4C;
            s32 lod = ((this->csMode != PLAYER_CSMODE_0) || (this->actor.projectedPos.z < 320.0f)) ? 0 : 1;
            Vec3f sp74;

            //! FAKE
            if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {}
            if (this->stateFlags1 & PLAYER_STATE1_100000) {
                SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->actor.focus.pos, &sp74);
                if (sp74.z < -4.0f) {
                    sp84 = func_801262C8;
                }
            }

            if (this->stateFlags2 & PLAYER_STATE2_4000000) {
                s16 temp_s0_2 = play->gameplayFrames * 600;
                s16 sp70 = (play->gameplayFrames * 1000) & 0xFFFF;

                Matrix_Push();

                this->actor.scale.y = -this->actor.scale.y;
                Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x,
                                             this->actor.world.pos.y + (2.0f * this->actor.depthInWater) +
                                                 (this->unk_ABC * this->actor.scale.y),
                                             this->actor.world.pos.z, &this->actor.shape.rot);
                Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
                Matrix_RotateXS(temp_s0_2, MTXMODE_APPLY);
                Matrix_RotateYS(sp70, MTXMODE_APPLY);
                Matrix_Scale(1.1f, 0.95f, 1.05f, MTXMODE_APPLY);
                Matrix_RotateYS(-sp70, MTXMODE_APPLY);
                Matrix_RotateXS(-temp_s0_2, MTXMODE_APPLY);
                Player_DrawGameplay(play, this, lod, gCullFrontDList, sp84);
                this->actor.scale.y = -this->actor.scale.y;

                Matrix_Pop();
            }

            gSPClearGeometryMode(POLY_OPA_DISP++, G_CULL_BOTH);

            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BOTH);

            if ((this->transformation == PLAYER_FORM_ZORA) && (this->unk_B62 != 0) &&
                !(this->stateFlags3 & PLAYER_STATE3_8000)) {
                Matrix_Push();
                Matrix_RotateXS(-0x4000, MTXMODE_APPLY);
                Matrix_Translate(0.0f, 0.0f, -1800.0f, MTXMODE_APPLY);
                Player_DrawZoraShield(play, this);
                Matrix_Pop();
            }

            Player_DrawGameplay(play, this, lod, gCullBackDList, sp84);
        }

        func_801229A0(play, this);
        if (this->stateFlags2 & PLAYER_STATE2_4000) {
            f32 temp_fa0 = this->unk_B48;

            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0U, -(s32)play->gameplayFrames & 0x7F, 0x20, 0x20, 1, 0,
                                        ((s32)play->gameplayFrames * -2) & 0x7F, 0x20, 0x20));

            Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, 255);

            gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);
        }

        if (this->unk_B2A > 0) {
            Player_DrawGetItem(play, this);
        }

        func_80122D44(play, &this->unk_3D0);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    play->actorCtx.unk5 &= ~8;
}

void Player_Destroy(Actor* thisx, PlayState* play) {
    Player* this = (Player*)thisx;

    Effect_Destroy(play, this->meleeWeaponEffectIndex[0]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[1]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[2]);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyCylinder(play, &this->cylinder);
    Collider_DestroyCylinder(play, &this->shieldCylinder);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->shieldQuad);
    ZeldaArena_Free(this->giObjectSegment);
    ZeldaArena_Free(this->maskObjectSegment);
    func_80115D5C(&play->state);
    func_80831454(this);
}

s32 func_80847190(PlayState* play, Player* this, s32 arg2) {
    s32 pad;
    s16 var_s0;

    if (!func_800B7128(this) && !func_8082EF20(this) && !arg2) {
        var_s0 = (s16)(D_80862B44->rel.stick_y * 0xF0);
        Math_SmoothStepToS(&this->actor.focus.rot.x, var_s0, 0xE, 0xFA0, 0x1E);

        var_s0 = (s16)(D_80862B44->rel.stick_x * -0x10);
        var_s0 = CLAMP(var_s0, -0xBB8, 0xBB8);
        this->actor.focus.rot.y += (s16)var_s0;
    } else {
        s16 temp3;

        temp3 = ((D_80862B44->rel.stick_y >= 0) ? 1 : -1) *
                (s32)((1.0f - Math_CosS(D_80862B44->rel.stick_y * 0xC8)) * 1500.0f);
        this->actor.focus.rot.x += temp3;

        if (this->stateFlags1 & PLAYER_STATE1_800000) {
            this->actor.focus.rot.x = CLAMP(this->actor.focus.rot.x, -0x1F40, 0xFA0);
        } else {
            this->actor.focus.rot.x = CLAMP(this->actor.focus.rot.x, -0x36B0, 0x36B0);
        }

        var_s0 = this->actor.focus.rot.y - this->actor.shape.rot.y;
        temp3 = ((D_80862B44->rel.stick_x >= 0) ? 1 : -1) *
                (s32)((1.0f - Math_CosS(D_80862B44->rel.stick_x * 0xC8)) * -1500.0f);
        var_s0 += temp3;

        this->actor.focus.rot.y = CLAMP(var_s0, -0x4AAA, 0x4AAA) + this->actor.shape.rot.y;
    }

    this->unk_AA6 |= 2;

    return func_80832754(this, (play->unk_1887C != 0) || func_800B7128(this) || func_8082EF20(this));
}

void func_8084748C(Player* this, f32* speed, f32 speedTarget, s16 yawTarget) {
    f32 incrStep;
    f32 maxSpeed;

    incrStep = this->skelAnime.curFrame - 10.0f;

    maxSpeed = (R_RUN_SPEED_LIMIT / 100.0f) * 0.8f;
    if (*speed > maxSpeed) {
        *speed = maxSpeed;
    }

    if ((0.0f < incrStep) && (incrStep < 16.0f)) {
        incrStep = fabsf(incrStep) * 0.5f;
    } else {
        speedTarget = 0.0f;
        incrStep = 0.0f;
    }

    Math_AsymStepToF(speed, speedTarget * 0.8f, incrStep, (fabsf(*speed) * 0.02f) + 0.05f);
    Math_ScaledStepToS(&this->currentYaw, yawTarget, 1600); // 1 ESS turn, also one frame of first-person rotation
}

void func_808475B4(Player* this) {
    f32 sp4;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_ft4 = -5.0f;
    f32 var_ft5 = this->ageProperties->unk_28;
    f32 var_ft5_4;

    temp_fv0 = this->actor.depthInWater - var_ft5;
    if (this->actor.velocity.y < 0.0f) {
        var_ft5 += 1.0f;
    }

    if (this->actor.depthInWater < var_ft5) {
        temp_fv0 = CLAMP(temp_fv0, -0.4f, -0.1f);
        sp4 = temp_fv0 - ((this->actor.velocity.y <= 0.0f) ? 0.0f : this->actor.velocity.y * 0.5f);
    } else {
        if (!(this->stateFlags1 & PLAYER_STATE1_80) && (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) &&
            (this->actor.velocity.y >= -5.0f)) {
            sp4 = -0.3f;
        } else if ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.velocity.y < 0.0f)) {
            var_ft4 = 0.0f;
            sp4 = -this->actor.velocity.y;
        } else {
            var_ft4 = 2.0f;
            var_ft5_4 = CLAMP(temp_fv0, 0.1f, 0.4f);
            sp4 = ((this->actor.velocity.y >= 0.0f) ? 0.0f : this->actor.velocity.y * -0.3f) + var_ft5_4;
        }

        if (this->actor.depthInWater > 100.0f) {
            this->stateFlags2 |= PLAYER_STATE2_400;
        }
    }

    this->actor.velocity.y += sp4;
    if (((this->actor.velocity.y - var_ft4) * sp4) > 0.0f) {
        this->actor.velocity.y = var_ft4;
    }
    this->actor.gravity = 0.0f;
}

void func_808477D0(PlayState* play, Player* this, Input* input, f32 arg3) {
    f32 var_fv0;

    if ((input != NULL) && CHECK_BTN_ANY(input->press.button, BTN_B | BTN_A)) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = 0.5f;
    }

    var_fv0 = var_fv0 * arg3;
    var_fv0 = CLAMP(var_fv0, 1.0f, 2.5f);
    this->skelAnime.playSpeed = var_fv0;

    LinkAnimation_Update(play, &this->skelAnime);
}

s32 func_80847880(PlayState* play, Player* this) {
    if (play->unk_1887C != 0) {
        if (play->sceneNum == SCENE_20SICHITAI) {
            Player_SetAction(play, this, func_80854430, 0);
            play->unk_1887C = 0;
            this->csMode = PLAYER_CSMODE_0;
            return true;
        }

        func_8082DE50(play, this);
        Player_SetAction(play, this, func_80854614, 0);
        if (!func_800B7118(this) || Player_IsHoldingHookshot(this)) {
            func_80831990(play, this, ITEM_BOW);
        }
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->csMode = PLAYER_CSMODE_0;
        this->stateFlags1 |= PLAYER_STATE1_100000;
        func_8082DABC(this);
        func_80836D8C(this);

        return true;
    }
    return false;
}

s32 func_80847994(PlayState* play, Player* this) {
    if (this->stateFlags3 & PLAYER_STATE3_20) {
        this->stateFlags3 &= ~PLAYER_STATE3_20;
        this->heldItemActionParam = PLAYER_AP_OCARINA;
        this->unk_AA5 = 5;
        func_80838A90(this, play);
        return true;
    }
    return false;
}

void func_808479F4(PlayState* play, Player* this, f32 arg2) {
    if (this->actor.wallBgId != BGCHECK_SCENE) {
        DynaPolyActor* actor = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

        if (actor != NULL) {
            func_800B72F8(actor, arg2, this->actor.world.rot.y);
        }
    }
}

void func_80847A50(Player* this) {
    func_800B8E58(this,
                  ((this->unk_AE7 != 0) ? NA_SE_PL_WALK_METAL1 : NA_SE_PL_WALK_LADDER) + this->ageProperties->unk_94);
}

Vec3f D_8085D588[] = {
    { 30.0f, 0.0f, 0.0f },
    { -30.0f, 0.0f, 0.0f },
};
Vec3f D_8085D5A0[] = {
    { 60.0f, 20.0f, 0.0f },
    { -60.0f, 20.0f, 0.0f },
};
Vec3f D_8085D5B8[] = {
    { 60.0f, -20.0f, 0.0f },
    { -60.0f, -20.0f, 0.0f },
};
Vec3f D_8085D5D0 = { 0.0f, 0.0f, -30.0f };

// related to mounting/unmounting the horse
s32 func_80847A94(PlayState* play, Player* this, s32 arg2, f32* arg3) {
    Actor* rideActor = this->rideActor;
    f32 sp60;
    f32 sp5C;
    Vec3f sp50;
    Vec3f sp44;
    CollisionPoly* sp40;
    CollisionPoly* sp3C;
    s32 sp38;
    s32 sp34;

    sp60 = rideActor->world.pos.y + 20.0f;
    sp5C = rideActor->world.pos.y - 20.0f;

    *arg3 = func_80835CD8(play, this, &D_8085D588[arg2], &sp50, &sp3C, &sp34);
    if ((sp5C < *arg3) && (*arg3 < sp60)) {
        if (!func_80835D58(play, this, &D_8085D5A0[arg2], &sp40, &sp38, &sp44)) {
            if (!func_80835D58(play, this, &D_8085D5B8[arg2], &sp40, &sp38, &sp44)) {
                this->actor.floorPoly = sp3C;
                this->actor.floorBgId = sp38;
                this->unk_B72 = SurfaceType_GetSfx(&play->colCtx, sp3C, sp34);
                return true;
            }
        }
    }
    return false;
}

s32 func_80847BF0(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;
    s32 var_a2; // sp38
    f32 sp34;

    if (this->unk_AE8 < 0) {
        this->unk_AE8 = 0x63;
    } else {
        var_a2 = (this->mountSide < 0) ? 0 : 1;

        if (!func_80847A94(play, this, var_a2, &sp34)) {
            var_a2 ^= 1;
            if (!func_80847A94(play, this, var_a2, &sp34)) {
                return false;
            }

            this->mountSide = -this->mountSide;
        }

        if (play->csCtx.state == CS_STATE_0) {
            if (!func_8082DA90(play)) {
                if (EN_HORSE_CHECK_1(rideActor) || EN_HORSE_CHECK_4(rideActor)) {
                    this->stateFlags2 |= PLAYER_STATE2_400000;

                    if (EN_HORSE_CHECK_1(rideActor) ||
                        (EN_HORSE_CHECK_4(rideActor) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_A))) {
                        rideActor->actor.child = NULL;

                        func_8083172C(play, this, func_808505D0, 0);
                        this->unk_B48 = sp34 - rideActor->actor.world.pos.y;

                        Player_AnimationPlayOnce(play, this,
                                                 (this->mountSide < 0) ? &gameplay_keep_Linkanim_00E060
                                                                       : &gameplay_keep_Linkanim_00E070);

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// Used in 2 horse-related functions
void func_80847E2C(Player* this, f32 arg1, f32 minFrame) {
    f32 addend;
    f32 dir;

    if ((this->unk_B48 != 0.0f) && (minFrame <= this->skelAnime.curFrame)) {
        if (arg1 < fabsf(this->unk_B48)) {
            dir = (this->unk_B48 >= 0.0f) ? 1 : -1;
            addend = dir * arg1;
        } else {
            addend = this->unk_B48;
        }
        this->actor.world.pos.y += addend;
        this->unk_B48 -= addend;
    }
}

s32 func_80847ED4(Player* this) {
    return (this->interactRangeActor != NULL) && (this->interactRangeActor->id == ACTOR_EN_ZOG) &&
           CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A);
}

void func_80847F1C(Player* this) {
    s32 pad;
    f32 yPos;
    s16 yaw;
    Actor* interactRangeActor = this->interactRangeActor;

    if (func_80847ED4(this)) {
        yPos = this->actor.world.pos.y;
        yaw = this->currentYaw - interactRangeActor->shape.rot.y;
        Lib_Vec3f_TranslateAndRotateY(&interactRangeActor->world.pos, interactRangeActor->shape.rot.y, &D_8085D5D0,
                                      &this->actor.world.pos);
        this->actor.world.pos.y = yPos;
        this->actor.shape.rot.y = interactRangeActor->shape.rot.y;

        interactRangeActor->speedXZ = Math_CosS(ABS_ALT(yaw)) * this->linearVelocity * 0.5f;
        if (interactRangeActor->speedXZ < 0.0f) {
            interactRangeActor->speedXZ = 0.0f;
        }
        func_8083133C(this);
    }
}

AnimSfxEntry D_8085D5DC[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 0, NA_SE_PL_SWIM, STOP),
};

void func_80847FF8(Player* this, f32* arg1, f32 arg2, s16 arg3) {
    func_8084748C(this, arg1, arg2, arg3);
    Player_PlayAnimSfx(this, D_8085D5DC);
    func_80847F1C(this);
}

void func_80848048(PlayState* play, Player* this) {
    Player_SetAction(play, this, func_80851588, 0);
    func_8082E634(play, this, &gameplay_keep_Linkanim_00DFD0);
}

s32 func_80848094(PlayState* play, Player* this, f32* arg2, s16* arg3) {
    LinkAnimationHeader* anim;
    s16 temp_v0 = this->currentYaw - *arg3;
    s32 temp_v0_2;

    if (ABS_ALT(temp_v0) > 0x6000) {
        anim = &gameplay_keep_Linkanim_00E000;
        if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
            this->currentYaw = *arg3;
        } else {
            *arg2 = 0.0f;
            *arg3 = this->currentYaw;
        }
    } else {
        temp_v0_2 = func_8083E514(this, arg2, arg3, play);
        if (temp_v0_2 > 0) {
            anim = &gameplay_keep_Linkanim_00DFD0;
        } else if (temp_v0_2 < 0) {
            anim = &gameplay_keep_Linkanim_00DFB8;
        } else {
            s16 diff = BINANG_SUB(this->actor.shape.rot.y, *arg3);

            if (diff > 0) {
                anim = &gameplay_keep_Linkanim_00DFB0;
            } else {
                anim = &gameplay_keep_Linkanim_00DFA8;
            }
        }
    }

    if (anim != this->skelAnime.animation) {
        func_8082E634(play, this, anim);
        return true;
    }
    return false;
}

void func_808481CC(PlayState* play, Player* this, f32 arg2) {
    f32 sp2C;
    s16 sp2A;

    func_80832F78(this, &sp2C, &sp2A, 0.0f, play);
    func_8084748C(this, &this->linearVelocity, sp2C / 2.0f, sp2A);
    func_8084748C(this, &this->actor.velocity.y, arg2, this->currentYaw);
}

void func_80848250(PlayState* play, Player* this) {
    this->unk_B2A = 0;
    this->stateFlags1 &= ~(PLAYER_STATE1_400 | PLAYER_STATE1_800);
    this->getItemId = GI_NONE;
    func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
}

void func_80848294(PlayState* play, Player* this) {
    func_80848250(play, this);
    func_8082DC28(this);
    func_80839E74(this, play);
    this->currentYaw = this->actor.shape.rot.y;
}

// Player_GetItem?
s32 func_808482E0(PlayState* play, Player* this) {
    if (this->getItemId == GI_NONE) {
        return true;
    }

    if (this->unk_AE7 == 0) {
        GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

        this->unk_AE7 = 1;
        Message_StartTextbox(play, giEntry->textId, &this->actor);
        Item_Give(play, giEntry->itemId);

        if ((this->getItemId >= GI_MASK_DEKU) && (this->getItemId <= GI_MASK_KAFEIS_MASK)) {
            func_801A3098(NA_BGM_GET_NEW_MASK);
        } else if (((this->getItemId >= GI_RUPEE_GREEN) && (this->getItemId <= GI_RUPEE_10)) ||
                   (this->getItemId == GI_RECOVERY_HEART)) {
            play_sound(NA_SE_SY_GET_BOXITEM);
        } else {
            s32 seqId;

            if ((this->getItemId == GI_HEART_CONTAINER) ||
                ((this->getItemId == GI_HEART_PIECE) && EQ_MAX_QUEST_HEART_PIECE_COUNT)) {
                seqId = NA_BGM_GET_HEART | 0x900;
            } else {
                s32 var_v1;

                if ((this->getItemId == GI_HEART_PIECE) ||
                    ((this->getItemId >= GI_RUPEE_PURPLE) && (this->getItemId <= GI_RUPEE_HUGE))) {
                    var_v1 = NA_BGM_GET_SMALL_ITEM;
                } else {
                    var_v1 = NA_BGM_GET_ITEM | 0x900;
                }
                seqId = var_v1;
            }

            func_801A3098(seqId);
        }
    } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        if (this->getItemId == GI_OCARINA) {
            // zelda teaching song of time cs?
            play->nextEntranceIndex = 0x1C00;
            gSaveContext.nextCutsceneIndex = 0xFFF2;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_03;
            gSaveContext.nextTransitionType = TRANS_TYPE_03;
            this->stateFlags1 &= ~PLAYER_STATE1_20000000;
            func_8085B28C(play, NULL, 7);
        }
        this->getItemId = GI_NONE;
    }

    return false;
}

AnimSfxEntry D_8085D5E0[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 60, NA_SE_IT_MASTER_SWORD_SWING, STOP),
};

void func_808484CC(Player* this) {
    Player_PlayAnimSfx(this, D_8085D5E0);
}

void func_808484F0(Player* this) {
    this->unk_B08[0] += this->unk_B08[1];
    this->unk_B08[1] -= this->unk_B08[0] * 5.0f;
    this->unk_B08[1] *= 0.3f;

    if (fabsf(this->unk_B08[1]) < 0.00001f) {
        this->unk_B08[1] = 0.0f;
        if (fabsf(this->unk_B08[0]) < 0.00001f) {
            this->unk_B08[0] = 0.0f;
        }
    }
}

s32 func_80848570(Player* this, PlayState* play) {
    if (!func_8083A6C0(play, this)) {
        if (func_808396B8(play, this)) {
            PlayerMeleeWeaponAnimation meleeWeaponAnimation = func_808335F4(this);

            func_80833864(play, this, meleeWeaponAnimation);
            if ((meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) ||
                ((this->transformation == PLAYER_FORM_FIERCE_DEITY) && func_8082FBE8(this))) {
                this->stateFlags2 |= PLAYER_STATE2_20000;
                func_808332A0(play, this, 0, meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H);
            }
        } else {
            return false;
        }
    }
    return true;
}

// elegy of emptiness (?)
void func_80848640(PlayState* play, Player* this) {
    EnTorch2* torch2;
    Actor* effChange;

    torch2 = (EnTorch2*)play->actorCtx.unk_254[this->transformation];
    if (torch2 != NULL) {
        Math_Vec3f_Copy(&torch2->actor.home.pos, &this->actor.world.pos);
        torch2->actor.home.rot.y = this->actor.shape.rot.y;
        torch2->state = 0;
        torch2->framesUntilNextState = 20;
    } else {
        torch2 = (EnTorch2*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TORCH2, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                                        this->transformation);
    }

    if (torch2 != NULL) {
        play->actorCtx.unk_254[this->transformation] = (Actor*)torch2;
        Play_SetupRespawnPoint(&play->state, this->transformation + 3, PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B));
    }

    effChange = Actor_Spawn(&play->actorCtx, play, ACTOR_EFF_CHANGE, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                            (GET_PLAYER_FORM << 3) | this->transformation);
    if (effChange != NULL) {
        //! @bug
        func_800B8E58((Player*)effChange, NA_SE_PL_TRANSFORM);
    }
}

s32 func_80848780(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }
    return false;
}

s32 func_808487B8(Player* this, PlayState* play) {
    if (func_80830B88(play, this) || func_80830DF0(this, play)) {
        return true;
    }
    return false;
}

s32 func_80848808(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->unk_284) ||
        ((Player_ItemToActionParam(this, this->heldItemId) == this->itemActionParam) &&
         (D_80862B48 = D_80862B48 || ((this->modelAnimType != PLAYER_ANIMTYPE_3) &&
                                      (this->itemActionParam != PLAYER_AP_STICK) && (play->unk_1887C == 0))))) {
        func_8082F43C(play, this, D_8085C9F0[this->itemActionParam]);
        this->unk_ACC = 0;
        this->unk_AA4 = 0;
        D_80862B4C = D_80862B48;
        return this->unk_AC4(this, play);
    }

    if (func_8082ED94(this) != 0) {
        func_80830D40(play, this);
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->unk_AA4 = 0;
    } else {
        func_80830D40(play, this);
    }
    return true;
}

s32 func_8084894C(Player* this, PlayState* play) {
    LinkAnimation_Update(play, &this->unk_284);
    if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_R)) {
        func_80830CE8(play, this);
    } else {
        this->stateFlags1 |= PLAYER_STATE1_400000;
        Player_SetModelsForHoldingShield(this);
        if ((this->transformation == PLAYER_FORM_ZORA) && CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
            func_8082F164(this, BTN_R | BTN_B);
        }
    }
    return true;
}

s32 func_80848A0C(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->unk_284)) {
        LinkAnimationHeader* anim;
        f32 lastFrame;

        anim = func_80830A58(play, this);
        lastFrame = Animation_GetLastFrame(anim);
        LinkAnimation_Change(play, &this->unk_284, anim, 1.0f, lastFrame, lastFrame, ANIMMODE_ONCE, 0.0f);
    }

    this->stateFlags1 |= PLAYER_STATE1_400000;
    Player_SetModelsForHoldingShield(this);
    return true;
}

s32 func_80848AB0(Player* this, PlayState* play) {
    // possibly a case of if ((D_80862B48 = D_80862B4C) || LinkAnimation_Update(play, &this->unk_284))
    D_80862B48 = D_80862B4C;
    if ((D_80862B48 != 0) || LinkAnimation_Update(play, &this->unk_284)) {
        func_8082F43C(play, this, D_8085C9F0[this->itemActionParam]);
        LinkAnimation_PlayLoop(play, &this->unk_284, D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType]);
        this->unk_AA4 = 0;
        this->unk_AC4(this, play);
        return false;
    }
    return true;
}

s32 func_80848B6C(Player* this, PlayState* play) {
    if (this->unk_B28 >= 0) {
        this->unk_B28 = -this->unk_B28;
    }

    if (!Player_IsHoldingHookshot(this) || func_80831124(play, this)) {
        if (!func_80830B88(play, this) && !func_80831094(this, play)) {
            return false;
        }
    }
    return true;
}

LinkAnimationHeader* D_8085D5E4[] = {
    &gameplay_keep_Linkanim_00D9E8,
    &gameplay_keep_Linkanim_00D528,
    &gameplay_keep_Linkanim_00E2F8,
};

LinkAnimationHeader* D_8085D5F0[] = {
    &gameplay_keep_Linkanim_00D9E0,
    &gameplay_keep_Linkanim_00D508,
    &gameplay_keep_Linkanim_00E2F8,
};

u16 D_8085D5FC[] = { NA_SE_IT_BOW_FLICK, NA_SE_PL_DEKUNUTS_MISS_FIRE, 0, 0 };

s32 func_80848BF4(Player* this, PlayState* play) {
    s32 index;
    s32 temp;

    if (Player_IsHoldingHookshot(this)) {
        index = 0;
    } else {
        temp = (this->transformation != PLAYER_FORM_DEKU) ? 1 : 2;
        index = temp;
    }

    if (this->transformation != PLAYER_FORM_DEKU) {
        Math_ScaledStepToS(&this->unk_AB2.z, 0x4B0, 0x190);
        this->unk_AA6 |= 0x100;
    }

    if ((this->unk_ACE == 0) && (func_8082ED94(this) == 0) &&
        (this->skelAnime.animation == &gameplay_keep_Linkanim_00D520)) {
        LinkAnimation_PlayOnce(play, &this->unk_284, D_8085D5E4[index]);
        this->unk_ACE = -1;
    } else if (LinkAnimation_Update(play, &this->unk_284)) {
        LinkAnimation_PlayLoop(play, &this->unk_284, D_8085D5F0[index]);
        this->unk_ACE = 1;
    } else if (this->unk_ACE == 1) {
        this->unk_ACE = 2;
    }

    if (this->unk_ACC >= 0xB) {
        this->unk_ACC--;
    }

    func_80831010(this, play);
    if ((this->unk_ACE > 0) && ((this->unk_B28 < 0) || ((D_80862B4C == 0) && !func_80830FD4(play)))) {
        func_8082F43C(play, this, func_80848E4C);
        if (this->unk_B28 >= 0) {
            if (index != 0) {
                if (!func_80831194(play, this)) {
                    func_800B8E58(this, D_8085D5FC[this->unk_B28 - 1]);
                }

                if (this->transformation == PLAYER_FORM_DEKU) {
                    LinkAnimation_PlayOnceSetSpeed(play, &this->unk_284, &gameplay_keep_Linkanim_00E2F0, 2.0f / 3.0f);
                }
            } else if (this->actor.bgCheckFlags & 1) {
                func_80831194(play, this);
            }
        }
        this->unk_ACC = 0xA;
        func_8082DABC(this);
    } else {
        this->stateFlags3 |= PLAYER_STATE3_40;
    }

    return 1;
}

s32 func_80848E4C(Player* this, PlayState* play) {
    s32 animFinished = LinkAnimation_Update(play, &this->unk_284);

    if (Player_IsHoldingHookshot(this) && !func_80831124(play, this)) {
        return 1;
    }

    if (!func_80830B88(play, this) &&
        ((((this->unk_B28 < 0) && (D_80862B4C != 0)) ||
          ((animFinished || (this->transformation != PLAYER_FORM_DEKU)) && (D_80862B48 != 0))) ||
         func_80830F9C(play))) {

        this->unk_B28 = ABS_ALT(this->unk_B28);
        if (func_808306F8(this, play)) {
            if (Player_IsHoldingHookshot(this)) {
                this->unk_ACE = 1;
            } else {
                LinkAnimation_PlayOnce(play, &this->unk_284,
                                       (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2F8
                                                                                  : &gameplay_keep_Linkanim_00D500);
            }
        }
    } else {
        if (this->unk_ACC != 0) {
            this->unk_ACC--;
        }

        if ((func_8082FBE8(this)) || (this->unk_AA5 != 0) || (this->stateFlags1 & PLAYER_STATE1_100000)) {
            if (this->unk_ACC == 0) {
                this->unk_ACC++;
            }
            return 1;
        }

        if (Player_IsHoldingHookshot(this)) {
            func_8082F43C(play, this, func_80848B6C);
        } else {
            func_8082F43C(play, this, func_80849054);
            LinkAnimation_PlayOnce(play, &this->unk_284,
                                   (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2F8
                                                                              : &gameplay_keep_Linkanim_00D4F8);
        }
        this->unk_ACC = 0;
    }

    return 1;
}

s32 func_80849054(Player* this, PlayState* play) {
    if (!(this->actor.bgCheckFlags & 1) || LinkAnimation_Update(play, &this->unk_284)) {
        func_8082F43C(play, this, func_80848B6C);
    }
    return true;
}

s32 func_808490B4(Player* this, PlayState* play) {
    Actor* heldActor = this->heldActor;

    if (heldActor == NULL) {
        func_808309CC(play, this);
    }

    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags1 & PLAYER_STATE1_800) {
        if (LinkAnimation_Update(play, &this->unk_284)) {
            LinkAnimation_PlayLoop(play, &this->unk_284, &gameplay_keep_Linkanim_00DB30);
        }

        if ((heldActor->id == ACTOR_EN_NIW) && (this->actor.velocity.y <= 0.0f)) {
            this->actor.terminalVelocity = -2.0f;
            this->actor.gravity = -0.5f;
            this->fallStartHeight = this->actor.world.pos.y;
        }
        return true;
    }
    return func_80848780(this, play);
}

s32 func_808491B4(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags1 & PLAYER_STATE1_2000000) {
        func_8082F43C(play, this, func_80849570);
    } else if (func_80831094(this, play)) {
        return true;
    }

    return false;
}

s32 func_8084923C(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->unk_284)) {
        func_8082F43C(play, this, func_808492C4);
        LinkAnimation_PlayLoop(play, &this->unk_284, &gameplay_keep_Linkanim_00E3C0);
    }
    if (this->unk_284.animation == &gameplay_keep_Linkanim_00E3C0) {
        func_80831010(this, play);
    }
    return true;
}

s32 func_808492C4(Player* this, PlayState* play) {
    LinkAnimation_Update(play, &this->unk_284);
    func_80831010(this, play);
    if (D_80862B4C == 0) {
        func_8082F43C(play, this, func_8084933C);
        LinkAnimation_PlayOnce(play, &this->unk_284, &gameplay_keep_Linkanim_00E398);
    }
    return true;
}

s32 func_8084933C(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->unk_284)) {
        func_8082F43C(play, this, func_80849570);
        this->unk_ACC = 0;
    } else if (LinkAnimation_OnFrame(&this->unk_284, 6.0f)) {
        Vec3f pos;
        s16 untargetedRotY;

        func_80835BF8(&this->bodyPartsPos[PLAYER_BODYPART_L_HAND], this->actor.shape.rot.y, 0.0f, &pos);
        pos.y = this->actor.world.pos.y + 50.0f;

        untargetedRotY = this->actor.shape.rot.y - 0x190;
        this->boomerangActor = Actor_Spawn(
            &play->actorCtx, play, ACTOR_EN_BOOM, pos.x, pos.y, pos.z, this->actor.focus.rot.x,
            (this->targetedActor != NULL) ? this->actor.shape.rot.y + 0x36B0 : untargetedRotY, 0, ZORA_BOOMERANG_LEFT);

        if (this->boomerangActor != NULL) {
            EnBoom* leftBoomerang = (EnBoom*)this->boomerangActor;
            EnBoom* rightBoomerang;

            leftBoomerang->moveTo = this->targetedActor;
            if (leftBoomerang->moveTo != NULL) {
                leftBoomerang->unk_1CF = 0x10;
            }
            leftBoomerang->unk_1CC = leftBoomerang->unk_1CF + 0x24;

            func_80835BF8(&this->bodyPartsPos[PLAYER_BODYPART_R_HAND], this->actor.shape.rot.y, 0.0f, &pos);

            untargetedRotY = (this->actor.shape.rot.y + 0x190);
            rightBoomerang =
                (EnBoom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOOM, pos.x, pos.y, pos.z, this->actor.focus.rot.x,
                                     (this->targetedActor != NULL) ? this->actor.shape.rot.y - 0x36B0 : untargetedRotY,
                                     0, ZORA_BOOMERANG_RIGHT);

            if (rightBoomerang != NULL) {
                rightBoomerang->moveTo = this->targetedActor;
                if (rightBoomerang->moveTo != NULL) {
                    rightBoomerang->unk_1CF = 0x10;
                }

                rightBoomerang->unk_1CC = rightBoomerang->unk_1CF + 0x24;
                leftBoomerang->actor.child = &rightBoomerang->actor;
                rightBoomerang->actor.parent = &leftBoomerang->actor;
            }

            this->stateFlags1 |= PLAYER_STATE1_2000000;
            this->stateFlags3 &= ~PLAYER_STATE1_800000;
            if (!func_80123420(this)) {
                func_8083133C(this);
            }

            this->unk_D57 = 20;

            func_800B8E58(this, NA_SE_IT_BOOMERANG_THROW);
            func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
        }
    }

    return true;
}

s32 func_80849570(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags3 & PLAYER_STATE3_800000) {
        func_8082F43C(play, this, func_80849620);
        LinkAnimation_PlayOnce(play, &this->unk_284, &gameplay_keep_Linkanim_00E3A0);
        this->stateFlags3 &= ~PLAYER_STATE3_800000;
        func_800B8E58(this, NA_SE_PL_CATCH_BOOMERANG);
        func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
        return true;
    }

    return false;
}

s32 func_80849620(Player* this, PlayState* play) {
    if (!func_808491B4(this, play) && LinkAnimation_Update(play, &this->unk_284)) {
        if (this->stateFlags1 & PLAYER_STATE1_2000000) {
            func_8082F43C(play, this, func_80849570);
            this->unk_ACC = 0;
        } else {
            func_8082F43C(play, this, func_80848780);
        }
    }
    return true;
}

void func_808496AC(Player* this, PlayState* play) {
    LinkAnimation_Update(play, &this->skelAnime);
    func_808323C0(this, play->playerActorCsIds[2]);

    if (DECR(this->unk_AE8) == 0) {
        if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
            func_80838760(this);
            Player_SetAction(play, this, func_80849FE0, 0);
            this->stateFlags1 &= ~PLAYER_STATE1_20000000;
        }
    } else if (this->unk_AE8 == 30) {
        if (Message_GetState(&play->msgCtx) != TEXT_STATE_NONE) {
            this->unk_AE8 += 1;
        } else {
            Message_StartTextbox(play, 0xC03, NULL);
        }
    }
}

void func_808497A0(Player* this, PlayState* play) {
    this->stateFlags3 |= PLAYER_STATE3_10000000;
    LinkAnimation_Update(play, &this->skelAnime);
    func_8083216C(this, play);

    if (MREG(64) == 0) {
        MREG(64) = 0x14;
        MREG(68) = 0;
        MREG(65) = MREG(66) = MREG(67) = MREG(68);
        play_sound(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
    } else if (MREG(64) > 0) {
        MREG(68) += MREG(64);
        if (MREG(68) > 0xFF) {
            MREG(68) = 0xFF;
            if (this->unk_B86[0] == 0) {
                this->unk_B86[0] = 1;
                func_8082DE50(play, this);
            } else {
                MREG(64) = -0x14;
                this->stateFlags1 &= ~PLAYER_STATE1_8000000;
                this->actor.bgCheckFlags &= ~1;
                Player_SetEquipmentData(play, this);
                this->prevBoots = this->currentBoots;

                if (this->unk_3CF != 0) {
                    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_3C0);
                    this->actor.shape.rot.y = this->unk_3CC;
                } else {
                    Math_Vec3f_Copy(&this->actor.world.pos, &gSaveContext.respawn[RESPAWN_MODE_DOWN].pos);
                    this->actor.shape.rot.y = gSaveContext.respawn[RESPAWN_MODE_DOWN].yaw;
                }

                Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                this->linearVelocity = 0.0f;
                this->currentYaw = this->actor.shape.rot.y;
                this->actor.velocity.y = 0.0f;
                Player_AnimationPlayOnce(play, this, func_8082ED20(this));

                if ((play->roomCtx.currRoom.num == this->unk_3CE) && (play->roomCtx.prevRoom.num < 0)) {
                    this->unk_AE8 = 5;
                } else {
                    play->roomCtx.currRoom.num = -1;
                    play->roomCtx.prevRoom.num = -1;
                    play->roomCtx.currRoom.segment = NULL;
                    play->roomCtx.prevRoom.segment = NULL;

                    func_8012EBF8(play, &play->roomCtx);
                    this->unk_AE8 = -1;
                    this->unk_AE7 = this->unk_3CE;
                }
            }
        }
    } else if (this->unk_AE8 < 0) {
        if (Room_StartRoomTransition(play, &play->roomCtx, this->unk_AE7) != 0) {
            Map_InitRoomData(play, play->roomCtx.currRoom.num);
            Minimap_SavePlayerRoomInitInfo(play);
            this->unk_AE8 = 5;
        }
    } else if (this->unk_AE8 > 0) {
        this->unk_AE8--;
    } else {
        MREG(68) += MREG(64);
        if (MREG(68) < 0) {
            MREG(68) = 0;
            MREG(64) = 0;
            func_808339B4(this, -40);
            func_8085B384(this, play);
            this->actor.bgCheckFlags |= 1;
        }
    }
}

void func_80849A9C(Player* this, PlayState* play) {
    f32 sp44;
    s16 sp42;
    s32 temp_v0;

    if (this->unk_AE8 != 0) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            func_8082E794(this);
            Player_AnimationPlayLoop(play, this, func_8082EF54(this));
            this->unk_AE8 = 0;
            this->stateFlags3 &= ~PLAYER_STATE3_8;
        }
        func_8082FC60(this);
    } else {
        func_8083E958(play, this);
    }

    func_80832F24(this);
    if (func_80833058(play, this, D_8085CFE4, 1)) {
        return;
    }

    if (!func_8082FB68(this) && (!func_80123434(this) || (func_8084894C != this->unk_AC4))) {
        func_8083B29C(this, play);
        return;
    }

    func_80832F78(this, &sp44, &sp42, 0.0f, play);

    temp_v0 = func_8083E404(this, sp44, sp42);
    if (temp_v0 > 0) {
        func_8083A844(this, play, sp42);
    } else if (temp_v0 < 0) {
        func_8083AF8C(this, sp42, play);
    } else if (sp44 > 4.0f) {
        func_8083B030(this, play);
    } else {
        u32 temp_v0_2;

        func_8083EA44(this, this->linearVelocity * 0.3f + 1.0f);
        func_8083E8E0(this, sp44, sp42);

        temp_v0_2 = this->unk_B38;
        if ((temp_v0_2 < 6) || ((temp_v0_2 - 0xE) < 6)) {
            Math_StepToF(&this->linearVelocity, 0.0f, 1.5f);
        } else {
            s16 temp_v0_3 = sp42 - this->currentYaw;
            s32 var_v1; // sp30

            var_v1 = ABS_ALT(temp_v0_3);
            if (var_v1 > 0x4000) {
                if (Math_StepToF(&this->linearVelocity, 0.0f, 1.5f) != 0) {
                    this->currentYaw = sp42;
                }
            } else {
                Math_AsymStepToF(&this->linearVelocity, sp44 * 0.3f, 2.0f, 1.5f);
                Math_ScaledStepToS(&this->currentYaw, sp42, var_v1 * 0.1f);
            }
        }
    }
}

void func_80849DD0(Player* this, PlayState* play) {
    f32 sp3C;
    s16 sp3A;
    s32 temp_v0;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->stateFlags3 &= ~PLAYER_STATE3_8;
    }

    func_80832F24(this);
    if (func_80833058(play, this, D_8085CFEC, 1)) {
        return;
    }

    if (func_8082FB68(this)) {
        func_8083B23C(this, play);
        return;
    }
    if (!func_80123434(this)) {
        func_8083172C(play, this, func_80849FE0, 1);
        this->currentYaw = this->actor.shape.rot.y;
        return;
    }
    if (func_8084894C == this->unk_AC4) {
        func_8083B23C(this, play);
        return;
    }

    func_80832F78(this, &sp3C, &sp3A, 0.0f, play);

    temp_v0 = func_8083E514(this, &sp3C, &sp3A, play);
    if (temp_v0 > 0) {
        func_8083A844(this, play, sp3A);
    } else if (temp_v0 < 0) {
        func_8083AECC(this, sp3A, play);
    } else if (sp3C > 4.9f) {
        func_8083B030(this, play);
        func_8082FC60(this);
    } else if (sp3C != 0.0f) {
        func_8083AF30(this, play);
    } else {
        s16 temp_v0_2 = sp3A - this->actor.shape.rot.y;

        if (ABS_ALT(temp_v0_2) > 0x320) {
            func_8083B0E4(play, this, sp3A);
        }
    }
}

void func_80849FE0(Player* this, PlayState* play) {
    s32 temp_v0 = func_8082ED94(this);
    s32 sp40 = LinkAnimation_Update(play, &this->skelAnime);
    f32 sp3C;
    s16 sp3A;
    s16 temp_v1_2;

    func_8083C85C(this);
    if (temp_v0 > 0) {
        func_8082EEA4(this, temp_v0 - 1);
    }

    if (sp40 ||
        ((this->currentMask == PLAYER_MASK_SCENTS) && (this->skelAnime.animation != &gameplay_keep_Linkanim_00D0B0)) ||
        ((this->currentMask != PLAYER_MASK_SCENTS) && (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0B0))) {
        if (this->unk_AE8 != 0) {
            if (DECR(this->unk_AE8) == 0) {
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }

            this->skelAnime.jointTable[0].y = (this->skelAnime.jointTable[0].y + ((this->unk_AE8 & 1) * 0x50)) - 0x28;
        } else {
            func_8082E794(this);
            Player_ChooseIdleAnim(play, this);
        }
        this->stateFlags3 &= ~PLAYER_STATE3_8;
    }

    func_80832F24(this);
    if ((this->unk_AE8 == 0) && !func_80847880(play, this) && !func_80833058(play, this, D_8085D01C, 1)) {
        if (func_8082FB68(this)) {
            func_8083B23C(this, play);
            return;
        }
        if (func_80123434(this)) {
            func_8083692C(this, play);
            return;
        }
        func_80832F78(this, &sp3C, &sp3A, 0.018f, play);
        if (sp3C != 0.0f) {
            func_8083A844(this, play, sp3A);
            return;
        }
        temp_v1_2 = sp3A - this->actor.shape.rot.y;

        if (ABS_ALT(temp_v1_2) > 0x320) {
            func_8083B0E4(play, this, sp3A);
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.y, sp3A, 0x4B0);
            this->currentYaw = this->actor.shape.rot.y;
            if (func_8082ED20(this) == this->skelAnime.animation) {
                func_8083C6E8(this, play);
            }
        }
    }
}

void func_8084A26C(Player* this, PlayState* play) {
    f32 var_fv0;
    s16 temp_v0_3;
    f32 sp44;
    s16 sp42;
    s32 var_v0;
    s32 temp_v0_2;
    s32 var_v1;
    f32 var_fv1;

    this->skelAnime.mode = 0;
    LinkAnimation_SetUpdateFunction(&this->skelAnime);

    this->skelAnime.animation = func_8082EFE4(this);
    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D520) {
        var_fv0 = 24.0f;
        var_fv1 = -(MREG(95) / 100.0f);
    } else {
        var_fv0 = 29.0f;
        var_fv1 = MREG(95) / 100.0f;
    }

    this->skelAnime.animLength = var_fv0;
    this->skelAnime.endFrame = var_fv0 - 1.0f;
    if (BINANG_SUB(this->currentYaw, this->actor.shape.rot.y) >= 0) {
        var_v0 = 1;
    } else {
        var_v0 = -1;
    }

    this->skelAnime.playSpeed = var_v0 * (this->linearVelocity * var_fv1);

    LinkAnimation_Update(play, &this->skelAnime);
    if (LinkAnimation_OnFrame(&this->skelAnime, 0.0f) || LinkAnimation_OnFrame(&this->skelAnime, var_fv0 / 2.0f)) {
        func_8082E12C(this, this->linearVelocity);
    }

    if (func_80833058(play, this, D_8085CFF8, 1)) {
        return;
    }

    if (func_8082FB68(this)) {
        func_8083B23C(this, play);
        return;
    }
    if (!func_80123434(this)) {
        func_8085B384(this, play);
        return;
    }
    func_80832F78(this, &sp44, &sp42, 0.0f, play);

    temp_v0_2 = func_8083E514(this, &sp44, &sp42, play);
    if (temp_v0_2 > 0) {
        func_8083A844(this, play, sp42);
        return;
    }
    if (temp_v0_2 < 0) {
        func_8083AECC(this, sp42, play);
        return;
    }
    if (sp44 > 4.9f) {
        func_8083B030(this, play);
        func_8082FC60(this);
        return;
    }
    if ((sp44 == 0.0f) && (this->linearVelocity == 0.0f)) {
        func_8083692C(this, play);
        return;
    }

    temp_v0_3 = sp42 - this->currentYaw;
    var_v1 = ABS_ALT(temp_v0_3);
    if (var_v1 > 0x4000) {
        if (Math_StepToF(&this->linearVelocity, 0.0f, 1.5f)) {
            this->currentYaw = sp42;
        }
    } else {
        Math_AsymStepToF(&this->linearVelocity, sp44 * 0.4f, 1.5f, 1.5f);
        Math_ScaledStepToS(&this->currentYaw, sp42, var_v1 * 0.1f);
    }
}

void func_8084A5C0(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;
    s32 sp2C;

    func_8083EE60(this, play);
    if (func_80833058(play, this, D_8085D004, 1)) {
        return;
    }

    if (func_8082FC24(this) == 0) {
        func_8083A844(this, play, this->currentYaw);
        return;
    }

    func_80832F78(this, &sp34, &sp32, 0.0f, play);

    sp2C = func_8083E514(this, &sp34, &sp32, play);
    if (sp2C >= 0) {
        if (!func_8083F190(this, &sp34, &sp32, play)) {
            if (sp2C != 0) {
                func_8083A794(this, play);
            } else if (sp34 > 4.9f) {
                func_8083B030(this, play);
            } else {
                func_8083AF30(this, play);
            }
        }
    } else {
        s16 sp2A = sp32 - this->currentYaw;

        Math_AsymStepToF(&this->linearVelocity, sp34 * 1.5f, 1.5f, 2.0f);
        Math_ScaledStepToS(&this->currentYaw, sp32, sp2A * 0.1f);
        if ((sp34 == 0.0f) && (this->linearVelocity == 0.0f)) {
            func_8083692C(this, play);
        }
    }
}

void func_8084A794(Player* this, PlayState* play) {
    s32 sp34 = LinkAnimation_Update(play, &this->skelAnime);
    f32 sp30;
    s16 sp2E;

    func_80832F24(this);

    if (func_80833058(play, this, D_8085D004, 1)) {
        return;
    }

    func_80832F78(this, &sp30, &sp2E, 0.0f, play);
    if (this->linearVelocity != 0.0f) {
        return;
    }

    this->currentYaw = this->actor.shape.rot.y;
    if (func_8083E514(this, &sp30, &sp2E, play) > 0) {
        func_8083A794(this, play);
    } else if ((sp30 != 0.0f) || sp34) {
        func_8083F230(this, play);
    }
}

void func_8084A884(Player* this, PlayState* play) {
    s32 sp1C = LinkAnimation_Update(play, &this->skelAnime);

    if (func_80833058(play, this, D_8085D004, 1)) {
        return;
    }

    if (sp1C) {
        func_8083692C(this, play);
    }
}

void func_8084A8E8(Player* this, PlayState* play) {
    f32 sp3C;
    s16 sp3A;
    s32 var_v0;

    func_8083F27C(play, this);
    if (func_80833058(play, this, D_8085D00C, 1)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    func_80832F78(this, &sp3C, &sp3A, 0.0f, play);
    if (func_80123434(this)) {
        var_v0 = func_8083E514(this, &sp3C, &sp3A, play);
    } else {
        var_v0 = func_8083E404(this, sp3C, sp3A);
    }

    if (var_v0 > 0) {
        func_8083A794(this, play);
    } else if (var_v0 < 0) {
        if (func_80123434(this)) {
            func_8083AECC(this, sp3A, play);
        } else {
            func_8083AF8C(this, sp3A, play);
        }
    } else if ((this->linearVelocity < 3.6f) && (sp3C < 4.0f)) {
        if ((func_80123420(this) == 0) && (func_80123434(this))) {
            func_8083AF30(this, play);
        } else {
            func_80836988(this, play);
        }
    } else {
        s16 temp_v0;
        s32 var_v1;
        s32 pad;

        func_8083E8E0(this, sp3C, sp3A);

        temp_v0 = sp3A - this->currentYaw;
        var_v1 = ABS_ALT(temp_v0);
        if (var_v1 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 3.0f)) {
                this->currentYaw = sp3A;
            }
        } else {
            sp3C = sp3C * 0.9f;
            Math_AsymStepToF(&this->linearVelocity, sp3C, 2.0f, 3.0f);
            Math_ScaledStepToS(&this->currentYaw, sp3A, var_v1 * 0.1f);
        }
    }
}

void func_8084AB4C(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;

    LinkAnimation_Update(play, &this->skelAnime);
    if (Player_IsHoldingTwoHandedWeapon(this)) {
        AnimationContext_SetLoadFrame(play, func_8082ED20(this), 0, this->skelAnime.limbCount,
                                      this->skelAnime.morphTable);
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->skelAnime.morphTable, D_8085B9F0);
    }

    func_80832F78(this, &sp34, &sp32, 0.018f, play);
    if ((this != GET_PLAYER(play)) && (this->targetedActor == NULL)) {
        sp32 = this->actor.home.rot.y;
    }

    if (func_80833058(play, this, D_8085D018, 1)) {
        return;
    }

    if (sp34 != 0.0f) {
        this->actor.shape.rot.y = sp32;
        func_8083A794(this, play);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, sp32, this->unk_B4E)) {
        func_80839E74(this, play);
    }
    this->currentYaw = this->actor.shape.rot.y;
}

void func_8084AC84(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (this->linearVelocity < 1.0f) {
        this->skelAnime.animation = &gameplay_keep_Linkanim_00D228;
    } else {
        this->skelAnime.animation = &gameplay_keep_Linkanim_00D220;
    }
    LinkAnimation_Update(play, &this->skelAnime);

    if (!func_80847880(play, this) &&
        (!func_80833058(play, this, D_8085D01C, 1) || (func_8084AC84 == this->actionFunc))) {
        f32 sp3C;
        f32 temp_fv0;
        f32 temp_fv1;
        s16 sp32;
        s16 sp30;

        if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
            func_80839E74(this, play);
            return;
        }

        this->linearVelocity = this->unk_B48;
        func_80832F78(this, &sp3C, &sp32, 0.018f, play);
        sp30 = sp32;

        if (!func_8083A4A4(this, &sp3C, &sp32, REG(43) / 100.0f)) {
            func_8083CB04(this, sp3C, sp32, REG(19) / 100.0f, 1.5f, 0x3E8);
            func_8083C8E8(this, play);
            if ((this->linearVelocity == 0.0f) && (sp3C == 0.0f)) {
                this->currentYaw = sp30;
                this->actor.shape.rot.y = this->currentYaw;
            }
        }

        this->unk_B48 = this->linearVelocity;
        temp_fv0 = this->skelAnime.curFrame + 5.0f;
        temp_fv1 = this->skelAnime.animLength / 2.0f;

        // effectively an fmodf
        temp_fv0 -= temp_fv1 * (s32)(temp_fv0 / temp_fv1);
        this->linearVelocity *= Math_CosS(temp_fv0 * 1000.0f) * 0.4f;
    }
}

void func_8084AEEC(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;
    LinkAnimation_Update(play, &this->skelAnime);
    func_80832F24(this);
    if (!func_80847880(play, this)) {
        if (!func_80833058(play, this, D_8085D01C, 0) || (func_8084AEEC == this->actionFunc)) {
            if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
                func_80839E74(this, play);
            }
        }
    }
}

void func_8084AF9C(Player* this, PlayState* play) {
    f32 sp2C; // player speed?
    s16 sp2A;

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_8083F57C(this, play);
    if (func_80833058(play, this, D_8085D028, 1)) {
        return;
    }

    if (func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    func_80832F78(this, &sp2C, &sp2A, 0.018f, play);
    if (this->currentMask == PLAYER_MASK_BUNNY) {
        sp2C *= 1.5f;
    }

    if (!func_8083A4A4(this, &sp2C, &sp2A, REG(43) / 100.0f)) {
        func_8083CB58(this, sp2C, sp2A);
        func_8083C8E8(this, play);
        if ((this->linearVelocity == 0.0f) && (sp2C == 0.0f)) {
            func_80839E3C(this, play);
        }
    }
}

void func_8084B0EC(Player* this, PlayState* play) {
    f32 sp2C;
    s16 sp2A;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8083F57C(this, play);
    if (func_80833058(play, this, D_8085D034, 1)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    func_80832F78(this, &sp2C, &sp2A, 0.0f, play);
    if (!func_8083A4A4(this, &sp2C, &sp2A, REG(43) / 100.0f)) {
        if (((func_80123434(this) != 0) && (sp2C != 0) && (func_8083E514(this, &sp2C, &sp2A, play) <= 0)) ||
            (!func_80123434(this) && (func_8083E404(this, sp2C, sp2A) <= 0))) {
            func_80836988(this, play);
        } else {
            func_8083CB58(this, sp2C, sp2A);
            func_8083C8E8(this, play);
            if ((this->linearVelocity == 0.0f) && (sp2C == 0.0f)) {
                func_80836988(this, play);
            }
        }
    }
}

void func_8084B288(Player* this, PlayState* play) {
    s32 sp34 = LinkAnimation_Update(play, &this->skelAnime);
    f32 sp30;
    s16 sp2E;

    if (func_80833058(play, this, D_8085D00C, 1)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    func_80832F78(this, &sp30, &sp2E, 0.0f, play);
    if ((this->skelAnime.morphWeight == 0.0f) && (this->skelAnime.curFrame > 5.0f)) {
        func_80832F24(this);
        if ((this->skelAnime.curFrame > 10.0f) && (func_8083E404(this, sp30, sp2E) < 0)) {
            func_8083AF8C(this, sp2E, play);
        } else if (sp34) {
            func_8083B090(this, play);
        }
    }
}

void func_8084B3B8(Player* this, PlayState* play) {
    s32 sp34 = LinkAnimation_Update(play, &this->skelAnime);
    f32 sp30;
    s16 sp2E;

    func_80832F24(this);
    if (func_80833058(play, this, D_8085D044, 1)) {
        return;
    }

    func_80832F78(this, &sp30, &sp2E, 0.0f, play);
    if (this->linearVelocity == 0.0f) {
        this->currentYaw = this->actor.shape.rot.y;
        if (func_8083E404(this, sp30, sp2E) > 0) {
            func_8083A794(this, play);
        } else if ((sp30 != 0.0f) || sp34) {
            func_80836988(this, play);
        }
    }
}

void func_8084B4A8(Player* this, PlayState* play) {
    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DB10) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            func_8082E794(this);
            func_8082E438(play, this, D_8085BE84[PLAYER_ANIMGROUP_31][this->modelAnimType]);
        }
    } else {
        func_8082E67C(play, this, D_8085BE84[PLAYER_ANIMGROUP_32][this->modelAnimType]);
    }

    if (DECR(this->unk_AE8) == 0) {
        if (!func_80838A90(this, play)) {
            func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_33][this->modelAnimType], play);
        }
        this->actor.flags &= ~ACTOR_FLAG_100;
        func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
    }
}

void func_8084B5C0(Player* this, PlayState* play) {
    func_80832F24(this);

    if (this->transformation == PLAYER_FORM_GORON) {
        SkelAnime_Update(&this->unk_2C8);

        if (!func_8083FE38(this, play)) {
            if (!func_8083A274(this, play)) {
                this->stateFlags1 &= ~PLAYER_STATE1_400000;

                if (this->heldItemActionParam < PLAYER_AP_NONE) {
                    func_80123C58(this);
                }

                func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_21][this->modelAnimType], play);
                func_80830B38(this);
            } else {
                this->stateFlags1 |= PLAYER_STATE1_400000;
            }
        }

        return;
    }

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (!Player_IsGoronOrDeku(this)) {
            Player_AnimationPlayLoop(play, this, D_8085BE84[PLAYER_ANIMGROUP_20][this->modelAnimType]);
        }

        this->unk_AE8 = 1;
        this->unk_AE7 = 0;
    }

    if (!Player_IsGoronOrDeku(this)) {
        this->stateFlags1 |= PLAYER_STATE1_400000;
        func_8083216C(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_400000;
        if (this->transformation == PLAYER_FORM_ZORA) {
            func_8082F164(this, BTN_R | BTN_B);
        }
    }

    if (this->unk_AE8 != 0) {
        f32 yStick = D_80862B44->rel.stick_y * 180;
        f32 xStick = D_80862B44->rel.stick_x * -120;
        s16 temp_a0 = this->actor.shape.rot.y - Camera_GetInputDirYaw(play->cameraPtrs[play->activeCamId]);
        s16 var_a1;
        s16 temp_ft5;
        s16 var_a2;
        s16 var_a3;

        var_a1 = (yStick * Math_CosS(temp_a0)) + (Math_SinS(temp_a0) * xStick);
        temp_ft5 = (xStick * Math_CosS(temp_a0)) - (Math_SinS(temp_a0) * yStick);

        var_a1 = CLAMP_MAX(var_a1, 0xDAC);
        var_a2 = ABS_ALT(var_a1 - this->actor.focus.rot.x) * 0.25f;
        var_a2 = CLAMP_MIN(var_a2, 0x64);

        var_a3 = ABS_ALT(temp_ft5 - this->unk_AB2.y) * 0.25f;
        var_a3 = CLAMP_MIN(var_a3, 0x32);
        Math_ScaledStepToS(&this->actor.focus.rot.x, var_a1, var_a2);

        this->unk_AB2.x = this->actor.focus.rot.x;
        Math_ScaledStepToS(&this->unk_AB2.y, temp_ft5, var_a3);

        if (this->unk_AE7 != 0) {
            if (!func_808401F4(play, this)) {
                if (this->skelAnime.curFrame < 2.0f) {
                    func_8082FA5C(play, this, 1);
                }
            } else {
                this->unk_AE8 = 1;
                this->unk_AE7 = 0;
            }
        } else if (!func_8083FE38(this, play)) {
            if (func_8083A274(this, play) != 0) {
                func_8083FD80(this, play);
            } else {
                this->stateFlags1 &= ~PLAYER_STATE1_400000;
                func_8082DC38(this);

                if (Player_IsGoronOrDeku(this)) {
                    func_80836A5C(this, play);
                    LinkAnimation_Change(play, &this->skelAnime, this->skelAnime.animation, 1.0f,
                                         Animation_GetLastFrame(this->skelAnime.animation), 0.0f, 2, 0.0f);
                } else {
                    if (this->heldItemActionParam < PLAYER_AP_NONE) {
                        func_80123C58(this);
                    }

                    func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_21][this->modelAnimType], play);
                }

                func_800B8E58(this, NA_SE_IT_SHIELD_REMOVE);
                return;
            }
        } else {
            return;
        }
    }

    this->stateFlags1 |= PLAYER_STATE1_400000;
    Player_SetModelsForHoldingShield(this);
    this->unk_AA6 |= 0xC1;
}

void func_8084BAA4(Player* this, PlayState* play) {
    func_80832F24(this);
    if (this->unk_AE7 == 0) {
        D_80862B04 = func_8083216C(this, play);
        if ((func_8084894C == this->unk_AC4) || (func_808331FC(play, this, &this->unk_284, 4.0f) > 0)) {
            Player_SetAction(play, this, func_80849A9C, 1);
        }
    } else {
        s32 temp_v0;

        this->stateFlags1 |= PLAYER_STATE1_400000;
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
        if ((temp_v0 != 0) && ((temp_v0 > 0) || LinkAnimation_Update(play, &this->skelAnime))) {
            LinkAnimationHeader* anim;
            f32 lastFrame;

            Player_SetAction(play, this, func_8084B5C0, 1);
            Player_SetModelsForHoldingShield(this);
            anim = D_8085BE84[PLAYER_ANIMGROUP_19][this->modelAnimType];
            lastFrame = Animation_GetLastFrame(anim);
            LinkAnimation_Change(play, &this->skelAnime, anim, 1.0f, lastFrame, lastFrame, ANIMMODE_ONCE, 0.0f);
        }
    }
}

void func_8084BBF0(Player* this, PlayState* play) {
    s32 temp_v0;

    func_80832F24(this);
    temp_v0 = func_808331FC(play, this, &this->skelAnime, 16.0f);
    if (temp_v0 != 0) {
        if (LinkAnimation_Update(play, &this->skelAnime) || (temp_v0 > 0)) {
            func_80836988(this, play);
        }
    }
}

void func_8084BC64(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20 | PLAYER_STATE2_40;
    func_808345A8(this);

    if (!(this->stateFlags1 & PLAYER_STATE1_20000000) && (this->unk_AE8 == 0) && (this->unk_B75 != 0)) {
        s16 temp_v0 = this->unk_B76;
        s16 temp_v1 = this->actor.shape.rot.y - temp_v0;

        this->actor.shape.rot.y = temp_v0;
        this->currentYaw = temp_v0;
        this->linearVelocity = this->unk_B78;

        if (ABS_ALT(temp_v1) > 0x4000) {
            this->actor.shape.rot.y = temp_v0 + 0x8000;
        }

        if (this->actor.velocity.y < 0.0f) {
            this->actor.gravity = 0.0f;
            this->actor.velocity.y = 0.0f;
        }
    }

    if (LinkAnimation_Update(play, &this->skelAnime) && (this->actor.bgCheckFlags & 1)) {
        if (this->unk_AE8 != 0) {
            this->unk_AE8--;
            if (this->unk_AE8 == 0) {
                func_8085B384(this, play);
            }
        } else if ((this->stateFlags1 & PLAYER_STATE1_20000000) ||
                   (!(this->cylinder.base.acFlags & 2) && (this->unk_B75 == 0))) {
            if (this->stateFlags1 & PLAYER_STATE1_20000000) {
                this->unk_AE8++;
            } else {
                Player_SetAction(play, this, func_8084BE40, 0);
                this->stateFlags1 |= PLAYER_STATE1_4000000;
            }

            Player_AnimationPlayOnce(play, this,
                                     (this->currentYaw != this->actor.shape.rot.y) ? &gameplay_keep_Linkanim_00DC80
                                                                                   : &gameplay_keep_Linkanim_00DAD8);
            func_8082DF8C(this, NA_SE_VO_LI_FREEZE);
        }
    }

    if (this->actor.bgCheckFlags & 2) {
        func_8082E094(this, NA_SE_PL_BOUND);
    }
}

void func_8084BE40(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    func_808345A8(this);
    func_80832F24(this);
    if (LinkAnimation_Update(play, &this->skelAnime) && (this->linearVelocity == 0.0f)) {
        if (this->stateFlags1 & PLAYER_STATE1_20000000) {
            this->unk_AE8 += 1;
        } else {
            Player_SetAction(play, this, func_8084BF28, 0);
            this->stateFlags1 |= PLAYER_STATE1_4000000;
        }

        func_8082DB90(play, this,
                      (this->currentYaw != this->actor.shape.rot.y) ? &gameplay_keep_Linkanim_00DC88
                                                                    : &gameplay_keep_Linkanim_00DAE0);
        this->currentYaw = this->actor.shape.rot.y;
    }
}

AnimSfxEntry D_8085D604[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 20, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 30, 0, STOP),
};

void func_8084BF28(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_808345A8(this);
    if (this->stateFlags1 & PLAYER_STATE1_20000000) {
        LinkAnimation_Update(play, &this->skelAnime);
    } else {
        s32 temp_v0 = func_808331FC(play, this, &this->skelAnime, 16.0f);

        if (temp_v0 != 0) {
            if (LinkAnimation_Update(play, &this->skelAnime) || (temp_v0 > 0)) {
                func_80836988(this, play);
            }
        }
    }

    Player_PlayAnimSfx(this, D_8085D604);
}

AnimSfxEntry D_8085D60C[] = {
    ANIMSFX(ANIMSFX_TYPE_2, 60, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 140, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 164, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 170, 0, STOP),
};

void func_8084BFDC(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) && (this->actor.depthInWater <= 0.0f)) {
        if ((play->roomCtx.currRoom.unk2 == 3) || (D_80862B08 == 9) ||
            ((func_808340AC(D_80862B08) >= 0) &&
             !SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
            func_808344C0(play, this);
        }
    }

    func_80832F24(this);
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this == GET_PLAYER(play)) {
            func_80840770(play, this);
        }
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D698) {
        Player_PlayAnimSfx(this, D_8085D60C);
    } else if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00DC28) &&
               LinkAnimation_OnFrame(&this->skelAnime, 88.0f)) {
        func_8082E094(this, NA_SE_PL_BOUND);
    }
}

s32 func_8084C124(PlayState* play, Player* this) {
    if (func_80837730(play, this, 3.0f, 500)) {
        func_800B8E58(this, NA_SE_EV_DIVE_INTO_WATER);
        return true;
    }
    return false;
}

void func_8084C16C(Player* this, PlayState* play) {
    f32 sp44;
    s16 sp42;
    Actor* heldActor;

    if (func_80123420(this) != 0) {
        this->actor.gravity = -1.2f;
    }

    if (!(this->actor.bgCheckFlags & 1)) {
        func_80832F78(this, &sp44, &sp42, 0.0f, play);
        if (this->stateFlags1 & 0x800) {
            heldActor = this->heldActor;
            if (!func_808313A8(play, this, heldActor) && (heldActor->id == ACTOR_EN_NIW) &&
                CHECK_BTN_ANY(D_80862B44->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
                func_808409A8(play, this, this->linearVelocity + 2.0f, this->actor.velocity.y + 2.0f);
            }
        }

        LinkAnimation_Update(play, &this->skelAnime);
        if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00DD50) &&
            LinkAnimation_OnFrame(&this->skelAnime, 4.0f)) {
            func_800B8E58(this, NA_SE_PL_ROLL);
        }

        if (this->transformation == PLAYER_FORM_DEKU) {
            s16 prevYaw = this->currentYaw;

            func_808378FC(play, this);
            func_8083CBC4(this, sp44 * 0.5f, sp42, 2.0f, 0.2f, 0.1f, 0x190);

            if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E270) {
                this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

                this->unk_B10[0] += -800.0f;
                this->actor.shape.rot.y += BINANG_ADD((s16)this->unk_B10[0], BINANG_SUB(this->currentYaw, prevYaw));
                Math_StepToF(&this->unk_B10[1], 0.0f, this->unk_B10[0]);
            }
        } else {
            func_8083CBC4(this, sp44, sp42, 1.0f, 0.05f, 0.1f, 0xC8);
        }

        func_8083216C(this, play);
        if ((((this->stateFlags2 & PLAYER_STATE2_80000) && ((this->unk_AE7 == 2) || (this->unk_AE7 >= 4))) ||
             !func_80839770(this, play)) &&
            (this->actor.velocity.y < 0.0f)) {
            if (this->unk_AE8 >= 0) {
                if ((this->actor.bgCheckFlags & 8) || (this->unk_AE8 == 0) || (this->fallDistance > 0)) {
                    if ((D_80862B18 > 800.0f) || (this->stateFlags3 & PLAYER_STATE3_10000)) {
                        func_80840980(this, NA_SE_VO_LI_FALL_S);
                        this->stateFlags3 &= ~PLAYER_STATE3_10000;
                    }
                    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00DD10, 1.0f, 0.0f, 0.0f,
                                         ANIMMODE_ONCE, 8.0f);
                    this->unk_AE8 = -1;
                }
            } else {
                if ((this->unk_AE8 == -1) && (this->fallDistance > 120) && (D_80862B18 > 280.0f)) {
                    this->unk_AE8 = -2;
                    func_80840980(this, NA_SE_VO_LI_FALL_L);
                }

                if ((this->actor.bgCheckFlags & 0x200) &&
                    !(this->stateFlags1 & (PLAYER_STATE1_800 | PLAYER_STATE1_8000000)) &&
                    (this->linearVelocity > 0.0f)) {
                    if ((this->transformation != PLAYER_FORM_GORON) &&
                        ((this->transformation != PLAYER_FORM_DEKU) || (this->unk_B67 != 0))) {
                        if ((this->wallHeight >= 150.0f) && (this->unk_AE3[this->unk_ADE] == 0)) {
                            if (func_8083D860(this, play)) {
                                func_8084C124(play, this);
                            }
                        } else if ((this->unk_B5C >= 2) &&
                                   ((this->wallHeight < (150.0f * this->ageProperties->unk_08)) &&
                                    (((this->actor.world.pos.y - this->actor.floorHeight) + this->wallHeight)) >
                                        (70.0f * this->ageProperties->unk_08))) {
                            AnimationContext_DisableQueue(play);
                            if (this->stateFlags3 & PLAYER_STATE3_10000) {
                                func_8082DF8C(this, NA_SE_VO_LI_HOOKSHOT_HANG);
                            } else {
                                func_8082DF8C(this, NA_SE_VO_LI_HANG);
                            }

                            this->actor.world.pos.y += this->wallHeight;
                            func_80837CEC(play, this, this->actor.wallPoly, this->wallDistance,
                                          GET_PLAYER_ANIM(PLAYER_ANIMGROUP_38, this->modelAnimType));
                            this->currentYaw += 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            this->stateFlags1 |= PLAYER_STATE1_2000;

                            func_8084C124(play, this);
                        }
                    }
                }
            }
        }
    } else {
        func_80837134(play, this);
        func_8083216C(this, play);
    }

    func_80838A90(this, play);
}

AnimSfxEntry D_8085D61C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_SWORD_N, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_3, 6, NA_SE_PL_WALK_GROUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 6, NA_SE_PL_ROLL, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 18, 0, STOP),
};

void func_8084C6EC(Player* this, PlayState* play) {
    s32 animFinished;

    this->stateFlags2 |= PLAYER_STATE2_20;
    this->stateFlags3 |= PLAYER_STATE3_8000000;

    animFinished = LinkAnimation_Update(play, &this->skelAnime);
    if (LinkAnimation_OnFrame(&this->skelAnime, 8.0f)) {
        func_808339B4(this, -10);
    }

    if (this->skelAnime.curFrame >= 8.0f) {
        if (this->skelAnime.curFrame < 18.0f) {
            func_8082F0E4(this, 0x04000000, 1, 12);
        } else {
            func_8082F09C(this);
        }
    }

    if (func_8083FE38(this, play)) {
        return;
    }

    if (this->unk_AE8 != 0) {
        s32 temp_v0;

        Math_StepToF(&this->linearVelocity, 0.0f, 2.0f);
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 5.0f);
        if (temp_v0 != 0) {
            if ((temp_v0 > 0) || animFinished) {
                func_80836A5C(this, play);
            }
        }
    } else if (!func_80840A30(play, this, &this->linearVelocity, 6.0f)) {
        if ((this->skelAnime.curFrame < 15.0f) || !func_80848570(this, play)) {
            f32 sp3C;
            s16 sp3A;

            if (this->skelAnime.curFrame >= 20.0f) {
                func_80836A5C(this, play);
                return;
            }

            func_80832F78(this, &sp3C, &sp3A, 0.018f, play);
            sp3C *= 1.5f;
            if ((sp3C < 3.0f) || (this->unk_AE3[this->unk_ADE] != 0)) {
                sp3C = 3.0f;
            }
            func_8083CB58(this, sp3C, this->actor.shape.rot.y);

            if (func_8083FBC4(play, this)) {
                func_800B8F98(&this->actor, (this->unk_B72 == NA_SE_PL_WALK_SNOW - SFX_FLAG)
                                                ? NA_SE_PL_ROLL_SNOW_DUST - SFX_FLAG
                                                : NA_SE_PL_ROLL_DUST - SFX_FLAG);
            }
            Player_PlayAnimSfx(this, D_8085D61C);
        }
    }
}

void func_8084C94C(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DE60);
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 0.05f);
    if (this->actor.bgCheckFlags & 1) {
        if (this->fallDistance >= 400) {
            this->actor.colChkInfo.damage = 0x10;
            func_80833B18(play, this, 1, 4.0f, 5.0f, this->actor.shape.rot.y, 20);
        } else {
            func_80836B3C(play, this, 4.0f);
        }
    }
}

void func_8084CA24(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082DB60(play, this, &gameplay_keep_Linkanim_00E3D8);
    }

    Math_SmoothStepToS(&this->unk_B86[1], 0, 6, 0x7D0, 0x190);
    if (!func_80840A30(play, this, &this->linearVelocity, 0.0f)) {
        if (this->actor.bgCheckFlags & 1) {
            if (this->unk_AAA > 0x36B0) {
                this->actor.colChkInfo.damage = 0x10;
                func_80833B18(play, this, 1, 4.0f, 5.0f, this->actor.shape.rot.y, 20);
            } else {
                func_80836B3C(play, this, 4.0f);
            }
        } else {
            this->actor.gravity = -1.0f;
            this->unk_AAA = Math_FAtan2F(this->actor.speedXZ, -this->actor.velocity.y);
            func_8082F164(this, BTN_R);
        }
    }
}

void func_8084CB58(Player* this, PlayState* play) {
    struct_8085CD30* sp3C = &D_8085CD30[this->meleeWeaponAnimation];
    f32 sp38;
    s16 sp36;

    this->stateFlags2 |= PLAYER_STATE2_20;

    if (this->transformation == PLAYER_FORM_ZORA) {
        this->actor.gravity = -0.8f;
    } else {
        this->actor.gravity = -1.2f;
    }

    LinkAnimation_Update(play, &this->skelAnime);

    if (!func_808401F4(play, this)) {
        func_8083FCF0(play, this, 6.0f, sp3C->unk_C, sp3C->unk_D);
        if (!(this->actor.bgCheckFlags & 1)) {
            func_80832F78(this, &sp38, &sp36, 0.0f, play);
            func_8083CBC4(this, sp38, this->currentYaw, 1.0f, 0.05f, 0.1f, 200);
        } else if (func_80836F10(play, this) >= 0) {
            this->meleeWeaponAnimation += 3;
            func_80833864(play, this, this->meleeWeaponAnimation);
            this->unk_ADD = 3;
            this->meleeWeaponState = 0;
            func_8082E1BC(this);
        }
    }
}

void func_8084CCEC(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;
    s32 temp_v0;

    this->stateFlags1 |= PLAYER_STATE1_1000;
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        func_8083133C(this);
        this->stateFlags1 &= ~PLAYER_STATE1_20000;
        Player_AnimationPlayLoop(play, this, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)]);
        this->unk_AE8 = -1;
    }

    func_80832F24(this);
    if (!func_8083FE38(this, play) && (this->unk_AE8 != 0)) {
        func_80840F34(this);
        if (this->unk_AE8 < 0) {
            if (this->unk_B08[0] >= 0.1f) {
                this->unk_ADD = 0;
                this->unk_AE8 = 1;
            } else if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_B)) {
                func_80840E5C(this, play);
            }
        } else if (!func_80840CD4(this, play)) {
            func_80832F78(this, &sp34, &sp32, 0.0f, play);
            temp_v0 = func_8083E7F8(this, &sp34, &sp32, play);
            if (temp_v0 > 0) {
                func_80840DEC(this, play);
            } else if (temp_v0 < 0) {
                func_80840E24(this, play);
            }
        }
    }
}

void func_8084CE84(Player* this, PlayState* play) {
    s32 var_v1;
    s32 temp_v0_2;
    f32 temp_ft4; // sp5C
    f32 var_fa0;  // sp58
    f32 sp54;
    s16 sp52;
    s16 temp_v0;
    f32 temp_fv1;
    s32 pad;
    s32 sp44;

    temp_v0 = this->currentYaw - this->actor.shape.rot.y;
    var_v1 = ABS_ALT(temp_v0);

    temp_ft4 = fabsf(this->linearVelocity);
    this->stateFlags1 |= 0x1000;

    var_fa0 = temp_ft4 * 1.5f;
    var_fa0 = CLAMP_MIN(var_fa0, 1.5f);

    var_fa0 = ((var_v1 < 0x4000) ? -1.0f : 1.0f) * var_fa0;

    func_8083EA44(this, var_fa0);

    var_fa0 = CLAMP(temp_ft4 * 0.5f, 0.5f, 1.0f);

    LinkAnimation_BlendToJoint(play, &this->skelAnime, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)], 0.0f,
                               D_8085CF70[Player_IsHoldingTwoHandedWeapon(this)], this->unk_B38 * 0.7241379f, var_fa0,
                               this->blendTableBuffer);
    if (!func_8083FE38(this, play) && !func_80840CD4(this, play)) {
        func_80840F34(this);
        func_80832F78(this, &sp54, &sp52, 0.0f, play);

        temp_v0_2 = func_8083E7F8(this, &sp54, &sp52, play);
        if (temp_v0_2 < 0) {
            func_80840E24(this, play);
            return;
        }

        if (temp_v0_2 == 0) {
            sp54 = 0.0f;
            sp52 = this->currentYaw;
        }

        sp44 = ABS_ALT(BINANG_SUB(sp52, this->currentYaw));
        if (sp44 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
                this->currentYaw = sp52;
            }
        } else {
            Math_AsymStepToF(&this->linearVelocity, sp54 * 0.2f, 1.0f, 0.5f);
            Math_ScaledStepToS(&this->currentYaw, sp52, sp44 * 0.1f);
            if ((sp54 == 0.0f) && (this->linearVelocity == 0.0f)) {
                func_80840EC0(this, play);
            }
        }
    }
}

#ifdef NON_MATCHING
// stack
void func_8084D18C(Player* this, PlayState* play) {
    f32 sp5C;
    s16 temp_v0_2;
    f32 sp54;
    s16 sp52;
    f32 var_fa0;
    s32 temp_v0;
    s32 var_v1; // sp44

    sp5C = fabsf(this->linearVelocity);
    this->stateFlags1 |= PLAYER_STATE1_1000;
    if (sp5C == 0.0f) {
        sp5C = ABS_ALT(this->unk_B4C) * 0.0015f;
        if (sp5C < 400.0f) {
            sp5C = 0.0f;
        }

        func_8083EA44(this, ((this->unk_B4C >= 0) ? 1 : -1) * sp5C);
    } else {
        var_fa0 = sp5C * 1.5f;
        var_fa0 = CLAMP_MIN(var_fa0, 1.5f);
        func_8083EA44(this, var_fa0);
    }

    var_fa0 = CLAMP(sp5C * 0.5f, 0.5f, 1.0f);

    LinkAnimation_BlendToJoint(play, &this->skelAnime, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)], 0.0f,
                               D_8085CF78[Player_IsHoldingTwoHandedWeapon(this)], this->unk_B38 * 0.7241379f, var_fa0,
                               this->blendTableBuffer);
    if (!func_8083FE38(this, play) && !func_80840CD4(this, play)) {
        func_80840F34(this);
        func_80832F78(this, &sp54, &sp52, 0.0f, play);
        temp_v0 = func_8083E7F8(this, &sp54, &sp52, play);
        if (temp_v0 > 0) {
            func_80840DEC(this, play);
            return;
        }

        if (temp_v0 == 0) {
            sp54 = 0.0f;
            sp52 = this->currentYaw;
        }

        temp_v0_2 = sp52 - this->currentYaw;
        var_v1 = ABS_ALT(temp_v0_2);
        if (var_v1 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f) != 0) {
                this->currentYaw = sp52;
            }
        } else {
            Math_AsymStepToF(&this->linearVelocity, sp54 * 0.2f, 1.0f, 0.5f);
            Math_ScaledStepToS(&this->currentYaw, sp52, var_v1 * 0.1f);
            if ((sp54 == 0.0f) && (this->linearVelocity == 0.0f) && (sp5C == 0.0f)) {
                func_80840EC0(this, play);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D18C.s")
#endif

void func_8084D4EC(Player* this, PlayState* play) {
    s32 animFinished;
    f32 frame;
    s32 temp_v0;

    this->stateFlags2 |= PLAYER_STATE2_20;
    animFinished = LinkAnimation_Update(play, &this->skelAnime);

    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DA70) {
        this->linearVelocity = 1.0f;
        if (LinkAnimation_OnFrame(&this->skelAnime, 8.0f)) {
            f32 var_fv0 = this->wallHeight;

            var_fv0 = CLAMP_MAX(var_fv0, this->ageProperties->unk_0C);
            if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                var_fv0 *= 0.085f;
            } else {
                var_fv0 *= 0.072f;
            }
            if (this->transformation == PLAYER_FORM_HUMAN) {
                var_fv0 += 1.0f;
            }
            func_80834D50(play, this, NULL, var_fv0, NA_SE_VO_LI_AUTO_JUMP);
            this->unk_AE8 = -1;
        }
    } else {
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
        if (temp_v0 == 0) {
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_4000 | PLAYER_STATE1_40000);
            return;
        }
        if (animFinished || (temp_v0 > 0)) {
            func_80839E74(this, play);
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_4000 | PLAYER_STATE1_40000);
            this->unk_ABC = 0.0f;
            return;
        }

        frame = 0.0f;
        if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DFC8) {
            if (LinkAnimation_OnFrame(&this->skelAnime, 30.0f)) {
                func_8083B32C(play, this, 10.0f);
            }
            frame = 50.0f;
        } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DA68) {
            frame = 30.0f;
        } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DA60) {
            frame = 16.0f;
        }

        if (LinkAnimation_OnFrame(&this->skelAnime, frame)) {
            func_8082E1BC(this);
            func_8082DF8C(this, NA_SE_VO_LI_CLIMB_END);
        }

        if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00DA60) || (this->skelAnime.curFrame > 5.0f)) {
            if (this->unk_AE8 == 0) {
                func_8082E188(this);
                this->unk_AE8 = 1;
            }
            Math_SmoothStepToF(&this->unk_ABC, 0.0f, 0.1f, 400.0f, 150.0f);
        }
    }
}

void func_8084D770(Player* this, PlayState* play) {
    s32 temp_v0;

    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    if (this->unk_D58 == func_80837BF8) {
        this->stateFlags2 |= PLAYER_STATE2_1;
    }

    LinkAnimation_Update(play, &this->skelAnime);
    func_8083249C(this);

    temp_v0 = func_8083216C(this, play);
    if (((this->stateFlags1 & PLAYER_STATE1_800) && (this->heldActor != NULL) && (this->getItemId == GI_NONE)) ||
        (temp_v0 == 0)) {
        this->unk_D58(play, this);
    }
}

void func_8084D820(Player* this, PlayState* play) {
    if (func_80838A90(this, play) == 0) {
        if ((this->stateFlags3 & 0x10) && !(this->actor.bgCheckFlags & 1)) {
            func_80833AA0(this, play);
            this->stateFlags1 |= 0x20000000;
        } else if (this->unk_AE8 == 0) {
            LinkAnimation_Update(play, &this->skelAnime);
            if (DECR(this->doorTimer) == 0) {
                this->linearVelocity = 0.1f;
                this->unk_AE8 = 1;
            }
        } else if (this->unk_AE7 == 0) {
            f32 sp6C;
            s32 var_t0; // sp68

            sp6C = 5.0f * D_8085C3E4;
            var_t0 = func_808411D4(play, this, &sp6C, -1);
            if (this->unk_397 == 4) {
                if (MREG(64) < 0) {
                    if (play->roomCtx.unk31 != 1) {
                        MREG(68) += MREG(64);
                        if (MREG(68) < 0) {
                            MREG(68) = 0;
                        }

                        this->actor.world.pos.y += (this->doorDirection != 0) ? 3.0f : -3.0f;
                        this->actor.prevPos.y = this->actor.world.pos.y;
                    }
                } else if (MREG(64) == 0) {
                    CollisionPoly* sp64;
                    s32 sp60;

                    if (func_80835DF8(play, this, &sp64, &sp60) != 0) {
                        this->actor.floorPoly = sp64;
                        this->actor.floorBgId = sp60;
                    }
                }
            }

            if (var_t0 < 0x1E) {
                this->unk_AE7 = 1;
                this->stateFlags1 |= 0x20000000;
                this->unk_3A0.x = this->unk_3AC.x;
                this->unk_3A0.z = this->unk_3AC.z;
            }
        } else {
            f32 sp5C;
            s32 sp58;
            s32 temp_v0_8;

            sp58 = 0x14;
            sp5C = 5.0f;
            if (this->stateFlags1 & 1) {
                sp5C = gSaveContext.entranceSpeed;
                if (D_80862B10 != 0) {
                    this->unk_3A0.x = (Math_SinS(D_80862B16) * 400.0f) + this->actor.world.pos.x;
                    this->unk_3A0.z = (Math_CosS(D_80862B16) * 400.0f) + this->actor.world.pos.z;
                }
            } else {
                if (this->unk_AE8 < 0) {
                    this->unk_AE8++;
                    sp5C = gSaveContext.entranceSpeed;
                    sp58 = -1;
                } else if (this->unk_397 == 4) {
                    if (MREG(64) == 0) {
                        MREG(64) = 0x10;
                        MREG(68) = 0;

                        MREG(65) = MREG(66) = MREG(67) = MREG(68);
                    } else if (MREG(64) >= 0) {
                        MREG(68) += MREG(64);
                        if (MREG(68) >= 0x100) {
                            TransitionActorEntry* temp_v1_4; // sp50
                            s32 roomNum;

                            temp_v1_4 = &play->doorCtx.transitionActorList[this->doorNext];
                            roomNum = temp_v1_4->sides[0].room;
                            MREG(68) = 0xFF;

                            if ((roomNum != play->roomCtx.currRoom.num) && (play->roomCtx.currRoom.num >= 0)) {
                                play->roomCtx.prevRoom = play->roomCtx.currRoom;

                                play->roomCtx.currRoom.num = -1;
                                play->roomCtx.currRoom.segment = NULL;
                                func_8012EBF8(play, &play->roomCtx);
                            } else {
                                static Vec3f D_8085D62C = { 0.0f, 0.0f, 0.0f };
                                static Vec3f D_8085D638 = { 0.0f, 0.0f, 0.0f };
                                static Vec3f D_8085D644 = { 0.0f, 0.0f, 0.0f };

                                MREG(64) = -0x10;
                                if (play->roomCtx.currRoom.num < 0) {
                                    Room_StartRoomTransition(play, &play->roomCtx, temp_v1_4->sides[0].room);
                                    play->roomCtx.prevRoom.num = -1;
                                    play->roomCtx.prevRoom.segment = NULL;
                                }

                                this->actor.world.pos.x = temp_v1_4->pos.x;
                                this->actor.world.pos.y = temp_v1_4->pos.y;
                                this->actor.world.pos.z = temp_v1_4->pos.z;

                                this->actor.shape.rot.y = ((((temp_v1_4->rotY >> 7) & 0x1FF) / 180.0f) * 0x8000);

                                D_8085D62C.x = (this->doorDirection != 0) ? -120.0f : 120.0f;
                                D_8085D62C.y = (this->doorDirection != 0) ? -75.0f : 75.0f;
                                D_8085D62C.z = -240.0f;
                                if (this->doorDirection != 0) {
                                    Camera_ChangeDoorCam(play->cameraPtrs[0], &this->actor, -2, 0.0f,
                                                         temp_v1_4->pos.x + 0x32, temp_v1_4->pos.y + 0x5F,
                                                         temp_v1_4->pos.z - 0x32);
                                } else {
                                    Camera_ChangeDoorCam(play->cameraPtrs[0], &this->actor, -2, 0.0f,
                                                         temp_v1_4->pos.x - 0x32, temp_v1_4->pos.y + 5,
                                                         temp_v1_4->pos.z - 0x32);
                                }

                                func_80835BC8(this, &this->actor.world.pos, &D_8085D62C, &this->actor.world.pos);

                                D_8085D638.x = (this->doorDirection != 0) ? 130.0f : -130.0f;
                                D_8085D638.z = 160.0f;
                                func_80835BC8(this, &this->actor.world.pos, &D_8085D638, &this->unk_3A0);
                                D_8085D644.z = 160.0f;
                                func_80835BC8(this, &this->unk_3A0, &D_8085D644, &this->unk_3AC);

                                this->actor.shape.rot.y += (this->doorDirection != 0) ? 0x4000 : -0x4000;
                                this->unk_AE7 = 0;

                                this->actor.world.rot.y = this->currentYaw = this->actor.shape.rot.y;
                            }
                        }

                        this->actor.world.pos.y += (this->doorDirection != 0) ? 3.0f : -3.0f;
                        this->actor.prevPos.y = this->actor.world.pos.y;
                    }
                }
            }

            temp_v0_8 = func_808411D4(play, this, &sp5C, sp58);
            if ((this->unk_AE8 == 0) ||
                ((temp_v0_8 == 0) && (this->linearVelocity == 0.0f) && (Play_GetCamera(play, 0)->stateFlags & 0x10))) {
                if (this->unk_397 == 4) {
                    Map_InitRoomData(play, (s16)play->roomCtx.currRoom.num);
                    Minimap_SavePlayerRoomInitInfo(play);
                }

                MREG(64) = 0;
                func_800E0238(Play_GetCamera(play, 0));
                func_80838760(this);
                if (!(this->stateFlags3 & 0x20000)) {
                    func_801226E0(play, ((void)0, gSaveContext.respawn[RESPAWN_MODE_DOWN].data));
                }

                if (play->unk_1887C != 0) {
                    play->func_18780(this, play);
                    Player_SetAction(play, this, func_80854430, 0);
                    if (play->sceneNum == 0x45) {
                        play->unk_1887C = 0;
                    }
                } else if (!func_808391D8(this, play)) {
                    func_8083B2E4(this, play);
                }
            }
        }
    }

    if (this->stateFlags1 & 0x800) {
        func_8083216C(this, play);
    }
}

// door stuff
void func_8084E034(Player* this, PlayState* play) {
    Actor* doorActor = this->doorActor;
    s32 sp38;
    s32 animFinished;
    CollisionPoly* poly;
    s32 bgId;

    //! @bug Incorrect struct access: `doorActor` can be either a `EnDoor` (correct access), `EnDoorEtc` (reads `angle`
    //! as a s16 instead of a u8) or a `DoorShutter` (OoB read)
    sp38 = (doorActor != NULL) && (((EnDoor*)doorActor)->unk_1A4 == 7);
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (DECR(this->unk_AE7) == 0) {
        func_80835DF8(play, this, &poly, &bgId);
    }

    animFinished = LinkAnimation_Update(play, &this->skelAnime);
    func_8083216C(this, play);

    if (animFinished) {
        if (this->unk_AE8 == 0) {
            if (DECR(this->doorTimer) == 0) {
                this->unk_AE8 = 1;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }
        } else {
            func_80838760(this);
            func_80839E74(this, play);

            if ((this->actor.category == ACTORCAT_PLAYER) && !sp38) {
                if (play->roomCtx.prevRoom.num >= 0) {
                    func_8012EBF8(play, &play->roomCtx);
                }

                func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
                Play_SetupRespawnPoint(&play->state, RESPAWN_MODE_DOWN, PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B));
            }
        }
    } else if (!(this->stateFlags1 & PLAYER_STATE1_20000000) && LinkAnimation_OnFrame(&this->skelAnime, 15.0f)) {
        func_80838760(this);
        play->func_18780(this, play);
    } else if (sp38 && LinkAnimation_OnFrame(&this->skelAnime, 15.0f)) {
        s16 doorRot = (this->doorDirection < 0) ? doorActor->world.rot.x : doorActor->world.rot.z;

        if (doorRot != 0) {
            func_808354A4(play, doorRot - 1, false);
        }
    }
}

// grab/hold an actor (?)
void func_8084E25C(Player* this, PlayState* play) {
    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
        func_808313F0(this, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor* interactRangeActor;

        interactRangeActor = this->interactRangeActor;
        if (!func_808313A8(play, this, interactRangeActor)) {
            this->actor.child = interactRangeActor;
            this->heldActor = interactRangeActor;
            interactRangeActor->parent = &this->actor;
            interactRangeActor->bgCheckFlags &= ~0xFF;
            this->leftHandWorld.rot.y = interactRangeActor->shape.rot.y - this->actor.shape.rot.y;
        }
    } else {
        Math_ScaledStepToS(&this->leftHandWorld.rot.y, 0, 0xFA0);
    }
}

// grab/hold an actor (?) What's the difference with func_8084E25C ?
void func_8084E334(Player* this, PlayState* play) {
    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DFA0);
        this->unk_AE8 = 1;
    } else if (this->unk_AE8 == 0) {
        if (LinkAnimation_OnFrame(&this->skelAnime, 27.0f)) {
            Actor* interactRangeActor = this->interactRangeActor;

            this->heldActor = interactRangeActor;
            this->actor.child = interactRangeActor;
            interactRangeActor->parent = &this->actor;
        } else if (LinkAnimation_OnFrame(&this->skelAnime, 25.0f)) {
            func_8082DF8C(this, NA_SE_VO_LI_SWORD_L);
        }
    } else if (CHECK_BTN_ANY(D_80862B44->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
        Player_SetAction(play, this, func_8084E434, 1);
        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DF98);
    }
}

// throw held actor (?)
void func_8084E434(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor* heldActor = this->heldActor;

        heldActor->world.rot.y = this->actor.shape.rot.y;
        heldActor->speedXZ = 10.0f;
        heldActor->velocity.y = 20.0f;
        func_808309CC(play, this);
        func_800B8E58(this, NA_SE_PL_THROW);
        func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
    }
}

void func_8084E4E4(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DD80);
        this->unk_AE8 = 0xF;
    } else if (this->unk_AE8 != 0) {
        this->unk_AE8--;
        if (this->unk_AE8 == 0) {
            func_80836A98(this, &gameplay_keep_Linkanim_00DD78, play);
            this->stateFlags1 &= ~PLAYER_STATE1_800;
            func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);
        }
    }
}

void func_8084E58C(Player* this, PlayState* play) {
    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor* heldActor = this->heldActor;

        if (!func_808313A8(play, this, heldActor)) {
            heldActor->velocity.y = 0.0f;
            heldActor->speedXZ = 0.0f;
            func_808309CC(play, this);
            if (heldActor->id == ACTOR_EN_BOM_CHU) {
                func_80831814(this, play, 0);
            }
        }
    }
}

void func_8084E65C(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;

    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime) ||
        ((this->skelAnime.curFrame >= 8.0f) && func_80832F78(this, &sp34, &sp32, 0.018f, play))) {
        func_80836988(this, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 3.0f)) {
        func_808409A8(play, this, this->linearVelocity + 8.0f, 12.0f);
    }
}

void func_8084E724(Player* this, PlayState* play) {
    u8 temp_v1;
    unsigned int new_var;

    if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_808475B4(this);
        func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
    } else {
        func_80832F24(this);
    }

    if (this->unk_AA5 == 3) {
        if (func_800B7118(this) || func_8082ECCC(this)) {
            func_8083216C(this, play);
        }
    }

    temp_v1 = this->unk_AA5;
    new_var = temp_v1;

    if (((temp_v1 == 2) && (!(play->actorCtx.unk5 & 4))) ||
        ((temp_v1 != 2) &&
         (((((((((this->csMode != PLAYER_CSMODE_0) || (new_var == 0)) || (((s32)temp_v1) >= 5)) ||
               (func_8082FB68(this) != 0)) ||
              (this->targetedActor != NULL)) ||
             (func_8083868C(play, this) == 0)) ||
            ((this->unk_AA5 == 3) &&
             (((((Player_ItemToActionParam(this, Inventory_GetBtnBItem(play)) != this->itemActionParam) &&
                 CHECK_BTN_ANY(D_80862B44->press.button, BTN_B)) ||
                CHECK_BTN_ANY(D_80862B44->press.button, BTN_R | BTN_A)) ||
               (func_80123434(this) != 0)) ||
              (!func_800B7128(this) && (func_8082EF20(this) == 0))))) ||
           ((this->unk_AA5 == 1) && CHECK_BTN_ANY(D_80862B44->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN |
                                                                                BTN_CUP | BTN_R | BTN_B | BTN_A))) ||
          func_808391D8(this, play)))) {
        func_80839ED0(this, play);
        play_sound(NA_SE_SY_CAMERA_ZOOM_UP);
    } else if ((DECR(this->unk_AE8) == 0) || (this->unk_AA5 != 3)) {
        if (func_801240DC(this)) {
            this->unk_AA6 |= 0x43;
        } else {
            this->actor.shape.rot.y = func_80847190(play, this, 0);
        }
    }

    this->currentYaw = this->actor.shape.rot.y;
}

void func_8084E980(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8083249C(this);
    func_8083216C(this, play);
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        this->actor.flags &= ~ACTOR_FLAG_100;
        if (!CHECK_FLAG_ALL(this->talkActor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_4)) {
            this->stateFlags2 &= ~PLAYER_STATE2_2000;
        }

        func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
        ActorCutscene_Stop(0x7C);
        if (this->stateFlags1 & PLAYER_STATE1_800000) {
            s32 sp44 = this->unk_AE8;

            func_80837BD0(play, this);
            this->unk_AE8 = sp44;
        } else if (!func_80847994(play, this) && !func_80847880(play, this) && !func_808387A0(play, this) &&
                   ((this->talkActor != this->interactRangeActor) || !func_8083D23C(this, play))) {
            if (func_801242B4(this)) {
                func_808353DC(play, this);
            } else {
                func_8085B384(this, play);
            }
        }

        this->unk_B5E = 0xA;
        return;
    }

    if (this->stateFlags1 & PLAYER_STATE1_800000) {
        func_8084FE7C(this, play);
    } else if (func_801242B4(this)) {
        func_808508C8(this, play);
        if (this->actor.depthInWater > 100.0f) {
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
        }
    } else if (!func_80123420(this) && LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->skelAnime.moveFlags != 0) {
            func_8082E794(this);
            if ((this->talkActor->category == ACTORCAT_NPC) && (this->itemActionParam != PLAYER_AP_FISHING_POLE)) {
                func_8082DB90(play, this, &gameplay_keep_Linkanim_00DEA0);
            } else {
                Player_AnimationPlayLoop(play, this, func_8082ED20(this));
            }
        } else {
            func_8082DB60(play, this, &gameplay_keep_Linkanim_00DEA8);
        }
    }

    if (this->targetedActor != NULL) {
        this->currentYaw = func_8083C62C(this, false);
        this->actor.shape.rot.y = this->currentYaw;
        if (this->unk_AE7 != 0) {
            if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                if (LinkAnimation_Update(play, &this->unk_284)) {
                    this->unk_AE7 -= 1;
                    if (this->unk_AE7 != 0) {
                        LinkAnimation_Change(play, &this->unk_284, &gameplay_keep_Linkanim_00DEA0, 1.0f, 0.0f,
                                             Animation_GetLastFrame(&gameplay_keep_Linkanim_00DEA0), ANIMMODE_ONCE,
                                             -6.0f);
                    }
                }
            }
            AnimationContext_SetCopyFalse(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                          this->unk_284.jointTable, D_8085B9F0);
        } else if (!(this->stateFlags1 & PLAYER_STATE1_800) &&
                   (this->skelAnime.animation == &gameplay_keep_Linkanim_00DEA8)) {
            s32 temp_v0 = this->actor.focus.rot.y - this->actor.shape.rot.y;

            if (ABS_ALT(temp_v0) > 0xFA0) {
                LinkAnimation_Change(play, &this->unk_284, D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType], 0.4f,
                                     0.0f, Animation_GetLastFrame(D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType]),
                                     ANIMMODE_ONCE, -6.0f);
                this->unk_AE7 = 2;
            }
        }
    }
}

void func_8084ED9C(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;
    s32 temp_v0;

    this->stateFlags2 |= (PLAYER_STATE2_1 | PLAYER_STATE2_40 | PLAYER_STATE2_100);
    func_8083DEE4(play, this);

    if (LinkAnimation_Update(play, &this->skelAnime) && !func_8083E14C(play, this)) {
        func_80832F78(this, &sp34, &sp32, 0.0f, play);
        temp_v0 = func_8083E758(this, &sp34, &sp32);
        if (temp_v0 > 0) {
            func_8083E234(this, play);
        } else if (temp_v0 < 0) {
            func_8083E28C(this, play);
        }
    }
}

AnimSfxEntry D_8085D650[] = {
    ANIMSFX(ANIMSFX_TYPE_2, 3, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_2, 21, NA_SE_PL_SLIP, STOP),
};

void func_8084EE50(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE1_1 | PLAYER_STATE1_40 | PLAYER_STATE1_100);

    if (func_8082E67C(play, this, &gameplay_keep_Linkanim_00DE10)) {
        this->unk_AE8 = 1;
    } else if ((this->unk_AE8 == 0) && LinkAnimation_OnFrame(&this->skelAnime, 11.0f)) {
        func_8082DF8C(this, NA_SE_VO_LI_PUSH);
    }

    Player_PlayAnimSfx(this, D_8085D650);
    func_8083DEE4(play, this);

    if (!func_8083E14C(play, this)) {
        f32 sp34;
        s16 sp32;
        s32 temp_v0;

        func_80832F78(this, &sp34, &sp32, 0.0f, play);
        temp_v0 = func_8083E758(this, &sp34, &sp32);
        if (temp_v0 < 0) {
            func_8083E28C(this, play);
        } else if (temp_v0 == 0) {
            func_8083DF38(this, &gameplay_keep_Linkanim_00DDF0, play);
        } else {
            this->stateFlags2 |= PLAYER_STATE2_10;
        }
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        func_808479F4(play, this, 2.0f);
        this->linearVelocity = 2.0f;
    }
}

AnimSfxEntry D_8085D658[] = {
    ANIMSFX(ANIMSFX_TYPE_2, 4, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_2, 24, NA_SE_PL_SLIP, STOP),
};

Vec3f D_8085D660 = { 0.0f, 26.800001f, -60.0f };

void func_8084EF9C(Player* this, PlayState* play) {
    LinkAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_35][this->modelAnimType];

    this->stateFlags2 |= (PLAYER_STATE1_1 | PLAYER_STATE1_40 | PLAYER_STATE1_100);

    if (func_8082E67C(play, this, anim)) {
        this->unk_AE8 = 1;
    } else if (this->unk_AE8 == 0) {
        if (LinkAnimation_OnFrame(&this->skelAnime, 11.0f)) {
            func_8082DF8C(this, NA_SE_VO_LI_PUSH);
        }
        if (0) {}
    } else {
        Player_PlayAnimSfx(this, D_8085D658);
    }

    func_8083DEE4(play, this);
    if (!func_8083E14C(play, this)) {
        f32 sp78;
        s16 sp76;
        s32 temp_v0;

        func_80832F78(this, &sp78, &sp76, 0.0f, play);

        temp_v0 = func_8083E758(this, &sp78, &sp76);
        if (temp_v0 > 0) {
            func_8083E234(this, play);
        } else if (temp_v0 == 0) {
            func_8083DF38(this, D_8085BE84[PLAYER_ANIMGROUP_36][this->modelAnimType], play);
        } else {
            this->stateFlags2 |= PLAYER_STATE2_10;
        }
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        Vec3f sp64;
        f32 yIntersect;
        CollisionPoly* poly;
        s32 bgId;
        Vec3f sp4C;
        Vec3f sp40;

        yIntersect = func_80835D2C(play, this, &D_8085D660, &sp64) - this->actor.world.pos.y;
        if (fabsf(yIntersect) < 26.800001f) {
            sp64.y -= 7.0f;
            sp4C.x = this->actor.world.pos.x;
            sp4C.z = this->actor.world.pos.z;
            sp4C.y = sp64.y;
            if (!BgCheck_EntityLineTest2(&play->colCtx, &sp4C, &sp64, &sp40, &poly, 1, 0, 0, 1, &bgId, &this->actor)) {
                func_808479F4(play, this, -2.0f);
                return;
            }
        }
        this->stateFlags2 &= ~PLAYER_STATE2_10;
    }
}

void func_8084F1B8(Player* this, PlayState* play) {
    f32 sp3C;
    s16 sp3A;

    this->stateFlags2 |= PLAYER_STATE2_40;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this,
                                 (this->unk_AE7 > 0) ? &gameplay_keep_Linkanim_00DC48
                                                     : D_8085BE84[PLAYER_ANIMGROUP_39][this->modelAnimType]);
    } else if (this->unk_AE7 == 0) {
        f32 frame;

        if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DC30) {
            frame = 11.0f;
        } else {
            frame = 1.0f;
        }

        if (LinkAnimation_OnFrame(&this->skelAnime, frame)) {
            func_8082E094(this, NA_SE_PL_WALK_GROUND);
            if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DC30) {
                this->unk_AE7 = 1;
            } else {
                this->unk_AE7 = -1;
            }
        }
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->currentYaw, 0x800);
    if (this->unk_AE7 != 0) {
        func_80832F78(this, &sp3C, &sp3A, 0.0f, play);
        if (this->unk_ADF[this->unk_ADE] >= 0) {
            func_808381A0(this,
                          (this->unk_AE7 > 0) ? D_8085BE84[PLAYER_ANIMGROUP_37][this->modelAnimType]
                                              : D_8085BE84[PLAYER_ANIMGROUP_40][this->modelAnimType],
                          play);
        } else if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A) || (this->actor.shape.feetFloorFlags != 0)) {
            func_80833A64(this);

            if (this->unk_AE7 < 0) {
                this->linearVelocity = -0.8f;
            } else {
                this->linearVelocity = 0.8f;
            }

            func_80833AA0(this, play);
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000);
            this->actor.bgCheckFlags &= ~1;
        }
    }
}

void func_8084F3DC(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        this->currentYaw = this->skelAnime.jointTable[1].y + this->actor.shape.rot.y;
        func_8082E820(this, 1);
        this->actor.shape.rot.y = this->currentYaw;
        func_80839E74(this, play);
        this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, this->skelAnime.endFrame - 6.0f)) {
        func_8082E1BC(this);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, this->skelAnime.endFrame - 34.0f)) {
        func_800B8E58(this, NA_SE_PL_CLIMB_CLIFF);
        func_8082DF8C(this, NA_SE_VO_LI_CLIMB_END);
        func_8084C124(play, this);
    }
}

void func_8084F4E8(Player* this, PlayState* play) {
    s32 yStick = D_80862B44->rel.stick_y;
    s32 xStick = D_80862B44->rel.stick_x;
    f32 var_fv0;
    f32 var_fv1;
    Vec3f sp7C;
    s32 sp78;
    Vec3f sp6C;
    Vec3f sp60;
    DynaPolyActor* dyna;
    LinkAnimationHeader* anim1;
    LinkAnimationHeader* anim2;

    this->fallStartHeight = this->actor.world.pos.y;

    this->stateFlags2 |= PLAYER_STATE2_40;

    if ((this->unk_AE7 != 0) && (ABS_ALT(yStick) < ABS_ALT(xStick))) {
        var_fv0 = ABS_ALT(xStick) * 0.0325f;
        yStick = 0;
    } else {
        var_fv0 = ABS_ALT(yStick) * 0.05f;
        xStick = 0;
    }

    if (var_fv0 < 1.0f) {
        var_fv0 = 1.0f;
    } else if (var_fv0 > 3.35f) {
        var_fv0 = 3.35f;
    }

    if (this->skelAnime.playSpeed >= 0.0f) {
        var_fv1 = 1.0f;
    } else {
        var_fv1 = -1.0f;
    }

    this->skelAnime.playSpeed = var_fv1 * var_fv0;

    if (this->unk_AE8 >= 0) {

        if ((this->actor.wallPoly != NULL) && (this->actor.wallBgId != BGCHECK_SCENE)) {
            dyna = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

            if (dyna != NULL) {
                Math_Vec3f_Diff(&dyna->actor.world.pos, &dyna->actor.prevPos, &sp7C);
                Math_Vec3f_Sum(&this->actor.world.pos, &sp7C, &this->actor.world.pos);
            }
        }

        Actor_UpdateBgCheckInfo(play, &this->actor, 26.800001f, 6.0f, this->ageProperties->unk_00 + 15.0f, 7);
        func_8083DD1C(play, this, 26.800001f, this->ageProperties->unk_3C, 50.0f, -20.0f);
    }

    func_80831944(play, this);

    if ((this->unk_AE8 < 0) || !func_8083E354(this, play)) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            if (this->unk_AE8 < 0) {
                this->unk_AE8 = ABS_ALT(this->unk_AE8) & 1;
            } else if (yStick != 0) {
                f32 yIntersect;

                sp78 = this->unk_AE7 + this->unk_AE8;

                if (yStick > 0) {
                    sp6C.x = 0.0f;
                    sp6C.y = this->ageProperties->unk_40;
                    sp6C.z = this->ageProperties->unk_3C + 10.0f;

                    yIntersect = func_80835D2C(play, this, &sp6C, &sp60);

                    if (this->actor.world.pos.y < yIntersect) {
                        if (this->unk_AE7 != 0) {
                            this->actor.world.pos.y = yIntersect;
                            this->stateFlags1 &= ~PLAYER_STATE1_200000;
                            func_80837CEC(play, this, this->actor.wallPoly, this->ageProperties->unk_3C,
                                          &gameplay_keep_Linkanim_00DCF8);
                            this->currentYaw += 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            func_808381A0(this, &gameplay_keep_Linkanim_00DCF8, play);
                            this->stateFlags1 |= PLAYER_STATE1_4000;
                        } else {
                            func_8083DCC4(this, this->ageProperties->unk_D4[this->unk_AE8], play);
                        }
                    } else {
                        this->skelAnime.prevTransl = this->ageProperties->unk_4A[sp78];
                        Player_AnimationPlayOnce(play, this, this->ageProperties->unk_B4[sp78]);
                    }
                } else if ((this->actor.world.pos.y - this->actor.floorHeight) < 15.0f) {
                    if (this->unk_AE7 != 0) {
                        func_8083E2F4(this, play);
                    } else {
                        if (this->unk_AE8 != 0) {
                            this->skelAnime.prevTransl = this->ageProperties->unk_44;
                        }

                        func_8083DCC4(this, this->ageProperties->unk_CC[this->unk_AE8], play);
                        this->unk_AE8 = 1;
                    }
                } else {
                    sp78 ^= 1;
                    this->skelAnime.prevTransl = this->ageProperties->unk_62[sp78];
                    anim1 = this->ageProperties->unk_B4[sp78];
                    LinkAnimation_Change(play, &this->skelAnime, anim1, -1.0f, Animation_GetLastFrame(anim1), 0.0f, 2,
                                         0.0f);
                }

                this->unk_AE8 ^= 1;
            } else if ((this->unk_AE7 != 0) && (xStick != 0)) {
                anim2 = this->ageProperties->unk_C4[this->unk_AE8];

                if (xStick > 0) {
                    this->skelAnime.prevTransl = this->ageProperties->unk_7A[this->unk_AE8];
                    Player_AnimationPlayOnce(play, this, anim2);
                } else {
                    this->skelAnime.prevTransl = this->ageProperties->unk_7A[this->unk_AE8 + 2];
                    LinkAnimation_Change(play, &this->skelAnime, anim2, -1.0f, Animation_GetLastFrame(anim2), 0.0f, 2,
                                         0.0f);
                }
            } else {
                this->stateFlags2 |= PLAYER_STATE2_1000;
            }

            return;
        }
    }

    if (this->unk_AE8 < 0) {
        if (((this->unk_AE8 == -2) &&
             (LinkAnimation_OnFrame(&this->skelAnime, 14.0f) || LinkAnimation_OnFrame(&this->skelAnime, 29.0f))) ||
            ((this->unk_AE8 == -4) &&
             (LinkAnimation_OnFrame(&this->skelAnime, 22.0f) || LinkAnimation_OnFrame(&this->skelAnime, 35.0f) ||
              LinkAnimation_OnFrame(&this->skelAnime, 49.0f) || LinkAnimation_OnFrame(&this->skelAnime, 55.0f)))) {
            func_80847A50(this);
        }
    } else if (LinkAnimation_OnFrame(&this->skelAnime, (this->skelAnime.playSpeed > 0.0f) ? 20.0f : 0.0f)) {
        func_80847A50(this);
    }
}

f32 D_8085D66C[] = { 11.0f, 21.0f };
f32 D_8085D674[] = { 40.0f, 50.0f };

AnimSfxEntry D_8085D67C[] = {
    ANIMSFX(ANIMSFX_TYPE_10, 10, NA_SE_PL_WALK_LADDER, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_10, 20, NA_SE_PL_WALK_LADDER, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_10, 30, NA_SE_PL_WALK_LADDER, STOP),
};

void func_8084FC0C(Player* this, PlayState* play) {
    s32 temp_v0;

    this->stateFlags2 |= PLAYER_STATE2_40;

    temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
    if (temp_v0 == 0) {
        this->stateFlags1 &= ~PLAYER_STATE1_200000;
    } else if ((temp_v0 > 0) || LinkAnimation_Update(play, &this->skelAnime)) {
        func_80839E74(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_200000;
    } else {
        f32* var_v1 = D_8085D66C;

        if (this->unk_AE8 != 0) {
            Player_PlayAnimSfx(this, D_8085D67C);
            var_v1 = D_8085D674;
        }

        if (LinkAnimation_OnFrame(&this->skelAnime, var_v1[0]) || LinkAnimation_OnFrame(&this->skelAnime, var_v1[1])) {
            CollisionPoly* poly;
            s32 bgId;
            Vec3f pos;

            pos.x = this->actor.world.pos.x;
            pos.y = this->actor.world.pos.y + 20.0f;
            pos.z = this->actor.world.pos.z;
            if (BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &pos) != 0.0f) {
                this->unk_B72 = SurfaceType_GetSfx(&play->colCtx, poly, bgId);
                func_8082E1BC(this);
            }
        }
    }
}

void func_8084FD7C(PlayState* play, Player* this, Actor* actor) {
    s16 var_a3;

    if (this->unk_B86[0] != 0) {
        this->unk_B86[0]--;
        return;
    }

    this->unk_AB2.y = func_80847190(play, this, 1) - this->actor.shape.rot.y;

    var_a3 = ABS_ALT(this->unk_AB2.y) - 0x4000;
    if (var_a3 > 0) {
        var_a3 = CLAMP_MAX(var_a3, 0x15E);
        actor->shape.rot.y += var_a3 * ((this->unk_AB2.y >= 0) ? 1 : -1);
        actor->world.rot.y = actor->shape.rot.y;
    }

    this->unk_AB2.y += 0x2710;
    this->unk_AA8 = -0x1388;
}

s32 func_8084FE48(Player* this) {
    return this->targetedActor == NULL && !func_8082FC24(this);
}

LinkAnimationHeader* D_8085D688[] = {
    &gameplay_keep_Linkanim_00E048, &gameplay_keep_Linkanim_00E040, &gameplay_keep_Linkanim_00E050,
    &gameplay_keep_Linkanim_00E030, &gameplay_keep_Linkanim_00E010, &gameplay_keep_Linkanim_00E020,
    &gameplay_keep_Linkanim_00E028,
};

LinkAnimationHeader* D_8085D6A4[] = {
    NULL,
    NULL,
    &gameplay_keep_Linkanim_00E058,
    &gameplay_keep_Linkanim_00E058,
    &gameplay_keep_Linkanim_00E058,
    &gameplay_keep_Linkanim_00E038,
    &gameplay_keep_Linkanim_00E018,
    &gameplay_keep_Linkanim_00E018,
    &gameplay_keep_Linkanim_00E018,
    NULL,
    NULL,
};

LinkAnimationHeader* D_8085D6D0[] = {
    &gameplay_keep_Linkanim_00E098,
    &gameplay_keep_Linkanim_00E088,
    &gameplay_keep_Linkanim_00E090,
};

u8 D_8085D6DC[][2] = {
    { 0x20, 0x3A },
    { 0x19, 0x2A },
};

Vec3s D_8085D6E0 = { -0x45, 0x1BEA, -0x10A };

AnimSfxEntry D_8085D6E8[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 48, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 58, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 68, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 92, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 110, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 126, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 132, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 136, NA_SE_PL_CALM_PAT, STOP),
};

void func_8084FE7C(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;

    this->stateFlags2 |= PLAYER_STATE2_40;

    func_80847E2C(this, 1.0f, 10.0f);
    if (this->unk_AE8 == 0) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            this->skelAnime.animation = &gameplay_keep_Linkanim_00E088;
            this->unk_AE8 = 0x63;
        } else {
            s32 var_v0 = (this->mountSide < 0) ? 0 : 1;

            if (LinkAnimation_OnFrame(&this->skelAnime, D_8085D6DC[var_v0][0])) {
                Actor_SetCameraHorseSetting(play, this);
                func_800B8E58(this, NA_SE_PL_CLIMB_CLIFF);
            } else if (LinkAnimation_OnFrame(&this->skelAnime, D_8085D6DC[var_v0][1])) {
                func_800B8E58(this, NA_SE_PL_SIT_ON_HORSE);
            }
        }
    } else {
        if (rideActor->actor.bgCheckFlags & 1) {
            func_80841A50(play, this);
        }

        Actor_SetCameraHorseSetting(play, this);

        this->skelAnime.prevTransl = D_8085D6E0;

        if ((this->unk_AE8 < 0) || ((rideActor->animationIdx != (this->unk_AE8 & 0xFFFF)) &&
                                    ((rideActor->animationIdx >= ENHORSE_ANIM_STOPPING) || (this->unk_AE8 >= 2)))) {
            s32 animationIdx = rideActor->animationIdx;

            if (animationIdx < ENHORSE_ANIM_STOPPING) {
                f32 temp_fv0 = Rand_ZeroOne();
                s32 index = 0;

                animationIdx = ENHORSE_ANIM_WHINNEY;
                if (temp_fv0 < 0.1f) {
                    index = 2;
                } else if (temp_fv0 < 0.2f) {
                    index = 1;
                }

                Player_AnimationPlayOnce(play, this, D_8085D6D0[index]);
            } else {
                this->skelAnime.animation = D_8085D688[animationIdx - 2];
                if (this->unk_AE8 >= 0) {
                    Animation_SetMorph(play, &this->skelAnime, 8.0f);
                }

                if (animationIdx < ENHORSE_ANIM_WALK) {
                    func_808309CC(play, this);
                    this->unk_AE7 = 0;
                }
            }

            this->unk_AE8 = animationIdx;
        }

        if (this->unk_AE8 == 1) {
            if ((D_80862B04 != 0) || func_8082DAFC(play)) {
                Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00E098);
            } else if (LinkAnimation_Update(play, &this->skelAnime)) {
                this->unk_AE8 = 0x63;
            } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E088) {
                Player_PlayAnimSfx(this, D_8085D6E8);
            }
        } else {
            this->skelAnime.curFrame = rideActor->curFrame;
            LinkAnimation_AnimateFrame(play, &this->skelAnime);
        }

        AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.morphTable,
                                    this->skelAnime.jointTable);

        if ((play->csCtx.state != CS_STATE_0) || (this->csMode != PLAYER_CSMODE_0)) {
            this->unk_AA5 = 0;
            this->unk_AE7 = 0;
        } else if ((this->unk_AE8 < 2) || (this->unk_AE8 >= 4)) {
            D_80862B04 = func_8083216C(this, play);
            if (D_80862B04 != 0) {
                this->unk_AE7 = 0;
            }
        }

        this->actor.world.pos.x = rideActor->actor.world.pos.x + rideActor->riderPos.x;
        this->actor.world.pos.y = rideActor->actor.world.pos.y + rideActor->riderPos.y - 27.0f;
        this->actor.world.pos.z = rideActor->actor.world.pos.z + rideActor->riderPos.z;

        this->currentYaw = this->actor.shape.rot.y = rideActor->actor.shape.rot.y;

        if (D_80862B04 == 0) {
            if (this->unk_AE7 != 0) {
                if (LinkAnimation_Update(play, &this->unk_284)) {
                    rideActor->stateFlags &= ~ENHORSE_FLAG_8;
                    this->unk_AE7 = 0;
                }

                if (this->unk_284.animation == &gameplay_keep_Linkanim_00E080) {
                    if (LinkAnimation_OnFrame(&this->unk_284, 23.0f)) {
                        func_800B8E58(this, NA_SE_IT_LASH);
                        func_8082DF8C(this, NA_SE_VO_LI_LASH);
                    }

                    AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                                this->unk_284.jointTable);
                } else {
                    if (LinkAnimation_OnFrame(&this->unk_284, 10.0f)) {
                        func_800B8E58(this, NA_SE_IT_LASH);
                        func_8082DF8C(this, NA_SE_VO_LI_LASH);
                    }

                    AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                                 this->unk_284.jointTable, D_8085B9F0);
                }
            } else if (!CHECK_FLAG_ALL(this->actor.flags, 0x100)) {
                LinkAnimationHeader* anim = NULL;

                if (EN_HORSE_CHECK_3(rideActor)) {
                    anim = &gameplay_keep_Linkanim_00E080;
                } else if (EN_HORSE_CHECK_2(rideActor)) {
                    if ((this->unk_AE8 >= 2) && (this->unk_AE8 != 0x63)) {
                        anim = D_8085D6A4[this->unk_AE8];
                    }
                }

                if (anim != NULL) {
                    LinkAnimation_PlayOnce(play, &this->unk_284, anim);
                    this->unk_AE7 = 1;
                }
            }
        }

        if (this->stateFlags1 & PLAYER_STATE1_100000) {
            if (CHECK_BTN_ANY(D_80862B44->press.button, BTN_A) || !func_8084FE48(this)) {
                this->unk_AA5 = 0;
                this->stateFlags1 &= ~PLAYER_STATE1_100000;
            } else {
                func_8084FD7C(play, this, &rideActor->actor);
            }
        } else if ((this->csMode != PLAYER_CSMODE_0) ||
                   (!func_8082DAFC(play) && ((rideActor->actor.speedXZ != 0.0f) || !func_808391D8(this, play)) &&
                    !func_80847BF0(this, play) && !func_80838A90(this, play))) {
            if (this->targetedActor != NULL) {
                if (func_800B7128(this)) {
                    this->unk_AB2.y = func_8083C62C(this, true) - this->actor.shape.rot.y;
                    this->unk_AB2.y = CLAMP(this->unk_AB2.y, -0x4AAA, 0x4AAA);
                    this->actor.focus.rot.y = this->actor.shape.rot.y + this->unk_AB2.y;
                    this->unk_AB2.y += 0xFA0;
                    this->unk_AA6 |= 0x80;
                } else {
                    func_8083C62C(this, false);
                }

                this->unk_AA8 = 0;
            } else if (func_8084FE48(this)) {
                if (func_800B7128(this)) {
                    func_80831010(this, play);
                }

                this->unk_B86[0] = 0xC;
            } else if (func_800B7128(this)) {
                func_8084FD7C(play, this, &rideActor->actor);
            }
        }
    }

    if (this->csMode == PLAYER_CSMODE_6) {
        this->csMode = PLAYER_CSMODE_0;
    }
}

AnimSfxEntry D_8085D708[] = {
    ANIMSFX(ANIMSFX_TYPE_5, 0, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 10, NA_SE_PL_GET_OFF_HORSE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 25, NA_SE_PL_SLIPDOWN, STOP),
};

void func_808505D0(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;
    func_80847E2C(this, 1.0f, 10.0f);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Actor* rideActor = this->rideActor;

        Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), 1);
        func_80839E74(this, play);

        this->stateFlags1 &= ~PLAYER_STATE1_800000;
        this->actor.parent = NULL;
        D_801BDA9C = 0;

        if (CHECK_QUEST_ITEM(QUEST_SONG_EPONA) || (DREG(1) != 0)) {
            gSaveContext.save.horseData.scene = play->sceneNum;
            gSaveContext.save.horseData.pos.x = rideActor->world.pos.x;
            gSaveContext.save.horseData.pos.y = rideActor->world.pos.y;
            gSaveContext.save.horseData.pos.z = rideActor->world.pos.z;
            gSaveContext.save.horseData.yaw = rideActor->shape.rot.y;
        }
    } else {
        if (this->mountSide < 0) {
            D_8085D708[0].flags = ANIMSFX_FLAGS(ANIMSFX_TYPE_5, 40, CONTINUE);
        } else {
            D_8085D708[0].flags = ANIMSFX_FLAGS(ANIMSFX_TYPE_5, 29, CONTINUE);
        }

        Player_PlayAnimSfx(this, D_8085D708);
    }
}

s32 func_80850734(PlayState* play, Player* this) {
    if ((this->transformation == PLAYER_STRENGTH_ZORA) && (this->windSpeed == 0.0f) &&
        (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) && CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) {
        func_8083B850(play, this);
        this->stateFlags2 |= PLAYER_STATE2_400;
        LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E418, 2.0f / 3.0f, 4.0f,
                             Animation_GetLastFrame(&gameplay_keep_Linkanim_00E418), ANIMMODE_ONCE, -6.0f);
        this->unk_AE8 = 5;
        this->unk_B86[0] = 0;
        this->unk_B48 = this->linearVelocity;
        this->actor.velocity.y = 0.0f;
        func_800B8E58(this, NA_SE_PL_ZORA_SWIM_DASH);
        return true;
    }
    return false;
}

s32 func_80850854(PlayState* play, Player* this) {
    if ((this->transformation == PLAYER_FORM_DEKU) && (this->unk_B67 != 0) &&
        (gSaveContext.save.playerData.health != 0) && (D_80862AFC != 0.0f)) {
        func_808373F8(play, this, 0);
        return true;
    }
    return false;
}

void func_808508C8(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8082E67C(play, this, &gameplay_keep_Linkanim_00E000);
    func_808475B4(this);

    if (this->unk_AE8 != 0) {
        this->unk_AE8--;
    }

    func_8082F164(this, BTN_R);

    if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
        this->unk_AE8 = 0;
    }

    if (!func_8082DAFC(play) && !func_80833058(play, this, D_8085D048, 1) && !func_8083B3B4(play, this, D_80862B44) &&
        ((this->unk_AE8 != 0) || !func_80850734(play, this))) {
        sp34 = 0.0f;
        sp32 = this->actor.shape.rot.y;

        if (this->unk_AA5 > 2) {
            this->unk_AA5 = 0;
        }

        if (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
            if (this->actor.bgCheckFlags & 1) {
                func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_14][this->modelAnimType], play);
                func_8082E1BC(this);
            }
        } else if ((func_80850854(play, this) == 0) &&
                   (func_80832F78(this, &sp34, &sp32, 0.0f, play), (sp34 != 0.0f))) {
            if ((ABS_ALT(BINANG_SUB(this->actor.shape.rot.y, sp32)) > 0x6000) &&
                !Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
                return;
            }

            if (func_8082FC24(this) || func_80847ED4(this)) {
                func_80848048(play, this);
            } else {
                func_8083B73C(play, this, sp32);
            }
        }

        func_8084748C(this, &this->linearVelocity, sp34, sp32);
        func_80847F1C(this);
    }
}

void func_80850B18(Player* this, PlayState* play) {
    if (!func_80838A90(this, play)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
        func_808477D0(play, this, NULL, this->linearVelocity);
        func_808475B4(this);

        if (DECR(this->unk_AE8) == 0) {
            func_808353DC(play, this);
        }
    }
}

void func_80850BA8(Player* this) {
    this->linearVelocity = Math_CosS(this->unk_AAA) * this->unk_B48;
    this->actor.velocity.y = -Math_SinS(this->unk_AAA) * this->unk_B48;
}

void func_80850BF8(Player* this, f32 arg1) {
    f32 temp_fv0;
    s16 temp_ft0;

    Math_AsymStepToF(&this->unk_B48, arg1, 1.0f, (fabsf(this->unk_B48) * 0.01f) + 0.4f);
    temp_fv0 = Math_CosS(D_80862B44->rel.stick_x * 0x10E);

    temp_ft0 = (((D_80862B44->rel.stick_x >= 0) ? 1 : -1) * (1.0f - temp_fv0) * -1100.0f);
    temp_ft0 = CLAMP(temp_ft0, -0x1F40, 0x1F40);

    this->currentYaw += temp_ft0;
}

void func_80850D20(PlayState* play, Player* this) {
    func_8083F8A8(play, this, 12.0f, -1, 1.0f, 160, 20, true);
}

#ifdef NON_MATCHING
void func_80850D68(Player* this, PlayState* play) {
    f32 sp44;
    s16 temp_a1_2; // sp42
    s16 sp40;
    s16 var_a1;
    s16 temp_v0_2; // sp3C
    s16 var_t1;    // sp3A
    s16 temp_v1_3;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_808475B4(this);
    func_8082F164(this, BTN_R);

    if (func_80833058(play, this, D_8085D048, 0)) {
        return;
    }

    if (func_8083B3B4(play, this, D_80862B44)) {
        return;
    }

    if (func_80840A30(play, this, &this->linearVelocity, 0.0f)) {
        return;
    }

    sp44 = 0.0f;

    if (this->unk_AE8 != 0) {
        if ((!func_8082DA90(play) && !CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) ||
            (this->currentBoots != PLAYER_BOOTS_ZORA_LAND)) {
            this->unk_B86[0] = 1;
        }

        if (LinkAnimation_Update(play, &this->skelAnime) && (DECR(this->unk_AE8) == 0)) {
            if (this->unk_B86[0] != 0) {
                this->stateFlags3 &= ~PLAYER_STATE3_8000;
                func_8082DB90(play, this, &gameplay_keep_Linkanim_00E408);
            } else {
                func_8082DB60(play, this, &gameplay_keep_Linkanim_00E3D8);
            }
        } else {
            func_80832F78(this, &sp44, &sp40, 0.0f, play);
            Math_ScaledStepToS(&this->currentYaw, sp40, 0x640);

            if (this->skelAnime.curFrame >= 13.0f) {
                sp44 = 12.0f;

                if (LinkAnimation_OnFrame(&this->skelAnime, 13.0f) != 0) {
                    this->unk_B48 = 16.0f;
                }
                this->stateFlags3 |= PLAYER_STATE3_8000;
            } else {
                sp44 = 0.0f;
            }
        }

        Math_SmoothStepToS(&this->unk_B86[1], D_80862B44->rel.stick_x * 0xC8, 0xA, 0x3E8, 0x64);
        Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(40) + 1, IREG(41), IREG(42));
    } else if (this->unk_B86[0] == 0) {
        LinkAnimation_Update(play, &this->skelAnime);

        if ((!func_8082DA90(play) && !CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) ||
            (this->currentBoots != PLAYER_BOOTS_ZORA_LAND) || (this->windSpeed > 9.0f)) {
            this->stateFlags3 &= ~PLAYER_STATE3_8000;
            func_8082DB90(play, this, &gameplay_keep_Linkanim_00E408);
            this->unk_B86[0] = 1;
        } else {
            sp44 = 9.0f;
            func_800B8F98(&this->actor, NA_SE_PL_ZORA_SWIM_LV - SFX_FLAG);
        }

        var_a1 = D_80862B44->rel.stick_y * 0xC8;
        if (this->unk_B8C != 0) {
            this->unk_B8C--;
            temp_v1_3 = this->unk_B6C - 0xFA0;
            if (temp_v1_3 < var_a1) {
                var_a1 = temp_v1_3;
            }
        }

        if ((this->unk_AAA >= -0x1555) && (this->actor.depthInWater < (this->ageProperties->unk_24 + 10.0f)) &&
            (var_a1 < 0x7D0)) {
            var_a1 = 0x7D0;
        }

        Math_SmoothStepToS(&this->unk_AAA, var_a1, 4, 0xFA0, 0x190);
        temp_a1_2 = D_80862B44->rel.stick_x * 0x64;
        if ((Math_ScaledStepToS(&this->unk_B8A, temp_a1_2, 0x384) != 0) && (temp_a1_2 == 0)) {
            Math_SmoothStepToS(&this->unk_B86[1], 0, 4, 0x5DC, 0x64);
            Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(44) + 1, IREG(45), IREG(46));
        } else {
            temp_v0_2 = this->unk_B86[1];
            var_t1 = (this->unk_B8A < 0) ? -0x3A98 : 0x3A98;
            this->unk_B86[1] += this->unk_B8A;
            Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(47) + 1, IREG(48), IREG(49));

            if ((ABS_ALT(this->unk_B8A) > 0xFA0) &&
                ((((temp_v0_2 + this->unk_B8A) - var_t1) * (temp_v0_2 - var_t1)) <= 0)) {
                func_800B8E58(this, NA_SE_PL_ZORA_SWIM_ROLL);
            }
        }

        if (D_80862B18 < 20.0f) {
            func_80850D20(play, this);
        }
    } else {
        Math_SmoothStepToS(&this->unk_B86[1], 0, 4, 0xFA0, 0x190);
        if ((this->skelAnime.curFrame <= 5.0f) || !func_80850734(play, this)) {
            if (LinkAnimation_Update(play, &this->skelAnime)) {
                func_808353DC(play, this);
            }
        }

        func_8082F09C(this);
    }

    if ((this->unk_B8C < 8) && (this->actor.bgCheckFlags & 1)) {
        DynaPolyActor* temp_v0_3;

        if ((this->actor.floorBgId == 0x32) ||
            ((temp_v0_3 = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId)) == NULL) ||
            (temp_v0_3->actor.id != ACTOR_EN_TWIG)) {
            this->unk_AAA += (-this->unk_B6C - this->unk_AAA) * 2;
            this->unk_B8C = 0xF;
        }

        func_80850D20(play, this);
        func_800B8E58(this, NA_SE_PL_BODY_BOUND);
    }

    func_80850BF8(this, sp44);
    func_80850BA8(this);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850D68.s")
#endif

void func_808513EC(Player* this, PlayState* play) {
    f32 sp34;
    s16 sp32;
    s16 sp30;
    s16 var_v0;

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_808475B4(this);
    func_8082F164(this, BTN_R);
    if (!func_80833058(play, this, D_8085D048, 1) && !func_8083B3B4(play, this, D_80862B44) &&
        !func_80850854(play, this)) {
        func_808477D0(play, this, D_80862B44, this->linearVelocity);
        if (func_8082DA90(play)) {
            sp34 = this->linearVelocity;
            sp32 = this->actor.shape.rot.y;
        } else {
            func_80832F78(this, &sp34, &sp32, 0.0f, play);
        }
        sp30 = this->actor.shape.rot.y - sp32;
        if (!func_80850734(play, this)) {
            if (func_8082FC24(this) || func_80847ED4(this)) {
                func_80848048(play, this);
            } else {
                if ((sp34 == 0.0f) || (ABS_ALT(sp30) > 0x6000) ||
                    (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER)) {
                    func_808353DC(play, this);
                }
            }
            func_80847FF8(this, &this->linearVelocity, sp34, sp32);
        }
    }
}

void func_80851588(Player* this, PlayState* play) {
    f32 sp2C;
    s16 sp2A;

    func_808477D0(play, this, D_80862B44, this->linearVelocity);
    func_808475B4(this);
    func_8082F164(this, BTN_R);

    if (!func_80833058(play, this, D_8085D048, 1) && !func_8083B3B4(play, this, D_80862B44)) {
        func_80832F78(this, &sp2C, &sp2A, 0.0f, play);

        if (sp2C == 0.0f) {
            func_808353DC(play, this);
        } else if (!func_8082FC24(this) && !func_80847ED4(this)) {
            func_8083B73C(play, this, sp2A);
        } else {
            func_80848094(play, this, &sp2C, &sp2A);
        }

        func_80847FF8(this, &this->linearVelocity, sp2C, sp2A);
    }
}

void func_808516B4(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    this->actor.gravity = 0.0f;
    func_8083216C(this, play);
    func_8082F164(this, BTN_R);

    if (func_80838A90(this, play)) {
        return;
    }

    if (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
        func_808353DC(play, this);
    } else if (this->unk_AE7 == 0) {
        f32 temp_fv0;

        if (this->unk_AE8 == 0) {
            if (LinkAnimation_Update(play, &this->skelAnime) ||
                ((this->skelAnime.curFrame >= 22.0f) && !CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A))) {
                func_8083B798(play, this);
            } else if (LinkAnimation_OnFrame(&this->skelAnime, 20.0f)) {
                this->actor.velocity.y = -2.0f;
            }
            func_80832F24(this);
        } else {
            func_808477D0(play, this, D_80862B44, this->actor.velocity.y);
            this->unk_AAA = 0x3E80;

            if (CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A) && !func_8083D23C(this, play) &&
                !(this->actor.bgCheckFlags & 1) && (this->actor.depthInWater < 120.0f)) {
                func_808481CC(play, this, -2.0f);
            } else {
                this->unk_AE7 += 1;
                func_8082E634(play, this, &gameplay_keep_Linkanim_00E000);
            }
        }

        temp_fv0 = (this->actor.depthInWater - this->ageProperties->unk_30) * 0.04f;
        if (temp_fv0 < this->actor.velocity.y) {
            this->actor.velocity.y = temp_fv0;
        }
    } else if (this->unk_AE7 == 1) {
        LinkAnimation_Update(play, &this->skelAnime);
        func_808475B4(this);
        if (this->unk_AAA < 0x2710) {
            this->unk_AE7++;
            this->unk_AE8 = this->actor.depthInWater;
            func_8082E634(play, this, &gameplay_keep_Linkanim_00DFD0);
        }
    } else if (!func_8083B3B4(play, this, D_80862B44)) {
        f32 var_fv1 = (this->unk_AE8 * 0.018f) + 4.0f;

        if (this->stateFlags1 & PLAYER_STATE1_800) {
            D_80862B44 = NULL;
        }

        func_808477D0(play, this, D_80862B44, fabsf(this->actor.velocity.y));
        Math_ScaledStepToS(&this->unk_AAA, -0x2710, 0x320);

        var_fv1 = CLAMP_MAX(var_fv1, 8.0f);
        func_808481CC(play, this, var_fv1);
    }
}

void func_808519FC(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8082F164(this, BTN_R);
    if (((this->stateFlags1 & PLAYER_STATE1_400) || (this->skelAnime.curFrame <= 1.0f) || !func_80850734(play, this)) &&
        LinkAnimation_Update(play, &this->skelAnime)) {
        if (!(this->stateFlags1 & PLAYER_STATE1_400) || func_808482E0(play, this)) {
            func_80848250(play, this);
            func_808353DC(play, this);
            func_8082DC64(play, this);
        }
    } else {
        if ((this->stateFlags1 & PLAYER_STATE1_400) && LinkAnimation_OnFrame(&this->skelAnime, 10.0f)) {
            func_8082ECE0(this);
            func_8082DC64(play, this);
        } else if (LinkAnimation_OnFrame(&this->skelAnime, 5.0f)) {
            func_8082DF8C(this, NA_SE_VO_LI_BREATH_DRINK);
        }
    }

    func_808475B4(this);
    func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
}

void func_80851B58(Player* this, PlayState* play) {
    func_808475B4(this);
    Math_StepToF(&this->linearVelocity, 0.0f, 0.4f);
    if (LinkAnimation_Update(play, &this->skelAnime) && (this->linearVelocity < 10.0f)) {
        func_808353DC(play, this);
    }
}

void func_80851BD4(Player* this, PlayState* play) {
    func_808475B4(this);
    if (LinkAnimation_Update(play, &this->skelAnime) && (this == GET_PLAYER(play))) {
        func_80840770(play, this);
    }
    func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
}

s32 func_80851C40(PlayState* play, Player* this) {
    return ((play->sceneNum == SCENE_MILK_BAR) && Audio_IsSequencePlaying(NA_BGM_BALLAD_OF_THE_WIND_FISH)) ||
           (((play->sceneNum != SCENE_MILK_BAR) && (this->csMode == PLAYER_CSMODE_68)) ||
            ((play->msgCtx.msgMode == 0x12) || (play->msgCtx.msgMode == 0x13) || (play->msgCtx.msgMode == 0x14) ||
             ((play->msgCtx.ocarinaMode != 1) &&
              ((this->csMode == PLAYER_CSMODE_5) || (play->msgCtx.ocarinaMode == 3) ||
               play->msgCtx.ocarinaAction == 0x32))));
}

// Deku playing the pipes? The loops both overwrite unk_AF0[0].y,z and unk_AF0[1].x,y,z
void func_80851D30(PlayState* play, Player* this) {
    f32* var_s0 = &this->unk_AF0[0].y; // TODO: what is going on around here in the struct?
    Vec3f sp50;

    if (func_80851C40(play, this)) {
        s32 i;

        if (this->skelAnime.mode != ANIMMODE_LOOP) {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }
        func_80124618(D_801C03A0, this->skelAnime.curFrame, &sp50);

        for (i = 0; i < 5; i++) {
            *var_s0 = sp50.x;
            var_s0++;
        }
    } else if (play->msgCtx.ocarinaMode == 1) {
        if (play->msgCtx.unk12048 != 0xFF) {
            var_s0[play->msgCtx.unk12048] = 1.2f;
            func_8082DB90(play, this, D_8085D190[this->transformation]);
        } else {
            s32 i;

            for (i = 0; i < 5; i++) {
                Math_StepToF(var_s0++, 1.0f, 0.04000001f);
            }
        }
    }
}

void func_80851EAC(Player* this) {
    this->unk_B86[0] = -1;
    this->unk_B86[1] = -1;
    this->unk_B10[0] = 0.0f;
}

struct_8085D714 D_8085D714[] = {
    { 1, &gameplay_keep_Linkanim_00E1C8 }, { 1, &gameplay_keep_Linkanim_00E1D8 }, { 1, &gameplay_keep_Linkanim_00E1D0 },
    { 0, &gameplay_keep_Linkanim_00E1E8 }, { 0, &gameplay_keep_Linkanim_00E1E0 },
};

void func_80851EC8(PlayState* play, Player* this) {
    struct_8085D714* temp3 = &D_8085D714[play->msgCtx.unk12048];
    f32* temp2 = &this->unk_B10[play->msgCtx.unk12048];
    s16* temp_a3 = &this->unk_B86[temp3->unk_0];

    temp_a3[0] = play->msgCtx.unk12048;
    temp2[0] = 3.0f;
}

#ifdef NON_MATCHING
// regalloc and some reordering
void func_80851F18(PlayState* play, Player* this) {
    struct_8085D714* temp;
    Vec3s* sp2C;
    f32* temp_v0;
    s32 i;
    // s32 temp_t1;

    // temp_t1 = this->unk_B86[0];
    if (this->unk_B86[0] >= 0) {
        temp = D_8085D714 + this->unk_B86[0];
        temp_v0 = &this->unk_B10[this->unk_B86[0]];
        AnimationContext_SetLoadFrame(play, temp->unk_4, *temp_v0, this->skelAnime.limbCount,
                                      this->skelAnime.morphTable);
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->skelAnime.morphTable, D_8085BA08);
    }
    // temp_t1 = this->unk_B86[1];
    if (this->unk_B86[1] >= 0) {
        temp = D_8085D714 + this->unk_B86[1];
        temp_v0 = &this->unk_B10[this->unk_B86[1]];
        sp2C = ALIGN16((uintptr_t)this->blendTableBuffer);
        AnimationContext_SetLoadFrame(play, temp->unk_4, *temp_v0, ((void)0, this->skelAnime.limbCount), sp2C);
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable, sp2C, D_8085BA20);
    }

    temp_v0 = this->unk_B10;
    for (i = 0; i < 5; i++) {
        *temp_v0 += 1.0f;
        if (*temp_v0 >= 9.0f) {
            *temp_v0 = 8.0f;
            if (this->unk_B86[0] == i) {
                this->unk_B86[0] = -1;
            } else if (this->unk_B86[1] == i) {
                this->unk_B86[1] = -1;
            }
        }
        temp_v0++;
    }
}
#else
void func_80851F18(PlayState* play, Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851F18.s")
#endif

// Goron playing the drums?
void func_808521E0(PlayState* play, Player* this) {
    if (func_80851C40(play, this)) {
        if (this->skelAnime.animation != &gameplay_keep_Linkanim_00E1F0) {
            func_8082DB60(play, this, &gameplay_keep_Linkanim_00E1F0);
        }

        func_80124618(D_801C0490, this->skelAnime.curFrame, &this->unk_AF0[1]);
    } else if (play->msgCtx.ocarinaMode == 1) {
        if (play->msgCtx.unk12048 != 0xFF) {
            func_80851EC8(play, this);
        }

        func_80851F18(play, this);
    }
}

// Zora playing the guitar?
void func_80852290(PlayState* play, Player* this) {
    if (func_80851C40(play, this)) {
        if (this->skelAnime.mode != ANIMMODE_LOOP) {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }

        this->unk_B8A = 8;
    } else {
        f32 sp3C;
        s16 var_a1_3;
        s16 sp38;

        if ((play->msgCtx.ocarinaMode == 1) && (play->msgCtx.unk12048 != 0xFF)) {
            if ((this->unk_A90 != NULL) && (this->unk_A94 < 0.0f)) {
                this->unk_A90->flags |= ACTOR_FLAG_20000000;
                this->unk_A94 = 0.0f;
            }

            func_8082DB90(play, this, D_8085D190[this->transformation]);
            this->unk_B8A = 8;
        }

        D_80862B44 = play->state.input;
        func_800FF3A0(&sp3C, &sp38, D_80862B44);

        if (BINANG_ADD(sp38, 0x4000) < 0) {
            sp38 -= 0x8000;
            sp3C = -sp3C;
        }

        if (sp38 < -0x1F40) {
            sp38 = -0x1F40;
        } else if (sp38 > 0x2EE0) {
            sp38 = 0x2EE0;
        }

        var_a1_3 = (sp3C * -100.0f);
        var_a1_3 = CLAMP_MAX(var_a1_3, 0xFA0);
        Math_SmoothStepToS(&this->unk_AB2.x, var_a1_3, 4, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_AB2.y, sp38, 4, 0x7D0, 0);
        this->unk_AAC.x = -this->unk_AB2.x;
        this->unk_AA6 |= 0xC8;

        var_a1_3 = ABS_ALT(this->unk_AB2.x);
        if (var_a1_3 < 0x7D0) {
            this->actor.shape.face = 0;
        } else if (var_a1_3 < 0xFA0) {
            this->actor.shape.face = 13;
        } else {
            this->actor.shape.face = 8;
        }
    }

    if (DECR(this->unk_B8A) != 0) {
        this->unk_B86[0] += (s16)(this->unk_AB2.x * 2.5f);
        this->unk_B86[1] += (s16)(this->unk_AB2.y * 3.0f);
    } else {
        this->unk_B86[0] = 0;
        this->unk_B86[1] = 0;
    }
}

void func_8085255C(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_DEKU) {
        func_80851D30(play, this);
    } else if (this->transformation == PLAYER_FORM_GORON) {
        func_808521E0(play, this);
    } else if (this->transformation == PLAYER_FORM_ZORA) {
        func_80852290(play, this);
    }
}

void func_808525C4(PlayState* play, Player* this) {
    if (this->unk_AE8++ >= 3) {
        if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_DEKU)) {
            func_8082E5A8(play, this, D_8085D190[this->transformation]);
        } else if (this->transformation == PLAYER_FORM_GORON) {
            func_80851EAC(this);
            func_8082DB60(play, this, &gameplay_keep_Linkanim_00E200);
        } else {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }

        this->unk_B48 = 1.0f;
    }
}

void func_8085269C(Player* this, PlayState* play) {
    if ((this->unk_AA5 != 4) && ((LinkAnimation_Update(play, &this->skelAnime) &&
                                  (this->skelAnime.animation == D_8085D17C[this->transformation])) ||
                                 ((this->skelAnime.mode == 0) && (this->unk_AE8 == 0)))) {
        func_808525C4(play, this);
        if (!(this->actor.flags & ACTOR_FLAG_20000000) || (this->unk_A90->id == ACTOR_EN_ZOT)) {
            func_80152434(play, 1);
        }
    } else if (this->unk_AE8 != 0) {
        if (play->msgCtx.ocarinaMode == 4) {
            play->interfaceCtx.unk_222 = 0;
            ActorCutscene_Stop(play->playerActorCsIds[0]);
            this->actor.flags &= ~ACTOR_FLAG_20000000;

            if ((this->talkActor != NULL) && (this->talkActor == this->unk_A90) && (this->unk_A94 >= 0.0f)) {
                func_8085B460(play, this->talkActor);
            } else if (this->tatlTextId < 0) {
                this->talkActor = this->tatlActor;
                this->tatlActor->textId = -this->tatlTextId;
                func_8085B460(play, this->talkActor);
            } else if (!func_80838A90(this, play)) {
                func_80836A5C(this, play);
                Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
            }
        } else {
            s32 var_v1 = (play->msgCtx.ocarinaMode >= 0x1C) && (play->msgCtx.ocarinaMode < 0x27);
            s32 pad[2];

            if (var_v1 || (play->msgCtx.ocarinaMode == 0x16) || (play->msgCtx.ocarinaMode == 0x1A) ||
                (play->msgCtx.ocarinaMode == 0x18) || (play->msgCtx.ocarinaMode == 0x19)) {
                if (play->msgCtx.ocarinaMode == 0x16) {
                    if (!func_8082DA90(play)) {
                        if (gSaveContext.save.playerData.deaths == 1) {
                            play->nextEntranceIndex = 0x1C10;
                        } else {
                            play->nextEntranceIndex = 0x1C00;
                        }

                        gSaveContext.nextCutsceneIndex = 0xFFF7;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                    }
                } else {
                    Actor* actor;

                    play->interfaceCtx.unk_222 = 0;
                    ActorCutscene_Stop(play->playerActorCsIds[0]);
                    this->actor.flags &= ~ACTOR_FLAG_20000000;

                    actor = Actor_Spawn(&play->actorCtx, play, var_v1 ? ACTOR_EN_TEST7 : ACTOR_EN_TEST6,
                                        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0,
                                        0, play->msgCtx.ocarinaMode);
                    if (actor != NULL) {
                        this->stateFlags1 &= ~PLAYER_STATE1_20000000;
                        this->csMode = PLAYER_CSMODE_0;
                        func_8085B28C(play, NULL, 0x13);
                        this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
                    } else {
                        func_80836A5C(this, play);
                        Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
                    }
                }
            } else if ((play->msgCtx.ocarinaMode == 3) && (play->msgCtx.lastPlayedSong == OCARINA_SONG_ELEGY)) {
                play->interfaceCtx.unk_222 = 0;
                ActorCutscene_Stop(play->playerActorCsIds[0]);

                this->actor.flags &= ~ACTOR_FLAG_20000000;
                func_80831760(play, this, func_80855A7C, 0);
                this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
            } else if (this->unk_AA5 == 4) {
                f32 temp_fa0 = this->skelAnime.jointTable[0].x;
                f32 temp_fa1 = this->skelAnime.jointTable[0].z;
                f32 var_fv1;

                var_fv1 = sqrtf(SQ(temp_fa0) + SQ(temp_fa1));
                if (var_fv1 != 0.0f) {
                    var_fv1 = (var_fv1 - 100.0f) / var_fv1;
                    var_fv1 = CLAMP_MIN(var_fv1, 0.0f);
                }

                this->skelAnime.jointTable[0].x = temp_fa0 * var_fv1;
                this->skelAnime.jointTable[0].z = temp_fa1 * var_fv1;
            } else {
                func_8085255C(play, this);
            }
        }
    }
}

void func_80852B28(Player* this, PlayState* play) {
    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80836A98(this, &gameplay_keep_Linkanim_00DD40, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 3.0f)) {
        if (Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW, this->bodyPartsPos[0xF].x, this->bodyPartsPos[0xF].y,
                        this->bodyPartsPos[0xF].z, 0xFA0, this->actor.shape.rot.y, 0, 8) != NULL) {
            Inventory_ChangeAmmo(SLOT_NUT, -1);
            this->unk_D57 = 4;
        }

        func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
    }
}

AnimSfxEntry D_8085D73C[] = {
    ANIMSFX(ANIMSFX_TYPE_7, 87, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 87, NA_SE_VO_LI_CLIMB_END, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 69, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 123, 0, STOP),
};

AnimSfxEntry D_8085D74C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_7, 13, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 73, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 120, 0, STOP),
};

void func_80852C04(Player* this, PlayState* play) {
    func_8083249C(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE8 != 0) {
            if (this->unk_AE8 > 1) {
                this->unk_AE8--;
            }

            if (func_808482E0(play, this) && (this->unk_AE8 == 1)) {
                Player_SetModels(this, Player_ActionToModelGroup(this, this->heldItemActionParam));

                if ((this->unk_B2A == 0x5D) || (this->unk_B2A == 0x64) || (this->unk_B2A == 0x65) ||
                    (this->unk_B2A == 0x66)) {
                    func_80838760(this);
                    func_80848250(play, this);
                    this->stateFlags1 &= ~PLAYER_STATE1_20000000;
                    func_8085B28C(play, NULL, 0x5D);
                } else {
                    s32 var_a2 = ((this->talkActor != NULL) && (this->exchangeItemId < PLAYER_AP_NONE)) ||
                                 (this->stateFlags3 & PLAYER_STATE3_20);

                    if (var_a2 || (gSaveContext.healthAccumulator == 0)) {
                        func_80838760(this);
                        if (var_a2) {
                            func_80848250(play, this);
                            this->exchangeItemId = PLAYER_AP_NONE;
                            if (!func_80847994(play, this)) {
                                func_8085B460(play, this->talkActor);
                            }
                        } else {
                            func_80848294(play, this);
                        }
                    }
                }
            }
        } else {
            func_8082E794(this);

            if ((this->getItemId == GI_STRAY_FAIRY) || (this->getItemId == GI_SKULL_TOKEN) ||
                (this->getItemId == GI_ICE_TRAP)) {
                func_80838760(this);
                this->stateFlags1 &= ~(PLAYER_STATE1_400 | PLAYER_STATE1_800);
                if (this->getItemId == GI_STRAY_FAIRY) {
                    func_80839E74(this, play);
                } else {
                    this->actor.colChkInfo.damage = 0;
                    func_80833B18(play, this, 3, 0.0f, 0.0f, 0, 20);
                }
            } else {
                if (this->skelAnime.animation == &gameplay_keep_Linkanim_00DB18) {
                    func_8082DB90(play, this,
                                  (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2C0
                                                                             : &gameplay_keep_Linkanim_00D5B0);
                } else {
                    func_8082DB90(play, this,
                                  (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2B8
                                                                             : &gameplay_keep_Linkanim_00D5A8);
                }

                func_8082E920(play, this, (1 | 2 | 4 | 8 | 0x10 | 0x80));
                func_80838760(this);
                this->unk_A86 = play->playerActorCsIds[1];
                this->unk_AE8 = 2;
            }
        }
    } else if (this->unk_AE8 == 0) {
        if (this->transformation == PLAYER_FORM_HUMAN) {
            Player_PlayAnimSfx(this, D_8085D73C);
        } else if (this->transformation == PLAYER_FORM_DEKU) {
            Player_PlayAnimSfx(this, D_8085D74C);
        }
    } else {
        if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00D5B0) ||
            (this->skelAnime.animation == &gameplay_keep_Linkanim_00E2C0)) {
            Math_ScaledStepToS(&this->actor.shape.rot.y,
                               BINANG_ADD(Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamId]), 0x8000), 0xFA0);
        } else if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00E2B8) &&
                   LinkAnimation_OnFrame(&this->skelAnime, 10.0f)) {
            func_8082E1BC(this);
        }

        if (LinkAnimation_OnFrame(&this->skelAnime, 21.0f)) {
            func_8082ECE0(this);
        }
    }
}

AnimSfxEntry D_8085D75C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 5, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 15, 0, STOP),
};

void func_80852FD4(Player* this, PlayState* play) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE7 == 0) {
            if (DECR(this->unk_AE8) == 0) {
                this->unk_AE7 = 1;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }
        } else {
            func_80839E74(this, play);
        }
    } else if ((this->transformation == PLAYER_FORM_FIERCE_DEITY) && LinkAnimation_OnFrame(&this->skelAnime, 158.0f)) {
        func_8082DF8C(this, NA_SE_VO_LI_SWORD_N);
    } else if (this->transformation != PLAYER_FORM_FIERCE_DEITY) {
        Player_PlayAnimSfx(this, D_8085D75C);
    } else {
        func_808484CC(this);
    }
}

Vec3f D_8085D764 = { 0.0f, 24.0f, 19.0f };
Vec3f D_8085D770 = { 0.0f, 0.0f, 2.0f };
Vec3f D_8085D77C = { 0.0f, 0.0f, -0.2f };

Color_RGBA8 D_8085D788 = { 255, 255, 255, 255 };
Color_RGBA8 D_8085D78C = { 255, 255, 255, 255 };

void func_808530E0(PlayState* play, Player* this) {
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;

    func_80835BC8(this, &this->actor.world.pos, &D_8085D764, &pos);
    func_80835BC8(this, &gZeroVec3f, &D_8085D770, &velocity);
    func_80835BC8(this, &gZeroVec3f, &D_8085D77C, &accel);
    func_800B0EB0(play, &pos, &velocity, &accel, &D_8085D788, &D_8085D78C, 40, 10, 10);
}

u8 D_8085D790[] = {
    1,     // PLAYER_AP_BOTTLE_POTION_RED
    1 | 2, // PLAYER_AP_BOTTLE_POTION_BLUE
    2,     // PLAYER_AP_BOTTLE_POTION_GREEN
    4,     // PLAYER_AP_BOTTLE_MILK
    4,     // PLAYER_AP_BOTTLE_MILK_HALF
    1 | 2, // PLAYER_AP_BOTTLE_CHATEAU
};

void func_80853194(Player* this, PlayState* play) {
    func_808323C0(this, play->playerActorCsIds[2]);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE8 == 0) {
            if (this->heldItemActionParam == PLAYER_AP_BOTTLE_POE) {
                s32 health = Rand_S16Offset(-1, 3);

                if (health == 0) {
                    health = 3;
                }
                if ((health < 0) && (gSaveContext.save.playerData.health <= 0x10)) {
                    health = 3;
                }

                if (health < 0) {
                    Health_ChangeBy(play, -0x10);
                } else {
                    gSaveContext.healthAccumulator = health * 0x10;
                }
            } else {
                s32 temp_v1 = D_8085D790[this->heldItemActionParam - PLAYER_AP_BOTTLE_POTION_RED];

                if (temp_v1 & 1) {
                    gSaveContext.healthAccumulator = 0x140;
                }
                if (temp_v1 & 2) {
                    Parameter_AddMagic(play, ((void)0, gSaveContext.unk_3F30) +
                                                 (gSaveContext.save.playerData.doubleMagic * 0x30) + 0x30);
                }
                if (temp_v1 & 4) {
                    gSaveContext.healthAccumulator = 0x50;
                }

                if (this->heldItemActionParam == PLAYER_AP_BOTTLE_CHATEAU) {
                    gSaveContext.save.weekEventReg[0xE] |= 8;
                }

                gSaveContext.jinxTimer = 0;
            }

            func_8082DB60(play, this,
                          (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E290
                                                                     : &gameplay_keep_Linkanim_00D4C0);
            this->unk_AE8 = 1;

        //! FAKE
        dummy_label_235515:;
        } else if (this->unk_AE8 < 0) {
            this->unk_AE8++;
            if (this->unk_AE8 == 0) {
                this->unk_AE8 = 3;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            } else if (this->unk_AE8 == -6) {
                func_808530E0(play, this);
            }
        } else {
            func_80838760(this);
            func_80839E74(this, play);
        }
    } else if (this->unk_AE8 == 1) {
        if ((gSaveContext.healthAccumulator == 0) && (gSaveContext.unk_3F28 != 9)) {
            if (this->transformation == PLAYER_FORM_DEKU) {
                LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E298, 2.0f / 3.0f, 0.0f, 5.0f, 2,
                                     -6.0f);
                this->unk_AE8 = -7;
            } else {
                func_8082E4A4(play, this, &gameplay_keep_Linkanim_00D4B0);
                this->unk_AE8 = 2;
            }

            Player_UpdateBottleHeld(play, this,
                                    (this->heldItemActionParam == PLAYER_AP_BOTTLE_MILK) ? ITEM_MILK_HALF : ITEM_BOTTLE,
                                    PLAYER_AP_BOTTLE);
        }

        func_8082DF8C(this, NA_SE_VO_LI_DRINK - SFX_FLAG);
    } else if ((this->unk_AE8 == 2) && LinkAnimation_OnFrame(&this->skelAnime, 29.0f)) {
        func_8082DF8C(this, NA_SE_VO_LI_BREATH_DRINK);
    }
}

struct_8085D798 D_8085D798[] = {
    { ACTOR_EN_ELF, 2, ITEM_FAIRY, PLAYER_AP_BOTTLE_FAIRY, 0x5E },
    { ACTOR_EN_FISH, -1, ITEM_FISH, PLAYER_AP_BOTTLE_FISH, 0x62 },
    { ACTOR_EN_INSECT, -1, ITEM_BUG, PLAYER_AP_BOTTLE_BUG, 0x63 },
    { ACTOR_EN_MUSHI2, -1, ITEM_BUG, PLAYER_AP_BOTTLE_BUG, 0x63 },
    { ACTOR_EN_TEST5, 0, ITEM_SPRING_WATER, PLAYER_AP_BOTTLE_SPRING_WATER, 0x67 },
    { ACTOR_EN_TEST5, 1, ITEM_HOT_SPRING_WATER, PLAYER_AP_BOTTLE_HOT_SPRING_WATER, 0x68 },
    { ACTOR_BG_GORON_OYU, -1, ITEM_HOT_SPRING_WATER, PLAYER_AP_BOTTLE_HOT_SPRING_WATER, 0x68 },
    { ACTOR_EN_ZORAEGG, -1, ITEM_ZORA_EGG, PLAYER_AP_BOTTLE_ZORA_EGG, 0x69 },
    { ACTOR_EN_DNP, -1, ITEM_DEKU_PRINCESS, PLAYER_AP_BOTTLE_DEKU_PRINCESS, 0x5F },
    { ACTOR_EN_OT, -1, ITEM_SEAHORSE, PLAYER_AP_BOTTLE_SEAHORSE, 0x6E },
    { ACTOR_OBJ_KINOKO, -1, ITEM_MUSHROOM, PLAYER_AP_BOTTLE_SEAHORSE, 0x6B },
    { ACTOR_EN_POH, -1, ITEM_POE, PLAYER_AP_BOTTLE_POE, 0x65 },
    { ACTOR_EN_BIGPO, -1, ITEM_BIG_POE, PLAYER_AP_BOTTLE_BIG_POE, 0x66 },
    { ACTOR_EN_ELF, 6, ITEM_FAIRY, PLAYER_AP_BOTTLE_FAIRY, 0x5E },
};

void func_808534C0(Player* this, PlayState* play) {
    struct_8085D200* sp24 = &D_8085D200[this->unk_AE8];

    func_80832F24(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE7 != 0) {
            func_808323C0(this, play->playerActorCsIds[3]);

            if (this->unk_AE8 == 0) {
                Message_StartTextbox(play, D_8085D798[this->unk_AE7 - 1].textId, &this->actor);

                func_801A3098(NA_BGM_GET_ITEM | 0x900);
                this->unk_AE8 = 1;
            } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
                Actor* targetActor;

                this->unk_AE7 = 0;
                func_80838760(this);
                func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));

                targetActor = this->talkActor;
                if ((targetActor != NULL) && (this->exchangeItemId < PLAYER_AP_NONE)) {
                    func_8085B460(play, targetActor);
                }
            }
        } else {
            func_80839E74(this, play);
        }
    } else {
        if (this->unk_AE7 == 0) {
            s32 temp_ft5 = this->skelAnime.curFrame - sp24->unk_8;

            if ((temp_ft5 >= 0) && ((s32)sp24->unk_9 >= temp_ft5)) {
                if ((this->unk_AE8 != 0) && (temp_ft5 == 0)) {
                    func_800B8E58(this, NA_SE_IT_SCOOP_UP_WATER);
                }

                if (func_8012364C(play, this, this->heldItemButton) == ITEM_BOTTLE) {
                    Actor* interactRangeActor = this->interactRangeActor;

                    if (interactRangeActor != NULL) {
                        struct_8085D798* entry = D_8085D798;
                        s32 i;

                        for (i = 0; i < ARRAY_COUNT(D_8085D798); i++) {
                            if (((interactRangeActor->id == entry->actorId) &&
                                 ((entry->actorParams < 0) || (interactRangeActor->params == entry->actorParams)))) {
                                break;
                            }
                            entry++;
                        }

                        if (i < ARRAY_COUNT(D_8085D798)) {
                            this->unk_AE7 = i + 1;
                            this->unk_AE8 = 0;
                            this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
                            interactRangeActor->parent = &this->actor;
                            Player_UpdateBottleHeld(play, this, entry->itemId, entry->actionParam);
                            func_8082DB90(play, this, sp24->unk_4);
                        }
                    }
                }
            }
        }

        if (this->skelAnime.curFrame <= 7.0f) {
            this->stateFlags3 |= PLAYER_STATE3_800;
        }
    }
}

Vec3f D_8085D7EC = { 0.0f, 0.0f, 5.0f };

void func_80853754(Player* this, PlayState* play) {
    func_808323C0(this, play->playerActorCsIds[2]);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80838760(this);
        func_80839E74(this, play);
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 37.0f)) {
        s32 sp2C = 8;

        func_800B8E58(this, NA_SE_EV_BOTTLE_CAP_OPEN);
        func_8082DF8C(this, NA_SE_VO_LI_AUTO_JUMP);
        if (this->heldItemActionParam == PLAYER_AP_BOTTLE_FAIRY) {
            Player_UpdateBottleHeld(play, this, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
            func_800B8E58(this, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
            sp2C = 1;
        }

        Player_SpawnFairy(play, this, &this->leftHandWorld.pos, &D_8085D7EC, sp2C);
    }
}

void func_80853850(Player* this, PlayState* play) {
    static Vec3f D_8085D7F8 = { 10.0f, 26.800001f, 30.0f };
    static s8 D_8085D804[PLAYER_FORM_MAX] = { 0x2D, 0x4B, 0x37, 0x23, 0x28 };
    static struct_8085D80C D_8085D80C[] = {
        { ACTOR_EN_FISH, 0 },       // PLAYER_AP_BOTTLE_FISH
        { ACTOR_OBJ_AQUA, 0 },      // PLAYER_AP_BOTTLE_SPRING_WATER
        { ACTOR_OBJ_AQUA, 1 },      // PLAYER_AP_BOTTLE_HOT_SPRING_WATER
        { ACTOR_EN_ZORAEGG, 0x11 }, // PLAYER_AP_BOTTLE_ZORA_EGG
        { ACTOR_EN_DNP, 1 },        // PLAYER_AP_BOTTLE_DEKU_PRINCESS
        { ACTOR_EN_MUSHI2, 0 },     // PLAYER_AP_BOTTLE_GOLD_DUST
        { ACTOR_EN_MUSHI2, 0 },     // PLAYER_AP_BOTTLE_1C
        { ACTOR_EN_OT, 0x8000 },    // PLAYER_AP_BOTTLE_SEAHORSE
        { ACTOR_EN_MUSHI2, 0 },     // PLAYER_AP_BOTTLE_MUSHROOM
        { ACTOR_EN_MUSHI2, 0 },     // PLAYER_AP_BOTTLE_HYLIAN_LOACH
        { ACTOR_EN_MUSHI2, 0 },     // PLAYER_AP_BOTTLE_BUG
    };
    static AnimSfxEntry D_8085D838[] = {
        ANIMSFX(ANIMSFX_TYPE_VOICE, 38, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
        ANIMSFX(ANIMSFX_TYPE_1, 40, NA_SE_EV_BOTTLE_CAP_OPEN, STOP),
    };

    CollisionPoly* sp6C;
    s32 sp68;
    Vec3f sp5C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    struct_8085D80C* sp4C;

    D_8085D7F8.z = D_8085D804[this->transformation];
    if (func_80835D58(play, this, &D_8085D7F8, &sp6C, &sp68, &sp5C)) {
        temp_fv1 = this->actor.world.pos.x - sp5C.x;
        temp_fa0 = this->actor.world.pos.z - sp5C.z;
        temp_fv0 = sqrtf(SQ(temp_fv1) + SQ(temp_fa0));

        if (temp_fv0 != 0.0f) {
            temp_fv0 = 3.0f / temp_fv0;

            this->actor.world.pos.x = this->actor.world.pos.x + (temp_fv1 * temp_fv0);
            this->actor.world.pos.z = this->actor.world.pos.z + (temp_fa0 * temp_fv0);
        }
    }

    func_80832F24(this);
    func_8083249C(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80838760(this);
        if (!func_80838A90(this, play)) {
            func_80839E74(this, play);
        }
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 76.0f)) {
        sp4C = &D_8085D80C[this->heldItemActionParam - PLAYER_AP_BOTTLE - 1];

        Actor_Spawn(&play->actorCtx, play, sp4C->actorId,
                    (Math_SinS(this->actor.shape.rot.y) * 5.0f) + this->leftHandWorld.pos.x, this->leftHandWorld.pos.y,
                    (Math_CosS(this->actor.shape.rot.y) * 5.0f) + this->leftHandWorld.pos.z, 0x4000,
                    this->actor.shape.rot.y, 0, sp4C->params);
        Player_UpdateBottleHeld(play, this, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
    } else {
        Player_PlayAnimSfx(this, D_8085D838);
    }
}

AnimSfxEntry D_8085D840[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 30, NA_SE_PL_PUT_OUT_ITEM, STOP),
};

void func_80853A5C(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;
    this->stateFlags3 |= PLAYER_STATE3_4000000;

    func_8083249C(this);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->exchangeItemId == PLAYER_AP_NONE) {
            Actor* targetActor = this->talkActor;

            func_80838760(this);
            this->unk_B2A = 0;

            if ((targetActor->textId != 0) && (targetActor->textId != 0xFFFF)) {
                this->actor.flags |= ACTOR_FLAG_100;
            }
            func_8085B460(play, targetActor);
        } else {
            GetItemEntry* giEntry = &sGetItemTable[D_8085D1A4[this->exchangeItemId] - 1];

            if (Player_ActionToBottle(this, this->heldItemActionParam) < 0) {
                this->unk_B2A = ABS_ALT(giEntry->unk_2);
            }

            if (this->unk_AE8 == 0) {
                if ((this->actor.textId != 0) && (this->actor.textId != 0xFFFF)) {
                    Message_StartTextbox(play, this->actor.textId, &this->actor);
                }

                this->unk_AE8 = 1;
            } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
                func_80838760(this);
                this->unk_B2A = 0;
                this->actor.flags &= ~ACTOR_FLAG_100;
                func_80839E74(this, play);
                this->unk_B5E = 0xA;
            }
        }
    } else if (this->unk_AE8 >= 0) {
        if ((Player_ActionToBottle(this, this->heldItemActionParam) >= 0) &&
            LinkAnimation_OnFrame(&this->skelAnime, 36.0f)) {
            Player_SetModels(this, PLAYER_MODELGROUP_BOTTLE);
        } else if (LinkAnimation_OnFrame(&this->skelAnime, 2.0f)) {
            GetItemEntry* giEntry = &sGetItemTable[D_8085D1A4[this->heldItemActionParam] - 1];

            func_80838830(this, giEntry->objectId);
        }
        Player_PlayAnimSfx(this, D_8085D840);
    }

    if ((this->unk_AE7 == 0) && (this->targetedActor != NULL)) {
        this->currentYaw = func_8083C62C(this, 0);
        this->actor.shape.rot.y = this->currentYaw;
    }
}

void func_80853CC0(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DE30);
    }

    if (play->sceneNum != SCENE_SEA_BS) {
        func_8082F164(this, BTN_R);
    }

    if (func_8082DE88(this, 0, 0x64)) {
        func_80836988(this, play);
        this->stateFlags2 &= ~PLAYER_STATE2_80;
    }
}

void func_80853D68(Player* this, PlayState* play) {
    CollisionPoly* floorPoly;
    f32 var_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    s16 downwardSlopeYaw;
    s16 var_v0;
    Vec3f slopeNormal;

    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    LinkAnimation_Update(play, &this->skelAnime);
    func_8083FBC4(play, this);
    func_8019F780(&this->actor.projectedPos, func_8082E078(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG), this->actor.speedXZ);

    if (func_80838A90(this, play)) {
        return;
    }

    if ((this->transformation == PLAYER_FORM_GORON) && func_8083A114(this, play)) {
        return;
    }

    floorPoly = this->actor.floorPoly;
    if (floorPoly == NULL) {
        func_80833AA0(this, play);
        return;
    }

    Actor_GetSlopeDirection(floorPoly, &slopeNormal, &downwardSlopeYaw);
    var_v0 = downwardSlopeYaw;
    if (this->unk_AE7 != 0) {
        var_v0 = downwardSlopeYaw + 0x8000;
    }
    if (this->linearVelocity < 0.0f) {
        downwardSlopeYaw += 0x8000;
    }

    var_fv0 = (1.0f - slopeNormal.y) * 40.0f;
    var_fv0 = CLAMP(var_fv0, 0.0f, 10.0f);

    temp_fv1 = var_fv0 * var_fv0 * 0.015f;
    var_fa0 = slopeNormal.y * 0.01f;
    if (SurfaceType_GetSlope(&play->colCtx, floorPoly, this->actor.floorBgId) != 1) {
        var_fv0 = 0.0f;
        var_fa0 = slopeNormal.y * 10.0f;
    }
    temp_fv1 = CLAMP_MIN(temp_fv1, 1.0f);

    if (Math_AsymStepToF(&this->linearVelocity, var_fv0, temp_fv1, var_fa0) && (var_fv0 == 0.0f)) {
        func_80836A98(this,
                      (this->unk_AE7 == 0) ? D_8085BE84[PLAYER_ANIMGROUP_41][this->modelAnimType]
                                           : D_8085BE84[PLAYER_ANIMGROUP_42][this->modelAnimType],
                      play);
    }

    Math_SmoothStepToS(&this->currentYaw, downwardSlopeYaw, 0xA, 0xFA0, 0x320);
    Math_ScaledStepToS(&this->actor.shape.rot.y, var_v0, 0x7D0);
}

void func_80859CE0(PlayState* play, Player* this, s32 arg2);

void func_80854010(Player* this, PlayState* play) {
    if ((DECR(this->unk_AE8) == 0) && func_808387A0(play, this)) {
        func_80859CE0(play, this, 0);
        Player_SetAction(play, this, func_8085B08C, 0);
        func_8085B08C(this, play);
    }
}

void func_808540A0(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_80854010, 0);
    this->unk_AE8 = 0x28;
    Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_KANKYO, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0x10);
}

void func_8085AB58(Player* this, CsCmdActorAction* playerAction);

void func_80854118(Player* this, PlayState* play) {
    if (D_80862B18 < 150.0f) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            if (this->unk_AE8 == 0) {
                if (this->actor.bgCheckFlags & 1) {
                    this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
                    func_8082E1BC(this);
                    this->unk_AE8 = 1;
                }
            } else {
                func_8085B384(this, play);
            }
        }

        Math_SmoothStepToF(&this->actor.velocity.y, 2.0f, 0.3f, 8.0f, 0.5f);
    }

    if (play->csCtx.state != CS_STATE_0) {
        if (play->csCtx.playerAction != NULL) {
            s32 pad;
            f32 sp28 = this->actor.world.pos.y;

            func_8085AB58(this, play->csCtx.playerAction);
            this->actor.world.pos.y = sp28;
        }
    }
}

void func_8085421C(Player* this, PlayState* play) {
    if (this->skelAnime.animation == NULL) {
        this->stateFlags2 |= PLAYER_STATE2_4000;
    } else {
        LinkAnimation_Update(play, &this->skelAnime);
        if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00D698) &&
            LinkAnimation_OnFrame(&this->skelAnime, 60.0f)) {
            func_8082E094(this, NA_SE_PL_BOUND);
            func_8082DF8C(this, NA_SE_VO_LI_DAMAGE_S);
        }
    }

    if ((this->unk_AE8++ >= 9) && !func_8082DA90(play)) {
        if (this->unk_AE7 != 0) {
            if (this->unk_AE7 < 0) {
                func_80169FDC(&play->state);
            } else {
                func_80169EFC(&play->state);
            }
            if (!SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
                gSaveContext.respawnFlag = -5;
            }

            play->transitionType = TRANS_TYPE_04;
            play_sound(NA_SE_OC_ABYSS);
        } else {
            play->transitionType = TRANS_TYPE_02;
            gSaveContext.nextTransitionType = TRANS_TYPE_02;
            gSaveContext.seqIndex = 0xFF;
            gSaveContext.nightSeqIndex = 0xFF;
        }

        play->transitionTrigger = TRANS_TRIGGER_START;
    }
}

void func_8085437C(Player* this, PlayState* play) {
    func_808365DC(this, play);
}

void func_8085439C(Player* this, PlayState* play) {
    this->actor.gravity = -1.0f;
    LinkAnimation_Update(play, &this->skelAnime);

    if (this->actor.velocity.y < 0.0f) {
        func_80833AA0(this, play);
    } else if (this->actor.velocity.y < 6.0f) {
        Math_StepToF(&this->linearVelocity, 3.0f, 0.5f);
    }
}

void func_80854430(Player* this, PlayState* play) {
    if (play->unk_1887C < 0) {
        play->unk_1887C = 0;
        func_80839ED0(this, play);
    } else if (this->unk_AE7 == 0) {
        if ((play->sceneNum != SCENE_20SICHITAI) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_B)) {
            play->unk_1887C = 0xA;
            func_80847880(play, this);
            Player_SetAction(play, this, func_80854430, 1);
            this->unk_AE7 = 1;
        } else {
            play->unk_1887C = 0;
            func_80847190(play, this, 0);

            if (play->actorCtx.unk5 & 4) {
                this->stateFlags1 |= PLAYER_STATE1_100000;
                func_8083868C(play, this);
            } else {
                this->stateFlags1 &= ~PLAYER_STATE1_100000;
                if ((play->sceneNum == SCENE_20SICHITAI) &&
                    (func_8012364C(play, this, func_8082FDC4()) == ITEM_PICTO_BOX)) {
                    s32 requiredScopeTemp;

                    play->actorCtx.unk5 |= 4;
                }
            }
        }
    } else if (CHECK_BTN_ANY(D_80862B44->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_R | BTN_A)) {
        play->unk_1887C = -1;
        func_80854614(this, play);
        Player_SetAction(play, this, func_80854430, 0);
        this->unk_AE7 = 0;
    } else {
        play->unk_1887C = 0xA;
        func_80854614(this, play);
    }
}

void func_80854614(Player* this, PlayState* play) {
    this->unk_AA5 = 3;
    func_8083868C(play, this);
    LinkAnimation_Update(play, &this->skelAnime);
    func_8083216C(this, play);
    this->unk_AB2.y = func_80847190(play, this, 1) - this->actor.shape.rot.y;
    this->unk_AA6 |= 0x80;

    if (play->unk_1887C < 0) {
        play->unk_1887C++;
        if (play->unk_1887C == 0) {
            func_80839ED0(this, play);
        }
    }
}

void func_808546D0(Player* this, PlayState* play) {
    if (this->unk_AE7 >= 0) {
        if (this->unk_AE7 < 6) {
            this->unk_AE7++;
        } else {
            this->unk_B48 = (this->unk_AE7 >> 1) * 22.0f;
            if (func_8082DE88(this, 1, 0x64)) {
                this->unk_AE7 = -1;
                EffectSsIcePiece_SpawnBurst(play, &this->actor.world.pos, this->actor.scale.x);
                func_800B8E58(this, NA_SE_PL_ICE_BROKEN);
            }

            if (this->transformation == PLAYER_FORM_ZORA) {
                func_80834104(play, this);
                this->skelAnime.animation = NULL;
                this->unk_AE8 = -0x28;
                this->unk_AE7 = 1;
                this->linearVelocity = 0.0f;
            } else if (play->gameplayFrames % 4 == 0) {
                Player_InflictDamage(play, -1);
            }
        }

        this->stateFlags2 |= PLAYER_STATE2_4000;
    } else if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
        func_808339B4(this, 0x14);
    }
}

void func_80854800(Player* this, PlayState* play) {
    LinkAnimation_Update(play, &this->skelAnime);
    func_808345A8(this);

    if (((this->unk_AE8 % 25) != 0) || func_808339D4(play, this, -1)) {
        if (DECR(this->unk_AE8) == 0) {
            func_80836988(this, play);
        }
    }

    this->shockTimer = 40;
    func_800B8F98(&this->actor, this->ageProperties->unk_92 + (NA_SE_VO_LI_TAKEN_AWAY - SFX_FLAG));
}

void func_808548B8(Player* this, PlayState* play) {
    struct_8085CD30* sp3C = &D_8085CD30[this->meleeWeaponAnimation];

    if (this->skelAnime.curFrame < (this->skelAnime.endFrame - 6.0f)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
    }

    if (func_808401F4(play, this)) {
        return;
    }

    if (this->linearVelocity >= 0.0f) {
        func_8083FCF0(play, this, (this->transformation == PLAYER_FORM_GORON) ? 5.0f : 0.0f, sp3C->unk_C, sp3C->unk_D);
    }

    if ((this->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_LEFT) ||
        (this->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_RIGHT)) {
        this->unk_3D0.unk_00 = 3;
    }

    if ((this->stateFlags2 & PLAYER_STATE2_40000000) && LinkAnimation_OnFrame(&this->skelAnime, 0.0f)) {
        this->linearVelocity = 15.0f;
        this->stateFlags2 &= ~PLAYER_STATE2_40000000;
    }

    if (this->linearVelocity > 12.0f) {
        func_8083FBC4(play, this);
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 5.0f);
    func_8083A548(this);

    if (LinkAnimation_Update(play, &this->skelAnime) ||
        ((this->meleeWeaponAnimation >= PLAYER_MWA_FLIPSLASH_FINISH) &&
         (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_JUMPKICK_FINISH) && (this->skelAnime.curFrame > 2.0f) &&
         func_808333CC(this))) {
        D_80862B48 = this->unk_AE8;

        if (!func_80848570(this, play)) {
            LinkAnimationHeader* anim = func_80123420(this) ? sp3C->unk_8 : sp3C->unk_4;

            func_8082DC38(this);

            if (anim == NULL) {
                this->skelAnime.moveFlags &= ~8;
                func_8085B384(this, play);
            } else {
                u8 moveFlags = this->skelAnime.moveFlags;

                if (this->transformation == PLAYER_FORM_ZORA) {
                    if (func_8083A580(this, play)) {
                        anim = this->unk_284.animation;
                    }
                    this->unk_ADC = 0;
                } else if ((anim == &gameplay_keep_Linkanim_00D728) && (this->modelAnimType != PLAYER_ANIMTYPE_3)) {
                    anim = &gameplay_keep_Linkanim_00D8B0;
                }

                this->skelAnime.moveFlags = 0;
                Player_SetAction(play, this, func_80849FE0, 1);
                func_8082EC9C(play, this, anim);
                this->currentYaw = this->actor.shape.rot.y;
                this->skelAnime.moveFlags = moveFlags;
            }
            this->stateFlags3 |= 8;
        }
    } else if (((this->transformation == PLAYER_FORM_ZORA) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_ZORA_PUNCH_KICK) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_ZORA_JUMPKICK_FINISH)) ||
               ((this->transformation == PLAYER_FORM_GORON) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_GORON_PUNCH_BUTT))) {
        this->unk_AE8 |= CHECK_BTN_ALL(D_80862B44->press.button, BTN_B) ? 1 : 0;
    }
}

void func_80854C70(Player* this, PlayState* play) {
    LinkAnimation_Update(play, &this->skelAnime);
    func_80832F24(this);

    if (this->skelAnime.curFrame >= 6.0f) {
        func_80836988(this, play);
    }
}

void func_80854CD0(f32 arg0, s16* arg1, u8* arg2, u8* arg3, u8* arg4, s16* arg5, u8* arg6, u8* arg7, u8* arg8,
                   s16* arg9, u8* argA, u8* argB, u8* argC) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *arg1 = ((s32)((*arg2 - *arg3) * arg0) + *arg3) - *arg4;
        *arg5 = ((s32)((*arg6 - *arg7) * arg0) + *arg7) - *arg8;
        *arg9 = ((s32)((*argA - *argB) * arg0) + *argB) - *argC;

        arg1++;
        arg2++;
        arg3++;
        arg4++;
        arg5++;
        arg6++;
        arg7++;
        arg8++;
        arg9++;
        argA++;
        argB++;
        argC++;
    }
}

u8 D_8085D844[] = { 0, 0, 0 };

#ifdef NON_MATCHING
void func_80854EFC(PlayState* play, f32 arg1, struct_8085D848_unk_00* arg2) {
    struct_8085D848_unk_00 sp70;
    struct_8085D848_unk_00* var_t0;
    struct_8085D848_unk_00* var_v1;
    u8* var_t3;
    u8* var_t4;
    s32 pad[5];

    sp70.unk_00 = play->envCtx.unk_C4.fogNear;
    sp70.unk_02 = play->envCtx.unk_C4.fogColor[0];
    sp70.unk_03 = play->envCtx.unk_C4.fogColor[1];
    sp70.unk_04 = play->envCtx.unk_C4.fogColor[2];
    sp70.unk_05 = play->envCtx.unk_C4.ambientColor[0];
    sp70.unk_06 = play->envCtx.unk_C4.ambientColor[1];
    sp70.unk_07 = play->envCtx.unk_C4.ambientColor[2];

    if (arg1 <= 1.0f) {
        var_t4 = play->envCtx.unk_C4.diffuseColor1;
        var_v1 = arg2;
        var_t0 = &sp70;
        var_t3 = D_8085D844;
    } else if (arg1 <= 2.0f) {
        arg1 -= 1.0f;
        var_v1 = &arg2[1];
        var_t0 = arg2;
        var_t4 = D_8085D844;
        var_t3 = D_8085D844;
    } else if (arg1 <= 3.0f) {
        arg1 -= 2.0f;
        var_v1 = &arg2[2];
        var_t0 = &arg2[1];
        var_t4 = D_8085D844;
        var_t3 = D_8085D844;
    } else {
        arg1 -= 3.0f;
        var_v1 = &sp70;
        var_t0 = &arg2[2];
        var_t4 = D_8085D844;
        var_t3 = play->envCtx.unk_C4.diffuseColor1;
    }

    play->envCtx.lightSettings.fogNear =
        play->envCtx.unk_C4.fogNear + (-(((s32)((var_v1->unk_00 - var_t0->unk_00) * arg1)) + var_t0->unk_00));

    func_80854CD0(arg1, play->envCtx.lightSettings.fogColor, &var_v1->unk_02, &var_t0->unk_02,
                  play->envCtx.unk_C4.fogColor, play->envCtx.lightSettings.ambientColor, &var_v1->unk_05,
                  &var_t0->unk_05, play->envCtx.unk_C4.ambientColor, play->envCtx.lightSettings.diffuseColor1, var_t3,
                  var_t4, play->envCtx.unk_C4.diffuseColor1);
}
#else
void func_80854EFC(PlayState* play, f32 arg1, struct_8085D848_unk_00 arg2[]);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854EFC.s")
#endif

struct_8085D848 D_8085D848[] = {
    {
        {
            { 0x28A, 0, 0, 0, 0xA, 0, 0x1E },
            { 0x12C, 0xC8, 0xC8, 0xFF, 0, 0, 0 },
            { 0x258, 0, 0, 0, 0, 0, 0xC8 },
        },
        {
            { { -40.0f, 20.0f, -10.0f }, 0x78, 0xC8, 0xFF, 0x3E8 },
            { { 0.0f, -10.0f, 0.0f }, 0xFF, 0xFF, 0xFF, 0x1388 },
            { { -10.0f, 4.0f, 3.0f }, 0xC8, 0xC8, 0xFF, 0x1388 },
        },
    },
    {
        {
            { 0x28A, 0, 0, 0, 0xA, 0, 0x1E },
            { 0x12C, 0xC8, 0xC8, 0xFF, 0, 0, 0 },
            { 0x258, 0, 0, 0, 0, 0, 0xC8 },
        },
        {
            { { 0.0f, 0.0f, 5.0f }, 0x9B, 0xFF, 0xFF, 0x64 },
            { { 0.0f, 0.0f, 5.0f }, 0x9B, 0xFF, 0xFF, 0x64 },
            { { 0.0f, 0.0f, 5.0f }, 0x9B, 0xFF, 0xFF, 0x64 },
        },
    },
};

void func_808550D0(PlayState* play, Player* this, f32 arg2, f32 arg3, s32 arg4) {
    struct_8085D848* temp_a2 = &D_8085D848[arg4];
    struct_8085D848_unk_18* var_s0;
    Vec3f sp3C;

    var_s0 = temp_a2->unk_18;
    func_80854EFC(play, arg2, temp_a2->unk_00);

    if (arg3 > 2.0f) {
        arg3 -= 2.0f;
        var_s0 += 2;
    } else if (arg3 > 1.0f) {
        arg3 -= 1.0f;
        var_s0 += 1;
    }

    func_80835BC8(this, &this->actor.world.pos, &var_s0->unk_00, &sp3C);
    Lights_PointNoGlowSetInfo(&this->lightInfo, sp3C.x, sp3C.y, sp3C.z, var_s0->unk_0C, var_s0->unk_0D, var_s0->unk_0E,
                              var_s0->unk_10 * arg3);
}

AnimSfxEntry D_8085D8F0[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 2, NA_SE_PL_PUT_OUT_ITEM, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 4, NA_SE_IT_SET_TRANSFORM_MASK, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 11, NA_SE_PL_FREEZE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 30, NA_SE_PL_TRANSFORM_VOICE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 20, NA_SE_IT_TRANSFORM_MASK_BROKEN, STOP),
};

AnimSfxEntry D_8085D904[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 8, NA_SE_IT_SET_TRANSFORM_MASK, STOP),
};

void func_80855218(PlayState* play, Player* this, UNK_PTR arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime) && (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0C8)) {
        func_8082DB60(play, this, &gameplay_keep_Linkanim_00D0D0);
    } else if ((this->skelAnime.animation == &gameplay_keep_Linkanim_00D0C8) ||
               (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0D0)) {
        if (this->unk_AE7 >= 0x3A) {
            Math_StepToS(&this->unk_AE8, 0xFF, 0x32);
        }

        if (this->unk_AE7 >= 0x40) {
            Math_StepToF(&this->unk_B10[2], 0.0f, 0.015f);
        } else if (this->unk_AE7 >= 0xE) {
            Math_StepToF(&this->unk_B10[2], 0.3f, 0.3f);
        }

        if (this->unk_AE7 >= 0x42) {
            Math_StepToF(&this->unk_B10[3], 0.0f, 0.02f);
        } else if (this->unk_AE7 >= 0x10) {
            Math_StepToF(&this->unk_B10[3], -0.1f, 0.1f);
        }

        if ((MREG(64) == 0) && (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0C8)) {
            Player_PlayAnimSfx(this, D_8085D8F0);
        }
    } else {
        if (this->unk_AE7 >= 0x14) {
            Math_StepToS(&this->unk_AE8, 0xFF, 0x14);
        }

        if (MREG(64) == 0) {
            Player_PlayAnimSfx(this, D_8085D904);
            if (this->unk_AE7 == 0xF) {
                func_800B8E58(this, NA_SE_PL_FACE_CHANGE);
            }
        }
    }
}

u16 D_8085D908[] = { 0x1E80, 0x1E20, 0x1E40, 0x1E10 };
struct_8085D910 D_8085D910[] = { { 0x10, 0xA, 0x3B, 0x3F }, { 9, 0x32, 0xA, 0xD } };

#ifdef NON_EQUIVALENT
void func_808553F4(Player* this, PlayState* play) {
    struct_8085D910* sp4C;
    s32 sp48;
    s32 temp_t7;
    s32 var_v0_2;
    s32 var_v0_3;
    s8 temp_a0;
    u16 temp_t8;

    sp4C = D_8085D910;
    sp48 = 0;
    func_808323C0(this, play->playerActorCsIds[5]);
    D_80862B44 = play->state.input;

    Camera_ChangeMode(play->cameraPtrs[play->activeCamId],
                      (this->transformation == PLAYER_FORM_HUMAN) ? CAM_MODE_NORMAL : CAM_MODE_JUMP);
    this->stateFlags2 |= 0x40;
    this->actor.shape.rot.y = Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamId]) + 0x8000;
    func_80855218(play, this, &sp4C);

    if (this->unk_AE7 == 0x14) {
        func_80165DCC(0x64);
    }

    if (MREG(64) != 0) {
        MREG(68) += MREG(64);
        if (MREG(68) > 0xFF) {
            MREG(68) = 0xFF;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->unk_AE7 = 0;
            func_80165DF0();
            temp_t8 = D_8085D908[gSaveContext.save.playerForm];
            temp_t7 = (s32)temp_t8 >> 8;
            gSaveContext.save.weekEventReg[temp_t7] |= temp_t8;
        }
    } else {
        temp_a0 = this->unk_AE7;

        var_v0_2 = (this->transformation == 4) ? 0x53 : 0x37;
        this->unk_AE7 = temp_a0 + 1;
#if 0
        if (var_v0_2 >= temp_a0) {
            if (this->unk_AE7 >= 5) {
                if ((this->transformation != 4) || ( var_v0_3 = (D_8085D908[gSaveContext.save.playerForm] & 0xFF & gSaveContext.save.weekEventReg[(s32) D_8085D908[gSaveContext.save.playerForm] >> 8]) != 0, (var_v0_3 != 0))) {
                    var_v0_3 = (D_80862B44->press.button & 0xC00F) != 0;
                }
                sp48 = var_v0_3;
                if (var_v0_3 != 0) {
                    goto block_17;
                }
            }
        } else {
block_17:
#endif
        if ((var_v0_2 < temp_a0) ||
            ((this->unk_AE7 >= 5) &&
             (((this->transformation != 4) ||
               (var_v0_3 = (D_8085D908[gSaveContext.save.playerForm] & 0xFF &
                            gSaveContext.save.weekEventReg[(s32)D_8085D908[gSaveContext.save.playerForm] >> 8]) != 0,
                (var_v0_3 != 0))) &&
              (sp48 = var_v0_3 = (D_80862B44->press.button & 0xC00F) != 0)))) {
            MREG(64) = 0x2D;
            MREG(65) = 0xDC;
            MREG(66) = 0xDC;
            MREG(67) = 0xDC;
            MREG(68) = 0;

            if (sp48 != 0) {
                if (ActorCutscene_GetCurrentIndex() == this->unk_A86) {
                    func_800E0348(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(this->unk_A86)));
                }

                if (this->transformation == 4) {
                    Audio_StopSfxById(0x9AAU);
                    Audio_StopSfxById(0x1858U);
                } else {
                    Audio_StopSfxById(0x9A4U);
                }
            }
            func_800B8E58(this, 0x484FU);
        }
    }

    if (this->unk_AE7 >= sp4C->unk_0) {
        if (this->unk_AE7 < sp4C->unk_2) {
            Math_StepToF(&this->unk_B10[4], 1.0f, sp4C->unk_1 / 100.0f);
        } else if (this->unk_AE7 < (s32)sp4C->unk_3) {
            if (this->unk_AE7 == sp4C->unk_2) {
                func_801000CC(NA_SE_EV_LIGHTNING_HARD);
            }

            Math_StepToF(&this->unk_B10[4], 2.0f, 0.5f);
        } else {
            Math_StepToF(&this->unk_B10[4], 3.0f, 0.2f);
        }
    }

    if (this->unk_AE7 >= 0x10) {
        if (this->unk_AE7 < 0x40) {
            Math_StepToF(&this->unk_B10[5], 1.0f, 0.2f);
        } else if (this->unk_AE7 < 0x37) {
            Math_StepToF(&this->unk_B10[5], 2.0f, 1.0f);
        } else {
            Math_StepToF(&this->unk_B10[5], 3.0f, 0.55f);
        }
    }

    func_808550D0(play, this, this->unk_B10[4], this->unk_B10[5], (this->transformation == 4) ? 0 : 1);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808553F4.s")
#endif

void func_80855818(Player* this, PlayState* play) {
    Camera_ChangeMode(play->cameraPtrs[play->activeCamId],
                      (this->prevMask == PLAYER_MASK_NONE) ? CAM_MODE_NORMAL : CAM_MODE_JUMP);

    if (MREG(64) != 0) {
        MREG(68) -= MREG(64);
        if (MREG(68) < 0) {
            MREG(64) = 0;
            MREG(68) = 0;
        }
    }

    if (this->unk_AE7++ < 4) {
        if ((this->prevMask == PLAYER_MASK_NONE) && (this->unk_AE7 == 4)) {
            LinkAnimation_Change(play, &this->skelAnime, func_8082ED20(this), 1.0f, 0.0f, 20.0f, ANIMMODE_ONCE, 20.0f);
        }
    } else {
        s32 pad;
        f32 dist;
        s16 angle;

        func_800FF3A0(&dist, &angle, play->state.input);
        if (LinkAnimation_Update(play, &this->skelAnime) || ((this->unk_AE7 >= 0xB) && (dist != 0.0f))) {
            if (MREG(64) == 0) {
                this->stateFlags1 &= ~PLAYER_STATE1_2;
                this->prevMask = this->currentMask;
                this->unk_A86 = play->playerActorCsIds[5];
                func_80838760(this);
                play->envCtx.lightSettings = D_80862B50;
                func_8085B384(this, play);
                return;
            }
        }

        Math_StepToF(&this->unk_B10[5], 4.0f, 0.2f);
    }

    func_808550D0(play, this, 0, this->unk_B10[5], (this->prevMask == PLAYER_MASK_NONE) ? 0 : 1);
}

void func_80855A7C(Player* this, PlayState* play) {
    if (this->unk_AE8++ >= 0x5B) {
        play->msgCtx.ocarinaMode = 4;
        func_8085B384(this, play);
        return;
    }
    if (this->unk_AE8 == 0xA) {
        func_80848640(play, this);
    }
}

// giant mask
void func_80855AF4(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    func_80855218(play, this, 0);
    this->unk_AE7++;

    if (!(this->stateFlags1 & PLAYER_STATE1_100)) {
        this->prevMask = this->currentMask;
        gSaveContext.save.equippedMask = this->currentMask = PLAYER_MASK_GIANT;
        func_80115DB4(play, 0, 6);
        this->currentBoots = PLAYER_BOOTS_GIANT;
        this->prevBoots = PLAYER_BOOTS_GIANT;
        func_80123140(play, this);
        func_8085B384(this, play);
    }
}

void func_80855B9C(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    LinkAnimation_Update(play, &this->skelAnime);

    if (!(this->stateFlags1 & PLAYER_STATE1_100)) {
        this->prevMask = this->currentMask;

        gSaveContext.save.equippedMask = this->currentMask = PLAYER_MASK_NONE;

        this->currentBoots = PLAYER_BOOTS_HYLIAN;
        this->prevBoots = PLAYER_BOOTS_HYLIAN;
        func_80123140(play, this);
        func_8085B384(this, play);
    }
}

void func_80855C28(Player* this, PlayState* play) {
    s16 sp3E;
    s32 pad;
    LinkAnimationHeader* sp34;
    s32 var_a0;

    func_808323C0(this, play->playerActorCsIds[4]);
    sp3E = BINANG_SUB(this->actor.shape.rot.y, this->actor.world.rot.y);

    var_a0 = 0;
    if ((this->actor.floorHeight - this->actor.world.pos.y) < 60.0f) {
        Math_StepToF(&this->unk_B10[5], 200.0f, 150.0f);
        var_a0 = Math_StepToS(&this->unk_AE8, 0xFA0, 0x15E);
    }

    this->actor.shape.rot.y += this->unk_AE8;
    this->skelAnime.jointTable->x = 0;
    this->skelAnime.jointTable->z = 0;
    this->unk_ABC += this->unk_B10[5];

    if (this->unk_ABC >= 0.0f) {
        this->unk_ABC = 0.0f;
        if ((var_a0 != 0) && (sp3E < 0)) {
            if (BINANG_SUB(this->actor.shape.rot.y, this->actor.world.rot.y) >= 0) {
                this->actor.shape.rot.y = this->actor.world.rot.y;
                func_80838760(this);
                if (PLAYER_GET_INITMODE(&this->actor) == PLAYER_INITMODE_8) {
                    sp34 = D_8085D17C[this->transformation];
                    func_80836A5C(this, play);
                    LinkAnimation_Change(play, &this->skelAnime, sp34, -2.0f / 3.0f, Animation_GetLastFrame(sp34), 0.0f,
                                         ANIMMODE_ONCE, -6.0f);
                } else {
                    func_80839E74(this, play);
                }
            }
        }
    } else if (this->unk_AE7 == 0) {
        func_800B8E58(this, NA_SE_PL_WARP_PLATE_OUT);
        this->unk_AE7 = 1;
    }
}

void func_80855E08(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (LinkAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00D9D0);
    }

    Math_Vec3f_Sum(&this->actor.world.pos, &this->actor.velocity, &this->actor.world.pos);
    if (func_80831124(play, this)) {
        f32 var_fv0;

        Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
        func_80843178(play, this);

        var_fv0 = this->actor.world.pos.y - this->actor.floorHeight;
        var_fv0 = CLAMP_MAX(var_fv0, 20.0f);

        this->actor.world.pos.y = this->actor.world.pos.y - var_fv0;
        this->actor.shape.rot.x = 0;
        this->linearVelocity = 1.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        func_80833AA0(this, play);
        this->stateFlags2 &= ~PLAYER_STATE2_400;
        this->actor.bgCheckFlags |= 1;
        this->stateFlags3 |= PLAYER_STATE3_10000;
    } else if ((this->skelAnime.animation != &gameplay_keep_Linkanim_00D9C8) || (this->skelAnime.curFrame >= 4.0f)) {
        this->actor.gravity = 0.0f;
        Math_ScaledStepToS(&this->actor.shape.rot.x, this->actor.world.rot.x, 0x800);
        Player_RequestRumble(play, this, 100, 2, 100, SQ(0));
    }
}

void func_80855F9C(PlayState* play, Player* this) {
    f32 sp24;
    s16 sp22;

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_80832F78(this, &sp24, &sp22, 0.018f, play);
    Math_ScaledStepToS(&this->currentYaw, sp22, 0x258);
}

s32 func_80856000(PlayState* play, Player* this) {
    CollisionPoly* poly;
    s32 bgId;
    Vec3f pos;
    f32 sp28;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y - 20.0f;
    pos.z = this->actor.world.pos.z;
    return BgCheck_EntityCheckCeiling(&play->colCtx, &sp28, &pos, 30.0f, &poly, &bgId, &this->actor);
}

void func_80856074(PlayState* play, Player* this) {
    if (func_8083F8A8(play, this, 12.0f, 4, 0.0f, 10, 50, true)) {
        EffectSsHahen_SpawnBurst(play, &this->actor.world.pos, 3.0f, 0, 4, 8, 2, -1, 10, NULL);
    }
}

void func_80856110(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4, s16 scale, s16 scaleStep, s16 life) {
    static Vec3f D_8085D918 = { 0.0f, 0.5f, 0.0f };
    static Vec3f D_8085D924 = { 0.0f, 0.5f, 0.0f };
    static Color_RGBA8 D_8085D930 = { 255, 255, 55, 255 };
    static Color_RGBA8 D_8085D934 = { 100, 50, 0, 0 };
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + arg2;
    pos.z = this->actor.world.pos.z;

    D_8085D918.y = arg3;
    D_8085D924.y = arg4;

    func_800B0EB0(play, &pos, &D_8085D918, &D_8085D924, &D_8085D930, &D_8085D934, scale, scaleStep, life);
}

void func_808561B0(Player* this, PlayState* play) {
    DynaPolyActor* dyna;
    s32 aux = 0xAE;
    f32 temp_fv0_2; // sp3C
    s32 sp38;
    s32 var_v1; // sp34

    LinkAnimation_Update(play, &this->skelAnime);

    if (func_80838A90(this, play)) {
        return;
    }

    if (this->unk_AE7 == 0) {
        this->unk_ABC += this->unk_B48;
        if (this->unk_ABC < -1000.0f) {
            this->unk_ABC = -1000.0f;
            this->unk_AE7 = 1;
            this->unk_B48 = 0.0f;
        }
        func_80856074(play, this);
    } else if (this->unk_AE7 == 1) {
        this->unk_B48 += -22.0f;
        if (this->unk_B48 < -170.0f) {
            this->unk_B48 = -170.0f;
        }
        this->unk_ABC += this->unk_B48;
        if (this->unk_ABC < -3900.0f) {
            this->unk_ABC = -3900.0f;
            this->unk_AE7 = 2;
            this->actor.shape.rot.y = Camera_GetInputDirYaw(play->cameraPtrs[play->activeCamId]);
            this->actor.scale.y = 0.01f;
            this->currentYaw = this->actor.world.rot.y = this->actor.shape.rot.y;
        } else {
            temp_fv0_2 = Math_SinS((1000.0f + this->unk_ABC) * (-30.0f)) * 0.004f;
            this->actor.scale.y = 0.01f + temp_fv0_2;
            this->actor.scale.z = this->actor.scale.x = 0.01f - (this->unk_B48 * -0.000015f);

            this->actor.shape.rot.y += (s16)(this->unk_B48 * 130.0f);
            if (this->actor.floorBgId != BGCHECK_SCENE) {
                dyna = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

                if (dyna != NULL) {
                    Math_Vec3f_StepToXZ(&this->actor.world.pos, &dyna->actor.world.pos, 1.0f);
                }
            }
        }

        func_80856074(play, this);
    } else if (this->unk_AE7 == 2) {
        if (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) {
            if (func_80856000(play, this)) {
                this->unk_AE8 = 0;
            } else {
                this->unk_AE7 = 3;
                if (this->unk_AE8 >= 0xA) {
                    this->unk_B48 = 2700.0f;
                } else {
                    this->unk_B48 = 1450.0f;
                }
                func_8082E1F0(this, NA_SE_PL_DEKUNUTS_OUT_GRD);
            }
        } else if (this->unk_AE8 < 0xF) {
            this->unk_AE8++;
            if (this->unk_AE8 == 0xA) {
                func_80856110(play, this, 20.0f, 3.8f, -0.1f, 0x8C, 0x17, 0xF);
            }
        }
        func_80855F9C(play, this);
    } else {
        this->unk_ABC += this->unk_B48;

        temp_fv0_2 = this->unk_ABC;
        if (temp_fv0_2 >= 0.0f) {
            f32 var_fv0; // sp30

            sp38 = (this->unk_AE8 >= 0xA);
            var_v1 = -1;
            var_fv0 = this->unk_B48 * this->actor.scale.y;
            if (this->actor.floorBgId != BGCHECK_SCENE) {
                dyna = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);
                var_v1 = 0;
                if ((dyna != NULL) && (dyna->actor.id == ACTOR_OBJ_ETCETERA) && (dyna->actor.params & 0x100)) {
                    var_v1 = 1;
                    var_fv0 *= (f32)aux / 100.0f;
                }
            }

            Math_Vec3f_Copy(this->unk_AF0, &this->actor.world.pos);
            this->unk_ABC = 0.0f;
            this->actor.world.pos.y += temp_fv0_2 * this->actor.scale.y;
            func_80834DB8(this, &gameplay_keep_Linkanim_00E2D0, var_fv0, play);
            Player_SetAction(play, this, func_80856918, 1);
            this->boomerangActor = NULL;

            this->stateFlags3 |= PLAYER_STATE3_200;
            if (sp38 != 0) {
                this->stateFlags3 |= PLAYER_STATE3_2000;
            }
            if (var_v1 < 0) {
                this->stateFlags3 |= PLAYER_STATE3_40000;
            }

            this->unk_AE7 = var_v1;
            this->unk_AE8 = 0x270F;
            func_8082F0E4(this, 0x20000, 2, 20);
        } else if (this->unk_ABC < 0.0f) {
            func_80856074(play, this);
        }
    }

    if (this->unk_ABC < -1500.0f) {
        this->stateFlags3 |= PLAYER_STATE3_100;
        if (this->unk_B86[0] < 8) {
            this->unk_B86[0]++;
            if (this->unk_B86[0] == 8) {
                func_8082E1F0(this, NA_SE_PL_DEKUNUTS_BUD);
            }
        }
    }
}

void func_808566C0(PlayState* play, Player* this, s32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 life) {
    Color_RGBA8 primColor = { 255, 200, 200, 0 };
    Color_RGBA8 envColor = { 255, 255, 0, 0 };
    static Vec3f D_8085D940 = { 0.0f, 0.3f, 0.0f };
    static Vec3f D_8085D94C = { 0.0f, -0.025f, 0.0f };
    Vec3f pos;
    s32 scale;
    f32 sp34;
    Vec3f* temp_v0;

    if (Rand_ZeroOne() < 0.5f) {
        sp34 = -1.0f;
    } else {
        sp34 = 1.0f;
    }

    D_8085D940.x = (Rand_ZeroFloat(arg4) + arg3) * sp34;
    D_8085D94C.x = arg5 * sp34;
    if (Rand_ZeroOne() < 0.5f) {
        sp34 = -1.0f;
    } else {
        sp34 = 1.0f;
    }

    temp_v0 = &this->bodyPartsPos[arg2];
    D_8085D940.z = (Rand_ZeroFloat(arg4) + arg3) * sp34;
    D_8085D94C.z = arg5 * sp34;
    pos.x = temp_v0->x;
    pos.y = Rand_ZeroFloat(15.0f) + temp_v0->y;
    pos.z = temp_v0->z;
    if (Rand_ZeroOne() < 0.5f) {
        scale = 2000;
    } else {
        scale = -150;
    }

    EffectSsKirakira_SpawnDispersed(play, &pos, &D_8085D940, &D_8085D94C, &primColor, &envColor, scale, life);
}

void func_8085687C(Player* this) {
}

s32 func_80856888(f32* arg0, f32 arg1, f32 arg2) {
    if (arg2 != 0.0f) {
        if (arg1 < *arg0) {
            arg2 = -arg2;
        }

        *arg0 += arg2;
        if (((*arg0 - arg1) * arg2) >= 0.0f) {
            *arg0 = arg1;
            return true;
        }
    } else if (arg1 == *arg0) {
        return true;
    }

    return false;
}

f32 D_8085D958[] = { 600.0f, 960.0f };
Vec3f D_8085D960 = { -30.0f, 50.0f, 0.0f };
Vec3f D_8085D96C = { 30.0f, 50.0f, 0.0f };

void func_80856918(Player* this, PlayState* play) {
    if ((this->boomerangActor != NULL) && (this->boomerangActor->update == NULL)) {
        this->boomerangActor = NULL;
    }

    if (func_80838A90(this, play)) {
        return;
    }

    if (this->actor.bgCheckFlags & 1) {
        func_80837134(play, this);
        return;
    }

    if ((this->actor.velocity.y > 0.0f) && (this->stateFlags3 & PLAYER_STATE3_200)) {
        this->actor.terminalVelocity = -20.0f;
        this->actor.gravity = -5.5f;
        func_8082F0E4(this, 0x20000, 2, 20);
        func_80856110(play, this, 0.0f, 0.0f, -1.0f, 0x1F4, 0, 8);

        if (this->actor.bgCheckFlags & 0x10) {
            func_80833AA0(this, play);
        }
    } else if (!(this->stateFlags3 & PLAYER_STATE3_2000)) {
        func_80833AA0(this, play);
    } else if (this->stateFlags3 & PLAYER_STATE3_200) {
        if (this->actor.velocity.y < 0.0f) {
            if (this->unk_AE7 < 0) {
                func_80833AA0(this, play);
            } else {
                LinkAnimation_Update(play, &this->skelAnime);
                if (this->skelAnime.curFrame > 6.0f) {
                    this->actor.velocity.y = 6.0f;
                    this->stateFlags3 &= ~PLAYER_STATE3_200;
                    this->stateFlags3 |= PLAYER_STATE3_1000000;
                    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_OPEN);
                    func_8019FD90(4, 2);
                }
            }
        }

        this->actor.terminalVelocity = -10.0f;
        this->actor.gravity = -0.5f;
        func_8082F09C(this);
    } else if (CHECK_BTN_ALL(D_80862B44->press.button, BTN_A)) {
        func_808355D8(play, this, &gameplay_keep_Linkanim_00E2D8);
    } else {
        s16 temp_a0;
        f32 temp_fv1; // sp78
        s16 sp76;
        s16 var_v1;
        s16 var_a1;
        f32 sp6C;
        f32 sp68;
        s16 sp66;
        s16 temp_ft0;
        s32 temp;
        s16 var_v1_4;

        this->linearVelocity = sqrtf(SQXZ(this->actor.velocity));
        if (this->linearVelocity != 0.0f) {
            var_a1 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);

            temp_a0 = this->actor.shape.rot.y - var_a1;
            if (ABS_ALT(temp_a0) > 0x4000) {
                this->linearVelocity = -this->linearVelocity;
                var_a1 = var_a1 + 0x8000;
            }
            this->currentYaw = var_a1;
        }

        if (this->windSpeed != 0.0f) {
            Math_SmoothStepToS(&this->unk_B8C, this->windAngleX, 3, 0x1F40, 0x190);
        }

        func_8085687C(this);

        if (this->unk_AE8 != 0) {
            this->unk_AE8--;
        }

        temp_fv1 = D_8085D958[this->unk_AE7] - Math_Vec3f_DistXZ(&this->actor.world.pos, this->unk_AF0);
        LinkAnimation_Update(play, &this->skelAnime);

        if ((this->unk_AE8 != 0) && (temp_fv1 > 300.0f)) {
            sp76 = 0x1770;
            if (this->skelAnime.animation != &gameplay_keep_Linkanim_00E2D0) {
                func_8082E5EC(play, this, &gameplay_keep_Linkanim_00E2D8);
            } else if (LinkAnimation_OnFrame(&this->skelAnime, 8.0f)) {
                s32 i;

                func_80835BC8(this, &this->actor.world.pos, &D_8085D960, &this->bodyPartsPos[0xC]);
                func_80835BC8(this, &this->actor.world.pos, &D_8085D96C, &this->bodyPartsPos[0xF]);

                for (i = 0; i < 0xD; i++) {
                    func_808566C0(play, this, 0xC, 0.6f, 1.0f, 0.8f, 0x11);
                    func_808566C0(play, this, 0xF, 0.6f, 1.0f, 0.8f, 0x11);
                }
            }
        } else if ((this->unk_AE8 == 0) || (temp_fv1 < 0.0f)) {
            sp76 = 0;
            func_808355D8(play, this, &gameplay_keep_Linkanim_00E2E8);
        } else {
            sp76 = 0x1770 - (s32)((300.0f - temp_fv1) * 10.0f);

            if (this->skelAnime.animation != &gameplay_keep_Linkanim_00E278) {
                func_8082E55C(play, this, &gameplay_keep_Linkanim_00E278);
            } else if (LinkAnimation_OnFrame(&this->skelAnime, 6.0f)) {
                func_800B8E58(this, NA_SE_PL_DEKUNUTS_STRUGGLE);
            }
        }

        Math_AsymStepToS(&this->unk_B86[1], sp76, 0x190, 0x190);

        this->unk_B8A += this->unk_B86[1];
        temp = ABS_ALT(this->unk_B86[1]);
        if (temp > 0xFA0) {
            this->unk_B66 += (u8)(ABS_ALT(this->unk_B86[1]) * 0.01f);
        }

        if (this->unk_B66 > 0xC8) {
            this->unk_B66 -= 0xC8;
            func_808566C0(play, this, 0xC, 0.0f, 1.0f, 0.0f, 0x20);
            func_808566C0(play, this, 0xF, 0.0f, 1.0f, 0.0f, 0x20);
        }

        func_8019FCB8(&this->actor.projectedPos, 0x1851, 2.0f * (this->unk_B86[1] * (1.0f / 6000.0f)));
        if ((this->boomerangActor == NULL) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_B)) {
            if (AMMO(ITEM_NUT) == 0) {
                play_sound(NA_SE_SY_ERROR);
            } else {
                this->boomerangActor =
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW, this->bodyPartsPos[0].x, this->bodyPartsPos[0].y,
                                this->bodyPartsPos[0].z, (s16)-1, (s16)0, (s16)0, 8);
                if (this->boomerangActor != NULL) {
                    this->boomerangActor->velocity.x = this->actor.velocity.x * 1.5f;
                    this->boomerangActor->velocity.z = this->actor.velocity.z * 1.5f;
                    Inventory_ChangeAmmo(ITEM_NUT, -1);
                    Actor_PlaySfxAtPos(this->boomerangActor, NA_SE_PL_DEKUNUTS_DROP_BOMB);
                }
            }
        }

        if (this->actor.velocity.y < 0.0f) {
            if (sp76 != 0) {
                this->actor.terminalVelocity = -0.38f;
                this->actor.gravity = -0.2f;
            } else {
                this->actor.terminalVelocity = (this->unk_B86[1] * 0.0033f) + -20.0f;
                this->actor.gravity = (this->unk_B86[1] * 0.00004f) + (REG(68) / 100.0f);
            }
        }

        this->fallStartHeight = this->actor.world.pos.y;
        func_80832F78(this, &sp6C, &sp66, 0.0f, play);
        if (sp6C == 0.0f) {
            sp68 = 0.1f;
        } else {
            s16 temp_v0_6 = this->currentYaw - sp66;

            if (ABS_ALT(temp_v0_6) > 0x4000) {
                sp6C = -sp6C;
                sp66 += 0x8000;
            }
            sp68 = 0.25f;
        }

        Math_SmoothStepToS(&this->unk_B8C, sp6C * 600.0f, 8, 0xFA0, 0x64);
        Math_ScaledStepToS(&this->currentYaw, sp66, 0xFA);

        temp_ft0 = BINANG_SUB(sp66, this->currentYaw) * -2.0f;
        temp_ft0 = CLAMP(temp_ft0, -0x1F40, 0x1F40);
        Math_SmoothStepToS(&this->unk_B8E, temp_ft0, 0x14, 0x320, 0x14);
        sp6C = (sp6C * (this->unk_B86[1] * 0.0004f)) * fabsf(Math_SinS(this->unk_B8C));
        func_80856888(&this->linearVelocity, sp6C, sp68);

        sp6C = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y));
        if (sp6C > 8.0f) {
            sp6C = 8.0f / sp6C;
            this->linearVelocity *= sp6C;
            this->actor.velocity.y *= sp6C;
        }
    }

    func_808378FC(play, this);
}

// Deku spinning related
void func_808573A4(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20 | PLAYER_STATE2_40;

    LinkAnimation_Update(play, &this->skelAnime);
    func_8082F0E4(this, 0x8000, 1, 30);

    if (!func_80838A90(this, play)) {
        s16 prevYaw = this->currentYaw;
        f32 sp40;
        s16 sp3E;

        func_80832F78(this, &sp40, &sp3E, 0.018f, play);
        sp40 *= 1.0f - (0.9f * ((11100.0f - this->unk_B10[0]) / 11100.0f));
        if (!func_8083A4A4(this, &sp40, &sp3E, REG(43) / 100.0f)) {
            func_8083CB58(this, sp40, sp3E);
        }

        this->unk_B10[0] += -800.0f;
        this->actor.shape.rot.y += (s16)((s16)this->unk_B10[0] + (s16)(this->currentYaw - prevYaw));

        if (Math_StepToF(&this->unk_B10[1], 0.0f, this->unk_B10[0])) {
            this->actor.shape.rot.y = this->currentYaw;
            func_8083B2E4(this, play);
        } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E270) {
            this->stateFlags3 |= PLAYER_STATE3_100000;

            if (this->unk_B10[1] < 0.0f) {
                func_8082E438(play, this, func_8082ED20(this));
            }
        }

        func_808566C0(play, this, 0, 1.0f, 0.5f, 0.0f, 32);

        if (this->unk_B10[0] > 9500.0f) {
            func_8083F8A8(play, this, 2.0f, 1, 2.5f, 10, 18, true);
        }

        func_800AE930(&play->colCtx, Effect_GetByIndex(this->meleeWeaponEffectIndex[2]), &this->actor.world.pos, 2.0f,
                      this->currentYaw, this->actor.floorPoly, this->actor.floorBgId);
        func_800B8F98(&this->actor, func_8082E078(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG));
    }
}

void func_80857640(Player* this, f32 arg1, s32 arg2) {
    func_80834CD0(this, arg1, NA_SE_VO_LI_SWORD_N);
    func_800B8E58(this, NA_SE_PL_GORON_BALLJUMP);
    func_8082DABC(this);
    if (this->unk_AE8 < arg2) {
        this->unk_AE8 = arg2;
    }
    this->unk_AE7 = 1;
    this->unk_B48 = 1.0f;
}

void func_808576BC(PlayState* play, Player* this) {
    s32 var_v0 = ((this->actor.velocity.z * Math_CosS(this->currentYaw)) +
                  (this->actor.velocity.x * Math_SinS(this->currentYaw))) *
                 800.0f;

    var_v0 -= this->unk_AE8;
    var_v0 = ABS_ALT(var_v0);

    if (var_v0 <= 0x7D0) {
        return;
    }

    if (var_v0 > 0x1770) {
        func_800B8F98(&this->actor, NA_SE_PL_GORON_SLIP - SFX_FLAG);
    }

    if (func_8083F8A8(play, this, 12.0f, -1 - (var_v0 >> 0xC), (var_v0 >> 0xA) + 1.0f, (var_v0 >> 7) + 160, 20, true)) {
        func_800B8E58(this, (this->unk_B72 == NA_SE_PL_WALK_SNOW - SFX_FLAG) ? NA_SE_PL_ROLL_SNOW_DUST - SFX_FLAG
                                                                             : NA_SE_PL_ROLL_DUST - SFX_FLAG);
    }
}

void func_808577E0(Player* this) {
    f32 temp_fa1 = ABS_ALT(this->unk_AE8) * 0.00004f;

    if (this->unk_ABC < temp_fa1) {
        this->unk_B48 += 0.08f;
    } else {
        this->unk_B48 += -0.07f;
    }

    this->unk_B48 = CLAMP(this->unk_B48, -0.2f, 0.14f);
    if (fabsf(this->unk_B48) < 0.12f) {
        if (Math_StepUntilF(&this->unk_ABC, temp_fa1, this->unk_B48)) {
            this->unk_B48 = 0.0f;
        }
    } else {
        this->unk_ABC += this->unk_B48;
        this->unk_ABC = CLAMP(this->unk_ABC, -0.7f, 0.3f);
    }
}

s32 func_80857950(PlayState* play, Player* this) {
    if (((this->unk_B86[1] == 0) && !CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A)) ||
        ((this->unk_AE7 == 3) && (this->actor.velocity.y < 0.0f))) {
        Player_SetAction(play, this, func_80849FE0, 1);
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
        LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E208, -2.0f / 3.0f, 7.0f, 0.0f,
                             ANIMMODE_ONCE, 0.0f);
        func_800B8E58(this, NA_SE_PL_BALL_TO_GORON);
        return true;
    }

    return false;
}

s32 func_80857A44(PlayState* play, Player* this) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);

        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.bgCheckFlags |= 0x800;
        this->unk_AE7 = 4;
        this->actor.shape.shadowScale = 30.0f;
        this->unk_AE8 = this->linearVelocity * 500.0f;
        this->unk_B08[0] = this->linearVelocity;
        this->unk_B08[1] = 0.0f;
        this->actor.home.rot.y = this->currentYaw;

        return true;
    }

    return false;
}

void func_80857AEC(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & 2) {
        this->unk_B08[1] += this->unk_B08[0] * 0.05f;

        if (this->unk_B86[1] == 0) {
            if (this->unk_AE7 == 1) {
                this->unk_AE7 = 2;
                func_8083FE90(play, this, NA_SE_PL_GORON_PUNCH);
                play->actorCtx.unk2 = 4;
                EffectSsBlast_SpawnWhiteShockwave(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
                this->unk_AE8 = 0;
                this->unk_B08[0] = 0.0f;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, 0, 0, 0);
            } else {
                this->unk_AE7 = 4;
            }
        }

        func_8082E1BC(this);
    }
}

Vec3f D_8085D978 = { -30.0f, 60.0f, 0.0f };
Vec3f D_8085D984 = { 30.0f, 60.0f, 0.0f };

#ifdef NON_EQUIVALENT
void func_80857BE8(Player* this, PlayState* play) {
    f32 spE4;
    s16 spE2;
    s32 spDC;
    s32 temp_a3; // spD8
    f32 spCC;
    s16 spCA;
    s16 var_a2_2; // spC8
    s32 var_v1_3; // spC0
    f32 spBC;
    f32 var_fa1_2; // spB8
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    Vec3f sp94;
    s16 sp92;
    s16 sp90;
    s16 temp_a0;   // sp8E
    f32 temp_fa0;  // sp88
    f32 var_fv1_7; // sp84
    f32 sp80;
    s16 temp_ft1_2; // sp7C
    Vec3f sp70;
    f32 sp6C;
    f32 var_fv0; // sp54
    f32 temp_fa0_3;
    f32 temp_fa1_2;
    f32 temp_fa1_3;
    f32 temp_ft4_2;
    f32 temp_ft5;
    f32 temp_fv0_3;
    f32 temp_fv0_5;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    s32 temp_v0_10;
    s32 var_a0_2;
    s32 var_a2;
    s16 var_a3;
    s16 temp_v0;
    s32 temp_ft3_2;
    s32 var_a0;

    if (func_80833058(play, this, D_8085D050, 0)) {
        return;
    }

    if ((this->unk_AE7 == 0) && !func_80857A44(play, this)) {
        return;
    }

    this->stateFlags3 |= PLAYER_STATE3_1000;
    func_808577E0(this);

    if (func_80857950(play, this)) {
        return;
    }

    spE4 = 0.0f;
    spE2 = this->currentYaw;
    var_fv1 = (this->doorType == PLAYER_DOORTYPE_STAIRCASE) ? 0.0f : 12.0f;

    if (func_80840A30(play, this, this->unk_B08, var_fv1)) {
        if (this->actionFunc == func_80857BE8) {
            this->linearVelocity *= 0.1f;
            func_80834CD0(this, 10.0f, 0);
            if (this->unk_B86[1] != 0) {
                this->unk_B86[1] = 0;
                this->unk_AE7 = 3;
            }
        } else {
            return;
        }
    } else if (this->actor.bgCheckFlags & 8) {
        if (this->unk_B08[0] >= 12.0f) {
            temp_v0 = this->currentYaw - (this->actor.wallYaw + 0x8000);
            var_a2 = ABS_ALT(temp_v0);
            this->unk_B08[1] += this->unk_B08[0] * 0.05f;
            this->unk_B8C = 4;
            this->currentYaw += 0x8000 - (((temp_v0 >= 0) ? 1 : -1) * ((var_a2 + 0x100) & ~0x1FF) * 2);

            this->actor.shape.rot.y = this->actor.home.rot.y = this->currentYaw;
            func_800B8E58(this, NA_SE_IT_GORON_ROLLING_REFLECTION);
        }
    }

    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

    if (this->unk_B8E != 0) {
        this->unk_B8E--;
    } else {
        func_80832F78(this, &spE4, &spE2, 0.0f, play);
        spE4 *= 2.6f;
    }

    if (this->unk_B8C != 0) {
        this->unk_B8C--;
        spE2 = this->currentYaw;
    }

    if (this->unk_B86[1] != 0) {
        spE4 = 18.0f;
        Math_StepToC(&this->unk_AE7, 4, 1);

        if ((this->stateFlags3 & PLAYER_STATE3_80000) &&
            (!CHECK_BTN_ALL(D_80862B44->cur.button, BTN_A) || (gSaveContext.save.playerData.magic == 0) ||
             ((this->unk_AE7 == 4) && (this->unk_B08[0] < 12.0f)))) {
            if (Math_StepToS(&this->unk_B86[1], 0, 1) != 0) {
                this->stateFlags3 &= ~PLAYER_STATE3_80000;
                func_80115D5C(&play->state);
                func_800B8E58(this, NA_SE_PL_GORON_BALL_CHARGE_FAILED);
            }
            this->unk_AE7 = 4;
        } else if (this->unk_B86[1] < 7) {
            if (!(this->stateFlags3 & PLAYER_STATE3_80000)) {
                this->unk_3D0.unk_00 = 2;
            }
            this->unk_B86[1]++;
        }
    }

    spDC = (s32)(spE4 * 900.0f);

    Math_AsymStepToF(&this->unk_B10[0], (this->unk_B8A != 0) ? 1.0f : 0.0f, 0.8f, 0.05f);
    if (this->actor.bgCheckFlags & 1) {
        func_80857AEC(play, this);
        if (this->unk_AE7 == 2) {
            if (this->unk_B8A == 0) {
                this->unk_AE7 = 4;
            } else {
                this->unk_B8A--;
                this->unk_ABC = 0.0f;
                this->unk_B48 = 0.14f;
            }
        } else if ((this->unk_B86[1] == 0) && CHECK_BTN_ALL(D_80862B44->press.button, BTN_B) &&
                   (Inventory_GetBtnBItem(play) < 0xFD)) {
            func_80857640(this, 14.0f, 0x1F40);
        } else {
            sp90 = this->currentYaw;
            temp_a0 = sp90 - this->actor.home.rot.y;
            temp_fa0 = Math_CosS(temp_a0);
            if (this->unk_B86[1] == 0) {
                this->unk_B08[1] = 0.0f;
                if (this->unk_AE7 >= 0x36) {
                    func_80115DB4(play, 2, 5);
                    this->unk_B08[0] = 18.0f;
                    this->unk_B86[1] = 1;
                    this->stateFlags3 |= PLAYER_STATE3_80000;
                    func_8082E1F0(this, NA_SE_PL_GORON_BALL_CHARGE_DASH);
                }
            } else {
                this->unk_B08[1] = CLAMP(this->unk_B08[1], 0.0f, 0.9f);
            }

            spBC = (1.0f - this->unk_B08[1]) * this->unk_B08[0] * temp_fa0;
            if (!(spBC < 0.0f)) {
                if (spE4 == 0.0f) {
                    if (ABS_ALT(temp_a0) >= 0xFA1) {
                        spBC = 0.0f;
                    }
                }
            } else {
                // spBC = 0.0f;
            }

            Math_StepToF(&this->unk_B08[1], 0.0f, fabsf(temp_fa0) * 20.0f);
            var_a0 = spBC * 500.0f;
            var_a0 = CLAMP_MIN(var_a0, 0);

            var_v1_3 = (s32)(spE4 * 400.0f) - var_a0;
            var_v1_3 = CLAMP_MIN(var_v1_3, 0);

            spDC = CLAMP_MIN(spDC, var_a0);

            spAC = spBC * Math_SinS(this->actor.home.rot.y);
            spA8 = spBC * Math_CosS(this->actor.home.rot.y);
            spA4 = this->unk_B08[0] * Math_SinS(this->currentYaw);
            spA0 = this->unk_B08[0] * Math_CosS(this->currentYaw);
            this->linearVelocity = spBC;
            spA4 -= spAC;
            spA0 -= spA8;
            this->currentYaw = this->actor.home.rot.y;
            spCC = spE4;
            spCA = spE2;

            if (func_8083A4A4(this, &spCC, &spCA, (this->unk_AE7 >= 5) ? 0.0f : 1.0f)) {
                if (this->unk_B86[1] == 0) {
                    this->unk_AE7 = 4;
                }

                if (this->unk_AE7 == 4) {
                    spDC = -0xFA0;
                }
            } else {
                if (((this->unk_B72 == 0xE) || (this->unk_B72 == 0xF) || (this->unk_B72 == 1) || (D_80862B08 == 5)) &&
                    (var_v1_3 >= 0x7D0)) {
                    var_fv1_7 = 0.08f;
                } else {
                    var_fv1_7 = this->unk_AE8 * 0.0003f;
                }

                var_fa0 = (Math_SinS(this->unk_B6C) * 8.0f) + 0.6f;
                if (this->unk_B86[1] == 0) {
                    if ((gSaveContext.unk_3F28 == 0) && (gSaveContext.save.playerData.magic >= 2) &&
                        (this->unk_AE8 >= 0x36B0)) {
                        this->unk_AE7 += 1;
                        sp80 = var_fa0;
                        func_800B8F98(&this->actor, NA_SE_PL_GORON_BALL_CHARGE - SFX_FLAG);
                    } else {
                        this->unk_AE7 = 4;
                    }
                }

                if (spE4 != spCC) {
                    this->currentYaw = spE2;
                }

                var_fv1_7 = CLAMP_MIN(var_fv1_7, 0.0f);
                var_fa0 = CLAMP_MIN(var_fa0, 0.0f);

                Math_AsymStepToF(&this->linearVelocity, spE4, var_fv1_7, var_fa0);
                var_a2_2 = (s16)(fabsf(this->actor.speedXZ) * 20.0f) + 0x12C;
                var_a2_2 = CLAMP_MIN(var_a2_2, 0x64);

                temp_ft1_2 = (s32)(BINANG_SUB(spE2, this->currentYaw) * -0.5f);
                this->unk_B08[1] += (f32)(SQ(temp_ft1_2)) * 8e-9f;
                Math_ScaledStepToS(&this->currentYaw, spE2, var_a2_2);
                sp6C = func_80835D2C(play, this, &D_8085D978, &sp70);

                var_fa1 = func_80835D2C(play, this, &D_8085D984, &sp70) - sp6C;
                if (fabsf(var_fa1) > 100.0f) {
                    var_fa1 = 0.0f;
                }

                var_a3 = Math_FAtan2F(60.0f, var_fa1);
                if (ABS_ALT(var_a3) > 0x2AAA) {
                    var_a3 = 0;
                }

                Math_ScaledStepToS(&this->actor.shape.rot.z, var_a3 + temp_ft1_2, var_a2_2);
            }

            spBC = this->linearVelocity;
            this->actor.home.rot.y = this->currentYaw;
            this->currentYaw = sp90;
            Actor_GetSlopeDirection(this->actor.floorPoly, &sp94, &sp92);

            var_fa1_2 = sqrtf(SQ(spA4) + SQ(spA0));
            if (this->unk_B86[1] != 0) {
                var_a0_2 = ABS_ALT(temp_a0);

                if ((ABS_ALT(this->unk_B6C) + var_a0_2) > 15000) {
                    this->unk_B86[1] = 0;
                    this->unk_AE7 = 4;
                    this->unk_B8E = 0x14;
                    this->unk_AE8 = 0;
                    this->stateFlags3 &= ~PLAYER_STATE3_80000;
                    func_80115D5C(&play->state);
                }
            } else {
                temp_ft4_2 = (0.6f * sp94.x) + spA4;
                temp_ft5 = (0.6f * sp94.z) + spA0;
                temp_fv0_3 = sqrtf(SQ(temp_ft4_2) + SQ(temp_ft5));
                if ((temp_fv0_3 < var_fa1_2) || (temp_fv0_3 < 6.0f)) {
                    spA4 = temp_ft4_2;
                    spA0 = temp_ft5;
                    var_fa1_2 = temp_fv0_3;
                }
            }

            if (var_fa1_2 != 0.0f) {
                var_fv0 = var_fa1_2 - 0.3f;
                if (var_fa1_2 < 0.3f) {
                    var_fv0 = 0.0f;
                }

                temp_fa1_2 = var_fv0 / var_fa1_2;
                spA4 *= temp_fa1_2;
                spA0 *= temp_fa1_2;
                if (var_fv0 != 0.0f) {
                    this->unk_B28 = Math_FAtan2F(spA0, spA4);
                }

                if (this->unk_AE8 == 0) {
                    temp_v0_10 = this->unk_B86[0];
                    temp_ft3_2 = (s32)(var_fv0 * 800.0f);
                    this->unk_B86[0] += temp_ft3_2;
                    if ((this->actor.bgCheckFlags & 1) && (temp_ft3_2 != 0) &&
                        (((temp_v0_10 + temp_ft3_2) * temp_v0_10) <= 0)) {
                        func_8019F780(&this->actor.projectedPos, func_8082E078(this, NA_SE_PL_GORON_ROLL), var_fv0);
                    }
                }
            }

            spAC = Math_SinS(this->actor.home.rot.y) * spBC;
            temp_fa0_3 = (Math_CosS(this->actor.home.rot.y) * spBC) + spA0;
            temp_fa1_3 = spAC + spA4;
            this->unk_B08[0] = sqrtf(SQ(temp_fa1_3) + SQ(temp_fa0_3));
            this->unk_B08[0] = CLAMP_MAX(this->unk_B08[0], 18.0f);

            this->currentYaw = Math_FAtan2F(temp_fa0_3, temp_fa1_3);
        }

        func_808576BC(play, this);

        if (ABS_ALT(this->unk_AE8) > 0xFA0) {
            this->stateFlags2 |= PLAYER_STATE2_8;
        }

        if (this->actor.bgCheckFlags & 1) {
            this->linearVelocity = Math_CosS(this->unk_B6C) * this->unk_B08[0];
            this->actor.velocity.y = Math_SinS(this->unk_B6C) * this->unk_B08[0];
        }

        if ((this->unk_B86[1] != 0) ||
            (func_800C9C24(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId, 1) != 0)) {
            func_800AE930(&play->colCtx, Effect_GetByIndex(this->meleeWeaponEffectIndex[2]), &this->actor.world.pos,
                          15.0f, this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
        } else {
            func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
        }
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.z, 0, 0x190);

        this->unk_B86[0] = 0;
        if (this->unk_B86[1] != 0) {
            this->actor.gravity = -1.0f;
            Math_ScaledStepToS(&this->actor.home.rot.y, spE2, 0x190);

            temp_fv0_5 = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y));

            this->unk_B08[0] = ((this->linearVelocity >= 0.0f) ? 1.0f : -1.0f) * temp_fv0_5;
            this->unk_B08[0] = CLAMP_MAX(this->unk_B08[0], 18.0f);
        } else {
            this->unk_B48 += this->actor.velocity.y * 0.005f;
            if (this->unk_AE7 == 1) {
                if (this->actor.velocity.y > 0.0f) {
                    if ((this->actor.velocity.y + this->actor.gravity) < 0.0f) {
                        this->actor.velocity.y = -this->actor.gravity;
                    }
                } else {
                    this->unk_B8A = 0xA;
                    if (this->actor.velocity.y > -1.0f) {
                        this->actor.gravity = -0.2f;
                    } else {
                        this->unk_3D0.unk_00 = 1;
                        this->actor.gravity = -10.0f;
                    }
                }
            }
            this->unk_B08[0] = this->linearVelocity;
        }

        func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x7D0);

    Math_AsymStepToS(&this->unk_AE8, spDC, (spDC >= 0) ? 0x7D0 : 0x3E8, 0x4B0);

    if (this->unk_AE8 != 0) {
        temp_a3 = this->actor.shape.rot.x;
        this->actor.shape.rot.x += this->unk_AE8;

        Math_ScaledStepToS(this->unk_B86, 0, ABS_ALT(this->unk_AE8));
        if ((this->actor.bgCheckFlags & 1) && (((this->unk_AE8 + temp_a3) * temp_a3) <= 0)) {
            func_8019F780(&this->actor.projectedPos,
                          func_8082E078(this, (this->unk_B86[1] != 0) ? NA_SE_PL_GORON_CHG_ROLL : NA_SE_PL_GORON_ROLL),
                          this->unk_B08[0]);
        }
    }

    if (this->unk_AE7 == 2) {
        func_8082F0E4(this, 0x400, 4, 0x3C);
        func_800B648C(play, 0, 2, 100.0f, &this->actor.world.pos);
    } else if (this->unk_B86[1] != 0) {
        func_8082F0E4(this, 0x4000, 1, 0x19);
    } else {
        func_8082F0E4(this, 0x04000000, 1, 0x19);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857BE8.s")
#endif

void func_80858C84(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_8082E784(this);
    func_8082E438(play, this, anim);
    func_8082DABC(this);
}

void func_80858CC8(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_8082E784(this);
    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                         -8.0f);
    func_8082DABC(this);
}

void func_80858D48(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    func_8082E784(this);
    LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f);
    func_8082DABC(this);
}

void func_80858DB4(PlayState* play, Player* this, void* anim) {
    func_8082DABC(this);
}

void func_80858DDC(PlayState* play, Player* this, void* anim) {
    func_80858C84(play, this, anim);
}

void func_80858DFC(PlayState* play, Player* this, void* anim) {
    func_8082E784(this);
    func_8082E5A8(play, this, anim);
    func_8082DABC(this);
}

void func_80858E40(PlayState* play, Player* this, void* anim) {
    func_80858CC8(play, this, anim);
}

void func_80858E60(PlayState* play, Player* this, void* anim) {
    func_80858D48(play, this, anim);
}

void func_80858E80(PlayState* play, Player* this, void* anim) {
    func_8082EA60(play, this, anim);
}

void func_80858EA0(PlayState* play, Player* this, void* anim) {
    func_8082EA10(play, this, anim, 0x9C);
}

void func_80858EC0(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayOnceReverse(play, this, anim);
    func_8082E920(play, this, 0x9C);
}

void func_80858EFC(PlayState* play, Player* this, void* anim) {
    func_8082EB18(play, this, anim);
}

void func_80858F1C(PlayState* play, Player* this, void* anim) {
    func_8082EAC8(play, this, anim, 0x9C);
}

void func_80858F3C(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayOnce(play, this, anim);
}

void func_80858F5C(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayLoop(play, this, anim);
}

void func_80858F7C(PlayState* play, Player* this, void* anim) {
    func_8082DB90(play, this, anim);
}

void func_80858F9C(PlayState* play, Player* this, void* anim) {
    func_8082DB60(play, this, anim);
}

void func_80858FBC(PlayState* play, Player* this, void* anim) {
    LinkAnimation_Update(play, &this->skelAnime);
}

void func_80858FE8(Player* this) {
    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E120) {
        func_8082E094(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG);
        func_800B8E58(this, NA_SE_VO_LK_DRAGGED_DAMAGE - SFX_FLAG);
    }
}

void (*D_8085D990[])(PlayState*, Player*, void*) = {
    /*  0 */ NULL,
    /*  1 */ func_80858DB4,
    /*  2 */ func_80858DDC,
    /*  3 */ func_80858E40,
    /*  4 */ func_80858E60,
    /*  5 */ func_80858E80,
    /*  6 */ func_80858EA0,
    /*  7 */ func_80858EFC,
    /*  8 */ func_80858F1C,
    /*  9 */ func_80858F3C,
    /* 10 */ func_80858F5C,
    /* 11 */ func_80858FBC,
    /* 12 */ func_80859028,
    /* 13 */ func_808591BC,
    /* 14 */ func_80858DFC,
    /* 15 */ func_80858F7C,
    /* 16 */ func_80858F9C,
    /* 17 */ func_80859168,
    /* 18 */ func_80859210,
    /* 19 */ func_80858EC0,
};

AnimSfxEntry D_8085D9E0[] = {
    ANIMSFX(ANIMSFX_TYPE_5, 34, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 45, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 51, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 64, NA_SE_PL_CALM_HIT, STOP),
};
AnimSfxEntry D_8085D9F0[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 7, NA_SE_VO_LI_DEMO_DAMAGE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_2, 18, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 18, NA_SE_VO_LI_FREEZE, STOP),
};
AnimSfxEntry D_8085D9FC[] = {
    ANIMSFX(ANIMSFX_TYPE_3, 14, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA00[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 6, NA_SE_PL_GET_UP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 18, NA_SE_VO_LK_WAKE_UP, STOP),
};
AnimSfxEntry D_8085DA08[] = {
    ANIMSFX(ANIMSFX_TYPE_3, 26, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA0C[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 16, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_7, 36, 0, STOP),
};
AnimSfxEntry D_8085DA14[] = {
    ANIMSFX(ANIMSFX_TYPE_7, 55, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_1, 55, NA_SE_VO_LK_CATCH_DEMO, STOP),
};
AnimSfxEntry D_8085DA1C[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 4, NA_SE_VO_LK_USING_UP_ENERGY, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_2, 16, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 16, NA_SE_VO_LI_DAMAGE_S, STOP),
};
AnimSfxEntry D_8085DA28[] = {
    ANIMSFX(ANIMSFX_TYPE_3, 28, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA2C[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 1, NA_SE_VO_LK_USING_UP_ENERGY, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_7, 42, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 44, NA_SE_VO_LI_FALL_L, STOP),
};
AnimSfxEntry D_8085DA38[] = {
    ANIMSFX(ANIMSFX_TYPE_2, 1, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_DAMAGE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_3, 39, NA_SE_PL_LAND_GROUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 49, 0, STOP),
};
AnimSfxEntry D_8085DA48[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 1, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 5, 0, STOP),
};
AnimSfxEntry D_8085DA50[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 10, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 13, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 16, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 19, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 22, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_2, 22, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 55, NA_SE_VO_LI_DAMAGE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_5, 62, 0, STOP),
};

AnimSfxEntry D_8085DA70[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 42, 0, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 48, 0, STOP),
};
AnimSfxEntry D_8085DA78[] = {
    ANIMSFX(ANIMSFX_TYPE_2, 2, NA_SE_PL_BOUND, STOP),
};
AnimSfxEntry D_8085DA7C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 5, NA_SE_VO_LI_FREEZE, STOP),
};
AnimSfxEntry D_8085DA80[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_FALL_L, STOP),
};
AnimSfxEntry D_8085DA84[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_HANG, STOP),
};
AnimSfxEntry D_8085DA88[] = {
    ANIMSFX(ANIMSFX_TYPE_5, 26, 0, STOP),
};
AnimSfxEntry D_8085DA8C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 4, NA_SE_VO_LI_SURPRISE, STOP),
};
AnimSfxEntry D_8085DA90[] = {
    ANIMSFX(ANIMSFX_TYPE_1, 18, NA_SE_PL_SIT_ON_HORSE, STOP),
};

void func_80859028(PlayState* play, Player* this, void* anim) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80858D48(play, this, anim);
        this->unk_AE8 = 1;
    }

    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E150) {
        Player_PlayAnimSfx(this, D_8085DA08);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E118) {
        Player_PlayAnimSfx(this, D_8085DA14);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00E430) {
        Player_PlayAnimSfx(this, D_8085DA38);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D030) {
        Player_PlayAnimSfx(this, D_8085DA7C);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00CF48) {
        Player_PlayAnimSfx(this, D_8085DA84);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D108) {
        Player_PlayAnimSfx(this, D_8085DA90);
    } else {
        func_80858FE8(this);
    }
}

void func_80859168(PlayState* play, Player* this, void* anim) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        func_8082DB60(play, this, anim);
    }
}

void func_808591BC(PlayState* play, Player* this, void* anim) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082EB18(play, this, anim);
        this->unk_AE8 = 1;
    }
}

void func_80859210(PlayState* play, Player* this, void* arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
    Player_PlayAnimSfx(this, arg2);
}

void func_80859248(Player* this) {
    if ((this->unk_398 == NULL) || (this->unk_398->update == NULL)) {
        this->unk_398 = NULL;
    }
    this->targetedActor = this->unk_398;
    if (this->unk_398 != NULL) {
        this->actor.shape.rot.y = func_8083C62C(this, 0);
    }
}

void func_8085929C(PlayState* play, Player* this, UNK_TYPE arg2) {
    this->stateFlags1 |= PLAYER_STATE1_8000000;
    this->stateFlags2 |= PLAYER_STATE2_400;
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);
    Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00DFD0);
    this->linearVelocity = 0.0f;
}

void func_80859300(PlayState* play, Player* this, UNK_TYPE arg2) {
    this->actor.gravity = 0.0f;

    if (this->unk_AE7 == 0) {
        if ((this->transformation == PLAYER_FORM_DEKU) || func_8083B3B4(play, this, NULL)) {
            this->unk_AE7 = 1;
        } else {
            func_808477D0(play, this, NULL, fabsf(this->actor.velocity.y));
            Math_ScaledStepToS(&this->unk_AAA, -0x2710, 0x320);
            func_8084748C(this, &this->actor.velocity.y, 4.0f, this->currentYaw);
        }
    } else {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            if (this->unk_AE7 == 1) {
                func_8082E634(play, this, &gameplay_keep_Linkanim_00E000);
            } else {
                Player_AnimationPlayLoop(play, this, &gameplay_keep_Linkanim_00E000);
            }
        }
        func_808475B4(this);
        func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
    }
}

void func_80859414(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_80859248(this);

    if (func_801242B4(this)) {
        func_80859300(play, this, 0);
    } else {
        LinkAnimation_Update(play, &this->skelAnime);
        if (func_801240DC(this) || (this->stateFlags1 & PLAYER_STATE1_800)) {
            func_8083216C(this, play);
        } else if ((this->interactRangeActor != NULL) && (this->interactRangeActor->textId == 0xFFFF)) {
            func_8083D23C(this, play);
        }
    }
}

void func_808594D0(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_8085929C(play, this, 0);
    } else {
        LinkAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType];

        if ((this->unk_396 == 6) || (this->unk_396 == 0x2E)) {
            Player_AnimationPlayOnce(play, this, anim);
        } else {
            func_8082E784(this);
            LinkAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim),
                                 ANIMMODE_LOOP, -4.0f);
        }
        func_8082DABC(this);
    }
}

void func_808595B8(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (func_80847880(play, this)) {
        return;
    }

    if ((this->csMode == PLAYER_CSMODE_20) && (play->csCtx.state == CS_STATE_0)) {
        func_800B7298(play, NULL, PLAYER_CSMODE_6);
    } else if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_80859300(play, this, 0);
        this->actor.velocity.y = 0.0f;
    } else {
        LinkAnimation_Update(play, &this->skelAnime);
        if (func_801240DC(this) || (this->stateFlags1 & PLAYER_STATE1_800)) {
            func_8083216C(this, play);
        }
    }
}

void func_8085968C(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (this->actor.id == ACTOR_EN_TEST3) {
        func_80838830(this, OBJECT_GI_MSSA);
        this->stateFlags1 |= PLAYER_STATE1_400;
    }

    func_8082DB90(play, this,
                  (this->transformation == PLAYER_FORM_DEKU) ? &gameplay_keep_Linkanim_00E2B8
                                                             : &gameplay_keep_Linkanim_00D5A8);
}

void func_80859708(PlayState* play, Player* this, UNK_TYPE arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
    if ((this->actor.id == ACTOR_EN_TEST3) && Animation_OnFrame(&this->skelAnime, 20.0f)) {
        this->unk_B2A = 0x3A;
        func_80151BB4(play, 0x1B);
        func_801A3098(0x37);
    }
}

void func_8085978C(PlayState* play, Player* this, UNK_TYPE arg2) {
    f32 linearVelocity;
    s16 yaw;

    this->stateFlags1 &= ~PLAYER_STATE1_2000000;

    yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_3A0);
    linearVelocity = this->linearVelocity;
    this->actor.world.rot.y = yaw;
    this->actor.shape.rot.y = yaw;
    this->currentYaw = yaw;
    if (linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    } else if (linearVelocity > 2.5f) {
        this->linearVelocity = 2.5f;
    }

    if ((this->transformation != PLAYER_FORM_HUMAN) && (play->roomCtx.currRoom.unk3 == 5)) {
        MREG(64) = 0x2D;
        MREG(65) = 0xFF;
        MREG(66) = 0xFF;
        MREG(67) = 0xFF;
        MREG(68) = 0;
        play_sound(NA_SE_SY_WHITE_OUT_T);
    }
}

void func_80859890(PlayState* play, Player* this, UNK_TYPE arg2) {
    f32 sp24;
    s16 temp_v1 = MREG(64);

    if (temp_v1 > 0) {
        MREG(68) += temp_v1;
        if (MREG(68) >= 0x100) {
            MREG(64) = -0x40;
            MREG(68) = 0xFF;
            gSaveContext.save.playerForm = 4;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->unk_AE7 = 0;
        }
    } else if (temp_v1 < 0) {
        MREG(68) += temp_v1;
        if (MREG(68) < 0) {
            MREG(64) = 0;
            MREG(68) = 0;
        }
    } else {
        sp24 = 2.5f;
        func_808411D4(play, this, &sp24, 0xA);
        this->unk_AE8++;
        if (this->unk_AE8 >= 0x15) {
            this->csMode = PLAYER_CSMODE_10;
        }
    }
}

void func_80859990(PlayState* play, Player* this, UNK_TYPE arg2) {
    this->linearVelocity = 2.5f;
    func_80835BF8(&this->actor.world.pos, this->actor.shape.rot.y, 180.0f, &this->unk_3A0);
}

void func_808599DC(PlayState* play, Player* this, UNK_TYPE arg2) {
    f32 sp1C;

    sp1C = 2.5f;
    func_808411D4(play, this, &sp1C, 0xA);
}

void func_80859A10(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_8083B23C(this, play);
}

void func_80859A44(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_80859248(this);
    if (this->unk_AE8 != 0) {
        if (LinkAnimation_Update(play, &this->skelAnime)) {
            Player_AnimationPlayLoop(play, this, func_8082EF54(this));
            this->unk_AE8 = 0;
        }
        func_8082FC60(this);
    } else {
        func_8083E958(play, this);
    }
}

void func_80859AD0(PlayState* play, Player* this, UNK_PTR arg2) {
    func_80840F90(play, this, arg2, 0.0f, 0, 0);
}

void func_80859AF8(PlayState* play, Player* this, UNK_PTR arg2) {
    this->actor.shape.face = 0xF;
    func_80840F90(play, this, arg2, 0.0f, 0, 0);
}

void func_80859B28(PlayState* play, Player* this, UNK_PTR arg2) {
    func_80840F90(play, this, arg2, 0.0f, 0, 1);
}

void func_80859B54(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_80858CC8(play, this, &gameplay_keep_Linkanim_00DDB0);
    this->heldItemActionParam = PLAYER_AP_OCARINA;
    Player_SetModels(this, Player_ActionToModelGroup(this, this->heldItemActionParam));
}

void func_80859BA8(PlayState* play, Player* this, void* arg) {
    f32 temp_ft1;
    CsCmdActorAction* playerAction = arg;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 xDiff;
    f32 new_var;
    f32 yDiff;
    f32 zDiff;

    temp_fv0 = playerAction->startPos.x;
    temp_fv1 = playerAction->startPos.y;
    temp_fa0 = playerAction->startPos.z;

    xDiff = playerAction->endPos.x - temp_fv0;
    yDiff = playerAction->endPos.y - temp_fv1;
    zDiff = playerAction->endPos.z - temp_fa0;

    //! FAKE
    temp_ft1 = (new_var = ((f32)(play->csCtx.frames - playerAction->startFrame)) /
                          ((f32)(playerAction->endFrame - playerAction->startFrame)));

    this->actor.world.pos.x = ((xDiff)*temp_ft1) + temp_fv0;
    this->actor.world.pos.y = ((yDiff)*temp_ft1) + temp_fv1;
    this->actor.world.pos.z = ((zDiff)*temp_ft1) + temp_fa0;
}

void func_80859C60(PlayState* play, Player* this, UNK_PTR arg2) {
    if (arg2 != NULL) {
        func_80859BA8(play, this, arg2);
    }

    LinkAnimation_Update(play, &this->skelAnime);
}

void func_80859CA0(PlayState* play, Player* this, s32 arg2) {
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
    func_8082DABC(this);
}

void func_80859CE0(PlayState* play, Player* this, s32 arg2) {
    this->actor.draw = Player_Draw;
}

void func_80859CFC(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_80841358(play, this, false);
    func_8082DB90(play, this, &gameplay_keep_Linkanim_00D660);
}

void func_80859D44(PlayState* play, Player* this, UNK_TYPE arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
}

struct_8085DA94 D_8085DA94[PLAYER_CSMODE_MAX] = {
    /* PLAYER_CSMODE_0   */ { 0, { NULL } },
    /* PLAYER_CSMODE_1   */ { -1, { func_808594D0 } },
    /* PLAYER_CSMODE_2   */ { 0, { NULL } },
    /* PLAYER_CSMODE_3   */ { 0, { NULL } },
    /* PLAYER_CSMODE_4   */ { 3, { &gameplay_keep_Linkanim_00D568 } },
    /* PLAYER_CSMODE_5   */ { 0, { NULL } },
    /* PLAYER_CSMODE_6   */ { 0, { NULL } },
    /* PLAYER_CSMODE_7   */ { -1, { func_808594D0 } },
    /* PLAYER_CSMODE_8   */ { 2, { &gameplay_keep_Linkanim_00D5A0 } },
    /* PLAYER_CSMODE_9   */ { -1, { func_8085978C } },
    /* PLAYER_CSMODE_10  */ { 3, { &gameplay_keep_Linkanim_00D680 } },
    /* PLAYER_CSMODE_11  */ { 5, { &gameplay_keep_Linkanim_00D1C0 } },
    /* PLAYER_CSMODE_12  */ { 7, { &gameplay_keep_Linkanim_00D1C8 } },
    /* PLAYER_CSMODE_13  */ { 2, { &gameplay_keep_Linkanim_00D560 } },
    /* PLAYER_CSMODE_14  */ { 0, { NULL } },
    /* PLAYER_CSMODE_15  */ { 3, { &gameplay_keep_Linkanim_00D5D0 } },
    /* PLAYER_CSMODE_16  */ { -1, { func_80859B54 } },
    /* PLAYER_CSMODE_17  */ { 2, { &gameplay_keep_Linkanim_00DDA8 } },
    /* PLAYER_CSMODE_18  */ { 16, { &gameplay_keep_Linkanim_00DCB0 } },
    /* PLAYER_CSMODE_19  */ { -1, { func_80859CA0 } },
    /* PLAYER_CSMODE_20  */ { -1, { func_808594D0 } },
    /* PLAYER_CSMODE_21  */ { 3, { &gameplay_keep_Linkanim_00D190 } },
    /* PLAYER_CSMODE_22  */ { 6, { &gameplay_keep_Linkanim_00E168 } },
    /* PLAYER_CSMODE_23  */ { 3, { &gameplay_keep_Linkanim_00D640 } },
    /* PLAYER_CSMODE_24  */ { 3, { &gameplay_keep_Linkanim_00DF38 } },
    /* PLAYER_CSMODE_25  */ { -1, { func_80859CFC } },
    /* PLAYER_CSMODE_26  */ { -1, { func_8085A66C } },
    /* PLAYER_CSMODE_27  */ { 3, { &gameplay_keep_Linkanim_00D688 } },
    /* PLAYER_CSMODE_28  */ { 3, { &gameplay_keep_Linkanim_00D610 } },
    /* PLAYER_CSMODE_29  */ { 3, { &gameplay_keep_Linkanim_00D620 } },
    /* PLAYER_CSMODE_30  */ { 3, { &gameplay_keep_Linkanim_00D628 } },
    /* PLAYER_CSMODE_31  */ { 6, { &gameplay_keep_Linkanim_00D310 } },
    /* PLAYER_CSMODE_32  */ { -1, { func_80859FCC } },
    /* PLAYER_CSMODE_33  */ { 3, { &gameplay_keep_Linkanim_00D2D0 } },
    /* PLAYER_CSMODE_34  */ { 4, { &gameplay_keep_Linkanim_00D2C8 } },
    /* PLAYER_CSMODE_35  */ { 3, { &gameplay_keep_Linkanim_00D2B8 } },
    /* PLAYER_CSMODE_36  */ { -1, { func_8085A120 } },
    /* PLAYER_CSMODE_37  */ { -1, { func_8085A19C } },
    /* PLAYER_CSMODE_38  */ { 6, { &gameplay_keep_Linkanim_00D278 } },
    /* PLAYER_CSMODE_39  */ { 6, { &gameplay_keep_Linkanim_00D288 } },
    /* PLAYER_CSMODE_40  */ { 5, { &gameplay_keep_Linkanim_00E428 } },
    /* PLAYER_CSMODE_41  */ { 5, { &gameplay_keep_Linkanim_00D060 } },
    /* PLAYER_CSMODE_42  */ { 5, { &gameplay_keep_Linkanim_00E148 } },
    /* PLAYER_CSMODE_43  */ { 5, { &gameplay_keep_Linkanim_00E150 } },
    /* PLAYER_CSMODE_44  */ { 7, { &gameplay_keep_Linkanim_00D068 } },
    /* PLAYER_CSMODE_45  */ { 5, { &gameplay_keep_Linkanim_00E420 } },
    /* PLAYER_CSMODE_46  */ { 5, { &gameplay_keep_Linkanim_00E430 } },
    /* PLAYER_CSMODE_47  */ { 5, { &gameplay_keep_Linkanim_00E440 } },
    /* PLAYER_CSMODE_48  */ { 3, { &gameplay_keep_Linkanim_00CF68 } },
    /* PLAYER_CSMODE_49  */ { 5, { &gameplay_keep_Linkanim_00D2F0 } },
    /* PLAYER_CSMODE_50  */ { 5, { &gameplay_keep_Linkanim_00E468 } },
    /* PLAYER_CSMODE_51  */ { 5, { &gameplay_keep_Linkanim_00E460 } },
    /* PLAYER_CSMODE_52  */ { 5, { &gameplay_keep_Linkanim_00E140 } },
    /* PLAYER_CSMODE_53  */ { 5, { &gameplay_keep_Linkanim_00E118 } },
    /* PLAYER_CSMODE_54  */ { 4, { &gameplay_keep_Linkanim_00E120 } },
    /* PLAYER_CSMODE_55  */ { 5, { &gameplay_keep_Linkanim_00E110 } },
    /* PLAYER_CSMODE_56  */ { 14, { &gameplay_keep_Linkanim_00E140 } },
    /* PLAYER_CSMODE_57  */ { 5, { &gameplay_keep_Linkanim_00D0E0 } },
    /* PLAYER_CSMODE_58  */ { -1, { func_8085978C } },
    /* PLAYER_CSMODE_59  */ { 5, { &gameplay_keep_Linkanim_00D0A0 } },
    /* PLAYER_CSMODE_60  */ { 2, { &gameplay_keep_Linkanim_00D080 } },
    /* PLAYER_CSMODE_61  */ { 7, { &gameplay_keep_Linkanim_00D0B8 } },
    /* PLAYER_CSMODE_62  */ { 5, { &gameplay_keep_Linkanim_00D0C0 } },
    /* PLAYER_CSMODE_63  */ { 3, { &gameplay_keep_Linkanim_00CF60 } },
    /* PLAYER_CSMODE_64  */ { 3, { &gameplay_keep_Linkanim_00CF48 } },
    /* PLAYER_CSMODE_65  */ { 3, { &gameplay_keep_Linkanim_00CF58 } },
    /* PLAYER_CSMODE_66  */ { 3, { &gameplay_keep_Linkanim_00CF40 } },
    /* PLAYER_CSMODE_67  */ { -1, { func_8085968C } },
    /* PLAYER_CSMODE_68  */ { -1, { func_8085A24C } },
    /* PLAYER_CSMODE_69  */ { -1, { func_8085A330 } },
    /* PLAYER_CSMODE_70  */ { 7, { &gameplay_keep_Linkanim_00D0D8 } },
    /* PLAYER_CSMODE_71  */ { 5, { &gameplay_keep_Linkanim_00D090 } },
    /* PLAYER_CSMODE_72  */ { 5, { &gameplay_keep_Linkanim_00D088 } },
    /* PLAYER_CSMODE_73  */ { 3, { &gameplay_keep_Linkanim_00CF88 } },
    /* PLAYER_CSMODE_74  */ { 3, { &gameplay_keep_Linkanim_00CF90 } },
    /* PLAYER_CSMODE_75  */ { 3, { &gameplay_keep_Linkanim_00CF78 } },
    /* PLAYER_CSMODE_76  */ { 3, { &gameplay_keep_Linkanim_00CF80 } },
    /* PLAYER_CSMODE_77  */ { 7, { &gameplay_keep_Linkanim_00D308 } },
    /* PLAYER_CSMODE_78  */ { 5, { &gameplay_keep_Linkanim_00D300 } },
    /* PLAYER_CSMODE_79  */ { 3, { &gameplay_keep_Linkanim_00D018 } },
    /* PLAYER_CSMODE_80  */ { 4, { &gameplay_keep_Linkanim_00D028 } },
    /* PLAYER_CSMODE_81  */ { 3, { &gameplay_keep_Linkanim_00CFE0 } },
    /* PLAYER_CSMODE_82  */ { 4, { &gameplay_keep_Linkanim_00D058 } },
    /* PLAYER_CSMODE_83  */ { 3, { &gameplay_keep_Linkanim_00D030 } },
    /* PLAYER_CSMODE_84  */ { 5, { &gameplay_keep_Linkanim_00CFB0 } },
    /* PLAYER_CSMODE_85  */ { 3, { &gameplay_keep_Linkanim_00CFC8 } },
    /* PLAYER_CSMODE_86  */ { 4, { &gameplay_keep_Linkanim_00D040 } },
    /* PLAYER_CSMODE_87  */ { 5, { &gameplay_keep_Linkanim_00D1D0 } },
    /* PLAYER_CSMODE_88  */ { 3, { &gameplay_keep_Linkanim_00CFD8 } },
    /* PLAYER_CSMODE_89  */ { 4, { &gameplay_keep_Linkanim_00CFC0 } },
    /* PLAYER_CSMODE_90  */ { 4, { &gameplay_keep_Linkanim_00CFB8 } },
    /* PLAYER_CSMODE_91  */ { 4, { &gameplay_keep_Linkanim_00D050 } },
    /* PLAYER_CSMODE_92  */ { 4, { &gameplay_keep_Linkanim_00D048 } },
    /* PLAYER_CSMODE_93  */ { -1, { func_8085A8C4 } },
    /* PLAYER_CSMODE_94  */ { 3, { &gameplay_keep_Linkanim_00D000 } },
    /* PLAYER_CSMODE_95  */ { 3, { &gameplay_keep_Linkanim_00D010 } },
    /* PLAYER_CSMODE_96  */ { 9, { &gameplay_keep_Linkanim_00DAD0 } },
    /* PLAYER_CSMODE_97  */ { -1, { func_8085A530 } },
    /* PLAYER_CSMODE_98  */ { 15, { &gameplay_keep_Linkanim_00D0A8 } },
    /* PLAYER_CSMODE_99  */ { 7, { &gameplay_keep_Linkanim_00D098 } },
    /* PLAYER_CSMODE_100 */ { 3, { &gameplay_keep_Linkanim_00CFA0 } },
    /* PLAYER_CSMODE_101 */ { 3, { &gameplay_keep_Linkanim_00CFF0 } },
    /* PLAYER_CSMODE_102 */ { -1, { func_8085A768 } },
    /* PLAYER_CSMODE_103 */ { -1, { func_8085AA60 } },
    /* PLAYER_CSMODE_104 */ { 5, { &gameplay_keep_Linkanim_00D070 } },
    /* PLAYER_CSMODE_105 */ { 5, { &gameplay_keep_Linkanim_00D358 } },
    /* PLAYER_CSMODE_106 */ { 5, { &gameplay_keep_Linkanim_00D330 } },
    /* PLAYER_CSMODE_107 */ { 5, { &gameplay_keep_Linkanim_00D340 } },
    /* PLAYER_CSMODE_108 */ { 5, { &gameplay_keep_Linkanim_00D350 } },
    /* PLAYER_CSMODE_109 */ { 5, { &gameplay_keep_Linkanim_00D328 } },
    /* PLAYER_CSMODE_110 */ { 7, { &gameplay_keep_Linkanim_00D368 } },
    /* PLAYER_CSMODE_111 */ { 3, { &gameplay_keep_Linkanim_00D9F8 } },
    /* PLAYER_CSMODE_112 */ { 5, { &gameplay_keep_Linkanim_00D108 } },
    /* PLAYER_CSMODE_113 */ { 5, { &gameplay_keep_Linkanim_00D118 } },
    /* PLAYER_CSMODE_114 */ { 4, { &gameplay_keep_Linkanim_00CF98 } },
    /* PLAYER_CSMODE_115 */ { 2, { &gameplay_keep_Linkanim_00D5B8 } },
    /* PLAYER_CSMODE_116 */ { 7, { &gameplay_keep_Linkanim_00E010 } },
    /* PLAYER_CSMODE_117 */ { 5, { &gameplay_keep_Linkanim_00D0F8 } },
    /* PLAYER_CSMODE_118 */ { 7, { &gameplay_keep_Linkanim_00D2D8 } },
    /* PLAYER_CSMODE_119 */ { 7, { &gameplay_keep_Linkanim_00D2E0 } },
    /* PLAYER_CSMODE_120 */ { 7, { &gameplay_keep_Linkanim_00D2E8 } },
    /* PLAYER_CSMODE_121 */ { -1, { func_80859990 } },
    /* PLAYER_CSMODE_122 */ { 0, { NULL } },
    /* PLAYER_CSMODE_123 */ { -1, { func_80859A10 } },
    /* PLAYER_CSMODE_124 */ { 7, { &gameplay_keep_Linkanim_00D158 } },
    /* PLAYER_CSMODE_125 */ { 5, { &gameplay_keep_Linkanim_00D160 } },
    /* PLAYER_CSMODE_126 */ { 5, { &gameplay_keep_Linkanim_00D168 } },
    /* PLAYER_CSMODE_127 */ { 3, { &gameplay_keep_Linkanim_00D5C0 } },
    /* PLAYER_CSMODE_128 */ { 4, { &gameplay_keep_Linkanim_00D668 } },
    /* PLAYER_CSMODE_129 */ { 3, { &gameplay_keep_Linkanim_00E470 } },
    /* PLAYER_CSMODE_130 */ { 3, { &gameplay_keep_Linkanim_00E478 } },
    /* PLAYER_CSMODE_131 */ { 3, { &gameplay_keep_Linkanim_00E4C0 } },
    /* PLAYER_CSMODE_132 */ { 3, { &gameplay_keep_Linkanim_00E480 } },
    /* PLAYER_CSMODE_133 */ { 3, { &gameplay_keep_Linkanim_00E490 } },
    /* PLAYER_CSMODE_134 */ { 3, { &gameplay_keep_Linkanim_00E488 } },
    /* PLAYER_CSMODE_135 */ { 3, { &gameplay_keep_Linkanim_00E498 } },
    /* PLAYER_CSMODE_136 */ { 3, { &gameplay_keep_Linkanim_00E4B0 } },
    /* PLAYER_CSMODE_137 */ { 3, { &gameplay_keep_Linkanim_00D660 } },
    /* PLAYER_CSMODE_138 */ { 3, { &gameplay_keep_Linkanim_00DA00 } },
    /* PLAYER_CSMODE_139 */ { 3, { &gameplay_keep_Linkanim_00DA08 } },
};

struct_8085DA94 D_8085DEF4[PLAYER_CSMODE_MAX] = {
    /* PLAYER_CSMODE_0   */ { 0, { NULL } },
    /* PLAYER_CSMODE_1   */ { -1, { func_80859414 } },
    /* PLAYER_CSMODE_2   */ { -1, { func_80859AD0 } },
    /* PLAYER_CSMODE_3   */ { -1, { func_80859B28 } },
    /* PLAYER_CSMODE_4   */ { 11, { NULL } },
    /* PLAYER_CSMODE_5   */ { -1, { func_8085ADA0 } },
    /* PLAYER_CSMODE_6   */ { -1, { func_8085AACC } },
    /* PLAYER_CSMODE_7   */ { -1, { func_808595B8 } },
    /* PLAYER_CSMODE_8   */ { 18, { D_8085DA70 } },
    /* PLAYER_CSMODE_9   */ { -1, { func_80859890 } },
    /* PLAYER_CSMODE_10  */ { -1, { func_80859C60 } },
    /* PLAYER_CSMODE_11  */ { 18, { D_8085D9E0 } },
    /* PLAYER_CSMODE_12  */ { 11, { NULL } },
    /* PLAYER_CSMODE_13  */ { 11, { NULL } },
    /* PLAYER_CSMODE_14  */ { 0, { NULL } },
    /* PLAYER_CSMODE_15  */ { 11, { NULL } },
    /* PLAYER_CSMODE_16  */ { 17, { &gameplay_keep_Linkanim_00DDB8 } },
    /* PLAYER_CSMODE_17  */ { 11, { NULL } },
    /* PLAYER_CSMODE_18  */ { 11, { NULL } },
    /* PLAYER_CSMODE_19  */ { -1, { func_8085A710 } },
    /* PLAYER_CSMODE_20  */ { -1, { func_808595B8 } },
    /* PLAYER_CSMODE_21  */ { 12, { &gameplay_keep_Linkanim_00D198 } },
    /* PLAYER_CSMODE_22  */ { -1, { func_80859D70 } },
    /* PLAYER_CSMODE_23  */ { 12, { &gameplay_keep_Linkanim_00D648 } },
    /* PLAYER_CSMODE_24  */ { 11, { NULL } },
    /* PLAYER_CSMODE_25  */ { 11, { NULL } },
    /* PLAYER_CSMODE_26  */ { -1, { func_8085A6C0 } },
    /* PLAYER_CSMODE_27  */ { 12, { &gameplay_keep_Linkanim_00D690 } },
    /* PLAYER_CSMODE_28  */ { 12, { &gameplay_keep_Linkanim_00D618 } },
    /* PLAYER_CSMODE_29  */ { 12, { &gameplay_keep_Linkanim_00D630 } },
    /* PLAYER_CSMODE_30  */ { 12, { &gameplay_keep_Linkanim_00D298 } },
    /* PLAYER_CSMODE_31  */ { 12, { &gameplay_keep_Linkanim_00D318 } },
    /* PLAYER_CSMODE_32  */ { -1, { func_80859FF4 } },
    /* PLAYER_CSMODE_33  */ { -1, { func_8085A04C } },
    /* PLAYER_CSMODE_34  */ { 11, { NULL } },
    /* PLAYER_CSMODE_35  */ { 12, { &gameplay_keep_Linkanim_00D2C0 } },
    /* PLAYER_CSMODE_36  */ { -1, { func_8085A144 } },
    /* PLAYER_CSMODE_37  */ { -1, { func_8085A1D4 } },
    /* PLAYER_CSMODE_38  */ { 12, { &gameplay_keep_Linkanim_00D280 } },
    /* PLAYER_CSMODE_39  */ { 12, { &gameplay_keep_Linkanim_00D290 } },
    /* PLAYER_CSMODE_40  */ { 18, { D_8085D9F0 } },
    /* PLAYER_CSMODE_41  */ { 11, { NULL } },
    /* PLAYER_CSMODE_42  */ { 18, { D_8085DA00 } },
    /* PLAYER_CSMODE_43  */ { 13, { &gameplay_keep_Linkanim_00E158 } },
    /* PLAYER_CSMODE_44  */ { -1, { func_8085A364 } },
    /* PLAYER_CSMODE_45  */ { 18, { D_8085DA2C } },
    /* PLAYER_CSMODE_46  */ { 12, { &gameplay_keep_Linkanim_00E438 } },
    /* PLAYER_CSMODE_47  */ { 12, { &gameplay_keep_Linkanim_00E448 } },
    /* PLAYER_CSMODE_48  */ { 12, { &gameplay_keep_Linkanim_00CF70 } },
    /* PLAYER_CSMODE_49  */ { 12, { &gameplay_keep_Linkanim_00D2F8 } },
    /* PLAYER_CSMODE_50  */ { 18, { D_8085DA50 } },
    /* PLAYER_CSMODE_51  */ { 11, { NULL } },
    /* PLAYER_CSMODE_52  */ { 18, { D_8085D9FC } },
    /* PLAYER_CSMODE_53  */ { 12, { &gameplay_keep_Linkanim_00E120 } },
    /* PLAYER_CSMODE_54  */ { -1, { func_8085A364 } },
    /* PLAYER_CSMODE_55  */ { 18, { D_8085DA1C } },
    /* PLAYER_CSMODE_56  */ { 11, { NULL } },
    /* PLAYER_CSMODE_57  */ { 18, { D_8085DA0C } },
    /* PLAYER_CSMODE_58  */ { -1, { func_808599DC } },
    /* PLAYER_CSMODE_59  */ { 11, { NULL } },
    /* PLAYER_CSMODE_60  */ { 18, { D_8085DA28 } },
    /* PLAYER_CSMODE_61  */ { -1, { func_8085A364 } },
    /* PLAYER_CSMODE_62  */ { 11, { NULL } },
    /* PLAYER_CSMODE_63  */ { 11, { NULL } },
    /* PLAYER_CSMODE_64  */ { 12, { &gameplay_keep_Linkanim_00CF50 } },
    /* PLAYER_CSMODE_65  */ { -1, { func_8085A40C } },
    /* PLAYER_CSMODE_66  */ { 11, { NULL } },
    /* PLAYER_CSMODE_67  */ { -1, { func_80859708 } },
    /* PLAYER_CSMODE_68  */ { -1, { func_8085A2AC } },
    /* PLAYER_CSMODE_69  */ { 11, { NULL } },
    /* PLAYER_CSMODE_70  */ { 11, { NULL } },
    /* PLAYER_CSMODE_71  */ { -1, { func_8085A40C } },
    /* PLAYER_CSMODE_72  */ { 11, { NULL } },
    /* PLAYER_CSMODE_73  */ { 11, { NULL } },
    /* PLAYER_CSMODE_74  */ { 11, { NULL } },
    /* PLAYER_CSMODE_75  */ { 11, { NULL } },
    /* PLAYER_CSMODE_76  */ { 11, { NULL } },
    /* PLAYER_CSMODE_77  */ { 11, { NULL } },
    /* PLAYER_CSMODE_78  */ { 18, { D_8085DA78 } },
    /* PLAYER_CSMODE_79  */ { 12, { &gameplay_keep_Linkanim_00D020 } },
    /* PLAYER_CSMODE_80  */ { -1, { func_8085A364 } },
    /* PLAYER_CSMODE_81  */ { 12, { &gameplay_keep_Linkanim_00CFE8 } },
    /* PLAYER_CSMODE_82  */ { 11, { NULL } },
    /* PLAYER_CSMODE_83  */ { 12, { &gameplay_keep_Linkanim_00D038 } },
    /* PLAYER_CSMODE_84  */ { 18, { D_8085DA80 } },
    /* PLAYER_CSMODE_85  */ { 12, { &gameplay_keep_Linkanim_00CFD0 } },
    /* PLAYER_CSMODE_86  */ { 11, { NULL } },
    /* PLAYER_CSMODE_87  */ { 11, { NULL } },
    /* PLAYER_CSMODE_88  */ { 11, { NULL } },
    /* PLAYER_CSMODE_89  */ { 11, { NULL } },
    /* PLAYER_CSMODE_90  */ { 11, { NULL } },
    /* PLAYER_CSMODE_91  */ { 11, { NULL } },
    /* PLAYER_CSMODE_92  */ { 11, { NULL } },
    /* PLAYER_CSMODE_93  */ { -1, { func_8085A940 } },
    /* PLAYER_CSMODE_94  */ { 12, { &gameplay_keep_Linkanim_00D008 } },
    /* PLAYER_CSMODE_95  */ { 11, { NULL } },
    /* PLAYER_CSMODE_96  */ { -1, { func_8085A4A4 } },
    /* PLAYER_CSMODE_97  */ { -1, { func_8085A5DC } },
    /* PLAYER_CSMODE_98  */ { -1, { func_8085AA84 } },
    /* PLAYER_CSMODE_99  */ { 11, { NULL } },
    /* PLAYER_CSMODE_100 */ { 12, { &gameplay_keep_Linkanim_00CFA8 } },
    /* PLAYER_CSMODE_101 */ { 12, { &gameplay_keep_Linkanim_00CFF8 } },
    /* PLAYER_CSMODE_102 */ { -1, { func_8085A7C0 } },
    /* PLAYER_CSMODE_103 */ { 11, { NULL } },
    /* PLAYER_CSMODE_104 */ { 13, { &gameplay_keep_Linkanim_00D078 } },
    /* PLAYER_CSMODE_105 */ { 13, { &gameplay_keep_Linkanim_00D360 } },
    /* PLAYER_CSMODE_106 */ { 13, { &gameplay_keep_Linkanim_00D338 } },
    /* PLAYER_CSMODE_107 */ { 13, { &gameplay_keep_Linkanim_00D348 } },
    /* PLAYER_CSMODE_108 */ { 11, { NULL } },
    /* PLAYER_CSMODE_109 */ { 11, { NULL } },
    /* PLAYER_CSMODE_110 */ { 11, { NULL } },
    /* PLAYER_CSMODE_111 */ { 12, { &gameplay_keep_Linkanim_00D9F0 } },
    /* PLAYER_CSMODE_112 */ { 13, { &gameplay_keep_Linkanim_00D110 } },
    /* PLAYER_CSMODE_113 */ { 13, { &gameplay_keep_Linkanim_00D120 } },
    /* PLAYER_CSMODE_114 */ { 11, { NULL } },
    /* PLAYER_CSMODE_115 */ { -1, { func_8085AA10 } },
    /* PLAYER_CSMODE_116 */ { 11, { NULL } },
    /* PLAYER_CSMODE_117 */ { -1, { func_8085A364 } },
    /* PLAYER_CSMODE_118 */ { 11, { NULL } },
    /* PLAYER_CSMODE_119 */ { 11, { NULL } },
    /* PLAYER_CSMODE_120 */ { 11, { NULL } },
    /* PLAYER_CSMODE_121 */ { -1, { func_808599DC } },
    /* PLAYER_CSMODE_122 */ { -1, { func_80859AF8 } },
    /* PLAYER_CSMODE_123 */ { -1, { func_80859A44 } },
    /* PLAYER_CSMODE_124 */ { 11, { NULL } },
    /* PLAYER_CSMODE_125 */ { 11, { NULL } },
    /* PLAYER_CSMODE_126 */ { 11, { NULL } },
    /* PLAYER_CSMODE_127 */ { 12, { &gameplay_keep_Linkanim_00D5C8 } },
    /* PLAYER_CSMODE_128 */ { 11, { NULL } },
    /* PLAYER_CSMODE_129 */ { 12, { &gameplay_keep_Linkanim_00E4A8 } },
    /* PLAYER_CSMODE_130 */ { 11, { NULL } },
    /* PLAYER_CSMODE_131 */ { 11, { NULL } },
    /* PLAYER_CSMODE_132 */ { 11, { NULL } },
    /* PLAYER_CSMODE_133 */ { 11, { NULL } },
    /* PLAYER_CSMODE_134 */ { -1, { func_80859D44 } },
    /* PLAYER_CSMODE_135 */ { 11, { NULL } },
    /* PLAYER_CSMODE_136 */ { 12, { &gameplay_keep_Linkanim_00E4A0 } },
    /* PLAYER_CSMODE_137 */ { -1, { func_80859EBC } },
    /* PLAYER_CSMODE_138 */ { -1, { func_80859F4C } },
    /* PLAYER_CSMODE_139 */ { -1, { func_80859F4C } },
};

LinkAnimationHeader* D_8085E354[PLAYER_FORM_MAX] = {
    &gameplay_keep_Linkanim_00E4B8, &gameplay_keep_Linkanim_00E4B8, &gameplay_keep_Linkanim_00E4B8,
    &gameplay_keep_Linkanim_00E4B8, &gameplay_keep_Linkanim_00E160,
};

struct_8085E368 D_8085E368[PLAYER_FORM_MAX] = {
    /* PLAYER_FORM_FIERCE_DEITY */ { { -200, 700, 100 }, { 800, 600, 800 } },
    /* PLAYER_FORM_GORON        */ { { -200, 700, 100 }, { 800, 600, 800 } },
    /* PLAYER_FORM_ZORA         */ { { -200, 700, 100 }, { 800, 600, 800 } },
    /* PLAYER_FORM_DEKU         */ { { -200, 700, 100 }, { 800, 600, 800 } },
    /* PLAYER_FORM_HUMAN        */ { { -200, 500, 0 }, { 600, 400, 600 } },
};

Color_RGBA8 D_8085E3A4 = { 255, 255, 255, 0 };
Color_RGBA8 D_8085E3A8 = { 0, 128, 128, 0 };

void func_80859D70(PlayState* play, Player* this, UNK_TYPE arg2) {
    struct_8085E368* posInfo;
    Vec3f effectPos;
    Vec3f randPos;

    func_808591BC(play, this, D_8085E354[this->transformation]);

    if (this->rightHandType != 0xFF) {
        this->rightHandType = 0xFF;
    } else {
        posInfo = &D_8085E368[this->transformation];
        randPos.x = randPlusMinusPoint5Scaled(posInfo->range.x) + posInfo->base.x;
        randPos.y = randPlusMinusPoint5Scaled(posInfo->range.y) + posInfo->base.y;
        randPos.z = randPlusMinusPoint5Scaled(posInfo->range.z) + posInfo->base.z;
        SkinMatrix_Vec3fMtxFMultXYZ(&this->shieldMf, &randPos, &effectPos);
        EffectSsKirakira_SpawnDispersed(play, &effectPos, &gZeroVec3f, &gZeroVec3f, &D_8085E3A4, &D_8085E3A8, 600, -10);
    }
}

void func_80859EBC(PlayState* play, Player* this, s32 arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8085AACC(play, this, arg2);
    } else if (this->unk_AE8 == 0) {
        Item_Give(play, ITEM_SWORD_RAZOR);
        func_80841358(play, this, false);
    } else {
        func_808484CC(this);
    }
}

void func_80859F4C(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime) != 0) {
        func_8083FCF0(play, this, 0.0f, 99.0f, this->skelAnime.endFrame - 8.0f);
    }
    if (this->itemActionParam != PLAYER_AP_SWORD_GILDED) {
        func_80841358(play, this, true);
    }
}

void func_80859FCC(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (this->transformation != PLAYER_FORM_DEKU) {
        gSaveContext.save.playerForm = PLAYER_FORM_DEKU;
    }
}

void func_80859FF4(PlayState* play, Player* this, UNK_TYPE arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
    if (gSaveContext.save.playerForm != this->transformation) {
        this->actor.update = func_8012301C;
        this->actor.draw = NULL;
    }
}

void func_8085A04C(PlayState* play, Player* this, void* arg) {
    CsCmdActorAction* playerAction = arg;
    f32 xEnd = playerAction->endPos.x;
    f32 yEnd = playerAction->endPos.y;
    f32 zEnd = playerAction->endPos.z;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 progress;

    xDiff = playerAction->startPos.x - xEnd;
    yDiff = playerAction->startPos.y - yEnd;
    zDiff = playerAction->startPos.z - zEnd;

    progress = ((f32)(playerAction->endFrame - play->csCtx.frames)) /
               ((f32)(playerAction->endFrame - playerAction->startFrame));

    this->actor.world.pos.x = (xDiff * progress) + xEnd;
    this->actor.world.pos.y = (yDiff * progress) + yEnd;
    this->actor.world.pos.z = (zDiff * progress) + zEnd;
    LinkAnimation_Update(play, &this->skelAnime);
}

void func_8085A120(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (this->transformation != PLAYER_FORM_FIERCE_DEITY) {
        gSaveContext.save.playerForm = PLAYER_FORM_FIERCE_DEITY;
    }
}

void func_8085A144(PlayState* play, Player* this, UNK_TYPE arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
    if (gSaveContext.save.playerForm != this->transformation) {
        this->actor.update = func_8012301C;
        this->actor.draw = NULL;
    }
}

void func_8085A19C(PlayState* play, Player* this, UNK_TYPE arg2) {
    Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00D2D0);
    this->unk_AAA = -0x8000;
}

void func_8085A1D4(PlayState* play, Player* this, UNK_TYPE arg2) {
    LinkAnimation_Update(play, &this->skelAnime);
    this->actor.gravity = 0.0f;
    Math_StepToF(&this->actor.velocity.y, -this->actor.terminalVelocity, -((f32)REG(68) / 100.0f));
}

void func_8085A24C(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_8082DB90(play, this, D_8085D17C[this->transformation]);
    this->heldItemActionParam = PLAYER_AP_OCARINA;
    Player_SetModels(this, Player_ActionToModelGroup(this, (enum PlayerActionParam)this->heldItemActionParam));
}

void func_8085A2AC(PlayState* play, Player* this, UNK_TYPE arg2) {
    if ((LinkAnimation_Update(play, &this->skelAnime)) &&
        (this->skelAnime.animation == D_8085D17C[this->transformation])) {
        func_808525C4(play, this);
        return;
    }
    if (this->unk_AE8 != 0) {
        func_8085255C(play, this);
    }
}

void func_8085A330(PlayState* play, Player* this, UNK_TYPE arg2) {
    Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
}

void func_8085A364(PlayState* play, Player* this, void* arg2) {
    func_80859BA8(play, this, arg2);
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_8082EB18(play, this, &gameplay_keep_Linkanim_00D100);
    }

    if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D0B8) {
        Player_PlayAnimSfx(this, D_8085DA48);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D028) {
        func_800B8F98(&this->actor, NA_SE_PL_FLYING_AIR - SFX_FLAG);
    } else {
        func_80858FE8(this);
    }
}

void func_8085A40C(PlayState* play, Player* this, void* arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        func_80859CA0(play, this, arg2);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00CF58) {
        Player_PlayAnimSfx(this, D_8085DA88);
    } else if (this->skelAnime.animation == &gameplay_keep_Linkanim_00D090) {
        Player_PlayAnimSfx(this, D_8085DA8C);
    }
}

void func_8085A4A4(PlayState* play, Player* this, void* arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime) && (this->unk_AE8 == 0) && (this->actor.bgCheckFlags & 1)) {
        Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DAD8);
        this->unk_AE8 = 1;
    }
    if (this->unk_AE8 != 0) {
        func_80832F24(this);
    }
}

void func_8085A530(PlayState* play, Player* this, void* arg2) {
    LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00DCA8, 1.0f,
                         (play->sceneNum == SCENE_ALLEY) ? IREG(56) : 0.0f,
                         Animation_GetLastFrame(&gameplay_keep_Linkanim_00DCA8), ANIMMODE_ONCE, -8.0f);
}

void func_8085A5DC(PlayState* play, Player* this, void* arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE8++ >= 0x15) {
            LinkAnimation_Change(play, &this->skelAnime, &gameplay_keep_Linkanim_00E410, 1.0f, 0.0f, 0.0f,
                                 ANIMMODE_LOOP, -16.0f);
        }
    }
}

void func_8085A66C(PlayState* play, Player* this, void* arg2) {
    if (func_801242B4(this)) {
        func_8085929C(play, this, 0);
    } else {
        func_80858E40(play, this, &gameplay_keep_Linkanim_00D638);
    }
}

void func_8085A6C0(PlayState* play, Player* this, void* arg2) {
    if (func_801242B4(this)) {
        func_80859300(play, this, 0);
    } else {
        func_80858FBC(play, this, (LinkAnimationHeader*)arg2);
    }
}

void func_8085A710(PlayState* play, Player* this, void* arg2) {
    func_80858FBC(play, this, (LinkAnimationHeader*)arg2);
    if (func_8083D23C(this, play)) {
        play->csCtx.state = CS_STATE_3;
        ActorCutscene_Stop(ActorCutscene_GetCurrentIndex());
    }
}

void func_8085A768(PlayState* play, Player* this, void* arg2) {
    func_80838830(this, OBJECT_GI_RESERVE_C_01);
    func_80858E40(play, this, &gameplay_keep_Linkanim_00DCA8);
    this->stateFlags2 &= ~PLAYER_STATE2_1000000;
}

void func_8085A7C0(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        if (this->unk_AE8 == 0) {
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) ||
                (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE)) {
                this->unk_B2A = 0;
                this->unk_AE8 = -1;
            } else {
                this->unk_B2A = 0x6F;
            }
        } else if (this->unk_AE8 < 0) {
            if (Actor_HasParent(&this->actor, play)) {
                this->actor.parent = NULL;
                this->unk_AE8 = 1;
            } else {
                Actor_PickUp(&this->actor, play, GI_PENDANT_OF_MEMORIES, 9999.9f, 9999.9f);
            }
        }
    } else if (LinkAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        gSaveContext.save.weekEventReg[50] |= 0x80;
    }
}

void func_8085A8C4(PlayState* play, Player* this, UNK_TYPE arg2) {
    if ((this->transformation != PLAYER_FORM_HUMAN) && (play->roomCtx.currRoom.unk3 == 5)) {
        MREG(64) = 0x2D;
        MREG(65) = 0xFF;
        MREG(66) = 0xFF;
        MREG(67) = 0xFF;
        MREG(68) = 0;
        play_sound(NA_SE_SY_WHITE_OUT_T);
    }
}

void func_8085A940(PlayState* play, Player* this, UNK_TYPE arg2) {
    s16 temp_v1 = MREG(64);

    if (temp_v1 > 0) {
        MREG(68) += temp_v1;
        if (MREG(68) >= 0x100) {
            MREG(64) = -0x40;
            MREG(68) = 0xFF;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->unk_AE7 = 0;
        }
    } else if (temp_v1 < 0) {
        MREG(68) += temp_v1;
        if (MREG(68) < 0) {
            MREG(64) = 0;
            MREG(68) = 0;
        }
    } else {
        LinkAnimation_Update(play, &this->skelAnime);
    }
}

void func_8085AA10(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime) && (ActorCutscene_GetCurrentIndex() == 0x7D)) {
        ActorCutscene_Stop(0x7D);
    }
}

void func_8085AA60(PlayState* play, Player* this, UNK_TYPE arg2) {
    func_80848640(play, this);
}

void func_8085AA84(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (LinkAnimation_Update(play, &this->skelAnime)) {
        this->stateFlags2 |= PLAYER_STATE2_1000000;
    }
}

void func_8085AACC(PlayState* play, Player* this, UNK_TYPE arg2) {
    if (func_801242B4(this)) {
        func_808353DC(play, this);
        func_8082DC64(play, this);
    } else {
        func_80839ED0(this, play);
        if (!func_808391D8(this, play)) {
            func_8083D23C(this, play);
        }
    }

    this->csMode = PLAYER_CSMODE_0;
    this->unk_AA5 = 0;
}

void func_8085AB58(Player* this, CsCmdActorAction* playerAction) {
    this->actor.world.pos.x = playerAction->startPos.x;
    this->actor.world.pos.y = playerAction->startPos.y;
    this->actor.world.pos.z = playerAction->startPos.z;

    this->currentYaw = this->actor.shape.rot.y = playerAction->rot.y;
}

void func_8085ABA8(Player* this, CsCmdActorAction* playerAction) {
    f32 xDiff = playerAction->startPos.x - (s32)this->actor.world.pos.x;
    f32 yDiff = playerAction->startPos.y - (s32)this->actor.world.pos.y;
    f32 zDiff = playerAction->startPos.z - (s32)this->actor.world.pos.z;
    f32 dist;
    s16 temp_v0;

    temp_v0 = playerAction->rot.y - this->actor.shape.rot.y;
    dist = sqrtf(SQ(xDiff) + SQ(yDiff) + SQ(zDiff));
    if (this->linearVelocity == 0.0f) {
        if ((dist > 50.0f) || (ABS_ALT(temp_v0) > 0x4000)) {
            func_8085AB58(this, playerAction);
        }
    }

    this->skelAnime.moveFlags = 0;
    func_8082E784(this);
}

void func_8085AC9C(PlayState* play, Player* this, CsCmdActorAction* actorAction, struct_8085DA94* arg3) {
    if (arg3->type > 0) {
        D_8085D990[arg3->type](play, this, arg3->anim);
    } else if (arg3->type < 0) {
        arg3->func(play, this, actorAction);
    }

    if ((D_80862B6C & 4) && !(this->skelAnime.moveFlags & 4)) {
        this->skelAnime.morphTable[0].y /= this->ageProperties->unk_08;
        D_80862B6C = 0;
    }
}

void func_8085AD5C(PlayState* play, Player* this, s32 csMode) {
    if ((csMode != PLAYER_CSMODE_1) && (csMode != PLAYER_CSMODE_7) && (csMode != PLAYER_CSMODE_20) &&
        (csMode != PLAYER_CSMODE_6)) {
        func_8082DCA0(play, this);
    }
}

void func_8085ADA0(PlayState* play, Player* this, UNK_TYPE arg2) {
    CsCmdActorAction* actorAction;
    u16 temp_t3;
    u8 var_v1;
    s32 var_a0;

    actorAction = (this->actor.id == ACTOR_EN_TEST3)
                      ? play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x1FA)]
                      : play->csCtx.playerAction;

    var_a0 = false;

    if ((play->csCtx.state == CS_STATE_0) || (play->csCtx.state == CS_STATE_3) || (play->csCtx.state == CS_STATE_4)) {
        if ((D_8085D384[this->unk_396] == 0x44) && (play->sceneNum == SCENE_OKUJOU)) {
            this->unk_AA5 = 5;

            if (func_80838A90(this, play)) {
                this->csMode = PLAYER_CSMODE_0;
            }
            return;
        } else {
            var_a0 = true;
            if (D_8085D384[this->unk_396] != 0x10) {
                this->csMode = PLAYER_CSMODE_6;
                func_800B7298(play, NULL, PLAYER_CSMODE_6);
                this->unk_396 = 0;
                func_8082DABC(this);
                return;
            }
        }
    }

    if (!var_a0 && (actorAction == NULL)) {
        this->actor.flags &= ~ACTOR_FLAG_40;
        return;
    }

    var_v1 = this->unk_396;
    if (!var_a0) {
        if (var_v1 != actorAction->action) {
            s32 csMode = D_8085D384[actorAction->action];

            if ((csMode >= PLAYER_CSMODE_0) && (D_801F4DE0 == 0)) {
                if ((csMode == PLAYER_CSMODE_2) || (csMode == PLAYER_CSMODE_3)) {
                    func_8085ABA8(this, actorAction);
                } else {
                    func_8085AB58(this, actorAction);
                }
            }

            if (csMode == PLAYER_CSMODE_108) {
                this->stateFlags3 |= PLAYER_STATE3_20000000;
            } else if (csMode == PLAYER_CSMODE_110) {
                this->stateFlags3 &= ~PLAYER_STATE3_20000000;
            }

            D_80862B6C = this->skelAnime.moveFlags;
            func_8082E794(this);

            func_8085AD5C(play, this, ABS_ALT(csMode));

            func_8085AC9C(play, this, actorAction, &D_8085DA94[ABS_ALT(csMode)]);
            this->unk_AE8 = 0;
            this->unk_AE7 = 0;

            //! FAKE
            temp_t3 = actorAction->action;
            this->unk_396 = (temp_t3 & 0xFF) & 0xFF;
            var_v1 = temp_t3 & 0xFF;
        }
    }

    func_8085AC9C(play, this, actorAction, &D_8085DEF4[ABS_ALT(D_8085D384[var_v1])]);

    if ((u16)actorAction->rot.x != 0) {
        Math_SmoothStepToS(&this->actor.focus.rot.x, (u16)actorAction->rot.x, 4, 0x2710, 0);
        func_80832754(this, false);
    }
}

void func_8085B08C(Player* this, PlayState* play) {
    if (this->csMode != this->prevCsMode) {
        D_80862B6C = this->skelAnime.moveFlags;
        func_8082E794(this);

        this->prevCsMode = this->csMode;
        func_8085AD5C(play, this, this->csMode);
        func_8085AC9C(play, this, NULL, &D_8085DA94[this->csMode]);
    }

    func_8085AC9C(play, this, NULL, &D_8085DEF4[this->csMode]);
}

s32 Player_StartFishing(PlayState* play) {
    Player* player = GET_PLAYER(play);

    func_8082DE50(play, player);
    func_80831990(play, player, ITEM_FISHING_POLE);
    return 1;
}

// Player_GrabPlayerImpl? Player_GrabPlayerNoChecks?
void func_8085B170(PlayState* play, Player* this) {
    func_8082DE50(play, this);
    Player_SetAction(play, this, func_80853CC0, 0);
    Player_AnimationPlayOnce(play, this, &gameplay_keep_Linkanim_00DE28);
    this->stateFlags2 |= PLAYER_STATE2_80;
    func_8082DAD4(this);
    func_8082DF8C(this, NA_SE_VO_LI_HELD);
}

s32 Player_GrabPlayer(PlayState* play, Player* player) {
    if (!Player_InBlockingCsMode(play, player) && (player->invincibilityTimer >= 0) && !func_801240DC(player)) {
        if (!(player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000 |
                                     PLAYER_STATE1_200000 | PLAYER_STATE1_800000))) {
            if (!(player->stateFlags2 & PLAYER_STATE2_80) && !(player->stateFlags3 & PLAYER_STATE3_80)) {
                func_8085B170(play, player);
                return true;
            }
        }
    }

    return false;
}

s32 func_8085B28C(PlayState* play, Player* this, s32 mode) {
    Player* player = GET_PLAYER(play);

    if (this != NULL) {
        if (mode == 0) {
            return func_8084E034 == this->actionFunc;
        }

        if ((this->actor.id == ACTOR_EN_TEST3) && (mode < 0)) {
            func_8083B0E4(play, this, this->actor.home.rot.y);
            return false;
        }

        if (this->actor.id == ACTOR_EN_TEST3) {
            player = this;
        }
    }

    if ((player->actor.id == ACTOR_EN_TEST3) || !Player_InBlockingCsMode(play, player)) {
        func_8082DE50(play, player);
        Player_SetAction(play, player, func_8085B08C, 0);
        player->csMode = mode;
        player->unk_398 = &this->actor;
        func_8082DAD4(player);

        return true;
    }

    return false;
}

void func_8085B384(Player* this, PlayState* play) {
    Player_SetAction(play, this, func_80849FE0, 1);
    func_8082E438(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

s32 Player_InflictDamage(PlayState* play, s32 damage) {
    Player* player = GET_PLAYER(play);

    if ((player->stateFlags2 & PLAYER_STATE2_80) || !Player_InBlockingCsMode(play, player)) {
        if (!func_808339D4(play, player, damage)) {
            player->stateFlags2 &= ~PLAYER_STATE2_80;
            return true;
        }
    }

    return false;
}

// Start talking with the given actor
void func_8085B460(PlayState* play, Actor* actor) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    func_808323C0(player, 0x7C);
    if ((player->talkActor != NULL) || (actor == player->tatlActor) ||
        CHECK_FLAG_ALL(actor->flags, ACTOR_FLAG_1 | ACTOR_FLAG_40000)) {
        actor->flags |= ACTOR_FLAG_100;
    }

    player->talkActor = actor;
    player->exchangeItemId = PLAYER_AP_NONE;
    player->targetedActor = actor;

    if (actor->textId == 0xFFFF) {
        func_800B7298(play, actor, PLAYER_CSMODE_1);
        actor->flags |= ACTOR_FLAG_100;
        func_8082DE14(play, player);
    } else {
        if (player->actor.flags & ACTOR_FLAG_100) {
            player->actor.textId = 0;
        } else {
            player->actor.flags |= ACTOR_FLAG_100;
            player->actor.textId = actor->textId;
        }

        if (player->stateFlags1 & PLAYER_STATE1_800000) {
            s32 sp24 = player->unk_AE8;

            func_8082DE14(play, player);
            func_80837B60(play, player);
            player->unk_AE8 = sp24;
        } else {
            if (func_801242B4(player)) {
                func_80832558(play, player, func_80837B60);
                func_8082E634(play, player, &gameplay_keep_Linkanim_00E000);
            } else if ((actor->category != ACTORCAT_NPC) || (player->itemActionParam == PLAYER_AP_FISHING_POLE)) {
                func_80837B60(play, player);

                if (!func_80123420(player)) {
                    if ((actor != player->tatlActor) && (actor->xzDistToPlayer < (actor->colChkInfo.cylRadius + 40))) {
                        func_8082DB90(play, player, &gameplay_keep_Linkanim_00DB10);
                    } else {
                        Player_AnimationPlayLoop(play, player, func_8082ED20(player));
                    }
                }
            } else {
                func_80832558(play, player, func_80837B60);
                func_8082DB90(play, player,
                              (actor->xzDistToPlayer < (actor->colChkInfo.cylRadius + 40))
                                  ? &gameplay_keep_Linkanim_00DB10
                                  : &gameplay_keep_Linkanim_00DEA0);
            }

            if (player->skelAnime.animation == &gameplay_keep_Linkanim_00DB10) {
                func_8082E920(play, player, 1 | 8 | 0x10);
            }
            func_8082DAD4(player);
        }

        player->stateFlags1 |= PLAYER_STATE1_40 | PLAYER_STATE1_20000000;
    }

    if ((player->tatlActor == player->talkActor) && ((player->talkActor->textId & 0xFF00) != 0x200)) {
        player->tatlActor->flags |= ACTOR_FLAG_100;
    }
}

void func_8085B74C(PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_fv1;
    f32 linearVelocity = player->linearVelocity;

    if (linearVelocity < 0.0f) {
        linearVelocity = -linearVelocity;
        player->actor.world.rot.y += 0x8000;
    }

    temp_fv1 = REG(45) / 100.0f;

    if (temp_fv1 < linearVelocity) {
        gSaveContext.entranceSpeed = temp_fv1;
    } else {
        gSaveContext.entranceSpeed = linearVelocity;
    }

    func_80835324(play, player, 400.0f, (D_80862B10 != 0) ? D_80862B16 : player->actor.world.rot.y);
    player->stateFlags1 |= (PLAYER_STATE1_1 | PLAYER_STATE1_20000000);
}

void func_8085B820(PlayState* play, s16 arg1) {
    Player* player = GET_PLAYER(play);

    player->actor.focus.rot.y = arg1;
    func_80836D8C(player);
}

PlayerActionParam func_8085B854(PlayState* play, Player* player, ItemID itemId) {
    PlayerActionParam actionParam = Player_ItemToActionParam(player, itemId);

    if ((actionParam >= PLAYER_AP_MASK_TRUTH) && (actionParam <= PLAYER_AP_MASK_DEKU) &&
        (actionParam == (player->currentMask + PLAYER_AP_MASK_TRUTH - 1))) {
        actionParam = PLAYER_AP_NONE;
    }

    if ((actionParam <= PLAYER_AP_NONE) || (actionParam >= PLAYER_AP_MAX)) {
        return -1;
    }

    player->heldItemActionParam = PLAYER_AP_NONE;
    player->actionFunc = NULL;
    func_80831760(play, player, func_80853A5C, 0);
    player->unk_A86 = 0x7C;
    player->heldItemActionParam = actionParam;
    Player_AnimationPlayOnce(play, player, &gameplay_keep_Linkanim_00DCA8);
    player->stateFlags1 |= (PLAYER_STATE1_40 | PLAYER_STATE1_20000000);
    player->unk_B2A = 0;
    player->exchangeItemId = actionParam;

    return actionParam;
}

s32 func_8085B930(PlayState* play, LinkAnimationHeader* talkAnim, s32 animMode) {
    Player* player = GET_PLAYER(play);

    if (!(player->actor.flags & ACTOR_FLAG_100)) {
        return false;
    }

    LinkAnimation_Change(play, &player->skelAnime, (talkAnim == NULL) ? func_8082ED20(player) : talkAnim, 2.0f / 3.0f,
                         0.0f, Animation_GetLastFrame(talkAnim), animMode, -6.0f);
    return true;
}
