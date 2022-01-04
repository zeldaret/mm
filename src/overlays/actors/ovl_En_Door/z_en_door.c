/*
 * File: z_en_door.c
 * Overlay: ovl_En_Door
 * Description: Wooden Door
 */

#include "z_en_door.h"
#include "objects/object_mkk/object_mkk.h"
#include "objects/object_dor01/object_dor01.h"
#include "objects/object_dor02/object_dor02.h"
#include "objects/object_dor03/object_dor03.h"
#include "objects/object_dor04/object_dor04.h"
#include "objects/object_wdor01/object_wdor01.h"
#include "objects/object_wdor02/object_wdor02.h"
#include "objects/object_wdor03/object_wdor03.h"
#include "objects/object_wdor04/object_wdor04.h"
#include "objects/object_wdor05/object_wdor05.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"

#define FLAGS 0x00000010

#define THIS ((EnDoor*)thisx)

void EnDoor_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80866B20(EnDoor*, GlobalContext*);
void func_8086704C(EnDoor*, GlobalContext*);
void func_80866F94(EnDoor*, GlobalContext*);
void func_80867080(EnDoor*, GlobalContext*);
void func_80867144(EnDoor*, GlobalContext*);
void func_808670F0(EnDoor*, GlobalContext*);
void func_80866A5C(EnDoor*, GlobalContext*);

// I have no idea what this is
s32 D_808675D0[] = {
    0x0C00030E, 0x02060017, 0x00080200, 0x00060002, 0x09070500,
};

s32 D_808675E4[] = {
    0x0F090047, 0x0F0C0015, 0x0C000113, 0x11000F0D, 0x000A0F0F, 0x00070F00, 0x00020909,
    0x0509080C, 0x00021900, 0x1C08070F, 0x0D000209, 0x09050F0D, 0x00EA0F11, 0x00E70F00,
    0x00E20909, 0x0F0D00DC, 0x0F0D00D9, 0x0F120001, 0x05090909, 0x09000000,
};

s32 D_80867634[] = { 0x02060017, 0x0002091C, 0x05000000 };

s32 D_80867640[] = { 0x02150016, 0x00010509, 0x0B000000 };
s32 D_8086764C[] = { 0x02160005, 0x0002090A, 0x05000000 };
s32 D_80867658[] = { 0x0C00020F, 0x001C0802, 0x090C020F, 0x0A160002, 0x090C050C, 0x0003110F,
                            0x0D000D00, 0x33080209, 0x0C0F1600, 0x02090C05, 0x090C0000 };
s32 D_80867684 = 0x05000000;

s32 D_80867688[] = { 0x0F160002, 0x090F0500 };

s32 D_80867690[] = { 0x0F160002, 0x09100500 };

s32 D_80867698[] = { 0x0F160002, 0x09110500 };

s32 D_808676A0[] = {
    0x020A0015, 0x000F0216, 0x00050002, 0x09120802, 0x02092209, 0x21050000,
};

s32 D_808676B8[] = {
    0x0800140C, 0x0003070F, 0x08000105, 0x09130208, 0x00141E02, 0x09130505,
};

s32 D_808676D0 = 0x05000000;

s32 D_808676D4 = 0x05000000;

s32 D_808676D8[] = {
    0x0C000305,
    0x0F120001,
    0x05091400,
};

s32 D_808676E4[] = {
    0x08000209,
    0x16050000,
};

s32 D_808676EC = 0x05000000;

s32 D_808676F0[] = {
    0x0C000305, 0x0F0A0007, 0x05020A00, 0x1400F909, 0x15000000,
};

s32 D_80867704 = 0x05000000;
s32 D_80867708 = 0x05000000;
s32 D_8086770C = 0x05000000;
s32 D_80867710 = 0x05000000;

s32 D_80867714[] = {
    0x0F140002,
    0x09170500,
};

s32 D_8086771C[] = {
    0x0C000107, 0x0F021E02, 0x0918050C, 0x0003FB0F, 0x1400F709, 0x0C000000,
};

