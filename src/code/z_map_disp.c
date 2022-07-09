#include "global.h"
#include "z64map.h"

void func_801031D0(PlayState* play, s32, s32, s32, s32, f32);
void func_80103090(MinimapEntry*, s32*, s32*);
void func_80105FE0(PlayState* play, s32 x, s32 z, s32 rot);
void func_80106644(PlayState* play, s32 x, s32 z, s32 rot);
s32 func_801039EC(PlayState* play);
void func_80103A58(PlayState* play, Actor* actor);

extern T_801BEBB8 D_801BEBB8;
extern s32 D_801BEC1C; //scene rooms
extern T_801BEC5C D_801BEC5C[5];
extern TexturePtr D_801BEB38;

extern MinimapList D_801BEC14;
extern MinimapEntry D_801F5130[0x50];

typedef struct {
    /* 0x00 */ UNK_TYPE1 unk0[8];
    /* 0x08 */ s32 unk8; // G_IM_SIZ
} T_801BEAE0;

extern Gfx D_0401ED00[];
extern T_801BEAE0 D_801BEAE0;

extern s32 D_801BEAF8;
extern s32 D_801BEB08;
extern s32 D_801BEB18;
extern s32 D_801BEB28;
extern s32 D_801BEAD8;
extern Color_RGBA8 D_801BEC2C[]; // cat colors

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102EF0.s")

f32 func_80102F9C(f32);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80102F9C.s")

void func_80103090(MinimapEntry* arg0, s32* out1, s32* out2){
    func_80109754(arg0->unk0, out1, out2);
}

void func_801030B4(MinimapEntry *arg0, s32 *arg1) {
    func_8010983C(arg0->unk0, arg1);
    if (*arg1 == 0) {
        *arg1 = 0x14;
    }
}

