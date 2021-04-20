#include "z_en_ginko_man.h"

#define FLAGS 0x00000009

#define THIS ((EnGinkoMan*)thisx)

void EnGinkoMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnGinkoMan_Update(EnGinkoMan* this, GlobalContext* globalCtx);
void EnGinkoMan_Draw(Actor* thisx, GlobalContext* globalCtx);
//void EnGinkoMan_Draw(EnGinkoMan* this, GlobalContext* globalCtx);

void func_80A64554(EnGinkoMan* this);
void func_80A65490(EnGinkoMan* this);
void func_80A6557C(EnGinkoMan* this);
void func_80A656C4(EnGinkoMan* this);
void func_80A65800(EnGinkoMan* this);

void func_80A645A4(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65590(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A656D8(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65844(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A654A4(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65988(EnGinkoMan* this, GlobalContext* globalCtx);

const ActorInit En_Ginko_Man_InitVars = {
    ACTOR_EN_GINKO_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnGinkoMan),
    (ActorFunc)EnGinkoMan_Init,
    (ActorFunc)EnGinkoMan_Destroy,
    (ActorFunc)EnGinkoMan_Update,
    (ActorFunc)EnGinkoMan_Draw
};

// looks like an array of structs
UNK_TYPE D_80A65D60[] = {
0x060008C0, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x060043F0, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x06004F40, 0x3F800000, 0x00000000, 0x00000000, 0x02000000, 0xC0800000,
0x06000AC4, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x06004A7C, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x00000000, 0x00000000,
};

void EnGinkoMan_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;
    this->actor.targetMode = 1;
    this->actor.uncullZoneForward = 400.0f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 100;
    this->unk258 = 0;
    this->unk25E = 0;
    this->unk260 = 0;
    this->unk25C = 0;
    this->unk25A = 0;
    SkelAnime_InitSV(globalCtx, &this->anime, &D_0600C240, &D_060043F0, &this->unk18C, &this->unk1EC, 0x10);
    func_80A64554(this);
}

void EnGinkoMan_Destroy(Actor *thisx, GlobalContext *globalCtx) { }

// init extension
void func_80A64554(EnGinkoMan* this) {

    this->actor.flags |= 1;
    func_800BDC5C(&this->anime, &D_80A65D60, 1); // what
    this->actionFunc = func_80A645A4;
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A64554.asm")

//action func
void func_80A645A4(EnGinkoMan *this, GlobalContext *globalCtx) {
    s32 dYaw;
    s32 dYawABS;

    dYaw = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    func_80A65988(this, globalCtx);
    if (func_800B84D0(&this->actor, globalCtx)) {
        if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) {
            func_800BDC5C(&this->anime, D_80A65D60, 0);
            func_801518B0(globalCtx, 0x44CU, &this->actor);
            this->unk258 = 0x44C;
        } else {
            func_800BDC5C(&this->anime, D_80A65D60, 1);
            if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                func_801518B0(globalCtx, 0x467U, &this->actor);
                this->unk258 = 0x467;
            } else {
                func_801518B0(globalCtx, 0x466U, &this->actor);
                this->unk258 = 0x466;
            }
        }
        func_80A65490(this);
    } else {

        dYawABS = dYaw < 0 ? -dYaw : dYaw;
        if (dYawABS < 0x1555) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

//jump tables
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A646F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A64DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65364.asm")

// setup
void func_80A65490(EnGinkoMan* this) {
    this->actionFunc =  func_80A654A4;
}

//action func
// jump tables
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A654A4.asm")

void func_80A6557C(EnGinkoMan* this) {
    this->actionFunc =  func_80A65590;
}

// savecontext shinanigans
// NON_EQUIVELENET nowhere close
/*
void func_80A65590(EnGinkoMan *this, GlobalContext *globalCtx) {
    SaveContext* sCtx = &gSaveContext;

    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        this->actor.parent = NULL;
        func_80A656C4(this);
    } else if (this->unk258 == 0x45B) {
        if ((sCtx->perm.weekEventReg[0xA] & 8) != 0) {
        //if ((gSaveContext.perm.weekEventReg[0xA] & 8) != 0) {
            func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
        } else {
            // hang on, pad48 is an array, are we looking for one value?
            //func_800B8A1C(&this->actor, globalCtx,
                 //((u32) ((s32) gSaveContext.perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) + 8, 500.0f, 100.0f);
            func_800B8A1C(&this->actor, globalCtx,
                 ((u32) ((s32) sCtx->perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) + 8, 500.0f, 100.0f);
        }
    } else if (this->unk258 == 0x45C) {
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    } else if ((sCtx->perm.weekEventReg[0x3B] & 8) == 0) {
    //} else if ((gSaveContext.perm.weekEventReg[0x3B] & 8) == 0) {
        func_800B8A1C(&this->actor, globalCtx, 12, 500.0f, 100.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65590.asm")

//setup
void func_80A656C4(EnGinkoMan* this) {
    this->actionFunc =  func_80A656D8;
}

# if NON_MATCHING
// NON_MATCHING: minor regalloc at globalCtx into func_80152498
void func_80A656D8(EnGinkoMan* this, GlobalContext *globalCtx) {
    //u8 tempSCTXunkF02;
    //u8 tempSCTXunkF33;
    GlobalContext* gCtx;// = globalCtx;

    if (func_800B84D0(&this->actor, globalCtx)) {
        //tempSCTXunkF02 = gSaveContext.unkF02;
        //if (((tempSCTXunkF02 & 8) == 0) && (this->unk258 == 0x45B)) {
        if (((gSaveContext.perm.weekEventReg[0xA] & 8) == 0) && (this->unk258 == 0x45B)) {
            gSaveContext.perm.weekEventReg[0xA] |= 8;
            func_801518B0(globalCtx, 0x47AU, &this->actor);
            if (1) { // might be fake, but it solves almost everything
                this->unk258 = 0x47A;
            }
        } else {
            func_800BDC5C(&this->anime, &D_80A65D60, 1);
            func_801518B0(globalCtx, 0x47BU, &this->actor);
            this->unk258 = 0x47B;
        }
        func_80A65490(this);
    } else if (this->unk258 == 0x45D) {
        //if ((func_80152498(&globalCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
        gCtx = globalCtx;
        if ((func_80152498(&gCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
            //tempSCTXunkF33 = gSaveContext.unkF33;
            //if ((tempSCTXunkF33 & 8) == 0) {
            if ((gSaveContext.perm.weekEventReg[0x3B] & 8) == 0) {
                gSaveContext.perm.weekEventReg[0x3B] |= 8;
            }
            func_80A64554(this);
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 500.0f, -1);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A656D8.asm")
#endif

void func_80A65800(EnGinkoMan* this) {
    func_800BDC5C(&this->anime, D_80A65D60, 2);
    this->actionFunc =  func_80A65844;
}

// action func: stamping?
void func_80A65844(EnGinkoMan *this, GlobalContext *globalCtx) {
    if ((this->unk258 == 0x464) && (func_801378B8(&this->anime, 10.0f))) {
        Audio_PlayActorSound2(this, 0x2993); // NA_SE_EV_HANKO "stamp"
    }

    if (func_801378B8(&this->anime, this->anime.animFrameCount)) {
        switch(this->unk258){
            case 0x464:
                func_800BDC5C(&this->anime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x465, &this->actor);
                this->unk258 = 0x465;
                break;

            case 0x469: 
                func_800BDC5C(&this->anime, D_80A65D60, 1);
                globalCtx->msgCtx.unk1207C = (gSaveContext.perm.unkEDC & 0xFFFF); 
                // perm.day case req for div vs divu
                if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                    func_801518B0(globalCtx, 0x46C, &this->actor);
                    this->unk258 = 0x46C;
                } else {
                    func_801518B0(globalCtx, 0x46A, &this->actor);
                    this->unk258 = 0x46A;
                }
                break;
        }

        func_80A65490(this);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65988.asm")

// update extension
//think this function adjusts his animation so that he faces the player
// non-matching: branch delay slot shinanigans
void func_80A65A5C(EnGinkoMan *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->anime);

    if (this->anime.animCurrentSeg != &D_06004A7C) {
        func_800E9250(globalCtx, &this->actor, &this->unk24C, &this->unk252,
           this->actor.focus.pos);
    } else {
        func_800E8F08(&this->unk24C, &this->unk252);
    }
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65A5C.asm")

void EnGinkoMan_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;

    this->actionFunc(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    func_80A65A5C(this, globalCtx);

}

//override limbdraw
// issue: these use values in the padding, I suspect a struct
/*
s32 func_80A65B44(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor){
    EnGinkoMan* this = (EnGinkoMan*) actor;
    if (limbIndex == 15) {
        *dList = (void *)0x600B1D8;
    }
    if (limbIndex == 15) {
        SysMatrix_InsertTranslation(D_80A65EE8, 0.0f, 0.0f, 1);
        SysMatrix_InsertXRotation_s(this->unk24E, 1);
        SysMatrix_InsertZRotation_s(this->unk24C, 1);
        SysMatrix_InsertTranslation(D_80A65EEC, 0.0f, 0.0f, 1);
    } else if (limbIndex == 8) {
        SysMatrix_InsertXRotation_s((s16) -(s32) this->unk254, 1);
        SysMatrix_InsertZRotation_s((s16) -(s32) this->unk252, 1);
    }
    return 0;
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65B44.asm")

// post limbdraw
void func_80A65C18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor){ }

// putting this here now, haven't worked on it yet
/*
void EnGinkoMan_Draw(EnGinkoMan *this, GlobalContext *globalCtx) {
    Gfx *sp38;
    Gfx *sp34;
    Gfx *temp_v0;
    Gfx *temp_v0_2;
    Gfx *temp_v0_3;
    GraphicsContext *temp_a0;
    GraphicsContext *temp_s0;

    temp_a0 = globalCtx->state.gfxCtx;
    temp_s0 = temp_a0;
    func_8012C28C(temp_a0);
    temp_v0 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0 + 8;
    temp_v0->words.w0 = 0xDB060020;
    sp38 = temp_v0;
    sp38->words.w1 = Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0);
    temp_v0_2 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_2 + 8;
    temp_v0_2->words.w0 = 0xDB060024;
    sp34 = temp_v0_2;
    sp34->words.w1 = Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0);
    temp_v0_3 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_3 + 8;
    temp_v0_3->words.w1 = 0;
    temp_v0_3->words.w0 = 0xE7000000;
    SkelAnime_DrawSV(globalCtx, this->anime.skeleton, this->anime.limbDrawTbl, (s32) this->anime.dListCount, &func_80A65B44, &func_80A65C18, this);
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Draw.asm")
