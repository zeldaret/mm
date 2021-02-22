#include "z_bg_ikana_shutter.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaShutter*)thisx)

void BgIkanaShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Shutter_InitVars = {
    ACTOR_BG_IKANA_SHUTTER,
    ACTORTYPE_SWITCH,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaShutter),
    (ActorFunc)BgIkanaShutter_Init,
    (ActorFunc)BgIkanaShutter_Destroy,
    (ActorFunc)BgIkanaShutter_Update,
    (ActorFunc)BgIkanaShutter_Draw
};
*/

static InitChainEntry D_80BD5D10[] = {
    ICHAIN_F32(unkFC, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(unk100, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(unk104, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern BgMeshHeader D_06000F28;

s32 func_80BD5690(BgIkanaShutter* this, GlobalContext* globalCtx) {
    return Actor_GetSwitchFlag(globalCtx, this->dyna.actor.params & 0x7F) &&
    Actor_GetSwitchFlag(globalCtx, (this->dyna.actor.params & 0x7F) + 1) &&
    Actor_GetSwitchFlag(globalCtx, (this->dyna.actor.params & 0x7F) + 2) &&
    Actor_GetSwitchFlag(globalCtx, (this->dyna.actor.params & 0x7F) + 3);
}

void BgIkanaShutter_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaShutter* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, D_80BD5D10);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000F28);
    if (!((this->dyna.actor.params >> 8) & 1)) {
        if (func_80BD5690(this, globalCtx)) {
            func_80BD599C(this);
            return;
        }
        func_80BD5828(this);
        return;
    }
    if (Actor_GetRoomCleared(globalCtx, this->dyna.actor.room)) {
        func_80BD5C64(this);
        return;
    }
    func_80BD5AE8(this);
}

void BgIkanaShutter_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaShutter* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
}
GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5844.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5894.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD58F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD599C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD59C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD59F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5A18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5AE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5BC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5BD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5C64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5C8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Draw.asm")
