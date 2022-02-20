/*
 * File: z_en_ending_hero6.c
 * Overlay: ovl_En_Ending_Hero6
 * Description:
 */

#include "z_en_ending_hero6.h"
#include "objects/object_dt/object_dt.h"
#include "objects/object_daiku/object_daiku.h"
#include "objects/object_bai/object_bai.h"
#include "objects/object_toryo/object_toryo.h"
#include "objects/object_sdn/object_sdn.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnEndingHero6*)thisx)

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnEndingHero6_InitSkelAnime(EnEndingHero6* this, s32 npcIndex);
void EnEndingHero6_SetupIdle(EnEndingHero6* this);
void EnEndingHero6_Idle(EnEndingHero6* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero6_InitVars = {
    ACTOR_EN_ENDING_HERO6,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnEndingHero6),
    (ActorFunc)EnEndingHero6_Init,
    (ActorFunc)EnEndingHero6_Destroy,
    (ActorFunc)EnEndingHero6_Update,
    (ActorFunc)EnEndingHero6_Draw,
};

static FlexSkeletonHeader* sSkeletons[] = {
    &object_dt_Skel_00B0CC,    &object_bai_Skel_007908,   &object_toryo_Skel_007150,
    &gSoldierSkeleton,         &object_daiku_Skel_00A850, &object_daiku_Skel_00A850,
    &object_daiku_Skel_00A850, &object_daiku_Skel_00A850, &object_daiku_Skel_00A850,
};

static AnimationHeader* sAnimations[] = {
    &object_dt_Anim_000BE0,    &object_bai_Anim_0011C0,   &object_toryo_Anim_000E50,
    &gSoldierCheerWithSpear,   &object_daiku_Anim_002FA0, &object_daiku_Anim_002FA0,
    &object_daiku_Anim_002FA0, &object_daiku_Anim_002FA0, &object_daiku_Anim_002FA0,
};

static s32 sLimbCounts[] = { 15, 20, 17, 17, 17, 17, 17, 17, 17 };

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero6* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, sSkeletons[this->npcIndex], sAnimations[this->npcIndex],
                       this->jointTable, this->morphTable, sLimbCounts[this->npcIndex]);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    EnEndingHero6_SetupIdle(this);
}

void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnEndingHero6_InitSkelAnime(EnEndingHero6* this, s32 npcIndex) {
    this->animIndex = npcIndex;
    this->frameCount = Animation_GetLastFrame(sAnimations[npcIndex]);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.f, this->frameCount, 0, 0.0f);
}

void EnEndingHero6_SetupIdle(EnEndingHero6* this) {
    EnEndingHero6_InitSkelAnime(this, this->npcIndex);
    this->isIdle = 1;
    this->actionFunc = EnEndingHero6_Idle;
}

void EnEndingHero6_Idle(EnEndingHero6* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero6* this = THIS;

    if (this->timer != 0) {
        this->timer--;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (this->blinkTimer == 0) {
        this->eyeState++;
        if (this->eyeState >= 3) {
            this->eyeState = 0;
            this->blinkTimer = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

void EnEndingHero6_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Gfx* D_80C2426C[] = { object_daiku_DL_0070C0, object_daiku_DL_006FB0, object_daiku_DL_006E80,
                                 object_daiku_DL_006D70, object_daiku_DL_00A390 };
    EnEndingHero6* this = THIS;
    s32 index;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->npcIndex >= 4 && limbIndex == 15) {
        index = this->npcIndex - 4;
        gSPDisplayList(POLY_OPA_DISP++, D_80C2426C[index]);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnEndingHero6_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80C24280[] = { object_dt_Tex_007350, object_dt_Tex_009590, object_dt_Tex_009F90,
                                       object_dt_Tex_00A790, object_dt_Tex_00AB90 };
    static TexturePtr D_80C24294[] = { object_dt_Tex_007750, object_dt_Tex_00A390, object_dt_Tex_00A490 };
    s32 pad;
    EnEndingHero6* this = THIS;
    s32 index = 0;

    if (this->isIdle == 1) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);

        if (this->objectIndex >= 0 && Object_IsLoaded(&globalCtx->objectCtx, this->objectIndex)) {
            gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->objectIndex].segment);

            switch (this->npcIndex) {
                case 4:
                    gDPSetEnvColor(POLY_OPA_DISP++, 170, 10, 70, 255);
                    break;
                case 5:
                    gDPSetEnvColor(POLY_OPA_DISP++, 170, 200, 255, 255);
                    break;
                case 6:
                    gDPSetEnvColor(POLY_OPA_DISP++, 0, 230, 70, 255);
                    break;
                case 7:
                    gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 150, 255);
                    break;
                case 8:
                    gDPSetEnvColor(POLY_OPA_DISP++, 245, 155, 0, 255);
                    break;
            }

            if (this->npcIndex == 0) {
                gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C24280[this->eyeState]));

                if (this->eyeState < 3) {
                    index = this->eyeState;
                }

                gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C24294[index]));
            }

            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, NULL, EnEndingHero6_PostLimbDraw, &this->actor);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
