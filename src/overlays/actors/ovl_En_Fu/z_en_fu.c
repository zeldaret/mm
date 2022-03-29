/*
 * File: z_en_fu.c
 * Overlay: ovl_En_Fu
 * Description: Honey & Darling
 */

#include "z_en_fu.h"
#include "overlays/actors/ovl_En_Fu_Mato/z_en_fu_mato.h"
#include "overlays/actors/ovl_En_Fu_Kago/z_en_fu_kago.h"
#include "overlays/actors/ovl_Bg_Fu_Kaiten/z_bg_fu_kaiten.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/object_mu/object_mu.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000)

#define THIS ((EnFu*)thisx)

void EnFu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809622FC(EnFu* this);
void func_80962340(EnFu* this, GlobalContext* globalCtx);
void func_809628BC(EnFu* this);
void func_809628D0(EnFu* this, GlobalContext* globalCtx);
void func_809629F8(EnFu* this);
void func_80962A10(EnFu* this, GlobalContext* globalCtx);
void func_80962BA8(EnFu* this);
void func_80962BCC(EnFu* this, GlobalContext* globalCtx);
void func_80962D48(EnFu* this);
void func_80962D60(EnFu* this, GlobalContext* globalCtx);
void func_80962F10(EnFu* this);
void func_80962F4C(EnFu* this, GlobalContext* globalCtx);
void func_8096326C(EnFu* this, GlobalContext* globalCtx);
void func_809632D0(EnFu* this);
void func_80963350(EnFu* this, GlobalContext* globalCtx);
void func_80963540(EnFu* this);
void func_80963560(EnFu* this, GlobalContext* globalCtx);
void func_80963610(EnFu* this);
void func_80963630(EnFu* this, GlobalContext* globalCtx);
s32 func_80963810(GlobalContext* globalCtx, Vec3f pos);
s32 func_809638F8(GlobalContext* globalCtx);
void func_809639D0(EnFu* this, GlobalContext* globalCtx);
void func_80963DE4(EnFu* this, GlobalContext* globalCtx);
void func_80963EAC(EnFu* this, GlobalContext* globalCtx);
void func_80963F44(EnFu* this, GlobalContext* globalCtx);
void func_80963F88(EnFu* this, GlobalContext* globalCtx);
void func_80963FF8(EnFu* this, GlobalContext* globalCtx);
void func_8096413C(EnFu* this, GlobalContext* globalCtx);
void func_80964190(EnFu* this, GlobalContext* globalCtx);
void func_8096426C(EnFu* this, GlobalContext* globalCtx);
void func_80964694(EnFu* this, EnFuUnkStruct* ptr, Vec3f* arg2, s32 len);
void func_809647EC(GlobalContext* globalCtx, EnFuUnkStruct* ptr, s32 len);
void func_80964950(GlobalContext* globalCtx, EnFuUnkStruct* ptr, s32 len);

const ActorInit En_Fu_InitVars = {
    ACTOR_EN_FU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnFu),
    (ActorFunc)EnFu_Init,
    (ActorFunc)EnFu_Destroy,
    (ActorFunc)EnFu_Update,
    (ActorFunc)EnFu_Draw,
};

static s32 D_80964B00[] = { 300, 100, 100 };

static Vec3f D_80964B0C = { 0.0f, 60.0f, -8.0f };
static Vec3f D_80964B18 = { 0.0f, 55.0f, 12.0f };
static Vec3f D_80964B24 = { 0.0f, 60.0f, 0.0f };

static AnimationInfo sAnimations[] = {
    { &object_mu_Anim_0053E0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_mu_Anim_001F74, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_mu_Anim_002F64, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_mu_Anim_004904, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_mu_Anim_005304, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &object_mu_Anim_005304, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_mu_Anim_00BAC4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
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
    { 20, 50, 0, { 0, 0, 0 } },
};

void func_809616E0(EnFu* this, GlobalContext* globalCtx) {
    s32 i;
    f32 temp_f20;
    f32 temp_f22;
    s16 atan;
    s16 spA0 = false;
    Vec3f sp94;

    if ((gSaveContext.save.playerForm == PLAYER_FORM_DEKU) && (CURRENT_DAY == 3)) {
        spA0 = true;
    }
    this->unk_54C = 0;

    for (i = 0; i < this->unk_520; i++) {
        temp_f20 = this->actor.world.pos.x - this->unk_538[i].x;
        temp_f22 = this->actor.world.pos.z - this->unk_538[i].z;
        atan = Math_FAtan2F(temp_f22, temp_f20);

        if (!spA0 || ((i % 2) != 0)) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, this->unk_544, this->unk_538[i].x, this->unk_538[i].y,
                        this->unk_538[i].z, 0, atan, 0, i);
            this->unk_54C++;
        }

        if (this->unk_546 == 1) {
            Vec3f sp88 = { 0.0f, 0.0f, 0.0f };
            Vec3f sp7C = { 0.0f, 0.2f, 0.0f };
            Color_RGBA8 sp78 = { 255, 255, 255, 255 };
            Color_RGBA8 sp74 = { 198, 198, 198, 255 };

            sp94.x = this->unk_538[i].x;
            sp94.y = this->unk_538[i].y;
            sp94.z = this->unk_538[i].z;
            func_800B0EB0(globalCtx, &sp94, &sp88, &sp7C, &sp78, &sp74, 100, 150, 10);
            sp94.x -= 0.1f * temp_f20;
            sp94.z -= 0.1f * temp_f22;
            func_800B3030(globalCtx, &sp94, &sp88, &sp7C, 100, 0, 3);
        }
    }
}

