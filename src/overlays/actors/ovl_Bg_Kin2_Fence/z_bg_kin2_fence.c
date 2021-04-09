#include "z_bg_kin2_fence.h"

#define FLAGS 0x00000010

#define THIS ((BgKin2Fence*)thisx)

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B6EADC(BgKin2Fence* this);
void func_80B6EAF4(BgKin2Fence* this, GlobalContext* globalCtx);
void func_80B6ED30(BgKin2Fence* this);
void func_80B6ED58(BgKin2Fence* this, GlobalContext* globalCtx);

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

extern InitChainEntry D_80B6EEE8;
extern BgMeshHeader* D_06000908;
extern ColliderJntSphInit* D_80B6EE70; 

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E890.asm")

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Fence* this = THIS;
    s32 i = 0;

    Actor_ProcessInitChain(&this->dyna.actor, &D_80B6EEE8);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000908);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->dyna.actor, &D_80B6EE70, &this->colliderElements);
    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, 1);

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

void func_80B6EADC(BgKin2Fence* this) {
    this->unk280 = 0;
    this->actionFunc = func_80B6EAF4;
}

void func_80B6EAF4(BgKin2Fence* this, GlobalContext* globalCtx) {
    s32 sp20;
    GlobalContext *temp_a3;
    s32 temp_v0;
    s8 temp_a2;
    s8 temp_v0_2;

    temp_a3 = arg1;
    if ((arg0->unk16D & 2) != 0) {
        arg1 = temp_a3;
        temp_v0 = func_80B6E820(arg0, temp_a3);
        if (temp_v0 >= 0) {
            temp_a2 = (s8) gSaveContext.perm.spiderHouseMaskOrder[arg0->unk280];
            if (temp_v0 == temp_a2) {
                sp20 = (s32) temp_a2;
                arg1 = arg1;
                play_sound((u16)0x4807U);
                arg0->unk280 = (s8) (arg0->unk280 + 1);
                func_80B6E890(arg0, arg1, temp_a2);
            } else {
                play_sound((u16)0x4806U);
                arg0->unk280 = (u8)0;
            }
        }
        arg0->unk16D = (u8) (arg0->unk16D & 0xFFFD);
        arg0->unk281 = (u8)5;
        if ((s32) arg0->unk280 >= 6) {
            func_80B6EBF4(arg0);
            return;
        }
    } else {
        temp_v0_2 = arg0->unk281;
        if ((s32) temp_v0_2 > 0) {
            arg0->unk281 = (s8) (temp_v0_2 - 1);
            return;
        }
        CollisionCheck_SetAC(temp_a3, temp_a3 + 0x18884, arg0 + 0x15C);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EBF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECD8.asm")

void func_80B6ED30(BgKin2Fence* this) {
    this->actionFunc = func_80B6ED58;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 58.0f;
}

void func_80B6ED58(BgKin2Fence* this, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Draw.asm")
