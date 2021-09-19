#include "z_obj_etcetera.h"

#define FLAGS 0x00000010

#define THIS ((ObjEtcetera*)thisx)

void ObjEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A7BF08(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C168(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C1F0(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C308(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C690(Actor* thisx, GlobalContext* globalCtx);
void func_80A7C718(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Etcetera_InitVars = {
    ACTOR_OBJ_ETCETERA,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjEtcetera),
    (ActorFunc)ObjEtcetera_Init,
    (ActorFunc)ObjEtcetera_Destroy,
    (ActorFunc)ObjEtcetera_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A7C790 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 20, 14, 0, { 0, 0, 0 } },
};

extern ColliderCylinderInit D_80A7C790;

static s16 D_80A7C7BC[] = { 0x0001, 0x0001, 0x0001, 0x0001 };

static f32 D_80A7C7C4[] = { -1.0, -1.0, -1.0, -0.7, 0.0, 0.7, 1.0, 0.7, 0.0,
                            -0.7, -1.0, -0.7, 0.0,  0.7, 1.0, 0.7, 0.0, -0.7 };

static s32 D_80A7C80C[] = { 0x0400E710, 0x0400E710, 0x040118D8, 0x040118D8, 0x00000000 };

void ObjEtcetera_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjEtcetera* this = THIS;
    s32 objectIndex;
    s32 index;
    s32 floorBgId;
    Vec3f somePos;

    index = (this->dyna.actor.params & 0xFF80) >> 7;
    if ((index < 0) || (index >= 4)) {
        index = 0;
    }
    objectIndex = Object_GetIndex(&globalCtx->objectCtx, D_80A7C7BC[index]);
    if (objectIndex >= 0) {
        this->unk_278 = (u8)objectIndex;
    }
    somePos.x = this->dyna.actor.world.pos.x;
    somePos.y = this->dyna.actor.world.pos.y + 10.0f;
    somePos.z = this->dyna.actor.world.pos.z;
    func_800C411C(&globalCtx->colCtx, &this->dyna.actor.floorPoly, &floorBgId, &this->dyna.actor, &somePos);
    this->dyna.actor.floorBgId = floorBgId;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80A7C790);
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    this->actionFunc = func_80A7C308;
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->dyna.actor.scale.y = 0.02f;
    this->unk_276 = 0;
}

void ObjEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjEtcetera* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BDC8.s")

void func_80A7BE8C(ObjEtcetera* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, (AnimationHeader*)&D_040117A8, 1.0f, 0.0f,
                         (f32)SkelAnime_GetFrameCount((AnimationHeaderCommon*)&D_040117A8), 2, 0.0f);
    this->dyna.actor.draw = func_80A7C718;
    this->actionFunc = func_80A7C168;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BF08.s")

void func_80A7C168(ObjEtcetera* this, GlobalContext* globalCtx) {
    if (func_800CAF70(&this->dyna) != 0) {
        this->unk_276 = (u16)this->unk_276 | 1;
    } else {
        this->unk_276 = (u16)this->unk_276 & ~1;
    }
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->dyna.actor.draw = func_80A7C690;
        this->actionFunc = func_80A7BF08;
    }
    func_80A7BDC8(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C308.s")

void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjEtcetera* this = THIS;
    CollisionPoly* floorPoly;
    u8 floorBgId;

    floorBgId = this->dyna.actor.floorBgId;
    if (floorBgId == 0x32) {
        floorPoly = this->dyna.actor.floorPoly;
        if ((floorPoly != NULL) && (((u16)this->unk_276 & 1) != 0)) {
            func_800FAAB4(globalCtx, func_800C9C9C(&globalCtx->colCtx, floorPoly, floorBgId));
        }
    }
    this->actionFunc(this, globalCtx);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80A7C690(Actor* thisx, GlobalContext* globalCtx) {
    ObjEtcetera* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_27C);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A7C718(Actor* thisx, GlobalContext* globalCtx) {
    ObjEtcetera* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, NULL, NULL, &this->dyna.actor);
}
