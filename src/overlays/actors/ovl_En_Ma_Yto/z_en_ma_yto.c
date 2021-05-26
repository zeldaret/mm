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


void func_80B8EC30(EnMaYto* this);
void func_80B8ECAC(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8ED8C(EnMaYto* this);
void func_80B8EDC8(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8EEAC(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8EF4C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F074(EnMaYto* this);
void func_80B8F108(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F254(EnMaYto* this);
void func_80B8F2D8(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F360(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F400(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F744(EnMaYto* this);
void func_80B8F7F4(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8F918(EnMaYto* this);
void func_80B8F998(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8FA14(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8FE04(EnMaYto* this);
void func_80B8FE74(EnMaYto* this, GlobalContext* globalCtx);
void func_80B8FF80(EnMaYto* this);
void func_80B8FF94(EnMaYto* this, GlobalContext* globalCtx);

void func_80B9000C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B900AC(EnMaYto* this);
void func_80B900C0(EnMaYto* this, GlobalContext* globalCtx);
void func_80B90170(EnMaYto* this);
void func_80B90184(EnMaYto* this, GlobalContext* globalCtx);
void func_80B902B8(EnMaYto* this);
void func_80B902CC(EnMaYto* this, GlobalContext* globalCtx);
void func_80B90340(EnMaYto* this);

void func_80B9037C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B904D0(EnMaYto *this);
void func_80B904E4(EnMaYto *this, GlobalContext *globalCtx);
void func_80B9059C(EnMaYto *this);
void func_80B905B0(EnMaYto* this, GlobalContext* globalCtx);
void func_80B9061C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B9083C(EnMaYto* this, GlobalContext* globalCtx);
void func_80B90A78(EnMaYto* this, GlobalContext* globalCtx);
void func_80B90C08(EnMaYto* this, s32 index);
void EnMaYto_Blink(EnMaYto* this);
void func_80B90E50(EnMaYto* this, s16);
void func_80B90E84(EnMaYto* this, s16, s16);
void EnMaYto_SetFaceExpression(EnMaYto* this, s16 arg1, s16 mouthIndex);
void func_80B90EF0(EnMaYto* this);
s32  func_80B90F84();

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


/*

glabel D_80B91410
0x0A000039
0x20010000
0x00000000
0x00000000
0x00000000
0x00000000
0x00000000
0x00000100
0x0012002E
0x00000000
0x00000000
*/

/*
glabel D_80B9143C
0x00000000
0x00000000
0xFF000000
*/

/*
glabel D_80B91448
0x0600A174
0x3F800000
0x00000000
0x00000000
0x0600A174
0x3F800000
0x00000000
0xC0C00000
0x0600AF7C
0x3F800000
0x02000000
0x00000000
0x0600AF7C
0x3F800000
0x02000000
0xC0C00000
0x06000CC0
0x3F800000
0x00000000
0x00000000
0x06000CC0
0x3F800000
0x00000000
0xC0C00000
0x06016720
0x3F800000
0x00000000
0x00000000
0x06016720
0x3F800000
0x00000000
0xC1000000
0x06005314
0x3F800000
0x00000000
0x00000000
0x06005314
0x3F800000
0x00000000
0xC1000000
0x060093E8
0x3F800000
0x00000000
0x00000000
0x060093E8
0x3F800000
0x00000000
0xC1200000
0x06007E28
0x3F800000
0x00000000
0x00000000
0x06007E28
0x3F800000
0x00000000
0xC1000000
0x060070EC
0x3F800000
0x00000000
0x00000000
0x060070EC
0x3F800000
0x00000000
0xC1000000
0x06003D54
0x3F800000
0x00000000
0x00000000
0x06003D54
0x3F800000
0x00000000
0xC1000000
0x06001FD0
0x3F800000
0x00000000
0x00000000
0x06001FD0
0x3F800000
0x00000000
0xC1000000
0x060030B4
0x3F800000
0x00000000
0x00000000
0x060030B4
0x3F800000
0x00000000
0xC1000000
0x06004370
0x3F800000
0x00000000
0x00000000
0x06004370
0x3F800000
0x00000000
0xC1000000
*/

/*
extern u64 D_06014AD8[];
extern u64 D_06014ED8[];
extern u64 D_060152D8[];
extern u64 D_060156D8[];

// sMouthTextures
void* D_80B915C8[] = {
    D_06014AD8, D_06014ED8, D_060152D8, D_060156D8, 
};
*/

/*
extern u64 D_06011AD8[];
extern u64 D_060122D8[];
extern u64 D_06012AD8[];
extern u64 D_060132D8[];
extern u64 D_06013AD8[];
extern u64 D_060142D8[];

// sEyesTextures
void* D_80B915D8[] = {
    D_06011AD8, D_060122D8, D_06012AD8, D_060132D8, D_06013AD8, D_060142D8,
};
*/

/*
static u16 D_80B915F0 = 0x63;
glabel D_80B915F0
0x00630000
0x00000000
0x00000000
0x00000000
*/


extern ColliderCylinderInit D_80B91410;
extern CollisionCheckInfoInit2 D_80B9143C;

extern FlexSkeletonHeader D_06015C28;

void EnMaYto_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;
    ColliderCylinder* temp_a1;

    this->actor.targetMode = 0;
    this->unk_200 = 0;
    this->unk_310 = 0;
    this->unk_320 = 0;
    this->eyeTexIndex = 0;

    if ((CURRENT_DAY == 1) || ((gSaveContext.weekEventReg[0x16] & 1) != 0)) {
        EnMaYto_SetFaceExpression(this, 0, 1);
    } else {
        EnMaYto_SetFaceExpression(this, 5, 2);
    }

    this->unk_31E = 0;
    this->blinkTimer = 0x64;
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

// CheckValidSpawn
s32 func_80B8E6E0(EnMaYto* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case 0:
            if (CURRENT_DAY == 3 && !(gSaveContext.weekEventReg[0x16] & 1)) {
                return false;
            }
            break;

        case 2:
            if (CURRENT_DAY != 1 && (gSaveContext.weekEventReg[0x16] & 1)) {
                return false;
            }
            break;

        case 1:
            if (gSaveContext.weekEventReg[0x16] & 1) {
                if (((this->actor.params & 0xF00) >> 8) != 0) {
                    return false;
                }
            } else if (((this->actor.params & 0xF00) >> 8) == 0) {
                return false;
            }
            if (gSaveContext.time >= 0xD555 && CURRENT_DAY == 3) {
                return false;
            }
            break;

        case 3:
            if ((!(gSaveContext.weekEventReg[0x34] & 1) && !(gSaveContext.weekEventReg[0x34] & 2)) || (gSaveContext.weekEventReg[0xE] & 1)) {
                return false;
            }
            break;

        case 4:
            break;
    }

    return true;
}

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
            if (gSaveContext.weekEventReg[0x16] & 1) {
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


void func_80B8E938(EnMaYto *this, GlobalContext *globalCtx) {
    switch (this->type) {
        case 0:
            func_80B8EC30(this);
            break;

        case 2:
            this->actor.targetMode = 6;
            func_80B8F074(this);
            break;

        case 1:
            func_80B8F744(this);
            break;

        case 3:
            this->unk_310 = 0;
            if ((gSaveContext.inventory.items[gItemSlots[0x3C]] == 0x3C) && (gSaveContext.weekEventReg[0x34] & 1) != 0 && ((Rand_Next() & 0x80) != 0)) {
                func_80B902B8(this);
            } else {
                func_80B8FE04(this);
            }
            break;

        case 4:
            this->actor.flags = this->actor.flags | 0x10;
            func_80B90340(this);
            break;

        default:
            func_80B8EC30(this);
            break;
    }
}

#define EN_MA_YTS_PARSE_TYPE(params) (((params)&0xF000) >> 12)


// SearchRomani
s32 func_80B8EA38(EnMaYto *this, GlobalContext *globalCtx) {
    Actor *phi_v1;
    s16 romaniType;

    phi_v1 = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;
    while (phi_v1 != NULL) {
        if (phi_v1->id == ACTOR_EN_MA_YTS) {
            EnMaYts* romani = (EnMaYts*)phi_v1;

            romaniType = EN_MA_YTS_PARSE_TYPE(romani->actor.params);
            if (((this->type == 2) && (romaniType == 1)) || ((this->type == 1) && (romaniType == 0))) {
                this->actor.child = &romani->actor;
                romani->actor.parent = &this->actor;
                return 1;
            } else {
                phi_v1 = phi_v1->next;
                continue;
            }
        }
        phi_v1 = phi_v1->next;
    }
    return 0;
}


s32 func_80B8EABC(EnMaYto *this, GlobalContext *globalCtx) {
    switch (this->type) {
    case 0:
        return 0;

    case 2:
        if (!(gSaveContext.weekEventReg[0x16] & 1) && (CURRENT_DAY) == 2) {
            return 0;
        }
        if (func_80B8EA38(this, globalCtx) != 0) {
            return 2;
        }
        return 1;

    case 1:
        if ((gSaveContext.weekEventReg[0x16] & 1) != 0) {
            if (func_80B8EA38(this, globalCtx) != 0) {
                return 2;
            }
            return 1;
        }
        return 0;
        break;

    case 3:
        return 0;

    case 4:
        return 0;
    }
    return 0;
}


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


void func_80B8EC30(EnMaYto *this) {
    if (this->actor.shape.rot.y == this->actor.home.rot.y) {
        this->unk_314 = 11;
        func_80B90C08(this, 11);
    } else {
        this->unk_314 = 1;
        func_80B90C08(this, 1);
    }
    func_80B90EF0(this);
    this->unk_31E = 2;
    this->actionFunc = func_80B8ECAC;
}

void func_80B8ECAC(EnMaYto *this, GlobalContext *globalCtx) {
    s16 rotY = this->actor.home.rot.y - 0x8000;
    s16 sp2C;

    sp2C = rotY - this->actor.yawTowardsPlayer;
    if ((Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, (u16)5, (u16)0x3000, 0x100) == 0) && (this->unk_314 == 1)) {
        this->unk_314 = 11;
        func_80B90C08(this, 11);
    }

    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B9061C(this, globalCtx);
        func_80B8ED8C(this);
    } else if (ABS_ALT(sp2C) < 0x1555) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80B8ED8C(EnMaYto *this) {
    func_80B90C08(this, 1);
    this->unk_31E = 2;
    this->actionFunc = func_80B8EDC8;
}

extern AnimationHeader D_0600AF7C;

void func_80B8EDC8(EnMaYto *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 4:
            func_80B8EEAC(this, globalCtx);
            break;

        case 5:
            func_80B8EF4C(this, globalCtx);
            break;

        case 6:
            if (func_80147624(globalCtx) != 0) {
                this->unk_31E = 0;
                func_80B8EC30(this);
            }
            break;

        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, (u16)5, (u16)0x3000, 0x100);
    if ((this->textId == 0x3395) && (this->skelAnime.animCurrentSeg == &D_0600AF7C) && (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0)) {
        func_80B90C08(this, 4);
    }
}

void func_80B8EEAC(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            func_8019F208();
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x3392U, &this->actor);
            this->textId = 0x3392;
        }
        else {
            func_8019F230();
            func_801518B0(globalCtx, 0x3391U, &this->actor);
            this->textId = 0x3391;
        }
    }
}

void func_80B8EF4C(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        switch (this->textId) {
        case 0x3391:
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x3392U, &this->actor);
            this->textId = 0x3392;
            break;

        case 0x3392:
            EnMaYto_SetFaceExpression(this, (u16)3, (u16)1);
            func_801518B0(globalCtx, 0x3393U, &this->actor);
            this->textId = 0x3393;
            func_80151BB4(globalCtx, 6U);
            break;

        case 0x3394:
            func_80B90C08(this, 2);
            func_801518B0(globalCtx, 0x3395U, &this->actor);
            this->textId = 0x3395;
            break;

        case 0x3395:
            func_80B90C08(this, 1);
            func_801518B0(globalCtx, 0x3396U, &this->actor);
            this->textId = 0x3396;
            func_80151BB4(globalCtx, 6U);
            break;
        }
    }
}

void func_80B8F074(EnMaYto *this) {
    if ((CURRENT_DAY == 1) || ((gSaveContext.weekEventReg[0x16] & 1) != 0)) {
        func_80B90E50(this, 0);
        this->unk_31E = 0;
    } else {
        func_80B90E50(this, 2);
        this->unk_31E = 2;
    }
    func_80B90EF0(this);
    this->actionFunc = func_80B8F108;
}


void func_80B8F108(EnMaYto *this, GlobalContext *globalCtx) {
    s16 temp_v1 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B9083C(this, globalCtx);
        func_80B8F254(this);
    } else {
        Actor* temp_a0 = this->actor.child;

        if (temp_a0 != NULL) {
            if (func_800B84D0(temp_a0, globalCtx)) {
                func_800B86C8(this, globalCtx, this);
                func_80B9083C(this, globalCtx);
                func_80B8F254(this);
                return;
            }
        }

        if (ABS_ALT(temp_v1) < 0x4000) {
            Actor* temp_a0_2;

            func_800B8614(&this->actor, globalCtx, 120.0f);
            temp_a0_2 = this->actor.child;
            if ((temp_a0_2 != NULL) && (CURRENT_DAY != 2)) {
                s16 temp_v1_3 = temp_a0_2->shape.rot.y - temp_a0_2->yawTowardsPlayer;

                if (ABS_ALT(temp_v1_3) < 0x4000) {
                    func_800B8614(temp_a0_2, globalCtx, 120.0f);
                }
            }
        }
    }
}


void func_80B8F254(EnMaYto *this) {
    if ((CURRENT_DAY == 1) || ((gSaveContext.weekEventReg[0x16] & 1) != 0)) {
        func_80B90E50(this, 1);
    } else {
        func_80B90E50(this, 2);
    }
    this->unk_31E = 0;
    this->actionFunc = func_80B8F2D8;
}

void func_80B8F2D8(EnMaYto *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 4:
            func_80B8F360(this, globalCtx);
            break;

        case 5:
            func_80B8F400(this, globalCtx);
            break;

        case 6:
            if (func_80147624(globalCtx) != 0) {
                func_80B8F074(this);
            }
            break;

        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;
    }
}

void func_80B8F360(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            func_8019F208();
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x3399U, &this->actor);
            this->textId = 0x3399;
        }
        else {
            func_8019F230();
            func_801518B0(globalCtx, 0x3398U, &this->actor);
            this->textId = 0x3398;
        }
    }
}


