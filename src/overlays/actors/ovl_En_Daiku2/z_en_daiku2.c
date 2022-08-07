/*
 * File: z_en_daiku2.c
 * Overlay: ovl_En_Daiku2
 * Description: Milk Road Carpenter
 */

#include "z_en_daiku2.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/object_daiku/object_daiku.h"
#include "objects/object_bombiwa/object_bombiwa.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDaiku2*)thisx)

void EnDaiku2_Init(Actor* thisx, PlayState* play);
void EnDaiku2_Destroy(Actor* thisx, PlayState* play);
void EnDaiku2_Update(Actor* thisx, PlayState* play);
void EnDaiku2_Draw(Actor* thisx, PlayState* play);

void func_80BE65B4(EnDaiku2* this, PlayState* play);
void func_80BE66E4(EnDaiku2* this, PlayState* play);
void func_80BE6B40(EnDaiku2* this, PlayState* play);
void func_80BE6BC0(EnDaiku2* this, PlayState* play);
void func_80BE6CFC(EnDaiku2* this);
void func_80BE6D40(EnDaiku2* this, PlayState* play);
void func_80BE6EB0(EnDaiku2* this);
void func_80BE6EF0(EnDaiku2* this, PlayState* play);
void func_80BE7600(EnDaiku2* this, PlayState* play);
void func_80BE71A0(EnDaiku2* this);
void func_80BE71D8(EnDaiku2* this, PlayState* play);
void func_80BE7504(EnDaiku2* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5);
void func_80BE7718(EnDaiku2* this, PlayState* play);

const ActorInit En_Daiku2_InitVars = {
    ACTOR_EN_DAIKU2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnDaiku2),
    (ActorFunc)EnDaiku2_Init,
    (ActorFunc)EnDaiku2_Destroy,
    (ActorFunc)EnDaiku2_Update,
    (ActorFunc)EnDaiku2_Draw,
};

