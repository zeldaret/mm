#include "global.h"

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012300C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012301C.s")

// OoT's Player_SetBootData?
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123140.s")

s32 Player_InBlockingCsMode(GameState* gameState, Player* player) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    return (player->stateFlags1 & 0x20000280) || player->unk_394 != 0 || globalCtx->sceneLoadFlag == 0x14 ||
           globalCtx->unk_18B4A != 0 || (player->stateFlags1 & 1) || (player->stateFlags3 & 0x80) ||
           globalCtx->actorCtx.unk268 != 0;
}

s32 Player_InCsMode(GameState* gameState) {
    Player* player = GET_PLAYER(gameState);

    return Player_InBlockingCsMode(gameState, player) || player->unk_AA5 == 5;
}

s32 func_80123420(Player* player) {
    return player->stateFlags3 & 0x80000000;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123434.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123448.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801234B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801234D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123590.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801235DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012364C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123810.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123960.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801239AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/Player_IsBurningStickInRange.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124020.s")

u8 Player_GetMask(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->currentMask;
}

void Player_RemoveMask(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->currentMask = PLAYER_MASK_NONE;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012405C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124088.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801240C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801240DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124110.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124148.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124168.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124190.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801241B4.s")

s32 Player_ActionToBottle(Player* player, s32 actionParam) {
    s32 bottle = actionParam - PLAYER_AP_BOTTLE;

    // Relies on bottle-related action params to be contiguous
    if ((bottle >= (PLAYER_AP_BOTTLE - PLAYER_AP_BOTTLE)) && (bottle <= (PLAYER_AP_BOTTLE_FAIRY - PLAYER_AP_BOTTLE))) {
        return bottle;
    }

    return -1;
}

s32 Player_GetBottleHeld(Player* Player) {
    return Player_ActionToBottle(Player, Player->itemActionParam);
}

s32 Player_ActionToExplosive(Player* player, s32 actionParam) {
    s32 explosive = actionParam - PLAYER_AP_BOMB;

    // Relies on explosive-related action params to be contiguous
    if ((explosive >= (PLAYER_AP_BOMB-PLAYER_AP_BOMB)) && (explosive <= (PLAYER_AP_BOMBCHU-PLAYER_AP_BOMB))) {
        return explosive;
    }

    return -1;
}

s32 Player_GetExplosiveHeld(Player* player) {
    return Player_ActionToExplosive(player, player->itemActionParam);
}

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

void Player_DrawGetItemImpl(GlobalContext* globalCtx, Player* player, Vec3f* refPos, s32 drawIdPlusOne) {
    f32 sp34;

    if (player->stateFlags3 & 0x4000000) {
        sp34 = 6.0f;
    } else {
        sp34 = 14.0f;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSegments[6] = PHYSICAL_TO_VIRTUAL(player->giObjectSegment);

    gSPSegment(POLY_OPA_DISP++, 0x06, player->giObjectSegment);
    gSPSegment(POLY_XLU_DISP++, 0x06, player->giObjectSegment);

    Matrix_InsertTranslation((Math_SinS(player->actor.shape.rot.y) * 3.3f) + refPos->x, refPos->y + sp34, (Math_CosS(player->actor.shape.rot.y) * 3.3f) + refPos->z, MTXMODE_NEW);
    Matrix_InsertRotation(0, (globalCtx->gameplayFrames * 1000), 0, MTXMODE_APPLY);
    Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
    GetItem_Draw(globalCtx, drawIdPlusOne - 1);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

extern Vec3f D_801F59E8;

void Player_DrawGetItem(GlobalContext* globalCtx, Player* player) {
    if (!player->giObjectLoading || (osRecvMesg(&player->giObjectLoadQueue, NULL, 0) == 0)) {
        Vec3f refPos;
        s32 drawIdPlusOne;

        player->giObjectLoading = false;
        if ((player->actor.id == ACTOR_EN_TEST3) || ((player->transformation == PLAYER_FORM_DEKU) && (player->stateFlags1 & 0x400))) {
            refPos.x = player->actor.world.pos.x;
            refPos.z = player->actor.world.pos.z;
            if (player->actor.id == ACTOR_EN_TEST3) {
                if (player->stateFlags1 & 0x400) {
                    refPos.y = player->actor.world.pos.y + 30.0f;
                } else {
                    refPos.x = player->bodyPartsPos[0xC].x;
                    refPos.y = player->bodyPartsPos[0xC].y - 6.0f;
                    refPos.z = player->bodyPartsPos[0xC].z;
                }
            } else {
                refPos.y = player->actor.world.pos.y + 28.0f;
            }
        } else {
            Math_Vec3f_Copy(&refPos, &D_801F59E8);
        }

        drawIdPlusOne = ABS_ALT(player->unk_B2A);
        Player_DrawGetItemImpl(globalCtx, player, &refPos, drawIdPlusOne);
    }
}

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
