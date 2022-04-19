/*
 * File: z_obj_ice_poly.c
 * Overlay: ovl_Obj_Ice_Poly
 * Description: Large Block of Meltable Ice
 */

#include "z_obj_ice_poly.h"
#include "overlays/actors/ovl_Obj_Aqua/z_obj_aqua.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjIcePoly*)thisx)

void ObjIcePoly_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80931828(ObjIcePoly* this, GlobalContext* globalCtx);
void func_80931A38(ObjIcePoly* this, GlobalContext* globalCtx);
void func_80931E58(ObjIcePoly* this, GlobalContext* globalCtx);
void func_80931EEC(ObjIcePoly* this, GlobalContext* globalCtx);

const ActorInit Obj_Ice_Poly_InitVars = {
    ACTOR_OBJ_ICE_POLY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjIcePoly),
    (ActorFunc)ObjIcePoly_Init,
    (ActorFunc)ObjIcePoly_Destroy,
    (ActorFunc)ObjIcePoly_Update,
    (ActorFunc)ObjIcePoly_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x02, 0x00 },
        { 0xF7CFF7FF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 50, 105, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK5,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0x00000800, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 65, 105, 0, { 0, 0, 0 } },
};

static Color_RGBA8 D_80932378 = { 250, 250, 250, 255 };
static Color_RGBA8 D_8093237C = { 180, 180, 180, 255 };

void ObjIcePoly_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjIcePoly* this = THIS;
    s32 i;

    this->unk_149 = OBJICEPOLY_GET_FF00(thisx);
    thisx->params &= 0xFF;
    thisx->uncullZoneForward = 5600.0f;

    Actor_SetScale(thisx, thisx->params * 0.01f);

    for (i = 0; i < ARRAY_COUNT(this->colliders1); i++) {
        Collider_InitAndSetCylinder(globalCtx, &this->colliders1[i], thisx, &sCylinderInit1);
        Collider_InitAndSetCylinder(globalCtx, &this->colliders2[i], thisx, &sCylinderInit2);
        Collider_UpdateCylinder(thisx, &this->colliders1[i]);
        Collider_UpdateCylinder(thisx, &this->colliders2[i]);
    }

    this->colliders1[0].dim.radius = thisx->scale.x * 48.0f;
    this->colliders1[0].dim.height = thisx->scale.y * 58.0f;
    this->colliders2[0].dim.height = this->colliders1[0].dim.height;
    this->colliders2[0].dim.radius = this->colliders1[0].dim.radius + 17;

    this->colliders1[1].dim.radius = thisx->scale.x * 23.0f;
    this->colliders1[1].dim.height = thisx->scale.y * 50.0f;
    this->colliders2[1].dim.radius = this->colliders1[1].dim.radius;
    this->colliders2[1].dim.height = this->colliders1[1].dim.height;

    this->colliders1[1].dim.yShift = this->colliders1[0].dim.height;
    this->colliders2[1].dim.yShift = this->colliders1[1].dim.yShift;

    thisx->colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_148 = 255;

    Actor_SetFocus(thisx, thisx->scale.y * 30.0f);

    thisx->shape.rot.x = 0x500;
    thisx->shape.rot.z = -0x500;

    if (((this->unk_149 != OBJICEPOLY_FF_FF) && Flags_GetSwitch(globalCtx, this->unk_149)) ||
        ((globalCtx->sceneNum == SCENE_KAJIYA) && (gSaveContext.save.weekEventReg[33] & 0x80))) {
        Actor_MarkForDeath(thisx);
        return;
    }

    this->actionFunc = func_80931A38;
}

void ObjIcePoly_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjIcePoly* this = THIS;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->colliders1); i++) {
        Collider_DestroyCylinder(globalCtx, &this->colliders1[i]);
        Collider_DestroyCylinder(globalCtx, &this->colliders2[i]);
    }
}

