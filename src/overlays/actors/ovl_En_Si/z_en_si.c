/*
 * File: z_en_si.c
 * Overlay: ovl_En_Si
 * Description: Golden Skulltula Token
 */

#include "z_en_si.h"

#define ENSI_GET_CHEST_FLAG(thisx) (((thisx)->params & 0xFC) >> 2)

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_200)

#define THIS ((EnSi*)thisx)

void EnSi_Init(Actor* thisx, PlayState* play);
void EnSi_Destroy(Actor* thisx, PlayState* play);
void EnSi_Update(Actor* thisx, PlayState* play);
void EnSi_Draw(Actor* thisx, PlayState* play);

void func_8098CBDC(EnSi* this, PlayState* play);

ActorInit En_Si_InitVars = {
    ACTOR_EN_SI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSi),
    (ActorFunc)EnSi_Init,
    (ActorFunc)EnSi_Destroy,
    (ActorFunc)EnSi_Update,
    (ActorFunc)EnSi_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 10 }, 100 },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

void func_8098CA20(EnSi* this, PlayState* play) {
    this->colliderSphere.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->colliderSphere.dim.worldSphere.center.y = this->actor.world.pos.y;
    this->colliderSphere.dim.worldSphere.center.z = this->actor.world.pos.z;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
    if (this->actor.colChkInfo.health > 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void func_8098CAD0(EnSi* this, PlayState* play) {
    s32 chestFlag = ENSI_GET_CHEST_FLAG(&this->actor);

    if ((chestFlag < 0x20) && (chestFlag >= 0)) {
        Flags_SetTreasure(play, chestFlag);
    }
    Item_Give(play, ITEM_SKULL_TOKEN);
    if (Inventory_GetSkullTokenCount(play->sceneId) >= 30) {
        Message_StartTextbox(play, 0xFC, NULL);
        Audio_PlayFanfare(NA_BGM_GET_ITEM | 0x900);
    } else {
        Message_StartTextbox(play, 0x52, NULL);
        Audio_PlayFanfare(NA_BGM_GET_SMALL_ITEM);
    }
}

void func_8098CB70(EnSi* this, PlayState* play) {
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_2000)) {
        this->actionFunc = func_8098CBDC;
    } else if (this->colliderSphere.base.ocFlags2 & OC2_HIT_PLAYER) {
        func_8098CAD0(this, play);
        Actor_Kill(&this->actor);
        return;
    }
    this->actor.shape.rot.y += 0x38E;
}

void func_8098CBDC(EnSi* this, PlayState* play) {
    if (!CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_2000)) {
        func_8098CAD0(this, play);
        Actor_Kill(&this->actor);
    }
}

void EnSi_Init(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;

    Collider_InitSphere(play, &this->colliderSphere);
    Collider_SetSphere(play, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.25f);
    this->actionFunc = func_8098CB70;
}

void EnSi_Destroy(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;

    Collider_DestroySphere(play, &this->colliderSphere);
}

void EnSi_Update(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;

    this->actionFunc(this, play);
    func_8098CA20(this, play);
    Actor_SetFocus(&this->actor, 0.0f);
}

void EnSi_Draw(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;

    func_800B8118(&this->actor, play, 0);
    func_800B8050(&this->actor, play, 0);
    GetItem_Draw(play, GID_SKULL_TOKEN_2);
}
