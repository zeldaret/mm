/*
 * File: z_en_slime.c
 * Overlay: ovl_En_Slime
 * Description: Chuchu
 */

#include "z_en_slime.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnSlime*)thisx)

void EnSlime_Init(Actor* thisx, PlayState* play);
void EnSlime_Destroy(Actor* thisx, PlayState* play);
void EnSlime_Update(Actor* thisx, PlayState* play);
void EnSlime_Draw(Actor* thisx, PlayState* play);

void func_80A2F110(EnSlime* this);
void func_80A2F140(EnSlime* this, PlayState* play); //Default action func
void func_80A2F180(EnSlime* this);    

void func_80A2F1A4(EnSlime* this, PlayState* play);
void func_80A2F418(EnSlime* this, PlayState* play);
void func_80A2F6CC(EnSlime* this, PlayState* play);
void func_80A2F8E0(EnSlime* this, PlayState* play);
void func_80A2FA88(EnSlime* this, PlayState* play);
void func_80A2FBA0(EnSlime* this, PlayState* play);
void func_80A2FE38(EnSlime* this, PlayState* play);
void func_80A30344(EnSlime* this, PlayState* play); //Action func
void func_80A304B8(EnSlime* this, PlayState* play);
void func_80A30820(EnSlime* this, PlayState* play);
void func_80A30944(EnSlime* this, PlayState* play);
void func_80A30A20(EnSlime* this, PlayState* play);
void func_80A30AE4(EnSlime* this, PlayState* play);
void func_80A30C2C(EnSlime* this, PlayState* play);
void func_80A30CEC(EnSlime* this, PlayState* play); //Action func

