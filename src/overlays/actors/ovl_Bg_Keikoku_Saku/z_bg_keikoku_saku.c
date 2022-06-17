/*
 * File: z_bg_keikoku_saku.c
 * Overlay: ovl_Bg_Keikoku_Saku
 * Description: Termina Field Spiked Fence
 */

#include "z_bg_keikoku_saku.h"
#include "objects/object_keikoku_obj/object_keikoku_obj.h"

#define FLAGS 0x00000000

#define THIS ((BgKeikokuSaku*)thisx)

void BgKeikokuSaku_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A5389C(BgKeikokuSaku* this, GlobalContext* globalCtx);
void func_80A538E0(BgKeikokuSaku* this, GlobalContext* globalCtx);
void func_80A53994(BgKeikokuSaku* this, GlobalContext* globalCtx);

const ActorInit Bg_Keikoku_Saku_InitVars = {
    ACTOR_BG_KEIKOKU_SAKU,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_OBJ,
    sizeof(BgKeikokuSaku),
    (ActorFunc)BgKeikokuSaku_Init,
    (ActorFunc)BgKeikokuSaku_Destroy,
    (ActorFunc)BgKeikokuSaku_Update,
    (ActorFunc)BgKeikokuSaku_Draw,
};

void BgKeikokuSaku_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgKeikokuSaku* this = THIS;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_keikoku_obj_Colheader_002300, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    this->switchFlag = BGKEIKOKUSAKU_GET_SWITCHFLAG(thisx);
    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        this->dyna.actor.world.pos.z = 2659.0f;
    } else {
        this->actionFunc = func_80A5389C;
    }
}

void BgKeikokuSaku_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgKeikokuSaku* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80A5389C(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        this->actionFunc = func_80A538E0;
    }
}

void func_80A538E0(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALGATE_OPEN - SFX_FLAG);
    this->dyna.actor.world.pos.z -= 2.0f + BREG(8);
    if (this->dyna.actor.world.pos.z < (BREG(9) + 2660.0f)) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BRIDGE_OPEN_STOP);
        this->timer = 30;
        this->actionFunc = func_80A53994;
    }
}

void func_80A53994(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    if (this->timer == 0) {
        this->actionFunc = func_80A5389C;
    }
}

void BgKeikokuSaku_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgKeikokuSaku* this = THIS;

    if (this->timer) {
        this->timer--;
    }
    this->dyna.actor.world.pos.x = BREG(5) + this->dyna.actor.home.pos.x;
    this->dyna.actor.world.pos.y = BREG(6) + this->dyna.actor.home.pos.y;
    this->dyna.actor.world.pos.z = BREG(7) + this->dyna.actor.home.pos.z;
    this->dyna.actor.scale.x = (BREG(10) / 1000.0f) + 0.1f;
    this->dyna.actor.scale.y = (BREG(11) / 1000.0f) + 0.1f;
    this->dyna.actor.scale.z = (BREG(12) / 1000.0f) + 0.1f;
    this->actionFunc(this, globalCtx);
}

void BgKeikokuSaku_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_keikoku_obj_DL_001640);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
