#include "z_en_peehat.h"

#define FLAGS 0x00000015

#define THIS ((EnPeehat*)thisx)

void EnPeehat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Peehat_InitVars = {
    ACTOR_EN_PEEHAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PH,
    sizeof(EnPeehat),
    (ActorFunc)EnPeehat_Init,
    (ActorFunc)EnPeehat_Destroy,
    (ActorFunc)EnPeehat_Update,
    (ActorFunc)EnPeehat_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80899430 = {
    { COLTYPE_WOOD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 50, 120, -20, { 0, 0, 0 } },
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_8089945C = {
    { COLTYPE_HIT6, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 40 }, 100 },
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80899488[2] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80899500 = {
    { COLTYPE_METAL, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    2, D_80899488, // sTrisElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_80899510 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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
static CollisionCheckInfoInit2 D_80899530 = { 15, 50, 120, -20, MASS_HEAVY };


// sColChkInfoInit
static CollisionCheckInfoInit2 D_8089953C = { 1, 20, 15, -5, 30 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80899548[] = {
    ICHAIN_F32(uncullZoneForward, 4200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 700, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80899430;
extern ColliderSphereInit D_8089945C;
extern ColliderTrisElementInit D_80899488[2];
extern ColliderTrisInit D_80899500;
extern DamageTable D_80899510;
extern CollisionCheckInfoInit2 D_80899530;
extern CollisionCheckInfoInit2 D_8089953C;
extern InitChainEntry D_80899548[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808971DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808976DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897F44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808982E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808984E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898654.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808986A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_8089874C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80899024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Draw.asm")
