#include "z_bg_kin2_fence.h"

#define FLAGS 0x00000010

#define THIS ((BgKin2Fence*)thisx)

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Kin2_Fence_InitVars = {
    ACTOR_BG_KIN2_FENCE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Fence),
    (ActorFunc)BgKin2Fence_Init,
    (ActorFunc)BgKin2Fence_Destroy,
    (ActorFunc)BgKin2Fence_Update,
    (ActorFunc)BgKin2Fence_Draw
};
*/

static InitChainEntry D_80B6EEE8[] = {
    ICHAIN_U8(shape, 8, ICHAIN_STOP),
};

extern BgMeshHeader* D_06000908;
extern ColliderJntSphInit* D_80B6EE70; 

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E890.asm")

//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Init.asm")
void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Fence* this = THIS;

    ColliderJntSph *temp_s3;
    s32 temp_s0;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, &D_80B6EEE8);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000908);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->dyna.actor, &D_80B6EE70, &this->collider.elements);
    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape);
    SysMatrix_InsertScale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, 1);
    i = 0;

    for (i = 0; i < 4; i++){
        Collider_UpdateSpheres(i, &this->collider);
    }

    if (Actor_GetSwitchFlag(globalCtx, this->dyna.actor.params & 0x7F)) {
        func_80B6ED30(this);
        return;
    }
    func_80B6EADC(this);
}
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EAF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EBF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ED30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ED58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Draw.asm")
