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

void func_80ACB6A0(ObjAqua *this, GlobalContext *globalCtx);
void func_80ACB7F4(ObjAqua *this, GlobalContext *globalCtx);
void func_80ACBA10(ObjAqua* this);
void func_80ACBD34(ObjAqua* this);

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
Vec3f D_80ACC308 = {1.0f/1000.0f, 7.0f/10000.0f, 1.0f/1000.0f};
Vec3f D_80ACC314 = {8.6f/1000.0f, 8.0f/10000.0f, 8.6f/1000.0f};
Vec3f D_80ACC320 = {1.0f/100.0f, 2.6f/1000.0f, 1.0f/100.0f};

extern Gfx D_0407D590[];

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB6A0.s")
// dropping water on top of waterbox
void func_80ACB6A0(ObjAqua *this, GlobalContext *globalCtx)
{
    s32 pad;
    Vec3f sp58;
    s32 phi_s0;
    s32 i;

    sp58.y = this->actor.world.pos.y + this->actor.yDistToWater;
    phi_s0 = 0;
    for (i = 0; i < 4; i++)
    {
        sp58.x = this->actor.world.pos.x + Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 8.0f;
        sp58.z = this->actor.world.pos.z + Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 8.0f;
        EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 0x78);
        phi_s0 += 0x4000;
    }
    sp58.x = this->actor.world.pos.x;
    sp58.z = this->actor.world.pos.z;
    EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 0x12C);
}


// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB7F4.s")
// dropping water on solid ground
void func_80ACB7F4(ObjAqua *this, GlobalContext *globalCtx)
{
    s32 pad;
    Vec3f sp58;
    s32 phi_s0;
    s32 i;

    sp58.y = this->actor.floorHeight;
    phi_s0 = 0;
    for (i = 0; i < 4; i++)
    {
        sp58.x = (this->actor.world.pos.x + Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 8.0f);
        sp58.z = (this->actor.world.pos.z + Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 8.0f);
        EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 0x78);
        phi_s0 += 0x4000;
    }
    sp58.x = this->actor.world.pos.x;
    sp58.z = this->actor.world.pos.z;
    EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 0x12C);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB940.s")
void func_80ACB940(ObjAqua *this, GlobalContext *globalCtx)
{
    s32 pad;
    Vec3f sp30; //pos
    Vec3f sp24; //velocity

    sp24.x = Rand_ZeroOne() - 0.5f;
    sp24.y = 2.0f;
    sp24.z = Rand_ZeroOne() - 0.5f;
    sp30.x = this->actor.world.pos.x + (sp24.x * 40.0f);
    sp30.y = this->actor.world.pos.y;
    sp30.z = this->actor.world.pos.z + (sp24.z * 40.0f);
    EffectSsIceSmoke_Spawn(globalCtx, &sp30, &sp24, &D_801D15B0, (s32)(Rand_ZeroOne() * 24.0f) + 70);
}


// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA10.s")
void func_80ACBA10(ObjAqua *this)
{
    s32 pad;
    MtxF sp2C;

    func_800C0094(this->actor.floorPoly, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, &sp2C);
    func_8018219C(&sp2C, &this->actor.shape.rot, 0);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA60.s")
//WaterBox_GetSurfaceImpl
//from mzx's bgcheck branch
extern s32 func_800C9EBC(GlobalContext* globalCtx, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
WaterBox** outWaterBox, s32* bgId);
s32 func_80ACBA60(ObjAqua *this, GlobalContext *globalCtx)
{
    s32 pad;
    WaterBox* waterBox;
    f32 ySurface;
    s32 bgId;

    if (func_800C9EBC(
        globalCtx,
        &globalCtx->colCtx,
        this->actor.world.pos.x,
        this->actor.world.pos.z,
        &ySurface, &waterBox, &bgId) && (this->actor.world.pos.y < ySurface))
    {
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Init.s")
void ObjAqua_Init(Actor* thisx, GlobalContext *globalCtx)
{
    ObjAqua* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80ACC2EC);
    this->actor.scale.x = 0.0009f;
    this->actor.scale.y = 0.0005f;
    this->actor.scale.z = 0.0009f;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80ACC2C0);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 60.0f);
    if(0){};
    this->actor.shape.shadowAlpha = 140;
    this->unk_196 = 255;
    if (func_80ACBA60(this, globalCtx))
    {
        for (i = 0; i < 8; i++)
        {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, -4.0f, 4.0f, 4.0f, (Rand_ZeroOne() * 0.09f) + 0.03f);
        }
        func_80ACBDCC(this);
    }
    else
    {
        func_80ACBC70(this);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Destroy.s")
void ObjAqua_Destroy(Actor* thisx, GlobalContext *globalCtx)
{
    ObjAqua* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}


// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC70.s")
void func_80ACBC70(ObjAqua *this)
{
    this->unk_194 = 200;
    this->actionFunc = func_80ACBC8C;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC8C.s")
void func_80ACBC8C(ObjAqua *this, GlobalContext *globalCtx)
{
    if (this->actor.bgCheckFlags & 0x21)
    {
        if (this->actor.bgCheckFlags & 1)
        {
            func_80ACB7F4(this, globalCtx);
            func_80ACBA10(this);
            Audio_PlayActorSound2(&this->actor, 0x2920);
            func_80ACBD34(this);
        }
        else
        {
            func_80ACB6A0(this, globalCtx);
            func_800F0568(globalCtx, &this->actor.world.pos, 0x28, 0x2817);
            Actor_MarkForDeath(&this->actor);
        }
    }
    else if (this->unk_194 <= 0)
    {
        Actor_MarkForDeath(&this->actor);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD34.s")
void func_80ACBD34(ObjAqua* this)
{
    this->actionFunc = func_80ACBD48;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD48.s")
void func_80ACBD48(ObjAqua *this, GlobalContext *globalCtx)
{
    if (((this->actor.params & 1) == 1) && (this->unk_196 >= 91))
    {
        func_80ACB940(this, globalCtx);
    }
    if (this->unk_196 >= 6)
    {
        this->unk_196 -= 5;
    }
    else
    {
        this->unk_196 = 0;
    }
    if (this->actor.shape.shadowAlpha >= 3)
    {
        this->actor.shape.shadowAlpha -= 2;
    }
    else
    {
        Actor_MarkForDeath(&this->actor);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDCC.s")
void func_80ACBDCC(ObjAqua *this)
{
    this->actor.gravity = -0.1f;
    this->unk_194 = 40;
    this->unk_196 = 140;
    this->actionFunc = func_80ACBDFC;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDFC.s")
void func_80ACBDFC(ObjAqua *this, GlobalContext *globalCtx)
{
    f32 temp_f2;
    f32 temp = this->unk_194 * 3.25f;
    
    this->unk_198 += 1000;
    this->actor.shape.shadowAlpha = this->unk_196 = (s32)(temp) + 10;
    if ((this->actor.params & 1) == 1)
    {
        temp_f2 = this->actor.scale.x * 10000.0f;
        EffectSsBubble_Spawn(
            globalCtx,
            &this->actor.world.pos,
            temp_f2 * -0.5f,
            temp_f2,
            temp_f2,
            (Rand_ZeroOne() * 0.1f) + 0.03f);
    }
    if (this->unk_194 <= 0)
    {
        Actor_MarkForDeath(&this->actor);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Update.s")
void ObjAqua_Update(Actor* thisx, GlobalContext *globalCtx)
{
    ObjAqua* this = THIS;
    s32 pad;

    if (this->unk_194 > 0)
    {
        this->unk_194 -= 1;
    }
    this->actionFunc(this, globalCtx);
    if (this->actor.update)
    {
        if (this->actionFunc == func_80ACBC8C)
        {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC308, 0.00006f);
        }
        else if (this->actionFunc == func_80ACBD48)
        {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC314, 0.00095f);
        }
        else
        {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC320, 0.0004f);
        }
        this->actor.velocity.y *= 0.9f;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 4.0f, 0.0f, 5);
        if (this->actionFunc != func_80ACBDFC)
        {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            this->collider.dim.radius = this->actor.scale.x * 3000.0f;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Draw.s")
void ObjAqua_Draw(Actor* thisx, GlobalContext *globalCtx)
{
    ObjAqua* this = THIS;
    s32 framesTemp;
    s32 pad;
    s16 cameraTemp = func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000;
    s32 actionFuncTemp = this->actionFunc == func_80ACBDFC;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    framesTemp = ((globalCtx->gameplayFrames & 0x7FFFFFFF) * -0xA) & 0x1FF;
    if (actionFuncTemp)
    {
        framesTemp = framesTemp >> 1;
    }
    gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx,0,0,0,0x20,0x40,1,0,framesTemp,0x20,0x80));
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 170, 255, 255, this->unk_196);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 150, 255, 0);
    if (actionFuncTemp)
    {
        s16 rotation = Math_SinS(this->unk_198) * 8000.0f;
        SysMatrix_InsertZRotation_s(rotation, 1);
        Matrix_Scale(1.3f, 1.0f, 1.0f, 1);
        SysMatrix_InsertZRotation_s(rotation * -1, 1);
        Matrix_Scale(10.0f/13.0f, 1.0f, 1.0f, 1);
    }
    Matrix_RotateY(cameraTemp, 1);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_0407D590);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
