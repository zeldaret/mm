#include "z_bg_goron_oyu.h"

#define FLAGS 0x00000030

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*const ActorInit Bg_Goron_Oyu_InitVars = {
    ACTOR_BG_GORON_OYU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OYU,
    sizeof(BgGoronOyu),
    (ActorFunc)BgGoronOyu_Init,
    (ActorFunc)BgGoronOyu_Destroy,
    (ActorFunc)BgGoronOyu_Update,
    (ActorFunc)BgGoronOyu_Draw,
};*/

void func_80B40100(BgGoronOyu* _this, GlobalContext* globalCtx);
void func_80B400C8(BgGoronOyu* _this, GlobalContext* globalCtx);
void func_80B401F8(BgGoronOyu* _this, GlobalContext* globalCtx);
void func_80B40308(BgGoronOyu* _this, GlobalContext* globalCtx);
void func_80B40394(BgGoronOyu* _this, GlobalContext* globalCtx);
void func_80B40160(BgGoronOyu* _this, GlobalContext* globalCtx);

void func_80B40080(BgGoronOyu* _this) {
    _this->unk17E = 1;
    _this->actionFunc = &func_80B400C8;
}

void func_80B4009C(BgGoronOyu* _this) {
    BgGoronOyuActionFunc actionCallback;

    _this->unk17E = 0;
    _this->initialActorCutscene = _this->polyActor.actor.cutscene;

    actionCallback = &func_80B40100;
    _this->actionFunc = actionCallback;
    _this->flt164 = 20.0f;
}

void func_80B400C8(BgGoronOyu* _this, GlobalContext* globalCtx) {
    func_80B40308(_this, globalCtx);
    func_80B401F8(_this, globalCtx);
}

void func_80B40100(BgGoronOyu* _this, GlobalContext* globalCtx) {
    s16 actorCutscene;
    s16 actorCutscene_2;

    actorCutscene = _this->initialActorCutscene;

    if (ActorCutscene_GetCanPlayNext(actorCutscene) != 0) {
        actorCutscene_2 = _this->initialActorCutscene;
        ActorCutscene_StartAndSetUnkLinkFields(actorCutscene_2, &_this->polyActor.actor);

        _this->actionFunc = &func_80B40160;
        return;
    }

    ActorCutscene_SetIntentToPlay(_this->initialActorCutscene);
}

void func_80B40160(BgGoronOyu* _this, GlobalContext* globalCtx) {
    Math_StepToF(&_this->flt164, 0.0f, 0.2f);
    _this->polyActor.actor.world.pos.y = _this->polyActor.actor.home.pos.y - _this->flt164;
    func_80B40308(_this, globalCtx);

    if (_this->flt164 <= 0.0f) {
        ActorCutscene_Stop(_this->initialActorCutscene);
        _this->flt164 = 0.0f;
        func_80B40080(_this);
    }

    // SFX ID
    func_8019F1C0(&D_80B40780, (u16)0x205EU);
}

void func_80B401F8(BgGoronOyu* _this, GlobalContext* globalCtx) {
    Player* player;
    Vec3f playerWorldDistance;

    if (Actor_HasParent(&_this->polyActor.actor, globalCtx) != 0) {
        _this->polyActor.actor.parent = NULL;
        return;
    }

    player = PLAYER;

    Math_Vec3f_DistXYZAndStoreDiff(&_this->collisionHeaderMinVec3f, &player->actor.world.pos, &playerWorldDistance);

    if (playerWorldDistance.x >= 0.0f && playerWorldDistance.x <= _this->collisionHeaderMaxX &&
        playerWorldDistance.z >= 0.0f && playerWorldDistance.z <= _this->collisionHeaderMaxY &&
        fabsf(playerWorldDistance.y) < 100.0f && player->actor.yDistToWater > 12.0f) {
        func_800B8A1C(&_this->polyActor.actor, globalCtx, 0xBA, _this->polyActor.actor.xzDistToPlayer,
                      fabsf(_this->polyActor.actor.yDistToPlayer));
    }
}

void func_80B40308(BgGoronOyu* _this, GlobalContext* globalCtx) {
    CollisionHeader* colHeader;
    f32 sp28;

    if (func_800CA1AC(globalCtx, &globalCtx->colCtx, _this->polyActor.actor.world.pos.x,
                      _this->polyActor.actor.world.pos.z, &sp28, &colHeader) != 0) {
        Math_Vec3s_ToVec3f(&_this->collisionHeaderMinVec3f, &colHeader->minBounds);
        _this->collisionHeaderMaxX = colHeader->maxBounds.x;
        _this->collisionHeaderMaxY = colHeader->maxBounds.y;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40394.s")

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* _this = (BgGoronOyu*)thisx;
    void* unkPad;
    CollisionHeader* actorCollisionHeader = NULL;

    Actor_SetScale(&_this->polyActor.actor, 0.1f);
    BcCheck3_BgActorInit(&_this->polyActor, 1);
    BgCheck_RelocateMeshHeader(&D_6000988, &actorCollisionHeader);

    _this->polyActor.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &_this->polyActor, actorCollisionHeader);

    func_80B40308(_this, globalCtx);

    if (!!thisx->params) {
        thisx->world.pos.y = thisx->home.pos.y;
        func_80B40080(_this);
        return;
    }

    thisx->world.pos.y = thisx->home.pos.y - 20.0f;
    func_80B4009C(_this);
}

void BgGoronOyu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* _this = (BgGoronOyu*)thisx;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, _this->polyActor.bgId);
}

void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* _this = (BgGoronOyu*)thisx;
    _this->actionFunc(_this, globalCtx);
    func_80B40394(_this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Draw.s")
