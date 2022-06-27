/*
 * File: z_bg_kin2_picture.c
 * Overlay: ovl_Bg_Kin2_Picture
 * Description: Ocean Spider House - Skullkid Painting
 */

#include "z_bg_kin2_picture.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Picture*)thisx)

void BgKin2Picture_Init(Actor* thisx, PlayState* play);
void BgKin2Picture_Destroy(Actor* thisx, PlayState* play);
void BgKin2Picture_Update(Actor* thisx, PlayState* play);
void BgKin2Picture_Draw(Actor* thisx, PlayState* play);

void func_80B6F4D4(BgKin2Picture* this, PlayState* play);
void func_80B6F5B8(BgKin2Picture* this, PlayState* play);
void func_80B6F640(BgKin2Picture* this, PlayState* play);
void func_80B6F72C(BgKin2Picture* this, PlayState* play);
void func_80B6F90C(BgKin2Picture* this, PlayState* play);

const ActorInit Bg_Kin2_Picture_InitVars = {
    ACTOR_BG_KIN2_PICTURE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Picture),
    (ActorFunc)BgKin2Picture_Init,
    (ActorFunc)BgKin2Picture_Destroy,
    (ActorFunc)BgKin2Picture_Update,
    (ActorFunc)BgKin2Picture_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80B6F990[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.3f, 9.0f }, { -20.0f, 3.0f, 9.0f }, { 20.0f, 3.0f, 9.0f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.3f, 9.0f }, { 20.0f, 3.0f, 9.0f }, { 20.0f, 53.3f, 9.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B6FA08 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80B6F990, // sTrisElementsInit,
};

static Vec3f D_80B6FA18 = { 0.0f, 23.0f, 0.0f };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B6FA24[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern UNK_TYPE D_06000658;
extern CollisionHeader D_06000798;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F098.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Init.s")

s32 func_80B6EFA0(PlayState *, s32);                /* extern */
void func_80B6F4C0(BgKin2Picture *);                   /* extern */

void BgKin2Picture_Init(Actor *thisx, PlayState *play) {
    Vec3f* vtx;
    Vec3f sp68[3];
    // ColliderTris *sp4C;
    // ColliderTris *temp_a1;
    // Vec3f *temp_s0;
    ColliderTrisElementInit* colliderElement;
    s16 temp_v0;
    BgKin2Picture *this = THIS;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->dyna.actor, D_80B6FA24);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(play, &this->dyna, &D_06000798);
    func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
    // temp_a1 = &this->colliderTris;
    // sp4C = temp_a1;
    Collider_InitTris(play, &this->colliderTris);
    Collider_SetTris(play, &this->colliderTris, &this->dyna.actor, &D_80B6FA08, &this->unk17C);
    Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    // phi_s2 = 0;
    // phi_s5 = 0;
    for(i = 0; i < ARRAY_COUNT(D_80B6F990); i++){
        colliderElement = &D_80B6FA08.elements[i];
        vtx = colliderElement->dim.vtx;
        for(j = 0; j < ARRAY_COUNT(sp68); j++){
            Matrix_MultVec3f(&vtx[j], &sp68[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &sp68[0], &sp68[1], &sp68[2]);
    }
//     do {
//         phi_s1 = 0;
//         phi_s0 = &sp68;
// loop_2:
//         Matrix_MultVec3f(phi_s2 + D_80B6FA08.elements + phi_s1 + 0x18, phi_s0);
//         temp_s0 = phi_s0 + 0xC;
//         phi_s1 += 0xC;
//         phi_s0 = temp_s0;
//         if (temp_s0 != &sp8C) {
//             goto loop_2;
//         }
//         Collider_SetTrisVertices(sp4C, phi_s5, &sp68, &sp74, &sp80);
//         temp_s5 = phi_s5 + 1;
//         phi_s2 += 0x3C;
//         phi_s5 = temp_s5;
//     } while (temp_s5 != 2);
    Actor_SetFocus(&this->dyna.actor, 23.0f);
    temp_v0 = this->dyna.actor.params;
    if (((((s32) temp_v0 >> 5) & 1) != 0) || (func_80B6EFA0(play, ((temp_v0 & 0x1F) * 4) | 0xFF03) != 0)) {
        this->unk242 = -1;
    }
    func_80B6F4C0(this);
}

void BgKin2Picture_Destroy(Actor *thisx, PlayState *play) {
    BgKin2Picture *this = (BgKin2Picture *) thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyTris(play, &this->colliderTris);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F90C.s")

void BgKin2Picture_Update(Actor *thisx, PlayState *play) {
    BgKin2Picture *this = THIS;
    this->actionFunc(this, play);
}

void BgKin2Picture_Draw(Actor *thisx, PlayState *play) {
    BgKin2Picture *this = THIS;
    Gfx_DrawDListOpa(play, (Gfx *) &D_06000658);
}
