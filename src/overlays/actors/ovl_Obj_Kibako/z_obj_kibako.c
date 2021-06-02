#include "z_obj_kibako.h"

#define FLAGS 0x04000010

#define THIS ((ObjKibako*)thisx)

void ObjKibako_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80927334(Actor* thisx, GlobalContext* globalCtx);

void func_809261B0(ObjKibako* this, GlobalContext* globalCtx);
void func_809262BC(ObjKibako* this);
void func_80926318(ObjKibako* this, GlobalContext* globalCtx);
void func_8092650C(ObjKibako* this, GlobalContext* globalCtx);
void func_809267EC(ObjKibako* this, GlobalContext* globalCtx);
void func_80926B40(ObjKibako* this);
void func_80926B54(ObjKibako* this, GlobalContext* globalCtx);
void func_80926BE0(ObjKibako* this);
void func_80926BF4(ObjKibako* this, GlobalContext* globalCtx);
void func_80926EF4(ObjKibako* this);
void func_80926F08(ObjKibako* this, GlobalContext* globalCtx);
void func_8092703C(ObjKibako* this);
void func_809270F8(ObjKibako* this, GlobalContext* globalCtx);


const ActorInit Obj_Kibako_InitVars = {
    ACTOR_OBJ_KIBAKO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjKibako),
    (ActorFunc)ObjKibako_Init,
    (ActorFunc)ObjKibako_Destroy,
    (ActorFunc)ObjKibako_Update,
    (ActorFunc)NULL,
};

static u16 D_80927380 = 0;
static s16 D_80927384 = 0;
static s16 D_80927388 = 0;
static s16 D_8092738C = 0;

//sCylinderInit
static ColliderCylinderInit D_809273B0 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00400000, 0x00, 0x02 },
        { 0x058BC79C, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 15, 30, 0, { 0, 0, 0 } },
};

//sObjectBankTable
static s16 D_809273DC[] = { GAMEPLAY_DANGEON_KEEP, OBJECT_KIBAKO };

//sParticleDisplayLists
static Gfx* D_809273E0[] = { 0x05007980, 0x06001A70 };

//sMainDisplayLists
static Gfx* D_809273E8[] = { 0x05007890, 0x06001180 };

//sInitChain
static InitChainEntry D_809273F0[] = {
    ICHAIN_F32_DIV1000(gravity, -1500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -18000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 60, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 60, ICHAIN_STOP),
};

