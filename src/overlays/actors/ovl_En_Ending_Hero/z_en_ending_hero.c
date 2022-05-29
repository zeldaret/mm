/*
 * File: z_en_ending_hero.c
 * Overlay: ovl_En_Ending_Hero
 * Description: Mayor Dotour at wedding during the credits
 */

#include "z_en_ending_hero.h"
#include "objects/object_dt/object_dt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

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

void EnEndingHero_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dt_Skel_00B0CC, &object_dt_Anim_000BE0, this->jointTable,
                       this->morphTable, 15);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    func_80C1E748(this);
}

void EnEndingHero_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C1E748(EnEndingHero* this) {
    this->unk244 = 1;
    this->actionFunc = func_80C1E764;
}

void func_80C1E764(EnEndingHero* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
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
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

static TexturePtr D_80C1E970[] = {
    object_dt_Tex_007350, object_dt_Tex_009590, object_dt_Tex_009F90, object_dt_Tex_00A790, object_dt_Tex_00AB90,
};
static TexturePtr D_80C1E984[] = {
    object_dt_Tex_007750,
    object_dt_Tex_00A390,
    object_dt_Tex_00A490,
};

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
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
