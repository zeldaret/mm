#include "global.h"

typedef struct {
    /* 0x00 */ s16 unk_0;
    /* 0x02 */ s16 unk_2;
    /* 0x04 */ s16 unk_4;
    /* 0x06 */ s16 unk_6;
    /* 0x08 */ s16 unk_8;
} struct_801F59D0;

extern struct_801F59D0 D_801F59D0;



struct _struct_D_801BFFB0_0x5 {
    /* 0x0 */ u8 unk_0;                             /* inferred */
    /* 0x1 */ u8 unk_1;                             /* inferred */
    /* 0x2 */ u8 unk_2;                             /* inferred */
    /* 0x3 */ u8 unk_3;                             /* inferred */
    /* 0x4 */ u8 unk_4;                             /* inferred */
};                                                  /* size = 0x5 */

// gPlayerModelTypes
extern u8 D_801BFFB0[0xF][5];/* = {
    { 2, 0, 8, 0xC, 0x10 },
    { 1, 2, 7, 0xF, 0x10 },
    { 1, 2, 8, 0xD, 0x10 },
    { 0, 0, 6, 0xE, 0x10 },
    { 0, 0, 6, 0xE, 0x10 },
    { 3, 3, 7, 0xE, 0x10 },
    { 4, 1, 9, 0xE, 0x10 },
    { 5, 0, 6, 0xE, 0x10 },
    { 0, 4, 6, 0xE, 0x10 },
    { 4, 0, 0xB, 0xE, 0x10 },
    { 3, 1, 7, 0xE, 0x10 },
    { 0, 0, 0xA, 0xE, 0x10 },
    { 0, 5, 6, 0xE, 0x10 },
    { 0, 2, 6, 0xF, 0x10 },
    { 0, 1, 7, 0xE, 0x10 },
};*/


extern s32 D_801F59E0;

// sPlayerDListGroups
extern Gfx** D_801C02F8[];


s32 func_801241B4(Player* player);


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
    return player->stateFlags1 & (0x40000000 | 0x30000);
}

s32 func_80123448(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return (player->stateFlags1 & 0x400000) && (player->transformation != PLAYER_FORM_HUMAN || (!func_80123434(player) && player->unk_730 == 0));
}

s32 func_801234B0(Player* player) {
    return player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_DEKU;
}

s32 func_801234D4(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return 
        (player->stateFlags2 & 8) 
        ||
        player->actor.speedXZ != 0.0f 
        || 
        (
            (player->transformation != PLAYER_FORM_ZORA) 
            && 
            (player->stateFlags1 & 0x8000000)
        )
        || 
        (
            (player->transformation == PLAYER_FORM_ZORA) 
            && 
            (player->stateFlags1 & 0x8000000) 
            && 
            (
                !(player->actor.bgCheckFlags & 1)
                || 
                (player->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER)
            )
        );
}

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

