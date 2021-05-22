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
void func_80ABFCAC(EnMa4* this, s16, s16);
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


/*
// ChangeAnim
void func_80ABDD2C(EnMa4 *this, s32 arg1) {
    void *sp28;
    void *temp_v1;

    temp_v1 = (index * 0x10) + &D_80AC010C;
    sp28 = temp_v1;
    SkelAnime_ChangeAnim(&this->skelAnime, temp_v1->unk0, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(temp_v1->unk0), (?32) temp_v1->unk8, temp_v1->unkC);
}
#if 0
    SkelAnime_ChangeAnim(&this->skelAnime, D_80B8E1A8[index].unk_00, 1.0f, 0.0f, 
        SkelAnime_GetFrameCount(&D_80B8E1A8[index].unk_00->common), 
        D_80B8E1A8[index].unk_08, D_80B8E1A8[index].unk_0C);
#endif
*/
void func_80ABDD2C(EnMa4* this, s32 index);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD2C.asm")


/*
void func_80ABDD9C(EnMa4 *this, GlobalContext *globalCtx) {
    Actor *temp_v1;
    AnimationHeader *temp_v0;
    s32 phi_a3;

    temp_v1 = globalCtx->actorCtx.actorList[2].first;
    if ((s16) this->unk_1D8 == 0) {
        temp_v0 = this->skelAnime.animCurrentSeg;
        if ((temp_v0 == &D_06007328) || (temp_v0 == 0x6002A8C) || (temp_v0 == 0x6015B7C)) {
            phi_a3 = 1;
        } else {
block_5:
            phi_a3 = 0;
            if (this->unk_332 == 2) {
                phi_a3 = 0;
                if (func_80ABEF8C != this->actionFunc) {
                    phi_a3 = 1;
                }
            }
        }
    } else {
        goto block_5;
    }
    this->unk1F0 = (bitwise s32) temp_v1->world.pos.x;
    this->unk1F4 = (bitwise s32) temp_v1->world.pos.y;
    this->unk1F8 = (bitwise s32) temp_v1->world.pos.z;
    this->unk1F4 = (f32) ((bitwise f32) this->unk1F4 - -10.0f);
    func_800BD888(&this->unk_1D8, 0, phi_a3);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD9C.asm")



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
    sp20.x = (f32) this->unk_200[1].x;
    sp20.y = (f32) this->unk_200[1].y;
    sp20.z = (f32) this->unk_200[1].z;

    this->actor.world.pos = this->actor.home.pos;
    this->actor.shape.rot.y = this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &sp20);
}


extern FlexSkeletonHeader D_06013928;

extern ColliderCylinderInit D_80AC00B0;
extern CollisionCheckInfoInit2 D_80AC00DC;

#ifdef NON_MATCHING
void EnMa4_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;
    u32 temp_v0;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, NULL, this->limbDrawTable, this->transitionDrawTable, OBJECT_MA1_LIMB_TABLE_COUNT);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80AC00B0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80AC00DC);
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 0;
    this->unk_1D8 = (u16)0;
    this->unk_334 = (u16)0;
    this->unk_33A = 1;
    this->unk_330 = (u16)0;
    this->unk_33C = (u16)0;

    if (CURRENT_DAY == (u16)1) {
        this->unk_332 = (u16)0;
    } else if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
        this->unk_332 = (u16)1;
    } else {
        this->unk_332 = (u16)2;
        this->unk_33A = 0;
    }

    if (func_800EE1D8(globalCtx) != 0) {
        func_80ABDD2C(this, 0);
        this->unk_336 = (u16)1;
        func_80ABF198(this, globalCtx);
    } else {
        func_80ABDE60(this, globalCtx);
        temp_v0 = gSaveContext.perm.entranceIndex;
        if (temp_v0 == 0x6410) {
            func_80ABDD2C(this, 0);
            this->unk_336 = (u16)2;
        } else if (temp_v0 == 0x64A0) {
            func_80ABDD2C(this, 0);
            this->unk_336 = (u16)3;
        } else {
            if (this->unk_332 == 2) {
                func_80ABDD2C(this, 0xE);
                this->actor.shape.shadowScale = 0.0f;
            } else {
                func_80ABDD2C(this, 8);
            }
            this->unk_336 = (u16)0;
        }
        func_80ABE4A4(this);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Init.asm")
#endif

void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    gSaveContext.perm.weekEventReg[0x8] &= 0xFE;
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
                func_80ABDD2C(this, 13);
                D_80AC024C = 0xD;
            }
        } else {
            this->actor.speedXZ = 2.7f;
            func_80ABDD2C(this, 9);
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
            func_80ABDD2C(this, 3);
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
            func_80ABDD2C(this, 9);
            this->actor.speedXZ = 2.7f;
        } else {
            func_80ABDD2C(this, 15);
            this->actor.speedXZ = 0.0f;
        }
    } else {
        func_80ABDD2C(this, 1);
        this->actor.speedXZ = 0.0f;
    }

    this->actor.gravity = -0.2f;
    this->unk_33C = 0;
    func_80ABFCD4(this);
    this->actionFunc = func_80ABE560;
}


/*
void func_80ABE560(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player;
    s16 sp22;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 phi_v0;

    player = PLAYER;
    sp22 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;
    temp_v0 = this->unk_336;
    if ((temp_v0 == 2) || (temp_v0 == 3)) {
        this->actor.flags = this->actor.flags | 0x10000;
    } else if (this->unk_332 != 2) {
        func_80ABE1C4(this, globalCtx);
    } else if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        this->unk_33C = this->unk_33C + 1;
        temp_v0_2 = this->unk_33C;
        if (temp_v0_2 == 5) {
            func_80ABDD2C(this, 17);
        } else if (temp_v0_2 == 8) {
            this->unk_33C = 0;
            func_80ABDD2C(this, 15);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        func_80ABF7C8(this, globalCtx);
        func_80ABEF34(this);
    } else if (this->unk_332 != 2 || ABS_ALT(sp22) < 0x4000) {
        if ((player->stateFlags1 << 8) >= 0) {
        //if ((player->stateFlags1 & 0xFFFFFF00))
            func_800B8614((Actor *) this, globalCtx, 100.0f);
        }
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE560.asm")


/*
void func_80ABE6C8(EnMa4 *this, GlobalContext *globalCtx) {
    u32 temp_t7;

    if (func_80147624(globalCtx) != 0) {
        temp_t7 = (u16) this->unk33E - 0x3339;
        if (temp_t7 < 0x21U) {
            goto **(&jtbl_D_80AC027C + (temp_t7 * 4));
        case 0:
            if (globalCtx->msgCtx.choiceIndex != 0) {
                func_8019F208();
                func_801518B0(globalCtx, 0x333BU, (Actor *) this);
                this->unk33E = 0x333B;
                return;
            case 8:
                if (globalCtx->msgCtx.choiceIndex != 0) {
                    func_8019F230();
                    func_80ABFCAC(this, (u16)0, (u16)1);
                    func_801518B0(globalCtx, 0x3342U, (Actor *) this);
                    this->unk33E = 0x3342;
                    this->unk_336 = 0;
                    func_80151BB4((s32) globalCtx, 5U);
                    return;
                case 13:
                    if (globalCtx->msgCtx.choiceIndex != 0) {
                        func_8019F230();
                        func_80ABFCAC(this, (u16)0, (u16)1);
                        func_801518B0(globalCtx, 0x3342U, (Actor *) this);
                        this->unk33E = 0x3342;
                        return;
                    case 14:
                        if (globalCtx->msgCtx.choiceIndex != 0) {
                            func_8019F230();
                            func_801518B0(globalCtx, 0x3348U, (Actor *) this);
                            this->unk33E = 0x3348;
                            func_80151BB4((s32) globalCtx, 5U);
                            return;
                        case 20:
                            if (globalCtx->msgCtx.choiceIndex != 0) {
                                func_8019F230();
                                func_80ABFCAC(this, (u16)0, (u16)0);
                                func_801518B0(globalCtx, 0x334CU, (Actor *) this);
                                this->unk33E = 0x334C;
                                return;
                            case 27:
                                if (globalCtx->msgCtx.choiceIndex != 0) {
                                    func_8019F230();
                                    func_80ABFCAC(this, (u16)1, (u16)0);
                                    func_801518B0(globalCtx, 0x3355U, (Actor *) this);
                                    this->unk33E = 0x3355;
                                    func_80151BB4((s32) globalCtx, 5U);
                                    return;
                                case 29:
                                    if (globalCtx->msgCtx.choiceIndex != 0) {
                                        if (this->unk_332 != 1) {
                                            func_8019F230();
                                            func_80ABFCAC(this, (u16)4, (u16)2);
                                            func_801518B0(globalCtx, 0x335BU, (Actor *) this);
                                            this->unk33E = 0x335B;
                                            func_80151BB4((s32) globalCtx, 5U);
                                            return;
                                        case 32:
                                            if (globalCtx->msgCtx.choiceIndex != 0) {
                                                func_8019F230();
                                                func_80ABFCAC(this, (u16)4, (u16)2);
                                                func_801518B0(globalCtx, 0x335AU, (Actor *) this);
                                                this->unk33E = 0x335A;
                                                func_80151BB4((s32) globalCtx, 5U);
                                            default:
                                                return;
                                            }
                                            func_8019F208();
                                            func_801518B0(globalCtx, 0x3349U, (Actor *) this);
                                            this->unk33E = 0x3349;
                                            return;
                                        }
                                        func_8019F230();
                                        func_80ABFCAC(this, (u16)3, (u16)3);
                                        func_801518B0(globalCtx, 0x3357U, (Actor *) this);
                                        this->unk33E = 0x3357;
                                        func_80151BB4((s32) globalCtx, 5U);
                                        return;
                                        return;
                                    }
                                    func_8019F208();
                                    func_801477B4(globalCtx);
                                    func_80ABF070(this);
                                    return;
                                }
                                func_8019F208();
                                func_801518B0(globalCtx, 0x3349U, (Actor *) this);
                                this->unk33E = 0x3349;
                                return;
                                return;
                            }
                            func_8019F208();
                            func_801518B0(globalCtx, 0x334EU, (Actor *) this);
                            this->unk33E = 0x334E;
                            if ((*(gBitFlags + 0x38) & (s32) gSaveContext.perm.inv.pad4C) != 0) {
                                func_80151BB4((s32) globalCtx, 0x1CU);
                            }
                            func_80151BB4((s32) globalCtx, 5U);
                            return;
                            return;
                        }
                        func_8019F208();
                        func_801518B0(globalCtx, 0x3349U, (Actor *) this);
                        this->unk33E = 0x3349;
                        return;
                        return;
                    }
                    func_8019F208();
                    gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x20);
                    func_801518B0(globalCtx, 0x3343U, (Actor *) this);
                    this->unk33E = 0x3343;
                    return;
                    return;
                }
                func_8019F208();
                gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x20);
                func_801518B0(globalCtx, 0x3343U, (Actor *) this);
                this->unk33E = 0x3343;
                return;
                return;
            }
            func_8019F208();
            func_801518B0(globalCtx, 0x333AU, (Actor *) this);
            this->unk33E = 0x333A;
            return;
            return;
        }
    }
default:
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE6C8.asm")

/*
void func_80ABEB6C(EnMa4 *this, GlobalContext *globalCtx) {
    Actor *sp24;
    Actor *temp_t6;
    GlobalContext *temp_a0;
    GlobalContext *temp_a0_2;
    GlobalContext *temp_a3;
    u16 temp_v0;
    u32 temp_t7;

    temp_a3 = globalCtx;
    temp_t6 = temp_a3->actorCtx.actorList[2].first;
    globalCtx = temp_a3;
    sp24 = temp_t6;
    if (func_80147624(temp_a3) != 0) {
        temp_v0 = (u16) this->unk33E;
        temp_t7 = temp_v0 - 0x3335;
        if ((s32) temp_v0 >= 0x2391) {
            if (temp_t7 < 0x39U) {
                goto **(&jtbl_D_80AC0300 + (temp_t7 * 4));
block_4:
                if (temp_v0 == 0x2390) {
                    func_801477B4(globalCtx);
                    func_80ABF070(this);
                    return;
                case 0:
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)3);
                    func_801518B0(globalCtx, 0x3336U, (Actor *) this);
                    this->unk33E = 0x3336;
                    func_80151BB4((s32) globalCtx, 5U);
                    return;
                case 3:
                    func_801518B0(globalCtx, 0x3339U, (Actor *) this);
                    this->unk33E = 0x3339;
                    return;
                case 5:
                case 6:
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)3);
                    func_801518B0(globalCtx, 0x333CU, (Actor *) this);
                    this->unk33E = 0x333C;
                    return;
                case 7:
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)2);
                    func_801518B0(globalCtx, 0x333DU, (Actor *) this);
                    this->unk33E = 0x333D;
                    return;
                case 8:
                    func_801518B0(globalCtx, 0x333EU, (Actor *) this);
                    this->unk33E = 0x333E;
                    return;
                case 9:
                    func_801477B4(globalCtx);
                    func_80ABF760(this);
                    return;
                case 10:
                    func_801518B0(globalCtx, 0x3340U, (Actor *) this);
                    this->unk33E = 0x3340;
                    return;
                case 11:
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)3);
                    func_801518B0(globalCtx, 0x3341U, (Actor *) this);
                    this->unk33E = 0x3341;
                    return;
                case 14:
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)0);
                    func_801518B0(globalCtx, 0x3344U, (Actor *) this);
                    this->unk33E = 0x3344;
                    return;
                case 15:
                    func_801518B0(globalCtx, 0x3345U, (Actor *) this);
                    this->unk33E = 0x3345;
                    return;
                case 16:
                    func_801518B0(globalCtx, 0x3349U, (Actor *) this);
                    this->unk33E = 0x3349;
                    return;
                case 20:
                    func_801518B0(globalCtx, 0x334AU, (Actor *) this);
                    this->unk33E = 0x334A;
                    return;
                case 21:
                    func_801477B4(globalCtx);
                    func_80ABF070(this);
                    return;
                case 23:
                    func_801518B0(globalCtx, 0x334DU, (Actor *) this);
                    this->unk33E = 0x334D;
                    return;
                case 27:
                case 28:
                case 40:
                case 41:
                    if (this->unk_332 != 0) {
                        func_801518B0(globalCtx, 0x3356U, (Actor *) this);
                        this->unk33E = 0x3356;
                        return;
                    case 29:
                    case 56:
                        globalCtx = globalCtx;
                        func_80ABFCAC(this, (u16)0, (u16)0);
                        temp_a0 = globalCtx;
                        if ((*(gBitFlags + 0x38) & (s32) gSaveContext.perm.inv.pad4C) == 0) {
                            globalCtx = globalCtx;
                            func_801477B4(temp_a0);
                            sp24->unkA6C = (s32) (sp24->unkA6C | 0x20);
                            func_80ABF494(this);
                            func_80ABF4A8(this, globalCtx);
                            return;
                        case 35:
                            temp_a0_2 = globalCtx;
                            if ((gSaveContext.perm.unk20 != 4) || ((*(gBitFlags + 0x38) & (s32) gSaveContext.perm.inv.pad4C) == 0)) {

                            } else {
                                func_801518B0(globalCtx, 0x3359U, (Actor *) this);
                                this->unk33E = 0x3359;
                            default:
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                                return;
                            }
                            globalCtx = globalCtx;
                            func_801518B0(temp_a0_2, 0x335CU, (Actor *) this);
                            this->unk33E = 0x335C;
                            func_80151BB4((s32) globalCtx, 5U);
                            return;
                        }
                        func_801518B0(globalCtx, 0x334CU, (Actor *) this);
                        this->unk33E = 0x334C;
                        return;
                        return;
                    }
                    func_801518B0(globalCtx, 0x3352U, (Actor *) this);
                    this->unk33E = 0x3352;
                    return;
                    return;
                }
            }
        } else {
            goto block_4;
        }
    }
default:
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEB6C.asm")


/*
void func_80ABEF34(EnMa4 *this) {
    if (this->unk_332 != 2) {
        func_80ABDD2C(this, 1);
    } else {
        func_80ABDD2C(this, 0xF);
    }
    this->actionFunc = func_80ABEF8C;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF34.asm")


/*
void func_80ABEF8C(EnMa4 *this, GlobalContext *globalCtx) {
    GlobalContext *temp_a0;
    u32 temp_v0;

    temp_v0 = func_80152498(&globalCtx->msgCtx);
    if (temp_v0 < 7U) {
        goto **(&jtbl_D_80AC03E4 + (temp_v0 * 4));
    case 4:
        func_80ABE6C8(this, globalCtx);
        goto block_8;
    case 5:
        func_80ABEB6C(this, globalCtx);
        goto block_8;
    case 6:
        temp_a0 = globalCtx;
        globalCtx = globalCtx;
        if (func_80147624(temp_a0) != 0) {
            if ((globalCtx->unk169B9 == 0) || ((*(gBitFlags + 0x48) & *gSaveContext.perm.inv.pad4C) == 0)) {
                func_80ABE4A4(this);
            }
        }
    }
default:
case 0:
block_8:
    if (this->unk_332 != 2) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, (u16)5, (u16)0x7D0, 0x3E8);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF8C.asm")

void func_80ABF070(EnMa4 *this) {
    this->actionFunc = func_80ABF084;
}

/*
void func_80ABF084(EnMa4 *this, GlobalContext *globalCtx) {
    globalCtx->nextEntranceIndex = 0x6400;
    gSaveContext.unk3F4A = (u16)0xFFF0;
    globalCtx->unk18875 = 0x14;
    globalCtx->unk1887F = 0x50;
    gSaveContext.unk3F55 = (u8)3;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF084.asm")


/*
void func_80ABF0D8(EnMa4 *this, GlobalContext *globalCtx) {
    GlobalContext *temp_a1;

    temp_a1 = globalCtx;
    globalCtx = globalCtx;
    if (func_800B84D0((Actor *) this, temp_a1) != 0) {
        func_801518B0(globalCtx, 0x336EU, (Actor *) this);
        this->actionFunc = func_80ABF160;
        return;
    }
    if ((gSaveContext.extra.unk_160 == 0) && ((u32) gSaveContext.extra.unk_164 < 0x2CECU)) {
        func_800B8614((Actor *) this, globalCtx, 100.0f);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF0D8.asm")

/*
void func_80ABF160(EnMa4 *this, GlobalContext *globalCtx) {
    if (func_800B867C((Actor *) this, globalCtx) != 0) {
        this->actionFunc = func_80ABF254;
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF160.asm")


void func_80ABF198(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    globalCtx->interfaceCtx.unk_280 = 1;
    func_8010E9F0(4, 0);
    gSaveContext.perm.weekEventReg[0x8] |= 0x01;
    func_80112AFC(globalCtx);
    player->stateFlags1 |= 0x20;
    this->actionFunc = func_80ABF218;
}


void func_80ABF218(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    //temp_v0 = globalCtx->actorCtx.actorList[2].first;
    if (globalCtx->interfaceCtx.unk_280 == 8) {
        this->actionFunc = func_80ABF254;
        player->stateFlags1 = (s32) (player->stateFlags1 & ~0x20);
    }
}

extern s16 D_80AC0258;

/*
void func_80ABF254(EnMa4 *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    s16 temp_v0_2;

    //temp_v0 = globalCtx->actorCtx.actorList[2].first;
    player->stateFlags1 = (s32) (player->stateFlags1 | 0x400);
    func_80ABF0D8(this, globalCtx);
    temp_v0_2 = this->unk_338;
    if (D_80AC0258 != temp_v0_2) {
        D_80AC0258 = temp_v0_2;
        globalCtx->interfaceCtx.unk25C = 1;
    }
    if ((gSaveContext.extra.unk_160 != 0) || ((u32) gSaveContext.extra.unk_164 >= 0x2EE0U) || (this->unk_338 == 0xA)) {
        gSaveContext.extra.unk_134 = (u8)6;
        func_80ABF2FC(this, globalCtx);
        D_80AC0258 = (u16)0;
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF254.asm")

void func_80ABF2FC(EnMa4 *this, GlobalContext *globalCtx) {
    gSaveContext.perm.weekEventReg[0x8] &= 0xFE;
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

/*
void func_80ABF4A8(EnMa4 *this, GlobalContext *globalCtx) {
    s16 sp1E;
    s8 temp_a0;

    temp_a0 = this->actor.cutscene;
    sp1E = (s16) temp_a0;
    if (ActorCutscene_GetCanPlayNext((s16) temp_a0) != 0) {
        ActorCutscene_Start((s16) temp_a0, (Actor *) this);
        func_80ABF51C(this);
    } else {
        if (ActorCutscene_GetCurrentIndex(temp_a0) == 0x7C) {
            ActorCutscene_Stop((u16)0x7C);
        }
        ActorCutscene_SetIntentToPlay(sp1E);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF4A8.asm")

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
                        func_80ABDD2C(this, 4);
                    }
                } else {
                    this->unk_33A = 1;
                    func_80ABDD2C(this, (s32) (u16)1);
                }
            }
        }
        func_800EDF24(this, globalCtx, sp24);
        if ((D_80AC0260 == 2) && (this->unk_33C == 0) && (func_801378B8(&this->skelAnime, (bitwise f32) (bitwise s32) this->skelAnime.animFrameCount) != 0)) {
            func_80ABDD2C(this, 7);
            return;
        }
    } else {
        temp_v0_2 = globalCtx->actorCtx.actorList[2].first;
        temp_v0_2->unkA6C = (s32) (temp_v0_2->unkA6C | 0x20);
        func_800B85E0((Actor *) this, globalCtx, 200.0f, -1);
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

/*void func_80ABF6B0(EnMa4 *this, GlobalContext *globalCtx) {
    Actor *sp24;
    Actor *temp_v1;

    temp_v1 = globalCtx->actorCtx.actorList[2].first;
    this->actor.flags = this->actor.flags | 0x10000;
    sp24 = temp_v1;
    if (func_800B84D0((Actor *) this, globalCtx) != 0) {
        temp_v1->unkA6C = (s32) (temp_v1->unkA6C & ~0x20);
        func_801518B0(globalCtx, 0x334CU, (Actor *) this);
        this->unk33E = 0x334C;
        this->actor.flags = this->actor.flags & 0xFFFEFFFF;
        func_80ABEF34(this);
        return;
    }
    func_800B85E0((Actor *) this, globalCtx, 200.0f, -1);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF6B0.asm")


void func_80ABF760(EnMa4 *this) {
    this->actionFunc = func_80ABF774;
}


/*
void func_80ABF774(EnMa4 *this, GlobalContext *globalCtx) {
    globalCtx->nextEntranceIndex = 0x6400;
    gSaveContext.unk3F4A = (u16)0xFFF5;
    globalCtx->unk18875 = 0x14;
    globalCtx->unk1887F = 0x40;
    gSaveContext.unk3F55 = (u8)2;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF774.asm")


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
                func_801518B0(globalCtx, 0x3335U, (Actor *) this);
                phi_t4 = (u16)0x3335;
block_49:
                this->unk33E = phi_t4;
            } else {
                temp_v0_2 = this->unk_336;
                if (temp_v0_2 == 0) {
                    func_801518B0(globalCtx, 0x3358U, (Actor *) this);
                    this->unk33E = 0x3358;
                    return;
                }
                if (temp_v0_2 == 2) {
                    temp_t0 = gSaveContext.extra.unk_160;
                    temp_t1 = gSaveContext.extra.unk_164;
                    sp20 = temp_t0;
                    sp24 = temp_t1;
                    if ((temp_t0 != 0) || (temp_t1 >= 0x2EE0U)) {
                        func_801518B0(globalCtx, 0x3356U, (Actor *) this);
                        this->unk33E = 0x3356;
                    } else {
                        sp34 = sp24;
                        sp30 = sp20;
                        if ((s32) sp24 < gSaveContext.unkEEC) {
                            gSaveContext.unkEEC = (s32) sp24;
                            func_801518B0(globalCtx, 0x335DU, (Actor *) this);
                            this->unk33E = 0x335D;
                        } else {
                            func_801518B0(globalCtx, 0x335EU, (Actor *) this);
                            this->unk33E = 0x335E;
                        }
                    }
                    this->unk_336 = 0;
                    this->actor.flags = this->actor.flags & 0xFFFEFFFF;
                    return;
                }
            }
        } else {
            if (gSaveContext.perm.unk20 != 4) {
                if ((gSaveContext.unkF0D & 0x80) == 0) {
                    func_801518B0(globalCtx, 0x3335U, (Actor *) this);
                    this->unk33E = 0x3335;
                    gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x80);
                    return;
                }
                globalCtx = globalCtx;
                func_80ABFCAC(this, (u16)3, (u16)3);
                func_801518B0(globalCtx, 0x3337U, (Actor *) this);
                this->unk33E = 0x3337;
                func_80151BB4((s32) globalCtx, 5U);
                return;
            }
            temp_v0_3 = this->unk_336;
            if (temp_v0_3 == 0) {
                func_801518B0(globalCtx, 0x3354U, (Actor *) this);
                phi_t4 = (u16)0x3354;
                goto block_49;
            } else if (temp_v0_3 == 2) {
                temp_t6 = gSaveContext.extra.unk_160;
                temp_t7 = gSaveContext.extra.unk_164;
                sp20 = temp_t6;
                sp24 = temp_t7;
                if ((temp_t6 != 0) || (temp_t7 >= 0x2EE0U)) {
                    func_801518B0(globalCtx, 0x3356U, (Actor *) this);
                    this->unk33E = 0x3356;
                } else {
                    sp34 = sp24;
                    sp30 = sp20;
                    if ((s32) sp24 < gSaveContext.unkEEC) {
                        gSaveContext.unkEEC = (s32) sp24;
                        globalCtx = globalCtx;
                        func_80ABFCAC(this, (u16)0, (u16)3);
                        func_801518B0(globalCtx, 0x3350U, (Actor *) this);
                        this->unk33E = 0x3350;
                    } else {
                        func_801518B0(globalCtx, 0x3351U, (Actor *) this);
                        this->unk33E = 0x3351;
                    }
                }
                this->unk_336 = 0;
                this->actor.flags = this->actor.flags & 0xFFFEFFFF;
                return;
            }
        }
    } else {
        if (gSaveContext.perm.unk20 != 4) {
            if ((gSaveContext.unkF0D & 0x80) == 0) {
                func_801518B0(globalCtx, 0x3335U, (Actor *) this);
                this->unk33E = 0x3335;
                gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x80);
                return;
            }
            globalCtx = globalCtx;
            func_80ABFCAC(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x3337U, (Actor *) this);
            this->unk33E = 0x3337;
            func_80151BB4((s32) globalCtx, 5U);
            return;
        }
        temp_v0_4 = this->unk_336;
        if (temp_v0_4 == 0) {
            temp_v0_5 = gSaveContext.unkF0D;
            if ((temp_v0_5 & 0x40) == 0) {
                func_801518B0(globalCtx, 0x3338U, (Actor *) this);
                this->unk33E = 0x3338;
                gSaveContext.unkF0D = (u8) (gSaveContext.unkF0D | 0x40);
                return;
            }
            if ((temp_v0_5 & 0x20) != 0) {
                func_801518B0(globalCtx, 0x3347U, (Actor *) this);
                this->unk33E = 0x3347;
                return;
            }
            func_801518B0(globalCtx, 0x3346U, (Actor *) this);
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
                func_80ABFCAC(this, (u16)0, (u16)0);
                func_801518B0(globalCtx, 0x336DU, (Actor *) this);
                this->unk33E = 0x336D;
            } else {
                sp34 = sp24;
                sp30 = sp20;
                if ((s32) sp24 < gSaveContext.unkEEC) {
                    gSaveContext.unkEEC = (s32) sp24;
                    globalCtx = globalCtx;
                    func_80ABFCAC(this, (u16)0, (u16)3);
                    func_801518B0(globalCtx, 0x3350U, (Actor *) this);
                    this->unk33E = 0x3350;
                } else {
                    func_801518B0(globalCtx, 0x3351U, (Actor *) this);
                    this->unk33E = 0x3351;
                }
            }
            this->unk_336 = 0;
            this->actor.flags = this->actor.flags & 0xFFFEFFFF;
            return;
        }
        if (temp_v0_4 == 3) {
            func_801518B0(globalCtx, 0x3340U, (Actor *) this);
            this->unk33E = 0x3340;
            this->actor.flags = this->actor.flags & 0xFFFEFFFF;
            return;
        }
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF7C8.asm")


// EnMa4_SetFaceExpression
void func_80ABFCAC(EnMa4 *this, s16 arg1, s16 arg2) {
    this->unk_32C = arg1;
    this->unk_330 = arg2;
}

void func_80ABFCD4(EnMa4 *this) {
    if (this->unk_332 != 2) {
        func_80ABFCAC(this, 0, 0);
    } else {
        func_80ABFCAC(this, 1, 2);
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


// EnMa4_OverrideLimbDraw
s32 func_80ABFD9C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
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

// EnMa4_PostLimbDraw
void func_80ABFE48(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnMa4* this = THIS;
    Vec3f sp28;

    sp28 = D_80AC0264;
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

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, func_80ABFD9C, func_80ABFE48, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
