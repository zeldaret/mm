#include "global.h"

#include "objects/object_link_goron/object_link_goron.h"
#include "objects/object_link_zora/object_link_zora.h"

#include "objects/object_mask_meoto/object_mask_meoto.h"

void PlayerCall_Init(Actor* thisx, PlayState* play);
void PlayerCall_Destroy(Actor* thisx, PlayState* play);
void PlayerCall_Update(Actor* thisx, PlayState* play);
void PlayerCall_Draw(Actor* thisx, PlayState* play);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} struct_801F58B0; // size = 0x1C

extern struct_801F58B0 D_801F58B0[3][3];

extern s32 D_801F59C8[2];

extern s32 D_801F59E0;

extern Vec3f D_801F59E8;

void func_80127B64(struct_801F58B0 arg0[], UNK_TYPE arg1, Vec3f* arg2);

s32 func_801226E0(PlayState* play, s32 arg1) {
    if (arg1 == 0) {
        Play_SetupRespawnPoint(&play->state, RESPAWN_MODE_DOWN, 0xBFF);
        if (play->sceneNum == SCENE_KAKUSIANA) {
            return 1;
        }
    }

    gSaveContext.respawn[RESPAWN_MODE_DOWN].data = 0;
    return arg1;
}

s32 func_80122744(PlayState* play, struct_80122744_arg1* arg1, u32 arg2, Vec3s* arg3) {
    arg1->unk_00 = arg2;
    arg1->unk_01 = 0;
    arg1->unk_04 = arg3;
    return 1;
}

s32 func_80122760(PlayState* play, struct_80122744_arg1* arg1, f32 arg2) {
    if (arg1->unk_01 < arg1->unk_00) {
        Player* player = GET_PLAYER(play);
        Vec3f sp30;
        s32 pad;
        s16 yaw;
        f32 distXZ;

        Math_Vec3s_ToVec3f(&sp30, &arg1->unk_04[arg1->unk_01]);
        yaw = Math_Vec3f_Yaw(&player->actor.world.pos, &sp30);
        func_800B6F20(play, &play->actorCtx.unk_26C, arg2, yaw);
        play->actorCtx.unk268 = 1;
        distXZ = Math_Vec3f_DistXZ(&player->actor.world.pos, &sp30);

        if ((fabsf(player->actor.world.pos.y - sp30.y) < 50.0f) && (distXZ < arg2)) {
            arg1->unk_01++;
        }

        return false;
    }

    return true;
}

