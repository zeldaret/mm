#include "z_en_elforg.h"

#define FLAGS 0x00000010

#define THIS ((EnElforg*)thisx)

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ACCEB0(EnElforg* this, GlobalContext* globalCtx);
void func_80ACCC98(EnElforg* this, GlobalContext* globalCtx);
void func_80ACCBD0(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD6A8(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD6EC(EnElforg* this, GlobalContext* globalCtx);
void func_80ACD2E4(EnElforg* this, GlobalContext* globalCtx);

const ActorInit En_Elforg_InitVars = {
    ACTOR_EN_ELFORG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElforg),
    (ActorFunc)EnElforg_Init,
    (ActorFunc)EnElforg_Destroy,
    (ActorFunc)EnElforg_Update,
    (ActorFunc)EnElforg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ACDA30 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 16, 32, 0, { 0, 0, 0 } },
};

static s32 D_80ACDA5C[] = { 0x00000000, 0xBD4CCCCD, 0x00000000 };

static s32 D_80ACDA68[] = { 0x00000000, 0xBCCCCCCD, 0x00000000 };

static s32 D_80ACDA74[] = { 0xFFEBDCFF, 0xFFDCDCFF, 0xDCFFDCFF, 0xDCDCFFFF, 0xFFFFC8FF };

static s32 D_80ACDA88[] = { 0xFF9600FF, 0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF };

void func_80ACC470(EnElforg* this) {
    this->actor.speedXZ = 1.0f;
    this->unk_224 = 1.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = randPlusMinusPoint5Scaled(65536.0f);
    this->unk_21C = 0;
    this->unk_220 = Rand_ZeroFloat(100.0f);
    this->actor.shape.yOffset = 0.0f;
    this->skelAnime.animCurrentFrame = (s32)Rand_ZeroFloat(5.0f);
}

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->unk_214 = 0;
    this->unk_216 = 0;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0402CA98, &D_0402B494, this->jointTable, this->jointTable, 10);
    this->skelAnime.animPlaybackSpeed = 1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actor.shape.shadowAlpha = 0xFF;

    switch (this->actor.params & 0xF) {
        case 3:
            if ((gSaveContext.weekEventReg[8] & 0x80) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case 7:
            if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0xFE00) >> 9) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        default:
            if (Flags_GetSwitch(globalCtx, (this->actor.params & 0xFE00) >> 9) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case 1:
        case 2:
        case 6:
        case 8:
            break;
    }

    if (func_8010A074(globalCtx) != 0) {
        this->unk_218 = gSaveContext.unk_48C8 + 1;
    } else {
        // Needs to be thisx in order to match
        this->unk_218 = (thisx->params & 0x1C0) >> 6;
    }

    switch (this->actor.params & 0xF) {
        case 1:
            func_80ACC470(this);
            this->actionFunc = func_80ACCEB0;
            this->unk_224 = Rand_ZeroFloat(2.0f) + 1.0f;
            this->unk_228 = Rand_ZeroFloat(100.0f) + 50.0f;
            break;
        case 8:
            func_80ACC470(this);
            this->actionFunc = func_80ACCC98;
            this->unk_220 = 0x3C;
            break;
        case 2:
            this->unk_21C = 0;
            this->actionFunc = func_80ACCBD0;
            break;
        case 4:
            this->actionFunc = func_80ACD6A8;
            func_80ACD6A8(this, globalCtx);
            this->actor.draw = NULL;
            break;
        case 5:
            this->actionFunc = func_80ACD6EC;
            this->actor.draw = NULL;
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80ACDA30);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            break;
        default:
            func_80ACC470(this);
            this->actionFunc = func_80ACD2E4;
            break;
    }

    this->actor.shape.rot.y = 0;
}

void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    if ((this->actor.params & 0xF) == 5) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC7E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC8D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCBB8.s")

void func_80ACCBD0(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actor.parent == NULL) || (this->actor.parent->update == NULL)) {
        func_80ACC470(this);
        this->actionFunc = func_80ACD2E4;
    } else {
        this->actor.shape.yOffset += 10.0f * Math_SinS(this->unk_21C << 9);
        this->actor.world.pos = this->actor.parent->world.pos;
        this->actor.world.pos.y += 12.0f;
    }
    func_80ACCBB8(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCC98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCEB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD6EC.s")

void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_21C == 0 && this->unk_220 > 0) {
        this->unk_220--;
    } else {
        this->unk_21C++;
    }

    if (this->unk_216 < 0) {
        this->unk_216++;
        if (this->unk_216 == 0) {
            this->unk_216 = Rand_ZeroFloat(20.0f) + 20.0f;
        }
    } else if (this->unk_216 > 0) {
        this->unk_216--;
    } else {
        this->unk_216 = -Rand_ZeroFloat(20.0f) - 20.0f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/EnElforg_Draw.s")
