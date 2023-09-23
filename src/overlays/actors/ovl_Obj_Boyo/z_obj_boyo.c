#include "z_obj_boyo.h"
#include "assets/objects/object_boyo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, PlayState* play);
void ObjBoyo_Destroy(Actor* thisx, PlayState* play2);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(Actor* thisx, PlayState* play);

void ObjBoyo_PushPlayer(ObjBoyo* this, Actor* actor);
void ObjBoyo_PushPirate(ObjBoyo* this, Actor* actor);
void ObjBoyo_ExplodeBomb(ObjBoyo* this, Actor* actor);
Actor* ObjBoyo_FindCollidedActor(ObjBoyo* this, PlayState* play, s32* index);

const ActorInit Obj_Boyo_InitVars = {
    ACTOR_OBJ_BOYO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOYO,
    sizeof(ObjBoyo),
    (ActorFunc)ObjBoyo_Init,
    (ActorFunc)ObjBoyo_Destroy,
    (ActorFunc)ObjBoyo_Update,
    (ActorFunc)ObjBoyo_Draw,
};

typedef void (*ObjBoyoCollisionHandler)(ObjBoyo* this, Actor* actor);

typedef struct ObjBoyoUnkStruct {
    /* 0x0 */ s16 id;
    /* 0x4 */ ObjBoyoCollisionHandler colHandler;
} ObjBoyoUnkStruct; // size = 0x8

static AnimatedMaterial* D_06000E88 = object_boyo_Matanimheader_000E88;

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_TYPE_PLAYER | AC_HARD | AC_ON,
        OC1_TYPE_2 | OC1_TYPE_1 | OC1_TYPE_PLAYER | OC1_ON,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01CBFFBE, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    {
        60,
        140,
        0,
        { 0, 0, 0 },
    },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static ObjBoyoUnkStruct gCollisionHandling[] = {
    { ACTOR_PLAYER, ObjBoyo_PushPlayer },
    { ACTOR_EN_KAIZOKU, ObjBoyo_PushPirate },
    { ACTOR_EN_BOM, ObjBoyo_ExplodeBomb },
};

void ObjBoyo_Init(Actor* thisx, PlayState* play) {
    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->actor.colChkInfo.mass = 0xFF;
    this->animatedMaterial = Lib_SegmentedToVirtual((void*)&D_06000E88);
}

void ObjBoyo_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjBoyo* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void ObjBoyo_PushPlayer(ObjBoyo* this, Actor* actor) {
    ((Player*)actor)->pushedSpeed = 30.0f;
    ((Player*)actor)->pushedYaw = (s16)this->actor.yawTowardsPlayer;
}

void ObjBoyo_PushPirate(ObjBoyo* this, Actor* actor) {
    this->pushedSpeed = 30.0f;                                       // push speed
    this->yawTowardsActor = Actor_WorldYawTowardActor(actor, thisx); // push direction
}

void ObjBoyo_ExplodeBomb(ObjBoyo* this, Actor* actor) {
    this->unk1F0 = 0;
}

/*
 * Find the Actor we collided with.
 */
Actor* ObjBoyo_FindCollidedActor(ObjBoyo* this, PlayState* play, s32* index) {
    Actor* collidedActor;
    ObjBoyoUnkStruct* data;
    s32 counter;

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
static Gfx* D_06000300 = object_boyo_DL_000300;
void ObjBoyo_Draw(Actor* thisx, PlayState* play) {
    AnimatedMat_Draw(play, this->animatedMaterial);
    Gfx_DrawDListOpa(play, D_06000300);
}
