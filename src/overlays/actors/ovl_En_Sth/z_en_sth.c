/*
 * File: z_en_sth.c
 * Overlay: ovl_En_Sth
 * Description: Guy looking at moon in South Clock Town
 */

#include "z_en_sth.h"
#include "objects/object_sth/object_sth.h"
#include "objects/object_ahg/object_ahg.h"
#include "objects/object_mask_truth/object_mask_truth.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnSth*)thisx)

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B67208(EnSth* this, GlobalContext* globalCtx);
void func_80B67540(EnSth* this, GlobalContext* globalCtx);
void func_80B677BC(EnSth* this, GlobalContext* globalCtx);
void func_80B678A8(EnSth* this, GlobalContext* globalCtx);
void func_80B67958(EnSth* this, GlobalContext* globalCtx);
void func_80B67C1C(EnSth* this, GlobalContext* globalCtx);
void func_80B67DA0(EnSth* this, GlobalContext* globalCtx);
void func_80B680A8(Actor* thisx, GlobalContext* globalCtx);
void func_80B6849C(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_Update,
    (ActorFunc)NULL,
};

#include "overlays/ovl_En_Sth/ovl_En_Sth.c"

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

AnimationHeader* D_80B6D1C8[] = {
    &ovl_En_Sth_Anim_003F50, &ovl_En_Sth_Anim_0045B4, &ovl_En_Sth_Anim_004CC0, &ovl_En_Sth_Anim_00533C,
    &ovl_En_Sth_Anim_0059B8, &ovl_En_Sth_Anim_005E40, &ovl_En_Sth_Anim_006354, &ovl_En_Sth_Anim_00645C,
};

u16 D_80B6D1E8[] = { 0x1144, 0x1145, 0x1146 };

u16 D_80B6D1F0[] = { 0x1139, 0x113E, 0x1143 };

u16 D_80B6D1F8[] = { 0x1132, 0x113A, 0x113F };

Vec3f D_80B6D200 = { 700.0f, 400.0f, 0.0f };

Color_RGB8 D_80B6D20C[] = {
    { 190, 110, 0 }, { 0, 180, 110 }, { 0, 255, 0x50 }, { 255, 160, 60 }, { 190, 230, 250 }, { 240, 230, 120 },
};

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSth* this = THIS;
    s32 objectId;

    if (ENSTH_GET_100(&this->actor)) {
        objectId = Object_GetIndex(&globalCtx->objectCtx, OBJECT_AHG);
    } else {
        objectId = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STH);
    }
    this->unk_29E = objectId;
    this->unk_29F = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MASK_TRUTH);

    Actor_SetScale(&this->actor, 0.01f);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);

    this->unk_29C = 0;
    this->unk_29A = 8;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    switch (ENSTH_GET_F(&this->actor)) {
        case ENSTH_F_1:
            if (globalCtx->actorCtx.unk5 & 2) {
                this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
                this->actionFunc = func_80B67958;
            } else {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ENSTH_F_2:
            if (Inventory_GetSkullTokenCount(globalCtx->sceneNum) >= 30) {
                this->actionFunc = func_80B67DA0;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.textId = 0;
            if (!(gSaveContext.save.weekEventReg[34] & 0x40) || !(gSaveContext.save.weekEventReg[34] & 8)) {
                this->unk_29C |= 1;
            }
            break;

        case ENSTH_F_3:
            if ((gSaveContext.save.skullTokenCount & 0xFFFF) >= 30) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actionFunc = func_80B678A8;
            this->unk_29C |= 8;
            this->actor.targetMode = 3;
            this->actor.uncullZoneForward = 800.0f;
            break;

        case ENSTH_F_4:
            if (gSaveContext.save.weekEventReg[13] & 0x20) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actor.textId = 0;
            this->actionFunc = func_80B677BC;
            if (gSaveContext.save.weekEventReg[13] & 0x80) {
                this->unk_29C |= 2;
            }
            break;

        case ENSTH_F_5:
            if (!(gSaveContext.save.weekEventReg[13] & 0x20) ||
                (Inventory_GetSkullTokenCount(globalCtx->sceneNum) < 30)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actionFunc = func_80B67208;
            this->actor.textId = 0;
            this->unk_29C |= 8;
            break;

        default:
            this->actionFunc = func_80B67958;
            break;
    }
}

void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80B6703C(EnSth* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
        Actor_IsFacingPlayer(&this->actor, 0x2000)) {
        return true;
    }
    return false;
}

void func_80B670A4(EnSth* this, s16 arg1) {
    if ((arg1 >= 0) && (arg1 < ARRAY_COUNT(D_80B6D1C8)) && (arg1 != this->unk_29A)) {
        Animation_Change(&this->skelAnime, D_80B6D1C8[arg1], 1.0f, 0.0f, Animation_GetLastFrame(D_80B6D1C8[arg1]), 0,
                         -5.0f);
        this->unk_29A = arg1;
    }
}

void func_80B67148(EnSth* this, GlobalContext* globalCtx) {
    s32 day = CURRENT_DAY - 1;
    u16 val;

    if (day < 0) {
        day = 0;
    }
    val = D_80B6D1E8[day];

    Message_StartTextbox(globalCtx, val, &this->actor);
}

void func_80B671A0(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        this->actionFunc = func_80B67208;
        func_801477B4(globalCtx);
    }
}

