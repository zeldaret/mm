/*
 * File: z_en_tanron5.c
 * Overlay: ovl_En_Tanron5
 * Description: Destructible props in Twinmold's arena
 */

#include "z_en_tanron5.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_boss02/object_boss02.h"
#include "overlays/actors/ovl_Boss_02/z_boss_02.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnTanron5*)thisx)

void EnTanron5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BE5818(Actor* thisx, GlobalContext* globalCtx);
void func_80BE5C10(Actor* thisx, GlobalContext* globalCtx);

s32 D_80BE5D80 = 0;

const ActorInit En_Tanron5_InitVars = {
    ACTOR_EN_TANRON5,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(EnTanron5),
    (ActorFunc)EnTanron5_Init,
    (ActorFunc)EnTanron5_Destroy,
    (ActorFunc)EnTanron5_Update,
    (ActorFunc)EnTanron5_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ALL,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 70, 450, 0, { 0, 0, 0 } },
};

f32 D_80BE5DD0 = 1.0f;

Vec2s D_80BE5DD4[] = {
    { 0x4B0, 0x9C4 },  { -0x4B0, 0x9C4 },  { 0x4B0, -0x9C4 },  { -0x4B0, -0x9C4 }, { 0x9C4, 0x4B0 },
    { -0x9C4, 0x4B0 }, { 0x9C4, -0x4B0 },  { -0x9C4, -0x4B0 }, { 0x3E8, 0x3E8 },   { -0x3E8, 0x3E8 },
    { 0x3E8, -0x3E8 }, { -0x3E8, -0x3E8 }, { 0x000, -0x3E8 },  { 0x000, 0x3E8 },   { 0x3E8, 0x000 },
    { -0x3E8, 0x000 }, { 0x000, -0x7D0 },  { 0x000, 0x7D0 },   { 0x7D0, 0x000 },   { -0x7D0, 0x000 },
};

Gfx* D_80BE5E24[] = {
    object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18,
    object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18,
    object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18, object_boss02_DL_007D18,
    object_boss02_DL_006FD0, object_boss02_DL_006FD0, object_boss02_DL_006FD0, object_boss02_DL_006FD0,
    object_boss02_DL_006FD0, object_boss02_DL_006FD0, object_boss02_DL_006FD0, object_boss02_DL_006FD0,
};

f32 D_80BE5E74[] = {
    0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f,
    0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f,
};

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ u8 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ UNK_TYPE1 unk28[0x4];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ UNK_TYPE1 unk2E[0x6];
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} EnTanron5Effect; // size = 0x3C

void func_80BE4930(EnTanron5Effect* effect, Vec3f* arg1, f32 arg2) {
    s16 i;

    for (i = 0; i < 150; i++, effect++) {
        if (effect->unk_24 == 0) {
            effect->unk_24 = 1;

            effect->unk_00 = *arg1;

            effect->unk_0C = randPlusMinusPoint5Scaled(10.0f);
            effect->unk_10 = Rand_ZeroFloat(2.0f) + 3.0f;
            effect->unk_14 = randPlusMinusPoint5Scaled(10.0f);

            effect->unk_18.y = -0.15f;
            effect->unk_18.x = 0.0f;
            effect->unk_18.z = 0.0f;

            effect->unk_2C = Rand_ZeroFloat(100.0f) + 200.0f;
            effect->unk_26 = 0;
            effect->unk_34 = arg2;
            effect->unk_38 = 2.0f * arg2;
            break;
        }
    }
}

void func_80BE4A2C(EnTanron5Effect* effect, Vec3f* arg1, f32 arg2) {
    s16 i;

    for (i = 0; i < 150; i++, effect++) {
        if (effect->unk_24 == 0) {
            effect->unk_24 = 2;

            effect->unk_00 = *arg1;

            effect->unk_0C = randPlusMinusPoint5Scaled(30.0f);
            effect->unk_10 = Rand_ZeroFloat(7.0f);
            effect->unk_14 = randPlusMinusPoint5Scaled(30.0f);

            effect->unk_18.y = -0.3f;
            effect->unk_18.x = 0.0f;
            effect->unk_18.z = 0.0f;

            effect->unk_2C = Rand_ZeroFloat(70.0f) + 150.0f;
            effect->unk_26 = 0;
            effect->unk_34 = arg2;
            effect->unk_38 = 2.0f * arg2;
            break;
        }
    }
}

