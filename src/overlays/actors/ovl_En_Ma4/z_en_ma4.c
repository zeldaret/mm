#include "z_en_ma4.h"

#define FLAGS 0x02000039

#define THIS ((EnMa4*)thisx)

void EnMa4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Draw(Actor* thisx, GlobalContext* globalCtx);



void func_80ABDD9C(EnMa4* this, GlobalContext* globalCtx); // TODO: remove


void func_80ABE4A4(EnMa4* this);
void func_80ABE560(EnMa4* this, GlobalContext* globalCtx);
void func_80ABE6C8(EnMa4* this, GlobalContext* globalCtx);
void func_80ABEB6C(EnMa4* this, GlobalContext* globalCtx);
void func_80ABEF34(EnMa4* this);
void func_80ABEF8C(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF070(EnMa4* this);
void func_80ABF084(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF0D8(EnMa4* this, GlobalContext* globalCtx); // TODO: remove
void func_80ABF160(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF198(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF218(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF254(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF2FC(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF354(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF494(EnMa4* this);
void func_80ABF4A8(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF51C(EnMa4* this);
void func_80ABF534(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF69C(EnMa4* this);
void func_80ABF6B0(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF760(EnMa4* this);
void func_80ABF774(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF7C8(EnMa4* this, GlobalContext* globalCtx);
void EnMa4_SetFaceExpression(EnMa4* this, s16, s16);
void func_80ABFCD4(EnMa4* this);


extern AnimationHeader D_06007328;


/*
const ActorInit En_Ma4_InitVars = {
    ACTOR_EN_MA4,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMa4),
    (ActorFunc)EnMa4_Init,
    (ActorFunc)EnMa4_Destroy,
    (ActorFunc)EnMa4_Update,
    (ActorFunc)EnMa4_Draw,
};
*/


// UpdateEyes
void func_80ABDCA0(EnMa4 *this) {
    if (this->unk_32C != 0) {
        this->unk_32E = this->unk_32C;
    } else if (DECR(this->unk_32A) == 0) {
        this->unk_32E++;
        if ((s32) this->unk_32E >= 3) {
            this->unk_32A = Rand_S16Offset(30, 30);
            this->unk_32E = 0;
        }
    }
}



struct struct_80AC010C {
    /* 0x00 */ AnimationHeader* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x0C */ f32 unk_0C;
};

extern struct struct_80AC010C D_80AC010C[];

void EnMa4_ChangeAnim(EnMa4 *this, s32 index) {
    SkelAnime_ChangeAnim(&this->skelAnime, D_80AC010C[index].unk_00, 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80AC010C[index].unk_00->common),
                         D_80AC010C[index].unk_08, D_80AC010C[index].unk_0C);
}


extern AnimationHeader D_06002A8C;
extern AnimationHeader D_06015B7C;


void func_80ABDD9C(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer* player = PLAYER;
    s16 phi_a3;

    if (this->unk_1D8 == 0 && ((this->skelAnime.animCurrentSeg == &D_06007328) || (this->skelAnime.animCurrentSeg == &D_06002A8C) || (this->skelAnime.animCurrentSeg == &D_06015B7C))) {
        phi_a3 = 1;
    } else {
        phi_a3 = (this->unk_332 == 2 && this->actionFunc != func_80ABEF8C) ? 1 : 0;
    }

    this->unk_1F0 = player->base.world.pos;
    this->unk_1F0.y -= -10.0f;
    func_800BD888(&this->actor, &this->unk_1D8, 0, phi_a3);
}


// InitPath?
void func_80ABDE60(EnMa4 *this, GlobalContext *globalCtx) {
    Path *temp_v1;
    Vec3f sp20;

    temp_v1 = &globalCtx->setupPathList[(s32) (this->actor.params & 0xFF00) >> 8];
    this->unk_200 = Lib_SegmentedToVirtual(temp_v1->points);
    this->unk_324 = 0;
    this->unk_326 = temp_v1->count;

    this->actor.home.pos.x = this->unk_200[0].x;
    this->actor.home.pos.y = this->unk_200[0].y;
    this->actor.home.pos.z = this->unk_200[0].z;
    sp20.x = this->unk_200[1].x;
    sp20.y = this->unk_200[1].y;
    sp20.z = this->unk_200[1].z;

    this->actor.world.pos = this->actor.home.pos;
    this->actor.shape.rot.y = this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &sp20);
}


extern FlexSkeletonHeader D_06013928;

extern ColliderCylinderInit D_80AC00B0;
extern CollisionCheckInfoInit2 D_80AC00DC;


void EnMa4_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnMa4* this = THIS;
    ColliderCylinder *temp_a1;

    ActorShape_Init(&this->actor.shape, 0.0f, (void (*)(struct Actor *actor, struct Lights *mapper, struct GlobalContext *globalCtx)) func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, NULL, this->limbDrawTable, this->transitionDrawTable, 0x17);
    temp_a1 = &this->collider;
    Collider_InitCylinder(globalCtx, temp_a1);
    Collider_SetCylinder(globalCtx, temp_a1, &this->actor, &D_80AC00B0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80AC00DC);
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 0;
    this->unk_1D8 = 0;
    this->unk_334 = 0;
    this->unk_33A = 1;
    this->unk_330 = 0;
    this->unk_33C = 0;
    if (CURRENT_DAY == (u16)1) {
        this->unk_332 = 0;
    } else if (gSaveContext.weekEventReg[0x16] & 1) {
        this->unk_332 = 1;
    } else {
        this->unk_332 = 2;
        this->unk_33A = 0;
    }
    if (func_800EE1D8(globalCtx) != 0) {
        EnMa4_ChangeAnim(this, 0);
        this->unk_336 = 1;
        func_80ABF198(this, globalCtx);
    } else {
        func_80ABDE60(this, globalCtx);

        if (gSaveContext.entranceIndex == 0x6410) {
            EnMa4_ChangeAnim(this, 0);
            this->unk_336 = 2;
        } else if (gSaveContext.entranceIndex == 0x64A0) {
            EnMa4_ChangeAnim(this, 0);
            this->unk_336 = 3;
        } else {
            if (this->unk_332 == 2) {
                EnMa4_ChangeAnim(this, 14);
                this->actor.shape.shadowScale = 0.0f;
            } else {
                EnMa4_ChangeAnim(this, 8);
            }
            this->unk_336 = 0;
        }
        func_80ABE4A4(this);
    }
}


void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    gSaveContext.weekEventReg[0x8] &= 0xFE;
}

extern s32 D_80AC024C;
extern s32 D_80AC0250;
extern s16 D_80AC0254;


/*
void func_80ABE1C4(EnMa4 *this, GlobalContext *globalCtx) {
    Vec3f sp34;
    s16 sp2E;
    //PosRot *sp28;
    //PosRot *temp_a0;
    //SkelAnime *temp_a0_2;
    //f32 *temp_a1;
    //s16 temp_v0_2;
    //s16 temp_v0_3;

    if ((D_80AC024C != 9) && (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0)) {
        if (D_80AC024C == 3) {
            if (D_80AC0250 < 3) {
                D_80AC0250++;
            } else {
                D_80AC0250 = 0;
                EnMa4_ChangeAnim(this, 13);
                D_80AC024C = 0xD;
            }
        } else {
            this->actor.speedXZ = 2.7f;
            EnMa4_ChangeAnim(this, 9);
            D_80AC024C = 9;
        }
    }

    if ((D_80AC024C == 0xD) && (func_801378B8(&this->skelAnime, 37.0f) != 0)) {
        Audio_PlayActorSound2(this, 0x29BF);
    }

    //temp_a0 = &this->actor.world;
    //temp_a1 = &sp34;
    sp34.x = (f32) this->unk_200[this->unk_324].x;
    sp34.y = (f32) this->unk_200[this->unk_324].y;
    //sp28 = temp_a0;
    sp34.z = (f32) this->unk_200[this->unk_324].z;

    sp2E = Math_Vec3f_Yaw(&this->actor.world, &sp34);

    if (Math_Vec3f_DistXZ(&this->actor.world, &sp34) > 50.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, sp2E, (u16)0xA, (u16)0x3000, 0x100);
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp2E, (u16)5, (u16)0x3000, 0x100);
    } else {
        if ((D_80AC0254 == 0) && ((Rand_Next() % 4) == 0)) {
            this->actor.speedXZ = 0.0f;
            D_80AC0254 = (u16)2;
            EnMa4_ChangeAnim(this, 3);
            D_80AC024C = 3;
        } else {
            //D_80AC0254 = D_80AC0254;
            if ((s32) D_80AC0254 > 0) {
                D_80AC0254 = (s16) (D_80AC0254 - 1);
            }
        }

        //temp_v0_3 = this->unk_324;
        if ((s32) this->unk_324 < (this->unk_326 - 1)) {
            this->unk_324++;
        } else {
            this->unk_324 = 0;
        }
    }

    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    //temp_a0_2 = &this->skelAnime;
    if (this->skelAnime.animCurrentSeg == &D_06007328) {
        //sp28 = (PosRot *) temp_a0_2;
        if ((func_801378B8(&this->skelAnime, 0.0f) != 0) || (func_801378B8(&this->skelAnime, 4.0f) != 0)) {
            Audio_PlayActorSound2(this, 0x3ABE);
        }
    }
}
*/
void func_80ABE1C4(EnMa4* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE1C4.asm")



void func_80ABE4A4(EnMa4 *this) {
    if ((this->unk_336 != 2) && (this->unk_336 != 3)) {
        if (this->unk_332 != 2) {
            EnMa4_ChangeAnim(this, 9);
            this->actor.speedXZ = 2.7f;
        } else {
            EnMa4_ChangeAnim(this, 15);
            this->actor.speedXZ = 0.0f;
        }
    } else {
        EnMa4_ChangeAnim(this, 1);
        this->actor.speedXZ = 0.0f;
    }

    this->actor.gravity = -0.2f;
    this->unk_33C = 0;
    func_80ABFCD4(this);
    this->actionFunc = func_80ABE560;
}



void func_80ABE560(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    s16 sp22 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if ((this->unk_336 == 2) || (this->unk_336 == 3)) {
        this->actor.flags = this->actor.flags | 0x10000;
    } else if (this->unk_332 != 2) {
        func_80ABE1C4(this, globalCtx);
    } else if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        this->unk_33C++;
        if (this->unk_33C == 5) {
            EnMa4_ChangeAnim(this, 17);
        } else if (this->unk_33C == 8) {
            this->unk_33C = 0;
            EnMa4_ChangeAnim(this, 15);
        }
    }

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        func_80ABF7C8(this, globalCtx);
        func_80ABEF34(this);
    } else if (!(this->unk_332 == 2) || ABS_ALT(sp22) < 0x4000) {
        if (!(player->stateFlags1 & 0x800000)) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}



void func_80ABE6C8(EnMa4 *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        switch (this->unk_33E) {
            case 0x3339:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    func_801518B0(globalCtx, 0x333A, &this->actor);
                    this->unk_33E = 0x333A;
                } else {
                    func_8019F208();
                    func_801518B0(globalCtx, 0x333B, &this->actor);
                    this->unk_33E = 0x333B;
                }
                break;

            case 0x3341:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    gSaveContext.weekEventReg[0x15] |= 0x20;
                    func_801518B0(globalCtx, 0x3343, &this->actor);
                    this->unk_33E = 0x3343;
                } else {
                    func_8019F230();
                    EnMa4_SetFaceExpression(this, 0, 1);
                    func_801518B0(globalCtx, 0x3342, &this->actor);
                    this->unk_33E = 0x3342;
                    this->unk_336 = 0;
                    func_80151BB4(globalCtx, 5);
                }
                break;

            case 0x3346:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    gSaveContext.weekEventReg[0x15] |= 0x20;
                    func_801518B0(globalCtx, 0x3343, &this->actor);
                    this->unk_33E = 0x3343;
                } else {
                    func_8019F230();
                    EnMa4_SetFaceExpression(this, 0, 1);
                    func_801518B0(globalCtx, 0x3342, &this->actor);
                    this->unk_33E = 0x3342;
                }
                break;

            case 0x3347:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    func_801518B0(globalCtx, 0x3349, &this->actor);
                    this->unk_33E = 0x3349;
                } else {
                    func_8019F230();
                    func_801518B0(globalCtx, 0x3348, &this->actor);
                    this->unk_33E = 0x3348;
                    func_80151BB4(globalCtx, 5);
                }
                break;

            case 0x334D: // Asks if you understood her explanation.
                if (globalCtx->msgCtx.choiceIndex == 0) { // Yes
                    s32 aux;

                    func_8019F208();
                    func_801518B0(globalCtx, 0x334E, &this->actor);
                    this->unk_33E = 0x334E;
                    if ((aux = gSaveContext.inventory.questItems) & gBitFlags[0xE]) {
                        func_80151BB4(globalCtx, 0x1C);
                    }
                    func_80151BB4(globalCtx, 5);
                } else { // No.
                    func_8019F230();
                    EnMa4_SetFaceExpression(this, 0, 0);
                    func_801518B0(globalCtx, 0x334C, &this->actor);
                    this->unk_33E = 0x334C;
                }
                break;

            case 0x3354:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    func_801518B0(globalCtx, 0x3349, &this->actor);
                    this->unk_33E = 0x3349;
                } else {
                    func_8019F230();
                    EnMa4_SetFaceExpression(this, 1, 0);
                    func_801518B0(globalCtx, 0x3355, &this->actor);
                    this->unk_33E = 0x3355;
                    func_80151BB4(globalCtx, 5);
                }
                break;

            case 0x3356:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    func_801477B4(globalCtx);
                    func_80ABF070(this);
                } else {
                    if (this->unk_332 == 1) {
                        func_8019F230();
                        EnMa4_SetFaceExpression(this, 3, 3);
                        func_801518B0(globalCtx, 0x3357, &this->actor);
                        this->unk_33E = 0x3357;
                        func_80151BB4(globalCtx, 5);
                    } else {
                        func_8019F230();
                        EnMa4_SetFaceExpression(this, 4, 2);
                        func_801518B0(globalCtx, 0x335B, &this->actor);
                        this->unk_33E = 0x335B;
                        func_80151BB4(globalCtx, 5);
                    }
                }
                break;

            case 0x3359:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_8019F208();
                    func_801518B0(globalCtx, 0x3349, &this->actor);
                    this->unk_33E = 0x3349;
                } else {
                    func_8019F230();
                    EnMa4_SetFaceExpression(this, 4, 2);
                    func_801518B0(globalCtx, 0x335A, &this->actor);
                    this->unk_33E = 0x335A;
                    func_80151BB4(globalCtx, 5);
                }
                break;
        }
    }
}


