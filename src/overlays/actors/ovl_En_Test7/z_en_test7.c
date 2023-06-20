/*
 * File: z_en_test7.c
 * Overlay: ovl_En_Test7
 * Description: Soaring effects (wings, sphere, etc)
 */

#include "prevent_bss_reordering.h"
#include "z_en_test7.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000 | ACTOR_FLAG_200000 | ACTOR_FLAG_2000000)

#define THIS ((EnTest7*)thisx)

void EnTest7_Init(Actor* thisx, PlayState* play2);
void EnTest7_Destroy(Actor* thisx, PlayState* play);
void EnTest7_Update(Actor* thisx, PlayState* play);
void EnTest7_Draw(Actor* thisx, PlayState* play);

void EnTest7_SetupAction(EnTest7* this, EnTest7ActionFunc actionFunc);
void func_80AF19A8(EnTest7* this, PlayState* play);
void func_80AF1A2C(EnTest7* this, PlayState* play);
void func_80AF1CA0(EnTest7* this, PlayState* play);
void func_80AF1E44(EnTest7* this, PlayState* play);
void func_80AF1F48(EnTest7* this, PlayState* play);
void func_80AF2030(EnTest7* this, PlayState* play);
void func_80AF21E8(EnTest7* this, PlayState* play);
void func_80AF2318(EnTest7* this, PlayState* play);
void func_80AF2350(EnTest7* this, PlayState* play);
void func_80AF2854(EnTest7* this, PlayState* play);
void func_80AF2938(EnTest7* this, PlayState* play);
void func_80AF2AE8(EnTest7* this, PlayState* play);
void func_80AF2C48(EnTest7* this, PlayState* play);
void func_80AF2EC8(EnTest7* this, PlayState* play);
void func_80AF2F98(EnTest7* this, PlayState* play);
void func_80AF30F4(EnTest7* this, PlayState* play);

ActorInit En_Test7_InitVars = {
    ACTOR_EN_TEST7,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest7),
    (ActorFunc)EnTest7_Init,
    (ActorFunc)EnTest7_Destroy,
    (ActorFunc)EnTest7_Update,
    (ActorFunc)EnTest7_Draw,
};

void EnTest7_SetupAction(EnTest7* this, EnTest7ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_80AF082C(EnTest7* this, EnTest7UnkFunc func) {
    this->unk_1E58 = func;
}

void func_80AF0838(EnTest7Struct2* arg0) {
    EnTest7Struct2* ptr = arg0;
    s32 i;

    for (i = 0, ptr = arg0; i < 100; i++, ptr++) {
        s32 pad;

        ptr->unk_00 = 0;
        ptr->unk_04 = 0;
        ptr->unk_08.x = 0.0f;
        ptr->unk_08.y = 0.0f;
        ptr->unk_08.z = 0.0f;
        ptr->unk_14 = 0.0f;
        ptr->unk_18 = 0.0f;
        ptr->unk_1C = 0.0f;
        ptr->unk_20 = 0.0f;
        ptr->unk_24 = 0.0f;
        ptr->unk_28 = 0.0f;
        ptr->unk_2C = 0.00001f;
        ptr->unk_30.x = 0;
        ptr->unk_30.y = 0;
        ptr->unk_30.z = 0;
        ptr->unk_36 = 0;
        ptr->unk_38 = 0;
        ptr->unk_3A = 0;
    }
}

void func_80AF0984(EnTest7Struct2* arg0, Vec3f* arg1, s32 arg2) {
    s16 sp26 = Rand_ZeroOne() * 0xFFFF;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f4;

    arg0->unk_08 = *arg1;

    if (arg2 != 0) {
        Math_CosS(sp26);
        arg0->unk_08.x = arg0->unk_08.x;
        arg0->unk_08.y += (Rand_ZeroOne() * 100.0f) - 20.0f;
        Math_SinS(sp26);
        arg0->unk_08.z = arg0->unk_08.z;
    }

    sp20 = (Rand_ZeroOne() * 4.0f) + 2.0f;

    arg0->unk_14 = Math_CosS(sp26) * sp20;
    arg0->unk_18 = Rand_ZeroOne();
    arg0->unk_1C = Math_SinS(sp26) * sp20;

    arg0->unk_20 = 0.0f;
    arg0->unk_24 = 0.0f;
    arg0->unk_28 = 0.0f;
    arg0->unk_2C = 0.25f;
    arg0->unk_30.x = Rand_ZeroOne() * 0x10000;
    arg0->unk_30.y = Rand_ZeroOne() * 0x10000;
    arg0->unk_30.z = Rand_ZeroOne() * 0x10000;
    arg0->unk_04 = 60;

    if (Rand_ZeroOne() < 0.9f) {
        arg0->unk_00 = 1;
        arg0->unk_30.x = Rand_ZeroOne() * 0x10000;
        arg0->unk_30.y = Rand_ZeroOne() * 0x10000;
        arg0->unk_30.z = Rand_ZeroOne() * 0x10000;
        arg0->unk_36 = 0;
        arg0->unk_38 = 0;
        arg0->unk_3A = 0;
    } else {
        arg0->unk_00 = 2;
        arg0->unk_30.x = 0;
        arg0->unk_30.y = 0;
        arg0->unk_30.z = Rand_ZeroOne() * 5000.0f;
        arg0->unk_36 = 0;
        arg0->unk_38 = (Rand_ZeroOne() * 8000.0f) + 2000.0f;
        if (Rand_ZeroOne() > 0.5f) {
            arg0->unk_38 = -arg0->unk_38;
        }
        arg0->unk_3A = 0;
    }
}

void func_80AF0C30(EnTest7Struct2* arg0, Vec3f* arg1, s32 arg2) {
    static s32 D_80AF3410 = 0;
    s32 i;
    s32 phi_t0 = false;
    EnTest7Struct2* ptr;
    s32 idx;

    for (i = 0, ptr = arg0; i < 100; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            func_80AF0984(ptr, arg1, arg2);
            D_80AF3410 = i;
            phi_t0 = true;
            break;
        }
    }

    if (!phi_t0) {
        idx = D_80AF3410 + 1;
        if (idx >= 100) {
            idx = 0;
        }

        func_80AF0984(&arg0[idx], arg1, arg2);
    }
}

