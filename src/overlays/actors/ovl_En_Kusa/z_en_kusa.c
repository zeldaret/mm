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
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809349E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934F58.asm")

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934FFC.asm")
void func_80934FFC(EnKusa* this, GlobalContext* globalCtx) {
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v1 = this->actor.params;
    temp_v0 = temp_v1 & 3;
    if (temp_v0 != 2) {
        if (temp_v0 == 0) {
        block_2:
            if (((temp_v1 >> 0xC) & 1) == 0) {
                Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world, (((temp_v1 >> 8) & 0xF) * 0x10));
                return;
            }
        } else {
            if (temp_v0 == 1) {
                Item_DropCollectible(globalCtx, &this->actor.world, 3U);
                return;
            }
            temp_v0_2 = func_800A8150((temp_v1 >> 2) & 0x3F);
            if (temp_v0_2 >= 0) {
                Item_DropCollectible(globalCtx, &this->actor.world,
                                     (((this->actor.params >> 8) & 0x7F) << 8) | temp_v0_2);
            }
        }
    } else {
        goto block_2;
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350C4.asm")
void func_809350C4(EnKusa* this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.minVelocityY) {
        this->actor.velocity.y = this->actor.minVelocityY;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093517C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809351A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809354F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809355A4.asm")

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093561C.asm")
void func_8093561C(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Init.asm")
// void EnKusa_Init(Actor *thisx, GlobalContext *globalCtx)
// {
//     s32 sp24;
//     s16 temp_v1;

//     sp24 = thisx->params & 3;
//     Actor_ProcessInitChain(thisx, &D_80936754);
//     if (globalCtx->csCtx.state != 0)
//     {
//         thisx->uncullZoneForward = thisx->uncullZoneForward + 1000.0f;
//     }
//     func_8093561C(thisx, globalCtx);
//     CollisionCheck_SetInfo(&thisx->colChkInfo, NULL, &D_8093670C);
//     if (sp24 == 0)
//     {
//         thisx->shape.shadowAlpha = 0x3C;
//         thisx->shape.shadowScale = 1.0f;
//     }
//     else
//     {
//         thisx->shape.shadowAlpha = 0x46;
//         thisx->shape.shadowScale = 0.9f;
//     }
//     if (thisx->shape.rot.y == 0)
//     {
//         thisx->shape.rot.y = (s16) (Rand_Next() >> 0x10);
//         temp_v1 = thisx->shape.rot.y;
//         thisx->home.rot.y = temp_v1;
//         thisx->world.rot.y = temp_v1;
//     }
//     if (func_80934F58(thisx, globalCtx, 0) == 0)
//     {
//         Actor_MarkForDeath(thisx);
//         return;
//     }
//     if (func_809355A4(thisx, globalCtx) != 0)
//     {
//         thisx->unk198 = (u8) (thisx->unk198 | 1);
//     }
//     thisx->unk195 = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, *(&D_809366D8 + ((thisx->params & 3) * 2)));
//     if ((s32) thisx->unk195 < 0)
//     {
//         Actor_MarkForDeath(thisx);
//         return;
//     }
//     func_809358C4(thisx);
//     if (D_809366B4 != 0)
//     {
//         D_80936CD8 = (s16) (Rand_Next() >> 0x10);
//         D_80936CDA = (s16) (Rand_Next() >> 0x10);
//         D_80936CDC = (s16) (Rand_Next() >> 0x10);
//         D_80936CDE = (s16) (Rand_Next() >> 0x10);
//         D_80936CE0 = (s16) (Rand_Next() >> 0x10);
//         D_809366B4 = (u8)0;
//         func_80934AB4();
//         D_80936AD0 = (u32) globalCtx->unk18840;
//     }
//     thisx->unk196 = (s8) (D_809366B0 & 7);
//     D_809366B0 = (s16) (D_809366B0 + 1);
// }

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Destroy.asm")
void EnKusa_Destroy(Actor *thisx, GlobalContext *globalCtx2)
{
    GlobalContext* globalCtx = globalCtx2;
    EnKusa* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358C4.asm")
// void func_809358C4(EnKusa *this)
// {
//     this->unk_144 = func_809358D8;
// }

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935988.asm")
// void func_80935988(EnKusa *this)
// {
//     this->unk_144 = &func_809359AC;
//     this->actor.flags = this->actor.flags & ~0x10;
// }

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809359AC.asm")
void func_809359AC(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Actor_HasParent(this, globalCtx)) {
        func_80935B94(this);
        func_800F0568(globalCtx, &this->actor.world, 0x14, 0x869);
        this->actor.shape.shadowDraw = func_800B3FC0;

    } else if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= 0xFFFD;
        func_809351A0(this, globalCtx);
        func_80934FFC(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world, 0x14, 0x284E);

        if ((this->actor.params >> 4) & 1) {
            if ((this->actor.params & 3) != 3) {
                func_809354F8(this, globalCtx);
            }
        }
        if ((this->actor.params & 3) == 0) {
            Actor_MarkForDeath(&this->actor);
            this->unk_197 = 1;
            return;
        }
        func_80936120(this);

    } else {
        if (!(this->collider.base.ocFlags1 & 8) && (this->actor.xzDistToPlayer > 12.0f)) {
            this->collider.base.ocFlags1 = this->collider.base.ocFlags1 | 8;
        }

        if (this->actor.xzDistToPlayer < 600.0f) {
            Collider_UpdateCylinder(this, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);

            if (this->actor.xzDistToPlayer < 400.0f) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
                if (this->actor.xzDistToPlayer < 100.0f) {
                    if ((this->actor.params & 3) != 3) {
                        func_800B8BB0(this, globalCtx);
                    }
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935B94.asm")
// void func_80935B94(EnKusa *this)
// {
//     this->unk_144 = func_80935BBC();
//     this->actor.room = -1;
//     this->actor.flags = this->actor.flags | 0x10;
// }

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936120.asm")

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936168.asm")
void func_80936168(EnKusa* this, GlobalContext* globalCtx) {
    this->timer += 1;

    if ((this->timer) >= 120) {
        func_80936290();
    }
}

// Matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361A4.asm")
void func_809361A4(EnKusa* this, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809362D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809365CC.asm")
