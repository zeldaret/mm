/*
 * File: z_en_water_effect.c
 * Overlay: ovl_En_Water_Effect
 * Description: Water splashing effect (used for Gyorg)
 */

#include "z_en_water_effect.h"
#include "objects/object_water_effect/object_water_effect.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnWaterEffect*)thisx)

void EnWaterEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A59C04(Actor* thisx, GlobalContext* globalCtx2);
void func_80A5A184(Actor* thisx, GlobalContext* globalCtx2);
void func_80A5A534(Actor* thisx, GlobalContext* globalCtx);
void func_80A5A6B8(Actor* thisx, GlobalContext* globalCtx2);

const ActorInit En_Water_Effect_InitVars = {
    ACTOR_EN_WATER_EFFECT,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_WATER_EFFECT,
    sizeof(EnWaterEffect),
    (ActorFunc)EnWaterEffect_Init,
    (ActorFunc)EnWaterEffect_Destroy,
    (ActorFunc)EnWaterEffect_Update,
    (ActorFunc)EnWaterEffect_Draw,
};

static Vec3f D_80A5AFB0 = { 0.0f, 0.0f, 0.0f };
static Vec3f D_80A5AFBC = { 0.0f, -1.0f, 0.0f };

void func_80A587A0(EnWaterEffect* this, Vec3f* arg1, u8 arg2) {
    s16 i;
    EnWaterEffectStruct* ptr = &this->unk_144[0];

    for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
        if (!ptr->unk_00) {
            ptr->unk_00 = true;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = D_80A5AFB0;
            ptr->unk_1C = D_80A5AFB0;
            ptr->unk_2C.x = 0.1f;
            ptr->unk_2C.y = 0.0f;
            ptr->unk_2C.z = Rand_ZeroFloat(M_PI * 2);
            ptr->unk_01 = Rand_ZeroFloat(100.0f);
            ptr->unk_2A = arg2;
            break;
        }
    }
}

void func_80A58908(EnWaterEffect* this, Vec3f* arg1, Vec3f* arg2, u8 arg3) {
    Vec3f sp2C = D_80A5AFBC;
    EnWaterEffectStruct* ptr = &this->unk_144[0];
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 2;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = sp2C;
            ptr->unk_2C.y = Rand_ZeroFloat(0.02f) + 0.02f;
            ptr->unk_2C.x = ptr->unk_2C.y;
            ptr->unk_2C.z = Rand_ZeroFloat(M_PI * 2);
            ptr->unk_01 = Rand_ZeroFloat(100.0f);
            ptr->unk_2A = arg3;
            break;
        }
    }
}

void EnWaterEffect_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWaterEffect* this = THIS;

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_DC4 = Rand_ZeroFloat(100.0f);

    if (this->actor.params == ENWATEREFFECT_1) {
        this->actor.update = func_80A59C04;
        this->actor.draw = func_80A5A184;
        this->unk_DC6 = Rand_ZeroFloat(100.0f) + 60.0f;
    } else if ((this->actor.params == ENWATEREFFECT_777) || (this->actor.params == ENWATEREFFECT_778) ||
               (this->actor.params == ENWATEREFFECT_779) || (this->actor.params == ENWATEREFFECT_780)) {
        this->actor.update = func_80A5A534;
        this->actor.draw = func_80A5A6B8;
        this->actor.shape.rot.y = Rand_ZeroFloat(0x10000);
        Actor_SetScale(&this->actor, this->actor.shape.rot.z * 0.0002f);

        if (this->actor.params == ENWATEREFFECT_777) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WATER_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, this->actor.shape.rot.z, 0x30A);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WATER_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, this->actor.shape.rot.z, 0x30B);
        } else if (this->actor.params == ENWATEREFFECT_778) {
            this->unk_DC4 = -3;
        } else if (this->actor.params == ENWATEREFFECT_779) {
            this->unk_DC4 = -6;
        } else if (this->actor.params == ENWATEREFFECT_780) {
            this->unk_DC4 = 23;
        }

        this->unk_E08[1] = 0.2f;
        this->unk_E18[1] = -0.017f;
        this->unk_E08[2] = 0.2f;
        this->unk_E18[2] = -0.018f;
        this->unk_E08[3] = 0.2f;
        this->unk_E18[3] = -0.019f;

        this->unk_DC8[1].y = 1.0f;
        this->unk_DC8[2].y = 1.0f;
        this->unk_DC8[3].y = 1.0f;

        this->unk_E2C = 255.0f;
        this->unk_E34 = 255.0f;
        this->unk_E30 = 200.0f;
        this->unk_E38 = 191.25f;
    }
}

