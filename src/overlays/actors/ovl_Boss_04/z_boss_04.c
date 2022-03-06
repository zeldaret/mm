/*
 * File: z_boss_04.c
 * Overlay: ovl_Boss_04
 * Description: Wart
 */

#include "z_boss_04.h"
#include "objects/object_boss04/object_boss04.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss04*)thisx)

void Boss04_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809EC544(Boss04* this);
void func_809EC568(Boss04* this, GlobalContext* globalCtx);
void func_809ECD00(Boss04* this, GlobalContext* globalCtx);
void func_809ECD18(Boss04* this, GlobalContext* globalCtx);
void func_809ECEF4(Boss04* this);
void func_809ECF58(Boss04* this, GlobalContext* globalCtx);
void func_809ED224(Boss04* this);
void func_809ED2A0(Boss04* this, GlobalContext* globalCtx);

static u8 D_809EE4D0;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(2, 0xF),
    /* Goron pound    */ DMG_ENTRY(2, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(2, 0xF),
    /* Zora punch     */ DMG_ENTRY(2, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit Boss_04_InitVars = {
    ACTOR_BOSS_04,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(Boss04),
    (ActorFunc)Boss04_Init,
    (ActorFunc)Boss04_Destroy,
    (ActorFunc)Boss04_Update,
    (ActorFunc)Boss04_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit1[1] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 50 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[1] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 70 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit2,
};

void func_809EC040(s32 index, ColliderJntSph* collider, Vec3f* arg2) {
    collider->elements[index].dim.worldSphere.center.x = arg2->x;
    collider->elements[index].dim.worldSphere.center.y = arg2->y;
    collider->elements[index].dim.worldSphere.center.z = arg2->z;
    collider->elements[index].dim.worldSphere.radius =
        collider->elements[index].dim.modelSphere.radius * collider->elements[index].dim.scale;
}

void Boss04_Init(Actor* thisx, GlobalContext* globalCtx2) {
    static Vec3f D_809EE1F8[] = {
        { -1000.0f, 0.0f, 0.0f },
        { 1000.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, -1000.0f },
        { 0.0f, 0.0f, 1000.0f },
    };
    GlobalContext* globalCtx = globalCtx2;
    Boss04* this = THIS;
    s32 i;
    CollisionPoly* spC0;
    Vec3f spB4;
    Vec3f spA8;
    s32 spA4;
    f32 phi_f20;
    f32 phi_f24;
    Vec3f sp90;
    s16 phi_s0_2;
    s32 pad;

    if (Flags_GetClear(globalCtx, globalCtx->roomCtx.currRoom.num)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.params = 0x64;
    Actor_SetScale(&this->actor, 0.1f);
    this->actor.targetMode = 5;
    this->actor.hintId = 0x19;
    this->actor.colChkInfo.health = 20;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->unk_700 = 1.0f;
    this->unk_6FC = 1.0f;
    this->unk_6F8 = 1.0f;
    Collider_InitAndSetJntSph(globalCtx, &this->collider1, &this->actor, &sJntSphInit1, this->collider1Elements);
    Collider_InitAndSetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit2, this->collider2Elements);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_boss04_Skel_0045E8, &object_boss04_Anim_00004C,
                       this->jointTable, this->morphtable, 9);
    spA8.y = this->actor.world.pos.y + 200.0f;

    for (i = 0; i < ARRAY_COUNT(D_809EE1F8); i++) {
        spA8.x = D_809EE1F8[i].x + this->actor.world.pos.x;
        spA8.z = D_809EE1F8[i].z + this->actor.world.pos.z;
        if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &spA8, &spB4, &spC0, true, false, false,
                                    true, &spA4)) {
            if (i == 0) {
                this->unk_6D8 = spB4.x;
            } else if (i == 1) {
                this->unk_6DC = spB4.x;
            } else if (i == 2) {
                this->unk_6E0 = spB4.z;
            } else if (i == 3) {
                this->unk_6E4 = spB4.z;
            }
        }
    }

    this->unk_6E8 = this->unk_6D8 + ((this->unk_6DC - this->unk_6D8) * 0.5f);
    this->unk_6F0 = this->unk_6E0 + ((this->unk_6E4 - this->unk_6E0) * 0.5f);
    this->actor.world.pos.x = this->unk_6E8;
    this->actor.world.pos.z = this->unk_6F0;
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 35.0f, 60.0f, 60.0f, 4);

    if ((KREG(64) != 0) || (gSaveContext.eventInf[6] & 1)) {
        func_809ECD00(this, globalCtx);
        this->actor.world.pos.y = this->actor.floorHeight + 160.0f;
        phi_f24 = this->actor.floorHeight;
        D_809EE4D0 = KREG(41) + 50;
    } else {
        func_809EC544(this);
        this->actor.world.pos.y = KREG(70) + (this->actor.floorHeight + 590.0f);
        phi_f24 = KREG(71) + (this->actor.floorHeight + 550.0f);
    }

    phi_f20 = 110.0f;
    this->unk_6F6 = 82;
    phi_s0_2 = 0;
    for (i = 0; i < 82; i++) {
        Matrix_RotateY(phi_s0_2, MTXMODE_NEW);
        Matrix_GetStateTranslationAndScaledZ(phi_f20, &sp90);
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TANRON2, this->unk_6E8 + sp90.x,
                           phi_f24, this->unk_6F0 + sp90.z, 0, 0, 0, i);
        phi_f20 += 2.5f;
        phi_s0_2 += 0x1300;
    }

    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TANRON2, this->actor.world.pos.x,
                       this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 100);
}

