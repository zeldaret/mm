/*
 * File: z_obj_switch.c
 * Overlay: ovl_Obj_Switch
 * Description: Floor and Eye Switches
 */

#include "z_obj_switch.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwitch*)thisx)

#define COS_OF_5_PI_DIV_8 -0.38268343f

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8093B6F4(ObjSwitch* this);
void func_8093B92C(ObjSwitch* this);
void func_8093B9C0(ObjSwitch* this);
void func_8093BB5C(ObjSwitch* this);
void func_8093BCC8(ObjSwitch* this);
void func_8093BD34(ObjSwitch* this);
void func_8093BDAC(ObjSwitch* this);
void func_8093BE10(ObjSwitch* this);
void func_8093BEF0(ObjSwitch* this);
void func_8093BF50(ObjSwitch* this);
void func_8093C0A4(ObjSwitch* this);
void func_8093C138(ObjSwitch* this);
void func_8093C23C(ObjSwitch* this);
void func_8093C2B4(ObjSwitch* this);
void func_8093C3C8(ObjSwitch* this);
void func_8093C460(ObjSwitch* this);
void func_8093C584(ObjSwitch* this);

void func_8093AF54(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093B668(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093B710(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093B940(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093B9E4(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BB70(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BCDC(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BD4C(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BDC0(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BE2C(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BF04(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093BF70(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C0B8(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C15C(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C250(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C2D4(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C3DC(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C488(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C598(ObjSwitch* this, GlobalContext* globalCtx);

void func_8093C778(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C888(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C8B8(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093C99C(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093CA80(ObjSwitch* this, GlobalContext* globalCtx);
void func_8093CAC4(ObjSwitch* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Switch_InitVars = {
    ACTOR_OBJ_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSwitch),
    (ActorFunc)ObjSwitch_Init,
    (ActorFunc)ObjSwitch_Destroy,
    (ActorFunc)ObjSwitch_Update,
    (ActorFunc)ObjSwitch_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_8093CCD4[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000400, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, 20.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000400, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, -20.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093CD4C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_8093CCD4, // sTrisElementsInit,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_8093CD5C[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093CDD4 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_8093CD5C, // sTrisElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8093CDE4[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01CBFFBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 300, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8093CE08 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_8093CDE4, // sJntSphElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093CE18[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

#endif

extern CollisionHeader D_05008018;
extern Gfx D_0501BEE0[];
extern Gfx D_0501BFB8[];
extern AnimatedMaterial D_0501C118;
extern AnimatedMaterial* D_8093D3B0;

extern Gfx* D_8093CC60[2][4];
extern ColliderTrisElementInit D_8093CCD4[2];
extern ColliderTrisInit D_8093CD4C;
extern ColliderTrisElementInit D_8093CD5C[2];
extern ColliderTrisInit D_8093CDD4;
extern ColliderJntSphElementInit D_8093CDE4[1];
extern ColliderJntSphInit D_8093CE08;
extern InitChainEntry D_8093CE18[];
extern s32 D_8093CC80;
extern f32 D_8093CCA4[];
extern f32 D_8093CCBC[];
extern Color_RGB8 D_8093CE24[2];
extern Gfx* D_8093CE2C[];
extern Gfx* D_8093CE40[];

#define ObjSwitch_Get_0070(p) ((p >> 4) & 7)

void func_8093ABD0(ObjSwitch* this, GlobalContext* globalCtx, ColliderJntSphInit* init) {
    s32 pad;

    Collider_InitJntSph(globalCtx, &this->colliderJntSph);
    Collider_SetJntSph(globalCtx, &this->colliderJntSph, &this->dyna.actor, init, this->colliderJntSphElements);
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x,
                                          this->dyna.actor.world.pos.y +
                                              (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y),
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, 1);
    Collider_UpdateSpheres(0, &this->colliderJntSph);
}

void func_8093AC6C(ObjSwitch* this, GlobalContext* globalCtx, ColliderTrisInit* init);

#ifdef NON_MATCHING
void func_8093AC6C(ObjSwitch* this, GlobalContext* globalCtx, ColliderTrisInit* init) {
    s32 pad;
    s32 s2;
    s32 s1;
    Vec3f vtx[3]; // sp58

    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->dyna.actor, init, this->colliderTrisElements);
    Matrix_StatePush();
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x,
                                          this->dyna.actor.world.pos.y +
                                              (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y),
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (s2 = 0; s2 < 2; s2++) {
        for (s1 = 0; s1 < 3; s1++) {
            Matrix_MultiplyVector3fByState(&init->elements[s2].dim.vtx[s1], &vtx[s1]);
        }
        Collider_SetTrisVertices(&this->colliderTris, s2, &vtx[0], &vtx[1], &vtx[2]);
    }
    Matrix_StatePop();
}
#else
void func_8093AC6C(ObjSwitch* this, GlobalContext* globalCtx, ColliderTrisInit* init);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AC6C.s")
#endif

Actor* func_8093ADA8(ObjSwitch* this, GlobalContext* globalCtx) {
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_OBJ_ICE_POLY,
                       this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y - 25.0f, this->dyna.actor.world.pos.z,
                       this->dyna.actor.world.rot.x, this->dyna.actor.world.rot.y, this->dyna.actor.world.rot.z,
                       0xFF32);
}

void func_8093AE1C(ObjSwitch* this, GlobalContext* globalCtx, s32 arg2) {
    if (arg2 != 0) {
        s32 flag = (this->dyna.actor.params >> 8) & 0x7F;
        Actor_SetSwitchFlag(globalCtx, flag);
    } else {
        s32 flag = (this->dyna.actor.params >> 8) & 0x7F;
        Actor_UnsetSwitchFlag(globalCtx, flag);
    }
}

void func_8093AE74(ObjSwitch* this) {
    this->unk_168++;
}

void func_8093AE88(ObjSwitch* this) {
    if (this->unk_172 != 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->unk_172 = 0;
    }
}

void func_8093AEC4(ObjSwitch* this) {
    if (this->unk_165 <= 0) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_FOOT_SWITCH);
    }
}

void func_8093AEF0(ObjSwitch* this) {
    if (this->unk_165 <= 0) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DIAMOND_SWITCH);
    }
}

void func_8093AF1C(ObjSwitch* this, s32 arg1) {
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        this->unk_170 = arg1;
    }
}

void func_8093AF54(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player;
    f32 sp24;
    s16 angle;
    f32 cos;

    if (globalCtx->actorCtx.unk5 & 0x80) {
        player = GET_PLAYER(globalCtx);
        angle = BINANG_SUB(this->dyna.actor.yawTowardsPlayer, this->dyna.actor.shape.rot.y);
        angle += 0x2000;
        angle &= 0x3FFF;
        angle -= 0x2000;
        sp24 = !(this->dyna.actor.params & 7) ? 24.0f : 48.0f;

        cos = Math_CosS(angle);
        if (fabsf(cos) > 0.01f) {
            sp24 /= cos;
            if (sp24 < this->dyna.actor.xzDistToPlayer) {
                player->actor.world.pos.x =
                    Math_SinS(this->dyna.actor.yawTowardsPlayer) * sp24 + this->dyna.actor.world.pos.x;
                player->actor.world.pos.z =
                    Math_CosS(this->dyna.actor.yawTowardsPlayer) * sp24 + this->dyna.actor.world.pos.z;
            }
            player->linearVelocity = 0.0f;
        }
    }
}

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp_s1;
    u32 sp4C;
    ObjSwitch* this = (ObjSwitch*)thisx;
    s32 pad2;

    sp4C = Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F);
    temp_s1 = this->dyna.actor.params & 7;
    Actor_ProcessInitChain(&this->dyna.actor, D_8093CE18);
    Actor_SetScale(&this->dyna.actor, D_8093CCBC[temp_s1]);

    if (temp_s1 == 0 || temp_s1 == 1 || temp_s1 == 5) {
        if (temp_s1 == 5) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.9f;
        } else {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.0f;
        }
        DynaPolyActor_Init(&this->dyna, 1);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_05008018);
    }
    if (temp_s1 == 0) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            this->unk_250 = 0.055000003f;
            this->unk_254 = 0.0055f;
        } else {
            this->unk_250 = 0.165f;
            this->unk_254 = 0.0165f;
        }
    }
    if ((temp_s1 == 0) || (temp_s1 == 5)) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            Color_RGB8* temp_v0 = &D_8093CE24[(this->dyna.actor.home.rot.z & 1)];
            this->unk_16C = temp_v0->r;
            this->unk_16D = temp_v0->g;
            this->unk_16E = temp_v0->b;
            this->dyna.actor.shape.rot.z = 0;
            this->dyna.actor.world.rot.z = 0;
        } else {
            this->unk_16C = 255;
            this->unk_16D = 255;
            this->unk_16E = 255;
        }
    }
    Actor_SetHeight(&this->dyna.actor, D_8093CCA4[temp_s1]);

    if (temp_s1 == 1) {
        func_8093AC6C(this, globalCtx, &D_8093CD4C);
    } else if (temp_s1 == 2) {
        func_8093AC6C(this, globalCtx, &D_8093CDD4);
    } else if ((temp_s1 == 3) || (temp_s1 == 4)) {
        func_8093ABD0(this, globalCtx, &D_8093CE08);
    }
    if (temp_s1 == 4) {
        this->dyna.actor.targetMode = 4;
        this->dyna.actor.flags |= 1;
    }
    this->dyna.actor.colChkInfo.mass = 0xFF;
    if ((this->dyna.actor.params >> 7) & 1) {
        if (func_8093ADA8(this, globalCtx) == NULL) {
            this->dyna.actor.params &= 0xFF7F;
        }
        this->unk_165 = 0;
    } else {
        this->unk_165 = 10;
    }
    if ((this->dyna.actor.params >> 3) & 1) {
        this->dyna.actor.flags |= 0x80;
    }
    if (temp_s1 == 2) {
        if (D_8093CC80 == 0) {
            s32 i, j;
            D_8093CC80 = 1;

            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j++) {
                    D_8093CC60[i][j] = Lib_SegmentedToVirtual(D_8093CC60[i][j]);
                }
            }
        }
    }
    if (temp_s1 == 3) {
        D_8093D3B0 = Lib_SegmentedToVirtual(&D_0501C118);
    }
    if (((this->dyna.actor.params >> 7) & 1) != 0) {
        func_8093BCC8(this);
    } else if (temp_s1 == 0 || temp_s1 == 1) {
        if ((((s32)this->dyna.actor.params >> 4) & 7) == 3) {
            if (sp4C != 0) {
                func_8093B6F4(this);
            } else {
                func_8093B9C0(this);
            }
        } else if (sp4C != 0) {
            func_8093B9C0(this);
        } else {
            func_8093B6F4(this);
        }
    } else if (temp_s1 == 2) {
        if (sp4C != 0) {
            func_8093BE10(this);
        } else {
            func_8093BD34(this);
        }
    } else if (temp_s1 == 3 || temp_s1 == 4) {
        if (sp4C != 0) {
            func_8093C138(this);
        } else {
            func_8093BF50(this);
        }
    } else if (temp_s1 == 5) {
        if (((this->dyna.actor.params >> 4) & 7) == 3) {
            if (sp4C != 0) {
                func_8093C2B4(this);
            } else {
                func_8093C460(this);
            }
        } else if (sp4C != 0) {
            func_8093C460(this);
        } else {
            func_8093C2B4(this);
        }
    }
}

void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjSwitch* this = (ObjSwitch*)thisx;
    s32 type = this->dyna.actor.params & 7;

    if (type == 0 || type == 1 || type == 5) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
    switch (type) {
        case 1:
        case 2:
            Collider_DestroyTris(globalCtx, &this->colliderTris);
            return;
        case 3:
        case 4:
            Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
            return;
    }
}

void func_8093B648(ObjSwitch* this, GlobalContext* globalCtx, ObjSwitchSetupActionFunc actionFunc, s32 arg3) {
    this->setupFunc = actionFunc;
    this->unk_171 = arg3;
    this->actionFunc = func_8093B668;
}

void func_8093B668(ObjSwitch* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_8093AE1C(this, globalCtx, this->unk_171);
        if (this->unk_170 == 1) {
            this->unk_170 = 2;
        }
        this->unk_172 = 1;
        this->setupFunc(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_8093B6F4(ObjSwitch* this) {
    this->actionFunc = func_8093B710;
    this->dyna.actor.scale.y = this->unk_250;
}

// TODO: verify type 1 is JntSph
void func_8093B710(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;

    if ((this->dyna.actor.params & 7) == 1) {
        if (this->colliderTris.base.acFlags & 2) {
            this->colliderTris.base.acFlags &= ~AT_HIT;
            func_8093B648(this, globalCtx, func_8093B92C, 1);
        } else {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
        }
    } else {
        switch ((this->dyna.actor.params >> 4) & 7) {
            case 0:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, 1);
                }
                break;
            case 4:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, 1);
                } else if (Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
                    func_8093B92C(this);
                }
                break;
            case 1:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    s32 sp20 = Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F) ? 0 : 1;

                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, sp20);
                }
                break;
            case 2:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, 1);
                }
                break;
            case 3:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 2);
                    func_8093AE1C(this, globalCtx, 0);
                    func_8093B92C(this);
                }
                break;
        }
    }
}

