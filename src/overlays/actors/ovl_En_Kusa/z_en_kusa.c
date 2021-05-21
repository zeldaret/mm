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

void func_809358D8(EnKusa* this, GlobalContext* globalCtx);
void func_809359AC(EnKusa* this, GlobalContext* globalCtx);
void func_80935B94(EnKusa* this);
void func_80935BBC(EnKusa* this, GlobalContext* globalCtx);

void func_80935CE8(EnKusa* this);
void func_80935D64(EnKusa* this, GlobalContext* globalCtx);
void func_80936120(EnKusa* this);
void func_80936168(EnKusa* this, GlobalContext* globalCtx);
void func_809361A4(EnKusa* this, GlobalContext* globalCtx);
void func_809361B4(EnKusa* this);
void func_80936220(EnKusa* this, GlobalContext* globalCtx);
void func_80936290(EnKusa* this);
void func_809362D8(EnKusa* this, GlobalContext* globalCtx);

s16 D_809366A0 = 0;
s16 D_809366A8 = 0;
s16 D_809366A4 = 0;
s16 D_809366AC = 0;

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

s32 D_809366D8[] = { 0x000200F8, 0x00F800F8 };

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

s32 D_8093670C[] = { 0x0000000C, 0x001EFF00 };

s32 D_80936714[] = { 0x00000000, 0x3F350481, 0x3F350481, 0x3F350481, 0x3F350481, 0x00000000,
                     0x00000000, 0x3F350481, 0xBF350481, 0xBF350481, 0x3F350481, 0x00000000 };

s32 D_80936744[] = { 0x006C0066, 0x00600054, 0x00420037, 0x002A0026 };

s32 D_80936754[] = { 0xC8580190, 0xB874F380, 0xB878BD98, 0xB0FC04B0, 0xB1000064, 0x310400C8, 0x00000000 };

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809351A0.asm")

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
// s32 func_809355A4(EnKusa* this, GlobalContext* globalCtx) {
//     Vec3f temp;

//     if ((func_800C9EBC(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &temp)) &&
//         (this->actor.world.pos.y < temp.y)) {
//         return 1;
//     }
//     return 0;
// }

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093561C.asm")
void func_8093561C(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Init.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358D8.asm")
// void func_809358D8(EnKusa *this, GlobalContext *globalCtx)
// {
//     s32 sp20;

//     if (Scene_IsObjectLoaded(&globalCtx->sceneContext, (s32) (s8) this->unk_197) != 0)
//     {
//         sp20 = this->actor.params & 3;
//         if (this->unk197 != 0)
//         {
//             func_80936120(this);
//         }
//         else
//         {
//             func_80935988(this);
//         }
//         if (sp20 == 0)
//         {
//             this->actor.draw = &func_80936414;
//         }
//         else
//         {
//             this->actor.draw = &func_809365CC;
//         }
//         this->actor.flags &= ~0x10;
//         this->actor.objBankIndex = (s8) this->unk_197;
//     }
// }

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935988.asm")
void func_80935988(EnKusa* this) {
    this->actionFunc = &func_809359AC;
    this->actor.flags = this->actor.flags & ~0x10;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809359AC.asm")
void func_809359AC(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        func_80935B94(this);
        func_800F0568(globalCtx, &this->actor.world.pos, 0x14, 0x869);
        this->actor.shape.shadowDraw = func_800B3FC0;

    } else if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= 0xFFFD;
        func_809351A0(this, globalCtx);
        func_80934FFC(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world.pos, 0x14, 0x284E);

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
            CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);

            if (this->actor.xzDistToPlayer < 400.0f) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
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
        this->actor.room = globalCtx->roomContext.currRoom.num;
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

// Needs work
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936120.asm")
// void func_80936120(EnKusa* this) {
//     s32 temp_v0;

//     temp_v0 = this->actor.params & 3;
//     if (temp_v0 != 1) {
//         if (temp_v0 != 2) {
//             if(temp_v0 != 3){

//             this->actionFunc = func_809361A4;
//             }
//         }
//     } else {
//         this->actionFunc = func_80936168;
//     }
//     this->timer = 0;
// }

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809365CC.asm")
