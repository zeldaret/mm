#include "z_bg_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AD68DC(BgLotus* this, GlobalContext* globalCtx);

const ActorInit Bg_Lotus_InitVars = {
    ACTOR_BG_LOTUS,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LOTUS,
    sizeof(BgLotus),
    (ActorFunc)BgLotus_Init,
    (ActorFunc)BgLotus_Destroy,
    (ActorFunc)BgLotus_Update,
    (ActorFunc)BgLotus_Draw,
};

/*static*/ u32 D_80AD6D10[] = {
    0x48580064,
    0x00000000,
    0x00000000,
    0x00000000,
};

extern BgMeshHeader D_06000A20; // Lilypad collision
extern Gfx D_06000040[]; // Liltpad model

void BgLotus_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;
    s32 pad;
    s32 sp2C;

    Actor_ProcessInitChain(&this->dyna.actor, D_80AD6D10);
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000A20);
    this->dyna.actor.floorHeight = func_800C411C(&globalCtx->colCtx, &thisx->floorPoly, &sp2C, &this->dyna.actor, &this->dyna.actor.world.pos);
    this->timer2 = 96;
    this->dyna.actor.world.rot.y = rand() >> 0x10;
    this->actionFunc = func_80AD68DC;
}

void BgLotus_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80AD6830(BgLotus* this) {
    f32 scale;

    if (this->dyna.actor.params == 0) {
        scale = sin_rad(this->timer * 0.7853982f) * ((0.014f * ((f32)this->timer / 8)) + 0.01f);
        this->dyna.actor.scale.x = (1.0f + scale) * 0.1f;
        this->dyna.actor.scale.z = (1.0f - scale) * 0.1f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD68DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD6A88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD6B68.asm")

void BgLotus_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;
    s32 pad;
    void* sp2C;

    func_800CA1E8(globalCtx, &globalCtx->colCtx, thisx->world.pos.x, thisx->world.pos.z, &this->unk160, &sp2C);
    this->actionFunc(this, globalCtx);
}

void BgLotus_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000040);
}
