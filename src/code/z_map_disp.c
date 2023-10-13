#include "global.h"
#include "gfx.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

void MapDisp_DestroyMapI(PlayState* play);
void MapDisp_InitMapI(PlayState* play);

extern s32 D_801BEAD0[4]; // G_IM_SIZ
extern s32 D_801BEAE0[4]; // siz_LOAD_BLOCK
extern u32 D_801BEAF0[4]; // siz_INCR
extern s32 D_801BEB00[4]; // siz_SHIFT
extern u32 D_801BEB10[4]; // siz_BYTES
extern u32 D_801BEB20[4]; // siz_LINE_BYTES
extern TexturePtr D_801BEB38;
extern T_801BEBB8 D_801BEBB8;
extern s16 D_801BEBFA;         // D_801BEBB8.unk42
extern MinimapList D_801BEC14; // D_801F5130
extern s32 D_801BEC1C;         // current scene's no. of rooms
extern s32 D_801BEC20;         // MinimapChest count
extern TransitionActorList D_801BEC24;
extern Color_RGBA8 D_801BEC2C[12]; // cat colors
extern T_801BEC5C D_801BEC5C[5];
extern T_801BEC70 D_801BEC70;
extern u16 D_801BEC84[0x10]; // palette 0
extern u16 D_801BECA4[0x10]; // palette 1
extern u16 D_801BECC4[0x10]; // palette 2
extern TexturePtr D_801BECE4[6];
extern TexturePtr D_801BED00[9];
extern T_801BED24 D_801BED24[2];

extern MinimapEntry D_801F5130[0x50];
extern MinimapChest D_801F5270[32];
extern TransitionActorEntry D_801F53B0[48];
extern T_801F56B0 D_801F56B0;

extern TexturePtr D_02002460;
extern TexturePtr D_02003F20;
extern Gfx D_0401ED00[];
extern TexturePtr D_0C000000;

void MapDisp_GetMapITexture(void* dst, s32 mapId) {
    if (MapDisp_GetSizeOfMapITex(mapId) != 0) {
        CmpDma_LoadFile(SEGMENT_ROM_START(map_i_static), mapId, dst, MapDisp_GetSizeOfMapITex(mapId));
    }
}

void func_80102E90(PlayState* play, s16* arg1) {
    *arg1 = -1;
}

void func_80102EA4(PlayState* play, s16* arg1) {
}

void func_80102EB4(u32 param_1) {
    D_801BEBB8.unk20 |= param_1;
}

void func_80102ED0(u32 param_1) {
    D_801BEBB8.unk20 &= ~param_1;
}

s32 func_80102EF0(PlayState* play) {
    MinimapEntry* entry;
    s8 curRoom;

    if (Map_IsInBossArea(play) == true) {
        return true;
    }
    curRoom = play->roomCtx.curRoom.num;
    if (curRoom == -1) {
        return false;
    }
    entry = &D_801BEBB8.minimapList->entry[curRoom];
    if (entry->mapId == 0xFFFF) {
        return false;
    }
    if (MapData_GetMapIId(entry->mapId) == MAPDATA_MAP_I_MAX) {
        return false;
    }
    return true;
}

f32 func_80102F9C(f32 arg0) {
    s32 i;

    if ((D_801BEBB8.unk48[D_801BEBB8.unk40 - 1] - 80.0f) < arg0) {
        return D_801BEBB8.unk48[D_801BEBB8.unk40 - 1];
    }
    for (i = D_801BEBB8.unk40 - 2; i >= 0; i--) {
        if (((D_801BEBB8.unk48[i] - 80.0f) < arg0) && (arg0 < (D_801BEBB8.unk48[i + 1] + 80.0f))) {
            return D_801BEBB8.unk48[i];
        }
    }
    if (arg0 < (D_801BEBB8.unk48[0] + 80.0f)) {
        return D_801BEBB8.unk48[0];
    }
    return 0.0f;
}

void MapDisp_GetMapTexDim(MinimapEntry* minimapEntry, s32* width, s32* height) {
    MapData_GetMapTexDim(minimapEntry->mapId, width, height);
}

void MapDisp_GetMapScale(MinimapEntry* minimapEntry, s32* scale) {
    MapData_GetMapScale(minimapEntry->mapId, scale);
    if (*scale == 0) {
        *scale = 20;
    }
}

void MapDisp_GetMapPos(MinimapEntry* minimapEntry, s32* offsetX, s32* offsetY) {
    s32 width;
    s32 height;
    s32 temp;
    s32 temp2;

    if (minimapEntry->mapId == 0xFFFF) {
        *offsetX = 0;
        *offsetY = 0;
        return;
    }
    MapDisp_GetMapTexDim(minimapEntry, &width, &height);
    MapData_GetMapTexOffset(minimapEntry->mapId, offsetX, offsetY);
    if (minimapEntry->unk8 & 1) {
        temp = width / 2;
        *offsetX = (temp - *offsetX) + temp;
    }
    if (minimapEntry->unk8 & 2) {
        temp2 = height / 2;
        *offsetY = (temp2 - *offsetY) + temp2;
    }
}

