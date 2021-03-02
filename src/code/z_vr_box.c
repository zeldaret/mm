#include <ultra64.h>
#include <global.h>

s32 D_801C5E30[] = {
    0, 0x2000, 0x4000, 0x6000, 0x8000, 0xC000,
};

u16 D_801C5E48[] = {
    0, 2, 10, 12, 2, 4, 12, 14, 10, 12, 20, 22, 12, 14, 22, 24, 1, 3, 5, 6, 7, 8, 9, 11, 13, 15, 16, 17, 18, 19, 21, 23,
};

s32 D_801C5E88[] = {
    0, 0x7C0, 0xF80, 0x1740, 0x1F00,
};

s32 D_801C5E9C[] = {
    0, 0x7C0, 0xF80, 0x1740, 0x1F00,
};

s32 D_801C5EB0[] = {
    0, 0x7C0, 0xF80, 0x7C0, 0,
};

s16 D_801C5EC4[] = {
    0,  16, 19, 18, 16, 1,  20, 19, 1,  17, 21, 20, 17, 5,  22, 21, 18, 19, 23, 2,  19, 20,
    3,  23, 20, 21, 24, 3,  21, 22, 7,  24, 2,  23, 26, 25, 23, 3,  27, 26, 3,  24, 28, 27,
    24, 7,  29, 28, 25, 26, 30, 10, 26, 27, 11, 30, 27, 28, 31, 11, 28, 29, 15, 31,
};

struct_801C5F44 D_801C5F44[] = {
    { -64, 64, -64, 32, -32 }, { 64, 64, 64, -32, -32 }, { -64, 64, 64, -32, -32 },
    { 64, 64, -64, 32, -32 },  { -64, 64, 64, 32, -32 }, { -64, -64, -64, 32, 32 },
};

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_80142440.asm")

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_80143148.asm")

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_801431E8.asm")
/*void func_801431E8(GameState* state, SkyboxContext* skyboxCtx, s16 skyType) {
    s32 sp2C;
    s32 sp24;
    s16 temp_a2;
    s16 temp_v0_2;
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_v0;

    temp_a2 = skyType;
    skyboxCtx->unk210 = 0.0f;
    if (temp_a2 != 1) {
        if (temp_a2 != 2) {
            return;
        }
    } else {
        skyboxCtx->unk168 = &D_80025D00;
        temp_a3 = 0x1F0A000 - 0x1EFE000;
        sp24 = temp_a3;
        DmaMgr_SendRequest0(&D_80025D00, 0x1EFE000, temp_a3, temp_a3);
        temp_v0 = (temp_a3 + 7 + &D_80025D00) & ~7;
        temp_a2_2 = 0x1EFE000 - 0x1EF2000;
        skyboxCtx->unk16C = temp_v0;
        sp2C = (temp_v0 + temp_a2_2 + 7) & ~7;
        DmaMgr_SendRequest0(skyboxCtx->unk16C, 0x1EF2000, temp_a2_2, temp_a3);
        skyboxCtx->unk178 = sp2C;
        DmaMgr_SendRequest0(sp2C, 0x1F0A000, 0x1F0A200 - 0x1F0A000);
        skyboxCtx->unk222 = 0x91;
        skyboxCtx->unk223 = 0x78;
        skyboxCtx->unk224 = 0x9B;
        skyboxCtx->unk225 = 0x28;
        skyboxCtx->unk226 = 0;
        skyboxCtx->unk227 = 0x28;
        temp_v0_2 = state->unkA4;
        if ((temp_v0_2 == 0x59) || (temp_v0_2 == 0x18)) {
            skyboxCtx->unk210 = D_801DF148;
        }
    }
}*/

void func_80143324(GlobalContext* globalCtx, SkyboxContext* skyboxCtx, s16 skyType) {
    u32 size;

    if (1) {}

    if (skyType == 1) {
        osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

        if (globalCtx->kankyoContext.unk10 == 0) {
            // Make a DMA request for the clear sky texture
            size = (u32)_vr_fine_staticSegmentRomEnd - (u32)_vr_fine_staticSegmentRomStart;

            DmaMgr_SendRequestImpl(&skyboxCtx->unk188, skyboxCtx->skyboxStaticSegment[0],
                                   (u32)_vr_fine_staticSegmentRomStart, size, 0, &skyboxCtx->loadQueue, NULL);
        } else {
            // Make a DMA request for the cloudy sky texture
            size = (u32)_vr_cloud_staticSegmentRomEnd - (u32)_vr_cloud_staticSegmentRomStart;

            DmaMgr_SendRequestImpl(&skyboxCtx->unk188, skyboxCtx->skyboxStaticSegment[0],
                                   (u32)_vr_cloud_staticSegmentRomStart, size, 0, &skyboxCtx->loadQueue, NULL);
        }

        osRecvMesg(&skyboxCtx->loadQueue, NULL, 1);
        osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

        if (globalCtx->kankyoContext.unk11 == 0) {
            // Make a DMA request for the clear sky texture
            size = (u32)_vr_fine_staticSegmentRomEnd - (u32)_vr_fine_staticSegmentRomStart;

            DmaMgr_SendRequestImpl(&skyboxCtx->unk1A8, skyboxCtx->skyboxStaticSegment[1],
                                   (u32)_vr_fine_staticSegmentRomStart, size, 0, &skyboxCtx->loadQueue, NULL);
        } else {
            // Make a DMA request for the cloudy sky texture
            size = (u32)_vr_cloud_staticSegmentRomEnd - (u32)_vr_cloud_staticSegmentRomStart;

            DmaMgr_SendRequestImpl(&skyboxCtx->unk1A8, skyboxCtx->skyboxStaticSegment[1],
                                   (u32)_vr_cloud_staticSegmentRomStart, size, 0, &skyboxCtx->loadQueue, NULL);
        }

        osRecvMesg(&skyboxCtx->loadQueue, NULL, 1);
        osCreateMesgQueue(&skyboxCtx->loadQueue, &skyboxCtx->loadMsg, 1);

        size = (u32)_vr_pal_staticSegmentRomEnd - (u32)_vr_pal_staticSegmentRomStart;

        // Make a DMA request for the skybox palette
        DmaMgr_SendRequestImpl(&skyboxCtx->unk1C8, skyboxCtx->skyboxPaletteStaticSegment,
                               (u32)_vr_pal_staticSegmentRomStart, size, 0, &skyboxCtx->loadQueue, NULL);

        osRecvMesg(&skyboxCtx->loadQueue, NULL, 1);
    }
}

void func_801434E4(GameState* state, SkyboxContext* skyboxCtx, s16 skyType) {
    skyboxCtx->skyboxShouldDraw = 0;
    skyboxCtx->rotX = skyboxCtx->rotY = skyboxCtx->rotZ = 0.0f;

    func_801431E8(state, skyboxCtx, skyType);

    if (skyType != 0) {
        skyboxCtx->unk17C = GameStateHeap_AllocFromEnd(&state->heap, 0x3840);

        if (skyType == 5) {
            // Allocate enough space for the vertices for a 6 sided skybox (cube)
            skyboxCtx->roomVtx = GameStateHeap_AllocFromEnd(&state->heap, sizeof(Vtx) * 32 * 6);
            func_80143148(skyboxCtx, 6);
        } else {
            // Allocate enough space for the vertices for a 5 sided skybox (bottom is missing)
            skyboxCtx->roomVtx = GameStateHeap_AllocFromEnd(&state->heap, sizeof(Vtx) * 32 * 5);
            func_80143148(skyboxCtx, 5);
        }
    }
}
