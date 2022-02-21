#include "global.h"

extern s32 D_801F59E0;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801226E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122744.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122760.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122868.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801229A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801229EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801229FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122BA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122D44.s")

extern u8 D_801BFDE8[PLAYER_MASK_MAX - 1];
#if 0
u8 D_801BFDE8[PLAYER_MASK_MAX - 1] = {
    ITEM_MASK_TRUTH,         // PLAYER_MASK_TRUTH
    ITEM_MASK_KAFEIS_MASK,   // PLAYER_MASK_KAFEIS_MASK
    ITEM_MASK_ALL_NIGHT,     // PLAYER_MASK_ALL_NIGHT
    ITEM_MASK_BUNNY,         // PLAYER_MASK_BUNNY
    ITEM_MASK_KEATON,        // PLAYER_MASK_KEATON
    ITEM_MASK_GARO,          // PLAYER_MASK_GARO
    ITEM_MASK_ROMANI,        // PLAYER_MASK_ROMANI
    ITEM_MASK_CIRCUS_LEADER, // PLAYER_MASK_CIRCUS_LEADER
    ITEM_MASK_POSTMAN,       // PLAYER_MASK_POSTMAN
    ITEM_MASK_COUPLE,        // PLAYER_MASK_COUPLE
    ITEM_MASK_GREAT_FAIRY,   // PLAYER_MASK_GREAT_FAIRY
    ITEM_MASK_GIBDO,         // PLAYER_MASK_GIBDO
    ITEM_MASK_DON_GERO,      // PLAYER_MASK_DON_GERO
    ITEM_MASK_KAMARO,        // PLAYER_MASK_KAMARO
    ITEM_MASK_CAPTAIN,       // PLAYER_MASK_CAPTAIN
    ITEM_MASK_STONE,         // PLAYER_MASK_STONE
    ITEM_MASK_BREMEN,        // PLAYER_MASK_BREMEN
    ITEM_MASK_BLAST,         // PLAYER_MASK_BLAST
    ITEM_MASK_SCENTS,        // PLAYER_MASK_SCENTS
    ITEM_MASK_GIANT,         // PLAYER_MASK_GIANT
    ITEM_MASK_FIERCE_DEITY,  // PLAYER_MASK_FIERCE_DEITY
    ITEM_MASK_GORON,         // PLAYER_MASK_GORON
    ITEM_MASK_ZORA,          // PLAYER_MASK_ZORA
    ITEM_MASK_DEKU,          // PLAYER_MASK_DEKU
};
#endif

u8 func_80122ED8(s32 maskIdMinusOne) {
    return D_801BFDE8[maskIdMinusOne];
}

u8 Player_CurMaskToItemId(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->currentMask != PLAYER_MASK_NONE) {
        return func_80122ED8(player->currentMask - 1);
    }

    return ITEM_NONE;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012300C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012301C.s")

extern s16 D_801BFE14[][18];

// OoT's Player_SetBootData?
void func_80123140(GlobalContext* globalCtx, Player* player) {
    s16* bootRegs;
    s32 currentBoots;
    f32 scale;

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        REG(27) = 0x4B0;
    } else {
        REG(27) = 0x7D0;
    }

    REG(48) = 0x172;

    currentBoots = player->currentBoots;
    if (currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
        if (player->stateFlags1 & PLAYER_STATE1_8000000) {
            currentBoots++;
        }
        if (player->transformation == PLAYER_FORM_GORON) {
            REG(48) = 0xC8;
        }
    } else if (currentBoots == PLAYER_BOOTS_GIANT) {
        REG(48) = 0xAA;
    }

    bootRegs = D_801BFE14[currentBoots];
    REG(19) = bootRegs[0];
    REG(30) = bootRegs[1];
    REG(32) = bootRegs[2];
    REG(34) = bootRegs[3];
    REG(35) = bootRegs[4];
    REG(36) = bootRegs[5];
    REG(37) = bootRegs[6];
    REG(38) = bootRegs[7];
    REG(39) = bootRegs[8];
    REG(43) = bootRegs[9];
    REG(45) = bootRegs[10];
    REG(68) = bootRegs[11];
    REG(69) = bootRegs[12];
    IREG(66) = bootRegs[13];
    IREG(67) = bootRegs[14];
    IREG(68) = bootRegs[15];
    IREG(69) = bootRegs[16];
    MREG(95) = bootRegs[17];

    if (globalCtx->roomCtx.currRoom.unk3 == 2) {
        REG(45) = 0x1F4;
    }

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        scale = 0.015f;
    } else {
        scale = 0.01f;
    }

    Actor_SetScale(&player->actor, scale);
}

s32 Player_InBlockingCsMode(GlobalContext* globalCtx, Player* player) {
    return (player->stateFlags1 & (PLAYER_STATE1_20000000 | PLAYER_STATE1_200 | PLAYER_STATE1_80)) ||
           player->csMode != 0 || globalCtx->sceneLoadFlag == 0x14 || globalCtx->unk_18B4A != 0 ||
           (player->stateFlags1 & PLAYER_STATE1_1) || (player->stateFlags3 & PLAYER_STATE3_80) ||
           globalCtx->actorCtx.unk268 != 0;
}

