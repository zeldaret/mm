/*
 * File: z_en_pr2.c
 * Overlay: ovl_En_Pr2
 * Description: Skullfish
 */

#include "z_en_pr2.h"
#include "objects/object_pr/object_pr.h"
#include "overlays/actors/ovl_En_Encount1/z_en_encount1.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnPr2*)thisx)

void EnPr2_Init(Actor* thisx, PlayState* play);
void EnPr2_Destroy(Actor* thisx, PlayState* play);
void EnPr2_Update(Actor* thisx, PlayState* play);
void EnPr2_Draw(Actor* thisx, PlayState* play);

void func_80A745C4(EnPr2* this);
void func_80A745FC(EnPr2* this, PlayState* play);
void func_80A74888(EnPr2* this);
void func_80A748E8(EnPr2* this, PlayState* play);
void func_80A74DEC(EnPr2* this, PlayState* play);
void func_80A74E90(EnPr2* this, PlayState* play);
void func_80A751B4(EnPr2* this);
void func_80A75310(EnPr2* this, PlayState* play);

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(2, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x08, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 17, 32, -10, { 0, 0, 0 } },
};

ActorInit En_Pr2_InitVars = {
    /**/ ACTOR_EN_PR2,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_PR,
    /**/ sizeof(EnPr2),
    /**/ EnPr2_Init,
    /**/ EnPr2_Destroy,
    /**/ EnPr2_Update,
    /**/ EnPr2_Draw,
};

static AnimationHeader* sAnimations[] = {
    &object_pr_Anim_004340,
    &object_pr_Anim_004274,
    &object_pr_Anim_003904,
};

u8 D_80A75C38[] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP };

s16 D_80A75C3C[] = {
    0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0,
};

void EnPr2_Init(Actor* thisx, PlayState* play) {
    EnPr2* this = THIS;

    this->actor.targetMode = TARGET_MODE_3;
    this->actor.hintId = TATL_HINT_ID_SKULLFISH;
    this->unk_1EC = 255;
    this->actor.colChkInfo.health = 1;
    this->actor.colChkInfo.damageTable = &sDamageTable;

    SkelAnime_InitFlex(play, &this->skelAnime, &object_pr_Skel_004188, &object_pr_Anim_004340, this->jointTable,
                       this->morphTable, 5);
    this->unk_1E0 = ENPR2_GET_F(&this->actor);
    this->actor.colChkInfo.mass = 10;
    Math_Vec3f_Copy(&this->unk_228, &this->actor.home.pos);

    if (this->unk_1E0 == 2) {
        this->unk_208 = ENPR2_GET_FF0(&this->actor) * 20.0f;
    }
    this->unk_1F4 = 255;
    this->actor.shape.yOffset = 500.0f;
    this->actor.shape.shadowScale = 12.0f;

    if (this->unk_1E0 < 10) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
        Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
        this->unk_218 = -1;
        this->unk_204 = 0.0f;

        if (this->actor.parent != NULL) {
            Actor* parent = this->actor.parent;

            if (parent->update != NULL) {
                if (parent->world.rot.y != 0) {
                    this->unk_218 = parent->world.rot.y - 1;
                }
            }
        } else if (this->actor.world.rot.z != 0) {
            this->unk_218 = this->actor.world.rot.z - 1;
            this->actor.world.rot.z = 0;
        }

        if (this->unk_1E0 == 3) {
            if (this->actor.parent != NULL) {
                Actor* parent = this->actor.parent;

                if (parent->update != NULL) {
                    this->pathIndex = ((EnEncount1*)parent)->pathIndex;
                    this->path = SubS_GetPathByIndex(play, this->pathIndex, ENPR2_PATH_INDEX_NONE);
                    this->unk_208 = parent->world.rot.z * 20.0f;
                    if (this->unk_208 < 20.0f) {
                        this->unk_208 = 20.0f;
                    }
                }
                func_80A745C4(this);
            } else {
                Actor_Kill(&this->actor);
                return;
            }
        } else {
            func_80A74888(this);
        }
    } else {
        this->unk_204 = 0.02f;
        func_80A751B4(this);
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 20.0f, 20.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 |
                                UPDBGCHECKINFO_FLAG_10);

    if (!(this->actor.bgCheckFlags & (BGCHECKFLAG_WATER | BGCHECKFLAG_WATER_TOUCH))) {
        Actor_Kill(&this->actor);
    }
}

