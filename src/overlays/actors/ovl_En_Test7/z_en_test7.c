/*
 * File: z_en_test7.c
 * Overlay: ovl_En_Test7
 * Description: Soaring effects (wings, sphere, etc)
 */

#include "z_en_test7.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000 | ACTOR_FLAG_200000 | ACTOR_FLAG_2000000)

#define THIS ((EnTest7*)thisx)

void EnTest7_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTest7_SetupAction(EnTest7* this, EnTest7ActionFunc actionFunc);
void func_80AF19A8(EnTest7* this, GlobalContext* globalCtx);
void func_80AF1A2C(EnTest7* this, GlobalContext* globalCtx);
void func_80AF1CA0(EnTest7* this, GlobalContext* globalCtx);
void func_80AF1E44(EnTest7* this, GlobalContext* globalCtx);
void func_80AF1F48(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2030(EnTest7* this, GlobalContext* globalCtx);
void func_80AF21E8(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2318(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2350(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2854(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2938(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2AE8(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2C48(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2EC8(EnTest7* this, GlobalContext* globalCtx);
void func_80AF2F98(EnTest7* this, GlobalContext* globalCtx);
void func_80AF30F4(EnTest7* this, GlobalContext* globalCtx);

const ActorInit En_Test7_InitVars = {
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

void func_80AF0CDC(GlobalContext* globalCtx, EnTest7Struct2* arg1) {
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

void func_80AF10D8(GlobalContext* globalCtx, EnTest7Struct2* arg1) {
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

void func_80AF118C(GlobalContext* globalCtx, EnTest7Struct2* arg1, EnTest7* this, s32 arg3, s32 arg4) {
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
            func_80AF0CDC(globalCtx, arg1);
        } else {
            func_80AF10D8(globalCtx, arg1);
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

void func_80AF14FC(GlobalContext* globalCtx2, EnTest7Struct2* arg1) {
    s32 pad[3];
    GlobalContext* globalCtx = globalCtx2;
    Mtx* temp_v0;
    EnTest7Struct2* ptr;
    s32 i;
    MtxF sp6C;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C1C0(globalCtx->state.gfxCtx);

    Matrix_StatePush();

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

        Matrix_InsertTranslation(ptr->unk_08.x, ptr->unk_08.y, ptr->unk_08.z, MTXMODE_NEW);

        if (ptr->unk_00 == 1) {
            Matrix_InsertRotation(ptr->unk_30.x, ptr->unk_30.y, ptr->unk_30.z, MTXMODE_APPLY);
        } else {
            SkinMatrix_SetRotateYRP(&sp6C, ptr->unk_30.x, ptr->unk_30.y, ptr->unk_30.z);
            Matrix_InsertMatrix(&sp6C, MTXMODE_APPLY);
        }

        Matrix_Scale(ptr->unk_2C, ptr->unk_2C, ptr->unk_2C, MTXMODE_APPLY);
        if (ptr->unk_00 == 2) {
            Matrix_InsertTranslation(0.0f, 30.0f, 0.0f, MTXMODE_APPLY);
        }

        temp_v0 = Matrix_NewMtx(globalCtx->state.gfxCtx);
        if (temp_v0 != NULL) {
            gSPMatrix(POLY_OPA_DISP++, temp_v0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_081628);
        }
    }

    if (ptr) {}

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80AF1730(EnTest7Struct* arg0) {
    arg0->unk_00 = 0.0f;
    arg0->unk_04 = 0.0f;
    arg0->unk_08 = 1.0f;
    arg0->unk_0C = 1.0f;
    arg0->unk_10 = 0;
}

void EnTest7_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTest7* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);

    this->actor.world.rot.y = this->actor.shape.rot.y = player->actor.shape.rot.y;
    this->unk_144 = 0;
    this->unk_1E54 = 0;
    this->unk_1E8E = player->actor.shape.rot.y;
    this->unk_1E90 = player->actor.scale.x;
    this->unk_1E94 = player->actor.scale.z;

    func_80183430(&this->unk_18CC, &gameplay_keep_Blob_085640, &gameplay_keep_Blob_083534, this->unk_18FC,
                  this->unk_1BA8, 0);
    func_801834A8(&this->unk_18CC, &gameplay_keep_Blob_083534);
    func_80AF0838(this->unk_15C);
    func_80AF1730(&this->unk_148);

    if (ENTEST7_GET(&this->actor) == ENTEST7_MINUS1) {
        func_80AF082C(this, func_80AF2938);
        EnTest7_SetupAction(this, NULL);
    } else {
        func_80AF082C(this, func_80AF19A8);
        EnTest7_SetupAction(this, func_80AF2854);
        func_801A2E54(NA_BGM_SONG_OF_SOARING);
    }

    if (globalCtx->playerActorCsIds[8] == -1) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[8]);
    player2->stateFlags1 |= 0x20;
    Lights_PointNoGlowSetInfo(&this->lightInfo, (Math_SinS(this->unk_1E8E) * 90.0f) + player->actor.world.pos.x,
                              player->actor.world.pos.y + 10.0f,
                              (Math_CosS(this->unk_1E8E) * 90.0f) + player->actor.world.pos.z, 255, 255, 255, 255);
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
}

void EnTest7_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTest7* this = THIS;

    ActorCutscene_Stop(globalCtx->playerActorCsIds[8]);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void func_80AF19A8(EnTest7* this, GlobalContext* globalCtx) {
    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[8])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[8]);
    } else {
        ActorCutscene_Start(globalCtx->playerActorCsIds[8], NULL);
        func_80AF082C(this, func_80AF1A2C);
        globalCtx->unk_18844 = 1;
    }
}

void func_80AF1A2C(EnTest7* this, GlobalContext* globalCtx) {
    Color_RGB8 sp34 = { 64, 0, 0 };
    Color_RGB8 sp30 = { 220, 220, 255 };
    f32 sp2C = this->unk_1E54 / 10.0f;

    func_800FD59C(globalCtx, &sp30, sp2C);
    func_800FD654(globalCtx, &sp34, sp2C);
    func_800FD698(globalCtx, 2000, 4000, sp2C);

    if (this->unk_1E54 >= 10) {
        Camera* camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));

        this->unk_1E60 = camera->eye;
        this->unk_1E6C = camera->at;
        this->unk_1E78 = camera->fov;

        func_80AF082C(this, func_80AF1CA0);
        this->unk_144 |= 0x20;
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_OPEN);
        func_8016566C(0x78);
    }
}

void func_80AF1B68(EnTest7* this, GlobalContext* globalCtx) {
    this->unk_144 |= 2;

    if (this->unk_148.unk_04 < 11.0f) {
        this->unk_148.unk_04 = this->unk_148.unk_04 + 0.3f;
        this->unk_148.unk_08 = ((this->unk_148.unk_00 * -0.45f) / 11.0f) + 0.7f;
        this->unk_148.unk_0C = ((this->unk_148.unk_00 * -0.29999998f) / 11.0f) + 0.7f;
    }

    if (this->unk_148.unk_00 < 11.0f) {
        this->unk_148.unk_00 += 1.0f;
        if (this->unk_148.unk_00 > 6.0f) {
            Player* player = GET_PLAYER(globalCtx);

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

void func_80AF1CA0(EnTest7* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    if (func_80183DE0(&this->unk_18CC)) {
        func_80AF082C(this, func_80AF1E44);
    }

    if (this->unk_18CC.frameCtrl.unk_10 > 60.0f) {
        func_80AF1B68(this, globalCtx);
    }

    if ((this->unk_18CC.frameCtrl.unk_10 > 20.0f) && !(this->unk_144 & 0x40)) {
        this->unk_144 |= 0x40;
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_CLOSE);
    }

    if (this->unk_18CC.frameCtrl.unk_10 > 42.0f) {
        if (!(this->unk_144 & 0x80)) {
            this->unk_144 |= 0x80;
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_ROLL);
        }

        if (Rand_ZeroOne() < 0.3f) {
            Camera* camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
            f32 rand = Rand_ZeroOne();

            sp34.x = ((camera->eye.x - this->actor.world.pos.x) * rand) + this->actor.world.pos.x;
            sp34.y = ((camera->eye.y - this->actor.world.pos.y) * rand) + this->actor.world.pos.y;
            sp34.z = ((camera->eye.z - this->actor.world.pos.z) * rand) + this->actor.world.pos.z;

            func_80AF0C30(this->unk_15C, &sp34, 1);
            this->unk_144 |= 8;
        }
    } else {
        this->unk_144 |= 1;
    }
}

void func_80AF1E44(EnTest7* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    Camera* camera;
    f32 rand;

    func_80AF1B68(this, globalCtx);

    if (Rand_ZeroOne() < 0.3f) {
        camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
        rand = Rand_ZeroOne();
        sp34.x = ((camera->eye.x - this->actor.world.pos.x) * rand) + this->actor.world.pos.x;
        sp34.y = ((camera->eye.y - this->actor.world.pos.y) * rand) + this->actor.world.pos.y;
        sp34.z = ((camera->eye.z - this->actor.world.pos.z) * rand) + this->actor.world.pos.z;
        func_80AF0C30(this->unk_15C, &sp34, 1);
    }

    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    func_80AF0C30(this->unk_15C, &sp34, 1);
    this->unk_18FC[1].y += 0x2EE0;
}

void func_80AF1F48(EnTest7* this, GlobalContext* globalCtx) {
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

void func_80AF2030(EnTest7* this, GlobalContext* globalCtx) {
    s32 temp = this->unk_1E54 - 96;
    f32 four = 4;
    f32 sp1C = 1.0f - (temp / four);
    Camera* camera;
    f32 temp_f2;
    f32 temp_f4;

    this->unk_148.unk_08 = ((temp * -0.1f) / four) + 0.1f;
    this->unk_148.unk_0C = ((temp * 5.9f) / four) + 0.1f;
    this->unk_148.unk_10 -= 0x2EE0;
    this->actor.world.pos.y += 100.0f;

    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
    camera->player = NULL;

    camera->eye.x = ((camera->eye.x - this->unk_1E60.x) * sp1C) + this->unk_1E60.x;
    camera->eye.y = ((camera->eye.y - this->unk_1E60.y) * sp1C) + this->unk_1E60.y;
    camera->eye.z = ((camera->eye.z - this->unk_1E60.z) * sp1C) + this->unk_1E60.z;
    camera->fov = ((camera->fov - this->unk_1E78) * sp1C) + this->unk_1E78;

    if (this->unk_1E54 >= 100) {
        MREG(64) = 1;
        MREG(65) = 255;
        MREG(66) = 255;
        MREG(67) = 255;
        MREG(68) = 255;
        globalCtx->unk_18844 = 0;
        this->unk_144 &= ~4;
        func_80AF082C(this, func_80AF21E8);
        func_80165690();
    }
}

void func_80AF21E8(EnTest7* this, GlobalContext* globalCtx) {
    s32 sp2C = this->unk_1E54 - 100;
    f32 sp1C;
    Color_RGB8 sp24 = { 64, 0, 0 };
    Color_RGB8 sp20 = { 220, 220, 255 };

    if (MREG(64) != 0) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_PL_WARP_WING_VANISH);
        MREG(64) = 0;
        MREG(65) = 0;
        MREG(66) = 0;
        MREG(67) = 0;
        MREG(68) = 0;
    }

    sp1C = 1.0f - (sp2C / 10.0f);
    func_800FD59C(globalCtx, &sp20, sp1C);
    func_800FD654(globalCtx, &sp24, sp1C);
    func_800FD698(globalCtx, 2000, 4000, sp1C);

    if (this->unk_1E54 >= 110) {
        func_80AF082C(this, func_80AF2318);
    }
}

void func_80AF2318(EnTest7* this, GlobalContext* globalCtx) {
    if (this->unk_1E54 >= 130) {
        func_80AF082C(this, func_80AF2350);
    }
}

u16 D_80AF343C[] = {
    0x68B0, 0x6A60, 0xB230, 0x9A80, 0xD890, 0x3E40, 0x8640, 0x84A0, 0x2040, 0xAA30,
};

void func_80AF2350(EnTest7* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this) {}

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);

    if (Rand_ZeroOne() < 0.1f) {
        func_80AF0C30(this->unk_15C, &sp2C, 1);
    }

    this->unk_148.unk_10 -= 0x2EE0;

    if (globalCtx->sceneNum == SCENE_SECOM) {
        globalCtx->nextEntranceIndex = 0x2060;
    } else if (ENTEST7_GET(&this->actor) == ENTEST7_26) {
        func_80169F78(&globalCtx->state);
        gSaveContext.respawn[2].playerParams = (gSaveContext.respawn[2].playerParams & 0xFF) | 0x600;
        gSaveContext.respawnFlag = -6;
    } else {
        globalCtx->nextEntranceIndex = D_80AF343C[ENTEST7_GET(&this->actor) - ENTEST7_1C];
        if ((globalCtx->nextEntranceIndex == 0x84A0) && (gSaveContext.save.weekEventReg[20] & 2)) {
            globalCtx->nextEntranceIndex = 0xCA0;
        } else if ((globalCtx->nextEntranceIndex == 0x9A80) && (gSaveContext.save.weekEventReg[33] & 0x80)) {
            globalCtx->nextEntranceIndex = 0xAE80;
        }
    }

    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
    gSaveContext.seqIndex = 0xFF;
    gSaveContext.nightSeqIndex = 0xFF;
}

void func_80AF24D8(EnTest7* this, GlobalContext* globalCtx, f32 arg2) {
    Vec3f sp3C;
    Vec3f* pos;
    Player* player = GET_PLAYER(globalCtx);
    Camera* camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));

    pos = &player->actor.world.pos;
    camera->player = NULL;

    sp3C.x = ((180.0f * Math_SinS(this->unk_1E8E)) * Math_CosS(0xFA0)) + pos->x;
    sp3C.y = (Math_SinS(0xFA0) * 180.0f) + pos->y;
    sp3C.z = ((180.0f * Math_CosS(this->unk_1E8E)) * Math_CosS(0xFA0)) + pos->z;

    camera->eye.x = ((sp3C.x - camera->eye.x) * arg2) + camera->eye.x;
    camera->eye.y = ((sp3C.y - camera->eye.y) * arg2) + camera->eye.y;
    camera->eye.z = ((sp3C.z - camera->eye.z) * arg2) + camera->eye.z;

    camera->fov = ((this->unk_1E78 - camera->fov) * arg2) + camera->fov;
    camera->at.y += 1.4444444f;
}

