/*
 * File: z_en_baisen.c
 * Overlay: ovl_En_Baisen
 * Description: Viscen (leader of the guards in Clock Town)
 */

#include "z_en_baisen.h"
#include "objects/object_bai/object_bai.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBaisen*)thisx)

void EnBaisen_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BE87B0(EnBaisen* this, GlobalContext* globalCtx);
void func_80BE87FC(EnBaisen* this);
void func_80BE887C(EnBaisen* this, GlobalContext* globalCtx);
void func_80BE895C(EnBaisen* this, GlobalContext* globalCtx);
void func_80BE8AAC(EnBaisen* this, GlobalContext* globalCtx);
void func_80BE89D8(EnBaisen* this, GlobalContext* globalCtx);

const ActorInit En_Baisen_InitVars = {
    ACTOR_EN_BAISEN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAI,
    sizeof(EnBaisen),
    (ActorFunc)EnBaisen_Init,
    (ActorFunc)EnBaisen_Destroy,
    (ActorFunc)EnBaisen_Update,
    (ActorFunc)EnBaisen_Draw,
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
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

static u16 sTextIds[] = { 0x2ABD, 0x2ABB, 0x2AD5, 0x2AD6, 0x2AD7, 0x2AD8, 0x2AC6 };

static AnimationHeader* D_80BE8E4C[] = { &object_bai_Anim_0011C0, &object_bai_Anim_0008B4, &object_bai_Anim_008198 };

static u8 animModes[] = { ANIMMODE_LOOP, ANIMMODE_LOOP };

void EnBaisen_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBaisen* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_bai_Skel_007908, &object_bai_Anim_0011C0, this->jointTable,
                       this->morphTable, 20);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->paramCopy = this->actor.params;
    if (this->actor.params == 0) {
        this->unk290 = true;
        if (!(gSaveContext.save.weekEventReg[63] & 0x80) &&
            ((gSaveContext.save.day != 3) || !gSaveContext.save.isNight)) {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        this->collider.dim.radius = 30;
        this->collider.dim.height = 60;
        this->collider.dim.yShift = 0;
        if ((gSaveContext.save.weekEventReg[63] & 0x80) ||
            ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight))) {
            Actor_MarkForDeath(&this->actor);
        }
    }
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    if (this->paramCopy == 0) {
        this->actionFunc = func_80BE87B0;
    } else {
        func_80BE87FC(this);
    }
}

void EnBaisen_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBaisen* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnBaisen_ChangeAnimation(EnBaisen* this, s32 animIndex) {
    this->animIndex = animIndex;
    this->frameCount = Animation_GetLastFrame(D_80BE8E4C[animIndex]);
    Animation_Change(&this->skelAnime, D_80BE8E4C[this->animIndex], 1.0f, 0.0f, this->frameCount,
                     animModes[this->animIndex], -10.0f);
}

void func_80BE871C(EnBaisen* this) {
    s16 yawTemp = this->unk29E - this->actor.world.rot.y;
    s32 yaw = ABS_ALT(yawTemp);

    this->headRotXTarget = 0;
    if ((this->actor.xzDistToPlayer < 200.0f) && (yaw < 0x4E20)) {
        this->headRotXTarget = this->unk29E - this->actor.world.rot.y;
        if (this->headRotXTarget > 0x2710) {
            this->headRotXTarget = 0x2710;
        } else if (this->headRotXTarget < -0x2710) {
            this->headRotXTarget = -0x2710;
        }
    }
}

void func_80BE87B0(EnBaisen* this, GlobalContext* globalCtx) {
    Actor* actorIterator = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorIterator != NULL) {
        if (actorIterator->id == ACTOR_EN_HEISHI) {
            this->heishiPointer = actorIterator;
        }
        actorIterator = actorIterator->next;
    }

    func_80BE87FC(this);
}

void func_80BE87FC(EnBaisen* this) {
    if (this->paramCopy == 0) {
        this->textIdIndex = 2;
        EnBaisen_ChangeAnimation(this, 2);
        this->unk29E = this->actor.world.rot.y;
    } else {
        EnBaisen_ChangeAnimation(this, 0);
    }

    this->actor.textId = sTextIds[this->textIdIndex];
    this->unk29C = 0;
    this->actionFunc = func_80BE887C;
}

