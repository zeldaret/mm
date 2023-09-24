/*
 * File: z_en_an.c
 * Overlay: ovl_En_An
 * Description: Anju
 */

#include "z_en_an.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAn*)thisx)

void EnAn_Init(Actor* thisx, PlayState* play);
void EnAn_Destroy(Actor* thisx, PlayState* play);
void EnAn_Update(Actor* thisx, PlayState* play);

void EnAn_Draw(Actor* this, PlayState* play);

// Action funcs
void func_80B577F0(EnAn* this, PlayState* play);
void func_80B578F8(EnAn* this, PlayState* play);
void func_80B57A44(EnAn* this, PlayState* play);




extern AnimationInfoS D_80B58BF4[];

#if 0
ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B58BBC = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B58BE8 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80B58BBC;
extern CollisionCheckInfoInit2 D_80B58BE8;

extern Gfx D_060111E8[];
extern FlexSkeletonHeader D_06012618;

s32 func_80B53840(EnAn* this, PlayState* play) {
    s32 ret = 0;

    if ((this->unk_214 != play->roomCtx.curRoom.num) && (play->roomCtx.status == 0) && (this->unk_3B8 == 0)) {
        this->unk_20C = SubS_GetObjectIndex(OBJECT_MSMO, play);
        this->unk_20B = SubS_GetObjectIndex(OBJECT_AN4, play);
        this->unk_20A = SubS_GetObjectIndex(OBJECT_MASK_KERFAY, play);
        this->unk_209 = SubS_GetObjectIndex(OBJECT_AN3, play);
        this->unk_208 = SubS_GetObjectIndex(OBJECT_AN2, play);
        this->actor.draw = NULL;
        this->unk_214 = play->roomCtx.curRoom.num;
        this->unk_3B8 = 1;
    }

    if (this->unk_3B8 == 0) {
        return 0;
    }

    if (((this->unk_208 >= 0) && (SubS_IsObjectLoaded(this->unk_208, play) == 0)) || ((this->unk_209 >= 0) && (SubS_IsObjectLoaded(this->unk_209, play) == 0)) || ((this->unk_20A >= 0) && (SubS_IsObjectLoaded(this->unk_20A, play) == 0)) || ((this->unk_20B >= 0) && (SubS_IsObjectLoaded(this->unk_20B, play) == 0)) || ((this->unk_20C >= 0) && (SubS_IsObjectLoaded(this->unk_20C, play) == 0))) {
        ret = 1;
    } else {
        this->actor.draw = EnAn_Draw;
        this->unk_3B8 = 0;
    }

    return ret;
}


Actor* func_80B539CC(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

Actor* func_80B53A7C(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            if (!(foundActor->params & 0x8000)) {
                break;
            }
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

EnDoor* func_80B53B3C(PlayState* play, s32 scheduleOutputResult) {
    s32 switchFlag;

    switch (scheduleOutputResult) {
        case 0x1A:
        case 0x1B:
            switchFlag = 0xD;
            break;

        case 0x21:
        case 0x22:
        case 0x25:
        case 0x26:
            switchFlag = 0xB;
            break;

        case 0x24:
            switchFlag = 0x10;
            break;

        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x23:
        case 0x27:
            switchFlag = 0xE;
            break;

        default:
            return NULL;
    }

    return SubS_FindDoor(play, switchFlag);
}

s32 func_80B53BA8(EnAn* this, PlayState* play) {
    s8 temp_a3 = this->actor.objBankIndex;
    s8 var_v1 = -1;
    s32 ret = 0;

    if ((this->unk_39C >= 0x19) && (this->unk_20B >= 0)) {
        var_v1 = this->unk_20B;
    } else if ((this->unk_39C >= 0x15) && (this->unk_209 >= 0)) {
        var_v1 = this->unk_209;
    } else if ((this->unk_39C >= 0x11) && (this->unk_208 >= 0)) {
        var_v1 = this->unk_208;
    } else if (this->unk_39C < 0x11) {
        var_v1 = temp_a3;
    }

    if (var_v1 < 0) {
        return 0;
    }

    if (var_v1 >= 0) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[var_v1].segment);
        this->unk_144.playSpeed = this->unk_368;
        ret = SkelAnime_Update(&this->unk_144);
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[temp_a3].segment);
    }

    return ret;
}

s32 func_80B53CE8(EnAn* this, PlayState* play, s32 arg2) {
    s8 temp_t1 = this->actor.objBankIndex;
    s8 var_v1 = -1;
    s32 var_t0 = 0;
    s32 var_t2 = 0;

    if ((arg2 >= 0x19) && (this->unk_20B >= 0)) {
        var_v1 = this->unk_20B;
    } else if ((arg2 >= 0x15) && (this->unk_209 >= 0)) {
        var_v1 = this->unk_209;
    } else if ((arg2 >= 0x11) && (this->unk_208 >= 0)) {
        var_v1 = this->unk_208;
    } else if (arg2 < 0x11) {
        var_v1 = temp_t1;
    }

    if (var_v1 < 0) {
        return 0;
    }

    switch (arg2) {
        case 0x1:
        case 0x2:
            if ((this->unk_39C != 1) && (this->unk_39C != 2)) {
                var_t0 = 1;
            }
            break;

        case 0x7:
        case 0x8:
            if ((this->unk_39C != 7) && (this->unk_39C != 8)) {
                var_t0 = 1;
            }
            break;

        case 0x9:
        case 0xA:
            if ((this->unk_39C != 9) && (this->unk_39C != 0xA)) {
                var_t0 = 1;
            }
            break;

        default:
            if (arg2 != this->unk_39C) {
                var_t0 = 1;
            }
            break;
    }

    if ((var_t0 != 0) && (var_v1 >= 0)) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[var_v1].segment);
        this->unk_39C = arg2;
        var_t2 = SubS_ChangeAnimationByInfoS(&this->unk_144, D_80B58BF4, arg2);
        this->unk_368 = this->unk_144.playSpeed;
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[temp_t1].segment);
    }

    return var_t2;
}

extern Vec3f D_80B58E34;

void func_80B53ED4(EnAn* this, PlayState* play) {
    f32 temp;
    s32 pad;
    Vec3f sp24;

    if (this->unk_200 == 0x19) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B58E34, &sp24);
        this->unk_190.dim.radius = 20;
        Math_Vec3f_ToVec3s(&this->unk_190.dim.pos, &sp24);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->unk_190);
    }

    temp = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->unk_190.dim.height = TRUNCF_BINANG(temp);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_190.base);
}

extern s16 D_80B58E40[];

