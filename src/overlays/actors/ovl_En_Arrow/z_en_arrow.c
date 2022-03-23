/*
 * File: z_en_arrow.c
 * Overlay: ovl_En_Arrow
 * Description: Arrows and other projectiles
 */

#include "z_en_arrow.h"
#include "overlays/effects/ovl_Effect_Ss_Sbn/z_eff_ss_sbn.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnArrow*)thisx)

void EnArrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8088A594(EnArrow* this, GlobalContext* globalCtx);
void func_8088ACE0(EnArrow* this, GlobalContext* globalCtx);
void func_8088B630(EnArrow* this, GlobalContext* globalCtx);
void func_8088B6B0(EnArrow* this, GlobalContext* globalCtx);

const ActorInit En_Arrow_InitVars = {
    ACTOR_EN_ARROW,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnArrow),
    (ActorFunc)EnArrow_Init,
    (ActorFunc)EnArrow_Destroy,
    (ActorFunc)EnArrow_Update,
    (ActorFunc)EnArrow_Draw,
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000020, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(terminalVelocity, -150, ICHAIN_STOP),
};

void EnArrow_Init(Actor* thisx, GlobalContext* globalCtx) {
    static EffectBlureInit2 D_8088C234 = {
        0, 4, 0, { 0, 255, 200, 255 },   { 0, 255, 255, 255 }, { 0, 255, 200, 0 }, { 0, 255, 255, 0 }, 16,
        0, 1, 0, { 255, 255, 170, 255 }, { 0, 150, 0, 0 },
    };
    static EffectBlureInit2 D_8088C258 = {
        0, 4, 0, { 0, 255, 200, 255 }, { 0, 255, 255, 255 }, { 0, 255, 200, 0 }, { 0, 255, 255, 0 }, 16,
        0, 1, 0, { 255, 200, 0, 255 }, { 255, 0, 0, 0 },
    };
    static EffectBlureInit2 D_8088C27C = {
        0, 4, 0, { 0, 255, 200, 255 },   { 0, 255, 255, 255 }, { 0, 255, 200, 0 }, { 0, 255, 255, 0 }, 16,
        0, 1, 0, { 170, 255, 255, 255 }, { 0, 0x64, 255, 0 },
    };
    static EffectBlureInit2 D_8088C2A0 = {
        0, 4, 0, { 0, 255, 200, 255 },   { 0, 255, 255, 255 }, { 0, 255, 200, 0 }, { 0, 255, 255, 0 }, 16,
        0, 1, 0, { 255, 255, 170, 255 }, { 255, 255, 0, 0 },
    };
    EnArrow* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (this->actor.params == ENARROW_MINUS8) {
        this->unk_263 = 1;
        this->actor.params = 8;
    }

    if (this->actor.params < ENARROW_6) {
        SkelAnime_Init(globalCtx, &this->arrow.skelAnime, &gameplay_keep_Skel_014560, &gameplay_keep_Anim_0128BC,
                       this->arrow.jointTable, this->arrow.jointTable, 5);
        if (this->actor.params < ENARROW_3) {
            if (this->actor.params == ENARROW_1) {
                D_8088C234.elemDuration = 4;
            } else {
                D_8088C234.elemDuration = 16;
            }
            Effect_Add(globalCtx, &this->unk_240, EFFECT_BLURE2, 0, 0, &D_8088C234);
        } else if (this->actor.params == ENARROW_3) {
            Effect_Add(globalCtx, &this->unk_240, EFFECT_BLURE2, 0, 0, &D_8088C258);
        } else if (this->actor.params == ENARROW_4) {
            Effect_Add(globalCtx, &this->unk_240, EFFECT_BLURE2, 0, 0, &D_8088C27C);
        } else if (this->actor.params == ENARROW_5) {
            Effect_Add(globalCtx, &this->unk_240, EFFECT_BLURE2, 0, 0, &D_8088C2A0);
        }
    }

    Collider_InitQuad(globalCtx, &this->collider);
    Collider_SetQuad(globalCtx, &this->collider, &this->actor, &sQuadInit);

    if (this->actor.params < ENARROW_6) {
        this->collider.info.toucherFlags &= ~(TOUCH_SFX_WOOD | TOUCH_SFX_HARD);
        this->collider.info.toucherFlags |= 0;
    }

    if (this->actor.params < ENARROW_0) {
        this->collider.base.atFlags = (AT_TYPE_ENEMY | AT_ON);
    } else {
        this->collider.info.toucher.dmgFlags = func_800BC188(this->actor.params);
        if (this->actor.params == ENARROW_8) {
            this->collider.info.toucher.damage = 1;
        }

        if (this->actor.params == ENARROW_7) {
            Actor_SetScale(&this->actor, 1.0f);
        }
    }
    this->actionFunc = func_8088A594;
}

void EnArrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnArrow* this = THIS;

    if (this->actor.params < ENARROW_6) {
        Effect_Destroy(globalCtx, this->unk_240);
    }

    Collider_DestroyQuad(globalCtx, &this->collider);

    if ((this->unk_264 != NULL) && (this->unk_264->update != NULL)) {
        this->unk_264->flags &= ~0x8000;
    }

    if ((this->actor.params >= ENARROW_3) && (this->actor.params < ENARROW_6) && (this->actor.child == NULL)) {
        func_80115D5C(&globalCtx->state);
    }
}

void func_8088A514(EnArrow* this) {
    f32 temp_f0 = 16.0f - this->bubble.unk_144;

    Actor_SetSpeeds(&this->actor, CLAMP(temp_f0, 1.0f, 80.0f));
}

void func_8088A594(EnArrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.parent != NULL) {
        if (this->actor.params == ENARROW_7) {
            if (Math_SmoothStepToF(&this->bubble.unk_144, 16.0f, 0.07f, 1.8f, 0.0f) > 0.5f) {
                func_800B9010(&this->actor, NA_SE_PL_DEKUNUTS_BUBLE_BREATH - SFX_FLAG);
                return;
            }

            this->bubble.unk_148++;
            if (this->bubble.unk_148 > 20) {
                this->actionFunc = func_8088ACE0;
                func_80115D5C(&globalCtx->state);
            }
        }
    } else {
        if ((this->actor.params != ENARROW_8) && (player->unk_D57 == 0)) {
            if (this->actor.params == ENARROW_7) {
                func_80115D5C(&globalCtx->state);
            }
            Actor_MarkForDeath(&this->actor);
            return;
        }

        switch (this->actor.params) {
            case ENARROW_6:
                func_800B8E58(player, NA_SE_IT_SLING_SHOT);
                break;

            case ENARROW_0:
            case ENARROW_1:
            case ENARROW_2:
                func_800B8E58(player, NA_SE_IT_ARROW_SHOT);
                break;

            case ENARROW_3:
            case ENARROW_4:
            case ENARROW_5:
                func_800B8E58(player, NA_SE_IT_MAGIC_ARROW_SHOT);

            case ENARROW_7:
                func_800B8E58(player, NA_SE_PL_DEKUNUTS_FIRE);
                break;
        }

        this->actionFunc = func_8088ACE0;
        Math_Vec3f_Copy(&this->unk_228, &this->actor.world.pos);

        if (this->actor.params == ENARROW_7) {
            this->bubble.unk_144 = CLAMP_MIN(this->bubble.unk_144, 3.5f);
            func_8088A514(this);
            this->unk_260 = 99;
            func_80115D5C(&globalCtx->state);
        } else if (this->actor.params >= ENARROW_6) {
            if ((this->actor.params == ENARROW_8) && (this->actor.world.rot.x < 0)) {
                Actor_SetScale(&this->actor, 0.009f);
                this->unk_260 = 40;
            } else {
                Actor_SetSpeeds(&this->actor, 80.0f);
                this->unk_260 = 15;
            }
            this->actor.shape.rot.x = 0;
            this->actor.shape.rot.y = 0;
            this->actor.shape.rot.z = 0;
        } else {
            Actor_SetSpeeds(&this->actor, 150.0f);
            this->unk_260 = 16;
        }
    }
}

