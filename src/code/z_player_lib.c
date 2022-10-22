#include "prevent_bss_reordering.h"
#include "global.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#include "objects/object_link_boy/object_link_boy.h"
#include "objects/object_link_goron/object_link_goron.h"
#include "objects/object_link_zora/object_link_zora.h"
#include "objects/object_link_nuts/object_link_nuts.h"
#include "objects/object_link_child/object_link_child.h"

#include "objects/object_mask_truth/object_mask_truth.h"
#include "objects/object_mask_kerfay/object_mask_kerfay.h"
#include "objects/object_mask_yofukasi/object_mask_yofukasi.h"
#include "objects/object_mask_rabit/object_mask_rabit.h"
#include "objects/object_mask_ki_tan/object_mask_ki_tan.h"
#include "objects/object_mask_json/object_mask_json.h"
#include "objects/object_mask_romerny/object_mask_romerny.h"
#include "objects/object_mask_zacho/object_mask_zacho.h"
#include "objects/object_mask_posthat/object_mask_posthat.h"
#include "objects/object_mask_meoto/object_mask_meoto.h"
#include "objects/object_mask_bigelf/object_mask_bigelf.h"
#include "objects/object_mask_gibudo/object_mask_gibudo.h"
#include "objects/object_mask_gero/object_mask_gero.h"
#include "objects/object_mask_dancer/object_mask_dancer.h"
#include "objects/object_mask_skj/object_mask_skj.h"
#include "objects/object_mask_stone/object_mask_stone.h"
#include "objects/object_mask_bree/object_mask_bree.h"
#include "objects/object_mask_bakuretu/object_mask_bakuretu.h"
#include "objects/object_mask_bu_san/object_mask_bu_san.h"
#include "objects/object_mask_kyojin/object_mask_kyojin.h"
#include "objects/object_mask_boy/object_mask_boy.h"
#include "objects/object_mask_goron/object_mask_goron.h"
#include "objects/object_mask_zora/object_mask_zora.h"
#include "objects/object_mask_nuts/object_mask_nuts.h"

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

struct_801F58B0 D_801F58B0[3][3];

Vec3f D_801F59B0[2];

s32 D_801F59C8[2];

typedef struct {
    /* 0x0 */ s16 unk_0;
    /* 0x2 */ s16 unk_2;
    /* 0x4 */ s16 unk_4;
    /* 0x6 */ s16 unk_6;
    /* 0x8 */ s16 unk_8;
} struct_801F59D0; // size = 0xA

struct_801F59D0 D_801F59D0;

Vec3f* D_801F59DC;

s32 D_801F59E0;

s32 D_801F59E4;

Vec3f D_801F59E8;

s32 D_801F59F4;
s32 D_801F59F8;

void func_80127B64(struct_801F58B0 arg0[], s32 count, Vec3f* arg2);

s32 func_801226E0(PlayState* play, s32 arg1) {
    if (arg1 == 0) {
        Play_SetupRespawnPoint(&play->state, RESPAWN_MODE_DOWN, 0xBFF);
        if (play->sceneId == SCENE_KAKUSIANA) {
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

s16 sMaskObjectIds[PLAYER_MASK_MAX - 1] = {
    OBJECT_MASK_TRUTH,  OBJECT_MASK_KERFAY,  OBJECT_MASK_YOFUKASI, OBJECT_MASK_RABIT,   OBJECT_MASK_KI_TAN,
    OBJECT_MASK_JSON,   OBJECT_MASK_ROMERNY, OBJECT_MASK_ZACHO,    OBJECT_MASK_POSTHAT, OBJECT_MASK_MEOTO,
    OBJECT_MASK_BIGELF, OBJECT_MASK_GIBUDO,  OBJECT_MASK_GERO,     OBJECT_MASK_DANCER,  OBJECT_MASK_SKJ,
    OBJECT_MASK_STONE,  OBJECT_MASK_BREE,    OBJECT_MASK_BAKURETU, OBJECT_MASK_BU_SAN,  OBJECT_MASK_KYOJIN,
    OBJECT_MASK_BOY,    OBJECT_MASK_GORON,   OBJECT_MASK_ZORA,     OBJECT_MASK_NUTS,
};

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

struct_801BFDD0 D_801BFDD0[] = {
    { { 180, 200, 255 }, gLinkGoronCurledDL },
    { { 155, 0, 0 }, gLinkGoronRollingSpikesAndEffectDL },
    { { 255, 0, 0 }, gLinkGoronGoronPunchEffectDL },
};

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

u8 Player_MaskIdToItemId(s32 maskIdMinusOne) {
    return sMaskItemIds[maskIdMinusOne];
}

s32 Player_GetCurMaskItemId(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->currentMask != PLAYER_MASK_NONE) {
        return Player_MaskIdToItemId(player->currentMask - 1);
    }

    return ITEM_NONE;
}

void func_80122F28(Player* player) {
    if ((player->actor.category == ACTORCAT_PLAYER) &&
        (!(player->stateFlags1 & (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_200000 | PLAYER_STATE1_800000 |
                                  PLAYER_STATE1_20000000))) &&
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

FlexSkeletonHeader* gPlayerSkeletons[PLAYER_FORM_MAX] = {
    &gLinkFierceDeitySkel, &gLinkGoronSkel, &gLinkZoraSkel, &gLinkDekuSkel, &gLinkHumanSkel,
};

s16 D_801BFE14[][18] = {
    { 200, 666, 200, 700, 366, 200, 600, 175, 60, 800, 1000, -100, 600, 590, 800, 125, 300, 65 },
    { 200, 1000, 300, 800, 500, 400, 800, 400, 120, 800, 550, -100, 600, 540, 750, 125, 400, 200 },
    { 100, 1000, 300, 800, 250, 200, 800, 200, 90, 800, 350, -80, 600, 540, 750, 60, 200, 200 },
    { 200, 1000, 300, 700, 550, 270, 600, 1000, 120, 800, 600, -100, 600, 590, 750, 125, 200, 130 },
    { 200, 1000, 300, 700, 550, 270, 700, 300, 120, 800, 600, -100, 600, 590, 750, 125, 200, 130 },
    { 200, 1000, 300, 700, 550, 270, 700, 300, 120, 800, 600, -100, 600, 590, 750, 125, 200, 130 },
    { 200, 1000, 300, 700, 550, 270, 700, 200, 120, 800, 600, -140, 600, 590, 750, 125, 200, 130 },
    { 80, 800, 150, 700, 480, 270, 600, 50, 120, 800, 300, -40, 400, 540, 270, 25, 0, 80 },
};

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

    if (play->roomCtx.curRoom.unk3 == 2) {
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
    return (player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_200 | PLAYER_STATE1_20000000)) ||
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
    return player->stateFlags1 & (PLAYER_STATE1_10000 | PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
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

ItemId func_8012364C(PlayState* play, Player* player, s32 arg2) {
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
        return (gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] != BTN_DISABLED) ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT)
               : (gSaveContext.hudVisibility == HUD_VISIBILITY_A_B_C)         ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT)
                                                                              : ITEM_NONE;
    }

    if (arg2 == 2) {
        return (gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] != BTN_DISABLED) ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN)
               : (gSaveContext.hudVisibility == HUD_VISIBILITY_A_B_C)         ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN)
                                                                              : ITEM_NONE;
    }

    return (gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] != BTN_DISABLED) ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT)
           : (gSaveContext.hudVisibility == HUD_VISIBILITY_A_B_C)          ? BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT)
                                                                           : ITEM_NONE;
}

u16 sCItemButtons[] = { BTN_CLEFT, BTN_CDOWN, BTN_CRIGHT };

s32 func_80123810(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 temp_v0;
    ItemId itemId;
    s32 i;

    if (gSaveContext.save.unk_06 == 0) {
        if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->press.button, BTN_A | BTN_B)) {
            play->interfaceCtx.unk_222 = 0;
            play->interfaceCtx.unk_224 = 0;
            Interface_SetHudVisibility(play->msgCtx.unk_120BC);
            return -1;
        }
    } else {
        gSaveContext.save.unk_06--;
    }

    for (i = 0; i < ARRAY_COUNT(sCItemButtons); i++) {
        if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, sCItemButtons[i])) {
            i++;
            itemId = func_8012364C(play, player, i);

            play->interfaceCtx.unk_222 = 0;
            play->interfaceCtx.unk_224 = 0;
            Interface_SetHudVisibility(play->msgCtx.unk_120BC);

            if ((itemId >= ITEM_FD) || (temp_v0 = play->unk_18794(play, player, itemId, i), (temp_v0 < 0))) {
                play_sound(NA_SE_SY_ERROR);
                return -1;
            } else {
                s32 pad;

                player->heldItemButton = i;
                return temp_v0;
            }
        }
    }

    return 0;
}