void func_809619D0(EnFu* this, GlobalContext* globalCtx) {
    s32 i;
    Path* path = &globalCtx->setupPathList[ENFU_GET_FF00(&this->actor)];

    switch (CURRENT_DAY) {
        case 1:
            this->unk_542 = 2;
            this->unk_544 = ACTOR_EN_FU_MATO;
            break;

        case 2:
            this->unk_542 = 1;
            this->unk_544 = ACTOR_EN_FU_KAGO;
            break;

        case 3:
            this->unk_542 = 0;
            this->unk_544 = ACTOR_EN_FU_MATO;
            break;

        default:
            this->unk_544 = ACTOR_EN_FU_MATO;
            this->unk_542 = 2;
            break;
    }

    for (i = 0; i < this->unk_542; i++) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    this->unk_520 = path->count;
    this->unk_538 = Lib_SegmentedToVirtual(path->points);
    func_809616E0(this, globalCtx);
}

void EnFu_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFu* this = THIS;
    Actor* fuKaiten = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (fuKaiten != NULL) {
        if (fuKaiten->id == ACTOR_BG_FU_KAITEN) {
            this->actor.child = fuKaiten;
            break;
        }
        fuKaiten = fuKaiten->next;
    }

    if (fuKaiten != NULL) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_mu_Skel_00B2B0, &object_mu_Anim_001F74,
                           this->jointTable, this->morphTable, 21);
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.gravity = -0.2f;
        this->actor.shape.rot.y += 0x4000;
        this->actor.world.rot = this->actor.shape.rot;
        this->unk_546 = 0;
        this->unk_54A = 1;
        this->unk_54C = 0;
        this->unk_53C = 0;
        this->unk_53E = 0;
        this->unk_540 = 0;
        this->unk_54E = 0;
        this->unk_550 = 0;
        func_809622FC(this);
        this->actor.targetMode = 6;
        func_809619D0(this, globalCtx);
        if (CURRENT_DAY == 2) {
            Vec3f sp40 = this->actor.child->home.pos;

            this->unk_2D4 = (BgFuMizu*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BG_FU_MIZU, sp40.x, sp40.y,
                                                   sp40.z, 0, 0, 0, 0);
        } else {
            this->unk_2D4 = NULL;
        }
    }
}

void EnFu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFu* this = THIS;

    gSaveContext.save.weekEventReg[63] &= (u8)~1;
    gSaveContext.save.weekEventReg[8] &= (u8)~1;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80961D10(EnFu* this) {
    if ((this->collider.base.acFlags & AC_HIT) && (this->unk_542 == 0)) {
        return true;
    }

    if ((this->collider.base.ocFlags1 & OC1_HIT) && (this->unk_542 == 2)) {
        Actor* actor = this->collider.base.oc;

        if (actor->id == ACTOR_EN_BOM_CHU) {
            return true;
        }
    }

    return false;
}

void func_80961D7C(GlobalContext* globalCtx) {
    Actor* explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if ((explosive->id == ACTOR_EN_BOM) && (explosive->bgCheckFlags & 1)) {
            EnBom* bomb = (EnBom*)explosive;

            if (bomb->actor.floorBgId != BGCHECK_SCENE) {
                DynaPolyActor* fuKago = DynaPoly_GetActor(&globalCtx->colCtx, bomb->actor.floorBgId);

                if ((fuKago != NULL) && (fuKago->actor.id == ACTOR_EN_FU_KAGO)) {
                    Math_SmoothStepToF(&bomb->actor.world.pos.x, fuKago->actor.world.pos.x, 0.1f, 1.0f, 0.5f);
                    Math_SmoothStepToF(&bomb->actor.world.pos.z, fuKago->actor.world.pos.z, 0.1f, 1.0f, 0.5f);
                }
            }
        }
        explosive = explosive->next;
    }
}

void func_80961E88(GlobalContext* globalCtx) {
    Actor* explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        Actor_MarkForDeath(explosive);
        explosive = explosive->next;
    }
}

void func_80961EC8(GlobalContext* globalCtx) {
    Actor* fuMato = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (fuMato != NULL) {
        if (fuMato->id == ACTOR_EN_FU_MATO) {
            ((EnFuMato*)fuMato)->unk_30A = 1;
        }
        fuMato = fuMato->next;
    }
}

void func_80961F00(GlobalContext* globalCtx) {
    Actor* fuKago = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (fuKago != NULL) {
        if (fuKago->id == ACTOR_EN_FU_KAGO) {
            ((EnFuKago*)fuKago)->unk_33C = 1;
        }
        fuKago = fuKago->next;
    }
}

void func_80961F38(GlobalContext* globalCtx, Vec3f* arg1, s16* arg2, s16 arg3, s16 arg4, s16 arg5) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp42;
    s16 sp40;
    Vec3f sp34 = player->actor.focus.pos;

    sp40 = Math_Vec3f_Yaw(arg1, &sp34) - arg3;

    if (arg5 < ABS_ALT(sp40)) {
        Math_SmoothStepToS(&arg2[0], 0, 6, 6200, 100);
        Math_SmoothStepToS(&arg2[1], 0, 6, 6200, 100);
    } else {
        sp42 = Math_Vec3f_Pitch(arg1, &sp34);

        Math_SmoothStepToS(&arg2[0], sp42, 6, 6200, 100);
        Math_SmoothStepToS(&arg2[1], sp40, 6, 6200, 100);
    }

    if (arg4 < ABS_ALT(arg2[1])) {
        if (arg2[1] > 0) {
            arg2[1] = arg4;
        } else {
            arg2[1] = -arg4;
        }
    }

    Math_SmoothStepToS(&arg2[2], 0, 6, 2000, 100);
}