s32 D_80867734[] = {
    0x0F140002,
    0x09190500,
};

s32 D_8086773C[] = {
    0x0F140002,
    0x091A0500,
};

s32 D_80867744[] = {
    0x0C000204, 0x00638006, 0x0F140008, 0x091B0F12, 0x0002091B, 0x05000000,
};

s32 D_8086775C[] = {
    0x00342017, 0x004B2013, 0x000E0402, 0x091D003B, 0x0108003D, 0x0202091E, 0x091F0505,
};

s32 D_80867778 = 0x09200000;
s32 D_8086777C = 0x05000000;
s32 D_80867780 = 0x05000000;
s32 D_80867784[] = { 0x0F160002, 0x09230500 };

s32 D_8086778C[] = {
    &D_808675D0, &D_808675E4, &D_80867634, &D_80867640, &D_8086764C, &D_80867658, &D_80867684, &D_80867688,
    &D_80867690, &D_80867698, &D_808676A0, &D_808676B8, &D_808676D0, &D_808676D4, &D_808676D8, &D_808676E4,
    &D_808676EC, &D_808676F0, &D_80867704, &D_80867708, &D_8086770C, &D_80867710, &D_80867714, &D_8086771C,
    &D_80867734, &D_8086773C, &D_80867744, &D_8086775C, &D_80867778, &D_8086777C, &D_80867780, &D_80867784,
};

const ActorInit En_Door_InitVars = {
    ACTOR_EN_DOOR,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoor),
    (ActorFunc)EnDoor_Init,
    (ActorFunc)EnDoor_Destroy,
    (ActorFunc)EnDoor_Update,
    (ActorFunc)EnDoor_Draw,
};

typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 dListIndex;
    /* 0x04 */ s16 objectId;
} EnDoorInfo;

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
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.x, 0, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.z, 0, ICHAIN_STOP),
};

static AnimationHeader* sAnimations[] = {
    &gameplay_keep_Anim_020658, &gameplay_keep_Anim_022CA8, &gameplay_keep_Anim_020658, &gameplay_keep_Anim_022E68,
    &gameplay_keep_Anim_0204B4, &gameplay_keep_Anim_022BE8, &gameplay_keep_Anim_022D90, &gameplay_keep_Anim_022BE8,
    &gameplay_keep_Anim_022FF0, &gameplay_keep_Anim_0205A0,
};
static u8 sAnimOpenFrames[10] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
};

static u8 sAnimCloseFrames[10] = {
    60, 60, 60, 70, 70, 60, 60, 60, 60, 70,
};

static Gfx* D_808679A4[14][2] = {
    { gDoorLeftDL, gDoorRightDL },
    { gWoodfallDoorDL, gWoodfallDoorDL },
    { object_dor01_DL_000448, object_dor01_DL_000448 },
    { gZoraHallDoorDL, gZoraHallDoorDL },
    { gSwampDoorDL, gSwampDoorDL },
    { gMagicHagPotionShopDoorDL, gMagicHagPotionShopDoorDL },
    { object_wdor01_DL_000548, object_wdor01_DL_000548 }, // Lottery Shop / Curiosity Shop / Mayor's House Door
    { object_wdor02_DL_000548, object_wdor02_DL_000548 }, // Trading Post / Post Office Door
    { object_wdor03_DL_000548, object_wdor03_DL_000548 }, // Stockpot Inn & Swordsman's School Door
    { gMilkBarDoorDL, gMilkBarDoorDL },
    { gMusicBoxHouseDoorDL, gMusicBoxHouseDoorDL },
    { gPiratesFortressDoorDL, gPiratesFortressDoorDL },
    { object_mkk_DL_000310, object_mkk_DL_000310 },
    { gFieldWoodDoorLeftDL, gFieldWoodDoorRightDL },
};

