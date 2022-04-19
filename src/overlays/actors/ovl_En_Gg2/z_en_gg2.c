/*
 * File: z_en_gg2.c
 * Overlay: ovl_En_Gg2
 * Description: Darmani's Ghost (2)
 */

#include "z_en_gg2.h"
#include "objects/object_gg/object_gg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80)

#define THIS ((EnGg2*)thisx)

void EnGg2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B3AE60(EnGg2* this, GlobalContext* globalCtx);
void func_80B3AFB0(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B05C(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B0A0(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B120(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B21C(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B294(EnGg2* this, GlobalContext* globalCtx);
void func_80B3B5D4(EnGg2* this, GlobalContext* globalCtx);
s32 func_80B3B648(EnGg2* this, Path* path, s32 arg2_);
f32 func_80B3B7E4(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3);

const ActorInit En_Gg2_InitVars = {
    ACTOR_EN_GG2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GG,
    sizeof(EnGg2),
    (ActorFunc)EnGg2_Init,
    (ActorFunc)EnGg2_Destroy,
    (ActorFunc)EnGg2_Update,
    (ActorFunc)EnGg2_Draw,
};

AnimationInfo D_80B3BF00[] = {
    { &object_gg_Anim_00F578, 1.0f, 0.0f, 0.0f, 0, -10.0f }, { &object_gg_Anim_00D528, 1.0f, 0.0f, 0.0f, 2, -10.0f },
    { &object_gg_Anim_00D174, 1.0f, 0.0f, 0.0f, 2, -10.0f }, { &object_gg_Anim_00ECC0, 1.0f, 0.0f, 0.0f, 2, -10.0f },
    { &object_gg_Anim_00BAF0, 1.0f, 0.0f, 0.0f, 0, -10.0f }, { &object_gg_Anim_00AF40, 1.0f, 0.0f, 0.0f, 0, -10.0f },
    { &object_gg_Anim_00F578, 1.0f, 0.0f, 0.0f, 0, -10.0f }, { &object_gg_Anim_00AF40, 1.0f, 0.0f, 0.0f, 0, -10.0f },
    { &object_gg_Anim_00F578, 1.0f, 0.0f, 0.0f, 0, -10.0f }, { &object_gg_Anim_0100C8, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_gg_Anim_00CDA0, 1.0f, 0.0f, 0.0f, 0, 0.0f },   { &object_gg_Anim_00B560, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_gg_Anim_00A4B4, 1.0f, 0.0f, 0.0f, 2, 0.0f },   { &object_gg_Anim_00E86C, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_gg_Anim_00D99C, 1.0f, 0.0f, 0.0f, 2, 0.0f },   { &object_gg_Anim_00E2A4, 1.0f, 0.0f, 0.0f, 0, 0.0f },
};

Color_RGBA8 D_80B3C080 = { 255, 255, 255, 255 };
Color_RGBA8 D_80B3C084 = { 255, 150, 0, 255 };

Vec3f D_80B3C088 = { 0.0f, 0.0f, 0.0f };
Vec3f D_80B3C094 = { 0.0f, 0.0f, 0.0f };
Vec3f D_80B3C0A0 = { 1000.0f, 0.0f, 0.0f };

TexturePtr D_80B3C0AC[] = {
    object_gg_Tex_009260,
    object_gg_Tex_009660,
    object_gg_Tex_009A60,
    object_gg_Tex_009E60,
};

void func_80B3AC50(EnGg2* this) {
    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = this->actor.world.pos.y + 80.0f;
    this->actor.focus.pos.z = this->actor.world.pos.z;

    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
}

s32 func_80B3AC94(EnGg2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;
    s16 pitch;

    sp40 = player->actor.world.pos;
    sp40.y = player->bodyPartsPos[7].y + 3.0f;

    sp34 = this->actor.world.pos;
    sp34.y += 70.0f;

    pitch = Math_Vec3f_Pitch(&sp34, &sp40);

    if ((this->actor.xzDistToPlayer < 250.0f) && (this->actor.xzDistToPlayer > 50.0f) &&
        CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_80)) {
        Math_SmoothStepToS(&this->unk_2F4, pitch, 4, 0x2AA8, 1);
    } else {
        Math_SmoothStepToS(&this->unk_2F4, 0, 4, 0x2AA8, 1);
    }

    this->unk_2F4 = CLAMP(this->unk_2F4, 0, 0x1C70);
    return true;
}

void func_80B3ADD8(EnGg2* this) {
    s16 temp_v0 = this->unk_2EC - 1;

    if (temp_v0 >= 3) {
        this->unk_2EA = 0;
        this->unk_2EC = temp_v0;
    } else if (temp_v0 == 0) {
        this->unk_2EA = 2;
        this->unk_2EC = (s32)(Rand_ZeroOne() * 60.0f) + 20;
    } else {
        this->unk_2EA = 1;
        this->unk_2EC = temp_v0;
    }
}

void func_80B3AE60(EnGg2* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(D_80B3BF00[this->unk_2EE].animation);

    if (curFrame == lastFrame) {
        switch (this->unk_2EE) {
            case 0:
                this->unk_2EE = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 1);
                this->actionFunc = func_80B3B0A0;
                break;

            case 1:
            case 8:
                this->unk_2EE = 5;
                this->actor.flags &= ~ACTOR_FLAG_1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 5);
                this->actionFunc = func_80B3B120;
                break;

            case 5:
                this->unk_2EE = 6;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 0);
                this->actionFunc = func_80B3B21C;
                break;

            case 6:
                this->unk_2EE = 7;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 5);
                this->actionFunc = func_80B3B294;
                break;

            default:
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 0);
                this->actionFunc = func_80B3AFB0;
                break;
        }
    }
}