void func_8088A7D8(GlobalContext* globalCtx, EnArrow* this) {
    this->actionFunc = func_8088B6B0;
    Animation_PlayOnce(&this->arrow.skelAnime, &gameplay_keep_Anim_012860);
    this->actor.world.rot.y += (s32)(0x6000 * (Rand_ZeroOne() - 0.5f)) + 0x8000;
    this->actor.speedXZ *= 0.02f + (0.02f * Rand_ZeroOne());
    this->actor.gravity = -1.5f;
    this->unk_260 = 50;
    this->unk_263 = 1;
}

void func_8088A894(EnArrow* this, GlobalContext* globalCtx) {
    CollisionPoly* sp74;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;
    f32 sp4C;
    f32 temp_f0;
    s32 sp44;

    Math_Vec3f_Diff(&this->actor.world.pos, &this->unk_228, &sp68);
    sp4C = ((this->actor.world.pos.x - this->unk_264->world.pos.x) * sp68.x) +
           ((this->actor.world.pos.y - this->unk_264->world.pos.y) * sp68.y) +
           ((this->actor.world.pos.z - this->unk_264->world.pos.z) * sp68.z);
    if (sp4C < 0.0f) {
        return;
    }

    temp_f0 = Math3D_LengthSquared(&sp68);
    if (temp_f0 < 1.0f) {
        return;
    }

    temp_f0 = sp4C / temp_f0;
    Math_Vec3f_Scale(&sp68, temp_f0);
    Math_Vec3f_Sum(&this->unk_264->world.pos, &sp68, &sp5C);
    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->unk_264->world.pos, &sp5C, &sp50, &sp74, true, true, true,
                                true, &sp44)) {
        this->unk_264->world.pos.x = ((sp5C.x <= sp50.x) ? 1.0f : -1.0f) + sp50.x;
        this->unk_264->world.pos.y = ((sp5C.y <= sp50.y) ? 1.0f : -1.0f) + sp50.y;
        this->unk_264->world.pos.z = ((sp5C.z <= sp50.z) ? 1.0f : -1.0f) + sp50.z;
    } else {
        Math_Vec3f_Copy(&this->unk_264->world.pos, &sp5C);
    }
}

void func_8088AA98(EnArrow* this, GlobalContext* globalCtx) {
    WaterBox* sp54;
    f32 sp50 = this->actor.world.pos.y;
    Vec3f sp44;
    f32 temp_f0;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp50,
                             &sp54) &&
        (this->actor.world.pos.y < sp50) && !(this->actor.bgCheckFlags & 0x20)) {
        this->actor.bgCheckFlags |= 0x20;

        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.home.pos, &sp44);

        if (sp44.y != 0.0f) {
            temp_f0 = sqrtf(SQ(sp44.x) + SQ(sp44.z));
            if (temp_f0 != 0.0f) {
                temp_f0 = (((sp50 - this->actor.home.pos.y) / sp44.y) * temp_f0) / temp_f0;
            }
            sp44.x = this->actor.home.pos.x + (sp44.x * temp_f0);
            sp44.y = sp50;
            sp44.z = this->actor.home.pos.z + (sp44.z * temp_f0);
            EffectSsGSplash_Spawn(globalCtx, &sp44, NULL, NULL, 0, 300);
        }

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_INTO_WATER_L);

        EffectSsGRipple_Spawn(globalCtx, &sp44, 100, 500, 0);
        EffectSsGRipple_Spawn(globalCtx, &sp44, 100, 500, 4);
        EffectSsGRipple_Spawn(globalCtx, &sp44, 100, 500, 8);

        if ((this->actor.params == ENARROW_4) || (this->actor.params == ENARROW_3)) {
            if ((this->actor.params == ENARROW_4) && (func_8088B6B0 != this->actionFunc)) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BG_ICEFLOE, sp44.x, sp44.y, sp44.z, 0, 0, 0, 300);
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->actor.params = ENARROW_2;
            this->collider.info.toucher.dmgFlags = 0x20;

            if (this->actor.child != NULL) {
                Actor_MarkForDeath(this->actor.child);
                return;
            }

            func_80115D5C(&globalCtx->state);
        }
    }
}