void func_8093B92C(ObjSwitch* this) {
    this->actionFunc = func_8093B940;
}

void func_8093B940(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y -= 0.0495f;
    if (this->dyna.actor.scale.y <= this->unk_254) {
        func_8093AEC4(this);
        func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        func_8093AE88(this);
        func_8093B9C0(this);
    }
}

void func_8093B9C0(ObjSwitch* this) {
    this->unk_160 = 6;
    this->actionFunc = func_8093B9E4;
    this->dyna.actor.scale.y = this->unk_254;
}

void func_8093B9E4(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    u32 temp_v0 = (this->dyna.actor.params >> 4) & 7;

    switch (temp_v0) {
        case 0:
        case 4:
            if (!Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
                if (globalCtx->sceneNum == SCENE_SECOM && DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AE1C(this, globalCtx, 1);
                } else {
                    func_8093BB5C(this);
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            if (!DynaPolyActor_IsInSwitchPressedState(&this->dyna) &&
                (func_801233E4(globalCtx) == 0 || globalCtx->sceneNum == SCENE_SECOM)) {
                if (this->unk_160 <= 0) {
                    if (temp_v0 == 2) {
                        func_8093AE1C(this, globalCtx, 0);
                        func_8093BB5C(this);
                    } else if (temp_v0 == 3) {
                        func_8093B648(this, globalCtx, func_8093BB5C, 1);
                    } else {
                        func_8093BB5C(this);
                    }
                }
            } else {
                if (globalCtx->sceneNum == SCENE_SECOM) {
                    this->unk_160 = 2;
                } else {
                    this->unk_160 = 6;
                }
            }
            break;
    }
}

void func_8093BB5C(ObjSwitch* this) {
    this->actionFunc = func_8093BB70;
}

void func_8093BB70(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y += 0.0495f;
    if (this->unk_250 <= this->dyna.actor.scale.y) {
        func_8093AEC4(this);
        func_8093AE88(this);
        func_8093B6F4(this);
    }
}

// OoT ObjSwitch_EyeIsHit
s32 func_8093BBD0(ObjSwitch* this) {
    Actor* acActor;
    Actor* actor = &this->dyna.actor;

    // TODO verify JntSph
    if ((this->colliderJntSph.base.acFlags & 2) && !(this->unk_16F & 2)) {
        acActor = this->colliderJntSph.base.ac;
        if (acActor != NULL) {
            Vec3f sp2C;
            Vec3f sp20;

            Matrix_StatePush();
            Matrix_RotateY(acActor->world.rot.y, 0);
            Matrix_InsertXRotation_s(acActor->world.rot.x, 1);
            Matrix_GetStateTranslationAndScaledZ(1.0f, &sp2C);
            Matrix_RotateY(actor->shape.rot.y, 0);
            Matrix_InsertXRotation_s(actor->shape.rot.x, 1);
            Matrix_InsertZRotation_s(actor->shape.rot.z, 1);
            Matrix_GetStateTranslationAndScaledZ(1.0f, &sp20);
            Matrix_StatePop();
            if ((Math3D_Parallel(&sp2C, &sp20) < COS_OF_5_PI_DIV_8)) {
                return true;
            }
        }
    }
    return false;
}

void func_8093BCC8(ObjSwitch* this) {
    this->actionFunc = func_8093BCDC;
}

void func_8093BCDC(ObjSwitch* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
        func_8093BE10(this);
    } else {
        func_8093BD34(this);
    }
}

void func_8093BD34(ObjSwitch* this) {
    this->actionFunc = func_8093BD4C;
    this->unk_164 = 0;
}

void func_8093BD4C(ObjSwitch* this, GlobalContext* globalCtx) {
    if ((func_8093BBD0(this) != 0) || ((this->dyna.actor.params >> 7) & 1)) {
        this->dyna.actor.params &= ~0x80;
        func_8093B648(this, globalCtx, func_8093BDAC, 1);
    }
}

void func_8093BDAC(ObjSwitch* this) {
    this->actionFunc = func_8093BDC0;
}

void func_8093BDC0(ObjSwitch* this, GlobalContext* globalCtx) {
    this->unk_164 += 1;
    if (this->unk_164 >= 3) {
        func_8093AE88(this);
        func_8093AEC4(this);
        func_8093BE10(this);
    }
}

void func_8093BE10(ObjSwitch* this) {
    this->actionFunc = func_8093BE2C;
    this->unk_164 = 3;
}

void func_8093BE2C(ObjSwitch* this, GlobalContext* globalCtx) {
    switch ((this->dyna.actor.params >> 4) & 7) {
        case 0:
            if (Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F) == 0) {
                this->dyna.actor.params &= ~0x80;
                func_8093BEF0(this);
                return;
            }
            return;
        case 1:
            if ((func_8093BBD0(this) != 0) || (((this->dyna.actor.params >> 7) & 1) != 0)) {
                this->dyna.actor.params &= ~0x80;
                func_8093B648(this, globalCtx, func_8093BEF0, 0);
            }
            break;
    }
}

