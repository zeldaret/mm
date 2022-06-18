/*
 * File: z_bg_ikana_mirror.c
 * Overlay: ovl_Bg_Ikana_Mirror
 * Description: Stone Tower Temple - Mirror
 */

//credits: darkeye, Isghj, EllipticEllipsis, mzxrules,

#include "z_bg_ikana_mirror.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaMirror*)thisx)

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx);
// first commit
#if 0
const ActorInit Bg_Ikana_Mirror_InitVars = {
    ACTOR_BG_IKANA_MIRROR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaMirror),
    (ActorFunc)BgIkanaMirror_Init,
    (ActorFunc)BgIkanaMirror_Destroy,
    (ActorFunc)BgIkanaMirror_Update,
    (ActorFunc)BgIkanaMirror_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[9] = {
static ColliderTrisElementInit D_80B7FF50[9] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 21.600000381469727f, 13.699999809265137f }, { -25.299999237060547f, 6.0f, 8.399999618530273f }, { 25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -25.299999237060547f, 6.0f, 8.399999618530273f }, { 0.0f, 21.600000381469727f, 13.699999809265137f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 0.0f, 21.600000381469727f, 13.699999809265137f }, { 25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -25.299999237060547f, 45.0f, 8.399999618530273f }, { -25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 25.299999237060547f, 6.0f, 8.399999618530273f }, { 25.299999237060547f, 45.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -17.899999618530273f, 64.0999984741211f, 8.399999618530273f }, { -25.299999237060547f, 45.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 25.299999237060547f, 45.0f, 8.399999618530273f }, { 17.899999618530273f, 64.0999984741211f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 0.0f, 72.0f, 8.399999618530273f }, { -17.899999618530273f, 64.0999984741211f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 17.899999618530273f, 64.0999984741211f, 8.399999618530273f }, { 0.0f, 72.0f, 8.399999618530273f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B8016C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    9, D_80B7FF50, // sTrisElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B8017C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 72.0f, 20.0f }, { 0.0f, 72.0f, 240.0f }, { 0.0f, 6.0f, 20.0f }, { 0.0f, 6.0f, 240.0f } } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B801FC = {
    { 0x41, AT_NONE | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_FIRST_ONLY | OC2_UNK1 | OC2_HIT_PLAYER, 0x70, },
    { 0xC1, { 0x41A00000, 0x41, 0xA0 }, { 0xC1CA6666, 0x41, 0xA0 }, TOUCH_ON | TOUCH_HIT | TOUCH_SFX_NORMAL | TOUCH_DREW_HITMARK, BUMP_NONE | BUMP_NO_DAMAGE | BUMP_NO_SWORD_SFX | BUMP_NO_HITMARK, OCELEM_NONE, },
    { { { -1.8339854079840734e-09f, -1.8626939990440405e-09f, -1.9208972190654094e-09f }, { 221185.5625f, 0.0f, 0.003921568859368563f }, { 0.0f, 0.0f, 0.0f }, { 2.8698592549372254e-42f, 1.0761972206014595e-42f, 2.2420775429197073e-44f } } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B8021C[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 220, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

void func_80B7F730(BgIkanaMirror *);
void func_80B7FA9C(BgIkanaMirror* arg0, GlobalContext* arg1); /* static */
void func_80B7FBA4(BgIkanaMirror* arg0, GlobalContext* arg1);

extern ColliderTrisElementInit D_80B7FF50[9];
extern ColliderTrisInit D_80B8016C;
extern ColliderQuadInit D_80B8017C[2];

//extern ColliderQuadInit D_80B801FC;
extern InitChainEntry D_80B8021C[];

extern Gfx* D_060014B0;
extern Gfx* D_06001880;
extern Gfx* D_06001E18;
extern CollisionHeader D_06002358;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7F730.s")

void func_80B7F730(BgIkanaMirror *arg0){
  ColliderQuad *new_var;
  s32 i;
  Vec3f sp84;
  Vec3f sp78;
  Vec3f sp6C;
  Vec3f sp60;
    ColliderQuadDimInit* dim;
  Matrix_Push();
  Matrix_SetTranslateRotateYXZ(arg0->actor.world.pos.x, arg0->actor.world.pos.y, arg0->actor.world.pos.z, &arg0->actor.shape.rot);
  for (i = 0; i < 2; i++)
  {
      dim = &D_80B8017C[i].dim;
    Matrix_MultVec3f(&dim->quad[0], &sp84);
    Matrix_MultVec3f(&dim->quad[1], &sp78);
    Matrix_MultVec3f(&dim->quad[2], &sp6C);
    Matrix_MultVec3f(&dim->quad[3], &sp60);
    new_var = &arg0->unk4B8[i];
    Collider_SetQuadVertices(new_var, &sp84, &sp78, &sp6C, &sp60);
  }

  Matrix_Pop();
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Init.s")

void func_80B7F730(BgIkanaMirror*); /* extern */
void func_80B7FA84(BgIkanaMirror* arg0);
void func_80B7FB84(BgIkanaMirror* arg0);
extern UNK_TYPE D_06001678; // AnimatedMaterial
extern UNK_TYPE D_06001AD8; // AnimatedMaterial

// ColliderTrisInit D_80B8016C = { { 0xA, 0, 0x29, 0, 0, 2 }, 9, D_80B7FF50 };

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIkanaMirror* this = ((BgIkanaMirror*)thisx);
    Vec3f* phi_s1;
    Vec3f sp60[3];
    ColliderTrisElementInit* temp;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->actor, D_80B8021C);
    DynaPolyActor_Init((DynaPolyActor*)this, 0);
    DynaPolyActor_LoadMesh(globalCtx, (DynaPolyActor*)this, &D_06002358);
    Collider_InitTris(globalCtx, &this->unk15C);
    Collider_SetTris(globalCtx, &this->unk15C, &this->actor, &D_80B8016C, &this->unk17C);
    Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 &this->actor.shape.rot);

    for (i = 0; i < 9; i++) {
        temp = &D_80B8016C.elements[i];
        phi_s1 = &temp->dim.vtx[0];
        for (j = 0; j < 3; j++) {
            Matrix_MultVec3f(phi_s1, &sp60[j]);
            phi_s1++;
        }
        Collider_SetTrisVertices(&this->unk15C, i, &sp60[0], &sp60[1], &sp60[2]);
    }

    for (i = 0; i < 2; i++) {
        Collider_InitQuad(globalCtx, &this->unk4B8[i]);
        Collider_SetQuad(globalCtx, &this->unk4B8[i], &this->actor, &D_80B8017C[i]);
    }

    func_80B7F730(this);
    this->unk5BC = Lib_SegmentedToVirtual(&D_06001678);
    this->unk5C0 = Lib_SegmentedToVirtual(&D_06001AD8);
    func_80B7FA84(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Destroy.s")

void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaMirror* this = THIS;
    ColliderQuad* var_s1;
    s32 var_s0;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->unk144);
    Collider_DestroyTris(globalCtx, &this->unk15C);
    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        Collider_DestroyQuad(globalCtx, &this->unk4B8[var_s0]);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FA84.s")

void func_80B7FA84(BgIkanaMirror* arg0) {
    arg0->unk5C8 = 0;
    arg0->actionFunc = func_80B7FA9C;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FA9C.s")

void func_80B7FA9C(BgIkanaMirror *arg0, GlobalContext *arg1)
{
  s16 temp_v1;
  s8 temp_v0_4;
  u8 temp_v0;
  u8 temp_v0_2;
  u8 temp_v0_3;
  s32 phi_a2;
  temp_v0 = arg0->unk5C7;
  phi_a2 = 0;
  if (((s32) temp_v0) >= 0x65)
  {
    arg0->unk5C7 = temp_v0 - 0x64;
  }
  else
  {
    arg0->unk5C7 = 0;
  }
  temp_v0_2 = arg0->unk15C.base.acFlags;
  if ((arg0->unk15C.base.acFlags & 2) != 0)
  {
    temp_v1 = arg0->unk5C4;
    arg0->unk15C.base.acFlags = arg0->unk15C.base.acFlags & 0xFFFD;
    arg0->unk5C8 = 0;
    if (((s32) temp_v1) < 0x190)
    {
      arg0->unk5C4 = temp_v1 + 1;
    }
    temp_v0_3 = arg0->unk5C6;
    if (((s32) temp_v0_3) < 0xC3)
    {
      arg0->unk5C6 = temp_v0_3 + 0x3C;
    }
    else
    {
      arg0->unk5C6 = 0xFF;
    }
  }
  else
  {
    temp_v0_4 = arg0->unk5C8;
    if (((s32) temp_v0_4) > 0)
    {
      phi_a2 = 1;
    }
    else
      if (((s32) arg0->unk5C4) > 0)
    {
      arg0->unk5C8 = temp_v0_4 + 1;
    }
  }
  if (phi_a2 != 0)
  {
    func_80B7FB84(arg0);
    return;
  }
  CollisionCheck_SetAC(arg1, &arg1->colChkCtx, &arg0->unk15C.base);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FB84.s")

void func_80B7FB84(BgIkanaMirror* arg0) {
    arg0->actor.flags |= 0x20;
    arg0->actionFunc = func_80B7FBA4;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FBA4.s")



//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Update.s")

void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaMirror* this = (BgIkanaMirror*)thisx;
    this->actionFunc(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Draw.s")

//score: 3198
// void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx) {
//     GraphicsContext* new_var8;
//     AnimatedMaterial* new_var6;
//     s32 new_var;
//     f32 sp38;
//     AnimatedMaterial* new_var3;
//     Gfx* temp_v0_10;
//     Gfx* temp_v0;
//     Gfx* temp_v0_2;
//     Gfx* temp_v0_3;
//     f32 new_var7;
//     Gfx* temp_v0_4;
//     GlobalContext* new_var5;
//     Gfx* temp_v0_5;
//     Gfx* temp_v0_7;
//     Gfx* temp_v0_8;
//     Gfx* temp_v0_9;
//     GraphicsContext* new_var2;
//     GraphicsContext* temp_a0;
//     GraphicsContext* temp_s0;
//     Gfx** new_var11;
//     f32 temp_ft1;
//     s8 temp_v0_6;
//     f32 phi_ft1;
//     BgIkanaMirror* this = (BgIkanaMirror*)thisx;
//     new_var = this->unk5C6;
//     temp_a0 = ((0, globalCtx))->state.gfxCtx;
//     temp_s0 = temp_a0;
//     func_8012C28C(temp_s0);
//     func_8012C2DC(globalCtx->state.gfxCtx);
//     temp_v0 = temp_s0->polyOpa.p;
//     new_var8 = temp_s0;
//     temp_s0->polyOpa.p = temp_s0->polyOpa.p + 8;
//     temp_v0->words.w0 = 0xDA380003;
//     if (1) {
//         new_var6 = this->unk5C0;
//         temp_v0->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
//     }
//     temp_v0_2 = temp_s0->polyOpa.p;
//     temp_s0->polyOpa.p = 8 + temp_v0_2;
//     temp_v0_2->words.w1 = (u32)(&D_06001E18);
//     temp_v0_2->words.w0 = 0xDE000000;
//     if (((s32)new_var) > 0) {
//         new_var3 = this->unk5BC;
//         AnimatedMat_Draw(globalCtx, new_var3);
//         temp_v0_3 = new_var8->polyXlu.p;
//         new_var8->polyXlu.p = temp_v0_3 + 8;
//         temp_v0_3->words.w0 = 0xFA000080;
//         new_var5 = globalCtx;
//         temp_v0_3->words.w1 = new_var | (~0xFF);
//         temp_v0_4 = new_var8->polyXlu.p;
//         new_var8->polyXlu.p = temp_v0_4 + 8;
//         temp_v0_4->words.w0 = 0xDA380003;
//         temp_v0_4->words.w1 = Matrix_NewMtx(new_var5->state.gfxCtx);
//     dummy_label_941816:;

//         if (1) {
//             temp_v0_5 = new_var8->polyXlu.p;
//             new_var8->polyXlu.p = temp_v0_5 + 8;
//             temp_v0_5->words.w1 = (u32)(&D_060014B0);
//         }
//         temp_v0_5->words.w0 = 0xDE000000;
//     }
//     temp_v0_6 = this->unk5C7;
//     if (((s32)temp_v0_6) > 0) {
//         temp_ft1 = (f32)temp_v0_6;
//         phi_ft1 = (f32)temp_v0_6;
//         if (((s32)temp_v0_6) < 0) {
//             phi_ft1 = 4294967296.0f + temp_ft1;
//         }
//         new_var7 = phi_ft1 * 0.003921569f;
//         AnimatedMat_Draw(new_var5, new_var6);
//         temp_v0_7 = new_var8->polyXlu.p;
//         temp_s0->polyXlu.p = temp_v0_7;
//         temp_s0->polyXlu.p = temp_s0->polyXlu.p + 8;
//         new_var2 = temp_s0;
//         phi_ft1 = new_var7 * 123.0f;
//         temp_v0_7->words.w0 = 0xFA000080;
//         temp_v0_7->words.w1 = (((s32)phi_ft1) & 0xFF) | (~0xFF);
//         if ((temp_v0_9 && temp_v0_9) && temp_v0_9) {}
//         temp_v0_8 = temp_s0->polyXlu.p;
//         new_var2->polyXlu.p = temp_v0_8 + 8;
//         temp_v0_8->words.w0 = 0xFB000000;
//         temp_v0_8->words.w1 = (((s32)(new_var7 * 185.0f)) & 0xFF) | 0xD7D7FF00;
//         temp_v0_9 = new_var2->polyXlu.p;
//         new_var2->polyXlu.p = temp_v0_9 + 8;
//         temp_v0_9->words.w0 = 0xDA380003;
//         new_var11 = &D_06001880;
//         temp_v0_9->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
//         if (0, (&new_var5->state) && (&new_var5->state)) {}
//         temp_v0_10 = new_var2->polyXlu.p;
//         new_var2->polyXlu.p = temp_s0->polyXlu.p;
//         new_var2->polyXlu.p = new_var2->polyXlu.p + 8;
//         temp_v0_10->words.w1 = (u32)new_var11;
//         temp_v0_10->words.w0 = 0xDE000000;
//     }
// }
