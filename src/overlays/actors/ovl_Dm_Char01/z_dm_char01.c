/*
 * File: z_dm_char01.c
 * Overlay: ovl_Dm_Char01
 * Description: Woodfall scene objects (temple, water, walls, etc)
 */

#include "z_dm_char01.h"
#include "objects/object_mtoride/object_mtoride.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((DmChar01*)thisx)

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AA8698(DmChar01* this, GlobalContext* globalCtx);
void func_80AA884C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA88A8(DmChar01* this, GlobalContext* globalCtx);
void func_80AA892C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8C28(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8F1C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8F2C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA9020(DmChar01* this, GlobalContext* globalCtx);
void func_80AA90AC(DmChar01* this, GlobalContext* globalCtx);
void func_80AA90F4(DmChar01* this, GlobalContext* globalCtx);

s16 D_80AAAE20;
s16 D_80AAAE22;
s16 D_80AAAE24;
s16 D_80AAAE26;

#include "overlays/ovl_Dm_Char01/ovl_Dm_Char01.c"

const ActorInit Dm_Char01_InitVars = {
    ACTOR_DM_CHAR01,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MTORIDE,
    sizeof(DmChar01),
    (ActorFunc)DmChar01_Init,
    (ActorFunc)DmChar01_Destroy,
    (ActorFunc)DmChar01_Update,
    (ActorFunc)DmChar01_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

s16 D_80AAAAB4 = false;

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmChar01* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, 1.0f);

    this->unk_346 = 0;
    this->unk_34D = false;
    D_80AAAE24 = 0;
    D_80AAAE26 = 0;

    switch (DMCHAR01_GET(&this->dyna.actor)) {
        case DMCHAR01_0:
            if (gSaveContext.save.weekEventReg[20] & 2) {
                this->unk_34C = 2;
                this->actionFunc = func_80AA8F1C;
                break;
            }

            if (gSaveContext.sceneSetupIndex == 0) {
                globalCtx->envCtx.unk_1F = 5;
                globalCtx->envCtx.unk_20 = 5;
            }
            this->unk_348 = 255.0f;

            for (i = 0; i < ARRAY_COUNT(this->unk_1AC); i++) {
                this->unk_1AC[i] = ovl_dm_char01_Vtx_1BE0[i].v.ob[1] * 409.6f;
            }

            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_009E4C);

            this->unk_34D = true;
            if (gSaveContext.sceneSetupIndex == 1) {
                this->unk_34C = 1;
                this->actionFunc = func_80AA8C28;
            } else {
                this->unk_34C = 0;
                this->actionFunc = func_80AA892C;
            }
            break;

        case DMCHAR01_1:
            if ((gSaveContext.save.weekEventReg[20] & 2) || (gSaveContext.sceneSetupIndex == 1)) {
                this->unk_34C = 1;
                this->actionFunc = func_80AA8F1C;
            } else {
                this->actionFunc = func_80AA8698;
            }
            break;

        case DMCHAR01_2:
            this->unk_34C = 0;
            if (!(gSaveContext.save.weekEventReg[20] & 1)) {
                this->unk_34C = 1;
                this->dyna.actor.world.pos.y -= 400.0f;
            }
            this->dyna.actor.world.rot.y += 0x8000;
            this->dyna.actor.shape.rot.y += 0x8000;
            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_010C3C);
            this->unk_34D = true;
            this->unk_348 = 200.0f;
            this->actionFunc = func_80AA8F2C;
            break;

        case DMCHAR01_3:
            this->dyna.actor.world.rot.y += 0x8000;
            this->dyna.actor.shape.rot.y += 0x8000;
            if (!(gSaveContext.save.weekEventReg[20] & 1)) {
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }

            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ETCETERA, 5.0f, 202.0f, 294.0f, 0, 0, 0, 0x80);
            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_00FE5C);

            this->unk_34D = true;
            if (!(gSaveContext.save.weekEventReg[20] & 2)) {
                this->actionFunc = func_80AA9020;
                this->dyna.actor.world.pos.y -= 120.0f;
            } else {
                this->actionFunc = func_80AA8F1C;
            }
            break;

        default:
            this->actionFunc = func_80AA88A8;
            break;
    }
}

