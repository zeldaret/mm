/*
 * File: z_en_elf.c
 * Overlay: ovl_En_Elf
 * Description: Fairies
 */

#include "z_en_elf.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((EnElf*)thisx)

void EnElf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnElf_SetupAction(EnElf* this, EnElfActionFunc actionFunc);
void func_8088C9CC(EnElf* this, GlobalContext* globalCtx);
void func_8088D3EC(EnElf* this, GlobalContext* globalCtx);
void func_8088D470(EnElf* this, GlobalContext* globalCtx);
void func_8088D504(EnElf* this, GlobalContext* globalCtx);
void func_8088DD34(EnElf* this, GlobalContext* globalCtx);
void func_8088E018(EnElf* this, GlobalContext* globalCtx);
void func_8088E0E0(EnElf* this, GlobalContext* globalCtx);
void func_8088E0F0(EnElf* this, GlobalContext* globalCtx);
void func_8088E484(EnElf* this, GlobalContext* globalCtx);
void func_8088E850(EnElf* this, GlobalContext* globalCtx);
void func_8088EFA4(EnElf* this, GlobalContext* globalCtx);
void func_8088F214(EnElf* this, GlobalContext* globalCtx);
void func_8088F5F4(EnElf* this, GlobalContext* globalCtx, s32 arg2);
void func_8089010C(Actor* thisx, GlobalContext* globalCtx);
void func_808908D0(Vec3f* arg0, GlobalContext* globalCtx, u32 arg2);

const ActorInit En_Elf_InitVars = {
    ACTOR_EN_ELF,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElf),
    (ActorFunc)EnElf_Init,
    (ActorFunc)EnElf_Destroy,
    (ActorFunc)EnElf_Update,
    (ActorFunc)EnElf_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 8, ICHAIN_STOP),
};