void func_80122868(PlayState* play, Player* player) {
    OPEN_DISPS(play->state.gfxCtx);

    if (player->invincibilityTimer > 0) {
        s32 phi_v0 = 50 - player->invincibilityTimer;

        phi_v0 = CLAMP(phi_v0, 8, 40);

        player->unk_B5F += phi_v0;
        POLY_OPA_DISP =
            Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 0, 0, 4000 - (s32)(Math_CosS(player->unk_B5F << 8) * 2000.0f));
    } else if (gSaveContext.jinxTimer != 0) {
        player->unk_B5F += 10;
        POLY_OPA_DISP =
            Gfx_SetFog(POLY_OPA_DISP, 0, 0, 255, 0, 0, 4000 - (s32)(Math_CosS(player->unk_B5F << 8) * 2000.0f));
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_801229A0(PlayState* play, Player* player) {
    OPEN_DISPS(play->state.gfxCtx);

    if ((gSaveContext.jinxTimer != 0) || (player->invincibilityTimer > 0)) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_801229EC(UNK_TYPE arg0, UNK_TYPE arg1) {
}

extern s16 sMaskObjectIds[PLAYER_MASK_MAX - 1];
#if 0
s16 sMaskObjectIds[PLAYER_MASK_MAX - 1] = {
    OBJECT_MASK_TRUTH,  OBJECT_MASK_KERFAY,  OBJECT_MASK_YOFUKASI, OBJECT_MASK_RABIT,   OBJECT_MASK_KI_TAN,
    OBJECT_MASK_JSON,   OBJECT_MASK_ROMERNY, OBJECT_MASK_ZACHO,    OBJECT_MASK_POSTHAT, OBJECT_MASK_MEOTO,
    OBJECT_MASK_BIGELF, OBJECT_MASK_GIBUDO,  OBJECT_MASK_GERO,     OBJECT_MASK_DANCER,  OBJECT_MASK_SKJ,
    OBJECT_MASK_STONE,  OBJECT_MASK_BREE,    OBJECT_MASK_BAKURETU, OBJECT_MASK_BU_SAN,  OBJECT_MASK_KYOJIN,
    OBJECT_MASK_BOY,    OBJECT_MASK_GORON,   OBJECT_MASK_ZORA,     OBJECT_MASK_NUTS,
};
#endif

// Load mask object?
/**
 * Notes:
 *
 * player->maskObjectLoadState seems to be able to take 3 possible values
 *    0: The mask object is loaded.
 *    1: The mask object must be changed (and the DMA request has not been sent yet)
 *    2: Waiting for the DMA request to complete.
 */
void func_801229FC(Player* player) {
    if (player->maskObjectLoadState == 1) {
        s16 objectId = sMaskObjectIds[(u8)player->maskId - 1];

        osCreateMesgQueue(&player->maskObjectLoadQueue, &player->maskObjectLoadMsg, 1);
        DmaMgr_SendRequestImpl(&player->maskDmaRequest, player->maskObjectSegment, gObjectTable[objectId].vromStart,
                               gObjectTable[objectId].vromEnd - gObjectTable[objectId].vromStart, 0,
                               &player->maskObjectLoadQueue, NULL);
        player->maskObjectLoadState++;
    } else if (player->maskObjectLoadState == 2) {
        if (osRecvMesg(&player->maskObjectLoadQueue, NULL, OS_MESG_NOBLOCK) == 0) {
            player->maskObjectLoadState = 0;

            if (player->currentMask == PLAYER_MASK_GREAT_FAIRY) {
                s32 i;

                for (i = 0; i < ARRAY_COUNT(D_801F58B0); i++) {
                    func_80127B64(D_801F58B0[i], ARRAY_COUNT(D_801F58B0[i]), &player->bodyPartsPos[7]);
                }
            }
        }
    } else if ((player->currentMask != PLAYER_MASK_NONE) && (player->currentMask != (u8)player->maskId)) {
        player->maskObjectLoadState = 1;
        player->maskId = player->currentMask;
    } else if (player->currentMask == PLAYER_MASK_CIRCUS_LEADER) {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(D_801F59C8); i++) {
            D_801F59C8[i] += Rand_S16Offset(4, 23) + (s32)(fabsf(player->linearVelocity) * 50.0f);
        }
    }
}

void func_80122BA4(PlayState* play, struct_80122D44_arg1* arg1, s32 arg2, s32 alpha) {
    if (arg2 == arg1->unk_00) {
        s32 index;

        arg1->unk_01--;
        if (arg1->unk_01 < 0) {
            arg1->unk_01 = 3;
        }

        index = arg1->unk_01;
        arg1->unk_04[index].unk_00 = arg1->unk_00;
        arg1->unk_04[index].alpha = alpha;
        Matrix_Get(&arg1->unk_04[index].mf);

        arg1->unk_00 = 0;
    }
}

void func_80122C20(PlayState* play, struct_80122D44_arg1* arg1) {
    struct_80122D44_arg1_unk_04* temp_v1 = &arg1->unk_04[0];
    s32 phi_a1;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(arg1->unk_04); i++, temp_v1++) {
        // Can't be `temp_v1->alpha != 0`
        if (temp_v1->alpha) {
            phi_a1 = temp_v1->unk_00 == 3 ? (255 / 3) : (255 / 5);
            if (phi_a1 >= temp_v1->alpha) {
                temp_v1->alpha = 0;
            } else {
                temp_v1->alpha -= phi_a1;
            }
        }
    }
}

typedef struct {
    /* 0x0 */ Color_RGB8 color;
    /* 0x4 */ Gfx* dList;
} struct_801BFDD0; // size = 0x08

extern struct_801BFDD0 D_801BFDD0[];
#if 0
struct_801BFDD0 D_801BFDD0[] = {
    { { 180, 200, 255 }, gLinkGoronCurledDL },
    { { 155, 0, 0 }, gLinkGoronRollingSpikesAndEffectDL },
    { { 255, 0, 0 }, gLinkGoronGoronPunchEffectDL },
};
#endif

void func_80122D44(PlayState* play, struct_80122D44_arg1* arg1) {
    struct_801BFDD0* temp_s3;
    struct_80122D44_arg1_unk_04* phi_s2 = arg1->unk_04;
    s32 phi_s6 = false;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    for (i = 0; i != ARRAY_COUNT(arg1->unk_04); i++) {
        if ((phi_s2->alpha != 0) && (phi_s2->alpha != 255)) {
            temp_s3 = &D_801BFDD0[phi_s2->unk_00 - 1];
            Matrix_Put(&phi_s2->mf);

            gDPPipeSync(POLY_XLU_DISP++);

            if (!phi_s6 && phi_s2->unk_00 == 2) {
                AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_goron_Matanimheader_013138));
                phi_s6 = true;
            }

            Scene_SetRenderModeXlu(play, 1, 2);
            gDPSetEnvColor(POLY_XLU_DISP++, temp_s3->color.r, temp_s3->color.g, temp_s3->color.b, phi_s2->alpha);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPDisplayList(POLY_XLU_DISP++, temp_s3->dList);
        }

        phi_s2++;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

