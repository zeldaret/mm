/*
 * File: z_obj_switch.c
 * Overlay: ovl_Obj_Switch
 * Description: Floor and Eye Switches
 */

#include "z_obj_switch.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjSwitch*)thisx)

#define COS_OF_5_PI_DIV_8 -0.38268343f

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjSwitch_FloorSwitchUpInit(ObjSwitch* this);
void ObjSwitch_FloorSwitchPushDownInit(ObjSwitch* this);
void ObjSwitch_FloorSwitchDownInit(ObjSwitch* this);
void ObjSwitch_FloorSwitchRiseUpInit(ObjSwitch* this);
void ObjSwitch_EyeSwitchFrozenInit(ObjSwitch* this);
void ObjSwitch_EyeSwitchOpenInit(ObjSwitch* this);
void ObjSwitch_EyeSwitchClosingInit(ObjSwitch* this);
void ObjSwitch_EyeSwitchClosedInit(ObjSwitch* this);
void ObjSwitch_EyeSwitchOpeningInit(ObjSwitch* this);
void ObjSwitch_CrystalSwitchOffInit(ObjSwitch* this);
void ObjSwitch_CrystalSwitchTurnOnInit(ObjSwitch* this);
void ObjSwitch_CrystalSwitchOnInit(ObjSwitch* this);
void ObjSwitch_CrystalSwitchTurnOffInit(ObjSwitch* this);
void ObjSwitch_LargeFloorSwitchUpInit(ObjSwitch* this);
void ObjSwitch_LargeFloorSwitchPushDownInit(ObjSwitch* this);
void ObjSwitch_LargeFloorSwitchDownInit(ObjSwitch* this);
void ObjSwitch_LargeFloorSwitchRiseUpInit(ObjSwitch* this);

