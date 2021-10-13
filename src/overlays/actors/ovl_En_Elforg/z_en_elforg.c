#include "z_en_elforg.h"

#define FLAGS 0x00000010

#define THIS ((EnElforg*)thisx)

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ACCEB0(EnElforg* this, GlobalContext* globalCtx);
void func_80ACCC98(EnElforg* this, GlobalContext* globalCtx);
void func_80ACCBD0(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD6A8(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD6EC(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD2E4(EnElforg* this, GlobalContext* globalCtx);
void func_80ACCE4C(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD1F0(EnElforg* this, GlobalContext* globalCtx);

const ActorInit En_Elforg_InitVars = {
    ACTOR_EN_ELFORG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElforg),
    (ActorFunc)EnElforg_Init,
    (ActorFunc)EnElforg_Destroy,
    (ActorFunc)EnElforg_Update,
    (ActorFunc)EnElforg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ACDA30 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 16, 32, 0, { 0, 0, 0 } },
};

// static Vec3f sVelocity
static Vec3f D_80ACDA5C = { 0.0f, -0.05f, 0.0f };

// static Vec3f sAcceleration
static Vec3f D_80ACDA68 = { 0.0f, -0.025f, 0.0f };

static Color_RGBA8 D_80ACDA74[] = {
    { 255, 235, 220, 255 }, { 255, 220, 220, 255 }, { 220, 255, 220, 255 },
    { 220, 220, 255, 255 }, { 255, 255, 200, 255 },
};

static Color_RGBA8 D_80ACDA88[] = {
    { 255, 150, 0, 255 }, { 255, 0, 0, 255 }, { 0, 255, 0, 255 }, { 0, 0, 255, 255 }, { 255, 255, 0, 255 },
};

void func_80ACC470(EnElforg* this) {
    this->actor.speedXZ = 1.0f;
    this->unk_224 = 1.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = randPlusMinusPoint5Scaled(65536.0f);
    this->unk_21C = 0;
    this->unk_220 = Rand_ZeroFloat(100.0f);
    this->actor.shape.yOffset = 0.0f;
    this->skelAnime.animCurrentFrame = (s32)Rand_ZeroFloat(5.0f);
}

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->unk_214 = 0;
    this->unk_216 = 0;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0402CA98, &D_0402B494, this->jointTable, this->jointTable, 10);
    this->skelAnime.animPlaybackSpeed = 1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actor.shape.shadowAlpha = 0xFF;

    switch (this->actor.params & 0xF) {
        case 3:
            if ((gSaveContext.weekEventReg[8] & 0x80) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case 7:
            if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0xFE00) >> 9) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        default:
            if (Flags_GetSwitch(globalCtx, (this->actor.params & 0xFE00) >> 9) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case 1:
        case 2:
        case 6:
        case 8:
            break;
    }

    if (func_8010A074(globalCtx) != 0) {
        this->unk_218 = gSaveContext.unk_48C8 + 1;
    } else {
        // Needs to be thisx in order to match
        this->unk_218 = (thisx->params & 0x1C0) >> 6;
    }

    switch (this->actor.params & 0xF) {
        case 1:
            func_80ACC470(this);
            this->actionFunc = func_80ACCEB0;
            this->unk_224 = Rand_ZeroFloat(2.0f) + 1.0f;
            this->unk_228 = Rand_ZeroFloat(100.0f) + 50.0f;
            break;
        case 8:
            func_80ACC470(this);
            this->actionFunc = func_80ACCC98;
            this->unk_220 = 0x3C;
            break;
        case 2:
            this->unk_21C = 0;
            this->actionFunc = func_80ACCBD0;
            break;
        case 4:
            this->actionFunc = func_80ACD6A8;
            func_80ACD6A8(this, globalCtx);
            this->actor.draw = NULL;
            break;
        case 5:
            this->actionFunc = func_80ACD6EC;
            this->actor.draw = NULL;
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80ACDA30);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            break;
        default:
            func_80ACC470(this);
            this->actionFunc = func_80ACD2E4;
            break;
    }

    this->actor.shape.rot.y = 0;
}

