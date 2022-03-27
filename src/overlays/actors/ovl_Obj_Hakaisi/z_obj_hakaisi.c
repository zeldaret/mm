/*
 * File: z_obj_hakaisi.c
 * Overlay: ovl_Obj_Hakaisi
 * Description: Gravestone
 */

#include "z_obj_hakaisi.h"
#include "objects/object_hakaisi/object_hakaisi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_20)

#define THIS ((ObjHakaisi*)thisx)

void ObjHakaisi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B1444C(ObjHakaisi* this);
void func_80B14460(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B14510(ObjHakaisi* this);
void func_80B14524(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B14558(ObjHakaisi* this);
void func_80B1456C(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B145F4(ObjHakaisi* this);
void func_80B14648(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B149A8(ObjHakaisi* this);
void func_80B149C0(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B14A24(ObjHakaisi* this, GlobalContext* globalCtx, Vec3f vec);
void func_80B14B6C(ObjHakaisi* this, GlobalContext* globalCtx, Vec3f vec, s16 arg3);
void func_80B14CF8(GlobalContext* globalCtx, Vec3f vec, s16 arg2, s16 arg3, s32 arg4);
void func_80B14F4C(ObjHakaisi* this, GlobalContext* globalCtx, s32 arg2);
void func_80B151E0(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B15254(Actor* thisx, GlobalContext* globalCtx);
void func_80B15264(ObjHakaisi* this);
void func_80B15330(ObjHakaisi* this, GlobalContext* globalCtx);
void func_80B1544C(Actor* thisx, GlobalContext* globalCtx);
void func_80B154A0(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Hakaisi_InitVars = {
    ACTOR_OBJ_HAKAISI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HAKAISI,
    sizeof(ObjHakaisi),
    (ActorFunc)ObjHakaisi_Init,
    (ActorFunc)ObjHakaisi_Destroy,
    (ActorFunc)ObjHakaisi_Update,
    (ActorFunc)ObjHakaisi_Draw,
};

Vec3f D_80B155B0 = { 0.0f, 25.0f, 30.0f };

Vec3f D_80B155BC[] = { { 0.0f, 65.0f, 8.0f }, { 0.0f, 35.0f, 8.0f }, { 0.0f, 15.0f, 8.0f } };

Vec3f D_80B155E0 = { 0.0f, 0.0f, 0.0f };

Vec3f D_80B155EC = { 0.0f, 0.0f, 0.0f };

Color_RGBA8 D_80B155F8 = { 170, 130, 90, 255 };

Color_RGBA8 D_80B155FC = { 100, 60, 20, 0 };

Vec3f D_80B15600 = { 1.0f, 0.0f, 0.0f };

void ObjHakaisi_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjHakaisi* this = THIS;
    CollisionHeader* sp7C = NULL;
    MtxF sp3C;
    s32 i;

    switch (OBJHAKAISI_GET_FF(&this->dyna.actor)) {
        case 0:
            this->dyna.actor.textId = 0x13F9;
            break;

        case 1:
            this->dyna.actor.textId = 0x13FA;
            break;

        case 2:
            this->dyna.actor.textId = 0x13FB;
            break;

        case 3:
            this->dyna.actor.textId = 0x13FC;
            break;

        case 4:
        case 5:
            func_80B151E0(this, globalCtx);
            return;

        default:
            this->dyna.actor.textId = 0x1412;
            break;
    }

    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->dyna.actor.targetMode = 0;
    this->dyna.actor.colChkInfo.health = 30;
    if (OBJHAKAISI_GET_FF(&this->dyna.actor) == 3) {
        this->dyna.actor.draw = NULL;
        func_80B1444C(this);
        return;
    }

    DynaPolyActor_Init(&this->dyna, 1);
    CollisionHeader_GetVirtual(&object_hakaisi_Colheader_002FC4, &sp7C);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp7C);
    this->unk_19A = 0;
    this->unk_198 = 0;
    this->switchFlag = OBJHAKAISI_GET_SWITCHFLAG(thisx);
    this->unk_196 = this->dyna.actor.cutscene;

    if (this->switchFlag == 0xFF) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag != -1) && Flags_GetSwitch(globalCtx, this->switchFlag)) {
        Actor_MarkForDeath(&this->dyna.actor);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->dyna.actor.floorPoly == NULL) {
        Actor_MarkForDeath(&this->dyna.actor);
    }

    func_800C0094(this->dyna.actor.floorPoly, this->dyna.actor.world.pos.x, this->dyna.actor.floorHeight,
                  this->dyna.actor.world.pos.z, &sp3C);
    Matrix_SetCurrentState(&sp3C);
    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);
    Matrix_CopyCurrentState(&sp3C);
    func_8018219C(&sp3C, &this->dyna.actor.shape.rot, 1);
    this->dyna.actor.world.rot = this->dyna.actor.shape.rot;
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);
    Matrix_MultiplyVector3fByState(&D_80B155B0, &this->dyna.actor.focus.pos);

    for (i = 0; i < ARRAY_COUNT(D_80B155BC); i++) {
        Matrix_MultiplyVector3fByState(&D_80B155BC[i], &this->unk_160[i]);
    }

    func_80B1444C(this);
}

void ObjHakaisi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjHakaisi* this = THIS;

    if (OBJHAKAISI_GET_FF(&this->dyna.actor) != 3) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80B1444C(ObjHakaisi* this) {
    this->actionFunc = func_80B14460;
}

void func_80B14460(ObjHakaisi* this, GlobalContext* globalCtx) {
    s16 sp26 = BINANG_SUB(this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer);

    if (Actor_ProcessTalkRequest(&this->dyna.actor, &globalCtx->state)) {
        func_80B14510(this);
    } else if (this->dyna.actor.textId != 0) {
        if (ABS_ALT(sp26) < 0x2000) {
            func_800B8614(&this->dyna.actor, globalCtx, 100.0f);
        }
    }

    if (this->unk_198 == 1) {
        func_80B14558(this);
    }
}

void func_80B14510(ObjHakaisi* this) {
    this->actionFunc = func_80B14524;
}

void func_80B14524(ObjHakaisi* this, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&this->dyna.actor, globalCtx)) {
        func_80B1444C(this);
    }
}

