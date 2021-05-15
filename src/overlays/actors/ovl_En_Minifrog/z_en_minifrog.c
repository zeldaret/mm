#include "z_en_minifrog.h"

#define FLAGS 0x00000019

#define THIS ((EnMinifrog*)thisx)

void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx);

EnMinifrog* func_808A3930(GlobalContext* globalCtx);

void func_808A3F88(EnMinifrog* this, GlobalContext* globalCtx);
void func_808A4040(EnMinifrog* this, GlobalContext* globalCtx);
void func_808A410C(EnMinifrog* this, GlobalContext* globalCtx);

void func_808A4AC8(Actor* thisx, GlobalContext* globalCtx);
void func_808A46E8(EnMinifrog* this, GlobalContext* globalCtx);
void func_808A4914(EnMinifrog* this, GlobalContext* globalCtx);

extern AnimationHeader D_060007BC;
extern AnimationHeader D_06001534;
extern SkeletonHeader D_0600B538;
extern UNK_TYPE1 D_0400DEA8;
extern UNK_TYPE1 D_0400E2A8;

const ActorInit En_Minifrog_InitVars = {
    ACTOR_EN_MINIFROG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnMinifrog),
    (ActorFunc)EnMinifrog_Init,
    (ActorFunc)EnMinifrog_Destroy,
    (ActorFunc)EnMinifrog_Update,
    (ActorFunc)EnMinifrog_Draw,
};

// static ColliderCylinderInit sCylinderInit
ColliderCylinderInit D_808A4D40 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 12, 14, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
CollisionCheckInfoInit D_808A4D6C = {
    1,
    12,
    14,
    MASS_IMMOVABLE,
};

s32 D_808A4D74[] = {
    0x060059A0,
    0x06005BA0,
};
u16 D_808A4D7C[] = {
    0x0000, 0x2040, 0x2080, 0x2101, 0x2102, 0x0000,
};

s32 D_808A4D88 = false;

// static InitChainEntry sInitChain
InitChainEntry D_808A4D8C[] = {
    ICHAIN_F32_DIV1000(gravity, -800, ICHAIN_STOP),
};

// primColor
Color_RGBA8 D_808A4D90 = {
    255,
    255,
    255,
    255,
};

// envColor
Color_RGBA8 D_808A4D94 = {
    80,
    80,
    80,
    255,
};

// sEnFrColor
Color_RGBA8 D_808A4D98[] = {
    { 200, 170, 0, 255 }, { 0, 170, 200, 255 }, { 210, 120, 100, 255 }, { 120, 130, 230, 255 }, { 190, 190, 190, 255 },
};

#ifdef NON_MATCHING
void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    int i;

    Actor_ProcessInitChain(&this->actor, D_808A4D8C);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 15.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B538, &D_06001534, this->limbDrawTable,
                     this->transitionDrawTable, 24);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_808A4D6C);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_808A4D40);

    if (D_808A4D88 == false) {
        for (i = 0; i < 2; i++) {
            D_808A4D7C[i] = Lib_SegmentedToVirtual(D_808A4D74[i]);
        }
        D_808A4D88 = true;
    }

    this->frogIndex = (this->actor.params & 0xF);
    if (this->frogIndex >= 5) {
        this->frogIndex = 0;
    }

    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808A4040;
    this->unk_2B2 = 2;
    this->flags = 0;
    this->timer = 0;

    if (((this->actor.params & 0xF0) >> 4) == 0) {
        if ((this->frogIndex == 0) ||
            (((u8)D_808A4D7C[this->frogIndex] & gSaveContext.perm.weekEventReg[this->frogIndex >> 8]) != 0)) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->timer = 30;
            this->actionFunc = func_808A3F88;
            this->actor.textId = 0xD81;
            this->actor.colChkInfo.mass = 30;
        }
    } else {
        if (this->frogIndex == 0) {
            this->actor.textId = 0;
            this->actionFunc = func_808A4914;
            if ((gSaveContext.perm.weekEventReg[34] & 1) == 0) {
                this->actor.flags |= 0x10000;
            }
            this->actor.home.rot.x = this->actor.home.rot.z = 0;
            this->frog = NULL;
        } else {
            this->frog = func_808A3930(globalCtx);
            this->actor.flags &= ~1;
            if (((u8)D_808A4D7C[this->frogIndex] & gSaveContext.perm.weekEventReg[D_808A4D7C[this->frogIndex] >> 8]) !=
                0) {
                this->actionFunc = func_808A410C;
            } else {
                this->actor.draw = NULL;
                this->actor.update = func_808A4AC8;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Init.asm")
#endif

void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (this->flags & 0x100) {
        func_801A1F88();
    }
}

EnMinifrog* func_808A3930(GlobalContext* globalCtx) {
    EnMinifrog* frog = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;

    while (frog != NULL) {
        if ((frog->actor.id != 0x22) || (frog->actor.params & 0xF)) {
            frog = frog->actor.next;
        } else {
            return frog;
        }
    }
    return NULL;
}

void func_808A3980(EnMinifrog* this) {
    if (this->unk_2B2 == 2) {
        this->unk_2B2 = 0;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060007BC, 1.0f, 0.0f, 7.0f, 2, -5.0f);
    }
}

void func_808A39EC(EnMinifrog* this) {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->timer = 60 + (s32)Rand_ZeroFloat(40.0f);
        func_808A3980(this);
    }
}