// Used to map action params to model groups
u8 sActionModelGroups[PLAYER_AP_MAX] = {
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_NONE
    PLAYER_MODELGROUP_13,             // PLAYER_AP_LAST_USED
    PLAYER_MODELGROUP_STICK,          // PLAYER_AP_FISHING_ROD
    PLAYER_MODELGROUP_ONE_HAND_SWORD, // PLAYER_AP_SWORD_KOKIRI
    PLAYER_MODELGROUP_ONE_HAND_SWORD, // PLAYER_AP_SWORD_RAZOR
    PLAYER_MODELGROUP_ONE_HAND_SWORD, // PLAYER_AP_SWORD_GILDED
    PLAYER_MODELGROUP_TWO_HAND_SWORD, // PLAYER_AP_SWORD_GREAT_FAIRY
    PLAYER_MODELGROUP_STICK,          // PLAYER_AP_STICK
    PLAYER_MODELGROUP_ZORA_FINS,      // PLAYER_AP_ZORA_FINS
    PLAYER_MODELGROUP_BOW,            // PLAYER_AP_BOW
    PLAYER_MODELGROUP_BOW,            // PLAYER_AP_BOW_FIRE
    PLAYER_MODELGROUP_BOW,            // PLAYER_AP_BOW_ICE
    PLAYER_MODELGROUP_BOW,            // PLAYER_AP_BOW_LIGHT
    PLAYER_MODELGROUP_HOOKSHOT,       // PLAYER_AP_HOOKSHOT
    PLAYER_MODELGROUP_EXPLOSIVES,     // PLAYER_AP_BOMB
    PLAYER_MODELGROUP_EXPLOSIVES,     // PLAYER_AP_POWDER_KEG
    PLAYER_MODELGROUP_EXPLOSIVES,     // PLAYER_AP_BOMBCHU
    PLAYER_MODELGROUP_8,              // PLAYER_AP_11
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_NUT
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_PICTO_BOX
    PLAYER_MODELGROUP_INSTRUMENT,     // PLAYER_AP_OCARINA
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_FISH
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_SPRING_WATER
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_HOT_SPRING_WATER
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_ZORA_EGG
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_DEKU_PRINCESS
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_GOLD_DUST
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_1C
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_SEAHORSE
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_MUSHROOM
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_HYLIAN_LOACH
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_BUG
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_POE
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_BIG_POE
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_POTION_RED
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_POTION_BLUE
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_POTION_GREEN
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_MILK
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_MILK_HALF
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_CHATEAU
    PLAYER_MODELGROUP_BOTTLE,         // PLAYER_AP_BOTTLE_FAIRY
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MOON_TEAR
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_DEED_LAND
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_ROOM_KEY
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_LETTER_TO_KAFEI
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MAGIC_BEANS
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_DEED_SWAMP
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_DEED_MOUNTAIN
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_DEED_OCEAN
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_32
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_LETTER_MAMA
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_34
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_35
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_PENDANT_OF_MEMORIES
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_37
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_38
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_39
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_TRUTH
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_KAFEIS_MASK
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_ALL_NIGHT
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_BUNNY
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_KEATON
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_GARO
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_ROMANI
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_CIRCUS_LEADER
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_POSTMAN
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_COUPLE
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_GREAT_FAIRY
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_GIBDO
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_DON_GERO
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_KAMARO
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_CAPTAIN
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_STONE
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_BREMEN
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_BLAST
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_SCENTS
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_GIANT
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_FIERCE_DEITY
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_GORON
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_ZORA
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_MASK_DEKU
    PLAYER_MODELGROUP_DEFAULT,        // PLAYER_AP_LENS
};

PlayerModelGroup Player_ActionToModelGroup(Player* player, PlayerActionParam actionParam) {
    PlayerModelGroup modelGroup = sActionModelGroups[actionParam];

    if ((modelGroup == PLAYER_MODELGROUP_ONE_HAND_SWORD) && Player_IsGoronOrDeku(player)) {
        return PLAYER_MODELGROUP_1;
    }
    return modelGroup;
}

u8 D_801BFF90[PLAYER_FORM_MAX] = {
    PLAYER_BOOTS_FIERCE_DEITY, // PLAYER_FORM_FIERCE_DEITY
    PLAYER_BOOTS_GORON,        // PLAYER_FORM_GORON
    PLAYER_BOOTS_ZORA_LAND,    // PLAYER_FORM_ZORA
    PLAYER_BOOTS_DEKU,         // PLAYER_FORM_DEKU
    PLAYER_BOOTS_HYLIAN,       // PLAYER_FORM_HUMAN
};

u8 sPlayerStrengths[PLAYER_FORM_MAX] = {
    PLAYER_STRENGTH_HUMAN, // PLAYER_FORM_FIERCE_DEITY
    PLAYER_STRENGTH_GORON, // PLAYER_FORM_GORON
    PLAYER_STRENGTH_ZORA,  // PLAYER_FORM_ZORA
    PLAYER_STRENGTH_DEKU,  // PLAYER_FORM_DEKU
    PLAYER_STRENGTH_HUMAN, // PLAYER_FORM_HUMAN
};

typedef struct {
    /* 0x00 */ u8 flag;
    /* 0x02 */ u16 textId;
} TextTriggerEntry; // size = 0x04

// These textIds are OoT remnants. The corresponding text entries are not present in this game, and so these don't point
// to anything relevant.
TextTriggerEntry sEnvironmentTextTriggers[] = {
    { 1, 0x26FC },
    { 2, 0x26FD },
    { 0, 0 },
    { 2, 0x26FD },
};

