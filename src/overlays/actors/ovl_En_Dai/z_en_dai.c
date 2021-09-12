/*
 * File: z_en_dai.c
 * Overlay: ovl_En_Dai
 * Description: Biggoron
 */

#include "z_en_dai.h"

#define FLAGS 0x02000039

#define THIS ((EnDai*)thisx)

void EnDai_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B3F00C(EnDai* this, GlobalContext* globalCtx);
void func_80B3EEDC(EnDai* this, GlobalContext* globalCtx);
void func_80B3EF90(EnDai* this, GlobalContext* globalCtx);

extern AnimationHeader D_060107B0;
extern AnimationHeader D_06010FB0;
extern AnimationHeader D_060117B0;
extern AnimationHeader D_06010FB0;
extern AnimationHeader D_06011FB0;
extern AnimationHeader D_060127B0;
extern AnimationHeader D_060079E4;
extern AnimationHeader D_06007354;
extern AnimationHeader D_06000CEC;
extern AnimationHeader D_060069DC;
extern AnimationHeader D_0600563C;
extern AnimationHeader D_06002E58;
extern AnimationHeader D_06006590;
extern FlexSkeletonHeader D_060130D0;
extern Gfx D_06000230[];
extern Gfx D_060002E8[];
extern Gfx D_0600C538[];

const ActorInit En_Dai_InitVars = {
    ACTOR_EN_DAI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnDai),
    (ActorFunc)EnDai_Init,
    (ActorFunc)EnDai_Destroy,
    (ActorFunc)EnDai_Update,
    (ActorFunc)EnDai_Draw,
};

static Vec3f D_80B3FBF0 = { 1.0f, 1.0f, 1.0f };

EnDaiParticle* func_80B3DFF0(EnDaiParticle* particle, Vec3f arg1, Vec3f arg2, Vec3f arg3, f32 arg4, f32 arg5,
                             s32 arg6) {
    s32 i;

    for (i = 0; i < 32; i++, particle++) {
        if (!particle->isEnabled) {
            particle->isEnabled = true;
            particle->unk_01 = (Rand_ZeroOne() * (2.0f * (arg6 / 3.0f))) + (arg6 / 3.0f);
            particle->unk_02 = particle->unk_01;
            particle->unk_10 = arg1;
            particle->unk_1C = arg2;
            particle->unk_28 = arg3;
            particle->unk_34 = arg4;
            particle->unk_38 = arg5;
            return particle;
        }
    }

    return NULL;
}