void EnDoor_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 objectBankIndex;
    EnDoorInfo* objectInfo = sObjInfo;
    EnDoor* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->unk_1A4 = ENDOOR_GET_PARAMS_7(thisx);

    this->switchFlag = ENDOOR_GET_PARAMS_7F(thisx);
    if ((this->unk_1A4 == 7) && (this->switchFlag == 0)) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gDoorCol);
    }
    SkelAnime_Init(globalCtx, &this->skelAnime, &gDoorSkel, &gameplay_keep_Anim_020658, this->limbTable,
                   this->limbTable, 5);
    if (this->unk_1A4 == 5) {
        objectInfo = &sObjInfo[17 + this->switchFlag];
    } else {
        for (i = 0; i < ARRAY_COUNT(sObjInfo) - 34; i++, objectInfo++) {
            if (globalCtx->sceneNum == objectInfo->sceneNum) {
                break;
            }
        }
        if ((i >= ARRAY_COUNT(sObjInfo) - 34) && (Object_GetIndex(&globalCtx->objectCtx, GAMEPLAY_FIELD_KEEP) >= 0)) {
            objectInfo++;
        }
    }

    this->dlIndex = objectInfo->dListIndex;
    objectBankIndex = Object_GetIndex(&globalCtx->objectCtx, objectInfo->objectId);
    if (objectBankIndex < 0) {
        objectInfo = &sObjInfo[15];
        objectBankIndex = Object_GetIndex(&globalCtx->objectCtx, objectInfo->objectId);
        if (objectBankIndex != 0) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
    }
    this->requiredObjBankIndex = objectBankIndex;
    this->dlIndex = objectInfo->dListIndex; // Set twice?
    if (this->dyna.actor.objBankIndex == this->requiredObjBankIndex) {
        func_80866A5C(this, globalCtx);
    } else {
        this->actionFunc = func_80866A5C;
    }
    Actor_SetHeight(&this->dyna.actor, 35.0f);
}

void EnDoor_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDoor* this = (EnDoor*)thisx;

    if (this->unk_1A4 != 7) {
        TransitionActorEntry* transitionEntry =
            &globalCtx->doorCtx.transitionActorList[(u16)this->dyna.actor.params >> 0xA];
        if (transitionEntry->id < 0) {
            transitionEntry->id = -transitionEntry->id;
        }
    } else if (this->switchFlag == 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80866A5C(EnDoor* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->requiredObjBankIndex)) {
        this->dyna.actor.objBankIndex = this->requiredObjBankIndex;
        this->actionFunc = func_80866B20;
        this->dyna.actor.world.rot.y = 0;
        if (this->unk_1A4 == 1) {
            if (!Flags_GetSwitch(globalCtx, this->switchFlag)) {
                this->unk_1A6 = 10;
            }
        } else if ((this->unk_1A4 == 4) &&
                   (Actor_XZDistanceBetweenActors(&this->dyna.actor, &GET_PLAYER(globalCtx)->actor) > 120.0f)) {
            this->actionFunc = func_8086704C;
            this->dyna.actor.world.rot.y = -0x1800;
        }
    }
}

