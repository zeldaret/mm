/*
 * File: z_obj_aqua.c
 * Overlay: ovl_Obj_Aqua
 * Description: Water poured out of a bottle
 */

#include "z_obj_aqua.h"

#define FLAGS 0x00000010

#define THIS ((ObjAqua*)thisx)

void ObjAqua_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80ACBA60(ObjAqua* this, GlobalContext* globalCtx);
void func_80ACBC70(ObjAqua* this);
void func_80ACBDCC(ObjAqua* this);

void func_80ACBC8C(ObjAqua* this, GlobalContext* globalCtx);
void func_80ACBD48(ObjAqua* this, GlobalContext* globalCtx);
void func_80ACBDFC(ObjAqua* this, GlobalContext* globalCtx);

const ActorInit Obj_Aqua_InitVars = {
    ACTOR_OBJ_AQUA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjAqua),
    (ActorFunc)ObjAqua_Init,
    (ActorFunc)ObjAqua_Destroy,
    (ActorFunc)ObjAqua_Update,
    (ActorFunc)ObjAqua_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ACC2C0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { 6, 10, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ACC2EC[] = {
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(world.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -900, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

s32 D_80ACC308[] = {0x3A83126F, 0x3A378034, 0x3A83126F};
s32 D_80ACC314[] = {0x3C0CE704, 0x3A51B717, 0x3C0CE704};
s32 D_80ACC320[] = {0x3C23D70A, 0x3B2A64C3, 0x3C23D70A};

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB6A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA60.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Init.s")
void ObjAqua_Init(Actor* thisx, GlobalContext *globalCtx)
{
    ObjAqua* this = THIS;
    s32 phi_s0;

    Actor_ProcessInitChain(&this->actor, D_80ACC2EC);
    this->actor.scale.x = 0.0009f;
    this->actor.scale.z = 0.0009f;
    this->actor.scale.y = 0.0005f;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80ACC2C0);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 60.0f);
    this->actor.shape.shadowAlpha = 140;
    this->unk_196 = 0xFF;
    phi_s0 = 0;
    if (func_80ACBA60(this, globalCtx))
    {
        while (phi_s0 != 8)
        {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, -4.0f, 4.0f, 4.0f, (Rand_ZeroOne() * 0.09f) + 0.03f);
            phi_s0++;
        } 
        func_80ACBDCC(this);
    }
    else
    {
        func_80ACBC70(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Draw.s")
