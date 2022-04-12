/*
 * File: z_en_kendo_js.c
 * Overlay: ovl_En_Kendo_Js
 * Description: Swordsman
 */

#include "z_en_kendo_js.h"
#include "overlays/actors/ovl_En_Maruta/z_en_maruta.h"
#include "objects/object_js/object_js.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000)

#define THIS ((EnKendoJs*)thisx)

void EnKendoJs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B26538(EnKendoJs* this);
void func_80B2654C(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B26AE8(EnKendoJs* this);
void func_80B26AFC(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B2701C(EnKendoJs* this);
void func_80B27030(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B2714C(EnKendoJs* this);
void func_80B27188(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B273D0(EnKendoJs* this);
void func_80B2740C(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B274BC(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B276C4(EnKendoJs* this);
void func_80B276D8(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B27760(EnKendoJs* this);
void func_80B27774(EnKendoJs* this, GlobalContext* globalCtx);
void func_80B2783C(EnKendoJs* this, GlobalContext* globalCtx);
s32 func_80B278C4(GlobalContext* globalCtx, Vec3f arg1);
void func_80B279F0(EnKendoJs* this, GlobalContext* globalCtx, s32 arg2);
void func_80B27A90(EnKendoJs* this, GlobalContext* globalCtx);

const ActorInit En_Kendo_Js_InitVars = {
    ACTOR_EN_KENDO_JS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JS,
    sizeof(EnKendoJs),
    (ActorFunc)EnKendoJs_Init,
    (ActorFunc)EnKendoJs_Destroy,
    (ActorFunc)EnKendoJs_Update,
    (ActorFunc)EnKendoJs_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 30, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfo sAnimations[] = {
    { &object_js_Anim_000C7C, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &object_js_Anim_000F4C, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &object_js_Anim_00016C, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &object_js_Anim_0003DC, 1.0f, 0.0f, 0.0f, 2, -8.0f },
    { &object_js_Anim_000AD4, 1.0f, 0.0f, 0.0f, 0, -8.0f },
};

s16 D_80B27CE0[][3] = {
    { 0x2731, 0x2732, 0x2733 },
    { 0x2734, 0x2735, 0x2736 },
    { 0x2737, 0x2738, 0x2739 },
};

s16 D_80B27CF4[][3] = {
    { 0x2710, 0x2712, 0x2714 },
    { 0x2711, 0x2713, 0x2715 },
};

s16 D_80B27D00[] = {
    0x271C, 0x271E, 0x2720, 0x2722, 0x2724, 0x2726, 0x2728,
};

s16 D_80B27D10[] = {
    0x271B, 0x271D, 0x271F, 0x2721, 0x2723, 0x2725, 0x2727,
};

void EnKendoJs_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnKendoJs* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_js_Skel_006990, &object_js_Anim_000F4C, this->jointTable,
                       this->morphTable, 13);

    if ((CURRENT_DAY == 3) &&
        !((gSaveContext.save.time <= CLOCK_TIME(23, 0)) && (gSaveContext.save.time >= CLOCK_TIME(6, 0)))) {
        if (ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_KANBAN, this->actor.home.pos.x,
                        this->actor.home.pos.y, this->actor.home.pos.z - 10.0f, this->actor.home.rot.x,
                        this->actor.home.rot.y, this->actor.home.rot.z, 0x10);
            Actor_MarkForDeath(&this->actor);
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
        }
    } else if (ENKENDOJS_GET_FF(&this->actor) == ENKENDOJS_FF_1) {
        Actor_MarkForDeath(&this->actor);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) {
        Path* path = &globalCtx->setupPathList[ENKENDOJS_GET_FF00(&this->actor)];

        this->unk_274 = Lib_SegmentedToVirtual(path->points);
    }

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    this->actor.child = NULL;
    this->unk_28A = 0;
    this->unk_28C = 0;
    this->unk_28E = 0;
    this->unk_286 = 0;
    func_80B26538(this);
}

void EnKendoJs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKendoJs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    gSaveContext.save.weekEventReg[82] &= (u8)~8;
}

void func_80B26538(EnKendoJs* this) {
    this->actionFunc = func_80B2654C;
}

void func_80B2654C(EnKendoJs* this, GlobalContext* globalCtx) {
    s32 phi_v0;
    s32 sp30;

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
        if (CURRENT_DAY != 0) {
            sp30 = CURRENT_DAY - 1;
        } else {
            sp30 = 0;
        }

        if (ENKENDOJS_GET_FF(&this->actor) == ENKENDOJS_FF_1) {
            Message_StartTextbox(globalCtx, 0x273C, &this->actor);
            this->unk_288 = 0x273C;
        } else if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
            switch (gSaveContext.save.playerForm) {
                case PLAYER_FORM_DEKU:
                    phi_v0 = 0;
                    break;

                case PLAYER_FORM_GORON:
                    phi_v0 = 1;
                    break;

                case PLAYER_FORM_ZORA:
                    phi_v0 = 2;
                    break;

                default:
                    phi_v0 = 0;
                    break;
            }

            Message_StartTextbox(globalCtx, D_80B27CE0[phi_v0][sp30], &this->actor);
            this->unk_288 = D_80B27CE0[phi_v0][sp30];
        } else if ((Player_GetMask(globalCtx) != PLAYER_MASK_NONE) && (Player_GetMask(globalCtx) < PLAYER_MASK_GIANT)) {
            u16 sp2E = Player_GetMask(globalCtx) + 0x273C;

            if (0) {}

            Message_StartTextbox(globalCtx, sp2E, &this->actor);
            this->unk_288 = sp2E;
        } else {
            if (this->unk_28A == 0) {
                this->unk_28A = 1;
                phi_v0 = 0;
            } else {
                phi_v0 = 1;
            }
            Message_StartTextbox(globalCtx, D_80B27CF4[phi_v0][sp30], &this->actor);
            this->unk_288 = D_80B27CF4[phi_v0][sp30];
        }

        func_80B26AE8(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80B26758(EnKendoJs* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx) && (this->unk_288 == 0x2716)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                if (GET_CUR_EQUIP_VALUE(EQUIP_SWORD) == EQUIP_SWORD) {
                    play_sound(NA_SE_SY_ERROR);
                    Message_StartTextbox(globalCtx, 0x272C, &this->actor);
                    this->unk_288 = 0x272C;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                } else if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
                    play_sound(NA_SE_SY_ERROR);
                    Message_StartTextbox(globalCtx, 0x2718, &this->actor);
                    this->unk_288 = 0x2718;
                } else {
                    func_8019F208();
                    func_801159EC(-globalCtx->msgCtx.unk1206C);
                    Message_StartTextbox(globalCtx, 0x2719, &this->actor);
                    this->unk_288 = 0x2719;
                }
                break;

            case 1:
                if (GET_CUR_EQUIP_VALUE(EQUIP_SWORD) == EQUIP_SWORD) {
                    play_sound(NA_SE_SY_ERROR);
                    Message_StartTextbox(globalCtx, 0x272C, &this->actor);
                    this->unk_288 = 0x272C;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                } else if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk12070) {
                    play_sound(NA_SE_SY_ERROR);
                    Message_StartTextbox(globalCtx, 0x2718, &this->actor);
                    this->unk_288 = 0x2718;
                } else {
                    func_8019F208();
                    func_801159EC(-globalCtx->msgCtx.unk12070);
                    Message_StartTextbox(globalCtx, 0x273A, &this->actor);
                    this->unk_288 = 0x273A;
                }
                break;

            case 2:
                func_8019F230();
                Message_StartTextbox(globalCtx, 0x2717, &this->actor);
                this->unk_288 = 0x2717;
        }
    }
}

