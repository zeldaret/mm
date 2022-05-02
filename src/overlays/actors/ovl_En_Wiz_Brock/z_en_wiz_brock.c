/*
 * File: z_en_wiz_brock.c
 * Overlay: ovl_En_Wiz_Brock
 * Description: Wizzrobe Warp Platform
 */

#include "z_en_wiz_brock.h"
#include "objects/object_wiz/object_wiz.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_8000000)

#define THIS ((EnWizBrock*)thisx)

void EnWizBrock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A490E4(EnWizBrock* this, GlobalContext* globalCtx);
void func_80A490FC(EnWizBrock* this, GlobalContext* globalCtx);

s16 D_80A495B0 = 0;

const ActorInit En_Wiz_Brock_InitVars = {
    ACTOR_EN_WIZ_BROCK,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizBrock),
    (ActorFunc)EnWizBrock_Init,
    (ActorFunc)EnWizBrock_Destroy,
    (ActorFunc)EnWizBrock_Update,
    (ActorFunc)EnWizBrock_Draw,
};

void EnWizBrock_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWizBrock* this = THIS;
    CollisionHeader* colHeader = NULL;
    s32 pad;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_wiz_Colheader_001690, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->dyna.actor.colChkInfo.health = 3;
    this->unk1A6 = 0;
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->unk1A8 = D_80A495B0++;
    this->actionFunc = func_80A490E4;
    this->dyna.actor.scale.x = this->dyna.actor.scale.y = this->dyna.actor.scale.z = 0.01f;
    this->alpha = 255.0f;
}

void EnWizBrock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWizBrock* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80A490E4(EnWizBrock* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A490FC;
}

void func_80A490FC(EnWizBrock* this, GlobalContext* globalCtx) {
    if (this->unk1AA == 0) {
        if (this->dyna.actor.colChkInfo.health != 3) {
            this->unk1AA = this->dyna.actor.colChkInfo.health;
        }
    }
    if (this->dyna.actor.colChkInfo.health == 0) {
        this->unk1A4++;
        if ((gGameInfo->data[0x991] + 0x1E) < this->unk1A4) {
            Math_ApproachZeroF(&this->dyna.actor.scale.y, (gGameInfo->data[0x992] / 10.0f) + 0.3f,
                               (gGameInfo->data[0x993] / 10000.0f) + 0.003f);
            Math_ApproachZeroF(&this->alpha, (gGameInfo->data[0x994] / 10.0f) + 1.0f,
                               (gGameInfo->data[0x995] / 10.0f) + 35.0f);
            Math_ApproachF(&this->dyna.actor.scale.x, (gGameInfo->data[0x996] / 100.0f) + 0.02f,
                           (gGameInfo->data[0x997] / 100.0f) + 0.2f, (gGameInfo->data[0x998] / 1000.0f) + 0.002f);
            this->dyna.actor.scale.z = this->dyna.actor.scale.x;
            if (this->dyna.actor.scale.y < 0.001f) {
                Actor_MarkForDeath(&this->dyna.actor);
            }
        }
    }
}

void EnWizBrock_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnWizBrock* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EnWizBrock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWizBrock* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                             0);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, 1);
    if (this->dyna.actor.colChkInfo.health != 0) {
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
        Gfx_DrawDListOpa(globalCtx, &object_wiz_DL_0010E8);

    } else {
        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (s8)this->alpha);
        Gfx_DrawDListXlu(globalCtx, &object_wiz_DL_0010E8);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
    if (this->unk1AA != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_wiz_Matanimheader_005C64));
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 255, 255);
        if (this->unk1AA == 1) {
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 00, 100, (s8)this->alpha);
        } else {
            gDPSetEnvColor(POLY_XLU_DISP++, 50, 00, 255, (s8)this->alpha);
        }
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, &object_wiz_DL_005870);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
