/*
 * File: z_actor.c
 * Description:
 */

//#include "prevent_bss_reordering.h"
#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"
#include "overlays/actors/ovl_En_Part/z_en_part.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

// bss
extern FaultClient D_801ED8A0;    // 2 funcs
extern CollisionPoly* D_801ED8B0; // 1 func
extern s32 D_801ED8B4;            // 2 funcs
extern Actor* D_801ED8B8;         // 2 funcs
extern Actor* D_801ED8BC;         // 2 funcs
extern Actor* D_801ED8C0;         // 2 funcs
extern Actor* D_801ED8C4;         // 2 funcs
extern f32 D_801ED8C8;            // 2 funcs
extern f32 D_801ED8CC;            // 2 funcs
extern f32 D_801ED8D0;            // 2 funcs
extern s32 D_801ED8D4;            // 2 funcs
extern s32 D_801ED8D8;            // 2 funcs
extern s16 D_801ED8DC;            // 2 funcs
extern Mtx D_801ED8E0;            // 1 func
extern s32 D_801ED920;            // 2 funcs. 1 out of z_actor

void Actor_PrintLists(ActorContext* actorCtx) {
    ActorListEntry* actorList = &actorCtx->actorList[0];
    Actor* actor;
    s32 i;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor\n", gMaxActorId);
    FaultDrawer_Printf("No. Actor   Name Part SegName\n");

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++) {
        actor = actorList[i].first;

        while (actor != NULL) {
            FaultDrawer_Printf("%3d %08x %04x %3d %s\n", i, actor, actor->id, actor->category, "");
            actor = actor->next;
        }
    }
}

void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale) {
    actorShape->yOffset = yOffset;
    actorShape->shadowDraw = shadowDraw;
    actorShape->shadowScale = shadowScale;
    actorShape->shadowAlpha = 255;
}

void ActorShadow_Draw(Actor* actor, Lights* lights, GlobalContext* globalCtx, Gfx* dlist, Color_RGBA8* color) {
    if (actor->floorPoly != NULL) {
        f32 dy = actor->world.pos.y - actor->floorHeight;

        if (dy >= -50.0f && dy < 500.0f) {
            f32 shadowScale;
            MtxF mtx;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);

            gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                              COMBINED);

            dy = CLAMP(dy, 0.0f, 150.0f);
            shadowScale = 1.0f - (dy * 0.0028571428f);
            if ((dy * 0.0028571428f) > 1.0f) {
                shadowScale = 0.0f;
            }

            if (color != NULL) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, color->r, color->g, color->b,
                                (u8)(actor->shape.shadowAlpha * shadowScale));
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(actor->shape.shadowAlpha * shadowScale));
            }

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &mtx);
            SysMatrix_SetCurrentState(&mtx);

            if ((dlist != D_04076BC0) || (actor->scale.x != actor->scale.z)) {
                Matrix_RotateY(actor->shape.rot.y, MTXMODE_APPLY);
            }

            shadowScale *= actor->shape.shadowScale;
            Matrix_Scale(actor->scale.x * shadowScale, 1.0f, actor->scale.z * shadowScale, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, dlist);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void ActorShadow_DrawCircle(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, NULL);
}

void ActorShadow_DrawSquare(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04075A40, NULL);
}

Color_RGBA8 D_801AEC80 = { 255, 255, 255, 255 };

void ActorShadow_DrawWhiteCircle(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, &D_801AEC80);
}

void ActorShadow_DrawHorse(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04077480, NULL);
}

void ActorShadow_DrawFoot(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 pad;
    s16 sp58;
    f32 dir2;
    f32 dir0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(CLAMP_MAX(arg3 * 1.3e-05f, 1.0f) * arg4));

    dir0 = light->l.dir[0];
    dir2 = light->l.dir[2];
    sp58 = Math_FAtan2F(dir2, dir0);
    arg6 *= 4.5f - light->l.dir[1] * 0.035f;
    arg6 = CLAMP_MIN(arg6, 1.0f);
    SysMatrix_SetCurrentState(arg2);
    Matrix_RotateY(sp58, MTXMODE_APPLY);
    Matrix_Scale(arg5, 1.0f, arg5 * arg6, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, D_04075B30);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#ifdef NON_MATCHING
// stack and regalloc
void ActorShadow_DrawFeet(Actor* actor, Lights* mapper, GlobalContext* globalCtx) {

    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f0_2;
    Vec3f* phi_fp;
    f32 distToFloor;
    s32 j;
    s32 temp_s5;

    MtxF sp13C;
    MtxF spFC;
    CollisionPoly* spF8;
    s32 spF4;
    f32 floorHeight[2]; // spEC

    s32 temp_a3;
    Light* sp9C;

    f32 temp_f24;

    s32 phi_s2;

    u8 spD3;
    s32 spD0;
    f32* spBC;
    s32 spB8;

    distToFloor = actor->world.pos.y - actor->floorHeight;
    if (distToFloor > 0.0f) {
        f32 shadowScale = actor->shape.shadowScale;
        u8 shadowAlpha = actor->shape.shadowAlpha;
        f32 alphaRatio;

        if ((actor->id == ACTOR_PLAYER) && (((Player*)actor)->stateFlags3 & 0x8000)) {
            f32 temp_f20 = actor->scale.z;

            actor->scale.z += 0.03f * fabsf(Math_CosS(((Player*)actor)->unk_AAA));
            actor->shape.shadowScale *= 0.2f;
            alphaRatio = distToFloor * 0.03f;
            actor->shape.shadowAlpha = actor->shape.shadowAlpha * CLAMP_MIN(alphaRatio, 1.0f);
            ActorShadow_Draw(actor, mapper, globalCtx, D_04076BC0, NULL);
            actor->scale.z = temp_f20;
        } else {
            actor->shape.shadowScale *= 0.3f;
            alphaRatio = (distToFloor - 20.0f) * 0.02f;
            actor->shape.shadowAlpha = actor->shape.shadowAlpha * CLAMP_MIN(alphaRatio, 1.0f);
            ActorShadow_DrawCircle(actor, mapper, globalCtx);
        }

        actor->shape.shadowScale = shadowScale;
        actor->shape.shadowAlpha = shadowAlpha;
    }

    if (distToFloor < 200.0f) {
        temp_s5 = mapper->numLights - 2;
        spBC = floorHeight;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        phi_fp = actor->shape.feetPos;
        POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
        actor->shape.feetFloorFlags = 0;
        spB8 = 2;

        for (spD0 = 0; spD0 < ARRAY_COUNT(floorHeight); spD0++) {
            f32 phi_f26;

            phi_fp->y += 50.0f;
            *spBC = func_80169100(globalCtx, &sp13C, &spF8, &spF4, phi_fp);
            phi_fp->y -= 50.0f;

            phi_f26 = phi_fp->y - *spBC;
            if ((phi_f26 >= -1.0f) && (phi_f26 < 500.0f)) {
                phi_s2 = 0;

                if (phi_f26 <= 10.0f) {
                    actor->shape.feetFloorFlags |= spB8;

                    if ((actor->yDistToWater < 0.0f) && (spF4 == 0x32) && ((actor->shape.unk_17 & spB8) != 0)) {
                        if (func_800C9C24(&globalCtx->colCtx, spF8, spF4, 1) != 0) {
                            SkinMatrix_MtxFCopy(&sp13C, &spFC);
                            SkinMatrix_MulYRotation(&spFC, actor->shape.rot.y);
                            EffFootmark_Add(globalCtx, &spFC, actor, spD3, phi_fp, (actor->shape.shadowScale * 0.3f),
                                            IREG(88) + 0x50, IREG(89) + 0x3C, IREG(90) + 0x28, 0x7530, 0xC8, 0x3C);
                        }
                        actor->shape.unk_17 &= ~spB8;
                    }
                }

                if (phi_f26 > 30.0f) {
                    phi_f26 = 30.0f;
                }

                temp_f22 = actor->shape.shadowAlpha * (1.0f - (phi_f26 * 0.033333335f));
                temp_f20_2 = 1.0f - (phi_f26 * 0.014285714f);
                temp_f24 = actor->shape.shadowScale * temp_f20_2 * actor->scale.x;

                sp9C = mapper->l.l;
                j = 0;
                while (j < temp_s5) {
                    if (sp9C->l.dir[1] > 0) {
                        s32 temp_lo;

                        temp_lo = (sp9C->l.col[0] + sp9C->l.col[1] + sp9C->l.col[2]) * ABS_ALT(sp9C->l.dir[1]);
                        if (temp_lo > 0) {
                            phi_s2 += temp_lo;
                            ActorShadow_DrawFoot(globalCtx, sp9C, &sp13C, temp_lo, temp_f22, temp_f24, temp_f20_2);
                        }
                    }
                    j++;
                    sp9C++;
                }

                for (j = 0; j < 2; j++) {
                    if (sp9C->l.dir[1] > 0) {
                        temp_a3 = ((sp9C->l.col[0] + sp9C->l.col[1] + sp9C->l.col[2]) * ABS_ALT(sp9C->l.dir[1])) -
                                  (phi_s2 * 8);
                        if (temp_a3 > 0) {
                            ActorShadow_DrawFoot(globalCtx, sp9C, &sp13C, temp_a3, temp_f22, temp_f24, temp_f20_2);
                        }
                    }
                    sp9C++;
                }
            }
            phi_fp++;
            spBC++;
            spB8 >>= 1;
        }

        if (!(actor->bgCheckFlags & 1)) {
            actor->shape.feetFloorFlags = 0;
        } else if (actor->shape.feetFloorFlags == 3) {
            temp_f0_2 = actor->shape.feetPos[0].y - actor->shape.feetPos[1].y;
            if ((floorHeight[0] + temp_f0_2) < (floorHeight[1] - temp_f0_2)) {
                actor->shape.feetFloorFlags = 2;
            } else {
                actor->shape.feetFloorFlags = 1;
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/ActorShadow_DrawFeet.s")
#endif

void Actor_SetFeetPos(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                      Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        SysMatrix_MultiplyVector3fByState(leftFootPos, &actor->shape.feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        SysMatrix_MultiplyVector3fByState(rightFootPos, &actor->shape.feetPos[FOOT_RIGHT]);
    }
}

void func_800B4AEC(GlobalContext* globalCtx, Actor* actor, f32 param_3) {
    s32 floorBgId;
    f32 yPos = actor->world.pos.y;

    actor->world.pos.y += param_3;
    actor->floorHeight =
        func_800C4188(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &floorBgId, actor, &actor->world.pos);
    actor->floorBgId = floorBgId;
    actor->world.pos.y = yPos;
}

#ifdef NON_MATCHING
// regalloc
void func_800B4B50(Actor* actor, Lights* mapper, GlobalContext* globalCtx) {
    f32 spEC;
    f32 temp_f12;
    f32 temp_f20;
    f32 shadowScaleZ;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f8;
    MtxF sp94;
    s32 lightNum;
    s32 numLights;
    s8 phi_v1;
    u8 temp_v0;
    f32 phi_f0;
    // f32 phi_f8;
    Light* phi_s0;
    s32 lightNumMax;

    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    if (actor->floorPoly != NULL) {
        s32 j;

        spEC = actor->world.pos.y - actor->floorHeight;
        if (spEC > 20.0f) {
            temp_f20 = actor->shape.shadowScale;
            temp_v0 = actor->shape.shadowAlpha;
            // actor->shape.shadowScale = temp_f20 * 0.3f;
            actor->shape.shadowScale *= 0.3f;
            temp_f12 = (spEC - 20.0f) * 0.02f;
            // if (temp_f12 > 1.0f) {
            //    phi_f0 = 1.0f;
            //} else {
            //    phi_f0 = temp_f12;
            //}
            phi_f0 = CLAMP_MIN(temp_f12, 1.0f);
            /*temp_f8 = (f32) temp_v0;
            phi_f8 = temp_f8;
            if ((s32) temp_v0 < 0) {
                phi_f8 = temp_f8 + 4294967296.0f;
            }
            actor->shape.shadowAlpha = (u8) (u32) (phi_f0 * phi_f8);*/
            // actor->shape.shadowAlpha = (phi_f0 *  temp_v0);
            actor->shape.shadowAlpha *= phi_f0;
            ActorShadow_DrawCircle(actor, mapper, globalCtx);
            actor->shape.shadowScale = temp_f20;
            actor->shape.shadowAlpha = temp_v0;
        dummy_label_111649:;
        } else if (spEC >= -1.0f) {
            numLights = mapper->numLights - 2;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &sp94);
            temp_f22 = (f32)actor->shape.shadowAlpha * (1.0f - (spEC * (1.0f / 30.0f)));
            phi_s0 = mapper->l.l;
            shadowScaleZ = 1.0f - (spEC * 0.014285714f);
            temp_f24 = actor->shape.shadowScale * shadowScaleZ * actor->scale.x;

            lightNumMax = 0;
            for (j = 0; j < numLights; j++, phi_s0++) {
                if (phi_s0->l.dir[1] > 0) {
                    lightNum = (phi_s0->l.col[0] + phi_s0->l.col[1] + phi_s0->l.col[2]) * ABS_ALT(phi_s0->l.dir[1]);
                    if (lightNum > 0) {
                        lightNumMax += lightNum;
                        ActorShadow_DrawFoot(globalCtx, phi_s0, &sp94, lightNum, temp_f22, temp_f24, shadowScaleZ);
                    }
                }
            }

            for (j = 0; j < 2; j++, phi_s0++) {
                if (phi_s0->l.dir[1] > 0) {
                    lightNum = (ABS_ALT(phi_s0->l.dir[1]) * (phi_s0->l.col[0] + phi_s0->l.col[1] + phi_s0->l.col[2])) -
                               (lightNumMax * ((void)0, 8));
                    if (lightNum > 0) {
                        ActorShadow_DrawFoot(globalCtx, phi_s0, &sp94, lightNum, temp_f22, temp_f24, shadowScaleZ);
                    }
                }
            }
            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4B50.s")
#endif

void func_800B4EDC(GlobalContext* globalCtx, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->projectionMatrix, pzParm2, pzParm3, pfParm4);
    if (*pfParm4 < 1.0f) {
        *pfParm4 = 1.0f;
    } else {
        *pfParm4 = 1.0f / *pfParm4;
    }
}

void func_800B4F40(TargetContext* targetCtx, s32 index, f32 x, f32 y, f32 z) {
    targetCtx->unk50[index].pos.x = x;
    targetCtx->unk50[index].pos.y = y;
    targetCtx->unk50[index].pos.z = z;
    targetCtx->unk50[index].unkC = targetCtx->unk44;
}

s801AEC84 D_801AEC84[] = {
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 255, 255, 230, 255 }, { 220, 160, 80, 0 } },  { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 150, 150, 255, 255 }, { 150, 150, 255, 0 } }, { { 255, 255, 0, 255 }, { 200, 155, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 255, 255, 0, 255 }, { 200, 155, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } }
};

void func_800B4F78(TargetContext* targetCtx, s32 type, GlobalContext* globalCtx) {
    s801AEC84* temp_s2;
    s32 phi_s1;
    TargetContextEntry* phi_s0;

    Math_Vec3f_Copy(&targetCtx->targetCenterPos, &globalCtx->view.eye);
    targetCtx->unk48 = 0x100;
    temp_s2 = &D_801AEC84[type];
    targetCtx->unk44 = 500.0f;

    phi_s0 = targetCtx->unk50;
    for (phi_s1 = 0; phi_s1 < ARRAY_COUNT(targetCtx->unk50); phi_s1++, phi_s0++) {
        func_800B4F40(targetCtx, phi_s1, 0.0f, 0.0f, 0.0f);
        phi_s0->color.r = temp_s2->inner.r;
        phi_s0->color.g = temp_s2->inner.g;
        phi_s0->color.b = temp_s2->inner.b;
    }
}

// OoT's func_8002BF60
void func_800B5040(TargetContext* targetCtx, Actor* actor, s32 type, GlobalContext* globalCtx) {
    targetCtx->unk0.x = actor->focus.pos.x;
    targetCtx->unk0.y = actor->focus.pos.y + (actor->targetArrowOffset * actor->scale.y);
    targetCtx->unk0.z = actor->focus.pos.z;

    targetCtx->fairyInner.r = D_801AEC84[type].inner.r;
    targetCtx->fairyInner.g = D_801AEC84[type].inner.g;
    targetCtx->fairyInner.b = D_801AEC84[type].inner.b;
    targetCtx->fairyInner.a = D_801AEC84[type].inner.a;
    targetCtx->fairyOuter.r = D_801AEC84[type].outer.r;
    targetCtx->fairyOuter.g = D_801AEC84[type].outer.g;
    targetCtx->fairyOuter.b = D_801AEC84[type].outer.b;
    targetCtx->fairyOuter.a = D_801AEC84[type].outer.a;
}

void Actor_TargetContextInit(TargetContext* targetCtx, Actor* actor, GlobalContext* globalCtx) {
    targetCtx->unk90 = NULL;
    targetCtx->unk8C = NULL;
    targetCtx->targetedActor = NULL;
    targetCtx->arrowPointedActor = NULL;
    targetCtx->unk4B = 0;
    targetCtx->unk4C = 0;
    targetCtx->unk40 = 0.0f;
    func_800B5040(targetCtx, actor, actor->category, globalCtx);
    func_800B4F78(targetCtx, actor->category, globalCtx);
}

#ifdef NON_MATCHING
// stack is too big
void func_800B5208(TargetContext* targetCtx, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags1 & 0x300006C2) == 0) {
        Actor* actor = targetCtx->targetedActor;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        if (targetCtx->unk48 != 0) {
            TargetContextEntry* entry;
            s16 spCE;
            f32 temp1;
            Vec3f spBC;
            s32 spB8;
            f32 spB4;
            s32 spB0;
            s32 spAC;
            f32 var1;
            f32 var2;
            s32 i;

            spCE = 0xFF;
            var1 = 1.0f;

            if (targetCtx->unk4B != 0) {
                spB8 = 1;
            } else {
                spB8 = 3;
            }

            if (actor != NULL) {
                Math_Vec3f_Copy(&targetCtx->targetCenterPos, &actor->focus.pos);
                var1 = (500.0f - targetCtx->unk44) / 420.0f;
            } else {
                targetCtx->unk48 -= 120;
                if (targetCtx->unk48 < 0) {
                    targetCtx->unk48 = 0;
                }
                spCE = targetCtx->unk48;
            }

            func_800B4EDC(globalCtx, &targetCtx->targetCenterPos, &spBC, &spB4);

            spBC.x = (160 * (spBC.x * spB4)) * var1;
            spBC.x = CLAMP(spBC.x, -320.0f, 320.0f);

            spBC.y = (120 * (spBC.y * spB4)) * var1;
            spBC.y = CLAMP(spBC.y, -240.0f, 240.0f);

            spBC.z = spBC.z * var1;

            targetCtx->unk4C--;
            if (targetCtx->unk4C < 0) {
                targetCtx->unk4C = 2;
            }

            func_800B4F40(targetCtx, targetCtx->unk4C, spBC.x, spBC.y, spBC.z);

            if ((!(player->stateFlags1 & 0x40)) || (actor != player->unk_730)) {
                OVERLAY_DISP = Gfx_CallSetupDL(OVERLAY_DISP, 0x39);

                for (spB0 = 0, spAC = targetCtx->unk4C; spB0 < spB8; spB0++, spAC = (spAC + 1) % 3) {
                    entry = &targetCtx->unk50[spAC];

                    if (entry->unkC < 500.0f) {
                        if (entry->unkC <= 120.0f) {
                            var2 = 0.15f;
                        } else {
                            var2 = ((entry->unkC - 120.0f) * 0.001f) + 0.15f;
                        }

                        SysMatrix_InsertTranslation(entry->pos.x, entry->pos.y, 0.0f, MTXMODE_NEW);
                        Matrix_Scale(var2, 0.15f, 1.0f, MTXMODE_APPLY);

                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, entry->color.r, entry->color.g, entry->color.b, (u8)spCE);

                        // SysMatrix_InsertZRotation_s((targetCtx->unk4B & 0x7F) * (M_PI / 64), MTXMODE_APPLY);
                        SysMatrix_InsertZRotation_s((targetCtx->unk4B * 512), MTXMODE_APPLY);

                        for (i = 0; i < 4; i++) {
                            SysMatrix_InsertZRotation_s(M_PI / 2, MTXMODE_APPLY);
                            SysMatrix_StatePush();
                            SysMatrix_InsertTranslation(entry->unkC, entry->unkC, 0.0f, MTXMODE_APPLY);
                            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                      G_MTX_MODELVIEW | G_MTX_LOAD);
                            // gSPDisplayList(OVERLAY_DISP++, gZTargetLockOnTriangleDL);
                            gSPDisplayList(OVERLAY_DISP++, D_0407AE00);
                            SysMatrix_StatePop();
                        }
                    }

                    spCE -= 0xFF / 3;
                    if (spCE < 0) {
                        spCE = 0;
                    }
                }
            }
        }

        actor = targetCtx->unk_94;
        if ((actor != NULL) && !(actor->flags & 0x8000000)) {
            // NaviColor* naviColor = &sNaviColorList[actor->category];
            s801AEC84* color = &D_801AEC84[actor->category];

            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0x07);

            SysMatrix_InsertTranslation(actor->focus.pos.x,
                                        actor->focus.pos.y + (actor->targetArrowOffset * actor->scale.y) + 17.0f,
                                        actor->focus.pos.z, MTXMODE_NEW);
            // Matrix_RotateY((f32)((u16)(globalCtx->gameplayFrames * 3000)) * (M_PI / 0x8000), MTXMODE_APPLY);
            Matrix_RotateY((globalCtx->gameplayFrames * 3000), MTXMODE_APPLY);
            Matrix_Scale((iREG(27) + 35) / 1000.0f, (iREG(28) + 60) / 1000.0f, (iREG(29) + 50) / 1000.0f,
                         MTXMODE_APPLY);

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, color->inner.r, color->inner.g, color->inner.b, 255);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_XLU_DISP++, D_0401F0F0);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5208.s")
#endif