void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    if ((this->actor.params & 0xF) == 5) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void func_80ACC7E4(EnElforg* this, GlobalContext* globalCtx, s32 life) {
    Vec3f pos;
    s32 pad;
    s32 index;

    pos.x = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.x;
    pos.y = (Rand_ZeroOne() * 6.0f) + this->actor.world.pos.y + (this->actor.shape.yOffset * this->actor.scale.y);
    pos.z = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.z;
    index = (this->unk_218 < 0 || this->unk_218 >= 5) ? 0 : this->unk_218;
    EffectSsKiraKira_SpawnDispersed(globalCtx, &pos, &D_80ACDA5C, &D_80ACDA68, &D_80ACDA74[index], &D_80ACDA88[index],
                                    1000, life);
}

void func_80ACC8D4(EnElforg* this, Vec3f* bodyPartsPos) {
    f32 yDifference;

    yDifference = bodyPartsPos->y - this->actor.world.pos.y;
    if (fabsf(yDifference) < this->actor.speedXZ) {
        this->actor.world.pos.y = bodyPartsPos->y;
        return;
    }
    if (yDifference > 0.0f) {
        this->actor.world.pos.y = this->actor.world.pos.y + this->actor.speedXZ;
        return;
    }
    this->actor.world.pos.y = this->actor.world.pos.y - this->actor.speedXZ;
}

void func_80ACC934(EnElforg* this) {
    if (this->actor.speedXZ > this->unk_224) {
        this->actor.speedXZ *= 0.9f;
    } else if (this->actor.speedXZ < (this->unk_224 - 0.1f)) {
        this->actor.speedXZ += 0.1f;
    } else {
        this->actor.speedXZ = this->unk_224;
    }
}

void func_80ACC994(EnElforg* this, Vec3f* pos) {
    s32 pad[2];
    f32 xzDistance;
    f32 zDifference;
    f32 xDifference;
    s16 phi_v0;
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->unk_21C << 9);
    func_80ACC8D4(this, pos);
    xDifference = this->actor.world.pos.x - pos->x;
    zDifference = this->actor.world.pos.z - pos->z;
    targetAngle = Math_FAtan2F(-zDifference, -xDifference);
    xzDistance = sqrtf(SQ(xDifference) + SQ(zDifference));
    if ((this->unk_228 + 10.0f) < xzDistance) {
        phi_v0 = 0x1000;
    } else if ((this->unk_228 - 10.0f) > xzDistance) {
        phi_v0 = 0x6000;
    } else {
        phi_v0 = 0x4000;
    }
    targetAngle += phi_v0;
    Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 4000, 1000);
    func_80ACC934(this);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80ACCAC0(EnElforg* this, Vec3f* pos) {
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->unk_21C << 9);
    func_80ACC8D4(this, pos);
    targetAngle = Math_FAtan2F(-(this->actor.world.pos.z - pos->z), -(this->actor.world.pos.x - pos->x));
    if (this->unk_224 > 2.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 0x400, 0x100);
    } else {
        targetAngle += 0x2000;
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 10, 0x200, 0x80);
    }
    func_80ACC934(this);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80ACCBB8(EnElforg* this, GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk5 |= 8;
}

void func_80ACCBD0(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actor.parent == NULL) || (this->actor.parent->update == NULL)) {
        func_80ACC470(this);
        this->actionFunc = func_80ACD2E4;
    } else {
        this->actor.shape.yOffset += 10.0f * Math_SinS(this->unk_21C << 9);
        this->actor.world.pos = this->actor.parent->world.pos;
        this->actor.world.pos.y += 12.0f;
    }
    func_80ACCBB8(this, globalCtx);
}

void func_80ACCC98(EnElforg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 xzDistToPlayer;
    s16 rotationTemp;
    s16 sp34;
    s32 pad;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.yOffset *= 0.9f;
    this->actor.speedXZ = 5.0f;
    func_80ACC8D4(this, player->bodyPartsPos);
    xzDistToPlayer = this->actor.xzDistToPlayer;
    if (xzDistToPlayer < 0.0f) {
        xzDistToPlayer = 10.0f;
    }
    sp34 = 163840.0f / xzDistToPlayer;
    Math_SmoothStepToF(&xzDistToPlayer, 40.0f, 0.2f, 100.0f, 1.0f);
    rotationTemp = this->actor.yawTowardsPlayer - sp34;
    this->actor.world.pos.x = player->actor.world.pos.x - (Math_SinS(rotationTemp) * xzDistToPlayer);
    this->actor.world.pos.z = player->actor.world.pos.z - (Math_CosS(rotationTemp) * xzDistToPlayer);
    func_80ACC7E4(this, globalCtx, 16);
    if (this->unk_220 > 0) {
        this->unk_220--;
        return;
    }
    this->actor.world.rot.y = rotationTemp + 0x4000;
    this->unk_21C = 0;
    this->unk_220 = Rand_ZeroFloat(100.0f);
    this->actor.shape.yOffset = 0.0f;
    this->unk_224 = 3.0f;
    this->unk_228 = 50.0f;
    this->actionFunc = func_80ACCEB0;
    this->unk_214 &= 0xFFFB;
}

