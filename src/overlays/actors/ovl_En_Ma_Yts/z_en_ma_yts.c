#include "z_en_ma_yts.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D0BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D12C.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8E0BC.asm")