void Boss04_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_809EC544(Boss04* this) {
    this->actionFunc = func_809EC568;
    this->actor.flags &= ~ACTOR_FLAG_1;
}

void func_809EC568(Boss04* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 x;
    f32 y;
    f32 z;
    s32 pad;

    this->unk_704++;
    this->unk_1FE = 15;
    if ((this->unk_708 != 0) && (this->unk_708 < 10)) {
        this->actor.world.pos.y = (Math_SinS(this->unk_1F4 * 512) * 10.0f) + (this->actor.floorHeight + 160.0f);
        Matrix_RotateY(this->actor.yawTowardsPlayer, MTXMODE_NEW);
    }

    switch (this->unk_708) {
        case 0:
            this->unk_2C8 = 50;
            this->unk_2D0 = 2000.0f;
            if ((player->stateFlags1 & 0x100000) && (this->actor.projectedPos.z > 0.0f) &&
                (fabsf(this->actor.projectedPos.x) < 300.0f) && (fabsf(this->actor.projectedPos.y) < 300.0f)) {
                if ((this->unk_704 >= 15) && (ActorCutscene_GetCurrentIndex() == -1)) {
                    Actor* boss;

                    this->unk_708 = 10;
                    this->unk_704 = 0;
                    Cutscene_Start(globalCtx, &globalCtx->csCtx);
                    this->unk_70A = Play_CreateSubCamera(globalCtx);
                    Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
                    Play_CameraChangeStatus(globalCtx, this->unk_70A, 7);
                    func_800B7298(globalCtx, &this->actor, 7);
                    player->actor.world.pos.x = this->unk_6E8;
                    player->actor.world.pos.z = this->unk_6F0 + 410.0f;
                    player->actor.shape.rot.y = 0x7FFF;
                    player->actor.world.rot.y = player->actor.shape.rot.y;
                    Math_Vec3f_Copy(&this->unk_70C, &player->actor.world.pos);
                    this->unk_70C.y += 100.0f;
                    Math_Vec3f_Copy(&this->unk_718, &this->actor.world.pos);
                    func_8016566C(150);
                    this->unk_744 = 60.0f;

                    boss = globalCtx->actorCtx.actorLists[ACTORCAT_BOSS].first;
                    while (boss != NULL) {
                        if (boss->id == ACTOR_EN_WATER_EFFECT) {
                            Actor_MarkForDeath(boss);
                        }
                        boss = boss->next;
                    }
                }
            } else {
                this->unk_704 = 0;
            }
            break;

        case 10:
            if (this->unk_704 == 3) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_DEMO_EYE);
                this->unk_74A = 1;
            }
            this->unk_2D0 = 10000.0f;
            this->unk_2C8 = 300;
            Math_ApproachF(&this->unk_744, 20.0f, 0.3f, 11.0f);
            if (this->unk_704 == 40) {
                this->unk_708 = 11;
                this->unk_704 = 0;
            }
            break;

        case 11:
            if (this->unk_704 > 50) {
                this->unk_708 = 12;
                this->unk_704 = 0;
                this->actor.gravity = -3.0f;
            }
            break;

        case 13:
            if (this->unk_704 == 45) {
                this->unk_708 = 1;
                this->unk_704 = 0;
                func_800B7298(globalCtx, &this->actor, 0x15);
                this->actor.gravity = 0.0f;
                break;
            }

        case 12:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ME_ATTACK - SFX_FLAG);
            Math_ApproachF(&this->unk_718.x, this->actor.world.pos.x, 0.5f, 1000.0f);
            Math_ApproachF(&this->unk_718.y, this->actor.world.pos.y, 0.5f, 1000.0f);
            Math_ApproachF(&this->unk_718.z, this->actor.world.pos.z, 0.5f, 1000.0f);
            if (this->actor.bgCheckFlags & 2) {
                play_sound(NA_SE_IT_BIG_BOMB_EXPLOSION);
                this->unk_6F4 = 15;
                this->unk_708 = 13;
                this->unk_704 = 0;
                this->unk_2DA = 10;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                            this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, CLEAR_TAG_SPLASH);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KONB_JUMP_LEV_OLD - SFX_FLAG);
                this->unk_748 = 20;
            }
            break;

        case 1:
            player->actor.shape.rot.y = 0x7FFF;
            player->actor.world.rot.y = player->actor.shape.rot.y;
            Matrix_GetStateTranslationAndScaledZ(-100.0f, &this->unk_70C);

            this->unk_70C.x += player->actor.world.pos.x;
            this->unk_70C.y = Player_GetHeight(player) + player->actor.world.pos.y + 36.0f;
            this->unk_70C.z += player->actor.world.pos.z;

            this->unk_718.x = player->actor.world.pos.x;
            this->unk_718.y = (Player_GetHeight(player) + player->actor.world.pos.y) - 4.0f;
            this->unk_718.z = player->actor.world.pos.z;

            if (this->unk_704 >= 35) {
                this->unk_704 = 0;
                this->unk_708 = 2;
                this->unk_728 = -200.0f;
            }
            break;

        case 2:
        case 3:
            Matrix_GetStateTranslationAndScaledZ(500.0f, &this->unk_70C);
            this->unk_70C.x += this->actor.world.pos.x;
            this->unk_70C.y += this->actor.world.pos.y - 50.0f;
            this->unk_70C.z += this->actor.world.pos.z;
            this->unk_718.x = this->actor.world.pos.x;
            this->unk_718.z = this->actor.world.pos.z;
            this->unk_718.y = (this->actor.world.pos.y - 70.0f) + this->unk_728;
            Math_ApproachZeroF(&this->unk_728, 0.05f, this->unk_73C);
            Math_ApproachF(&this->unk_73C, 3.0f, 1.0f, 0.05f);
            if (this->unk_704 == 20) {
                this->unk_708 = 3;
            }

            if (this->unk_704 == 70) {
                this->unk_2C8 = 300;
                this->unk_2D0 = 0.0f;
                D_809EE4D0 = 1;
                this->unk_2E2 = 60;
                this->unk_2E0 = 93;
            }

            if (this->unk_704 > 140) {
                Camera* sp5C = Play_GetCamera(globalCtx, CAM_ID_MAIN);

                this->unk_708 = 0;
                func_809ECD00(this, globalCtx);
                sp5C->eye = this->unk_70C;
                sp5C->eyeNext = this->unk_70C;
                sp5C->at = this->unk_718;
                func_80169AFC(globalCtx, this->unk_70A, 0);
                this->unk_70A = 0;
                Cutscene_End(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                func_80165690();
                gSaveContext.eventInf[6] |= 1;
            }
            break;
    }

    if (this->unk_70A != 0) {
        Vec3f sp50;

        ShrinkWindow_SetLetterboxTarget(27);
        if (this->unk_748 != 0) {
            this->unk_748--;
        }
        Math_Vec3f_Copy(&sp50, &this->unk_718);
        sp50.y += Math_SinS(this->unk_748 * 0x4000) * this->unk_748 * 1.5f;
        Play_CameraSetAtEye(globalCtx, this->unk_70A, &sp50, &this->unk_70C);
        Play_CameraSetFov(globalCtx, this->unk_70A, this->unk_744);
        Math_ApproachF(&this->unk_744, 60.0f, 0.1f, 1.0f);
    }
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    x = player->actor.world.pos.x - this->actor.world.pos.x;
    y = player->actor.world.pos.y - this->actor.world.pos.y;
    z = player->actor.world.pos.z - this->actor.world.pos.z;
    this->actor.shape.rot.x = Math_Atan2S(-y, sqrtf(SQ(x) + SQ(z)));
}