void func_8096209C(EnFu* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    if (this->unk_53C & 1) {
        func_80961F38(globalCtx, &this->unk_508, this->unk_524, this->actor.shape.rot.y, 0x38E3, 0x6AAA);
    } else {
        Math_SmoothStepToS(&this->unk_524[0], 0, 6, 6000, 100);
        Math_SmoothStepToS(&this->unk_524[1], 0, 6, 6000, 100);
        Math_SmoothStepToS(&this->unk_524[2], 0, 6, 6000, 100);
    }

    if (this->unk_53C & 2) {
        s16 rotY = BINANG_SUB(this->actor.shape.rot.y, 0x8000);

        func_80961F38(globalCtx, &this->unk_514, this->unk_52A, rotY, 0x38E3, 0x5555);
    } else {
        Math_SmoothStepToS(&this->unk_52A[0], 0, 6, 6000, 100);
        Math_SmoothStepToS(&this->unk_52A[1], 0, 6, 6000, 100);
        Math_SmoothStepToS(&this->unk_52A[2], 0, 6, 6000, 100);
    }

    if ((this->unk_53C & 1) && (this->unk_53C & 2)) {
        sp34 = D_80964B24;
    } else if (this->unk_53C & 1) {
        sp34 = D_80964B0C;
    } else if (this->unk_53C & 2) {
        sp34 = D_80964B18;
    } else {
        sp34 = D_80964B24;
    }

    Matrix_StatePush();
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_MultiplyVector3fByState(&sp34, &this->actor.focus.pos);
    Matrix_StatePop();
    this->actor.focus.pos.x += this->actor.world.pos.x;
    this->actor.focus.pos.y += this->actor.world.pos.y;
    this->actor.focus.pos.z += this->actor.world.pos.z;
}

void func_809622FC(EnFu* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80962340;
}

void func_80962340(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_54A == 2) {
        this->actor.flags |= ACTOR_FLAG_10000;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (this->unk_54A == 2) {
            if (this->unk_552 == 0x287D) {
                if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
                    Message_StartTextbox(globalCtx, 0x287E, &this->actor);
                    this->unk_552 = 0x287E;
                } else if ((CURRENT_DAY == 3) && (gSaveContext.save.weekEventReg[22] & 0x10) &&
                           (gSaveContext.save.weekEventReg[22] & 0x20)) {
                    if ((gSaveContext.save.weekEventReg[22] & 0x40)) {
                        Message_StartTextbox(globalCtx, 0x2883, &this->actor);
                        this->unk_552 = 0x2883;
                    } else {
                        Message_StartTextbox(globalCtx, 0x2880, &this->actor);
                        this->unk_552 = 0x2880;
                    }
                } else {
                    Message_StartTextbox(globalCtx, 0x287E, &this->actor);
                    this->unk_552 = 0x287E;
                }
            } else if ((gSaveContext.unk_3DE0[4] == 0) && (this->unk_552 != 0x2888)) {
                Message_StartTextbox(globalCtx, 0x2886, &this->actor);
                this->unk_552 = 0x2886;
            } else {
                Message_StartTextbox(globalCtx, 0x2889, &this->actor);
                this->unk_552 = 0x2889;
            }
            this->actor.flags &= ~ACTOR_FLAG_10000;
            player->stateFlags1 &= ~0x20;
            this->unk_54A = 1;
        } else {
            Message_StartTextbox(globalCtx, 0x283C, &this->actor);
            this->unk_552 = 0x283C;
        }
        func_809628BC(this);
    } else if (this->unk_54A == 2) {
        func_800B8614(&this->actor, globalCtx, 500.0f);
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, BINANG_SUB(this->actor.child->shape.rot.y, 0x4000), 10, 3000, 100);
}

void func_80962588(EnFu* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx) && (this->unk_552 == 0x2871)) {
        if (1) {}
        if (globalCtx->msgCtx.choiceIndex == 0) {
            if (gSaveContext.save.playerData.rupees >= 10) {
                func_8019F208();
                func_801159EC(-10);
                func_80963DE4(this, globalCtx);
            } else {
                play_sound(NA_SE_SY_ERROR);
                Message_StartTextbox(globalCtx, 0x2873, &this->actor);
                this->unk_552 = 0x2873;
            }
        } else {
            func_8019F230();
            Message_StartTextbox(globalCtx, 0x2872, &this->actor);
            this->unk_552 = 0x2872;
        }
    }
}

void func_80962660(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_552) {
            case 0x283C:
                func_80963F44(this, globalCtx);
                break;

            case 0x283D:
                func_809639D0(this, globalCtx);
                break;

            case 0x283E:
            case 0x283F:
            case 0x2841:
            case 0x2843:
            case 0x2845:
                func_80963F44(this, globalCtx);
                break;

            case 0x2846:
                Message_StartTextbox(globalCtx, 0x2849, &this->actor);
                this->unk_552 = 0x2849;
                break;

            case 0x2847:
            case 0x2849:
            case 0x284B:
            case 0x284D:
            case 0x284F:
            case 0x2851:
            case 0x2853:
            case 0x2855:
            case 0x2857:
            case 0x2859:
            case 0x285B:
            case 0x285D:
            case 0x285F:
            case 0x2861:
            case 0x2863:
            case 0x2865:
            case 0x2867:
            case 0x2869:
            case 0x286B:
            case 0x286D:
            case 0x286F:
            case 0x2873:
            case 0x2875:
            case 0x2877:
            case 0x2879:
            case 0x287B:
                func_80963F44(this, globalCtx);
                break;

            case 0x2848:
            case 0x284A:
            case 0x284E:
            case 0x2850:
            case 0x2852:
            case 0x2856:
            case 0x2858:
            case 0x285A:
            case 0x285C:
            case 0x285E:
            case 0x2860:
            case 0x2862:
            case 0x2864:
            case 0x2866:
            case 0x2868:
            case 0x286A:
            case 0x286C:
            case 0x286E:
                Message_StartTextbox(globalCtx, 0x2871, &this->actor);
                this->unk_552 = 0x2871;
                break;

            case 0x2876:
            case 0x2878:
            case 0x287A:
            case 0x287C:
                Message_StartTextbox(globalCtx, 0x287D, &this->actor);
                this->unk_552 = 0x287D;
                break;

            case 0x287D:
                gSaveContext.save.weekEventReg[63] |= 1;
                gSaveContext.save.weekEventReg[63] &= (u8)~2;
                func_801477B4(globalCtx);
                player->stateFlags1 |= 0x20;
                this->unk_53C = 0;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                func_801A2BB8(NA_BGM_MINI_GAME_2);
                if (this->unk_542 == 0) {
                    if (this->unk_546 == 1) {
                        func_80961EC8(globalCtx);
                    }
                    func_809629F8(this);
                } else if (this->unk_542 == 1) {
                    if (this->unk_546 == 1) {
                        func_80961F00(globalCtx);
                    }
                    func_80962BA8(this);
                } else if (this->unk_542 == 2) {
                    if (this->unk_546 == 1) {
                        func_80961EC8(globalCtx);
                    }
                    func_80962D48(this);
                }
                break;

            case 0x287E:
            case 0x2880:
            case 0x2883:
                func_801477B4(globalCtx);
                func_80963540(this);
                func_80963560(this, globalCtx);
                break;

            case 0x2886:
            case 0x2889:
                func_80963F44(this, globalCtx);
                break;
        }
    }
}