void EnPr2_Destroy(Actor* thisx, PlayState* play) {
    EnPr2* this = THIS;

    if (this->unk_1E0 < 10) {
        Collider_DestroyCylinder(play, &this->collider);
    }

    if (this->actor.parent != NULL) {
        EnEncount1* encount1 = (EnEncount1*)this->actor.parent;

        if ((encount1->actor.update != NULL) && (encount1->spawnActiveCount > 0)) {
            encount1->spawnActiveCount--;
        }
    }
}

s32 func_80A7429C(EnPr2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp1A;
    s16 sp18;

    Actor_GetScreenPos(play, &this->actor, &sp1A, &sp18);

    if ((fabsf(player->actor.world.pos.y - this->actor.world.pos.y) > 160.0f) ||
        (this->actor.projectedPos.z < -40.0f) || (sp1A < 0) || (sp1A > 320) || (sp18 < 0) || (sp18 > 240)) {
        return false;
    }

    if (!(player->stateFlags1 & PLAYER_STATE1_8000000)) {
        return false;
    } else {
        return true;
    }
}

void func_80A7436C(EnPr2* this, s16 arg1) {
    s16 sp2E = arg1 - this->actor.world.rot.y;

    if (sp2E > 10000) {
        sp2E = 10000;
    } else if (sp2E < -10000) {
        sp2E = -10000;
    }

    Math_ApproachF(&this->actor.world.pos.y, this->unk_21C.y, 0.3f, 5.0f);

    if (fabsf(this->actor.world.pos.y - this->unk_21C.y) > 10.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.x, Math_Vec3f_Pitch(&this->actor.world.pos, &this->unk_21C) * 0.3f,
                           20, 5000, 500);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.x, 0, 20, 5000, 500);
    }

    if (fabsf(this->actor.world.rot.y - arg1) < 30.0f) {
        Math_ApproachZeroF(&this->unk_1FC, 0.5f, 20.0f);
    } else {
        Math_ApproachF(&this->unk_1FC, sp2E, 0.5f, 3000.0f);
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, arg1, 1, 2000, 300);
}

void func_80A74510(EnPr2* this, s32 arg0) {
    f32 sp34 = 1.0f;

    this->unk_210 = arg0;
    this->unk_1F8 = Animation_GetLastFrame(sAnimations[arg0]);
    if (this->unk_210 == 3) {
        sp34 = 0.0f;
    }
    Animation_Change(&this->skelAnime, sAnimations[arg0], sp34, 0.0f, this->unk_1F8, D_80A75C38[arg0], 0.0f);
}

void func_80A745C4(EnPr2* this) {
    func_80A74510(this, 0);
    this->unk_1D4 = 0;
    this->actionFunc = func_80A745FC;
}

void func_80A745FC(EnPr2* this, PlayState* play) {
    f32 x;
    f32 y;
    f32 z;
    f32 sqrtXYZ;

    if (fabsf(this->actor.world.rot.y - this->unk_1EE) < 200.0f) {
        SkelAnime_Update(&this->skelAnime);
    }

    Actor_PlaySfx(&this->actor, NA_SE_EN_PIRANHA_EXIST - SFX_FLAG);
    Math_ApproachF(&this->unk_204, 0.02f, 0.1f, 0.005f);

    if (this->path->customValue < this->unk_1D0) {
        Math_ApproachF(&this->actor.speed, 5.0f, 0.3f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speed, 10.0f, 0.3f, 1.0f);
    }

    if ((this->path != NULL) && !SubS_CopyPointFromPath(this->path, this->unk_1D0, &this->unk_21C)) {
        Actor_Kill(&this->actor);
    }

    Math_ApproachF(&this->actor.world.pos.y, this->unk_21C.y, 0.3f, 5.0f);

    if (fabsf(this->actor.world.pos.y - this->unk_21C.y) > 10.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.x, Math_Vec3f_Pitch(&this->actor.world.pos, &this->unk_21C) * 0.3f,
                           20, 5000, 500);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.x, 0, 20, 5000, 500);
    }

    x = this->actor.world.pos.x - this->unk_21C.x;
    y = this->actor.world.pos.y - this->unk_21C.y;
    z = this->actor.world.pos.z - this->unk_21C.z;
    sqrtXYZ = sqrtf(SQ(x) + SQ(y) + SQ(z));

    if (sqrtXYZ < (Rand_ZeroFloat(20.0f) + 15.0f)) {
        this->unk_1D0++;
        Math_Vec3f_Copy(&this->unk_228, &this->actor.world.pos);
        if (this->unk_1D0 >= this->path->count) {
            this->unk_1E0 = 2;
            func_80A74888(this);
        }
    }

    this->unk_1EE = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_21C);
    func_80A7436C(this, this->unk_1EE);
}

