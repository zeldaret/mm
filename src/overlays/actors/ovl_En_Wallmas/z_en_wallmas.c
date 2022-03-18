/*
 * File: z_en_wallmas.c
 * Overlay: ovl_En_Wallmas
 * Description: Wallmaster
 */

#include "z_en_wallmas.h"
#include "overlays/actors/ovl_En_Encount1/z_en_encount1.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((EnWallmas*)thisx)

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80874BE4(EnWallmas* this, GlobalContext* globalCtx);
void func_80874DE8(EnWallmas* this, GlobalContext* globalCtx);
void func_80874FD8(EnWallmas* this, GlobalContext* globalCtx);
void func_80875054(EnWallmas* this, GlobalContext* globalCtx);
void func_80875108(EnWallmas* this, GlobalContext* globalCtx);
void func_8087520C(EnWallmas* this, GlobalContext* globalCtx);
void func_808752CC(EnWallmas* this, GlobalContext* globalCtx);
void func_80875484(EnWallmas* this, GlobalContext* globalCtx);
void func_8087556C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875638(EnWallmas* this, GlobalContext* globalCtx);
void func_8087571C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875910(EnWallmas* this, GlobalContext* globalCtx);
void func_8087596C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875A0C(EnWallmas* this, GlobalContext* globalCtx);
void func_80875248(EnWallmas* this);
void func_808758C8(EnWallmas* this);
void func_80874B88(EnWallmas* this, GlobalContext* globalCtx);
void func_80874D1C(EnWallmas* this, GlobalContext* globalCtx);
void func_80874F14(EnWallmas* this, GlobalContext* globalCtx);
void func_808756AC(EnWallmas* this, GlobalContext* globalCtx);
void func_80875014(EnWallmas* this);
void func_808750B8(EnWallmas* this);
void func_808751C4(EnWallmas* this);

#if 0
const ActorInit En_Wallmas_InitVars = {
    ACTOR_EN_WALLMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnWallmas),
    (ActorFunc)EnWallmas_Init,
    (ActorFunc)EnWallmas_Destroy,
    (ActorFunc)EnWallmas_Update,
    (ActorFunc)EnWallmas_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80876360 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_8087638C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808763AC = { 3, 30, 40, 150 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808763B4[] = {
    ICHAIN_S8(hintId, 48, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80876360;
extern DamageTable D_8087638C;
extern CollisionCheckInfoInit D_808763AC;
extern InitChainEntry D_808763B4[];
extern f32 D_808763C0[];

extern UNK_TYPE D_06000590;
extern UNK_TYPE D_06000EA4;
extern AnimationHeader D_060019CC;
extern AnimationHeader D_0600299C;
extern AnimationHeader D_060041F4;
extern UNK_TYPE D_06008688;
extern AnimationHeader D_06009244;
extern AnimationHeader D_06009520;
extern AnimationHeader D_06009DB0;
extern AnimationHeader D_0600A054;
extern FlexSkeletonHeader D_06008FB0;

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWallmas* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_808763B4);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.5f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06008FB0, &D_06009DB0, this->jointTable, this->morphTable, 25);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80876360);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_8087638C, &D_808763AC);

    this->switchFlag = EN_WALLMAS_GET_SWITCH_FLAG(thisx);
    this->actor.params &= 0xFF;
    this->unk_2C4 = this->actor.shape.rot.x * 40.0f * 0.1f;
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    if (this->unk_2C4 <= 0.0f) {
        this->unk_2C4 = 200.0f;
    }

    Actor_SetFocus(&this->actor, 25.0f);

    if (EN_WALLMAS_IS_FROZEN(&this->actor)) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                           this->actor.world.pos.y - 15.0f, this->actor.world.pos.z, this->actor.world.rot.x,
                           (this->actor.world.rot.y + 0x5900), this->actor.world.rot.z, 0xFF50);
        this->actor.params &= ~0x80;
        func_80875248(this);
        return;
    }

    if (EN_WALLMAS_GET_TYPE(&this->actor) == 2) {
        if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        func_808758C8(this);
    } else if (EN_WALLMAS_GET_TYPE(&this->actor) == 1) {
        func_808758C8(this);
    } else {
        func_80874B88(this, globalCtx);
    }
}

void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWallmas* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);

    if (this->actor.parent != NULL) {
        EnEncount1* encount1 = (EnEncount1*)this->actor.parent;

        if ((encount1->actor.update != NULL) && (encount1->unk_14E > 0)) {
            encount1->unk_14E--;
        }
    }
}

