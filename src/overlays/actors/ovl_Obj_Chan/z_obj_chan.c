/*
 * File: z_obj_chan.c
 * Overlay: ovl_Obj_Chan
 * Description: Goron Shrine chandelier
 *
 * This actor class is used for both the chandelier and its sub-components.
 * The distinction is made using the subtype actor parameter:
 *  -  0 for the chandelier itself
 *  -  1 for one of the 5 breakable pots that are attached to the chandelier
 */

#include "z_obj_chan.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_obj_chan/object_obj_chan.h"
#include "objects/object_tsubo/object_tsubo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjChan*)thisx)

#define OBJCHAN_ROTATION_SPEED 364 // == (65536 * 2/360) i.e. 2 degrees per second

void ObjChan_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjChan_ChandelierAction(ObjChan* this, GlobalContext* globalCtx);
void ObjChan_PotAction(ObjChan* this, GlobalContext* globalCtx);

const ActorInit Obj_Chan_InitVars = {
    ACTOR_OBJ_CHAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OBJ_CHAN,
    sizeof(ObjChan),
    (ActorFunc)ObjChan_Init,
    (ActorFunc)ObjChan_Destroy,
    (ActorFunc)ObjChan_Update,
    (ActorFunc)ObjChan_Draw,
};

static ColliderCylinderInit sObjChanCylinderInit = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 48, 76, -60, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjChan_InitChandelier(ObjChan* this, GlobalContext* globalCtx);
void ObjChan_InitPot(ObjChan* this, GlobalContext* globalCtx);
void ObjChan_CreateSmashParticles(ObjChan* this, GlobalContext* globalCtx);
void ObjChan_DrawPot(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_DrawFire(ObjChan* this, GlobalContext* globalCtx);

static Vec3f sObjChanFlameSize[2] = {
    { 0.16f, 0.11f, 1.0f },
    { 0.13f, 0.09f, 1.0f },
};
static f32 sObjChanFlameYOffset[2] = { 1800, 1800 };
static s32 sObjChanLoaded;

void ObjChan_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjChan* this = THIS;

    if (OBJCHAN_SUBTYPE(&this->actor) == OBJCHAN_SUBTYPE_CHANDELIER) {
        if (sObjChanLoaded) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->actor.room = -1;
        sObjChanLoaded = true;
    }
    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sObjChanCylinderInit);
    SubS_FillCutscenesList(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));
    switch (OBJCHAN_SUBTYPE(&this->actor)) {
        case OBJCHAN_SUBTYPE_CHANDELIER:
            this->rotation = this->actor.shape.rot.y;
            this->actor.shape.rot.y = 0;
            ObjChan_InitChandelier(this, globalCtx);
            break;
        case OBJCHAN_SUBTYPE_POT:
            this->actor.draw = ObjChan_DrawPot;
            ObjChan_InitPot(this, globalCtx);
            break;
    }
}

void ObjChan_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjChan* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

u32 func_80BB9A1C(ObjChan* this, f32 arg1) {
    f32 temp_f6;
    f32 sp20;

    sp20 = Math_SinS(this->unk1D4) * this->unk1D0;
    temp_f6 = (Math_CosS(this->unk1D4) * 0.03834952f * this->unk1D0) + arg1;
    if (temp_f6 != 0.0f) {
        this->unk1D4 = RADF_TO_BINANG(func_80086B30(sp20 * 0.03834952f, temp_f6));
    } else if (sp20 >= 0.0f) {
        this->unk1D4 = 0x4000;
    } else {
        this->unk1D4 = -0x4000;
    }
    if (Math_CosS(this->unk1D4) != 0.0f) {
        this->unk1D0 = (temp_f6 / (Math_CosS(this->unk1D4) * 0.03834952f));
    } else {
        this->unk1D0 = sp20;
    }
    return 0;
}

