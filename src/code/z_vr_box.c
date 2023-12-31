#include "global.h"
#include "buffers.h"

u32 D_801C5E30[] = { 0, 0x2000, 0x4000, 0x6000, 0x8000, 0xC000 };

u16 D_801C5E48[] = {
    0, 2, 10, 12, 2, 4, 12, 14, 10, 12, 20, 22, 12, 14, 22, 24, 1, 3, 5, 6, 7, 8, 9, 11, 13, 15, 16, 17, 18, 19, 21, 23,
};
s32 D_801C5E88[] = { 0, 62 << 5, 124 << 5, 186 << 5, 248 << 5 };

s32 D_801C5E9C[] = { 0, 62 << 5, 124 << 5, 186 << 5, 248 << 5 };

s32 D_801C5EB0[] = { 0, 62 << 5, 124 << 5, 62 << 5, 0 };

s16 D_801C5EC4[] = {
    0,  16, 19, 18, 16, 1,  20, 19, 1,  17, 21, 20, 17, 5,  22, 21, 18, 19, 23, 2,  19, 20,
    3,  23, 20, 21, 24, 3,  21, 22, 7,  24, 2,  23, 26, 25, 23, 3,  27, 26, 3,  24, 28, 27,
    24, 7,  29, 28, 25, 26, 30, 10, 26, 27, 11, 30, 27, 28, 31, 11, 28, 29, 15, 31,
};

