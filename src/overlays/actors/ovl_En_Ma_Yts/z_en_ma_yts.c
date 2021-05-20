#include "z_en_ma_yts.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMaYts_UpdateEyes(EnMaYts* this);
// func_80B8D0BC
void func_80B8D12C(EnMaYts* this, GlobalContext* globalCtx);

void func_80B8D698(EnMaYts* this);
void func_80B8D6AC(EnMaYts* this, GlobalContext* globalCtx);
void func_80B8D6BC(EnMaYts* this);
void func_80B8D6F8(EnMaYts* this, GlobalContext* globalCtx);
void func_80B8D95C(EnMaYts* this);
void func_80B8D970(EnMaYts* this, GlobalContext* globalCtx);
void func_80B8D9E4(EnMaYts* this);
void func_80B8DA28(EnMaYts* this, GlobalContext* globalCtx);
void func_80B8DBB8(EnMaYts* this, GlobalContext* globalCtx);

void func_80B8DD88(EnMaYts* this, s16 arg1, s16 arg2);

void func_80B8E0BC(Actor *thisx, GlobalContext *globalCtx);

/*
const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw,
};
*/

// blinking probably. DECR does weird things, probably bad types in the actor's struct
void EnMaYts_UpdateEyes(EnMaYts *this) {
    if (this->unk_328 != 0) {
        this->eyeTexIndex = this->unk_328;
    }
    else if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 3) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}


/*
glabel D_80B8E170
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
glabel D_80B8E19C
0x00000000
0x00000000
0xFF000000
*/

struct struct_80B8E1A8{
    /* 0x00 */ AnimationHeader* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x0C */ f32 unk_0C;
};

extern AnimationHeader D_06009E58;
extern AnimationHeader D_06009E58;
extern AnimationHeader D_06018948;
extern AnimationHeader D_06018948;
extern AnimationHeader D_0601B76C;
extern AnimationHeader D_0601B76C;
extern AnimationHeader D_06007328;
extern AnimationHeader D_06007328;
extern AnimationHeader D_06014088;
extern AnimationHeader D_06014088;
extern AnimationHeader D_06002A8C;
extern AnimationHeader D_06002A8C;
extern AnimationHeader D_06015B7C;
extern AnimationHeader D_06015B7C;
extern AnimationHeader D_06007D98;
extern AnimationHeader D_06007D98;
extern AnimationHeader D_0600852C;
extern AnimationHeader D_0600852C;
extern AnimationHeader D_06008F6C;
extern AnimationHeader D_06008F6C;
extern AnimationHeader D_060180DC;
extern AnimationHeader D_060180DC;

extern struct struct_80B8E1A8 D_80B8E1A8[];
/*
struct struct_80B8E1A8 D_80B8E1A8[] = {
    { &D_06009E58, 0x3F800000, 0x00, 0.0f },
    { &D_06009E58, 0x3F800000, 0x00, -6.0f },
    { &D_06018948, 0x3F800000, 0x02, 0.0f },
    { &D_06018948, 0x3F800000, 0x02, -6.0f },
    { &D_0601B76C, 0x3F800000, 0x00, 0.0f },
    { &D_0601B76C, 0x3F800000, 0x00, -6.0f },
    { &D_06007328, 0x3F800000, 0x00, 0.0f },
    { &D_06007328, 0x3F800000, 0x00, -6.0f },
    { &D_06014088, 0x3F800000, 0x00, 0.0f },
    { &D_06014088, 0x3F800000, 0x00, -6.0f },
    { &D_06002A8C, 0x3F800000, 0x00, 0.0f },
    { &D_06002A8C, 0x3F800000, 0x00, -6.0f },
    { &D_06015B7C, 0x3F800000, 0x00, 0.0f },
    { &D_06015B7C, 0x3F800000, 0x00, -6.0f },
    { &D_06007D98, 0x3F800000, 0x00, 0.0f },
    { &D_06007D98, 0x3F800000, 0x00, -6.0f },
    { &D_0600852C, 0x3F800000, 0x00, 0.0f },
    { &D_0600852C, 0x3F800000, 0x00, -6.0f },
    { &D_06008F6C, 0x3F800000, 0x00, 0.0f },
    { &D_06008F6C, 0x3F800000, 0x00, -6.0f },
    { &D_060180DC, 0x3F800000, 0x02, 0.0f },
    { &D_060180DC, 0x3F800000, 0x02, -6.0f },
};
*/

/*
glabel D_80B8E308
0x060127C8
0x06012BC8
0x06012FC8
0x060133C8
*/

/*
glabel D_80B8E318
0x0600FFC8
0x060107C8
0x06010FC8
0x060117C8
0x06011FC8
*/
/*
glabel D_80B8E32C
0x00630000
*/