s32 Player_InCsMode(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return Player_InBlockingCsMode(globalCtx, player) || player->unk_AA5 == 5;
}

s32 func_80123420(Player* player) {
    return player->stateFlags3 & PLAYER_STATE3_80000000;
}

s32 func_80123434(Player* player) {
    return player->stateFlags1 & (PLAYER_STATE1_40000000 | PLAYER_STATE1_20000 | PLAYER_STATE1_10000);
}

s32 func_80123448(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return (player->stateFlags1 & PLAYER_STATE1_400000) &&
           (player->transformation != PLAYER_FORM_HUMAN || (!func_80123434(player) && player->unk_730 == 0));
}

s32 func_801234B0(Player* player) {
    return player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_DEKU;
}

s32 func_801234D4(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return (player->stateFlags2 & PLAYER_STATE2_8) || player->actor.speedXZ != 0.0f ||
           ((player->transformation != PLAYER_FORM_ZORA) && (player->stateFlags1 & PLAYER_STATE1_8000000)) ||
           ((player->transformation == PLAYER_FORM_ZORA) && (player->stateFlags1 & PLAYER_STATE1_8000000) &&
            (!(player->actor.bgCheckFlags & 1) || (player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER)));
}

s32 func_80123590(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags1 & PLAYER_STATE1_800) && (player->heldActor == actor)) {
        player->interactRangeActor = NULL;
        player->heldActor = NULL;
        player->actor.child = NULL;
        player->stateFlags1 &= ~PLAYER_STATE1_800;
        return 1;
    }
    return 0;
}

s32 func_801235DC(GlobalContext* globalCtx, f32 arg1, s16 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags3 & PLAYER_STATE3_1000) {
        player->unk_B08[0] = arg1;
        player->unk_B08[1] += arg1 * 0.05f;
        player->currentYaw = arg2;
        player->actor.home.rot.y = arg2;
        player->actor.shape.rot.y = arg2;
        player->unk_B8C = 4;
        player->invincibilityTimer = 20;

        return true;
    }

    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012364C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123810.s")

extern u8 sActionModelGroups[];

s32 Player_ActionToModelGroup(Player* player, s32 actionParam) {
    s32 modelGroup = sActionModelGroups[actionParam];

    if ((modelGroup == 2) && func_801234B0(player)) {
        return 1;
    }
    return modelGroup;
}

extern u8 D_801BFF90[PLAYER_FORM_MAX];
#if 0
u8 D_801BFF90[PLAYER_FORM_MAX] = {
    PLAYER_BOOTS_FIERCE_DEITY, // PLAYER_FORM_FIERCE_DEITY
    PLAYER_BOOTS_GORON,        // PLAYER_FORM_GORON
    PLAYER_BOOTS_ZORA_LAND,    // PLAYER_FORM_ZORA
    PLAYER_BOOTS_DEKU,         // PLAYER_FORM_DEKU
    PLAYER_BOOTS_HYLIAN,       // PLAYER_FORM_HUMAN
};
#endif

extern Gfx** sPlayerDListGroups[];

void func_801239AC(Player* player) {
    if (player->stateFlags1 & PLAYER_STATE1_400000) {
        if ((player->heldItemActionParam < 0) || (player->heldItemActionParam == player->itemActionParam)) {
            if (!Player_HoldsTwoHandedWeapon(player)) {
                if (!func_801234B0(player)) {
                    D_801F59E0 = player->transformation * 2;
                    player->rightHandType = 8;
                    player->rightHandDLists = &sPlayerDListGroups[8][D_801F59E0];

                    if (player->sheathType == 14) {
                        player->sheathType = 12;
                    } else if (player->sheathType == 15) {
                        player->sheathType = 13;
                    }

                    player->sheathDLists = &sPlayerDListGroups[player->sheathType][D_801F59E0];
                    player->modelAnimType = 2;
                    player->heldItemActionParam = -1;
                }
            }
        }
    }
}

void Player_SetModels(Player* player, s32 modelGroup) {
    u8* aux;

    D_801F59E0 = player->transformation * 2;
    player->leftHandType = gPlayerModelTypes[modelGroup][1];
    player->rightHandType = gPlayerModelTypes[modelGroup][2];
    player->sheathType = gPlayerModelTypes[modelGroup][3];

    if (player->sheathType == 14) {
        if (gSaveContext.equips.buttonItems[CUR_FORM][0] == ITEM_NONE) {
            player->sheathType = 15;
        }
    }

    aux = gPlayerModelTypes[modelGroup];

    player->leftHandDLists = &sPlayerDListGroups[aux[1]][D_801F59E0];
    player->rightHandDLists = &sPlayerDListGroups[aux[2]][D_801F59E0];
    player->sheathDLists = &sPlayerDListGroups[aux[3]][D_801F59E0];
    player->waistDLists = &sPlayerDListGroups[aux[4]][D_801F59E0];

    func_801239AC(player);
}