void func_80931828(ObjIcePoly* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80932380 = { 170, 255, 255, 255 };
    static Color_RGBA8 D_80932384 = { 0, 50, 100, 255 };
    static Vec3f D_80932388 = { 0.0f, -1.0f, 0.0f };
    f32 temp;
    Vec3f spA0;
    Vec3f sp94;
    f32 sp90;
    s32 i;
    CollisionPoly* sp88;

    spA0.x = this->actor.world.pos.x;
    spA0.y = (this->colliders1[0].dim.height * 2) + this->actor.world.pos.y;
    spA0.z = this->actor.world.pos.z;

    sp90 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp88, &spA0);
    if (sp90 < this->actor.world.pos.y) {
        sp90 = this->actor.world.pos.y;
    }
    temp = spA0.y - sp90;

    for (i = 0; i < 30; i++) {
        sp94.x = randPlusMinusPoint5Scaled(12.0f);
        sp94.y = Rand_ZeroFloat(15.0f);
        sp94.z = randPlusMinusPoint5Scaled(12.0f);

        spA0.x = (this->colliders1[0].dim.radius * (sp94.x * (1.0f / 12))) + this->actor.world.pos.x;
        spA0.z = (this->colliders1[0].dim.radius * (sp94.z * (1.0f / 12))) + this->actor.world.pos.z;
        spA0.y = Rand_ZeroFloat(temp) + sp90;
        EffectSsEnIce_Spawn(globalCtx, &spA0, (Rand_ZeroFloat(0.4f) + 0.3f) * this->actor.scale.x, &sp94, &D_80932388,
                            &D_80932380, &D_80932384, 40);
    }
}

void func_80931A38(ObjIcePoly* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp6C;
    s32 i;
    s32 pad2;
    s32 phi_v0;
    s32 pad3;
    f32 sp58;

    if (!(player->stateFlags2 & 0x4000) && (this->unk_14A != 0)) {
        this->unk_14A--;
    }

    if ((this->colliders1[0].base.atFlags & AT_HIT) || (this->colliders1[1].base.atFlags & AT_HIT)) {
        this->unk_14A = 40;
        this->colliders1[0].base.atFlags &= ~AT_HIT;
        this->colliders1[1].base.atFlags &= ~AT_HIT;
    }

    if (((this->colliders2[0].base.acFlags & AC_HIT) &&
         ((this->colliders2[0].base.ac == NULL) ||
          ((this->colliders2[0].base.ac->id != ACTOR_OBJ_AQUA) &&
           (this->colliders2[0].info.acHitInfo->toucher.dmgFlags == 0x800)) ||
          ((this->colliders2[0].base.ac->id == ACTOR_OBJ_AQUA) &&
           (this->colliders2[0].base.ac->params == OBJAQUA_1)))) ||
        ((this->colliders2[1].base.acFlags & AC_HIT) &&
         ((this->colliders2[1].base.ac == NULL) ||
          ((this->colliders2[1].base.ac->id != ACTOR_OBJ_AQUA) &&
           (this->colliders2[1].info.acHitInfo->toucher.dmgFlags == 0x800)) ||
          ((this->colliders2[1].base.ac->id == ACTOR_OBJ_AQUA) &&
           (this->colliders2[1].base.ac->params == OBJAQUA_1))))) {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->unk_14A = 0;
        this->actionFunc = func_80931E58;
        this->actor.focus.rot.y = this->actor.yawTowardsPlayer;

        if (globalCtx->sceneNum == SCENE_00KEIKOKU) {
            Actor* actor = NULL;

            do {
                actor = SubS_FindActor(globalCtx, actor, ACTORCAT_ITEMACTION, ACTOR_OBJ_ICE_POLY);
                if (actor != NULL) {
                    if ((&this->actor != actor) && (&this->actor != actor)) {
                        ((ObjIcePoly*)actor)->unk_14A = 0;
                        ((ObjIcePoly*)actor)->actionFunc = func_80931E58;
                    }
                    actor = actor->next;
                }
            } while (actor != NULL);
        }
    } else if ((this->unk_149 != OBJICEPOLY_FF_FF) && Flags_GetSwitch(globalCtx, this->unk_149)) {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->unk_14A = 1;
        this->actionFunc = func_80931E58;
    } else {
        if ((this->actor.parent != NULL) && (this->actor.parent->update != NULL)) {
            this->actor.parent->freezeTimer = 40;
        } else {
            this->actor.parent = NULL;
        }

        if (this->unk_14A == 0) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliders1[0].base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliders1[1].base);
        }

        for (i = 0; i < ARRAY_COUNT(this->colliders1); i++) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliders1[i].base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliders1[i].base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliders2[i].base);
        }
    }

    if (Rand_ZeroOne() < 0.05f) {
        sp58 = Rand_ZeroOne();
        if (Rand_ZeroOne() < 0.5f) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        sp6C.x = (phi_v0 * (15.0f + (sp58 * 15.0f)) * this->actor.scale.x) + this->actor.world.pos.x;
        sp6C.y = (((Rand_ZeroOne() * 90.0f) + 10.0f) * this->actor.scale.y) + this->actor.world.pos.y;

        sp58 = Rand_ZeroOne();
        if (Rand_ZeroOne() < 0.5f) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        sp6C.z = (phi_v0 * (15.0f + (sp58 * 15.0f)) * this->actor.scale.z) + this->actor.world.pos.z;

        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp6C, &gZeroVec3f, &gZeroVec3f, &D_80932378, &D_8093237C, 2000, 5);
    }
}