void ObjSwitch_FloorSwitchSnapPlayerToSwitchEdge(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_TryPlayCutscene(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_FloorSwitchUp(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_FloorSwitchPushDown(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_FloorSwitchDown(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_FloorSwitchRiseUp(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_EyeSwitchUnfrozen(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_EyeSwitchOpen(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_EyeSwitchClosing(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_EyeSwitchClosed(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_EyeSwitchOpening(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_CrystalSwitchOff(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_CrystalSwitchTurnOn(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_CrystalSwitchOn(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_CrystalSwitchTurnOff(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_LargeFloorSwitchUp(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_LargeFloorSwitchPushDown(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_LargeFloorSwitchDown(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_LargeFloorSwitchRiseUp(ObjSwitch* this, GlobalContext* globalCtx);

void ObjSwitch_DrawFloorSwitch(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_DrawRustyFloorSwitch(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_DrawVisibleEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_DrawInvisibleEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_DrawEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx);
void ObjSwitch_DrawCrystalSwitch(ObjSwitch* this, GlobalContext* globalCtx);

static TexturePtr sEyeSwitchTextures[][4] = {
    { gEyeSwitchGoldOpenTex, gEyeSwitchGoldOpeningTex, gEyeSwitchGoldClosingTex, gEyeSwitchGoldClosedTex },
    { gEyeSwitchSilverOpenTex, gEyeSwitchSilverHalfTex, gEyeSwitchSilverClosedTex, gEyeSwitchSilverClosedTex },
};

static s32 sIsSegmentTableInit = false;

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

static f32 sHeights[] = { 10.0f, 10.0f, 0.0f, 30.0f, 30.0f, 15.0f };

static f32 sScale[] = { 0.123f, 0.123f, 0.1f, 0.118f, 0.118f, 0.248f };

static ColliderTrisElementInit sRustyFloorTrisElementsInit[2] = {
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

static ColliderTrisInit sRustyFloorTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sRustyFloorTrisElementsInit),
    sRustyFloorTrisElementsInit,
};

static ColliderTrisElementInit sEyeSwitchTrisElementsInit[2] = {
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

static ColliderTrisInit sEyeSwitchTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sEyeSwitchTrisElementsInit),
    sEyeSwitchTrisElementsInit,
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

static Color_RGB8 sSakonHideoutColor[2] = { { 250, 90, 60 }, { 255, 255, 255 } };

static Gfx* sFloorSwitchDL[] = { gFloorSwitch1DL, gFloorSwitch3DL, gFloorSwitch2DL, gFloorSwitch2DL, gFloorSwitch1DL };

static Gfx* sEyeSwitchDL[] = { gEyeSwitchGoldDL, gEyeSwitchSilverDL };

static AnimatedMaterial* sCrystalSwitchAnimatedMat;

void ObjSwitch_InitJntSphCollider(ObjSwitch* this, GlobalContext* globalCtx, ColliderJntSphInit* init) {
    s32 pad;

    Collider_InitJntSph(globalCtx, &this->colliderJntSph);
    Collider_SetJntSph(globalCtx, &this->colliderJntSph, &this->dyna.actor, init, this->colliderJntSphElements);
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x,
                                          this->dyna.actor.world.pos.y +
                                              (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y),
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->colliderJntSph);
}

void ObjSwitch_InitTrisCollider(ObjSwitch* this, GlobalContext* globalCtx, ColliderTrisInit* init) {
    s32 pad;
    s32 i;
    s32 j;
    Vec3f vtx[3];

    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->dyna.actor, init, this->colliderTrisElements);
    Matrix_StatePush();
    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x,
                                          this->dyna.actor.world.pos.y +
                                              this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y,
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (i = 0; i < ARRAY_COUNT(this->colliderTrisElements); i++) {
        if (this) {}
        for (j = 0; j < ARRAY_COUNT(vtx); j++) {
            Matrix_MultiplyVector3fByState(&init->elements[i].dim.vtx[j], &vtx[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &vtx[0], &vtx[1], &vtx[2]);
    }
    Matrix_StatePop();
}

Actor* ObjSwitch_SpawnIce(ObjSwitch* this, GlobalContext* globalCtx) {
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_OBJ_ICE_POLY,
                       this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y - 25.0f, this->dyna.actor.world.pos.z,
                       this->dyna.actor.world.rot.x, this->dyna.actor.world.rot.y, this->dyna.actor.world.rot.z,
                       0xFF32);
}

void ObjSwitch_SetSwitchFlagState(ObjSwitch* this, GlobalContext* globalCtx, s32 setFlag) {
    if (setFlag) {
        s32 flag = OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor);

        Flags_SetSwitch(globalCtx, flag);
    } else {
        s32 flag = OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor);

        Flags_UnsetSwitch(globalCtx, flag);
    }
}

void ObjSwitch_CrystalUpdateTimer(ObjSwitch* this) {
    this->crystalAnimTimer++;
}

void ObjSwitch_StopCutscene(ObjSwitch* this) {
    if (this->isPlayingCutscene) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->isPlayingCutscene = false;
    }
}

void ObjSwitch_PlayFootSwitchSfx(ObjSwitch* this) {
    if (this->sfxTimer <= 0) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FOOT_SWITCH);
    }
}

void ObjSwitch_PlayDiamondSwitchSfx(ObjSwitch* this) {
    if (this->sfxTimer <= 0) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_DIAMOND_SWITCH);
    }
}

void ObjSwitch_SetFloorSwitchSnapPlayerState(ObjSwitch* this, s32 state) {
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        this->floorSwitchPlayerSnapState = state;
    }
}

void ObjSwitch_FloorSwitchSnapPlayerToSwitchEdge(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player;
    f32 centerDisplacement;
    s16 yaw;
    f32 cos;

    if (globalCtx->actorCtx.unk5 & 0x80) {
        player = GET_PLAYER(globalCtx);
        // compute yawTowardsPlayer relative to model space
        yaw = BINANG_SUB(this->dyna.actor.yawTowardsPlayer, this->dyna.actor.shape.rot.y);

        // clamps yaw to the range -45 to 45 degrees, such that 0 degrees follows along the apothem
        yaw += 0x2000;
        yaw &= 0x3FFF;
        yaw -= 0x2000;

        // set centerDisplacement to the length of the apothem for the floor switch square
        // only OBJSWITCH_TYPE_FLOOR and OBJSWITCH_TYPE_FLOOR_LARGE are supported
        centerDisplacement = OBJ_SWITCH_GET_TYPE(&this->dyna.actor) == OBJSWITCH_TYPE_FLOOR ? 24.0f : 48.0f;

        cos = Math_CosS(yaw);
        if (fabsf(cos) > 0.01f) {
            // compute how far to displace the player so that the player is touching an edge
            centerDisplacement /= cos;
            // if the player is already inside the square, don't move them
            if (centerDisplacement < this->dyna.actor.xzDistToPlayer) {
                player->actor.world.pos.x =
                    Math_SinS(this->dyna.actor.yawTowardsPlayer) * centerDisplacement + this->dyna.actor.world.pos.x;
                player->actor.world.pos.z =
                    Math_CosS(this->dyna.actor.yawTowardsPlayer) * centerDisplacement + this->dyna.actor.world.pos.z;
            }
            player->linearVelocity = 0.0f;
        }
    }
}

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    s32 type;
    u32 isSwitchFlagSet;
    ObjSwitch* this = THIS;
    s32 pad2;

    isSwitchFlagSet = Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
    type = OBJ_SWITCH_GET_TYPE(&this->dyna.actor);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, sScale[type]);

    if (type == OBJSWITCH_TYPE_FLOOR || type == OBJSWITCH_TYPE_FLOOR_RUSTY || type == OBJSWITCH_TYPE_FLOOR_LARGE) {
        if (type == OBJSWITCH_TYPE_FLOOR_LARGE) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.9f;
        } else {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.0f;
        }
        DynaPolyActor_Init(&this->dyna, 1);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gFloorSwitchCol);
    }
    if (type == OBJSWITCH_TYPE_FLOOR) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            this->floorSwitchUpScale = 33.0f / 200.0f / 3.0f;
            this->floorSwitchDownScale = 33.0f / 2000.0f / 3.0f;
        } else {
            this->floorSwitchUpScale = 33.0f / 200.0f;
            this->floorSwitchDownScale = 33.0f / 2000.0f;
        }
    }
    if (type == OBJSWITCH_TYPE_FLOOR || type == OBJSWITCH_TYPE_FLOOR_LARGE) {
        if (globalCtx->sceneNum == SCENE_SECOM) {
            Color_RGB8* color = &sSakonHideoutColor[OBJ_SWITCH_GET_COLOR_ID(&this->dyna.actor)];

            this->color.r = color->r;
            this->color.g = color->g;
            this->color.b = color->b;
            this->dyna.actor.shape.rot.z = 0;
            this->dyna.actor.world.rot.z = 0;
        } else {
            this->color.r = 255;
            this->color.g = 255;
            this->color.b = 255;
        }
    }
    Actor_SetFocus(&this->dyna.actor, sHeights[type]);

    if (type == OBJSWITCH_TYPE_FLOOR_RUSTY) {
        ObjSwitch_InitTrisCollider(this, globalCtx, &sRustyFloorTrisInit);
    } else if (type == OBJSWITCH_TYPE_EYE) {
        ObjSwitch_InitTrisCollider(this, globalCtx, &sEyeSwitchTrisInit);
    } else if (type == OBJSWITCH_TYPE_CRYSTAL || type == OBJSWITCH_TYPE_CRYSTAL_TARGETABLE) {
        ObjSwitch_InitJntSphCollider(this, globalCtx, &sJntSphInit);
    }
    if (type == OBJSWITCH_TYPE_CRYSTAL_TARGETABLE) {
        this->dyna.actor.targetMode = 4;
        this->dyna.actor.flags |= 1;
    }
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    if (OBJ_SWITCH_IS_FROZEN(&this->dyna.actor)) {
        if (ObjSwitch_SpawnIce(this, globalCtx) == NULL) {
            OBJ_SWITCH_UNSET_FROZEN(&this->dyna.actor);
        }
        this->sfxTimer = 0;
    } else {
        this->sfxTimer = 10;
    }
    if (OBJ_SWITCH_IS_INVISIBLE(&this->dyna.actor)) {
        this->dyna.actor.flags |= 0x80;
    }
    if (type == OBJSWITCH_TYPE_EYE) {
        if (sIsSegmentTableInit == false) {
            s32 i, j;

            sIsSegmentTableInit = true;

            for (i = 0; i < ARRAY_COUNT(sEyeSwitchTextures); i++) {
                for (j = 0; j < ARRAY_COUNT(*sEyeSwitchTextures); j++) {
                    sEyeSwitchTextures[i][j] = Lib_SegmentedToVirtual(sEyeSwitchTextures[i][j]);
                }
            }
        }
    }
    if (type == OBJSWITCH_TYPE_CRYSTAL) {
        sCrystalSwitchAnimatedMat = Lib_SegmentedToVirtual(&gCrystalSwitchAnimatedMat);
    }
    if (OBJ_SWITCH_IS_FROZEN(&this->dyna.actor)) {
        ObjSwitch_EyeSwitchFrozenInit(this);
    } else if (type == OBJSWITCH_TYPE_FLOOR || type == OBJSWITCH_TYPE_FLOOR_RUSTY) {
        if (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor) == OBJSWITCH_SUBTYPE_RESET_INVERTED) {
            if (isSwitchFlagSet) {
                ObjSwitch_FloorSwitchUpInit(this);
            } else {
                ObjSwitch_FloorSwitchDownInit(this);
            }
        } else {
            if (isSwitchFlagSet) {
                ObjSwitch_FloorSwitchDownInit(this);
            } else {
                ObjSwitch_FloorSwitchUpInit(this);
            }
        }
    } else if (type == OBJSWITCH_TYPE_EYE) {
        if (isSwitchFlagSet) {
            ObjSwitch_EyeSwitchClosedInit(this);
        } else {
            ObjSwitch_EyeSwitchOpenInit(this);
        }
    } else if (type == OBJSWITCH_TYPE_CRYSTAL || type == OBJSWITCH_TYPE_CRYSTAL_TARGETABLE) {
        if (isSwitchFlagSet) {
            ObjSwitch_CrystalSwitchOnInit(this);
        } else {
            ObjSwitch_CrystalSwitchOffInit(this);
        }
    } else if (type == OBJSWITCH_TYPE_FLOOR_LARGE) {
        if (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor) == OBJSWITCH_SUBTYPE_RESET_INVERTED) {
            if (isSwitchFlagSet) {
                ObjSwitch_LargeFloorSwitchUpInit(this);
            } else {
                ObjSwitch_LargeFloorSwitchDownInit(this);
            }
        } else {
            if (isSwitchFlagSet) {
                ObjSwitch_LargeFloorSwitchDownInit(this);
            } else {
                ObjSwitch_LargeFloorSwitchUpInit(this);
            }
        }
    }
}

void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjSwitch* this = THIS;
    s32 type = OBJ_SWITCH_GET_TYPE(&this->dyna.actor);

    if (type == OBJSWITCH_TYPE_FLOOR || type == OBJSWITCH_TYPE_FLOOR_RUSTY || type == OBJSWITCH_TYPE_FLOOR_LARGE) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
    switch (type) {
        case OBJSWITCH_TYPE_FLOOR_RUSTY:
        case OBJSWITCH_TYPE_EYE:
            Collider_DestroyTris(globalCtx, &this->colliderTris);
            break;
        case OBJSWITCH_TYPE_CRYSTAL:
        case OBJSWITCH_TYPE_CRYSTAL_TARGETABLE:
            Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
            break;
    }
}

