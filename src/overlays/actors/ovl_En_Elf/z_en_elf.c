/*
 * File: z_en_elf.c
 * Overlay: ovl_En_Elf
 * Description: Fairies
 */

#include "z_en_elf.h"

#define FLAGS 0x02000030

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

extern SkeletonHeader D_0402AF58;

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

static Color_RGBAf D_808909E4[] = {
    { 255.0f, 255.0f, 230.0f, 255.0f },
    { 255.0f, 220.0f, 220.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

static Color_RGBAf D_80890A14[] = {
    { 220.0f, 160.0f, 80.0f, 255.0f },
    { 255.0f, 50.0f, 100.0f, 255.0f },
    { 255.0f, 150.0f, 0.0f, 255.0f },
};

static u8 D_80890A44[][3] = {
    { 0x00, 0x00, 0x00 }, 
    { 0x01, 0x00, 0x00 }, 
    { 0x01, 0x02, 0x00 }, 
    { 0x01, 0x00, 0x02 },
    { 0x00, 0x01, 0x00 }, 
    { 0x02, 0x01, 0x00 }, 
    { 0x00, 0x01, 0x02 }, 
    { 0x00, 0x00, 0x01 },
    { 0x02, 0x00, 0x01 }, 
    { 0x00, 0x02, 0x01 }, 
    { 0x01, 0x01, 0x00 }, 
    { 0x01, 0x00, 0x01 },
    { 0x00, 0x01, 0x01 }, 
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
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_250 = 5.0f;
            this->unk_254 = 20.0f;
            break;

        case 10:
            this->unk_24A = 0x400;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->unk_25C = 0x64;
            this->unk_250 = 1.0f;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_254 = 5.0f;
            break;

        case 8:
            this->unk_24A = 0x400;
            this->unk_24C = 0;
            this->unk_26C = func_8088D3EC;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_254 = 0.0f;
            this->unk_250 = 5.0f;
            break;

        case 7:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_250 = 3.0f;
            this->unk_254 = 10.0f;
            break;

        case 5:
            this->unk_26C = func_8088D3EC;
            this->unk_24A = 0x1E;
            this->unk_25C = 1;
            this->unk_250 = 0.0f;
            this->unk_254 = 0.0f;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            break;

        case 6:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x200;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 0.0f;
            this->unk_254 = 0.0f;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            break;

        case 1:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x800;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 5.0f;
            this->unk_254 = 7.5f;
            this->skelAnime.animPlaybackSpeed = 2.0f;
            break;

        case 2:
            this->unk_24A = 0x400;
            this->unk_24C = 0x1000;
            this->unk_26C = func_8088D470;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_250 = 10.0f;
            this->unk_254 = 20.0f;
            break;

        case 3:
            this->unk_24C = 0x600;
            this->unk_26C = func_8088D504;
            this->unk_254 = 1.0f;
            this->unk_250 = 1.0f;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            break;

        case 4:
            this->unk_24A = 0x1000;
            this->unk_24C = 0x800;
            this->unk_26C = func_8088D3EC;
            this->unk_250 = 60.0f;
            this->unk_254 = 20.0f;
            this->skelAnime.animPlaybackSpeed = 2.0f;
            break;

        case 9:
            this->unk_24A = 0x400;
            this->unk_24C = 0x2000;
            this->unk_26C = func_8088D3EC;
            this->unk_25C = 0x2A;
            this->unk_254 = 1.0f;
            this->skelAnime.animPlaybackSpeed = 1.0f;
            this->unk_250 = 5.0f;
            break;
    }
}

s32 func_8088C804(Vec3f* arg0, Vec3f* arg1, f32 arg2) {
    f32 temp_f0 = arg1->x - arg0->x;
    f32 temp_f2 = arg1->z - arg0->z;

    return SQ(arg2) < SQ(temp_f0) + SQ(temp_f2);
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
    f32 sp24;

    if (this->unk_25C > 0) {
        this->unk_25C--;
    } else {
        sp24 = this->actor.xzDistToPlayer;

        if (sp24 < 50.0f) {
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
            if (sp24 > 150.0f) {
                sp24 = 150.0f;
            }
            sp24 = ((sp24 - 50.0f) * 0.95f) + 0.05f;
            if (Rand_ZeroOne() < sp24) {
                this->unk_244 = 3;
                this->unk_248 = 0x200;
                this->unk_254 = (2.0f * sp24) + 1.0f;
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

    if (this->unk_262 & 0x4000) {
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
    this->unk_258 = randPlusMinusPoint5Scaled(32767.0f);
    this->unk_26C = func_8088C9CC;
    func_8088CBAC(this, globalCtx);
    this->unk_25C = 0;
    this->unk_25E = 0xF0;
    if ((this->unk_262 & 0x400) && Actor_GetCollectibleFlag(globalCtx, this->unk_260)) {
        Actor_MarkForDeath(&this->actor);
    }
}

f32 func_8088CD3C(s32 arg0) {
    switch (arg0) {
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
    s32 sp48;
    s32 params;

    Actor_ProcessInitChain(thisx, sInitChain);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_0402AF58, &D_04029140, this->jointTable, this->morphTable, 7);
    ActorShape_Init(&thisx->shape, 0.0f, NULL, 15.0f);
    thisx->shape.shadowAlpha = 255;
    Lights_PointGlowSetInfo(&this->lightInfo1, thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0xFF, 0xFF, 0xFF, 0);
    this->lightNode1 = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo1);
    Lights_PointNoGlowSetInfo(&this->lightInfo2, thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0xFF, 0xFF, 0xFF, 0);
    this->lightNode2 = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo2);
    this->unk_262 = 0;
    this->unk_25E = 0x258;
    this->unk_240 = 0.0f;
    sp48 = 0;

    this->unk_260 = (this->actor.params & 0xFE00) >> 9;
    params = this->actor.params & 0xF;
    if (thisx->params & 0x100) {
        this->unk_262 |= 0x400;
    }

    this->actor.params = params;
    switch (params) {
        case 0:
            thisx->room = -1;
            EnElf_SetupAction(this, func_8088E850);
            func_8088C51C(this, 0);
            this->unk_262 |= 4;
            thisx->update = func_8089010C;
            this->unk_230 = 0;
            this->unk_234 = 0;
            this->unk_269 = 20;
            if ((gSaveContext.naviTimer >= 0x64C8) || (gSaveContext.naviTimer < 0xBB8)) {
                gSaveContext.naviTimer = 0;
            }
            this->unk_266 = func_800F05C0(globalCtx);
            break;

        case 1:
            sp48 = -1;
            gSaveContext.unk_1016 = 0;
            EnElf_SetupAction(this, func_8088E0F0);
            this->unk_254 = Math_Vec3f_DistXZ(&thisx->world.pos, &player->actor.world.pos);
            this->unk_248 = player->actor.shape.rot.y;
            this->unk_24C = -0x1000;
            this->unk_224.y = thisx->world.pos.y - player->actor.world.pos.y;
            this->unk_246 = 0;
            this->unk_250 = 0.0f;
            break;

        case 5:
            sp48 = -1;
            EnElf_SetupAction(this, func_8088E484);
            this->unk_254 = 0.0f;
            this->unk_248 = player->actor.shape.rot.y;
            this->unk_24C = 0;
            this->unk_224.y = thisx->world.pos.y - player->actor.world.pos.y;
            this->unk_246 = 0;
            this->unk_250 = 7.0f;
            break;

        case 7:
            this->unk_262 |= 0x200;
            thisx->shape.shadowDraw = func_800B4088;
            this->unk_262 |= 0x100;
            sp48 = -1;
            this->unk_262 |= 0x800;
            this->unk_262 |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 2:
            this->unk_262 |= 0x100;
            sp48 = -1;
            this->unk_262 |= 0x800;
            this->unk_262 |= 0x2000;
            this->unk_262 |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 6:
            sp48 = -1;
            this->unk_262 |= 0x800;
            this->unk_262 |= 0x2000;
            this->unk_262 |= 0x1000;
            func_8088CC48(this, globalCtx);
            break;

        case 9:
            this->unk_262 |= 0x1000;

        case 10:
            sp48 = -2;
            func_8088CC48(this, globalCtx);
            break;

        case 8:
            Actor_MarkForDeath(thisx);
            return;

        case 3:
            sp48 = Rand_ZeroFloat(11.99f) + 1.0f;
            EnElf_SetupAction(this, func_8088E018);
            func_8088C51C(this, 0);
            break;

        case 4:
            EnElf_SetupAction(this, func_8088E0E0);
            func_8088C51C(this, 6);
            this->unk_262 |= 8;
            {
                s32 i;

                for (i = 0; i < 8; i++) {
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, thisx->world.pos.x, thisx->world.pos.y - 30.0f, thisx->world.pos.z, 0, 0, 0, 6);
                }
            }
            break;
    }

    this->unk_23C = 3.0f;
    this->unk_1DC = D_808909E4[0];
    if (sp48 > 0) {
        this->unk_1EC.r = func_8088CD3C(D_80890A44[sp48][0]);
        this->unk_1EC.g = func_8088CD3C(D_80890A44[sp48][1]);
        this->unk_1EC.b = func_8088CD3C(D_80890A44[sp48][2]);
        this->unk_1EC.a = 0;
    } else {
        this->unk_1DC = D_808909E4[sp48 * -1];
        this->unk_1EC = D_80890A14[sp48 * -1];
    }
}

void EnElf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElf* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode1);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode2);
}