#ifdef NON_MATCHING
// https://decomp.me/scratch/XPZfI
void func_801031D0(PlayState* play, TexturePtr arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    MinimapEntry* spCC;
    s32 spC8;
    s32 spC4;
    s16 var_a0_4;
    s16 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_v1_4;
    s32 var_v1_5;
    Color_RGBA8 spAC_color;
    s32 spA8_drawType;

    spCC = &D_801BEBB8.minimapList->entry[arg4];
    if ((spCC->mapId != 0xFFFF) && (arg1 != 0)) {
        MapDisp_GetMapTexDim(spCC, &spC8, &spC4);
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL39_Overlay(play->state.gfxCtx);
        MapData_GetMapColor(MapData_GetMapColorIndex(spCC->mapId), &spAC_color);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, spAC_color.r, spAC_color.g, spAC_color.b,
                        (s32)(play->interfaceCtx.minimapAlpha * arg5 * spAC_color.a / 255.0f));
        MapData_GetDrawType(spCC->mapId, &spA8_drawType);
        switch (spA8_drawType) {
            case MAPDATA_DRAW_1:
                gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPLoadTextureBlock_4b(OVERLAY_DISP++, arg1, G_IM_FMT_IA, spC8, spC4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case MAPDATA_DRAW_3:
                gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0,
                                  TEXEL0);
                gDPLoadTextureBlock_4b(OVERLAY_DISP++, arg1, G_IM_FMT_I, spC8, spC4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            default:
            case MAPDATA_DRAW_0:
                gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPLoadTextureBlock_4b(OVERLAY_DISP++, arg1, G_IM_FMT_I, spC8, spC4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
        }

        var_t1 = (spCC->unk8 & 1) ? (spC8 - 1) << 5 : 0;
        var_t0 = (spCC->unk8 & 2) ? 0 : (spC4 - 1) << 5;

        var_v1_4 = (spCC->unk8 & 1) ? -1 : 1;
        var_a3 = var_v1_4 << 0xA;
        var_v1_5 = (spCC->unk8 & 2) ? 1 : -1;

        if ((spCC->unk8 & 1) != 0) {
            var_a3 = var_a3 & 0xFFFF;
        }
        if ((spCC->unk8 & 2) != 0) {
            var_a0_4 = var_v1_5 << 0xA;
        } else {
            var_a0_4 = (var_v1_5 << 0xA) & 0xFFFF;
        }
        gSPTextureRectangle(OVERLAY_DISP++, arg2 << 2, arg3 << 2, (spC8 + arg2) << 2, (arg3 + spC4) << 2,
                            G_TX_RENDERTILE, var_t1, var_t0, var_a3, var_a0_4);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
#else
void func_801031D0(PlayState* play, TexturePtr arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801031D0.s")
#endif

// Tests if the map data should be rotated 180 degrees
// SCENE_35TAKI is the only scene with data flipped in this manner.
s32 MapDisp_IsDataRotated(PlayState* play) {
    if (play->sceneId == SCENE_35TAKI) {
        return true;
    }
    return false;
}

s32 func_80103A10(PlayState* play) {
    if ((gSaveContext.save.entrance == 0x6400) && (Cutscene_GetSceneLayer(play) != 0)) {
        return false;
    }
    return true;
}

#define gDPLoadTextureBlock_TEST(pkt, timg, fmt, siz_LOAD_BLOCK, siz_INCR, siz_SHIFT, siz_BYTES, siz_LINE_BYTES, siz, \
                                 width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                          \
    _DW({                                                                                                             \
        gDPSetTextureImage(pkt, fmt, siz_LOAD_BLOCK, 1, timg);                                                        \
        gDPSetTile(pkt, fmt, siz_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);         \
        gDPLoadSync(pkt);                                                                                             \
        gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, (((width) * (height) + siz_INCR) >> siz_SHIFT) - 1,                    \
                     CALC_DXT(width, siz_BYTES));                                                                     \
        gDPPipeSync(pkt);                                                                                             \
        gDPSetTile(pkt, fmt, siz, (((width)*siz_LINE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,   \
                   cms, masks, shifts);                                                                               \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                               \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                         \
    })

#ifdef NON_MATCHING
// https://decomp.me/scratch/TR5Jq
void func_80103A58(PlayState* play, Actor* actor) {
    MinimapEntry* spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    f32 spC0;
    u32 pad;
    s32 scale;
    Player* spB4;
    u32 pad2;
    s32 spAC_scaleTemp;
    // GraphicsContext *spA8;

    spDC = &D_801BEBB8.minimapList->entry[D_801BEBB8.curRoom];
    spB4 = GET_PLAYER(play);
    if (spDC->mapId != 0xFFFF) {
        MapDisp_GetMapPos(spDC, &spD0, &spCC);
        MapDisp_GetMapTexDim(spDC, &spC8, &spC4);
        scale = D_801BEBB8.minimapList->scale;
        if (D_801BEBB8.minimapList->scale == 0) {
            scale = 20;
        } else if (D_801BEBB8.minimapList->scale == -1) {
            MapDisp_GetMapScale(spDC, &spAC_scaleTemp);
            scale = spAC_scaleTemp;
        }
        spC0 = 1.0f / (f32)scale;
        if (!MapDisp_IsDataRotated(play)) {
            spD8 = (s32)((actor->world.pos.x - (f32)spDC->unk2) * spC0) + D_801BEBB8.unk8 + D_801BEBB8.unkC -
                   D_801BEBB8.unk8 + spD0;
            spD4 = (s32)((actor->world.pos.z - (f32)spDC->unk6) * spC0) + D_801BEBB8.unkA + D_801BEBB8.unkE -
                   D_801BEBB8.unkA + spCC;
        } else {
            spD8 = -(s32)((actor->world.pos.x - (f32)spDC->unk2) * spC0) + D_801BEBB8.unk8 + D_801BEBB8.unkC -
                   D_801BEBB8.unk8 + spD0;
            spD4 = -(s32)((actor->world.pos.z - (f32)spDC->unk6) * spC0) + D_801BEBB8.unkA + D_801BEBB8.unkE -
                   D_801BEBB8.unkA + spCC;
        }
        if ((spD8 > 0) && (spD8 < 0x3FF) && (spD4 > 0) && (spD4 < 0x3FF)) {
            OPEN_DISPS(play->state.gfxCtx);

            if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & 0x80000000)) {
                s16 spA2;
                Gfx_SetupDL42_Overlay(play->state.gfxCtx);
                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
                gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

                Matrix_Translate((f32)spD8 - 160.0f, 120.0f - (f32)spD4, 0.0f, MTXMODE_NEW);
                Matrix_RotateXFApply(-1.6f);
                spA2 = (s32)(0x7FFF - actor->focus.rot.y) / 1024;
                if (MapDisp_IsDataRotated(play)) {
                    spA2 += 0x7FFF;
                }
                Matrix_RotateYF((f32)spA2 / 10.0f, MTXMODE_APPLY);
                Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
                gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 255, 0, play->interfaceCtx.minimapAlpha);
                gSPDisplayList(OVERLAY_DISP++, &D_0401ED00);
                return;
            }
            if (actor->id == ACTOR_EN_BOX) {
                if (!Flags_GetTreasure(play, actor->params & 0x1F)) {
                    if (func_80102F9C(spB4->actor.world.pos.y) == func_80102F9C(actor->world.pos.y)) {
                        Gfx_SetupDL39_Overlay(play->state.gfxCtx);
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
                        gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
                        gDPPipeSync(OVERLAY_DISP++);

                        gDPLoadTextureBlock_TEST(
                            OVERLAY_DISP++, &D_02003F20, G_IM_FMT_RGBA, D_801BEAE0[2], D_801BEAF0[2], D_801BEB00[2],
                            D_801BEB10[2], D_801BEB20[2], D_801BEAD0[2], 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                        // gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_RGBA, D_801BEAE0.unk8, 1, &D_02003F20);
                        // gDPSetTile(OVERLAY_DISP++, G_IM_FMT_RGBA, D_801BEAE0.unk8, 0, 0x0000, G_TX_LOADTILE, 0,
                        //     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                        //     G_TX_NOMASK, //maskt
                        //     G_TX_NOLOD, //shiftt
                        //     G_TX_NOMIRROR | G_TX_WRAP, //cms
                        //     G_TX_NOMASK, //masks
                        //     G_TX_NOLOD); //shifts
                        // gDPLoadSync(OVERLAY_DISP++);
                        // gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0,
                        //  ((D_801BEAF8 + 0x40) >> D_801BEB08) - 1,
                        //        (((D_801BEB18 * 8 >> 3 == 0)? 1 : D_801BEB18) + 0x7FF)
                        //     /   ((D_801BEB18 * 8 >> 3 == 0)? 1 : D_801BEB18));
                        // gDPPipeSync(OVERLAY_DISP++);
                        // gDPSetTile(OVERLAY_DISP++, G_IM_FMT_RGBA, D_801BEAD8,
                        //   ((D_801BEB28 * 8) + 7) >> 3, 0x0000, G_TX_RENDERTILE, 0,
                        //     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                        //     G_TX_NOMASK,
                        //     G_TX_NOLOD,
                        //     G_TX_NOMIRROR | G_TX_WRAP,
                        //     G_TX_NOMASK,
                        //     G_TX_NOLOD);
                        // gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 0x001C, 0x001C);
                        gSPTextureRectangle(OVERLAY_DISP++, (spD8 - 4) << 2, (spD4 - 4) << 2, (spD8 + 4) << 2,
                                            (spD4 + 4) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                        return;
                    }
                }
            }
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            if (actor->flags & 0x80000000) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, D_801BEC2C[actor->category].r, D_801BEC2C[actor->category].g,
                                D_801BEC2C[actor->category].b, play->interfaceCtx.minimapAlpha);
                gSPTextureRectangle(OVERLAY_DISP++, (spD8 - 1) << 2, (spD4 - 1) << 2, (spD8 + 1) << 2, (spD4 + 1) << 2,
                                    G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
            }

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
#else
void func_80103A58(PlayState* play, Actor* actor);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80103A58.s")
#endif

void func_8010439C(PlayState* play) {
    ActorContext* actorCtx;
    s32 i;

    if (play->roomCtx.curRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_801BEB38, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actorCtx = &play->actorCtx;
        for (i = 0; i < ACTORCAT_MAX; i++) {
            Actor* actor = actorCtx->actorLists[i].first;
            if (actor != NULL) {
                do {
                    if ((actor->update != NULL) && (actor->init == NULL) &&
                        (Object_IsLoaded(&play->objectCtx, actor->objectSlot)) &&
                        ((actor->id == ACTOR_EN_BOX) || (i == ACTORCAT_PLAYER) ||
                         (actor->flags & ACTOR_FLAG_80000000)) &&
                        ((D_801BEBB8.curRoom == actor->room) || (actor->room == -1))) {
                        func_80103A58(play, actor);
                    }
                    actor = actor->next;
                } while (actor != NULL);
            }
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void func_801045AC(PlayState* play, Actor* actor) {
    MinimapEntry* sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    Player* player = GET_PLAYER(play);
    f32 sp5C;
    f32 temp_fv1 = fabsf(player->actor.world.pos.y - actor->world.pos.y);
    s32 var_v1;
    f32 sp50 = 1.0f - (1 / 350.0f) * temp_fv1;

    if (sp50 < 0) {
        sp50 = 0.0f;
    }
    sp7C = &D_801BEBB8.minimapList->entry[D_801BEBB8.curRoom];
    if (sp7C->mapId != 0xFFFF) {
        MapDisp_GetMapPos(sp7C, &sp70, &sp6C);
        MapDisp_GetMapTexDim(sp7C, &sp68, &sp64);

        var_v1 = D_801BEBB8.minimapList->scale;
        if (D_801BEBB8.minimapList->scale == 0) {
            var_v1 = 20;
        } else if (D_801BEBB8.minimapList->scale == -1) {
            s32 sp4C;

            MapDisp_GetMapScale(sp7C, &sp4C);
            var_v1 = sp4C;
        }
        sp5C = 1.0f / var_v1;
        if (!MapDisp_IsDataRotated(play)) {
            sp78 = (((s32)((actor->world.pos.x - sp7C->unk2) * sp5C) + D_801BEBB8.unk8 + D_801BEBB8.unkC) -
                    D_801BEBB8.unk8) +
                   sp70;
            sp74 = (((s32)((actor->world.pos.z - sp7C->unk6) * sp5C) + D_801BEBB8.unkA + D_801BEBB8.unkE) -
                    D_801BEBB8.unkA) +
                   sp6C;
        } else {
            sp78 = (((D_801BEBB8.unk8 - (s32)((actor->world.pos.x - sp7C->unk2) * sp5C)) + D_801BEBB8.unkC) -
                    D_801BEBB8.unk8) +
                   sp70;
            sp74 = (((D_801BEBB8.unkA - (s32)((actor->world.pos.z - sp7C->unk6) * sp5C)) + D_801BEBB8.unkE) -
                    D_801BEBB8.unkA) +
                   sp6C;
        }
        if ((sp78 > 0) && (sp78 < 0x3FF) && (sp74 > 0) && (sp74 < 0x3FF)) {
            OPEN_DISPS(play->state.gfxCtx);

            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

            if ((actor->category == 0xA) && (func_80103A10(play) != 0)) {
                s32 pad;

                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, D_801BEC2C[actor->category].r, D_801BEC2C[actor->category].g,
                                D_801BEC2C[actor->category].b,
                                (s32)((D_801BEC2C[actor->category].a * (1.0f - D_801BEBB8.swapAnimTimer * 0.05f) *
                                       sp50 * play->interfaceCtx.minimapAlpha) /
                                      255.0f));

                var_v1 = D_801BEBB8.minimapList->scale;
                if (D_801BEBB8.minimapList->scale == 0) {
                    var_v1 = 20;
                } else if (D_801BEBB8.minimapList->scale == -1) {
                    s32 sp34;

                    MapDisp_GetMapScale(sp7C, &sp34);
                    var_v1 = sp34;
                }
                if (var_v1 <= 50) {
                    gSPTextureRectangle(OVERLAY_DISP++, (sp78 - 2) << 2, (sp74 - 2) << 2, (sp78 + 2) << 2,
                                        (sp74 + 2) << 2, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                } else {
                    gSPTextureRectangle(OVERLAY_DISP++, (sp78 - 1) << 2, (sp74 - 1) << 2, (sp78 + 1) << 2,
                                        (sp74 + 1) << 2, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                }
            }

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

void func_80104AE8(PlayState* play) {
    s32 i;
    Actor* actor;

    if (play->roomCtx.curRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_801BEB38, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actor = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
        if (actor != NULL) {
            do {
                if ((actor->update != NULL) && (actor->init == NULL) &&
                    Object_IsLoaded(&play->objectCtx, actor->objectSlot) &&
                    ((D_801BEBB8.curRoom == actor->room) || (actor->room == -1))) {
                    func_801045AC(play, actor);
                }
                actor = actor->next;
            } while (actor != NULL);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

//! FAKE: https://decomp.me/scratch/kvGBZ
void func_80104C80(PlayState* play) {
    s32 objectSlot = Object_GetSlot(&play->objectCtx, GAMEPLAY_DANGEON_KEEP);

    if (objectSlot <= OBJECT_SLOT_NONE) {
        D_801BEBB8.unk20 |= 1;
    } else {
        do { } while (!Object_IsLoaded(&play->objectCtx, objectSlot)); }
    if (&play->objectCtx) {}
}

void MapDisp_Init(PlayState* play) {
    s32 i;

    D_801BEBB8.minimapList = NULL;
    D_801BEBB8.curRoom = -1;
    D_801BEBB8.unk8 = 0xD2;
    D_801BEBB8.unkA = 0x8C;
    D_801BEBB8.unkC = 0xD2;
    D_801BEBB8.unkE = 0x8C;
    D_801BEBB8.lMapCurTex = NULL;
    D_801BEBB8.prevRoom = -1;
    D_801BEBB8.lMapPrevTex = NULL;
    D_801BEBB8.unk1C = 0;
    D_801BEBB8.unk1E = 0;
    D_801BEBB8.unk20 = 0;
    D_801BEBB8.swapAnimTimer = 0;

    if (!Map_IsInBossArea(play)) {
        D_801BEC1C = play->numRooms;
    }
    D_801BEBB8.texBuff0 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    D_801BEBB8.texBuff1 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    func_80104C80(play);
    if (!Map_IsInBossArea(play)) {
        D_801BEBB8.sceneMinX = 0;
        D_801BEBB8.sceneMinZ = 0;
        D_801BEBB8.sceneWidth = 100;
        D_801BEBB8.sceneHeight = 100;
        D_801BEBB8.sceneMidX = (s16)(s32)((f32)D_801BEBB8.sceneMinX + ((f32)D_801BEBB8.sceneWidth * 0.5f));
        D_801BEBB8.sceneMidZ = (s16)(s32)((f32)D_801BEBB8.sceneMinZ + ((f32)D_801BEBB8.sceneHeight * 0.5f));
    }
    D_801BEBB8.unk3C = THA_AllocTailAlign16(&play->state.tha, D_801BEC1C * sizeof(s16));

    for (i = 0; i < D_801BEC1C; i++) {
        func_80102E90(play, &D_801BEBB8.unk3C[i]);
    }
    D_801BEBB8.unk48 = THA_AllocTailAlign16(&play->state.tha, 32 * sizeof(s16));

    for (i = 0; i < 32; i++) {
        D_801BEBB8.unk48[i] = -0x7FFF;
    }
    MapDisp_InitMapI(play);
    D_801BEBB8.unk58 = 0;
    D_801BEBB8.unk5A = 0;
    if (Map_IsInBossArea(play)) {
        func_8010549C(play, NULL);
        func_8010565C(play, 0, NULL);
    }
}

void func_80104F34(PlayState* play) {
    s32 i1;
    s32 i2;
    s32 i3;
    s32 i4;

    for (i1 = 0; i1 < 32; i1++) {
        D_801BEBB8.unk48[i1] = -0x7FFF;
    }
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        MinimapEntry* mapEntry1 = &D_801BEBB8.minimapList->entry[i2];

        if (mapEntry1->mapId == 0xFFFF) {
            continue;
        }
        for (i1 = 0; i1 < 32; i1++) {
            if (D_801BEBB8.unk48[i1] == -0x7FFF) {
                D_801BEBB8.unk48[i1] = mapEntry1->unk4;
                break;
            } else if (fabsf((f32)D_801BEBB8.unk48[i1] - (f32)mapEntry1->unk4) < 5.0f) {
                break;
            }
        }
    }
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        if (D_801BEBB8.unk48[i2] == -0x7FFF) {
            break;
        }
        for (i3 = i2 + 1; i3 < D_801BEC1C; i3++) {
            if (D_801BEBB8.unk48[i3] == -0x7FFF) {
                break;
            }
            if (D_801BEBB8.unk48[i3] < D_801BEBB8.unk48[i2]) {
                s16 temp_t3 = D_801BEBB8.unk48[i2];

                D_801BEBB8.unk48[i2] = D_801BEBB8.unk48[i3];
                D_801BEBB8.unk48[i3] = temp_t3;
            }
        }
    }
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        MinimapEntry* mapEntry2 = &D_801BEBB8.minimapList->entry[i2];

        D_801BEBB8.unk3C[i2] = -1;

        for (i4 = 0; i4 < D_801BEC1C; i4++) {
            if (D_801BEBB8.unk48[i4] != -0x7FFF) {
                if (fabsf((f32)D_801BEBB8.unk48[i4] - (f32)mapEntry2->unk4) < 5.0f) {
                    D_801BEBB8.unk3C[i2] = i4;
                    break;
                }
            }
        }
    }
    D_801BEBB8.unk40 = 0;
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        if (D_801BEBB8.unk48[i2] != -0x7FFF) {
            D_801BEBB8.unk40++;
        }
    }
    D_801BEBB8.unk44 = 0;
    for (i2 = 0; i2 < 5; i2++) {
        if (play->sceneId == D_801BEC5C[i2].unk0) {
            D_801BEBB8.unk44 = D_801BEC5C[i2].unk2;
        }
    }
}

s32 func_80105294(void) {
    T_801BEC70 sp4 = D_801BEC70;

    if ((D_801BEBB8.minimapList == NULL) || (D_801BEBB8.unk58 < 0) || (D_801BEBB8.unk58 >= 5) || (D_801BEC1C == 0)) {
        return 0x7B;
    }
    return sp4.unk0[D_801BEBB8.unk58];
}

s16 func_80105318(void) {
    return D_801BEBB8.unk58;
}

// TransitionActor params test
s32 func_80105328(s32 params) {
    if (ENDOOR_PARAMS_GET_TYPE((u16)params) == ENDOOR_TYPE_5) {
        return true;
    }
    return false;
}

void func_8010534C(PlayState* play) {
    TransitionActorList* transitionActors = &D_801BEC24;
    s32 var_v0;
    s32 i;

    for (i = 0; i < transitionActors->count; i++) {
        if (func_80105328(D_801F53B0[i].params) != 0) {
            if (ABS_ALT(D_801F53B0[i].id) != 0x18) {
                for (var_v0 = 0; var_v0 < D_801BEBB8.unk40; var_v0++) {
                    s32 temp = (D_801BEBB8.unk48[var_v0] - 5); // needed for matching

                    if (((var_v0 == D_801BEBB8.unk40 - 1) && (D_801F53B0[i].pos.y >= (D_801BEBB8.unk48[var_v0] - 5)))

                        ||
                        ((var_v0 != D_801BEBB8.unk40 - 1) && (D_801F53B0[i].pos.y >= (D_801BEBB8.unk48[var_v0] - 5)) &&
                         (D_801F53B0[i].pos.y < (D_801BEBB8.unk48[var_v0 + 1] - 5)))) {
                        D_801BEBB8.unk58 = var_v0;
                        return;
                    }
                }
            }
        }
    }
    D_801BEBB8.unk58 = 0;
}

void func_8010549C(PlayState* play, void* segmentAddress) {
    MinimapEntry* var_v1;
    MinimapList* temp_v0;
    s32 i;

    if (!Map_IsInBossArea(play)) {
        D_801BEC1C = play->numRooms;
        temp_v0 = Lib_SegmentedToVirtual(segmentAddress);
        D_801BEC14 = *temp_v0;
        var_v1 = Lib_SegmentedToVirtual(temp_v0->entry);

        for (i = 0; i < D_801BEC1C; i++) {
            D_801F5130[i] = *var_v1++;
        }

        D_801BEC14.entry = D_801F5130;
        if (play->colCtx.colHeader != NULL) {
            D_801BEBB8.sceneMinX = play->colCtx.colHeader->minBounds.x;
            D_801BEBB8.sceneMinZ = play->colCtx.colHeader->minBounds.z;
            D_801BEBB8.sceneWidth = play->colCtx.colHeader->maxBounds.x - play->colCtx.colHeader->minBounds.x;
            D_801BEBB8.sceneHeight = play->colCtx.colHeader->maxBounds.z - play->colCtx.colHeader->minBounds.z;
            D_801BEBB8.sceneMidX = D_801BEBB8.sceneMinX + (D_801BEBB8.sceneWidth * 0.5f);
            D_801BEBB8.sceneMidZ = D_801BEBB8.sceneMinZ + (D_801BEBB8.sceneHeight * 0.5f);
        }
    }
    D_801BEBB8.minimapList = &D_801BEC14;
    func_80104F34(play);
    func_8010534C(play);
}

void func_8010565C(PlayState* play, s32 num, void* segmentAddress) {
    MinimapChest* var_v1;
    s32 var_a3;

    if (!Map_IsInBossArea(play)) {
        var_v1 = Lib_SegmentedToVirtual(segmentAddress);
        for (var_a3 = 0; var_a3 < num; var_v1++, var_a3++) {
            D_801F5270[var_a3] = *var_v1;
        }
        D_801BEC20 = num;
    }
    D_801BEBB8.unk54 = D_801F5270;
    D_801BEBB8.numChests = D_801BEC20;
}

void func_80105818(PlayState* play, s32 num, TransitionActorEntry* transitionActorList) {
    s32 i;

    if (!Map_IsInBossArea(play)) {
        D_801BEC24.count = num;
        for (i = 0; i < num; i++) {
            D_801F53B0[i] = transitionActorList[i];
        }
        D_801BEC24.list = D_801F53B0;
    }
}

void MapDisp_Destroy(PlayState* play) {
    s32 i;

    D_801BEBB8.minimapList = NULL;
    D_801BEBB8.curRoom = -1;
    D_801BEBB8.unkC = 0xD2;
    D_801BEBB8.unkE = 0x8C;
    D_801BEBB8.lMapCurTex = NULL;
    D_801BEBB8.prevRoom = -1;
    D_801BEBB8.lMapPrevTex = NULL;
    D_801BEBB8.unk1C = 0;
    D_801BEBB8.unk1E = 0;
    D_801BEBB8.unk20 = 0;
    D_801BEBB8.swapAnimTimer = 0;
    D_801BEBB8.texBuff0 = NULL;
    D_801BEBB8.texBuff1 = NULL;

    for (i = 0; i < D_801BEC1C; i++) {
        func_80102EA4(play, &D_801BEBB8.unk3C[i]);
    }

    D_801BEBB8.unk3C = NULL;
    D_801BEBB8.unk40 = 0;
    D_801BEBB8.unk42 = 0;
    D_801BEBB8.unk44 = 0;
    D_801BEBB8.unk4C = 0;
    D_801BEBB8.unk48 = NULL;
    D_801BEBB8.numChests = 0;
    D_801BEBB8.unk54 = NULL;
    MapDisp_DestroyMapI(play);
    D_801BEBB8.unk5A = 0;
}

void func_80105B34(PlayState* play) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v1;
    s16 temp_v1_2;

    if ((D_801BEBB8.minimapList != NULL) && (D_801BEC1C != 0)) {
        D_801BEBFA = 8 - play->pauseCtx.unk_256;
        if (D_801BEBB8.prevRoom != -1) {
            if (D_801BEBB8.swapAnimTimer > 0) {
                temp_v1 = D_801BEBB8.unk8;
                temp_a0 = D_801BEBB8.unkC;
                if (temp_v1 != temp_a0) {
                    D_801BEBB8.unkC =
                        (s16)(s32)(((f32)(temp_v1 - temp_a0) / (f32)D_801BEBB8.swapAnimTimer) + (f32)temp_a0);
                }
                temp_v1_2 = D_801BEBB8.unkA;
                temp_a0_2 = D_801BEBB8.unkE;
                if (temp_v1_2 != temp_a0_2) {
                    D_801BEBB8.unkE =
                        (s16)(s32)(((f32)(temp_v1_2 - temp_a0_2) / (f32)D_801BEBB8.swapAnimTimer) + (f32)temp_a0_2);
                }
                D_801BEBB8.swapAnimTimer--;
            } else {
                D_801BEBB8.prevRoom = -1;
                D_801BEBB8.swapAnimTimer = 0;
                D_801BEBB8.unkC = D_801BEBB8.unk8;
                D_801BEBB8.unkE = D_801BEBB8.unkA;
            }
        } else {
            D_801BEBB8.swapAnimTimer = 0;
        }
    }
}

void MapDisp_SwapRooms(s16 nextRoom) {
    MinimapEntry* nextMinimapEntry;
    MinimapEntry* prevMinimapEntry;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;

    if ((D_801BEBB8.minimapList != NULL) && (D_801BEC1C != 0) && (nextRoom != -1)) {
        nextMinimapEntry = &D_801BEBB8.minimapList->entry[nextRoom];
        if ((nextMinimapEntry->mapId < 5) ||
            ((nextMinimapEntry->mapId >= 0x100) && (nextMinimapEntry->mapId < 0x162)) ||
            nextMinimapEntry->mapId == 0xFFFF) {

            D_801BEBB8.prevRoom = D_801BEBB8.curRoom;
            D_801BEBB8.curRoom = nextRoom;
            D_801BEBB8.swapAnimTimer = 20;

            D_801BEBB8.lMapPrevTex = D_801BEBB8.lMapCurTex;
            sp54 = D_801BEBB8.unk8;
            sp50 = D_801BEBB8.unkA;

            nextMinimapEntry = &D_801BEBB8.minimapList->entry[D_801BEBB8.curRoom];

            if (nextMinimapEntry->mapId == 0xFFFF) {
                D_801BEBB8.unk1E = 0;
                D_801BEBB8.unk8 = 0xD2;
                D_801BEBB8.unkA = 0x8C;
                D_801BEBB8.unkC = 0xD2;
                D_801BEBB8.unkE = 0x8C;
                D_801BEBB8.lMapCurTex = NULL;
                D_801BEBB8.unk1C = D_801BEBB8.unk1E;
                return;
            }
            MapDisp_GetMapPos(nextMinimapEntry, &sp44, &sp40);
            MapDisp_GetMapTexDim(nextMinimapEntry, &sp4C, &sp48);
            D_801BEBB8.unk8 = 0x127 - sp4C;
            D_801BEBB8.unkA = 0xDC - sp48;
            if (D_801BEBB8.prevRoom != -1) {
                prevMinimapEntry = &D_801BEBB8.minimapList->entry[D_801BEBB8.prevRoom];
                if (prevMinimapEntry->mapId == 0xFFFF) {
                    D_801BEBB8.unk1E = 0;
                    D_801BEBB8.lMapCurTex = NULL;
                    D_801BEBB8.unk1C = D_801BEBB8.unk1E;
                    D_801BEBB8.unkC = D_801BEBB8.unk8;
                    D_801BEBB8.unkE = D_801BEBB8.unkA;
                    return;
                } else {
                    s32 sp3C;
                    s32 sp38;
                    s32 scale;
                    s32 pad;

                    MapDisp_GetMapPos(prevMinimapEntry, &sp3C, &sp38);
                    scale = D_801BEBB8.minimapList->scale;
                    if (D_801BEBB8.minimapList->scale == 0) {
                        scale = 20;
                    } else if (D_801BEBB8.minimapList->scale == -1) {
                        s32 scaleTemp;

                        MapDisp_GetMapScale(nextMinimapEntry, &scaleTemp);
                        scale = scaleTemp;
                    }
                    D_801BEBB8.unk1C =
                        (s16)(s32)(((f32)sp44 +
                                    (((f32)prevMinimapEntry->unk2 - (f32)nextMinimapEntry->unk2) * (1.0f / scale))) -
                                   (f32)sp3C);
                    D_801BEBB8.unk1E =
                        (s16)(s32)(((f32)sp40 +
                                    (((f32)prevMinimapEntry->unk6 - (f32)nextMinimapEntry->unk6) * (1.0f / scale))) -
                                   (f32)sp38);
                    D_801BEBB8.unkC = sp54 - D_801BEBB8.unk1C;
                    D_801BEBB8.unkE = sp50 - D_801BEBB8.unk1E;
                }
            } else {
                D_801BEBB8.unk1C = D_801BEBB8.unk1E = 0;
                D_801BEBB8.unkC = D_801BEBB8.unk8;
                D_801BEBB8.unkE = D_801BEBB8.unkA;
            }
            D_801BEBB8.lMapCurTex = NULL;

            switch (MapData_MID_GetType(nextMinimapEntry->mapId)) {
                case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
                    D_801BEBB8.lMapCurTex = MapData_GetMapTexGameplayDangeonKeep(nextMinimapEntry->mapId);
                    return;

                case MAPDATA_MID_MAP_GRAND_STATIC:
                    if (D_801BEBB8.lMapPrevTex == D_801BEBB8.texBuff0) {
                        D_801BEBB8.lMapCurTex = D_801BEBB8.texBuff1;
                    } else {
                        D_801BEBB8.lMapCurTex = D_801BEBB8.texBuff0;
                    }
                    if (MapData_GetSizeOfMapGrandTex(nextMinimapEntry->mapId) != 0) {
                        CmpDma_LoadFile(SEGMENT_ROM_START(map_grand_static), nextMinimapEntry->mapId - 0x100,
                                        D_801BEBB8.lMapCurTex, MapData_GetSizeOfMapGrandTex(nextMinimapEntry->mapId));
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

#ifdef NON_MATCHING
// https://decomp.me/scratch/WiRnZ
void func_80105FE0(PlayState* play, s32 x, s32 z, s32 rot) {
    MinimapEntry* sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 var_v0;

    sp6C = &D_801BEBB8.minimapList->entry[D_801BEBB8.curRoom];
    if (sp6C->mapId != 0xFFFF) {
        f32 sp4C;
        MapDisp_GetMapPos(sp6C, &sp60, &sp5C);
        MapDisp_GetMapTexDim(sp6C, &sp58, &sp54);
        var_v0 = D_801BEBB8.minimapList->scale;
        if (D_801BEBB8.minimapList->scale == 0) {
            var_v0 = 20;
        } else if (D_801BEBB8.minimapList->scale == -1) {
            s32 sp48;

            MapDisp_GetMapScale(sp6C, &sp48);
            var_v0 = sp48;
        }
        sp4C = (1.0f / var_v0);
        if (!MapDisp_IsDataRotated(play)) {
            sp68 = (s32)((x - (f32)sp6C->unk2) * sp4C) + D_801BEBB8.unk8 + (D_801BEBB8.unkC - D_801BEBB8.unk8) + sp60;
            sp64 = (s32)((z - (f32)sp6C->unk6) * sp4C) + D_801BEBB8.unkA + (D_801BEBB8.unkE - D_801BEBB8.unkA) + sp5C;
        } else {
            sp68 = -(s32)((x - (f32)sp6C->unk2) * sp4C) + D_801BEBB8.unk8 + (D_801BEBB8.unkC - D_801BEBB8.unk8) + sp60;
            sp64 = -(s32)((z - (f32)sp6C->unk6) * sp4C) + D_801BEBB8.unkA + (D_801BEBB8.unkE - D_801BEBB8.unkA) + sp5C;
        }
        if ((sp68 > 0) && (sp68 < 0x3FF) && (sp64 > 0) && (sp64 < 0x3FF)) {
            OPEN_DISPS(play->state.gfxCtx);

            Gfx_SetupDL42_Overlay(play->state.gfxCtx);
            gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
            Matrix_Translate((f32)sp68 - 160.0f, 120.0f - (f32)sp64, 0.0f, MTXMODE_NEW);
            Matrix_RotateXFApply(-1.6f);
            if (MapDisp_IsDataRotated(play)) {
                rot += 0x7FFF;
            }
            Matrix_RotateYF(rot / 10.0f, MTXMODE_APPLY);
            Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0xFF, 200, 0, 0, play->interfaceCtx.minimapAlpha);
            gSPDisplayList(OVERLAY_DISP++, D_0401ED00);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
#else
void func_80105FE0(PlayState* play, s32 x, s32 z, s32 rot);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105FE0.s")
#endif

s32 func_80106408(PlayState* play) {
    if ((gSaveContext.save.entrance == 0x6400) && (Cutscene_GetSceneLayer(play) != 0)) {
        return true;
    }
    return false;
}

s32 func_80106450(PlayState* play) {
    if (((func_8010A0A4(play) == 0) && (Inventory_IsMapVisible(play->sceneId) != 0)) ||
        ((func_8010A0A4(play) != 0) && CHECK_DUNGEON_ITEM(DUNGEON_MAP, gSaveContext.mapIndex))) {
        return true;
    }
    return false;
}

s32 func_801064CC(PlayState* play) {
    if (((play->csCtx.state != CS_STATE_IDLE) && !func_80106408(play)) || (D_801BEBB8.unk20 & 2) ||
        Map_IsInBossArea(play)) {
        return true;
    }
    return false;
}

s32 func_80106530(PlayState* play) {
    if ((func_801064CC(play) == true) || !func_80106450(play)) {
        return true;
    }
    return false;
}

s32 func_8010657C(s32 curRoom, s32 prevRoom) {
    MinimapEntry* entry;
    s16* temp1; // Can be removed, but adds readability

    if ((curRoom == -1) || (prevRoom == -1)) {
        return 0;
    }
    entry = &D_801BEBB8.minimapList->entry[curRoom];
    temp1 = D_801BEBB8.unk3C;
    if ((temp1[curRoom] <= temp1[prevRoom]) && (temp1[prevRoom] <= (temp1[curRoom] + ((entry->unk8 >> 2) & 7)))) {
        return 1;
    }
    entry = &D_801BEBB8.minimapList->entry[prevRoom];
    if ((temp1[prevRoom] <= temp1[curRoom]) && (temp1[curRoom] <= (temp1[prevRoom] + ((entry->unk8 >> 2) & 7)))) {
        return 1;
    }
    return 0;
}

void func_80106644(PlayState* play, s32 x, s32 z, s32 rot) {
    PauseContext* pauseCtx = &play->pauseCtx;

    if ((D_801BEBB8.minimapList != 0) && ((s32)pauseCtx->state < 4) && (XREG(95) == 0) &&
        (play->interfaceCtx.minimapAlpha != 0)) {
        if ((func_801064CC(play) == 0) && (D_801BEC1C != 0)) {
            if (func_80106450(play) != 0) {
                func_801031D0(play, D_801BEBB8.lMapCurTex, D_801BEBB8.unkC, D_801BEBB8.unkE, D_801BEBB8.curRoom,
                              1.0f - (D_801BEBB8.swapAnimTimer * 0.05f));
                if ((D_801BEBB8.curRoom != D_801BEBB8.prevRoom) &&
                    (func_8010657C(D_801BEBB8.curRoom, D_801BEBB8.prevRoom) != 0)) {
                    func_801031D0(play, D_801BEBB8.lMapPrevTex, D_801BEBB8.unkC + D_801BEBB8.unk1C,
                                  D_801BEBB8.unkE + D_801BEBB8.unk1E, D_801BEBB8.prevRoom,
                                  D_801BEBB8.swapAnimTimer * 0.05f);
                }
                func_80104AE8(play);
            }
            if (((func_8010A0A4(play) == 0) || CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, gSaveContext.mapIndex)) &&
                ((func_8010A0A4(play) != 0) || Inventory_IsMapVisible(play->sceneId))) {
                if (play->interfaceCtx.minigameState == MINIGAME_STATE_NONE) {
                    func_80105FE0(play, x, z, rot);
                }
                func_8010439C(play);
            }
        }
    }
}

void MapDisp_ResetIMap(void) {
    s32 i;

    D_801F56B0.rooms = 0;
    for (i = 0; i < 32; i++) {
        D_801F56B0.unk4[i] = 0;
        D_801F56B0.unk84[i] = NULL;
        D_801F56B0.unk104[i] = NULL;
    }

    D_801F56B0.unk184 = 0;
    D_801BEBB8.unk20 &= ~1;
}

void MapDisp_InitMapI(PlayState* play) {
    MapDisp_ResetIMap();
}

void MapDisp_DestroyMapI(PlayState* play) {
    MapDisp_ResetIMap();
}

// alloc pause screen dungeon map
void* func_801068FC(PlayState* play, void* heap) {
    void* heapNext;
    s32 mapId;
    s32 mapCompactId;
    s32 dungeonMapRoomIter;
    s32 var_s2;
    s32 roomIter;
    MinimapEntry* entry;
    s32 var_s3;

    heapNext = heap;
    if ((D_801BEBB8.minimapList == NULL) || (D_801BEC1C == 0)) {
        return heapNext;
    }
    D_801F56B0.rooms = 0;

    // loop for number of rooms
    for (roomIter = 0; roomIter < D_801BEC1C; roomIter++) {
        var_s2 = false;
        entry = &D_801BEBB8.minimapList->entry[roomIter];
        if (entry->mapId == 0xFFFF) {
            continue;
        }
        mapCompactId = MapData_GetMapCompactId(entry->mapId);
        if (mapCompactId == -1) {
            continue;
        }
        for (dungeonMapRoomIter = 0; dungeonMapRoomIter < D_801F56B0.rooms; dungeonMapRoomIter++) {
            if (mapCompactId == D_801F56B0.unk4[dungeonMapRoomIter]) {
                var_s2 = true;
                break;
            }
        }
        if (var_s2 == false) {
            D_801F56B0.unk4[D_801F56B0.rooms] = mapCompactId;
            D_801F56B0.rooms += 1;
        }
    }

    D_801F56B0.unk84[0] = heap;
    for (dungeonMapRoomIter = 0; dungeonMapRoomIter < D_801F56B0.rooms; dungeonMapRoomIter++) {
        mapId = D_801F56B0.unk4[dungeonMapRoomIter];
        MapDisp_GetMapITexture(D_801F56B0.unk84[dungeonMapRoomIter], mapId);
        if (dungeonMapRoomIter + 1 < D_801F56B0.rooms) {
            D_801F56B0.unk84[dungeonMapRoomIter + 1] =
                ALIGN16((intptr_t)D_801F56B0.unk84[dungeonMapRoomIter] + MapData_CPID_GetSizeOfMapTex(mapId));
        } else {
            heapNext = (intptr_t)D_801F56B0.unk84[dungeonMapRoomIter] + MapData_CPID_GetSizeOfMapTex(mapId);
        }
    }
    for (roomIter = 0; roomIter < D_801BEC1C; roomIter++) {
        entry = &D_801BEBB8.minimapList->entry[roomIter];
        if (entry->mapId == 0xFFFF) {
            D_801F56B0.unk104[roomIter] = NULL;
        } else {
            var_s3 = false;
            mapCompactId = MapData_GetMapCompactId(entry->mapId);
            for (dungeonMapRoomIter = 0; dungeonMapRoomIter < D_801F56B0.rooms; dungeonMapRoomIter++) {
                if (mapCompactId == D_801F56B0.unk4[dungeonMapRoomIter]) {
                    var_s3 = true;
                    break;
                }
            }
            if (!var_s3) {
                D_801F56B0.unk104[roomIter] = NULL;
            } else {
                void* dummy = D_801F56B0.unk84[dungeonMapRoomIter]; //! FAKE:

                D_801F56B0.unk104[roomIter] = D_801F56B0.unk84[dungeonMapRoomIter];
            }
        }
    }
    return heapNext;
}

s32 func_80106BEC(s32 arg0, f32 arg1) {
    if (arg0 == 0) {
        if ((D_801BEBB8.unk48[0] <= arg1) && ((D_801BEBB8.unk40 == 1) || (arg1 < D_801BEBB8.unk48[1]))) {
            return 1;
        }
    } else if (arg0 >= (D_801BEBB8.unk40 - 1)) {
        if (D_801BEBB8.unk48[D_801BEBB8.unk40 - 1] <= arg1) {
            return 1;
        }
    } else if ((D_801BEBB8.unk48[arg0] <= arg1) && (arg1 < D_801BEBB8.unk48[arg0 + 1])) {
        return 1;
    }
    return 0;
}

s32 func_80106D08(s32 sceneId) {
    switch (sceneId) {
        case SCENE_MITURIN_BS:
            return SCENE_MITURIN;

        case SCENE_HAKUGIN_BS:
            return SCENE_HAKUGIN;

        case SCENE_SEA_BS:
            return SCENE_SEA;

        case SCENE_INISIE_BS:
            return SCENE_INISIE_N;

        default:
            return sceneId;
    }
}

#define COLOR16(r, g, b, a)                                                          \
    (s16)(((s32)(((r)*31.0f) / 255.0f) << 11) | ((s32)(((g)*31.0f) / 255.0f) << 6) | \
          ((s32)(((b)*31.0f) / 255.0f) << 1) | (a))

#ifdef NON_MATCHING
// https://decomp.me/scratch/3cGkW
void func_80106D5C(PlayState* play, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    PauseContext* pauseCtx = &play->pauseCtx;
    // s32 var_a0;
    s32 var_a1_2;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_v1;
    s32 var_s2;
    TexturePtr temp_s1;
    s32 temp1;
    s32 temp2;

    temp1 = ((D_801F56B0.unk184 * -120.0f / 40.0f) + 200.0f) * 31.0f / 255.0f;
    temp2 = ((D_801F56B0.unk184 * 115.0f / 40.0f) + 140.0f) * 31.0f / 255.0f;

    D_801BECC4[1] = (temp1 << 6) | (temp2 << 1) | 1;
    if (CHECK_DUNGEON_ITEM(DUNGEON_MAP, arg6)) {
        D_801BEC84[0xF] = 0xAD5F;
        D_801BECA4[0xF] = 0xAD5F;
        D_801BECC4[0xF] = 0xAD5F;
    } else {
        D_801BEC84[0xF] = 0;
        D_801BECA4[0xF] = 0;
        D_801BECC4[0xF] = 0;
    }

    OPEN_DISPS(play->state.gfxCtx);

    // temp_a0 = play->state.gfxCtx;
    // sp48 = arg6 + &gSaveContext;
    Gfx_SetupDL39_Opa(play->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 0, D_801BEC84);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 1, D_801BECA4);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 2, D_801BECC4);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);

    for (var_s2 = 0; var_s2 < D_801BEC1C; var_s2++) {
        s32 sp118_texWidth;
        s32 sp114_texHeight;
        s32 sp110_offsetX;
        s32 sp10C_offsetY;
        MinimapEntry* sp108;
        s32 pad104;
        s32 sp100;
        s32 spFC;
        s32 spF8;
        s32 spF4;
        s32 spF0;
        s32 spEC;
        s32 spE8;
        s32 padE4;
        s32 padE0;

        sp108 = &D_801BEBB8.minimapList->entry[var_s2];
        if ((sp108->mapId != 0xFFFF) && (sp108->mapId < 0x162)) {
            if ((D_801BEBB8.unk42 >= D_801BEBB8.unk3C[var_s2]) &&
                ((D_801BEBB8.unk3C[var_s2] + ((sp108->unk8 >> 2) & 7)) >= D_801BEBB8.unk42)) {
                temp_s1 = D_801F56B0.unk104[var_s2];
                if (temp_s1 != NULL) {
                    spE8 = MapData_GetMapCompactId(sp108->mapId);
                    if (spE8 == -1) {
                        continue;
                    } else {
                        // sp3C = play + 0x18000;
                        MapData_CPID_GetTexDim(spE8, &sp118_texWidth, &sp114_texHeight);
                        MapData_CPID_GetTexOffset(spE8, &sp110_offsetX, &sp10C_offsetY);
                        if (sp108->unk8 & 1) {
                            sp110_offsetX = (sp118_texWidth / 2 - sp110_offsetX) + sp118_texWidth / 2;
                            sp100 = (sp118_texWidth - 1) << 5;
                            spF8 = 0xFC00;
                        } else {
                            sp100 = 0;
                            spF8 = 0x400;
                        }
                        if (sp108->unk8 & 2) {
                            sp10C_offsetY = (sp114_texHeight / 2 - sp10C_offsetY) + sp114_texHeight / 2;
                            spFC = (sp114_texHeight - 1) << 5;
                            spF4 = 0xFC00;
                        } else {
                            spFC = 0;
                            spF4 = 0x400;
                        }
                        spF0 = ((sp108->unk2 - (f32)D_801BEBB8.sceneMidX) * arg5 - sp110_offsetX) + ((arg3 / 2) + arg1);
                        spEC = ((sp108->unk6 - (f32)D_801BEBB8.sceneMidZ) * arg5 - sp10C_offsetY) + ((arg4 / 2) + arg2);

                        if (var_s2 == play->roomCtx.curRoom.num) {
                            if (Map_IsInBossArea(play)) {
                                gDPLoadTextureBlock_4b(POLY_OPA_DISP++, temp_s1, G_IM_FMT_CI, sp118_texWidth,
                                                       sp114_texHeight, 1, G_TX_NOMIRROR | G_TX_WRAP,
                                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                       G_TX_NOLOD);
                            } else {
                                gDPLoadTextureBlock_4b(POLY_OPA_DISP++, temp_s1, G_IM_FMT_CI, sp118_texWidth,
                                                       sp114_texHeight, 2, G_TX_NOMIRROR | G_TX_WRAP,
                                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                       G_TX_NOLOD);
                            }
                        } else if (gSaveContext.save.saveInfo
                                       .permanentSceneFlags[Play_GetOriginalSceneId(func_80106D08(play->sceneId))]
                                       .rooms &
                                   (1 << var_s2)) {
                            gDPLoadTextureBlock_4b(POLY_OPA_DISP++, temp_s1, G_IM_FMT_CI, sp118_texWidth,
                                                   sp114_texHeight, 1, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                        } else if (CHECK_DUNGEON_ITEM(
                                       DUNGEON_MAP,
                                       arg6)) { //*(gBitFlags + 8) & gSaveContext.save.inventory.dungeonItems[arg6]) {
                            gDPLoadTextureBlock_4b(POLY_OPA_DISP++, temp_s1, G_IM_FMT_CI, sp118_texWidth,
                                                   sp114_texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                        } else {
                            continue;
                        }
                        gSPTextureRectangle(POLY_OPA_DISP++, (spF0 << 2), (spEC << 2), (spF0 + sp118_texWidth) << 2,
                                            (spEC + sp114_texHeight) << 2, 0, sp100, spFC, spF8, spF4);
                        gDPPipeSync(POLY_OPA_DISP++);
                    }
                }
            }
        }
    }
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    CLOSE_DISPS(play->state.gfxCtx);
}
#else
void func_80106D5C(PlayState*, s32, s32, s32, s32, f32, s32);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106D5C.s")
#endif

#ifdef NON_MATCHING
// https://decomp.me/scratch/dKnQx
void func_80107B78(PlayState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    s32 sp3C;
    MinimapEntry* sp38;
    GraphicsContext* temp_s1;
    MinimapChest* var_s0;
    s32 temp_ft0;
    s32 temp_ft0_2;
    s32 var_s3;
    s32 var_v1;
    s32 var_v1_2;

    // temp_t0 = ;
    if (D_801BEBB8.unk54 != NULL) {
        // temp_s1 = arg0->state.gfxCtx;
        OPEN_DISPS(arg0->state.gfxCtx);

        // temp_v1 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1 + 8;
        // temp_v1->words.w1 = 0x00000000;
        // temp_v1->words.w0 = 0xE7000000;

        // temp_v1_2 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_2 + 8;
        // temp_v1_2->words.w1 = 0x00000000;
        // temp_v1_2->words.w0 = 0xE3001001;

        // temp_v1_3 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_3 + 8;
        // temp_v1_3->words.w0 = 0xFA000000;
        // temp_v1_3->words.w1 = (arg0->pauseCtx.alpha & 0xFF) | ~0xFF;

        // temp_v1_4 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_4 + 8;
        // temp_v1_4->words.w1 = 0x000000FF;
        // temp_v1_4->words.w0 = 0xFB000000;

        // temp_v1_5 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_5 + 8;
        // temp_v1_5->words.w1 = 0x00000000;
        // temp_v1_5->words.w0 = 0xE7000000;

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, arg0->pauseCtx.alpha);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        gDPPipeSync(POLY_OPA_DISP++);

        // temp_v1_6 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_6 + 8;
        // temp_v1_6->words.w1 = (u32) &D_02003F20;
        // temp_v1_6->words.w0 = ((D_801BEAE0.unk8 & 3) << 0x13) | 0xFD000000;

        // temp_v1_7 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_7 + 8;
        // var_a0 = 0x7FF;
        // temp_v1_7->words.w1 = 0x07000000;
        // temp_v1_7->words.w0 = ((D_801BEAE0.unk8 & 3) << 0x13) | 0xF5000000;

        // temp_v1_8 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_8 + 8;
        // temp_v1_8->words.w1 = 0x00000000;
        // temp_v1_8->words.w0 = 0xE6000000;

        // temp_a1 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_a1 + 8;
        // temp_a1->words.w0 = 0xF3000000;
        // temp_v0 = ((u32) (D_801BEAF8 + 0x40) >> D_801BEB08) - 1;
        // if (temp_v0 < 0x7FFU) {
        //     var_a0 = temp_v0;
        // }
        // temp_v1_9 = (u32) (D_801BEB18 * 8) >> 3;
        // var_a2 = temp_v1_9;
        // if (temp_v1_9 == 0) {
        //     var_a2 = 1;
        // }
        // if (temp_v1_9 == 0) {
        //     var_v0 = 1;
        // } else {
        //     var_v0 = temp_v1_9;
        // }
        // temp_a1->words.w1 = (((u32) (var_a2 + 0x7FF) / var_v0) & 0xFFF) | 0x07000000U | ((var_a0 & 0xFFF) << 0xC);

        // temp_v1_10 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_10 + 8;
        // temp_v1_10->words.w1 = 0x00000000;
        // temp_v1_10->words.w0 = 0xE7000000;

        // temp_v1_11 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_11 + 8;
        // temp_v1_11->words.w0 = ((((u32) ((D_801BEB28 * 8) + 7) >> 3) & 0x1FF) << 9) | 0xF5000000 | ((D_801BEAD8 & 3)
        // << 0x13); temp_v1_11->words.w1 = 0x00000000;

        // temp_v1_12 = temp_s1->polyOpa.p;
        // temp_s1->polyOpa.p = temp_v1_12 + 8;
        // temp_v1_12->words.w0 = 0xF2000000;
        // temp_v1_12->words.w1 = 0x0001C01C;

        // gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 1, 0x02003F20);
        // gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR |
        // G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        // gDPLoadSync(POLY_OPA_DISP++);
        // gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 0, 0);
        // gDPPipeSync(POLY_OPA_DISP++);
        // gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR |
        // G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        // gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x001C, 0x001C);

        gDPLoadTextureBlock_TEST(OVERLAY_DISP++, &D_02003F20, G_IM_FMT_RGBA, D_801BEAE0[2], D_801BEAF0[2],
                                 D_801BEB00[2], D_801BEB10[2], D_801BEB20[2], D_801BEAD0[2], 8, 8, 0,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                 G_TX_NOLOD, G_TX_NOLOD);

        var_s3 = 0;
        var_s0 = D_801BEBB8.unk54;
        // if (D_801BEBB8.numChests > 0) {
        for (var_s3 = 0; var_s3 < D_801BEBB8.numChests; var_s3++) {
            sp3C = var_s0[var_s3].unk0;
            sp38 = &D_801BEBB8.minimapList->entry[sp3C];
            switch (arg0->sceneId) {
                case SCENE_MITURIN_BS:
                    var_v1_2 = gSaveContext.cycleSceneFlags[SCENE_MITURIN].chest & (1 << var_s0[var_s3].unk2);
                    break;

                case SCENE_HAKUGIN_BS:
                    var_v1_2 = gSaveContext.cycleSceneFlags[SCENE_HAKUGIN].chest & (1 << var_s0[var_s3].unk2);
                    break;

                case SCENE_SEA_BS:
                    var_v1_2 = gSaveContext.cycleSceneFlags[SCENE_SEA].chest & (1 << var_s0[var_s3].unk2);
                    break;

                case SCENE_INISIE_BS:
                    var_v1_2 = gSaveContext.cycleSceneFlags[SCENE_INISIE_N].chest & (1 << var_s0[var_s3].unk2);
                    break;

                default:
                    var_v1_2 = Flags_GetTreasure(arg0, (s32)var_s0[var_s3].unk2);
                    break;
            }
            if ((D_801BEBB8.unk42 < D_801BEBB8.unk3C[sp3C]) ||
                ((D_801BEBB8.unk3C[sp3C] + ((sp38->unk8 >> 2) & 7)) < (s32)D_801BEBB8.unk42) || (var_v1_2 != 0)) {
                continue;
            } else if (func_80106BEC((s32)D_801BEBB8.unk42, (f32)var_s0[var_s3].unk6) == 0) {
                continue;
            } else {
                temp_ft0 = (s32)(((((f32)var_s0[var_s3].unk4 - (f32)D_801BEBB8.sceneMidX) * arg5) - (f32)4) +
                                 (f32)((arg3 / 2) + arg1));
                temp_ft0_2 = (s32)(((((f32)var_s0[var_s3].unk8 - (f32)D_801BEBB8.sceneMidZ) * arg5) - (f32)4) +
                                   (f32)((arg4 / 2) + arg2));
                // temp_v1_13 = temp_s1->polyOpa.p;
                // temp_s1->polyOpa.p = temp_v1_13 + 8;
                // temp_v1_13->words.w1 = (((temp_ft0 * 4) & 0xFFF) << 0xC) | ((temp_ft0_2 * 4) & 0xFFF);
                // temp_v1_13->words.w0 = ((((temp_ft0 + 8) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((temp_ft0_2 + 8) * 4)
                // & 0xFFF); temp_v1_14 = temp_s1->polyOpa.p; temp_s1->polyOpa.p = temp_v1_14 + 8; temp_v1_14->words.w1
                // = 0; temp_v1_14->words.w0 = 0xE1000000; temp_v1_15 = temp_s1->polyOpa.p; temp_s1->polyOpa.p =
                // temp_v1_15 + 8; temp_v1_15->words.w1 = 0x04000400; temp_v1_15->words.w0 = 0xF1000000;

                gSPTextureRectangle(POLY_OPA_DISP++, temp_ft0 << 2, temp_ft0_2 << 2, (temp_ft0 + 8) << 2,
                                    (temp_ft0_2 + 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            }
        }

        CLOSE_DISPS(arg0->state.gfxCtx);
    }
}
#else
void func_80107B78(PlayState*, s32, s32, s32, s32, f32);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80107B78.s")
#endif

void func_80108124(PlayState* play, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    PauseContext* pauseCtx = &play->pauseCtx;
    TransitionActorList* transitionActors = &D_801BEC24;
    TransitionActorEntry* var_s1;
    s32 tempX;
    s32 tempY;
    s32 i;
    s8 roomA;
    s8 roomB;

    if (transitionActors->count != 0) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, &D_801BEB38, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        for (i = 0; i < transitionActors->count; i++) {
            if (func_80106BEC(D_801BEBB8.unk42, D_801F53B0[i].pos.y)) {
                if ((ABS_ALT(D_801F53B0[i].id) != ACTOR_EN_HOLL) && (func_80105328(D_801F53B0[i].params) == 0)) {
                    roomA = D_801F53B0[i].sides[0].room;
                    roomB = D_801F53B0[i].sides[1].room;
                    if (CHECK_DUNGEON_ITEM(DUNGEON_MAP, gSaveContext.mapIndex) || (roomA < 0) ||
                        (gSaveContext.save.saveInfo
                             .permanentSceneFlags[Play_GetOriginalSceneId(func_80106D08(play->sceneId))]
                             .rooms &
                         (1 << roomA)) ||
                        (roomB < 0) ||
                        (gSaveContext.save.saveInfo
                             .permanentSceneFlags[Play_GetOriginalSceneId(func_80106D08(play->sceneId))]
                             .rooms &
                         (1 << roomB))) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

                        tempX = ((f32)D_801F53B0[i].pos.x - D_801BEBB8.sceneMidX) * arg5 + ((arg3 / 2) + arg1);
                        tempY = ((f32)D_801F53B0[i].pos.z - D_801BEBB8.sceneMidZ) * arg5 + ((arg4 / 2) + arg2);
                        gSPTextureRectangle(POLY_OPA_DISP++, ((tempX - 1) << 2), ((tempY - 1) << 2), ((tempX + 1) << 2),
                                            ((tempY + 1) << 2), G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                    }
                }
            }
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

#ifdef NON_MATCHING
// https://decomp.me/scratch/nHYgx
void func_80108558(PlayState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    TransitionActorList* sp30;
    // TransitionActorEntry* var_s0;
    s32 temp_ft0;
    s32 temp_ft0_2;
    s32 var_s2;

    sp30 = &D_801BEC24;
    OPEN_DISPS(arg0->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, arg0->pauseCtx.alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gDPPipeSync(POLY_OPA_DISP++);
    if (CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, arg6)) {
        gDPLoadTextureBlock_TEST(POLY_OPA_DISP++, &D_02002460, G_IM_FMT_IA, D_801BEAE0[1], D_801BEAF0[1], D_801BEB00[1],
                                 D_801BEB10[1], D_801BEB20[1], D_801BEAD0[1], 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                 G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        for (var_s2 = 0; var_s2 < sp30->count; var_s2++) {
            if ((func_80105328((s32)D_801F53B0[var_s2].params) != 0) &&
                (func_80106BEC((s32)D_801BEBB8.unk42, (f32)D_801F53B0[var_s2].pos.y) != 0)) {
                if (ABS_ALT(D_801F53B0[var_s2].id) != ACTOR_EN_HOLL) {
                    temp_ft0 =
                        ((((f32)D_801F53B0[var_s2].pos.x - D_801BEBB8.sceneMidX) * arg5) - 4) + ((arg3 / 2) + arg1);
                    temp_ft0_2 =
                        ((((f32)D_801F53B0[var_s2].pos.z - D_801BEBB8.sceneMidZ) * arg5) - 4) + ((arg4 / 2) + arg2);
                    gSPTextureRectangle(POLY_OPA_DISP++, temp_ft0 << 2, temp_ft0_2 << 2, (temp_ft0 + 8) << 2,
                                        (temp_ft0_2 + 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                }
            }
        }
    }

    CLOSE_DISPS(arg0->state.gfxCtx);
}
#else
void func_80108558(PlayState*, s32, s32, s32, s32, f32, s32);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108558.s")
#endif

TexturePtr func_80108A10(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 8)) {
        return D_801BECE4[arg0];
    }
    if ((arg0 >= -8) && (arg0 < 0)) {
        return D_801BED00[-arg0];
    }
    return &D_0C000000;
}

s32 func_80108A64(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    if (pauseCtx->pageIndex != PAUSE_MAP) {
        return 1;
    }
    if ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) || IS_PAUSE_STATE_GAMEOVER) {
        return 1;
    }
    if ((pauseCtx->state != PAUSE_STATE_MAIN) || (pauseCtx->mainState != PAUSE_MAIN_STATE_IDLE)) {
        return 1;
    }
    if (pauseCtx->alpha == 0) {
        return 1;
    }
    return 0;
}

void func_80108AF8(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s32 temp_a0_2;
    s32 temp_a2_2;
    s16 a3;
    s16 a2;
    s32 pad;
    s32 var_s1;
    s32 spB4 = 0;

    if ((D_801BEBB8.minimapList != NULL) && (D_801BEC1C != 0) && (func_80108A64(play) == 0)) {
        if (Map_IsInBossArea(play)) {
            switch (play->sceneId) {
                case SCENE_MITURIN_BS:
                    spB4 = 0;
                    break;

                case SCENE_HAKUGIN_BS:
                    spB4 = 1;
                    break;

                case SCENE_SEA_BS:
                    spB4 = 2;
                    break;

                case SCENE_INISIE_BS:
                    spB4 = 3;
                    break;

                default:
                    break;
            }
        } else {
            spB4 = gSaveContext.mapIndex;
        }
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL39_Opa(play->state.gfxCtx);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 200, pauseCtx->alpha);

        for (var_s1 = 0; var_s1 < D_801BEBB8.unk40; var_s1++) {
            if ((gSaveContext.save.saveInfo.permanentSceneFlags[Play_GetOriginalSceneId(func_80106D08(play->sceneId))]
                     .unk_14 &
                 gBitFlags[4 - var_s1]) ||
                CHECK_DUNGEON_ITEM2(DUNGEON_MAP, spB4)) {
                gDPLoadTextureBlock(POLY_OPA_DISP++, func_80108A10(D_801BEBB8.unk44 + var_s1), G_IM_FMT_IA, G_IM_SIZ_8b,
                                    24, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                    G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(POLY_OPA_DISP++, 0x0144, (125 - var_s1 * 15) << 2, 0x01A4,
                                    ((125 - var_s1 * 15) + 16) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            }
        }
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 150, 255, pauseCtx->alpha);
        gDPLoadTextureBlock(POLY_OPA_DISP++, func_80108A10((D_801BEBB8.unk44 - pauseCtx->unk_256) + 8), G_IM_FMT_IA,
                            G_IM_SIZ_8b, 24, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        a3 = 80;
        a2 = 106;
        temp_a0_2 = (5 + (pauseCtx->unk_256 * 0xF));
        temp_a2_2 = temp_a0_2 + 0x10;
        if ((pauseCtx->cursorSpecialPos == 0) && (pauseCtx->cursorXIndex[1] == 0)) {
            a2++;
            a3--;
            temp_a2_2 += 4;
            temp_a0_2 -= 4;
            gSPTextureRectangle(POLY_OPA_DISP++, a3 << 2, (temp_a0_2) << 2, a2 << 2, (temp_a2_2) << 2, G_TX_RENDERTILE,
                                0, 0, 0x036E, 0x02AA);
        } else {
            gSPTextureRectangle(POLY_OPA_DISP++, (a3 + 1) << 2, temp_a0_2 << 2, (a2 - 1) << 2, temp_a2_2 << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        }
        Gfx_SetupDL42_Opa(play->state.gfxCtx);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

s32 func_801090B0(s32 arg0) {
    if ((D_801BEBB8.minimapList == NULL) || (D_801BEC1C == 0)) {
        return false;
    }
    if ((arg0 < 0) || (arg0 >= 6)) {
        return false;
    }
    if (D_801BEBB8.unk48[arg0] != -0x7FFF) {
        return true;
    }
    return false;
}

s32 func_80109124(s16 arg0) {
    s32 i;

    if ((D_801BEBB8.minimapList == NULL) || (D_801BEC1C == 0)) {
        return -1;
    }
    if (D_801BEBB8.unk40 < 2) {
        return 0;
    }
    if ((D_801BEBB8.unk48[1] - 5) >= arg0) {
        return 0;
    }
    for (i = 1; i < D_801BEBB8.unk40; i++) {
        if (((D_801BEBB8.unk48[i] - 5) < arg0) && ((D_801BEBB8.unk48[i + 1] - 5) >= arg0)) {
            return i;
        }
    }
    return D_801BEBB8.unk40 - 1;
}

#ifdef NON_MATCHING
void func_801091F0(PlayState* play) {
    s32 var_t2;
    u16 temp_a0;
    s16 sp44;
    s32 sp40;
    s32 sp3C;
    s32 var_v0;
    s32 temp_v0_2;

    sp44 = 0;
    sp40 = 0;
    sp3C = 0;
    if (func_80108A64(play) == 0) {
        if (Map_IsInBossArea(play)) {
            switch (play->sceneId) {
                case SCENE_MITURIN_BS:
                    sp44 = 0;
                    break;

                case SCENE_HAKUGIN_BS:
                    sp44 = 1;
                    break;

                case SCENE_SEA_BS:
                    sp44 = 2;
                    break;

                case SCENE_INISIE_BS:
                    sp44 = 3;
                    break;

                default:
                    break;
            }
        } else {
            sp44 = gSaveContext.mapIndex;
        }
        temp_a0 = D_801BEBB8.minimapList->entry->mapId;
        if ((temp_a0 != 0xFFFF) && (temp_a0 < 0x162)) {
            temp_v0_2 = MapData_GetMapCompactId(temp_a0);
            if (temp_v0_2 != -1) {
                var_t2 = MapData_CPID_GetMapScale(temp_v0_2);
                if (var_t2 == 0) {
                    var_t2 = 0x50;
                }
                for (var_v0 = 0; var_v0 < 2; var_v0++) {
                    if (play->sceneId == D_801BED24[var_v0].unk0) {
                        sp40 = D_801BED24[var_v0].unk4;
                        sp3C = D_801BED24[var_v0].unk8;
                    }
                }

                func_80106D5C(play, sp40 + 0x90, sp3C + 0x55, 0x78, 0x64, 1.0f / var_t2, sp44);
                func_80108124(play, sp40 + 0x90, sp3C + 0x55, 0x78, 0x64, 1.0f / var_t2, sp44);
                func_80108558(play, sp40 + 0x90, sp3C + 0x55, 0x78, 0x64, 1.0f / var_t2, sp44);
                if (CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, sp44)) {
                    func_80107B78(play, sp40 + 0x90, sp3C + 0x55, 0x78, 0x64, 1.0f / var_t2);
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801091F0.s")
#endif

void func_80109428(PlayState* play) {
    D_801BEBB8.unk4C++;
    if (!(D_801BEBB8.unk20 & 1)) {
        D_801F56B0.unk184++;
        if (D_801F56B0.unk184 > 40) {
            D_801BEBB8.unk20 |= 1;
        }
    } else {
        D_801F56B0.unk184--;
        if (D_801F56B0.unk184 < 0) {
            D_801BEBB8.unk20 &= ~1;
        }
    }
}
