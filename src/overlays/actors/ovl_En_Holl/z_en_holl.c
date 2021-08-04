#include "z_en_holl.h"

#define FLAGS 0x00000010

#define THIS ((EnHoll*)thisx)

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80899960(EnHoll* this);
void func_808999B0(GlobalContext* globalCtx, EnHoll* this, Vec3f* vec3fP);
void func_80899B88(EnHoll* this, GlobalContext* globalCtx);
void func_8089A238(EnHoll* this, GlobalContext* globalCtx);
void func_80899F30(EnHoll* this, GlobalContext* globalCtx);
void func_8089A0C0(EnHoll* this, GlobalContext* globalCtx);

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

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

static s32 D_8089A590[] = {
    0xD7000000, 0xFFFFFFFF, 0xFCFFFFFF, 0xFFFDF638, 0x01004008, &sInitChain, 0x06000204, 0x00000406, 0xDF000000, 0x00000000};

static UNK_PTR D_8089A5B8 = 0;

static UNK_PTR enHollActionFuncs[] = {
    func_80899B88, func_8089A238, func_80899F30, func_8089A0C0, func_80899B88
};

//EnHoll_SetTypeAndOpacity(EnHoll* this) {
void func_80899960(EnHoll* this) {
    this->type = GET_HOLL_TYPE(this);
    this->actionFunc = enHollActionFuncs[this->type];
    if (IS_HOLL_TYPE_VISIBLE(this)) {
        this->opacity = EN_HOLL_OPAQUE;
    } else {
        this->actor.draw = NULL;
    }
}

// EnHoll_SetPlayerSide(GlobalContext* globalCtx, EnHoll* this, Vec3f* rotatedPlayerPos) {
void func_808999B0(GlobalContext* globalCtx, EnHoll* this, Vec3f* rotatedPlayerPos) {
    Player* player = PLAYER;

    /* rotatedPlayerPos = function output
     * = hypothetical rotation of Player around Holl's origin to intersect Holl's z axis */
    Actor_CalcOffsetOrientedToDrawRotation(&this->actor, rotatedPlayerPos, &player->actor.world.pos);
    if (rotatedPlayerPos->z < 0.0f) {
        this->playerSide = EN_HOLL_PLAYER_BEHIND;
    } else {
        this->playerSide = EN_HOLL_PLAYER_NOT_BEHIND;
    }
}

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    UNK_TYPE4 pad;
    Vec3f rotatedPlayerPos;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    func_80899960(this) /* Sets visible Holls to OPAQUE, invisible Holls to not draw */;
    this->alwaysZero = 0;
    this->opacity = EN_HOLL_OPAQUE /* Sets *all* Holls to OPAQUE */;
    func_808999B0(globalCtx, this, &rotatedPlayerPos);
}

void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;

    if (!IS_HOLL_TYPE_SCENE_CHANGER(this)) {
        u32 transitionActorIndex = ((u16)this->actor.params) >> 0xA;
        globalCtx->doorCtx.transitionActorList[transitionActorIndex].id =
            -globalCtx->doorCtx.transitionActorList[transitionActorIndex].id;
        if (this == D_8089A5B8) {
            D_8089A5B8 = NULL;
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899ACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A0C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A330.asm")

void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    Player* player = PLAYER;

    if ((globalCtx->sceneLoadFlag == 0) && (globalCtx->unk_18B4A == 0) && !(player->stateFlags1 & 0x200)) {
        this->actionFunc(this, globalCtx);
    }
}

void EnHoll_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnHoll* this = THIS;
    Gfx* gfxP;
    u32 dlIndex;

    if (this->opacity != EN_HOLL_INVISIBLE) {
	OPEN_DISPS(globalCtx->state.gfxCtx);
        if (this->opacity == EN_HOLL_OPAQUE) {
            gfxP = POLY_OPA_DISP;
            dlIndex = 37;
        } else {
            gfxP = POLY_XLU_DISP;
            dlIndex = 0;
        }
        gfxP = Gfx_CallSetupDL(gfxP, dlIndex);
        if (this->playerSide == EN_HOLL_PLAYER_BEHIND) {
            SysMatrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
        }
	gSPMatrix(gfxP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
	gDPSetPrimColor(gfxP++, 0, 0, 0, 0, 0, this->opacity);
	gSPDisplayList(gfxP++, D_8089A590);
        if (this->opacity == EN_HOLL_OPAQUE) {
            POLY_OPA_DISP = gfxP;
	} else {
            POLY_XLU_DISP = gfxP;
	}
	CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