#ifdef NON_EQUIVALENT
void func_80866B20(EnDoor* this, GlobalContext* globalCtx) {
    static s32 D_80867BC0[4];

    Player* player;
    Vec3f playerPosRelToDoor;
    struct_80133038_arg2 sp30;
    s16 temp_a2;
    s16 yawDiff;
    s32 temp_a1_2;
    s32 temp_t0;
    u8 temp_a1;
    // s16 baseTextId;

    player = GET_PLAYER(globalCtx);
    if ((func_800B84D0(&this->dyna.actor, globalCtx) != 0) && (this->dyna.actor.textId == 0x1821)) {
        D_80867BC0[0] = 1;
    }
    if (this->unk_1A1 != 0) {
        this->actionFunc = func_80867144;
        Animation_PlayOnceSetSpeed(&this->skelAnime, sAnimations[this->animIndex],
                                   (player->stateFlags1 & 0x8000000) ? 0.75f : 1.5f);
        if (this->unk_1A6 != 0) {
            gSaveContext.inventory.dungeonKeys[gSaveContext.mapIndex]--;
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
        }
    } else if (this->unk_1A7 != 0) {
        this->actionFunc = func_80866F94;
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_OPEN);
    } else if (func_801233E4(globalCtx) == 0) { // Player_InCsMode
        Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &playerPosRelToDoor, &player->actor.world.pos);
        if ((D_80867BC0[0] != 0) || ((fabsf(playerPosRelToDoor.y) < 20.0f) && (fabsf(playerPosRelToDoor.x) < 20.0f) &&
                                     (fabsf(playerPosRelToDoor.z) < 50.0f))) {
            yawDiff = player->actor.shape.rot.y - this->dyna.actor.shape.rot.y;
            if (playerPosRelToDoor.z > 0.0f) {
                yawDiff = (0x8000 - yawDiff);
            }
            if (ABS(yawDiff) < 0x3000) {
                player->doorType = 1;
                player->doorDirection = playerPosRelToDoor.z >= 0.0f ? 1.0f : -1.0f;
                player->doorActor = &this->dyna.actor;
                if (this->unk_1A6 != 0) {
                    if (gSaveContext.inventory.dungeonKeys[gSaveContext.mapIndex] <= 0) {
                        player->doorType = -1;
                        this->dyna.actor.textId = 0x1802;
                    } else {
                        player->doorTimer = 10;
                    }
                } else {
                    if (this->unk_1A4 == 4) {
                        player->doorType = -1;
                        this->dyna.actor.textId = 0x1800;
                    } else if ((this->unk_1A4 == 0) || (this->unk_1A4 == 2) || (this->unk_1A4 == 3)) {
                        temp_t0 = (globalCtx->actorCtx.unkC & 0x2AA) >> 1;
                        temp_a2 = D_801AED48[this->switchFlag & 7];
                        temp_a1_2 = globalCtx->actorCtx.unkC & 0x155;
                        if (((this->unk_1A4 == 0) && (((temp_t0 | temp_a1_2) & temp_a2) == 0)) ||
                            ((this->unk_1A4 == 2) && ((temp_a2 & temp_a1_2) == 0)) ||
                            ((this->unk_1A4 == 3) && ((temp_a2 & temp_t0) == 0))) {
                            s16 baseTextId = 0x182D;
                            if (this->unk_1A4 == 3) {
                                baseTextId = 0x180D;
                            } else if (this->unk_1A4 == 2) {
                                baseTextId = 0x181D;
                            }
                            player->doorType = -1;
                            this->dyna.actor.textId = baseTextId + ((this->switchFlag >> 3) & 0xF);
                        }
                    } else if ((this->unk_1A4 == 5) && (playerPosRelToDoor.z > 0.0f)) {
                        if (func_80133038(globalCtx, D_8086778C[this->switchFlag], &sp30) != 0) {
                            this->dyna.actor.textId = sp30.unk0 + 0x1800;

                            player->doorType = ((this->dyna.actor.textId == 0x1821) && (D_80867BC0[0] != 0)) ? 5 : -1;
                        }
                    }
                }
                func_80122F28(player);
            }
        } else if ((this->unk_1A4 == 4) && (this->dyna.actor.xzDistToPlayer > 240.0f)) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_OPEN);
            this->actionFunc = func_80867080;
        }
    }
}
#endif
static s32 D_80867BC0[4];
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866B20.s")

void func_80866F94(EnDoor* this, GlobalContext* globalCtx) {
    s32 direction;

    if (this->unk_1A7 != 0) {
        if (this->unk_1A7 >= 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (Math_ScaledStepToS(&this->dyna.actor.world.rot.y, direction * 0x3E80, 0x7D0)) {
            Math_StepToC(&this->unk_1A7, 0, 1);
        }
    } else {
        if (Math_ScaledStepToS(&this->dyna.actor.world.rot.y, 0, 0x7D0)) {
            this->actionFunc = func_80866B20;
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_AUTO_DOOR_CLOSE);
        }
    }
}