extern u8 sMaskItemIds[PLAYER_MASK_MAX - 1];
#if 0
u8 sMaskItemIds[PLAYER_MASK_MAX - 1] = {
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

u8 Player_MaskIdToItemId(s32 maskIdMinusOne) {
    return sMaskItemIds[maskIdMinusOne];
}

u8 Player_GetCurMaskItemId(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->currentMask != PLAYER_MASK_NONE) {
        return Player_MaskIdToItemId(player->currentMask - 1);
    }

    return ITEM_NONE;
}

void func_80122F28(Player* player) {
    if ((player->actor.category == ACTORCAT_PLAYER) &&
        (!(player->stateFlags1 & (PLAYER_STATE1_20000000 | PLAYER_STATE1_800000 | PLAYER_STATE1_200000 |
                                  PLAYER_STATE1_800 | PLAYER_STATE1_400))) &&
        (!(player->stateFlags2 & PLAYER_STATE2_1))) {
        if (player->doorType < 0) {
            ActorCutscene_SetIntentToPlay(0x7C);
        } else {
            ActorCutscene_SetIntentToPlay(0x7D);
        }
    }
}

s32 func_80122F9C(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->stateFlags2 & PLAYER_STATE2_80000) && player->unk_AE7 == 2;
}

s32 func_80122FCC(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->stateFlags2 & PLAYER_STATE2_80000) && (player->unk_AE7 == 1 || player->unk_AE7 == 3);
}

void func_8012300C(PlayState* play, s32 arg1) {
    Player* player = GET_PLAYER(play);

    player->unk_B2B = arg1;
}

void func_8012301C(Player* player, PlayState* play2) {
    PlayState* play = play2;
    s32 pad;

    player->unk_AE7++;

    if (player->unk_AE7 == 2) {
        s16 objectId = gPlayerFormObjectIndices[((void)0, gSaveContext.save.playerForm)];

        gActorOverlayTable[ACTOR_PLAYER].initInfo->objectId = objectId;
        func_8012F73C(&play->objectCtx, player->actor.objBankIndex, objectId);
        player->actor.objBankIndex = Object_GetIndex(&play->objectCtx, GAMEPLAY_KEEP);
    } else if (player->unk_AE7 >= 3) {
        s32 objBankIndex = Object_GetIndex(&play->objectCtx, gActorOverlayTable[ACTOR_PLAYER].initInfo->objectId);

        if (Object_IsLoaded(&play->objectCtx, objBankIndex)) {
            player->actor.objBankIndex = objBankIndex;
            player->actor.shape.rot.z = gSaveContext.save.playerForm + 1;
            player->actor.init = PlayerCall_Init;
            player->actor.update = PlayerCall_Update;
            player->actor.draw = PlayerCall_Draw;
            gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
        }
    }
}

extern s16 D_801BFE14[][18];

// OoT's Player_SetBootData
void func_80123140(PlayState* play, Player* player) {
    s16* bootRegs;
    s32 currentBoots;
    f32 scale;

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        REG(27) = 1200;
    } else {
        REG(27) = 2000;
    }

    REG(48) = 370;

    currentBoots = player->currentBoots;
    if (currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
        if (player->stateFlags1 & PLAYER_STATE1_8000000) {
            currentBoots++;
        }
        if (player->transformation == PLAYER_FORM_GORON) {
            REG(48) = 200;
        }
    } else if (currentBoots == PLAYER_BOOTS_GIANT) {
        REG(48) = 170;
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
    R_RUN_SPEED_LIMIT = bootRegs[10];
    REG(68) = bootRegs[11];
    REG(69) = bootRegs[12];
    IREG(66) = bootRegs[13];
    IREG(67) = bootRegs[14];
    IREG(68) = bootRegs[15];
    IREG(69) = bootRegs[16];
    MREG(95) = bootRegs[17];

    if (play->roomCtx.currRoom.unk3 == 2) {
        R_RUN_SPEED_LIMIT = 500;
    }

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        scale = 0.015f;
    } else {
        scale = 0.01f;
    }

    Actor_SetScale(&player->actor, scale);
}

s32 Player_InBlockingCsMode(PlayState* play, Player* player) {
    return (player->stateFlags1 & (PLAYER_STATE1_20000000 | PLAYER_STATE1_200 | PLAYER_STATE1_80)) ||
           (player->csMode != 0) || (play->transitionTrigger == TRANS_TRIGGER_START) ||
           (play->transitionMode != TRANS_MODE_OFF) || (player->stateFlags1 & PLAYER_STATE1_1) ||
           (player->stateFlags3 & PLAYER_STATE3_80) || (play->actorCtx.unk268 != 0);
}