void func_809ECD00(Boss04* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809ECD18;
}

void func_809ECD18(Boss04* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_1F4 >= 0x500) {
        this->unk_1F4 -= 0x300;
        this->unk_1F7 += 1;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 10, 0x200);
    this->actor.world.pos.y = (this->actor.floorHeight + KREG(17) + 160.0f) + (Math_SinS(this->unk_1F4 * 512) * 10.0f);
    Math_ApproachF(&this->actor.speedXZ, this->unk_6D4, 1.0f, 0.5f);

    if (this->unk_1F8 == 0) {
        this->unk_1F8 = Rand_ZeroFloat(100.0f) + 50.0f;
        this->unk_6D4 = Rand_ZeroFloat(3.0f);
        if (Rand_ZeroOne() < 0.1f) {
            Math_Vec3f_Copy(&this->unk_6C8, &player->actor.world.pos);
        } else {
            this->unk_6C8.x = randPlusMinusPoint5Scaled(600.0f) + this->unk_6E8;
            this->unk_6C8.z = randPlusMinusPoint5Scaled(600.0f) + this->unk_6F0;
        }
    }

    Math_ApproachS(&this->actor.world.rot.y,
                   Math_Atan2S(this->unk_6C8.x - this->actor.world.pos.x, this->unk_6C8.z - this->actor.world.pos.z), 5,
                   0x200);

    if (((s8)this->actor.colChkInfo.health <= 10) || (KREG(88) != 0)) {
        KREG(88) = 0;
        func_809ECEF4(this);
    }
}

