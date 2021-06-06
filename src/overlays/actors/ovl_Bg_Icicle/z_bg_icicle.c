#include "z_bg_icicle.h"

#define FLAGS 0x00000000

#define THIS ((BgIcicle*)thisx)

void BgIcicle_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809C9D7C(BgIcicle* this, GlobalContext* globalCtx);
void func_809C9D8C(BgIcicle* this, GlobalContext* globalCtx);
void func_809C9DC4(BgIcicle* this, GlobalContext* globalCtx);
void func_809C9F28(BgIcicle* this, GlobalContext* globalCtx);
void func_809CA06C(BgIcicle* this, GlobalContext* globalCtx);

/*
const ActorInit Bg_Icicle_InitVars = {
    ACTOR_BG_ICICLE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_ICICLE,
    sizeof(BgIcicle),
    (ActorFunc)BgIcicle_Init,
    (ActorFunc)BgIcicle_Destroy,
    (ActorFunc)BgIcicle_Update,
    (ActorFunc)BgIcicle_Draw,
};
*/

extern InitChainEntry D_809CA2FC;
extern ColliderCylinderInit D_809CA2B0;
extern Vec3f D_809CA30C;
extern Color_RGBA8 D_809CA318;
extern Color_RGBA8 D_809CA31C;

extern Gfx D_060000D0[];
extern CollisionHeader D_06000294;

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Init.asm")
void BgIcicle_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIcicle* this = THIS;

    s32 paramsHigh;
    s32 paramsMid;

    Actor_ProcessInitChain(thisx, &D_809CA2FC);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000294);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, thisx, &D_809CA2B0);
    Collider_UpdateCylinder(thisx, &this->collider);

    paramsHigh = (thisx->params >> 8) & 0xFF;
    paramsMid = (thisx->params >> 2) & 0x3F;
    this->unk_161 = (thisx->params >> 8) & 0xFF;
    thisx->params &= 3;

    if (thisx->params == 0 || thisx->params == 3) {
        if (thisx->params == 0) {
            this->unk_160 = paramsHigh;
        } else {
            this->unk_160 = paramsMid;
        }
        this->actionFunc = func_809C9D7C;
    } else {
        this->dyna.actor.shape.rot.x = -0x8000;
        this->dyna.actor.shape.yOffset = 1200.0f;
        this->actionFunc = func_809C9D8C;
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Destroy.asm")
void BgIcicle_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIcicle* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9B9C.asm")
void func_809C9B9C(BgIcicle *this, GlobalContext *globalCtx, f32 arg2) {
    Vec3f velocity;
    Vec3f pos;
    s32 j;
    s32 i;

    func_800F0568(globalCtx, &this->dyna.actor.world.pos, 30, 0x28CB);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            pos.x = this->dyna.actor.world.pos.x + randPlusMinusPoint5Scaled(8.0f);
            pos.y = this->dyna.actor.world.pos.y + (Rand_ZeroOne() * arg2) + (i * arg2);
            pos.z = this->dyna.actor.world.pos.z + randPlusMinusPoint5Scaled(8.0f);

            velocity.x = randPlusMinusPoint5Scaled(7.0f);
            velocity.z = randPlusMinusPoint5Scaled(7.0f);
            velocity.y = (Rand_ZeroOne() * 4.0f) + 8.0f;
            
            EffectSsEnIce_Spawn(globalCtx, &pos, (Rand_ZeroOne() * 0.2f) + 0.1f, &velocity, &D_809CA30C, &D_809CA318, &D_809CA31C, 30);
        }
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9D7C.asm")
void func_809C9D7C(BgIcicle* this, GlobalContext* globalCtx) {
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9D8C.asm")
void func_809C9D8C(BgIcicle* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistToPlayer < 60.0f) {
        this->unk_162 = 10;
        this->actionFunc = func_809C9DC4;
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9DC4.asm")
void func_809C9DC4(BgIcicle* this, GlobalContext* globalCtx) {
    s32 randSign;
    f32 rand;

    if (this->unk_162 != 0) {
        this->unk_162--;
    }

    if (!(this->unk_162 % 4)) {
        Audio_PlayActorSound2(this, 0x28D4);
    }
    if (this->unk_162 == 0) {
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z;

        CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->actionFunc = func_809C9F28;
    } else {
        rand = Rand_ZeroOne();
        randSign = (Rand_ZeroOne() < 0.5f ? -1 : 1);
        this->dyna.actor.world.pos.x = (randSign * ((0.5f * rand) + 0.5f)) + this->dyna.actor.home.pos.x;
        rand = Rand_ZeroOne();
        randSign = (Rand_ZeroOne() < 0.5f ? -1 : 1);
        this->dyna.actor.world.pos.z = (randSign * ((0.5f * rand) + 0.5f)) + this->dyna.actor.home.pos.z;
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9F28.asm")
void func_809C9F28(BgIcicle* this, GlobalContext* globalCtx) {
    if ((this->collider.base.atFlags & 2) || (this->dyna.actor.bgCheckFlags & 1)) {
        this->collider.base.atFlags &= ~2;
        this->dyna.actor.bgCheckFlags &= ~1;

        if (this->dyna.actor.world.pos.y < this->dyna.actor.floorHeight) {
            this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
        }
        func_809C9B9C(this, globalCtx, 40.0f);

        if (this->dyna.actor.params == 2) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
            func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            this->actionFunc = func_809CA06C;
        } else {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
    } else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
        this->dyna.actor.world.pos.y += 40.0f;
        func_800B78B8(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);
        this->dyna.actor.world.pos.y -= 40.0f;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809CA06C.asm")
void func_809CA06C(BgIcicle* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 1.0f)) {
        this->actionFunc = func_809C9D8C;
        this->dyna.actor.velocity.y = 0.0f;
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809CA0BC.asm")
void func_809CA0BC(BgIcicle* this, GlobalContext* globalCtx) {
    s32 sp24;

    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        
        if (this->dyna.actor.params == 0) {
            func_809C9B9C(this, globalCtx, 50.0f);
            
            if (this->unk_160 != 0xFF) {
                Item_DropCollectibleRandom(globalCtx, NULL, &this->dyna.actor.world.pos, this->unk_160 << 4);
            }
        } else if (this->dyna.actor.params == 3) {
            sp24 = func_800A8150((s32)this->unk_160);
            func_809C9B9C(this, globalCtx, 50.0f);
            Item_DropCollectible(globalCtx, &this->dyna.actor.world.pos, (this->unk_161 << 8) | sp24);
        } else {
            if (this->dyna.actor.params == 2) {
                func_809C9B9C(this, globalCtx, 40.0f);
                this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                this->actionFunc = func_809CA06C;
                return;
            }

            func_809C9B9C(this, globalCtx, 40.0f);
        }
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Update.asm")
void BgIcicle_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIcicle* this = THIS;

    func_809CA0BC(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (this->actionFunc != func_809CA06C) {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Draw.asm")
void BgIcicle_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_060000D0);
}
