/*
 * File: z_en_osn.c
 * Overlay: ovl_En_Osn
 * Description: Happy Mask Salesman
 */

#include "z_en_osn.h"

#define FLAGS 0x00000019

#define THIS ((EnOsn*)thisx)

void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Osn_InitVars = {
    ACTOR_EN_OSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OSN,
    sizeof(EnOsn),
    (ActorFunc)EnOsn_Init,
    (ActorFunc)EnOsn_Destroy,
    (ActorFunc)EnOsn_Update,
    (ActorFunc)EnOsn_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AD2518 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AD2544 = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80AD2550 = {
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AD2570[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AD2518;
extern CollisionCheckInfoInit2 D_80AD2544;
extern DamageTable D_80AD2550;
extern InitChainEntry D_80AD2570[];

extern UNK_TYPE D_060192A0;
extern UNK_TYPE D_060201BC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD08B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD10FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD144C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD14C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD16A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD19A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1A4C.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Init.s")
void func_80AD1398(EnOsn*, GlobalContext*);            /* extern */
void func_80AD144C(EnOsn*, GlobalContext*);            /* extern */
void func_80AD1634(EnOsn*, GlobalContext*);         /* extern */
void func_80AD16A8(EnOsn*, GlobalContext*);         /* extern */
void func_80AD1A4C(EnOsn*, GlobalContext*);         /* extern */
extern FlexSkeletonHeader D_060202F0;
extern ActorAnimationEntry D_80AD22C0;

void EnOsn_Init(Actor *thisx, GlobalContext *globalCtx)
{
  s32 pad;
  EnOsn *this = (EnOsn *) thisx;

  Actor_ProcessInitChain(&this->actor, D_80AD2570);
  ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
  SkelAnime_InitFlex(globalCtx, &this->anime, &D_060202F0, (AnimationHeader *) (&D_060201BC), 0, 0, 0);
  Collider_InitCylinder(globalCtx, &this->collider);
  Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80AD2518);
  CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80AD2550, &D_80AD2544);
  this->unk_1D8[0x24] = -1;
  switch (this->actor.params & 3)
  {
    case 0:
      if (((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC030)) || (gSaveContext.entranceIndex == 0xC060))
    {
      this->unk_1EA = (u16) (this->unk_1EA | 1);
    }
      this->unk_1D8[0x18] = 1;
      if (globalCtx->sceneNum == 0x63)
    {
      if ((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC060))
      {
        this->actionFunc = func_80AD16A8;
        return;
      }
      if (gSaveContext.entranceIndex == 0xC030)
      {
        func_80AD1398(this, globalCtx);
        this->actionFunc = func_80AD1634;
        return;
      }
      func_80AD144C(this, globalCtx);
      return;
    }
      func_80AD144C(this, globalCtx);
      return;

    case 1:
      this->unk_1D8[0x14] = 0xF;
      func_800BDC5C(&this->anime, (ActorAnimationEntry *) (&D_80AD22C0), this->unk_1D8[0x14]);
      this->actionFunc = func_80AD1A4C;
      return;

    case 2:
      this->unk_1D8[0x14] = 0x10;
      func_800BDC5C(&this->anime, (ActorAnimationEntry *) (&D_80AD22C0), this->unk_1D8[0x14]);
      this->actionFunc = func_80AD1A4C;
      return;

    case 3:
      this->actor.flags &= -2;
      this->actionFunc = func_80AD16A8;
      return;

    default:
      Actor_MarkForDeath(&this->actor);
      return;

  }

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Draw.s")
