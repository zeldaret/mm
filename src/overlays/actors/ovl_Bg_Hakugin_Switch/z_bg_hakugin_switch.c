/*
 * File: z_bg_hakugin_switch.c
 * Overlay: ovl_Bg_Hakugin_Switch
 * Description: Goron Link Switch
 */

#include "z_bg_hakugin_switch.h"
#include "objects/object_goronswitch/object_goronswitch.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgHakuginSwitch*)thisx)

void BgHakuginSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B15A68(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15B1C(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15B74(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15E0C(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15E78(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15F3C(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B15F88(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B1606C(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B160DC(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B161A0(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B16244(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B162AC(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B163C4(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B16400(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B16494(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B16520(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B165A0(BgHakuginSwitch* this, GlobalContext* globalCtx);
void func_80B165E0(BgHakuginSwitch* this, GlobalContext* globalCtx);

u32 D_80B16AF0;

const ActorInit Bg_Hakugin_Switch_InitVars = {
    ACTOR_BG_HAKUGIN_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_GORONSWITCH,
    sizeof(BgHakuginSwitch),
    (ActorFunc)BgHakuginSwitch_Init,
    (ActorFunc)BgHakuginSwitch_Destroy,
    (ActorFunc)BgHakuginSwitch_Update,
    (ActorFunc)BgHakuginSwitch_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000400, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 60, 10, 180, { 0, 0, 0 } },
};

typedef struct {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ Gfx* unk_10;
    /* 0x14 */ u8 unk_14;
} BgHakuginSwitchStruct;

BgHakuginSwitchStruct D_80B1688C[] = {
    { -156.0f, -178.0f, 6.0f, 10.0f, object_goronswitch_DL_000268, 0xB4 },
    { -60.0f, -178.0f, 6.0f, 10.0f, object_goronswitch_DL_000268, 0x32 },
    { -60.0f, -178.0f, 6.0f, 10.0f, object_goronswitch_DL_000268, 0x31 },
    { -120.0f, -178.0f, 6.0f, 10.0f, object_goronswitch_DL_0007D8, 0x3A },
    { -156.0f, -178.0f, 6.0f, 10.0f, object_goronswitch_DL_0007D8, 0xB4 },
};

static InitChainEntry sInitChain1[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 130, ICHAIN_STOP),
};

static InitChainEntry sInitChain2[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 260, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 360, ICHAIN_STOP),
};

void func_80B15790(BgHakuginSwitch* this, u16 sfxId) {
    if (this->unk_1B2 <= 0) {
        Actor_PlaySfxAtPos(&this->dyna.actor, sfxId);
    }
}

void func_80B157C4(BgHakuginSwitch* this, u16 arg1) {
    if (this->unk_1B2 <= 0) {
        func_800B9010(&this->dyna.actor, arg1);
    }
}

void BgHakuginSwitch_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitch* this = THIS;
    s32 sp34 = BGHAKUGINSWITCH_GET_7(&this->dyna.actor);
    s32 sp30;
    s32 pad2;
    s32 sp28;

    if (Flags_GetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor))) {
        sp30 = true;
    } else {
        sp30 = false;
    }

    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_goronswitch_Colheader_0005C8);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);

    this->unk_1B2 = 15;
    if (!BGHAKUGINSWITCH_GET_10(&this->dyna.actor)) {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChain1);

        this->dyna.actor.scale.x = 0.07f;
        this->dyna.actor.scale.y = 0.016f;
        this->dyna.actor.scale.z = 0.07f;
        this->collider.dim.radius = 46;
        this->collider.dim.yShift = 0x1D;

        this->unk_1A8 = object_goronswitch_DL_000268;
        this->unk_1B8 = this->dyna.actor.cutscene;

        if (sp34 == 0) {
            this->unk_1BA = -1;
        } else {
            this->unk_1BA = ActorCutscene_GetAdditionalCutscene(this->unk_1B8);
        }

        if (sp30) {
            func_80B16494(this, globalCtx);
        } else {
            func_80B16244(this, globalCtx);
        }
    } else {
        if (D_80B1688C[sp34].unk_14 & 4) {
            sp28 = true;
        } else {
            sp28 = false;
        }

        Actor_ProcessInitChain(&this->dyna.actor, sInitChain2);

        this->unk_1A8 = D_80B1688C[sp34].unk_10;
        this->unk_1B8 = this->dyna.actor.cutscene;
        this->unk_1BA = ActorCutscene_GetAdditionalCutscene(this->unk_1B8);

        if (sp30 == sp28) {
            func_80B15F3C(this, globalCtx);
        } else {
            func_80B15B1C(this, globalCtx);
        }
    }

    this->unk_1C8 = 1.0f / this->dyna.actor.scale.y;
}

void BgHakuginSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgHakuginSwitch* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B15A4C(BgHakuginSwitch* this, BgHakuginSwitchUnkFunc func, s32 arg2) {
    this->unk_1B4 = func;
    this->unk_1BC = arg2;
    this->actionFunc = func_80B15A68;
}

void func_80B15A68(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitchStruct* s = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];
    s32 sp18 = !(s->unk_14 & 0x40);

    if (ActorCutscene_GetCanPlayNext(this->unk_1BC)) {
        if (sp18) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_1BC, &this->dyna.actor);
            this->unk_1BF = 40;
        }
        this->unk_1B4(this, globalCtx);
    } else if (sp18) {
        ActorCutscene_SetIntentToPlay(this->unk_1BC);
    }
}

void func_80B15B1C(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    BgHakuginSwitchStruct* s = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    this->dyna.actor.world.pos.y = s->unk_0 + this->dyna.actor.home.pos.y;
    this->unk_1C0 = 1;
    this->unk_1B0 = 480;
    this->actionFunc = func_80B15B74;
}

void func_80B15B74(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitchStruct* sp38 = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];
    s32 sp34 = (this->collider.base.acFlags & AC_HIT) != 0;
    s32 pad2;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;

    if (Flags_GetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor))) {
        sp2C = 1;
    } else {
        sp2C = 0;
    }

    if (sp38->unk_14 & 4) {
        sp28 = 1;
    } else {
        sp28 = 0;
    }

    sp24 = false;
    sp20 = -1;

    if (sp34) {
        this->collider.base.acFlags &= ~AC_HIT;
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            sp24 = true;
            sp20 = sp28;
        }
    }

    if (this->unk_1B0 > 0) {
        this->unk_1B0--;
        if (sp38->unk_14 & 8) {
            func_800B9038(&this->dyna.actor, this->unk_1B0);
            if (this->unk_1B0 == 0) {
                sp24 = true;
                sp20 = sp28;
            }
        }
    }

    if (sp2C == sp28) {
        if ((sp38->unk_14 & 0xFF) & 0x10) {
            if (D_80B16AF0 < globalCtx->gameplayFrames) {
                sp24 = true;
            }
        } else {
            sp24 = true;
        }
    }

    if (sp24) {
        if (sp20 == 1) {
            Flags_SetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor));
        } else if (sp20 == 0) {
            Flags_UnsetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor));
        }

        D_80B16AF0 = globalCtx->gameplayFrames;

        if (sp38->unk_14 & 0x10) {
            func_80B15A4C(this, func_80B15E0C, this->unk_1B8);
        } else {
            func_80B15E0C(this, globalCtx);
        }
    } else if (!(sp38->unk_14 & 1)) {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B15E0C(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    BgHakuginSwitchStruct* s = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    if ((s->unk_14 & 0x80)) {
        func_80B15790(this, NA_SE_EV_STONE_SWITCH_ON);
    }
    this->unk_1C0 = 0;
    this->actionFunc = func_80B15E78;
}

void func_80B15E78(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitchStruct* sp20 = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    if (Math_StepToF(&this->dyna.actor.world.pos.y, sp20->unk_4 + this->dyna.actor.home.pos.y, sp20->unk_C)) {
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        }
        func_80B15F3C(this, globalCtx);
    } else if (!(sp20->unk_14 & 0x80)) {
        func_80B157C4(this, NA_SE_EV_STONE_STATUE_OPEN - SFX_FLAG);
    }
}