void EnWaterEffect_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnWaterEffect_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnWaterEffect* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    EnWaterEffectStruct* ptr = &this->unk_144[0];
    s16 i;
    s16 j;
    s32 phi_v0;
    Vec3f spA4;
    Vec3f sp98;
    u8 phi_v1;
    Vec3f sp88;

    if (!Flags_GetSwitch(globalCtx, this->actor.params)) {
        this->unk_DC4++;
        if ((this->unk_DC4 % 32) == 0) {
            if (Rand_ZeroOne() < 0.5f) {
                Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 10.0f, 40.0f, 4);
                sp88.x = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.x;
                sp88.y = this->actor.world.pos.y;
                sp88.z = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.z;
                if ((this->actor.world.pos.y + this->actor.depthInWater) <= this->actor.floorHeight) {
                    phi_v1 = 0;
                } else {
                    phi_v1 = 1;
                    this->actor.floorHeight = this->actor.world.pos.y + this->actor.depthInWater;
                }
                func_80A587A0(this, &sp88, phi_v1);
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_01++;

            ptr->unk_04.x += ptr->unk_10.x;
            ptr->unk_04.y += ptr->unk_10.y;
            ptr->unk_04.z += ptr->unk_10.z;
            ptr->unk_10.y += ptr->unk_1C.y;

            Math_ApproachF(&ptr->unk_38, (ptr->unk_01 & 6) ? 80.0f : 200.0f, 1.0f, 80);

            if (ptr->unk_00 == 1) {
                ptr->unk_2C.z += 0.15f;
                Math_ApproachF(&ptr->unk_2C.x, 0.03f, 0.5f, 0.005f);
                Math_ApproachF(&ptr->unk_2C.y, 0.5f, 0.5f, 0.02f);

                if (ptr->unk_2C.y > 0.15f) {
                    ptr->unk_1C.y = -1.0f;
                    if (ptr->unk_10.y < -20.0f) {
                        ptr->unk_10.y = -20.0f;
                    }
                }

                if ((fabsf(ptr->unk_04.x - player->actor.world.pos.x) < 15.0f) &&
                    (fabsf(ptr->unk_04.z - player->actor.world.pos.z) < 15.0f) &&
                    (player->actor.world.pos.y < ptr->unk_04.y) &&
                    ((ptr->unk_04.y - player->actor.world.pos.y) < 40.0f)) {
                    phi_v0 = true;
                } else {
                    phi_v0 = false;
                }

                if ((ptr->unk_04.y <= this->actor.floorHeight) || phi_v0) {

                    if (phi_v0) {
                        ptr->unk_00 = 0;
                        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_04, 30, NA_SE_EV_BOMB_DROP_WATER);
                    } else {
                        ptr->unk_04.y = this->actor.floorHeight;
                        if (ptr->unk_2A == 0) {
                            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_04, 30, NA_SE_EV_WATERDROP_GRD);
                            ptr->unk_00 = 3;
                            ptr->unk_2C.x = 0.1f;
                            ptr->unk_2C.y = 0.6f;
                            ptr->unk_10 = D_80A5AFB0;
                            ptr->unk_1C = D_80A5AFB0;
                            ptr->unk_3C = 200;
                            ptr->unk_28 = 9;
                            Math_Vec3f_Copy(&sp98, &ptr->unk_04);
                            sp98.y += 3.0f;
                            EffectSsGSplash_Spawn(globalCtx, &sp98, NULL, NULL, 1, 100);
                        } else {
                            ptr->unk_00 = 0;
                            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_04, 30, NA_SE_EV_WATERDROP);
                            EffectSsGRipple_Spawn(globalCtx, &ptr->unk_04, 70, 500, 0);
                            EffectSsGRipple_Spawn(globalCtx, &ptr->unk_04, 70, 500, 10);
                            Math_Vec3f_Copy(&sp98, &ptr->unk_04);
                            sp98.y += 10.0f;
                            EffectSsGSplash_Spawn(globalCtx, &sp98, NULL, NULL, 1, 300);
                        }
                    }

                    for (j = 0; j < 12; j++) {
                        Matrix_InsertYRotation_f((2.0f * (j * M_PI)) / 5.5f, MTXMODE_NEW);
                        Matrix_GetStateTranslationAndScaledZ(Rand_ZeroFloat(1.5f) + 1.5f, &spA4);
                        spA4.y = Rand_ZeroFloat(4.0f) + 2.0f;
                        func_80A58908(this, &ptr->unk_04, &spA4, ptr->unk_2A);
                    }
                }
            } else if (ptr->unk_00 == 2) {
                ptr->unk_2C.z += 0.15f;
                if (ptr->unk_10.y < -8.0f) {
                    ptr->unk_10.y = -8.0f;
                }

                if (ptr->unk_10.y < 0.0f) {
                    if (ptr->unk_04.y <= this->actor.floorHeight) {
                        ptr->unk_04.y = this->actor.floorHeight;
                        if (ptr->unk_2A == 0) {
                            ptr->unk_00 = 3;
                            ptr->unk_2C.x = 0.05f;
                            ptr->unk_2C.y = 0.2f;
                            ptr->unk_10 = D_80A5AFB0;
                            ptr->unk_1C = D_80A5AFB0;
                            ptr->unk_3C = 150;
                            ptr->unk_28 = Rand_ZeroFloat(5.0f) + 7.0f;
                        } else {
                            EffectSsGRipple_Spawn(globalCtx, &ptr->unk_04, 0, 200, 0);
                            ptr->unk_00 = 0;
                        }
                    }
                }
            } else if (ptr->unk_00 == 3) {
                Math_ApproachF(&ptr->unk_2C.x, ptr->unk_2C.y, 0.1f, 0.6f);
                ptr->unk_3C -= ptr->unk_28;
                if (ptr->unk_3C <= 0) {
                    ptr->unk_3C = 0;
                    ptr->unk_00 = 0;
                }
            }
        }
    }
}

