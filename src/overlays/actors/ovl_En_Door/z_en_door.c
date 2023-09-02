/*
 * File: z_en_door.c
 * Overlay: ovl_En_Door
 * Description: Wooden Door
 */

#include "z_en_door.h"
#include "objects/object_kinsta2_obj/object_kinsta2_obj.h"
#include "objects/object_dor01/object_dor01.h"
#include "objects/object_dor02/object_dor02.h"
#include "objects/object_dor03/object_dor03.h"
#include "objects/object_dor04/object_dor04.h"
#include "objects/object_wdor01/object_wdor01.h"
#include "objects/object_wdor02/object_wdor02.h"
#include "objects/object_wdor03/object_wdor03.h"
#include "objects/object_wdor04/object_wdor04.h"
#include "objects/object_wdor05/object_wdor05.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnDoor*)thisx)

void EnDoor_Init(Actor* thisx, PlayState* play2);
void EnDoor_Destroy(Actor* thisx, PlayState* play);
void EnDoor_Update(Actor* thisx, PlayState* play);
void EnDoor_Draw(Actor* thisx, PlayState* play);

void func_80866B20(EnDoor*, PlayState*);
void func_8086704C(EnDoor*, PlayState*);
void func_80866F94(EnDoor*, PlayState*);
void func_80867080(EnDoor*, PlayState*);
void func_80867144(EnDoor*, PlayState*);
void func_808670F0(EnDoor*, PlayState*);
void func_80866A5C(EnDoor*, PlayState*);

u8 D_808675D0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x12 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 23, 0, 0x12 - 0x0A),
    /* 0x0A */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x12 - 0x10),
    /* 0x10 */ SCHEDULE_CMD_RET_VAL_S(7),
    /* 0x12 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808675E4[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(9, 0, 0x4B - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(12, 0, 0x1D - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x1F - 0x0C),
    /* 0x0C */ SCHEDULE_CMD_BRANCH_S(0x0),
    /* 0x0E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x1C - 0x12),
    /* 0x12 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(15, 0, 0x1D - 0x16),
    /* 0x16 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(0, 0, 0x1C - 0x1A),
    /* 0x1A */ SCHEDULE_CMD_RET_VAL_S(9),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_S(8),
    /* 0x1F */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x3C - 0x23),
    /* 0x23 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_28_08, 0x2E - 0x27),
    /* 0x27 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x2D - 0x2B),
    /* 0x2B */ SCHEDULE_CMD_RET_VAL_S(9),
    /* 0x2D */ SCHEDULE_CMD_RET_NONE(),
    /* 0x2E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x1C - 0x32),
    /* 0x32 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(17, 0, 0x1D - 0x36),
    /* 0x36 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(0, 0, 0x1C - 0x3A),
    /* 0x3A */ SCHEDULE_CMD_RET_VAL_S(9),
    /* 0x3C */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x1C - 0x40),
    /* 0x40 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x1D - 0x44),
    /* 0x44 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(18, 0, 0x49 - 0x48),
    /* 0x48 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x49 */ SCHEDULE_CMD_RET_VAL_S(9),
    /* 0x4B */ SCHEDULE_CMD_RET_VAL_S(9),
};

u8 D_80867634[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 23, 0, 0x8 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_S(28),
    /* 0x8 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867640[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 22, 0, 0x7 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x7 */ SCHEDULE_CMD_RET_VAL_S(11),
};

u8 D_8086764C[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(22, 0, 5, 0, 0x8 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_S(10),
    /* 0x8 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867658[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x13 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_28_08, 0x0A - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_S(12),
    /* 0x0A */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 10, 22, 0, 0x12 - 0x10),
    /* 0x10 */ SCHEDULE_CMD_RET_VAL_S(12),
    /* 0x12 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x13 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x28 - 0x17),
    /* 0x17 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(13, 0, 0x28 - 0x1B),
    /* 0x1B */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_51_08, 0x21 - 0x1F),
    /* 0x1F */ SCHEDULE_CMD_RET_VAL_S(12),
    /* 0x21 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(22, 0, 0x27 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_RET_VAL_S(12),
    /* 0x27 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x28 */ SCHEDULE_CMD_RET_VAL_S(12),
};

