/*
 * File: z_en_ishi.c
 * Overlay: ovl_En_Ishi
 * Description: Liftable rocks and silver boulders
 */

#include "z_en_ishi.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_ishi/object_ishi.h"
#include "overlays/actors/ovl_En_Insect/z_en_insect.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_800000)

#define THIS ((EnIshi*)thisx)

void EnIshi_Init(Actor* thisx, PlayState* play);
void EnIshi_Destroy(Actor* thisx, PlayState* play2);
void EnIshi_Update(Actor* thisx, PlayState* play);

void func_8095D804(Actor* thisx, PlayState* play);
void func_8095DABC(Actor* thisx, PlayState* play);
void func_8095DDA8(EnIshi* this, PlayState* play);
void func_8095DE9C(EnIshi* this, PlayState* play);
void func_8095E5AC(EnIshi* this);
void func_8095E5C0(EnIshi* this, PlayState* play);
void func_8095E64C(EnIshi* this);
void func_8095E660(EnIshi* this, PlayState* play);
void func_8095E934(EnIshi* this);
void func_8095E95C(EnIshi* this, PlayState* play);
void func_8095EA70(EnIshi* this);
void func_8095EBDC(EnIshi* this, PlayState* play);
void func_8095F060(EnIshi* this);
void func_8095F0A4(EnIshi* this, PlayState* play);
void func_8095F180(EnIshi* this);
void func_8095F194(EnIshi* this, PlayState* play);
void func_8095F210(EnIshi* this, PlayState* play);
void func_8095F36C(EnIshi* this, PlayState* play);
void func_8095F61C(Actor* thisx, PlayState* play);
void func_8095F654(Actor* thisx, PlayState* play);

static s16 D_8095F690 = 0;

static s16 D_8095F694 = 0;

ActorInit En_Ishi_InitVars = {
    /**/ ACTOR_EN_ISHI,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnIshi),
    /**/ EnIshi_Init,
    /**/ EnIshi_Destroy,
    /**/ EnIshi_Update,
    /**/ NULL,
};

static f32 D_8095F6B8[] = { 0.1f, 0.4f };

static f32 D_8095F6C0[] = { 58.0f, 80.0f };

static f32 D_8095F6C8[] = { 0.0f, 0.005f };

static u16 D_8095F6D0[] = { NA_SE_EV_ROCK_BROKEN, NA_SE_EV_WALL_BROKEN };

static u8 D_8095F6D4[] = { 25, 40 };

static EnIshiUnkFunc2 D_8095F6D8[] = { func_8095D804, func_8095DABC };

static EnIshiUnkFunc D_8095F6E0[] = { func_8095DDA8, func_8095DE9C };

static s16 D_8095F6E8[] = { GAMEPLAY_FIELD_KEEP, OBJECT_ISHI };

static ColliderCylinderInit sCylinderInit[] = {
    {
        {
            COLTYPE_HARD,
            AT_ON | AT_TYPE_PLAYER,
            AC_ON | AC_HARD | AC_TYPE_PLAYER,
            OC1_ON | OC1_TYPE_ALL,
            OC2_TYPE_2,
            COLSHAPE_CYLINDER,
        },
        {
            ELEMTYPE_UNK0,
            { 0x00400000, 0x00, 0x02 },
            { 0x01C37FBE, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, 18, -2, { 0, 0, 0 } },
    },
    {
        {
            COLTYPE_HARD,
            AT_ON | AT_TYPE_PLAYER,
            AC_ON | AC_HARD | AC_TYPE_PLAYER,
            OC1_ON | OC1_TYPE_ALL,
            OC2_TYPE_2,
            COLSHAPE_CYLINDER,
        },
        {
            ELEMTYPE_UNK0,
            { 0x00400000, 0x00, 0x02 },
            { 0x01C37BB6, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 55, 70, 0, { 0, 0, 0 } },
    },
};

static CollisionCheckInfoInit sColChkInfoInit = { 0, 12, 60, MASS_IMMOVABLE };

static s16 D_8095F74C[] = { 16, 13, 11, 9, 7, 5 };

static s16 D_8095F758[] = { 145, 135, 120, 100, 70, 50, 45, 40, 35 };

static s16 D_8095F76C[] = { -1, 1, 2, 20, 8, 0 };

static Vec3f D_8095F778 = { 0.0f, 1.0f, 0.0f };

static InitChainEntry sInitChain[][5] = {
    {
        ICHAIN_F32_DIV1000(gravity, -1200, ICHAIN_CONTINUE),
        ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
    },
    {
        ICHAIN_F32_DIV1000(gravity, -2500, ICHAIN_CONTINUE),
        ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
        ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
    },
};

static u16 D_8095F7AC[] = { NA_SE_PL_PULL_UP_ROCK, NA_SE_PL_PULL_UP_BIGROCK };

static EnIshiUnkFunc D_8095F7B0[] = { func_8095F210, func_8095F36C };

void func_8095D6E0(Actor* thisx, PlayState* play) {
    EnIshi* this = THIS;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit[ENISHI_GET_1(&this->actor)]);
    Collider_UpdateCylinder(&this->actor, &this->collider);
}

s32 func_8095D758(EnIshi* this, PlayState* play, f32 arg2) {
    Vec3f sp24;
    s32 sp20;

    sp24.x = this->actor.world.pos.x;
    sp24.y = this->actor.world.pos.y + 30.0f;
    sp24.z = this->actor.world.pos.z;
    this->actor.floorHeight =
        BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &sp20, &this->actor, &sp24);
    if (this->actor.floorHeight > BGCHECK_Y_MIN) {
        this->actor.world.pos.y = this->actor.floorHeight + arg2;
        Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
        return true;
    }
    return false;
}

