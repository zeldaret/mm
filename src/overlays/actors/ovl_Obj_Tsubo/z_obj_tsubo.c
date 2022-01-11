/*
 * File: z_obj_tsubo.c
 * Overlay: ovl_Obj_Tsubo
 * Description: Pots
 */

#include "z_obj_tsubo.h"

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

extern s16 D_80929500;
extern s16 D_80929504;
extern s16 D_80929508;
extern s16 D_8092950C;

typedef struct {
    /* 0x00 */ s16 objId;
    char pad[2];
    /* 0x04 */ f32 scale;
    /* 0x08 */ char pad8[0x04];
    /* 0x0C */ Gfx* unkC;
    /* 0x10 */ s16 radius;
    /* 0x12 */ s16 height;
    /* 0x14 */ ObjTsuboUnkFunc unk14;
    /* 0x18 */ ObjTsuboUnkFunc unk18;
    /* 0x1C */ ObjTsuboUnkFunc unk1C;

} T_80929530;

extern T_80929530 D_80929530[4];

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809295B0 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x05CBFFBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 12, 30, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809295DC[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_809295B0;
extern InitChainEntry D_809295DC[];

s32 func_809275C0(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 chestFlag = -1;
    s32 unkParams = ((this->actor.params & 0x1F) << 2) | 0xFF01;

    if (unkParams & 3 & 0xF) {
        chestFlag = ((unkParams & (0xFF << 2)) >> 2) & 0xFF;
    }

    return (chestFlag < 0) == true || !Actor_GetChestFlag(globalCtx, chestFlag);
}

void func_8092762C(ObjTsubo* this, GlobalContext* globalCtx) {
    if (!((this->actor.params >> 4) & 1) && this->actor.home.rot.z != 2) {
        Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, (this->actor.params & 0xF) * 0x10);
    }
}

void func_80927690(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 itemDrop;

    if (this->unk197 == 0 && this->actor.home.rot.z != 2) {
        itemDrop = func_800A8150(this->actor.params & 0x3F);
        if (itemDrop > ITEM00_NO_DROP) {
            Item_DropCollectible(globalCtx, &this->actor.world.pos, (((this->actor.params >> 9) & 0x7F) << 8) | itemDrop);
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
        sp38 = ((this->actor.params & 0x1F) * 4) | 0xFF01;
        child = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_SW, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, (u32)Rand_Next() >> 0x10, 0, sp38);
        if (child != NULL) {
            child->parent = &this->actor;
            child->velocity.y = 0.0f;
            child->speedXZ = 0.0f;
        }
    }
}

void func_80927818(ObjTsubo* this, GlobalContext* globalCtx, s32 arg2) {
    if (this->actor.home.rot.z == 1) {
        func_80927714(this, globalCtx, arg2);
    } else if (this->actor.home.rot.z == 2) {
        func_8092776C(this, globalCtx, arg2);
    }
}

s32 func_80927864(ObjTsubo* this, GlobalContext* globalCtx) {
    return globalCtx->sceneNum != SCENE_HAKUGIN_BS && globalCtx->sceneNum != SCENE_INISIE_BS;
}

void func_8092788C(ObjTsubo* this, GlobalContext* globalCtx) {
    if (this->unk197 == 0 && globalCtx->roomCtx.currRoom.num != this->unk196) {
        this->unk197 = 1;
    }
}

