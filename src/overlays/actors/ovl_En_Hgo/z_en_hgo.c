/*
 * File: z_en_pamera.c
 * Overlay: En_Hgo
 * Description: Pamela's Father As a Gibdo
 */

#include "z_en_hgo.h"

#define FLAGS 0x02000019

#define THIS ((EnHgo*)thisx)

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD03EC(EnHgo* this);
void func_80BD0410(EnHgo* this, GlobalContext* globalCtx);
void func_80BD0434(EnHgo* this, GlobalContext* globalCtx);
void func_80BD049C(EnHgo* this);
void func_80BD04E0(EnHgo* this, GlobalContext* globalCtx);
void func_80BD064C(EnHgo* this);
void func_80BD0660(EnHgo* this, GlobalContext* globalCtx);
void func_80BD06FC(EnHgo* this, GlobalContext* globalCtx);
s32 func_80BD0898(EnHgo* this, GlobalContext* globalCtx);
s32 EnHgo_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnHgo_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx);

extern FlexSkeletonHeader D_06012A58;
extern AnimationHeader D_0600B644;
extern AnimationHeader D_06013684;
extern AnimationHeader D_060152EC;
extern AnimationHeader D_06015C70;
extern AnimationHeader D_060165F0;
extern AnimationHeader D_06014220;
extern AnimationHeader D_06014A9C;
extern Gfx D_0600F248[];
extern UNK_TYPE4 D_06011138;
extern UNK_TYPE4 D_06011938;
extern UNK_TYPE4 D_06012138;

const ActorInit En_Hgo_InitVars = {
    ACTOR_EN_HGO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw,
};

static ActorAnimationEntry sAnimations[] = {
    { &D_0600B644, 1.0f, 0.0f, 0.0f, 0, -4.0f }, { &D_06013684, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &D_060152EC, 1.0f, 0.0f, 0.0f, 2, 0.0f },  { &D_06015C70, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &D_060165F0, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &D_06014220, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &D_06014A9C, 1.0f, 0.0f, 0.0f, 0, 0.0f },
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
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// Eye Textures
static UNK_TYPE4* D_80BD0F80[] = {
    &D_06011138,
    &D_06011938,
    &D_06012138,
};

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;
    s32 pad;

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 36.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06012A58, &D_0600B644, this->limbDrawTbl,
                       this->transitionDrawTbl, 19);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, NULL, &sColChkInfoInit);
    thisx->targetMode = 6;
    this->unk_30C = 0;
    this->unk_30E = 0;
    this->unk_314 = 0;
    this->unk_310 = 0;
    this->unk_312 = 0;
    if (gSaveContext.weekEventReg[75] & 0x20 || gSaveContext.weekEventReg[52] & 0x20) {
        func_80BD049C(this);
    } else {
        thisx->draw = NULL;
        func_80BD03EC(this);
    }
}

void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BD03EC(EnHgo* this) {
    this->actor.flags &= -2;
    this->actionFunc = &func_80BD0410;
}

void func_80BD0410(EnHgo* this, GlobalContext* globalCtx) {
}

void func_80BD0420(EnHgo* this) {
    this->actionFunc = func_80BD0434;
}

