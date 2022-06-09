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
    BgKeikokuSaku* this = THIS;
    s32 pad;
    CollisionHeader* colHeader;

    colHeader = NULL;
    DynaPolyActor_Init(&this->Dyna, 0);
    CollisionHeader_GetVirtual(&object_keikoku_obj_Colheader_002300, &colHeader);
    this->Dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->Dyna.actor, colHeader);
    this->unk160 = ACTOR_GET_SWITCHFLAG(thisx);
    if (Flags_GetSwitch(globalCtx, this->unk160)) {
        this->Dyna.actor.world.pos.z = 2659.0f;
        return;
    }
    this->actionFunc = func_80A5389C;
}

void BgKeikokuSaku_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgKeikokuSaku* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->Dyna.bgId);
}

void func_80A5389C(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->unk160)) {
        this->actionFunc = func_80A538E0;
    }
}

void func_80A538E0(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->Dyna.actor, NA_SE_EV_METALGATE_OPEN - SFX_FLAG);
    this->Dyna.actor.world.pos.z -= 2.0f + gGameInfo->data[0x968];
    if (this->Dyna.actor.world.pos.z < (gGameInfo->data[0x969] + 2660.0f)) {
        Actor_PlaySfxAtPos(&this->Dyna.actor, 0x280EU);
        this->unk162 = 30;
        this->actionFunc = func_80A53994;
    }
}

void func_80A53994(BgKeikokuSaku* this, GlobalContext* globalCtx) {
    if (this->unk162 == 0) {
        this->actionFunc = func_80A5389C;
    }
}

void BgKeikokuSaku_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgKeikokuSaku* this = THIS;

    if (this->unk162) {
        this->unk162--;
    }
    this->Dyna.actor.world.pos.x = gGameInfo->data[0x965] + this->Dyna.actor.home.pos.x;
    this->Dyna.actor.world.pos.y = gGameInfo->data[0x966] + this->Dyna.actor.home.pos.y;
    this->Dyna.actor.world.pos.z = gGameInfo->data[0x967] + this->Dyna.actor.home.pos.z;
    this->Dyna.actor.scale.x = (gGameInfo->data[0x96A] / 1000.0f) + 0.1f;
    this->Dyna.actor.scale.y = (gGameInfo->data[0x96B] / 1000.0f) + 0.1f;
    this->Dyna.actor.scale.z = (gGameInfo->data[0x96C] / 1000.0f) + 0.1f;
    this->actionFunc(this, globalCtx);
}

void BgKeikokuSaku_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_keikoku_obj_DL_001640);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
