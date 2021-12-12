/*
 * File: z_obj_switch.c
 * Overlay: ovl_Obj_Switch
 * Description: Floor and Eye Switches
 */

#include "z_obj_switch.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwitch*)thisx)

#define COS_OF_5_PI_DIV_8 -0.38268343f

#define OBJ_SWITCH_GET_TYPE(p) ((p)&7)
#define OBJ_SWITCH_GET_SUBTYPE(p) (p >> 4 & 7)
#define OBJ_SWITCH_GET_SWITCH_FLAG(p) ((p) >> 8 & 0x7F)
#define OBJ_SWITCH_IS_FROZEN(p) ((p) >> 7 & 1)
#define OBJ_SWITCH_UNSET_FROZEN(p) ((p) &= ~(1 << 7))
#define OBJ_SWITCH_IS_3(p) ((p) >> 3 & 1)
#define OBJ_SWITCH_GET_COLOR_ID(z) ((z)&1)

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

extern CollisionHeader D_05008018;
extern Gfx D_0501BEE0[];
extern Gfx D_0501BFB8[];
extern AnimatedMaterial D_0501C118;

Gfx* D_8093CC60[2][4] = {
    { 0x0500AEC0, 0x05009EC0, 0x0500A6C0, 0x050096C0 },
    { 0x0500B6C0, 0x0500BEC0, 0x0500C6C0, 0x0500C6C0 },
};

s32 sIsSegmentTableInit = false;

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

f32 D_8093CCA4[] = { 10.0f, 10.0f, 0.0f, 30.0f, 30.0f, 15.0f };

f32 D_8093CCBC[] = { 0.123f, 0.123f, 0.1f, 0.118f, 0.118f, 0.248f };

static ColliderTrisElementInit sTrisElementsInit1[2] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000400, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, 20.0f } } },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000400, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, -20.0f } } },
    },
};

static ColliderTrisInit sTrisInit1 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sTrisElementsInit1),
    sTrisElementsInit1,
};

static ColliderTrisElementInit sTrisElementsInit2[2] = {
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

static ColliderTrisInit sTrisInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sTrisElementsInit2),
    sTrisElementsInit2,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x01CBFFBE, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 300, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

Color_RGB8 D_8093CE24[2] = { { 250, 90, 60 }, { 255, 255, 255 } };

Gfx* D_8093CE2C[] = { 0x0501B508, 0x0501B9F8, 0x0501B788, 0x0501B788, 0x0501B508 };

Gfx* D_8093CE40[] = { 0x050083F0, 0x050085F0 };

AnimatedMaterial* sAnimatedMat;

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

void func_8093AC6C(ObjSwitch* this, GlobalContext* globalCtx, ColliderTrisInit* init) {
    s32 pad;
    s32 s1;
    s32 s2;
    Vec3f vtx[3];

    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->dyna.actor, init, this->colliderTrisElements);
    Matrix_StatePush();
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x,
                                          this->dyna.actor.world.pos.y +
                                              this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y,
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (s2 = 0; s2 < ARRAY_COUNT(this->colliderTrisElements); s2++) {
        if (this) {}
        for (s1 = 0; s1 < ARRAY_COUNT(vtx); s1++) {
            Matrix_MultiplyVector3fByState(&init->elements[s2].dim.vtx[s1], &vtx[s1]);
        }
        Collider_SetTrisVertices(&this->colliderTris, s2, &vtx[0], &vtx[1], &vtx[2]);
    }
    Matrix_StatePop();
}

Actor* func_8093ADA8(ObjSwitch* this, GlobalContext* globalCtx) {
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_OBJ_ICE_POLY,
                       this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y - 25.0f, this->dyna.actor.world.pos.z,
                       this->dyna.actor.world.rot.x, this->dyna.actor.world.rot.y, this->dyna.actor.world.rot.z,
                       0xFF32);
}

