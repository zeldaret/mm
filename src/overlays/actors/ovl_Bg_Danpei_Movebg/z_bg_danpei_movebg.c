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

void func_80AF6EA8(BgDanpeiMovebg*, PlayState*);

void BgDanpeiMovebg_Init(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;
    DynaPolyActor_Init(&this->dyna, 1);
    this->bankIdx = SubS_GetObjectIndex(D_80AF7530[(this->dyna.actor.params >> 0xE) & 0x3], play);
    if (this->bankIdx < 0) {
        Actor_Kill(&this->dyna.actor);
    }
    this->actionFunc = func_80AF6EA8;
}

void func_80AF70FC(BgDanpeiMovebg* this, PlayState* play);
void func_80AF74CC(Actor* thisx, PlayState* play);

void func_80AF6EA8(BgDanpeiMovebg* this, PlayState* play) {
    Actor* thisx = (Actor*)this;
    if (SubS_IsObjectLoaded(this->bankIdx, play)) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->bankIdx].segment);
        this->dyna.actor.objBankIndex = this->bankIdx;
        this->dyna.actor.draw = func_80AF74CC;
        Actor_ProcessInitChain(thisx, sInitChain);
        DynaPolyActor_LoadMesh(play, &this->dyna, D_80AF7538[(thisx->params >> 0xE) & 0x3]);
        this->unk_1D0 = D_80AF7534[((thisx->params >> 0xE) & 0x3)];

        /* If D_LIFT */
        if (((thisx->params >> 0xE) & 0x3) == 0) {
            this->dyna.actor.gravity = 0.0f;
            this->dyna.actor.speed = 1.0f;
            SubS_ActorPathing_Init(play, &thisx->world.pos, thisx, &this->actorPath, play->setupPathList,
                                   thisx->params & 0x7F, 0, 0, 0, 0);
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
    this->unk_1CE = this->unk_1CC;
    this->unk_1CC &= ~1;
}

u16 func_80AF705C(BgDanpeiMovebg* this, u16 unk_1CC) {
    u16 v1 = unk_1CC & ~0x1C;

    if (DynaPolyActor_IsActorOnTop(&this->dyna) && (this->unk_1CC & 1)) {
        v1 |= 4;
    }
    if (DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
        if (gSaveContext.save.playerForm == 3) {
            v1 |= 8;
        } else {
            v1 |= 0x10;
        }
    }
    return v1;
}

u16 func_80AF705C(BgDanpeiMovebg*, u16);
void func_80AF71FC(BgDanpeiMovebg*, PlayState*);

void func_80AF70FC(BgDanpeiMovebg* this, PlayState* play) {
    this->unk_1CC = func_80AF705C(this, this->unk_1CC);
    if (this->unk_1CC & 0xC) {
        if (this->unk_1CC & 4) {
            this->unk_1CC |= 2;
        }
        this->actionFunc = func_80AF71FC;
        return;
    }
    if (this->unk_1CC & 0x10) {
        if (!(this->unk_1CE & 0x10)) {
            Actor_PlaySfx(&this->dyna.actor, 0x2979U);
        }
        Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y - 8.0f, 1.0f, 2.0f, 0.01f);
        return;
    }
    if (this->unk_1CE & 0x10) {
        Actor_PlaySfx(&this->dyna.actor, 0x297AU);
    }
    Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 1.0f, 2.0f, 0.01f);
}

s32 func_80AF6DE0(PlayState*, ActorPathing*);
void func_80AF72F8(BgDanpeiMovebg*, PlayState*);
void func_80AF7354(BgDanpeiMovebg*, PlayState*);
void func_80AF746C(BgDanpeiMovebg*, PlayState*);

void func_80AF71FC(BgDanpeiMovebg* this, PlayState* play) {
    SubS_ActorPathing_Update(play, &this->actorPath, SubS_ActorPathing_ComputePointInfo, func_80AF6DE0,
                             SubS_ActorPathing_MoveWithoutGravityReverse, SubS_ActorPathing_SetNextPoint);
    Actor_PlaySfx_Flagged(&this->dyna.actor, 0x2103U);
    if (this->actorPath.flags & 0x80) {
        if (this->unk_1CC & 2) {
            this->unk_1CC &= ~0x2;
        }
        this->actionFunc = func_80AF72F8;
        return;
    }
    this->unk_1CC = func_80AF705C(this, this->unk_1CC);
    if ((this->unk_1CC & 0x10) || ((this->unk_1CC & 0xC) == 0xC)) {
        this->actionFunc = func_80AF746C;
        return;
    }
    if (!(this->unk_1CC & 0x1C)) {
        this->actorPath.flags |= 8;
        this->dyna.actor.speed = 2.0f;
        this->actionFunc = func_80AF7354;
    }
}

void func_80AF72F8(BgDanpeiMovebg* this, PlayState* play) {
    this->unk_1CC = func_80AF705C(this, this->unk_1CC);
    if (!(this->unk_1CC & 0x1C)) {
        this->actorPath.flags |= 8;
        this->dyna.actor.speed = 2.0f;
        this->actionFunc = func_80AF7354;
    }
}

void func_80AF7354(BgDanpeiMovebg* this, PlayState* play) {
    Actor_PlaySfx_Flagged(&this->dyna.actor, 0x2103U);
    this->unk_1CC = func_80AF705C(this, this->unk_1CC);
    SubS_ActorPathing_Update(play, &this->actorPath, SubS_ActorPathing_ComputePointInfo, func_80AF6DE0,
                             SubS_ActorPathing_MoveWithoutGravityReverse, SubS_ActorPathing_SetNextPoint);
    if ((this->unk_1CC & 0x10) || (this->unk_1CC & 0xC) == 0xC) {
        this->actionFunc = func_80AF746C;
    } else if ((this->unk_1CC & 0xC) && (this->unk_1CC & 0xC) != 0xC) {
        this->actorPath.flags &= 0xFFF7;
        this->dyna.actor.speed = 1.0f;
        if (this->unk_1CC & 4) {
            this->unk_1CC = this->unk_1CC | 2;
        }
        this->actionFunc = func_80AF71FC;
    }
    if (this->actorPath.flags & 0x80) {
        this->actorPath.flags = this->actorPath.flags & 0xFFF7;
        this->unk_1CC &= 0xFFFD;
        this->dyna.actor.speed = 1.0f;
        this->actionFunc = func_80AF70FC;
    }
}

void func_80AF746C(BgDanpeiMovebg* this, PlayState* arg1) {
    this->unk_1CC = func_80AF705C(this, this->unk_1CC);
    if (!(this->unk_1CC & 0x18)) {
        if (this->actorPath.flags & 8) {
            this->actionFunc = func_80AF7354;
        } else {
            this->actionFunc = func_80AF71FC;
        }
    }
}

void func_80AF74CC(Actor* thisx, PlayState* play) {
    BgDanpeiMovebg* this = THIS;
    if (this->unk_1D0 != NULL) {
        Gfx_DrawDListOpa(play, this->unk_1D0);
    }
}