Vec3f D_80AF3414 = { 0.0f, 1.0f, 0.0f };

Vec3f D_80AF3420 = { 0.0f, 0.0f, 1.0f };

void func_80AF0CDC(PlayState* play, EnTest7Struct2* arg1) {
    static MtxF D_80AF38B0;
    static Vec3f D_80AF38F0;
    static f32 D_80AF38FC;
    static Vec3f D_80AF3900;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_v0;
    f32 phi_f8;

    sp2C = arg1->unk_04 % 41;
    sp24 = 0;
    sp28 = (arg1->unk_04 + 0x1B58) % 41;

    SkinMatrix_SetRotateRPY(&D_80AF38B0, arg1->unk_30.x, arg1->unk_30.y, arg1->unk_30.z);
    SkinMatrix_Vec3fMtxFMultXYZ(&D_80AF38B0, &D_80AF3414, &D_80AF38F0);
    SkinMatrix_Vec3fMtxFMultXYZ(&D_80AF38B0, &D_80AF3420, &D_80AF3900);

    if (arg1->unk_30.x < 0x3448) {
        arg1->unk_30.x += 0x384;
    } else if (arg1->unk_30.x >= 0x4BB9) {
        arg1->unk_30.x -= 0x384;
    } else {
        arg1->unk_30.x = (Math_SinS((sp2C * 65535.0f) / 41.0f) * 2000.0f) + 16384.0f;
    }

    if (arg1->unk_30.y < -0xBB8) {
        arg1->unk_30.y += 0x384;
    } else if (arg1->unk_30.y > 0xBB8) {
        arg1->unk_30.y -= 0x384;
    } else {
        sp24 = 1;
        arg1->unk_30.y = Math_SinS((sp28 * 65535.0f) / 41.0f) * 2000.0f;
    }

    if (sp24 == 1) {
        if (D_80AF38F0.y < 0.0f) {
            arg1->unk_14 += D_80AF38F0.x * 0.5f;
            arg1->unk_18 += (D_80AF38F0.y * 0.5f) + 0.08f;
            arg1->unk_1C += (D_80AF38F0.z * 0.5f);
        } else {
            arg1->unk_14 += -D_80AF38F0.x * 0.5f;
            arg1->unk_18 += (-D_80AF38F0.y * 0.5f) + 0.08f;
            arg1->unk_1C += -D_80AF38F0.z * 0.5f;
        }
    } else if (D_80AF38F0.y < 0.0f) {
        arg1->unk_14 += D_80AF38F0.x * 0.2f;
        arg1->unk_18 += (D_80AF38F0.y * 0.2f) + 0.08f;
        arg1->unk_1C += D_80AF38F0.z * 0.2f;
    } else {
        arg1->unk_14 += -D_80AF38F0.x * 0.2f;
        arg1->unk_18 += (-D_80AF38F0.y * 0.2f) + 0.08f;
        arg1->unk_1C += (-D_80AF38F0.z * 0.2f);
    }

    arg1->unk_08.x += arg1->unk_14;
    arg1->unk_08.y += arg1->unk_18;
    arg1->unk_08.z += arg1->unk_1C;
}

void func_80AF10D8(PlayState* play, EnTest7Struct2* arg1) {
    arg1->unk_30.y += arg1->unk_38;

    arg1->unk_20 = Rand_Centered();
    arg1->unk_24 = Rand_Centered() + -0.01f;
    arg1->unk_28 = Rand_Centered();

    arg1->unk_14 += arg1->unk_20;
    arg1->unk_18 += arg1->unk_24;
    arg1->unk_1C += arg1->unk_28;

    arg1->unk_08.x += arg1->unk_14;
    arg1->unk_08.y += arg1->unk_18;
    arg1->unk_08.z += arg1->unk_1C;
}

