#include "z_en_az.h"
#include "overlays/actors/ovl_En_Twig/z_en_twig.h"
#include "overlays/actors/ovl_En_Fish/z_en_fish.h"

#define FLAGS 0x80000010

#define THIS ((EnAz*)thisx)

#define GET_PARAM1(beaver) (((beaver)->params >> 8) & 0xF)
#define GET_PARAM2(beaver) ((beaver)->params & 0xFF)

typedef struct {
    s16 unk_0;
    f32 unk_4;
} struct_80A98F94;

void EnAz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80A94A90(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
s32 func_80A95534(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
s32 func_80A9565C(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
s32 func_80A95730(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
s32 func_80A958B0(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
s32 func_80A95B34(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);
void func_80A982E0(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1);

void func_80A94A30(EnAz* this);
void func_80A94A64(EnAz* this);
void func_80A94AB8(EnAz *this, GlobalContext *globalCtx, s32 arg2);
void func_80A94B20(GlobalContext * globalCtx);
s32 func_80A94B98(EnAz *this, GlobalContext *globalCtx);
void func_80A98414(EnAz *this, GlobalContext *globalCtx);
f32 func_80A954AC(EnAz *this);

s32 func_80A98DA4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx);
void func_80A98E48(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor* thisx);
void func_80A98EFC(EnAz* this, GlobalContext* globalCtx, u16 textId, s32 arg3, s32 arg4);
void func_80A98F94(struct_80A98F94* arg0, f32 arg1, f32* arg2);


void func_80A95C5C(EnAz *this, GlobalContext *globalCtx);
void func_80A95CEC(EnAz* this, GlobalContext* globalCtx);

void func_80A95DA0(EnAz *this, GlobalContext *globalCtx);
void func_80A95E88(EnAz* this, GlobalContext* globalCtx);

void func_80A95F94(EnAz* this, GlobalContext* globalCtx);
void func_80A95FE8(EnAz* this, GlobalContext* globalCtx);

s32 func_80A9617C(EnAz* this, GlobalContext* globalCtx);
void func_80A97114(EnAz* this, GlobalContext* globalCtx);
s32 func_80A97274(EnAz* this, GlobalContext* globalCtx);
s32 func_80A973B4(EnAz* this, GlobalContext* globalCtx);
void func_80A97410(EnAz* this, GlobalContext* globalCtx);

void func_80A979DC(EnAz *this, GlobalContext *globalCtx);
void func_80A979F4(EnAz* this, GlobalContext* globalCtx);

void func_80A97A28(EnAz* this, GlobalContext* globalCtx);
void func_80A97A40(EnAz* this, GlobalContext* globalCtx);

void func_80A97A9C(EnAz* this, GlobalContext* globalCtx);
void func_80A97AB4(EnAz* this, GlobalContext* globalCtx);

void func_80A97C0C(EnAz *this, GlobalContext *globalCtx);
void func_80A97C24(EnAz* this, GlobalContext* globalCtx);
void func_80A97C4C(EnAz* this, GlobalContext* globalCtx);

void func_80A97D5C(EnAz *this, GlobalContext *globalCtx);
void func_80A97E48(EnAz* this, GlobalContext* globalCtx);

void func_80A97EAC(EnAz* this, GlobalContext* globalCtx);
void func_80A97F9C(EnAz* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Az_InitVars = {
    ACTOR_EN_AZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AZ,
    sizeof(EnAz),
    (ActorFunc)EnAz_Init,
    (ActorFunc)EnAz_Destroy,
    (ActorFunc)EnAz_Update,
    (ActorFunc)EnAz_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A99110 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 46, 0, { 0, 0, 0 } },
};

#endif

extern struct_80B8E1A8 D_80A99010[];
extern ColliderCylinderInit D_80A99110;
extern EnAz *D_80A9913C;
extern InitChainEntry D_80A99140[];
extern s16 D_80A9914C[];
extern s16 D_80A9915C[];
extern Gfx* D_80A9916C[];
extern AnimatedMaterial* D_80A99180[];
extern u8 D_80A9919C[];
extern u8 D_80A99194[];
extern struct_80124618 D_80A991A4[][9];
extern struct_80A98F94 D_80A9930C[][4];
extern Vec3f D_80A993AC[];
extern Vec3f D_80A993D0[];
extern Gfx* D_80A993F4[];
extern Gfx* D_80A99404[];
extern Vec3f D_80A99410;
extern Vec3f D_80A9941C;
extern Vec3f D_80A99428;

extern Vec3f D_80A99E80;
extern f32 D_80A99E8C;
extern f32 D_80A99E90[];

extern Gfx D_0601AD00[];
extern FlexSkeletonHeader D_06007438;
extern FlexSkeletonHeader D_06017990;
extern AnimationHeader D_0600C94C;
extern Gfx D_0601ABF0[];

void func_80A94A30(EnAz *this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.minVelocityY) {
        this->actor.velocity.y = this->actor.minVelocityY;
    }
}

void func_80A94A64(EnAz *this) {
    func_80A94A30(this);
    Actor_ApplyMovement(&this->actor);
}

s32 func_80A94A90(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    func_80A94A64((EnAz*)arg1->unk_48);
    return 0;
}

void func_80A94AB8(EnAz *this, GlobalContext *globalCtx, s32 arg2) {
    globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(arg2);
    gSaveContext.nextCutsceneIndex = 0;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 3;
    gSaveContext.nextTransition = 3;
}

void func_80A94B20(GlobalContext *globalCtx) {
    Actor *phi_s0 = NULL;
    do {
        phi_s0 = func_ActorCategoryIterateById(globalCtx, phi_s0, ACTORCAT_MISC, ACTOR_EN_TWIG);
        if (phi_s0 != NULL) {
            if ((phi_s0->params & 0xF) == 1) {
                Actor_MarkForDeath(phi_s0);
            }
            phi_s0 = phi_s0->next;
        }
    } while (phi_s0 != NULL);
}

#ifdef NON_MATCHING
s32 func_80A94B98(EnAz *this, GlobalContext *globalCtx) {
    EnTwig* pad;
    s32 sp28 = 0;
    Actor* phi_s0 = NULL;
    
    do {
        pad = (EnTwig*) func_ActorCategoryIterateById(globalCtx, phi_s0, ACTORCAT_MISC, ACTOR_EN_TWIG);
        if((pad != NULL) && ((pad->dyna.actor.params & 0xF) == 1) && !(pad->unk_16C & 1)) {
            sp28 = 1;
            break;
        }
        phi_s0 = pad->dyna.actor.next;
    } while(phi_s0 != NULL);
    return sp28;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94B98.s")
#endif

#ifdef NON_MATCHING
void EnAz_Init(Actor *thisx, GlobalContext *globalCtx2) {
    EnAz *this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s16 sp4E;
    s16 pad4C;
    s32 phi_v1;

    Actor_ProcessInitChain(thisx, D_80A99140);
    this->unk_374 = 0;
    thisx->colChkInfo.mass = 0xFF;
    thisx->targetMode = 1;
    switch (GET_PARAM1(thisx)) {
        case 0:
            phi_v1 = (gSaveContext.entranceIndex == 0x8E00) && (gSaveContext.weekEventReg[93] & 1);
            phi_v1 = !phi_v1;
            break;
        case 2:
            phi_v1 = (gSaveContext.entranceIndex != 0x8E10) || !(gSaveContext.weekEventReg[24] & 4);
            break;
        case 4:
            phi_v1 = gSaveContext.entranceIndex != 0x8E20;
            break;
        case 1:
            phi_v1 = (gSaveContext.entranceIndex == 0x8E00) && (gSaveContext.weekEventReg[93] & 1);
            phi_v1 = !phi_v1;
            break;
        case 3:
            phi_v1 = (gSaveContext.entranceIndex != 0x8E10) || (gSaveContext.weekEventReg[24] & 4);
            break;
        case 5:
            phi_v1 = gSaveContext.entranceIndex != 0x8E20;
            break;
        case 6:
            phi_v1 = (gSaveContext.entranceIndex == 0x8E00) && !(gSaveContext.weekEventReg[93] & 1);
            phi_v1 = !phi_v1;
            break;
        default:
            phi_v1 = 1;
            break;
    }
    if (phi_v1) {
        Actor_MarkForDeath(thisx);
        return;
    }
    this->unk_2F8 = D_80A9915C[GET_PARAM1(thisx)];

    if (GET_PARAM1(thisx) >= 0) {
        sp4E = D_80A9914C[GET_PARAM1(thisx)];
    } else {
        sp4E = -1;
    }
    if (this->unk_2F8 == 0) {
        this->unk_374 |= 2;
    }
    func_8013E3B8(thisx, &this->unk_3D0, 1);
    if (D_80A9913C == NULL) {
        D_80A9913C = THIS;
        this->unk_374 |= 1;
    }
    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 30.0f);
    if (this->unk_374 & 2) {
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06007438, &D_0600C94C, this->jointTable, this->morphTable, 0x18);
        Actor_SetScale(thisx, 0.012f);
    } else {
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06017990, &D_0600C94C, this->jointTable, this->morphTable, 0x18);
    }
    Collider_InitAndSetCylinder(globalCtx, &this->collider, thisx, &D_80A99110);
    if (this->unk_374 & 2) {
        this->collider.dim.radius = this->collider.dim.radius * 1.2f;
        this->collider.dim.height = this->collider.dim.height * 1.2f;
        this->collider.dim.yShift = this->collider.dim.yShift * 1.2f;
    }
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 5);
    if ((thisx->bgCheckFlags & 0x20) && (thisx->yDistToWater > 22.0f)) {
        this->unk_374 |= 0x100;
        this->unk_376 |= 0x100;
    }
    SkelAnime_ChangeAnim(&this->skelAnime, D_80A99010->animationSeg, 1.0f, SkelAnime_GetFrameCount(&D_80A99010->animationSeg->common) * Rand_ZeroOne(), SkelAnime_GetFrameCount(&D_80A99010->animationSeg->common), D_80A99010->mode, D_80A99010->transitionRate);
    this->unk_37E = 0;
    this->unk_380 = 0;
    this->unk_384 = 0;
    thisx->gravity = -1.0f;
    this->unk_376 = this->unk_374;
    func_8013E1C8(&this->skelAnime, D_80A99010, 0, &this->unk_2FC);
    this->skelAnime.animCurrentFrame = Rand_ZeroOne() * this->skelAnime.animFrameCount;

    switch(gSaveContext.entranceIndex) {
        case 0x8E00:
            if (gSaveContext.weekEventReg[93] & 1) {
                this->unk_2FA = 5;
                if (this->unk_374 & 2) {
                    this->unk_374 |= 0x20;
                    thisx->flags |= 9;
                }
            } else {
                this->unk_2FA = 0;
                thisx->flags |= 9;
                this->unk_374 |= 0x20;
            }
            func_80A94B20(globalCtx);
            if (this->unk_2FA == 5) {
                func_80A97C0C(this, globalCtx);
            } else {
                func_80A95DA0(this, globalCtx);
            }
            break;
        case 0x8E30:
            this->unk_2FA = 0;
            if (!(this->unk_374 & 2)) {
                thisx->flags |= 0x10009;
            }
            if (gSaveContext.entranceIndex == 0x8E30) {
                this->unk_2FA = 0xA;
            }
            func_80A97C0C(this, globalCtx);
            break;
        case 0x8E10:
            if (gSaveContext.weekEventReg[93] & 1) {
                if (gSaveContext.weekEventReg[24] & 4) {
                    this->unk_2FA = 8;
                } else {
                    this->unk_2FA = 6;
                }
            } else {
                if (gSaveContext.weekEventReg[24] & 4) {
                    this->unk_2FA = 3;
                } else {
                    this->unk_2FA = 1;
                }
            }
            if (this->unk_374 & 1) {
                func_8013DC40(globalCtx->setupPathList, GET_PARAM2(thisx), globalCtx->setupPathList[GET_PARAM2(thisx)].count - 1, &D_80A99E80);
            }
            if (gSaveContext.weekEventReg[24] & 4) {
                if (this->unk_374 & 2) {
                    func_80A97D5C(this, globalCtx);
                } else {
                    func_80A979DC(this, globalCtx);
                }
            } else if (this->unk_374 & 2) {
                func_80A979DC(this, globalCtx);
            } else {
                func_80A97D5C(this, globalCtx);
            }
            break;
        case 0x8E20:
            if (gSaveContext.weekEventReg[93] & 1) {
                if (gSaveContext.weekEventReg[24] & 4) {
                    this->unk_2FA = 9;
                } else {
                    this->unk_2FA = 7;
                }
            } else {
                if (gSaveContext.weekEventReg[24] & 4) {
                    this->unk_2FA = 4;
                } else {
                    this->unk_2FA = 2;
                }
            }
            if (this->unk_2FA == 2) {
                if (!(this->unk_374 & 2)) {
                    this->unk_374 |= 0x20;
                    thisx->flags |= 0x10009;
                    this->actionFunc = func_80A97C24;
                } else {
                    thisx->flags |= 9;
                    func_80A95C5C(this, globalCtx);
                }
            } else {
                if (this->unk_374 & 2) {
                    this->unk_374 |= 0x20;
                    thisx->flags |= 0x10009;
                } else {
                    thisx->flags |= 9;
                }
                this->actionFunc = func_80A97C24;
            }
            break;
    }
    if (sp4E >= 0) {
        this->unk_388 = NULL;
        do {
            this->unk_388 = (EnAz*) func_ActorCategoryIterateById(globalCtx, &this->unk_388->actor, ACTORCAT_NPC, ACTOR_EN_AZ);
            if (this->unk_388 != NULL) {
                if (sp4E == GET_PARAM1(&this->unk_388->actor)) {
                    break;
                }
                this->unk_388 = (EnAz*)this->unk_388->actor.next;
            }
        } while(this->unk_388 != NULL);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/EnAz_Init.s")
#endif

void EnAz_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    EnAz* this = THIS;

    if (gSaveContext.entranceIndex != 0x8E10) {
        gSaveContext.unk_3DD0[4] = 5;
    }
    Collider_DestroyCylinder(globalCtx2, &this->collider);
}

f32 func_80A954AC(EnAz *this) {
    EnDno_ActorUnkStruct* pad = &this->unk_300;
    Vec3f sp28;
    Vec3f sp1C;
    
    sp28.x = pad->unk_20.x - this->actor.world.pos.x;
    sp28.y = pad->unk_20.y - this->actor.world.pos.y;
    sp28.z = pad->unk_20.z - this->actor.world.pos.z;
    sp1C.x = pad->unk_20.x - pad->unk_38.x;
    sp1C.y = pad->unk_20.y - pad->unk_38.y;
    sp1C.z = pad->unk_20.z - pad->unk_38.z;
    return Math3D_Parallel(&sp28, &sp1C);
}

s32 func_80A95534(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz *temp_s0 = arg1->unk_48;
    s32 sp28 = 0;

    temp_s0->actor.world.rot.x = 0;
    Math_SmoothStepToS(&temp_s0->unk_39E, temp_s0->actor.world.rot.x, 2, 0x71C, 0);
    Math_SmoothStepToS(&temp_s0->actor.shape, 0, 2, 0x71C, 0);
    Math_SmoothStepToS(&temp_s0->actor.world.rot.y, arg1->unk_56, 1, 0xE38, 0);
    Math_SmoothStepToS(&temp_s0->actor.shape.rot.y, temp_s0->actor.world.rot.y, 2, 0x71C, 0);
    temp_s0->actor.gravity = -1.0f;
    temp_s0->unk_36C = 1.5f;
    if (arg1->unk_10 == arg1->unk_18) {
        if (arg1->unk_4C < temp_s0->unk_36C) {
            temp_s0->unk_36C = arg1->unk_4C;
        }
    }
    Math_SmoothStepToF(&temp_s0->actor.speedXZ, temp_s0->unk_36C, 0.8f, 2.0f, 0.0f);
    arg1->unk_64 = func_8013E054;
    if (arg1->unk_4C <= temp_s0->actor.speedXZ) {
        sp28 = 1;
    }
    return sp28;
}

s32 func_80A9565C(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz* temp_s0 = (EnAz*) arg1->unk_48;
    s32 sp20 = 0;
    f32 temp_f0;

    temp_s0->actor.gravity = -1.0f;
    arg1->unk_64 = func_80A94A90;
    temp_s0->unk_374 |= 0x2000;
    temp_f0 = func_80A954AC(temp_s0);
    if ((arg1->unk_4C < SQ(temp_s0->actor.speedXZ)) || (temp_f0 <= 0.0f)) {
        sp20 = 1;
    } else {
        temp_s0->unk_39E = temp_s0->actor.world.rot.x = Math_Atan2S(-temp_s0->actor.velocity.y, Math_CosS(-temp_s0->actor.world.rot.x) * temp_s0->actor.speedXZ);
    }
    return sp20;
}

s32 func_80A95730(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz *temp_s0 = (EnAz*)arg1->unk_48;
    s32 sp48 = 0;
    f32 temp_f0;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;

    temp_s0->actor.gravity = 0.0f;
    temp_f0 = func_80A954AC(temp_s0);
    if ((arg1->unk_4C < SQ(temp_s0->actor.speedXZ)) || (temp_f0 <= 0.0f)) {
        sp48 = 1;
    } else {
        sp40 = SQ(temp_s0->actor.speedXZ) / arg1->unk_50;
        sp34 = ABS(arg1->unk_54 - temp_s0->actor.world.rot.x);
        
        sp3C = (s32) (sp34 * sp40) + 0xAAA;
        sp34 = ABS(arg1->unk_56 - temp_s0->actor.world.rot.y);

        Math_SmoothStepToS(&temp_s0->actor.world.rot.x, arg1->unk_54, 1, sp3C, 0);
        sp38 = (s32) (sp34 * sp40) + 0xAAA;
        Math_SmoothStepToS(&temp_s0->actor.world.rot.y, arg1->unk_56, 1, sp38, 0);

        Math_SmoothStepToS(&temp_s0->unk_39E, temp_s0->actor.world.rot.x, 2, sp3C, 0);
        Math_SmoothStepToS(&temp_s0->actor.shape.rot.y, temp_s0->actor.world.rot.y, 2, sp38, 0);
    }
    arg1->unk_64 = func_8013E07C;
    return sp48;
}

s32 func_80A958B0(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz *temp_s0 = arg1->unk_48;
    s32 sp50 = 0;
    f32 pad;
    f32 phi_f0;
    f32 temp1;
    f32 pad2;
    f32 sp3C;
    s32 sp2C;
    s32 sp28;
    s32 sp30;

    temp_s0->actor.gravity = 0.0f;
    pad2 = D_80A99E8C;
    pad = D_80A99E90[temp_s0->unk_2F8];
    
    if (pad <= pad2) {
        phi_f0 = (temp_s0->unk_374 & 2) ? 480.0f : 240.0f;

        if (temp_s0->actor.xzDistToPlayer < phi_f0) {
            Math_SmoothStepToF(&temp_s0->unk_36C, 12.0f, 0.8f, 0.5f, 0.01f);
        } else {
            Math_SmoothStepToF(&temp_s0->unk_36C, 6.0f, 0.8f, 0.5f, 0.01f);
        }
    } else {
        Math_SmoothStepToF(&temp_s0->unk_36C, 26.0f, 0.5f, 1.0f, 0.01f);
    }
    Math_SmoothStepToF(&temp_s0->actor.speedXZ, temp_s0->unk_36C, 0.8f, 2.0f, 0.0f);
    temp1 = func_80A954AC(temp_s0);
    if ((arg1->unk_4C < SQ(temp_s0->actor.speedXZ)) || (temp1 <= 0.0f)) {
        sp50 = 1;
    } else {
        sp3C = SQ(temp_s0->actor.speedXZ) / arg1->unk_50;
        sp30 = ABS(arg1->unk_54 - temp_s0->actor.world.rot.x);
        sp2C = (s32) (sp30 * sp3C) + 0xAAA;
        sp30 = ABS(arg1->unk_56 - temp_s0->actor.world.rot.y);
        
        
        Math_SmoothStepToS(&temp_s0->actor.world.rot.x, arg1->unk_54, 1, sp2C, 0);
        sp28 = (s32) (sp30 * sp3C) + 0xAAA;
        Math_SmoothStepToS(&temp_s0->actor.world.rot.y, arg1->unk_56, 1, sp28, 0);
        Math_SmoothStepToS(&temp_s0->unk_39E, temp_s0->actor.world.rot.x, 2, sp2C, 0);
        Math_SmoothStepToS(&temp_s0->actor.shape.rot.y, temp_s0->actor.world.rot.y, 2, sp28, 0);
    }
    arg1->unk_64 = func_8013E07C;
    return sp50;
}

s32 func_80A95B34(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz *temp_s0 = arg1->unk_48;
    s32 phi_v0;

    if (temp_s0->unk_374 & 0x100) {
        if (!(temp_s0->unk_374 & 8)) {
            if (temp_s0->unk_374 & 2) {
                func_8013E1C8(&temp_s0->skelAnime, D_80A99010, 8, &temp_s0->unk_2FC);
            } else {
                func_8013E1C8(&temp_s0->skelAnime, D_80A99010, 2, &temp_s0->unk_2FC);
            }
            temp_s0->unk_374 |= 8;
        }
        if (temp_s0->unk_2FA == 0) {
            phi_v0 = func_80A95730(globalCtx, arg1);
        } else {
            phi_v0 = func_80A958B0(globalCtx, arg1);
        }
    } else if (temp_s0->actor.bgCheckFlags & 1) {
        if (temp_s0->unk_374 & 8) {
            func_8013E1C8(&temp_s0->skelAnime, D_80A99010, 1, &temp_s0->unk_2FC);
            temp_s0->unk_374 &= ~8;
        }
        phi_v0 = func_80A95534(globalCtx, arg1);
    } else {
        phi_v0 = func_80A9565C(globalCtx, arg1);
    }
    return phi_v0;
}

void func_80A95C5C(EnAz *this, GlobalContext *globalCtx) {
    this->actor.draw = NULL;
    this->actor.world.pos.y = this->actor.home.pos.y + 120.0f;
    this->actor.gravity = -1.0f;
    func_8013E1C8(&this->skelAnime, D_80A99010, 0, &this->unk_2FC);
    this->actor.flags &= ~0x9;
    this->actor.bgCheckFlags &= ~0x21;
    this->unk_3C0 = 0;
    this->actionFunc = func_80A95CEC;
}

void func_80A95CEC(EnAz *this, GlobalContext *globalCtx) {
    if (this->unk_374 & 0x8000) {
        if (!(this->actor.bgCheckFlags & 1)) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actor.draw = EnAz_Draw;
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            func_800B9010(&this->actor, 0x20A0);
        } else {
            if (this->actor.bgCheckFlags & 2) {
                Audio_PlayActorSound2(&this->actor, 0x387A);
            }
            if (func_8013E2D4(&this->actor, 0x7C, this->unk_3D0, 1)) {
                func_80A97C0C(this, globalCtx);
            }
        }
    }
}