void func_80BE887C(EnBaisen* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80BE895C(this, globalCtx);
    } else {
        if (this->paramCopy != 0) {
            this->textIdIndex = 0;
            if (gSaveContext.save.weekEventReg[60] & 8) {
                this->textIdIndex = 1;
            }
            if (Player_GetMask(globalCtx) == PLAYER_MASK_COUPLE) {
                this->textIdIndex = 6;
            }
            if (this->unk2AC == 1) {
                func_80BE895C(this, globalCtx);
                return;
            }
        }
        this->actor.textId = sTextIds[this->textIdIndex];
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80BE895C(EnBaisen* this, GlobalContext* globalCtx) {
    if (this->unk2A4 != NULL) {
        this->unk290 = true;
        this->unk2AC = 1;
        Actor_ChangeFocus(this->unk2A4, globalCtx, this->unk2A4);
    }
    this->unk29C = 1;
    if (this->paramCopy == 0) {
        this->unk2A4 = this->heishiPointer;
        this->actionFunc = func_80BE8AAC;
    } else {
        this->actionFunc = func_80BE89D8;
    }
}

void func_80BE89D8(EnBaisen* this, GlobalContext* globalCtx) {
    if (&this->actor == this->unk2A4) {
        this->unk29E = this->actor.world.rot.y;
        if (this->animIndex == 0) {
            EnBaisen_ChangeAnimation(this, 1);
        }
    } else {
        this->unk29E = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk2A4->world.pos);
        if (this->animIndex != 0) {
            EnBaisen_ChangeAnimation(this, 0);
        }
    }
    if ((globalCtx->msgCtx.currentTextId == 0x2AC6) || (globalCtx->msgCtx.currentTextId == 0x2AC7) ||
        (globalCtx->msgCtx.currentTextId == 0x2AC8)) {
        this->skelAnime.playSpeed = 0.0f;
        this->unk29E = this->actor.yawTowardsPlayer;
    }
    if (this->unk2AC == 2) { // Note: This variable is only ever set to 1.
        func_80BE87FC(this);
    }
}

void func_80BE8AAC(EnBaisen* this, GlobalContext* globalCtx) {
    if ((this->textIdIndex % 2) != 0) {
        this->unk29E = this->actor.world.rot.y;
        if (this->animIndex == 0) {
            EnBaisen_ChangeAnimation(this, 1);
        }
    } else {
        if (this->unk2A4 != NULL) {
            this->unk29E = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk2A4->world.pos);
        }
        if (this->animIndex != 0) {
            EnBaisen_ChangeAnimation(this, 0);
        }
    }
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        this->textIdIndex++;
        if (this->textIdIndex < 6) {
            func_80151938(globalCtx, sTextIds[this->textIdIndex]);
            if ((this->textIdIndex % 2) == 0) {
                this->unk2A4 = this->heishiPointer;
            } else {
                this->unk2A4 = &this->actor;
            }
            Actor_ChangeFocus(this->unk2A4, globalCtx, this->unk2A4);
        } else {
            func_80BE87FC(this);
        }
    }
}

void EnBaisen_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBaisen* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    if (this->unusedCounter != 0) {
        this->unusedCounter--;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if ((this->paramCopy != 0) && (gSaveContext.save.day == 3) && gSaveContext.save.isNight) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    Actor_SetScale(&this->actor, 0.01f);
    if (this->unk290) {
        func_80BE871C(this);
    }
    Actor_SetFocus(&this->actor, 60.0f);
    Math_SmoothStepToS(&this->headRotX, this->headRotXTarget, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->headRotY, this->headRotYTarget, 1, 0x3E8, 0);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnBaisen_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    EnBaisen* this = THIS;

    if (limbIndex == 9) {
        rot->x += this->headRotX;
        rot->y += this->headRotY;
        rot->z += this->headRotZ;
    }

    return false;
}

void EnBaisen_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBaisen* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBaisen_OverrideLimbDraw, NULL, &this->actor);
}