void func_80BD0434(EnHgo* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.focus.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.focus.pos.z;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80BD049C(EnHgo* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80BD04E0;
}

void func_80BD04E0(EnHgo* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO_MASK) {
            if (!(this->unk_310 & 4)) {
                this->unk_310 |= 4;
                func_801518B0(globalCtx, 0x15A5, &this->actor);
                this->unk_314 = 0x15A5;

            } else {
                func_801518B0(globalCtx, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7;
            }
        } else if (gSaveContext.playerForm == 4) {
            if (!(this->unk_310 & 1)) {
                this->unk_310 |= 1;
                func_801518B0(globalCtx, 0x158F, &this->actor);
                this->unk_314 = 0x158F;
            } else {
                func_801518B0(globalCtx, 0x1593, &this->actor);
                this->unk_314 = 0x1593;
            }
        } else {
            if (!(this->unk_310 & 2)) {
                this->unk_310 |= 2;
                func_801518B0(globalCtx, 0x1595, &this->actor);
                this->unk_314 = 0x1595;
            } else {
                func_801518B0(globalCtx, 0x1598, &this->actor);
                this->unk_314 = 0x1598;
            }
        }
        func_80BD064C(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80BD064C(EnHgo* this) {
    this->actionFunc = func_80BD0660;
}

void func_80BD0660(EnHgo* this, GlobalContext* globalCtx) {

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            func_80BD06FC(this, globalCtx);
            break;
        case 6:
            if (func_80147624(globalCtx)) {
                func_80BD049C(this);
            }
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x71C, 0xB6);
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80BD06FC(EnHgo* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->unk_314) {
            case 5519:
                func_801518B0(globalCtx, 0x1590, &this->actor);
                this->unk_314 = 0x1590;
                break;
            case 5520:
                if ((gSaveContext.weekEventReg[14]) & 4) {
                    func_801518B0(globalCtx, 0x1591, &this->actor);
                    this->unk_314 = 0x1591;
                    break;
                }
                func_801518B0(globalCtx, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 5521:
                func_801518B0(globalCtx, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 5523:
                func_801518B0(globalCtx, 0x1594, &this->actor);
                this->unk_314 = 0x1594;
                break;
            case 5525:
                func_801518B0(globalCtx, 0x1596, &this->actor);
                this->unk_314 = 0x1596;
                break;
            case 5526:
                func_801518B0(globalCtx, 0x1597, &this->actor);
                this->unk_314 = 0x1597;
                break;
            case 5528:
                func_801518B0(globalCtx, 0x1599, &this->actor);
                this->unk_314 = 0x1599;
                break;
            case 5541:
                func_801518B0(globalCtx, 0x15A6, &this->actor);
                this->unk_314 = 0x15A6;
                break;
            case 5542:
                func_801518B0(globalCtx, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7;
                break;
            case 5543:
                func_801477B4(globalCtx);
                func_80BD049C(this);
                break;
        }
    }
}

s32 func_80BD0898(EnHgo* this, GlobalContext* globalCtx) {
    u32 actionIndex;

    if (func_800EE29C(globalCtx, 0x1E6U) != 0) {
        actionIndex = func_800EE200(globalCtx, 0x1E6);
        if (this->unk_316 != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
            this->unk_316 = globalCtx->csCtx.npcActions[actionIndex]->unk0;
            switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                case 1:
                    this->unk_218 = 0;
                    func_800BDC5C(&this->skelAnime, sAnimations, 0);
                    break;
                case 2:
                    this->actor.draw = EnHgo_Draw;
                    this->unk_218 = 1;
                    func_800BDC5C(&this->skelAnime, sAnimations, 1);
                    break;
                case 3:
                    this->unk_218 = 2;
                    func_800BDC5C(&this->skelAnime, sAnimations, 2);
                    break;
                case 4:
                    this->unk_218 = 3;
                    func_800BDC5C(&this->skelAnime, sAnimations, 3);
                    break;
                case 5:
                    this->unk_218 = 4;
                    func_800BDC5C(&this->skelAnime, sAnimations, 4);
                    break;
                case 6:
                    this->unk_218 = 5;
                    func_800BDC5C(&this->skelAnime, sAnimations, 5);
                    break;
            }
        } else {
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                switch (this->unk_218) {
                    case 1:
                        if ((Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) &&
                                (this->unk_312 == 0)) {
                            this->unk_312 = 1;
                            if ((gSaveContext.sceneSetupIndex == 0) &&
                                ((globalCtx->csCtx.unk_12 == 2) || (globalCtx->csCtx.unk_12 == 4))) {
                                Audio_PlayActorSound2(&this->actor, NA_SE_VO_GBVO02);
                            }
                        }
                        break;
                    case 2:
                        this->unk_218 = 3;
                        func_800BDC5C(&this->skelAnime, sAnimations, 3);
                        break;
                    case 5:
                        this->unk_218 = 6;
                        func_800BDC5C(&this->skelAnime, sAnimations, 6);

                }
            }
        }
        func_800EDF24(&this->actor, globalCtx, actionIndex);
        return 1;
    }
    if ((globalCtx->csCtx.state == 0) && (((gSaveContext.weekEventReg[75]) & 0x20) != 0) &&
        (this->actionFunc == func_80BD0410)) {
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xC6, this->actor.focus.pos.x, this->actor.focus.pos.y,
                    this->actor.focus.pos.z, 7, 0, 0, 0x7F5A);
        func_80BD0420(this);
    }
    this->unk_316 = 0x63;
    return 0;
}

void func_80BD0B8C(EnHgo* this, GlobalContext* globalCtx) {
    func_800E9250(globalCtx, &this->actor, &this->unk_300, &this->unk_306, this->actor.focus.pos);
    if (this->unk_30E >= 3) {
        this->unk_30E--;
    } else if (this->unk_30E == 2) {
        this->unk_30C = 1;
        this->unk_30E = 1;
    } else if (this->unk_30E == 1) {
        this->unk_30C = 2;
        this->unk_30E = 0;
    } else {
        this->unk_30C = 0;
        this->unk_30E = 0x3C;
    }
}

void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    if (func_80BD0898(this, globalCtx)) {
        func_800E8F08(&this->unk_300, &this->unk_306);
    } else {
        if (this->actionFunc != func_80BD0410) {
            if (this->actionFunc != func_80BD0434) {
                Collider_UpdateCylinder(&this->actor, &this->collider);
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                func_80BD0B8C(this, globalCtx);
            }
        }
    }
}

s32 EnHgo_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == 11) {
        rot->x += this->unk_300.y;
        rot->z += this->unk_300.x;
    }
    return false;
}

void EnHgo_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == 11) {
        Matrix_CopyCurrentState(&this->unk_1D8);
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BD0F80[this->unk_30C]));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHgo_OverrideLimbDraw, EnHgo_PostLimbDraw, &this->actor);
    Matrix_SetCurrentState(&this->unk_1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0600F248);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
