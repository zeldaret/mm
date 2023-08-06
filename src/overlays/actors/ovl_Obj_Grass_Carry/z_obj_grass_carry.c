/*
 * File: z_obj_grass_carry.c
 * Overlay: ovl_Obj_Grass_Carry
 * Description: Grass that the player is holding (spawned by Obj_Grass_Unit)
 */

#include "z_obj_grass_carry.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_Obj_Grass/z_obj_grass.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_800000)

#define THIS ((ObjGrassCarry*)thisx)

void ObjGrassCarry_Init(Actor* thisx, PlayState* play);
void ObjGrassCarry_Destroy(Actor* thisx, PlayState* play);
void ObjGrassCarry_Update(Actor* thisx, PlayState* play);

void func_809AB3C4(ObjGrassCarry* this);
void func_809AB3D8(ObjGrassCarry* this, PlayState* play);
void func_809AB428(ObjGrassCarry* this);
void func_809AB43C(ObjGrassCarry* this, PlayState* play);
void func_809AB474(ObjGrassCarry* this);
void func_809AB4A8(ObjGrassCarry* this, PlayState* play);
void func_809AB5FC(ObjGrassCarry* this);
void func_809AB610(ObjGrassCarry* this, PlayState* play);
void func_809AB6FC(ObjGrassCarry* this);
void func_809AB77C(ObjGrassCarry* this, PlayState* play);
void func_809ABB7C(Actor* this, PlayState* play);

ActorInit Obj_Grass_Carry_InitVars = {
    /**/ ACTOR_OBJ_GRASS_CARRY,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_FIELD_KEEP,
    /**/ sizeof(ObjGrassCarry),
    /**/ ObjGrassCarry_Init,
    /**/ ObjGrassCarry_Destroy,
    /**/ ObjGrassCarry_Update,
    /**/ NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00400000, 0x00, 0x02 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 44, 0, { 0, 0, 0 } },
};

s16 D_809ABBFC = 0;
s16 D_809ABC00 = 0;
s16 D_809ABC04 = 0;
s16 D_809ABC08 = 0;

Vec3f D_809ABC0C[] = {
    { 0.0f, 0.7071f, 0.7071f },
    { 0.7071f, 0.7071f, 0.0f },
    { 0.0f, 0.7071f, -0.7071f },
    { -0.7071f, 0.7071f, 0.0f },
};

s16 D_809ABC3C[] = { 0x6C, 0x66, 0x60, 0x54, 0x42, 0x37, 0x2A, 0x26 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -3200, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -17000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_STOP),
};

void func_809AAE60(ObjGrassCarry* this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.terminalVelocity) {
        this->actor.velocity.y = this->actor.terminalVelocity;
    }
}

void func_809AAE94(Vec3f* arg0, f32 arg1) {
    arg1 += ((Rand_ZeroOne() * 0.2f) - 0.1f) * arg1;

    arg0->x -= (arg0->x * arg1);
    arg0->y -= (arg0->y * arg1);
    arg0->z -= (arg0->z * arg1);
}

void func_809AAF18(ObjGrassCarry* this) {
    func_809AAE60(this);
    func_809AAE94(&this->actor.velocity, 0.05f);
    Actor_UpdatePos(&this->actor);
}

void func_809AAF58(ObjGrassCarry* this, PlayState* play) {
    Actor_UpdateBgCheckInfo(play, &this->actor, 7.5f, 35.0f, 0.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40 |
                                UPDBGCHECKINFO_FLAG_80);
}

void func_809AAF9C(Vec3f* arg0, s16 arg1, PlayState* play) {
    if (!(arg1 & 0x10)) {
        Item_DropCollectibleRandom(play, NULL, arg0, arg1 * 0x10);
    }
}