void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmChar01* this = THIS;

    if (this->unk_34D) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80AA8698(DmChar01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);

    if (gSaveContext.save.weekEventReg[20] & 1) {
        return;
    }

    if ((player->stateFlags2 & 0x8000000) && (player2->actor.world.pos.x > -40.0f) &&
        (player2->actor.world.pos.x < 40.0f) && (player2->actor.world.pos.z > 1000.0f) &&
        (player2->actor.world.pos.z < 1078.0f)) {
        if (!D_80AAAAB4) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            D_80AAAAB4 = true;
        }
    } else {
        D_80AAAAB4 = false;
    }

    if ((player->transformation == PLAYER_FORM_DEKU) && (globalCtx->msgCtx.ocarinaMode == 3) &&
        (globalCtx->msgCtx.unk1202E == 0)) {

        if ((player2->actor.world.pos.x > -40.0f) && (player2->actor.world.pos.x < 40.0f) &&
            (player2->actor.world.pos.z > 1000.0f) && (player2->actor.world.pos.z < 1078.0f)) {
            gSaveContext.save.weekEventReg[20] |= 1;
            this->actionFunc = func_80AA884C;
        }
    }
}

void func_80AA884C(DmChar01* this, GlobalContext* globalCtx) {
    s16 sp1E = this->dyna.actor.cutscene;

    if (ActorCutscene_GetCanPlayNext(sp1E)) {
        ActorCutscene_Start(sp1E, &this->dyna.actor);
        this->actionFunc = func_80AA88A8;
    } else {
        ActorCutscene_SetIntentToPlay(sp1E);
    }
}

void func_80AA88A8(DmChar01* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 135)) {
        if (globalCtx->csCtx.frames ==
            globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 135)]->startFrame) {
            D_80AAAE24 = 1;
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FORT_RISING);
        }
    } else {
        D_80AAAE24 = 0;
    }
}

void func_80AA892C(DmChar01* this, GlobalContext* globalCtx) {
    f32 temp_f18;
    s32 temp_v0_4;
    s32 i;

    switch (this->unk_346) {
        case 0:
            D_80AAAE22 = -2200;
            D_80AAAE20 = 380;
            this->unk_346++;
            break;

        case 1:
            if (D_80AAAE24 != 0) {
                this->unk_34C = 1;
                if (D_80AAAE22 > -2000) {
                    D_80AAAE26 = 1;
                }

                D_80AAAE22 += 40;
                if (D_80AAAE22 > 3400) {
                    if (D_80AAAE20 > 100) {
                        D_80AAAE20 -= 230;
                    }
                    this->unk_346++;
                }
            }
            break;

        case 2:
            D_80AAAE22 -= 40;
            if (D_80AAAE22 <= -2200) {
                if (D_80AAAE20 > 100) {
                    D_80AAAE20 -= 70;
                }
                this->unk_346--;
            }
            break;
    }

    if (D_80AAAE24 == 0) {
        this->unk_34C = 0;
    }

    for (i = 0; i < ARRAY_COUNT(ovl_dm_char01_Vtx_1BE0); i++) {
        s32 temp_s2 = sqrtf(SQ((f32)ovl_dm_char01_Vtx_1BE0[i].v.ob[2]) + SQ((f32)ovl_dm_char01_Vtx_1BE0[i].v.ob[0]));
        f32 cos = Math_CosS((temp_s2 / 1892.0f) * 0x4000);
        f32 temp_f20 = (1.0f - (ABS_ALT(temp_s2 - D_80AAAE22) / 1892.0f)) * D_80AAAE20 * cos;

        if (temp_f20 < 0.0f) {
            temp_f20 = 0.0f;
        }

        temp_f18 = Math_SinS(this->unk_1AC[i]) * 15.0f;
        temp_f20 += temp_f18;

        this->unk_1AC[i] += 1600;
        ovl_dm_char01_Vtx_1BE0[i].v.ob[1] = temp_f20;
    }
}