void func_80B53F84(EnAn* this) {
    s32 var_a1 = 0;

    if (this->unk_360 & 0x100) {
        if (DECR(this->unk_38E) == 0) {
            // default case doesn't match
            switch (this->unk_38C) {
                case 0x2:
                case 0x4:
                case 0x6:
                    if ((this->unk_390 == 5) || (this->unk_390 == 2)) {
                        var_a1 = 1;
                        this->unk_390 = 5;
                    }
                    break;

                case 0x5:
                case 0x7:
                    if ((this->unk_390 == 6) || (this->unk_390 == 1)) {
                        var_a1 = 1;
                        this->unk_390 = 6;
                    }
                    break;

                case 0x8:
                    if ((this->unk_390 == 4) || (this->unk_390 == 2)) {
                        var_a1 = 1;
                        this->unk_390 = 4;
                    }
                    break;
            }

            if (var_a1 == 0) {
                if ((this->unk_390 == 4) || (this->unk_390 == 5)) {
                    this->unk_390 = 0;
                } else if (this->unk_390 == 6) {
                    this->unk_390 = 1;
                }
            }

            if (var_a1 == 0) {
                this->unk_390++;

                if (this->unk_390 >= 4) {
                    if ((this->unk_38C == 0) || (this->unk_38C == 1) || (this->unk_38C == 3)) {
                        this->unk_38E = Rand_S16Offset(0x1E, 0x1E);
                    } else {
                        this->unk_38E = 8;
                    }
                    this->unk_390 = 0;
                }
            }
        }
    }

    this->unk_392 = D_80B58E40[this->unk_38C];
}

extern Vec3f D_80B58E54;
extern Vec3s D_80B58E60;

extern Gfx D_0A000D40[];

extern Gfx D_06000378[];
extern Gfx D_06000308[];
extern Gfx D_06012478[];
extern Gfx D_06000E70[];

extern Vec3f D_80B58E68;
extern Vec3s D_80B58E74;


void func_80B54124(EnAn* this, PlayState* play, u32 arg2) {
    s32 pad;
    s8 sp53 = this->actor.objBankIndex;
    s8 temp_a2;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Push();

    switch (arg2) {
        case 0x0:
            if ((this->unk_360 & 0x800) && (this->unk_3B0 == 0)) {
                this->unk_3A8 += 1;
                this->unk_3AC -= 2;
                Gfx_SetupDL25_Xlu(play->state.gfxCtx);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(POLY_XLU_DISP++, 0x08,  Gfx_TwoTexScroll(play->state.gfxCtx, 0, this->unk_3A8, 0U, 0x10, 0x10, 1, 0U, this->unk_3AC, 0x10, 0x10));
                gSPDisplayList(POLY_XLU_DISP++, D_060111E8);

                Gfx_SetupDL25_Opa(play->state.gfxCtx);
            }
            break;

        case 0x1:
            temp_a2 = this->unk_20A;
            if ((this->unk_360 & 0x4000) && (this->unk_3B0 == 0) && (temp_a2 >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x0A, play->objectCtx.status[temp_a2].segment);

                Matrix_TranslateRotateZYX(&D_80B58E54, &D_80B58E60);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, D_0A000D40);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp53].segment);
            }
            break;
        case 0x2:
            temp_a2 = this->unk_208;
            if ((this->unk_360 & 0x1000) && (this->unk_3B0 == 0) && (temp_a2 >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[temp_a2].segment);
                gSPDisplayList(POLY_OPA_DISP++, D_06000378);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp53].segment);
            }
            break;

        case 0x3:
            temp_a2 = this->unk_209;
            if ((this->unk_360 & 0x2000) && (this->unk_3B0 == 0) && (temp_a2 >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[temp_a2].segment);
                gSPDisplayList(POLY_OPA_DISP++, D_06000308);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp53].segment);
            }
            break;

        case 0x4:
            if ((this->unk_360 & 0x8000) && (this->unk_3B0 == 0)) {
                gSPDisplayList(POLY_OPA_DISP++, D_06012478);
            }
            break;

        case 0x5:
            temp_a2 = this->unk_20C;
            if ((this->unk_3B4 != 0) && (temp_a2 >= 0)) {
                Matrix_TranslateRotateZYX(&D_80B58E68, &D_80B58E74);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[temp_a2].segment);
                gSPDisplayList(POLY_OPA_DISP++, D_06000E70);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp53].segment);
            }
            break;
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 func_80B54678(EnAn* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }

    return ret;
}

s16 func_80B546F4(EnAn* this, s32 arg1) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < arg1; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

s16 func_80B54750(EnAn* this, s32 arg1) {
    Actor* temp_v0 = this->actor.child;
    s16 csId = -1;
    s32 i;

    if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
        csId = temp_v0->csId;

        for (i = 0; i < arg1; i++) {
            csId = CutsceneManager_GetAdditionalCsId(csId);
        }
    }

    return csId;
}

s32 func_80B547C8(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;
    s16 csId = func_80B546F4(this, 0);
    s32 ret = 0;

    switch (this->unk_394) {
        case 0x0:
            ret = 0;
            if (func_80B54678(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = 1;
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
            if ((gSaveContext.save.saveInfo.weekEventReg[0x56] & 8) && (this->unk_394 == 3)) {
                CutsceneManager_Stop(csId);
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), this->actor.child);
            }
            this->unk_394++;
            ret = 1;
            break;

        case 0x7:
            CutsceneManager_Stop(csId);
            ret = 1;
            this->unk_394++;
            break;
    }

    return ret;
}
s32 func_80B5492C(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;
    s16 csId = func_80B546F4(this, 0);
    s32 var_a2 = 0;

    switch (this->unk_394) {
        case 0x0:
            var_a2 = 0;
            if (func_80B54678(this,  csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            var_a2 = 1;
            this->unk_394++;
            break;


        case 0x1:
        case 0x3:
            if (!(gSaveContext.save.saveInfo.weekEventReg[0x4B] & 0x10) && (this->unk_394 == 3)) {
                CutsceneManager_Stop(csId);
                this->unk_394 = 5;
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), this->actor.child);
            }
            this->unk_394++;
            var_a2 = 1;
            break;

        case 0x5:
            CutsceneManager_Stop(csId);
            var_a2 = 1;
            this->unk_394++;
            break;
    }
    return var_a2;
}

s32 func_80B54A94(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;
    s16 csId = func_80B54750(this, 0);
    s32 ret = 0;

    switch (this->unk_394) {
        case 0x0:
            ret = 0;
            if (func_80B54678(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        case 0x8:
        label:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), this->actor.child);
            }
            ret = 1;
            this->unk_394 += 1;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = 1;
            this->unk_394 += 1;
            break;

        case 0x9:
            CutsceneManager_Stop(csId);
            ret = 1;
            this->unk_394 += 1;
            break;
    }

    return ret;
}

s32 func_80B54BC4(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;

    if (this->unk_394 == 0) {
        func_800B7298(play, &this->actor, PLAYER_CSMODE_WAIT);
        play->nextEntrance = ENTRANCE(STOCK_POT_INN, 3);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_FADE_BLACK;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
        this->unk_394++;
    }
    return 0;
}