void ObjSwitch_TryPlayCutsceneInit(ObjSwitch* this, GlobalContext* globalCtx, ObjSwitchSetupActionFunc actionFunc,
                                   s32 nextSwitchFlagState) {
    this->setupFunc = actionFunc;
    this->nextSwitchFlagState = nextSwitchFlagState;
    this->actionFunc = ObjSwitch_TryPlayCutscene;
}

void ObjSwitch_TryPlayCutscene(ObjSwitch* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        ObjSwitch_SetSwitchFlagState(this, globalCtx, this->nextSwitchFlagState);
        if (this->floorSwitchPlayerSnapState == 1) {
            this->floorSwitchPlayerSnapState = 2;
        }
        this->isPlayingCutscene = true;
        this->setupFunc(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjSwitch_FloorSwitchUpInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_FloorSwitchUp;
    this->dyna.actor.scale.y = this->floorSwitchUpScale;
}

void ObjSwitch_FloorSwitchUp(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;

    if (OBJ_SWITCH_GET_TYPE(&this->dyna.actor) == OBJSWITCH_TYPE_FLOOR_RUSTY) {
        if (this->colliderTris.base.acFlags & AC_HIT) {
            this->colliderTris.base.acFlags &= ~AT_HIT;
            ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchPushDownInit, true);
        } else {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
        }
    } else {
        switch (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor)) {
            case OBJSWITCH_SUBTYPE_ONCE:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
                    ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchPushDownInit, true);
                }
                break;
            case OBJSWITCH_SUBTYPE_SYNC:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
                    ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchPushDownInit, true);
                } else if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
                    ObjSwitch_FloorSwitchPushDownInit(this);
                }
                break;
            case OBJSWITCH_SUBTYPE_TOGGLE:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    s32 isSwitchFlagNotSet =
                        Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor)) ? false : true;

                    ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
                    ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchPushDownInit,
                                                  isSwitchFlagNotSet);
                }
                break;
            case OBJSWITCH_SUBTYPE_RESET:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
                    ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchPushDownInit, true);
                }
                break;
            case OBJSWITCH_SUBTYPE_RESET_INVERTED:
                if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetFloorSwitchSnapPlayerState(this, 2);
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
                    ObjSwitch_FloorSwitchPushDownInit(this);
                }
                break;
        }
    }
}