void func_80B269A4(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!Message_ShouldAdvance(globalCtx)) {
        return;
    }

    switch (this->unk_288) {
        case 0x2710:
        case 0x2711:
        case 0x2712:
        case 0x2713:
        case 0x2714:
        case 0x2715:
            Message_StartTextbox(globalCtx, 0x2716, &this->actor);
            this->unk_288 = 0x2716;
            break;

        case 0x2719:
            func_801477B4(globalCtx);
            player->stateFlags1 |= 0x20;
            func_80B2701C(this);
            break;

        case 0x271A:
            func_801477B4(globalCtx);
            func_80B2714C(this);
            break;

        case 0x273A:
            Message_StartTextbox(globalCtx, 0x273B, &this->actor);
            this->unk_288 = 0x273B;
            break;

        case 0x273B:
            func_801477B4(globalCtx);
            func_80112AFC(globalCtx);
            player->stateFlags1 |= 0x20;
            func_80B273D0(this);
            break;

        case 0x272D:
            func_801477B4(globalCtx);
            gSaveContext.minigameState = 3;
            func_80B276C4(this);
            func_80B276D8(this, globalCtx);
            break;
    }
}

void func_80B26AE8(EnKendoJs* this) {
    this->actionFunc = func_80B26AFC;
}

void func_80B26AFC(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 4:
            func_80B26758(this, globalCtx);
            break;

        case 5:
            func_80B269A4(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                if (this->unk_288 == 0x272C) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                }

                if ((this->unk_288 == 0x272E) || (this->unk_288 == 0x272F) || (this->unk_288 == 0x2730)) {
                    gSaveContext.minigameState = 3;
                }

                player->stateFlags1 &= ~0x20;
                func_80B26538(this);
            }

        case 0:
        case 1:
        case 2:
        case 3:
            break;
    }
}

