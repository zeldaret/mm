#include "z_obj_boyo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, PlayState* play);
void ObjBoyo_Destroy(Actor* thisx, PlayState* play2);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(Actor* thisx, PlayState* play);

/*
 * From Z64Utils
 * Segment: 0xFF (0x08)
 * Type: Two Tex Scroll
 * Params Seg: 0x06000E80
 */
extern AnimatedMaterial* D_06000E88;

#if 0
const ActorInit Obj_Boyo_InitVars = {
    ACTOR_OBJ_BOYO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOYO,
    sizeof(ObjBoyo),
    (ActorFunc)ObjBoyo_Init,
    (ActorFunc)ObjBoyo_Destroy,
    (ActorFunc)ObjBoyo_Update,
    (ActorFunc)ObjBoyo_Draw
};

#endif

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Init.s")
// D_809A6170
static ColliderCylinderInit Obj_Boyo_ColliderCylinderInit = {
    {
        /* ColliderInit base */
        0xA,  /* u8 coltype */
        0,    /* u8 atFlags */
        0xD,  /* u8 acFlags */
        0x39, /* u8 ocFlags1 */
        0x20, /* u8 ocFlags2 */
        1     /* u8 shape */
    },
    {
        /* ColliderInfoInit info */
        0, /* u8 elemType */
        {  /* ColliderTouchInit toucher */
          0 /* u32 dmgFlags */, 0 /* u8 effect */, 0 /* u8 defense */ },
        {
            /* ColliderBumpInit  bumper */
            0x01CBFFBE /* u32 dmgFlags */, 0 /* u8 effect */, 0 /* u8 defense */
        },
        0, /* u8 toucherFlags */
        1, /* u8 bumperFlags */
        1  /* u8 ocElemFlags */
    },
    { /* Cylinder16 dim */
      0x3C /* s16 radius */,
      0x8C /* s16 height */,
      0 /* yShift */,
      {
          /* Vec3s pos */
          0, /* s16 x */
          0, /* s16 y */
          0  /*s16 z */
      } },
};

// D_809A619C
static InitChainEntry Obj_Boyo_InitChainEntry[5] = { 0xB0FC0FA0, 0xB100012C, 0xB104012C, 0x48580064,
                                                     0x00000000 }; /* unable to generate initializer */

typedef void (*func_unk)(ObjBoyo* this, Actor* actor);

typedef struct {
    /* 0x0 */ func_unk unk_0;
    /* 0x4 */ u8 unk_4[0x4];
} struct_809A61B0; /* Size 0x8 */

extern struct_809A61B0 D_809A61B0[] = { { func_809A5DC0, { 0, 0, 0, 0 } } };

static s32 D_809A61B4[0x8] = {
    0x021D0000, func_809A5DE0, 0x00090000, func_809A5E14, 0x0, 0x0, 0x0, 0x0
}; /* unable to generate initializer */

/********************** INIT **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Init.s")
void ObjBoyo_Init(Actor* thisx, PlayState* play) {
    ColliderCylinder* sp20;
    ColliderCylinder* temp_a1;
    ObjBoyo* this = THIS;

    Actor_ProcessInitChain(&this->actor, Obj_Boyo_InitChainEntry);
    temp_a1 = &this->collider;
    sp20 = temp_a1;
    Collider_InitCylinder(play, temp_a1);
    Collider_SetCylinder(play, temp_a1, &this->actor, &Obj_Boyo_ColliderCylinderInit);
    Collider_UpdateCylinder(&this->actor, temp_a1);
    this->actor.colChkInfo.mass = 0xFF;
    this->animated_material = Lib_SegmentedToVirtual((void*)&D_06000E88);
}

/********************** DESTROY **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Destroy.s")
void ObjBoyo_Destroy(Actor* thisx, PlayState* play2) {
    ObjBoyo* this = THIS;
    Collider_DestroyCylinder(play2, &this->collider);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5DC0.s")
void func_809A5DC0(Actor* actor_a, Actor* actor_b) {
    actor_b->unkB80 = 30.0f;
    actor_b->unkB84 = (s16)actor_a->unk92;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5DE0.s")
void func_809A5DE0(Actor* actor, Actor* actor_b) {
    actor_b->unk2F0 = 30.0f;
    actor_b->yawTowardsPlayer = Actor_WorldYawTowardActor(actor_a, actor_b);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E14.s")
void func_809A5E14(s32 arg0, void* arg1) {
    arg1->unk1F0 = 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E24.s")
/*
 * Return first actor of type 2 (supposing actorList is deterministic)
 * or
 * look for the address A in D_809A61B4 matching the address in *this->unk150
 * arg2 is the index of the address into D_809A61B4.
 */