void ObjTsubo_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTsubo* this = (ObjTsubo*)thisx;
    s32 pad;
    s32 sp34;
    s16 pad2;
    s32 sp2C;

    sp34 = (this->actor.params >> 7) & 3;
    sp2C = this->actor.home.rot.z;

    Actor_ProcessInitChain(&this->actor, D_809295DC);
    Actor_SetScale(&this->actor, D_80929530[sp34].scale);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    Collider_InitCylinder(globalCtx, &this->cylinderCollider);
    Collider_SetCylinder(globalCtx, &this->cylinderCollider, &this->actor, &D_809295B0);
    Collider_UpdateCylinder(&this->actor, &this->cylinderCollider);
    this->cylinderCollider.dim.radius = D_80929530[sp34].radius;
    this->cylinderCollider.dim.height = D_80929530[sp34].height;
    this->actor.colChkInfo.mass = 0xFF;
    this->unk199 = Object_GetIndex(&globalCtx->objectCtx, D_80929530[sp34].objId);
    if (this->unk199 < 0) {
        Actor_MarkForDeath(&this->actor);
    }
    else {
        this->actor.shape.shadowScale = 1.8f;
        this->unk196 = this->actor.room;
        if (sp34 != 3 && sp2C != 2) {
            if (func_800A81A4(globalCtx, this->actor.params & 0x3F, (this->actor.params >> 9) & 0x7F) != 0) {
                this->unk198 = 1;
            }
        }
        if (sp34 == 3 || sp2C != 2 || !func_809275C0(this, globalCtx)) {
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
    T_80929530* temp_s4;
    f32 temp_f0;
    f32 sinf;
    f32 cosf;
    s32 pad2;

    temp_s4 = &D_80929530[(this->actor.params >> 7) & 3];
    
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
        temp_f0 = Rand_ZeroOne();

        if (temp_f0 < 0.2f) {
            phi_s0 = 0x60;
        }
        else if (temp_f0 < 0.6f) {
            phi_s0 = 0x40;
        }
        else {
            phi_s0 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, &this->actor.world.pos, -260, phi_s0, 0x14, 0, 0, Rand_ZeroOne() * 110.0f + 15.0f, 0, 0, 0x32, -1, temp_s4->objId, temp_s4->unkC);
    }
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 0x14, 0x32, 1);
    func_800BBFB0(globalCtx, &this->actor.world.pos, 30.0f, 2, 0xA, 0x50, 1);
}

void func_80927D2C(ObjTsubo* this, GlobalContext* globalCtx) {
    s16 rot;
    s32 phi_s0;
    s32 i;
    T_80929530* temp_s4;
    Vec3f pos;
    Vec3f vel;
    f32 temp_f0;
    f32 sinf;
    f32 cosf;
    s32 pad[2];

    temp_s4 = &D_80929530[(this->actor.params >> 7) & 3];

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
        temp_f0 = Rand_ZeroOne();
        if (temp_f0 < 0.2f) {
            phi_s0 = 0xE0;
        }
        else if (temp_f0 < 0.6f) {
            phi_s0 = 0xC0;
        }
        else {
            phi_s0 = 0xA0;
        }
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, &this->actor.world.pos, -0x154, phi_s0, 0x14, 0, 0, (Rand_ZeroOne() * 160.0f) + 15.0f, 0, 0, 0x32, -1, temp_s4->objId, temp_s4->unkC);
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
    T_80929530* temp_s6;
    f32 sinf;
    f32 cosf;
    s32 pad;

    worldPos = &this->actor.world.pos;
    temp_s6 = &D_80929530[(this->actor.params >> 7) & 3];
    pos.y = worldPos->y + this->actor.depthInWater;

    for (rot = 0, i = 0; i < 5; i++, rot += 0x3333) {
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
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, worldPos, -170, phi_s0, 0x32, 5, 0, (Rand_ZeroOne() * 105.0f) + 10.0f, 0, 0, 0x46, -1, temp_s6->objId, temp_s6->unkC);
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
    T_80929530* temp_s6;
    f32 sinf;
    f32 cosf;
    s32 phi_s0;
    s16 scale;

    temp_s6 = &D_80929530[(this->actor.params >> 7) & 3];
    worldPos = &this->actor.world.pos;
    pos.y = this->actor.world.pos.y + this->actor.depthInWater;

    for (rot = 0, i = 0; i < 5; i++, rot += 0x3333) {
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

        EffectSsKakera_Spawn(globalCtx, &pos, &vel, worldPos, -170, phi_s0, 0x32, 5, 0, scale, 0, 0, 0x46, -1, temp_s6->objId, temp_s6->unkC);
    }
}

void func_8092860C(ObjTsubo* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = (GlobalContext*)globalCtx2;
    s32 phi_s1;
    s16 phi_s2;
    s32 phi_s0;
    Vec3f spCC;
    Vec3f spC0;
    T_80929530* temp_s6;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f4;

    temp_s6 = &D_80929530[(this->actor.params >> 7) & 3];

    for (phi_s1 = 0, phi_s2 = 0; phi_s1 < 13; phi_s1++, phi_s2 += 0x4E20) {
        temp_f0 = Rand_ZeroOne();
        temp_f20 = ((1.0f - (temp_f0 * temp_f0)) * 4.8f) + 3.2f;
        if (this);
        temp_f4 = Math_SinS(phi_s2);
        temp_f24 = Math_CosS(phi_s2);
        spCC.x = temp_f4 * temp_f20;
        spCC.y = (Rand_ZeroOne() * 15.0f) + 2.0f;
        spCC.z = temp_f24 * temp_f20;
        spC0.x = spCC.x * 0.4f;
        spC0.y = (Rand_ZeroOne() * 4.0f) + 4.0f;
        spC0.z = spCC.z * 0.4f;
        Math_Vec3f_Sum(&spCC, &this->actor.world.pos, &spCC);

        if (Rand_ZeroOne() < 0.2f) {
            phi_s0 = 0x40;
        }
        else {
            phi_s0 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &spCC, &spC0, &this->actor.world.pos, -0xAA, phi_s0, 0x32, 3, 0, (Rand_ZeroOne() * 105.0f) + 10.0f, 0, 0, 0x46, -1, temp_s6->objId, temp_s6->unkC);
    }
    for (phi_s1 = 0; phi_s1 < 7; phi_s1++) {
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
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0x44);
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk199)) {
        this->actor.objBankIndex = this->unk199;
        func_809289B4(this);
    }
}

