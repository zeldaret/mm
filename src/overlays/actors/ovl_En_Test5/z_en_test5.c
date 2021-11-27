/*
 * File: z_en_test5.c
 * Overlay: ovl_En_Test5
 * Description: Spring Water
 */

#include "z_en_test5.h"

#define FLAGS 0x00000010

#define THIS ((EnTest5*)thisx)

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A90478(EnTest5* this, GlobalContext* globalCtx);

void EnTest5_SetupAction(EnTest5* this, EnTest5ActionFunc actionFunc);

#if 0
const ActorInit En_Test5_InitVars = {
    ACTOR_EN_TEST5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest5),
    (ActorFunc)EnTest5_Init,
    (ActorFunc)EnTest5_Destroy,
    (ActorFunc)EnTest5_Update,
    (ActorFunc)NULL,
};
#endif

void EnTest5_SetupAction(EnTest5* this, EnTest5ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx2) {
    EnTest5* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    WaterBox* sp2C;
    f32 sp28;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp28,
                             &sp2C) == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_Vec3s_ToVec3f(&this->unk_144, &sp2C->minPos);

    this->unk_150 = (f32)sp2C->xLength;
    this->unk_154 = (f32)sp2C->zLength;

    EnTest5_SetupAction(this, func_80A90478);
}

void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTest5* this = THIS;
}

void func_80A90478(EnTest5* this, GlobalContext* globalCtx) {
    Player* sp44;
    Vec3f sp30;

    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        this->actor.parent = NULL;
        return;
    }

    sp44 = GET_PLAYER(globalCtx);

    if ((sp44->unk_388 == 0) || (sp44->unk_384 != 0xBA)) {
        Math_Vec3f_DistXYZAndStoreDiff(&this->unk_144, &sp44->actor.world.pos, &sp30);
        if ((sp30.x >= 0.0f) && (sp30.x <= this->unk_150) && (sp30.z >= 0.0f) && (sp30.z <= this->unk_154) &&
            (fabsf(sp30.y) < 100.0f) && (sp44->actor.depthInWater > 12.0f)) {
            func_800B8A1C(&this->actor, globalCtx, 0xBA, this->actor.xzDistToPlayer,
                          fabsf(this->actor.playerHeightRel));
        }
    }
}

void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx2) {
    EnTest5* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    Vec3f sp44;
    CollisionPoly* sp40;
    UNK_TYPE pad;

    this->actionFunc(this, globalCtx);

    if ((this->actor.params != 0) && ((globalCtx->state.frames & 3) == 0)) {
        sp44.x = (Rand_ZeroOne() * this->unk_150) + this->unk_144.x;
        sp44.y = this->unk_144.y + 100.0f;
        sp44.z = (Rand_ZeroOne() * this->unk_154) + this->unk_144.z;

        if ((BgCheck_EntityRaycastFloor2(globalCtx, &globalCtx->colCtx, &sp40, &sp44) + 10.0f) < this->unk_144.y) {
            Vec3f sp30;

            sp44.y = this->unk_144.y + 10.0f;
            sp30.y = 0.5f;
            sp30.x = 0.0f;
            sp30.z = 0.0f;

            EffectSsIceSmoke_Spawn(globalCtx, &sp44, &sp30, &D_801D15B0, (s16)((-200) - (s32)(Rand_ZeroOne() * 50.0f)));
        }
    }
}