void func_809AAFE8(Vec3f* arg0, PlayState* play) {
    Vec3f spBC;
    Vec3f spB0;
    s32 i;
    Vec3f* ptr;

    for (i = 0; i < ARRAY_COUNT(D_809ABC0C); i++) {
        ptr = &D_809ABC0C[i];

        spB0.x = arg0->x + (ptr->x * 8.0f);
        spB0.y = arg0->y + (ptr->y * 8.0f) + 10.0f;
        spB0.z = arg0->z + (ptr->z * 8.0f);

        spBC.x = (Rand_ZeroOne() - 0.5f) * 8.0f;
        spBC.y = Rand_ZeroOne() * 10.0f;
        spBC.z = (Rand_ZeroOne() - 0.5f) * 8.0f;

        EffectSsKakera_Spawn(play, &spB0, &spBC, &spB0, -100, 64, 40, 3, 0,
                             D_809ABC3C[(s32)(Rand_ZeroOne() * 111.1f) & 7], 0, 0, 80, -1, 1, gKakeraLeafMiddle);

        spB0.x = arg0->x + (ptr->x * 16.0f);
        spB0.y = arg0->y + (ptr->y * 16.0f) + 10.0f;
        spB0.z = arg0->z + (ptr->z * 16.0f);

        spBC.x = (Rand_ZeroOne() - 0.5f) * 6.0f;
        spBC.y = Rand_ZeroOne() * 10.0f;
        spBC.z = (Rand_ZeroOne() - 0.5f) * 6.0f;

        EffectSsKakera_Spawn(play, &spB0, &spBC, &spB0, -100, 64, 40, 3, 0,
                             D_809ABC3C[(s32)(Rand_ZeroOne() * 111.1f) % 7], 0, 0, 80, -1, 1, gKakeraLeafTip);
    }
}

void ObjGrassCarry_Init(Actor* thisx, PlayState* play) {
    ObjGrassCarry* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = 80;
    func_809AB3C4(this);
}

void ObjGrassCarry_Destroy(Actor* thisx, PlayState* play) {
    ObjGrassCarry* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);

    if (this->unk_190 != NULL) {
        ObjGrassCarry** carry = &this->unk_190->unk_3298[this->actor.params];

        if (this == *carry) {
            *carry = NULL;
            this->unk_190 = NULL;
        }
    }
}

void func_809AB3C4(ObjGrassCarry* this) {
    this->actionFunc = func_809AB3D8;
}

void func_809AB3D8(ObjGrassCarry* this, PlayState* play) {
    if (this->unk_190 != NULL) {
        if (this->actor.params != this->unk_190->unk_3292) {
            func_809AB474(this);
        } else {
            func_809AB428(this);
        }
    }
}

void func_809AB428(ObjGrassCarry* this) {
    this->actionFunc = func_809AB43C;
}

void func_809AB43C(ObjGrassCarry* this, PlayState* play) {
    if (this->actor.params != this->unk_190->unk_3292) {
        func_809AB474(this);
    }
}

void func_809AB474(ObjGrassCarry* this) {
    this->actor.shape.rot.z = 0;
    this->actionFunc = func_809AB4A8;
    this->unk_194 = NULL;
    this->actor.shape.rot.y = this->actor.shape.rot.z;
    this->actor.shape.rot.x = this->actor.shape.rot.z;
    this->actor.world.rot.z = this->actor.shape.rot.z;
    this->actor.world.rot.y = this->actor.shape.rot.z;
    this->actor.world.rot.x = this->actor.shape.rot.z;
}

void func_809AB4A8(ObjGrassCarry* this, PlayState* play) {
    Actor* thisx = &this->actor;

    if (Actor_HasParent(thisx, play)) {
        func_809AB5FC(this);
        if (this->unk_194 != NULL) {
            this->unk_194->unk_0F |= 4;
        }
        thisx->draw = func_809ABB7C;
        thisx->shape.shadowDraw = ActorShadow_DrawCircle;
        thisx->shape.shadowAlpha = 60;
        thisx->shape.shadowScale = 1.0f;
        this->unk_190->unk_3292 ^= 1;
        thisx->room = -1;
        SoundSource_PlaySfxAtFixedWorldPos(play, &thisx->world.pos, 20, NA_SE_PL_PULL_UP_PLANT);
    } else if (this->unk_190->unk_3294 != NULL) {
        Player* player = GET_PLAYER(play);

        this->unk_194 = this->unk_190->unk_3294;
        Math_Vec3f_Copy(&thisx->world.pos, &this->unk_194->unk_00);
        thisx->shape.rot.y = thisx->world.rot.y = this->unk_194->unk_0C;
        this->unk_198 = this->unk_194->unk_0E;
        thisx->xzDistToPlayer = Actor_WorldDistXZToActor(&this->actor, &player->actor);
        thisx->playerHeightRel = Actor_HeightDiff(&this->actor, &player->actor);
        thisx->xyzDistToPlayerSq = SQ(thisx->xzDistToPlayer) + SQ(thisx->playerHeightRel);
        thisx->yawTowardsPlayer = Actor_WorldYawTowardActor(&this->actor, &player->actor);
        Actor_OfferCarry(&this->actor, play);
    }
}

