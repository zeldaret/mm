/*
 * File: z_obj_tsubo.c
 * Overlay: ovl_Obj_Tsubo
 * Description: Pots
 */

#include "z_obj_tsubo.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_tsubo/object_tsubo.h"
#include "objects/object_racetsubo/object_racetsubo.h"

#define FLAGS 0x04800010

#define THIS ((ObjTsubo*)thisx)

void ObjTsubo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Update(Actor* thisx, GlobalContext* globalCtx);

//UnkFunc
void func_80927A78(ObjTsubo* this, GlobalContext* globalCtx);
void func_80927D2C(ObjTsubo* this, GlobalContext* globalCtx);
void func_80927FCC(ObjTsubo* this, GlobalContext* globalCtx);
void func_809282F0(ObjTsubo* this, GlobalContext* globalCtx);
void func_8092860C(ObjTsubo* this, GlobalContext* globalCtx);
void func_80928904(ObjTsubo* this, GlobalContext* globalCtx);

void func_809294B0(Actor* this, GlobalContext* globalCtx); // draw

void func_80928914(ObjTsubo* this);
void func_809289B4(ObjTsubo* this);
void func_80928D6C(ObjTsubo* this);
void func_80928E74(ObjTsubo* this);
void func_809291DC(ObjTsubo* this);

void func_80928928(ObjTsubo* this, GlobalContext* globalCtx);
void func_809289E4(ObjTsubo* this, GlobalContext* globalCtx);
void func_80928D80(ObjTsubo* this, GlobalContext* globalCtx);
void func_80928F18(ObjTsubo* this, GlobalContext* globalCtx);
void func_8092926C(ObjTsubo* this, GlobalContext* globalCtx);

s16 D_80929500 = 0;
s16 D_80929504 = 0;
s16 D_80929508 = 0;
s16 D_8092950C = 0;

const ActorInit Obj_Tsubo_InitVars = {
    ACTOR_OBJ_TSUBO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjTsubo),
    (ActorFunc)ObjTsubo_Init,
    (ActorFunc)ObjTsubo_Destroy,
    (ActorFunc)ObjTsubo_Update,
    (ActorFunc)NULL,
};

typedef struct {
    /* 0x00 */ s16 objId;
    /* 0x04 */ f32 scale;
    /* 0x08 */ Gfx* unk8;
    /* 0x0C */ Gfx* unkC;
    /* 0x10 */ s16 radius;
    /* 0x12 */ s16 height;
    /* 0x14 */ ObjTsuboUnkFunc unk14;
    /* 0x18 */ ObjTsuboUnkFunc unk18;
    /* 0x1C */ ObjTsuboUnkFunc unk1C;

} ObjTsuboData;

ObjTsuboData sPotTypeData[4] = {
    { GAMEPLAY_DANGEON_KEEP, 0.197f,
        gameplay_dangeon_keep_DL_017EA0,
        gameplay_dangeon_keep_DL_018090,
        12, 32,
        func_80927A78, 
        func_80927FCC,
        func_8092860C
    },
    {
        OBJECT_RACETSUBO, 0.29549998f,
        object_racetsubo_DL_000278,
        object_racetsubo_DL_001610,
        18, 45,
        func_80927D2C,
        func_809282F0,
        func_80928904
    },
    {
        OBJECT_TSUBO, 0.197f,
        object_tsubo_DL_0017C0,
        object_tsubo_DL_001960,
        12, 32,
        func_80927A78,
        func_80927FCC,
        func_8092860C
    },
    {
        GAMEPLAY_DANGEON_KEEP, 0.197f,
        gameplay_dangeon_keep_DL_017EA0,
        gameplay_dangeon_keep_DL_018090,
        12, 32,
        func_80927A78,
        func_80927FCC,
        func_8092860C
    },
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x05CBFFBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 12, 30, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

s32 func_809275C0(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 chestFlag = -1;
    s32 unkParams = (OBJ_TSUBO_P001F(&this->actor) << 2) | 0xFF01;

    if (unkParams & 3 & 0xF) {
        chestFlag = ((unkParams & (0xFF << 2)) >> 2) & 0xFF;
    }

    return (chestFlag < 0) == true || !Flags_GetTreasure(globalCtx, chestFlag);
}

void func_8092762C(ObjTsubo* this, GlobalContext* globalCtx) {
    if (!OBJ_TSUBO_P0010(&this->actor) && OBJ_TSUBO_ZROT(&this->actor) != 2) {
        Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, OBJ_TSUBO_P000F(&this->actor) * 0x10);
    }
}

