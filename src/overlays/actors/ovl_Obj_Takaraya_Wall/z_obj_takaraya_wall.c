/*
 * File: z_obj_takaraya_wall.c
 * Overlay: ovl_Obj_Takaraya_Wall
 * Description: Treasure Chest Shop rising wall
 */

#include "z_obj_takaraya_wall.h"
#include "objects/object_takaraya_objects/object_takaraya_objects.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjTakarayaWall*)thisx)

void ObjTakarayaWall_Init(Actor* thisx, PlayState* play);
void ObjTakarayaWall_Destroy(Actor* thisx, PlayState* play);
void ObjTakarayaWall_Update(Actor* thisx, PlayState* play2);
void ObjTakarayaWall_Draw(Actor* thisx, PlayState* play);

void func_80AD9B04(ObjTakarayaWall* this, PlayState* play);

ActorInit Obj_Takaraya_Wall_InitVars = {
    ACTOR_OBJ_TAKARAYA_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TAKARAYA_OBJECTS,
    sizeof(ObjTakarayaWall),
    (ActorFunc)ObjTakarayaWall_Init,
    (ActorFunc)ObjTakarayaWall_Destroy,
    (ActorFunc)ObjTakarayaWall_Update,
    (ActorFunc)ObjTakarayaWall_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 40, 120, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

typedef struct TakarayaUnkStruct {
    /* 0 */ u8 unk0;
    /* 1 */ u8 unk1;
} TakarayaUnkStruct; // size = 0x2

s32 D_80ADA450;
TakarayaUnkStruct D_80ADA458[88];
s32 D_80ADA508;
s32 D_80ADA50C;
Vec3f D_80ADA510[11][8];
u8 D_80ADA930[11][8];
f32 D_80ADA988[11][8];

s32 func_80AD9240(PosRot* arg0, s32* arg1, s32* arg2) {
    *arg1 = ((s32)arg0->pos.x + (14 * 120)) / 120;
    *arg2 = (s32)arg0->pos.z / 120;

    if ((*arg1 < 0) || (*arg1 >= ARRAY_COUNT(D_80ADA988)) || (*arg2 < 0) || (*arg2 >= ARRAY_COUNT(D_80ADA988[0]))) {
        return false;
    }
    return true;
}

s32 func_80AD92FC(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= ARRAY_COUNT(D_80ADA988)) || (arg1 < 0) || (arg1 >= ARRAY_COUNT(D_80ADA988[0])) ||
        (D_80ADA988[arg0][arg1] == 0.0f)) {
        return false;
    }

    return true;
}

s32 func_80AD9358(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    if ((arg2 == 2) || (arg2 == 0)) {
        if (arg2 == 0) {
            var_v0 = arg0 - 1;
            sp1C = arg0 - 2;
        } else {
            var_v0 = arg0 + 1;
            sp1C = arg0 + 2;
        }
        var_v1 = arg1;
        sp18 = arg1;
        var_a2 = var_v0;
        var_a3 = arg1 + 1;
        sp24 = var_v0;
        sp20 = arg1 - 1;
    } else {
        if (arg2 == 1) {
            var_v1 = arg1 - 1;
            sp18 = arg1 - 2;
        } else {
            var_v1 = arg1 + 1;
            sp18 = arg1 + 2;
        }
        var_v0 = arg0;
        sp1C = arg0;
        var_a2 = arg0 + 1;
        var_a3 = var_v1;
        sp24 = arg0 - 1;
        sp20 = var_v1;
    }

    if ((var_v0 < 0) || (var_v0 >= ARRAY_COUNT(D_80ADA988)) || (var_v1 < 0) || (var_v1 >= ARRAY_COUNT(D_80ADA988[0])) ||
        (D_80ADA988[var_v0][var_v1] == -10.0f) || func_80AD92FC(var_a2, var_a3) || func_80AD92FC(sp24, sp20) ||
        func_80AD92FC(sp1C, sp18)) {
        return false;
    }

    return true;
}