PlayerModelIndices gPlayerModelTypes[PLAYER_MODELGROUP_MAX] = {
    /* PLAYER_MODELGROUP_0 */
    { PLAYER_ANIMTYPE_2, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_SHIELD, PLAYER_MODELTYPE_SHEATH_12,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_1 */
    { PLAYER_ANIMTYPE_1, PLAYER_MODELTYPE_LH_ONE_HAND_SWORD, PLAYER_MODELTYPE_RH_CLOSED, PLAYER_MODELTYPE_SHEATH_15,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_ONE_HAND_SWORD */
    { PLAYER_ANIMTYPE_1, PLAYER_MODELTYPE_LH_ONE_HAND_SWORD, PLAYER_MODELTYPE_RH_SHIELD, PLAYER_MODELTYPE_SHEATH_13,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_DEFAULT */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_4 */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_TWO_HAND_SWORD */
    { PLAYER_ANIMTYPE_3, PLAYER_MODELTYPE_LH_TWO_HAND_SWORD, PLAYER_MODELTYPE_RH_CLOSED, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_BOW */
    { PLAYER_ANIMTYPE_4, PLAYER_MODELTYPE_LH_CLOSED, PLAYER_MODELTYPE_RH_BOW, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_EXPLOSIVES */
    { PLAYER_ANIMTYPE_5, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_8 */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_4, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_HOOKSHOT */
    { PLAYER_ANIMTYPE_4, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_HOOKSHOT, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_STICK */
    { PLAYER_ANIMTYPE_3, PLAYER_MODELTYPE_LH_CLOSED, PLAYER_MODELTYPE_RH_CLOSED, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_INSTRUMENT */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_OPEN, PLAYER_MODELTYPE_RH_INSTRUMENT, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_BOTTLE */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_BOTTLE, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_13 */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_ONE_HAND_SWORD, PLAYER_MODELTYPE_RH_OPEN, PLAYER_MODELTYPE_SHEATH_15,
      PLAYER_MODELTYPE_WAIST },
    /* PLAYER_MODELGROUP_ZORA_FINS */
    { PLAYER_ANIMTYPE_0, PLAYER_MODELTYPE_LH_CLOSED, PLAYER_MODELTYPE_RH_CLOSED, PLAYER_MODELTYPE_SHEATH_14,
      PLAYER_MODELTYPE_WAIST },
};

/* DLists groups start */
// Note: Only the ones with size 2 * PLAYER_FORM_MAX

Gfx* gPlayerWaistDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityWaistDL, gLinkFierceDeityWaistDL, gLinkGoronWaistDL, gLinkGoronWaistDL, gLinkZoraWaistDL,
    gLinkZoraWaistDL,        gLinkDekuWaistDL,        gLinkDekuWaistDL,  gLinkHumanWaistDL, gLinkHumanWaistDL,
};

Gfx* gPlayerHandHoldingShields[PLAYER_SHIELD_MAX - 1][2] = {
    { gLinkHumanRightHandHoldingHylianShieldDL, gLinkHumanRightHandHoldingHylianShieldDL },
    { gLinkHumanRightHandHoldingMirrorShieldDL, gLinkHumanRightHandHoldingMirrorShieldDL },
};

Gfx* gPlayerSheath12DLs[2 * PLAYER_FORM_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    gLinkDekuSheathDL,
    gLinkDekuSheathDL,
    gLinkHumanSheathEmptyDL,
    gLinkHumanSheathEmptyDL,
};

Gfx* gPlayerSheath13DLs[2 * PLAYER_FORM_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    gLinkDekuSheathDL,
    gLinkDekuSheathDL,
    gLinkHumanSheathEmptyDL,
    gLinkHumanSheathEmptyDL,
};

Gfx* gPlayerSheath14DLs[2 * PLAYER_FORM_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    gLinkDekuSheathDL,
    gLinkDekuSheathDL,
    gLinkHumanSheathEmptyDL,
    gLinkHumanSheathEmptyDL,
};

Gfx* gPlayerShields[][2] = {
    { gLinkHumanHylianShieldWithMtxDL, gLinkHumanHylianShieldWithMtxDL },
    { gLinkHumanMirrorShieldWithMtxDL, gLinkHumanMirrorShieldWithMtxDL },
};

Gfx* gPlayerSheathedSwords[][2] = {
    { gLinkHumanSheathedKokiriSwordDL, gLinkHumanSheathedKokiriSwordDL },
    { gLinkHumanSheathedRazorSwordDL, gLinkHumanSheathedRazorSwordDL },
    { gLinkHumanSheathedGildedSwordDL, gLinkHumanSheathedGildedSwordDL },
};

Gfx* gPlayerSwordSheaths[][2] = {
    { gLinkHumanKokiriSwordSheathDL, gLinkHumanKokiriSwordSheathDL },
    { gLinkHumanRazorSwordSheathDL, gLinkHumanRazorSwordSheathDL },
    { gLinkHumanGildedSwordSheathDL, gLinkHumanGildedSwordSheathDL },
};

Gfx* gPlayerLeftHandTwoHandSwordDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandHoldingSwordDL,
    gLinkFierceDeityLeftHandHoldingSwordDL,
    gLinkGoronLeftHandOpenDL,
    gLinkGoronLeftHandOpenDL,
    gLinkZoraLeftHandOpenDL,
    gLinkZoraLeftHandOpenDL,
    gLinkDekuLeftHandDL,
    gLinkDekuLeftHandDL,
    gLinkHumanLeftHandHoldingGreatFairysSwordDL,
    gLinkHumanLeftHandHoldingGreatFairysSwordDL,
};

Gfx* gPlayerLeftHandOpenDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandDL, gLinkFierceDeityLeftHandDL, gLinkGoronLeftHandOpenDL, gLinkGoronLeftHandOpenDL,
    gLinkZoraLeftHandOpenDL,    gLinkZoraLeftHandOpenDL,    gLinkDekuLeftHandDL,      gLinkDekuLeftHandDL,
    gLinkHumanLeftHandOpenDL,   gLinkHumanLeftHandOpenDL,
};

Gfx* gPlayerLeftHandClosedDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandDL, gLinkFierceDeityLeftHandDL, gLinkGoronLeftHandClosedDL, gLinkGoronLeftHandClosedDL,
    gLinkZoraLeftHandClosedDL,  gLinkZoraLeftHandClosedDL,  gLinkDekuLeftHandDL,        gLinkDekuLeftHandDL,
    gLinkHumanLeftHandClosedDL, gLinkHumanLeftHandClosedDL,
};

Gfx* gPlayerLeftHandOneHandSwordDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandDL,
    gLinkFierceDeityLeftHandDL,
    gLinkGoronLeftHandOpenDL,
    gLinkGoronLeftHandOpenDL,
    gLinkZoraLeftHandClosedDL,
    gLinkZoraLeftHandClosedDL,
    gLinkDekuLeftHandDL,
    gLinkDekuLeftHandDL,
    gLinkHumanLeftHandHoldingKokiriSwordDL,
    gLinkHumanLeftHandHoldingKokiriSwordDL,
};

Gfx* D_801C018C[][2] = {
    { gLinkHumanLeftHandHoldingKokiriSwordDL, gLinkHumanLeftHandHoldingKokiriSwordDL },
    { gLinkHumanLeftHandHoldingRazorSwordDL, gLinkHumanLeftHandHoldingRazorSwordDL },
    { gLinkHumanLeftHandHoldingGildedSwordDL, gLinkHumanLeftHandHoldingGildedSwordDL },
};

Gfx* gPlayerRightHandOpenDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL, gLinkFierceDeityRightHandDL, gLinkGoronRightHandOpenDL, gLinkGoronRightHandOpenDL,
    gLinkZoraRightHandOpenDL,    gLinkZoraRightHandOpenDL,    gLinkDekuRightHandDL,      gLinkDekuRightHandDL,
    gLinkHumanRightHandOpenDL,   gLinkHumanRightHandOpenDL,
};

Gfx* gPlayerRightHandClosedDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL, gLinkFierceDeityRightHandDL, gLinkGoronRightHandClosedDL, gLinkGoronRightHandClosedDL,
    gLinkZoraRightHandClosedDL,  gLinkZoraRightHandClosedDL,  gLinkDekuRightHandDL,        gLinkDekuRightHandDL,
    gLinkHumanRightHandClosedDL, gLinkHumanRightHandClosedDL,
};

Gfx* gPlayerRightHandBowDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL,
    gLinkFierceDeityRightHandDL,
    gLinkGoronRightHandOpenDL,
    gLinkGoronRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkDekuRightHandDL,
    gLinkDekuRightHandDL,
    gLinkHumanRightHandHoldingBowDL,
    gLinkHumanRightHandHoldingBowDL,
};

Gfx* gPlayerRightHandInstrumentDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL,
    gLinkFierceDeityRightHandDL,
    gLinkGoronRightHandOpenDL,
    gLinkGoronRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkDekuRightHandDL,
    gLinkDekuRightHandDL,
    gLinkHumanRightHandHoldingOcarinaDL,
    gLinkHumanRightHandHoldingOcarinaDL,
};

Gfx* gPlayerRightHandHookshotDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL,
    gLinkFierceDeityRightHandDL,
    gLinkGoronRightHandOpenDL,
    gLinkGoronRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkZoraRightHandOpenDL,
    gLinkDekuRightHandDL,
    gLinkDekuRightHandDL,
    gLinkHumanRightHandHoldingHookshotDL,
    gLinkHumanRightHandHoldingHookshotDL,
};

Gfx* gPlayerLeftHandBottleDLs[2 * PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandDL,
    gLinkFierceDeityLeftHandDL,
    gLinkGoronLeftHandHoldBottleDL,
    gLinkGoronLeftHandHoldBottleDL,
    gLinkZoraLeftHandHoldBottleDL,
    gLinkZoraLeftHandHoldBottleDL,
    gLinkDekuLeftHandDL,
    gLinkDekuLeftHandDL,
    gLinkHumanLeftHandHoldBottleDL,
    gLinkHumanLeftHandHoldBottleDL,
};

/* DLists groups end */

Gfx* D_801C0294[PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftForearmDL, gLinkGoronLeftForearmDL, gLinkZoraLeftForearmDL,
    gLinkDekuLeftForearmDL,        gLinkHumanLeftForearmDL,
};

Gfx* D_801C02A8[PLAYER_FORM_MAX] = {
    gLinkFierceDeityLeftHandDL, gLinkGoronLeftHandOpenDL,   gLinkZoraLeftHandClosedDL,
    gLinkDekuLeftHandDL,        gLinkHumanLeftHandClosedDL,
};

Gfx* D_801C02BC[PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightShoulderDL, gLinkGoronRightShoulderDL, gLinkZoraRightShoulderDL,
    gLinkDekuRightShoulderDL,        gLinkHumanRightShoulderDL,
};

Gfx* D_801C02D0[PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL,
    //! @bug This is in the middle of a texture in the link_goron object. It has the same offset as a link_nuts dlist
    0x060038C0,
    gLinkZoraRightHandOpenDL,
    gLinkDekuRightHandDL,
    object_link_child_DL_018490,
};

Gfx* D_801C02E4[PLAYER_FORM_MAX] = {
    gLinkFierceDeityRightHandDL,
    //! @bug This is in the middle of a texture in the link_goron object. It has the same offset as a link_nuts dlist
    0x060038C0,
    gLinkZoraRightHandOpenDL,
    gLinkDekuRightHandDL,
    object_link_child_DL_017B40,
};

