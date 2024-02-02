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

void func_80866B20(EnDoor* this, PlayState* play);
void func_8086704C(EnDoor* this, PlayState* play);
void func_80866F94(EnDoor* this, PlayState* play);
void func_80867080(EnDoor* this, PlayState* play);
void func_80867144(EnDoor* this, PlayState* play);
void func_808670F0(EnDoor* this, PlayState* play);
void func_80866A5C(EnDoor* this, PlayState* play);

typedef enum DoorScheduleResult {
    /*  0 */ DOOR_SCH_NONE,
    /*  1 */ DOOR_SCH_1,
    /*  2 */ DOOR_SCH_2,
    /*  3 */ DOOR_SCH_3,
    /*  4 */ DOOR_SCH_4,
    /*  5 */ DOOR_SCH_5,
    /*  6 */ DOOR_SCH_6,
    /*  7 */ DOOR_SCH_7,
    /*  8 */ DOOR_SCH_8,
    /*  9 */ DOOR_SCH_9,
    /* 10 */ DOOR_SCH_10,
    /* 11 */ DOOR_SCH_11,
    /* 12 */ DOOR_SCH_12,
    /* 13 */ DOOR_SCH_13,
    /* 14 */ DOOR_SCH_14,
    /* 15 */ DOOR_SCH_15,
    /* 16 */ DOOR_SCH_16,
    /* 17 */ DOOR_SCH_17,
    /* 18 */ DOOR_SCH_18,
    /* 19 */ DOOR_SCH_19,
    /* 20 */ DOOR_SCH_20,
    /* 21 */ DOOR_SCH_21,
    /* 22 */ DOOR_SCH_22,
    /* 23 */ DOOR_SCH_23,
    /* 24 */ DOOR_SCH_24,
    /* 25 */ DOOR_SCH_25,
    /* 26 */ DOOR_SCH_26,
    /* 27 */ DOOR_SCH_27,
    /* 28 */ DOOR_SCH_28,
    /* 29 */ DOOR_SCH_29,
    /* 30 */ DOOR_SCH_30,
    /* 31 */ DOOR_SCH_31,
    /* 32 */ DOOR_SCH_32,
    /* 33 */ DOOR_SCH_33,
    /* 34 */ DOOR_SCH_34,
    /* 35 */ DOOR_SCH_35,
    /* 36 */ DOOR_SCH_MAX
} DoorScheduleResult;

#include "build/src/overlays/actors/ovl_En_Door/scheduleScripts.schl.inc"

