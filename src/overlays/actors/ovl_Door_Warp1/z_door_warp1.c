/*
 * File: z_door_warp1.c
 * Overlay: ovl_Door_Warp1
 * Description: Blue Warp
 */

#include "z_door_warp1.h"
#include "objects/object_warp1/object_warp1.h"

#define FLAGS 0x00000000

#define THIS ((DoorWarp1*)thisx)

void DoorWarp1_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Draw(Actor* thisx, GlobalContext* globalCtx);

void DoorWarp1_SetupAction(DoorWarp1* this, DoorWarp1ActionFunc actionFunc);
void func_808B8924(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B8A7C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B8C48(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B8E78(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9094(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B90CC(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B921C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B93A0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B94A4(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9524(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B958C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B96A0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B96B0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B977C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9840(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B98A8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9B30(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9BE8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9CE8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9E94(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9ED8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9F10(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9FD0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BA10C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BA550(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BAAF4(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BABF4(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BB8D4(DoorWarp1* this, GlobalContext* globalCtx, s32 arg2);

static s16 D_808BC000;
static f32 D_808BC004;

const ActorInit Door_Warp1_InitVars = {
    ACTOR_DOOR_WARP1,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_WARP1,
    sizeof(DoorWarp1),
    (ActorFunc)DoorWarp1_Init,
    (ActorFunc)DoorWarp1_Destroy,
    (ActorFunc)DoorWarp1_Update,
    (ActorFunc)DoorWarp1_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};

void DoorWarp1_SetupAction(DoorWarp1* this, DoorWarp1ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

s32 func_808B849C(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 ret = 0;

    if ((globalCtx->sceneNum == SCENE_MITURIN_BS) && !CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA)) {
        ret = 1;
    } else if ((globalCtx->sceneNum == SCENE_HAKUGIN_BS) && !CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT)) {
        ret = 2;
    } else if ((globalCtx->sceneNum == SCENE_SEA_BS) && !CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG)) {
        ret = 3;
    } else if ((globalCtx->sceneNum == SCENE_INISIE_BS) && !CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
        ret = 4;
    }
    return ret;
}

void func_808B8568(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 pad[2];

    Lights_PointNoGlowSetInfo(&this->unk_1E0, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 0, 0, 0, 0);
    this->unk_1DC = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->unk_1E0);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 0, 0, 0, 0);
    this->unk_1F0 = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->unk_1F4);
}

s32 func_808B866C(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 ret = false;

    if ((fabsf(this->dyna.actor.xzDistToPlayer) < 60.0f) &&
        (((player->actor.world.pos.y - 20.0f) < this->dyna.actor.world.pos.y) &&
         (this->dyna.actor.world.pos.y < (player->actor.world.pos.y + 20.0f)))) {
        ret = true;
    }
    return ret;
}

void DoorWarp1_Init(Actor* thisx, GlobalContext* globalCtx) {
    DoorWarp1* this = THIS;

    this->unk_1CC = 0;
    this->unk_202 = 0;
    this->unk_203 = 0;
    this->unk_1A0 = NULL;
    this->unk_1C0 = 0.0f;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 0.0f);

    this->unk_1D3 = 0;
    this->unk_1D4 = 0;
    this->unk_203 = 0;
    this->unk_204 = 1.0f;

    switch (DOORWARP1_GET_FF(&this->dyna.actor)) {
        case ENDOORWARP1_FF_0:
        case ENDOORWARP1_FF_1:
        case ENDOORWARP1_FF_2:
        case ENDOORWARP1_FF_3:
        case ENDOORWARP1_FF_4:
        case ENDOORWARP1_FF_5:
            func_808B8568(this, globalCtx);
            break;
    }

    switch (DOORWARP1_GET_FF(&this->dyna.actor)) {
        case ENDOORWARP1_FF_0:
            func_808B8924(this, globalCtx);
            break;

        case ENDOORWARP1_FF_1:
            func_808B8A7C(this, globalCtx);
            break;

        case ENDOORWARP1_FF_2:
        case ENDOORWARP1_FF_3:
        case ENDOORWARP1_FF_4:
        case ENDOORWARP1_FF_5:
            this->unk_1D3 = 1;
            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_warp1_Colheader_008BD4);
            func_808B8C48(this, globalCtx);
            break;

        case ENDOORWARP1_FF_6:
            func_808B8E78(this, globalCtx);
            break;
    }

    if ((globalCtx->sceneNum == SCENE_MITURIN_BS) || (globalCtx->sceneNum == SCENE_HAKUGIN_BS) ||
        (globalCtx->sceneNum == SCENE_INISIE_BS) || (globalCtx->sceneNum == SCENE_SEA_BS)) {
        func_800FE484();
        globalCtx->interfaceCtx.restrictions.unk_312 = 1;
        globalCtx->interfaceCtx.restrictions.songOfSoaring = 1;
    }
}

void DoorWarp1_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DoorWarp1* this = THIS;
    s16 i;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->unk_1DC);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->unk_1F0);

    for (i = 0; i < ARRAY_COUNT(globalCtx->envCtx.lightSettings.diffuseColor1); i++) {
        globalCtx->envCtx.lightSettings.diffuseColor1[i] = 0;
        globalCtx->envCtx.lightSettings.fogColor[i] = globalCtx->envCtx.lightSettings.diffuseColor1[i];
        globalCtx->envCtx.lightSettings.ambientColor[i] = globalCtx->envCtx.lightSettings.diffuseColor1[i];
    }

    if (this->unk_1D3 != 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_808B8924(DoorWarp1* this, GlobalContext* globalCtx) {
    this->unk_1C4 = 0;
    this->unk_1C6 = -140;
    this->unk_1C8 = -80;
    this->unk_1BC = 1.0f;
    this->unk_1B0 = 0.0f;
    this->unk_1B4 = 0.0f;
    this->unk_1B8 = 0.0f;
    this->unk_1A4 = 0.3f;
    this->unk_1A8 = 0.3f;
    this->unk_1AC = 0.0f;
    this->dyna.actor.shape.yOffset = 1.0f;
    this->unk_1D0 = 0;
    D_808BC000 = 100;
    Lights_PointNoGlowSetInfo(&this->unk_1E0, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    DoorWarp1_SetupAction(this, func_808B96B0);
}

void func_808B8A7C(DoorWarp1* this, GlobalContext* globalCtx) {
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_warp1_Skel_002CA8, &object_warp1_Anim_001374, NULL, NULL, 0);
    Animation_ChangeImpl(&this->skelAnime, &object_warp1_Anim_001374, 1.0f, 1.0f, 1.0f, 2, 40.0f, 1);
    this->unk_1C4 = 0;
    this->unk_1C6 = -140;
    this->unk_1C8 = -80;
    this->unk_1D0 = 0;
    this->unk_1BC = 1.0f;
    this->unk_1A4 = 0.3f;
    this->unk_1A8 = 0.3f;
    this->unk_1B0 = 0.0f;
    this->unk_1B4 = 0.0f;
    this->unk_1B8 = 0.0f;
    this->unk_1AC = 0.0f;
    this->dyna.actor.shape.yOffset = -400.0f;
    D_808BC000 = 160;
    Lights_PointNoGlowSetInfo(&this->unk_1E0, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    DoorWarp1_SetupAction(this, func_808B9B30);
}

void func_808B8C48(DoorWarp1* this, GlobalContext* globalCtx) {
    this->dyna.actor.shape.yOffset = 0.0f;
    Actor_SetScale(&this->dyna.actor, 0.1f);
    Lights_PointNoGlowSetInfo(&this->unk_1E0, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 255);
    if (((DOORWARP1_GET_FF(&this->dyna.actor) == ENDOORWARP1_FF_2) && CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA)) ||
        ((DOORWARP1_GET_FF(&this->dyna.actor) == ENDOORWARP1_FF_3) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT)) ||
        ((DOORWARP1_GET_FF(&this->dyna.actor) == ENDOORWARP1_FF_4) && CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG)) ||
        ((DOORWARP1_GET_FF(&this->dyna.actor) == ENDOORWARP1_FF_5) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD))) {
        s16 params = DOORWARP1_GET_FF00_2(&this->dyna.actor);

        params |= 6;
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_DOOR_WARP1,
                           this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + 10.0f,
                           this->dyna.actor.world.pos.z, this->dyna.actor.world.rot.x, this->dyna.actor.world.rot.y,
                           this->dyna.actor.world.rot.z, params);
        DoorWarp1_SetupAction(this, func_808BAAF4);
    } else {
        DoorWarp1_SetupAction(this, func_808BABF4);
    }
}

void func_808B8E78(DoorWarp1* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->dyna.actor, 0.1f);
    Lights_PointNoGlowSetInfo(&this->unk_1E0, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 0);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                              this->dyna.actor.world.pos.z, 200, 255, 255, 0);
    Actor_SetScale(&this->dyna.actor, 3.0f);
    this->unk_1D4 = 1;
    this->unk_1D0 = 0;
    this->unk_1A8 = 0.0f;
    this->unk_1AC = 0.0f;
    this->unk_1A4 = 700.0f;
    if (globalCtx->sceneNum == SCENE_INISIE_N) {
        DoorWarp1_SetupAction(this, func_808B96A0);
    } else if (gSaveContext.save.weekEventReg[86] & 0x80) {
        this->unk_1D4 = 0;
        DoorWarp1_SetupAction(this, func_808B921C);
    } else {
        DoorWarp1_SetupAction(this, func_808B9094);
    }
}