void func_80A95DA0(EnAz *this, GlobalContext *globalCtx) {
    EnDno_ActorUnkStruct *sp40 = &this->unk_300;

    func_8013DCE0(globalCtx, &this->actor.world.pos, &this->actor, sp40, globalCtx->setupPathList, this->actor.params & 0xFF, 0, 0, 1, 1);
    this->unk_36C = 4.0f;
    this->actor.speedXZ = 4.0f;
    this->actor.gravity = 0.0f;
    func_8013E1C8(&this->skelAnime, D_80A99010, 2, &this->unk_2FC);
    this->actor.flags |= 9;
    this->actor.bgCheckFlags &= ~0x21;
    this->unk_374 |= 0x1000;
    Math_Vec3f_Copy(&this->actor.world.pos, &sp40->unk_20);
    this->actionFunc = func_80A95E88;
}

void func_80A95E88(EnAz *this, GlobalContext *globalCtx) {
    func_8013DE04(globalCtx, &this->unk_300, func_80A982E0, func_80A95B34, func_8013E054, func_8013E0A4);
    if (this->actor.yDistToWater > 8.0f) {
        if (this->unk_374 & 2){
            if ((this->skelAnime.animCurrentFrame < this->skelAnime.animPlaybackSpeed) && (this->skelAnime.animCurrentFrame >= 0.0f)) {
                Audio_PlayActorSound2(&this->actor, 0x2909);
            }
        } else {
            func_800B9010(&this->actor, 0x2108);
        }
    }
    if (!(this->unk_374 & 0x2000)) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
    this->unk_374 &= ~0x2000;
    if (this->actor.isTargeted) {
        func_80A95F94(this, globalCtx);
    }
}

