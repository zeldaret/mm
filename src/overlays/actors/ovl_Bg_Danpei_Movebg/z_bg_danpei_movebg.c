/*
 * File: z_bg_danpei_movebg.c
 * Overlay: ovl_Bg_Danpei_Movebg
 * Description: Moving platforms beneath Dampe's house
 */

#include "z_bg_danpei_movebg.h"
#include "objects/object_d_lift/object_d_lift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgDanpeiMovebg*)thisx)

void BgDanpeiMovebg_Init(Actor* thisx, PlayState* play);
void BgDanpeiMovebg_Destroy(Actor* thisx, PlayState* play);
void BgDanpeiMovebg_Update(Actor* thisx, PlayState* play);

void func_80AF6EA8(BgDanpeiMovebg* this, PlayState* play);
void func_80AF70FC(BgDanpeiMovebg* this, PlayState* play);
void func_80AF74CC(Actor* thisx, PlayState* play);
u16 func_80AF705C(BgDanpeiMovebg* this, u16 flags);
void func_80AF71FC(BgDanpeiMovebg* this, PlayState* play);
void func_80AF72F8(BgDanpeiMovebg* this, PlayState* play);
void func_80AF7354(BgDanpeiMovebg* this, PlayState* play);
void func_80AF746C(BgDanpeiMovebg* this, PlayState* play);

ActorInit Bg_Danpei_Movebg_InitVars = {
    ACTOR_BG_DANPEI_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgDanpeiMovebg),
    (ActorFunc)BgDanpeiMovebg_Init,
    (ActorFunc)BgDanpeiMovebg_Destroy,
    (ActorFunc)BgDanpeiMovebg_Update,
    (ActorFunc)NULL,
};

static u16 D_80AF7530[] = { OBJECT_D_LIFT, OBJECT_DANPEI_OBJECT };

static Gfx* D_80AF7534[] = { gDampeGraveBrownElevatorDL };

static CollisionHeader* D_80AF7538[] = { &gDampeGraveBrownElevatorCol };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

s32 func_80AF6DE0(PlayState* this, ActorPathing* actorPathing) {
    Actor* actor;
    s32 res;

    actor = actorPathing->actor;
    res = 0;
    if (actorPathing->distSqToCurPoint < actor->speed * actor->speed) {
        res = 1;
    } else {
        actor->world.rot.x = actorPathing->rotToCurPoint.x;
        actor->world.rot.y = actorPathing->rotToCurPoint.y;
    }
    return res;
}

void BgDanpeiMovebg_Init(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;
    DynaPolyActor_Init(&this->dyna, 1);
    this->bankIdx = SubS_GetObjectIndex(D_80AF7530[BGDANPEIMOVEBG_GET_TYPE(thisx)], play);
    if (this->bankIdx < 0) {
        Actor_Kill(&this->dyna.actor);
    }
    this->actionFunc = func_80AF6EA8;
}

void func_80AF6EA8(BgDanpeiMovebg* this, PlayState* play) {
    Actor* thisx = (Actor*)this;
    if (SubS_IsObjectLoaded(this->bankIdx, play)) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->bankIdx].segment);
        this->dyna.actor.objBankIndex = this->bankIdx;
        this->dyna.actor.draw = func_80AF74CC;
        Actor_ProcessInitChain(thisx, sInitChain);
        DynaPolyActor_LoadMesh(play, &this->dyna, D_80AF7538[BGDANPEIMOVEBG_GET_TYPE(thisx)]);
        this->dList = D_80AF7534[BGDANPEIMOVEBG_GET_TYPE(thisx)];

        /* If D_LIFT */
        if (BGDANPEIMOVEBG_GET_TYPE(thisx) == 0) {
            this->dyna.actor.gravity = 0.0f;
            this->dyna.actor.speed = 1.0f;
            SubS_ActorPathing_Init(play, &thisx->world.pos, thisx, &this->actorPath, play->setupPathList,
                                   BGDANPEIMOVEBG_GET_PATH_INDEX(thisx), 0, 0, 0, 0);
            this->actionFunc = func_80AF70FC;
        }
    }
}

void BgDanpeiMovebg_Destroy(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgDanpeiMovebg_Update(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;

    this->actionFunc(this, play);
    this->prevFlags = this->flags;
    this->flags &= ~1;
}

u16 func_80AF705C(BgDanpeiMovebg* this, u16 flags) {
    u16 newFlags = flags & ~0x1C;

    if (DynaPolyActor_IsActorOnTop(&this->dyna) && (this->flags & 1)) {
        newFlags |= 4;
    }
    if (DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            newFlags |= 8;
        } else {
            newFlags |= 0x10;
        }
    }
    return newFlags;
}

