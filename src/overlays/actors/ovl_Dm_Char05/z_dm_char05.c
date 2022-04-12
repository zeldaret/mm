/*
 * File: z_dm_char05.c
 * Overlay: ovl_Dm_Char05
 * Description: Cutscene mask objects
 */

#include "z_dm_char05.h"
#include "objects/object_dmask/object_dmask.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar05*)thisx)

void DmChar05_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AAC990(DmChar05* this, GlobalContext* globalCtx);
void func_80AAC9DC(DmChar05* this, GlobalContext* globalCtx);
void func_80AACA98(DmChar05* this, GlobalContext* globalCtx);
void func_80AACAE4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACBE4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACC48(DmChar05* this, GlobalContext* globalCtx);
void func_80AACC6C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACCD4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD0C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD1C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD68(DmChar05* this, GlobalContext* globalCtx);
void func_80AACE10(DmChar05* this, GlobalContext* globalCtx);
void func_80AACE5C(DmChar05* this, GlobalContext* globalCtx);
void func_80AADD9C(GlobalContext* globalCtx, DmChar05* this);
void func_80AADE78(GlobalContext* globalCtx, DmChar05* this);
void func_80AADF54(GlobalContext* globalCtx, DmChar05* this);
void func_80AAE030(GlobalContext* globalCtx, DmChar05* this);
void func_80AAE114(GlobalContext* globalCtx, DmChar05* this);

const ActorInit Dm_Char05_InitVars = {
    ACTOR_DM_CHAR05,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_DMASK,
    sizeof(DmChar05),
    (ActorFunc)DmChar05_Init,
    (ActorFunc)DmChar05_Destroy,
    (ActorFunc)DmChar05_Update,
    (ActorFunc)DmChar05_Draw,
};

static AnimationInfo sAnimations[] = {
    { &object_dmask_Anim_001090, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dmask_Anim_004288, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dmask_Anim_0001A8, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dmask_Anim_00017C, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dmask_Anim_0011A0, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dmask_Anim_0013A4, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
};

void func_80AAC5A0(SkelAnime* skelAnime, AnimationInfo* animation, u16 arg2) {
    f32 phi_f2;

    animation += arg2;

    if (animation->frameCount < 0.0f) {
        phi_f2 = Animation_GetLastFrame(animation->animation);
    } else {
        phi_f2 = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, phi_f2,
                     animation->mode, animation->morphFrames);
}

void func_80AAC63C(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dmask_Skel_010B0, NULL, NULL, NULL, 0);
    if (DMCHAR05_GET(&this->actor) == DMCHAR05_0) {
        func_80AAC5A0(&this->skelAnime, &sAnimations[0], 0);
    } else {
        func_80AAC5A0(&this->skelAnime, &sAnimations[1], 0);
    }
    this->actionFunc = func_80AACC48;
}

void func_80AAC6E4(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dmask_Skel_042B0, NULL, NULL, NULL, 0);
    func_80AAC5A0(&this->skelAnime, &sAnimations[1], 0);
    this->actionFunc = func_80AACC48;
}

void func_80AAC770(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dmask_Skel_001D0, NULL, NULL, NULL, 0);
    func_80AAC5A0(&this->skelAnime, &sAnimations[3], 0);
    this->actionFunc = func_80AACC48;
}

void func_80AAC7FC(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dmask_Skel_013D0, NULL, NULL, NULL, 0);
    func_80AAC5A0(&this->skelAnime, &sAnimations[4], 0);
    this->actionFunc = func_80AACC48;
}

void func_80AAC888(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    this->actionFunc = func_80AACA98;
}

void DmChar05_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    this->unk_18C = 0;
    this->unk_18E = 0;
    this->unk_19C = 0;
    this->unk_1A0 = 0;
    this->unk_1A4 = 0;
    this->unk_1A8 = 0;
    this->unk_1AC = 100;
    this->unk_1B0 = 1000;
    this->unk_1B4 = 0;

    switch (DMCHAR05_GET(&this->actor)) {
        case DMCHAR05_0:
            func_80AAC63C(thisx, globalCtx);
            break;

        case DMCHAR05_1:
            func_80AAC6E4(thisx, globalCtx);
            break;

        case DMCHAR05_2:
            func_80AAC770(thisx, globalCtx);
            break;

        case DMCHAR05_3:
            func_80AAC7FC(thisx, globalCtx);
            break;

        case DMCHAR05_4:
            func_80AAC888(thisx, globalCtx);
            break;

        case DMCHAR05_5:
        case DMCHAR05_6:
        case DMCHAR05_7:
        case DMCHAR05_8:
        case DMCHAR05_9:
        case DMCHAR05_10:
        case DMCHAR05_11:
        case DMCHAR05_12:
            this->actionFunc = func_80AACBE4;
            break;
    }
    Actor_SetScale(&this->actor, 0.01f);
}

