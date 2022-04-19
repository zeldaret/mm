/*
 * File: z_en_geg.c
 * Overlay: ovl_En_Geg
 * Description: Goron With Don Gero's Mask
 */

#include "z_en_geg.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"
#include "objects/object_taisou/object_taisou.h"
#include "objects/object_hakugin_demo/object_hakugin_demo.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnGeg*)thisx)

void EnGeg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB217C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB221C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2520(EnGeg* this, GlobalContext* globalCtx);
void func_80BB26EC(EnGeg* this, GlobalContext* globalCtx);
void func_80BB27D4(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2944(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2A54(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2B1C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2E00(EnGeg* this, GlobalContext* globalCtx);
void func_80BB2F7C(EnGeg* this, GlobalContext* globalCtx);
void func_80BB30B4(EnGeg* this, GlobalContext* globalCtx);
void func_80BB31B8(EnGeg* this, GlobalContext* globalCtx);
void func_80BB32AC(EnGeg* this, GlobalContext* globalCtx);
void func_80BB3318(EnGeg* this, GlobalContext* globalCtx);
void func_80BB347C(EnGeg* this, GlobalContext* globalCtx);

const ActorInit En_Geg_InitVars = {
    ACTOR_EN_GEG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGeg),
    (ActorFunc)EnGeg_Init,
    (ActorFunc)EnGeg_Destroy,
    (ActorFunc)EnGeg_Update,
    (ActorFunc)EnGeg_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 0 }, 100 },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, 0, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static AnimationInfoS sAnimations[] = {
    { &object_oF1d_map_Anim_011D98, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_011D98, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_oF1d_map_Anim_012DE0, 2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_oF1d_map_Anim_012DE0, 2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_oF1d_map_Anim_012DE0, -2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_oF1d_map_Anim_003E28, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_003E28, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_oF1d_map_Anim_0039D8, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_taisou_Anim_0016C8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_004DD4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_00283C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_007764, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005EE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_002C48, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_0031D8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005790, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_003650, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_hakugin_demo_Anim_002704, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_hakugin_demo_Anim_003378, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_oF1d_map_Anim_0135E8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_oF1d_map_Anim_014CE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

u16 func_80BB16D0(EnGeg* this) {
    switch (this->unk_496) {
        case 0xD5E:
            return 0xD5F;
        case 0xD5F:
            return 0xD60;
        case 0xD60:
            return 0xD61;
        case 0xD62:
            return 0xD63;
        case 0xD64:
            return 0xD65;
        case 0xD66:
            return 0xD67;
        case 0xD67:
            return 0xD68;
        case 0xD68:
            return 0xD69;
        case 0xD6A:
            return 0xD6B;
        case 0xD6B:
            return 0xD6C;
        case 0xD6C:
            return 0xD6D;
        case 0xD6E:
            return 0xD6F;
        case 0xD70:
            return 0xD71;
        case 0xD71:
            return 0xD72;
        case 0xD73:
            return 0xD74;
        case 0xD74:
            return 0xD75;
        case 0xD89:
            return 0xD8A;
    }
    return 0;
}

void func_80BB178C(EnGeg* this, GlobalContext* globalCtx) {
    Vec3f sp34 = this->actor.world.pos;
    Collider* collider;

    if (this->unk_230 & 1) {
        this->colliderSphere.dim.worldSphere.center.x = sp34.x;
        this->colliderSphere.dim.worldSphere.center.y = sp34.y;
        this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
        this->colliderSphere.dim.worldSphere.center.z = sp34.z;
        this->colliderSphere.dim.modelSphere.radius = 20;
        this->colliderSphere.dim.worldSphere.radius =
            this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
        collider = &this->colliderSphere.base;
    } else {
        f32 radius = 24.0f;
        f32 height = 62.0f;

        this->colliderCylinder.dim.pos.x = sp34.x;
        this->colliderCylinder.dim.pos.y = sp34.y;
        this->colliderCylinder.dim.pos.z = sp34.z;
        this->colliderCylinder.dim.radius = radius;
        this->colliderCylinder.dim.height = height;
        collider = &this->colliderCylinder.base;
    }

    if (collider != NULL) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, collider);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 5);
    }
}

