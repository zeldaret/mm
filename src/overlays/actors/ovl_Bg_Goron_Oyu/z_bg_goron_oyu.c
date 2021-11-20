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

const ActorInit Bg_Goron_Oyu_InitVars = {
    ACTOR_BG_GORON_OYU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OYU,
    sizeof(BgGoronOyu),
    (ActorFunc)BgGoronOyu_Init,
    (ActorFunc)BgGoronOyu_Destroy,
    (ActorFunc)BgGoronOyu_Update,
    (ActorFunc)BgGoronOyu_Draw,
};

extern Gfx D_06000080;
extern Gfx D_06000158;
extern AnimatedMaterial D_06000968;
extern CollisionHeader D_06000988;

void func_80B40080(BgGoronOyu* this) {
    this->unk_17E = 1;
    this->actionFunc = func_80B400C8;
}

void func_80B4009C(BgGoronOyu* this) {
    this->unk_17E = 0;
    this->initialActorCutscene = this->dyna.actor.cutscene;
    this->actionFunc = func_80B40100;
    this->unk_164 = 20.0f;
}

void func_80B400C8(BgGoronOyu* this, GlobalContext* globalCtx) {
    func_80B40308(this, globalCtx);
    func_80B401F8(this, globalCtx);
}

void func_80B40100(BgGoronOyu* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->initialActorCutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->initialActorCutscene, &this->dyna.actor);
        this->actionFunc = func_80B40160;
    } else {
        ActorCutscene_SetIntentToPlay(this->initialActorCutscene);
    }
}

void func_80B40160(BgGoronOyu* this, GlobalContext* globalCtx) {
    static Vec3f D_80B40780 = { 0, 0, 0 };
    Math_StepToF(&this->unk_164, 0.0f, 0.2f);
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - this->unk_164;
    func_80B40308(this, globalCtx);

    if (this->unk_164 <= 0.0f) {
        ActorCutscene_Stop(this->initialActorCutscene);
        this->unk_164 = 0.0f;
        func_80B40080(this);
    }

    func_8019F1C0(&D_80B40780, NA_SE_EV_WATER_LEVEL_DOWN - SFX_FLAG);
}

void func_80B401F8(BgGoronOyu* this, GlobalContext* globalCtx) {
    Player* player;
    Vec3f dist;

    if (Actor_HasParent(&this->dyna.actor, globalCtx)) {
        this->dyna.actor.parent = NULL;
        return;
    }

    player = GET_PLAYER(globalCtx);
    Math_Vec3f_DistXYZAndStoreDiff(&this->waterBoxPos, &player->actor.world.pos, &dist);

    if (dist.x >= 0.0f && dist.x <= this->waterBoxXLength && dist.z >= 0.0f && dist.z <= this->waterBoxZLength &&
        fabsf(dist.y) < 100.0f && player->actor.depthInWater > 12.0f) {
        func_800B8A1C(&this->dyna.actor, globalCtx, 0xBA, this->dyna.actor.xzDistToPlayer,
                      fabsf(this->dyna.actor.playerHeightRel));
    }
}

void func_80B40308(BgGoronOyu* this, GlobalContext* globalCtx) {
    WaterBox* waterBox;
    f32 sp28;

    if (func_800CA1AC(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.z, &sp28,
                      &waterBox) != 0) {
        Math_Vec3s_ToVec3f(&this->waterBoxPos, &waterBox->xMin);
        this->waterBoxXLength = waterBox->xLength;
        this->waterBoxZLength = waterBox->zLength;
    }
}

void func_80B40394(BgGoronOyu* this, GlobalContext* globalCtx) {
    s16 sp6E;
    Vec3f sp60;
    Vec3f sp54;
    CollisionPoly* poly;
    s32 pad;

    if ((globalCtx->state.frames & 3) == 0) {
        Vec3f sp40;
        Vec3f sp34;

        sp60.x = this->dyna.actor.world.pos.x;
        sp60.y = this->dyna.actor.world.pos.y + 100.0f;
        sp60.z = this->dyna.actor.world.pos.z;
        sp40.x = 0.0f;
        sp40.y = 2.5f;
        sp40.z = 0.0f;
        sp6E = -200 - (s32)(Rand_ZeroOne() * 50.0f);

        if (func_800C4000(globalCtx, &globalCtx->colCtx, &poly, &sp60) < this->waterBoxPos.y) {
            sp60.y = this->waterBoxPos.y + 10.0f;
            EffectSsIceSmoke_Spawn(globalCtx, &sp60, &sp40, &D_801D15B0, sp6E);
        }
        sp54.x = (Rand_ZeroOne() * this->waterBoxXLength) + this->waterBoxPos.x;
        sp54.y = this->waterBoxPos.y + 100.0f;
        sp54.z = (Rand_ZeroOne() * this->waterBoxZLength) + this->waterBoxPos.z;
        sp34.x = 0.0f;
        sp34.y = 0.5f;
        sp34.z = 0.0f;
        sp6E = -200 - (s32)(Rand_ZeroOne() * 50.0f);

        if (func_800C4000(globalCtx, &globalCtx->colCtx, &poly, &sp54) < this->waterBoxPos.y) {
            sp54.y = this->waterBoxPos.y + 10.0f;
            EffectSsIceSmoke_Spawn(globalCtx, &sp54, &sp34, &D_801D15B0, sp6E);
        }
    }
}

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* this = (BgGoronOyu*)thisx;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    Actor_SetScale(&this->dyna.actor, 0.1f);
    DynaPolyActor_Init(&this->dyna, 1);
    BgCheck_RelocateMeshHeader(&D_06000988, &colHeader);

    this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);

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

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgGoronOyu* this = (BgGoronOyu*)thisx;

    this->actionFunc(this, globalCtx);
    func_80B40394(this, globalCtx);
}

void BgGoronOyu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06000968));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, &D_06000158);
    gSPDisplayList(POLY_XLU_DISP++, &D_06000080);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