void func_809ECEF4(Boss04* this) {
    this->actionFunc = func_809ECF58;
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    this->unk_1F8 = 0;
    this->unk_1F6 = 1;
    this->unk_1FA = 60;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = -3.0f;
}

void func_809ECF58(Boss04* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    if ((this->unk_1FE == 14) || ((this->actor.bgCheckFlags & 8) && (this->unk_1F8 == 0))) {
        this->unk_1F8 = 20;
        if ((Rand_ZeroOne() < 0.2f) && (this->unk_1FE == 0)) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->unk_2D0 = 10000.0f;
            this->unk_2C8 = 100;
        } else {
            this->actor.world.rot.y = BINANG_ROT180((s16)Rand_ZeroFloat(8000.0f) + this->actor.world.rot.y);
        }

        this->actor.speedXZ = 0.0f;

        if (this->actor.bgCheckFlags & 8) {
            play_sound(NA_SE_IT_BIG_BOMB_EXPLOSION);
            func_800BC848(&this->actor, globalCtx, 15, 10);
            this->unk_6F4 = 15;
            sp3C.x = this->actor.focus.pos.x;
            sp3C.y = this->actor.focus.pos.y;
            sp3C.z = this->actor.focus.pos.z;
            func_800BBFB0(globalCtx, &sp3C, 100.0f, 40, 500, 10, 0);
        }
    }

    Math_ApproachS(&this->actor.shape.rot.x, Math_SinS(this->unk_1F4 * 0xFB8) * 5000.0f, 5, 0x800);
    Math_ApproachS(&this->actor.shape.rot.z, Math_SinS(this->unk_1F4 * 0xCD0) * 3000.0f, 5, 0x800);

    if (this->unk_6F4 == 0) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x1000);
        if (this->unk_1FA == 0) {
            Math_ApproachF(&this->actor.speedXZ, 20.0f, 1.0f, 1.0f);
            sp3C.x = this->actor.world.pos.x;
            sp3C.y = this->actor.floorHeight + 2.0f;
            sp3C.z = this->actor.world.pos.z;
            EffectSsGRipple_Spawn(globalCtx, &sp3C, 1400, 500, 0);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ME_ATTACK - SFX_FLAG);
        }
    }

    if (KREG(88) != 0) {
        KREG(88) = 0;
        func_809ED224(this);
        this->unk_1FE = 100;
        this->unk_200 = 100;
    }
}