void func_80927690(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 itemDrop;

    if (this->unk197 == 0 && OBJ_TSUBO_ZROT(&this->actor) != 2) {
        itemDrop = func_800A8150(OBJ_TSUBO_P003F(&this->actor));
        if (itemDrop > ITEM00_NO_DROP) {
            Item_DropCollectible(globalCtx, &this->actor.world.pos, (OBJ_TSUBO_PFE00(&this->actor) << 8) | itemDrop);
            this->unk197 = 1;
        }
    }
}

void func_80927714(ObjTsubo* this, GlobalContext* globalCtx, s32 arg2) {
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_MKK, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 2);
}

void func_8092776C(ObjTsubo* this, GlobalContext* globalCtx, s32 arg2) {
    Actor* child;
    s32 sp38;

    if (func_809275C0(this, globalCtx) != 0) {
        sp38 = (OBJ_TSUBO_P001F(&this->actor) * 4) | 0xFF01;
        child = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_SW, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, (u32)Rand_Next() >> 0x10, 0, sp38);
        if (child != NULL) {
            child->parent = &this->actor;
            child->velocity.y = 0.0f;
            child->speedXZ = 0.0f;
        }
    }
}

void func_80927818(ObjTsubo* this, GlobalContext* globalCtx, s32 arg2) {
    if (OBJ_TSUBO_ZROT(&this->actor) == 1) {
        func_80927714(this, globalCtx, arg2);
    } else if (OBJ_TSUBO_ZROT(&this->actor) == 2) {
        func_8092776C(this, globalCtx, arg2);
    }
}

s32 func_80927864(ObjTsubo* this, GlobalContext* globalCtx) {
    return globalCtx->sceneNum != SCENE_HAKUGIN_BS && globalCtx->sceneNum != SCENE_INISIE_BS;
}

void func_8092788C(ObjTsubo* this, GlobalContext* globalCtx) {
    if (this->unk197 == 0 && globalCtx->roomCtx.currRoom.num != this->homeRoom) {
        this->unk197 = 1;
    }
}

void ObjTsubo_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTsubo* this = (ObjTsubo*)thisx;
    s32 pad;
    s32 type;
    s16 pad2;
    s32 sp2C;

    type = OBJ_TSUBO_GET_TYPE(&this->actor);
    sp2C = OBJ_TSUBO_ZROT(&this->actor);

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, sPotTypeData[type].scale);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    Collider_InitCylinder(globalCtx, &this->cylinderCollider);
    Collider_SetCylinder(globalCtx, &this->cylinderCollider, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->cylinderCollider);
    this->cylinderCollider.dim.radius = sPotTypeData[type].radius;
    this->cylinderCollider.dim.height = sPotTypeData[type].height;
    this->actor.colChkInfo.mass = 0xFF;
    this->objBankIdx = Object_GetIndex(&globalCtx->objectCtx, sPotTypeData[type].objId);
    if (this->objBankIdx < 0) {
        Actor_MarkForDeath(&this->actor);
    }
    else {
        this->actor.shape.shadowScale = 1.8f;
        this->homeRoom = this->actor.room;
        if (type != OBJ_TSUBO_TYPE_3 && sp2C != 2) {
            if (func_800A81A4(globalCtx, OBJ_TSUBO_P003F(&this->actor), OBJ_TSUBO_PFE00(&this->actor)) != 0) {
                this->unk198 = 1;
            }
        }
        if (type == OBJ_TSUBO_TYPE_3 || sp2C != 2 || !func_809275C0(this, globalCtx)) {
            this->unk19A = -1;
        }
        func_80928914(this);
    }
}

void ObjTsubo_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;
    ObjTsubo* this = (ObjTsubo*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->cylinderCollider);
}

