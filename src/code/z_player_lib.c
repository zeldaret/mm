#include "global.h"
#include "objects/gameplay_keep/gameplay_keep.h"



extern Gfx D_0600E2A0[];
extern Gfx D_0600E088[];

extern s16 D_801BFDA0[];

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

extern u8 D_801BFDE8[];

extern UNK_PTR D_801BFE00[];

extern s16 D_801BFE14[][18];

extern u16 D_801BFF34[4];

extern u8 D_801BFF3C[];

extern u8 D_801BFF90[];

extern u8 D_801BFF98[];

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ u16 unk_02;
} struct_801BFFA0;

extern struct_801BFFA0 D_801BFFA0[];

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

extern Gfx* D_801BFFFC[];

#if 0
glabel D_801C0024
#endif

extern Gfx* D_801C0034[];

#if 0
glabel D_801C0040
#endif

extern Gfx* D_801C005C[];

#if 0
glabel D_801C0060
glabel D_801C0070
#endif

extern Gfx* D_801C0084[];

#if 0
glabel D_801C00A0
#endif

#if 0
glabel D_801C00AC
glabel D_801C00BC
glabel D_801C00D4
#endif

extern Gfx* D_801C00EC[];
extern Gfx* D_801C0114[];
extern Gfx* D_801C013C[];
extern Gfx* D_801C0164[];

#if 0
glabel D_801C018C
#endif

extern Gfx* D_801C01A4[];
extern Gfx* D_801C01CC[];
extern Gfx* D_801C01F4[];
extern Gfx* D_801C021C[];
extern Gfx* D_801C0244[];
extern Gfx* D_801C026C[];


#if 0
static s32 D_801C0294[5] = { 0x6006C38, 0x600A220, 0x600C020, 0x6003AB8, 0x600D3D8 };
static s32 D_801C02A8[5] = { 0x6006EB8, 0x600A500, 0x600C270, 0x6003BC0, 0x600E1C8 };
static s32 D_801C02BC[5] = { 0x6006410, 0x6009A98, 0x600B820, 0x60036B0, 0x600CCE0 };
static s32 D_801C02D0[5] = { 0x60067D8, 0x60038C0, 0x600FBB8, 0x60038C0, 0x6018490 };
static s32 D_801C02E4[5] = { 0x60067D8, 0x60038C0, 0x600FBB8, 0x60038C0, 0x6017B40 };
#endif
extern Gfx* D_801C0294[PLAYER_FORM_MAX];
extern Gfx* D_801C02A8[PLAYER_FORM_MAX];
extern Gfx* D_801C02BC[PLAYER_FORM_MAX];
extern Gfx* D_801C02D0[PLAYER_FORM_MAX];
extern Gfx* D_801C02E4[PLAYER_FORM_MAX];

// sPlayerDListGroups
extern Gfx** D_801C02F8[]; /* = {
    D_801C0114,
    D_801C013C,
    D_801C0164,
    D_801C00EC,
    D_801C0114,
    D_801C026C,
    D_801C01A4,
    D_801C01CC,
    D_801C01CC,
    D_801C01F4,
    D_801C021C,
    D_801C0244,
    D_801C0034,
    D_801C005C,
    D_801C0084,
    D_801C0084,
    D_801BFFFC,
    NULL,
};*/


#if 0
glabel D_801C0340
glabel D_801C0368
glabel D_801C03A0
#endif

extern struct_80124618 D_801C03C0[];
extern struct_80124618 D_801C03E0[];

#if 0
glabel D_801C0410
glabel D_801C0428
#endif

extern struct_80124618 D_801C0460[];

#if 0
glabel D_801C0490
glabel D_801C0510
glabel D_801C0538
glabel D_801C0560
glabel D_801C0580
glabel D_801C05A8
glabel D_801C05C8
glabel D_801C05D8
glabel D_801C05F0
glabel D_801C05F2
glabel D_801C05FA
#endif
extern struct_80124618 D_801C0608[];
extern struct_80124618 D_801C0628[];

extern struct_80124618 D_801C0678[];
extern struct_80124618 D_801C0698[];
extern struct_80124618 D_801C06B8[];
extern struct_80124618 D_801C06E0[];
extern struct_80124618 D_801C06F8[];
extern struct_80124618 D_801C0718[];
extern struct_80124618 D_801C0730[];
extern struct_80124618 D_801C0740[];

extern struct_80124618 D_801C0750[];

extern u8 D_801C0778[];

extern struct_80124618 D_801C0784[];

extern u8 D_801C07AC[];

extern struct_80124618 D_801C07C0[];

extern struct_80124618 D_801C07F0[];
extern struct_80124618 D_801C0820[];
extern struct_80124618 D_801C0838[];

extern Gfx D_801C0850[];
extern Gfx D_801C0860[];

extern UNK_PTR D_801C0870[];
extern void* D_801C0890[];
extern u8 D_801C08A0[][2];

extern Vec3f D_801C08C0[];

extern f32 D_801C08FC[];
extern f32 D_801C0910[];
extern f32 D_801C0924[];
extern f32 D_801C0938[];

extern Vec3f D_801C094C;

extern s32 D_801C0958 /* = false */;

#if 0
glabel D_801C095C
glabel D_801C0964
#endif
extern u8 D_801C096C[];

#if 0
Vec3f D_801C0970[3] = {
    { 0.0f, 400.0f, 0.0f },
    { 0.0f, 1400.0f, -1000.0f },
    { 0.0f, -400.0f, 1000.0f },
};
#endif

extern Vec3f D_801C0970[3];

#if 0
static Vec3f D_801C0994[3] = {
    { 5000.0f, 400.0f, 0.0f },
    { 5000.0f, -400.0f, 1000.0f },
    { 5000.0f, 1400.0f, -1000.0f },
};
#endif
extern Vec3f D_801C0994[];

#if 0
Vec3f D_801C09B8[3] = {
    { 0.0f, 750.0f, 750.0f },
    { 1500.0f, 1500.0f, 1500.0f },
    { -2500.0f, -2000.0f, -3000.0f },
};
#endif
extern Vec3f D_801C09B8[];

#if 0
glabel D_801C09DC
glabel D_801C0A00
glabel D_801C0A24
glabel D_801C0A48
glabel D_801C0A6C
glabel D_801C0A90
glabel D_801C0AB4
glabel D_801C0ABC
glabel D_801C0ADC
#endif

extern struct_80124618* D_801C0AF4[];
extern struct_80124618* D_801C0AFC[];
extern struct_80124618* D_801C0B04[];
extern struct_80124618* D_801C0B0C[];

extern Gfx* D_801C0B14[];

extern Gfx* D_801C0B1C[];

extern Gfx* D_801C0B20[];

extern Vec3f D_801C0B90[2];





// bss

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} struct_801F58B0; // size = 0x1C

extern struct_801F58B0 D_801F58B0[3][3];

extern struct_801F58B0 D_801F59AC[][3];

extern Vec3f D_801F59B0[2];

extern s32 D_801F59C8[2];

typedef struct {
    /* 0x00 */ s16 unk_0;
    /* 0x02 */ s16 unk_2;
    /* 0x04 */ s16 unk_4;
    /* 0x06 */ s16 unk_6;
    /* 0x08 */ s16 unk_8;
} struct_801F59D0;

extern struct_801F59D0 D_801F59D0;

extern s32 D_801F59E0;

extern s32 D_801F59E4;

extern Vec3f D_801F59E8;

extern s32 D_801F59F4;
extern s32 D_801F59F8;

















void func_80127B64(struct_801F58B0 arg0[], UNK_TYPE arg1, Vec3f* arg2);





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

