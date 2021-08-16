/*
 * File: z_en_holl.c
 * Overlay: ovl_En_Holl
 * Description: Room/Scene Loading Hallways
 */

#include "z_en_holl.h"

#define FLAGS 0x00000010

#define THIS ((EnHoll*)thisx)

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnHoll_SetupAction(EnHoll* this);
void EnHoll_SetPlayerSide(GlobalContext* globalCtx, EnHoll* this, Vec3f* transformedPlayerPos);
void EnHoll_ChangeRooms(GlobalContext* globalCtx);
void EnHoll_VisibleIdle(EnHoll* this, GlobalContext* globalCtx);
void EnHoll_VerticalIdle(EnHoll* this, GlobalContext* globalCtx);
void EnHoll_TransparentIdle(EnHoll* this, GlobalContext* globalCtx);
void EnHoll_VerticalBgCoverIdle(EnHoll* this, GlobalContext* globalCtx);
void EnHoll_RoomTransitionIdle(EnHoll* this, GlobalContext* globalCtx);

const ActorInit En_Holl_InitVars = {
    ACTOR_EN_HOLL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHoll),
    (ActorFunc)EnHoll_Init,
    (ActorFunc)EnHoll_Destroy,
    (ActorFunc)EnHoll_Update,
    (ActorFunc)EnHoll_Draw,
};

static UNK_TYPE D_8089A550[] = { 0x465055F0, 0x00000000, 0x08000800, 0xFFFFFFFF, 0xB9B055F0, 0x00000000,
                                 0x00000800, 0xFFFFFFFF, 0xB9B0AA10, 0x00000000, 0x00000000, 0xFFFFFFFF,
                                 0x4650AA10, 0x00000000, 0x08000000, 0xFFFFFFFF };

static UNK_TYPE D_8089A590[] = { 0xD7000000,  0xFFFFFFFF, 0xFCFFFFFF, 0xFFFDF638, 0x01004008,
                                 &D_8089A550, 0x06000204, 0x00000406, 0xDF000000, 0x00000000 };

static EnHoll* sInstancePlayingSound = NULL;

static EnHollActionFunc sActionFuncs[] = {
    EnHoll_VisibleIdle, EnHoll_VerticalIdle, EnHoll_TransparentIdle, EnHoll_VerticalBgCoverIdle, EnHoll_VisibleIdle,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

static f32 sActivationPlaneDistance = 200.0f;
static f32 sLoadingPlaneDistance = 150.0f;
static f32 sTranslucencyPlaneDistance = 100.0f;
static f32 sTransparencyPlaneDistance = 50.0f;

void EnHoll_SetupAction(EnHoll* this) {
    this->type = EN_HOLL_GET_TYPE(this);
    this->actionFunc = sActionFuncs[this->type];
    if (EN_HOLL_IS_VISIBLE(this)) {
        this->alpha = 255;
    } else {
        this->actor.draw = NULL;
    }
}

void EnHoll_SetPlayerSide(GlobalContext* globalCtx, EnHoll* this, Vec3f* transformedPlayerPos) {
    Player* player = PLAYER;

    Actor_CalcOffsetOrientedToDrawRotation(&this->actor, transformedPlayerPos, &player->actor.world.pos);
    this->playerSide = (transformedPlayerPos->z < 0.0f) ? EN_HOLL_BEHIND : EN_HOLL_BEFORE;
}

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    s32 pad;
    Vec3f transformedPlayerPos;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnHoll_SetupAction(this);
    this->bgCoverAlphaActive = false;
    this->alpha = 255;
    EnHoll_SetPlayerSide(globalCtx, this, &transformedPlayerPos);
}

void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;

    if (!EN_HOLL_IS_SCENE_CHANGER(this)) {
        u32 enHollId = EN_HOLL_GET_ID_CAST(this);

        globalCtx->doorCtx.transitionActorList[enHollId].id = -globalCtx->doorCtx.transitionActorList[enHollId].id;
        if (this == sInstancePlayingSound) {
            sInstancePlayingSound = NULL;
        }
    }
}

void EnHoll_ChangeRooms(GlobalContext* globalCtx) {
    Room oldCurrRoom = globalCtx->roomCtx.currRoom;
    globalCtx->roomCtx.currRoom = globalCtx->roomCtx.prevRoom;
    globalCtx->roomCtx.prevRoom = oldCurrRoom;
    globalCtx->roomCtx.activeMemPage ^= 1;
}

