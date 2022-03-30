/*
 * File: z_en_tru_mt.c
 * Overlay: ovl_En_Tru_Mt
 * Description: Koume's Target Game - Koume on Broom
 */

#include "z_en_tru_mt.h"
#include "overlays/actors/ovl_En_Jc_Mato/z_en_jc_mato.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnTruMt*)thisx)

void EnTruMt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B76A64(EnTruMt* this, GlobalContext* globalCtx);
void func_80B76BB8(EnTruMt* this, GlobalContext* globalCtx);
void func_80B76C38(EnTruMt* this, GlobalContext* globalCtx);

const ActorInit En_Tru_Mt_InitVars = {
    ACTOR_EN_TRU_MT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTruMt),
    (ActorFunc)EnTruMt_Init,
    (ActorFunc)EnTruMt_Destroy,
    (ActorFunc)EnTruMt_Update,
    (ActorFunc)EnTruMt_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 22 }, 100 },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static AnimationInfoS D_80B7755C[] = {
    { &object_tru_Anim_00F9A0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_tru_Anim_00F9A0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_tru_Anim_0108AC, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_tru_Anim_009348, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_tru_Anim_00EEDC, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_tru_Anim_015CA0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_tru_Anim_015CA0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_tru_Anim_014728, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_tru_Anim_01B5C4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_tru_Anim_007FA0, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_tru_Anim_016B4C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_tru_Anim_011F88, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_tru_Anim_00446C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_tru_Anim_003698, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_tru_Anim_002BD8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_tru_Anim_00446C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

Vec3f D_80B7765C = { 3000.0f, -800.0f, 0.0f };

Vec3f D_80B77668 = { 0.0f, 0.0f, -3000.0f };

s32 func_80B76030(SkelAnime* skelAnime, s16 arg1) {
    s16 endFrame;
    s16 startFrame;
    s32 ret = false;

    if ((arg1 >= 0) && (arg1 < ARRAY_COUNT(D_80B7755C))) {
        endFrame = D_80B7755C[arg1].frameCount;
        if (endFrame < 0) {
            endFrame = Animation_GetLastFrame(D_80B7755C[arg1].animation);
        }

        startFrame = D_80B7755C[arg1].startFrame;
        if (startFrame < 0) {
            startFrame = Animation_GetLastFrame(D_80B7755C[arg1].animation);
        }

        Animation_Change(skelAnime, D_80B7755C[arg1].animation, D_80B7755C[arg1].playSpeed, startFrame, endFrame,
                         D_80B7755C[arg1].mode, D_80B7755C[arg1].morphFrames);
        ret = true;
    }
    return ret;
}

void func_80B76110(EnTruMt* this) {
    if (DECR(this->unk_34E) == 0) {
        this->unk_34C++;
        if (this->unk_34C >= 3) {
            this->unk_34E = Rand_S16Offset(30, 30);
            this->unk_34C = 0;
        }
    }
}

void func_80B76188(EnTruMt* this) {
    this->unk_38E.x = Math_CosS(this->unk_38A) * this->unk_38C;
    this->unk_38A += 0x1555;
    Math_SmoothStepToS(&this->unk_38C, 0, 4, 0x3E8, 1);
}

s32 func_80B761FC(EnTruMt* this, GlobalContext* globalCtx) {
    this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = this->actor.world.pos.y + 16.0f;
    this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

    if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        if (!(((EnJcMato*)this->actor.child)->collider.base.acFlags & AC_HIT) &&
            (this->actor.child->colChkInfo.damageEffect != 0xF)) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->unk_3A4 == 0) {
                this->unk_3A4 = 1;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KOUME_DAMAGE);
            } else {
                this->unk_3A4 = 0;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KOUME_DAMAGE2);
            }
            globalCtx->interfaceCtx.unk_25E = 1;
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
            return true;
        }
    }

    if (this->unk_38C >= 0xB7) {
        func_80B76188(this);
    } else {
        this->unk_38E.x = 0;
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    return false;
}

s32 func_80B76368(EnTruMt* this, GlobalContext* globalCtx) {
    Actor* bgActor = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (bgActor != NULL) {
        if (bgActor->id == ACTOR_BG_INGATE) {
            this->unk_394 = bgActor->shape.rot.y;
            this->unk_398 = bgActor->world.pos;
            return true;
        }
        bgActor = bgActor->next;
    }

    return false;
}

s32 func_80B763C4(EnTruMt* this, GlobalContext* globalCtx) {
    Actor* foundActor;
    Actor* actor = NULL;

    while (true) {
        foundActor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_TRU_MT);

        if (foundActor == NULL) {
            break;
        }

        if ((EnTruMt*)foundActor != this) {
            return true;
        }

        foundActor = foundActor->next;
        if (foundActor == NULL) {
            break;
        }
        actor = foundActor;
    };

    return false;
}