void ObjSwitch_FloorSwitchPushDownInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_FloorSwitchPushDown;
}

void ObjSwitch_FloorSwitchPushDown(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y -= 0.0495f;
    if (this->dyna.actor.scale.y <= this->floorSwitchDownScale) {
        ObjSwitch_PlayFootSwitchSfx(this);
        func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        ObjSwitch_StopCutscene(this);
        ObjSwitch_FloorSwitchDownInit(this);
    }
}

void ObjSwitch_FloorSwitchDownInit(ObjSwitch* this) {
    this->floorSwitchReleaseTimer = 6;
    this->actionFunc = ObjSwitch_FloorSwitchDown;
    this->dyna.actor.scale.y = this->floorSwitchDownScale;
}

void ObjSwitch_FloorSwitchDown(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    u32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    switch (subType) {
        case OBJSWITCH_SUBTYPE_ONCE:
        case OBJSWITCH_SUBTYPE_SYNC:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
                if (globalCtx->sceneNum == SCENE_SECOM && DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, true);
                } else {
                    ObjSwitch_FloorSwitchRiseUpInit(this);
                }
            }
            break;
        case OBJSWITCH_SUBTYPE_TOGGLE:
        case OBJSWITCH_SUBTYPE_RESET:
        case OBJSWITCH_SUBTYPE_RESET_INVERTED:
            if (!DynaPolyActor_IsInSwitchPressedState(&this->dyna) &&
                (Player_InCsMode(&globalCtx->state) == 0 || globalCtx->sceneNum == SCENE_SECOM)) {
                if (this->floorSwitchReleaseTimer <= 0) {
                    if (subType == OBJSWITCH_SUBTYPE_RESET) {
                        ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
                        ObjSwitch_FloorSwitchRiseUpInit(this);
                    } else if (subType == OBJSWITCH_SUBTYPE_RESET_INVERTED) {
                        ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_FloorSwitchRiseUpInit, true);
                    } else {
                        ObjSwitch_FloorSwitchRiseUpInit(this);
                    }
                }
            } else {
                if (globalCtx->sceneNum == SCENE_SECOM) {
                    this->floorSwitchReleaseTimer = 2;
                } else {
                    this->floorSwitchReleaseTimer = 6;
                }
            }
            break;
    }
}

