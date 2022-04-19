/*
 * File: z_en_gk.c
 * Overlay: ovl_En_Gk
 * Description: Goron Elder's Son
 */

#include "z_en_gk.h"
#include "objects/object_gk/object_gk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnGk*)thisx)

void EnGk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B51698(EnGk* this, GlobalContext* globalCtx);
void func_80B51760(EnGk* this, GlobalContext* globalCtx);
void func_80B51970(EnGk* this, GlobalContext* globalCtx);
void func_80B51B40(EnGk* this, GlobalContext* globalCtx);
void func_80B51D9C(EnGk* this, GlobalContext* globalCtx);
void func_80B51EA4(EnGk* this, GlobalContext* globalCtx);
void func_80B51FD0(EnGk* this, GlobalContext* globalCtx);
void func_80B5202C(EnGk* this, GlobalContext* globalCtx);
void func_80B5216C(EnGk* this, GlobalContext* globalCtx);
void func_80B521E8(EnGk* this, GlobalContext* globalCtx);
void func_80B5227C(EnGk* this, GlobalContext* globalCtx);
void func_80B52340(EnGk* this, GlobalContext* globalCtx);
void func_80B52430(EnGk* this, GlobalContext* globalCtx);
void func_80B5253C(EnGk* this, GlobalContext* globalCtx);
void func_80B525E0(EnGk* this, GlobalContext* globalCtx);
void func_80B52654(EnGk* this, GlobalContext* globalCtx);

const ActorInit En_Gk_InitVars = {
    ACTOR_EN_GK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GK,
    sizeof(EnGk),
    (ActorFunc)EnGk_Init,
    (ActorFunc)EnGk_Destroy,
    (ActorFunc)EnGk_Update,
    (ActorFunc)EnGk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 24, 32, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 24, 32, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static AnimationInfo sAnimations[] = {
    { &object_gk_Anim_00787C, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_007DC4, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_gk_Anim_0092C0, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_005EDC, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_gk_Anim_009638, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_008774, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_gk_Anim_00AE34, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_00BD90, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_gk_Anim_00C308, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_009858, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_gk_Anim_009D88, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &object_gk_Anim_00A21C, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_gk_Anim_00AAEC, 1.0f, 0.0f, 0.0f, 0, 0.0f },
};

Color_RGBA8 D_80B533A0 = { 255, 255, 255, 255 };
Color_RGBA8 D_80B533A4 = { 50, 150, 150, 0 };

u16 func_80B50410(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->sceneNum == SCENE_17SETUGEN2) {
        if (player->transformation == PLAYER_FORM_GORON) {
            if (!(gSaveContext.save.weekEventReg[40] & 0x80)) {
                switch (this->unk_31C) {
                    case 0xE7A:
                        return 0xE7B;
                    case 0xE7B:
                        return 0xE7C;
                    case 0xE7C:
                        return 0xE7D;
                    case 0xE7D:
                        return 0xE7E;
                    case 0xE7E:
                        return 0xE7F;
                    case 0xE7F:
                        gSaveContext.save.weekEventReg[40] |= 0x80;
                        this->unk_1E4 |= 1;
                        return 0xE80;
                    default:
                        return 0xE7A;
                }
            } else {
                this->unk_1E4 |= 1;
                return 0xE81;
            }
        } else if (!(gSaveContext.save.weekEventReg[41] & 1)) {
            switch (this->unk_31C) {
                case 0xE82:
                    return 0xE83;
                case 0xE83:
                    return 0xE7D;
                case 0xE7D:
                    return 0xE7E;
                case 0xE7E:
                    return 0xE7F;
                case 0xE7F:
                    gSaveContext.save.weekEventReg[41] |= 1;
                    this->unk_1E4 |= 1;
                    return 0xE80;
                default:
                    return 0xE82;
            }
        } else {
            this->unk_1E4 |= 1;
            return 0xE81;
        }
    } else if (globalCtx->sceneNum == SCENE_GORONRACE) {
        if (player->transformation == PLAYER_FORM_GORON) {
            if (!(gSaveContext.save.weekEventReg[41] & 4)) {
                if (this->unk_31C == 0xE88) {
                    if (!(gSaveContext.save.weekEventReg[41] & 8) || Interface_HasEmptyBottle()) {
                        return 0xE89;
                    }
                    gSaveContext.save.weekEventReg[41] |= 4;
                    this->unk_1E4 |= 1;
                    return 0xE94;
                }
                return 0xE88;
            }

            if ((this->unk_31C == 0xE8D) || (this->unk_31C == 0xE98)) {
                if (!(gSaveContext.save.weekEventReg[41] & 8) || Interface_HasEmptyBottle()) {
                    return 0xE89;
                }
                gSaveContext.save.weekEventReg[41] |= 4;
                this->unk_1E4 |= 1;
                return 0xE94;
            }

            if (this->unk_1E4 & 0x10) {
                return 0xE8D;
            }
            return 0xE98;
        }

        if (!(gSaveContext.save.weekEventReg[41] & 2)) {
            switch (this->unk_31C) {
                case 0xE85:
                    return 0xE86;
                case 0xE86:
                    gSaveContext.save.weekEventReg[41] |= 2;
                    this->unk_1E4 |= 1;
                    return 0xE87;
                default:
                    return 0xE85;
            }
        } else {
            this->unk_1E4 |= 1;
            return 0xE87;
        }
    } else {
        return 0;
    }
}

