/*
 * File: z_en_elfbub.c
 * Overlay: ovl_En_Elfbub
 * Description: Stray fairy in bubble
 */

#include "z_en_elfbub.h"
#include "overlays/actors/ovl_En_Elforg/z_en_elforg.h"
#include "objects/object_bubble/object_bubble.h"

#define FLAGS (ACTOR_FLAG_1)

#define THIS ((EnElfbub*)thisx)

void EnElfbub_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnElfbub_Pop(EnElfbub* this, GlobalContext* globalCtx);
void EnElfbub_Idle(EnElfbub* this, GlobalContext* globalCtx);

const ActorInit En_Elfbub_InitVars = {
    ACTOR_EN_ELFBUB,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_BUBBLE,
    sizeof(EnElfbub),
    (ActorFunc)EnElfbub_Init,
    (ActorFunc)EnElfbub_Destroy,
    (ActorFunc)EnElfbub_Update,
    (ActorFunc)EnElfbub_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
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
    { 16, 32, 0, { 0, 0, 0 } },
};

void EnElfbub_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnElfbub* this = THIS;
    Actor* childActor;

    if (Flags_GetSwitch(globalCtx, ENELFBUB_GET_SWITCHFLAG(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 16.0f, ActorShadow_DrawCircle, 0.2f);
    this->actor.hintId = 0x16;
    Actor_SetScale(&this->actor, 1.25f);

    this->actionFunc = EnElfbub_Idle;
    this->zRot = randPlusMinusPoint5Scaled(0x10000);
    this->zRotDelta = 1000;
    this->xScale = 0.08f;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    childActor = Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_ELFORG,
                                    this->actor.world.pos.x, this->actor.world.pos.y + 12.0f, this->actor.world.pos.z,
                                    this->actor.world.rot.x, this->actor.world.rot.y, this->actor.world.rot.z,
                                    ((ENELFBUB_GET_SWITCHFLAG(&this->actor) & 0x7F) << 9) | STRAY_FAIRY_TYPE_BUBBLE);
    if (childActor != NULL) {
        childActor->parent = &this->actor;
    }

    this->oscillationAngle = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
}

void EnElfbub_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnElfbub* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnElfbub_Pop(EnElfbub* this, GlobalContext* globalCtx) {
    static Color_RGBA8 sPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sEnvColor = { 150, 150, 150, 0 };
    static Vec3f sAccel = { 0.0f, -0.5f, 0.0f };
    s32 effectCounter;
    Vec3f velocity;
    Vec3f pos;

    Math_SmoothStepToF(&this->xyScale, 3.0f, 0.1f, 1000.0f, 0.0f);
    Math_SmoothStepToF(&this->xScale, 0.2f, 0.1f, 1000.0f, 0.0f);
    this->zRotDelta += 1000;
    this->zRot += this->zRotDelta;
    this->popTimer--;
    if (this->popTimer <= 0) {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y;
        pos.z = this->actor.world.pos.z;

        for (effectCounter = 0; effectCounter < 20; effectCounter++) {
            velocity.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
            velocity.y = Rand_ZeroOne() * 7.0f;
            velocity.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
            EffectSsDtBubble_SpawnCustomColor(globalCtx, &pos, &velocity, &sAccel, &sPrimColor, &sEnvColor,
                                              Rand_S16Offset(100, 50), 25, 0);
        }

        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 60, NA_SE_EN_AWA_BREAK);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnElfbub_Idle(EnElfbub* this, GlobalContext* globalCtx) {
    s32 pad;

    this->zRot += this->zRotDelta;
    this->actor.world.pos.y += Math_SinS(this->oscillationAngle);
    this->oscillationAngle += 0x200;

    if (this->collider.base.acFlags & AC_HIT || this->collider.base.ocFlags1 & OC1_HIT) {
        this->actionFunc = EnElfbub_Pop;
        this->popTimer = 6;
        return;
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnElfbub_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElfbub* this = THIS;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->actor, this->actor.shape.yOffset);
}

void EnElfbub_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnElfbub* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, 0.0f, 1.0f, MTXMODE_APPLY);
    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
    Matrix_Scale(this->xyScale + 1.0f, this->xyScale + 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->zRot, MTXMODE_APPLY);
    Matrix_Scale(this->xScale + 1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->zRot * -1, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_bubble_DL_001000);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
