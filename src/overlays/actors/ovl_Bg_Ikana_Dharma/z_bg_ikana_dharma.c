/*
 * File: z_bg_ikana_dharma.c
 * Overlay: ovl_Bg_Ikana_Dharma
 * Description: Stone Tower Temple - Punchable Pillar Segments
 */

#include "z_bg_ikana_dharma.h"
#include "assets/objects/object_ikana_obj/object_ikana_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaDharma*)thisx)

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80BEC5C4(BgIkanaDharma* this);
void func_80BEC5E0(BgIkanaDharma* this, GlobalContext* globalCtx);
void func_80BEC758(BgIkanaDharma* this);
void func_80BEC790(BgIkanaDharma* this, GlobalContext* globalCtx);
void func_80BEC7EC(BgIkanaDharma* this);
void func_80BEC808(BgIkanaDharma* this, GlobalContext* globalCtx);

const ActorInit Bg_Ikana_Dharma_InitVars = {
    ACTOR_BG_IKANA_DHARMA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaDharma),
    (ActorFunc)BgIkanaDharma_Init,
    (ActorFunc)BgIkanaDharma_Destroy,
    (ActorFunc)BgIkanaDharma_Update,
    (ActorFunc)BgIkanaDharma_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000100, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 98, 10, 25, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 320, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 320, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1100, ICHAIN_STOP),
};

static BgIkanaDharma* D_80BECBD0;

void func_80BEC240(BgIkanaDharma* this, GlobalContext* globalCtx) {
    u32 pad;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    f32 speed;
    f32 dirX;
    f32 initialY;
    f32 dirZ;
    f32 initialRadius;
    s16 angle;
    s32 i;

    initialRadius = this->dyna.actor.scale.x * 200.0f;
    initialY = this->dyna.actor.scale.y * 50.0f;
    for (i = 0; i != 4; i++) {
        speed = (Rand_ZeroOne() * 5.0f) + 5.0f;
        angle = ((u32)Rand_Next() >> 0x12) + this->dyna.actor.world.rot.y + 0x6000;
        dirX = Math_SinS(angle);
        dirZ = Math_CosS(angle);
        pos.x = (dirX * initialRadius) + this->dyna.actor.world.pos.x;
        pos.y = this->dyna.actor.world.pos.y + initialY;
        pos.z = (dirZ * initialRadius) + this->dyna.actor.world.pos.z;
        velocity.x = speed * dirX;
        velocity.y = Rand_ZeroOne() + 0.5f;
        velocity.z = speed * dirZ;
        accel.x = velocity.x * -0.05f;
        accel.y = -0.15f;
        accel.z = velocity.z * -0.05f;
        EffectSsKiraKira_SpawnSmallYellow(globalCtx, &pos, &velocity, &accel);
    }
}

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx) {
    ColliderCylinder* temp_s1;
    s16 temp_v0;
    BgIkanaDharma* this = THIS;
    f32 phi_f20;
    GlobalContext* globalCtx2 = globalCtx;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.scale.x = 0.3f;
    this->dyna.actor.scale.y = 0.1f;
    this->dyna.actor.scale.z = 0.3f;
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_ikana_obj_Colheader_000C50);
    Collider_InitCylinder(globalCtx, &this->unk15C);
    Collider_SetCylinder(globalCtx2, &this->unk15C, &this->dyna.actor, &sCylinderInit);
    i = 0;
    temp_v0 = this->dyna.actor.params;
    if ((((s32)temp_v0 >> 5) & 1) == 0) {
        phi_f20 = this->dyna.actor.world.pos.y;
        if (i < (temp_v0 & 0xF)) {
            do {
                phi_f20 += 60.0f;
                Actor_SpawnAsChildAndCutscene(
                    &globalCtx2->actorCtx, globalCtx2, 0x273, this->dyna.actor.world.pos.x, phi_f20,
                    this->dyna.actor.world.pos.z, (s16)(s32)this->dyna.actor.shape.rot.x,
                    (s16)(s32)this->dyna.actor.shape.rot.y, (s16)(s32)this->dyna.actor.shape.rot.z, 0x20,
                    (u32)this->dyna.actor.cutscene, (s32)this->dyna.actor.unk20, NULL);
                i++;
            } while (i != (temp_v0 & 0xF));
        }
        this->dyna.actor.bgCheckFlags |= 1;
    }
    func_80BEC5C4(this);
}

void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->unk15C);
    if (this == D_80BECBD0) {
        D_80BECBD0 = NULL;
    }
}

void func_80BEC5C4(BgIkanaDharma* this) {
    this->actionFunc = &func_80BEC5E0;
    this->dyna.actor.speedXZ = 0.0f;
}