u16 func_80B50710(EnGk* this) {
    switch (this->unk_31C) {
        case 0xE8E:
            gSaveContext.save.weekEventReg[41] |= 4;
            this->unk_1E4 &= ~0x10;
            this->unk_1E4 |= 1;
            return 0xE8F;

        case 0xE8A:
            return 0xE8B;

        case 0xE8B:
            gSaveContext.save.weekEventReg[41] |= 4;
            this->unk_1E4 |= 0x10;
            this->unk_1E4 |= 1;
            return 0xE8C;
    }
    return 0;
}

void func_80B507A0(EnGk* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 30.0f, 30.0f, 7);
}

s32 func_80B50854(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(this->unk_1E4 & 0x40)) {
        if (player->stateFlags2 & 0x8000000) {
            this->unk_1E4 |= 0x40;
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        }
    } else if (!(player->stateFlags2 & 0x8000000)) {
        this->unk_1E4 &= ~0x40;
    }

    if ((player->transformation == PLAYER_FORM_GORON) && (globalCtx->msgCtx.ocarinaMode == 3) &&
        (globalCtx->msgCtx.unk1202E == 1)) {
        Flags_SetSwitch(globalCtx, ENGK_GET_3F00(&this->actor));
        this->unk_2E4 = 3;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
        this->actionFunc = func_80B521E8;
        return true;
    }
    return false;
}

void func_80B50954(EnGk* this) {
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLONKID_WALK);
    }
}

void func_80B509A8(EnGk* this, GlobalContext* globalCtx) {
    Vec3f sp4C;
    s16 phi_s1 = 0;

    this->unk_300.x += 2.0f * Rand_Centered();
    this->unk_300.y += Rand_ZeroOne();
    this->unk_300.z += 2.0f * Rand_Centered();

    this->unk_30C.x += 2.0f * Rand_Centered();
    this->unk_30C.y += Rand_ZeroOne();
    this->unk_30C.z += 2.0f * Rand_Centered();

    if (this->unk_2E4 == 0) {
        sp4C.x = 0.0f;
        sp4C.z = 0.0f;
        sp4C.y = -1.2f;
        phi_s1 = 25;
    } else if ((this->unk_2E4 == 2) || (this->unk_2E4 == 9) || (this->unk_2E4 == 10) || (this->unk_2E4 == 11)) {
        sp4C.x = 0.0f;
        sp4C.z = 0.0f;
        sp4C.y = -0.5f;
        phi_s1 = 10;
    }

    EffectSsDtBubble_SpawnCustomColor(globalCtx, &this->unk_2E8, &this->unk_300, &sp4C, &D_80B533A0, &D_80B533A4,
                                      Rand_S16Offset(15, 15), phi_s1, 0);
    EffectSsDtBubble_SpawnCustomColor(globalCtx, &this->unk_2F4, &this->unk_30C, &sp4C, &D_80B533A0, &D_80B533A4,
                                      Rand_S16Offset(15, 15), phi_s1, 0);
}