void func_80927A78(ObjTsubo* this, GlobalContext* globalCtx) {
    s16 rot;
    s32 i;
    s32 phi_s0;
    s32 pad;
    Vec3f pos;
    Vec3f vel;
    ObjTsuboData* typeData;
    f32 randf;
    f32 sinf;
    f32 cosf;
    f32 scale;
    s32 pad2;

    typeData = &sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)];
    
    for (i = 0, rot = 0; i < 18; rot += 0x4E20, i++) {
        sinf = Math_SinS(rot);
        cosf = Math_CosS(rot);
        pos.x = sinf * 8.0f;
        pos.y = Rand_ZeroOne() * 12.0f + 2.0f;
        pos.z = cosf * 8.0f;
        vel.x = pos.x * 0.23f;
        vel.y = Rand_ZeroOne() * 5.0f + 2.5f;
        vel.z = pos.z * 0.23f;
        Math_Vec3f_Sum(&pos, &this->actor.world.pos, &pos);
        randf = Rand_ZeroOne();

        if (randf < 0.2f) {
            phi_s0 = 0x60;
        }
        else if (randf < 0.6f) {
            phi_s0 = 0x40;
        }
        else {
            phi_s0 = 0x20;
        }
        scale = Rand_ZeroOne() * 110.0f + 15.0f;
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, &this->actor.world.pos, -260, phi_s0, 0x14, 0, 0, scale, 0, 0, 50, -1, typeData->objId, typeData->unkC);
    }
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 0x14, 0x32, 1);
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 0xA, 0x50, 1);
}

void func_80927D2C(ObjTsubo* this, GlobalContext* globalCtx) {
    s16 rot;
    s32 phi_s0;
    s32 i;
    ObjTsuboData* typeData;
    Vec3f pos;
    Vec3f vel;
    f32 randf;
    f32 sinf;
    f32 cosf;
    f32 scale;
    s32 pad[2];

    typeData = &sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)];

    for (i = 0, rot = 0; i < 20; rot += 0x4E20, i++) {
        sinf = Math_SinS(rot);
        cosf = Math_CosS(rot);
        pos.x = sinf * 10.0f;
        pos.y = Rand_ZeroOne() * 20.0f + 2.0f;
        pos.z = cosf * 10.0f;
        vel.x = pos.x * 0.3f;
        vel.y = Rand_ZeroOne() * 10.0f + 2.0f;
        vel.z = pos.z * 0.3f;
        Math_Vec3f_Sum(&pos, &this->actor.world.pos, &pos);
        randf = Rand_ZeroOne();
        if (randf < 0.2f) {
            phi_s0 = 0xE0;
        }
        else if (randf < 0.6f) {
            phi_s0 = 0xC0;
        }
        else {
            phi_s0 = 0xA0;
        }
        scale = Rand_ZeroOne() * 160.0f + 15.0f;
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, &this->actor.world.pos, -340, phi_s0, 0x14, 0, 0, scale, 0, 0, 50, -1, typeData->objId, typeData->unkC);
    }
    func_800BBFB0(globalCtx, &this->actor.world.pos, 50.0f, 2, 0x28, 0x32, 1);
    func_800BBFB0(globalCtx, &this->actor.world.pos, 50.0f, 2, 0x14, 0x50, 1);
}

void func_80927FCC(ObjTsubo* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;
    s16 rot;
    s32 i;
    s32 phi_s0;
    Vec3f pos;
    Vec3f vel;
    Vec3f* worldPos;
    ObjTsuboData* typeData;
    f32 sinf;
    f32 cosf;
    f32 scale;
    s32 pad;

    worldPos = &this->actor.world.pos;
    typeData = &sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)];
    pos.y = worldPos->y + this->actor.depthInWater;

    for (rot = 0, i = 0; i < 5; i++, rot += 0x10000/5) {
        pos.x = Math_SinS((s32)(Rand_ZeroOne() * 6000) + rot) * 15.0f + worldPos->x;
        pos.z = Math_CosS((s32)(Rand_ZeroOne() * 6000) + rot) * 15.0f + worldPos->z;
        EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 350);
    }
    pos.x = worldPos->x;
    pos.z = worldPos->z;
    EffectSsGRipple_Spawn(globalCtx, &pos, 0xC8, 0x258, 0);
    for (i = 0, rot = 0; i < 13; rot += 0x4E20, i++) {
        sinf = Math_SinS(rot);
        cosf = Math_CosS(rot);
        pos.x = sinf * 8.0f;
        pos.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        pos.z = cosf * 8.0f;
        vel.x = pos.x * 0.2f;
        vel.y = (Rand_ZeroOne() * 4.0f) + 2.0f;
        vel.z = pos.z * 0.2f;
        Math_Vec3f_Sum(&pos, worldPos, &pos);
        if (Rand_ZeroOne() < .2f) {
            phi_s0 = 0x40;
        }
        else {
            phi_s0 = 0x20;
        }
        scale = Rand_ZeroOne() * 105.0f + 10.0f;
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, worldPos, -170, phi_s0, 0x32, 5, 0, scale, 0, 0, 70, -1, typeData->objId, typeData->unkC);
    }
}