void func_80B8D0BC(EnMaYts* this, s32 index) {
    SkelAnime_ChangeAnim(&this->skelAnime, D_80B8E1A8[index].unk_00, 1.0f, 0.0f, 
        SkelAnime_GetFrameCount(&D_80B8E1A8[index].unk_00->genericHeader), 
        D_80B8E1A8[index].unk_08, D_80B8E1A8[index].unk_0C);
}

void func_80B8D12C(EnMaYts *this, GlobalContext *globalCtx) {
    ActorPlayer* player = PLAYER;
    s16 phi_a3 = this->unk_32C == 2 ? 1 : 0;

    if ((this->unk_32C == 0) || (this->actor.parent == NULL)) {
        this->unk_1F0 = player->base.world.pos;
        this->unk_1F0.y -= -10.0f;
    } else {
        Math_Vec3f_StepTo(&this->unk_1F0, &this->actor.parent->world.pos, 8.0f);
        this->unk_1F0.y -= -10.0f;
    }

    func_800BD888(&this->actor, &this->unk_1D8, 0, phi_a3);
}


void func_80B8D1E8(EnMaYts *this, GlobalContext *globalCtx) {
    switch (this->type)
    {
    case 0:
        this->actor.targetMode = 0;
        func_80B8D0BC(this, 0);
        break;

    case 1:
        this->actor.targetMode = 6;
        if ((((s32) gSaveContext.perm.day % 5) == 1) || ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
            func_80B8D0BC(this, 14);
        }
        else {
            func_80B8D0BC(this, 18);
        }
        break;

    case 2:
        this->actor.targetMode = 0;
        this->actor.draw = func_80B8E0BC;
        func_80B8D0BC(this, 0);
        break;

    case 3:
        this->actor.targetMode = 0;
        func_80B8D0BC(this, 0);
        break;

    default:
        func_80B8D0BC(this, 0);
        break;
    }
}


#ifdef NON_EQUIVALENT
s32 func_80B8D2D8(EnMaYts *this, GlobalContext *globalCtx) {
    s16 temp_v0;
    s32 temp_hi;

    switch (this->type) {
        case 3:
            break;

        case 1:
            switch ((s32) gSaveContext.perm.day % 5) {
                default:
                    break;

                case 3:
                    if ((gSaveContext.perm.weekEventReg[0x16] & 1) == 0) {
                        return 0;
                    }
                    break;

                case 2:
                    if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                        return 0;
                    }
                    break;

                case 1:
                    break;



            }
            break;

        case 0:
            if (!(gSaveContext.perm.weekEventReg[0x16] & 1)) {
                return 0;
            }
            if (((s32) gSaveContext.perm.time >= 0xD555) && (((s32) gSaveContext.perm.day % 5) == 3)) {
                return 0;
            }
            break;

        case 2:
            if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                return 0;
            }
            break;

    }

    return 1;

    /*
    temp_v0 = this->type;
    if (temp_v0 != 0) {
        if (temp_v0 != 1) {
            if (temp_v0 != 2) {
                if (temp_v0 != 3) {

                }
            } else if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                return 0;
            }
        } else {
            temp_hi = (s32) gSaveContext.perm.day % 5;
            if (temp_hi != 1) {
                if (temp_hi != 2) {
                    if (temp_hi != 3) {

                    } else if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
                        return 0;
                    }
                } else if ((gSaveContext.perm.weekEventReg[0x16] & 1) == 0) {
                    return 0;
                }
            }
        }
    } else {
        if ((gSaveContext.perm.weekEventReg[0x16] & 1) == 0) {
            return 0;
        }
        if (((s32) gSaveContext.perm.time >= 0xD555) && (((s32) gSaveContext.perm.day % 5) == 3)) {
            return 0;
        }
    }
    */
    return 1;
}
#else
s32 func_80B8D2D8(EnMaYts *this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D2D8.asm")
#endif

extern ColliderCylinderInit D_80B8E170;
extern CollisionCheckInfoInit2 D_80B8E19C;

extern SkeletonHeader D_06013928;

void EnMaYts_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;
    s32 pad;

    this->type = (this->actor.params & 0xF000) >> 0xC;
    if (func_80B8D2D8(this, globalCtx) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, NULL, &this->unk_204, &this->unk_294, 0x17);
    func_80B8D1E8(this, globalCtx);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B8E170);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B8E19C);

    if (this->type == 2) {
        this->collider.dim.radius = 0x28;
    }

    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_1D8 = 0;
    this->unk_200 = 0;
    this->blinkTimer = 0;

    if (this->type == 3) {
        this->unk_336 = 1;
    } else {
        this->unk_336 = 0;
    }

    if (((u16)1 == ((s32) gSaveContext.perm.day % 5)) || ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0)) {
        this->unk_328 = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 0;
    } else {
        this->unk_328 = 1;
        this->eyeTexIndex = 1;
        this->mouthTexIndex = 2;
        this->unk_32C = 2;
    }

    if (this->type == 3) {
        this->unk_328 = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 2;
        func_80B8D9E4(this);
    }
    else if (
        (((s32) gSaveContext.perm.day % 5) == 2) && 
        (1 == (s32)gSaveContext.perm.isNight) && 
        ((gSaveContext.perm.weekEventReg[0x16] & 1))) {
        func_80B8D6BC(this);
    }
    else {
        func_80B8D698(this);
    }
}