void func_8093BEF0(ObjSwitch* this) {
    this->actionFunc = func_8093BF04;
}

void func_8093BF04(ObjSwitch* this, GlobalContext* globalCtx) {
    this->unk_164 += -1;
    if (this->unk_164 <= 0) {
        func_8093AE88(this);
        func_8093AEC4(this);
        func_8093BD34(this);
    }
}

void func_8093BF50(ObjSwitch* this) {
    this->unk_16C = 0;
    this->unk_16D = 0;
    this->unk_16E = 0;
    this->actionFunc = func_8093BF70;
}

void func_8093BF70(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 v0;
    s32 a2;

    // TODO: verify JntSph
    a2 = (this->colliderJntSph.base.acFlags & 2) != 0;
    v0 = a2 && !(this->unk_16F & 2) && (this->unk_162 < 1);
    if (a2) {
        this->unk_162 = 10;
    }
    switch ((this->dyna.actor.params >> 4) & 7) {
        case 0:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, 1);
            }
            break;
        case 4:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, 1);

            } else if (Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
                this->unk_162 = 10;
                func_8093C0A4(this);
            }
            break;
        case 1:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, 1);
            }
            func_8093AE74(this);
            break;
    }
}

void func_8093C0A4(ObjSwitch* this) {
    this->actionFunc = func_8093C0B8;
}