void func_80B3E168(EnDaiParticle* particle, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;
    s32 isDisplayListSet = false;
    s32 i;
    f32 alpha;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 32; i++, particle++) {
        if (particle->isEnabled == true) {
            gDPPipeSync(POLY_XLU_DISP++);

            if (!isDisplayListSet) {
                gSPDisplayList(POLY_XLU_DISP++, D_06000230);
                isDisplayListSet = true;
            }

            SysMatrix_StatePush();

            alpha = (particle->unk_02 / (f32)particle->unk_01);
            alpha *= 255.0f;

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, (u8)alpha);

            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (particle->unk_02 + (i * 3)) * 3,
                                        (particle->unk_02 + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

            SysMatrix_InsertTranslation(particle->unk_10.x, particle->unk_10.y, particle->unk_10.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(particle->unk_34, particle->unk_34, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_060002E8);

            SysMatrix_StatePop();
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80B3E460(EnDai* this) {
    EnDaiParticle* particle = &this->particles[0];
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (particle->isEnabled && particle->unk_02) {
            particle->unk_10.x += particle->unk_28.x;
            particle->unk_02--;
            particle->unk_10.y += particle->unk_28.y;
            particle->unk_10.z += particle->unk_28.z;
            particle->unk_28.x += particle->unk_1C.x;
            particle->unk_28.y += particle->unk_1C.y;
            particle->unk_28.z += particle->unk_1C.z;
            particle->unk_34 += particle->unk_38;
            count++;
        } else if (particle->isEnabled) {
            particle->isEnabled = false;
        }
    }

    return count;
}

s32 func_80B3E5B4(EnDai* this, GlobalContext* globalCtx) {
    func_80B3E168(this->particles, globalCtx);
    return 0;
}

s32 func_80B3E5DC(EnDai* this, s32 arg1) {
    static ActorAnimationEntryS D_80B3FBFC[] = {
        { &D_060079E4, 1.0f, 0, -1, 0, 0 },  { &D_060079E4, 1.0f, 0, -1, 0, -4 }, { &D_06007354, 1.0f, 0, -1, 2, -4 },
        { &D_06000CEC, 1.0f, 0, -1, 2, -4 }, { &D_060069DC, 1.0f, 0, -1, 2, -4 }, { &D_0600563C, 1.0f, 0, -1, 2, 0 },
        { &D_0600563C, 1.0f, 0, -1, 2, -4 }, { &D_06002E58, 1.0f, 0, -1, 0, -4 }, { &D_06006590, 1.0f, 0, -1, 2, -4 },
    };

    s32 phi_v1 = false;
    s32 ret = 0;

    switch (arg1) {
        case 0:
        case 1:
            if ((this->unk_A70 != 0) && (this->unk_A70 != 1)) {
                phi_v1 = true;
            }
            break;

        case 5:
        case 6:
            if ((this->unk_A70 != 5) && (this->unk_A70 != 6)) {
                phi_v1 = true;
            }
            break;

        default:
            if (arg1 != this->unk_A70) {
                phi_v1 = true;
            }
            break;
    }

    if (phi_v1) {
        this->unk_A70 = arg1;
        ret = func_8013BC6C(&this->skelAnime, D_80B3FBFC, arg1);
    }

    return ret;
}

s32 func_80B3E69C(EnDai* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((globalCtx->csCtx.state != 0) && (globalCtx->sceneNum == SCENE_12HAKUGINMAE) &&
        (globalCtx->csCtx.unk_12 == 0) && !(gSaveContext.weekEventReg[30] & 1)) {
        if (!(this->unk_1CE & 0x10)) {
            Actor_SetSwitchFlag(globalCtx, 20);
            this->unk_1CE |= (0x80 | 0x10);
            this->unk_1CE &= ~(0x100 | 0x20);
            this->unk_1CC = 0xFF;
            this->unk_1DC = 0;
            this->unk_1CD = 0;
            this->unk_1F0 = D_80B3FBF0;
            this->unk_1FC = D_80B3FBF0;
        }
        ret = true;
    } else if (this->unk_1CE & 0x10) {
        this->unk_1CE &= ~0x10;
        this->unk_1CE |= 0x200;
        gSaveContext.weekEventReg[30] |= 1;
        this->actionFunc = func_80B3F00C;
    }

    return ret;
}

s32 func_80B3E7C8(EnDai* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (this->unk_1CE & 7) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            func_8013AED4(&this->unk_1CE, 0, 7);
            this->actionFunc = func_80B3EF90;
            ret = true;
        }
    }

    return ret;
}

void func_80B3E834(EnDai* this) {
    s16 phi_v1;

    if (this->unk_1CE & 0x80) {
        if (this->unk_1D8 == 0) {
            phi_v1 = 0;
        } else {
            this->unk_1D8--;
            phi_v1 = this->unk_1D8;
        }

        if (phi_v1 == 0) {
            this->unk_1D6++;
            if (this->unk_1D6 >= 5) {
                this->unk_1D8 = Rand_S16Offset(20, 20);
                this->unk_1D6 = 0;
            }
        }
    }
}

// Some kind of struct?
static s32 D_80B3FC8C[] = {
    0x0100060E, 0x0C900C12, 0x10005520, 0x00110E0C, 0x910C0F0C,
    0x920C0F0C, 0x930C1211, 0x5520100E, 0x0C940C12, 0x10000000,
};