void func_80ACCE4C(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80ACC994(this, &this->actor.home.pos);
    if (this->unk_220 < 31) {
        this->actionFunc = func_80ACCC98;
    }
    this->unk_220--;
}

void func_80ACCEB0(EnElforg* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->unk_214 & 1) {
        if (this->unk_224 < 8.0f) {
            this->unk_224 += 0.1f;
        }
        if (this->unk_228 > 0.0f) {
            this->unk_228 -= 2.0f;
        }
    } else if ((this->unk_21C & 0x7F) == 0x7F) {
        if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 150.0f) {
            this->unk_224 = 5.0f;
        } else {
            this->unk_224 = Rand_ZeroFloat(2.0f) + 1.0f;
        }
        this->unk_228 = Rand_ZeroFloat(100.0f) + 50.0f;
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80ACC994(this, &this->actor.home.pos);
    if (this->unk_214 & 4) {
        this->actionFunc = func_80ACCE4C;
    }
    if (this->unk_214 & 2) {
        if (this->actor.home.rot.x > 0) {
            func_80ACC7E4(this, globalCtx, 10);
            this->actor.home.rot.x += -1;
        }
        Actor_SetScale(&this->actor, this->actor.scale.x * 0.9f);
        if (this->actor.scale.x < 0.001f) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD088.s")

void func_80ACD164(EnElforg* this, GlobalContext* globalCtx) {
    func_80ACD088(this, globalCtx);
    if (this->unk_21C >= 0x51) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    func_800B9010(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1B0.s")

void func_80ACD1F0(EnElforg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80ACD088(this, globalCtx);
    player->actor.freezeTimer = 0x64;
    player->stateFlags1 |= 0x20000000;
    if (func_800B867C(&this->actor, globalCtx)) {
        player->actor.freezeTimer = 0;
        player->stateFlags1 &= 0xDFFFFFFF;
        Actor_MarkForDeath(&this->actor);
        gSaveContext.weekEventReg[8] |= 0x80;
        ActorCutscene_Stop(0x7C);
    } else {
        func_800B9010(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
        if (ActorCutscene_GetCurrentIndex() != 0x7C) {
            if (ActorCutscene_GetCanPlayNext(0x7C)) {
                ActorCutscene_Start(0x7C, &this->actor);
            } else {
                ActorCutscene_SetIntentToPlay(0x7C);
            }
        }
    }
}

void func_80ACD2E4(EnElforg* this, GlobalContext* globalCtx) {
    Vec3f pos;
    f32 temp_f0;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRYS_MASK) {
        pos = player->bodyPartsPos[0];
        this->unk_224 = 5.0f;
        func_80ACCAC0(this, &pos);
    } else {
        this->unk_224 = 1.0f;
        func_80ACCAC0(this, &this->actor.home.pos);
    }
    temp_f0 = this->actor.yDistToPlayer - (this->actor.shape.yOffset * this->actor.scale.y);
    if (func_801233E4(globalCtx) == 0) {
        if ((this->actor.xzDistToPlayer < 30.0f) && (temp_f0 < 12.0f) && (temp_f0 > -68.0f)) {
            func_80ACD1B0(this, globalCtx);
            func_80115908(globalCtx, 0x30);
            switch (this->actor.params & 0xF) {
                case 7:
                    Actor_SetCollectibleFlag(globalCtx, (this->actor.params & 0xFE00) >> 9);
                    break;
                case 6:
                    Actor_SetChestFlag(globalCtx, (this->actor.params & 0xFE00) >> 9);
                    break;
                default:
                    Actor_SetSwitchFlag(globalCtx, (this->actor.params & 0xFE00) >> 9);
                    break;
            }
            if ((this->actor.params & 0xF) == 3) {
                player->actor.freezeTimer = 0x64;
                player->stateFlags1 |= 0x20000000;
                func_801518B0(globalCtx, 0x579, NULL);
                this->actionFunc = func_80ACD1F0;
                ActorCutscene_SetIntentToPlay(0x7C);
                return;
            }
            if (func_8010A074(globalCtx)) {
                gSaveContext.inventory.strayFairies[gSaveContext.unk_48C8]++;
                func_801518B0(globalCtx, 0x11, NULL);
                if (gSaveContext.inventory.strayFairies[(void)0, gSaveContext.unk_48C8] >= 15) {
                    func_801A3098(0x922);
                }
            }
        }
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 7);
        func_80ACCBB8(this, globalCtx);
        if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRYS_MASK) {
            if ((this->unk_214 & 8) == 0) {
                play_sound(NA_SE_SY_FAIRY_MASK_SUCCESS);
            }
            this->unk_214 |= 8;
        } else {
            this->unk_214 &= 0xFFF7;
        }
    }
}

Actor* func_80ACD59C(EnElforg* this, GlobalContext* globalCtx) {
    Actor* enemy;

    for (enemy = globalCtx->actorCtx.actorList[ACTORCAT_ENEMY].first; enemy != NULL; enemy = enemy->next) {
        if ((enemy->home.pos.x == this->actor.home.pos.x) && (enemy->home.pos.y == this->actor.home.pos.y) &&
            (enemy->home.pos.z == this->actor.home.pos.z)) {
            return enemy;
        }
    }
    return NULL;
}

void func_80ACD610(EnElforg* this, GlobalContext* globalCtx) {
    f32 posTemp;

    if (this->enemy->update == NULL) {
        func_80ACC470(this);
        this->actionFunc = func_80ACD2E4;
        this->actor.draw = EnElforg_Draw;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
        posTemp = this->enemy->world.pos.x;
        this->actor.world.pos.x = posTemp;
        this->actor.home.pos.x = posTemp;
        posTemp = this->enemy->world.pos.y + 30.0f;
        this->actor.world.pos.y = posTemp;
        this->actor.home.pos.y = posTemp;
        posTemp = this->enemy->world.pos.z;
        this->actor.world.pos.z = posTemp;
        this->actor.home.pos.z = posTemp;
    }
    func_80ACCBB8(this, globalCtx);
}

void func_80ACD6A8(EnElforg* this, GlobalContext* globalCtx) {
    Actor* enemy;

    enemy = func_80ACD59C(this, globalCtx);
    if (enemy != NULL && enemy->update != NULL) {
        this->actionFunc = func_80ACD610;
        this->enemy = enemy;
    }
}

void func_80ACD6EC(EnElforg* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        func_80ACC470(this);
        this->actionFunc = func_80ACD2E4;
        this->actor.draw = EnElforg_Draw;
        this->actor.world.pos.y += 40.0f;
        this->actor.home.pos.y += 40.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    func_80ACCBB8(this, globalCtx);
}

void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_21C == 0 && this->unk_220 > 0) {
        this->unk_220--;
    } else {
        this->unk_21C++;
    }

    if (this->unk_216 < 0) {
        this->unk_216++;
        if (this->unk_216 == 0) {
            this->unk_216 = Rand_ZeroFloat(20.0f) + 20.0f;
        }
    } else if (this->unk_216 > 0) {
        this->unk_216--;
    } else {
        this->unk_216 = -Rand_ZeroFloat(20.0f) - 20.0f;
    }
}

s32 func_80ACD878(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnElforg* this = THIS;

    if (this->unk_216 < 0) {
        if (limbIndex == 9) {
            *dList = NULL;
        }
    } else if (limbIndex == 1) {
        *dList = NULL;
    }
    return 0;
}

void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    switch (this->unk_218) {
        case 1:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C908));
            break;
        case 2:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C890));
            break;
        case 3:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C980));
            break;
        case 4:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C9F8));
            break;
        default:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C818));
            break;
    }
    SysMatrix_InsertMatrix(&globalCtx->mf_187FC, 1);

    POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                      this->skelAnime.dListCount, func_80ACD878, NULL, &this->actor, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