// Load mask?
void func_801229FC(Player* player) {
    if (player->maskObjectLoading == 1) {
        // TODO: check if player->maskId is unsigned
        s16 temp_s1 = D_801BFDA0[(u8)player->maskId-1];

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

u8 func_80122ED8(s32 index) {
    return D_801BFDE8[index];
}

u8 func_80122EEC(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

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
void func_80123140(GlobalContext* globalCtx, Player* player) {
    s16* bootRegs;
    s32 currentBoots;
    f32 scale;

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        gGameInfo->data[0x1B] = 0x4B0;
    } else {
        gGameInfo->data[0x1B] = 0x7D0;
    }

    gGameInfo->data[0x30] = 0x172;

    currentBoots = player->currentBoots;
    if (currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
        if (player->stateFlags1 & 0x8000000) {
            currentBoots++;
        }
        if (player->transformation == PLAYER_FORM_GORON) {
            gGameInfo->data[0x30] = 0xC8;
        }
    } else if (currentBoots == PLAYER_BOOTS_GIANT) {
        gGameInfo->data[0x30] = 0xAA;
    }

    bootRegs = D_801BFE14[currentBoots];
    gGameInfo->data[0x13] = bootRegs[0];
    gGameInfo->data[0x1E] = bootRegs[1];
    gGameInfo->data[0x20] = bootRegs[2];
    gGameInfo->data[0x22] = bootRegs[3];
    gGameInfo->data[0x23] = bootRegs[4];
    gGameInfo->data[0x24] = bootRegs[5];
    gGameInfo->data[0x25] = bootRegs[6];
    gGameInfo->data[0x26] = bootRegs[7];
    gGameInfo->data[0x27] = bootRegs[8];
    gGameInfo->data[0x2B] = bootRegs[9];
    gGameInfo->data[0x2D] = bootRegs[10];
    gGameInfo->data[0x44] = bootRegs[11];
    gGameInfo->data[0x45] = bootRegs[12];
    gGameInfo->data[0x3A2] = bootRegs[13];
    gGameInfo->data[0x3A3] = bootRegs[14];
    gGameInfo->data[0x3A4] = bootRegs[15];
    gGameInfo->data[0x3A5] = bootRegs[16];
    gGameInfo->data[0x23F] = bootRegs[17];

    if (globalCtx->roomCtx.currRoom.unk3 == 2) {
        gGameInfo->data[0x2D] = 0x1F4;
    }

    if ((player->actor.id == ACTOR_PLAYER) && (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
        scale = 0.015f;
    } else {
        scale = 0.01f;
    }

    Actor_SetScale(&player->actor, scale);
}


s32 Player_InBlockingCsMode(GlobalContext* globalCtx, Player* player) {
    return (player->stateFlags1 & 0x20000280) || player->unk_394 != 0 || globalCtx->sceneLoadFlag == 0x14 ||
           globalCtx->unk_18B4A != 0 || (player->stateFlags1 & 1) || (player->stateFlags3 & 0x80) ||
           globalCtx->actorCtx.unk268 != 0;
}

s32 Player_InCsMode(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return Player_InBlockingCsMode(globalCtx, player) || player->unk_AA5 == 5;
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

s32 func_80123590(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

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

#ifdef NON_MATCHING
// regalloc and a few missing moves
s32 func_8012364C(GlobalContext* globalCtx, Player* player, s32 arg2) {
    s32 phi_v1;

    if (arg2 >= 4) {
        if (1) {}
        return 0xFF;
    }

    if (arg2 == 0) {
        phi_v1 = func_8012EC80(globalCtx);
        if (phi_v1 >= 0xFD) {
            return phi_v1;
        }

        if ((player->currentMask == PLAYER_MASK_BLAST) && (globalCtx->interfaceCtx.unk_21E == 0x18)) {
            return 0xF0;
        }
        if ((player->currentMask == PLAYER_MASK_BREMEN) && (globalCtx->interfaceCtx.unk_21E == 0x1A)) {
            return 0xF1;
        }
        if ((player->currentMask == PLAYER_MASK_KAMARO) && (globalCtx->interfaceCtx.unk_21E == 0x19)) {
            return 0xF2;
        }
    } else {
        s32 phi_v0;

        dummy_label_74791: ;

        if (arg2 == 1) {
            if (gSaveContext.buttonStatus[1] != 0xFF) {
                //if (gSaveContext.equips.buttonItems && gSaveContext.equips.buttonItems) {}
                return gSaveContext.equips.buttonItems[0][1];
            } 

            if (gSaveContext.unk_3F22 == 0x10) {
                phi_v0 = gSaveContext.equips.buttonItems[0][1];
            } else {
                phi_v0 = 0xFF;
            }

            phi_v1 = phi_v0;
        } else if (arg2 == 2) {
            if (gSaveContext.buttonStatus[2] != 0xFF) {
                return gSaveContext.equips.buttonItems[0][2];
            }

            if (gSaveContext.unk_3F22 == 0x10) {
                phi_v0 = gSaveContext.equips.buttonItems[0][2];
            } else {
                phi_v0 = 0xFF;
            }
            phi_v1 = phi_v0;
        } else if (gSaveContext.buttonStatus[3] != 0xFF) {
            phi_v1 = gSaveContext.equips.buttonItems[0][3];
        } else {
            if (gSaveContext.unk_3F22 == 0x10) {
                if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } if (1) { }
                phi_v0 = gSaveContext.equips.buttonItems[0][3];
            } else {
                phi_v0 = 0xFF;
            }
            phi_v1 = phi_v0;
            //phi_v1 = gSaveContext.unk_3F22 == 0x10 ? gSaveContext.equips.buttonItems[0][3] : 0xFF;
        }
    }

    if (!gSaveContext.unk_3F22) {}

    return phi_v1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_8012364C.s")
#endif


#ifdef NON_EQUIVALENT
s32 func_80123810(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    Input* input = CONTROLLER1(globalCtx);

    if (gSaveContext.unk_06 == 0) {
        if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_B)) {
            globalCtx->interfaceCtx.unk_222 = 0;
            globalCtx->interfaceCtx.unk_224 = 0;
            Interface_ChangeAlpha(globalCtx->msgCtx.unk_120BC);
            return -1;
        }
    } else {
        gSaveContext.unk_06--;
    }

    for (i = 0; i < ARRAY_COUNT(D_801BFF34); i++) {
        if (CHECK_BTN_ALL(input->press.button, D_801BFF34[i])) {
            s32 temp_v0;
            s32 sp24 = func_8012364C(globalCtx, player, i + 1);

            globalCtx->interfaceCtx.unk_222 = 0;
            globalCtx->interfaceCtx.unk_224 = 0;
            Interface_ChangeAlpha(globalCtx->msgCtx.unk_120BC);
            if ((sp24 >= 0xFD) || ( temp_v0 = globalCtx->unk_18794(globalCtx, player, sp24, i + 1), (temp_v0 < 0))) {
                play_sound(0x4806);
                return -1;
            }
            player->heldItemButton = i + 1;
            return temp_v0;
        }
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80123810.s")
#endif

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

void Player_SetEquipmentData(GlobalContext* globalCtx, Player* player) {
    if (player->unk_394 != 0x86) {
        player->currentShield = CUR_EQUIP_VALUE_VOID(EQUIP_SHIELD);
        if ((player->transformation != PLAYER_FORM_ZORA) || (((player->currentBoots != PLAYER_BOOTS_ZORA_LAND)) && (player->currentBoots != PLAYER_BOOTS_ZORA_UNDERWATER))) {
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

s32 func_8012405C(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->transformation == PLAYER_FORM_HUMAN && player->currentShield == 2;
}

s32 func_80124088(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

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
    if (!Player_InCsMode(globalCtx)) {
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

void func_80124618(struct_80124618* arg0, f32 curFrame, Vec3f* arg2) {
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

    progress = (curFrame - temp_f0) / (((f32) temp_v1) - temp_f0);

    temp_f14 = arg0[-1].unk_2.x;
    arg2->x = LERPIMP(temp_f14, arg0->unk_2.x, progress) * 0.01f;

    temp_f14 = arg0[-1].unk_2.y;
    arg2->y = LERPIMP(temp_f14, arg0->unk_2.y, progress) * 0.01f;

    temp_f14 = arg0[-1].unk_2.z;
    arg2->z = LERPIMP(temp_f14, arg0->unk_2.z, progress) * 0.01f;
}

// OoT's func_8008F470
void func_801246F4(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod, s32 tunic, s32 boots, s32 face, OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor) {
    s32 phi_v1 = (jointTable[0x16].x & 0xF) - 1; // eyeIndex
    s32 phi_t1 = (((s32) jointTable[0x16].x >> 4) & 0xF) - 1; // mouthIndex
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    dl = POLY_OPA_DISP;

    if (phi_v1 < 0) {
        phi_v1 = D_801C08A0[face][0];
    }

    if (tunic == 1) {
        if ((phi_v1 >= 3) && (phi_v1 < 7)) {
            phi_v1 = 0;
        } else if (phi_v1 == 7) {
            phi_v1 = 3;
        }
    }

    gSPSegment(&dl[0], 0x08, Lib_SegmentedToVirtual(D_801C0870[phi_v1]));

    if (phi_t1 < 0) {
        phi_t1 = D_801C08A0[face][1];
    }

    gSPSegment(&dl[1], 0x09, Lib_SegmentedToVirtual(D_801C0890[phi_t1]));

    POLY_OPA_DISP = &dl[2];

    D_801F59E0 = tunic * 2;
    D_801F59E4 = lod;
    SkelAnime_DrawFlexLod(globalCtx, skeleton, jointTable, dListCount, overrideLimbDraw, postLimbDraw, actor, lod);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124870.s")

#ifdef NON_MATCHING
// Matches, but requires in function static data
void func_80124CC4(GlobalContext* globalCtx, Actor* actor, f32 arg2) {
    static Vec3f D_801C094C = { -500.0f, -100.0f, 0.0f };
    CollisionPoly* poly;
    s32 bgId;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    f32 sp54;
    f32 sp50;

    D_801C094C.z = 0.0f;
    Matrix_MultiplyVector3fByState(&D_801C094C, &sp7C);
    D_801C094C.z = arg2;
    Matrix_MultiplyVector3fByState(&D_801C094C, &sp70);

    if (BgCheck_AnyLineTest3(&globalCtx->colCtx, &sp7C, &sp70, &sp64, &poly, 1, 1, 1, 1, &bgId)) {
        if (func_800B90AC(globalCtx, actor, poly, bgId, &sp64) == 0 || BgCheck_ProjectileLineTest(&globalCtx->colCtx, &sp7C, &sp70, &sp64, &poly, 1, 1, 1, 1, &bgId)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            OVERLAY_DISP = Gfx_CallSetupDL(OVERLAY_DISP, 7);

            SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &sp64, &sp58, &sp54);
            if (sp54 < 200.0f) {
                sp50 = 0.08f;
            } else {
                sp50 = (sp54 / 200.0f) * 0.08f;
            }
            Matrix_InsertTranslation(sp64.x, sp64.y, sp64.z, MTXMODE_NEW);
            Matrix_Scale(sp50, sp50, sp50, 1);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPSegment(OVERLAY_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);

            gSPDisplayList(OVERLAY_DISP++, gameplay_keep_DL_04F250);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
#else
void func_80124CC4(GlobalContext* globalCtx, Actor* actor, f32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124CC4.s")
#endif

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
void func_80124F18(s16* arg0, f32* arg1, s16 arg2, f32 arg3, f32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124F18.s")
#endif

#ifdef NON_EQUIVALENT
// This is weird...
void func_80124FF0(f32 arg0, s16 arg1, Vec3f* arg2, s16 arg3, Vec3f* arg4, Vec3f* arg5, s16* arg6, f32* arg7, f32 arg8, s16 arg9, s16* arg10, f32* arg11, UNK_TYPE arg12) {
    Vec3f sp44;
    f32 sp40;
    volatile s16 sp3C;
    f32 sp34;
    f32 sp30;
    //s32 sp28;
    //s32 sp24;
    f32 temp_f14;
    s32 temp_v0_2;
    s16 phi_a1;
    //s32 phi_v1;
    s32 phi_v0;
    s16 phi_a2;

    sp34 = Math_CosS(arg1) * arg0;
    sp30 = Math_SinS(arg1) * -arg0;

    arg5->x = (Math_SinS(arg3) * sp30) + arg2->x;
    arg5->y = arg2->y + sp34;
    arg5->z = (Math_CosS(arg3) * sp30) + arg2->z;

    Math_Vec3f_Diff(arg5, arg4, &sp44);
    sp40 = sqrtf(SQ(sp44.x) + SQ(sp44.z));
    if (sp40 <= 1.0f) {
        phi_a1 = arg3;
    } else {
        phi_a1 = Math_FAtan2F(sp44.z, sp44.x);
    }

    phi_v0 = phi_a1 - arg3;
    //sp24 = (s32) phi_v0;
    //sp28 = (s32) phi_v0;
    temp_f14 = (Math_CosS(phi_v0) * sp40) + arg8;

    if (ABS_ALT(phi_v0) > 0x4000) {
        phi_v0 = (s16) BINANG_ROT180(phi_a1) - arg3;
    }
    sp3C = phi_v0;

    temp_v0_2 = Math_FAtan2F(sp44.y, temp_f14);
    phi_a2 = (s32) arg9 * -1;
    phi_a2 = phi_a2;
    if ((temp_v0_2 >= (s32) phi_a2)) {

        phi_a2 = CLAMP_MAX(temp_v0_2, arg9);
    }

    func_80124F18(arg6, arg7, phi_a2, 20.0f, 2000.0f);
}
#else
void func_80124FF0(f32 arg0, s16 arg1, Vec3f* arg2, s16 arg3, Vec3f* arg4, Vec3f* arg5, s16* arg6, f32* arg7, f32 arg8, s16 arg9, s16* arg10, f32* arg11, UNK_TYPE arg12);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80124FF0.s")
#endif

void func_801251C4(Player* player, Vec3f* arg1) {
    Vec3f sp4C;
    Vec3f sp40;

    sp4C.x = player->actor.world.pos.x;
    sp4C.y = player->actor.world.pos.y + 60.0f;
    sp4C.z = player->actor.world.pos.z;
    func_80124FF0(-20.0f, player->unk_B8C, &sp4C, player->actor.shape.rot.y, player->bodyPartsPos, arg1, &player->unk_B90, &player->unk_B08[2], 0.0f, 0x1F40, &player->unk_B92, &player->unk_B08[3], 0);

    sp40.x = (player->bodyPartsPos[6].x + player->bodyPartsPos[3].x) * 0.5f;
    sp40.y = (player->bodyPartsPos[6].y + player->bodyPartsPos[3].y) * 0.5f;
    sp40.z = (player->bodyPartsPos[6].z + player->bodyPartsPos[3].z) * 0.5f;
    func_80124FF0(-20.0f, player->unk_B90, arg1, (player->actor.shape.rot.y + player->unk_B92), &sp40, arg1, &player->unk_B94, &player->unk_B08[4], -1.9f, 0x1F40, &player->unk_B96, &player->unk_B08[5], 0);
}

void func_80125318(Vec3f* arg0, Vec3s* arg1) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    arg1->x = 0;
    arg1->y = 0;
    arg1->z = 0;
}

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

extern AnimatedMaterial D_06012A80;

extern UNK_TYPE D_06011210;
extern UNK_TYPE D_06011710;

extern Gfx D_06011760[];

#ifdef NON_MATCHING
void func_801253A4(GlobalContext* globalCtx, Player* player) {
    Vtx* sp30;
    Gfx* dl;
    s32 i;
    f32 sp28; // scale
    u8* phi_a0;

    sp28 = player->unk_B62 * 0.19607843f;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(&D_06012A80));
    Matrix_Scale(sp28, sp28, sp28, 1);

    // clang-format off
    sp30 = Lib_SegmentedToVirtual(&D_06011210); phi_a0 = Lib_SegmentedToVirtual(&D_06011710);
    // clang-format on

    for (i = 0; i < 0x50; i++) {
        sp30[i].v.cn[3] = (phi_a0[i] * player->unk_B62) >> 8;
    }

    dl = POLY_XLU_DISP;

    gSPMatrix(&dl[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[1], D_06011760);

    POLY_XLU_DISP = &dl[2];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801253A4.s")
#endif

void func_80125500(GlobalContext* globalCtx, Player* player, UNK_PTR arg2, UNK_TYPE arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125500.s")

extern Vec3f* D_801F59DC;

typedef struct {
    /* 0x000 */ Actor actor;
    /* 0x144 */ f32 unk_144;
} ActorUnknown;


#ifdef NON_EQUIVALENT
// maybe equivalent?
s32 func_80125580(GlobalContext* globalCtx, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Player* player) {
    Vec3f sp54;
    Actor* sp50;
    s32 pad[4];
    f32 temp_f6;
    Actor* phi_v0;
    struct_80124618* phi_a0;
    s16 phi_a0_2;
    struct_80124618* phi_v0_2;
    struct_80124618* phi_v1_2;

    if (arg1 == 1) {
        D_801F59F4 = (s32) player->leftHandType;

        if (1) { }

        D_801F59F8 = (s32) player->rightHandType;
        D_801F59DC = &player->swordInfo[2].base;
        if (player->transformation != PLAYER_FORM_FIERCE_DEITY) {
            if (!(player->skelAnime.moveFlags & 4) || (player->skelAnime.moveFlags & 1)) {
                arg3->x *= player->ageProperties->unk_08;
                arg3->z *= player->ageProperties->unk_08;
            }
            if (!(player->skelAnime.moveFlags & 4) || (player->skelAnime.moveFlags & 2)) {
                arg3->y *= player->ageProperties->unk_08;
            }
        }

        arg3->y -= player->unk_AB8;
        if ((player->transformation == PLAYER_FORM_ZORA) && ((player->stateFlags3 & 0x8000) != 0)) {
            Matrix_InsertTranslation(arg3->x, ((Math_CosS(player->unk_AAA) - 1.0f) * 200.0f) + arg3->y, arg3->z, 1);
            Matrix_InsertXRotation_s(player->unk_AAA, 1);
            if (player->unk_B62 != 0) {
                Matrix_StatePush();
                Matrix_InsertZRotation_s(player->unk_B8E, 1);
                Matrix_InsertRotation(arg4->x, arg4->y, arg4->z, 1);
                Matrix_InsertXRotation_s(-0x8000, 1);
                Matrix_InsertTranslation(0.0f, 0.0f, -4000.0f, 1);
                func_801253A4(globalCtx, player);
                Matrix_StatePop();
            }
            Matrix_InsertZRotation_s(player->unk_B88, 1);
            Matrix_InsertRotation(arg4->x, arg4->y, arg4->z, 1);
            func_80125318(arg3, arg4);
        } else if ((player->stateFlags3 & 0x2000) != 0) {
            func_801251C4(player, &sp54);
            sp54.x -= player->actor.world.pos.x;
            sp54.y -= player->actor.world.pos.y;
            sp54.z -= player->actor.world.pos.z;
            Matrix_InsertTranslation(arg3->x + sp54.x, arg3->y + sp54.y, arg3->z + sp54.z, 1);
            Matrix_InsertXRotation_s(player->unk_B94, 1);
            Matrix_InsertZRotation_s(player->unk_B8E, 1);
            player->unk_AB2.x = player->unk_B90 - player->unk_B94;
            Matrix_InsertRotation(arg4->x, arg4->y, arg4->z, 1);
            func_80125318(arg3, arg4);
        } else {
            if (player->unk_AAA != 0) {
                Matrix_InsertTranslation(arg3->x, ((Math_CosS(player->unk_AAA) - 1.0f) * 200.0f) + arg3->y, arg3->z, 1);
                Matrix_InsertXRotation_s(player->unk_AAA, 1);
                Matrix_InsertRotation(arg4->x, arg4->y, arg4->z, 1);
                func_80125318(arg3, arg4);
            }
        }
    } else {
        if (*arg2 != 0) {
            D_801F59DC++;
        }
        if (arg1 == 0xB) {
            arg4->x += player->unk_AAC.z;
            arg4->y -= player->unk_AAC.y;
            arg4->z += player->unk_AAC.x;
            if (player->transformation == PLAYER_FORM_DEKU) {
                phi_v0 = NULL;

                if (((&gameplay_keep_Linkanim_00E298 == player->skelAnime.animation)) || (&gameplay_keep_Linkanim_00E2F0 == player->unk_284.animation) || (((player->stateFlags3 & 0x40) != 0) && (phi_v0 = player->leftHandActor, (phi_v0 != 0)))) {
                    sp50 = phi_v0;
                    Matrix_JointPosition(arg3, arg4);
                    func_80125340();
                    func_80125318(arg3, arg4);
                    if (phi_v0 != 0) {
                        player->unk_AF0[0].x = 1.0f - (((ActorUnknown*)phi_v0)->unk_144 * 0.03f);
                        player->unk_AF0[0].y = 1.0f - (((ActorUnknown*)phi_v0)->unk_144 * 0.01f);
                        player->unk_AF0[0].z = 1.0f - (((ActorUnknown*)phi_v0)->unk_144 * 0.04f);
                        arg4->z = (s16) (s32) (((ActorUnknown*)phi_v0)->unk_144 * 320.0f);
                    } else if (&gameplay_keep_Linkanim_00E298 == player->skelAnime.animation) {
                        func_80124618(D_801C03E0, player->skelAnime.curFrame, player->unk_AF0);
                    } else {
                        func_80124618(D_801C03C0, player->unk_284.curFrame, player->unk_AF0);
                    }
                    Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, 1);
                }
            }
        } else if (arg1 == 0x15) {
            if ((&gameplay_keep_Linkanim_00E1F8 == player->skelAnime.animation) || (&gameplay_keep_Linkanim_00E260 == player->skelAnime.animation) || (&gameplay_keep_Linkanim_00E248 == player->skelAnime.animation) || (player->transformation == 2)) {
                Matrix_JointPosition(arg3, arg4);
                if (player->transformation == PLAYER_FORM_GORON) {
                    func_80125340();
                }
                func_80125318(arg3, arg4);
                if ((player->transformation != PLAYER_FORM_ZORA) || (&D_0400E410 == player->skelAnime.animation)) {
                    if (&D_0400E410 == player->skelAnime.animation) {
                        phi_a0 = D_801C0608;
                    } else {
                        if (&gameplay_keep_Linkanim_00E260 == player->skelAnime.animation) {
                            phi_v0_2 = D_801C0628;
                        } else {
                            if (&gameplay_keep_Linkanim_00E248 == player->skelAnime.animation) {
                                phi_v1_2 = D_801C07C0;
                            } else {
                                phi_v1_2 = D_801C0460;
                            }
                            phi_v0_2 = phi_v1_2;
                        }
                        phi_a0 = phi_v0_2;
                    }
                    func_80124618(phi_a0, player->skelAnime.curFrame, player->unk_AF0);
                } else {
                    player->unk_AF0[0].y = 1.0f;
                }
                if (player->transformation == PLAYER_FORM_ZORA) {
                    player->unk_AF0[0].x = 1.0f;
                    player->unk_AF0[0].z = 1.0f;
                    player->unk_AF0[0].y *= 1.0f + (0.29999995f * player->unk_B08[2]);
                }
                Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, 1);
            }
        } else if (arg1 == 0xA) {
            if (player->unk_AA8 != 0) {
                Matrix_InsertZRotation_s(0x44C, 1);
                Matrix_RotateY(player->unk_AA8, 1);
            }
            if (player->unk_AB2.y != 0) {
                Matrix_RotateY(player->unk_AB2.y, 1);
            }
            phi_a0_2 = player->unk_AB2.x;
            if ((player->transformation == PLAYER_FORM_DEKU) && ((player->stateFlags3 & 0x40) != 0)) {
                if (player->leftHandActor != 0) {
                    phi_a0_2 = (s16) (player->unk_AB2.x + (s32) (((ActorUnknown*)player->leftHandActor)->unk_144 * -470.0f));
                }
            }
            Matrix_InsertXRotation_s(phi_a0_2, 1);
            if (player->unk_AB2.z != 0) {
                Matrix_InsertZRotation_s(player->unk_AB2.z, 1);
            }
        } else {
            func_80125500(globalCtx, player, arg1, arg4);
        }
    }

    return 0;
}
#else
s32 func_80125580(GlobalContext* globalCtx, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Player* player);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125580.s")
#endif

void func_80125CE0(Player* player, struct_80124618* arg1, Vec3f* arg2, Vec3s* arg3) {
    Matrix_JointPosition(arg2, arg3);
    func_80125318(arg2, arg3);
    func_80124618(arg1, player->skelAnime.curFrame, player->unk_AF0);
    Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, 1);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80125D4C.s")


s32 func_801262C8(GlobalContext* globalCtx, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Player* player) {
    if (func_80125580(globalCtx, arg1, arg2, arg3, arg4, player) == 0) {
        if (player->unk_AA5 != 3) {
            *arg2 = NULL;
        } else if (arg1 == 0xF) {
            *arg2 = D_801C0294[player->transformation];
        } else if (arg1 == 0x10) {
            *arg2 = D_801C02A8[player->transformation];
        } else if (arg1 == 0x11) {
            *arg2 = D_801C02BC[player->transformation];
        } else if (arg1 == 0x13) {
            if (func_801240C8(player) != 0) {
                *arg2 = D_801C02E4[player->transformation];
            } else {
                *arg2 = D_801C02D0[player->transformation];
            }
        } else {
            *arg2 = NULL;
        }
    }

    return 0;
}

s32 func_801263FC(GlobalContext* globalCtx, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Player* player) {
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
            EffectBlure_AddVertex(Effect_GetByIndex(player->blureEffectIndex[0]), &player->swordInfo[0].tip, &player->swordInfo[0].base);
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

void func_80126AB4(Player* player, Vec3f** arg1) {
    if ((player->transformation == PLAYER_FORM_GORON) || (player->actor.id == ACTOR_EN_TEST3)) {
        Math_Vec3f_Copy(&player->unk_AF0[1], &player->swordInfo[0].base);
        *arg1 = D_801C09B8;
        return;
    }

    D_801C0994[1].x = D_801C0994[0].x;

    if (player->unk_ADD >= 3) {
        player->unk_ADD++;
        D_801C0994[1].x *= 1.0f + ((9 - player->unk_ADD) * 0.1f);
    }

    D_801C0994[1].x += 1200.0f;
    D_801C0994[2].x = D_801C0994[1].x;
    *arg1 = D_801C0994;
}

void func_80126B8C(GlobalContext* globalCtx, Player* player) {
    Vec3f* sp1C;

    func_80126AB4(player, &sp1C);
    func_8012669C(globalCtx, player, sp1C, D_801C0970);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80126BD0.s")

extern LinkAnimationHeader gameplay_keep_Linkanim_00E278;
extern Gfx D_06008AA0[];
extern Gfx D_06008C50[];

s32 func_801271B0(GlobalContext* globalCtx, Player* player, s32 arg2) {
    if ((player->transformation == PLAYER_FORM_DEKU) && (((player->skelAnime.animation == &D_0400E2D0)) || (player->skelAnime.animation == &D_0400E2D8) || (player->skelAnime.animation == &D_0400E2E8) || (player->skelAnime.animation == &gameplay_keep_Linkanim_00E278))) {
        struct_80124618** sp3C = D_801C0AF4;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (player->skelAnime.animation == &D_0400E2D8) {
            sp3C = D_801C0AFC;
        } else if (player->skelAnime.animation == &gameplay_keep_Linkanim_00E278) {
            sp3C = D_801C0B0C;
        } else if (player->skelAnime.animation == &D_0400E2E8) {
            sp3C = D_801C0B04;
        }

        Matrix_StatePush();
        Matrix_InsertTranslation(0.0f, 150.0f, 0.0f, 1);
        func_80124618(sp3C[0], player->skelAnime.curFrame, &player->unk_AF0[1]);
        Matrix_Scale(player->unk_AF0[1].x, player->unk_AF0[1].y, player->unk_AF0[1].z, 1);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(POLY_OPA_DISP++, D_801C0B14[arg2]);

        Matrix_InsertTranslation(2150.0f, 0.0f, 0.0f, 1);
        Matrix_InsertXRotation_s(player->unk_B8A, 1);
        func_80124618(sp3C[1], player->skelAnime.curFrame, &player->unk_AF0[1]);
        Matrix_Scale(player->unk_AF0[1].x, player->unk_AF0[1].y, player->unk_AF0[1].z, 1);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(POLY_OPA_DISP++, player->actor.velocity.y < -6.0f ? &D_06008AA0 : &D_06008C50);

        Matrix_GetStateTranslation(&player->bodyPartsPos[*((u8*)D_801C0B1C + arg2)]);
        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return 1;
    }
    return 0;
}


s32 func_80127438(GlobalContext* globalCtx, Player* player, s32 maskId) {
    if (!player->maskObjectLoading && (maskId == (u8)player->maskId)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x0A, player->maskObjectSegment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return true;
    }

    return false;
}

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

#ifdef NON_EQUIVALENT
void func_80127594(GlobalContext* globalCtx, Player* player) {
    static Vec3f D_801C0BA8 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_801C0BB4 = { 0.0f, 0.0f, 0.0f };
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    s16 temp_s0_2;
    s32 temp_v0;
    u32* temp_s0;
    Vec3f* phi_s6;
    Vec3f* phi_s2;
    s32* phi_s3;
    f32 phi_f20;
    Gfx* phi_s1;
    s32 phi_v0;
    //f32 phi_f20_2;
    s16 phi_s0;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    phi_s6 = D_801C0B90;
    phi_s2 = D_801F59B0;
    phi_s3 = D_801F59C8;
    phi_s1 = POLY_XLU_DISP;
    i = 0;
    do {
        temp_f22 = ((f32) *phi_s3 / 400.0f) * 0.1f;
        Matrix_MultiplyVector3fByState(phi_s6, phi_s2);
        phi_s2->y += -10.0f * temp_f22;
        if (*phi_s3 < 0x190) {
            //temp_s0 = &gSegments[(u32) ((s32) D_04091BE0 * 0x10) >> 0x1C];
            temp_s0 = &gSegments[(u32) ((s32) D_04091BE0 * 0x10) >> 0x1C];
            if (temp_f22 > 0.05f) {
                phi_f20 = 0.05f;
            } else {
                phi_f20 = temp_f22;
            }
            Matrix_StatePush();
            Matrix_InsertTranslation(phi_s2->x, phi_s2->y, phi_s2->z, 0);
            Matrix_Scale(phi_f20, temp_f22, phi_f20, 1);
            //phi_s1->words.w0 = 0xDA380002;
            //phi_s1->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
            gSPMatrix(&phi_s1[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            //TODO
            //phi_s1->unk_8 = 0xDB060020;
            //phi_s1->unk_C = (s32) (*temp_s0 + ((s32) &D_04091BE0 & 0xFFFFFF));
            //gSPSegment(&phi_s1[1], 0x08, (*temp_s0 + ((s32) D_04091BE0 & 0xFFFFFF)));
            //gSPSegment(&phi_s1[1], 0x08, (*temp_s0 + ((s32) D_04091BE0 & 0xFFFFFF)));
            gSPSegment(&phi_s1[1], 0x08, (*temp_s0 + ((s32) D_04091BE0 & 0xFFFFFF)));


            //phi_s1->unk_10 = 0xFA000000;
            //phi_s1->unk_14 = -1;
            gDPSetPrimColor(&phi_s1[2], 0, 0, 255, 255, 255, 255);

            //phi_s1->unk_18 = 0xFB000000;
            //phi_s1->unk_1C = 0x96969600;
            gDPSetEnvColor(&phi_s1[3], 150, 150, 150, 0);

            //phi_s1->unk_20 = 0xDE000000;
            //phi_s1->unk_24 = D_040301B0;
            gSPDisplayList(&phi_s1[4], D_040301B0);

            //phi_s1->unk_2C = 0x40;
            //phi_s1->unk_28 = 0xD8380002;
            gSPPopMatrix(&phi_s1[5], G_MTX_MODELVIEW);

            Matrix_StatePop();
            //phi_s1 = phi_s1 + 0x30;
            phi_s1 = &phi_s1[6];
        } else {
            temp_f0 = sqrtf(SQ(player->actor.velocity.x) + SQ(player->actor.velocity.z));
            temp_v0 = (temp_f0 * 2000.0f);
            D_801C0BA8.y = temp_f0 * 0.4f;
            D_801C0BB4.y = -0.3f;
            phi_s0 = temp_v0;
            if ((s16)temp_v0 > 0x3E80) {
                phi_s0 = 0x3E80;
            }

            //phi_s0 = CLAMP_MIN(temp_v0, 0x3E80);

            if (phi_s2 != D_801F59B0) {
                phi_v0 = phi_s0;
            } else {
                phi_v0 = -phi_s0;
            }
            temp_f20 = temp_f0 * 0.2f;
            temp_s0_2 = phi_v0 + player->actor.focus.rot.y;
            //phi_f20_2 = temp_f20;
            //if (temp_f20 > 4.0f) {
            //    phi_f20_2 = 4.0f;
            //}
            //phi_f20_2 = CLAMP_MIN(temp_f20, 4.0f);
            D_801C0BA8.x = -Math_SinS(temp_s0_2) * CLAMP_MIN(temp_f20, 4.0f);
            D_801C0BA8.z = -Math_CosS(temp_s0_2) * CLAMP_MIN(temp_f20, 4.0f);
            EffectSsDtBubble_SpawnColorProfile(globalCtx, phi_s2, &D_801C0BA8, &D_801C0BB4, 0x14, 0x14, 3, 0);
            *phi_s3 += -0x190;
        }

        phi_s2 = phi_s2 + 1;
        phi_s6 += 1;
        phi_s3 += 1;
    } while (phi_s2 != (Vec3f*)D_801F59C8);
    POLY_XLU_DISP = phi_s1;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else

extern Vec3f D_801C0BA8;
extern Vec3f D_801C0BB4;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127594.s")
void func_80127594(GlobalContext* globalCtx, Player* player);
#endif



// Gfx?
extern UNK_TYPE D_801C0BC0;

// Gfx?
extern UNK_TYPE D_801C0BD0;

extern Vec3f D_801C0BE0;
#if 0
glabel D_801C0BE4
glabel D_801C0BE8
#endif

extern Vec3f D_801C0BEC;

#if 0
glabel D_801C0BF0
glabel D_801C0BF4
#endif

extern Color_RGBA8 D_801C0BF8;

extern Color_RGBA8 D_801C0BFC;

//Vec3f D_801C0C00 = { 0.0f, 20.0f, 0.0f };
extern Vec3f D_801C0C00;

/*
Vec3f D_801C0C0C[3] = {
    { 174.0f, -1269.0f, -1.0f },
    { 401.0f, -729.0f, -701.0f },
    { 401.0f, -729.0f, 699.0f },
};
*/
extern Vec3f D_801C0C0C[3];

/*
Vec3f D_801C0C30[3] = {
    { 74.0f, -1269.0f, -1.0f },
    { 301.0f, -729.0f, -701.0f },
    { 301.0f, -729.0f, 699.0f },
};
*/
extern Vec3f D_801C0C30[3];

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ char unk_14[0x04];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} struct_80128388_arg1; // size = 0x1C

extern struct_80128388_arg1 D_801C0C54[3];

extern Color_RGB8 D_801C0CA8[];

extern Vec3f D_801C0CE8[];

extern Vec3f D_801C0D24[];

#if 0
glabel D_801C0D60
glabel D_801C0D6C
glabel D_801C0D78
glabel D_801C0D94
glabel D_801C0D98
glabel D_801C0D9C
glabel D_801C0DA0
glabel D_801C0DA8
glabel D_801C0DD8
glabel D_801C0DE4
glabel D_801C0DF0
glabel D_801C0E04
glabel D_801C0E2C
glabel D_801C0E40
glabel D_801C0E7C
glabel D_801C0E94
glabel D_801C0EA0
glabel D_801C0EAC
glabel D_801C0EB8
#endif



extern AnimatedMaterial D_0A0011F8;

extern Gfx D_0A000440[];

#if NON_MATCHING
// regalloc
void func_801278F8(GlobalContext* globalCtx, Player* player) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (player->unk_B60 != 0) {
        u8 new_var;
        s32 phi_a0;

        gSegments[0xA] = PHYSICAL_TO_VIRTUAL(player->maskObjectSegment);

        AnimatedMat_DrawOpa(globalCtx, Lib_SegmentedToVirtual(&D_0A0011F8));

        if ((player->unk_B60 < 0xB) != 0)
        {
            phi_a0 = ((player->unk_B60 / 10.0f) * 255.0f);
        } else {
            phi_a0 = 0xFF;
        }

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, phi_a0);

        new_var = phi_a0;

        gSPDisplayList(POLY_OPA_DISP++, D_0A000440);

        gSPSegment(POLY_OPA_DISP++, 0x09, &D_801C0BD0);

        gDPSetEnvColor(__gfxCtx->polyOpa.p++, 0, 0, 0, 0xFF - new_var);
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x09, &D_801C0BC0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801278F8.s")
#endif

void func_80127A60(GlobalContext* globalCtx) {
    Mtx* temp_a1 = GRAPH_ALLOC(globalCtx->state.gfxCtx, 2*sizeof(Mtx));
    Vec3s sp2C;

    OPEN_DISPS( globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0B, temp_a1);

    Matrix_StatePush();

    sp2C.x = D_801F59D0.unk_2 + 0x3E2;
    sp2C.y = D_801F59D0.unk_4 + 0xDBE;
    sp2C.z = D_801F59D0.unk_0 - 0x348A;
    Matrix_SetStateRotationAndTranslation(97.0f, -1203.0f, -240.0f, &sp2C);

    Matrix_ToMtx(temp_a1++);

    sp2C.x = D_801F59D0.unk_2 - 0x3E2;
    sp2C.y = -D_801F59D0.unk_4 -0xDBE;
    sp2C.z = D_801F59D0.unk_0 - 0x348A;
    Matrix_SetStateRotationAndTranslation(97.0f, -1203.0f, 240.0f,&sp2C);

    Matrix_ToMtx(temp_a1);

    Matrix_StatePop();

    CLOSE_DISPS( globalCtx->state.gfxCtx);
}

void func_80127B64(struct_801F58B0 arg0[], s32 count, Vec3f* arg2) {
    s32 i;

    for (i = 0; i < count; i++) {
        Math_Vec3f_Copy(&arg0->unk_00, arg2);
        Math_Vec3f_Copy(&arg0->unk_0C, &gZeroVec3f);
        // maybe fake match?
        arg0++;
        arg0[-1].unk_18 = 0;
        arg0[-1].unk_1A = 0;
    }
}

void func_80127BE8(GlobalContext* arg0, Vec3f* arg1) {
    Vec3f sp2C;
    f32 sp28;

    D_801C0BE0.y = Rand_ZeroFloat(0.07f) + -0.1f;
    D_801C0BEC.y = Rand_ZeroFloat(0.1f) + 0.04f;
    if (Rand_ZeroOne() < 0.5f) {
        sp28 = -1.0f;
    } else {
        sp28 = 1.0f;
    }

    D_801C0BE0.x = (Rand_ZeroFloat(0.2f) + 0.1f) * sp28;
    D_801C0BEC.x = 0.1f * sp28;
    if (Rand_ZeroOne() < 0.5f) {
        sp28 = -1.0f;
    } else {
        sp28 = 1.0f;
    }

    D_801C0BE0.z = (Rand_ZeroFloat(0.2f) + 0.1f) * sp28;
    D_801C0BEC.z = 0.1f * sp28;
    sp2C.x = arg1->x;
    sp2C.y = Rand_ZeroFloat(15.0f) + arg1->y;
    sp2C.z = arg1->z;
    EffectSsKiraKira_SpawnDispersed(arg0, &sp2C, &D_801C0BE0, &D_801C0BEC, &D_801C0BF8, &D_801C0BFC, -0x32, 0xB);
}


void func_80127DA4(GlobalContext* globalCtx, struct_801F58B0 arg1[], struct_80128388_arg1 arg2[], s32, Vec3f*, Vec3f*, u32*);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80127DA4.s")



void func_80128388(struct_801F58B0 arg0[], struct_80128388_arg1 arg1[], s32 arg2, Mtx** arg3) {
    struct_801F58B0* phi_s1;
    Vec3f sp58;
    Vec3s sp50;
    s32 i;

    phi_s1 = &arg0[1];
    sp58.y = 0.0f;
    sp58.z = 0.0f;
    sp50.x = 0;
    i = 1;

    if (arg2 >= 2) {
        do {
            sp58.x = arg1->unk_00 * 100.0f;
            sp50.z = arg1->unk_06 + (s16)(phi_s1->unk_1A - arg0->unk_1A);
            sp50.y = arg1->unk_04 + (s16)(phi_s1->unk_18 - arg0->unk_18);
            Matrix_JointPosition(&sp58, &sp50);
            Matrix_ToMtx(*arg3);
            (*arg3)++;
            arg0++;
            phi_s1++;
            arg1++;
            i++;
        } while (i < arg2);
    }
}

#ifdef NON_EQUIVALENT
// Not sure about equivalency
void func_801284A0(GlobalContext* globalCtx, Player* player) {
    Mtx* sp90;
    Vec3f sp84;
    Vec3f sp78;
    u32 sp6C;
    Mtx* temp_v0;
    struct_801F58B0 (*phi_s0)[3];
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp90 = GRAPH_ALLOC(globalCtx->state.gfxCtx, 6*sizeof(Mtx));

    sp6C = globalCtx->gameplayFrames;

    gSPSegment(POLY_OPA_DISP++, 0x0B, sp90);

    Matrix_MultiplyVector3fByState(&D_801C0C00, &D_801C0C54[1].unk_08);
    Math_Vec3f_Lerp(&player->bodyPartsPos[7], &player->bodyPartsPos[0], 0.2f, &D_801C0C54[1].unk_08);

    for (i = 0; i < 3; i++) {
        Matrix_MultiplyVector3fByState(&D_801C0C0C[i], &sp84);
        Matrix_MultiplyVector3fByState(&D_801C0C30[i], &sp78);

        func_80127DA4(globalCtx, D_801F58B0[i], D_801C0C54, 3, &sp84, &sp78, &sp6C);
        sp6C += 11;

        Matrix_StatePush();
        Matrix_InsertTranslation(D_801C0C0C[i].x, D_801C0C0C[i].y, D_801C0C0C[i].z, 1);
        func_80128388(D_801F58B0[i], D_801C0C54, 3, &sp90);
        Matrix_StatePop();
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_801284A0.s")
#endif

#ifdef NON_EQUIVALENT
// Looks equivalent
s32 func_80128640(GlobalContext* globalCtx, Player* player, Gfx* dlist) {
    s32 sp6C;
    //Gfx* sp50;
    s32 sp48;
    //Gfx* sp38;
    s16 sp26;
    s16 sp24;
    f32 temp_f0;
    //s16 temp_a0_2;
    //s16 temp_v0_10;
    //s16 temp_v0_11;
    s32 temp_v1;
    Color_RGB8* temp_v1_3;
    Vec3f* temp_v1_2;

    temp_v1 = &D_0400D0A8 == player->skelAnime.animation;
    if ((temp_v1 != 0) || ((player->currentMask != 0) && (&D_0400D0C8 == player->skelAnime.animation) && (temp_f0 = player->skelAnime.curFrame - 8.0f, (temp_f0 >= 0.0f)) && (temp_f0 < 4.0f)) || (player->stateFlags2 & 0x01000000)) {
        if (temp_v1 != 0) {
            sp6C = player->prevMask;
        } else {
            sp6C = player->currentMask;
        }
        if (func_80127438(globalCtx, player, sp6C) != 0) {
            OPEN_DISPS(globalCtx->state.gfxCtx);
            //sp68 = globalCtx->state.gfxCtx;

            Matrix_StatePush();
            Matrix_InsertTranslation(-323.67f, 412.15f, -969.96f, 1);
            Matrix_InsertRotation(-0x32BE, -0x50DE, -0x7717, 1);
            //temp_v0_2 = sp68->polyOpa.p;
            //sp68->polyOpa.p = temp_v0_2 + 8;
            //temp_v0_2->words.w0 = 0xDA380003;
            //sp60 = temp_v0_2;
            //sp60->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            // temp_v0_3 = sp68->polyOpa.p;
            // sp68->polyOpa.p = temp_v0_3 + 8;
            // temp_v0_3->words.w0 = 0xDE000000;
            // temp_v0_3->words.w1 = D_801C0B1C[sp6C];
            gSPDisplayList(POLY_OPA_DISP++, D_801C0B1C[sp6C]);

            Matrix_StatePop();

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
        return 1;
    }
    if (player->heldItemActionParam == 7) {

        OPEN_DISPS(globalCtx->state.gfxCtx);
        //sp58 = globalCtx->state.gfxCtx;

        Matrix_StatePush();
        Matrix_InsertTranslation(-428.26f, 267.2f, -33.82f, 1);
        Matrix_InsertRotation(-0x8000, 0, 0x4000, 1);
        Matrix_Scale(1.0f, player->unk_B08[1], 1.0f, 1);

        //temp_v0_4 = sp58->polyOpa.p;
        //sp58->polyOpa.p = temp_v0_4 + 8;
        //temp_v0_4->words.w0 = 0xDA380003;
        //sp50 = temp_v0_4;
        //sp50->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        //temp_v0_5 = sp58->polyOpa.p;
        //sp58->polyOpa.p = temp_v0_5 + 8;
        //temp_v0_5->words.w1 = (u32) &D_040032B0;
        //temp_v0_5->words.w0 = 0xDE000000;
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0032B0); 

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return 1;
    }
    if (player->leftHandType == 5) {
        sp48 = Player_ActionToBottle(player, player->heldItemActionParam);
        temp_v1_2 = &D_801C0CE8[player->transformation];

        OPEN_DISPS(globalCtx->state.gfxCtx);
        //temp_a1_2 = globalCtx->state.gfxCtx;

        Matrix_StatePush();
        Matrix_InsertTranslation(temp_v1_2->x, temp_v1_2->y, temp_v1_2->z, 1);

        //temp_v0_6 = temp_a1_2->polyXlu.p;
        //temp_a1_2->polyXlu.p = temp_v0_6 + 8;
        //temp_v0_6->words.w0 = 0xDA380003;
        //sp40 = temp_a1_2;
        //sp38 = temp_v0_6;
        //sp38->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (sp48 != 0) {
            //temp_v0_7 = temp_a1_2->polyXlu.p;
            //temp_a1_2->polyXlu.p = temp_v0_7 + 8;
            temp_v1_3 = &D_801C0CA8[sp48];
            //temp_v0_7->words.w0 = 0xFB000000;
            //temp_v0_7->words.w1 = (temp_v1_3->r << 0x18) | (temp_v1_3->g << 0x10) | (temp_v1_3->b << 8);
            gDPSetEnvColor(POLY_OPA_DISP++, temp_v1_3->r, temp_v1_3->g, temp_v1_3->b, 0);

            //temp_v0_8 = temp_a1_2->polyXlu.p;
            //temp_a1_2->polyXlu.p = temp_v0_8 + 8;
            //temp_v0_8->words.w0 = 0xDE000000;
            //temp_v0_8->words.w1 = gameplay_keep_DL_000320;
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_000320);

        }
        //temp_v0_9 = temp_a1_2->polyXlu.p;
        //temp_a1_2->polyXlu.p = temp_v0_9 + 8;
        //temp_v0_9->words.w0 = 0xDE000000;
        //temp_v0_9->words.w1 = gameplay_keep_DL_0003E0;
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0003E0);

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return 1;
    }
    if (dlist == D_0600E2A0) {
        f32 sins_1 = Math_SinS(player->unk_B86);
        f32 sins_2;

        //temp_v0_10 = player->unk_AB2.x;
        //if ((s32) temp_v0_10 < 0) {
        //    phi_v1 = -(s32) temp_v0_10;
        //} else {
        //    phi_v1 = (s32) temp_v0_10;
        //}
        //sp26 = (s16) (s32) ((((f32) (gGameInfo->data[0x394] + 0x14) * (f32) phi_v1) / 100.0f) * Math_SinS(temp_a0_2));
        sp26 = (s16) (s32) ((((f32) (gGameInfo->data[0x394] + 0x14) * ABS_ALT(player->unk_AB2.x)) / 100.0f) * sins_1);


        sins_2 = Math_SinS(player->unk_B88);
        //temp_v0_11 = player->unk_AB2.y;
        //phi_v1_2 = temp_v0_11;
        //if ((s32) temp_v0_11 < 0) {
        //    phi_v1_2 = (s16) -(s32) temp_v0_11;
        //}
        //sp24 = (s16) (s32) ((((f32) (gGameInfo->data[0x395] + 0xF) * (f32) phi_v1_2) / 100.0f) * Math_SinS(player->unk_B88));
        sp24 = (s16) (s32) ((((f32) (gGameInfo->data[0x395] + 0xF) * ABS_ALT(player->unk_AB2.y)) / 100.0f) * sins_2);

        OPEN_DISPS(globalCtx->state.gfxCtx);
        //sp20 = globalCtx->state.gfxCtx;

        Matrix_StatePush();
        Matrix_InsertXRotation_s(sp26, 1);
        Matrix_RotateY(sp24, 1);
        //temp_v0_12 = sp20->polyOpa.p;
        //sp20->polyOpa.p = temp_v0_12 + 8;
        //temp_v0_12->words.w0 = 0xDA380003;
        //sp18 = temp_v0_12;
        //sp18->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        //temp_v0_13 = sp20->polyOpa.p;
        //sp20->polyOpa.p = temp_v0_13 + 8;
        //temp_v0_13->words.w1 = D_0600E088;
        //temp_v0_13->words.w0 = 0xDE000000;
        gSPDisplayList(POLY_OPA_DISP++, D_0600E088);

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        return 1;
        //if (((!__gfxCtx) && (!__gfxCtx)) && (!__gfxCtx)) {}
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128640.s")
#endif

void func_80128B74(GlobalContext* globalCtx, Player* player, s32 limbIndex) {
    Vec3f* footPos = &D_801C0D24[player->transformation];

    func_800B4A98(&player->actor, limbIndex, 9, footPos, 6, footPos);
}





#if 0

#if 0
struct _mips2c_stack_func_80128BD0 {
    /* 0x000 */ char pad_0[0x30];
    /* 0x030 */ Vec3f* sp30;                        /* inferred */
    /* 0x034 */ char pad_34[0x1C];                  /* maybe part of sp30[8]? */
    /* 0x050 */ ? sp50;                             /* inferred */
    /* 0x050 */ char pad_50[0xC];
    /* 0x05C */ ? sp5C;                             /* inferred */
    /* 0x05C */ char pad_5C[0xC];
    /* 0x068 */ ? sp68;                             /* inferred */
    /* 0x068 */ char pad_68[0x40];
    /* 0x0A8 */ Actor* spA8;                        /* inferred */
    /* 0x0AC */ char pad_AC[0x10];                  /* maybe part of spA8[5]? */
    /* 0x0BC */ GraphicsContext* spBC;              /* inferred */
    /* 0x0C0 */ char pad_C0[8];                     /* maybe part of spBC[3]? */
    /* 0x0C8 */ Gfx* spC8;                          /* inferred */
    /* 0x0CC */ char pad_CC[8];                     /* maybe part of spC8[3]? */
    /* 0x0D4 */ f32 spD4;                           /* inferred */
    /* 0x0D8 */ char pad_D8[0xC];                   /* maybe part of spD4[4]? */
    /* 0x0E4 */ GraphicsContext* spE4;              /* inferred */
    /* 0x0E8 */ char pad_E8[8];                     /* maybe part of spE4[3]? */
    /* 0x0F0 */ f32 spF0;                           /* inferred */
    /* 0x0F4 */ f32 spF4;                           /* inferred */
    /* 0x0F8 */ f32 spF8;                           /* inferred */
    /* 0x0FC */ ? spFC;                             /* inferred */
    /* 0x0FC */ char pad_FC[0x30];
    /* 0x12C */ ? sp12C;                            /* inferred */
    /* 0x12C */ char pad_12C[8];
    /* 0x134 */ Gfx* sp134;                         /* inferred */
    /* 0x138 */ char pad_138[0x18];                 /* maybe part of sp134[7]? */
    /* 0x150 */ GraphicsContext* sp150;             /* inferred */
    /* 0x154 */ s32 sp154;                          /* inferred */
    /* 0x158 */ char pad_158[4];
    /* 0x15C */ Gfx* sp15C;                         /* inferred */
    /* 0x160 */ char pad_160[8];                    /* maybe part of sp15C[3]? */
    /* 0x168 */ f32* sp168;                         /* inferred */
    /* 0x16C */ char pad_16C[4];
    /* 0x170 */ GraphicsContext* sp170;             /* inferred */
    /* 0x174 */ char pad_174[4];
    /* 0x178 */ ? sp178;                            /* inferred */
    /* 0x178 */ char pad_178[0x3C];
    /* 0x1B4 */ ? sp1B4;                            /* inferred */
    /* 0x1B4 */ char pad_1B4[8];
    /* 0x1BC */ ? sp1BC;                            /* inferred */
    /* 0x1BC */ char pad_1BC[0x50];
    /* 0x20C */ ? sp20C;                            /* inferred */
    /* 0x20C */ char pad_20C[0x10];
    /* 0x21C */ GraphicsContext* sp21C;             /* inferred */
    /* 0x220 */ char pad_220[4];
    /* 0x224 */ Actor* sp224;                       /* inferred */
    /* 0x228 */ char pad_228[8];                    /* maybe part of sp224[3]? */
    /* 0x230 */ ? sp230;                            /* inferred */
    /* 0x230 */ char pad_230[0x48];
};                                                  /* size = 0x278 */
#endif
s32 func_800B7118(Player*);                         /* extern */
s32 func_800B7128(Player*);                         /* extern */
//? func_80124CC4(GraphicsContext**, Player*, ?);     /* extern */
//? func_80126BD0(GraphicsContext**, Player*, ?);     /* extern */
//s32 func_801271B0(GraphicsContext**, Player*, ?);   /* extern */
//? func_80127594(GraphicsContext**, Player*);        /* extern */
//? func_80127A60(GraphicsContext**, Player*);        /* extern */
//? func_801284A0(GraphicsContext**, Player*);        /* extern */
//extern ? D_0400D0D0;
//extern ? D_0400E1F8;
extern UNK_TYPE D_0400E218;
//extern ? D_0400E230;
//extern ? D_0400E298;
//extern ? D_0400E2C8;
//extern ? D_0400E2F0;
//extern ? D_04054C90;
extern AnimatedMaterial D_04054F18;
extern Gfx D_06007390[];
extern Gfx D_0600A348[];
extern Gfx D_0600FC18[];
extern Gfx* D_801C00AC[][2];
extern u16 D_801C0340;
extern u16 D_801C0368;
extern u16 D_801C0410;
extern u16 D_801C0428;
extern u16 D_801C0510;
extern u8 D_801C0778[];
extern u8 D_801C07AC[];
extern Vec3f D_801C0A24;
extern Vec3f D_801C0A48;
extern Vec3f D_801C0A6C;
extern Vec3f D_801C0A90;
extern Gfx* D_801C0B20[];
extern Vec3f D_801C0D60;
extern Vec3f D_801C0D6C;
extern f32 D_801C0D78[];
extern u32 D_801C0D94;
extern f32 D_801C0D9C;
extern f32 D_801C0DA0;
extern Vec3f D_801C0DA8;
extern Vec3f D_801C0DD8;
extern Vec3f D_801C0DE4;
extern Gfx* D_801C0DF0[];
extern Vec2f D_801C0E04;
extern Gfx* D_801C0E2C[];
extern Vec3f D_801C0E40[];
extern Vec3f D_801C0E7C;
extern Vec3f D_801C0E94;
extern Vec3f D_801C0EA0;
extern Vec3f D_801C0EAC;
extern Vec3s D_801C0EB8;
extern Vec3f* D_801F59DC;



void func_80128BD0(GlobalContext* globalCtx, s32 arg1, Gfx** arg2, Gfx** arg3, Player* player, Player* arg5) {
    MtxF sp230;
    Actor* sp224;
    GraphicsContext* sp21C;
    Vec3f sp20C;
    MtxF sp1BC;
    Vec3f sp1B4; // ?
    Vec3f sp178[5];
    GraphicsContext* sp170;
    f32* sp168;
    Gfx* sp15C;
    s32 sp154;
    GraphicsContext* sp150;
    Gfx* sp134;
    Vec3f sp12C; // ?
    Vec3f spFC;
    Vec3f spF0;
    GraphicsContext* spE4;
    f32 spD4;
    Gfx* spC8;
    GraphicsContext* spBC;
    MtxF sp68;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f* sp30;
    Actor* temp_s0;
    Gfx* temp_v0_10;
    Gfx* temp_v0_12;
    Gfx* temp_v0_14;
    Gfx* temp_v0_16;
    Gfx* temp_v0_17;
    Gfx* temp_v0_19;
    Gfx* temp_v0_20;
    Gfx* temp_v0_21;
    Gfx* temp_v0_22;
    Gfx* temp_v0_23;
    Gfx* temp_v0_24;
    Gfx* temp_v0_25;
    Gfx* temp_v0_3;
    Gfx* temp_v0_4;
    Gfx* temp_v0_7;
    Gfx* temp_v0_8;
    Gfx* temp_v0_9;
    Gfx* temp_v1_6;
    GraphicsContext* temp_a0_2;
    GraphicsContext* temp_s0_7;
    MtxF* temp_s0_2;
    Vec3f* temp_s0_4;
    Vec3f* temp_s0_5;
    Vec3f* temp_s0_8;
    Vec3s* temp_s0_11;
    Vec3s* temp_s1;
    f32 temp_f0;
    f32 temp_f12;
    f32* temp_a1;
    f32* temp_a1_2;
    f32* temp_at;
    f32* temp_v0_18;
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s8 temp_v0_26;
    u8 temp_v0_11;
    u8 temp_v0_27;
    u8 temp_v0_28;
    u8 temp_v1;
    Vec3f* temp_s0_10;
    Vec2f* temp_s0_6;
    Vec3f* temp_s0_9;
    void* temp_v0_13;
    void* temp_v0_15;
    Vec3f* phi_a0;
    f32* phi_v0;
    Vec3f* phi_s0;
    Vec3f* phi_s0_2;
    f32* phi_a1;
    Vec3f* phi_s0_3;
    Vec3f* phi_s0_4;
    Gfx** phi_a1_2;
    Vec3f* phi_s0_5;

    if (*arg3 != 0) {
        Matrix_GetStateTranslation(D_801F59DC);
    }
    if (arg1 == 0x10) {
        Math_Vec3f_Copy(&arg5->leftHandWorld.pos, D_801F59DC);
        if ((*arg2 != 0) && (func_801271B0(globalCtx, arg5, 0) == 0) && (func_80128640(globalCtx, arg5, *arg2) == 0) && (&D_0400E218 == arg5->skelAnime.animation)) {
            func_80127488(globalCtx, arg5, D_801C0778[(s32) arg5->skelAnime.curFrame]);
        }
        if (arg5->actor.scale.y >= 0.0f) {
            if ((func_801240C8(arg5) == 0) && ((arg5->leftHandActor != 0))) {
                if (((arg5->stateFlags3 & 0x40) != 0) && (temp_v1 = arg5->transformation, (temp_v1 != 3))) {
                    phi_a0 = &D_801C0D60;
                    if (temp_v1 == 4) {
                        phi_a0 = &D_801C0D6C;
                    }
                    Matrix_MultiplyVector3fByState(phi_a0, &arg5->leftHandActor->world.pos);
                    Matrix_InsertRotation(0x69E8, -0x5708, 0x458E, 1);
                    Matrix_CopyCurrentState((MtxF* ) &sp230);
                    temp_s1 = &arg5->leftHandActor->world.rot;
                    func_8018219C((MtxF* ) &sp230, temp_s1, 0);
                    arg5->leftHandActor->shape.rot = *temp_s1;
                } else if ((arg5->stateFlags1 & 0x800) != 0) {
                    temp_v0 = arg5->actor.shape.rot.y + arg5->leftHandWorld.rot.y;
                    arg5->leftHandActor->shape.rot.y = temp_v0;
                    arg5->leftHandActor->world.rot.y = temp_v0;
                }
            } else {
                if ((arg5->transformation == 0) || ((arg5->transformation != 2) && ((arg5->heldItemActionParam == 7) || ((arg5->swordState != 0) && ((arg5->swordAnimation != 0x19)) && (arg5->swordAnimation != 0x1A))))) {
                    if (arg5->heldItemActionParam == 7) {
                        D_801C0994->x = arg5->unk_B08[1] * 5000.0f;
                    } else {
                        D_801C0994->x = D_801C0D78[func_80124190(arg5)];
                    }
                    func_80126B8C(globalCtx, arg5);
                }
                temp_s0_2 = &arg5->mf_CC4;
                Matrix_CopyCurrentState(temp_s0_2);
                func_8018219C(temp_s0_2, &arg5->leftHandWorld.rot, 0);
            }
        }
    } else if (arg1 == 0x13) {
        sp224 = arg5->leftHandActor;
        if (*arg2 != 0) {
            if (arg5->rightHandType == 9) {
                OPEN_DISPS(globalCtx->state.gfxCtx);
                //sp21C = globalCtx->state.gfxCtx;

                Matrix_StatePush();
                Matrix_InsertTranslation(D_801C0D9C, D_801C0D9C, D_801C0DA0, 1);
                if (((arg5->stateFlags3 & 0x40) != 0) && ((s32) arg5->unk_B28 >= 0) && ((s32) arg5->unk_ACC < 0xB)) {
                    Matrix_GetStateTranslation((Vec3f* ) &sp20C);
                    temp_f0 = Math_Vec3f_DistXYZ(D_801F59DC, (Vec3f* ) &sp20C);
                    arg5->unk_B08[0] = temp_f0 - 3.0f;
                    if (temp_f0 < 3.0f) {
                        arg5->unk_B08[0] = 0.0f;
                    } else {
                        arg5->unk_B08[0] *= 1.6f;
                        if (arg5->unk_B08[0] > 1.0f) {
                            arg5->unk_B08[0] = 1.0f;
                        }
                    }
                    arg5->unk_B08[1] = -0.5f;
                }
                Matrix_Scale(1.0f, arg5->unk_B08[0], 1.0f, 1);
                //temp_v0_3 = sp21C->polyXlu.p;
                //sp21C->polyXlu.p = temp_v0_3 + 8;
                //temp_v0_3->words.w0 = 0xDA380003;
                //temp_v0_3->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);


                //temp_v0_4 = sp21C->polyXlu.p;
                //sp21C->polyXlu.p = temp_v0_4 + 8;
                //temp_v0_4->words.w0 = 0xDE000000;
                //temp_v0_4->words.w1 = D_801C0D94;
                gSPDisplayList(POLY_XLU_DISP++, D_801C0D94);

                Matrix_StatePop();

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            } else if (&gameplay_keep_Linkanim_00E230 == arg5->skelAnime.animation) {
                func_80127488(globalCtx, arg5, D_801C07AC[(s32)arg5->skelAnime.curFrame]);
            } else {
                func_801271B0(globalCtx, arg5, 1);
            }
        }

        if (arg5->actor.scale.y >= 0.0f) {
            if (arg5->rightHandType == 0xFF) {
                Matrix_CopyCurrentState(&arg5->shieldMf);
            } else if (arg5->rightHandType == 8) {
                Matrix_CopyCurrentState(&arg5->shieldMf);
                func_801265C8((GlobalContext* ) globalCtx, arg5, &arg5->shieldQuad, &D_801C0DA8);
            } else if (arg5->rightHandType == 0xB) {
                Matrix_MultiplyVector3fByState(&D_801C0DD8, &arg5->rightHandWorld.pos);
                if (sp224 != 0) {
                    Matrix_MultiplyVector3fByState(&D_801C0DE4, &sp224->world.pos);
                    Matrix_InsertRotation(0, -0x4000, -0x4000, 1);
                    Matrix_CopyCurrentState((MtxF* ) &sp1BC);
                    func_8018219C((MtxF* ) &sp1BC, &sp224->world.rot, 0);
                    sp224->shape.rot = sp224->world.rot;
                    if (func_800B7128(arg5) != 0) {
                        Matrix_InsertTranslation(500.0f, 300.0f, 0.0f, 1);
                        func_80124CC4(globalCtx, arg5, 0x47979000);
                    }
                }
            } else if ((arg5->swordState != 0) && (arg5->swordAnimation == 0x19)) {
                func_80126B8C((GlobalContext* ) globalCtx, arg5);
            }
            if ((arg5->unk_B2A != 0) || ((func_800B7118(arg5) == 0) && (sp224 != 0))) {
                if (((arg5->stateFlags1 & 0x400) == 0) && (arg5->unk_B2A != 0) && (arg5->unk_A87 != 0)) {
                    Math_Vec3f_Copy(&D_801F59E8, &arg5->leftHandWorld.pos);
                } else {
                    temp_at = &D_801F59E8.y;
                    *temp_at = (arg5->bodyPartsPos[0xF].x + arg5->leftHandWorld.pos.x) * 0.5f;
                    *temp_at = (arg5->bodyPartsPos[0xF].y + arg5->leftHandWorld.pos.y) * 0.5f;
                    D_801F59E8.z = (arg5->bodyPartsPos[0xF].z + arg5->leftHandWorld.pos.z) * 0.5f;
                }
                if (arg5->unk_B2A == 0) {
                    Math_Vec3f_Copy(&sp224->world.pos, &D_801F59E8);
                }
            }
        }
    } else if (arg1 == 0xF) {
        func_80126BD0(globalCtx, arg5, 0);
    } else if (arg1 == 0x12) {
        func_80126BD0(globalCtx, arg5, 1);
    } else if (arg1 == 0x15) {
        if ((arg5->transformation == 1) && (( ( &gameplay_keep_Linkanim_00E1F8 == arg5->skelAnime.animation)) || (&D_0400E200 == arg5->skelAnime.animation != 0) || (&D_0400E1F0 == arg5->skelAnime.animation))) {
            Gfx** aux_a1;

            OPEN_DISPS(globalCtx->state.gfxCtx);
            //sp170 = globalCtx->state.gfxCtx;

            if (&D_0400E200 == arg5->skelAnime.animation) {

                phi_v0 = &arg5->unk_B08[2];
                phi_s0 = (Vec3f* ) &sp178;
                do {
                    sp168 = phi_v0;
                    func_80124618(&D_801C0510, *phi_v0, phi_s0);
                    phi_s0++;
                    phi_v0 += 4;
                } while (phi_s0 != &sp1B4);

            } else {
                if ( &gameplay_keep_Linkanim_00E1F8 == arg5->skelAnime.animation) {
                    func_8012536C();
                    func_80124618(&D_801C0428, arg5->skelAnime.curFrame, &arg5->unk_AF0[1]);
                }
                sp30 = &arg5->unk_AF0[1];
                phi_s0_2 = (Vec3f* ) &sp178;
                do {
                    Math_Vec3f_Copy(phi_s0_2, sp30);
                    phi_s0_2++;
                } while (phi_s0_2 != &sp1B4);
            }
            Matrix_StatePush();
            Matrix_Scale(arg5->unk_AF0[1].x, arg5->unk_AF0[1].y, arg5->unk_AF0[1].z, 1);

            //temp_v0_7 = sp170->polyOpa.p;
            //sp170->polyOpa.p = temp_v0_7 + 8;
            //temp_v0_7->words.w0 = 0xDA380003;
            //temp_v0_7->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            //temp_v0_8 = sp170->polyOpa.p;
            //sp170->polyOpa.p = temp_v0_8 + 8;
            //temp_v0_8->words.w0 = 0xDE000000;
            //temp_v0_8->words.w1 = (u32) D_0600FC18;
            gSPDisplayList(POLY_XLU_DISP++, D_0600FC18);

            Matrix_StatePop();
            aux_a1 = &D_801C0DF0;
            phi_s0_3 = &sp178;
            do {
                sp30 = aux_a1;
                Matrix_StatePush();
                Matrix_Scale(phi_s0_3->x, phi_s0_3->y, phi_s0_3->z, 1);
                //temp_v0_9 = sp170->polyOpa.p;
                //sp170->polyOpa.p = temp_v0_9 + 8;
                //temp_v0_9->words.w0 = 0xDA380003;
                //sp15C->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                //sp30 = phi_a1;
                //sp15C = temp_v0_9;
                //temp_v0_10 = sp170->polyOpa.p;
                //sp170->polyOpa.p = temp_v0_10 + 8;
                //temp_v0_10->words.w0 = 0xDE000000;
                ////temp_v0_10->words.w1 = (bitwise u32) phi_a1->x;
                //temp_v0_10->words.w1 = *phi_a1;
                gSPDisplayList(POLY_XLU_DISP++, *aux_a1);

                sp30 = aux_a1;
                Matrix_StatePop();
                aux_a1 = aux_a1+1;
                phi_s0_3 += 0xC;
            } while (aux_a1 != (Gfx**)&D_801C0E04);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    } else if (arg1 == 0xB) {
        if ((*arg2 != 0) && ((arg5->currentMask != 0)) && ((((arg5->transformation == 4)) && ((&D_0400D0C8 != arg5->skelAnime.animation) || (arg5->skelAnime.curFrame >= 12.0f))) || ((arg5->transformation != 4) && ((s32) arg5->currentMask >= 0x15) && (arg5->currentMask != (arg5->transformation + 0x15)) && (arg5->skelAnime.curFrame >= 10.0f)))) {
            if (func_80127438(globalCtx, arg5, (s32) arg5->currentMask) != 0) {
                OPEN_DISPS(globalCtx->state.gfxCtx);

                temp_v0_11 = arg5->currentMask;
                sp154 = temp_v0_11 - 1;
                //sp150 = globalCtx->state.gfxCtx;
                if (temp_v0_11 == 0xA) {
                    func_8012754C((GlobalContext* ) globalCtx, arg5);
                } else if (temp_v0_11 == 8) {
                    func_80127594(globalCtx, arg5);
                } else if (temp_v0_11 == 0x12) {
                    func_801278F8((GlobalContext* ) globalCtx, arg5);
                } else if (temp_v0_11 == 4) {
                    func_80127A60(globalCtx, arg5);
                } else if (temp_v0_11 == 0xB) {
                    func_801284A0(globalCtx, arg5);
                } else if (((s32) temp_v0_11 >= 0x15) && (((temp_s0_6 = (arg5->transformation * 8) + &D_801C0E04, Matrix_StatePush(), Matrix_InsertTranslation(temp_s0_6->x, temp_s0_6->y, 0.0f, 1), Matrix_Scale(1.0f, 1.0f - arg5->unk_B08[5], 1.0f - arg5->unk_B08[4], 1), temp_v0_12 = sp150->polyOpa.p, sp150->polyOpa.p = temp_v0_12 + 8, temp_v0_12->words.w0 = 0xDA380003, temp_v0_12->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx), Matrix_StatePop(), temp_v0_13 = arg5->skelAnime.animation, (&D_0400D0C8 == temp_v0_13)) && (arg5->skelAnime.curFrame >= 51.0f)) || (&gameplay_keep_Linkanim_00D0D0 == temp_v0_13))) {
                    sp154 += 4;
                }
                //temp_v0_14 = sp150->polyOpa.p;
                //sp150->polyOpa.p = temp_v0_14 + 8;
                //temp_v0_14->words.w0 = 0xDE000000;
                //temp_v0_14->words.w1 = *(D_801C0B20 + (sp154 * 4));
                gSPDisplayList(POLY_XLU_DISP++, D_801C0B20[sp154]);

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }
        } else if (arg5->transformation == 3) {
            temp_v0_15 = arg5->skelAnime.animation;
            if (&gameplay_keep_Linkanim_00E2C8 == arg5->skelAnime.animation) {
                OPEN_DISPS(globalCtx->state.gfxCtx);
                //temp_s0_7 = globalCtx->state.gfxCtx;

                func_80124618(&D_801C0410, arg5->skelAnime.curFrame, arg5->unk_AF0);
                Matrix_StatePush();
                Matrix_Scale(arg5->unk_AF0[0].x, arg5->unk_AF0[0].y, arg5->unk_AF0[0].z, 1);
                //temp_v0_16 = temp_s0_7->polyOpa.p;
                //temp_s0_7->polyOpa.p = temp_v0_16 + 8;
                //temp_v0_16->words.w0 = 0xDA380003;
                //sp134->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
                //gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                //sp134 = temp_v0_16;
                //temp_v0_17 = temp_s0_7->polyOpa.p;
                //temp_s0_7->polyOpa.p = temp_v0_17 + 8;
                //temp_v0_17->words.w1 = (u32) &D_0600A348;
                //temp_v0_17->words.w0 = 0xDE000000;
                gSPDisplayList(POLY_XLU_DISP++, D_0600A348);
                Matrix_StatePop();

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            } else {
                if (&gameplay_keep_Linkanim_00E2B0 ==  arg5->skelAnime.animation || (&D_0400E2A8 == arg5->skelAnime.animation) || (&gameplay_keep_Linkanim_00D300 == arg5->skelAnime.animation)) {
                    s32 i;

                    OPEN_DISPS(globalCtx->state.gfxCtx);
                    //spE4 = globalCtx->state.gfxCtx;

                    if (&gameplay_keep_Linkanim_00E2B0 ==  arg5->skelAnime.animation) {
                        func_80124618(&D_801C0340, arg5->skelAnime.curFrame, (Vec3f* ) &spD4);
                        arg5->unk_AF0[0].x = spD4;
                        func_80124618(&D_801C0368, arg5->skelAnime.curFrame, (Vec3f* ) &spF0);
                        phi_s0_4 = (Vec3f* ) &spFC;
                        do {
                            Math_Vec3f_Copy(phi_s0_4, (Vec3f* ) &spF0);
                            phi_s0_4++;
                        } while ((u32) phi_s0_4 < (u32) &sp12C);
                        arg5->unk_AF0[0].y = spF0.x;
                        arg5->unk_AF0[0].z = spF0.x;
                        arg5->unk_AF0[1].x = spF0.x;
                        arg5->unk_AF0[1].y = spF0.x;
                        arg5->unk_AF0[1].z = spF0.x;
                    } else {
                        spF0.x = arg5->unk_AF0[0].y;
                        spF0.y = arg5->unk_AF0[0].y;
                        temp_s0_9 = (1 * 0xC) + &spF0;
                        spF0.z = arg5->unk_AF0[0].y;
                        temp_v0_18 = &arg5->unk_AF0[1].z;
                        temp_s0_9[0].x = (f32) arg5->unk_AF0[0].z;
                        temp_s0_9[0].y = (f32) arg5->unk_AF0[0].z;
                        temp_s0_9[0].z = (f32) arg5->unk_AF0[0].z;
                        temp_s0_9[1].x = (f32) arg5->unk_AF0[1].x;
                        temp_s0_9[1].y = (f32) arg5->unk_AF0[1].x;
                        temp_s0_9[1].z = (f32) arg5->unk_AF0[1].x;
                        temp_s0_9[2].x = (f32) arg5->unk_AF0[1].y;
                        temp_s0_9[2].y = (f32) arg5->unk_AF0[1].y;
                        temp_s0_9[2].z = (f32) arg5->unk_AF0[1].y;
                        temp_s0_9[3].x = (f32) *temp_v0_18;
                        temp_s0_9[3].y = (f32) *temp_v0_18;
                        temp_s0_9[3].z = (f32) *temp_v0_18;
                    }
                    Matrix_StatePush();
                    temp_f12 = arg5->unk_AF0[0].x;
                    Matrix_Scale(temp_f12, temp_f12, temp_f12, 1);
                    //temp_v0_19 = spE4->polyOpa.p;
                    //spE4->polyOpa.p = temp_v0_19 + 8;
                    //temp_v0_19->words.w0 = 0xDA380003;
                    //temp_v0_19->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    //temp_v0_20 = spE4->polyOpa.p;
                    //spE4->polyOpa.p = temp_v0_20 + 8;
                    //temp_v0_20->words.w0 = 0xDE000000;
                    //temp_v0_20->words.w1 = (u32) &D_06007390;
                    gSPDisplayList(POLY_XLU_DISP++, D_06007390);
                    Matrix_StatePop();
                    phi_a1_2 = D_801C0E2C;
                    phi_s0_5 = &spF0;
                    
                    for (i = 0; i < 5; i++) {
                        //sp30 = phi_a1_2;
                        Matrix_StatePush();
                        Matrix_Scale(phi_s0_5->x, phi_s0_5->y, phi_s0_5->z, 1);
                        //temp_v0_21 = spE4->polyOpa.p;
                        //spE4->polyOpa.p = temp_v0_21 + 8;
                        //temp_v0_21->words.w0 = 0xDA380003;
                        //spC8->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        //sp30 = phi_a1_2;
                        //spC8 = temp_v0_21;
                        //temp_v0_22 = spE4->polyOpa.p;
                        //spE4->polyOpa.p = temp_v0_22 + 8;
                        //temp_v0_22->words.w0 = 0xDE000000;
                        ////temp_v0_22->words.w1 = (bitwise u32) phi_a1_2->x;
                        //temp_v0_22->words.w1 = phi_a1_2->x;
                        gSPDisplayList(POLY_XLU_DISP++, *phi_a1_2);
                        //sp30 = phi_a1_2;
                        Matrix_StatePop();
                        phi_a1_2++;
                        phi_s0_5++;
                    }

                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                }
            }
        }
        if (((arg5->stateFlags1 & 0x102) != 0) && (arg5->unk_AE8 != 0)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);
            temp_s0_10 = &D_801C0E40[arg5->transformation];
            //spBC = globalCtx->state.gfxCtx;
            Matrix_StatePush();
            AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(&D_04054F18));
            Matrix_InsertTranslation(temp_s0_10->x, temp_s0_10->y, 0.0f, 1);
            if (arg5->transformation == 2) {
                Matrix_Scale(0.7f, 0.7f, 0.7f, 1);
            }
            //temp_v0_23 = spBC->polyXlu.p;
            //spBC->polyXlu.p = temp_v0_23 + 8;
            //temp_v0_23->words.w0 = 0xDA380003;
            //temp_v0_23->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            //temp_v0_24 = spBC->polyXlu.p;
            //spBC->polyXlu.p = temp_v0_24 + 8;
            //temp_v0_24->words.w0 = 0xFB000000;
            ////temp_v0_24->words.w1 = arg5->unk_AE9 | 0xFF00;
            //temp_v0_24->words.w1 = (u8)arg5->unk_AE8 | 0xFF00;
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 255, (u8)arg5->unk_AE8);
            
            //temp_v0_25 = spBC->polyXlu.p;
            //spBC->polyXlu.p = temp_v0_25 + 8;
            //temp_v0_25->words.w1 = gameplay_keep_DL_054C90;
            //temp_v0_25->words.w0 = 0xDE000000;
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_054C90);
            Matrix_StatePop();

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
        if (arg5->actor.scale.y >= 0.0f) {
            if (arg5->transformation != 3) {
                Matrix_MultiplyVector3fByState(&D_801C0E7C, &arg5->actor.focus.pos);
            } else {
                Matrix_MultiplyVector3fByState(&D_801C0E7C, &arg5->actor.focus.pos);
                Matrix_MultiplyVector3fByState(&D_801C0E94, D_801F59DC);
                if (((&gameplay_keep_Linkanim_00E298 == arg5->skelAnime.animation) || (&gameplay_keep_Linkanim_00E2F0 == arg5->unk_284.animation) || (((arg5->stateFlags3 & 0x40) != 0) && ((arg5->leftHandActor != 0)))) && (arg5->leftHandActor != 0)) {
                    Matrix_StatePush();
                    Matrix_MultiplyVector3fByState(&D_801C0EA0, &arg5->leftHandActor->world.pos);
                    Matrix_InsertRotation(0, 0x4000, 0, 1);
                    Matrix_CopyCurrentState((MtxF* ) &sp68);
                    temp_s0_11 = &arg5->leftHandActor->world.rot;
                    func_8018219C((MtxF* ) &sp68, temp_s0_11, 0);
                    //arg5->leftHandActor->unk_BC = (unaligned s32) temp_s0_11->unk_0;
                    //arg5->leftHandActor->unk_BC = temp_s0_11->unk_0;
                    arg5->leftHandActor->shape.rot = *temp_s0_11;
                    Matrix_StatePop();
                }
            }
        }
    } else if ((arg1 == 0xC) && (arg5->stateFlags3 & 0x100000)) {
        Matrix_GetStateTranslationAndScaledX(3000.0f, (Vec3f* ) &sp5C);
        Matrix_GetStateTranslationAndScaledX(2300.0f, (Vec3f* ) &sp50);
        if (func_80126440((GlobalContext* ) globalCtx, NULL, arg5->swordInfo, (Vec3f* ) &sp5C, (Vec3f* ) &sp50) != 0) {
            EffectBlure_AddVertex(Effect_GetByIndex(arg5->blureEffectIndex[0]), &arg5->swordInfo[0].tip, &arg5->swordInfo[0].base);
        }
    } else if (arg1 == 5) {
        if ((arg5->swordState != 0) && ((temp_v0_26 = arg5->swordAnimation, (temp_v0_26 == 0x1D)) || (temp_v0_26 == 0x12) || (temp_v0_26 == 0x15))) {
            func_8012669C((GlobalContext* ) globalCtx, arg5, &D_801C0A48, &D_801C0A24);
        }
    } else if (arg1 == 2) {
        if ((arg5->swordState != 0) && (arg5->swordAnimation == 0x1A)) {
            Math_Vec3f_Copy(&arg5->unk_AF0[1], &arg5->swordInfo[0].base);
            func_8012669C((GlobalContext* ) globalCtx, arg5, &D_801C0A90, &D_801C0A6C);
        }
    } else if (arg1 == 0x14) {
        if ((*arg2 != 0) && (arg5->transformation == 4) && (arg5->currentShield != 0) && (((arg5->sheathType == 0xE)) || (arg5->sheathType == 0xF))) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            //temp_a0_2 = globalCtx->state.gfxCtx;
            //temp_v1_6 = temp_a0_2->polyOpa.p;
            //temp_a0_2->polyOpa.p = temp_v1_6 + 8;
            //temp_v1_6->words.w0 = 0xDE000000;
            //temp_v1_6->words.w1 = *(D_801C00AC + ((arg5->currentShield - 1) * 8));
            gSPDisplayList(POLY_XLU_DISP++, D_801C00AC[arg5->currentShield - 1][0]);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
        if (arg5->actor.scale.y >= 0.0f) {
            if (( arg5->rightHandType != 8) && ( arg5->rightHandType != 0xFF)) {
                Matrix_JointPosition(&D_801C0EAC, &D_801C0EB8);
                Matrix_CopyCurrentState(&arg5->shieldMf);
            }
        }
    } else if (arg5->actor.scale.y >= 0.0f) {
        func_80128B74(globalCtx, arg5, arg1);
    }
    func_8012536C();
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_player_lib/func_80128BD0.s")
#endif