void func_80874A88(EnWallmas* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874A88.s")

void func_80874B04(EnWallmas* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874B04.s")

void func_80874B88(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags |= ACTOR_FLAG_20;
    this->timer = 130;
    this->actor.velocity.y = 0.0f;
    this->actor.world.pos.y = player->actor.world.pos.y;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.draw = EnWallmas_Draw;
    this->actionFunc = func_80874BE4;
}

void func_80874BE4(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* playerPos = &player->actor.world.pos;

    this->actor.world.pos = *playerPos;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.floorPoly = player->actor.floorPoly;

    if (this->timer != 0) {
        this->timer--;
    }

    if ((player->stateFlags1 & 0x08100000) || (player->stateFlags2 & 0x80) || (player->unk_B5E > 0) ||
        (player->actor.freezeTimer > 0) || !(player->actor.bgCheckFlags & 1) ||
        ((EN_WALLMAS_GET_TYPE(&this->actor) == 1) &&
         (Math_Vec3f_DistXZ(&this->actor.home.pos, playerPos) > (120.f + this->unk_2C4)))) {
        func_801A75E8(NA_SE_EN_FALL_AIM);
        this->timer = 130;
    }

    if (this->timer == 0x50) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_AIM);
    }

    if (this->timer == 0) {
        func_80874D1C(this, globalCtx);
    }
}

void func_80874D1C(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Animation_Change(&this->skelAnime, &D_0600299C, 0.0f, 20.0f, Animation_GetLastFrame(&D_0600299C), ANIMMODE_ONCE,
                     0.0f);

    this->unk_2C0 = player->actor.world.pos.y;
    this->actor.world.pos.y = player->actor.world.pos.y + 300.0f;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.floorHeight = player->actor.floorHeight;
    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.flags &= ~ACTOR_FLAG_20;
    this->actionFunc = func_80874DE8;
}

void func_80874DE8(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags2 & 0x80) || (player->actor.freezeTimer > 0)) {
        func_80875248(this);
    } else if (!func_801690CC(globalCtx) && !(player->stateFlags2 & 0x10) && (player->invincibilityTimer >= 0) &&
               (this->actor.xzDistToPlayer < 30.0f) && (this->actor.playerHeightRel < -5.0f) &&
               (-(f32)(player->cylinder.dim.height + 10) < this->actor.playerHeightRel)) {
        func_808756AC(this, globalCtx);
    } else if (this->actor.world.pos.y <= this->unk_2C0) {
        this->actor.world.pos.y = this->unk_2C0;
        this->actor.velocity.y = 0.0f;
        func_80874F14(this, globalCtx);
    }
}

void func_80874F14(EnWallmas* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &D_060019CC, 1.0f, 41.0f, Animation_GetLastFrame(&D_060019CC), ANIMMODE_ONCE,
                     -3.0f);

    Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 15.0f, 6, 20.0f, 300, 100, true);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_LAND);
    this->actionFunc = func_80874FD8;
}

void func_80874FD8(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_80875014(this);
    }
}

void func_80875014(EnWallmas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_0600A054);
    this->actionFunc = func_80875054;
}

void func_80875054(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808750B8(this);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + 0x8000, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_808750B8(EnWallmas* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &D_060041F4, 3.0f);
    this->actor.speedXZ = 3.0f;
    this->actionFunc = func_80875108;
}

void func_80875108(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808751C4(this);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + 0x8000, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f) ||
        Animation_OnFrame(&this->skelAnime, 24.0f) || Animation_OnFrame(&this->skelAnime, 36.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_WALK);
    }
}

void func_808751C4(EnWallmas* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06009244);
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_8087520C;
}

void func_8087520C(EnWallmas* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_80875248(this);
    }
}

void func_80875248(EnWallmas* this) {
    this->timer = 0;
    this->actor.speedXZ = 0.0f;
    Animation_Change(&this->skelAnime, &D_060019CC, 3.0f, 0.0f, Animation_GetLastFrame(&D_060019CC), ANIMMODE_ONCE,
                     -3.0f);
    this->actionFunc = func_808752CC;
}

void func_808752CC(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (this->skelAnime.curFrame > 20.0f) {
        this->actor.world.pos.y += 30.0f;
        this->timer += 9;
        this->actor.flags &= ~ACTOR_FLAG_2000;
    }

    if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_UP);
    }

    if (this->actor.playerHeightRel < -900.0f) {
        if (EN_WALLMAS_GET_TYPE(&this->actor) == 2) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        if ((EN_WALLMAS_GET_TYPE(&this->actor) == 0) ||
            (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < this->unk_2C4)) {
            func_80874B88(this, globalCtx);
        } else {
            func_808758C8(this);
        }
    }
}

void func_808753F0(EnWallmas* this, s32 arg1);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808753F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808755A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875638.s")

void func_808756AC(EnWallmas* this, GlobalContext* globalCtx) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06009520, -5.0f);
    this->timer = -30;
    this->actionFunc = func_8087571C;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->unk_2C0 = this->actor.playerHeightRel;
    func_800B724C(globalCtx, &this->actor, 18);
}