s32 func_80B26BF8(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (this->unk_284) {
        case 0:
            if (func_80122FCC(globalCtx)) {
                return 0;
            }

            if ((player->swordState != 0) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                return 1;
            }
            break;

        case 1:
            if ((player->stateFlags3 & 0x8000000)) {
                return 0;
            }

            if ((player->swordState != 0) || (player->stateFlags2 & 0x80000)) {
                return 1;
            }
            break;

        case 2:
            if (func_80122F9C(globalCtx)) {
                return 0;
            }

            if ((player->swordState != 0) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                return 1;
            }
            this->unk_28E = 0;
            break;

        case 3:
            if ((this->unk_28E == 1) && ((player->swordAnimation == 4) || (player->swordAnimation == 6))) {
                this->unk_28E = 0;
                return 0;
            }

            if ((this->unk_28E == 1) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                this->unk_28E = 0;
                return 1;
            }
            break;

        case 4:
            if ((this->unk_28E == 1) && ((player->swordAnimation == 0) || (player->swordAnimation == 2))) {
                this->unk_28E = 0;
                return 0;
            }

            if ((this->unk_28E == 1) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                this->unk_28E = 0;
                return 1;
            }
            break;

        case 5:
            if ((this->unk_28E == 1) && (player->swordAnimation == 12)) {
                this->unk_28E = 0;
                return 0;
            }

            if ((this->unk_28E == 1) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                this->unk_28E = 0;
                return 1;
            }
            break;

        case 6:
            if ((this->unk_28E == 1) && ((player->swordAnimation == 17) || (player->swordAnimation == 20))) {
                this->unk_28E = 0;
                return 0;
            }

            if ((this->unk_28E == 1) || (player->stateFlags3 & 0x8000000) || (player->stateFlags2 & 0x80000)) {
                this->unk_28E = 0;
                return 1;
            }
            break;
    }
    return 2;
}

void func_80B26EB4(EnKendoJs* this, GlobalContext* globalCtx) {
    Message_StartTextbox(globalCtx, D_80B27D00[this->unk_284], &this->actor);
    this->unk_288 = D_80B27D00[this->unk_284];
    this->unk_284++;
}

void func_80B26F14(EnKendoJs* this, GlobalContext* globalCtx) {
    Message_StartTextbox(globalCtx, D_80B27D10[this->unk_284], &this->actor);
    this->unk_288 = D_80B27D10[this->unk_284];
}

s32 func_80B26F6C(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (this->unk_288) {
        case 0x271D:
            if (func_80124190(player)) {
                Message_StartTextbox(globalCtx, 0x272A, &this->actor);
                this->unk_288 = 0x272A;
                return true;
            }
            break;

        case 0x2721:
            if (this->unk_292 != 0) {
                Message_StartTextbox(globalCtx, 0x272B, &this->actor);
                this->unk_288 = 0x272B;
                return true;
            }
            break;
    }
    return false;
}

