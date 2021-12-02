#include "global.h"

typedef struct {
    /* 0x00 */ s16 unk_0;
    /* 0x02 */ s16 unk_2;
    /* 0x04 */ s16 unk_4;
    /* 0x06 */ s16 unk_6;
    /* 0x08 */ s16 unk_8;
} struct_801F59D0;

extern struct_801F59D0 D_801F59D0;

s32 func_801226E0(GlobalContext* globalCtx, s32 arg1) {
    if (arg1 == 0){
        func_80169E6C(globalCtx, 0, 0xBFF);
        if (globalCtx->sceneNum == SCENE_KAKUSIANA){
            return 1;
        }
    }

    gSaveContext.respawn[0].data = 0;
    return arg1;
}

s32 func_80122744(GlobalContext* globalCtx, PlayerLib_80122744_arg1* arg1, u32 arg2, Vec3s* arg3) {
    arg1->unk_00 = arg2;
    arg1->unk_01 = 0;
    arg1->unk_04 = arg3;
    return 1;
}

s32 func_80122760(GlobalContext* globalCtx, PlayerLib_80122744_arg1* arg1, f32 arg2) {
    if (arg1->unk_01 < arg1->unk_00) {
        Player* player = GET_PLAYER(globalCtx);
        Vec3f sp30;
        s32 pad;
        s16 yaw;
        f32 distXZ;

        Math_Vec3s_ToVec3f(&sp30, &arg1->unk_04[arg1->unk_01]);
        yaw = Math_Vec3f_Yaw(&player->actor.world.pos, &sp30);
        func_800B6F20(globalCtx, globalCtx->actorCtx.pad26C, arg2, yaw);
        globalCtx->actorCtx.unk268 = 1;
        distXZ = Math_Vec3f_DistXZ(&player->actor.world.pos, &sp30);

        if ((fabsf(player->actor.world.pos.y - sp30.y) < 50.0f) && (distXZ < arg2)) {
            arg1->unk_01++;
        }

        return 0;
    }

    return 1;
}

void func_80122868(GlobalContext* globalCtx, Player* player) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (player->invincibilityTimer > 0) {
        s32 phi_v0 = 50 - player->invincibilityTimer;

        phi_v0 = CLAMP(phi_v0, 8, 40);

        player->unk_B5F += phi_v0;
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0xFF, 0, 0, 0, 0, 0xFA0 - (s32) (Math_CosS((player->unk_B5F << 8)) * 2000.0f));
    } else if (gSaveContext.unk_1016 != 0) {
        player->unk_B5F += 10;
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0xFF, 0, 0, 0xFA0 - (s32) (Math_CosS((player->unk_B5F << 8)) * 2000.0f));
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_801229A0(GlobalContext* globalCtx, Player* player) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((gSaveContext.unk_1016 != 0) || (player->invincibilityTimer > 0)) {
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_801229EC(UNK_TYPE arg0, UNK_TYPE arg1) {
}

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} struct_801F58B0; // size = 0x1C

extern s16 D_801BFD9E[];
extern struct_801F58B0 D_801F58B0[3][3];
extern s32 D_801F59C8[2];

void func_80127B64(struct_801F58B0 arg0[], UNK_TYPE arg1, Vec3f* arg2);

// Load mask?
void func_801229FC(Player* player) {
    if (player->maskObjectLoading == 1) {
        // TODO: check if player->maskId is unsigned
        s16 temp_s1 = D_801BFD9E[(u8)player->maskId];

        osCreateMesgQueue(&player->maskObjectLoadQueue, &player->maskObjectLoadMsg, 1);
        DmaMgr_SendRequestImpl(&player->maskDmaRequest, player->maskObjectSegment, objectFileTable[temp_s1].vromStart, objectFileTable[temp_s1].vromEnd - objectFileTable[temp_s1].vromStart, 0, &player->maskObjectLoadQueue, NULL);
        player->maskObjectLoading += 1;
    } else if (player->maskObjectLoading == 2) {
        if (osRecvMesg(&player->maskObjectLoadQueue, NULL, 0) == 0) {
            player->maskObjectLoading = 0;

            if (player->currentMask == PLAYER_MASK_GREAT_FAIRY) {
                s32 i;

                for (i = 0; i < ARRAY_COUNT(D_801F58B0); i++) {
                    func_80127B64(D_801F58B0[i], ARRAY_COUNT(D_801F58B0[i]), &player->bodyPartsPos[7]);
                }
            }
        }
    } else if ((player->currentMask != 0) && (player->currentMask != (u8)player->maskId)) {
        player->maskObjectLoading = 1;
        player->maskId = player->currentMask;
    } else if (player->currentMask == 8) {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(D_801F59C8); i++) {
            D_801F59C8[i] += Rand_S16Offset(4, 0x17) + (s32) (fabsf(player->linearVelocity) * 50.0f);
        }
    }
}