void func_80B67208(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80B67148(this, globalCtx);
        this->actionFunc = func_80B671A0;
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void func_80B672A4(EnSth* this, GlobalContext* globalCtx) {
    u16 sp1E;
    s32 day = CURRENT_DAY - 1;

    if (day < 0) {
        day = 0;
    }

    if (this->unk_29C & 2) {
        s32 pad;

        sp1E = D_80B6D1F0[day];
        if (day == 2) {
            func_80B670A4(this, 5);
        }
    } else {
        sp1E = D_80B6D1F8[day];
    }
    Message_StartTextbox(globalCtx, sp1E, &this->actor);
}

void func_80B67348(EnSth* this, GlobalContext* globalCtx) {
    u16 phi_a1;

    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = func_80B67540;

        switch (this->actor.home.rot.z) {
            case 8:
            case 9:
                phi_a1 = 0x1137;
                break;

            case 6:
                phi_a1 = 0x1138;
                break;

            case 5:
                if (gSaveContext.save.weekEventReg[13] & 0x40) {
                    phi_a1 = 0x113D;
                } else {
                    phi_a1 = 0x113C;
                }
                break;

            default:
                if (gSaveContext.save.weekEventReg[13] & 0x40) {
                    phi_a1 = 0x1142;
                } else {
                    phi_a1 = 0x1141;
                }
                break;
        }
        Message_StartTextbox(globalCtx, phi_a1, &this->actor);
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_80B67458(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80B67348;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
        if (CURRENT_DAY == 3) {
            func_80B670A4(this, 6);
        } else {
            func_80B670A4(this, 3);
        }
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->actor.home.rot.z, 10000.0f, 500.0f);
    }
}

void func_80B67540(EnSth* this, GlobalContext* globalCtx) {
    s32 sp2C = CURRENT_DAY - 1;

    if (sp2C < 0) {
        sp2C = 0;
    }

    if (this->unk_29A == 6) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    SkelAnime_Update(&this->skelAnime);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x1134:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x1132:
                    case 0x113A:
                    case 0x113F:
                        func_80151938(globalCtx, 0x1133);
                        break;

                    case 0x1133:
                        func_80151938(globalCtx, 0x1136);
                        func_80B670A4(this, 6);
                        break;

                    case 0x1136:
                        gSaveContext.save.weekEventReg[13] |= 0x80;

                        switch (sp2C) {
                            case 0:
                                if (gSaveContext.save.weekEventReg[13] & 0x40) {
                                    this->actor.home.rot.z = 6;
                                } else {
                                    gSaveContext.save.weekEventReg[13] |= 0x40;
                                    switch (CUR_UPG_VALUE(UPG_WALLET)) {
                                        case 0:
                                            this->actor.home.rot.z = 8;
                                            break;

                                        case 1:
                                            this->actor.home.rot.z = 9;
                                            break;
                                    }
                                }
                                break;

                            case 1:
                                this->actor.home.rot.z = 5;
                                break;

                            default:
                                this->actor.home.rot.z = 4;
                                break;
                        }
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80B67458;
                        func_80B67458(this, globalCtx);
                        break;

                    case 0x113C:
                        func_80151938(globalCtx, 0x113B);
                        break;

                    case 0x1141:
                        func_80151938(globalCtx, 0x1140);
                        func_80B670A4(this, 3);
                        break;

                    default:
                        this->actionFunc = func_80B677BC;
                        func_801477B4(globalCtx);
                        this->unk_29C |= 2;
                        break;
                }
            }
            break;

        case 2:
            this->actionFunc = func_80B677BC;
            this->unk_29C |= 2;
            break;
    }
}