void func_80B50B38(EnGk* this, GlobalContext* globalCtx) {
    s16 i;
    s16 temp;

    switch (this->unk_2E4) {
        case 0:
            this->unk_2E0 = 3;
            for (i = 0; i < 2; i++) {
                func_80B509A8(this, globalCtx);
            }
            break;

        case 2:
            this->unk_2E0 = 3;
            func_80B509A8(this, globalCtx);
            break;

        case 1:
        case 3:
        case 12:
            this->unk_2E0 = 2;
            break;

        case 9:
        case 10:
        case 11:
            this->unk_2E0 = 3;
            func_80B509A8(this, globalCtx);
            break;

        default:
            temp = this->unk_2E2;
            temp--;
            if (temp >= 3) {
                this->unk_2E0 = 0;
                this->unk_2E2 = temp;
            } else if (temp == 0) {
                this->unk_2E0 = 2;
                this->unk_2E2 = (s32)(Rand_ZeroOne() * 60.0f) + 20;
            } else {
                this->unk_2E0 = 1;
                this->unk_2E2 = temp;
            }
            break;
    }
}

s32 func_80B50C78(EnGk* this, Path* path, s32 arg2_) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 arg2 = arg2_;
    s32 ret = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);
    if (arg2 == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if ((sp58 - 1) == arg2) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[arg2 + 1].x - sp5C[arg2 - 1].x;
        phi_f14 = sp5C[arg2 + 1].z - sp5C[arg2 - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }
    return ret;
}

f32 func_80B50E14(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    Vec3s* points;
    Vec3f sp20;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        sp20.x = points[0].x;
        sp20.y = points[0].y;
        sp20.z = points[0].z;
    }
    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);
    return sp20.y - arg2->y;
}

s32 func_80B50ED4(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4, s32 arg5) {
    Vec3f sp7C;
    Vec3f sp70 = gZeroVec3f;
    Vec3s sp68;
    MtxF sp28;

    Matrix_MultiplyVector3fByState(&sp70, &sp7C);
    Matrix_CopyCurrentState(&sp28);
    func_8018219C(&sp28, &sp68, 0);

    *arg2 = sp7C;

    if (!arg4 && !arg5) {
        arg3->x = sp68.x;
        arg3->y = sp68.y;
        arg3->z = sp68.z;
        return true;
    }

    if (arg5) {
        sp68.z = arg0;
        sp68.y = arg1;
    }

    Math_SmoothStepToS(&arg3->x, sp68.x, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&arg3->y, sp68.y, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&arg3->z, sp68.z, 3, 0x2AA8, 0xB6);

    return true;
}

s32 func_80B5100C(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;

    Math_SmoothStepToS(&this->unk_320, (this->actor.yawTowardsPlayer - this->unk_324) - this->actor.shape.rot.y, 4,
                       0x2AA8, 1);
    this->unk_320 = CLAMP(this->unk_320, -0x1FFE, 0x1FFE);

    Math_SmoothStepToS(&this->unk_324, (this->actor.yawTowardsPlayer - this->unk_320) - this->actor.shape.rot.y, 4,
                       0x2AA8, 1);
    this->unk_324 = CLAMP(this->unk_324, -0x1C70, 0x1C70);

    sp40 = player->actor.world.pos;
    sp40.y = player->bodyPartsPos[7].y + 3.0f;

    sp34 = this->actor.world.pos;
    sp34.y += 70.0f;

    Math_SmoothStepToS(&this->unk_31E, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_322, 4, 0x2AA8, 1);
    this->unk_31E = CLAMP(this->unk_31E, -0x1C70, 0x1C70);

    Math_SmoothStepToS(&this->unk_322, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_31E, 4, 0x2AA8, 1);
    this->unk_322 = CLAMP(this->unk_322, -0x1C70, 0x1C70);
    return true;
}

s32 func_80B5123C(EnGk* this, GlobalContext* globalCtx) {
    s16 temp_v0;
    s16 phi_v1;

    if (DECR(this->unk_34E) != 0) {
        this->unk_31E = 0;
        this->unk_320 = 0;
        this->unk_1E4 &= ~8;
        this->unk_322 = 0;
        this->unk_324 = 0;
        return true;
    }

    if (Actor_IsFacingAndNearPlayer(&this->actor, 300.0f, 0x7FF8)) {
        this->unk_1E4 |= 8;
        func_80B5100C(this, globalCtx);
    } else {
        if (this->unk_1E4 & 8) {
            this->unk_34E = 20;
        }
        this->unk_1E4 &= ~8;
        this->unk_31E = 0;
        this->unk_320 = 0;
        this->unk_322 = 0;
        this->unk_324 = 0;
    }
    return true;
}

void func_80B51308(EnGk* this, GlobalContext* globalCtx) {
    s16 sp1E = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_31A].animation);

    if ((this->unk_2E4 == 7) && (sp1E == lastFrame)) {
        this->unk_2E4 = 8;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
    }
}

