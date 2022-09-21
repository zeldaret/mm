/*
 * File: z_en_zod.c
 * Overlay: ovl_En_Zod
 * Description: Zora Drummer Tijo
 */

#include "z_en_zod.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, PlayState* play);
void EnZod_Destroy(Actor* thisx, PlayState* play);
void EnZod_Update(Actor* thisx, PlayState* play);
void EnZod_Draw(Actor* thisx, PlayState* play);

void func_80BAF338(EnZod* this, s16 arg1, u8 mode);
void func_80BAF99C(EnZod* this, PlayState* play);
void func_80BAFB84(EnZod* this, PlayState* play);
void func_80BAFDB4(EnZod* this, PlayState* play);
void func_80BAFF14(EnZod* this, PlayState* play);
s32 func_80BAF2B4(EnZod* this, PlayState* play);
void func_80BAF3E0(EnZod* this);
void func_80BAF7CC(EnZod* this, PlayState* play);
void func_80BAFA44(EnZod* this, PlayState* play);
void func_80BAFADC(EnZod* this, PlayState* play);
void func_80BAFC00(EnZod* this, PlayState* play);
void func_80BAFC10(EnZod* this, PlayState* play);
void func_80BAFD00(EnZod* this, PlayState* play);
void func_80BAFE34(EnZod* this, PlayState* play);
void func_80BAF4D8(EnZod* this);
s32 func_80BB0128(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80BB0170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80BB01B0(EnZod* this, PlayState* play);

#if 0
const ActorInit En_Zod_InitVars = {
    ACTOR_EN_ZOD,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOD,
    sizeof(EnZod),
    (ActorFunc)EnZod_Init,
    (ActorFunc)EnZod_Destroy,
    (ActorFunc)EnZod_Update,
    (ActorFunc)EnZod_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB0540 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 60, 40, 0, { 0, 0, 0 } },
};

static AnimationHeader *D_80BB056C[5] = {
    (AnimationHeader *)0x060002E8,
    (AnimationHeader *)0x06000894,
    (AnimationHeader *)0x06000A9C,
    (AnimationHeader *)0x06000D94,
    (AnimationHeader *)0x0600D9B0,
};

static void *D_80BB062C[5] = { (void *)0x06005E50, (void *)0x06006650, (void *)0x06006E50, NULL, NULL };

static Vec3f D_80BB0580 = { 1300.0f, 1100.0f, 0.0f };

static f32 D_80BB058C[0xA] = {
    0.0f,
    -2690.0f,
    2310.0f,
    3888.0f,
    -4160.0f,
    -2200.0f,
    -463.0f,
    1397.0f,
    3413.0f,
    389.0f,
};
static f32 D_80BB05B4[0xA] = {
    0.0f,
    6335.0f,
    6703.0f,
    5735.0f,
    3098.0f,
    3349.0f,
    3748.0f,
    3718.0f,
    2980.0f,
    1530.0f,
};
static f32 D_80BB05DC[0xA] = {
    0.0f,
    4350.0f,
    3200.0f,
    1555.0f,
    2874.0f,
    3901.0f,
    4722.0f,
    4344.0f,
    3200.0f,
    3373.0f,
};
static u32 D_80BB0604[0xA] = {
    0x0600A460,
    0x0600A550,
    0x0600A5E0,
    0x0600A670,
    0x0600A700,
    0x0600A8F8,
    0x0600AAF0,
    0x0600ACE8,
    0x0600AEE0,
    0x0600B0D8,
};

#endif