void func_809AB5FC(ObjGrassCarry* this) {
    this->actionFunc = func_809AB610;
}

void func_809AB610(ObjGrassCarry* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;
    s32 sp2C;

    if (Actor_HasNoParent(&this->actor, play)) {
        func_809AB6FC(this);
        this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * this->actor.speed;
        this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * this->actor.speed;
        this->actor.gravity = -0.1f;
        this->actor.terminalVelocity = -17.0f;
        func_809AAF18(this);
        func_809AAF58(this, play);
        this->actor.gravity = -3.2f;
    } else {
        sp30.x = this->actor.world.pos.x;
        sp30.y = this->actor.world.pos.y + 20.0f;
        sp30.z = this->actor.world.pos.z;
        this->actor.floorHeight =
            BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &sp2C, &this->actor, &sp30);
    }
}

void func_809AB6FC(ObjGrassCarry* this) {
    this->actionFunc = func_809AB77C;
    D_809ABBFC = -0xBB8;
    D_809ABC04 = (Rand_ZeroOne() - 0.5f) * 1600.0f;
    D_809ABC00 = 0;
    D_809ABC08 = 0;
    this->unk_19A = 60;
}

void func_809AB77C(ObjGrassCarry* this, PlayState* play) {
    s16 phi_s0;
    s32 temp_v0 = (this->collider.base.atFlags & AT_HIT) != 0;
    Vec3f sp5C;
    s32 i;

    if (temp_v0) {
        this->collider.base.atFlags &= ~AT_HIT;
    }

    this->unk_19A--;

    if ((this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH | BGCHECKFLAG_WALL)) || temp_v0 ||
        (this->unk_19A <= 0)) {
        func_809AAFE8(&this->actor.world.pos, play);
        func_809AAF9C(&this->actor.world.pos, this->unk_198, play);

        this->actor.draw = NULL;
        this->actor.shape.shadowDraw = NULL;

        if (this->unk_190 != NULL) {
            this->actor.room = this->unk_190->actor.room;
        }

        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER)) {
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 20, NA_SE_EV_PLANT_BROKEN);
        }
        func_809AB428(this);
        return;
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH) {
        sp5C.y = this->actor.world.pos.y + this->actor.depthInWater;

        for (phi_s0 = 0, i = 0; i < 4; i++, phi_s0 += 0x4000) {
            sp5C.x = (Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 15.0f) + this->actor.world.pos.x;
            sp5C.z = (Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + phi_s0) * 15.0f) + this->actor.world.pos.z;
            EffectSsGSplash_Spawn(play, &sp5C, NULL, NULL, 0, 190);
        }

        sp5C.x = this->actor.world.pos.x;
        sp5C.z = this->actor.world.pos.z;

        EffectSsGSplash_Spawn(play, &sp5C, NULL, NULL, 0, 280);
        EffectSsGRipple_Spawn(play, &sp5C, 300, 700, 0);

        this->actor.terminalVelocity = -3.0f;
        this->actor.velocity.x *= 0.1f;
        this->actor.velocity.y *= 0.4f;
        this->actor.velocity.z *= 0.1f;
        this->actor.gravity *= 0.5f;

        D_809ABC00 = D_809ABC00 >> 1;
        D_809ABBFC = D_809ABBFC >> 1;
        D_809ABC08 = D_809ABC08 >> 1;
        D_809ABC04 = D_809ABC04 >> 1;
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_WATER_TOUCH;
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 40, NA_SE_EV_DIVE_INTO_WATER_L);
    }

    Math_StepToS(&D_809ABC00, D_809ABBFC, 0x1F4);
    Math_StepToS(&D_809ABC08, D_809ABC04, 0xAA);
    this->actor.shape.rot.x += D_809ABC00;
    this->actor.shape.rot.y += D_809ABC08;
    func_809AAF18(this);
    func_809AAF58(this, play);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void ObjGrassCarry_Update(Actor* thisx, PlayState* play) {
    ObjGrassCarry* this = THIS;

    if (this->unk_190 == NULL) {
        if ((this->actionFunc != func_809AB610) && (this->actionFunc != func_809AB77C)) {
            Actor_Kill(&this->actor);
            return;
        }
    }

    this->actionFunc(this, play);
}

void func_809ABB7C(Actor* this, PlayState* play) {
    Gfx_DrawDListOpa(play, gKusaBushType1DL);
}