void func_80AF2654(EnTest7* this, GlobalContext* globalCtx, f32 arg2) {
    Vec3f* pos;
    Player* player = GET_PLAYER(globalCtx);
    Camera* camera;
    Vec3f sp30;

    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
    camera->player = NULL;

    pos = &player->actor.world.pos;

    sp30.x = ((80.0f * Math_SinS(this->unk_1E8E)) * Math_CosS(0xBB8)) + pos->x;
    sp30.y = (Math_SinS(0xBB8) * 80.0f) + pos->y;
    sp30.z = ((80.0f * Math_CosS(this->unk_1E8E)) * Math_CosS(0xBB8)) + pos->z;

    camera->eye.x = ((sp30.x - camera->eye.x) * arg2) + camera->eye.x;
    camera->eye.y = ((sp30.y - camera->eye.y) * arg2) + camera->eye.y;
    camera->eye.z = ((sp30.z - camera->eye.z) * arg2) + camera->eye.z;

    camera->at.x = ((pos->x - camera->at.x) * arg2) + camera->at.x;
    camera->at.y = (((pos->y + 40.0f) - camera->at.y) * arg2) + camera->at.y;
    camera->at.z = ((pos->z - camera->at.z) * arg2) + camera->at.z;

    camera->fov = ((this->unk_1E78 - camera->fov) * arg2) + camera->fov;
}