void func_80AF70FC(BgDanpeiMovebg* this, PlayState* play) {
    this->flags = func_80AF705C(this, this->flags);
    if (this->flags & 0xC) {
        if (this->flags & 4) {
            this->flags |= 2;
        }
        this->actionFunc = func_80AF71FC;
    } else if (this->flags & 0x10) {
        if (!(this->prevFlags & 0x10)) {
            Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_SINK_WOOD_FLOOR);
        }
        Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y - 8.0f, 1.0f, 2.0f, 0.01f);
    } else {
        if (this->prevFlags & 0x10) {
            Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_REBOUND_WOOD_FLOOR);
        }
        Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 1.0f, 2.0f, 0.01f);
    }
}

void func_80AF71FC(BgDanpeiMovebg* this, PlayState* play) {
    SubS_ActorPathing_Update(play, &this->actorPath, SubS_ActorPathing_ComputePointInfo, func_80AF6DE0,
                             SubS_ActorPathing_MoveWithoutGravityReverse, SubS_ActorPathing_SetNextPoint);
    Actor_PlaySfx_Flagged(&this->dyna.actor, NA_SE_EV_PLATE_LIFT_LEVEL - SFX_FLAG);
    if (this->actorPath.flags & ACTOR_PATHING_REACHED_END_TEMPORARY) {
        if (this->flags & 2) {
            this->flags &= ~0x2;
        }
        this->actionFunc = func_80AF72F8;
    } else {
        this->flags = func_80AF705C(this, this->flags);
        if ((this->flags & 0x10) || (this->flags & 0xC) == 0xC) {
            this->actionFunc = func_80AF746C;
        } else if ((this->flags & 0x1C) == 0) {
            this->actorPath.flags |= ACTOR_PATHING_MOVE_BACKWARDS;
            this->dyna.actor.speed = 2.0f;
            this->actionFunc = func_80AF7354;
        }
    }
}

void func_80AF72F8(BgDanpeiMovebg* this, PlayState* play) {
    this->flags = func_80AF705C(this, this->flags);
    if (!(this->flags & 0x1C)) {
        this->actorPath.flags |= ACTOR_PATHING_MOVE_BACKWARDS;
        this->dyna.actor.speed = 2.0f;
        this->actionFunc = func_80AF7354;
    }
}

void func_80AF7354(BgDanpeiMovebg* this, PlayState* play) {
    Actor_PlaySfx_Flagged(&this->dyna.actor, NA_SE_EV_PLATE_LIFT_LEVEL - SFX_FLAG);
    this->flags = func_80AF705C(this, this->flags);
    SubS_ActorPathing_Update(play, &this->actorPath, SubS_ActorPathing_ComputePointInfo, func_80AF6DE0,
                             SubS_ActorPathing_MoveWithoutGravityReverse, SubS_ActorPathing_SetNextPoint);
    if ((this->flags & 0x10) || (this->flags & 0xC) == 0xC) {
        this->actionFunc = func_80AF746C;
    } else if ((this->flags & 0xC) && (this->flags & 0xC) != 0xC) {
        this->actorPath.flags &= ~ACTOR_PATHING_MOVE_BACKWARDS;
        this->dyna.actor.speed = 1.0f;
        if (this->flags & 4) {
            this->flags |= 2;
        }
        this->actionFunc = func_80AF71FC;
    }
    if (this->actorPath.flags & ACTOR_PATHING_REACHED_END_TEMPORARY) {
        this->actorPath.flags &= ~ACTOR_PATHING_MOVE_BACKWARDS;
        this->flags &= ~2;
        this->dyna.actor.speed = 1.0f;
        this->actionFunc = func_80AF70FC;
    }
}

void func_80AF746C(BgDanpeiMovebg* this, PlayState* arg1) {
    this->flags = func_80AF705C(this, this->flags);
    if (!(this->flags & 0x18)) {
        if (this->actorPath.flags & ACTOR_PATHING_MOVE_BACKWARDS) {
            this->actionFunc = func_80AF7354;
        } else {
            this->actionFunc = func_80AF71FC;
        }
    }
}

void func_80AF74CC(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;
    if (this->dList != NULL) {
        Gfx_DrawDListOpa(play, this->dList);
    }
}
