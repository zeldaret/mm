/*
 * File: z_en_daiku.c
 * Overlay: ovl_En_Daiku
 * Description: Carpenter
 */

#include "z_en_daiku.h"
#include "objects/object_daiku/object_daiku.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDaiku*)thisx)

void EnDaiku_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80943820(EnDaiku* this);
void func_80943BC0(EnDaiku* this);
void func_80943BDC(EnDaiku* this, GlobalContext* globalCtx);
void func_809438F8(EnDaiku* this, GlobalContext* globalCtx);

const ActorInit En_Daiku_InitVars = {
    ACTOR_EN_DAIKU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnDaiku),
    (ActorFunc)EnDaiku_Init,
    (ActorFunc)EnDaiku_Destroy,
    (ActorFunc)EnDaiku_Update,
    (ActorFunc)EnDaiku_Draw,
};

static u16 sTextIds[] = {
    0x061C, 0x061A, 0x061B, 0x061C, 0x061C, 0x061D, 0x061E, 0x061F, 0x061C, 0x0620, 0x0621, 0x0622,
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
    { 20, 60, 0, { 0, 0, 0 } },
};

void EnDaiku_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDaiku* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    this->actor.targetMode = 0;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_278 = ENDAIKU_GET_FF(&this->actor);
    if (this->unk_278 == ENDAIKU_PARAMS_FF_3) {
        this->unk_288 = ENDAIKU_GET_FF00(&this->actor);
        this->unk_258 = SubS_GetPathByIndex(globalCtx, this->unk_288, 0x3F);
    } else if (this->unk_278 == ENDAIKU_PARAMS_FF_2) {
        this->unk_264 = -2000;
    }

    if (this->unk_278 == ENDAIKU_PARAMS_FF_0) {
        this->collider.dim.radius = 30;
        this->collider.dim.height = 60;
        this->collider.dim.yShift = 0;
        this->actor.flags |= ACTOR_FLAG_8000000;
        if ((gSaveContext.save.weekEventReg[63] & 0x80) ||
            ((gSaveContext.save.day == 3) && gSaveContext.save.isNight)) {
            Actor_MarkForDeath(&this->actor);
        }
    } else if ((gSaveContext.save.day == 3) && gSaveContext.save.isNight) {
        Actor_MarkForDeath(&this->actor);
    }

    Math_Vec3f_Copy(&this->unk_26C, &this->actor.world.pos);
    this->unk_280 = this->actor.world.rot.y;
    this->actor.gravity = -3.0f;

    switch (this->unk_278) {
        case ENDAIKU_PARAMS_FF_0:
            this->unk_27E = this->unk_278 * 4 + 4;

        case ENDAIKU_PARAMS_FF_1:
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_002FA0,
                               this->jointTable, this->morphTable, 17);
            break;

        case ENDAIKU_PARAMS_FF_2:
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_00B690,
                               this->jointTable, this->morphTable, 17);
            break;

        case ENDAIKU_PARAMS_FF_3:
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_001114,
                               this->jointTable, this->morphTable, 17);
            break;
    }

    func_80943820(this);
}

void EnDaiku_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDaiku* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_8094373C(EnDaiku* this, s32 arg1) {
    static AnimationHeader* D_809440A4[] = {
        &object_daiku_Anim_002FA0, &object_daiku_Anim_00ACD0, &object_daiku_Anim_00C92C,
        &object_daiku_Anim_000C44, &object_daiku_Anim_00C234, &object_daiku_Anim_000600,
        &object_daiku_Anim_001114, &object_daiku_Anim_00B690, &object_daiku_Anim_00BEAC,
    };
    static u8 D_809440C8[] = {
        0, 0, 0, 0, 2, 0, 0, 2, 2,
    };

    this->unk_284 = Animation_GetLastFrame(D_809440A4[arg1]);
    Animation_Change(&this->skelAnime, D_809440A4[arg1], 1.0f, 0.0f, this->unk_284, D_809440C8[arg1], -4.0f);
}