s32 func_808B900C(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 index;
    u8 ret = false;

    if (Cutscene_CheckActorAction(globalCtx, 569)) {
        index = Cutscene_GetActorActionIndex(globalCtx, 569);

        if (this->unk_208 != globalCtx->csCtx.actorActions[index]->action) {
            this->unk_208 = globalCtx->csCtx.actorActions[index]->action;
            if (globalCtx->csCtx.actorActions[index]->action == 2) {
                ret = true;
            }
        }
    }

    return ret;
}

void func_808B9094(DoorWarp1* this, GlobalContext* globalCtx) {
    if (func_808B900C(this, globalCtx)) {
        DoorWarp1_SetupAction(this, func_808B90CC);
    }
}

void func_808B90CC(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s16 sp2E = 0;
    f32 phi_f0 = 0.0f;

    if (globalCtx->sceneNum == SCENE_MITURIN) {
        sp2E = -10;
        phi_f0 = -5.0f;
    } else if (globalCtx->sceneNum == SCENE_HAKUGIN) {
        sp2E = -20;
    } else if (globalCtx->sceneNum == SCENE_SEA) {
        sp2E = -20;
    }

    Math_SmoothStepToF(&this->unk_1AC, 40.0f, 0.5f, 1.2f + phi_f0, 0.01f);
    Math_SmoothStepToF(&this->unk_1A4, 0.0f, 0.5f, 12.0f, 0.1f);
    if ((this->unk_1A4 < 460.0f) && (this->unk_1A4 > 100.0f)) {
        func_808BB8D4(this, globalCtx, 6);
    }

    if (this->unk_1A4 < 0.1f) {
        this->unk_1D0 = sp2E + 30;
        this->unk_1D4 = 0;
        DoorWarp1_SetupAction(this, func_808B921C);
    }

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WARP_HOLE_ENERGY - SFX_FLAG);
}