void func_80AD9488(s32 arg0, s32 arg1) {
    s32 sp1C = 0;
    s32 sp18 = 0;
    s32 temp_hi;
    s32 var_v0;

    if (func_80AD9358(arg0, arg1, 0)) {
        sp18++;
        sp1C |= 1;
    }

    if (func_80AD9358(arg0, arg1, 1)) {
        sp18++;
        sp1C |= 2;
    }

    if (func_80AD9358(arg0, arg1, 2)) {
        sp18++;
        sp1C |= 4;
    }

    if (func_80AD9358(arg0, arg1, 3)) {
        sp18++;
        sp1C |= 8;
    }

    if (sp18 == 0) {
        D_80ADA450--;
        if (D_80ADA50C == 0) {
            D_80ADA508--;
        }
    } else {
        temp_hi = (s32)Rand_ZeroFloat(sp18) % sp18;
        if (temp_hi == 0) {
            var_v0 = 0;
            while (!((1 << var_v0) & sp1C)) {
                var_v0++;
            }
        } else if (temp_hi == 1) {
            var_v0 = 3;
            while (!((1 << var_v0) & sp1C)) {
                var_v0--;
            }
        } else if (temp_hi == 2) {
            var_v0 = 0;
            while (!((1 << var_v0) & sp1C)) {
                var_v0++;
            }
            var_v0++;
            while (!((1 << var_v0) & sp1C)) {
                var_v0++;
            }
        } else {
            var_v0 = 3;
            while (!((1 << var_v0) & sp1C)) {
                var_v0--;
            }
            var_v0--;
            while (!((1 << var_v0) & sp1C)) {
                var_v0--;
            }
        }

        if (var_v0 == 0) {
            arg0--;
        } else if (var_v0 == 2) {
            arg0++;
        } else if (var_v0 == 1) {
            arg1--;
        } else {
            arg1++;
        }

        D_80ADA988[arg0][arg1] = -10.0f;
        D_80ADA458[D_80ADA450].unk0 = arg0;
        D_80ADA458[D_80ADA450].unk1 = arg1;
        D_80ADA450++;
        if (D_80ADA50C == 0) {
            D_80ADA508++;
            if (arg0 == 10) {
                D_80ADA50C = 1;
            }
        }
    }
}

void ObjTakarayaWall_Init(Actor* thisx, PlayState* play) {
    ObjTakarayaWall* this = THIS;
    Actor* chest;
    s32 index;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    for (i = 0; i < ARRAY_COUNT(D_80ADA988); i++) {
        for (j = 0; j < ARRAY_COUNT(D_80ADA988[0]); j++) {
            D_80ADA988[i][j] = 0.0f;
        }
    }

    Collider_InitAndSetCylinder(play, &this->unk148, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(play, &this->unk194, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    index = (s32)Rand_ZeroFloat(8.0f) % 8;
    chest = Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_EN_BOX, -1635.0f, 0.0f, (index * 120) + 60, 0,
                                          0x4000, this->actor.shape.rot.z, this->actor.params, this->actor.csId,
                                          HALFDAYBIT_ALL, NULL);
    Flags_SetSwitch(play, this->actor.shape.rot.z);
    this->actor.shape.rot.z = 0;

    if (chest != NULL) {
        chest->uncullZoneForward = 2000.0f;
    }

    D_80ADA988[0][index] = -10.0f;
    D_80ADA458[D_80ADA450].unk0 = 0;
    D_80ADA458[D_80ADA450].unk1 = index;
    D_80ADA450++;
    D_80ADA508++;

    do {
        func_80AD9488(D_80ADA458[D_80ADA450 - 1].unk0, D_80ADA458[D_80ADA450 - 1].unk1);
    } while (D_80ADA450 >= 2);

    for (j = 1; j < ARRAY_COUNT(D_80ADA988[0]) - 1; j++) {
        if (D_80ADA988[10][j] == -10.0f) {
            break;
        }
    }

    if (j == 7) {
        if (D_80ADA988[10][0] == -10.0f) {
            D_80ADA988[10][1] = -10.0f;
        } else {
            D_80ADA988[10][6] = -10.0f;
        }
    }

    this->actionFunc = func_80AD9B04;
}

void ObjTakarayaWall_Destroy(Actor* thisx, PlayState* play) {
    ObjTakarayaWall* this = THIS;
    s32 i;
    s32 j;

    Collider_DestroyCylinder(play, &this->unk148);
    Collider_DestroyCylinder(play, &this->unk194);

    for (i = 0; i < ARRAY_COUNT(D_80ADA510); i++) {
        for (j = 0; j < ARRAY_COUNT(D_80ADA510[0]); j++) {
            AudioSfx_StopByPos(&D_80ADA510[i][j]);
        }
    }
}

void func_80AD9B04(ObjTakarayaWall* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    ColliderCylinder* collider;
    s32 var_fp;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 var_s2;
    s32 var_s1;
    s32 sp90;
    s32 sp8C;
    s32 var_s7;

    spA4 = 0;
    spA8 = 0;
    var_s7 = -1;
    var_fp = -1;
    sp8C = sp90 = -1;

    func_80AD9240(&player->actor.world, &spB0, &spAC);
    spA0 = (((s32)player->actor.world.pos.x + (15 * 120)) % 120) - 60;
    sp9C = (((s32)player->actor.world.pos.z + (1 * 120)) % 120) - 60;

    if (spA0 > 20) {
        var_fp = spB0 + 1;
    } else if (spA0 < -20) {
        var_s7 = spB0 - 1;
    }

    if (sp9C > 20) {
        sp8C = spAC + 1;
    } else if (sp9C < -20) {
        sp90 = spAC - 1;
    }

    for (var_s2 = 0; var_s2 < ARRAY_COUNT(D_80ADA988); var_s2++) {
        for (var_s1 = 0; var_s1 < ARRAY_COUNT(D_80ADA988[0]); var_s1++) {
            if (D_80ADA988[var_s2][var_s1] >= 0.0f) {
                if (((var_s1 == spAC) && ((var_s2 == var_s7) || (var_s2 == var_fp))) ||
                    ((var_s2 == spB0) && ((var_s1 == sp90) || (var_s1 == sp8C)))) {
                    if (Math_StepToF(&D_80ADA988[var_s2][var_s1], 120.0f, 15.0f)) {
                        D_80ADA930[var_s2][var_s1] = 0;
                    } else {
                        D_80ADA930[var_s2][var_s1] = 1;
                    }
                    if (var_s1 == spAC) {
                        spA8 = 1;
                    } else if (var_s2 == spB0) {
                        spA4 = 1;
                    }
                } else if ((var_s2 != spB0) || (var_s1 != spAC)) {
                    Math_SmoothStepToF(&D_80ADA988[var_s2][var_s1], 0.0f, 0.2f, 5.0f, 1.0f);
                    D_80ADA930[var_s2][var_s1] = 2;
                }
            }
        }
    }

    collider = &this->unk148;
    collider->dim.radius = 200;
    if (spA8 == 0) {
        collider->dim.pos.y = (s32)this->actor.world.pos.y - 240;
    } else {
        collider->dim.pos.y = (s32)this->actor.world.pos.y;
        collider->dim.pos.z = (s32)player->actor.world.pos.z;
        if (spA0 > 0) {
            collider->dim.pos.x = ((((s32)player->actor.world.pos.x + (14 * 120)) / 120) * 120) - 1380;
        } else {
            collider->dim.pos.x = ((((s32)player->actor.world.pos.x + (14 * 120)) / 120) * 120) - 1860;
        }
    }

    collider = &this->unk194;
    collider->dim.radius = 200;
    if (spA4 == 0) {
        collider->dim.pos.y = (s32)this->actor.world.pos.y - 240;
    } else {
        collider->dim.pos.y = (s32)this->actor.world.pos.y;
        collider->dim.pos.x = (s32)player->actor.world.pos.x;
        if (sp9C > 0) {
            collider->dim.pos.z = (((s32)player->actor.world.pos.z / 120) * 120) + 300;
        } else {
            collider->dim.pos.z = (((s32)player->actor.world.pos.z / 120) * 120) - 180;
        }
    }
}

void ObjTakarayaWall_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjTakarayaWall* this = THIS;

    this->actionFunc(this, play);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk148.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk194.base);
}

