/*
 * File: z_en_mt_tag.c
 * Overlay: ovl_En_Mt_tag
 * Description: Controls the Goron Race minigame
 */

#include "z_en_mt_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnMttag*)thisx)

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx);

void func_809CF9A0(EnMttag* this, GlobalContext* globalCtx);
void func_809CFA00(EnMttag* this, GlobalContext* globalCtx);
void func_809CFA54(EnMttag* this, GlobalContext* globalCtx);
void func_809CFC38(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_FinishRace(EnMttag* this, GlobalContext* globalCtx);
void func_809CFE28(EnMttag* this, GlobalContext* globalCtx);
void func_809CFF94(EnMttag* this, GlobalContext* globalCtx);

const ActorInit En_Mt_tag_InitVars = {
    ACTOR_EN_MT_TAG,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMttag),
    (ActorFunc)EnMttag_Init,
    (ActorFunc)EnMttag_Destroy,
    (ActorFunc)EnMttag_Update,
    (ActorFunc)NULL,
};

static s32 D_809D01B0[] = {
    0, 0, 0, 0, 1, 9, 12, 16, 19, 22, 26, 29, 30, 32, 34, 36, 39, 42, 45,
};

static Vec3f D_809D01FC[] = {
    { -105.0, 1000.0, -240.0 },   { -1751.0, 1000.0, -240.0 },  { -3138.0, 1000.0, -74.0 },
    { -4617.0, 1000.0, 277.0 },   { -5060.0, 1000.0, 388.0 },   { -5412.0, 1000.0, 573.0 },
    { -5523.0, 1000.0, 1035.0 },  { -5393.0, 1000.0, 1405.0 },  { -5060.0, 1000.0, 1553.0 },
    { -3933.0, 1000.0, 1479.0 },  { -3212.0, 1000.0, 1461.0 },  { -2805.0, 1000.0, 1645.0 },
    { -2638.0, 1000.0, 2071.0 },  { -2823.0, 1000.0, 2422.0 },  { -3212.0, 1000.0, 2607.0 },
    { -3785.0, 1000.0, 2977.0 },  { -4321.0, 1000.0, 3501.0 },  { -4654.0, 1000.0, 4185.0 },
    { -4802.0, 1000.0, 4779.0 },  { -4672.0, 1000.0, 5426.0 },  { -4339.0, 1000.0, 6037.0 },
    { -3748.0, 1000.0, 6314.0 },  { -2749.0, 1000.0, 6478.0 },  { -2453.0, 1000.0, 6922.0 },
    { -2269.0, 1000.0, 7754.0 },  { -2453.0, 1000.0, 8309.0 },  { -3008.0, 1000.0, 8438.0 },
    { -3304.0, 1000.0, 8179.0 },  { -3600.0, 1000.0, 7606.0 },  { -3600.0, 1000.0, 6885.0 },
    { -3618.0, 1000.0, 4392.0 },  { -3600.0, 1000.0, 3855.0 },  { -3396.0, 1000.0, 3189.0 },
    { -3396.0, 1000.0, 2283.0 },  { -3600.0, 1000.0, 818.0 },   { -3803.0, 1000.0, -88.0 },
    { -4543.0, 1000.0, -2457.0 }, { -4543.0, 1000.0, -2938.0 }, { -4543.0, 1000.0, -3530.0 },
    { -4284.0, 1000.0, -4333.0 }, { -3581.0, 1000.0, -4795.0 }, { -2805.0, 1000.0, -4850.0 },
    { -1825.0, 1000.0, -4703.0 }, { -1326.0, 1000.0, -4166.0 }, { -1122.0, 1000.0, -3186.0 },
    { -1085.0, 1000.0, -2059.0 }, { -1067.0, 1000.0, -912.0 },
};

s32 func_809CF350(Vec3f* pos) {
    return Math3D_XZBoundCheck(-1261.0f, -901.0f, -1600.0f, -1520.0f, pos->x, pos->z);
}

s32 func_809CF394(Vec3f* pos) {
    if (!(gSaveContext.eventInf[1] & 1)) {
        if (Math3D_XZBoundCheck(-466.0f, -386.0f, -687.0f, 193.0f, pos->x, pos->z)) {
            return 1;
        }
    } else if (Math3D_XZBoundCheck(-1127.0f, -1007.0f, -867.0f, -787.0f, pos->x, pos->z)) {
        return 2;
    }
    return 0;
}

s32 func_809CF444(EnMttag* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;
    s32 i = 0;
    s32 ret;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_RG);
        if (actor != NULL) {
            this->raceGorons[i] = (EnRg*)actor;
            i++;
        } else if ((actor == NULL) || (actor->next == NULL)) {
            break;
        }
        actor = actor->next;
    } while (i < 4);

    if (i < 4) {
        ret = 0;
    } else {
        ret = 1;
    }

    return ret;
}

