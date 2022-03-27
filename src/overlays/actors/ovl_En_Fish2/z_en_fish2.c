/*
 * File: z_en_fish2.c
 * Overlay: ovl_En_Fish2
 * Description: Marine Research Lab Fish
 */

#include "overlays/actors/ovl_En_Fish/z_en_fish.h"
#include "overlays/actors/ovl_En_Mushi2/z_en_mushi2.h"
#include "z_en_fish2.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_fb/object_fb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnFish2*)thisx)

void EnFish2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B28B5C(EnFish2* this);
void func_80B28C14(EnFish2* this, GlobalContext* globalCtx);
void func_80B29128(EnFish2* this);
void func_80B2913C(EnFish2* this, GlobalContext* globalCtx);
void func_80B29194(EnFish2* this);
void func_80B29250(EnFish2* this, GlobalContext* globalCtx);
void func_80B2938C(EnFish2* this);
void func_80B293C4(EnFish2* this, GlobalContext* globalCtx);
void func_80B2951C(EnFish2* this);
void func_80B295A4(EnFish2* this, GlobalContext* globalCtx);
void func_80B29778(EnFish2* this);
void func_80B297FC(EnFish2* this, GlobalContext* globalCtx);
void func_80B29E5C(EnFish2* this, GlobalContext* globalCtx);
void func_80B29EE4(EnFish2* this, GlobalContext* globalCtx);
void func_80B2A01C(EnFish2* this, GlobalContext* globalCtx);
void func_80B2A094(EnFish2* this, GlobalContext* globalCtx);
void func_80B2A23C(EnFish2* this, GlobalContext* globalCtx);
void func_80B2A448(EnFish2* this);
void func_80B2A498(EnFish2* this, GlobalContext* globalCtx);
void func_80B2ADB0(EnFish2* this, Vec3f* vec, s16 arg2);
void func_80B2AF80(EnFish2* this, GlobalContext* globalCtx);
void func_80B2B180(EnFish2* this, GlobalContext* globalCtx);

static s32 D_80B2B2E0 = 0;
static s32 D_80B2B2E4 = 0;
static s32 D_80B2B2E8 = 0;
static s32 D_80B2B2EC = 0;
static s32 D_80B2B2F0 = 0;
static Actor* D_80B2B2F4 = NULL;

const ActorInit En_Fish2_InitVars = {
    ACTOR_EN_FISH2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FB,
    sizeof(EnFish2),
    (ActorFunc)EnFish2_Init,
    (ActorFunc)EnFish2_Destroy,
    (ActorFunc)EnFish2_Update,
    (ActorFunc)EnFish2_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 17, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit,
};

static f32 D_80B2B370[] = { 0.01f, 0.012f, 0.014f, 0.017f };
static f32 D_80B2B380[] = { 0.019f, 0.033f };

void func_80B28370(EnFish2* this, s32 arg0) {
    static AnimationHeader* D_80B2B388[] = {
        &object_fb_Anim_0013AC, &object_fb_Anim_0007D4, &object_fb_Anim_0006D8,
        &object_fb_Anim_0006D8, &object_fb_Anim_001174, &object_fb_Anim_000ACC,
    };
    static u8 D_80B2B3A0[] = { 0, 0, 2, 2, 2, 2 };
    f32 sp34;

    this->unk_2AC = arg0;
    this->unk_2CC = Animation_GetLastFrame(&D_80B2B388[arg0]->common);
    sp34 = 0.0f;
    if (this->unk_2AC == 3) {
        sp34 = Animation_GetLastFrame(&D_80B2B388[this->unk_2AC]->common) - 21.0f;
    }

    if (this->unk_2AC == 2) {
        this->unk_2CC = Animation_GetLastFrame(&D_80B2B388[this->unk_2AC]->common) - 21.0f;
    }

    Animation_Change(&this->skelAnime, D_80B2B388[this->unk_2AC], 1.0f, sp34, this->unk_2CC, D_80B2B3A0[this->unk_2AC],
                     -10.0f);
}

s32 func_80B28478(EnFish2* this) {
    if (this->unk_2C8 == 0) {
        if ((D_80B2B2E4 != 0) && ((D_80B2B2E0 != 1) || (this->unk_350 == NULL) || (this->unk_350->update == NULL)) &&
            (this->unk_2B0 == 0)) {
            this->unk_2B4 = 0;
            this->unk_2C4 = 0;
            this->unk_2B6 = this->unk_2B4;
            func_80B28B5C(this);
            return true;
        }
    } else if ((this->unk_350 == NULL) || (this->unk_350->update == NULL)) {
        this->unk_2B4 = 0;
        this->unk_2C4 = 0;
        this->unk_2B6 = this->unk_2B4;
        func_80B28B5C(this);
        return true;
    }

    return false;
}