void func_80AA8C28(DmChar01* this, GlobalContext* globalCtx) {
    f32 temp_f18;
    s32 temp_v0_4;
    s32 i;

    switch (this->unk_346) {
        case 0:
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WATER_PURIFICATION);
            D_80AAAE22 = -2200;
            D_80AAAE20 = 100;
            this->unk_346++;
            break;

        case 1:
            D_80AAAE22 += 40;
            if (D_80AAAE22 > 3400) {
                this->unk_346++;
            }
            break;

        case 2:
            D_80AAAE22 -= 40;
            if (D_80AAAE22 <= -2200) {
                this->unk_346--;
            }
            break;
    }

    for (i = 0; i < ARRAY_COUNT(ovl_dm_char01_Vtx_1BE0); i++) {
        s32 temp_s2 = sqrtf(SQ((f32)ovl_dm_char01_Vtx_1BE0[i].v.ob[2]) + SQ((f32)ovl_dm_char01_Vtx_1BE0[i].v.ob[0]));
        f32 cos = Math_CosS((temp_s2 / 1892.0f) * 0x4000);
        f32 temp_f20 = (1.0f - (ABS_ALT(temp_s2 - D_80AAAE22) / 1892.0f)) * D_80AAAE20 * cos;

        if (temp_f20 < 0.0f) {
            temp_f20 = 0.0f;
        }

        temp_f18 = Math_SinS(this->unk_1AC[i]) * 15.0f;
        temp_f20 += temp_f18;

        this->unk_1AC[i] += 1600;
        ovl_dm_char01_Vtx_1BE0[i].v.ob[1] = temp_f20;
    }

    Math_SmoothStepToF(&this->unk_348, 0.0f, 0.02f, 0.6f, 0.4f);

    if (this->unk_348 < 0.01f) {
        this->unk_34C = 2;
        this->actionFunc = func_80AA8F1C;
    }
}

void func_80AA8F0C(DmChar01* this, GlobalContext* globalCtx) {
}

void func_80AA8F1C(DmChar01* this, GlobalContext* globalCtx) {
}

void func_80AA8F2C(DmChar01* this, GlobalContext* globalCtx) {
    if (D_80AAAE26 != 0) {
        Math_SmoothStepToF(&this->dyna.actor.world.pos.y, 0.0f, 0.05f, 6.0f, 0.001f);
        Math_SmoothStepToF(&this->unk_348, 0.0f, 0.01f, 0.5f, 0.4f);
        if ((s32)this->dyna.actor.world.pos.y >= 0) {
            D_80AAAE26 = 2;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ETCETERA, 5.0f, 202.0f, 294.0f, 0, 0, 0, 0x80);
            this->actionFunc = func_80AA90F4;
        }
    }
    func_80AA8F0C(this, globalCtx);
}

void func_80AA9020(DmChar01* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 135)) {
        CsCmdActorAction* temp_v1 = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 135)];

        if ((temp_v1->startFrame == globalCtx->csCtx.frames) && (temp_v1->action == 2)) {
            gSaveContext.save.weekEventReg[20] |= 2;
            this->actionFunc = func_80AA90AC;
        }
    }
}

void func_80AA90AC(DmChar01* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->dyna.actor.world.pos.y, 0.0f, 0.05f, 2.0f, 0.001f);
}

void func_80AA90F4(DmChar01* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->unk_348, 0.0f, 0.02f, 0.8f, 0.4f);
}

void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DmChar01* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_34D) {
        if (DMCHAR01_GET(&this->dyna.actor) == DMCHAR01_0) {
            Player* player = GET_PLAYER(globalCtx);

            if (player->actor.world.pos.y > 5.0f) {
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            } else {
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            }
        }

        if (DMCHAR01_GET(&this->dyna.actor) == DMCHAR01_2) {
            if (this->dyna.actor.xzDistToPlayer > 600.0f) {
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            } else {
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            }
        }
    }
}

