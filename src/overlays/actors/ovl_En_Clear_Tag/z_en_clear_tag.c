#include "z_en_clear_tag.h"

#define FLAGS 0x00000035

#define THIS ((EnClearTag*)thisx)

void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809495F8(EnClearTag* this, GlobalContext* globalCtx);
void func_80949BD4(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Clear_Tag_InitVars = {
    ACTOR_EN_CLEAR_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnClearTag),
    (ActorFunc)EnClearTag_Init,
    (ActorFunc)EnClearTag_Destroy,
    (ActorFunc)EnClearTag_Update,
    (ActorFunc)EnClearTag_Draw,
};

extern Gfx D_04030100[];
extern Gfx D_040378F0[];
extern Gfx D_04037DF0[];
extern Gfx D_040382F0[];
extern Gfx D_040387F0[];
extern Gfx D_04038CF0[];
extern Gfx D_040391F0[];
extern Gfx D_040396F0[];
extern Gfx D_04039BF0[];
extern Gfx D_0403A0F0[];

static Vec3f sZeroVec = { 0.0f, 0.0f, 0.0f };

static Vec3f sEnvColor[] = {
    { 255.0f, 255.0f, 0.0f },
    { 255.0f, 100.0f, 100.0f },
    { 100.0f, 255.0f, 100.0f },
    { 100.0f, 100.0f, 255.0f },
};

static Vec3f sPrimColor[] = {
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
};

static f32 sScaleZ1[] = {
    6.0f,
    12.0f,
    9.0f,
};

static f32 sScale1[] = {
    3.0f,
    6.0f,
};

static f32 sScaleZ2[] = {
    15.0f,
    30.0f,
    20.0f,
};

static f32 sScale2[] = {
    0.03f,
    0.06f,
    0.04f,
};

static f32 sScale3[] = {
    1000.0f, 2000.0f, 1500.0f, 800.0f, 1300.0f,
};

// sScaleZ3_Target
static f32 sScaleZ3[] = {
    15.0f, 30.0f, 20.0f, 10.0f, 20.0f,
};

static f32 sScale4[] = {
    25.0f, 100.0f, 48.0f, 20.0f, 32.0f,
};

static Gfx* D_8094AE34[] = {
    D_040378F0, D_04037DF0, D_040382F0, D_040387F0, D_04038CF0, D_040391F0, D_040396F0, D_04039BF0, NULL, NULL, NULL,
};

#include "overlays/ovl_En_Clear_Tag/ovl_En_Clear_Tag.c"

void func_80947F60(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale, f32 rotZ) {
    f32 rotX;
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s16 i;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_00 = 1;
            unkEffect->pos = *pos;
            unkEffect->vel = *vel;
            unkEffect->accel = *accel;
            unkEffect->scale = scale;
            unkEffect->rotY = Rand_ZeroFloat(2 * M_PI);
            rotX = Rand_ZeroFloat(2 * M_PI);
            unkEffect->unk_48 = 0;
            unkEffect->rotX = rotX;
            unkEffect->unk_4A = unkEffect->unk_48;
            unkEffect->rotZ = rotZ;
            unkEffect->unk_01 = Rand_ZeroFloat(10.0f);
            break;
        }
    }
}

void func_809480C8(EnClearTag* this, Vec3f* pos, f32 scale) {
    s16 i;
    EnClearTagUnkEffect* unkEffect = this->unkEffect;

    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_01 = Rand_ZeroFloat(100.0f);
            unkEffect->unk_00 = 3;
            unkEffect->pos = *pos;
            unkEffect->vel = sZeroVec;
            unkEffect->accel = sZeroVec;
            unkEffect->scale = scale;
            unkEffect->scaleZ = 2.0f * scale;
            unkEffect->scaleX = 1.0f;
            unkEffect->scaleY = 1.0f;
            unkEffect->primColorAlpha = 255.0f;
            unkEffect->envColorR = 255.0f;
            unkEffect->envColorB = 255.0f;
            unkEffect->primColorR = 200.0f;
            unkEffect->primColorG = 20.0f;
            unkEffect->primColorB = 0.0f;
            unkEffect->envColorG = 215.0f;
            break;
        }
    }
}

