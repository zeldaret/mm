/*
 * File: z_en_dy_extra.c
 * Overlay: ovl_En_Dy_Extra
 * Description: Great Fairy beam
 */

#include "z_en_dy_extra.h"
#include "objects/object_dy_obj/object_dy_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnDyExtra*)thisx)

void EnDyExtra_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A61334(EnDyExtra* this, GlobalContext* globalCtx);
void func_80A613C8(EnDyExtra* this, GlobalContext* globalCtx);

const ActorInit En_Dy_Extra_InitVars = {
    ACTOR_EN_DY_EXTRA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DY_OBJ,
    sizeof(EnDyExtra),
    (ActorFunc)EnDyExtra_Init,
    (ActorFunc)EnDyExtra_Destroy,
    (ActorFunc)EnDyExtra_Update,
    (ActorFunc)EnDyExtra_Draw,
};

void EnDyExtra_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnDyExtra_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDyExtra* this = THIS;

    this->type = this->actor.params;
    this->actor.scale.x = 0.025f;
    this->actor.scale.y = 0.039f;
    this->actor.scale.z = 0.025f;
    this->unk160 = this->actor.world.pos;
    this->actor.gravity = -0.2f;
    this->unk150 = 1.0f;
    this->unk14C = 0x3C;
    this->actionFunc = func_80A61334;
}

void func_80A61334(EnDyExtra* this, GlobalContext* globalCtx) {
    Math_ApproachF(&this->actor.gravity, 0.0f, 0.1f, 0.005f);

    if (this->actor.world.pos.y < -85.0f) {
        this->actor.velocity.y = 0.0f;
    }

    if (this->unk14C == 0 && this->unk14A != 0) {
        this->unk14C = 0x32;
        this->actionFunc = func_80A613C8;
    }
}

void func_80A613C8(EnDyExtra* this, GlobalContext* globalCtx) {
    Math_ApproachF(&this->actor.gravity, 0.0f, 0.1f, 0.005f);

    if (this->unk14C == 0 || this->unk150 < 0.02f) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk150 -= 0.02f;

    if (this->actor.world.pos.y < -85.0f) {
        this->actor.velocity.y = 0.0f;
    }
}

void EnDyExtra_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDyExtra* this = THIS;

    DECR(this->unk14C);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_SPIRAL_HEAL_BEAM - SFX_FLAG);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
}

void EnDyExtra_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80A61740[] = {
        { 255, 255, 170, 255 }, { 255, 170, 255, 255 }, { 255, 255, 170, 255 },
        { 170, 255, 255, 255 }, { 255, 255, 170, 255 },
    };
    static Color_RGBA8 D_80A61754[] = {
        { 255, 100, 0, 255 }, { 255, 0, 100, 255 }, { 100, 255, 0, 255 }, { 0, 100, 255, 255 }, { 255, 230, 0, 255 }
    };
    static u8 D_80A61768[] = { 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x02, 0x01,
                               0x00, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00 };
    EnDyExtra* this = THIS;
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Vtx* vertices = Lib_SegmentedToVirtual(object_dy_obj_Vtx_00DD40);
    s32 i;
    u8 unk[3];

    unk[0] = 0.0f;
    unk[1] = (s8)(this->unk150 * 240.0f);
    unk[2] = (s8)(this->unk150 * 255.0f);

    for (i = 0; i < 27; i++) {
        if (D_80A61768[i]) {
            vertices[i].v.cn[3] = unk[D_80A61768[i]];
        }
    }

    OPEN_DISPS(gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 2, 0, 0x20, 0x40, 1,
                                globalCtx->state.frames, globalCtx->state.frames * -8, 0x10, 0x10));
    gDPPipeSync(POLY_XLU_DISP++);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, D_80A61740[this->type].r, D_80A61740[this->type].g,
                    D_80A61740[this->type].b, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, D_80A61754[this->type].r, D_80A61754[this->type].g, D_80A61754[this->type].b, 128);
    gSPDisplayList(POLY_XLU_DISP++, object_dy_obj_DL_00DEF0);

    CLOSE_DISPS(gfxCtx);
}