s32 func_80BB18FC(EnGeg* this, Actor* actor) {
    if (actor->bgCheckFlags & 1) {
        f32 sp24 = Math_Vec3f_DistXZ(&this->actor.world.pos, &actor->world.pos);
        f32 sp20 = Math_Vec3f_DiffY(&this->actor.world.pos, &actor->world.pos);

        if ((sp24 < 150.0f) && (fabsf(sp20) < 5.0f)) {
            this->unk_230 |= 0x20;
            actor->speedXZ = 0.0f;
            actor->velocity.y = 0.0f;
            this->actor.child = actor;
            actor->parent = &this->actor;
            return true;
        }
    }
    return false;
}

Vec3f* func_80BB19C0(Vec3f* arg0, EnGeg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32 = player->actor.world.rot.y + 0x4000;
    s16 sp30;
    f32 sp2C;
    f32 sp28;

    sp40.x = (Math_SinS(sp32) * 50.0f) + player->actor.world.pos.x;
    sp40.y = player->actor.world.pos.y;
    sp40.z = (Math_CosS(sp32) * 50.0f) + player->actor.world.pos.z;

    sp2C = Math_Vec3f_DistXZ(&this->actor.world.pos, &sp40);
    sp30 = player->actor.world.rot.y - 0x4000;

    sp34.x = (Math_SinS(sp30) * 50.0f) + player->actor.world.pos.x;
    sp34.y = player->actor.world.pos.y;
    sp34.z = (Math_CosS(sp30) * 50.0f) + player->actor.world.pos.z;

    if (Math_Vec3f_DistXZ(&this->actor.world.pos, &sp34) < sp2C) {
        // clang-format off
        *arg0 = sp40; return arg0;
        // clang-format on
    } else {
        *arg0 = sp34;
    }
    return arg0;
}

u8 func_80BB1B14(EnGeg* this, GlobalContext* globalCtx) {
    Actor* explosive;
    Actor* mm = SubS_FindActor(globalCtx, NULL, ACTORCAT_ITEMACTION, ACTOR_EN_MM);

    if (mm != NULL) {
        this->unk_4B0 = Math_Vec3f_Yaw(&this->actor.world.pos, &mm->world.pos);
        if (func_80BB18FC(this, mm)) {
            return 1;
        }
    }

    explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if ((explosive->id == ACTOR_EN_BOM) && func_80BB18FC(this, explosive)) {
            this->unk_4B0 = Math_Vec3f_Yaw(&this->actor.world.pos, &explosive->world.pos);
            if (this->unk_230 & 0x200) {
                return 0;
            }

            if (((EnBom*)explosive)->isPowderKeg == 0) {
                return 2;
            }

            return 3;
        }
        explosive = explosive->next;
    }

    this->unk_230 &= ~0x200;
    return 0;
}

void func_80BB1C1C(EnGeg* this) {
    u16 i;

    this->unk_49C[0] = this->actor.cutscene;

    for (i = 1; i < ARRAY_COUNT(this->unk_49C); i++) {
        this->unk_49C[i] = ActorCutscene_GetAdditionalCutscene(this->unk_49C[i - 1]);
    }
}

void func_80BB1C8C(EnGeg* this) {
    if (DECR(this->unk_240) == 0) {
        this->unk_23E++;
        if (this->unk_23E >= 3) {
            this->unk_240 = Rand_S16Offset(30, 30);
            this->unk_23E = 0;
        }
    }
}

void func_80BB1D04(EnGeg* this) {
    f32 temp;

    if (this->unk_230 & 1) {
        temp = this->actor.shape.yOffset;
    } else {
        temp = 58.0f;
    }

    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = temp + this->actor.world.pos.y;
    this->actor.focus.pos.z = this->actor.world.pos.z;
    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
}