void func_80B76440(EnTruMt* this, GlobalContext* globalCtx) {
    if (func_80B76368(this, globalCtx)) {
        s16 temp_v1 = this->unk_394 - Math_Vec3f_Yaw(&this->unk_398, &this->actor.world.pos);

        if ((temp_v1 <= -0x2000) || (temp_v1 >= 0x2000)) {
            Math_ApproachF(&this->actor.speedXZ, 7.0f, 0.2f, 1.0f);
        } else if (this->actor.xzDistToPlayer < 300.0f) {
            Math_ApproachF(&this->actor.speedXZ, 7.0f, 0.2f, 1.0f);
        } else if (this->actor.xzDistToPlayer > 500.0f) {
            Math_ApproachF(&this->actor.speedXZ, 2.5f, 0.2f, 1.0f);
        } else {
            Math_ApproachF(&this->actor.speedXZ, 4.0f, 0.2f, 1.0f);
        }
    }
}

f32 func_80B76540(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    s32 pad;
    Vec3f sp20;

    if (path != NULL) {
        Vec3s* temp_v1 = Lib_SegmentedToVirtual(path->points);

        temp_v1 = &temp_v1[arg1];
        sp20.x = temp_v1->x;
        sp20.y = temp_v1->y;
        sp20.z = temp_v1->z;
    }
    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);

    return sp20.y - arg2->y;
}

s32 func_80B76600(EnTruMt* this, Path* path, s32 arg2) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 idx = arg2;
    s32 sp50 = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[idx]);

    if (idx == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if (idx == (sp58 - 1)) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[idx + 1].x - sp5C[idx - 1].x;
        phi_f14 = sp5C[idx + 1].z - sp5C[idx - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);
    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = true;
    }

    return sp50;
}

void func_80B7679C(EnTruMt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;

    Math_SmoothStepToS(&this->unk_34A, (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - 0x4000, 4, 0x38E0, 1);
    this->unk_34A = CLAMP(this->unk_34A, -0x38E0, 0x38E0);

    sp40 = player->actor.world.pos;
    sp40.y = player->bodyPartsPos[7].y + 3.0f;

    sp34 = this->actor.world.pos;
    sp34.y += 30.0f;

    Math_SmoothStepToS(&this->unk_348, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x1C70, 1);
    this->unk_348 = CLAMP(this->unk_348, -0x1C70, 0x1C70);
}

s32 func_80B768F0(EnTruMt* this, GlobalContext* globalCtx) {
    if (this->unk_328 & 0x10) {
        func_80B7679C(this, globalCtx);
    }
    return true;
}

void func_80B76924(EnTruMt* this) {
    this->unk_38E.z = Math_SinS(this->unk_388) * 30.0f * (0x10000 / 360.0f);
    this->unk_388 += 0x400;
}

void func_80B76980(EnTruMt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (gSaveContext.unk_3F3C >= 10) {
        Message_StartTextbox(globalCtx, 0x87F, &this->actor);
        gSaveContext.eventInf[3] |= 0x40;
        gSaveContext.eventInf[4] |= 1;
        player->stateFlags3 &= ~0x400;
        this->actor.speedXZ = 0.0f;
        this->actionFunc = func_80B76BB8;
    } else if (gSaveContext.eventInf[4] & 1) {
        u32 score = gSaveContext.minigameScore;

        if (((gSaveContext.save.unk_EE8 & 0xFFFF0000) >> 0x10) < score) {
            gSaveContext.save.unk_EE8 =
                ((gSaveContext.minigameScore & 0xFFFF) << 0x10) | (gSaveContext.save.unk_EE8 & 0xFFFF);
            gSaveContext.eventInf[3] |= 0x80;
        }
    }
}

void func_80B76A64(EnTruMt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3s sp34;

    func_80B76924(this);
    func_80B76980(this, globalCtx);
    player->stateFlags3 |= 0x400;

    if (this->path != NULL) {
        func_80B76540(this->path, this->unk_36C, &this->actor.world.pos, &sp34);
        Math_SmoothStepToS(&this->actor.world.rot.y, sp34.y, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Math_SmoothStepToS(&this->actor.shape.rot.x, sp34.x, 4, 0x3E8, 1);

        this->actor.world.rot.x = -this->actor.shape.rot.x;
        this->actor.shape.rot.z = CLAMP(this->actor.world.rot.y, -0x1770, 0x1770);
        this->actor.world.rot.z = this->actor.shape.rot.z;

        if (func_80B76600(this, this->path, this->unk_36C)) {
            if (this->unk_36C >= (this->path->count - 1)) {
                this->actionFunc = func_80B76C38;
                this->actor.speedXZ = 0.0f;
                return;
            }
            this->unk_36C++;
        }
        func_80B76440(this, globalCtx);
    }
}

void func_80B76BB8(EnTruMt* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            globalCtx->nextEntranceIndex = 0xA810;
            globalCtx->unk_1887F = 3;
            gSaveContext.nextTransition = 3;
            globalCtx->sceneLoadFlag = 0x14;
        }
    }
}

void func_80B76C38(EnTruMt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80B76924(this);
    func_80B76980(this, globalCtx);
    player->stateFlags3 |= 0x400;
}

