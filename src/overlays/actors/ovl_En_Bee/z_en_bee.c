/*
 * File: z_en_bee.c
 * Overlay: ovl_En_Bee
 * Description: Giant Bee
 */

#include "z_en_bee.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnBee*)thisx)

void EnBee_Init(Actor* thisx, PlayState* play);
void EnBee_Destroy(Actor* thisx, PlayState* play);
void EnBee_Update(Actor* thisx, PlayState* play);
void EnBee_Draw(Actor* thisx, PlayState* play);

void func_80B5A9E8(EnBee* this, PlayState* play);
void func_80B5AC3C(EnBee* this, PlayState* play);
void func_80B5A854(EnBee* this);
void func_80B5ABC4(EnBee* this);

s32 D_80B5B1F0 = 0;

const ActorInit En_Bee_InitVars = {
    ACTOR_EN_BEE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BEE,
    sizeof(EnBee),
    (ActorFunc)EnBee_Init,
    (ActorFunc)EnBee_Destroy,
    (ActorFunc)EnBee_Update,
    (ActorFunc)EnBee_Draw,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0xF),
    /* Ice arrow      */ DMG_ENTRY(2, 0xF),
    /* Light arrow    */ DMG_ENTRY(2, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x08, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 6, 13, -4, { 0, 0, 0 } },
};

void EnBee_Init(Actor* thisx, PlayState* play) {
    EnBee* this = THIS;

    this->actor.colChkInfo.mass = 10;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_Init(play, &this->skelAnime, &object_bee_Skel_001398, &object_bee_Anim_00005C, this->morphTable,
                   this->jointTable, OBJECT_BEE_LIMB_MAX);
    this->actor.colChkInfo.health = 1;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.targetMode = 6;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->unk_218 = D_80B5B1F0;
    D_80B5B1F0++;
    this->actor.shape.shadowScale = 12.0f;

    if (ActorCutscene_GetCurrentIndex() != -1) {
        func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_ITEMACTION);
    }

    this->actor.hintId = TATL_HINT_ID_GIANT_BEE;
    func_80B5A854(this);
}

void EnBee_Destroy(Actor* thisx, PlayState* play) {
    EnBee* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80B5A854(EnBee* this) {
    s32 pad;
    Vec3f sp48;
    s16 sp46;

    Animation_Change(&this->skelAnime, &object_bee_Anim_00005C, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_bee_Anim_00005C), 0, -10.0f);
    Math_Vec3f_Copy(&sp48, &this->actor.home.pos);

    sp46 = (this->unk_218 * 0x700) + 0x2000;
    sp48.x += Math_SinS(sp46) * 50.0f;
    sp48.y = Rand_ZeroFloat(50.0f) + (this->actor.floorHeight + 30.0f);
    sp48.z += Math_CosS(sp46) * 50.0f;

    Math_Vec3f_Copy(&this->unk_21C[0], &sp48);
    Math_Vec3f_Copy(&sp48, &this->actor.home.pos);

    sp48.x += Math_SinS(sp46 - 0x4000) * 50.0f;
    sp48.y = Rand_ZeroFloat(50.0f) + (this->actor.floorHeight + 30.0f);
    sp48.z += Math_CosS(sp46 - 0x4000) * 50.0f;

    Math_Vec3f_Copy(&this->unk_21C[1], &sp48);

    this->unk_204 = Rand_S16Offset(0x14, 0x1E);
    this->unk_208 = 0;
    this->actionFunc = func_80B5A9E8;
}

void func_80B5A9E8(EnBee* this, PlayState* play) {
    Vec3f sp3C;
    s32 pad[2];

    if ((this->actor.category != ACTORCAT_ENEMY) && (ActorCutscene_GetCurrentIndex() == -1)) {
        func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_ENEMY);
    }

    Math_Vec3f_Copy(&sp3C, &this->unk_21C[this->unk_214]);
    sp3C.x += Math_SinS(this->unk_20C) * 30.0f;
    sp3C.z += Math_CosS(this->unk_20C) * 30.0f;

    if (!(this->unk_218 & 1)) {
        this->unk_20C += (s16)((s32)randPlusMinusPoint5Scaled(1000.0f) + 4000);
    } else {
        this->unk_20C -= (s16)((s32)randPlusMinusPoint5Scaled(1000.0f) + 4000);
    }

    this->unk_210 += 1000;
    this->actor.velocity.y = Math_SinS(this->unk_210);

    if (this->unk_20C > 0x10000) {
        this->unk_20C = 0;
        this->unk_214++;
        this->unk_214 &= 1;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp3C), 1, 0x7D0, 0);
    Math_ApproachF(&this->actor.speedXZ, 3.0f, 0.3f, 1.0f);

    if ((this->unk_204 == 0) && (this->actor.params != 0)) {
        func_80B5ABC4(this);
    }
}