s32 func_80B54C5C(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;
    s32 sp20 = false;

    switch (this->unk_394) {
        case 0x0:
            func_80B53CE8(this, play, 0xD);
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
            if (Animation_OnFrame(&this->unk_144, this->unk_144.endFrame)) {
                this->unk_394++;
                sp20 = true;
            }
            break;

        case 0x2:
            func_80B53CE8(this, play, 0xE);
            this->unk_394++;
            break;
    }

    return sp20;
}

s32 func_80B54D18(Actor* thisx, PlayState* play) {
    EnAn *this = THIS;
    s32 ret = false;

    switch (this->unk_394) {
        case 0x0:
            if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) || (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20)) {
                this->unk_394++;
                goto label;
            } else {
                ret = true;
                this->unk_360 |= 0x4000;
                this->unk_394++;
            }
            break;

        case 0x1:
        label:
            this->unk_360 &= ~(0x20|0x4000);
            this->unk_360 |= 0x200;
            func_80B53CE8(this, play, 0x14);
            ret = true;
            this->unk_394++;
            break;
    }

    return ret;
}

extern s32 D_80B58718[];
extern s32 D_80B58784[];
extern s32 D_80B58808[];
extern s32 D_80B5885C[];
extern s32 D_80B58938[];
extern s32 D_80B58944[];
extern s32 D_80B5894C[];
extern s32 D_80B58954[];
extern s32 D_80B58980[];
extern s32 D_80B58988[];
extern s32 D_80B58994[];
extern s32 D_80B5899C[];
extern s32 D_80B589AC[];
extern s32 D_80B589FC[];
extern s32 D_80B58A04[];
extern s32 D_80B58A24[];
extern s32 D_80B58A3C[];
extern s32 D_80B58A44[];
extern s32 D_80B58ABC[];
extern s32 D_80B58AC4[];
extern s32 D_80B58AE8[];
extern s32 D_80B58AF4[];
extern s32 D_80B58B3C[];
extern s32 D_80B58B7C[];
extern s32 D_80B58B88[];
extern s32 D_80B58B90[];

// TODO: figure out what to do with this
#define SCHEDULE_CALC_TIME_ALT(hour, minute) SCHEDULE_CONVERT_TIME((((hour)*60.0f) + (minute)) * (0x10000 / 60 / 24.0f))

s32* func_80B54DF4(EnAn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->unk_200) {
        case 0x15:
            this->msgEventFunc = func_80B54A94;
            return D_80B58808;

        case 0x10:
            this->msgEventFunc = func_80B547C8;
            return D_80B58718;

        case 0x11:
            this->msgEventFunc = func_80B5492C;
            return D_80B58784;

        case 0xE:
            this->msgEventFunc = func_80B54C5C;
            return D_80B58954;

        case 0xC:
            return D_80B5899C;

        case 0x19:
            return D_80B58B90;

        default:
            if (player->transformation == PLAYER_FORM_DEKU) {
                switch (this->unk_200) {
                    case 0x1:
                        return D_80B58AE8;

                    case 0x28:
                    case 0x2A:
                    case 0x2B:
                    case 0x2C:
                    case 0x2D:
                    case 0x2F:
                        return D_80B58B7C;

                    case 0x3:
                        return D_80B58A24;

                    case 0x31:
                        return D_80B589FC;

                    default:
                        return D_80B58A04;
                }
            } else {
                if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
                    if (this->unk_200 == 0x31) {
                        return D_80B58B88;
                    }

                    if (this->unk_200 == 0x17) {
                        this->msgEventFunc = func_80B54BC4;
                        return D_80B589AC;
                    }

                    if (this->unk_200 == 3) {
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58B3C;
                    }

                    if (gSaveContext.save.day >= 2) {
                        return D_80B58A44;
                    }

                    //if ((gSaveContext.save.time - 0x3FFC) < 0x5883) {
                    //if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CONVERT_TIME_ALT(CLOCK_TIME(14, 18))) {
                    if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CALC_TIME_ALT(14, 18)) {
                        return D_80B58ABC;
                    }
                    return D_80B58AC4;
                }

                if ((player->transformation == PLAYER_FORM_HUMAN) && (gSaveContext.save.saveInfo.weekEventReg[0x32] & 8)) {
                    if (this->unk_200 == 0x17) {
                        this->msgEventFunc = func_80B54BC4;
                        return D_80B589AC;
                    }
                    if (this->unk_200 == 3) {
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58AF4;
                    }
                    if (gSaveContext.save.day >= 2) {
                        return D_80B58A44;
                    }
                }

                switch (this->unk_200) {
                    case 0x1:
                        return D_80B58AE8;

                    case 0x28:
                        return D_80B5894C;

                    case 0x2A:
                    case 0x2B:
                    case 0x2C:
                    case 0x2D:
                        return D_80B58980;

                    case 0x3:
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58AF4;

                    case 0x12:
                        if (gSaveContext.save.day >= 2) {
                            return D_80B58A3C;
                        }
                        return D_80B5885C;

                    case 0x13:
                    case 0x2F:
                        return D_80B58938;

                    case 0x16:
                        return D_80B58988;

                    case 0x17:
                        return D_80B589FC;

                    case 0x30:
                        return D_80B58944;

                    case 0x31:
                        if (player->transformation == PLAYER_FORM_HUMAN) {
                            return D_80B58B88;
                        }
                        return D_80B589FC;

                    case 0x34:
                    case 0x35:
                        return D_80B58994;

                    default:
                        break;
                }
            }
            break;
    }

    return NULL;
}

s32 func_80B55180(EnAn* this, PlayState* play) {
    s32 ret = false;

    if ((this->unk_360 & 7) && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        SubS_SetOfferMode(&this->unk_360, 0U, 7U);
        this->unk_3C4 = 0;
        this->unk_394 = 0;
        this->msgEventFunc = NULL;
        this->actor.child = this->unk_218;
        this->msgEventScript = func_80B54DF4(this, play);

        if ((this->unk_200 == 1) || (this->unk_200 == 3) || (this->unk_200 == 0x12) || (this->unk_200 == 0x13) || (this->unk_200 == 0x17) || (this->unk_200 == 0x16) || (this->unk_200 == 0x28) || (this->unk_200 == 0x2A) || (this->unk_200 == 0x2B) || (this->unk_200 == 0x2C) || (this->unk_200 == 0x2D) || (this->unk_200 == 0x2F) || (this->unk_200 == 0x30) || (this->unk_200 == 0x31) || (this->unk_200 == 0x34) || (this->unk_200 == 0x35)) {
            this->unk_360 |= 0x20;
        }

        if ((this->unk_200 == 3) && (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20)) {
            this->unk_360 &= ~0x20;
        }

        this->actionFunc = func_80B57A44;
        ret = true;
    }

    return ret;
}