void func_808B921C(DoorWarp1* this, GlobalContext* globalCtx) {
    if (this->unk_1D0 != 0) {
        this->unk_1D0--;
        return;
    }

    Math_SmoothStepToF(&this->unk_1A8, 1.0f, 0.2f, 0.05f, 0.01f);
    this->unk_203 = (u8)(this->unk_1A8 * 200.0f);
    if (this->unk_1A8 > 0.8f) {
        func_808BB8D4(this, globalCtx, 1);
    }

    if (func_808B866C(this, globalCtx) && !Play_InCsMode(globalCtx)) {
        func_800B7298(globalCtx, &this->dyna.actor, 7);
        Message_StartTextbox(globalCtx, 0xF2, &this->dyna.actor);
        DoorWarp1_SetupAction(this, func_808B93A0);
    }

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BOSS_WARP_HOLE - SFX_FLAG);
}

void func_808B93A0(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (Message_GetState(&globalCtx->msgCtx) == 4 && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        if (globalCtx->msgCtx.choiceIndex == 0) {
            func_8019F208();
            func_800B7298(globalCtx, &this->dyna.actor, 9);
            player->unk_3A0.x = this->dyna.actor.world.pos.x;
            player->unk_3A0.z = this->dyna.actor.world.pos.z;
            this->unk_1CA = 1;
            DoorWarp1_SetupAction(this, func_808B9524);
        } else {
            func_8019F230();
            func_800B7298(globalCtx, &this->dyna.actor, 6);
            DoorWarp1_SetupAction(this, func_808B94A4);
        }
    }
    func_808BB8D4(this, globalCtx, 1);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BOSS_WARP_HOLE - SFX_FLAG);
}

void func_808B94A4(DoorWarp1* this, GlobalContext* globalCtx) {
    if (!func_808B866C(this, globalCtx) && (ActorCutscene_GetCurrentIndex() != globalCtx->playerActorCsIds[8])) {
        DoorWarp1_SetupAction(this, func_808B921C);
    }
    func_808BB8D4(this, globalCtx, 1);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BOSS_WARP_HOLE - SFX_FLAG);
}

void func_808B9524(DoorWarp1* this, GlobalContext* globalCtx) {
    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[9])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[9]);
    } else {
        ActorCutscene_Start(globalCtx->playerActorCsIds[9], NULL);
        DoorWarp1_SetupAction(this, func_808B958C);
    }
}

void func_808B958C(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_808BB8D4(this, globalCtx, 1);

    if (this->unk_1CA > 100) {
        if (player->actor.velocity.y < 10.0f) {
            player->actor.gravity = 0.1f;
        } else {
            player->actor.gravity = 0.0f;
        }
    } else {
        this->unk_1CA++;
    }

    this->unk_1D0++;
    if ((this->unk_1D0 > 120) && (gSaveContext.nextCutsceneIndex == 0xFFEF)) {
        func_808BA10C(this, globalCtx);
        globalCtx->unk_1887F = 3;
        gSaveContext.nextTransition = 3;
    }

    Math_SmoothStepToF(&this->unk_1A8, 6.0f, 0.2f, 0.02f, 0.01f);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_LINK_WARP - SFX_FLAG);
}

void func_808B96A0(DoorWarp1* this, GlobalContext* globalCtx) {
}

void func_808B96B0(DoorWarp1* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WARP_HOLE - SFX_FLAG);
    Math_SmoothStepToF(&this->unk_1B0, 255.0f, 0.4f, 10.0f, 0.01f);
    Math_SmoothStepToF(&this->unk_1B4, 255.0f, 0.4f, 10.0f, 0.01f);

    if (this->unk_1C4 < 100) {
        this->unk_1C4 += 2;
    }

    if (this->unk_1C6 < 120) {
        this->unk_1C6 += 4;
    }

    if (this->unk_1C8 < 230) {
        this->unk_1C8 += 4;
    } else {
        DoorWarp1_SetupAction(this, func_808B977C);
    }
}

void func_808B977C(DoorWarp1* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WARP_HOLE - SFX_FLAG);
    if (func_808B866C(this, globalCtx) && !Play_InCsMode(globalCtx)) {
        Player* player = GET_PLAYER(globalCtx);

        Audio_PlaySfxGeneral(NA_SE_EV_LINK_WARP, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
        func_800B7298(globalCtx, &this->dyna.actor, 9);
        player->unk_3A0.x = this->dyna.actor.world.pos.x;
        player->unk_3A0.z = this->dyna.actor.world.pos.z;
        this->unk_1CA = 1;
        DoorWarp1_SetupAction(this, func_808B9840);
    }
}

