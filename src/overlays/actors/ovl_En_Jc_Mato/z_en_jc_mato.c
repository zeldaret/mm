/*
 * File: z_en_jc_mato.c
 * Overlay: ovl_En_Jc_Mato
 * Description: Boat Cruise Target
 */

#include "z_en_jc_mato.h"
#include "objects/object_tru/object_tru.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_4000)

#define THIS ((EnJcMato*)thisx)

void EnJcMato_Init(Actor* thisx, PlayState* play);
void EnJcMato_Destroy(Actor* thisx, PlayState* play);
void EnJcMato_Update(Actor* thisx, PlayState* play);
void EnJcMato_Draw(Actor* thisx, PlayState* play);

s32 EnJcMato_CheckForHit(EnJcMato* this, PlayState* play);
void EnJcMato_SetupIdle(EnJcMato* this);
void EnJcMato_Idle(EnJcMato* this, PlayState* play);

ActorInit En_Jc_Mato_InitVars = {
    /**/ ACTOR_EN_JC_MATO,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_TRU,
    /**/ sizeof(EnJcMato),
    /**/ EnJcMato_Init,
    /**/ EnJcMato_Destroy,
    /**/ EnJcMato_Update,
    /**/ EnJcMato_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 15 }, 100 },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
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

s32 EnJcMato_CheckForHit(EnJcMato* this, PlayState* play) {
    this->collider.dim.worldSphere.center.x = this->pos.x;
    this->collider.dim.worldSphere.center.y = this->pos.y;
    this->collider.dim.worldSphere.center.z = this->pos.z;
    if ((this->collider.base.acFlags & AC_HIT) && !this->hitFlag && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
        play->interfaceCtx.minigamePoints = 1;
        this->hitFlag = true;
        return 1;
    } else {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        return 0;
    }
}

void EnJcMato_SetupIdle(EnJcMato* this) {
    this->actionFunc = EnJcMato_Idle;
}

void EnJcMato_Idle(EnJcMato* this, PlayState* play) {
    if (this->hitFlag) {
        if (DECR(this->despawnTimer) == 0) {
            Actor_Kill(&this->actor);
        }
    }
}

void EnJcMato_Init(Actor* thisx, PlayState* play) {
    EnJcMato* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    Collider_InitSphere(play, &this->collider);
    Collider_SetSphere(play, &this->collider, &this->actor, &sSphereInit);
    this->collider.dim.worldSphere.radius = 15;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    Actor_SetScale(&this->actor, 0.008f);
    this->hitFlag = false;
    this->despawnTimer = 25;
    EnJcMato_SetupIdle(this);
}

void EnJcMato_Destroy(Actor* thisx, PlayState* play) {
    EnJcMato* this = THIS;

    Collider_DestroySphere(play, &this->collider);
}

void EnJcMato_Update(Actor* thisx, PlayState* play) {
    EnJcMato* this = THIS;

    this->actionFunc(this, play);
    if (!CHECK_EVENTINF(EVENTINF_40)) {
        EnJcMato_CheckForHit(this, play);
    }
}

void EnJcMato_Draw(Actor* thisx, PlayState* play) {
    static Vec3f sOffset = { 0.0f, -2500.0f, 0.0f };
    EnJcMato* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gKoumeTargetDL);
    Matrix_MultVec3f(&sOffset, &this->pos);

    CLOSE_DISPS(play->state.gfxCtx);
}