s16 func_80B3E8BC(EnDai* this, s32 arg1) {
    static f32 D_80B3FCB4[] = {
        1.0f, 6.0f, 16.0f, 19.0f, 46.0f, 48.0f, 50.0f, 52.0f, 54.0f, 1.0f, 6.0f, 36.0f,
    };

    static f32 D_80B3FCE4[] = {
        5.0f, 15.0f, 18.0f, 45.0f, 47.0f, 49.0f, 51.0f, 53.0f, 55.0f, 5.0f, 35.0f, 45.0f,
    };

    static s16 D_80B3FD14[] = {
        4, 5, 2, 0, 4, 5, 2, 5, 4, 4, 5, 2,
    };

    s32 i;
    s32 end;

    if (arg1 == 3) {
        end = 9;
        i = 0;
    } else if (arg1 == 4) {
        end = 12;
        i = 9;
    } else {
        return 2;
    }

    while (i < end) {
        if ((D_80B3FCB4[i] <= this->skelAnime.animCurrentFrame) &&
            (D_80B3FCE4[i] >= this->skelAnime.animCurrentFrame)) {
            return D_80B3FD14[i];
        }
        i++;
    }

    return this->unk_1D6;
}

s32 func_80B3E96C(EnDai* this, GlobalContext* globalCtx) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;

    if ((DECR(this->unk_1DA) == 0) &&
        ((this->unk_1DC == 0) || func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount))) {
        switch (this->unk_1DC) {
            case 0:
                func_80B3E5DC(this, 2);
                this->unk_1DC++;
                break;

            case 1:
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_SNOWSTORM_HARD);
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WEATHER_TAG, this->actor.world.pos.x,
                            this->actor.world.pos.y, this->actor.world.pos.z, 0x1388, 0x708, 0x3E8, 0);
                func_80B3E5DC(this, 3);
                this->unk_1DC++;
                break;

            case 2:
                func_80B3E5DC(this, 4);
                this->unk_1DC++;
                break;

            case 3:
                func_80B3E5DC(this, 1);
                this->unk_1F0 = D_80B3FBF0;
                this->unk_1FC = D_80B3FBF0;
                this->unk_1DC = 0;
                this->unk_1DA = Rand_S16Offset(20, 20);
                break;
        }
    } else if (this->unk_1DC == 2) {
        sp50.x = sp50.y = 0.0f;
        sp50.z = 200.0f;

        sp68.x = sp68.z = 0.0f;
        sp68.y = 6.0f;

        sp5C.x = Math_SinS(this->unk_1D4) * 80.0f;
        sp5C.z = Math_CosS(this->unk_1D4) * 80.0f;
        sp5C.y = -40.0f;

        Lib_Vec3f_TranslateAndRotateY(&this->unk_1E4, this->unk_1D4, &sp50, &sp74);
        func_80B3DFF0(this->particles, sp74, sp68, sp5C, 0.03f, 0.04f, 0x10);
    }

    return 0;
}

void func_80B3EC10(f32 arg0, Vec3f arg1, f32 arg2, Vec3f arg3, f32 arg4, Vec3f* arg5) {
    f32 temp_f0 = (arg4 - arg0) / (arg2 - arg0);

    arg5->x = ((arg3.x - arg1.x) * temp_f0) + arg1.x;
    arg5->y = ((arg3.y - arg1.y) * temp_f0) + arg1.y;
    arg5->z = ((arg3.z - arg1.z) * temp_f0) + arg1.z;
}

