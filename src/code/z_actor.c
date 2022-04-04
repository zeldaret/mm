/*
 * File: z_actor.c
 * Description:
 */

#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"
#include "overlays/actors/ovl_En_Part/z_en_part.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_bdoor/object_bdoor.h"

// bss
extern FaultClient sActorFaultClient; // 2 funcs
extern CollisionPoly* D_801ED8B0;     // 1 func
extern s32 D_801ED8B4;                // 2 funcs
extern Actor* D_801ED8B8;             // 2 funcs
extern Actor* D_801ED8BC;             // 2 funcs
extern Actor* D_801ED8C0;             // 2 funcs
extern Actor* D_801ED8C4;             // 2 funcs
extern f32 D_801ED8C8;                // 2 funcs
extern f32 sBgmEnemyDistSq;           // 2 funcs
extern f32 D_801ED8D0;                // 2 funcs
extern s32 D_801ED8D4;                // 2 funcs
extern s32 D_801ED8D8;                // 2 funcs
extern s16 D_801ED8DC;                // 2 funcs
extern Mtx D_801ED8E0;                // 1 func
extern Actor* D_801ED920;             // 2 funcs. 1 out of z_actor

// Internal forward declarations
void func_800BA8B8(GlobalContext* globalCtx, ActorContext* actorCtx);
Actor* Actor_SpawnEntry(ActorContext* actorCtx, ActorEntry* actorEntry, GlobalContext* globalCtx);
Actor* Actor_Delete(ActorContext* actorCtx, Actor* actor, GlobalContext* globalCtx);
void func_800BB8EC(GameState* gameState, ActorContext* actorCtx, Actor** arg2, Actor** arg3, Player* player);
s32 func_800BA2FC(GlobalContext* globalCtx, Actor* actor, Vec3f* projectedPos, f32 projectedW);
void Actor_AddToCategory(ActorContext* actorCtx, Actor* actor, u8 actorCategory);
Actor* Actor_RemoveFromCategory(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actorToRemove);

void Actor_PrintLists(ActorContext* actorCtx) {
    ActorListEntry* actorList = &actorCtx->actorLists[0];
    Actor* actor;
    s32 i;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor\n", gMaxActorId);
    FaultDrawer_Printf("No. Actor   Name Part SegName\n");

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++) {
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
            shadowScale = 1.0f - (dy * (1.0f / 350.0f));
            if ((dy * (1.0f / 350.0f)) > 1.0f) {
                shadowScale = 0.0f;
            }

            if (color != NULL) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, color->r, color->g, color->b,
                                (u8)(actor->shape.shadowAlpha * shadowScale));
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(actor->shape.shadowAlpha * shadowScale));
            }

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &mtx);
            Matrix_SetCurrentState(&mtx);

            if ((dlist != gCircleShadowDL) || (actor->scale.x != actor->scale.z)) {
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

    ActorShadow_Draw(actor, lights, globalCtx, gCircleShadowDL, NULL);
}

void ActorShadow_DrawSquare(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, gSquareShadowDL, NULL);
}

void ActorShadow_DrawWhiteCircle(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    static Color_RGBA8 color = { 255, 255, 255, 255 };

    ActorShadow_Draw(actor, lights, globalCtx, gCircleShadowDL, &color);
}

void ActorShadow_DrawHorse(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, gHorseShadowDL, NULL);
}

void ActorShadow_DrawFoot(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 lightNum, f32 shadowAlpha,
                          f32 shadowScaleX, f32 shadowScaleZ) {
    s32 pad;
    s16 sp58;
    f32 dir2;
    f32 dir0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(CLAMP_MAX(lightNum * 1.3e-05f, 1.0f) * shadowAlpha));

    dir0 = light->l.dir[0];
    dir2 = light->l.dir[2];
    sp58 = Math_FAtan2F(dir2, dir0);
    shadowScaleZ *= (4.5f - (light->l.dir[1] * 0.035f));
    shadowScaleZ = CLAMP_MIN(shadowScaleZ, 1.0f);
    Matrix_SetCurrentState(arg2);
    Matrix_RotateY(sp58, MTXMODE_APPLY);
    Matrix_Scale(shadowScaleX, 1.0f, shadowScaleX * shadowScaleZ, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, gFootShadowDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ActorShadow_DrawFeet(Actor* actor, Lights* mapper, GlobalContext* globalCtx) {
    f32 distToFloor = actor->world.pos.y - actor->floorHeight;

    if (distToFloor > 0.0f) {
        f32 shadowScale = actor->shape.shadowScale;
        u8 shadowAlpha = actor->shape.shadowAlpha;
        f32 alphaRatio;

        if ((actor->id == ACTOR_PLAYER) && (((Player*)actor)->stateFlags3 & 0x8000)) {
            f32 tmpScaleZ = actor->scale.z;

            actor->scale.z += 0.03f * fabsf(Math_CosS(((Player*)actor)->unk_AAA));
            actor->shape.shadowScale *= 0.2f;
            alphaRatio = distToFloor * 0.03f;
            actor->shape.shadowAlpha = actor->shape.shadowAlpha * CLAMP_MAX(alphaRatio, 1.0f);
            ActorShadow_Draw(actor, mapper, globalCtx, gCircleShadowDL, NULL);
            actor->scale.z = tmpScaleZ;
        } else {
            actor->shape.shadowScale *= 0.3f;
            alphaRatio = (distToFloor - 20.0f) * 0.02f;
            actor->shape.shadowAlpha = actor->shape.shadowAlpha * CLAMP_MAX(alphaRatio, 1.0f);
            ActorShadow_DrawCircle(actor, mapper, globalCtx);
        }

        actor->shape.shadowScale = shadowScale;
        actor->shape.shadowAlpha = shadowAlpha;
    }

    if (distToFloor < 200.0f) {
        MtxF sp13C;
        MtxF spFC;
        CollisionPoly* spF8;
        s32 bgId;
        f32 floorHeight[2];
        f32 pad;
        f32 shadowAlpha;
        f32 shadowScaleX;
        f32 shadowScaleZ;
        Light* lightPtr;
        s32 lightNumMax;
        s32 i;
        s32 j;
        s32 lightNum;
        Vec3f* feetPosPtr;
        s32 numLights;
        f32* floorHeightPtr;
        s32 spB8;

        numLights = mapper->numLights - 2;
        feetPosPtr = actor->shape.feetPos;
        floorHeightPtr = floorHeight;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
        actor->shape.feetFloorFlags = 0;
        spB8 = 2;

        for (i = 0; i < ARRAY_COUNT(floorHeight); i++, spB8 >>= 1) {
            feetPosPtr->y += 50.0f;
            *floorHeightPtr = func_80169100(globalCtx, &sp13C, &spF8, &bgId, feetPosPtr);
            feetPosPtr->y -= 50.0f;

            distToFloor = feetPosPtr->y - *floorHeightPtr;
            if ((distToFloor >= -1.0f) && (distToFloor < 500.0f)) {
                lightNumMax = 0;

                if (distToFloor <= 10.0f) {
                    actor->shape.feetFloorFlags |= spB8;

                    if ((actor->depthInWater < 0.0f) && (bgId == 0x32) && ((actor->shape.unk_17 & spB8) != 0)) {
                        if (func_800C9C24(&globalCtx->colCtx, spF8, bgId, 1) != 0) {
                            SkinMatrix_MtxFCopy(&sp13C, &spFC);
                            SkinMatrix_MulYRotation(&spFC, actor->shape.rot.y);
                            EffFootmark_Add(globalCtx, &spFC, actor, i, feetPosPtr, (actor->shape.shadowScale * 0.3f),
                                            IREG(88) + 80, IREG(89) + 60, IREG(90) + 40, 30000, 200, 60);
                        }
                        actor->shape.unk_17 &= ~spB8;

                        if (!mapper->l.l) {} // POSSIBLE FAKE MATCH
                    }
                }

                if (distToFloor > 30.0f) {
                    distToFloor = 30.0f;
                }

                shadowAlpha = actor->shape.shadowAlpha * (1.0f - (distToFloor * (1 / 30.0f)));
                shadowScaleZ = 1.0f - (distToFloor * (1.0f / 70.0f));
                shadowScaleX = actor->shape.shadowScale * shadowScaleZ * actor->scale.x;

                for (lightPtr = mapper->l.l, j = 0; j < numLights; lightPtr++, j++) {
                    if (lightPtr->l.dir[1] > 0) {
                        lightNum = (lightPtr->l.col[0] + lightPtr->l.col[1] + lightPtr->l.col[2]) *
                                   ABS_ALT(lightPtr->l.dir[1]);

                        if (lightNum > 0) {
                            lightNumMax += lightNum;
                            ActorShadow_DrawFoot(globalCtx, lightPtr, &sp13C, lightNum, shadowAlpha, shadowScaleX,
                                                 shadowScaleZ);
                        }
                    }
                }

                for (j = 0; j < 2; lightPtr++, j++) {
                    if (lightPtr->l.dir[1] > 0) {
                        lightNum = ((lightPtr->l.col[0] + lightPtr->l.col[1] + lightPtr->l.col[2]) *
                                    ABS_ALT(lightPtr->l.dir[1])) -
                                   (lightNumMax * 8);
                        if (lightNum > 0) {
                            ActorShadow_DrawFoot(globalCtx, lightPtr, &sp13C, lightNum, shadowAlpha, shadowScaleX,
                                                 shadowScaleZ);
                        }
                    }
                }
            }
            feetPosPtr++;
            floorHeightPtr++;
        }

        if (!(actor->bgCheckFlags & 1)) {
            actor->shape.feetFloorFlags = 0;
        } else if (actor->shape.feetFloorFlags == 3) {
            f32 footDistY = actor->shape.feetPos[FOOT_LEFT].y - actor->shape.feetPos[FOOT_RIGHT].y;

            if ((floorHeight[0] + footDistY) < (floorHeight[1] - footDistY)) {
                actor->shape.feetFloorFlags = 2;
            } else {
                actor->shape.feetFloorFlags = 1;
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void Actor_SetFeetPos(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                      Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        Matrix_MultiplyVector3fByState(leftFootPos, &actor->shape.feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        Matrix_MultiplyVector3fByState(rightFootPos, &actor->shape.feetPos[FOOT_RIGHT]);
    }
}

void func_800B4AEC(GlobalContext* globalCtx, Actor* actor, f32 y) {
    s32 floorBgId;
    f32 yPos = actor->world.pos.y;

    actor->world.pos.y += y;
    actor->floorHeight = BgCheck_EntityRaycastFloor5_2(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &floorBgId,
                                                       actor, &actor->world.pos);
    actor->floorBgId = floorBgId;
    actor->world.pos.y = yPos;
}

void func_800B4B50(Actor* actor, Lights* mapper, GlobalContext* globalCtx) {
    f32 spEC;
    f32 temp_f12;
    f32 shadowScaleZ;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f8;
    s32 lightNum;
    MtxF sp94;
    s32 numLights;
    s8 phi_v1;
    u8 temp_v0;
    Light* phi_s0;
    s32 lightNumMax;

    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    if (actor->floorPoly != NULL) {
        s32 j;

        spEC = actor->world.pos.y - actor->floorHeight;
        if (spEC > 20.0f) {
            f32 temp_f20 = actor->shape.shadowScale;

            temp_v0 = actor->shape.shadowAlpha;
            actor->shape.shadowScale *= 0.3f;
            temp_f12 = (spEC - 20.0f) * 0.02f;
            actor->shape.shadowAlpha = CLAMP_MAX(temp_f12, 1.0f) * actor->shape.shadowAlpha;
            ActorShadow_DrawCircle(actor, mapper, globalCtx);
            actor->shape.shadowScale = temp_f20;
            actor->shape.shadowAlpha = temp_v0;
        } else if (spEC >= -1.0f) {
            numLights = mapper->numLights - 2;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &sp94);
            temp_f22 = (f32)actor->shape.shadowAlpha * (1.0f - (spEC * (1.0f / 30.0f)));
            phi_s0 = mapper->l.l;
            shadowScaleZ = 1.0f - (spEC * (1.0f / 70.0f));
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
                    lightNum = ((phi_s0->l.col[0] + phi_s0->l.col[1] + phi_s0->l.col[2]) * ABS_ALT(phi_s0->l.dir[1])) -
                               (8 * lightNumMax);
                    if (lightNum > 0) {
                        ActorShadow_DrawFoot(globalCtx, phi_s0, &sp94, lightNum, temp_f22, temp_f24, shadowScaleZ);
                    }
                }
            }
            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void Actor_GetProjectedPos(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, f32* arg3) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, arg1, arg2, arg3);
    if (*arg3 < 1.0f) {
        *arg3 = 1.0f;
    } else {
        *arg3 = 1.0f / *arg3;
    }
}

void Target_SetPos(TargetContext* targetCtx, s32 index, f32 x, f32 y, f32 z) {
    targetCtx->unk50[index].pos.x = x;
    targetCtx->unk50[index].pos.y = y;
    targetCtx->unk50[index].pos.z = z;
    targetCtx->unk50[index].unkC = targetCtx->unk44;
}

typedef struct {
    /* 0x0 */ Color_RGBA8 inner;
    /* 0x4 */ Color_RGBA8 outer;
} TatlColor; // size = 0x8

TatlColor sTatlColorList[] = {
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 255, 255, 230, 255 }, { 220, 160, 80, 0 } },  { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 150, 150, 255, 255 }, { 150, 150, 255, 0 } }, { { 255, 255, 0, 255 }, { 200, 155, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 255, 255, 0, 255 }, { 200, 155, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },         { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } },
    { { 0, 255, 0, 255 }, { 0, 255, 0, 0 } }
};

void func_800B4F78(TargetContext* targetCtx, s32 type, GlobalContext* globalCtx) {
    TatlColor* tatlColorEntry;
    s32 i;
    TargetContextEntry* targetEntry;

    Math_Vec3f_Copy(&targetCtx->targetCenterPos, &globalCtx->view.eye);
    targetCtx->unk48 = 0x100;
    tatlColorEntry = &sTatlColorList[type];
    targetCtx->unk44 = 500.0f;

    targetEntry = targetCtx->unk50;
    for (i = 0; i < ARRAY_COUNT(targetCtx->unk50); i++, targetEntry++) {
        Target_SetPos(targetCtx, i, 0.0f, 0.0f, 0.0f);

        targetEntry->color.r = tatlColorEntry->inner.r;
        targetEntry->color.g = tatlColorEntry->inner.g;
        targetEntry->color.b = tatlColorEntry->inner.b;
    }
}

void Target_SetColors(TargetContext* targetCtx, Actor* actor, s32 type, GlobalContext* globalCtx) {
    targetCtx->unk0.x = actor->focus.pos.x;
    targetCtx->unk0.y = actor->focus.pos.y + (actor->targetArrowOffset * actor->scale.y);
    targetCtx->unk0.z = actor->focus.pos.z;

    targetCtx->fairyInner.r = sTatlColorList[type].inner.r;
    targetCtx->fairyInner.g = sTatlColorList[type].inner.g;
    targetCtx->fairyInner.b = sTatlColorList[type].inner.b;
    targetCtx->fairyInner.a = sTatlColorList[type].inner.a;
    targetCtx->fairyOuter.r = sTatlColorList[type].outer.r;
    targetCtx->fairyOuter.g = sTatlColorList[type].outer.g;
    targetCtx->fairyOuter.b = sTatlColorList[type].outer.b;
    targetCtx->fairyOuter.a = sTatlColorList[type].outer.a;
}

void Actor_TargetContextInit(TargetContext* targetCtx, Actor* actor, GlobalContext* globalCtx) {
    targetCtx->bgmEnemy = NULL;
    targetCtx->unk8C = NULL;
    targetCtx->targetedActor = NULL;
    targetCtx->arrowPointedActor = NULL;
    targetCtx->unk4B = 0;
    targetCtx->unk4C = 0;
    targetCtx->unk40 = 0.0f;
    Target_SetColors(targetCtx, actor, actor->category, globalCtx);
    func_800B4F78(targetCtx, actor->category, globalCtx);
}

void Actor_DrawZTarget(TargetContext* targetCtx, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x300006C2)) {
        Actor* actor = targetCtx->targetedActor;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        if (targetCtx->unk48 != 0) {
            TargetContextEntry* entry;
            s16 alpha = 255;
            f32 var1 = 1.0f;
            Vec3f spBC;
            s32 spB8;
            f32 spB4;
            s32 spB0;
            s32 spAC;
            f32 var2;
            s32 i;

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
                alpha = targetCtx->unk48;
            }

            Actor_GetProjectedPos(globalCtx, &targetCtx->targetCenterPos, &spBC, &spB4);

            spBC.x = (160 * (spBC.x * spB4)) * var1;
            spBC.x = CLAMP(spBC.x, -320.0f, 320.0f);

            spBC.y = (120 * (spBC.y * spB4)) * var1;
            spBC.y = CLAMP(spBC.y, -240.0f, 240.0f);

            spBC.z = spBC.z * var1;

            targetCtx->unk4C--;
            if (targetCtx->unk4C < 0) {
                targetCtx->unk4C = 2;
            }

            Target_SetPos(targetCtx, targetCtx->unk4C, spBC.x, spBC.y, spBC.z);

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

                        Matrix_InsertTranslation(entry->pos.x, entry->pos.y, 0.0f, MTXMODE_NEW);
                        Matrix_Scale(var2, 0.15f, 1.0f, MTXMODE_APPLY);

                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, entry->color.r, entry->color.g, entry->color.b,
                                        (u8)alpha);

                        Matrix_InsertZRotation_s((targetCtx->unk4B * 512), MTXMODE_APPLY);

                        for (i = 0; i < 4; i++) {
                            Matrix_InsertZRotation_s(0x4000, MTXMODE_APPLY);
                            Matrix_StatePush();
                            Matrix_InsertTranslation(entry->unkC, entry->unkC, 0.0f, MTXMODE_APPLY);
                            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                      G_MTX_MODELVIEW | G_MTX_LOAD);
                            gSPDisplayList(OVERLAY_DISP++, gZTargetLockOnTriangleDL);
                            Matrix_StatePop();
                        }
                    }

                    alpha -= 255 / 3;
                    if (alpha < 0) {
                        alpha = 0;
                    }
                }
            }
        }

        actor = targetCtx->unk_94;
        if ((actor != NULL) && !(actor->flags & ACTOR_FLAG_8000000)) {
            TatlColor* color = &sTatlColorList[actor->category];

            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0x07);

            Matrix_InsertTranslation(actor->focus.pos.x,
                                     actor->focus.pos.y + (actor->targetArrowOffset * actor->scale.y) + 17.0f,
                                     actor->focus.pos.z, MTXMODE_NEW);
            Matrix_RotateY((globalCtx->gameplayFrames * 3000), MTXMODE_APPLY);
            Matrix_Scale((iREG(27) + 35) / 1000.0f, (iREG(28) + 60) / 1000.0f, (iREG(29) + 50) / 1000.0f,
                         MTXMODE_APPLY);

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, color->inner.r, color->inner.g, color->inner.b, 255);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_XLU_DISP++, gZTargetArrowDL);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