s32 func_809CF4EC(Actor* actor, GlobalContext* globalCtx, s32* arg1, f32* arg2, f32* arg3) {
    s32 phi_s2 = -1;
    s32 phi_s4 = 0;
    f32 phi_f20 = 0.0f;
    s32 temp_v0;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    s32 temp_s1;

    temp_v0 = SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    if ((temp_v0 < 4) || (temp_v0 >= 19)) {
        return -1;
    }

    temp_s1 = D_809D01B0[temp_v0];

    do {
        if ((Math3D_PointDistToLine2D(actor->world.pos.x, actor->world.pos.z, (&D_809D01FC[temp_s1])[-1].x,
                                      (&D_809D01FC[temp_s1])[-1].z, (&D_809D01FC[temp_s1])[1].x,
                                      (&D_809D01FC[temp_s1])[1].z, &sp74, &sp70, &sp6C) != 0) &&
            ((phi_s4 == 0) || ((phi_s2 + 1) == temp_s1) || (sp6C < phi_f20))) {
            phi_f20 = sp6C;
            phi_s2 = temp_s1;
            *arg2 = sp74;
            *arg3 = sp70;
            phi_s4 = 1;
        }
        temp_s1++;
    } while (temp_s1 < D_809D01B0[temp_v0 + 1]);

    *arg1 = phi_s2 + 1;
    return phi_s2;
}

s32 func_809CF67C(EnMttag* this, GlobalContext* globalCtx) {
    Player* player;
    EnRg* rg;
    s32 spA4[5];
    s32 sp90[5];
    f32 sp7C[5];
    f32 sp68[5];
    s32 phi_fp;
    s32 i;
    s32 ret;

    player = GET_PLAYER(globalCtx);
    ret = 0;
    phi_fp = -1;

    spA4[0] = func_809CF4EC(&player->actor, globalCtx, &sp90[0], &sp7C[0], &sp68[0]);
    for (i = 1; i < 5; i++) {
        spA4[i] = func_809CF4EC(&this->raceGorons[i - 1]->actor, globalCtx, &sp90[i], &sp7C[i], &sp68[i]);
        if (phi_fp < spA4[i]) {
            phi_fp = spA4[i];
        }
    }

    for (i = 1; i < 5; i++) {
        rg = this->raceGorons[i - 1];
        if ((sp90[i] != -1) && (sp90[0] != -1)) {
            rg->unk_348 = (sp90[i] - sp90[0]);
        } else {
            rg->unk_348 = 0;
        }
    }

    if ((spA4[0] > 0) && (spA4[0] < phi_fp) && (player->actor.bgCheckFlags & 1) && ((phi_fp - spA4[0]) >= 0x18)) {
        ret = 1;
    }
    return ret;
}

s32 EnMttag_ExitRace(GlobalContext* globalCtx, s32 arg1, s32 nextTransition) {
    CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
    globalCtx->nextEntranceIndex = 0xD020;
    if ((gSaveContext.weekEventReg[0x21] & 0x80)) {
        gSaveContext.nextCutsceneIndex = 0xFFF0;
    } else {
        gSaveContext.nextCutsceneIndex = 0;
    }
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = arg1;
    gSaveContext.nextTransition = nextTransition;
    func_801477B4(globalCtx);
    return 1;
}

void EnMttag_ShowFalseStartMessage(EnMttag* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3DD0[4] = 0;
    func_801518B0(globalCtx, 0xE95, NULL); // An entrant made a false start
    func_800B7298(globalCtx, &this->actor, 7);
    Audio_QueueSeqCmd(0x101400FF);
    this->actionFunc = func_809CFE28;
}

void EnMttag_ShowCantWinMessage(EnMttag* this, GlobalContext* globalCtx) {
    func_801518B0(globalCtx, 0xE97, NULL); // You can't win now...
    func_800B7298(globalCtx, &this->actor, 7);
    this->actionFunc = func_809CFF94;
}

void func_809CF9A0(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = func_809CFA00;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_809CFA00(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        gSaveContext.weekEventReg[0xC] |= 2;
        this->actionFunc = func_809CFA54;
    }
}

