/*
 * File: z_en_kusa.c
 * Overlay: ovl_En_Kusa
 * Description: Grass
 */

#include "z_en_kusa.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa*)thisx)

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx);

s32 func_80934F58(EnKusa* this, GlobalContext* globalCtx, f32 yOffset);
void func_80934FFC(EnKusa* this, GlobalContext* globalCtx);
void func_809350C4(EnKusa* this);
void func_809350F8(Vec3f* vec, f32 arg1);
void func_8093517C(EnKusa* this);

s32 func_809355A4(EnKusa* this, GlobalContext* globalCtx);
void func_809358C4(EnKusa* this);
void func_809358D8(EnKusa* this, GlobalContext* globalCtx);
void func_809359AC(EnKusa* this, GlobalContext* globalCtx);
void func_80935B94(EnKusa* this);
void func_80935BBC(EnKusa* this, GlobalContext* globalCtx);

void func_809358D8(EnKusa* this, GlobalContext* globalCtx);
void func_80935988(EnKusa* this);

void func_80935CE8(EnKusa* this);
void func_80935D64(EnKusa* this, GlobalContext* globalCtx);
void func_80936120(EnKusa* this);
void func_80936168(EnKusa* this, GlobalContext* globalCtx);
void func_809361A4(EnKusa* this, GlobalContext* globalCtx);
void func_809361B4(EnKusa* this);
void func_80936220(EnKusa* this, GlobalContext* globalCtx);
void func_80936290(EnKusa* this);
void func_809362D8(EnKusa* this, GlobalContext* globalCtx);
void func_80936414(EnKusa* this, GlobalContext* globalCtx);
void func_809365CC(EnKusa* this, GlobalContext* globalCtx);

s16 D_809366A0 = 0;
s16 D_809366A4 = 0;
s16 D_809366A8 = 0;
s16 D_809366AC = 0;

s16 D_809366B0 = 0;
u8 D_809366B4 = 0;

u32 D_80936AD0 = 0;

s16 D_80936CD8 = 0;
s16 D_80936CDA = 0;
s16 D_80936CDC = 0;
s16 D_80936CDE = 0;
s16 D_80936CE0 = 0;

/*
const ActorInit En_Kusa_InitVars = {
    ACTOR_EN_KUSA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnKusa),
    (ActorFunc)EnKusa_Init,
    (ActorFunc)EnKusa_Destroy,
    (ActorFunc)EnKusa_Update,
    (ActorFunc)NULL,
};
*/

static s16 D_809366D8[] = { GAMEPLAY_FIELD_KEEP, OBJECT_KUSA };

// was D_809366E0
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00400000, 0x00, 0x02 },
        { 0x0580C71C, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 6, 44, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit D_8093670C[] = { 0x0000000C, 0x001EFF00 };

static Vec3f D_80936714[] = {
    { 0.0f, 0.7071f, 0.7071f },
    { 0.7071f, 0.7071f, 0.0f },
    { 0.0f, 0.7071f, -0.7071f },
    { -0.7071f, 0.7071f, 0.0f },
};

s16 D_80936744[] = { 108, 102, 96, 84, 66, 55, 42, 38 };

// s32 D_80936754[] = { 0xC8580190, 0xB874F380, 0xB878BD98, 0xB0FC04B0, 0xB1000064, 0x310400C8, 0x00000000 };
static InitChainEntry D_80936754[] = {
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_CONTINUE),         ICHAIN_F32_DIV1000(gravity, -3200, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -17000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),         ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

extern Gfx D_040527F0[];
extern Gfx D_040528B0[];

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809349E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934AB4.asm")

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934F58.asm")
s32 func_80934F58(EnKusa* this, GlobalContext* globalCtx, f32 yOffset) {
    s32 pad;
    CollisionPoly* poly;
    Vec3f pos;
    s32 bgId;
    f32 floorY;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + 30.0f;
    pos.z = this->actor.world.pos.z;

    floorY = func_800C411C(&globalCtx->colCtx, &poly, &bgId, &this->actor, &pos);
    if (floorY > -32000.0f) {
        this->actor.world.pos.y = floorY + yOffset;
        Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
        return true;
    } else {
        return false;
    }
}

// Can't match with Item_DropCollectible not matching
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934FFC.asm")

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350C4.asm")
void func_809350C4(EnKusa* this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.minVelocityY) {
        this->actor.velocity.y = this->actor.minVelocityY;
    }
}