void EnFish2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFish2* this = THIS;
    s32 i;
    s32 cs;

    Math_Vec3f_Copy(&this->unk_324, &this->actor.home.pos);
    this->unk_344 = D_80B2B2F0;
    D_80B2B2F0++;

    if (this->actor.params == 0) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_fb_Skel_006190, &object_fb_Anim_0013AC,
                           this->jointTable, this->morphTable, 24);
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        if (this->unk_344 == 0) {
            if (gSaveContext.save.weekEventReg[81] & 0x10) {
                this->unk_2C0 = 1;
            }

            if (gSaveContext.save.weekEventReg[81] & 0x20) {
                this->unk_2C0 = 2;
            }

            if (gSaveContext.save.weekEventReg[81] & 0x40) {
                this->unk_2C0 = 3;
            }
        } else {
            if (gSaveContext.save.weekEventReg[81] & 0x80) {
                this->unk_2C0 = 1;
            }

            if (gSaveContext.save.weekEventReg[82] & 1) {
                this->unk_2C0 = 2;
            }

            if (gSaveContext.save.weekEventReg[82] & 2) {
                this->unk_2C0 = 3;
            }
        }
        cs = this->actor.cutscene;
        this->unk_330 = D_80B2B370[this->unk_2C0];
        i = 0;

        // clang-format off
        while (cs != -1) { this->unk_2BA[i] = cs; cs = ActorCutscene_GetAdditionalCutscene(cs); i++; }
        // clang-format on

        Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
        this->collider.elements[0].dim.modelSphere.radius = 5;
        this->collider.elements[0].dim.scale = 1.0f;
        this->collider.elements[0].dim.modelSphere.center.x = 1300;
        this->collider.elements[0].dim.modelSphere.center.y = 0;
        this->collider.elements[0].dim.modelSphere.center.z = 0;
        this->collider.elements[1].dim.modelSphere.radius = 5;
        this->collider.elements[1].dim.scale = 1.0f;
        this->collider.elements[1].dim.modelSphere.center.x = 500;
        this->collider.elements[1].dim.modelSphere.center.y = 0;
        this->collider.elements[1].dim.modelSphere.center.z = 0;
        this->actor.textId = 0x24C;
        func_80B28B5C(this);
    } else if (this->actor.params != 0) {
        this->unk_2B4 = 10;
        this->actor.draw = NULL;
        this->actor.flags |= ACTOR_FLAG_8000000;
        this->actionFunc = func_80B2A01C;
    }
}

void EnFish2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFish2* this = THIS;

    if (this->actor.params != 1) {
        Collider_DestroyJntSph(globalCtx, &this->collider);
    }
}

void func_80B287F4(EnFish2* this, s32 arg1) {
    Vec3f sp2C;

    if ((this->unk_354 != 0) && (this->unk_2C8 == 0)) {
        if (this->unk_2C4 < 400) {
            this->unk_2C4++;
        }
        this->unk_338 = 440.0f - this->unk_2C4;
        if (arg1 == 0) {
            this->unk_338 = 410.0f - this->unk_2C4;
        }
        Math_ApproachF(&this->unk_350->speedXZ, (D_80B2B380[0] - this->unk_330) * this->unk_338, 0.1f, 0.4f);
    }
    Math_Vec3f_Copy(&sp2C, &this->unk_350->world.pos);
    this->unk_34A = Math_Vec3f_Yaw(&this->actor.world.pos, &sp2C);
    this->unk_348 = Math_Vec3f_Pitch(&this->actor.world.pos, &sp2C);
}

s32 func_80B288E8(EnFish2* this, Vec3f vec, s32 arg2) {
    f32 temp_f2 = this->unk_350->world.pos.x - vec.x;
    f32 temp_f12 = this->unk_350->world.pos.y - vec.y;
    f32 temp_f14 = this->unk_350->world.pos.z - vec.z;
    f32 dist = sqrtf(SQ(temp_f2) + SQ(temp_f12) + SQ(temp_f14));
    f32 phi_f2;

    if (arg2 == 0) {
        phi_f2 = 40.0f;
    } else {
        phi_f2 = this->unk_330 * 2000.0f;
        if (phi_f2 > 20.0f) {
            phi_f2 = 20.0f;
        }
    }

    if (dist < phi_f2) {
        return true;
    }

    return false;
}

s32 func_80B2899C(EnFish2* this, GlobalContext* globalCtx) {
    if (BgCheck_SphVsFirstWall(&globalCtx->colCtx, &this->unk_2F4, this->unk_33C)) {
        return true;
    }

    return false;
}

void func_80B289DC(EnFish2* this, GlobalContext* globalCtx) {
    WaterBox* sp2C;

    if (this->unk_2B4 != 0) {
        this->unk_348 = 0;
    }

    if (this->unk_348 != 0) {
        if (this->unk_348 > 0) {
            if (this->unk_2D4 < this->actor.world.pos.y) {
                this->actor.velocity.y = this->actor.world.rot.x * 0.001f * -0.1f;
                if (this->actionFunc == func_80B297FC) {
                    this->actor.velocity.y *= 2.0f;
                }
            } else {
                this->unk_348 = 0;
                this->actor.velocity.y = 0.0f;
                this->actor.gravity = 0.0f;
            }
        } else if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                        &this->unk_334, &sp2C)) {
            if ((this->unk_334 != BGCHECK_Y_MIN) && (this->actor.world.pos.y < (this->unk_334 - this->unk_2D8))) {
                this->actor.velocity.y = this->actor.world.rot.x * 0.001f * -0.1f;
                if (this->actionFunc == func_80B297FC) {
                    this->actor.velocity.y *= 2.0f;
                }
            }
        } else {
            this->unk_348 = 0;
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
        }
    }
}

