/*
 * File: z_bg_goron_oyu.c
 * Overlay: ovl_Bg_Goron_Oyu
 * Description: Goron Hot Spring Water
 */

#include "z_bg_goron_oyu.h"

#define FLAGS 0x00000030

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B40100(BgGoronOyu* this, GlobalContext* globalCtx);
void func_80B400C8(BgGoronOyu* this, GlobalContext* globalCtx);
void func_80B401F8(BgGoronOyu* this, GlobalContext* globalCtx);
void func_80B40308(BgGoronOyu* this, GlobalContext* globalCtx);
void func_80B40394(BgGoronOyu* this, GlobalContext* globalCtx);
void func_80B40160(BgGoronOyu* this, GlobalContext* globalCtx);

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

extern CollisionHeader D_06000988;
extern Vec3f D_80B40780;

void func_80B40080(BgGoronOyu* this) {
    this->unk17E = 1;
    this->actionFunc = func_80B400C8;
}

void func_80B4009C(BgGoronOyu* this) {
    this->unk17E = 0;
    this->initialActorCutscene = this->polyActor.actor.cutscene;
    this->actionFunc = func_80B40100;
    this->flt164 = 20.0f;
}

void func_80B400C8(BgGoronOyu* this, GlobalContext* globalCtx) {
    func_80B40308(this, globalCtx);
    func_80B401F8(this, globalCtx);
}

void func_80B40100(BgGoronOyu* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->initialActorCutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->initialActorCutscene, &this->polyActor.actor);

        this->actionFunc = func_80B40160;
    } else {
        ActorCutscene_SetIntentToPlay(this->initialActorCutscene);
    }
}

void func_80B40160(BgGoronOyu* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->flt164, 0.0f, 0.2f);
    this->polyActor.actor.world.pos.y = this->polyActor.actor.home.pos.y - this->flt164;
    func_80B40308(this, globalCtx);

    if (this->flt164 <= 0.0f) {
        ActorCutscene_Stop(this->initialActorCutscene);
        this->flt164 = 0.0f;
        func_80B40080(this);
    }

    func_8019F1C0(&D_80B40780, NA_SE_EV_WATER_LEVEL_DOWN - SFX_FLAG);
}

void func_80B401F8(BgGoronOyu* this, GlobalContext* globalCtx) {
    Player* player;
    Vec3f playerWorldDistance;

    if (Actor_HasParent(&this->polyActor.actor, globalCtx)) {
        this->polyActor.actor.parent = NULL;
        return;
    }

    player = GET_PLAYER(globalCtx);
    Math_Vec3f_DistXYZAndStoreDiff(&this->waterBoxPos, &player->actor.world.pos, &playerWorldDistance);

    if (playerWorldDistance.x >= 0.0f && playerWorldDistance.x <= this->waterBoxXLength &&
        playerWorldDistance.z >= 0.0f && playerWorldDistance.z <= this->waterBoxZLength &&
        fabsf(playerWorldDistance.y) < 100.0f && player->actor.depthInWater > 12.0f) {
        func_800B8A1C(&this->polyActor.actor, globalCtx, 0xBA, this->polyActor.actor.xzDistToPlayer,
                      fabsf(this->polyActor.actor.playerHeightRel));
    }
}

void func_80B40308(BgGoronOyu* this, GlobalContext* globalCtx) {
    WaterBox* waterBox;
    f32 sp28;

    if (func_800CA1AC(globalCtx, &globalCtx->colCtx, this->polyActor.actor.world.pos.x,
                      this->polyActor.actor.world.pos.z, &sp28, &waterBox) != 0) {
        Math_Vec3s_ToVec3f(&this->waterBoxPos, &waterBox->xMin);
        this->waterBoxXLength = waterBox->xLength;
        this->waterBoxZLength = waterBox->zLength;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40394.s")

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* this = (BgGoronOyu*)thisx;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    Actor_SetScale(&this->polyActor.actor, 0.1f);
    DynaPolyActor_Init(&this->polyActor, 1);
    BgCheck_RelocateMeshHeader(&D_06000988, &colHeader);

    this->polyActor.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->polyActor, colHeader);

    func_80B40308(this, globalCtx);

    if (thisx->params != 0) {
        thisx->world.pos.y = thisx->home.pos.y;
        func_80B40080(this);
    } else {
        thisx->world.pos.y = thisx->home.pos.y - 20.0f;
        func_80B4009C(this);
    }
}

void BgGoronOyu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* this = (BgGoronOyu*)thisx;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->polyActor.bgId);
}

void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* this = (BgGoronOyu*)thisx;
    this->actionFunc(this, globalCtx);
    func_80B40394(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Draw.s")
