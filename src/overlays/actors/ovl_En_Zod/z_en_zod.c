/*
 * File: z_en_zod.c
 * Overlay: ovl_En_Zod
 * Description: Zora Drummer Tijo
 */

#include "z_en_zod.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, PlayState* play);
void EnZod_Destroy(Actor* thisx, PlayState* play);
void EnZod_Update(Actor* thisx, PlayState* play);
void EnZod_Draw(Actor* thisx, PlayState* play);

void func_80BAF338(EnZod* this, u32 arg1, u32 arg2, u16 arg3);
void func_80BAF99C(EnZod* this, PlayState* play); /* extern */
void func_80BAFB84(EnZod* this, PlayState* play); /* extern */
void func_80BAFDB4(EnZod* this, PlayState* play); /* extern */
void func_80BAFF14(EnZod* this, PlayState* play);

#if 0
const ActorInit En_Zod_InitVars = {
    ACTOR_EN_ZOD,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOD,
    sizeof(EnZod),
    (ActorFunc)EnZod_Init,
    (ActorFunc)EnZod_Destroy,
    (ActorFunc)EnZod_Update,
    (ActorFunc)EnZod_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB0540 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 60, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BB0540;
extern FlexSkeletonHeader D_0600D658;

extern UNK_TYPE D_06000D94;
extern UNK_TYPE D_06007650;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Init.s")
/*
void EnZod_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    struct EnZod* temp_v0_3;
    EnZod* this = THIS;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 60.0f);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600D658, (AnimationHeader*)&D_06000D94, &this->morphTable,
                       &this->JointTable, 0xA);
    Animation_PlayLoop(&this->skelAnime, (AnimationHeader*)&D_06000D94);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &D_80BB0540);
    this->unk260 = 0;
    this->unk266 = 0x12C;
    this->unk25E = this->unk260;
    this->unk25C = this->unk260;
    this->unk256 = 0;
    this->unk25A = -1;
    this->unk258 = -1;
    this->actor.textId = 0;
    this->unk298 = 0;
    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -4.0f;
    this->unk264 = this->unk266;
    this->unk262 = this->unk266;
    temp_v0_3 = this + (2 * 4);
    this->unk280 = 0.01f;
    this->unk284 = 0.01f;
    this->unk26C = 0.0f;
    this->unk268 = 0.0f;
    temp_v0_3->unk28C = 0.01f;
    temp_v0_3->unk274 = 0.0f;
    temp_v0_3->unk288 = 0.01f;
    temp_v0_3->unk270 = 0.0f;
    temp_v0_3->unk284 = 0.01f;
    temp_v0_3->unk26C = 0.0f;
    temp_v0_3->unk268 = 0.0f;
    temp_v0_3->unk280 = 0.01f;
    func_80BAF338(this, 3, 2, -1);
    this->actionFunc = func_80BAF99C;
    switch (this->actor.params & 0xF) {
        case 1:
            if ((gSaveContext.save.weekEventReg[0x4E] & 1) != 0) {
                this->actionFunc = func_80BAFDB4;
                func_80BAF338(this, 0, 2, -1);
                this->actor.flags |= 0x10;
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);
                return;
            }
            this->actionFunc = func_80BAFB84;
            if ((gSaveContext.save.weekEventReg[0x37] & 0x80) == 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            return;
        case 2:
            this->actionFunc = func_80BAFF14;
            this->unk29A = -1;
            this->unk256 |= 2;
            return;
        default:
            if ((gSaveContext.save.weekEventReg[0x37] & 0x80) != 0) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= 0x10;
            break;
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Destroy.s")

void EnZod_Destroy(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF1EC.s")

void func_80BAF1EC(EnZod* this, PlayState* play) {
    u16 phi_a3;
    if (gSaveContext.save.playerForm != 2) {
        phi_a3 = 0x1227;
        if ((gSaveContext.save.weekEventReg[0x20] & 8) != 0) {
            phi_a3 = 0x1229;
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 8;
        }
    } else if ((this->unk256 & 1) != 0) {
        phi_a3 = 0x1225;
    } else {
        phi_a3 = 0x1219;
        if ((gSaveContext.save.weekEventReg[0x20] & 0x10) != 0) {
            phi_a3 = 0x1226;
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 0x10;
        }
        this->unk256 |= 1;
    }
    func_80BAF338(this, 0, 2, phi_a3);
    Message_StartTextbox(play, phi_a3, &this->actor);
}



#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF4D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFB84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFD00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFDB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB01B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Draw.s")
