#include "z_en_suttari.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#define FLAGS 0x00000019

#define THIS ((EnSuttari*)thisx)

void EnSuttari_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BAB490(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAC6E8(EnSuttari* this, GlobalContext* globalCtx);
void func_80BACA14(EnSuttari* this, GlobalContext* globalCtx);
void func_80BACEE0(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD004(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD5F8(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD7F8(EnSuttari* this, GlobalContext* globalCtx);
void func_80BABA90(EnSuttari* this, s32 arg1, u8 arg2);
void func_80BAB434(EnSuttari* this);
void func_80BACBB0(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAAB78(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADA9C(EnSuttari* this, GlobalContext* globalCtx);
s32 func_80BABF64(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct);
void func_80BAC2FC(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADDB4(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAB1A0(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD130(EnSuttari* this, GlobalContext* globalCtx);
Actor* func_80BAA848(GlobalContext* globalCtx, s16 actorId);
s16 func_80BAB698(Path* path, s32 idx, Vec3f* pos, f32* dist);
s32 func_80BAB758(EnSuttari* this, Path* path, s32 arg2);
s32 func_80BAA904(EnSuttari* this, GlobalContext* globalCtx);
void func_80BACD2C(EnSuttari* this, GlobalContext* globalCtx);
void func_80BACE4C(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADD0C(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAA9B4(EnSuttari* this);
s32 func_80BABDD8(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct);
s32 func_80BABC48(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct);
void func_80BADA08(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD2B4(EnSuttari* this, GlobalContext* globalCtx);
s32 func_80BAC220(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADE14(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADE8C(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAAFDC(EnSuttari* this, GlobalContext* globalCtx);
void func_80BADF3C(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAAA94(EnSuttari* this);
void func_80BAD230(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAB374(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAB4F0(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAA8D0(void);
void func_80BAA6D0(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAD380(EnSuttari* this, GlobalContext* globalCtx);
void func_80BAAF1C(EnSuttari* this);
void func_80BAA88C(GlobalContext* globalCtx, u16 arg1);
void func_80BABB90(EnSuttari* this, s32 arg1);
s32 func_80BAB8F4(EnSuttari* this, Path* path, s32 arg2);
s32 func_80BAE250(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80BAE3C4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80BAE524(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx);
s32 func_80BABFD4(EnSuttari* this, GlobalContext* globalCtx);

extern FlexSkeletonHeader D_0600C240;
extern AnimationHeader D_0600071C;
extern AnimationHeader D_060128F4;
extern AnimationHeader D_06011F84;
extern AnimationHeader D_06012E84;
extern AnimationHeader D_0601139C;
extern AnimationHeader D_06011C38;
extern AnimationHeader D_06010BDC;
extern Gfx D_0600AF90[];
extern Gfx D_06013380[];

const ActorInit En_Suttari_InitVars = {
    ACTOR_EN_SUTTARI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnSuttari),
    (ActorFunc)EnSuttari_Init,
    (ActorFunc)EnSuttari_Destroy,
    (ActorFunc)EnSuttari_Update,
    (ActorFunc)EnSuttari_Draw,
};

static ActorAnimationEntry D_80BAE6D0[] = {
    { &D_0600071C, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &D_060128F4, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &D_06011F84, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &D_06012E84, 1.0f, 0.0f, 0.0f, 0, -6.0f },
    { &D_0601139C, 1.0f, 0.0f, 0.0f, 0, 0.0f }, { &D_0600071C, 2.0f, 0.0f, 0.0f, 0, 0.0f },
    { &D_06011F84, 2.0f, 0.0f, 0.0f, 0, 0.0f }, { &D_06011C38, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &D_06010BDC, 1.0f, 0.0f, 0.0f, 0, 0.0f },
};

static ColliderCylinderInit D_80BAE7A8 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80BAE7D4 = {
    0, 18, 64, 0, MASS_IMMOVABLE,
};

static DamageTable D_80BAE7E0 = {
    0x01, 0x01, 0x01, 0xE1, 0xE1, 0xE1, 0x01, 0xE1, 0xF1, 0xF1, 0x01, 0xE1, 0xE1, 0xE1, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xF1, 0xF1, 0xE1, 0x01, 0x01, 0x01, 0x01, 0x01, 0xE1,
};

static s16 D_80BAE800[] = {
    0xFA0, 4, 1, 3, 0x1770, 4, 1, 6, 0xFA0, 4, 1, 3, 0x1770, 4, 1, 6,
};

static UNK_TYPE D_80BAE820[] = {
    0xC00027C,  0x210877,   0xA006D31,  0x2000000, 0x19250200, 0x19001E19, 0x2010F01, 0x140D0201, 0x14012D01,
    0x50E0114,  0x12D0E0E,  0x10F0114,  0x70E0019, 0x1E060E,   0x19,       0xD0A000D, 0x3D020019, 0x1E3102,
    0x1E002D,   0x2502002D, 0x1001902,  0x100010F, 0xD02010F,  0x1140105,  0xE010F01, 0x14090E01, 0x10F0B,
    0xE002D01,  0x20E00,    0x1E002D0A, 0xE001900, 0x1E080505, 0xC000125,  0xA006E20, 0x2120000,  0x14140200,
    0x14001E08, 0xF001E03,  0x4000405,  0xE001400, 0x1E0F0E12, 0x1403,     0x50C0003, 0x270A0013, 0x22021200,
    0x13001602, 0x13001319, 0xD021319,  0x105,     0xE131900,  0x10400,    0x50E1200, 0x13000C05, 0x5000000,
};

static s32 D_80BAE8F8[] = {
    -1, -1, -1, -1, -1, -1, 1, 2, 0, 3, 1, 2, 0, 0, 3, 0,
};

void func_80BAA6D0(EnSuttari* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    if (this->unk1E4 & 0x40) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->actor.colChkInfo.damageEffect == 0xF) {
                this->unk1E4 |= 0x100;
                this->unk1E4 &= ~0x40;
                func_800BBA88(globalCtx, &this->actor);
            } else if (this->actor.colChkInfo.damageEffect == 0xE) {
                this->unk1E4 |= 0x200;
                this->unk1E4 &= ~0x40;
            }
        }
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if ((this->unk1E4 & 1) && (this->actionFunc != func_80BADE14)) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 35.0f, 30.0f, 30.0f, 5);
    } else {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 35.0f, 30.0f, 30.0f, 4);
    }
}

Actor* func_80BAA848(GlobalContext* globalCtx, s16 actorId) {
    Actor* actor = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;

    while (actor != NULL) {
        if (actor->id == actorId) {
            return actor;
        }
        actor = actor->next;
    }
    return NULL;
}

void func_80BAA88C(GlobalContext* globalCtx, u16 arg1) {
    globalCtx->nextEntranceIndex = arg1;
    globalCtx->unk_1887F = 0x40;
    gSaveContext.nextTransition = 0x40;
    globalCtx->sceneLoadFlag = 0x14;
}

void func_80BAA8D0(void) {
    u32* unk_14 = &gSaveContext.unk_14;
    u16 time = gSaveContext.time;

    gSaveContext.time = (u16)REG(15) + time;
    time = gSaveContext.time;
    gSaveContext.time = (u16)*unk_14 + time;
}

s32 func_80BAA904(EnSuttari* this, GlobalContext* globalCtx) {
    Vec3f sp2C;
    Vec3s sp24;

    sp2C.x = (Math_SinS(this->actor.world.rot.y) * 50.0f) + this->actor.world.pos.x;
    sp2C.y = this->actor.world.pos.y + 100.0f;
    sp2C.z = (Math_CosS(this->actor.world.rot.y) * 50.0f) + this->actor.world.pos.z;
    if (func_800C4000(globalCtx, &globalCtx->colCtx, &sp24, &sp2C) > -500.0f) {
        return 0;
    }
    return 1;
}

void func_80BAA9B4(EnSuttari* this) {
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    switch (this->unk1E8) {
        case 0x1454:
        case 0x1455:
        case 0x1456:
        case 0x1457:
        case 0x1458:
        case 0x1459:
        case 0x145A:
        case 0x145B:
            if ((this->unk450 != 8) && (curFrame == frameCount)) {
                this->unk450 = 8;
                func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            }
            break;
        default:
            if ((this->unk450 != 1) && (curFrame == frameCount)) {
                this->unk450 = 1;
                func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            }
    }
}

void func_80BAAA94(EnSuttari* this) {
    switch (this->unk1E8) {
        case 0x29E5:
            this->unk450 = 1;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            break;
        case 0x29E9:
            this->enFsn->flags |= ENFSN_ANGRY;
            break;
        case 0x29EA:
            this->enFsn->flags |= ENFSN_CALM_DOWN;
            break;
        case 0x29EB:
            this->enFsn->flags |= ENFSN_OFFER_FINAL_PRICE;
            break;
        case 0x29EC:
            this->unk450 = 7;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            break;
        case 0x29ED:
            this->unk450 = 1;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            break;
    }
}

void func_80BAAB78(EnSuttari* this, GlobalContext* globalCtx) {
    if (this->unk1E4 & 4) {
        switch (this->unk1E8) {
            case 0:
                this->unk1E4 |= 0x20;
                this->unk45A = 0;
                this->unk1E8 = 0x29E5;
                break;
            case 0x29E5:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 1;
                this->unk1E8 = 0x29E6;
                break;
            case 0x29E6:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 0;
                this->unk1E8 = 0x29E7;
                break;
            case 0x29E7:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 1;
                this->unk1E8 = 0x29E8;
                break;
            case 0x29E8:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 0;
                this->unk1E8 = 0x29E9;
                break;
            case 0x29E9:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 1;
                this->unk1E8 = 0x29EA;
                break;
            case 0x29EA:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 0;
                this->unk1E8 = 0x29EB;
                break;
            case 0x29EB:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 1;
                this->unk1E8 = 0x29EC;
                break;
            case 0x29EC:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk45A = 0;
                this->unk1E8 = 0x29ED;
                break;
            case 0x29ED:
                ActorCutscene_Stop(this->unk456[this->unk45A]);
                this->unk1E4 |= 0x400;
                this->unk45A = 1;
                this->unk1E8 = 0x29EE;
                break;
        }
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk456[this->unk45A]);
        this->actionFunc = func_80BADD0C;
    } else if (this->unk1E4 & 1) {
        switch (this->unk1E8) {
            case 0:
                if (gSaveContext.weekEventReg[0x51] & 1) {
                    this->unk1E8 = 0x1455;
                    ((EnElf*)PLAYER->naviActor)->unk264 |= 8;
                    this->unk1E6 |= 1;
                } else {
                    this->unk1E8 = 0x1450;
                }
                break;
            case 0x1450:
                this->unk1E8 = 0x1451;
                break;
            case 0x1451:
                if (this->unk1E4 & 0x800) {
                    this->unk1E4 &= ~0x800;
                    this->unk1E8 = 0x1453;
                } else {
                    this->unk1E4 |= 0x400;
                    this->unk1E8 = 0x1452;
                    gSaveContext.weekEventReg[0x51] |= 1;
                }
                break;
            case 0x1453:
                this->unk1E4 |= 0x400;
                gSaveContext.weekEventReg[0x51] |= 1;
                ((EnElf*)PLAYER->naviActor)->unk264 |= 8;
                this->unk1E6 |= 1;
                this->unk1E8 = 0x1454;
                break;
            case 0x1455:
                this->unk1E8 = 0x1456;
                break;
            case 0x1456:
                this->unk1E8 = 0x1457;
                break;
            case 0x1457:
                this->unk1E8 = 0x1458;
                break;
            case 0x1458:
                this->unk1E8 = 0x1459;
                break;
            case 0x1459:
                this->unk1E8 = 0x145A;
                break;
            case 0x145A:
                this->unk1E4 |= 0x400;
                this->unk1E8 = 0x145B;
                break;
        }
    }
    func_801518B0(globalCtx, this->unk1E8, &this->actor);
}

void func_80BAAF1C(EnSuttari* this) {
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    if (this->unk450 == 5) {
        this->unk450 = 3;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
    } else if ((this->unk450 == 3) && (curFrame == frameCount)) {
        this->unk450 = 6;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
        this->unk1E4 &= ~0x100;
    }
}

void func_80BAAFDC(EnSuttari* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 500.0f) && (this->actor.yDistToPlayer < 100.0f)) {
        Vec3f D_80BAE938 = { 0.0f, 0.0f, 0.0f };
        Vec3f sp48;
        Vec3f sp3C;

        Math_Vec3f_Copy(&sp48, &this->actor.world.pos);
        sp48.x += Math_SinS(this->actor.world.rot.y + this->unk3F4) * 10.0f;
        sp48.y += 60.0f;
        sp48.z += Math_CosS(this->actor.world.rot.y + this->unk3F4) * 10.0f;
        SysMatrix_StatePush();
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        D_80BAE938.z = 20.0f;
        SysMatrix_MultiplyVector3fByState(&D_80BAE938, &sp3C);
        SysMatrix_StatePop();
        if (this->unk3F0 == 0) {
            EffectSsSolderSrchBall_Spawn(globalCtx, &sp48, &sp3C, &D_801D15B0, 50, &this->unk3F0, 1);
        }
        if (this->unk3F0 == 1) {
            play_sound(NA_SE_SY_FOUND);
            this->unk3F0 = 0;
            this->actor.speedXZ = 0.0f;
            if (this->unk1F4[0] != 0) {
                this->unk1F4[0]--;
            }
            gSaveContext.weekEventReg[0x3D] |= 8;
            this->unk3F6 = 20;
            this->actionFunc = func_80BADE8C;
        }
    }
}

void func_80BAB1A0(EnSuttari* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 500.0f) && (this->actor.yDistToPlayer < 100.0f)) {
        Vec3f D_80BAE944 = { 0.0f, 0.0f, 0.0f };
        Vec3f sp48;
        Vec3f sp3C;

        Math_Vec3f_Copy(&sp48, &this->actor.world.pos);
        sp48.x += Math_SinS(this->actor.world.rot.y + this->unk3F4) * 350.0f;
        sp48.y += 60.0f;
        sp48.z += Math_CosS(this->actor.world.rot.y + this->unk3F4) * 350.0f;
        SysMatrix_StatePush();
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        D_80BAE944.z = 20.0f;
        SysMatrix_MultiplyVector3fByState(&D_80BAE944, &sp3C);
        SysMatrix_StatePop();
        if (this->unk3F0 == 0) {
            EffectSsSolderSrchBall_Spawn(globalCtx, &sp48, &sp3C, &D_801D15B0, 50, &this->unk3F0, 1);
        }
        if (this->unk3F0 == 1) {
            play_sound(NA_SE_SY_FOUND);
            this->unk3F0 = 0;
            this->actor.speedXZ = 0.0f;
            if (this->unk1F4[0] != 0) {
                this->unk1F4[0]--;
            }
            gSaveContext.weekEventReg[0x3D] |= 8;
            this->unk3F6 = 20;
            this->actionFunc = func_80BADE8C;
        } else {
            func_80BAAFDC(this, globalCtx);
        }
    }
}

void func_80BAB374(EnSuttari* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.animCurrentFrame;
    Vec3f sp38;

    if ((curFrame % 3) == 0) {
        sp38.x = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.x;
        sp38.y = this->actor.world.pos.y;
        sp38.z = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.z;
        func_800BBDAC(globalCtx, &this->actor, &sp38, 10.0f, 0, 2.0f, 0, 0, 0);
    }
}

void func_80BAB434(EnSuttari* this) {
    this->unk3F2 = Math_SinS(this->unk3F4) * 60.0f * (0x10000 / 360.0f);
    this->unk3F4 += 0x400;
}

void func_80BAB490(EnSuttari* this, GlobalContext* globalCtx) {
    this->paths[0] = func_8013D648(globalCtx, (this->actor.params & 0x7E00) >> 9, 0x3F);
    this->paths[1] = func_8013D648(globalCtx, this->paths[0]->unk1, 0x3F);
}

void func_80BAB4F0(EnSuttari* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp30;

    if (this->unk1E4 & 0x80) {
        func_80BAA6D0(this, globalCtx);
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (!(this->unk1E4 & 4) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE_MASK)) {
        if (func_8013D5E8(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer) != 0) {
            sp30.x = player->actor.world.pos.x;
            sp30.y = player->bodyPartsPos[7].y + 3.0f;
            sp30.z = player->actor.world.pos.z;
            func_8013D2E0(&sp30, &this->actor.focus, &this->actor.shape, &this->unk2D6, &this->unk2DC, &this->unk2E2,
                          D_80BAE800);
        } else {
            Math_SmoothStepToS(&this->unk2D6, 0, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk2D8, 0, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk2DC, 0, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk2DE, 0, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk2E2, 0, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk2E4, 0, 4, 0x3E8, 1);
        }
    }
    func_8013D9C8(globalCtx, this->unk2FA, this->unk31A, 16);
}

s16 func_80BAB698(Path* path, s32 idx, Vec3f* pos, f32* dist) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
        points = &points[idx];
        diffX = points->x - pos->x;
        diffZ = points->z - pos->z;
    } else {
        diffX = 0.0f;
        diffZ = 0.0f;
    }
    *dist = SQ(diffX) + SQ(diffZ);
    return Math_Acot2F(diffZ, diffX) * (0x8000 / M_PI);
}

s32 func_80BAB758(EnSuttari* this, Path* path, s32 arg2) {
    Vec3s* sp5C;
    s32 sp58;
    f32 phi_f12;
    s32 sp50;
    s32 pad4C;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    sp5C = Lib_SegmentedToVirtual(path->points);
    if (sp5C[arg2 - 1].x) {}
    sp58 = path->count;
    sp50 = 0;
    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);
    if (arg2 == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if (arg2 == sp58 - 1) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[arg2 + 1].x - sp5C[arg2 - 1].x;
        phi_f14 = sp5C[arg2 + 1].z - sp5C[arg2 - 1].z;
    }
    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);
    if (((sp44 * this->actor.world.pos.x) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = 1;
    }
    return sp50;
}

s32 func_80BAB8F4(EnSuttari* this, Path* path, s32 arg2) {
    Vec3s* sp5C;
    s32 sp58;
    f32 phi_f12;
    s32 sp50;
    s32 pad4C;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    sp5C = Lib_SegmentedToVirtual(path->points);
    if (sp5C[arg2 - 1].x) {}
    sp58 = path->count;
    sp50 = 0;
    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);
    if (arg2 == 0) {
        phi_f12 = sp5C[0].x - sp5C[1].x;
        phi_f14 = sp5C[0].z - sp5C[1].z;
    } else if (arg2 == sp58 - 1) {
        phi_f12 = sp5C[sp58 - 2].x - sp5C[sp58 - 1].x;
        phi_f14 = sp5C[sp58 - 2].z - sp5C[sp58 - 1].z;
    } else {
        phi_f12 = sp5C[arg2 - 1].x - sp5C[arg2 + 1].x;
        phi_f14 = sp5C[arg2 - 1].z - sp5C[arg2 + 1].z;
    }
    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);
    if (((sp44 * this->actor.world.pos.x) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = 1;
    }
    return sp50;
}

void func_80BABA90(EnSuttari* this, s32 arg1, u8 arg2) {
    s16 target;
    f32 dist;

    if (this->paths[arg1] != NULL) {
        target = func_80BAB698(this->paths[arg1], this->unk1F4[arg1], &this->actor.world.pos, &dist);
        if (this->actor.bgCheckFlags & 8) {
            if (arg2 == 2) {
                this->unk1F4[arg1] = -0x63;
            } else {
                target = this->actor.wallYaw;
            }
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, target, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        if (func_80BAB758(this, this->paths[arg1], this->unk1F4[arg1])) {
            if (this->unk1F4[arg1] >= (this->paths[arg1]->count - 1)) {
                if (arg2 == 0) {
                    this->unk1F4[arg1] = 0;
                } else {
                    this->unk1F4[arg1] = -0x63;
                }
            } else {
                this->unk1F4[arg1]++;
            }
        }
    }
}

void func_80BABB90(EnSuttari* this, s32 arg1) {
    s16 target;
    f32 sp30;

    if (this->paths[arg1] != NULL) {
        target = func_80BAB698(this->paths[arg1], this->unk1F4[arg1], &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            target = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, target, 1, 0xBB8, 0);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        if (func_80BAB8F4(this, this->paths[arg1], this->unk1F4[arg1])) {
            if (this->unk1F4[arg1] <= 0) {
                this->unk1F4[arg1] = -0x63;
            } else {
                this->unk1F4[arg1]--;
            }
        }
    }
}

s32 func_80BABC48(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct) {
    u16 sp26;
    u16 pad1;
    u8 sp23;
    u16 pad2;
    UNK_TYPE sp1C;
    u16 phi_a0;

    sp26 = gSaveContext.time - 0x3FFC;
    sp23 = (this->actor.params & 0x7E00) >> 9;
    sp1C = D_80BAE8F8[unkStruct->unk0];
    if (sp1C >= 0) {
        this->unk404 = func_8013BB34(globalCtx, sp23, sp1C);
    }
    if (this->unk404 == NULL) {
        return 0;
    }
    if ((this->unk428 != 0 && this->unk428 < 0xC) && (this->unk42A >= 0)) {
        phi_a0 = sp26;
    } else {
        phi_a0 = unkStruct->unk4;
    }
    if (unkStruct->unk8 < phi_a0) {
        this->unk418 = (phi_a0 - unkStruct->unk8) + 0xFFFF;
    } else {
        this->unk418 = unkStruct->unk8 - phi_a0;
    }
    this->unk424 = sp26 - phi_a0;
    phi_a0 = this->unk404->count - 2;
    this->unk42C = 0;
    this->unk41C = this->unk418 / phi_a0;
    this->unk420 = (this->unk424 / this->unk41C) + 2;
    this->unk430 = 0;
    return 1;
}

s32 func_80BABDD8(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct) {
    s32 pad;
    EnDoor* sp48;
    u8 sp47;
    u16 sp44;
    Vec3f sp38;
    Vec3f sp2C;
    Vec3s* sp28;
    UNK_TYPE sp24;

    sp47 = (this->actor.params & 0x7E00) >> 9;
    sp44 = gSaveContext.time - 0x3FFC;
    if (this->unk428 == 10 || this->unk428 == 11 || this->unk428 == 2) {
        return 0;
    }
    sp48 = (EnDoor*)func_8013BB7C(&this->actor, globalCtx, ACTORCAT_DOOR, ACTOR_EN_DOOR);
    sp24 = D_80BAE8F8[unkStruct->unk0];
    if ((sp48 != NULL) && (sp24 >= 0)) {
        this->unk404 = func_8013BB34(globalCtx, sp47, sp24);
    }
    if ((sp48 == NULL) || (this->unk404 == NULL)) {
        return 0;
    }
    sp28 = (Vec3s*)Lib_SegmentedToVirtual(this->unk404->points);
    Math_Vec3s_ToVec3f(&sp38, &sp28[0]);
    Math_Vec3s_ToVec3f(&sp2C, &sp28[1]);
    this->unk434 = sp44 - unkStruct->unk4;
    this->unk436 = unkStruct->unk8 - unkStruct->unk4;
    if (unkStruct->unk0 != 10 && unkStruct->unk0 != 11) {
        sp48->unk1A7 = 0x4B;
    }
    Math_Vec3f_Copy(&this->unk438, &sp38);
    Math_Vec3f_Copy(&this->unk444, &sp2C);
    this->actor.world.rot.y = Math_Vec3f_Yaw(&sp38, &sp2C);
    this->actor.world.pos = sp38;
    return 1;
}

s32 func_80BABF64(EnSuttari* this, GlobalContext* globalCtx, UnkStruct* unkStruct) {
    s32 ret;

    switch (unkStruct->unk0) {
        case 15:
        case 14:
        case 13:
        case 12:
            ret = func_80BABC48(this, globalCtx, unkStruct);
            break;
        case 11:
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
            ret = func_80BABDD8(this, globalCtx, unkStruct);
            break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
            ret = 1;
            break;
        default:
            ret = 0;
            break;
    }
    return ret;
}

s32 func_80BABFD4(EnSuttari* this, GlobalContext* globalCtx) {
    UNK_TYPE1 sp7C[0x424];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54;
    s32 sp50;
    s32 pad2;

    sp54 = 0;
    sp50 = 0;
    func_8013AF00(&sp7C, 3, this->unk404->count + 3);
    if (this->unk42C == 0) {
        sp58 = D_801D15B0;
        func_8013B6B0(this->unk404, &this->unk414, &this->unk424, this->unk41C, this->unk418, &this->unk420, &sp7C,
                      &sp58, this->unk42A);
        func_8013B878(globalCtx, this->unk404, this->unk420, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->unk42C = 1;
    } else {
        sp58 = this->unk408;
    }
    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;
    if (func_8013AD6C(globalCtx)) {
        sp54 = this->unk424;
        sp50 = this->unk420;
        sp58 = this->actor.world.pos;
    }
    this->unk408 = D_801D15B0;
    if (func_8013B6B0(this->unk404, &this->unk414, &this->unk424, this->unk41C, this->unk418, &this->unk420, &sp7C,
                      &this->unk408, this->unk42A)) {
        this->unk430 = 1;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->unk408;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }
    if (func_8013AD6C(globalCtx)) {
        this->unk424 = sp54;
        this->unk420 = sp50;
        this->unk408 = sp58;
    }
    return 0;
}

s32 func_80BAC220(EnSuttari* this, GlobalContext* globalCtx) {
    Vec3f sp3C;
    Vec3f sp30;
    s32 tmp2;
    f32 tmp;

    if (this->unk434 < 0) {
        this->unk434 = 0;
    } else {
        tmp2 = (this->unk436 < this->unk434) ? this->unk436 : this->unk434;
        this->unk434 = tmp2;
    }
    tmp = Math_Vec3f_DistXZ(&this->unk438, &this->unk444) / this->unk436;
    sp3C.x = sp3C.y = 0.0f;
    sp3C.z = this->unk434 * tmp;
    Lib_Vec3f_TranslateAndRotateY(&this->unk438, this->actor.world.rot.y, &sp3C, &sp30);
    this->actor.world.pos = sp30;
    this->unk434 += this->unk42A;
    return 0;
}

void func_80BAC2FC(EnSuttari* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    switch (this->unk428) {
        case 12:
        case 13:
            this->unk1E4 |= 0x80;
            func_80BABFD4(this, globalCtx);
            break;
        case 15:
            if ((this->unk450 == 1) && (curFrame == frameCount)) {
                this->unk450 = 2;
                func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            }
            if (!(gSaveContext.weekEventReg[0x53] & 4) && !(this->unk1E4 & 0x1000)) {
                if (ActorCutscene_GetCanPlayNext(this->unk456[0])) {
                    ActorCutscene_Start(this->unk456[0], &this->actor);
                    if (!(player->stateFlags1 & 0x10000000)) {
                        this->unk1E6 |= 0x10;
                        player->stateFlags1 |= 0x10000000;
                    }
                    this->unk1E4 |= 0x1000;
                    this->unk1E6 |= 2;
                } else {
                    ActorCutscene_SetIntentToPlay(this->unk456[0]);
                }
            }
            func_80BABFD4(this, globalCtx);
            break;
        case 6:
        case 8:
            this->unk1E4 |= 0x80;
            func_80BAC220(this, globalCtx);
            break;
        case 10:
            this->unk1E4 |= 0x80;
            func_80BAC220(this, globalCtx);
            break;
        case 9:
        case 11:
            this->unk1E4 |= 0x80;
            this->unk1E4 |= 0x20;
            this->enFsn->flags &= ~ENFSN_HAGGLE;
            if (this->unk450 != 2) {
                this->unk450 = 2;
                func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            }
            func_80BAC220(this, globalCtx);
            break;
        case 7:
            this->unk1E4 |= 0x20;
            this->unk1E4 |= 0x80;
            func_80BAC220(this, globalCtx);
            break;
        case 14:
            this->unk1E4 |= 0x20;
            this->unk1E4 |= 0x80;
            func_80BABFD4(this, globalCtx);
            break;
        case 1:
            Actor_MarkForDeath(&this->actor);
            break;
        case 2:
            if (!(gSaveContext.weekEventReg[0x51] & 4)) {
                this->unk1E4 |= 0x80;
                this->actor.world.pos.x = -16.0f;
                this->actor.world.pos.z = -16.0f;
                this->actor.world.pos.y = 12.0f;
                this->enFsn->flags |= ENFSN_HAGGLE;
                this->actionFunc = func_80BADA08;
            }
            break;
        case 4:
            if (!(gSaveContext.weekEventReg[0x21] & 8)) {
                if (this->unk450 == 2 || this->unk450 == 1) {
                    this->unk450 = 5;
                    func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
                }
                this->unk1E4 |= 0x10;
                if (this->unk1E6 & 2) {
                    this->unk1E6 &= ~2;
                }
                if (!(player->stateFlags1 & 0x10000000)) {
                    this->unk1E6 |= 0x10;
                    player->stateFlags1 |= 0x10000000;
                }
                this->unk1E8 = 0x2A30;
                func_801518B0(globalCtx, this->unk1E8, &this->actor);
                this->actionFunc = func_80BAD2B4;
            }
            break;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1554);
}

void func_80BAC6E8(EnSuttari* this, GlobalContext* globalCtx) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600C240, &D_0600071C, this->limbDrawTbl, this->transitionDrawTbl,
                     16);
    this->actor.draw = EnSuttari_Draw;
    this->actor.flags |= 1;
    if (globalCtx->sceneNum == 0x13) {
        this->unk1E4 |= 1;
        if (gSaveContext.day == 1 || gSaveContext.day == 2) {
            this->unk450 = 2;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            this->unk1E4 |= 0x80;
            this->actionFunc = func_80BACA14;
            return;
        } else if ((gSaveContext.day == 3) && (gSaveContext.time <= CLOCK_TIME(19, 00)) &&
                   !(gSaveContext.weekEventReg[0x3D] & 8) && !(gSaveContext.weekEventReg[0x21] & 8) &&
                   (gSaveContext.weekEventReg[0x33] & 8)) {
            this->unk450 = 2;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
            this->actionFunc = func_80BACEE0;
            return;
        }
    } else if (globalCtx->sceneNum == 0x6E) {
        if (gSaveContext.time >= CLOCK_TIME(0, 20) && gSaveContext.time < CLOCK_TIME(6, 00)) {
            Actor_MarkForDeath(&this->actor);
        }
        if ((gSaveContext.entranceIndex == 0xD670) || (gSaveContext.weekEventReg[0x3A] & 0x40)) {
            Actor_MarkForDeath(&this->actor);
        }
        this->unk456[0] = this->actor.cutscene;
        this->unk456[1] = ActorCutscene_GetAdditionalCutscene(this->unk456[0]);
        this->unk1E4 |= 0x80;
        this->unk1E4 |= 8;
        this->unk450 = 1;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
        this->actionFunc = func_80BAD004;
        return;
    } else if (globalCtx->sceneNum == 0x6D) {
        if (gSaveContext.weekEventReg[0x21] & 8) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk450 = 0;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
        this->unk1E4 |= 2;
        this->actionFunc = func_80BAD5F8;
        return;
    } else if (globalCtx->sceneNum == 0xD) {
        if (gSaveContext.weekEventReg[0x21] & 8) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk450 = 0;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
        this->unk456[0] = this->actor.cutscene;
        this->unk456[1] = ActorCutscene_GetAdditionalCutscene(this->unk456[0]);
        this->unk1E4 |= 4;
        this->actionFunc = func_80BAD7F8;
        return;
    } else {
        this->unk1E4 |= 8;
        this->unk1E4 |= 0x10;
        this->actionFunc = func_80BACA14;
        return;
    }
    Actor_MarkForDeath(&this->actor);
}

void func_80BACA14(EnSuttari* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk450 == 1 || this->unk450 == 8) {
        this->unk450 = 2;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
    }
    func_80BABA90(this, 0, 0);
    func_80BAB434(this);
    if (player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_ZORA) {
        if (this->actor.yDistToPlayer < 60.0f && this->actor.xzDistToPlayer < 500.0f) {
            this->unk3F2 = this->unk2DE;
            this->actionFunc = func_80BACBB0;
        }
    } else if ((player->transformation == PLAYER_FORM_HUMAN) && CUR_EQUIP_VALUE_VOID(EQUIP_SWORD) != 0) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            this->unk3F2 = this->unk2DE;
            func_80BAAB78(this, globalCtx);
            this->actionFunc = func_80BADA9C;
        } else if (this->actor.xzDistToPlayer < 200.0f) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        }
    }
    Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 0.1f);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BACBB0(EnSuttari* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 target;

    this->unk3F2 = this->unk2DE;
    if (player->transformation == PLAYER_FORM_HUMAN || player->transformation == PLAYER_FORM_DEKU) {
        this->actionFunc = func_80BACA14;
    }
    if ((this->actor.yDistToPlayer < 60.0f) && (this->actor.xzDistToPlayer < 500.0f)) {
        if (this->actor.bgCheckFlags & 8) {
            target = this->actor.wallYaw;
        } else if (func_80BAA904(this, globalCtx)) {
            target = -this->actor.world.rot.y;
        } else {
            target = -this->actor.yawTowardsPlayer;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, target, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 0.1f);
    } else {
        this->actionFunc = func_80BACD2C;
        this->actor.speedXZ = 0.0f;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (!(this->actor.bgCheckFlags & 1)) {
        this->actor.world.pos = this->actor.prevPos;
        this->actor.world.rot.y = -this->actor.world.rot.y;
        this->actionFunc = func_80BACE4C;
    }
}

void func_80BACD2C(EnSuttari* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->unk3F2 = this->unk2DE;
    if (player->transformation == PLAYER_FORM_HUMAN || player->transformation == PLAYER_FORM_DEKU) {
        this->actionFunc = func_80BACA14;
    }
    if ((this->actor.yDistToPlayer < 60.0f) && (this->actor.xzDistToPlayer < 500.0f)) {
        this->actionFunc = func_80BACBB0;
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 0.1f);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (!(this->actor.bgCheckFlags & 1)) {
        this->actor.world.pos = this->actor.prevPos;
        this->actor.world.rot.y = -this->actor.world.rot.y;
        this->actionFunc = func_80BACE4C;
    }
}

void func_80BACE4C(EnSuttari* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer > 100.0f) {
        this->actionFunc = func_80BACBB0;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (this->actor.world.pos.y != this->actor.floorHeight) {
        this->actor.world.pos = this->actor.prevPos;
        this->actor.world.rot.y = -this->actor.world.rot.y;
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void func_80BACEE0(EnSuttari* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.unk_14;
    UnkStruct unkStruct;

    this->unk42A = REG(15) + *unk_14;
    if (!func_80133038(globalCtx, D_80BAE820, &unkStruct) ||
        ((this->unk428 != unkStruct.unk0) && !func_80BABF64(this, globalCtx, &unkStruct))) {
        this->actor.flags &= ~1;
        unkStruct.unk0 = 0;
    } else {
        this->actor.flags |= 1;
    }
    this->unk428 = unkStruct.unk0;
    func_80BAC2FC(this, globalCtx);
    func_80BAB434(this);
    if (this->unk428 == 5) {
        gSaveContext.weekEventReg[0x3A] |= 0x80;
        this->actionFunc = func_80BADDB4;
        this->actor.speedXZ = 0.0f;
    } else if (Player_GetMask(globalCtx) != PLAYER_MASK_STONE_MASK) {
        func_80BAB1A0(this, globalCtx);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BAD004(EnSuttari* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.unk_14;
    UnkStruct unkStruct;

    this->unk42A = REG(15) + *unk_14;
    if (!func_80133038(globalCtx, D_80BAE820, &unkStruct) ||
        ((this->unk428 != unkStruct.unk0) && !func_80BABF64(this, globalCtx, &unkStruct))) {
        this->actor.flags &= ~1;
        unkStruct.unk0 = 0;
    } else {
        this->actor.flags |= 1;
    }
    this->unk428 = unkStruct.unk0;
    func_80BAC2FC(this, globalCtx);
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0x2A3A, &this->actor);
        this->actionFunc = func_80BAD130;
    } else if ((this->actor.xzDistToPlayer < 200.0f) || this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BAD130(EnSuttari* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if ((talkState == 5 || talkState == 6) && func_80147624(globalCtx)) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        if (this->unk1E4 & 8) {
            this->actionFunc = func_80BAD004;
        } else if (this->unk1E4 & 4) {
            this->actionFunc = func_80BAD7F8;
        } else if (this->unk1E4 & 2) {
            this->actionFunc = func_80BAD5F8;
        } else if (this->unk1E4 & 1) {
            this->unk3F6 = 20;
            this->actionFunc = func_80BADF3C;
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
}

void func_80BAD230(EnSuttari* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk456[1])) {
        ActorCutscene_Start(this->unk456[1], &this->actor);
        this->unk1E8 = 0x2A31;
        func_801518B0(globalCtx, this->unk1E8, &this->actor);
        this->unk1E4 |= 0x4000;
        func_801A89A8(0x8003); // SFX?
        this->actionFunc = func_80BAD380;
    } else {
        ActorCutscene_SetIntentToPlay(this->unk456[1]);
    }
}

void func_80BAD2B4(EnSuttari* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->unk1E8 == 0x2A30) {
            ActorCutscene_Stop(this->unk456[0]);
            ActorCutscene_SetIntentToPlay(this->unk456[1]);
            this->actionFunc = func_80BAD230;
        } else {
            ActorCutscene_Stop(this->unk456[1]);
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk1E4 |= 0x40;
            this->actionFunc = func_80BAD380;
        }
    }
    func_80BAB374(this, globalCtx);
}

void func_80BAD380(EnSuttari* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;

    if ((player->stateFlags1 & 0x40) && (globalCtx->msgCtx.unk11F04 != 0x2A31)) {
        this->unk1E4 |= 0x8000;
        this->actor.speedXZ = 0.0f;
    } else {
        this->unk1E4 &= ~0x8000;
        func_80BABA90(this, 1, 1);
        if ((this->unk1E4 & 0x4000) && (talkState == 5) && func_80147624(globalCtx)) {
            this->unk1E6 &= ~0x10;
            player->stateFlags1 &= ~0x10000000;
            this->unk1E4 &= ~0x4000;
            ActorCutscene_Stop(this->unk456[1]);
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk1E4 |= 0x40;
        }
        if (this->unk1E4 & 0x100) {
            this->unk1E6 |= 8;
            func_80BAAF1C(this);
        } else if (this->unk1E4 & 0x200) {
            gSaveContext.weekEventReg[0x4F] |= 0x40;
            this->unk1E6 |= 4;
            this->actor.speedXZ = 0.0f;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            func_800F0568(globalCtx, &this->actor.world.pos, 30, NA_SE_IT_BOMB_EXPLOSION);
            Actor_MarkForDeath(&this->actor);
            return;
        }
        if (this->unk1F4[1] == -0x63) {
            if (this->unk1E6 & 8) {
                gSaveContext.weekEventReg[0x21] |= 8;
            }
            this->actor.speedXZ = 0.0f;
            func_801A89A8(0x101400FF);
            this->unk1E6 |= 4;
            func_80BAA88C(globalCtx, 0xD670);
        } else {
            this->unk3F2 = this->unk2DE;
            Math_ApproachF(&this->actor.speedXZ, 4.0f, 0.2f, 0.5f);
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            func_80BAB374(this, globalCtx);
        }
    }
}

void func_80BAD5F8(EnSuttari* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.unk_14;
    UnkStruct unkStruct;
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    if ((curFrame == frameCount) && (this->unk450 == 0) && (this->unk1E4 & 0x20)) {
        this->unk450 = 2;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
    }
    this->unk42A = REG(15) + *unk_14;
    if (!func_80133038(globalCtx, D_80BAE820, &unkStruct) ||
        ((this->unk428 != unkStruct.unk0) && !func_80BABF64(this, globalCtx, &unkStruct))) {
        this->actor.flags &= ~1;
        unkStruct.unk0 = 0;
    } else {
        this->actor.flags |= 1;
    }
    this->unk428 = unkStruct.unk0;
    func_80BAC2FC(this, globalCtx);
    if ((this->unk430 == 1) && (this->unk404->unk1 == 0xFF)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    func_80BAB434(this);
    if ((this->unk1E4 & 0x20) && (this->unk430 == 0) && (unkStruct.unk0 != 7)) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            func_801518B0(globalCtx, 0x2A02, &this->actor);
            this->actionFunc = func_80BAD130;
        } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BAD7F8(EnSuttari* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.unk_14;
    UnkStruct unkStruct;
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    if (this->enFsn == NULL) {
        this->enFsn = (EnFsn*)func_80BAA848(globalCtx, ACTOR_EN_FSN);
    } else {
        if ((this->unk1E4 & 0x2000) && (this->unk450 == 1) && (curFrame == frameCount)) {
            this->unk450 = 2;
            func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
        }
        this->unk42A = REG(15) + *unk_14;
        if (!func_80133038(globalCtx, D_80BAE820, &unkStruct) ||
            ((this->unk428 != unkStruct.unk0) && !func_80BABF64(this, globalCtx, &unkStruct))) {
            this->actor.flags &= ~1;
            unkStruct.unk0 = 0;
        } else {
            this->actor.flags |= 1;
        }
        this->unk428 = unkStruct.unk0;
        func_80BAC2FC(this, globalCtx);
        if ((this->unk430 == 1) && (this->unk404->unk1 == 0xFF)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        if ((this->unk1E4 & 0x20) && (unkStruct.unk0 != 9)) {
            if (func_800B84D0(&this->actor, globalCtx)) {
                func_801518B0(globalCtx, 0x2A02, &this->actor);
                this->actionFunc = func_80BAD130;
            } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
                func_800B863C(&this->actor, globalCtx);
            }
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void func_80BADA08(EnSuttari* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        func_80BAAB78(this, globalCtx);
        gSaveContext.weekEventReg[0x51] |= 4;
    } else if (this->actor.xzDistToPlayer < 500.0f) {
        this->actor.flags |= 0x10000;
        func_800B8614(&this->actor, globalCtx, 500.0f);
    }
}

void func_80BADA9C(EnSuttari* this, GlobalContext* globalCtx) {
    u8 talkstate = func_80152498(&globalCtx->msgCtx);
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount = SkelAnime_GetFrameCount(&D_80BAE6D0[this->unk450].animation->common);

    if (this->unk1E4 & 1) {
        this->unk3F2 = this->unk2DE;
        func_80BAA9B4(this);
    } else if ((this->unk450 == 7) && (curFrame == frameCount)) {
        this->unk450 = 1;
        func_800BDC5C(&this->skelAnime, D_80BAE6D0, this->unk450);
    }
    if (talkstate == 5) {
        if (func_80147624(globalCtx)) {
            if (this->unk1E4 & 0x400) {
                if (this->unk1E8 == 0x29EE) {
                    ActorCutscene_Stop(this->unk456[this->unk45A]);
                }
                this->unk1E4 &= ~0x400;
                if (this->unk1E6 & 1) {
                    ((EnElf*)PLAYER->naviActor)->unk264 |= 0x10;
                    this->unk1E6 &= ~1;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk1E8 = 0;
                if (this->unk1E4 & 1) {
                    this->actionFunc = func_80BACA14;
                } else {
                    this->actionFunc = func_80BAD7F8;
                }
                return;
            }
            func_80BAAB78(this, globalCtx);
        }
    } else if ((talkstate == 4) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                func_8019F208();
                this->unk1E4 |= 0x800;
                func_80BAAB78(this, globalCtx);
                break;
            case 1:
                func_8019F230();
                func_80BAAB78(this, globalCtx);
                break;
        }
    }
    if (!(this->unk1E4 & 4)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void func_80BADD0C(EnSuttari* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk456[this->unk45A])) {
        if (this->unk45A == 0) {
            ActorCutscene_Start(this->unk456[this->unk45A], &this->enFsn->actor);
        } else {
            ActorCutscene_Start(this->unk456[this->unk45A], &this->actor);
        }
        func_80BAAA94(this);
        this->actionFunc = func_80BADA9C;
    } else {
        ActorCutscene_SetIntentToPlay(this->unk456[this->unk45A]);
    }
}

void func_80BADDB4(EnSuttari* this, GlobalContext* globalCtx) {
    func_80BABA90(this, 1, 1);
    func_80BAB434(this);
    if (gSaveContext.weekEventReg[0x33] & 0x10) {
        this->actionFunc = func_80BADE14;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BADE14(EnSuttari* this, GlobalContext* globalCtx) {
    func_80BABA90(this, 1, 2);
    if (this->unk1F4[1] == -0x63) {
        this->actor.speedXZ = 0.0f;
    } else {
        this->unk3F2 = this->unk2DE;
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.2f, 0.5f);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BADE8C(EnSuttari* this, GlobalContext* globalCtx) {
    this->unk3F2 = this->unk2DE;
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xBB8, 0);
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        func_801518B0(globalCtx, 0x2A3A, &this->actor);
        this->actionFunc = func_80BAD130;
    } else {
        this->actor.flags |= 0x10000;
        func_800B8614(&this->actor, globalCtx, 500.0f);
    }
}

void func_80BADF3C(EnSuttari* this, GlobalContext* globalCtx) {
    func_80BABB90(this, 0);
    if (this->unk1F4[0] == -0x63) {
        Actor_MarkForDeath(&this->actor);
    }
    this->unk3F2 = this->unk2DE;
    if (DECR(this->unk3F6) == 0) {
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.2f, 0.5f);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void EnSuttari_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSuttari* this = THIS;
    s32 pad;

    if (gSaveContext.weekEventReg[0x4F] & 0x40) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80BAE7A8);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80BAE7E0, &D_80BAE7D4);
    this->actor.flags &= ~1;
    func_80BAB490(this, globalCtx);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80BAC6E8;
    this->actor.gravity = -4.0f;
}

void EnSuttari_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSuttari* this = THIS;

    if ((globalCtx->sceneNum == 0x6E) && !(this->unk1E6 & 4)) {
        func_801A89A8(0x101400FF);
    }
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnSuttari_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSuttari* this = THIS;
    s32 pad;
    Player* player = PLAYER;

    this->actionFunc(this, globalCtx);
    if ((this->unk1E4 & 8) && (this->unk1E6 & 0x10) && (player->stateFlags1 & 0x10000000)) {
        player->actor.freezeTimer = 3;
    }
    if (!(this->unk1E4 & 0x8000)) {
        func_80BAB4F0(this, globalCtx);
    }
    if (this->unk1E6 & 2) {
        func_80BAA8D0();
    }
    if (this->unk428 != 0) {
        if (this->unk450 == 2 || this->unk450 == 6) {
            if (func_801378B8(&this->skelAnime, 8.0f) || func_801378B8(&this->skelAnime, 16.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
            }
        } else if (this->unk450 == 0 || this->unk450 == 5) {
            if (func_801378B8(&this->skelAnime, 8.0f) || func_801378B8(&this->skelAnime, 17.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
            }
        }
    }
}

s32 func_80BAE250(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnSuttari* this = THIS;

    if (limbIndex == 15) {
        *dList = D_0600AF90;
        if (!(this->unk1E4 & 4)) {
            SysMatrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            SysMatrix_InsertXRotation_s(this->unk3F2, MTXMODE_APPLY);
            SysMatrix_InsertZRotation_s(-this->unk2DC, MTXMODE_APPLY);
            SysMatrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        }
    }
    if (limbIndex == 8) {
        SysMatrix_InsertXRotation_s(-this->unk2E4, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(-this->unk2E2, MTXMODE_APPLY);
    }
    if (limbIndex == 8 || limbIndex == 9 || limbIndex == 0xC) {
        rot->y += (s16)(Math_SinS(this->unk2FA[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->unk31A[limbIndex]) * 200.0f);
    }
    return 0;
}

void func_80BAE3C4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80BAE950 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_80BAE95C = { 2000.0f, -1000.0f, 0.0f };
    EnSuttari* this = THIS;
    s32 pad;
    MtxF* sp44;
    Actor* bombBag;

    if ((((this->unk1E4 & 8) && (this->unk1E4 & 0x10)) || ((this->unk1E4 & 2) && !(this->unk1E4 & 0x20)) ||
         ((this->unk1E4 & 4) && !(this->unk1E4 & 0x20)))) {
        if (limbIndex == 8) {
            sp44 = SysMatrix_GetCurrentState();
            SysMatrix_MultiplyVector3fByState(&D_80BAE95C, &this->unk3F8);
            if (this->actor.child == NULL) {
                if (this->unk1E4 & 0x100) {
                    bombBag = Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_NIMOTSU,
                                                    sp44->mf[3][0], sp44->mf[3][1], sp44->mf[3][2], 0, 0, 0, -1);
                    if (bombBag != NULL) {
                        func_8018219C(sp44, &bombBag->shape.rot, 0);
                    }
                } else {
                    func_8012C28C(globalCtx->state.gfxCtx);
                    OPEN_DISPS(globalCtx->state.gfxCtx);
                    gSPDisplayList(POLY_OPA_DISP++, D_06013380);
                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                }
            }
        }
    }
    if (limbIndex == 15) {
        SysMatrix_MultiplyVector3fByState(&D_80BAE950, &this->actor.focus.pos);
    }
}

void func_80BAE524(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnSuttari_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSuttari* this = THIS;
    s32 pad;
    Vec3f sp5C;
    Vec3f sp50;

    if (this->unk1E4 & 0x80) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        func_8012C28C(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 255, 255, 255, 0));
        gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 55, 55, 255, 0));
        gDPPipeSync(POLY_OPA_DISP++);
        func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                      func_80BAE250, func_80BAE3C4, func_80BAE524, &this->actor);
        if (this->unk1E4 & 0x80) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            sp5C = this->actor.world.pos;
            sp50.x = 0.2f;
            sp50.y = 0.2f;
            sp50.z = 0.2f;
            func_800BC620(&sp5C, &sp50, 0xFF, globalCtx);
        }
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
