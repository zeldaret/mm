/*
 * File: z_en_stone_heishi.c
 * Overlay: ovl_En_Stone_heishi
 * Description: Shiro
 */

#include "z_en_stone_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80)

#define THIS ((EnStoneheishi*)thisx)

void EnStoneheishi_Init(Actor* thisx, PlayState* play);
void EnStoneheishi_Destroy(Actor* thisx, PlayState* play);
void EnStoneheishi_Update(Actor* thisx, PlayState* play);
void EnStoneheishi_Draw(Actor* thisx, PlayState* play);

void func_80BC9560(EnStoneheishi* this, PlayState* play);
void func_80BC9680(EnStoneheishi* this, PlayState* play);
void EnStoneheishi_CheckGivenItem(EnStoneheishi* this, PlayState* play);
void EnStoneheishi_DrinkBottleProcess(EnStoneheishi* this, PlayState* play);
void func_80BC9D28(EnStoneheishi* this, PlayState* play);
void func_80BC9E50(EnStoneheishi* this, PlayState* play);
void func_80BC94B0(EnStoneheishi* this);
void func_80BC9660(EnStoneheishi* this);
void func_80BC98EC(EnStoneheishi*);
void EnStoneheishi_GiveItemPrize(EnStoneheishi* this, PlayState* play);
void EnStoneheishi_SetupDrinkBottleProcess(EnStoneheishi* this);

const ActorInit En_Stone_heishi_InitVars = {
    ACTOR_EN_STONE_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStoneheishi),
    (ActorFunc)EnStoneheishi_Init,
    (ActorFunc)EnStoneheishi_Destroy,
    (ActorFunc)EnStoneheishi_Update,
    (ActorFunc)EnStoneheishi_Draw,
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
    { 15, 70, 0, { 0, 0, 0 } },
};

static u16 sEnStoneHeishiTextIds[] = { 0x1473, 0x1474, 0x1475, 0x1476, 0x1477, 0x1478, 0x1479, 0x147A, 0x1472 };

static AnimationHeader* sEnStoneHeishiAnimationInfoS[] = {
    &gSoldierStandHandOnHip, &gSoldierDrink, &gSoldierCheerWithSpear, &gSoldierWave,
    &gSoldierSitAndReach,    &gSoldierDrink, &gSoldierStandUp,
};

static u8 sEnStoneHeishiAnimations[] = { 0, 2, 0, 0, 0, 0, 2 };

void EnStoneheishi_Init(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gSoldierSkel, &gSoldierWave, this->jointTable, this->morphTable,
                       SOLDIER_LIMB_MAX);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->collider.dim.radius = 0x28;
    this->collider.dim.height = 0x28;
    this->collider.dim.yShift = 0;

    func_80BC94B0(this);
}

void EnStoneheishi_Destroy(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnStoneheishi_SetAnimation(EnStoneheishi* this, s32 animIndex) {
    f32 startFrame = 0.0f;

    this->animIndex = animIndex;
    this->endFrame = Animation_GetLastFrame(sEnStoneHeishiAnimationInfoS[animIndex]);

    if (animIndex == EN_STONE_HEISHI_DRINK_2) { // This will never pass since this animation index is never used.
        startFrame = 55.0f;
    }

    Animation_Change(&this->skelAnime, sEnStoneHeishiAnimationInfoS[this->animIndex], 1.0f, startFrame, this->endFrame,
                     sEnStoneHeishiAnimations[this->animIndex], -10.0f);
}

void EnStoneheishi_HeadTowardsLink(EnStoneheishi* this) {
    s16 yawDiff;
    s32 absYawDiff;

    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    absYawDiff = ABS_ALT(yawDiff);

    this->targetHeadPosX = 0;

    if ((this->actor.xzDistToPlayer < 200.0f) && (absYawDiff < 0x4E20)) {
        this->targetHeadPosX = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
        if (this->targetHeadPosX >= 0x2711) {
            this->targetHeadPosX = 0x2710;
        } else {
            if (this->targetHeadPosX < -0x2710) {
                this->targetHeadPosX = -0x2710;
            }
        }
    }
}

void func_80BC94B0(EnStoneheishi* this) {
    this->textIndex = 0;
    if (gSaveContext.save.weekEventReg[0x29] & 0x40) { // After drinking bottle
        EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_CHEER_WITH_SPEAR);
        this->textIndex = 8;
        this->actor.flags &= ~ACTOR_FLAG_80;
    } else { // Initial configuration
        EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_WAVE);
        if (gSaveContext.save.weekEventReg[0x29] & 0x80) {
            this->textIndex = 2;
        }
    }
    this->actor.textId = sEnStoneHeishiTextIds[this->textIndex];
    this->action = 0;
    this->actionFunc = func_80BC9560;
}