static Color_RGBAf sInnerColors[] = {
    { 255.0f, 255.0f, 230.0f, 255.0f },
    { 255.0f, 220.0f, 220.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

static Color_RGBAf sOuterColors[] = {
    { 220.0f, 160.0f, 80.0f, 255.0f },
    { 255.0f, 50.0f, 100.0f, 255.0f },
    { 255.0f, 150.0f, 0.0f, 255.0f },
};

typedef struct {
    u8 r, g, b;
} FairyColorFlags;

static FairyColorFlags sColorFlags[] = {
    { 0, 0, 0 }, { 1, 0, 0 }, { 1, 2, 0 }, { 1, 0, 2 }, { 0, 1, 0 }, { 2, 1, 0 }, { 0, 1, 2 },
    { 0, 0, 1 }, { 2, 0, 1 }, { 0, 2, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 0, 1, 1 },
};

void EnElf_SetupAction(EnElf* this, EnElfActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_8088C51C(EnElf* this, s32 arg1) {
    this->unk_244 = arg1;

    switch (this->unk_244) {
        case 0:
            this->unk_24A = 0x400;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->unk_25C = 0x64;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_250 = 5.0f;
            this->unk_254 = 20.0f;
            break;

        case 10:
            this->unk_24A = 0x400;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->unk_25C = 0x64;
            this->unk_250 = 1.0f;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_254 = 5.0f;
            break;

        case 8:
            this->unk_24A = 0x400;
            this->unk_24C = 0;
            this->unk_26C = func_8088D3EC;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_254 = 0.0f;
            this->unk_250 = 5.0f;
            break;

        case 7:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_250 = 3.0f;
            this->unk_254 = 10.0f;
            break;

        case 5:
            this->unk_26C = func_8088D3EC;
            this->unk_24A = 0x1E;
            this->unk_25C = 1;
            this->unk_250 = 0.0f;
            this->unk_254 = 0.0f;
            this->skelAnime.playSpeed = 1.0f;
            break;

        case 6:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 0.0f;
            this->unk_254 = 0.0f;
            this->skelAnime.playSpeed = 1.0f;
            break;

        case 1:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x800;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 5.0f;
            this->unk_254 = 7.5f;
            this->skelAnime.playSpeed = 2.0f;
            break;

        case 2:
            this->unk_24A = 0x400;
            this->unk_24C = 0x1000;
            this->unk_26C = func_8088D470;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_250 = 10.0f;
            this->unk_254 = 20.0f;
            break;

        case 3:
            this->unk_24C = 0x600;
            this->unk_26C = func_8088D504;
            this->unk_254 = 1.0f;
            this->unk_250 = 1.0f;
            this->skelAnime.playSpeed = 1.0f;
            break;

        case 4:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x800;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 60.0f;
            this->unk_254 = 20.0f;
            this->skelAnime.playSpeed = 2.0f;
            break;

        case 9:
            this->unk_24A = 0x400;
            this->unk_24C = 0x2000;
            this->unk_26C = func_8088D3EC;
            this->unk_25C = 0x2A;
            this->unk_254 = 1.0f;
            this->skelAnime.playSpeed = 1.0f;
            this->unk_250 = 5.0f;
            break;
    }
}

s32 func_8088C804(Vec3f* arg0, Vec3f* arg1, f32 arg2) {
    return SQ(arg2) < SQ(arg1->x - arg0->x) + SQ(arg1->z - arg0->z);
}

void func_8088C858(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!func_8088C804(&this->actor.world.pos, &player->actor.world.pos, 30.0f)) {
        this->unk_254 = 0.5f;
    } else {
        this->unk_254 = 2.0f;
    }
    if (this->unk_25C > 0) {
        this->unk_25C--;
    } else {
        this->unk_244 = 1;
        this->unk_248 = 128;
        this->unk_254 = Rand_ZeroFloat(1.0f) + 0.5f;
        this->unk_24C = randPlusMinusPoint5Scaled(0x7FFF);
        this->unk_26C = func_8088C9CC;
    }
}

void func_8088C920(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (func_8088C804(&this->actor.world.pos, &player->actor.world.pos, 50.0f)) {
        if (this->unk_25C > 0) {
            this->unk_25C--;
        } else {
            this->unk_244 = 1;
            this->unk_248 = 128;
            this->unk_254 = Rand_ZeroFloat(1.0f) + 0.5f;
            this->unk_24C = randPlusMinusPoint5Scaled(0x7FFF);
            this->unk_26C = func_8088C9CC;
        }
    }
}

void func_8088C9CC(EnElf* this, GlobalContext* globalCtx) {
    f32 xzDistToPlayer;

    if (this->unk_25C > 0) {
        this->unk_25C--;
    } else {
        xzDistToPlayer = this->actor.xzDistToPlayer;

        if (xzDistToPlayer < 50.0f) {
            if (Rand_ZeroOne() < 0.2f) {
                this->unk_244 = 2;
                this->unk_248 = 0x400;
                this->unk_254 = 2.0f;
                this->actor.speedXZ = 1.5f;
                this->unk_26C = func_8088C920;
                this->unk_25C = (s32)Rand_ZeroFloat(8.0f) + 4;
            } else {
                this->unk_25C = 10;
            }
        } else {
            if (xzDistToPlayer > 150.0f) {
                xzDistToPlayer = 150.0f;
            }

            xzDistToPlayer = ((xzDistToPlayer - 50.0f) * 0.95f) + 0.05f;

            if (Rand_ZeroOne() < xzDistToPlayer) {
                this->unk_244 = 3;
                this->unk_248 = 0x200;
                this->unk_254 = (2.0f * xzDistToPlayer) + 1.0f;
                this->unk_26C = func_8088C858;
                this->unk_25C = (s32)Rand_ZeroFloat(16.0f) + 16;
            } else {
                this->unk_25C = 10;
            }
        }
    }

    if (Rand_ZeroOne() < 0.1f) {
        this->unk_244 = 1;
        this->unk_248 = 128;
        this->unk_254 = Rand_ZeroFloat(0.5f) + 0.5f;
        this->unk_24C = randPlusMinusPoint5Scaled(0x7FFF);
    }
}

void func_8088CBAC(EnElf* this, GlobalContext* globalCtx) {
    f32 phi_f0;

    if (this->fairyFlags & 0x4000) {
        phi_f0 = 0.0f;
    } else {
        phi_f0 = 100.0f;
    }

    if (func_8088C804(&this->unk_224, &this->actor.world.pos, phi_f0)) {
        this->unk_244 = 0;
        this->unk_248 = 0x200;
        this->unk_254 = 1.5f;
        this->unk_26C = func_8088C9CC;
    } else {
        this->unk_26C(this, globalCtx);
    }
}

void func_8088CC48(EnElf* this, GlobalContext* globalCtx) {
    EnElf_SetupAction(this, func_8088DD34);
    this->unk_250 = Rand_ZeroFloat(10.0f) + 10.0f;
    this->unk_246 = 0;
    this->unk_24A = (s32)Rand_ZeroFloat(1048.0f) + 0x200;
    this->unk_224 = this->actor.world.pos;
    this->unk_258 = randPlusMinusPoint5Scaled(0x7FFF);
    this->unk_26C = func_8088C9CC;
    func_8088CBAC(this, globalCtx);
    this->unk_25C = 0;
    this->disappearTimer = 240;
    if ((this->fairyFlags & 0x400) && Flags_GetCollectible(globalCtx, this->unk_260)) {
        Actor_MarkForDeath(&this->actor);
    }
}

f32 func_8088CD3C(s32 colorFlag) {
    switch (colorFlag) {
        case 1:
            return Rand_ZeroFloat(55.0f) + 200.0f;

        case 2:
            return Rand_ZeroFloat(255.0f);
    }

    return 0.0f;
}

void EnElf_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnElf* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 colorConfig;
    s32 params;

    Actor_ProcessInitChain(thisx, sInitChain);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gameplay_keep_Skel_02AF58.sh, &gameplay_keep_Anim_029140,
                   this->jointTable, this->morphTable, 7);
    ActorShape_Init(&thisx->shape, 0.0f, NULL, 15.0f);
    thisx->shape.shadowAlpha = 255;

    Lights_PointGlowSetInfo(&this->lightInfoGlow, thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 255, 255,
                            255, 0);
    this->lightNodeGlow = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfoGlow);
    Lights_PointNoGlowSetInfo(&this->lightInfoNoGlow, thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 255,
                              255, 255, 0);
    this->lightNodeNoGlow = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfoNoGlow);

    this->fairyFlags = 0;
    this->disappearTimer = 600;
    this->unk_240 = 0.0f;
    colorConfig = 0;

    this->unk_260 = ENELF_GET_FE00(&this->actor);
    params = ENELF_GET_F(&this->actor);
    if (thisx->params & 0x100) {
        this->fairyFlags |= 0x400;
    }

    this->actor.params = params;
    switch (params) {
        case 0:
            thisx->room = -1;
            EnElf_SetupAction(this, func_8088E850);
            func_8088C51C(this, 0);
            this->fairyFlags |= 4;
            thisx->update = func_8089010C;
            this->elfMsg = NULL;
            this->unk_234 = NULL;
            this->unk_269 = 20;
            if ((gSaveContext.save.playerData.tatlTimer >= 25800) || (gSaveContext.save.playerData.tatlTimer < 3000)) {
                gSaveContext.save.playerData.tatlTimer = 0;
            }
            this->unk_266 = ElfMessage_GetFirstCycleHint(globalCtx);
            break;

        case 1:
            colorConfig = -1;
            gSaveContext.jinxTimer = 0;
            EnElf_SetupAction(this, func_8088E0F0);
            this->unk_254 = Math_Vec3f_DistXZ(&thisx->world.pos, &player->actor.world.pos);
            this->unk_248 = player->actor.shape.rot.y;
            this->unk_24C = -0x1000;
            this->unk_224.y = thisx->world.pos.y - player->actor.world.pos.y;
            this->unk_246 = 0;
            this->unk_250 = 0.0f;
            break;

        case 5:
            colorConfig = -1;
            EnElf_SetupAction(this, func_8088E484);
            this->unk_254 = 0.0f;
            this->unk_248 = player->actor.shape.rot.y;
            this->unk_24C = 0;
            this->unk_224.y = thisx->world.pos.y - player->actor.world.pos.y;
            this->unk_246 = 0;
            this->unk_250 = 7.0f;
            break;

        case 7:
            this->fairyFlags |= 0x200;
            thisx->shape.shadowDraw = ActorShadow_DrawWhiteCircle;
            this->fairyFlags |= 0x100;
            colorConfig = -1;
            this->fairyFlags |= 0x800;
            this->fairyFlags |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 2:
            this->fairyFlags |= 0x100;
            colorConfig = -1;
            this->fairyFlags |= 0x800;
            this->fairyFlags |= 0x2000;
            this->fairyFlags |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 6:
            colorConfig = -1;
            this->fairyFlags |= 0x800;
            this->fairyFlags |= 0x2000;
            this->fairyFlags |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 9:
            this->fairyFlags |= 0x1000;

        case 10:
            colorConfig = -2;
            func_8088CC48(this, globalCtx);
            break;

        case 8:
            Actor_MarkForDeath(thisx);
            return;

        case 3:
            colorConfig = Rand_ZeroFloat(11.99f) + 1.0f;
            EnElf_SetupAction(this, func_8088E018);
            func_8088C51C(this, 0);
            break;

        case 4:
            EnElf_SetupAction(this, func_8088E0E0);
            func_8088C51C(this, 6);
            this->fairyFlags |= 8;
            {
                s32 i;

                for (i = 0; i < 8; i++) {
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, thisx->world.pos.x,
                                thisx->world.pos.y - 30.0f, thisx->world.pos.z, 0, 0, 0, 6);
                }
            }
            break;
    }

    this->unk_23C = 3.0f;
    this->innerColor = sInnerColors[0];
    if (colorConfig > 0) {
        this->outerColor.r = func_8088CD3C(sColorFlags[colorConfig].r);
        this->outerColor.g = func_8088CD3C(sColorFlags[colorConfig].g);
        this->outerColor.b = func_8088CD3C(sColorFlags[colorConfig].b);
        this->outerColor.a = 0;
    } else {
        this->innerColor = sInnerColors[-colorConfig];
        this->outerColor = sOuterColors[-colorConfig];
    }
}

