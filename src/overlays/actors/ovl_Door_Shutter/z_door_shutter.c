/*
 * File: z_door_shutter.c
 * Overlay: ovl_Door_Shutter
 * Description: Studded Lifting Door / Ikana Castle Rolling Door
 */

#include "z_door_shutter.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_bdoor/object_bdoor.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_hakugin_obj/object_hakugin_obj.h"
#include "objects/object_dblue_object/object_dblue_object.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"
#include "objects/object_redead_obj/object_redead_obj.h"
#include "objects/object_ikninside_obj/object_ikninside_obj.h"
#include "objects/object_random_obj/object_random_obj.h"
#include "objects/object_kinsta1_obj/object_kinsta1_obj.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"
#include "objects/object_last_obj/object_last_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DoorShutter*)thisx)

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx);

void DoorShutter_SetupType(DoorShutter* this, GlobalContext* globalCtx);
void func_808A0F88(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1080(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1090(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1548(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1618(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1684(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1784(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1B48(DoorShutter* this, GlobalContext* globalCtx);
void func_808A1C50(DoorShutter* this, GlobalContext* globalCtx);
void DoorShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Door_Shutter_InitVars = {
    ACTOR_DOOR_SHUTTER,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorShutter),
    (ActorFunc)DoorShutter_Init,
    (ActorFunc)DoorShutter_Destroy,
    (ActorFunc)DoorShutter_Update,
    (ActorFunc)NULL,
};

typedef struct {
    /* 0x0 */ s16 objectId;
    /* 0x2 */ u8 index1;
    /* 0x3 */ u8 index2;
} ShutterObjectInfo; // size = 0x4

ShutterObjectInfo D_808A2180[] = {
    { OBJECT_BDOOR, 0, 0 },       { GAMEPLAY_KEEP, 1, 1 },        { OBJECT_NUMA_OBJ, 2, 2 },
    { OBJECT_HAKUGIN_OBJ, 3, 3 }, { OBJECT_DBLUE_OBJECT, 4, 4 },  { OBJECT_IKANA_OBJ, 5, 5 },
    { OBJECT_REDEAD_OBJ, 6, 6 },  { OBJECT_IKNINSIDE_OBJ, 7, 7 }, { OBJECT_LAST_OBJ, 11, 11 },
    { OBJECT_RANDOM_OBJ, 8, 8 },  { OBJECT_KINSTA1_OBJ, 9, 9 },   { OBJECT_KAIZOKU_OBJ, 10, 10 },
};

typedef struct {
    /* 0x0 */ Gfx* unk_00;
    /* 0x4 */ Gfx* unk_04;
    /* 0x8 */ u8 unk_08;
    /* 0x9 */ u8 translateZ;
    /* 0xA */ u8 unk_0A;
    /* 0xB */ u8 unk_0B;
} ShutterInfo; // size = 0xC

ShutterInfo D_808A21B0[] = {
    { object_bdoor_DL_0000C0, NULL, 130, 12, 50, 15 },
    { gameplay_keep_DL_077990, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_numa_obj_DL_007150, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_hakugin_obj_DL_000128, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_dblue_object_DL_017D00, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_ikana_obj_DL_014A40, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_redead_obj_DL_0001A0, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_ikninside_obj_DL_004440, object_ikninside_obj_DL_005260, 130, 0, 20, 15 },
    { object_random_obj_DL_000190, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_kinsta1_obj_DL_000198, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_kaizoku_obj_DL_0001A0, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
    { object_last_obj_DL_0039C0, gameplay_keep_DL_078A80, 130, 12, 20, 15 },
};

s8 D_808A2240[] = {
    -1, -1, -1, -1, -1, 0, -1, -1,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 index;
} ShutterSceneInfo; // size = 0x4

ShutterSceneInfo D_808A2258[] = {
    { SCENE_MITURIN, 2 },   { SCENE_HAKUGIN, 3 },   { SCENE_SEA, 4 },
    { SCENE_INISIE_N, 5 },  { SCENE_INISIE_R, 5 },  { SCENE_REDEAD, 6 },
    { SCENE_IKNINSIDE, 7 }, { SCENE_CASTLE, 7 },    { SCENE_RANDOM, 9 },
    { SCENE_KINSTA1, 10 },  { SCENE_KAIZOKU, 11 },  { SCENE_PIRATE, 11 },
    { SCENE_TORIDE, 11 },   { SCENE_LAST_DEKU, 8 }, { SCENE_LAST_GORON, 8 },
    { SCENE_LAST_ZORA, 8 }, { SCENE_LAST_LINK, 8 }, { -1, 1 },
};

typedef struct {
    /* 0x00 */ s16 dungeonScene;
    /* 0x02 */ s16 bossScene;
    /* 0x04 */ u8 index;
} BossDoorInfo; // size = 0x6

BossDoorInfo D_808A22A0[] = {
    { SCENE_MITURIN, SCENE_MITURIN_BS, 1 }, { SCENE_HAKUGIN, SCENE_HAKUGIN_BS, 2 }, { SCENE_SEA, SCENE_SEA_BS, 3 },
    { SCENE_INISIE_N, SCENE_INISIE_BS, 4 }, { SCENE_INISIE_R, SCENE_INISIE_BS, 4 }, { -1, -1, 0 },
};

Vec3f D_808A22C4 = { 120.0f, 0.0f, 0.0f };

Vec3f D_808A22D0 = { -90.0f, 0.0f, 0.0f };

TexturePtr D_808A22DC[] = {
    object_bdoor_Tex_006BA0, object_bdoor_Tex_005BA0, object_bdoor_Tex_0005C0,
    object_bdoor_Tex_004BA0, object_bdoor_Tex_003BA0,
};

void DoorShutter_SetupAction(DoorShutter* this, DoorShutterActionFunc actionFunc) {
    this->actionFunc = actionFunc;
    this->unk_167 = 0;
}

s32 func_808A0900(DoorShutter* this, GlobalContext* globalCtx) {
    TransitionActorEntry* transitionEntry = &globalCtx->doorCtx.transitionActorList[DOORSHUTTER_GET_FC00(&this->actor)];
    s8 frontRoom = transitionEntry->sides[0].room;

    if (frontRoom == transitionEntry->sides[1].room) {
        if (ABS_ALT(BINANG_SUB(this->actor.shape.rot.y, this->actor.yawTowardsPlayer)) < 0x4000) {
            frontRoom = -1;
        }
    }
    return frontRoom == this->actor.room;
}

s32 DoorShutter_SetupDoor(DoorShutter* this, GlobalContext* globalCtx) {
    ShutterObjectInfo* sp24 = &D_808A2180[this->unk_163];
    s32 doorType = this->doorType;

    if (doorType != 4) {
        if (func_808A0900(this, globalCtx)) {
            if ((doorType == 7) || (doorType == 6)) {
                doorType = 1;
            } else if (doorType == 5) {
                doorType = 3;
            } else {
                doorType = 0;
            }
        }
    }

    if (doorType == 0) {
        this->unk_164 = sp24->index1;
    } else {
        this->unk_164 = sp24->index2;
    }

    if (doorType == 1) {
        if (!Flags_GetClear(globalCtx, this->actor.room)) {
            DoorShutter_SetupAction(this, func_808A0F88);
            this->unk_168 = 1.0f;
            return true;
        }
    } else if ((doorType == 2) || (doorType == 7)) {
        if (!Flags_GetSwitch(globalCtx, DOORSHUTTER_GET_7F(&this->actor))) {
            DoorShutter_SetupAction(this, func_808A1548);
            this->unk_168 = 1.0f;
            return true;
        }
        DoorShutter_SetupAction(this, func_808A1618);
        return false;
    } else if (doorType == 3) {
        DoorShutter_SetupAction(this, func_808A1080);
        this->unk_168 = 1.0f;
        return false;
    }
    DoorShutter_SetupAction(this, func_808A1090);
    return false;
}

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DoorShutter* this = THIS;
    s32 sp24;
    s32 i;
    s8 objId;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->doorType = DOORSHUTTER_GET_380(&this->actor);
    sp24 = D_808A2240[this->doorType];

    if (sp24 < 0) {
        ShutterSceneInfo* shutterSceneInfo = &D_808A2258[0];

        for (i = 0; i < ARRAY_COUNT(D_808A2258) - 1; i++, shutterSceneInfo++) {
            if (globalCtx->sceneNum == shutterSceneInfo->sceneNum) {
                break;
            }
        }

        sp24 = shutterSceneInfo->index;
        if (sp24 == 6) {
            this->actor.flags |= ACTOR_FLAG_10000000;
        }
    } else if (sp24 == 0) {
        BossDoorInfo* bossDoorInfo = &D_808A22A0[0];

        for (i = 0; i < ARRAY_COUNT(D_808A22A0) - 1; i++, bossDoorInfo++) {
            if ((globalCtx->sceneNum == bossDoorInfo->dungeonScene) ||
                (globalCtx->sceneNum == bossDoorInfo->bossScene)) {
                break;
            }
        }

        this->unk_15E = bossDoorInfo->index;
    } else {
        this->actor.room = -1;
    }

    // clang-format off
    objId = Object_GetIndex(&globalCtx->objectCtx, D_808A2180[sp24].objectId); this->requiredObjBankIndex = objId; if (objId < 0) { Actor_MarkForDeath(&this->actor); return; }
    // clang-format on

    DoorShutter_SetupAction(this, DoorShutter_SetupType);
    this->unk_163 = sp24;

    if ((this->doorType == 4) || (this->doorType == 5)) {
        if (!Flags_GetSwitch(globalCtx, DOORSHUTTER_GET_7F(&this->actor))) {
            this->unk_166 = 10;
        }
    }

    Actor_SetFocus(&this->actor, 60.0f);
}

void DoorShutter_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DoorShutter* this = THIS;

    if (this->actor.room >= 0) {
        s32 transitionActorId = DOORSHUTTER_GET_FC00(&this->actor);

        globalCtx->doorCtx.transitionActorList[transitionActorId].id =
            -globalCtx->doorCtx.transitionActorList[transitionActorId].id;
    }
}

void DoorShutter_SetupType(DoorShutter* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->requiredObjBankIndex) && ((MREG(64) == 0) || (MREG(68) == 0))) {
        this->actor.objBankIndex = this->requiredObjBankIndex;
        this->actor.draw = DoorShutter_Draw;
        DoorShutter_SetupDoor(this, globalCtx);
    }
}

f32 func_808A0D90(GlobalContext* globalCtx, DoorShutter* this, f32 arg2, f32 arg3, f32 arg4) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp28;
    Vec3f sp1C;

    sp28.x = player->actor.world.pos.x;
    sp28.y = player->actor.world.pos.y + arg2;
    sp28.z = player->actor.world.pos.z;

    Actor_OffsetOfPointInActorCoords(&this->actor, &sp1C, &sp28);

    if ((arg3 < fabsf(sp1C.x)) || (arg4 < fabsf(sp1C.y))) {
        return FLT_MAX;
    }
    return sp1C.z;
}

s32 func_808A0E28(DoorShutter* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!Player_InCsMode(&globalCtx->state)) {
        ShutterInfo* shutterInfo = &D_808A21B0[this->unk_164];
        f32 temp_f0 = func_808A0D90(globalCtx, this, 0.0f, shutterInfo->unk_0A, shutterInfo->unk_0B);

        if (fabsf(temp_f0) < 50.0f) {
            s16 temp_v0_2 = BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y);

            if (temp_f0 > 0.0f) {
                temp_v0_2 = 0x8000 - temp_v0_2;
            }

            if (ABS_ALT(temp_v0_2) < 0x3000) {
                return (temp_f0 >= 0.0f) ? 1.0f : -1.0f;
            }
        }
    }
    return false;
}