void func_80B14558(ObjHakaisi* this) {
    this->actionFunc = func_80B1456C;
}

void func_80B1456C(ObjHakaisi* this, GlobalContext* globalCtx) {
    if (this->unk_196 != -1) {
        if (ActorCutscene_GetCanPlayNext(this->unk_196)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_196, &this->dyna.actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_196);
        }
    }
    if (this->dyna.actor.colChkInfo.health < 30) {
        func_80B145F4(this);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80B145F4(ObjHakaisi* this) {
    this->unk_19A = 0;
    this->dyna.actor.flags |= ACTOR_FLAG_8000000;
    this->dyna.actor.flags &= ~ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WALL_BROKEN);
    this->actionFunc = func_80B14648;
}

void func_80B14648(ObjHakaisi* this, GlobalContext* globalCtx) {
    if (this->unk_19A < 2) {
        func_80B14CF8(globalCtx, this->unk_160[this->unk_194], 100, 30, 5);
    }

    this->unk_19A++;

    if (this->dyna.actor.colChkInfo.health == 0) {
        func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
        func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
        func_80B14B6C(this, globalCtx, this->unk_160[this->unk_194], 70);
        Flags_SetSwitch(globalCtx, this->switchFlag);
        this->dyna.actor.draw = NULL;
        func_80B149A8(this);
    }

    if (this->unk_19E != this->dyna.actor.colChkInfo.health) {
        if ((this->unk_19E > 20) && (this->dyna.actor.colChkInfo.health <= 20)) {
            func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
            func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
            func_80B14F4C(this, globalCtx, 0);
            func_80B14B6C(this, globalCtx, this->unk_160[this->unk_194], 40);
            this->unk_194 = 1;
        } else if ((this->unk_19E > 10) && (this->dyna.actor.colChkInfo.health <= 10)) {
            func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
            func_80B14A24(this, globalCtx, this->unk_160[this->unk_194]);
            func_80B14B6C(this, globalCtx, this->unk_160[this->unk_194], 60);
            this->unk_194 = 2;
        }
        this->unk_19A = 0;
        this->dyna.actor.shape.yOffset -= 3.0f;
    }

    Math_ApproachZeroF(&this->dyna.actor.shape.yOffset, 0.8f, 100.0f);
    this->unk_19E = this->dyna.actor.colChkInfo.health;
}

void func_80B149A8(ObjHakaisi* this) {
    this->unk_19A = 0;
    this->actionFunc = func_80B149C0;
}

void func_80B149C0(ObjHakaisi* this, GlobalContext* globalCtx) {
    if (this->unk_19A < 60) {
        this->unk_19A++;
    } else if ((this->unk_196 != -1) && !ActorCutscene_GetCanPlayNext(this->unk_196)) {
        ActorCutscene_Stop(this->unk_196);
    }
}

void func_80B14A24(ObjHakaisi* this, GlobalContext* globalCtx, Vec3f vec) {
    s32 i;

    func_80B14CF8(globalCtx, vec, 100, 30, 5);

    for (i = 0; i < 5; i++) {
        vec.x += Rand_Centered() * 20.0f;
        vec.y += Rand_ZeroOne() * 5.0f;
        vec.z += Rand_Centered() * 20.0f;
        EffectSsHahen_SpawnBurst(globalCtx, &vec, 5.0f, 0, 20, 15, 3, OBJECT_HAKAISI, 10, object_hakaisi_DL_0021B0);
    }
}