void func_80AF118C(PlayState* play, EnTest7Struct2* arg1, EnTest7* this, s32 arg3, s32 arg4) {
    s32 pad[4];
    EnTest7Struct2* ptr;
    s16 phi_s1;
    s32 i;
    f32 temp_f28;
    Vec3f sp8C;
    f32 temp_f0;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;

    for (i = 0, ptr = arg1; i < (s32)(ARRAY_COUNT(this->unk_15C) * sizeof(this->unk_15C[0]));
         i += sizeof(this->unk_15C[0]), ptr++) {
        arg1 = ptr;

        if (arg1->unk_00 == 0) {
            continue;
        }

        if (arg1->unk_00 == 1) {
            func_80AF0CDC(play, arg1);
        } else {
            func_80AF10D8(play, arg1);
        }

        if (arg3) {
            temp_f22 = arg1->unk_08.x - this->actor.world.pos.x;
            temp_f24 = arg1->unk_08.z - this->actor.world.pos.z;
            temp_f0 = SQ(temp_f22) + SQ(temp_f24);

            phi_s1 = -10000;
            if (temp_f0 > SQ(20.0f)) {
                phi_s1 /= ((temp_f0 - SQ(20.0f)) * 0.00125f) + 1.0f;
            }

            temp_f26 = (temp_f22 * Math_CosS(phi_s1)) - (Math_SinS(phi_s1) * temp_f24);
            temp_f28 = (temp_f22 * Math_SinS(phi_s1)) + (Math_CosS(phi_s1) * temp_f24);

            arg1->unk_08.x = this->actor.world.pos.x + temp_f26;
            arg1->unk_08.z = this->actor.world.pos.z + temp_f28;

            temp_f22 = arg1->unk_14;
            temp_f24 = arg1->unk_1C;

            arg1->unk_14 = (temp_f22 * Math_CosS(phi_s1)) - (Math_SinS(phi_s1) * temp_f24);
            arg1->unk_1C = (temp_f22 * Math_SinS(phi_s1)) + (Math_CosS(phi_s1) * temp_f24);

            temp_f22 = arg1->unk_20;
            temp_f24 = arg1->unk_28;

            arg1->unk_20 = (temp_f22 * Math_CosS(phi_s1)) - (Math_SinS(phi_s1) * temp_f24);
            arg1->unk_28 = (temp_f22 * Math_SinS(phi_s1)) + (Math_CosS(phi_s1) * temp_f24);
        }

        if (arg4) {
            sp8C.x = arg1->unk_08.x - this->actor.world.pos.x;
            sp8C.y = arg1->unk_08.y - (this->actor.world.pos.y + 40.0f);
            sp8C.z = arg1->unk_08.z - this->actor.world.pos.z;

            temp_f2 = 1.0f - (0.5f / ((Math3D_Vec3fMagnitude(&sp8C) / 500.0f) + 1.0f));

            sp8C.x *= temp_f2;
            sp8C.y *= temp_f2;
            sp8C.z *= temp_f2;

            arg1->unk_08.x = this->actor.world.pos.x + sp8C.x;
            arg1->unk_08.y = this->actor.world.pos.y + sp8C.y + 40.0f;
            arg1->unk_08.z = this->actor.world.pos.z + sp8C.z;
        }
    }
}

