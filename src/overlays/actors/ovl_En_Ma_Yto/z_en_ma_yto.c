/*
 * File: z_en_ma_yto.c
 * Overlay: ovl_En_Ma_Yto
 * Description: Cremia
 */

#include "z_en_ma_yto.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYto*)thisx)

void EnMaYto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ma_Yto_InitVars = {
    ACTOR_EN_MA_YTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA2,
    sizeof(EnMaYto),
    (ActorFunc)EnMaYto_Init,
    (ActorFunc)EnMaYto_Destroy,
    (ActorFunc)EnMaYto_Update,
    (ActorFunc)EnMaYto_Draw
};
*/


/*
void EnMaYto_Init(Actor *thisx, GlobalContext *globalCtx) {
    ColliderCylinder *sp30;
    ColliderCylinder *temp_a1;

    thisx->targetMode = 0;
    thisx->unk200 = 0;
    thisx->unk310 = (u16)0;
    thisx->unk320 = (u16)0;
    thisx->unk31A = (u16)0;
    if ((((s32) gSaveContext.perm.day % 5) == 1) || ((gSaveContext.unkF0E & 1) != 0)) {
        func_80B90EC8(thisx, 0, 1);
    } else {
        func_80B90EC8(thisx, 5, 2);
    }
    thisx->unk31E = (u16)0;
    thisx->unk31C = (u16)0x64;
    thisx->unk204 = (s32) ((s32) (thisx->params & 0xF000) >> 0xC);
    if (func_80B8E6E0(thisx, globalCtx) == 0) {
        Actor_MarkForDeath(thisx);
        return;
    }
    ActorShape_Init(&thisx->shape, 0.0f, (void (*)(struct Actor *actor, struct Lights *mapper, struct GlobalContext *ctxt)) func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, (SkelAnime *) (thisx + 0x144), (void *)0x6015C28, NULL, thisx + 0x208, thisx + 0x28C, 0x16);
    func_80B8E84C(thisx, globalCtx);
    temp_a1 = thisx + 0x18C;
    sp30 = temp_a1;
    Collider_InitCylinder(globalCtx, temp_a1);
    Collider_SetCylinder(globalCtx, temp_a1, thisx, &D_80B91410);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, DamageTable_Get(0x16), &D_80B9143C);
    func_800B78B8(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 4);
    if (func_80B8EABC(thisx, globalCtx) == 1) {
        func_80B8EBDC(thisx);
        return;
    }
    func_80B8E938(thisx, globalCtx);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E84C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EA38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EABC.asm")

void EnMaYto_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYto* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EBF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ECAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ED8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EF4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9000C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9037C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9059C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B905B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9061C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9083C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90C08.asm")

void func_80B90C78(EnMaYto* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90C78.asm")

void func_80B90D98(EnMaYto* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90D98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9109C.asm")

void EnMaYto_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYto* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80B90D98(this, globalCtx);
    func_80B90C78(this, globalCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Draw.asm")