void func_80AF2808(EnTest7* this, GlobalContext* globalCtx, f32 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.shape.rot.y += 0x2EE0;
    player->actor.scale.x = ((0.0f - this->unk_1E90) * arg2) + this->unk_1E90;
    player->actor.scale.z = ((0.0f - this->unk_1E94) * arg2) + this->unk_1E94;
}

void func_80AF2854(EnTest7* this, GlobalContext* globalCtx) {
    f32 temp;
    f32 sixteen = 16.0f;

    if ((this->unk_1E54 >= 12) && (this->unk_1E54 < 31)) {
        temp = (this->unk_1E54 - 12) / 18.0f;
        func_80AF24D8(this, globalCtx, temp);
    } else if ((this->unk_1E54 >= 79) && (this->unk_1E54 < 96)) {
        temp = (this->unk_1E54 - 79) / sixteen;
        func_80AF2654(this, globalCtx, temp);
    }

    if ((this->unk_1E54 >= 42) && (this->unk_1E54 < 69)) {
        temp = (this->unk_1E54 - 42) / 26.0f;
        func_80AF2808(this, globalCtx, temp);
    }
}

void func_80AF2938(EnTest7* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_1E98 = player->actor.draw;
    player->actor.draw = NULL;
    player->stateFlags2 |= 0x20000000;
    this->unk_144 |= 2;
    this->unk_148.unk_04 = 30.0f;
    if (globalCtx->roomCtx.currRoom.unk3 != 1) {
        func_80AF082C(this, func_80AF2AE8);
    } else {
        func_80AF082C(this, func_80AF2EC8);
    }
}

