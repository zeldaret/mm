/*
 * File: z_bg_f40_block.c
 * Overlay: ovl_Bg_F40_Block
 * Description: Stone Tower Block
 */

#include "z_bg_f40_block.h"
#include "objects/object_f40_obj/object_f40_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgF40Block*)thisx)

void BgF40Block_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC41AC(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC4228(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC4344(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC4380(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC43CC(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC4448(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC44F4(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC4530(BgF40Block* this, GlobalContext* globalCtx);
void func_80BC457C(BgF40Block* this, GlobalContext* globalCtx);

const ActorInit Bg_F40_Block_InitVars = {
    ACTOR_BG_F40_BLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_F40_OBJ,
    sizeof(BgF40Block),
    (ActorFunc)BgF40Block_Init,
    (ActorFunc)BgF40Block_Destroy,
    (ActorFunc)BgF40Block_Update,
    (ActorFunc)BgF40Block_Draw,
};

static Vec3f D_80BC4620[] = {
    { 1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f, 0.0f },  { 0.0f, 0.0f, 1.0f },
    { -1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

s32 func_80BC3980(BgF40Block* this, GlobalContext* globalCtx) {
    Vec3s* points;

    this->unk_160 = 0;
    this->unk_164 = 0;

    if (BGF40BLOCK_GET_PATH(&this->dyna.actor) != 0x3F) {
        this->path = &globalCtx->setupPathList[BGF40BLOCK_GET_PATH(&this->dyna.actor)];
        if (this->path != NULL) {
            points = Lib_SegmentedToVirtual(this->path->points);

            this->dyna.actor.world.pos.x = points->x;
            this->dyna.actor.world.pos.y = points->y;
            this->dyna.actor.world.pos.z = points->z;
        }
    } else {
        this->path = NULL;
    }

    return false;
}

s32 func_80BC3A2C(BgF40Block* this, GlobalContext* globalCtx) {
    Vec3s* points;

    this->unk_160 = this->path->count - 1;
    this->unk_164 = this->path->count - 1;

    if (BGF40BLOCK_GET_PATH(&this->dyna.actor) != 0x3F) {
        this->path = &globalCtx->setupPathList[BGF40BLOCK_GET_PATH(&this->dyna.actor)];
        if (this->path != NULL) {
            points = Lib_SegmentedToVirtual(this->path->points);
            points += this->unk_164;

            this->dyna.actor.world.pos.x = points->x;
            this->dyna.actor.world.pos.y = points->y;
            this->dyna.actor.world.pos.z = points->z;
        }
    } else {
        this->path = NULL;
    }

    return false;
}

s32 func_80BC3B00(BgF40Block* this) {
    s32 pad;
    Path* path;
    Vec3s* points;
    Vec3f sp28;
    Vec3f sp24;

    if (this->path == NULL) {
        return true;
    }

    if (this->unk_160 == this->unk_164) {
        return true;
    }

    path = this->path;
    points = Lib_SegmentedToVirtual(path->points);
    points += this->unk_164;

    sp28.x = points->x;
    sp28.y = points->y;
    sp28.z = points->z;

    if (this->unk_168 == 6) {
        sp24.x = sp28.x - this->dyna.actor.world.pos.x;
        sp24.y = sp28.y - this->dyna.actor.world.pos.y;
        sp24.z = sp28.z - this->dyna.actor.world.pos.z;

        if (sp24.x > 10.0f) {
            this->unk_168 = 0;
        }

        if (sp24.y > 10.0f) {
            this->unk_168 = 1;
        }

        if (sp24.z > 10.0f) {
            this->unk_168 = 2;
        }

        if (sp24.x < -10.0f) {
            this->unk_168 = 3;
        }

        if (sp24.y < -10.0f) {
            this->unk_168 = 4;
        }

        if (sp24.z < -10.0f) {
            this->unk_168 = 5;
        }
    }

    if (Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &sp28, this->dyna.actor.speedXZ) <= 0.0f) {
        this->unk_168 = 6;
        this->unk_160 = this->unk_164;
        return true;
    }
    return false;
}

s32 func_80BC3CA4(BgF40Block* this) {
    if (this->dyna.actor.cutscene == -1) {
        return true;
    }

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        return true;
    }

    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    return false;
}

s32 func_80BC3D08(BgF40Block* this, GlobalContext* globalCtx, s32 arg2) {
    CollisionPoly* sp54;
    Vec3f sp48;
    Vec3f sp3C;
    Vec3f sp30;

    if (this->unk_168 == 6) {
        return false;
    }

    if (arg2 != 0) {
        sp48.x =
            (D_80BC4620[this->unk_168].x * ((800.0f * this->dyna.actor.scale.x) - (this->dyna.actor.speedXZ * 0.5f))) +
            this->dyna.actor.world.pos.x;
        sp48.y =
            (D_80BC4620[this->unk_168].y * ((800.0f * this->dyna.actor.scale.y) - (this->dyna.actor.speedXZ * 0.5f))) +
            this->dyna.actor.world.pos.y;
        sp48.z =
            (D_80BC4620[this->unk_168].z * ((800.0f * this->dyna.actor.scale.z) - (this->dyna.actor.speedXZ * 0.5f))) +
            this->dyna.actor.world.pos.z;

        sp3C.x = (D_80BC4620[this->unk_168].x * this->dyna.actor.speedXZ) + sp48.x;
        sp3C.y = (D_80BC4620[this->unk_168].y * this->dyna.actor.speedXZ) + sp48.y;
        sp3C.z = (D_80BC4620[this->unk_168].z * this->dyna.actor.speedXZ) + sp48.z;
    } else {
        sp3C.x = (D_80BC4620[this->unk_168].x * 800.0f * this->dyna.actor.scale.x) + this->dyna.actor.world.pos.x;
        sp3C.y = (D_80BC4620[this->unk_168].y * 800.0f * this->dyna.actor.scale.y) + this->dyna.actor.world.pos.y;
        sp3C.z = (D_80BC4620[this->unk_168].z * 800.0f * this->dyna.actor.scale.z) + this->dyna.actor.world.pos.z;

        sp48.x = sp3C.x - (D_80BC4620[this->unk_168].x * this->dyna.actor.speedXZ * 1.5f);
        sp48.y = sp3C.y - (D_80BC4620[this->unk_168].y * this->dyna.actor.speedXZ * 1.5f);
        sp48.z = sp3C.z - (D_80BC4620[this->unk_168].z * this->dyna.actor.speedXZ * 1.5f);
    }

    if (BgCheck_AnyLineTest1(&globalCtx->colCtx, &sp48, &sp3C, &sp30, &sp54, true)) {
        if (arg2 == 0) {
            this->dyna.actor.world.pos.x -= sp3C.x - sp30.x;
            this->dyna.actor.world.pos.y -= sp3C.y - sp30.y;
            this->dyna.actor.world.pos.z -= sp3C.z - sp30.z;
        }
        return true;
    }

    return false;
}

void func_80BC4038(BgF40Block* this) {
    s32 temp = this->unk_160;

    this->unk_160 = this->unk_164;
    this->unk_164 = temp;
    this->unk_168 = 6;
}

void BgF40Block_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Block* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_f40_obj_Colheader_004640);

    if (BGF40BLOCK_GET_PATH(&this->dyna.actor) != 0x3F) {
        this->path = &globalCtx->setupPathList[BGF40BLOCK_GET_PATH(&this->dyna.actor)];
    } else {
        this->path = NULL;
    }

    if (this->path != NULL) {
        if (Flags_GetSwitch(globalCtx, BGF40BLOCK_GET_SWITCHFLAG(&this->dyna.actor))) {
            this->actionFunc = func_80BC4530;
            this->dyna.actor.speedXZ = 40.0f;
            func_80BC3A2C(this, globalCtx);
        } else {
            this->actionFunc = func_80BC4380;
            this->dyna.actor.speedXZ = 20.0f;
            func_80BC3980(this, globalCtx);
        }
    } else {
        this->actionFunc = func_80BC457C;
    }
    this->unk_168 = 6;
}

void BgF40Block_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Block* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80BC41AC(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3D08(this, globalCtx, 1)) {
        if (!Flags_GetSwitch(globalCtx, BGF40BLOCK_GET_SWITCHFLAG(&this->dyna.actor))) {
            func_80BC4038(this);
            this->actionFunc = func_80BC44F4;
        }
    } else {
        this->actionFunc = func_80BC4344;
    }
}

void func_80BC4228(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3B00(this)) {
        this->dyna.actor.speedXZ = 20.0f;
        if (this->unk_160 < (this->path->count - 1)) {
            this->unk_164 = this->unk_160 + 1;
        } else {
            this->actionFunc = func_80BC4530;
            ActorCutscene_Stop(this->dyna.actor.cutscene);
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_STOP_C);
        }
    }

    if (func_80BC3D08(this, globalCtx, 0)) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->actionFunc = func_80BC41AC;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_STOP_F);
        return;
    }

    switch (this->unk_168) {
        case 0:
        case 3:
            func_800B9010(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_MOVE_X - SFX_FLAG);
            break;

        case 1:
        case 4:
            func_800B9010(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_MOVE_Y - SFX_FLAG);
            break;

        case 2:
        case 5:
            func_800B9010(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_MOVE_Z - SFX_FLAG);
            break;
    }
}

