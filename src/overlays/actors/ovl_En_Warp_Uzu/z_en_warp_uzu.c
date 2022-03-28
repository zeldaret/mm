/*
 * File: z_en_warp_uzu.c
 * Overlay: ovl_En_Warp_Uzu
 * Description: Pirates Fortress Telescope
 */

#include "z_en_warp_uzu.h"
#include "objects/object_warp_uzu/object_warp_uzu.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnWarpUzu*)thisx)

void EnWarpUzu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A66208(EnWarpUzu* this, GlobalContext* globalCtx);
void func_80A66278(EnWarpUzu* this, GlobalContext* globalCtx);
void func_80A66384(EnWarpUzu* this, GlobalContext* globalCtx);
void EnWarpUzu_DoNothing(EnWarpUzu* this, GlobalContext* globalCtx);

const ActorInit En_Warp_Uzu_InitVars = {
    ACTOR_EN_WARP_UZU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WARP_UZU,
    sizeof(EnWarpUzu),
    (ActorFunc)EnWarpUzu_Init,
    (ActorFunc)EnWarpUzu_Destroy,
    (ActorFunc)EnWarpUzu_Update,
    (ActorFunc)EnWarpUzu_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 25, 43, -20, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void EnWarpUzu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWarpUzu* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    thisx->targetMode = 0;
    func_80A66208(this, globalCtx);
}

void EnWarpUzu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWarpUzu* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

static Vec3f D_80A664FC = { 0.0f, 53.0f, -29.0f };
void func_80A66208(EnWarpUzu* this, GlobalContext* globalCtx) {
    Vec3f sp24;

    this->actor.textId = 0;
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_MultiplyVector3fByState(&D_80A664FC, &sp24);
    Math_Vec3f_Sum(&this->actor.world.pos, &sp24, &this->actor.focus.pos);
    Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.shape.rot);
    this->actionFunc = func_80A66278;
}

void func_80A66278(EnWarpUzu* this, GlobalContext* globalCtx) {
    Player* player;
    s16 temp_v0;
    s16 phi_a0;
    s16 phi_v1;

    do {
        player = GET_PLAYER(globalCtx);
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            func_80A66384(this, globalCtx);
        } else {
            phi_a0 = ABS((s16)(Actor_YawBetweenActors(&this->actor, &player->actor) - this->actor.shape.rot.y));
            temp_v0 = player->actor.shape.rot.y - this->actor.shape.rot.y;
            phi_v1 = ABS(temp_v0);
            if (phi_a0 >= 0x2AAB) {
                if (phi_v1 < 0x238E) {
                    func_800B8614(&this->actor, globalCtx, 70.0f);
                }
            }
        }
    } while (0);
}

void func_80A66384(EnWarpUzu* this, GlobalContext* globalCtx) {
    globalCtx->nextEntranceIndex = 0x22A0;
    gSaveContext.respawn[RESTART_MODE_DOWN].entranceIndex = globalCtx->nextEntranceIndex;
    func_80169EFC(&globalCtx->state);
    gSaveContext.respawnFlag = -2;
    this->actionFunc = EnWarpUzu_DoNothing;
}

void EnWarpUzu_DoNothing(EnWarpUzu* this, GlobalContext* globalCtx) {
}

void EnWarpUzu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnWarpUzu* this = THIS;
    s32 pad;

    this->actor.uncullZoneForward = 1000.0f;
    this->actionFunc(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnWarpUzu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_warp_uzu_DL_000EC0);
}