s32 func_80BB1D64(EnGeg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;
    s16 yaw = (this->actor.yawTowardsPlayer - this->unk_46E) - this->actor.shape.rot.y;

    Math_SmoothStepToS(&this->unk_46A, yaw, 4, 0x2AA8, 1);
    this->unk_46A = CLAMP(this->unk_46A, -0x1FFE, 0x1FFE);

    yaw = (this->actor.yawTowardsPlayer - this->unk_46A) - this->actor.shape.rot.y;
    Math_SmoothStepToS(&this->unk_46E, yaw, 4, 0x2AA8, 1);
    this->unk_46E = CLAMP(this->unk_46E, -0x1C70, 0x1C70);

    if (this->unk_230 & 0x20) {
        sp40 = player->actor.world.pos;
    } else {
        sp40 = player->actor.world.pos;
        sp40.y = player->bodyPartsPos[7].y + 3.0f;
    }

    sp34 = this->actor.world.pos;
    sp34.y += 70.0f;

    yaw = Math_Vec3f_Pitch(&sp34, &sp40);
    Math_SmoothStepToS(&this->unk_468, yaw - this->unk_46C, 4, 0x2AA8, 1);
    this->unk_468 = CLAMP(this->unk_468, -0x1C70, 0x1C70);

    yaw = Math_Vec3f_Pitch(&sp34, &sp40);
    Math_SmoothStepToS(&this->unk_46C, yaw - this->unk_468, 4, 0x2AA8, 1);
    this->unk_46C = CLAMP(this->unk_46C, -0x1C70, 0x1C70);

    return true;
}

void func_80BB1FCC(EnGeg* this, GlobalContext* globalCtx) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[this->unk_248].segment);
    SkelAnime_Update(&this->skelAnime);
}

void func_80BB2020(EnGeg* this, GlobalContext* globalCtx) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[this->unk_248].segment);
    SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, this->unk_4AC);
}

s32 func_80BB2088(EnGeg* this, GlobalContext* globalCtx) {
    if (DECR(this->unk_242) != 0) {
        this->unk_468 = 0;
        this->unk_46A = 0;
        this->unk_230 &= ~2;
        this->unk_46C = 0;
        this->unk_46E = 0;
        return true;
    }

    if (Actor_IsFacingAndNearPlayer(&this->actor, 300.0f, 0x7FF8) &&
        ((this->unk_4AC == 5) || ((this->unk_4AC == 13) && (this->unk_496 == 0xD69)))) {
        this->unk_230 |= 2;
        func_80BB1D64(this, globalCtx);
    } else {
        if (this->unk_230 & 2) {
            this->unk_242 = 20;
        }
        this->unk_230 &= ~2;
        this->unk_468 = 0;
        this->unk_46A = 0;
        this->unk_46C = 0;
        this->unk_46E = 0;
    }

    return true;
}

void func_80BB217C(EnGeg* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_248)) {
        this->unk_4AC = 5;
        func_80BB2020(this, globalCtx);
        Actor_SetScale(&this->actor, 0.01f);
        this->unk_230 = 0;
        this->actor.shape.shadowScale = 20.0f;
        this->actor.gravity = -1.0f;
        func_80BB1C1C(this);
        this->actionFunc = func_80BB221C;
        this->actor.targetMode = 3;
    }
}

void func_80BB221C(EnGeg* this, GlobalContext* globalCtx) {
    u8 sp27 = func_80BB1B14(this, globalCtx);

    if (sp27 != 0) {
        this->unk_230 &= ~8;
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_230 & 4)) {
            if (sp27 == 1) {
                this->unk_496 = 0xD66;
                this->unk_49A = this->unk_49C[3];
            } else if (sp27 == 2) {
                this->unk_496 = 0xD64;
                this->unk_49A = this->unk_49C[2];
                this->unk_230 &= ~4;
            } else if (sp27 == 3) {
                this->unk_230 |= 0x200;
                this->unk_496 = 0xD64;
                this->unk_49A = this->unk_49C[2];
                this->unk_230 &= ~4;
            }
            Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
            this->actionFunc = func_80BB2520;
            this->actor.flags &= ~ACTOR_FLAG_10000;
        } else if (this->actor.xzDistToPlayer < 300.0f) {
            this->unk_230 |= 4;
            this->actor.flags |= ACTOR_FLAG_10000;
            func_800B8614(&this->actor, globalCtx, 300.0f);
        }
    } else {
        this->unk_230 &= ~4;
        if (gSaveContext.save.weekEventReg[35] & 0x40) {
            if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_230 & 8)) {
                this->unk_496 = 0xD62;
                Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
                this->unk_230 &= ~8;
                this->actionFunc = func_80BB27D4;
            } else if ((this->actor.xzDistToPlayer < 300.0f) && this->actor.isTargeted) {
                func_800B8614(&this->actor, globalCtx, 300.0f);
                this->unk_230 |= 8;
            }
        } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_230 & 8)) {
            gSaveContext.save.weekEventReg[35] |= 0x40;
            this->unk_496 = 0xD5E;
            this->unk_49A = this->unk_49C[0];
            Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
            this->actionFunc = func_80BB2520;
            this->unk_230 &= ~8;
            this->actor.flags &= ~ACTOR_FLAG_10000;
        } else if (this->actor.xzDistToPlayer < 300.0f) {
            this->actor.flags |= ACTOR_FLAG_10000;
            func_800B8614(&this->actor, globalCtx, 300.0f);
            this->unk_230 |= 8;
        }
    }
}