void func_8088D3EC(EnElf* this, GlobalContext* globalCtx) {
    this->unk_224.x = Math_SinS(this->unk_248) * this->unk_254;
    this->unk_224.y = Math_SinS(this->unk_246) * this->unk_250;
    this->unk_224.z = Math_CosS(this->unk_248) * this->unk_254;
    this->unk_248 += this->unk_24C;
    this->unk_246 += this->unk_24A;
}

void func_8088D470(EnElf* this, GlobalContext* globalCtx) {
    f32 sp24 = (Math_CosS(this->unk_246) * this->unk_250) + this->unk_254;

    this->unk_224.x = Math_SinS(this->unk_248) * sp24;
    this->unk_224.y = 0.0f;
    this->unk_224.z = Math_CosS(this->unk_248) * sp24;

    this->unk_248 += this->unk_24C;
    this->unk_246 += this->unk_24A;
}

void func_8088D504(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_246 = (u16)this->unk_248 * 2;
    this->unk_224.x = Math_SinS(this->unk_248) * this->unk_254;
    this->unk_224.y = Math_SinS(this->unk_246) * this->unk_250;
    this->unk_224.z = -Math_SinS(player->actor.shape.rot.y) * this->unk_224.x;

    this->unk_224.x = Math_CosS(player->actor.shape.rot.y) * this->unk_224.x;

    this->unk_248 += this->unk_24C;
}