void func_808A3A44(EnMinifrog* this) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    switch (this->unk_2B2) {
        case 0:
            if (func_801378B8(&this->skelAnime, 4.0f)) {
                this->actor.bgCheckFlags &= ~1;
                this->actor.velocity.y = 6.0f;
                Audio_PlayActorSound2(this, 0x28B1);
                this->unk_2B2 = 1;
            }
            break;
        case 1:
            if (this->actor.bgCheckFlags & 1) {
                this->unk_2B2 = 2;
                SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001534, -2.5f);
                SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            }
            break;
    }
}

void func_808A3B04(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_808A3B3C(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

#ifdef NON_MATCHING
void func_808A3B74(EnMinifrog* this, GlobalContext* globalCtx) {
    Camera* camera = ACTIVE_CAM;
    Vec3f vec1;
    Vec3f vec2;
    Vec3f vec3;
    Vec3f vec4;
    Vec3f vec5;
    s16 pitch;
    s16 yaw;
    s32 i;

    vec4 = camera->eye;
    yaw = Math_Vec3f_Yaw(&vec4, &this->actor.world.pos);
    pitch = -Math_Vec3f_Pitch(&vec4, &this->actor.world.pos);

    vec5.x = this->actor.world.pos.x - (5.0f * Math_SinS(yaw) * Math_CosS(pitch));
    vec5.y = this->actor.world.pos.y - (5.0f * Math_SinS(pitch));
    vec5.z = this->actor.world.pos.z - (5.0f * Math_CosS(yaw) * Math_CosS(pitch));

    for (i = 0; i < 5; i++) {
        vec2.x = randPlusMinusPoint5Scaled(4.0f);
        vec2.y = randPlusMinusPoint5Scaled(4.0f);
        vec2.z = randPlusMinusPoint5Scaled(4.0f);

        vec3.x = -vec2.x * 0.1f;
        vec3.y = -vec2.y * 0.1f;
        vec3.z = -vec2.z * 0.1f;

        vec1.x = vec5.x + vec2.x;
        vec1.y = vec5.y + vec2.y;
        vec1.z = vec5.z + vec2.z;

        func_800B0F80(globalCtx, &vec1, &vec2, &vec3, &D_808A4D90, &D_808A4D94, 300, 30, 10);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B74.asm")
#endif

void func_808A3DA8(EnMinifrog* this, GlobalContext* globalCtx);

// Down to regalloc
#ifdef NON_MATCHING
void func_808A3DA8(EnMinifrog* this, GlobalContext* globalCtx) {
    // s32 temp_t1;
    // s8 temp_a0;
    // u16 temp_t3;
    u16 new_var;
    u16 new_var2;

    func_808A3B04(this);
    func_808A3A44(this);
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        func_808A3980(this);

        switch (globalCtx->msgCtx.unk11F04) {
            case 0xD81:
            case 0xD83:
            case 0xD84:
            case 0xD86:
            case 0xD87:
                // func_80151938(globalCtx, (temp_v0 + 1) & 0xFFFF);
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;
            case 0xD82:
                if (gSaveContext.perm.weekEventReg[33] & 0x80) {
                    func_80151938(globalCtx, 0xD83);
                } else {
                    func_80151938(globalCtx, 0xD86);
                }

                // PERM_RANDOMIZE(
                // if(1) {}
                // temp_t3 = D_808A4D7C[this->frogIndex];
                // temp_t1 = temp_t3 >> 8;
                new_var = D_808A4D7C[this->frogIndex];
                new_var2 = new_var;
                gSaveContext.perm.weekEventReg[D_808A4D7C[this->frogIndex] >> 8] |= new_var2;
                if (1) {}
                // )
                break;
            // case 0xD88:
            case 0xD85:
            default:
                func_801477B4(globalCtx);
                func_808A3B74(this, globalCtx);
                func_800F0568(globalCtx, &this->actor.world.pos, 30, 0x3A87);
                if (this->actor.cutscene != -1) {
                    // temp_a0 = this->actor.cutscene;
                    if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                        ActorCutscene_Stop(this->actor.cutscene);
                    }
                }
                Actor_MarkForDeath(&this->actor);
                return;
                // default:
                //     if(1) {}
        }
    }

    if (this->flags & 1) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            this->flags &= ~1;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3DA8.asm")
#endif

void func_808A3F88(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3A44(this);
    if (this->timer > 0) {
        Actor_SetScale(&this->actor, (0.01f + 0.0003f * this->timer * Math_SinS(0x1000 * (this->timer & 7))));
        this->timer--;
    } else {
        Actor_SetScale(&this->actor, 0.01f);
        this->actionFunc = func_808A4040;
    }
}

void func_808A4040(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3B04(this);
    func_808A3A44(this);
    func_808A39EC(this);
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actionFunc = func_808A3DA8;
        if (this->actor.cutscene != -1) {
            this->flags |= 1;
        }
    } else if ((this->actor.xzDistToPlayer < 100.0f) &&
               (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) != 0) && (func_8012403C(globalCtx) == 0xD)) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void func_808A410C(EnMinifrog* this, GlobalContext* globalCtx) {
    struct EnMinifrog* frog1;
    struct EnMinifrog* frog2;

    func_808A3A44(this);
    frog1 = this->frog;
    if (frog1 != NULL) {
        frog2 = frog1->frog;
        if (frog1->frog != NULL) {
            this->actor.home.rot.y = (s16)(s32)Actor_YawBetweenActors(&this->actor, &frog2->actor);
            func_808A3B3C(this);
        } else {
            func_808A3B04(this);
        }
        if (this->frog->actor.home.rot.z == (this->actor.params & 0xF)) {
            func_808A3980(this);
            this->frog->actor.home.rot.z = 0;
        }
    }
}

void func_808A41A0(EnMinifrog* this, GlobalContext* globalCtx) {
    this->actionFunc = func_808A46E8;
    if (this->frog != NULL) {
        func_80151938(globalCtx, 0xD78U);
    } else {
        func_80151938(globalCtx, 0xD7CU);
    }
    func_808A3980(this);
    this->frog = NULL;
    this->actor.home.rot.z = 0;
}

// TODO: Should match without return's
void func_808A4214(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3A44(this);
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        func_808A41A0(this, globalCtx);
        return;
    }
    if (ActorCutscene_GetCanPlayNext(0x7C)) {
        ActorCutscene_Start(0x7C, NULL);
        func_808A41A0(this, globalCtx);
        return;
    }
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
            ActorCutscene_Stop(this->actor.cutscene);
            ActorCutscene_SetIntentToPlay(0x7C);
            return;
        }
    }
    ActorCutscene_SetIntentToPlay(0x7C);
}

