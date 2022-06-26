/*
 * File: z_obj_hsblock.c
 * Overlay: ovl_Obj_Hsblock
 * Description: Hookshot Block
 */

#include "z_obj_hsblock.h"
#include "objects/object_d_hsblock/object_d_hsblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjHsblock*)thisx)

void ObjHsblock_Init(Actor* thisx, PlayState* play);
void ObjHsblock_Destroy(Actor* thisx, PlayState* play);
void ObjHsblock_Update(Actor* thisx, PlayState* play);
void ObjHsblock_Draw(Actor* thisx, PlayState* play);

void func_8093E0A0(ObjHsblock* this, PlayState* play);

void func_8093E03C(ObjHsblock* this);
void func_8093E05C(ObjHsblock* this);
void func_8093E0E8(ObjHsblock* this);
void func_8093E10C(ObjHsblock* this, GlobalContext* globalCtx);

const ActorInit Obj_Hsblock_InitVars = {
    ACTOR_OBJ_HSBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_HSBLOCK,
    sizeof(ObjHsblock),
    (ActorFunc)ObjHsblock_Init,
    (ActorFunc)ObjHsblock_Destroy,
    (ActorFunc)ObjHsblock_Update,
    (ActorFunc)ObjHsblock_Draw,
};

static f32 focusPos[] = { 85.0f, 85.0f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

static CollisionHeader* sColHeader[] = {
    &object_d_hsblock_Colheader_000730,
    &object_d_hsblock_Colheader_000730,
    &object_d_hsblock_Colheader_000578,
};

static u32 sDisplayLists[] = { object_d_hsblock_DL_000210, object_d_hsblock_DL_000210, object_d_hsblock_DL_000470 };

static Color_RGB8 sEnvColor[] = {
    { 60, 60, 120 },
    { 120, 100, 70 },
    { 100, 150, 120 },
    { 255, 255, 255 },
};

void ObjHsblock_SetupAction(ObjHsblock* this, ObjHsblockActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_8093DEAC(ObjHsblock* this, GlobalContext* globalCtx) {
    if (OBJHSBLOCK_GET_5(&this->dyna.actor) != 0) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, 0x8E, this->dyna.actor.world.pos.x,
                           this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.world.rot.x,
                           this->dyna.actor.world.rot.y, this->dyna.actor.world.rot.z, 0xFF64);
    }
}

void ObjHsblock_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsblock* this = THIS;

    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, sColHeader[OBJHSBLOCK_GET_3(thisx)]);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    func_8093DEAC(this, globalCtx);

    switch (OBJHSBLOCK_GET_3(&this->dyna.actor)) {
        case 0:
        case 2:
            func_8093E03C(this);
            break;
        case 1:
            if (Flags_GetSwitch(globalCtx, OBJHSBLOCK_GET_SWITCH(thisx)) != 0) {
                func_8093E03C(this);
            } else {
                func_8093E05C(this);
            }
            break;
        default:
            break;
    }
}

void ObjHsblock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsblock* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_8093E03C(ObjHsblock* this) {
    ObjHsblock_SetupAction(this, NULL);
}

void func_8093E05C(ObjHsblock* this) {
    this->dyna.actor.flags |= 0x10;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - 105.0f;
    ObjHsblock_SetupAction(this, func_8093E0A0);
}

void func_8093E0A0(ObjHsblock* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, OBJHSBLOCK_GET_SWITCH(&this->dyna.actor)) != 0) {
        func_8093E0E8(this);
    }
}

void func_8093E0E8(ObjHsblock* this) {
    ObjHsblock_SetupAction(this, func_8093E10C);
}

void func_8093E10C(ObjHsblock* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->dyna.actor.velocity.y, 16.0f, 0.1f, 0.8f, 0.0f);
    if (fabsf(Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 0.3f,
                                 this->dyna.actor.velocity.y, 0.3f)) < 0.001f) {
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
        func_8093E03C(this);
        this->dyna.actor.flags &= -0x11;
    }
}

void ObjHsblock_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsblock* this = THIS;

    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
    }
    Actor_SetFocus(&this->dyna.actor, focusPos[OBJHSBLOCK_GET_3(thisx)]);
}

void ObjHsblock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Color_RGB8* envColor;
    envColor = &sEnvColor[OBJHSBLOCK_GET_6(thisx)];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(POLY_OPA_DISP++, envColor->r, envColor->g, envColor->b, 255);
    gSPDisplayList(POLY_OPA_DISP++, sDisplayLists[OBJHSBLOCK_GET_3(thisx)]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