void func_808B9840(DoorWarp1* this, GlobalContext* globalCtx) {
    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[9])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[9]);
    } else {
        ActorCutscene_Start(globalCtx->playerActorCsIds[9], NULL);
        DoorWarp1_SetupAction(this, func_808B98A8);
    }
}

void func_808B98A8(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_1CA > 100) {
        if (player->actor.velocity.y < 10.0f) {
            player->actor.gravity = 0.1f;
        } else {
            player->actor.gravity = 0.0f;
        }
    } else {
        this->unk_1CA++;
    }

    Math_SmoothStepToF(&this->unk_1B0, 0.0f, 0.2f, 6.0f, 0.01f);

    this->unk_1D0++;
    if (D_808BC000 < this->unk_1D0) {
        if ((gSaveContext.nextCutsceneIndex == 0xFFEF) && (D_808BC000 < this->unk_1D0) &&
            (gSaveContext.nextCutsceneIndex == 0xFFEF)) {
            if (DOORWARP1_GET_FF00_1(&this->dyna.actor) != 0xFF) {
                globalCtx->nextEntranceIndex = globalCtx->setupExitList[DOORWARP1_GET_FF00_3(&this->dyna.actor)];
                Scene_SetExitFade(globalCtx);
                globalCtx->sceneLoadFlag = 0x14;
            } else {
                func_80169FDC(&globalCtx->state);
            }
        }
    }

    Math_StepToF(&this->unk_1A4, 2.0f, 0.01f);
    Math_StepToF(&this->unk_1A8, 10.0f, 0.02f);
    Lights_PointNoGlowSetInfo(&this->unk_1E0, player->actor.world.pos.x + 10, player->actor.world.pos.y + 10,
                              player->actor.world.pos.z + 10, 235, 255, 255, 255);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, player->actor.world.pos.x - 10, player->actor.world.pos.y - 10,
                              player->actor.world.pos.z - 10, 235, 255, 255, 255);
    Math_SmoothStepToF(&this->dyna.actor.shape.yOffset, 0.0f, 0.5f, 2.0f, 0.1f);
}

void func_808B9B30(DoorWarp1* this, GlobalContext* globalCtx) {
    if (fabsf(this->dyna.actor.xzDistToPlayer) >= 60.0f) {
        if (func_808B849C(this, globalCtx)) {
            this->unk_1A0 =
                (DmHina*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_DM_HINA,
                                            this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                            this->dyna.actor.world.pos.z, 0, 0, 0, func_808B849C(this, globalCtx) - 1);
        }
        DoorWarp1_SetupAction(this, func_808B9BE8);
    }
}

void func_808B9BE8(DoorWarp1* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WARP_HOLE - SFX_FLAG);
    Math_SmoothStepToF(&this->unk_1B0, 255.0f, 0.2f, 2.0f, 0.1f);
    Math_SmoothStepToF(&this->unk_1B4, 255.0f, 0.2f, 2.0f, 0.1f);
    if (this->unk_1C4 < 10) {
        this->unk_1C4 += 2;
    }

    if (this->unk_1C6 < 120) {
        this->unk_1C6 += 4;
    }

    if (this->unk_1C8 < 230) {
        this->unk_1C8 += 4;
        return;
    }

    this->dyna.actor.parent = NULL;
    if (func_808B849C(this, globalCtx)) {
        this->unk_202 = 1;
        DoorWarp1_SetupAction(this, func_808B9CE8);
    } else {
        DoorWarp1_SetupAction(this, func_808B9F10);
    }
}

void func_808B9CE8(DoorWarp1* this, GlobalContext* globalCtx) {
    if (this->unk_203 != 0) {
        if (1) {}
        return;
    }

    if (!Actor_HasParent(&this->dyna.actor, globalCtx)) {
        Actor_PickUp(&this->dyna.actor, globalCtx, func_808B849C(this, globalCtx) + 84, 30.0f, 80.0f);
        return;
    }

    switch (globalCtx->sceneNum) {
        case SCENE_MITURIN_BS:
            gSaveContext.save.unk_ECC[0] =
                (((void)0, gSaveContext.save.unk_ECC[0]) & 0xFFFFFF00) | (((u8)gSaveContext.save.unk_ECC[1]) & 0xFF);
            break;

        case SCENE_HAKUGIN_BS:
            gSaveContext.save.unk_ECC[0] = (((void)0, gSaveContext.save.unk_ECC[0]) & 0xFFFF00FF) |
                                           ((((u8)gSaveContext.save.unk_ECC[1]) & 0xFF) << 8);
            break;

        case SCENE_INISIE_BS:
            gSaveContext.save.unk_ECC[0] = (((void)0, gSaveContext.save.unk_ECC[0]) & 0xFF00FFFF) |
                                           ((((u8)gSaveContext.save.unk_ECC[1]) & 0xFF) << 0x10);
            break;

        case SCENE_SEA_BS:
            gSaveContext.save.unk_ECC[0] = (((void)0, gSaveContext.save.unk_ECC[0]) & 0x00FFFFFF) |
                                           ((((u8)gSaveContext.save.unk_ECC[1]) & 0xFF) << 0x18);
            break;
    }

    gSaveContext.save.unk_ECC[1] =
        (gSaveContext.save.unk_ECC[1] & 0xFFFFFF00) | ((((u8)gSaveContext.save.unk_ECC[1]) + 1) & 0xFF);
    Item_Give(globalCtx, func_808B849C(this, globalCtx) + (ITEM_REMAINS_ODOLWA - 1));
    DoorWarp1_SetupAction(this, func_808B9E94);
}

