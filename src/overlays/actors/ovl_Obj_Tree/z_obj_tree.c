#include "z_obj_tree.h"

#define FLAGS 0x02000000

#define THIS ((ObjTree*)thisx)

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Tree_InitVars = {
    ACTOR_OBJ_TREE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TREE,
    sizeof(ObjTree),
    (ActorFunc)ObjTree_Init,
    (ActorFunc)ObjTree_Destroy,
    (ActorFunc)ObjTree_Update,
    (ActorFunc)ObjTree_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B9A570 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x0100020A, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 28, 120, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B9A59C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B9A5BC = { 8, 0, 0, 0, MASS_HEAVY };

#endif

extern ColliderCylinderInit D_80B9A570;
extern DamageTable D_80B9A59C;
extern CollisionCheckInfoInit2 D_80B9A5BC;

extern UNK_TYPE D_06000680;
extern UNK_TYPE D_06001B2C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A20C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Draw.s")