void func_809437C8(EnDaiku* this) {
    if ((this->unk_288 != -1) && (this->unk_258 != 0)) {
        if (!SubS_CopyPointFromPath(this->unk_258, this->unk_25C, &this->unk_26C)) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80943820(EnDaiku* this) {
    s32 day = gSaveContext.save.day - 1;

    switch (this->unk_278) {
        case 0:
        case 1:
            func_8094373C(this, 0);
            break;

        case 2:
            func_8094373C(this, 7);
            break;

        case 3:
            func_8094373C(this, 6);
            break;
    }

    this->unk_28C = (day * 4) + this->unk_278;
    this->actor.textId = sTextIds[this->unk_28C];
    this->unk_280 = this->actor.shape.rot.y;
    this->unk_28A = 0;
    this->actionFunc = func_809438F8;
}

void func_809438F8(EnDaiku* this, GlobalContext* globalCtx) {
    f32 currentFrame = this->skelAnime.curFrame;
    s32 pad;
    s32 day = gSaveContext.save.day - 1;
    s32 pad2;

    if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
        if (this->unk_278 == ENDAIKU_PARAMS_FF_1) {
            this->actor.textId = 0x2365;
        } else {
            this->actor.textId = 0x2366;
        }
    } else {
        this->unk_28C = (day * 4) + this->unk_278;
        this->actor.textId = sTextIds[this->unk_28C];
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80943BC0(this);
        return;
    }

    if ((this->unk_278 == ENDAIKU_PARAMS_FF_2) && (this->unk_284 <= currentFrame)) {
        if (Rand_ZeroOne() < 0.5f) {
            func_8094373C(this, 7);
        } else {
            func_8094373C(this, 8);
        }
    }

    if (this->unk_278 == ENDAIKU_PARAMS_FF_3) {
        f32 sq, abs;

        Math_ApproachF(&this->actor.world.pos.x, this->unk_26C.x, 0.5f,
                       fabsf(2.0f * Math_SinS(this->actor.world.rot.y)));
        Math_ApproachF(&this->actor.world.pos.z, this->unk_26C.z, 0.5f,
                       fabsf(2.0f * Math_CosS(this->actor.world.rot.y)));
        Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_282, 1, 0x7D0, 0xA);

        sq = sqrtf(SQ(this->actor.world.pos.x - this->unk_26C.x) + SQ(this->actor.world.pos.z - this->unk_26C.z));
        abs = fabsf(this->actor.world.rot.y - this->unk_282);
        if ((sq < SQ(2.0f)) && (this->unk_258 != NULL) && (abs < 10.0f)) {
            this->unk_25C++;
            if (this->unk_25C >= this->unk_258->count) {
                this->unk_25C = 0;
            }

            func_809437C8(this);
            this->unk_282 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_26C);
        }
    }

    if (this->unk_278 != ENDAIKU_PARAMS_FF_0) {
        s16 angle = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y));
        this->unk_280 = this->actor.yawTowardsPlayer;
        if ((this->unk_278 == ENDAIKU_PARAMS_FF_1) || (this->unk_278 == ENDAIKU_PARAMS_FF_2) || (angle <= 0x2890)) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

void func_80943BC0(EnDaiku* this) {
    this->unk_28A = 1;
    this->actionFunc = func_80943BDC;
}

void func_80943BDC(EnDaiku* this, GlobalContext* globalCtx) {
    f32 currentFrame = this->skelAnime.curFrame;

    if ((this->unk_278 == ENDAIKU_PARAMS_FF_2) && (this->unk_284 <= currentFrame)) {
        if (Rand_ZeroOne() < 0.5f) {
            func_8094373C(this, 7);
        } else {
            func_8094373C(this, 8);
        }
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80943820(this);
    }
}

void EnDaiku_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDaiku* this = THIS;
    s32 pad;

    if (this->unk_27E == 0) {
        SkelAnime_Update(&this->skelAnime);
    }

    if ((this->unk_278 == ENDAIKU_PARAMS_FF_0) && (gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_27C != 0) {
        this->unk_27C--;
    }

    if (this->unk_27E != 0) {
        this->unk_27E--;
    }

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetFocus(&this->actor, 65.0f);
    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_260, this->unk_266, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->unk_25E, this->unk_264, 1, 0xBB8, 0);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    this->actor.uncullZoneForward = 650.0f;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnDaiku_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnDaiku* this = THIS;

    if (limbIndex == 15) {
        rot->x += this->unk_260;
        rot->z += this->unk_25E;
    }

    return false;
}

void EnDaiku_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Gfx* D_809440D4[] = {
        object_daiku_DL_0070C0,
        object_daiku_DL_006FB0,
        object_daiku_DL_006E80,
        object_daiku_DL_006D70,
    };
    EnDaiku* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (limbIndex == 15) {
        gSPDisplayList(POLY_OPA_DISP++, D_809440D4[this->unk_278]);
    }

    if ((this->unk_278 == ENDAIKU_PARAMS_FF_3) && (limbIndex == 8)) {
        gSPDisplayList(POLY_OPA_DISP++, object_daiku_DL_008EC8);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnDaiku_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDaiku* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    switch (this->unk_278) {
        case 0:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 10, 70, 255);
            break;

        case 1:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 200, 255, 255);
            break;

        case 2:
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 230, 70, 255);
            break;

        case 3:
            gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 150, 255);
            break;

        case 4:
            gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 0, 255);
            break;
    }

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDaiku_OverrideLimbDraw, EnDaiku_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