void func_808B9E94(DoorWarp1* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 2) {
        this->unk_1CE = 110;
        DoorWarp1_SetupAction(this, func_808B9ED8);
    }
}

void func_808B9ED8(DoorWarp1* this, GlobalContext* globalCtx) {
    this->unk_1CE--;
    if (this->unk_1CE <= 0) {
        func_808BA10C(this, globalCtx);
    }
}

void func_808B9F10(DoorWarp1* this, GlobalContext* globalCtx) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WARP_HOLE - SFX_FLAG);
    if ((this->unk_203 == 0) && func_808B866C(this, globalCtx) && !Play_InCsMode(globalCtx) && (this->unk_203 == 0)) {
        Player* player = GET_PLAYER(globalCtx);

        Interface_ChangeAlpha(1);
        func_800B7298(globalCtx, &this->dyna.actor, 9);
        player->unk_3A0.x = this->dyna.actor.world.pos.x;
        player->unk_3A0.z = this->dyna.actor.world.pos.z;
        this->unk_1CA = 20;
        DoorWarp1_SetupAction(this, func_808B9FD0);
    }
}

void func_808B9FD0(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);

    if (this->unk_1CA != 0) {
        this->unk_1CA--;
        return;
    }

    if (!ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[9])) {
        ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[9]);
    } else {
        ActorCutscene_Start(globalCtx->playerActorCsIds[9], NULL);
        Audio_PlaySfxGeneral(NA_SE_EV_LINK_WARP, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
        Animation_ChangeImpl(&this->skelAnime, &object_warp1_Anim_001374, 1.0f,
                             Animation_GetLastFrame(&object_warp1_Anim_001374.common),
                             Animation_GetLastFrame(&object_warp1_Anim_001374.common), 2, 40.0f, 1);
        this->unk_1CA = 50;
        D_808BC004 = player2->actor.world.pos.y;
        DoorWarp1_SetupAction(this, func_808BA550);
    }
}

void func_808BA10C(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 phi_v0_2;
    u8 phi_a0;
    s32 phi_v0_3;

    if ((globalCtx->sceneNum == SCENE_MITURIN_BS) || (globalCtx->sceneNum == SCENE_HAKUGIN_BS) ||
        (globalCtx->sceneNum == SCENE_INISIE_BS) || (globalCtx->sceneNum == SCENE_SEA_BS)) {
        D_801F4DE2 = globalCtx->sceneNum;
        if (globalCtx->sceneNum == SCENE_MITURIN_BS) {
            phi_v0_2 = 0;
        } else if (globalCtx->sceneNum == SCENE_HAKUGIN_BS) {
            phi_v0_2 = 1;
        } else if (globalCtx->sceneNum == SCENE_INISIE_BS) {
            phi_v0_2 = 2;
        } else if (globalCtx->sceneNum == SCENE_SEA_BS) {
            phi_v0_2 = 3;
        } else {
            phi_v0_2 = 0;
        }

        if (this->unk_202 != 0) {
            if (phi_v0_2 > 0) {
                gSaveContext.save.weekEventReg[7] |= 0x80;
            }

            switch (phi_v0_2) {
                case 0:
                    phi_a0 = gSaveContext.save.unk_ECC[0] & 0xFF;
                    break;

                case 1:
                    phi_a0 = (gSaveContext.save.unk_ECC[0] & 0xFF00) >> 8;
                    break;

                case 2:
                    phi_a0 = (gSaveContext.save.unk_ECC[0] & 0xFF0000) >> 0x10;
                    break;

                case 3:
                    phi_a0 = (gSaveContext.save.unk_ECC[0] & 0xFF000000) >> 0x18;
                    break;

                default:
                    phi_a0 = 0;
                    break;
            }

            switch (phi_a0) {
                case 0:
                    phi_v0_3 = 10;
                    break;

                case 1:
                    phi_v0_3 = 0;
                    break;

                case 2:
                    phi_v0_3 = 1;
                    break;

                case 3:
                    phi_v0_3 = 2;
                    break;

                default:
                    phi_v0_3 = 10;
                    break;
            }

            globalCtx->nextEntranceIndex = 0xCC00;
            if (phi_v0_3 < 10) {
                gSaveContext.nextCutsceneIndex = phi_v0_3 + 0xFFF0;
            }

            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 3;
            gSaveContext.nextTransition = 3;
        } else {
            switch (phi_v0_2) {
                case 0:
                    if (gSaveContext.save.weekEventReg[20] & 2) {
                        gSaveContext.save.weekEventReg[7] |= 0x80;
                        globalCtx->nextEntranceIndex = 0x3010;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                        gSaveContext.nextTransition = 3;
                    } else {
                        globalCtx->nextEntranceIndex = 0x8600;
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                        gSaveContext.nextTransition = 3;
                    }
                    break;

                case 1:
                    gSaveContext.save.weekEventReg[33] |= 0x80;
                    globalCtx->nextEntranceIndex = 0xAE70;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 3;
                    gSaveContext.nextTransition = 3;
                    break;

                case 3:
                    if (gSaveContext.save.weekEventReg[55] & 0x80) {
                        globalCtx->nextEntranceIndex = 0x6A90;
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                        gSaveContext.nextTransition = 3;
                    } else {
                        gSaveContext.save.weekEventReg[55] |= 0x80;
                        globalCtx->nextEntranceIndex = 0x6A80;
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                        gSaveContext.nextTransition = 3;
                    }
                    break;

                case 2:
                    gSaveContext.save.weekEventReg[52] |= 0x20;
                    globalCtx->nextEntranceIndex = 0x20F0;
                    gSaveContext.nextCutsceneIndex = 0xFFF2;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 3;
                    gSaveContext.nextTransition = 3;
                    break;
            }
        }
    } else if (DOORWARP1_GET_FF00_1(&this->dyna.actor) != 0xFF) {
        if (DOORWARP1_GET_FF(&this->dyna.actor) == ENDOORWARP1_FF_6) {
            gSaveContext.respawnFlag = ~1;
        }
        globalCtx->nextEntranceIndex = globalCtx->setupExitList[DOORWARP1_GET_FF00_3(&this->dyna.actor)];
        Scene_SetExitFade(globalCtx);
        globalCtx->sceneLoadFlag = 0x14;
    } else {
        func_80169FDC(&globalCtx->state);
    }
}