s32 func_80B3EC84(EnDai* this) {
    static f32 D_80B3FD2C[] = {
        6.0f, 11.0f, 15.0f, 0.0f, 12.0f, 17.0f, 0.0f, 3.0f,
    };

    static f32 D_80B3FD4C[] = {
        8.0f, 15.0f, 24.0f, 4.0f, 17.0f, 26.0f, 3.0f, 7.0f,
    };

    static s16 D_80B3FD6C[] = {
        1, 1, 1, 2, 2, 2, 3, 3,
    };

    static Vec3f D_80B3FD7C[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.8f, 0.8f },   { 1.0f, 1.1f, 1.1f }, { 1.0f, 1.3f, 1.3f }, { 1.0f, 0.7f, 0.9f },
        { 1.0f, 0.8f, 0.9f },  { 1.0f, 0.7f, 0.9f }, { 1.0f, 0.8f, 0.9f },  { 1.0f, 1.0f, 1.0f },
    };

    s32 i;
    s32 ret = false;

    for (i = 0; i < ARRAY_COUNT(D_80B3FD6C); i++) {
        if ((this->unk_1DC == D_80B3FD6C[i]) && (D_80B3FD2C[i] < this->skelAnime.animCurrentFrame) &&
            (D_80B3FD4C[i] >= this->skelAnime.animCurrentFrame)) {
            func_80B3EC10(D_80B3FD2C[i], D_80B3FD7C[i], D_80B3FD4C[i], D_80B3FD7C[i + 1],
                          this->skelAnime.animCurrentFrame, &this->unk_1F0);
            ret = true;
            break;
        }
    }

    return ret;
}

s32 func_80B3ED88(EnDai* this) {
    static f32 D_80B3FDE8[] = { 22.0f, 0.0f, 0.0f };
    static f32 D_80B3FDF4[] = { 29.0f, 3.0f, 9.0f };
    static s16 D_80B3FE00[] = { 1, 2, 3 };
    static Vec3f D_80B3FE08[] = {
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.2f, 1.2f },
        { 1.0f, 0.7f, 0.8f },
        { 1.0f, 1.0f, 1.0f },
    };

    s32 i;
    s32 ret = false;

    for (i = 0; i < ARRAY_COUNT(D_80B3FE00); i++) {
        if ((this->unk_1DC == D_80B3FE00[i]) && (D_80B3FDE8[i] < this->skelAnime.animCurrentFrame) &&
            (D_80B3FDF4[i] >= this->skelAnime.animCurrentFrame)) {
            func_80B3EC10(D_80B3FDE8[i], D_80B3FE08[i], D_80B3FDF4[i], D_80B3FE08[i + 1],
                          this->skelAnime.animCurrentFrame, &this->unk_1FC);
            ret = true;
            break;
        }
    }

    return ret;
}

void func_80B3EE8C(EnDai* this, GlobalContext* globalCtx) {
    s16 cutscene = this->actor.cutscene;

    if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->actor);
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

void func_80B3EEDC(EnDai* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((player->transformation == PLAYER_FORM_GORON) && (globalCtx->msgCtx.unk1202A == 3) &&
        (globalCtx->msgCtx.unk1202E == 1)) {
        func_80B3E5DC(this, 1);
        this->actionFunc = func_80B3EE8C;
    } else if (!(player->stateFlags2 & 0x08000000)) {
        func_80B3E96C(this, globalCtx);
        this->unk_A6C = 0;
    } else if (this->unk_A6C == 0) {
        play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        this->unk_A6C = 1;
    }
}

void func_80B3EF90(EnDai* this, GlobalContext* globalCtx) {
    if (func_8010BF58(&this->actor, globalCtx, D_80B3FC8C, NULL, &this->unk_1D0)) {
        func_8013AED4(&this->unk_1CE, 3, 7);
        this->unk_1D0 = 0;
        this->actionFunc = func_80B3F00C;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x2AA8);
    }
}