void func_80B8F400(EnMaYto *this, GlobalContext *globalCtx) {
    u32 temp_t7;

    if (func_80147624(globalCtx) != 0) {
        switch (this->textId) {
        case 0x3398:
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x3399U, &this->actor);
            this->textId = 0x3399;
            break;

        case 0x3399:
            EnMaYto_SetFaceExpression(this, (u16)3, (u16)1);
            func_801518B0(globalCtx, 0x339AU, &this->actor);
            this->textId = 0x339A;
            break;

        case 0x339A:
            this->unk_31E = 1;
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x339BU, &this->actor);
            this->textId = 0x339B;
            break;

        case 0x339B:
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E50(this, 0);
            func_80B90E84(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x339CU, &this->actor);
            this->textId = 0x339C;
            break;

        case 0x339C:
            this->unk_31E = 1;
            func_800B86C8(this, globalCtx, this);
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)2);
            func_801518B0(globalCtx, 0x339DU, &this->actor);
            this->textId = 0x339D;
            break;

        case 0x339D:
            func_80B90E50(this, 1);
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E84(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x339EU, &this->actor);
            this->textId = 0x339E;
            func_80151BB4(globalCtx, 6U);
            func_80151BB4(globalCtx, 5U);
            break;

        case 0x339F:
            this->unk_31E = 0;
            func_801518B0(globalCtx, 0x33A0U, &this->actor);
            this->textId = 0x33A0;
            break;

        case 0x33A0:
            func_801518B0(globalCtx, 0x33A1U, &this->actor);
            this->textId = 0x33A1;
            break;

        case 0x33A1:
            func_80B90E50(this, 1);
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E84(this, (u16)0, (u16)2);
            func_801518B0(globalCtx, 0x33A2U, &this->actor);
            this->textId = 0x33A2;
            break;

        case 0x33A2:
            this->unk_31E = 1;
            func_800B86C8(this, globalCtx, this);
            EnMaYto_SetFaceExpression(this, (u16)4, (u16)3);
            func_801518B0(globalCtx, 0x33A3U, &this->actor);
            this->textId = 0x33A3;
            break;

        case 0x33A3:
            this->unk_31E = 0;
            EnMaYto_SetFaceExpression(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x33A4U, &this->actor);
            this->textId = 0x33A4;
            func_80151BB4(globalCtx, 6U);
            func_80151BB4(globalCtx, 5U);
            break;

        case 0x33A5:
            func_801518B0(globalCtx, 0x33A6U, &this->actor);
            this->textId = 0x33A6;
            func_80151BB4(globalCtx, 6U);
            break;

        case 0x33A7:
            func_801518B0(globalCtx, 0x33A8U, &this->actor);
            this->textId = 0x33A8;
            func_80151BB4(globalCtx, 6U);
            break;
        }
    }
}