void func_809628BC(EnFu* this) {
    this->actionFunc = func_809628D0;
}

void func_809628D0(EnFu* this, GlobalContext* globalCtx) {
    u8 sp27 = Message_GetState(&globalCtx->msgCtx);

    switch (sp27) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;

        case 4:
            func_80962588(this, globalCtx);
            break;

        case 5:
            func_80962660(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                this->unk_54A = 1;
                switch (this->unk_552) {
                    case 0x287F:
                    case 0x2881:
                    case 0x2882:
                    case 0x2884:
                    case 0x2887:
                    case 0x288A:
                        gSaveContext.save.weekEventReg[63] &= (u8)~1;
                        gSaveContext.save.weekEventReg[63] &= (u8)~2;
                        func_809622FC(this);
                        break;

                    default:
                        func_809622FC(this);
                        break;
                }
            }
            break;
    }

    if (sp27 != 3) {
        func_80964190(this, globalCtx);
        func_8096426C(this, globalCtx);
    }

    func_8096413C(this, globalCtx);
}

void func_809629F8(EnFu* this) {
    this->unk_54A = 0;
    this->actionFunc = func_80962A10;
}

void func_80962A10(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    BgFuKaiten* fuKaiten = (BgFuKaiten*)this->actor.child;

    this->unk_53C = 0;
    if ((fuKaiten->rotationSpeed < 300) || (fuKaiten->bounceHeight < 40.0f) || (fuKaiten->bounceSpeed < 600)) {
        Math_SmoothStepToS(&fuKaiten->rotationSpeed, 300, 10, 5, 5);
        Math_SmoothStepToS(&fuKaiten->bounceSpeed, 600, 20, 10, 10);
        Math_SmoothStepToF(&fuKaiten->bounceHeight, 40.0f, 0.1f, 1.0f, 1.0f);
        return;
    }

    play_sound(NA_SE_SY_FOUND);
    player->stateFlags1 &= ~0x20;
    func_8010E9F0(4, 60);
    if (this->unk_546 == 1) {
        func_809616E0(this, globalCtx);
    } else {
        this->unk_546 = 1;
    }

    if ((gSaveContext.save.playerForm == PLAYER_FORM_DEKU) && gSaveContext.save.playerData.magicAcquired) {
        s16 temp = gSaveContext.unk_3F30;

        Parameter_AddMagic(globalCtx, temp + (gSaveContext.save.playerData.doubleMagic * 48) + 48);
    }

    func_80962F10(this);
}

void func_80962BA8(EnFu* this) {
    BgFuMizu* mizu = this->unk_2D4;

    this->unk_54A = 0;
    mizu->unk_160 = 1;
    this->actionFunc = func_80962BCC;
}

void func_80962BCC(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    BgFuKaiten* fuKaiten = (BgFuKaiten*)this->actor.child;

    if ((fuKaiten->rotationSpeed < 100) || (fuKaiten->bounceHeight < 30.0f) || (fuKaiten->bounceSpeed < 600)) {
        Math_SmoothStepToS(&fuKaiten->rotationSpeed, 100, 10, 5, 5);
        Math_SmoothStepToS(&fuKaiten->bounceSpeed, 600, 20, 10, 10);
        Math_SmoothStepToF(&fuKaiten->elevation, 10.0f, 0.1f, 1.0f, 1.0f);
        Math_SmoothStepToF(&fuKaiten->bounceHeight, 30.0f, 0.1f, 1.0f, 1.0f);
        return;
    }

    play_sound(NA_SE_SY_FOUND);
    player->stateFlags1 &= ~0x20;
    player->stateFlags3 |= 0x400000;
    func_8010E9F0(4, 60);

    if (this->unk_546 == 1) {
        func_809616E0(this, globalCtx);
    } else {
        this->unk_546 = 1;
    }

    globalCtx->unk_1887E = 30;
    func_80962F10(this);
}

void func_80962D48(EnFu* this) {
    this->unk_54A = 0;
    this->actionFunc = func_80962D60;
}

void func_80962D60(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    BgFuKaiten* fuKaiten = (BgFuKaiten*)this->actor.child;

    if ((fuKaiten->rotationSpeed < 100) || (fuKaiten->bounceHeight < 40.0f) || (fuKaiten->bounceSpeed < 600)) {
        Math_SmoothStepToS(&fuKaiten->rotationSpeed, 100, 10, 5, 5);
        Math_SmoothStepToS(&fuKaiten->bounceSpeed, 600, 20, 10, 10);
        Math_SmoothStepToF(&fuKaiten->bounceHeight, 40.0f, 0.1f, 1.0f, 1.0f);
        return;
    }

    play_sound(NA_SE_SY_FOUND);
    player->stateFlags1 &= ~0x20;
    player->stateFlags3 |= 0x400000;
    func_8010E9F0(4, 60);

    if (this->unk_546 == 1) {
        func_809616E0(this, globalCtx);
    } else {
        this->unk_546 = 1;
    }

    globalCtx->unk_1887D = 30;
    func_80962F10(this);
}