void func_80AF14FC(PlayState* play2, EnTest7Struct2* arg1) {
    s32 pad[3];
    PlayState* play = play2;
    Mtx* temp_v0;
    EnTest7Struct2* ptr;
    s32 i;
    MtxF sp6C;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL26_Opa(play->state.gfxCtx);

    Matrix_Push();

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

    for (i = 0, ptr = arg1; i < 0x1770; i += 0x3C, ptr++) {
        if (ptr->unk_00 == 0) {
            continue;
        }

        if ((ptr->unk_08.x > 30000.0f) || (ptr->unk_08.x < -30000.0f) || (ptr->unk_08.y > 30000.0f) ||
            (ptr->unk_08.y < -30000.0f) || (ptr->unk_08.z > 30000.0f) || (ptr->unk_08.z < -30000.0f)) {
            ptr->unk_00 = 0;
            continue;
        }

        Matrix_Translate(ptr->unk_08.x, ptr->unk_08.y, ptr->unk_08.z, MTXMODE_NEW);

        if (ptr->unk_00 == 1) {
            Matrix_RotateZYX(ptr->unk_30.x, ptr->unk_30.y, ptr->unk_30.z, MTXMODE_APPLY);
        } else {
            SkinMatrix_SetRotateYRP(&sp6C, ptr->unk_30.x, ptr->unk_30.y, ptr->unk_30.z);
            Matrix_Mult(&sp6C, MTXMODE_APPLY);
        }

        Matrix_Scale(ptr->unk_2C, ptr->unk_2C, ptr->unk_2C, MTXMODE_APPLY);
        if (ptr->unk_00 == 2) {
            Matrix_Translate(0.0f, 30.0f, 0.0f, MTXMODE_APPLY);
        }

        temp_v0 = Matrix_NewMtx(play->state.gfxCtx);
        if (temp_v0 == NULL) {
            continue;
        }
        gSPMatrix(POLY_OPA_DISP++, temp_v0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_081628);
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80AF1730(EnTest7Struct* arg0) {
    arg0->unk_00 = 0.0f;
    arg0->unk_04 = 0.0f;
    arg0->unk_08 = 1.0f;
    arg0->unk_0C = 1.0f;
    arg0->unk_10 = 0;
}

void EnTest7_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest7* this = THIS;
    Player* player = GET_PLAYER(play);
    Player* player2 = GET_PLAYER(play);

    this->actor.world.rot.y = this->actor.shape.rot.y = player->actor.shape.rot.y;
    this->unk_144 = 0;
    this->unk_1E54 = 0;
    this->unk_1E8E = player->actor.shape.rot.y;
    this->unk_1E90 = player->actor.scale.x;
    this->unk_1E94 = player->actor.scale.z;

    func_80183430(&this->unk_18CC, &gameplay_keep_Blob_085640, &gameplay_keep_Blob_083534, this->unk_18FC,
                  this->unk_1BA8, NULL);
    func_801834A8(&this->unk_18CC, &gameplay_keep_Blob_083534);
    func_80AF0838(this->unk_15C);
    func_80AF1730(&this->unk_148);

    if (ENTEST7_GET(&this->actor) == ENTEST7_MINUS1) {
        func_80AF082C(this, func_80AF2938);
        EnTest7_SetupAction(this, NULL);
    } else {
        func_80AF082C(this, func_80AF19A8);
        EnTest7_SetupAction(this, func_80AF2854);
        Audio_PlayBgm_StorePrevBgm(NA_BGM_SONG_OF_SOARING);
    }

    if (play->playerCsIds[PLAYER_CS_ID_SONG_WARP] == CS_ID_NONE) {
        Actor_Kill(&this->actor);
        return;
    }

    CutsceneManager_Queue(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]);
    player2->stateFlags1 |= PLAYER_STATE1_20;
    Lights_PointNoGlowSetInfo(&this->lightInfo, (Math_SinS(this->unk_1E8E) * 90.0f) + player->actor.world.pos.x,
                              player->actor.world.pos.y + 10.0f,
                              (Math_CosS(this->unk_1E8E) * 90.0f) + player->actor.world.pos.z, 255, 255, 255, 255);
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
}

void EnTest7_Destroy(Actor* thisx, PlayState* play) {
    EnTest7* this = THIS;

    CutsceneManager_Stop(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
}

void func_80AF19A8(EnTest7* this, PlayState* play) {
    if (!CutsceneManager_IsNext(play->playerCsIds[PLAYER_CS_ID_SONG_WARP])) {
        CutsceneManager_Queue(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]);
    } else {
        CutsceneManager_Start(play->playerCsIds[PLAYER_CS_ID_SONG_WARP], NULL);
        func_80AF082C(this, func_80AF1A2C);
        play->unk_18844 = true;
    }
}

void func_80AF1A2C(EnTest7* this, PlayState* play) {
    Color_RGB8 fogColor = { 64, 0, 0 };
    Color_RGB8 ambientColor = { 220, 220, 255 };
    f32 envLerp = this->unk_1E54 / 10.0f;

    Environment_LerpAmbientColor(play, &ambientColor, envLerp);
    Environment_LerpFogColor(play, &fogColor, envLerp);
    Environment_LerpFog(play, 2000, 4000, envLerp);

    if (this->unk_1E54 >= 10) {
        Camera* subCam =
            Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));

        this->subCamEye = subCam->eye;
        this->subCamAt = subCam->at;
        this->subCamFov = subCam->fov;

        func_80AF082C(this, func_80AF1CA0);
        this->unk_144 |= 0x20;
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_OPEN);
        Play_EnableMotionBlur(120);
    }
}

void func_80AF1B68(EnTest7* this, PlayState* play) {
    this->unk_144 |= 2;

    if (this->unk_148.unk_04 < 11.0f) {
        this->unk_148.unk_04 = this->unk_148.unk_04 + 0.3f;
        this->unk_148.unk_08 = ((this->unk_148.unk_00 * -0.45f) / 11.0f) + 0.7f;
        this->unk_148.unk_0C = ((this->unk_148.unk_00 * -0.29999998f) / 11.0f) + 0.7f;
    }

    if (this->unk_148.unk_00 < 11.0f) {
        this->unk_148.unk_00 += 1.0f;
        if (this->unk_148.unk_00 > 6.0f) {
            Player* player = GET_PLAYER(play);

            this->unk_144 &= ~1;
            player->actor.draw = NULL;
        }
    } else if (this->unk_1E54 >= 87) {
        func_80AF082C(this, func_80AF1F48);
        this->unk_144 &= -9;
        this->unk_148.unk_10 -= 0x2EE0;
    } else {
        this->unk_148.unk_10 -= 0x2EE0;
    }
}

