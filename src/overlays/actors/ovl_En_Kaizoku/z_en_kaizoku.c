#include "z_en_kaizoku.h"

#define FLAGS 0x00100015

#define THIS ((EnKaizoku*)thisx)

void EnKaizoku_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Update(Actor* thisx, GlobalContext* globalCtx);

#if(0)
// static DamageTable sDamageTable = {
static DamageTable D_80B8AB3C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};


const ActorInit En_Kaizoku_InitVars = {
    ACTOR_EN_KAIZOKU,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_KZ,
    sizeof(EnKaizoku),
    (ActorFunc)EnKaizoku_Init,
    (ActorFunc)EnKaizoku_Destroy,
    (ActorFunc)EnKaizoku_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B8AB7C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 50, 0, { 0, 0, 0 } },
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B8ABA8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK4, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


extern DamageTable D_80B8AB3C;
extern ColliderCylinderInit D_80B8AB7C;
extern ColliderQuadInit D_80B8ABA8;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B868B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B872A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B872F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B874D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8760C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8798C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87C7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87CF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87FDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8833C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B887AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B891B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B89280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B893CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B894C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8960C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8971C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B89A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A718.asm")
