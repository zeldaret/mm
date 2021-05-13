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
extern UNK_TYPE1 D_0400DEA8;
extern UNK_TYPE1 D_0400E2A8;

const ActorInit En_Minifrog_InitVars = { ACTOR_EN_MINIFROG,
                                         ACTORCAT_NPC,
                                         FLAGS,
                                         OBJECT_FR,
                                         sizeof(EnMinifrog),
                                         (ActorFunc)EnMinifrog_Init,
                                         (ActorFunc)EnMinifrog_Destroy,
                                         (ActorFunc)EnMinifrog_Update,
                                         (ActorFunc)EnMinifrog_Draw };

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
CollisionCheckInfoInit D_808A4D6C = { 1, 12, 14, MASS_IMMOVABLE };

s32 D_808A4D74[] = {
    0x060059A0,
    0x06005BA0,
};
s32 D_808A4D7C[] = {
    0x00002040,
    0x20802101,
    0x21020000,
};

void* D_808A4D88[] = { NULL };

// static InitChainEntry sInitChain
InitChainEntry D_808A4D8C[] = {
    ICHAIN_F32_DIV1000(gravity, -800, ICHAIN_STOP),
};

// primColor
Color_RGBA8 D_808A4D90 = {
    255, 255, 255, 255,
};

// envColor
Color_RGBA8 D_808A4D94 = {
    80, 80, 80, 255,
};

// sEnFrColor
Color_RGBA8 D_808A4D98[] = {
    {200, 170, 0, 255},
    {0, 170, 200, 255},
    {210, 120, 100, 255},
    {120, 130, 230, 255},
    {190, 190, 190, 255},
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Init.asm")
// void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx) {
//     EnMinifrog* this = THIS;
//     s16 temp_v0;
//     s32 *temp_s0;
//     u16 temp_v1;
//     u16 temp_v1_2;
//     s32 *phi_s0;

//     Actor_ProcessInitChain(&this->actor, D_808A4D8C);
//     ActorShape_Init(&this->actor.shape, 0.0f, (void (*)(struct Actor *actor, struct Lights *mapper, struct GlobalContext *ctxt)) func_800B3FC0, 15.0f);
//     SkelAnime_InitSV(globalCtx, (SkelAnime *) this->unk_144, (void *)0x600B538, (void *)0x6001534, this + 0x188, this + 0x218, 0x18);
//     CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, (CollisionCheckInfoInit *) D_808A4D6C);
//     Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, (ColliderCylinderInit *) D_808A4D40);
//     if (*D_808A4D88 == 0) {
//         phi_s0 = D_808A4D74;

//         loop_2:
//         temp_s0 = phi_s0 + 4;
//         temp_s0->unk-4 = Lib_SegmentedToVirtual(*phi_s0);
//         phi_s0 = temp_s0;
//         if (temp_s0 != D_808A4D7C) {
//             goto loop_2;
//         }
//         *D_808A4D88 = 1;
//     }

//     this->frogIndex = this->actor.params & 0xF;
//     if (this->frogIndex >= 5) {
//         this->frogIndex = 0;
//     }

//     this->actor.speedXZ = 0.0f;
//     this->actionFunc = func_808A4040;
//     this->unk_2B2 = 2;
//     this->flags = 0;
//     this->timer = 0;

//     if (((this->actor.params & 0xF0) >> 4) == 0) {
//         temp_v0 = this->frogIndex;
//         if ((temp_v0 == 0) || (temp_v1 = *(D_808A4D7C + (temp_v0 * 2)), ((temp_v1 & 0xFF & gSaveContext.perm.weekEventReg[(s32) temp_v1 >> 8]) != 0))) {

//         } else {
//             this->timer = (u16)0x1E;
//             this->actionFunc = func_808A3F88;
//             this->actor.textId = 0xD81;
//             this->actor.colChkInfo.mass = 0x1E;
//             return;
//         }
//         Actor_MarkForDeath(&this->actor);
//         return;
//     }
//     if (this->frogIndex == 0) {
//         this->actor.textId = 0;
//         this->actionFunc = func_808A4914;
//         if ((*(&gSaveContext + 0xF1A) & 1) == 0) {
//             this->actor.flags |= 0x10000;
//         }
//         this->actor.home.rot.z = 0;
//         this->unk2AC = 0;
//         this->actor.home.rot.x = this->actor.home.rot.z;
//         return;
//     }
//     this->unk2AC = func_808A3930(globalCtx);
//     this->actor.flags &= ~1;
//     temp_v1_2 = *(D_808A4D7C + (this->frogIndex * 2));
//     if ((temp_v1_2 & 0xFF & gSaveContext.perm.weekEventReg[(s32) temp_v1_2 >> 8]) != 0) {
//         this->actionFunc = func_808A410C;
//         return;
//     }
//     this->actor.draw = NULL;
//     this->actor.update = func_808A4AC8;
// }


void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (this->flags & 0x100) {
        func_801A1F88();
    }
}


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3930.asm")
// EnMinifrog *func_808A3930(GlobalContext *globalCtx) {
//     Actor* frogFirst;
//     EnMinifrog* frogNext;