void func_80B2701C(EnKendoJs* this) {
    this->actionFunc = func_80B27030;
}

void func_80B27030(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp20 = this->actor.world.pos;

    sp20.z += 200.0f;

    if (func_80B278C4(globalCtx, sp20)) {
        this->actor.flags |= ACTOR_FLAG_10000;
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            player->stateFlags1 &= ~0x20;
            func_80B279F0(this, globalCtx, 0);
            Message_StartTextbox(globalCtx, 0x271A, &this->actor);
            this->unk_288 = 0x271A;
            func_80B26AE8(this);
        } else {
            func_800B8614(&this->actor, globalCtx, 800.0f);
        }
    }
}

void func_80B2714C(EnKendoJs* this) {
    gSaveContext.save.weekEventReg[82] |= 8;
    this->unk_28C = 1;
    this->unk_290 = 0;
    this->unk_284 = 0;
    this->unk_286 = 1;
    this->actionFunc = func_80B27188;
}

void func_80B27188(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_288 == 0x2729) {
            func_80B26F14(this, globalCtx);
        } else if (!func_80B26F6C(this, globalCtx)) {
            if (this->skelAnime.animation == &object_js_Anim_00016C) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            }
            this->unk_286 = 2;
            func_801477B4(globalCtx);
            player->stateFlags1 &= ~0x20;
        }
    } else if (this->unk_286 == 2) {
        this->unk_286 = 1;
    }

    if (this->unk_286 == 1) {
        switch (func_80B26BF8(this, globalCtx)) {
            case 0:
                this->unk_286 = 0;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
                player->stateFlags1 |= 0x20;
                func_80B26EB4(this, globalCtx);
                break;

            case 1:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_ERROR);
                this->unk_286 = 0;
                player->stateFlags1 |= 0x20;
                Message_StartTextbox(globalCtx, 0x2729, &this->actor);
                this->unk_288 = 0x2729;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                break;

            default:
                if (this->unk_28C == 0) {
                    this->unk_290++;
                    if (this->unk_290 == 30) {
                        this->unk_290 = 0;
                        func_80B279F0(this, globalCtx, 0);
                    }
                }
                break;
        }

        if ((this->skelAnime.animation == &object_js_Anim_0003DC) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
        }

        if (this->unk_284 == 7) {
            gSaveContext.save.weekEventReg[82] &= (u8)~8;
            func_80B26AE8(this);
        }
    }
}

void func_80B273D0(EnKendoJs* this) {
    gSaveContext.save.weekEventReg[82] |= 8;
    this->unk_290 = 120;
    this->unk_284 = 0;
    this->unk_286 = 1;
    this->actionFunc = func_80B2740C;
}

void func_80B2740C(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp18 = this->actor.world.pos;

    sp18.z += 300.0f;

    if (func_80B278C4(globalCtx, sp18)) {
        this->unk_28C = 0;
        player->stateFlags1 &= ~0x20;
        this->actionFunc = func_80B274BC;
    }
}

void func_80B274BC(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_290 >= 140) {
        if (this->unk_284 == 5) {
            if (gSaveContext.minigameScore == 30) {
                Message_StartTextbox(globalCtx, 0x272D, &this->actor);
                this->unk_288 = 0x272D;
            } else {
                Message_StartTextbox(globalCtx, 0x272E, &this->actor);
                this->unk_288 = 0x272E;
            }
            player->stateFlags1 |= 0x20;
            gSaveContext.save.weekEventReg[82] &= (u8)~8;
            func_80B26AE8(this);
            return;
        }

        play_sound(NA_SE_SY_FOUND);
        func_80B279F0(this, globalCtx, ((Rand_Next() & 0xFF) % 3) + 1);
        func_80B279F0(this, globalCtx, ((Rand_Next() & 0xFF) % 3) + 4);
        this->unk_290 = 0;
        this->unk_284++;
    } else if (this->unk_290 == 120) {
        func_80B27A90(this, globalCtx);
        this->unk_290++;
    } else {
        this->unk_290++;
    }

    if (this->unk_28E == 1) {
        if ((player->swordAnimation == 17) || (player->swordAnimation == 20)) {
            globalCtx->interfaceCtx.unk_25C = 3;
            if (gSaveContext.minigameScore >= 27) {
                player->stateFlags1 |= 0x20;
            }
        } else if (player->swordAnimation == 12) {
            globalCtx->interfaceCtx.unk_25C = 2;
        } else {
            globalCtx->interfaceCtx.unk_25C = 1;
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
        this->unk_28E = 0;
    }
    func_80B2783C(this, globalCtx);
}