void func_8095D804(Actor* thisx, PlayState* play) {
    EnIshi* this = THIS;
    s32 i;
    s16 temp;
    Gfx* phi_s4;
    Vec3f spC4;
    Vec3f spB8;

    if (!ENISHI_GET_8(&this->actor)) {
        phi_s4 = gameplay_field_keep_DL_0066B0;
    } else {
        phi_s4 = gSmallRockDL;
    }

    temp = D_8095F6E8[ENISHI_GET_8(&this->actor)];

    for (i = 0; i < ARRAY_COUNT(D_8095F74C); i++) {
        spB8.x = ((Rand_ZeroOne() - 0.5f) * 8.0f) + this->actor.world.pos.x;
        spB8.y = (Rand_ZeroOne() * 5.0f) + this->actor.world.pos.y + 5.0f;
        spB8.z = ((Rand_ZeroOne() - 0.5f) * 8.0f) + this->actor.world.pos.z;
        Math_Vec3f_Copy(&spC4, &this->actor.velocity);

        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            spC4.x *= 0.6f;
            spC4.y *= -0.3f;
            spC4.z *= 0.6f;
        } else if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            spC4.x *= -0.5f;
            spC4.y *= 0.5f;
            spC4.z *= -0.5f;
        }

        spC4.x += (Rand_ZeroOne() - 0.5f) * 11.0f;
        spC4.y += (Rand_ZeroOne() * 7.0f) + 6.0f;
        spC4.z += (Rand_ZeroOne() - 0.5f) * 11.0f;

        EffectSsKakera_Spawn(play, &spB8, &spC4, &spB8, -420, ((s32)Rand_Next() > 0) ? 65 : 33, 30, 5, 0, D_8095F74C[i],
                             3, 10, 40, -1, temp, phi_s4);
    }
}

void func_8095DABC(Actor* thisx, PlayState* play) {
    EnIshi* this = THIS;
    Vec3f spD8;
    Vec3f spCC;
    f32 temp_f20;
    s16 temp_s1 = 0x1000;
    s32 i;
    s16 phi_v0;
    s16 phi_v1;

    for (i = 0; i < ARRAY_COUNT(D_8095F758); i++) {
        temp_s1 += 0x4E20;
        temp_f20 = Rand_ZeroOne() * 10.0f;

        spCC.x = (Math_SinS(temp_s1) * temp_f20) + this->actor.world.pos.x;
        spCC.y = (Rand_ZeroOne() * 40.0f) + this->actor.world.pos.y + 5.0f;
        spCC.z = (Math_CosS(temp_s1) * temp_f20) + this->actor.world.pos.z;

        Math_Vec3f_Copy(&spD8, &this->actor.velocity);

        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            spD8.x *= 0.9f;
            spD8.y *= -0.8f;
            spD8.z *= 0.9f;
        } else if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            spD8.x *= -0.9f;
            spD8.y *= 0.8f;
            spD8.z *= -0.9f;
        }

        temp_f20 = Rand_ZeroOne() * 10.0f;
        spD8.x += temp_f20 * Math_SinS(temp_s1);
        spD8.y += (Rand_ZeroOne() * 4.0f) + (Rand_ZeroOne() * i * 0.7f);
        spD8.z += temp_f20 * Math_CosS(temp_s1);

        if (i == 0) {
            phi_v0 = 41;
            phi_v1 = -450;
        } else if (i < 4) {
            phi_v0 = 37;
            phi_v1 = -380;
        } else {
            phi_v0 = 69;
            phi_v1 = -320;
        }

        EffectSsKakera_Spawn(play, &spCC, &spD8, &this->actor.world.pos, phi_v1, phi_v0, 30, 5, 0, D_8095F758[i], 5, 2,
                             70, 0, GAMEPLAY_FIELD_KEEP, gameplay_field_keep_DL_006420);
    }
}