void DmChar05_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AAC990(DmChar05* this, GlobalContext* globalCtx) {
    s32 objectIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_GOLONMASK);

    if (objectIdx >= 0) {
        this->unk_18F = objectIdx;
        this->actionFunc = func_80AAC9DC;
    }
}

void func_80AAC9DC(DmChar05* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 109) != 0) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 109);

        if (globalCtx->csCtx.actorActions[actionIndex]->action == 4) {
            this->unk_18E = 1;
            this->unk_190.x = globalCtx->csCtx.actorActions[actionIndex]->startPos.x;
            this->unk_190.y = globalCtx->csCtx.actorActions[actionIndex]->startPos.y;
            this->unk_190.z = globalCtx->csCtx.actorActions[actionIndex]->startPos.z;
        }
    }
}

void func_80AACA98(DmChar05* this, GlobalContext* globalCtx) {
    s32 objectIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_MASK13);

    if (objectIdx >= 0) {
        this->unk_18F = objectIdx;
        this->actionFunc = func_80AACAE4;
    }
}

void func_80AACAE4(DmChar05* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 564)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 564);

        if (globalCtx->csCtx.actorActions[actionIndex]->action == 2) {
            if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
                Item_Give(globalCtx, ITEM_MASK_COUPLE);
            }
            this->unk_18E = 1;
            this->unk_190.x = globalCtx->csCtx.actorActions[actionIndex]->startPos.x;
            this->unk_190.y = globalCtx->csCtx.actorActions[actionIndex]->startPos.y;
            this->unk_190.z = globalCtx->csCtx.actorActions[actionIndex]->startPos.z;
        } else {
            this->unk_18E = 0;
        }
    }
}

void func_80AACBE4(DmChar05* this, GlobalContext* globalCtx) {
    static s16 D_80AAE2F0[] = {
        OBJECT_GI_MASK17, OBJECT_GI_MASK14, OBJECT_GI_MASK10,     OBJECT_GI_MASK21,
        OBJECT_GI_MASK11, OBJECT_GI_MASK20, OBJECT_GI_RABIT_MASK, OBJECT_GI_MASK12,
    };
    s32 params = DMCHAR05_GET(&this->actor) - DMCHAR05_5;
    s32 objectIdx = Object_GetIndex(&globalCtx->objectCtx, D_80AAE2F0[params]);

    if (objectIdx >= 0) {
        this->unk_18F = objectIdx;
        this->actionFunc = func_80AACD0C;
    }
}

void func_80AACC48(DmChar05* this, GlobalContext* globalCtx) {
    if (this->unk_1B4 != 0) {
        this->actionFunc = func_80AACC6C;
    }
}

void func_80AACC6C(DmChar05* this, GlobalContext* globalCtx) {
    if (this->unk_19C < 247) {
        this->unk_19C += 8;
    }

    if (this->unk_1A0 < 247) {
        this->unk_1A0 += 8;
    }

    if (this->unk_1A4 < 247) {
        this->unk_1A4 += 8;
    } else {
        this->unk_19C = 255;
        this->unk_1A0 = 255;
        this->unk_1A4 = 255;
        this->actionFunc = func_80AACCD4;
    }
}

void func_80AACCD4(DmChar05* this, GlobalContext* globalCtx) {
    if (this->unk_1AC < 975) {
        this->unk_1AC += 25;
    } else {
        this->unk_1AC = 996;
        this->actionFunc = func_80AACD0C;
    }
}

void func_80AACD0C(DmChar05* this, GlobalContext* globalCtx) {
}

void func_80AACD1C(DmChar05* this, GlobalContext* globalCtx) {
    s32 objectIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_ZORAMASK);

    if (objectIdx >= 0) {
        this->unk_18F = objectIdx;
        this->actionFunc = func_80AACD68;
    }
}

void func_80AACD68(DmChar05* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 473)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 473);

        this->unk_18E = 1;
        this->unk_190.x = globalCtx->csCtx.actorActions[actionIndex]->startPos.x;
        this->unk_190.y = globalCtx->csCtx.actorActions[actionIndex]->startPos.y;
        this->unk_190.z = globalCtx->csCtx.actorActions[actionIndex]->startPos.z;
    }
}

