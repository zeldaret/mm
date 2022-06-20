/*
 * File: z_obj_boyo.c
 * Overlay: ovl_Obj_Boyo
 * Description: Unused Bumper
 */

#include "z_obj_boyo.h"
#include "overlays/actors/ovl_En_Kaizoku/z_en_kaizoku.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/object_boyo/object_boyo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoyo_Destroy(Actor* thisx, GlobalContext* globalCtx2);
void ObjBoyo_Update(Actor* thisx, GlobalContext* globalCtx2);
void ObjBoyo_Draw(Actor* thisx, GlobalContext* globalCtx);

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

void ObjBoyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoyo* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_190 = Lib_SegmentedToVirtual(object_boyo_Matanimheader_000E88);
}

void ObjBoyo_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjBoyo* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void ObjBoyo_UpdatePlayerBumpValues(ObjBoyo* this, Player* target) {
    target->unk_B80 = 30.0f;
    target->unk_B84 = this->actor.yawTowardsPlayer;
}

void ObjBoyo_UpdatePirateBumpValues(ObjBoyo* src, EnKaizoku* target) {
    target->unk_2F0 = 30.0f;
    target->unk_2F4 = Actor_YawBetweenActors(&src->actor, &target->actor);
}

void ObjBoyo_UpdateBombBumpValues(ObjBoyo* src, EnBom* target) {
    target->timer = 0;
}

BumperCollideInfo sBumperCollideInfo[] = {
    { ACTOR_PLAYER, (BumperCollideActorFunc)ObjBoyo_UpdatePlayerBumpValues },
    { ACTOR_EN_KAIZOKU, (BumperCollideActorFunc)ObjBoyo_UpdatePirateBumpValues },
    { ACTOR_EN_BOM, (BumperCollideActorFunc)ObjBoyo_UpdateBombBumpValues },
};

Actor* ObjBoyo_GetCollidedActor(ObjBoyo* this, GlobalContext* globalCtx, s32* num) {
    Actor* collideActor;
    BumperCollideInfo* collideInfo;
    s32 i;

    if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
        *num = 0;
        return &GET_PLAYER(globalCtx)->actor;
    }

    if (this->collider.base.ocFlags1 & OC2_UNK1) {
        for (collideActor = this->collider.base.oc, collideInfo = &sBumperCollideInfo[1], i = 1; i < 3;
             collideInfo++, i++) {
            if (collideInfo->id == collideActor->id) {
                *num = i;
                return collideActor;
            }
        }
    }

    return NULL;
}

void ObjBoyo_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjBoyo* this = THIS;
    Actor* target;
    s32 num;

    target = ObjBoyo_GetCollidedActor(this, globalCtx, &num);

    if (target != NULL) {
        sBumperCollideInfo[num].actorCollideFunc(this, (void*)target);
        this->unk_194 = 100;
        this->unk_196 = 3;
        this->unk_198 = 0.01f;
        this->unk_19C = this->unk_1A0 = 0.03f;
        this->unk_1A4 = 0x3F40;
        this->unk_1A6 = 2000;
        this->unk_1A8 = 0;
        this->unk_1AA = 0x2DF7;
        this->unk_1AC = 600;
    }

    if (this->unk_194 > 0) {
        this->unk_194 -= this->unk_196;
        this->unk_1AA += this->unk_1AC;
        this->unk_1A8 += this->unk_1AA;

        this->actor.scale.x = this->actor.scale.z =
            (Math_CosS(this->unk_1A8 + this->unk_1A4) * this->unk_194 * this->unk_19C * this->unk_198) + 0.1f;
        this->actor.scale.y =
            (Math_CosS(this->unk_1A8 + this->unk_1A6) * this->unk_194 * this->unk_1A0 * this->unk_198) + 0.1f;
    } else {
        Actor_SetScale(&this->actor, 0.1f);

        if (this->collider.base.acFlags & AC_HIT) {
            this->unk_194 = 30;
            this->unk_196 = 2;
            this->unk_198 = 0.033333335f;
            this->unk_19C = 0.012f;
            this->unk_1A0 = 0.006f;
            this->unk_1A4 = 0x3F40;
            this->unk_1A6 = 2000;
            this->unk_1A8 = 0;
            this->unk_1AA = 15000;
            this->unk_1AC = 1600;
        }
    }

    this->collider.base.acFlags &= ~AC_HIT;
    this->collider.base.ocFlags1 &= ~OC1_HIT;
    this->collider.base.ocFlags2 &= ~OC2_HIT_PLAYER;

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (thisx->xzDistToPlayer < 2000.0f) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void ObjBoyo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoyo* this = THIS;

    AnimatedMat_Draw(globalCtx, this->unk_190);
    Gfx_DrawDListOpa(globalCtx, object_boyo_DL_000300);
}