void func_808A42D8(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3B3C(this);
    func_808A3A44(this);
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = func_808A4214;
    }
}

void func_808A4328(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3A44(this);
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = func_808A4214;
        this->flags &= -0x3F;
        globalCtx->unk18798(globalCtx, &D_0400DEA8, 0);
    }
}

void func_808A43A4(EnMinifrog* this, GlobalContext* globalCtx) {
    u8 temp_v0;

    func_808A3A44(this);
    temp_v0 = func_801A39F8();
    if (temp_v0 != 0xFF) {
        if (temp_v0 == 0) {
            func_808A3980(this);
        } else {
            this->actor.home.rot.z = temp_v0;
        }
        if ((this->flags & (2 << temp_v0)) == 0) {
            this->flags |= (2 << temp_v0);
            this->timer--;
        }
    }

    if (this->frog != NULL) {
        this->actor.home.rot.z = 0;
        this->actionFunc = func_808A42D8;
        this->timer = 60;
        this->actor.home.rot.y = Actor_YawBetweenActors(&this->actor, &this->frog->actor);
        func_801A1F88();
        this->flags &= ~0x100;
        this->flags &= ~0x3E;
        globalCtx->unk18798(globalCtx, &D_0400DEA8, 0);
    } else if (this->timer <= 0) {
        this->actionFunc = func_808A4328;
        this->timer = 30;
    }
}

