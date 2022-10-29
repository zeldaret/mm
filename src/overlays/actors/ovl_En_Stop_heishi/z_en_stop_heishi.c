/*
 * File: z_en_stop_heishi.c
 * Overlay: ovl_En_Stop_heishi
 * Description: Clock Town - Gate-Blocking Soldier
 */

#include "z_en_stop_heishi.h"
#include "z64quake.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnStopheishi*)thisx)

void EnStopheishi_Init(Actor* thisx, PlayState* play);
void EnStopheishi_Destroy(Actor* thisx, PlayState* play);
void EnStopheishi_Update(Actor* thisx, PlayState* play);
void EnStopheishi_Draw(Actor* thisx, PlayState* play);

void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE85C4(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE7E9C(EnStopheishi* this);
void func_80AE854C(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE795C(EnStopheishi* this, GlobalContext* globalCtx);

const ActorInit En_Stop_heishi_InitVars = {
    ACTOR_EN_STOP_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStopheishi),
    (ActorFunc)EnStopheishi_Init,
    (ActorFunc)EnStopheishi_Destroy,
    (ActorFunc)EnStopheishi_Update,
    (ActorFunc)EnStopheishi_Draw,
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
    { 50, 260, 0, { 0, 0, 0 } },
};

u16 D_80AE88DC[] = {
    0x0516, 0x0517, 0x051A, 0x0000, 0x051C, 0x0000, 0x051E, 0x0000, 0x0520, 0x0521, 0x0524, 0x0000, 0x0526, 0x0000,
    0x0528, 0x0000, 0x052A, 0x052B, 0x052E, 0x0000, 0x0530, 0x0000, 0x0532, 0x0000, 0x0534, 0x0535, 0x0538, 0x0000,
    0x053A, 0x0000, 0x053C, 0x0000, 0x0518, 0x0519, 0x051B, 0x0000, 0x051D, 0x0000, 0x051F, 0x0000, 0x0522, 0x0523,
    0x0525, 0x0000, 0x0527, 0x0000, 0x0529, 0x0000, 0x052C, 0x052D, 0x052F, 0x0000, 0x0531, 0x0000, 0x0533, 0x0000,
    0x0536, 0x0537, 0x0539, 0x0000, 0x053B, 0x0000, 0x053D, 0x0000, 0x0514, 0x0000, 0x0560, 0x0000, 0x0562, 0x0000,
    0x0564, 0x0000, 0x0515, 0x0000, 0x0561, 0x0000, 0x0563, 0x0000, 0x0565, 0x0000,
};

u16 D_80AE897C[] = {
    0x0540, 0x0541, 0x0542, 0x0000, 0x0543, 0x0000, 0x0543, 0x0000, 0x0547, 0x0548, 0x0549, 0x0000, 0x054A, 0x0000,
    0x054B, 0x0000, 0x054F, 0x0550, 0x0551, 0x0000, 0x0552, 0x0000, 0x0553, 0x0000, 0x0557, 0x0558, 0x0559, 0x0000,
    0x055A, 0x0000, 0x055A, 0x0000, 0x0544, 0x0545, 0x0546, 0x0000, 0x0546, 0x0000, 0x0546, 0x0000, 0x054C, 0x054D,
    0x054E, 0x0000, 0x054E, 0x0000, 0x054E, 0x0000, 0x0554, 0x0555, 0x0556, 0x0000, 0x0556, 0x0000, 0x0556, 0x0000,
    0x055B, 0x055C, 0x055D, 0x0000, 0x055D, 0x0000, 0x055D, 0x0000, 0x053E, 0x0000, 0x053E, 0x0000, 0x053E, 0x0000,
    0x053E, 0x0000, 0x053F, 0x0000, 0x053F, 0x0000, 0x053F, 0x0000, 0x053F, 0x0000,
};

static AnimationHeader* sAnimations[] = {
    &gSoldierLookDown,       &gSoldierComeUpHere,     &gSoldierStandHandOnHip, &gSoldierStandAndLookDown,
    &object_sdn_Anim_0057BC, &object_sdn_Anim_005D28, &object_sdn_Anim_0064C0, &gSoldierStandWithHandOnChest,

};

void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gSoldierSkeleton, &gSoldierStandHandOnHip, this->limbDrawTable,
                       this->transitionDrawTable, 17);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_276 = ((this->actor.params >> 0xC) & 0xF);
    this->switchFlag = (this->actor.params & 0x3F);
    this->unk_288 = (this->actor.world.rot.z * 40.0f) + 50.0f;
    this->actor.world.rot.z = 0;
    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }
    if ((this->switchFlag >= 0) && (Flags_GetSwitch(globalCtx, this->switchFlag) != 0)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actor.targetMode = 0;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_280 = this->actor.world.rot.y;
    this->unk_284 = 6;
    func_80AE7E9C(this);
}