// OoT: func_8002C7BC
void func_800B5814(TargetContext* targetCtx, Player* player, Actor* actor, GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    Actor* sp68 = NULL;
    s32 category;
    Vec3f sp58;
    f32 sp54;

    if ((player->unk_730 != 0) && (player->unk_AE3[player->unk_ADE] == 2)) {
        targetCtx->unk_94 = NULL;
    } else {
        func_800BB8EC(gameState, &globalCtx->actorCtx, &sp68, &D_801ED920, player);
        targetCtx->unk_94 = sp68;
    }

    if (targetCtx->unk8C != 0) {
        sp68 = targetCtx->unk8C;
        targetCtx->unk8C = NULL;
    } else if (actor != 0) {
        sp68 = actor;
    }

    if (sp68 != NULL) {
        category = sp68->category;
    } else {
        category = player->actor.category;
    }

    if ((sp68 != targetCtx->arrowPointedActor) || (category != targetCtx->unk4A)) {
        targetCtx->arrowPointedActor = sp68;
        targetCtx->unk4A = category;
        targetCtx->unk40 = 1.0f;
    }

    if (sp68 == NULL) {
        sp68 = &player->actor;
    }

    if (!Math_StepToF(&targetCtx->unk40, 0.0f, 0.25f)) {
        f32 temp_f0;
        f32 x;
        f32 y;
        f32 z;

        temp_f0 = 0.25f / targetCtx->unk40;

        x = sp68->focus.pos.x - targetCtx->unk0.x;
        y = (sp68->focus.pos.y + (sp68->targetArrowOffset * sp68->scale.y)) - targetCtx->unk0.y;
        z = sp68->focus.pos.z - targetCtx->unk0.z;

        targetCtx->unk0.x += x * temp_f0;
        targetCtx->unk0.y += y * temp_f0;
        targetCtx->unk0.z += z * temp_f0;
    } else {
        Target_SetColors(targetCtx, sp68, category, globalCtx);
    }

    if (actor != NULL && targetCtx->unk4B == 0) {
        Actor_GetProjectedPos(globalCtx, &actor->focus.pos, &sp58, &sp54);
        if ((sp58.z <= 0.0f) || (fabsf(sp58.x * sp54) >= 1.0f) || (fabsf(sp58.y * sp54) >= 1.0f)) {
            actor = NULL;
        }
    }

    if (actor != NULL) {
        if (actor != targetCtx->targetedActor) {
            s32 sfxId;

            func_800B4F78(targetCtx, actor->category, globalCtx);

            targetCtx->targetedActor = actor;

            if (actor->id == ACTOR_EN_BOOM) {
                targetCtx->unk48 = 0;
            }

            sfxId =
                CHECK_FLAG_ALL(actor->flags, ACTOR_FLAG_4 | ACTOR_FLAG_1) ? NA_SE_SY_LOCK_ON : NA_SE_SY_LOCK_ON_HUMAN;
            play_sound(sfxId);
        }

        targetCtx->targetCenterPos.x = actor->world.pos.x;
        targetCtx->targetCenterPos.y = actor->world.pos.y - (actor->shape.yOffset * actor->scale.y);
        targetCtx->targetCenterPos.z = actor->world.pos.z;

        if (targetCtx->unk4B == 0) {
            f32 temp_f0_2;
            f32 clampedFloat;

            temp_f0_2 = (500.0f - targetCtx->unk44) * 3.0f;
            clampedFloat = CLAMP(temp_f0_2, 30.0f, 100.0f);

            if (Math_StepToF(&targetCtx->unk44, 80.0f, clampedFloat)) {
                targetCtx->unk4B++;
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

/* Start of Flags section */

/**
 * Tests if current scene switch flag is set.
 */
s32 Flags_GetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return globalCtx->actorCtx.flags.switches[(flag & ~0x1F) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

/**
 * Sets current scene switch flag.
 */
void Flags_SetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.flags.switches[(flag & ~0x1F) >> 5] |= 1 << (flag & 0x1F);
    }
}

/**
 * Unsets current scene switch flag.
 */
void Flags_UnsetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.flags.switches[(flag & ~0x1F) >> 5] &= ~(1 << (flag & 0x1F));
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

/**
 * Overrides the all the chest flags.
 */
void Flags_SetAllTreasure(GlobalContext* globalCtx, s32 flag) {
    globalCtx->actorCtx.flags.chest = flag;
}

/**
 * Returns all the chest flags.
 */
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

/* End of Flags section */

/* Start of TitleCard section */

void TitleCard_ContextInit(GameState* gameState, TitleCardContext* titleCtx) {
    titleCtx->durationTimer = 0;
    titleCtx->delayTimer = 0;
    titleCtx->intensity = 0;
    titleCtx->alpha = 0;
}

void TitleCard_InitBossName(GameState* gameState, TitleCardContext* titleCtx, TexturePtr texture, s16 x, s16 y,
                            u8 width, u8 height) {
    titleCtx->texture = texture;
    titleCtx->x = x;
    titleCtx->y = y;
    titleCtx->width = width;
    titleCtx->height = height;
    titleCtx->durationTimer = 80;
    titleCtx->delayTimer = 0;
}

void TitleCard_InitPlaceName(GameState* gameState, TitleCardContext* titleCtx, TexturePtr texture, s32 x, s32 y,
                             s32 width, s32 height, s32 delay) {
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
    if (titleCtx->alpha != 0) {
        s32 width = titleCtx->width;
        s32 height = titleCtx->height;
        s32 unk1;
        s32 spC0;
        s32 sp38;
        s32 spB8;
        s32 spB4;
        s32 temp;

        temp = width * 2;
        spC0 = (titleCtx->x * 4) - temp;
        spB8 = (titleCtx->y * 4) - (height * 2);
        sp38 = width * 2;

        OPEN_DISPS(gameState->gfxCtx);

        height = (width * height > TMEM_SIZE) ? TMEM_SIZE / width : height;
        spB4 = spB8 + (height * 4);

        if (1) {}

        OVERLAY_DISP = func_8012C014(OVERLAY_DISP);

        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, (u8)titleCtx->intensity, (u8)titleCtx->intensity, (u8)titleCtx->intensity,
                        (u8)titleCtx->alpha);

        gDPLoadTextureBlock(OVERLAY_DISP++, (s32*)titleCtx->texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, spC0, spB8, ((sp38 * 2) + spC0) - 4, spB8 + (height * 4) - 1,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

        height = titleCtx->height - height;

        if (height > 0) {
            gDPLoadTextureBlock(OVERLAY_DISP++, (s32)titleCtx->texture + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, width,
                                height, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, spC0, spB4, ((sp38 * 2) + spC0) - 4, spB4 + (height * 4) - 1,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }

        CLOSE_DISPS(gameState->gfxCtx);
    }
}

/* End of TitleCard section */

// unused
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
        return false;
    }

    globalCtx->actorCtx.unk1F4 = arg1;
    globalCtx->actorCtx.unk1F5 = arg2;
    globalCtx->actorCtx.unk1F8 = arg3;
    Math_Vec3f_Copy(&globalCtx->actorCtx.unk1FC, arg4);

    return true;
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

/**
 * Initializes an element of the `globalCtx->actorCtx.unk_20C` array to the `arg2` pointer, or allocates one using the
 * `size` argument in case `arg2` is NULL. This element is associated to an `id`
 *
 * In success returns the allocated pointer if `arg2` was NULL or the `arg2` pointer otherwise
 * In failure (There's no space left in `globalCtx->actorCtx.unk_20C` or an allocation error happened) returns NULL
 *
 * Note there are no duplicated id checks.
 *
 * Used only by EnLiftNuts.
 */
void* func_800B6584(GlobalContext* globalCtx, s16 id, void* arg2, size_t size) {
    ActorContext_unk_20C* entry = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (entry->id == 0) {
            if (arg2 == NULL) {
                arg2 = ZeldaArena_Malloc(size);
                if (arg2 == NULL) {
                    return NULL;
                }
                entry->isDynamicallyInitialised = true;
            }

            entry->id = id;
            entry->ptr = arg2;
            return arg2;
        }

        entry++;
    }

    return NULL;
}

/**
 * Frees the first element of `globalCtx->actorCtx.unk_20C` with id `id`.
 *
 * If success, the free'd pointer is returned.
 * If failure, NULL is returned.
 *
 * Used only by EnLiftNuts.
 */
void* func_800B6608(GlobalContext* globalCtx, s16 id) {
    ActorContext_unk_20C* entry = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (id == entry->id) {
            entry->id = 0;
            if (entry->isDynamicallyInitialised) {
                ZeldaArena_Free(entry->ptr);
                entry->isDynamicallyInitialised = false;
            }
            return entry->ptr;
        }

        entry++;
    }

    return NULL;
}

/**
 * Retrieves the first pointer stored with the id `id`.
 * If there's no pointer stored with that id, NULL is returned.
 *
 * Used only by EnLiftNuts.
 */
void* func_800B6680(GlobalContext* globalCtx, s16 id) {
    ActorContext_unk_20C* entry = globalCtx->actorCtx.unk_20C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->actorCtx.unk_20C); i++) {
        if (id == entry->id) {
            return entry->ptr;
        }

        entry++;
    }

    return NULL;
}

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~ACTOR_FLAG_1;
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
    gSegments[0x06] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}

void Actor_Init(Actor* actor, GlobalContext* globalCtx) {
    Actor_SetWorldToHome(actor);
    Actor_SetShapeRotToWorld(actor);
    Actor_SetFocus(actor, 0.0f);
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01f);
    actor->targetMode = 3;
    actor->terminalVelocity = -20.0f;

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

/**
 * Update actor position using velocity and any push from z_collision_check.
 */
void Actor_UpdatePos(Actor* actor) {
    f32 speedRate = actorMovementScale;

    actor->world.pos.x += (actor->velocity.x * speedRate) + actor->colChkInfo.displacement.x;
    actor->world.pos.y += (actor->velocity.y * speedRate) + actor->colChkInfo.displacement.y;
    actor->world.pos.z += (actor->velocity.z * speedRate) + actor->colChkInfo.displacement.z;
}

/**
 * Updates actor's velocity accounting for gravity (without exceeding terminal velocity)
 * The operation is performed in cylindrical coordinates
 *
 * It is recommended to not call this function directly and use `Actor_MoveWithGravity` instead
 */
void Actor_UpdateVelocityWithGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_SinS(actor->world.rot.y);
    actor->velocity.z = actor->speedXZ * Math_CosS(actor->world.rot.y);

    actor->velocity.y += actor->gravity;
    if (actor->velocity.y < actor->terminalVelocity) {
        actor->velocity.y = actor->terminalVelocity;
    }
}

/**
 * Moves actor accounting for its current velocity and applying gravity
 * The operation is performed in cylindrical coordinates
 */
void Actor_MoveWithGravity(Actor* actor) {
    Actor_UpdateVelocityWithGravity(actor);
    Actor_UpdatePos(actor);
}

/**
 * Updates actor's velocity, ignoring gravity
 * The operation is performed in spherical coordinates
 *
 * It is recommended to not call this function directly and use `Actor_MoveWithoutGravity` instead
 */