void func_80B8F744(EnMaYto *this) {
    if ((CURRENT_DAY == 1) || ((gSaveContext.weekEventReg[0x16] & 1) != 0)) {
        func_80B90C08(this, 0xD);
        func_80B90E50(this, 0);
        this->unk_31E = 0;
    } else {
        this->unk_320 = 0;
        func_80B90C08(this, 9);
        func_80B90E50(this, 2);
        this->unk_31E = 2;
    }
    func_80B90EF0(this);
    this->actionFunc = func_80B8F7F4;
}



void func_80B8F7F4(EnMaYto *this, GlobalContext *globalCtx) {
    s16 temp_v1 = this->actor.shape.rot.y + 0x471C;

    temp_v1 -= this->actor.yawTowardsPlayer;
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B90A78(this, globalCtx);
        func_80B8F918(this);
    } else {
        Actor *temp_a0 = this->actor.child;
        if (temp_a0 != NULL) {
            if (func_800B84D0(temp_a0, globalCtx)) {
                func_800B86C8(this, globalCtx, this);
                func_80B90A78(this, globalCtx);
                func_80B8F918(this);
                return;
            }
        }

        if ((!(gSaveContext.weekEventReg[0x16] & 1)) || (ABS_ALT(temp_v1) < 0x2000)) {
            Actor *temp_a0_2;

            func_800B8614(&this->actor, globalCtx, 100.0f);
            temp_a0_2 = this->actor.child;
            if (temp_a0_2 != NULL) {
                func_800B8614(temp_a0_2, globalCtx, 100.0f);
            }
        }
    }
}