void ObjChan_CalculatePotPosition(Vec3f* childPosOut, Vec3s* childRotOut, Vec3f* parentPos, Vec3s* parentRot,
                                  s16 childAngle) {
    Vec3f offset;

    Matrix_RotateY(parentRot->y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(parentRot->x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(parentRot->z, MTXMODE_APPLY);
    Matrix_RotateY(childAngle, MTXMODE_APPLY);
    Matrix_GetStateTranslationAndScaledX(-280.0f, &offset);

    childPosOut->x = parentPos->x + offset.x;
    childPosOut->y = parentPos->y + offset.y;
    childPosOut->z = parentPos->z + offset.z;
    Math_Vec3s_Copy(childRotOut, parentRot);
    childRotOut->y += childAngle;
}

void ObjChan_InitChandelier(ObjChan* this, GlobalContext* globalCtx) {
    s32 j;
    s32 i;
    ObjChan* temp_v0;
    Vec3f childPos;
    Vec3s childRot;
    CollisionPoly* sp94;
    s32 sp90;
    Vec3f sp84;

    Math_Vec3f_Copy(&this->unk1C0, &this->actor.world.pos);

    Math_Vec3f_Copy(&sp84, &this->actor.world.pos);
    sp84.y += 1600.0f;
    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp84, &this->unk1C0, &sp94, false, false,
                                true, true, &sp90)) {
        this->unk1CC = this->actor.world.pos.y - this->unk1C0.y;
    } else {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    for (i = 0; i < 5; i++) {
        temp_v0 = (ObjChan*)&globalCtx->actorCtx; // strange cast needed for matching
        ObjChan_CalculatePotPosition(&childPos, &childRot, &this->actor.world.pos, &this->actor.shape.rot,
                                     (s32)(i * 360.0f / 5.0f * (65536.0f / 360.0f)) + this->rotation);
        temp_v0 = (ObjChan*)Actor_SpawnAsChildAndCutscene((ActorContext*)temp_v0, globalCtx, ACTOR_OBJ_CHAN, childPos.x,
                                                          childPos.y, childPos.z, childRot.x, childRot.y, childRot.z,
                                                          (this->actor.params & 0xFFF) | 0x1000, this->actor.cutscene,
                                                          this->actor.unk20, &this->actor);
        if (temp_v0 != NULL) {
            this->pots[i] = temp_v0;
            temp_v0->myPotIndex = i;
            temp_v0->actor.cutscene = this->actor.cutscene;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }

    if (Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
        this->stateFlags |= OBJCHAN_STATE_FIRE_DELAY;
        this->stateFlags |= OBJCHAN_STATE_ON_FIRE;

        this->rotationSpeed = OBJCHAN_ROTATION_SPEED;
        this->flameSize = 1.0f;

        for (i = 0; i < 5; i++) {
            if (this->pots[i] != NULL) {
                this->pots[i]->stateFlags |= OBJCHAN_STATE_FIRE_DELAY;
                this->pots[i]->stateFlags |= OBJCHAN_STATE_ON_FIRE;
                this->pots[i]->flameSize = 1.0f;
            }
        }
    }
    this->collider.dim.radius = 45;
    this->collider.dim.height = 60;
    this->collider.dim.yShift = -20;
    this->actionFunc = ObjChan_ChandelierAction;
}

void ObjChan_ChandelierAction(ObjChan* thisx, GlobalContext* globalCtx) {
    ObjChan* this = thisx;
    ObjChan* temp;
    s32 i;
    Vec3f sp60;
    Vec3s sp58;

    if (this->unk1D0 > 0.0f) {
        this->unk1D4 += 0x190;
        if (this->unk1D0 <= 400.0f) {
            this->unk1D0 = this->unk1D0 * 0.99f;
        } else {
            this->unk1D0 = this->unk1D0 - 1.0f;
        }
        if (this->unk1D0 < 0.0f) {
            this->unk1D4 = 0;
            this->unk1D0 = 0.0f;
        }
    }
    this->actor.shape.rot.z = (Math_SinS(this->unk1D4) * this->unk1D0);
    if ((this->stateFlags & OBJCHAN_STATE_START_CUTSCENE) &&
        SubS_StartActorCutscene(&this->actor, this->cutscenes[0], -1, 0)) {
        this->stateFlags |= OBJCHAN_STATE_CUTSCENE;
        this->stateFlags &= ~OBJCHAN_STATE_START_CUTSCENE;
    }
    if ((this->stateFlags & OBJCHAN_STATE_CUTSCENE) && this->rotationSpeed == OBJCHAN_ROTATION_SPEED) {
        this->stateFlags &= ~OBJCHAN_STATE_CUTSCENE;
        ActorCutscene_Stop(this->cutscenes[0]);
    }
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateY(this->rotation, MTXMODE_APPLY);
    Matrix_GetStateTranslationAndScaledY(this->unk1CC, &this->actor.world.pos);
    Math_Vec3f_Sum(&this->actor.world.pos, &this->unk1C0, &this->actor.world.pos);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    for (i = 0; i < 5; i++) {
        temp = this->pots[i];
        if (temp != NULL) {
            ObjChan_CalculatePotPosition(&sp60, &sp58, &this->actor.world.pos, &this->actor.shape.rot,
                                         (s32)(i * 360.0f / 5.0f * (65536.0f / 360.0f)) + this->rotation);
            Math_Vec3f_Copy(&temp->actor.world.pos, &sp60);
            Math_Vec3s_Copy(&temp->actor.shape.rot, &this->actor.shape.rot);
            temp->actor.shape.rot.y = this->rotation;
            Math_Vec3f_ToVec3s(&temp->collider.dim.pos, &temp->actor.world.pos);
        }
    }
    if ((this->collider.base.acFlags & AC_HIT) && (this->collider.info.acHitInfo->toucher.dmgFlags & 0x800)) {
        Flags_SetSwitch(globalCtx, this->actor.params & 0x7F);
    }
    if (Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
        if (!(this->stateFlags & OBJCHAN_STATE_FIRE_DELAY)) {
            this->rotationSpeed = 0;
            this->flameSize = 0.0f;
            for (i = 0; i < 5; i++) {
                temp = this->pots[i];
                if (temp != NULL) {
                    this->pots[i]->stateFlags |= OBJCHAN_STATE_FIRE_DELAY;
                    this->pots[i]->fireDelayFrames = 20 + i * 5;
                    this->pots[i]->flameSize = 0.0f;
                }
            }
            this->stateFlags |= OBJCHAN_STATE_FIRE_DELAY;
            this->stateFlags |= OBJCHAN_STATE_ON_FIRE;
            this->stateFlags |= OBJCHAN_STATE_START_CUTSCENE;
        } else {
            Math_StepToF(&this->flameSize, 1.0f, 0.05f);
            this->rotation += this->rotationSpeed;
            Math_StepToS(&this->rotationSpeed, OBJCHAN_ROTATION_SPEED, 5);
            func_800B9010(&this->actor, NA_SE_EV_CHANDELIER_ROLL - SFX_FLAG);
        }
    }
}

void ObjChan_InitPot(ObjChan* this, GlobalContext* globalCtx) {
    this->actionFunc = ObjChan_PotAction;
}

void ObjChan_PotAction(ObjChan* this, GlobalContext* globalCtx) {
    s32 potBreaks;
    s16 temp_v0_2;
    s32 phi_v1;

    potBreaks = false;
    if ((this->collider.base.acFlags & AC_HIT) && (this->collider.info.acHitInfo->toucher.dmgFlags & 0x4004000)) {
        potBreaks = true;
    }
    if (this->stateFlags & OBJCHAN_STATE_ON_FIRE) {
        Math_StepToF(&this->flameSize, 1.0f, 0.05f);
    } else if (this->stateFlags & OBJCHAN_STATE_FIRE_DELAY) {
        this->fireDelayFrames--;
        if (this->fireDelayFrames <= 0) {
            this->stateFlags |= OBJCHAN_STATE_ON_FIRE;
        }
    }
    if (potBreaks) {
        ObjChan_CreateSmashParticles(this, globalCtx);
        ((ObjChan*)this->actor.parent)->pots[this->myPotIndex] = NULL;
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 20, NA_SE_EV_CHANDELIER_BROKEN);
        func_80BB9A1C((ObjChan*)this->actor.parent, 40.0f);
        if (this->myPotIndex == 4) {
            temp_v0_2 = gSaveContext.save.weekEventReg[0x25];
            if (!(temp_v0_2 & 0x10)) {
                gSaveContext.save.weekEventReg[0x25] = temp_v0_2 | 0x10;
                Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_EN_MM, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0x8000,
                                              this->actor.cutscene, this->actor.unk20, NULL);
            }
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjChan_CreateSmashParticles(ObjChan* this, GlobalContext* globalCtx) {
    s16 new_var = 0;
    s32 phi_s0;
    Vec3f spDC;
    Vec3f spD0;
    f32 temp_f0;
    f32 new_var2;
    s16 temp_s1 = 0;
    s32 temp_s2;
    f32 spAC;
    f32 spA8 = new_var + 15.0f;
    f32 spA4 = new_var + (spAC = 110.0f);

    for (temp_s2 = 0, temp_s1 = 0; temp_s2 != 18; temp_s2++, temp_s1 += 0x4E20) {
        f32 sin = Math_SinS(temp_s1);
        f32 cos = Math_CosS(temp_s1);
        spDC.x = sin * 8.0f;
        spDC.y = Rand_ZeroOne() * 12.0f + 2.0f;
        spDC.z = cos * 8.0f;
        spD0.x = spDC.x * 0.23f;
        spD0.y = Rand_ZeroOne() * 5.0f + 2.5f;
        spD0.z = spDC.z * 0.23f;
        temp_f0 = Rand_ZeroOne();
        if (temp_f0 < 0.2f) {
            phi_s0 = 0x60;
        } else if (temp_f0 < 0.6f) {
            phi_s0 = 0x40;
        } else {
            phi_s0 = 0x20;
        }
        new_var2 = spA4 * Rand_ZeroOne();
        EffectSsKakera_Spawn(globalCtx, &spDC, &spD0, &this->actor.world.pos, -260, phi_s0, 20, 0, 0, spA8 + new_var2,
                             0, 0, 50, -1, OBJECT_TSUBO, object_tsubo_DL_001960);
    }
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 20, 50, true);
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 10, 80, true);
}

void ObjChan_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjChan* this = THIS;

    this->actionFunc(this, globalCtx);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void ObjChan_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjChan* this = THIS;
    Gfx* opa;
    Gfx* xlu;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    Matrix_RotateY(this->rotation, MTXMODE_APPLY);

    opa = Gfx_CallSetupDL(POLY_OPA_DISP, 0x19);
    gSPMatrix(&opa[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
    gSPDisplayList(&opa[1], object_obj_chan_DL_000AF0);
    POLY_OPA_DISP = &opa[2];

    xlu = func_8012C2B4(POLY_XLU_DISP);
    gSPMatrix(&xlu[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
    gSPDisplayList(&xlu[1], object_obj_chan_DL_000A10);
    POLY_XLU_DISP = &xlu[2];

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();
    if (this->stateFlags & OBJCHAN_STATE_ON_FIRE) {
        ObjChan_DrawFire(this, globalCtx);
    }
    Matrix_StatePop();
}

void ObjChan_DrawPot(Actor* thisx, GlobalContext* globalCtx) {
    ObjChan* this = THIS;
    s32 pad;
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    dl = Gfx_CallSetupDL(POLY_OPA_DISP, 0x19);
    gSPMatrix(&dl[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
    gSPDisplayList(&dl[1], object_obj_chan_DL_002358);
    POLY_OPA_DISP = &dl[2];
    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->stateFlags & OBJCHAN_STATE_ON_FIRE) {
        ObjChan_DrawFire(this, globalCtx);
    }
}

void ObjChan_DrawFire(ObjChan* this, GlobalContext* globalCtx) {
    u32 sp4C;
    Gfx* dl;
    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp4C = globalCtx->gameplayFrames;

    Matrix_RotateY(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)) - this->actor.shape.rot.y - this->rotation + 0x8000,
                   MTXMODE_APPLY);
    Matrix_Scale(sObjChanFlameSize[OBJCHAN_SUBTYPE(&this->actor)].x * this->flameSize,
                 sObjChanFlameSize[OBJCHAN_SUBTYPE(&this->actor)].y * this->flameSize, 1.0f, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, sObjChanFlameYOffset[OBJCHAN_SUBTYPE(&this->actor)], 0.0f, MTXMODE_APPLY);

    dl = func_8012C2B4(POLY_XLU_DISP);
    gSPMatrix(&dl[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
    gMoveWd(&dl[1], 6, 32, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0U, -sp4C * 20, 32, 128));
    gDPSetPrimColor(&dl[2], 128, 128, 255, 255, 0, 255);
    gDPSetEnvColor(&dl[3], 255, 0, 0, 0);
    gSPDisplayList(&dl[4], &gGameplayKeepDrawFlameDL);
    POLY_XLU_DISP = &dl[5];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