s32 Player_InCsMode(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return Player_InBlockingCsMode(play, player) || player->unk_AA5 == 5;
}

s32 func_80123420(Player* player) {
    return player->stateFlags3 & PLAYER_STATE3_80000000;
}

s32 func_80123434(Player* player) {
    return player->stateFlags1 & (PLAYER_STATE1_40000000 | PLAYER_STATE1_20000 | PLAYER_STATE1_10000);
}

// Unused
s32 func_80123448(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->stateFlags1 & PLAYER_STATE1_400000) &&
           (player->transformation != PLAYER_FORM_HUMAN || (!func_80123434(player) && player->unk_730 == NULL));
}

// TODO: Player_IsGoronOrDeku is a temporary name until we have more info on this function.
// Hypothesis: this function checks if the current form would crouch when he tries to use the shield
s32 Player_IsGoronOrDeku(Player* player) {
    return player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_DEKU;
}

s32 func_801234D4(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->stateFlags2 & PLAYER_STATE2_8) || player->actor.speedXZ != 0.0f ||
           ((player->transformation != PLAYER_FORM_ZORA) && (player->stateFlags1 & PLAYER_STATE1_8000000)) ||
           ((player->transformation == PLAYER_FORM_ZORA) && (player->stateFlags1 & PLAYER_STATE1_8000000) &&
            (!(player->actor.bgCheckFlags & 1) || (player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER)));
}

s32 func_80123590(PlayState* play, Actor* actor) {
    Player* player = GET_PLAYER(play);

    if ((player->stateFlags1 & PLAYER_STATE1_800) && (player->heldActor == actor)) {
        player->interactRangeActor = NULL;
        player->heldActor = NULL;
        player->actor.child = NULL;
        player->stateFlags1 &= ~PLAYER_STATE1_800;
        return true;
    }

    return false;
}

s32 func_801235DC(PlayState* play, f32 arg1, s16 arg2) {
    Player* player = GET_PLAYER(play);

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

s32 func_8012364C(PlayState* play, Player* player, s32 arg2) {
    if (arg2 >= 4) {
        return ITEM_NONE;
    }

    if (arg2 == 0) {
        s32 item = Inventory_GetBtnBItem(play);

        if (item >= ITEM_FD) {
            return item;
        }

        if ((player->currentMask == PLAYER_MASK_BLAST) && (play->interfaceCtx.bButtonDoAction == 0x18)) {
            return ITEM_F0;
        }

        if ((player->currentMask == PLAYER_MASK_BREMEN) && (play->interfaceCtx.bButtonDoAction == 0x1A)) {
            return ITEM_F1;
        }

        if ((player->currentMask == PLAYER_MASK_KAMARO) && (play->interfaceCtx.bButtonDoAction == 0x19)) {
            return ITEM_F2;
        }

        return item;
    }

    if (arg2 == 1) {
        return (gSaveContext.buttonStatus[1] != BTN_DISABLED)
                   ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_LEFT]
               : (gSaveContext.unk_3F22 == 0x10) ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_LEFT]
                                                 : ITEM_NONE;
    }

    if (arg2 == 2) {
        return (gSaveContext.buttonStatus[2] != BTN_DISABLED)
                   ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_DOWN]
               : (gSaveContext.unk_3F22 == 0x10) ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_DOWN]
                                                 : ITEM_NONE;
    }

    return (gSaveContext.buttonStatus[3] != BTN_DISABLED) ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_RIGHT]
           : (gSaveContext.unk_3F22 == 0x10)              ? gSaveContext.save.equips.buttonItems[0][EQUIP_SLOT_C_RIGHT]
                                                          : ITEM_NONE;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123810.s")

extern u8 sActionModelGroups[];

