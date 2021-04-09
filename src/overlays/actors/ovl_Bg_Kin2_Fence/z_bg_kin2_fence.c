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

s32 func_80B6E820(BgKin2Fence* this) {
    ColliderJntSphElement* elements = this->collider.elements;
    
    if (elements[0].info.bumperFlags & 2) {
        return 0;
    }
    if (elements[1].info.bumperFlags & 2) {
        return 1;
    }
    if (elements[2].info.bumperFlags & 2) {
        return 2;
    }
    if (elements[3].info.bumperFlags & 2) {
        return 3;
    }
    return -1;
}

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

void BgKin2Fence_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    BgKin2Fence* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80B6EADC(BgKin2Fence* this) {
    this->unk280 = 0;
    this->actionFunc = func_80B6EAF4;
}

void func_80B6EAF4(BgKin2Fence* this, GlobalContext* globalCtx) {
    s32 hitMask;
    s32 nextMask;

    if (this->collider.base.acFlags & 2) {
        hitMask = func_80B6E820(this);
        if (hitMask >= 0) {
            nextMask = (s8)gSaveContext.perm.spiderHouseMaskOrder[this->unk280];
            if (hitMask == nextMask) {
                play_sound(0x4807U);
                this->unk280 += 1;
                func_80B6E890(this, globalCtx, nextMask);
            } else {
                play_sound(0x4806U);
                this->unk280 = 0;
            }
        }
        this->collider.base.acFlags &= 0xFFFD;
        this->unk281 = 5;
        if (this->unk280 >= 6) {
            func_80B6EBF4(this);
            return;
        }
    } else {
        if (this->unk281 > 0) {
            this->unk281 -= 1;
            return;
        }
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EBF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECC4.asm")

void func_80B6ECD8(BgKin2Fence* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 58.0f, 5.0f)) {
        func_80B6ED30(this);
    }
}
void func_80B6ED30(BgKin2Fence* this) {
    this->actionFunc = func_80B6ED58;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 58.0f;
}

void func_80B6ED58(BgKin2Fence* this, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Draw.asm")