void func_80B3F00C(EnDai* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80B3F044(EnDai* this, GlobalContext* globalCtx) {
    static s32 D_80B3FE38[] = {
        0, 0, 6, 7, 8,
    };

    s32 sp2C = 0;
    s32 sp28;

    if (func_800EE29C(globalCtx, 0x1D8)) {
        sp2C = func_800EE200(globalCtx, 0x1D8);
        sp28 = globalCtx->csCtx.npcActions[sp2C]->unk0;
        if (this->unk_1CC != (u8)sp28) {
            func_80B3E5DC(this, D_80B3FE38[sp28]);
            switch (sp28) {
                case 1:
                    this->unk_1E0 = 0.0f;
                    break;

                case 2:
                    Audio_PlayActorSound2(&this->actor, NA_SE_EV_ROLL_AND_FALL);
                    break;

                case 3:
                    this->unk_1CE &= ~0x80;
                    break;
            }
        }
        this->unk_1CC = sp28;
    }

    switch (this->unk_1CC) {
        case 1:
            this->unk_1E0 += 1.0f;
            if (this->unk_1E0 < 30.0f) {
                this->unk_1CD = (this->unk_1E0 / 30.0f) * 255.0f;
            } else {
                this->unk_1CD = 0xFF;
            }
            break;

        case 2:
            if (globalCtx->csCtx.frames == 360) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIGOLON_SLEEP3 - SFX_FLAG);
            }
            if (func_801378B8(&this->skelAnime, 43.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_GORON_BOUND_1);
            }
            this->unk_1D6 = func_80B3E8BC(this, this->unk_1CC);
            break;

        case 3:
            if (func_801378B8(&this->skelAnime, 6.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIGOLON_SLEEP1);
            }
            this->unk_1D6 = func_80B3E8BC(this, this->unk_1CC);
            break;

        case 4:
            if (func_801378B8(&this->skelAnime, 30.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIGOLON_SLEEP2);
            }
            if (func_801378B8(&this->skelAnime, 35.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_GORON_BOUND_0);
            }
            this->unk_1D6 = func_80B3E8BC(this, this->unk_1CC);
            break;
    }

    func_800EDF24(&this->actor, globalCtx, sp2C);
}

void EnDai_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDai* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 0.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060130D0, NULL, this->jointTable, this->morphTable, 19);
    this->unk_A70 = -1;
    func_80B3E5DC(this, 0);
    Actor_SetScale(&this->actor, 0.2f);
    this->actor.targetMode = 10;
    this->unk_1F0 = D_80B3FBF0;
    this->unk_1FC = D_80B3FBF0;
    this->unk_1CE = 0;
    this->unk_1D6 = 0;

    if (gSaveContext.weekEventReg[33] & 0x80) {
        func_8013AED4(&this->unk_1CE, 3, 7);
        this->unk_1CE |= 0x80;
        this->unk_1CD = 0xFF;
        this->actionFunc = func_80B3F00C;
        return;
    }

    if (gSaveContext.weekEventReg[30] & 1) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_1CD = 0;
    this->actor.flags &= ~1;
    this->unk_1CE |= (0x100 | 0x20);
    this->unk_1CE |= 0x80;
    this->actionFunc = func_80B3EEDC;
}

void EnDai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnDai_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDai* this = THIS;
    s32 pad;
    Player* player = PLAYER;

    if (!func_80B3E7C8(this, globalCtx) && func_80B3E69C(this, globalCtx)) {
        func_80B3F044(this, globalCtx);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80B3E834(this);
        func_80B3E460(this);
    } else {
        this->actionFunc(this, globalCtx);
        if (!(player->stateFlags2 & 0x8000000)) {
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            func_80B3E834(this);
            if (!(this->unk_1CE & 0x200)) {
                func_8013C964(&this->actor, globalCtx, 0.0f, 0.0f, 0, this->unk_1CE & 7);
            }
            func_80B3E460(this);
        }
    }
}

s32 func_80B3F598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnDai* this = THIS;

    if (!(this->unk_1CE & 0x40)) {
        *dList = NULL;
    }

    if (limbIndex == 11) {
        SysMatrix_MultiplyVector3fByState(&D_801D15B0, &this->unk_1E4);
    }

    if (limbIndex == 10) {
        *dList = NULL;
    }

    return 0;
}