void Player_SetModelGroup(Player* player, s32 modelGroup) {
    player->modelGroup = modelGroup;

    if (modelGroup == 1) {
        player->modelAnimType = 0;
    } else {
        player->modelAnimType = gPlayerModelTypes[modelGroup][0];
    }

    if ((player->modelAnimType < 3) &&
        ((((player->transformation != PLAYER_FORM_FIERCE_DEITY)) && (player->transformation != PLAYER_FORM_HUMAN)) ||
         (player->currentShield == PLAYER_SHIELD_NONE))) {
        player->modelAnimType = 0;
    }

    Player_SetModels(player, modelGroup);
}

void func_80123C58(Player* player) {
    player->heldItemActionParam = player->itemActionParam;
    Player_SetModelGroup(player, Player_ActionToModelGroup(player, player->itemActionParam));
    player->unk_AA5 = 0;
}

void Player_SetEquipmentData(GlobalContext* globalCtx, Player* player) {
    if (player->csMode != 0x86) {
        player->currentShield = CUR_EQUIP_VALUE_VOID(EQUIP_SHIELD);
        if ((player->transformation != PLAYER_FORM_ZORA) || (((player->currentBoots != PLAYER_BOOTS_ZORA_LAND)) &&
                                                             (player->currentBoots != PLAYER_BOOTS_ZORA_UNDERWATER))) {
            player->currentBoots = D_801BFF90[player->transformation];
        }
        Player_SetModelGroup(player, Player_ActionToModelGroup(player, player->itemActionParam));
        func_80123140(globalCtx, player);
        if (player->unk_B62 != 0) {
            player->unk_B62 = 1;
        }
    }
}

void func_80123D50(GlobalContext* globalCtx, Player* player, s32 item, s32 actionParam) {
    func_80114FD0(globalCtx, item, player->heldItemButton);

    if (item != ITEM_BOTTLE) {
        player->heldItemId = item;
        player->itemActionParam = actionParam;
    }

    player->heldItemActionParam = actionParam;
}

void func_80123DA4(Player* player) {
    player->unk_730 = NULL;
    player->stateFlags2 &= ~PLAYER_STATE2_2000;
}

void func_80123DC0(Player* player) {
    if ((player->actor.bgCheckFlags & 1) ||
        (player->stateFlags1 & (PLAYER_STATE1_8000000 | PLAYER_STATE1_800000 | PLAYER_STATE1_200000)) ||
        (!(player->stateFlags1 & (PLAYER_STATE1_80000 | PLAYER_STATE1_40000)) &&
         ((player->actor.world.pos.y - player->actor.floorHeight) < 100.0f))) {
        player->stateFlags1 &= ~(PLAYER_STATE1_40000000 | PLAYER_STATE1_80000 | PLAYER_STATE1_40000 |
                                 PLAYER_STATE1_20000 | PLAYER_STATE1_10000 | PLAYER_STATE1_8000);
    } else if (!(player->stateFlags1 & (PLAYER_STATE1_200000 | PLAYER_STATE1_80000 | PLAYER_STATE1_40000))) {
        player->stateFlags1 |= PLAYER_STATE1_80000;
    } else if ((player->stateFlags1 & PLAYER_STATE1_40000) && (player->transformation == PLAYER_FORM_DEKU)) {
        player->stateFlags1 &=
            ~(PLAYER_STATE1_40000000 | PLAYER_STATE1_20000 | PLAYER_STATE1_10000 | PLAYER_STATE1_8000);
    }
    func_80123DA4(player);
}

void func_80123E90(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    func_80123DC0(player);
    player->unk_730 = actor;
    player->unk_A78 = actor;
    player->stateFlags1 |= PLAYER_STATE1_10000;
    func_800DFD78(Play_GetCamera(globalCtx, CAM_ID_MAIN), 8, actor);
    Camera_ChangeMode(Play_GetCamera(globalCtx, CAM_ID_MAIN), 9);
}

s32 func_80123F14(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->stateFlags1 & PLAYER_STATE1_800000;
}

s32 func_80123F2C(GlobalContext* globalCtx, s32 ammo) {
    globalCtx->unk_1887C = ammo + 1;

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124020.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/Player_GetMask.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/Player_RemoveMask.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012405C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124088.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801240C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801240DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124110.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124148.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124168.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124190.s")

s32 Player_HoldsTwoHandedWeapon(Player* player) {
    // Relies on two-handed weapons to be contiguous
    if ((player->itemActionParam >= PLAYER_AP_SWORD_GREAT_FAIRY) && (player->itemActionParam <= PLAYER_AP_STICK)) {
        return true;
    }

    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801241E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012420C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012422C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/Player_GetExplosiveHeld.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124278.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801242B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801242DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124420.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124618.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801246F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124870.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801251C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125318.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125340.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012536C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801253A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125500.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125580.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801262C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801263FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126440.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801265C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012669C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126808.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012697C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801271B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127438.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127488.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012754C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127594.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801278F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127A60.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128388.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801284A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128640.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128BD0.s")