void func_80B28B5C(EnFish2* this) {
    func_80B28370(this, 0);
    this->unk_2B4 = 0;
    this->unk_348 = 0;
    this->unk_2C4 = 0;
    this->unk_2C8 = 0;
    this->unk_334 = BGCHECK_Y_MIN;
    this->unk_2B6 = this->unk_2B4;
    this->unk_34C = this->unk_348;
    this->unk_34A = this->actor.world.rot.y;
    this->collider.elements[1].dim.modelSphere.radius = (s32)((this->unk_330 - 0.01f) * 1000.0f) + 5;
    if (this->collider.elements[1].dim.modelSphere.radius > 15) {
        this->collider.elements[1].dim.modelSphere.radius = 15;
    }
    this->actionFunc = func_80B28C14;
}

void func_80B28C14(EnFish2* this, GlobalContext* globalCtx) {
    Actor* itemAction = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    WaterBox* waterbox;

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80B29128(this);
        return;
    }

    if ((this->unk_2B8 == 0) && (fabsf(this->actor.world.rot.y - this->unk_34A) < 100.0f)) {
        if (func_80B2899C(this, globalCtx)) {
            if (this->unk_340 == 0) {
                this->unk_34A += 0x4000;
            } else {
                this->unk_34A -= 0x4000;
            }
            this->unk_2B8 = (s32)(this->unk_330 * 1000.0f) - 10;
        }
    }

    func_80B289DC(this, globalCtx);

    if (this->unk_2B6 == 0) {
        if (this->unk_2B4 == 0) {
            this->unk_2B4 = (s32)Rand_ZeroFloat(20.0f) + 10;
        } else if (this->unk_2B4 == 1) {
            if ((this->unk_348 == 0) || (Rand_ZeroOne() < 0.6f)) {
                this->unk_348 = randPlusMinusPoint5Scaled(0x2000);
            } else {
                this->unk_348 = Math_Vec3f_Pitch(&this->actor.world.pos, &this->unk_324);
                if (this->unk_348 < -0x1000) {
                    this->unk_348 = -0x1000;
                }

                if (this->unk_348 > 0x1000) {
                    this->unk_348 = 0x1000;
                }
            }

            this->unk_2B6 = (s32)Rand_ZeroFloat(70.0f) + 30;
            if (this->unk_2C0 >= 3) {
                this->unk_2B6 -= (s32)Rand_ZeroFloat(20.0f);
            }
        }
    }

    if ((this->unk_334 == BGCHECK_Y_MIN) &&
        !WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                              &this->unk_334, &waterbox)) {
        this->unk_334 = this->actor.world.pos.y;
    }

    if (this->unk_2B4 == 0) {
        Math_ApproachF(&this->actor.speedXZ, (D_80B2B380[0] - this->unk_330) * 400.0f, 0.3f, 0.3f);
        if (this->actor.speedXZ > 3.0f) {
            this->actor.speedXZ = 3.0f;
        } else if (this->actor.speedXZ < 1.5f) {
            this->actor.speedXZ = 1.5f;
        }
    } else {
        Math_ApproachZeroF(&this->actor.speedXZ, 0.3f, 0.3f);
    }

    if ((D_80B2B2E8 == 0) && (D_80B2B2E0 != 2)) {
        while (itemAction != NULL) {
            if ((itemAction->id != ACTOR_EN_FISH) && (itemAction->id != ACTOR_EN_MUSHI2)) {
                itemAction = itemAction->next;
                continue;
            }

            if (itemAction->id == ACTOR_EN_MUSHI2) {
                if ((itemAction->update != NULL) && (((EnMushi2*)itemAction)->unk_30C & 0x200)) {
                    this->unk_350 = itemAction;
                    this->unk_2C8 = 1;
                    func_80B29194(this);
                    break;
                }
            } else if ((itemAction->update != NULL) && (itemAction->params == 0) &&
                       (fabsf(itemAction->world.pos.x - this->actor.world.pos.x) < 100.0f) &&
                       (fabsf(itemAction->world.pos.z - this->actor.world.pos.z) < 100.0f) &&
                       (itemAction->bgCheckFlags & 0x20)) {
                this->unk_350 = itemAction;
                if (D_80B2B2E0 == 0) {
                    EnFish2* fish;

                    this->unk_354 = NULL;
                    fish = (EnFish2*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_FISH2,
                                                        this->unk_324.x, this->unk_324.y, this->unk_324.z, 0, 0, 0, 1);
                    this->unk_354 = fish;
                    if (this->unk_354 != NULL) {
                        D_80B2B2E4 = 0;
                        D_80B2B2E0 = 1;
                        fish->unk_2BA[0] = this->unk_2BA[0];
                        fish->unk_350 = this->unk_350;
                    }
                }
                func_80B29194(this);
                break;
            }
            itemAction = itemAction->next;
        }

        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80B29128(EnFish2* this) {
    this->actionFunc = func_80B2913C;
}

void func_80B2913C(EnFish2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80B28B5C(this);
    }
}

void func_80B29194(EnFish2* this) {
    if ((this->unk_354 != NULL) && (this->unk_2C8 == 0)) {
        EnFish* fish = (EnFish*)this->unk_350;
        fish->unk_277 = 1;
    }

    this->unk_2C4 = 0;
    this->actor.speedXZ = 0.0f;
    if (this->unk_2C8 == 0) {
        this->unk_34C = 400;
        Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_324);
        this->actor.world.pos.y = this->actor.floorHeight + (this->unk_330 * 1200.0f);
    }

    this->unk_34A = 0;
    this->unk_340 = (s32)Rand_ZeroOne() & 1;
    func_80B28370(this, 1);
    this->actionFunc = func_80B29250;
}