void func_80ABEB6C(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    s32 aux;

    if (func_80147624(globalCtx) != 0) {
        switch (this->unk_33E) {
            case 0x2390:
                func_801477B4(globalCtx);
                func_80ABF070(this);
                break;

            case 0x3335:
                EnMa4_SetFaceExpression(this, 0, 3);
                func_801518B0(globalCtx, 0x3336, &this->actor);
                this->unk_33E = 0x3336;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3338:
                func_801518B0(globalCtx, 0x3339, &this->actor);
                this->unk_33E = 0x3339;
                break;

            case 0x333A:
            case 0x333B:
                EnMa4_SetFaceExpression(this, 0, 3);
                func_801518B0(globalCtx, 0x333C, &this->actor);
                this->unk_33E = 0x333C;
                break;

            case 0x333C:
                EnMa4_SetFaceExpression(this, 0, 2);
                func_801518B0(globalCtx, 0x333D, &this->actor);
                this->unk_33E = 0x333D;
                break;

            case 0x333D:
                func_801518B0(globalCtx, 0x333E, &this->actor);
                this->unk_33E = 0x333E;
                break;

            case 0x333E:
                func_801477B4(globalCtx);
                func_80ABF760(this);
                break;

            case 0x333F:
                func_801518B0(globalCtx, 0x3340, &this->actor);
                this->unk_33E = 0x3340;
                break;

            case 0x3340:
                EnMa4_SetFaceExpression(this, 0, 3);
                func_801518B0(globalCtx, 0x3341, &this->actor);
                this->unk_33E = 0x3341;
                break;

            case 0x3343:
                EnMa4_SetFaceExpression(this, 0, 0);
                func_801518B0(globalCtx, 0x3344, &this->actor);
                this->unk_33E = 0x3344;
                break;

            case 0x3344:
                func_801518B0(globalCtx, 0x3345, &this->actor);
                this->unk_33E = 0x3345;
                break;

            case 0x3345:
                func_801518B0(globalCtx, 0x3349, &this->actor);
                this->unk_33E = 0x3349;
                break;

            case 0x3349:
                func_801518B0(globalCtx, 0x334A, &this->actor);
                this->unk_33E = 0x334A;
                break;

            case 0x334A:
                func_801477B4(globalCtx);
                func_80ABF070(this);
                break;

            case 0x334C:
                func_801518B0(globalCtx, 0x334D, &this->actor);
                this->unk_33E = 0x334D;
                break;

            case 0x3350:
            case 0x3351:
            case 0x335D:
            case 0x335E:
                if (this->unk_332 == 0) {
                    func_801518B0(globalCtx, 0x3352, &this->actor);
                    this->unk_33E = 0x3352;
                } else {
                    func_801518B0(globalCtx, 0x3356, &this->actor);
                    this->unk_33E = 0x3356;
                }
                break;

            case 0x3352: // Win minigame
            case 0x336d: // Lose minigame
                EnMa4_SetFaceExpression(this, 0, 0);
                if ((aux = gSaveContext.inventory.questItems) & gBitFlags[0xE]) {
                    func_801518B0(globalCtx, 0x334C, &this->actor);
                    this->unk_33E = 0x334C;
                } else {
                    func_801477B4(globalCtx);
                    player->stateFlags1 |= 0x20;
                    func_80ABF494(this);
                    func_80ABF4A8(this, globalCtx);
                }
                break;

            case 0x3358:
                if ((gSaveContext.playerForm != 4) || !((aux = gSaveContext.inventory.questItems) & gBitFlags[0xE])) {
                    func_801518B0(globalCtx, 0x335C, &this->actor);
                    this->unk_33E = 0x335C;
                    func_80151BB4(globalCtx, 5);
                } else {
                    func_801518B0(globalCtx, 0x3359, &this->actor);
                    this->unk_33E = 0x3359;
                }
                break;
        }
    }
}