void EnHoll_VisibleIdle(EnHoll* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f transformedPlayerPos;
    f32 playerDistFromCentralPlane;

    if (this->type == EN_HOLL_TYPE_DEFAULT) {
        u32 actorCtxBitmask = (globalCtx->actorCtx.unkC & 0x2AA) >> 1 | (globalCtx->actorCtx.unkC & 0x155);
        u32 zActorBitmask = D_801AED48[EN_HOLL_GET_Z_ACTOR_BITMASK_INDEX(this)];

        if ((actorCtxBitmask & zActorBitmask) == 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        if (this == sInstancePlayingSound) {
            func_800B9010(&this->actor, NA_SE_EV_INVISIBLE_MONKEY - SFX_FLAG);
        }
    }
    if ((globalCtx->sceneLoadFlag != 0) || (globalCtx->unk_18B4A != 0)) {
        this->alpha = 255;
    } else {
        f32 enHollBottom = EN_HOLL_BOTTOM_DEFAULT;
        f32 enHollHalfwidth = EN_HOLL_HALFWIDTH_DEFAULT;

        EnHoll_SetPlayerSide(globalCtx, this, &transformedPlayerPos);
        playerDistFromCentralPlane = fabsf(transformedPlayerPos.z);
        if (globalCtx->sceneNum == SCENE_IKANA) {
            enHollBottom = EN_HOLL_BOTTOM_IKANA;
            enHollHalfwidth = EN_HOLL_HALFWIDTH_IKANA;
        }
        if ((enHollBottom < transformedPlayerPos.y) && (transformedPlayerPos.y < EN_HOLL_TOP_DEFAULT) &&
            (fabsf(transformedPlayerPos.x) < enHollHalfwidth) &&
            (playerDistFromCentralPlane < sActivationPlaneDistance)) {
            u32 enHollId = EN_HOLL_GET_ID_AND(this);

            if (sLoadingPlaneDistance < playerDistFromCentralPlane) {
                if ((globalCtx->roomCtx.prevRoom.num >= 0) && (globalCtx->roomCtx.unk31 == 0)) {
                    this->actor.room = globalCtx->doorCtx.transitionActorList[enHollId].sides[this->playerSide].room;
                    if (globalCtx->roomCtx.prevRoom.num == this->actor.room) {
                        EnHoll_ChangeRooms(globalCtx);
                    }
                    func_8012EBF8(globalCtx, &globalCtx->roomCtx);
                }
            } else if (this->type == EN_HOLL_TYPE_SCENE_CHANGER) {
                globalCtx->nextEntranceIndex = globalCtx->setupExitList[EN_HOLL_GET_EXIT_LIST_INDEX(this)];
                gSaveContext.unk_3DBB = 1;
                Scene_SetExitFade(globalCtx);
                globalCtx->sceneLoadFlag = 0x14;
                globalCtx->unk_1878C(globalCtx);
            } else {
                this->actor.room = globalCtx->doorCtx.transitionActorList[enHollId].sides[this->playerSide ^ 1].room;
                if (globalCtx->roomCtx.prevRoom.num < 0) {
                    Room_StartRoomTransition(globalCtx, &globalCtx->roomCtx, this->actor.room);
                    if (this == sInstancePlayingSound) {
                        sInstancePlayingSound = NULL;
                    }
                } else {
                    s32 unclampedAlpha = EN_HOLL_SCALE_ALPHA(playerDistFromCentralPlane);

                    this->alpha = CLAMP(unclampedAlpha, 0, 255);
                    if (globalCtx->roomCtx.currRoom.num != this->actor.room) {
                        EnHoll_ChangeRooms(globalCtx);
                    }
                }
            }
        } else if ((this->type == EN_HOLL_TYPE_DEFAULT) && (globalCtx->sceneNum == SCENE_26SARUNOMORI) &&
                   (sInstancePlayingSound == NULL)) {
            sInstancePlayingSound = this;
        }
    }
}

void EnHoll_TransparentIdle(EnHoll* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 useViewEye = D_801D0D50 || globalCtx->csCtx.state != 0;
    Vec3f transformedPlayerPos;
    f32 enHollTop;
    f32 playerDistFromCentralPlane;

    Actor_CalcOffsetOrientedToDrawRotation(&this->actor, &transformedPlayerPos,
                                           useViewEye ? &globalCtx->view.eye : &player->actor.world.pos);
    enHollTop = (globalCtx->sceneNum == SCENE_PIRATE) ? EN_HOLL_TOP_PIRATE : EN_HOLL_TOP_DEFAULT;
    if ((transformedPlayerPos.y > EN_HOLL_BOTTOM_DEFAULT) && (transformedPlayerPos.y < enHollTop) &&
        (fabsf(transformedPlayerPos.x) < EN_HOLL_HALFWIDTH_TRANSPARENT)) {
        if (playerDistFromCentralPlane = fabsf(transformedPlayerPos.z),
            playerDistFromCentralPlane < EN_HOLL_ACTIVATION_PLANE_DISTANCE &&
                playerDistFromCentralPlane > EN_HOLL_LOADING_PLANE_DISTANCE) {
            s32 enHollId = EN_HOLL_GET_ID_CAST(this);
            s32 playerSide = (transformedPlayerPos.z < 0.0f) ? EN_HOLL_BEHIND : EN_HOLL_BEFORE;
            TransitionActorEntry* transitionActorEntry = &globalCtx->doorCtx.transitionActorList[enHollId];
            s8 room = transitionActorEntry->sides[playerSide].room;

            this->actor.room = room;
            if ((this->actor.room != globalCtx->roomCtx.currRoom.num) &&
                (Room_StartRoomTransition(globalCtx, &globalCtx->roomCtx, this->actor.room))) {
                this->actionFunc = EnHoll_RoomTransitionIdle;
            }
        }
    }
}

void EnHoll_VerticalBgCoverIdle(EnHoll* this, GlobalContext* globalCtx) {
    f32 playerDistFromCentralPlane;

    if ((this->actor.xzDistToPlayer < EN_HOLL_RADIUS) &&
        (playerDistFromCentralPlane = fabsf(this->actor.yDistToPlayer),
         playerDistFromCentralPlane < EN_HOLL_ACTIVATION_PLANE_DISTANCE_VERTICAL)) {
        if (playerDistFromCentralPlane < EN_HOLL_LOADING_PLANE_DISTANCE_VERTICAL) {
            globalCtx->bgCoverAlpha = 255;
        } else {
            globalCtx->bgCoverAlpha = EN_HOLL_SCALE_BG_COVER_ALPHA(playerDistFromCentralPlane);
        }
        if (playerDistFromCentralPlane > EN_HOLL_LOADING_PLANE_DISTANCE_VERTICAL) {
            s32 enHollId = EN_HOLL_GET_ID_CAST(this);
            s32 playerSide = (this->actor.yDistToPlayer > 0.0f) ? EN_HOLL_ABOVE : EN_HOLL_BELOW;

            this->actor.room = globalCtx->doorCtx.transitionActorList[enHollId].sides[playerSide].room;
            if ((this->actor.room != globalCtx->roomCtx.currRoom.num) &&
                Room_StartRoomTransition(globalCtx, &globalCtx->roomCtx, this->actor.room)) {
                this->actionFunc = EnHoll_RoomTransitionIdle;
                this->bgCoverAlphaActive = true;
            }
        }
    } else if (this->bgCoverAlphaActive) {
        this->bgCoverAlphaActive = false;
        globalCtx->bgCoverAlpha = 0;
    }
}

void EnHoll_VerticalIdle(EnHoll* this, GlobalContext* globalCtx) {

    if (this->actor.xzDistToPlayer < EN_HOLL_RADIUS) {
        f32 playerDistFromCentralPlane = fabsf(this->actor.yDistToPlayer);

        if (playerDistFromCentralPlane < EN_HOLL_ACTIVATION_PLANE_DISTANCE_VERTICAL &&
            playerDistFromCentralPlane > EN_HOLL_LOADING_PLANE_DISTANCE_VERTICAL) {
            s32 enHollId = EN_HOLL_GET_ID_CAST(this);
            s32 playerSide = (this->actor.yDistToPlayer > 0.0f) ? EN_HOLL_ABOVE : EN_HOLL_BELOW;

            this->actor.room = globalCtx->doorCtx.transitionActorList[enHollId].sides[playerSide].room;
            if ((this->actor.room != globalCtx->roomCtx.currRoom.num) &&
                Room_StartRoomTransition(globalCtx, &globalCtx->roomCtx, this->actor.room)) {
                this->actionFunc = EnHoll_RoomTransitionIdle;
            }
        }
    }
}

void EnHoll_RoomTransitionIdle(EnHoll* this, GlobalContext* globalCtx) {
    if (globalCtx->roomCtx.unk31 == 0) {
        func_8012EBF8(globalCtx, &globalCtx->roomCtx);
        if (globalCtx->bgCoverAlpha == 0) {
            this->bgCoverAlphaActive = false;
        }
        EnHoll_SetupAction(this);
    }
}

void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    Player* player = PLAYER;

    if ((globalCtx->sceneLoadFlag == 0) && (globalCtx->unk_18B4A == 0) && !(player->stateFlags1 & 0x200)) {
        this->actionFunc(this, globalCtx);
    }
}

void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    Gfx* dl;
    u32 dlIndex;

    if (this->alpha != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        if (this->alpha == 255) {
            dl = POLY_OPA_DISP;
            dlIndex = 37;
        } else {
            dl = POLY_XLU_DISP;
            dlIndex = 0;
        }
        dl = Gfx_CallSetupDL(dl, dlIndex);
        if (this->playerSide == EN_HOLL_BEHIND) {
            SysMatrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
        }
        gSPMatrix(dl++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, this->alpha);
        gSPDisplayList(dl++, D_8089A590);
        if (this->alpha == 255) {
            POLY_OPA_DISP = dl;
        } else {
            POLY_XLU_DISP = dl;
        }
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