void EnWaterEffect_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    EnWaterEffect* this = THIS;
    s32 pad;
    EnWaterEffectStruct* backupPtr = &this->unk_144[0];
    EnWaterEffectStruct* ptr = backupPtr;
    u8 phi_s4 = false;
    s16 i;

    OPEN_DISPS(gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
        if ((ptr->unk_00 == 1) || (ptr->unk_00 == 2)) {
            if (!phi_s4) {
                POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);

                gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gDust1Tex));
                gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_004260);
                gDPSetEnvColor(POLY_XLU_DISP++, 250, 250, 255, 0);
                phi_s4++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)ptr->unk_38, (u8)(((void)0, ptr->unk_38) + 55.0f), 225, 150);

            Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);

            if (ptr->unk_00 == 1) {
                Matrix_RotateY(Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx)), MTXMODE_APPLY);
            } else {
                Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            }

            Matrix_Scale(ptr->unk_2C.x, ptr->unk_2C.y, 1.0f, MTXMODE_APPLY);
            Matrix_InsertZRotation_f(ptr->unk_2C.z, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_0042B0);
        }
    }

    phi_s4 = false;
    ptr = backupPtr;

    for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
        if (ptr->unk_00 == 3) {
            if (!phi_s4) {
                func_8012C448(gfxCtx);

                gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gDust1Tex));
                gDPSetEnvColor(POLY_XLU_DISP++, 250, 250, 255, 0);
                gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_004260);
                phi_s4++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)ptr->unk_38, (u8)(((void)0, ptr->unk_38) + 55.0f), 225,
                            ptr->unk_3C);

            Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);
            Matrix_Scale(ptr->unk_2C.x, 1.0f, ptr->unk_2C.x, MTXMODE_APPLY);
            Matrix_InsertYRotation_f(ptr->unk_2C.z, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_0042F8);
        }
    }

    CLOSE_DISPS(gfxCtx);
}