void func_808A0F88(DoorShutter* this, GlobalContext* globalCtx) {
    if (Flags_GetClear(globalCtx, this->actor.room) || Flags_GetClearTemp(globalCtx, this->actor.room)) {
        this->unk_160 = this->actor.cutscene;
        if (this->doorType == 7) {
            if (this->unk_160 != -1) {
                this->unk_160 = ActorCutscene_GetAdditionalCutscene(this->unk_160);
            }
        }

        if (ActorCutscene_GetCanPlayNext(this->unk_160)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_160, &this->actor);
            Flags_SetClear(globalCtx, this->actor.room);
            DoorShutter_SetupAction(this, func_808A1784);
            this->unk_167 = -1;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_160);
        }
    } else if (func_808A0E28(this, globalCtx)) {
        Player* player = GET_PLAYER(globalCtx);

        player->doorType = -1;
        player->doorActor = &this->actor;
        this->actor.textId = 0x1801;
        func_80122F28(player);
    }
}

void func_808A1080(DoorShutter* this, GlobalContext* globalCtx) {
}

void func_808A1090(DoorShutter* this, GlobalContext* globalCtx) {
    if (this->unk_15C != 0) {
        DoorShutter_SetupAction(this, func_808A1684);
        this->actor.velocity.y = 0.0f;
        if (this->unk_166 != 0) {
            Flags_SetSwitch(globalCtx, DOORSHUTTER_GET_7F(&this->actor));
            if (this->doorType != 5) {
                gSaveContext.save.inventory.dungeonKeys[gSaveContext.mapIndex]--;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIN_KEY_UNLOCK_B);
            }
        }
    } else {
        s32 doorDirection = func_808A0E28(this, globalCtx);

        if (doorDirection != 0) {
            Player* player = GET_PLAYER(globalCtx);

            player->doorType = 2;
            player->doorDirection = doorDirection;
            player->doorActor = &this->actor;

            if (this->unk_163 == 7) {
                player->doorTimer = 12;
            } else {
                player->doorTimer = 0;
            }

            if (this->doorType == 6) {
                if (gSaveContext.save.playerData.healthCapacity < (DOORSHUTTER_GET_1F(&this->actor) * 0x10)) {
                    player->doorType = -1;
                    this->actor.textId = 0x14FC;
                }
            } else if (this->unk_166 != 0) {
                if (this->doorType == 5) {
                    if (!CHECK_DUNGEON_ITEM(0, gSaveContext.mapIndex)) {
                        player->doorType = -1;
                        this->actor.textId = 0x1803;
                    }
                    player->doorTimer += 10;
                } else if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) <= 0) {
                    player->doorType = -1;
                    this->actor.textId = 0x1802;
                } else {
                    player->doorTimer += 10;
                }
            }
            func_80122F28(player);
        }
    }
}