void EnElf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElf* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNodeGlow);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNodeNoGlow);
}

void func_8088D3EC(EnElf* this, GlobalContext* globalCtx) {
    this->unk_224.x = Math_SinS(this->unk_248) * this->unk_254;
    this->unk_224.y = Math_SinS(this->unk_246) * this->unk_250;
    this->unk_224.z = Math_CosS(this->unk_248) * this->unk_254;
    this->unk_248 += this->unk_24C;
    this->unk_246 += this->unk_24A;
}

void func_8088D470(EnElf* this, GlobalContext* globalCtx) {
    f32 xzScale = (Math_CosS(this->unk_246) * this->unk_250) + this->unk_254;

    this->unk_224.x = Math_SinS(this->unk_248) * xzScale;
    this->unk_224.y = 0.0f;
    this->unk_224.z = Math_CosS(this->unk_248) * xzScale;

    this->unk_248 += this->unk_24C;
    this->unk_246 += this->unk_24A;
}

void func_8088D504(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_246 = (this->unk_248 * 2) & 0xFFFF;
    this->unk_224.x = Math_SinS(this->unk_248) * this->unk_254;
    this->unk_224.y = Math_SinS(this->unk_246) * this->unk_250;
    this->unk_224.z = -Math_SinS(player->actor.shape.rot.y) * this->unk_224.x;
    this->unk_224.x = Math_CosS(player->actor.shape.rot.y) * this->unk_224.x;
    this->unk_248 += this->unk_24C;
}

void func_8088D5A0(EnElf* this, Vec3f* arg1, f32 arg2) {
    f32 yVelTarget = ((arg1->y + this->unk_224.y) - this->actor.world.pos.y) * arg2;
    f32 yVelAbs = fabsf(yVelTarget);
    f32 yVelDirection = (yVelTarget >= 0.0f) ? 1.0f : -1.0f;

    yVelAbs = CLAMP(yVelAbs, 0.0f, 30.0f);
    Math_StepToF(&this->actor.velocity.y, yVelAbs * yVelDirection, 32.0f);
}

void func_8088D660(EnElf* this, Vec3f* targetPos, f32 arg2) {
    f32 xVelTarget = ((targetPos->x + this->unk_224.x) - this->actor.world.pos.x) * arg2;
    f32 zVelTarget = ((targetPos->z + this->unk_224.z) - this->actor.world.pos.z) * arg2;
    f32 xVelDirection = (xVelTarget >= 0.0f) ? 1.0f : -1.0f;
    f32 zVelDirection = (zVelTarget >= 0.0f) ? 1.0f : -1.0f;

    xVelTarget = fabsf(xVelTarget);
    zVelTarget = fabsf(zVelTarget);

    xVelTarget = CLAMP(xVelTarget, 0.0f, 30.0f) * xVelDirection;
    zVelTarget = CLAMP(zVelTarget, 0.0f, 30.0f) * zVelDirection;

    func_8088D5A0(this, targetPos, arg2);
    Math_StepToF(&this->actor.velocity.x, xVelTarget, 1.5f);
    Math_StepToF(&this->actor.velocity.z, zVelTarget, 1.5f);
    Actor_UpdatePos(&this->actor);
}

void func_8088D7F8(EnElf* this, Vec3f* targetPos) {
    func_8088D5A0(this, targetPos, 0.2f);
    this->actor.velocity.x = 0.0f;
    this->actor.velocity.z = 0.0f;
    Actor_UpdatePos(&this->actor);
    this->actor.world.pos.x = targetPos->x + this->unk_224.x;
    this->actor.world.pos.z = targetPos->z + this->unk_224.z;
}

void func_8088D864(EnElf* this, Vec3f* targetPos) {
    func_8088D5A0(this, targetPos, 0.2f);
    this->actor.velocity.z = 0.0f;
    this->actor.velocity.x = 0.0f;
    Actor_UpdatePos(&this->actor);
    this->actor.world.pos.x = targetPos->x + this->unk_224.x;
    this->actor.world.pos.z = targetPos->z + this->unk_224.z;
}

void func_8088D8D0(EnElf* this, Vec3f* arg1) {
    f32 yVelTarget = (((Math_SinS(this->unk_246) * this->unk_250) + arg1->y) - this->actor.world.pos.y) * 0.2f;
    f32 yVelAbs = fabsf(yVelTarget);
    f32 yVelDirection = (yVelTarget >= 0.0f) ? 1.0f : -1.0f;

    this->unk_246 += this->unk_24A;
    yVelAbs = CLAMP(yVelAbs, 0.0f, 30.0f);

    Math_StepToF(&this->actor.velocity.y, yVelAbs * yVelDirection, 1.5f);
}

void func_8088D9BC(EnElf* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Player* player = GET_PLAYER(globalCtx);
    s16 targetYaw;
    Vec3f* vec = &this->unk_224;

    if (this->fairyFlags & 0x4000) {
        Math_SmoothStepToF(&this->actor.speedXZ, 5.0f, 0.5f, 1.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&this->actor.speedXZ, this->unk_254, 0.2f, 0.5f, 0.01f);
    }

    switch (this->unk_244) {
        case 0:
            targetYaw = Math_FAtan2F(-(this->actor.world.pos.z - vec->z), -(this->actor.world.pos.x - vec->x));
            break;

        case 3:
            targetYaw = Math_FAtan2F(-(this->actor.world.pos.z - player->actor.world.pos.z),
                                     -(this->actor.world.pos.x - player->actor.world.pos.x));
            break;

        case 2:
            targetYaw = Math_FAtan2F(this->actor.world.pos.z - player->actor.world.pos.z,
                                     this->actor.world.pos.x - player->actor.world.pos.x);
            break;

        default:
            targetYaw = this->unk_24C;
            break;
    }

    if (this->fairyFlags & 0x4000) {
        Math_SmoothStepToS(&this->unk_258, targetYaw, 10, this->unk_248, 0x1000);
    } else {
        Math_SmoothStepToS(&this->unk_258, targetYaw, 10, this->unk_248, 0x20);
    }

    this->actor.world.rot.y = this->unk_258;
    Actor_MoveWithGravity(&this->actor);
}