void func_8088D5A0(EnElf* this, Vec3f* arg1, f32 arg2) {
    f32 temp_f2 = ((arg1->y + this->unk_224.y) - this->actor.world.pos.y) * arg2;
    f32 temp_f0 = fabsf(temp_f2);
    f32 phi_f12;

    if (temp_f2 >= 0.0f) {
        phi_f12 = 1.0f;
    } else {
        phi_f12 = -1.0f;
    }

    temp_f0 = CLAMP(temp_f0, 0.0f, 30.0f);
    Math_StepToF(&this->actor.velocity.y, temp_f0 * phi_f12, 32.0f);
}

void func_8088D660(EnElf* this, Vec3f* arg1, f32 arg2) {
    f32 sp34 = ((arg1->x + this->unk_224.x) - this->actor.world.pos.x) * arg2;
    f32 sp28 = ((arg1->z + this->unk_224.z) - this->actor.world.pos.z) * arg2;
    f32 temp_f14;
    f32 temp_f2;

    temp_f14 = (sp34 >= 0.0f) ? 1.0f : -1.0f;
    temp_f2 = (sp28 >= 0.0f) ? 1.0f : -1.0f;

    sp34 = fabsf(sp34);
    sp28 = fabsf(sp28);

    sp34 = CLAMP(sp34, 0.0f, 30.0f) * temp_f14;
    sp28 = CLAMP(sp28, 0.0f, 30.0f) * temp_f2;

    func_8088D5A0(this, arg1, arg2);
    Math_StepToF(&this->actor.velocity.x, sp34, 1.5f);
    Math_StepToF(&this->actor.velocity.z, sp28, 1.5f);
    Actor_ApplyMovement(&this->actor);
}

void func_8088D7F8(EnElf* this, Vec3f* arg1) {
    func_8088D5A0(this, arg1, 0.2f);
    this->actor.velocity.x = 0.0f;
    this->actor.velocity.z = 0.0f;
    Actor_ApplyMovement(&this->actor);
    this->actor.world.pos.x = arg1->x + this->unk_224.x;
    this->actor.world.pos.z = arg1->z + this->unk_224.z;
}

void func_8088D864(EnElf* this, Vec3f* arg1) {
    func_8088D5A0(this, arg1, 0.2f);
    this->actor.velocity.z = 0.0f;
    this->actor.velocity.x = 0.0f;
    Actor_ApplyMovement(&this->actor);
    this->actor.world.pos.x = arg1->x + this->unk_224.x;
    this->actor.world.pos.z = arg1->z + this->unk_224.z;
}

void func_8088D8D0(EnElf* this, Vec3f* arg1) {
    f32 temp_f0;
    f32 temp_f2 = (((Math_SinS(this->unk_246) * this->unk_250) + arg1->y) - this->actor.world.pos.y) * 0.2f;
    f32 phi_f12;

    temp_f0 = fabsf(temp_f2);
    phi_f12 = (temp_f2 >= 0.0f) ? 1.0f : -1.0f;

    this->unk_246 += this->unk_24A;
    temp_f0 = CLAMP(temp_f0, 0.0f, 30.0f);

    Math_StepToF(&this->actor.velocity.y, temp_f0 * phi_f12, 1.5f);
}