void func_80A74888(EnPr2* this) {
    func_80A74510(this, 0);
    this->unk_1DA = 2;
    this->unk_1D8 = 0;
    Math_Vec3f_Copy(&this->unk_21C, &this->unk_228);
    this->unk_1D4 = 1;
    this->actionFunc = func_80A748E8;
}

void func_80A748E8(EnPr2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_f12;
    f32 temp_f2;
    f32 sqrtXZ;
    s32 sp4C = false;
    s32 sp48 = false;
    Vec3f sp3C;

    Math_ApproachF(&this->unk_204, 0.02f, 0.1f, 0.005f);
    Actor_PlaySfx(&this->actor, NA_SE_EN_PIRANHA_EXIST - SFX_FLAG);

    if (fabsf(this->actor.world.rot.y - this->unk_1EE) < 200.0f) {
        sp48 = true;
        SkelAnime_Update(&this->skelAnime);
    }

    if (this->unk_1F4 != 255) {
        this->actor.speed = 0.0f;
        Math_SmoothStepToS(&this->unk_1F4, 0, 1, 30, 100);
        if (this->unk_1F4 < 2) {
            Actor_Kill(&this->actor);
        }
    } else {
        switch (this->unk_1E0) {
            case 1:
                if (this->unk_1DC == 0) {
                    sp4C = true;
                    func_80A74DEC(this, play);
                } else if (!func_80A7429C(this, play) && (this->unk_1F4 == 255)) {
                    this->unk_1F4 = 254;
                }
                break;

            case 2:
                if (this->unk_1DE == 0) {
                    temp_f2 = player->actor.world.pos.x - this->unk_228.x;
                    temp_f12 = player->actor.world.pos.z - this->unk_228.z;
                    sqrtXZ = sqrtf(SQ(temp_f2) + SQ(temp_f12));

                    if (sp48 && (player->stateFlags1 & PLAYER_STATE1_8000000) && (sqrtXZ < this->unk_208)) {
                        sp4C = true;
                        func_80A74DEC(this, play);
                    }
                } else {
                    temp_f2 = this->actor.world.pos.x - this->unk_228.x;
                    temp_f12 = this->actor.world.pos.z - this->unk_228.z;
                    sqrtXZ = sqrtf(SQ(temp_f2) + SQ(temp_f12));

                    if (sqrtXZ > 20.0f) {
                        this->unk_1DE = 5;
                        sp4C = true;
                        this->unk_1DC = 0;
                        Math_Vec3f_Copy(&this->unk_21C, &this->unk_228);
                        Math_ApproachF(&this->actor.speed, 3.0f, 0.3f, 0.2f);
                    }
                }
                break;
        }

        if (!sp4C) {
            this->unk_21C.y = this->actor.world.pos.y;
            if (this->unk_1DA != 0) {
                if ((Rand_ZeroOne() < 0.3f) && !this->unk_1D6) {
                    this->unk_1D6 = true;
                }

                Math_ApproachZeroF(&this->actor.speed, 0.1f, 0.2f);

                if (this->unk_1DA == 1) {
                    this->unk_1D8 = Rand_S16Offset(100, 100);
                    Math_Vec3f_Copy(&sp3C, &this->unk_228);
                    sp3C.x += Rand_CenteredFloat(300.0f);
                    sp3C.z += Rand_CenteredFloat(300.0f);
                    Math_Vec3f_Copy(&this->unk_21C, &sp3C);
                }
            } else {
                Math_ApproachF(&this->actor.speed, 2.0f, 0.3f, 0.2f);
                Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
                sp3C.x += Math_SinS(this->actor.world.rot.y) * 20.0f;
                sp3C.z += Math_CosS(this->actor.world.rot.y) * 20.0f;
                if (fabsf(this->actor.world.rot.y - this->unk_1EE) < 100.0f) {
                    if (BgCheck_SphVsFirstPoly(&play->colCtx, &sp3C, 20.0f) ||
                        (this->actor.bgCheckFlags & BGCHECKFLAG_WALL)) {
                        this->unk_1DC = 0;
                        this->unk_1F2++;
                        Math_Vec3f_Copy(&this->unk_21C, &this->unk_228);
                        if (this->unk_1F2 > 10) {
                            this->unk_1F0 += 0x2000;
                        }
                    } else {
                        Math_SmoothStepToS(&this->unk_1F0, 0, 1, 1000, 100);
                        this->unk_1F2 = 0;
                    }
                }

                if ((this->unk_1D8 == 0) || ((fabsf(this->unk_21C.x - this->actor.world.pos.x) < 10.0f) &&
                                             (fabsf(this->unk_21C.z - this->actor.world.pos.z) < 10.0f))) {
                    this->unk_1DA = Rand_S16Offset(20, 30);
                }
            }
        }

        if (this->unk_1DA == 0) {
            this->unk_1EE = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_21C) + this->unk_1F0;
            func_80A7436C(this, this->unk_1EE);
        }
    }
}