void func_80BEC5E0(BgIkanaDharma* thisx, GlobalContext* globalCtx) {
    s32 phi_v0;
    Actor* temp_a3;
    s32 temp_v0_2;
    s16 temp_v0_3;
    BgIkanaDharma* this = thisx;

    temp_a3 = globalCtx->actorCtx.actorLists[2].first;
    phi_v0 = (this->unk15C.base.acFlags & AC_HIT) != 0;
    if (phi_v0) {
        this->unk15C.base.acFlags &= ~AC_HIT;
    }
    if (phi_v0 && D_80BECBD0 == 0) { // TODO: ! or ==NULL?
        D_80BECBD0 = this;
        Flags_SetSwitch(globalCtx, BGIKANADHARMA_GET_SWITCHFLAG(&this->dyna.actor));
        temp_v0_3 = this->dyna.actor.yawTowardsPlayer + 0x8000;
        temp_v0_2 = ((s16)(temp_a3->shape.rot.y - temp_v0_3) >> 1);
        this->dyna.actor.world.rot.y = temp_v0_3 + temp_v0_2 + 0xF000;
        this->dyna.actor.speedXZ = 20.0f;
        Actor_PlaySfxAtPos(&this->dyna.actor, 0x29BDU);
        func_80BEC758(this);
    } else if (((this->dyna.actor.flags & 0x40) == 0x40) && (D_80BECBD0 == 0) &&
               (this->dyna.actor.xzDistToPlayer < 420.0f)) {
        phi_v0 = (s16)(this->dyna.actor.yawTowardsPlayer - temp_a3->shape.rot.y);
        if ((s32)phi_v0 < 0) {
            phi_v0 = -phi_v0;
            if (phi_v0) {}
        }
        if (phi_v0 >= 0x4001) {
            Collider_UpdateCylinder(&this->dyna.actor, &this->unk15C);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &thisx->unk15C.base);
        }
    }
}

void func_80BEC758(BgIkanaDharma* arg0) {
    ActorCutscene_SetIntentToPlay((s16)arg0->dyna.actor.cutscene);
    arg0->actionFunc = func_80BEC790;
}

void func_80BEC790(BgIkanaDharma* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_80BEC7EC(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80BEC7EC(BgIkanaDharma* this) {
    this->unk_1AC = 0xA;
    this->actionFunc = &func_80BEC808;
}

void func_80BEC808(BgIkanaDharma* this, GlobalContext* arg1) {
    if (this->unk_1AC > 0) {
        this->unk_1AC--;
        if (this->unk_1AC == 0) {
            if (D_80BECBD0 == this) {
                D_80BECBD0 = NULL;
            }
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
    if (Math_StepToF(&this->dyna.actor.scale.y, 0.0f, 0.0033333334f) != 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    this->dyna.actor.scale.x = this->dyna.actor.scale.y * 3.0f;
    this->dyna.actor.scale.z = this->dyna.actor.scale.y * 3.0f;
    func_80BEC240(this, arg1);
}

void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = (BgIkanaDharma*)thisx;

    this->actionFunc(this, globalCtx);
    if (this->actionFunc == func_80BEC5E0) {
        DynaPolyActor* temp_v0;
        u32 pad, pad2;
        s16 temp_v0_2;
        func_800B4AEC(globalCtx, &this->dyna.actor, 30.0f);
        temp_v0 = DynaPoly_GetActor(&globalCtx->colCtx, this->dyna.actor.floorBgId);
        if (temp_v0 == 0) {
            Actor_MoveWithGravity(&this->dyna.actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4U);
            if ((this->dyna.actor.bgCheckFlags & 2) != 0) {
                temp_v0_2 = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 3U);
                Quake_SetSpeed(temp_v0_2, 0x5420);
                Quake_SetQuakeValues(temp_v0_2, 4, 0, 0, 0);
                Quake_SetCountdown(temp_v0_2, 0xC);
                Actor_PlaySfxAtPos(&this->dyna.actor, 0x2835U); // TODO look up constant
            }
        } else {
            if (temp_v0->actor.id == 0x273) { // TODO look up constant
                this->dyna.actor.world.pos.y = temp_v0->actor.world.pos.y + 60.0f;
            } else {
                this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
            }
            this->dyna.actor.velocity.y = 0.0f;
        }
    } else {
        f32 phi_f0 = this->dyna.actor.scale.x * 300.0f;
        if (phi_f0 < 2.0f) {
            phi_f0 = 2.0f;
        }
        Actor_MoveWithGravity(&this->dyna.actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 20.0f, phi_f0, 0.0f, 5U);
    }
    Actor_SetFocus(&this->dyna.actor, 40.0f);
}

void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = (BgIkanaDharma*)thisx;
    Gfx_DrawDListOpa(globalCtx, object_ikana_obj_DL_0008C8);
}