s32 Player_ActionToModelGroup(Player* player, s32 actionParam) {
    s32 modelGroup = sActionModelGroups[actionParam];

    if ((modelGroup == 2) && Player_IsGoronOrDeku(player)) {
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

extern u8 sPlayerStrengths[PLAYER_FORM_MAX];
#if 0
u8 sPlayerStrengths[PLAYER_FORM_MAX] = {
    PLAYER_STRENGTH_HUMAN, // PLAYER_FORM_FIERCE_DEITY
    PLAYER_STRENGTH_GORON, // PLAYER_FORM_GORON
    PLAYER_STRENGTH_ZORA,  // PLAYER_FORM_ZORA
    PLAYER_STRENGTH_DEKU,  // PLAYER_FORM_DEKU
    PLAYER_STRENGTH_HUMAN, // PLAYER_FORM_HUMAN
};
#endif

typedef struct {
    /* 0x00 */ u8 flag;
    /* 0x02 */ u16 textId;
} TextTriggerEntry; // size = 0x04

extern TextTriggerEntry sEnvironmentTextTriggers[];
// These textIds are OoT remnants. The corresponding text entries are not present in this game, and so these don't point
// to anything relevant.
#if 0
TextTriggerEntry sEnvironmentTextTriggers[] = {
    { 1, 0x26FC },
    { 2, 0x26FD },
    { 0, 0 },
    { 2, 0x26FD },
};
#endif

extern Gfx** sPlayerDListGroups[];

void func_801239AC(Player* player) {
    if (player->stateFlags1 & PLAYER_STATE1_400000) {
        if ((player->heldItemActionParam < 0) || (player->heldItemActionParam == player->itemActionParam)) {
            if (!Player_IsHoldingTwoHandedWeapon(player)) {
                if (!Player_IsGoronOrDeku(player)) {
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
    u8* playerModelTypes;

    D_801F59E0 = player->transformation * 2;
    player->leftHandType = gPlayerModelTypes[modelGroup][1];
    player->rightHandType = gPlayerModelTypes[modelGroup][2];
    player->sheathType = gPlayerModelTypes[modelGroup][3];

    if (player->sheathType == 14) {
        if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_NONE) {
            player->sheathType = 15;
        }
    }

    playerModelTypes = gPlayerModelTypes[modelGroup];

    player->leftHandDLists = &sPlayerDListGroups[playerModelTypes[1]][D_801F59E0];
    player->rightHandDLists = &sPlayerDListGroups[playerModelTypes[2]][D_801F59E0];
    player->sheathDLists = &sPlayerDListGroups[playerModelTypes[3]][D_801F59E0];
    player->waistDLists = &sPlayerDListGroups[playerModelTypes[4]][D_801F59E0];

    func_801239AC(player);
}

void Player_SetModelGroup(Player* player, s32 modelGroup) {
    player->modelGroup = modelGroup;

    if (modelGroup == 1) {
        player->modelAnimType = 0;
    } else {
        player->modelAnimType = gPlayerModelTypes[modelGroup][0];
    }

    if (player->modelAnimType < 3) {
        if (((player->transformation != PLAYER_FORM_FIERCE_DEITY) && (player->transformation != PLAYER_FORM_HUMAN)) ||
            (player->currentShield == PLAYER_SHIELD_NONE)) {
            player->modelAnimType = 0;
        }
    }

    Player_SetModels(player, modelGroup);
}

void func_80123C58(Player* player) {
    player->heldItemActionParam = player->itemActionParam;
    Player_SetModelGroup(player, Player_ActionToModelGroup(player, player->itemActionParam));
    player->unk_AA5 = 0;
}

void Player_SetEquipmentData(PlayState* play, Player* player) {
    if (player->csMode != 0x86) {
        player->currentShield = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD);
        if ((player->transformation != PLAYER_FORM_ZORA) || (((player->currentBoots != PLAYER_BOOTS_ZORA_LAND)) &&
                                                             (player->currentBoots != PLAYER_BOOTS_ZORA_UNDERWATER))) {
            player->currentBoots = D_801BFF90[player->transformation];
        }
        Player_SetModelGroup(player, Player_ActionToModelGroup(player, player->itemActionParam));
        func_80123140(play, player);
        if (player->unk_B62 != 0) {
            player->unk_B62 = 1;
        }
    }
}

void func_80123D50(PlayState* play, Player* player, s32 itemId, s32 actionParam) {
    Inventory_UpdateBottleItem(play, itemId, player->heldItemButton);

    if (itemId != ITEM_BOTTLE) {
        player->heldItemId = itemId;
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

void func_80123E90(PlayState* play, Actor* actor) {
    Player* player = GET_PLAYER(play);

    func_80123DC0(player);
    player->unk_730 = actor;
    player->unk_A78 = actor;
    player->stateFlags1 |= PLAYER_STATE1_10000;
    func_800DFD78(Play_GetCamera(play, CAM_ID_MAIN), 8, actor);
    Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), 9);
}

s32 func_80123F14(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return player->stateFlags1 & PLAYER_STATE1_800000;
}

s32 func_80123F2C(PlayState* play, s32 ammo) {
    play->unk_1887C = ammo + 1;

    return 1;
}

s32 Player_IsBurningStickInRange(PlayState* play, Vec3f* pos, f32 xzRange, f32 yRange) {
    Player* this = GET_PLAYER(play);
    Vec3f diff;
    s32 pad;

    if ((this->itemActionParam == PLAYER_AP_STICK) && (this->unk_B28 != 0)) {
        Math_Vec3f_Diff(&this->meleeWeaponInfo[0].tip, pos, &diff);
        return (SQXZ(diff) <= SQ(xzRange)) && (0.0f <= diff.y) && (diff.y <= yRange);
    }

    return false;
}

u8 Player_GetStrength(void) {
    return sPlayerStrengths[(void)0, gSaveContext.save.playerForm];
}

u8 Player_GetMask(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return player->currentMask;
}

// Unused
void Player_RemoveMask(PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->currentMask = PLAYER_MASK_NONE;
}

s32 Player_HasMirrorShieldEquipped(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->transformation == PLAYER_FORM_HUMAN) && (player->currentShield == PLAYER_SHIELD_MIRROR_SHIELD);
}

s32 Player_IsHoldingMirrorShield(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return (player->transformation == PLAYER_FORM_HUMAN) && (player->rightHandType == 8) &&
           (player->currentShield == PLAYER_SHIELD_MIRROR_SHIELD);
}

s32 Player_IsHoldingHookshot(Player* player) {
    return player->itemActionParam == PLAYER_AP_HOOKSHOT;
}

s32 func_801240DC(Player* player) {
    return Player_IsHoldingHookshot(player) && (player->heldActor == NULL);
}

s32 func_80124110(Player* player, s32 actionParam) {
    s32 temp_v0 = actionParam - PLAYER_AP_FISHING_POLE;

    if (player->transformation != PLAYER_FORM_GORON) {
        if (((actionParam - PLAYER_AP_FISHING_POLE) > (PLAYER_AP_FISHING_POLE - PLAYER_AP_FISHING_POLE)) &&
            ((actionParam - PLAYER_AP_FISHING_POLE) < (PLAYER_AP_SWORD_GREAT_FAIRY - PLAYER_AP_FISHING_POLE))) {
            return temp_v0;
        }
    }

    return 0;
}

s32 func_80124148(Player* player) {
    return func_80124110(player, player->itemActionParam);
}

s32 Player_ActionToMeleeWeapon(s32 actionParam) {
    s32 weapon = actionParam - (PLAYER_AP_SWORD_KOKIRI - 1);

    if ((weapon > 0) && (weapon <= (PLAYER_AP_ZORA_FINS - (PLAYER_AP_SWORD_KOKIRI - 1)))) {
        return weapon;
    }
    return 0;
}

s32 Player_GetMeleeWeaponHeld(Player* player) {
    return Player_ActionToMeleeWeapon(player->itemActionParam);
}

s32 Player_IsHoldingTwoHandedWeapon(Player* player) {
    // Relies on the actionParams for two-handed weapons being contiguous.
    if ((player->itemActionParam >= PLAYER_AP_SWORD_GREAT_FAIRY) && (player->itemActionParam <= PLAYER_AP_STICK)) {
        return true;
    }

    return false;
}

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
    if ((explosive >= (PLAYER_AP_BOMB - PLAYER_AP_BOMB)) && (explosive <= (PLAYER_AP_BOMBCHU - PLAYER_AP_BOMB))) {
        return explosive;
    }

    return -1;
}

s32 Player_GetExplosiveHeld(Player* player) {
    return Player_ActionToExplosive(player, player->itemActionParam);
}

// Convert actionParam to sword
s32 func_80124278(Actor* actor, s32 actionParam) {
    s32 sword = 0;

    //! FAKE:
    if ((actionParam == PLAYER_AP_LAST_USED) ||
        ((sword = actionParam - PLAYER_AP_SWORD_KOKIRI, (sword >= PLAYER_AP_SWORD_KOKIRI - PLAYER_AP_SWORD_KOKIRI)) &&
         (sword <= PLAYER_AP_SWORD_GREAT_FAIRY - PLAYER_AP_SWORD_KOKIRI))) {
        return sword;
    }

    return -1;
}

s32 func_801242B4(Player* player) {
    return (player->stateFlags1 & PLAYER_STATE1_8000000) && player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER;
}

s32 func_801242DC(PlayState* play) {
    Player* player = GET_PLAYER(play);
    TextTriggerEntry* triggerEntry;
    s32 envIndex;

    if (play->roomCtx.currRoom.unk2 == 3) { // Room is hot
        envIndex = 0;
    } else if ((player->transformation != PLAYER_FORM_ZORA) && (player->unk_AD8 > 80)) {
        envIndex = 3;
    } else if (player->stateFlags1 & PLAYER_STATE1_8000000) {
        if ((player->transformation == PLAYER_FORM_ZORA) && (player->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) &&
            (player->actor.bgCheckFlags & 1)) {
            envIndex = 1;
        } else {
            envIndex = 2;
        }
    } else {
        return 0;
    }

    // Trigger general textboxes under certain conditions, like "It's so hot in here!". Unused in MM
    triggerEntry = &sEnvironmentTextTriggers[envIndex];
    if (!Player_InCsMode(play)) {
        if ((triggerEntry->flag) && !(gSaveContext.textTriggerFlags & triggerEntry->flag) && (envIndex == 0)) {
            Message_StartTextbox(play, triggerEntry->textId, NULL);
            gSaveContext.textTriggerFlags |= triggerEntry->flag;
        }
    }

    return envIndex + 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124420.s")

void func_80124618(struct_80124618 arg0[], f32 curFrame, Vec3f* arg2) {
    s32 currentFrame = curFrame;
    f32 temp_f0;
    f32 temp_f14;
    f32 progress;
    s16 temp_v1;

    do {
        temp_v1 = arg0[1].unk_0;
        arg0++;
    } while (temp_v1 < currentFrame);

    temp_f0 = arg0[-1].unk_0;

    progress = (curFrame - temp_f0) / (temp_v1 - temp_f0);

    temp_f14 = arg0[-1].unk_2.x;
    arg2->x = LERPIMP(temp_f14, arg0->unk_2.x, progress) * 0.01f;

    temp_f14 = arg0[-1].unk_2.y;
    arg2->y = LERPIMP(temp_f14, arg0->unk_2.y, progress) * 0.01f;

    temp_f14 = arg0[-1].unk_2.z;
    arg2->z = LERPIMP(temp_f14, arg0->unk_2.z, progress) * 0.01f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801246F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124870.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124CC4.s")

extern s32 D_801C0958;
#if 0
s32 D_801C0958 = false;
#endif

void func_80124F18(s16* arg0, f32* arg1, s16 arg2, f32 arg3, f32 arg4) {
    f32 phi_f12;

    if (*arg0 < arg2) {
        *arg1 += arg3;
    } else {
        *arg1 -= arg3;
    }

    *arg1 = CLAMP(*arg1, -arg4, arg4);
    *arg0 += (s16)*arg1;
    if (((arg2 - *arg0) * (s16)*arg1) < 0) {
        *arg0 = arg2;
    }
}

void func_80124FF0(f32 arg0, s16 arg1, Vec3f* arg2, s16 arg3, Vec3f* arg4, Vec3f* arg5, s16* arg6, f32* arg7, f32 arg8,
                   s16 arg9, s16* arg10, f32* arg11, s32 arg12) {
    Vec3f sp44;
    f32 sp40;
    s16 temp_v0;
    s16 sp3C;
    f32 temp_f14;
    f32 sp34 = Math_CosS(arg1) * arg0;
    f32 sp30 = Math_SinS(arg1) * -arg0;

    arg5->x = (Math_SinS(arg3) * sp30) + arg2->x;
    arg5->y = arg2->y + sp34;
    arg5->z = (Math_CosS(arg3) * sp30) + arg2->z;

    Math_Vec3f_Diff(arg5, arg4, &sp44);
    sp40 = sqrtf(SQXZ(sp44));

    sp3C = (sp40 <= 1.0f) ? arg3 : Math_FAtan2F(sp44.z, sp44.x);
    sp40 = (Math_CosS(sp3C - arg3) * sp40) + arg8;

    if (ABS_ALT(BINANG_SUB(sp3C, arg3)) > 0x4000) {
        sp3C = BINANG_ROT180(sp3C);
    }
    sp3C -= arg3;

    temp_v0 = Math_FAtan2F(sp44.y, sp40);
    temp_v0 = CLAMP(temp_v0, (s16)-arg9, arg9);
    //! FAKE:
    if (sp3C) {}

    func_80124F18(arg6, arg7, temp_v0, 20.0f, 2000.0f);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801251C4.s")

void func_80125318(Vec3f* arg0, Vec3s* arg1) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    arg1->x = 0;
    arg1->y = 0;
    arg1->z = 0;
}

void func_80125340(void) {
    Matrix_Push();
    D_801C0958 = true;
}

void func_8012536C(void) {
    if (D_801C0958) {
        Matrix_Pop();
        D_801C0958 = false;
    }
}

void Player_DrawZoraShield(PlayState* play, Player* player) {
    u8* phi_a0;
    Vtx* vtx;
    Gfx* dList;
    f32 scale;
    s32 i;

    scale = player->unk_B62 * (10.0f / 51.0f);

    OPEN_DISPS(play->state.gfxCtx);

    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_zora_Matanimheader_012A80));
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

    // clang-format off
    vtx = Lib_SegmentedToVirtual(&object_link_zora_Vtx_011210); phi_a0 = Lib_SegmentedToVirtual(&object_link_zora_U8_011710);
    // clang-format on

    // ARRAY_COUNT(object_link_zora_Vtx_011210)
    for (i = 0; i < 80; i++) {
        // Editing the Vtxs in object itself
        vtx->v.cn[3] = (*phi_a0 * player->unk_B62) >> 8;
        vtx++;
        phi_a0++;
    }

    dList = POLY_XLU_DISP;

    gSPMatrix(&dList[0], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dList[1], object_link_zora_DL_011760);

    POLY_XLU_DISP = &dList[2];

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125500.s")

s32 func_80125580(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125580.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801262C8.s")

// unused
s32 func_801263FC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Player* player = (Player*)thisx;

    if (!func_80125580(play, limbIndex, dList, pos, rot, thisx)) {
        *dList = NULL;
    }

    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126440.s")

extern u8 D_801C096C[PLAYER_SHIELD_MAX];
#if 0
u8 D_801C096C[PLAYER_SHIELD_MAX] = {
    COLTYPE_METAL,
    COLTYPE_METAL,
    COLTYPE_METAL,
};
#endif

void func_801265C8(PlayState* play, Player* player, ColliderQuad* collider, Vec3f arg3[4]) {
    if (player->stateFlags1 & PLAYER_STATE1_400000) {
        Vec3f sp4C;
        Vec3f sp40;
        Vec3f sp34;
        Vec3f sp28;

        player->shieldQuad.base.colType = D_801C096C[player->currentShield];
        Matrix_MultVec3f(&arg3[0], &sp28);
        Matrix_MultVec3f(&arg3[1], &sp34);
        Matrix_MultVec3f(&arg3[2], &sp40);
        Matrix_MultVec3f(&arg3[3], &sp4C);
        Collider_SetQuadVertices(collider, &sp28, &sp34, &sp40, &sp4C);
        CollisionCheck_SetAC(play, &play->colChkCtx, &collider->base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &collider->base);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012669C.s")

void Player_DrawGetItemImpl(PlayState* play, Player* player, Vec3f* refPos, s32 drawIdPlusOne) {
    f32 sp34;

    if (player->stateFlags3 & PLAYER_STATE3_4000000) {
        sp34 = 6.0f;
    } else {
        sp34 = 14.0f;
    }

    OPEN_DISPS(play->state.gfxCtx);

    gSegments[6] = PHYSICAL_TO_VIRTUAL(player->giObjectSegment);

    gSPSegment(POLY_OPA_DISP++, 0x06, player->giObjectSegment);
    gSPSegment(POLY_XLU_DISP++, 0x06, player->giObjectSegment);

    Matrix_Translate((Math_SinS(player->actor.shape.rot.y) * 3.3f) + refPos->x, refPos->y + sp34,
                     (Math_CosS(player->actor.shape.rot.y) * 3.3f) + refPos->z, MTXMODE_NEW);
    Matrix_RotateZYX(0, (play->gameplayFrames * 1000), 0, MTXMODE_APPLY);
    Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
    GetItem_Draw(play, drawIdPlusOne - 1);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Player_DrawGetItem(PlayState* play, Player* player) {
    if (!player->giObjectLoading || (osRecvMesg(&player->giObjectLoadQueue, NULL, OS_MESG_NOBLOCK) == 0)) {
        Vec3f refPos;
        s32 drawIdPlusOne;

        player->giObjectLoading = false;
        if ((player->actor.id == ACTOR_EN_TEST3) ||
            ((player->transformation == PLAYER_FORM_DEKU) && (player->stateFlags1 & PLAYER_STATE1_400))) {
            refPos.x = player->actor.world.pos.x;
            refPos.z = player->actor.world.pos.z;
            if (player->actor.id == ACTOR_EN_TEST3) {
                if (player->stateFlags1 & PLAYER_STATE1_400) {
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
        Player_DrawGetItemImpl(play, player, &refPos, drawIdPlusOne);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801271B0.s")

// Player_SetMaskSegment?
s32 func_80127438(PlayState* play, Player* player, s32 currentMask) {
    if ((player->maskObjectLoadState == 0) && (currentMask == (u8)player->maskId)) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x0A, player->maskObjectSegment);

        CLOSE_DISPS(play->state.gfxCtx);

        return true;
    }

    return false;
}

void func_80127488(PlayState* play, Player* player, u8 alpha) {
    OPEN_DISPS(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, alpha);
    gSPDisplayList(POLY_XLU_DISP++, gLinkGoronGoronPunchEffectDL);

    func_80122BA4(play, &player->unk_3D0, 3, alpha);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Player_DrawCouplesMask(PlayState* play, Player* player) {
    gSegments[0xA] = PHYSICAL_TO_VIRTUAL(player->maskObjectSegment);
    AnimatedMat_DrawOpa(play, Lib_SegmentedToVirtual(&object_mask_meoto_Matanimheader_001CD8));
}

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