void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static f32 D_80AAAAB8 = 0.0f;
    static f32 D_80AAAABC = 0.0f;
    static s16 D_80AAAAC0 = 0;
    static s16 D_80AAAAC4 = 0;
    static s16 D_80AAAAC8 = 0;
    static s16 D_80AAAACC = 0;
    DmChar01* this = THIS;
    f32 temp_f12;
    f32 spBC;
    s32 i;
    u8 spB7 = false;

    switch (DMCHAR01_GET(thisx)) {
        case DMCHAR01_0:
            switch (this->unk_34C) {
                case 0:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00AA50));
                    Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_00A8F8);
                    break;

                case 1:
                    if (gSaveContext.sceneSetupIndex == 1) {
                        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_0110B8));
                        Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_010FD8);
                        Gfx_DrawDListXlu(globalCtx, object_mtoride_DL_010EF0);
                        Matrix_InsertTranslation(0.0f, 10.0f, 0.0f, MTXMODE_APPLY);
                    }
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_009D70));

                    OPEN_DISPS(globalCtx->state.gfxCtx);

                    if ((u8)this->unk_348 == 255) {
                        func_8012C28C(globalCtx->state.gfxCtx);

                        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
                        gDPPipeSync(POLY_OPA_DISP++);
                        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x96, 255, 255, 255, 255);
                        gSPSegment(POLY_OPA_DISP++, 0x0B, Lib_SegmentedToVirtual(ovl_dm_char01_Vtx_1BE0));
                        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_OPA_DISP++, object_mtoride_DL_009928);
                    } else {
                        func_8012C2DC(globalCtx->state.gfxCtx);

                        gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
                        gDPPipeSync(POLY_XLU_DISP++);
                        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, (u8)this->unk_348);
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x96, 255, 255, 255, (u8)this->unk_348);
                        gSPSegment(POLY_XLU_DISP++, 0x0B, Lib_SegmentedToVirtual(ovl_dm_char01_Vtx_1BE0));
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_XLU_DISP++, object_mtoride_DL_009928);
                    }

                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                    break;

                case 2:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_0110B8));
                    Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_010FD8);
                    Gfx_DrawDListXlu(globalCtx, object_mtoride_DL_010EF0);
                    break;
            }
            break;

        case DMCHAR01_1:
            switch (this->unk_34C) {
                case 0:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00A5C0));
                    Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_00A398);
                    break;

                case 1:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00B1A0));
                    Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_00AF98);
                    break;
            }
            break;

        case DMCHAR01_2:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00FE90));
            Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_00DF18);

            if ((this->unk_34C != 0) && ((u8)this->unk_348 != 0)) {
                AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00F768));

                OPEN_DISPS(globalCtx->state.gfxCtx);

                func_8012C2DC(globalCtx->state.gfxCtx);

                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, (u8)this->unk_348);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (u8)this->unk_348);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, object_mtoride_DL_00F3C0);

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }

            if (D_80AAAE24 != 0) {
                if ((D_80AAAE22 > -1800) && (D_80AAAE22 < 3000)) {
                    temp_f12 = D_80AAAE22 - 640.0f;
                    if ((D_80AAAE20 == 380) && (D_80AAAE22 > 640)) {
                        D_80AAAAC0 = 2;
                        D_80AAAAC4 = 0;
                        D_80AAAAC8 = 900;
                        D_80AAAACC = 700;
                        spB7 = true;
                        if (D_80AAAE22 < 1350) {
                            f32 temp_f0 = temp_f12 / 2000.0f;

                            D_80AAAAB8 = 420.0f - (420.0f * temp_f0);
                            D_80AAAABC = (200.0f * temp_f0) + 200.0f;
                        } else {
                            f32 temp_f0 = temp_f12 / 2000.0f;

                            D_80AAAAB8 = 420.0f - (420.0f * temp_f0);
                            D_80AAAABC = 400.0f;
                        }
                    }
                }

                if (spB7) {
                    for (i = 0; i < D_80AAAAC0 * 2; i++) {
                        Vec3f sp44;
                        f32 phi_f2 = D_80AAAABC;
                        s16 temp;

                        spBC = Rand_ZeroOne() * D_80AAAAC8;
                        if ((globalCtx->state.frames % 2) != 0) {
                            sp44.x = (Rand_ZeroOne() - 0.5f) * (2.0f * phi_f2);
                            sp44.y = D_80AAAAB8;
                            sp44.z = (Rand_ZeroOne() * D_80AAAAC4) + phi_f2;
                            temp = (s16)spBC + D_80AAAACC;
                            EffectSsGSplash_Spawn(globalCtx, &sp44, NULL, NULL, 0, temp);
                        } else {
                            sp44.x = -phi_f2 - (Rand_ZeroOne() * D_80AAAAC4);
                            sp44.y = D_80AAAAB8;
                            sp44.z = (Rand_ZeroOne() - 0.5f) * (2.0f * phi_f2);
                            temp = (s16)spBC + D_80AAAACC;
                            EffectSsGSplash_Spawn(globalCtx, &sp44, NULL, NULL, 0, temp);
                        }
                    }
                }
            }

            Gfx_DrawDListXlu(globalCtx, object_mtoride_DL_00DE50);
            break;

        case DMCHAR01_3:
            if (thisx->world.pos.y > -120.0f) {
                Gfx_DrawDListOpa(globalCtx, object_mtoride_DL_00FAE8);
            }
            break;
    }
}
