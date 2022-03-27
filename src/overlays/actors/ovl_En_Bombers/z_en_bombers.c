/*
 * File: z_en_bombers.c
 * Overlay: ovl_En_Bombers
 * Description: Bombers - Blue-Hatted Bomber
 */

#include "z_en_bombers.h"
#include "overlays/actors/ovl_En_Bom_Bowl_Man/z_en_bom_bowl_man.h"
#include "objects/object_cs/object_cs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBombers*)thisx)

void EnBombers_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C03ACC(EnBombers* this);
void func_80C03AF4(EnBombers* this, GlobalContext* globalCtx);
void func_80C03F64(EnBombers* this);
void func_80C03FAC(EnBombers* this, GlobalContext* globalCtx);
void func_80C042F8(EnBombers* this);
void func_80C04354(EnBombers* this, GlobalContext* globalCtx);
void func_80C043C8(EnBombers* this, GlobalContext* globalCtx);

const ActorInit En_Bombers_InitVars = {
    ACTOR_EN_BOMBERS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBombers),
    (ActorFunc)EnBombers_Init,
    (ActorFunc)EnBombers_Destroy,
    (ActorFunc)EnBombers_Update,
    (ActorFunc)EnBombers_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
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
    { 10, 30, 0, { 0, 0, 0 } },
};

AnimationHeader* D_80C0479C[] = {
    &gBomberIdleAnim,       &object_cs_Anim_0053F4, &object_cs_Anim_01007C, &object_cs_Anim_00349C,
    &object_cs_Anim_004960, &object_cs_Anim_005128, &object_cs_Anim_004C1C, &object_cs_Anim_001A1C,
    &object_cs_Anim_003EE4, &object_cs_Anim_00478C, &object_cs_Anim_00433C, &object_cs_Anim_0060E8,
    &object_cs_Anim_001708, &object_cs_Anim_005DC4, &object_cs_Anim_0026B0, &object_cs_Anim_0036B0,
    &object_cs_Anim_0031C4,
};

u8 D_80C047E0[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP,
    ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP,
    ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP,
};

#include "overlays/ovl_En_Bombers/ovl_En_Bombers.c"

Gfx* D_80C04818[] = {
    ovl_En_Bombers_DL_12C8, ovl_En_Bombers_DL_12D8, ovl_En_Bombers_DL_12D8,
    ovl_En_Bombers_DL_12D8, ovl_En_Bombers_DL_12D8,
};

TexturePtr D_80C0482C[] = {
    object_cs_Tex_00C520,
    object_cs_Tex_00CD20,
    object_cs_Tex_00D520,
};

TexturePtr D_80C04838[] = {
    object_cs_Tex_00E620, object_cs_Tex_00EA20, object_cs_Tex_00EE20, object_cs_Tex_00DD20, object_cs_Tex_00F220,
};