void func_808A1288(DoorShutter* this, GlobalContext* globalCtx) {
    if (this->actor.category == ACTORCAT_DOOR) {
        Player* player = GET_PLAYER(globalCtx);
        s32 sp38 = this->unk_164;
        s32 sp34 = 0xF;

        if (DoorShutter_SetupDoor(this, globalCtx)) {
            sp34 = 0x20;
        }

        DoorShutter_SetupAction(this, func_808A1684);

        this->unk_164 = sp38;
        this->unk_168 = 0.0f;

        func_800DFFAC(globalCtx->cameraPtrs[CAM_ID_MAIN], &this->actor, player->unk_3BA, this->unk_168, 12, sp34, 10);
    }
}

s32 func_808A1340(DoorShutter* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this->actor.velocity.y == 0.0f) {
        func_808A1288(this, globalCtx);
        if (this->unk_163 != 7) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SLIDE_DOOR_OPEN);
        }
    }

    if (this->unk_163 == 7) {
        s32 pad;

        if (this->unk_163 == 7) {
            func_800B9010(&this->actor, NA_SE_EV_IKANA_DOOR_OPEN - SFX_FLAG);
        }

        Lib_Vec3f_TranslateAndRotateY(&this->actor.home.pos, this->actor.shape.rot.y,
                                      (this->unk_163 == 7) ? &D_808A22C4 : &D_808A22D0, &sp2C);
        Math_StepToF(&this->actor.velocity.y, 5.0f, 0.5f);

        if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &sp2C, this->actor.velocity.y) == 0.0f) {
            return true;
        }
    } else {
        Math_StepToF(&this->actor.velocity.y, 15.0f, 3.0f);

        if (Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 200.0f, this->actor.velocity.y)) {
            return true;
        }
    }
    return false;
}