void func_80B51398(EnGk* this, GlobalContext* globalCtx) {
    s16 sp1E = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[9].animation);

    if ((this->unk_2E4 == 9) && (sp1E == lastFrame)) {
        this->unk_2E4 = 10;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 10);
    }
}

void func_80B51410(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.xzDistToPlayer < 100.0f) {
        if ((player->transformation == PLAYER_FORM_GORON) && (globalCtx->msgCtx.ocarinaMode == 3) &&
            (globalCtx->msgCtx.unk1202E == 0xE)) {
            this->unk_1E4 |= 0x20;
        }

        if (ActorCutscene_GetCanPlayNext(this->unk_318)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLONKID_SOB_TALK);
            ActorCutscene_Start(this->unk_318, &this->actor);
            this->unk_1E4 &= ~0x20;
            return;
        }

        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }

        if (this->unk_1E4 & 0x20) {
            ActorCutscene_SetIntentToPlay(this->unk_318);
        }
    } else {
        this->unk_1E4 &= ~0x20;
    }
}

void func_80B51510(EnGk* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 actionIndex;

    if (this) {}

    if (Cutscene_CheckActorAction(globalCtx, 479)) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 479);

        if (globalCtx->csCtx.actorActions[actionIndex]->action != this->unk_31B) {
            this->unk_31B = globalCtx->csCtx.actorActions[actionIndex]->action;
            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                case 1:
                    this->unk_31A = 0;
                    this->unk_2E4 = 0;
                    break;

                case 2:
                    this->unk_31A = 2;
                    this->unk_2E4 = 2;
                    break;

                case 3:
                    this->unk_31A = 7;
                    this->unk_2E4 = 7;
                    break;

                case 4:
                    this->unk_31A = 3;
                    this->unk_2E4 = 3;
                    break;

                case 5:
                    this->unk_31A = 1;
                    this->unk_2E4 = 1;
                    this->unk_1E4 |= 0x80;
                    this->actionFunc = func_80B5227C;
                    break;

                case 6:
                    this->unk_31A = 12;
                    this->unk_2E4 = 12;
                    break;

                case 7:
                    Flags_SetSwitch(globalCtx, ENGK_GET_3F00(&this->actor));
                    break;
            }
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_31A);
        }

        if (this->unk_31A == 7) {
            func_80B51308(this, globalCtx);
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
        this->actor.shape.yOffset = 0.0f;
    } else {
        this->unk_31B = 0x63;
    }
}

void func_80B51698(EnGk* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_2E4].animation);

    if (sp26 == lastFrame) {
        switch (this->unk_2E4) {
            case 0:
                this->unk_2E4 = 2;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                this->actionFunc = func_80B5216C;
                break;

            case 2:
                this->unk_2E4 = 0;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
                this->actionFunc = func_80B5202C;
                break;
        }
    }
}

void func_80B51760(EnGk* this, GlobalContext* globalCtx) {
    s16 sp2E = this->skelAnime.curFrame;
    s16 lastFrame;

    if (this->unk_2E4 == 11) {
        lastFrame = Animation_GetLastFrame(sAnimations[this->unk_2E4].animation);
        if (sp2E == lastFrame) {
            this->unk_2E4 = 5;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_2E4);
        }
    } else if (this->unk_2E4 == 10) {
        lastFrame = Animation_GetLastFrame(sAnimations[this->unk_2E4].animation);
        if (sp2E == lastFrame) {
            this->unk_2E4 = 11;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_2E4);
        }
    } else {
        if (Flags_GetSwitch(globalCtx, ENGK_GET_3F00(&this->actor))) {
            gSaveContext.save.weekEventReg[40] |= 0x40;
            this->actionFunc = func_80B51D9C;
            return;
        }

        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->unk_1E4 |= 4;
            this->unk_31C = func_80B50410(this, globalCtx);
            Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
            this->actionFunc = func_80B51970;
            if (this->unk_31C == 0xE81) {
                this->unk_2E4 = 0;
                this->unk_1E4 |= 2;
            }
        } else if (((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) &&
                   (gSaveContext.save.entranceIndex != 0xD010)) {
            func_800B863C(&this->actor, globalCtx);
        }

        if (this->unk_1E4 & 4) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
            this->actor.world.rot.y = this->actor.shape.rot.y;
        }
    }
}