void func_80A74DEC(EnPr2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->unk_1F0 = 0;
    func_80A74510(this, 1);
    Actor_PlaySfx(&this->actor, NA_SE_EN_PIRANHA_ATTACK);
    Math_Vec3f_Copy(&this->unk_21C, &player->actor.world.pos);

    this->unk_1EE = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_21C);
    this->unk_20C = Rand_ZeroFloat(30.0f);
    this->unk_1DC = 0;
    this->unk_1D8 = 70;
    this->unk_1D4 = 2;
    this->actionFunc = func_80A74E90;
}

void func_80A74E90(EnPr2* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    WaterBox* sp40;

    Math_ApproachF(&this->unk_204, 0.02f, 0.1f, 0.005f);
    if ((this->unk_1D8 == 0) || !(player->stateFlags1 & PLAYER_STATE1_8000000) || (this->unk_1E0 == 0)) {
        func_80A74888(this);
        return;
    }

    if (this->unk_1F4 != 255) {
        this->actor.speed = 0.0f;
        Math_SmoothStepToS(&this->unk_1F4, 0, 1, 30, 100);
        if (this->unk_1F4 < 2) {
            Actor_Kill(&this->actor);
        }
    } else {
        SkelAnime_Update(&this->skelAnime);

        if ((this->unk_1DC == 0) && (fabsf(this->actor.world.rot.y - this->unk_1EE) < 200.0f)) {
            Math_Vec3f_Copy(&this->unk_21C, &player->actor.world.pos);
        }

        if ((Rand_ZeroOne() < 0.3f) && !this->unk_1D6) {
            this->unk_1D6 = true;
            this->unk_20C = Rand_ZeroFloat(30.0f);
        }

        this->unk_21C.y = player->actor.world.pos.y + 30.0f + this->unk_20C;
        Math_ApproachF(&this->actor.speed, 5.0f, 0.3f, 1.0f);
        this->unk_1F0 = 0;

        if (this->unk_1E0 == 2) {
            f32 temp_f2 = this->actor.world.pos.x - this->unk_228.x;
            f32 temp_f12 = this->actor.world.pos.z - this->unk_228.z;
            f32 sqrtXZ = sqrtf(SQ(temp_f2) + SQ(temp_f12));

            if (this->unk_208 < sqrtXZ) {
                this->unk_1DE = 20;
                func_80A74888(this);
                return;
            }
        } else {
            Math_Vec3f_Copy(&this->unk_228, &this->actor.world.pos);
        }

        if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &this->unk_200,
                                 &sp40)) {
            if ((this->unk_200 - 40.0f) < this->unk_21C.y) {
                this->unk_21C.y = this->unk_200 - 40.0f;
            }
        }

        if ((this->unk_1E0 == 1) && !func_80A7429C(this, play)) {
            if (this->unk_1F4 == 255) {
                this->unk_1F4 = 254;
            }
        } else {
            if (this->collider.base.atFlags & AT_HIT) {
                this->unk_1DC = Rand_S16Offset(30, 30);
                this->unk_1D8 = 100;
                if (this->unk_1E0 != 2) {
                    func_80A74888(this);
                }
            }
            this->unk_1EE = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_21C);
            func_80A7436C(this, this->unk_1EE);
        }
    }
}

