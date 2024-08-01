#ifndef Z64INVENTORY_H
#define Z64INVENTORY_H

#include "PR/ultratypes.h"

struct PlayState;

s32 Inventory_GetBtnBItem(struct PlayState* play);
void Inventory_ChangeEquipment(s16 value);
u8 Inventory_DeleteEquipment(struct PlayState* play, s16 equipment);
void Inventory_ChangeUpgrade(s16 upgrade, u32 value);
s32 Inventory_IsMapVisible(s16 sceneId);
void Inventory_SetWorldMapCloudVisibility(s16 tingleIndex);
void Inventory_SaveDekuPlaygroundHighScore(s16 timerId);
void Inventory_IncrementSkullTokenCount(s16 sceneIndex);
s16 Inventory_GetSkullTokenCount(s16 sceneIndex);
void Inventory_SaveLotteryCodeGuess(struct PlayState* play);

extern u32 gBitFlags[32];
extern u16 gEquipMasks[];
extern u16 gEquipNegMasks[];
extern u32 gUpgradeMasks[8];
extern u32 gUpgradeNegMasks[];
extern u8 gEquipShifts[];
extern u8 gUpgradeShifts[8];
extern u16 gUpgradeCapacities[][4];
extern u32 gGsFlagsMask[];
extern u32 gGsFlagsShift[];
extern TexturePtr gItemIcons[];
extern u8 gItemSlots[];
extern s16 gItemPrices[];
extern u16 gSceneIdsPerRegion[11][27];
extern u8 gPlayerFormItemRestrictions[][114];

#endif
