/*
 * File: z_en_tsn.c
 * Overlay: ovl_En_Tsn
 * Description: Great Bay - Fisherman
 */

#include "z_en_tsn.h"
#include "objects/object_tsn/object_tsn.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnTsn*)thisx)

void EnTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE0010(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0304(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0418(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0460(EnTsn* this, GlobalContext* globalCtx);
void func_80AE04C4(EnTsn* this, GlobalContext* globalCtx);
void func_80AE04FC(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0704(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0C88(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0D10(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0D78(EnTsn* this, GlobalContext* globalCtx);
void func_80AE0F84(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Tsn_InitVars = {
    ACTOR_EN_TSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnTsn),
    (ActorFunc)EnTsn_Init,
    (ActorFunc)EnTsn_Destroy,
    (ActorFunc)EnTsn_Update,
    (ActorFunc)EnTsn_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

Vec3f D_80AE11BC = { 0.0f, 0.0f, 0.0f };

TexturePtr D_80AE11C8[] = { object_tsn_Tex_0073B8, object_tsn_Tex_0085B8 };

EnTsn* func_80ADFCA0(GlobalContext* globalCtx) {
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_TSN) && !ENTSN_GET_100(npc)) {
            return (EnTsn*)npc;
        }
        npc = npc->next;
    }

    return NULL;
}

void func_80ADFCEC(EnTsn* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80AE0C88;
    this->actor.update = func_80AE0F84;
    this->actor.destroy = NULL;
    this->actor.draw = NULL;
    this->actor.targetMode = 7;

    switch (ENTSN_GET_F(&this->actor)) {
        case ENTSN_F_0:
            if (gSaveContext.save.weekEventReg[26] & 8) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actor.textId = 0x106E;
            break;

        case ENTSN_F_1:
            if (gSaveContext.save.weekEventReg[26] & 4) {
                this->actor.textId = 0x1091;
            } else {
                this->actor.textId = 0x108A;
            }
            break;
    }

    if (gSaveContext.save.weekEventReg[55] & 0x80) {
        if ((ENTSN_GET_F(&this->actor)) == ENTSN_F_0) {
            this->actionFunc = func_80AE0D78;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    this->unk_1D8 = func_80ADFCA0(globalCtx);
    this->unk_220 = 0;

    if (this->unk_1D8 == NULL) {
        Actor_MarkForDeath(&this->actor);
    } else if ((ENTSN_GET_F(&this->actor)) == ENTSN_F_1) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
    }
}

void EnTsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTsn* this = THIS;

    if (ENTSN_GET_100(&this->actor)) {
        func_80ADFCEC(this, globalCtx);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_tsn_Skel_008AB8, &object_tsn_Anim_0092FC, NULL, NULL, 0);
    Animation_PlayLoop(&this->skelAnime, &object_tsn_Anim_0092FC);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_220 = 0;
    this->actionFunc = func_80AE0304;
    this->actor.textId = 0;
    this->actor.velocity.y = 0.0f;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    if (gSaveContext.save.weekEventReg[55] & 0x80) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnTsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTsn* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80ADFF84(EnTsn* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.save.weekEventReg[26] & 8) {
        textId = 0x107E;
    } else if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[25] & 0x80) {
            textId = 0x1083;
        } else {
            textId = 0x107F;
        }
    } else if (gSaveContext.save.weekEventReg[26] & 1) {
        textId = 0x1089;
    } else {
        textId = 0x1084;
    }

    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80AE0010(EnTsn* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.currentTextId) {
        case 0x107F:
        case 0x1080:
        case 0x1081:
        case 0x1082:
        case 0x1083:
        case 0x1084:
        case 0x1085:
        case 0x1086:
        case 0x1087:
        case 0x1088:
        case 0x1089:
        case 0x1093:
            Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, 0x64);
            this->actor.shape.rot.y = this->actor.world.rot.y;
            break;
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x107F:
            case 0x1081:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1080:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_001198, -10.0f);
                break;

            case 0x1082:
                Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                gSaveContext.save.weekEventReg[25] |= 0x80;
                func_801477B4(globalCtx);
                this->actionFunc = func_80AE0304;
                this->actor.textId = 0;
                break;

            case 0x1083:
                gSaveContext.save.weekEventReg[25] |= 0x80;
                func_801477B4(globalCtx);
                this->actionFunc = func_80AE0304;
                this->actor.textId = 0;
                break;

            case 0x1084:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_000964, -10.0f);
                break;

            case 0x1085:
            case 0x1086:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1089:
            case 0x1093:
                gSaveContext.save.weekEventReg[26] |= 1;
                func_801477B4(globalCtx);
                Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                this->actionFunc = func_80AE0304;
                this->actor.textId = 0;
                break;

            case 0x1087:
                Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_001198, -10.0f);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1088:
                gSaveContext.save.weekEventReg[26] |= 1;
                if (INV_CONTENT(ITEM_MASK_ZORA) == ITEM_MASK_ZORA) {
                    func_801477B4(globalCtx);
                    Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                    this->actionFunc = func_80AE0304;
                    this->actor.textId = 0;
                } else {
                    func_80151938(globalCtx, 0x1093);
                    Animation_MorphToLoop(&this->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                }
                break;

            case 0x107E:
                func_801477B4(globalCtx);
                this->actionFunc = func_80AE0304;
                this->actor.textId = 0;
                break;
        }
    }
}