void func_80BB2520(EnGeg* this, GlobalContext* globalCtx) {
    if (this->unk_230 & 0x10) {
        ActorCutscene_Stop(this->unk_498);
        this->unk_230 &= ~0x10;
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk_498 = this->unk_49A;
        ActorCutscene_SetIntentToPlay(this->unk_498);
        return;
    }

    if (ActorCutscene_GetCanPlayNext(this->unk_498)) {
        ActorCutscene_StartAndSetFlag(this->unk_498, &this->actor);
        this->unk_230 |= 0x10;

        switch (this->unk_496) {
            case 0xD5E:
            case 0xD5F:
                this->actionFunc = func_80BB26EC;
                break;

            case 0xD64:
                this->unk_230 &= ~0x20;
                this->actionFunc = func_80BB2A54;
                break;

            case 0xD66:
                this->unk_248 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OF1D_MAP);
                if (this->unk_248 >= 0) {
                    this->unk_4AC = 19;
                    func_80BB2020(this, globalCtx);
                }
                this->unk_230 |= 0x20;
                this->actionFunc = func_80BB2944;
                break;

            case 0xD67:
                this->unk_498 = this->unk_49C[5];
                this->actionFunc = func_80BB2B1C;
                break;

            case 0xD69:
            case 0xD72:
            case 0xD75:
            case 0xD8B:
                this->unk_248 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OF1D_MAP);
                if (this->unk_248 >= 0) {
                    this->unk_4AC = 4;
                    func_80BB2020(this, globalCtx);
                }
                this->actionFunc = func_80BB2E00;
                break;
        }
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk_498 = this->unk_49A;
        ActorCutscene_SetIntentToPlay(this->unk_498);
    }
}

void func_80BB26EC(EnGeg* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_496) {
            case 0xD5E:
                this->unk_49A = this->unk_49C[1];
                this->actionFunc = func_80BB2520;
                break;

            case 0xD61:
                ActorCutscene_Stop(this->unk_498);
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_230 &= ~0x10;
                this->actionFunc = func_80BB221C;
                return;
        }

        this->unk_496 = func_80BB16D0(this);
        Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
    }
}

void func_80BB27D4(EnGeg* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_496) {
            case 0xD63:
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80BB221C;
                break;

            case 0xD69:
                this->unk_49A = this->unk_49C[6];
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80BB2520;
                break;

            case 0xD6D:
            case 0xD6F:
            case 0xD8A:
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80BB31B8;
                break;

            case 0xD72:
            case 0xD75:
            case 0xD8B:
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_230 &= ~0x10;
                this->unk_49A = this->unk_49C[7];
                this->actionFunc = func_80BB2520;
                break;

            default:
                this->unk_496 = func_80BB16D0(this);
                Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
                break;
        }
    }
}

void func_80BB2944(EnGeg* this, GlobalContext* globalCtx) {
    u8 sp27 = Message_GetState(&globalCtx->msgCtx);
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_4AC].animation);

    if (this->unk_4AC == 19) {
        if (curFrame == lastFrame) {
            this->unk_4AC = 6;
            func_80BB2020(this, globalCtx);
        }
    } else if ((sp27 == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_496 == 0xD67) {
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_49A = this->unk_49C[4];
            this->actionFunc = func_80BB2520;
        } else {
            this->unk_496 = func_80BB16D0(this);
            func_80151938(globalCtx, this->unk_496);
        }
    }
}

void func_80BB2A54(EnGeg* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_496 == 0xD65) {
            ActorCutscene_Stop(this->unk_498);
            this->unk_230 &= ~0x10;
            this->unk_244 = 65;
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->actionFunc = func_80BB347C;
        } else {
            this->unk_496 = func_80BB16D0(this);
            Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
        }
    }
}