ScheduleScript* D_8086778C[] = {
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

typedef enum EnDoorDListIndex {
    /*  0 */ DOOR_DL_DEFAULT,
    /*  1 */ DOOR_DL_WOODFALL,
    /*  2 */ DOOR_DL_OBSERVATORY_LAB,
    /*  3 */ DOOR_DL_ZORA_HALL,
    /*  4 */ DOOR_DL_SWAMP,
    /*  5 */ DOOR_DL_MAGIC_HAG_POTION_SHOP,
    /*  6 */ DOOR_DL_LOTTERY_CURIOSITY_SHIP_MAYOR_HOUSE,
    /*  7 */ DOOR_DL_POST_OFFICE_TRAIDING_POST,
    /*  8 */ DOOR_DL_INN_SCHOOL,
    /*  9 */ DOOR_DL_MILK_BAR,
    /* 10 */ DOOR_DL_MUSIC_BOX,
    /* 11 */ DOOR_DL_PIRATES_FORTESS,
    /* 12 */ DOOR_DL_OCEANSIDE_SPIDER_HOUSE,
    /* 13 */ DOOR_DL_DEFAULT_FIELD_KEEP,
    /* 14 */ DOOR_DL_MAX
} EnDoorDListIndex;

typedef struct EnDoorInfo {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ u8 dListIndex;
    /* 0x4 */ s16 objectId;
} EnDoorInfo; // size = 0x6

typedef enum EnDoorObjectInfoIndex {
    /*  0 */ DOOR_OBJKIND_DEFAULT,
    /*  0 */ DOOR_OBJINFO_0 = DOOR_OBJKIND_DEFAULT,
    /*  1 */ DOOR_OBJINFO_1,
    /*  2 */ DOOR_OBJINFO_2,
    /*  3 */ DOOR_OBJINFO_3,
    /*  4 */ DOOR_OBJINFO_4,
    /*  5 */ DOOR_OBJINFO_5,
    /*  6 */ DOOR_OBJINFO_6,
    /*  7 */ DOOR_OBJINFO_7,
    /*  8 */ DOOR_OBJINFO_8,
    /*  9 */ DOOR_OBJINFO_9,
    /* 10 */ DOOR_OBJINFO_10,
    /* 11 */ DOOR_OBJINFO_11,
    /* 12 */ DOOR_OBJINFO_12,
    /* 13 */ DOOR_OBJINFO_13,
    /* 14 */ DOOR_OBJINFO_14,

    /* 15 */ DOOR_OBJKIND_KEEP,
    /* 15 */ DOOR_OBJINFO_15 = DOOR_OBJKIND_KEEP,
    /* 16 */ DOOR_OBJINFO_16,

    /* 17 */ DOOR_OBJKIND_SCHEDULE,
    /* 17 */ DOOR_OBJINFO_17 = DOOR_OBJKIND_SCHEDULE,
    /* 18 */ DOOR_OBJINFO_18,
    /* 19 */ DOOR_OBJINFO_19,
    /* 20 */ DOOR_OBJINFO_20,
    /* 21 */ DOOR_OBJINFO_21,
    /* 22 */ DOOR_OBJINFO_22,
    /* 23 */ DOOR_OBJINFO_23,
    /* 24 */ DOOR_OBJINFO_24,
    /* 25 */ DOOR_OBJINFO_25,
    /* 26 */ DOOR_OBJINFO_26,
    /* 27 */ DOOR_OBJINFO_27,
    /* 28 */ DOOR_OBJINFO_28,
    /* 29 */ DOOR_OBJINFO_29,
    /* 30 */ DOOR_OBJINFO_30,
    /* 31 */ DOOR_OBJINFO_31,
    /* 32 */ DOOR_OBJINFO_32,
    /* 33 */ DOOR_OBJINFO_33,
    /* 34 */ DOOR_OBJINFO_34,
    /* 35 */ DOOR_OBJINFO_35,
    /* 36 */ DOOR_OBJINFO_36,
    /* 37 */ DOOR_OBJINFO_37,
    /* 38 */ DOOR_OBJINFO_38,
    /* 39 */ DOOR_OBJINFO_39,
    /* 40 */ DOOR_OBJINFO_40,
    /* 41 */ DOOR_OBJINFO_41,
    /* 42 */ DOOR_OBJINFO_42,
    /* 43 */ DOOR_OBJINFO_43,
    /* 44 */ DOOR_OBJINFO_44,
    /* 45 */ DOOR_OBJINFO_45,
    /* 46 */ DOOR_OBJINFO_46,
    /* 47 */ DOOR_OBJINFO_47,
    /* 48 */ DOOR_OBJINFO_48,
    /* 49 */ DOOR_OBJINFO_MAX
} EnDoorObjectInfoIndex;

static EnDoorInfo sObjectInfo[DOOR_OBJINFO_MAX] = {
    { SCENE_MITURIN, DOOR_DL_WOODFALL, OBJECT_NUMA_OBJ },                  // DOOR_OBJINFO_0
    { SCENE_TENMON_DAI, DOOR_DL_OBSERVATORY_LAB, OBJECT_DOR01 },           // DOOR_OBJINFO_1
    { SCENE_00KEIKOKU, DOOR_DL_OBSERVATORY_LAB, OBJECT_DOR01 },            // DOOR_OBJINFO_2
    { SCENE_30GYOSON, DOOR_DL_OBSERVATORY_LAB, OBJECT_DOR01 },             // DOOR_OBJINFO_3
    { SCENE_LABO, DOOR_DL_OBSERVATORY_LAB, OBJECT_DOR01 },                 // DOOR_OBJINFO_4
    { SCENE_33ZORACITY, DOOR_DL_ZORA_HALL, OBJECT_DOR02 },                 // DOOR_OBJINFO_5
    { SCENE_UNSET_31, DOOR_DL_ZORA_HALL, OBJECT_DOR02 },                   // DOOR_OBJINFO_6
    { SCENE_BANDROOM, DOOR_DL_ZORA_HALL, OBJECT_DOR02 },                   // DOOR_OBJINFO_7
    { SCENE_20SICHITAI, DOOR_DL_SWAMP, OBJECT_DOR03 },                     // DOOR_OBJINFO_8
    { SCENE_20SICHITAI2, DOOR_DL_SWAMP, OBJECT_DOR03 },                    // DOOR_OBJINFO_9
    { SCENE_MAP_SHOP, DOOR_DL_SWAMP, OBJECT_DOR03 },                       // DOOR_OBJINFO_10
    { SCENE_KAIZOKU, DOOR_DL_PIRATES_FORTESS, OBJECT_KAIZOKU_OBJ },        // DOOR_OBJINFO_11
    { SCENE_PIRATE, DOOR_DL_PIRATES_FORTESS, OBJECT_KAIZOKU_OBJ },         // DOOR_OBJINFO_12
    { SCENE_TORIDE, DOOR_DL_PIRATES_FORTESS, OBJECT_KAIZOKU_OBJ },         // DOOR_OBJINFO_13
    { SCENE_KINDAN2, DOOR_DL_OCEANSIDE_SPIDER_HOUSE, OBJECT_KINSTA2_OBJ }, // DOOR_OBJINFO_14

    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_15
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_16

    { -1, DOOR_DL_INN_SCHOOL, OBJECT_WDOR03 },                             // DOOR_OBJINFO_17
    { -1, DOOR_DL_POST_OFFICE_TRAIDING_POST, OBJECT_WDOR02 },              // DOOR_OBJINFO_18
    { -1, DOOR_DL_LOTTERY_CURIOSITY_SHIP_MAYOR_HOUSE, OBJECT_WDOR01 },     // DOOR_OBJINFO_19
    { -1, DOOR_DL_POST_OFFICE_TRAIDING_POST, OBJECT_WDOR02 },              // DOOR_OBJINFO_20
    { -1, DOOR_DL_LOTTERY_CURIOSITY_SHIP_MAYOR_HOUSE, OBJECT_WDOR01 },     // DOOR_OBJINFO_21
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_22
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_23
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_24
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_25
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_26
    { -1, DOOR_DL_MILK_BAR, OBJECT_WDOR04 },                               // DOOR_OBJINFO_27
    { -1, DOOR_DL_INN_SCHOOL, OBJECT_WDOR03 },                             // DOOR_OBJINFO_28
    { -1, DOOR_DL_INN_SCHOOL, OBJECT_WDOR03 },                             // DOOR_OBJINFO_29
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_30
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_31
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_32
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_33
    { -1, DOOR_DL_LOTTERY_CURIOSITY_SHIP_MAYOR_HOUSE, OBJECT_WDOR01 },     // DOOR_OBJINFO_34
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_35
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_36
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_37
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_38
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_39
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_40
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_41
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_42
    { -1, DOOR_DL_DEFAULT, GAMEPLAY_KEEP },                                // DOOR_OBJINFO_43
    { -1, DOOR_DL_MUSIC_BOX, OBJECT_WDOR05 },                              // DOOR_OBJINFO_44
    { -1, DOOR_DL_DEFAULT_FIELD_KEEP, GAMEPLAY_FIELD_KEEP },               // DOOR_OBJINFO_45
    { -1, DOOR_DL_MAGIC_HAG_POTION_SHOP, OBJECT_DOR04 },                   // DOOR_OBJINFO_46
    { -1, DOOR_DL_MILK_BAR, OBJECT_WDOR04 },                               // DOOR_OBJINFO_47
    { -1, DOOR_DL_SWAMP, OBJECT_DOR03 },                                   // DOOR_OBJINFO_48
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

static Gfx* D_808679A4[DOOR_DL_MAX][2] = {
    { gDoorLeftDL, gDoorRightDL },                            // DOOR_DL_DEFAULT
    { gWoodfallDoorDL, gWoodfallDoorDL },                     // DOOR_DL_WOODFALL
    { gObservatoryLabDoorDL, gObservatoryLabDoorDL },         // DOOR_DL_OBSERVATORY_LAB
    { gZoraHallDoorDL, gZoraHallDoorDL },                     // DOOR_DL_ZORA_HALL
    { gSwampDoorDL, gSwampDoorDL },                           // DOOR_DL_SWAMP
    { gMagicHagPotionShopDoorDL, gMagicHagPotionShopDoorDL }, // DOOR_DL_MAGIC_HAG_POTION_SHOP
    { gLotteryCuriosityShopMayorHouseDoorDL,
      gLotteryCuriosityShopMayorHouseDoorDL },                      // DOOR_DL_LOTTERY_CURIOSITY_SHIP_MAYOR_HOUSE
    { gPostOfficeTradingPostDoorDL, gPostOfficeTradingPostDoorDL }, // DOOR_DL_POST_OFFICE_TRAIDING_POST
    { gInnSchoolDoorDL, gInnSchoolDoorDL },                         // DOOR_DL_INN_SCHOOL
    { gMilkBarDoorDL, gMilkBarDoorDL },                             // DOOR_DL_MILK_BAR
    { gMusicBoxHouseDoorDL, gMusicBoxHouseDoorDL },                 // DOOR_DL_MUSIC_BOX
    { gPiratesFortressDoorDL, gPiratesFortressDoorDL },             // DOOR_DL_PIRATES_FORTESS
    { gOceansideSpiderHouseDoorDL, gOceansideSpiderHouseDoorDL },   // DOOR_DL_OCEANSIDE_SPIDER_HOUSE
    { gFieldWoodDoorLeftDL, gFieldWoodDoorRightDL },                // DOOR_DL_DEFAULT_FIELD_KEEP
};

void EnDoor_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    s32 objectSlot;
    EnDoorInfo* objectInfo = &sObjectInfo[0];
    EnDoor* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->knobDoor.dyna.actor, sInitChain);

    this->doorType = ENDOOR_GET_TYPE(thisx);
    this->actionVar.actionVar = ENDOOR_GET_ACTION_VAR(thisx);

    if ((this->doorType == ENDOOR_TYPE_7) && (this->actionVar.actionVar_7 == 0)) {
        DynaPolyActor_Init(&this->knobDoor.dyna, 0);
        DynaPolyActor_LoadMesh(play, &this->knobDoor.dyna, &gDoorCol);
    }

    SkelAnime_Init(play, &this->knobDoor.skelAnime, &gDoorSkel, &gameplay_keep_Anim_020658, this->limbTable,
                   this->limbTable, DOOR_LIMB_MAX);

    if (this->doorType == ENDOOR_TYPE_5) {
        objectInfo = &sObjectInfo[DOOR_OBJKIND_SCHEDULE + this->actionVar.actionVar_5];
    } else {
        for (i = 0; i < DOOR_OBJKIND_KEEP; i++, objectInfo++) {
            if (play->sceneId == objectInfo->sceneId) {
                break;
            }
        }
        if ((i >= DOOR_OBJKIND_KEEP) &&
            (Object_GetSlot(&play->objectCtx, GAMEPLAY_FIELD_KEEP) > OBJECT_SLOT_NONE)) {
            objectInfo++;
        }
    }

    this->knobDoor.dlIndex = objectInfo->dListIndex;
    objectSlot = Object_GetSlot(&play->objectCtx, objectInfo->objectId);
    if (objectSlot <= OBJECT_SLOT_NONE) {
        objectInfo = &sObjectInfo[DOOR_OBJINFO_15];
        objectSlot = Object_GetSlot(&play->objectCtx, objectInfo->objectId);
        if (objectSlot != 0) {
            Actor_Kill(&this->knobDoor.dyna.actor);
            return;
        }
    }

    this->knobDoor.objectSlot = objectSlot;
    this->knobDoor.dlIndex = objectInfo->dListIndex; // Set twice?
    if (this->knobDoor.dyna.actor.objectSlot == this->knobDoor.objectSlot) {
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
    } else if (this->actionVar.actionVar_7 == 0) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->knobDoor.dyna.bgId);
    }
}