s32 func_80142440(SkyboxContext* skyboxCtx, Vtx* roomVtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8) {
    s32 i;
    s32 j;
    s32 k;
    s16 phi_a0_4;
    s16 phi_t1;
    s32 temp1;
    u16 index;
    s16 phi_a2_4;
    s16 phi_ra;
    s16 phi_t2_4;
    s32 temp2;
    s32 roomVtxPosX[5 * 5];
    s32 roomVtxPosY[5 * 5];
    s32 roomVtxPosZ[5 * 5];
    s32 roomVtxTexU[5 * 5];
    s32 roomVtxTexV[5 * 5];
    s32 pad;

    switch (arg8) {
        case 0:
        case 1:
            temp1 = arg4;

            for (i = 0, k = 0; k < 25; i++) {
                temp2 = arg3;
                for (j = 0; j < 5; j++, k++) {
                    roomVtxPosZ[k] = arg5;
                    roomVtxPosX[k] = temp2;
                    roomVtxPosY[k] = temp1;
                    roomVtxTexU[k] = D_801C5E88[j];
                    roomVtxTexV[k] = D_801C5EB0[i];
                    temp2 += arg6;
                }
                temp1 += arg7;
            }
            break;

        case 2:
        case 3:
            temp1 = arg4;

            for (i = 0, k = 0; k < 25; i++) {
                temp2 = arg5;
                for (j = 0; j < 5; j++, k++) {
                    roomVtxPosX[k] = arg3;
                    roomVtxPosY[k] = temp1;
                    roomVtxPosZ[k] = temp2;
                    roomVtxTexU[k] = D_801C5E88[j];
                    roomVtxTexV[k] = D_801C5EB0[i];
                    temp2 += arg6;
                }
                temp1 += arg7;
            }
            break;

        case 4:
        case 5:
            temp1 = arg5;

            for (i = 0, k = 0; k < 25; i++) {
                temp2 = arg3;
                for (j = 0; j < 5; j++, k++) {
                    roomVtxPosY[k] = arg4;
                    roomVtxPosX[k] = temp2;
                    roomVtxPosZ[k] = temp1;
                    roomVtxTexU[k] = D_801C5E88[j];
                    roomVtxTexV[k] = D_801C5E9C[i];
                    temp2 += arg6;
                }
                temp1 += arg7;
            }
            break;

        default:
            break;
    }

    skyboxCtx->roomDL = &skyboxCtx->dListBuf[2 * arg8][0];

    for (i = 0; i < 0x20; i++) {
        index = D_801C5E48[i];

        roomVtx[arg2 + i].v.ob[0] = roomVtxPosX[index];
        roomVtx[arg2 + i].v.ob[1] = roomVtxPosY[index];
        roomVtx[arg2 + i].v.ob[2] = roomVtxPosZ[index];
        roomVtx[arg2 + i].v.flag = 0;
        roomVtx[arg2 + i].v.tc[0] = roomVtxTexU[index];
        roomVtx[arg2 + i].v.tc[1] = roomVtxTexV[index];
        roomVtx[arg2 + i].v.cn[1] = 0;
        roomVtx[arg2 + i].v.cn[2] = 0;
        roomVtx[arg2 + i].v.cn[0] = 255;
    }
    gSPVertex(skyboxCtx->roomDL++, &roomVtx[arg2], 32, 0);
    arg2 += i;
    gSPCullDisplayList(skyboxCtx->roomDL++, 0, 15);

    if ((arg8 == 4) || (arg8 == 5)) {
        phi_a2_4 = 0;
        for (phi_t2_4 = 0, phi_ra = 0; phi_ra < 4; phi_ra++, phi_a2_4 += 0x1F) {
            for (phi_a0_4 = 0, phi_t1 = 0; phi_t1 < 4; phi_t1++, phi_a0_4 += 0x1F, phi_t2_4 += 4) {
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[0] + D_801C5E30[arg8], 0,
                                 G_TX_RENDERTILE, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[1] + D_801C5E30[arg8], 0x80,
                                 1, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gSP1Quadrangle(skyboxCtx->roomDL++, D_801C5EC4[phi_t2_4 + 1], D_801C5EC4[phi_t2_4 + 2],
                               D_801C5EC4[phi_t2_4 + 3], D_801C5EC4[phi_t2_4 + 0], 3);
            }
        }
    } else {
        phi_a2_4 = 0;
        for (phi_t2_4 = 0, phi_ra = 0; phi_ra < 2; phi_ra++, phi_a2_4 += 0x1F) {
            for (phi_a0_4 = 0, phi_t1 = 0; phi_t1 < 4; phi_t1++, phi_a0_4 += 0x1F, phi_t2_4 += 4) {
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[0] + D_801C5E30[arg8], 0,
                                 G_TX_RENDERTILE, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[1] + D_801C5E30[arg8], 0x80,
                                 1, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gSP1Quadrangle(skyboxCtx->roomDL++, D_801C5EC4[phi_t2_4 + 1], D_801C5EC4[phi_t2_4 + 2],
                               D_801C5EC4[phi_t2_4 + 3], D_801C5EC4[phi_t2_4 + 0], 3);
            }
        }
        phi_a2_4 -= 0x1F;
        for (phi_ra = 0; phi_ra < 2; phi_ra++, phi_a2_4 -= 0x1F) {
            for (phi_a0_4 = 0, phi_t1 = 0; phi_t1 < 4; phi_t1++, phi_a0_4 += 0x1F, phi_t2_4 += 4) {
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[0] + D_801C5E30[arg8], 0,
                                 G_TX_RENDERTILE, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gDPLoadMultiTile(skyboxCtx->roomDL++, (uintptr_t)skyboxCtx->staticSegments[1] + D_801C5E30[arg8], 0x80,
                                 1, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, phi_a0_4, phi_a2_4, phi_a0_4 + 0x1F,
                                 phi_a2_4 + 0x1F, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                gSP1Quadrangle(skyboxCtx->roomDL++, D_801C5EC4[phi_t2_4 + 1], D_801C5EC4[phi_t2_4 + 2],
                               D_801C5EC4[phi_t2_4 + 3], D_801C5EC4[phi_t2_4 + 0], 3);
            }
        }
    }
    gSPEndDisplayList(skyboxCtx->roomDL++);
    return arg2;
}

void func_80143148(SkyboxContext* skyboxCtx, s32 arg1) {
    static struct_801C5F44 D_801C5F44[] = {
        { -64, 64, -64, 32, -32 }, { 64, 64, 64, -32, -32 }, { -64, 64, 64, -32, -32 },
        { 64, 64, -64, 32, -32 },  { -64, 64, 64, 32, -32 }, { -64, -64, -64, 32, 32 },
    };
    s32 ret = 0;
    struct_801C5F44* unkStruct;
    s32 face;

    for (face = 0; face < arg1; face++) {
        unkStruct = &D_801C5F44[face];
        ret = func_80142440(skyboxCtx, skyboxCtx->roomVtx, ret, unkStruct->unk0, unkStruct->unk4, unkStruct->unk8,
                            unkStruct->unkC, unkStruct->unk10, face);
    }
}

void Skybox_Setup(GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId) {
    PlayState* play = (PlayState*)gameState;
    size_t size;
    void* segment;

    skyboxCtx->rot.z = 0.0f;

    switch (skyboxId) {
        case SKYBOX_NORMAL_SKY:
            // Send a DMA request for the cloudy sky texture
            skyboxCtx->staticSegments[0] = gLoBuffer.skyboxBuffer;
            size = SEGMENT_ROM_SIZE(d2_cloud_static);
            segment = (void*)ALIGN8((uintptr_t)skyboxCtx->staticSegments[0] + size);
            DmaMgr_SendRequest0(skyboxCtx->staticSegments[0], SEGMENT_ROM_START(d2_cloud_static), size);

            // Send a DMA request for the clear sky texture
            skyboxCtx->staticSegments[1] = segment;
            size = SEGMENT_ROM_SIZE(d2_fine_static);
            segment = (void*)ALIGN8((uintptr_t)segment + size);
            DmaMgr_SendRequest0(skyboxCtx->staticSegments[1], SEGMENT_ROM_START(d2_fine_static), size);

            // Send a DMA request for the skybox palette
            skyboxCtx->paletteStaticSegment = segment;
            size = SEGMENT_ROM_SIZE(d2_fine_pal_static);
            segment = (void*)ALIGN8((uintptr_t)segment + size);
            DmaMgr_SendRequest0(skyboxCtx->paletteStaticSegment, SEGMENT_ROM_START(d2_fine_pal_static), size);

            skyboxCtx->prim.r = 145;
            skyboxCtx->prim.g = 120;
            skyboxCtx->prim.b = 155;

            skyboxCtx->env.r = 40;
            skyboxCtx->env.g = 0;
            skyboxCtx->env.b = 40;

            // Inverted Stone Tower Temple and Inverted Stone Tower
            if ((play->sceneId == SCENE_F41) || (play->sceneId == SCENE_INISIE_R)) {
                skyboxCtx->rot.z = 3.15f;
            }
            break;

        case SKYBOX_2:
            break;

        default:
            break;
    }
}

void func_80143324(PlayState* play, SkyboxContext* skyboxCtx, s16 skyboxId) {
    size_t size;

    switch (skyboxId) {
        case SKYBOX_NORMAL_SKY:
            osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

            if (play->envCtx.skybox1Index == 0) {
                // Send a DMA request for the clear sky texture
                size = SEGMENT_ROM_SIZE(d2_fine_static);

                DmaMgr_SendRequestImpl(&skyboxCtx->unk188, skyboxCtx->staticSegments[0],
                                       SEGMENT_ROM_START(d2_fine_static), size, 0, &skyboxCtx->loadQueue, NULL);
            } else {
                // Send a DMA request for the cloudy sky texture
                size = SEGMENT_ROM_SIZE(d2_cloud_static);

                DmaMgr_SendRequestImpl(&skyboxCtx->unk188, skyboxCtx->staticSegments[0],
                                       SEGMENT_ROM_START(d2_cloud_static), size, 0, &skyboxCtx->loadQueue, NULL);
            }

            osRecvMesg(&skyboxCtx->loadQueue, NULL, OS_MESG_BLOCK);
            osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

            if (play->envCtx.skybox2Index == 0) {
                // Send a DMA request for the clear sky texture
                size = SEGMENT_ROM_SIZE(d2_fine_static);

                DmaMgr_SendRequestImpl(&skyboxCtx->unk1A8, skyboxCtx->staticSegments[1],
                                       SEGMENT_ROM_START(d2_fine_static), size, 0, &skyboxCtx->loadQueue, NULL);
            } else {
                // Send a DMA request for the cloudy sky texture
                size = SEGMENT_ROM_SIZE(d2_cloud_static);

                DmaMgr_SendRequestImpl(&skyboxCtx->unk1A8, skyboxCtx->staticSegments[1],
                                       SEGMENT_ROM_START(d2_cloud_static), size, 0, &skyboxCtx->loadQueue, NULL);
            }

            osRecvMesg(&skyboxCtx->loadQueue, NULL, OS_MESG_BLOCK);
            osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

            size = SEGMENT_ROM_SIZE(d2_fine_pal_static);

            // Send a DMA request for the skybox palette
            DmaMgr_SendRequestImpl(&skyboxCtx->unk1C8, skyboxCtx->paletteStaticSegment,
                                   SEGMENT_ROM_START(d2_fine_pal_static), size, 0, &skyboxCtx->loadQueue, NULL);

            osRecvMesg(&skyboxCtx->loadQueue, NULL, OS_MESG_BLOCK);
            break;

        default:
            break;
    }
}

void Skybox_Init(GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId) {
    skyboxCtx->skyboxShouldDraw = false;
    skyboxCtx->rot.x = skyboxCtx->rot.y = skyboxCtx->rot.z = 0.0f;

    Skybox_Setup(gameState, skyboxCtx, skyboxId);

    if (skyboxId != SKYBOX_NONE) {
        skyboxCtx->dListBuf = THA_AllocTailAlign16(&gameState->tha, 0x3840);

        if (skyboxId == SKYBOX_CUTSCENE_MAP) {
            // Allocate enough space for the vertices for a 6 sided skybox (cube)
            skyboxCtx->roomVtx = THA_AllocTailAlign16(&gameState->tha, sizeof(Vtx) * 32 * 6);
            func_80143148(skyboxCtx, 6);
        } else {
            // Allocate enough space for the vertices for a 5 sided skybox (bottom is missing)
            skyboxCtx->roomVtx = THA_AllocTailAlign16(&gameState->tha, sizeof(Vtx) * 32 * 5);
            func_80143148(skyboxCtx, 5);
        }
    }
}
