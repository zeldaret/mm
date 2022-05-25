/*
 * File: z_en_horse_game_check.c
 * Overlay: ovl_En_Horse_Game_Check
 * Description: Dirt patches you can jump over on Gorman Race Track
 */

#include "z_en_horse_game_check.h"
#include "objects/object_horse_game_check/object_horse_game_check.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnHorseGameCheck*)thisx)

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_808F8AA0(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F8C24(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F8C5C(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F8C70(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F8CCC(EnHorseGameCheck* this, GlobalContext* globalCtx2);
s32 func_808F8E94(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F8FAC(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F96E4(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F9830(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F9868(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F987C(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F990C(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F9944(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F9958(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F999C(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F99B0(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F99C4(EnHorseGameCheck* this, GlobalContext* globalCtx);
s32 func_808F99D8(EnHorseGameCheck* this, GlobalContext* globalCtx);

const ActorInit En_Horse_Game_Check_InitVars = {
    ACTOR_EN_HORSE_GAME_CHECK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_GAME_CHECK,
    sizeof(EnHorseGameCheck),
    (ActorFunc)EnHorseGameCheck_Init,
    (ActorFunc)EnHorseGameCheck_Destroy,
    (ActorFunc)EnHorseGameCheck_Update,
    (ActorFunc)EnHorseGameCheck_Draw,
};

#include "overlays/ovl_En_Horse_Game_Check/ovl_En_Horse_Game_Check.c"

s32 func_808F8AA0(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    s32 pad[3];
    CollisionHeader* sp78 = NULL;
    MtxF sp38;

    this->dyna.actor.scale.x = this->dyna.actor.scale.y = this->dyna.actor.scale.z = this->unk_160 * 0.001f;
    this->dyna.actor.flags |= ACTOR_FLAG_400000;

    DynaPolyActor_Init(&this->dyna, 0);

    if (GET_RACE_FLAGS != RACE_FLAG_START) {
        Actor_MarkForDeath(&this->dyna.actor);
        return false;
    }

    CollisionHeader_GetVirtual(&object_horse_game_check_Colheader_003918, &sp78);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp78);
    this->unk_15C = ENHORSEGAMECHECK_FF_5;
    this->dyna.actor.floorPoly = NULL;
    this->dyna.actor.world.pos.y += 100.0f;

    this->dyna.actor.floorHeight = BgCheck_EntityRaycastFloor2(
        globalCtx, &globalCtx->colCtx, &this->dyna.actor.floorPoly, &this->dyna.actor.world.pos);
    this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight + 3.0f;
    func_800C0094(this->dyna.actor.floorPoly, this->dyna.actor.world.pos.x, this->dyna.actor.floorHeight,
                  this->dyna.actor.world.pos.z, &sp38);

    Matrix_SetCurrentState(&sp38);
    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.y, MTXMODE_APPLY);
    Matrix_CopyCurrentState(&sp38);

    func_8018219C(&sp38, &this->dyna.actor.shape.rot, 1);
    this->dyna.actor.world.rot = this->dyna.actor.shape.rot;
    return true;
}

s32 func_808F8C24(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    return true;
}

s32 func_808F8C5C(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_808F8C70(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    if (Matrix_NewMtx(globalCtx->state.gfxCtx) == NULL) {
        return true;
    } else {
        Gfx_DrawDListXlu(globalCtx, object_horse_game_check_DL_003030);
        Gfx_DrawDListOpa(globalCtx, object_horse_game_check_DL_0030C0);
    }
    return true;
}

s32 func_808F8CCC(EnHorseGameCheck* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;
    Vec3f sp4C = { -1262.0f, 15.0f, 780.0f };
    Vec3f sp40 = { -1262.0f, -26.0f, 470.0f };

    this->unk_164 = 0;
    this->unk_168 = 0;
    this->unk_174 = 0;

    if (GET_RACE_FLAGS != RACE_FLAG_START) {
        Actor_MarkForDeath(&this->dyna.actor);
        return false;
    }

    func_8010E9F0(4, 0);
    globalCtx->interfaceCtx.unk_280 = 1;

    this->horse1 = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, -1149.0f, -106.0f, 470.0f, 0,
                                         0x7FFF, 0, 0x2004);
    if (this->horse1 == NULL) {
        __assert("../z_en_horse_game_check.c", 1517);
    }

    this->horse2 = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, -1376.0f, -106.0f, 470.0f, 0,
                                         0x7FFF, 0, 0x2005);
    if (this->horse2 == NULL) {
        __assert("../z_en_horse_game_check.c", 1526);
    }

    this->unk_17C = -1;
    func_800DFAC8(globalCtx->cameraPtrs[CAM_ID_MAIN], 10);
    Play_CameraSetAtEye(globalCtx, 0, &sp40, &sp4C);
    Play_CameraSetFov(globalCtx, 0, 45.0f);
    func_800FE484();
    return false;
}

s32 func_808F8E94(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3DD0[4] = 0;
    return true;
}

s32 func_808F8EB0(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->nextEntranceIndex == 0xCE20) {
        return false;
    }

    if (GET_RACE_FLAGS == RACE_FLAG_3) {
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 2;
    } else if (GET_RACE_FLAGS == RACE_FLAG_2) {
        globalCtx->unk_1887F = 0x50;
        gSaveContext.nextTransition = 3;
    } else if (GET_RACE_FLAGS == RACE_FLAG_4) {
        SET_RACE_FLAGS(RACE_FLAG_3);
        globalCtx->unk_1887F = 2;
        gSaveContext.nextTransition = 2;
    }

    D_801BDA9C = 0;
    if (player->stateFlags1 & 0x800000) {
        D_801BDAA0 = 1;
    }
    globalCtx->nextEntranceIndex = 0xCE20;
    globalCtx->sceneLoadFlag = 0x14;
    return false;
}

f32 D_808F9BAC[] = {
    -1825.0f,
    -237.0f,
    -2867.0f,
    -1987.0f,
};

f32 D_808F9BBC[] = {
    1564.0f,
    3395.0f,
    -1665.0f,
    -200.0f,
};

f32 D_808F9BCC[] = {
    -22.0f,
    2005.0f,
    3869.0f,
    5368.0f,
};

s32 func_808F8FAC(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Player* player = GET_PLAYER(globalCtx);
    s32 pad2;
    EnHorse* horse = (EnHorse*)player->rideActor;
    s32 pad3[2];
    EnHorseGameCheck* horseGameCheck;

    if (horse == NULL) {
        return true;
    }

    if ((this->unk_168 > 50) && !(this->unk_164 & 2)) {
        this->unk_164 |= 2;
    } else if ((globalCtx->interfaceCtx.unk_280 >= 8) && !(this->unk_164 & 1)) {
        this->unk_164 |= 1;
        horse->inRace = true;
    } else if ((globalCtx->interfaceCtx.unk_280 >= 8) && !(this->unk_164 & 8)) {
        EnHorse* horse = this->horse1;

        horse->inRace = true;
        horse = this->horse2;
        horse->inRace = true;

        this->unk_164 |= 8;
        this->unk_17C = this->unk_168;
    }

    if ((this->unk_17C != -1) && ((this->unk_168 - this->unk_17C) > 10)) {
        this->unk_17C = -1;
        func_800DFAC8(globalCtx->cameraPtrs[CAM_ID_MAIN], 4);
    }

    this->unk_168++;
    if ((this->unk_164 & 0x4000) && (this->unk_164 & 0x200000)) {
        if (!(this->unk_164 & 0x10)) {
            this->unk_164 |= 0x10;
        }
    }

    if ((this->unk_164 & 0x800) || (this->unk_164 & 0x40000) || (this->unk_164 & 0x02000000)) {
        if (this->unk_174 > 0) {
            this->unk_174--;
        } else {
            func_808F8EB0(this, globalCtx);
        }
        return true;
    }

    if (gSaveContext.unk_3DE0[4] >= 0x4650) {
        Audio_QueueSeqCmd(0x8041);
        play_sound(NA_SE_SY_START_SHOT);
        this->unk_164 |= 0x40000;
        gSaveContext.unk_3DD0[4] = 6;
        SET_RACE_FLAGS(RACE_FLAG_4)
        this->unk_174 = 60;
    }

    if (!(this->unk_164 & 0x1000)) {
        if (Math3D_XZBoundCheck(D_808F9BAC[0], D_808F9BAC[1], D_808F9BAC[2], D_808F9BAC[3],
                                this->horse1->actor.world.pos.x, this->horse1->actor.world.pos.z)) {
            this->unk_164 |= 0x1000;
        }
    }

    if (!(this->unk_164 & 0x2000) && (this->unk_164 & 0x1000)) {
        if (Math3D_XZBoundCheck(D_808F9BBC[0], D_808F9BBC[1], D_808F9BBC[2], D_808F9BBC[3],
                                this->horse1->actor.world.pos.x, this->horse1->actor.world.pos.z)) {
            this->unk_164 |= 0x2000;
        }
    }

    if (!(this->unk_164 & 0x4000) && (this->unk_164 & 0x2000)) {
        if (Math3D_XZBoundCheck(D_808F9BCC[0], D_808F9BCC[1], D_808F9BCC[2], D_808F9BCC[3],
                                this->horse1->actor.world.pos.x, this->horse1->actor.world.pos.z)) {
            this->unk_164 |= 0x4000;
        }
    }

    horseGameCheck = (EnHorseGameCheck*)DynaPoly_GetActor(&globalCtx->colCtx, this->horse1->unk_24C);
    if ((this->unk_164 & 0x4000) && (horseGameCheck != NULL) &&
        (horseGameCheck->dyna.actor.id == ACTOR_EN_HORSE_GAME_CHECK) &&
        (horseGameCheck->unk_15C == ENHORSEGAMECHECK_FF_7) && !(this->unk_164 & 0x40000)) {
        Audio_QueueSeqCmd(0x8041);
        play_sound(NA_SE_SY_START_SHOT);
        this->unk_164 |= 0x40000;
        gSaveContext.unk_3DD0[4] = 6;
        SET_RACE_FLAGS(RACE_FLAG_3)
        this->unk_174 = 60;
    }

    if (!(this->unk_164 & 0x80000)) {
        if (Math3D_XZBoundCheck(D_808F9BAC[0], D_808F9BAC[1], D_808F9BAC[2], D_808F9BAC[3],
                                this->horse2->actor.world.pos.x, this->horse2->actor.world.pos.z)) {
            this->unk_164 |= 0x80000;
        }
    }

    if (!(this->unk_164 & 0x100000) && (this->unk_164 & 0x80000)) {
        if (Math3D_XZBoundCheck(D_808F9BBC[0], D_808F9BBC[1], D_808F9BBC[2], D_808F9BBC[3],
                                this->horse2->actor.world.pos.x, this->horse2->actor.world.pos.z)) {
            this->unk_164 |= 0x100000;
        }
    }

    if (!(this->unk_164 & 0x200000) && (this->unk_164 & 0x100000)) {
        if (Math3D_XZBoundCheck(D_808F9BCC[0], D_808F9BCC[1], D_808F9BCC[2], D_808F9BCC[3],
                                this->horse2->actor.world.pos.x, this->horse2->actor.world.pos.z)) {
            this->unk_164 |= 0x200000;
        }
    }

    horseGameCheck = (EnHorseGameCheck*)DynaPoly_GetActor(&globalCtx->colCtx, this->horse2->unk_24C);
    if ((this->unk_164 & 0x200000) && (horseGameCheck != NULL) &&
        (horseGameCheck->dyna.actor.id == ACTOR_EN_HORSE_GAME_CHECK) &&
        (horseGameCheck->unk_15C == ENHORSEGAMECHECK_FF_7) && !(this->unk_164 & 0x02000000)) {
        Audio_QueueSeqCmd(0x8041);
        play_sound(NA_SE_SY_START_SHOT);
        this->unk_164 |= 0x02000000;
        gSaveContext.unk_3DD0[4] = 6;
        SET_RACE_FLAGS(RACE_FLAG_3)
        this->unk_174 = 60;
    }

    if (!(this->unk_164 & 0x20) && Math3D_XZBoundCheck(D_808F9BAC[0], D_808F9BAC[1], D_808F9BAC[2], D_808F9BAC[3],
                                                       horse->actor.world.pos.x, horse->actor.world.pos.z)) {
        this->unk_164 |= 0x20;
    }

    if (!(this->unk_164 & 0x40) && (this->unk_164 & 0x20) &&
        Math3D_XZBoundCheck(D_808F9BBC[0], D_808F9BBC[1], D_808F9BBC[2], D_808F9BBC[3], horse->actor.world.pos.x,
                            horse->actor.world.pos.z)) {
        this->unk_164 |= 0x40;
    }

    if (!(this->unk_164 & 0x80) && (this->unk_164 & 0x40) &&
        Math3D_XZBoundCheck(D_808F9BCC[0], D_808F9BCC[1], D_808F9BCC[2], D_808F9BCC[3], horse->actor.world.pos.x,
                            horse->actor.world.pos.z)) {
        this->unk_164 |= 0x80;
    }

    horseGameCheck = (EnHorseGameCheck*)DynaPoly_GetActor(&globalCtx->colCtx, horse->unk_24C);
    if ((this->unk_164 & 0x80) && (horseGameCheck != NULL) &&
        (horseGameCheck->dyna.actor.id == ACTOR_EN_HORSE_GAME_CHECK) &&
        (horseGameCheck->unk_15C == ENHORSEGAMECHECK_FF_7) && !(this->unk_164 & 0x800)) {
        Audio_QueueSeqCmd(0x8041);
        play_sound(NA_SE_SY_START_SHOT);
        this->unk_164 |= 0x800;
        gSaveContext.unk_3DD0[4] = 6;
        SET_RACE_FLAGS(RACE_FLAG_2)
        this->unk_174 = 60;
    }
    return true;
}

s32 func_808F96E4(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    s32 pad[3];
    CollisionHeader* sp78 = NULL;
    MtxF sp38;

    this->dyna.actor.scale.x = this->dyna.actor.scale.y = this->dyna.actor.scale.z = this->unk_160 * 0.01f;
    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&ovl_En_Horse_Game_Check_Colheader_0010C8, &sp78);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp78);
    this->unk_15C = ENHORSEGAMECHECK_FF_7;
    this->dyna.actor.floorPoly = NULL;
    this->dyna.actor.world.pos.y += 100.0f;

    this->dyna.actor.floorHeight = BgCheck_EntityRaycastFloor2(
        globalCtx, &globalCtx->colCtx, &this->dyna.actor.floorPoly, &this->dyna.actor.world.pos);
    this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight + 1.0f;
    func_800C0094(this->dyna.actor.floorPoly, this->dyna.actor.world.pos.x, this->dyna.actor.floorHeight,
                  this->dyna.actor.world.pos.z, &sp38);

    Matrix_SetCurrentState(&sp38);
    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.y, MTXMODE_APPLY);
    Matrix_CopyCurrentState(&sp38);

    func_8018219C(&sp38, &this->dyna.actor.shape.rot, 1);
    this->dyna.actor.world.rot = this->dyna.actor.shape.rot;
    return true;
}

s32 func_808F9830(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    return true;
}

s32 func_808F9868(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 2400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

s32 func_808F987C(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    s32 pad[3];
    CollisionHeader* sp28 = NULL;
    s32 pad2;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.scale.z = 1.0f;
    this->dyna.actor.scale.y = 1.0f;
    this->dyna.actor.scale.x = 1.0f;
    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_horse_game_check_Colheader_002FB8, &sp28);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp28);
    this->unk_15C = ENHORSEGAMECHECK_FF_8;
    return true;
}

s32 func_808F990C(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    return true;
}

s32 func_808F9944(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_808F9958(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_horse_game_check_DL_0014B0);
    Gfx_DrawDListOpa(globalCtx, object_horse_game_check_DL_0013A0);
    return true;
}

s32 func_808F999C(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_808F99B0(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_808F99C4(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_808F99D8(EnHorseGameCheck* this, GlobalContext* globalCtx) {
    return true;
}

EnHorseGameCheckUnkFunc D_808F9BE4[] = {
    NULL, NULL, NULL, NULL, NULL, func_808F8AA0, func_808F8CCC, func_808F96E4, func_808F987C, func_808F999C,
};

EnHorseGameCheckUnkFunc D_808F9C0C[] = {
    NULL, NULL, NULL, NULL, NULL, func_808F8C24, func_808F8E94, func_808F9830, func_808F990C, func_808F99B0,
};

EnHorseGameCheckUnkFunc D_808F9C34[] = {
    NULL, NULL, NULL, NULL, NULL, func_808F8C5C, func_808F8FAC, func_808F9868, func_808F9944, func_808F99C4,
};

EnHorseGameCheckUnkFunc D_808F9C5C[] = {
    NULL, NULL, NULL, NULL, NULL, func_808F8C70, NULL, NULL, func_808F9958, func_808F99D8,
};

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseGameCheck* this = THIS;

    this->unk_15C = ENHORSEGAMECHECK_GET_FF(&this->dyna.actor);
    this->unk_160 = ENHORSEGAMECHECK_GET_FF00(&this->dyna.actor);

    if (this->unk_15C >= ENHORSEGAMECHECK_FF_MAX) {
        this->unk_15C = ENHORSEGAMECHECK_FF_0;
    }

    if (D_808F9BE4[this->unk_15C] != NULL) {
        D_808F9BE4[this->unk_15C](this, globalCtx);
    }
}

void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseGameCheck* this = THIS;

    if (D_808F9C0C[this->unk_15C] != NULL) {
        D_808F9C0C[this->unk_15C](this, globalCtx);
    }
}

void EnHorseGameCheck_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseGameCheck* this = THIS;

    if (D_808F9C34[this->unk_15C] != NULL) {
        D_808F9C34[this->unk_15C](this, globalCtx);
    }
}

void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseGameCheck* this = THIS;

    if (D_808F9C5C[this->unk_15C] != NULL) {
        D_808F9C5C[this->unk_15C](this, globalCtx);
    }
}
