#include "z_obj_tree.h"

#define FLAGS 0x02000000

#define THIS ((ObjTree*)thisx)

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B9A220(ObjTree* this, GlobalContext* globalCtx);
void func_80B9A20C(ObjTree* this);
void func_80B9A27C(ObjTree* this, GlobalContext* globalCtx);

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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B9A570 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x0100020A, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 28, 120, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B9A59C = {
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

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B9A5BC = { 8, 0, 0, 0, MASS_HEAVY };

extern Gfx D_06000680[];
extern Gfx D_060007C8[];
extern CollisionHeader D_06001B2C;

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjTree* this = THIS;
    CollisionHeader* colHeader = NULL;

    if (this->dyna.actor.params & 0x8000) {
        Actor_SetScale(&this->dyna.actor, 0.15f);
        this->dyna.actor.uncullZoneForward = 4000.0f;
    } else {
        Actor_SetScale(&this->dyna.actor, 0.1f);
        BcCheck3_BgActorInit(&this->dyna, 1);
        BgCheck_RelocateMeshHeader(&D_06001B2C, &colHeader);
        this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);
    }
    
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80B9A570);
    CollisionCheck_SetInfo2(&this->dyna.actor.colChkInfo, &D_80B9A59C, &D_80B9A5BC);
    
    if (this->dyna.actor.params & 0x8000) {
        this->collider.dim.height = 220;
    }

    this->unk_1AC = 0.0f;
    this->unk_1B0 = 0;
    this->unk_1B2 = 0;
    func_80B9A20C(this);
}

void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjTree* this = THIS;
    s32 index;

    if (!(this->dyna.actor.params & 0x8000)) {
        index = this->dyna.bgId;
        BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, index);
    }

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B9A20C(ObjTree* this) {
    this->actionFunc = func_80B9A220;
}

void func_80B9A220(ObjTree* this, GlobalContext* globalCtx) {
}

void func_80B9A230(ObjTree* this) {
    this->unk_1B4 = 0;
    this->unk_1AC = 546.0f;
    this->unk_1B2 = 0x18E3;
    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_TREE_SWING);
    this->actionFunc = func_80B9A27C;
}

void func_80B9A27C(ObjTree* this, GlobalContext* globalCtx) {
    if (this->unk_1B4 > 0x50) {
        func_80B9A20C(this);
        return;
    }

    Math_SmoothStepToF(&this->unk_1AC, 0.0f, 0.1f, 91.0f, 18.0f);
    this->unk_1B2 += 0xB6;
    this->unk_1B0 += this->unk_1B2;
    this->dyna.actor.shape.rot.x = Math_SinS(this->unk_1B0) * this->unk_1AC;
    this->dyna.actor.shape.rot.z = Math_CosS(this->unk_1B0) * this->unk_1AC;
    this->unk_1B4 += 1;
}

void func_80B9A348(ObjTree* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (this->dyna.actor.xzDistToPlayer < 600.0f) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (this->dyna.actor.home.rot.y == 1) {
            this->dyna.actor.home.rot.y = 0;
            func_80B9A230(this);
        }
    }
}

void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTree* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80B9A348(this, globalCtx);
}

void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s16 sp36 = (f32) thisx->shape.rot.x;
    s16 sp34 = (f32) thisx->shape.rot.z;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000680);

    SysMatrix_InsertRotation(sp36, 0, sp34, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_060007C8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