void EnTanron5_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron5* this = THIS;

    if (ENTANRON5_GET(&this->actor) >= ENTANRON5_100) {
        D_80BE5D80++;
        if (D_80BE5D80 > 60) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        this->unk_198 = randPlusMinusPoint5Scaled(0x2000);
        this->unk_19A = randPlusMinusPoint5Scaled(0x2000);

        if (ENTANRON5_GET(&this->actor) < ENTANRON5_107) {
            Actor_SetScale(&this->actor, (Rand_ZeroFloat(0.025f) + 0.085f) * D_80BE5DD0);
        } else {
            Actor_SetScale(&this->actor, (Rand_ZeroFloat(0.015f) + 0.01f) * D_80BE5DD0);
        }

        this->actor.speedXZ = (Rand_ZeroFloat(10.0f) + 10.0f) * D_80BE5DD0;
        this->actor.velocity.y = (Rand_ZeroFloat(10.0f) + 15.0f) * D_80BE5DD0;
        this->actor.gravity = -2.5f * D_80BE5DD0;
        this->actor.terminalVelocity = -1000.0f * D_80BE5DD0;
        this->actor.update = func_80BE5818;

        if (ENTANRON5_GET(&this->actor) >= ENTANRON5_110) {
            this->actor.draw = func_80BE5C10;
            this->unk_1A0 = Rand_ZeroFloat(1.999f);
            Actor_SetScale(&this->actor, D_80BE5DD0 * 0.03f);
            this->unk_144 = 250;
            this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z = 0;
        } else {
            this->unk_148 = object_boss02_DL_007A88;
            this->unk_144 = 150;
        }
    } else if (ENTANRON5_GET(&this->actor) == ENTANRON5_0) {
        EnTanron5* child;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(D_80BE5E74); i++) {
            child =
                (EnTanron5*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_TANRON5, D_80BE5DD4[i].x,
                                        this->actor.world.pos.y, D_80BE5DD4[i].z, 0, Rand_ZeroFloat(0x10000), 0, i + 1);

            child->actor.parent = this->actor.parent;
            child->unk_19C = D_80BE5E74[i];

            Actor_SetScale(&child->actor, child->unk_19C);

            child->unk_148 = D_80BE5E24[i];
            if (child->unk_148 == object_boss02_DL_006FD0) {
                child->actor.shape.rot.y = 0;
            }

            Collider_InitAndSetCylinder(globalCtx, &child->collider, &child->actor, &sCylinderInit);
        }

        Actor_MarkForDeath(&this->actor);
    } else {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 150.0f, 100.0f, 4);
        this->actor.world.pos.y = this->actor.floorHeight + -20.0f;
    }
}

void EnTanron5_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron5* this = THIS;

    if (ENTANRON5_GET(&this->actor) >= ENTANRON5_100) {
        D_80BE5D80--;
    }
}