void func_801030F4(MinimapEntry* arg0, s32* arg1, s32* arg2) {
    s32 sp2C;
    s32 sp28;
    s32 temp_v0;
    s32 temp_v0_2;

    if (arg0->unk0 == 0xFFFF) {
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    func_80103090(arg0, &sp2C, &sp28);
    func_801097C8(arg0->unk0, arg1, arg2);
    if (arg0->unk8 & 1) {
        temp_v0 = sp2C / 2;
        *arg1 = (temp_v0 - *arg1) + temp_v0;
    }
    if (arg0->unk8 & 2) {
        temp_v0_2 = sp28 / 2;
        *arg2 = (temp_v0_2 - *arg2) + temp_v0_2;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801031D0.s")

s32 func_801039EC(PlayState *play) {
    if (play->sceneNum == SCENE_35TAKI) {
        return true;
    }
    return false;
}

s32 func_80103A10(PlayState* play) {
    if ((gSaveContext.save.entranceIndex == 0x6400) && (Cutscene_GetSceneSetupIndex(play) != 0)) {
        return false;
    }
    return true;
}

#ifdef NON_MATCHING
void func_80103A58(PlayState *play, Actor *actor) {
    MinimapEntry *spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    f32 spC0;
    Player *spB4;
    s32 spAC;
    GraphicsContext *spA8;
    s16 spA2;
    //GraphicsContext *temp_a0_2;
    f32 temp_fv0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v1_3;
    s16 var_v0;
    s16 var_v1;
    s32 temp_t3;
    s32 temp_v1_4;
    s32 var_t2;
    s32 var_t8;
    u32 temp_v0_19;
    u32 temp_v1_5;
    u32 var_a0;
    u32 var_a1;
    u32 var_v1_2;
    Color_RGBA8 *temp_v1_6;
    
    spB4 = GET_PLAYER(play); //play->actorCtx.actorLists[2].first;
    spDC = &D_801BEBB8.unk0->entry[D_801BEBB8.unk4];//->unk0 + ( * 0xA);
    if (spDC->unk0 != 0xFFFF) {
        //spDC = temp_a0;
        func_801030F4(spDC, &spD0, &spCC);
        func_80103090(spDC, &spC8, &spC4);
        temp_v1 = D_801BEBB8.unk0->unk4;
        var_v0 = temp_v1;
        if (temp_v1 == 0) {
            var_v0 = 0x14;
        } else if (temp_v1 == -1) {
            func_801030B4(spDC, &spAC);
            var_v0 = (s16) spAC;
        }
        temp_fv0 = 1.0f / (f32) var_v0;
        spC0 = temp_fv0;
        if (func_801039EC(play) == 0) {
            spD8 = (((s32) ((actor->world.pos.x - (f32) spDC->unk2) * temp_fv0) + D_801BEBB8.unk8 + D_801BEBB8.unkC) - D_801BEBB8.unk8) + spD0;
            var_t8 = ((s32) ((actor->world.pos.z - (f32) spDC->unk6) * temp_fv0) + D_801BEBB8.unkA + D_801BEBB8.unkE) - D_801BEBB8.unkA;
        } else {
            spD8 = (((D_801BEBB8.unk8 - (s32) ((actor->world.pos.x - (f32) spDC->unk2) * temp_fv0)) + D_801BEBB8.unkC) - D_801BEBB8.unk8) + spD0;
            var_t8 = ((D_801BEBB8.unkA - (s32) ((actor->world.pos.z - (f32) spDC->unk6) * temp_fv0)) + D_801BEBB8.unkE) - D_801BEBB8.unkA;
        }
        spD4 = var_t8 + spCC;
        if ((spD8 > 0) && (spD8 < 0x3FF) && (spD4 > 0) && (spD4 < 0x3FF)) {
            //temp_a0_2 = play->state.gfxCtx;
            OPEN_DISPS(play->state.gfxCtx);
            if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & 0x80000000)) {
                //spA8 = temp_a0_2;
                func_8012C8D4(play->state.gfxCtx); //temp_a0_2);
                // temp_v0_3 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_3 + 8;
                // temp_v0_3->words.w0 = 0xDA380003;
                // temp_v0_3->words.w1 = (u32) &gIdentityMtx;
                // temp_v0_4 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_4 + 8;
                // temp_v0_4->words.w0 = 0xFC309661;
                // temp_v0_4->words.w1 = 0x552EFF7F;
                // temp_v0_5 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_5 + 8;
                // temp_v0_5->words.w0 = 0xFB000000;
                // temp_v0_5->words.w1 = play->interfaceCtx.minimapAlpha & 0xFF;
                // temp_v0_6 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_6 + 8;
                // temp_v0_6->words.w1 = 0xFFFDF6FB;
                // temp_v0_6->words.w0 = 0xFCFFFFFF;
                // temp_v0_7 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_7 + 8;
                // temp_v0_7->words.w0 = 0xE200001C;
                // temp_v0_7->words.w1 = 0x00407248;

                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
                gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

                //sp1C = play + 0x10000;
                //spA8 = spA8;
                Matrix_Translate((f32) spD8 - 160.0f, 120.0f - (f32) spD4, 0.0f, MTXMODE_NEW);
                Matrix_RotateXFApply(-1.6f);
                temp_v1_4 = (s32) (0x7FFF - actor->focus.rot.y) / 1024;
                spA2 = (s16) temp_v1_4;
                var_v1 = (s16) temp_v1_4;
                if (func_801039EC(play) != 0) {
                    var_v1 += 0x7FFF;
                }
                // spA8 = spA8;
                Matrix_RotateYF((f32) var_v1 / 10.0f, MTXMODE_APPLY);
                Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
                // temp_v0_8 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_8 + 8;
                // temp_v0_8->words.w0 = 0xDA380003;
                // spA8 = spA8;
                // sp88 = temp_v0_8;
                // sp88->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                // temp_v0_9 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_9 + 8;
                // temp_v0_9->words.w0 = 0xFA000000;
                // temp_v0_9->words.w1 = ((u8)play->interfaceCtx.minimapAlpha) | 0xC8FF0000;
                // temp_v0_10 = spA8->overlay.p;
                // spA8->overlay.p = temp_v0_10 + 8;
                // temp_v0_10->words.w1 = (u32) &D_0401ED00;
                // temp_v0_10->words.w0 = 0xDE000000;
                gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0xC8, 0xFF, 0x00, 0x00);
                gSPDisplayList(OVERLAY_DISP++, &D_0401ED00);
                return;
            }
            if (actor->id == ACTOR_EN_BOX) {
                //spD4 = spD4;
                //spD8 = spD8;
                //spA8 = temp_a0_2; = play->state.gfxCtx;
                if (Flags_GetTreasure(play, actor->params & 0x1F) == 0) {
                    //spD4 = spD4;
                    //spD8 = spD8;
                    //spA8 = temp_a0_2;
                    //sp2C = ;
                    if (func_80102F9C(spB4->actor.world.pos.y) == func_80102F9C(actor->world.pos.y)) {
                        //spD4 = spD4;
                        //spD8 = spD8;
                        //spA8 = temp_a0_2;
                        func_8012C654(play->state.gfxCtx);
                        // temp_v0_11 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_11 + 8;
                        // temp_v0_11->words.w1 = 0x00000000;
                        // temp_v0_11->words.w0 = 0xE7000000;
                        // temp_v0_12 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_12 + 8;
                        // temp_v0_12->words.w1 = 0x00000000;
                        // temp_v0_12->words.w0 = 0xE3001001;
                        // temp_v0_13 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_13 + 8;
                        // temp_v0_13->words.w0 = 0xFA000000;
                        // temp_v0_13->words.w1 = (play->interfaceCtx.minimapAlpha & 0xFF) | ~0xFF;
                        // temp_v0_14 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_14 + 8;
                        // temp_v0_14->words.w0 = 0xFB000000;
                        // temp_v0_14->words.w1 = play->interfaceCtx.minimapAlpha & 0xFF;
                        // temp_v0_15 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_15 + 8;
                        // temp_v0_15->words.w1 = 0x00000000;
                        // temp_v0_15->words.w0 = 0xE7000000;
                        // temp_v0_16 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_16 + 8;
                        // //gsDPSetTextureImage(G_IM_FMT_RGBA, (D_801BEAE0.unk8 & 3), 1, 0x02003F20)
                        // temp_v0_16->words.w0 = ((D_801BEAE0.unk8 & 3) << 0x13) | 0xFD000000;
                        // temp_v0_16->words.w1 = (u32) &D_02003F20;
                        // temp_v0_17 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_17 + 8;
                        // temp_v0_17->words.w1 = 0x07000000;
                        // temp_v0_17->words.w0 = ((D_801BEAE0.unk8 & 3) << 0x13) | 0xF5000000;
                        // //gsDPSetTile(G_IM_FMT_RGBA, (D_801BEAE0.unk8 & 3), 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD)
                        // temp_v0_18 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_18 + 8;
                        // temp_v0_18->words.w1 = 0x00000000;
                        // temp_v0_18->words.w0 = 0xE6000000;
                        // temp_a2 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_a2 + 8;
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
                        gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_RGBA, (D_801BEAE0.unk8 & 3), 1, 0x02003F20);
                        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_RGBA, (D_801BEAE0.unk8 & 3), 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                        gDPLoadSync(OVERLAY_DISP++);

                        //temp_a2->words.w0 = 0xF3000000;
                        temp_v1_5 = ((u32) (D_801BEAF8 + 0x40) >> D_801BEB08) - 1;
                        var_a0 = 0x7FF;
                        if (temp_v1_5 < 0x7FFU) {
                            var_a0 = temp_v1_5;
                        }
                        temp_v0_19 = (u32) (D_801BEB18 * 8) >> 3;
                        var_a1 = temp_v0_19;
                        if (temp_v0_19 == 0) {
                            var_a1 = 1;
                        }
                        if (temp_v0_19 == 0) {
                            var_v1_2 = 1;
                        } else {
                            var_v1_2 = temp_v0_19;
                        }
                        //temp_a2->words.w1 = (((u32) (var_a1 + 0x7FF) / var_v1_2) & 0xFFF) | 0x07000000U | ((var_a0 & 0xFFF) << 0xC);
                        gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0, var_a0, (u32) (var_a1 + 0x7FF) / var_v1_2);
                        // temp_v0_20 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_20 + 8;
                        // temp_v0_20->words.w1 = 0x00000000;
                        // temp_v0_20->words.w0 = 0xE7000000;
                        gDPPipeSync(OVERLAY_DISP++);

                        // temp_v0_21 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_21 + 8;
                        // temp_v0_21->words.w0 = ((((u32) ((D_801BEB28 * 8) + 7) >> 3) & 0x1FF) << 9) | 0xF5000000 | ((D_801BEAD8 & 3) << 0x13);
                        // temp_v0_21->words.w1 = 0x00000000;
                        
                        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_RGBA, (D_801BEAD8 & 3), ((u32) ((D_801BEB28 * 8) + 7) >> 3), 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
                        // temp_v0_22 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_22 + 8;
                        // temp_v0_22->words.w0 = 0xF2000000;
                        // temp_v0_22->words.w1 = 0x0001C01C;
                        gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 0x001C, 0x001C);
                        // temp_v0_23 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_23 + 8;
                        // temp_v0_23->words.w0 = ((((var_t2 + 4) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((temp_t3 + 4) * 4) & 0xFFF);
                        // temp_v0_23->words.w1 = ((((var_t2 - 4) * 4) & 0xFFF) << 0xC) | (((temp_t3 - 4) * 4) & 0xFFF);
                        // temp_v0_24 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_24 + 8;
                        // temp_v0_24->words.w1 = 0x00000000;
                        // temp_v0_24->words.w0 = 0xE1000000;
                        // temp_v0_25 = temp_a0_2->overlay.p;
                        // temp_a0_2->overlay.p = temp_v0_25 + 8;
                        // temp_v0_25->words.w1 = 0x04000400;
                        // temp_v0_25->words.w0 = 0xF1000000;
                        gSPTextureRectangle(OVERLAY_DISP++, ((spD8 - 4) * 4), ((spD4 - 4) * 4), ((spD8 + 4) * 4), ((spD4 + 4) * 4), G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                        return;
                    }
                }
            }
            spD4 = spD4;
            spD8 = spD8;
            //spA8 = temp_a0_2;
            func_8012C654(play->state.gfxCtx);
            // temp_v0_26 = temp_a0_2->overlay.p;
            // temp_a0_2->overlay.p = temp_v0_26 + 8;
            // temp_v0_26->words.w0 = 0xFC119623;
            // temp_v0_26->words.w1 = 0xFF2FFFFF;
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            if (actor->flags & 0x80000000) {
                // temp_v0_27 = temp_a0_2->overlay.p;
                // temp_a0_2->overlay.p = temp_v0_27 + 8;
                // temp_v0_27->words.w0 = 0xFA000000;
                temp_v1_6 = &D_801BEC2C[actor->category];
                //temp_v0_27->words.w1 = (temp_v1_6->unk2 << 8) | (temp_v1_6->unk0 << 0x18) | (temp_v1_6->unk1 << 0x10) | (play->interfaceCtx.minimapAlpha & 0xFF);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, temp_v1_6->r, temp_v1_6->g, temp_v1_6->b, play->interfaceCtx.minimapAlpha);
                // temp_v0_28 = temp_a0_2->overlay.p;
                // temp_a0_2->overlay.p = temp_v0_28 + 8;
                // temp_v0_28->words.w0 = ((((var_t2 + 1) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((temp_t3 + 1) * 4) & 0xFFF);
                // temp_v0_28->words.w1 = ((((var_t2 - 1) * 4) & 0xFFF) << 0xC) | (((temp_t3 - 1) * 4) & 0xFFF);
                // temp_v0_29 = temp_a0_2->overlay.p;
                // temp_a0_2->overlay.p = temp_v0_29 + 8;
                // temp_v0_29->words.w1 = 0x00000000;
                // temp_v0_29->words.w0 = 0xE1000000;
                // temp_v0_30 = temp_a0_2->overlay.p;
                // temp_a0_2->overlay.p = temp_v0_30 + 8;
                // temp_v0_30->words.w1 = 0x00010001;
                // temp_v0_30->words.w0 = 0xF1000000;
                gSPTextureRectangle(OVERLAY_DISP++, ((spD8 - 1) * 4), ((spD4 - 1) * 4), ((spD8 + 1) * 4), ((spD4 + 1) * 4), G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
            }
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80103A58.s")
#endif

void func_8010439C(PlayState *play) {
    ActorContext *actorCtx;
    s32 i;

    if (play->roomCtx.currRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_801BEB38, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actorCtx = &play->actorCtx;
        for (i = 0; i < ACTORCAT_MAX; i++) {
            Actor *actor = actorCtx->actorLists[i].first;
            if (actor != NULL) {
                do {
                    if (
                        (actor->update != NULL) 
                        && (actor->init == NULL) 
                        && (Object_IsLoaded(&play->objectCtx, actor->objBankIndex))
                        && ((actor->id == ACTOR_EN_BOX) || (i == ACTORCAT_PLAYER) || (actor->flags & ACTOR_FLAG_80000000))
                        && ((D_801BEBB8.unk4 == actor->room) || (actor->room == -1))) {
                        func_80103A58(play, actor);
                    }
                    actor = actor->next;
                } while (actor != NULL);
            }
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

#ifdef NON_MATCHING
void func_801045AC(PlayState* play, Actor* actor) { //4729
    MinimapEntry* sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v0_5;
    f32 sp5C;
    s32 var_v1;
    s32 var_v1_2;
    f32 sp50;
    s32 sp4C;
    //GraphicsContext* sp48;
    
    temp_fv1 = 0.0028571428f * fabsf(play->actorCtx.actorLists[2].first->world.pos.y - actor->world.pos.y);
    sp50 = 1.0f - temp_fv1;
    if (temp_fv1 > 1.0f) {
        sp50 = 0.0f;
    }
    sp7C = &D_801BEBB8.unk0->entry[D_801BEBB8.unk4];
    if (sp7C->unk0 != 0xFFFF) {
        func_801030F4(sp7C, &sp70, &sp6C);
        func_80103090(sp7C, &sp68, &sp64);
        temp_v0 = D_801BEBB8.unk0->unk4;
        var_v1 = temp_v0;
        if (temp_v0 == 0) {
            var_v1 = 0x14;
        } else if (temp_v0 == -1) {
            func_801030B4(sp7C, &sp4C);
            var_v1 = sp4C;
        }
        sp5C = 1.0f / (f32) var_v1;
        if (func_801039EC(play) == 0) {
            sp78 = (((s32) ((actor->world.pos.x - (f32) sp7C->unk2) * sp5C) + D_801BEBB8.unk8 + D_801BEBB8.unkC) - D_801BEBB8.unk8) + sp70;
            sp74 = (((s32) ((actor->world.pos.z - (f32) sp7C->unk6) * sp5C) + D_801BEBB8.unkA + D_801BEBB8.unkE) - D_801BEBB8.unkA) + sp6C;
        } else {
            sp78 = (((D_801BEBB8.unk8 - (s32) ((actor->world.pos.x - (f32) sp7C->unk2) * sp5C)) + D_801BEBB8.unkC) - D_801BEBB8.unk8) + sp70;
            sp74 = (((D_801BEBB8.unkA - (s32) ((actor->world.pos.z - (f32) sp7C->unk6) * sp5C)) + D_801BEBB8.unkE) - D_801BEBB8.unkA) + sp6C;
        }
        if ((sp78 > 0) && (sp78 < 0x3FF) && (sp74 > 0) && (sp74 < 0x3FF) ) {
            OPEN_DISPS(play->state.gfxCtx);
            func_8012C654(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            
            if ((actor->category == 0xA) && (func_80103A10(play) != 0)) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, D_801BEC2C[actor->category].r, D_801BEC2C[actor->category].g, D_801BEC2C[actor->category].b, (s32)((D_801BEC2C[actor->category].a * (1.0f - ((f32) D_801BEBB8.unk24 * 0.05f)) * sp50 * (f32) play->interfaceCtx.minimapAlpha) / 255.0f));
                temp_v0_5 = D_801BEBB8.unk0->unk4;
                var_v1_2 = temp_v0_5;
                if (temp_v0_5 == 0) {
                    var_v1_2 = 0x14;
                } else if (temp_v0_5 == -1) {
                    s32 sp34;
                    func_801030B4(sp7C, &sp34); // sp34 is local temp
                    var_v1_2 = sp34;
                }
                if (var_v1_2 <= 50) {
                    gSPTextureRectangle(OVERLAY_DISP++, (sp78 - 2) * 4, (sp74 - 2) * 4, (sp78 + 2) * 4, (sp74 + 2) * 4, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                } else {
                    gSPTextureRectangle(OVERLAY_DISP++, (sp78 - 1) * 4, (sp74 - 1) * 4, (sp78 + 1) * 4, (sp74 + 1) * 4, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                }
            }
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
#else
void func_801045AC(PlayState* play, Actor* actor);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801045AC.s")
#endif

void func_80104AE8(PlayState *play) {
    s32 i;
    Actor* actor;

    if (play->roomCtx.currRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_801BEB38, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actor = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
        if (actor != NULL) {
            do {
                if (
                    (actor->update != NULL) 
                    && (actor->init == NULL) 
                    && Object_IsLoaded(&play->objectCtx, actor->objBankIndex)
                    && ((D_801BEBB8.unk4 == actor->room) || (actor->room == -1))) {
                    func_801045AC(play, actor);
                }
                actor = actor->next;
            } while (actor != NULL);
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80104C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80104CF4.s")

void func_80104F34(PlayState* arg0) {
    s32 i1;
    s32 i2;
    s32 i3;
    s32 i4;

    for (i1 = 0; i1 < 32; i1++){
        D_801BEBB8.unk48[i1] = -0x7FFF;
    }
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        MinimapEntry* mapEntry1 = &D_801BEBB8.unk0->entry[i2];
        
        if (mapEntry1->unk0 == 0xFFFF) {
            continue;
        }
        for (i1 = 0; i1 < 32; i1++) {
            if (D_801BEBB8.unk48[i1] == -0x7FFF) {
                D_801BEBB8.unk48[i1] = mapEntry1->unk4;
                break;
            } else if(fabsf((f32) D_801BEBB8.unk48[i1] - (f32) mapEntry1->unk4) < 5.0f) {
                break;
            }
        }
    }
    for (i2 = 0; i2 < D_801BEC1C; i2++) {
        if (D_801BEBB8.unk48[i2] == -0x7FFF) {
            break;
        } 
        for (i3 = i2+1; i3 < D_801BEC1C; i3++) {
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
        MinimapEntry* mapEntry2 = &D_801BEBB8.unk0->entry[i2];
        
        D_801BEBB8.unk3C[i2] = -1;

        for (i4 = 0; i4 < D_801BEC1C; i4++) {
            if (D_801BEBB8.unk48[i4] != -0x7FFF) {
                if (fabsf((f32) D_801BEBB8.unk48[i4] - (f32) mapEntry2->unk4) < 5.0f) {
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
        if (arg0->sceneNum == D_801BEC5C[i2].unk0) {
            D_801BEBB8.unk44 = D_801BEC5C[i2].unk2;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105294.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105318.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105328.s")

void func_8010534C(PlayState*);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_8010534C.s")

#ifdef NON_MATCHING
void func_8010549C(PlayState* globalCtx, void* segmentAddress) {
    MinimapEntry* var_v1;
    MinimapList* temp_v0;
    s32 i;

    if (func_8010A208(globalCtx) == 0) {
        D_801BEC1C = globalCtx->numRooms;
        temp_v0 = Lib_SegmentedToVirtual(segmentAddress);
        D_801BEC14 = *temp_v0;
        var_v1 = Lib_SegmentedToVirtual(temp_v0->entry);

        for (i = 0; i < D_801BEC1C; i++)
        {
            D_801F5130[i] = var_v1[i];
        }
        
        D_801BEC14.entry = D_801F5130;
        if (globalCtx->colCtx.colHeader != NULL) {
            D_801BEBB8.unk30 = globalCtx->colCtx.colHeader->minBounds.x;
            D_801BEBB8.unk32 = globalCtx->colCtx.colHeader->minBounds.z;
            D_801BEBB8.unk34 = globalCtx->colCtx.colHeader->maxBounds.x - globalCtx->colCtx.colHeader->minBounds.x;
            D_801BEBB8.unk36 = globalCtx->colCtx.colHeader->maxBounds.z - globalCtx->colCtx.colHeader->minBounds.z;
            D_801BEBB8.unk38 = (s16) (D_801BEBB8.unk30 + (D_801BEBB8.unk34 * 0.5f));
            D_801BEBB8.unk3A = (s16) (D_801BEBB8.unk32 + (D_801BEBB8.unk36 * 0.5f));
        }
    }
    D_801BEBB8.unk0 = &D_801BEC14;
    func_80104F34(globalCtx);
    func_8010534C(globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_8010549C.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_8010565C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105818.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105B34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80105FE0.s")

s32 func_80106408(PlayState* arg0) {
    if ((gSaveContext.save.entranceIndex == 0x6400) && (Cutscene_GetSceneSetupIndex(arg0) != 0)) {
        return true;
    }
    return false;
}

s32 func_80106450(PlayState* play) {
    if (((func_8010A0A4(play) == 0) && (Inventory_IsMapVisible(play->sceneNum) != 0)) 
    || ((func_8010A0A4(play) != 0) && CHECK_DUNGEON_ITEM(2, gSaveContext.mapIndex)  )) {
        return true;
    }
    return false;
}

s32 func_801064CC(PlayState* play) {
    if (((play->csCtx.state != 0) && (func_80106408(play) == 0)) || (D_801BEBB8.unk20 & 2) || (func_8010A208(play) != 0)) {
        return true;
    }
    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106530.s")

s32 func_8010657C(s32 arg0, s32 arg1) {
    MinimapEntry* temp_v1;
    s16* temp1; // Can be removed, but adds readability

    if ((arg0 == -1) || (arg1 == -1)) {
        return 0;
    }
    temp_v1 = &D_801BEBB8.unk0->entry[arg0];
    temp1 = D_801BEBB8.unk3C;
    if ((temp1[arg0] <= temp1[arg1]) && (temp1[arg1] <= (temp1[arg0] + ((temp_v1->unk8 >> 2) & 7)))) {
        return 1;
    } 
    temp_v1 = &D_801BEBB8.unk0->entry[arg1];
    if ((temp1[arg1] <= temp1[arg0]) && (temp1[arg0] <= (temp1[arg1] + ((temp_v1->unk8 >> 2) & 7)) )) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
void func_80106644(PlayState *play, s32 x, s32 z, s32 rot) {
    s32 pad[2];
    
    if ((D_801BEBB8.unk0 != 0) && ((s32) play->pauseCtx.state < 4) && (XREG(95) == 0) && (play->interfaceCtx.minimapAlpha != 0)) {
        //sp2C = ;// + 0x10000;
        if ((func_801064CC(play) == 0) && (D_801BEC1C != 0)) {
            if (func_80106450(play) != 0) {
                func_801031D0(play, D_801BEBB8.unk10, D_801BEBB8.unkC, D_801BEBB8.unkE, D_801BEBB8.unk4, 1.0f - ((f32) D_801BEBB8.unk24 * 0.05f));
                if ((D_801BEBB8.unk4 != D_801BEBB8.unk14) && (func_8010657C(D_801BEBB8.unk4, D_801BEBB8.unk14) != 0)) {
                    func_801031D0(play, D_801BEBB8.unk18, D_801BEBB8.unkC + D_801BEBB8.unk1C, D_801BEBB8.unkE + D_801BEBB8.unk1E, D_801BEBB8.unk14, (f32) D_801BEBB8.unk24 * 0.05f);
                }
                func_80104AE8(play);
            }
            if (((func_8010A0A4(play) == 0) || (gSaveContext.save.inventory.dungeonItems[gSaveContext.mapIndex] & gBitFlags[1]) )
                 && ((func_8010A0A4(play) != 0) || Inventory_IsMapVisible(play->sceneNum))) {
                if (play->interfaceCtx.unk_280 == 0) {
                    func_80105FE0(play, x, z, rot);
                }
                func_8010439C(play);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106644.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_8010683C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801068B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801068D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801068FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80106D5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80107B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108124.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108558.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80108AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801090B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80109124.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_801091F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_map_disp/func_80109428.s")