void func_8088DB4C(EnElf* this, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 xVelTarget = ((arg1->x + this->unk_224.x) - this->actor.world.pos.x) * arg4;
    f32 zVelTarget = ((arg1->z + this->unk_224.z) - this->actor.world.pos.z) * arg4;
    f32 xzVelocity;
    f32 clampedXZ;

    arg4 += 0.3f;
    arg3 += 30.0f;

    func_8088D5A0(this, arg1, arg4);

    xzVelocity = sqrtf(SQ(xVelTarget) + SQ(zVelTarget));
    clampedXZ = CLAMP(xzVelocity, arg2, arg3);
    this->actor.speedXZ = clampedXZ;

    if ((xzVelocity != clampedXZ) && (xzVelocity != 0.0f)) {
        xzVelocity = clampedXZ / xzVelocity;
        xVelTarget *= xzVelocity;
        zVelTarget *= xzVelocity;
    }

    Math_StepToF(&this->actor.velocity.x, xVelTarget, 5.0f);
    Math_StepToF(&this->actor.velocity.z, zVelTarget, 5.0f);
    Actor_UpdatePos(&this->actor);
}

s32 func_8088DCA4(EnElf* this) {
    if (this->disappearTimer > 0) {
        this->disappearTimer--;
    } else {
        this->disappearTimer--;
        if (this->disappearTimer > -10) {
            Actor_SetScale(&this->actor, (this->disappearTimer + 10) * 0.008f * 0.1f);
        } else {
            Actor_MarkForDeath(&this->actor);
            return true;
        }
    }
    return false;
}

void func_8088DD34(EnElf* this, GlobalContext* globalCtx) {
    Player* refActor = GET_PLAYER(globalCtx);
    s32 pad;
    Player* player2 = GET_PLAYER(globalCtx);
    f32 heightDiff;

    SkelAnime_Update(&this->skelAnime);

    if (Rand_ZeroOne() < 0.05f) {
        this->unk_250 = Rand_ZeroFloat(10.0f) + 10.0f;
        this->unk_24A = (s32)Rand_ZeroFloat(0x400) + 0x200;
    }

    func_8088CBAC(this, globalCtx);
    if (this->fairyFlags & 0x800) {
        this->unk_224.y = player2->bodyPartsPos[0].y;
    }

    func_8088D8D0(this, &this->unk_224);
    func_8088D9BC(this, globalCtx);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (this->fairyFlags & 0x400) {
            Flags_SetCollectible(globalCtx, this->unk_260);
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (Player_InCsMode(&globalCtx->state)) {
        if ((this->fairyFlags & 0x4000) && (this->fairyFlags & 0x100) && func_8088DCA4(this)) {
            return;
        }
        return;
    }

    heightDiff = this->actor.world.pos.y - refActor->actor.world.pos.y;

    if ((this->fairyFlags & 0x1000) && (heightDiff > 0.0f) && (heightDiff < 60.0f) &&
        !func_8088C804(&this->actor.world.pos, &refActor->actor.world.pos, 10.0f)) {
        func_80115908(globalCtx, 0x80);
        if (this->fairyFlags & 0x200) {
            Parameter_AddMagic(globalCtx, ((void)0, gSaveContext.unk_3F30) +
                                              (gSaveContext.save.playerData.doubleMagic * 0x30) + 0x30);
        }
        gSaveContext.jinxTimer = 0;
        this->unk_254 = 50.0f;
        this->unk_248 = refActor->actor.shape.rot.y;
        this->unk_24C = -0x1000;
        this->unk_224.y = 30.0f;
        this->unk_250 = 0.0f;
        this->unk_246 = 0;
        EnElf_SetupAction(this, func_8088E0F0);
        if (this->fairyFlags & 0x400) {
            Flags_SetCollectible(globalCtx, this->unk_260);
        }
        return;
    }

    if (this->fairyFlags & 0x100) {
        if (func_8088DCA4(this)) {
            return;
        }
    } else {
        Actor_SetScale(&this->actor, 0.008f);
    }

    if (this->fairyFlags & 0x2000) {
        Actor_PickUp(&this->actor, globalCtx, GI_MAX, 80.0f, 60.0f);
    }
}

void func_8088E018(EnElf* this, GlobalContext* globalCtx) {
    Vec3f parentPos;
    Actor* parent;

    SkelAnime_Update(&this->skelAnime);
    func_8088D3EC(this, globalCtx);
    parent = this->actor.parent;

    if ((parent != NULL) && (parent->update != NULL)) {
        parentPos = this->actor.parent->world.pos;
        parentPos.y += (1500.0f * this->actor.scale.y) + 40.0f;
        func_8088D660(this, &parentPos, 0.2f);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
}

void func_8088E0E0(EnElf* this, GlobalContext* globalCtx) {
}

void func_8088E0F0(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToF(&this->unk_254, 30.0f, 0.1f, 4.0f, 1.0f);

    this->unk_224.x = Math_CosS(this->unk_248) * this->unk_254;
    this->unk_224.y += this->unk_250;

    switch (this->unk_246) {
        case 0:
            if (this->unk_250 < 2.0f) {
                this->unk_250 += 0.1f;
            } else {
                gSaveContext.healthAccumulator = 160;
                this->unk_246++;
            }
            break;

        case 1:
            if (this->unk_250 > -1.0f) {
                this->unk_250 -= 0.2f;
            }
            break;
    }

    this->unk_224.z = Math_SinS(this->unk_248) * -this->unk_254;
    this->unk_248 += this->unk_24C;
    func_8088D660(this, &player->actor.world.pos, 0.2f);

    if (this->unk_250 < 0.0f) {
        if ((this->unk_224.y < 20.0f) && (this->unk_224.y > 0.0f)) {
            Actor_SetScale(&this->actor, this->unk_224.y * 0.008f * 0.05f);
        }
    }

    if (this->unk_224.y < -10.0f) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    func_8088F5F4(this, globalCtx, 32);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
}

void func_8088E304(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_224.y > 200.0f) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->unk_24A >= 0x7E) {
        this->unk_254 += 0.1f;
        this->unk_250 += 0.5f;
        this->unk_224.y += this->unk_250;
    } else {
        this->unk_24A++;
        if (this->unk_254 < 30.0f) {
            this->unk_254 += 0.5f;
        }

        if (this->unk_224.y > 0.0f) {
            this->unk_224.y -= 0.7f;
        }
    }

    this->unk_224.x = Math_CosS(this->unk_248) * this->unk_254;
    this->unk_224.z = Math_SinS(this->unk_248) * -this->unk_254;
    this->unk_248 += this->unk_24C;

    func_8088D7F8(this, &player->bodyPartsPos[0]);
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    func_8088F5F4(this, globalCtx, 0x20);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
}