s32 func_80B552E4(EnAn* this, PlayState* play) {
    u16 temp_v0 = play->csCtx.scriptIndex;
    s32 ret = false;

    if ((play->csCtx.state != 0) && (play->sceneId == 0x61) && (gSaveContext.sceneLayer == 0) && ((temp_v0 == 0) || (temp_v0 == 1))) {
        if (this->unk_3B0 == 0) {
            this->unk_38A = 0;
            this->unk_38C = 0;
            this->unk_360 |= 0x300;
            this->unk_38E = 8;
            this->unk_364 = -1;
            this->unk_3B0 = 1;
            this->unk_3B4 = 0;
        }

        ret = true;
    } else if (this->unk_3B0 != 0) {
        this->unk_3B0 = 0;
        this->unk_3B4 = 0;
        this->unk_3C0 = 1;
        this->actor.room = play->roomCtx.curRoom.num;
        this->actionFunc = func_80B578F8;
    }

    return ret;
}

void func_80B553AC(EnAn* this) {
    Actor* temp_v0_2;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad;

    Math_Vec3f_Copy(&sp40, &this->unk_218->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_37E, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->unk_37E = CLAMP(this->unk_37E, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    temp_v0_2 = this->unk_218;
    if (temp_v0_2->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)temp_v0_2)->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &temp_v0_2->focus.pos);
    }

    Math_ApproachS(&this->unk_37C, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->unk_37C = CLAMP(this->unk_37C, -0x1554, 0x1554);
}

void func_80B554E8(EnAn* this) {
    if (this->unk_360 & 0x20) {
        if ((this->unk_218 != NULL) && (this->unk_218->update != NULL)) {
            if (DECR(this->unk_388) == 0) {
                func_80B553AC(this);
                this->unk_360 &= ~0x200;
                this->unk_360 |= 0x80;
                return;
            }
        }
    }

    if (this->unk_360 & 0x80) {
        this->unk_360 &= ~0x80;
        this->unk_37C = 0;
        this->unk_37E = 0;
        this->unk_388 = 0x14;
        return;
    }

    if (DECR(this->unk_388) == 0) {
        this->unk_360 |= 0x200;
    }
}

s32 func_80B555C8(EnAn* this, PlayState* play) {
    switch (this->unk_200) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x17:
            func_80B53CE8(this, play, 1);
            break;

        case 0x16:
            func_80B53CE8(this, play, 0x17);
            this->unk_360 |= 0x2000;
            break;

        case 0xE:
            func_80B53CE8(this, play, 0xC);
            break;

        case 0x15:
            func_80B53CE8(this, play, 0xF);
            break;

        case 0x2F:
        case 0x31:
            func_80B53CE8(this, play, 7);
            break;

        case 0x34:
        case 0x35:
            func_80B53CE8(this, play, 0x16);
            this->unk_360 |= 0x2000;
            break;

        default:
            if (this->unk_39C == 0xF) {
                func_80B53CE8(this, play, 0x10);
            }
            if (this->unk_39C == 0x11) {
                func_80B53CE8(this, play, 0x12);
            }
            if ((this->unk_39C == 1) || (this->unk_39C == 2)) {
                func_80B53CE8(this, play, 8);
            }
            break;
    }

    return 0;
}

