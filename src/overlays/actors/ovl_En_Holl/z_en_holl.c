#include "z_en_holl.h"

#define FLAGS 0x00000010

#define THIS ((EnHoll*)thisx)

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_SetTypeAndOpacity(EnHoll* this);
void EnHoll_SetPlayerSide(GlobalContext* globalCtx, EnHoll* this, Vec3f* vec3fP);
void func_80899B88(EnHoll* this, GlobalContext* globalCtx);
void func_8089A238(EnHoll* this, GlobalContext* globalCtx);
void func_80899F30(EnHoll* this, GlobalContext* globalCtx);
void func_8089A0C0(EnHoll* this, GlobalContext* globalCtx);
void func_8089A330(EnHoll* this, GlobalContext* globalCtx);

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

static s32 D_8089A550[] = {
    0x465055F0, 0x00000000, 0x08000800, 0xFFFFFFFF,
    0xB9B055F0, 0x00000000, 0x00000800, 0xFFFFFFFF,
    0xB9B0AA10, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0x4650AA10, 0x00000000, 0x08000000, 0xFFFFFFFF
};

static s32 D_8089A590[] = {
    0xD7000000, 0xFFFFFFFF, 0xFCFFFFFF, 0xFFFDF638,
    0x01004008, &D_8089A550, 0x06000204, 0x00000406,
    0xDF000000, 0x00000000
};

static UNK_PTR D_8089A5B8 = 0;

static EnHollActionFunc D_8089A5BC[] /* sEnHollActionFuncs */ = {
    func_80899B88, func_8089A238, func_80899F30, func_8089A0C0,
    func_80899B88
};

static InitChainEntry D_8089A5D0[] /* sInitChain[] */ = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

static f32 D_8089A5DC = 200.0f;
static f32 D_8089A5E0 = 150.0f;
static f32 D_8089A5E4 = 100.0f;
static f32 D_8089A5E8 = 50.0f;

void EnHoll_SetTypeAndOpacity(EnHoll* this) {
    this->type = EN_HOLL_GET_TYPE(this);
    this->actionFunc = D_8089A5BC[this->type];
    if (EN_HOLL_IS_VISIBLE(this)) {
        this->opacity = EN_HOLL_OPAQUE;
    } else {
        this->actor.draw = NULL;
    }
}

void EnHoll_SetPlayerSide(GlobalContext* globalCtx, EnHoll* this, Vec3f* rotatedPlayerPos) {
    Player* player = PLAYER;

    /* rotatedPlayerPos = function output
     * = hypothetical rotation of Player around Holl's origin to intersect its y-z plane */
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

    Actor_ProcessInitChain(&this->actor, D_8089A5D0);
    EnHoll_SetTypeAndOpacity(this) /* Sets visible Holls to OPAQUE, invisible Holls to not draw */;
    this->alwaysZero = 0;
    this->opacity = EN_HOLL_OPAQUE /* Sets *all* Holls to OPAQUE */;
    EnHoll_SetPlayerSide(globalCtx, this, &rotatedPlayerPos);
}

void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;

    if (!EN_HOLL_IS_SCENE_CHANGER(this)) {
        u32 transitionActorIndex = ((u16)this->actor.params) >> 0xA;
        globalCtx->doorCtx.transitionActorList[transitionActorIndex].id =
            -globalCtx->doorCtx.transitionActorList[transitionActorIndex].id;
        if (this == D_8089A5B8) {
            D_8089A5B8 = NULL;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A0C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A330.s")

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

    if (this->opacity != EN_HOLL_TRANSPARENT) {
	OPEN_DISPS(globalCtx->state.gfxCtx);
        if (this->opacity == EN_HOLL_OPAQUE) {
            gfxP = POLY_OPA_DISP;
            dlIndex = 37;
        } else { // EN_HOLL_TRANSLUCENT
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
	} else { // EN_HOLL_TRANSLUCENT
            POLY_XLU_DISP = gfxP;
	}
	CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