void func_80AF1CA0(EnTest7* this, PlayState* play) {
    Vec3f sp34;

    if (func_80183DE0(&this->unk_18CC)) {
        func_80AF082C(this, func_80AF1E44);
    }

    if (this->unk_18CC.frameCtrl.unk_10 > 60.0f) {
        func_80AF1B68(this, play);
    }

    if ((this->unk_18CC.frameCtrl.unk_10 > 20.0f) && !(this->unk_144 & 0x40)) {
        this->unk_144 |= 0x40;
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_CLOSE);
    }

    if (this->unk_18CC.frameCtrl.unk_10 > 42.0f) {
        if (!(this->unk_144 & 0x80)) {
            this->unk_144 |= 0x80;
            Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_ROLL);
        }

        if (Rand_ZeroOne() < 0.3f) {
            Camera* subCam =
                Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
            f32 rand = Rand_ZeroOne();

            sp34.x = ((subCam->eye.x - this->actor.world.pos.x) * rand) + this->actor.world.pos.x;
            sp34.y = ((subCam->eye.y - this->actor.world.pos.y) * rand) + this->actor.world.pos.y;
            sp34.z = ((subCam->eye.z - this->actor.world.pos.z) * rand) + this->actor.world.pos.z;

            func_80AF0C30(this->unk_15C, &sp34, 1);
            this->unk_144 |= 8;
        }
    } else {
        this->unk_144 |= 1;
    }
}

void func_80AF1E44(EnTest7* this, PlayState* play) {
    Vec3f sp34;
    Camera* subCam;
    f32 rand;

    func_80AF1B68(this, play);

    if (Rand_ZeroOne() < 0.3f) {
        subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
        rand = Rand_ZeroOne();
        sp34.x = ((subCam->eye.x - this->actor.world.pos.x) * rand) + this->actor.world.pos.x;
        sp34.y = ((subCam->eye.y - this->actor.world.pos.y) * rand) + this->actor.world.pos.y;
        sp34.z = ((subCam->eye.z - this->actor.world.pos.z) * rand) + this->actor.world.pos.z;
        func_80AF0C30(this->unk_15C, &sp34, 1);
    }

    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    func_80AF0C30(this->unk_15C, &sp34, 1);
    this->unk_18FC[1].y += 0x2EE0;
}

void func_80AF1F48(EnTest7* this, PlayState* play) {
    s32 pad;
    s32 temp = this->unk_1E54 - 86;
    f32 temp_f0 = temp / 10.0f;
    Vec3f sp20;

    this->unk_144 |= 0x10;

    this->unk_148.unk_08 = (-0.15f * temp_f0) + 0.25f;
    this->unk_148.unk_0C = (-0.3f * temp_f0) + 0.4f;
    this->unk_148.unk_10 -= 0x2EE0;

    this->unk_144 |= 4;

    if (this->unk_1E54 >= 96) {
        func_80AF082C(this, func_80AF2030);
        this->unk_144 &= ~0x10;
    }
    Math_Vec3f_Copy(&sp20, &this->actor.world.pos);
    func_80AF0C30(this->unk_15C, &sp20, 1);
}

void func_80AF2030(EnTest7* this, PlayState* play) {
    s32 temp = this->unk_1E54 - 96;
    f32 four = 4;
    f32 sp1C = 1.0f - (temp / four);
    Camera* subCam;
    f32 temp_f2;
    f32 temp_f4;

    this->unk_148.unk_08 = ((temp * -0.1f) / four) + 0.1f;
    this->unk_148.unk_0C = ((temp * 5.9f) / four) + 0.1f;
    this->unk_148.unk_10 -= 0x2EE0;
    this->actor.world.pos.y += 100.0f;

    subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
    subCam->focalActor = NULL;

    subCam->eye.x = ((subCam->eye.x - this->subCamEye.x) * sp1C) + this->subCamEye.x;
    subCam->eye.y = ((subCam->eye.y - this->subCamEye.y) * sp1C) + this->subCamEye.y;
    subCam->eye.z = ((subCam->eye.z - this->subCamEye.z) * sp1C) + this->subCamEye.z;
    subCam->fov = ((subCam->fov - this->subCamFov) * sp1C) + this->subCamFov;

    if (this->unk_1E54 >= 100) {
        R_PLAY_FILL_SCREEN_ON = true;
        R_PLAY_FILL_SCREEN_R = 255;
        R_PLAY_FILL_SCREEN_G = 255;
        R_PLAY_FILL_SCREEN_B = 255;
        R_PLAY_FILL_SCREEN_ALPHA = 255;
        play->unk_18844 = false;
        this->unk_144 &= ~4;
        func_80AF082C(this, func_80AF21E8);
        Play_DisableMotionBlur();
    }
}

void func_80AF21E8(EnTest7* this, PlayState* play) {
    s32 sp2C = this->unk_1E54 - 100;
    f32 envLerp;
    Color_RGB8 fogColor = { 64, 0, 0 };
    Color_RGB8 ambientColor = { 220, 220, 255 };

    if (R_PLAY_FILL_SCREEN_ON) {
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_VANISH);
        R_PLAY_FILL_SCREEN_ON = false;
        R_PLAY_FILL_SCREEN_R = 0;
        R_PLAY_FILL_SCREEN_G = 0;
        R_PLAY_FILL_SCREEN_B = 0;
        R_PLAY_FILL_SCREEN_ALPHA = 0;
    }

    envLerp = 1.0f - (sp2C / 10.0f);
    Environment_LerpAmbientColor(play, &ambientColor, envLerp);
    Environment_LerpFogColor(play, &fogColor, envLerp);
    Environment_LerpFog(play, 2000, 4000, envLerp);

    if (this->unk_1E54 >= 110) {
        func_80AF082C(this, func_80AF2318);
    }
}

