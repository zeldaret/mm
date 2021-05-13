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
void func_808A4914(EnMinifrog* this, GlobalContext* globalCtx);

void func_808A4AC8(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_060007BC;

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

s32 D_808A4D6C[] = {
    0x0100000C,
    0x000EFF00,
};
s32 D_808A4D74[] = {
    0x060059A0,
    0x06005BA0,
};
s32 D_808A4D7C[] = {
    0x00002040,
    0x20802101,
    0x21020000,
};
s32 D_808A4D88[] = {
    0x00000000,
};

// static InitChainEntry sInitChain
InitChainEntry D_808A4D8C[] = {
    ICHAIN_F32_DIV1000(gravity, -800, ICHAIN_STOP),
};

s32 D_808A4D90[] = {
    0xFFFFFFFF,
};
s32 D_808A4D94[] = {
    0x505050FF,
};
s32 D_808A4D98[] = {
    0xC8AA00FF, 0x00AAC8FF, 0xD27864FF, 0x7882E6FF, 0xBEBEBEFF, 0x00000000,
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

//     this->unk_2B0 = this->actor.params & 0xF;
//     if (this->unk_2B0 >= 5) {
//         this->unk_2B0 = 0;
//     }

//     this->actor.speedXZ = 0.0f;
//     this->actionFunc = func_808A4040;
//     this->unk_2B2 = 2;
//     this->flags = 0;
//     this->timer = 0;

//     if (((this->actor.params & 0xF0) >> 4) == 0) {
//         temp_v0 = this->unk_2B0;
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
//     if (this->unk_2B0 == 0) {
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
//     temp_v1_2 = *(D_808A4D7C + (this->unk_2B0 * 2));
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
        SkelAnime_ChangeAnim(&this->anime, &D_060007BC, 1.0f, 0.0f, 7.0f, 2, -5.0f);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A39EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3A44.asm")

void func_808A3B04(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_808A3B3C(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B74.asm")


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
//         temp_t3 = *(D_808A4D7C + ((s16) this->unk_2B0 * 2));
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
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A41A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A42D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A43A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A44BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A45A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A46E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Draw.asm")