void func_80A95F94(EnAz *this, GlobalContext *globalCtx) {
    func_800BE33C(&this->actor.world.pos, &this->actor.home.pos, &this->actor.world.rot, 0);
    this->unk_39E = 0;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actionFunc = func_80A95FE8;
}

void func_80A95FE8(EnAz *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (ActorCutscene_GetCanPlayNext(this->unk_3D0) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_3D0, &this->actor);
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_3D0);
    }
    if (Actor_DistanceToPoint(&this->actor, &this->actor.home.pos) > 20.0f) {
        func_800B9010(&this->actor, 0x2108);
        func_800BE33C( &this->actor.world.pos, &this->actor.home.pos, &this->actor.world.rot, 0);
        Math_SmoothStepToS(&this->actor.shape.rot.x, this->actor.world.rot.x, 3, 0xE38, 0x38E);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0xE38, 0x38E);
        this->actor.shape.rot.z = 0;
        Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    } else {
        func_8013E1C8(&this->skelAnime, D_80A99010, 0, &this->unk_2FC);
        this->unk_374 &= ~0x1000;
        this->actor.gravity = -1.0f;
        this->actor.speedXZ = 0.0f;
        Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 3, 0x1000, 0x100);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1038, 0x100);
        if (this->actor.bgCheckFlags & 1) {
            this->actor.shape.rot.x = 0;
            this->actor.gravity = 0.0f;
            func_80A97C0C(this, globalCtx);
            ActorCutscene_Stop(this->unk_3D0);
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A9617C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A973B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97410.s")

void func_80A979DC(EnAz *this, GlobalContext *globalCtx) {
    this->actionFunc = func_80A979F4;
}

void func_80A979F4(EnAz *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80A97A28(EnAz *this, GlobalContext *globalCtx) {
    this->actionFunc = func_80A97A40;
}

void func_80A97A40(EnAz *this, GlobalContext *globalCtx) {
    if (func_8013E2D4(&this->actor, 0, -1, 0)) {
        globalCtx->msgCtx.unk11F22 = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        func_80A97A9C(this, globalCtx);
    }
}

void func_80A97A9C(EnAz *this, GlobalContext *globalCtx) {
    this->actionFunc = func_80A97AB4;
}

void func_80A97AB4(EnAz *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            func_801518B0(globalCtx, 0x10D7, NULL);
            return;
        case 4:
        case 5:
        case 6:
            if (func_80147624(globalCtx) != 0) {
                switch(globalCtx->msgCtx.unk11F04) {
                    case 0x10D7:
                        func_80151938(globalCtx, 0x10D8);
                        break;
                    case 0x10D8:
                        if (globalCtx->msgCtx.choiceIndex == 0) {
                            func_8019F208();
                            globalCtx->msgCtx.unk11F22 = 0x44;
                            func_800FD750(0x25);
                            func_80A94AB8(this, globalCtx, 1);
                            func_80A979DC(this, globalCtx);
                        } else {
                            func_8019F230();
                            if (gSaveContext.weekEventReg[24] & 4) {
                                gSaveContext.weekEventReg[24] &= (u8)~4;
                            }
                            func_80151938(globalCtx, 0x10D9);
                        }
                        break;
                    case 0x10D9:
                        func_80A94AB8(this, globalCtx, 0);
                        func_80A979DC(this, globalCtx);
                        break;
                }
            }
        case 1:
        case 2:
            break;
    }
}

void func_80A97C0C(EnAz *this, GlobalContext *globalCtx) {
    this->actionFunc = func_80A97C4C;
}

void func_80A97C24(EnAz *this, GlobalContext *globalCtx) {
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actionFunc = func_80A97C4C;
}

void func_80A97C4C(EnAz *this, GlobalContext *globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (this->unk_2FC == 0xB)) {
        func_8013E1C8(&this->skelAnime, D_80A99010, 0, &this->unk_2FC);
    }
    func_80A97410(this, globalCtx);
    if ((this->unk_2FA == 1) || (this->unk_2FA == 3) || (this->unk_2FA == 6) || (this->unk_2FA == 8)) {
        gSaveContext.weekEventReg[24] &= (u8)~1;
        func_800FD750(0x25);
        globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(1);
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 0x50;
        gSaveContext.nextTransition = 3;
        func_80A979DC(this, globalCtx);
    } else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void func_80A97D5C(EnAz *this, GlobalContext *globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 |= 0x20;
    func_80112AFC(globalCtx);
    gSaveContext.minigameScore = (this->unk_374 & 2) ? 25 : 20;
    globalCtx->interfaceCtx.unk_280 = 1;
    if ((this->unk_2FA == 1) || (this->unk_2FA == 3)) {
        func_8010E9F0(4, 0x78);
    } else if (gSaveContext.weekEventReg[25] & 1) {
        func_8010E9F0(4, 0x64);
    } else {
        func_8010E9F0(4, 0x6E);
    }
    this->actionFunc = func_80A97E48;
}

void func_80A97E48(EnAz *this, GlobalContext *globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->interfaceCtx.unk_280 >= 8) {
        player->stateFlags1 &= ~0x20;
        func_80A97EAC(this, globalCtx);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80A97EAC(EnAz *this, GlobalContext *globalCtx) {
    func_8013DCE0(globalCtx, &this->actor.world.pos, &this->actor, &this->unk_300, globalCtx->setupPathList, this->actor.params & 0xFF, 0, 0, 1, 0);
    this->unk_36C = 8.0f;
    this->actor.speedXZ = 8.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 6.0f;
    func_8013E1C8(&this->skelAnime, D_80A99010, 2, &this->unk_2FC);
    this->actor.flags |= 0x8000000;
    this->actor.flags &= ~9;
    this->actor.bgCheckFlags &= ~0x21;
    this->unk_374 |= 0x1000;
    this->unk_3C2 = 0;
    this->unk_3C4 = 0;
    this->actionFunc = func_80A97F9C;
}

void func_80A97F9C(EnAz *this, GlobalContext *globalCtx) {
    Player *player = GET_PLAYER(globalCtx);

    D_80A99E8C = Math3D_XZDistanceSquared(player->actor.world.pos.x, player->actor.world.pos.z, D_80A99E80.x, D_80A99E80.z);
    if (Math3D_XZDistanceSquared(this->actor.world.pos.x, this->actor.world.pos.z, D_80A99E80.x, D_80A99E80.z) >= SQ(1000.0f)) {
        this->unk_374 |= 0x1000;
    }
    if (!(this->unk_300.unk_1C & 0x20)) {
        func_8013DE04(globalCtx, &this->unk_300, func_80A982E0, func_80A95B34, func_8013E054, func_8013E0A4);
    }
    if (!(this->unk_374 & 0x10) && func_800C9B90(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        this->unk_374 |= 0x10;
    }
    if (func_800C9B90(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId)) {
        if (func_80A94B98(this, globalCtx) != 0) {
            gSaveContext.weekEventReg[24] &= (u8)~1;
        } else {
            gSaveContext.weekEventReg[24] |= 1;
        }
        gSaveContext.unk_3DD0[4] = 5;
        this->unk_374 &= ~0x10;
        globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(2);
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 3;
        gSaveContext.nextTransition = 3;
        this->actor.speedXZ = 0.0f;
        func_80A979DC(this, globalCtx);
        return;
    }
    if (gSaveContext.unk_3DE0[4] == 0) {
        gSaveContext.unk_3DD0[4] = 5;
        this->unk_374 |= 0x4000;
        func_80A97A28(this, globalCtx);
    }
    if (this->unk_374 & 0x100) {
        if (this->actor.flags & 0x40) {
            func_80A98414(this, globalCtx);
        }
        if ((DECR(this->unk_37A) == 0) && (this->actor.flags & 0x40)) {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 0.0f, 20.0f, 20.0f, 0.35f);
            this->unk_37A = (Rand_ZeroOne() * 70.0f) + 10.0f;
        }
    }
    if (this->actor.yDistToWater > 8.0f) {
        if (this->unk_374 & 2) {
            if ((this->skelAnime.animCurrentFrame < this->skelAnime.animPlaybackSpeed) && (this->skelAnime.animCurrentFrame >= 0.0f)) {
                Audio_PlayActorSound2(&this->actor, 0x2909);
            }
        } else {
            func_800B9010(&this->actor, 0x2108);
        }
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80A982E0(GlobalContext *globalCtx, EnDno_ActorUnkStruct *arg1) {
    EnAz *temp_v1 = arg1->unk_48;
    Vec3f sp28;

    arg1->unk_20.x = arg1->unk_08[arg1->unk_10].x;
    if ((temp_v1->actor.bgCheckFlags & 1) != 0) {
        arg1->unk_20.y = arg1->unk_08[arg1->unk_10].y;
    } else {
        arg1->unk_20.y = arg1->unk_08[arg1->unk_10].y - temp_v1->unk_3A4;
    }
    arg1->unk_20.z = arg1->unk_08[arg1->unk_10].z;
    sp28.x = arg1->unk_20.x - arg1->unk_44->x;
    sp28.y = arg1->unk_20.y - arg1->unk_44->y;
    sp28.z = arg1->unk_20.z - arg1->unk_44->z;
    arg1->unk_4C = Math3D_XZLengthSquared(sp28.x, sp28.z);
    arg1->unk_50 = Math3D_LengthSquared(&sp28);
    arg1->unk_56 = Math_FAtan2F(sp28.z, sp28.x);
    arg1->unk_54 = Math_FAtan2F(sqrtf(arg1->unk_4C), -sp28.y);
    arg1->unk_58 = 0;
}

void func_80A98414(EnAz *this, GlobalContext *globalCtx) {
    Actor *itemAction = globalCtx->actorCtx.actorList[ACTORCAT_ITEMACTION].first;

    while(itemAction != NULL) {
        if(itemAction->id == ACTOR_EN_FISH) {
            EnFish* fish = (EnFish*)itemAction;

            if((fish->actor.params < 0) && (fish->actor.room == this->actor.room) && (Math3D_DistanceSquared(&this->actor.world.pos, &fish->actor.world.pos) < SQ(200.0f))) {
                fish->unk_276 = 0x14;
                fish->unk_274 = Actor_YawBetweenActors(&fish->actor, &this->actor);
            }
        }
        itemAction = itemAction->next;
    }
}

void EnAz_Update(Actor *thisx, GlobalContext *globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnAz* this = THIS;

    this->unk_374 &= ~0x100;
    if ((this->actor.bgCheckFlags & 0x20) && (this->actor.yDistToWater > 22.0f)) {
        if (!(this->unk_376 & 0x100)) {
            this->unk_374 |= 0x200;
        }
        this->unk_374 |= 0x100;
    } else if (this->unk_376 & 0x100) {
        this->unk_374 |= 0x400;
    }
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 40.0f);
    if (this->unk_374 & 0x200) {
        Audio_PlayActorSound2(&this->actor, 0x2889);
    }
    if (this->unk_374 & 0x400) {
        Audio_PlayActorSound2(&this->actor, 0x288A);
    }
    this->unk_37E++;
    if (this->unk_37E >= 4) {
        this->unk_37E = 0;
    }
    this->unk_380++;
    if (this->unk_380 >= 3) {
        this->unk_380 = 0;
    }
    this->unk_384--;
    if (this->unk_384 < 0) {
        this->unk_384 = 2;
    }
    this->unk_39C++;
    if (this->unk_39C >= 0x10) {
        this->unk_39C = 0;
    }
    if ((this->unk_374 & 0x1000) == 0) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 5U);
    } else {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 0x400U);
        this->unk_374 &= ~0x1000;
    }
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    this->unk_376 = this->unk_374;
    this->unk_374 &= ~0x600;
    
    if (GET_ACTIVE_CAM(globalCtx)->flags2 & 0x100) {
        this->unk_374 |= 0x800;
    } else {
        this->unk_374 &= ~0x800;
    }
}