void func_808BA550(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player2 = GET_PLAYER(globalCtx);
    Player* player = GET_PLAYER(globalCtx);
    s16 i;
    s32 temp_f16;
    f32 temp_f0;
    f32 temp_f2;
    s32 temp;
    s32 tempS;

    if (this->unk_1CA != 0) {
        this->unk_1CA--;
    }

    if (this->unk_1CA < 0x1F) {
        temp_f0 = 0.0f;
        switch (player2->transformation) {
            case PLAYER_FORM_FIERCE_DEITY:
                temp_f0 = -37.0f;
                break;

            case PLAYER_FORM_GORON:
                temp_f0 = -37.0f;
                break;

            case PLAYER_FORM_ZORA:
                temp_f0 = -37.0f;
                break;

            case PLAYER_FORM_DEKU:
                temp_f0 = -20.0f;
                break;

            case PLAYER_FORM_HUMAN:
                temp_f0 = -25.0f;
                break;
        }

        temp_f2 = this->dyna.actor.world.pos.y + (this->dyna.actor.shape.yOffset * 0.1f) + temp_f0;

        if (D_808BC004 < temp_f2) {
            player->actor.world.pos.y = temp_f2;
        }

        if (this->unk_1CA <= 0) {
            if (this->unk_1CC < 4000) {
                this->unk_1CC += 40;
            }
            player->actor.world.rot.y -= this->unk_1CC;
            player->actor.shape.rot.y -= this->unk_1CC;
        }
        Math_SmoothStepToF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.5f, 0.1f, 0.01f);
        Math_SmoothStepToF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.5f, 0.1f, 0.01f);
    }

    this->unk_1D0++;
    if ((D_808BC000 < this->unk_1D0) && (gSaveContext.nextCutsceneIndex == 0xFFEF)) {
        func_808BA10C(this, globalCtx);
    }

    if (this->unk_1D0 > 140) {
        globalCtx->envCtx.fillScreen = 1;
        temp_f0 = (this->unk_1D0 - 140) / 20.0f;
        if (temp_f0 > 1.0f) {
            temp_f0 = 1.0f;
        }
        globalCtx->envCtx.screenFillColor[0] = 160;
        globalCtx->envCtx.screenFillColor[1] = 160;
        globalCtx->envCtx.screenFillColor[2] = 160;
        globalCtx->envCtx.screenFillColor[3] = 255.0f * temp_f0;
    }

    Lights_PointNoGlowSetInfo(&this->unk_1E0, player->actor.world.pos.x + 10.0f, player->actor.world.pos.y + 10.0f,
                              player->actor.world.pos.z + 10.0f, 235, 255, 255, 255);
    Lights_PointNoGlowSetInfo(&this->unk_1F4, player->actor.world.pos.x - 10.0f, player->actor.world.pos.y - 10.0f,
                              player->actor.world.pos.z - 10.0f, 235, 255, 255, 255);
    Math_SmoothStepToF(&this->dyna.actor.shape.yOffset, 800.0f, 0.2f, 15.0f, 0.01f);
    this->dyna.actor.shape.rot.y += 0x320;
    Math_SmoothStepToF(&this->unk_1BC, 1.13f, 0.2f, 0.1f, 0.01f);
    Math_StepToF(&this->unk_1A4, 2.0f, 0.003f);
    Math_StepToF(&this->unk_1A8, 10.0f, 0.006f);
    Math_SmoothStepToF(&this->unk_1B0, 0.0f, 0.2f, 3.0f, 0.01f);
    Math_SmoothStepToF(&this->unk_1B4, 0.0f, 0.2f, 2.0f, 0.01f);
    Math_SmoothStepToF(&this->unk_1B8, 255.0f, 0.1f, 1.0f, 0.01f);

    tempS = D_808BC000;
    if (1) {}
    temp_f0 = 1.0f - ((f32)(D_808BC000 - this->unk_1D0) / ((D_808BC000 - tempS) + 100));
    if (temp_f0 > 0.0f) {
        temp_f16 = -255.0f * temp_f0;

        for (i = 0; i < 3; i++) {
            globalCtx->envCtx.lightSettings.diffuseColor1[i] = temp_f16;
            globalCtx->envCtx.lightSettings.fogColor[i] = temp_f16;
            globalCtx->envCtx.lightSettings.ambientColor[i] = temp_f16;
        }

        globalCtx->envCtx.lightSettings.fogNear = -500.0f * temp_f0;
        if (globalCtx->envCtx.lightSettings.fogNear < -300) {
            globalCtx->roomCtx.currRoom.segment = NULL;
        }
    }
}