void func_80BC9560(EnStoneheishi* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 yawDiff;
    s32 absYawDiff;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BC9660(this);
        return;
    }

    if ((!(gSaveContext.save.weekEventReg[0x29] & 0x40)) && (play->actorCtx.unk4 != 0x64)) {
        this->actor.flags |= ACTOR_FLAG_8000000;
        return;
    }

    SkelAnime_Update(&this->skelAnime);

    this->actor.flags &= ~ACTOR_FLAG_8000000;
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    absYawDiff = ABS_ALT(yawDiff);

    if (absYawDiff < 0x18F1 && ((s32)(player->stateFlags1 << 8) >= 0)) {
        func_800B8614(&this->actor, play, 70.0f);
    }
}

void func_80BC9660(EnStoneheishi* this) {
    this->textIdSet = false;
    this->action = 1;
    this->actionFunc = func_80BC9680;
}

void func_80BC9680(EnStoneheishi* this, PlayState* play) {
    f32 currentFrame = this->skelAnime.curFrame;

    if (this->textIndex == 0 || this->textIndex == 2) {
        if (this->animIndex != EN_STONE_HEISHI_SIT_AND_REACH) {
            if (fabsf(this->headRotY - this->targetHeadPosY) < 50.0f) {
                EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_SIT_AND_REACH);
            }
            return;
        }
    } else if (this->textIndex == 3) {
        if (this->animIndex != EN_STONE_HEISHI_WAVE) {
            if ((this->timer == 0) && (fabsf((f32)(this->headRotY - this->targetHeadPosY)) < 50.0f)) {
                EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_WAVE);
            }
            return;
        } else if (!this->textIdSet && (this->endFrame <= currentFrame)) {
            Player* player = GET_PLAYER(play);

            this->textIdSet = true;
            player->actor.textId = sEnStoneHeishiTextIds[this->textIndex];

            func_80151938(play, sEnStoneHeishiTextIds[this->textIndex]);
            func_80151BB4(play, 0x12);
        }
    }

    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);

        if (this->textIndex == 2) {
            func_80151938(play, 0xFF);
            func_80BC98EC(this);
            return;
        }
        if (this->textIndex == 3) {
            func_80BC94B0(this);
            return;
        }
        if (this->textIndex == 6) {
            EnStoneheishi_GiveItemPrize(this, play);
            return;
        }
        if (this->textIndex < 7) {
            this->textIndex++;
        } else {
            func_80151BB4(play, 0x12);
            func_80BC94B0(this);
            return;
        }

        func_80151938(play, sEnStoneHeishiTextIds[this->textIndex]);
    }
}

void func_80BC98EC(EnStoneheishi* this) {
    this->action = 2;
    this->actionFunc = EnStoneheishi_CheckGivenItem;
}

void EnStoneheishi_CheckGivenItem(EnStoneheishi* this, PlayState* play) {
    s32 item;

    SkelAnime_Update(&this->skelAnime);

    if (Message_GetState(&play->msgCtx) == TEXT_STATE_16) {
        item = func_80123810(play);
        if (item > PLAYER_AP_NONE) {
            this->timer = 40;
            func_801477B4(play);

            if ((item == PLAYER_AP_BOTTLE_POTION_RED) || (item == PLAYER_AP_BOTTLE_POTION_BLUE)) {
                this->playerGivesBluePotion = false;
                if (item == PLAYER_AP_BOTTLE_POTION_BLUE) {
                    this->playerGivesBluePotion = true;
                }
                EnStoneheishi_SetupDrinkBottleProcess(this);
            } else {
                Player* player = GET_PLAYER(play);

                this->textIndex = 3;
                player->actor.textId = 0;
                gSaveContext.save.weekEventReg[0x29] |= 0x80;
                this->action = 1;
                this->actionFunc = func_80BC9680;
            }
        } else if (item < PLAYER_AP_NONE) {
            func_801477B4(play);
            func_80151BB4(play, 0x12);
            func_80BC94B0(this);
        }
    }
}