u8 D_80867684[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867688[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(22, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(15),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867690[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(22, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(16),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867698[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(22, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(17),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676A0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 0, 21, 0, 0x15 - 0x06),
    /* 0x06 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(22, 0, 5, 0, 0x0E - 0x0C),
    /* 0x0C */ SCHEDULE_CMD_RET_VAL_S(18),
    /* 0x0E */ SCHEDULE_CMD_CHECK_MISC_S(SCHEDULE_CHECK_MISC_MASK_ROMANI, 0x13 - 0x11),
    /* 0x11 */ SCHEDULE_CMD_RET_VAL_S(34),
    /* 0x13 */ SCHEDULE_CMD_RET_VAL_S(33),
    /* 0x15 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676B8[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_MISC_S(SCHEDULE_CHECK_MISC_ROOM_KEY, 0x17 - 0x03),
    /* 0x03 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0E - 0x07),
    /* 0x07 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(8, 0, 0x0C - 0x0B),
    /* 0x0B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0C */ SCHEDULE_CMD_RET_VAL_S(19),
    /* 0x0E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(8, 0, 20, 30, 0x16 - 0x14),
    /* 0x14 */ SCHEDULE_CMD_RET_VAL_S(19),
    /* 0x16 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x17 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676D0[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676D4[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676D8[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x9 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(18, 0, 0x9 - 0x8),
    /* 0x8 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_S(20),
};

u8 D_808676E4[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_MISC_S(SCHEDULE_CHECK_MISC_ROOM_KEY, 0x5 - 0x3),
    /* 0x3 */ SCHEDULE_CMD_RET_VAL_S(22),
    /* 0x5 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676EC[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_808676F0[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x9 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(10, 0, 0xF - 0x8),
    /* 0x8 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x9 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 0, 20, 0, 0x8 - 0xF),
    /* 0xF */ SCHEDULE_CMD_RET_VAL_S(21),
};

u8 D_80867704[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867708[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_8086770C[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867710[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867714[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(20, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(23),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_8086771C[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x0B - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(2, 30, 0x0A - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_S(24),
    /* 0x0A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0A - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(20, 0, 0x0A - 0x13),
    /* 0x13 */ SCHEDULE_CMD_RET_VAL_S(12),
};

u8 D_80867734[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(20, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(25),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_8086773C[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(20, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(26),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867744[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x08 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_99_80, 0x0E - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(20, 0, 0x14 - 0x0C),
    /* 0x0C */ SCHEDULE_CMD_RET_VAL_S(27),
    /* 0x0E */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(18, 0, 0x14 - 0x12),
    /* 0x12 */ SCHEDULE_CMD_RET_VAL_S(27),
    /* 0x14 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_8086775C[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE, 0x1B - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_75_20, 0x1B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_14_04, 0x0E - 0x0C),
    /* 0x0C */ SCHEDULE_CMD_RET_VAL_S(29),
    /* 0x0E */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_59_01, 0x1A - 0x12),
    /* 0x12 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_61_02, 0x18 - 0x16),
    /* 0x16 */ SCHEDULE_CMD_RET_VAL_S(30),
    /* 0x18 */ SCHEDULE_CMD_RET_VAL_S(31),
    /* 0x1A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1B */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867778[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_VAL_S(32),
};

u8 D_8086777C[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867780[] = {
    /* 0x0 */ SCHEDULE_CMD_RET_NONE(),
};

u8 D_80867784[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_BEFORE_TIME_S(22, 0, 0x6 - 0x4),
    /* 0x4 */ SCHEDULE_CMD_RET_VAL_S(35),
    /* 0x6 */ SCHEDULE_CMD_RET_NONE(),
};

u8* D_8086778C[] = {
    D_808675D0, D_808675E4, D_80867634, D_80867640, D_8086764C, D_80867658, D_80867684, D_80867688,
    D_80867690, D_80867698, D_808676A0, D_808676B8, D_808676D0, D_808676D4, D_808676D8, D_808676E4,
    D_808676EC, D_808676F0, D_80867704, D_80867708, D_8086770C, D_80867710, D_80867714, D_8086771C,
    D_80867734, D_8086773C, D_80867744, D_8086775C, D_80867778, D_8086777C, D_80867780, D_80867784,
};

ActorInit En_Door_InitVars = {
    /**/ ACTOR_EN_DOOR,
    /**/ ACTORCAT_DOOR,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnDoor),
    /**/ EnDoor_Init,
    /**/ EnDoor_Destroy,
    /**/ EnDoor_Update,
    /**/ EnDoor_Draw,
};

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ u8 dListIndex;
    /* 0x4 */ s16 objectId;
} EnDoorInfo; // size = 0x6

static EnDoorInfo sObjInfo[] = {
    { SCENE_MITURIN, 0x01, OBJECT_NUMA_OBJ },
    { SCENE_TENMON_DAI, 0x02, OBJECT_DOR01 },
    { SCENE_00KEIKOKU, 0x02, OBJECT_DOR01 },
    { SCENE_30GYOSON, 0x02, OBJECT_DOR01 },
    { SCENE_LABO, 0x02, OBJECT_DOR01 },
    { SCENE_33ZORACITY, 0x03, OBJECT_DOR02 },
    { SCENE_UNSET_31, 0x03, OBJECT_DOR02 },
    { SCENE_BANDROOM, 0x03, OBJECT_DOR02 },
    { SCENE_20SICHITAI, 0x04, OBJECT_DOR03 },
    { SCENE_20SICHITAI2, 0x04, OBJECT_DOR03 },
    { SCENE_MAP_SHOP, 0x04, OBJECT_DOR03 },
    { SCENE_KAIZOKU, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_PIRATE, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_TORIDE, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_KINDAN2, 0x0C, OBJECT_KINSTA2_OBJ },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0A, OBJECT_WDOR05 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x05, OBJECT_DOR04 },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x04, OBJECT_DOR03 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, TARGET_MODE_0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.x, 0, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.z, 0, ICHAIN_STOP),
};

static AnimationHeader* sAnimations[2 * PLAYER_FORM_MAX] = {
    // left
    &gameplay_keep_Anim_020658, // PLAYER_FORM_FIERCE_DEITY
    &gameplay_keep_Anim_022CA8, // PLAYER_FORM_GORON
    &gameplay_keep_Anim_020658, // PLAYER_FORM_ZORA
    &gameplay_keep_Anim_022E68, // PLAYER_FORM_DEKU
    &gameplay_keep_Anim_0204B4, // PLAYER_FORM_HUMAN
    // right
    &gameplay_keep_Anim_022BE8, // PLAYER_FORM_FIERCE_DEITY
    &gameplay_keep_Anim_022D90, // PLAYER_FORM_GORON
    &gameplay_keep_Anim_022BE8, // PLAYER_FORM_ZORA
    &gameplay_keep_Anim_022FF0, // PLAYER_FORM_DEKU
    &gameplay_keep_Anim_0205A0, // PLAYER_FORM_HUMAN
};
static u8 sAnimOpenFrames[2 * PLAYER_FORM_MAX] = {
    // left
    25, // PLAYER_FORM_FIERCE_DEITY
    25, // PLAYER_FORM_GORON
    25, // PLAYER_FORM_ZORA
    25, // PLAYER_FORM_DEKU
    25, // PLAYER_FORM_HUMAN
    // right
    25, // PLAYER_FORM_FIERCE_DEITY
    25, // PLAYER_FORM_GORON
    25, // PLAYER_FORM_ZORA
    25, // PLAYER_FORM_DEKU
    25, // PLAYER_FORM_HUMAN
};

static u8 sAnimCloseFrames[2 * PLAYER_FORM_MAX] = {
    // left
    60, // PLAYER_FORM_FIERCE_DEITY
    60, // PLAYER_FORM_GORON
    60, // PLAYER_FORM_ZORA
    70, // PLAYER_FORM_DEKU
    70, // PLAYER_FORM_HUMAN
    // right
    60, // PLAYER_FORM_FIERCE_DEITY
    60, // PLAYER_FORM_GORON
    60, // PLAYER_FORM_ZORA
    60, // PLAYER_FORM_DEKU
    70, // PLAYER_FORM_HUMAN
};

static Gfx* D_808679A4[14][2] = {
    { gDoorLeftDL, gDoorRightDL },
    { gWoodfallDoorDL, gWoodfallDoorDL },
    { gObservatoryLabDoorDL, gObservatoryLabDoorDL },
    { gZoraHallDoorDL, gZoraHallDoorDL },
    { gSwampDoorDL, gSwampDoorDL },
    { gMagicHagPotionShopDoorDL, gMagicHagPotionShopDoorDL },
    { gLotteryCuriosityShopMayorHouseDoorDL, gLotteryCuriosityShopMayorHouseDoorDL },
    { gPostOfficeTradingPostDoorDL, gPostOfficeTradingPostDoorDL },
    { gInnSchoolDoorDL, gInnSchoolDoorDL },
    { gMilkBarDoorDL, gMilkBarDoorDL },
    { gMusicBoxHouseDoorDL, gMusicBoxHouseDoorDL },
    { gPiratesFortressDoorDL, gPiratesFortressDoorDL },
    { gOceansideSpiderHouseDoorDL, gOceansideSpiderHouseDoorDL },
    { gFieldWoodDoorLeftDL, gFieldWoodDoorRightDL },
};

void EnDoor_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    s32 objectBankIndex;
    EnDoorInfo* objectInfo = &sObjInfo[0];
    EnDoor* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->knobDoor.dyna.actor, sInitChain);

    this->doorType = ENDOOR_GET_TYPE(thisx);

    this->switchFlag = ENDOOR_GET_PARAM_7F(thisx);
    if ((this->doorType == ENDOOR_TYPE_7) && (this->switchFlag == 0)) {
        DynaPolyActor_Init(&this->knobDoor.dyna, 0);
        DynaPolyActor_LoadMesh(play, &this->knobDoor.dyna, &gDoorCol);
    }
    SkelAnime_Init(play, &this->knobDoor.skelAnime, &gDoorSkel, &gameplay_keep_Anim_020658, this->limbTable,
                   this->limbTable, DOOR_LIMB_MAX);
    if (this->doorType == ENDOOR_TYPE_5) {
        objectInfo = &sObjInfo[17 + this->switchFlag];
    } else {
        for (i = 0; i < ARRAY_COUNT(sObjInfo) - 34; i++, objectInfo++) {
            if (play->sceneId == objectInfo->sceneId) {
                break;
            }
        }
        if ((i >= ARRAY_COUNT(sObjInfo) - 34) && (Object_GetIndex(&play->objectCtx, GAMEPLAY_FIELD_KEEP) >= 0)) {
            objectInfo++;
        }
    }

    this->knobDoor.dlIndex = objectInfo->dListIndex;
    objectBankIndex = Object_GetIndex(&play->objectCtx, objectInfo->objectId);
    if (objectBankIndex < 0) {
        objectInfo = &sObjInfo[15];
        objectBankIndex = Object_GetIndex(&play->objectCtx, objectInfo->objectId);
        if (objectBankIndex != 0) {
            Actor_Kill(&this->knobDoor.dyna.actor);
            return;
        }
    }
    this->knobDoor.requiredObjBankIndex = objectBankIndex;
    this->knobDoor.dlIndex = objectInfo->dListIndex; // Set twice?
    if (this->knobDoor.dyna.actor.objBankIndex == this->knobDoor.requiredObjBankIndex) {
        func_80866A5C(this, play);
    } else {
        this->actionFunc = func_80866A5C;
    }
    Actor_SetFocus(&this->knobDoor.dyna.actor, 35.0f);
}

void EnDoor_Destroy(Actor* thisx, PlayState* play) {
    EnDoor* this = (EnDoor*)thisx;

    if (this->doorType != ENDOOR_TYPE_7) {
        TransitionActorEntry* transitionEntry =
            &play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&this->knobDoor.dyna.actor)];
        if (transitionEntry->id < 0) {
            transitionEntry->id = -transitionEntry->id;
        }
    } else if (this->switchFlag == 0) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->knobDoor.dyna.bgId);
    }
}

void func_80866A5C(EnDoor* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->knobDoor.requiredObjBankIndex)) {
        this->knobDoor.dyna.actor.objBankIndex = this->knobDoor.requiredObjBankIndex;
        this->actionFunc = func_80866B20;
        this->knobDoor.dyna.actor.world.rot.y = 0;
        if (this->doorType == ENDOOR_TYPE_1) {
            if (!Flags_GetSwitch(play, this->switchFlag)) {
                this->unk_1A6 = 10;
            }
        } else if ((this->doorType == ENDOOR_TYPE_4) &&
                   (Actor_WorldDistXZToActor(&this->knobDoor.dyna.actor, &GET_PLAYER(play)->actor) > 120.0f)) {
            this->actionFunc = func_8086704C;
            this->knobDoor.dyna.actor.world.rot.y = -0x1800;
        }
    }
}

void func_80866B20(EnDoor* this, PlayState* play) {
    static s32 D_80867BC0;
    Player* player = GET_PLAYER(play);

    if (Actor_ProcessTalkRequest(&this->knobDoor.dyna.actor, &play->state) &&
        (this->knobDoor.dyna.actor.textId == 0x1821)) {
        D_80867BC0 = true;
    }
    if (this->knobDoor.playOpenAnim) {
        this->actionFunc = func_80867144;
        Animation_PlayOnceSetSpeed(&this->knobDoor.skelAnime, sAnimations[this->knobDoor.animIndex],
                                   (player->stateFlags1 & PLAYER_STATE1_8000000) ? 0.75f : 1.5f);
        if (this->unk_1A6 != 0) {
            DUNGEON_KEY_COUNT(gSaveContext.mapIndex) = DUNGEON_KEY_COUNT(gSaveContext.mapIndex) - 1;
            Flags_SetSwitch(play, this->switchFlag);
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
        }
    } else if (this->unk_1A7 != 0) {
        this->actionFunc = func_80866F94;
        Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_OPEN);
    } else if (!Player_InCsMode(play)) {
        Vec3f playerPosRelToDoor;

        Actor_OffsetOfPointInActorCoords(&this->knobDoor.dyna.actor, &playerPosRelToDoor, &player->actor.world.pos);
        if (D_80867BC0 || ((fabsf(playerPosRelToDoor.y) < 20.0f) && (fabsf(playerPosRelToDoor.x) < 20.0f) &&
                           (fabsf(playerPosRelToDoor.z) < 50.0f))) {
            s16 yawDiff = player->actor.shape.rot.y - this->knobDoor.dyna.actor.shape.rot.y;

            if (playerPosRelToDoor.z > 0.0f) {
                yawDiff = (0x8000 - yawDiff);
            }
            if (ABS_ALT(yawDiff) < 0x3000) {
                player->doorType = PLAYER_DOORTYPE_HANDLE;
                player->doorDirection = playerPosRelToDoor.z >= 0.0f ? 1.0f : -1.0f;
                player->doorActor = &this->knobDoor.dyna.actor;
                if (this->unk_1A6 != 0) {
                    if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) <= 0) {
                        player->doorType = PLAYER_DOORTYPE_TALKING;
                        this->knobDoor.dyna.actor.textId = 0x1802;
                    } else {
                        player->doorTimer = 10;
                    }
                } else if (this->doorType == ENDOOR_TYPE_4) {
                    player->doorType = PLAYER_DOORTYPE_TALKING;
                    this->knobDoor.dyna.actor.textId = 0x1800;
                } else if ((this->doorType == ENDOOR_TYPE_0) || (this->doorType == ENDOOR_TYPE_2) ||
                           (this->doorType == ENDOOR_TYPE_3)) {
                    s32 halfDaysDayBit = (play->actorCtx.halfDaysBit & HALFDAYBIT_DAWNS) >> 1;
                    s32 halfDaysNightBit = play->actorCtx.halfDaysBit & HALFDAYBIT_NIGHTS;
                    s16 temp_a2 = D_801AED48[this->switchFlag & 7];
                    s32 textIdOffset = (this->switchFlag >> 3) & 0xF;

                    if (((this->doorType == ENDOOR_TYPE_0) && !((halfDaysDayBit | halfDaysNightBit) & temp_a2)) ||
                        ((this->doorType == ENDOOR_TYPE_2) && !(halfDaysNightBit & temp_a2)) ||
                        ((this->doorType == ENDOOR_TYPE_3) && !(halfDaysDayBit & temp_a2))) {
                        s16 baseTextId = 0x182D;

                        if (this->doorType == ENDOOR_TYPE_3) {
                            baseTextId = 0x180D;
                        } else if (this->doorType == ENDOOR_TYPE_2) {
                            baseTextId = 0x181D;
                        }
                        player->doorType = PLAYER_DOORTYPE_TALKING;
                        this->knobDoor.dyna.actor.textId = baseTextId + textIdOffset;
                    }
                } else if ((this->doorType == ENDOOR_TYPE_5) && (playerPosRelToDoor.z > 0.0f)) {
                    ScheduleOutput scheduleOutput;

                    if (Schedule_RunScript(play, D_8086778C[this->switchFlag], &scheduleOutput)) {
                        this->knobDoor.dyna.actor.textId = scheduleOutput.result + 0x1800;

                        player->doorType = ((this->knobDoor.dyna.actor.textId == 0x1821) && D_80867BC0)
                                               ? PLAYER_DOORTYPE_PROXIMITY
                                               : PLAYER_DOORTYPE_TALKING;
                    }
                }
                func_80122F28(player);
            }
        } else if ((this->doorType == ENDOOR_TYPE_4) && (this->knobDoor.dyna.actor.xzDistToPlayer > 240.0f)) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_OPEN);
            this->actionFunc = func_80867080;
        }
    }
}