static u16 sTextIds[] = {
    0x32CB, 0x32CC, 0x32CD, 0x32CE, 0x32CF, 0x32D0, 0x32D1, 0x32D2,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

void func_80BE61D0(EnDaiku2* this) {
    if ((this->unk_27A != -1) && (this->unk_258 != 0)) {
        if (!SubS_CopyPointFromPath(this->unk_258, this->unk_25C, &this->unk_268)) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnDaiku2_Init(Actor* thisx, PlayState* play) {
    EnDaiku2* this = THIS;
    s32 day = gSaveContext.save.day;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_002FA0, this->jointTable,
                       this->morphTable, 17);
    this->actor.targetMode = 0;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->unk_278 = ENDAIKU2_GET_7F(&this->actor);
    this->unk_27A = ENDAIKU2_GET_1F80(&this->actor);
    this->unk_258 = SubS_GetPathByIndex(play, this->unk_27A, 0x3F);
    this->unk_280 = ENDAIKU2_GET_8000(&this->actor);
    Actor_SetScale(&this->actor, 0.01f);
    if (!this->unk_280) {
        if (day == 3) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        if (this->unk_278 == ENDAIKU2_GET_7F_127) {
            this->unk_278 = ENDAIKU2_GET_7F_MINUS1;
        } else if (Flags_GetSwitch(play, this->unk_278)) {
            this->unk_25C = this->unk_258->count - 1;
            func_80BE61D0(this);
            Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_268);
        }
    } else if (day != 3) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.gravity = -3.0f;
    Math_Vec3f_Copy(&this->unk_268, &this->actor.world.pos);
    func_80BE65B4(this, play);
}

void EnDaiku2_Destroy(Actor* thisx, PlayState* play) {
    EnDaiku2* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80BE6408(EnDaiku2* this, s32 arg1) {
    static AnimationHeader* sAnimations[] = {
        &object_daiku_Anim_002FA0, &object_daiku_Anim_00ACD0, &object_daiku_Anim_00C92C, &object_daiku_Anim_000C44,
        &object_daiku_Anim_00C234, &object_daiku_Anim_000600, &object_daiku_Anim_001114, &object_daiku_Anim_00B690,
        &object_daiku_Anim_001A24, &object_daiku_Anim_002134, &object_daiku_Anim_00D328,
    };
    static u8 D_80BE7958[] = {
        ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP,
        ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP,
    };
    f32 sp34 = 1.0f;

    this->unk_276 = arg1;
    this->unk_284 = Animation_GetLastFrame(sAnimations[this->unk_276]);
    if (this->unk_276 == 3) {
        sp34 = 2.0f;
    }
    Animation_Change(&this->skelAnime, sAnimations[this->unk_276], sp34, 0.0f, this->unk_284, D_80BE7958[this->unk_276],
                     -4.0f);
}

s32 func_80BE64C0(EnDaiku2* this, PlayState* play) {
    EnBom* bomb;
    Vec3f sp30;

    Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    bomb = (EnBom*)Actor_FindNearby(play, &this->actor, -1, ACTORCAT_EXPLOSIVES, BREG(7) + 240.0f);
    Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
    if ((this->unk_278 >= ENDAIKU2_GET_7F_0) && !Flags_GetSwitch(play, this->unk_278) && (bomb != NULL) &&
        (bomb->actor.id == ACTOR_EN_BOM)) {
        if (!bomb->isPowderKeg) {
            this->actor.textId = 0x32D3;
        } else {
            this->actor.textId = 0x32D4;
        }

        return true;
    }

    return false;
}

void func_80BE65B4(EnDaiku2* this, PlayState* play) {
    switch (gSaveContext.save.day - 1) {
        case 0:
            this->unk_28A = 0;
            if (gSaveContext.save.weekEventReg[64] & 2) {
                this->unk_28A = 6;
            }
            func_80BE6408(this, 8);
            break;

        case 1:
            this->unk_28A = 2;
            if (gSaveContext.save.weekEventReg[64] & 4) {
                this->unk_28A = 7;
            }
            func_80BE6408(this, 8);
            break;

        case 2:
            this->unk_28A = 4;
            this->unk_264 = 1.0f;
            func_80BE6408(this, 10);
            break;
    }

    this->unk_264 = 1.0f;
    if ((this->unk_278 >= ENDAIKU2_GET_7F_0) && Flags_GetSwitch(play, this->unk_278)) {
        this->unk_28A = 5;
        if (this->unk_276 != 10) {
            func_80BE6408(this, 10);
        }
    }

    this->unk_288 = 0;
    this->actionFunc = func_80BE66E4;
}

void func_80BE66E4(EnDaiku2* this, PlayState* play) {
    f32 sp9C = this->skelAnime.curFrame;
    s32 sp98 = gSaveContext.save.day - 1;
    s32 i;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    s32 pad[2];
    s16 temp_v0;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0x0);
    if (sp98 != 2) {
        if ((this->unk_278 >= ENDAIKU2_GET_7F_0) && Flags_GetSwitch(play, this->unk_278)) {
            this->unk_28A = 5;
            if (this->unk_276 != 10) {
                func_80BE6408(this, 10);
            }
        }
    }

    this->actor.textId = sTextIds[this->unk_28A];

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BE6B40(this, play);
        return;
    }

    if ((this->unk_28A != 5) && (sp98 != 2) && func_80BE64C0(this, play)) {
        func_80BE6CFC(this);
        return;
    }

    func_800B8614(&this->actor, play, 80.0f);
    if ((this->unk_276 == 8) && Animation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ROCK_BROKEN);

        for (i = 0; i < 10; i++) {
            Math_Vec3f_Copy(&sp70, &this->actor.world.pos);

            sp70.x += Math_SinS(this->actor.world.rot.y) * 70.0f;
            sp70.y += 40.0f;
            sp70.z += Math_CosS(this->actor.world.rot.y) * 70.0f;

            sp70.x += randPlusMinusPoint5Scaled(5.0f);
            sp70.y += randPlusMinusPoint5Scaled(5.0f);
            sp70.z += randPlusMinusPoint5Scaled(5.0f);

            sp88.y = -1.0f;

            sp7C.x = (Rand_ZeroOne() - 0.5f) * 4.0f;
            sp7C.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
            sp7C.z = (Rand_ZeroOne() - 0.5f) * 4.0f;

            func_80BE7504(this, &sp70, &sp7C, &sp88, 0.01f - (Rand_ZeroFloat(1.0f) * 0.005f), 40);
        }
    }

    temp_v0 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.home.rot.y));
    if (temp_v0 > 0x2890) {
        if (sp98 != 2) {
            if ((this->unk_276 == 5) || (this->unk_276 == 9)) {
                func_80BE6408(this, 10);
            } else if ((this->unk_276 == 10) && (this->unk_284 <= sp9C)) {
                this->unk_284 = Animation_GetLastFrame(&object_daiku_Anim_002134);
                Animation_Change(&this->skelAnime, &object_daiku_Anim_002134, -1.0f, this->unk_284, 0.0f, ANIMMODE_ONCE,
                                 -4.0f);
                this->unk_276 = 11;
            } else if ((this->unk_276 == 11) && (sp9C <= 0.0f)) {
                func_80BE6408(this, 8);
            }
        }
    } else if (sp98 != 2) {
        if ((this->unk_276 != 9) && (this->unk_276 != 10)) {
            func_80BE6408(this, 9);
        } else if ((this->unk_276 == 9) && (this->unk_284 <= sp9C)) {
            func_80BE6408(this, 10);
        }
    }
}