void EnBombers_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBombers* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    this->actor.gravity = -1.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_cs_Skel_00F82C, &gBomberIdleAnim, this->jointTable,
                       this->morphtable, 21);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.targetMode = 0;
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_2BC = ENBOMBERS_GET_F0(&this->actor);
    this->unk_2BE = ENBOMBERS_GET_F(&this->actor);

    if (this->unk_2BC == ENBOMBERS_F0_0) {
        if ((gSaveContext.save.weekEventReg[73] & 0x10) || (gSaveContext.save.weekEventReg[85] & 2)) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->unk_2BE++;
            func_80C03ACC(this);
        }
    } else if (((gSaveContext.save.weekEventReg[73] & 0x10) || (gSaveContext.save.weekEventReg[85] & 2)) &&
               (((this->unk_2BE == ENBOMBERS_F_0) && (gSaveContext.save.weekEventReg[76] & 1)) ||
                ((this->unk_2BE == ENBOMBERS_F_1) && (gSaveContext.save.weekEventReg[76] & 2)) ||
                ((this->unk_2BE == ENBOMBERS_F_2) && (gSaveContext.save.weekEventReg[76] & 4)) ||
                ((this->unk_2BE == ENBOMBERS_F_3) && (gSaveContext.save.weekEventReg[76] & 8)) ||
                ((this->unk_2BE == ENBOMBERS_F_4) && (gSaveContext.save.weekEventReg[76] & 0x10)))) {
        if (gSaveContext.save.weekEventReg[75] & 0x40) {
            if (this->unk_2BE == ENBOMBERS_F_0) {
                EnBomBowlMan* bomBowlMan = (EnBomBowlMan*)Actor_Spawn(
                    &globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM_BOWL_MAN, this->actor.world.pos.x,
                    this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 0);

                if (bomBowlMan != NULL) {
                    s32 cs = this->actor.cutscene;
                    s32 i = 0;

                    // clang-format off
                    while (cs != -1) { bomBowlMan->unk_2CC[i] = cs; cs = ActorCutscene_GetAdditionalCutscene(cs); i++; }
                    // clang-format on

                    gSaveContext.save.weekEventReg[76] &= (u8)~1;
                    gSaveContext.save.weekEventReg[76] &= (u8)~2;
                    gSaveContext.save.weekEventReg[76] &= (u8)~4;
                    gSaveContext.save.weekEventReg[76] &= (u8)~8;
                    gSaveContext.save.weekEventReg[76] &= (u8)~0x10;
                }
            }
            Actor_MarkForDeath(&this->actor);
        } else {
            func_80C042F8(this);
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBombers_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBombers* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80C03824(EnBombers* this, s32 arg1, f32 arg2) {
    this->unk_2C4 = arg1;
    this->unk_2B0 = Animation_GetLastFrame(D_80C0479C[arg1]);
    Animation_Change(&this->skelAnime, D_80C0479C[this->unk_2C4], arg2, 0.0f, this->unk_2B0, D_80C047E0[this->unk_2C4],
                     -10.0f);
}

void func_80C038B4(EnBombers* this) {
    if ((this->unk_2C4 == 2) &&
        (Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 10.0f) ||
         Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 18.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2C4 == 15) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 2.0f) ||
         Animation_OnFrame(&this->skelAnime, 4.0f) || Animation_OnFrame(&this->skelAnime, 6.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }
}

void func_80C039A8(EnBombers* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    this->unk_2A6 = 5;

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            this->actor.textId = 0x73D;
            if (gSaveContext.save.weekEventReg[84] & 0x80) {
                this->actor.textId = 0x74B;
            }
            break;

        case PLAYER_FORM_GORON:
            this->actor.textId = 0x73E;
            break;

        case PLAYER_FORM_ZORA:
            this->actor.textId = 0x73F;
            break;

        case PLAYER_FORM_DEKU:
            if (gSaveContext.save.weekEventReg[73] & 0x20) {
                this->actor.textId = 0x75A;
            } else if (gSaveContext.save.weekEventReg[73] & 0x40) {
                this->actor.textId = 0x749;
                if (((this->unk_2BE == ENBOMBERS_F_1) && (gSaveContext.save.weekEventReg[74] & 1)) ||
                    ((this->unk_2BE == ENBOMBERS_F_2) && (gSaveContext.save.weekEventReg[74] & 2)) ||
                    ((this->unk_2BE == ENBOMBERS_F_3) && (gSaveContext.save.weekEventReg[74] & 4)) ||
                    ((this->unk_2BE == ENBOMBERS_F_4) && (gSaveContext.save.weekEventReg[74] & 8))) {
                    this->actor.textId = 0x74A;
                }
            } else {
                this->actor.textId = 0x744;
            }
            break;
    }
}

void func_80C03ACC(EnBombers* this) {
    this->collider.dim.radius = 10;
    this->collider.dim.height = 30;
    this->unk_2C0 = 0;
    this->actionFunc = func_80C03AF4;
}

