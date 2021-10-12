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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC8D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCAC0.s")

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
    Player* player = PLAYER;
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
    func_80ACC7E4(this, globalCtx, 0x10);
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCEB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD2E4.s")

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