// matches...?
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350F8.asm")
void func_809350F8(Vec3f* vec, f32 arg1) {
    arg1 += ((Rand_ZeroOne() * 0.2f) - 0.1f) * arg1;
    vec->x -= vec->x * arg1;
    vec->y -= vec->y * arg1;
    vec->z -= vec->z * arg1;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093517C.asm")
void func_8093517C(EnKusa* this) {
    this->actor.scale.y = 0.16000001f;
    this->actor.scale.x = 0.120000005f;
    this->actor.scale.z = 0.120000005f;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809351A0.asm")
void func_809351A0(EnKusa* this, GlobalContext* globalCtx) {
    Vec3f velocity;
    Vec3f pos;
    s32 i;
    s32 index;
    Vec3f* scale;
    s32 pad;

    for (i = 0; i < ARRAY_COUNT(D_80936714); i++) {
        scale = &D_80936714[i];

        pos.x = this->actor.world.pos.x + (scale->x * this->actor.scale.x * 20.0f);
        pos.y = this->actor.world.pos.y + (scale->y * this->actor.scale.y * 20.0f) + 10.0f;
        pos.z = this->actor.world.pos.z + (scale->z * this->actor.scale.z * 20.0f);
        velocity.x = (Rand_ZeroOne() - 0.5f) * 8.0f;
        velocity.y = Rand_ZeroOne() * 10.0f;
        velocity.z = (Rand_ZeroOne() - 0.5f) * 8.0f;

        index = (s32)(Rand_ZeroOne() * 111.1f) & 7;

        EffectSsKakera_Spawn(globalCtx, &pos, &velocity, &pos, -0x64, 0x40, 0x28, 3, 0, D_80936744[index], 0, 0, 0x50,
                             -1, 1, &D_040527F0);

        pos.x = this->actor.world.pos.x + (scale->x * this->actor.scale.x * 40.0f);
        pos.y = this->actor.world.pos.y + (scale->y * this->actor.scale.y * 40.0f) + 10.0f;
        pos.z = this->actor.world.pos.z + (scale->z * this->actor.scale.z * 40.0f);
        velocity.x = (Rand_ZeroOne() - 0.5f) * 6.0f;
        velocity.y = Rand_ZeroOne() * 10.0f;
        velocity.z = (Rand_ZeroOne() - 0.5f) * 6.0f;

        index = (s32)(Rand_ZeroOne() * 111.1f) % 7;

        EffectSsKakera_Spawn(globalCtx, &pos, &velocity, &pos, -0x64, 0x40, 0x28, 3, 0, D_80936744[index], 0, 0, 0x50,
                             -1, 1, &D_040528B0);
    }
}

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809354F8.asm")
void func_809354F8(EnKusa* this, GlobalContext* globalCtx) {
    u32 i = 0;
    for (i = 0; i < 3; i++) {
        Actor* bug = Actor_SpawnWithParentAndCutscene(
            &globalCtx->actorCtx, globalCtx, (u16)0x16, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, 0, 0, 0, 1, this->actor.cutscene, (s16)this->actor.unk20, 0);

        if (bug == NULL) {
            break;
        }
    }
}

// Can't finish, func_800C9EBC is missing?
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809355A4.asm")

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093561C.asm")
void func_8093561C(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Init.asm")
void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;
    s16 rand;
    s32 sp24;

    sp24 = this->actor.params & 3;
    Actor_ProcessInitChain(&this->actor, D_80936754);
    if (globalCtx->csCtx.state != 0) {
        this->actor.uncullZoneForward += 1000.0f;
    }
    func_8093561C(&this->actor, globalCtx);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, D_8093670C);
    if (!sp24) {
        this->actor.shape.shadowScale = 1.0f;
        this->actor.shape.shadowAlpha = 0x3C;
    } else {
        this->actor.shape.shadowScale = 0.9f;
        this->actor.shape.shadowAlpha = 0x46;
    }

    if (this->actor.shape.rot.y == 0) {
        rand = (u32)Rand_Next() >> 0x10;
        this->actor.shape.rot.y = rand;
        this->actor.home.rot.y = this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if (!func_80934F58(this, globalCtx, 0.0f)) {
        Actor_MarkForDeath(&this->actor);
    } else {

        if (func_809355A4(this, globalCtx)) {
            this->unk198 |= 1;
        }
        this->objIndex = Object_GetIndex(&globalCtx->objectCtx, D_809366D8[this->actor.params & 3]);
        if (this->objIndex < 0) {
            Actor_MarkForDeath(&this->actor);
        } else {

            func_809358C4(this);
            if (D_809366B4) {
                D_80936CD8 = (u32)Rand_Next() >> 0x10;
                D_80936CDA = (u32)Rand_Next() >> 0x10;
                D_80936CDC = (u32)Rand_Next() >> 0x10;
                D_80936CDE = (u32)Rand_Next() >> 0x10;
                D_80936CE0 = (u32)Rand_Next() >> 0x10;
                D_809366B4 = 0;
                func_80934AB4();
                D_80936AD0 = globalCtx->gameplayFrames;
            }
            this->unk_196 = D_809366B0 & 7;
            D_809366B0++;
        }
    }
}

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Destroy.asm")
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnKusa* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358C4.asm")
void func_809358C4(EnKusa* this) {
    this->actionFunc = func_809358D8;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358D8.asm")
void func_809358D8(EnKusa* this, GlobalContext* globalCtx) {
    vu16 pad; // REVIEW: not sure about this, but it matches

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex) != 0) {
        s32 sp20 = this->actor.params & 3;
        if (this->unk_197 != 0) {
            func_80936120(this);
        } else {
            func_80935988(this);
        }
        if (sp20 == 0) {
            this->actor.draw = func_80936414;
        } else {
            this->actor.draw = func_809365CC;
        }
        this->actor.objBankIndex = this->objIndex;
        this->actor.flags &= ~0x10;
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935988.asm")
void func_80935988(EnKusa* this) {
    this->actionFunc = &func_809359AC;
    this->actor.flags &= ~0x10;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809359AC.asm")
void func_809359AC(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        func_80935B94(this);
        func_800F0568(globalCtx, &this->actor.world.pos, 0x14, NA_SE_PL_PULL_UP_PLANT);
        this->actor.shape.shadowDraw = func_800B3FC0;

    } else if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= 0xFFFD;
        func_809351A0(this, globalCtx);
        func_80934FFC(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EV_PLANT_BROKEN);

        if ((this->actor.params >> 4) & 1) {
            if ((this->actor.params & 3) != 3) {
                func_809354F8(this, globalCtx);
            }
        }
        if ((this->actor.params & 3) == 0) {
            Actor_MarkForDeath(&this->actor);
        } else {
            func_80936120(this);
            this->unk_197 = 1;
        }

    } else {
        if (!(this->collider.base.ocFlags1 & 8) && (this->actor.xzDistToPlayer > 12.0f)) {
            this->collider.base.ocFlags1 |= 8;
        }

        if (this->actor.xzDistToPlayer < 600.0f) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

            if (this->actor.xzDistToPlayer < 400.0f) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                if (this->actor.xzDistToPlayer < 100.0f) {
                    if ((this->actor.params & 3) != 3) {
                        func_800B8BB0(this, globalCtx);
                    }
                }
            }
        }
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935B94.asm")
void func_80935B94(EnKusa* this) {
    this->actionFunc = func_80935BBC;
    this->actor.room = -1;
    this->actor.flags = this->actor.flags | 0x10;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935BBC.asm")
void func_80935BBC(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f pos;
    s32 sp2C;

    if (func_800B8BFC(this, globalCtx)) {
        this->actor.room = globalCtx->roomCtx.currRoom.num;
        func_80935CE8(this);
        this->actor.velocity.x = this->actor.speedXZ * Math_SinS(this->actor.world.rot.y);
        this->actor.velocity.z = this->actor.speedXZ * Math_CosS(this->actor.world.rot.y);
        this->actor.colChkInfo.mass = 0x50;
        this->actor.gravity = -0.1f;
        func_809350C4(this);
        func_809350F8(&this->actor.velocity, 0.005f);
        Actor_ApplyMovement(&this->actor);
        func_800B78B8(globalCtx, &this->actor, 7.5f, 35.0f, 0.0f, 0xC5);
        this->actor.gravity = -3.2f;
    } else {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y + 20.0f;
        pos.z = this->actor.world.pos.z;
        this->actor.floorHeight = func_800C411C(&globalCtx->colCtx, &this->actor.floorPoly, &sp2C, &this->actor, &pos);
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935CE8.asm")
void func_80935CE8(EnKusa* this) {
    this->actionFunc = func_80935D64;
    D_809366A0 = -0xBB8;
    D_809366A8 = ((Rand_ZeroOne() - 0.5f) * 1600.0f);
    D_809366A4 = 0;
    D_809366AC = 0;
    this->timer = 0;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935D64.asm")
// void func_80935D64(EnKusa* this, GlobalContext* globalCtx) {
//     s32 i;
//     s16 angle;
//     s32 temp_v0;
//     u16 temp_v1_2;
//     u8 temp_t8;
//     u8 temp_v1;
//     Vec3f contactPos;

//     temp_v0 = (this->collider.base.atFlags & 2) != 0;
//     if (temp_v0 != 0) {
//         this->collider.base.atFlags &= 0xFFFD;
//     }
//     // temp_v1_2 = this->actor.bgCheckFlags;
//     this->timer++;
//     if ((this->actor.bgCheckFlags & 0xB) == 0) {
//         if (temp_v0 == 0) {
//             if ((this->timer & 0xFF) >= 0x64) {
//             block_5:
//                 if ((this->actor.bgCheckFlags & 0x20) == 0) {
//                     func_800F0568(globalCtx, &this->actor.world.pos, 0x14, NA_SE_EV_PLANT_BROKEN);
//                 }
//                 func_809351A0(this, globalCtx);
//                 func_80934FFC(this, globalCtx);
//                 switch (this->actor.params & 3) {
//                     case 0:
//                     case 1:
//                         func_809361B4(this);
//                         this->actor.shape.shadowDraw = NULL;
//                         break;
//                     case 2:
//                         Actor_MarkForDeath(&this->actor);
//                         break;
//                 }
//             } else {
//                 if (this->actor.bgCheckFlags & 0x40) {
//                     for (i = 0, angle = 0; i < 4; i++, angle += 0x4000) {
//                         contactPos.x = (Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + angle) * 15.0f) +
//                                        this->actor.world.pos.x;
//                         contactPos.y = this->actor.world.pos.y + this->actor.yDistToWater;
//                         contactPos.z = (Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + angle) * 15.0f) +
//                                        this->actor.world.pos.z;
//                         EffectSsGSplash_Spawn(globalCtx, &contactPos, NULL, NULL, 0, 0xBE);
//                     }

//                     contactPos.x = this->actor.world.pos.x;
//                     contactPos.z = this->actor.world.pos.z;
//                     EffectSsGSplash_Spawn(globalCtx, &contactPos, NULL, NULL, 0, 280);
//                     EffectSsGRipple_Spawn(globalCtx, &contactPos, 300, 700, 0);
//                     this->actor.minVelocityY = -3.0f;
//                     this->actor.velocity.x *= 0.1f;
//                     this->actor.velocity.y *= 0.4f;
//                     this->actor.velocity.z *= 0.1f;
//                     this->actor.gravity *= 0.5f;
//                     D_809366A4 >>= 1;
//                     D_809366A0 >>= 1;
//                     D_809366AC >>= 1;
//                     D_809366A8 >>= 1;
//                     this->actor.bgCheckFlags &= 0xFFBF;
//                     func_800F0568(globalCtx, &this->actor.world.pos, 0x28, NA_SE_EV_DIVE_INTO_WATER_L);
//                 }
//                 func_809350C4(this);
//                 Math_StepToS(&D_809366A4, D_809366A0, 0x1F4);
//                 Math_StepToS(&D_809366AC, D_809366A8, 0xAA);
//                 this->actor.shape.rot.x += D_809366A4;
//                 this->actor.shape.rot.y += D_809366AC;
//                 func_809350F8(&this->actor.velocity, 0.05f);
//                 Actor_ApplyMovement(this);
//                 func_800B78B8(globalCtx, &this->actor, 7.5f, 35.0f, 0.0f, 0xC5U);
//                 Collider_UpdateCylinder(&this->actor, &this->collider);
//                 CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
//                 CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
//             }
//         } else {
//             goto block_5;
//         }
//     } else {
//         goto block_5;
//     }
// }

// Needs work
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936120.asm")
void func_80936120(EnKusa* this) {
    switch (this->actor.params & 3) {
        case 2:
        case 3:
            this->actionFunc = func_809361A4;
            break;
        case 1:
            this->actionFunc = func_80936168;
            break;
    }
    this->timer = 0;
}

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936168.asm")
void func_80936168(EnKusa* this, GlobalContext* globalCtx) {
    this->timer++;
    if ((this->timer) >= 120) {
        func_80936290(this);
    }
}

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361A4.asm")
void func_809361A4(EnKusa* this, GlobalContext* globalCtx) {
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361B4.asm")
void func_809361B4(EnKusa* this) {
    this->actor.world.pos.x = this->actor.home.pos.x;
    this->actor.world.pos.y = this->actor.home.pos.y - 9.0f;
    this->actor.world.pos.z = this->actor.home.pos.z;
    func_8093517C(this);
    this->timer = 0;
    this->actor.shape.rot = this->actor.home.rot;
    this->actionFunc = func_80936220;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936220.asm")
void func_80936220(EnKusa* this, GlobalContext* globalCtx) {
    this->timer++;
    if ((this->timer) >= 121) {
        if ((Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.6f)) && (this->timer >= 170)) {
            func_80936290(this);
        }
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936290.asm")
void func_80936290(EnKusa* this) {
    this->actionFunc = func_809362D8;
    func_8093517C(this);
    this->unk_197 = 0;
    this->actor.shape.rot = this->actor.home.rot;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809362D8.asm")
void func_809362D8(EnKusa* this, GlobalContext* globalCtx) {
    s32 sp24;

    sp24 = Math_StepToF(&this->actor.scale.y, 0.4f, 0.014f) & 1;
    sp24 &= Math_StepToF(&this->actor.scale.x, 0.4f, 0.011f);
    this->actor.scale.z = this->actor.scale.x;
    if (sp24) {
        Actor_SetScale(&this->actor, 0.4f);
        func_80935988(this);
        this->collider.base.ocFlags1 &= 0xFFF7;
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Update.asm")
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;
    GlobalContext* globalCtx2 = globalCtx;

    this->actionFunc(this, globalCtx);
    if (this->unk_197 != 0) {
        this->actor.shape.yOffset = -6.25f;
    } else {
        this->actor.shape.yOffset = 0.0f;
    }
    if ((D_80936AD0 != globalCtx->gameplayFrames) && (globalCtx2->roomCtx.currRoom.unk3 == 0)) {
        func_80934AB4();
        D_80936AD0 = globalCtx2->gameplayFrames;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809365CC.asm")