void ObjTakarayaWall_Draw(Actor* thisx, PlayState* play) {
    Vec3f sp94;
    ObjTakarayaWall* this = THIS;
    MtxF* mtx;
    Gfx* gfx;
    s32 i;
    s32 j;

    OPEN_DISPS(play->state.gfxCtx);

    mtx = Matrix_GetCurrent();
    gfx = POLY_OPA_DISP;
    gSPDisplayList(gfx++, gSetupDLs[SETUPDL_25]);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < ARRAY_COUNT(D_80ADA988); i++) {
        for (j = 0; j < ARRAY_COUNT(D_80ADA988[0]); j++) {
            if (D_80ADA988[i][j] > 0.0f) {
                mtx->xw = (i * 120) - 1620;
                mtx->yw = D_80ADA988[i][j] + (this->actor.world.pos.y - 120.0f);
                mtx->zw = (j * 120) + 60;

                gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (((i + j) % 2) != 0) {
                    gSPDisplayList(gfx++, object_takaraya_objects_DL_000D60);
                } else {
                    gSPDisplayList(gfx++, object_takaraya_objects_DL_000B70);
                }

                if (D_80ADA930[i][j] != 0) {
                    sp94.x = mtx->xw;
                    sp94.y = mtx->yw;
                    sp94.z = mtx->zw;

                    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &sp94, &D_80ADA510[i][j]);

                    if (D_80ADA930[i][j] == 1) {
                        Audio_PlaySfx_AtPos(&D_80ADA510[i][j], NA_SE_EV_ROCK_CUBE_RISING - SFX_FLAG);
                    } else {
                        Audio_PlaySfx_AtPos(&D_80ADA510[i][j], NA_SE_EV_ROCK_CUBE_FALL - SFX_FLAG);
                    }
                }
            }
        }
    }

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}