void func_8088D9BC(EnElf* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_a1;
    Vec3f* temp = &this->unk_224;

    if (this->unk_262 & 0x4000) {
        Math_SmoothStepToF(&this->actor.speedXZ, 5.0f, 0.5f, 1.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&this->actor.speedXZ, this->unk_254, 0.2f, 0.5f, 0.01f);
    }

    switch (this->unk_244) {
        case 0:
            phi_a1 = Math_FAtan2F(-(this->actor.world.pos.z - temp->z), 
                                  -(this->actor.world.pos.x - temp->x));
            break;

        case 3:
            phi_a1 = Math_FAtan2F(-(this->actor.world.pos.z - player->actor.world.pos.z), 
                                  -(this->actor.world.pos.x - player->actor.world.pos.x));
            break;

        case 2:
            phi_a1 = Math_FAtan2F(this->actor.world.pos.z - player->actor.world.pos.z, 
                                  this->actor.world.pos.x - player->actor.world.pos.x);
            break;

        default:
            phi_a1 = this->unk_24C;
            break;
    }

    if (this->unk_262 & 0x4000) {
        Math_SmoothStepToS(&this->unk_258, phi_a1, 10, this->unk_248, 0x1000);
    } else {
        Math_SmoothStepToS(&this->unk_258, phi_a1, 10, this->unk_248, 0x20);
    }

    this->actor.world.rot.y = this->unk_258;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_8088DB4C(EnElf* this, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f12;

    sp24 = ((arg1->x + this->unk_224.x) - this->actor.world.pos.x) * arg4;
    sp20 = ((arg1->z + this->unk_224.z) - this->actor.world.pos.z) * arg4;
    arg4 += 0.3f;
    arg3 += 30.0f;

    func_8088D5A0(this, arg1, arg4);

    temp_f0 = sqrtf(SQ(sp24) + SQ(sp20));
    temp_f12 = CLAMP(temp_f0, arg2, arg3);
    this->actor.speedXZ = temp_f12;

    if ((temp_f0 != temp_f12) && (temp_f0 != 0.0f)) {
        temp_f0 = temp_f12 / temp_f0;
        sp24 *= temp_f0;
        sp20 *= temp_f0;
    }

    Math_StepToF(&this->actor.velocity.x, sp24, 5.0f);
    Math_StepToF(&this->actor.velocity.z, sp20, 5.0f);
    Actor_ApplyMovement(&this->actor);
}

s32 func_8088DCA4(EnElf* this) {
    if (this->unk_25E > 0) {
        this->unk_25E--;
    } else {
        this->unk_25E--;
        if (this->unk_25E >= -9) {
            Actor_SetScale(&this->actor, (this->unk_25E + 10) * 0.008f * 0.1f);
        } else {
            Actor_MarkForDeath(&this->actor);
            return 1;
        }
    }
    return 0;
}

void func_8088DD34(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Player* player2 = GET_PLAYER(globalCtx);
    f32 temp;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (Rand_ZeroOne() < 0.05f) {
        this->unk_250 = Rand_ZeroFloat(10.0f) + 10.0f;
        this->unk_24A = (s32)Rand_ZeroFloat(1024.0f) + 0x200;
    }

    func_8088CBAC(this, globalCtx);
    if (this->unk_262 & 0x800) {
        this->unk_224.y = player2->bodyPartsPos[0].y;
    }

    func_8088D8D0(this, &this->unk_224);
    func_8088D9BC(this, globalCtx);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (this->unk_262 & 0x400) {
            Actor_SetCollectibleFlag(globalCtx, this->unk_260);
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_801233E4(globalCtx)) {
        if ((this->unk_262 & 0x4000) && (this->unk_262 & 0x100) && func_8088DCA4(this)) {
            return;
        }
        return;
    }

    temp = this->actor.world.pos.y - player->actor.world.pos.y;
    if ((this->unk_262 & 0x1000) && (temp > 0.0f) && (temp < 60.0f) && !func_8088C804(&this->actor.world.pos, &player->actor.world.pos, 10.0f)) {
        func_80115908(globalCtx, 0x80);
        if (this->unk_262 & 0x200) {
            Parameter_AddMagic(globalCtx, ((void)0, gSaveContext.unk_3F30) + (gSaveContext.doubleMagic * 0x30) + 0x30);
        }
        gSaveContext.unk_1016 = 0;
        this->unk_254 = 50.0f;
        this->unk_248 = player->actor.shape.rot.y;
        this->unk_24C = -0x1000;
        this->unk_224.y = 30.0f;
        this->unk_250 = 0.0f;
        this->unk_246 = 0;
        EnElf_SetupAction(this, func_8088E0F0);
        if (this->unk_262 & 0x400) {
            Actor_SetCollectibleFlag(globalCtx, this->unk_260);
        }
        return;
    }

    if (this->unk_262 & 0x100) {
        if (func_8088DCA4(this)) {
            return;
        }
    } else {
        Actor_SetScale(&this->actor, 0.008f);
    }
    
    if (this->unk_262 & 0x2000) {
        func_800B8A1C(&this->actor, globalCtx, 0xBA, 80.0f, 60.0f);
    }
}

void func_8088E018(EnElf* this, GlobalContext* globalCtx) {
    Vec3f sp2C;
    Actor* parent;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8088D3EC(this, globalCtx);
    parent = this->actor.parent;

    if ((parent != NULL) && (parent->update != NULL)) {
        sp2C = this->actor.parent->world.pos;
        sp2C.y += (1500.0f * this->actor.scale.y) + 40.0f;
        func_8088D660(this, &sp2C, 0.2f);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
}

void func_8088E0E0(EnElf* this, GlobalContext* globalCtx) {
}

void func_8088E0F0(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothStepToF(&this->unk_254, 30.0f, 0.1f, 4.0f, 1.0f);
    this->unk_224.x = Math_CosS(this->unk_248) * this->unk_254;
    this->unk_224.y += this->unk_250;

    switch (this->unk_246) {
        case 0:
            if (this->unk_250 < 2.0f) {
                this->unk_250 += 0.1f;
            } else {
                gSaveContext.healthAccumulator = 0xA0;
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
    func_8088F5F4(this, globalCtx, 0x20);
    Audio_PlayActorSound2(&this->actor, 0x20A8);
}

void func_8088E304(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
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
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
}

void func_8088E484(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
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
    Actor_SetScale(&this->actor, (1.0f - (SQ(this->unk_250) * 0.012345679f)) * 0.008f);
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    func_8088F5F4(this, globalCtx, 0x20);
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
}

void func_8088E5A8(EnElf* this, GlobalContext* globalCtx) {
    if (this->unk_262 & 4) {
        func_8088EFA4(this, globalCtx);
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    this->unk_26C(this, globalCtx);
}

void func_8088E60C(EnElf* this, GlobalContext* globalCtx) {
    s16 sp36;
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags1 & 0x400) {
        sp36 = 200;
    } else {
        sp36 = 100;
    }

    if ((this->unk_244 == 6) || (player->stateFlags1 & 2) || (this->unk_262 & 0x8000)) {
        sp36 = 0;
    }

    if (func_800EE29C(globalCtx, 0xC9)) {
        if (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0xC9)]->unk0 == 6) {
            sp36 = 0;
        }
    }

    if (this->unk_262 & 0x20) {
        Player* player = GET_PLAYER(globalCtx);

        Lights_PointNoGlowSetInfo(&this->lightInfo2, player->actor.world.pos.x, player->actor.world.pos.y + 60.0f, player->actor.world.pos.z, 0xFF, 0xFF, 0xFF, 0xC8);
    } else {
        Lights_PointNoGlowSetInfo(&this->lightInfo2, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0xFF, 0xFF, 0xFF, -1);
    }

    Lights_PointGlowSetInfo(&this->lightInfo1, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0xFF, 0xFF, 0xFF, sp36);
    this->unk_258 = Math_FAtan2F(this->actor.velocity.z, this->actor.velocity.x);
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void func_8088E850(EnElf* this, GlobalContext* globalCtx) {
    Vec3f sp4C;
    Player* player = GET_PLAYER(globalCtx);
    Actor* sp44;
    f32 sp40;
    f32 sp3C;
    u32 sp38;

    if (globalCtx) {}

    func_8088F214(this, globalCtx);
    func_8088E5A8(this, globalCtx);
    sp40 = 0.0f;

    if (func_800EE29C(globalCtx, 0xC9)) {
        sp38 = func_800EE200(globalCtx, 0xC9);
        func_808908D0(&sp4C, globalCtx, sp38);
        this->actor.shape.rot.y = globalCtx->csCtx.npcActions[sp38]->unk8;
        this->actor.shape.rot.x = globalCtx->csCtx.npcActions[sp38]->unk6;
        if (globalCtx->csCtx.npcActions[sp38]->unk0 == 5) {
            func_8088F5F4(this, globalCtx, 0x10);
        }

        if (this->unk_244 == 8) {
            func_8088D864(this, &sp4C);
        } else {
            func_8088D660(this, &sp4C, 0.2f);
        }

        if ((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.unk_12 == 0) && ((globalCtx->csCtx.frames == 0x95) || (globalCtx->csCtx.frames == 0x17D) || (globalCtx->csCtx.frames == 0x24F))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
        }

        if ((globalCtx->sceneNum == SCENE_SECOM) && (gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.unk_12 == 4) && (globalCtx->csCtx.frames == 0x5F)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
        }
    } else {
        this->actor.shape.rot.x = 0;
        sp3C = Math_Vec3f_DistXYZ(&player->bodyPartsPos[8], &this->actor.world.pos);
        switch (this->unk_244) {
            case 5:
                func_8088D660(this, &player->bodyPartsPos[8], 1.0f - (this->unk_24A * 0.033333335f));
                sp40 = Math_Vec3f_DistXYZ(&player->bodyPartsPos[8], &this->actor.world.pos);

                if (sp3C < 7.0f) {
                    this->unk_25C = 0;
                    sp40 = 0;
                } else if (sp3C < 25.0f) {
                    sp40 = (sp40 - 5.0f) * 0.05f;
                    sp40 = 1.0f - sp40;
                    sp40 = (1.0f - SQ(sp40)) * 0.008f;
                } else {
                    sp40 = 0.008f;
                }
                func_8088F5F4(this, globalCtx, 16);
                break;

            case 6:
                func_8088D660(this, &player->bodyPartsPos[8], 0.2f);
                this->actor.world.pos = player->bodyPartsPos[8];
                break;

            case 9:
                sp4C = player->bodyPartsPos[8];
                sp4C.y += 1500.0f * this->actor.scale.y;

                func_8088D7F8(this, &sp4C);
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
                sp4C = GET_ACTIVE_CAM(globalCtx)->eye;
                sp4C.y += -2000.0f * this->actor.scale.y;
                func_8088DB4C(this, &sp4C, 0.0f, 30.0f, 0.2f);
                break;

            default:
                sp44 = globalCtx->actorCtx.targetContext.unk38;
                if ((player->stateFlags1 & 0x40) && (player->targetActor != NULL)) {
                    Math_Vec3f_Copy(&sp4C, &player->targetActor->focus.pos);
                } else {
                    Math_Vec3f_Copy(&sp4C, &globalCtx->actorCtx.targetContext.unk0);
                }
                sp4C.y += 1500.0f * this->actor.scale.y;

                if (sp44 != NULL) {
                    func_8088DB4C(this, &sp4C, 0.0f, 30.0f, 0.2f);
                    if (this->actor.speedXZ >= 5.0f) {
                        func_8088F5F4(this, globalCtx, 0x10);
                    }
                } else {
                    if (!(this->unk_25A & 0x1F)) {
                        this->unk_23C = Rand_ZeroFloat(7.0f) + 3.0f;
                    }

                    if (this->unk_262 & 2) {
                        if (sp3C < 30.0f) {
                            this->unk_262 ^= 2;
                        }
                        func_8088DB4C(this, &sp4C, 0.0f, 30.0f, 0.2f);
                        func_8088F5F4(this, globalCtx, 0x10);
                    } else {
                        if (sp3C > 100.0f) {
                            this->unk_262 |= 2;
                            if (this->unk_269 == 0) {
                                Audio_PlayActorSound2(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
                            }
                            this->unk_25C = 100;
                        }
                        func_8088DB4C(this, &sp4C, 0.0f, this->unk_23C, 0.2f);
                    }
                }
                break;
        }
    }

    if (this->unk_244 == 5) {
        this->actor.scale.x = sp40;
    } else if (this->unk_244 == 6) {
        this->actor.scale.x = 0.0f;
    } else {
        Math_SmoothStepToF(&this->actor.scale.x, 0.008f, 0.3f, 0.00080000004f, 0.000080000005f);
    }

    func_8088E60C(this, globalCtx);

    if (!func_800EE29C(globalCtx, 0xC9)) {
        this->actor.shape.rot.y = this->unk_258;
    }
}

void func_8088EF18(Color_RGBAf* arg0, Color_RGBAf* arg1, Color_RGBAf* arg2, f32 arg3) {
    f32 r = arg1->r - arg2->r;
    f32 g = arg1->g - arg2->g;
    f32 b = arg1->b - arg2->b;
    f32 a = arg1->a - arg2->a;

    arg0->r += r * arg3;
    arg0->g += g * arg3;
    arg0->b += b * arg3;
    arg0->a += a * arg3;
}

void func_8088EFA4(EnElf* this, GlobalContext* globalCtx) {
    Actor* sp2C = globalCtx->actorCtx.targetContext.unk38;
    Player* player = GET_PLAYER(globalCtx);
    f32 sp24;

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
            this->unk_1DC.r = 255.0f;
            this->unk_1DC.g = 0.0f;
            this->unk_1DC.b = 0.0f;
            this->unk_1DC.a = 255.0f;

            this->unk_1EC.r = 200.0f;
            this->unk_1EC.g = 80.0f;
            this->unk_1EC.b = 80.0f;
            this->unk_1EC.a = 0.0f;
        }
    } else if (globalCtx->actorCtx.targetContext.unk40 != 0.0f) {
        this->unk_268 = 0;
        this->unk_238 = 1.0f;
        if (!this->unk_269) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
        }
    } else if (this->unk_268 == 0) {
        if ((sp2C == NULL) || (Math_Vec3f_DistXYZ(&this->actor.world.pos, &globalCtx->actorCtx.targetContext.unk0) < 50.0f)) {
            this->unk_268 = 1;
        }
    } else if (this->unk_238 != 0.0f) {
        if (Math_StepToF(&this->unk_238, 0.0f, 0.25f)) {
            this->unk_1DC = globalCtx->actorCtx.targetContext.unk18;
            this->unk_1EC = globalCtx->actorCtx.targetContext.unk28;
        } else {
            sp24 = 0.25f / this->unk_238;
            func_8088EF18(&this->unk_1DC, &globalCtx->actorCtx.targetContext.unk18, &this->unk_1DC, sp24);
            func_8088EF18(&this->unk_1EC, &globalCtx->actorCtx.targetContext.unk28, &this->unk_1EC, sp24);
        }
    }

    if (this->unk_262 & 1) {
        if ((sp2C == NULL) || (player->unk_730 == NULL)) {
            this->unk_262 ^= 1;
        }
    } else if ((sp2C != NULL) && (player->unk_730 != NULL)) {
        u8 temp = this->unk_269;
        u16 sound = this->unk_269 == 0 ? NA_SE_PL_WALK_GROUND - SFX_FLAG : NA_SE_PL_WALK_GROUND - SFX_FLAG;

        if (!temp) {
            Audio_PlayActorSound2(&this->actor, sound);
        }
        this->unk_262 |= 1;
    }
}

void func_8088F214(EnElf* this, GlobalContext* globalCtx) {
    s32 sp34;
    Actor* actor;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if (globalCtx->csCtx.state != 0) {
        if (func_800EE29C(globalCtx, 0xC9)) {
            switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0xC9)]->unk0) {
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
        actor = globalCtx->actorCtx.targetContext.unk38;
        if (player->stateFlags1 & 0x400) {
            sp34 = 10;
            this->unk_25C = 100;
        } else if ((actor == NULL) || (actor->category == 4)) {
            if (actor != NULL) {
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
                                Audio_PlayActorSound2(&this->actor, NA_SE_EV_NAVY_VANISH);
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
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_NAVY_VANISH);
                    }
                }
                break;

            case 6:
                if (player->stateFlags2 & 0x100000) {
                    sp34 = 9;
                    this->unk_25C = 0x2A;
                    if (this->unk_269 == 0) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_BELL_DASH_NORMAL);
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

void func_8088F5F4(EnElf* this, GlobalContext* globalCtx, s32 arg2) {
    static Vec3f D_80890A6C = { 0.0f, -0.05f, 0.0f };
    static Vec3f D_80890A78 = { 0.0f, -0.025f, 0.0f };
    s32 pad;
    Vec3f sp38;
    Color_RGBA8 sp34;
    Color_RGBA8 sp30;

    if (!(this->unk_262 & 8)) {
        sp38.x = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.x;
        sp38.y = (Rand_ZeroOne() * 6.0f) + this->actor.world.pos.y;
        sp38.z = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.z;

        sp34.r = this->unk_1DC.r;
        sp34.g = this->unk_1DC.g;
        sp34.b = this->unk_1DC.b;

        sp30.r = this->unk_1EC.r;
        sp30.g = this->unk_1EC.g;
        sp30.b = this->unk_1EC.b;

        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp38, &D_80890A6C, &D_80890A78, &sp34, &sp30, 0x3E8, arg2);
    }
}