void func_8087571C(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_CATCH);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        player->actor.world.pos.x = this->actor.world.pos.x;
        player->actor.world.pos.z = this->actor.world.pos.z;

        if (this->timer < 0) {
            this->actor.world.pos.y += 2.0f;
        } else {
            this->actor.world.pos.y += 10.0f;
        }

        player->actor.world.pos.y = this->actor.world.pos.y - D_808763C0[(void)0, gSaveContext.playerForm];
        if (this->timer == -30) {
            func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_TAKEN_AWAY);
        }

        if (this->timer == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_UP);
        }

        this->timer += 2;
    } else {
        Math_StepToF(&this->actor.world.pos.y, D_808763C0[(void)0, gSaveContext.playerForm] + player->actor.world.pos.y,
                     5.0f);
    }

    Math_StepToF(&this->actor.world.pos.x, player->actor.world.pos.x, 3.0f);
    Math_StepToF(&this->actor.world.pos.z, player->actor.world.pos.z, 3.0f);

    if (this->timer == 30) {
        play_sound(NA_SE_OC_ABYSS);
        func_80169FDC(&globalCtx->state);
    }
}

void func_808758C8(EnWallmas* this) {
    this->timer = 0;
    this->actor.draw = NULL;
    this->actor.flags &= ~ACTOR_FLAG_1;
    if (EN_WALLMAS_GET_TYPE(&this->actor) == 1) {
        this->actionFunc = func_80875910;
    } else {
        this->actionFunc = func_8087596C;
    }
}

void func_80875910(EnWallmas* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < this->unk_2C4) {
        func_80874B88(this, globalCtx);
    }
}

void func_8087596C(EnWallmas* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        func_80874B88(this, globalCtx);
        this->timer = 81;
    }
}

void func_808759B8(EnWallmas* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808759B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875A0C.s")

void func_80875A74(EnWallmas* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if ((this->unk_18C != 0xA) || (!(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3))) {
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(globalCtx, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DAIOCTA_REVERSE);
                this->actor.flags &= ~ACTOR_FLAG_1;
            } else if (this->actor.colChkInfo.damage != 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FALL_DAMAGE);
            }

            func_80874B04(this, globalCtx);

            if (this->actor.colChkInfo.damageEffect != 0xF) {
                if (this->actor.colChkInfo.damageEffect == 3) {
                    func_80874A88(this);
                    if (this->actor.colChkInfo.health == 0) {
                        this->timer = 3;
                        this->collider.base.acFlags &= ~AC_ON;
                    }

                    func_808759B8(this);
                } else if (this->actor.colChkInfo.damageEffect == 1) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    func_808759B8(this);
                } else if (this->actor.colChkInfo.damageEffect == 5) {
                    this->timer = 40;
                    Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                    this->unk_2CC = 0.55f;
                    this->unk_2C8 = 2.0f;
                    this->unk_18C = 0x1F;
                    func_808759B8(this);
                } else {
                    if (this->actor.colChkInfo.damageEffect == 2) {
                        this->unk_2C8 = 4.0f;
                        this->unk_2CC = 0.55f;
                        this->unk_18C = 0;
                    } else if (this->actor.colChkInfo.damageEffect == 4) {
                        this->unk_2C8 = 4.0f;
                        this->unk_2CC = 0.55f;
                        this->unk_18C = 0x14;
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                    this->collider.info.bumper.hitPos.x, this->collider.info.bumper.hitPos.y,
                                    this->collider.info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                    }

                    func_808753F0(this, 1);
                }
            }
        }
    }
}

void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWallmas* this = THIS;

    func_80875A74(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != func_80874BE4) && (this->actionFunc != func_80875910) &&
        (this->actionFunc != func_8087571C) && (this->actionFunc != func_8087596C)) {
        if ((this->actionFunc != func_808752CC) && (this->actionFunc != func_8087571C)) {
            Actor_MoveWithGravity(&this->actor);
        }

        if (this->actionFunc != func_80874DE8) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 25.0f, 0.0f, 0x1DU);
        }

        if ((this->actionFunc != func_80875638) && (this->actionFunc != func_80874DE8)) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            if ((this->actionFunc != func_80875484) && (this->actor.bgCheckFlags & 1) &&
                (this->actor.freezeTimer == 0)) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }

        Actor_SetFocus(&this->actor, 25.0f);

        if (this->unk_2C8 > 0.0f) {
            if (this->unk_18C != 0xA) {
                Math_StepToF(&this->unk_2C8, 0.0f, 0.05f);
                this->unk_2CC = (this->unk_2C8 + 1.0f) * 0.275f;
                this->unk_2CC = CLAMP_MAX(this->unk_2CC, 0.55f);
            } else if (Math_StepToF(&this->unk_2D0, 0.55f, 0.01375f) == 0) {
                func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808760A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80876118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Draw.s")