void func_8088E484(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);

    this->unk_224.z = 0.0f;
    this->unk_224.x = 0.0f;
    this->unk_224.y += this->unk_250;
    this->unk_250 -= 0.35f;

    if (this->unk_250 <= 0.0f) {
        EnElf_SetupAction(this, func_8088E304);
        this->unk_24C = 0x800;
        this->unk_24A = 0;
        this->unk_250 = 0.0f;
        this->unk_254 = 1.0f;
    }

    func_8088D7F8(this, &player->bodyPartsPos[0]);
    Actor_SetScale(&this->actor, (1.0f - (SQ(this->unk_250) * SQ(1.0f / 9.0f))) * 0.008f);
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    func_8088F5F4(this, globalCtx, 32);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
}

void func_8088E5A8(EnElf* this, GlobalContext* globalCtx) {
    if (this->fairyFlags & 4) {
        func_8088EFA4(this, globalCtx);
    }

    SkelAnime_Update(&this->skelAnime);

    this->unk_26C(this, globalCtx);
}

void func_8088E60C(EnElf* this, GlobalContext* globalCtx) {
    s16 glowLightRadius;
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags1 & 0x400) {
        glowLightRadius = 200;
    } else {
        glowLightRadius = 100;
    }

    if ((this->unk_244 == 6) || (player->stateFlags1 & 2) || (this->fairyFlags & 0x8000)) {
        glowLightRadius = 0;
    }

    if (Cutscene_CheckActorAction(globalCtx, 201)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 201)]->action == 6) {
            glowLightRadius = 0;
        }
    }

    if (this->fairyFlags & 0x20) {
        Player* player = GET_PLAYER(globalCtx);

        Lights_PointNoGlowSetInfo(&this->lightInfoNoGlow, player->actor.world.pos.x, player->actor.world.pos.y + 60.0f,
                                  player->actor.world.pos.z, 255, 255, 255, 200);
    } else {
        Lights_PointNoGlowSetInfo(&this->lightInfoNoGlow, this->actor.world.pos.x, this->actor.world.pos.y,
                                  this->actor.world.pos.z, 255, 255, 255, -1);
    }

    Lights_PointGlowSetInfo(&this->lightInfoGlow, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 255, 255, 255, glowLightRadius);
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void func_8088E850(EnElf* this, GlobalContext* globalCtx) {
    Vec3f nextPos;
    Player* player = GET_PLAYER(globalCtx);
    Actor* arrowPointedActor;
    f32 xScale;
    f32 distFromLinksHead;
    u32 sp38;

    func_8088F214(this, globalCtx);
    func_8088E5A8(this, globalCtx);
    xScale = 0.0f;

    if (Cutscene_CheckActorAction(globalCtx, 201)) {
        sp38 = Cutscene_GetActorActionIndex(globalCtx, 201);
        func_808908D0(&nextPos, globalCtx, sp38);
        this->actor.shape.rot.y = globalCtx->csCtx.actorActions[sp38]->urot.y;
        this->actor.shape.rot.x = globalCtx->csCtx.actorActions[sp38]->urot.x;
        if (globalCtx->csCtx.actorActions[sp38]->action == 5) {
            func_8088F5F4(this, globalCtx, 16);
        }

        if (this->unk_244 == 8) {
            func_8088D864(this, &nextPos);
        } else {
            func_8088D660(this, &nextPos, 0.2f);
        }

        if ((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 0) &&
            (globalCtx->csCtx.currentCsIndex == 0) &&
            ((globalCtx->csCtx.frames == 149) || (globalCtx->csCtx.frames == 381) ||
             (globalCtx->csCtx.frames == 591))) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
        }

        if ((globalCtx->sceneNum == SCENE_SECOM) && (gSaveContext.sceneSetupIndex == 0) &&
            (globalCtx->csCtx.currentCsIndex == 4) && (globalCtx->csCtx.frames == 95)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
        }
    } else {
        this->actor.shape.rot.x = 0;
        distFromLinksHead = Math_Vec3f_DistXYZ(&player->bodyPartsPos[8], &this->actor.world.pos);
        switch (this->unk_244) {
            case 5:
                func_8088D660(this, &player->bodyPartsPos[8], 1.0f - (this->unk_24A * 0.033333335f));
                xScale = Math_Vec3f_DistXYZ(&player->bodyPartsPos[8], &this->actor.world.pos);

                if (distFromLinksHead < 7.0f) {
                    this->unk_25C = 0;
                    xScale = 0;
                } else if (distFromLinksHead < 25.0f) {
                    xScale = (xScale - 5.0f) * 0.05f;
                    xScale = 1.0f - xScale;
                    xScale = (1.0f - SQ(xScale)) * 0.008f;
                } else {
                    xScale = 0.008f;
                }
                func_8088F5F4(this, globalCtx, 16);
                break;

            case 6:
                func_8088D660(this, &player->bodyPartsPos[8], 0.2f);
                this->actor.world.pos = player->bodyPartsPos[8];
                break;

            case 9:
                nextPos = player->bodyPartsPos[8];
                nextPos.y += 1500.0f * this->actor.scale.y;

                func_8088D7F8(this, &nextPos);
                func_8088F5F4(this, globalCtx, 16);

                if (this->unk_254 <= 19.0f) {
                    this->unk_254 += 1.0f;
                }

                if (this->unk_254 >= 21.0f) {
                    this->unk_254 -= 1.0f;
                }

                if (this->unk_25C < 0x20) {
                    this->unk_24C = (this->unk_25C * 240) + 0x200;
                }
                break;

            case 10:
                nextPos = GET_ACTIVE_CAM(globalCtx)->eye;
                nextPos.y += -2000.0f * this->actor.scale.y;
                func_8088DB4C(this, &nextPos, 0.0f, 30.0f, 0.2f);
                break;

            default:
                arrowPointedActor = globalCtx->actorCtx.targetContext.arrowPointedActor;
                if ((player->stateFlags1 & 0x40) && (player->targetActor != NULL)) {
                    Math_Vec3f_Copy(&nextPos, &player->targetActor->focus.pos);
                } else {
                    Math_Vec3f_Copy(&nextPos, &globalCtx->actorCtx.targetContext.unk0);
                }
                nextPos.y += 1500.0f * this->actor.scale.y;

                if (arrowPointedActor != NULL) {
                    func_8088DB4C(this, &nextPos, 0.0f, 30.0f, 0.2f);
                    if (this->actor.speedXZ >= 5.0f) {
                        func_8088F5F4(this, globalCtx, 0x10);
                    }
                } else {
                    if ((this->timer % 32) == 0) {
                        this->unk_23C = Rand_ZeroFloat(7.0f) + 3.0f;
                    }

                    if (this->fairyFlags & 2) {
                        if (distFromLinksHead < 30.0f) {
                            this->fairyFlags ^= 2;
                        }
                        func_8088DB4C(this, &nextPos, 0.0f, 30.0f, 0.2f);
                        func_8088F5F4(this, globalCtx, 0x10);
                    } else {
                        if (distFromLinksHead > 100.0f) {
                            this->fairyFlags |= 2;
                            if (this->unk_269 == 0) {
                                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
                            }
                            this->unk_25C = 100;
                        }
                        func_8088DB4C(this, &nextPos, 0.0f, this->unk_23C, 0.2f);
                    }
                }
                break;
        }
    }

    if (this->unk_244 == 5) {
        this->actor.scale.x = xScale;
    } else if (this->unk_244 == 6) {
        this->actor.scale.x = 0.0f;
    } else {
        Math_SmoothStepToF(&this->actor.scale.x, 0.008f, 0.3f, 0.00080000004f, 0.000080000005f);
    }

    func_8088E60C(this, globalCtx);

    if (!Cutscene_CheckActorAction(globalCtx, 0xC9)) {
        this->actor.shape.rot.y = this->unk_258;
    }
}