void func_80B29250(EnFish2* this, GlobalContext* globalCtx) {
    if (!func_80B28478(this)) {
        Math_ApproachF(&this->actor.speedXZ, (D_80B2B380[0] - this->unk_330) * 1000.0f, 0.3f, 0.3f);

        if (this->actor.speedXZ > 4.0f) {
            this->actor.speedXZ = 4.0f;
        } else if (this->actor.speedXZ < 2.0f) {
            this->actor.speedXZ = 2.0f;
        }

        func_80B287F4(this, 0);
        func_80B289DC(this, globalCtx);
        if (func_80B288E8(this, this->unk_300, 0) &&
            (((this->unk_2C8 == 0) && (D_80B2B2E4 == 1)) || (this->unk_2C8 != 0))) {
            Math_Vec3f_Copy(&this->unk_30C, &this->unk_350->world.pos);
            func_80B2938C(this);
        }
    }
}

void func_80B2938C(EnFish2* this) {
    func_80B28370(this, 5);
    this->unk_348 = 0;
    this->actionFunc = func_80B293C4;
}

void func_80B293C4(EnFish2* this, GlobalContext* globalCtx) {
    f32 currentFrame = this->skelAnime.curFrame;

    if (func_80B28478(this) == 0) {
        func_80B287F4(this, 1);
        Math_ApproachF(&this->actor.speedXZ, (*D_80B2B380 - this->unk_330) * 1000.0f, 0.3f, 0.3f);

        if (this->actor.speedXZ > 3.0f) {
            this->actor.speedXZ = 3.0f;
        } else if (this->actor.speedXZ < 1.0f) {
            this->actor.speedXZ = 1.0f;
        }

        if (this->unk_2CC <= currentFrame) {
            func_80B28370(this, 1);
            if (this->unk_2B0 == 0) {
                this->actionFunc = func_80B29250;
            } else {
                this->actionFunc = func_80B29EE4;
            }
        } else {
            func_80B289DC(this, globalCtx);
            if (func_80B288E8(this, this->unk_318, 1)) {
                func_80B2951C(this);
            }
        }
    }
}

void func_80B2951C(EnFish2* this) {
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->unk_348 = 0;

    if (this->unk_2C8 == 0) {
        D_80B2B2E0 = 2;
    }

    this->unk_2B4 = 10;
    this->actor.speedXZ = 3.0f;
    Actor_MarkForDeath(this->unk_350);
    this->unk_350 = NULL;
    D_80B2B2F4 = &this->actor;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DODO_M_EAT);
    this->actionFunc = func_80B295A4;
}

void func_80B295A4(EnFish2* this, GlobalContext* globalCtx) {
    s32 i;
    f32 currentFrame = this->skelAnime.curFrame;
    s32 pad;
    Vec3f sp60;

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &globalCtx->view.eye), 1,
                       0x1388, 0);
    Math_ApproachZeroF(&this->actor.speedXZ, 0.3f, 0.3f);
    if (this->unk_2B4 != 0) {
        Math_Vec3f_Copy(&sp60, &this->unk_318);
        sp60.x += randPlusMinusPoint5Scaled(100.0f);
        sp60.z += randPlusMinusPoint5Scaled(100.0f);

        for (i = 0; i < 2; i++) {
            EffectSsBubble_Spawn(globalCtx, &sp60, 0.0f, 5.0f, 5.0f, Rand_ZeroFloat(this->unk_330 * 4.0f) + 0.1f);
        }
    } else if (this->unk_2CC <= currentFrame) {
        if (this->unk_2AC != 5) {
            func_80B28370(this, 5);
        } else if (this->unk_2C8 == 0) {
            func_80B29778(this);
        } else {
            this->unk_2B4 = 0;
            this->unk_2C4 = 0;
            this->unk_2B6 = this->unk_2B4;
            func_80B28B5C(this);
        }
    }
}

void func_80B29778(EnFish2* this) {
    func_80B28370(this, 0);
    this->unk_2B4 = 0;
    this->unk_2C4 = 0;
    this->unk_2B6 = this->unk_2B4;
    if (this->unk_2B0 != 0) {
        this->unk_324.x = this->actor.home.pos.x - 14.0f;
        this->unk_324.z = this->actor.home.pos.z - 18.0f;
    }
    this->actionFunc = func_80B297FC;
    this->unk_324.y = this->unk_2D4;
    this->actor.speedXZ = 0.0f;
}

