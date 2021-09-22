#include "z_en_ending_hero6.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero6*)thisx)

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C23D60(EnEndingHero6* this, s32 npcIndex);
void func_80C23DDC(EnEndingHero6* this);
void func_80C23E18(EnEndingHero6* this, GlobalContext* globalCtx);

#if 0
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
#endif

extern FlexSkeletonHeader* D_80C24200[];
extern AnimationHeader* D_80C24224[];

extern s32 D_80C24248[];

// object_daiku
extern Gfx* D_80C2426C[];

// object_dt
extern TexturePtr D_80C24280[];
extern TexturePtr D_80C24294[];

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero6* this = THIS;

    this->actor.colChkInfo.mass = 255;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, D_80C24200[this->npcIndex], D_80C24224[this->npcIndex],
                     this->limbDrawTable, this->transitionDrawTable, D_80C24248[this->npcIndex]);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_80C23DDC(this);
}

void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C23D60(EnEndingHero6* this, s32 npcIndex) {
    this->animIndex = npcIndex;
    this->frameCount = SkelAnime_GetFrameCount(&D_80C24224[npcIndex]->common);
    SkelAnime_ChangeAnim(&this->skelAnime, D_80C24224[this->animIndex], 1.0f, 0.f, this->frameCount, 0, 0.0f);
}

void func_80C23DDC(EnEndingHero6* this) {
    func_80C23D60(this, this->npcIndex);
    this->unk290 = 1;
    this->actionFunc = func_80C23E18;
}

void func_80C23E18(EnEndingHero6* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero6* this = THIS;

    if (this->unk286 != 0) {
        this->unk286--;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (this->unk288 == 0) {
        this->eyeState++;
        if (this->eyeState >= 3) {
            this->eyeState = 0;
            this->unk288 = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1DU);
}

void func_80C23F14(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
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
    EnEndingHero6* this = THIS;
    s32 pad;
    s32 index = 0;

    if (this->unk290 == 1) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);

        if (this->unk284 >= 0) {
            if (Object_IsLoaded(&globalCtx->objectCtx, this->unk284) != 0) {
                gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->unk284].segment);

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

                SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                 this->skelAnime.dListCount, NULL, func_80C23F14, &this->actor);
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