void EnAz_Draw(Actor *thisx, GlobalContext *globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnAz* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x19);
    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_374 & 2) {
        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80A98DA4, func_80A98E48, &this->actor);
    } else {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 8, Lib_SegmentedToVirtual(D_80A993F4[this->unk_37E]));
        gSPSegment(POLY_OPA_DISP++, 9, Lib_SegmentedToVirtual(D_80A99404[this->unk_380]));
        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80A98DA4, func_80A98E48, &this->actor);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    OPEN_DISPS(globalCtx->state.gfxCtx);
    if ((this->actor.yDistToWater >= 28.0f) && (this->actor.speedXZ > 0.5f)) {
        SysMatrix_InsertTranslation(this->unk_3B4.x, this->unk_3B4.y, this->unk_3B4.z, 0);
        Matrix_RotateY(this->actor.shape.rot.y, 1);
        SysMatrix_InsertXRotation_s(this->actor.shape.rot.x, 1);
        SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, 1);
        SysMatrix_InsertXRotation_s(this->unk_39E, 1);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        func_8012C2DC(globalCtx->state.gfxCtx);
        if (this->unk_374 & 2) {
            s32 i;
            Vec3f sp98;
            f32 sp94;
            
            SysMatrix_InsertTranslation(0.0f, 0.0f, -2000.0f, 1);
            for(i = 0; i < 5; i++) {
                SysMatrix_StatePush();
                func_80A98F94(D_80A9930C[i], this->unk_39C, &sp94);
                AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(D_80A99180[i]));
                SysMatrix_InsertTranslation(0.0f, sp94 * 100.0f, i * -930.0f, 1);
                Matrix_Scale(1.1f, 0.95f, 1.0f, 1);
                func_80124618(D_80A991A4[i], this->unk_39C, &sp98);
                Matrix_Scale(sp98.x, sp98.y, sp98.z, 1);
                if (this->unk_374 & 0x800) {
                    gSPSegment(POLY_XLU_DISP++, 9, Gfx_PrimColor(globalCtx->state.gfxCtx, 0x80, 0xFF, 0xFF, 0xFF, D_80A99194[i]));
                } else {
                    gSPSegment(POLY_XLU_DISP++, 9, Gfx_PrimColor(globalCtx->state.gfxCtx, 0x80, 0xFF, 0xFF, 0xFF, D_80A9919C[i]));
                }
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
                gSPDisplayList(POLY_XLU_DISP++, D_80A9916C[i]);
                SysMatrix_StatePop();
            }
        } else {
            SysMatrix_StatePush();
            SysMatrix_InsertTranslation(0.0f, 2000.0f, -2000.0f, 1);
            SysMatrix_InsertZRotation_s(D_80A993D0[this->unk_384].z * 182.04445f, 1);
            Matrix_Scale(D_80A993AC[this->unk_384].x, D_80A993AC[this->unk_384].y, 0.0f, 1);
            if (this->unk_374 & 0x800) {
                gSPSegment(POLY_XLU_DISP++, 8, Gfx_PrimColor(globalCtx->state.gfxCtx, 0x80, 0xFF, 0xFF, 0xFF, 0xFF)); 
            } else {
                gSPSegment(POLY_XLU_DISP++, 8, Gfx_PrimColor(globalCtx->state.gfxCtx, 0x80, 0xFF, 0xFF, 0xFF, 0x55)); 
            }
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
            gSPDisplayList(POLY_XLU_DISP++, D_0601ABF0);
            SysMatrix_StatePop();
            SysMatrix_InsertTranslation(0.0f, 2000.0f, -2100.0f, 1);
            SysMatrix_InsertZRotation_s(D_80A993D0[this->unk_384].z * 182.04445f, 1);
            Matrix_Scale(D_80A993D0[this->unk_384].x, D_80A993D0[this->unk_384].y, 0.0f, 1);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
            gSPDisplayList(POLY_XLU_DISP++, D_0601AD00);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80A98DA4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnAz* this = THIS;

    if ((limbIndex == 0) && (globalCtx->gameplayFrames & 1)) {
        *dList = NULL;
    }
    if (limbIndex == 0) {
        rot->x = rot->x;
        rot->y = rot->y;
        rot->z = rot->z;
    }
    if (limbIndex == 3) {
        rot->y -= this->unk_39E;
    } else {
        // this space intentionally left blank
    }
    if (limbIndex == 5) {
        rot->x += this->unk_3D4;
        rot->y -= this->unk_3D8;
    }
    return false;
}