void func_80948264(EnClearTag* this, Vec3f* pos, f32 scale) {
    s16 i;
    EnClearTagUnkEffect* unkEffect = this->unkEffect;

    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_01 = Rand_ZeroFloat(100.0f);
            unkEffect->unk_00 = 8;
            unkEffect->pos = *pos;
            unkEffect->vel = sZeroVec;
            unkEffect->accel = sZeroVec;
            unkEffect->scale = scale;
            unkEffect->scaleZ = 2.0f * scale;
            unkEffect->scaleX = 1.0f;
            unkEffect->scaleY = 1.0f;

            if (scale <= 1.1f) {
                unkEffect->scale = ((KREG(23) * 0.1f) + 1.0f) * scale;
                unkEffect->primColorAlpha = KREG(16) + 150.0f;
                unkEffect->primColorR = KREG(17);
                unkEffect->primColorG = KREG(18);
                unkEffect->primColorB = KREG(19);
                unkEffect->envColorR = KREG(20);
                unkEffect->envColorG = KREG(21);
                unkEffect->envColorB = KREG(22);
            } else {
                unkEffect->envColorB = 0.0f;
                unkEffect->envColorG = 0.0f;
                unkEffect->envColorR = 0.0f;
                unkEffect->primColorB = 0.0f;
                unkEffect->primColorG = 0.0f;
                unkEffect->primColorR = 0.0f;
                unkEffect->primColorAlpha = 255.0f;
            }
            break;
        }
    }
}

void func_809484EC(EnClearTag* this, Vec3f* pos, f32 scaleZ, f32 rotZ) {
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s16 i;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_00 = 4;
            unkEffect->pos = *pos;
            unkEffect->vel = sZeroVec;
            unkEffect->accel = sZeroVec;
            unkEffect->scale = 0.0f;
            unkEffect->scaleZ = scaleZ * 3.0f;
            unkEffect->rotZ = rotZ;
            unkEffect->primColorAlpha = 255.0f;
            break;
        }
    }
}

void func_809485A8(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale, f32 scaleZTarget, s16 arg6) {
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s16 i;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_00 = 5;
            unkEffect->pos = *pos;
            unkEffect->vel = *vel;
            unkEffect->accel = *accel;
            unkEffect->scale = scale / 1000.0f;
            unkEffect->scaleZ = 1.0f;
            unkEffect->scaleZTarget = scaleZTarget;
            unkEffect->unk_4C = Rand_ZeroFloat(100.0f) + 200.0f;
            unkEffect->unk_4E = arg6;
            unkEffect->unk_01 = Rand_ZeroFloat(10.0f);
            unkEffect->rotY = Math_Acot2F(unkEffect->vel.z, unkEffect->vel.x);
            unkEffect->rotX = -Math_Acot2F(sqrtf(SQXZ(unkEffect->vel)), unkEffect->vel.y);
            unkEffect->envColorR = 255.0f;
            unkEffect->envColorG = 255.0f;
            unkEffect->primColorR = 255.0f;
            unkEffect->primColorG = 255.0f;
            unkEffect->primColorB = 255.0f;
            unkEffect->envColorB = 0.0f;
            break;
        }
    dummy:;
    }
}

void func_80948788(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale, f32 scaleZTarget, s16 arg6, s16 arg7) {
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s16 i;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_00 = 5;
            unkEffect->pos = *pos;
            unkEffect->vel = *vel;
            unkEffect->accel = *accel;
            unkEffect->scale = scale / 1000.0f;
            unkEffect->scaleZ = 1.0f;
            unkEffect->scaleZTarget = scaleZTarget;
            unkEffect->unk_4C = Rand_ZeroFloat(100.0f) + 200.0f;
            unkEffect->unk_4E = arg7;
            unkEffect->unk_01 = Rand_ZeroFloat(10.0f);
            unkEffect->rotY = Math_Acot2F(unkEffect->vel.z, unkEffect->vel.x);
            unkEffect->rotX = -Math_Acot2F(sqrtf(SQXZ(unkEffect->vel)), unkEffect->vel.y);
            unkEffect->envColorR = sEnvColor[arg6].x;
            unkEffect->envColorG = sEnvColor[arg6].y;
            unkEffect->envColorB = sEnvColor[arg6].z;
            unkEffect->primColorR = sPrimColor[arg6].x;
            unkEffect->primColorG = sPrimColor[arg6].y;
            unkEffect->primColorB = sPrimColor[arg6].z;
            break;
        }
    }
}