void func_80B51970(EnGk* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (((temp_v0 == 6) || (temp_v0 == 5)) && Message_ShouldAdvance(globalCtx)) {
        if ((this->unk_31C == 0xE84) || (this->unk_31C == 0xE99)) {
            ActorCutscene_Stop(this->unk_318);
            this->unk_318 = ActorCutscene_GetAdditionalCutscene(this->unk_318);
            ActorCutscene_SetIntentToPlay(this->unk_318);
            this->actionFunc = func_80B51D9C;
            return;
        }

        if (this->unk_1E4 & 1) {
            this->unk_1E4 &= ~1;
            this->unk_1E4 &= ~4;
            if (this->unk_2E4 == 10) {
                this->unk_1E4 &= ~2;
            }
            this->actionFunc = func_80B51760;
            return;
        }

        this->unk_31C = func_80B50410(this, globalCtx);
        Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
        if (this->unk_31C == 0xE80) {
            this->unk_1E4 |= 2;
        } else if (this->unk_31C == 0xE89) {
            this->actionFunc = func_80B51B40;
        }
    }

    if (this->unk_1E4 & 2) {
        func_801A4748(&this->actor.projectedPos, NA_SE_EN_GOLON_KID_CRY - SFX_FLAG);
        if (this->unk_2E4 != 10) {
            if (this->unk_2E4 != 9) {
                this->unk_2E4 = 9;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 9);
            } else {
                func_80B51398(this, globalCtx);
            }
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->unk_2E4 == 6) {
        func_80B50954(this);
    }
}

void func_80B51B40(EnGk* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 6) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->unk_1E4 & 1) {
                this->unk_1E4 &= ~1;
                this->unk_1E4 &= ~4;

                if (this->unk_2E4 == 10) {
                    this->unk_1E4 &= ~2;
                }

                if (this->unk_31C == 0xE8F) {
                    globalCtx->nextEntranceIndex = 0xD010;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 3;
                    gSaveContext.nextTransition = 3;
                    Parameter_AddMagic(globalCtx, ((void)0, gSaveContext.unk_3F30) +
                                                      (gSaveContext.save.playerData.doubleMagic * 0x30) + 0x30);
                } else {
                    this->actionFunc = func_80B51760;
                }
                return;
            }

            this->unk_31C = func_80B50710(this);
            Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
            if (this->unk_31C == 0xE8C) {
                this->unk_1E4 |= 2;
            }
        }
    } else if ((temp_v0 == 4) && (Message_ShouldAdvance(globalCtx) != 0)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                func_8019F208();
                this->unk_31C = 0xE8E;
                Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
                break;

            case 1:
                func_8019F230();
                this->unk_31C = 0xE8A;
                Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
                break;
        }
    }

    if (this->unk_1E4 & 2) {
        func_801A4748(&this->actor.projectedPos, NA_SE_EN_GOLON_KID_CRY - SFX_FLAG);
        if (this->unk_2E4 != 10) {
            if (this->unk_2E4 != 9) {
                this->unk_2E4 = 9;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 9);
            } else {
                func_80B51398(this, globalCtx);
            }
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80B51D9C(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->unk_318)) {
        ActorCutscene_StartAndSetFlag(this->unk_318, &this->actor);
        if (this->unk_1E4 & 4) {
            this->unk_1E4 &= ~4;
            this->unk_2E4 = 6;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
            this->actionFunc = func_80B51EA4;
        } else {
            this->unk_1E4 |= 4;
            if (player->transformation == PLAYER_FORM_GORON) {
                this->unk_31C = 0xE84;
            } else {
                this->unk_31C = 0xE99;
            }
            Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
            this->actionFunc = func_80B51970;
        }
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk_318);
    }
    func_80B50954(this);
}

void func_80B51EA4(EnGk* this, GlobalContext* globalCtx) {
    Vec3s sp38;
    s16 sp36;

    if (this->path != NULL) {
        func_80B50E14(this->path, this->unk_1EC, &this->actor.world.pos, &sp38);
        Math_SmoothStepToS(&this->actor.world.rot.y, sp38.y, 5, 0x1000, 0x100);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        sp36 = this->actor.shape.rot.y - sp38.y;
        if (func_80B50C78(this, this->path, this->unk_1EC)) {
            if (this->unk_1EC >= (this->path->count - 1)) {
                ActorCutscene_Stop(this->unk_318);
                Actor_MarkForDeath(&this->actor);
            } else {
                this->unk_1EC++;
            }
        }

        if (this->actor.bgCheckFlags & 8) {
            sp38.y = this->actor.wallYaw;
        }

        if (ABS_ALT(sp36) < 0x2AAA) {
            Math_ApproachF(&this->actor.speedXZ, 3.0f, 0.2f, 0.5f);
        }
        Actor_MoveWithGravity(&this->actor);
    }
    func_80B50954(this);
}