void func_80BB2B1C(EnGeg* this, GlobalContext* globalCtx) {
    Vec3f sp74;
    f32 temp_f20;
    s16 i;
    f32 sp68;

    this->actor.child->world.pos = this->unk_4B4;
    this->actor.child->shape.rot = this->actor.shape.rot;

    if (ActorCutscene_GetCurrentIndex() != this->unk_49C[4]) {
        if (ActorCutscene_GetCanPlayNext(this->unk_498)) {
            gSaveContext.save.weekEventReg[37] |= 8;
            if (this->actor.child != NULL) {
                Actor_MarkForDeath(this->actor.child);
            }
            this->unk_230 |= 0x10;
            ActorCutscene_StartAndSetFlag(this->unk_498, &this->actor);
            this->unk_496 = 0xD68;
            func_80151938(globalCtx, this->unk_496);
            this->unk_248 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_TAISOU);
            if (this->unk_248 >= 0) {
                this->unk_4AC = 13;
                func_80BB2020(this, globalCtx);
            }
            this->actionFunc = func_80BB27D4;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->unk_498);
        }
    } else {
        temp_f20 = this->unk_4E0 * 0.005f;
        sp68 = this->unk_4E0 * 0.07f;

        sp74.x = Rand_Centered() * temp_f20;
        sp74.y = Rand_Centered() * temp_f20;
        sp74.z = Rand_Centered() * temp_f20;

        this->actor.child->scale.x *= 0.98f;
        this->actor.child->scale.y *= 0.98f;
        this->actor.child->scale.z *= 0.98f;

        if (this->unk_4E0 > 70) {
            for (i = 0; i < ARRAY_COUNT(this->unk_4C0); i++) {
                this->unk_4C0[i].x *= temp_f20;
                this->unk_4C0[i].y *= temp_f20;
                this->unk_4C0[i].z *= temp_f20;
                EffectSsHahen_Spawn(globalCtx, &this->unk_4B4, &this->unk_4C0[i], &sp74, 1, sp68, 1, 15,
                                    gameplay_keep_DL_06AB30);
            }
        }
        this->unk_4E0--;
    }
    func_8019F570(&this->actor.projectedPos, 1);
    func_8019F4AC(&this->actor.projectedPos, NA_SE_EN_GOLON_SIRLOIN_EAT - SFX_FLAG);
}

void func_80BB2E00(EnGeg* this, GlobalContext* globalCtx) {
    s16 sp2E = this->skelAnime.curFrame;
    s16 sp2C = Animation_GetLastFrame(sAnimations[this->unk_4AC].animation);

    if (this->unk_4AC == 2) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (sp2E == sp2C) {
            ActorCutscene_Stop(this->unk_498);
            this->unk_4AC = 20;
            func_80BB2020(this, globalCtx);
            this->actionFunc = func_80BB30B4;
        } else if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_STAND_IMT);
        }
    } else if (this->unk_4AC == 4) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
            this->unk_230 |= 1;
            this->actor.shape.yOffset = 14.0f;
            if (this->unk_496 == 0xD69) {
                func_80BB19C0(&this->unk_4E4, this, globalCtx);
                this->actionFunc = func_80BB2F7C;
            } else {
                this->actionFunc = func_80BB3318;
            }
        } else if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SIT_IMT);
        }
    }
}

void func_80BB2F7C(EnGeg* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_4E4), 4, 1000, 1);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    if ((this->actor.xzDistToPlayer < 150.0f) && (fabsf(this->actor.playerHeightRel) < 10.0f) &&
        (this->actor.bgCheckFlags & 1)) {
        this->unk_4AC = 2;
        this->actor.speedXZ = 0.0f;
        this->unk_230 &= ~1;
        this->actor.shape.yOffset = 0.0f;
        func_80BB2020(this, globalCtx);
        this->actionFunc = func_80BB2E00;
    } else {
        this->actor.speedXZ = 5.0f;
        Actor_MoveWithGravity(&this->actor);
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->unk_230 & 0x80) {
            func_800B9010(&this->actor, NA_SE_EN_GOLON_SIRLOIN_ROLL - SFX_FLAG);
        } else {
            this->unk_230 |= 0x80;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        }
    }
}

