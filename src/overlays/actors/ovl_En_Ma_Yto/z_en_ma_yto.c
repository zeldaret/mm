/*
 * File: z_en_ma_yto.c
 * Overlay: ovl_En_Ma_Yto
 * Description: Cremia
 */

#include "z_en_ma_yto.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYto*)thisx)

void EnMaYto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Draw(Actor* thisx, GlobalContext* globalCtx);

s32  func_80B8E6E0(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8E84C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8E938(EnMaYto* this, GlobalContext* globalCtx);
s32  func_80B8EABC(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8EBDC(EnMaYto* this);
void func_80B8EBF0(EnMaYto* this, GlobalContext* globalCtx);

void func_80B90C08(EnMaYto* this, s32 index);
void func_80B90DF0(EnMaYto* this);
void func_80B90EC8(EnMaYto* this, s16, s16);

s32  func_80B91014(void);
void func_80B9109C(void);

/*
const ActorInit En_Ma_Yto_InitVars = {
    ACTOR_EN_MA_YTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA2,
    sizeof(EnMaYto),
    (ActorFunc)EnMaYto_Init,
    (ActorFunc)EnMaYto_Destroy,
    (ActorFunc)EnMaYto_Update,
    (ActorFunc)EnMaYto_Draw,
};
*/

extern ColliderCylinderInit D_80B91410;
extern CollisionCheckInfoInit2 D_80B9143C;

extern SkeletonHeader D_06015C28;

void EnMaYto_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;
    ColliderCylinder* temp_a1;

    this->actor.targetMode = 0;
    this->unk_200 = 0;
    this->unk_310 = 0;
    this->unk_320 = 0;
    this->unk_31A = 0;

    if ((CURRENT_DAY == 1) || ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
        func_80B90EC8(this, 0, 1);
    } else {
        func_80B90EC8(this, 5, 2);
    }

    this->unk_31E = 0;
    this->unk_31C = 0x64;
    this->type = (s32)(this->actor.params & 0xF000) >> 0xC;
    if (func_80B8E6E0(this, globalCtx) == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06015C28, NULL, &this->unk_208, &this->unk_28C, 0x16);
    func_80B8E84C(this, globalCtx);
    temp_a1 = &this->collider;
    Collider_InitCylinder(globalCtx, temp_a1);
    Collider_SetCylinder(globalCtx, temp_a1, &this->actor, &D_80B91410);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B9143C);
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (func_80B8EABC(this, globalCtx) == 1) {
        func_80B8EBDC(this);
    } else {
        func_80B8E938(this, globalCtx);
    }
}

#ifdef NON_MATCHING
s32 func_80B8E6E0(EnMaYto* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case 0:
            if ((CURRENT_DAY == 3) && ((gSaveContext.perm.weekEventReg[0x16] & 1) == 0)) {
                return 0;
            }
        case 2:
            if ((CURRENT_DAY != 1) && ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
                return 0;
            }
        case 1:
            if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                if (((s32)(this->actor.params & 0xF00) >> 8) != 0) {
                    return 0;
                }
            } else if (((s32)(this->actor.params & 0xF00) >> 8) == 0) {
                return 0;
            }
            if (((s32)gSaveContext.perm.time >= 0xD555) && (CURRENT_DAY == 3)) {
                return 0;
            }
        case 3:
            if (((gSaveContext.perm.weekEventReg[0x34] & 1) == 0) &&
                ((gSaveContext.perm.weekEventReg[0x34] & 2) != 0)) {
                return 0;
            }
            if ((gSaveContext.perm.weekEventReg[0xE] & 1) != 0) {
                return 0;
            }
        case 4:
            return 1;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E6E0.asm")
#endif

void func_80B8E84C(EnMaYto* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case 0:
            func_80B90C08(this, 10);
            break;

        case 2:
            if (CURRENT_DAY == 1) {
                func_80B90C08(this, 14);
            } else {
                func_80B90C08(this, 16);
            }
            break;

        case 1:
            if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                func_80B90C08(this, 12);
            } else {
                func_80B90C08(this, 8);
            }
            break;

        case 3:
            func_80B90C08(this, 0);
            break;

        case 4:
            func_80B90C08(this, 0);
            break;

        default:
            func_80B90C08(this, 0);
            break;
    }
}

