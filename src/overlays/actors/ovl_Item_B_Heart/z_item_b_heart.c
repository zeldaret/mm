#include "z_item_b_heart.h"
#include "objects/object_gi_hearts/object_gi_hearts.h"

#define FLAGS 0x00000000

#define THIS ((ItemBHeart*)thisx)

void ItemBHeart_Init(Actor* thisx, PlayState* play);
void ItemBHeart_Destroy(Actor* thisx, PlayState* play);
void ItemBHeart_Update(Actor* thisx, PlayState* play);
void ItemBHeart_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Item_B_Heart_InitVars = {
    /**/ ACTOR_ITEM_B_HEART,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_GI_HEARTS,
    /**/ sizeof(ItemBHeart),
    /**/ ItemBHeart_Init,
    /**/ ItemBHeart_Destroy,
    /**/ ItemBHeart_Update,
    /**/ ItemBHeart_Draw,
};
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_B_Heart/ItemBHeart_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_B_Heart/ItemBHeart_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_B_Heart/ItemBHeart_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_B_Heart/func_808BCF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_B_Heart/ItemBHeart_Draw.s")