void func_80B297FC(EnFish2* this, GlobalContext* globalCtx) {
    f32 phi_f0 = 0.0f;
    Vec3f sp48;

    switch (this->unk_2C4) {
        case 0:
            Math_Vec3f_Copy(&sp48, &this->unk_324);
            sp48.y = this->unk_2D4;
            this->unk_348 = Math_Vec3f_Pitch(&this->actor.world.pos, &sp48);

            if (this->unk_348 < -0x2000) {
                this->unk_348 = -0x2000;
            }

            if (this->unk_348 > 0x2000) {
                this->unk_348 = 0x2000;
            }

            this->unk_34A = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_324);
            func_80B289DC(this, globalCtx);
            Math_ApproachF(&this->actor.world.pos.x, this->unk_324.x, 0.3f, 3.0f);
            Math_ApproachF(&this->actor.world.pos.y, this->unk_2D4, 0.3f, 3.0f);
            Math_ApproachF(&this->actor.world.pos.z, this->unk_324.z, 0.3f, 3.0f);
            if ((fabsf(this->actor.world.pos.x - this->unk_324.x) < 2.0f) &&
                (this->actor.world.pos.y < (this->unk_2D4 + 3.0f)) &&
                (fabsf(this->actor.world.pos.z - this->unk_324.z) < 2.0f)) {
                this->actor.speedXZ = 0.0f;
                this->unk_34A = BINANG_ROT180(this->actor.home.rot.y);
                this->unk_2C4++;
                this->actor.velocity.y = 0.0f;
                this->actor.gravity = 0.0f;
            }
            break;

        case 1:
            Math_SmoothStepToS(&this->unk_348, 0, 1, 0x7D0, 0);
            if ((fabsf(this->actor.world.rot.y - this->unk_34A) < 100.0f) && (fabsf(this->actor.world.rot.x) < 30.0f)) {
                this->unk_2C0++;
                if (this->unk_344 == 0) {
                    if (this->unk_2C0 == 1) {
                        gSaveContext.save.weekEventReg[81] |= 0x10;
                    } else if (this->unk_2C0 == 2) {
                        gSaveContext.save.weekEventReg[81] |= 0x20;
                    } else if (this->unk_2C0 == 3) {
                        gSaveContext.save.weekEventReg[81] |= 0x40;
                    }
                } else if (this->unk_2C0 == 1) {
                    gSaveContext.save.weekEventReg[81] |= 0x80;
                } else if (this->unk_2C0 == 2) {
                    gSaveContext.save.weekEventReg[82] |= 1;
                } else if (this->unk_2C0 == 3) {
                    gSaveContext.save.weekEventReg[82] |= 2;
                }

                if (this->unk_2B0 != 0) {
                    this->unk_2C0 = 5;
                }

                this->unk_2B6 = 4;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FISH_GROW_UP);
                this->unk_2C4++;
            }
            break;

        case 2:
            phi_f0 = 0.1f;

        case 4:
            if (phi_f0 == 0) {
                phi_f0 = 0.3f;
            }

        case 6:
            if (phi_f0 == 0) {
                phi_f0 = 0.5f;
            }

            Math_ApproachF(&this->unk_330, D_80B2B370[this->unk_2C0] * phi_f0, 0.3f, 0.004f);

            if (this->unk_2B6 == 0) {
                Vec3f sp3C;
                s32 i;
                s32 pad2;

                Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
                sp3C.y += -10.0f;

                for (i = 0; i < 30; i++) {
                    func_80B2ADB0(this, &sp3C, 0x46);
                }
                this->unk_2C4++;
                this->unk_2B6 = 2;
            }
            break;

        case 3:
            phi_f0 = 1.3f;

        case 5:
            if (phi_f0 == 0) {
                phi_f0 = 1.5f;
            }

        case 7:
            if (phi_f0 == 0) {
                phi_f0 = 1.7f;
            }

            Math_ApproachF(&this->unk_330, D_80B2B370[this->unk_2C0] * phi_f0, 0.3f, 0.004f);

            if (this->unk_2B6 == 0) {
                this->unk_2B6 = 2;
                this->unk_2C4++;
            }
            break;

        case 8:
            Math_ApproachF(&this->unk_330, D_80B2B370[this->unk_2C0], 0.3f, 0.004f);
            if (this->unk_2B6 == 0) {
                this->unk_2B6 = 30;
                this->unk_2C4++;
            }
            break;

        case 9:
            if (this->unk_2B6 == 0) {
                if (this->unk_2C0 > 3) {
                    this->unk_2C0 = 3;
                    this->unk_2C4 = 0;
                    if (this->unk_2B0 == 0) {
                        this->actionFunc = func_80B29E5C;
                    } else {
                        func_80B2A448(this);
                    }
                } else {
                    this->unk_2B6 = 0;
                    this->unk_2B4 = 0;
                    this->unk_2C4 = 0;
                    if (D_80B2B2EC > 200) {
                        D_80B2B2E4 = 0;
                        D_80B2B2E0 = D_80B2B2EC = 0;
                    } else {
                        D_80B2B2E4 = 3;
                    }

                    this->collider.elements[0].dim.modelSphere.radius = (s32)((this->unk_330 - 0.01f) * 1000.0f) + 5;
                    if (this->collider.elements[0].dim.modelSphere.radius > 15) {
                        this->collider.elements[0].dim.modelSphere.radius = 15;
                    }

                    this->collider.elements[1].dim.modelSphere.radius = (s32)((this->unk_330 - 0.01f) * 1000.0f) + 5;
                    if (this->collider.elements[1].dim.modelSphere.radius > 15) {
                        this->collider.elements[1].dim.modelSphere.radius = 15;
                    }
                    func_80B28B5C(this);
                }
            }
            break;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_34A, 1, 0xFA0, 0);
}