void func_80A599E8(EnWaterEffect* this, Vec3f* arg1, u8 arg2) {
    s16 i;
    EnWaterEffectStruct* ptr = &this->unk_144[0];

    for (i = 0; i < ARRAY_COUNT(this->unk_144); i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 4;
            ptr->unk_04 = *arg1;

            ptr->unk_1C = D_80A5AFB0;
            ptr->unk_10 = D_80A5AFB0;

            if ((arg2 == 0) || (arg2 == 2)) {
                ptr->unk_1C.y = -1.0f;
            }

            if (arg2 >= 2) {
                if (arg2 == 2) {
                    ptr->unk_10.x = randPlusMinusPoint5Scaled(10.0f);
                    ptr->unk_10.y = Rand_ZeroFloat(3.0f) + 5.0f;
                    ptr->unk_10.z = randPlusMinusPoint5Scaled(10.0f);
                }
                ptr->unk_2C.z = 0.0017f;
                ptr->unk_2C.x = 0.003f;
                ptr->unk_2C.y = 0.0018f;
            } else {
                ptr->unk_2C.z = 0.003f;
                ptr->unk_2C.x = 0.003f;
                ptr->unk_2C.y = 0.003f;
            }
            ptr->unk_38 = 255.0f;
            ptr->unk_28 = Rand_ZeroFloat(0x10000);
            ptr->unk_3C = 255;
            ptr->unk_01 = Rand_ZeroFloat(200.0f);
            ptr->unk_2A = arg2;
            break;
        }
    }
}

