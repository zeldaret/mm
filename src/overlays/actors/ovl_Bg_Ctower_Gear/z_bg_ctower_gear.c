/*
 * File: z_bg_ctower_gear.c
 * Overlay: ovl_Bg_Ctower_Gear
 * Description: Different Cogs/Organ inside Clock Tower
 */

#include "z_bg_ctower_gear.h"
#include "objects/object_ctower_rot/object_ctower_rot.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgCtowerGear*)thisx)

void BgCtowerGear_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgCtowerGear_UpdateOrgan(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_DrawOrgan(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Ctower_Gear_InitVars = {
    ACTOR_BG_CTOWER_GEAR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_CTOWER_ROT,
    sizeof(BgCtowerGear),
    (ActorFunc)BgCtowerGear_Init,
    (ActorFunc)BgCtowerGear_Destroy,
    (ActorFunc)BgCtowerGear_Update,
    (ActorFunc)BgCtowerGear_Draw,
};

static Vec3f sExitSplashOffsets[] = {
    { -70.0f, -60.0f, 8.0f },
    { -60.0f, -60.0f, -9.1f },
    { -75.0f, -60.0f, -9.1f },
    { -70.0f, -60.0f, -26.2f },
};

static Vec3f sEnterSplashOffsets[] = {
    { 85.0f, -60.0f, 8.0f },
    { 80.0f, -60.0f, -9.1f },
    { 85.0f, -60.0f, -26.2f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

static InitChainEntry sInitChainCenterCog[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2000, ICHAIN_STOP),
};

static InitChainEntry sInitChainOrgan[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 420, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 570, ICHAIN_STOP),
};

static Gfx* sDLists[] = { gClockTowerCeilingCogDL, gClockTowerCenterCogDL, gClockTowerWaterWheelDL };

void BgCtowerGear_Splash(BgCtowerGear* this, GlobalContext* globalCtx) {
    s32 i;
    s32 flag40 = this->dyna.actor.flags & 0x40;
    Vec3f splashSpawnPos;
    Vec3f splashOffset;
    s32 pad;
    s32 j;
    s16 rotZ = this->dyna.actor.shape.rot.z & 0x1FFF;

    if (flag40 && (rotZ < 0x1B58) && (rotZ >= 0x1388)) {
        Matrix_RotateY(this->dyna.actor.home.rot.y, MTXMODE_NEW);
        Matrix_InsertXRotation_s(this->dyna.actor.home.rot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->dyna.actor.home.rot.z, MTXMODE_APPLY);
        for (i = 0; i < 4; i++) {
            if ((u32)Rand_Next() >= 0x40000000) {
                splashOffset.x = sExitSplashOffsets[i].x - (Rand_ZeroOne() * 30.0f);
                splashOffset.y = sExitSplashOffsets[i].y;
                splashOffset.z = sExitSplashOffsets[i].z;
                Matrix_MultiplyVector3fByState(&splashOffset, &splashSpawnPos);
                splashSpawnPos.x += this->dyna.actor.world.pos.x + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                splashSpawnPos.y += this->dyna.actor.world.pos.y;
                splashSpawnPos.z += this->dyna.actor.world.pos.z + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                EffectSsGSplash_Spawn(globalCtx, &splashSpawnPos, NULL, NULL, 0, ((u32)Rand_Next() >> 25) + 340);
            }
        }
    }
    if ((rotZ < 0x1F4) && (rotZ >= 0)) {
        if (flag40) {
            Matrix_RotateY(this->dyna.actor.home.rot.y, MTXMODE_NEW);
            Matrix_InsertXRotation_s(this->dyna.actor.home.rot.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->dyna.actor.home.rot.z, MTXMODE_APPLY);
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 2; j++) {
                    splashOffset.x = sEnterSplashOffsets[i].x + (Rand_ZeroOne() * 10.0f);
                    splashOffset.y = sEnterSplashOffsets[i].y;
                    splashOffset.z = sEnterSplashOffsets[i].z;
                    Matrix_MultiplyVector3fByState(&splashOffset, &splashSpawnPos);
                    splashSpawnPos.x += this->dyna.actor.world.pos.x + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                    splashSpawnPos.y += this->dyna.actor.world.pos.y;
                    splashSpawnPos.z += this->dyna.actor.world.pos.z + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                    EffectSsGSplash_Spawn(globalCtx, &splashSpawnPos, NULL, NULL, 0, ((u32)Rand_Next() >> 25) + 280);
                }
            }
        }
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WATERWHEEL_LEVEL);
    }
}

void BgCtowerGear_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type = BGCTOWERGEAR_GET_TYPE(&this->dyna.actor);

    Actor_SetScale(&this->dyna.actor, 0.1f);
    if (type == BGCTOWERGEAR_CENTER_COG) {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChainCenterCog);
    } else if (type == BGCTOWERGEAR_ORGAN) {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChainOrgan);
        this->dyna.actor.draw = NULL;
        this->dyna.actor.update = BgCtowerGear_UpdateOrgan;
    } else {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    }
    if (type == BGCTOWERGEAR_WATER_WHEEL) {
        DynaPolyActor_Init(&this->dyna, 3);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gClockTowerWaterWheelCol);
    } else if (type == BGCTOWERGEAR_ORGAN) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gClockTowerOrganCol);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgCtowerGear_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type = BGCTOWERGEAR_GET_TYPE(&this->dyna.actor);

    if ((type == BGCTOWERGEAR_WATER_WHEEL) || (type == BGCTOWERGEAR_ORGAN)) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgCtowerGear_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type = BGCTOWERGEAR_GET_TYPE(&this->dyna.actor);

    if (type == BGCTOWERGEAR_CEILING_COG) {
        this->dyna.actor.shape.rot.x -= 0x1F4;
    } else if (type == BGCTOWERGEAR_CENTER_COG) {
        this->dyna.actor.shape.rot.y += 0x1F4;
        func_800B9010(&this->dyna.actor, NA_SE_EV_WINDMILL_LEVEL - SFX_FLAG);
    } else if (type == BGCTOWERGEAR_WATER_WHEEL) {
        this->dyna.actor.shape.rot.z -= 0x1F4;
        BgCtowerGear_Splash(this, globalCtx);
    }
}

void BgCtowerGear_UpdateOrgan(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;

    if (Cutscene_CheckActorAction(globalCtx, 104)) {
        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 104)]->action) {
            case 1:
                this->dyna.actor.draw = NULL;
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                break;
            case 2:
                this->dyna.actor.draw = BgCtowerGear_DrawOrgan;
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                break;
            case 3:
                Actor_MarkForDeath(&this->dyna.actor);
                break;
        }
    }
}

void BgCtowerGear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, sDLists[BGCTOWERGEAR_GET_TYPE(thisx)]);
}

void BgCtowerGear_DrawOrgan(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gClockTowerOrganDL);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gClockTowerOrganPipesDL);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