void func_80B29E5C(EnFish2* this, GlobalContext* globalCtx) {
    Actor* prop = globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (prop != NULL) {
        if (prop->id != ACTOR_EN_FISH2) {
            prop = prop->next;
            continue;
        }

        if (&this->actor != prop) {
            this->unk_350 = prop;
            this->unk_2B0 = D_80B2B2E8 = 1;
            func_80B28370(this, 0);
            this->actionFunc = func_80B29EE4;
            break;
        }

        prop = prop->next;
    }
}

void func_80B29EE4(EnFish2* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this->unk_2C4 < 400) {
        this->unk_2C4++;
    }
    this->unk_338 = 410.0f - this->unk_2C4;
    Math_ApproachF(&this->actor.speedXZ, 2.0f, 0.3f, 0.3f);
    Math_ApproachF(&this->unk_350->speedXZ, (D_80B2B380[0] - this->unk_330) * this->unk_338, 0.1f, 0.4f);
    func_80B289DC(this, globalCtx);
    Math_Vec3f_Copy(&sp2C, &this->unk_350->world.pos);
    this->unk_34A = Math_Vec3f_Yaw(&this->actor.world.pos, &sp2C);
    this->unk_348 = Math_Vec3f_Pitch(&this->actor.world.pos, &sp2C);
    if (func_80B288E8(this, this->unk_300, 0)) {
        Math_Vec3f_Copy(&this->unk_30C, &this->unk_350->world.pos);
        func_80B2938C(this);
    }
}

void func_80B2A01C(EnFish2* this, GlobalContext* globalCtx) {
    if (this->unk_2B4 == 0) {
        if (!ActorCutscene_GetCanPlayNext(this->unk_2BA[0])) {
            ActorCutscene_SetIntentToPlay(this->unk_2BA[0]);
        } else {
            this->unk_2B4 = 15;
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_2BA[0], &this->actor);
            this->actionFunc = func_80B2A094;
        }
    }
}

void func_80B2A094(EnFish2* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this->unk_2B4 == 0) {
        D_80B2B2E4 = 1;
    }

    this->unk_2CA = ActorCutscene_GetCurrentCamera(this->unk_2BA[0]);

    if (D_80B2B2EC != 0) {
        D_80B2B2EC++;
        if (D_80B2B2EC > 200) {
            Actor_MarkForDeath(&this->actor);
            ActorCutscene_Stop(this->unk_2BA[0]);
            return;
        }
    }

    if ((this->unk_350 != NULL) && (this->unk_350->update != NULL)) {
        Math_Vec3f_Copy(&sp2C, &this->unk_350->world.pos);
        sp2C.x += Math_SinS(-0x3A98) * 110.0f;
        sp2C.z += Math_CosS(-0x3A98) * 110.0f;
        Math_Vec3f_Copy(&this->unk_2DC, &sp2C);
        Math_Vec3f_Copy(&sp2C, &this->unk_350->world.pos);
        sp2C.x += Math_SinS(-0x3A98) * 10.0f;
        sp2C.z += Math_CosS(-0x3A98) * 10.0f;
        Math_Vec3f_Copy(&this->unk_2E8, &sp2C);
    }

    Play_CameraSetAtEye(globalCtx, this->unk_2CA, &this->unk_2E8, &this->unk_2DC);
    if ((this->unk_350 == NULL) || (this->unk_350->update == NULL)) {
        this->unk_350 = NULL;
        this->unk_2B0++;
        if (this->unk_2B0 > 10) {
            this->unk_2B4 = 20;
            this->actionFunc = func_80B2A23C;
        }
    }
}