s16 D_80AF3450[] = { 0, 0x31C7 };

f32 D_80AF3454 = 3500.0f;

void func_80AF29C0(EnTest7* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* pos = &player->actor.world.pos;
    Camera* temp_s0 = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));

    temp_s0->at.x = ((D_80AF3454 * Math_SinS(D_80AF3450[0]) * Math_CosS(D_80AF3450[1]))) + pos->x;
    temp_s0->at.y = (Math_SinS(D_80AF3450[1]) * D_80AF3454) + pos->y;
    temp_s0->at.z = ((D_80AF3454 * Math_CosS(D_80AF3450[0])) * Math_CosS(D_80AF3450[1])) + pos->z;

    this->actor.world.pos.x = temp_s0->at.x;
    this->actor.world.pos.y = temp_s0->at.y - 40.0f;
    this->actor.world.pos.z = temp_s0->at.z;
}

void func_80AF2AE8(EnTest7* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[8])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[8]);
        return;
    }

    ActorCutscene_Start(globalCtx->playerActorCsIds[8], NULL);
    func_80AF082C(this, func_80AF2C48);

    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
    this->unk_1E60 = camera->eye;
    this->unk_1E6C = camera->at;

    func_80AF29C0(this, globalCtx);
}

void func_80AF2BAC(EnTest7* this, GlobalContext* globalCtx, Vec3f* arg2, f32 arg3) {
    f32 x;
    f32 y;
    f32 z;
    Camera* camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));

    camera->player = NULL;
    x = ((camera->at.x - arg2->x) * arg3) + arg2->x;
    y = ((camera->at.y - arg2->y) * arg3) + arg2->y;
    z = ((camera->at.z - arg2->z) * arg3) + arg2->z;

    camera->at.x = x;
    camera->at.y = y;
    camera->at.z = z;
}

