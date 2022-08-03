/*
 * File: z_oceff_wipe5.c
 * Overlay: ovl_Oceff_Wipe5
 * Description: Sonata/Lullaby/Bossa Nova/Elegy/Oath Ocarina Effect
 */

#include "z_oceff_wipe5.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe5*)thisx)

void OceffWipe5_Init(Actor* thisx, PlayState* play);
void OceffWipe5_Destroy(Actor* thisx, PlayState* play);
void OceffWipe5_Update(Actor* thisx, PlayState* play);
void OceffWipe5_Draw(Actor* thisx, PlayState* play);

#if 0
const ActorInit Oceff_Wipe5_InitVars = {
    ACTOR_OCEFF_WIPE5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe5),
    (ActorFunc)OceffWipe5_Init,
    (ActorFunc)OceffWipe5_Destroy,
    (ActorFunc)OceffWipe5_Update,
    (ActorFunc)OceffWipe5_Draw,
};

#endif

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Init.s")

void OceffWipe5_Init(Actor *thisx, PlayState *play) {
    OceffWipe5 *this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->unk144 = 0;
    this->actor.world.pos = play->cameraPtrs[play->activeCamId]->eye;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Destroy.s")

void OceffWipe5_Destroy(Actor *thisx, PlayState *play) {
    OceffWipe5 *this = THIS;

    func_80115D5C(&play->state);
    play->msgCtx.unk120B0 = 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Update.s")

void OceffWipe5_Update(Actor *thisx, PlayState *play) {
    OceffWipe5 *this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->unk144 < 800) {
        this->unk144++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Draw.s")
