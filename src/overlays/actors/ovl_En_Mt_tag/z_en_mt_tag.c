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
void func_809CFD98(EnMttag* this, GlobalContext* globalCtx);
void func_809CFE28(EnMttag* this, GlobalContext* globalCtx);
void func_809CFF94(EnMttag* this, GlobalContext* globalCtx);

#if 0
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

#endif

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
            this->unk_148[i] = actor;
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

extern s32 D_809D01B0[];
extern Vec3f D_809D01FC[];

#ifdef NON_MATCHING
// Stack is too big
s32 func_809CF4EC(Actor* actor, GlobalContext* globalCtx, s32* arg1, f32* arg2, f32* arg3) {
    s32 phi_s2 = -1;
    s32 phi_s4 = 0;
    f32 phi_f20 = 0.0f;
    Vec3f* phi_s0;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    s32 temp_s1;
    s32 temp_v0;

    temp_v0 = SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    if ((temp_v0 < 4) || (temp_v0 >= 19)) {
        return -1;
    }

    temp_s1 = D_809D01B0[temp_v0];

    do {
        phi_s0 = &D_809D01FC[temp_s1];
        if ((Math3D_PointDistToLine2D(actor->world.pos.x, actor->world.pos.z, phi_s0[-1].x, phi_s0[-1].z, phi_s0[1].x,
                                      phi_s0[1].z, &sp74, &sp70, &sp6C) != 0) &&
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF4EC.s")
#endif

s32 func_809CF67C(EnMttag* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF67C.s")

s32 func_809CF848(GlobalContext* globalCtx, s32 arg1, s32 arg2) {
    CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
    globalCtx->nextEntranceIndex = 0xD020;
    if ((gSaveContext.weekEventReg[0x21] & 0x80)) {
        gSaveContext.nextCutsceneIndex = 0xFFF0;
    } else {
        gSaveContext.nextCutsceneIndex = 0;
    }
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = arg1;
    gSaveContext.nextTransition = arg2;
    func_801477B4(globalCtx);
    return 1;
}

void func_809CF8EC(EnMttag* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3DD0[4] = 0;
    func_801518B0(globalCtx, 0xE95U, NULL);
    func_800B7298(globalCtx, &this->actor, 7);
    Audio_QueueSeqCmd(0x101400FF);
    this->actionFunc = func_809CFE28;
}

void func_809CF950(EnMttag* this, GlobalContext* globalCtx) {
    func_801518B0(globalCtx, 0xE97, NULL);
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
    s32 phi_v1;

    if (this->unk_158 == 1) {
        temp_v0_2 = func_809CF394(&player->actor.world.pos);
        if (temp_v0_2 != 0) {
            if (temp_v0_2 == 1) {
                this->unk_164 = 1;
            } else {
                this->unk_164 = 0;
            }
            func_809CF8EC(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else {
            if (this->unk_15A == 0) {
                phi_v1 = 0;
            } else {
                this->unk_15A--;
                phi_v1 = this->unk_15A;
            }
            if (phi_v1 == 0x3C) {
                func_8010E9F0(4, 0);
                globalCtx->interfaceCtx.unk_280 = 1;
                Audio_QueueSeqCmd(NA_BGM_GORON_RACE | 0x8000);
                globalCtx->envCtx.unk_E4 = 0xFE;
                player->stateFlags1 &= ~0x20;
            } else if ((this->unk_15A < 0x3C) && (globalCtx->interfaceCtx.unk_280 == 8)) {
                this->unk_15A = 0;
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
        if ((func_809CF350(&this->unk_148[i]->world.pos)) && (this->unk_148[i]->update != NULL)) {
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
        this->unk_15A = 0x37;
        gSaveContext.eventInf[1] |= 2;
        this->actionFunc = func_809CFD98;
    } else if (func_809CFBC4(this)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->unk_15A = 0x37;
        gSaveContext.eventInf[1] |= 4;
        this->actionFunc = func_809CFD98;
    } else {
        temp_v0 = func_809CF394(playerPos);
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                this->unk_164 = 1;
            } else {
                this->unk_164 = 0;
            }
            func_809CF8EC(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else if ((func_809CF67C(this, globalCtx)) && (this->unk_15A == 0)) {
            func_809CF950(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        }
    }
}

void func_809CFD98(EnMttag* this, GlobalContext* globalCtx) {
    s32 phi_v1;

    if (this->unk_15A == 0) {
        phi_v1 = 0;
    } else {
        this->unk_15A--;
        phi_v1 = this->unk_15A;
    }
    if (phi_v1 == 0) {
        if ((gSaveContext.eventInf[1] & 2)) {
            func_809CF848(globalCtx, 3, 3);
        } else {
            func_809CF848(globalCtx, 2, 2);
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
            func_809CF848(globalCtx, 2, 2);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void func_809CFF94(EnMttag* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
        if (globalCtx->msgCtx.choiceIndex != 0) {
            func_8019F230();
            gSaveContext.unk_3DD0[4] = 0;
            func_809CF848(globalCtx, 2, 2);
            gSaveContext.eventInf[1] &= 0xF7;
            gSaveContext.eventInf[1] |= 4;
            Actor_MarkForDeath(&this->actor);
        } else {
            func_8019F208();
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 6);
            gSaveContext.eventInf[1] &= 0xF7;
            this->unk_15A = 0x64;
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
        this->unk_15A = 0x64;
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
