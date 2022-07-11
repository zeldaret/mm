#include "global.h"
#include "overlays/actors/ovl_Bg_Umajump/z_bg_umajump.h"

s32 func_800F3940(PlayState* play) {
    Actor* actor;

    for (actor = NULL; ; actor = actor->next) {
        actor = SubS_FindActor(play, actor, ACTORCAT_PROP, ACTOR_BG_UMAJUMP);

        if (actor == NULL) {
            break;
        }

        if (actor->params == 2) {
            return ((BgUmajump*)actor)->unk_160;
        }
    }

    return -1;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F39B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3B2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F40A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F415C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F41E4.s")
