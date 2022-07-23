/*
 * File: z_mir_ray2.c
 * Overlay: ovl_Mir_Ray2
 * Description: Reflectable light ray (static beam)
 */

#include "z_mir_ray2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((MirRay2*)thisx)

void MirRay2_Init(Actor* thisx, PlayState* play);
void MirRay2_Destroy(Actor* thisx, PlayState* play);
void MirRay2_Update(Actor* thisx, PlayState* play);
void MirRay2_Draw(Actor* thisx, PlayState* play);

void func_80AF3F70(MirRay2* this);
void func_80AF3FE0(MirRay2* this, PlayState* play);

const ActorInit Mir_Ray2_InitVars = {
    ACTOR_MIR_RAY2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay2),
    (ActorFunc)MirRay2_Init,
    (ActorFunc)MirRay2_Destroy,
    (ActorFunc)MirRay2_Update,
    (ActorFunc)MirRay2_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00200000, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 50 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_OTHER,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

void func_80AF3F70(MirRay2* this) {
    ColliderJntSphElement* elements;

    this->collider.elements->dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements->dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider.elements->dim.worldSphere.center.z = this->actor.world.pos.z;
    elements = this->collider.elements;
    elements->dim.worldSphere.radius = this->unk1A8 * elements->dim.scale;
}

void func_80AF3FE0(MirRay2* this, PlayState* play) {
    if (this->actor.xzDistToPlayer < this->unk1A8) {
        Math_StepToS(&this->radius, 150, 50);
    } else {
        Math_StepToS(&this->radius, 0, 50);
    }
    Lights_PointNoGlowSetInfo(&this->info, this->actor.world.pos.x, this->actor.world.pos.y + 100.0f,
                              this->actor.world.pos.z, 255, 255, 255, this->radius);
}

void MirRay2_Init(Actor* thisx, PlayState* play) {
    s32 switchFlags;
    MirRay2* this = THIS;

    if (this->actor.home.rot.x <= 0) {
        this->unk1A8 = 100.0f;
    } else {
        this->unk1A8 = this->actor.home.rot.x * 4.0f;
    }
    Actor_SetScale(&this->actor, 1.0f);
    if (MIRRAY2_GET_F(&this->actor) != 1) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawWhiteCircle, this->unk1A8 * 0.02f);
    }
    func_80AF3FE0(this, play);
    this->unk1AC = LightContext_InsertLight(play, &play->lightCtx, &this->info);
    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, &this->elements);
    func_80AF3F70(this);
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = this->actor.shape.rot.x;
    if (MIRRAY2_GET_F(&this->actor) != 1) {
        switchFlags = MIRRAY2_GET_SWITCH_FLAGS(&this->actor);
        if ((switchFlags != 0x7F) && !Flags_GetSwitch(play, switchFlags)) {
            this->unk1A4 |= 1;
        }
    }
}

void MirRay2_Destroy(Actor* thisx, PlayState* play) {
    MirRay2* this = THIS;

    LightContext_RemoveLight(play, &play->lightCtx, this->unk1AC);
    Collider_DestroyJntSph(play, &this->collider);
}

void MirRay2_Update(Actor* thisx, PlayState* play) {
    MirRay2* this = THIS;

    if (this->unk1A4 & 1) {
        if (Flags_GetSwitch(play, MIRRAY2_GET_SWITCH_FLAGS(thisx))) {
            this->unk1A4 &= ~1;
        }
    } else {
        func_80AF3FE0(this, play);
        if ((this->actor.params & 0xF) != 1) {
            Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, 4);
            this->actor.shape.shadowAlpha = 0x50;
        } else {
            func_80AF3F70(this);
        }
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }
}

void MirRay2_Draw(Actor* thisx, PlayState* play) {
}