void func_80B5ABC4(EnBee* this) {
    Animation_Change(&this->skelAnime, &object_bee_Anim_00005C, 1.0f, 0.0f,
                     Animation_GetLastFrame(&object_bee_Anim_00005C), 0, -10.0f);
    this->unk_208 = 1;
    this->actionFunc = func_80B5AC3C;
}

void func_80B5AC3C(EnBee* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp88;
    f32 rnd;
    f32 phi_fs1;
    s32 i;

    Math_Vec3f_Copy(&sp88, &player->actor.world.pos);
    phi_fs1 = (this->unk_218 * 0x700) + 0x2000;

    for (i = 0; i < 2; i++) {
        rnd = randPlusMinusPoint5Scaled(20.0f);
        sp88.x += Math_SinS((this->actor.yawTowardsPlayer + ((f32)this->unk_20C)) + phi_fs1) * (rnd + 30.0f);
        sp88.y = (Math_SinS(this->unk_210) * 10.0f) + (player->actor.floorHeight + 40.0f);
        rnd = randPlusMinusPoint5Scaled(20.0f);
        sp88.z += Math_CosS((f32)this->actor.yawTowardsPlayer + this->unk_20C + phi_fs1) * (rnd + 30.0f);
        Math_Vec3f_Copy(&this->unk_21C[i], &sp88);
        phi_fs1 -= 16384.0f;
    }

    Math_Vec3f_Copy(&sp88, &this->unk_21C[this->unk_214]);

    if (!(this->unk_218 & 1)) {
        this->unk_20C += (this->unk_218 * 0x700) + (s32)randPlusMinusPoint5Scaled((this->unk_218 * 0x700) * 0.5f);
    } else {
        this->unk_20C -= (this->unk_218 * 0x700) + (s32)randPlusMinusPoint5Scaled((this->unk_218 * 0x700) * 0.5f);
    }

    this->unk_210 += (s32)randPlusMinusPoint5Scaled(500.0f) + 1000;

    if (this->unk_20C > 0x10000) {
        this->unk_20C = 0;
        this->unk_214++;
        this->unk_214 &= 1;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp88), 1, 0x1388, 0);
    Math_ApproachF(&this->actor.world.pos.y, sp88.y, 0.3f, 3.0f);
    Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.3f, 1.0f);
}

void func_80B5AF80(EnBee* this, PlayState* play) {
    if ((this->unk_206 == 0) && (this->collider.base.atFlags & AC_HIT)) {
        AudioSfx_StopByPosAndId(&this->actor.projectedPos, NA_SE_EN_BEE_FLY - SFX_FLAG);
        this->unk_206 = 5;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        Enemy_StartFinishingBlow(play, &this->actor);
        this->actor.speedXZ = 0.0f;
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 10, NA_SE_EN_CUTBODY);
        this->actor.colChkInfo.health = 0;
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EN_EXTINCT);
        func_800B3030(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, 100, 0, 2);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBee_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnBee* this = THIS;

    SkelAnime_Update(&this->skelAnime);

    if (this->actor.category == ACTORCAT_ENEMY) {
        if (this->unk_204 != 0) {
            this->unk_204--;
        }
        if (this->unk_206 != 0) {
            this->unk_206--;
        }
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BEE_FLY - SFX_FLAG);
    func_80B5AF80(this, play);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    Actor_SetFocus(&this->actor, 0.0f);
    Actor_SetScale(&this->actor, 0.01f);

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 40.0f, 40.0f, 0x1D);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
}

void EnBee_Draw(Actor* thisx, PlayState* play) {
    EnBee* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);
}