void func_80B677BC(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80B672A4(this, globalCtx);
        this->actionFunc = func_80B67540;
    } else if (func_80B6703C(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void func_80B67838(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        this->actionFunc = func_80B678A8;
        func_801477B4(globalCtx);
    }
    this->unk_294.x = -0x1388;
}

void func_80B678A8(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B67838;
    } else if (func_80B6703C(this, globalCtx) || this->actor.isTargeted) {
        if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time <= CLOCK_TIME(18, 0))) {
            this->actor.textId = 0x1130;
        } else {
            this->actor.textId = 0x1131;
        }
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
    this->unk_294.x = -0x1388;
}

void func_80B67958(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void func_80B67984(EnSth* this, GlobalContext* globalCtx) {
    u16 sp1E;

    if (gSaveContext.save.weekEventReg[34] & 0x10) {
        sp1E = 0x903;
        func_80B670A4(this, 2);
    } else if (gSaveContext.save.weekEventReg[34] & 0x20) {
        sp1E = 0x90F;
        func_80B670A4(this, 2);
    } else if (gSaveContext.save.weekEventReg[34] & 0x40) {
        if (!(gSaveContext.save.weekEventReg[34] & 8)) {
            sp1E = 0x91B;
        } else {
            sp1E = 0x918;
        }
        func_80B670A4(this, 2);
    } else if (Inventory_GetSkullTokenCount(globalCtx->sceneNum) >= 30) {
        if (INV_CONTENT(ITEM_MASK_TRUTH) == ITEM_MASK_TRUTH) {
            this->unk_29C |= 4;
            sp1E = 0x919;
        } else {
            sp1E = 0x916;
        }
    } else if (gSaveContext.save.weekEventReg[34] & 2) {
        sp1E = 0x8FF;
    } else {
        sp1E = 0x8FC;
        gSaveContext.save.weekEventReg[34] |= 2;
    }
    Message_StartTextbox(globalCtx, sp1E, &this->actor);
}

void func_80B67AB4(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B67C1C;
        gSaveContext.save.weekEventReg[34] |= 0x40;
        Message_StartTextbox(globalCtx, 0x918, &this->actor);
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_80B67B50(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80B67AB4;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        this->unk_29C &= ~1;
        gSaveContext.save.weekEventReg[34] |= 8;
        Actor_PickUp(&this->actor, globalCtx, GI_MASK_CAPTAIN, 10000.0f, 50.0f);
    }
}

void func_80B67C1C(EnSth* this, GlobalContext* globalCtx) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x90C:
                func_80B670A4(this, 2);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x916:
            case 0x919:
                func_80B670A4(this, 3);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x8FC:
            case 0x8FD:
            case 0x900:
            case 0x90A:
            case 0x90D:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x901:
            case 0x90B:
            case 0x917:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B67B50;
                func_80B67B50(this, globalCtx);
                break;

            case 0x91A:
                gSaveContext.save.weekEventReg[34] |= 0x40;
                gSaveContext.save.weekEventReg[34] &= (u8)~8;

            case 0x902:
            case 0x903:
            case 0x90E:
            case 0x90F:
            case 0x918:
            case 0x91B:
                func_80B670A4(this, 3);

            default:
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_801477B4(globalCtx);
                this->actionFunc = func_80B67DA0;
                break;
        }
    }
}

