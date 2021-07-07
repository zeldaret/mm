#include "z_door_ana.h"

#define FLAGS 0x02000000

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

// entrances grottos can link to statically, type DOORANA_TYPE_ADJACENT uses scene exit addresses instead
static u16 entrances[] = {
    0x1A00, 0x1400, 0x1410, 0x1420, 0x1430, 0x1440, 0x1450, 0x1460,
    0x1470, 0x1480, 0x1490, 0x14A0, 0x14B0, 0x14C0, 0x14D0,
};

void DoorAna_SetupAction(DoorAna* this, DoorAnaActionFunc actionFunction) {
    this->actionFunc = actionFunction;
}

void DoorAna_Init(Actor* thisx, GlobalContext* globalCtx) {
    DoorAna* this = THIS;
    s32 grottoType = GET_DOORANA_TYPE(this);
    this->actor.shape.rot.y = this->actor.shape.rot.z = 0;

    if ((grottoType == DOORANA_TYPE_UNK) || (grottoType == DOORANA_TYPE_HIDDEN)) {
        if (grottoType == DOORANA_TYPE_HIDDEN) {
            Collider_InitAndSetCylinder(globalCtx, &this->bombCollider, &this->actor, &sCylinderInit);
        } else {
            this->actor.flags |= 0x10; // always update
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
    s32 grottoType = GET_DOORANA_TYPE(this);

    if (grottoType == DOORANA_TYPE_HIDDEN) {
        Collider_DestroyCylinder(globalCtx, &this->bombCollider);
    }
}

void DoorAna_WaitClosed(DoorAna* this, GlobalContext* globalCtx) {
    s32 grottoIsOpen = 0;
    u32 grottoType = GET_DOORANA_TYPE(this);

    if (grottoType == DOORANA_TYPE_UNK) {
        // in OOT decomp its marked as open with storms, but does not seem to open with storms in MM
        if ((this->actor.xyzDistToPlayerSq < 40000.0f) && (func_800F13E8(globalCtx, 5))) {
            grottoIsOpen = 1;
            this->actor.flags &= ~0x10; // always update OFF
        }

    } else {
        if (this->bombCollider.base.acFlags & AC_HIT) { // bomb collision
            grottoIsOpen = 1;
            Collider_DestroyCylinder(globalCtx, &this->bombCollider);

        } else {
            Collider_UpdateCylinder(&this->actor, &this->bombCollider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->bombCollider.base);
        }
    }

    if (grottoIsOpen) {
        this->actor.params &= ~DOORANA_TYPE_BITRANGE;
        DoorAna_SetupAction(this, DoorAna_WaitOpen);
        play_sound(NA_SE_SY_CORRECT_CHIME);
    }

    func_800B8C50(&this->actor, globalCtx);
}

void DoorAna_WaitOpen(DoorAna* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 dooranaType = GET_DOORANA_TYPE(this);
    s8 pad[4];
    s32 entranceIndex;
    f32 yDist;

    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.001f) != 0) {
        if ((this->actor.targetMode != 0) && (globalCtx->sceneLoadFlag == 0) && (globalCtx->unk_18B4A == 0) &&
            (player->stateFlags1 & 0x80000000) && (player->unk_AE7 == 0)) {

            if (dooranaType == DOORANA_TYPE_ADJACENT) {
                // 300 uses scene exit addresses, not static DoorAna entrance addresses,
                // eg. deku playground gets address in the NCT scene exit table

                entranceIndex = GET_DOORANA_ADJACENT_ENTRANCE(this);
                globalCtx->nextEntranceIndex = globalCtx->setupExitList[entranceIndex];
            lblUnk_808E03B8:; // required to convince compiler to not use delay slot

            } else {
                // unused in vanilla, the highest params bits can directly index an address
                entranceIndex = GET_DOORANA_DIRECT_ENTRANCE(this);

                func_80169E6C(globalCtx, 3, 0x4FF);

                gSaveContext.respawn[3].pos.y = this->actor.world.pos.y;
                gSaveContext.respawn[3].yaw = this->actor.home.rot.y;

                // save the params lower byte for En_Torch to decide what item to use in the grotto chest
                gSaveContext.respawn[3].data = GET_DOORANA_ITEMFLAGS(this);

                // most grottos in the game use their zrotation as their entrance index, not params
                if (DOORANA_TYPE_ROTATION_ENTRANCE(entranceIndex)) {
                    entranceIndex = GET_DOORANA_ROTATION_ENTRANCE(this);
                }

                globalCtx->nextEntranceIndex = entrances[entranceIndex];
            }

            DoorAna_SetupAction(this, DoorAna_GrabLink);

        } else {
            if ((func_801690CC(globalCtx) == 0) && ((player->stateFlags1 & 0x08800000) == 0) &&
                (this->actor.xzDistToPlayer <= 20.0f) && (yDist = this->actor.yDistToPlayer, (yDist >= -50.0f)) &&
                (yDist <= 15.0f)) {
                player->stateFlags1 |= 0x80000000;
                this->actor.targetMode = 1;

            } else {
                this->actor.targetMode = 0;
            }
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

    if ((this->actor.yDistToPlayer <= 0.0f) && (this->actor.xzDistToPlayer > 20.0f)) {
        player = PLAYER;
        player->actor.world.pos.x = (Math_SinS(this->actor.yawTowardsPlayer) * 20.0f) + this->actor.world.pos.x;
        player->actor.world.pos.z = (Math_CosS(this->actor.yawTowardsPlayer) * 20.0f) + this->actor.world.pos.z;
    }
}

void DoorAna_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorAna* this = THIS;

    this->actionFunc(this, globalCtx);
    this->actor.shape.rot.y = func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000;
}

void DoorAna_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BE03C(globalCtx, D_05000C40);
}