#if 0
const ActorInit En_Slime_InitVars = {
    ACTOR_EN_SLIME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SLIME,
    sizeof(EnSlime),
    (ActorFunc)EnSlime_Init,
    (ActorFunc)EnSlime_Destroy,
    (ActorFunc)EnSlime_Update,
    (ActorFunc)EnSlime_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A31AF0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 22, 35, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A31B1C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80A31B3C = { 1, 22, 35, 60 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A31B54[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

#endif


extern u8 D_0405BEF0[];
extern u8 D_0405E6F0[];
extern u8 D_0405FFC0[];
extern void* D_80A31B44[];
extern s32 D_80A31B5C;
extern void* D_80A32200;

extern u8 D_0405F6F0[];
extern u8 D_06000650[];
extern u8 D_06000A10[];

extern ColliderCylinderInit D_80A31AF0;
extern DamageTable D_80A31B1C;
extern CollisionCheckInfoInit D_80A31B3C;
extern InitChainEntry D_80A31B54[];

extern Color_RGBA8 D_80A31B74[];
extern Color_RGBA8 D_80A31B84[];
extern Vec3f D_80A31B94[];

extern UNK_TYPE D_060004C0;
extern UNK_TYPE D_06000828;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Init.s")
void EnSlime_Init(Actor* thisx, PlayState* play) {
    s32 actorParamsHi;
    s32 i;
    EnSlime* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80A31B54);
    Collider_InitAndSetCylinder(play, &this->unk1BC, &this->actor, &D_80A31AF0);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80A31B1C, &D_80A31B3C);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 38.0f);

    this->unk148 = 0xFF;
    this->unk149 = 0;
    this->unk158 = 0.0f;

    if (this->actor.shape.rot.x <= 0) {
        this->unk170 = 30000.0f;
    } else {
        this->unk170 = (f32)this->actor.shape.rot.x * 40.0f;
    }

    this->actor.shape.rot.x = 0;
    actorParamsHi = (this->actor.params >> 8) & 0xFF;
    this->actor.shape.rot.z = 0;
    this->actor.params = this->actor.params & 0xFF;
    if (actorParamsHi == 0xFF) {
        actorParamsHi = 0;
    }

    this->unk152 = (actorParamsHi * 0x14) + 0xC8;

    if (!D_80A31B5C) {
        for (i = 0; i < 4; i++) {
            D_80A31B44[i] = Lib_SegmentedToVirtual(D_80A31B44[i]);
        }
        D_80A32200 = Lib_SegmentedToVirtual(&D_06000828);
        D_80A31B5C = 1;
    }

    if (this->actor.params == 2) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405BEF0);
        this->actor.hintId = 0x22;
    } else if (this->actor.params == 1) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405FFC0);
        this->actor.hintId = 0x5D;
    } else if (this->actor.params == 3) {
        this->unk160 = Lib_SegmentedToVirtual(&D_0405E6F0);
        this->actor.hintId = 5;
    } else {
        this->actor.hintId = 6;
    }

    func_80A2F110(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Destroy.s")
void EnSlime_Destroy(Actor* thisx, PlayState* play) {
    EnSlime* this = THIS;
    Collider_DestroyCylinder(play, &this->unk1BC);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2EFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F0A8.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F110.s")
void func_80A2F110(EnSlime* this) {
    this->actor.scale.x = 0.008f;
    this->actor.scale.z = 0.008f;
    this->actor.scale.y = 0.011f;
    this->actionFunc = func_80A2F140;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F140.s")
void func_80A2F140(EnSlime* this, PlayState* play) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.flags &= ~0x10;
        func_80A2F180(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F180.s")
void func_80A2F180(EnSlime* this) {
    this->unk14C = 0x19;
    this->actionFunc = func_80A2F1A4;
    this->actor.speedXZ = 0.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F1A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F9A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FD94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A304B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A3072C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A309C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30C2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Update.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Draw.s")
void EnSlime_Draw(Actor* thisx, PlayState* play) {
    s32 i;
    EnSlime* this = THIS;
    Vec3f vec3f;
    Color_RGBA8* color1;
    Color_RGBA8* color2;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    func_800B8118(&this->actor, play, 0);
    if (this->unk148 != 0xFF) {
        gSPSegment(POLY_XLU_DISP++, 0x0A, (u32)D_801AEFA0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetEnvColor(POLY_XLU_DISP++, 0x96, 0xFF, 0xFF, this->unk148);
    } else {
        color1 = &D_80A31B74[this->actor.params];
        color2 = &D_80A31B84[this->actor.params];
        AnimatedMat_Draw(play, (AnimatedMaterial*)D_80A32200);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x64, color1->r, color1->g, color1->b, color1->a);
        gDPSetEnvColor(POLY_XLU_DISP++, color2->r, color2->g, color2->b, 0xFF);
    }

    if (this->actionFunc == func_80A30344) {
        vec3f.x = 1.0f - (sin_rad((f32)this->unk14C * 1.5707964f) * 0.3f);
        vec3f.y = (sin_rad((f32)this->unk14C * 1.5707964f) * 0.3f) + 1.0f;
        vec3f.z = 1.0f - (cos_rad((f32)this->unk14C * 1.5707964f) * 0.3f);

        Matrix_RotateXFApply(this->unk154);
        Matrix_RotateZF(this->unk15C, MTXMODE_APPLY);
        Matrix_Scale(vec3f.x, vec3f.y, vec3f.z, MTXMODE_APPLY);
        Matrix_RotateZF(-this->unk15C, MTXMODE_APPLY);
        Matrix_RotateXFApply(-this->unk154);
    }

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, (u32)&D_060004C0);

    if (this->unk148 == 0xFF) {
        Scene_SetRenderModeXlu(play, 0, 1U);

        gSPSegment(POLY_OPA_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x1E, 0x46, 0xFF);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, (u32)&D_06000650);

    } else {
        Scene_SetRenderModeXlu(play, 1, 2U);
        gSPSegment(POLY_XLU_DISP++, 0x09, (u32)D_80A31B44[(u8)this->unk149]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, (u32)&D_06000650);
    }

    for (i = 0; i < 5; i++) {
        Matrix_MultVec3f(&D_80A31B94[i], &this->unk180[i]);
    }

    if (this->actionFunc == func_80A30CEC) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk150, MTXMODE_APPLY);
        Matrix_Scale(this->unk174, this->unk178, this->unk17C, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, (u32)&D_06000A10);
    }

    if ((this->actor.params != 0) && (this->actor.scale.x > 0.0f)) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (2000.0f * this->actor.scale.y),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(0.03f, 0.03f, 0.03f, MTXMODE_APPLY);

        gSPSegment(POLY_OPA_DISP++, 0x08, (u32)this->unk160);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, (u32)&D_0405F6F0);
    }

    Actor_DrawDamageEffects(play, &this->actor, &this->unk180, 5, this->unk168, this->unk16C, this->unk164,
                            (u8)(s32)this->unk14A);

    CLOSE_DISPS(play->state.gfxCtx);
}