void func_809ED224(Boss04* this) {
    this->actionFunc = func_809ED2A0;
    this->unk_1F8 = 60;
    this->unk_1FA = 100;
    this->actor.speedXZ = 0.0f;
    this->unk_2D0 = 10000.0f;
    this->unk_2C8 = 200;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ME_DEAD);
    this->actor.flags &= ~ACTOR_FLAG_1;
    func_801A2ED8();
    this->unk_1F6 = 10;
}

void func_809ED2A0(Boss04* this, GlobalContext* globalCtx) {
    this->unk_2DA = 10;

    if (this->unk_1F8 >= 5) {
        this->unk_6FC = (Math_SinS(this->unk_1F8 * 0x3000) * 10.0f * 0.01f) + 1.0f;
        this->unk_700 = (Math_CosS(this->unk_1F8 * 0x3000) * 10.0f * 0.01f) + 1.0f;
        this->unk_6F8 = this->unk_700;
    }

    if (this->unk_1F8 == 5) {
        this->unk_6F8 *= 1.3f;
        this->unk_6FC *= 1.3f;
        this->unk_700 *= 1.3f;
    }

    if (this->unk_1F8 == 3) {
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->unk_700 = 0.0f;
        this->unk_6FC = 0.0f;
        this->unk_6F8 = 0.0f;
    }

    if ((this->unk_1F8 == 2) || (this->unk_1F8 == 5)) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                    this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_EXPLOSION);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_IT_BIG_BOMB_EXPLOSION);
    }

    if (this->unk_1FA == 3) {
        this->unk_1F6 = 11;
    }

    if (this->unk_1FA == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_809ED45C(Boss04* this, GlobalContext* globalCtx) {
    ColliderJntSphElement* temp_v0;
    u8 damage;

    if ((this->unk_1FE == 0) && (this->collider1.elements[0].info.bumperFlags & BUMP_HIT)) {
        this->collider1.elements[0].info.bumperFlags &= ~BUMP_HIT;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ME_DAMAGE);
        damage = this->actor.colChkInfo.damage;
        this->actor.colChkInfo.health = this->actor.colChkInfo.health - damage;
        if ((s8)this->actor.colChkInfo.health <= 0) {
            func_809ED224(this);
            this->unk_1FE = 100;
            this->unk_200 = 100;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
        } else {
            this->unk_2DA = 15;
            this->unk_1FE = 15;
            this->unk_200 = 15;
        }
    }
}