void func_8095DDA8(EnIshi* this, PlayState* play) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        sp2C.x += 2.0f * this->actor.velocity.x;
        sp2C.y -= 2.0f * this->actor.velocity.y;
        sp2C.z += 2.0f * this->actor.velocity.z;
    } else if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        sp2C.x -= 2.0f * this->actor.velocity.x;
        sp2C.y += 2.0f * this->actor.velocity.y;
        sp2C.z -= 2.0f * this->actor.velocity.z;
    }
    func_800BBFB0(play, &sp2C, 60.0f, 3, 80, 60, 1);
}

void func_8095DE9C(EnIshi* this, PlayState* play) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        sp2C.x += 2.0f * this->actor.velocity.x;
        sp2C.y -= 2.0f * this->actor.velocity.y;
        sp2C.z += 2.0f * this->actor.velocity.z;
    } else if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        sp2C.x -= 2.0f * this->actor.velocity.x;
        sp2C.y += 2.0f * this->actor.velocity.y;
        sp2C.z -= 2.0f * this->actor.velocity.z;
    }
    func_800BBFB0(play, &sp2C, 140.0f, 10, 180, 90, 1);
}

void func_8095DF90(EnIshi* this, PlayState* play) {
    if (!ENISHI_GET_1(&this->actor) && !ENISHI_GET_100(&this->actor)) {
        Item_DropCollectibleRandom(play, NULL, &this->actor.world.pos, ENISHI_GET_F0(&this->actor) * 0x10);
    }
}

void func_8095DFF0(EnIshi* this, PlayState* play) {
    s32 pad;
    s32 temp = D_8095F76C[ENISHI_GET_70(&this->actor)];
    Actor* sp3C;
    Vec3f sp30;
    f32 sp2C;
    f32 temp_f2;
    s16 temp_v1_2;

    if (temp >= 0) {
        sp3C = Item_DropCollectible(play, &this->actor.world.pos, temp | (ENISHI_GET_FE00(&this->actor) << 8));
        if (sp3C != NULL) {
            Matrix_Push();
            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
            Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
            Matrix_MultVecY(1.0f, &sp30);
            sp2C = Math3D_Parallel(&sp30, &D_8095F778);
            if (sp2C < 0.707f) {
                temp_v1_2 = Math_Atan2S_XY(sp30.z, sp30.x) - sp3C->world.rot.y;
                if (ABS_ALT(temp_v1_2) > 0x4000) {
                    sp3C->world.rot.y = BINANG_ROT180(sp3C->world.rot.y);
                }
                temp_f2 = sp2C + 0.5f;
                if (temp_f2 < 0.5f) {
                    temp_f2 = 0.5f;
                }
                sp3C->velocity.y *= temp_f2;
            }
            Matrix_Pop();
        }
    }
}

void func_8095E14C(EnIshi* this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.terminalVelocity) {
        this->actor.velocity.y = this->actor.terminalVelocity;
    }
}

void func_8095E180(Vec3f* arg0, f32 arg1) {
    arg1 += ((Rand_ZeroOne() * 0.2f) - 0.1f) * arg1;

    arg0->x -= arg0->x * arg1;
    arg0->y -= arg0->y * arg1;
    arg0->z -= arg0->z * arg1;
}

void func_8095E204(EnIshi* this, PlayState* play) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_EN_INSECT, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                                          ENINSECT_PARAMS(true), this->actor.csId, this->actor.halfDaysBits,
                                          NULL) == NULL) {
            break;
        }
    }
}