void func_8093C0B8(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 test;
    s32 sp20;

    test = (this->colliderJntSph.base.acFlags & 2) != 0;
    sp20 = (this->dyna.actor.params >> 4) & 7;
    if (test) {
        this->unk_162 = 10;
    }
    func_8093AE88(this);
    if (sp20 == 1) {
        func_8093AE74(this);
    }
    func_8093AEF0(this);
    func_8093C138(this);
}

void func_8093C138(ObjSwitch* this) {
    this->unk_16C = 0xFF;
    this->unk_16D = 0xFF;
    this->unk_16E = 0xFF;
    this->actionFunc = func_8093C15C;
}

void func_8093C15C(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 a2;
    s32 v0;

    // TODO: Verify JntSph
    a2 = (this->colliderJntSph.base.acFlags & 2) != 0;
    v0 = a2 && !(this->unk_16F & 2) && (this->unk_162 < 1);
    if (a2 != 0) {
        this->unk_162 = 10;
    }
    switch ((this->dyna.actor.params >> 4) & 7) {
        case 0:
        case 4:
            if (!Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
                this->unk_162 = 10;
                func_8093C23C(this);
            }
            break;
        case 1:
            if (v0 != 0) {
                func_8093B648(this, globalCtx, func_8093C23C, 0);
            }
    }
    func_8093AE74(this);
}

