#include "z_en_ending_hero.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero*)thisx)

void EnEndingHero_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1E748(EnEndingHero* this);

/*
const ActorInit En_Ending_Hero_InitVars = {
    ACTOR_EN_ENDING_HERO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DT,
    sizeof(EnEndingHero),
    (ActorFunc)EnEndingHero_Init,
    (ActorFunc)EnEndingHero_Destroy,
    (ActorFunc)EnEndingHero_Update,
    (ActorFunc)EnEndingHero_Draw
};
*/

extern SkeletonHeader D_0600B0CC;
extern AnimationHeader D_06000BE0;

void EnEndingHero_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnEndingHero* this = THIS;

    this->actor.unkA0.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.unk1F = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B0CC, &D_06000BE0, this->limbDrawTable, this->transitionDrawTable, 15);
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_80C1E748(this);
}

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/func_80C1E748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/func_80C1E764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Draw.asm")