void func_80AF2318(EnTest7* this, PlayState* play) {
    if (this->unk_1E54 >= 130) {
        func_80AF082C(this, func_80AF2350);
    }
}

u16 D_80AF343C[] = {
    ENTRANCE(GREAT_BAY_COAST, 11), ENTRANCE(ZORA_CAPE, 6),
    ENTRANCE(SNOWHEAD, 3),         ENTRANCE(MOUNTAIN_VILLAGE_WINTER, 8),
    ENTRANCE(SOUTH_CLOCK_TOWN, 9), ENTRANCE(MILK_ROAD, 4),
    ENTRANCE(WOODFALL, 4),         ENTRANCE(SOUTHERN_SWAMP_POISONED, 10),
    ENTRANCE(IKANA_CANYON, 4),     ENTRANCE(STONE_TOWER, 3),
};

void func_80AF2350(EnTest7* this, PlayState* play) {
    Vec3f sp2C;

    if (this) {}

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);

    if (Rand_ZeroOne() < 0.1f) {
        func_80AF0C30(this->unk_15C, &sp2C, 1);
    }

    this->unk_148.unk_10 -= 0x2EE0;

    if (play->sceneId == SCENE_SECOM) {
        play->nextEntrance = ENTRANCE(IKANA_CANYON, 6);
    } else if (ENTEST7_GET(&this->actor) == ENTEST7_26) {
        func_80169F78(&play->state);
        gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams =
            (gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams & 0xFF) | 0x600;
        gSaveContext.respawnFlag = -6;
    } else {
        play->nextEntrance = D_80AF343C[ENTEST7_GET(&this->actor) - ENTEST7_1C];
        if ((play->nextEntrance == ENTRANCE(SOUTHERN_SWAMP_POISONED, 10)) &&
            CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_WOODFALL_TEMPLE)) {
            play->nextEntrance = ENTRANCE(SOUTHERN_SWAMP_CLEARED, 10);
        } else if ((play->nextEntrance == ENTRANCE(MOUNTAIN_VILLAGE_WINTER, 8)) &&
                   CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE)) {
            play->nextEntrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 8);
        }
    }

    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_BLACK;
    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
    gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
}

void func_80AF24D8(EnTest7* this, PlayState* play, f32 arg2) {
    Vec3f sp3C;
    Vec3f* pos;
    Player* player = GET_PLAYER(play);
    Camera* subCam =
        Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));

    pos = &player->actor.world.pos;
    subCam->focalActor = NULL;

    sp3C.x = ((180.0f * Math_SinS(this->unk_1E8E)) * Math_CosS(0xFA0)) + pos->x;
    sp3C.y = (Math_SinS(0xFA0) * 180.0f) + pos->y;
    sp3C.z = ((180.0f * Math_CosS(this->unk_1E8E)) * Math_CosS(0xFA0)) + pos->z;

    subCam->eye.x = ((sp3C.x - subCam->eye.x) * arg2) + subCam->eye.x;
    subCam->eye.y = ((sp3C.y - subCam->eye.y) * arg2) + subCam->eye.y;
    subCam->eye.z = ((sp3C.z - subCam->eye.z) * arg2) + subCam->eye.z;

    subCam->fov = ((this->subCamFov - subCam->fov) * arg2) + subCam->fov;
    subCam->at.y += 1.4444444f;
}

void func_80AF2654(EnTest7* this, PlayState* play, f32 arg2) {
    Vec3f* pos;
    Player* player = GET_PLAYER(play);
    Camera* subCam;
    Vec3f sp30;

    subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
    subCam->focalActor = NULL;

    pos = &player->actor.world.pos;

    sp30.x = ((80.0f * Math_SinS(this->unk_1E8E)) * Math_CosS(0xBB8)) + pos->x;
    sp30.y = (Math_SinS(0xBB8) * 80.0f) + pos->y;
    sp30.z = ((80.0f * Math_CosS(this->unk_1E8E)) * Math_CosS(0xBB8)) + pos->z;

    subCam->eye.x = ((sp30.x - subCam->eye.x) * arg2) + subCam->eye.x;
    subCam->eye.y = ((sp30.y - subCam->eye.y) * arg2) + subCam->eye.y;
    subCam->eye.z = ((sp30.z - subCam->eye.z) * arg2) + subCam->eye.z;

    subCam->at.x = ((pos->x - subCam->at.x) * arg2) + subCam->at.x;
    subCam->at.y = (((pos->y + 40.0f) - subCam->at.y) * arg2) + subCam->at.y;
    subCam->at.z = ((pos->z - subCam->at.z) * arg2) + subCam->at.z;

    subCam->fov = ((this->subCamFov - subCam->fov) * arg2) + subCam->fov;
}