s32 func_808A1478(DoorShutter* this, GlobalContext* globalCtx, f32 arg2) {
    f32 temp = 1.0f - arg2;

    if (temp == this->unk_168) {
        if (arg2 == 1.0f) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_METALDOOR_CLOSE);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_METALDOOR_OPEN);
        }

        if ((this->unk_160 != -1) && (ActorCutscene_GetCurrentIndex() == this->unk_160)) {
            func_800B724C(globalCtx, &this->actor, 1);
        }
    }

    if (Math_StepToF(&this->unk_168, arg2, 0.2f)) {
        return true;
    }
    return false;
}

void func_808A1548(DoorShutter* this, GlobalContext* globalCtx) {
    if (func_808A1478(this, globalCtx, 1.0f)) {
        if (Flags_GetSwitch(globalCtx, DOORSHUTTER_GET_7F(&this->actor))) {
            this->unk_160 = this->actor.cutscene;
            if (ActorCutscene_GetCanPlayNext(this->unk_160)) {
                ActorCutscene_StartAndSetUnkLinkFields(this->unk_160, &this->actor);
                DoorShutter_SetupAction(this, func_808A1784);
                this->unk_167 = -1;
            } else {
                ActorCutscene_SetIntentToPlay(this->unk_160);
            }
        } else if (func_808A0E28(this, globalCtx)) {
            Player* player = GET_PLAYER(globalCtx);

            player->doorType = -1;
            player->doorActor = &this->actor;
            this->actor.textId = 0x1800;
            func_80122F28(player);
        }
    }
}

