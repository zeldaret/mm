#include "global.h"

static s16 D_801BF550 = 0;

static s16 D_801BF554 = 0;

static s16 D_801BF558 = 0;

static s32 D_801BF55C[] = {
    SCENE_MITURIN,    SCENE_HAKUGIN,    SCENE_SEA,    SCENE_INISIE_N,  SCENE_INISIE_R,
    SCENE_MITURIN_BS, SCENE_HAKUGIN_BS, SCENE_SEA_BS, SCENE_INISIE_BS,
};

static s32 D_801BF580[] = {
    SCENE_MITURIN, SCENE_HAKUGIN, SCENE_SEA, SCENE_INISIE_N, SCENE_INISIE_R,
};

static s32 D_801BF594[] = {
    SCENE_MITURIN_BS,
    SCENE_HAKUGIN_BS,
    SCENE_SEA_BS,
    SCENE_INISIE_BS,
};

static s32 D_801BF5A4[] = {
    SCENE_22DEKUCITY,
    SCENE_KOEPONARACE,
    SCENE_F01,
};

static s16 D_801BF5B0 = 99;

s32 func_8010A000(PlayState* play) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == D_801BF55C[i]) {
            return i;
        }
    }

    return -1;
}

s32 func_8010A074(PlayState* play) {
    if (func_8010A000(play) == -1) {
        return 0;
    }

    return 1;
}

s32 func_8010A0A4(PlayState* play) {
    if ((func_8010A000(play) == -1) || (func_80102EF0(play) == 0)) {
        return 0;
    }

    return 1;
}

s32 func_8010A0F0(PlayState* play) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == D_801BF580[i]) {
            return i;
        }
    }

    return -1;
}

s32 func_8010A164(PlayState* play) {
    if (func_8010A0F0(play) == -1) {
        return 0;
    }

    return 1;
}

s32 func_8010A194(PlayState* play) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == D_801BF594[i]) {
            return i;
        }
    }

    return -1;
}

s32 func_8010A208(PlayState* play) {
    if (func_8010A194(play) == -1) {
        return 0;
    }

    return 1;
}

s32 func_8010A238(PlayState* play) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == D_801BF5A4[i]) {
            return i;
        }
    }

    return -1;
}

s32 func_8010A2AC(PlayState* play) {
    if (func_8010A238(play) == -1) {
        return 0;
    }

    return 1;
}

void func_8010A2DC(PlayState* play) {
    Player* player = GET_PLAYER(play);

    D_801BF550 = player->actor.world.pos.x;
    D_801BF554 = player->actor.world.pos.z;
    D_801BF558 = ((0x7FFF - player->actor.shape.rot.y) / 1024);
}

void func_8010A33C(PlayState* play, s16 param_2) {
    s32 mapIndex;
    InterfaceContext* interfaceCtx;

    mapIndex = gSaveContext.mapIndex;
    func_80105C40(param_2);
    if (param_2 >= 0) {
        if (func_8010A074(play) != 0) {
            interfaceCtx = &play->interfaceCtx;
            gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneNumber(play->sceneNum)].unk_18 |=
                gBitFlags[param_2];
            interfaceCtx->mapRoomNum = param_2;
            interfaceCtx->unk_27A = mapIndex;
        }
    } else {
        play->interfaceCtx.mapRoomNum = 0;
    }

    if (gSaveContext.sunsSongState != SUNSSONG_SPEED_TIME) {
        gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    }
}

void func_8010A410(void) {
    func_80105A40();
}

void func_8010A430(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 temp_v0;

    func_80105C40(play->roomCtx.currRoom.num);
    interfaceCtx->unk_278 = -1;
    interfaceCtx->unk_27A = -1;
    interfaceCtx->mapSegment = THA_AllocEndAlign16(&play->state.heap, 0x1000);
    if (func_8010A2AC(play) != 0) {
        gSaveContext.mapIndex = func_8010A238(play);
        return;
    }

    if (func_8010A074(play) != 0) {
        temp_v0 = func_8010A000(play);
        gSaveContext.mapIndex = temp_v0;
        switch (play->sceneNum) {
            case SCENE_MITURIN_BS:
                temp_v0 = 0;
                break;
            case SCENE_HAKUGIN_BS:
                temp_v0 = 1;
                break;
            case SCENE_SEA_BS:
                temp_v0 = 2;
                break;
            case SCENE_INISIE_BS:
                temp_v0 = 3;
                break;
        }

        gSaveContext.unk_48C8 = temp_v0;
        func_8010A33C(play, play->roomCtx.currRoom.num);
    }
}

void func_8010A54C(PlayState* play) {
    func_80106644(play, D_801BF550, D_801BF554, D_801BF558);
}

void func_8010A580(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    Input* controller = CONTROLLER1(&play->state);
    s32 pad1;
    s16 temp_v0_2;
    s32 pad2;

    if ((play->pauseCtx.state < 4) && (CHECK_BTN_ALL(controller->press.button, BTN_L)) && (!Play_InCsMode(play)) &&
        (!func_80106530(play))) {
        if (XREG(95) == 0) {
            play_sound(NA_SE_SY_CAMERA_ZOOM_UP);
        } else {
            play_sound(NA_SE_SY_CAMERA_ZOOM_DOWN);
        }

        XREG(95) ^= 1;
    }

    func_80105B34(play);

    if ((play->pauseCtx.state == 0) && (play->pauseCtx.debugState == 0)) {
        if (func_8010A164(play) != 0) {
            temp_v0_2 = func_80109124(player->actor.world.pos.y);
            if (temp_v0_2 != -1) {
                gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneNumber(play->sceneNum)].unk_14 |=
                    gBitFlags[4 - temp_v0_2];
                XREG(94) = 4 - temp_v0_2;
                if (interfaceCtx->mapRoomNum != D_801BF5B0) {
                    D_801BF5B0 = interfaceCtx->mapRoomNum;
                }
            }
        } else if (func_8010A208(play) != 0) {
            func_80105294();
            XREG(94) = 4 - func_80105318();
        }
    }
}