// Indexed by model types (left hand, right hand, sheath or waist)
Gfx** sPlayerDListGroups[PLAYER_MODELTYPE_MAX] = {
    gPlayerLeftHandOpenDLs,         // PLAYER_MODELTYPE_LH_OPEN
    gPlayerLeftHandClosedDLs,       // PLAYER_MODELTYPE_LH_CLOSED
    gPlayerLeftHandOneHandSwordDLs, // PLAYER_MODELTYPE_LH_ONE_HAND_SWORD
    gPlayerLeftHandTwoHandSwordDLs, // PLAYER_MODELTYPE_LH_TWO_HAND_SWORD
    gPlayerLeftHandOpenDLs,         // PLAYER_MODELTYPE_LH_4
    gPlayerLeftHandBottleDLs,       // PLAYER_MODELTYPE_LH_BOTTLE
    gPlayerRightHandOpenDLs,        // PLAYER_MODELTYPE_RH_OPEN
    gPlayerRightHandClosedDLs,      // PLAYER_MODELTYPE_RH_CLOSED
    gPlayerRightHandClosedDLs,      // PLAYER_MODELTYPE_RH_SHIELD
    gPlayerRightHandBowDLs,         // PLAYER_MODELTYPE_RH_BOW
    gPlayerRightHandInstrumentDLs,  // PLAYER_MODELTYPE_RH_INSTRUMENT
    gPlayerRightHandHookshotDLs,    // PLAYER_MODELTYPE_RH_HOOKSHOT
    gPlayerSheath12DLs,             // PLAYER_MODELTYPE_SHEATH_12
    gPlayerSheath13DLs,             // PLAYER_MODELTYPE_SHEATH_13
    gPlayerSheath14DLs,             // PLAYER_MODELTYPE_SHEATH_14
    gPlayerSheath14DLs,             // PLAYER_MODELTYPE_SHEATH_15
    gPlayerWaistDLs,                // PLAYER_MODELTYPE_WAIST
    NULL,                           // PLAYER_MODELTYPE_17
};

struct_80124618 D_801C0340[] = {
    { 0, { 0, 0, 0 } },       { 5, { 0, 0, 0 } },        { 7, { 100, 100, 100 } },
    { 9, { 110, 110, 110 } }, { 11, { 100, 100, 100 } },
};
struct_80124618 D_801C0368[] = {
    { 0, { 0, 0, 0 } },       { 4, { 0, 0, 0 } },      { 6, { 120, 150, 60 } },   { 8, { 130, 80, 160 } },
    { 9, { 100, 100, 100 } }, { 10, { 90, 100, 90 } }, { 11, { 100, 100, 100 } },
};
struct_80124618 D_801C03A0[] = {
    { 0, { 100, 100, 100 } },
    { 2, { 120, 120, 120 } },
    { 6, { 90, 90, 90 } },
    { 7, { 93, 93, 93 } },
};
struct_80124618 D_801C03C0[] = {
    { 0, { 200, 100, 110 } },
    { 2, { 90, 100, 100 } },
    { 3, { 100, 100, 100 } },
    { 7, { 100, 100, 100 } },
};
struct_80124618 D_801C03E0[] = {
    { 0, { 100, 100, 110 } }, { 2, { 60, 100, 80 } },    { 3, { 130, 105, 110 } },
    { 7, { 130, 105, 110 } }, { 10, { 100, 100, 100 } }, { 19, { 100, 100, 100 } },
};
struct_80124618 D_801C0410[] = {
    { 0, { 0, 0, 0 } },
    { 2, { 80, 110, 80 } },
    { 3, { 100, 100, 100 } },
};
struct_80124618 D_801C0428[] = {
    { 0, { 0, 0, 0 } },      { 6, { 0, 0, 0 } },        { 7, { 60, 60, 50 } },     { 8, { 120, 130, 100 } },
    { 9, { 100, 120, 80 } }, { 11, { 100, 100, 100 } }, { 13, { 100, 100, 100 } },
};
struct_80124618 D_801C0460[] = {
    { 0, { 100, 100, 100 } }, { 5, { 100, 100, 100 } }, { 7, { 100, 74, 80 } },
    { 8, { 100, 180, 130 } }, { 10, { 100, 80, 80 } },  { 13, { 100, 100, 100 } },
};
struct_80124618 D_801C0490[] = {
    { 0, { 100, 100, 100 } },  { 1, { 100, 100, 100 } },  { 2, { 90, 100, 105 } },  { 4, { 110, 100, 100 } },
    { 5, { 90, 100, 105 } },   { 6, { 100, 100, 100 } },  { 7, { 90, 100, 105 } },  { 8, { 100, 100, 100 } },
    { 9, { 90, 100, 105 } },   { 10, { 100, 100, 100 } }, { 11, { 90, 100, 105 } }, { 12, { 110, 100, 100 } },
    { 13, { 100, 100, 100 } }, { 14, { 90, 100, 105 } },  { 15, { 90, 100, 105 } }, { 17, { 100, 100, 100 } },
};
struct_80124618 D_801C0510[] = {
    { 0, { 100, 100, 100 } }, { 4, { 100, 100, 100 } }, { 5, { 90, 110, 100 } },
    { 6, { 110, 105, 100 } }, { 8, { 100, 100, 100 } },
};
struct_80124618 D_801C0538[] = {
    { 0, { 100, 100, 100 } }, { 5, { 100, 100, 100 } },  { 6, { 0, 0, 0 } },
    { 8, { 100, 100, 100 } }, { 14, { 100, 100, 100 } },
};
struct_80124618 D_801C0560[] = {
    { 0, { 100, 100, 100 } },
    { 2, { 95, 95, 100 } },
    { 3, { 105, 105, 100 } },
    { 5, { 102, 102, 102 } },
};
struct_80124618 D_801C0580[] = {
    { 0, { 100, 100, 100 } }, { 9, { 100, 100, 100 } }, { 10, { 150, 150, 150 } },
    { 12, { 0, 0, 0 } },      { 14, { 0, 0, 0 } },
};
struct_80124618 D_801C05A8[] = {
    { 0, { 100, 100, 100 } },
    { 6, { 100, 100, 100 } },
    { 7, { 0, 0, 0 } },
    { 17, { 0, 0, 0 } },
};
struct_80124618 D_801C05C8[] = {
    { 0, { 0, 0, 0 } },
    { 17, { 50, 50, 50 } },
};
struct_80124618 D_801C05D8[] = {
    { 0, { 0, 0, 0 } },
    { 5, { 0, 0, 0 } },
    { 9, { 100, 100, 100 } },
};
struct_80124618 D_801C05F0[] = {
    { 0, { 100, 100, 100 } },
    { 5, { 100, 100, 100 } },
    { 9, { 0, 0, 0 } },
};
struct_80124618 D_801C0608[] = {
    { 0, { 100, 100, 100 } },
    { 10, { 100, 100, 100 } },
    { 32, { 100, 115, 105 } },
    { 58, { 100, 101, 100 } },
};
struct_80124618 D_801C0628[] = {
    { 0, { 100, 100, 100 } },  { 5, { 100, 100, 100 } },  { 15, { 100, 100, 105 } }, { 25, { 100, 100, 105 } },
    { 34, { 100, 100, 100 } }, { 46, { 100, 100, 100 } }, { 57, { 100, 100, 105 } }, { 67, { 100, 100, 105 } },
    { 76, { 100, 100, 100 } }, { 78, { 100, 100, 100 } },
};
struct_80124618 D_801C0678[] = {
    { 0, { 0, 0, 0 } },
    { 6, { 0, 0, 0 } },
    { 8, { 100, 100, 100 } },
    { 11, { 100, 100, 100 } },
};
struct_80124618 D_801C0698[] = {
    { 0, { 0, 0, 0 } },
    { 7, { 1120, 112, 112 } },
    { 8, { 140, 168, 168 } },
    { 11, { 140, 140, 140 } },
};
struct_80124618 D_801C06B8[] = {
    { 0, { 100, 100, 100 } }, { 7, { 100, 100, 100 } }, { 8, { 70, 30, 70 } }, { 10, { 0, 0, 0 } }, { 14, { 0, 0, 0 } },
};
struct_80124618 D_801C06E0[] = {
    { 0, { 140, 140, 140 } },
    { 1, { 0, 0, 0 } },
    { 14, { 0, 0, 0 } },
};
struct_80124618 D_801C06F8[] = {
    { 0, { 100, 100, 100 } },
    { 5, { 100, 100, 100 } },
    { 6, { 0, 0, 0 } },
    { 10, { 0, 0, 0 } },
};
struct_80124618 D_801C0718[] = {
    { 0, { 140, 140, 140 } },
    { 1, { 0, 0, 0 } },
    { 10, { 0, 0, 0 } },
};
struct_80124618 D_801C0730[] = {
    { 0, { 100, 100, 100 } },
    { 13, { 100, 100, 100 } },
};
struct_80124618 D_801C0740[] = {
    { 0, { 140, 140, 140 } },
    { 13, { 140, 140, 140 } },
};
struct_80124618 D_801C0750[] = {
    { 0, { 100, 100, 100 } },  { 5, { 100, 100, 100 } },  { 6, { 200, 200, 200 } },
    { 10, { 200, 200, 200 } }, { 11, { 100, 100, 100 } },
};