void func_80866F94(EnDoor* this, PlayState* play) {
    s32 direction;

    if (this->unk_1A7 != 0) {
        if (this->unk_1A7 >= 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, direction * 0x3E80, 0x7D0)) {
            Math_StepToC(&this->unk_1A7, 0, 1);
        }
    } else {
        if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, 0, 0x7D0)) {
            this->actionFunc = func_80866B20;
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_AUTO_DOOR_CLOSE);
        }
    }
}

void func_8086704C(EnDoor* this, PlayState* play) {
    if (this->knobDoor.dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    }
}

void func_80867080(EnDoor* this, PlayState* play) {
    if (this->knobDoor.dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    } else if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, -0x1800, 0x100)) {
        this->actionFunc = func_8086704C;
    }
}

void func_808670F0(EnDoor* this, PlayState* play) {
    if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, 0, 0x700)) {
        Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_CLOSE);
        this->actionFunc = func_80866B20;
    }
}

void func_80867144(EnDoor* this, PlayState* play) {
    s32 numEffects;
    s32 i;

    if (DECR(this->unk_1A6) == 0) {
        if (SkelAnime_Update(&this->knobDoor.skelAnime)) {
            this->actionFunc = func_80866B20;
            this->knobDoor.playOpenAnim = false;
        } else if (Animation_OnFrame(&this->knobDoor.skelAnime, sAnimOpenFrames[this->knobDoor.animIndex])) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_OC_DOOR_OPEN);
            if (this->knobDoor.skelAnime.playSpeed < 1.5f) {
                numEffects = (s32)(Rand_ZeroOne() * 30.0f) + 50;
                for (i = 0; i < numEffects; i++) {
                    EffectSsBubble_Spawn(play, &this->knobDoor.dyna.actor.world.pos, 60.0, 100.0f, 50.0f, 0.15f);
                }
            }
        } else if (Animation_OnFrame(&this->knobDoor.skelAnime, sAnimCloseFrames[this->knobDoor.animIndex])) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_CLOSE);
        }
    }
}