void func_80B556F8(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        func_80B53CE8(this, play, 6);
        this->unk_360 &= 0xFFDF;
        this->unk_360 |= 0x200;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && Animation_OnFrame(&this->unk_144, this->unk_144.endFrame)) {
        func_80B53CE8(this, play, 2);
        this->unk_360 &= 0xFDFF;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

void func_80B557AC(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        func_80B53CE8(this, play, 3);
        this->unk_360 &= 0xFFDF;
        this->unk_360 |= 0x200;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && Animation_OnFrame(&this->unk_144, this->unk_144.endFrame)) {
        func_80B53CE8(this, play, 2);
        this->unk_360 &= 0xFDFF;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

void func_80B55860(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        func_80B53CE8(this, play, 4);
        this->unk_360 |= 0x200;
        this->unk_360 &= 0xFFDF;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && (Animation_OnFrame(&this->unk_144, this->unk_144.endFrame) != 0)) {
        func_80B53CE8(this, play, 2);
        this->unk_360 &= 0xFDFF;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

s32 func_80B55914(EnAn* this, PlayState* play) {
    Player* player;
    u16 sp22;

    player = GET_PLAYER(play);
    sp22 = play->msgCtx.currentTextId;
    if (player->stateFlags1 & PLAYER_STATE1_40) {
        this->unk_360 |= 0x400;
        if (this->unk_362 != sp22) {
            switch (sp22) {                         /* switch 3; irregular */
                case 0x28E5:                        /* switch 3 */
                    func_80B53CE8(this, play, 5);
                    this->unk_360 &= 0xDFFF;
                    break;
                case 0x28BA:                        /* switch 3 */
                case 0x28D1:                        /* switch 3 */
                    func_80B53CE8(this, play, 5);
                    break;
                case 0x28AF:                        /* switch 3 */
                case 0x28C1:                        /* switch 3 */
                    func_80B53CE8(this, play, 1);
                    break;
                case 0x28BC:                        /* switch 3 */
                    func_80B53CE8(this, play, 2);
                    break;
                case 0x28C6:                        /* switch 3 */
                    func_80B53CE8(this, play, 0xF);
                    break;
                case 0x28F5:                        /* switch 3 */
                    func_80B53CE8(this, play, 0xA);
                    break;
                case 0x28F7:                        /* switch 3 */
                case 0x28F8:                        /* switch 3 */
                    func_80B53CE8(this, play, 0x15);
                    break;
                case 0x28EB:                        /* switch 3 */
                    if (this->unk_39C != 0x14) {
                        this->unk_360 &= 0xBFDF;
                        this->unk_360 |= 0x200;
                        func_80B53CE8(this, play, 0x14);
                    }
                    break;
                case 0x28A4:                        /* switch 3 */
                case 0x28A9:                        /* switch 3 */
                case 0x28BE:                        /* switch 3 */
                case 0x28C0:                        /* switch 3 */
                case 0x295E:
                    this->unk_18C = func_80B556F8;
                    this->unk_396 = 0;
                    break;
                case 0x28E6:                        /* switch 3 */
                    this->unk_360 &= 0xDFFF;
                    this->unk_18C = func_80B55860;
                    this->unk_396 = 0;
                    break;
                case 0x1885:                        /* switch 3 */
                case 0x28A0:                        /* switch 3 */
                case 0x28A3:                        /* switch 3 */
                case 0x28A5:                        /* switch 3 */
                case 0x28B1:                        /* switch 3 */
                case 0x28D2:                        /* switch 3 */
                case 0x28D9:                        /* switch 3 */
                case 0x28DC:                        /* switch 3 */
                case 0x28DE:                        /* switch 3 */
                    this->unk_18C = func_80B557AC;
                    this->unk_396 = 0;
                    break;
                case 0x28A1:                        /* switch 3 */
                case 0x28A2:                        /* switch 3 */
                case 0x28A6:                        /* switch 3 */
                case 0x28A7:                        /* switch 3 */
                case 0x28A8:                        /* switch 3 */
                case 0x28AA:                        /* switch 3 */
                case 0x28AB:                        /* switch 3 */
                case 0x28AC:                        /* switch 3 */
                case 0x28AD:                        /* switch 3 */
                case 0x28AE:                        /* switch 3 */
                case 0x28B0:                        /* switch 3 */
                case 0x28B2:                        /* switch 3 */
                case 0x28B3:                        /* switch 3 */
                case 0x28B4:                        /* switch 3 */
                case 0x28B5:                        /* switch 3 */
                case 0x28B6:                        /* switch 3 */
                case 0x28B7:                        /* switch 3 */
                case 0x28B8:                        /* switch 3 */
                case 0x28B9:                        /* switch 3 */
                case 0x28BB:                        /* switch 3 */
                case 0x28BD:                        /* switch 3 */
                case 0x28BF:                        /* switch 3 */
                case 0x28C2:                        /* switch 3 */
                case 0x28C3:                        /* switch 3 */
                case 0x28C4:                        /* switch 3 */
                case 0x28C5:                        /* switch 3 */
                case 0x28C7:                        /* switch 3 */
                case 0x28C8:                        /* switch 3 */
                case 0x28C9:                        /* switch 3 */
                case 0x28CA:                        /* switch 3 */
                case 0x28CB:                        /* switch 3 */
                case 0x28CC:                        /* switch 3 */
                case 0x28CD:                        /* switch 3 */
                case 0x28CE:                        /* switch 3 */
                case 0x28CF:                        /* switch 3 */
                case 0x28D0:                        /* switch 3 */
                case 0x28D3:                        /* switch 3 */
                case 0x28D4:                        /* switch 3 */
                case 0x28D5:                        /* switch 3 */
                case 0x28D6:                        /* switch 3 */
                case 0x28D7:                        /* switch 3 */
                case 0x28D8:                        /* switch 3 */
                case 0x28DA:                        /* switch 3 */
                case 0x28DB:                        /* switch 3 */
                case 0x28DD:                        /* switch 3 */
                case 0x28DF:                        /* switch 3 */
                case 0x28E0:                        /* switch 3 */
                case 0x28E1:                        /* switch 3 */
                case 0x28E2:                        /* switch 3 */
                case 0x28E3:                        /* switch 3 */
                case 0x28E4:                        /* switch 3 */
                case 0x28E7:                        /* switch 3 */
                case 0x28E8:                        /* switch 3 */
                case 0x28E9:                        /* switch 3 */
                case 0x28EA:                        /* switch 3 */
                case 0x28EC:                        /* switch 3 */
                case 0x28ED:                        /* switch 3 */
                case 0x28EE:                        /* switch 3 */
                case 0x28EF:                        /* switch 3 */
                case 0x28F0:                        /* switch 3 */
                case 0x28F1:                        /* switch 3 */
                case 0x28F2:                        /* switch 3 */
                case 0x28F3:                        /* switch 3 */
                case 0x28F4:                        /* switch 3 */
                case 0x28F6:                        /* switch 3 */
                default: // idk
                    if (this->unk_39C == 0x10) {
                        func_80B53CE8(this, play, 0xF);
                    }
                    if (this->unk_39C == 0x12) {
                        func_80B53CE8(this, play, 0x11);
                    }
                    if ((this->unk_39C == 0x16) || (this->unk_39C == 0x17)) {
                        func_80B53CE8(this, play, 0x15);
                    }
                    if ((this->unk_39C == 7) || (this->unk_39C == 8)) {
                        func_80B53CE8(this, play, 2);
                    }
                    break;
            }

            switch (sp22) {                         /* switch 4; irregular */
                case 0x28F5:                        /* switch 4 */
                    this->unk_38A = 0;
                    /* fallthrough */
                case 0x28A5:                        /* switch 4 */
                case 0x28AA:                        /* switch 4 */
                case 0x28F8:                        /* switch 4 */
                    this->unk_38C = 0;
                    this->unk_38E = 8;
                    break;
                case 0x1885:                        /* switch 4 */
                case 0x28A0:                        /* switch 4 */
                case 0x28A6:                        /* switch 4 */
                case 0x28AF:                        /* switch 4 */
                case 0x28C1:                        /* switch 4 */
                    this->unk_38C = 3;
                    this->unk_38E = 8;
                    break;
                case 0x28A2:                        /* switch 4 */
                case 0x28B3:                        /* switch 4 */
                case 0x28B6:                        /* switch 4 */
                case 0x28BA:                        /* switch 4 */
                case 0x28BE:                        /* switch 4 */
                case 0x28CE:                        /* switch 4 */
                case 0x28D0:                        /* switch 4 */
                case 0x28D6:                        /* switch 4 */
                case 0x28E5:                        /* switch 4 */
                case 0x28E7:                        /* switch 4 */
                case 0x28ED:                        /* switch 4 */
                    this->unk_38C = 1;
                    this->unk_38E = 8;
                    break;
                case 0x28AD:                        /* switch 4 */
                    this->unk_38C = 8;
                    this->unk_38E = 8;
                    break;
                case 0x28C0:                        /* switch 4 */
                case 0x28D7:                        /* switch 4 */
                case 0x28DE:                        /* switch 4 */
                    this->unk_38C = 2;
                    this->unk_38E = 8;
                    break;
                case 0x28E6:                        /* switch 4 */
                case 0x28F7:                        /* switch 4 */
                    this->unk_38C = 6;
                    this->unk_38E = 8;
                    break;
                case 0x28A3:                        /* switch 4 */
                case 0x28B1:                        /* switch 4 */
                case 0x28B8:                        /* switch 4 */
                case 0x28C6:                        /* switch 4 */
                case 0x28CA:                        /* switch 4 */
                case 0x28CC:                        /* switch 4 */
                case 0x28D5:                        /* switch 4 */
                case 0x28E2:                        /* switch 4 */
                case 0x28E3:                        /* switch 4 */
                case 0x28E4:                        /* switch 4 */
                    this->unk_38C = 4;
                    this->unk_38E = 8;
                    break;
                case 0x28EC:                        /* switch 4 */
                    this->unk_38A = 5;
                    /* fallthrough */
                case 0x28DC:                        /* switch 4 */
                case 0x28EB:                        /* switch 4 */
                case 0x28F2:                        /* switch 4 */
                case 0x28F9:                        /* switch 4 */
                    this->unk_38C = 5;
                    this->unk_38E = 8;
                    break;
                case 0x28F6:                        /* switch 4 */
                    this->unk_38C = 9;
                    this->unk_38E = 8;
                    break;
                case 0x28A4:                        /* switch 4 */
                case 0x28A9:                        /* switch 4 */
                    this->unk_38C = 7;
                    this->unk_38E = 8;
                    break;
            }
        }

        this->unk_362 = sp22;
    } else if (this->unk_360 & 0x400) {
        this->unk_18C = NULL;
        this->unk_362 = 0;
        this->unk_360 &= ~0x400;
        this->unk_38C = this->unk_38A;
        this->unk_38E = 4;
        func_80B555C8(this, play);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

Actor* func_80B55D20(EnAn* this, PlayState* play) {
    Actor* actor;

    switch (this->unk_200) {
        default:
            actor = &GET_PLAYER(play)->actor;
            break;

        case 0x15:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_NB);
            break;

        case 0x10:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_PM);
            break;

        case 0x11:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_IG);
            break;
    }

    return actor;
}

extern s32 D_80B58618[];

s32 func_80B55D98(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput, u8 actorCategory, s16 actorId) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3s* temp_v0_3;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* var_v1;
    s32 pad;
    s32 ret = false;

    var_v1 = func_80B539CC(this, play, actorCategory, actorId);
    this->unk_1DC = NULL;

    if (D_80B58618[scheduleOutput->result] >= 0) {
        this->unk_1DC = SubS_GetAdditionalPath(play, sp4F, D_80B58618[scheduleOutput->result]);
    }

    if ((var_v1 != NULL) && (var_v1->update != NULL)) {
        if (this->unk_1DC != NULL) {
            temp_v0_3 = Lib_SegmentedToVirtual(this->unk_1DC->points);
            Math_Vec3s_ToVec3f(&sp3C, &temp_v0_3[this->unk_1DC->count-2]);
            Math_Vec3s_ToVec3f(&sp30, &temp_v0_3[this->unk_1DC->count-1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55F8C.s")

s32 func_80B5600C(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_PM) != 0) {
        func_80B53CE8(this, play, 1);
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0x200;
    }

    return ret;
}

s32 func_80B56094(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_IG) != 0) {
        func_80B53CE8(this, play, 1);
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0x200;
    }

    return ret;
}

s32 func_80B5611C(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, 4, 0x243) != 0) {
        func_80B53CE8(this, play, 0xF);
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0xA00;
    }

    return ret;
}