void func_80A59C04(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnWaterEffect* this = THIS;
    s16 i;
    s16 j;
    f32 temp_f0_2;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp90;
    Actor* rotaryRoom = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;
    CollisionPoly* sp88;
    EnWaterEffectStruct* ptr = &this->unk_144[0];
    u8 phi_s5;
    Vec3f sp74;

    while (rotaryRoom != NULL) {
        if (rotaryRoom->id == ACTOR_BG_IKANA_ROTARYROOM) {
            break;
        }
        rotaryRoom = rotaryRoom->next;
    }

    if (this->unk_DC6 != 0) {
        this->unk_DC6--;
    }

    if ((rotaryRoom != NULL) && Flags_GetSwitch(globalCtx, (rotaryRoom->params >> 1) & 0x7F)) {
        this->unk_DC6 = Rand_ZeroFloat(150.0f) + 100.0f;
    } else if (!Play_InCsMode(globalCtx)) {
        this->unk_DC4++;
        if (this->unk_DC6 == 0) {
            this->unk_DC6 = Rand_ZeroFloat(150.0f) + 100.0f;
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 10.0f, 40.0f, 4);
            sp74.x = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.x;
            sp74.y = this->actor.world.pos.y;
            sp74.z = randPlusMinusPoint5Scaled(50.0f) + this->actor.world.pos.z;
            func_80A599E8(this, &sp74, 0);
        }
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_144); i++, ptr++) {
        phi_s5 = false;

        if (ptr->unk_00 != 0) {
            ptr->unk_01++;

            ptr->unk_04.x += ptr->unk_10.x;
            ptr->unk_04.y += ptr->unk_10.y;
            ptr->unk_04.z += ptr->unk_10.z;
            ptr->unk_10.y = ptr->unk_10.y + ptr->unk_1C.y;

            if (ptr->unk_00 == 4) {
                if (ptr->unk_2A > 0) {
                    if (ptr->unk_2A == 1) {
                        Math_ApproachF(&ptr->unk_2C.x, 0.001f, 0.5f, 0.0002f);
                    }

                    if (ptr->unk_2A & 1) {
                        Math_ApproachZeroF(&ptr->unk_38, 1.0f, 30.0f);
                        if (ptr->unk_2A == 1) {
                            ptr->unk_3C -= 20;
                        } else {
                            ptr->unk_3C -= 10;
                        }
                        if (ptr->unk_3C <= 0) {
                            ptr->unk_00 = 0;
                        }
                        Math_ApproachZeroF(&ptr->unk_10.x, 1.0f, 1.0f);
                        Math_ApproachZeroF(&ptr->unk_10.z, 1.0f, 1.0f);
                    }
                }

                if ((ptr->unk_2A % 2) == 0) {
                    if (ptr->unk_2A == 0) {
                        func_80A599E8(this, &ptr->unk_04, 1);
                    } else if ((ptr->unk_01 & 1) == 0) {
                        func_80A599E8(this, &ptr->unk_04, 3);
                    }

                    if (ptr->unk_10.y < -20.0f) {
                        ptr->unk_10.y = -20.0f;
                    }

                    ptr->unk_28 += 0x800;
                    if ((fabsf(ptr->unk_04.x - player->actor.world.pos.x) < 20.0f) &&
                        (fabsf(ptr->unk_04.z - player->actor.world.pos.z) < 20.0f) &&
                        (fabsf(ptr->unk_04.y - (player->actor.world.pos.y + 25.0f)) < 30.0f)) {
                        phi_s5 = true;
                        if ((player->transformation != PLAYER_FORM_GORON) && !player->isBurning) {
                            func_800B8D50(globalCtx, &this->actor, 2.0f, Rand_ZeroFloat(0x10000), 0.0f, 0x10);
                            for (j = 0; j < ARRAY_COUNT(player->flameTimers); j++) {
                                player->flameTimers[j] = Rand_S16Offset(0, 200);
                            }
                            player->isBurning = true;
                            func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_DEMO_DAMAGE);
                        }
                    }

                    Math_Vec3f_Copy(&sp90, &ptr->unk_04);
                    sp90.y += 30.0f;

                    temp_f0_2 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp88, &sp90);
                    if (fabsf(temp_f0_2 - this->actor.floorHeight) > 200.0f) {
                        phi_s5 = true;
                    }

                    if ((ptr->unk_04.y <= temp_f0_2) || (phi_s5 != 0)) {
                        if (phi_s5 == 0) {
                            ptr->unk_04.y = temp_f0_2;
                        }
                        ptr->unk_10.y = 0.0f;
                        ptr->unk_1C.y = 0.0f;
                        if (ptr->unk_2A == 0) {
                            for (j = 0; j < 5; j++) {
                                func_80A599E8(this, &ptr->unk_04, 2);
                            }
                            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_04, 30, NA_SE_EV_PLANT_BROKEN);
                        }
                        ptr->unk_2A++;
                    }
                }
            }
        }
    }
}

void func_80A5A184(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnWaterEffect* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    EnWaterEffectStruct* ptr = &this->unk_144[0];
    u8 flag = false;
    s16 i;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_144); i++, ptr++) {
        if (ptr->unk_00 == 4) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_004340);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 10, 0, 0);
                POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 500, 3600);
                flag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, (u8)ptr->unk_38, 0, 0, (u8)ptr->unk_3C);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, (ptr->unk_01 * -20) & 0x1FF,
                                        0x20, 0x80));

            Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);

            if (ptr->unk_2A >= 2) {
                Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            } else {
                Matrix_RotateY(Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx)), MTXMODE_APPLY);
            }

            Matrix_Scale(ptr->unk_2C.x, ptr->unk_2C.y, 1.0f, MTXMODE_APPLY);

            if ((i & 1) != 0) {
                Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
            }

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_0043E8);

            if ((ptr->unk_2A & 1) == 0) {
                Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y + 5.0f, ptr->unk_04.z, MTXMODE_NEW);
                Matrix_InsertXRotation_s(ptr->unk_28, MTXMODE_APPLY);
                Matrix_Scale(ptr->unk_2C.z, ptr->unk_2C.z, ptr->unk_2C.z, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_06AB30);
            }
        }
    }

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    CLOSE_DISPS(gfxCtx);
}

