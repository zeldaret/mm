#include <ultra64.h>
#include <global.h>

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_80142440.asm")

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_80143148.asm")

#pragma GLOBAL_ASM("./asm/nonmatching/z_vr_box/func_801431E8.asm")

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