s32 func_8095E2B0(EnIshi* this, PlayState* play) {
    s32 pad;
    WaterBox* sp30;
    f32 sp2C;
    s32 sp28;

    if (WaterBox_GetSurfaceImpl(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp2C, &sp30,
                                &sp28) &&
        (this->actor.world.pos.y < sp2C)) {
        return true;
    }
    return false;
}

void EnIshi_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnIshi* this = THIS;
    s32 sp34 = ENISHI_GET_1(&this->actor);
    s32 sp30 = ENISHI_GET_4(&this->actor);

    if ((sp34 == 0) && (sp30 != 0)) {
        this->unk_197 |= 2;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain[sp34]);

    if (play->csCtx.state != CS_STATE_IDLE) {
        this->actor.uncullZoneForward += 1000.0f;
    }

    if ((this->actor.shape.rot.y == 0) && !(this->unk_197 & 2)) {
        this->actor.shape.rot.y = this->actor.world.rot.y = Rand_Next() >> 0x10;
    }

    Actor_SetScale(&this->actor, D_8095F6B8[sp34]);
    func_8095D6E0(&this->actor, play);

    if ((sp34 == 1) && Flags_GetSwitch(play, ENISHI_GET_FE00(&this->actor))) {
        Actor_Kill(&this->actor);
        return;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);

    if (sp34 == 1) {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.shape.shadowScale = 2.3f;
    } else {
        this->actor.shape.shadowScale = 2.4f;
        this->actor.shape.shadowAlpha = 160;
    }

    this->actor.shape.yOffset = D_8095F6C0[sp34];

    if ((sp30 == 0) && !func_8095D758(this, play, 0)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (func_8095E2B0(this, play)) {
        this->unk_197 |= 1;
    }

    this->unk_196 = Object_GetIndex(&play->objectCtx, D_8095F6E8[ENISHI_GET_8(&this->actor)]);
    if (this->unk_196 < 0) {
        Actor_Kill(&this->actor);
        return;
    }

    func_8095E5AC(this);
}

void EnIshi_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnIshi* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_8095E5AC(EnIshi* this) {
    this->actionFunc = func_8095E5C0;
}

void func_8095E5C0(EnIshi* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->unk_196)) {
        this->actor.objBankIndex = this->unk_196;
        this->actor.flags &= ~ACTOR_FLAG_10;
        if (!ENISHI_GET_8(&this->actor)) {
            this->actor.draw = func_8095F61C;
        } else {
            this->actor.draw = func_8095F654;
        }
        func_8095E64C(this);
    }
}

void func_8095E64C(EnIshi* this) {
    this->actionFunc = func_8095E660;
}

void func_8095E660(EnIshi* this, PlayState* play) {
    s32 pad;
    s32 sp38 = ENISHI_GET_1(&this->actor);
    s32 sp34 = (this->collider.base.acFlags & AC_HIT) != 0;
    s32 sp30 = this->unk_197 & 2;

    if (sp34) {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    if (Actor_HasParent(&this->actor, play)) {
        func_8095E934(this);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 20, D_8095F7AC[sp38]);
        if (ENISHI_GET_2(&this->actor)) {
            func_8095E204(this, play);
        }
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        return;
    }

    if (sp34 && (sp38 == 0) && (this->collider.info.acHitInfo->toucher.dmgFlags & 0x508)) {
        if (sp30 != 0) {
            func_8095DFF0(this, play);
            func_8095F060(this);
            return;
        }
        func_8095DF90(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, D_8095F6D4[sp38], D_8095F6D0[sp38]);
        D_8095F6D8[sp38](&this->actor, play);
        D_8095F6E0[sp38](this, play);
        Actor_Kill(&this->actor);
        return;
    }

    if (sp34) {
        this->unk_195 = 5;
    }

    if ((this->actor.xzDistToPlayer < 600.0f) || (sp30 != 0)) {
        if (this->unk_195 > 0) {
            this->unk_195--;
            if (this->unk_195 == 0) {
                this->collider.base.colType = sCylinderInit[sp38].base.colType;
            } else {
                this->collider.base.colType = COLTYPE_NONE;
            }
        }

        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

        if ((this->actor.xzDistToPlayer < 90.0f) && (sp30 == 0)) {
            if (sp38 == 1) {
                Actor_OfferGetItem(&this->actor, play, GI_NONE, 80.0f, 20.0f);
            } else {
                Actor_OfferGetItem(&this->actor, play, GI_NONE, 50.0f, 10.0f);
            }
        }
    }
}

