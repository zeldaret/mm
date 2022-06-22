/*
 * File: z_bg_ikana_mirror.c
 * Overlay: ovl_Bg_Ikana_Mirror
 * Description: Stone Tower Temple - Mirror
 */

//credits for documentation:

#include "z_bg_ikana_mirror.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaMirror*)thisx) 

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx);

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
        { { { 0.0f, 21.6f, 13.7f }, { -25.3f, 6.0f, 8.4f }, { 25.3f, 6.0f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { -25.3f, 6.0f, 8.4f }, { 0.0f, 21.6f, 13.7f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { 0.0f, 21.6f, 13.7f }, { 25.3f, 6.0f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { -25.3f, 45.0f, 8.4f }, { -25.3f, 6.0f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { 25.3f, 6.0f, 8.4f }, { 25.3f, 45.0f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { -17.9f, 64.1f, 8.4f }, { -25.3f, 45.0f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { 25.3f, 45.0f, 8.4f }, { 17.9f, 64.1f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { 0.0f, 72.0f, 8.4f }, { -17.9f, 64.1f, 8.4f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.7f }, { 17.9f, 64.1f, 8.4f }, { 0.0f, 72.0f, 8.4f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B8016C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    9, D_80B7FF50, 
};

// static ColliderQuadInit sQuadInit = { //check if some floats can be rewritten.
static ColliderQuadInit D_80B8017C[2] = {{
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 72.0f, 20.0f }, { 0.0f, 72.0f, 240.0f }, { 0.0f, 6.0f, 20.0f }, { 0.0f, 6.0f, 240.0f } } },
},
{
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { { { 25.3f, 20.0f, 20.0f }, { 25.3f, 20.0f, 240.0f }, { -25.3f, 20.0f, 20.0f }, { -25.3f, 20.0f, 240.0f } } },
}};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B8021C[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 220, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void func_80B7FA84(BgIkanaMirror* arg0);
void func_80B7FA9C(BgIkanaMirror* arg0, GlobalContext* arg1);
void func_80B7FB84(BgIkanaMirror* arg0);
void func_80B7FBA4(BgIkanaMirror* arg0, GlobalContext* arg1);

extern Gfx* D_060014B0; 
extern Gfx* D_06001880; 
extern Gfx* D_06001E18;
extern CollisionHeader D_06002358;

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

extern UNK_TYPE D_06001678; // AnimatedMaterial
extern UNK_TYPE D_06001AD8; // AnimatedMaterial

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

void func_80B7FA84(BgIkanaMirror* arg0) {
    arg0->unk5C8 = 0;
    arg0->actionFunc = func_80B7FA9C;
}

void func_80B7FA9C(BgIkanaMirror *arg0, GlobalContext *arg1)
{
  s16 temp_v1;
  s8 temp_v0_4;
  u8 temp_v0;
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
  
  if ((arg0->unk15C.base.acFlags & 2))
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

void func_80B7FB84(BgIkanaMirror* arg0) {
    arg0->actor.flags |= 0x20;
    arg0->actionFunc = func_80B7FBA4;
}

void func_80B7FBA4(BgIkanaMirror *this, GlobalContext *arg1)
{
  s32 i;

  for (i = 0; i < 2; i++)
  {
    if ((this->unk4B8[i].base.atFlags & 2))
    {
      this->unk4B8[i].base.atFlags &= ~2;
    }
  }

  if (this->unk5C7 < 0x9B)
  {
    this->unk5C7 += 0x64;
  }
  else
  {
    this->unk5C7 = 0xFF;
  }

  if (this->unk5C6 >= 61)
  {
    this->unk5C6 -= 60;
  }
  else
  {
    this->unk5C6 = 0;
  }

  if (this->unk5C4 > 0)
  {
    this->unk5C4--;
    for (i = 0; i < 2; i++)
    {
      CollisionCheck_SetAT(arg1, &arg1->colChkCtx, &this->unk4B8[i].base);
    }
    return;
  }
  this->actor.flags &= ~0x20;
  func_80B7FA84(this);
}

void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaMirror* this = (BgIkanaMirror*)thisx;
    this->actionFunc(this, globalCtx); 
}

void BgIkanaMirror_Draw(Actor *thisx, GlobalContext *globalCtx)
{
  s32 pad;
  BgIkanaMirror *this = (BgIkanaMirror *) thisx;
  OPEN_DISPS(globalCtx->state.gfxCtx);

  func_8012C28C(globalCtx->state.gfxCtx);
  func_8012C2DC(globalCtx->state.gfxCtx);
  gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
  gSPDisplayList(POLY_OPA_DISP++, (u32) (&D_06001E18));
  if (this->unk5C6 > 0)
  {
    AnimatedMat_Draw(globalCtx, this->unk5BC);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->unk5C6);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(POLY_XLU_DISP++, (u32) (&D_060014B0));
  }
  if (this->unk5C7 > 0)
  {
    f32 temp_fv0 = this->unk5C7 * (1.0f / 255.0f);
    s32 pad2[2];
    AnimatedMat_Draw(globalCtx, this->unk5C0);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (s32) (temp_fv0 * 123.0f));
    gDPSetEnvColor(POLY_XLU_DISP++, 215, 215, 255, (s32) (temp_fv0 * 185.0f));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(POLY_XLU_DISP++, (u32) (&D_06001880));
  }
  CLOSE_DISPS(globalCtx->state.gfxCtx);
}