s32 func_801235DC(GlobalContext* globalCtx, f32 arg1, s16 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags3 & 0x1000) {
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

extern u8 D_801BFF3C[];

s32 func_80123960(Player* player, s32 actionParam) {
    s32 temp_v1_2;

    temp_v1_2 = D_801BFF3C[actionParam];
    if ((temp_v1_2 == 2) && func_801234B0(player)) {
        return 1;
    }
    return temp_v1_2;
}

void func_801239AC(Player* player) {
    u8 phi_v0;

    if (player->stateFlags1 & 0x400000) {
        if ((player->heldItemActionParam < 0) || (player->heldItemActionParam == player->itemActionParam)) {
            if (func_801241B4(player) == 0) {
                if (func_801234B0(player) == 0) {
                    D_801F59E0 = player->transformation * 2;
                    player->rightHandType = 8;
                    player->rightHandDLists = &D_801C02F8[8][D_801F59E0];

                    if (player->sheathType == 0xE) {
                        player->sheathType = 0xC;
                    } else if (player->sheathType == 0xF) {
                        player->sheathType = 0xD;
                    }

                    player->sheathDLists = &D_801C02F8[player->sheathType][D_801F59E0];
                    player->modelAnimType = 2;
                    player->heldItemActionParam = -1;
                }
            }
        }
    }
}

// Player_SetModels
void func_80123AA4(Player* player, s32 modelGroup) {
    u8* aux;

    D_801F59E0 = player->transformation * 2;
    player->leftHandType = D_801BFFB0[modelGroup][1];
    player->rightHandType = D_801BFFB0[modelGroup][2];
    player->sheathType = D_801BFFB0[modelGroup][3];

    if (player->sheathType == 0xE) {
        if (gSaveContext.equips.buttonItems[CUR_FORM][0] == 0xFF) {
            player->sheathType = 0xF;
        }
    }

    aux = D_801BFFB0[modelGroup];

    player->leftHandDLists = &D_801C02F8[aux[1]][D_801F59E0];
    player->rightHandDLists = &D_801C02F8[aux[2]][D_801F59E0];
    player->sheathDLists = &D_801C02F8[aux[3]][D_801F59E0];
    player->waistDLists = &D_801C02F8[aux[4]][D_801F59E0];

    func_801239AC(player);
}

void func_80123BD4(Player* player, s32 arg1) {
    player->modelGroup = arg1;

    if (arg1 == 1) {
        player->modelAnimType = 0;
    } else {
        player->modelAnimType = D_801BFFB0[arg1][0];
    }

    if ((player->modelAnimType < 3) && ((((player->transformation != PLAYER_FORM_FIERCE_DEITY)) && (player->transformation != PLAYER_FORM_HUMAN)) || (player->currentShield == 0))) {
        player->modelAnimType = 0;
    }

    func_80123AA4(player, arg1);
}

void func_80123C58(Player* player) {
    player->heldItemActionParam = player->itemActionParam;
    func_80123BD4(player, func_80123960(player, player->itemActionParam));
    player->unk_AA5 = 0;
}

extern u8 D_801BFF90[];

void func_80123C90(GlobalContext* globalCtx, Player* player) {
    if (player->unk_394 != 0x86) {
        player->currentShield = CUR_EQUIP_VALUE_VOID(EQUIP_SHIELD);
        if ((player->transformation != 2) || (((player->currentBoots != PLAYER_BOOTS_ZORA_LAND)) && (player->currentBoots != PLAYER_BOOTS_ZORA_UNDERWATER))) {
            player->currentBoots = D_801BFF90[player->transformation];
        }
        func_80123BD4(player, func_80123960(player, player->itemActionParam));
        func_80123140(globalCtx, player);
        if (player->unk_B62 != 0) {
            player->unk_B62 = 1;
        }
    }
}

void func_80123D50(GlobalContext* globalCtx, Player* player, s32 arg2, s32 arg3) {
    func_80114FD0(globalCtx, arg2, player->heldItemButton);
    if (arg2 != 0x12) {
        player->heldItemId = arg2;
        player->itemActionParam = arg3;
    }
    player->heldItemActionParam = arg3;
}

void func_80123DA4(Player* player) {
    player->unk_730 = NULL;
    player->stateFlags2 &= ~0x2000;
}

void func_80123DC0(Player* player) {
    if ((player->actor.bgCheckFlags & 1) || (player->stateFlags1 & (0x8000000 | 0x800000 | 0x200000)) || (!(player->stateFlags1 & 0xC0000) && ((player->actor.world.pos.y - player->actor.floorHeight) < 100.0f))) {
        player->stateFlags1 &= ~(0x40000000 | 0x80000 | 0x40000| 0x30000 | 0x10000 | 0x8000);
    } else if (!(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000))) {
        player->stateFlags1 |= 0x80000;
    } else if ((player->stateFlags1 & 0x40000) && (player->transformation == PLAYER_FORM_DEKU)) {
        player->stateFlags1 &= ~(0x40000000 | 0x20000 | 0x10000 | 0x8000);
    }
    func_80123DA4(player);
}

void func_80123E90(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    func_80123DC0(player);
    player->unk_730 = actor;
    player->unk_A78 = actor;
    player->stateFlags1 |= 0x10000;
    func_800DFD78(Play_GetCamera(globalCtx, MAIN_CAM), 8, actor);
    func_800DF840(Play_GetCamera(globalCtx, MAIN_CAM), 9);
}

s32 func_80123F14(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->stateFlags1 & 0x800000;
}

s32 func_80123F2C(GlobalContext* globalCtx, s32 arg1) {
    globalCtx->unk_1887C = arg1 + 1;

    return 1;
}

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

    return player->transformation == PLAYER_FORM_HUMAN && player->currentShield == 2;
}

