/*
 * File: z_en_snowman.c
 * Overlay: ovl_En_Snowman
 * Description: Enos
 */

#include "z_en_snowman.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnSnowman*)thisx)

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B1746C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B178B8(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17A58(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17D78(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17EFC(EnSnowman* this, GlobalContext* globalCtx);
void func_80B17FE0(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18124(EnSnowman* this, GlobalContext* globalCtx);
void func_80B183A4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B1848C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B1861C(EnSnowman* this, GlobalContext* globalCtx);
void func_80B189C4(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18A04(EnSnowman* this, GlobalContext* globalCtx);
void func_80B18C7C(EnSnowman* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Snowman_InitVars = {
    ACTOR_EN_SNOWMAN,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SNOWMAN,
    sizeof(EnSnowman),
    (ActorFunc)EnSnowman_Init,
    (ActorFunc)EnSnowman_Destroy,
    (ActorFunc)EnSnowman_Update,
    (ActorFunc)EnSnowman_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B19A00 = {
    { COLTYPE_HIT4, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 60, 80, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B19A2C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 60, 80, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B19A58 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
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
static CollisionCheckInfoInit D_80B19A78 = { 2, 60, 80, 150 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B19AAC[] = {
    ICHAIN_S8(hintId, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B19A00;
extern ColliderCylinderInit D_80B19A2C;
extern DamageTable D_80B19A58;
extern CollisionCheckInfoInit D_80B19A78;
extern InitChainEntry D_80B19AAC[];

extern UNK_TYPE D_06000404;
extern UNK_TYPE D_06004628;
extern UNK_TYPE D_060046D8;
extern UNK_TYPE D_06004F14;
extern UNK_TYPE D_0600554C;
extern UNK_TYPE D_060058CC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B16FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B173D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1746C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B177EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B178B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B179D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B180A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1848C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1861C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B189C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B189D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19998.s")
