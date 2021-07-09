/*
 * File: z_bg_ctower_gear.c
 * Overlay: Bg_Ctower_Gear
 * Description: Different Cogs/Organ inside Clock Tower
 */

#include "z_bg_ctower_gear.h"

#define FLAGS 0x00000010

#define THIS ((BgCtowerGear*)thisx)

#define BGCTOWERGEAR_GET_TYPE(this) (((BgCtowerGear*)this)->dyna.actor.params & 3)

typedef enum {
    /* 0x00 */ CEILING_COG,
    /* 0x01 */ CENTER_COG,
    /* 0x02 */ WATER_WHEEL,
    /* 0x03 */ ORGAN
} BgCtowerGearType;

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

extern Gfx D_06010828[];

extern Gfx D_06015F30[];

extern Gfx D_060160A0[];

extern CollisionHeader D_06016E70;

extern Gfx D_06017018[];

extern Gfx D_06018118[];

extern CollisionHeader D_06018588;

static Vec3f D_80AD3270[] = {
    { -70.0f, -60.0f, 8.0f }, { -60.0f, -60.0f, -9.1f }, { -75.0f, -60.0f, -9.1f }, { -70.0f, -60.0f, -26.2f }
};

static Vec3f D_80AD32A0[] = {
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

static Gfx* D_80AD32E8[] = { D_06010828, D_06017018, D_06018118 };

void BgCtowerGear_Splash(BgCtowerGear* this, GlobalContext* globalCtx) {
    int i;
    s32 flags;
    Vec3f splashSpawnPos;
    Vec3f splashOffset;
    s32 pad;
    int j;
    s16 rotZ;

    flags = this->dyna.actor.flags & 0x40;
    rotZ = this->dyna.actor.shape.rot.z & 0x1FFF;
    if ((flags != 0) && (rotZ < 0x1B58) && (rotZ >= 0x1388)) {
        Matrix_RotateY(this->dyna.actor.home.rot.y, 0);
        SysMatrix_InsertXRotation_s(this->dyna.actor.home.rot.x, 1);
        SysMatrix_InsertZRotation_s(this->dyna.actor.home.rot.z, 1);
        for (i = 0; i < 4; i++) {
            if ((u32)Rand_Next() >= 0x40000000) {
                splashOffset.x = D_80AD3270[i].x - (Rand_ZeroOne() * 30.0f);
                splashOffset.y = D_80AD3270[i].y;
                splashOffset.z = D_80AD3270[i].z;
                SysMatrix_MultiplyVector3fByState(&splashOffset, &splashSpawnPos);
                splashSpawnPos.x += this->dyna.actor.world.pos.x + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                splashSpawnPos.y += this->dyna.actor.world.pos.y;
                splashSpawnPos.z += this->dyna.actor.world.pos.z + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                EffectSsGSplash_Spawn(globalCtx, &splashSpawnPos, NULL, NULL, 0, ((u32)Rand_Next() >> 25) + 340);
            }
        }
    }
    if ((rotZ < 0x1F4) && (rotZ >= 0)) {
        if (flags != 0) {
            Matrix_RotateY(this->dyna.actor.home.rot.y, 0);
            SysMatrix_InsertXRotation_s(this->dyna.actor.home.rot.x, 1);
            SysMatrix_InsertZRotation_s(this->dyna.actor.home.rot.z, 1);
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 2; j++) {
                    splashOffset.x = D_80AD32A0[i].x + (Rand_ZeroOne() * 10.0f);
                    splashOffset.y = D_80AD32A0[i].y;
                    splashOffset.z = D_80AD32A0[i].z;
                    SysMatrix_MultiplyVector3fByState(&splashOffset, &splashSpawnPos);
                    splashSpawnPos.x += this->dyna.actor.world.pos.x + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                    splashSpawnPos.y += this->dyna.actor.world.pos.y;
                    splashSpawnPos.z += this->dyna.actor.world.pos.z + ((Rand_ZeroOne() * 20.0f) - 10.0f);
                    EffectSsGSplash_Spawn(globalCtx, &splashSpawnPos, NULL, NULL, 0, ((u32)Rand_Next() >> 25) + 280);
                }
            }
        }
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_WATERWHEEL_LEVEL);
    }
}

void BgCtowerGear_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type;

    type = BGCTOWERGEAR_GET_TYPE(this);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    if (type == CENTER_COG) {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChainCenterCog);
    } else if (type == ORGAN) {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChainOrgan);
        this->dyna.actor.draw = NULL;
        this->dyna.actor.update = BgCtowerGear_UpdateOrgan;
    } else {
        Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    }
    if (type == WATER_WHEEL) {
        BcCheck3_BgActorInit(&this->dyna, 3);
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06018588);
    } else if (type == ORGAN) {
        BcCheck3_BgActorInit(&this->dyna, 0);
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06016E70);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgCtowerGear_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type;

    type = BGCTOWERGEAR_GET_TYPE(this);
    if ((type == WATER_WHEEL) || (type == ORGAN)) {
        BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgCtowerGear_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;
    s32 type;

    type = BGCTOWERGEAR_GET_TYPE(this);
    if (type == CEILING_COG) {
        this->dyna.actor.shape.rot.x -= 0x1F4;
    } else if (type == CENTER_COG) {
        this->dyna.actor.shape.rot.y += 0x1F4;
        func_800B9010(&this->dyna.actor, NA_SE_EV_WINDMILL_LEVEL - SFX_FLAG);
    } else if (type == WATER_WHEEL) {
        this->dyna.actor.shape.rot.z -= 0x1F4;
        BgCtowerGear_Splash(this, globalCtx);
    }
}

void BgCtowerGear_UpdateOrgan(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerGear* this = THIS;

    if (func_800EE29C(globalCtx, 0x68)) {
        switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x68)]->unk0) {
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

// Using BgCtowerGear *this = THIS causes regalloc issues
void BgCtowerGear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_80AD32E8[BGCTOWERGEAR_GET_TYPE(thisx)]);
}

void BgCtowerGear_DrawOrgan(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_060160A0);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06015F30);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