extern s32 D_80B58618[];

s32 func_80B561A4(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 sp56 = SCHEDULE_TIME_NOW;
    u8 pathIndex = this->actor.params & 0xFF;
    EnDoor* sp50;
    Vec3s* temp_v0_2;
    Vec3f sp40;
    Vec3f sp34;
    s32 limit;
    s32 ret = false;

    this->unk_1DC = NULL;
    sp50 = func_80B53B3C(play, scheduleOutput->result);

    limit = D_80B58618[scheduleOutput->result];
    if (limit >= 0) {
        this->unk_1DC = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((sp50 != NULL) && (sp50->knobDoor.dyna.actor.update != NULL)) {
        if (this->unk_1DC != NULL) {
            temp_v0_2 = Lib_SegmentedToVirtual(this->unk_1DC->points);
            Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[0]);
            Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[1]);
            Math_Vec3f_Copy(&this->unk_228, &sp40);
            Math_Vec3f_Copy(&this->unk_234, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, sp50->knobDoor.dyna.actor.shape.rot.y)) <= 0x4000) {
                this->unk_215 = -0x4B;
            } else {
                this->unk_215 = 0x4B;
            }

            this->unk_378 = scheduleOutput->time1 - scheduleOutput->time0;
            this->unk_37A = sp56 - scheduleOutput->time0;

            switch (scheduleOutput->result) {                    /* switch 1 */
                case 0x1B:                          /* switch 1 */
                case 0x1C:                          /* switch 1 */
                case 0x20:                          /* switch 1 */
                case 0x21:                          /* switch 1 */
                case 0x22:                          /* switch 1 */
                case 0x23:                          /* switch 1 */
                case 0x25:                          /* switch 1 */
                case 0x26:                          /* switch 1 */
                    this->unk_38A = 2;
                    this->unk_38C = 2;
                    this->unk_38E = 8;
                    break;
            }

            switch (scheduleOutput->result) {       /* switch 2 */
                case 0x1A:                          /* switch 2 */
                case 0x1B:                          /* switch 2 */
                case 0x1C:                          /* switch 2 */
                    this->unk_360 |= 0x900;
                    func_80B53CE8(this, play, 0x10);
                    break;
                case 0x24:                          /* switch 2 */
                case 0x27:                          /* switch 2 */
                    this->unk_360 |= 0x2100;
                    func_80B53CE8(this, play, 0x16);
                    break;
                default:                            /* switch 2 */
                    this->unk_360 |= 0x100;
                    func_80B53CE8(this, play, 7);
                    break;
            }

            this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
            this->unk_360 |= 0x200;
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }

    return ret;
}