void func_808A1618(DoorShutter* this, GlobalContext* globalCtx) {
    if ((this->unk_15C == 0) && !Flags_GetSwitch(globalCtx, DOORSHUTTER_GET_7F(&this->actor))) {
        DoorShutter_SetupAction(this, func_808A1548);
    } else {
        func_808A1090(this, globalCtx);
    }
}

void func_808A1684(DoorShutter* this, GlobalContext* globalCtx) {
    f32 phi_f0;

    if ((DECR(this->unk_166) == 0) && (globalCtx->roomCtx.unk31 == 0) && func_808A1340(this, globalCtx)) {
        if (this->doorType == 5) {
            phi_f0 = 20.0f;
        } else {
            phi_f0 = 50.0f;
        }

        if (phi_f0 < this->actor.xzDistToPlayer) {
            if (this->unk_163 == 7) {
                this->actor.velocity.y = 0.0f;
            } else {
                if (DoorShutter_SetupDoor(this, globalCtx)) {
                    this->actor.velocity.y = 30.0f;
                }
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SLIDE_DOOR_CLOSE);
            }
            DoorShutter_SetupAction(this, func_808A1B48);
        }
    }
}

void func_808A1784(DoorShutter* this, GlobalContext* globalCtx) {
    if (this->unk_167 != 0) {
        if (func_800F22C4(this->unk_160, &this->actor)) {
            if (this->unk_167 < 0) {
                if ((globalCtx->state.frames % 2) != 0) {
                    this->unk_167++;
                }
            } else {
                this->unk_167--;
            }
        }
    } else if (func_808A1478(this, globalCtx, 0.0f)) {
        u8 doorType = this->doorType;

        if ((doorType != 0) && (doorType != 1) &&
            (((doorType != 7) && (doorType != 6)) || !func_808A0900(this, globalCtx))) {
            DoorShutter_SetupAction(this, func_808A1618);
        } else {
            DoorShutter_SetupAction(this, func_808A1090);
        }
        func_801A2ED8();
    }
}

void func_808A1884(DoorShutter* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s8 room = this->actor.room;
    Vec3f sp44;

    if (this->actor.room >= 0) {
        Actor_OffsetOfPointInActorCoords(&this->actor, &sp44, &player->actor.world.pos);

        this->actor.room = globalCtx->doorCtx.transitionActorList[DOORSHUTTER_GET_FC00(&this->actor)]
                               .sides[(sp44.z < 0.0f) ? 0 : 1]
                               .room;

        if (room != this->actor.room) {
            Room temp = globalCtx->roomCtx.currRoom;

            globalCtx->roomCtx.currRoom = globalCtx->roomCtx.prevRoom;
            globalCtx->roomCtx.prevRoom = temp;
            globalCtx->roomCtx.activeMemPage ^= 1;
        }
        func_8012EBF8(globalCtx, &globalCtx->roomCtx);
    }

    this->unk_15C = 0;
    this->actor.velocity.y = 0.0f;

    if (DoorShutter_SetupDoor(this, globalCtx) && !(player->stateFlags1 & 0x800)) {
        DoorShutter_SetupAction(this, func_808A1C50);
        if (ActorCutscene_GetCurrentIndex() == 0x7D) {
            s8 data = gSaveContext.respawn[RESTART_MODE_DOWN].data;

            func_801226E0(globalCtx, data);
            player->unk_A86 = -1;
            func_800B7298(globalCtx, NULL, 0x73);
        }
    }
}

s32 func_808A1A70(DoorShutter* this) {
    if (this->unk_163 == 7) {
        if (this->unk_163 == 7) {
            func_800B9010(&this->actor, NA_SE_EV_IKANA_DOOR_CLOSE - SFX_FLAG);
        }

        Math_StepToF(&this->actor.velocity.y, 5.0f, 0.5f);

        if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->actor.home.pos, this->actor.velocity.y) == 0.0f) {
            return true;
        }
    } else {
        if (this->actor.velocity.y < 20.0f) {
            Math_StepToF(&this->actor.velocity.y, 20.0f, 8.0f);
        }

        if (Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, this->actor.velocity.y)) {
            return true;
        }
    }
    return false;
}