void ObjSwitch_SetSwitchFlagState(ObjSwitch* this, GlobalContext* globalCtx, s32 setFlag) {
    if (setFlag) {
        s32 flag = OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params);
        Actor_SetSwitchFlag(globalCtx, flag);
    } else {
        s32 flag = OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params);
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
        sp24 = OBJ_SWITCH_GET_TYPE(this->dyna.actor.params) == 0 ? 24.0f : 48.0f;

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
    s32 type;
    u32 isSwitchFlagSet;
    ObjSwitch* this = (ObjSwitch*)thisx;
    s32 pad2;

    isSwitchFlagSet = Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params));
    type = OBJ_SWITCH_GET_TYPE(this->dyna.actor.params);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, D_8093CCBC[type]);

    if (type == 0 || type == 1 || type == 5) {
        if (type == 5) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.9f;
        } else {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.0f;
        }
        DynaPolyActor_Init(&this->dyna, 1);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_05008018);
    }
    if (type == 0) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            this->unk_250 = 0.055000003f;
            this->unk_254 = 0.0055f;
        } else {
            this->unk_250 = 0.165f;
            this->unk_254 = 0.0165f;
        }
    }
    if (type == 0 || type == 5) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            Color_RGB8* color = &D_8093CE24[OBJ_SWITCH_GET_COLOR_ID(this->dyna.actor.home.rot.z)];

            this->unk_16C = color->r;
            this->unk_16D = color->g;
            this->unk_16E = color->b;
            this->dyna.actor.shape.rot.z = 0;
            this->dyna.actor.world.rot.z = 0;
        } else {
            this->unk_16C = 255;
            this->unk_16D = 255;
            this->unk_16E = 255;
        }
    }
    Actor_SetHeight(&this->dyna.actor, D_8093CCA4[type]);

    if (type == 1) {
        func_8093AC6C(this, globalCtx, &sTrisInit1);
    } else if (type == 2) {
        func_8093AC6C(this, globalCtx, &sTrisInit2);
    } else if (type == 3 || type == 4) {
        func_8093ABD0(this, globalCtx, &sJntSphInit);
    }
    if (type == 4) {
        this->dyna.actor.targetMode = 4;
        this->dyna.actor.flags |= 1;
    }
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    if (OBJ_SWITCH_IS_FROZEN(this->dyna.actor.params)) {
        if (func_8093ADA8(this, globalCtx) == NULL) {
            OBJ_SWITCH_UNSET_FROZEN(this->dyna.actor.params);
        }
        this->unk_165 = 0;
    } else {
        this->unk_165 = 10;
    }
    if (OBJ_SWITCH_IS_3(this->dyna.actor.params)) {
        this->dyna.actor.flags |= 0x80;
    }
    if (type == 2) {
        if (sIsSegmentTableInit == false) {
            s32 i, j;
            sIsSegmentTableInit = true;

            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j++) {
                    D_8093CC60[i][j] = Lib_SegmentedToVirtual(D_8093CC60[i][j]);
                }
            }
        }
    }
    if (type == 3) {
        sAnimatedMat = Lib_SegmentedToVirtual(&D_0501C118);
    }
    if (OBJ_SWITCH_IS_FROZEN(this->dyna.actor.params)) {
        func_8093BCC8(this);
    } else if (type == 0 || type == 1) {
        if (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params) == 3) {
            if (isSwitchFlagSet) {
                func_8093B6F4(this);
            } else {
                func_8093B9C0(this);
            }
        } else if (isSwitchFlagSet) {
            func_8093B9C0(this);
        } else {
            func_8093B6F4(this);
        }
    } else if (type == 2) {
        if (isSwitchFlagSet) {
            func_8093BE10(this);
        } else {
            func_8093BD34(this);
        }
    } else if (type == 3 || type == 4) {
        if (isSwitchFlagSet) {
            func_8093C138(this);
        } else {
            func_8093BF50(this);
        }
    } else if (type == 5) {
        if (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params) == 3) {
            if (isSwitchFlagSet) {
                func_8093C2B4(this);
            } else {
                func_8093C460(this);
            }
        } else if (isSwitchFlagSet) {
            func_8093C460(this);
        } else {
            func_8093C2B4(this);
        }
    }
}

