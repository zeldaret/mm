#include "z_obj_kibako2.h"

#define FLAGS 0x00000000

#define THIS ((ObjKibako2*)thisx)

void ObjKibako2_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_8098EC68(ObjKibako2* this, GlobalContext* globalCtx);
void func_8098ED20(ObjKibako2* this, GlobalContext* globalCtx);
s32 func_8098EB78(ObjKibako2* this);

const ActorInit Obj_Kibako2_InitVars = {
    ACTOR_OBJ_KIBAKO2,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIBAKO2,
    sizeof(ObjKibako2),
    (ActorFunc)ObjKibako2_Init,
    (ActorFunc)ObjKibako2_Destroy,
    (ActorFunc)ObjKibako2_Update,
    (ActorFunc)ObjKibako2_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8098EE60 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x80000508, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 31, 48, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8098EE8C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

extern Gfx D_06000960;
extern CollisionHeader D_06000B70;
extern UNK_TYPE D_06001040;

#ifdef NON_MATCHING
s32 func_8098E5C0(ObjKibako2* this, GlobalContext* globalCtx) {
    s32 temp_v0;
    s32 flag;
    s32 phi_v0;

    temp_v0 = ((this->dyna.actor.params & 0x1F) * 4) | 0xFF01;
    flag = -1;
    if ((temp_v0 & 3)) {
        flag = ((temp_v0 & 0x3FC) >> 2) & 0xFF;
    }
    phi_v0 = (flag < 0) == 1;
    if (phi_v0 == 0) {
        phi_v0 = Actor_GetChestFlag(globalCtx, flag) == 0;
    }
    return phi_v0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E5C0.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E62C.s")

void func_8098E8A8(ObjKibako2* this, GlobalContext* globalCtx) {
    s32 collectible;

    collectible = func_800A8150(this->dyna.actor.params & 0x3F);
    if (collectible >= 0) {
        Item_DropCollectible(globalCtx, &this->dyna.actor.world.pos, collectible | GET_KIBAKO2_COLLECTIBLE_ID(this));
    }
}

void func_8098E900(ObjKibako2* this, GlobalContext* globalCtx) {
    s16 yRotation;
    s32 param;
    Actor* skulltula;

    if (func_8098E5C0(this, globalCtx) != 0) {
        param = ((this->dyna.actor.params & 0x1F) * 4) | 0xFF01;
        yRotation = ((u32) Rand_Next() >> 0x11) + this->dyna.actor.yawTowardsPlayer + 0xC000;
        skulltula = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_SW, this->dyna.actor.world.pos.x,
                                this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0, yRotation, 0,
                                param);
        if (skulltula != NULL) {
            skulltula->parent = &this->dyna.actor;
            skulltula->velocity.y = 13.0f;
            skulltula->speedXZ = 0.0f;
        }
    }
}

void func_8098E9C4(ObjKibako2* this, GlobalContext* globalCtx) {
    if (((this->dyna.actor.params >> 0xF) & 1) == 0) {
        func_8098E8A8(this, globalCtx);
    } else {
        func_8098E900(this, globalCtx);
    }
}

void ObjKibako2_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjKibako2* this = THIS;
    s16 tempParams;
    s32 sp24;

    sp24 = (this->dyna.actor.params >> 0xF) & 1;
    BcCheck3_BgActorInit(&this->dyna, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Actor_ProcessInitChain(thisx, D_8098EE8C);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000B70);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_8098EE60);
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    thisx->home.rot.z = 0;
    thisx->world.rot.z = 0;
    thisx->shape.rot.z = 0;
    thisx->world.rot.x = 0;
    thisx->shape.rot.x = 0;
    if (sp24 == 0) {
        tempParams = thisx->params;
        if (func_800A81A4(globalCtx, tempParams & 0x3F, (tempParams >> 8) & 0x7F) != 0) {
            this->unk_1AC = 1;
            thisx->flags |= 0x10;
        }
    }
    if ((sp24 != 1) || (func_8098E5C0(this, globalCtx) == 0)) {
        this->skulltulaNoiseTimer = -1;
    }
    this->actionFunc = func_8098EC68;
}

void ObjKibako2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjKibako2* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

s32 func_8098EB78(ObjKibako2* this) {
    u8 acFlags = this->collider.base.acFlags;
    s32 ret = 0;

    if ((acFlags & 2)) {
        Actor* ac = this->collider.base.ac;
        this->collider.base.acFlags = acFlags & 0xFFFD;
        if (ac != NULL) {
            if (this->collider.info.acHitInfo->toucher.dmgFlags & 0x80000000) {
                if (Math3D_DistanceSquared(&this->dyna.actor.world.pos, &ac->world.pos) < 25600.0f) {
                    ret = 1;
                }
            } else if ((this->collider.info.acHitInfo->toucher.dmgFlags & 8) != 0) {
                if (Math3D_DistanceSquared(&this->dyna.actor.world.pos, &ac->world.pos) < 10000.0f) {
                    ret = 1;
                }
            } else if ((this->collider.info.acHitInfo->toucher.dmgFlags & 0x500) != 0) {
                ret = 1;
            }
        }
    } else if (this->dyna.actor.home.rot.z != 0) {
        ret = 1;
    }
    return ret;
}


void func_8098EC68(ObjKibako2* this, GlobalContext* globalCtx) {
    if (func_8098EB78(this) != 0) {
        func_8098E62C(this, globalCtx);
        func_800F0568(globalCtx, &this->dyna.actor.world.pos, 20, NA_SE_EV_WOODBOX_BREAK);
        this->dyna.actor.flags |= 0x10;
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->dyna.actor.draw = NULL;
        this->actionFunc = func_8098ED20;
        return;
    }
    if (this->dyna.actor.xzDistToPlayer < 600.0f) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_8098ED20(ObjKibako2* this, GlobalContext* globalCtx) {
    func_8098E9C4(this, globalCtx);
    Actor_MarkForDeath(&this->dyna.actor);
}

// Still needs a lot of love
#ifdef NON_MATCHING
void ObjKibako2_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjKibako2* this = THIS;

    if (this->unk_1AC != 0) {
        globalCtx->actorCtx.unk5 |= 8;
    }

    if (this->skulltulaNoiseTimer > 0) {
        this->skulltulaNoiseTimer--;
    }
    else if (this->skulltulaNoiseTimer == 0) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EN_STALGOLD_ROLL);
        if (Rand_ZeroOne() < 0.1f) {
            this->skulltulaNoiseTimer = Rand_S16Offset(40, 80);
        } else {
            this->skulltulaNoiseTimer = 8;
        }
    }
    this->actionFunc(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/ObjKibako2_Update.s")
#endif

void ObjKibako2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, &D_06000960);
}