s32 func_80B56418(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 temp_t0 = (gSaveContext.save.time - 0x3FFC);
    u16 var_v1_2;
    u8 sp2B = this->actor.params & 0xFF;
    s32 pad;
    s32 var_v1 = 0;
    s32 temp_a3;

    this->unk_1DC = NULL;
    temp_a3 = D_80B58618[scheduleOutput->result];

    if (temp_a3 >= 0) {
        this->unk_1DC = SubS_GetAdditionalPath(play, sp2B, temp_a3);
    }

    if ((this->unk_1DC != NULL) && (this->unk_1DC->count < 3)) {
        this->unk_1DC = NULL;
    }

    if (this->unk_1DC != NULL) {
        if ((this->unk_200 < 0x28) && (this->unk_200 != 0) && (this->unk_384 >= 0)) {
            var_v1_2 = temp_t0;
        } else {
            var_v1_2 = scheduleOutput->time0;
        }

        if (scheduleOutput->time1 <  var_v1_2) {
            this->unk_1F0 = (var_v1_2 - scheduleOutput->time1) + 0xFFFF;
        } else {
            this->unk_1F0 = scheduleOutput->time1 - var_v1_2;
        }

        this->unk_1FC = temp_t0 - var_v1_2;
        var_v1_2 = (this->unk_1DC->count - 2);
        this->unk_1F4 = this->unk_1F0 / var_v1_2;

        this->unk_1F8 = (this->unk_1FC / this->unk_1F4) + 2;
        this->unk_360 &= ~8;
        this->unk_360 &= ~0x10;

        switch (scheduleOutput->result) {                           /* switch 1 */
            case 0x2C:                              /* switch 1 */
            case 0x2D:                              /* switch 1 */
            case 0x32:                              /* switch 1 */
            case 0x33:                              /* switch 1 */
            case 0x36:                              /* switch 1 */
            case 0x37:                              /* switch 1 */
            case 0x38:                              /* switch 1 */
            case 0x39:                              /* switch 1 */
            case 0x3A:                              /* switch 1 */
            case 0x3B:                              /* switch 1 */
            case 0x3C:                              /* switch 1 */
            case 0x3D:                              /* switch 1 */
            case 0x3E:                              /* switch 1 */
            case 0x3F:                              /* switch 1 */
                this->unk_38A = 2;
                this->unk_38C = 2;
                this->unk_38E = 8;
                break;
        }

        switch (scheduleOutput->result) {                           /* switch 2 */
            case 0x2A:                              /* switch 2 */
            case 0x2B:                              /* switch 2 */
                SubS_SetOfferMode(&this->unk_360, 3U, 7U);
                /* fallthrough */
            case 0x2C:                              /* switch 2 */
            case 0x2D:                              /* switch 2 */
                func_80B53CE8(this, play, 0x10);
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x800;
                break;

            case 0x34:                              /* switch 2 */
            case 0x35:                              /* switch 2 */
                func_80B53CE8(this, play, 0x16);
                SubS_SetOfferMode(&this->unk_360, 3U, 7U);

                this->unk_360 |= 0x300;
                this->unk_360 |= 0x2000;
                break;

            case 0x32:                              /* switch 2 */
            case 0x33:                              /* switch 2 */
                func_80B53CE8(this, play, 7);
                this->unk_360 |= 0x300;
                break;

            case 0x36:                              /* switch 2 */
            case 0x37:                              /* switch 2 */
            case 0x38:                              /* switch 2 */
            case 0x39:                              /* switch 2 */
            case 0x3A:                              /* switch 2 */
            case 0x3B:                              /* switch 2 */
            case 0x3C:                              /* switch 2 */
            case 0x3D:                              /* switch 2 */
            case 0x3E:                              /* switch 2 */
            case 0x3F:                              /* switch 2 */
                func_80B53CE8(this, play, 0x12);
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x1000;
                break;

            case 0x28:                              /* switch 2 */
            case 0x2F:                              /* switch 2 */
            case 0x30:                              /* switch 2 */
            case 0x31:                              /* switch 2 */
                SubS_SetOfferMode(&this->unk_360, 3U, 7U);
                this->unk_360 |= 0x300;
                /* fallthrough */
            default:                                /* switch 2 */
                func_80B53CE8(this, play, 7);
                break;
        }

        var_v1 = 1;
        this->actor.gravity = -1.0f;
    }

    return var_v1;
}

s32 func_80B56744(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* temp_v0_2;
    s32 limit;
    s32 ret = false;

    this->unk_1DC = NULL;

    limit = D_80B58618[scheduleOutput->result];
    if (limit >= 0) {
        this->unk_1DC = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->unk_1DC != NULL) && (this->unk_1DC->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(this->unk_1DC->points);
        Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[0]);
        Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[1]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);
        if (scheduleOutput->result == 0x16) {
            func_80B53CE8(this, play, 0x17);
            SubS_SetOfferMode(&this->unk_360, 3U, 7U);

            this->unk_360 |= 0x300;
            this->unk_360 |= 0x2000;
        }
        ret = true;
    }

    return ret;
}

s32 func_80B56880(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* temp_v0_2; // sp30
    s32 limit;
    s32 ret = false;

    this->unk_1DC = NULL;
    limit = D_80B58618[scheduleOutput->result];
    if (limit >= 0) {
        this->unk_1DC = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->unk_1DC != NULL) && (this->unk_1DC->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(this->unk_1DC->points);
        Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[this->unk_1DC->count-1]);
        Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[this->unk_1DC->count-2]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);

        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3s_Copy(&this->actor.home.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (scheduleOutput->result) {
            case 0x13:
                this->actor.world.rot.y += 0x7FF8;
                /* fallthrough */
            case 0x12:
            case 0x17:
                func_80B53CE8(this, play, 1);
                SubS_SetOfferMode(&this->unk_360, 3U, 7U);
                this->unk_37A = 0;
                this->unk_360 |= 0x300;
                if (scheduleOutput->result == 0x12) {
                    this->unk_374 = 70.0f;
                }
                break;

            case 0x3:
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x1000;

                if (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20) {
                    func_80B53CE8(this, play, 0x14);
                    this->unk_360 |= 0x40;
                    this->actor.world.rot.y += 0x7FF8;
                    this->actor.shape.rot.y = this->actor.world.rot.y;
                    this->unk_37A = 4;
                } else {
                    func_80B53CE8(this, play, 0x12);
                    this->unk_37A = 0;
                }

                this->unk_38A = 2;
                this->unk_38C = 2;
                this->unk_38E = 8;
                break;
            case 0xE:
                func_80B53CE8(this, play, 0xC);
                SubS_SetOfferMode(&this->unk_360, 3U, 7U);

                this->unk_360 |= 0x300;
                this->unk_360 |= 0x8000;
                break;
        }
        ret = true;
    }

    return ret;
}

extern Vec3f D_80B58E7C;
extern Vec3s D_80B58E88;

s32 func_80B56B00(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E7C);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E88);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    if (scheduleOutput->result == 0xC) {
        func_80B53CE8(this, play, 0xB);
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);

        this->unk_360 |= 0x300;
        this->unk_360 |= 0x40;

        this->unk_38A = 5;
        this->unk_38C = 5;
        this->unk_38E = 8;
    }

    return true;
}

extern Vec3f D_80B58E90;
extern Vec3s D_80B58E9C;

s32 func_80B56BC0(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E90);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E9C);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    switch (scheduleOutput->result) {
        case 0x1:
            SubS_SetOfferMode(&this->unk_360, 3U, 7U);
            func_80B53CE8(this, play, 9);
            break;

        case 0x18:
            func_80B53CE8(this, play, 0xB);
            this->unk_38A = 5;
            this->unk_38C = 5;
            this->unk_38E = 8;
            break;
    }

    this->unk_360 |= 0x300;
    this->unk_360 |= 0x40;

    this->actor.gravity = 0.0f;
    return true;
}

extern Vec3s D_80B58EA4;

s32 func_80B56CAC(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58EA4);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    func_80B53CE8(this, play, 0);
    SubS_SetOfferMode(&this->unk_360, 3U, 7U);
    this->unk_360 |= 0x300;

    return 1;
}