void func_80B3AFB0(EnGg2* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2F0 = 1;
        this->actionFunc = func_80B3AE60;
    } else if ((this->actor.xzDistToPlayer < 100.0f) && (this->actor.xzDistToPlayer > 50.0f) &&
               CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_80)) {
        func_800B863C(&this->actor, globalCtx);
        this->actor.textId = 0xCE4;
    }
}

void func_80B3B05C(EnGg2* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 100.0f) && CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_80)) {
        this->actionFunc = func_80B3B5D4;
    }
}

void func_80B3B0A0(EnGg2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->unk_2F0 = 0;
        this->actionFunc = func_80B3B5D4;
    }
}

void func_80B3B120(EnGg2* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    if (this->unk_1D8 != NULL) {
        func_80B3B7E4(this->unk_1D8, this->unk_1DC, &this->actor.world.pos, &sp30);
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Math_SmoothStepToS(&this->actor.shape.rot.x, sp30.x, 4, 0x3E8, 1);
        this->actor.world.rot.x = -this->actor.shape.rot.x;
        if (func_80B3B648(this, this->unk_1D8, this->unk_1DC) != 0) {
            if (this->unk_1DC >= (this->unk_1D8->count - 2)) {
                this->actionFunc = func_80B3AE60;
                this->actor.speedXZ = 0.0f;
            } else {
                this->unk_1DC++;
            }
        }
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 1.0f);
    }
}

void func_80B3B21C(EnGg2* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    if ((this->actor.xzDistToPlayer < 100.0f) && CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_80)) {
        this->unk_2E4 = ActorCutscene_GetAdditionalCutscene(this->unk_2E4);
        this->actionFunc = func_80B3B5D4;
    }
}