//     frogFirst = globalCtx->actorCtx.actorList[4].first;
//     frogNext = (EnMinifrog *) frogFirst;
//     if (frogFirst != NULL) {
//         do {
//             if ((frogNext->actor.id == 0x22) && ((frogNext->actor.params & 0xF) == 0)) {
//                 return frogNext;
//             }
//             frogNext = (EnMinifrog *) frogNext->actor.next;
//         } while (frogNext != NULL);
//     return NULL;
// }


void func_808A3980(EnMinifrog *this) {
    if (this->unk_2B2 == 2) {
        this->unk_2B2 = 0;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060007BC, 1.0f, 0.0f, 7.0f, 2, -5.0f);
    }
}

void func_808A39EC(EnMinifrog *this) {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->timer = 60 + (s32) Rand_ZeroFloat(40.0f);
        func_808A3980(this);
    }
}


// void func_808A3A44(EnMinifrog* this);
#ifdef NON_MATCHING
void func_808A3A44(EnMinifrog *this) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_2B2 == 0) {
        if (func_801378B8(&this->skelAnime, 4.0f)) {
            this->actor.bgCheckFlags &= ~1;
            this->actor.velocity.y = 6.0f;
            Audio_PlayActorSound2(this, 0x28B1);
            this->unk_2B2 = 1;
        }
    } else if (this->unk_2B2 == 1) {
        if (this->actor.bgCheckFlags & 1) {
            this->unk_2B2 = 2;
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001534, -2.5f);
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3A44.asm")
#endif

void func_808A3B04(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_808A3B3C(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B74.asm")
// void func_808A3B74(EnMinifrog* this, GlobalContext* globalCtx);
// void func_808A3B74(EnMinifrog *this, GlobalContext *globalCtx) {
//     f32 spC4;
//     f32 spC0;
//     f32 spBC;
//     f32 spAC;
//     f32 spA8;
//     f32 spA4;
//     f32 spA0;
//     f32 sp9C;
//     f32 sp98;
//     ? sp88;
//     Camera *temp_t9;
//     PosRot *temp_s0;
//     f32 *temp_s1_2;
//     f32 *temp_s2;
//     f32 *temp_s3;
//     f32 temp_f0;
//     f32 temp_f16;
//     f32 temp_f20;
//     f32 temp_f20_2;
//     f32 temp_f24;
//     f32 temp_f26;
//     f32 temp_f28;
//     f32 temp_f4;
//     s16 temp_s0_2;
//     s16 temp_s1;
//     s32 temp_s0_3;
//     s32 phi_s0;

//     temp_s0 = &this->actor.world;
//     temp_t9 = globalCtx->cameraPtrs[globalCtx->activeCamera];
//     sp88.unk0 = (bitwise s32) temp_t9->eye.x;
//     sp88.unk4 = (bitwise s32) temp_t9->eye.y;
//     sp88.unk8 = (bitwise s32) temp_t9->eye.z;
//     temp_s1 = Math_Vec3f_Yaw((Vec3f *) &sp88, (Vec3f *) temp_s0);
//     temp_s0_2 = (s16) -Math_Vec3f_Pitch((Vec3f *) &sp88, (Vec3f *) temp_s0);
//     temp_f20 = Math_SinS(temp_s1);
//     temp_f24 = this->actor.world.pos.x - (Math_CosS(temp_s0_2) * (5.0f * temp_f20));
//     temp_f26 = this->actor.world.pos.y - (Math_SinS(temp_s0_2) * 5.0f);
//     temp_f20_2 = Math_CosS(temp_s1);
//     temp_s2 = &spA4;
//     temp_s3 = &sp98;
//     temp_s1_2 = &spBC;
//     temp_f28 = this->actor.world.pos.z - (Math_CosS(temp_s0_2) * (5.0f * temp_f20_2));
//     phi_s0 = 0;

//     loop_1:
//         spA4 = randPlusMinusPoint5Scaled(4.0f);
//         spA8 = randPlusMinusPoint5Scaled(4.0f);
//         temp_f0 = randPlusMinusPoint5Scaled(4.0f);
//         temp_f16 = temp_f28 + temp_f0;
//         temp_f4 = -temp_f0 * 0.1f;
//         sp98 = -spA4 * 0.1f;
//         spAC = temp_f0;
//         sp9C = -spA8 * 0.1f;
//         spBC = temp_f24 + spA4;
//         spA0 = temp_f4;
//         spC0 = temp_f26 + spA8;
//         spC4 = temp_f16;
//         func_800B0F80(globalCtx, temp_s1_2, temp_s2, temp_s3, D_808A4D90, D_808A4D94, 0x12C, 0x1E, 0xA);
//         temp_s0_3 = phi_s0 + 1;
//         phi_s0 = temp_s0_3;
//         if (temp_s0_3 != 5) {
//             goto loop_1;
//         }
// }




void func_808A3DA8(EnMinifrog* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3DA8.asm")
// void func_808A3DA8(EnMinifrog *this, GlobalContext *globalCtx) {
//     s32 temp_t1;
//     u16 temp_t3;
//     u16 temp_v0;
//     u32 temp_t6;

//     func_808A3B04(this);
//     func_808A3A44(this);

//     if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
//         func_808A3980(this);
//         temp_v0 = globalCtx->msgCtx.unk11F04;
//         temp_t6 = temp_v0 - 0xD81;
//         if (temp_t6 >= 7U) {
//         case 4:
//             func_801477B4(globalCtx);
//             func_808A3B74(this, globalCtx);
//             func_800F0568(globalCtx, &this->actor.world.pos, 0x1E, 0x3A87); // (u16)0x3A87
//             if (this->actor.cutscene != -1) {
//                 if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
//                     ActorCutscene_Stop(this->actor.cutscene);
//                 }
//             }
//             Actor_MarkForDeath(&this->actor);
//             return;
//         }
//         goto **(&jtbl_D_808A4DB4 + (temp_t6 * 4));
//     default:
//     case 0:
//         func_80151938(globalCtx, (temp_v0 + 1) & 0xFFFF);
//         goto block_13;
//     case 1:
//         if ((*(&gSaveContext + 0xF19) & 0x80) != 0) {
//             func_80151938(globalCtx, 0xD83U);
//         } else {
//             func_80151938(globalCtx, 0xD86U);
//         }
//         temp_t3 = *(D_808A4D7C + ((s16) this->frogIndex * 2));
//         temp_t1 = (s32) temp_t3 >> 8;
//         gSaveContext.perm.weekEventReg[temp_t1] |= temp_t3;
//     }


//     block_13:
//     if (this->flags & 1) {
//         if (ActorCutscene_GetCurrentIndex() == 0x7C) {
//             ActorCutscene_Stop(0x7C);
//             ActorCutscene_SetIntentToPlay(this->actor.cutscene);
//         } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
//             ActorCutscene_Start(this->actor.cutscene, &this->actor);
//             this->flags &= ~1;
//         } else {
//             ActorCutscene_SetIntentToPlay(this->actor.cutscene);
//         }
//     }
// }




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
    } else if ((this->actor.xzDistToPlayer < 100.0f) && (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) != 0) && (func_8012403C(globalCtx) == 0xD)) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void func_808A410C(EnMinifrog *this, GlobalContext *globalCtx) {
    struct EnMinifrog* frog1;
    struct EnMinifrog* frog2;

    func_808A3A44(this);
    frog1 = this->frog;
    if (frog1 != NULL) {
        frog2 = frog1->frog;
        if (frog2 != NULL) {
            this->actor.home.rot.y = Actor_YawBetweenActors(&this->actor, &frog2->actor);
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

void func_808A4328(EnMinifrog *this, GlobalContext *globalCtx) {
    func_808A3A44(this);
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = func_808A4214;
        this->flags &= -0x3F;
        globalCtx->unk18798(globalCtx, &D_0400DEA8, 0);
    }
}

void func_808A43A4(EnMinifrog *this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A43A4.asm")

// void func_808A43A4(EnMinifrog *this, GlobalContext *globalCtx) {
//     u8 sp27;
//     s16 temp_v0;
//     s32 temp_v1;
//     struct EnMinifrog* frog;
//     u16 temp_t5;

//     func_808A3A44(this);
//     temp_v0 = func_801A39F8();
//     if (temp_v0 != 0xFF) {
//         if (temp_v0 == 0) {
//             sp27 = temp_v0 & 0xFF;
//             func_808A3980(this);
//         } else {
//             this->actor.home.rot.z = temp_v0;
//         }
//         temp_v1 = 2 << (temp_v0 & 0xFF);
//         if ((this->flags & temp_v1) == 0) {
//             this->flags |= temp_v1;
//             this->timer--;
//         }
//     }

//     frog = this->frog;
//     if (frog != NULL) {
//         this->actor.home.rot.z = 0;
//         this->actionFunc = func_808A42D8;
//         this->timer = 60;
//         this->actor.home.rot.y = Actor_YawBetweenActors(&this->actor, &frog->actor);
//         func_801A1F88();
//         temp_t5 = this->flags & 0xFEFF;
//         this->flags = temp_t5;
//         this->flags = temp_t5 & 0xFFC1;
//         globalCtx->unk18798(globalCtx, &D_0400DEA8, 0);
//         return;
//     }
//     if (this->timer <= 0) {
//         this->actionFunc = func_808A4328;
//         this->timer = 30;
//     }
// }


void func_808A44BC(EnMinifrog* this, GlobalContext* globalCtx) {
    func_808A3A44(this);
    if (this->actor.cutscene == -1) {
        this->actionFunc = func_808A43A4;
    }
    else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
    else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
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

void func_808A45A8(EnMinifrog* this, GlobalContext* globalCtx);
#ifdef NON_MATCHING
void func_808A45A8(EnMinifrog* this, GlobalContext* globalCtx) {
    f32 float1 = 1000.0f;

    func_808A3B04(this);
    func_808A3A44(this);
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0xD7EU, &this->actor);
        this->actionFunc = func_808A46E8;
    } else {
        func_800B8500(this, globalCtx, float1, float1, -1);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A45A8.asm")
#endif

void func_808A4634(EnMinifrog* this, GlobalContext* globalCtx);
#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4634.asm")
#endif

// switch-case
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A46E8.asm")


void func_808A4914(EnMinifrog *this, GlobalContext *globalCtx) {
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
    } else if ((this->actor.xzDistToPlayer < 150.0f) && (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) || ((this->actor.flags & 0x10000) == 0x10000)) && func_8012403C(globalCtx) == 0xD) {
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

s32 EnMinifrog_OverrideLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx) {
    if (limbIndex == 1) {
        pos->z -= 500.0f;
    }
    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }
    return 0;
}

void EnMinifrog_PostLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor* thisx) {
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

#ifdef NON_EQUIVALENT
void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_808A4D74[0]);
    gSPSegment(POLY_OPA_DISP++, 0x09, D_808A4D74[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, D_808A4D98[this->frogIndex].r, D_808A4D98[this->frogIndex].g, D_808A4D98[this->frogIndex].b, D_808A4D98[this->frogIndex].a);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, EnMinifrog_OverrideLimbDraw, EnMinifrog_PostLimbDraw, &this->actor);
}
#else 
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Draw.asm")
#endif