void func_80122BA4(GraphicsContext** gfxCtx, struct_80122D44_arg1* arg1, s32 arg2, s32 arg3) {
    if (arg2 == arg1->unk_00) {
        s32 index;

        arg1->unk_01--;
        if (arg1->unk_01 < 0) {
            arg1->unk_01 = 3;
        }

        index = arg1->unk_01;
        arg1->unk_04[index].unk_00 = arg1->unk_00;
        arg1->unk_04[index].unk_01 = arg3;
        Matrix_CopyCurrentState(&arg1->unk_04[index].unk_04);

        arg1->unk_00 = 0;
    }
}

#ifdef NON_EQUIVALENT
// Probably equivalent, but I'm not sure
// Maybe it is a unrolled loop?
void func_80122C20(GlobalContext* globalCtx, struct_80122D44_arg1* arg1) {
    u8 temp_v0;
    struct_80122D44_arg1_unk_04* temp_v1;
    s32 phi_a1;

    temp_v1 = arg1->unk_04;
    temp_v0 = temp_v1->unk_01;
    if (temp_v0 != 0) {
        phi_a1 = temp_v1->unk_00 == 3 ? 0x55 : 0x33;

        if (phi_a1 >= temp_v0) {
            temp_v1->unk_01 = 0;
        } else {
            temp_v1->unk_01 = (temp_v0 - phi_a1);
        }
    }

    temp_v1++;
    temp_v0 = temp_v1->unk_01;
    if (temp_v0 != 0) {
        phi_a1 = temp_v1->unk_00 == 3 ? 0x55 : 0x33;

        if (phi_a1 >= temp_v0) {
            temp_v1->unk_01 = 0;
        } else {
            temp_v1->unk_01 = (temp_v0 - phi_a1);
        }
    }

    temp_v1++;
    temp_v0 = temp_v1->unk_01;
    if (temp_v0 != 0) {
        phi_a1 = temp_v1->unk_00 == 3 ? 0x55 : 0x33;

        if (phi_a1 >= temp_v0) {
            temp_v1->unk_01 = 0;
        } else {
            temp_v1->unk_01 = (temp_v0 - phi_a1);
        }
    }

    temp_v1++;
    temp_v0 = temp_v1->unk_01;
    if (temp_v0 != 0) {
        phi_a1 = temp_v1->unk_00 == 3 ? 0x55 : 0x33;

        if (phi_a1 >= temp_v0) {
            temp_v1->unk_01 = 0;
        } else {
            temp_v1->unk_01 = (temp_v0 - phi_a1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80122C20.s")
#endif

struct _struct_D_801BFDD0_0x8 {
    /* 0x0 */ u8 unk_0;                             /* inferred */
    /* 0x1 */ u8 unk_1;                             /* inferred */
    /* 0x2 */ u8 unk_2;                             /* inferred */
    ///* 0x3 */ char pad_3[1];
    /* 0x4 */ Gfx* unk_4;                            /* inferred */
};
extern struct _struct_D_801BFDD0_0x8 D_801BFDD0[3];/* = {
    { 0xB4, 0xC8, 0xFF, 0x600BDD8 },
    { 0x9B, 0, 0, 0x6014690 },
    { 0xFF, 0, 0, 0x6011AB8 },
};*/

extern AnimatedMaterial D_06013138;

void func_80122D44(GlobalContext* globalCtx, struct_80122D44_arg1* arg1) {
    struct _struct_D_801BFDD0_0x8* temp_s3;
    struct_80122D44_arg1_unk_04* phi_s2 = arg1->unk_04;
    s32 phi_s6 = false;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    for (i = 0; i != ARRAY_COUNT(arg1->unk_04); i++) {
        if ((phi_s2->unk_01 != 0) && (phi_s2->unk_01 != 0xFF)) {
            temp_s3 = &D_801BFDD0[phi_s2->unk_00 - 1];
            Matrix_SetCurrentState(&phi_s2->unk_04);

            gDPPipeSync(POLY_XLU_DISP++);

            if (!phi_s6 && phi_s2->unk_00 == 2) {
                AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(&D_06013138));
                phi_s6 = true;
            }

            Scene_SetRenderModeXlu(globalCtx, 1, 2);
            gDPSetEnvColor(POLY_XLU_DISP++, temp_s3->unk_0, temp_s3->unk_1, temp_s3->unk_2, phi_s2->unk_01);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPDisplayList(POLY_XLU_DISP++, temp_s3->unk_4);
        }

        phi_s2++;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

extern u8 D_801BFDE8[];

u8 func_80122ED8(s32 index) {
    return D_801BFDE8[index];
}

u8 func_80122EEC(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u8 temp_v1;

    if (player->currentMask != PLAYER_MASK_NONE) {
        return func_80122ED8(player->currentMask - 1);
    } else {
        return 0xFF;
    }
}

void func_80122F28(Player* player) {
    if ((player->actor.category == 2) && (!(player->stateFlags1 & (0x20000000 | 0xA00000 | 0xC00))) && (!(player->stateFlags2 & 1))) {
        if (player->doorType < 0) {
            ActorCutscene_SetIntentToPlay(0x7C);
        } else {
            ActorCutscene_SetIntentToPlay(0x7D);
        }
    }
}

s32 func_80122F9C(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return (player->stateFlags2 & 0x80000) && player->unk_AE7 == 2;
}

s32 func_80122FCC(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return (player->stateFlags2 & 0x80000) && (player->unk_AE7 == 1 || player->unk_AE7 == 3);
}

void func_8012300C(GlobalContext* globalCtx, s32 arg1) {
    Player* player = GET_PLAYER(globalCtx);

    player->unk_B2B = arg1;
}

void func_8012301C(Player* player, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;

    player->unk_AE7++;

    if (player->unk_AE7 == 2) {
        s16 objectId = gLinkFormObjectIndexes[((void)0, gSaveContext.playerForm)];

        gActorOverlayTable->initInfo->objectId = objectId;
        func_8012F73C(&globalCtx->objectCtx, player->actor.objBankIndex, objectId);
        player->actor.objBankIndex = Object_GetIndex(&globalCtx->objectCtx, 1);
    } else if (player->unk_AE7 >= 3) {
        s32 objBankIndex = Object_GetIndex(&globalCtx->objectCtx, gActorOverlayTable->initInfo->objectId);

        if (Object_IsLoaded(&globalCtx->objectCtx, objBankIndex)) {
            player->actor.objBankIndex = objBankIndex;
            player->actor.shape.rot.z = gSaveContext.playerForm + 1;
            player->actor.init = func_80160AF8;
            player->actor.update = func_80160B80;
            player->actor.draw = func_80160BC0;
            gSaveContext.equippedMask = 0;
        }
    }
}

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

s32 func_80123434(Player* player) {
    return player->stateFlags1 & 0x40030000;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123448.s")

s32 func_801234B0(Player* player) {
    return player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_DEKU;
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801234D4.s")

s32 func_80123590(GameState* gameState, Actor* actor) {
    Player* player = GET_PLAYER(gameState);

    if ((player->stateFlags1 & 0x800) && (player->leftHandActor == actor)) {
        player->unk_388 = NULL;
        player->leftHandActor = NULL;
        player->actor.child = NULL;
        player->stateFlags1 &= ~0x800;
        return 1;
    }
    return 0;
}

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

s32 Player_IsBurningStickInRange(GlobalContext* globalCtx, Vec3f* pos, f32 xzRange, f32 yRange) {
    Player* this = GET_PLAYER(globalCtx);
    Vec3f diff;
    s32 pad;

    if ((this->itemActionParam == PLAYER_AP_STICK) && (this->unk_B28 != 0)) {
        Math_Vec3f_Diff(&this->swordInfo[0].tip, pos, &diff);
        return ((SQ(diff.x) + SQ(diff.z)) <= SQ(xzRange)) && (0.0f <= diff.y) && (diff.y <= yRange);
    } else {
        return false;
    }
}

extern u8 D_801BFF98[];

u8 func_80124020(void) {
    return D_801BFF98[(void)0, gSaveContext.playerForm];
}

u8 Player_GetMask(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->currentMask;
}

void Player_RemoveMask(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->currentMask = PLAYER_MASK_NONE;
}

s32 func_8012405C(GameState* gameState) {
    Player* player = GET_PLAYER(gameState);

    return player->transformation == 4 && player->currentShield == 2;
}

s32 func_80124088(GameState* gameState) {
    Player* player = GET_PLAYER(gameState);

    return player->transformation == 4 && player->rightHandType == 8 && player->currentShield == 2;
}

s32 func_801240C8(Player* player) {
    return player->itemActionParam == 0xD;
}

s32 func_801240DC(Player* player) {
    return func_801240C8(player) && player->leftHandActor == NULL;
}

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

s32 func_801242B4(Player* player) {
    return (player->stateFlags1 & 0x8000000) && player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER;
}

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ u16 unk_02;
} struct_801BFFA0;

extern struct_801BFFA0 D_801BFFA0[];

s32 func_801242DC(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    struct_801BFFA0* sp18;
    s32 sp1C;

    if (globalCtx->roomCtx.currRoom.unk2 == 3) {
        sp1C = 0;
    } else if ((player->transformation != PLAYER_FORM_ZORA) && (player->unk_AD8 > 0x50)) {
        sp1C = 3;
    } else if (player->stateFlags1 & 0x8000000) {
        if ((player->transformation == PLAYER_FORM_ZORA) && (player->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) && (player->actor.bgCheckFlags & 1)) {
            sp1C = 1;
        } else {
            sp1C = 2;
        }
    } else {
        return 0;
    }

    sp18 = &D_801BFFA0[sp1C];
    if (!Player_InCsMode(&globalCtx->state)) {
        if ((sp18->unk_00 != 0) && !(gSaveContext.textTriggerFlags & sp18->unk_00) && (sp1C == 0)) {
            func_801518B0(globalCtx, sp18->unk_02, NULL);
            gSaveContext.textTriggerFlags |= sp18->unk_00;
        }
    }

    return sp1C + 1;
}

#ifdef NON_MATCHING
void func_80124420(Player* player) {
    int new_var;
    s16 sp28;
    s16 sp26;
    f32 sp20;
    f32 temp_f10;

    D_801F59D0.unk_6 = D_801F59D0.unk_6 - (D_801F59D0.unk_6 >> 3);
    D_801F59D0.unk_8 = D_801F59D0.unk_8 - (D_801F59D0.unk_8 >> 3);
    D_801F59D0.unk_6 = D_801F59D0.unk_6 + (-D_801F59D0.unk_0 >> 2);
    D_801F59D0.unk_8 = D_801F59D0.unk_8 + (-D_801F59D0.unk_2 >> 2);

    sp26 = player->actor.world.rot.y - player->actor.shape.rot.y;
    sp20 = Math_CosS(sp26);
    sp28 = (randPlusMinusPoint5Scaled(2.0f) + 10.0f) * (player->actor.speedXZ * -200.0f * sp20);
    sp20 = Math_SinS(sp26);
    temp_f10 = randPlusMinusPoint5Scaled(2.0f) + 10.0f;
    new_var = ((s16) (temp_f10 * ((player->actor.speedXZ * 100.0f) * sp20)));

    D_801F59D0.unk_6 = (D_801F59D0.unk_6 + (sp28 >> 2));
    D_801F59D0.unk_8 = D_801F59D0.unk_8 + (new_var >> 2);

    if (D_801F59D0.unk_6 > 0x1770) {
        D_801F59D0.unk_6 = 0x1770;
    } else if (D_801F59D0.unk_6 < -0x1770) {
        D_801F59D0.unk_6 = -0x1770;
    }

    if (D_801F59D0.unk_8 > 0x1770) {
        D_801F59D0.unk_8 = 0x1770;
    } else if (D_801F59D0.unk_8 < -0x1770) {
        D_801F59D0.unk_8 = -0x1770;
    }

    D_801F59D0.unk_0 += D_801F59D0.unk_6;
    D_801F59D0.unk_2 += D_801F59D0.unk_8;

    if (D_801F59D0.unk_0 < 0) {
        D_801F59D0.unk_4 = D_801F59D0.unk_0 >> 1;
    } else {
        D_801F59D0.unk_4 = 0;
    }
}
#else
void func_80124420(Player* player);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124420.s")
#endif

void func_80124618(f32*, f32, Vec3f*);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124618.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801246F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124870.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801251C4.s")

void func_80125318(Vec3f* arg0, Vec3s* arg1) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    arg1->x = 0;
    arg1->y = 0;
    arg1->z = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125340.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012536C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801253A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125500.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125580.s")

void func_80125CE0(Player* player, f32* arg1, Vec3f* arg2, Vec3s* arg3) {
    Matrix_JointPosition(arg2, arg3);
    func_80125318(arg2, arg3);
    func_80124618(arg1, player->skelAnime.curFrame, player->unk_AF0);
    Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, 1);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801262C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801263FC.s")

s32 func_80126440(GlobalContext* globalCtx, ColliderQuad* collider, struct_80126440_arg2* arg2, Vec3f* arg3, Vec3f* arg4) {
    if (arg2->unk_00 == 0) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }
        Math_Vec3f_Copy(&arg2->unk_04, arg3);
        Math_Vec3f_Copy(&arg2->unk_10, arg4);
        arg2->unk_00 = 1;

        return 1;
    } else if ((arg2->unk_04.x == arg3->x) && (arg2->unk_04.y == arg3->y) && (arg2->unk_04.z == arg3->z) && (arg2->unk_10.x == arg4->x) && (arg2->unk_10.y == arg4->y) && (arg2->unk_10.z == arg4->z)) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }

        return 0;
    } else {
        if (collider != NULL) {
            Collider_SetQuadVertices(collider, arg4, arg3, &arg2->unk_10, &arg2->unk_04);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &collider->base);
        }
        Math_Vec3f_Copy(&arg2->unk_10, arg4);
        Math_Vec3f_Copy(&arg2->unk_04, arg3);
        arg2->unk_00 = 1;
    }
    return 1;
}

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

extern Gfx D_06011AB8[];

void func_80127488(GraphicsContext** gfxCtx, Player* player, u8 arg2) {
    OPEN_DISPS(*gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(*gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, arg2);
    gSPDisplayList(POLY_XLU_DISP++, D_06011AB8);

    func_80122BA4(gfxCtx, &player->unk_3D0, 3, arg2);

    CLOSE_DISPS(*gfxCtx);
}

extern AnimatedMaterial D_0A001CD8;

void func_8012754C(GlobalContext* globalCtx, Player* player) {
    gSegments[0xA] = PHYSICAL_TO_VIRTUAL(player->maskObjectSegment);
    AnimatedMat_DrawOpa(globalCtx, Lib_SegmentedToVirtual(&D_0A001CD8));
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127594.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801278F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127A60.s")

void func_80127B64(struct_801F58B0 arg0[], s32 count, Vec3f* arg2) {
    s32 i;

    for (i = 0; i < count; i++) {
        Math_Vec3f_Copy(&arg0->unk_00, arg2);
        Math_Vec3f_Copy(&arg0->unk_0C, &D_801D15B0);
        // maybe fake match?
        arg0++;
        arg0[-1].unk_18 = 0;
        arg0[-1].unk_1A = 0;
    }
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128388.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801284A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128640.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128BD0.s")
