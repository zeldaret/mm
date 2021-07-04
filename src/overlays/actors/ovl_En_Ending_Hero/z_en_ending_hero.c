#include "z_en_ending_hero.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero*)thisx)

void EnEndingHero_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1E748(EnEndingHero* this);
void func_80C1E764(EnEndingHero* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero_InitVars = {
    ACTOR_EN_ENDING_HERO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DT,
    sizeof(EnEndingHero),
    (ActorFunc)EnEndingHero_Init,
    (ActorFunc)EnEndingHero_Destroy,
    (ActorFunc)EnEndingHero_Update,
    (ActorFunc)EnEndingHero_Draw,
};

extern FlexSkeletonHeader D_0600B0CC;
extern AnimationHeader D_06000BE0;
extern UNK_PTR D_06007350[];
extern UNK_PTR D_06009590[];
extern UNK_PTR D_06009F90[];
extern UNK_PTR D_0600A790[];
extern UNK_PTR D_0600AB90[];
extern UNK_PTR D_06007750[];
extern UNK_PTR D_0600A390[];
extern UNK_PTR D_0600A490[];

void EnEndingHero_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero* this = THIS;

    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B0CC, &D_06000BE0, this->limbDrawTable,
                     this->transitionDrawTable, 15);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_80C1E748(this);
}

void EnEndingHero_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C1E748(EnEndingHero* this) {
    this->unk244 = 1;
    this->actionFunc = func_80C1E764;
}

void func_80C1E764(EnEndingHero* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void EnEndingHero_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero* this = THIS;

    if (this->unk240 == 0) {
        this->unk242 += 1;
        if (this->unk242 > 2) {
            this->unk242 = 0;
            this->unk240 = (s16)Rand_ZeroFloat(60.0f) + 0x14;
        }
    }
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

static UNK_PTR D_80C1E970[] = { D_06007350, D_06009590, D_06009F90, D_0600A790, D_0600AB90 };
static UNK_PTR D_80C1E984[] = { D_06007750, D_0600A390, D_0600A490 };

void EnEndingHero_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero* this = THIS;
    s32 index = 0;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C1E970[this->unk242]));

    if (this->unk242 < 3) {
        index = this->unk242;
    }

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C1E984[index]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, 0, 0,
                     &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