void Actor_UpdateVelocityWithoutGravity(Actor* actor) {
    f32 horizontalSpeed = Math_CosS(actor->world.rot.x) * actor->speedXZ;

    actor->velocity.x = Math_SinS(actor->world.rot.y) * horizontalSpeed;
    actor->velocity.y = Math_SinS(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * horizontalSpeed;
}

/**
 * Moves actor accounting for its current velocity, without applying gravity
 * The operation is performed in spherical coordinates
 *
 * Useful for flying or swimming actors
 */
void Actor_MoveWithoutGravity(Actor* actor) {
    Actor_UpdateVelocityWithoutGravity(actor);
    Actor_UpdatePos(actor);
}

/**
 * Like `Actor_UpdateVelocityWithoutGravity`, but the actor is moved backwards instead of forwards
 *
 * It is recommended to not call this function directly and use `Actor_MoveWithoutGravityReverse` instead
 */
void Actor_UpdateVelocityWithoutGravityReverse(Actor* actor) {
    f32 horizontalSpeed = Math_CosS(-actor->world.rot.x) * actor->speedXZ;

    actor->velocity.x = Math_SinS(actor->world.rot.y) * horizontalSpeed;
    actor->velocity.y = Math_SinS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * horizontalSpeed;
}

/**
 * Like `Actor_MoveWithoutGravity`, but the actor is moved backwards instead of forwards
 */
void Actor_MoveWithoutGravityReverse(Actor* actor) {
    Actor_UpdateVelocityWithoutGravityReverse(actor);
    Actor_UpdatePos(actor);
}

/**
 * Sets horizontal speed and Y velocity using the `speed` argument and current pitch
 */
void Actor_SetSpeeds(Actor* actor, f32 speed) {
    actor->speedXZ = Math_CosS(actor->world.rot.x) * speed;
    actor->velocity.y = -Math_SinS(actor->world.rot.x) * speed;
}

// unused
void Actor_UpdatePosFromSkelAnime(Actor* actor, SkelAnime* skelAnime) {
    Vec3f pos;

    SkelAnime_UpdateTranslation(skelAnime, &pos, actor->shape.rot.y);
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

/**
 * Find the offset of a point from an actor in that actor's own coordinates (origin at the actor's
 * world.pos, z-axis is facing angle, i.e. shape.rot.y)
 *
 * @param[in]  actor  The actor whose coordinate system to transform to.
 * @param[out] offset The transformed coordinates.
 * @param[in]  point  The point to transform to actor coordinates.
 */
void Actor_OffsetOfPointInActorCoords(Actor* actor, Vec3f* offset, Vec3f* point) {
    f32 cos = Math_CosS(actor->shape.rot.y);
    f32 sin = Math_SinS(actor->shape.rot.y);
    f32 diffX;
    f32 diffZ;

    // Shift X,Z to actor coordinates origin
    diffX = point->x - actor->world.pos.x;
    diffZ = point->z - actor->world.pos.z;

    // Rotate X and Z offsets to align Z to actor's shape.rot.y
    offset->x = ((diffX * cos) - (diffZ * sin));
    offset->z = ((diffZ * cos) + (diffX * sin));

    // Shift Y to origin
    offset->y = point->y - actor->world.pos.y;
}

f32 Actor_HeightDiff(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

/**
 * Sets the current and new inputs.
 */
void func_800B6F20(GlobalContext* globalCtx, Input* input, f32 magnitude, s16 baseYaw) {
    s16 relativeYaw = baseYaw - Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));

    input->cur.stick_x = -Math_SinS(relativeYaw) * magnitude;
    input->rel.stick_x = input->cur.stick_x;
    input->cur.stick_y = Math_CosS(relativeYaw) * magnitude;
    input->rel.stick_y = input->cur.stick_y;
}

f32 Player_GetHeight(Player* player) {
    f32 extraHeight;

    if (player->stateFlags1 & 0x800000) {
        extraHeight = 32.0f;
    } else {
        extraHeight = 0.0f;
    }

    switch (player->transformation) {
        default:
        case PLAYER_FORM_FIERCE_DEITY:
            return extraHeight + 124.0f;
        case PLAYER_FORM_GORON:
            // (player->stateFlags3 & 0x1000): being curled?
            return extraHeight + ((player->stateFlags3 & 0x1000) ? 34.0f : 80.0f);
        case PLAYER_FORM_ZORA:
            return extraHeight + 68.0f;
        case PLAYER_FORM_DEKU:
            return extraHeight + 36.0f;
        case PLAYER_FORM_HUMAN:
            return extraHeight + 44.0f;
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
    return player->stateFlags1 & 0x8;
}

s32 func_800B7128(Player* player) {
    return func_800B7118(player) && player->unk_ACC;
}

s32 func_800B715C(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->stateFlags2 & 0x8;
}

void Actor_SetCameraHorseSetting(GlobalContext* globalCtx, Player* player) {
    if ((globalCtx->roomCtx.currRoom.unk3 != 4) && (player->actor.id == ACTOR_PLAYER)) {
        EnHorse* rideActor = (EnHorse*)player->rideActor;

        if ((rideActor != NULL) && !(rideActor->unk_1EC & 0x10)) {
            func_800DFAC8(Play_GetCamera(globalCtx, CAM_ID_MAIN), 4);
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

u32 func_800B7298(GlobalContext* globalCtx, Actor* actor, u8 csMode) {
    Player* player = GET_PLAYER(globalCtx);

    if (func_800B724C(globalCtx, actor, csMode)) {
        player->unk_3BA = 1;
        return true;
    }
    return false;
}

// Unused
void func_800B72E0(DynaPolyActor* dyna) {
    dyna->unk14C = 0.0f;
    dyna->pushForce = 0.0f;
}

void func_800B72F8(DynaPolyActor* dyna, f32 extraPushForce, s16 yRotation) {
    dyna->yRotation = yRotation;
    dyna->pushForce += extraPushForce;
}

/**
 * Check if the player is facing the specified actor.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngleDiff`.
 */
s32 Player_IsFacingActor(Actor* actor, s16 maxAngleDiff, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yawDiff = BINANG_ADD(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;

    if (ABS_ALT(yawDiff) < maxAngleDiff) {
        return true;
    }
    return false;
}

/**
 * Check if `actorB` is facing `actorA`.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngle`.
 *
 * This function is unused in the original game.
 */
s32 Actor_ActorBIsFacingActorA(Actor* actorA, Actor* actorB, s16 maxAngleDiff) {
    s16 angle = BINANG_ROT180(Actor_YawBetweenActors(actorA, actorB));
    s16 dist = angle - actorB->shape.rot.y;

    if (ABS_ALT(dist) < maxAngleDiff) {
        return true;
    }

    return false;
}

/**
 * Check if the specified actor is facing the player.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngleDiff`.
 */
s32 Actor_IsFacingPlayer(Actor* actor, s16 angle) {
    s16 dist = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(dist) < angle) {
        return true;
    }
    return false;
}

/**
 * Check if `actorA` is facing `actorB`.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngleDiff`.
 */
s32 Actor_ActorAIsFacingActorB(Actor* actorA, Actor* actorB, s16 maxAngleDiff) {
    s16 dist = Actor_YawBetweenActors(actorA, actorB) - actorA->shape.rot.y;

    if (ABS_ALT(dist) < maxAngleDiff) {
        return true;
    }
    return false;
}

/**
 * Check if the specified actor is facing the player and is nearby.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngleDiff`.
 * The maximum distance that qualifies as "nearby" is specified by `range`.
 */
s32 Actor_IsFacingAndNearPlayer(Actor* actor, f32 range, s16 maxAngleDiff) {
    s16 yaw = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(yaw) < maxAngleDiff) {
        s16 pad;

        if (sqrtf(SQ(actor->xzDistToPlayer) + SQ(actor->playerHeightRel)) < range) {
            return true;
        }
    }

    return false;
}

/**
 * Check if `actorA` is facing `actorB` and is nearby.
 * The maximum angle difference that qualifies as "facing" is specified by `maxAngleDiff`.
 * The maximum distance that qualifies as "nearby" is specified by `range`.
 */
s32 Actor_ActorAIsFacingAndNearActorB(Actor* actorA, Actor* actorB, f32 range, s16 maxAngleDiff) {
    if (Actor_DistanceBetweenActors(actorA, actorB) < range) {
        s16 dist = Actor_YawBetweenActors(actorA, actorB) - actorA->shape.rot.y;

        if (ABS_ALT(dist) < maxAngleDiff) {
            return true;
        }
    }
    return false;
}

/* Start of BgCheck related section */

void func_800B75A0(CollisionPoly* poly, Vec3f* normal, s16* azimuth) {
    normal->x = COLPOLY_GET_NORMAL(poly->normal.x);
    normal->y = COLPOLY_GET_NORMAL(poly->normal.y);
    normal->z = COLPOLY_GET_NORMAL(poly->normal.z);
    *azimuth = Math_FAtan2F(normal->z, normal->x);
}

s32 func_800B761C(Actor* actor, f32 arg1, s32 arg2) {
    if (actor->bgCheckFlags & 1) {
        actor->bgCheckFlags &= ~1;
        actor->bgCheckFlags |= 4;

        if ((actor->velocity.y < 0.0f) && (arg2 & 0x10)) {
            actor->velocity.y = 0.0f;
        }
        return false;
    }

    return true;
}

s32 func_800B7678(GlobalContext* globalCtx, Actor* actor, Vec3f* pos, s32 flags) {
    f32 distToFloor;
    s32 bgId;

    pos->y += (flags & 0x800) ? 10.0f : 50.0f;

    actor->floorHeight =
        BgCheck_EntityRaycastFloor5_2(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &bgId, actor, pos);
    actor->bgCheckFlags &= ~(0x80 | 0x04 | 0x02);
    if (actor->floorHeight <= BGCHECK_Y_MIN) {
        return func_800B761C(actor, BGCHECK_Y_MIN, flags);
    }

    distToFloor = actor->floorHeight - actor->world.pos.y;
    actor->floorBgId = bgId;
    if ((distToFloor >= 0.0f) || (((actor->bgCheckFlags & 1)) && !(actor->bgCheckFlags & 0x800) &&
                                  (distToFloor >= -11.0f) && (actor->velocity.y < 0.0f))) {
        actor->bgCheckFlags |= 0x80;

        if (actor->bgCheckFlags & 0x10) {
            if (bgId != D_801ED8B4) {
                if (distToFloor > 15.0f) {
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
                actor->bgCheckFlags |= 2;
            } else if ((flags & 8) && (actor->gravity < 0.0f)) {
                actor->velocity.y = -4.0f;
            } else if (!(flags & 0x100)) {
                actor->velocity.y = 0.0f;
            }

            actor->bgCheckFlags |= 1;
            BgCheck2_AttachToMesh(&globalCtx->colCtx, actor, (s32)actor->floorBgId);
        }
    } else {
        return func_800B761C(actor, distToFloor, flags);
    }

    return true;
}

void Actor_UpdateBgCheckInfo(GlobalContext* globalCtx, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, u32 flags) {
    f32 sp94 = actor->world.pos.y - actor->prevPos.y;
    s32 pad;
    Vec3f pos;

    if ((actor->floorBgId != BGCHECK_SCENE) && (actor->bgCheckFlags & 1)) {
        BgCheck2_UpdateActorAttachedToMesh(&globalCtx->colCtx, actor->floorBgId, actor);
    }

    if (flags & 1) {
        s32 bgId;

        actor->bgCheckFlags &= ~0x1000;
        if ((!(flags & 0x80) &&
             (BgCheck_EntitySphVsWall3(&globalCtx->colCtx, &pos, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                                       &actor->wallPoly, &bgId, actor, wallCheckHeight))) ||
            ((flags & 0x80) &&
             (BgCheck_EntitySphVsWall4(&globalCtx->colCtx, &pos, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                                       &actor->wallPoly, &bgId, actor, wallCheckHeight)))) {
            CollisionPoly* sp7C = actor->wallPoly;

            actor->bgCheckFlags |= 8;
            if ((flags & 0x200) && (actor->bgCheckFlags & 0x1000) && ((s32)sp7C->normal.y > 0) &&
                (sqrtf(SQXYZ(actor->colChkInfo.displacement)) < 10.0f)) {
                actor->bgCheckFlags &= ~8;
            } else if (actor->bgCheckFlags & 8) {
                Math_Vec3f_Copy(&actor->world.pos, &pos);
            }

            actor->wallYaw = Math_FAtan2F(sp7C->normal.z, sp7C->normal.x);
            actor->wallBgId = bgId;
        } else {
            actor->bgCheckFlags &= ~8;
        }
    }

    pos.x = actor->world.pos.x;
    pos.z = actor->world.pos.z;
    if (flags & 2) {
        f32 y;

        pos.y = actor->prevPos.y + 4.0f;
        if (BgCheck_EntityCheckCeiling(&globalCtx->colCtx, &y, &pos, (ceilingCheckHeight + sp94) - 4.0f, &D_801ED8B0,
                                       &D_801ED8B4, actor)) {
            actor->bgCheckFlags |= 0x10;
            actor->world.pos.y = (y + sp94) - 4.0f;
        } else {
            actor->bgCheckFlags &= ~0x10;
        }
    }
    if (flags & 4) {
        WaterBox* waterbox;
        f32 y;

        pos.y = actor->prevPos.y;
        func_800B7678(globalCtx, actor, &pos, flags);
        y = actor->world.pos.y;

        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &y,
                                 &waterbox)) {
            actor->depthInWater = y - actor->world.pos.y;
            if (actor->depthInWater <= 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if (!(actor->bgCheckFlags & 0x20)) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if (!(flags & 0x40)) {
                    Vec3f sp64;

                    sp64.x = actor->world.pos.x;
                    sp64.y = y;
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
            actor->depthInWater = BGCHECK_Y_MIN;
        }
    }

    if (flags & 0x400) {
        WaterBox* waterbox;
        f32 y = actor->world.pos.y;

        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &y,
                                 &waterbox)) {
            actor->depthInWater = y - actor->world.pos.y;

            if (actor->depthInWater < 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if (!(actor->bgCheckFlags & 0x20)) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if (!(flags & 0x40)) {
                    Vec3f sp50;

                    sp50.x = actor->world.pos.x;
                    sp50.y = y;
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
            actor->depthInWater = BGCHECK_Y_MIN;
        }
    }
}

Gfx* Hilite_Draw(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx, Gfx* dl, Hilite** hilite) {
    LookAt* lookAt = GRAPH_ALLOC(gfxCtx, sizeof(LookAt));
    f32 correctedEyeX = (eye->x == object->x) && (eye->z == object->z) ? eye->x + 0.001f : eye->x;

    *hilite = GRAPH_ALLOC(gfxCtx, sizeof(Hilite));

    guLookAtHilite(&D_801ED8E0, lookAt, *hilite, correctedEyeX, eye->y, eye->z, object->x, object->y, object->z, 0.0f,
                   1.0f, 0.0f, lightDir->x, lightDir->y, lightDir->z, lightDir->x, lightDir->y, lightDir->z, 0x10,
                   0x10);

    gSPLookAt(dl++, lookAt);
    gDPSetHilite1Tile(dl++, 1, *hilite, 0x10, 0x10);

    return dl;
}

Hilite* Hilite_DrawOpa(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* hilite;

    OPEN_DISPS(gfxCtx);

    POLY_OPA_DISP = Hilite_Draw(object, eye, lightDir, gfxCtx, POLY_OPA_DISP, &hilite);

    CLOSE_DISPS(gfxCtx);

    return hilite;
}

Hilite* Hilite_DrawXlu(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* hilite;

    OPEN_DISPS(gfxCtx);

    POLY_XLU_DISP = Hilite_Draw(object, eye, lightDir, gfxCtx, POLY_XLU_DISP, &hilite);

    CLOSE_DISPS(gfxCtx);

    return hilite;
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

f32 func_800B82EC(Actor* actor, Player* player, s16 angle) {
    f32 temp_f12;
    s16 temp_v0 = BINANG_SUB(BINANG_SUB(actor->yawTowardsPlayer, 0x8000), angle);
    s16 yaw = ABS_ALT(temp_v0);

    if (player->unk_730 != NULL) {
        if ((yaw > 0x4000) || ((actor->flags & ACTOR_FLAG_8000000))) {
            return FLT_MAX;
        }

        temp_f12 = actor->xyzDistToPlayerSq - ((actor->xyzDistToPlayerSq * 0.8f) * ((0x4000 - yaw) * (1.0f / 0x8000)));
        return temp_f12;
    }

    if (yaw >= 0x2AAB) {
        return FLT_MAX;
    }
    return actor->xyzDistToPlayerSq;
}

#define TARGET_RANGE(range, leash) \
    { SQ(range), (f32)range / leash }

TargetRangeParams gTargetRanges[] = {
    TARGET_RANGE(70, 140),   TARGET_RANGE(170, 255),    TARGET_RANGE(280, 5600),      TARGET_RANGE(350, 525),
    TARGET_RANGE(700, 1050), TARGET_RANGE(1000, 1500),  TARGET_RANGE(100, 105.36842), TARGET_RANGE(140, 163.33333),
    TARGET_RANGE(240, 576),  TARGET_RANGE(280, 280000), TARGET_RANGE(2500, 3750),
};

s32 func_800B83BC(Actor* actor, f32 arg1) {
    return arg1 < gTargetRanges[actor->targetMode].rangeSq;
}

s32 func_800B83F8(Actor* actor, Player* player, s32 flag) {
    if ((actor->update == NULL) || !(actor->flags & ACTOR_FLAG_1) || (actor->flags & ACTOR_FLAG_8000000)) {
        return true;
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

        return !func_800B83BC(actor, gTargetRanges[actor->targetMode].leashScale * dist);
    }

    return false;
}

s16 D_801AED48[] = {
    0x101, 0x141, 0x111, 0x151, 0x105, 0x145, 0x115, 0x155,
};

s32 Actor_ProcessTalkRequest(Actor* actor, GameState* gameState) {
    if (actor->flags & ACTOR_FLAG_100) {
        actor->flags &= ~ACTOR_FLAG_100;
        return true;
    }

    return false;
}

// Actor_PickUpExchange? Seems to be called with exchangeItemId -1 if the same actor used Actor_PickUp
// This function is also used to toggle the "Speak" action on the A button
s32 func_800B8500(Actor* actor, GlobalContext* globalCtx, f32 xzRange, f32 yRange, s32 exchangeItemId) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->actor.flags & ACTOR_FLAG_100) ||
        ((exchangeItemId > EXCH_ITEM_NONE) && Player_InCsMode(&globalCtx->state)) ||
        (!actor->isTargeted &&
         ((fabsf(actor->playerHeightRel) > fabsf(yRange)) || ((actor->xzDistToPlayer > player->targetActorDistance)) ||
          (xzRange < actor->xzDistToPlayer)))) {
        return false;
    }

    player->targetActor = actor;
    player->targetActorDistance = actor->xzDistToPlayer;
    player->exchangeItemId = exchangeItemId;

    ActorCutscene_SetIntentToPlay(0x7C);
    return true;
}

s32 func_800B85E0(Actor* actor, GlobalContext* globalCtx, f32 radius, s32 exchangeItemId) {
    return func_800B8500(actor, globalCtx, radius, radius, exchangeItemId);
}

s32 func_800B8614(Actor* actor, GlobalContext* globalCtx, f32 radius) {
    return func_800B85E0(actor, globalCtx, radius, EXCH_ITEM_NONE);
}

s32 func_800B863C(Actor* actor, GlobalContext* globalCtx) {
    f32 cylRadius = actor->colChkInfo.cylRadius + 50.0f;

    return func_800B8614(actor, globalCtx, cylRadius);
}

s32 Actor_TextboxIsClosing(Actor* actor, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 2) {
        actor->flags &= ~ACTOR_FLAG_100;
        return true;
    }

    return false;
}

/**
 * Changes the actor the Player is focussing on
 * Fails if Player is not already focussing on an actor or in a talking state
 */
s32 Actor_ChangeFocus(Actor* actor1, GlobalContext* globalCtx, Actor* actor2) {
    Actor* targetActor;
    Player* player = GET_PLAYER(globalCtx);

    targetActor = player->targetActor;

    if ((player->actor.flags & ACTOR_FLAG_100) && (targetActor != NULL)) {
        player->targetActor = actor2;
        player->unk_730 = actor2;
        return true;
    }

    return false;
}

s32 Player_GetExchangeItemId(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    return player->exchangeItemId;
}

s32 func_800B8718(Actor* actor, GameState* gameState) {
    if (actor->flags & ACTOR_FLAG_20000000) {
        actor->flags &= ~ACTOR_FLAG_20000000;
        return true;
    }

    return false;
}

// Similar to func_800B8500
s32 func_800B874C(Actor* actor, GlobalContext* globalCtx, f32 xzRange, f32 yRange) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->actor.flags & ACTOR_FLAG_20000000) || Player_InCsMode(&globalCtx->state) ||
        (yRange < fabsf(actor->playerHeightRel)) || ((player->unk_A94 < actor->xzDistToPlayer)) ||
        (xzRange < actor->xzDistToPlayer)) {
        return false;
    }

    player->unk_A90 = actor;
    player->unk_A94 = actor->xzDistToPlayer;
    return true;
}

s32 func_800B8804(Actor* actor, GlobalContext* globalCtx, f32 xzRange) {
    return func_800B874C(actor, globalCtx, xzRange, 20.0f);
}

s32 func_800B882C(Actor* actor, GlobalContext* globalCtx) {
    f32 cylRadius = actor->colChkInfo.cylRadius + 50.0f;

    return func_800B8804(actor, globalCtx, cylRadius);
}

s32 func_800B886C(Actor* actor, GlobalContext* globalCtx) {
    if (!(GET_PLAYER(globalCtx)->actor.flags & ACTOR_FLAG_20000000)) {
        return true;
    }

    return false;
}

void Actor_GetScreenPos(GlobalContext* globalCtx, Actor* actor, s16* x, s16* y) {
    Vec3f projectedPos;
    f32 w;

    Actor_GetProjectedPos(globalCtx, &actor->focus.pos, &projectedPos, &w);
    *x = (projectedPos.x * w * (SCREEN_WIDTH / 2)) + (SCREEN_WIDTH / 2);
    *y = (projectedPos.y * w * -(SCREEN_HEIGHT / 2)) + (SCREEN_HEIGHT / 2);
}

