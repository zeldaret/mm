#include "z_en_hg.h"

#define FLAGS 0x02100019

#define THIS ((EnHg*)thisx)

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BCF354(EnHg* this);
void func_80BCF398(EnHg* this, GlobalContext* globalCtx);
void func_80BCF468(EnHg* this);
void func_80BCF468(EnHg* this);
void func_80BCF4AC(EnHg* this, GlobalContext* globalCtx);
void func_80BCF5F0(EnHg* this);
void func_80BCF634(EnHg* this, GlobalContext* globalCtx);
void func_80BCF68C(EnHg* this);
void func_80BCF6D0(EnHg* this, GlobalContext* globalCtx);

void func_80BCF8A0(EnHg* this, GlobalContext* globalCtx);
void func_80BCF93C(EnHg* this);
void func_80BCF95C(EnHg* this, GlobalContext* globalCtx);

s32 func_80BCFE54(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
s32 func_80BCFE70(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx);

/*
const ActorInit En_Hg_InitVars = {
    ACTOR_EN_HG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHg),
    (ActorFunc)EnHg_Init,
    (ActorFunc)EnHg_Destroy,
    (ActorFunc)EnHg_Update,
    (ActorFunc)EnHg_Draw,
};
*/

ColliderCylinderInit D_80BCFFB0[] = {
    0x00000939, 0x20010000, 0x00000000, 0x00000000, 0x00000000, 0xF7CFFFFF,
    0x00000000, 0x00010100, 0x0012002E, 0x00000000, 0x00000000,
};

// D_80BCFFB0
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
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
    { 18, 46, 0, { 0, 0, 0 } },
};

DamageTable D_80BCFFDC[] = {
    0x10D100F1, 0xC3C3F210, 0xF2F1F123, 0x3341F210, 0xD1F21000, 0x0000F1F1, 0xF1020400, 0x000000F1,
};

CollisionCheckInfoInit2 D_80BCFFFC[] = {
    0x00000000,
    0x00000000,
    0x80000000,
};

ActorAnimationEntry D_80BD0008[] = {
    0x0600260C, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000, 0x06009D44, 0x3F800000,
    0x00000000, 0x00000000, 0x00000000, 0xC0800000, 0x0600A164, 0x3F800000, 0x00000000, 0x00000000,
    0x00000000, 0xC0800000, 0x06000370, 0x3F800000, 0x00000000, 0x00000000, 0x02000000, 0x00000000,
    0x06001138, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x060015D4, 0x3F800000,
    0x00000000, 0x00000000, 0x02000000, 0x00000000, 0x06001960, 0x3F800000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x0600AE1C, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

u32 D_80BD00C8 = 0;

extern FlexSkeletonHeader D_06008580;
extern AnimationHeader D_0600260C;
extern Gfx D_06005E28[];

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;
    s16 phi_s1;
    s32 i;

    phi_s1 = this->actor.cutscene;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06008580, &D_0600260C, &this->limbDrawTbl,
                     &this->transitionDrawTbl, 0x13);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, D_80BCFFB0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, D_80BCFFDC, D_80BCFFFC);
    if ((gSaveContext.weekEventReg[75] & 0x20) || (gSaveContext.weekEventReg[52] & 0x20)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actor.targetMode = 1;
    this->actor.colChkInfo.health = 0;
    this->actor.gravity = -1.0f;
    for (i = 0; i < 4; i++) {
        if (phi_s1 == -1) {
            break;
        }
        this->unk310[i] = phi_s1;
        phi_s1 = ActorCutscene_GetAdditionalCutscene(phi_s1);
    }
    func_80BCF354(this);
}

void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BCF354(EnHg* this) {
    func_800BDC5C(&this->skelAnime, &D_80BD0008, 0);
    this->actionFunc = func_80BCF398;
}

void func_80BCF398(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if ((this->actor.xzDistToPlayer < 200.0f && this->actor.yDistToPlayer < 40.0f) &&
            (func_800EE29C(globalCtx, 0x1E3U) == 0)) {
            func_80BCF468(this);
        }
        if ((gSaveContext.sceneSetupIndex == 0 && globalCtx->csCtx.unk_12 == 0) &&
            (globalCtx->csCtx.frames == 0x14 || globalCtx->csCtx.frames == 0x3C)) {
            Audio_PlayActorSound2(this, 0x3AB8);
        }
    }
}