void func_80BB30B4(EnGeg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (player->transformation == PLAYER_FORM_GORON) {
            this->unk_496 = 0xD6A;
        } else if (Player_GetMask(globalCtx) == PLAYER_MASK_DON_GERO) {
            this->unk_496 = 0xD89;
        } else {
            this->unk_496 = 0xD6E;
        }
        Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
        this->actionFunc = func_80BB27D4;
        this->actor.flags &= ~ACTOR_FLAG_10000;
    } else if (this->actor.xzDistToPlayer < 150.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, 150.0f);
    }
}

void func_80BB31B8(EnGeg* this, GlobalContext* globalCtx) {
    s32 getItemId = GI_MASK_DON_GERO;

    if (INV_CONTENT(ITEM_MASK_DON_GERO) == ITEM_MASK_DON_GERO) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_DON_GERO) {
            this->unk_496 = 0xD8B;
            getItemId = GI_RUPEE_PURPLE;
        } else {
            this->unk_496 = 0xD73;
            getItemId = GI_RUPEE_PURPLE;
        }
    } else {
        this->unk_496 = 0xD70;
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        gSaveContext.save.weekEventReg[61] |= 1;
        if (getItemId == GI_MASK_DON_GERO) {
            this->unk_230 |= 0x40;
        }
        this->actionFunc = func_80BB32AC;
    } else {
        Actor_PickUp(&this->actor, globalCtx, getItemId, 300.0f, 300.0f);
    }
}

void func_80BB32AC(EnGeg* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, this->unk_496, &this->actor);
        this->actionFunc = func_80BB27D4;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80BB3318(EnGeg* this, GlobalContext* globalCtx) {
    static Vec3f D_80BB4044[] = {
        { -550.0f, 8.0f, 550.0f },
        { 220.0f, 43.0f, 525.0f },
    };
    s16 sp46;
    f32 sp40;

    if (this->unk_4D8 < 2) {
        sp46 = Math_Vec3f_Yaw(&this->actor.world.pos, &D_80BB4044[this->unk_4D8]);
        sp40 = Math_Vec3f_DistXZ(&this->actor.world.pos, &D_80BB4044[this->unk_4D8]);
        Math_SmoothStepToS(&this->actor.world.rot.y, sp46, 4, 1000, 1);
        if (sp40 < 20.0f) {
            this->unk_4D8++;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
        func_800AE930(&globalCtx->colCtx, Effect_GetByIndex(this->unk_4DC), &this->actor.world.pos, 18.0f,
                      this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
    }

    if (ActorCutscene_GetCurrentIndex() != this->unk_49C[7]) {
        func_800AEF44(Effect_GetByIndex(this->unk_4DC));
        Actor_MarkForDeath(&this->actor);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 10.0f, 0.2f, 1.0f);
        Actor_MoveWithGravity(&this->actor);
    }

    func_800B9010(&this->actor, NA_SE_EN_GOLON_SIRLOIN_ROLL - SFX_FLAG);
}

void func_80BB347C(EnGeg* this, GlobalContext* globalCtx) {
    if (DECR(this->unk_244) == 0) {
        this->unk_244 = 65;
        this->actionFunc = func_80BB221C;
    }
}

void EnGeg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGeg* this = THIS;
    s32 pad2;
    s32 sp34[] = { 0x3E, 0xF64 };

    if (gSaveContext.save.weekEventReg[61] & 1) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_oF1d_map_Skel_011AC8, &object_oF1d_map_Anim_012DE0,
                       this->jointTable, this->morphTable, 18);

    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitSphere(globalCtx, &this->colliderSphere);
    Collider_SetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    if (this->actor.update != NULL) {
        this->unk_248 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OF1D_MAP);
        if (this->unk_248 < 0) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    Effect_Add(globalCtx, &this->unk_4DC, 4, 0, 0, &sp34);
    thisx->draw = NULL;
    this->unk_4E0 = 100;
    this->actor.draw = EnGeg_Draw;
    this->actionFunc = func_80BB217C;
}

void EnGeg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGeg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
    Effect_Destroy(globalCtx, this->unk_4DC);
}

void EnGeg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGeg* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80BB1FCC(this, globalCtx);
    func_80BB2088(this, globalCtx);
    func_80BB1C8C(this);
    SubS_FillLimbRotTables(globalCtx, this->unk_238, this->unk_232, ARRAY_COUNT(this->unk_238));
    func_80BB1D04(this);
    func_80BB178C(this, globalCtx);
}