void func_80962EBC(EnFu* this, GlobalContext* globalCtx) {
    if (this->unk_542 != 0) {
        if (this->actor.cutscene != -1) {
            Camera_ChangeDataIdx(globalCtx->cameraPtrs[CAM_ID_MAIN],
                                 ActorCutscene_GetCutscene(this->actor.cutscene)->csCamSceneDataId);
        }
    }
}

void func_80962F10(EnFu* this) {
    this->unk_548 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    gSaveContext.save.weekEventReg[8] |= 1;
    this->actionFunc = func_80962F4C;
}

void func_80962F4C(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    BgFuKaiten* fuKaiten = (BgFuKaiten*)this->actor.child;

    switch (this->unk_542) {
        case 0:
            if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
                player->stateFlags3 |= 0x400;
            }
            break;

        case 1:
            globalCtx->unk_1887E = 30;
            break;

        case 2:
            globalCtx->unk_1887D = 30;
            break;
    }

    if (gSaveContext.unk_3DE0[4] < 2000) {
        s16 val = D_80964B00[this->unk_542] + 200;

        Math_SmoothStepToS(&fuKaiten->rotationSpeed, val, 10, 5, 5);
    } else if (gSaveContext.unk_3DE0[4] < 4000) {
        s16 val = D_80964B00[this->unk_542] + 100;

        Math_SmoothStepToS(&fuKaiten->rotationSpeed, val, 10, 5, 5);
    }

    if (func_80961D10(this)) {
        Message_StartTextbox(globalCtx, 0x288B, &this->actor);
    }

    if ((!DynaPolyActor_IsInRidingRotatingState((DynaPolyActor*)this->actor.child) &&
         (player->actor.bgCheckFlags & 1)) ||
        (gSaveContext.unk_3DE0[4] < 1) || (this->unk_548 == this->unk_54C)) {
        player->stateFlags3 &= ~0x400000;
        func_80961E88(globalCtx);
        player->stateFlags1 |= 0x20;
        if (this->unk_548 < this->unk_54C) {
            if (gSaveContext.unk_3DE0[4] == 0) {
                Message_StartTextbox(globalCtx, 0x2885, &this->actor);
                this->unk_552 = 0x2885;
            } else {
                Message_StartTextbox(globalCtx, 0x2888, &this->actor);
                this->unk_552 = 0x2888;
            }
            func_801A2C20();
            gSaveContext.unk_3DE0[4] = 0;
            gSaveContext.unk_3DD0[4] = 5;
            this->unk_548 = 0;
            func_809632D0(this);
        } else {
            this->unk_548 = 0;
            func_801A2C20();
            gSaveContext.unk_3DE0[4] = 0;
            gSaveContext.unk_3DD0[4] = 5;
            func_801A3098(NA_BGM_GET_ITEM | 0x900);
            func_8011B4E0(globalCtx, 1);
            this->unk_54A = 3;
            func_809632D0(this);
        }
    }
    func_80962EBC(this, globalCtx);
}

void func_80963258(EnFu* this) {
    this->actionFunc = func_8096326C;
}

void func_8096326C(EnFu* this, GlobalContext* globalCtx) {
    func_80963FF8(this, globalCtx);
    if (func_80963810(globalCtx, this->actor.world.pos)) {
        func_809622FC(this);
    }
}

void func_809632D0(EnFu* this) {
    if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
        Interface_ChangeAlpha(50);
    }

    gSaveContext.save.weekEventReg[8] &= (u8)~1;

    if (this->unk_2D4 != NULL) {
        BgFuMizu* mizu = this->unk_2D4;

        mizu->unk_160 = 0;
    }

    this->actor.flags |= ACTOR_FLAG_1;
    this->actionFunc = func_80963350;
}

void func_80963350(EnFu* this, GlobalContext* globalCtx) {
    static s32 D_80964C24 = 0;
    BgFuKaiten* fuKaiten = (BgFuKaiten*)this->actor.child;

    if ((this->unk_54A == 0) && (((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) ||
                                 ((Message_GetState(&globalCtx->msgCtx) == 2) && (globalCtx->msgCtx.unk12023 == 1)))) {
        func_801477B4(globalCtx);
        this->unk_54A = 2;
        D_80964C24 = 1;
    }

    if ((this->unk_54A == 3) && (globalCtx->interfaceCtx.unk_286 == 0)) {
        this->unk_54A = 2;
        D_80964C24 = 1;
    }

    if ((fuKaiten->rotationSpeed != 0) || (fuKaiten->bounceSpeed != 0) || (fuKaiten->bounceHeight > 0.0f) ||
        !func_809638F8(globalCtx)) {
        Math_SmoothStepToS(&fuKaiten->rotationSpeed, 0, 10, 10, 5);
        Math_SmoothStepToS(&fuKaiten->bounceSpeed, 0, 10, 15, 5);
        Math_SmoothStepToF(&fuKaiten->bounceHeight, 0.0f, 0.1f, 1.0f, 1.0f);
        Math_SmoothStepToF(&fuKaiten->elevation, 0.0f, 0.1f, 1.0f, 1.0f);
        func_80962EBC(this, globalCtx);
    } else if (D_80964C24 == 1) {
        D_80964C24 = 0;
        fuKaiten->bounce = 0;
        func_80963F88(this, globalCtx);
        globalCtx->actorCtx.unk268 = 1;
        func_80963258(this);
    }
}

void func_80963540(EnFu* this) {
    this->actor.child->freezeTimer = 10;
    this->actionFunc = func_80963560;
}

void func_80963560(EnFu* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80963610(this);
    } else if ((this->unk_552 == 0x2880) && !(gSaveContext.save.weekEventReg[22] & 0x80)) {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 500.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    }
    this->actor.child->freezeTimer = 10;
}