#ifdef NON_EQUIVALENT
// OoT: func_8002C7BC
void func_800B5814(TargetContext* targetCtx, Player* player, Actor* actor, GlobalContext* globalCtx) {
    Actor* sp68;
    s32 sp64;
    Vec3f sp58;
    f32 sp54;
    f32 sp44;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    Actor* phi_s1;

    sp68 = NULL;
    phi_s1 = actor;
    if ((player->unk_730 != 0) && (player->unk_AE3[player->unk_ADE] == 2)) {
        targetCtx->unk_94 = NULL;
    } else {
        func_800BB8EC(globalCtx, &globalCtx->actorCtx, &sp68, &D_801ED920, player);
        targetCtx->unk_94 = sp68;
    }

    if (targetCtx->unk8C != 0) {
        sp68 = targetCtx->unk8C;
        targetCtx->unk8C = NULL;
    } else if (actor != 0) {
        sp68 = actor;
    }

    if (sp68 != 0) {
        sp64 = sp68->category;
    } else {
        sp64 = player->actor.category;
    }

    if ((sp68 != targetCtx->arrowPointedActor) || (sp64 != targetCtx->unk4A)) {
        targetCtx->arrowPointedActor = sp68;
        targetCtx->unk4A = sp64;
        targetCtx->unk40 = 1.0f;
    }

    if (sp68 == NULL) {
        sp68 = player;
    }

    if (Math_StepToF(&targetCtx->unk40, 0.0f, 0.25f) == 0) {
        temp_f0 = 0.25f / targetCtx->unk40;
        targetCtx->unk0.x += ((sp68->focus.pos.x - targetCtx->unk0.x) * temp_f0);
        targetCtx->unk0.y +=
            (((sp68->focus.pos.y + (sp68->targetArrowOffset * sp68->scale.z)) - targetCtx->unk0.y) * temp_f0);
        targetCtx->unk0.z += (sp68->focus.pos.z - targetCtx->unk0.z) * temp_f0;
    } else {
        func_800B5040(targetCtx, sp68, sp64, globalCtx);
    }

    if (actor != NULL && targetCtx->unk4B == 0) {
        func_800B4EDC(globalCtx, &actor->focus.pos, &sp58, &sp54);
        if ((sp58.z <= 0.0f) || (fabsf(sp58.x * sp54) >= 1.0f) || (fabsf(sp58.y * sp54) >= 1.0f)) {
            phi_s1 = NULL;
        }
    }

    if (phi_s1 != NULL) {
        if (phi_s1 != targetCtx->targetedActor) {
            func_800B4F78(targetCtx, phi_s1->category, globalCtx);
            targetCtx->targetedActor = phi_s1;

            if (phi_s1->id == ACTOR_EN_BOOM) {
                targetCtx->unk48 = 0;
            }

            play_sound((phi_s1->flags & 5) == 5 ? 0x4830 : 0x4810);
        }

        targetCtx->targetCenterPos.x = phi_s1->world.pos.x;
        targetCtx->targetCenterPos.y = phi_s1->world.pos.y - (phi_s1->shape.yOffset * phi_s1->scale.y);
        targetCtx->targetCenterPos.z = phi_s1->world.pos.z;
        if (targetCtx->unk4B == 0) {
            temp_f0_2 = (500.0f - targetCtx->unk44) * 3.0f;

            if (Math_StepToF(&targetCtx->unk44, 80.0f, CLAMP(temp_f0_2, 30.0f, 100.0f)) != 0) {
                targetCtx->unk4B += 1;
            }
        } else {
            targetCtx->unk4B = (targetCtx->unk4B + 3) | 0x80;
            targetCtx->unk44 = 120.0f;
        }
    } else {
        targetCtx->targetedActor = NULL;
        Math_StepToF(&targetCtx->unk44, 500.0f, 80.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5814.s")
#endif

/**
 * Tests if current scene switch flag is set.
 */
s32 Flags_GetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return globalCtx->actorCtx.flags.swch[(flag & ~0x1F) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

/**
 * Sets current scene switch flag.
 */
void Flags_SetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.flags.swch[(flag & ~0x1F) >> 5] |= 1 << (flag & 0x1F);
    }
}

/**
 * Unsets current scene switch flag.
 */
void Flags_UnsetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.flags.swch[(flag & ~0x1F) >> 5] &= ~(1 << (flag & 0x1F));
    }
}

/**
 * Tests if current scene chest flag is set.
 */
s32 Flags_GetTreasure(GlobalContext* globalCtx, s32 flag) {
    return globalCtx->actorCtx.flags.chest & (1 << flag);
}

/**
 * Sets current scene chest flag.
 */
void Flags_SetTreasure(GlobalContext* globalCtx, s32 flag) {
    globalCtx->actorCtx.flags.chest |= (1 << flag);
}

void Flags_SetAllTreasure(GlobalContext* globalCtx, s32 flag) {
    globalCtx->actorCtx.flags.chest = flag;
}

s32 Flags_GetAllTreasure(GlobalContext* globalCtx) {
    return globalCtx->actorCtx.flags.chest;
}

/**
 * Tests if current scene clear flag is set.
 */
s32 Flags_GetClear(GlobalContext* globalCtx, s32 roomNumber) {
    return globalCtx->actorCtx.flags.clearedRoom & (1 << roomNumber);
}

/**
 * Sets current scene clear flag.
 */
void Flags_SetClear(GlobalContext* globalCtx, s32 roomNumber) {
    globalCtx->actorCtx.flags.clearedRoom |= (1 << roomNumber);
}

/**
 * Unsets current scene clear flag.
 */
void Flags_UnsetClear(GlobalContext* globalCtx, s32 roomNumber) {
    globalCtx->actorCtx.flags.clearedRoom &= ~(1 << roomNumber);
}

/**
 * Tests if current scene temp clear flag is set.
 */
s32 Flags_GetClearTemp(GlobalContext* globalCtx, s32 roomNumber) {
    return globalCtx->actorCtx.flags.clearedRoomTemp & (1 << roomNumber);
}

/**
 * Sets current scene temp clear flag.
 */
void Flags_SetClearTemp(GlobalContext* globalCtx, s32 roomNumber) {
    globalCtx->actorCtx.flags.clearedRoomTemp |= (1 << roomNumber);
}

/**
 * Unsets current scene temp clear flag.
 */
void Flags_UnsetClearTemp(GlobalContext* globalCtx, s32 roomNumber) {
    globalCtx->actorCtx.flags.clearedRoomTemp &= ~(1 << roomNumber);
}

/**
 * Tests if current scene collectible flag is set.
 */
s32 Flags_GetCollectible(GlobalContext* globalCtx, s32 flag) {
    if (flag > 0 && flag < 0x80) {
        return globalCtx->actorCtx.flags.collectible[(flag & ~0x1F) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

/**
 * Sets current scene collectible flag.
 */
void Flags_SetCollectible(GlobalContext* globalCtx, s32 flag) {
    if (flag > 0 && flag < 0x80) {
        globalCtx->actorCtx.flags.collectible[(flag & ~0x1F) >> 5] |= 1 << (flag & 0x1F);
    }
}

void TitleCard_ContextInit(GameState* gameState, TitleCardContext* titleCtx) {
    titleCtx->durationTimer = 0;
    titleCtx->delayTimer = 0;
    titleCtx->intensity = 0;
    titleCtx->alpha = 0;
}

void TitleCard_InitBossName(GameState* gameState, TitleCardContext* titleCtx, u32 texture, s16 param_4, s16 param_5,
                            u8 param_6, u8 param_7) {
    titleCtx->texture = texture;
    titleCtx->x = param_4;
    titleCtx->y = param_5;
    titleCtx->width = param_6;
    titleCtx->height = param_7;
    titleCtx->durationTimer = 80;
    titleCtx->delayTimer = 0;
}

void TitleCard_InitPlaceName(GameState* gameState, TitleCardContext* titleCtx, void* texture, s32 x, s32 y, s32 width,
                             s32 height, s32 delay) {
}

void TitleCard_Update(GameState* gameState, TitleCardContext* titleCtx) {
    if (DECR(titleCtx->delayTimer) == 0) {
        if (DECR(titleCtx->durationTimer) == 0) {
            Math_StepToS(&titleCtx->alpha, 0, 30);
            Math_StepToS(&titleCtx->intensity, 0, 70);
        } else {
            Math_StepToS(&titleCtx->alpha, 255, 10);
            Math_StepToS(&titleCtx->intensity, 255, 20);
        }
    }
}

void TitleCard_Draw(GameState* gameState, TitleCardContext* titleCtx) {
    s32 spCC;
    s32 spC8;
    s32 unk1;
    s32 spC0;
    s32 sp38;
    s32 spB8;
    s32 spB4;
    s32 temp;

    if (titleCtx->alpha != 0) {
        spCC = titleCtx->width;
        spC8 = titleCtx->height;
        temp = spCC * 2;
        spC0 = (titleCtx->x * 4) - temp;
        spB8 = (titleCtx->y * 4) - (spC8 * 2);
        sp38 = spCC * 2;

        OPEN_DISPS(gameState->gfxCtx);

        spC8 = (spCC * spC8 > 0x1000) ? 0x1000 / spCC : spC8;
        spB4 = spB8 + (spC8 * 4);

        if (1) {}

        OVERLAY_DISP = func_8012C014(OVERLAY_DISP);

        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, (u8)titleCtx->intensity, (u8)titleCtx->intensity, (u8)titleCtx->intensity,
                        (u8)titleCtx->alpha);

        gDPLoadTextureBlock(OVERLAY_DISP++, (s32*)titleCtx->texture, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, spC0, spB8, ((sp38 * 2) + spC0) - 4, spB8 + (spC8 * 4) - 1, G_TX_RENDERTILE,
                            0, 0, 1 << 10, 1 << 10);

        spC8 = titleCtx->height - spC8;

        if (spC8 > 0) {
            gDPLoadTextureBlock(OVERLAY_DISP++, (s32)titleCtx->texture + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8,
                                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, spC0, spB4, ((sp38 * 2) + spC0) - 4, spB4 + (spC8 * 4) - 1,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }

        CLOSE_DISPS(gameState->gfxCtx);
    }
}

s32 func_800B6434(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if ((globalCtx->actorCtx.titleCtxt.delayTimer != 0) || (globalCtx->actorCtx.titleCtxt.alpha != 0)) {
        titleCtx->durationTimer = 0;
        titleCtx->delayTimer = 0;
        return false;
    }
    return true;
}

void func_800B6468(GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk1F5 = 0;
}

void func_800B6474(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk1F5 != 0) {
        globalCtx->actorCtx.unk1F5--;
    }
}

s32 func_800B648C(GlobalContext* globalCtx, s32 arg1, s32 arg2, f32 arg3, Vec3f* arg4) {
    if ((globalCtx->actorCtx.unk1F5 != 0) && (arg3 < globalCtx->actorCtx.unk1F8)) {
        return 0;
    }

    globalCtx->actorCtx.unk1F4 = arg1;
    globalCtx->actorCtx.unk1F5 = arg2;
    globalCtx->actorCtx.unk1F8 = arg3;
    Math_Vec3f_Copy(&globalCtx->actorCtx.unk1FC, arg4);
    return 1;
}

f32 func_800B64FC(GlobalContext* globalCtx, f32 arg1, Vec3f* arg2, u32* arg3) {
    f32 temp_f8;

    if ((globalCtx->actorCtx.unk1F5 == 0) || (arg1 == 0.0f)) {
        return -1.0f;
    }

    temp_f8 = Math_Vec3f_DistXYZ(&globalCtx->actorCtx.unk1FC, arg2) / arg1;
    *arg3 = globalCtx->actorCtx.unk1F4;
    return globalCtx->actorCtx.unk1F8 - temp_f8;
}

void* func_800B6584(GlobalContext* globalCtx, s16 arg1, void* arg2, size_t arg3) {
    ActorContext_unk_20C* sp1C = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (sp1C->unk_0 == 0) {
            if (arg2 == NULL) {
                arg2 = zelda_malloc(arg3);
                if (arg2 == NULL) {
                    return NULL;
                }
                sp1C->unk_2 = 1;
            }

            sp1C->unk_0 = arg1;
            sp1C->unk_4 = arg2;
            return arg2;
        }
        sp1C++;
    }

    return NULL;
}

void* func_800B6608(GlobalContext* globalCtx, s16 arg1) {
    ActorContext_unk_20C* sp1C = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (arg1 == sp1C->unk_0) {
            sp1C->unk_0 = 0;
            if (sp1C->unk_2 != 0) {
                zelda_free(sp1C->unk_4);
                sp1C->unk_2 = 0;
            }
            return sp1C->unk_4;
        }
        sp1C++;
    }

    return NULL;
}

void* func_800B6680(GlobalContext* globalCtx, s16 arg1) {
    ActorContext_unk_20C* phi_v1 = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (arg1 == phi_v1->unk_0) {
            return phi_v1->unk_4;
        }

        phi_v1++;
    }

    return NULL;
}

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}

void Actor_SetWorldToHome(Actor* actor) {
    actor->world = actor->home;
}

void Actor_SetFocus(Actor* actor, f32 height) {
    actor->focus.pos.x = actor->world.pos.x;
    actor->focus.pos.y = actor->world.pos.y + height;
    actor->focus.pos.z = actor->world.pos.z;

    actor->focus.rot.x = actor->world.rot.x;
    actor->focus.rot.y = actor->world.rot.y;
    actor->focus.rot.z = actor->world.rot.z;
}

void Actor_SetWorldRotToShape(Actor* actor) {
    actor->world.rot = actor->shape.rot;
}

void Actor_SetShapeRotToWorld(Actor* actor) {
    actor->shape.rot = actor->world.rot;
}

void Actor_SetScale(Actor* actor, f32 scale) {
    actor->scale.z = scale;
    actor->scale.y = scale;
    actor->scale.x = scale;
}

void Actor_SetObjectDependency(GlobalContext* globalCtx, Actor* actor) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}

void Actor_Init(Actor* actor, GlobalContext* globalCtx) {
    Actor_SetWorldToHome(actor);
    Actor_SetShapeRotToWorld(actor);
    Actor_SetFocus(actor, 0.0f);
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01f);
    actor->targetMode = 3;
    actor->minVelocityY = -20.0f;

    actor->xyzDistToPlayerSq = FLT_MAX;
    actor->uncullZoneForward = 1000.0f;
    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->hintId = 255;

    CollisionCheck_InitInfo(&actor->colChkInfo);
    actor->floorBgId = BGCHECK_SCENE;

    ActorShape_Init(&actor->shape, 0.0f, NULL, 0.0f);
    if (Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
        Actor_SetObjectDependency(globalCtx, actor);
        actor->init(actor, globalCtx);
        actor->init = NULL;
    }
}

void Actor_Destroy(Actor* actor, GlobalContext* globalCtx) {
    if (actor->init == NULL) {
        if (actor->destroy != NULL) {
            actor->destroy(actor, globalCtx);
            actor->destroy = NULL;
        }
    }
}

f32 actorMovementScale = 1.0f;

void Actor_SetMovementScale(s32 scale) {
    actorMovementScale = scale * 0.5f;
}

void Actor_ApplyMovement(Actor* actor) {
    f32 speedRate = actorMovementScale;

    actor->world.pos.x += ((actor->velocity.x * speedRate) + actor->colChkInfo.displacement.x);
    actor->world.pos.y += ((actor->velocity.y * speedRate) + actor->colChkInfo.displacement.y);
    actor->world.pos.z += ((actor->velocity.z * speedRate) + actor->colChkInfo.displacement.z);
}

void Actor_SetVelocityYRotationAndGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_SinS(actor->world.rot.y);
    actor->velocity.z = actor->speedXZ * Math_CosS(actor->world.rot.y);

    actor->velocity.y += actor->gravity;
    if (actor->velocity.y < actor->minVelocityY) {
        actor->velocity.y = actor->minVelocityY;
    }
}

void Actor_MoveForward(Actor* actor) {
    Actor_SetVelocityYRotationAndGravity(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotation(Actor* actor) {
    f32 velX = Math_CosS(actor->world.rot.x) * actor->speedXZ;

    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotation(Actor* actor) {
    Actor_SetVelocityXYRotation(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotationReverse(Actor* actor) {
    f32 velX = Math_CosS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor) {
    Actor_SetVelocityXYRotationReverse(actor);
    Actor_ApplyMovement(actor);
}

void func_800B6C04(Actor* actor, f32 speed) {
    actor->speedXZ = Math_CosS(actor->world.rot.x) * speed;
    actor->velocity.y = -Math_SinS(actor->world.rot.x) * speed;
}

void func_800B6C58(Actor* actor, SkelAnime* skelAnime) {
    Vec3f pos;

    func_80137748(skelAnime, &pos, actor->shape.rot.y);
    actor->world.pos.x += pos.x * actor->scale.x;
    actor->world.pos.y += pos.y * actor->scale.y;
    actor->world.pos.z += pos.z * actor->scale.z;
}

s16 Actor_YawBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->world.pos, &to->world.pos);
}

s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->focus.pos, &to->focus.pos);
}

s16 Actor_YawToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Yaw(&actor->world.pos, point);
}