void func_80AACE10(DmChar05* this, GlobalContext* globalCtx) {
    s32 objectIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_MASK15);

    if (objectIdx >= 0) {
        this->unk_18F = objectIdx;
        this->actionFunc = func_80AACE5C;
    }
}

void func_80AACE5C(DmChar05* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 518)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 518);

        this->unk_18E = 1;
        this->unk_190.x = globalCtx->csCtx.actorActions[actionIndex]->startPos.x;
        this->unk_190.y = globalCtx->csCtx.actorActions[actionIndex]->startPos.y;
        this->unk_190.z = globalCtx->csCtx.actorActions[actionIndex]->startPos.z;
    }
}

void func_80AACF04(DmChar05* this, GlobalContext* globalCtx) {
    u8 sp2F = true;
    s32 actionIndex;

    switch (DMCHAR05_GET(&this->actor)) {
        case DMCHAR05_0:
            if (Cutscene_CheckActorAction(globalCtx, 109)) {
                actionIndex = Cutscene_GetActorActionIndex(globalCtx, 109);

                if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
                    switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                        case 1:
                            sp2F = false;
                            break;

                        case 2:
                            this->unk_1B4 = 1;
                            break;

                        case 3:
                            this->unk_18C = 0;
                            break;

                        case 4:
                            Item_Give(globalCtx, ITEM_MASK_GORON);
                            sp2F = false;
                            this->actionFunc = func_80AAC990;
                            break;

                        case 5:
                            sp2F = false;
                            Actor_MarkForDeath(&this->actor);
                            break;

                        default:
                            sp2F = false;
                            break;
                    }

                    if (sp2F) {
                        func_80AAC5A0(&this->skelAnime, &sAnimations[this->unk_18C], 0);
                    }
                }

                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
            }
            break;

        case DMCHAR05_1:
            if (Cutscene_CheckActorAction(globalCtx, 473)) {
                actionIndex = Cutscene_GetActorActionIndex(globalCtx, 473);

                if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
                    switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                        case 1:
                            sp2F = false;
                            break;

                        case 2:
                            this->unk_18C = 1;
                            this->unk_1B4 = 1;
                            break;

                        case 3:
                            this->unk_18C = 1;
                            break;

                        case 4:
                            Item_Give(globalCtx, ITEM_MASK_ZORA);
                            sp2F = false;
                            this->actionFunc = func_80AACD1C;
                            break;

                        case 5:
                            sp2F = false;
                            Actor_MarkForDeath(&this->actor);
                            break;

                        default:
                            sp2F = false;
                            break;
                    }

                    if (sp2F) {
                        func_80AAC5A0(&this->skelAnime, &sAnimations[this->unk_18C], 0);
                    }
                }

                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
            }
            break;

        case DMCHAR05_2:
            if (Cutscene_CheckActorAction(globalCtx, 518)) {
                actionIndex = Cutscene_GetActorActionIndex(globalCtx, 518);

                if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
                    switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                        case 1:
                            sp2F = false;
                            break;

                        case 2:
                            this->unk_18C = 3;
                            break;

                        case 3:
                            this->unk_18C = 2;
                            break;

                        case 4:
                            Item_Give(globalCtx, ITEM_MASK_GIBDO);
                            sp2F = false;
                            this->actionFunc = func_80AACE10;
                            break;

                        case 5:
                            sp2F = false;
                            Actor_MarkForDeath(&this->actor);
                            break;

                        default:
                            sp2F = false;
                            break;
                    }

                    if (sp2F) {
                        func_80AAC5A0(&this->skelAnime, &sAnimations[this->unk_18C], 0);
                    }
                }

                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
            }
            break;

        case DMCHAR05_3:
            if (Cutscene_CheckActorAction(globalCtx, 559)) {
                actionIndex = Cutscene_GetActorActionIndex(globalCtx, 559);

                if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
                    switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                        default:
                            sp2F = false;
                            break;

                        case 1:
                            sp2F = false;
                            break;

                        case 2:
                            this->unk_18C = 4;
                            break;

                        case 3:
                            this->unk_18C = 5;
                            break;

                        case 4:
                            this->unk_18C = 5;
                            break;
                    }

                    if (sp2F) {
                        func_80AAC5A0(&this->skelAnime, &sAnimations[this->unk_18C], 0);
                    }
                }

                if (globalCtx->csCtx.actorActions[actionIndex]->action != 4) {
                    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
                } else {
                    Cutscene_ActorTranslate(&this->actor, globalCtx, actionIndex);
                }
            }

            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                if (this->unk_18C == 4) {
                    this->unk_18C++;
                    func_80AAC5A0(&this->skelAnime, &sAnimations[this->unk_18C], 0);
                }
            }
            break;
    }
}