void func_809282F0(ObjTsubo* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;
    s32 pad;
    s16 rot;
    s32 i;
    Vec3f pos;
    Vec3f vel;
    Vec3f* worldPos;
    ObjTsuboData* typeData;
    f32 sinf;
    f32 cosf;
    s32 phi_s0;
    s16 scale;

    typeData = &sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)];
    worldPos = &this->actor.world.pos;
    pos.y = this->actor.world.pos.y + this->actor.depthInWater;

    for (rot = 0, i = 0; i < 5; i++, rot += 0x10000/5) {
        pos.x = Math_SinS((s32)(Rand_ZeroOne() * 6000) + rot) * 30.0f + worldPos->x;
        pos.z = Math_CosS((s32)(Rand_ZeroOne() * 6000) + rot) * 30.0f + worldPos->z;
        EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 0x15E);
    }
    pos.x = worldPos->x;
    pos.z = worldPos->z;
    EffectSsGRipple_Spawn(globalCtx, &pos, 0x12C, 0x2BC, 0);

    for (i = 0, rot = 0; i < 15; rot += 0x4E20, i++) {
        sinf = Math_SinS(rot);
        cosf = Math_CosS(rot);
        pos.x = sinf * 10.0f;
        pos.y = (Rand_ZeroOne() * 15.0f) + 2.0f;
        pos.z = cosf * 10.0f;
        vel.x = pos.x * 0.3f;
        vel.y = (Rand_ZeroOne() * 4.0f) + 2.0f;
        vel.z = pos.z * 0.3f;
        Math_Vec3f_Sum(&pos, worldPos, &pos);

        phi_s0 = Rand_ZeroOne() < 0.2f ? 0xC0 : 0xA0;
        scale = (Rand_ZeroOne() * 150.0f) + 10.0f;

        EffectSsKakera_Spawn(globalCtx, &pos, &vel, worldPos, -170, phi_s0, 0x32, 5, 0, scale, 0, 0, 70, -1, typeData->objId, typeData->unkC);
    }
}

void func_8092860C(ObjTsubo* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;
    s32 i;
    s16 rot;
    s32 phi_s0;
    Vec3f pos;
    Vec3f vel;
    ObjTsuboData* typeData;
    f32 randf;
    f32 temp_f20;
    f32 cosf;
    f32 sinf;

    typeData = &sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)];

    for (i = 0, rot = 0; i < 13; i++, rot += 0x4E20) {
        randf = Rand_ZeroOne();
        temp_f20 = (1.0f - SQ(randf)) * 4.8f + 3.2f;
        if (this) { }
        sinf = Math_SinS(rot);
        cosf = Math_CosS(rot);
        pos.x = sinf * temp_f20;
        pos.y = (Rand_ZeroOne() * 15.0f) + 2.0f;
        pos.z = cosf * temp_f20;
        vel.x = pos.x * 0.4f;
        vel.y = (Rand_ZeroOne() * 4.0f) + 4.0f;
        vel.z = pos.z * 0.4f;
        Math_Vec3f_Sum(&pos, &this->actor.world.pos, &pos);

        if (Rand_ZeroOne() < 0.2f) {
            phi_s0 = 0x40;
        }
        else {
            phi_s0 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, &this->actor.world.pos, -170, phi_s0, 0x32, 3, 0, (Rand_ZeroOne() * 105.0f) + 10.0f, 0, 0, 70, -1, typeData->objId, typeData->unkC);
    }
    for (i = 0; i < 7; i++) {
        EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 20.0f, 30.0f, 40.0f, (Rand_ZeroOne() * 0.06f) + 0.09f);
        EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 10.0f, 10.0f, 10.0f, (Rand_ZeroOne() * 0.08f) + 0.09f);
    }
}

void func_80928904(ObjTsubo* this, GlobalContext* globalCtx2) {

}