void EnTanron5_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTanron5* this = THIS;
    Boss02* boss02 = (Boss02*)this->actor.parent;
    Player* player = GET_PLAYER(globalCtx2);
    s32 i;
    s32 phi_v0;
    s32 spC4;
    Vec3f spB8;

    if (this->unk_1A0 >= 3) {
        this->unk_1A0++;
        Actor_SetScale(&this->actor, 0.0f);
        if (this->unk_1A0 >= 40) {
            Actor_MarkForDeath(&this->actor);
        }
        return;
    } else {
        // required
    }

    if (this->unk_144 != 0) {
        this->unk_144--;
    }

    if (boss02->actor.update != NULL) {
        D_80BE5DD0 = boss02->unk_01AC;
    } else {
        D_80BE5DD0 = 1.0f;
    }

    Actor_SetScale(&this->actor, this->unk_19C * D_80BE5DD0);

    if (this->unk_148 == object_boss02_DL_007D18) {
        this->collider.dim.radius = 65.0f * D_80BE5DD0;
        this->collider.dim.height = 380.0f * D_80BE5DD0;
    } else if (this->unk_1A0 == 0) {
        this->collider.dim.radius = 85.0f * D_80BE5DD0;
        this->collider.dim.height = 200.0f * D_80BE5DD0;
    } else if (this->unk_1A0 == 1) {
        this->collider.dim.radius = 95.0f * D_80BE5DD0;
        this->collider.dim.height = 100.0f * D_80BE5DD0;
    } else if (this->unk_1A0 == 2) {
        this->collider.dim.radius = 95.0f * D_80BE5DD0;
        this->collider.dim.height = 30.0f * D_80BE5DD0;
    }

    if (this->unk_144 == 0) {
        if (this->collider.base.acFlags & AC_HIT) {
            ColliderInfo* acHitInfo = this->collider.info.acHitInfo;
            Actor* ac = this->collider.base.ac;

            this->collider.base.acFlags &= ~AC_HIT;
            spC4 = 10;

            if (Play_InCsMode(globalCtx)) {
                this->unk_144 = 1;
            } else {
                this->unk_144 = 5;
                spC4 = (s32)Rand_ZeroFloat(2.99f) + 10;
            }

            if ((KREG(19) != 0) || ((acHitInfo->toucher.dmgFlags & 0x05000202) && (D_80BE5DD0 < 0.5f)) ||
                (ac->id == ACTOR_BOSS_02)) {
                if (this->unk_148 == object_boss02_DL_007D18) {
                    Math_Vec3f_Copy(&spB8, &this->actor.world.pos);
                    spB8.y += D_80BE5DD0 * 300.0f;

                    for (i = 3; i < spC4; i++) {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_TANRON5, spB8.x, spB8.y, spB8.z,
                                    Rand_ZeroFloat(0x10000), Rand_ZeroFloat(0x10000), 0, i + 100);
                    }

                    for (i = 0; i < 6; i++) {
                        func_80BE4A2C(globalCtx->specialEffects, &spB8, Rand_ZeroFloat(3.0f) + 6.0f);
                    }

                    this->actor.world.pos.y -= D_80BE5DD0 * 130.0f;
                } else {
                    f32 spAC;
                    f32 spA8;
                    Vec3f sp9C;

                    if (this->unk_1A0 == 0) {
                        spAC = 180.0f;
                        this->unk_19C *= 1.4f;
                    } else if (this->unk_1A0 == 1) {
                        spAC = 230.0f;
                        this->unk_19C *= 1.37f;
                    } else if (this->unk_1A0 == 2) {
                        spAC = 780.0f;
                        this->unk_19C *= 1.5f;
                    }

                    this->actor.world.pos.y -= D_80BE5DD0 * spAC;
                    Actor_SetScale(&this->actor, this->unk_19C * D_80BE5DD0);
                    Math_Vec3f_Copy(&spB8, &this->actor.world.pos);

                    for (i = 0; i < spC4; i++) {
                        if (this->unk_1A0 == 0) {
                            spA8 = 100.0f;
                            spAC = 180.0f;
                        } else if (this->unk_1A0 == 1) {
                            spA8 = 200.0f;
                            spAC = 100.0f;
                        } else if (this->unk_1A0 == 2) {
                            spA8 = 250.0f;
                            spAC = 50.0f;
                        }

                        sp9C.x = (randPlusMinusPoint5Scaled(spA8) * D_80BE5DD0) + spB8.x;
                        sp9C.z = (randPlusMinusPoint5Scaled(spA8) * D_80BE5DD0) + spB8.z;
                        sp9C.y = this->actor.floorHeight + (spAC * D_80BE5DD0);

                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_TANRON5, sp9C.x, sp9C.y, sp9C.z,
                                    Rand_ZeroFloat(0x10000), Rand_ZeroFloat(0x10000), 0, i + 100);

                        if (i < 8) {
                            func_80BE4A2C(globalCtx->specialEffects, &sp9C, Rand_ZeroFloat(3.0f) + 6.0f);
                        }
                    }
                }

                if (Rand_ZeroOne() < 0.333f) {
                    phi_v0 = 0x4000;
                } else if (Rand_ZeroOne() < 0.5f) {
                    phi_v0 = -0x8000;
                } else {
                    phi_v0 = -0x4000;
                }

                this->actor.shape.rot.y += phi_v0;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BIG_BOMB_EXPLOSION);
                func_800BC848(&this->actor, globalCtx, 4, 4);
                this->unk_1A0++;
            } else {
                Vec3f sp90;
                ColliderInfo* info = this->collider.info.acHitInfo;

                sp90.x = info->bumper.hitPos.x;
                sp90.y = info->bumper.hitPos.y;
                sp90.z = info->bumper.hitPos.z;

                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
                CollisionCheck_SpawnShieldParticlesMetal(globalCtx, &sp90);
            }
        }
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    if (this->unk_148 == object_boss02_DL_006FD0) {
        this->collider.dim.pos.y = this->actor.floorHeight;
    }

    if ((this->unk_148 == object_boss02_DL_007D18) || (D_80BE5DD0 < 0.5f)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        f32 xDiff = player->actor.world.pos.x - this->actor.world.pos.x;
        f32 yDiff = player->actor.world.pos.z - this->actor.world.pos.z;

        if ((fabsf(xDiff) < 120.0f) && (fabsf(yDiff) < 120.0f)) {
            if (fabsf(yDiff) < fabsf(xDiff)) {
                if (xDiff > 0.0f) {
                    player->actor.prevPos.x = player->actor.world.pos.x = this->actor.world.pos.x + 120.0f;
                } else {
                    player->actor.prevPos.x = player->actor.world.pos.x = this->actor.world.pos.x - 120.0f;
                }
            } else if (yDiff > 0.0f) {
                player->actor.prevPos.z = player->actor.world.pos.z = this->actor.world.pos.z + 120.0f;
            } else {
                player->actor.prevPos.z = player->actor.world.pos.z = this->actor.world.pos.z - 120.0f;
            }
        }
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80BE5818(Actor* thisx, GlobalContext* globalCtx2) {
    f32 sp6C;
    s32 i;
    Vec3f sp5C;
    EnTanron5* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    if ((ENTANRON5_GET(&this->actor) < ENTANRON5_110) && (this->unk_1A0 != 0)) {
        this->unk_1A0++;
        this->actor.world.pos.y -= 2.0f * D_80BE5DD0;
        if (this->unk_1A0 == 40) {
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    if (DECR(this->unk_144) == 0) {
        Actor_MarkForDeath(&this->actor);
    }

    if (this->actor.speedXZ > 0.02f) {
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 150.0f, 100.0f, 4);
    }

    if (ENTANRON5_GET(&this->actor) < ENTANRON5_110) {
        this->actor.shape.rot.x += this->unk_198;
        this->actor.shape.rot.y += this->unk_19A;
        sp6C = 1225.0f;

        if (this->actor.bgCheckFlags & 1) {
            if (ENTANRON5_GET(&this->actor) < ENTANRON5_108) {
                Math_Vec3f_Copy(&sp5C, &this->actor.world.pos);
                sp5C.y = this->actor.floorHeight;

                for (i = 0; i < 4; i++) {
                    func_80BE4930(globalCtx->specialEffects, &sp5C, Rand_ZeroFloat(1.0f) + 2.0f);
                }
                this->unk_1A0++;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
        }
    } else {
        sp6C = 400.0f;
        this->unk_198 += 0x2000;
        if (this->actor.bgCheckFlags & 1) {
            this->unk_198 = 0;
            this->actor.speedXZ = 0.0f;
        }
    }

    if (this->unk_1A1 == 0) {
        if ((D_80BE5DD0 > 0.5f) &&
            ((ENTANRON5_GET(&this->actor) < ENTANRON5_108) || (ENTANRON5_GET(&this->actor) >= ENTANRON5_110))) {
            Player* player = GET_PLAYER(globalCtx);
            Vec3f temp;

            temp.x = player->actor.world.pos.x - this->actor.world.pos.x;
            temp.y = (player->actor.world.pos.y + 10.0f) - this->actor.world.pos.y;
            temp.z = player->actor.world.pos.z - this->actor.world.pos.z;

            if (SQXYZ(temp) < sp6C) {
                if (ENTANRON5_GET(&this->actor) >= ENTANRON5_110) {
                    if (this->unk_1A0 == 0) {
                        Item_Give(globalCtx, ITEM_ARROWS_10);
                    } else {
                        Item_Give(globalCtx, ITEM_MAGIC_LARGE);
                    }
                    Actor_MarkForDeath(&this->actor);
                    play_sound(NA_SE_SY_GET_ITEM);
                } else {
                    this->unk_1A1 = 20;
                    func_800B8D50(globalCtx, NULL, 5.0f, this->actor.world.rot.y, 0.0f, 8);
                }
            }
        }
    } else {
        this->unk_1A1--;
    }
}

void EnTanron5_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron5* this = THIS;

    if ((-500.0f * D_80BE5DD0) < this->actor.projectedPos.z) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, this->unk_148);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_80BE5C10(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron5* this = THIS;
    TexturePtr texture;
    s32 phi_v0;

    if ((this->unk_144 > 50) || (this->unk_144 & 1)) {
        phi_v0 = true;
    } else {
        phi_v0 = false;
    }

    if (((-500.0f * D_80BE5DD0) < this->actor.projectedPos.z) && phi_v0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        if (this->unk_1A0 == 0) {
            texture = gameplay_keep_Tex_05BEF0;
        } else {
            texture = gameplay_keep_Tex_0617C0;
        }

        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(texture));

        Matrix_InsertTranslation(0.0f, 200.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_198, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_05F6F0);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