#ifndef NON_MATCHING
void func_809261B0(ObjKibako* this, GlobalContext* globalCtx) {
    s32 collectible;

    if (this->unk198 == 0) {
        collectible = func_800A8150(this->actor.params & 0x3F);
        if (collectible >= 0) {
            Item_DropCollectible(globalCtx, &this->actor.world.pos, collectible | (((this->actor.params >> 8) & 0x7F) << 8));
            this->unk198 = 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_809261B0.asm")
#endif

#ifndef NON_MATCHING
void func_80926224(ObjKibako *this) {
    if ((this->actor.projectedPos.z < 370.0f) && (this->actor.projectedPos.z > -10.0f)) {
        this->actor.shape.shadowDraw = func_800B4024;
        this->actor.shape.shadowScale = 1.4f;
        this->actor.shape.shadowAlpha = (this->actor.projectedPos.z < 200.0f) ? 100 : (400 - ((s32)this->actor.projectedPos.z)) >> 1;
    } else {
        this->actor.shape.shadowDraw = NULL;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926224.asm")
#endif

#ifndef NON_MATCHING
void func_809262BC(ObjKibako *this) {
    s16 angle = this->actor.world.rot.y;

    if ((angle & 0x3FFF) != 0) {
        angle = Math_ScaledStepToS(&this->actor.world.rot.y, (s16)(angle + 0x2000) & 0xC000, 0x640);
        (&this->actor.shape.rot)->y = this->actor.world.rot.y;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_809262BC.asm")
#endif

#ifndef NON_MATCHING
void func_80926318(ObjKibako* this, GlobalContext* globalCtx) {
    s16 angle;
    s32 pad;

    if (this->actor.xzDistToPlayer < 100.0f) {
        angle = this->actor.yawTowardsPlayer - globalCtx->actorCtx.actorList[2].first->world.rot.y;
        if (ABS_ALT(angle) >= 0x5556) {
            func_800B8A1C(&this->actor, globalCtx, 0, 36.0f, 30.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926318.asm")
#endif

#ifndef NON_MATCHING
void func_80926394(ObjKibako* this, GlobalContext* globalCtx) {
    if ((this->unk198 == 0) && (globalCtx->roomContext.currRoom.num != this->unk199)) {
        this->unk198 = 1;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926394.asm")
#endif

#ifndef NON_MATCHING
void ObjKibako_Init(Actor* thisx, GlobalContext* globalCtx2) {
    ObjKibako* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 whichBankIndex;

    whichBankIndex = (this->actor.params >> 0xF) & 1;
    Actor_ProcessInitChain(&this->actor, D_809273F0);
    Actor_SetScale(&this->actor, 0.15f);
    if (!whichBankIndex) {
        this->actor.uncullZoneForward = 4000.0f;
    } else {
        this->actor.uncullZoneForward = 800.0f;
    }
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_809273B0);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->actor.colChkInfo.mass = 0xFF;
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, D_809273DC[whichBankIndex]);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->unk199 = this->actor.room;
    func_80926B40(this);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/ObjKibako_Init.asm")
#endif

#ifndef NON_MATCHING
void ObjKibako_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjKibako* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/ObjKibako_Destroy.asm")
#endif

#ifndef NON_MATCHING
void func_8092650C(ObjKibako* this, GlobalContext* globalCtx) {
    s16 angle;
    s32 i;
    Vec3f* worldPos = &this->actor.world.pos;
    Vec3f pos;
    Vec3f velocity;

    for (i = 0, angle = 0; i < 12; i++, angle += 0x4E20) {
        f32 sn = Math_SinS(angle);
        f32 cs = Math_CosS(angle);
        f32 temp_rand;
        s16 phi_s0;

        pos.x = sn * 16.0f;
        pos.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        pos.z = cs * 16.0f;
        velocity.x = pos.x * 0.2f;
        velocity.y = (Rand_ZeroOne() * 6.0f) + 2.0f;
        velocity.z = pos.z * 0.2f;
        pos.x += worldPos->x;
        pos.y += worldPos->y;
        pos.z += worldPos->z;
        temp_rand = Rand_ZeroOne();
        if (temp_rand < 0.1f) {
            phi_s0 = 0x60;
        } else if (temp_rand < 0.7f) {
            phi_s0 = 0x40;
        } else {
            phi_s0 = 0x20;
        }

        EffectSsKakera_Spawn(globalCtx, &pos, &velocity, worldPos, -200, phi_s0, 20, 0, 0,
                             (Rand_ZeroOne() * 38.0f) + 10.0f, 0, 0, 60, -1,
                             D_809273DC[(this->actor.params >> 0xF) & 1], D_809273E0[(this->actor.params >> 0xF) & 1]);
    }

    func_800BBFB0(globalCtx, worldPos, 40.0f, 3, 0x32, 0x8C, 1);
    func_800BBFB0(globalCtx, worldPos, 40.0f, 2, 0x14, 0x50, 1);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_8092650C.asm")
#endif

#ifndef NON_MATCHING
void func_809267EC(ObjKibako* this, GlobalContext* globalCtx) {
    s16 angle;
    s32 i;
    Vec3f* worldPos = &this->actor.world.pos;
    Vec3f pos;
    Vec3f velocity;

    pos.y = worldPos->y + this->actor.yDistToWater;
    for (angle = 0, i = 0; i < 5; i++, angle += 0x3333) {
        pos.x = (Math_SinS(((s32)(Rand_ZeroOne() * 6000.0f)) + angle) * 15.0f) + worldPos->x;
        pos.z = (Math_CosS(((s32)(Rand_ZeroOne() * 6000.0f)) + angle) * 15.0f) + worldPos->z;
        EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 350);
    }
    pos.x = worldPos->x;
    pos.z = worldPos->z;
    EffectSsGRipple_Spawn(globalCtx, &pos, 200, 600, 0);

    for (i = 0, angle = 0; i < 12; i++, angle += 0x4E20) {
        f32 sn = Math_SinS(angle);
        f32 cs = Math_CosS(angle);
        f32 temp_rand;
        s16 phi_s0;

        pos.x = sn * 16.0f;
        pos.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        pos.z = cs * 16.0f;
        velocity.x = pos.x * 0.18f;
        velocity.y = (Rand_ZeroOne() * 4.0f) + 2.0f;
        velocity.z = pos.z * 0.18f;
        pos.x += worldPos->x;
        pos.y += worldPos->y;
        pos.z += worldPos->z;
        temp_rand = Rand_ZeroOne();
        phi_s0 = (temp_rand < 0.2f) ? 0x40 : 0x20;

        EffectSsKakera_Spawn(globalCtx, &pos, &velocity, worldPos, -180, phi_s0, 50, 5, 0,
                        (Rand_ZeroOne() * 35.0f) + 10.0f, 0, 0, 70, -1,
                        D_809273DC[(this->actor.params >> 0xF) & 1], D_809273E0[(this->actor.params >> 0xF) & 1]);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_809267EC.asm")
#endif

#ifndef NON_MATCHING
void func_80926B40(ObjKibako* this) {
    this->actionFunc = func_80926B54;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926B40.asm")
#endif

#ifndef NON_MATCHING
void func_80926B54(ObjKibako* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800B78B8(globalCtx, &this->actor, 18.0f, 15.0f, 0.0f, 0x45);
    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex) != 0) {
        this->actor.draw = func_80927334;
        this->actor.objBankIndex = this->bankIndex;
        func_80926BE0(this);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926B54.asm")
#endif

#ifndef NON_MATCHING
void func_80926BE0(ObjKibako* this) {
    this->actionFunc = func_80926BF4;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926BE0.asm")
#endif

#ifndef NON_MATCHING
void func_80926BF4(ObjKibako* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad1;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        func_80926EF4(this);
        this->actor.room = -1;
        this->actor.colChkInfo.mass = 0x78;
        if (func_800A817C(this->actor.params & 0x3F)) {
            func_809261B0(this, globalCtx);
        }
        func_800B8E58(this, 0x878);
        return;
    } else if (((this->actor.bgCheckFlags & 0x20)) && (this->actor.yDistToWater > 19.0f)) {
        func_809267EC(this, globalCtx);
        func_809261B0(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world.pos, 20, 0x28AA); // NA_SE_EV_WOODBOX_BREAK
        func_800F0568(globalCtx, &this->actor.world.pos, 40, 0x28C5);
        Actor_MarkForDeath(&this->actor);
        return;
    } else if ((this->collider.base.acFlags & 2)) {
        func_8092650C(this, globalCtx);
        func_809261B0(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world.pos, 0x14, 0x28AA); // NA_SE_EV_WOODBOX_BREAK
        Actor_MarkForDeath(&this->actor);
        return;
    } else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        func_809262BC(this);
        func_800B78B8(globalCtx, &this->actor, 18.0f, 15.0f, 0.0f, 0x45);
        if (!(this->collider.base.ocFlags1 & 8) && (this->actor.xzDistToPlayer > 28.0f)) {
            this->collider.base.ocFlags1 |= 8;
        }
        if ((this->actor.colChkInfo.mass != 0xFF) && (Math3D_DistanceSquared(&this->actor.world.pos, &this->actor.prevPos) < 0.01f)) {
            this->actor.colChkInfo.mass = 0xFF;
        }
        this->collider.base.acFlags &= ~(2);
        if ((this->actor.params >> 7) & 1) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
            if (this->actor.xzDistToPlayer < 800.0f) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
                func_80926318(this, globalCtx);
                return;
            }
        } else {
            if (this->actor.xzDistToPlayer < 800.0f) {
                Collider_UpdateCylinder(&this->actor, &this->collider);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
                if (this->actor.xzDistToPlayer < 180.0f) {
                    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
                    func_80926318(this, globalCtx);
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926BF4.asm")
#endif

#ifndef NON_MATCHING
void func_80926EF4(ObjKibako* this) {
    this->actionFunc = func_80926F08;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926EF4.asm")
#endif

#ifndef NON_MATCHING
void func_80926F08(ObjKibako* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f pos;
    s32 sp2C;

    func_80926394(this, globalCtx);
    if (func_800B8BFC(&this->actor, globalCtx)) {
        this->actor.room = globalCtx->roomContext.currRoom.num;
        if (fabsf(this->actor.speedXZ) < 0.1f) {
            func_80926BE0(this);
            this->collider.base.ocFlags1 &= ~(8);
            Audio_PlayActorSound2(&this->actor, 0x28AB); // NA_SE_EV_PUT_DOWN_WOODBOX
        } else {
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            func_8092703C(this);
            this->actor.flags &= 0xFBFFFFFF;
        }
        func_800B78B8(globalCtx, &this->actor, 18.0f, 15.0f, 0.0f, 0x45);
        return;
    }
    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + 20.0f;
    pos.z = this->actor.world.pos.z;
    this->actor.floorHeight = func_800C411C(&globalCtx->colCtx, &this->actor.floorPoly, &sp2C, &this->actor, &pos);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80926F08.asm")
#endif

#ifndef NON_MATCHING
void func_8092703C(ObjKibako* this) {
    f32 temp;

    D_80927380 = 0;
    temp = (Rand_ZeroOne() - 0.5f) * 1000.0f;
    D_80927388 = temp;
    D_80927384 = (Rand_ZeroOne() - 2.0f) * 1500.0f;
    D_8092738C = temp * 3.0f;
    this->timer = 80;
    this->actionFunc = func_809270F8;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_8092703C.asm")
#endif

#ifndef NON_MATCHING
void func_809270F8(ObjKibako* this, GlobalContext* globalCtx) {
    void* pad;
    void* pad2;
    s32 at_hit;

    at_hit = (this->collider.base.atFlags & 2) != 0;
    if (at_hit) {
        this->collider.base.atFlags &= ~(2);
    }
    func_80926394(this, globalCtx);
    if (this->timer > 0) {
        this->timer--;
    }
    if ((this->actor.bgCheckFlags & 0xB) || (at_hit) || (this->timer <= 0)) {
        func_8092650C(this, globalCtx);
        func_809261B0(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world.pos, 20, 0x28AA); // NA_SE_EV_WOODBOX_BREAK
        Actor_MarkForDeath(&this->actor);
    }
    else {
        if ((this->actor.bgCheckFlags & 0x40) != 0) {
            func_809267EC(this, globalCtx);
            func_809261B0(this, globalCtx);
            func_800F0568(globalCtx, &this->actor.world.pos, 20, 0x28AA); // NA_SE_EV_WOODBOX_BREAK
            func_800F0568(globalCtx, &this->actor.world.pos, 40, 0x28C5);
            Actor_MarkForDeath(&this->actor);
        }
        else {
            if (this->actor.velocity.y < -0.05f) {
                this->actor.gravity = -2.3f;
            }
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            Math_StepToS(&D_80927384, D_80927380, 0xA0);
            Math_StepToS(&D_8092738C, D_80927388, 0xA0);
            this->actor.shape.rot.x = (s16) (this->actor.shape.rot.x + D_80927384);
            this->actor.shape.rot.y = (s16) (this->actor.shape.rot.y + D_8092738C);
            func_800B78B8(globalCtx, &this->actor, 18.0f, 15.0f, 0.0f, 0x45);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_809270F8.asm")
#endif

#ifndef NON_MATCHING
void ObjKibako_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjKibako* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80926224(this);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/ObjKibako_Update.asm")
#endif

#ifndef NON_MATCHING
void func_80927334(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_809273E8[((thisx->params >> 0xF) & 1)]);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako_0x809261B0/func_80927334.asm")
#endif