void EnStoneheishi_SetupDrinkBottleProcess(EnStoneheishi* this) {
    this->action = 3;
    this->actionFunc = EnStoneheishi_DrinkBottleProcess;
}

void EnStoneheishi_DrinkBottleProcess(EnStoneheishi* this, PlayState* play) {
    f32 currentFrame = this->skelAnime.curFrame;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);

    switch (this->DrinkBottleState) {
        case EN_STONE_DRINK_BOTTLE_INITIAL:
            if (this->timer == 0) {
                this->textIndex = 4;
                func_80151938(play, sEnStoneHeishiTextIds[this->textIndex]);
                player->actor.textId = sEnStoneHeishiTextIds[this->textIndex];
                this->DrinkBottleState++;
            }

        default:
            return;

        case EN_STONE_DRINK_BOTTLE_DRINKING:
            if (Message_GetState(&play->msgCtx) == TEXT_STATE_5 && Message_ShouldAdvance(play)) {
                Player* player = GET_PLAYER(play);

                play->msgCtx.msgLength = 0;
                player->actor.textId = 0;
                player->exchangeItemId = 0;
                this->bottleDisplay = EN_STONE_BOTTLE_RED_POTION;

                if (this->playerGivesBluePotion) {
                    this->bottleDisplay = EN_STONE_BOTTLE_BLUE_POTION;
                }

                Player_SetModels(player, 3);
                EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_DRINK_1);
                this->timer = 30;
                this->DrinkBottleState++;
            }
            break;

        case EN_STONE_DRINK_BOTTLE_EMPTY:
            if (this->timer != 0) {
                if (this->timer < 10 && (this->bottleDisplay != EN_STONE_BOTTLE_EMPTY)) {
                    this->bottleDisplay = EN_STONE_BOTTLE_EMPTY;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_NP_DRINK);
                    func_80123D50(play, GET_PLAYER(play), ITEM_BOTTLE, PLAYER_AP_BOTTLE);
                }
            } else {
                this->DrinkBottleState++;
            }
            break;

        case EN_STONE_DRINK_BOTTLE_STAND_UP:
            if (this->endFrame <= currentFrame) {
                func_801A3098(0x922);
                this->bottleDisplay = EN_STONE_BOTTLE_NONE;
                EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_STAND_UP);
                this->DrinkBottleState++;
            }
            break;

        case EN_STONE_DRINK_BOTTLE_STANDING:
            if (this->endFrame <= currentFrame) {
                this->textIndex = 5;
                func_80151938(play, sEnStoneHeishiTextIds[this->textIndex]);
                player->actor.textId = sEnStoneHeishiTextIds[this->textIndex];
                EnStoneheishi_SetAnimation(this, EN_STONE_HEISHI_STAND_HAND_ON_HIP);
                this->action = 1;
                this->actionFunc = func_80BC9680;
            }
            break;
    }
}

void EnStoneheishi_GiveItemPrize(EnStoneheishi* this, PlayState* play) {
    func_801477B4(play);

    if (gSaveContext.save.inventory.items[gItemSlots[0x45]] == 0x45) {
        Actor_PickUp(&this->actor, play, GI_RUPEE_BLUE, 300.0f, 300.0f);
    } else {
        Actor_PickUp(&this->actor, play, GI_MASK_STONE, 300.0f, 300.0f);
    }

    this->action = 4;
    this->actionFunc = func_80BC9D28;
}

void func_80BC9D28(EnStoneheishi* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->textIndex++;
        this->actor.textId = sEnStoneHeishiTextIds[this->textIndex];
        gSaveContext.save.weekEventReg[0x29] |= 0x40;
        Actor_ProcessTalkRequest(&this->actor, &play->state);
        func_800B8500(&this->actor, play, 400.0f, 400.0f, PLAYER_AP_MINUS1);
        this->actionFunc = func_80BC9E50;
    } else if (gSaveContext.save.inventory.items[gItemSlots[0x45]] == 0x45) {
        Actor_PickUp(&this->actor, play, GI_RUPEE_BLUE, 300.0f, 300.0f);
    } else {
        Actor_PickUp(&this->actor, play, GI_MASK_STONE, 300.0f, 300.0f);
    }
}

