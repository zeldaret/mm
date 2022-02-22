/*
 * File: z_obj_dora.c
 * Overlay: ovl_Obj_Dora
 * Description: Swordsman's School - Gong
 */

#include "z_obj_dora.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDora*)thisx)

void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Dora_InitVars = {
    ACTOR_OBJ_DORA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjDora),
    (ActorFunc)ObjDora_Init,
    (ActorFunc)ObjDora_Destroy,
    (ActorFunc)ObjDora_Update,
    (ActorFunc)ObjDora_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[6] = {
static ColliderTrisElementInit D_80B61310[6] = {
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x00100000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, -35.0f, 0.0f }, { 260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x00100000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 260.0f, -185.0f, 0.0f }, { 260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 260.0f, -485.0f, 0.0f }, { 0.0f, -635.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, -635.0f, 0.0f }, { -260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -260.0f, -485.0f, 0.0f }, { -260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -260.0f, -185.0f, 0.0f }, { 0.0f, -35.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B61478 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_TRIS, },
    6, D_80B61310, // sTrisElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B61488 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B614A8 = { 8, 0, 0, 0, MASS_HEAVY };

#endif

extern ColliderTrisElementInit D_80B61310[6];
extern ColliderTrisInit D_80B61478;
extern DamageTable D_80B61488;
extern CollisionCheckInfoInit2 D_80B614A8;

extern UNK_TYPE D_06004160;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Draw.s")
