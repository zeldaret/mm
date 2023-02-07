/*
 * File: z_en_si.c
 * Overlay: ovl_En_Si
 * Description: Golden Skulltula Token
 */

#include "z_en_si.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_200)

#define THIS ((EnSi*)thisx)

void EnSi_Init(Actor* thisx, PlayState* play);
void EnSi_Destroy(Actor* thisx, PlayState* play);
void EnSi_Update(Actor* thisx, PlayState* play);
void EnSi_Draw(Actor* thisx, PlayState* play);

void func_8098CB70(EnSi* this, PlayState* play);
void func_8098CBDC(EnSi* this, PlayState* play);
void func_8098CAD0(EnSi* this, PlayState* play);
void func_8098CA20(EnSi* this, PlayState* play);

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

// static ColliderSphereInit sSphereInit = {
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
    this->collider_sphere.dim.worldSphere.center.x = (s16)(s32)this->actor.world.pos.x;
    this->collider_sphere.dim.worldSphere.center.y = (s16)(s32)this->actor.world.pos.y;
    this->collider_sphere.dim.worldSphere.center.z = (s16)(s32)this->actor.world.pos.z;
    this->collider_sphere.dim.worldSphere.radius =
        (s16)(s32)((f32)this->collider_sphere.dim.modelSphere.radius * this->collider_sphere.dim.scale);
    if ((s32)this->actor.colChkInfo.health > 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider_sphere.base);
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider_sphere.base);
}

void func_8098CAD0(EnSi* this, PlayState* play) {
    s32 temp_a2;

    temp_a2 = (s32)(this->actor.params & 0xFC) >> 2;
    if ((temp_a2 < 0x20) && (temp_a2 >= 0)) {
        Flags_SetTreasure(play, temp_a2);
    }
    Item_Give(play, ITEM_SKULL_TOKEN);
    if (Inventory_GetSkullTokenCount(play->sceneId) >= 0x1E) {
        Message_StartTextbox(play, 0xFCU, NULL);
        Audio_PlayFanfare(NA_SE_PL_DUMMY_290);
        return;
    }
    Message_StartTextbox(play, 0x52U, NULL);
    Audio_PlayFanfare(NA_BGM_GET_SMALL_ITEM);
}

void func_8098CB70(EnSi* this, PlayState* play) {
    if ((this->actor.flags & 0x2000) == 0x2000) {
        this->actionFunc = func_8098CBDC;
        goto block_4;
    }
    if (this->collider_sphere.base.ocFlags2 & 1) {
        func_8098CAD0(this, play);
        Actor_Kill(&this->actor);
        return;
    }
block_4:
    this->actor.shape.rot.y += 0x38E;
}

void func_8098CBDC(EnSi* this, PlayState* play) {
    if ((this->actor.flags & 0x2000) != 0x2000) {
        func_8098CAD0(this, play);
        Actor_Kill(&this->actor);
    }
}

void EnSi_Init(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;

    Collider_InitSphere(play, &this->collider_sphere);
    Collider_SetSphere(play, &this->collider_sphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.25f);
    this->actionFunc = func_8098CB70;
}

void EnSi_Destroy(Actor* thisx, PlayState* play) {
    EnSi* this = THIS;
    Collider_DestroySphere(play, &this->collider_sphere);
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