void func_8093C23C(ObjSwitch* this) {
    this->actionFunc = func_8093C250;
}

void func_8093C250(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 test = (this->colliderJntSph.base.acFlags & 2) != 0;
    if (test) {
        this->unk_162 = 10;
    }
    func_8093AE88(this);
    func_8093AE74(this);
    func_8093AEF0(this);
    func_8093BF50(this);
}

void func_8093C2B4(ObjSwitch* this) {
    this->dyna.actor.scale.y = 0.2475f;
    this->actionFunc = func_8093C2D4;
}

void func_8093C2D4(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 temp_v0 = ((s32)this->dyna.actor.params >> 4) & 7;

    if (temp_v0 == 0) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            func_8093AF1C(this, 1);
            func_8093B648(this, globalCtx, func_8093C3C8, 1);
        }
    } else if (temp_v0 == 2) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            func_8093AF1C(this, 1);
            func_8093B648(this, globalCtx, func_8093C3C8, 1);
        }
    } else if ((temp_v0 == 3) && DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
        func_8093AF1C(this, 2);
        func_8093AE1C(this, globalCtx, 0);
        func_8093C3C8(this);
    }
}

void func_8093C3C8(ObjSwitch* this) {
    this->actionFunc = func_8093C3DC;
}

void func_8093C3DC(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y -= 0.074250005f;
    if (this->dyna.actor.scale.y <= 0.0165f) {
        func_8093AEC4(this);
        func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        func_8093AE88(this);
        func_8093C460(this);
    }
}