void func_80B2A23C(EnFish2* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
    if (D_80B2B2E4 == 2) {
        sp2C.x += (Math_SinS(-0x3A98) * 180.0f);
        sp2C.y += 90.0f;
        sp2C.z += Math_CosS(-0x3A98) * 180.0f;
        Math_Vec3f_Copy(&this->unk_2DC, &sp2C);
        Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
        sp2C.y += 70.0f;
        Math_Vec3f_Copy(&this->unk_2E8, &sp2C);
    } else if (D_80B2B2F4 != NULL) {
        Math_Vec3f_Copy(&sp2C, &D_80B2B2F4->world.pos);
        sp2C.x += Math_SinS(-0x3A98) * 110.0f;
        sp2C.z += Math_CosS(-0x3A98) * 110.0f;
        Math_Vec3f_Copy(&this->unk_2DC, &sp2C);
        Math_Vec3f_Copy(&sp2C, &D_80B2B2F4->world.pos);
        sp2C.x += Math_SinS(-0x3A98) * 10.0f;
        sp2C.z += Math_CosS(-0x3A98) * 10.0f;
        Math_Vec3f_Copy(&this->unk_2E8, &sp2C);
    }

    Play_CameraSetAtEye(globalCtx, this->unk_2CA, &this->unk_2E8, &this->unk_2DC);

    if ((this->unk_2B4 == 0) && (D_80B2B2E4 == 3)) {
        D_80B2B2E0 = D_80B2B2EC = D_80B2B2E4 = 0;
        D_80B2B2F4 = NULL;
        ActorCutscene_Stop(this->unk_2BA[0]);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B2A448(EnFish2* this) {
    func_80B28370(this, 4);
    this->unk_2B4 = 0;
    this->unk_2C4 = 0;
    this->unk_2B6 = this->unk_2B4;
    D_80B2B2E4 = 2;
    this->actionFunc = func_80B2A498;
}

void func_80B2A498(EnFish2* this, GlobalContext* globalCtx) {
    f32 currentFrame = this->skelAnime.curFrame;
    Vec3f sp80;

    if ((this->unk_2AC == 4) && Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor* temp_v0;

        Math_Vec3f_Copy(&sp80, &this->unk_318);
        temp_v0 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_COL_MAN, sp80.x, sp80.y, sp80.z, 0,
                              this->actor.world.rot.y, 0, 0);
        if (temp_v0 != NULL) {
            temp_v0->speedXZ = 4.0f;
            temp_v0->velocity.y = 15.0f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_PIECE_OF_HEART);
            gSaveContext.save.weekEventReg[81] &= (u8)~0x10;
            gSaveContext.save.weekEventReg[81] &= (u8)~0x20;
            gSaveContext.save.weekEventReg[81] &= (u8)~0x40;
            gSaveContext.save.weekEventReg[81] &= (u8)~0x80;
            gSaveContext.save.weekEventReg[82] &= (u8)~1;
            gSaveContext.save.weekEventReg[82] &= (u8)~2;
        }
    }

    if ((this->unk_2AC == 4) &&
        (Animation_OnFrame(&this->skelAnime, 13.0f) || Animation_OnFrame(&this->skelAnime, 31.0f))) {
        WaterBox* sp78;

        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                 &this->unk_334, &sp78)) {
            Vec3f sp6C;
            s32 i;

            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 50, NA_SE_EV_BOMB_DROP_WATER);

            for (i = 0; i < 10; i++) {
                Math_Vec3f_Copy(&sp6C, &this->actor.world.pos);
                sp6C.x += randPlusMinusPoint5Scaled(70.0f);
                sp6C.y = this->unk_334 + 10.0f;
                sp6C.z += randPlusMinusPoint5Scaled(70.0f);
                EffectSsGSplash_Spawn(globalCtx, &sp6C, NULL, NULL, 0, (s32)randPlusMinusPoint5Scaled(50.0f) + 350);
            }
        }
    }

    if ((this->unk_2CC <= currentFrame) && (this->unk_2AC == 4)) {
        D_80B2B2E0 = 0;
        D_80B2B2E4 = 3;
        this->actor.world.pos.x = this->unk_324.x;
        this->actor.world.pos.z = this->unk_324.z;
        func_80B28370(this, 0);
    }
}

void EnFish2_Update(Actor* thisx, GlobalContext* globalCtx2) {
    static f32 D_80B2B3A8[] = {
        0.0f, 40.0f, -40.0f, 0.0f, 0.0f, 0.0f,
    };
    GlobalContext* globalCtx = globalCtx2;
    EnFish2* this = THIS;

    if ((this->actionFunc != func_80B295A4) && (this->actor.params != 1)) {
        SkelAnime_Update(&this->skelAnime);
    }

    if (this->unk_2B8 != 0) {
        this->unk_2B8--;
    }

    if (this->unk_2B6 != 0) {
        this->unk_2B6--;
    }

    if (this->unk_2B4 == 0) {
    } else {
        this->unk_2B4--;
    }

    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->actor, 0);

    if (this->actor.params != 1) {
        WaterBox* sp6C;
        s32 i;
        Vec3f sp5C;

        if (this->actor.params == 0) {
            Math_SmoothStepToS(&this->actor.world.rot.x, this->unk_348, 1, this->unk_34C + 200, 0);
            if (this->actionFunc != func_80B297FC) {
                Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_34A, 1, 0xBB8, 0);
            }
        }

        if ((globalCtx->gameplayFrames % 8) == 0) {
            Math_Vec3f_Copy(&sp5C, &this->unk_324);
            sp5C.x += randPlusMinusPoint5Scaled(100.0f);
            sp5C.y = this->actor.floorHeight;
            sp5C.z += randPlusMinusPoint5Scaled(100.0f);

            for (i = 0; i < (s32)randPlusMinusPoint5Scaled(5.0f) + 10; i++) {
                EffectSsBubble_Spawn(globalCtx, &sp5C, 0, 5.0f, 5.0f, Rand_ZeroFloat(this->unk_330 * 4.0f) + 0.1f);
            }
        }

        func_80B2AF80(this, globalCtx);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->unk_2F4, &this->actor.world.pos);
        this->unk_2F4.x += (Math_SinS(this->actor.world.rot.y) * 25.0f) - this->unk_330;
        this->unk_2F4.z += (Math_CosS(this->actor.world.rot.y) * 25.0f) - this->unk_330;
        this->unk_33C = 25.0f - ((this->unk_330 - 0.01f) * 1000.0f);
        Actor_SetScale(&this->actor, this->unk_330);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0, 15.0f, 10.0f, 7);

        if (this->actor.params != 2) {
            this->unk_2D4 = this->actor.floorHeight + (this->unk_330 * 1000.0f);
            this->unk_2D8 = this->unk_330 * 600.0f;
            if (this->actor.world.pos.y < this->unk_2D4) {
                this->actor.world.pos.y = this->unk_2D4 + 0.1f;
            }

            if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                     &this->unk_334, &sp6C)) {
                if ((this->unk_334 != BGCHECK_Y_MIN) && (this->unk_334 - this->unk_2D8 < this->actor.world.pos.y)) {
                    this->actor.world.pos.y = this->unk_334 - this->unk_2D8;
                }
            }

            if ((D_80B2B2E8 == 0) && (this->actionFunc == func_80B28C14)) {
                s32 temp_s0_2 = this->unk_344 * 2;
                f32 phi_f2 = 0.0f;
                f32 phi_f20 = 0;
                WaterBox* sp4C;

                if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x,
                                         this->actor.world.pos.z, &this->unk_334, &sp4C)) {
                    phi_f20 = D_80B2B3A8[temp_s0_2] + (this->unk_334 - this->unk_2D8);
                    phi_f2 = D_80B2B3A8[temp_s0_2 + 1] + this->unk_2D4;
                }

                if ((phi_f20 < this->actor.world.pos.y) && (this->unk_348 < 0)) {
                    this->unk_348 = 0;
                    this->actor.velocity.y = 0;
                    this->actor.gravity = 0;
                }

                if ((this->actor.world.pos.y < phi_f2) && (this->unk_348 > 0)) {
                    this->unk_348 = 0;
                    this->actor.velocity.y = 0;
                    this->actor.gravity = 0;
                }
            }

            if (D_80B2B2E8 == 0) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }
    }
}