void func_80AE0304(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80AE0010;
        this->unk_220 |= 1;
        if (this->actor.textId == 0) {
            func_80ADFF84(this, globalCtx);
        }
    } else if ((this->actor.xzDistToPlayer < 150.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 160.0f);
        this->unk_220 |= 1;
    } else {
        this->unk_220 &= ~1;
    }
    if (ENTSN_GET_Z(&this->actor)) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, 0x64);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.home.rot.y, 6, 0x1838, 0x64);
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80AE0418(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        Message_StartTextbox(globalCtx, 0x107D, NULL);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80AE0460(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        ENTSN_SET_Z(&this->unk_1D8->actor, false);
        this->actionFunc = func_80AE0418;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_95, 2000.0f, 1000.0f);
    }
}

void func_80AE04C4(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        this->actionFunc = func_80AE0C88;
    }
}

void func_80AE04FC(EnTsn* this, GlobalContext* globalCtx) {
    s32 sp24;
    Player* player = GET_PLAYER(globalCtx);

    if (Message_GetState(&globalCtx->msgCtx) == 0x10) {
        sp24 = func_80123810(globalCtx);
        if (sp24 != 0) {
            gSaveContext.save.weekEventReg[26] |= 2;
        }

        if (sp24 > 0) {
            func_801477B4(globalCtx);
            this->actionFunc = func_80AE0704;
            if (sp24 == 19) {
                if (CHECK_QUEST_ITEM(QUEST_UNK_19)) {
                    if (func_8013A4C4(1 | 8)) {
                        player->actor.textId = 0x107B;
                        return;
                    }

                    if (func_8013A4C4(1 | 2 | 8)) {
                        player->actor.textId = 0x10A9;
                        return;
                    }

                    player->actor.textId = 0x1078;
                    this->unk_220 |= 8;
                    return;
                }

                player->actor.textId = 0x1078;
                this->unk_220 |= 8;
                return;
            }

            if (sp24 == 13) {
                player->actor.textId = 0x1075;
                return;
            }

            player->actor.textId = 0x1078;
            this->unk_220 |= 8;
            return;
        }

        if (sp24 < 0) {
            func_80151938(globalCtx, 0x1078);
            Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_001198, -10.0f);
            this->actionFunc = func_80AE0704;
        }
    }
}

void func_80AE0698(EnTsn* this, GlobalContext* globalCtx) {
    func_801477B4(globalCtx);
    this->actionFunc = func_80AE0C88;
    this->unk_220 &= ~2;
    this->actor.focus.pos = this->actor.world.pos;
    ActorCutscene_Stop(this->actor.cutscene);
    ENTSN_SET_Z(&this->unk_1D8->actor, false);
}