void func_80866A5C(EnDoor* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->knobDoor.objectSlot)) {
        this->knobDoor.dyna.actor.objectSlot = this->knobDoor.objectSlot;
        this->actionFunc = func_80866B20;
        this->knobDoor.dyna.actor.world.rot.y = 0;
        if (this->doorType == ENDOOR_TYPE_1) {
            if (!Flags_GetSwitch(play, this->actionVar.switchFlag)) {
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

    if (Actor_TalkOfferAccepted(&this->knobDoor.dyna.actor, &play->state) &&
        (this->knobDoor.dyna.actor.textId == 0x1821)) {
        D_80867BC0 = true;
    }

    if (this->knobDoor.playOpenAnim) {
        this->actionFunc = func_80867144;
        Animation_PlayOnceSetSpeed(&this->knobDoor.skelAnime, sAnimations[this->knobDoor.animIndex],
                                   (player->stateFlags1 & PLAYER_STATE1_8000000) ? 0.75f : 1.5f);

        if (this->unk_1A6 != 0) {
            DUNGEON_KEY_COUNT(gSaveContext.mapIndex) = DUNGEON_KEY_COUNT(gSaveContext.mapIndex) - 1;
            Flags_SetSwitch(play, this->actionVar.switchFlag);
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
        }
    } else if (this->openTimer != 0) {
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
                    s16 temp_a2 = D_801AED48[this->actionVar.actionVar_0_2_3 & 7];
                    s32 textIdOffset = (this->actionVar.actionVar_0_2_3 >> 3) & 0xF;

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

                    if (Schedule_RunScript(play, D_8086778C[this->actionVar.actionVar_5], &scheduleOutput)) {
                        this->knobDoor.dyna.actor.textId = scheduleOutput.result + 0x1800;

                        // TODO: is really worth to do (0x1800 + DOOR_SCH_33)?
                        player->doorType = ((this->knobDoor.dyna.actor.textId == (0x1800 + DOOR_SCH_33)) && D_80867BC0)
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

    if (this->openTimer != 0) {
        if (this->openTimer >= 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, direction * 0x3E80, 0x7D0)) {
            Math_StepToC(&this->openTimer, 0, 1);
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
        Gfx** sideDLists = D_808679A4[this->knobDoor.dlIndex];

        transitionEntry = NULL;

        if (this->doorType != ENDOOR_TYPE_7) {
            transitionEntry = &play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&this->knobDoor.dyna.actor)];
        }
        rot->z += this->knobDoor.dyna.actor.world.rot.y;
        if ((this->doorType == ENDOOR_TYPE_7) || (play->roomCtx.prevRoom.num >= 0) ||
            (transitionEntry->sides[0].room == transitionEntry->sides[1].room)) {
            s16 temp =
                (this->knobDoor.dyna.actor.shape.rot.y + this->knobDoor.skelAnime.jointTable[DOOR_LIMB_3].z + rot->z) -
                Math_Vec3f_Yaw(&play->view.eye, &this->knobDoor.dyna.actor.world.pos);

            *dList = (ABS_ALT(temp) < 0x4000) ? sideDLists[0] : sideDLists[1];

        } else {
            s32 index = 0;

            if (transitionEntry->sides[0].room != this->knobDoor.dyna.actor.room) {
                index = 1;
            }
            *dList = sideDLists[index];
        }
    }
    return false;
}

void EnDoor_Draw(Actor* thisx, PlayState* play) {
    EnDoor* this = THIS;

    if (this->knobDoor.dyna.actor.objectSlot == this->knobDoor.objectSlot) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((this->doorType == ENDOOR_TYPE_7) && (this->actionVar.actionVar_7 == 0)) {
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