void func_809289B4(ObjTsubo* this) {
    this->actor.draw = func_809294B0;
    this->actor.flags |= 0x10;
    this->unk195 = 0;
    this->actionFunc = func_809289E4;
}

#ifdef NON_MATCHING
void func_809289E4(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 sp44;
    s16 temp_v0_5;
    s32 sp3C;
    //s32 temp_a2;
    s32 temp_v1;
    //u8 temp_v0_2;

    sp44 = (this->actor.params >> 7) & 3;
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
        if ((sp44 != 3) && (func_800A817C(this->actor.params & 0x3F) != 0)) {
            func_80927690(this, globalCtx);
        }
        func_80927818(this, globalCtx, 0);
        func_800B8E58(&this->actor, 0x086F);
        func_80928D6C(this);
    }
    else if ((this->pad19B != 0) || ((sp3C != 0) && ((this->cylinderCollider.info.acHitInfo->toucher.dmgFlags & 0x058BFFBC) != 0))) {
        this->pad19B = 0;
        if ((this->actor.bgCheckFlags & 0x20) && this->actor.depthInWater > 15.0f) {
            //T_80929530* temp_v0_3;
            //temp_v0_3 = &D_80929530[sp44];
            //sp30 = temp_v0_3;
            D_80929530[sp44].unk1C(this, globalCtx);
        }
        else {
            //T_80929530* temp_v0_4;
            //temp_v0_4 = &D_80929530[sp44];
            //sp30 = temp_v0_4;
            D_80929530[sp44].unk14(this, globalCtx);
        }
        if (sp44 == 3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        func_80927818(this, globalCtx, 1);
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x14, 0x2887);
        if (func_80927864(this, globalCtx) != 0) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else {
        if (this->unk195 == 0) {
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 15.0f, 0.0f, 0x44);
            if (((this->actor.bgCheckFlags & 1) != 0) && (DynaPoly_GetActor(&globalCtx->colCtx, this->actor.floorBgId) == 0)) {
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
                    s32 phi_v1;
                    temp_v0_5 = this->actor.yawTowardsPlayer - GET_PLAYER(globalCtx)->actor.world.rot.y;
                    phi_v1 = temp_v0_5;
                    if (temp_v0_5 < 0) {
                        phi_v1 = -temp_v0_5;
                    }
                    if (phi_v1 >= 0x5556) {
                        func_800B8A1C(&this->actor, globalCtx, 0, 36.0f, 30.0f);
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809289E4.s")
#endif

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
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
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

#ifdef NON_MATCHING
void func_80928F18(ObjTsubo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    s32 sp34;
    s32 pad3;
    s32 sp2C;

    sp34 = (this->actor.params >> 7) & 3;
    sp2C = (this->cylinderCollider.base.atFlags & 2) != 0;
    if (sp2C) {
        this->cylinderCollider.base.atFlags &= ~2;
    }
    func_8092788C(this, globalCtx);

    if (this->unk194 > 0) {
        this->unk194 -= 1;
    }
    if ((this->actor.bgCheckFlags & 0xB) || sp2C || this->unk194 <= 0) {
        D_80929530[sp34].unk14(this, globalCtx);
        if (sp34 == 3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x14, 0x2887);
        if (func_80927864(this, globalCtx)) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else if (this->actor.bgCheckFlags & 0x40) {
        D_80929530[sp34].unk18(this, globalCtx);
        if (sp34 == 3) {
            func_8092762C(this, globalCtx);
        }
        else {
            func_80927690(this, globalCtx);
        }
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x14, 0x2887);
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x28, 0x28C5);
        if (func_80927864(this, globalCtx)) {
            Actor_MarkForDeath(&this->actor);
        }
        else {
            func_809291DC(this);
        }
    }
    else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928F18.s")
#endif


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809291DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092926C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809294B0.s")