void func_80A751B4(EnPr2* this) {
    this->unk_1EC = 0;
    this->actor.flags |= ACTOR_FLAG_CANT_LOCK_ON;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    if (this->unk_1E0 < 10) {
        func_80A74510(this, 2);
    } else {
        this->unk_1F8 = Animation_GetLastFrame(&object_pr_Anim_003904);
        Animation_Change(&this->skelAnime, &object_pr_Anim_003904, 1.0f, this->unk_1F8, this->unk_1F8, ANIMMODE_ONCE,
                         0.0f);
        this->unk_1D8 = Rand_S16Offset(20, 30);
        this->unk_1E4 = 0x4000;
        if (Rand_ZeroOne() < 0.5f) {
            this->unk_1E4 = -0x4000;
        }
        this->unk_1E6 = this->actor.world.rot.y;
        this->actor.shape.rot.x = this->actor.world.rot.x;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.shape.rot.z = this->actor.world.rot.z;
        this->unk_1D8 = 30;
        this->actor.speed = Rand_ZeroFloat(0.5f);
        this->actor.world.rot.y = Rand_CenteredFloat(0x8000);
    }
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 10);
    this->unk_1D4 = 3;
    this->actionFunc = func_80A75310;
}

void func_80A75310(EnPr2* this, PlayState* play) {
    s32 temp;
    f32 frame;
    WaterBox* sp74;

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_1E0 < 10) {
        s32 i;

        frame = this->skelAnime.curFrame;

        if (this->unk_1F8 <= frame) {
            for (i = 0; i < ARRAY_COUNT(this->unk_234); i++) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_PR2, this->unk_234[i].x, this->unk_234[i].y,
                            this->unk_234[i].z, this->actor.world.rot.x, this->actor.world.rot.y,
                            this->actor.world.rot.z, i + 10);
            }

            Actor_Kill(&this->actor);
            return;
        }
    } else {
        Vec3f sp64;

        temp = false;
        Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 5, 10000, 1000);
        Math_SmoothStepToS(&this->actor.shape.rot.z, this->unk_1E4, 5, 10000, 1000);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_1E6, 5, 10000, 1000);

        if ((Rand_ZeroOne() < 0.3f) && !this->unk_1D6) {
            this->unk_1D6 = true;
        }

        if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &this->unk_200,
                                 &sp74)) {
            frame = this->unk_200 - 15.0f;

            if (frame <= this->actor.world.pos.y) {
                temp = true;
            } else {
                Math_ApproachF(&this->actor.world.pos.y, frame, 0.3f, 1.0f);
            }
        }

        if ((this->unk_1D8 == 0) || temp) {
            s32 i;

            Math_SmoothStepToS(&this->unk_1F4, 0, 1, 15, 50);

            if (this->unk_1F4 < 2) {
                for (i = 0; i < 10; i++) {
                    Math_Vec3f_Copy(&sp64, &this->actor.world.pos);

                    sp64.x += Rand_CenteredFloat(20.0f);
                    sp64.y += Rand_CenteredFloat(5.0f);
                    sp64.z += Rand_CenteredFloat(20.0f);
                    frame = Rand_ZeroFloat(0.03f) + 0.07f;

                    EffectSsBubble_Spawn(play, &sp64, 0.0f, 5.0f, 5.0f, frame);
                }

                Actor_Kill(&this->actor);
            }
        }
    }
}