void func_80BC4344(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3CA4(this)) {
        this->actionFunc = func_80BC4228;
    }
}

void func_80BC4380(BgF40Block* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, BGF40BLOCK_GET_SWITCHFLAG(&this->dyna.actor))) {
        this->actionFunc = func_80BC4344;
    }
}

void func_80BC43CC(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3D08(this, globalCtx, 1)) {
        if (Flags_GetSwitch(globalCtx, BGF40BLOCK_GET_SWITCHFLAG(&this->dyna.actor))) {
            func_80BC4038(this);
            this->actionFunc = func_80BC4344;
        }
    } else {
        this->actionFunc = func_80BC44F4;
    }
}

void func_80BC4448(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3B00(this)) {
        this->dyna.actor.speedXZ = 40.0f;
        if (this->unk_160 > 0) {
            this->unk_164 = this->unk_160 - 1;
        } else {
            this->actionFunc = func_80BC4380;
            ActorCutscene_Stop(this->dyna.actor.cutscene);
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_STOP_C);
        }
    }

    if (func_80BC3D08(this, globalCtx, 0)) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->actionFunc = func_80BC43CC;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_STOP_F);
    }
}

void func_80BC44F4(BgF40Block* this, GlobalContext* globalCtx) {
    if (func_80BC3CA4(this)) {
        this->actionFunc = func_80BC4448;
    }
}

void func_80BC4530(BgF40Block* this, GlobalContext* globalCtx) {
    if (!Flags_GetSwitch(globalCtx, BGF40BLOCK_GET_SWITCHFLAG(&this->dyna.actor))) {
        this->actionFunc = func_80BC44F4;
    }
}

void func_80BC457C(BgF40Block* this, GlobalContext* globalCtx) {
}

void BgF40Block_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Block* this = THIS;

    this->actionFunc(this, globalCtx);

    Math_Vec3f_Copy(&this->dyna.actor.focus.pos, &this->dyna.actor.world.pos);
}

void BgF40Block_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_f40_obj_DL_0043D0);
}