void ObjSwitch_FloorSwitchRiseUpInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_FloorSwitchRiseUp;
}

void ObjSwitch_FloorSwitchRiseUp(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y += 0.0495f;
    if (this->floorSwitchUpScale <= this->dyna.actor.scale.y) {
        ObjSwitch_PlayFootSwitchSfx(this);
        ObjSwitch_StopCutscene(this);
        ObjSwitch_FloorSwitchUpInit(this);
    }
}

s32 ObjSwitch_IsEyeSwitchHit(ObjSwitch* this) {
    Actor* acActor;
    Actor* actor = &this->dyna.actor;

    if ((this->colliderTris.base.acFlags & AC_HIT) && !(this->collisionFlags & AC_HIT)) {
        acActor = this->colliderTris.base.ac;
        if (acActor != NULL) {
            Vec3f sp2C;
            Vec3f sp20;

            Matrix_StatePush();
            Matrix_RotateY(acActor->world.rot.y, MTXMODE_NEW);
            Matrix_InsertXRotation_s(acActor->world.rot.x, MTXMODE_APPLY);
            Matrix_GetStateTranslationAndScaledZ(1.0f, &sp2C);
            Matrix_RotateY(actor->shape.rot.y, MTXMODE_NEW);
            Matrix_InsertXRotation_s(actor->shape.rot.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(actor->shape.rot.z, MTXMODE_APPLY);
            Matrix_GetStateTranslationAndScaledZ(1.0f, &sp20);
            Matrix_StatePop();
            if ((Math3D_Parallel(&sp2C, &sp20) < COS_OF_5_PI_DIV_8)) {
                return true;
            }
        }
    }
    return false;
}

void ObjSwitch_EyeSwitchFrozenInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_EyeSwitchUnfrozen;
}

void ObjSwitch_EyeSwitchUnfrozen(ObjSwitch* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
        ObjSwitch_EyeSwitchClosedInit(this);
    } else {
        ObjSwitch_EyeSwitchOpenInit(this);
    }
}

void ObjSwitch_EyeSwitchOpenInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_EyeSwitchOpen;
    this->eyeTexIndex = 0;
}

void ObjSwitch_EyeSwitchOpen(ObjSwitch* this, GlobalContext* globalCtx) {
    if (ObjSwitch_IsEyeSwitchHit(this) || OBJ_SWITCH_IS_FROZEN(&this->dyna.actor)) {
        OBJ_SWITCH_UNSET_FROZEN(&this->dyna.actor);
        ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_EyeSwitchClosingInit, true);
    }
}