void func_80BC9E50(EnStoneheishi* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80151BB4(play, 0x35);
        func_80151BB4(play, 0x12);
        this->action = 1;
        this->actionFunc = func_80BC9680;
    } else {
        func_800B8500(&this->actor, play, 400.0f, 400.0f, PLAYER_AP_MINUS1);
    }
}

void EnStoneheishi_Update(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (this->timer != 0) {
        this->timer--;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 50.0f, 29);
    Actor_SetScale(&this->actor, 0.01f);

    if (((gSaveContext.save.weekEventReg[0x29] & 0x40) || play->actorCtx.unk4 == 100) &&
        (((s32)player->stateFlags1 << 8) >= 0)) {
        if ((this->animIndex != EN_STONE_HEISHI_WAVE) &&
            ((((this->action == 0) || (this->action == 1)) || (this->action == 2)) ||
             ((this->action == 3) && (this->DrinkBottleState <= EN_STONE_DRINK_BOTTLE_DRINKING)))) {
            EnStoneheishi_HeadTowardsLink(this);
        } else {
            this->targetHeadPosX = 0;
        }

        if (!(gSaveContext.save.weekEventReg[0x29] & 0x40)) {
            Actor_SetFocus(&this->actor, 30.0f);
        } else {
            Actor_SetFocus(&this->actor, 60.0f);
        }

        Math_SmoothStepToS(&this->headRotX, this->targetHeadPosX, 1, 0xBB8, 0);
        Math_SmoothStepToS(&this->headRotY, this->targetHeadPosY, 1, 0x3E8, 0);

        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

s32 EnStoneheishi_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                                   Gfx** gfx) {
    EnStoneheishi* this = THIS;

    if (limbIndex == SOLDIER_LIMB_HEAD) {
        rot->x += this->headRotX;
        rot->y += this->headRotY;
        rot->z += this->headRotZ;
    }

    return false;
}

void EnStoneheishi_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80BCA404 = { 0.0f, 0.0f, 0.0f };
    EnStoneheishi* this = THIS;
    Gfx* gfx2;

    if (limbIndex == SOLDIER_LIMB_LEFT_HAND && this->bottleDisplay != EN_STONE_BOTTLE_NONE) {
        gfx2 = func_8012C2B4(*gfx);

        D_80BCA404.x = 320.0f;
        D_80BCA404.y = 210.0f;
        D_80BCA404.z = 440.0f;

        Matrix_Translate(D_80BCA404.x, D_80BCA404.y, D_80BCA404.z, MTXMODE_APPLY);

        gDPPipeSync(gfx2++);

        Matrix_RotateYS(-0x1770, MTXMODE_APPLY);
        Matrix_RotateXS(0x7D0, MTXMODE_APPLY);
        Matrix_RotateZS(-0x7530, MTXMODE_APPLY);

        if (this->bottleDisplay != EN_STONE_BOTTLE_EMPTY) {
            if (this->bottleDisplay == EN_STONE_BOTTLE_BLUE_POTION) {
                gDPSetEnvColor(gfx2++, 0, 0, 200, 0); // Blue Potion
            } else {
                gDPSetEnvColor(gfx2++, 200, 0, 0, 0); // Red Potion
            }
            gSPMatrix(gfx2++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx2++, gSoldierBottleContentsDL);
        }

        gSPMatrix(gfx2++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx2++, gSoldierBottleDL);

        *gfx = gfx2++;
    }
}

void EnStoneheishi_Draw(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (!(gSaveContext.save.weekEventReg[0x29] & 0x40)) {
        func_8012C2DC(play->state.gfxCtx);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnStoneheishi_OverrideLimbDraw, EnStoneheishi_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    } else {
        func_8012C28C(play->state.gfxCtx);

        POLY_OPA_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnStoneheishi_OverrideLimbDraw, EnStoneheishi_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
