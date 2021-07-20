#include "z_obj_kendo_kanban.h"

#define FLAGS 0x00000000

#define THIS ((ObjKendoKanban*)thisx)

void ObjKendoKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Obj_Kendo_Kanban_InitVars = {
    ACTOR_OBJ_KENDO_KANBAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjKendoKanban),
    (ActorFunc)ObjKendoKanban_Init,
    (ActorFunc)ObjKendoKanban_Destroy,
    (ActorFunc)ObjKendoKanban_Update,
    (ActorFunc)ObjKendoKanban_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80B6673C[2] = {
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -300.0f, 850.0f, 40.0f }, { -300.0f, 10.0f, 40.0f }, { 300.0f, 850.0f, 40.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 300.0f, 850.0f, 40.0f }, { 300.0f, 10.0f, 40.0f }, { -300.0f, 10.0f, 40.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B667B4 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    2, D_80B6673C, // sTrisElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B667C4 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 33, 80, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80B667F0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
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
static CollisionCheckInfoInit2 D_80B66810 = { 8, 0, 0, 0, MASS_HEAVY };

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/ObjKendoKanban_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/ObjKendoKanban_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B658A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65D68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B65DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B6618C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/func_80B66304.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/ObjKendoKanban_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban_0x80B654C0/ObjKendoKanban_Draw.asm")
