/*
 * File: z_en_boyo.c
 * Overlay: ovl_En_Boyo
 * Description: Unused trap
 */

#include "z_obj_boyo.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Kaizoku/z_en_kaizoku.h"
#include "assets/objects/object_boyo/object_boyo.h"

#define FLAGS 0x00000010

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, PlayState* play);
void ObjBoyo_Destroy(Actor* thisx, PlayState* play2);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(Actor* thisx, PlayState* play2);

ActorInit Obj_Boyo_InitVars = {
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

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01CBFFBE, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 140, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjBoyo_Init(Actor* thisx, PlayState* play) {
    ObjBoyo* this = (ObjBoyo*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(play, &this->unk_144);
    Collider_SetCylinder(play, &this->unk_144, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->unk_144);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_190 = Lib_SegmentedToVirtual(object_boyo_Matanimheader_000E88);
}

void ObjBoyo_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjBoyo* this = (ObjBoyo*)thisx;

    Collider_DestroyCylinder(play, &this->unk_144);
}

void func_809A5DC0(ObjBoyo* this, Actor* actor) {
    Player* player = (Player*)actor;

    player->unk_B80 = 30.0f;
    player->unk_B84 = this->actor.yawTowardsPlayer;
}

void func_809A5DE0(ObjBoyo* this, Actor* actor) {
    EnKaizoku* pirate = (EnKaizoku*)actor;

    pirate->unk_2F0 = 30.0f;
    pirate->unk_2F4 = Actor_YawBetweenActors(&this->actor, &pirate->actor);
}

void func_809A5E14(ObjBoyo* this, Actor* actor) {
    EnBom* bomb = (EnBom*)actor;

    bomb->timer = 0;
}

typedef struct {
    s16 actorId;
    void (*hitFunc)(ObjBoyo* this, Actor* actor);
} ObjBoyoHitInfo;

static ObjBoyoHitInfo sActorHitInfo[] = {
    { ACTOR_PLAYER, func_809A5DC0 },
    { ACTOR_EN_KAIZOKU, func_809A5DE0 },
    { ACTOR_EN_BOM, func_809A5E14 },
};

Actor* func_809A5E24(ObjBoyo* this, PlayState* play, s32* index) {
    if (this->unk_144.base.ocFlags2 & OC2_HIT_PLAYER) {
        *index = 0;
        return (Actor*)GET_PLAYER(play);
    } else if (this->unk_144.base.ocFlags1 & OC1_HIT) {
        Actor* hitActor = this->unk_144.base.oc;
        ObjBoyoHitInfo* hitInfo = &sActorHitInfo[1];
        s32 i;

        for (i = 1; i < ARRAY_COUNT(sActorHitInfo); i++, hitInfo++) {
            if (hitInfo->actorId == hitActor->id) {
                *index = i;
                return hitActor;
            }
        }
    }
    return NULL;
}

void ObjBoyo_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjBoyo* this = (ObjBoyo*)thisx;
    Actor* hitActor;
    s32 index;

    hitActor = func_809A5E24(this, play, &index);
    if (hitActor != NULL) {
        sActorHitInfo[index].hitFunc(this, hitActor);
        this->unk_194 = 100;
        this->unk_196 = 3;
        this->unk_198 = 1.0f / 100.0f;
        this->unk_19C = 0.03f;
        this->unk_1A0 = 0.03f;
        this->unk_1A4 = 0x3F40;
        this->unk_1A6 = 0x7D0;
        this->unk_1A8 = 0;
        this->unk_1AA = 0x2DF7;
        this->unk_1AC = 0x258;
    }
    if (this->unk_194 > 0) {
        this->unk_194 -= this->unk_196;
        this->unk_1AA += this->unk_1AC;
        this->unk_1A8 += this->unk_1AA;

        this->actor.scale.x = this->actor.scale.z =
            0.1f + (Math_CosS(this->unk_1A8 + this->unk_1A4) * this->unk_194 * this->unk_19C * this->unk_198);
        this->actor.scale.y =
            0.1f + (Math_CosS(this->unk_1A8 + this->unk_1A6) * this->unk_194 * this->unk_1A0 * this->unk_198);
    } else {
        Actor_SetScale(&this->actor, 0.1f);
        if (this->unk_144.base.acFlags & AC_HIT) {
            this->unk_194 = 30;
            this->unk_196 = 2;
            this->unk_198 = 1.0f / 30.0f;
            this->unk_19C = 0.012f;
            this->unk_1A0 = 0.006f;
            this->unk_1A4 = 0x3F40;
            this->unk_1A6 = 0x7D0;
            this->unk_1A8 = 0;
            this->unk_1AA = 0x3A98;
            this->unk_1AC = 0x640;
        }
    }
    this->unk_144.base.acFlags &= ~AC_HIT;
    this->unk_144.base.ocFlags1 &= ~OC1_HIT;
    this->unk_144.base.ocFlags2 &= ~OC2_HIT_PLAYER;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_144.base);
    if (this->actor.xzDistToPlayer < 2000.0f) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_144.base);
    }
}

void ObjBoyo_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjBoyo* this = (ObjBoyo*)thisx;

    AnimatedMat_Draw(play, this->unk_190);
    Gfx_DrawDListOpa(play, object_boyo_DL_000300);
}