void func_80B51FD0(EnGk* this, GlobalContext* globalCtx) {
    if (!(gSaveContext.save.weekEventReg[22] & 4)) {
        if (this->unk_1E4 & 2) {
            func_801A4748(&this->actor.projectedPos, NA_SE_EN_GOLON_KID_CRY - SFX_FLAG);
        } else {
            this->unk_1E4 |= 2;
        }
    }
}

void func_80B5202C(EnGk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->csCtx.state == 0) {
        func_80B51410(this, globalCtx);
    }

    if (!func_80B50854(this, globalCtx)) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            gSaveContext.save.weekEventReg[24] |= 0x80;
            this->actionFunc = func_80B51698;
        } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
            if (player->transformation == PLAYER_FORM_GORON) {
                this->actor.textId = 0xE74;
            } else {
                this->actor.textId = 0xE76;
            }
        }

        if (this->unk_1E4 & 2) {
            if ((globalCtx->msgCtx.ocarinaMode != 1) && (globalCtx->msgCtx.ocarinaMode != 3) &&
                (globalCtx->csCtx.state == 0)) {
                func_801A4748(&this->actor.projectedPos, NA_SE_EN_GOLON_KID_CRY - SFX_FLAG);
            }
        } else {
            this->unk_1E4 |= 2;
        }
    }
}

void func_80B5216C(EnGk* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = func_80B51698;
    }
}

void func_80B521E8(EnGk* this, GlobalContext* globalCtx) {
    s16 sp1E = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_2E4].animation);

    if (sp1E == lastFrame) {
        this->unk_2E4 = 1;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
        this->actionFunc = func_80B5227C;
    }
}

void func_80B5227C(EnGk* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_2E4].animation);

    if ((sp26 + 1) == lastFrame) {
        func_800B14D4(globalCtx, 20.0f, &this->actor.home.pos);
        this->unk_350 = 60;
        if (!(this->unk_1E4 & 0x80)) {
            gSaveContext.save.weekEventReg[22] |= 4;
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SIT_IMT);
        this->unk_350 = 0x4000;
        this->actionFunc = func_80B52654;
    }
}