void func_80BCF468(EnHg* this) {
    func_800BDC5C(&this->skelAnime, D_80BD0008, 1);
    this->actionFunc = func_80BCF4AC;
}

void func_80BCF4AC(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 pad;

    this->actor.speedXZ = 1.6f;
    if (!(player->stateFlags2 & 0x08000000)) {
        if (func_80152498(&globalCtx->msgCtx) == 0) {
            if (((this->skelAnime.animCurrentFrame > 9.0f) && (this->skelAnime.animCurrentFrame < 16.0f)) ||
                (this->skelAnime.animCurrentFrame > 44.0f) && (this->skelAnime.animCurrentFrame < 51.0f)) {
                Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
                Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0x14);
                this->actor.world.rot.y = this->actor.shape.rot.y;
            }
            if ((Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 200.0f) &&
                (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) > 200.0f)) {
                func_80BCF5F0(this);
            }
        }
    }
}

void func_80BCF5F0(EnHg* this) {
    func_800BDC5C(&this->skelAnime, D_80BD0008, 0);
    this->actionFunc = func_80BCF634;
}

void func_80BCF634(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) < 200.0f) {
        func_80BCF468(this);
    }
}

void func_80BCF68C(EnHg* this) {
    func_800BDC5C(&this->skelAnime, D_80BD0008, 2);
    this->actionFunc = func_80BCF6D0;
}

void func_80BCF6D0(EnHg* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        func_80BCF5F0(this);
    }
}

void func_80BCF710(EnHg* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 0) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            func_801518B0(globalCtx, 0x24FU, &this->actor);
        } else {
            func_800B8614(&this->actor, globalCtx, 80.0f);
        }
    }
}

void func_80BCF778(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if (this->actionFunc == func_80BCF4AC || this->actionFunc == func_80BCF6D0 ||
            this->actionFunc == func_80BCF634) {
            func_800B9010(this, 0x32B7);
        }
    }
}

void func_80BCF7D8(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health) {
        if ((this->collider.base.acFlags & 2)) {
            this->collider.base.acFlags &= ~2;
            func_80BCF68C(this);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (this->actionFunc != func_80BCF6D0 && this->actionFunc != func_80BCF8A0 &&
            this->actionFunc != func_80BCF95C) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80BCF88C(EnHg* this) {
    this->actionFunc = func_80BCF8A0;
}

void func_80BCF8A0(EnHg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk310[this->unk218]) != 0) {
        ActorCutscene_Start(this->unk310[this->unk218], &this->actor);
        func_80BCF93C(this);
        return;
    }
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    }
    ActorCutscene_SetIntentToPlay(this->unk310[this->unk218]);
}