s32 func_800B8934(GlobalContext* globalCtx, Actor* actor) {
    Vec3f sp2C;
    f32 sp28;
    s32 pad[2];

    Actor_GetProjectedPos(globalCtx, &actor->focus.pos, &sp2C, &sp28);

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
 * Allows to pick up an item (GetItem or GI), lift an actor or catch various actors in bottles
 * within the specified range.
 *
 * GI_NONE is usually used as a special case to lift an actor
 * GI_MAX is usually used to catch an actor in a bottle
 */
s32 Actor_PickUp(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x3C7080) && Player_GetExplosiveHeld(player) < 0) {
        if ((actor->xzDistToPlayer <= xzRange) && (fabsf(actor->playerHeightRel) <= fabsf(yRange))) {
            if (((getItemId == GI_MASK_CIRCUS_LEADER) || (getItemId == GI_PENDANT_OF_MEMORIES) ||
                 (getItemId == GI_DEED_LAND) ||
                 (((player->heldActor != NULL) || (actor == player->targetActor)) &&
                  (getItemId > GI_NONE && getItemId < GI_MAX))) ||
                (!(player->stateFlags1 & 0x20000800))) {
                s16 yawDiff = actor->yawTowardsPlayer - player->actor.shape.rot.y;
                s32 absYawDiff = ABS_ALT(yawDiff);

                if ((getItemId != GI_NONE) || (player->getItemDirection < absYawDiff)) {
                    player->getItemId = getItemId;
                    player->interactRangeActor = actor;
                    player->getItemDirection = absYawDiff;

                    if ((getItemId > GI_NONE) && (getItemId < GI_MAX)) {
                        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[1]);
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
    if (actor->parent == NULL) {
        return true;
    }

    return false;
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

s32 Actor_HasRider(GlobalContext* globalCtx, Actor* horse) {
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

s32 Actor_HasNoRider(GlobalContext* globalCtx, Actor* horse) {
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
    if (player->currentMask == PLAYER_MASK_GIANT) {
        func_8019F170(&player->actor.projectedPos, sfxId);
    } else {
        Audio_PlaySfxGeneral(sfxId, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
    }
}

/**
 * Plays the sound effect at the actor's position
 */
void Actor_PlaySfxAtPos(Actor* actor, u16 sfxId) {
    Audio_PlaySfxAtPos(&actor->projectedPos, sfxId);
}

void func_800B8EF4(GlobalContext* globalCtx, Actor* actor) {
    u32 sfxId;

    if (actor->bgCheckFlags & 0x20) {
        if (actor->depthInWater < 20.0f) {
            sfxId = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            sfxId = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
    } else {
        sfxId = SurfaceType_GetSfx(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    }

    Audio_PlaySfxAtPos(&actor->projectedPos, NA_SE_EV_BOMB_BOUND);
    Audio_PlaySfxAtPos(&actor->projectedPos, sfxId + SFX_FLAG);
}

void func_800B8F98(Actor* actor, u16 sfxId) {
    actor->sfxId = sfxId;
    actor->audioFlags &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->audioFlags |= 0x02;
}

void func_800B8FC0(Actor* actor, u16 sfxId) {
    actor->sfxId = sfxId;
    actor->audioFlags &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->audioFlags |= 4;
}

void func_800B8FE8(Actor* actor, u16 sfxId) {
    actor->sfxId = sfxId;
    actor->audioFlags &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->audioFlags |= 0x08;
}

void func_800B9010(Actor* actor, u16 sfxId) {
    actor->sfxId = sfxId;
    actor->audioFlags &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->audioFlags |= 0x01;
}

void func_800B9038(Actor* actor, s32 timer) {
    actor->audioFlags &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->audioFlags |= 0x10;

    // The sfxId here are not actually sound effects, but instead this is data that gets sent into
    // the io ports of the music macro language (func_801A0810 / Audio_PlaySfxAtPosWithSoundScriptIO is
    // the function that it's used for)
    if (timer < 40) {
        actor->sfxId = 3;
    } else if (timer < 100) {
        actor->sfxId = 2;
    } else {
        actor->sfxId = 1;
    }
}

void func_800B9084(Actor* actor) {
    actor->audioFlags |= 0x20;
}

void func_800B9098(Actor* actor) {
    actor->audioFlags |= 0x40;
}

s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, CollisionPoly* polygon, s32 index, s32 arg4) {
    if (func_800C99D4(&globalCtx->colCtx, polygon, index) == 8) {
        return true;
    }

    return false;
}

void func_800B90F4(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk3 != 0) {
        globalCtx->actorCtx.unk3 = 0;
        func_80115D5C(&globalCtx->state);
    }
}

void func_800B9120(ActorContext* actorCtx) {
    s32 phi_v0 = CURRENT_DAY * 2;

    if (gSaveContext.save.time < CLOCK_TIME(6, 0) || gSaveContext.save.time > CLOCK_TIME(18, 0)) {
        phi_v0++;
    }

    actorCtx->unkC = 0x200 >> phi_v0;
}

void Actor_InitContext(GlobalContext* globalCtx, ActorContext* actorCtx, ActorEntry* actorEntry) {
    ActorOverlay* overlayEntry;
    CycleSceneFlags* cycleFlags;
    s32 i;

    gSaveContext.save.weekEventReg[92] |= 0x80;
    cycleFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneNumber(globalCtx->sceneNum)];

    bzero(actorCtx, sizeof(ActorContext));
    ActorOverlayTable_Init();
    Matrix_MtxFCopy(&globalCtx->billboardMtxF, &gIdentityMtxF);
    Matrix_MtxFCopy(&globalCtx->viewProjectionMtxF, &gIdentityMtxF);

    overlayEntry = gActorOverlayTable;
    for (i = 0; i < ARRAY_COUNT(gActorOverlayTable); i++) {
        overlayEntry->loadedRamAddr = NULL;
        overlayEntry->numLoaded = 0;
        overlayEntry++;
    }

    actorCtx->flags.chest = cycleFlags->chest;
    actorCtx->flags.switches[0] = cycleFlags->switch0;
    actorCtx->flags.switches[1] = cycleFlags->switch1;
    if (globalCtx->sceneNum == SCENE_INISIE_R) {
        cycleFlags = &gSaveContext.cycleSceneFlags[globalCtx->sceneNum];
    }
    actorCtx->flags.collectible[0] = cycleFlags->collectible;
    actorCtx->flags.clearedRoom = cycleFlags->clearedRoom;

    TitleCard_ContextInit(&globalCtx->state, &actorCtx->titleCtxt);
    func_800B6468(globalCtx);

    actorCtx->absoluteSpace = NULL;

    Actor_SpawnEntry(actorCtx, actorEntry, globalCtx);
    Actor_TargetContextInit(&actorCtx->targetContext, actorCtx->actorLists[ACTORCAT_PLAYER].first, globalCtx);
    func_800B9120(actorCtx);
    Fault_AddClient(&sActorFaultClient, (void*)Actor_PrintLists, actorCtx, NULL);
    func_800B722C(&globalCtx->state, (Player*)actorCtx->actorLists[ACTORCAT_PLAYER].first);
}

/**
 * Spawns the actors in the current setup (of the current scene/setup/room triple)
 * Only spawns actors based on the time flags embedded in their rotation parameters
 */
void Actor_SpawnSetupActors(GlobalContext* globalCtx, ActorContext* actorCtx) {
    if (globalCtx->numSetupActors > 0) {
        ActorEntry* actorEntry = globalCtx->setupActorList;
        s32 temp_fp = actorCtx->unkC;
        s32 temp_s1;
        s32 phi_v0;
        s32 i;

        func_800B9120(actorCtx);
        func_800BA8B8(globalCtx, &globalCtx->actorCtx);

        temp_s1 = (actorCtx->unkC * 2) & 0x2FF;

        for (i = 0; i < globalCtx->numSetupActors; i++) {
            phi_v0 = ((actorEntry->rot.x & 7) << 7) | (actorEntry->rot.z & 0x7F);
            if (phi_v0 == 0) {
                phi_v0 = 0x3FF;
            }

            if (!(phi_v0 & temp_fp) && (phi_v0 & actorCtx->unkC) &&
                (!(gSaveContext.eventInf[1] & 0x80) || !(phi_v0 & temp_s1) || !(actorEntry->id & 0x800))) {
                Actor_SpawnEntry(&globalCtx->actorCtx, actorEntry, globalCtx);
            }
            actorEntry++;
        }

        // Prevents re-spawning the setup actors
        globalCtx->numSetupActors = -globalCtx->numSetupActors;
    }
}

typedef struct {
    /* 0x00 */ GlobalContext* globalCtx;
    /* 0x04 */ Actor* actor;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ Actor* unk10;
    /* 0x14 */ Player* player;
    /* 0x18 */ u32 unk_18; // Bitmask of actor flags. The actor will only have main called if it has at least 1
                           // flag set that matches this bitmask
} UpdateActor_Params;      // size = 0x1C

Actor* Actor_UpdateActor(UpdateActor_Params* params) {
    GlobalContext* globalCtx = params->globalCtx;
    Actor* actor = params->actor;
    Actor* nextActor;

    if (actor->world.pos.y < -25000.0f) {
        actor->world.pos.y = -25000.0f;
    }

    actor->sfxId = 0;
    actor->audioFlags &= ~0x7F;

    if (actor->init != NULL) {
        if (Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
            Actor_SetObjectDependency(globalCtx, actor);
            actor->init(actor, globalCtx);
            actor->init = NULL;
        }
        nextActor = actor->next;
    } else if (actor->update == NULL) {
        if (!actor->isDrawn) {
            nextActor = Actor_Delete(&globalCtx->actorCtx, actor, globalCtx);
        } else {
            Actor_Destroy(actor, globalCtx);
            nextActor = actor->next;
        }
    } else {
        if (!Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
            Actor_MarkForDeath(actor);
        } else {
            s32 tmp = (params->unk_08 == 0);

            if (((params->unk_08) && !(actor->flags & params->unk_08)) ||
                ((tmp = (params->unk_08 == 0)) &&
                 (!(actor->flags & ACTOR_FLAG_100000) ||
                  ((actor->category == ACTORCAT_EXPLOSIVES) && (params->player->stateFlags1 & 0x200))) &&
                 (params->unkC != 0) && (actor != params->unk10) && ((actor != params->player->heldActor)) &&
                 (actor->parent != &params->player->actor))) {
                CollisionCheck_ResetDamage(&actor->colChkInfo);
            } else {
                Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
                actor->xzDistToPlayer = Actor_XZDistanceBetweenActors(actor, &params->player->actor);
                actor->playerHeightRel = Actor_HeightDiff(actor, &params->player->actor);
                actor->xyzDistToPlayerSq = SQ(actor->xzDistToPlayer) + SQ(actor->playerHeightRel);

                actor->yawTowardsPlayer = Actor_YawBetweenActors(actor, &params->player->actor);
                actor->flags &= ~ACTOR_FLAG_1000000;

                if ((DECR(actor->freezeTimer) == 0) && (actor->flags & params->unk_18)) {
                    if (actor == params->player->unk_730) {
                        actor->isTargeted = true;
                    } else {
                        actor->isTargeted = false;
                    }

                    if ((actor->targetPriority != 0) && (params->player->unk_730 == 0)) {
                        actor->targetPriority = 0;
                    }

                    Actor_SetObjectDependency(globalCtx, actor);

                    if (actor->colorFilterTimer != 0) {
                        actor->colorFilterTimer--;
                    }

                    actor->update(actor, globalCtx);
                    BgCheck_ResetFlagsIfLoadedActor(globalCtx, &globalCtx->colCtx.dyna, actor);
                }

                CollisionCheck_ResetDamage(&actor->colChkInfo);
            }
        }
        nextActor = actor->next;
    }
    return nextActor;
}

u32 D_801AED58[] = {
    0x100002C2, 0x100002C2, 0x00000200, 0x100006C2, 0x00000282, 0x300002C2,
    0x10000282, 0x00000002, 0x300002C2, 0x100006C2, 0x00000002, 0x100002C2,
};

void Actor_UpdateAll(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s32 i;
    Actor* actor;
    Player* player = GET_PLAYER(globalCtx);
    u32* tmp;
    s32 cat;
    Actor* next;
    ActorListEntry* entry;
    UpdateActor_Params params;

    params.player = player;
    params.globalCtx = globalCtx;

    if (globalCtx->unk_18844 != 0) {
        params.unk_18 = ACTOR_FLAG_200000;
    } else {
        params.unk_18 = ACTOR_FLAG_200000 | ACTOR_FLAG_40 | ACTOR_FLAG_10;
    }

    Actor_SpawnSetupActors(globalCtx, actorCtx);

    if (actorCtx->unk2 != 0) {
        actorCtx->unk2--;
    }

    tmp = D_801AED58;

    if (player->stateFlags2 & 0x8000000) {
        params.unk_08 = 0x2000000;
    } else {
        params.unk_08 = 0;
    }

    if ((player->stateFlags1 & 0x40) && ((player->actor.textId & 0xFF00) != 0x1900)) {
        params.unk10 = player->targetActor;
    } else {
        params.unk10 = NULL;
    }

    for (i = 0, entry = actorCtx->actorLists; i < ARRAY_COUNT(actorCtx->actorLists); entry++, tmp++, i++) {
        params.unkC = *tmp & player->stateFlags1;
        params.actor = entry->first;

        while (params.actor != NULL) {
            params.actor = Actor_UpdateActor(&params);
        }

        if (i == ACTORCAT_BG) {
            DynaPoly_Setup(globalCtx, &globalCtx->colCtx.dyna);
        }
    }

    for (i = 0, entry = actorCtx->actorLists; i < ARRAY_COUNT(actorCtx->actorLists); entry++, i++) {
        if (entry->unk_08 != 0) {
            actor = entry->first;

            while (actor != NULL) {
                if (i == actor->category) {
                    actor = actor->next;
                } else {
                    next = actor->next;
                    cat = actor->category;
                    actor->category = i;
                    Actor_RemoveFromCategory(globalCtx, actorCtx, actor);
                    Actor_AddToCategory(actorCtx, actor, cat);
                    actor = next;
                }
            }
            entry->unk_08 = 0;
        }
    }

    actor = player->unk_730;
    if ((actor != NULL) && (actor->update == NULL)) {
        actor = NULL;
        func_80123DA4(player);
    }

    if ((actor == NULL) || (player->unk_738 < 5)) {
        actor = NULL;
        if (actorCtx->targetContext.unk4B != 0) {
            actorCtx->targetContext.unk4B = 0;
            play_sound(NA_SE_SY_LOCK_OFF);
        }
    }

    if (!(player->stateFlags1 & 2)) {
        func_800B5814(&actorCtx->targetContext, player, actor, &globalCtx->state);
    }

    TitleCard_Update(&globalCtx->state, &actorCtx->titleCtxt);
    func_800B6474(globalCtx);
    DynaPoly_UpdateBgActorTransforms(globalCtx, &globalCtx->colCtx.dyna);
}

void Actor_Draw(GlobalContext* globalCtx, Actor* actor) {
    Lights* light;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    light = LightContext_NewLights(&globalCtx->lightCtx, globalCtx->state.gfxCtx);
    if ((actor->flags & ACTOR_FLAG_10000000) && (globalCtx->roomCtx.currRoom.enablePosLights || (MREG(93) != 0))) {
        light->enablePosLights = true;
    }

    Lights_BindAll(light, globalCtx->lightCtx.listHead,
                   (actor->flags & (ACTOR_FLAG_10000000 | ACTOR_FLAG_400000)) ? NULL : &actor->world.pos, globalCtx);
    Lights_Draw(light, globalCtx->state.gfxCtx);

    if (actor->flags & ACTOR_FLAG_1000) {
        Matrix_SetStateRotationAndTranslation(
            actor->world.pos.x + globalCtx->mainCamera.skyboxOffset.x,
            actor->world.pos.y + ((actor->shape.yOffset * actor->scale.y) + globalCtx->mainCamera.skyboxOffset.y),
            actor->world.pos.z + globalCtx->mainCamera.skyboxOffset.z, &actor->shape.rot);
    } else {
        Matrix_SetStateRotationAndTranslation(actor->world.pos.x,
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
        actor->shape.shadowDraw(actor, light, globalCtx);
    }
    actor->isDrawn = true;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800B9D1C(Actor* actor) {
    s32 sfxId = actor->sfxId;

    if (sfxId != 0) {
        if (actor->audioFlags & 2) {
            Audio_PlaySfxGeneral(sfxId, &actor->projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
        } else if (actor->audioFlags & 4) {
            play_sound(sfxId);
        } else if (actor->audioFlags & 8) {
            func_8019F128(sfxId);
        } else if (actor->audioFlags & 0x10) {
            func_801A0810(&D_801DB4A4, NA_SE_SY_TIMER - SFX_FLAG, (sfxId - 1));
        } else if (actor->audioFlags & 1) {
            Audio_PlaySfxAtPos(&actor->projectedPos, sfxId);
        }
    }

    if (sfxId) {}

    if (actor->audioFlags & 0x40) {
        func_801A1FB4(3, &actor->projectedPos, NA_BGM_MUSIC_BOX_HOUSE, 1500.0f);
    }

    if (actor->audioFlags & 0x20) {
        func_801A1FB4(0, &actor->projectedPos, NA_BGM_KAMARO_DANCE, 900.0f);
    }
}

void Actor_DrawAllSetup(GlobalContext* globalCtx) {
    globalCtx->actorCtx.undrawnActorCount = 0;
    globalCtx->actorCtx.unkB = 0;
}

s32 Actor_RecordUndrawnActor(GlobalContext* globalCtx, Actor* actor) {
    if (globalCtx->actorCtx.undrawnActorCount >= 32) {
        return false;
    }

    globalCtx->actorCtx.undrawnActors[globalCtx->actorCtx.undrawnActorCount] = actor;
    globalCtx->actorCtx.undrawnActorCount++;
    return true;
}

void func_800B9E84(Gfx** arg0, s32 arg1) {
    func_80164C14(arg0, D_801DE890, 4, 0, 6, 6, ((100 - arg1) * 0.003f) + 1.0f);
}

#ifdef NON_EQUIVALENT
// Related to draw actors with lens
void func_800B9EF4(GlobalContext* globalCtx, s32 numActors, Actor** actors) {
    s32 spB4;
    Gfx* spAC;
    void* spA8; // pad
    s32 spA4;
    // void* sp34;
    // Gfx* temp_s1_11;
    // Gfx** temp_a0_2;
    // Gfx** temp_a1;
    // GraphicsContext* temp_s2;
    // void* temp_s1_10;
    // void* temp_s1_7;
    // void* temp_s1_8;
    // void* temp_s1_9;
    // Gfx* phi_s1;
    Gfx* phi_s1_2;
    // void* phi_s1_4;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    // temp_s2 = globalCtx->state.gfxCtx;

    if (numActors > 0) {
        spAC = POLY_XLU_DISP;
        // sp34 = globalCtx + 0x18000;
        spA4 = globalCtx->unk_18E68;

        PreRender_SetValues(&globalCtx->pauseBgPreRender, D_801FBBCC, D_801FBBCE, __gfxCtx->curFrameBuffer,
                            __gfxCtx->zbuffer);

        func_80170200(&globalCtx->pauseBgPreRender, &spAC, __gfxCtx->zbuffer, (void*)spA4);

        // spAC->words.w0 = 0xE7000000;
        // spAC->words.w1 = 0;
        // temp_s1_2 = spAC + 8;
        gDPPipeSync(spAC++);

        // temp_s1_2->words.w0 = 0xEE000000;
        // temp_s1_2->words.w1 = 0;
        // temp_s1_3 = temp_s1_2 + 8;
        gDPSetPrimDepth(spAC++, 0, 0);

        // temp_s1_3->words.w0 = 0xEF002C30;
        // temp_s1_3->words.w1 = 0xAF504365;
        // temp_s1_4 = temp_s1_3 + 8;
        gDPSetOtherMode(spAC++,
                        G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PRIM | Z_UPD | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
                            GBL_c1(G_BL_CLR_BL, G_BL_0, G_BL_CLR_MEM, G_BL_1MA) |
                            GBL_c2(G_BL_CLR_BL, G_BL_0, G_BL_CLR_MEM, G_BL_1MA));

        // temp_s1_4->words.w1 = 0xFF;
        // temp_s1_4->words.w0 = 0xFA000000;
        // temp_s1_5 = temp_s1_4 + 8;
        gDPSetPrimColor(spAC++, 0, 0, 0, 0, 0, 255);
        // temp_s1_5 = spAC;

        if (globalCtx->roomCtx.currRoom.unk5 == 0) {
            // temp_s1_5->words.w0 = 0xFC61E6C3;
            // temp_s1_5->words.w1 = 0x11CF9FCF;
            // phi_s1 = temp_s1_5 + 8;
            gDPSetCombineLERP(spAC++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1,
                              TEXEL0, PRIMITIVE, 0);
        } else {
            // temp_s1_5->words.w0 = 0xFC119623;
            // temp_s1_5->words.w1 = 0xFF2FFFFF;
            // phi_s1 = temp_s1_5 + 8;
            gDPSetCombineMode(spAC++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        }

        // spAC = phi_s1;
        func_800B9E84(&spAC, globalCtx->actorCtx.unk4);
        phi_s1_2 = func_801660B8(globalCtx, spAC);

        for (spB4 = 0; spB4 < numActors; spB4++, actors++) {
            Actor_Draw(globalCtx, *actors);
        }

        // temp_s0_2 = &globalCtx->pauseBgPreRender;

        // phi_s1_2->words.w0 = 0xE7000000;
        // phi_s1_2->words.w1 = 0;
        // temp_s1_7 = phi_s1_2 + 8;
        gDPPipeSync(phi_s1_2++);

        // temp_s1_7->unk_0 = 0xEF002CF0;
        // temp_s1_7->unk_4 = 0xF5A714D;
        // temp_s1_8 = temp_s1_7 + 8;
        gDPSetOtherMode(phi_s1_2++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PRIM | AA_EN | IM_RD | CVG_DST_WRAP | ZMODE_OPA | CVG_X_ALPHA |
                            ALPHA_CVG_SEL | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1) |
                            GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1));

        // temp_s1_8->unk_4 = -0x100;
        // temp_s1_8->unk_0 = 0xF9000000;
        // temp_s1_9 = temp_s1_8 + 8;
        gDPSetBlendColor(phi_s1_2++, 255, 255, 255, 0);

        // temp_s1_9->unk_4 = 0x20;
        // temp_s1_9->unk_0 = 0xFA0000FF;
        // temp_s1_10 = temp_s1_9 + 8;
        gDPSetPrimColor(phi_s1_2++, 0, 0xFF, 0, 0, 0, 32);

        // temp_a0_2 = &spAC;
        // if (sp34->unk_6E5 == 0) {
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
            gDPSetCombineLERP(phi_s1_2++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1,
                              TEXEL0, PRIMITIVE, 0);

            //}
        }
        // phi_s1_4->unk_0 = (s32) (((sp34->unk_B4C - 1) & 0xFFF) | 0xFF100000);
        // temp_s1_11 = phi_s1_4 + 8;
        // phi_s1_4->unk_4 = spA4;
        gDPSetColorImage(phi_s1_2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((globalCtx->pauseBgPreRender.width - 1) & 0xFFF),
                         spA4);
        // temp_s1_11 = phi_s1_2;

        spAC = phi_s1_2;

        // spAC = temp_s1_11;
        func_800B9E84(&spAC, (s32)globalCtx->actorCtx.unk4);
        // temp_s1_11->words.w0 = 0xE7000000;
        // temp_s1_11->words.w1 = 0;
        // temp_s1_12 = temp_s1_11 + 8;
        gDPPipeSync(spAC++);

        // temp_s1_12->words.w1 = -0xF8;
        // temp_s1_12->words.w0 = 0xF9000000;
        // temp_s1_13 = temp_s1_12 + 8;
        gDPSetBlendColor(spAC++, 255, 255, 255, 8);

        // temp_s1_14 = temp_s1_13 + 8;
        // temp_s1_13->words.w0 = ((sp34->unk_B4C - 1) & 0xFFF) | 0xFF100000;
        // temp_s1_13->words.w1 = sp34->unk_B5C;
        gDPSetColorImage(spAC++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((globalCtx->pauseBgPreRender.width - 1) & 0xFFF),
                         globalCtx->pauseBgPreRender.fbuf);

        // temp_a1 = &spAC;
        // spAC = temp_s1_14;
        // func_8016FDB8(&globalCtx->pauseBgPreRender, temp_a1, (void* ) spA4, spA8, 1U);
        func_8016FDB8(&globalCtx->pauseBgPreRender, &spAC, (void*)spA4, __gfxCtx->zbuffer, 1U);
        //
        // POLY_OPA_DISP = temp_s1_14;
        POLY_OPA_DISP = spAC;
    }

    // temp_s1_15 = OVERLAY_DISP;
    // temp_s1_15->words.w0 = 0xE7000000;
    // temp_s1_15->words.w1 = 0;
    // temp_s1_16 = temp_s1_15 + 8;
    spAC = OVERLAY_DISP;
    gDPPipeSync(spAC++);

    // temp_s1_16->words.w0 = 0xEF002C30;
    // temp_s1_16->words.w1 = 0x00504345;
    // temp_s1_17 = temp_s1_16 + 8;
    gDPSetOtherMode(spAC++,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_THRESHOLD | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2);

    // temp_s1_17->words.w0 = 0xFC61E6C3;
    // temp_s1_17->words.w1 = 0x11CF9FCF;
    // temp_s1_18 = temp_s1_17 + 8;
    gDPSetCombineLERP(spAC++, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0, PRIMITIVE, 0, 1, TEXEL0,
                      PRIMITIVE, 0);

    // temp_s1_18->words.w0 = 0xFA000000;
    // temp_s1_18->words.w1 = 0x4A00004A;
    // spAC = temp_s1_18 + 8;
    gDPSetPrimColor(spAC++, 0, 0, 74, 0, 0, 74);

    func_800B9E84(&spAC, (s32)globalCtx->actorCtx.unk4);

    OVERLAY_DISP = spAC;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
void func_800B9EF4(GlobalContext* globalCtx, s32 numActors, Actor** actors);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9EF4.s")
#endif

s32 func_800BA2D8(GlobalContext* globalCtx, Actor* actor) {
    return func_800BA2FC(globalCtx, actor, &actor->projectedPos, actor->projectedW);
}

s32 func_800BA2FC(GlobalContext* globalCtx, Actor* actor, Vec3f* projectedPos, f32 projectedW) {
    if ((-actor->uncullZoneScale < projectedPos->z) &&
        (projectedPos->z < (actor->uncullZoneForward + actor->uncullZoneScale))) {
        f32 phi_f12;
        f32 phi_f2 = CLAMP_MIN(projectedW, 1.0f);
        f32 phi_f14;
        f32 phi_f16;

        if (globalCtx->view.fovy != 60.0f) {
            phi_f12 = actor->uncullZoneScale * globalCtx->unk_187F0.x * 0.76980036f; // sqrt(16/27)

            phi_f14 = globalCtx->unk_187F0.y * 0.57735026f; // 1 / sqrt(3)
            phi_f16 = actor->uncullZoneScale * phi_f14;
            phi_f14 *= actor->uncullZoneDownward;
        } else {
            phi_f16 = phi_f12 = actor->uncullZoneScale;
            phi_f14 = actor->uncullZoneDownward;
        }

        if (((fabsf(projectedPos->x) - phi_f12) < phi_f2) && ((-phi_f2 < (projectedPos->y + phi_f14))) &&
            ((projectedPos->y - phi_f16) < phi_f2)) {
            return true;
        }
    }

    return false;
}

void Actor_DrawAll(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s32 pad[2];
    Gfx* ref2;
    Gfx* tmp2;
    s32 pad2;
    Gfx* sp58;
    ActorListEntry* actorEntry;
    Actor* actor;
    s32 actorFlags;
    s32 i;

    if (globalCtx->unk_18844 != 0) {
        actorFlags = ACTOR_FLAG_200000;
    } else {
        actorFlags = ACTOR_FLAG_200000 | ACTOR_FLAG_40 | ACTOR_FLAG_20;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Actor_DrawAllSetup(globalCtx);

    sp58 = POLY_XLU_DISP;
    POLY_XLU_DISP = &sp58[1];

    for (i = 0, actorEntry = actorCtx->actorLists; i < ARRAY_COUNT(actorCtx->actorLists); i++, actorEntry++) {
        actor = actorEntry->first;

        while (actor != NULL) {
            SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &actor->world.pos, &actor->projectedPos,
                                         &actor->projectedW);

            if (actor->audioFlags & 0x7F) {
                func_800B9D1C(actor);
            }

            if (func_800BA2D8(globalCtx, actor)) {
                actor->flags |= ACTOR_FLAG_40;
            } else {
                actor->flags &= ~ACTOR_FLAG_40;
            }

            actor->isDrawn = false;
            if ((actor->init == NULL) && (actor->draw != NULL) && (actor->flags & actorFlags)) {
                if ((actor->flags & ACTOR_FLAG_80) &&
                    ((globalCtx->roomCtx.currRoom.unk5 == 0) || (globalCtx->actorCtx.unk4 == 0x64) ||
                     (actor->room != globalCtx->roomCtx.currRoom.num))) {
                    if (Actor_RecordUndrawnActor(globalCtx, actor)) {}
                } else {
                    Actor_Draw(globalCtx, actor);
                }
            }

            actor = actor->next;
        }
    }

    Effect_DrawAll(globalCtx->state.gfxCtx);
    EffectSS_DrawAllParticles(globalCtx);
    EffFootmark_Draw(globalCtx);

    ref2 = POLY_XLU_DISP;
    gSPDisplayList(sp58, &ref2[1]);
    POLY_XLU_DISP = &ref2[1];

    if (globalCtx->actorCtx.unk3 != 0) {
        Math_StepToC(&globalCtx->actorCtx.unk4, 100, 20);
        if (GET_PLAYER(globalCtx)->stateFlags2 & 0x8000000) {
            func_800B90F4(globalCtx);
        }
    } else {
        Math_StepToC(&globalCtx->actorCtx.unk4, 0, 10);
    }
    if (globalCtx->actorCtx.unk4 != 0) {
        globalCtx->actorCtx.unkB = 1;
        func_800B9EF4(globalCtx, globalCtx->actorCtx.undrawnActorCount, globalCtx->actorCtx.undrawnActors);
    }

    tmp2 = POLY_XLU_DISP;
    gSPEndDisplayList(&tmp2[0]);
    gSPBranchList(ref2, &tmp2[1]);
    POLY_XLU_DISP = &tmp2[1];

    if (globalCtx->unk_18844 == 0) {
        Lights_DrawGlow(globalCtx);
    }

    TitleCard_Draw(&globalCtx->state, &actorCtx->titleCtxt);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Kills every actor which its object is not loaded
 */
void func_800BA6FC(GlobalContext* globalCtx, ActorContext* actorCtx) {
    Actor* actor;
    s32 i;

    for (i = 0; i != ARRAY_COUNT(actorCtx->actorLists); i++) {
        actor = actorCtx->actorLists[i].first;

        while (actor != NULL) {
            if (!Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
                Actor_MarkForDeath(actor);
            }

            actor = actor->next;
        }
    }
}

/**
 * Kill actors on room change and update flags accordingly
 */
void func_800BA798(GlobalContext* globalCtx, ActorContext* actorCtx) {
    Actor* actor;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++) {
        actor = actorCtx->actorLists[i].first;

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
    actorCtx->flags.switches[3] = 0;
    actorCtx->flags.collectible[3] = 0;
    globalCtx->msgCtx.unk_12030 = 0;
}

void func_800BA8B8(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++) {
        Actor* actor = actorCtx->actorLists[i].first;

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

void Actor_CleanupContext(ActorContext* actorCtx, GlobalContext* globalCtx) {
    s32 i;

    Fault_RemoveClient(&sActorFaultClient);

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorLists); i++) {
        if (i != ACTORCAT_PLAYER) {
            Actor* actor = actorCtx->actorLists[i].first;

            while (actor != NULL) {
                Actor_Delete(actorCtx, actor, globalCtx);
                actor = actorCtx->actorLists[i].first;
            }
        }
    }

    while (actorCtx->actorLists[ACTORCAT_PLAYER].first != NULL) {
        Actor_Delete(actorCtx, actorCtx->actorLists[ACTORCAT_PLAYER].first, globalCtx);
    }

    if (actorCtx->absoluteSpace != NULL) {
        ZeldaArena_Free(actorCtx->absoluteSpace);
        actorCtx->absoluteSpace = NULL;
    }

    Play_SaveCycleSceneFlags(&globalCtx->state);
    ActorOverlayTable_Cleanup();
}

/**
 * Adds a given actor instance at the front of the actor list of the specified category.
 * Also sets the actor instance as being of that category.
 */
void Actor_AddToCategory(ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    Actor* actorAux;
    Actor* lastActor;

    actor->category = actorCategory;

    actorCtx->totalLoadedActors++;
    actorCtx->actorLists[actorCategory].length++;
    lastActor = actorCtx->actorLists[actorCategory].first;

    if (lastActor == NULL) {
        actorCtx->actorLists[actorCategory].first = actor;
        return;
    }

    actorAux = lastActor->next;
    while (actorAux != NULL) {
        lastActor = actorAux;
        actorAux = actorAux->next;
    }

    lastActor->next = actor;
    actor->prev = lastActor;
}

/**
 * Removes a given actor instance from its actor list.
 * Also sets the temp clear flag of the current room if the actor removed was the last enemy loaded.
 */
Actor* Actor_RemoveFromCategory(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actorToRemove) {
    Actor* newHead;

    actorCtx->totalLoadedActors--;
    actorCtx->actorLists[actorToRemove->category].length--;

    if (actorToRemove->prev != NULL) {
        actorToRemove->prev->next = actorToRemove->next;
    } else {
        actorCtx->actorLists[actorToRemove->category].first = actorToRemove->next;
    }

    newHead = actorToRemove->next;

    if (newHead != NULL) {
        newHead->prev = actorToRemove->prev;
    }

    actorToRemove->next = NULL;
    actorToRemove->prev = NULL;

    if ((actorToRemove->room == globalCtx->roomCtx.currRoom.num) && (actorToRemove->category == ACTORCAT_ENEMY) &&
        (actorCtx->actorLists[ACTORCAT_ENEMY].length == 0)) {
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
                    ZeldaArena_Free(ramAddr);
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

    overlaySize = VRAM_PTR_SIZE(overlayEntry);

    if (overlayEntry->vramStart == NULL) {
        actorInit = overlayEntry->initInfo;
    } else {
        if (overlayEntry->loadedRamAddr == NULL) {
            if (overlayEntry->allocType & ALLOCTYPE_ABSOLUTE) {
                if (actorCtx->absoluteSpace == NULL) {
                    actorCtx->absoluteSpace = ZeldaArena_MallocR(AM_FIELD_SIZE);
                }
                gActorOverlayTable[index].loadedRamAddr = actorCtx->absoluteSpace;
            } else if (overlayEntry->allocType & ALLOCTYPE_PERMANENT) {
                gActorOverlayTable[index].loadedRamAddr = ZeldaArena_MallocR(overlaySize);
            } else {
                gActorOverlayTable[index].loadedRamAddr = ZeldaArena_Malloc(overlaySize);
            }

            if (overlayEntry->loadedRamAddr == NULL) {
                return NULL;
            }

            Load2_LoadOverlay(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart,
                              overlayEntry->vramEnd, overlayEntry->loadedRamAddr);
            overlayEntry->numLoaded = 0;
        }

        actorInit =
            (uintptr_t)((overlayEntry->initInfo != NULL)
                            ? (void*)(-OVERLAY_RELOCATION_OFFSET(overlayEntry) + (uintptr_t)overlayEntry->initInfo)
                            : NULL);
    }

    return actorInit;
}

Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, GlobalContext* globalCtx, s16 index, f32 x, f32 y, f32 z,
                                     s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 arg11, Actor* parent) {
    s32 pad;
    Actor* actor;
    ActorInit* actorInit;
    s32 objBankIndex;
    ActorOverlay* overlayEntry;

    if (actorCtx->totalLoadedActors >= 0xFF) {
        return NULL;
    }

    actorInit = Actor_LoadOverlay(actorCtx, index);
    if (actorInit == NULL) {
        return NULL;
    }

    objBankIndex = Object_GetIndex(&globalCtx->objectCtx, actorInit->objectId);
    if ((objBankIndex < 0) ||
        ((actorInit->type == ACTORCAT_ENEMY) && Flags_GetClear(globalCtx, globalCtx->roomCtx.currRoom.num) &&
         (actorInit->id != ACTOR_BOSS_05))) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    actor = ZeldaArena_Malloc(actorInit->instanceSize);
    if (actor == NULL) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    overlayEntry = &gActorOverlayTable[index];
    if (overlayEntry->vramStart != 0) {
        overlayEntry->numLoaded++;
    }

    bzero(actor, actorInit->instanceSize);
    actor->overlayEntry = overlayEntry;
    actor->id = actorInit->id;
    actor->flags = actorInit->flags;

    if (actorInit->id == ACTOR_EN_PART) {
        actor->objBankIndex = rotZ;
        rotZ = 0;
    } else {
        actor->objBankIndex = objBankIndex;
    }

    actor->init = actorInit->init;
    actor->destroy = actorInit->destroy;
    actor->update = actorInit->update;
    actor->draw = actorInit->draw;

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

    if (arg11 != 0) {
        actor->unk20 = arg11;
    } else {
        actor->unk20 = 0x3FF;
    }

    Actor_AddToCategory(actorCtx, actor, actorInit->type);

    {
        u32 sp20 = gSegments[6];

        Actor_Init(actor, globalCtx);
        gSegments[6] = sp20;
    }

    return actor;
}

Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, GlobalContext* globalCtx, s16 actorId, f32 posX,
                          f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         parent->unk20, parent);
}

void Actor_SpawnTransitionActors(GlobalContext* globalCtx, ActorContext* actorCtx) {
    TransitionActorEntry* transitionActorList = globalCtx->doorCtx.transitionActorList;
    s32 i;
    s16 numTransitionActors = globalCtx->doorCtx.numTransitionActors;

    for (i = 0; i < numTransitionActors; transitionActorList++, i++) {
        if (transitionActorList->id >= 0) {
            if ((transitionActorList->sides[0].room >= 0 &&
                 (globalCtx->roomCtx.currRoom.num == transitionActorList->sides[0].room ||
                  globalCtx->roomCtx.prevRoom.num == transitionActorList->sides[0].room)) ||
                (transitionActorList->sides[1].room >= 0 &&
                 (globalCtx->roomCtx.currRoom.num == transitionActorList->sides[1].room ||
                  globalCtx->roomCtx.prevRoom.num == transitionActorList->sides[1].room))) {
                s16 rotY = ((transitionActorList->rotY >> 7) & 0x1FF) * (0x10000 / 360.0f);

                if (Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, transitionActorList->id & 0x1FFF,
                                                  transitionActorList->pos.x, transitionActorList->pos.y,
                                                  transitionActorList->pos.z, 0, rotY, 0,
                                                  (i << 0xA) + (transitionActorList->params & 0x3FF),
                                                  transitionActorList->rotY & 0x7F, 0x3FF, 0) != NULL) {
                    transitionActorList->id = -transitionActorList->id;
                }
                numTransitionActors = globalCtx->doorCtx.numTransitionActors;
            }
        }
    }
}

Actor* Actor_SpawnEntry(ActorContext* actorCtx, ActorEntry* actorEntry, GlobalContext* globalCtx) {
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

    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorEntry->id & 0x1FFF, actorEntry->pos.x,
                                         actorEntry->pos.y, actorEntry->pos.z, rotX, rotY, rotZ,
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
        Camera_ChangeMode(Play_GetCamera(globalCtx, Play_GetActiveCamId(globalCtx)), 0);
    }

    if (actor == actorCtx->targetContext.arrowPointedActor) {
        actorCtx->targetContext.arrowPointedActor = NULL;
    }

    if (actor == actorCtx->targetContext.unk8C) {
        actorCtx->targetContext.unk8C = NULL;
    }

    if (actor == actorCtx->targetContext.bgmEnemy) {
        actorCtx->targetContext.bgmEnemy = NULL;
    }

    Audio_StopSfxByPos(&actor->projectedPos);
    Actor_Destroy(actor, globalCtx);

    newHead = Actor_RemoveFromCategory(globalCtx, actorCtx, actor);
    ZeldaArena_Free(actor);

    if (overlayEntry->vramStart != NULL) {
        overlayEntry->numLoaded--;
        Actor_FreeOverlay(overlayEntry);
    }

    return newHead;
}

s32 func_800BB59C(GlobalContext* globalCtx, Actor* actor) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(globalCtx, actor, &x, &y);

    return (x > -20) && (x < gScreenWidth + 20) && (y > -160) && (y < gScreenHeight + 160);
}

void func_800BB604(GameState* gameState, ActorContext* actorCtx, Player* player, s32 actorCategory) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    f32 temp_f0_2;
    Actor* sp8C;
    Actor* actor;
    s32 phi_s2;
    CollisionPoly* sp80;
    s32 sp7C;
    Vec3f sp70;
    s32 phi_s2_2;

    actor = actorCtx->actorLists[actorCategory].first;
    sp8C = player->unk_730;
    while (actor != NULL) {
        if ((actor->update != NULL) && ((Player*)actor != player)) {
            if (actor->flags & (ACTOR_FLAG_40000000 | ACTOR_FLAG_1)) {
                if ((actorCategory == ACTORCAT_ENEMY) && CHECK_FLAG_ALL(actor->flags, ACTOR_FLAG_4 | ACTOR_FLAG_1)) {
                    if ((actor->xyzDistToPlayerSq < SQ(500.0f)) && (actor->xyzDistToPlayerSq < sBgmEnemyDistSq)) {
                        actorCtx->targetContext.bgmEnemy = actor;
                        sBgmEnemyDistSq = actor->xyzDistToPlayerSq;
                    }
                }

                if ((actor != sp8C) || (actor->flags & ACTOR_FLAG_80000)) {
                    temp_f0_2 = func_800B82EC(actor, player, D_801ED8DC);
                    phi_s2_2 = (actor->flags & 1) != 0;
                    if (phi_s2_2) {
                        phi_s2_2 = temp_f0_2 < D_801ED8C8;
                    }
                    phi_s2 = phi_s2_2;
                    phi_s2_2 = (actor->flags & ACTOR_FLAG_40000000) != 0;
                    if (phi_s2_2) {
                        phi_s2_2 = temp_f0_2 < D_801ED8D0;
                    }

                    if (((phi_s2) || (phi_s2_2)) && (func_800B83BC(actor, temp_f0_2))) {
                        if (func_800BB59C(globalCtx, actor)) {
                            if (((!BgCheck_CameraLineTest1(&globalCtx->colCtx, &player->actor.focus.pos,
                                                           &actor->focus.pos, &sp70, &sp80, true, true, true, true,
                                                           &sp7C)) ||
                                 (SurfaceType_IsIgnoredByProjectiles(&globalCtx->colCtx, sp80, sp7C)))) {
                                if (actor->targetPriority != 0) {
                                    if ((phi_s2 != 0) && (actor->targetPriority < D_801ED8D4)) {
                                        D_801ED8BC = actor;
                                        D_801ED8D4 = actor->targetPriority;
                                    }
                                    if ((phi_s2_2 != 0) && (actor->targetPriority < D_801ED8D8)) {
                                        D_801ED8C4 = actor;
                                        D_801ED8D8 = actor->targetPriority;
                                    }
                                } else {
                                    if (phi_s2 != 0) {
                                        D_801ED8B8 = actor;
                                        D_801ED8C8 = temp_f0_2;
                                    }
                                    if (phi_s2_2 != 0) {
                                        D_801ED8C0 = actor;
                                        D_801ED8D0 = temp_f0_2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        actor = actor->next;
    }
}

u8 D_801AED8C[] = {
    ACTORCAT_BOSS,  ACTORCAT_ENEMY,  ACTORCAT_BG,   ACTORCAT_EXPLOSIVES, ACTORCAT_NPC,  ACTORCAT_ITEMACTION,
    ACTORCAT_CHEST, ACTORCAT_SWITCH, ACTORCAT_PROP, ACTORCAT_MISC,       ACTORCAT_DOOR, ACTORCAT_SWITCH,
};

void func_800BB8EC(GameState* gameState, ActorContext* actorCtx, Actor** arg2, Actor** arg3, Player* player) {
    u8* actorCategories;
    s32 i;

    D_801ED8B8 = D_801ED8BC = D_801ED8C0 = D_801ED8C4 = NULL;
    D_801ED8C8 = D_801ED8D0 = sBgmEnemyDistSq = FLT_MAX;
    D_801ED8D4 = D_801ED8D8 = INT32_MAX;

    actorCtx->targetContext.bgmEnemy = NULL;
    D_801ED8DC = player->actor.shape.rot.y;

    actorCategories = D_801AED8C;

    for (i = 0; i < 3; i++) {
        func_800BB604(gameState, actorCtx, player, *actorCategories);
        actorCategories++;
    }

    if (D_801ED8B8 == NULL) {
        for (; i < ARRAY_COUNT(D_801AED8C); i++) {
            func_800BB604(gameState, actorCtx, player, *actorCategories);
            actorCategories++;
        }
    }

    if (D_801ED8B8 == NULL) {
        *arg2 = D_801ED8BC;
    } else {
        *arg2 = D_801ED8B8;
    }

    if (D_801ED8C0 == NULL) {
        *arg3 = D_801ED8C4;
    } else {
        *arg3 = D_801ED8C0;
    }
}

/**
 * Play the death sound effect and flash the screen white for 4 frames.
 * While the screen flashes, the game freezes.
 */
void Enemy_StartFinishingBlow(GlobalContext* globalCtx, Actor* actor) {
    globalCtx->actorCtx.freezeFlashTimer = 5;
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &actor->world.pos, 20, NA_SE_EN_LAST_DAMAGE);
}

// blinking routine
s16 func_800BBAC0(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3) {
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

void Actor_SpawnBodyParts(Actor* actor, GlobalContext* globalCtx, s32 arg2, Gfx** dList) {
    EnPart* part;
    Actor* spawnedPart;
    MtxF* currentMatrix;

    if (*dList != NULL) {
        currentMatrix = Matrix_GetCurrentState();
        spawnedPart =
            Actor_SpawnAsChild(&globalCtx->actorCtx, actor, globalCtx, ACTOR_EN_PART, currentMatrix->mf[3][0],
                               currentMatrix->mf[3][1], currentMatrix->mf[3][2], 0, 0, actor->objBankIndex, arg2);
        if (spawnedPart != NULL) {
            part = (EnPart*)spawnedPart;

            func_8018219C(currentMatrix, &part->actor.shape.rot, 0);
            part->unk_150 = *dList;
            Math_Vec3f_Copy(&part->actor.scale, &actor->scale);
        }
    }
}

void Actor_SpawnFloorDustRing(GlobalContext* globalCtx, Actor* actor, Vec3f* posXZ, f32 radius, s32 countMinusOne,
                              f32 randAccelWeight, s16 scale, s16 scaleStep, u8 useLighting) {
    Vec3f pos;
    Vec3f accel = { 0.0f, 0.3f, 0.0f };
    s32 pad[2];
    f32 angle;
    s32 i;

    angle = (Rand_ZeroOne() - 0.5f) * (2.0f * 3.14f);
    pos.y = actor->floorHeight;
    accel.y += (Rand_ZeroOne() - 0.5f) * 0.2f;

    for (i = countMinusOne; i >= 0; i--) {
        pos.x = (sin_rad(angle) * radius) + posXZ->x;
        pos.z = (cos_rad(angle) * radius) + posXZ->z;
        accel.x = (Rand_ZeroOne() - 0.5f) * randAccelWeight;
        accel.z = (Rand_ZeroOne() - 0.5f) * randAccelWeight;

        if (scale == 0) {
            func_800B10C0(globalCtx, &pos, &gZeroVec3f, &accel);
        } else if (useLighting) {
            func_800B1210(globalCtx, &pos, &gZeroVec3f, &accel, scale, scaleStep);
        } else {
            func_800B11A0(globalCtx, &pos, &gZeroVec3f, &accel, scale, scaleStep);
        }
        angle += (2.0f * 3.14f) / (countMinusOne + 1.0f);
    }
}

void func_800BBFB0(GlobalContext* globalCtx, Vec3f* position, f32 arg2, s32 arg3, s16 arg4, s16 scaleStep, u8 arg6) {
    Vec3f pos;
    Vec3f accel = { 0.0f, 0.3f, 0.0f };
    s32 i;

    for (i = arg3; i >= 0; i--) {
        s16 scale;

        pos.x = ((Rand_ZeroOne() - 0.5f) * arg2) + position->x;
        pos.y = ((Rand_ZeroOne() - 0.5f) * arg2) + position->y;
        pos.z = ((Rand_ZeroOne() - 0.5f) * arg2) + position->z;

        scale = (s32)(Rand_ZeroOne() * arg4 * 0.2f);
        scale += arg4;

        if (arg6) {
            func_800B1210(globalCtx, &pos, &gZeroVec3f, &accel, scale, scaleStep);
        } else {
            func_800B11A0(globalCtx, &pos, &gZeroVec3f, &accel, scale, scaleStep);
        }
    }
}

void func_800BC154(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    actorCtx->actorLists[actor->category].unk_08 = 1;
    actor->category = actorCategory;
}

// Damage flags for EnArrow
s32 D_801AEDB0[] = {
    0x800, 0x20, 0x20, 0x800, 0x1000, 0x2000, 0x1, 0x10000, 0x1,
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
            return true;
        }
    }

    return false;
}

Actor* func_800BC270(GlobalContext* globalCtx, Actor* actor, f32 arg2, s32 arg3) {
    Actor* itemAction = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (itemAction != NULL) {
        if (((itemAction->id == ACTOR_ARMS_HOOK) && (arg3 & 0x80)) ||
            ((itemAction->id == ACTOR_EN_BOOM) && (arg3 & 0x10)) ||
            ((itemAction->id == ACTOR_EN_ARROW) && (func_800BC188(itemAction->params) & arg3))) {
            f32 speedXZ;

            if ((itemAction->speedXZ <= 0.0f) && (GET_PLAYER(globalCtx)->unk_D57 != 0)) {
                if (itemAction->id == ACTOR_ARMS_HOOK) {
                    speedXZ = 20.0f;
                } else if (itemAction->id == ACTOR_EN_BOOM) {
                    speedXZ = 12.0f;
                } else {
                    s32 temp_v0_3 = func_800BC188(itemAction->params);

                    if (temp_v0_3 == 1) {
                        speedXZ = 80.0f;
                    } else if (temp_v0_3 == 0x10000) {
                        speedXZ = 60.0f;
                    } else {
                        speedXZ = 150.0f;
                    }
                }
            } else {
                speedXZ = itemAction->speedXZ;
            }

            if (func_800BC1B4(actor, itemAction, arg2, speedXZ)) {
                break;
            }
        }

        itemAction = itemAction->next;
    }

    return itemAction;
}

Actor* func_800BC444(GlobalContext* globalCtx, Actor* actor, f32 arg2) {
    Actor* explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if (((explosive->id == ACTOR_EN_BOM) || (explosive->id == ACTOR_EN_BOM_CHU) ||
             (explosive->id == ACTOR_EN_BOMBF))) {
            if (func_800BC1B4(actor, explosive, arg2, explosive->speedXZ)) {
                break;
            }
        }
        explosive = explosive->next;
    }

    return explosive;
}

/**
 * Checks if a given actor will be standing on the ground after being translated
 * by the provided distance and angle.
 *
 * Returns true if the actor will be standing on ground.
 */
s16 Actor_TestFloorInDirection(Actor* actor, GlobalContext* globalCtx, f32 distance, s16 angle) {
    s16 ret;
    u16 bgCheckFlags;
    f32 dx;
    f32 dz;
    Vec3f actorPos;

    Math_Vec3f_Copy(&actorPos, &actor->world.pos);

    bgCheckFlags = actor->bgCheckFlags;

    dx = Math_SinS(angle) * distance;
    dz = Math_CosS(angle) * distance;

    actor->world.pos.x += dx;
    actor->world.pos.z += dz;

    Actor_UpdateBgCheckInfo(globalCtx, actor, 0.0f, 0.0f, 0.0f, 4);
    Math_Vec3f_Copy(&actor->world.pos, &actorPos);

    ret = actor->bgCheckFlags & 1;

    actor->bgCheckFlags = bgCheckFlags;

    return ret;
}

/**
 * Returns true if the player is targeting the provided actor
 */
s32 Actor_IsTargeted(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags3 & 0x80000000) && actor->isTargeted) {
        return true;
    }

    return false;
}

/**
 * Returns true if the player is targeting an actor other than the provided actor
 */
s32 Actor_OtherIsTargeted(GlobalContext* globalCtx, Actor* actor) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->stateFlags3 & 0x80000000) && !actor->isTargeted) {
        return true;
    }

    return false;
}

void func_800BC620(Vec3f* arg0, Vec3f* arg1, u8 alpha, GlobalContext* globalCtx) {
    MtxF sp58;
    f32 sp54;
    Vec3f sp48;
    CollisionPoly* sp44;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, alpha);

    sp48.x = arg0->x;
    sp48.y = arg0->y + 1.0f;
    sp48.z = arg0->z;

    sp54 = BgCheck_EntityRaycastFloor2(globalCtx, &globalCtx->colCtx, &sp44, &sp48);
    if (sp44 != NULL) {
        func_800C0094(sp44, arg0->x, sp54, arg0->z, &sp58);
        Matrix_SetCurrentState(&sp58);
    } else {
        Matrix_InsertTranslation(arg0->x, arg0->y, arg0->z, MTXMODE_NEW);
    }
    Matrix_Scale(arg1->x, 1.0f, arg1->z, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gCircleShadowDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BC770(GlobalContext* globalCtx, s16 y, s16 countdown) {
    s16 idx = Quake_Add(&globalCtx->mainCamera, 3);

    Quake_SetSpeed(idx, 20000);
    Quake_SetQuakeValues(idx, y, 0, 0, 0);
    Quake_SetCountdown(idx, countdown);
}

void func_800BC7D8(GlobalContext* globalCtx, s16 y, s16 countdown, s16 speed) {
    s16 idx = Quake_Add(&globalCtx->mainCamera, 3);

    Quake_SetSpeed(idx, speed);
    Quake_SetQuakeValues(idx, y, 0, 0, 0);
    Quake_SetCountdown(idx, countdown);
}

void func_800BC848(Actor* actor, GlobalContext* globalCtx, s16 y, s16 countdown) {
    if (y >= 5) {
        func_8013ECE0(actor->xyzDistToPlayerSq, 255, 20, 150);
    } else {
        func_8013ECE0(actor->xyzDistToPlayerSq, 180, 20, 100);
    }
    func_800BC770(globalCtx, y, countdown);
}

typedef struct {
    /* 0x00 */ f32 chainAngle;
    /* 0x04 */ f32 chainLength;
    /* 0x08 */ f32 yShift;
    /* 0x0C */ f32 chainsScale;
    /* 0x10 */ f32 chainsRotZInit;
    /* 0x14 */ Gfx* chainDL;
    /* 0x18 */ Gfx* lockDL;
} DoorLockInfo; // size = 0x1C

DoorLockInfo sDoorLocksInfo[DOORLOCK_MAX] = {
    /* DOORLOCK_NORMAL */ { 0.54f, 6000.0f, 5000.0, 1.0f, 0.0f, gDoorChainsDL, gDoorLockDL },
    /* DOORLOCK_BOSS */ { 0.644f, 12000.0f, 8000.0f, 1.0f, 0.0f, object_bdoor_DL_000530, object_bdoor_DL_000400 },
    /* DOORLOCK_2 */ { 0.6400000453f, 8500.0f, 8000.0f, 1.75f, 0.1f, gDoorChainsDL, gDoorLockDL },
};

/**
 * Draws chains and lock of a locked door, of the specified `type` (see `DoorLockType`).
 * `frame` can be 0 to 10, where 0 is "open" and 10 is "closed", the chains slide accordingly.
 */
void Actor_DrawDoorLock(GlobalContext* globalCtx, s32 frame, s32 type) {
    s32 pad[2];
    MtxF baseMtxF;
    s32 i;
    f32 chainsTranslateX;
    f32 chainsTranslateY;
    DoorLockInfo* entry = &sDoorLocksInfo[type];
    f32 chainRotZ = entry->chainsRotZInit;
    f32 rotZStep;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, entry->yShift, 500.0f, MTXMODE_APPLY);
    Matrix_CopyCurrentState(&baseMtxF);

    chainsTranslateX = __sinf(entry->chainAngle - chainRotZ) * -(10 - frame) * 0.1f * entry->chainLength;
    chainsTranslateY = __cosf(entry->chainAngle - chainRotZ) * (10 - frame) * 0.1f * entry->chainLength;

    for (i = 0; i < 4; i++) {
        Matrix_SetCurrentState(&baseMtxF);
        Matrix_InsertZRotation_f(chainRotZ, MTXMODE_APPLY);
        Matrix_InsertTranslation(chainsTranslateX, chainsTranslateY, 0.0f, MTXMODE_APPLY);
        if (entry->chainsScale != 1.0f) {
            Matrix_Scale(entry->chainsScale, entry->chainsScale, entry->chainsScale, MTXMODE_APPLY);
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, entry->chainDL);

        if ((i % 2) != 0) {
            rotZStep = 2.0f * entry->chainAngle;
        } else {
            rotZStep = M_PI - (2.0f * entry->chainAngle);
        }

        chainRotZ += rotZStep;
    }

    Matrix_SetCurrentState(&baseMtxF);
    Matrix_Scale(frame * 0.1f, frame * 0.1f, frame * 0.1f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, entry->lockDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void Actor_SpawnShieldParticlesMetal(GlobalContext* globalCtx, Vec3f* pos) {
    CollisionCheck_SpawnShieldParticlesMetal(globalCtx, pos);
}

void Actor_SetColorFilter(Actor* actor, u16 colorFlag, u16 colorIntensityMax, u16 xluFlag, u16 duration) {
    if ((colorFlag == 0x8000) && !(colorIntensityMax & 0x8000)) {
        Actor_PlaySfxAtPos(actor, NA_SE_EN_LIGHT_ARROW_HIT);
    }

    actor->colorFilterParams = colorFlag | xluFlag | ((colorIntensityMax & 0xF8) << 5) | duration;
    actor->colorFilterTimer = duration;
}

Hilite* func_800BCBF4(Vec3f* arg0, GlobalContext* globalCtx) {
    Vec3f lightDir;

    lightDir.x = globalCtx->envCtx.dirLight1.params.dir.x;
    lightDir.y = globalCtx->envCtx.dirLight1.params.dir.y;
    lightDir.z = globalCtx->envCtx.dirLight1.params.dir.z;

    return Hilite_DrawOpa(arg0, &globalCtx->view.eye, &lightDir, globalCtx->state.gfxCtx);
}

Hilite* func_800BCC68(Vec3f* arg0, GlobalContext* globalCtx) {
    Vec3f lightDir;

    lightDir.x = globalCtx->envCtx.dirLight1.params.dir.x;
    lightDir.y = globalCtx->envCtx.dirLight1.params.dir.y;
    lightDir.z = globalCtx->envCtx.dirLight1.params.dir.z;

    return Hilite_DrawXlu(arg0, &globalCtx->view.eye, &lightDir, globalCtx->state.gfxCtx);
}

/**
 * Calculates the closest position `dstPos` to the input position `srcPos` along the path given by `points`/`numPoints`
 * Whether the points provided forms a closed-loop path is indicated by `isPathLoop`
 */
void Actor_GetClosestPosOnPath(Vec3s* points, s32 numPoints, Vec3f* srcPos, Vec3f* dstPos, s32 isPathLoop) {
    s32 pointIndex;
    s32 closestPointIndex;
    s32 useAdjacentLines[2] = {
        false, // determines whether to use line connecting to previous point in calculations
        false, // determines whether to use line connecting to next point in calculations
    };
    s32 isRightSideOfAdjacentLines[2] = {
        false, // determines whether srcPos is on the right side of the line from prev to curr point
        false, // determines whether srcPos is on the right side of the line from curr to next point
    };
    Vec3f closestPoint;
    Vec3f closestPos[2];
    Vec3f closestPointNext;
    Vec3f closestPointPrev;
    f32 distSq; // First used as distSq to closest point, then used as distSq to closest position
    f32 closestPointDistSq;
    f32 loopDistSq[2];
    s32 i;

    closestPointIndex = 0;
    closestPointDistSq = SQ(40000.0f);

    // Find the point closest to srcPos
    for (pointIndex = 0; pointIndex < numPoints; pointIndex++) {
        distSq = Math3D_XZDistanceSquared(srcPos->x, srcPos->z, points[pointIndex].x, points[pointIndex].z);
        if (distSq < closestPointDistSq) {
            closestPointDistSq = distSq;
            closestPointIndex = pointIndex;
        }
    }

    closestPoint.x = (points + closestPointIndex)->x;
    closestPoint.z = (points + closestPointIndex)->z;
    dstPos->y = (points + closestPointIndex)->y;

    // Analyze point on path immediately previous to the closest point
    if (closestPointIndex != 0) {
        // The point previous to the closest point
        closestPointPrev.x = (points + closestPointIndex - 1)->x;
        closestPointPrev.z = (points + closestPointIndex - 1)->z;
    } else if (isPathLoop) {
        // Closest point is the first point in the path list
        // Set the previous point to loop around to the the final point on the path
        closestPointPrev.x = (points + numPoints - 1)->x;
        closestPointPrev.z = (points + numPoints - 1)->z;
    }
    if ((closestPointIndex != 0) || isPathLoop) {
        // Use the adjacent line
        useAdjacentLines[0] =
            Math3D_PointDistToLine2D(srcPos->x, srcPos->z, closestPointPrev.x, closestPointPrev.z, closestPoint.x,
                                     closestPoint.z, &closestPos[0].x, &closestPos[0].z, &distSq);
    }

    // Analyze point on path immediately next to the closest point
    if (closestPointIndex + 1 != numPoints) {
        // The point next to the closest point
        closestPointNext.x = (points + closestPointIndex + 1)->x;
        closestPointNext.z = (points + closestPointIndex + 1)->z;
    } else if (isPathLoop) {
        // Closest point is the final point in the path list
        // Set the next point to loop around to the the first point on the path
        closestPointNext.x = (points + 0)->x;
        closestPointNext.z = (points + 0)->z;
    }
    if ((closestPointIndex + 1 != numPoints) || isPathLoop) {
        useAdjacentLines[1] =
            Math3D_PointDistToLine2D(srcPos->x, srcPos->z, closestPoint.x, closestPoint.z, closestPointNext.x,
                                     closestPointNext.z, &closestPos[1].x, &closestPos[1].z, &distSq);
    }

    /**
     * For close-looped paths, they must be defined in a clockwise orientation looking from the top down.
     * Therefore, `srcPos` being interior of the loop will lead to both lines of `isRightSideOfAdjacentLines`
     * returning true.
     */
    if (isPathLoop) {
        isRightSideOfAdjacentLines[0] = ((closestPointPrev.x - srcPos->x) * (closestPoint.z - srcPos->z)) <
                                        ((closestPointPrev.z - srcPos->z) * (closestPoint.x - srcPos->x));

        isRightSideOfAdjacentLines[1] = ((closestPointNext.z - srcPos->z) * (closestPoint.x - srcPos->x)) <
                                        ((closestPoint.z - srcPos->z) * (closestPointNext.x - srcPos->x));

        for (i = 0; i < ARRAY_COUNT(loopDistSq); i++) {
            if (useAdjacentLines[i]) {
                // Get distSq from srcPos to closestPos
                loopDistSq[i] = Math3D_XZDistanceSquared(srcPos->x, srcPos->z, closestPos[i].x, closestPos[i].z);
            } else {
                // The closest Pos is not contained within the line-segment
                loopDistSq[i] = SQ(40000.0f);
            }
        }
    }

    // Calculate closest position along path
    if (isPathLoop && ((isRightSideOfAdjacentLines[0] && isRightSideOfAdjacentLines[1]) ||
                       (isRightSideOfAdjacentLines[0] && useAdjacentLines[0] && (loopDistSq[0] < loopDistSq[1])) ||
                       (isRightSideOfAdjacentLines[1] && useAdjacentLines[1] && (loopDistSq[1] < loopDistSq[0])))) {
        // srcPos is contained within the closed loop
        dstPos->x = srcPos->x;
        dstPos->z = srcPos->z;
    } else if (useAdjacentLines[0] && useAdjacentLines[1]) {
        // srcPos is somewhere withing the bend of the path
        if (!isRightSideOfAdjacentLines[0] && !isRightSideOfAdjacentLines[1]) {
            // srcPos is not inside a loop
            if (!Math3D_PointDistToLine2D(srcPos->x, srcPos->z, closestPos[0].x, closestPos[0].z, closestPos[1].x,
                                          closestPos[1].z, &dstPos->x, &dstPos->z, &distSq)) {
                // The dstPos calculated in Math3D_PointDistToLine2D was not valid.
                // Take the midpoint of the two closest ponits instead
                dstPos->x = (closestPos[1].x + closestPos[0].x) * 0.5f;
                dstPos->z = (closestPos[1].z + closestPos[0].z) * 0.5f;
            }
        } else if (loopDistSq[1] < loopDistSq[0]) {
            // Use closest position along the line in the loop connecting the closest point and the next point
            dstPos->x = closestPos[1].x;
            dstPos->z = closestPos[1].z;
        } else {
            // Use closest position along the ling in the loop connecting the closest point and the prev point
            dstPos->x = closestPos[0].x;
            dstPos->z = closestPos[0].z;
        }
    } else if (useAdjacentLines[0]) {
        // Use closest position along line segment connecting the closest point and the prev point
        dstPos->x = closestPos[0].x;
        dstPos->z = closestPos[0].z;
    } else if (useAdjacentLines[1]) {
        // Use closest position along line segment connecting the closest point and the next point
        dstPos->x = closestPos[1].x;
        dstPos->z = closestPos[1].z;
    } else if (isPathLoop && ((((closestPointPrev.x - srcPos->x) * (closestPointNext.z - srcPos->z)) <
                               ((closestPointPrev.z - srcPos->z) * (closestPointNext.x - srcPos->x))))) {
        // Inside the line that directly connects the previous point to the next point (inside the bend of a corner)
        dstPos->x = srcPos->x;
        dstPos->z = srcPos->z;
    } else {
        // The closest point and the closest position are the same (srcPos is near the outer region of a corner)
        dstPos->x = closestPoint.x;
        dstPos->z = closestPoint.z;
    }
}

// unused
s32 func_800BD2B4(GlobalContext* globalCtx, Actor* actor, s16* arg2, f32 arg3,
                  u16 (*textIdCallback)(GlobalContext*, Actor*), s16 (*arg5)(GlobalContext*, Actor*)) {
    if (Actor_ProcessTalkRequest(actor, &globalCtx->state)) {
        *arg2 = true;
        return true;
    } else if (*arg2) {
        *arg2 = arg5(globalCtx, actor);
        return false;
    } else if (!func_800B8934(globalCtx, actor)) {
        return false;
    } else if (!func_800B8614(actor, globalCtx, arg3)) {
        return false;
    } else {
        actor->textId = textIdCallback(globalCtx, actor);
        return false;
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
    { { 0x1C20, 0xE390, 0x1C70, 0x1554, 0x0000, 0x0000, 0x0000 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xEAAC, 0x1554, 0x1554, 0xF8E4, 0x0E38, 0x0001 }, 170.0f, 0x3FFC },
    { { 0x31C4, 0xE390, 0x0E38, 0x0E38, 0xF1C8, 0x071C, 0x0001 }, 170.0f, 0x3FFC },
    { { 0x1554, 0xF1C8, 0x0000, 0x071C, 0xF8E4, 0x0000, 0x0001 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF8E4, 0x071C, 0x0E38, 0xD558, 0x2AA8, 0x0001 }, 170.0f, 0x3FFC },
    { { 0x0000, 0xE390, 0x2AA8, 0x3FFC, 0xF1C8, 0x0E38, 0x0001 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF1C8, 0x0E38, 0x0E38, 0x0000, 0x0000, 0x0001 }, 0.0f, 0x0000 },
    { { 0x2AA8, 0xF1C8, 0x0000, 0x0E38, 0x0000, 0x1C70, 0x0001 }, 0.0f, 0x0000 },
    { { 0x2AA8, 0xF1C8, 0xF1C8, 0x0000, 0x0000, 0x0000, 0x0001 }, 0.0f, 0x0000 },
    { { 0x071C, 0xF1C8, 0x0E38, 0x1C70, 0x0000, 0x0000, 0x0001 }, 0.0f, 0x0000 },
    { { 0x0E38, 0xF1C8, 0x0000, 0x1C70, 0x0000, 0x0E38, 0x0001 }, 0.0f, 0x0000 },
    { { 0x2AA8, 0xE390, 0x1C70, 0x0E38, 0xF1C8, 0x0E38, 0x0001 }, 0.0f, 0x0000 },
    { { 0x18E2, 0xF1C8, 0x0E38, 0x0E38, 0x0000, 0x0000, 0x0001 }, 0.0f, 0x0000 },
    { { 0x2A6C, 0xE390, 0x1C70, 0x1554, 0x0000, 0x0000, 0x0000 }, 170.0f, 0x3FFC },
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

Gfx* func_800BD9A0(GraphicsContext* gfxCtx) {
    Gfx* displayListHead;
    Gfx* displayList;

    displayListHead = displayList = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gDPSetRenderMode(displayListHead++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         G_RM_FOG_SHADE_A,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gSPEndDisplayList(displayListHead++);

    return displayList;
}

// unused
void func_800BD9E0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw,
                   PostLimbDraw postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_OPA_DISP++, 0x0C, gEmptyDL);

    POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                       overrideLimbDraw, postLimbDraw, actor, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BDAA0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw,
                   PostLimbDraw postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0C, func_800BD9A0(globalCtx->state.gfxCtx));

    POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
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
        actor->flags &= ~ACTOR_FLAG_1;
        Math_SmoothStepToS(&arg2, 0, 6, 0x14, 1);
    } else {
        actor->flags |= ACTOR_FLAG_1;
        Math_SmoothStepToS(&arg2, 0xFF, 6, 0x14, 1);
    }

    return arg2;
}

void Actor_ChangeAnimationByInfo(SkelAnime* skelAnime, AnimationInfo* animation, s32 index) {
    f32 frameCount;

    animation += index;
    if (animation->frameCount > 0.0f) {
        frameCount = animation->frameCount;
    } else {
        frameCount = Animation_GetLastFrame(&animation->animation->common);
    }

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
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

/**
 * Finds the first actor instance of a specified Id and category within a given range from
 * an actor if there is one. If the Id provided is -1, this will look for any actor of the
 * specified category rather than a specific Id.
 */
Actor* Actor_FindNearby(GlobalContext* globalCtx, Actor* inActor, s16 actorId, u8 actorCategory, f32 distance) {
    Actor* actor = globalCtx->actorCtx.actorLists[actorCategory].first;

    while (actor != NULL) {
        if (actor == inActor || ((actorId != -1) && (actorId != actor->id))) {
            actor = actor->next;
            continue;
        }

        if (Actor_DistanceBetweenActors(inActor, actor) <= distance) {
            return actor;
        }

        actor = actor->next;
    }

    return NULL;
}

s32 func_800BE184(GlobalContext* globalCtx, Actor* actor, f32 xzDist, s16 arg3, s16 arg4, s16 arg5) {
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_v0 = BINANG_SUB(BINANG_ROT180(actor->yawTowardsPlayer), player->actor.shape.rot.y);
    s16 temp_t0 = actor->yawTowardsPlayer - arg5;

    if ((actor->xzDistToPlayer <= xzDist) && (player->swordState != 0)) {
        if ((arg4 >= ABS_ALT(phi_v0)) && (arg3 >= ABS_ALT(temp_t0))) {
            return true;
        }
    }

    return false;
}

u8 Actor_ApplyDamage(Actor* actor) {
    if (actor->colChkInfo.damage >= actor->colChkInfo.health) {
        actor->colChkInfo.health = 0;
    } else {
        actor->colChkInfo.health -= actor->colChkInfo.damage;
    }
    return actor->colChkInfo.health;
}

void Actor_SetDropFlag(Actor* actor, ColliderInfo* colInfo) {
    ColliderInfo* acHitInfo = colInfo->acHitInfo;

    if (acHitInfo == NULL) {
        actor->dropFlag = 0;
    } else if (acHitInfo->toucher.dmgFlags & 0x800) { // DMG_FIRE_ARROW
        actor->dropFlag = 1;
    } else if (acHitInfo->toucher.dmgFlags & 0x1000) { // DMG_ICE_ARROW
        actor->dropFlag = 2;
    } else if (acHitInfo->toucher.dmgFlags & 0x2000) { // DMG_LIGHT_ARROW
        actor->dropFlag = 0x20;
    } else {
        actor->dropFlag = 0;
    }
}

void Actor_SetDropFlagJntSph(Actor* actor, ColliderJntSph* jntSphere) {
    s32 i;
    ColliderJntSphElement* jntElement;
    ColliderInfo* acHitInfo;
    s32 flag;

    actor->dropFlag = 0;

    for (i = jntSphere->count - 1; i >= 0; i--) {
        jntElement = &jntSphere->elements[i];
        acHitInfo = jntElement->info.acHitInfo;

        if (acHitInfo == NULL) {
            flag = 0;
        } else {
            s32 dmgFlags = acHitInfo->toucher.dmgFlags;

            if (dmgFlags & 0x800) {
                flag = 1;
            } else if (dmgFlags & 0x1000) {
                flag = 2;
            } else {
                flag = (dmgFlags & 0x2000) ? 0x20 : 0;
            }
        }

        actor->dropFlag |= flag;
    }
}

void func_800BE33C(Vec3f* arg0, Vec3f* arg1, Vec3s* arg2, s32 arg3) {
    f32 xDiff = arg1->x - arg0->x;
    f32 zDiff = arg1->z - arg0->z;
    f32 yDiff = arg3 ? (arg1->y - arg0->y) : (arg0->y - arg1->y);

    arg2->y = Math_FAtan2F(zDiff, xDiff);
    arg2->x = Math_FAtan2F(sqrtf(SQ(xDiff) + SQ(zDiff)), yDiff);
}

void func_800BE3D0(Actor* actor, s16 angle, Vec3s* arg2) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 pad[3];

    if (actor->floorPoly != NULL) {
        CollisionPoly* floorPoly = actor->floorPoly;

        sp44 = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        sp40 = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        sp3C = COLPOLY_GET_NORMAL(floorPoly->normal.z);

        sp38 = Math_SinS(angle);
        sp34 = Math_CosS(angle);
        arg2->x = (s16)-Math_Atan2S((-(sp44 * sp38) - (sp3C * sp34)) * sp40, 1.0f);

        sp2C = Math_SinS(angle - 0x3FF7);
        sp30 = Math_CosS(angle - 0x3FF7);
        arg2->z = (s16)-Math_Atan2S((-(sp44 * sp2C) - (sp3C * sp30)) * sp40, 1.0f);
    }
}

void func_800BE504(Actor* actor, ColliderCylinder* collider) {
    // Checks if was hit by either DMG_NORMAL_ARROW, DMG_FIRE_ARROW, DMG_ICE_ARROW, DMG_LIGHT_ARROW or DMG_DEKU_BUBBLE
    if ((collider->info.acHitInfo->toucher.dmgFlags & (0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20))) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

void func_800BE568(Actor* actor, ColliderSphere* collider) {
    if (collider->info.acHitInfo->toucher.dmgFlags & (0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20)) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

void func_800BE5CC(Actor* actor, ColliderJntSph* collider, s32 colliderIndex) {
    if (collider->elements[colliderIndex].info.acHitInfo->toucher.dmgFlags &
        (0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20)) {
        actor->world.rot.y = collider->base.ac->shape.rot.y;
    } else {
        actor->world.rot.y = Actor_YawBetweenActors(collider->base.ac, actor);
    }
}

s32 func_800BE63C(struct EnBox* chest) {
    if ((chest->unk_1F1 == 5) || (chest->unk_1F1 == 6) || (chest->unk_1F1 == 7) || (chest->unk_1F1 == 8) ||
        (chest->unk_1F1 == 0xC)) {
        return true;
    }
    return false;
}

TexturePtr sElectricSparkTextures[] = {
    gElectricSpark1Tex,
    gElectricSpark2Tex,
    gElectricSpark3Tex,
    gElectricSpark4Tex,
};

/**
 * Draw common damage effects applied to each limb provided in limbPos
 */
void Actor_DrawDamageEffects(GlobalContext* globalCtx, Actor* actor, Vec3f limbPos[], s16 limbPosCount, f32 effectScale,
                             f32 frozenSteamScale, f32 effectAlpha, u8 type) {
    if (effectAlpha > 0.001f) {
        s32 twoTexScrollParam;
        s16 limbIndex;
        MtxF* currentMatrix;
        f32 alpha;
        f32 frozenScale;
        f32 lightOrbsScale;
        f32 electricSparksScale;
        f32 steamScale;
        Vec3f* limbPosStart = limbPos;
        u32 gameplayFrames = globalCtx->gameplayFrames;
        f32 effectAlphaScaled;

        currentMatrix = Matrix_GetCurrentState();

        // Apply sfx along with damage effect
        if ((actor != NULL) && (effectAlpha > 0.05f) && (globalCtx->gameOverCtx.state == 0)) {
            if (type == ACTOR_DRAW_DMGEFF_FIRE) {
                Actor_PlaySfxAtPos(actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
            } else if (type == ACTOR_DRAW_DMGEFF_BLUE_FIRE) {
                Actor_PlaySfxAtPos(actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
            } else if (type == ACTOR_DRAW_DMGEFF_FROZEN_SFX) {
                Actor_PlaySfxAtPos(actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            } else if ((type == ACTOR_DRAW_DMGEFF_LIGHT_ORBS) || (type == ACTOR_DRAW_DMGEFF_BLUE_LIGHT_ORBS)) {
                Actor_PlaySfxAtPos(actor, NA_SE_EN_COMMON_DEADLIGHT - SFX_FLAG);
            }
        }

        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C2DC(globalCtx->state.gfxCtx);

        switch (type) {
            case ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX:
            case ACTOR_DRAW_DMGEFF_FROZEN_SFX:
                frozenScale = ((KREG(19) * 0.01f) + 2.3f) * effectScale;
                steamScale = ((KREG(28) * 0.0001f) + 0.035f) * frozenSteamScale;
                func_800BCC68(limbPos, globalCtx);

                // Setup to draw ice over frozen actor

                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, gameplayFrames & 0xFF, 32, 16, 1, 0,
                                            (gameplayFrames * 2) & 0xFF, 64, 32));
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, 255);
                gSPDisplayList(POLY_XLU_DISP++, gFrozenIceDL);

                effectAlphaScaled = effectAlpha * 255.0f;

                // Apply and draw ice over each limb of frozen actor
                for (limbIndex = 0; limbIndex < limbPosCount; limbIndex++, limbPos++) {
                    alpha = limbIndex & 3;
                    alpha = effectAlphaScaled - (30.0f * alpha);
                    if (effectAlphaScaled < (30.0f * (limbIndex & 3))) {
                        alpha = 0.0f;
                    }
                    if (alpha > 255.0f) {
                        alpha = 255.0f;
                    }

                    gDPSetEnvColor(POLY_XLU_DISP++, KREG(20) + 200, KREG(21) + 200, KREG(22) + 255, (u8)alpha);

                    Matrix_InsertTranslation(limbPos->x, limbPos->y, limbPos->z, MTXMODE_NEW);
                    Matrix_Scale(frozenScale, frozenScale, frozenScale, MTXMODE_APPLY);

                    if (limbIndex & 1) {
                        Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
                    }

                    if (limbIndex & 2) {
                        Matrix_InsertZRotation_f(M_PI, MTXMODE_APPLY);
                    }

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gFrozenIceVtxDL);
                }

                limbPos = limbPosStart; // reset limbPos

                // Setup to draw steam over frozen actor

                gDPSetColorDither(POLY_XLU_DISP++, G_CD_BAYER);
                gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_PATTERN);
                gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamDL);

                alpha = effectAlpha * 100.0f;
                if (alpha > 100.0f) {
                    alpha = 100.0f;
                }

                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, (u8)alpha);

                // Apply and draw steam over each limb of frozen actor
                for (limbIndex = 0; limbIndex < limbPosCount; limbIndex++, limbPos++) {
                    twoTexScrollParam = ((limbIndex * 3) + gameplayFrames);
                    gSPSegment(POLY_XLU_DISP++, 0x08,
                               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, twoTexScrollParam * 3,
                                                twoTexScrollParam * -12, 32, 64, 1, 0, 0, 32, 32));

                    Matrix_InsertTranslation(limbPos->x, limbPos->y, limbPos->z, MTXMODE_NEW);
                    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
                    Matrix_Scale(steamScale, steamScale, 1.0f, MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamVtxDL);
                }
                break;

            case ACTOR_DRAW_DMGEFF_FIRE:
            case ACTOR_DRAW_DMGEFF_BLUE_FIRE:
                if (type == ACTOR_DRAW_DMGEFF_FIRE) {
                    gDPSetEnvColor(POLY_XLU_DISP++, 255, 10, 0, 0);
                } else {
                    gDPSetEnvColor(POLY_XLU_DISP++, 0, 255, 255, 0);
                    // Reuse type for blue primitive color
                    type = 255;
                }

                Matrix_SetCurrentState(&globalCtx->billboardMtxF);
                Matrix_Scale((effectScale * 0.005f) * 1.35f, (effectScale * 0.005f), (effectScale * 0.005f) * 1.35f,
                             MTXMODE_APPLY);

                effectAlphaScaled = effectAlpha * 255.0f;

                // Apply and draw fire on every limb
                for (limbIndex = 0; limbIndex < limbPosCount; limbIndex++, limbPos++) {
                    alpha = limbIndex & 3;
                    alpha = effectAlphaScaled - 30.0f * alpha;
                    if (effectAlphaScaled < 30.0f * (limbIndex & 3)) {
                        alpha = 0.0f;
                    }
                    if (alpha > 255.0f) {
                        alpha = 255.0f;
                    }

                    // Use type for blue primitive color
                    // = 0 for ACTOR_DRAW_DMGEFF_FIRE
                    // = 255 for ACTOR_DRAW_DMGEFF_BLUE_FIRE
                    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, type, (u8)alpha);

                    gSPSegment(POLY_XLU_DISP++, 0x08,
                               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0,
                                                ((limbIndex * 10 + gameplayFrames) * -20) & 0x1FF, 32, 128));

                    Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
                    currentMatrix->mf[3][0] = limbPos->x;
                    currentMatrix->mf[3][1] = limbPos->y;
                    currentMatrix->mf[3][2] = limbPos->z;

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);
                }
                break;

            case ACTOR_DRAW_DMGEFF_LIGHT_ORBS:
            case ACTOR_DRAW_DMGEFF_BLUE_LIGHT_ORBS:

                // Setup to draw light orbs on actor

                lightOrbsScale = ((KREG(19) * 0.01f) + 4.0f) * effectScale;

                gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);

                alpha = effectAlpha * 255.0f;
                if (alpha > 255.0f) {
                    alpha = 255.0f;
                }

                if (type == ACTOR_DRAW_DMGEFF_BLUE_LIGHT_ORBS) {
                    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)(sREG(16) + 255), (u8)(sREG(17) + 255),
                                    (u8)(sREG(18) + 255), (u8)alpha);

                    gDPSetEnvColor(POLY_XLU_DISP++, (u8)sREG(19), (u8)(sREG(20) + 255), (u8)(sREG(21) + 255), 128);
                } else {
                    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (u8)alpha);

                    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 100, 128);
                }

                Matrix_SetCurrentState(&globalCtx->billboardMtxF);
                Matrix_Scale(lightOrbsScale, lightOrbsScale, 1.0f, MTXMODE_APPLY);

                // Apply and draw a light orb over each limb of frozen actor
                for (limbIndex = 0; limbIndex < limbPosCount; limbIndex++, limbPos++) {
                    Matrix_InsertZRotation_f(randPlusMinusPoint5Scaled(2 * M_PI), MTXMODE_APPLY);
                    currentMatrix->mf[3][0] = limbPos->x;
                    currentMatrix->mf[3][1] = limbPos->y;
                    currentMatrix->mf[3][2] = limbPos->z;

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
                }
                break;

            case ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL:
            case ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM:
            case ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE:
                if (type == ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL) {
                    electricSparksScale = (KREG(19) * 0.01f + 1.0f) * effectScale;
                } else if (type == ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM) {
                    electricSparksScale = (KREG(19) * 0.01f + 1.5f) * effectScale;
                } else {
                    electricSparksScale = (KREG(19) * 0.01f + 2.0f) * effectScale;
                }

                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Lib_SegmentedToVirtual(sElectricSparkTextures[globalCtx->gameplayFrames % 4]));

                gSPDisplayList(POLY_XLU_DISP++, gElectricSparkDL);

                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)(sREG(16) + 255), (u8)(sREG(17) + 255), (u8)(sREG(18) + 150),
                                (u8)(sREG(19) + 255));

                gDPSetEnvColor(POLY_XLU_DISP++, (u8)(sREG(20) + 255), (u8)(sREG(21) + 255), (u8)sREG(22), (u8)sREG(23));

                Matrix_SetCurrentState(&globalCtx->billboardMtxF);
                Matrix_Scale(electricSparksScale, electricSparksScale, electricSparksScale, MTXMODE_APPLY);

                // Every limb draws two electric sparks at random orientations
                for (limbIndex = 0; limbIndex < limbPosCount; limbIndex++, limbPos++) {
                    // first electric spark
                    Matrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    Matrix_InsertZRotation_f(Rand_ZeroFloat(2 * M_PI), MTXMODE_APPLY);
                    currentMatrix->mf[3][0] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->x;
                    currentMatrix->mf[3][1] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->y;
                    currentMatrix->mf[3][2] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->z;

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gElectricSparkVtxDL);

                    // second electric spark
                    Matrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    Matrix_InsertZRotation_f(Rand_ZeroFloat(2 * M_PI), MTXMODE_APPLY);
                    currentMatrix->mf[3][0] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->x;
                    currentMatrix->mf[3][1] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->y;
                    currentMatrix->mf[3][2] = randPlusMinusPoint5Scaled((f32)sREG(24) + 30.0f) + limbPos->z;

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_XLU_DISP++, gElectricSparkVtxDL);
                }

                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void Actor_SpawnIceEffects(GlobalContext* globalCtx, Actor* actor, Vec3f limbPos[], s32 limbPosCount,
                           s32 effectsPerLimb, f32 scale, f32 scaleRange) {
    static Color_RGBA8 primColor = { 170, 255, 255, 255 };
    static Color_RGBA8 envColor = { 200, 200, 255, 255 };
    static Vec3f accel = { 0.0f, -1.0f, 0.0f };
    s32 i;
    s32 pad;
    Vec3f velocity;
    s16 randomYaw;
    s16 yaw;
    s32 j;

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &actor->world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < limbPosCount; i++) {
        yaw = Actor_YawToPoint(actor, limbPos);

        for (j = 0; j < effectsPerLimb; j++) {
            randomYaw = (Rand_Next() >> 0x13) + yaw;

            velocity.z = Rand_ZeroFloat(5.0f);

            velocity.x = Math_SinS(randomYaw) * velocity.z;
            velocity.y = Rand_ZeroFloat(4.0f) + 8.0f;
            velocity.z *= Math_CosS(randomYaw);

            EffectSsEnIce_Spawn(globalCtx, limbPos, Rand_ZeroFloat(scaleRange) + scale, &velocity, &accel, &primColor,
                                &envColor, 30);
        }

        limbPos++;
    }
}