s32 func_80124088(GameState* gameState) {
    Player* player = GET_PLAYER(gameState);

    return player->transformation == PLAYER_FORM_HUMAN && player->rightHandType == 8 && player->currentShield == 2;
}

s32 func_801240C8(Player* player) {
    return player->itemActionParam == 0xD;
}

s32 func_801240DC(Player* player) {
    return func_801240C8(player) && player->leftHandActor == NULL;
}

s32 func_80124110(Player* player, s32 actionParam) {
    s32 temp_v0 = actionParam - PLAYER_AP_UNK_2;

    if (((player->transformation != PLAYER_FORM_GORON) && ((actionParam - PLAYER_AP_UNK_2) > (PLAYER_AP_UNK_2 - PLAYER_AP_UNK_2))) && ((actionParam - PLAYER_AP_UNK_2) < (PLAYER_AP_SWORD_GREAT_FAIRY - PLAYER_AP_UNK_2))) {
        return temp_v0;
    }

    return 0;
}

s32 func_80124148(Player* player) {
    return func_80124110(player, player->itemActionParam);
}

// Player_ActionToSword
s32 func_80124168(s32 actionParam) {
    s32 sword = actionParam - PLAYER_AP_UNK_2;

    if ((sword > (PLAYER_AP_UNK_2 - PLAYER_AP_UNK_2)) && (sword <= (PLAYER_AP_UNK_8 - PLAYER_AP_UNK_2))) {
        return sword;
    }
    return 0;
}

// Player_GetSwordHeld
s32 func_80124190(Player* player) {
    return func_80124168(player->itemActionParam);
}

// Player_HoldsTwoHandedWeapon
s32 func_801241B4(Player* player) {
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
    if ((explosive >= (PLAYER_AP_BOMB-PLAYER_AP_BOMB)) && (explosive <= (PLAYER_AP_BOMBCHU-PLAYER_AP_BOMB))) {
        return explosive;
    }

    return -1;
}

s32 Player_GetExplosiveHeld(Player* player) {
    return Player_ActionToExplosive(player, player->itemActionParam);
}

s32 func_80124278(Actor* actor, s32 arg1) {
    s32 phi_v1 = 0;

    // Fake match?
    if ((arg1 == 1) || ((phi_v1 = arg1 - 3, (phi_v1 >= 0)) && (phi_v1 < 4))) {
        return phi_v1;
    }
    return -1;
}

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

#ifdef NON_EQUIVALENT
// Float fun, maybe equivalent
void func_80124F18(s16* arg0, f32* arg1, s16 arg2, f32 arg3, f32 arg4) {
    f32 phi_f12;

    if (*arg0 < arg2) {
        *arg1 += arg3;
    } else {
        *arg1 -= arg3;
    }

    if (*arg1 < -arg4) {
        phi_f12 = -arg4;
    } else if (arg4 < *arg1) {
        phi_f12 = arg4;
    } else {
        phi_f12 = *arg1;
    }

    *arg1 = phi_f12;
    *arg0 += (s16)*arg1;
    if (((s16) *arg1 * (arg2 - *arg0)) < 0) {
        *arg0 = arg2;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124F18.s")
#endif

//void func_80124FF0(f32 arg0, s16 arg1, f32* arg2, s16 arg3, Vec3f* arg4, Vec3f* arg5, s16* arg6, f32* arg7, f32 arg8, s16 arg9);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124FF0.s")

void func_801251C4(Player* player, Vec3f* arg1);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801251C4.s")

void func_80125318(Vec3f* arg0, Vec3s* arg1) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    arg1->x = 0;
    arg1->y = 0;
    arg1->z = 0;
}

extern s32 D_801C0958 /* = false */;

void func_80125340(void) {
    Matrix_StatePush();
    D_801C0958 = true;
}

void func_8012536C(void) {
    if (D_801C0958) {
        Matrix_StatePop();
        D_801C0958 = false;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801253A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125500.s")

s32 func_80125580(GlobalContext* globalCtx, Vec3s* arg1, s32* arg2, Vec3f* arg3, Vec3s* arg4, Player* player);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125580.s")

void func_80125CE0(Player* player, f32* arg1, Vec3f* arg2, Vec3s* arg3) {
    Matrix_JointPosition(arg2, arg3);
    func_80125318(arg2, arg3);
    func_80124618(arg1, player->skelAnime.curFrame, player->unk_AF0);
    Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, 1);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801262C8.s")

s32 func_801263FC(GlobalContext* globalCtx, Vec3s* arg1, s32* arg2, Vec3f* arg3, Vec3s* arg4, Player* player) {
    if (func_80125580(globalCtx, arg1, arg2, arg3, arg4, player) == 0) {
        *arg2 = 0;
    }
    return 0;
}

s32 func_80126440(GlobalContext* globalCtx, ColliderQuad* collider, WeaponInfo* weaponInfo, Vec3f* arg3, Vec3f* arg4) {
    if (weaponInfo->active == 0) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }
        Math_Vec3f_Copy(&weaponInfo->tip, arg3);
        Math_Vec3f_Copy(&weaponInfo->base, arg4);
        weaponInfo->active = 1;

        return 1;
    } else if ((weaponInfo->tip.x == arg3->x) && (weaponInfo->tip.y == arg3->y) && (weaponInfo->tip.z == arg3->z) && (weaponInfo->base.x == arg4->x) && (weaponInfo->base.y == arg4->y) && (weaponInfo->base.z == arg4->z)) {
        if (collider != NULL) {
            Collider_ResetQuadAT(globalCtx, &collider->base);
        }

        return 0;
    } else {
        if (collider != NULL) {
            Collider_SetQuadVertices(collider, arg4, arg3, &weaponInfo->base, &weaponInfo->tip);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &collider->base);
        }
        Math_Vec3f_Copy(&weaponInfo->base, arg4);
        Math_Vec3f_Copy(&weaponInfo->tip, arg3);
        weaponInfo->active = 1;

        return 1;
    }
}

