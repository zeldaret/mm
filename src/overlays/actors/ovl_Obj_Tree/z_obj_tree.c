/*
 * File: z_obj_tree.c
 * Overlay: ovl_Obj_Tree
 * Description: Single branching tree (e.g. North Clock Town)
 */

#include "z_obj_tree.h"
#include "objects/object_tree/object_tree.h"

#define FLAGS (ACTOR_FLAG_2000000)

#define THIS ((ObjTree*)thisx)

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObTree_DoNothing(ObjTree* this, GlobalContext* globalCtx);
void ObTree_SetupDoNothing(ObjTree* this);
void ObTree_Sway(ObjTree* this, GlobalContext* globalCtx);

const ActorInit Obj_Tree_InitVars = {
    ACTOR_OBJ_TREE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TREE,
    sizeof(ObjTree),
    (ActorFunc)ObjTree_Init,
    (ActorFunc)ObjTree_Destroy,
    (ActorFunc)ObjTree_Update,
    (ActorFunc)ObjTree_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x0100020A, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 28, 120, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static CollisionCheckInfoInit2 sColchkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjTree* this = THIS;
    CollisionHeader* colHeader = NULL;

    if (OBJTREE_ISLARGE(&this->dyna.actor)) {
        Actor_SetScale(&this->dyna.actor, 0.15f);
        this->dyna.actor.uncullZoneForward = 4000.0f;
    } else {
        Actor_SetScale(&this->dyna.actor, 0.1f);
        DynaPolyActor_Init(&this->dyna, 1);
        CollisionHeader_GetVirtual(&object_tree_Colheader_001B2C, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    }

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->dyna.actor.colChkInfo, &sDamageTable, &sColchkInfoInit);

    if (OBJTREE_ISLARGE(&this->dyna.actor)) {
        this->collider.dim.height = 220;
    }

    this->swayAmplitude = 0.0f;
    this->swayAngle = 0;
    this->swayVelocity = 0;
    ObTree_SetupDoNothing(this);
}

void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjTree* this = THIS;
    s32 bgId;

    if (!OBJTREE_ISLARGE(&this->dyna.actor)) {
        bgId = this->dyna.bgId;
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, bgId);
    }

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void ObTree_SetupDoNothing(ObjTree* this) {
    this->actionFunc = ObTree_DoNothing;
}

void ObTree_DoNothing(ObjTree* this, GlobalContext* globalCtx) {
}

void ObTree_SetupSway(ObjTree* this) {
    this->timer = 0;
    this->swayAmplitude = 546.0f;
    this->swayVelocity = 35 * 0x10000 / 360;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_TREE_SWING);
    this->actionFunc = ObTree_Sway;
}

void ObTree_Sway(ObjTree* this, GlobalContext* globalCtx) {
    if (this->timer > 80) {
        ObTree_SetupDoNothing(this);
        return;
    }

    Math_SmoothStepToF(&this->swayAmplitude, 0.0f, 0.1f, 91.0f, 18.0f);
    this->swayVelocity += 1 * 0x10000 / 360;
    this->swayAngle += this->swayVelocity;
    this->dyna.actor.shape.rot.x = Math_SinS(this->swayAngle) * this->swayAmplitude;
    this->dyna.actor.shape.rot.z = Math_CosS(this->swayAngle) * this->swayAmplitude;
    this->timer++;
}

void ObTree_UpdateCollision(ObjTree* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (this->dyna.actor.xzDistToPlayer < 600.0f) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (this->dyna.actor.home.rot.y == 1) {
            this->dyna.actor.home.rot.y = 0;
            ObTree_SetupSway(this);
        }
    }
}

void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTree* this = THIS;

    this->actionFunc(this, globalCtx);
    ObTree_UpdateCollision(this, globalCtx);
}

void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s16 xRot = (f32)thisx->shape.rot.x;
    s16 zRot = (f32)thisx->shape.rot.z;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_tree_DL_000680);

    Matrix_InsertRotation(xRot, 0, zRot, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_tree_DL_0007C8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
