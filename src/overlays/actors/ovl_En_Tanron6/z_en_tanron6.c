/*
 * File: z_en_tanron6.c
 * Overlay: ovl_En_Tanron6
 * Description: Swarm of Giant Bees
 */

#include "z_en_tanron6.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnTanron6*)thisx)

void EnTanron6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTanron6_DoNothing(EnTanron6* this);
void func_80BE60D0(EnTanron6* this, GlobalContext* globalCtx);

const ActorInit En_Tanron6_InitVars = {
    ACTOR_EN_TANRON6,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TANRON5,
    sizeof(EnTanron6),
    (ActorFunc)EnTanron6_Init,
    (ActorFunc)EnTanron6_Destroy,
    (ActorFunc)EnTanron6_Update,
    (ActorFunc)EnTanron6_Draw,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(6, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

void EnTanron6_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron6* this = THIS;

    this->actor.colChkInfo.mass = 10;
    ActorShape_Init(&this->actor.shape, 0, ActorShadow_DrawCircle, 19.0f);
    this->actor.colChkInfo.health = 1;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.targetMode = 6;
    EnTanron6_DoNothing(this);
}

void EnTanron6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnTanron6_DoNothing(EnTanron6* this) {
    this->actionFunc = func_80BE60D0;
}

void func_80BE60D0(EnTanron6* this, GlobalContext* globalCtx) {
}

void EnTanron6_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron6* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 40.0f, 40.0f, 0x1D);
}

void EnTanron6_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