void func_809CFA54(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 temp_v0_2;

    if (this->unk_158 == 1) {
        temp_v0_2 = func_809CF394(&player->actor.world.pos);
        if (temp_v0_2 != 0) {
            if (temp_v0_2 == 1) {
                this->unk_164 = 1;
            } else {
                this->unk_164 = 0;
            }
            EnMttag_ShowFalseStartMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else {
            if (DECR(this->timer) == 60) {
                func_8010E9F0(4, 0);
                globalCtx->interfaceCtx.unk_280 = 1;
                Audio_QueueSeqCmd(NA_BGM_GORON_RACE | 0x8000);
                globalCtx->envCtx.unk_E4 = 0xFE;
                player->stateFlags1 &= ~0x20;
            } else if ((this->timer < 60) && (globalCtx->interfaceCtx.unk_280 == 8)) {
                this->timer = 0;
                gSaveContext.eventInf[1] |= 1;
                this->actionFunc = func_809CFC38;
            }
        }
    } else {
        if (func_809CF444(this, globalCtx)) {
            this->unk_158 = 1;
        }
    }
}

s32 func_809CFBC4(EnMttag* this) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((func_809CF350(&this->raceGorons[i]->actor.world.pos)) && (this->raceGorons[i]->actor.update != NULL)) {
            ret = 1;
            break;
        }
    }
    return ret;
}

void func_809CFC38(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* playerPos = &player->actor.world.pos;
    s32 temp_v0;

    if (func_809CF350(playerPos)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 2;
        this->actionFunc = EnMttag_FinishRace;
    } else if (func_809CFBC4(this)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 4;
        this->actionFunc = EnMttag_FinishRace;
    } else {
        temp_v0 = func_809CF394(playerPos);
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                this->unk_164 = 1;
            } else {
                this->unk_164 = 0;
            }
            EnMttag_ShowFalseStartMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else if ((func_809CF67C(this, globalCtx)) && (this->timer == 0)) {
            EnMttag_ShowCantWinMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        }
    }
}

void EnMttag_FinishRace(EnMttag* this, GlobalContext* globalCtx) {
    if (DECR(this->timer) == 0) {
        if ((gSaveContext.eventInf[1] & 2)) {
            // Player won
            EnMttag_ExitRace(globalCtx, 3, 3);
        } else {
            // A non-player Goron won
            EnMttag_ExitRace(globalCtx, 2, 2);
        }

        Actor_MarkForDeath(&this->actor);
    }
}

void func_809CFE28(EnMttag* this, GlobalContext* globalCtx) {
    u8 talkState;

    talkState = Message_GetState(&globalCtx->msgCtx);
    if (((talkState == 5 && func_80147624(globalCtx)) || talkState == 2)) {
        if (this->unk_164) {
            globalCtx->nextEntranceIndex = 0xD010;
            if ((gSaveContext.weekEventReg[0x21] & 0x80)) {
                gSaveContext.nextCutsceneIndex = 0xFFF0;
            } else {
                gSaveContext.nextCutsceneIndex = 0;
            }
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 2;
            gSaveContext.nextTransition = 2;
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 7);
            Parameter_AddMagic(globalCtx, ((void)0, gSaveContext.unk_3F30) + (gSaveContext.doubleMagic * 48) + 48);
            gSaveContext.eventInf[1] &= 0xFE;
            gSaveContext.eventInf[1] &= 0xFD;
            gSaveContext.eventInf[1] &= 0xFB;
            gSaveContext.eventInf[1] &= 0xF7;
            gSaveContext.eventInf[2] = ((gSaveContext.eventInf[2] & 0xF) + 1) | (gSaveContext.eventInf[2] & 0xF0);
        } else {
            EnMttag_ExitRace(globalCtx, 2, 2);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void func_809CFF94(EnMttag* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
        if (globalCtx->msgCtx.choiceIndex != 0) {
            func_8019F230();
            gSaveContext.unk_3DD0[4] = 0;
            EnMttag_ExitRace(globalCtx, 2, 2);
            gSaveContext.eventInf[1] &= 0xF7;
            gSaveContext.eventInf[1] |= 4;
            Actor_MarkForDeath(&this->actor);
        } else {
            func_8019F208();
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 6);
            gSaveContext.eventInf[1] &= 0xF7;
            this->timer = 100;
            this->actionFunc = func_809CFC38;
        }
    }
}

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx) {
    Player* player;
    EnMttag* this = THIS;

    if (gSaveContext.entranceIndex == 0xD010) {
        player = GET_PLAYER(globalCtx);
        player->stateFlags1 |= 0x20;
        this->unk_158 = 0;
        this->timer = 100;
        gSaveContext.eventInf[1] &= 0xFE;
        gSaveContext.eventInf[1] &= 0xFD;
        gSaveContext.eventInf[1] &= 0xFB;
        gSaveContext.eventInf[1] &= 0xF7;
        if (!(gSaveContext.weekEventReg[0xC] & 2)) {
            this->actionFunc = func_809CF9A0;
        } else {
            s32 requiredScopeTemp;

            this->actionFunc = func_809CFA54;
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMttag* this = THIS;
    if (gSaveContext.unk_3DD0[4] != 6) {
        gSaveContext.unk_3DD0[4] = 5;
    }
}

void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMttag* this = THIS;
    this->actionFunc(this, globalCtx);
}