void func_80AE0704(EnTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad[2];

    if ((this->unk_220 & 8) && (globalCtx->msgCtx.currentTextId == 0x1078)) {
        this->unk_220 &= ~8;
        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_001198, -10.0f);
    }

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 2:
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x106E:
                        if (gSaveContext.save.weekEventReg[25] & 0x40) {
                            func_80151938(globalCtx, 0x1074);
                        } else {
                            func_80151938(globalCtx, 0x106F);
                        }
                        this->unk_220 |= 2;
                        gSaveContext.save.weekEventReg[25] |= 0x40;
                        ENTSN_SET_Z(&this->unk_1D8->actor, true);
                        this->unk_220 |= 4;
                        break;

                    case 0x106F:
                    case 0x1070:
                    case 0x1071:
                    case 0x1072:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x1076:
                    case 0x1079:
                        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_000964, -10.0f);
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x107A:
                        func_80151938(globalCtx, 0x10A6);
                        break;

                    case 0x1075:
                    case 0x1078:
                        player->exchangeItemId = 0;
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                        break;

                    case 0x107C:
                        if (Interface_HasEmptyBottle()) {
                            gSaveContext.save.weekEventReg[26] |= 8;
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80AE0460;
                            func_80AE0460(this, globalCtx);
                            this->unk_220 &= ~2;
                            this->actor.focus.pos = this->actor.world.pos;
                            ActorCutscene_Stop(this->actor.cutscene);
                            this->actor.flags &= ~ACTOR_FLAG_100;
                            REMOVE_QUEST_ITEM(QUEST_UNK_19);
                        } else {
                            func_80151938(globalCtx, 0x10A8);
                        }
                        break;

                    case 0x1073:
                    case 0x1074:
                        func_80151938(globalCtx, 0xFF);
                        this->actionFunc = func_80AE04FC;
                        break;

                    case 0x107B:
                        player->exchangeItemId = 0;
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                        break;

                    case 0x1077:
                    case 0x10A6:
                    case 0x10A8:
                        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                        func_80AE0698(this, globalCtx);
                        this->actor.flags &= ~ACTOR_FLAG_100;
                        this->actionFunc = func_80AE04C4;
                        break;

                    case 0x108A:
                    case 0x1091:
                        gSaveContext.save.weekEventReg[26] |= 4;
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        this->unk_220 |= 2;
                        this->actor.textId = 0x1091;
                        break;

                    case 0x108B:
                    case 0x108C:
                    case 0x108D:
                    case 0x108E:
                    case 0x108F:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x1092:
                        if (gSaveContext.save.weekEventReg[26] & 8) {
                            func_80AE0698(this, globalCtx);
                        } else {
                            func_80151938(globalCtx, 0x10A7);
                            Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_000964, -10.0f);
                        }
                        break;

                    case 0x10A7:
                        Animation_MorphToLoop(&this->unk_1D8->skelAnime, &object_tsn_Anim_0092FC, -10.0f);
                        func_80AE0698(this, globalCtx);
                        break;

                    case 0x1090:
                        func_80AE0698(this, globalCtx);
                        break;

                    case 0x10A9:
                        func_80AE0698(this, globalCtx);
                        this->actor.flags &= ~ACTOR_FLAG_100;
                        this->actionFunc = func_80AE04C4;
                        break;
                }
            }
    }

    if (this->unk_220 & 2) {
        if (this->unk_1D8 != NULL) {
            Math_SmoothStepToF(&this->actor.focus.pos.x, this->unk_1D8->actor.focus.pos.x, 0.8f, 100.0f, 5.0f);
            Math_SmoothStepToF(&this->actor.focus.pos.y, this->unk_1D8->actor.focus.pos.y, 0.8f, 100.0f, 5.0f);
            Math_SmoothStepToF(&this->actor.focus.pos.z, this->unk_1D8->actor.focus.pos.z, 0.8f, 100.0f, 5.0f);
        }
    }

    if (this->unk_220 & 4) {
        if (this->actor.cutscene == -1) {
            this->unk_220 &= ~4;
        } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            this->unk_220 &= ~4;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_80AE0C88(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80AE0704;
        if ((this->actor.textId == 0x108A) || (this->actor.textId == 0x1091)) {
            this->unk_220 |= 4;
            ENTSN_SET_Z(&this->unk_1D8->actor, true);
        }
    } else if (this->actor.isTargeted) {
        func_800B8614(&this->actor, globalCtx, 1000.0f);
    }
}

void func_80AE0D10(EnTsn* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        this->actionFunc = func_80AE0D78;
        ActorCutscene_Stop(this->actor.cutscene);
    }
}

void func_80AE0D78(EnTsn* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80AE0D10;
        this->unk_220 |= 4;
    } else if (this->actor.isTargeted) {
        func_800B8614(&this->actor, globalCtx, 1000.0f);
    }
}

void EnTsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTsn* this = THIS;

    this->actionFunc(this, globalCtx);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 25.0f, 0.0f, 4);
    SkelAnime_Update(&this->skelAnime);

    if (this->unk_220 & 1) {
        func_800E9250(globalCtx, &this->actor, &this->unk_222, &this->unk_228, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_222.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_222.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_228.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_228.y, 0, 6, 0x1838, 0x64);
    }

    if (DECR(this->unk_230) == 0) {
        this->unk_230 = Rand_S16Offset(60, 60);
    }

    if ((this->unk_230 == 1) || (this->unk_230 == 3)) {
        this->unk_22E = 1;
    } else {
        this->unk_22E = 0;
    }
}

void func_80AE0F84(Actor* thisx, GlobalContext* globalCtx) {
    EnTsn* this = THIS;

    this->actionFunc(this, globalCtx);
}

s32 EnTsn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTsn* this = THIS;
    s16 shifted = this->unk_222.x >> 1;

    if (limbIndex == 15) {
        rot->x += this->unk_222.y;
        rot->z += shifted;
    }

    if (limbIndex == 8) {
        rot->x += this->unk_228.y;
        rot->z += shifted;
    }
    return false;
}

void EnTsn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTsn* this = THIS;
    Vec3f sp18 = D_80AE11BC;

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&sp18, &this->actor.focus.pos);
    }
}

void EnTsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTsn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C5B0(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AE11C8[this->unk_22E]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AE11C8[this->unk_22E]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnTsn_OverrideLimbDraw, EnTsn_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