s32 func_80B56D28(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    this->actor.targetMode = TARGET_MODE_6;
    this->unk_360 = 0;
    this->unk_38A = 0;
    this->unk_38C = 0;
    this->unk_38E = 8;
    this->unk_374 = 40.0f;

    switch (scheduleOutput->result) {
        case 0x10:
            ret = func_80B5600C(this, play, scheduleOutput);
            break;

        case 0x11:
            ret = func_80B56094(this, play, scheduleOutput);
            break;

        case 0x15:
            ret = func_80B5611C(this, play, scheduleOutput);
            break;

        case 0xC:
            ret = func_80B56B00(this, play, scheduleOutput);
            break;

        case 0x1:
        case 0x18:
            ret = func_80B56BC0(this, play, scheduleOutput);
            break;

        case 0x3:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x17:
            ret = func_80B56880(this, play, scheduleOutput);
            break;

        case 0x16:
            ret = func_80B56744(this, play, scheduleOutput);
            break;

        case 0x19:
            ret = func_80B56CAC(this, play, scheduleOutput);
            break;

        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
            ret = func_80B561A4(this, play, scheduleOutput);
            break;

        case 0x28:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            ret = func_80B56418(this, play, scheduleOutput);
            break;

        default:
            ret = 0;
            break;
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B5702C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B572D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B573F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B575BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57674.s")

void func_80B57718(EnAn* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57718.s")

void func_80B577F0(EnAn* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->unk_144, &D_06012618, NULL, this->unk_264, this->unk_2E2, 0x15);

    this->unk_39C = -1;
    func_80B53CE8(this, play, 1);
    Collider_InitAndSetCylinder(play, &this->unk_190, &this->actor, &D_80B58BBC);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B58BE8);

    if (this->actor.params & 0x8000) {
        this->unk_3C0 = 1;
    }

    this->actor.draw = EnAn_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_360 = 0;
    this->unk_200 = 0;

    this->actionFunc = func_80B578F8;
    this->actionFunc(this, play);
}

extern u8 D_80B581D0[];

void func_80B578F8(EnAn* this, PlayState* play) {
    ScheduleOutput sp20;

    this->unk_384 = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (!(this->actor.params & 0x8000) && (this->unk_3C0 == 0) && (gSaveContext.save.saveInfo.weekEventReg[0x33] & 0x40)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk_3C0 != 0) {
        sp20.result = 0x19;
        if (this->unk_200 != 0x19) {
            func_80B56D28(this, play, &sp20);
        }
    } else if ((Schedule_RunScript(play, D_80B581D0, &sp20) == 0) || ((this->unk_200 != sp20.result) && (func_80B56D28(this, play, &sp20) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        sp20.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    }

    this->unk_200 = sp20.result;
    this->unk_218 = func_80B55D20(this, play);
    func_80B57718(this, play);
}


void func_80B57A44(EnAn* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventFunc, &this->msgScriptResumePos) != 0) {
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);

        this->unk_360 &= ~0x20;
        this->unk_360 |= 0x200;
        this->unk_388 = 0x14;
        this->msgScriptResumePos = 0;
        this->actionFunc = func_80B578F8;
    } else if ((this->unk_200 != 1) && (this->unk_200 != 3) && (this->unk_200 != 0xC) && (this->unk_200 != 0xE) && (this->unk_200 != 0x19)) {
        if ((this->unk_218 != NULL) && (this->unk_218->update != NULL)) {
            s32 temp;
            Vec3f sp38;
            Vec3f sp2C;

            Math_Vec3f_Copy(&sp38, &this->unk_218->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            temp = Math_Vec3f_Yaw(&sp2C, &sp38);

            Math_ApproachS(&this->actor.shape.rot.y, temp, 4, 0x2AA8);
        }
    }
}

void func_80B57B48(EnAn* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57B48.s")

void EnAn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAn* this = THIS;
    s32 temp_v1;
    s32 temp_v0;

    if (play->sceneId != SCENE_YADOYA) {
        this->actor.params &= (s16)~0x8000;
    }

    temp_v1 = ENAN_GET_8000(&this->actor);
    temp_v0 = gSaveContext.save.saveInfo.weekEventReg[0x33] & 0x40;

    if (((temp_v0 == 0) && (temp_v1 == 1)) || ((temp_v0 != 0) && (temp_v1 == 0))) {
        Actor_Kill(&this->actor);
        return;
    }

    if (temp_v1 == 0) {
        if (func_80B53A7C(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
            Actor_Kill(&this->actor);
            return;
        }
    }

    this->unk_214 = -0x80;
    this->unk_3B8 = 0;
    if (temp_v1 == 0) {
        this->actor.room = -1;
    }

    this->actionFunc = func_80B577F0;
}

void EnAn_Destroy(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    Collider_DestroyCylinder(play, &this->unk_190);
}

void EnAn_Update(Actor* thisx, PlayState* play) {
    EnAn* this = (EnAn* ) thisx;

    if (func_80B53840(this, play) != 0) {
        return;
    }

    if ((this->actionFunc != func_80B577F0) && !func_80B55180(this, play) && (func_80B552E4(this, play) != 0)) {
        func_80B57B48(this, play);
        func_80B53BA8(this, play);
        func_80B53F84(this);
        return;
    }

    this->actionFunc(this, play);
    if (this->unk_200 != 0) {
        func_80B55914(this, play);
        func_80B53BA8(this, play);
        func_80B53F84(this);
        func_80B554E8(this);
        SubS_Offer(&this->actor, play, this->unk_374, 30.0f, 0, this->unk_360 & 7);

        if (!(this->unk_360 & 0x40)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4U);
        }

        func_80B53ED4(this, play);
    }
}

extern Vec3f D_80B58ED4;

void func_80B57EE8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAn* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80B58ED4, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
        func_80B54124(this, play, 1U);
    } else if (limbIndex == 8) {
        func_80B54124(this, play, 0U);
        func_80B54124(this, play, 4U);
        func_80B54124(this, play, 2U);
        func_80B54124(this, play, 3U);
    } else if (limbIndex == 5) {
        func_80B54124(this, play, 5U);
    }
}

void func_80B57FC4(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAn* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_360 & 0x200)) {
        if (this->unk_360 & 0x80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == 9) {
        SubS_UpdateLimb((s16) (this->unk_37C + 0x4000), (s16) (this->unk_37E + this->actor.shape.rot.y + 0x4000), &this->unk_240, &this->unk_258, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_240.x, this->unk_240.y, this->unk_240.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_258.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_258.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_258.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

extern UNK_PTR D_80B58EEC[];
extern UNK_PTR D_80B58EE0[];

void EnAn_Draw(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if ((this->unk_200 != 0) || (this->unk_3B0 != 0)) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B58EEC[this->unk_390]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B58EE0[this->unk_392]));

        SkelAnime_DrawTransformFlexOpa(play, this->unk_144.skeleton, this->unk_144.jointTable, this->unk_144.dListCount, NULL, func_80B57EE8, func_80B57FC4, &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