void func_80C03AF4(EnBombers* this, GlobalContext* globalCtx) {
    CollisionPoly* colPoly;
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    f32 x;
    f32 z;
    s32 sp48;
    s16 abs;

    switch (this->unk_2A0) {
        case 0:
            if (this->unk_2A8 == 0) {
                Math_Vec3f_Copy(&sp60, &this->actor.home.pos);

                sp60.x += randPlusMinusPoint5Scaled(150.0f);
                sp60.z += randPlusMinusPoint5Scaled(150.0f);

                abs = ABS_ALT(BINANG_SUB(this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp60)));
                if ((abs < 0x4000) && !BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp60, &sp6C,
                                                               &colPoly, true, false, false, true, &sp48)) {
                    func_80C03824(this, 2, 1.0f);
                    Math_Vec3f_Copy(&this->unk_294, &sp60);
                    this->unk_2AA = Rand_S16Offset(30, 50);
                    this->unk_2A0++;
                }
            }
            break;

        case 1:
            if (curFrame >= 0.0f) {
                this->unk_2A4 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_294);
                Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2A4, 0xA, 0x7D0, 0x14);
            }

            if ((s16)ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->unk_2A4)) < 0x100) {
                Math_Vec3f_Copy(&sp54, &this->actor.world.pos);
                sp54.x += Math_SinS(this->actor.world.rot.y) * 60.0f;
                sp54.z += Math_CosS(this->actor.world.rot.y) * 60.0f;

                if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp54, &sp6C, &colPoly, true,
                                            false, false, true, &sp48)) {
                    this->unk_2A8 = 0;
                    if (Rand_ZeroOne() < 0.5f) {
                        func_80C03824(this, 16, 1.0f);
                    } else {
                        func_80C03824(this, 0, 1.0f);
                    }
                    this->unk_2A0 = 0;
                    this->unk_2B4 = 0.0f;
                    break;
                }
            }

            x = this->unk_294.x - this->actor.world.pos.x;
            z = this->unk_294.z - this->actor.world.pos.z;

            if ((this->unk_2AA == 0) || (sqrtf(SQ(x) + SQ(z)) < 4.0f)) {
                this->unk_2A8 = Rand_S16Offset(20, 20);
                if (!(this->unk_2A8 & 1)) {
                    func_80C03824(this, 16, 1.0f);
                } else {
                    func_80C03824(this, 0, 1.0f);
                }
                this->unk_2A0 = 0;
                this->unk_2B4 = 0.0f;
            } else if (curFrame >= 0.0f) {
                Math_ApproachF(&this->actor.world.pos.x, this->unk_294.x, 0.3f, this->unk_2B4);
                Math_ApproachF(&this->actor.world.pos.z, this->unk_294.z, 0.3f, this->unk_2B4);
                Math_ApproachF(&this->unk_2B4, 1.0f, 0.3f, 0.5f);
            }
            break;
    }

    if (!Text_GetFaceReaction(globalCtx, 0x12)) {
        func_80C039A8(this, globalCtx);
    } else {
        this->unk_2A6 = 5;
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x12);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2A4 = this->actor.yawTowardsPlayer;
        this->collider.dim.radius = 20;
        this->collider.dim.height = 60;
        func_80C03F64(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80C03F64(EnBombers* this) {
    this->unk_2A4 = this->actor.yawTowardsPlayer;
    func_80C03824(this, 1, 1.0f);
    this->unk_2C0 = 1;
    this->actionFunc = func_80C03FAC;
}

void func_80C03FAC(EnBombers* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp2A;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2A4, 1, 0x1388, 0);

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            this->unk_28E = -0xFA0;
            break;

        case PLAYER_FORM_GORON:
        case PLAYER_FORM_ZORA:
            this->unk_28E = -0x1770;
            break;
    }

    if ((this->unk_2A6 == Message_GetState(&globalCtx->msgCtx)) && Message_ShouldAdvance(globalCtx)) {
        sp2A = 0;
        func_801477B4(globalCtx);
        this->unk_2A6 = 5;

        if ((this->actor.textId == 0x73D) || (this->actor.textId == 0x73E) || (this->actor.textId == 0x73F)) {
            this->actor.textId = 0x740;
            this->unk_2A6 = 4;
            sp2A = 1;
        } else if (this->actor.textId == 0x740) {
            if (globalCtx->msgCtx.choiceIndex == 0) {
                func_8019F208();
                this->actor.textId = 0x742;
                sp2A = 1;
            } else {
                func_8019F230();
                this->actor.textId = 0x741;
                sp2A = 1;
            }
        } else if (this->actor.textId == 0x742) {
            this->actor.textId = 0x737;
            sp2A = 1;
        } else if (this->actor.textId == 0x737) {
            this->actor.textId = 0x743;
            sp2A = 1;
        } else if (this->actor.textId == 0x74B) {
            this->actor.textId = 0x74C;
            this->unk_2A6 = 4;
            sp2A = 1;
        } else if (this->actor.textId == 0x74C) {
            if (globalCtx->msgCtx.choiceIndex == 1) {
                func_8019F230();
                this->actor.textId = 0x737;
                sp2A = 1;
            } else {
                func_8019F208();
                this->actor.textId = 0x74D;
                func_80C03824(this, 14, 1.0f);
                sp2A = 1;
            }
        } else if (this->actor.textId == 0x744) {
            s32 day = gSaveContext.save.day - 1;

            if (day == 2) {
                this->actor.textId = 0x746;
                sp2A = 1;
            } else {
                this->actor.textId = 0x745;
                sp2A = 1;
            }
        } else if ((this->actor.textId == 0x745) || (this->actor.textId == 0x746)) {
            this->actor.textId = 0x747;
            sp2A = 1;
        } else if (this->actor.textId == 0x747) {
            this->actor.textId = 0x748;
            sp2A = 1;
        } else if (this->actor.textId == 0x748) {
            switch (this->unk_2BE) {
                case ENBOMBERS_F_1:
                    gSaveContext.save.weekEventReg[74] |= 1;
                    break;

                case ENBOMBERS_F_2:
                    gSaveContext.save.weekEventReg[74] |= 2;
                    break;

                case ENBOMBERS_F_3:
                    gSaveContext.save.weekEventReg[74] |= 4;
                    break;

                case ENBOMBERS_F_4:
                    gSaveContext.save.weekEventReg[74] |= 8;
                    break;
            }
            gSaveContext.save.weekEventReg[73] |= 0x40;
        }

        switch (sp2A) {
            case 0:
                this->unk_28E = 0;
                func_80C03ACC(this);
                break;

            case 1:
                func_80151938(globalCtx, this->actor.textId);
                break;
        }
    }
}