/*
void func_80B8E938(void *arg0, ? arg1) {
    u32 temp_t6;

    temp_t6 = arg0->unk204;
    if (temp_t6 < 5U) {
        goto **(&jtbl_D_80B91628 + (temp_t6 * 4));
    case 0:
        func_80B8EC30();
        return;
    case 2:
        arg0->unk1F = (u8)6;
        func_80B8F074();
        return;
    case 1:
        func_80B8F744();
        return;
    case 3:
        arg0->unk310 = (u16)0;
        if (gSaveContext.perm.inv.items[D_801C20B4] != 0x3C) {
block_9:
            func_80B8FE04(arg0);
            return;
        case 4:
            arg0->unk4 = (s32) (arg0->unk4 | 0x10);
            func_80B90340();
            return;
        }
        if ((gSaveContext.unkF2C & 1) == 0) {
            goto block_9;
        }
        if ((Rand_Next() & 0x80) == 0) {
            goto block_9;
        }
        func_80B902B8(arg0);
        return;
        return;
    }
    func_80B8EC30();
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E938.asm")

/*
? func_80B8EA38(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 temp_a1;
    void *temp_v1;
    void *temp_v1_2;
    void *phi_v1;

    temp_v1 = arg1->unk1CE4;
    phi_v1 = temp_v1;
    if (temp_v1 != 0) {
loop_1:
        if (phi_v1->unk0 == 0x21F) {
            temp_a1 = arg0->unk204;
            temp_v0 = (s16) ((s32) (phi_v1->unk1C & 0xF000) >> 0xC);
            if ((temp_a1 != 2) || (temp_v0 != 1)) {

            } else {
                arg0->unk124 = phi_v1;
                phi_v1->unk120 = arg0;
                return 1;
            }
            if ((temp_a1 == 1) && (temp_v0 == 0)) {
                arg0->unk124 = phi_v1;
                phi_v1->unk120 = arg0;
                return 1;
            }
        }
        temp_v1_2 = phi_v1->unk12C;
        phi_v1 = temp_v1_2;
        if (temp_v1_2 != 0) {
            goto loop_1;
        }
    }
    return 0;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EA38.asm")

/*
s32 func_80B8EABC(EnMaYto *this, GlobalContext *globalCtx) {
    s32 temp_t6;

    temp_t6 = this->type;
    if ((u32) temp_t6 < 5U) {
        goto **(&jtbl_D_80B9163C + (temp_t6 * 4));
    case 0:
        return 0;
    case 2:
        if ((gSaveContext.unkF0E & 1) != 0) {
block_6:
            if (func_80B8EA38() == 0) {
                return 1;
            case 1:
                if ((gSaveContext.unkF0E & 1) == 0) {
                    return 0;
                case 3:
                    return 0;
                case 4:
                    return 0;
                    return 0;
                }
                if (func_80B8EA38() == 0) {
                    return 1;
                    return 0;
                    return 0;
                }
                return 2;
            }
            return 2;
            return 1;
        }
        if (((s32) gSaveContext.perm.day % 5) != 2) {
            goto block_6;
        }
        return 0;
    }
    return 0;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EABC.asm")

void EnMaYto_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// Setup function
void func_80B8EBDC(EnMaYto *this) {
    this->actionFunc = func_80B8EBF0;
}

void func_80B8EBF0(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_80B8EABC(this, globalCtx) == 2) {
        func_80B8E938(this, globalCtx);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ECAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ED8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EF4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9000C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90340.asm")

void func_80B9037C(EnMaYto* this, GlobalContext* globalCtx);
/*
void func_80B9037C(EnMaYto *this, GlobalContext *globalCtx) {
    u32 sp24;
    s32 temp_t6;
    u16 temp_a0;
    u32 temp_v0;
    void *temp_v1;

    if (func_800EE29C(globalCtx, 0x22CU) != 0) {
        temp_v0 = func_800EE200(globalCtx, 0x22CU);
        temp_t6 = temp_v0 * 4;
        sp24 = temp_v0;
        temp_v1 = (globalCtx + temp_t6)->unk1F4C;
        if (globalCtx->csCtx.frames == temp_v1->unk2) {
            temp_a0 = temp_v1->unk0;
            if (D_80B915F0 != temp_a0) {
                D_80B915F0 = temp_a0;
                if (temp_a0 != 1) {
                    if (temp_a0 != 2) {
                        if (temp_a0 != 3) {

                        } else {
                            func_80B90C08(this, 0x16);
block_10:
                        }
                    } else {
                        gSaveContext.unkF06 = (u8) (gSaveContext.unkF06 | 1);
                        func_80B90C08(this, 0x12);
                        goto block_10;
                    }
                } else {
                    func_80B90C08(this, 0);
                    goto block_10;
                }
            }
        }
        func_800EDF24(this, globalCtx, sp24, globalCtx);
        if ((D_80B915F0 == 2) && (this->skelAnime.animCurrentSeg == 0x6001FD0) && (func_801378B8(&this->skelAnime,
(bitwise f32) (bitwise s32) this->skelAnime.animFrameCount) != 0)) { func_80B90C08(this, 0x14); return;
        }
    } else {
        D_80B915F0 = (u16)0x63;
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9037C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9059C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B905B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9061C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9083C.asm")

void func_80B90A78(EnMaYto* this, GlobalContext* globalCtx);

void func_80B90A78(EnMaYto* this, GlobalContext* globalCtx) {
    s32 temp_hi;

    if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
        temp_hi = CURRENT_DAY;
        if (temp_hi == 2) {
            if (this->unk_310 == 1) {
                func_801518B0(globalCtx, 0x33AEU, &this->actor);
                this->unk_322 = 0x33AE;
            } else {
                this->unk_310 = 1;
                func_80B9109C();
                func_801518B0(globalCtx, 0x33A9U, &this->actor);
                this->unk_322 = 0x33A9;
            }
        }
        else if (temp_hi == 3) {
            if (this->unk_310 == 1) {
                func_801518B0(globalCtx, 0x33CBU, &this->actor);
                this->unk_322 = 0x33CB;
            } else {
                this->unk_310 = 1;
                func_80B9109C();
                func_80B90EC8(this, (u16)0, (u16)1);
                func_801518B0(globalCtx, 0x33C6U, &this->actor);
                this->unk_322 = 0x33C6;
            }
        }
    } else {
        if (func_80B91014() != 0) {
            this->unk_31E = 2;
            func_80B90EC8(this, (u16)5, (u16)3);
            func_801518B0(globalCtx, 0x33B3U, &this->actor);
            this->unk_322 = 0x33B3;
            func_80151BB4(globalCtx, 6U);
        }
        else {
            func_80B9109C();
            func_80B90EC8(this, (u16)5, (u16)3);
            func_801518B0(globalCtx, 0x33B1U, &this->actor);
            this->unk_322 = 0x33B1;
        }
    }
}

/*
void func_80B90C08(EnMaYto *this, s32 index) {
    void *sp28;
    void *temp_v1;

    temp_v1 = (index * 0x10) + &D_80B91448;
    sp28 = temp_v1;
    SkelAnime_ChangeAnim(&this->skelAnime, temp_v1->unk0, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(temp_v1->unk0),
(?32) temp_v1->unk8, temp_v1->unkC);
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90C08.asm")

void func_80B90C78(EnMaYto* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    s16 phi_a3;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    phi_a3 = this->unk_31E == 2 ? 1 : 0;

    if (this->unk_31E == 0) {
        this->unk_1F0 = player->base.world.pos;
        this->unk_1EC = 0.0f;
    } else if (this->unk_31E == 1) {
        Math_Vec3f_StepTo(&this->unk_1F0, &this->actor.child->world.pos, 8.0f);
        this->unk_1EC = 0.0f;
    }

    if (this->unk_320 == 0) {
        if (this->actionFunc == func_80B9037C) {
            this->unk_1E0.y = (u16)0;
            this->unk_1E0.x = (u16)0;
        } else {
            func_800BD888(this, this->unk_1D8, 0xD, phi_a3);
        }
    } else {
        Math_SmoothStepToS(&this->unk_1E0.y, (u16)0, (u16)3, (u16)0x71C, 0xB6);
        Math_SmoothStepToS(&this->unk_1E0.x, (u16)0x18E3, (u16)5, (u16)0x71C, 0xB6);
    }

    func_80B90DF0(this);
}

void func_80B90D98(EnMaYto* this, GlobalContext* globalCtx);
/*
void func_80B90D98(EnMaYto *this, GlobalContext *globalCtx) {
    ColliderCylinder *sp1C;
    ColliderCylinder *temp_a2;

    temp_a2 = &this->collider;
    if (func_80B9037C != this->actionFunc) {
        sp1C = temp_a2;
        globalCtx = globalCtx;
        Collider_UpdateCylinder(&this->actor, temp_a2);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, (Collider *) temp_a2);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90D98.asm")

/*
void func_80B90DF0(EnMaYto *this) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    temp_v0 = this->unk316;
    if (temp_v0 != 0) {
        this->unk_31A = temp_v0;
        return;
    }
    temp_v0_2 = (s16) this->unk_31C;
    if (temp_v0_2 == 0x64) {
        temp_v0_3 = this->unk_31A;
        if (temp_v0_3 == 0) {
            this->unk_31C = 0;
            return;
        }
        this->unk_31A = temp_v0_3 - 1;
        return;
    }
    this->unk_31C = temp_v0_2 + 1;
    if ((s16) this->unk_31C == 0x64) {
        this->unk_31A = 2;
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E84.asm")


void func_80B90EC8(EnMaYto *this, s16 arg1, s16 arg2) {
    this->unk_316 = arg1;
    this->unk_318 = arg2;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91014.asm")

/*
s32 func_80B9109C(void) {
    s32 temp_hi;

    temp_hi = CURRENT_DAY;
    if (temp_hi == 1) {
        gSaveContext.perm.weekEventReg[0xD] |= 1<<2;
        return temp_hi;
    }
    if (temp_hi == 2) {
        gSaveContext.perm.weekEventReg[0xD] |= 1<<3;
        return temp_hi;
    }
    if (temp_hi != 3) {
        return temp_hi;
    }
    gSaveContext.perm.weekEventReg[0xD] |= 1<<4;
    return temp_hi;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9109C.asm")

void EnMaYto_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80B90D98(this, globalCtx);
    func_80B90C78(this, globalCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Update.asm")

extern AnimationHeader D_06007E28;
extern AnimationHeader D_06003D54;
extern AnimationHeader D_0600A174;
extern AnimationHeader D_060070EC;
extern AnimationHeader D_06003D54;

// OverrideLimbDraw
s32 func_80B91154(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMaYto* this = THIS;
    Vec3s sp4;

    if (limbIndex == 9) {
        sp4 = this->unk_1E0;
        rot->x = rot->x + sp4.y;
        rot->z = rot->z + sp4.x;
    } else if (limbIndex == 2) {
        if ((this->skelAnime.animCurrentSeg != &D_06007E28) && (this->skelAnime.animCurrentSeg != &D_06003D54)) {
            sp4 = this->unk_1E6;
            rot->x = rot->x + sp4.y;
            if ((this->skelAnime.animCurrentSeg == &D_0600A174) || (this->skelAnime.animCurrentSeg == &D_060070EC) ||
                (this->skelAnime.animCurrentSeg == &D_06003D54)) {
                rot->z = rot->z + sp4.x;
            }
        }
    }
    return 0;
}

// PostLimbDraw
void func_80B91250(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYto* this = THIS;

    if (limbIndex == 9) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

extern Gfx D_06005430[];
extern void* D_80B915C8[];
extern void* D_80B915D8[];

void EnMaYto_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (this->type == 1 && (gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06005430);
    }
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B915C8[this->unk_318]));
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B915D8[this->unk_31A]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B91154, func_80B91250, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