// alpha values
u8 D_801C0778[] = {
    0, 0, 0, 0, 0, 100, 200, 255, 255, 255, 200, 100,
};

struct_80124618 D_801C0784[] = {
    { 0, { 100, 100, 100 } },  { 14, { 100, 100, 100 } }, { 15, { 200, 200, 200 } },
    { 16, { 200, 200, 200 } }, { 18, { 100, 100, 100 } },
};

u8 D_801C07AC[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 200, 255, 255, 255, 200, 100, 0,
};

void Player_SetModelsForHoldingShield(Player* player) {
    if (player->stateFlags1 & PLAYER_STATE1_400000) {
        if ((player->heldItemActionParam < 0) || (player->heldItemActionParam == player->itemActionParam)) {
            if (!Player_IsHoldingTwoHandedWeapon(player)) {
                if (!Player_IsGoronOrDeku(player)) {
                    D_801F59E0 = player->transformation * 2;
                    player->rightHandType = PLAYER_MODELTYPE_RH_SHIELD;
                    player->rightHandDLists = &sPlayerDListGroups[PLAYER_MODELTYPE_RH_SHIELD][D_801F59E0];

                    if (player->sheathType == PLAYER_MODELTYPE_SHEATH_14) {
                        player->sheathType = PLAYER_MODELTYPE_SHEATH_12;
                    } else if (player->sheathType == PLAYER_MODELTYPE_SHEATH_15) {
                        player->sheathType = PLAYER_MODELTYPE_SHEATH_13;
                    }

                    player->sheathDLists = &sPlayerDListGroups[player->sheathType][D_801F59E0];
                    player->modelAnimType = PLAYER_ANIMTYPE_2;
                    player->heldItemActionParam = -1;
                }
            }
        }
    }
}

void Player_SetModels(Player* player, PlayerModelGroup modelGroup) {
    PlayerModelIndices* playerModelTypes;

    D_801F59E0 = player->transformation * 2;
    player->leftHandType = gPlayerModelTypes[modelGroup].leftHandType;
    player->rightHandType = gPlayerModelTypes[modelGroup].rightHandType;
    player->sheathType = gPlayerModelTypes[modelGroup].sheathType;

    if (player->sheathType == PLAYER_MODELTYPE_SHEATH_14) {
        if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_NONE) {
            player->sheathType = PLAYER_MODELTYPE_SHEATH_15;
        }
    }

    playerModelTypes = &gPlayerModelTypes[modelGroup];

    player->leftHandDLists = &sPlayerDListGroups[playerModelTypes->leftHandType][D_801F59E0];
    player->rightHandDLists = &sPlayerDListGroups[playerModelTypes->rightHandType][D_801F59E0];
    player->sheathDLists = &sPlayerDListGroups[playerModelTypes->sheathType][D_801F59E0];
    player->waistDLists = &sPlayerDListGroups[playerModelTypes->waistType][D_801F59E0];

    Player_SetModelsForHoldingShield(player);
}