void func_80B3F614(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80B3FE4C = { 0.0f, 0.0f, 0.0f };
    EnDai* this = THIS;
    Vec3s sp64;
    MtxF sp24;

    switch (limbIndex) {
        case 11:
            D_80B3FE4C.x = sREG(0);
            D_80B3FE4C.y = sREG(1);
            D_80B3FE4C.z = sREG(2);
            SysMatrix_MultiplyVector3fByState(&D_80B3FE4C, &this->actor.focus.pos);
            Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            SysMatrix_CopyCurrentState(&sp24);
            func_8018219C(&sp24, &sp64, 0);
            this->unk_1D4 = BINANG_SUB(sp64.y, 0x4000);
            break;

        case 10:
            SysMatrix_CopyCurrentState(&this->unk_18C);
            break;
    }
}

void func_80B3F6EC(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx, Gfx** gfx) {
    EnDai* this = THIS;

    switch (limbIndex) {
        case 9:
            if (this->unk_1CE & 0x100) {
                func_80B3EC84(this);
            }
            Matrix_Scale(this->unk_1F0.x, this->unk_1F0.y, this->unk_1F0.z, MTXMODE_APPLY);
            break;

        case 2:
            if (this->unk_1CE & 0x100) {
                func_80B3ED88(this);
            }
            Matrix_Scale(this->unk_1FC.x, this->unk_1FC.y, this->unk_1FC.z, MTXMODE_APPLY);
            break;
    }
}

void func_80B3F78C(EnDai* this, GlobalContext* globalCtx) {
    static AnimationHeader* D_80B3FE58[] = {
        &D_060107B0, &D_06010FB0, &D_060117B0, &D_06010FB0, &D_06011FB0, &D_060127B0,
    };

    s32 pad;

    if (globalCtx->actorCtx.unkB != 0) {
        this->unk_1CE |= 0x40;
    } else {
        Actor_RecordUndrawnActor(globalCtx, &this->actor);
        this->unk_1CE &= ~0x40;
    }

    func_8012C2DC(globalCtx->state.gfxCtx);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Scene_SetRenderModeXlu(globalCtx, 2, 2);

    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B3FE58[this->unk_1D6]));

    POLY_XLU_DISP =
        func_8013AB00(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                      func_80B3F598, func_80B3F614, func_80B3F6EC, &this->actor, POLY_XLU_DISP);
    if (this->unk_1CE & 0x40) {
        SysMatrix_SetCurrentState(&this->unk_18C);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, D_0600C538);
    }

    func_80B3E5B4(this, globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B3F920(EnDai* this, GlobalContext* globalCtx) {
    static AnimationHeader* D_80B3FE70[] = {
        &D_060107B0, &D_06010FB0, &D_060117B0, &D_06010FB0, &D_06011FB0, &D_060127B0,
    };

    s32 pad;

    this->unk_1CE |= 0x40;
    if (this->unk_1CD == 0xFF) {
        func_8012C28C(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B3FE70[this->unk_1D6]));

        POLY_OPA_DISP =
            func_8013AB00(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                          func_80B3F598, func_80B3F614, func_80B3F6EC, &this->actor, POLY_OPA_DISP);
        SysMatrix_SetCurrentState(&this->unk_18C);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_0600C538);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Scene_SetRenderModeXlu(globalCtx, 2, 2);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_1CD);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B3FE70[this->unk_1D6]));

        POLY_XLU_DISP =
            func_8013AB00(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                          func_80B3F598, func_80B3F614, func_80B3F6EC, &this->actor, POLY_XLU_DISP);
        SysMatrix_SetCurrentState(&this->unk_18C);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, D_0600C538);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    func_80B3E5B4(this, globalCtx);
}

void EnDai_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDai* this = THIS;

    if (!(this->unk_1CE & 0x200)) {
        if (this->unk_1CE & 0x20) {
            func_80B3F78C(this, globalCtx);
        } else {
            func_80B3F920(this, globalCtx);
        }
    }
}