void func_80C042F8(EnBombers* this) {
    if (this->unk_2C4 != 6) {
        func_80C03824(this, 6, 1.0f);
    }
    this->actor.textId = 0x72D;
    this->unk_28E = 0x1F40;
    this->unk_2C0 = 2;
    this->actionFunc = func_80C04354;
}

void func_80C04354(EnBombers* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 0x3E8, 0);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_28E = 0;
        this->actionFunc = func_80C043C8;
    } else {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80C043C8(EnBombers* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 0x3E8, 0);
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80C042F8(this);
    }
}

void EnBombers_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBombers* this = THIS;

    if (this->unk_2AA != 0) {
        this->unk_2AA--;
    }

    if (this->unk_2A8 != 0) {
        this->unk_2A8--;
    }

    if (this->unk_2AC != 0) {
        this->unk_2AC--;
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_80C038B4(this);
    Actor_SetFocus(&this->actor, 20.0f);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_28A, this->unk_290, 1, 0x1388, 0);
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 0x1388, 0);

    if (this->unk_2BA == 0) {
        this->unk_2B8++;
        if (this->unk_2B8 >= 3) {
            this->unk_2B8 = 0;
            this->unk_2BA = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    this->actor.uncullZoneForward = 500.0f;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnBombers_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnBombers* this = THIS;

    if (limbIndex == OBJECT_CS_LIMB_0F) {
        *dList = NULL;
    }

    if (limbIndex == OBJECT_CS_LIMB_11) {
        rot->x += this->unk_28A;
        rot->z += this->unk_288;
    }

    if (limbIndex == OBJECT_CS_LIMB_13) {
        *dList = NULL;
    }

    return false;
}

void EnBombers_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBombers* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C0482C[this->unk_2B8]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C04838[this->unk_2BE]));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80C04818[this->unk_2BE]));

    Scene_SetRenderModeXlu(globalCtx, 0, 1);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBombers_OverrideLimbDraw, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