void EnStopheishi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnStopHeishi_ChangeAnim(EnStopheishi* this, s32 animIndex) {
    s32 mode;
    f32 morphFrames;

    this->unk_268 = animIndex;
    this->currentAnimFrameCount = Animation_GetLastFrame(sAnimations[animIndex]);
    mode = 2;
    morphFrames = -10.0f;
    if ((animIndex >= 2) && (animIndex != 4)) {
        mode = 0;
    }
    if (animIndex == 5) {
        morphFrames = 0.0f;
    }
    Animation_Change(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->currentAnimFrameCount, mode, morphFrames);
}

void func_80AE75C8(EnStopheishi* this, GlobalContext* globalCtx) {
    s32 yawDiff;
    Player* player;
    Vec3f playerPos;

    yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));

    this->unk_260 = 0;

    if (this->actor.xzDistToPlayer < 200.0f) {
        player = GET_PLAYER(globalCtx);
        if (yawDiff < 0x4E20) {
            this->unk_260 = (this->actor.yawTowardsPlayer - this->actor.world.rot.y);
            if (this->unk_260 >= 0x2711) {
                this->unk_260 = 0x2710;
            } else if (this->unk_260 < -0x2710) {
                this->unk_260 = -0x2710;
            }
        }

        Math_Vec3f_Copy(&playerPos, &player->actor.world.pos);

        if ((player->transformation == PLAYER_FORM_DEKU) || (player->transformation == PLAYER_FORM_HUMAN)) {
            playerPos.y += (57.0f + BREG(34));
        } else {
            playerPos.y += (70.0f + BREG(35));
        }
        this->pitchToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &playerPos);
    }
}

void func_80AE7718(EnStopheishi* this) {
    if (this->unk_272 != 0) {
        this->unk_272--;
    }
    this->pitchToPlayer = -0xBB8;
    this->unk_260 = 0;
    if (this->unk_284 < 6) {
        this->unk_260 = 0x1770;
        if (!(this->unk_284 & 7)) {
            this->unk_260 = -0x1770;
        }
        if (this->unk_272 == 0) {
            this->unk_284++;
            this->unk_272 = 10;
            if (this->unk_284 >= 6) {
                this->unk_272 = 50;
            }
        }
    } else if ((this->unk_272 == 0) && (Quake_NumActiveQuakes() != 0) && (this->unk_284 >= 6)) {
        this->unk_284 = 0;
    }
}

void func_80AE77D4(EnStopheishi* this) {
    this->unk_274 = 0;
    this->unk_28C = 0.0f;
    this->unk_280 = this->actor.home.rot.y;
    if (this->unk_270 == 1) {
        this->pitchToPlayer = 0;
        EnStopHeishi_ChangeAnim(this, 5);
    }
    if ((this->unk_270 == 0) && (this->unk_264 == 0)) {
        if ((fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 3.0f) ||
            (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 3.0f)) {
            this->skelAnime.playSpeed = 3.0f;
            Math_ApproachF(&this->actor.world.pos.x, this->actor.home.pos.x, 0.3f, 5.0f);
            Math_ApproachF(&this->actor.world.pos.z, this->actor.home.pos.z, 0.3f, 5.0f);
        } else {
            this->unk_264 = 1;
        }
    }
    if ((this->unk_268 != 2) && (this->unk_268 != 3) && (this->unk_268 != 7) && (this->unk_264 != 0)) {
        this->skelAnime.playSpeed = 1.0f;
        EnStopHeishi_ChangeAnim(this, 2);
        if ((gSaveContext.save.day != 3) && (gSaveContext.save.isNight != 0)) {
            EnStopHeishi_ChangeAnim(this, 3);
        }
        if (gSaveContext.save.day == 3) {
            EnStopHeishi_ChangeAnim(this, 7);
        }
    }
}

