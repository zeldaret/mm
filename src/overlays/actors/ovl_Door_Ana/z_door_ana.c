/*
 * File: z_door_ana.c
 * Overlay: ovl_Door_Ana
 * Description: Grotto Hole Entrance
 */

#include "z_door_ana.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"

#define FLAGS (ACTOR_FLAG_2000000)

#define THIS ((DoorAna*)thisx)

void DoorAna_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Draw(Actor* thisx, GlobalContext* globalCtx);

void DoorAna_WaitClosed(DoorAna* this, GlobalContext* globalCtx);
void DoorAna_WaitOpen(DoorAna* this, GlobalContext* globalCtx);
void DoorAna_GrabLink(DoorAna* this, GlobalContext* globalCtx);

const ActorInit Door_Ana_InitVars = {
    ACTOR_DOOR_ANA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(DoorAna),
    (ActorFunc)DoorAna_Init,
    (ActorFunc)DoorAna_Destroy,
    (ActorFunc)DoorAna_Update,
    (ActorFunc)DoorAna_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000008, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 50, 10, 0, { 0, 0, 0 } },
};

static u16 sEntranceIndexes[] = {
    0x1A00, 0x1400, 0x1410, 0x1420, 0x1430, 0x1440, 0x1450, 0x1460,
    0x1470, 0x1480, 0x1490, 0x14A0, 0x14B0, 0x14C0, 0x14D0,
};

void DoorAna_SetupAction(DoorAna* this, DoorAnaActionFunc actionFunction) {
    this->actionFunc = actionFunction;
}

void DoorAna_Init(Actor* thisx, GlobalContext* globalCtx) {
    DoorAna* this = THIS;
    s32 grottoType = DOORANA_GET_TYPE(&this->actor);

    this->actor.shape.rot.y = this->actor.shape.rot.z = 0;

    if (grottoType == DOORANA_TYPE_HIDDEN_STORMS || grottoType == DOORANA_TYPE_HIDDEN_BOMB) {
        if (grottoType == DOORANA_TYPE_HIDDEN_BOMB) {
            Collider_InitAndSetCylinder(globalCtx, &this->bombCollider, &this->actor, &sCylinderInit);
        } else {
            this->actor.flags |= ACTOR_FLAG_10; // always update
        }

        Actor_SetScale(&this->actor, 0);
        DoorAna_SetupAction(this, DoorAna_WaitClosed);

    } else {
        DoorAna_SetupAction(this, DoorAna_WaitOpen);
    }

    this->actor.targetMode = 0;
}

void DoorAna_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DoorAna* this = THIS;
    s32 grottoType = DOORANA_GET_TYPE(&this->actor);

    if (grottoType == DOORANA_TYPE_HIDDEN_BOMB) {
        Collider_DestroyCylinder(globalCtx, &this->bombCollider);
    }
}

void DoorAna_WaitClosed(DoorAna* this, GlobalContext* globalCtx) {
    s32 grottoIsOpen = false;
    u32 grottoType = DOORANA_GET_TYPE(&this->actor);

    if (grottoType == DOORANA_TYPE_HIDDEN_STORMS) {
        //! @bug Implementation from OoT is not updated for MM, grotto does not open on Song of Storms
        if (this->actor.xyzDistToPlayerSq < SQ(200.0f) && EnvFlags_Get(globalCtx, 5)) {
            grottoIsOpen = true;
            this->actor.flags &= ~ACTOR_FLAG_10; // always update OFF
        }

    } else {
        if (this->bombCollider.base.acFlags & AC_HIT) { // bomb collision
            grottoIsOpen = true;
            Collider_DestroyCylinder(globalCtx, &this->bombCollider);

        } else {
            Collider_UpdateCylinder(&this->actor, &this->bombCollider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->bombCollider.base);
        }
    }

    if (grottoIsOpen) {
        DOORANA_SET_TYPE(&this->actor, DOORANA_TYPE_VISIBLE);
        DoorAna_SetupAction(this, DoorAna_WaitOpen);
        play_sound(NA_SE_SY_CORRECT_CHIME);
    }

    func_800B8C50(&this->actor, globalCtx);
}

void DoorAna_WaitOpen(DoorAna* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 grottoType = DOORANA_GET_TYPE(&this->actor);

    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.001f)) {
        if (this->actor.targetMode != 0 && globalCtx->sceneLoadFlag == 0 && globalCtx->unk_18B4A == 0 &&
            (player->stateFlags1 & 0x80000000) && player->unk_AE7 == 0) {

            if (grottoType == DOORANA_TYPE_VISIBLE_SCENE_EXIT) {
                s32 exitIndex = DOORANA_GET_EXIT_INDEX(&this->actor);

                globalCtx->nextEntranceIndex = globalCtx->setupExitList[exitIndex];
            } else {
                s32 destinationIdx = DOORANA_GET_ENTRANCE(&this->actor);

                Play_SetupRespawnPoint(&globalCtx->state, RESPAWN_MODE_UNK_3, 0x4FF);

                gSaveContext.respawn[RESPAWN_MODE_UNK_3].pos.y = this->actor.world.pos.y;
                gSaveContext.respawn[RESPAWN_MODE_UNK_3].yaw = this->actor.home.rot.y;

                // Stores item and chest flag that ACTOR_EN_TORCH uses for spawning the grotto chest
                gSaveContext.respawn[RESPAWN_MODE_UNK_3].data = DOORANA_GET_ITEMFLAGS(&this->actor);

                if (destinationIdx < 0) {
                    destinationIdx = DOORANA_GET_EX_ENTRANCE(&this->actor);
                }

                globalCtx->nextEntranceIndex = sEntranceIndexes[destinationIdx];
            }

            DoorAna_SetupAction(this, DoorAna_GrabLink);

        } else if (!Play_InCsMode(globalCtx) && !(player->stateFlags1 & 0x08800000) &&
                   (this->actor.xzDistToPlayer <= 20.0f) && (this->actor.playerHeightRel >= -50.0f) &&
                   (this->actor.playerHeightRel <= 15.0f)) {
            player->stateFlags1 |= 0x80000000;
            this->actor.targetMode = 1;

        } else {
            this->actor.targetMode = 0;
        }
    }

    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void DoorAna_GrabLink(DoorAna* this, GlobalContext* globalCtx) {
    Player* player;
    s8 pad[2];

    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }

    if (this->actor.playerHeightRel <= 0.0f && this->actor.xzDistToPlayer > 20.0f) {
        player = GET_PLAYER(globalCtx);
        player->actor.world.pos.x = Math_SinS(this->actor.yawTowardsPlayer) * 20.0f + this->actor.world.pos.x;
        player->actor.world.pos.z = Math_CosS(this->actor.yawTowardsPlayer) * 20.0f + this->actor.world.pos.z;
    }
}

void DoorAna_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorAna* this = THIS;

    this->actionFunc(this, globalCtx);
    this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)));
}

void DoorAna_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListXlu(globalCtx, gameplay_field_keep_DL_000C40);
}