void func_80928914(ObjTsubo* this) {
    this->actionFunc = func_80928928;
}

void func_80928928(ObjTsubo* this, GlobalContext* globalCtx) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0x44);
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objBankIdx)) {
        this->actor.objBankIndex = this->objBankIdx;
        func_809289B4(this);
    }
}

void func_809289B4(ObjTsubo* this) {
    this->actor.draw = func_809294B0;
    this->actor.flags |= 0x10;
    this->unk195 = 0;
    this->actionFunc = func_809289E4;
}

void func_809289E4(ObjTsubo* this, GlobalContext* globalCtx) {
    ObjTsuboData* typeData;
    s32 pad2;
    s32 type;
    s32 pad3;
    s32 sp3C;

    type = OBJ_TSUBO_GET_TYPE(&this->actor);
    sp3C = (this->cylinderCollider.base.acFlags & 2) != 0;
    if (sp3C != 0) {
        this->cylinderCollider.base.acFlags &= ~2;
    }
    if ((this->cylinderCollider.base.ocFlags1 & 2) != 0) {
        this->cylinderCollider.base.ocFlags1 &= ~2;
    }
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.room = -1;
        this->actor.flags |= 0x10;
        if (type != OBJ_TSUBO_TYPE_3 && func_800A817C(OBJ_TSUBO_P003F(&this->actor))) {
            func_80927690(this, globalCtx);
        }
        func_80927818(this, globalCtx, 0);
        func_800B8E58(&this->actor, NA_SE_PL_PULL_UP_POT);
        func_80928D6C(this);
    }
    else if (this->pad19B != 0 || (sp3C != 0 && (this->cylinderCollider.info.acHitInfo->toucher.dmgFlags & 0x058BFFBC) != 0)) {
        typeData = &sPotTypeData[type];
        this->pad19B = 0;
        if ((this->actor.bgCheckFlags & 0x20) && this->actor.depthInWater > 15.0f) {
            typeData->unk1C(this, globalCtx);
        }
        else {
            typeData->unk14(this, globalCtx);
        }
        if (type == OBJ_TSUBO_TYPE_3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        func_80927818(this, globalCtx, 1);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EV_POT_BROKEN);
        if (func_80927864(this, globalCtx) != 0) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else {
        if (this->unk195 == 0) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0x44);
            if ((this->actor.bgCheckFlags & 1) && DynaPoly_GetActor(&globalCtx->colCtx, this->actor.floorBgId) == NULL) {
                this->unk195 = 1;
                this->actor.flags &= ~0x10;
            }
        }
        if (this->actor.xzDistToPlayer < 800.0f || gSaveContext.entranceIndex == 0xD010) {
            Collider_UpdateCylinder(&this->actor, &this->cylinderCollider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->cylinderCollider.base);
            if (this->actor.xzDistToPlayer < 150.0f) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->cylinderCollider.base);
                if (this->actor.xzDistToPlayer < 100.0f) {
                    s32 absYawDiff;
                    s16 yawDiff = this->actor.yawTowardsPlayer - GET_PLAYER(globalCtx)->actor.world.rot.y;
                    
                    if (yawDiff < 0) {
                        absYawDiff = -yawDiff;
                    }
                    else {
                        absYawDiff = yawDiff;
                    }
                    if (absYawDiff >= 0x5556) {
                        Actor_PickUp(&this->actor, globalCtx, 0, 36.0f, 30.0f);
                    }
                }
            }
        }
    }
}

void func_80928D6C(ObjTsubo* this) {
    this->actionFunc = func_80928D80;
}

void func_80928D80(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f pos;
    s32 bgId;

    func_8092788C(this, globalCtx);
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        this->actor.room = globalCtx->roomCtx.currRoom.num;
        Actor_MoveWithGravity(&this->actor);
        this->actor.flags &= ~(1 << 26);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0xC5);
        func_80928E74(this);
    }
    else {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y + 20.0f;
        pos.z = this->actor.world.pos.z;
        this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &bgId, &this->actor, &pos);
    }
}

void func_80928E74(ObjTsubo* this) {
    this->unk194 = 0x50;
    this->actor.colChkInfo.mass = 180;
    D_80929500 = (Rand_ZeroOne() - 0.78f) * 4500.0f;
    D_80929508 = (Rand_ZeroOne() - 0.5f) * 2000.0f;
    D_80929504 = 0;
    D_8092950C = 0;
    this->actionFunc = func_80928F18;
}