void func_80AE795C(EnStopheishi* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f newPos;
    f32 xDiff;
    f32 zDiff;
    f32 playSpeed;
    s16 yaw;
    s16 rotY;

    
    if (ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.home.rot.y)) < 0x2000) {
        this->unk_280 = this->actor.yawTowardsPlayer;
    }
    playSpeed =
        fabsf((f32)this->actor.yawTowardsPlayer - Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos)) *
        0.01f * 5.0f;
    if (this->unk_274 != 4) {
        this->skelAnime.playSpeed = CLAMP(playSpeed, 1.0f, 5.0f);
    }
    yaw = Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos);
    xDiff = fabsf(this->actor.home.pos.x - player->actor.world.pos.x);
    zDiff = fabsf(this->actor.home.pos.z - player->actor.world.pos.z);
    Math_Vec3f_Copy(&newPos, &this->actor.home.pos);
    rotY = this->actor.home.rot.y;

    if (rotY == -0x8000) {
        if (yaw > 0) {
            xDiff = Math_SinS(this->actor.home.rot.y + 0xC000) * xDiff;
            zDiff = Math_CosS(this->actor.home.rot.y + 0xC000) * zDiff;
        } else {
            xDiff = Math_SinS(this->actor.home.rot.y + 0x4000) * xDiff;
            zDiff = Math_CosS(this->actor.home.rot.y + 0x4000) * zDiff;
        }
    } else if (yaw < rotY) {
        xDiff = Math_SinS(this->actor.home.rot.y + 0xC000) * xDiff;
        zDiff = Math_CosS(this->actor.home.rot.y + 0xC000) * zDiff;
    } else {
        xDiff = Math_SinS(this->actor.home.rot.y + 0x4000) * xDiff;
        zDiff = Math_CosS(this->actor.home.rot.y + 0x4000) * zDiff;
    }

    if (this->unk_288 < xDiff) {
        xDiff = this->unk_288;
    } else if (xDiff < -this->unk_288) {
        xDiff = -this->unk_288;
    }
    if (this->unk_288 < zDiff) {
        zDiff = this->unk_288;
    } else if (zDiff < -this->unk_288) {
        zDiff = -this->unk_288;
    }
    newPos.x += xDiff;
    newPos.z += zDiff;
    Math_ApproachF(&this->actor.world.pos.x, newPos.x, 0.5f, this->unk_28C);
    Math_ApproachF(&this->actor.world.pos.z, newPos.z, 0.5f, this->unk_28C);
    Math_ApproachF(&this->unk_28C, 50.0f, 0.3f, 1.0f);

    switch (this->unk_274) {
        case 0:
            if (gSaveContext.save.day != 3) {
                EnStopHeishi_ChangeAnim(this, 4);
                this->unk_274 = 2;
            } else {
                EnStopHeishi_ChangeAnim(this, 2);
                this->unk_274 = 1;
            }
            break;
        case 1:
            EnStopHeishi_ChangeAnim(this, 4);
            this->unk_274 = 2;
            break;
        case 2:
            if (this->currentAnimFrameCount <= curFrame) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
        case 3:
            if ((fabsf(this->actor.world.pos.x - newPos.x) < 2.0f) &&
                (fabsf(this->actor.world.pos.z - newPos.z) < 2.0f)) {
                this->skelAnime.playSpeed = 1.0f;
                EnStopHeishi_ChangeAnim(this, 6);
                this->unk_274 = 4;
            }
            break;
        case 4:
            if ((fabsf(this->actor.world.pos.x - newPos.x) > 4.0f) ||
                (fabsf(this->actor.world.pos.z - newPos.z) > 4.0f)) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
    }
    this->unk_264 = 0;
    this->unk_270 = 0x14;
    this->pitchToPlayer = 0;
    if (this->unk_276 == 3) {
        Math_Vec3f_Copy(&newPos, &player->actor.world.pos);
        if ((player->transformation == 3) || (player->transformation == 4)) {
            newPos.y += 77.0f + BREG(37);
            this->pitchToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &newPos);
        }
    }
}

