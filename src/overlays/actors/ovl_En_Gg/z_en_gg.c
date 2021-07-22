#include "z_en_gg.h"

#define FLAGS 0x00000089

#define THIS ((EnGg*)thisx)

void EnGg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Gg_InitVars = {
    ACTOR_EN_GG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GG,
    sizeof(EnGg),
    (ActorFunc)EnGg_Init,
    (ActorFunc)EnGg_Destroy,
    (ActorFunc)EnGg_Update,
    (ActorFunc)EnGg_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B36C00 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 24, 72, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B36C2C = { 0, 24, 72, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80B36C38 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


extern ColliderCylinderInit D_80B36C00;
extern CollisionCheckInfoInit2 D_80B36C2C;
extern DamageTable D_80B36C38;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B34F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B34FB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B351A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B352A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3556C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B357F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3584C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B358D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B359DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35B24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3610C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B363E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B364D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B368B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B368F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Draw.asm")
