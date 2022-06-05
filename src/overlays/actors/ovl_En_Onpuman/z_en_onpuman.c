/*
 * File: z_en_onpuman.c
 * Overlay: ovl_En_Onpuman
 * Description: Monkey Instrument Prompt (unused)
 */

#include "z_en_onpuman.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnOnpuman*)thisx)

void EnOnpuman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B121D8(EnOnpuman*, GlobalContext* globalCtx); /* extern */
s32 func_80B11F44(GlobalContext* globalCtx);              /* extern */
void func_80B1202C(EnOnpuman*, GlobalContext* globalCtx); /* extern */
void func_80B1217C(EnOnpuman*, GlobalContext* globalCtx); /* extern */
#if 1
const ActorInit En_Onpuman_InitVars = {
    ACTOR_EN_ONPUMAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOnpuman),
    (ActorFunc)EnOnpuman_Init,
    (ActorFunc)EnOnpuman_Destroy,
    (ActorFunc)EnOnpuman_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B12390 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80B12390;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Init.s")

void EnOnpuman_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnOnpuman* this = (EnOnpuman*)thisx;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    this->actor.flags |= 0x02000000;
    Collider_InitAndSetCylinder(globalCtx, &this->unk254, &this->actor, &D_80B12390);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->unk2A4 = 0;
    this->unk2A0 = 0;
    this->actionFunc = func_80B121D8;
    this->actor.velocity.y = -10.0f;
    this->actor.terminalVelocity = -10.0f;
    this->actor.gravity = -5.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Destroy.s")

void EnOnpuman_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOnpuman* this = (EnOnpuman*)thisx;
    Collider_DestroyCylinder(globalCtx, &this->unk254);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1202C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B121D8.s")
/*
void func_80B121D8(EnOnpuman *arg0, GlobalContext *arg1) {
    s16 temp_v0;
    s16 phi_v1;

    if (func_800B8718(&arg0->actor, &arg1->state) != 0) {
        arg0->actionFunc = func_80B1202C;
        Message_StartTextbox(arg1, 0x8D4U, NULL);
        arg0->unk2A0 = func_80B11F44(arg1);
        return;
    }
    if (Actor_ProcessTalkRequest(&arg0->actor, &arg1->state) != 0) {
        arg0->actionFunc = func_80B1217C;
        return;
    }
    temp_v0 = arg0->actor.yawTowardsPlayer - arg0->actor.shape.rot.y;
    if (arg0->actor.xzDistToPlayer < 200.0f) {
        phi_v1 = temp_v0;
        if (temp_v0 < 0) {
            phi_v1 = -temp_v0;
        }
        if (phi_v1 < 0x4301) {
            arg0->actor.textId = 0x8D3;
            func_800B8614(&arg0->actor, arg1, 100.0f);
            func_800B874C(&arg0->actor, arg1, 100.0f, 100.0f);
        }
    }
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Update.s")
