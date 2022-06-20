/*
 * File: z_bg_botihasira.c
 * Overlay: ovl_Bg_Botihasira
 * Description: Captain Keeta Race - Gatepost
 */

#include "z_bg_botihasira.h"
#include "objects/object_botihasira/object_botihasira.h"

#define FLAGS 0x00000000

#define THIS ((BgBotihasira*)thisx)

void BgBotihasira_Init(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Update(Actor* thisx, GlobalContext* globalCtx2);
void BgBotihasira_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgBotihasira_DoNothing(BgBotihasira* this, GlobalContext* globalCtx);

const ActorInit Bg_Botihasira_InitVars = {
    ACTOR_BG_BOTIHASIRA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOTIHASIRA,
    sizeof(BgBotihasira),
    (ActorFunc)BgBotihasira_Init,
    (ActorFunc)BgBotihasira_Destroy,
    (ActorFunc)BgBotihasira_Update,
    (ActorFunc)BgBotihasira_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 27, 80, 0, { 0, 0, 0 } },
};

void BgBotihasira_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgBotihasira* this = THIS;
    CollisionHeader* colHeader;

    colHeader = NULL;
    if (this->dyna.actor.params == 0) {
        DynaPolyActor_Init(&this->dyna, 0);
        CollisionHeader_GetVirtual(&object_botihasira_Colheader_001BD8, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    } else {
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    }
    this->actionFunc = BgBotihasira_DoNothing;
    this->dyna.actor.scale.x = 0.1f;
    this->dyna.actor.scale.y = 0.1f;
    this->dyna.actor.scale.z = 0.1f;
}

void BgBotihasira_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgBotihasira* this = THIS;

    if (this->dyna.actor.params == 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgBotihasira_DoNothing(BgBotihasira* this, GlobalContext* globalCtx) {
}

void BgBotihasira_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgBotihasira* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->dyna.actor.params != 0) {
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x + (Math_SinS(this->dyna.actor.world.rot.y) * -27.0f);
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + (Math_CosS(this->dyna.actor.world.rot.y) * 7.0f);
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos);
    }
}

void BgBotihasira_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_botihasira_DL_000638);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