void EnTruMt_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTruMt* this = THIS;

    if (!(gSaveContext.eventInf[3] & 0x20)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80B763C4(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_tru_Skel_01AA60, NULL, this->jointTable, this->morphTable,
                       OBJECT_TRU_LIMB_MAX);

    Collider_InitSphere(globalCtx, &this->collider);
    Collider_SetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);

    this->collider.dim.worldSphere.radius = 22;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->path = SubS_GetPathByIndex(globalCtx, ENTRUMT_GET_FF(&this->actor), 0x3F);
    this->actor.targetMode = 0;

    Actor_SetScale(&this->actor, 0.008f);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->unk_328 = 0;
    this->actor.room = -1;
    this->path = SubS_GetPathByIndex(globalCtx, ENTRUMT_GET_FC00(&this->actor), 0x3F);
    func_80B76030(&this->skelAnime, 14);
    this->actionFunc = func_80B76A64;
}

void EnTruMt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTruMt* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

void EnTruMt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTruMt* this = THIS;

    func_80B768F0(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);

    this->actionFunc(this, globalCtx);

    func_80B76110(this);
    Actor_SetFocus(&this->actor, 34.0f);

    if (!(gSaveContext.eventInf[4] & 1)) {
        func_80B761FC(this, globalCtx);
    }

    Actor_MoveWithoutGravity(&this->actor);
}

void func_80B76ED4(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4) {
    Vec3f sp7C;
    Vec3f sp70 = gZeroVec3f;
    Vec3s sp68;
    MtxF sp28;

    Matrix_MultiplyVector3fByState(&sp70, &sp7C);
    Matrix_CopyCurrentState(&sp28);
    func_8018219C(&sp28, &sp68, 0);

    *arg2 = sp7C;

    if (arg4 != 0) {
        sp68.x += arg0;
        sp68.y += arg1;
        Math_SmoothStepToS(&arg3->x, sp68.x, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->y, sp68.y, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->z, sp68.z, 4, 0x1FFE, 1);
    } else {
        arg3->x = sp68.x;
        arg3->y = sp68.y;
        arg3->z = sp68.z;
    }
}

s32 EnTruMt_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnTruMt* this = THIS;

    if (limbIndex == OBJECT_TRU_LIMB_15) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_35C);
    }

    if (limbIndex == OBJECT_TRU_LIMB_15) {
        Matrix_MultiplyVector3fByState(&D_80B7765C, &this->unk_350);
    }
    return false;
}

void EnTruMt_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnTruMt* this = THIS;
    MtxF* sp54;
    s32 phi_v0;

    if (limbIndex == OBJECT_TRU_LIMB_15) {
        if (this->unk_328 & 0x10) {
            phi_v0 = 1;
        } else {
            phi_v0 = 0;
        }
        func_80B76ED4(this->unk_348, this->unk_34A, &this->unk_33C, &this->unk_336, phi_v0);
        Matrix_InsertTranslation(this->unk_33C.x, this->unk_33C.y, this->unk_33C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_336.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_336.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_336.z, MTXMODE_APPLY);
    }

    if (limbIndex == OBJECT_TRU_LIMB_0E) {
        func_8012C28C(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_MultiplyVector3fByState(&D_80B77668, &this->unk_370);
        Matrix_InsertTranslation(this->unk_370.x, this->unk_370.y, this->unk_370.z, MTXMODE_NEW);
        Matrix_RotateY(BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx))), MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_38E.z, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_38E.x, MTXMODE_APPLY);
        Matrix_Scale(0.008f, 0.008f, 0.008f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_tru_DL_0004C8);

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        sp54 = Matrix_GetCurrentState();
        if ((this->actor.child == NULL) || (this->actor.child->update == NULL)) {
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_JC_MATO, sp54->wx, sp54->wy,
                               sp54->wz, this->unk_38E.x, BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx))),
                               this->unk_38E.z, -1);
        } else if (!((EnJcMato*)this->actor.child)->hitFlag) {
            this->actor.child->world.pos.x = sp54->wx;
            this->actor.child->world.pos.y = sp54->wy;
            this->actor.child->world.pos.z = sp54->wz;

            this->actor.child->world.rot = this->unk_38E;
            this->actor.child->world.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)));

            this->actor.child->shape.rot = this->actor.child->world.rot;
        }
    }
}

void EnTruMt_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnTruMt* this = THIS;

    if (limbIndex == OBJECT_TRU_LIMB_15) {
        Matrix_InsertTranslation(this->unk_33C.x, this->unk_33C.y, this->unk_33C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_336.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_336.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_336.z, MTXMODE_APPLY);
    }
}

void EnTruMt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTruMt* this = THIS;
    TexturePtr sp48[] = {
        object_tru_Tex_018FA0,
        object_tru_Tex_0197A0,
        object_tru_Tex_019FA0,
    };

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sp48[this->unk_34C]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sp48[this->unk_34C]));

    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnTruMt_OverrideLimbDraw, EnTruMt_PostLimbDraw,
                                   EnTruMt_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