void func_8088EF18(Color_RGBAf* dest, Color_RGBAf* newColor, Color_RGBAf* curColor, f32 rate) {
    Color_RGBAf rgbaDiff;

    rgbaDiff.r = newColor->r - curColor->r;
    rgbaDiff.g = newColor->g - curColor->g;
    rgbaDiff.b = newColor->b - curColor->b;
    rgbaDiff.a = newColor->a - curColor->a;

    dest->r += rgbaDiff.r * rate;
    dest->g += rgbaDiff.g * rate;
    dest->b += rgbaDiff.b * rate;
    dest->a += rgbaDiff.a * rate;
}

void func_8088EFA4(EnElf* this, GlobalContext* globalCtx) {
    Actor* arrayPointerActor = globalCtx->actorCtx.targetContext.arrowPointedActor;
    Player* player = GET_PLAYER(globalCtx);
    f32 transitionRate;

    if (!(this->unk_264 & 8)) {
        this->unk_264 &= ~0x10;
    }

    if (this->unk_264 & 8) {
        if (this->unk_264 & 0x10) {
            this->unk_238 = 1.0f;
            this->unk_264 &= ~8;
            this->unk_268 = 0;
            this->unk_264 &= ~0x10;
        } else {
            this->innerColor.r = 255.0f;
            this->innerColor.g = 0.0f;
            this->innerColor.b = 0.0f;
            this->innerColor.a = 255.0f;

            this->outerColor.r = 200.0f;
            this->outerColor.g = 80.0f;
            this->outerColor.b = 80.0f;
            this->outerColor.a = 0.0f;
        }
    } else if (globalCtx->actorCtx.targetContext.unk40 != 0.0f) {
        this->unk_268 = 0;
        this->unk_238 = 1.0f;
        if (!this->unk_269) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
        }
    } else if (this->unk_268 == 0) {
        if ((arrayPointerActor == NULL) ||
            (Math_Vec3f_DistXYZ(&this->actor.world.pos, &globalCtx->actorCtx.targetContext.unk0) < 50.0f)) {
            this->unk_268 = 1;
        }
    } else if (this->unk_238 != 0.0f) {
        if (Math_StepToF(&this->unk_238, 0.0f, 0.25f)) {
            this->innerColor = globalCtx->actorCtx.targetContext.fairyInner;
            this->outerColor = globalCtx->actorCtx.targetContext.fairyOuter;
        } else {
            transitionRate = 0.25f / this->unk_238;
            func_8088EF18(&this->innerColor, &globalCtx->actorCtx.targetContext.fairyInner, &this->innerColor,
                          transitionRate);
            func_8088EF18(&this->outerColor, &globalCtx->actorCtx.targetContext.fairyOuter, &this->outerColor,
                          transitionRate);
        }
    }

    if (this->fairyFlags & 1) {
        if ((arrayPointerActor == NULL) || (player->unk_730 == NULL)) {
            this->fairyFlags ^= 1;
        }
    } else if ((arrayPointerActor != NULL) && (player->unk_730 != NULL)) {
        u8 temp = this->unk_269;
        u16 targetSfxId = this->unk_269 == 0 ? NA_SE_PL_WALK_GROUND - SFX_FLAG : NA_SE_PL_WALK_GROUND - SFX_FLAG;

        if (!temp) {
            Actor_PlaySfxAtPos(&this->actor, targetSfxId);
        }
        this->fairyFlags |= 1;
    }
}

void func_8088F214(EnElf* this, GlobalContext* globalCtx) {
    s32 sp34;
    Actor* arrowPointedActor;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if (globalCtx->csCtx.state != 0) {
        if (Cutscene_CheckActorAction(globalCtx, 201)) {
            switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 201)]->action) {
                case 4:
                    sp34 = 7;
                    break;

                case 3:
                    sp34 = 4;
                    break;

                case 1:
                    sp34 = 8;
                    break;

                default:
                    sp34 = 0;
                    break;
            }
        } else {
            sp34 = 0;
            this->unk_25C = 100;
        }
    } else if (this->unk_264 & 8) {
        sp34 = 1;
        func_800B9010(&this->actor, NA_SE_EV_BELL_ANGER - SFX_FLAG);
    } else {
        arrowPointedActor = globalCtx->actorCtx.targetContext.arrowPointedActor;
        if (player->stateFlags1 & 0x400) {
            sp34 = 10;
            this->unk_25C = 100;
        } else if ((arrowPointedActor == NULL) || (arrowPointedActor->category == 4)) {
            if (arrowPointedActor != NULL) {
                this->unk_25C = 100;
                player->stateFlags2 |= 0x100000;
                sp34 = 0;
            } else {
                switch (this->unk_244) {
                    case 0:
                        if (this->unk_25C != 0) {
                            this->unk_25C--;
                            sp34 = 0;
                        } else if (!(player->stateFlags1 & 0x40)) {
                            if (this->unk_269 == 0) {
                                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_NAVY_VANISH);
                            }
                            sp34 = 5;
                        } else {
                            sp34 = 0;
                        }
                        break;

                    case 5:
                        if (this->unk_25C != 0) {
                            if (this->unk_24A > 0) {
                                this->unk_24A--;
                                sp34 = 5;
                            } else {
                                player->stateFlags2 |= 0x100000;
                                sp34 = 0;
                            }
                        } else {
                            sp34 = 6;
                        }
                        break;

                    case 6:
                        sp34 = 6;
                        break;

                    case 9:
                        sp34 = this->unk_244;
                        if (this->unk_25C > 0) {
                            this->unk_25C--;
                        } else {
                            sp34 = 0;
                        }
                        break;

                    default:
                        sp34 = 0;
                        break;
                }
            }
        } else {
            sp34 = 1;
        }

        switch (sp34) {
            case 0:
                if (!(player->stateFlags2 & 0x100000)) {
                    sp34 = 5;
                    if (this->unk_269 == 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_NAVY_VANISH);
                    }
                }
                break;

            case 6:
                if (player->stateFlags2 & 0x100000) {
                    sp34 = 9;
                    this->unk_25C = 0x2A;
                    if (this->unk_269 == 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
                    }
                } else if (player->stateFlags1 & 0x40) {
                    player->stateFlags2 |= 0x100000;
                    sp34 = 0;
                    this->unk_25C = 0;
                }
                break;

            case 5:
                player->stateFlags2 &= ~0x100000;
                break;

            default:
                player->stateFlags2 |= 0x100000;
                break;
        }
    }

    if (sp34 != this->unk_244) {
        func_8088C51C(this, sp34);
        if (sp34 == 9) {
            this->unk_254 = Math_Vec3f_DistXZ(&player->bodyPartsPos[8], &this->actor.world.pos);
            this->unk_248 = Math_Vec3f_Yaw(&this->actor.world.pos, &player->bodyPartsPos[8]);
        }
    }
}