void func_80AF2C48(EnTest7* this, GlobalContext* globalCtx) {
    f32 sp24 = (40 - this->unk_1E54) / 40.0f;
    Camera* camera;

    this->unk_148.unk_00 = 11.0f;
    this->unk_144 |= 4;
    this->unk_148.unk_08 = 0.05f;
    this->unk_148.unk_0C = 0.05f;
    this->unk_148.unk_10 += 0x2EE0;

    this->actor.world.pos.x = ((this->actor.world.pos.x - this->actor.home.pos.x) * sp24) + this->actor.home.pos.x;
    this->actor.world.pos.y = ((this->actor.world.pos.y - this->actor.home.pos.y) * sp24) + this->actor.home.pos.y;
    this->actor.world.pos.z = ((this->actor.world.pos.z - this->actor.home.pos.z) * sp24) + this->actor.home.pos.z;

    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
    func_80AF2BAC(this, globalCtx, &this->actor.home.pos, sp24);

    camera->at.x = this->actor.world.pos.x;
    camera->at.y = this->actor.world.pos.y + 40.0f;
    camera->at.z = this->actor.world.pos.z;

    func_800B9010(&this->actor, NA_SE_PL_WARP_WING_ROLL_2 - SFX_FLAG);
    if (this->unk_1E54 >= 40) {
        this->unk_144 &= ~4;
        func_80AF082C(this, func_80AF2F98);
    }
}