void func_80963610(EnFu* this) {
    this->actor.child->freezeTimer = 10;
    this->actionFunc = func_80963630;
}

void func_80963630(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if ((gSaveContext.save.weekEventReg[22] & 0x10) && (gSaveContext.save.weekEventReg[22] & 0x20) &&
            (CURRENT_DAY == 3) && (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
            if (gSaveContext.save.weekEventReg[22] & 0x40) {
                Message_StartTextbox(globalCtx, 0x2884, &this->actor);
                this->unk_552 = 0x2884;
            } else if (!(gSaveContext.save.weekEventReg[22] & 0x80)) {
                gSaveContext.save.weekEventReg[22] |= 0x80;
                Message_StartTextbox(globalCtx, 0x2882, &this->actor);
                this->unk_552 = 0x2882;
            } else {
                Message_StartTextbox(globalCtx, 0x2881, &this->actor);
                this->unk_552 = 0x2881;
            }
        } else {
            Message_StartTextbox(globalCtx, 0x287F, &this->actor);
            this->unk_552 = 0x287F;
        }

        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actor.child->freezeTimer = 0;
        func_809628BC(this);

        if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
            switch (CURRENT_DAY) {
                case 1:
                    gSaveContext.save.weekEventReg[22] |= 0x10;
                    break;

                case 2:
                    gSaveContext.save.weekEventReg[22] |= 0x20;
                    break;

                case 3:
                    gSaveContext.save.weekEventReg[22] |= 0x40;
                    break;
            }
        }
        player->stateFlags1 &= ~0x20;
    } else {
        this->actor.child->freezeTimer = 10;
        func_800B85E0(&this->actor, globalCtx, 500.0f, EXCH_ITEM_MINUS1);
    }
}

s32 func_80963810(GlobalContext* globalCtx, Vec3f pos) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sp28;
    f32 phi_f0;
    s16 sp22;

    sp22 = Math_Vec3f_Yaw(&player->actor.world.pos, &pos);
    sp28 = Math_Vec3f_DistXZ(&player->actor.world.pos, &pos);

    if (sp28 < 80.0f) {
        phi_f0 = 10.0f;
    } else if (sp28 < 90.0f) {
        phi_f0 = 40.0f;
    } else {
        phi_f0 = 80.0f;
    }

    globalCtx->actorCtx.unk268 = 1;
    func_800B6F20(globalCtx, &globalCtx->actorCtx.unk_26C, phi_f0, sp22);

    if (sp28 < 80.0f) {
        return true;
    }
    return false;
}

s32 func_809638F8(GlobalContext* globalCtx) {
    s32 ret = true;

    if (globalCtx->envCtx.lightSettings.diffuseColor1[0] > 25) {
        globalCtx->envCtx.lightSettings.diffuseColor1[0] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.diffuseColor1[0] = 0;
    }

    if (globalCtx->envCtx.lightSettings.diffuseColor1[1] > 25) {
        globalCtx->envCtx.lightSettings.diffuseColor1[1] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.diffuseColor1[1] = 0;
    }

    if (globalCtx->envCtx.lightSettings.diffuseColor1[2] > 25) {
        globalCtx->envCtx.lightSettings.diffuseColor1[2] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.diffuseColor1[2] = 0;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[0] > 25) {
        globalCtx->envCtx.lightSettings.ambientColor[0] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.ambientColor[0] = 0;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[1] > 25) {
        globalCtx->envCtx.lightSettings.ambientColor[1] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.ambientColor[1] = 0;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[2] > 25) {
        globalCtx->envCtx.lightSettings.ambientColor[2] -= 25;
        ret = false;
    } else {
        globalCtx->envCtx.lightSettings.ambientColor[2] = 0;
    }
    return ret;
}