void func_80B14B6C(ObjHakaisi* this, GlobalContext* globalCtx, Vec3f vec, s16 arg3) {
    s32 i;
    s16 temp_s1;
    Vec3f sp6C;

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WALL_BROKEN);

    for (i = 0; i < 5; i++) {
        temp_s1 = Rand_Next();

        sp6C.x = (Math_SinS(temp_s1) * 15.0f) + vec.x;
        sp6C.y = (Rand_ZeroOne() * 3.0f) + vec.y;
        sp6C.z = (Math_CosS(temp_s1) * 15.0f) + vec.z;

        EffectSsHahen_SpawnBurst(globalCtx, &sp6C, 10.0f, 0, arg3, 30, 2, OBJECT_HAKAISI, 15, object_hakaisi_DL_0021B0);
    }

    func_80B14CF8(globalCtx, vec, 100, 50, 20);
}

void func_80B14CF8(GlobalContext* globalCtx, Vec3f vec, s16 arg2, s16 arg3, s32 arg4) {
    s32 i;
    s16 temp_s0;
    Vec3f spAC;
    Vec3f spA0 = D_80B155E0;
    Vec3f sp94 = D_80B155EC;
    f32 temp_f20;
    f32 temp_f22;

    for (i = 0; i < arg4; i++) {
        temp_f20 = Rand_ZeroOne() * 30.0f;
        temp_f22 = Rand_ZeroOne() * 1.5f;
        temp_s0 = Rand_Next();

        spAC.x = (Math_SinS(temp_s0) * temp_f20) + vec.x;
        spAC.y = (Rand_Centered() * 4.0f) + vec.y;
        spAC.z = (Math_CosS(temp_s0) * temp_f20) + vec.z;

        spA0.x += temp_f22 * Math_SinS(temp_s0);
        spA0.y += Rand_Centered() + 0.5f;
        spA0.z += temp_f22 * Math_CosS(temp_s0);

        sp94.x = -0.1f * spA0.x;
        sp94.y = -0.1f * spA0.y;
        sp94.z = -0.1f * spA0.z;

        func_800B0EB0(globalCtx, &spAC, &spA0, &sp94, &D_80B155F8, &D_80B155FC, arg2, arg3, 10);
    }
}

void func_80B14F4C(ObjHakaisi* this, GlobalContext* globalCtx, s32 arg2) {
    if (arg2 == 0) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_HAKAISI, this->dyna.actor.world.pos.x,
                    this->dyna.actor.world.pos.y + 55.0f, this->dyna.actor.world.pos.z - 10.0f,
                    this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 4);
    } else {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_HAKAISI, this->dyna.actor.world.pos.x + 20.0f,
                    this->dyna.actor.world.pos.y + 30.0f, this->dyna.actor.world.pos.z - 10.0f,
                    this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 5);
    }
}

void ObjHakaisi_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHakaisi* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjHakaisi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjHakaisi* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_194 == 0) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_hakaisi_DL_002650);
    } else if (this->unk_194 == 1) {
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_hakaisi_DL_0029C0);
    } else {
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_hakaisi_DL_002CC0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B151E0(ObjHakaisi* this, GlobalContext* globalCtx) {
    this->dyna.actor.update = func_80B1544C;
    this->dyna.actor.draw = func_80B154A0;
    this->dyna.actor.destroy = func_80B15254;
    Actor_SetScale(&this->dyna.actor, 0.1f);
    this->dyna.actor.shape.yOffset = 100.0f;
    this->dyna.actor.flags &= ~ACTOR_FLAG_1;
    func_80B15264(this);
}

void func_80B15254(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80B15264(ObjHakaisi* this) {
    s32 pad;
    s16 sp32 = Rand_Next();

    Matrix_InsertRotation(Rand_Next(), Rand_Next(), Rand_Next(), MTXMODE_NEW);
    Matrix_MultiplyVector3fByState(&D_80B15600, &this->unk_184);
    this->dyna.actor.gravity = -1.0f;
    this->unk_19C = Rand_Next() >> 0x12;
    this->dyna.actor.velocity.x = Math_SinS(sp32) * 4.0f;
    this->dyna.actor.velocity.z = Math_CosS(sp32) * 4.0f;
    this->dyna.actor.velocity.y = 7.0f;
    this->actionFunc = func_80B15330;
}

void func_80B15330(ObjHakaisi* this, GlobalContext* globalCtx) {
    s32 pad;
    MtxF sp34;

    this->dyna.actor.velocity.y += this->dyna.actor.gravity;
    Actor_UpdatePos(&this->dyna.actor);

    if (this->dyna.actor.bgCheckFlags & 2) {
        func_80B14B6C(this, globalCtx, this->dyna.actor.world.pos, 40);
        func_80B14CF8(globalCtx, this->dyna.actor.world.pos, 100, 30, 10);
        Actor_MarkForDeath(&this->dyna.actor);
    }

    Matrix_InsertRotationAroundUnitVector_s(this->unk_19C, &this->unk_184, MTXMODE_NEW);
    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_CopyCurrentState(&sp34);

    func_8018219C(&sp34, &this->dyna.actor.shape.rot, 0);
}

void func_80B1544C(Actor* thisx, GlobalContext* globalCtx) {
    ObjHakaisi* this = THIS;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);
}

void func_80B154A0(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (OBJHAKAISI_GET_FF(thisx) == 4) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_hakaisi_DL_001F10);
    } else {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_hakaisi_DL_0021B0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