void func_808BAAF4(DoorWarp1* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 cutscene;
    f32 phi_f2;

    phi_f2 = 200.0f;
    if (globalCtx->sceneNum == SCENE_SEA) {
        phi_f2 = 85.0f;
    }

    if (!(gSaveContext.save.weekEventReg[86] & 0x80) && (fabsf(this->dyna.actor.xzDistToPlayer) < phi_f2) &&
        ((player->actor.world.pos.y - 20.0f) < this->dyna.actor.world.pos.y) &&
        (this->dyna.actor.world.pos.y < (player->actor.world.pos.y + 20.0f))) {
        cutscene = this->dyna.actor.cutscene;

        if (ActorCutscene_GetCanPlayNext(cutscene)) {
            ActorCutscene_Start(cutscene, &this->dyna.actor);
            gSaveContext.save.weekEventReg[86] |= 0x80;
            DoorWarp1_SetupAction(this, func_808BABF4);
        } else {
            ActorCutscene_SetIntentToPlay(cutscene);
        }
    }
}

void func_808BABF4(DoorWarp1* this, GlobalContext* globalCtx) {
}

void DoorWarp1_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorWarp1* this = THIS;

    if (this->unk_203 == 0) {
        this->unk_204 = 1.0f;
    }

    if ((this->unk_1A0 != NULL) && (this->unk_1A0->unk_15C != this->unk_204)) {
        this->unk_1A0->actor.world.pos.y = this->dyna.actor.world.pos.y;
        this->unk_1A0->unk_158 = this->dyna.actor.world.pos.y;
        this->unk_1A0->unk_15C = this->unk_204;
    }

    this->actionFunc(this, globalCtx);

    if (DOORWARP1_GET_FF(&this->dyna.actor) < ENDOORWARP1_FF_2) {
        Actor_SetScale(&this->dyna.actor, this->unk_1C4 / 100.0f);
    }
}

void func_808BACCC(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0xFF, 0xFF, 200, 255, 255, (u8)this->unk_1B8);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, (u8)this->unk_1B8);

    POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL,
                                   &this->dyna.actor, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    SkelAnime_Update(&this->skelAnime);
}

void func_808BAE9C(DoorWarp1* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    s32 sp94 = globalCtx->state.frames * 10;
    f32 sp90;
    f32 sp8C;
    f32 phi_f12;
    f32 sp84;

    if (this->unk_1A4 >= 1.0f) {
        sp90 = 0.0f;
    } else {
        sp90 = 1.0f - this->unk_1A4;
    }

    if (this->unk_1A8 >= 1.0f) {
        sp8C = 0.0f;
    } else {
        sp8C = 1.0f - this->unk_1A8;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp84 = 1.0f - ((2.0f - this->unk_1A4) / 1.7f);
    this->unk_1AC += sp84 * 15.0f;
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255.0f * sp84, 255, 255, (u8)this->unk_1B4);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 255.0f * sp84, 255, 255);

    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + 1.0f,
                             this->dyna.actor.world.pos.z, MTXMODE_NEW);
    phi_f12 = 1.0f;
    if (this->unk_203 != 0) {
        phi_f12 = this->unk_204 * phi_f12;
    }
    Matrix_Scale(phi_f12, phi_f12, phi_f12, MTXMODE_APPLY);

    gSPSegment(POLY_XLU_DISP++, 0x0A, Matrix_NewMtx(globalCtx->state.gfxCtx));
    Matrix_StatePush();
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, sp94 & 0xFF, -((s16)(2.0f * this->unk_1AC) & 0x1FF), 0x100,
                                0x100, 1, sp94 & 0xFF, -((s16)(2.0f * this->unk_1AC) & 0x1FF), 0x100, 0x100));

    Matrix_InsertTranslation(0.0f, this->unk_1A4 * 230.0f, 0.0f, MTXMODE_APPLY);
    Matrix_Scale(((this->unk_1C6 * sp90) / 100.0f) + 1.0f, 1.0f, ((this->unk_1C6 * sp90) / 100.0f) + 1.0f,
                 MTXMODE_APPLY);

    gSPSegment(POLY_XLU_DISP++, 0x09, Matrix_NewMtx(globalCtx->state.gfxCtx));
    gSPDisplayList(POLY_XLU_DISP++, object_warp1_DL_0001A0);

    Matrix_StatePop();

    if (this->unk_1B0 > 0.0f) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255.0f * sp84, 255, 255, (u8)this->unk_1B0);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 255.0f * sp84, 255, 255);

        sp94 *= 2;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, sp94 & 0xFF, -((s16)this->unk_1AC & 0x1FF), 0x100,
                                    0x100, 1, sp94 & 0xFF, -((s16)this->unk_1AC & 0x1FF), 0x100, 0x100));

        Matrix_InsertTranslation(0.0f, this->unk_1A8 * 60.0f, 0.0f, MTXMODE_APPLY);
        Matrix_Scale(((this->unk_1C8 * sp8C) / 100.0f) + 1.0f, 1.0f, ((this->unk_1C8 * sp8C) / 100.0f) + 1.0f,
                     MTXMODE_APPLY);

        gSPSegment(POLY_XLU_DISP++, 0x09, Matrix_NewMtx(globalCtx->state.gfxCtx));
        gSPDisplayList(POLY_XLU_DISP++, object_warp1_DL_0001A0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808BB4C4(DoorWarp1* this, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_warp1_DL_0076C0);
}

