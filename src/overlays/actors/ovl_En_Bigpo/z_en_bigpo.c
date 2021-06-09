#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

//void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
//void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Init(EnBigpo* this, GlobalContext* globalCtx);
//void EnBigpo_Destroy(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_Update(EnBigpo* this, GlobalContext* globalCtx);

void func_80B61AC8(EnBigpo* this);
void func_80B61B38(EnBigpo* this);
void func_80B61D74(EnBigpo* this);
void func_80B61E9C(EnBigpo* this);
void func_80B62034(EnBigpo* this);
void func_80B62154(EnBigpo* this);
void func_80B622E4(EnBigpo* this);
void func_80B624F4(EnBigpo* this);
void func_80B6275C(EnBigpo* this);

void func_80B61AF8(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61B70(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61DA4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61F04(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62084(EnBigpo* this, GlobalContext* globalCtx);
void func_80B621CC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B623BC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B6259C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B627B4(EnBigpo* this, GlobalContext* globalCtx);

/*
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,;
    (ActorFunc)NULL,
};
*/

extern InitChainEntry D_80B65064;
extern DamageTable D_80B65044; 
extern ColliderCylinderInit D_80B65010;
extern CollisionCheckInfoInit D_80B6503C;

/*
// bleh these struct memes hurt
void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    s16 temp_a1;
    s32 *temp_s0;
    s32 temp_s1;
    LightInfo *phi_s3;
    s32 *phi_s0;
    LightInfo *phi_s2;
    s32 phi_s1;

    Actor_ProcessInitChain((Actor *) this, &D_80B65064);
    //temp_t6 = this->actor.params;
    //this->unk210 = ((s32) temp_t6 >> 8) & 0xFF;
    this->unk210 = (this->actor.params >> 8) & 0xFF;
    this->actor.params &= 0xFF;
    if (this->actor.params == 2) {
        if (Flags_GetSwitch(globalCtx, (s32) this->unk210) == 0) {
            this->actor.update = func_800BDFB0;
            func_80B6383C(this);
            return;
        }
        Actor_MarkForDeath((Actor *) this);
        return;
    }
    SkelAnime_Init(globalCtx, &this->skelAnime, (void *)0x6005C18, (void *)0x6000924, this->limbDrawTbl, this->transitionDrawTbl, 0xA);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, (Actor *) this, &D_80B65010);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B65044, &D_80B6503C);
    temp_s0 = &this->fires[0].unk10;
    phi_s3 = this->fires[1].info;
    phi_s0 = temp_s0;
    phi_s2 = (LightInfo *) (temp_s0 + 0x10);
    phi_s1 = 0;
  loop_5:
    phi_s0->unkC = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, phi_s3);
    Lights_PointNoGlowSetInfo(phi_s2, (s16) (s32) this->actor.home.pos.x, (s16) (s32) this->actor.home.pos.y, (s16) (s32) this->actor.home.pos.z, 0xFF, 0xFF, 0xFF, 0);
    temp_s1 = phi_s1 + 0x20;

    //phi_s3 += 0x20;
    //phi_s0 += 0x20;
    //phi_s2 += 0x20;
    //phi_s1 = temp_s1;
    if (temp_s1 != 0x60) {
        goto loop_5;
    }
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 45.0f);
    temp_a1 = this->unk210;
    this->actor.bgCheckFlags |= 0x400;
    this->unk218 = this->actor.home.pos.y + 100.0f;
    this->unk290 = 0xFF; // color?
    this->unk291 = 0xFF;
    this->unk292 = 0xD2;
    this->unk293 = 0;
    if ((temp_a1 != 0xFF) && (Flags_GetSwitch(globalCtx, (s32) temp_a1) != 0)) {
        Actor_MarkForDeath((Actor *) this);
    }
    if (this->actor.params == 0) {
        this->unk204 = (u8)1;
        this->actor.flags &= -0x11;
        func_80B61AC8(this);
    } else if (this->actor.params == 1) {
        func_80B63450(this);
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Init.asm")

void EnBigpo_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    GlobalContext *gCtx2;
    s32 i;

    if ((this->actor.params != 2) && (this->actor.params != 3) && (this->actor.params != 4) && (this->actor.params != 5)) {
        if (1) {}
        gCtx2 = globalCtx;
        for(i = 0; i < 3; ++i){
          LightContext_RemoveLight(gCtx2, &gCtx2->lightCtx, this->fires[i].light);
        }
        Collider_DestroyCylinder(gCtx2, &this->collider);
    }
} //#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B619B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B619FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61CFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61D74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61F04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B621CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B622E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B623BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B624F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6259C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6275C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B627B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B629E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62A68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62AD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62B10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B631F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B632BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6330C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B633E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B636D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B636E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6382C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6383C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B638AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B638D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63D88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B641E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6467C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64DFC.asm")