void func_808A1B48(DoorShutter* this, GlobalContext* globalCtx) {
    s16 quake;

    if (func_808A1A70(this)) {
        if (this->actor.velocity.y > 20.0f) {
            this->actor.floorHeight = this->actor.home.pos.y;
            Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 45.0f, 10, 8.0f, 500, 10, 0);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BIGWALL_BOUND);
        quake = Quake_Add(Play_GetCamera(globalCtx, 0), 3);
        Quake_SetSpeed(quake, -32536);
        Quake_SetQuakeValues(quake, 2, 0, 0, 0);
        Quake_SetCountdown(quake, 10);
        func_8013ECE0(this->actor.xyzDistToPlayerSq, 180, 20, 100);
        func_808A1884(this, globalCtx);
    }
}

void func_808A1C50(DoorShutter* this, GlobalContext* globalCtx) {
    if (this->unk_167++ > 30) {
        if (GET_PLAYER(globalCtx)->csMode == 0x73) {
            func_800B7298(globalCtx, NULL, 6);
        }
        DoorShutter_SetupDoor(this, globalCtx);
    }
}

void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorShutter* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x100004C0) || (this->actionFunc == DoorShutter_SetupType)) {
        this->actionFunc(this, globalCtx);

        if (this->unk_163 == 7) {
            this->actor.home.rot.z = Math_Vec3f_DistXZ(&this->actor.home.pos, &this->actor.world.pos) * -100.0f;
        }
    }
}

s32 func_808A1D68(DoorShutter* this, GlobalContext* globalCtx) {
    s32 temp_a0;
    s32 temp_a1;

    if (Player_InCsMode(&globalCtx->state)) {
        return true;
    }

    temp_a0 = BINANG_SUB(Actor_YawToPoint(&this->actor, &globalCtx->view.eye), this->actor.shape.rot.y);
    temp_a1 = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    temp_a0 = ABS_ALT(temp_a0);
    temp_a1 = ABS_ALT(temp_a1);

    if (((temp_a1 < 0x4000) && (temp_a0 > 0x4000)) || ((temp_a1 > 0x4000) && (temp_a0 < 0x4000))) {
        return false;
    }
    return true;
}

void DoorShutter_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DoorShutter* this = THIS;
    ShutterInfo* sp44;

    if (func_808A1D68(this, globalCtx)) {
        sp44 = &D_808A21B0[this->unk_164];

        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        if (this->unk_164 == 7) {
            Matrix_InsertTranslation(0.0f, 64.96f, 0.0f, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->actor.home.rot.z, MTXMODE_APPLY);
            Matrix_InsertTranslation(0.0f, -64.96f, 0.0f, MTXMODE_APPLY);
        }

        if (sp44->unk_04 != 0) {
            TransitionActorEntry* transitionEntry =
                &globalCtx->doorCtx.transitionActorList[DOORSHUTTER_GET_FC00(&this->actor)];

            if ((globalCtx->roomCtx.prevRoom.num >= 0) ||
                (transitionEntry->sides[0].room == transitionEntry->sides[1].room)) {
                s16 yaw = this->actor.shape.rot.y - Math_Vec3f_Yaw(&globalCtx->view.eye, &this->actor.world.pos);

                if (ABS_ALT(yaw) < 0x4000) {
                    Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
                }
            } else if (this->actor.room == transitionEntry->sides[0].room) {
                Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
            }
        } else if (this->doorType == 5) {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_808A22DC[this->unk_15E]));
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, sp44->unk_00);

        if ((this->unk_168 != 0.0f) && (sp44->unk_04 != 0)) {
            Matrix_InsertTranslation(0.0f, sp44->unk_08 * (1.0f - this->unk_168), sp44->translateZ, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, sp44->unk_04);
        }

        if (this->unk_166 != 0) {
            Matrix_Scale(0.01f, 0.01f, 0.025f, MTXMODE_APPLY);
            Actor_DrawDoorLock(globalCtx, this->unk_166, (this->doorType == 5) ? DOORLOCK_BOSS : DOORLOCK_NORMAL);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