void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjSwitch* this = (ObjSwitch*)thisx;
    s32 type = OBJ_SWITCH_GET_TYPE(this->dyna.actor.params);

    if (type == 0 || type == 1 || type == 5) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
    switch (type) {
        case 1:
        case 2:
            Collider_DestroyTris(globalCtx, &this->colliderTris);
            break;
        case 3:
        case 4:
            Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
            break;
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
        ObjSwitch_SetSwitchFlagState(this, globalCtx, this->unk_171);
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

void func_8093B710(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;

    if (OBJ_SWITCH_GET_TYPE(this->dyna.actor.params) == 1) {
        if (this->colliderTris.base.acFlags & 2) {
            this->colliderTris.base.acFlags &= ~AT_HIT;
            func_8093B648(this, globalCtx, func_8093B92C, true);
        } else {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
        }
    } else {
        switch (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params)) {
            case 0:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, true);
                }
                break;
            case 4:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, true);
                } else if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
                    func_8093B92C(this);
                }
                break;
            case 1:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    s32 isSwitchFlagNotSet =
                        Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params)) ? false : true;

                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, isSwitchFlagNotSet);
                }
                break;
            case 2:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 1);
                    func_8093B648(this, globalCtx, func_8093B92C, true);
                }
                break;
            case 3:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    func_8093AF1C(this, 2);
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
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
    u32 subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);

    switch (subType) {
        case 0:
        case 4:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
                if (globalCtx->sceneNum == SCENE_SECOM && DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, true);
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
                    if (subType == 2) {
                        ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
                        func_8093BB5C(this);
                    } else if (subType == 3) {
                        func_8093B648(this, globalCtx, func_8093BB5C, true);
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

    if ((this->colliderTris.base.acFlags & 2) && !(this->unk_16F & 2)) {
        acActor = this->colliderTris.base.ac;
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
    if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
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
    if (func_8093BBD0(this) || OBJ_SWITCH_IS_FROZEN(this->dyna.actor.params)) {
        OBJ_SWITCH_UNSET_FROZEN(this->dyna.actor.params);
        func_8093B648(this, globalCtx, func_8093BDAC, true);
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
    switch (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params)) {
        case 0:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
                OBJ_SWITCH_UNSET_FROZEN(this->dyna.actor.params);
                func_8093BEF0(this);
            }
            break;
        case 1:
            if (func_8093BBD0(this) || OBJ_SWITCH_IS_FROZEN(this->dyna.actor.params)) {
                OBJ_SWITCH_UNSET_FROZEN(this->dyna.actor.params);
                func_8093B648(this, globalCtx, func_8093BEF0, false);
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

    a2 = (this->colliderJntSph.base.acFlags & 2) != 0;
    v0 = a2 && !(this->unk_16F & 2) && (this->unk_162 < 1);
    if (a2) {
        this->unk_162 = 10;
    }
    switch (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params)) {
        case 0:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, true);
            }
            break;
        case 4:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, true);

            } else if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
                this->unk_162 = 10;
                func_8093C0A4(this);
            }
            break;
        case 1:
            if (v0) {
                func_8093B648(this, globalCtx, func_8093C0A4, true);
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
    s32 subType;

    test = (this->colliderJntSph.base.acFlags & 2) != 0;
    subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);
    if (test) {
        this->unk_162 = 10;
    }
    func_8093AE88(this);
    if (subType == 1) {
        func_8093AE74(this);
    }
    func_8093AEF0(this);
    func_8093C138(this);
}

void func_8093C138(ObjSwitch* this) {
    this->unk_16C = 255;
    this->unk_16D = 255;
    this->unk_16E = 255;
    this->actionFunc = func_8093C15C;
}