void EnMaYts_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}


// EnMaYts_SetupDoNothing
void func_80B8D698(EnMaYts *this) {
    this->actionFunc = func_80B8D6AC;
}

// EnMaYts_DoNothing
void func_80B8D6AC(EnMaYts* this, GlobalContext* globalCtx) {
}

void func_80B8D6BC(EnMaYts *this) {
    func_80B8DD88(this, 0, 0);
    this->actionFunc = func_80B8D6F8;
}

void func_80B8D6F8(EnMaYts *this, GlobalContext *globalCtx) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        if (gSaveContext.perm.unk20 != 4) {
            if ((gSaveContext.perm.weekEventReg[0x41] & 0x80) == 0) {
                gSaveContext.perm.weekEventReg[0x41] |= 0x80;
                func_80B8DD88(this, (u16)0, (u16)0);
                func_801518B0(globalCtx, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                func_80B8DD88(this, (u16)4, (u16)3);
                func_801518B0(globalCtx, 0x3362U, &this->actor);
                this->textId = 0x3362;
                func_80151BB4((s32) globalCtx, 5U);
            }
        } else if (func_8012403C(globalCtx) != 0) {
            if ((gSaveContext.perm.weekEventReg[0x41] & 0x40) == 0) {
                gSaveContext.perm.weekEventReg[0x41] |= 0x40;
                func_80B8DD88(this, (u16)0, (u16)0);
                func_801518B0(globalCtx, 0x3363U, &this->actor);
                this->textId = 0x3363;
            } else {
                func_80B8DD88(this, (u16)4, (u16)2);
                func_801518B0(globalCtx, 0x3366U, &this->actor);
                this->textId = 0x3366;
                func_80151BB4((s32) globalCtx, 5U);
            }
        } else if ((gSaveContext.perm.weekEventReg[0x15] & 0x20) == 0) {
            func_80B8DD88(this, (u16)0, (u16)0);
            func_801518B0(globalCtx, 0x3367U, &this->actor);
            this->textId = 0x3367;
        } else {
            if ((gSaveContext.perm.weekEventReg[0x41] & 0x20) == 0) {
                gSaveContext.perm.weekEventReg[0x41] |= 0x20;
                func_80B8DD88(this, (u16)4, (u16)2);
                func_801518B0(globalCtx, 0x3369U, &this->actor);
                this->textId = 0x3369;
            } else {
                func_80B8DD88(this, (u16)0, (u16)0);
                func_801518B0(globalCtx, 0x336CU, &this->actor);
                this->textId = 0x336C;
                func_80151BB4((s32) globalCtx, 5U);
            }
        }
        func_80B8D95C(this);
    }
    else if (ABS_ALT(sp26) < 0x4000) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void func_80B8D95C(EnMaYts *this) {
    this->actionFunc = func_80B8D970;
}