void func_80B67DA0(EnSth* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80B67984(this, globalCtx);
        this->actionFunc = func_80B67C1C;
    } else if (func_80B6703C(this, globalCtx)) {
        this->actor.textId = 0;
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void func_80B67E20(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* this = THIS;

    if (Inventory_GetSkullTokenCount(globalCtx->sceneNum) >= 30) {
        this->actor.update = func_80B680A8;
        this->actor.draw = func_80B6849C;
        this->actor.flags |= ACTOR_FLAG_1;
    }
}

void EnSth_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSth* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_29E)) {
        this->actor.objBankIndex = this->unk_29E;
        Actor_SetObjectDependency(globalCtx, &this->actor);

        if (ENSTH_GET_100(&this->actor)) {
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_ahg_Skel_005998, &ovl_En_Sth_Anim_0045B4,
                               this->jointTable, this->morphTable, 16);
            Animation_PlayLoop(&this->skelAnime, &ovl_En_Sth_Anim_0045B4);
            this->unk_29A = 1;
            if ((gSaveContext.save.weekEventReg[34] & 0x10) || (gSaveContext.save.weekEventReg[34] & 0x20) ||
                (gSaveContext.save.weekEventReg[34] & 0x40) ||
                (Inventory_GetSkullTokenCount(globalCtx->sceneNum) >= 30)) {
                func_80B670A4(this, 3);
            }
        } else {
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_sth_Skel_0031F8, &ovl_En_Sth_Anim_003F50,
                               this->jointTable, this->morphTable, 16);
            Animation_PlayLoop(&this->skelAnime, &ovl_En_Sth_Anim_003F50);
        }

        this->actor.update = func_80B680A8;
        this->actor.draw = func_80B6849C;

        switch (ENSTH_GET_F(&this->actor)) {
            case ENSTH_F_3:
                func_80B670A4(this, 4);
                break;

            case ENSTH_F_4:
                if (gSaveContext.save.weekEventReg[13] & 0x80) {
                    func_80B670A4(this, 5);
                } else {
                    func_80B670A4(this, 5);
                }
                break;

            case ENSTH_F_5:
                func_80B670A4(this, 7);
                break;
        }

        if ((ENSTH_GET_F(&this->actor) == ENSTH_F_4) && (Inventory_GetSkullTokenCount(globalCtx->sceneNum) < 30)) {
            this->actor.update = func_80B67E20;
            this->actor.draw = NULL;
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
    }
}

void func_80B680A8(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSth* this = THIS;
    Vec3s sp38;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->actionFunc(this, globalCtx);

    if (func_80B6703C(this, globalCtx) && !(this->unk_29C & 8) && (this->unk_29A != 5)) {
        sp38.x = sp38.y = sp38.z = 0;

        func_800E9250(globalCtx, &this->actor, &this->unk_294, &sp38, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_294.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_294.y, 0, 6, 6200, 100);
    }
}

s32 func_80B681E8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnSth* this = THIS;

    if (limbIndex == 15) {
        rot->x += this->unk_294.y;
        rot->z += this->unk_294.x;
        *dList = ovl_En_Sth_DL_0034A0;
    }

    if ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13)) {
        rot->y += (s16)(Math_SinS(globalCtx->state.frames * ((limbIndex * 50) + 0x814)) * 200.0f);
        rot->z += (s16)(Math_CosS(globalCtx->state.frames * ((limbIndex * 50) + 0x940)) * 200.0f);
    }
    return false;
}

void func_80B68310(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSth* this = THIS;

    if (limbIndex == 15) {
        s32 pad;

        Matrix_MultiplyVector3fByState(&D_80B6D200, &this->actor.focus.pos);

        if (!ENSTH_GET_100(&this->actor)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, ovl_En_Sth_DL_0037C0);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        } else {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            if (this->unk_29C & 1) {
                if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_29F)) {
                    Matrix_StatePush();
                    Matrix_InsertZRotation_s(0x3A98, MTXMODE_APPLY);
                    Matrix_InsertTranslation(0.0f, 190.0f, 0.0f, MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(POLY_OPA_DISP++, 0x0A, globalCtx->objectCtx.status[this->unk_29F].segment);
                    gSPDisplayList(POLY_OPA_DISP++, object_mask_truth_DL_0001A0);

                    Matrix_StatePop();
                }
            }

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void func_80B6849C(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSth* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_EnvColor(globalCtx->state.gfxCtx, D_80B6D20C[1].r, D_80B6D20C[1].g, D_80B6D20C[1].b, 255));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 90, 110, 130, 255));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B681E8, func_80B68310, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