extern ColliderCylinderInit D_80BB0540;
extern FlexSkeletonHeader D_0600D658;
extern AnimationHeader* D_80BB056C[5];
extern TexturePtr D_80BB062C[5];
extern UNK_TYPE D_06000D94;
extern TexturePtr D_06007650;
extern Vec3f D_80BB0580;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Init.s")
void EnZod_Init(Actor* thisx, PlayState* play) {
    s32 i;
    EnZod* this = (EnZod*)thisx;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 60.0f);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600D658, (AnimationHeader*)(&D_06000D94), &this->morphTable,
                       &this->JointTable, 0xA);
    Animation_PlayLoop(&this->skelAnime, (AnimationHeader*)(&D_06000D94));
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &D_80BB0540);
    this->unk25C = this->unk25E = this->unk260 = 0;
    this->actor.gravity = this->actor.terminalVelocity = -4.0f;
    this->unk262 = this->unk264 = this->unk266 = 0x12C;
    this->unk256 = 0;
    this->unk25A = -1;
    this->unk258 = -1;
    this->actor.textId = 0;
    this->unk298 = 0;

    for(i = 0; i < 6; i++) {
        this->unk268[i] = 0.0f;
        this->unk280[i] = 0.01;
    }

    func_80BAF338(this, 3, 2U);
    this->actionFunc = func_80BAF99C;
    switch (this->actor.params & 0xF) {
        case 1:
            if ((gSaveContext.save.weekEventReg[0x4E] & 1)) {
                this->actionFunc = func_80BAFDB4;
                func_80BAF338(this, 0, 2);
                this->actor.flags |= 0x10;
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);
                return;
            }
            this->actionFunc = func_80BAFB84;
            if (!(gSaveContext.save.weekEventReg[0x37] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            return;

        case 2:
            this->actionFunc = func_80BAFF14;
            this->unk29A = -1;
            this->unk256 |= 2;
            return;

        default:
            if ((gSaveContext.save.weekEventReg[0x37] & 0x80) != 0) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= 0x10;
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Destroy.s")

void EnZod_Destroy(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF1EC.s")

void func_80BAF1EC(EnZod* this, PlayState* play) {
    u16 phi_a3;
    if (gSaveContext.save.playerForm != 2) {
        phi_a3 = 0x1227;
        if ((gSaveContext.save.weekEventReg[0x20] & 8) != 0) {
            phi_a3 = 0x1229;
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 8;
        }
    } else if ((this->unk256 & 1) != 0) {
        phi_a3 = 0x1225;
    } else {
        phi_a3 = 0x1219;
        if ((gSaveContext.save.weekEventReg[0x20] & 0x10) != 0) {
            phi_a3 = 0x1226;
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 0x10;
        }
        this->unk256 |= 1;
    }
    func_80BAF338(this, 0, 2);
    Message_StartTextbox(play, phi_a3, &this->actor);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF2B4.s")

s32 func_80BAF2B4(EnZod* this, PlayState* play) {
    if ((this->actor.playerHeightRel < 30.0f) && (this->actor.xzDistToPlayer < 200.0f) &&
        Player_IsFacingActor(&this->actor, 0x3000, play) && Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        return true;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF338.s")

void func_80BAF338(EnZod* this, s16 arg1, u8 mode) {
    if ((arg1 < 0) || (arg1 >= 5)) {
        arg1 = 3;
    }
    Animation_Change(&this->skelAnime, D_80BB056C[arg1], 1.0f, 0.0f, Animation_GetLastFrame(D_80BB056C[arg1]), mode,
                     -5.0f);
    this->unk258 = arg1;
    this->unk25A = arg1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF3E0.s")

void func_80BAF3E0(EnZod* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk25A == this->unk258) {
            func_80BAF338(this, this->unk258, 2);
            switch (this->unk258) {
                case 3:
                    if (Rand_ZeroFloat(1.0f) < 0.2f) {
                        this->unk25A = 4;
                    }
                    break;

                case 4:
                    if (Rand_ZeroFloat(1.0f) < 0.8f) {
                        this->unk25A = 3;
                    }
                    break;
            }

        } else {
            func_80BAF338(this, this->unk25A, 2);
        }
        SkelAnime_Update(&this->skelAnime);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF4D8.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF7CC.s")

void func_80BAF7CC(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if ((Message_ShouldAdvance(play) != 0) && (play->msgCtx.currentTextId == 0x121F)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x1220U);
                        return;
                    case 1:
                        func_8019F230();
                        func_80151938(play, 0x1223U);
                        return;
                }
            } else {
                return;
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.currentTextId) {
                    case 0x121A:
                    case 0x121B:
                    case 0x121C:
                    case 0x1220:
                    case 0x1221:
                    case 0x1227:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                    case 0x1219:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->unk25A = 2;
                        return;
                    case 0x121D:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->unk25A = 1;
                        return;
                    case 0x1223:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->unk25A = 0;
                        return;
                    case 0x121E:
                    case 0x1226:
                        func_80151938(play, 0x121FU);
                        this->unk25A = 1;
                        return;
                    default:
                        func_801477B4(play);
                        this->actionFunc = func_80BAF99C;
                        func_80BAF338(this, 3, 2U);
                        break;
                }
            }
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF99C.s")

void func_80BAF99C(EnZod* this, PlayState* play) {
    s32 pad;
    Vec3f sp20;

    func_80BAF3E0(this);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BAF1EC(this, play);
        this->actionFunc = func_80BAF7CC;
    } else if (func_80BAF2B4(this, play)) {
        func_800B8614(&this->actor, play, 210.0f);
    }

    sp20.x = this->actor.projectedPos.x;
    sp20.y = this->actor.projectedPos.y;
    sp20.z = this->actor.projectedPos.z;

    func_801A1FB4(3, &sp20, 0x6D, 700.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFA44.s")

void func_80BAFA44(EnZod* this, PlayState* play) {
    u16 phi_a3;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[0x4F] & 1) {
            phi_a3 = 0x1253;
        } else {
            phi_a3 = 0x1251;
            if (gSaveContext.save.weekEventReg[0x4E] & 0x20) {
                phi_a3 = 0x1252;
            } else {
                gSaveContext.save.weekEventReg[0x4E] |= 0x20;
            }
        }
    } else {
        phi_a3 = 0x1250;
    }
    func_80BAF338(this, 0, 2);
    Message_StartTextbox(play, phi_a3, &this->actor);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFADC.s")

void func_80BAFADC(EnZod* this, PlayState* play) {
    u8 msgState;

    func_80BAF3E0(this);
    msgState = Message_GetState(&play->msgCtx);
    if (msgState != 2) {
        if ((msgState == 5) && Message_ShouldAdvance(play)) {
            func_801477B4(play);
            this->actionFunc = func_80BAFB84;
            func_80BAF338(this, 3, 2);
        }
    } else {
        this->actionFunc = func_80BAFB84;
        func_80BAF338(this, 3, 2);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFB84.s")

void func_80BAFB84(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BAFA44(this, play);
        this->actionFunc = func_80BAFADC;
    } else if (func_80BAF2B4(this, play)) {
        func_800B8614(&this->actor, play, 210.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC00.s")

void func_80BAFC00(EnZod *this, PlayState *play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC10.s")

void func_80BAFC10(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        if (this->actor.cutscene == -1) {
            this->actionFunc = func_80BAFC00;
            play->nextEntrance = play->setupExitList[ENZOD_GET_ENTRANCE_INDEX(&this->actor)];
            play->transitionType = 5;
            play->transitionTrigger = 0x14;
            gSaveContext.save.weekEventReg[0x4E] &= 0xFE;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFD00.s")

void func_80BAFD00(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        func_80BAF338(this, 3, 2);
        this->actionFunc = func_80BAFC10;
        ActorCutscene_Stop(this->actor.cutscene);
        this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        gSaveContext.save.weekEventReg[0x4F] |= 1;
        Audio_QueueSeqCmd(NA_BGM_INDIGO_GO_SESSION | 0x8000);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFDB4.s")

void func_80BAFDB4(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_800B7298(play, NULL, 0x44);
        Message_StartTextbox(play, 0x103A, &this->actor);
        this->actionFunc = func_80BAFD00;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFE34.s")

void func_80BAFE34(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (this->unk29A < 0x31F) {
        this->unk29A += 0xC8;
    } else {
        this->unk29A += 0x1E;
    }
    if (this->unk29A >= 0x3E8) {
        this->unk29A = 0x3E7;
    }
    if (Cutscene_CheckActorAction(play, 0x203U) != 0) {
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x203U)]->action == 1) {
            this->actionFunc = func_80BAFF14;
            this->unk29A = -1;
        }
    } else {
        this->actionFunc = func_80BAFF14;
        this->unk29A = -1;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFF14.s")

void func_80BAFF14(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (Cutscene_CheckActorAction(play, 0x203) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x203)]->action == 4)) {
        this->actionFunc = func_80BAFE34;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Update.s")

void EnZod_Update(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;
    u32 phi_v0;
    Vec3s torsoRot;
    s32 pad;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, 4);
    this->actionFunc(this, play);
    func_80BAF4D8(this);

    if (this->unk24E == 0) {
        phi_v0 = 0;
    } else {
        this->unk24E--;
        phi_v0 = this->unk24E;
    }

    if (phi_v0 == 0) {
        this->unk24E = Rand_S16Offset(0x3C, 0x3C);
    }

    this->unk24C = this->unk24E;

    if (this->unk24C >= 3) {
        this->unk24C = 0;
    }

    torsoRot.z = 0;
    torsoRot.y = 0;
    torsoRot.x = 0;

    if (func_80BAF2B4(this, play)) {
        Actor_TrackPlayer(play, &this->actor, &this->headRot, &torsoRot, this->actor.focus.pos);
        if (this->headRot.x > 0xBB8) {
            this->headRot.x = 0xBB8;
        } else if (this->headRot.x < -0xBB8) {
            this->headRot.x = -0xBB8;
        }
    } else {
        Math_SmoothStepToS(&this->headRot.x, 0, 6, 0x1838, 100);
        Math_SmoothStepToS(&this->headRot.y, 0, 6, 0x1838, 100);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0128.s")

s32 func_80BB0128(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZod* this = THIS;

    if (limbIndex == 3) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0170.s")

void func_80BB0170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 3) {
        Matrix_MultVec3f(&D_80BB0580, &thisx->focus.pos);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB01B0.s")

typedef struct unkStruct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
} unkStruct;
extern f32 D_80BB058C[];
extern f32 D_80BB05B4[];
extern f32 D_80BB05DC[];
extern u32 D_80BB0604[];
void func_80BB01B0(EnZod *this, PlayState *play) {
    f32 spC4;
    f32 sp9C;
    f32 sp74;
    Gfx *temp_v0;
    Gfx *temp_v0_2;
    GraphicsContext *temp_s2;
    unkStruct *temp_t0;
    unkStruct *temp_t1;
    unkStruct *temp_t2;
    unkStruct *temp_t6;
    unkStruct *temp_t7;
    unkStruct *temp_t7_2;
    f32 temp_fa0;
    s32 temp_s1;
    unkStruct *phi_t7;
    f32 *phi_t6;
    f32 *phi_t2;
    f32 *phi_t1;
    f32 *phi_t7_2;
    f32 *phi_t0;
    f32 *phi_s4;
    f32 *phi_s5;
    f32 *phi_s6;
    s32 phi_s1;
    s32 phi_s3;
    u32 *phi_s7;

    phi_t7 = D_80BB058C;
    phi_t6 = &spC4;
    do {
        temp_t7 = phi_t7 + 0xC;
        temp_t6 = phi_t6 + 0xC;
        temp_t6->unk_C =  *phi_t7;
        temp_t6->unk_8 = (s32) temp_t7->unk_8;
        temp_t6->unk_4 = (s32) temp_t7->unk_4;
        phi_t7 = temp_t7;
        phi_t6 = temp_t6;
    } while (temp_t7 != (D_80BB058C + 0x24));
    temp_t6->unk_0 = temp_t7->unk_0;
    phi_t2 = D_80BB05B4;
    phi_t1 = &sp9C;
    do {
        temp_t2 = phi_t2 + 0xC;
        temp_t1 = phi_t1 + 0xC;
        temp_t1->unk_C = (f32) *phi_t2;
        temp_t1->unk_8 = (s32) temp_t2->unk_8;
        temp_t1->unk_4 = (s32) temp_t2->unk_4;
        phi_t2 = temp_t2;
        phi_t1 = temp_t1;
    } while (temp_t2 != (D_80BB05B4 + 0x24));
    temp_t1->unk_0 = temp_t2->unk_0;
    phi_t7_2 = D_80BB05DC;
    phi_t0 = &sp74;
    do {
        temp_t7_2 = phi_t7_2 + 0xC;
        temp_t0 = phi_t0 + 0xC;
        temp_t0->unk_C = (f32) *phi_t7_2;
        temp_t0->unk_8 = (s32) temp_t7_2->unk_8;
        temp_t0->unk_4 = (s32) temp_t7_2->unk_4;
        phi_t7_2 = temp_t7_2;
        phi_t0 = temp_t0;
    } while (temp_t7_2 != (D_80BB05DC + 0x24));
    temp_t0->unk_0 = temp_t7_2->unk_0;
    temp_s2 = play->state.gfxCtx;
    phi_s4 = &spC4;
    phi_s5 = &sp9C;
    phi_s6 = &sp74;
    phi_s1 = 0;
    phi_s3 = 0;
    phi_s7 = D_80BB0604;
    do {
        Matrix_Push();
        Matrix_Translate(*phi_s4, *phi_s5, *phi_s6, MTXMODE_APPLY);
        switch (phi_s1) {
        case 1:
        case 2:
        case 3:
            Matrix_RotateXS((this + (phi_s1 * 2))->unk25A, MTXMODE_APPLY);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            temp_fa0 = (this + -phi_s3)->unk28C + 1.0f;
            Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);
            break;
        }
        temp_v0 = temp_s2->polyOpa.p;
        temp_s2->polyOpa.p = temp_v0 + 8;
        temp_v0->words.w0 = 0xDA380003;
        temp_v0->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
        temp_v0_2 = temp_s2->polyOpa.p;
        temp_s2->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w0 = 0xDE000000;
        temp_v0_2->words.w1 = *phi_s7;
        Matrix_Pop();
        temp_s1 = phi_s1 + 1;
        phi_s4 += 4;
        phi_s5 += 4;
        phi_s6 += 4;
        phi_s1 = temp_s1;
        phi_s3 += 4;
        phi_s7 += 4;
    } while (temp_s1 != 0xA);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Draw.s")

void EnZod_Draw(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;
    Gfx* gfxP;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->unk256 & 2) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 0, this->unk29A, 1000);
    }

    gfxP = POLY_OPA_DISP;

    gSPSegment(gfxP, 0x08, Lib_SegmentedToVirtual(D_80BB062C[this->unk24C]));
    gSPSegment(gfxP + 1, 0x09, Lib_SegmentedToVirtual(&D_06007650));

    POLY_OPA_DISP = gfxP + 2;

    func_80BB01B0(this, play);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80BB0128, func_80BB0170, &this->actor);
    if (this->unk256 & 2) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}