void func_80BE6B40(EnDaiku2* this, PlayState* play) {
    s32 day = gSaveContext.save.day;

    this->unk_288 = 1;
    if ((day != 3) && Flags_GetSwitch(play, this->unk_278)) {
        this->actionFunc = func_80BE6BC0;
    } else {
        func_80BE6408(this, 5);
        this->actionFunc = func_80BE6BC0;
    }
}

void func_80BE6BC0(EnDaiku2* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 0xBB8, 0x0);
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        s32 day = gSaveContext.save.day - 1;

        func_801477B4(play);

        if (this->unk_288 == 2) {
            this->actionFunc = func_80BE6D40;
        } else if (this->unk_288 == 3) {
            this->actionFunc = func_80BE6EF0;
        } else if ((this->unk_28A == 0) || (this->unk_28A == 2)) {
            this->unk_28A++;
            func_80151938(play, sTextIds[this->unk_28A]);
        } else {
            switch (day) {
                case 0:
                    gSaveContext.save.weekEventReg[64] |= 2;
                    break;

                case 1:
                    gSaveContext.save.weekEventReg[64] |= 4;
                    break;
            }
            func_80BE65B4(this, play);
        }
    }
}

void func_80BE6CFC(EnDaiku2* this) {
    func_80BE6408(this, 3);
    this->unk_288 = 2;
    this->actionFunc = func_80BE6D40;
    this->unk_264 = 0.0f;
}

void func_80BE6D40(EnDaiku2* this, PlayState* play) {
    s32 pad[3];
    s16 sp3A = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_268);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BE6BC0;
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, sp3A, 1, 0x7D0, 0xA);
    Math_ApproachF(&this->actor.world.pos.x, this->unk_268.x, 0.5f, fabsf(Math_SinS(this->actor.world.rot.y) * 6.0f));
    Math_ApproachF(&this->actor.world.pos.z, this->unk_268.z, 0.5f, fabsf(Math_CosS(this->actor.world.rot.y) * 6.0f));

    if ((sqrtf(SQ(this->actor.world.pos.x - this->unk_268.x) + SQ(this->actor.world.pos.z - this->unk_268.z)) < 4.0f) &&
        (this->unk_258 != 0)) {
        this->unk_25C++;
        if (this->unk_25C >= this->unk_258->count) {
            func_80BE6EB0(this);
            return;
        }
        func_80BE61D0(this);
    }
    func_800B8614(&this->actor, play, 80.0f);
}

void func_80BE6EB0(EnDaiku2* this) {
    func_80BE6408(this, 2);
    this->unk_274 = 0;
    this->unk_288 = 3;
    this->actionFunc = func_80BE6EF0;
}

void func_80BE6EF0(EnDaiku2* this, PlayState* play) {
    f32 sp5C = this->skelAnime.curFrame;
    s32 pad[4];
    Vec3f sp40;
    s16 var;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BE6BC0;
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0x0);
    if (this->unk_284 <= sp5C) {
        this->unk_274 = 1;
    }

    if (this->unk_274 != 0) {
        Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_268), 1, 0x7D0,
                           0xA);
        Math_ApproachF(&this->actor.world.pos.x, this->unk_268.x, 0.5f,
                       fabsf(Math_SinS(this->actor.world.rot.y) * 4.0f));
        Math_ApproachF(&this->actor.world.pos.z, this->unk_268.z, 0.5f,
                       fabsf(Math_CosS(this->actor.world.rot.y) * 4.0f));
        if ((sqrtf(SQ(this->actor.world.pos.x - this->unk_268.x) + SQ(this->actor.world.pos.z - this->unk_268.z)) <
             4.0f) &&
            (this->unk_258 != 0)) {
            if (!func_80BE64C0(this, play)) {
                if (this->unk_276 != 3) {
                    func_80BE6408(this, 3);
                }

                if ((this->unk_278 >= ENDAIKU2_GET_7F_0) && Flags_GetSwitch(play, this->unk_278)) {
                    this->unk_28A = 5;
                    if (this->unk_276 != 10) {
                        func_80BE6408(this, 10);
                    }
                    func_80BE65B4(this, play);
                    return;
                }

                this->unk_25C--;
                if (this->unk_25C < 0) {
                    this->unk_25C = 0;
                    func_80BE71A0(this);
                    return;
                }
                func_80BE61D0(this);
            }
        } else if (func_80BE64C0(this, play)) {
            Math_Vec3f_Copy(&sp40, &this->unk_268);
            var = this->unk_25C;
            this->unk_25C++;
            if (this->unk_25C < this->unk_258->count) {
                func_80BE61D0(this);
                func_80BE6CFC(this);
                return;
            }
            this->unk_25C = var;
            Math_Vec3f_Copy(&this->unk_268, &sp40);
        }
    }
    func_800B8614(&this->actor, play, 80.0f);
}

