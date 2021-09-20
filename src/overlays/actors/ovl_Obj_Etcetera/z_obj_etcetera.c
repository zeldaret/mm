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
void func_80A7BDC8(ObjEtcetera* this, GlobalContext* globalCtx);
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
extern CollisionHeader D_0400E710;
extern Gfx D_0400ED80;
extern SkeletonHeader D_04011518;
extern CollisionHeader D_040118D8;
extern Gfx D_04011BD0;
extern SkeletonHeader D_040127E8;

static s16 D_80A7C7BC[] = { 0x0001, 0x0001, 0x0001, 0x0001 };

static f32 D_80A7C7C4[] = { -1.0, -1.0, -1.0, -0.7, 0.0, 0.7, 1.0, 0.7, 0.0,
                            -0.7, -1.0, -0.7, 0.0,  0.7, 1.0, 0.7, 0.0, -0.7 };

static CollisionHeader* D_80A7C80C[] = { &D_0400E710, &D_0400E710, &D_040118D8, &D_040118D8, NULL };

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
        this->unk_278 = objectIndex;
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

void func_80A7BDC8(ObjEtcetera* this, GlobalContext* globalCtx) {
    if (this->unk_274 > 0) {
        Actor_SetScale(&this->dyna.actor,
                       (D_80A7C7C4[globalCtx->gameplayFrames % 18] * (0.0001f * this->unk_274)) + 0.01f);
        this->dyna.actor.scale.y = 0.02f;
        this->unk_274 -= 1;
    dummy_label:; // POSSIBLE FAKE MATCH
        return;
    }
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->dyna.actor.scale.y = 0.02f;
}

void func_80A7BE8C(ObjEtcetera* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, (AnimationHeader*)&D_040117A8, 1.0f, 0.0f,
                         SkelAnime_GetFrameCount((AnimationHeaderCommon*)&D_040117A8), 2, 0.0f);
    this->dyna.actor.draw = func_80A7C718;
    this->actionFunc = func_80A7C168;
}

void func_80A7BF08(ObjEtcetera* this, GlobalContext* globalCtx) {
    s16 temp_v0_2;
    Player* player = PLAYER;

    if ((player->stateFlags3 & 0x200) && (this->dyna.actor.xzDistToPlayer < 20.0f)) {
        SkelAnime_ChangeAnim(&this->skelAnime, (AnimationHeader*)&D_0400EB7C, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount((AnimationHeaderCommon*)&D_0400EB7C), 2, 0.0f);
        this->dyna.actor.draw = func_80A7C718;
        this->actionFunc = func_80A7C1F0;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        this->dyna.actor.scale.y = 0.02f;
        this->unk_270 = 0.003f;
        this->unk_274 = 30;
        this->unk_276 &= ~1;
    } else if ((player->stateFlags3 & 0x2000) && (this->dyna.actor.xzDistToPlayer < 30.0f) &&
               (this->dyna.actor.yDistToPlayer > 0.0f)) {
        temp_v0_2 = 10 - (s32)(this->dyna.actor.yDistToPlayer * 0.05f);
        if (this->unk_274 < temp_v0_2) {
            this->unk_274 = temp_v0_2;
        }
    } else {
        if (func_800CAF70(&this->dyna) != 0) {
            if (!(this->unk_276 & 1)) {
                this->unk_274 = 10;
                func_80A7BE8C(this);
            } else if ((player->actor.speedXZ > 0.1f) || ((player->unk_ABC < 0.0f) && !(player->stateFlags3 & 0x100))) {
                this->unk_274 = 10;
            }
            this->unk_276 |= 1;
        } else {
            if (this->unk_276 & 1) {
                this->unk_274 = 10;
                func_80A7BE8C(this);
            }
            this->unk_276 &= ~1;
        }
    }
    if ((this->collider.base.acFlags & 2)) {
        this->unk_274 = 10;
        func_80A7BE8C(this);
    }
    func_80A7BDC8(this, globalCtx);
}

void func_80A7C168(ObjEtcetera* this, GlobalContext* globalCtx) {
    if (func_800CAF70(&this->dyna)) {
        this->unk_276 |= 1;
    } else {
        this->unk_276 &= ~1;
    }
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        this->dyna.actor.draw = func_80A7C690;
        this->actionFunc = func_80A7BF08;
    }
    func_80A7BDC8(this, globalCtx);
}

void func_80A7C1F0(ObjEtcetera* this, GlobalContext* globalCtx) {
    // In order to match, we are seemingly required to access scale.x at one point
    // without using this. We can create a thisx or dyna pointer to achieve that, but
    // it's more likely they used dyna given that func_800CAF70 takes a DynaPolyActor.
    DynaPolyActor* dyna = &this->dyna;
    f32 scaleTemp;

    if (func_800CAF70(dyna)) {
        this->unk_276 |= 1;
    } else {
        this->unk_276 &= ~1;
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (0 < this->unk_274) {
        this->unk_274--;
    } else {
        this->dyna.actor.draw = func_80A7C690;
        this->actionFunc = func_80A7BF08;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        this->dyna.actor.scale.y = 0.02f;
        this->unk_274 = 0;
        this->unk_270 = 0.0f;
        return;
    }
    this->unk_270 *= 0.8f;
    this->unk_270 -= (this->dyna.actor.scale.x - 0.01f) * 0.4f;
    scaleTemp = dyna->actor.scale.x + this->unk_270;
    Actor_SetScale(&this->dyna.actor, scaleTemp);
    this->dyna.actor.scale.y = 2.0f * scaleTemp;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C308.s")

void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjEtcetera* this = THIS;
    CollisionPoly* floorPoly;
    u8 floorBgId;

    floorBgId = this->dyna.actor.floorBgId;
    if (floorBgId == 0x32) {
        floorPoly = this->dyna.actor.floorPoly;
        if ((floorPoly != NULL) && ((this->unk_276 & 1))) {
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