#ifdef NON_MATCHING
// Stack. Scoped variable required to fix code gen at the bottom, likely sp60/54 there,
// but sp50 must be declared below those so maybe not?
void func_8088ACE0(EnArrow* this, GlobalContext* globalCtx) {
    CollisionPoly* spAC;
    s32 spA8;
    Vec3f sp9C;
    s32 phi_a2 = 0;
    EffectSsSbnInitParams sp84;
    u16 sp82;
    Actor* sp7C;
    f32 sp78;
    f32 sp74;
    f32 temp_f12_2;
    Vec3f sp60;
    Vec3f sp54;
    s32 sp50;

    if ((DECR(this->unk_260) == 0) ||
        ((this->actor.params == ENARROW_7) &&
         ((this->unk_262 != 0) || (phi_a2 = (this->collider.base.atFlags & AT_HIT) != 0)))) {
        if (this->actor.params == ENARROW_7) {
            if (phi_a2 && (this->collider.info.atHitInfo->elemType != ELEMTYPE_UNK4) &&
                (this->collider.base.atFlags & AT_BOUNCED)) {
                if ((this->collider.base.at != NULL) && (this->collider.base.at->id != ACTOR_OBJ_SYOKUDAI)) {
                    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
                    this->actor.world.rot.y += BINANG_ROT180((s16)randPlusMinusPoint5Scaled(8000.0f));
                    this->actor.velocity.y = -this->actor.velocity.y;
                    this->bubble.unk_149 = -1;
                    return;
                }
            }

            if ((this->unk_262 != 0) || phi_a2) {
                EffectSsStone1_Spawn(globalCtx, &this->actor.world.pos, 0);
            }

            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_IT_DEKUNUTS_BUBLE_VANISH);

            if ((this->unk_262 != 0) && (this->actor.wallBgId == BG_ACTOR_MAX)) {

                Math_Vec3f_Copy(&sp84.unk_00, &this->actor.world.pos);
                sp84.unk_0C = this->actor.wallPoly;
                sp84.unk_10 = this->bubble.unk_144;
                EffectSs_Spawn(globalCtx, EFFECT_SS_SBN, 128, &sp84.unk_00);
            }
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    sp50 =
        (this->actor.params != ENARROW_0) && (this->actor.params < ENARROW_8) && (this->collider.base.atFlags & AT_HIT);

    if (sp50 || (this->unk_262 != 0)) {
        if (this->actor.params >= ENARROW_6) {
            if (sp50) {
                this->actor.world.pos.x = (this->actor.world.pos.x + this->actor.prevPos.x) * 0.5f;
                this->actor.world.pos.y = (this->actor.world.pos.y + this->actor.prevPos.y) * 0.5f;
                this->actor.world.pos.z = (this->actor.world.pos.z + this->actor.prevPos.z) * 0.5f;
            }

            if (this->actor.params == ENARROW_8) {
                iREG(50) = -1;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_M_FIRE1, this->actor.world.pos.x,
                            this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, this->actor.speedXZ == 0.0f);
                sp82 = NA_SE_IT_DEKU;
            } else {
                sp82 = NA_SE_IT_SLING_REFLECT;
            }
            EffectSsStone1_Spawn(globalCtx, &this->actor.world.pos, 0);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, sp82);
            Actor_MarkForDeath(&this->actor);
        } else {
            EffectSsHitMark_SpawnCustomScale(globalCtx, 0, 150, &this->actor.world.pos);

            if (sp50 && (this->collider.info.atHitInfo->elemType != ELEMTYPE_UNK4)) {
                sp7C = this->collider.base.at;

                if ((sp7C->update != NULL) && !(this->collider.base.atFlags & AT_BOUNCED) && (sp7C->flags & 0x4000)) {
                    this->unk_264 = sp7C;
                    func_8088A894(this, globalCtx);
                    Math_Vec3f_Diff(&sp7C->world.pos, &this->actor.world.pos, &this->unk_268);
                    sp7C->flags |= 0x8000;
                    this->collider.base.atFlags &= ~AT_HIT;
                    this->actor.speedXZ *= 0.5f;
                    this->actor.velocity.y *= 0.5f;
                } else {
                    this->unk_261 |= 1;
                    this->unk_261 |= 2;
                    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
                    func_8088A7D8(globalCtx, this);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_HOOKSHOT_STICK_CRE);
                }
            } else if (this->unk_262 != 0) {
                this->actionFunc = func_8088B630;
                Animation_PlayOnce(&this->arrow.skelAnime, &gameplay_keep_Anim_0128BC);
                if (this->actor.params >= ENARROW_0) {
                    this->unk_260 = 60;
                } else {
                    this->unk_260 = 20;
                }
                if ((this->actor.params >= ENARROW_3) && (this->actor.params < ENARROW_6)) {
                    this->actor.draw = NULL;
                }
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_ARROW_STICK_OBJ);
                this->unk_261 |= 1;
            }
        }
    } else {
        func_8088AA98(this, globalCtx);
        if (this->actor.params == ENARROW_7) {
            if (this->bubble.unk_149 == 0) {
                sp78 = sqrtf(SQ(this->actor.speedXZ) + SQ(this->actor.velocity.y));
                sp74 = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
                temp_f12_2 = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;

                this->actor.prevPos.x = this->actor.world.pos.x - (sp74 * (10.0f / sp78));
                this->actor.prevPos.y = this->actor.world.pos.y - (this->actor.velocity.y * (10.0f / sp78));
                this->actor.prevPos.z = this->actor.world.pos.z - (temp_f12_2 * (10.0f / sp78));

                this->bubble.unk_149 = 1;
            }

            if (Math_StepToF(&this->bubble.unk_144, 1.0f, 0.4f)) {
                this->unk_260 = 0;
            } else {
                this->bubble.unk_14A += (s16)(this->bubble.unk_144 * (500.0f + Rand_ZeroFloat(1400.0f)));
                this->actor.world.rot.x += (s16)(500.0f * Math_SinS(this->bubble.unk_14A));
                this->actor.shape.rot.x = this->actor.world.rot.x;

                this->bubble.unk_14C += (s16)(this->bubble.unk_144 * (500.0f + Rand_ZeroFloat(1400.0f)));
                this->actor.world.rot.y += (s16)(500.0f * Math_SinS(this->bubble.unk_14C));

                this->actor.shape.rot.y = this->actor.world.rot.y;

                func_8088A514(this);
            }
            func_800B9010(&this->actor, NA_SE_IT_DEKUNUTS_BUBLE_SHOT_LEVEL - SFX_FLAG);
        } else if (this->unk_260 < 7) {
            this->actor.gravity = -0.4f;
        }

        Math_Vec3f_Copy(&this->unk_228, &this->actor.world.pos);

        if (this->actor.speedXZ == 0.0f) {
            this->actor.velocity.y -= 1.0f;
            if (this->actor.velocity.y < this->actor.terminalVelocity) {
                this->actor.velocity.y = this->actor.terminalVelocity;
            }
            Actor_UpdatePos(&this->actor);
        } else {
            Actor_MoveWithGravity(&this->actor);
        }

        this->unk_262 = BgCheck_ProjectileLineTest(&globalCtx->colCtx, &this->actor.prevPos, &this->actor.world.pos,
                                                   &sp9C, &this->actor.wallPoly, true, true, true, true, &spA8);
        if (this->unk_262 != 0) {
            func_800B90AC(globalCtx, &this->actor, this->actor.wallPoly, spA8, &sp9C);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp9C);
            this->actor.wallBgId = spA8;
        }

        if (this->actor.params < ENARROW_6) {
            this->actor.shape.rot.x = Math_FAtan2F(this->actor.speedXZ, -this->actor.velocity.y);
        }
    }

    if (this->unk_264 != NULL) {
        if (this->unk_264->update != NULL) {
            s32 pad;

            Math_Vec3f_Sum(&this->unk_228, &this->unk_268, &sp60);
            Math_Vec3f_Sum(&this->actor.world.pos, &this->unk_268, &sp54);

            if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &sp60, &sp54, &sp9C, &spAC, true, true, true, true,
                                        &spA8)) {
                this->unk_264->world.pos.x = ((sp54.x <= sp9C.x) ? 1.0f : -1.0f) + sp9C.x;
                this->unk_264->world.pos.y = ((sp54.y <= sp9C.y) ? 1.0f : -1.0f) + sp9C.y;
                this->unk_264->world.pos.z = ((sp54.z <= sp9C.z) ? 1.0f : -1.0f) + sp9C.z;

                Math_Vec3f_Diff(&this->unk_264->world.pos, &this->actor.world.pos, &this->unk_268);
                this->unk_264->flags &= ~0x8000;
                this->unk_264 = NULL;
            } else {
                Math_Vec3f_Sum(&this->actor.world.pos, &this->unk_268, &this->unk_264->world.pos);
            }

            if ((this->unk_262 != 0) && (this->unk_264 != NULL)) {
                this->unk_264->flags &= ~0x8000;
                this->unk_264 = NULL;
            }
        } else {
            this->unk_264 = NULL;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088ACE0.s")
#endif

void func_8088B630(EnArrow* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->arrow.skelAnime);

    if (this->actor.wallBgId != BG_ACTOR_MAX) {
        BgCheck2_UpdateActorAttachedToMesh(&globalCtx->colCtx, this->actor.wallBgId, &this->actor);
    }

    if (DECR(this->unk_260) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_8088B6B0(EnArrow* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->arrow.skelAnime);
    Actor_MoveWithGravity(&this->actor);
    func_8088AA98(this, globalCtx);

    if (DECR(this->unk_260) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnArrow_Update(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_8088C2CC = { 0.0f, 0.5f, 0.0f };
    static Vec3f D_8088C2D8 = { 0.0f, 0.5f, 0.0f };
    static Color_RGBA8 D_8088C2E4 = { 255, 255, 100, 255 };
    static Color_RGBA8 D_8088C2E8 = { 255, 50, 0, 0 };
    s32 pad;
    EnArrow* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    if ((this->unk_263 != 0) ||
        ((this->actor.params >= ENARROW_0) && ((this->actor.params == ENARROW_7) || (player->unk_D57 != 0))) ||
        !func_80123358(globalCtx, player)) {
        this->actionFunc(this, globalCtx);
    }

    if ((this->actor.params >= ENARROW_3) && (this->actor.params < ENARROW_6)) {
        s16 sp44[] = { ACTOR_ARROW_FIRE, ACTOR_ARROW_ICE, ACTOR_ARROW_LIGHT };

        if (this->actor.child == NULL) {
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, sp44[this->actor.params - ENARROW_3],
                               this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
        }
    } else if (this->actor.params == ENARROW_0) {
        func_800B0EB0(globalCtx, &this->unk_234, &D_8088C2CC, &D_8088C2D8, &D_8088C2E4, &D_8088C2E8, 100, 0, 8);
    }
    Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.prevPos);
}

typedef struct {
    /* 0x00 */ Vec3f unk_00[2];
    /* 0x18 */ Vec3f unk_18[2][2];
    /* 0x48 */ Vec3f unk_48;
} EnArrowUnkStruct; // size = 0x54

void func_8088B88C(GlobalContext* globalCtx, EnArrow* this, EnArrowUnkStruct* arg2) {
    Vec3f* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s32 sp30;

    Matrix_MultiplyVector3fByState(&arg2->unk_48, &this->unk_234);
    if (func_8088ACE0 == this->actionFunc) {
        if (this->unk_244 == 0) {
            sp4C = arg2->unk_00;
        } else {
            sp4C = arg2->unk_18[globalCtx->gameplayFrames % 2];
        }
        Matrix_MultiplyVector3fByState(&sp4C[0], &sp40);
        Matrix_MultiplyVector3fByState(&sp4C[1], &sp34);
        if (this->actor.params < ENARROW_8) {
            sp30 = this->actor.params < ENARROW_6;
            if (this->unk_264 == 0) {
                sp30 &= func_80126440(globalCtx, &this->collider.base, &this->unk_244, &sp40, &sp34);
            } else if (sp30 && (sp40.x == this->unk_248) && (sp40.y == this->unk_24C) && (sp40.z == this->unk_250) &&
                       (sp34.x == this->unk_254) && (sp34.y == this->unk_258) && (sp34.z == this->unk_25C)) {
                sp30 = false;
            }
            if (sp30) {
                EffectBlure_AddVertex(Effect_GetByIndex(this->unk_240), &sp40, &sp34);
            }
        }
    }
}

void EnArrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static EnArrowUnkStruct D_8088C2EC[] = {
        {
            {
                { 400.0f, 400.0f, 0.0f },
                { -400.0f, 400.0f, 0.0f },
            },
            {
                {
                    { 400.0f, 400.0f, 1500.0f },
                    { -400.0f, 400.0f, 1500.0f },
                },
                {
                    { 400.0f, 400.0f, 1500.0f },
                    { -400.0f, 400.0f, 1500.0f },
                },
            },
            { 0.0f, 0.0f, -300.0f },
        },
        {
            {
                { 20.0f, -20.0f, 20.0f },
                { 20.0f, -20.0f, 20.0f },
            },
            {
                {
                    { 20.0f, -20.0f, 20.0f },
                    { -20.0f, 20.0f, 20.0f },
                },
                {
                    { -20.0f, -20.0f, 20.0f },
                    { 20.0f, 20.0f, 20.0f },
                },
            },
            { 0.0f, 0.0f, 20.0f },
        },
    };
    EnArrow* this = THIS;
    s32 phi_v0;

    if (this->actor.params < ENARROW_6) {
        func_8012C28C(globalCtx->state.gfxCtx);
        SkelAnime_DrawLod(globalCtx, this->arrow.skelAnime.skeleton, this->arrow.skelAnime.jointTable, NULL, NULL,
                          &this->actor, this->actor.projectedPos.z < 160.0f ? 0 : 1);
    } else if (this->actor.params == ENARROW_7) {
        s32 spA4 = 255 - (s32)(this->bubble.unk_144 * 4.0f);
        f32 spA0 = (this->actor.speedXZ * 0.1f) + 1.0f;
        f32 sp9C = (1.0f / spA0);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (this->bubble.unk_149 >= 0) {
            func_8088B88C(globalCtx, this, &D_8088C2EC[1]);
        } else {
            Collider_ResetQuadAT(globalCtx, &this->collider.base);
        }

        sp9C *= 0.002f;
        spA0 *= 0.002f;

        Matrix_Scale(this->bubble.unk_144 * sp9C, this->bubble.unk_144 * sp9C, this->bubble.unk_144 * spA0,
                     MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, 0.0f, 460.0f, MTXMODE_APPLY);

        if (this->actor.speedXZ == 0.0f) {
            func_800B8118(&this->actor, globalCtx, MTXMODE_NEW);

            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_06F380);
            gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
            gDPSetCombineLERP(POLY_XLU_DISP++, TEXEL1, 0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                              COMBINED, 0, ENVIRONMENT, 0, COMBINED, 0, ENVIRONMENT, 0);
            gDPSetEnvColor(POLY_XLU_DISP++, 230, 225, 150, spA4);

            Matrix_NormalizeXYZ(&gIdentityMtxF);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPMatrix(POLY_XLU_DISP++, &D_01000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_06F9F0);
        } else {
            func_800B8050(&this->actor, globalCtx, MTXMODE_NEW);

            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_06F380);
            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL1, 0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                              COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x7F, 230, 225, 150, 255);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_06FAE0);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return;
    } else if (this->actor.speedXZ != 0.0f) {
        u8 sp63 = (Math_CosS(this->unk_260 * 5000) * 127.5f) + 127.5f;
        f32 sp5C;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C240(globalCtx->state.gfxCtx);

        gSPClearGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);

        if (this->actor.params == ENARROW_6) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 255, 255, sp63);
            sp5C = 50.0f;
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 12, 0, 0, 255);
            gDPSetEnvColor(POLY_XLU_DISP++, 250, 250, 0, sp63);
            sp5C = 150.0f;
        }

        Matrix_StatePush();
        Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

        if (this->actor.speedXZ == 0.0f) {
            phi_v0 = 0;
        } else {
            phi_v0 = (globalCtx->gameplayFrames % 256) * 4000;
        }

        Matrix_InsertZRotation_s(phi_v0, MTXMODE_APPLY);
        Matrix_Scale(sp5C, sp5C, sp5C, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_054A90);

        Matrix_StatePop();
        Matrix_RotateY(this->actor.world.rot.y, MTXMODE_APPLY);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else if (this->actor.velocity.y != 0.0f) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_058BA0);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    func_8088B88C(globalCtx, this, &D_8088C2EC[0]);
}
