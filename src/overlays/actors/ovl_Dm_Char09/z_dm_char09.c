/*
 * File: z_dm_char09.c
 * Overlay: ovl_Dm_Char09
 * Description: Pirates' Fortress cutscene characters
 */

#include "z_dm_char09.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar09*)thisx)

void DmChar09_Init(Actor* thisx, PlayState* play);
void DmChar09_Destroy(Actor* thisx, PlayState* play);
void DmChar09_Update(Actor* thisx, PlayState* play);
void DmChar09_Draw(Actor* thisx, PlayState* play);

void DmChar09_DoNothing(DmChar09* this, PlayState* play);
void func_80AB2268(DmChar09* this, PlayState* play);

const ActorInit Dm_Char09_InitVars = {
    ACTOR_DM_CHAR09,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BEE,
    sizeof(DmChar09),
    (ActorFunc)DmChar09_Init,
    (ActorFunc)DmChar09_Destroy,
    (ActorFunc)DmChar09_Update,
    (ActorFunc)DmChar09_Draw,
};

static AnimationInfo sAnimations[] = { { &object_bee_Anim_00005C, 1.0f, 0.0f, -1.0f, 0, 0.0f } };

void DmChar09_ChangeAnimation(SkelAnime* skelAnime, AnimationInfo* animation, u16 index) {
    f32 frameCount;

    animation += index;

    if (animation->frameCount < 0.0f) {
        frameCount = Animation_GetLastFrame(animation->animation);
    } else {
        frameCount = animation->frameCount;
    }

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                     animation->mode, animation->morphFrames);
}

void DmChar09_Init(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_Init(play, &this->skelAnime, &object_bee_Skel_001398, &object_bee_Anim_00005C, this->jointTable,
                   this->morphTable, OBJECT_BEE_LIMB_MAX);
    DmChar09_ChangeAnimation(&this->skelAnime, sAnimations, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_228 = Rand_ZeroOne() * 65535.0f;
    this->unk_22A = Rand_ZeroOne() * 65535.0f;
    this->actionFunc = DmChar09_DoNothing;
}

void DmChar09_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AB1FA0(DmChar09* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->unk_224[arg1]);
}

void func_80AB1FDC(DmChar09* this, PlayState* play) {
    Actor* thisx = &this->actor;
    Vec3f sp58;
    f32 sp54;
    f32 phi_fa0;
    f32 phi_fv0;
    Vec3f sp40;
    s32 phi_a1;
    Vec3s* temp_v1;

    Math_Vec3f_Copy(&sp40, &thisx->world.pos);
    Math_Vec3s_ToVec3f(&sp58, this->unk_224 + this->unk_21C + this->unk_220);
    Math_Vec3f_Diff(&sp58, &thisx->world.pos, &thisx->velocity);
    sp54 = Math3D_Vec3fMagnitude(&thisx->velocity);
    if ((sp54 < (this->speed * 8.0f)) && (this->speed > 2.0f)) {
        phi_fv0 = ((this->speed - 2.0f) * 0.1f) + 2.0f;
        phi_fa0 = this->speed * 0.03f;
    } else {
        phi_fv0 = this->speed;
        phi_fa0 = this->speed * 0.16f;
    }
    Math_StepToF(&thisx->speedXZ, phi_fv0, phi_fa0);
    if ((thisx->speedXZ + 0.05f) < sp54) {
        Math_Vec3f_Scale(&thisx->velocity, thisx->speedXZ / sp54);
        thisx->world.pos.x += thisx->velocity.x;
        thisx->world.pos.y += thisx->velocity.y;
        thisx->world.pos.z += thisx->velocity.z;
    } else {
        this->unk_21C += this->unk_220;
        thisx->speedXZ *= 0.4f;
        phi_a1 = 1;
        if (((this->unk_21C >= this->unk_218) && (this->unk_220 > 0)) ||
            ((this->unk_21C <= 0) && (this->unk_220 < 0))) {
            temp_v1 = this->unk_224 + this->unk_218;
            if (((this->unk_224->x == temp_v1->x) && (this->unk_224->y == temp_v1->y)) &&
                (this->unk_224->z == temp_v1->z)) {
                this->unk_21C = 0;
                this->unk_220 = 1;
            } else {
                phi_a1 = 0;
                this->actionFunc = func_80AB2268;
            }
        }
        if (phi_a1) {
            func_80AB1FA0(this, this->unk_21C);
        }
    }
    Math_SmoothStepToS(&thisx->world.rot.y, Math_Vec3f_Yaw(&thisx->world.pos, &sp40) + 0x7FFF, 1, 0x7D0, 0);
    thisx->shape.rot.y = thisx->world.rot.y;
}

