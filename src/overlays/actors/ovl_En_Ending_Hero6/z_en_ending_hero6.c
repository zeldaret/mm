/*
 * File: z_en_ending_hero6.c
 * Overlay: ovl_En_Ending_Hero6
 * Description:
 */

#include "z_en_ending_hero6.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero6*)thisx)

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnEndingHero6_InitSkelAnime(EnEndingHero6* this, s32 npcIndex);
void EnEndingHero6_SetupIdle(EnEndingHero6* this);
void EnEndingHero6_Idle(EnEndingHero6* this, GlobalContext* globalCtx);

extern FlexSkeletonHeader D_0600B0CC; // object_dt
extern FlexSkeletonHeader D_06007908; // object_bai
extern FlexSkeletonHeader D_06007150; // object_toryo
extern FlexSkeletonHeader D_0600D640; // object_sdn
extern FlexSkeletonHeader D_0600A850; // object_daiku

extern AnimationHeader D_06000BE0; // object_dt
extern AnimationHeader D_060011C0; // object_bai
extern AnimationHeader D_06000E50; // object_toryo
extern AnimationHeader D_06002A84; // object_sdn
extern AnimationHeader D_06002FA0; // object_daiku

// object_daiku
extern Gfx D_060070C0[];
extern Gfx D_06006FB0[];
extern Gfx D_06006E80[];
extern Gfx D_06006D70[];
extern Gfx D_0600A390_dl[];

// object_dt
extern TexturePtr D_06007350;
extern TexturePtr D_06009590;
extern TexturePtr D_06009F90;
extern TexturePtr D_0600A790;
extern TexturePtr D_0600AB90;

extern TexturePtr D_06007750;
extern TexturePtr D_0600A390_tex;
extern TexturePtr D_0600A490;

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

static FlexSkeletonHeader* sSkeletons[] = { &D_0600B0CC, &D_06007908, &D_06007150, &D_0600D640, &D_0600A850,
                                            &D_0600A850, &D_0600A850, &D_0600A850, &D_0600A850 };

static AnimationHeader* sAnimations[] = { &D_06000BE0, &D_060011C0, &D_06000E50, &D_06002A84, &D_06002FA0,
                                          &D_06002FA0, &D_06002FA0, &D_06002FA0, &D_06002FA0 };

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
    static Gfx* D_80C2426C[] = { D_060070C0, D_06006FB0, D_06006E80, D_06006D70, D_0600A390_dl };
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
    static TexturePtr D_80C24280[] = { &D_06007350, &D_06009590, &D_06009F90, &D_0600A790, &D_0600AB90 };
    static TexturePtr D_80C24294[] = { &D_06007750, &D_0600A390_tex, &D_0600A490 };
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