void func_809ED50C(Boss04* this) {
    s32 i;

    this->unk_2DE += this->unk_2E2;
    this->unk_2DC += this->unk_2E0;

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, 10.0f, MTXMODE_APPLY);
    Matrix_GetStateTranslation(&this->unk_6BC);
    Matrix_Scale(this->actor.scale.x * 13.0f, this->actor.scale.y * 13.0f, this->actor.scale.z * 16.0f, MTXMODE_APPLY);
    Matrix_RotateY(this->unk_2DC, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->unk_2DE, MTXMODE_APPLY);
    Matrix_StatePush();

    for (i = 0; i < ARRAY_COUNT(this->unk_2E4); i++) {
        Matrix_RotateStateAroundXAxis(0.3926991f);
        Matrix_GetStateTranslationAndScaledZ(100.0f, &this->unk_2E4[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(38.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_3A4); i++) {
        Matrix_RotateStateAroundXAxis(0.41887903f);
        Matrix_GetStateTranslationAndScaledZ(92.0f, &this->unk_3A4[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(-38.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_458); i++) {
        Matrix_RotateStateAroundXAxis(0.41887903f);
        Matrix_GetStateTranslationAndScaledZ(92.0f, &this->unk_458[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(71.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_50C); i++) {
        Matrix_RotateStateAroundXAxis(0.5711987f);
        Matrix_GetStateTranslationAndScaledZ(71.0f, &this->unk_50C[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(-71.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_590); i++) {
        Matrix_RotateStateAroundXAxis(0.5711987f);
        Matrix_GetStateTranslationAndScaledZ(71.0f, &this->unk_590[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(92.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_614); i++) {
        Matrix_RotateStateAroundXAxis(1.0471976f);
        Matrix_GetStateTranslationAndScaledZ(38.0f, &this->unk_614[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(-92.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->unk_65C); i++) {
        Matrix_RotateStateAroundXAxis(1.0471976f);
        Matrix_GetStateTranslationAndScaledZ(38.0f, &this->unk_65C[i]);
    }

    Matrix_StatePop();
    Matrix_StatePush();
    Matrix_InsertTranslation(100.0f, 0.0f, 0.0f, MTXMODE_APPLY);

    Matrix_GetStateTranslation(&this->unk_6A4);
    Matrix_StatePop();
    Matrix_InsertTranslation(-100.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    Matrix_GetStateTranslation(&this->unk_6B0);
}

void Boss04_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss04* this = THIS;
    s16 temp_v0_8;
    s32 pad;

    this->unk_1F4++;
    if (KREG(63) == 0) {
        if (this->unk_1F8 != 0) {
            this->unk_1F8--;
        }

        if (this->unk_1FA != 0) {
            this->unk_1FA--;
        }

        if (this->unk_2C8 != 0) {
            this->unk_2C8--;
        }
        if (this->unk_1FE != 0) {
            this->unk_1FE--;
        }

        if (this->unk_200 != 0) {
            this->unk_200--;
        }

        if (this->unk_2DA != 0) {
            this->unk_2DA--;
        }

        if (this->unk_6F4 != 0) {
            this->unk_6F4--;
        }

        this->actionFunc(this, globalCtx);

        Actor_MoveWithGravity(&this->actor);
        this->actor.world.pos.y -= 100.0f;
        this->actor.prevPos.y -= 100.0f;
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 100.0f, 120.0f, 200.0f, 5);
        this->actor.world.pos.y += 100.0f;
        this->actor.prevPos.y += 100.0f;
    }

    if (this->unk_200 == 10) {
        this->unk_2D0 = 0.0f;
        this->unk_2C8 = Rand_ZeroFloat(100.0f) + 60.0f;
    }

    if (this->unk_2C8 == 0) {
        this->unk_2C8 = Rand_ZeroFloat(100.0f) + 60.0f;
        this->unk_2D0 = 10000.0f - this->unk_2D0;
    }

    Math_ApproachF(&this->unk_2CC, this->unk_2D0, 0.2f, 1000.0f);
    if (this->actionFunc != func_809ED2A0) {
        temp_v0_8 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (ABS_ALT(temp_v0_8) < 0x6000) {
            if (temp_v0_8 > 0x2500) {
                this->unk_2D6 = 0x2500;
            } else if (temp_v0_8 < -0x2500) {
                this->unk_2D6 = -0x2500;
            } else {
                this->unk_2D6 = temp_v0_8;
            }
        } else {
            this->unk_2D6 = 0;
        }
        Math_ApproachS(&this->unk_2D4, this->unk_2D6, 5, 0x800);
        this->unk_2D8 = 2000;
        this->unk_700 = (Math_SinS(this->unk_6F4 * 0x3000) * this->unk_6F4 * 0.02f) + 1.0f;
        this->unk_6FC = (Math_CosS(this->unk_6F4 * 0x3000) * this->unk_6F4 * 0.02f) + 1.0f;
        this->unk_6F8 = this->unk_6FC;
        this->actor.shape.yOffset = (this->unk_6FC - 1.0f) * 1000.0f;
        func_809ED45C(this, globalCtx);
        if (this->unk_2CC > 3000.0f) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
            this->actor.flags |= ACTOR_FLAG_1;
        } else {
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        func_809ED50C(this);
    }

    if (D_809EE4D0 != 0) {
        D_809EE4D0--;
        if (D_809EE4D0 == 0) {
            func_801A2E54(0x38);
        }
    }

    if (this->unk_74A != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_ME_EXIST - SFX_FLAG);
    }
}

s32 Boss04_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    Boss04* this = THIS;

    if (limbIndex == KREG(32)) {
        if (!(this->unk_1F4 & 3)) {
            *dList = NULL;
        }
        rot->x += KREG(33) * 256;
        rot->y += KREG(34) * 256;
        rot->z += KREG(35) * 256;
    }

    if ((limbIndex == 5) || (limbIndex == 7)) {
        rot->y = (rot->y + (s16)this->unk_2CC) - 0x500;
    }

    if (limbIndex == 4) {
        rot->y += this->unk_2D8;
        rot->z += this->unk_2D4;
        if (this->unk_2DA != 0) {
            rot->y = (s16)(Math_SinS(this->unk_1F4 * 0x3000) * (this->unk_2DA * 500)) + rot->y;
            rot->z = (s16)(Math_SinS(this->unk_1F4 * 0x3500) * (this->unk_2DA * 300)) + rot->z;
        }
    }

    return false;
}

void Boss04_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_809EE228 = { 0.0f, -200.0f, 0.0f };
    static Vec3f D_809EE234 = { 0.0f, 720.0f, 0.0f };
    Boss04* this = THIS;
    Vec3f sp18;

    if (limbIndex == 1) {
        Matrix_GetStateTranslationAndScaledY(-500.0f, &this->actor.focus.pos);
        Matrix_MultiplyVector3fByState(&D_809EE228, &sp18);
        func_809EC040(0, &this->collider1, &sp18);
        Matrix_MultiplyVector3fByState(&D_809EE234, &sp18);
        func_809EC040(0, &this->collider2, &sp18);
    }
}

void Boss04_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Boss04* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_200 & 1) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }

    Matrix_InsertTranslation(0.0f, 0.0f, 800.0f, MTXMODE_APPLY);
    Matrix_Scale(this->unk_6F8, this->unk_6FC, this->unk_700, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          Boss04_OverrideLimbDraw, Boss04_PostLimbDraw, &this->actor);

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    if (this->actionFunc != func_809EC568) {
        func_8012C448(globalCtx->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, 150);
        gSPDisplayList(POLY_XLU_DISP++, object_boss04_DL_004510);

        Matrix_InsertTranslation(this->unk_6BC.x, this->actor.floorHeight, this->unk_6BC.z, MTXMODE_NEW);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, 0.0f, -20.0f, MTXMODE_APPLY);
        Matrix_Scale(this->unk_6F8 * 1.8f, 0.0f, this->unk_700 * 2.8f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_boss04_DL_004550);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