void func_8094899C(EnClearTag* this, Vec3f* pos, f32 scaleZ, s16 arg3) {
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s16 i;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            unkEffect->unk_00 = 6;
            unkEffect->pos = *pos;
            unkEffect->vel = sZeroVec;
            unkEffect->accel = sZeroVec;
            unkEffect->scaleZ = scaleZ;
            unkEffect->unk_01 = arg3;
            unkEffect->scale = 0.0f;
            unkEffect->primColorAlpha = 200.0f;
            break;
        }
    }
}

void func_80948A54(EnClearTag* this, Vec3f* pos, s16 arg2) {
    s16 i;
    EnClearTagUnkEffect* unkEffect = this->unkEffect;

    for (i = 0; i < 102; i++, unkEffect++) {
        if (unkEffect->unk_00 == 0) {
            // Immediately overwritten and generates a lot of wasted asm (f32 to u8)
            unkEffect->unk_01 = Rand_ZeroFloat(100.0f);
            unkEffect->unk_00 = 7;
            unkEffect->pos = *pos;
            unkEffect->vel = sZeroVec;
            unkEffect->accel = sZeroVec;
            unkEffect->scale = 0.0f;
            unkEffect->scaleZ = 0.0f;
            unkEffect->unk_01 = 0;
            unkEffect->unk_4A = arg2;
            unkEffect->rotX = 0.78f;
            break;
        }
    }
}

void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnClearTag* this = THIS;
    f32 temp_f20_2;
    f32 temp_f20_4;
    u8 i;
    Vec3f spA4;
    Vec3f sp98;
    Vec3f sp8C;

    this->actor.flags &= -2;
    if (thisx->params >= 0) {
        this->activeTimer = 70;
        Math_Vec3f_Copy(&spA4, &this->actor.world.pos);
        if (thisx->params == 200) {
            func_80948264(this, &spA4, this->actor.world.rot.z);
            return;
        }
            
        if (thisx->params != 35) {
            if (thisx->params == 3 || thisx->params == 4) { 
                for (i = 0; i < 54; i++) {
                    temp_f20_4 = sScale4[thisx->params] + Rand_ZeroFloat(sScale4[thisx->params]);
                    SysMatrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), 0);
                    SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    SysMatrix_GetStateTranslationAndScaledZ(temp_f20_4, &sp98);
                    sp8C.x = sp98.x * -0.03f;
                    sp8C.y = sp98.y * -0.03f;
                    sp8C.z = sp98.z * -0.03f;
                    func_80948788(
                        this, &spA4, &sp98, &sp8C,
                        sScale3[thisx->params] + Rand_ZeroFloat(sScale3[thisx->params] * 0.5f),
                        sScaleZ3[thisx->params], this->actor.world.rot.z, Rand_ZeroFloat(10.0f) + 20.0f);
                }
                return;
            } else {
                if (!((this->actor.world.rot.x == 0) && (this->actor.world.rot.y == 0) &&
                    (this->actor.world.rot.z == 0))) {
                    this->envColor.r = this->actor.world.rot.x;
                    this->envColor.g = this->actor.world.rot.y;
                    this->envColor.b = this->actor.world.rot.z;
                } else {
                    this->envColor.r = 0xFF;
                    this->envColor.g = 0;
                }

                Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 30.0f, 100.0f, 4);
                spA4 = this->actor.world.pos;
                func_809484EC(this, &spA4, sScaleZ1[thisx->params], this->actor.floorHeight);
                if ((this->actor.bgCheckFlags & 0x20) == 0) {
                    if (thisx->params < 0xA) {
                        spA4.y = this->actor.world.pos.y - 40.0f;
                        if (thisx->params != 2) {
                            func_809480C8(this, &spA4, sScale1[thisx->params]);
                        }
                        spA4.y = this->actor.floorHeight + 3.0f;
                        func_8094899C(this, &spA4, sScaleZ2[thisx->params], 0);
                        func_8094899C(this, &spA4, sScaleZ2[thisx->params], 3);
                        if (thisx->params == 1) {
                            func_8094899C(this, &spA4, sScaleZ2[thisx->params], 6);
                        }
                    }

                    if (thisx->params != 2) {
                        spA4.y = this->actor.world.pos.y;
                        for (i = 0; i < 18; i++) {
                            sp98.x = __sinf(i * 0.825f) * i * .5f;
                            sp98.z = __cosf(i * 0.825f) * i * .5f;
                            sp98.y = Rand_ZeroFloat(8.0f) + 7.0f;
                            sp98.x += randPlusMinusPoint5Scaled(0.5f);
                            sp98.z += randPlusMinusPoint5Scaled(0.5f);
                            sp8C.x = 0.0f;
                            sp8C.y = -1.0f;
                            sp8C.z = 0.0f;
                            func_80947F60(this, &spA4, &sp98, &sp8C,
                                        sScale2[thisx->params] + Rand_ZeroFloat(sScale2[thisx->params]),
                                        this->actor.floorHeight);
                        }
                    }
                }
                spA4 = this->actor.world.pos;

                for (i = 0; i < 44; i++) {
                    temp_f20_2 = sScale4[thisx->params] + Rand_ZeroFloat(sScale4[thisx->params]);
                    SysMatrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), 0);
                    SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    SysMatrix_GetStateTranslationAndScaledZ(temp_f20_2, &sp98);
                    sp8C.x = sp98.x * -0.03f;
                    sp8C.y = sp98.y * -0.03f;
                    sp8C.z = sp98.z * -0.03f;
                    func_809485A8(this, &spA4, &sp98, &sp8C,
                                sScale3[thisx->params] + Rand_ZeroFloat(sScale3[thisx->params] * 0.5f),
                                sScaleZ3[thisx->params], Rand_ZeroFloat(10.0f) + 20.0f);
                }

            }
        }

        func_80948A54(this, &spA4, 0);
        func_80948A54(this, &spA4, 2);
    }
}