void func_80B276C4(EnKendoJs* this) {
    this->actionFunc = func_80B276D8;
}

void func_80B276D8(EnKendoJs* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80B27760(this);
    } else if (!(gSaveContext.save.weekEventReg[63] & 0x20)) {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 800.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_RED, 800.0f, 100.0f);
    }
}

void func_80B27760(EnKendoJs* this) {
    this->actionFunc = func_80B27774;
}

void func_80B27774(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (!(gSaveContext.save.weekEventReg[63] & 0x20)) {
            gSaveContext.save.weekEventReg[63] |= 0x20;
            Message_StartTextbox(globalCtx, 0x272F, &this->actor);
            this->unk_288 = 0x272F;
        } else {
            Message_StartTextbox(globalCtx, 0x2730, &this->actor);
            this->unk_288 = 0x2730;
        }
        func_80B26AE8(this);
        player->stateFlags1 &= ~0x20;
    } else {
        func_800B85E0(&this->actor, globalCtx, 1000.0f, -1);
    }
}

void func_80B2783C(EnKendoJs* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        Camera_ChangeDataIdx(globalCtx->cameraPtrs[CAM_ID_MAIN],
                             ActorCutscene_GetCutscene(this->actor.cutscene)->csCamSceneDataId);
    }
}

void func_80B27880(EnKendoJs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f0 = this->actor.world.pos.z + 70.0f;

    if ((ENKENDOJS_GET_FF(&this->actor) != ENKENDOJS_FF_1) && (player->actor.world.pos.z < temp_f0)) {
        player->actor.world.pos.z = temp_f0;
    }
}

s32 func_80B278C4(GlobalContext* globalCtx, Vec3f arg1) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f0;
    f32 sp28;
    s16 sp22 = Math_Vec3f_Yaw(&player->actor.world.pos, &arg1);

    temp_f0 = Math_Vec3f_DistXZ(&player->actor.world.pos, &arg1);

    if (temp_f0 < 20.0f) {
        sp28 = 10.0f;
    } else if (temp_f0 < 40.0f) {
        sp28 = 40.0f;
    } else {
        sp28 = 80.0f;
    }

    globalCtx->actorCtx.unk268 = 1;
    func_800B6F20(globalCtx, &globalCtx->actorCtx.unk_26C, sp28, sp22);

    if (temp_f0 < 20.0f) {
        return true;
    } else {
        return false;
    }
}

void func_80B279AC(EnKendoJs* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80B279F0(EnKendoJs* this, GlobalContext* globalCtx, s32 arg2) {
    f32 x = this->unk_274[arg2].x;
    f32 y = this->unk_274[arg2].y;
    f32 z = this->unk_274[arg2].z;

    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_MARUTA, x, y, z, 0, 0, 0, 0);
    this->unk_28C++;
}

void func_80B27A90(EnKendoJs* this, GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_EN_MARUTA) {
            ((EnMaruta*)actor)->unk_220 = 1;
        }
        actor = actor->next;
    }

    this->unk_28C = 0;
}

void EnKendoJs_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKendoJs* this = THIS;

    this->actionFunc(this, globalCtx);

    SkelAnime_Update(&this->skelAnime);
    func_800E9250(globalCtx, &this->actor, &this->unk_278, &this->unk_27E, this->actor.focus.pos);
    func_80B279AC(this, globalCtx);
    func_80B27880(this, globalCtx);
}

s32 EnKendoJs_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnKendoJs* this = THIS;

    if (limbIndex == 12) {
        rot->y -= this->unk_278.y;
    }
    return false;
}

void EnKendoJs_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnKendoJs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKendoJs* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnKendoJs_OverrideLimbDraw, EnKendoJs_PostLimbDraw, &this->actor);
}
