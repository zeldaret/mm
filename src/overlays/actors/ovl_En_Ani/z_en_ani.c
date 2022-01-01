/*
 * File: z_en_ani.c
 * Overlay: ovl_En_Ani
 * Description: Part-time worker
 */

#include "z_en_ani.h"

#define FLAGS 0x00000009

#define THIS ((EnAni*)thisx)

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809679D0(EnAni* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ani_InitVars = {
    ACTOR_EN_ANI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80968670 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8096869C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 850, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80968670;
extern InitChainEntry D_8096869C[];

extern UNK_TYPE D_06000C14;
extern UNK_TYPE D_060011CC;
extern UNK_TYPE D_060027A0;
extern UNK_TYPE D_06009220;
extern AnimationHeader D_06009D34;

void func_80967AB4(void *arg0);                       /* static */
void func_80967DA0(EnAni *this, GlobalContext *arg1); /* static */
void func_80967E34(Actor *this, GlobalContext *arg1); /* static */
void func_80968164(EnAni *this, GlobalContext *arg1); /* static */
extern AnimationHeader D_060007FC;
extern AnimationHeader D_06001D48;
extern FlexSkeletonHeader D_060028A0;
extern Vec3f D_809686A4;
extern UNK_TYPE D_809686B0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_809679D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967AB4.s")

void EnAni_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnAni *this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, D_8096869C);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->unk1DC, &D_060028A0, (AnimationHeader *) &D_06009D34, &this->unk220, &this->unk280, 0x10);
    Animation_PlayOnce(&this->unk1DC, (AnimationHeader *) &D_06009D34);
    Collider_InitAndSetCylinder(globalCtx, &this->unk144, &this->actor, &D_80968670);
    Collider_InitAndSetCylinder(globalCtx, &this->unk190, &this->actor, &D_80968670);
    Collider_UpdateCylinder(&this->actor, &this->unk190);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk2EC = 0;
    this->unk2EE = 0;
    this->unk2F0 = 0;
    this->actionFunc = func_809679D0;
    if ((this->actor.params & 0xFF) == 1) {
        Animation_Change(&this->unk1DC, &D_06001D48, 1.0f, 0.0f, 
              Animation_GetLastFrame(&D_06001D48), 2, 0.0f);
        this->unk2FC = func_80968164;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
        this->actor.flags |= 0x10;
        this->unk2EC |= 4;
        gSaveContext.eventInf[1] &= 0xEF;
    }else {
        this->unk190.dim.radius = 0x3C;
        this->unk2FC = func_80967DA0;
        this->actor.velocity.y = -25.0f;
        this->actor.minVelocityY = -25.0f;
        this->actor.gravity = -5.0f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_809680B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80968164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80968504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_8096854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Draw.s")
