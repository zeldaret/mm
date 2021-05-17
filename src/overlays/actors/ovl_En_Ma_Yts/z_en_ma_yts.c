#include "z_en_ma_yts.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B8D030(EnMaYts* this);
// func_80B8D0BC
void func_80B8D12C(EnMaYts* this, GlobalContext* globalCtx);

/*
const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw
};
*/

// blinking probably. DECR does weird things, probably bad types in the actor's struct
void func_80B8D030(EnMaYts *this) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 phi_v1;

    temp_v0 = (s16) this->unk_328;
    if (temp_v0 != 0) {
        this->unk_32A = (u16) temp_v0;
        return;
    }
    temp_v0_2 = (s16) this->unk_326;
    if (temp_v0_2 == 0) {
        phi_v1 = (u16)0;
    } else {
        this->unk_326 = temp_v0_2 - 1;
        phi_v1 = (s16) this->unk_326;
    }
    if (phi_v1 == 0) {
        this->unk_32A = (s16) this->unk_32A + 1;
        if ((s32) (s16) this->unk_32A >= 3) {
            this = this;
            this->unk_326 = Rand_S16Offset(30, 30);
            this->unk_32A = 0;
        }
    }
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D030.asm")

/*
void func_80B8D0BC(EnMaYts *this, GlobalContext *globalCtx) {
    void *sp28;
    void *temp_v1;

    temp_v1 = ((s32) globalCtx * 0x10) + &D_80B8E1A8;
    sp28 = temp_v1;
    SkelAnime_ChangeAnim(&this->unk_144, temp_v1->unk0, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(temp_v1->unk0), (?32) temp_v1->unk8, temp_v1->unkC);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D0BC.asm")

/*
void func_80B8D12C(EnMaYts *this, GlobalContext *globalCtx) {
    s16 sp22;
    Actor *temp_v1;
    s16 temp_v0;
    struct Actor *temp_v0_2;
    s16 phi_a3;

    temp_v0 = (s16) this->unk_32C;
    temp_v1 = globalCtx->actorCtx.actorList[2].first;
    phi_a3 = (u16)0;
    if (temp_v0 == 2) {
        phi_a3 = (u16)1;
    }
    if ((temp_v0 == 0) || (temp_v0_2 = this->actor.parent, (temp_v0_2 == 0))) {
        this->unk1F0 = (bitwise s32) temp_v1->world.pos.x;
        this->unk1F4 = (bitwise f32) (bitwise s32) temp_v1->world.pos.y;
        this->unk1F8 = (bitwise s32) temp_v1->world.pos.z;
        this->unk1F4 = (f32) (this->unk1F4 - -10.0f);
    } else {
        sp22 = phi_a3;
        Math_Vec3f_StepTo(this + 0x1F0, (Vec3f *) &temp_v0_2->world, 8.0f);
        this->unk1F4 = (f32) (this->unk1F4 - -10.0f);
    }
    func_800BD888(this, &this->unk_1D8, 0, phi_a3);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D12C.asm")

/*
void func_80B8D1E8(void *arg0, ? arg1) {
    s16 temp_v0;

    temp_v0 = arg0->unk330;
    if (temp_v0 == 0) {
        arg0->unk1F = (u8)0;
        func_80B8D0BC(0);
        return;
    }
    if (temp_v0 == 1) {
        arg0->unk1F = (u8)6;
        if ((((s32) gSaveContext.perm.day % 5) == 1) || ((gSaveContext.unkF0E & 1) != 0)) {

        } else {
            func_80B8D0BC(0x12);
            return;
        }
        func_80B8D0BC(0xE);
        return;
    }
    if (temp_v0 == 2) {
        arg0->unk1F = (u8)0;
        arg0->unk13C = &func_80B8E0BC;
        func_80B8D0BC(0);
        return;
    }
    if (temp_v0 == 3) {
        arg0->unk1F = (u8)0;
        func_80B8D0BC(0);
        return;
    }
    func_80B8D0BC(0);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D2D8.asm")

extern ColliderCylinderInit D_80B8E170;
extern CollisionCheckInfoInit2 D_80B8E19C;

/*
void EnMaYts_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;
    ColliderCylinder *temp_a1;

    this->unk_330 = (s16) ((s32) (this->actor.params & 0xF000) >> 0xC);
    if (func_80B8D2D8(this, globalCtx) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
    ActorShape_Init(&this->actor.shape, 0.0f, (void (*)(struct Actor *actor, struct Lights *mapper, struct GlobalContext *ctxt)) func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->unk_144, (void *)0x6013928, NULL, &this->unk_204, &this->unk_294, 0x17);
    func_80B8D1E8(this, globalCtx);
    temp_a1 = &this->unk_18C;
    Collider_InitCylinder(globalCtx, temp_a1);
    Collider_SetCylinder(globalCtx, temp_a1, &this->actor, &D_80B8E170);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B8E19C);
    if (this->unk_330 == 2) {
        this->unk_18C.dim.radius = 0x28;
    }
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_1D8 = 0;
    this->unk_200 = 0;
    this->unk_326 = 0;
    if (this->unk_330 == 3) {
        this->unk_336 = 1;
    } else {
        this->unk_336 = 0;
    }
    if (((u16)1U == ((s32) gSaveContext.perm.day % 5)) || ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
        this->unk_328 = 0;
        this->unk_32A = 0;
        this->unk_32E = 0;
        this->unk_32C = 0;
    } else {
        this->unk_328 = 1;
        this->unk_32A = 1;
        this->unk_32E = 2;
        this->unk_32C = 2;
    }
    if (this->unk_330 == 3) {
        this->unk_328 = 0;
        this->unk_32A = 0;
        this->unk_32E = 0;
        this->unk_32C = 2;
        func_80B8D9E4(this, 5);
        return;
    }
    if ((((s32) gSaveContext.perm.day % 5) == (u16)2U) && ((u16)1U == gSaveContext.perm.isNight) && ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
        func_80B8D6BC(this, 5);
        return;
    }
    func_80B8D698(this, 5);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Init.asm")

void EnMaYts_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk_18C);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DBB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DD88.asm")

void EnMaYts_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;
    ColliderCylinder *cylinder;

    this->unk_188(this, globalCtx);
    cylinder = &this->unk_18C;
    Collider_UpdateCylinder(&this->actor, cylinder);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &cylinder->base);
    SkelAnime_FrameUpdateMatrix(&this->unk_144);
    func_80B8D030(this);
    func_80B8D12C(this, globalCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Update.asm")

extern AnimationHeader D_06009E58;
extern AnimationHeader D_06007D98;

// OverrideLimbDraw
s32 func_80B8DE44(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnMaYts* this = THIS;
    Vec3s sp4;

    if (limbIndex == 14) {
        sp4 = this->unk_1E0;
        rot->x = rot->x + sp4.y;
        if ((this->unk_144.animCurrentSeg == &D_06009E58) || (this->unk_144.animCurrentSeg == &D_06007D98)) {
            rot->z = rot->z + sp4.x;
        }
    } else if (limbIndex == 13) {
        sp4 = this->unk_1E6;
        rot->x = rot->x + sp4.y;
        rot->z = rot->z + sp4.x;
    }
    return 0;
}

extern UNK_TYPE D_060003B0;

// PostLimbDraw
void func_80B8DF18(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == 14) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
    else if ((limbIndex == 19) && (this->unk_336 == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, &D_060003B0);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

extern void* D_80B8E308[];
extern void* D_80B8E318[]; // eyeTextures

void EnMaYts_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_80B8E308[this->unk_32E]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80B8E318[this->unk_32A]));

    SkelAnime_DrawSV(globalCtx, this->unk_144.skeleton, this->unk_144.limbDrawTbl, (s32) this->unk_144.dListCount, func_80B8DE44, func_80B8DF18, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8E0BC.asm")