void func_80949288(EnClearTag* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Camera* camera;
    s32 pad;

    switch(this->unk_2E54) {
        case 0:
            if(((player->actor.world.pos.z > 0.0f) &&
                (player->actor.world.pos.z > 290.0f) &&
                (fabsf(player->actor.world.pos.x) < 60.0f)) ||
                ((player->actor.world.pos.z < 0.0f) &&
                (player->actor.world.pos.z < -950.0f) &&
                (fabsf(player->actor.world.pos.x) < 103.0f))) {

                if (player->actor.world.pos.z > 0.0f) {
                    player->actor.world.pos.z = 290.0f;
                } else {
                    player->actor.world.pos.z = -950.0f;
                }
                player->actor.speedXZ = 0.0f;
                if (this->activeTimer == 0) {
                    this->unk_2E54 = 1;
                }
            }

            
            break;
        case 1:
            func_800EA0D4(globalCtx, &globalCtx->csCtx);
            this->camID = func_801694DC(globalCtx);
            func_80169590(globalCtx, 0, 1);
            func_80169590(globalCtx, this->camID, 7);
            func_800B7298(globalCtx, this, 4);
            camera = Play_GetCamera(globalCtx, 0);
            this->eye.x = camera->eye.x;
            this->eye.y = camera->eye.y;
            this->eye.z = camera->eye.z;
            this->at.x = camera->focalPoint.x;
            this->at.y = camera->focalPoint.y;
            this->at.z = camera->focalPoint.z;
            func_801518B0(globalCtx, 0xF, NULL);
            this->unk_2E54 = 2;
            func_8019FDC8(&D_801DB4A4, NA_SE_VO_NA_LISTEN, 0x20);
        case 2:
            if (player->actor.world.pos.z > 0.0f) {
                player->actor.world.pos.z = 290.0f;
            } else {
                player->actor.world.pos.z = -950.0f;
            }

            player->actor.speedXZ = 0.0f;
            if (func_80152498(&globalCtx->msgCtx) == 0) {
                camera = Play_GetCamera(globalCtx, 0);
                camera->eye = this->eye;
                camera->unk74 = this->eye;
                camera->focalPoint = this->at;
                func_80169AFC(globalCtx, this->camID, 0);
                func_800EA0EC(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, this, 6);
                this->unk_2E54 = 0;
                this->camID = 0;
                this->activeTimer = 20;
            }
            break;
    }

    if (this->camID != 0) {
        func_8016970C(globalCtx, this->camID, &this->at, &this->eye);
    }
}