void func_80ABEF34(EnMa4 *this) {
    if (this->unk_332 != 2) {
        EnMa4_ChangeAnim(this, 1);
    } else {
        EnMa4_ChangeAnim(this, 15);
    }
    this->actionFunc = func_80ABEF8C;
}



void func_80ABEF8C(EnMa4 *this, GlobalContext *globalCtx) {
    s32 temp_v0;

    switch (func_80152498(&globalCtx->msgCtx)) {
        default:
        break;

        case 4:
            func_80ABE6C8(this, globalCtx);
            break;

        case 5:
            func_80ABEB6C(this, globalCtx);
            break;

        case 6:
            if (func_80147624(globalCtx) != 0) {
                if ((globalCtx->msgCtx.unk_120B1 == 0) || (((temp_v0 = gSaveContext.inventory.questItems) & gBitFlags[0x12]) == 0)) {
                    func_80ABE4A4(this);
                }
            }

        case 0:
        case 1:
        case 2:
        case 3:
            break;
    }

    if (this->unk_332 != 2) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, (u16)5, (u16)0x7D0, 0x3E8);
    }
}


void func_80ABF070(EnMa4 *this) {
    this->actionFunc = func_80ABF084;
}

void func_80ABF084(EnMa4 *this, GlobalContext *globalCtx) {
    globalCtx->nextEntranceIndex = 0x6400;
    gSaveContext.unk_3F4A = 0xFFF0;
    globalCtx->unk18875 = 0x14;
    globalCtx->unk1887F = 0x50;
    gSaveContext.nextTransition = 3;
}