void func_809639D0(EnFu* this, GlobalContext* globalCtx) {
    switch (CURRENT_DAY) {
        case 1:
            if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
                if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
                    Message_StartTextbox(globalCtx, 0x2853, &this->actor);
                    this->unk_552 = 0x2853;
                } else if (gSaveContext.save.weekEventReg[22] & 0x10) {
                    Message_StartTextbox(globalCtx, 0x284D, &this->actor);
                    this->unk_552 = 0x284D;
                } else if (this->unk_53E == 1) {
                    Message_StartTextbox(globalCtx, 0x284F, &this->actor);
                    this->unk_552 = 0x284F;
                } else {
                    this->unk_53E = 1;
                    Message_StartTextbox(globalCtx, 0x2851, &this->actor);
                    this->unk_552 = 0x2851;
                }
            } else {
                Message_StartTextbox(globalCtx, 0x286F, &this->actor);
                this->unk_552 = 0x286F;
            }
            break;

        case 2:
            if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
                Message_StartTextbox(globalCtx, 0x286F, &this->actor);
                this->unk_552 = 0x286F;
            } else if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
                Message_StartTextbox(globalCtx, 0x2853, &this->actor);
                this->unk_552 = 0x2853;
            } else if (!(gSaveContext.save.weekEventReg[22] & 0x10)) {
                if (this->unk_53E == 1) {
                    Message_StartTextbox(globalCtx, 0x285B, &this->actor);
                    this->unk_552 = 0x285B;
                } else {
                    this->unk_53E = 1;
                    Message_StartTextbox(globalCtx, 0x285D, &this->actor);
                    this->unk_552 = 0x285D;
                }
            } else if (gSaveContext.save.weekEventReg[22] & 0x20) {
                Message_StartTextbox(globalCtx, 0x2855, &this->actor);
                this->unk_552 = 0x2855;
            } else if (this->unk_53E == 1) {
                Message_StartTextbox(globalCtx, 0x2857, &this->actor);
                this->unk_552 = 0x2857;
            } else {
                this->unk_53E = 1;
                Message_StartTextbox(globalCtx, 0x2859, &this->actor);
                this->unk_552 = 0x2859;
            }
            break;

        case 3:
            if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
                if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
                    func_80963EAC(this, globalCtx);
                } else {
                    Message_StartTextbox(globalCtx, 0x2841, &this->actor);
                    this->unk_552 = 0x2841;
                }
            } else if (CUR_UPG_VALUE(UPG_QUIVER) == 0) {
                Message_StartTextbox(globalCtx, 0x284B, &this->actor);
                this->unk_552 = 0x284B;
            } else if (gSaveContext.save.weekEventReg[22] & 0x40) {
                if ((gSaveContext.save.weekEventReg[22] & 0x10) && (gSaveContext.save.weekEventReg[22] & 0x20)) {
                    Message_StartTextbox(globalCtx, 0x285F, &this->actor);
                    this->unk_552 = 0x285F;
                } else {
                    Message_StartTextbox(globalCtx, 0x2861, &this->actor);
                    this->unk_552 = 0x2861;
                }
            } else if ((gSaveContext.save.weekEventReg[22] & 0x10) && (gSaveContext.save.weekEventReg[22] & 0x20)) {
                if (this->unk_53E == 1) {
                    Message_StartTextbox(globalCtx, 0x2863, &this->actor);
                    this->unk_552 = 0x2863;
                } else {
                    this->unk_53E = 1;
                    Message_StartTextbox(globalCtx, 0x2865, &this->actor);
                    this->unk_552 = 0x2865;
                }
            } else if ((gSaveContext.save.weekEventReg[22] & 0x10) || (gSaveContext.save.weekEventReg[22] & 0x20)) {
                if (this->unk_53E == 1) {
                    Message_StartTextbox(globalCtx, 0x2867, &this->actor);
                    this->unk_552 = 0x2867;
                } else {
                    this->unk_53E = 1;
                    Message_StartTextbox(globalCtx, 0x2869, &this->actor);
                    this->unk_552 = 0x2869;
                }
            } else if (this->unk_53E == 1) {
                Message_StartTextbox(globalCtx, 0x286B, &this->actor);
                this->unk_552 = 0x286B;
            } else {
                this->unk_53E = 1;
                Message_StartTextbox(globalCtx, 0x286D, &this->actor);
                this->unk_552 = 0x286D;
            }
            break;
    }
}

void func_80963DE4(EnFu* this, GlobalContext* globalCtx) {
    switch (this->unk_542) {
        case 0:
            if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
                Message_StartTextbox(globalCtx, 0x2875, &this->actor);
                this->unk_552 = 0x2875;
            } else {
                Message_StartTextbox(globalCtx, 0x2877, &this->actor);
                this->unk_552 = 0x2877;
            }
            break;

        case 1:
            Message_StartTextbox(globalCtx, 0x2879, &this->actor);
            this->unk_552 = 0x2879;
            break;

        case 2:
            Message_StartTextbox(globalCtx, 0x287B, &this->actor);
            this->unk_552 = 0x287B;
            break;
    }
}

void func_80963EAC(EnFu* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.playerData.magicAcquired) {
        if (this->unk_540 == 1) {
            Message_StartTextbox(globalCtx, 0x2847, &this->actor);
            this->unk_552 = 0x2847;
        } else {
            this->unk_540 = 1;
            Message_StartTextbox(globalCtx, 0x2845, &this->actor);
            this->unk_552 = 0x2845;
        }
    } else {
        Message_StartTextbox(globalCtx, 0x2843, &this->actor);
        this->unk_552 = 0x2843;
    }
}

void func_80963F44(EnFu* this, GlobalContext* globalCtx) {
    u16 sp1E = this->unk_552 + 1;

    Message_StartTextbox(globalCtx, sp1E, &this->actor);
    this->unk_552 = sp1E;
}

void func_80963F88(EnFu* this, GlobalContext* globalCtx) {
    if (this->unk_542 == 1) {
        func_800DFAC8(globalCtx->cameraPtrs[CAM_ID_MAIN], 75);
        globalCtx->unk_1887E = 0;
    } else if (this->unk_542 == 2) {
        globalCtx->unk_1887D = 0;
        func_800DFAC8(globalCtx->cameraPtrs[CAM_ID_MAIN], 75);
    }
}

void func_80963FF8(EnFu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags1 & 0x100000) {
        globalCtx->actorCtx.unk268 = 1;
        globalCtx->actorCtx.unk_26C.press.button = 0x8000;
    } else {
        globalCtx->actorCtx.unk268 = 1;
    }
}

void func_80964034(EnFu* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (DECR(this->unk_54E) == 0) {
        this->unk_54E = 12;
        sp2C = this->actor.world.pos;
        sp2C.y += 62.0f;
        func_80964694(this, this->unk_2D8, &sp2C, ARRAY_COUNT(this->unk_2D8));
    }
    func_809647EC(globalCtx, this->unk_2D8, ARRAY_COUNT(this->unk_2D8));
}

void func_809640D8(EnFu* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80962A10) || (this->actionFunc == func_80962BCC) ||
        (this->actionFunc == func_80962D60) || (this->actionFunc == func_80962F4C) ||
        (this->actionFunc == func_80963350)) {
        this->actor.shape.rot.y += 0x400;
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void func_8096413C(EnFu* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, BINANG_SUB(this->actor.yawTowardsPlayer, 0x4000), 5, 1000, 100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80964190(EnFu* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_552) {
            case 0x2842:
            case 0x2844:
            case 0x2848:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                break;

            case 0x2840:
            case 0x2841:
            case 0x2843:
            case 0x2847:
            case 0x2849:
            case 0x284B:
            case 0x284D:
            case 0x284F:
            case 0x2851:
            case 0x2853:
            case 0x2855:
            case 0x2857:
            case 0x2859:
            case 0x285B:
            case 0x285D:
            case 0x2861:
            case 0x2863:
            case 0x2865:
            case 0x2867:
            case 0x2869:
            case 0x286B:
            case 0x286D:
            case 0x2871:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
                break;

            case 0x2860:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
                break;

            case 0x285F:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
                break;

            case 0x287E:
            case 0x2880:
            case 0x2883:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                break;
        }
    }
}