s32 EnFish2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnFish2* this = THIS;

    if ((limbIndex == 20) || (limbIndex == 21)) {
        *dList = NULL;
    }

    return false;
}

void EnFish2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnFish2* this = THIS;
    s32 pad;

    if ((limbIndex == 20) || (limbIndex == 21)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_StatePush();
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, *dList);

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 14) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_318);
    }

    if (limbIndex == 17) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_300);
    }

    Collider_UpdateSpheres(limbIndex, &this->collider);
}

void EnFish2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFish2* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnFish2_OverrideLimbDraw, EnFish2_PostLimbDraw, &this->actor);
    func_80B2B180(this, globalCtx);
}

void func_80B2ADB0(EnFish2* this, Vec3f* vec, s16 arg2) {
    s16 i;
    EnFish2UnkStruct* ptr = &this->unk_3F8[0];

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++, ptr++) {
        if (!ptr->unk_00) {
            TexturePtr phi_v0;

            if (Rand_ZeroOne() < 0.5f) {
                phi_v0 = gEffBubble2Tex;
            } else {
                phi_v0 = gEffBubble1Tex;
            }

            ptr->unk_20 = VIRTUAL_TO_PHYSICAL(SEGMENTED_TO_VIRTUAL(phi_v0));
            ptr->unk_00 = true;
            ptr->unk_04 = *vec;
            ptr->unk_04.x += randPlusMinusPoint5Scaled(ptr->unk_00 + (this->unk_330 * 4000.0f));
            ptr->unk_04.y += randPlusMinusPoint5Scaled(20.0f);
            ptr->unk_04.z += randPlusMinusPoint5Scaled(ptr->unk_00 + (this->unk_330 * 4000.0f));
            ptr->unk_18 = (this->unk_330 * 20.0f) - (Rand_ZeroFloat(5.0f) * 0.01f);
            ptr->unk_1C = 0x42;
            ptr->unk_10 = arg2;
            break;
        }
    }
}

void func_80B2AF80(EnFish2* this, GlobalContext* globalCtx) {
    EnFish2UnkStruct* ptr = &this->unk_3F8[0];
    WaterBox* sp90;
    f32 sp8C;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++, ptr++) {
        if (ptr->unk_00) {
            if ((ptr->unk_10 != 0) && (ptr->unk_1C != 0)) {
                Math_ApproachF(&ptr->unk_14, ptr->unk_18, 0.4f, 0.5f);
                ptr->unk_10--;
            } else {
                ptr->unk_00 = 0;
            }

            if (ptr->unk_00) {
                ptr->unk_04.x += (0.3f + (Rand_ZeroOne() * 0.5f)) - 0.55f;
                ptr->unk_04.y += 1.0f + ((Rand_ZeroOne() - 0.3f) * 1.2f);
                ptr->unk_04.z += (0.3f + (Rand_ZeroOne() * 0.5f)) - 0.55f;
                sp8C = ptr->unk_04.y;
                if (!WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, ptr->unk_04.x, ptr->unk_04.z, &sp8C, &sp90)) {
                    ptr->unk_00 = 0;
                } else if (sp8C < ptr->unk_04.y) {
                    Vec3f sp7C;

                    sp7C.x = ptr->unk_04.x;
                    sp7C.y = sp8C;
                    sp7C.z = ptr->unk_04.z;
                    EffectSsGRipple_Spawn(globalCtx, &sp7C, 0, 80, 0);
                    ptr->unk_00 = 0;
                }
            }
        }
    }
}

void func_80B2B180(EnFish2* this, GlobalContext* globalCtx) {
    s16 i;
    EnFish2UnkStruct* ptr;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    ptr = &this->unk_3F8[0];
    func_8012C28C(gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++, ptr++) {
        if (ptr->unk_00) {
            Matrix_InsertTranslation(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);
            Matrix_Scale(ptr->unk_14, ptr->unk_14, ptr->unk_14, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(POLY_OPA_DISP++, 150, 150, 150, 0);
            gSPSegment(POLY_OPA_DISP++, 0x08, ptr->unk_20);
            gSPDisplayList(POLY_OPA_DISP++, gEffBubbleDL);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
