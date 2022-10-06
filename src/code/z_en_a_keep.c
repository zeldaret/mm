#include "global.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnAObj*)thisx)

void EnAObj_Init(Actor* thisx, PlayState* play);
void EnAObj_Destroy(Actor* thisx, PlayState* play);
void EnAObj_Update(Actor* thisx, PlayState* play);
void EnAObj_Draw(Actor* thisx, PlayState* play);

void EnAObj_Update1(EnAObj* this, PlayState* play);
void EnAObj_Update2(EnAObj* this, PlayState* play);

ActorInit En_A_Obj_InitVars = {
    ACTOR_EN_A_OBJ,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnAObj),
    (ActorFunc)EnAObj_Init,
    (ActorFunc)EnAObj_Destroy,
    (ActorFunc)EnAObj_Update,
    (ActorFunc)EnAObj_Draw,
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
        TOUCH_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 25, 60, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN(ICHAINTYPE_U8, targetMode, 0, ICHAIN_STOP),
};

void EnAObj_Init(Actor* thisx, PlayState* play) {
    EnAObj* this = THIS;

    this->actor.textId = ((this->actor.params >> 8) & 0xFF) | 0x300;
    this->actor.params = (this->actor.params & 0xFF) - 9;
    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0, ActorShadow_DrawCircle, 12);
    Collider_InitAndSetCylinder(play, &this->collision, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collision);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actionFunc = EnAObj_Update1;
}

void EnAObj_Destroy(Actor* thisx, PlayState* play) {
    EnAObj* this = THIS;

    Collider_DestroyCylinder(play, &this->collision);
}

void EnAObj_Update1(EnAObj* this, PlayState* play) {
    s32 yawDiff;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = EnAObj_Update2;
    } else {
        yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y));

        if ((yawDiff < 0x2800) || ((this->actor.params == 1) && (yawDiff > 0x5800))) {
            func_800B863C(&this->actor, play);
        }
    }
}

void EnAObj_Update2(EnAObj* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->actionFunc = EnAObj_Update1;
    }
}

void EnAObj_Update(Actor* thisx, PlayState* play) {
    EnAObj* this = THIS;

    this->actionFunc(this, play);
    Actor_SetFocus(&this->actor, 45.0f);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collision.base);
}

static Gfx* sDLists[] = {
    gSignRectangularDL,
    gSignDirectionalDL,
};

void EnAObj_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, sDLists[thisx->params]);
}