void ObjSwitch_EyeSwitchClosingInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_EyeSwitchClosing;
}

void ObjSwitch_EyeSwitchClosing(ObjSwitch* this, GlobalContext* globalCtx) {
    this->eyeTexIndex++;
    if (this->eyeTexIndex >= 3) {
        ObjSwitch_StopCutscene(this);
        ObjSwitch_PlayFootSwitchSfx(this);
        ObjSwitch_EyeSwitchClosedInit(this);
    }
}

void ObjSwitch_EyeSwitchClosedInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_EyeSwitchClosed;
    this->eyeTexIndex = 3;
}

void ObjSwitch_EyeSwitchClosed(ObjSwitch* this, GlobalContext* globalCtx) {
    switch (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor)) {
        case OBJSWITCH_SUBTYPE_ONCE:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
                OBJ_SWITCH_UNSET_FROZEN(&this->dyna.actor);
                ObjSwitch_EyeSwitchOpeningInit(this);
            }
            break;
        case OBJSWITCH_SUBTYPE_TOGGLE:
            if (ObjSwitch_IsEyeSwitchHit(this) || OBJ_SWITCH_IS_FROZEN(&this->dyna.actor)) {
                OBJ_SWITCH_UNSET_FROZEN(&this->dyna.actor);
                ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_EyeSwitchOpeningInit, false);
            }
            break;
    }
}

void ObjSwitch_EyeSwitchOpeningInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_EyeSwitchOpening;
}

void ObjSwitch_EyeSwitchOpening(ObjSwitch* this, GlobalContext* globalCtx) {
    this->eyeTexIndex--;
    if (this->eyeTexIndex <= 0) {
        ObjSwitch_StopCutscene(this);
        ObjSwitch_PlayFootSwitchSfx(this);
        ObjSwitch_EyeSwitchOpenInit(this);
    }
}

void ObjSwitch_CrystalSwitchOffInit(ObjSwitch* this) {
    this->color.r = 0;
    this->color.g = 0;
    this->color.b = 0;
    this->actionFunc = ObjSwitch_CrystalSwitchOff;
}

void ObjSwitch_CrystalSwitchOff(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 switchHit = (this->colliderJntSph.base.acFlags & AC_HIT) != 0;
    s32 canActivate = switchHit && !(this->collisionFlags & AC_HIT) && (this->disableCrystalSwitchTimer <= 0);

    if (switchHit) {
        this->disableCrystalSwitchTimer = 10;
    }
    switch (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor)) {
        case OBJSWITCH_SUBTYPE_ONCE:
            if (canActivate) {
                ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_CrystalSwitchTurnOnInit, true);
            }
            break;
        case OBJSWITCH_SUBTYPE_SYNC:
            if (canActivate) {
                ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_CrystalSwitchTurnOnInit, true);

            } else if (Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
                this->disableCrystalSwitchTimer = 10;
                ObjSwitch_CrystalSwitchTurnOnInit(this);
            }
            break;
        case OBJSWITCH_SUBTYPE_TOGGLE:
            if (canActivate) {
                ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_CrystalSwitchTurnOnInit, true);
            }
            ObjSwitch_CrystalUpdateTimer(this);
            break;
    }
}

void ObjSwitch_CrystalSwitchTurnOnInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_CrystalSwitchTurnOn;
}

void ObjSwitch_CrystalSwitchTurnOn(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 switchHit = (this->colliderJntSph.base.acFlags & AC_HIT) != 0;
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    if (switchHit) {
        this->disableCrystalSwitchTimer = 10;
    }
    ObjSwitch_StopCutscene(this);
    if (subType == OBJSWITCH_SUBTYPE_TOGGLE) {
        ObjSwitch_CrystalUpdateTimer(this);
    }
    ObjSwitch_PlayDiamondSwitchSfx(this);
    ObjSwitch_CrystalSwitchOnInit(this);
}

void ObjSwitch_CrystalSwitchOnInit(ObjSwitch* this) {
    this->color.r = 255;
    this->color.g = 255;
    this->color.b = 255;
    this->actionFunc = ObjSwitch_CrystalSwitchOn;
}

