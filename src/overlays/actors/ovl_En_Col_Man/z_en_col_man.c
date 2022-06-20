/*
 * File: z_en_col_man.c
 * Overlay: ovl_En_Col_Man
 * Description: Lab HP, Garo Master falling rocks, Garo Master bomb
 */

#include "z_en_col_man.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_100000)

#define THIS ((EnColMan*)thisx)

void EnColMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80AFDD60(EnColMan* this);
void func_80AFDE00(EnColMan* this, GlobalContext* globalCtx);
void EnColMan_SetHeartPieceCollectedAndKill(EnColMan* this, GlobalContext* globalCtx);
void func_80AFDF60(EnColMan* this);
void func_80AFDFB4(EnColMan* this, GlobalContext* globalCtx);
void func_80AFE234(EnColMan* this);
void func_80AFE25C(EnColMan* this, GlobalContext* globalCtx);
void func_80AFE414(Actor* thisx, GlobalContext* globalCtx);
void func_80AFE4AC(Actor* thisx, GlobalContext* globalCtx);
void func_80AFE584(Actor* thisx, GlobalContext* globalCtx);
void func_80AFE650(Actor* thisx, GlobalContext* globalCtx);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 11, 1, { 0, 0, 0 } },
};

const ActorInit En_Col_Man_InitVars = {
    ACTOR_EN_COL_MAN,
    ACTORCAT_MISC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnColMan),
    (ActorFunc)EnColMan_Init,
    (ActorFunc)EnColMan_Destroy,
    (ActorFunc)EnColMan_Update,
    (ActorFunc)NULL,
};

static Color_RGBA8 primColor = { 60, 50, 20, 255 };
static Color_RGBA8 envColor = { 40, 30, 30, 255 };

void EnColMan_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnColMan* this = THIS;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.targetMode = 1;
    this->scale = (BREG(55) / 1000.0f) + 0.01f;

    switch (this->actor.params) {
        case EN_COL_MAN_HEART_PIECE:
        case EN_COL_MAN_RECOVERY_HEART:
        default:
            ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);
            func_80AFDD60(this);
            break;
        case EN_COL_MAN_FALLING_ROCK:
            ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);
            func_80AFDF60(this);
            break;
        case EN_COL_MAN_CUTSCENE_BOMB:
        case EN_COL_MAN_GAMEPLAY_BOMB:
            func_80AFE234(this);
            break;
    }
}

void EnColMan_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnColMan* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80AFDD60(EnColMan* this) {
    if (!(gSaveContext.save.weekEventReg[56] & 2)) {
        this->actor.draw = func_80AFE414;
        this->actor.shape.yOffset = 700.0f;
        if (this->actor.params == EN_COL_MAN_HEART_PIECE) {
            this->actor.gravity = -2.0f;
        }
        this->type = EN_COL_MAN_HEART_PIECE;
    } else {
        this->actor.draw = func_80AFE4AC;
        this->actor.shape.yOffset = 300.0f;
        this->actor.shape.shadowScale = 5.0f;
        if (this->actor.params == EN_COL_MAN_HEART_PIECE) {
            this->actor.gravity = -2.0f;
        }
        this->type = EN_COL_MAN_RECOVERY_HEART;
    }
    this->actionFunc = func_80AFDE00;
}

void func_80AFDE00(EnColMan* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.params == EN_COL_MAN_HEART_PIECE) {
            this->actor.params = EN_COL_MAN_RECOVERY_HEART;
            this->actor.speedXZ = 2.0f;
            this->actor.velocity.y = 8.0f;
        } else {
            this->actor.speedXZ = 0.0f;
        }
    }
    if (!(gSaveContext.save.weekEventReg[56] & 2)) {
        this->actor.shape.rot.y += 0x3E8;
    }
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actor.draw = NULL;
        this->actionFunc = EnColMan_SetHeartPieceCollectedAndKill;
    } else if (!(gSaveContext.save.weekEventReg[56] & 2)) {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 40.0f, 40.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_RECOVERY_HEART, 40.0f, 40.0f);
    }
}

void EnColMan_SetHeartPieceCollectedAndKill(EnColMan* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 6 && Message_ShouldAdvance(globalCtx)) {
        gSaveContext.save.weekEventReg[56] |= 2;
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80AFDF60(EnColMan* this) {
    this->actor.draw = func_80AFE584;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.flags |= ACTOR_FLAG_20;
    this->type = EN_COL_MAN_FALLING_ROCK;
    this->actionFunc = func_80AFDFB4;
    this->actor.shape.shadowScale = 5.0f;
    this->actor.gravity = -3.0f;
}

void func_80AFDFB4(EnColMan* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f velocity;
    Vec3f accel;

    this->scale = (BREG(55) / 10000.0f) + 0.0015f;

    if ((this->actor.bgCheckFlags & 1) && (this->actor.velocity.y < 0.0f)) {
        if (!this->hasSetRandomValues) {
            this->actor.world.rot.y = randPlusMinusPoint5Scaled(30000.0f);
            this->actor.speedXZ = 2.0f + BREG(56) + Rand_ZeroFloat(2.0f);
            this->actor.velocity.y = 12.0f + BREG(57) + Rand_ZeroFloat(5.0f);
            this->hasSetRandomValues = true;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ANSATSUSYA_ROCK);
            return;
        }

        for (i = 0; i < 2; i++) {
            velocity.x = randPlusMinusPoint5Scaled(2.0f);
            velocity.y = Rand_ZeroFloat(2.0f) + 1.0f;
            velocity.z = randPlusMinusPoint5Scaled(2.0f);
            accel.y = -0.1f;
            accel.z = 0.0f;
            accel.x = 0.0f;

            func_800B0EB0(globalCtx, &this->actor.world.pos, &velocity, &accel, &primColor, &envColor,
                          Rand_ZeroFloat(50.0f) + 60.0f, 30, Rand_ZeroFloat(5.0f) + 20.0f);
        }

        Actor_MarkForDeath(&this->actor);
    }
}

void func_80AFE234(EnColMan* this) {
    this->actor.draw = func_80AFE650;
    this->type = EN_COL_MAN_CUTSCENE_BOMB;
    this->actionFunc = func_80AFE25C;
}

void func_80AFE25C(EnColMan* this, GlobalContext* globalCtx) {
    this->scale = BREG(55) * 0.01f + 0.05f;

    if (BREG(60) || (this->actor.world.rot.z != 0)) {
        if (this->actor.params == EN_COL_MAN_CUTSCENE_BOMB) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.parent->world.pos.x,
                        this->actor.parent->world.pos.y, this->actor.parent->world.pos.z, 0, 0, 0,
                        CLEAR_TAG_SMALL_EXPLOSION);
        } else {
            EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);

            if (bomb != NULL) {
                bomb->timer = 0;
            }
        }

        Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnColMan_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnColMan* this = THIS;

    Actor_SetScale(&this->actor, this->scale);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 30.0f, 30.0f, 0x1F);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80AFE414(Actor* thisx, GlobalContext* globalCtx) {
    EnColMan* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    func_800B8118(&this->actor, globalCtx, 0);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_05AAB0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80AFE4AC(Actor* thisx, GlobalContext* globalCtx) {
    EnColMan* this = THIS;

    func_8012C2DC(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05E6F0));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_05F6F0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80AFE584(Actor* thisx, GlobalContext* globalCtx) {
    func_8012C2DC(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_06AB30);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80AFE650(Actor* thisx, GlobalContext* globalCtx) {
    func_8012C28C(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05CEF0));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_05F6F0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
