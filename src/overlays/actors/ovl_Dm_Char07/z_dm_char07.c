/*
 * File: z_dm_char07.c
 * Overlay: Dm_Char07
 * Description: Different Milk Bar Objects (Stage, Credits Stage, Spotlights, Dishes)
 */

#include "z_dm_char07.h"

#define FLAGS 0x00000030

#define THIS ((DmChar07*)thisx)

void DmChar07_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmChar07_DoNothing(DmChar07* this, GlobalContext* globalCtx);

const ActorInit Dm_Char07_InitVars = {
    ACTOR_DM_CHAR07,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MILKBAR,
    sizeof(DmChar07),
    (ActorFunc)DmChar07_Init,
    (ActorFunc)DmChar07_Destroy,
    (ActorFunc)DmChar07_Update,
    (ActorFunc)DmChar07_Draw,
};

extern Gfx D_06000100[];
extern Gfx D_06000240[];
extern Gfx D_06000650[];
extern Gfx D_06000790[];
extern Gfx D_06000B80[];
extern Gfx D_06000CC0[];
extern Gfx D_060010D0[];
extern Gfx D_06001210[];
extern Gfx D_060015E0[];
extern Gfx D_060016B8[];
extern Gfx D_06002BA0[];
extern Gfx D_06002CD0[];
extern CollisionHeader D_06006688;
extern Gfx D_060076A0[];
extern Gfx D_06007918[];
extern AnimatedMaterial D_060105F8;
extern Gfx D_06010D68[];

void DmChar07_SetupAction(DmChar07* this, DmChar07ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DmChar07_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    this->isStage = 0;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->spotlightFlags = DMCHAR07_GET_SPOTLIGHTFLAGS(thisx);
    thisx->params = DMCHAR07_GET_TYPE(thisx);
    if (this->dyna.actor.params == DMCHAR07_STAGE) {
        Actor_SetScale(&this->dyna.actor, 0.1f);
        this->isStage = 1;
        BcCheck3_BgActorInit(&this->dyna, 0);
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06006688);
    } else {
        Actor_SetScale(&this->dyna.actor, 1.0f);
    }
    DmChar07_SetupAction(this, DmChar07_DoNothing);
}

void DmChar07_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    if (this->isStage) {
        BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void DmChar07_DoNothing(DmChar07* this, GlobalContext* globalCtx) {
}

void DmChar07_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    this->actionFunc(this, globalCtx);
}

void DmChar07_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->dyna.actor.params) {
        case DMCHAR07_STAGE:
            gSPDisplayList(POLY_OPA_DISP++, D_06002CD0);
            break;
        case DMCHAR07_CREDITS_STAGE:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_060105F8));
            gSPDisplayList(POLY_OPA_DISP++, D_06007918);
            gSPDisplayList(POLY_OPA_DISP++, D_06000240);
            gSPDisplayList(POLY_OPA_DISP++, D_06000790);
            gSPDisplayList(POLY_OPA_DISP++, D_06000CC0);
            gSPDisplayList(POLY_OPA_DISP++, D_06001210);
            gSPDisplayList(POLY_OPA_DISP++, D_060016B8);
            break;
        case DMCHAR07_SPOTLIGHTS:
            if (this->spotlightFlags & DMCHAR07_STAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000240);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000790);
            }
            if (this->spotlightFlags & DMCHAR07_STAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000CC0);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_LEFT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06001210);
            }
            if (this->spotlightFlags & DMCHAR07_DOWNSTAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_060016B8);
            }
            break;
        case DMCHAR07_DISHES:
            gSPDisplayList(POLY_OPA_DISP++, D_06010D68);
            break;
    }

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->dyna.actor.params) {
        case DMCHAR07_STAGE:
            gSPDisplayList(POLY_XLU_DISP++, D_06002BA0);
            break;
        case DMCHAR07_CREDITS_STAGE:
            gSPDisplayList(POLY_XLU_DISP++, D_060076A0);
            gSPDisplayList(POLY_XLU_DISP++, D_06000100);
            gSPDisplayList(POLY_XLU_DISP++, D_06000650);
            gSPDisplayList(POLY_XLU_DISP++, D_06000B80);
            gSPDisplayList(POLY_XLU_DISP++, D_060010D0);
            gSPDisplayList(POLY_XLU_DISP++, D_060015E0);
            break;
        case DMCHAR07_SPOTLIGHTS:
            if (this->spotlightFlags & DMCHAR07_STAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000100);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000650);
            }
            if (this->spotlightFlags & DMCHAR07_STAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000B80);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_LEFT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_060010D0);
            }
            if (this->spotlightFlags & DMCHAR07_DOWNSTAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, D_060015E0);
            }
            break;
        case DMCHAR07_DISHES:
            break;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