void func_80A98E48(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnAz* this = THIS;

    if (limbIndex == 3) {
        SysMatrix_MultiplyVector3fByState(&D_80A99410, &this->unk_3A8);
        Math_SmoothStepToF(&this->unk_3A4, this->unk_3A8.y - this->actor.world.pos.y, 0.8f, 10.0f, 0.01f);
        if (this->unk_374 & 2) {
            SysMatrix_MultiplyVector3fByState(&D_80A9941C, &this->unk_3B4);
        } else {
            SysMatrix_MultiplyVector3fByState(&D_80A99428, &this->unk_3B4);
        }
    }
}

void func_80A98EFC(EnAz *this, GlobalContext *globalCtx, u16 textId, s32 arg3, s32 arg4) {
    EnAz* temp_s0 = this->unk_388;

    func_800B86C8(&this->actor, globalCtx, &temp_s0->actor);
    if (arg3 >= 0) {
        func_8013E1C8(&this->skelAnime, D_80A99010, arg3, &this->unk_2FC);
    }
    this->actor.textId = 0;
    temp_s0->actor.textId = textId;
    temp_s0->unk_378 = 5;
    if ((arg4 >= 0) && (arg4 != temp_s0->unk_2FC)) {
        func_8013E1C8(&temp_s0->skelAnime, D_80A99010, arg4, &temp_s0->unk_2FC);
    }
    this->unk_378 = 0;
}

#ifdef NON_MATCHING
void func_80A98F94(struct_80A98F94 *arg0, f32 arg1, f32 *arg2) {
    f32 temp_f0;
    f32 weight;

    do {
        arg0++;
        temp_f0 = arg0->unk_0;
    } while(temp_f0 < arg1);

    weight = ((arg1 - arg0[-1].unk_0) / (temp_f0 - arg0[-1].unk_0));
    *arg2 = (arg0[-1].unk_4 + weight * (arg0->unk_4 - arg0[-1].unk_4))*0.01f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98F94.s")
#endif