void func_80928F18(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 pad;
    ObjTsuboData* typeData;
    s32 type;
    s32 pad2;
    s32 atHit;

    type = OBJ_TSUBO_GET_TYPE(&this->actor);
    atHit = (this->cylinderCollider.base.atFlags & AT_HIT) != 0;
    if (atHit) {
        this->cylinderCollider.base.atFlags &= ~AT_HIT;
    }
    func_8092788C(this, globalCtx);

    if (this->unk194 > 0) {
        this->unk194 -= 1;
    }
    typeData = &sPotTypeData[type];
    if ((this->actor.bgCheckFlags & 0xB) || atHit || this->unk194 <= 0) {
        typeData->unk14(this, globalCtx);
        if (type == OBJ_TSUBO_TYPE_3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EV_POT_BROKEN);
        if (func_80927864(this, globalCtx)) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else if (this->actor.bgCheckFlags & 0x40) {
        typeData->unk18(this, globalCtx);
        if (type == OBJ_TSUBO_TYPE_3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EV_POT_BROKEN);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0x28, NA_SE_EV_DIVE_INTO_WATER_L);
        if (func_80927864(this, globalCtx)) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else {
        Actor_MoveWithGravity(&this->actor);
        Math_StepToS(&D_80929504, D_80929500, 150);
        Math_StepToS(&D_8092950C, D_80929508, 150);
        this->actor.shape.rot.x += D_80929504;
        this->actor.shape.rot.y += D_8092950C;
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0xC5);
        Collider_UpdateCylinder(&this->actor, &this->cylinderCollider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->cylinderCollider.base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->cylinderCollider.base);
    }
}

void func_809291DC(ObjTsubo* this) {
    this->actor.draw = NULL;
    this->actor.flags |= 0x10;

    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    this->unk197 = 0;
    this->actor.shape.rot.x = this->actor.home.rot.x;
    this->actor.world.rot.x = this->actor.home.rot.x;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.shape.rot.y = this->actor.home.rot.y;
    this->actor.world.rot.y = this->actor.home.rot.y;
    Actor_SetScale(&this->actor, 0.0f);
    this->unk194 = 0x7F;
    this->actionFunc = func_8092926C;
}

void func_8092926C(ObjTsubo* this, GlobalContext* globalCtx) {
    f32 scale;

    if (this->unk194 > 0) {
        this->unk194 -= 1;
        if (this->unk194 == 0) {
            this->actor.draw = func_809294B0;
        }
    }
    else {
        scale = sPotTypeData[OBJ_TSUBO_GET_TYPE(&this->actor)].scale;
        if (Math_StepToF(&this->actor.scale.x, scale, scale * 0.1f) != 0) {
            this->actor.flags |= 0x04000000;
            func_809289B4(this);
        }
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void ObjTsubo_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTsubo* this = (ObjTsubo*)thisx;

    this->actionFunc(this, globalCtx);
    if (this->actor.draw == NULL) {
        this->actor.shape.shadowDraw = NULL;
    }
    else if (this->actor.projectedPos.z < 811.0f) {
        if (this->actor.projectedPos.z > 300.0f) {
            this->actor.shape.shadowAlpha = (811 - (s32)this->actor.projectedPos.z) >> 1;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        }
        else if (this->actor.projectedPos.z > -10.0f) {
            this->actor.shape.shadowAlpha = 255;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        }
        else {
            this->actor.shape.shadowDraw = NULL;
        }
    }
    else {
        this->actor.shape.shadowDraw = NULL;
    }
    if (this->unk197 == 0) {
        if (this->unk198 != 0) {
            globalCtx->actorCtx.unk5 |= 8;
            this->actor.flags |= 0x10;
        }
        if (this->unk19A >= 0) {
            if (this->unk19A == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALGOLD_ROLL);
                if (Rand_ZeroOne() < 0.1f) {
                    this->unk19A = Rand_S16Offset(40, 80);
                }
                else {
                    this->unk19A = 8;
                }
            }
            else {
                this->unk19A -= 1;
            }
        }
    }
}

void func_809294B0(Actor* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;

    Gfx_DrawDListOpa(globalCtx, sPotTypeData[OBJ_TSUBO_GET_TYPE(this)].unk8);
}