s16 Actor_PitchBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->world.pos, &to->world.pos);
}

s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->focus.pos, &to->focus.pos);
}

s16 Actor_PitchToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Pitch(&actor->world.pos, point);
}

f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXYZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXYZ(&actor->world.pos, point);
}

f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXZ(&actor->world.pos, point);
}

/** Performs the affine (linear) transformation from world coordinates to actor coordinates
 *
 * @param[in]  actor  The actor whose coordinate system to transform to.
 * @param[out] offset The transformed coordinates.
 * @param[in]  point  The point to transform to actor coordinates.
 */
void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point) {
    f32 cos_rot_y;
    f32 sin_rot_y;
    f32 imm_x;
    f32 imm_z;

    cos_rot_y = Math_CosS(actor->shape.rot.y);
    sin_rot_y = Math_SinS(actor->shape.rot.y);
    imm_x = point->x - actor->world.pos.x;
    imm_z = point->z - actor->world.pos.z;
    offset->x = ((imm_x * cos_rot_y) - (imm_z * sin_rot_y));
    offset->z = ((imm_z * cos_rot_y) + (imm_x * sin_rot_y));
    offset->y = point->y - actor->world.pos.y;
}

f32 Actor_HeightDiff(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

void func_800B6F20(GlobalContext* globalCtx, Input* input, f32 arg2, s16 arg3) {
    s16 sp26 = arg3 - func_800DFC68(GET_ACTIVE_CAM(globalCtx));

    input->cur.stick_x = -Math_SinS(sp26) * arg2;
    input->rel.stick_x = input->cur.stick_x;
    input->cur.stick_y = Math_CosS(sp26) * arg2;
    input->rel.stick_y = input->cur.stick_y;
}

f32 Player_GetHeight(Player* player) {
    f32 offset;

    if (player->stateFlags1 & 0x800000) {
        offset = 32.0f;
    } else {
        offset = 0.0f;
    }

    switch (player->transformation) {
        default:
        case PLAYER_FORM_FIERCE_DEITY:
            return offset + 124.0f;
        case PLAYER_FORM_GORON:
            return offset + ((player->stateFlags3 & 0x1000) ? 34.0f : 80.0f);
        case PLAYER_FORM_ZORA:
            return offset + 68.0f;
        case PLAYER_FORM_DEKU:
            return offset + 36.0f;
        case PLAYER_FORM_HUMAN:
            return offset + 44.0f;
    }
}

f32 Player_GetRunSpeedLimit(Player* player) {
    if (player->stateFlags1 & 0x800000) {
        return 15.0f;
    } else if (player->stateFlags1 & 0x8000000) {
        return (R_RUN_SPEED_LIMIT / 100.0f) * 0.6f;
    } else {
        return R_RUN_SPEED_LIMIT / 100.0f;
    }
}

s32 func_800B7118(Player* player) {
    return player->stateFlags1 & 8;
}

s32 func_800B7128(Player* player) {
    return func_800B7118(player) && player->unk_ACC;
}

s32 func_800B715C(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->stateFlags2 & 8;
}

void func_800B7170(GlobalContext* globalCtx, Player* player) {
    if ((globalCtx->roomCtx.currRoom.unk3 != 4) && (player->actor.id == ACTOR_PLAYER)) {
        EnHorse* rideActor = (EnHorse*)player->rideActor;

        if ((rideActor != NULL) && !(rideActor->unk_1EC & 0x10)) {
            func_800DFAC8(Play_GetCamera(globalCtx, 0), 4);
        }
    }
}

void Actor_MountHorse(GlobalContext* globalCtx, Player* player, Actor* horse) {
    player->rideActor = horse;
    player->stateFlags1 |= 0x800000;
    horse->child = &player->actor;
}

s32 func_800B7200(Player* player) {
    return (player->stateFlags1 & 0x20000080) || (player->csMode != 0);
}

void func_800B722C(GameState* gameState, Player* player) {
    func_800F40A0(gameState, player);
}

s32 func_800B724C(GlobalContext* globalCtx, Actor* actor, u8 csMode) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->csMode == 5) || ((csMode == 6) && (player->csMode == 0))) {
        return false;
    }

    player->csMode = csMode;
    player->unk_398 = actor;
    player->unk_3BA = 0;
    return true;
}

u32 func_800B7298(GlobalContext* globalCtx, Actor* actor, u8 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    if (func_800B724C(globalCtx, actor, arg2)) {
        player->unk_3BA = 1;
        return true;
    }
    return false;
}

void func_800B72E0(DynaPolyActor* dyna) {
    dyna->unk14C = 0.0f;
    dyna->unk148 = 0.0f;
}

void func_800B72F8(DynaPolyActor* dyna, f32 a1, s16 a2) {
    dyna->unk150 = a2;
    dyna->unk148 += a1;
}

s32 Actor_IsPlayerFacingActor(Actor* actor, s16 tolerance, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yawDiff = BINANG_ADD(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;

    if (ABS_ALT(yawDiff) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 angle = BINANG_ROT180(Actor_YawBetweenActors(actor, other));
    s16 dist;

    dist = angle - other->shape.rot.y;
    if (ABS_ALT(dist) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingPlayer(Actor* actor, s16 angle) {
    s16 dist = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(dist) < angle) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;

    if (ABS_ALT(dist) < tolerance) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingPlayerAndWithinRange(Actor* actor, f32 range, s16 tolerance) {
    s16 yaw = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(yaw) < tolerance) {
    label:;
        if (sqrtf(SQ(actor->xzDistToPlayer) + SQ(actor->yDistToPlayer)) < range) {
            return 1;
        }
    }
    return 0;
}

s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance) {
    s16 dist;

    if (Actor_DistanceBetweenActors(actor, other) < range) {
        dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
        if (ABS_ALT(dist) < tolerance) {
            return 1;
        }
    }
    return 0;
}

void func_800B75A0(CollisionPoly* param_1, Vec3f* param_2, s16* param_3) {
    param_2->x = param_1->normal.x * (1.0f / 0x7FFF);
    param_2->y = param_1->normal.y * (1.0f / 0x7FFF);
    param_2->z = param_1->normal.z * (1.0f / 0x7FFF);
    *param_3 = Math_FAtan2F(param_2->z, param_2->x);
}

s32 func_800B761C(Actor* actor, f32 arg1, s32 arg2) {
    if (actor->bgCheckFlags & 0x01) {
        actor->bgCheckFlags &= ~0x01;
        actor->bgCheckFlags |= 0x04;
        if ((actor->velocity.y < 0.0f) && (arg2 & 0x10)) {
            actor->velocity.y = 0.0f;
        }
        return false;
    }
    return true;
}

s32 func_800B7678(GlobalContext* globalCtx, Actor* actor, Vec3f* arg2, s32 arg3) {
    f32 temp_f0;
    s32 sp38;

    arg2->y += (arg3 & 0x800) ? 10.0f : 50.0f;

    actor->floorHeight = func_800C4188(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &sp38, actor, arg2);
    actor->bgCheckFlags &= ~(0x80 | 0x04 | 0x02);
    if (actor->floorHeight <= BGCHECK_Y_MIN) {
        return func_800B761C(actor, BGCHECK_Y_MIN, arg3);
    }

    temp_f0 = actor->floorHeight - actor->world.pos.y;
    actor->floorBgId = sp38;
    if ((temp_f0 >= 0.0f) || (((actor->bgCheckFlags & 1)) && !(actor->bgCheckFlags & 0x800) && (temp_f0 >= -11.0f) &&
                              (actor->velocity.y < 0.0f))) {
        actor->bgCheckFlags |= 0x80;

        if (actor->bgCheckFlags & 0x10) {
            if (sp38 != D_801ED8B4) {
                if (temp_f0 > 15.0f) {
                    actor->bgCheckFlags |= 0x100;
                }
            } else {
                actor->world.pos.x = actor->prevPos.x;
                actor->world.pos.z = actor->prevPos.z;
            }
        }
        actor->world.pos.y = actor->floorHeight;
        if (actor->velocity.y <= 0.0f) {
            if (!(actor->bgCheckFlags & 1)) {
                actor->bgCheckFlags |= 0x02;
            } else if ((arg3 & 8) && (actor->gravity < 0.0f)) {
                actor->velocity.y = -4.0f;
            } else if (!(arg3 & 0x100)) {
                actor->velocity.y = 0.0f;
            }

            actor->bgCheckFlags |= 0x01;
            BgCheck2_AttachToMesh(&globalCtx->colCtx, actor, (s32)actor->floorBgId);
        }
    } else {
        return func_800B761C(actor, temp_f0, arg3);
    }

    return 1;
}

void Actor_UpdateBgCheckInfo(GlobalContext* globalCtx, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, u32 flags) {
    f32 sp94;
    s32 pad;
    Vec3f sp84;

    sp94 = actor->world.pos.y - actor->prevPos.y;
    if ((actor->floorBgId != 0x32) && (actor->bgCheckFlags & 1)) {
        BgCheck2_UpdateActorAttachedToMesh(&globalCtx->colCtx, actor->floorBgId, actor);
    }

    if (flags & 1) {
        s32 sp80;

        actor->bgCheckFlags &= ~0x1000;
        if ((!(flags & 0x80) &&
             ((func_800C4D3C(&globalCtx->colCtx, &sp84, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                             &actor->wallPoly, &sp80, actor, wallCheckHeight) != 0))) ||
            ((flags & 0x80) &&
             ((func_800C4DA4(&globalCtx->colCtx, &sp84, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                             &actor->wallPoly, &sp80, actor, wallCheckHeight) != 0)))) {
            CollisionPoly* sp7C = actor->wallPoly;

            actor->bgCheckFlags |= 0x08;
            if ((flags & 0x200) && ((actor->bgCheckFlags & 0x1000) != 0) && ((s32)sp7C->normal.y > 0) &&
                ((sqrtf(SQ(actor->colChkInfo.displacement.x) + SQ(actor->colChkInfo.displacement.y) +
                        SQ(actor->colChkInfo.displacement.z)) < 10.0f))) {
                actor->bgCheckFlags &= ~0x08;
            } else if (actor->bgCheckFlags & 0x08) {
                Math_Vec3f_Copy(&actor->world.pos, &sp84);
            }

            actor->wallYaw = Math_FAtan2F(sp7C->normal.z, sp7C->normal.x);
            actor->wallBgId = sp80;
        } else {
            actor->bgCheckFlags &= ~0x08;
        }
    }

    sp84.x = actor->world.pos.x;
    sp84.z = actor->world.pos.z;
    if (flags & 2) {
        f32 sp78;

        sp84.y = actor->prevPos.y + 4.0f;
        if (func_800C4F84(&globalCtx->colCtx, &sp78, &sp84, (ceilingCheckHeight + sp94) - 4.0f, &D_801ED8B0,
                          &D_801ED8B4, actor) != 0) {
            actor->bgCheckFlags |= 0x10;
            actor->world.pos.y = (sp78 + sp94) - 4.0f;
        } else {
            actor->bgCheckFlags &= ~0x10;
        }
    }
    if (flags & 4) {
        WaterBox* sp74;
        f32 sp70;

        sp84.y = actor->prevPos.y;
        func_800B7678(globalCtx, actor, &sp84, flags);
        sp70 = actor->world.pos.y;
        if (func_800CA1AC(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &sp70, &sp74) != 0) {
            actor->yDistToWater = sp70 - actor->world.pos.y;
            if (actor->yDistToWater <= 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if ((actor->bgCheckFlags & 0x20) == 0) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if ((flags & 0x40) == 0) {
                    Vec3f sp64;

                    sp64.x = actor->world.pos.x;
                    sp64.y = sp70;
                    sp64.z = actor->world.pos.z;
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 0);
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 4);
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 8);
                }
            } else {
                actor->bgCheckFlags &= ~0x40;
            }
        } else {
            actor->bgCheckFlags &= ~(0x40 | 0x20);
            actor->yDistToWater = BGCHECK_Y_MIN;
        }
    }

    if (flags & 0x400) {
        WaterBox* sp60;
        f32 sp5C = actor->world.pos.y;

        if (func_800CA1AC(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &sp5C, &sp60) != 0) {
            actor->yDistToWater = sp5C - actor->world.pos.y;
            if (actor->yDistToWater < 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if (!(actor->bgCheckFlags & 0x20)) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if (!(flags & 0x40)) {
                    Vec3f sp50;

                    sp50.x = actor->world.pos.x;
                    sp50.y = sp5C;
                    sp50.z = actor->world.pos.z;
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 0);
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 4);
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 8);
                }
            } else {
                actor->bgCheckFlags &= ~0x40;
            }
        } else {
            actor->bgCheckFlags &= ~(0x40 | 0x20);
            actor->yDistToWater = BGCHECK_Y_MIN;
        }
    }
}

Gfx* func_800B7E04(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx, Gfx* dl, Hilite** hilite) {
    LookAt* lookAt;
    f32 correctedEyeX;

    lookAt = GRAPH_ALLOC(gfxCtx, sizeof(LookAt));

    correctedEyeX = (eye->x == object->x) && (eye->z == object->z) ? eye->x + 0.001f : eye->x;

    *hilite = GRAPH_ALLOC(gfxCtx, sizeof(Hilite));

    guLookAtHilite(&D_801ED8E0, lookAt, *hilite, correctedEyeX, eye->y, eye->z, object->x, object->y, object->z, 0.0f,
                   1.0f, 0.0f, lightDir->x, lightDir->y, lightDir->z, lightDir->x, lightDir->y, lightDir->z, 0x10,
                   0x10);

    gSPLookAt(dl++, lookAt);
    gDPSetHilite1Tile(dl++, 1, *hilite, 0x10, 0x10);

    return dl;
}

Hilite* func_800B7FE0(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* sp2C;

    OPEN_DISPS(gfxCtx);

    POLY_OPA_DISP = func_800B7E04(object, eye, lightDir, gfxCtx, POLY_OPA_DISP, &sp2C);

    CLOSE_DISPS(gfxCtx);

    return sp2C;
}

Hilite* func_800B8018(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* sp2C;

    OPEN_DISPS(gfxCtx);

    POLY_XLU_DISP = func_800B7E04(object, eye, lightDir, gfxCtx, POLY_XLU_DISP, &sp2C);

    CLOSE_DISPS(gfxCtx);

    return sp2C;
}