void func_8086704C(EnDoor* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    }
}

void func_80867080(EnDoor* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    } else if (Math_ScaledStepToS(&this->dyna.actor.world.rot.y, -0x1800, 0x100)) {
        this->actionFunc = func_8086704C;
    }
}

void func_808670F0(EnDoor* this, GlobalContext* globalCtx) {
    if (Math_ScaledStepToS(&this->dyna.actor.world.rot.y, 0, 0x700)) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_CLOSE);
        this->actionFunc = func_80866B20;
    }
}

void func_80867144(EnDoor* this, GlobalContext* globalCtx) {
    s32 numEffects;
    s32 i;

    if (DECR(this->unk_1A6) == 0) {
        if (SkelAnime_Update(&this->skelAnime) != 0) {
            this->actionFunc = func_80866B20;
            this->unk_1A1 = 0;
        } else if (Animation_OnFrame(&this->skelAnime, sAnimOpenFrames[this->animIndex])) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_OC_DOOR_OPEN);
            if (this->skelAnime.playSpeed < 1.5f) {
                numEffects = (s32)(Rand_ZeroOne() * 30.0f) + 50;
                for (i = 0; i < numEffects; i++) {
                    EffectSsBubble_Spawn(globalCtx, &this->dyna.actor.world.pos, 60.0, 100.0f, 50.0f, 0.15f);
                }
            }
        } else if (Animation_OnFrame(&this->skelAnime, sAnimCloseFrames[this->animIndex])) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_CLOSE);
        }
    }
}

void EnDoor_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDoor* this = THIS;

    this->actionFunc(this, globalCtx);
}

s32 EnDoor_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    TransitionActorEntry* transitionEntry;
    EnDoor* this = THIS;

    if (limbIndex == 4) {
        Gfx** dl = D_808679A4[this->dlIndex];
        s16 temp;
        s32 dlIndex;
        
        transitionEntry = NULL;

        if (this->unk_1A4 != 7) {
            transitionEntry = &globalCtx->doorCtx.transitionActorList[(u16)this->dyna.actor.params >> 0xA];
        }
        rot->z += this->dyna.actor.world.rot.y;
        if ((this->unk_1A4 == 7) || (globalCtx->roomCtx.prevRoom.num >= 0) ||
            (transitionEntry->sides[0].room == transitionEntry->sides[1].room)) {
            s32 pad;
            
            temp = (this->dyna.actor.shape.rot.y + this->skelAnime.jointTable[3].z + rot->z) -
                   Math_Vec3f_Yaw(&globalCtx->view.eye, &this->dyna.actor.world.pos);
            *dList = (ABS_ALT(temp) < 0x4000) ? dl[0] : dl[1];

        } else {
            dlIndex = 0;
            if (transitionEntry->sides[0].room != this->dyna.actor.room) {
                dlIndex = 1;
            }
            *dList = dl[dlIndex];
        }
    }
    return 0;
}

void EnDoor_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDoor* this = THIS;

    if (this->dyna.actor.objBankIndex == this->requiredObjBankIndex) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        if ((this->unk_1A4 == 7) && (this->switchFlag == 0)) {
            func_800BDFC0(globalCtx, gameplay_keep_DL_0221B8);
        } else {
            func_8012C28C(globalCtx->state.gfxCtx);
        }
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnDoor_OverrideLimbDraw,
                          NULL, &this->dyna.actor);
        if (this->dyna.actor.world.rot.y != 0) {
            if (this->dyna.actor.world.rot.y > 0) {
                gSPDisplayList(POLY_OPA_DISP++, gDoorRightDL);
            } else {
                gSPDisplayList(POLY_OPA_DISP++, gDoorLeftDL);
            }
        }
        if (this->unk_1A6) {
            func_800BC8B8(globalCtx, this->unk_1A6, 0);
        }
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
