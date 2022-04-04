/*
 * File: z_arrow_light.c
 * Overlay: ovl_Arrow_Light
 * Description: Light Arrow
 */

#include "z_arrow_light.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((ArrowLight*)thisx)

void ArrowLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Draw(Actor* thisx, GlobalContext* globalCtx);

void ArrowLight_Charge(ArrowLight* this, GlobalContext* globalCtx);
void ArrowLight_Fly(ArrowLight* this, GlobalContext* globalCtx);

#include "overlays/ovl_Arrow_Light/ovl_Arrow_Light.c"

const ActorInit Arrow_Light_InitVars = {
    ACTOR_ARROW_LIGHT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowLight),
    (ActorFunc)ArrowLight_Init,
    (ActorFunc)ArrowLight_Destroy,
    (ActorFunc)ArrowLight_Update,
    (ActorFunc)ArrowLight_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

static s32 sUnused;

void ArrowLight_SetupAction(ArrowLight* this, ArrowLightActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArrowLight_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArrowLight* this = (ArrowLight*)thisx;
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->radius = 0;
    this->height = 1.0f;
    ArrowLight_SetupAction(this, ArrowLight_Charge);
    Actor_SetScale(&this->actor, 0.01f);
    this->alpha = 130;
    this->timer = 0;
    this->screenFillIntensity = 0.0f;
}

void ArrowLight_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_80115D5C(&globalCtx->state);
    (void)"消滅"; // Unreferenced in retail, means "Disappearance"
}

void ArrowLight_Charge(ArrowLight* this, GlobalContext* globalCtx) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;

    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->radius < 10) {
        this->radius++;
    }

    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    func_800B9010(&this->actor, NA_SE_PL_ARROW_CHARGE_LIGHT - SFX_FLAG);
    if (arrow->actor.parent == NULL) {
        this->firedPos = this->actor.world.pos;
        this->radius = 10;
        ArrowLight_SetupAction(this, ArrowLight_Fly);
        this->alpha = 255;
    }
}

void ArrowLight_Lerp(Vec3f* firedPos, Vec3f* pos, f32 scale) {
    VEC3F_LERPIMPDST(firedPos, firedPos, pos, scale);
}

void ArrowLight_Hit(ArrowLight* this, GlobalContext* globalCtx) {
    f32 scale;
    u16 timer;

    if (this->actor.projectedW < 50.0f) {
        scale = 10.0f;
    } else if (this->actor.projectedW > 950.0f) {
        scale = 310.0f;
    } else {
        scale = this->actor.projectedW;
        scale = ((scale - 50.0f) * (1.0f / 3.0f)) + 10.0f;
    }

    timer = this->timer;
    if (timer != 0) {
        this->timer--;
        if (this->timer >= 8) {
            f32 offset = (this->timer - 8) * (1.0f / 24.0f);

            offset = SQ(offset);
            this->radius = (((1.0f - offset) * scale) + 10.0f);
            this->height = F32_LERPIMP(this->height, 2.0f, 0.1f);
            if (this->timer < 16) {
                this->alpha = (this->timer * 35) - 280;
            }
        }
    }
    if (this->timer >= 9) {
        if (this->screenFillIntensity < 1.0f) {
            this->screenFillIntensity += 0.25f;
        }
    } else {
        if (this->screenFillIntensity > 0.0f) {
            this->screenFillIntensity -= 0.125f;
        }
    }
    if (this->timer < 8) {
        this->alpha = 0;
    }
    if (this->timer == 0) {
        this->timer = 255;
        Actor_MarkForDeath(&this->actor);
        return;
    }
}

void ArrowLight_Fly(ArrowLight* this, GlobalContext* globalCtx) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;
    s32 pad[2];

    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    this->height = Math_Vec3f_DistXYZ(&this->firedPos, &this->actor.world.pos) * (1.0f / 24.0f);
    if (this->height < 1.0f) {
        this->height = 1.0f;
    }

    ArrowLight_Lerp(&this->firedPos, &this->actor.world.pos, 0.05f);

    if (arrow->unk_261 & 1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_EXPLOSION_LIGHT);
        ArrowLight_SetupAction(this, ArrowLight_Hit);
        this->timer = 32;
        this->alpha = 255;
        return;
    }
    if (arrow->unk_260 < 34) {
        if (this->alpha < 35) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->alpha -= 25;
    }
}

void ArrowLight_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArrowLight* this = THIS;

    if ((globalCtx->msgCtx.msgMode == 0xE) || (globalCtx->msgCtx.msgMode == 0x12)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc(this, globalCtx);
}

void ArrowLight_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ArrowLight* this = (ArrowLight*)thisx;
    u32 frames = globalCtx->state.frames;
    EnArrow* arrow = (EnArrow*)this->actor.parent;

    if ((arrow != NULL) && (arrow->actor.update != NULL) && (this->timer < 255)) {
        Actor* transform = (arrow->unk_261 & 2) ? &this->actor : &arrow->actor;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_InsertTranslation(transform->world.pos.x, transform->world.pos.y, transform->world.pos.z, MTXMODE_NEW);
        Matrix_RotateY(transform->shape.rot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(transform->shape.rot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(transform->shape.rot.z, MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
        if (this->screenFillIntensity > 0.0f) {
            POLY_XLU_DISP = func_8012BFC4(POLY_XLU_DISP);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (s32)(this->screenFillIntensity * 30.0f) & 0xFF,
                            (s32)(40.0f * this->screenFillIntensity) & 0xFF, 0,
                            (s32)(150.0f * this->screenFillIntensity) & 0xFF);
            gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_DISABLE);
            gDPSetColorDither(POLY_XLU_DISP++, G_CD_DISABLE);
            gSPDisplayList(POLY_XLU_DISP++, D_0E000000.fillRect);
        }

        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 128);

        Matrix_InsertRotation(0x4000, 0, 0, MTXMODE_APPLY);
        if (this->timer != 0) {
            Matrix_InsertTranslation(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        } else {
            Matrix_InsertTranslation(0.0f, 1500.0f, 0.0f, MTXMODE_APPLY);
        }
        Matrix_Scale(this->radius * 0.2f, this->height * 4.0f, this->radius * 0.2f, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, -700.0f, 0.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightArrowMaterialDL);
        gSPDisplayList(POLY_XLU_DISP++,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 511 - ((frames * 5) % 512), 0, 4, 32, 1,
                                        511 - ((frames * 10) % 512), 511 - ((frames * 30) % 512), 8, 16));
        gSPDisplayList(POLY_XLU_DISP++, gLightArrowModelDL);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