s32 func_809A5E24(ObjBoyo* this, PlayState* play, s32* index) {
    s32* temp_v1;
    s32* data;
    s32 counter;

    if (this->unk157 & 1) {
        *index = 0;
        /* Returns first actor of the actor List for actors of types ??? */
        return (s32)play->actorCtx.actorLists[2].first;
    }
    data = D_809A61B4;
    if (this->unk156 & 2) {
        temp_v1 = this->unk150; // Address of target data.
        counter = 1;
    loop_4:
        if (*temp_v1 == *data) {
            *index = counter;
            return temp_v1;
        }
        counter += 1;
        data += 8;
        if (counter == 3) {
            return 0;
        }
        goto loop_4;
    }
    return 0;
}

/********************** UPDATE **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Update.s")
void ObjBoyo_Update(Actor* thisx, PlayState* play2) {
    s32 index;
    CollisionCheckContext* temp_a1;
    ColliderCylinder* sp20;
    ColliderCylinder* temp_a2;
    CollisionCheckContext* sp24;
    f32 temp_fv1;
    s16 temp_v0_2;
    Actor* temp_v0;
    ObjBoyo* this = THIS;

    temp_v0 = func_809A5E24(this, play2, &index);
    if (temp_v0 != 0) {
        D_809A61B0[index].unk_0(this, temp_v0);
        this->unk194 = 0x64;
        this->unk196 = 3;
        this->unk1A4 = 0x3F40;
        this->unk1A6 = 0x7D0;
        this->unk1A8 = 0;
        this->unk1AA = 0x2DF7;
        this->unk1AC = 0x258;
        this->unk19C = 0.03f;
        this->unk1A0 = 0.03f;
        this->unk198 = 0.01f;
    }
    temp_v0_2 = this->unk194;
    if (temp_v0_2 > 0) { /* compute new scaling */
        this->unk1AA += this->unk1AC;
        this->unk1A8 += this->unk1AA;
        this->unk194 = temp_v0_2 - this->unk196;
        temp_fv1 =
            (Math_CosS((s16)(this->unk1A8 + this->unk1A4)) * (f32)this->unk194 * this->unk19C * this->unk198) + 0.1f;
        this->actor.scale.z = temp_fv1;
        this->actor.scale.x = temp_fv1;
        this->actor.scale.y =
            (Math_CosS((s16)(this->unk1A8 + this->unk1A6)) * (f32)this->unk194 * this->unk1A0 * this->unk198) + 0.1f;
    } else {
        Actor_SetScale(&this->actor, 0.1f);
        if (this->collider.base.acFlags & 2) {
            this->unk194 = 0x1E;
            this->unk196 = 2;
            this->unk198 = 0.033333335f;
            this->unk19C = 0.012f;
            this->unk1A4 = 0x3F40;
            this->unk1A6 = 0x7D0;
            this->unk1A8 = 0;
            this->unk1AA = 0x3A98;
            this->unk1AC = 0x640;
            this->unk1A0 = 0.006f;
        }
    }
    this->collider.base.acFlags &= 0xFFFD;
    this->collider.base.ocFlags1 &= 0xFFFD;
    this->collider.base.ocFlags2 &= 0xFFFE;
    temp_a1 = &play2->colChkCtx;
    temp_a2 = &this->collider;
    sp20 = temp_a2;
    sp24 = temp_a1;
    CollisionCheck_SetOC(play2, temp_a1, &temp_a2->base);
    if (this->actor.xzDistToPlayer < 2000.0f) {
        CollisionCheck_SetAC(play2, temp_a1, &temp_a2->base);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Draw.s")
extern Gfx dList;

void ObjBoyo_Draw(Actor* thisx, PlayState* play) {
    ObjBoyo* this = THIS;
    AnimatedMat_Draw(play, this->animated_material);
    Gfx_DrawDListOpa(play, &dList);
}