void func_80A5A534(Actor* thisx, GlobalContext* globalCtx) {
    EnWaterEffect* this = THIS;
    s32 i;

    if (this->unk_E38 < 1.0f) {
        Actor_MarkForDeath(&this->actor);
    }

    this->unk_DC4++;

    if (this->unk_DC4 >= 0) {
        for (i = 1; i < 4; i++) {
            this->unk_DC8[i].z += this->unk_E08[i];
            this->unk_E08[i] += this->unk_E18[i];
            if (this->unk_DC8[i].z <= 0.0f) {
                this->unk_DC8[i].z = 0.0f;
                this->unk_E08[i] = 0.0f;
            }
        }

        Math_ApproachF(&this->unk_DC8[1].y, 20.0f, 1.0f, 0.025f);
        Math_ApproachF(&this->unk_DC8[2].y, 20.0f, 1.0f, 0.075f);
        Math_ApproachF(&this->unk_DC8[3].y, 20.0f, 1.0f, 0.1f);

        if (this->unk_DC4 >= 24) {
            Math_ApproachF(&this->unk_DC8[4].y, 2.0f, 0.1f, 0.2f);
            Math_ApproachZeroF(&this->unk_E2C, 1.0f, 26.0f);
            Math_ApproachZeroF(&this->unk_E30, 1.0f, 26.0f);
            Math_ApproachZeroF(&this->unk_E34, 1.0f, 24.0f);
            if (this->unk_DC4 >= 50) {
                Math_ApproachZeroF(&this->unk_E38, 1.0f, 3.75f);
            }
        }
    }
}

void func_80A5A6B8(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnWaterEffect* this = THIS;
    EnWaterEffectStruct* ptr = &this->unk_144[0];
    u8 phi_s4 = false;
    s16 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, 165, 235, 255, 128);

    Matrix_StatePush();
    Matrix_StatePush();
    Matrix_StatePush();

    if ((this->actor.params == ENWATEREFFECT_777) || (this->actor.params == ENWATEREFFECT_778)) {
        if (this->unk_E2C > 1.0f) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_water_effect_Matanimheader_000DE0));
            Matrix_Scale(this->unk_DC8[1].y, this->unk_DC8[1].z, this->unk_DC8[1].y, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)this->unk_E2C);
            gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_000420);
        }

        Matrix_StatePop();

        if (this->unk_E30 > 1.0f) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_water_effect_Matanimheader_000E0C));
            Matrix_Scale(this->unk_DC8[2].y, this->unk_DC8[2].z, this->unk_DC8[2].y, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)this->unk_E30);
            gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_000730);
        }
        Matrix_StatePop();
    } else {
        Matrix_StatePop();
        Matrix_StatePop();
    }

    if ((this->unk_E34 > 1.0f) && (this->actor.params != ENWATEREFFECT_780)) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_water_effect_Matanimheader_000E40));
        Matrix_Scale(this->unk_DC8[3].y, this->unk_DC8[3].z, this->unk_DC8[3].y, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)this->unk_E34);
        gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_000A48);
    }

    Matrix_StatePop();

    if ((this->actor.params == ENWATEREFFECT_777) || (this->actor.params == ENWATEREFFECT_780)) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_water_effect_Matanimheader_000E58));
        Matrix_Scale(this->unk_DC8[4].y, this->unk_DC8[4].z, this->unk_DC8[4].y, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)this->unk_E38);
        gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_000CD8);
    }

    if (this->actor.params == ENWATEREFFECT_777) {
        func_8012C2DC(globalCtx->state.gfxCtx);

        for (i = 0; i < ARRAY_COUNT(this->unk_144) / 2; i++, ptr++) {
            if (ptr->unk_00 == 3) {
                if (!phi_s4) {
                    func_8012C448(globalCtx->state.gfxCtx);

                    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gDust1Tex));
                    gDPSetEnvColor(POLY_XLU_DISP++, 250, 250, 255, 0);
                    gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_004260);
                    phi_s4++;
                }

                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)ptr->unk_38, (u8)(((void)0, ptr->unk_38) + 55.0f), 225,
                                ptr->unk_3C);

                Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);
                Matrix_Scale(ptr->unk_2C.x, 1.0f, ptr->unk_2C.x, MTXMODE_APPLY);
                Matrix_InsertYRotation_f(ptr->unk_2C.z, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, object_water_effect_DL_0042F8);
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