void func_80B52340(EnGk* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_1E4 |= 4;
        if (gSaveContext.eventInf[1] & 2) {
            this->unk_31C = 0xE90;
            this->actionFunc = func_80B52430;
        } else {
            this->unk_31C = 0xE93;
            this->actionFunc = func_80B52430;
        }
        Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
        this->actor.flags &= ~ACTOR_FLAG_10000;
    } else {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80B52430(EnGk* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 6) && Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_31C) {
            case 0xE93:
                this->unk_31C = 0xE89;
                Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
                this->actionFunc = func_80B51B40;
                return;

            case 0xE90:
                this->unk_31C = 0xE91;
                Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
                return;

            case 0xE91:
                this->actionFunc = func_80B5253C;
                return;

            case 0xE92:
                this->unk_1E4 &= ~4;
                this->actionFunc = func_80B51760;
                return;
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80B5253C(EnGk* this, GlobalContext* globalCtx) {
    s32 sp24;

    if (gSaveContext.save.weekEventReg[41] & 8) {
        sp24 = 0x93;
    } else {
        sp24 = 0x6A;
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        if (sp24 == 0x6A) {
            gSaveContext.save.weekEventReg[41] |= 8;
        }
        this->actionFunc = func_80B525E0;
    } else {
        Actor_PickUp(&this->actor, globalCtx, sp24, 300.0f, 300.0f);
    }
}

void func_80B525E0(EnGk* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_31C = 0xE92;
        Message_StartTextbox(globalCtx, this->unk_31C, &this->actor);
        this->actionFunc = func_80B52430;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80B52654(EnGk* this, GlobalContext* globalCtx) {
    this->unk_350 += 0x400;
    if ((this->unk_1E4 & 0x80) && (globalCtx->csCtx.frames == 250)) {
        gSaveContext.save.weekEventReg[22] |= 4;
    }

    this->unk_354 = Math_SinS(this->unk_350) * 0.006f * 0.06f;
    this->actor.scale.y = 0.006f - this->unk_354;
    this->actor.scale.z = 0.006f - this->unk_354;
    this->actor.scale.x = 0.006f + this->unk_354;
    if (this->unk_350 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLONKID_SNORE);
    }
}

void EnGk_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGk* this = THIS;

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_gk_Skel_0079C0, &object_gk_Anim_00787C, this->jointTable,
                       this->morphTable, 20);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->unk_2E2 = 20;
    this->unk_2E0 = 0;
    this->unk_1E4 = 0;
    this->unk_354 = 0.006f;
    Actor_SetScale(&this->actor, 0.006f);
    this->actor.gravity = -1.0f;

    if (ENGK_GET_F(&this->actor) == ENGK_F_1) {
        this->unk_2E4 = 5;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
        if (globalCtx->sceneNum == SCENE_17SETUGEN2) {
            if (Flags_GetSwitch(globalCtx, ENGK_GET_3F00(&this->actor))) {
                Actor_MarkForDeath(&this->actor);
            } else {
                this->unk_318 = this->actor.cutscene;
                this->path = SubS_GetPathByIndex(globalCtx, ENGK_GET_F0(&this->actor), 15);
                this->actionFunc = func_80B51760;
            }
        } else if (globalCtx->sceneNum == SCENE_GORONRACE) {
            if (gSaveContext.save.weekEventReg[33] & 0x80) {
                if (gSaveContext.save.entranceIndex == 0xD010) {
                    this->actionFunc = func_80B51760;
                } else if (gSaveContext.save.entranceIndex == 0xD020) {
                    this->actionFunc = func_80B52340;
                } else {
                    this->actionFunc = func_80B51760;
                }
            } else {
                Actor_MarkForDeath(&this->actor);
            }
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (ENGK_GET_F(&this->actor) == ENGK_F_2) {
        if (!(gSaveContext.save.weekEventReg[22] & 4)) {
            this->actionFunc = func_80B51FD0;
            this->actor.draw = NULL;
            this->actor.flags |= ACTOR_FLAG_10;
            this->actor.flags &= ~ACTOR_FLAG_1;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (!(gSaveContext.save.weekEventReg[22] & 4)) {
        this->unk_2E4 = 0;
        this->unk_318 = this->actor.cutscene;
        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
        this->actionFunc = func_80B5202C;
    } else {
        this->actionFunc = func_80B52654;
    }
}

void EnGk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGk* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnGk_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGk* this = THIS;

    this->actionFunc(this, globalCtx);

    if ((ENGK_GET_F(&this->actor) == ENGK_F_1) ||
        ((ENGK_GET_F(&this->actor) == ENGK_F_0) && !(gSaveContext.save.weekEventReg[22] & 4))) {
        func_80B507A0(this, globalCtx);
        SkelAnime_Update(&this->skelAnime);
        func_800E9250(globalCtx, &this->actor, &this->unk_1D8, &this->unk_1DE, this->actor.focus.pos);
        if (ENGK_GET_F(&this->actor) == ENGK_F_1) {
            func_80B5123C(this, globalCtx);
        }
        func_80B50B38(this, globalCtx);
    }

    if (ENGK_GET_F(&this->actor) == ENGK_F_0) {
        func_80B51510(this, globalCtx);
    }
}

s32 EnGk_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnGk_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGk* this = THIS;
    Vec3f sp58 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp40 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp34 = { 1100.0f, -100.0f, 0.0f };
    Vec3f sp28 = { 1100.0f, -100.0f, 0.0f };
    f32 phi_f0;

    sp34.x = 1100.0f;
    sp34.z = 500.0f;

    sp28.x = 1100.0f;
    sp28.z = -500.0f;

    if (this->unk_2E4 == 0) {
        sp34.y = -100.0f;
        sp28.y = -100.0f;

        sp40.x = 2.0f;
        sp40.y = 5.8f;
        sp40.z = 0.0f;

        sp4C = sp40;
        sp4C.x *= -1.0f;
    } else if ((this->unk_2E4 == 2) || (this->unk_2E4 == 9) || (this->unk_2E4 == 10) || (this->unk_2E4 == 11)) {
        sp34.y = 400.0f;
        sp28.y = 400.0f;

        sp40.x = 1.0f;
        sp40.y = 0.8f;
        sp40.z = 0.0f;

        sp4C = sp40;
        sp4C.x *= -1.0f;
    }

    if (limbIndex == 17) {
        if (ENGK_GET_F(&this->actor) == ENGK_F_1) {
            phi_f0 = 100.0f;
        } else {
            phi_f0 = 50.0f;
        }

        this->actor.focus.pos.x = this->actor.world.pos.x;
        this->actor.focus.pos.y = this->actor.world.pos.y + phi_f0;
        this->actor.focus.pos.z = this->actor.world.pos.z;

        Matrix_MultiplyVector3fByState(&sp58, &this->actor.focus.pos);
        Matrix_MultiplyVector3fByState(&sp34, &this->unk_2E8);
        Matrix_MultiplyVector3fByState(&sp28, &this->unk_2F4);

        Matrix_StatePush();

        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_MultiplyVector3fByState(&sp4C, &this->unk_30C);
        Matrix_MultiplyVector3fByState(&sp40, &this->unk_300);

        Matrix_StatePop();
    }
}

void EnGk_TransformDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnGk* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    switch (limbIndex) {
        case 18:
            if (this->unk_1E4 & 8) {
                phi_v1 = true;
            } else {
                phi_v1 = false;
            }

            if (this->unk_34E != 0) {
                phi_v0 = true;
            } else {
                phi_v0 = false;
            }
            func_80B50ED4(this->unk_31E + this->unk_322 + 0x4000,
                          this->unk_320 + this->unk_324 + this->actor.shape.rot.y + 0x4000, &this->unk_328,
                          &this->unk_334, phi_v0, phi_v1);

            Matrix_StatePop();

            Matrix_InsertTranslation(this->unk_328.x, this->unk_328.y, this->unk_328.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_334.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_334.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_334.z, MTXMODE_APPLY);

            Matrix_StatePush();
            break;

        case 9:
            if (this->unk_1E4 & 8) {
                phi_v1 = true;
            } else {
                phi_v1 = false;
            }

            if (this->unk_34E != 0) {
                phi_v0 = true;
            } else {
                phi_v0 = false;
            }
            func_80B50ED4(this->unk_322 + 0x4000, this->unk_324 + this->actor.shape.rot.y + 0x4000, &this->unk_33C,
                          &this->unk_348, phi_v0, phi_v1);

            Matrix_StatePop();

            Matrix_InsertTranslation(this->unk_33C.x, this->unk_33C.y, this->unk_33C.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_348.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_348.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_348.z, MTXMODE_APPLY);

            Matrix_StatePush();
            break;
    }
}