void func_80AF2808(EnTest7* this, PlayState* play, f32 arg2) {
    Player* player = GET_PLAYER(play);

    player->actor.shape.rot.y += 0x2EE0;
    player->actor.scale.x = ((0.0f - this->unk_1E90) * arg2) + this->unk_1E90;
    player->actor.scale.z = ((0.0f - this->unk_1E94) * arg2) + this->unk_1E94;
}

void func_80AF2854(EnTest7* this, PlayState* play) {
    f32 temp;
    f32 sixteen = 16.0f;

    if ((this->unk_1E54 >= 12) && (this->unk_1E54 < 31)) {
        temp = (this->unk_1E54 - 12) / 18.0f;
        func_80AF24D8(this, play, temp);
    } else if ((this->unk_1E54 >= 79) && (this->unk_1E54 < 96)) {
        temp = (this->unk_1E54 - 79) / sixteen;
        func_80AF2654(this, play, temp);
    }

    if ((this->unk_1E54 >= 42) && (this->unk_1E54 < 69)) {
        temp = (this->unk_1E54 - 42) / 26.0f;
        func_80AF2808(this, play, temp);
    }
}

void func_80AF2938(EnTest7* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->unk_1E98 = player->actor.draw;
    player->actor.draw = NULL;
    player->stateFlags2 |= PLAYER_STATE2_20000000;
    this->unk_144 |= 2;
    this->unk_148.unk_04 = 30.0f;
    if (play->roomCtx.curRoom.behaviorType1 != ROOM_BEHAVIOR_TYPE1_1) {
        func_80AF082C(this, func_80AF2AE8);
    } else {
        func_80AF082C(this, func_80AF2EC8);
    }
}

s16 D_80AF3450[] = { 0, 0x31C7 };

f32 D_80AF3454 = 3500.0f;

void func_80AF29C0(EnTest7* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);
    Vec3f* pos = &player->actor.world.pos;
    Camera* subCam =
        Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));

    subCam->at.x = ((D_80AF3454 * Math_SinS(D_80AF3450[0]) * Math_CosS(D_80AF3450[1]))) + pos->x;
    subCam->at.y = (Math_SinS(D_80AF3450[1]) * D_80AF3454) + pos->y;
    subCam->at.z = ((D_80AF3454 * Math_CosS(D_80AF3450[0])) * Math_CosS(D_80AF3450[1])) + pos->z;

    this->actor.world.pos.x = subCam->at.x;
    this->actor.world.pos.y = subCam->at.y - 40.0f;
    this->actor.world.pos.z = subCam->at.z;
}

void func_80AF2AE8(EnTest7* this, PlayState* play) {
    Camera* subCam;

    if (!CutsceneManager_IsNext(play->playerCsIds[PLAYER_CS_ID_SONG_WARP])) {
        CutsceneManager_Queue(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]);
        return;
    }

    CutsceneManager_Start(play->playerCsIds[PLAYER_CS_ID_SONG_WARP], NULL);
    func_80AF082C(this, func_80AF2C48);

    subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
    this->subCamEye = subCam->eye;
    this->subCamAt = subCam->at;

    func_80AF29C0(this, play);
}

void func_80AF2BAC(EnTest7* this, PlayState* play, Vec3f* arg2, f32 arg3) {
    f32 x;
    f32 y;
    f32 z;
    Camera* subCam =
        Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));

    subCam->focalActor = NULL;
    x = ((subCam->at.x - arg2->x) * arg3) + arg2->x;
    y = ((subCam->at.y - arg2->y) * arg3) + arg2->y;
    z = ((subCam->at.z - arg2->z) * arg3) + arg2->z;

    subCam->at.x = x;
    subCam->at.y = y;
    subCam->at.z = z;
}

void func_80AF2C48(EnTest7* this, PlayState* play) {
    f32 sp24 = (40 - this->unk_1E54) / 40.0f;
    Camera* subCam;

    this->unk_148.unk_00 = 11.0f;
    this->unk_144 |= 4;
    this->unk_148.unk_08 = 0.05f;
    this->unk_148.unk_0C = 0.05f;
    this->unk_148.unk_10 += 0x2EE0;

    this->actor.world.pos.x = ((this->actor.world.pos.x - this->actor.home.pos.x) * sp24) + this->actor.home.pos.x;
    this->actor.world.pos.y = ((this->actor.world.pos.y - this->actor.home.pos.y) * sp24) + this->actor.home.pos.y;
    this->actor.world.pos.z = ((this->actor.world.pos.z - this->actor.home.pos.z) * sp24) + this->actor.home.pos.z;

    subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
    func_80AF2BAC(this, play, &this->actor.home.pos, sp24);

    subCam->at.x = this->actor.world.pos.x;
    subCam->at.y = this->actor.world.pos.y + 40.0f;
    subCam->at.z = this->actor.world.pos.z;

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_PL_WARP_WING_ROLL_2 - SFX_FLAG);
    if (this->unk_1E54 >= 40) {
        this->unk_144 &= ~4;
        func_80AF082C(this, func_80AF2F98);
    }
}

