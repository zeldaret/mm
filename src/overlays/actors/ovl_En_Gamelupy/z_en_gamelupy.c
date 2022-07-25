/*
 * File: z_en_gamelupy.c
 * Overlay: ovl_En_Gamelupy
 * Description: Deku Scrub Playground Rupees
 */

#include "z_en_gamelupy.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnGamelupy*)thisx)

void EnGamelupy_Init(Actor* thisx, PlayState* play);
void EnGamelupy_Destroy(Actor* thisx, PlayState* play);
void EnGamelupy_Update(Actor* thisx, PlayState* play);
void EnGamelupy_Draw(Actor* thisx, PlayState* play);

void func_80AF6958(EnGamelupy* this, PlayState* play);
void func_80AF69A8(EnGamelupy* this, PlayState* play);
void func_80AF6A78(EnGamelupy* this, PlayState* play);
void func_80AF6944(EnGamelupy* this);
void func_80AF6994(EnGamelupy* this);
void func_80AF6A38(EnGamelupy* this);

const ActorInit En_Gamelupy_InitVars = {
    ACTOR_EN_GAMELUPY,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGamelupy),
    (ActorFunc)EnGamelupy_Init,
    (ActorFunc)EnGamelupy_Destroy,
    (ActorFunc)EnGamelupy_Update,
    (ActorFunc)EnGamelupy_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 30, 0, { 0, 0, 0 } },
};

static TexturePtr sRupeeTex[] = {
    gameplay_keep_Tex_061FC0, gameplay_keep_Tex_061FE0, gameplay_keep_Tex_062000,
    gameplay_keep_Tex_062040, gameplay_keep_Tex_062020,
};

static Color_RGBA8 sPrimColor = { 255, 255, 255, 255 };

static Color_RGBA8 sEnvColor = { 100, 200, 0, 255 };

void EnGamelupy_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGamelupy* this = THIS;

    Actor_SetScale(&this->actor, 0.03f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);
    this->actor.shape.yOffset = 700.0f;
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.gravity = -0.5f;
    this->actor.shape.rot.y = Rand_Next();
    this->unk_19C = 0;
    this->unk_19E = 0;
    this->unk_1A0 = 0x7D0;
    if (this->actor.params == 1) {
        this->rupeeIndex = 1;
    } else {
        this->rupeeIndex = 0;
    }
    func_80AF6944(this);
}

void EnGamelupy_Destroy(Actor* thisx, PlayState* play) {
    EnGamelupy* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80AF6854(EnGamelupy* this, PlayState* play) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp30;

    sp4C = this->actor.world.pos;
    sp30.x = Math_SinS(this->unk_19E) * 3.0f;
    sp30.y = 5.5f;
    sp30.z = Math_CosS(this->unk_19E) * 3.0f;
    sp40.x = -0.05f * sp30.x;
    sp40.y = -0.4f;
    sp40.z = -0.05f * sp30.z;
    EffectSsKirakira_SpawnDispersed(play, &sp4C, &sp30, &sp40, &sPrimColor, &sEnvColor, 3000, 40);
    this->unk_19E += this->unk_1A0;
}

void func_80AF6944(EnGamelupy* this) {
    this->actionFunc = func_80AF6958;
}

void func_80AF6958(EnGamelupy* this, PlayState* play) {
    s16* unk_198 = func_800B6680(play, ACTOR_EN_GAMELUPY);

    if (unk_198 != NULL) {
        this->unk_198 = unk_198;
        func_80AF6994(this);
    }
}

void func_80AF6994(EnGamelupy* this) {
    this->actionFunc = func_80AF69A8;
}

void func_80AF69A8(EnGamelupy* this, PlayState* play) {
    if (this->collider.base.ocFlags1 & OC1_HIT) {
        *this->unk_198 += 0x32;
        if (this->rupeeIndex == 1) {
            Rupees_ChangeBy(5);
        } else {
            Rupees_ChangeBy(1);
        }
        func_80AF6A38(this);
    }
    this->actor.shape.rot.y += 0x1F4;
}

void func_80AF6A38(EnGamelupy* this) {
    this->unk_19C = 0;
    this->actor.gravity = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_GET_RUPY);
    this->actionFunc = func_80AF6A78;
}

void func_80AF6A78(EnGamelupy* this, PlayState* play) {
    f32 scale;
    Player* player = GET_PLAYER(play);

    if (this->unk_19C > 30) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->unk_19C++;
        this->actor.world.pos = player->actor.world.pos;
        this->actor.world.pos.y += 40.0f;
        scale = (30.0f - this->unk_19C) * 0.001f;
        Actor_SetScale(&this->actor, scale);
        func_80AF6854(this, play);
    }
    this->actor.shape.rot.y += 0x3E8;
}

void func_80AF6B40(EnGamelupy* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnGamelupy_Update(Actor* thisx, PlayState* play) {
    EnGamelupy* this = THIS;

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 32.0f, 30.0f, 0.0f, 0xC);
    func_80AF6B40(this, play);
}

void EnGamelupy_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGamelupy* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_800B8050(&this->actor, play, 0);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sRupeeTex[this->rupeeIndex]));
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0622C0);

    CLOSE_DISPS(play->state.gfxCtx);
}