void func_80B15F3C(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    BgHakuginSwitchStruct* s = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    this->dyna.actor.world.pos.y = s->unk_4 + this->dyna.actor.home.pos.y;
    this->unk_1C0 = 0;
    this->actionFunc = func_80B15F88;
}

void func_80B15F88(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 phi_a0;
    BgHakuginSwitchStruct* sp18 = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];
    s32 phi_v1;

    if (Flags_GetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor))) {
        phi_a0 = true;
    } else {
        phi_a0 = false;
    }

    if (sp18->unk_14 & 4) {
        phi_v1 = true;
    } else {
        phi_v1 = false;
    }

    if (phi_a0 != phi_v1) {
        if ((sp18->unk_14 & 0xFF) & 0x20) {
            if (D_80B16AF0 < globalCtx->gameplayFrames) {
                func_80B15A4C(this, func_80B1606C, this->unk_1BA);
            }
        } else {
            func_80B1606C(this, globalCtx);
        }
    }
}

void func_80B1606C(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    BgHakuginSwitchStruct* s = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    if (s->unk_14 & 0x80) {
        func_80B15790(this, NA_SE_EV_STONE_SWITCH_OFF);
    }
    this->unk_1C0 = 1;
    this->actionFunc = func_80B160DC;
}

void func_80B160DC(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitchStruct* sp18 = &D_80B1688C[BGHAKUGINSWITCH_GET_7(&this->dyna.actor)];

    if (Math_StepToF(&this->dyna.actor.world.pos.y, sp18->unk_0 + this->dyna.actor.home.pos.y, sp18->unk_8)) {
        func_80B15B1C(this, globalCtx);
    } else if (!(sp18->unk_14 & 0x80)) {
        func_80B157C4(this, NA_SE_EV_PILLAR_UP_FAST - SFX_FLAG);
    }
}

void func_80B16180(BgHakuginSwitch* this, BgHakuginSwitchUnkFunc func, s32 arg2, s32 arg3) {
    this->unk_1B4 = func;
    this->unk_1BE = arg2;
    this->unk_1BC = arg3;
    this->actionFunc = func_80B161A0;
}