void func_8088F5F4(EnElf* this, GlobalContext* globalCtx, s32 sparkleLife) {
    static Vec3f sparkleVelocity = { 0.0f, -0.05f, 0.0f };
    static Vec3f sparkleAccel = { 0.0f, -0.025f, 0.0f };
    s32 pad;
    Vec3f sparklePos;
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;

    if (!(this->fairyFlags & 8)) {
        sparklePos.x = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.x;
        sparklePos.y = (Rand_ZeroOne() * 6.0f) + this->actor.world.pos.y;
        sparklePos.z = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.z;

        primColor.r = this->innerColor.r;
        primColor.g = this->innerColor.g;
        primColor.b = this->innerColor.b;

        envColor.r = this->outerColor.r;
        envColor.g = this->outerColor.g;
        envColor.b = this->outerColor.b;

        EffectSsKiraKira_SpawnDispersed(globalCtx, &sparklePos, &sparkleVelocity, &sparkleAccel, &primColor, &envColor,
                                        1000, sparkleLife);
    }
}

void func_8088F9E4(Actor* thisx, GlobalContext* globalCtx) {
    EnElf* this = THIS;
    s32 bgId;

    thisx->floorHeight = BgCheck_EntityRaycastFloor5_2(globalCtx, &globalCtx->colCtx, &thisx->floorPoly, &bgId,
                                                       &this->actor, &thisx->world.pos);
    thisx->shape.shadowAlpha = 50;
}

void func_8088FA38(EnElf* this, GlobalContext* globalCtx) {
    Vec3f refPos;
    Player* player = GET_PLAYER(globalCtx);

    if (this->fairyFlags & 0x10) {
        refPos = globalCtx->actorCtx.targetContext.unk0;

        if (this->unk_234 != NULL) {
            refPos = this->unk_234->world.pos;
        } else {
            if ((player->unk_730 == NULL) || (&player->actor == player->unk_730) || (&this->actor == player->unk_730) ||
                (this->unk_264 & 4)) {
                refPos.x = player->bodyPartsPos[7].x + (Math_SinS(player->actor.shape.rot.y) * 20.0f);
                refPos.y = player->bodyPartsPos[7].y + 5.0f;
                refPos.z = player->bodyPartsPos[7].z + (Math_CosS(player->actor.shape.rot.y) * 20.0f);
                this->unk_264 &= ~4;
            }
        }
        this->actor.focus.pos = refPos;
        this->fairyFlags &= ~0x10;
    }

    func_8088E5A8(this, globalCtx);
    refPos = this->actor.focus.pos;
    func_8088DB4C(this, &refPos, 0, 30.0f, 0.2f);

    if (this->actor.speedXZ >= 5.0f) {
        func_8088F5F4(this, globalCtx, 0x10);
    }

    Math_SmoothStepToF(&this->actor.scale.x, 0.008f, 0.3f, 0.00080000004f, 0.000080000005f);
    func_8088E60C(this, globalCtx);
}

void func_8088FC34(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_258, 5, 0x1000, 0x400);
    this->timer++;

    if (this->unk_234 == NULL) {
        if (this->unk_264 & 0x20) {
            this->unk_240 = 0.0f;
        } else {
            Math_StepToF(&this->unk_240, 1.0f, 0.05f);
        }
        func_800FD2B4(globalCtx, SQ(this->unk_240), player->actor.projectedPos.z + 780.0f, 0.2f, 0.5f);
    }
}

void func_8088FD04(EnElf* this) {
    if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
        this->unk_264 &= ~1;
        this->unk_264 |= 2;
    } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->unk_264 |= 1;
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->unk_264 &= ~1;
        this->unk_264 |= 2;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->unk_264 |= 1;
    }
}

void func_8088FDCC(EnElf* this) {
    this->actor.update = func_8089010C;
    func_8088C51C(this, 0);
    this->fairyFlags &= ~0x20;
    this->actor.focus.pos = this->actor.world.pos;
    this->unk_234 = NULL;
    if ((this->unk_264 & 2) && (this->actor.cutscene != 0x7C)) {
        ActorCutscene_Stop(this->actor.cutscene);
    }
    this->unk_264 &= ~0x20;
}

void func_8088FE64(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnElf* this = THIS;

    func_8088FA38(this, globalCtx);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(globalCtx)) {
                if (globalCtx->msgCtx.currentTextId == 0x202) {
                    switch (globalCtx->msgCtx.choiceIndex) {
                        case 0:
                            func_8019F230();
                            break;

                        case 1:
                            func_8019F208();
                            break;
                    }
                }

                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId - 1);
                        break;

                    case 1:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 576:
                        func_80151938(globalCtx, 0x245);
                        break;

                    case 0x21D:
                    case 0x21E:
                    case 0x21F:
                    case 0x220:
                    case 0x221:
                    case 0x222:
                    case 0x223:
                    case 0x23F:
                    case 0x241:
                    case 0x242:
                    case 0x243:
                    case 0x244:
                        switch (CURRENT_DAY) {
                            case 1:
                                func_80151938(globalCtx, 0x246);
                                break;

                            case 2:
                                func_80151938(globalCtx, 0x247);
                                break;

                            case 3:
                                if (!gSaveContext.save.isNight) {
                                    func_80151938(globalCtx, 0x248);
                                } else if ((gSaveContext.save.time < CLOCK_TIME(6, 0)) &&
                                           (gSaveContext.save.weekEventReg[74] & 0x20)) {
                                    func_80151938(globalCtx, 0x225);
                                } else {
                                    func_80151938(globalCtx, 0x249);
                                }
                                break;
                        }
                        break;

                    default:
                        func_801477B4(globalCtx);
                        func_8088FDCC(this);
                        break;
                }
            }
            break;

        case 2:
            func_8088FDCC(this);
            break;
    }

    func_8088FC34(this, globalCtx);

    if (this->unk_264 & 1) {
        func_8088FD04(this);
    }
}