void func_80AAD3F8(DmChar05* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 490) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER);
    }

    if (globalCtx->csCtx.frames > 550) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MASK_FLOAT - SFX_FLAG);
    }
}

void func_80AAD450(DmChar05* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 262) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER);
    }

    if (globalCtx->csCtx.frames > 318) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MASK_FLOAT - SFX_FLAG);
    }
}

void func_80AAD4A8(DmChar05* this, GlobalContext* globalCtx) {
    if (DMCHAR05_GET(&this->actor) == DMCHAR05_0) {
        if (Cutscene_CheckActorAction(globalCtx, 109) &&
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 109)]->action == 3)) {
            if (Animation_OnFrame(&this->skelAnime, 14.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_0);
            } else if (Animation_OnFrame(&this->skelAnime, 19.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_1);
            }
        }
    } else if (DMCHAR05_GET(&this->actor) == DMCHAR05_1) {
        if (Cutscene_CheckActorAction(globalCtx, 473)) {
            if ((globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 473)]->action == 3) &&
                Animation_OnFrame(&this->skelAnime, 5.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_SAND);
            }
        }
    } else if (DMCHAR05_GET(&this->actor) == DMCHAR05_2) {
        if (Cutscene_CheckActorAction(globalCtx, 518) &&
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 518)]->action == 2)) {
            if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_0);
            }

            if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_1);
            }

            if (Animation_OnFrame(&this->skelAnime, 18.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_MASK_BOUND_1);
            }
        }
    } else if (DMCHAR05_GET(&this->actor) == DMCHAR05_3) {
        if (globalCtx->sceneNum == SCENE_OKUJOU) {
            if (gSaveContext.sceneSetupIndex == 2) {
                if (globalCtx->csCtx.currentCsIndex == 0) {
                    func_80AAD3F8(this, globalCtx);
                } else if (globalCtx->csCtx.currentCsIndex == 1) {
                    func_80AAD450(this, globalCtx);
                }
            }
        } else if (globalCtx->sceneNum == SCENE_SPOT00) {
            if (gSaveContext.sceneSetupIndex == 9) {
                if ((globalCtx->csCtx.currentCsIndex == 0) && (globalCtx->csCtx.frames == 255)) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER);
                }
            } else if ((gSaveContext.sceneSetupIndex == 0xB) && (globalCtx->csCtx.frames == 115)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER_PREDEMO);
            }
        }
    }
}

void DmChar05_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    func_80AACF04(this, globalCtx);
    if (Cutscene_CheckActorAction(globalCtx, 109)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 109)]->action == 3) {
            SkelAnime_Update(&this->skelAnime);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, 473)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 473)]->action == 3) {
            SkelAnime_Update(&this->skelAnime);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, 518)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 518)]->action == 2) {
            SkelAnime_Update(&this->skelAnime);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, 559)) {
        if ((globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 559)]->action == 2) ||
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 559)]->action == 3)) {
            SkelAnime_Update(&this->skelAnime);
        }

        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 559)]->action == 4) {
            this->actor.world.rot.y += 0x258;
            this->actor.shape.rot.y += 0x258;
        }
    }
    this->actionFunc(this, globalCtx);
    func_80AAD4A8(this, globalCtx);
}

s32 DmChar05_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    return false;
}

void DmChar05_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void func_80AAD998(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;
    s32 pad[2];

    if (this->unk_18E == 0) {
        if (Cutscene_CheckActorAction(globalCtx, 109) &&
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 109)]->action != 1)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C28C(globalCtx->state.gfxCtx);
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, this->unk_19C, this->unk_1A0, this->unk_1A4, this->unk_1A8,
                                       this->unk_1AC, this->unk_1B0);
            SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              DmChar05_OverrideLimbDraw, DmChar05_PostLimbDraw, &this->actor);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    } else if (this->unk_18E == 1) {
        func_80AADD9C(globalCtx, this);
    }
}

void func_80AADA90(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    if (this->unk_18E == 0) {
        if (Cutscene_CheckActorAction(globalCtx, 473) &&
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 473)]->action != 1)) {
            func_8012C28C(globalCtx->state.gfxCtx);
            SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              DmChar05_OverrideLimbDraw, DmChar05_PostLimbDraw, &this->actor);
        }
    } else if (this->unk_18E == 1) {
        func_80AADE78(globalCtx, this);
    }
}