void func_80B8F918(EnMaYto *this) {
    if ((CURRENT_DAY == 1) || ((gSaveContext.weekEventReg[0x16] & 1))) {
        func_80B90E50(this, 1);
    } else {
        func_80B90E50(this, 2);
    }
    this->actionFunc = func_80B8F998;
}

void func_80B8F998(EnMaYto *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 5:
            func_80B8FA14(this, globalCtx);
            break;

        case 6:
            if (func_80147624(globalCtx) != 0) {
                this->unk_31E = 0;
                func_80B8F744(this);
            }
            break;

        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
    }
}

/*
void func_80B8FA14(EnMaYto *this, GlobalContext *globalCtx) {
    u32 temp_t7;

    if (func_80147624(globalCtx) != 0) {
        temp_t7 = this->textId - 0x33A9;
        if (temp_t7 < 0x23U) {
            goto **(&jtbl_D_80B916E4 + (temp_t7 * 4));
        case 0:
            func_80B90E50(this, 0);
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E84(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x33AAU, &this->actor);
            this->textId = 0x33AA;
            return;
        case 1:
            func_800B86C8(this, globalCtx, this);
            this->unk_31E = 1;
            func_801518B0(globalCtx, 0x33ABU, &this->actor);
            this->textId = 0x33AB;
            return;
        case 2:
            func_80B90E50(this, 1);
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E84(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x33ACU, &this->actor);
            this->textId = 0x33AC;
            return;
        case 3:
            this->unk_31E = 0;
            func_800B86C8(this, globalCtx, this);
            func_801518B0(globalCtx, 0x33ADU, &this->actor);
            this->textId = 0x33AD;
            func_80151BB4(globalCtx, 6U);
            func_80151BB4(globalCtx, 5U);
            return;
        case 5:
            func_80B90E50(this, 1);
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E84(this, (u16)4, (u16)2);
            func_801518B0(globalCtx, 0x33AFU, &this->actor);
            this->textId = 0x33AF;
            return;
        case 6:
            this->unk_31E = 1;
            func_800B86C8(this, globalCtx, this);
            EnMaYto_SetFaceExpression(this, (u16)4, (u16)2);
            func_801518B0(globalCtx, 0x33B0U, &this->actor);
            this->textId = 0x33B0;
            func_80151BB4(globalCtx, 6U);
            func_80151BB4(globalCtx, 5U);
            return;
        case 8:
            this->unk_31E = 2;
            EnMaYto_SetFaceExpression(this, (u16)5, (u16)3);
            func_801518B0(globalCtx, 0x33B2U, &this->actor);
            this->textId = 0x33B2;
            func_80151BB4(globalCtx, 6U);
            return;
        case 29:
            func_800B86C8(this, globalCtx, this->actor.child);
            this->unk_31E = 0;
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x33C7U, &this->actor);
            this->textId = 0x33C7;
            return;
        case 30:
            func_800B86C8(this, globalCtx, this);
            this->unk_31E = 1;
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x33C8U, &this->actor);
            this->textId = 0x33C8;
            return;
        case 31:
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E50(this, 1);
            func_80B90E84(this, (u16)0, (u16)2);
            func_801518B0(globalCtx, 0x33C9U, &this->actor);
            this->textId = 0x33C9;
            return;
        case 32:
            func_800B86C8(this, globalCtx, this);
            this->unk_31E = 1;
            EnMaYto_SetFaceExpression(this, (u16)3, (u16)1);
            func_801518B0(globalCtx, 0x33CAU, &this->actor);
            this->textId = 0x33CA;
            return;
        case 33:
            this->unk_31E = 1;
            func_801518B0(globalCtx, 0x33CBU, &this->actor);
            this->textId = 0x33CB;
            return;
        case 34:
            func_800B86C8(this, globalCtx, this->actor.child);
            func_80B90E50(this, 1);
            func_80B90E84(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x33CCU, &this->actor);
            this->textId = 0x33CC;
            func_80151BB4(globalCtx, 6U);
            func_80151BB4(globalCtx, 5U);
        }
    }
default:
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FA14.asm")


void func_80B8FE04(EnMaYto *this) {
    if (gSaveContext.weekEventReg[0x34] & 1) {
        EnMaYto_SetFaceExpression(this, 3, 1);
    } else {
        func_801A3098(9);
        EnMaYto_SetFaceExpression(this, 5, 2);
    }
    this->actionFunc = func_80B8FE74;
}


// problematic
void func_80B8FE74(EnMaYto *this, GlobalContext *globalCtx) {
    this->actor.flags = this->actor.flags | 0x10000;
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actor.flags &= ~0x10000;
        if ((gSaveContext.weekEventReg[0x34] & 1) != 0) {
            func_801518B0(globalCtx, 0x33C1U, (Actor *) this);
            this->textId = 0x33C1;
        } else {
            EnMaYto_SetFaceExpression(this, (u16)5, (u16)2);
            func_801518B0(globalCtx, 0x33C0U, (Actor *) this);
            this->textId = 0x33C0;
            gSaveContext.weekEventReg[0xE] = (u8) (gSaveContext.weekEventReg[0xE] | 1);
            this->unk_310 = 4;
            func_80B904D0(this);
            func_80151BB4(globalCtx, 6U);
            return;
        }
        func_80B8FF80(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 200.0f);
    }
}


void func_80B8FF80(EnMaYto *this) {
    this->actionFunc = func_80B8FF94;
}

void func_80B8FF94(EnMaYto *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
            break;

        case 5:
            func_80B9000C(this, globalCtx);
            break;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, (u16)5, (u16)0x71C, 0xB6);
}


void func_80B9000C(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        switch (this->textId) {
            case 0x33C1:
                EnMaYto_SetFaceExpression(this, (u16)3, (u16)1);
                func_801518B0(globalCtx, 0x33C2U, &this->actor);
                this->textId = 0x33C2;
                break;

            case 0x33C2:
                func_801477B4(globalCtx);
                func_80B900AC(this);
                func_80B900C0(this, globalCtx);
                break;
        }
    }
}

void func_80B900AC(EnMaYto *this) {
    this->actionFunc = func_80B900C0;
}


void func_80B900C0(EnMaYto *this, GlobalContext *globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        func_80B90170(this);
        return;
    } else if (gSaveContext.inventory.items[gItemSlots[0x3C]] == 0x3C) {
        func_800B8A1C(&this->actor, globalCtx, 7, 500.0f, 100.0f);
        this->unk_310 = 2;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x82, 500.0f, 100.0f);
        this->unk_310 = 1;
    }
}

void func_80B90170(EnMaYto *this) {
    this->actionFunc = func_80B90184;
}


void func_80B90184(EnMaYto *this, GlobalContext *globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->unk_310 == 1) {
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x33C3U, &this->actor);
            this->textId = 0x33C3;
            gSaveContext.weekEventReg[0xE] |= 1;
            this->unk_310 = 3;
            func_80151BB4(globalCtx, 0x20U);
            func_80151BB4(globalCtx, 0x1FU);
            func_80151BB4(globalCtx, 6U);
            func_80B904D0(this);
        } else {
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
            func_801518B0(globalCtx, 0x33D0U, &this->actor);
            this->textId = 0x33D0;
            gSaveContext.weekEventReg[0xE] |= 1;
            this->unk_310 = 3;
            func_80151BB4(globalCtx, 6U);
            func_80B904D0(this);
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}


void func_80B902B8(EnMaYto *this) {
    this->actionFunc = func_80B902CC;
}

void func_80B902CC(EnMaYto *this, GlobalContext *globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene) != 0) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_80B90340(this);
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop((u16)0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80B90340(EnMaYto *this) {
    EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
    this->actionFunc = func_80B9037C;
}

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

void func_80B904D0(EnMaYto *this) {
    this->actionFunc = func_80B904E4;
}

void func_80B904E4(EnMaYto *this, GlobalContext *globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 6) || (func_80152498(&globalCtx->msgCtx) == 5)) {
        if ((func_80147624(globalCtx) != 0) && (func_80152498(&globalCtx->msgCtx) == 5)) {
            func_800B7298(globalCtx, &this->actor, (u8)7U);
            func_801477B4(globalCtx);
        }
    }
    if ((func_80152498(&globalCtx->msgCtx) == 0) && (globalCtx->msgCtx.unk120B1 == 0)) {
        func_80B9059C(this);
    }
}

void func_80B9059C(EnMaYto *this) {
    this->actionFunc = func_80B905B0;
}

void func_80B905B0(EnMaYto *this, GlobalContext *globalCtx) {
    if (this->unk_310 == 3) {
        globalCtx->nextEntranceIndex = 0x54D0;
    } else {
        globalCtx->nextEntranceIndex = 0x6480;
    }
    gSaveContext.unk_3F4A = (u16)0;
    globalCtx->unk18875 = 0x14;
    globalCtx->unk1887F = 0x50;
    gSaveContext.nextTransition = 3;
}

/*
void func_80B9061C(EnMaYto* this, GlobalContext* globalCtx) {
    s32 temp_hi;
    u32 temp_v0;

    temp_hi = (s32) gSaveContext.day % 5;
    if (temp_hi == 1) {
        if (func_8012403C(globalCtx) == 0) {
block_13:
            if (!func_80B91014()) {
                func_80B9109C();
                func_801518B0(globalCtx, 0x3390U, &this->actor);
                this->textId = 0x3390;
                return;
            }
            func_801518B0(globalCtx, 0x3394U, &this->actor);
            this->textId = 0x3394;
            return;
        }
        if (gSaveContext.unk20 != 4) {
            goto block_13;
        }
        temp_v0 = func_8012403C(globalCtx);
        if (temp_v0 == 2) {
            EnMaYto_SetFaceExpression(this, (u16)1, (u16)2);
            func_801518B0(globalCtx, 0x235FU, &this->actor);
            this->textId = 0x235F;
            return;
        }
        if (temp_v0 == 7) {
            func_801518B0(globalCtx, 0x235DU, &this->actor);
            this->textId = 0x235D;
            return;
        }
        if (temp_v0 == 8) {
            EnMaYto_SetFaceExpression(this, (u16)1, (u16)3);
            func_801518B0(globalCtx, 0x235EU, &this->actor);
            this->textId = 0x235E;
            return;
        }
        if (temp_v0 == 0xA) {
            func_801518B0(globalCtx, 0x2360U, &this->actor);
            this->textId = 0x2360;
            return;
        }
        func_801518B0(globalCtx, 0x2361U, &this->actor);
        this->textId = 0x2361;
        return;
    }
    if (temp_hi == 3) {
        if (func_80B90F84()) {
            EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
            func_801518B0(globalCtx, 0x33C5U, &this->actor);
            this->textId = 0x33C5;
            func_80151BB4(globalCtx, 6U);
            return;
        }
        func_80B9109C();
        EnMaYto_SetFaceExpression(this, (u16)0, (u16)3);
        func_801518B0(globalCtx, 0x33C4U, &this->actor);
        this->textId = 0x33C4;
        func_80151BB4(globalCtx, 6U);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9061C.asm")

/*
void func_80B9083C(Actor *arg0, GlobalContext *arg1) {
    s32 temp_hi;
    u32 temp_v0;
    s16 phi_t7;

    temp_hi = (s32) gSaveContext.day % 5;
    if (temp_hi != 1) {
        if (temp_hi == 2) {
            if (!func_80B91014()) {
                func_80B9109C();
                func_801518B0(arg1, 0x33A5U, arg0);
                arg0->unk322 = (u16)0x33A5;
                return;
            }
            func_801518B0(arg1, 0x33A6U, arg0);
            arg0->unk322 = (u16)0x33A6;
            func_80151BB4(arg1, 6U);
            return;
        }
        if (temp_hi != 3) {
            return;
        }
        if (func_80B91014()) {
            func_801518B0(arg1, 0x33A8U, arg0);
            arg0->unk322 = (u16)0x33A8;
            func_80151BB4(arg1, 6U);
            return;
        }
        func_80B9109C();
        func_801518B0(arg1, 0x33A7U, arg0);
        phi_t7 = (u16)0x33A7;
    } else {
        if (func_8012403C(arg1) == 0) {
block_16:
            if (!func_80B91014()) {
                func_80B9109C();
                func_801518B0(arg1, 0x3397U, arg0);
                arg0->unk322 = (u16)0x3397;
                return;
            }
            func_801518B0(arg1, 0x339FU, arg0);
            arg0->unk322 = (u16)0x339F;
            return;
        }
        if (gSaveContext.unk20 != 4) {
            goto block_16;
        }
        temp_v0 = func_8012403C(arg1);
        if (temp_v0 == 2) {
            func_801518B0(arg1, 0x235FU, arg0);
            arg0->unk322 = (u16)0x235F;
            return;
        }
        if (temp_v0 != 7) {
            if (temp_v0 == 8) {
                func_801518B0(arg1, 0x235EU, arg0);
                arg0->unk322 = (u16)0x235E;
                return;
            }
            if (temp_v0 == 0xA) {
                func_801518B0(arg1, 0x2360U, arg0);
                arg0->unk322 = (u16)0x2360;
                return;
            }
            func_801518B0(arg1, 0x2361U, arg0);
            arg0->unk322 = (u16)0x2361;
            return;
        }
        func_801518B0(arg1, 0x235DU, arg0);
        phi_t7 = (u16)0x235D;
    }
    arg0->unk322 = phi_t7;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9083C.asm")


void func_80B90A78(EnMaYto* this, GlobalContext* globalCtx) {
    s32 temp_hi;

    if ((gSaveContext.weekEventReg[0x16] & 1) != 0) {
        temp_hi = CURRENT_DAY;
        if (temp_hi == 2) {
            if (this->unk_310 == 1) {
                func_801518B0(globalCtx, 0x33AEU, &this->actor);
                this->textId = 0x33AE;
            } else {
                this->unk_310 = 1;
                func_80B9109C();
                func_801518B0(globalCtx, 0x33A9U, &this->actor);
                this->textId = 0x33A9;
            }
        }
        else if (temp_hi == 3) {
            if (this->unk_310 == 1) {
                func_801518B0(globalCtx, 0x33CBU, &this->actor);
                this->textId = 0x33CB;
            } else {
                this->unk_310 = 1;
                func_80B9109C();
                EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
                func_801518B0(globalCtx, 0x33C6U, &this->actor);
                this->textId = 0x33C6;
            }
        }
    } else {
        if (func_80B91014()) {
            this->unk_31E = 2;
            EnMaYto_SetFaceExpression(this, (u16)5, (u16)3);
            func_801518B0(globalCtx, 0x33B3U, &this->actor);
            this->textId = 0x33B3;
            func_80151BB4(globalCtx, 6U);
        }
        else {
            func_80B9109C();
            EnMaYto_SetFaceExpression(this, (u16)5, (u16)3);
            func_801518B0(globalCtx, 0x33B1U, &this->actor);
            this->textId = 0x33B1;
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

    EnMaYto_Blink(this);
}

void func_80B90D98(EnMaYto* this, GlobalContext* globalCtx) {
    if (this->actionFunc != func_80B9037C) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
}


void EnMaYto_Blink(EnMaYto *this) {
    if (this->unk_316 != 0) {
        this->eyeTexIndex = this->unk_316;
    } else if (this->blinkTimer == 0x64) {
        if (this->eyeTexIndex == 0) {
            this->blinkTimer = 0;
        } else {
            this->eyeTexIndex--;
        }
    } else {
        this->blinkTimer++;
        if (this->blinkTimer == 0x64) {
            this->eyeTexIndex = 2;
        }
    }
}



void func_80B90E50(EnMaYto *this, s16 arg1) {
    EnMaYts* romani;

    romani = (EnMaYts*)this->actor.child;
    if ((romani != NULL) && (romani->actor.id == ACTOR_EN_MA_YTS)) {
        romani->unk_32C = arg1;
    }
}

void func_80B90E84(EnMaYto *this, s16 arg1, s16 arg2) {
    EnMaYts* romani;

    romani = (EnMaYts*)this->actor.child;
    if ((romani != NULL) && (romani->actor.id == ACTOR_EN_MA_YTS)) {
        romani->overrideEyeTexIndex = arg1;
        romani->mouthTexIndex = arg2;
    }
}


void EnMaYto_SetFaceExpression(EnMaYto *this, s16 arg1, s16 mouthIndex) {
    this->unk_316 = arg1;
    this->mouthTexIndex = mouthIndex;
}

void func_80B90EF0(EnMaYto *this) {
    if (CURRENT_DAY == 1 || (gSaveContext.weekEventReg[0x16] & 1) != 0) {
        EnMaYto_SetFaceExpression(this, (u16)0, (u16)1);
        func_80B90E84(this, 0, 0);
    } else {
        EnMaYto_SetFaceExpression(this, (u16)5, (u16)2);
        func_80B90E84(this, 1, 2);
    }
}

s32 func_80B90F84(void) {
    switch (CURRENT_DAY) {
        case 1:
            if (gSaveContext.weekEventReg[0xD] & 4) {
                return true;
            }
            break;

        case 2:
            if (gSaveContext.weekEventReg[0xD] & 8) {
                return true;
            }
            break;

        case 3:
            if (gSaveContext.weekEventReg[0xD] & 0x10) {
                return true;
            }
            break;

    }
    return false;
}



s32 func_80B91014(void) {
    // Note each case doesn't have `break`s.
    switch (CURRENT_DAY) {
    case 3:
        if ((gSaveContext.weekEventReg[0xD] & 0x10) != 0) {
            return 1;
        }

    case 2:
        if ((gSaveContext.weekEventReg[0xD] & 8) != 0) {
            return 1;
        }

    case 1:
        if (gSaveContext.weekEventReg[0xD] & 4) {
            return 1;
        }
    }
    return 0;
}


void func_80B9109C(void) {
    switch (CURRENT_DAY) {
    case 1:
        gSaveContext.weekEventReg[0xD] |= 1<<2;
        break;

    case 2:
        gSaveContext.weekEventReg[0xD] |= 1<<3;
        break;

    case 3:
        gSaveContext.weekEventReg[0xD] |= 1<<4;
        break;
    }
}


void EnMaYto_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYto* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80B90D98(this, globalCtx);
    func_80B90C78(this, globalCtx);
}

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
    if (this->type == 1 && (gSaveContext.weekEventReg[0x16] & 1) != 0) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06005430);
    }
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B915C8[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B915D8[this->eyeTexIndex]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B91154, func_80B91250, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