void func_8089010C(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElf* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    u16 temp_v0 = ElfMessage_GetFirstCycleHint(globalCtx);

    if (temp_v0 != this->unk_266) {
        this->unk_266 = temp_v0;
        gSaveContext.save.playerData.tatlTimer = 0;
    }

    if ((player->tatlTextId == 0) && (player->unk_730 == NULL)) {
        if ((gSaveContext.save.playerData.tatlTimer >= 600) && (gSaveContext.save.playerData.tatlTimer <= 3000)) {
            player->tatlTextId = ElfMessage_GetFirstCycleHint(globalCtx);
        }
    }

    if (player->tatlTextId < 0) {
        thisx->flags |= 0x10000;
    }

    if (Actor_ProcessTalkRequest(thisx, &globalCtx->state)) {
        func_8019FDC8(&D_801DB4A4, NA_SE_VO_NA_LISTEN, 0x20);
        thisx->focus.pos = thisx->world.pos;

        if (thisx->textId == ElfMessage_GetFirstCycleHint(globalCtx)) {
            this->fairyFlags |= 0x80;
            gSaveContext.save.playerData.tatlTimer = 3001;
        }

        this->fairyFlags |= 0x10;
        this->fairyFlags |= 0x20;
        thisx->update = func_8088FE64;
        func_8088C51C(this, 3);
        if (this->elfMsg != NULL) {
            this->elfMsg->flags |= 0x100;
            thisx->cutscene = this->elfMsg->cutscene;
            if (thisx->cutscene != -1) {
                func_8088FD04(this);
            }
            if (this->elfMsg->home.rot.x == -0x961) {
                this->unk_234 = this->elfMsg;
                Actor_ChangeFocus(thisx, globalCtx, this->elfMsg);
            }
        } else {
            thisx->cutscene = -1;
        }
        thisx->flags &= ~0x10000;
    } else if (this->unk_264 & 4) {
        thisx->focus.pos = thisx->world.pos;
        this->fairyFlags |= 0x10;
        this->fairyFlags |= 0x20;
        thisx->update = func_8088FE64;
        func_8088C51C(this, 3);
    } else {
        this->actionFunc(this, globalCtx);

        if (!Play_InCsMode(globalCtx)) {
            if (gSaveContext.save.playerData.tatlTimer < 25800) {
                gSaveContext.save.playerData.tatlTimer++;
            } else if (!(this->fairyFlags & 0x80)) {
                gSaveContext.save.playerData.tatlTimer = 0;
            }
        }
    }

    this->elfMsg = NULL;
    this->timer++;

    if ((this->unk_240 >= 0.0f) && func_800FD2B4(globalCtx, SQ(this->unk_240) * this->unk_240,
                                                 player->actor.projectedPos.z + 780.0f, 0.2f, 0.5f)) {
        Math_StepToF(&this->unk_240, -0.05f, 0.05f);
    }

    if (this->unk_269 > 0) {
        this->unk_269--;
    }

    if (!this->unk_269 && (globalCtx->csCtx.state != 0)) {
        this->unk_269 = 1;
    }
}

void EnElf_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElf* this = THIS;

    this->actionFunc(this, globalCtx);

    thisx->shape.rot.y = this->unk_258;
    this->timer++;

    if (this->fairyFlags & 0x200) {
        func_8088F9E4(thisx, globalCtx);
    }
}

s32 EnElf_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                           Gfx** gfx) {
    static Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnElf* this = THIS;
    Vec3f sp34;
    f32 scale;

    if (limbIndex == 6) {
        scale = ((Math_SinS(this->timer * 4096) * 0.1f) + 1.0f) * 0.012f;
        if (this->fairyFlags & 0x200) {
            scale *= 2.0f;
        }
        scale *= this->actor.scale.x * 124.99999f;

        Matrix_MultiplyVector3fByState(&zeroVec, &sp34);
        Matrix_InsertTranslation(sp34.x, sp34.y, sp34.z, MTXMODE_NEW);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    }

    if ((this->fairyFlags & 0x200) &&
        ((limbIndex == 4) || (limbIndex == 7) || (limbIndex == 11) || (limbIndex == 14))) {
        *dList = NULL;
    }
    return false;
}

void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnElf* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s32 pad2;

    if (player->currentMask != PLAYER_MASK_GIANT) {
        if (!(this->fairyFlags & 8) &&
            (!Cutscene_CheckActorAction(globalCtx, 201) ||
             (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 201)]->action != 6)) &&
            (!(player->stateFlags1 & 0x100000) || (kREG(90) < this->actor.projectedPos.z))) {
            Gfx* dListHead = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 4);
            f32 alphaScale;
            s32 envAlpha;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C94C(globalCtx->state.gfxCtx);

            envAlpha = (this->timer * 50) & 0x1FF;
            envAlpha = (envAlpha >= 0x100) ? 511 - envAlpha : envAlpha;

            alphaScale = (this->disappearTimer < 0) ? (this->disappearTimer * 0.0011666666f) + 1.0f : 1.0f;

            gSPSegment(POLY_XLU_DISP++, 0x08, dListHead);

            gDPPipeSync(dListHead++);
            gDPSetPrimColor(dListHead++, 0, 0x01, (u8)(s8)this->innerColor.r, (u8)(s8)this->innerColor.g,
                            (u8)(s8)this->innerColor.b, (u8)(s8)(this->innerColor.a * alphaScale));

            if (this->fairyFlags & 4) {
                gDPSetRenderMode(dListHead++, G_RM_PASS, G_RM_CLD_SURF2);
            } else {
                gDPSetRenderMode(dListHead++, G_RM_PASS, G_RM_ZB_CLD_SURF2);
            }

            gSPEndDisplayList(dListHead);

            gDPSetEnvColor(POLY_XLU_DISP++, (u8)(s8)this->outerColor.r, (u8)(s8)this->outerColor.g,
                           (u8)(s8)this->outerColor.b, (u8)(s8)(envAlpha * alphaScale));

            POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           EnElf_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void func_808908D0(Vec3f* vec, GlobalContext* globalCtx, u32 action) {
    Vec3f startPos;
    Vec3f endPos;
    CsCmdActorAction* npcAction = globalCtx->csCtx.actorActions[action];
    f32 lerp;

    startPos.x = npcAction->startPos.x;
    startPos.y = npcAction->startPos.y;
    startPos.z = npcAction->startPos.z;

    endPos.x = npcAction->endPos.x;
    endPos.y = npcAction->endPos.y;
    endPos.z = npcAction->endPos.z;

    lerp = Environment_LerpWeight(npcAction->endFrame, npcAction->startFrame, globalCtx->csCtx.frames);
    VEC3F_LERPIMPDST(vec, &startPos, &endPos, lerp);
}