void func_80AF2DB4(EnTest7* this, PlayState* play) {
    Camera* subCam;
    Player* player = GET_PLAYER(play);
    Vec3f* pos = &player->actor.world.pos;

    subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));

    subCam->eye.x = (Math_SinS(-player->actor.shape.rot.y) * 200.0f * -0.83907f) + pos->x;
    subCam->eye.y = pos->y + 108.8042f;
    subCam->eye.z = (Math_CosS(-player->actor.shape.rot.y) * 200.0f * -0.83907f) + pos->z;

    subCam->at.x = pos->x;
    subCam->at.y = pos->y + 40.0f;
    subCam->at.z = pos->z;
}

void func_80AF2EC8(EnTest7* this, PlayState* play) {
    Camera* subCam;

    if (!CutsceneManager_IsNext(play->playerCsIds[PLAYER_CS_ID_SONG_WARP])) {
        CutsceneManager_Queue(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]);
    } else {
        CutsceneManager_Start(play->playerCsIds[PLAYER_CS_ID_SONG_WARP], NULL);
        func_80AF082C(this, func_80AF2F98);

        subCam = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(play->playerCsIds[PLAYER_CS_ID_SONG_WARP]));
        this->subCamEye = subCam->eye;
        this->subCamAt = subCam->at;
        this->unk_1E54 = 40;

        func_80AF2DB4(this, play);
    }
}

void func_80AF2F98(EnTest7* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Player* player2 = GET_PLAYER(play);
    Vec3f sp2C;

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_PL_WARP_WING_ROLL_2 - SFX_FLAG);

    sp2C = this->actor.world.pos;

    func_80AF0C30(this->unk_15C, &sp2C, 1);
    func_80AF0C30(this->unk_15C, &sp2C, 1);
    this->unk_148.unk_04 = 70 - this->unk_1E54;
    if (this->unk_1E54 > 70) {
        func_80AF082C(this, func_80AF30F4);
    }

    if (this->unk_148.unk_04 > 11.0f) {
        f32 temp = this->unk_148.unk_04 - 11.0f;

        this->unk_148.unk_08 = ((-0.35f * temp) / 19.0f) + 0.4f;
        this->unk_148.unk_0C = ((-0.35f * temp) / 19.0f) + 0.4f;
        this->unk_148.unk_10 += 0x2EE0;
    } else {
        player2->actor.draw = this->unk_1E98;
        this->unk_148.unk_00 = this->unk_148.unk_04;
        this->unk_148.unk_08 = ((this->unk_148.unk_04 * -0.29999998f) / 11.0f) + 0.7f;
        this->unk_148.unk_0C = ((this->unk_148.unk_04 * -0.29999998f) / 11.0f) + 0.7f;
        player->stateFlags2 &= ~PLAYER_STATE2_20000000;
    }
}

void func_80AF30F4(EnTest7* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->unk_1E54 > 90) {
        player->stateFlags1 &= ~PLAYER_STATE1_20;
        player->stateFlags1 &= ~PLAYER_STATE1_20000000;
        Actor_Kill(&this->actor);
    }
}

void EnTest7_Update(Actor* thisx, PlayState* play) {
    EnTest7* this = THIS;

    this->unk_1E58(this, play);

    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }

    this->unk_1E54++;

    func_80AF118C(play, this->unk_15C, this, (this->unk_144 & 8) != 0, (this->unk_144 & 0x10) != 0);
}

s32 func_80AF31D0(PlayState* play, SkeletonInfo* skeletonInfo, s32 limbIndex, Gfx** dList, u8* flags, Actor* thisx,
                  Vec3f* scale, Vec3s* rot, Vec3f* pos) {
    EnTest7* this = THIS;
    Vec3f sp18;

    if ((*dList != NULL) && (Rand_ZeroOne() < 0.03f)) {
        Matrix_MultVec3f(&gZeroVec3f, &sp18);
        func_80AF0C30(this->unk_15C, &sp18, 0);
    }
    return true;
}

void EnTest7_Draw(Actor* thisx, PlayState* play) {
    s32 pad[2];
    EnTest7* this = THIS;
    s32 sp40;

    if (this->unk_144 & 1) {
        Mtx* mtx = GRAPH_ALLOC(play->state.gfxCtx, this->unk_18CC.unk_18->unk_1 * sizeof(Mtx));

        if (mtx != NULL) {
            func_8018450C(play, &this->unk_18CC, mtx, func_80AF31D0, NULL, &this->actor);
        } else {
            return;
        }
    }

    if (this->unk_144 & 2) {
        Matrix_Push();
        Matrix_Translate(0.0f, 4000.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateZYX(0, this->unk_148.unk_10, 0, MTXMODE_APPLY);
        Matrix_Scale(this->unk_148.unk_08 * 100.0f, this->unk_148.unk_0C * 100.0f, this->unk_148.unk_08 * 100.0f,
                     MTXMODE_APPLY);
        sp40 = this->unk_148.unk_00;
        AnimatedMat_DrawStep(play, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_0815D0), sp40);
        Gfx_DrawDListXlu(play, gameplay_keep_DL_080FC8);
        Matrix_Pop();
    }

    func_80AF14FC(play, this->unk_15C);

    if (this->unk_144 & 4) {
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, this->actor.world.pos, 70.0f, 5.0f, 0, 0);
    }
}