void func_80B3B294(EnGg2* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    if (this->unk_2F1 == 0) {
        if (globalCtx->sceneNum == SCENE_11GORONNOSATO) {
            gSaveContext.save.weekEventReg[20] |= 4;
            gSaveContext.save.weekEventReg[20] &= (u8)~8;
            gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
        } else if (globalCtx->sceneNum == SCENE_17SETUGEN) {
            gSaveContext.save.weekEventReg[20] &= (u8)~4;
            gSaveContext.save.weekEventReg[20] |= 8;
            gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
        } else if (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA) {
            gSaveContext.save.weekEventReg[20] &= (u8)~4;
            gSaveContext.save.weekEventReg[20] &= (u8)~8;
            gSaveContext.save.weekEventReg[20] |= 0x10;
        }

        if (this->unk_1D8 != NULL) {
            func_80B3B7E4(this->unk_1D8, this->unk_1DC, &this->actor.world.pos, &sp30);
            Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 4, 0x3E8, 1);
            this->actor.shape.rot.y = this->actor.world.rot.y;
            Math_SmoothStepToS(&this->actor.shape.rot.x, sp30.x, 4, 0x3E8, 1);
            this->actor.world.rot.x = -this->actor.shape.rot.x;

            if (func_80B3B648(this, this->unk_1D8, this->unk_1DC)) {
                if (this->unk_1DC < (this->unk_1D8->count - 1)) {
                    this->unk_1DC++;
                } else {
                    this->unk_2F1 = 1;
                    if (globalCtx->sceneNum == SCENE_11GORONNOSATO) {
                        gSaveContext.save.weekEventReg[20] |= 4;
                        gSaveContext.save.weekEventReg[20] &= (u8)~8;
                        gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
                    } else if (globalCtx->sceneNum == SCENE_17SETUGEN) {
                        gSaveContext.save.weekEventReg[20] &= (u8)~4;
                        gSaveContext.save.weekEventReg[20] |= 8;
                        gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
                    } else if (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA) {
                        gSaveContext.save.weekEventReg[20] &= (u8)~4;
                        gSaveContext.save.weekEventReg[20] &= (u8)~8;
                        gSaveContext.save.weekEventReg[20] |= 0x10;
                    }
                }
            }
        }
    }
    Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 1.0f);
}

void func_80B3B4B0(EnGg2* this, GlobalContext* globalCtx) {
    Vec3f sp64;
    Color_RGBA8 sp60 = D_80B3C080;
    Color_RGBA8 sp5C = D_80B3C084;
    s32 i;

    for (i = 0; i < 5; i++) {
        sp64.x = (Rand_Centered() * 50.0f) + this->unk_304.x;
        sp64.y = this->unk_304.y;
        sp64.z = (Rand_Centered() * 50.0f) + this->unk_304.z;
        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp64, &D_80B3C088, &D_80B3C094, &sp60, &sp5C, 3000, 40);
    }
}

void func_80B3B5D4(EnGg2* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_2E4)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2E4, &this->actor);
        this->actionFunc = func_80B3AE60;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk_2E4);
    }
}

s32 func_80B3B648(EnGg2* this, Path* path, s32 arg2_) {
    Vec3s* points = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 arg2 = arg2_;
    s32 ret = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &points[arg2]);

    if (arg2 == 0) {
        phi_f12 = points[1].x - points[0].x;
        phi_f14 = points[1].z - points[0].z;
    } else if ((sp58 - 1) == arg2) {
        phi_f12 = points[sp58 - 1].x - points[sp58 - 2].x;
        phi_f14 = points[sp58 - 1].z - points[sp58 - 2].z;
    } else {
        phi_f12 = points[arg2 + 1].x - points[arg2 - 1].x;
        phi_f14 = points[arg2 + 1].z - points[arg2 - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }
    return ret;
}

f32 func_80B3B7E4(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    Vec3s* points;
    Vec3f sp20;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        sp20.x = points->x;
        sp20.y = points->y;
        sp20.z = points->z;
    }

    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);
    return sp20.y - arg2->y;
}

void func_80B3B8A4(EnGg2* this) {
    f32 sp1C;

    if ((this->unk_2EE != 5) && (this->unk_2EE != 7)) {
        this->unk_2F2 += 0x62C;
        sp1C = 1100.0f;
    } else {
        this->unk_2F2 += 0x7BC;
        sp1C = 950.0f;
    }

    this->actor.shape.yOffset = Math_SinS(this->unk_2F2) * sp1C;
    this->actor.shape.shadowScale = 30.0f - (Math_SinS(this->unk_2F2) * 5.0f);
    this->unk_2F6 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
}

