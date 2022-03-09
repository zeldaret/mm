/*
 * File: z_en_encount2.c
 * Overlay: ovl_En_Encount2
 * Description: Astral Observatory - Majora's Mask Balloon
 */

#include "z_en_encount2.h"
#include "objects/object_fusen/object_fusen.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnEncount2_Idle(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_Popped(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_Die(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_SetIdle(EnEncount2* this);
void EnEncount2_InitParticles(EnEncount2* this, Vec3f* pos, s16 fadeDelay);
void EnEncount2_UpdateParticles(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_DrawParticles(EnEncount2* this, GlobalContext* globalCtx);

const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_fusen_Colheader_002420, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->dyna.actor, &sJntSphInit, &this->colElement);

    this->dyna.actor.targetMode = 6;
    this->dyna.actor.colChkInfo.health = 1;
    this->scale = 0.1;
    this->switchFlag = GET_ENCOUNT2_SWITCH_FLAG(this);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag >= 0) && (Flags_GetSwitch(globalCtx, this->switchFlag))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    this->collider.elements->dim.modelSphere.radius = 0x39;
    this->collider.elements->dim.scale = 1.0f;
    this->collider.elements->dim.modelSphere.center.x = 0;
    this->collider.elements->dim.modelSphere.center.y = -4;
    this->collider.elements->dim.modelSphere.center.z = 0;

    this->dyna.actor.colChkInfo.damageTable = &sDamageTable;
    EnEncount2_SetIdle(this);
}

void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnEncount2_SetIdle(EnEncount2* this) {
    this->isPopped = false;
    this->actionFunc = EnEncount2_Idle;
}

void EnEncount2_Idle(EnEncount2* this, GlobalContext* globalCtx) {
    this->oscillationAngle += 1500.0f;
    this->dyna.actor.velocity.y = Math_SinS(this->oscillationAngle);
    Math_ApproachF(&this->scale, 0.1f, 0.3f, 0.01f);
    if ((this->collider.base.acFlags & AC_HIT) && (this->dyna.actor.colChkInfo.damageEffect == 0xE)) {
        this->dyna.actor.colChkInfo.health = 0;
        this->isPopped = true;
        this->actionFunc = EnEncount2_Popped;
    }
}

void EnEncount2_Popped(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f curPos;

    Math_Vec3f_Copy(&curPos, &this->dyna.actor.world.pos);
    curPos.y += 60.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, curPos.x, curPos.y, curPos.z, 255, 255, 200,
                CLEAR_TAG_LARGE_EXPLOSION);

    for (i = 0; i < ARRAY_COUNT(this->particles) / 2; ++i) {
        EnEncount2_InitParticles(this, &curPos, 10);
    }

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_MUJURA_BALLOON_BROKEN);
    this->deathTimer = 30;
    this->actionFunc = EnEncount2_Die;
}

void EnEncount2_Die(EnEncount2* this, GlobalContext* globalCtx) {
    if (this->deathTimer == 0) {
        if (this->switchFlag >= 0) {
            Flags_SetSwitch(globalCtx, this->switchFlag);
        }
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s32 pad;

    DECR(this->deathTimer);

    this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
    Actor_SetFocus(&this->dyna.actor, 30.0f);
    Actor_SetScale(&this->dyna.actor, this->scale);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->dyna.actor);
    EnEncount2_UpdateParticles(this, globalCtx);

    if (!this->isPopped) {
        Collider_UpdateSpheresElement(&this->collider, 0, &this->dyna.actor);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    if (this->isPopped != true) {
        Gfx_DrawDListOpa(globalCtx, object_fusen_DL_000A00);
        Gfx_DrawDListOpa(globalCtx, object_fusen_DL_000D78);
    }
    EnEncount2_DrawParticles(this, globalCtx);
}

void EnEncount2_InitParticles(EnEncount2* this, Vec3f* pos, s16 fadeDelay) {
    s16 i;
    EnEncount2Particle* sPtr = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, sPtr++) {
        if (!sPtr->enabled) {
            sPtr->enabled = true;
            sPtr->pos = *pos;
            sPtr->alphaFadeDelay = fadeDelay;
            sPtr->alpha = 0xFF;

            sPtr->accel.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->accel.y = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->accel.z = (Rand_ZeroOne() - 0.5f) * 10.0f;

            sPtr->vel.x = Rand_ZeroOne() - 0.5f;
            sPtr->vel.y = Rand_ZeroOne() - 0.5f;
            sPtr->vel.z = Rand_ZeroOne() - 0.5f;

            sPtr->scale = (Rand_ZeroFloat(1.0f) * 0.5f) + 2.0f;
            return;
        }
    }
}

void EnEncount2_UpdateParticles(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    EnEncount2Particle* sPtr = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, sPtr++) {
        if (sPtr->enabled) {
            sPtr->pos.x += sPtr->vel.x;
            sPtr->pos.y += sPtr->vel.y;
            sPtr->pos.z += sPtr->vel.z;
            sPtr->vel.x += sPtr->accel.x;
            sPtr->vel.y += sPtr->accel.y;
            sPtr->vel.z += sPtr->accel.z;

            if (sPtr->alphaFadeDelay != 0) {
                sPtr->alphaFadeDelay--;
            } else {
                sPtr->alpha -= 10;
                if (sPtr->alpha < 10) {
                    sPtr->enabled = 0;
                }
            }
        }
    }
}

void EnEncount2_DrawParticles(EnEncount2* this, GlobalContext* globalCtx) {
    s16 i;
    EnEncount2Particle* sPtr;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    sPtr = this->particles;
    func_8012C28C(gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, sPtr++) {
        if (sPtr->enabled) {
            Matrix_InsertTranslation(sPtr->pos.x, sPtr->pos.y, sPtr->pos.z, MTXMODE_NEW);
            Matrix_Scale(sPtr->scale, sPtr->scale, sPtr->scale, MTXMODE_APPLY);
            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gSun1Tex));
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB10);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(POLY_XLU_DISP++, 250, 180, 255, sPtr->alpha);
            Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
            Matrix_InsertZRotation_f(DEGTORAD(globalCtx->state.frames * 20.0f), MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB58);
        }
    }
    CLOSE_DISPS(gfxCtx);
}