void func_80AE7E9C(EnStopheishi* this) {
    EnStopHeishi_ChangeAnim(this, 2);
    if ((gSaveContext.save.day != 3) && (gSaveContext.save.isNight != 0)) {
        EnStopHeishi_ChangeAnim(this, 3);
    }
    if (gSaveContext.save.day == 3) {
        EnStopHeishi_ChangeAnim(this, 7);
    }
    this->unk_274 = 0;
    this->unk_278 = 0;
    this->actionFunc = func_80AE7F34;
    this->actor.speedXZ = 0.0f;
}

void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp32;
    s16 phi_a2;
    s32 yawDiffAbs;
    s16 yawDiff;
    f32 xDiff;
    f32 zDiff;

    SkelAnime_Update(&this->skelAnime);
    if ((this->unk_268 == 5) && (((s16)this->skelAnime.curFrame & 1) != 0)) {
        Actor_PlaySfxAtPos(&this->actor, 0x2931U);
    }
    if (gSaveContext.save.day != 3) {
        func_80AE75C8(this, globalCtx);
    } else {
        func_80AE7718(this);
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_280, 1, 0x1388, 0);

    sp32 = 0;
    if (gSaveContext.save.isNight != 0) {
        sp32 = 0x20;
    }

    phi_a2 = 0;
    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            if ((STOLEN_ITEM_1 == SLOT_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_1 == ITEM_SWORD_KOKIRI) ||
                (STOLEN_ITEM_1 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_1 == ITEM_SWORD_GILDED) ||
                (STOLEN_ITEM_2 == SLOT_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_2 == ITEM_SWORD_KOKIRI) ||
                (STOLEN_ITEM_2 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_2 == ITEM_SWORD_GILDED)) {
                if (this->unk_265 != 0) {
                    phi_a2 = 1;
                }
            } else if ((gSaveContext.save.weekEventReg[0xC] & 0x20) != 0) {
                phi_a2 = 1;
            }
            break;
        case PLAYER_FORM_DEKU:
            phi_a2 = 4;
            break;
        case PLAYER_FORM_ZORA:
            phi_a2 = 3;
            break;
        case PLAYER_FORM_GORON:
            phi_a2 = 2;
            break;
    }

    if (((phi_a2 == 1) || (phi_a2 == 2) || (phi_a2 == 3)) &&
        (((this->unk_268 == 4)) || (this->unk_268 == 5) || (this->unk_268 == 6))) {
        EnStopHeishi_ChangeAnim(this, 2);
        if ((gSaveContext.save.day != 3) && (gSaveContext.save.isNight != 0)) {
            EnStopHeishi_ChangeAnim(this, 3);
        }
        if (gSaveContext.save.day == 3) {
            EnStopHeishi_ChangeAnim(this, 7);
        }
    }

    if ((phi_a2 == 0) || (phi_a2 == 4)) {
        xDiff = this->actor.home.pos.x - player->actor.world.pos.x;
        zDiff = this->actor.home.pos.z - player->actor.world.pos.z;
        this->collider.dim.radius = 0x32;
        this->collider.dim.height = 0x104;
        if (sqrtf(SQ(xDiff) + SQ(zDiff)) < 240.0f) {
            func_80AE795C(this, globalCtx);
        } else {
            func_80AE77D4(this);
        }
    } else {
        this->collider.dim.radius = 0xF;
        this->collider.dim.height = 0x3C;
    }
    if (phi_a2 != 4) {
        this->unk_27C = this->unk_276 * 8;
        this->unk_27C += sp32;
        this->unk_27C += phi_a2 * 2;
    } else {
        this->unk_27C = 0x40;
        if (sp32 != 0) {
            this->unk_27C = 0x48;
        }
        this->unk_27C += this->unk_276 * 2;
    }
    if (gSaveContext.save.day != 3) {
        this->actor.textId = D_80AE88DC[this->unk_27C];
        this->unk_27E = D_80AE88DC[this->unk_27C + 1];
    } else {
        this->actor.textId = D_80AE897C[this->unk_27C];
        this->unk_27E = D_80AE897C[this->unk_27C + 1];
    }
    if (this->unk_27E != 0) {
        if ((STOLEN_ITEM_1 == ITEM_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_1 == ITEM_SWORD_KOKIRI) ||
            (STOLEN_ITEM_1 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_1 == ITEM_SWORD_GILDED) ||
            (STOLEN_ITEM_2 == ITEM_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_2 == ITEM_SWORD_KOKIRI) ||
            (STOLEN_ITEM_2 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_2 == ITEM_SWORD_GILDED)) {
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x56C;
            } else if (this->actor.textId == 0x520) {
                this->actor.textId = 0x56E;
            } else if (this->actor.textId == 0x52A) {
                this->actor.textId = 0x570;
            } else if (this->actor.textId == 0x534) {
                this->actor.textId = 0x572;
            } else if (this->actor.textId == 0x518) {
                this->actor.textId = 0x56D;
            } else if (this->actor.textId == 0x522) {
                this->actor.textId = 0x56F;
            } else if (this->actor.textId == 0x52C) {
                this->actor.textId = 0x571;
            } else if (this->actor.textId == 0x536) {
                this->actor.textId = 0x573;
            }
        } else if (GET_CUR_EQUIP_VALUE(EQUIP_SWORD) == 0) {
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x55E;
            } else if (this->actor.textId == 0x520) {
                this->actor.textId = 0x566;
            } else if (this->actor.textId == 0x52A) {
                this->actor.textId = 0x568;
            } else if (this->actor.textId == 0x534) {
                this->actor.textId = 0x56A;
            } else if (this->actor.textId == 0x518) {
                this->actor.textId = 0x55F;
            } else if (this->actor.textId == 0x522) {
                this->actor.textId = 0x567;
            } else if (this->actor.textId == 0x52C) {
                this->actor.textId = 0x569;
            } else if (this->actor.textId == 0x536) {
                this->actor.textId = 0x56BU;
            }
        }
    }
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    if (yawDiff < 0) {
        yawDiffAbs = -yawDiff;
    } else {
        yawDiffAbs = yawDiff;
    }
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
        this->skelAnime.playSpeed = 1.0f;
        func_80AE854C(this, globalCtx);
    } else if (yawDiffAbs < 0x4BB9) {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80AE854C(EnStopheishi* this, GlobalContext* globalCtx) {
    if (((this->unk_265 != 0) || (gSaveContext.save.weekEventReg[0xC] & 0x20)) && (this->unk_268 != 2)) {
        EnStopHeishi_ChangeAnim(this, 2);
    }
    this->pitchToPlayer = 0;
    this->unk_274 = 0;
    this->unk_278 = 1;
    this->actionFunc = func_80AE85C4;
}

void func_80AE85C4(EnStopheishi* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    func_80AE75C8(this, globalCtx);
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && (Message_ShouldAdvance(globalCtx) != 0)) {
        if (this->unk_27E != 0) {
            this->actor.textId = this->unk_27E;
            func_80151938(globalCtx, this->actor.textId);
            EnStopHeishi_ChangeAnim(this, 2);
            gSaveContext.save.weekEventReg[0xC] |= 0x20;
            this->unk_265 = 1;
            this->unk_27E = 0;
            return;
        }
        func_801477B4(globalCtx);
        func_80AE7E9C(this);
    }
}

void EnStopheishi_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = (EnStopheishi*)thisx;
    s32 pad;

    if (this->unk_270 != 0) {
        this->unk_270 = this->unk_270 - 1;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->unk_25A, this->unk_260, 1, 0x7D0, 0);
    Math_SmoothStepToS(&this->unk_258, this->pitchToPlayer, 1, 0x7D0, 0);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.uncullZoneForward = 500.0f;
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk_290);
    Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    if (this->unk_278 == 0) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 func_80AE87A4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnStopheishi* this = THIS;

    if (limbIndex == OBJECT_SDN_LIMB_10) {
        rot->x += this->unk_25A;
        rot->z += this->unk_258;
    }
    return 0;
}

void func_80AE87EC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnStopheishi* this = THIS;

    if (limbIndex == OBJECT_SDN_LIMB_10) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_290);
    }
}

void EnStopheishi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          (s32)this->skelAnime.dListCount, func_80AE87A4, func_80AE87EC, &this->actor);
}
