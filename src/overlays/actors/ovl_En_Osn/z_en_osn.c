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

void func_80AD1634(EnOsn*, GlobalContext*); /* extern */
void func_80AD16A8(EnOsn*, GlobalContext*); /* extern */
void EnOsn_Idle(EnOsn*, GlobalContext*);    /* extern */
void func_80AD0998(EnOsn*);                 /* extern */
void func_80AD0A24(EnOsn*);                 /* extern */
void func_80AD0AB0(EnOsn*);                 /* extern */

extern FlexSkeletonHeader D_060202F0;
extern ActorAnimationEntry D_80AD22C0;
extern ColliderCylinderInit D_80AD2518;
extern CollisionCheckInfoInit2 D_80AD2544;
extern DamageTable D_80AD2550;
extern InitChainEntry D_80AD2570[];

extern UNK_TYPE D_060192A0;
extern UNK_TYPE D_060201BC;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0830.s")

void func_80AD0830(EnOsn* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD08B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0A24.s")

/*void func_80AD0A24(EnOsn *this)
{
  s16 sp1E;
  int new_var;
  sp1E = (s16) this->anime.curFrame;
  new_var = Animation_GetLastFrame((ActorAnimationEntry*)(D_80AD22C0).animation);
  if ((this->unk_1EC[0] == 0x15) && (sp1E == new_var))
  {
    this->unk_1EC[0] = 0x16U;
    sp1E = 0x16;
    func_800BDC5C(&this->anime, (ActorAnimationEntry *) (&D_80AD22C0), sp1E);
  }
}*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD10FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD144C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD14C8.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1634.s")
void func_80AD1634(EnOsn* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->actionFunc = func_80AD16A8;
        return;
    }
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    }
    ActorCutscene_SetIntentToPlay(this->cutscene);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD16A8.s")
void func_80AD16A8(EnOsn* this, GlobalContext* globalCtx) {
    u8 temp_v0_2;
    u32 temp_v0;

    if (func_800EE29C(globalCtx, 0x82U)) {
        temp_v0 = func_800EE200(globalCtx, 0x82);
        this->unk_1F0[0] = 0;
        if (this->unk_1ED != globalCtx->csCtx.npcActions[temp_v0]->unk0) {
            this->unk_1ED = globalCtx->csCtx.npcActions[temp_v0]->unk0;
            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
                case 1:
                    this->unk_1EC = 2;
                    break;
                case 2:
                    this->unk_1EC = 1;
                    break;
                case 3:
                    this->unk_1EC = 7;
                    break;
                case 4:
                    this->unk_1EC = 3;
                    break;
                case 5:
                    this->unk_1EC = 6;
                    break;
                case 6:
                    this->unk_1EC = 5;
                    break;
                case 7:
                    this->unk_1EC = 4;
                    break;
                case 8:
                    this->unk_1EC = 0;
                    break;
                case 10:
                    this->unk_1EC = 8;
                    break;
                case 11:
                    this->unk_1EC = 9;
                    break;
                case 13:
                    this->unk_1EC = 0xA;
                    break;
                case 15:
                    this->unk_1EC = 0xB;
                    break;
                case 16:
                    this->unk_1EC = 0xC;
                    break;
                case 17:
                    this->unk_1EC = 0xD;
                    break;
                case 18:
                    this->unk_1EC = 0xE;
                    break;
                case 19:
                    this->unk_1EC = 0x11;
                    break;
                case 20:
                    this->unk_1EC = 0x12;
                    break;
                case 21:
                    this->unk_1EC = 0x14;
                    break;
                case 22:
                    this->unk_1EC = 0x15;
                    break;
                case 23:
                    this->unk_1EC = 0x17;
                    break;
                case 24:
                    this->unk_1EC = 0x18;
                    break;
                default:
                    this->unk_1EC = 0;
                    break;
            }
            func_800BDC5C(&this->anime, (ActorAnimationEntry*)&D_80AD22C0, this->unk_1EC);
        }

        if ((this->unk_1EC == 5) && (globalCtx->sceneNum == 8) && (gSaveContext.sceneSetupIndex == 0xB) &&
            (globalCtx->csCtx.frames == 0x190)) {
            Audio_PlayActorSound2(&this->actor, 0x697DU);
        }
        if (this->unk_1EC == 0x12) {
            func_80AD0998(this);
        }
        if (this->unk_1EC == 0x15) {
            func_80AD0A24(this);
        }
        if (this->unk_1EC == 0x18) {
            func_80AD0AB0(this);
        }
        if ((this->unk_1EC == 0x14) &&
            (((Animation_OnFrame(&this->anime, 17.0f) != 0)) || (Animation_OnFrame(&this->anime, 27.0f) != 0) ||
             (Animation_OnFrame(&this->anime, 37.0f) != 0) || (Animation_OnFrame(&this->anime, 47.0f) != 0) ||
             (Animation_OnFrame(&this->anime, 57.0f) != 0) || (Animation_OnFrame(&this->anime, 67.0f) != 0))) {
            Audio_PlayActorSound2(&this->actor, 0x29B3U);
        }
        func_800EDF24(&this->actor, globalCtx, temp_v0);
        return;
    }
    this->unk_1F0[0] = 1;
    this->unk_1ED = 0x63;
    func_80AD144C(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD19A0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Idle.s")
void EnOsn_Idle(EnOsn* this, GlobalContext* globalCtx) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Init.s")
void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOsn* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80AD2570);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->anime, &D_060202F0, (AnimationHeader*)(&D_060201BC), 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80AD2518);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80AD2550, &D_80AD2544);
    this->unk_1D8[0x24] = -1;
    switch (this->actor.params & 3) {
        case 0:
            if (((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC030)) ||
                (gSaveContext.entranceIndex == 0xC060)) {
                this->unk_1EA = (u16)(this->unk_1EA | 1);
            }
            this->unk_1D8[0x18] = 1;
            if (globalCtx->sceneNum == 0x63) {
                if ((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC060)) {
                    this->actionFunc = func_80AD16A8;
                    return;
                }
                if (gSaveContext.entranceIndex == 0xC030) {
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
            func_800BDC5C(&this->anime, (ActorAnimationEntry*)(&D_80AD22C0), this->unk_1D8[0x14]);
            this->actionFunc = EnOsn_Idle;
            return;

        case 2:
            this->unk_1D8[0x14] = 0x10;
            func_800BDC5C(&this->anime, (ActorAnimationEntry*)(&D_80AD22C0), this->unk_1D8[0x14]);
            this->actionFunc = EnOsn_Idle;
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

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Destroy.s")
void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOsn* this = THIS;

    SkelAnime_Free(&this->anime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Update.s")
void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    u32 pad1;
    u16 pad2;
    u32 sp34;
    EnOsn* this = THIS;

    sp34 = Flags_GetSwitch(globalCtx, 0);
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    SkelAnime_Update(&this->anime);
    if ((this->actor.params & 3) == 0) {
        if (sp34 != 0) {
            this->actor.flags |= 1;
            func_80AD0830(this, globalCtx);
            this->actor.draw = EnOsn_Draw;
        } else {
            this->actor.draw = 0;
            this->actor.flags &= -2;
        }
    }
    func_800E9250(globalCtx, &this->actor, (Vec3s*)this->unk_1D8, (Vec3s*)&this->unk_1D8[6], this->actor.focus.pos);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Draw.s")