s32 func_80BB3728(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4, s32 arg5) {
    Vec3f sp7C;
    Vec3f sp70 = gZeroVec3f;
    Vec3s sp68;
    MtxF sp28;

    Matrix_MultiplyVector3fByState(&sp70, &sp7C);
    Matrix_CopyCurrentState(&sp28);
    func_8018219C(&sp28, &sp68, 0);
    *arg2 = sp7C;

    if (!arg4 && !arg5) {
        arg3->x = sp68.x;
        arg3->y = sp68.y;
        arg3->z = sp68.z;
        return true;
    }

    if (arg5) {
        sp68.z = arg0;
        sp68.y = arg1;
    }
    Math_SmoothStepToS(&arg3->x, sp68.x, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&arg3->y, sp68.y, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&arg3->z, sp68.z, 3, 0x2AA8, 0xB6);

    return true;
}

s32 EnGeg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnGeg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80BB407C = { -1500.0f, 1500.0f, 0.0f };
    EnGeg* this = THIS;
    Vec3f sp38 = { 1.0f, 5.0f, -0.5f };
    Vec3f sp2C = { -1.0f, 5.0f, -0.5f };

    if (limbIndex == 17) {
        if (!(this->unk_230 & 0x40)) {
            func_8012C28C(globalCtx->state.gfxCtx);

            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, object_oF1d_map_DL_004DB0);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }

        sp38.x += Rand_Centered();
        sp38.y += 2.0f * Rand_Centered();
        sp38.z += Rand_Centered();

        sp2C.x += Rand_Centered();
        sp2C.y += 2.0f * Rand_Centered();
        sp2C.z += Rand_Centered();

        Matrix_MultiplyVector3fByState(&D_80BB407C, &this->unk_4B4);
        Matrix_StatePush();
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_MultiplyVector3fByState(&sp38, &this->unk_4C0[0]);
        Matrix_MultiplyVector3fByState(&sp2C, &this->unk_4C0[1]);
        Matrix_StatePop();
    }
}

void EnGeg_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnGeg* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    switch (limbIndex) {
        case 17:
            if (this->unk_230 & 2) {
                phi_v1 = true;
            } else {
                phi_v1 = false;
            }

            if (this->unk_242 != 0) {
                phi_v0 = true;
            } else {
                phi_v0 = false;
            }

            func_80BB3728(this->unk_468 + this->unk_46C + 0x4000,
                          this->unk_46A + this->unk_46E + this->actor.shape.rot.y + 0x4000, &this->unk_470,
                          &this->unk_47C, phi_v0, phi_v1);
            Matrix_StatePop();
            Matrix_InsertTranslation(this->unk_470.x, this->unk_470.y, this->unk_470.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_47C.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_47C.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_47C.z, MTXMODE_APPLY);
            Matrix_StatePush();
            break;

        case 10:
            if (this->unk_230 & 2) {
                phi_v1 = true;
            } else {
                phi_v1 = false;
            }

            if (this->unk_242 != 0) {
                phi_v0 = true;
            } else {
                phi_v0 = false;
            }

            func_80BB3728(this->unk_46C + 0x4000, this->unk_46E + this->actor.shape.rot.y + 0x4000, &this->unk_484,
                          &this->unk_490, phi_v0, phi_v1);
            Matrix_StatePop();
            Matrix_InsertTranslation(this->unk_484.x, this->unk_484.y, this->unk_484.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_490.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_490.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_490.z, MTXMODE_APPLY);
            Matrix_StatePush();
            break;
    }
}

void func_80BB3BE0(EnGeg* this, GlobalContext* globalCtx) {
    static TexturePtr D_80BB4088[] = {
        object_oF1d_map_Tex_010438,
        object_oF1d_map_Tex_010C38,
        object_oF1d_map_Tex_011038,
        object_oF1d_map_Tex_010838,
    };
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BB4088[this->unk_23E]));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnGeg_OverrideLimbDraw, EnGeg_PostLimbDraw,
                                   EnGeg_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BB3CB4(EnGeg* this, GlobalContext* globalCtx) {
    f32 sp24 = globalCtx->state.frames * this->actor.speedXZ * 1400.0f;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                             this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(sp24, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_oF1d_map_DL_0091A8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnGeg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGeg* this = THIS;

    if (this->unk_230 & 1) {
        func_80BB3CB4(this, globalCtx);
    } else {
        func_80BB3BE0(this, globalCtx);
    }
}