void DmChar09_DoNothing(DmChar09* this, PlayState* play) {
}

void func_80AB2268(DmChar09* this, PlayState* play) {
    Path* path;
    s32 pad;
    s32 i;
    s32 actionIndex;
    s32 action = 0;
    s32 pathnum;
    u8 csIndex = 0;

    if (!(this->actor.params & 0xF)) {
        if (play->csCtx.currentCsIndex == 1) {
            csIndex = 1;
        }
    } else if (play->csCtx.currentCsIndex == 0) {
        csIndex = 1;
    }

    if (Cutscene_CheckActorAction(play, 0x1F7) && (csIndex != 0)) {
        actionIndex = Cutscene_GetActorActionIndex(play, 0x1F7);
        if (this->unk_22F != play->csCtx.actorActions[actionIndex]->action) {
            this->unk_22F = play->csCtx.actorActions[actionIndex]->action;
            switch (play->csCtx.actorActions[actionIndex]->action) {
                case 2:
                    action = 0;
                    break;
                case 3:
                    action = 1;
                    break;
                case 4:
                    action = 2;
                    break;
                case 5:
                    action = 3;
                    break;
            }

            if (play->csCtx.actorActions[actionIndex]->action >= 2) {
                pathnum = (this->actor.params >> 4) & 0xF;
                path = &play->setupPathList[pathnum];

                for (i = 0; i < action; i++) {
                    pathnum = path->unk1;
                    path = &play->setupPathList[pathnum];
                }

                this->unk_224 = Lib_SegmentedToVirtual(path->points);
                this->unk_214 = path->count;
                this->unk_21C = 0;
                this->unk_218 = path->count - 1;
                this->unk_220 = 1;
                this->unk_22E = 1;

                this->speed = (u16)play->csCtx.actorActions[actionIndex]->rot.z * 0.00390625f;
                this->actionFunc = func_80AB1FDC;
            } else {
                this->unk_22E = 0;
                this->actionFunc = DmChar09_DoNothing;
            }
        }
    } else {
        this->unk_22F = 0x63;
    }
}

void func_80AB24BC(DmChar09* this, PlayState* play) {
    this->unk_228 += 0xBB8;
    this->unk_22A += 0x1388;
    this->unk_204 = Math_SinS(this->unk_228) * 150.0f;
    this->unk_208 = Math_SinS(this->unk_22A) * 150.0f;
    this->unk_20C = Math_SinS(this->unk_228) * 150.0f;
}

void DmChar09_Update(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    func_80AB2268(this, play);
    func_80AB24BC(this, play);
    if ((play->csCtx.state != 0) && (this->unk_22E) && (this->actor.params & 0x100)) {
        Actor_PlaySfxAtPos(&this->actor, 0x304A);
    }
}

s32 DmChar09_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmChar09* this = THIS;

    Matrix_Translate(this->unk_204, this->unk_208, this->unk_20C, MTXMODE_APPLY);
    return 0;
}

void DmChar09_Draw(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    if ((play->csCtx.state != 0) && this->unk_22E) {
        func_8012C28C(play->state.gfxCtx);
        func_8012C2DC(play->state.gfxCtx);
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, DmChar09_OverrideLimbDraw, NULL,
                          &this->actor);
    }
}