void func_80AADB4C(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    if (this->unk_18E == 0) {
        if (Cutscene_CheckActorAction(globalCtx, 518) &&
            (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 518)]->action != 1)) {
            func_8012C28C(globalCtx->state.gfxCtx);
            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, NULL, NULL, &this->actor);
        }
    } else if (this->unk_18E == 1) {
        func_80AADF54(globalCtx, this);
    }
}

void func_80AADC00(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmChar05* this = THIS;
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 559)) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 559);

        if ((globalCtx->csCtx.actorActions[actionIndex]->action != 1) &&
            (globalCtx->csCtx.actorActions[actionIndex]->action != 4)) {
            func_8012C28C(globalCtx->state.gfxCtx);
            SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              DmChar05_OverrideLimbDraw, DmChar05_PostLimbDraw, &this->actor);
        }

        if (globalCtx->csCtx.actorActions[actionIndex]->action == 4) {
            Matrix_InsertTranslation(-600.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Gfx_DrawDListOpa(globalCtx, object_dmask_DL_001E70);
        }
    }
}

void DmChar05_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmChar05* this = THIS;

    switch (DMCHAR05_GET(&this->actor)) {
        case DMCHAR05_0:
            func_80AAD998(thisx, globalCtx);
            break;

        case DMCHAR05_1:
            func_80AADA90(thisx, globalCtx);
            break;

        case DMCHAR05_2:
            func_80AADB4C(thisx, globalCtx);
            break;

        case DMCHAR05_3:
            func_80AADC00(thisx, globalCtx);
            break;

        case DMCHAR05_4:
            func_80AAE030(globalCtx, this);
            break;

        case DMCHAR05_5:
        case DMCHAR05_6:
        case DMCHAR05_7:
        case DMCHAR05_8:
        case DMCHAR05_9:
        case DMCHAR05_10:
        case DMCHAR05_11:
        case DMCHAR05_12:
            func_80AAE114(globalCtx, this);
            break;
    }
}

void func_80AADD9C(GlobalContext* globalCtx, DmChar05* this) {
    if (this->actor.objBankIndex == this->unk_18F) {
        Matrix_InsertTranslation(this->unk_190.x, this->unk_190.y, this->unk_190.z, MTXMODE_NEW);
        Matrix_InsertRotation(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
        Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
        GetItem_Draw(globalCtx, GID_44);
    }

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_18F)) {
        this->actor.objBankIndex = this->unk_18F;
    }
}

void func_80AADE78(GlobalContext* globalCtx, DmChar05* this) {
    if (this->actor.objBankIndex == this->unk_18F) {
        Matrix_InsertTranslation(this->unk_190.x, this->unk_190.y, this->unk_190.z, MTXMODE_NEW);
        Matrix_InsertRotation(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
        Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
        GetItem_Draw(globalCtx, GID_45);
    }

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_18F)) {
        this->actor.objBankIndex = this->unk_18F;
    }
}

void func_80AADF54(GlobalContext* globalCtx, DmChar05* this) {
    if (this->actor.objBankIndex == this->unk_18F) {
        Matrix_InsertTranslation(this->unk_190.x, this->unk_190.y, this->unk_190.z, MTXMODE_NEW);
        Matrix_InsertRotation(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
        Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
        GetItem_Draw(globalCtx, GID_6B);
    }

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_18F)) {
        this->actor.objBankIndex = this->unk_18F;
    }
}

void func_80AAE030(GlobalContext* globalCtx, DmChar05* this) {
    if (this->unk_18E != 0) {
        if (this->actor.objBankIndex == this->unk_18F) {
            Matrix_InsertTranslation(this->unk_190.x, this->unk_190.y, this->unk_190.z, MTXMODE_NEW);
            Matrix_InsertRotation(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
            Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
            GetItem_Draw(globalCtx, GID_03);
        }

        if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_18F)) {
            this->actor.objBankIndex = this->unk_18F;
        }
    }
}

void func_80AAE114(GlobalContext* globalCtx, DmChar05* this) {
    s32 sp34;
    s16 sp24[] = {
        GID_02, GID_6A, GID_70, GID_3A, GID_0E, GID_0F, GID_3E, GID_71,
    };

    sp34 = DMCHAR05_GET(&this->actor) - DMCHAR05_5;
    if (this->actor.objBankIndex == this->unk_18F) {
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_InsertRotation(0, globalCtx->gameplayFrames * 1000, 0, MTXMODE_APPLY);
        Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
        GetItem_Draw(globalCtx, sp24[sp34]);
    }

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_18F)) {
        this->actor.objBankIndex = this->unk_18F;
    }
}