extern u8 D_801C096C[];

void func_801265C8(GlobalContext* globalCtx, Player* player, ColliderQuad* arg2, Vec3f* arg3) {
    if (player->stateFlags1 & 0x400000) {
        Vec3f sp4C;
        Vec3f sp40;
        Vec3f sp34;
        Vec3f sp28;

        player->shieldQuad.base.colType = D_801C096C[player->currentShield];
        Matrix_MultiplyVector3fByState(&arg3[0], &sp28);
        Matrix_MultiplyVector3fByState(&arg3[1], &sp34);
        Matrix_MultiplyVector3fByState(&arg3[2], &sp40);
        Matrix_MultiplyVector3fByState(&arg3[3], &sp4C);
        Collider_SetQuadVertices(arg2, &sp28, &sp34, &sp40, &sp4C);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &arg2->base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &arg2->base);
    }
}

void func_8012669C(GlobalContext* globalCtx, Player* player, Vec3f* arg2, Vec3f* arg3) {
    Vec3f sp3C;
    Vec3f sp30;

    Matrix_MultiplyVector3fByState(arg2, &sp3C);
    Matrix_MultiplyVector3fByState(arg3, &sp30);

    if (player->swordState != 0) {
        if ((func_80126440(globalCtx, NULL, &player->swordInfo[0], &sp3C, &sp30) != 0) && (player->transformation != PLAYER_FORM_GORON) && (!(player->stateFlags1 & 0x400000))) {
            func_800A81F0(Effect_GetParams(player->blureEffectIndex[0]), &player->swordInfo[0].tip, &player->swordInfo[0].base);
        }
        if ((player->swordState > 0) && ((player->swordAnimation < 0x1E) || (player->stateFlags2 & 0x20000))) {
            Matrix_MultiplyVector3fByState(&arg2[1], &sp3C);
            Matrix_MultiplyVector3fByState(&arg3[1], &sp30);
            func_80126440(globalCtx, &player->swordQuads[0], &player->swordInfo[1], &sp3C, &sp30);
            Matrix_MultiplyVector3fByState(&arg2[2], &sp3C);
            Matrix_MultiplyVector3fByState(&arg3[2], &sp30);
            func_80126440(globalCtx, &player->swordQuads[1], &player->swordInfo[2], &sp3C, &sp30);
        }
    } else {
        Math_Vec3f_Copy(&player->swordInfo[0].tip, &sp3C);
        Math_Vec3f_Copy(&player->swordInfo[0].base, &sp30);
    }
}

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