void func_80A755D8(EnPr2* this, PlayState* play) {
    s32 temp_v0;

    if (this->collider.base.acFlags & AC_HIT) {
        Actor_ApplyDamage(&this->actor);
        if ((this->actor.colChkInfo.health <= 0) && (this->unk_1D4 != 3)) {
            Enemy_StartFinishingBlow(play, &this->actor);
            this->actor.speed = 0.0f;
            Actor_PlaySfx(&this->actor, NA_SE_EN_PIRANHA_DEAD);

            if (this->unk_218 >= 0) {
                Item_DropCollectibleRandom(play, NULL, &this->actor.world.pos, D_80A75C3C[this->unk_218]);
            }

            this->actor.colChkInfo.health = 0;
            func_80A751B4(this);
        }
    }

    if (this->collider.base.atFlags & AT_BOUNCED) {
        this->actor.speed = -10.0f;
    }
}

void EnPr2_Update(Actor* thisx, PlayState* play) {
    EnPr2* this = THIS;
    f32 rand;

    if (thisx) {}

    Actor_SetScale(&this->actor, this->unk_204);

    this->actionFunc(this, play);

    if (this->unk_1DA != 0) {
        this->unk_1DA--;
    }

    if (this->unk_1D8 != 0) {
        this->unk_1D8--;
    }

    if (this->unk_1DC != 0) {
        this->unk_1DC--;
    }

    if (this->unk_1DE != 0) {
        this->unk_1DE--;
    }

    Actor_SetFocus(&this->actor, 10.0f);
    func_80A755D8(this, play);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0, 10.0f, 20.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4 |
                                UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10);

    if (this->unk_1D6) {
        s32 i;
        Vec3f sp58;
        f32 rand;

        Math_Vec3f_Copy(&sp58, &this->unk_270);
        this->unk_1D6 = false;

        sp58.x += Rand_CenteredFloat(20.0f);
        sp58.y += Rand_CenteredFloat(5.0f);
        sp58.z += Rand_CenteredFloat(20.0f);

        for (i = 0; i < 2; i++) {
            rand = Rand_ZeroFloat(0.03f) + 0.07f;
            EffectSsBubble_Spawn(play, &sp58, 0, 5.0f, 5.0f, rand);
        }
    }

    if ((this->unk_1F4 == 255) && (this->unk_1E0 < 10)) {
        this->actor.shape.rot.x = this->actor.world.rot.x;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.shape.rot.z = this->actor.world.rot.z;
        if (this->unk_1D4 != 3) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

s32 func_80A758E8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnPr2* this = THIS;

    if (this->unk_1E0 < 10) {
        if (limbIndex == 2) {
            rot->y += (s16)this->unk_1FC * -1;
        }
    } else if ((limbIndex + 10) != this->unk_1E0) {
        *dList = NULL;
    }
    return false;
}

void func_80A75950(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnPr2* this = THIS;

    if (this->unk_1E0 < 10) {
        if (limbIndex == 2) {
            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultZero(&this->unk_270);
        }
        Matrix_MultZero(&this->unk_234[limbIndex]);
    }
}

s32 func_80A759D8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnPr2* this = THIS;

    if (this->unk_1E0 < 10) {
        if (limbIndex == 2) {
            rot->y += (s16)this->unk_1FC * -1;
        }
    } else if ((limbIndex + 10) != this->unk_1E0) {
        *dList = NULL;
    }
    return false;
}

void EnPr2_Draw(Actor* thisx, PlayState* play) {
    EnPr2* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    if (this->unk_1F4 == 255) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_1EC, this->unk_1EC, this->unk_1EC, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->unk_1F4);

        Scene_SetRenderModeXlu(play, 0, 1);
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                              func_80A758E8, func_80A75950, &this->actor);
    } else {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_1F4);

        Scene_SetRenderModeXlu(play, 1, 2);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               func_80A759D8, NULL, &this->actor, POLY_XLU_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