void func_8088F9E4(Actor* thisx, GlobalContext* globalCtx) {
    EnElf* this = THIS;
    s32 sp28;

    thisx->floorHeight = func_800C4188(globalCtx, &globalCtx->colCtx, &thisx->floorPoly, &sp28, &this->actor, &thisx->world.pos);
    thisx->shape.shadowAlpha = 50;
}

void func_8088FA38(EnElf* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_262 & 0x10) {
        sp34 = globalCtx->actorCtx.targetContext.unk0;
        if (this->unk_234 != 0) {
            sp34 = this->unk_234->world.pos;
        } else {
            if ((player->unk_730 == NULL) || (&player->actor == player->unk_730) || (&this->actor == player->unk_730) || (this->unk_264 & 4)) {
                sp34.x = player->bodyPartsPos[7].x + (Math_SinS(player->actor.shape.rot.y) * 20.0f);
                sp34.y = player->bodyPartsPos[7].y + 5.0f;
                sp34.z = player->bodyPartsPos[7].z + (Math_CosS(player->actor.shape.rot.y) * 20.0f);
                this->unk_264 &= ~4;
            }
        }
        this->actor.focus.pos = sp34;
        this->unk_262 &= ~0x10;
    }

    func_8088E5A8(this, globalCtx);
    sp34 = this->actor.focus.pos;
    func_8088DB4C(this, &sp34, 0, 30.0f, 0.2f);

    if (this->actor.speedXZ >= 5.0f) {
        func_8088F5F4(this, globalCtx, 0x10);
    }

    Math_SmoothStepToF(&this->actor.scale.x, 0.008f, 0.3f, 0.00080000004f, 0.000080000005f);
    func_8088E60C(this, globalCtx);
}

