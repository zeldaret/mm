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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF4EC.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF950.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFF94.s")

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