void func_8095E934(EnIshi* this) {
    this->actionFunc = func_8095E95C;
    this->actor.room = -1;
    this->actor.flags |= ACTOR_FLAG_10;
}

void func_8095E95C(EnIshi* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;
    s32 sp2C;

    if (Actor_HasNoParent(&this->actor, play)) {
        this->actor.room = play->roomCtx.curRoom.num;
        if (ENISHI_GET_1(&this->actor) == 1) {
            Flags_SetSwitch(play, ENISHI_GET_FE00(&this->actor));
        }
        func_8095EA70(this);
        func_8095E14C(this);
        func_8095E180(&this->actor.velocity, D_8095F6C8[ENISHI_GET_1(&this->actor)]);
        Actor_UpdatePos(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 7.5f, 35.0f, 0.0f,
                                UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40 |
                                    UPDBGCHECKINFO_FLAG_80);
    } else {
        sp30.x = this->actor.world.pos.x;
        sp30.y = this->actor.world.pos.y + 20.0f;
        sp30.z = this->actor.world.pos.z;
        this->actor.floorHeight =
            BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &sp2C, &this->actor, &sp30);
    }
}

void func_8095EA70(EnIshi* this) {
    f32 sp24;

    this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * this->actor.speed;
    this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * this->actor.speed;
    if (!ENISHI_GET_1(&this->actor)) {
        sp24 = Rand_ZeroOne() - 0.9f;
        D_8095F690 = sp24 * 11000.0f;
        D_8095F694 = ((Rand_ZeroOne() - 0.5f) * 3000.0f) * (fabsf(sp24) + 0.1f);
    } else {
        sp24 = Rand_ZeroOne() - 0.5f;
        D_8095F690 = sp24 * 6000.0f;
        D_8095F694 = ((Rand_ZeroOne() - 0.5f) * 1200.0f) * (fabsf(sp24) + 0.5f);
    }
    this->actor.colChkInfo.mass = 200;
    this->unk_194 = 100;
    this->actionFunc = func_8095EBDC;
}

void func_8095EBDC(EnIshi* this, PlayState* play) {
    s32 pad;
    s32 sp70 = ENISHI_GET_1(&this->actor);
    s16 temp_s0;
    s32 i;
    s16 phi_s0;
    Vec3f sp58;
    s32 temp_v0 = (this->collider.base.atFlags & AT_HIT) != 0;

    if (temp_v0) {
        this->collider.base.atFlags &= ~AT_HIT;
    }

    this->unk_194--;

    if ((this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_WALL)) || temp_v0 || (this->unk_194 <= 0)) {
        func_8095DF90(this, play);
        D_8095F6D8[sp70](&this->actor, play);

        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER)) {
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, D_8095F6D4[sp70], D_8095F6D0[sp70]);
            D_8095F6E0[sp70](this, play);
        }

        if (sp70 == 1) {
            s16 quakeIndex = Quake_Request(GET_ACTIVE_CAM(play), QUAKE_TYPE_3);

            Quake_SetSpeed(quakeIndex, 17232);
            Quake_SetPerturbations(quakeIndex, 3, 0, 0, 0);
            Quake_SetDuration(quakeIndex, 7);

            Rumble_Request(this->actor.xyzDistToPlayerSq, 255, 20, 150);
        }

        Actor_Kill(&this->actor);
        return;
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH) {
        if (sp70 == 0) {
            sp58.x = this->actor.world.pos.x;
            sp58.y = this->actor.world.pos.y + this->actor.depthInWater;
            sp58.z = this->actor.world.pos.z;
            EffectSsGSplash_Spawn(play, &sp58, NULL, NULL, 0, 350);
            EffectSsGRipple_Spawn(play, &sp58, 150, 650, 0);
        } else {
            sp58.y = this->actor.world.pos.y + this->actor.depthInWater;

            for (phi_s0 = 0, i = 0; i < 11; i++, phi_s0 += 0x1746) {
                sp58.x = (Math_SinS((s32)(Rand_ZeroOne() * 2000.0f) + phi_s0) * 50.0f) + this->actor.world.pos.x;
                sp58.z = (Math_CosS((s32)(Rand_ZeroOne() * 2000.0f) + phi_s0) * 50.0f) + this->actor.world.pos.z;
                EffectSsGSplash_Spawn(play, &sp58, NULL, NULL, 0, 350);
            }

            sp58.x = this->actor.world.pos.x;
            sp58.z = this->actor.world.pos.z;
            EffectSsGRipple_Spawn(play, &sp58, 500, 900, 4);
        }

        this->actor.terminalVelocity = -6.0f;
        this->actor.velocity.x *= 0.12f;
        this->actor.velocity.y *= 0.4f;
        this->actor.velocity.z *= 0.12f;
        this->actor.gravity *= 0.5f;

        D_8095F690 >>= 2;
        D_8095F694 >>= 2;

        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 40, NA_SE_EV_DIVE_INTO_WATER_L);
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_WATER_TOUCH;
    }

    Math_StepToF(&this->actor.shape.yOffset, 0.0f, 2.0f);
    func_8095E14C(this);
    func_8095E180(&this->actor.velocity, D_8095F6C8[sp70]);
    Actor_UpdatePos(&this->actor);
    this->actor.shape.rot.x += D_8095F690;
    this->actor.shape.rot.y += D_8095F694;
    Actor_UpdateBgCheckInfo(play, &this->actor, 7.5f, 35.0f, 0.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40 |
                                UPDBGCHECKINFO_FLAG_80);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
}