void func_800B8050(Actor* actor, GlobalContext* globalCtx, s32 flag) {
    Hilite* hilite = func_800BCBF4(&actor->world.pos, globalCtx);

    if (flag != 0) {
        Gfx* displayListHead;
        Gfx* displayList = GRAPH_ALLOC(globalCtx->state.gfxCtx, 2 * sizeof(Gfx));

        displayListHead = displayList;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gDPSetHilite1Tile(displayListHead++, 1, hilite, 0x10, 0x10);
        gSPEndDisplayList(displayListHead);
        gSPSegment(POLY_OPA_DISP++, 0x07, displayList);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_800B8118(Actor* actor, GlobalContext* globalCtx, s32 flag) {
    Hilite* hilite = func_800BCC68(&actor->world.pos, globalCtx);

    if (flag != 0) {
        Gfx* displayListHead;
        Gfx* displayList = GRAPH_ALLOC(globalCtx->state.gfxCtx, 2 * sizeof(Gfx));

        displayListHead = displayList;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gDPSetHilite1Tile(displayListHead++, 1, hilite, 0x10, 0x10);
        gSPEndDisplayList(displayListHead);
        gSPSegment(POLY_XLU_DISP++, 0x07, displayList);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

PosRot* Actor_GetFocus(PosRot* dest, Actor* actor) {
    *dest = actor->focus;

    return dest;
}

PosRot* Actor_GetWorld(PosRot* dest, Actor* actor) {
    *dest = actor->world;

    return dest;
}

PosRot* Actor_GetWorldPosShapeRot(PosRot* dest, Actor* actor) {
    PosRot sp1C;

    Math_Vec3f_Copy(&sp1C.pos, &actor->world.pos);
    if (actor->id == ACTOR_PLAYER) {
        Player* player = (Player*)actor;

        sp1C.pos.y += player->unk_AC0 * actor->scale.y;
    }
    sp1C.rot = actor->shape.rot;
    *dest = sp1C;

    return dest;
}

#ifdef NON_MATCHING
// wrong float register
f32 func_800B82EC(Actor* actor, Player* player, s16 arg2) {
    f32 temp_f12;
    s16 temp_v0;
    s16 temp_v1;
    s32 phi_v1;

    temp_v0 = BINANG_SUB(BINANG_SUB(actor->yawTowardsPlayer, 0x8000), arg2);
    temp_v1 = ABS_ALT(temp_v0);

    if (player->unk_730 != NULL) {
        if ((temp_v1 > 0x4000) || ((actor->flags & 0x8000000))) {
            // return FLT_MAX;
            return 3.4028235e38f;
        }

        return actor->xyzDistToPlayerSq - (actor->xyzDistToPlayerSq * 0.8f * ((0x4000 - temp_v1) * 0.000030517578f));
    }

    if (temp_v1 >= 0x2AAB) {
        // return FLT_MAX;
        return 3.4028235e38f;
    }
    return actor->xyzDistToPlayerSq;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B82EC.s")
#endif

TargetRangeParams D_801AECF0[] = {
    TARGET_RANGE(70, 140),   TARGET_RANGE(170, 255),    TARGET_RANGE(280, 5600),      TARGET_RANGE(350, 525),
    TARGET_RANGE(700, 1050), TARGET_RANGE(1000, 1500),  TARGET_RANGE(100, 105.36842), TARGET_RANGE(140, 163.33333),
    TARGET_RANGE(240, 576),  TARGET_RANGE(280, 280000), TARGET_RANGE(2500, 3750),
};

s32 func_800B83BC(Actor* actor, f32 arg1) {
    return arg1 < D_801AECF0[actor->targetMode].rangeSq;
}

s32 func_800B83F8(Actor* actor, Player* player, s32 flag) {
    if ((actor->update == NULL) || !(actor->flags & 1) || (actor->flags & 0x8000000)) {
        return 1;
    }

    if (!flag) {
        s16 yaw = BINANG_SUB(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;
        s16 phi_v1 = ABS_ALT(yaw);
        f32 dist;

        if ((player->unk_730 == NULL) && (phi_v1 >= 0x2AAB)) {
            dist = FLT_MAX;
        } else {
            dist = actor->xyzDistToPlayerSq;
        }

        return !func_800B83BC(actor, D_801AECF0[actor->targetMode].leashScale * dist);
    }
    return 0;
}

s16 D_801AED48[] = {
    0x0101, 0x0141, 0x0111, 0x0151, 0x0105, 0x0145, 0x0115, 0x0155,
};

s32 Actor_RequestTalk(Actor* actor, GameState* gameState) {
    if (actor->flags & 0x100) {
        actor->flags &= ~0x100;
        return true;
    }

    return false;
}

s32 func_800B8500(Actor* actor, GameState* gameState, f32 xzRange, f32 yRange, s32 exchangeItemId) {
    Player* player = GET_PLAYER(gameState);

    if ((player->actor.flags & 0x100) || ((exchangeItemId > EXCH_ITEM_NONE) && Player_InCsMode(gameState)) ||
        (!actor->isTargeted &&
         ((fabsf(actor->yDistToPlayer) > fabsf(yRange)) || ((actor->xzDistToPlayer > player->targetActorDistance)) ||
          (xzRange < actor->xzDistToPlayer)))) {
        return false;
    }

    player->targetActor = actor;
    player->targetActorDistance = actor->xzDistToPlayer;
    player->exchangeItemId = exchangeItemId;

    ActorCutscene_SetIntentToPlay(0x7C);
    return true;
}

s32 func_800B85E0(Actor* actor, GameState* gameState, f32 radius, s32 exchangeItemId) {
    return func_800B8500(actor, gameState, radius, radius, exchangeItemId);
}

s32 func_800B8614(Actor* actor, GameState* gameState, f32 radius) {
    return func_800B85E0(actor, gameState, radius, EXCH_ITEM_NONE);
}

s32 func_800B863C(Actor* actor, GameState* gameState) {
    f32 cylRadius = actor->colChkInfo.cylRadius + 50.0f;

    return func_800B8614(actor, gameState, cylRadius);
}

s32 func_800B867C(Actor* actor, GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    if (func_80152498(&globalCtx->msgCtx) == 2) {
        actor->flags &= ~0x100;
        return 1;
    }

    return 0;
}

/**
 * Changes the actor the Player is focussing on
 * Fails if Player is not already focussing on an actor
 */
s32 func_800B86C8(Actor* actor1, GameState* gameState, Actor* actor2) {
    Actor* targetActor;
    Player* player = GET_PLAYER(gameState);

    targetActor = player->targetActor;

    if ((player->actor.flags & 0x100) && (targetActor != NULL)) {
        player->targetActor = actor2;
        player->unk_730 = actor2;
        return true;
    }

    return false;
}

s32 Player_GetExchangeItemId(GameState* gameState) {
    Player* player = GET_PLAYER(gameState);

    return player->exchangeItemId;
}

s32 func_800B8718(Actor* actor, GameState* gameState) {
    if (actor->flags & 0x20000000) {
        actor->flags &= ~0x20000000;
        return true;
    }

    return false;
}

#ifdef NON_MATCHING
void func_800B874C(Actor* actor, GameState* gameState, f32 xzRange, f32 yRange) {
    Player* player = GET_PLAYER(gameState);

    if ((player->actor.flags & 0x20000000) || ((Player_InCsMode(gameState) != 0)) ||
        (yRange < fabsf(actor->yDistToPlayer)) || ((player->unk_A94 < actor->xzDistToPlayer)) ||
        (xzRange < actor->xzDistToPlayer)) {
        return;
    }

    player->unk_A90 = actor;
    player->unk_A94 = actor->xzDistToPlayer;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B874C.s")
#endif

void func_800B8804(Actor* actor, GameState* gameState, f32 xzRange) {
    func_800B874C(actor, gameState, xzRange, 20.0f);
}

void func_800B882C(Actor* actor, GameState* gameState) {
    f32 cylRadius = actor->colChkInfo.cylRadius + 50.0f;

    func_800B8804(actor, gameState, cylRadius);
}

s32 func_800B886C(Actor* actor, GameState* gameState) {
    if (!(GET_PLAYER(gameState)->actor.flags & 0x20000000)) {
        return 1;
    }
    return 0;
}

void func_800B8898(GlobalContext* globalCtx, Actor* actor, s16* arg2, s16* arg3) {
    Vec3f sp1C;
    f32 sp18;

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp1C, &sp18);
    *arg2 = (sp1C.x * sp18 * 160.0f) + 160.0f;
    *arg3 = (sp1C.y * sp18 * -120.0f) + 120.0f;
}

s32 func_800B8934(GameState* gameState, Actor* actor) {
    Vec3f sp2C;
    f32 sp28;
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s32 pad;

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp2C, &sp28);

    return (sp2C.x * sp28 >= -1.0f) && (sp2C.x * sp28 <= 1.0f) && (sp2C.y * sp28 >= -1.0f) && (sp2C.y * sp28 <= 1.0f);
}

s32 Actor_HasParent(Actor* actor, GlobalContext* globalCtx) {
    if (actor->parent != NULL) {
        return true;
    } else {
        return false;
    }
}

/**
 * Allows to pick up an item (GetItem), lift an actor or catch various actors in bottles
 * within the specified range.
 *
 * GI_NONE is usually used as a special case to lift an actor
 * GI_MAX is usually used to catch an actor in a bottle
 */
s32 Actor_PickUp(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x3C7080) && Player_GetExplosiveHeld(player) < 0) {
        if ((actor->xzDistToPlayer <= xzRange) && (fabsf(actor->yDistToPlayer) <= fabsf(yRange))) {
            if ((getItemId == GI_MASK_CIRCUS_LEADER || getItemId == GI_PENDANT_OF_MEMORIES ||
                 getItemId == GI_LAND_TITLE_DEED ||
                 (((player->heldActor != NULL) || (actor == player->targetActor)) &&
                  (getItemId > GI_NONE && getItemId < GI_MAX))) ||
                (!(player->stateFlags1 & 0x20000800))) {
                s16 yawDiff = actor->yawTowardsPlayer - player->actor.shape.rot.y;
                s32 absYawDiff = ABS_ALT(yawDiff);

                if ((getItemId != GI_NONE) || (player->getItemDirection < absYawDiff)) {
                    player->getItemId = getItemId;
                    player->interactRangeActor = actor;
                    player->getItemDirection = absYawDiff;

                    if (getItemId > GI_NONE && getItemId < GI_MAX) {
                        ActorCutscene_SetIntentToPlay(globalCtx->unk_1879C[1]);
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

s32 Actor_PickUpNearby(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return Actor_PickUp(actor, globalCtx, getItemId, 50.0f, 10.0f);
}

s32 Actor_LiftActor(Actor* actor, GlobalContext* globalCtx) {
    return Actor_PickUpNearby(actor, globalCtx, GI_NONE);
}

s32 Actor_PickUpFar(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return Actor_PickUp(actor, globalCtx, getItemId, 9999.9f, 9999.9f);
}

s32 Actor_HasNoParent(Actor* actor, GlobalContext* globalCtx) {
    if (!actor->parent) {
        return true;
    } else {
        return false;
    }
}

void func_800B8C20(Actor* actorA, Actor* actorB, GlobalContext* globalCtx) {
    Actor* parent = actorA->parent;

    if (parent->id == ACTOR_PLAYER) {
        Player* player = (Player*)parent;

        player->heldActor = actorB;
        player->interactRangeActor = actorB;
    }

    parent->child = actorB;
    actorB->parent = parent;
    actorA->parent = NULL;
}

void func_800B8C50(Actor* actor, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (actor->xyzDistToPlayerSq < player->unk_AA0) {
        player->unk_AA0 = actor->xyzDistToPlayerSq;
    }
}

s32 Actor_IsMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child != NULL) {
        return true;
    }

    return false;
}

s32 Actor_SetRideActor(GlobalContext* globalCtx, Actor* horse, s32 mountSide) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x003C7880)) {
        player->rideActor = horse;
        player->mountSide = mountSide;
        ActorCutscene_SetIntentToPlay(0x7C);
        return true;
    }

    return false;
}

s32 Actor_NotMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child == NULL) {
        return true;
    }

    return false;
}

void func_800B8D10(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5, u32 arg6) {
    Player* player = GET_PLAYER(globalCtx);

    player->unk_B74 = arg6;
    player->unk_B75 = arg5;
    player->unk_B78 = arg2;
    player->unk_B76 = arg3;
    player->unk_B7C = arg4;
}

void func_800B8D50(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 yaw, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, yaw, arg4, 3, arg5);
}

void func_800B8D98(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8D50(globalCtx, actor, arg2, arg3, arg4, 0);
}

void func_800B8DD4(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, arg3, arg4, 2, arg5);
}

void func_800B8E1C(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8DD4(globalCtx, actor, arg2, arg3, arg4, 0);
}