void func_8093C460(ObjSwitch* this) {
    this->dyna.actor.scale.y = 0.0165f;
    this->unk_160 = 6;
    this->actionFunc = func_8093C488;
}

void func_8093C488(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 temp_v0 = (this->dyna.actor.params >> 4) & 7;

    if (temp_v0 == 0) {
        if (!Flags_GetSwitch(globalCtx, (this->dyna.actor.params >> 8) & 0x7F)) {
            func_8093C584(this);
        }
    } else if (temp_v0 == 2 || temp_v0 == 3) {
        if (!DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna) && !func_801233E4(globalCtx)) {
            if (this->unk_160 <= 0) {
                if (((this->dyna.actor.params >> 4) & 7) == 2) {
                    func_8093AE1C(this, globalCtx, 0);
                    func_8093C584(this);
                } else {
                    func_8093B648(this, globalCtx, func_8093C584, 1);
                }
            }
        } else {
            this->unk_160 = 6;
        }
    }
}

void func_8093C584(ObjSwitch* this) {
    this->actionFunc = func_8093C598;
}

void func_8093C598(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y += 0.074250005f;
    if (this->dyna.actor.scale.y >= 0.2475f) {
        func_8093AEC4(this);
        func_8093AE88(this);
        func_8093C2B4(this);
    }
}