void EnGg2_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnGg2* this = THIS;

    if (INV_CONTENT(ITEM_MASK_GORON) == ITEM_MASK_GORON) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (gSaveContext.save.weekEventReg[91] & 0x10) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.bgCheckFlags |= 0x400;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_gg_Skel_00F6C0, &object_gg_Anim_00F578, this->jointTable,
                       this->morphTable, 20);
    this->unk_1D8 = SubS_GetPathByIndex(globalCtx, ENGG2_GET_FC00(&this->actor), 0x3F);
    this->actor.flags &= ~ACTOR_FLAG_80;
    this->unk_2F0 = 0;
    this->unk_2F1 = 0;
    this->unk_2F2 = 0;
    this->unk_2F4 = 0;
    this->unk_2F6 = 0;
    this->unk_2E4 = this->actor.cutscene;
    this->unk_2EC = 20;
    this->unk_2EA = 0;

    if (globalCtx->sceneNum == SCENE_11GORONNOSATO) {
        gSaveContext.save.weekEventReg[20] &= (u8)~4;
        gSaveContext.save.weekEventReg[20] &= (u8)~8;
        gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
        this->unk_2EE = 0;
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 0);
        this->actionFunc = func_80B3AFB0;
    } else if (globalCtx->sceneNum == SCENE_17SETUGEN) {
        if ((gSaveContext.save.weekEventReg[20] & 4) && !(gSaveContext.save.weekEventReg[20] & 8) &&
            !(gSaveContext.save.weekEventReg[20] & 0x10)) {
            gSaveContext.save.weekEventReg[20] &= (u8)~4;
            this->unk_2EE = 8;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 0);
            this->actionFunc = func_80B3B05C;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA) {
        if (!(gSaveContext.save.weekEventReg[20] & 4) && (gSaveContext.save.weekEventReg[20] & 8) &&
            !(gSaveContext.save.weekEventReg[20] & 0x10)) {
            gSaveContext.save.weekEventReg[20] &= (u8)~8;
            this->unk_2EE = 8;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80B3BF00, 0);
            this->actionFunc = func_80B3B05C;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        gSaveContext.save.weekEventReg[20] &= (u8)~4;
        gSaveContext.save.weekEventReg[20] &= (u8)~8;
        gSaveContext.save.weekEventReg[20] &= (u8)~0x10;
        Actor_MarkForDeath(&this->actor);
    }
}

void EnGg2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnGg2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGg2* this = THIS;

    if (globalCtx->actorCtx.unk4 == 100) {
        this->actor.flags |= ACTOR_FLAG_80;
        this->actor.flags |= ACTOR_FLAG_1;
        if ((this->unk_2EE == 5) && (this->unk_2EE == 7)) {
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
    } else {
        this->actor.flags &= ~ACTOR_FLAG_80;
        this->actor.flags &= ~ACTOR_FLAG_1;
    }

    this->actionFunc(this, globalCtx);

    func_80B3AC50(this);
    func_80B3AC94(this, globalCtx);
    Actor_MoveWithoutGravity(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    func_80B3B8A4(this);
    func_800E9250(globalCtx, &this->actor, &this->unk_1E0, &this->unk_1E6, this->actor.focus.pos);

    if ((this->unk_2EE == 5) || (this->unk_2EE == 7)) {
        func_800B9010(&this->actor, NA_SE_EN_SHARP_FLOAT - SFX_FLAG);
        if ((globalCtx->actorCtx.unk4 == 100) && ((globalCtx->state.frames % 4) == 0)) {
            func_80B3B4B0(this, globalCtx);
        }
    }

    func_80B3ADD8(this);
}

s32 func_80B3BD44(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnGg2* this = THIS;

    if ((this->unk_2EE != 5) && (this->unk_2EE != 7)) {
        if (limbIndex == 1) {
            Matrix_RotateY(this->unk_2F6, MTXMODE_APPLY);
        }

        if (limbIndex == 2) {
            Matrix_InsertZRotation_s(this->unk_2F4, MTXMODE_APPLY);
        }
    }
    return false;
}

void func_80B3BDC0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnGg2* this = THIS;

    if (limbIndex == 4) {
        Matrix_MultiplyVector3fByState(&D_80B3C0A0, &this->unk_304);
    }
}

void EnGg2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGg2* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_80) || (this->unk_2F0 == 1)) {
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B3C0AC[this->unk_2EA]));

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_80B3BD44, func_80B3BDC0, &this->actor, POLY_XLU_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