void func_80ABF0D8(EnMa4 *this, GlobalContext *globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        func_801518B0(globalCtx, 0x336EU, &this->actor);
        this->actionFunc = func_80ABF160;
    } else if ((gSaveContext.unk_3DE0[4] < 0x2CECU)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}


void func_80ABF160(EnMa4 *this, GlobalContext *globalCtx) {
    if (func_800B867C(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80ABF254;
    }
}


void func_80ABF198(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    globalCtx->interfaceCtx.unk_280 = 1;
    func_8010E9F0(4, 0);
    gSaveContext.weekEventReg[0x8] |= 0x01;
    func_80112AFC(globalCtx);
    player->stateFlags1 |= 0x20;
    this->actionFunc = func_80ABF218;
}


void func_80ABF218(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    if (globalCtx->interfaceCtx.unk_280 == 8) {
        this->actionFunc = func_80ABF254;
        player->stateFlags1 = (s32) (player->stateFlags1 & ~0x20);
    }
}

#ifdef NON_MATCHING
// Waiting to import data
void func_80ABF254(EnMa4 *this, GlobalContext *globalCtx) {
    static s16 D_80AC0258;
    ActorPlayer *player = PLAYER;

    player->unkA74 |= 0x400;
    func_80ABF0D8(this, globalCtx);
    if (this->unk_338 != D_80AC0258) {
        D_80AC0258 = this->unk_338;
        globalCtx->interfaceCtx.unk25C = 1;
    }
    if ((gSaveContext.unk_3DE0[4] >= 0x2EE0U) || (this->unk_338 == 0xA)) {
        gSaveContext.unk_3DD0[4] = 6;
        func_80ABF2FC(this, globalCtx);
        D_80AC0258 = 0;
    }
}
#else
extern s16 D_80AC0258;
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF254.asm")
#endif


void func_80ABF2FC(EnMa4 *this, GlobalContext *globalCtx) {
    gSaveContext.weekEventReg[0x8] &= 0xFE;
    this->actionFunc = func_80ABF354;
    func_801A89A8(0x100000FF);
    func_801A89A8(0x8041);
}

/*
void func_80ABF354(EnMa4 *this, GlobalContext *globalCtx) {
    EnMa4 *temp_a2;
    s32 temp_v1;
    s32 phi_v1;
    ActorPlayer* player = PLAYER;

    temp_a2 = this;
    if (player->stateFlags1 & 0x100000) {
        globalCtx->actorCtx.unk268 = 1;
        globalCtx->unk1F18 = (u16)0x8000;
    } else {
        globalCtx->actorCtx.unk268 = 1;
    }
    temp_v1 = D_80AC025C;
    if (temp_v1 == 0x19) {
        if (temp_a2->unk_338 == 0xA) {
            this = temp_a2;
            func_801518B0(globalCtx, 0x334FU, (Actor *) temp_a2);
            this->unk33E = 0x334F;
        } else {
            this = temp_a2;
            func_801518B0(globalCtx, 0x334BU, (Actor *) temp_a2);
            this->unk33E = 0x334B;
        }
        phi_v1 = D_80AC025C;
    } else {
        phi_v1 = temp_v1;
        if (temp_v1 == 0x32) {
            globalCtx->actorCtx.unk268 = 0;
            globalCtx->nextEntranceIndex = 0x6410;
            gSaveContext.unk3F4A = (u16)0;
            globalCtx->unk18875 = 0x14;
            if (temp_a2->unk_338 == 0xA) {
                globalCtx->unk1887F = 0x50;
                gSaveContext.unk3F55 = (u8)3;
            } else {
                globalCtx->unk1887F = 0x40;
                gSaveContext.unk3F55 = (u8)2;
            }
            temp_a2->unk_338 = 0;
            phi_v1 = 0;
        }
    }
    D_80AC025C = (s32) (phi_v1 + 1);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF354.asm")


void func_80ABF494(EnMa4 *this) {
    this->actionFunc = func_80ABF4A8;
}

void func_80ABF4A8(EnMa4 *this, GlobalContext *globalCtx) {
    s16 cutsceneIndex = this->actor.cutscene;

    if (ActorCutscene_GetCanPlayNext(cutsceneIndex) != 0) {
        ActorCutscene_Start(cutsceneIndex, &this->actor);
        func_80ABF51C(this);
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(cutsceneIndex);
    }
}


void func_80ABF51C(EnMa4 *this) {
    this->unk_33C = 0;
    this->actionFunc = func_80ABF534;
}

/*
void func_80ABF534(EnMa4 *this, GlobalContext *globalCtx) {
    u32 sp24;
    Actor *temp_v0_2;
    s32 temp_t6;
    u16 temp_a0_2;
    u16 temp_a1;
    u32 temp_v0;
    void *temp_a0;
    void *temp_v1;

    if (func_800EE29C(globalCtx, 0x78U) != 0) {
        temp_v0 = func_800EE200(globalCtx, 0x78U);
        temp_t6 = temp_v0 * 4;
        sp24 = temp_v0;
        temp_v1 = globalCtx + temp_t6;
        temp_a0 = temp_v1->unk1F4C;
        if (globalCtx->csCtx.frames == temp_a0->unk2) {
            temp_a1 = temp_a0->unk0;
            if (D_80AC0260 != temp_a1) {
                D_80AC0260 = temp_a1;
                this->unk_33C = 0;
                temp_a0_2 = temp_v1->unk1F4C->unk0;
                if (temp_a0_2 != (u16)1) {
                    if (temp_a0_2 != 2) {

                    } else {
                        this->unk_33A = 0;
                        EnMa4_ChangeAnim(this, 4);
                    }
                } else {
                    this->unk_33A = 1;
                    EnMa4_ChangeAnim(this, (s32) (u16)1);
                }
            }
        }
        func_800EDF24(this, globalCtx, sp24);
        if ((D_80AC0260 == 2) && (this->unk_33C == 0) && (func_801378B8(&this->skelAnime, (bitwise f32) (bitwise s32) this->skelAnime.animFrameCount) != 0)) {
            EnMa4_ChangeAnim(this, 7);
            return;
        }
    } else {
        temp_v0_2 = globalCtx->actorCtx.actorList[2].first;
        temp_v0_2->unkA6C = (s32) (temp_v0_2->unkA6C | 0x20);
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
        D_80AC0260 = (u16)0x63;
        this->unk_33A = 1;
        func_80ABF69C(this);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF534.asm")

void func_80ABF69C(EnMa4 *this) {
    this->actionFunc = func_80ABF6B0;
}

void func_80ABF6B0(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    this->actor.flags |= 0x10000;
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        player->stateFlags1 &= ~0x20;
        func_801518B0(globalCtx, 0x334C, &this->actor);
        this->unk_33E = 0x334C;
        this->actor.flags &= ~0x10000;
        func_80ABEF34(this);
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}


void func_80ABF760(EnMa4 *this) {
    this->actionFunc = func_80ABF774;
}

void func_80ABF774(EnMa4 *this, GlobalContext *globalCtx) {
    globalCtx->nextEntranceIndex = 0x6400;
    gSaveContext.unk_3F4A = (u16)0xFFF5;
    globalCtx->unk18875 = 0x14;
    globalCtx->unk1887F = 0x40;
    gSaveContext.nextTransition = (u8)2;
}


/*
void func_80ABF7C8(EnMa4 *this, GlobalContext *globalCtx) {
    u32 sp34;
    s32 sp30;
    u32 sp24;
    s32 sp20;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t6;
    u32 temp_t1;
    u32 temp_t3;
    u32 temp_t7;
    u8 temp_v0_5;
    s16 phi_t4;

    temp_v0 = this->unk_332;
    if (temp_v0 != 0) {
        if (temp_v0 != 1) {
            if (temp_v0 != 2) {
                func_801518B0(globalCtx, 0x3335U, &this->actor);
                phi_t4 = (u16)0x3335;
block_49:
                this->unk33E = phi_t4;
            } else {
                temp_v0_2 = this->unk_336;
                if (temp_v0_2 == 0) {
                    func_801518B0(globalCtx, 0x3358U, &this->actor);
                    this->unk33E = 0x3358;
                    return;
                }
                if (temp_v0_2 == 2) {
                    temp_t0 = gSaveContext.extra.unk_160;
                    temp_t1 = gSaveContext.extra.unk_164;
                    sp20 = temp_t0;
                    sp24 = temp_t1;
                    if ((temp_t0 != 0) || (temp_t1 >= 0x2EE0U)) {
                        func_801518B0(globalCtx, 0x3356U, &this->actor);
                        this->unk33E = 0x3356;
                    } else {
                        sp34 = sp24;
                        sp30 = sp20;
                        if ((s32) sp24 < gSaveContext.unkEEC) {
                            gSaveContext.unkEEC = (s32) sp24;
                            func_801518B0(globalCtx, 0x335DU, &this->actor);
                            this->unk33E = 0x335D;
                        } else {
                            func_801518B0(globalCtx, 0x335EU, &this->actor);
                            this->unk33E = 0x335E;
                        }
                    }
                    this->unk_336 = 0;
                    this->actor.flags = this->actor.flags & 0xFFFEFFFF;
                    return;
                }
            }
        } else {
            if (gSaveContext.unk20 != 4) {
                if ((gSaveContext.unkF0D & 0x80) == 0) {
                    func_801518B0(globalCtx, 0x3335U, &this->actor);
                    this->unk33E = 0x3335;
                    gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x80);
                    return;
                }
                globalCtx = globalCtx;
                EnMa4_SetFaceExpression(this, (u16)3, (u16)3);
                func_801518B0(globalCtx, 0x3337U, &this->actor);
                this->unk33E = 0x3337;
                func_80151BB4((s32) globalCtx, 5U);
                return;
            }
            temp_v0_3 = this->unk_336;
            if (temp_v0_3 == 0) {
                func_801518B0(globalCtx, 0x3354U, &this->actor);
                phi_t4 = (u16)0x3354;
                goto block_49;
            } else if (temp_v0_3 == 2) {
                temp_t6 = gSaveContext.extra.unk_160;
                temp_t7 = gSaveContext.extra.unk_164;
                sp20 = temp_t6;
                sp24 = temp_t7;
                if ((temp_t6 != 0) || (temp_t7 >= 0x2EE0U)) {
                    func_801518B0(globalCtx, 0x3356U, &this->actor);
                    this->unk33E = 0x3356;
                } else {
                    sp34 = sp24;
                    sp30 = sp20;
                    if ((s32) sp24 < gSaveContext.unkEEC) {
                        gSaveContext.unkEEC = (s32) sp24;
                        globalCtx = globalCtx;
                        EnMa4_SetFaceExpression(this, (u16)0, (u16)3);
                        func_801518B0(globalCtx, 0x3350U, &this->actor);
                        this->unk33E = 0x3350;
                    } else {
                        func_801518B0(globalCtx, 0x3351U, &this->actor);
                        this->unk33E = 0x3351;
                    }
                }
                this->unk_336 = 0;
                this->actor.flags = this->actor.flags & 0xFFFEFFFF;
                return;
            }
        }
    } else {
        if (gSaveContext.unk20 != 4) {
            if ((gSaveContext.unkF0D & 0x80) == 0) {
                func_801518B0(globalCtx, 0x3335U, &this->actor);
                this->unk33E = 0x3335;
                gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x80);
                return;
            }
            globalCtx = globalCtx;
            EnMa4_SetFaceExpression(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x3337U, &this->actor);
            this->unk33E = 0x3337;
            func_80151BB4((s32) globalCtx, 5U);
            return;
        }
        temp_v0_4 = this->unk_336;
        if (temp_v0_4 == 0) {
            temp_v0_5 = gSaveContext.unkF0D;
            if ((temp_v0_5 & 0x40) == 0) {
                func_801518B0(globalCtx, 0x3338U, &this->actor);
                this->unk33E = 0x3338;
                gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x40);
                return;
            }
            if ((temp_v0_5 & 0x20) != 0) {
                func_801518B0(globalCtx, 0x3347U, &this->actor);
                this->unk33E = 0x3347;
                return;
            }
            func_801518B0(globalCtx, 0x3346U, &this->actor);
            this->unk33E = 0x3346;
            return;
        }
        if (temp_v0_4 == 2) {
            temp_t2 = gSaveContext.extra.unk_160;
            temp_t3 = gSaveContext.extra.unk_164;
            sp20 = temp_t2;
            sp24 = temp_t3;
            if ((temp_t2 != 0) || (temp_t3 >= 0x2EE0U)) {
                globalCtx = globalCtx;
                EnMa4_SetFaceExpression(this, (u16)0, (u16)0);
                func_801518B0(globalCtx, 0x336DU, &this->actor);
                this->unk33E = 0x336D;
            } else {
                sp34 = sp24;
                sp30 = sp20;
                if ((s32) sp24 < gSaveContext.unkEEC) {
                    gSaveContext.unkEEC = (s32) sp24;
                    globalCtx = globalCtx;
                    EnMa4_SetFaceExpression(this, (u16)0, (u16)3);
                    func_801518B0(globalCtx, 0x3350U, &this->actor);
                    this->unk33E = 0x3350;
                } else {
                    func_801518B0(globalCtx, 0x3351U, &this->actor);
                    this->unk33E = 0x3351;
                }
            }
            this->unk_336 = 0;
            this->actor.flags = this->actor.flags & 0xFFFEFFFF;
            return;
        }
        if (temp_v0_4 == 3) {
            func_801518B0(globalCtx, 0x3340U, &this->actor);
            this->unk33E = 0x3340;
            this->actor.flags = this->actor.flags & 0xFFFEFFFF;
            return;
        }
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF7C8.asm")


void EnMa4_SetFaceExpression(EnMa4 *this, s16 arg1, s16 arg2) {
    this->unk_32C = arg1;
    this->unk_330 = arg2;
}

void func_80ABFCD4(EnMa4 *this) {
    if (this->unk_332 != 2) {
        EnMa4_SetFaceExpression(this, 0, 0);
    } else {
        EnMa4_SetFaceExpression(this, 1, 2);
    }
}

void EnMa4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80ABDCA0(this);
    this->actionFunc(this, globalCtx);
    func_80ABDD9C(this, globalCtx);
}


s32 EnMa4_OverrideLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnMa4* this = THIS;
    Vec3s sp4;

    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        sp4 = this->unk_1E0;
        rot->x = rot->x + sp4.y;
        rot->z = rot->z + sp4.x;
    }
    if (limbIndex == OBJECT_MA1_LIMB_HEAD) {
        sp4 = this->unk_1E6;
        rot->x = rot->x - sp4.y;
        rot->z = rot->z - sp4.x;
    }

    return 0;
}


extern Vec3f D_80AC0264;
extern Gfx D_060003B0[];

void EnMa4_PostLimbDraw(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnMa4* this = THIS;
    Vec3f sp28 = D_80AC0264;

    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        SysMatrix_MultiplyVector3fByState(&sp28, &this->actor.focus.pos);
    } else if ((limbIndex == OBJECT_MA1_LIMB_ARM_RIGHT) && (this->unk_33A == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, D_060003B0);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}


extern void* D_80AC00E8[]; // eye textures
extern void* D_80AC00FC[]; // mouth textures

extern Gfx D_06000A20[];

void EnMa4_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (this->unk_332 == 2) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06000A20);
    }

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80AC00E8[this->unk_32E]));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_80AC00FC[this->unk_330]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, EnMa4_OverrideLimbDraw, EnMa4_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
