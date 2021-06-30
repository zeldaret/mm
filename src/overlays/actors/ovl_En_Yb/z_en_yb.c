#include "z_en_yb.h"

#define FLAGS 0x02000019

#define THIS ((EnYb*)thisx)

//void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
//void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnYb_Init(EnYb* this, GlobalContext* globalCtx);
void EnYb_Update(EnYb* this, GlobalContext* globalCtx);
void EnYb_Draw(EnYb* this, GlobalContext* globalCtx);


void func_80BFAC88(EnYb* this, GlobalContext* globalCtx);
void func_80BFAE80(EnYb* this, GlobalContext* globalCtx);
void func_80BFA730(EnYb* this, GlobalContext* globalCtx);
void func_80BFA91C(EnYb* this, GlobalContext* globalCtx);
void func_80BFA9D4(EnYb* this, GlobalContext* globalCtx);
void func_80BFAB4C(EnYb* this, GlobalContext* globalCtx);
void func_80BFABF0(EnYb* this, GlobalContext* globalCtx);
void func_80BFA868(EnYb* this, GlobalContext* globalCtx);

void func_80BFA634(EnYb* this, GlobalContext* globalCtx);
s32 func_80BFA5CC(EnYb* this, GlobalContext* globalCtx); 
void func_80BFA67C(EnYb* this);


/*
const ActorInit En_Yb_InitVars = {
    ACTOR_EN_YB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_YB,
    sizeof(EnYb),
    (ActorFunc)EnYb_Init,
    (ActorFunc)EnYb_Destroy,
    (ActorFunc)EnYb_Update,
    (ActorFunc)EnYb_Draw,
};
*/


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Init.asm")

void EnYb_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnYb* this = (EnYb*) thisx;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BFA2FC(GlobalContext *globalCtx);

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA5CC.asm")

void func_80BFA634(EnYb *this, GlobalContext *globalCtx) {
    if (this->unk412 <= 0) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    } else {
        func_801360E0(globalCtx, &this->skelAnime);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA67C.asm")

// zero is the only input...?
void func_80BFA6E0(EnYb *this, s16 arg1) {
    func_80BFA67C(this);
    this->unk41A[0] = arg1;
}

void func_80BFA710(EnYb* this) { 
    func_800B9084(&this->actor); // sets flag 20 of unk39 in actor
}

extern u32 D_80BFB2E8;

void func_80BFA730(EnYb *this, GlobalContext *globalCtx) {
    s32 pad;
    Vec3f sp60;
    s32 i;

    func_80BFA634(this, globalCtx);
    for (i = 3; i >= 0; i--) {
        sp60.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
        sp60.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
        func_800B3030(globalCtx, &sp60, &D_80BFB2E8, &D_80BFB2E8, 0x64, 0, 2);
    }

    func_800F0568(globalCtx, (Vec3f *) &this->actor.world, 0x14, (u16)0x3878);
    if ((s32) this->unk414 >= 0xB) {
        this->unk414 -= 10;
        return;
    }
    Actor_MarkForDeath((Actor *) this);
}

void func_80BFA868(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if (func_800B84D0((Actor *) this, globalCtx) != 0) {
        this->actor.flags &= ~ 0x10000;
        this->actionFunc = func_80BFA9D4;
        func_801518B0(globalCtx, 0x147D, (Actor *) this);
        func_80BFA2FC(globalCtx);
    } else {
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

void func_80BFA91C(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if (Actor_HasParent((Actor *) this, globalCtx) != 0) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BFA868;
        this->actor.flags |= 0x10000;
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        func_800B8A1C((Actor *) this, globalCtx, 0x89, 10000.0f, 100.0f);
    }
    func_80BFA710(this);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA9D4.asm")

void func_80BFAB4C(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if (func_800B84D0((Actor *) this, globalCtx) != 0) {
        this->actionFunc = func_80BFA9D4;
        func_801518B0(globalCtx, 0x147C, (Actor *) this); //sfx?
        this->actor.flags &= ~ 0x10000; //0xFFFEFFFF;
    } else {
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

void func_80BFABF0(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if ((s32) this->unk41A[1] > 0) {
        this->unk41A[1]--;
    } else {
        func_80BFA67C(this);
        this->actionFunc = func_80BFAB4C;
        this->actor.flags |= 0x10000;
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

void func_80BFAC88(EnYb *this, GlobalContext *globalCtx) {
    s32 pad;
    ActorPlayer *player = PLAYER;

    func_80BFA634(this, globalCtx);
    if ((this->actor.xzDistToPlayer < 180.0f) && (fabsf(this->actor.yDistToPlayer) < 50.0f) 
      && (globalCtx->msgCtx.unk1202A == 3) && (globalCtx->msgCtx.unk1202E == 7) && (gSaveContext.playerForm == 4)) {
        this->actionFunc = func_80BFABF0;
        this->unk41A[1] = 0xC8;
        func_80BFA6E0(this, 0);
    } else if (func_800B84D0((Actor *) this, globalCtx) != 0) {
        func_80BFA2FC(globalCtx);
        this->actionFunc = func_80BFA9D4;
        if (func_8012403C(globalCtx) == 0xE) {
            func_801518B0(globalCtx, 0x147C, (Actor *) this);
        } else {
            func_801518B0(globalCtx, 0x147B, (Actor *) this);
        }
    } else if (func_80BFA5CC(this, globalCtx) != 0) {
        func_800B8614((Actor *) this, globalCtx, 120.0f);
    }

    if ((this->unk410 & 1) != 0) {
        if ((player->unkA70 * 0x10) >= 0) {
            this->unk410 &= ~1;
        }
    } else if (((player->unkA70 * 0x10) < 0) && (this->actor.xzDistToPlayer < 180.0f) && (fabsf(this->actor.yDistToPlayer) < 50.0f)) {
        this->unk410 |= 1;
        Audio_PlayActorSound2((Actor *) this, 0x4807);
    }

    func_80BFA710(this);
}

void func_80BFAE80(EnYb *this, GlobalContext *globalCtx) {
    if (gSaveContext.time < 0x4000) {
        func_80BFA634(this, globalCtx);
        this->unk414 += 5;
        if (this->unk414 >= 0xFB) {
            this->unk414 = 0xFF;
            this->actor.flags |= 1;
            this->actionFunc = func_80BFAC88;
        }
        func_80BFA710(this);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFB074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFB0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Draw.asm")