void Player_SetModelGroup(Player* player, PlayerModelGroup modelGroup) {
    player->modelGroup = modelGroup;

    if (modelGroup == PLAYER_MODELGROUP_1) {
        player->modelAnimType = PLAYER_ANIMTYPE_0;
    } else {
        player->modelAnimType = gPlayerModelTypes[modelGroup].modelAnimType;
    }

    if (player->modelAnimType < PLAYER_ANIMTYPE_3) {
        if (((player->transformation != PLAYER_FORM_FIERCE_DEITY) && (player->transformation != PLAYER_FORM_HUMAN)) ||
            (player->currentShield == PLAYER_SHIELD_NONE)) {
            player->modelAnimType = PLAYER_ANIMTYPE_0;
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

void func_80123D50(PlayState* play, Player* player, ItemId itemId, PlayerActionParam actionParam) {
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
        (player->stateFlags1 & (PLAYER_STATE1_200000 | PLAYER_STATE1_800000 | PLAYER_STATE1_8000000)) ||
        (!(player->stateFlags1 & (PLAYER_STATE1_40000 | PLAYER_STATE1_80000)) &&
         ((player->actor.world.pos.y - player->actor.floorHeight) < 100.0f))) {
        player->stateFlags1 &= ~(PLAYER_STATE1_8000 | PLAYER_STATE1_10000 | PLAYER_STATE1_20000 | PLAYER_STATE1_40000 |
                                 PLAYER_STATE1_80000 | PLAYER_STATE1_40000000);
    } else if (!(player->stateFlags1 & (PLAYER_STATE1_40000 | PLAYER_STATE1_80000 | PLAYER_STATE1_200000))) {
        player->stateFlags1 |= PLAYER_STATE1_80000;
    } else if ((player->stateFlags1 & PLAYER_STATE1_40000) && (player->transformation == PLAYER_FORM_DEKU)) {
        player->stateFlags1 &=
            ~(PLAYER_STATE1_8000 | PLAYER_STATE1_10000 | PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
    }

    func_80123DA4(player);
}

void func_80123E90(PlayState* play, Actor* actor) {
    Player* player = GET_PLAYER(play);

    func_80123DC0(player);
    player->unk_730 = actor;
    player->unk_A78 = actor;
    player->stateFlags1 |= PLAYER_STATE1_10000;
    Camera_SetViewParam(Play_GetCamera(play, CAM_ID_MAIN), CAM_VIEW_TARGET, actor);
    Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), CAM_MODE_FOLLOWTARGET);
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

    return (player->transformation == PLAYER_FORM_HUMAN) && (player->rightHandType == PLAYER_MODELTYPE_RH_SHIELD) &&
           (player->currentShield == PLAYER_SHIELD_MIRROR_SHIELD);
}

s32 Player_IsHoldingHookshot(Player* player) {
    return player->itemActionParam == PLAYER_AP_HOOKSHOT;
}

s32 func_801240DC(Player* player) {
    return Player_IsHoldingHookshot(player) && (player->heldActor == NULL);
}

s32 func_80124110(Player* player, PlayerActionParam actionParam) {
    s32 temp_v0 = actionParam - PLAYER_AP_FISHING_ROD;

    if (player->transformation != PLAYER_FORM_GORON) {
        if (((actionParam - PLAYER_AP_FISHING_ROD) > (PLAYER_AP_FISHING_ROD - PLAYER_AP_FISHING_ROD)) &&
            ((actionParam - PLAYER_AP_FISHING_ROD) < (PLAYER_AP_SWORD_GREAT_FAIRY - PLAYER_AP_FISHING_ROD))) {
            return temp_v0;
        }
    }

    return 0;
}

s32 func_80124148(Player* player) {
    return func_80124110(player, player->itemActionParam);
}

s32 Player_ActionToMeleeWeapon(PlayerActionParam actionParam) {
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

s32 Player_ActionToBottle(Player* player, PlayerActionParam actionParam) {
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

s32 Player_ActionToExplosive(Player* player, PlayerActionParam actionParam) {
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

s32 Player_ActionToSword(Actor* actor, PlayerActionParam actionParam) {
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
    return (player->stateFlags1 & PLAYER_STATE1_8000000) && (player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER);
}

s32 Player_GetEnvTimerType(PlayState* play) {
    Player* player = GET_PLAYER(play);
    TextTriggerEntry* triggerEntry;
    s32 envTimerType;

    if (play->roomCtx.curRoom.unk2 == 3) { // Room is hot
        envTimerType = PLAYER_ENV_TIMER_HOTROOM - 1;
    } else if ((player->transformation != PLAYER_FORM_ZORA) && (player->underwaterTimer > 80)) {
        envTimerType = PLAYER_ENV_TIMER_UNDERWATER_FREE - 1;
    } else if (player->stateFlags1 & PLAYER_STATE1_8000000) {
        if ((player->transformation == PLAYER_FORM_ZORA) && (player->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) &&
            (player->actor.bgCheckFlags & 1)) {
            envTimerType = PLAYER_ENV_TIMER_UNDERWATER_FLOOR - 1;
        } else {
            envTimerType = PLAYER_ENV_TIMER_SWIMMING - 1;
        }
    } else {
        return PLAYER_ENV_TIMER_NONE;
    }

    // Trigger general textboxes under certain conditions, like "It's so hot in here!". Unused in MM
    triggerEntry = &sEnvironmentTextTriggers[envTimerType];
    if (!Player_InCsMode(play)) {
        if ((triggerEntry->flag) && !(gSaveContext.textTriggerFlags & triggerEntry->flag) &&
            (envTimerType == (PLAYER_ENV_TIMER_HOTROOM - 1))) {
            Message_StartTextbox(play, triggerEntry->textId, NULL);
            gSaveContext.textTriggerFlags |= triggerEntry->flag;
        }
    }

    return envTimerType + 1;
}

void func_80124420(Player* player);
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

struct_80124618 D_801C07C0[] = {
    { 0, { 100, 100, 100 } },  { 10, { 100, 100, 100 } }, { 11, { 100, 120, 120 } },
    { 12, { 100, 120, 120 } }, { 14, { 100, 100, 100 } }, { 19, { 100, 100, 100 } },
};

struct_80124618 D_801C07F0[] = {
    { 0, { 40, 60, 70 } },    { 3, { 40, 60, 70 } },    { 4, { 75, 90, 85 } },
    { 5, { 110, 120, 100 } }, { 7, { 100, 100, 100 } }, { 8, { 100, 100, 100 } },
};
struct_80124618 D_801C0820[] = {
    { 0, { 100, 100, 100 } },
    { 7, { 100, 100, 100 } },
    { 12, { 40, 60, 70 } },
};
struct_80124618 D_801C0838[] = {
    { 0, { 40, 60, 70 } },
    { 7, { 40, 60, 70 } },
    { 12, { 100, 100, 100 } },
};

Gfx gCullBackDList[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
Gfx gCullFrontDList[] = {
    gsSPSetGeometryMode(G_CULL_FRONT),
    gsSPEndDisplayList(),
};

TexturePtr sPlayerEyesTextures[] = {
    gLinkHumanEyesOpenTex,     gLinkHumanEyesHalfTex,   gLinkHumanEyesClosedTex,   gLinkHumanEyesRollRightTex,
    gLinkHumanEyesRollLeftTex, gLinkHumanEyesRollUpTex, gLinkHumanEyesRollDownTex, object_link_child_Tex_003800,
};

TexturePtr sPlayerMouthTextures[] = {
    gLinkHumanMouthClosedTex,
    gLinkHumanMouthTeethTex,
    gLinkHumanMouthAngryTex,
    gLinkHumanMouthHappyTex,
};

typedef struct PlayerFaceIndices {
    /* 0x00 */ u8 eyeIndex;
    /* 0x01 */ u8 mouthIndex;
} PlayerFaceIndices; // size = 0x02

PlayerFaceIndices sPlayerFaces[] = {
    { PLAYER_EYES_OPEN, PLAYER_MOUTH_CLOSED },       // PLAYER_FACE_0
    { PLAYER_EYES_HALF, PLAYER_MOUTH_CLOSED },       // PLAYER_FACE_1
    { PLAYER_EYES_CLOSED, PLAYER_MOUTH_CLOSED },     // PLAYER_FACE_2
    { PLAYER_EYES_OPEN, PLAYER_MOUTH_CLOSED },       // PLAYER_FACE_3
    { PLAYER_EYES_HALF, PLAYER_MOUTH_CLOSED },       // PLAYER_FACE_4
    { PLAYER_EYES_CLOSED, PLAYER_MOUTH_CLOSED },     // PLAYER_FACE_5
    { PLAYER_EYES_ROLL_LEFT, PLAYER_MOUTH_CLOSED },  // PLAYER_FACE_6
    { PLAYER_EYES_ROLL_UP, PLAYER_MOUTH_TEETH },     // PLAYER_FACE_7
    { PLAYER_EYES_7, PLAYER_MOUTH_ANGRY },           // PLAYER_FACE_8
    { PLAYER_EYES_OPEN, PLAYER_MOUTH_ANGRY },        // PLAYER_FACE_9
    { PLAYER_EYES_ROLL_RIGHT, PLAYER_MOUTH_CLOSED }, // PLAYER_FACE_10
    { PLAYER_EYES_ROLL_LEFT, PLAYER_MOUTH_CLOSED },  // PLAYER_FACE_11
    { PLAYER_EYES_CLOSED, PLAYER_MOUTH_ANGRY },      // PLAYER_FACE_12
    { PLAYER_EYES_HALF, PLAYER_MOUTH_TEETH },        // PLAYER_FACE_13
    { PLAYER_EYES_OPEN, PLAYER_MOUTH_ANGRY },        // PLAYER_FACE_14
    { PLAYER_EYES_OPEN, PLAYER_MOUTH_HAPPY },        // PLAYER_FACE_15
};

// Note the correct pointer to pass as the jointTable is the jointTable pointer from the SkelAnime struct, not the
// buffer from the Player struct itself since that one may be misaligned.
void Player_DrawImpl(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod,
                     PlayerTransformation playerForm, s32 boots, s32 face, OverrideLimbDrawFlex overrideLimbDraw,
                     PostLimbDrawFlex postLimbDraw, Actor* actor) {
    s32 eyeIndex = (jointTable[22].x & 0xF) - 1;
    s32 mouthIndex = ((jointTable[22].x >> 4) & 0xF) - 1;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    if (eyeIndex < 0) {
        eyeIndex = sPlayerFaces[face].eyeIndex;
    }

    if (playerForm == PLAYER_FORM_GORON) {
        if ((eyeIndex >= PLAYER_EYES_ROLL_RIGHT) && (eyeIndex <= PLAYER_EYES_ROLL_DOWN)) {
            eyeIndex = PLAYER_EYES_OPEN;
        } else if (eyeIndex == PLAYER_EYES_7) {
            eyeIndex = PLAYER_EYES_ROLL_RIGHT;
        }
    }

    gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(sPlayerEyesTextures[eyeIndex]));

    if (mouthIndex < 0) {
        mouthIndex = sPlayerFaces[face].mouthIndex;
    }

    gSPSegment(&gfx[1], 0x09, Lib_SegmentedToVirtual(sPlayerMouthTextures[mouthIndex]));

    POLY_OPA_DISP = &gfx[2];

    D_801F59E0 = playerForm * 2;
    D_801F59E4 = lod;
    SkelAnime_DrawFlexLod(play, skeleton, jointTable, dListCount, overrideLimbDraw, postLimbDraw, actor, lod);

    CLOSE_DISPS(play->state.gfxCtx);
}

Vec3f D_801C08C0[PLAYER_FORM_MAX] = {
    { 1304.0f, 0.0f, 0.0f }, { 1156.0f, 0.0f, 0.0f }, { 1406.0f, 0.0f, 0.0f },
    { 408.0f, 0.0f, 0.0f },  { 695.0f, 0.0f, 0.0f },
};

f32 D_801C08FC[PLAYER_FORM_MAX] = {
    1265.0f, 1056.0f, 1506.0f, 359.0f, 826.0f,
};
f32 D_801C0910[PLAYER_FORM_MAX] = {
    170.0416f, 133.63359f, 197.68358f, 16.646399f, 48.302498f,
};
f32 D_801C0924[PLAYER_FORM_MAX] = {
    10.019104f, 22.120003f, -29.12001f, 3.7582989f, -19.925102f,
};
f32 D_801C0938[PLAYER_FORM_MAX] = {
    5.0f, 4.0f, 1.0f, 1.0f, 3.0f,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124870.s")

void func_80124CC4(PlayState* play, Player* player, f32 arg2) {
    static Vec3f D_801C094C = { -500.0f, -100.0f, 0.0f };
    CollisionPoly* poly;
    s32 bgId;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f pos;
    Vec3f sp58;
    f32 sp54;
    f32 scale;

    D_801C094C.z = 0.0f;
    Matrix_MultVec3f(&D_801C094C, &sp7C);
    D_801C094C.z = arg2;
    Matrix_MultVec3f(&D_801C094C, &sp70);

    if (BgCheck_AnyLineTest3(&play->colCtx, &sp7C, &sp70, &pos, &poly, true, true, true, true, &bgId)) {
        if (!func_800B90AC(play, &player->actor, poly, bgId, &pos) ||
            BgCheck_ProjectileLineTest(&play->colCtx, &sp7C, &sp70, &pos, &poly, true, true, true, true, &bgId)) {
            OPEN_DISPS(play->state.gfxCtx);

            OVERLAY_DISP = Gfx_CallSetupDL(OVERLAY_DISP, 7);

            SkinMatrix_Vec3fMtxFMultXYZW(&play->viewProjectionMtxF, &pos, &sp58, &sp54);
            if (sp54 < 200.0f) {
                scale = 0.08f;
            } else {
                scale = (sp54 / 200.0f) * 0.08f;
            }
            Matrix_Translate(pos.x, pos.y, pos.z, MTXMODE_NEW);
            Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPSegment(OVERLAY_DISP++, 0x06, play->objectCtx.status[player->actor.objBankIndex].segment);
            gSPDisplayList(OVERLAY_DISP++, gameplay_keep_DL_04F250);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

s32 D_801C0958 = false;

Gfx** D_801C095C[] = {
    gPlayerLeftHandClosedDLs,
    gPlayerLeftHandOpenDLs,
};
Gfx** D_801C0964[] = {
    gPlayerRightHandClosedDLs,
    gPlayerRightHandOpenDLs,
};

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

u8 D_801C096C[PLAYER_SHIELD_MAX] = {
    COLTYPE_METAL,
    COLTYPE_METAL,
    COLTYPE_METAL,
};

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

Vec3f D_801C0970[] = {
    { 0.0f, 400.0f, 0.0f },
    { 0.0f, 1400.0f, -1000.0f },
    { 0.0f, -400.0f, 1000.0f },
};

Vec3f D_801C0994[] = {
    { 5000.0f, 400.0f, 0.0f },
    { 5000.0f, -400.0f, 1000.0f },
    { 5000.0f, 1400.0f, -1000.0f },
};

Vec3f D_801C09B8[] = {
    { 0.0f, 750.0f, 750.0f },
    { 1500.0f, 1500.0f, 1500.0f },
    { -2500.0f, -2000.0f, -3000.0f },
};

Vec3f D_801C09DC[] = {
    { 900.0f, 300.0f, 100.0f },
    { 1300.0f, 700.0f, -300.0f },
    { 500.0f, -100.0f, 500.0f },
};

Vec3f D_801C0A00[] = {
    { -2500.0f, 1400.0f, 1100.0f },
    { -2900.0f, 1000.0f, 1500.0f },
    { -2100.0f, 1800.0f, 700.0f },
};

Vec3f D_801C0A24[] = {
    { 0.0f, 0.0f, 0.0f },
    { -800.0f, 800.0f, 800.0f },
    { -800.0f, -800.0f, -800.0f },
};

Vec3f D_801C0A48[] = {
    { 2000.0f, 0.0f, 0.0f },
    { 2800.0f, -800.0f, -800.0f },
    { 2800.0f, 800.0f, 800.0f },
};

Vec3f D_801C0A6C[] = {
    { -400.0f, 800.0f, 0.0f },
    { -5000.0f, -500.0f, -4000.0f },
    { -5000.0f, 8000.0f, 4000.0f },
};

Vec3f D_801C0A90[] = {
    { -400.0f, 1800.0f, 0.0f },
    { 5000.0f, 8000.0f, 4000.0f },
    { 5000.0f, -500.0f, -4000.0f },
};

Gfx* D_801C0AB4[] = {
    object_link_zora_DL_00CC38,
    object_link_zora_DL_00CDA0,
};

Gfx* D_801C0ABC[] = {
    object_link_zora_DL_010868,
    object_link_zora_DL_010978,
};

Vec3f D_801C0AC4[] = {
    { 5400.0f, 1700.0f, 1800.0f },
    { 5400.0f, 1700.0f, -1800.0f },
};

Vec3f D_801C0ADC[] = {
    { 5250.0f, 570.0f, 2400.0f },
    { 5250.0f, 570.0f, -2400.0f },
};

struct_80124618* D_801C0AF4[] = {
    D_801C0678,
    D_801C0698,
};

struct_80124618* D_801C0AFC[] = {
    D_801C06B8,
    D_801C06E0,
};

struct_80124618* D_801C0B04[] = {
    D_801C06F8,
    D_801C0718,
};

struct_80124618* D_801C0B0C[] = {
    D_801C0730,
    D_801C0740,
};

Gfx* D_801C0B14[] = {
    object_link_nuts_DL_008760,
    object_link_nuts_DL_008660,
};

u8 D_801C0B1C[] = {
    0x0C,
    0x0F,
};

Gfx* D_801C0B20[] = {
    object_mask_truth_DL_0001A0,
    object_mask_kerfay_DL_000D40,
    object_mask_yofukasi_DL_000490,
    object_mask_rabit_DL_000610,
    object_mask_ki_tan_DL_0004A0,
    object_mask_json_DL_0004C0,
    object_mask_romerny_DL_0007A0,
    object_mask_zacho_DL_000700,
    object_mask_posthat_DL_000290,
    object_mask_meoto_DL_0005A0,
    object_mask_bigelf_DL_0016F0,
    object_mask_gibudo_DL_000250,
    gDonGeroMaskDL,
    object_mask_dancer_DL_000EF0,
    object_mask_skj_DL_0009F0,
    object_mask_stone_DL_000820,
    object_mask_bree_DL_0003C0,
    object_mask_bakuretu_DL_0005C0,
    object_mask_bu_san_DL_000710,
    object_mask_kyojin_DL_000380,
    gameplay_keep_DL_00B260,
    gameplay_keep_DL_005A10,
    gameplay_keep_DL_005360,
    gDekuMaskDL,
    object_mask_boy_DL_000900,
    object_mask_goron_DL_0014A0,
    object_mask_zora_DL_000DB0,
    object_mask_nuts_DL_001D90,
};

Vec3f D_801C0B90[] = {
    { 950.0f, -800.0f, 300.0f },
    { 950.0f, -800.0f, -300.0f },
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012669C.s")

void Player_DrawGetItemImpl(PlayState* play, Player* player, Vec3f* refPos, s32 drawIdPlusOne) {
    f32 sp34;

    if (player->stateFlags3 & PLAYER_STATE3_4000000) {
        sp34 = 6.0f;
    } else {
        sp34 = 14.0f;
    }

    OPEN_DISPS(play->state.gfxCtx);

    gSegments[6] = VIRTUAL_TO_PHYSICAL(player->giObjectSegment);

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
    gSegments[0xA] = VIRTUAL_TO_PHYSICAL(player->maskObjectSegment);
    AnimatedMat_DrawOpa(play, Lib_SegmentedToVirtual(&object_mask_meoto_Matanimheader_001CD8));
}

void Player_DrawCircusLeadersMask(PlayState* play, Actor* actor) {
    static Vec3f bubbleVelocity = { 0.0f, 0.0f, 0.0f };
    static Vec3f bubbleAccel = { 0.0f, 0.0f, 0.0f };
    Gfx* gfx;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_XLU_DISP;

    for (i = 0; i < ARRAY_COUNT(D_801C0B90); i++) {
        f32 scaleY = (D_801F59C8[i] / 400.0f) * 0.1f;

        Matrix_MultVec3f(&D_801C0B90[i], &D_801F59B0[i]);

        //! FAKE
        if (1) {}

        D_801F59B0[i].y += -10.0f * scaleY;

        if (D_801F59C8[i] < 0x190) {
            f32 scaleXZ = CLAMP_MAX(scaleY, 0.05f);

            Matrix_Push();
            Matrix_Translate(D_801F59B0[i].x, D_801F59B0[i].y, D_801F59B0[i].z, MTXMODE_NEW);
            Matrix_Scale(scaleXZ, scaleY, scaleXZ, MTXMODE_APPLY);

            gSPMatrix(&gfx[0], Matrix_NewMtx(play->state.gfxCtx), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(&gfx[1], 0x08, VIRTUAL_TO_PHYSICAL(SEGMENTED_TO_VIRTUAL(gEffBubble1Tex)));
            gDPSetPrimColor(&gfx[2], 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(&gfx[3], 150, 150, 150, 0);
            gSPDisplayList(&gfx[4], gEffBubbleDL);
            gSPPopMatrix(&gfx[5], G_MTX_MODELVIEW);

            Matrix_Pop();

            gfx = &gfx[6];
        } else {
            Player* player = (Player*)actor;
            f32 temp_f0 = sqrtf(SQ(player->actor.velocity.x) + SQ(player->actor.velocity.z));
            s16 phi_s0 = temp_f0 * 2000.0f;
            f32 temp_f20;

            bubbleVelocity.y = temp_f0 * 0.4f;
            bubbleAccel.y = -0.3f;

            if (phi_s0 > 0x3E80) {
                phi_s0 = 0x3E80;
            }

            phi_s0 = player->actor.focus.rot.y + ((i != 0) ? phi_s0 : -phi_s0);
            temp_f20 = temp_f0 * 0.2f;

            if (temp_f20 > 4.0f) {
                temp_f20 = 4.0f;
            }

            bubbleVelocity.x = -Math_SinS(phi_s0) * temp_f20;
            bubbleVelocity.z = -Math_CosS(phi_s0) * temp_f20;

            EffectSsDtBubble_SpawnColorProfile(play, &D_801F59B0[i], &bubbleVelocity, &bubbleAccel, 20, 20, 3, 0);
            D_801F59C8[i] -= 0x190;
        }
    }

    POLY_XLU_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void Player_DrawBlastMask(PlayState* play, Player* player) {
    static Gfx D_801C0BC0[] = {
        gsDPSetEnvColor(0, 0, 0, 255),
        gsSPEndDisplayList(),
    };
    static Gfx D_801C0BD0[] = {
        gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                              G_RM_FOG_SHADE_A,
                          AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                              GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
        gsSPEndDisplayList(),
    };

    OPEN_DISPS(play->state.gfxCtx);

    if (player->unk_B60 != 0) {
        s32 alpha;

        gSegments[0xA] = VIRTUAL_TO_PHYSICAL(player->maskObjectSegment);

        AnimatedMat_DrawOpa(play, Lib_SegmentedToVirtual(&object_mask_bakuretu_Matanimheader_0011F8));

        if (player->unk_B60 < 11) {
            alpha = (player->unk_B60 / 10.0f) * 255;
        } else {
            alpha = 255;
        }

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, (u8)alpha);
        gSPDisplayList(POLY_OPA_DISP++, object_mask_bakuretu_DL_000440);
        gSPSegment(POLY_OPA_DISP++, 0x09, D_801C0BD0);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, (u8)(255 - alpha));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x09, D_801C0BC0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

Vec3f D_801C0BE0 = { 0.0f, 0.3f, 0.0f };
Vec3f D_801C0BEC = { 0.0f, -0.025f, 0.0f };
Color_RGBA8 D_801C0BF8 = { 250, 100, 100, 0 };
Color_RGBA8 D_801C0BFC = { 0, 0, 100, 0 };

Vec3f D_801C0C00 = { 0.0f, 20.0f, 0.0f };

Vec3f D_801C0C0C[] = {
    { 174.0f, -1269.0f, -1.0f },
    { 401.0f, -729.0f, -701.0f },
    { 401.0f, -729.0f, 699.0f },
};

Vec3f D_801C0C30[] = {
    { 74.0f, -1269.0f, -1.0f },
    { 301.0f, -729.0f, -701.0f },
    { 301.0f, -729.0f, 699.0f },
};

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} struct_80128388_arg1; // size = 0x1C

struct_80128388_arg1 D_801C0C54[] = {
    { 0.0f, 0x0000, 0x8000, { 0.0f, 0.0f, 0.0f }, 0.0f, 0x0000, 0x0000 },
    { 16.8f, 0x0000, 0x0000, { 0.0f, 0.0f, 0.0f }, 20.0f, 0x1388, 0x1388 },
    { 30.0f, 0x0000, 0x0000, { 0.0f, 0.0f, 0.0f }, 20.0f, 0x1F40, 0x2EE0 },
};

Color_RGB8 D_801C0CA8[] = {
    { 255, 255, 255 }, { 80, 80, 255 },   { 136, 192, 255 }, { 136, 192, 255 }, { 184, 232, 232 }, { 248, 200, 0 },
    { 255, 180, 0 },   { 0, 128, 0 },     { 252, 238, 0 },   { 131, 0, 174 },   { 64, 64, 32 },    { 0, 0, 255 },
    { 255, 0, 255 },   { 255, 0, 255 },   { 255, 0, 0 },     { 0, 0, 255 },     { 0, 200, 0 },     { 255, 255, 255 },
    { 255, 255, 255 }, { 255, 255, 255 }, { 80, 80, 255 },
};

Vec3f D_801C0CE8[PLAYER_FORM_MAX] = {
    { 0.0f, 0.0f, 0.0f },    { 300.0f, 300.0f, -230.0f }, { 0.0f, 90.0f, -50.0f },
    { 0.0f, 20.0f, -60.0f }, { 0.0f, 0.0f, 0.0f },
};
Vec3f D_801C0D24[PLAYER_FORM_MAX] = {
    { 200.0f, 300.0f, 0.0f }, { 200.0f, 200.0f, 0.0f }, { 200.0f, 300.0f, 0.0f },
    { 200.0f, 150.0f, 0.0f }, { 200.0f, 200.0f, 0.0f },
};
Vec3f D_801C0D60 = { 398.0f, 1419.0f, 244.0f };
Vec3f D_801C0D6C = { 420.0f, 1210.0f, 380.0f };

f32 D_801C0D78[] = {
    0.0f,    // Player is not holding a melee weapon
    3000.0f, // PLAYER_AP_SWORD_KOKIRI
    3000.0f, // PLAYER_AP_SWORD_RAZOR
    4000.0f, // PLAYER_AP_SWORD_GILDED
    5500.0f, // PLAYER_AP_SWORD_GREAT_FAIRY
    -1.0f,   // PLAYER_AP_STICK
    2500.0f, // PLAYER_AP_ZORA_FINS
};

Gfx* D_801C0D94 = object_link_child_DL_017818;

f32 D_801C0D98 = -35.0f;

f32 D_801C0D9C = -395.0f;
f32 D_801C0DA0 = 0.0f;

f32 D_801C0DA4 = 0.0f;

Vec3f D_801C0DA8[4] = {
    { -4500.0f, -3000.0f, -600.0f },
    { 1500.0f, -3000.0f, -600.0f },
    { -4500.0f, 3000.0f, -600.0f },
    { 1500.0f, 3000.0f, -600.0f },
};

Vec3f D_801C0DD8 = { 50.0f, 800.0f, 0.0f };
Vec3f D_801C0DE4 = { 50.0f, 850.0f, 0.0f };
Gfx* D_801C0DF0[] = {
    object_link_goron_DL_010590, object_link_goron_DL_010368, object_link_goron_DL_010140,
    object_link_goron_DL_00FF18, object_link_goron_DL_00FCF0,
};

Vec2f D_801C0E04[PLAYER_FORM_MAX] = {
    { 140.0f, -130.0f }, { 0.0f, -200.0f }, { -160.0f, 0.0f }, { 220.0f, -200.0f }, { 0.0f, 0.0f },
};

Gfx* D_801C0E2C[] = {
    object_link_nuts_DL_007A28, object_link_nuts_DL_0077D0, object_link_nuts_DL_007548,
    object_link_nuts_DL_007900, object_link_nuts_DL_0076A0,
};
Vec3f D_801C0E40[PLAYER_FORM_MAX] = {
    { 0.0f, 0.0f, 0.0f },       { -578.3f, -1100.9f, 0.0f }, { -189.5f, -594.87f, 0.0f },
    { -570.0f, -812.0f, 0.0f }, { -230.0f, -520.0f, 0.0f },
};
Vec3f D_801C0E7C = { 1100.0f, -700.0f, 0.0f };

// unused
Vec3f D_801C0E88 = { 1600.0f, -1700.0f, -70.0f };

Vec3f D_801C0E94 = { 1800.0f, -300.0f, 0.0f };
Vec3f D_801C0EA0 = { 1300.0f, -400.0f, 0.0f };
Vec3f D_801C0EAC = { 630.0f, 100.0f, -30.0f };
Vec3s D_801C0EB8 = { 0, 0, 0x7FFF };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/Player_DrawBunnyHood.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127BE8.s")

void func_80127DA4(PlayState* play, struct_801F58B0 arg1[], struct_80128388_arg1 arg2[], s32 arg3, Vec3f* arg4,
                   Vec3f* arg5, u32* arg6);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127DA4.s")

void func_80128388(struct_801F58B0 arg0[], struct_80128388_arg1 arg1[], s32 arg2, Mtx** arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128388.s")

void Player_DrawGreatFairysMask(PlayState* play, Player* player) {
    s32 pad;
    Mtx* sp90 = GRAPH_ALLOC(play->state.gfxCtx, 6 * sizeof(Mtx));
    Vec3f sp84;
    Vec3f sp78;
    Vec3f* iter = D_801C0C0C;
    Vec3f* iter2 = D_801C0C30;
    u32 sp6C = play->gameplayFrames;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0B, sp90);

    Matrix_MultVec3f(&D_801C0C00, &D_801C0C54[1].unk_08);
    Math_Vec3f_Lerp(&player->bodyPartsPos[7], &player->bodyPartsPos[0], 0.2f, &D_801C0C54[2].unk_08);

    for (i = 0; i < ARRAY_COUNT(D_801C0C0C); i++) {
        Matrix_MultVec3f(iter, &sp84);
        Matrix_MultVec3f(iter2, &sp78);

        func_80127DA4(play, D_801F58B0[i], D_801C0C54, 3, &sp84, &sp78, &sp6C);
        sp6C += 11;

        Matrix_Push();
        Matrix_Translate(iter->x, iter->y, iter->z, MTXMODE_APPLY);
        func_80128388(D_801F58B0[i], D_801C0C54, 3, &sp90);
        Matrix_Pop();
        iter++;
        iter2++;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128640.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128BD0.s")
