/*
 * File: z_bg_heavy_block.c
 * Overlay: ovl_Bg_Heavy_Block
 * Description: Large block that can only be lifted with Golden Gauntlets
 */

#include "z_bg_heavy_block.h"

#include "versions.h"

#define FLAGS 0

void BgHeavyBlock_Init(Actor* thisx, PlayState* play);
void BgHeavyBlock_Destroy(Actor* thisx, PlayState* play);
void BgHeavyBlock_Update(Actor* thisx, PlayState* play);
void BgHeavyBlock_Draw(Actor* thisx, PlayState* play);

ActorProfile Bg_Heavy_Block_Profile = {
    /**/ ACTOR_BG_HEAVY_BLOCK,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_HEAVY_OBJECT,
    /**/ sizeof(BgHeavyBlock),
    /**/ BgHeavyBlock_Init,
    /**/ BgHeavyBlock_Destroy,
    /**/ BgHeavyBlock_Update,
    /**/ BgHeavyBlock_Draw,
};

void BgHeavyBlock_Init(Actor* thisx, PlayState* play) {
}

void BgHeavyBlock_Destroy(Actor* thisx, PlayState* play) {
}

void BgHeavyBlock_Update(Actor* thisx, PlayState* play) {
}

void BgHeavyBlock_Draw(Actor* thisx, PlayState* play) {
}