void EnClearTag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnClearTag* this = THIS;

    if (this->activeTimer != 0) {
        this->activeTimer--;
    }
    if (this->actor.params < 0) {
        func_80949288(this, globalCtx);
        return;
    }
    if (this->activeTimer != 0) {
        func_809495F8(this, globalCtx);
        return;
    }

    Actor_MarkForDeath(&this->actor);
}

void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_80949BD4(thisx, globalCtx);
}

void func_809495F8(EnClearTag* this, GlobalContext* globalCtx) {
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    s32 pad;
    f32 sp6C;
    Vec3f sp60;
    s16 i;

    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 != 0) {
            unkEffect->unk_01++;
            unkEffect->pos.x += unkEffect->vel.x;
            sp6C = unkEffect->pos.y;
            unkEffect->pos.y += unkEffect->vel.y;
            unkEffect->pos.z += unkEffect->vel.z;

            unkEffect->vel.x += unkEffect->accel.x;
            unkEffect->vel.y += unkEffect->accel.y;
            unkEffect->vel.z += unkEffect->accel.z;
            if (unkEffect->unk_00 == 1) {
                if (unkEffect->vel.y < -5.0f) {
                    unkEffect->vel.y = -5.0f;
                }

                if (unkEffect->vel.y < 0.0f) {
                    sp60 = unkEffect->pos;
                    sp60.y += 5.0f;
                    if (func_800C5A20(&globalCtx->colCtx, &sp60, 11.0f) != 0) {
                        unkEffect->pos.y = sp6C;
                        if (unkEffect->unk_48 <= 0) {
                            unkEffect->unk_48++;
                            unkEffect->vel.y *= -0.5f;
                            unkEffect->unk_4A = Rand_ZeroFloat(20.0f) + 25.0f;
                        } else {
                            unkEffect->vel.y = 0.0f;
                            unkEffect->accel.y = 0.0f;
                            unkEffect->vel.z = 0.0f;
                            unkEffect->vel.x = 0.0f;
                        }
                    }
                }

                if (unkEffect->accel.y != 0.0f) {
                    unkEffect->rotY += 0.5f;
                    unkEffect->rotX += 0.35f;
                }

                if (unkEffect->unk_4A == 1) {
                    unkEffect->unk_00 = 0;
                }
            } else if (unkEffect->unk_00 == 2) {
                Math_ApproachZeroF(&unkEffect->primColorAlpha, 1.0f, 15.0f);
                if (unkEffect->primColorAlpha <= 0.0f) {
                    unkEffect->unk_00 = 0;
                }
            } else if (unkEffect->unk_00 == 6) {
                if (unkEffect->unk_01 >= 4) {
                    Math_ApproachF(&unkEffect->scale, unkEffect->scaleZ, 0.2f, unkEffect->scaleZ * 0.6666666f);
                    Math_ApproachZeroF(&unkEffect->primColorAlpha, 1.0f, 15.0f);
                    if (unkEffect->primColorAlpha <= 0.0f) {
                        unkEffect->unk_00 = 0;
                    }
                }
            } else if (unkEffect->unk_00 == 3) {
                Math_ApproachZeroF(&unkEffect->primColorR, 1.0f, 20.0f);
                Math_ApproachZeroF(&unkEffect->primColorG, 1.0f, 2.0f);
                Math_ApproachZeroF(&unkEffect->envColorR, 1.0f, 25.5f);
                Math_ApproachZeroF(&unkEffect->envColorG, 1.0f, 21.5f);
                Math_ApproachZeroF(&unkEffect->envColorB, 1.0f, 25.5f);
                Math_ApproachF(&unkEffect->scale, unkEffect->scaleZ, 0.05f, 0.1f);
                if (unkEffect->primColorR == 0.0f) {
                    Math_ApproachF(&unkEffect->scaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&unkEffect->scaleY, 3.0f, 0.1f, 0.02f);
                    Math_ApproachZeroF(&unkEffect->primColorAlpha, 1.0f, 5.f);
                    if (unkEffect->primColorAlpha <= 0.0f) {
                        unkEffect->unk_00 = 0;
                    }
                }
            } else if (unkEffect->unk_00 == 8) {
                Math_ApproachF(&unkEffect->scale, unkEffect->scaleZ, 0.05f, 0.1f);
                if (unkEffect->unk_01 >= 0xB) {
                    Math_ApproachF(&unkEffect->scaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&unkEffect->scaleY, 3.0f, 0.1f, 0.02f);
                    Math_ApproachZeroF(&unkEffect->primColorAlpha, 1.0f, 5.f);
                    if (unkEffect->primColorAlpha <= 0.0f) {
                        unkEffect->unk_00 = 0;
                    }
                }
            } else if (unkEffect->unk_00 == 4) {
                Math_ApproachF(&unkEffect->scale, unkEffect->scaleZ, 0.5f, 6.0f);
                Math_ApproachZeroF(&unkEffect->primColorAlpha, 1.0f, 15.0f);
                if (unkEffect->primColorAlpha <= 0.0f) {
                    unkEffect->unk_00 = 0;
                }
            } else if (unkEffect->unk_00 == 5) {
                unkEffect->rotZ += Rand_ZeroFloat(M_PI / 2) + (M_PI / 2);
                unkEffect->unk_4C -= unkEffect->unk_4E;
                if (unkEffect->unk_4C <= 0) {
                    unkEffect->unk_4C = 0;
                    unkEffect->unk_00 = 0;
                }
                unkEffect->primColorAlpha = unkEffect->unk_4C;
                if (unkEffect->primColorAlpha > 255.0f) {
                    unkEffect->primColorAlpha = 255.0f;
                }
                Math_ApproachF(&unkEffect->scaleZ, unkEffect->scaleZTarget, 1.0f, (unkEffect->scaleZTarget / 15.0f) * 4.0f);
            } else if (unkEffect->unk_00 == 7) {
                if (unkEffect->unk_4A == 0) {
                    unkEffect->scale = 7.0f;
                    Math_ApproachF(&unkEffect->scaleZ, 500.0f, 1.0f, 50.0f);
                    Math_ApproachF(&unkEffect->rotX, 1.5f, 1.0f, 0.12f);
                    if (unkEffect->unk_01 >= 8) {
                        unkEffect->unk_00 = 0;
                    }
                } else {
                    unkEffect->unk_01 = 0;
                }
            }
            if (unkEffect->unk_4A != 0) {
                unkEffect->unk_4A--;
            }
        }
    }
}