void func_80AF2DB4(EnTest7* this, GlobalContext* globalCtx) {
    Camera* camera;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* pos = &player->actor.world.pos;

    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));

    camera->eye.x = (Math_SinS(-player->actor.shape.rot.y) * 200.0f * -0.83907f) + pos->x;
    camera->eye.y = pos->y + 108.8042f;
    camera->eye.z = (Math_CosS(-player->actor.shape.rot.y) * 200.0f * -0.83907f) + pos->z;

    camera->at.x = pos->x;
    camera->at.y = pos->y + 40.0f;
    camera->at.z = pos->z;
}

void func_80AF2EC8(EnTest7* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[8])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[8]);
    } else {
        ActorCutscene_Start(globalCtx->playerActorCsIds[8], NULL);
        func_80AF082C(this, func_80AF2F98);

        camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(globalCtx->playerActorCsIds[8]));
        this->unk_1E60 = camera->eye;
        this->unk_1E6C = camera->at;
        this->unk_1E54 = 40;

        func_80AF2DB4(this, globalCtx);
    }
}

void func_80AF2F98(EnTest7* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);
    Vec3f sp2C;

    func_800B9010(&this->actor, NA_SE_PL_WARP_WING_ROLL_2 - SFX_FLAG);

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
        player->stateFlags2 &= ~0x20000000;
    }
}

void func_80AF30F4(EnTest7* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_1E54 > 90) {
        player->stateFlags1 &= ~0x20;
        player->stateFlags1 &= ~0x20000000;
        Actor_MarkForDeath(&this->actor);
    }
}

void EnTest7_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTest7* this = THIS;

    this->unk_1E58(this, globalCtx);

    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
    }

    this->unk_1E54++;

    func_80AF118C(globalCtx, this->unk_15C, this, (this->unk_144 & 8) != 0, (this->unk_144 & 0x10) != 0);
}

s32 func_80AF31D0(GlobalContext* globalCtx, SkeletonInfo* skeletonInfo, s32 limbIndex, Gfx** dList, u8* flags,
                  Actor* thisx, Vec3f* scale, Vec3s* rot, Vec3f* pos) {
    EnTest7* this = THIS;
    Vec3f sp18;

    if ((*dList != NULL) && (Rand_ZeroOne() < 0.03f)) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp18);
        func_80AF0C30(this->unk_15C, &sp18, 0);
    }
    return true;
}

void EnTest7_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnTest7* this = THIS;
    s32 sp40;

    if (this->unk_144 & 1) {
        Mtx* mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * this->unk_18CC.unk_18->unk_1));

        if (mtx != NULL) {
            func_8018450C(globalCtx, &this->unk_18CC, mtx, func_80AF31D0, NULL, &this->actor);
        } else {
            return;
        }
    }

    if (this->unk_144 & 2) {
        Matrix_StatePush();
        Matrix_InsertTranslation(0.0f, 4000.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertRotation(0, this->unk_148.unk_10, 0, MTXMODE_APPLY);
        Matrix_Scale(this->unk_148.unk_08 * 100.0f, this->unk_148.unk_0C * 100.0f, this->unk_148.unk_08 * 100.0f,
                     MTXMODE_APPLY);
        sp40 = this->unk_148.unk_00;
        AnimatedMat_DrawStep(globalCtx, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_0815D0), sp40);
        Gfx_DrawDListXlu(globalCtx, gameplay_keep_DL_080FC8);
        Matrix_StatePop();
    }

    func_80AF14FC(globalCtx, this->unk_15C);

    if (this->unk_144 & 4) {
        func_800F9824(globalCtx, &globalCtx->envCtx, &globalCtx->view, globalCtx->state.gfxCtx, this->actor.world.pos,
                      70.0f, 5.0f, 0, 0);
    }
}