void func_8096426C(EnFu* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_552) {
            case 0x2840:
            case 0x2841:
            case 0x2843:
            case 0x2847:
            case 0x2849:
            case 0x284D:
            case 0x284F:
            case 0x2851:
            case 0x2853:
            case 0x2855:
            case 0x2857:
            case 0x2859:
            case 0x285B:
            case 0x285D:
            case 0x2861:
            case 0x2863:
            case 0x2865:
            case 0x2867:
            case 0x2869:
            case 0x286B:
            case 0x286D:
            case 0x2871:
            case 0x2875:
            case 0x2877:
            case 0x2879:
            case 0x287B:
            case 0x287D:
                this->unk_53C = 1;
                break;

            case 0x2848:
            case 0x284A:
            case 0x284E:
            case 0x2850:
            case 0x2852:
            case 0x2856:
            case 0x2858:
            case 0x285A:
            case 0x285C:
            case 0x285E:
            case 0x2860:
            case 0x2862:
            case 0x2864:
            case 0x2866:
            case 0x2868:
            case 0x286A:
            case 0x286C:
            case 0x286E:
                this->unk_53C = 2;
                break;

            default:
                this->unk_53C = 0;
                break;
        }
    }
}

void func_809642E0(EnFu* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    if (this->unk_542 == 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnFu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFu* this = THIS;

    this->actionFunc(this, globalCtx);

    func_809642E0(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    func_8096209C(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    SkelAnime_Update(&this->skelAnime);
    func_80961D7C(globalCtx);
    func_809640D8(this, globalCtx);
    func_80964034(this, globalCtx);
}

s32 EnFu_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnFu* this = THIS;

    if (limbIndex == 9) {
        Matrix_InsertTranslation(1600.0f, 300.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_524[1], MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_524[0], MTXMODE_APPLY);
        Matrix_RotateY(this->unk_524[2], MTXMODE_APPLY);
        Matrix_InsertTranslation(-1600.0f, -300.0f, 0.0f, MTXMODE_APPLY);
    } else if (limbIndex == 20) {
        Matrix_InsertTranslation(1800.0f, 200.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_52A[1], MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_52A[0], MTXMODE_APPLY);
        Matrix_RotateY(this->unk_52A[2], MTXMODE_APPLY);
        Matrix_InsertTranslation(-1800.0f, -200.0f, 0.0f, MTXMODE_APPLY);
    }
    return false;
}

void EnFu_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80964C28 = { -2500.0f, 0.0f, 0.0f };
    static Vec3f D_80964C34 = { -3500.0f, 0.0f, 0.0f };
    EnFu* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultiplyVector3fByState(&D_80964C28, &this->unk_508);
    } else if (limbIndex == 20) {
        Matrix_MultiplyVector3fByState(&D_80964C34, &this->unk_514);
    }
}

void EnFu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFu* this = THIS;

    Matrix_StatePush();
    func_80964950(globalCtx, this->unk_2D8, ARRAY_COUNT(this->unk_2D8));
    Matrix_StatePop();

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 0, 50, 160, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 255, 255, 255, 0));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnFu_OverrideLimbDraw, EnFu_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80964694(EnFu* this, EnFuUnkStruct* ptr, Vec3f* arg2, s32 len) {
    Vec3f sp2C = { 0.0f, 1.5f, 0.0f };
    Vec3f sp20 = { 0.0f, 0.0f, 0.0f };
    s32 i = 0;

    while ((i < len) && (ptr->unk_36 != 0)) {
        i++;
        ptr++;
    }

    if (i < len) {
        ptr->unk_36 = 1;
        ptr->unk_08 = *arg2;
        ptr->unk_20 = sp2C;
        ptr->unk_14 = sp20;
        ptr->unk_00 = 0.01f;

        ptr->unk_08.x += 4.0f * Math_SinS(this->actor.shape.rot.y);
        ptr->unk_08.z += 4.0f * Math_CosS(this->actor.shape.rot.y);
        ptr->unk_37 = 16;
    }
}

void func_809647EC(GlobalContext* globalCtx, EnFuUnkStruct* ptr, s32 len) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    s16 yaw = Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));
    s32 i;

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk_36 == 1) {
            if (DECR(ptr->unk_37) == 0) {
                ptr->unk_36 = false;
            }
            ptr->unk_08.y += ptr->unk_20.y;
            ptr->unk_08.x += 2.0f * Math_SinS(ptr->unk_2C);
            ptr->unk_08.z += 2.0f * Math_CosS(ptr->unk_2C);
            Matrix_StatePush();
            Matrix_InsertTranslation(ptr->unk_08.x, ptr->unk_08.y, ptr->unk_08.z, MTXMODE_NEW);
            Matrix_RotateY(yaw, MTXMODE_APPLY);
            Matrix_MultiplyVector3fByState(&sp44, &ptr->unk_08);
            Matrix_StatePop();
            ptr->unk_2C += 6000;
        }
    }
}

void func_80964950(GlobalContext* globalCtx, EnFuUnkStruct* ptr, s32 len) {
    s32 i;
    s32 flag = false;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk_36 == 1) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0A0);
                flag = true;
            }
            Matrix_InsertTranslation(ptr->unk_08.x, ptr->unk_08.y, ptr->unk_08.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk_00, ptr->unk_00, ptr->unk_00, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0E0);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