void func_8093C15C(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 a2;
    s32 v0;

    a2 = (this->colliderJntSph.base.acFlags & 2) != 0;
    v0 = a2 && !(this->unk_16F & 2) && (this->unk_162 < 1);
    if (a2 != 0) {
        this->unk_162 = 10;
    }
    switch (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params)) {
        case 0:
        case 4:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
                this->unk_162 = 10;
                func_8093C23C(this);
            }
            break;
        case 1:
            if (v0 != 0) {
                func_8093B648(this, globalCtx, func_8093C23C, false);
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
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);

    if (subType == 0) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            func_8093AF1C(this, 1);
            func_8093B648(this, globalCtx, func_8093C3C8, true);
        }
    } else if (subType == 2) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            func_8093AF1C(this, 1);
            func_8093B648(this, globalCtx, func_8093C3C8, true);
        }
    } else if ((subType == 3) && DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
        func_8093AF1C(this, 2);
        ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
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
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);

    if (subType == 0) {
        if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(this->dyna.actor.params))) {
            func_8093C584(this);
        }
    } else if (subType == 2 || subType == 3) {
        if (!DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna) && !func_801233E4(globalCtx)) {
            if (this->unk_160 <= 0) {
                if (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params) == 2) {
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
                    func_8093C584(this);
                } else {
                    func_8093B648(this, globalCtx, func_8093C584, true);
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

void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjSwitch* this = (ObjSwitch*)thisx;

    if (this->unk_160 > 0) {
        this->unk_160--;
    }
    if (this->unk_165 > 0) {
        this->unk_165--;
    }
    this->actionFunc(this, globalCtx);
    if (this->unk_170 != 0) {
        s32 pad;

    dummy:
        func_8093AF54(this, globalCtx);
        if (this->unk_170 == 2) {
            this->unk_170 = 0;
        }
    }
    switch (OBJ_SWITCH_GET_TYPE(this->dyna.actor.params)) {
        case 0:
        case 1:
        case 5:
            this->unk_16F = this->dyna.stateFlags;
            break;
        case 2:
            this->unk_16F = this->colliderTris.base.acFlags;
            this->colliderTris.base.acFlags &= ~2;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
            break;
        case 3:
        case 4:
            if (!func_801233E4(globalCtx)) {
                if (this->unk_162 > 0) {
                    this->unk_162--;
                }
            }
            if (this->unk_162 == 0) {
                this->colliderJntSph.base.colType = sJntSphInit.base.colType;
            } else {
                this->colliderJntSph.base.colType = COLTYPE_NONE;
            }
            this->unk_16F = this->colliderJntSph.base.acFlags;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }
}

void func_8093C778(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    if (OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params) == 0) {
        Gfx* opa;
        OPEN_DISPS(globalCtx->state.gfxCtx);
        opa = POLY_OPA_DISP;
        gSPDisplayList(opa++, &sSetupDL[6 * 25]);
        gSPMatrix(opa++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(opa++, 0, 0x80, this->unk_16C, this->unk_16D, this->unk_16E, 255);
        gSPDisplayList(opa++, D_0501B508);
        POLY_OPA_DISP = opa;
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        func_800BDFC0(globalCtx, D_8093CE2C[OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params)]);
    }
}

void func_8093C888(ObjSwitch* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_05007E00);
}

void func_8093C8B8(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_8093CC60[subType][this->unk_164]);
    gSPDisplayList(POLY_OPA_DISP++, D_8093CE40[subType]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_8093C99C(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(this->dyna.actor.params);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08, D_8093CC60[subType][this->unk_164]);
    gSPDisplayList(POLY_XLU_DISP++, D_8093CE40[subType]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_8093CA80(ObjSwitch* this, GlobalContext* globalCtx) {
    if (OBJ_SWITCH_IS_3(this->dyna.actor.params)) {
        func_8093C99C(this, globalCtx);
    } else {
        func_8093C8B8(this, globalCtx);
    }
}

void func_8093CAC4(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_800B8118(&this->dyna.actor, globalCtx, 0);
    AnimatedMat_DrawStep(globalCtx, sAnimatedMat, this->unk_168);
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

void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static ObjSwitchDrawFunc drawFunc[] = { func_8093C778, func_8093C888, func_8093CA80,
                                            func_8093CAC4, func_8093CAC4, func_8093C778 };
    ObjSwitch* this = (ObjSwitch*)thisx;

    drawFunc[OBJ_SWITCH_GET_TYPE(this->dyna.actor.params)](this, globalCtx);
}
