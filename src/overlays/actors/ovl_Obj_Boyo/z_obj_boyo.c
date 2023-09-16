#include "z_obj_boyo.h"

#define ACTOR_COLLISION_HANDLING_CASES 4

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(ObjBoyo* this, PlayState* play);
void ObjBoyo_Destroy(ObjBoyo* thisx, PlayState* play);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(ObjBoyo* this, PlayState* play);

void ObjBoyo_PushPlayer(Actor* thisx, Actor* player);
void func_809A5DE0(Actor* actor, Actor* thisx);
void func_809A5E14(Actor* arg0, Actor* thisx);
Actor* ObjBoyo_FindCollidedActor(ObjBoyo* this, PlayState* play, u32* index);

const ActorInit Obj_Boyo_InitVars = { ACTOR_OBJ_BOYO,
                                      ACTORCAT_PROP,
                                      FLAGS,
                                      OBJECT_BOYO,
                                      sizeof(ObjBoyo),
                                      (ActorFunc)ObjBoyo_Init,
                                      (ActorFunc)ObjBoyo_Destroy,
                                      (ActorFunc)ObjBoyo_Update,
                                      (ActorFunc)ObjBoyo_Draw };

typedef void (*ObjBoyoCollisionHandler)(Actor* actor_a, Actor* actor_b);

typedef struct ObjBoyoUnkStruct {
    /* 0x0 */ ObjBoyoCollisionHandler colHandler;
    /* 0x4 */ s16 id;
} ObjBoyoUnkStruct; // size = 0x8

static AnimatedMaterial* D_06000E88;

static ColliderCylinderInit gColliderCylinderInit = {
    {
        /* ColliderInit base */
        COLTYPE_NONE,                                       /* u8 coltype */
        AT_NONE,                                            /* u8 atFlags */
        AC_TYPE_PLAYER | AC_HARD | AC_ON,                   /* u8 acFlags */
        OC1_TYPE_2 | OC1_TYPE_1 | OC1_TYPE_PLAYER | OC1_ON, /* u8 ocFlags1 */
        OC2_TYPE_2,                                         /* u8 ocFlags2 */
        COLSHAPE_CYLINDER                                   /* u8 shape */
    },
    {
        /* ColliderInfoInit info */
        ELEMTYPE_UNK0, /* u8 elemType */
        { 0x00000000 /* u32 dmgFlags */, 0x00 /* u8 effect */, 0x00 /* u8 defense */ },
        { 0x01CBFFBE /* u32 dmgFlags */, 0x00 /* u8 effect */, 0x00 /* u8 defense */ },
        TOUCH_NONE, /* u8 toucherFlags */
        BUMP_ON,    /* u8 bumperFlags */
        OCELEM_ON   /* u8 ocElemFlags */
    },
    { 60 /* s16 radius */, 140 /* s16 height */, 0 /* yShift */, { 0 /* s16 x */, 0 /* s16 y */, 0 /*s16 z */ } },
};

static InitChainEntry gInitChainEntry[5] = { 0xB0FC0FA0, 0xB100012C, 0xB104012C, 0x48580064,
                                             0x00000000 }; /* unable to generate initializer */

static objBoyoUnkStruct gCollisionHandling[] = {
    { ObjBoyo_PushPlayer, 0x021D0000 }, { func_809A5DE0, 0x00090000 }, { func_809A5E14, 0x0 }, { NULL, 0x0 }
};

void ObjBoyo_Init(ObjBoyo* this, PlayState* play) {
    ColliderCylinder* temp_a1;

    Actor_ProcessInitChain(&this->actor, gInitChainEntry);
    temp_a1 = &this->collider;
    Collider_InitCylinder(play, temp_a1);
    Collider_SetCylinder(play, temp_a1, &this->actor, &gColliderCylinderInit);
    Collider_UpdateCylinder(&this->actor, temp_a1);
    this->actor.colChkInfo.mass = 0xFF;
    this->animatedMaterial = Lib_SegmentedToVirtual((void*)&D_06000E88);
}

void ObjBoyo_Destroy(ObjBoyo* thisx, PlayState* play) {
    Collider_DestroyCylinder(play, &THIS->collider);
}

void ObjBoyo_PushPlayer(Actor* thisx, Actor* player) {
    ((Player*)player)->pushedSpeed = 30.0f;
    ((Player*)player)->pushedYaw = (s16)THIS->actor.yawTowardsPlayer;
}

void func_809A5DE0(Actor* actor, Actor* thisx) {
    THIS->pushedSpeed = 30.0f;                                       // push speed
    THIS->yawTowardsActor = Actor_WorldYawTowardActor(actor, thisx); // push direction
}

void func_809A5E14(Actor* arg0, Actor* thisx) {
    // some kind of reset ?
    THIS->unk1F0 = 0;
}

/*
 * Find the Actor we collided with.
 */
Actor* ObjBoyo_FindCollidedActor(ObjBoyo* this, PlayState* play, u32* index) {
    Actor* collidedActor;
    ObjBoyoUnkStruct* data;
    u32 counter;

    if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
        *index = 0;
        // Returns first actor of the actor List for actors of type Player.
        // In short it gets the player's Actor*.
        return (s32)play->actorCtx.actorLists[2].first;
    }
    data = gCollisionHandling;
    if (this->collider.base.ocFlags1 & OC1_HIT) {
        collidedActor = this->collider.base.oc;
        for (counter = 1; counter != 3; ++counter) {
            if (collidedActor->id == (*data).id) {
                *index = counter;
                return collidedActor;
            }
            data += 4;
        }
    }
    return 0;
}

void ObjBoyo_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjBoyo* this = THIS;
    Actor* dataPtr;
    u32 index;

    dataPtr = ObjBoyo_FindCollidedActor(this, play, &index);

    if (dataPtr != 0) {
        gCollisionHandling[index].colHandler(&(this->actor), dataPtr);
        // TODO: find out what all of these are.

        this->unk194 = 0x64;
        this->unk196 = 3;
        this->unk198 = 0.01f;
        this->unk19C = 0.03f;
        this->unk1A4 = 0x3F40;
        this->unk1A6 = 0x7D0;
        this->unk1A8 = 0;
        this->unk1A0 = 0.03f;
        this->unk1AA = 0x2DF7;
        this->unk1AC = 0x258;
    }

    if (this->unk194 > 0) { /* compute new scaling */
        // this computation might help finding what those values are.

        this->unk194 -= this->unk196;
        this->unk1AA += this->unk1AC;
        this->unk1A8 += this->unk1AA;

        this->actor.scale.x = this->actor.scale.z =
            (Math_CosS((s16)(this->unk1A8 + this->unk1A4)) * (f32)this->unk194 * this->unk19C * this->unk198) + 0.1f;

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
            this->unk1A0 = 0.006f;
            this->unk1A4 = 0x3F40;
            this->unk1A6 = 0x7D0;
            this->unk1A8 = 0;
            this->unk1AA = 0x3A98;
            this->unk1AC = 0x640;
        }
    }
    this->collider.base.acFlags &= 0xFFFD;
    this->collider.base.ocFlags1 &= 0xFFFD;
    this->collider.base.ocFlags2 &= 0xFFFE;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    if (this->actor.xzDistToPlayer < 2000.0f) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}
static Gfx* D_06000300;
void ObjBoyo_Draw(ObjBoyo* this, PlayState* play) {
    AnimatedMat_Draw(play, this->animatedMaterial);
    Gfx_DrawDListOpa(play, D_06000300);
}