void func_80949BD4(Actor* thisx, GlobalContext* globalCtx) {
    u8 sp1B7 = 0;
    s16 i;
    s16 j;
    Vec3f sp1A4;
    UNK_PTR sp1A0;
    f32 posY;
    MtxF mtxF;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    EnClearTag* this = THIS;
    EnClearTagUnkEffect* unkEffect = this->unkEffect;
    EnClearTagUnkEffect* unkEffectRef = this->unkEffect;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 1) {
            if (sp1B7 == 0) {
                sp1B7++;
                gSPDisplayList(POLY_OPA_DISP++, D_8094B090);
            }
            SysMatrix_InsertTranslation(unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, MTXMODE_NEW);
            Matrix_Scale(unkEffect->scale, unkEffect->scale, unkEffect->scale, MTXMODE_APPLY);
            SysMatrix_InsertYRotation_f(unkEffect->rotY, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(unkEffect->rotX);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_8094B110);
        }
    }

    unkEffect = unkEffectRef;
    if (this->actor.floorPoly != 0) {
        for (i = 0; i < 103; i++, unkEffect++) {
            if (unkEffect->unk_00 == 6) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (s8)unkEffect->primColorAlpha);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s8)unkEffect->primColorAlpha);
                func_800C0094(this->actor.floorPoly, unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, &mtxF);
                SysMatrix_SetCurrentState(&mtxF);
                Matrix_Scale(unkEffect->scale, 1.0f, unkEffect->scale, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_04030100);
            }
        }
    }

    sp1B7 = 0;
    unkEffect = unkEffectRef;
    if (this->actor.floorPoly != 0) {
        for (i = 0; i < 103; i++, unkEffect++) {
            if (unkEffect->unk_00 == 4) {
                if (sp1B7 == 0) {
                    gDPPipeSync(POLY_XLU_DISP++);
                    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 200, 0);
                    sp1B7++;
                }
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)(unkEffect->primColorAlpha * 0.7f));
                func_800C0094(this->actor.floorPoly, unkEffect->pos.x, this->actor.floorHeight, unkEffect->pos.z, &mtxF);
                SysMatrix_SetCurrentState(&mtxF);
                Matrix_Scale(unkEffect->scale * 3.0f, 1.0f, unkEffect->scale * 3.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_8094CB10);
            }
        }
    }

    sp1B7 = 0;
    unkEffect = unkEffectRef;
    for (i = 0; i < 103; i++, unkEffect++) {
        if ((unkEffect->unk_00 == 3) || (unkEffect->unk_00 == 8)) {
            if (sp1B7 == 0) {
                gSPDisplayList(POLY_XLU_DISP++, D_8094B758);
                sp1B7++;
            }
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, (s8)unkEffect->envColorR, (s8)unkEffect->envColorG, (s8)unkEffect->envColorB, 128);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (s8)unkEffect->primColorR, (s8)unkEffect->primColorG, (s8)unkEffect->primColorB,
                            (s8)unkEffect->primColorAlpha);
            gSPSegment(
                POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 5 * -unkEffect->unk_01, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));
            SysMatrix_InsertTranslation(unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(unkEffect->scaleX * unkEffect->scale, unkEffect->scaleY * unkEffect->scale, 1.0f, MTXMODE_APPLY);
            SysMatrix_InsertTranslation(0.0f, 20.0f, 0.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_8094B800);
        }
    }

    sp1B7 = 0;
    unkEffect = unkEffectRef;
    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 2) {
            if (sp1B7 == 0) {
                gSPDisplayList(POLY_XLU_DISP++, D_8094B758);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 215, 255, 128);
                sp1B7++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 20, 0, (s8)unkEffect->primColorAlpha);
            gSPSegment(
                POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 15 * -unkEffect->unk_01, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));
            SysMatrix_InsertTranslation(unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(unkEffect->scale, unkEffect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_8094B800);
        }
    }

    sp1B7 = 0;
    unkEffect = unkEffectRef;
    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 4) {
            if (sp1B7 == 0) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 0);
                sp1B7++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)unkEffect->primColorAlpha);
            SysMatrix_InsertTranslation(unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(2.0f * unkEffect->scale, 2.0f * unkEffect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_8094C860);
        }
    }

    sp1B7 = 0;
    unkEffect = unkEffectRef;
    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 5) {
            if (sp1B7 == 0) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, (u8)unkEffect->envColorR, (u8)unkEffect->envColorG, (u8)unkEffect->envColorB, 0);
                gSPDisplayList(POLY_XLU_DISP++, D_8094DBD8);
                sp1B7++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)unkEffect->primColorR, (u8)unkEffect->primColorG, (u8)unkEffect->primColorB,
                            (u8)unkEffect->primColorAlpha);
            SysMatrix_InsertTranslation(unkEffect->pos.x, unkEffect->pos.y, unkEffect->pos.z, MTXMODE_NEW);
            SysMatrix_InsertYRotation_f(unkEffect->rotY, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(unkEffect->rotX);
            SysMatrix_InsertZRotation_f(unkEffect->rotZ, MTXMODE_APPLY);
            Matrix_Scale(unkEffect->scale * 0.5f, unkEffect->scale * 0.5f, unkEffect->scaleZ * unkEffect->scale, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(M_PI / 2);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_8094DC48);
        }
    }

    unkEffect = unkEffectRef;
    for (i = 0; i < 103; i++, unkEffect++) {
        if (unkEffect->unk_00 == 7) {
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 200);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 200);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_8094AE34[unkEffect->unk_01]));
            func_8012C9BC(gfxCtx);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BACK);
            sp1B7++;
            for (j = 0; j < 16; j++) {
                SysMatrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_NEW);
                SysMatrix_GetStateTranslationAndScaledZ(unkEffect->scaleZ, &sp1A4);
                posY = unkEffect->pos.y;
                if (func_800CA1AC(globalCtx, &globalCtx->colCtx, unkEffect->pos.x + sp1A4.x, unkEffect->pos.z + sp1A4.z, &posY,
                                  &sp1A0) != 0) {
                    if ((unkEffect->pos.y - posY) < 200.0f) {
                        SysMatrix_InsertTranslation(unkEffect->pos.x + sp1A4.x, posY, unkEffect->pos.z + sp1A4.z, MTXMODE_NEW);
                        SysMatrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_APPLY);
                        SysMatrix_RotateStateAroundXAxis(unkEffect->rotX);
                        Matrix_Scale(unkEffect->scale, unkEffect->scale, unkEffect->scale, MTXMODE_APPLY);
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_XLU_DISP++, D_0403A0F0);
                    }
                }
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