void func_8088FC34(EnElf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_258, 5, 0x1000, 0x400);
    this->unk_25A++;
    if (this->unk_234 == 0) {
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
    this->unk_262 &= ~0x20;
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

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 4:
            if (func_80147624(globalCtx)) {
                if (globalCtx->msgCtx.unk11F04 == 0x202) {
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
                        func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 - 1);
                        break;

                    case 1:
                        func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                        break;
                }
            }
            break;

        case 5:
            if (func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.unk11F04) {
                    case 576:
                        func_80151938(globalCtx, 0x245);
                        break;

                    case 541:
                    case 542:
                    case 543:
                    case 544:
                    case 545:
                    case 546:
                    case 547:
                    case 575:
                    case 577:
                    case 578:
                    case 579:
                    case 580:
                        switch (CURRENT_DAY) {
                            case 1:
                                func_80151938(globalCtx, 0x246);
                                break;

                            case 2:
                                func_80151938(globalCtx, 0x247);
                                break;

                            case 3:
                                if (gSaveContext.isNight == 0) {
                                    func_80151938(globalCtx, 0x248);
                                } else if ((gSaveContext.time < 0x4000) && (gSaveContext.weekEventReg[74] & 0x20)) {
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
    u16 temp_v0 = func_800F05C0(globalCtx);

    if (temp_v0 != this->unk_266) {
        this->unk_266 = temp_v0;
        gSaveContext.naviTimer = 0;
    }

    if ((player->tatlTextId == 0) && (player->unk_730 == NULL)) {
        if ((gSaveContext.naviTimer >= 0x258) && (gSaveContext.naviTimer < 0xBB9)) {
            player->tatlTextId = func_800F05C0(globalCtx);
        }
    }

    if (player->tatlTextId < 0) {
        thisx->flags |= 0x10000;
    }

    if (func_800B84D0(thisx, globalCtx)) {
        func_8019FDC8(&D_801DB4A4, 0x6873, 0x20);
        thisx->focus.pos = thisx->world.pos;

        if (thisx->textId == func_800F05C0(globalCtx)) {
            this->unk_262 |= 0x80;
            gSaveContext.naviTimer = 0xBB9;
        }

        this->unk_262 |= 0x10;
        this->unk_262 |= 0x20;
        thisx->update = func_8088FE64;
        func_8088C51C(this, 3);
        if (this->unk_230 != NULL) {
            this->unk_230->flags |= 0x100;
            thisx->cutscene = this->unk_230->cutscene;
            if (thisx->cutscene != -1) {
                func_8088FD04(this);
            }
            if (this->unk_230->home.rot.x == -0x961) {
                this->unk_234 = this->unk_230;
                func_800B86C8(thisx, globalCtx, this->unk_230);
            }
        } else {
            thisx->cutscene = -1;
        }
        thisx->flags &= ~0x10000;
    } else if (this->unk_264 & 4) {
        thisx->focus.pos = thisx->world.pos;
        this->unk_262 |= 0x10;
        this->unk_262 |= 0x20;
        thisx->update = func_8088FE64;
        func_8088C51C(this, 3);
    } else {
        this->actionFunc(this, globalCtx);

        if (func_801690CC(globalCtx) == 0) {
            if (gSaveContext.naviTimer < 0x64C8) {
                gSaveContext.naviTimer++;
            } else if (!(this->unk_262 & 0x80)) {
                gSaveContext.naviTimer = 0;
            }
        }
    }

    this->unk_230 = NULL;
    this->unk_25A++;
    if ((this->unk_240 >= 0.0f) && (func_800FD2B4(globalCtx, SQ(this->unk_240) * this->unk_240, player->actor.projectedPos.z + 780.0f, 0.2f, 0.5f))) {
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
    this->unk_25A++;
    if (this->unk_262 & 0x200) {
        func_8088F9E4(thisx, globalCtx);
    }
}

s32 func_80890494(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80890A84 = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnElf* this = THIS;
    Vec3f sp34;
    f32 temp_f20;

    if (limbIndex == 6) {
        temp_f20 = ((Math_SinS(this->unk_25A << 0xC) * 0.1f) + 1.0f) * 0.012f;
        if (this->unk_262 & 0x200) {
            temp_f20 = 2.0f * temp_f20;
        }
        temp_f20 *= this->actor.scale.x * 124.99999f;

        SysMatrix_MultiplyVector3fByState(&D_80890A84, &sp34);
        SysMatrix_InsertTranslation(sp34.x, sp34.y, sp34.z, MTXMODE_NEW);
        Matrix_Scale(temp_f20, temp_f20, temp_f20, MTXMODE_APPLY);
    }
    if ((this->unk_262 & 0x200) && 
        ((limbIndex == 4) || (limbIndex == 7) || 
         (limbIndex == 11) || (limbIndex == 14))) {
        *dList = NULL;
    }
    return false;
}

void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnElf* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s32 pad2;

    if (player->currentMask != PLAYER_MASK_GIANTS_MASK) {
        if (!(this->unk_262 & 8) && 
            (!func_800EE29C(globalCtx, 0xC9) || (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0xC9)]->unk0 != 6)) && 
            (!(player->stateFlags1 & 0x100000) || (kREG(90) < this->actor.projectedPos.z))) {
            Gfx* alloc = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 4);
            f32 phi_f0;
            s32 phi_a0;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C94C(globalCtx->state.gfxCtx);

            phi_a0 = (this->unk_25A * 50) & 0x1FF;
            phi_a0 = (phi_a0 >= 0x100) ? 511 - phi_a0 : phi_a0;

            phi_f0 = (this->unk_25E < 0) ? (this->unk_25E * 0.0011666666f) + 1.0f : 1.0f;

            gSPSegment(POLY_XLU_DISP++, 0x08, alloc);

            gDPPipeSync(alloc++);
            gDPSetPrimColor(alloc++, 0, 0x01, (u8)(s8)this->unk_1DC.r, (u8)(s8)this->unk_1DC.g, (u8)(s8)this->unk_1DC.b, (u8)(s8)(this->unk_1DC.a * phi_f0));

            if (this->unk_262 & 4) {
                gDPSetRenderMode(alloc++, G_RM_PASS, G_RM_CLD_SURF2);
            } else {
                gDPSetRenderMode(alloc++, G_RM_PASS, G_RM_ZB_CLD_SURF2);
            }

            gSPEndDisplayList(alloc);

            gDPSetEnvColor(POLY_XLU_DISP++, (u8)(s8)this->unk_1EC.r, (u8)(s8)this->unk_1EC.g, (u8)(s8)this->unk_1EC.b, (u8)(s8)(phi_a0 * phi_f0));

            POLY_XLU_DISP = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80890494, NULL, &this->actor, POLY_XLU_DISP);
            
            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void func_808908D0(Vec3f* arg0, GlobalContext* globalCtx, u32 arg2) {
    Vec3f sp24;
    Vec3f sp18;
    CsCmdActorAction* temp_v0 = globalCtx->csCtx.npcActions[arg2];
    f32 temp_f0;

    sp24.x = temp_v0->unk0C.x;
    sp24.y = temp_v0->unk0C.y;
    sp24.z = temp_v0->unk0C.z;

    sp18.x = temp_v0->unk18.x;
    sp18.y = temp_v0->unk18.y;
    sp18.z = temp_v0->unk18.z;

    temp_f0 = func_800F5A8C(temp_v0->endFrame, temp_v0->startFrame, globalCtx->csCtx.frames, globalCtx);
    arg0->x = ((sp18.x - sp24.x) * temp_f0) + sp24.x;
    arg0->y = ((sp18.y - sp24.y) * temp_f0) + sp24.y;
    arg0->z = ((sp18.z - sp24.z) * temp_f0) + sp24.z;
}