void func_80BE71A0(EnDaiku2* this) {
    func_80BE6408(this, 9);
    this->actionFunc = func_80BE71D8;
}

void func_80BE71D8(EnDaiku2* this, PlayState* play) {
    f32 currentFrame = this->skelAnime.curFrame;

    if (func_80BE64C0(this, play)) {
        func_80BE6CFC(this);
    } else if ((this->unk_276 == 9) && (this->unk_284 <= currentFrame)) {
        func_80BE6408(this, 0);
    } else if ((this->unk_276 == 0) && (this->unk_284 <= currentFrame)) {
        func_80BE6408(this, 5);
    } else if ((this->unk_276 == 5) && (this->unk_284 <= currentFrame)) {
        func_80BE65B4(this, play);
    }
}

void EnDaiku2_Update(Actor* thisx, PlayState* play) {
    EnDaiku2* this = THIS;
    s32 pad;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetFocus(&this->actor, 65.0f);
    Actor_MoveWithGravity(&this->actor);
    Math_ApproachF(&this->unk_260, this->unk_264, 0.3f, 2.0f);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    func_80BE7600(this, play);
}

void EnDaiku2_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDaiku2* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (limbIndex == 14) {
        Matrix_Scale(this->unk_260, this->unk_260, this->unk_260, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_daiku_DL_009638);
    }

    if (limbIndex == 15) {
        gSPDisplayList(POLY_OPA_DISP++, object_daiku_DL_00A390);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnDaiku2_Draw(Actor* thisx, PlayState* play) {
    EnDaiku2* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 245, 155, 0, 255);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          EnDaiku2_PostLimbDraw, &this->actor);
    func_80BE7718(this, play);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80BE7504(EnDaiku2* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5) {
    s16 i;
    EnDaiku2Effect* effect = this->effects;

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (!effect->isEnabled) {
            effect->isEnabled = true;
            effect->unk_04 = *arg1;
            effect->unk_10 = *arg2;
            effect->unk_1C = *arg3;
            effect->unk_30 = arg4;
            effect->unk_34 = arg5;
            effect->unk_28.x = randPlusMinusPoint5Scaled(30000.0f);
            effect->unk_28.y = randPlusMinusPoint5Scaled(30000.0f);
            effect->unk_28.z = randPlusMinusPoint5Scaled(30000.0f);
            break;
        }
    }
}

void func_80BE7600(EnDaiku2* this, PlayState* play) {
    s32 i;
    EnDaiku2Effect* effect = this->effects;

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->isEnabled) {
            effect->unk_04.x += effect->unk_10.x;
            effect->unk_28.x += 0x100;
            effect->unk_28.z += 0x130;
            effect->unk_04.y += effect->unk_10.y;
            effect->unk_04.z += effect->unk_10.z;
            effect->unk_10.y += effect->unk_1C.y;
            if (effect->unk_34 != 0) {
                effect->unk_34 -= 1;
            } else {
                effect->isEnabled = false;
            }
        }
    }
}

void func_80BE7718(EnDaiku2* this, PlayState* play) {
    s32 i;
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    EnDaiku2Effect* effect = this->effects;
    s32 objectIdx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    objectIdx = Object_GetIndex(&play->objectCtx, OBJECT_BOMBIWA);
    if ((objectIdx >= 0) && Object_IsLoaded(&play->objectCtx, objectIdx)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[objectIdx].segment);

        for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
            if (effect->isEnabled) {
                Matrix_Push();
                Matrix_Translate(effect->unk_04.x, effect->unk_04.y, effect->unk_04.z, MTXMODE_NEW);
                Matrix_RotateXS(effect->unk_28.x, MTXMODE_APPLY);
                Matrix_RotateYS(effect->unk_28.y, MTXMODE_APPLY);
                Matrix_RotateZS(effect->unk_28.z, MTXMODE_APPLY);
                Matrix_Scale(effect->unk_30, effect->unk_30, effect->unk_30, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, object_bombiwa_DL_0009E0);

                Matrix_Pop();
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