void func_800B8E58(Player* player, u16 sfxId) {
    if (player->currentMask == PLAYER_MASK_GIANTS_MASK) {
        func_8019F170(&player->actor.projectedPos, sfxId);
    } else {
        Audio_PlaySoundGeneral(sfxId, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
    }
}

void Audio_PlayActorSound2(Actor* actor, u16 sfxId) {
    func_8019F1C0(&actor->projectedPos, sfxId);
}

void func_800B8EF4(GlobalContext* globalCtx, Actor* actor) {
    u32 sfxId;

    if (actor->bgCheckFlags & 0x20) {
        if (actor->yDistToWater < 20.0f) {
            sfxId = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            sfxId = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
    } else {
        sfxId = func_800C9BDC(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    }

    func_8019F1C0(&actor->projectedPos, NA_SE_EV_BOMB_BOUND);
    func_8019F1C0(&actor->projectedPos, sfxId + SFX_FLAG);
}

void func_800B8F98(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x02;
}

void func_800B8FC0(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 4;
}

void func_800B8FE8(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x08;
}

void func_800B9010(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x01;
}

void func_800B9038(Actor* actor, s32 arg1) {
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x10;

    if (arg1 < 40) {
        actor->sfx = 3;
    } else if (arg1 < 100) {
        actor->sfx = 2;
    } else {
        actor->sfx = 1;
    }
}

void func_800B9084(Actor* actor) {
    actor->unk39 |= 0x20;
}

void func_800B9098(Actor* actor) {
    actor->unk39 |= 0x40;
}

s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, CollisionPoly* polygon, s32 index, s32 arg4) {
    if (func_800C99D4(&globalCtx->colCtx, polygon, index) == 8) {
        return 1;
    }
    return 0;
}

void func_800B90F4(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk3 != 0) {
        globalCtx->actorCtx.unk3 = 0;
        func_80115D5C(&globalCtx->state);
    }
}

void func_800B9120(ActorContext* actorCtx) {
    s32 phi_v0 = CURRENT_DAY * 2;

    if (gSaveContext.time < CLOCK_TIME(6, 0) || gSaveContext.time > CLOCK_TIME(18, 0)) {
        phi_v0++;
    }
    actorCtx->unkC = (0x200 >> phi_v0);
}

// Actor_InitContext // OoT's func_800304DC
void func_800b9170(GameState* gameState, ActorContext* actorCtx, ActorEntry* actorEntry) {
    ActorOverlay* overlayEntry;
    u32* temp_a2_2;
    s32 i;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    gSaveContext.weekEventReg[92] |= 0x80;
    temp_a2_2 = gSaveContext.cycleSceneFlags[convert_scene_number_among_shared_scenes(globalCtx->sceneNum)];

    bzero(actorCtx, sizeof(ActorContext));
    ActorOverlayTable_Init();
    Matrix_MtxFCopy(&globalCtx->mf_187FC, &D_801D1E20);
    Matrix_MtxFCopy(&globalCtx->projectionMatrix, &D_801D1E20);

    overlayEntry = gActorOverlayTable;
    for (i = 0; i < ARRAY_COUNT(gActorOverlayTable); i++) {
        overlayEntry->loadedRamAddr = NULL;
        overlayEntry->numLoaded = 0;
        overlayEntry++;
    }

    actorCtx->flags.chest = temp_a2_2[0];
    actorCtx->flags.swch[0] = temp_a2_2[1];
    actorCtx->flags.swch[1] = temp_a2_2[2];
    if (globalCtx->sceneNum == 0x18) {
        temp_a2_2 = gSaveContext.cycleSceneFlags[globalCtx->sceneNum];
    }
    actorCtx->flags.collectible[0] = temp_a2_2[4];
    actorCtx->flags.clearedRoom = temp_a2_2[3];

    TitleCard_ContextInit(gameState, &actorCtx->titleCtxt);
    func_800B6468(globalCtx);

    actorCtx->absoluteSpace = NULL;

    Actor_SpawnEntry(actorCtx, actorEntry, gameState);
    Actor_TargetContextInit(&actorCtx->targetContext, actorCtx->actorList[ACTORCAT_PLAYER].first, globalCtx);
    func_800B9120(actorCtx);
    Fault_AddClient(&D_801ED8A0, (void*)Actor_PrintLists, actorCtx, NULL);
    func_800B722C(gameState, (Player*)actorCtx->actorList[ACTORCAT_PLAYER].first);
}

#ifdef NON_EQUIVALENT
void func_800B9334(GlobalContext* globalCtx, ActorContext* actorCtx) {
    ActorEntry* temp_s0;
    s16 temp_fp;
    s16 temp_v1;
    s32 temp_s1;
    s32 temp_v0;
    ActorEntry* phi_s0;
    s32 phi_v0;
    s32 phi_s1;

    if (globalCtx->numSetupActors > 0) {
        phi_s0 = globalCtx->setupActorList;
        temp_fp = actorCtx->unkC;
        func_800B9120(actorCtx);
        func_800BA8B8(globalCtx, &globalCtx->actorCtx);

        for (phi_s1 = 0; phi_s1 < globalCtx->numSetupActors; phi_s1++) {
            phi_v0 = ((phi_s0->rot.x & 7) << 7) | (phi_s0->rot.z & 0x7F);
            if (phi_v0 == 0) {
                phi_v0 = 0x3FF;
            }
            if (((phi_v0 & temp_fp) == 0) && ((actorCtx->unkC & phi_v0) != 0) &&
                (((gSaveContext.eventInf[1] & 0x80) == 0) || ((phi_v0 & ((actorCtx->unkC * 2) & 0x2FF)) == 0) ||
                 ((phi_s0->id & 0x800) == 0))) {
                Actor_SpawnEntry(&globalCtx->actorCtx, phi_s0, globalCtx);
            }
            phi_s0++;
        }
        globalCtx->numSetupActors = -globalCtx->numSetupActors;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9334.s")
#endif

#ifdef NON_EQUIVALENT
Actor* Actor_UpdateActor(s800B948C* params) {
    GlobalContext* sp24;
    Actor* temp_s0;
    u32 temp_v1;
    Actor* phi_v1;

    temp_s0 = params->actor;
    sp24 = params->globalCtx;
    if (temp_s0->world.pos.y < -25000.0f) {
        temp_s0->world.pos.y = -25000.0f;
    }
    temp_s0->sfx = 0;
    temp_s0->unk39 &= 0xFF80;
    if (temp_s0->init != 0) {
        if (Object_IsLoaded(&sp24->objectCtx, (s32)temp_s0->objBankIndex) != 0) {
            Actor_SetObjectDependency(sp24, temp_s0);
            temp_s0->init(temp_s0, sp24);
            temp_s0->init = NULL;
        }
        // goto block_38;
        return temp_s0->next;
    } else if (temp_s0->update == 0) {
        if (temp_s0->isDrawn == 0) {
            phi_v1 = Actor_Delete(&sp24->actorCtx, temp_s0, sp24);
        } else {
            Actor_Destroy(temp_s0, sp24);
            // goto block_38;
            return temp_s0->next;
        }
    } else {
        if (Object_IsLoaded(&sp24->objectCtx, (s32)temp_s0->objBankIndex) == 0) {
            Actor_MarkForDeath(temp_s0);
            return temp_s0->next;
        } else {
            if (((params->updateActorIfSet != 0) && ((temp_s0->flags & params->updateActorIfSet) == 0)) ||
                ((params->updateActorIfSet != 0) &&
                 (!(temp_s0->flags & 0x100000) ||
                  ((temp_s0->category == 3) && ((params->player->stateFlags1 & 0x200) != 0))) &&
                 (params->unkC != 0) && (temp_s0 != params->unk10) && ((temp_s0 != params->player->heldActor)) &&
                 (&params->player->actor != temp_s0->parent))) {
                CollisionCheck_ResetDamage(&temp_s0->colChkInfo);
            } else {
                s32 phi_v0;

                Math_Vec3f_Copy(&temp_s0->prevPos, (Vec3f*)&temp_s0->world);
                temp_s0->xzDistToPlayer = Actor_XZDistanceBetweenActors(temp_s0, (Actor*)params->player);
                temp_s0->yDistToPlayer = Actor_HeightDiff(temp_s0, (Actor*)params->player);
                temp_s0->xyzDistToPlayerSq = SQ(temp_s0->xzDistToPlayer) + SQ(temp_s0->yDistToPlayer);

                temp_s0->yawTowardsPlayer = Actor_YawBetweenActors(temp_s0, (Actor*)params->player);
                temp_s0->flags &= 0xFEFFFFFF;

                if (temp_s0->freezeTimer == 0) {
                    phi_v0 = 0;
                } else {
                    temp_s0->freezeTimer--;
                    phi_v0 = temp_s0->freezeTimer & 0xFFFF;
                }

                if ((phi_v0 == 0) && ((temp_s0->flags & params->runMainIfSet) != 0)) {
                    if (temp_s0 == params->player->unk_730) {
                        temp_s0->isTargeted = 1;
                    } else {
                        temp_s0->isTargeted = 0;
                    }
                    if ((temp_s0->targetPriority != 0) && (params->player->unk_730 == 0)) {
                        temp_s0->targetPriority = 0;
                    }
                    Actor_SetObjectDependency(sp24, temp_s0);

                    if (temp_s0->colorFilterTimer != 0) {
                        temp_s0->colorFilterTimer--;
                    }
                    temp_s0->update(temp_s0, sp24);
                    BgCheck_ResetFlagsIfLoadedActor(sp24, &sp24->colCtx.dyna, temp_s0);
                }
                CollisionCheck_ResetDamage(&temp_s0->colChkInfo);
            }
        }
        // block_38:
        phi_v1 = temp_s0->next;
    }
    return phi_v1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateActor.s")
#endif

s32 D_801AED58[] = {
    0x100002C2, 0x100002C2, 0x00000200, 0x100006C2, 0x00000282, 0x300002C2,
    0x10000282, 0x00000002, 0x300002C2, 0x100006C2, 0x00000002, 0x100002C2,
};

#ifdef NON_EQUIVALENT
void Actor_UpdateAll(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s800B948C sp40;
    ActorListEntry* sp3C;
    DynaCollisionContext* sp38;
    s32 phi_s3;
    u8 phi_s3_2;
    Actor* phi_s0_3;

    sp40.player = GET_PLAYER(globalCtx);
    sp40.globalCtx = globalCtx;

    if (globalCtx->unk_18844 != 0) {
        sp40.runMainIfSet = 0x200000;
    } else {
        sp40.runMainIfSet = 0x200050;
    }

    func_800B9334(globalCtx, actorCtx);

    if (actorCtx->unk2 != 0) {
        actorCtx->unk2--;
    }

    if (sp40.player->stateFlags2 & 0x8000000) {
        sp40.updateActorIfSet = 0x2000000;
    } else {
        sp40.updateActorIfSet = 0;
    }
    if (((sp40.player->stateFlags1 & 0x40) != 0) && ((sp40.player->actor.textId & 0xFF00) != 0x1900)) {
        sp40.unk10 = sp40.player->targetActor;
    } else {
        sp40.unk10 = 0;
    }

    sp38 = &globalCtx->colCtx.dyna;
    for (phi_s3 = 0; phi_s3 < ARRAY_COUNT(actorCtx->actorList); phi_s3++) {
        sp40.unkC = D_801AED58[phi_s3] & sp40.player->stateFlags1;
        sp40.actor = actorCtx->actorList[phi_s3].first;
        while (sp40.actor != 0) {
            sp40.actor = Actor_UpdateActor(&sp40);
        }
        if (phi_s3 == 1) {
            BgCheck_Update(globalCtx, sp38);
        }
    }

    for (phi_s3_2 = 0; phi_s3_2 != 0xC; phi_s3_2++) {
        if (sp3C->unk_08 != 0) {
            Actor* phi_s0;

            phi_s0 = sp3C->first;
            if (phi_s0 != 0) {
                Actor* phi_s0_2;

                do {
                    u8 temp_v0_3;

                    temp_v0_3 = phi_s0->category;
                    if (phi_s3_2 == temp_v0_3) {
                        phi_s0_2 = phi_s0->next;
                    } else {
                        phi_s0_2 = phi_s0->next;
                        phi_s0->category = phi_s3_2;
                        Actor_RemoveFromCategory(globalCtx, actorCtx, phi_s0);
                        Actor_AddToCategory(actorCtx, phi_s0, temp_v0_3);
                    }
                    phi_s0 = phi_s0_2;
                } while (phi_s0_2 != 0);
            }
            sp3C->unk_08 = 0;
        }
        sp3C++;
    }

    phi_s0_3 = sp40.player->unk_730;
    if ((phi_s0_3 != 0) && (phi_s0_3->update == 0)) {
        func_80123DA4(sp40.player);
        phi_s0_3 = NULL;
    }

    if ((phi_s0_3 == 0) || (sp40.player->unk_738 < 5)) {
        phi_s0_3 = NULL;
        if (actorCtx->targetContext.unk4B != 0) {
            actorCtx->targetContext.unk4B = 0;
            play_sound(NA_SE_SY_LOCK_OFF);
        }
    }

    if ((sp40.player->stateFlags1 & 2) == 0) {
        func_800B5814(&actorCtx->targetContext, sp40.player, phi_s0_3, globalCtx);
    }

    TitleCard_Update(globalCtx, &actorCtx->titleCtxt);
    func_800B6474(globalCtx);
    BgCheck_UpdateAllActorMeshes(globalCtx, sp38);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateAll.s")
#endif

void Actor_Draw(GlobalContext* globalCtx, Actor* actor) {
    Lights* sp44;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp44 = LightContext_NewLights(&globalCtx->lightCtx, globalCtx->state.gfxCtx);
    if ((actor->flags & 0x10000000) && (globalCtx->roomCtx.currRoom.enablePosLights || (MREG(93) != 0))) {
        sp44->enablePosLights = true;
    }

    Lights_BindAll(sp44, globalCtx->lightCtx.listHead, (actor->flags & 0x10400000) ? NULL : &actor->world.pos,
                   globalCtx);
    Lights_Draw(sp44, globalCtx->state.gfxCtx);

    if (actor->flags & 0x1000) {
        SysMatrix_SetStateRotationAndTranslation(
            actor->world.pos.x + globalCtx->mainCamera.skyboxOffset.x,
            actor->world.pos.y + ((actor->shape.yOffset * actor->scale.y) + globalCtx->mainCamera.skyboxOffset.y),
            actor->world.pos.z + globalCtx->mainCamera.skyboxOffset.z, &actor->shape.rot);
    } else {
        SysMatrix_SetStateRotationAndTranslation(actor->world.pos.x,
                                                 actor->world.pos.y + (actor->shape.yOffset * actor->scale.y),
                                                 actor->world.pos.z, &actor->shape.rot);
    }

    Matrix_Scale(actor->scale.x, actor->scale.y, actor->scale.z, MTXMODE_APPLY);
    Actor_SetObjectDependency(globalCtx, actor);

    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);
    gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);

    if (actor->colorFilterTimer != 0) {
        s32 temp_v0_2 = actor->colorFilterParams & 0xC000;
        Color_RGBA8 actorDefaultHitColor = { 0, 0, 0, 255 };

        if (temp_v0_2 == 0x8000) {
            actorDefaultHitColor.r = actorDefaultHitColor.g = actorDefaultHitColor.b =
                ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        } else if (temp_v0_2 == 0x4000) {
            actorDefaultHitColor.r = ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        } else if (temp_v0_2 == 0xC000) {
            actorDefaultHitColor.b = actorDefaultHitColor.g = actorDefaultHitColor.r = 0;
        } else {
            actorDefaultHitColor.b = ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        }

        if (actor->colorFilterParams & 0x2000) {
            func_800AE778(globalCtx, &actorDefaultHitColor, actor->colorFilterTimer, actor->colorFilterParams & 0xFF);
        } else {
            func_800AE434(globalCtx, &actorDefaultHitColor, actor->colorFilterTimer, actor->colorFilterParams & 0xFF);
        }
    }

    actor->draw(actor, globalCtx);

    if (actor->colorFilterTimer != 0) {
        if (actor->colorFilterParams & 0x2000) {
            func_800AE8EC(globalCtx);
        } else {
            func_800AE5A0(globalCtx);
        }
    }

    if (actor->shape.shadowDraw != NULL) {
        actor->shape.shadowDraw(actor, sp44, globalCtx);
    }
    actor->isDrawn = true;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#ifdef NON_MATCHING
void func_801A0810(s32*, u16, u8);
void func_800B9D1C(Actor* actor) {
    if (actor->sfx != 0) {
        if ((actor->unk39 & 2) != 0) {
            Audio_PlaySoundGeneral(actor->sfx & 0xFFFF, &actor->projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
        } else if ((actor->unk39 & 4) != 0) {
            play_sound(actor->sfx & 0xFFFF);
        } else if ((actor->unk39 & 8) != 0) {
            func_8019F128(actor->sfx & 0xFFFF);
        } else if ((actor->unk39 & 0x10) != 0) {
            func_801A0810(&D_801DB4A4, NA_SE_SY_TIMER - SFX_FLAG, (actor->sfx - 1));
        } else if ((actor->unk39 & 1) != 0) {
            func_8019F1C0(&actor->projectedPos, actor->sfx & 0xFFFF);
        }
    }

    if (actor->unk39 & 0x40) {
        func_801A1FB4(3, &actor->projectedPos, 0x27, 1500.0f);
    }

    if (actor->unk39 & 0x20) {
        func_801A1FB4(0, &actor->projectedPos, 0x71, 900.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9D1C.s")
#endif

void Actor_DrawAllSetup(GlobalContext* globalCtx) {
    globalCtx->actorCtx.undrawnActorCount = 0;
    globalCtx->actorCtx.unkB = 0;
}

s32 Actor_RecordUndrawnActor(GlobalContext* globalCtx, Actor* actor) {
    if (globalCtx->actorCtx.undrawnActorCount >= 32) {
        return 0;
    }

    globalCtx->actorCtx.undrawnActors[globalCtx->actorCtx.undrawnActorCount] = actor;
    globalCtx->actorCtx.undrawnActorCount++;
    return 1;
}

void func_800B9E84(Gfx** arg0, s32 arg1) {
    func_80164C14(arg0, D_801DE890, 4, 0, 6, 6, ((100 - arg1) * 0.003f) + 1.0f);
}

#ifdef NON_EQUIVALENT
void func_800B9EF4(GlobalContext* globalCtx, s32 numActors, Actor** actors) {
    s32 spB4;
    Gfx* spAC;
    void* spA8; //pad
    s32 spA4;
    //void* sp34;
    //Gfx* temp_s1_11;
    //Gfx** temp_a0_2;
    //Gfx** temp_a1;
    //GraphicsContext* temp_s2;
    //void* temp_s1_10;
    //void* temp_s1_7;
    //void* temp_s1_8;
    //void* temp_s1_9;
    //Gfx* phi_s1;
    Gfx* phi_s1_2;
    //void* phi_s1_4;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    //temp_s2 = globalCtx->state.gfxCtx;

    if (numActors > 0) {
        spAC = POLY_XLU_DISP;
        //sp34 = globalCtx + 0x18000;
        spA4 = globalCtx->unk_18E68;

        PreRender_SetValues(&globalCtx->pauseBgPreRender, D_801FBBCC, D_801FBBCE, __gfxCtx->framebuffer, __gfxCtx->zbuffer);

        func_80170200(&globalCtx->pauseBgPreRender, &spAC, __gfxCtx->zbuffer, (void* ) spA4);

        //spAC->words.w0 = 0xE7000000;
        //spAC->words.w1 = 0;
        //temp_s1_2 = spAC + 8;
        gDPPipeSync(spAC++);

        //temp_s1_2->words.w0 = 0xEE000000;
        //temp_s1_2->words.w1 = 0;
        //temp_s1_3 = temp_s1_2 + 8;
        gDPSetPrimDepth(spAC++, 0, 0);

        //temp_s1_3->words.w0 = 0xEF002C30;
        //temp_s1_3->words.w1 = 0xAF504365;
        //temp_s1_4 = temp_s1_3 + 8;
        gDPSetOtherMode(spAC++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PRIM | Z_UPD | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | GBL_c1(G_BL_CLR_BL, G_BL_0, G_BL_CLR_MEM, G_BL_1MA) | GBL_c2(G_BL_CLR_BL, G_BL_0, G_BL_CLR_MEM, G_BL_1MA));

        //temp_s1_4->words.w1 = 0xFF;
        //temp_s1_4->words.w0 = 0xFA000000;
        //temp_s1_5 = temp_s1_4 + 8;
        gDPSetPrimColor(spAC++, 0, 0, 0, 0, 0, 255);
        //temp_s1_5 = spAC;

        if (globalCtx->roomCtx.currRoom.unk5 == 0) {
            //temp_s1_5->words.w0 = 0xFC61E6C3;
            //temp_s1_5->words.w1 = 0x11CF9FCF;
            //phi_s1 = temp_s1_5 + 8;
            gDPSetCombineLERP(spAC++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0);
        } else {
            //temp_s1_5->words.w0 = 0xFC119623;
            //temp_s1_5->words.w1 = 0xFF2FFFFF;
            //phi_s1 = temp_s1_5 + 8;
            gDPSetCombineMode(spAC++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        }

        //spAC = phi_s1;
        func_800B9E84(&spAC, globalCtx->actorCtx.unk4);
        phi_s1_2 = func_801660B8(globalCtx, spAC);

        for (spB4 = 0; spB4 < numActors; spB4++, actors++) {
            Actor_Draw(globalCtx, *actors);
        }

        //temp_s0_2 = &globalCtx->pauseBgPreRender;

        //phi_s1_2->words.w0 = 0xE7000000;
        //phi_s1_2->words.w1 = 0;
        //temp_s1_7 = phi_s1_2 + 8;
        gDPPipeSync(phi_s1_2++);

        //temp_s1_7->unk_0 = 0xEF002CF0;
        //temp_s1_7->unk_4 = 0xF5A714D;
        //temp_s1_8 = temp_s1_7 + 8;
        gDPSetOtherMode(phi_s1_2++, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PRIM | AA_EN | IM_RD | CVG_DST_WRAP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1) | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1));

        //temp_s1_8->unk_4 = -0x100;
        //temp_s1_8->unk_0 = 0xF9000000;
        //temp_s1_9 = temp_s1_8 + 8;
        gDPSetBlendColor(phi_s1_2++, 255, 255, 255, 0);

        //temp_s1_9->unk_4 = 0x20;
        //temp_s1_9->unk_0 = 0xFA0000FF;
        //temp_s1_10 = temp_s1_9 + 8;
        gDPSetPrimColor(phi_s1_2++, 0, 0xFF, 0, 0, 0, 32);

        //temp_a0_2 = &spAC;
        //if (sp34->unk_6E5 == 0) {
        if (globalCtx->roomCtx.currRoom.unk5 == 0) {
        //    temp_s1_10->unk_0 = 0xFC119623;
        //    temp_s1_10->unk_4 = 0xFF2FFFFF;
        //    phi_s1_4 = temp_s1_10 + 8;
            gDPSetCombineMode(phi_s1_2++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        //} else {
        } else {
        //    temp_s1_10->unk_4 = 0x11CF9FCF;
        //    temp_s1_10->unk_0 = 0xFC61E6C3;
        //    phi_s1_4 = temp_s1_10 + 8;
            gDPSetCombineLERP(phi_s1_2++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0);

        //}
        }
        //phi_s1_4->unk_0 = (s32) (((sp34->unk_B4C - 1) & 0xFFF) | 0xFF100000);
        //temp_s1_11 = phi_s1_4 + 8;
        //phi_s1_4->unk_4 = spA4;
        gDPSetColorImage(phi_s1_2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((globalCtx->pauseBgPreRender.width - 1) & 0xFFF), spA4);
        //temp_s1_11 = phi_s1_2;

        spAC = phi_s1_2;

        //spAC = temp_s1_11;
        func_800B9E84(&spAC, (s32) globalCtx->actorCtx.unk4);
        //temp_s1_11->words.w0 = 0xE7000000;
        //temp_s1_11->words.w1 = 0;
        //temp_s1_12 = temp_s1_11 + 8;
        gDPPipeSync(spAC++);

        //temp_s1_12->words.w1 = -0xF8;
        //temp_s1_12->words.w0 = 0xF9000000;
        //temp_s1_13 = temp_s1_12 + 8;
        gDPSetBlendColor(spAC++, 255, 255, 255, 8);

        //temp_s1_14 = temp_s1_13 + 8;
        //temp_s1_13->words.w0 = ((sp34->unk_B4C - 1) & 0xFFF) | 0xFF100000;
        //temp_s1_13->words.w1 = sp34->unk_B5C;
        gDPSetColorImage(spAC++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((globalCtx->pauseBgPreRender.width - 1) & 0xFFF), globalCtx->pauseBgPreRender.fbuf);

        //temp_a1 = &spAC;
        //spAC = temp_s1_14;
        //func_8016FDB8(&globalCtx->pauseBgPreRender, temp_a1, (void* ) spA4, spA8, 1U);
        func_8016FDB8(&globalCtx->pauseBgPreRender, &spAC, (void* ) spA4, __gfxCtx->zbuffer, 1U);
//
        //POLY_OPA_DISP = temp_s1_14;
        POLY_OPA_DISP = spAC;
    }

    //temp_s1_15 = OVERLAY_DISP;
    //temp_s1_15->words.w0 = 0xE7000000;
    //temp_s1_15->words.w1 = 0;
    //temp_s1_16 = temp_s1_15 + 8;
    spAC = OVERLAY_DISP;
    gDPPipeSync(spAC++);

    //temp_s1_16->words.w0 = 0xEF002C30;
    //temp_s1_16->words.w1 = 0x00504345;
    //temp_s1_17 = temp_s1_16 + 8;
    gDPSetOtherMode(spAC++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2);


    //temp_s1_17->words.w0 = 0xFC61E6C3;
    //temp_s1_17->words.w1 = 0x11CF9FCF;
    //temp_s1_18 = temp_s1_17 + 8;
    gDPSetCombineLERP(spAC++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0);


    //temp_s1_18->words.w0 = 0xFA000000;
    //temp_s1_18->words.w1 = 0x4A00004A;
    //spAC = temp_s1_18 + 8;
    gDPSetPrimColor(spAC++, 0, 0, 74, 0, 0, 74);

    func_800B9E84(&spAC, (s32) globalCtx->actorCtx.unk4);

    OVERLAY_DISP = spAC;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9EF4.s")
#endif

s32 func_800BA2D8(GlobalContext* globalCtx, Actor* actor) {
    return func_800BA2FC(globalCtx, actor, &actor->projectedPos, actor->projectedW);
}

#ifdef NON_MATCHING
s32 func_800BA2FC(GlobalContext* globalCtx, Actor* actor, Vec3f* param_3, f32 param_4) {
    f32 temp_f14;
    f32 phi_f12;
    f32 phi_f2;
    f32 phi_f14;
    f32 phi_f16;

    if ((-actor->uncullZoneScale < param_3->z) && (param_3->z < (actor->uncullZoneForward + actor->uncullZoneScale))) {
        phi_f2 = CLAMP_MIN(param_4, 1.0f);

        if (globalCtx->view.fovy != 60.0f) {
            temp_f14 = globalCtx->unk_187F0.y * 0.57735026f;
            phi_f12 = actor->uncullZoneScale * globalCtx->unk_187F0.x * 0.76980036f;
            phi_f14 = temp_f14 * actor->uncullZoneDownward;
            phi_f16 = actor->uncullZoneScale * temp_f14;
        } else {
            phi_f12 = actor->uncullZoneScale;
            phi_f14 = actor->uncullZoneDownward;
            phi_f16 = actor->uncullZoneScale;
        }

        if (((fabsf(param_3->x) - phi_f12) < phi_f2) && ((-phi_f2 < (param_3->y + phi_f14))) &&
            ((param_3->y - phi_f16) < phi_f2)) {
            return 1;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA2FC.s")
#endif

#ifdef NON_EQUIVALENT
// weird DISPS stuff
void Actor_DrawAll(GlobalContext* globalCtx, ActorContext* actorCtx) {
    Gfx* sp58;
    GraphicsContext* sp44;
    Actor* temp_s0;
    Actor* temp_s0_2;
    Gfx* temp_s0_3;
    Gfx* temp_t9;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    Gfx* temp_v1;
    s32 temp_s7;
    ActorListEntry* phi_fp;
    Actor* phi_s0;
    s32 phi_s6;
    s32 i;

    if (globalCtx->unk_18844 != 0) {
        phi_s6 = 0x200000;
    } else {
        phi_s6 = 0x200060;
    }

    sp44 = globalCtx->state.gfxCtx;
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Actor_DrawAllSetup(globalCtx);

    // temp_t9 = sp44->polyXlu.p;
    // sp58 = temp_t9;
    // sp44->polyXlu.p = temp_t9 + 8;
    sp58 = POLY_XLU_DISP;
    POLY_XLU_DISP = &POLY_XLU_DISP[1];

    phi_fp = actorCtx->actorList;

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++, phi_fp++) {
        phi_s0 = phi_fp->first;
        while (phi_s0 != NULL) {
            SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->projectionMatrix, &phi_s0->world.pos, &phi_s0->projectedPos,
                                         &phi_s0->projectedW);

            if ((phi_s0->unk39 & 0x7F) != 0) {
                func_800B9D1C(phi_s0);
            }

            if (func_800BA2D8(globalCtx, phi_s0) != 0) {
                phi_s0->flags |= 0x40;
            } else {
                phi_s0->flags &= ~0x40;
            }

            phi_s0->isDrawn = false;
            if ((phi_s0->init == NULL) && (phi_s0->draw != NULL)) {
                if (phi_s0->flags & phi_s6) {
                    if ((phi_s0->flags & 0x80) &&
                        ((globalCtx->roomCtx.currRoom.unk5 == 0) || (globalCtx->actorCtx.unk4 == 0x64) ||
                         (globalCtx->roomCtx.currRoom.num != phi_s0->room))) {
                        if (Actor_RecordUndrawnActor(globalCtx, phi_s0) != 0) {}
                    } else {
                        Actor_Draw(globalCtx, phi_s0);
                    }
                }
            }

            phi_s0 = phi_s0->next;
        }
    }

    Effect_DrawAll(globalCtx->state.gfxCtx);
    EffectSS_DrawAllParticles(globalCtx);
    EffFootmark_Draw(globalCtx);

    temp_s0_3 = POLY_XLU_DISP;
    // temp_s0_3 = sp44->polyXlu.p;
    // sp58->words.w0 = 0xDE000000;
    // temp_v0_2 = temp_s0_3 + 8;
    // sp58->words.w1 = (u32) temp_v0_2;
    // sp44->polyXlu.p = temp_v0_2;
    gSPDisplayList(sp58, POLY_XLU_DISP++);

    if (globalCtx->actorCtx.unk3 != 0) {
        Math_StepToC(&globalCtx->actorCtx.unk4, 100, 20);
        if ((GET_PLAYER(globalCtx)->stateFlags2 & 0x8000000)) {
            func_800B90F4(globalCtx);
        }
    } else {
        Math_StepToC(&globalCtx->actorCtx.unk4, 0, 10);
    }
    if (globalCtx->actorCtx.unk4 != 0) {
        globalCtx->actorCtx.unkB = 1;
        func_800B9EF4(globalCtx, globalCtx->actorCtx.undrawnActorCount, globalCtx->actorCtx.undrawnActors);
    }

    // temp_v0_3 = sp44->polyXlu.p;
    // temp_v0_3->words.w0 = 0xDF000000;
    // temp_v0_3->words.w1 = 0;
    // temp_v1 = temp_v0_3 + 8;
    // temp_s0_3->words.w1 = (u32) temp_v1;
    // temp_s0_3->words.w0 = 0xDE010000;
    // sp44->polyXlu.p = temp_v1;

    // gSPEndDisplayList(POLY_XLU_DISP++);
    // gSPBranchList(POLY_XLU_DISP++, POLY_XLU_DISP);
    // temp_v0_3 = POLY_XLU_DISP;
    gSPEndDisplayList(POLY_XLU_DISP++);
    gSPBranchList(temp_s0_3, POLY_XLU_DISP);

    if (globalCtx->unk_18844 == 0) {
        Lights_DrawGlow(globalCtx);
    }

    TitleCard_Draw(globalCtx, &actorCtx->titleCtxt);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_DrawAll.s")
#endif

/**
 * Kills every actor which its object is not loaded
 */
void func_800BA6FC(GlobalContext* globalCtx, ActorContext* actorCtx) {
    Actor* actor;
    s32 i;

    for (i = 0; i != ARRAY_COUNT(actorCtx->actorList); i++) {
        actor = actorCtx->actorList[i].first;

        while (actor != NULL) {
            if (!Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
                Actor_MarkForDeath(actor);
            }

            actor = actor->next;
        }
    }
}

/**
 * Kill actors on room change
 */
void func_800BA798(GlobalContext* globalCtx, ActorContext* actorCtx) {
    Actor* actor;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++) {
        actor = actorCtx->actorList[i].first;

        while (actor != NULL) {
            if ((actor->room >= 0) && (actor->room != globalCtx->roomCtx.currRoom.num) &&
                (actor->room != globalCtx->roomCtx.prevRoom.num)) {
                if (!actor->isDrawn) {
                    actor = Actor_Delete(actorCtx, actor, globalCtx);
                } else {
                    Actor_MarkForDeath(actor);
                    Actor_Destroy(actor, globalCtx);
                    actor = actor->next;
                }
            } else {
                actor = actor->next;
            }
        }
    }

    CollisionCheck_ClearContext(globalCtx, &globalCtx->colChkCtx);
    actorCtx->flags.clearedRoomTemp = 0;
    actorCtx->flags.swch[3] = 0;
    actorCtx->flags.collectible[3] = 0;
    globalCtx->msgCtx.unk_12030 = 0;
}

void func_800BA8B8(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++) {
        Actor* actor = actorCtx->actorList[i].first;

        while (actor != NULL) {
            if (!(actor->unk20 & actorCtx->unkC)) {
                func_80123590(globalCtx, actor);
                if (!actor->isDrawn) {
                    actor = Actor_Delete(actorCtx, actor, globalCtx);
                } else {
                    Actor_MarkForDeath(actor);
                    Actor_Destroy(actor, globalCtx);
                    actor = actor->next;
                }
            } else {
                actor = actor->next;
            }
        }
    }

    CollisionCheck_ClearContext(globalCtx, &globalCtx->colChkCtx);
    globalCtx->msgCtx.unk_12030 = 0;
}

// Actor_CleanupContext
void func_800BA9B4(ActorContext* arg0, GlobalContext* arg1) {
    s32 i;

    Fault_RemoveClient(&D_801ED8A0);

    for (i = 0; i < ARRAY_COUNT(arg0->actorList); i++) {
        if (i != ACTORCAT_PLAYER) {
            Actor* phi_s0 = arg0->actorList[i].first;

            while (phi_s0 != NULL) {
                Actor_Delete(arg0, phi_s0, arg1);
                phi_s0 = arg0->actorList[i].first;
            }
        }
    }

    while (arg0->actorList[ACTORCAT_PLAYER].first != NULL) {
        Actor_Delete(arg0, arg0->actorList[ACTORCAT_PLAYER].first, arg1);
    }

    if (arg0->absoluteSpace != NULL) {
        zelda_free(arg0->absoluteSpace);
        arg0->absoluteSpace = NULL;
    }

    func_80169D40(arg1);
    ActorOverlayTable_Cleanup();
}

/**
 * Adds a given actor instance at the front of the actor list of the specified category.
 * Also sets the actor instance as being of that category.
 */
void Actor_AddToCategory(ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    Actor* phi_v0;
    Actor* phi_v1;

    actor->category = actorCategory;

    actorCtx->totalLoadedActors++;
    actorCtx->actorList[actorCategory].length++;
    phi_v1 = actorCtx->actorList[actorCategory].first;

    if (phi_v1 == NULL) {
        actorCtx->actorList[actorCategory].first = actor;
        return;
    }

    phi_v0 = phi_v1->next;
    while (phi_v0 != NULL) {
        phi_v1 = phi_v0;
        phi_v0 = phi_v0->next;
    }

    phi_v1->next = actor;
    actor->prev = phi_v1;
}

/**
 * Removes a given actor instance from its actor list.
 * Also sets the temp clear flag of the current room if the actor removed was the last enemy loaded.
 */
Actor* Actor_RemoveFromCategory(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actorToRemove) {
    Actor* newHead;

    actorCtx->totalLoadedActors--;
    actorCtx->actorList[actorToRemove->category].length--;

    if (actorToRemove->prev != NULL) {
        actorToRemove->prev->next = actorToRemove->next;
    } else {
        actorCtx->actorList[actorToRemove->category].first = actorToRemove->next;
    }

    newHead = actorToRemove->next;

    if (newHead != NULL) {
        newHead->prev = actorToRemove->prev;
    }

    actorToRemove->next = NULL;
    actorToRemove->prev = NULL;

    if ((actorToRemove->room == globalCtx->roomCtx.currRoom.num) && (actorToRemove->category == ACTORCAT_ENEMY) &&
        (actorCtx->actorList[ACTORCAT_ENEMY].length == 0)) {
        Flags_SetClearTemp(globalCtx, globalCtx->roomCtx.currRoom.num);
    }

    return newHead;
}

void Actor_FreeOverlay(ActorOverlay* entry) {
    if (entry->numLoaded == 0) {
        void* ramAddr = entry->loadedRamAddr;

        if (ramAddr != NULL) {
            if (!(entry->allocType & ALLOCTYPE_PERMANENT)) {
                if (entry->allocType & ALLOCTYPE_ABSOLUTE) {
                    entry->loadedRamAddr = NULL;
                } else {
                    zelda_free(ramAddr);
                    entry->loadedRamAddr = NULL;
                }
            }
        }
    }
}

Actor* Actor_Spawn(ActorContext* actorCtx, GlobalContext* globalCtx, s16 actorId, f32 posX, f32 posY, f32 posZ,
                   s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         0x3FF, NULL);
}

ActorInit* Actor_LoadOverlay(ActorContext* actorCtx, s16 index) {
    size_t overlaySize;
    ActorOverlay* overlayEntry = &gActorOverlayTable[index];
    ActorInit* actorInit;

    overlaySize = (uintptr_t)overlayEntry->vramEnd - (uintptr_t)overlayEntry->vramStart;

    if (overlayEntry->vramStart == NULL) {
        actorInit = overlayEntry->initInfo;
    } else {
        if (overlayEntry->loadedRamAddr == 0) {
            if (overlayEntry->allocType & ALLOCTYPE_ABSOLUTE) {
                if (actorCtx->absoluteSpace == NULL) {
                    actorCtx->absoluteSpace = zelda_mallocR(AM_FIELD_SIZE);
                }
                gActorOverlayTable[index].loadedRamAddr = actorCtx->absoluteSpace;
            } else {
                if (overlayEntry->allocType & ALLOCTYPE_PERMANENT) {
                    gActorOverlayTable[index].loadedRamAddr = zelda_mallocR(overlaySize);
                } else {
                    gActorOverlayTable[index].loadedRamAddr = zelda_malloc(overlaySize);
                }
            }

            if (overlayEntry->loadedRamAddr == NULL) {
                return NULL;
            }

            Load2_LoadOverlay(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart,
                              overlayEntry->vramEnd, overlayEntry->loadedRamAddr);
            overlayEntry->numLoaded = 0;
        }

        actorInit = (void*)(u32)((overlayEntry->initInfo != NULL)
                                     ? (void*)((u32)overlayEntry->initInfo -
                                               (s32)((u32)overlayEntry->vramStart - (u32)overlayEntry->loadedRamAddr))
                                     : NULL);
    }

    return actorInit;
}

#ifdef NON_MATCHING
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, GlobalContext* globalCtx, s16 index, f32 x, f32 y, f32 z,
                                     s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 param_12,
                                     Actor* parent) {
    s32 pad;
    Actor* actor;
    ActorInit* sp2C; // actorInit
    s32 sp28;        // objBankIndex
    // s32 pad2;
    u32 sp20;           // segmentAux
    ActorOverlay* sp1C; // overlayEntry

    if (actorCtx->totalLoadedActors >= 0xFF) {
        return NULL;
    }

    sp2C = Actor_LoadOverlay(actorCtx, index);
    if (sp2C == NULL) {
        return NULL;
    }

    sp28 = Object_GetIndex(&globalCtx->objectCtx, sp2C->objectId);
    if ((sp28 < 0) ||
        ((sp2C->type == ACTORCAT_ENEMY) && ((Flags_GetClear(globalCtx, globalCtx->roomCtx.currRoom.num) != 0)) &&
         (sp2C->id != ACTOR_BOSS_05))) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    actor = zelda_malloc(sp2C->instanceSize);
    if (actor == NULL) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    sp1C = &gActorOverlayTable[index];
    if (sp1C->vramStart != 0) {
        sp1C->numLoaded++;
    }

    bzero(actor, sp2C->instanceSize);
    actor->overlayEntry = sp1C;
    actor->id = sp2C->id;
    actor->flags = sp2C->flags;

    if (sp2C->id == ACTOR_EN_PART) {
        actor->objBankIndex = rotZ;
        rotZ = 0;
    } else {
        actor->objBankIndex = sp28;
    }

    actor->init = sp2C->init;
    actor->destroy = sp2C->destroy;
    actor->update = sp2C->update;
    actor->draw = sp2C->draw;

    if (parent != NULL) {
        actor->room = parent->room;
        actor->parent = parent;
        parent->child = actor;
    } else {
        actor->room = globalCtx->roomCtx.currRoom.num;
    }

    actor->home.pos.x = x;
    actor->home.pos.y = y;
    actor->home.pos.z = z;
    actor->home.rot.x = rotX;
    actor->home.rot.y = rotY;
    actor->home.rot.z = rotZ;
    actor->params = params & 0xFFFF;
    actor->cutscene = (cutscene & 0x7F);

    if (actor->cutscene == 0x7F) {
        actor->cutscene = -1;
    }

    if (param_12 != 0) {
        actor->unk20 = param_12;
    } else {
        actor->unk20 = 0x3FF;
    }

    Actor_AddToCategory(actorCtx, actor, sp2C->type);

    goto dummy_label_;
dummy_label_:;

    sp20 = gSegments[6];
    Actor_Init(actor, globalCtx);
    gSegments[6] = sp20;

    //    goto dummy_label_47816;
    // dummy_label_47816:;

    return actor;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnAsChildAndCutscene.s")
#endif

Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, GlobalContext* globalCtx, s16 actorId, f32 posX,
                          f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         parent->unk20, parent);
}

#ifdef NON_MATCHING
void Actor_SpawnTransitionActors(GlobalContext* globalCtx, ActorContext* actorCtx) {
    TransitionActorEntry* phi_s0;
    s32 phi_s2;
    s16 phi_v1;

    phi_s0 = globalCtx->doorCtx.transitionActorList;
    phi_v1 = globalCtx->doorCtx.numTransitionActors;

    for (phi_s2 = 0; phi_s2 < phi_v1; phi_s2++) {
        if (phi_s0->id >= 0) {
            if ((phi_s0->sides[0].room >= 0 && (globalCtx->roomCtx.currRoom.num == phi_s0->sides[0].room ||
                                                globalCtx->roomCtx.prevRoom.num == phi_s0->sides[0].room)) ||
                (phi_s0->sides[1].room >= 0 && (globalCtx->roomCtx.currRoom.num == phi_s0->sides[1].room ||
                                                globalCtx->roomCtx.prevRoom.num == phi_s0->sides[1].room))) {
                s16 rotY = ((phi_s0->rotY >> 7) & 0x1FF) * 182.04445f;

                if (Actor_SpawnAsChildAndCutscene(
                        actorCtx, globalCtx, phi_s0->id & 0x1FFF, phi_s0->pos.x, phi_s0->pos.y, phi_s0->pos.z, 0, rotY,
                        0, (phi_s2 << 0xA) + (phi_s0->params & 0x3FF), phi_s0->pos.x & 0x7F, 0x3FF, 0) != NULL) {
                    phi_s0->id = -phi_s0->id;
                }
                phi_v1 = globalCtx->doorCtx.numTransitionActors;
            }
        }
        phi_s0 += 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnTransitionActors.s")
#endif

Actor* Actor_SpawnEntry(ActorContext* actorCtx, ActorEntry* actorEntry, GameState* gameState) {
    s16 rotX = (actorEntry->rot.x >> 7) & 0x1FF;
    s16 rotY = (actorEntry->rot.y >> 7) & 0x1FF;
    s16 rotZ = (actorEntry->rot.z >> 7) & 0x1FF;

    if (!(actorEntry->id & 0x8000)) {
        rotY *= 0x10000 / 360.0f;
    } else if (rotY > 180) {
        rotY -= 360;
    }

    if (!(actorEntry->id & 0x4000)) {
        rotX *= 0x10000 / 360.0f;
    } else if (rotX > 180) {
        rotX -= 360;
    }

    if (!(actorEntry->id & 0x2000)) {
        rotZ *= 0x10000 / 360.0f;
    } else if (rotZ > 180) {
        rotZ -= 360;
    }

    return Actor_SpawnAsChildAndCutscene(actorCtx, (GlobalContext*)gameState, actorEntry->id & 0x1FFF,
                                         actorEntry->pos.x, actorEntry->pos.y, actorEntry->pos.z, rotX, rotY, rotZ,
                                         actorEntry->params & 0xFFFF, actorEntry->rot.y & 0x7F,
                                         ((actorEntry->rot.x & 7) << 7) | (actorEntry->rot.z & 0x7F), NULL);
}

Actor* Actor_Delete(ActorContext* actorCtx, Actor* actor, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    Actor* newHead;
    ActorOverlay* overlayEntry = actor->overlayEntry;

    if ((player != NULL) && (actor == player->unk_730)) {
        func_80123DA4(player);
        Camera_ChangeMode(Play_GetCamera(globalCtx, Play_GetActiveCameraIndex(globalCtx)), 0);
    }

    if (actor == actorCtx->targetContext.arrowPointedActor) {
        actorCtx->targetContext.arrowPointedActor = NULL;
    }

    if (actor == actorCtx->targetContext.unk8C) {
        actorCtx->targetContext.unk8C = NULL;
    }

    if (actor == actorCtx->targetContext.unk90) {
        actorCtx->targetContext.unk90 = NULL;
    }

    func_801A72CC(&actor->projectedPos);
    Actor_Destroy(actor, globalCtx);

    newHead = Actor_RemoveFromCategory(globalCtx, actorCtx, actor);
    zelda_free(actor);

    if (overlayEntry->vramStart != NULL) {
        overlayEntry->numLoaded--;
        Actor_FreeOverlay(overlayEntry);
    }

    return newHead;
}

s32 func_800BB59C(GlobalContext* globalCtx, Actor* actor) {
    s16 sp1E;
    s16 sp1C;

    func_800B8898(globalCtx, actor, &sp1E, &sp1C);

    return (sp1E > -20) && (sp1E < gScreenWidth + 20) && (sp1C > -160) && (sp1C < gScreenHeight + 160);
}

#ifdef NON_EQUIVALENT
void func_800BB604(GlobalContext* globalCtx, ActorContext* actorCtx, Player* player, s32 actorCategory) {
    Actor* sp8C;
    CollisionPoly* sp80;
    s32 sp7C;
    Vec3f sp70;
    f32 temp_f0_2;
    Actor* phi_s0;
    s32 phi_s2;
    s32 phi_s2_2;

    phi_s0 = actorCtx->actorList[actorCategory].first;
    sp8C = player->unk_730;
    while (phi_s0 != 0) {
        if ((phi_s0->update != 0) && (phi_s0 != &player->actor)) {
            if ((phi_s0->flags & 0x40000001) != 0) {
                if ((actorCategory == ACTORCAT_ENEMY) && ((phi_s0->flags & 5) == 5)) {
                    if ((phi_s0->xyzDistToPlayerSq < SQ(500.0f)) && (phi_s0->xyzDistToPlayerSq < D_801ED8CC)) {
                        actorCtx->targetContext.unk90 = phi_s0;
                        D_801ED8CC = phi_s0->xyzDistToPlayerSq;
                    }
                }

                if ((phi_s0 != sp8C) || (phi_s0->flags & 0x80000)) {
                    temp_f0_2 = func_800B82EC(phi_s0, player, D_801ED8DC);
                    phi_s2 = (phi_s0->flags & 1) != 0;
                    if (phi_s2 != 0) {
                        // phi_s2 = 0;
                        // if (temp_f0_2 < D_801ED8C8) {
                        //    phi_s2 = 1;
                        //}
                        phi_s2 = temp_f0_2 < D_801ED8C8 ? 1 : 0;
                    }
                    phi_s2_2 = (phi_s0->flags & 0x40000000) != 0;
                    if (phi_s2_2) {
                        // phi_s2_2 = 0;
                        // if (temp_f0_2 < D_801ED8D0) {
                        //    phi_s2_2 = 1;
                        //}
                        phi_s2_2 = temp_f0_2 < D_801ED8D0;
                    }

                    if (((phi_s2 != 0) || (phi_s2_2 != 0)) && (func_800B83BC(phi_s0, temp_f0_2) != 0)) {
                        if (func_800BB59C(globalCtx, phi_s0)) {
                            if (((func_800C54AC(&globalCtx->colCtx, &player->actor.focus.pos, &phi_s0->focus.pos, &sp70,
                                                &sp80, 1, 1, 1, 1, &sp7C) == 0) ||
                                 (func_800C9D50(&globalCtx->colCtx, sp80, sp7C) != 0))) {
                                if (phi_s0->targetPriority != 0) {
                                    if ((phi_s2 != 0) && (phi_s0->targetPriority < D_801ED8D4)) {
                                        D_801ED8BC = phi_s0;
                                        D_801ED8D4 = phi_s0->targetPriority;
                                    }
                                    if ((phi_s2_2 != 0) && (phi_s0->targetPriority < D_801ED8D8)) {
                                        D_801ED8C4 = phi_s0;
                                        D_801ED8D8 = phi_s0->targetPriority;
                                    }
                                } else {
                                    if (phi_s2 != 0) {
                                        D_801ED8B8 = phi_s0;
                                        D_801ED8C8 = temp_f0_2;
                                    }
                                    if (phi_s2_2 != 0) {
                                        D_801ED8C0 = phi_s0;
                                        D_801ED8D0 = temp_f0_2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        phi_s0 = phi_s0->next;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB604.s")
#endif

u8 D_801AED8C[] = {
    ACTORCAT_BOSS,  ACTORCAT_ENEMY,  ACTORCAT_BG,   ACTORCAT_EXPLOSIVES, ACTORCAT_NPC,  ACTORCAT_ITEMACTION,
    ACTORCAT_CHEST, ACTORCAT_SWITCH, ACTORCAT_PROP, ACTORCAT_MISC,       ACTORCAT_DOOR, ACTORCAT_SWITCH,
};

#if 0
// static bss?
void func_800BB8EC(GlobalContext* globalCtx, ActorContext* actorCtx, Actor** arg2, Actor** arg3, Player* player) {
    Actor* temp_v0;
    Actor* temp_v0_2;
    u8* phi_s1;
    s32 phi_s0;
    s8* phi_s1_2;
    s32 phi_s0_2;

    D_801ED8C4 = NULL;
    D_801ED8C0 = NULL;
    D_801ED8BC = NULL;
    D_801ED8B8 = NULL;

    D_801ED8C8 = D_801ED8D0 = D_801ED8CC = FLT_MAX;
    D_801ED8D8 = 0x7FFFFFFF;
    D_801ED8D4 = 0x7FFFFFFF;

    actorCtx->targetContext.unk90 = NULL;
    D_801ED8DC = player->actor.shape.rot.y;

    phi_s1 = D_801AED8C;
    phi_s0 = 0;

    while (phi_s0 < 3) {
        func_800BB604(globalCtx, actorCtx, player, *phi_s1);
        phi_s0 = phi_s0 + 1;
        phi_s1 = phi_s1 + 1;
    }

    if ((D_801ED8B8 == 0)) {
        while (phi_s0 < 0xC) {
            func_800BB604(globalCtx, actorCtx, player, *phi_s1);
            phi_s0 = phi_s0 + 1;
            phi_s1 += 1;
        }
    }

    if (D_801ED8B8 == 0) {
        *arg2 = (Actor* ) D_801ED8BC;
    } else {
        *arg2 = D_801ED8B8;
    }

    if (D_801ED8C0 == 0) {
        *arg3 = (s32) D_801ED8C4;
        return;
    }
    *arg3 = (s32) D_801ED8C0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB8EC.s")
#endif

void Enemy_StartFinishingBlow(GlobalContext* globalCtx, Actor* actor) {
    globalCtx->actorCtx.freezeFlashTimer = 5;
    Audio_PlaySoundAtPosition(globalCtx, &actor->world.pos, 20, NA_SE_EN_LAST_DAMAGE);
}

// blinking routine
s16 func_800BBAC0(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3) {
    s16 temp_v1;
    s32 temp_v0;
    s16 phi_v0;
    s32 phi_v1;

    if (DECR(arg0[1]) == 0) {
        arg0[1] = Rand_S16Offset(arg1, arg2);
    }

    if (arg0[1] - arg3 > 0) {
        arg0[0] = 0;
    } else if ((arg0[1] - arg3 >= -1) || (arg0[1] < 2)) {
        arg0[0] = 1;
    } else {
        arg0[0] = 2;
    }

    return arg0[0];
}

// blinking routine
s16 func_800BBB74(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3) {
    if (DECR(arg0[1]) == 0) {
        arg0[1] = Rand_S16Offset(arg1, arg2);
    }

    if (arg0[1] - arg3 > 0) {
        arg0[0] = 0;
    } else if (arg0[1] - arg3 == 0) {
        arg0[0] = 1;
    } else {
        arg0[0] = 2;
    }

    return arg0[0];
}

// unused blinking routine
s16 func_800BBC20(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3) {
    if (DECR(arg0[1]) == 0) {
        arg0[1] = Rand_S16Offset(arg1, arg2);
        arg0[0]++;
        if ((arg0[0] % 3) == 0) {
            arg0[0] = (s32)(Rand_ZeroOne() * arg3) * 3;
        }
    }
    return arg0[0];
}

void func_800BBCEC(Actor* actor, GlobalContext* globalCtx, s32 arg2, Gfx** dList) {
    EnPart* sp40;
    Actor* temp_v0_2;
    MtxF* sp3C;

    if (*dList != NULL) {
        sp3C = SysMatrix_GetCurrentState();
        temp_v0_2 = Actor_SpawnAsChild(&globalCtx->actorCtx, actor, globalCtx, ACTOR_EN_PART, sp3C->mf[3][0],
                                       sp3C->mf[3][1], sp3C->mf[3][2], 0, 0, actor->objBankIndex, arg2);
        if (temp_v0_2 != NULL) {
            sp40 = (EnPart*)temp_v0_2;

            func_8018219C(sp3C, &sp40->actor.shape.rot, 0);
            sp40->unk_150 = *dList;
            Math_Vec3f_Copy(&sp40->actor.scale, &actor->scale);
        }
    }
}

void Actor_SpawnFloorDustRing(GlobalContext* globalCtx, Actor* actor, Vec3f* posXZ, f32 radius, s32 amountMinusOne,
                              f32 randAccelWeight, s16 scale, s16 scaleStep, u8 useLighting) {
    Vec3f pos;
    Vec3f accel = { 0.0f, 0.3f, 0.0f };
    s32 pad[2];
    f32 angle;
    s32 i;

    angle = (Rand_ZeroOne() - 0.5f) * (2.0f * 3.14f);
    pos.y = actor->floorHeight;
    accel.y += (Rand_ZeroOne() - 0.5f) * 0.2f;

    for (i = amountMinusOne; i >= 0; i--) {
        pos.x = (sin_rad(angle) * radius) + posXZ->x;
        pos.z = (cos_rad(angle) * radius) + posXZ->z;
        accel.x = (Rand_ZeroOne() - 0.5f) * randAccelWeight;
        accel.z = (Rand_ZeroOne() - 0.5f) * randAccelWeight;

        if (scale == 0) {
            func_800B10C0(globalCtx, &pos, &D_801D15B0, &accel);
        } else if (useLighting) {
            func_800B1210(globalCtx, &pos, &D_801D15B0, &accel, scale, scaleStep);
        } else {
            func_800B11A0(globalCtx, &pos, &D_801D15B0, &accel, scale, scaleStep);
        }
        angle += (2.0f * 3.14f) / (amountMinusOne + 1.0f);
    }
}

void func_800BBFB0(GlobalContext* globalCtx, Vec3f* position, f32 param3, s32 param_4, s16 param_5, s16 scaleStep,
                   u8 param_7) {
    Vec3f pos;
    Vec3f accel = { 0.0f, 0.3f, 0.0f };
    s32 i;

    for (i = param_4; i >= 0; i--) {
        s16 scale;

        pos.x = ((Rand_ZeroOne() - 0.5f) * param3) + position->x;
        pos.y = ((Rand_ZeroOne() - 0.5f) * param3) + position->y;
        pos.z = ((Rand_ZeroOne() - 0.5f) * param3) + position->z;

        scale = (s32)(Rand_ZeroOne() * param_5 * 0.2f);
        scale += param_5;

        if (param_7) {
            func_800B1210(globalCtx, &pos, &D_801D15B0, &accel, scale, scaleStep);
        } else {
            func_800B11A0(globalCtx, &pos, &D_801D15B0, &accel, scale, scaleStep);
        }
    }
}

void func_800BC154(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    actorCtx->actorList[actor->category].unk_08 = 1;
    actor->category = actorCategory;
}

s32 D_801AEDB0[] = {
    0x00000800, 0x00000020, 0x00000020, 0x00000800, 0x00001000, 0x00002000, 0x00000001, 0x00010000, 0x00000001,
};

s32 func_800BC188(s32 index) {
    if ((index < 0) || (index >= ARRAY_COUNT(D_801AEDB0))) {
        return 0;
    }
    return D_801AEDB0[index];
}

s32 func_800BC1B4(Actor* actor, Actor* arg1, f32 arg2, f32 arg3) {
    if ((arg3 > 0.0f) && (Actor_DistanceBetweenActors(arg1, actor) < ((arg3 * 2.5f) + arg2))) {
        s16 temp_v1 = BINANG_SUB(Actor_YawBetweenActors(arg1, actor), arg1->world.rot.y);

        if (ABS_ALT(temp_v1) < 0x1400) {
            return 1;
        }
    }

    return 0;
}

Actor* func_800BC270(GlobalContext* globalCtx, Actor* actor, f32 arg2, s32 arg3) {
    Actor* phi_s0;

    phi_s0 = globalCtx->actorCtx.actorList[ACTORCAT_ITEMACTION].first;
    while (phi_s0 != NULL) {
        if (((phi_s0->id == ACTOR_ARMS_HOOK) && (arg3 & 0x80)) || ((phi_s0->id == ACTOR_EN_BOOM) && (arg3 & 0x10)) ||
            ((phi_s0->id == ACTOR_EN_ARROW) && ((func_800BC188(phi_s0->params) & arg3) != 0))) {
            f32 phi_f0;

            if ((phi_s0->speedXZ <= 0.0f) && (GET_PLAYER(globalCtx)->unk_D57 != 0)) {
                if (phi_s0->id == ACTOR_ARMS_HOOK) {
                    phi_f0 = 20.0f;
                } else if (phi_s0->id == ACTOR_EN_BOOM) {
                    phi_f0 = 12.0f;
                } else {
                    s32 temp_v0_3 = func_800BC188(phi_s0->params);

                    if (temp_v0_3 == 1) {
                        phi_f0 = 80.0f;
                    } else if (temp_v0_3 == 0x10000) {
                        phi_f0 = 60.0f;
                    } else {
                        phi_f0 = 150.0f;
                    }
                }
            } else {
                phi_f0 = phi_s0->speedXZ;
            }

            if (func_800BC1B4(actor, phi_s0, arg2, phi_f0) != 0) {
                break;
            }
        }

        phi_s0 = phi_s0->next;
    }

    return phi_s0;
}

Actor* func_800BC444(GlobalContext* globalCtx, Actor* actor, f32 arg2) {
    Actor* explosive = globalCtx->actorCtx.actorList[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if (((explosive->id == ACTOR_EN_BOM) || (explosive->id == ACTOR_EN_BOM_CHU) ||
             (explosive->id == ACTOR_EN_BOMBF))) {
            if (func_800BC1B4(actor, explosive, arg2, explosive->speedXZ) != 0) {
                break;
            }
        }
        explosive = explosive->next;
    }

    return explosive;
}

s16 func_800BC4EC(Actor* actor, GlobalContext* globalCtx, f32 arg2, s16 arg3) {
    s16 temp_v1;
    u16 sp44;
    f32 sp40;
    f32 temp_f0;
    Vec3f sp30;

    Math_Vec3f_Copy(&sp30, &actor->world.pos);
    sp44 = actor->bgCheckFlags;
    sp40 = Math_SinS(arg3) * arg2;
    temp_f0 = Math_CosS(arg3);
    actor->world.pos.x += sp40;
    actor->world.pos.z += temp_f0 * arg2;
    Actor_UpdateBgCheckInfo(globalCtx, actor, 0.0f, 0.0f, 0.0f, 4);
    Math_Vec3f_Copy(&actor->world.pos, &sp30);
    temp_v1 = (actor->bgCheckFlags & 1);
    actor->bgCheckFlags = sp44;

    return temp_v1;
}

s32 func_800BC5B8(GameState* gameState, Actor* actor) {
    Player* player = GET_PLAYER(gameState);

    if ((player->stateFlags3 & 0x80000000) && (actor->isTargeted != 0)) {
        return 1;
    }
    return 0;
}

s32 func_800BC5EC(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags3 & 0x80000000) && (actor->isTargeted == 0)) {
        return 1;
    }

    return 0;
}

void func_800BC620(Vec3f* arg0, Vec3f* arg1, u8 arg2, GlobalContext* globalCtx) {
    MtxF sp58;
    f32 sp54;
    Vec3f sp48;
    CollisionPoly* sp44;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, arg2);

    sp48.x = arg0->x;
    sp48.y = arg0->y + 1.0f;
    sp48.z = arg0->z;

    sp54 = func_800C4000(globalCtx, &globalCtx->colCtx, &sp44, &sp48);
    if (sp44 != NULL) {
        func_800C0094(sp44, arg0->x, sp54, arg0->z, &sp58);
        SysMatrix_SetCurrentState(&sp58);
    } else {
        SysMatrix_InsertTranslation(arg0->x, arg0->y, arg0->z, 0);
    }
    Matrix_Scale(arg1->x, 1.0f, arg1->z, 1);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_04076BC0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BC770(GameState* gameState, s16 arg1, s16 arg2) {
    s16 sp26;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    sp26 = Quake_Add(&globalCtx->mainCamera, 3);
    Quake_SetSpeed(sp26, 20000);
    Quake_SetQuakeValues(sp26, arg1, 0, 0, 0);
    Quake_SetCountdown(sp26, arg2);
}

void func_800BC7D8(GameState* gameState, s16 arg1, s16 arg2, s16 arg3) {
    s16 sp26;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    sp26 = Quake_Add(&globalCtx->mainCamera, 3);
    Quake_SetSpeed(sp26, arg3);
    Quake_SetQuakeValues(sp26, arg1, 0, 0, 0);
    Quake_SetCountdown(sp26, arg2);
}

void func_800BC848(Actor* actor, GameState* gameState, s16 arg2, s16 arg3) {
    if (arg2 >= 5) {
        func_8013ECE0(actor->xyzDistToPlayerSq, 0xFF, 0x14, 0x96);
    } else {
        func_8013ECE0(actor->xyzDistToPlayerSq, 0xB4, 0x14, 0x64);
    }
    func_800BC770(gameState, arg2, arg3);
}

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ Gfx* unk_14;
    /* 0x18 */ Gfx* unk_18;
} struct_801AEDD4; // size = 0x1C

struct_801AEDD4 D_801AEDD4[] = {
    { 0.540000021458f, 6000.0f, 5000.0, 1.0f, 0.0f, 0x05000230, 0x05000140 },
    { 0.643999993801f, 12000.0f, 8000.0f, 1.0f, 0.0f, 0x06000530, 0x06000400 },
    { 0.6400000453f, 8500.0f, 8000.0f, 1.75f, 0.10000000149f, 0x05000230, 0x05000140 },
};

// Actor_DrawDoorLock
void func_800BC8B8(GlobalContext* globalCtx, s32 frame, s32 type) {
    s32 pad[2];
    MtxF spA8;
    s32 phi_s1;
    f32 temp_f22;
    f32 temp_f24;
    struct_801AEDD4* temp_s2;
    f32 phi_f20;
    f32 phi_f2;

    temp_s2 = &D_801AEDD4[type];
    phi_f20 = temp_s2->unk_10;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    SysMatrix_InsertTranslation(0.0f, temp_s2->unk_08, 500.0f, MTXMODE_APPLY);
    SysMatrix_CopyCurrentState(&spA8);

    temp_f22 = __sinf(temp_s2->unk_00 - phi_f20) * -(10 - frame) * 0.1f * temp_s2->unk_04;
    temp_f24 = __cosf(temp_s2->unk_00 - phi_f20) * (10 - frame) * 0.1f * temp_s2->unk_04;

    for (phi_s1 = 0; phi_s1 < 4; phi_s1++) {
        SysMatrix_SetCurrentState(&spA8);
        SysMatrix_InsertZRotation_f(phi_f20, 1);
        SysMatrix_InsertTranslation(temp_f22, temp_f24, 0.0f, 1);
        if (temp_s2->unk_0C != 1.0f) {
            Matrix_Scale(temp_s2->unk_0C, temp_s2->unk_0C, temp_s2->unk_0C, 1);
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, temp_s2->unk_14);

        if ((phi_s1 % 2) != 0) {
            phi_f2 = 2.0f * temp_s2->unk_00;
        } else {
            phi_f2 = M_PI - (2.0f * temp_s2->unk_00);
        }
        phi_f20 += phi_f2;
    }

    SysMatrix_SetCurrentState(&spA8);
    Matrix_Scale(frame * 0.1f, frame * 0.1f, frame * 0.1f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, temp_s2->unk_18);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BCB50(GlobalContext* arg0, Vec3f* arg1) {
    CollisionCheck_SpawnShieldParticlesMetal(arg0, arg1);
}

void func_800BCB70(Actor* actor, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    if ((arg1 == 0x8000) && !(arg2 & 0x8000)) {
        Audio_PlayActorSound2(actor, 0x3836);
    }
    actor->colorFilterParams = arg1 | arg3 | ((arg2 & 0xF8) << 5) | arg4;
    actor->colorFilterTimer = arg4;
}

Hilite* func_800BCBF4(Vec3f* arg0, GlobalContext* globalCtx) {
    Vec3f lightDir;

    // lightDir.x = globalCtx->envCtx.dirLight1.params.dir.x;
    lightDir.x = globalCtx->envCtx.unk_28.params.dir.x;
    lightDir.y = globalCtx->envCtx.unk_28.params.dir.y;
    lightDir.z = globalCtx->envCtx.unk_28.params.dir.z;

    return func_800B7FE0(arg0, &globalCtx->view.eye, &lightDir, globalCtx->state.gfxCtx);
}

Hilite* func_800BCC68(Vec3f* arg0, GlobalContext* globalCtx) {
    Vec3f sp1C;

    sp1C.x = globalCtx->envCtx.unk_28.params.dir.x;
    sp1C.y = globalCtx->envCtx.unk_28.params.dir.y;
    sp1C.z = globalCtx->envCtx.unk_28.params.dir.z;
    return func_800B8018(arg0, &globalCtx->view.eye, &sp1C, globalCtx->state.gfxCtx);
}

#ifdef NON_MATCHING
// small regalloc
void func_800BCCDC(Vec3s* points, s32 pathcount, Vec3f* pos1, Vec3f* pos2, s32 parm5) {
    s32 spB4;
    s32 spB0;
    s32 spA8[2] = { 0, 0 };
    s32 spA0[2] = { 0, 0 };
    Vec3f sp94;
    Vec3f sp7C[2];
    Vec3f sp70;
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp54[2];

    spB0 = 0;
    sp5C = 1.6e9f;

    for (spB4 = 0; spB4 < pathcount; spB4++) {
        sp60 = Math3D_XZDistanceSquared(pos1->x, pos1->z, points[spB4].x, points[spB4].z);
        if (sp60 < sp5C) {
            sp5C = sp60;
            spB0 = spB4;
        }
    }

    sp94.x = points[spB0].x;
    sp94.z = points[spB0].z;
    pos2->y = points[spB0].y;
    if (spB0 != 0) {
        sp64.x = points[spB0 - 1].x;
        sp64.z = points[spB0 - 1].z;
    } else if (parm5) {
        sp64.x = points[pathcount - 1].x;
        sp64.z = points[pathcount - 1].z;
    }

    if ((spB0 != 0) || (parm5)) {
        spA8[0] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp64.x, sp64.z, sp94.x, sp94.z, &sp7C[0].x, &sp7C[0].z, &sp60);
    }

    if (spB0 + 1 != pathcount) {
        sp70.x = points[spB0 + 1].x;
        sp70.z = points[spB0 + 1].z;
    } else if (parm5) {
        sp70.x = points->x;
        sp70.z = points->z;
    }

    if ((spB0 + 1 != pathcount) || (parm5)) {
        spA8[1] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp94.x, sp94.z, sp70.x, sp70.z, &sp7C[1].x, &sp7C[1].z, &sp60);
    }

    if (parm5) {
        s32 phi_s0_2;

        spA0[0] = ((sp64.x - pos1->x) * (sp94.z - pos1->z)) < ((sp64.z - pos1->z) * (sp94.x - pos1->x));
        spA0[1] = ((sp70.z - pos1->z) * (sp94.x - pos1->x)) < ((sp94.z - pos1->z) * (sp70.x - pos1->x));

        for (phi_s0_2 = 0; phi_s0_2 < ARRAY_COUNT(sp54); phi_s0_2++) {
            if ((spA8)[phi_s0_2] != 0) {
                sp54[phi_s0_2] = Math3D_XZDistanceSquared(pos1->x, pos1->z, sp7C[phi_s0_2].x, sp7C[phi_s0_2].z);
            } else {
                sp54[phi_s0_2] = 1.6e9f;
            }
        }
    }

    if ((parm5) && (((spA0[0] != 0) && (spA0[1] != 0)) || ((spA0[0] != 0) && (spA8[0] != 0) && (sp54[0] < sp54[1])) ||
                    ((spA0[1] != 0) && (spA8[1] != 0) && (sp54[1] < sp54[0])))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else if ((spA8[0] != 0) && (spA8[1] != 0)) {
        if ((spA0[0] == 0) && (spA0[1] == 0)) {
            if (Math3D_PointDistToLine2D(pos1->x, pos1->z, sp7C[0].x, sp7C[0].z, sp7C[1].x, sp7C[1].z, &pos2->x,
                                         &pos2->z, &sp60) == 0) {
                pos2->x = (sp7C[1].x + sp7C[0].x) * 0.5f;
                pos2->z = (sp7C[1].z + sp7C[0].z) * 0.5f;
            }
        } else if (sp54[1] < sp54[0]) {
            pos2->x = sp7C[1].x;
            pos2->z = sp7C[1].z;
        } else {
            pos2->x = sp7C[0].x;
            pos2->z = sp7C[0].z;
        }
    } else if (spA8[0] != 0) {
        pos2->x = sp7C[0].x;
        pos2->z = sp7C[0].z;
    } else if (spA8[1] != 0) {
        pos2->x = sp7C[1].x;
        pos2->z = sp7C[1].z;
    } else if ((parm5) && ((((sp64.x - pos1->x) * (sp70.z - pos1->z)) < ((sp64.z - pos1->z) * (sp70.x - pos1->x))))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else {
        pos2->x = sp94.x;
        pos2->z = sp94.z;
    }
}
#else
s32 D_801AEE28[] = { 0, 0 };
s32 D_801AEE30[] = { 0, 0 };
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCCDC.s")
#endif

// unused
s32 func_800BD2B4(GameState* gameState, Actor* actor, s16* arg2, f32 arg3, u16 (*arg4)(GameState*, Actor*),
                  s16 (*arg5)(GameState*, Actor*)) {
    if (Actor_RequestTalk(actor, gameState)) {
        *arg2 = 1;
        return 1;
    } else if (*arg2 != 0) {
        *arg2 = arg5(gameState, actor);
        return 0;
    } else if (func_800B8934(gameState, actor) == 0) {
        return 0;
    } else if (!func_800B8614(actor, gameState, arg3)) {
        return 0;
    } else {
        actor->textId = arg4(gameState, actor);
        return 0;
    }
}

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 unk_0C;
} struct_801AEE38_0; // size = 0x10

typedef struct {
    /* 0x00 */ struct_801AEE38_0 sub_00;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
} struct_801AEE38; // size = 0x18

struct_801AEE38 D_801AEE38[] = {
    { { 0x1C20, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xEAAC, 0x1554, 0x1554, 0xF8E4, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x31C4, 0xE390, 0xE38, 0xE38, 0xF1C8, 0x71C, 1 }, 170.0f, 0x3FFC },
    { { 0x1554, 0xF1C8, 0, 0x71C, 0xF8E4, 0, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF8E4, 0x71C, 0xE38, 0xD558, 0x2AA8, 1 }, 170.0f, 0x3FFC },
    { { 0, 0xE390, 0x2AA8, 0x3FFC, 0xF1C8, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0, 0xE38, 0, 0x1C70, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0xF1C8, 0, 0, 0, 1 }, 0.0f, 0 },
    { { 0x71C, 0xF1C8, 0xE38, 0x1C70, 0, 0, 1 }, 0.0f, 0 },
    { { 0xE38, 0xF1C8, 0, 0x1C70, 0, 0xE38, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xE390, 0x1C70, 0xE38, 0xF1C8, 0xE38, 1 }, 0.0f, 0 },
    { { 0x18E2, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2A6C, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
};

void func_800BD384(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   u8 arg8) {
    s16 sp46;
    s16 sp44;
    s16 temp2;
    s16 sp40;
    s16 temp1;
    Vec3f sp30;

    sp30.x = actor->world.pos.x;
    sp30.y = actor->world.pos.y + arg1->unk_14;
    sp30.z = actor->world.pos.z;

    sp46 = Math_Vec3f_Pitch(&sp30, &arg1->unk_18);
    sp44 = Math_Vec3f_Yaw(&sp30, &arg1->unk_18);
    sp40 = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18) - actor->shape.rot.y;

    temp1 = CLAMP(sp40, -arg2, arg2);
    Math_SmoothStepToS(&arg1->unk_08.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_08.y = CLAMP(arg1->unk_08.y, -temp1, temp1);

    sp40 -= arg1->unk_08.y;

    temp1 = CLAMP(sp40, -arg5, arg5);
    Math_SmoothStepToS(&arg1->unk_0E.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_0E.y = CLAMP(arg1->unk_0E.y, -temp1, temp1);

    if (arg8) {
        Math_SmoothStepToS(&actor->shape.rot.y, sp44, 6, 2000, 1);
    }

    temp1 = CLAMP(sp46, arg4, (s16)(u16)arg3);
    Math_SmoothStepToS(&arg1->unk_08.x, temp1, 6, 2000, 1);

    temp2 = sp46 - arg1->unk_08.x;

    temp1 = CLAMP(temp2, arg7, arg6);
    Math_SmoothStepToS(&arg1->unk_0E.x, temp1, 6, 2000, 1);
}

// unused
s16 func_800BD6B8(s16 arg0) {
    return D_801AEE38[arg0].unk_14;
}

s16 func_800BD6E4(Actor* actor, struct_800BD888_arg1* arg1, f32 arg2, s16 arg3, s16 flag) {
    s32 pad;

    if (flag) {
        return flag;
    } else if (arg1->unk_00 != 0) {
        return 4;
    } else if (arg2 < Math_Vec3f_DistXYZ(&actor->world.pos, &arg1->unk_18)) {
        arg1->unk_04 = 0;
        arg1->unk_06 = 0;
        return 1;
    } else {
        s16 yaw = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18);
        s16 phi_a0 = ABS_ALT(BINANG_SUB(yaw, actor->shape.rot.y));

        if (arg3 >= phi_a0) {
            arg1->unk_04 = 0;
            arg1->unk_06 = 0;
            return 2;
        } else if (DECR(arg1->unk_04) != 0) {
            return arg1->unk_02;
        } else {
            switch (arg1->unk_06) {
                case 0:
                case 2:
                    arg1->unk_04 = Rand_S16Offset(30, 30);
                    arg1->unk_06++;
                    return 1;

                case 1:
                    arg1->unk_04 = Rand_S16Offset(10, 10);
                    arg1->unk_06++;
                    return 3;

                default:
                    return 4;
            }
        }
    }
}

// This function is very similar to OoT's func_80034A14
void func_800BD888(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3) {
    struct_801AEE38_0 sp38;

    arg1->unk_02 = func_800BD6E4(actor, arg1, D_801AEE38[arg2].unk_10, D_801AEE38[arg2].unk_14, arg3);
    sp38 = D_801AEE38[arg2].sub_00;

    switch (arg1->unk_02) {
        case 1:
            sp38.unk_00 = 0;
            sp38.unk_04 = 0;
            sp38.unk_02 = 0;
        case 3:
            sp38.unk_06 = 0;
            sp38.unk_0A = 0;
            sp38.unk_08 = 0;
        case 2:
            sp38.unk_0C = 0;
    }

    func_800BD384(actor, arg1, sp38.unk_00, sp38.unk_04, sp38.unk_02, sp38.unk_06, sp38.unk_0A, sp38.unk_08,
                  sp38.unk_0C);
}

Gfx D_801AEF88[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          G_RM_FOG_SHADE_A,
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

Gfx D_801AEFA0[] = {
    gsSPEndDisplayList(),
};

void* func_800BD9A0(GraphicsContext* gfxCtx) {
    Gfx* displayListHead;
    Gfx* displayList;

    displayListHead = displayList = GRAPH_ALLOC(gfxCtx, 0x10);

    gDPSetRenderMode(displayListHead++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         G_RM_FOG_SHADE_A,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gSPEndDisplayList(displayListHead++);

    return displayList;
}

// unused
void func_800BD9E0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_OPA_DISP++, 0x0C, gEmptyDL);

    POLY_OPA_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BDAA0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0C, func_800BD9A0(globalCtx->state.gfxCtx));

    POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_XLU_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// Unused
s16 func_800BDB6C(Actor* actor, GlobalContext* globalCtx, s16 arg2, f32 arg3) {
    Player* player = GET_PLAYER(globalCtx);
    f32 phi_f2;

    if ((globalCtx->csCtx.state != 0) || (D_801D0D50 != 0)) {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &globalCtx->view.eye) * 0.25f;
    } else {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &player->actor.world.pos);
    }

    if (arg3 < phi_f2) {
        actor->flags &= -2;
        Math_SmoothStepToS(&arg2, 0, 6, 0x14, 1);
    } else {
        actor->flags |= 1;
        Math_SmoothStepToS(&arg2, 0xFF, 6, 0x14, 1);
    }

    return arg2;
}

void func_800BDC5C(SkelAnime* skelAnime, ActorAnimationEntry* animation, s32 index) {
    f32 frameCount;

    animation += index;
    if (animation->frameCount > 0.0f) {
        frameCount = animation->frameCount;
    } else {
        frameCount = SkelAnime_GetFrameCount(&animation->animation->common);
    }

    SkelAnime_ChangeAnim(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                         animation->mode, animation->morphFrames);
}

// Unused
void func_800BDCF4(GlobalContext* globalCtx, s16* arg1, s16* arg2, s32 size) {
    s32 frames = globalCtx->gameplayFrames;
    s32 i;

    for (i = 0; i < size; i++) {
        arg1[i] = (0x814 + 50 * i) * frames;
        arg2[i] = (0x940 + 50 * i) * frames;
    }
}

void Actor_Noop(Actor* actor, GlobalContext* globalCtx) {
}

#include "z_cheap_proc.c"

Actor* func_800BE0B8(GlobalContext* globalCtx, Actor* inActor, s16 arg2, u8 arg3, f32 arg4) {
    Actor* actor = globalCtx->actorCtx.actorList[arg3].first;

    while (actor != NULL) {
        if (actor == inActor || ((arg2 != -1) && (arg2 != actor->id))) {
            actor = actor->next;
            continue;
        }

        if (Actor_DistanceBetweenActors(inActor, actor) <= arg4) {
            return actor;
        }

        actor = actor->next;
    }

    return NULL;
}

#ifdef NON_MATCHING
// regalloc
s32 func_800BE184(GameState* gameState, Actor* actor, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s16 temp_a2;
    s16 temp_t0;
    s16 temp_v1;
    s16 temp_t8;
    Player* player;
    s16 phi_v0;

    player = GET_PLAYER(globalCtx);

    temp_a2 = actor->yawTowardsPlayer;
    temp_t0 = temp_a2 - arg5;

    temp_t8 = BINANG_ADD(temp_a2, 0x8000);
    phi_v0 = BINANG_SUB(temp_t8, player->actor.shape.rot.y);

    if ((!temp_t0)) {}

    if ((actor->xzDistToPlayer <= arg2) && (player->swordState != 0)) {
        if (arg4 >= ABS_ALT(phi_v0) && arg3 >= ABS_ALT(temp_t0)) {
            return 1;
        }
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE184.s")
s32 func_800BE184(GameState* gameState, Actor* actor, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
#endif

u8 Actor_ApplyDamage(Actor* actor) {
    if (actor->colChkInfo.damage >= actor->colChkInfo.health) {
        actor->colChkInfo.health = 0;
    } else {
        actor->colChkInfo.health -= actor->colChkInfo.damage;
    }
    return actor->colChkInfo.health;
}

void func_800BE258(Actor* actor, ColliderInfo* colInfo) {
    ColliderInfo* temp_v0 = colInfo->acHitInfo;

    if (temp_v0 == NULL) {
        actor->dropFlag = 0;
    } else if ((temp_v0->toucher.dmgFlags & 0x800) != 0) {
        actor->dropFlag = 1;
    } else if ((temp_v0->toucher.dmgFlags & 0x1000) != 0) {
        actor->dropFlag = 2;
    } else if ((temp_v0->toucher.dmgFlags & 0x2000) != 0) {
        actor->dropFlag = 0x20;
    } else {
        actor->dropFlag = 0;
    }
}

void func_800BE2B8(Actor* actor, ColliderJntSph* jntSphere) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    ColliderJntSphElement* new_var2;
    s32 phi_v1;
    s32 phi_v0;
    ColliderInfo* temp_a2;

    actor->dropFlag = 0;

    for (phi_v1 = jntSphere->count - 1; phi_v1 >= 0; phi_v1--) {
        new_var2 = &jntSphere->elements[phi_v1];
        temp_a2 = new_var2->info.acHitInfo;

        if (temp_a2 == NULL) {
            phi_v0 = 0;
        } else {
            temp_v0_2 = temp_a2->toucher.dmgFlags;

            if (temp_v0_2 & 0x800) {
                phi_v0 = 1;
            } else if (temp_v0_2 & 0x1000) {
                phi_v0 = 2;
            } else {
                phi_v0 = (temp_v0_2 & 0x2000) ? 0x20 : 0;
            }
        }

        actor->dropFlag |= phi_v0;
    }
}

void func_800BE33C(Vec3f* arg0, Vec3f* arg1, Vec3s* arg2, s32 arg3) {
    f32 sp24 = arg1->x - arg0->x;
    f32 sp20 = arg1->z - arg0->z;
    f32 sp1C;

    if (arg3) {
        sp1C = arg1->y - arg0->y;
    } else {
        sp1C = arg0->y - arg1->y;
    }
    arg2->y = Math_FAtan2F(sp20, sp24);
    arg2->x = Math_FAtan2F(sqrtf(SQ(sp24) + SQ(sp20)), sp1C);
}

#ifdef NON_MATCHING
// stack
void func_800BE3D0(Actor* actor, s16 arg1, Vec3s* arg2) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s32 pad[2];
    f32 sp2C;
    s32 pad2;

    if (actor->floorPoly != 0) {
        CollisionPoly* floorPoly = actor->floorPoly;

        sp44 = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        sp40 = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        sp3C = COLPOLY_GET_NORMAL(floorPoly->normal.z);

        sp38 = Math_SinS(arg1);
        sp34 = Math_CosS(arg1);
        arg2->x = (s16)-Math_Atan2S((-(sp44 * sp38) - (sp3C * sp34)) * sp40, 1.0f);

        sp2C = Math_SinS(arg1 - 0x3FF7);
        sp30 = Math_CosS(arg1 - 0x3FF7);
        arg2->z = (s16)-Math_Atan2S((-(sp44 * sp2C) - (sp3C * sp30)) * sp40, 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE3D0.s")
#endif

void func_800BE504(Actor* actor, ColliderCylinder* collider) {
    if ((collider->info.acHitInfo->toucher.dmgFlags & 0x13820)) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

void func_800BE568(Actor* actor, ColliderSphere* collider) {
    if (collider->info.acHitInfo->toucher.dmgFlags & (0x13820)) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

void func_800BE5CC(Actor* actor, ColliderJntSph* collider, s32 arg2) {
    if (collider->elements[arg2].info.acHitInfo->toucher.dmgFlags & (0x13820)) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

s32 func_800BE63C(EnBox* box) {
    if ((box->unk_1F1 == 5) || (box->unk_1F1 == 6) || (box->unk_1F1 == 7) || (box->unk_1F1 == 8) || (box->unk_1F1 == 0xC)) {
        return true;
    }
    return false;
}

UNK_TYPE4 D_801AEFA8[] = {
    0x04091DE0,
    0x04091FE0,
    0x040921E0,
    0x040923E0,
};

// has lots of gfx macros
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE680.s")

static Color_RGBA8 D_801AEFB8 = { 170, 255, 255, 255 };
static Color_RGBA8 D_801AEFBC = { 200, 200, 255, 255 };
static Vec3f D_801AEFC0 = { 0.0f, -1.0f, 0.0f };

void func_800BF7CC(GlobalContext* globalCtx, Actor* actor, Vec3f* limbPos, s32 arg3, s32 arg4, f32 arg5, f32 arg6) {
    s32 sp94;
    s32 pad;
    Vec3f sp84;
    s16 temp_s0;
    s16 temp_s2;
    s32 phi_s1;
    phi_s1 = arg3;

    Audio_PlaySoundAtPosition(globalCtx, &actor->world.pos, 0x1E, 0x28CB);

    for (sp94 = 0; sp94 < arg3; sp94++) {
        temp_s2 = Actor_YawToPoint(actor, limbPos);

        for (phi_s1 = 0; phi_s1 < arg4; phi_s1++) {
            temp_s0 = (Rand_Next() >> 0x13) + temp_s2;
            sp84.z = Rand_ZeroFloat(5.0f);
            sp84.x = Math_SinS(temp_s0) * sp84.z;
            sp84.y = Rand_ZeroFloat(4.0f) + 8.0f;
            sp84.z *= Math_CosS(temp_s0);
            EffectSsEnIce_Spawn(globalCtx, limbPos, Rand_ZeroFloat(arg6) + arg5, &sp84, &D_801AEFC0, &D_801AEFB8,
                                &D_801AEFBC, 30);
        }

        limbPos++;
    }
}
