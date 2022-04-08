/*
 * File: z_en_raf.c
 * Overlay: ovl_En_Raf
 * Description: Carnivorous Lilypad
 */

#include "z_en_raf.h"

#define FLAGS (ACTOR_FLAG_8000000)

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A171D8(EnRaf* this, GlobalContext* globalCtx);
void func_80A17464(EnRaf* this, GlobalContext* globalCtx);
void func_80A175E4(EnRaf* this, GlobalContext* globalCtx);
void func_80A178A0(EnRaf* this, GlobalContext* globalCtx);
void func_80A17C6C(EnRaf* this, GlobalContext* globalCtx);
void func_80A17D54(EnRaf* this, GlobalContext* globalCtx);
void func_80A17E1C(EnRaf* this, GlobalContext* globalCtx);
void func_80A180B4(EnRaf* this, GlobalContext* globalCtx);
void func_80A1712C(EnRaf* this);
void func_80A18080(EnRaf* this);

#if 0
const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A18EE0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 50, 10, -10, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A1939C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

#endif

extern ColliderCylinderInit D_80A18EE0;
extern DamageTable D_80A1939C;
extern Vec3f D_80A193BC;

extern AnimationHeader D_06000A64;
extern FlexSkeletonHeader D_06003428;
extern CollisionHeader D_06000108;
extern UNK_TYPE D_060024E0;
extern UNK_TYPE D_060032F8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D6C.s")

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;
    Vec3f sp60 = D_80A193BC;
    s32 i;
    s32 j;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&D_06000108, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80A18EE0);
    this->dyna.actor.targetMode = 3;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06003428, &D_06000A64, this->jointTable, this->morphTable, 12);
    for (i = 0; i < 12; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &sp60);
        Math_Vec3f_Copy(&this->unk_234[i], &sp60);
    }

    this->dyna.actor.colChkInfo.damageTable = &D_80A1939C;
    this->dyna.actor.colChkInfo.health = BREG(1) + 2;
    this->unk_3BE = EN_RAF_GET_F(&this->dyna.actor);
    this->unk_3BA = EN_RAF_GET_1F(&this->dyna.actor);
    this->unk_3C0 = EN_RAF_GET_7F(&this->dyna.actor);
    if (this->unk_3C0 == 0x7F) {
        this->unk_3C0 = -1;
    }

    if (this->unk_3BA == 0x1F) {
        this->unk_3BA = -1;
    } else {
        this->unk_3BA = 0x1E;
    }

    if (((this->unk_3C0 >= 0) || (this->unk_3BE == 1) || (gSaveContext.save.weekEventReg[12] & 1)) &&
        ((Flags_GetSwitch(globalCtx, this->unk_3C0)) || (this->unk_3BE == 1))) {
        for (j = 2; j < 11; j++) {
            Math_Vec3f_Copy(&this->unk_234[j], &gZeroVec3f);
            Math_Vec3f_Copy(&this->unk_2C4[j], &gZeroVec3f);
        }

        func_80A18080(this);
    } else {
        this->unk_3B0 = Rand_ZeroFloat(1.0f) * 20000.0f;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        func_80A1712C(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A1712C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A171D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A175E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A178A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A179C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A180B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A1859C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18DA0.s")