void func_80931E58(ObjIcePoly* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        if (this->unk_14A == 1) {
            func_80931828(this, globalCtx);
            Actor_MarkForDeath(&this->actor);
        } else {
            this->unk_14A = 40;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT);
            this->actionFunc = func_80931EEC;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80931EEC(ObjIcePoly* this, GlobalContext* globalCtx) {
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    f32 temp_f20;
    s32 i;
    s32 phi_v0;

    spAC.x = 0.0f;
    spAC.y = this->actor.scale.y;
    spAC.z = 0.0f;

    spA0.x = 0.0f;
    spA0.y = this->actor.scale.y;
    spA0.z = 0.0f;

    for (i = 0; i < 2; i++) {
        temp_f20 = Rand_ZeroOne();
        if (Rand_ZeroOne() < 0.5f) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        sp94.x = (phi_v0 * (20.0f + (20.0f * temp_f20)) * this->actor.scale.x) + this->actor.world.pos.x;
        sp94.y = (Rand_ZeroOne() * this->actor.scale.y * 50.0f) + this->actor.world.pos.y;

        temp_f20 = Rand_ZeroOne();
        if (Rand_ZeroOne() < 0.5f) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        sp94.z = (phi_v0 * (20.0f + (20.0f * temp_f20)) * this->actor.scale.x) + this->actor.world.pos.z;

        func_800B0DE0(globalCtx, &sp94, &spA0, &spAC, &D_80932378, &D_8093237C,
                      ((Rand_ZeroOne() * 100.0f) + 350.0f) * this->actor.scale.x, this->actor.scale.x * 20.0f);
    }

    if (this->unk_14A != 0) {
        this->unk_14A--;
    }

    this->actor.scale.y = this->actor.params * 0.01f * (0.5f + (this->unk_14A * 0.0125f));
    this->unk_148 -= 6;

    if (this->unk_14A == 0) {
        ActorCutscene_Stop(this->actor.cutscene);
        if (this->unk_149 != OBJICEPOLY_FF_FF) {
            Flags_SetSwitch(globalCtx, this->unk_149);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjIcePoly_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjIcePoly* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjIcePoly_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjIcePoly* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    func_800B8118(&this->actor, globalCtx, 0);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, globalCtx->gameplayFrames % 256, 0x20, 0x10, 1, 0,
                                (globalCtx->gameplayFrames * 2) % 256, 0x40, 0x20));
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, this->unk_148);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_050D10);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
