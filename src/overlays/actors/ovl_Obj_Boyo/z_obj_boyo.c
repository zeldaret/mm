#include "z_obj_boyo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(ObjBoyo* thisx, PlayState* play);
void ObjBoyo_Destroy(ObjBoyo* thisx, PlayState* play);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(ObjBoyo* thisx, PlayState* play);

void ObjBoyo_PushPlayer(ObjBoyo* this, Actor* player);
void func_809A5DE0(Actor* actor, ObjBoyo* this);
void func_809A5E14(Actor* arg0, ObjBoyo* this);
Actor* func_809A5E24(ObjBoyo* this, PlayState* play, u32* index);

f32 D_809A61D4 = 0.01f;
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
static ColliderCylinderInit sColliderCylinderInit = {
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
static InitChainEntry sInitChainEntry[5] = { 0xB0FC0FA0, 0xB100012C, 0xB104012C, 0x48580064,
                                             0x00000000 }; /* unable to generate initializer */

typedef void (*func_unk)(ObjBoyo* this, Actor* actor);
typedef struct {
    /* 0x0 */ func_unk unk_0;
    /* 0x4 */ u8 unk_4[4];
} Struct809A61B0; /* Size 0x8 */

static Struct809A61B0 D_809A61B0[] = { { ObjBoyo_PushPlayer, { 0, 0, 0, 0 } } };

extern s16 D_809A61B4[0xE];
//     0x021D0000, func_809A5DE0, 0x00090000, func_809A5E14, 0x0, 0x0, 0x0, 0x0
// }; /* unable to generate initializer */

/********************** INIT **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Init.s")
// MATCHING
void ObjBoyo_Init(ObjBoyo* this, PlayState* play) {
    ColliderCylinder* temp_a1;

    Actor_ProcessInitChain(&this->actor, sInitChainEntry);
    temp_a1 = &this->collider;
    // sp20 = temp_a1;
    Collider_InitCylinder(play, temp_a1);
    Collider_SetCylinder(play, temp_a1, &this->actor, &sColliderCylinderInit);
    Collider_UpdateCylinder(&this->actor, temp_a1);
    this->actor.colChkInfo.mass = 0xFF;
    this->animatedMaterial = Lib_SegmentedToVirtual((void*)&D_06000E88);
}

/********************** DESTROY **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Destroy.s")
// MATCHING
void ObjBoyo_Destroy(ObjBoyo* thisx, PlayState* play) {
    Collider_DestroyCylinder(play, &THIS->collider);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_PushPlayer.s")
// ObjBoyo_PushPlayer
void ObjBoyo_PushPlayer(ObjBoyo* this, Actor* player) {
    ((Player*)player)->pushedSpeed = 30.0f;
    ((Player*)player)->pushedYaw = (s16)this->actor.yawTowardsPlayer;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5DE0.s")
// MATCHING
void func_809A5DE0(Actor* actor, ObjBoyo* this) {
    this->pushedSpeed = 30.0f;                                              // push speed
    this->yawTowardsActor = Actor_WorldYawTowardActor(actor, &this->actor); // push direction
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E14.s")
void func_809A5E14(Actor* arg0, ObjBoyo* this) {
    // some kind of reset ?
    // arg1->unk1F0 = 0;
    this->unk1F0 = 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E24.s")
/*
 * Return first actor of type 2 (supposing actorList is deterministic)
 * or
 * look for the address A in D_809A61B4 matching the address in *this->unk150
 * arg2 is the index of the address into D_809A61B4.
 */
// ALMOST MATCHING:
// only diff is $a0 and $a1 being set in the inverse order.
// no clue on how to make the cpu rearrange it without
// messing with all the asm.
Actor* func_809A5E24(ObjBoyo* this, PlayState* play, u32* index) {
    Actor* collidedActor;
    s16* data;
    u32 counter;

    if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
        *index = 0;
        // Returns first actor of the actor List for actors of type Player.
        // In short it gets the player's Actor*.
        return (s32)play->actorCtx.actorLists[2].first;
    }
    data = D_809A61B4;
    if (this->collider.base.ocFlags1 & OC1_HIT) {
        collidedActor = this->collider.base.oc;
        counter = 1;
    loop_4:
        if (collidedActor->id == *data) {
            *index = counter;
            return collidedActor;
        }
        data += 4;
        counter += 1;
        if (3 != counter) {
            goto loop_4;
        }
    }
    return 0;
}

/********************** UPDATE **********************/
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Update.s")
void ObjBoyo_Update(Actor* thisx, PlayState* play2) {
    CollisionCheckContext* tempCollisionChkCxt;
    ColliderCylinder* tempCollider;
    f32 temp_fv1;
    s16 temp_v0_2;
    PlayState* play = play2;
    ObjBoyo* this = THIS;
    Actor* dataPtr;
    u32 index;

    dataPtr = func_809A5E24(this, play, &index);

    if (dataPtr != 0) {
        D_809A61B0[index].unk_0(this, dataPtr);
        // TODO: find out what all of these are.
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
        // this computation might help finding what those values are.
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
        if (this->collider.base.acFlags & AC_HIT) {
            // TODO: find out what all of these are.
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
    tempCollisionChkCxt = &play->colChkCtx;
    tempCollider = &this->collider;
    CollisionCheck_SetOC(play, tempCollisionChkCxt, &tempCollider->base);
    if (this->actor.xzDistToPlayer < 2000.0f) {
        CollisionCheck_SetAC(play, tempCollisionChkCxt, &tempCollider->base);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Draw.s")
extern Gfx D_06000300;

void ObjBoyo_Draw(ObjBoyo* this, PlayState* play) {
    AnimatedMat_Draw(play, this->animatedMaterial);
    Gfx_DrawDListOpa(play, &D_06000300);
}