void func_80BCF93C(EnHg* this) {
    this->unk310[3] = 0x63;
    this->unk310[2] = 0;
    this->actionFunc = func_80BCF95C;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF95C.asm")
// void func_80BCF95C(EnHg* this, GlobalContext* globalCtx) {
//     u32 actionIndex;
//     s32 temp;

//     if (func_800EE29C(globalCtx, 0x1E4U) != 0) {
//         actionIndex = func_800EE200(globalCtx, 0x1E4U);
//         if (this->unk310[3] != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
//             this->unk310[3] = globalCtx->csCtx.npcActions[actionIndex]->unk0;
//             switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
//                 case 1:
//                     this->unk21C = NULL;
//                     func_800BDC5C(&this->skelAnime, D_80BD0008, 0);
//                     break;
//                 case 2:
//                     this->unk310[2] = 0;
//                     this->unk21C = 3;
//                     func_800BDC5C(&this->skelAnime, D_80BD0008, 3);
//                     break;
//                 case 3:
//                     this->unk310[2] = 0;
//                     this->unk21C = 5;
//                     func_800BDC5C(&this->skelAnime, D_80BD0008, 5);
//                     break;
//                 case 4:
//                     this->unk310[2] = 0;
//                     this->unk21C = 7;
//                     if ((this->unk218 == 1) || (this->unk218 == 3)) {
//                         func_8019F128(0x3ABA);
//                     }
//                     func_800BDC5C(&this->skelAnime, D_80BD0008, 7);
//                     break;
//                 case 5:
//                     this->unk21C = 1;
//                     func_800BDC5C(&this->skelAnime, D_80BD0008, 1);
//                     break;
//                 case 6:
//                     gSaveContext.weekEventReg[75] |= 0x20;
//                     Actor_MarkForDeath(&this->actor);
//                     break;
//             }
//         } else {
//             if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
//                 switch (this->unk21C) {
//                     case 3:
//                         this->unk21C = 4;
//                         func_800BDC5C(&this->skelAnime, D_80BD0008, 4);
//                         break;
//                     case 5:
//                         this->unk21C = 6;
//                         func_800BDC5C(&this->skelAnime, D_80BD0008, 6);
//                         break;
//                 }
//                 // if (this->unk21C != 3) {
//                 //     if (this->unk21C != 5) {

//                 //     } else {
//                 //         this->unk21C = 6;
//                 //         func_800BDC5C(&this->skelAnime, D_80BD0008, 6);
//                 //     }
//                 // } else {
//                 //     this->unk21C = 4;
//                 //     func_800BDC5C(&this->skelAnime, D_80BD0008, 4);
//                 // }
//             }
//         }
//         switch (this->unk21C) {
//             case 0:
//                 func_800B9010(this, 0x32B7);
//                 break;
//             // case 5:
//             case 3:
//                 func_800B9010(this, 0x32B9);
//                 break;
//             case 4:
//                 if (this->unk218 == 0 || this->unk218 == 2) {
//                     func_800B9010(this, 0x32B9);
//                 }
//         }
//         func_800EDF24(this, globalCtx, actionIndex);
//         return;
//     } else if (globalCtx->csCtx.state == 0) {
//         func_80BCF354(this);
//     }
//     this->unk310[3] = 0x63;
// }

void func_80BCFC0C(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->actor.colChkInfo.health == 1 && !(fabsf(this->actor.yDistToPlayer) >= 80.0f)) {
        if ((player->stateFlags2 & 0x08000000)) {
            if (D_80BD00C8 == 0) {
                play_sound(0x4807);
            }
            D_80BD00C8 = 1;
        } else {
            D_80BD00C8 = 0;
        }
        if (globalCtx->msgCtx.unk1202A == 3) {
            if (globalCtx->msgCtx.unk1202E == 7 && gSaveContext.playerForm == 4) {
                if (gSaveContext.inventory.items[gItemSlots[0]] == 0x41) {
                    this->unk218 = 3;
                } else {
                    this->unk218 = 1;
                }
                func_80BCF88C(this);
                return;
            }
        } else {
            if (this->actor.xzDistToPlayer < 60.0f && fabsf(this->actor.yDistToPlayer) < 40.0f) {
                if (this->actionFunc != func_80BCF8A0 && this->actionFunc != func_80BCF95C) {
                    if ((gSaveContext.weekEventReg[61] & 2) == 0) {
                        gSaveContext.weekEventReg[61] |= 2;
                        this->unk218 = NULL;
                    } else {
                        this->unk218 = 2;
                    }
                    func_80BCF88C(this);
                    return;
                }
            }
            func_80BCF710(this, globalCtx);
        }
    }
}

void EnHg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80BCF7D8(this, globalCtx);
    func_80BCFC0C(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 25.0f, 0.0f, 5U);
    func_80BCF778(this, globalCtx);
}

// override limb
s32 func_80BCFE54(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

// post limb
s32 func_80BCFE70(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx) {
    EnHg* this = THIS;
    if (limbIndex == 10) {
        SysMatrix_CopyCurrentState(&this->unk1D8);
        return;
    }
    if (limbIndex == 11) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80BCFE54, func_80BCFE70, &this->actor);
    Matrix_Put(&this->unk1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06005E28);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