void func_8095F060(EnIshi* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    CutsceneManager_Queue(this->actor.csId);
    this->actionFunc = func_8095F0A4;
}

void func_8095F0A4(EnIshi* this, PlayState* play) {
    s32 pad;
    s32 sp28 = ENISHI_GET_1(&this->actor);

    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, D_8095F6D4[sp28], D_8095F6D0[sp28]);
        D_8095F6D8[sp28](&this->actor, play);
        D_8095F6E0[sp28](this, play);
        this->actor.draw = NULL;
        func_8095F180(this);
    } else {
        CutsceneManager_Queue(this->actor.csId);
    }
}

void func_8095F180(EnIshi* this) {
    this->actionFunc = func_8095F194;
}

void func_8095F194(EnIshi* this, PlayState* play) {
    if (this->actor.csId <= CS_ID_NONE) {
        Actor_Kill(&this->actor);
    } else if (CutsceneManager_GetCurrentCsId() != this->actor.csId) {
        Actor_Kill(&this->actor);
    }
}

void EnIshi_Update(Actor* thisx, PlayState* play) {
    EnIshi* this = THIS;

    this->actionFunc(this, play);
}

void func_8095F210(EnIshi* this, PlayState* play) {
    s32 pad;
    s32 sp28;

    if ((this->actor.projectedPos.z <= 1200.0f) || ((this->unk_197 & 1) && (this->actor.projectedPos.z < 1300.0f))) {
        Gfx_DrawDListOpa(play, gameplay_field_keep_DL_0066B0);
        return;
    }

    if (this->actor.projectedPos.z < 1300.0f) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        sp28 = (1300.0f - this->actor.projectedPos.z) * 2.55f;

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s32)sp28);
        gSPDisplayList(POLY_XLU_DISP++, gameplay_field_keep_DL_006760);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void func_8095F36C(EnIshi* this, PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    if ((this->actor.projectedPos.z <= 2150.0f) || ((this->unk_197 & 1) && (this->actor.projectedPos.z < 2250.0f))) {
        this->actor.shape.shadowAlpha = 160;

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        gSPDisplayList(POLY_OPA_DISP++, gameplay_field_keep_DL_0061E8);
    } else if (this->actor.projectedPos.z < 2250.0f) {
        f32 sp20 = (2250.0f - this->actor.projectedPos.z) * 2.55f;

        this->actor.shape.shadowAlpha = sp20 * 0.627451f;

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s32)sp20);
        gSPDisplayList(POLY_XLU_DISP++, gameplay_field_keep_DL_0061E8);
    } else {
        this->actor.shape.shadowAlpha = 0;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_8095F61C(Actor* thisx, PlayState* play) {
    EnIshi* this = THIS;

    D_8095F7B0[ENISHI_GET_1(&this->actor)](this, play);
}

void func_8095F654(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gSmallRockDL);
}