#if 0
void ObjSwitch_Update(ObjSwitch* this, GlobalContext* globalCtx) {
    if (this->unk_160 > 0) {
        this->unk_160--;
    }
    if (this->unk_165 > 0) {
        this->unk_165--;
    }
    this->actionFunc(this, globalCtx);
    if (this->unk_170 != 0) {
        func_8093AF54(this, globalCtx);
        if (this->unk_170 == 2) {
            this->unk_170 = 0;
        }
    }
    switch (this->dyna.actor.params & 7) {
    case 0:
    case 1:
    case 5:
        this->unk_16F = this->dyna.stateFlags;
        break;
    case 2:
        this->unk_16F = this->colliderJntSph.base.acFlags;
        this->colliderJntSph.base.acFlags &= ~2;
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris);
        break;
    case 3:
    case 4:
        if (!func_801233E4(globalCtx)) {
            if (this->unk_162 > 0) {
                this->unk_162--;
            }
        }
        if (this->unk_162 == 0) {
            this->colliderJntSph.base.colType = D_8093CE08.base.colType;
        }
        else {
            this->colliderJntSph.base.colType = 0xA;
        }
        this->unk_16F = this->colliderJntSph.base.acFlags;
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Update.s")
#endif

#ifdef NON_MATCHING
void func_8093C778(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    if (ObjSwitch_Get_0070(this->dyna.actor.params) == 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, &sSetupDL[6 * 25]);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, this->unk_16C, this->unk_16D, this->unk_16E, 255);
        gSPDisplayList(POLY_OPA_DISP++, D_0501B508);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        func_800BDFC0(globalCtx, D_8093CE2C[ObjSwitch_Get_0070(this->dyna.actor.params)]);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C778.s")
#endif

void func_8093C888(ObjSwitch* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_05007E00);
}

void func_8093C8B8(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp28 = (this->dyna.actor.params >> 4) & 7;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_8093CC60[sp28][this->unk_164]);
    gSPDisplayList(POLY_OPA_DISP++, D_8093CE40[sp28]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_8093C99C(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp28 = (this->dyna.actor.params >> 4) & 7;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08, D_8093CC60[sp28][this->unk_164]);
    gSPDisplayList(POLY_XLU_DISP++, D_8093CE40[sp28]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_8093CA80(ObjSwitch* this, GlobalContext* globalCtx) {
    if ((this->dyna.actor.params >> 3) & 1) {
        func_8093C99C(this, globalCtx);
    } else {
        func_8093C8B8(this, globalCtx);
    }
}

void func_8093CAC4(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_800B8118(&this->dyna.actor, globalCtx, 0);
    AnimatedMat_DrawStep(globalCtx, D_8093D3B0, (u32)this->unk_168);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0501C058);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, this->unk_16C, this->unk_16D, this->unk_16E, 255);
    gSPDisplayList(POLY_OPA_DISP++, D_0501BEE0);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_0501BFB8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

extern ObjSwitchDrawFunc D_8093CE48[];

void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjSwitch* this = (ObjSwitch*)thisx;
    D_8093CE48[this->dyna.actor.params & 7](this, globalCtx);
}