TexturePtr D_80B533E4[] = {
    object_gk_Tex_00F720,
    object_gk_Tex_00FF20,
    object_gk_Tex_010720,
    object_gk_Tex_010F20,
};

void EnGk_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGk* this = THIS;
    Vec3f sp5C;
    Vec3f sp50;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if ((ENGK_GET_F(&this->actor) == ENGK_F_0) && (gSaveContext.save.weekEventReg[22] & 4)) {
        Matrix_InsertXRotation_s(-0x4000, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_gk_DL_006688);
        gSPDisplayList(POLY_OPA_DISP++, object_gk_DL_006680);

        func_8012C2DC(globalCtx->state.gfxCtx);

        sp5C = this->actor.world.pos;
        sp50.x = 0.2f;
        sp50.y = 0.2f;
        sp50.z = 0.2f;

        func_800BC620(&sp5C, &sp50, 255, globalCtx);
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B533E4[this->unk_2E0]));

        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGk_OverrideLimbDraw, EnGk_PostLimbDraw,
                                       EnGk_TransformDraw, &this->actor);

        if (ENGK_GET_F(&this->actor) != ENGK_F_2) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            if ((this->unk_2E4 == 0) || (this->unk_2E4 == 1) || (this->unk_2E4 == 2) || (this->unk_2E4 == 3) ||
                (this->unk_2E4 == 4)) {
                sp5C.x = this->actor.world.pos.x - 15.0f;
                sp5C.y = this->actor.world.pos.y;
                sp5C.z = this->actor.world.pos.z;

                sp50.x = 0.2f;
                sp50.y = 0.2f;
                sp50.z = 0.2f;
            } else {
                sp5C = this->actor.world.pos;
                sp50.x = 0.2f;
                sp50.y = 0.2f;
                sp50.z = 0.2f;
            }
            func_800BC620(&sp5C, &sp50, 255, globalCtx);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
