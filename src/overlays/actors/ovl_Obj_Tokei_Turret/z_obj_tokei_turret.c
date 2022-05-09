/*
 * File: z_obj_tokei_turret.c
 * Overlay: ovl_Obj_Tokei_Turret
 * Description: South Clock Town - Flags & Carnival Platform
 */

#include "z_obj_tokei_turret.h"
#include "objects/object_tokei_turret/object_tokei_turret.h"

#define FLAGS 0x00000000

#define THIS ((ObjTokeiTurret*)thisx)

void ObjTokeiTurret_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTurret_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTurret_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTurret_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Tokei_Turret_InitVars = {
    ACTOR_OBJ_TOKEI_TURRET,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TOKEI_TURRET,
    sizeof(ObjTokeiTurret),
    (ActorFunc)ObjTokeiTurret_Init,
    (ActorFunc)ObjTokeiTurret_Destroy,
    (ActorFunc)ObjTokeiTurret_Update,
    (ActorFunc)ObjTokeiTurret_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjTokeiTurret_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiTurret* this = THIS;
    Actor* actor;
    s32 actorParams;

    actor = &this->dyna.actor;
    actorParams = actor->params & 3;
    this->dyna.actor = *actor;
    Actor_ProcessInitChain(actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);

    if ((actorParams == 0) || (actorParams == 1)) { // could this be day?

        actor->uncullZoneScale = 240.0f;
        actor->uncullZoneDownward = 240.0f;

        if (actorParams == 0) {
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_tokei_turret_Colheader_0026A0);
            return;
        }

        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_tokei_turret_Colheader_002D80);
        return;
    }

    actor->uncullZoneScale = 1300.0f;
    actor->uncullZoneDownward = 1300.0f;
}

void ObjTokeiTurret_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiTurret* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjTokeiTurret_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjTokeiTurret_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiTurret* this = THIS;
    Gfx* gfx;

    if ((this->dyna.actor.params & 3) == 1) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gfx = POLY_OPA_DISP;
        gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
        gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
        gSPDisplayList(gfx++, &gTokeiTurretPlatformTopDL);
        POLY_OPA_DISP = gfx;

        CLOSE_DISPS(globalCtx->state.gfxCtx);
        return;
    }
    if ((this->dyna.actor.params & 3) == 0) {
        Gfx_DrawDListOpa(globalCtx, gTokeiTurretPlatformBaseDL);
        return;
    }
    Gfx_DrawDListOpa(globalCtx, gClockTownFlagsDL);
}