void func_808A44BC(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3A44(this);
    if (this->actor.cutscene == -1) {
        this->actionFunc = func_808A43A4;
    } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actionFunc = func_808A43A4;
        this->timer = 5;
        func_801A1F00(3, 0x5A);
        this->flags |= 0x100;
        globalCtx->unk18798(globalCtx, &D_0400E2A8, 0);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_808A45A8(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3B04(this);
    func_808A3A44(this);
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0xD7EU, &this->actor);
        this->actionFunc = func_808A46E8;
    } else {
        func_800B8500(this, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_808A4634(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3B04(this);
    func_808A3A44(this);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_808A45A8;
        this->actor.flags |= 0x10000;
        func_800B8500(this, globalCtx, 1000.0f, 1000.0f, 0);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0xC, 10000.0f, 50.0f);
    }
}

void func_808A46E8(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3B04(this);
    func_808A3A44(this);
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 4:
            if (func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        this->actionFunc = func_808A44BC;
                        globalCtx->msgCtx.unk11F10 = 0;
                        break;
                    case 1:
                        func_8019F230();
                        func_80151938(globalCtx, 0xD7E);
                        break;
                }
            }
            break;
        case 5:
            if (func_80147624(globalCtx)) {
                func_808A3980(this);
                switch (globalCtx->msgCtx.unk11F04) {
                    case 0xD76:
                        func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                        this->actor.flags &= ~0x10000;
                        gSaveContext.perm.weekEventReg[34] |= 1;
                        break;
                    case 0xD78:
                    case 0xD79:
                    case 0xD7A:
                    case 0xD7F:
                        func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                        break;
                    case 0xD77:
                        this->actionFunc = func_808A44BC;
                        globalCtx->msgCtx.unk11F10 = 0;
                        break;
                    case 0xD7C:
                        if (gSaveContext.perm.weekEventReg[35] & 0x80) {
                            func_80151938(globalCtx, 0xD7E);
                        } else {
                            func_80151938(globalCtx, 0xD7D);
                            gSaveContext.perm.weekEventReg[35] |= 0x80;
                        }
                        break;
                    case 0xD7D:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_808A4634;
                        func_808A4634(this, globalCtx);
                        break;
                    case 0xD7B:
                    case 0xD7E:
                    default:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_808A4914;
                        this->actor.flags &= ~0x10000;
                        break;
                }
            }
    }
}

void func_808A4914(EnMinifrog* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x180);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808A3B04(this);
    func_808A3A44(this);
    func_808A39EC(this);
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actionFunc = func_808A46E8;
        if ((gSaveContext.perm.weekEventReg[34] & 1) == 0) {
            func_801518B0(globalCtx, 0xD76U, &this->actor);
        } else {
            func_801518B0(globalCtx, 0xD7FU, &this->actor);
        }
    } else if ((this->actor.xzDistToPlayer < 150.0f) &&
               (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) ||
                ((this->actor.flags & 0x10000) == 0x10000)) &&
               func_8012403C(globalCtx) == 0xD) {
        func_800B8614(&this->actor, globalCtx, 160.0f);
    }
}

void EnMinifrog_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800B78B8(globalCtx, &this->actor, 25.0f, 12.0f, 0.0f, 0x1D);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    this->actor.focus.rot.y = this->actor.shape.rot.y;
}

void func_808A4AC8(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    struct EnMinifrog* frog;

    frog = this->frog;
    if ((frog != NULL) && (frog->actor.home.rot.z == (this->actor.params & 0xF))) {
        frog->frog = this;
    }
}

s32 EnMinifrog_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                Actor* thisx) {
    if (limbIndex == 1) {
        pos->z -= 500.0f;
    }
    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }
    return 0;
}

void EnMinifrog_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMinifrog* this = THIS;

    if ((limbIndex == 7) || (limbIndex == 8)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, *dList);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    if (limbIndex == 4) {
        SysMatrix_GetStateTranslation(&this->actor.focus);
    }
}

void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    Color_RGBA8* envColor;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    envColor = &D_808A4D98[this->frogIndex];
    gSPSegment(POLY_OPA_DISP++, 0x08, D_808A4D74[0]);
    gSPSegment(POLY_OPA_DISP++, 0x09, D_808A4D74[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, envColor->r, envColor->g, envColor->b, envColor->a);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnMinifrog_OverrideLimbDraw, EnMinifrog_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