void ObjSwitch_CrystalSwitchOn(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 switchHit = (this->colliderJntSph.base.acFlags & AC_HIT) != 0;
    s32 canActivate = switchHit && !(this->collisionFlags & AC_HIT) && (this->disableCrystalSwitchTimer <= 0);

    if (switchHit) {
        this->disableCrystalSwitchTimer = 10;
    }
    switch (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor)) {
        case OBJSWITCH_SUBTYPE_ONCE:
        case OBJSWITCH_SUBTYPE_SYNC:
            if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
                this->disableCrystalSwitchTimer = 10;
                ObjSwitch_CrystalSwitchTurnOffInit(this);
            }
            break;
        case OBJSWITCH_SUBTYPE_TOGGLE:
            if (canActivate) {
                ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_CrystalSwitchTurnOffInit, false);
            }
    }
    ObjSwitch_CrystalUpdateTimer(this);
}

void ObjSwitch_CrystalSwitchTurnOffInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_CrystalSwitchTurnOff;
}

void ObjSwitch_CrystalSwitchTurnOff(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 switchHit = (this->colliderJntSph.base.acFlags & AC_HIT) != 0;

    if (switchHit) {
        this->disableCrystalSwitchTimer = 10;
    }
    ObjSwitch_StopCutscene(this);
    ObjSwitch_CrystalUpdateTimer(this);
    ObjSwitch_PlayDiamondSwitchSfx(this);
    ObjSwitch_CrystalSwitchOffInit(this);
}

void ObjSwitch_LargeFloorSwitchUpInit(ObjSwitch* this) {
    this->dyna.actor.scale.y = 0.2475f;
    this->actionFunc = ObjSwitch_LargeFloorSwitchUp;
}

void ObjSwitch_LargeFloorSwitchUp(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    if (subType == OBJSWITCH_SUBTYPE_ONCE) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
            ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_LargeFloorSwitchPushDownInit, true);
        }
    } else if (subType == OBJSWITCH_SUBTYPE_RESET) {
        if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
            ObjSwitch_SetFloorSwitchSnapPlayerState(this, 1);
            ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_LargeFloorSwitchPushDownInit, true);
        }
    } else if (subType == OBJSWITCH_SUBTYPE_RESET_INVERTED && DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
        ObjSwitch_SetFloorSwitchSnapPlayerState(this, 2);
        ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
        ObjSwitch_LargeFloorSwitchPushDownInit(this);
    }
}

void ObjSwitch_LargeFloorSwitchPushDownInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_LargeFloorSwitchPushDown;
}

void ObjSwitch_LargeFloorSwitchPushDown(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y -= 0.074250005f;
    if (this->dyna.actor.scale.y <= 33.0f / 2000.0f) {
        ObjSwitch_PlayFootSwitchSfx(this);
        func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        ObjSwitch_StopCutscene(this);
        ObjSwitch_LargeFloorSwitchDownInit(this);
    }
}

void ObjSwitch_LargeFloorSwitchDownInit(ObjSwitch* this) {
    this->dyna.actor.scale.y = 33.0f / 2000.0f;
    this->floorSwitchReleaseTimer = 6;
    this->actionFunc = ObjSwitch_LargeFloorSwitchDown;
}

void ObjSwitch_LargeFloorSwitchDown(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    if (subType == OBJSWITCH_SUBTYPE_ONCE) {
        if (!Flags_GetSwitch(globalCtx, OBJ_SWITCH_GET_SWITCH_FLAG(&this->dyna.actor))) {
            ObjSwitch_LargeFloorSwitchRiseUpInit(this);
        }
    } else if (subType == OBJSWITCH_SUBTYPE_RESET || subType == OBJSWITCH_SUBTYPE_RESET_INVERTED) {
        if (!DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna) && !Player_InCsMode(&globalCtx->state)) {
            if (this->floorSwitchReleaseTimer <= 0) {
                if (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor) == OBJSWITCH_SUBTYPE_RESET) {
                    ObjSwitch_SetSwitchFlagState(this, globalCtx, false);
                    ObjSwitch_LargeFloorSwitchRiseUpInit(this);
                } else {
                    ObjSwitch_TryPlayCutsceneInit(this, globalCtx, ObjSwitch_LargeFloorSwitchRiseUpInit, true);
                }
            }
        } else {
            this->floorSwitchReleaseTimer = 6;
        }
    }
}

void ObjSwitch_LargeFloorSwitchRiseUpInit(ObjSwitch* this) {
    this->actionFunc = ObjSwitch_LargeFloorSwitchRiseUp;
}

void ObjSwitch_LargeFloorSwitchRiseUp(ObjSwitch* this, GlobalContext* globalCtx) {
    this->dyna.actor.scale.y += 0.074250005f;
    if (this->dyna.actor.scale.y >= 0.2475f) {
        ObjSwitch_PlayFootSwitchSfx(this);
        ObjSwitch_StopCutscene(this);
        ObjSwitch_LargeFloorSwitchUpInit(this);
    }
}