#ifdef NON_MATCHING
// GraphicsContext should be compiler-managed?
void func_808BB4F4(DoorWarp1* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    GraphicsContext* gfxCtx;
    Color_RGB8 sp64[] = {
        { 50, 150, 0 },
        { 100, 150, 200 },
        { 0, 50, 200 },
        { 120, 150, 0 },
    };
    s32 sp60 = 0;

    if (this->unk_1D4 != 0) {
        Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + this->unk_1A4,
                                 this->dyna.actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(4.0f, this->unk_1AC, 4.0f, MTXMODE_APPLY);
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_warp1_Matanimheader_0044D8));
        Gfx_DrawDListXlu(globalCtx, object_warp1_DL_003230);
        return;
    }

    if (globalCtx->sceneNum != SCENE_MITURIN) {
        if (globalCtx->sceneNum == SCENE_HAKUGIN) {
            sp60 = 1;
        } else if (globalCtx->sceneNum == SCENE_SEA) {
            sp60 = 2;
        } else if (globalCtx->sceneNum == SCENE_INISIE_R) {
            sp60 = 3;
        }
    }

    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                             MTXMODE_NEW);
    Matrix_RotateY(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
    Matrix_Scale(1.0f, this->unk_1A8, 1.0f, MTXMODE_APPLY);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_warp1_Matanimheader_0057D8));

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, sp64[sp60].r, sp64[sp60].g, sp64[sp60].b, 255);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, 255);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_warp1_DL_004690);
    gfxCtx = globalCtx->state.gfxCtx;

    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_warp1_Matanimheader_007238));
    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                             MTXMODE_NEW);
    Matrix_RotateY(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
    Matrix_Scale(1.0f, 0.0f, 1.0f, MTXMODE_APPLY);

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    OPEN_DISPS(gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, sp64[sp60].r, sp64[sp60].g, sp64[sp60].b, 255);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->unk_203);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_warp1_DL_0058C8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
static Color_RGB8 D_808BBB50[] = {
    { 50, 150, 0 },
    { 100, 150, 200 },
    { 0, 50, 200 },
    { 120, 150, 0 },
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BB4F4.s")
#endif

void DoorWarp1_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DoorWarp1* this = THIS;

    switch (DOORWARP1_GET_FF(&this->dyna.actor)) {
        case ENDOORWARP1_FF_0:
            func_808BAE9C(this, globalCtx);
            break;

        case ENDOORWARP1_FF_1:
            func_808BACCC(this, globalCtx);
            func_808BAE9C(this, globalCtx);
            break;

        case ENDOORWARP1_FF_2:
        case ENDOORWARP1_FF_3:
        case ENDOORWARP1_FF_4:
        case ENDOORWARP1_FF_5:
            func_808BB4C4(this, globalCtx);
            break;

        case ENDOORWARP1_FF_6:
            func_808BB4F4(this, globalCtx);
            break;
    }
}

#ifdef NON_MATCHING
// casting/macro on temp_s1/s0
void func_808BB8D4(DoorWarp1* this, GlobalContext* globalCtx, s32 arg2) {
    static Vec3f D_808BBB5C = { 0.0f, 0.05f, 0.0f };
    static Vec3f D_808BBB68 = { 0.0f, 0.25f, 0.0f };
    Vec3f sp9C;
    Color_RGBA8 sp98;
    Color_RGBA8 sp94;
    s32 i;
    s16 temp_s0;
    s32 temp_s1;
    s32 phi_s2;

    for (i = 0; i < arg2; i++) {
        temp_s1 = (Rand_ZeroOne() * 0x10000);
        temp_s0 = temp_s1 - 0x8000;

        sp9C.x = (-Math_SinS(temp_s0) * 35.0f) + this->dyna.actor.world.pos.x;
        sp9C.y = this->dyna.actor.world.pos.y;
        temp_s0 = (s16)(temp_s1 - 0x8000);
        sp9C.z = Math_CosS(temp_s0) * 35.0f + this->dyna.actor.world.pos.z;

        D_808BBB5C.x = 0.0f;
        D_808BBB68.y = 0.25f;

        sp98.r = 255;
        sp98.g = 255;
        sp98.b = 255;
        sp94.r = 200;
        sp94.g = 200;
        sp94.b = 255;

        D_808BBB5C.z = 0.0f;

        temp_s1 = (s16)((Rand_ZeroOne() * 1000.0f) + 800.0f);

        phi_s2 = 27;
        if (arg2 >= 2) {
            phi_s2 = 8;
            D_808BBB68.y = 1.8f;
            D_808BBB5C.x = -Math_SinS(temp_s0) * 5.0f;
            D_808BBB5C.z = Math_CosS(temp_s0) * 5.0f;
        }
        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp9C, &D_808BBB5C, &D_808BBB68, &sp98, &sp94, temp_s1, phi_s2);
    }
}
#else
static Vec3f D_808BBB5C = { 0.0f, 0.05f, 0.0f };
static Vec3f D_808BBB68 = { 0.0f, 0.25f, 0.0f };
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BB8D4.s")
#endif