void EnDoor_Update(Actor* thisx, PlayState* play) {
    EnDoor* this = THIS;

    this->actionFunc(this, play);
}

s32 EnDoor_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    TransitionActorEntry* transitionEntry;
    EnDoor* this = THIS;

    if (limbIndex == DOOR_LIMB_4) {
        Gfx** dl = D_808679A4[this->knobDoor.dlIndex];
        s16 temp;
        s32 dlIndex;

        transitionEntry = NULL;

        if (this->doorType != ENDOOR_TYPE_7) {
            transitionEntry = &play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&this->knobDoor.dyna.actor)];
        }
        rot->z += this->knobDoor.dyna.actor.world.rot.y;
        if ((this->doorType == ENDOOR_TYPE_7) || (play->roomCtx.prevRoom.num >= 0) ||
            (transitionEntry->sides[0].room == transitionEntry->sides[1].room)) {
            s32 pad;

            temp =
                (this->knobDoor.dyna.actor.shape.rot.y + this->knobDoor.skelAnime.jointTable[DOOR_LIMB_3].z + rot->z) -
                Math_Vec3f_Yaw(&play->view.eye, &this->knobDoor.dyna.actor.world.pos);
            *dList = (ABS_ALT(temp) < 0x4000) ? dl[0] : dl[1];

        } else {
            dlIndex = 0;
            if (transitionEntry->sides[0].room != this->knobDoor.dyna.actor.room) {
                dlIndex = 1;
            }
            *dList = dl[dlIndex];
        }
    }
    return false;
}

void EnDoor_Draw(Actor* thisx, PlayState* play) {
    EnDoor* this = THIS;

    if (this->knobDoor.dyna.actor.objBankIndex == this->knobDoor.requiredObjBankIndex) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((this->doorType == ENDOOR_TYPE_7) && (this->switchFlag == 0)) {
            Gfx_DrawDListOpa(play, gameplay_keep_DL_0221B8);
        } else {
            Gfx_SetupDL25_Opa(play->state.gfxCtx);
        }
        SkelAnime_DrawOpa(play, this->knobDoor.skelAnime.skeleton, this->knobDoor.skelAnime.jointTable,
                          EnDoor_OverrideLimbDraw, NULL, &this->knobDoor.dyna.actor);
        if (this->knobDoor.dyna.actor.world.rot.y != 0) {
            if (this->knobDoor.dyna.actor.world.rot.y > 0) {
                gSPDisplayList(POLY_OPA_DISP++, gDoorRightDL);
            } else {
                gSPDisplayList(POLY_OPA_DISP++, gDoorLeftDL);
            }
        }
        if (this->unk_1A6) {
            Actor_DrawDoorLock(play, this->unk_1A6, 0);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