void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjSwitch* this = THIS;

    if (this->floorSwitchReleaseTimer > 0) {
        this->floorSwitchReleaseTimer--;
    }
    if (this->sfxTimer > 0) {
        this->sfxTimer--;
    }
    this->actionFunc(this, globalCtx);
    if (this->floorSwitchPlayerSnapState != 0) {
        s32 pad;

    dummy:
        ObjSwitch_FloorSwitchSnapPlayerToSwitchEdge(this, globalCtx);
        if (this->floorSwitchPlayerSnapState == 2) {
            this->floorSwitchPlayerSnapState = 0;
        }
    }
    switch (OBJ_SWITCH_GET_TYPE(&this->dyna.actor)) {
        case OBJSWITCH_TYPE_FLOOR:
        case OBJSWITCH_TYPE_FLOOR_RUSTY:
        case OBJSWITCH_TYPE_FLOOR_LARGE:
            this->collisionFlags = this->dyna.stateFlags;
            break;
        case OBJSWITCH_TYPE_EYE:
            this->collisionFlags = this->colliderTris.base.acFlags;
            this->colliderTris.base.acFlags &= ~AC_HIT;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
            break;
        case OBJSWITCH_TYPE_CRYSTAL:
        case OBJSWITCH_TYPE_CRYSTAL_TARGETABLE:
            if (!Player_InCsMode(&globalCtx->state)) {
                if (this->disableCrystalSwitchTimer > 0) {
                    this->disableCrystalSwitchTimer--;
                }
            }
            if (this->disableCrystalSwitchTimer == 0) {
                this->colliderJntSph.base.colType = sJntSphInit.base.colType;
            } else {
                this->colliderJntSph.base.colType = COLTYPE_NONE;
            }
            this->collisionFlags = this->colliderJntSph.base.acFlags;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }
}

void ObjSwitch_DrawFloorSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    if (OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor) == OBJSWITCH_SUBTYPE_ONCE) {
        Gfx* opa;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        opa = POLY_OPA_DISP;
        gSPDisplayList(opa++, &sSetupDL[6 * 25]);
        gSPMatrix(opa++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(opa++, 0, 0x80, this->color.r, this->color.g, this->color.b, 255);
        gSPDisplayList(opa++, gFloorSwitch1DL);
        POLY_OPA_DISP = opa;
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        Gfx_DrawDListOpa(globalCtx, sFloorSwitchDL[OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor)]);
    }
}

void ObjSwitch_DrawRustyFloorSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, gRustyFloorSwitchDL);
}

void ObjSwitch_DrawVisibleEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, sEyeSwitchTextures[subType][this->eyeTexIndex]);
    gSPDisplayList(POLY_OPA_DISP++, sEyeSwitchDL[subType]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjSwitch_DrawInvisibleEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 subType = OBJ_SWITCH_GET_SUBTYPE(&this->dyna.actor);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08, sEyeSwitchTextures[subType][this->eyeTexIndex]);
    gSPDisplayList(POLY_XLU_DISP++, sEyeSwitchDL[subType]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjSwitch_DrawEyeSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    if (OBJ_SWITCH_IS_INVISIBLE(&this->dyna.actor)) {
        ObjSwitch_DrawInvisibleEyeSwitch(this, globalCtx);
    } else {
        ObjSwitch_DrawVisibleEyeSwitch(this, globalCtx);
    }
}

void ObjSwitch_DrawCrystalSwitch(ObjSwitch* this, GlobalContext* globalCtx) {
    s32 pad[2];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_800B8118(&this->dyna.actor, globalCtx, 0);
    AnimatedMat_DrawStep(globalCtx, sCrystalSwitchAnimatedMat, this->crystalAnimTimer);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gCrystalSwitchBaseDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, this->color.r, this->color.g, this->color.b, 255);
    gSPDisplayList(POLY_OPA_DISP++, gCrystalSwitchCoreDL);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gCrystalSwitchDiamondDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static ObjSwitchDrawFunc drawFunc[] = {
        ObjSwitch_DrawFloorSwitch,   ObjSwitch_DrawRustyFloorSwitch, ObjSwitch_DrawEyeSwitch,
        ObjSwitch_DrawCrystalSwitch, ObjSwitch_DrawCrystalSwitch,    ObjSwitch_DrawFloorSwitch,
    };
    ObjSwitch* this = THIS;

    drawFunc[OBJ_SWITCH_GET_TYPE(&this->dyna.actor)](this, globalCtx);
}