void func_80B161A0(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_1BC)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_1BC, &this->dyna.actor);
        if (this->unk_1BE != 0) {
            Flags_SetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor));
        } else {
            Flags_UnsetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor));
        }
        this->unk_1BF = 50;
        this->unk_1B4(this, globalCtx);
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_1BC);
    }
}

void func_80B16244(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    this->unk_1C0 = 1;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
    if ((BGHAKUGINSWITCH_GET_7(&this->dyna.actor) == BGHAKUGINSWITCH_GET_7_1) &&
        (this->dyna.actor.category != ACTORCAT_SWITCH)) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 0);
    }
    this->actionFunc = func_80B162AC;
}

void func_80B162AC(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    s32 sp34 = (this->collider.base.acFlags & AC_HIT) != 0;
    s32 sp30 = BGHAKUGINSWITCH_GET_7(&this->dyna.actor);
    s32 pad;
    s32 sp28 = false;
    s32 sp24 = false;

    if (sp34) {
        this->collider.base.acFlags &= ~AC_HIT;
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            sp24 = true;
            sp28 = true;
        }
    }

    if (sp30 == 1) {
        if (Flags_GetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor))) {
            sp24 = true;
        }
    }

    if (sp24) {
        if (sp28) {
            func_80B16180(this, func_80B163C4, 1, this->unk_1B8);
        } else {
            func_80B163C4(this, globalCtx);
        }
    } else {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B163C4(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    func_80B15790(this, NA_SE_EV_STONE_SWITCH_ON);
    this->unk_1C0 = 0;
    this->actionFunc = func_80B16400;
}

void func_80B16400(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y,
                     (this->dyna.actor.home.pos.y + 2.0f) - (1800.0f * this->dyna.actor.scale.y), 10.0f)) {
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
        }
        func_80B16494(this, globalCtx);
    }
}

void func_80B16494(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    this->unk_1C0 = 0;
    this->dyna.actor.world.pos.y = (this->dyna.actor.home.pos.y - (1800.0f * this->dyna.actor.scale.y)) + 2.0f;
    if ((BGHAKUGINSWITCH_GET_7(&this->dyna.actor) == BGHAKUGINSWITCH_GET_7_1) &&
        (this->dyna.actor.category != ACTORCAT_PROP)) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, ACTORCAT_PROP);
    }
    this->actionFunc = func_80B16520;
}

void func_80B16520(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    if (!Flags_GetSwitch(globalCtx, BGHAKUGINSWITCH_GET_SWITCHFLAG(&this->dyna.actor))) {
        if (BGHAKUGINSWITCH_GET_7(&this->dyna.actor) == BGHAKUGINSWITCH_GET_7_1) {
            func_80B16180(this, func_80B165A0, 0, this->unk_1BA);
        } else {
            func_80B165A0(this, globalCtx);
        }
    }
}

void func_80B165A0(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    func_80B15790(this, NA_SE_EV_STONE_SWITCH_OFF);
    this->unk_1C0 = 1;
    this->actionFunc = func_80B165E0;
}

void func_80B165E0(BgHakuginSwitch* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 6.0f)) {
        func_80B16244(this, globalCtx);
    }
}

void BgHakuginSwitch_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgHakuginSwitch* this = THIS;
    f32 sp24;

    if (this->unk_1B2 > 0) {
        this->unk_1B2--;
    }

    if (this->unk_1BF > 0) {
        if ((this->actionFunc != func_80B15A68) && (this->actionFunc != func_80B161A0)) {
            this->unk_1BF--;
            if (this->unk_1BF == 0) {
                ActorCutscene_Stop(this->unk_1BC);
            }
        }
    }

    this->actionFunc(this, globalCtx);

    sp24 = this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y;

    if (this->unk_1C0 != 0) {
        f32 phi_f0;

        if (DynaPolyActor_IsInSwitchPressedState(&this->dyna)) {
            if (DynaPolyActor_IsInHeavySwitchPressedState(&this->dyna)) {
                phi_f0 = (sp24 - -10.0f) * -0.21f;
            } else {
                phi_f0 = (sp24 - -3.0f) * -0.08f;
            }
            this->unk_1C4 += phi_f0;
            this->unk_1C4 *= 0.75f;
            this->dyna.actor.shape.yOffset += this->unk_1C4 * this->unk_1C8;
        } else {
            this->unk_1C4 += sp24 * -0.11f;
            this->unk_1C4 *= 0.75f;
            this->dyna.actor.shape.yOffset += this->unk_1C4 * this->unk_1C8;
            this->dyna.actor.shape.yOffset = CLAMP_MAX(this->dyna.actor.shape.yOffset, 0.0f);
        }
    } else {
        Math_StepToF(&this->dyna.actor.shape.yOffset, 0.0f, 2.0f * this->unk_1C8);
        this->unk_1C4 = 0.0f;
    }
}

void BgHakuginSwitch_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgHakuginSwitch* this = THIS;

    Gfx_DrawDListOpa(globalCtx, this->unk_1A8);
}