void func_80B8D970(EnMaYts *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
    case 5:
        func_80B8DBB8(this, globalCtx);
        break;

    case 6:
        if (func_80147624(globalCtx) != 0) {
            func_80B8D6BC(this);
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


void func_80B8D9E4(EnMaYts *this) {
    this->actor.flags |= 0x10;
    func_80B8DD88(this, 0, 0);
    this->actionFunc = func_80B8DA28;
}


extern u16 D_80B8E32C;
#ifdef NON_MATCHING
void func_80B8DA28(EnMaYts *this, GlobalContext *globalCtx) {
    //u32 sp24;
    //s32 temp_t6;
    //u16 temp_a1;
    //u16 temp_v1_2;
    u32 temp_v0;
    //void *temp_a0;
    CsCmdActorAction *temp_v1;

    if (func_800EE29C(globalCtx, 0x78U) != 0) {
        temp_v0 = func_800EE200(globalCtx, 0x78U);
        //temp_t6 = temp_v0 * 4;
        //sp24 = temp_v0;
        //temp_a0 = globalCtx + temp_t6;
        temp_v1 = globalCtx->csCtx.actorActions[temp_v0];
        if (globalCtx->csCtx.frames == temp_v1->startFrame) {
            //temp_a1 = temp_v1->unk0;
            if (temp_v1->unk0 != D_80B8E32C) {
                D_80B8E32C = temp_v1->unk0;
                this->unk_334 = 0;
                switch (globalCtx->csCtx.actorActions[temp_v0]->unk0) {
                    case 1:
                        this->unk_336 = 1;
                        func_80B8D0BC(this, 0);
                        break;

                    case 2:
                        this->unk_336 = 0;
                        func_80B8D0BC(this, 2);
                        break;

                    case 3:
                        this->unk_336 = 1;
                        func_80B8D0BC(this, 0xC);
                        break;

                    case 4:
                        this->unk_336 = 1;
                        func_80B8D0BC(this, 0x14);
                        break;

                    //default:
                        //break;
                }
            }
        }
        func_800EDF24(this, globalCtx, temp_v0, globalCtx);
        if ((D_80B8E32C == 2) && (this->unk_334 == 0) && (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount))) {
            this->unk_334++;
            func_80B8D0BC(this, 5);
        }
    } else {
        D_80B8E32C = 0x63;
        this->unk_336 = 1;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DA28.asm")
#endif

void func_80B8DBB8(EnMaYts *this, GlobalContext *globalCtx) {

    if (func_80147624(globalCtx) != 0) {
        switch (this->textId) {
        case 0x335F:
            func_80B8DD88(this, (u16)0, (u16)2);
            func_801518B0(globalCtx, 0x3360U, &this->actor);
            this->textId = 0x3360;
            break;

        case 0x3360:
            func_80B8DD88(this, (u16)4, (u16)3);
            func_801518B0(globalCtx, 0x3361U, &this->actor);
            this->textId = 0x3361;
            func_80151BB4(globalCtx, 5U);
            break;

        case 0x3363:
            func_80B8DD88(this, (u16)1, (u16)1);
            func_801518B0(globalCtx, 0x3364U, &this->actor);
            this->textId = 0x3364;
            break;

        case 0x3364:
            func_80B8DD88(this, (u16)4, (u16)2);
            func_801518B0(globalCtx, 0x3365U, &this->actor);
            this->textId = 0x3365;
            func_80151BB4(globalCtx, 5U);
            break;

        case 0x3367:
            func_80B8DD88(this, (u16)4, (u16)3);
            func_801518B0(globalCtx, 0x3368U, &this->actor);
            this->textId = 0x3368;
            func_80151BB4(globalCtx, 5U);
            break;

        case 0x3369:
            func_80B8DD88(this, (u16)0, (u16)0);
            func_801518B0(globalCtx, 0x336AU, &this->actor);
            this->textId = 0x336A;
            break;

        case 0x336A:
            func_80B8DD88(this, (u16)3, (u16)3);
            func_801518B0(globalCtx, 0x336BU, &this->actor);
            this->textId = 0x336B;
            func_80151BB4(globalCtx, 5U);
            break;

        default:
            break;
        }
    }
}


void func_80B8DD88(EnMaYts* this, s16 arg1, s16 arg2) {
    this->unk_328 = arg1;
    this->mouthTexIndex = arg2;
    if (this->unk_328 == 0) {
        this->eyeTexIndex = 0;
    }
}

void EnMaYts_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;
    ColliderCylinder *collider;

    this->actionFunc(this, globalCtx);
    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &collider->base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnMaYts_UpdateEyes(this);
    func_80B8D12C(this, globalCtx);
}

extern AnimationHeader D_06009E58;
extern AnimationHeader D_06007D98;

// OverrideLimbDraw
s32 func_80B8DE44(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnMaYts* this = THIS;
    Vec3s sp4;

    if (limbIndex == 14) {
        sp4 = this->unk_1E0;
        rot->x = rot->x + sp4.y;
        if ((this->skelAnime.animCurrentSeg == &D_06009E58) || (this->skelAnime.animCurrentSeg == &D_06007D98)) {
            rot->z = rot->z + sp4.x;
        }
    } else if (limbIndex == 13) {
        sp4 = this->unk_1E6;
        rot->x = rot->x + sp4.y;
        rot->z = rot->z + sp4.x;
    }
    return 0;
}

//extern Gfx D_060003B0[];
extern UNK_TYPE D_060003B0;

// PostLimbDraw
void func_80B8DF18(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == 14) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
    else if ((limbIndex == 19) && (this->unk_336 == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, &D_060003B0);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

extern void* D_80B8E308[]; // mouthTextures
extern void* D_80B8E318[]; // eyeTextures

void EnMaYts_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnMaYts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_80B8E308[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80B8E318[this->eyeTexIndex]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, func_80B8DE44, func_80B8DF18, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}


extern Gfx D_060043A0[];

// Alternative draw function
void func_80B8E0BC(Actor *thisx, GlobalContext *globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_060043A0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
