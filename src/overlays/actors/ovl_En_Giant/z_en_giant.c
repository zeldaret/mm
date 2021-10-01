#include "z_en_giant.h"

#define FLAGS 0x00000030

#define THIS ((EnGiant*)thisx)

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B01990(EnGiant* this, s16 arg1);
void func_80B023D0(EnGiant* this, GlobalContext* globalCtx);
void func_80B024AC(EnGiant* this, GlobalContext* globalCtx);
void func_80B024D8(EnGiant* this, GlobalContext* globalCtx);

const ActorInit En_Giant_InitVars = {
    ACTOR_EN_GIANT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GIANT,
    sizeof(EnGiant),
    (ActorFunc)EnGiant_Init,
    (ActorFunc)EnGiant_Destroy,
    (ActorFunc)EnGiant_Update,
    (ActorFunc)EnGiant_Draw,
};

extern AnimationHeader D_06002168;
extern UNK_TYPE D_06007610;
extern FlexSkeletonHeader D_060079B0;
extern AnimationHeader D_060116E4;
extern AnimationHeader D_06013004;
extern AnimationHeader D_06013FE8;

s32 D_80B02950[] = {
    0x06008394, 0x060096E4, 0x060102A4, 0x060116E4, 0x06012A38, 0x06013004, 0x06013FE8, 0x06015334,
    0x06017944, 0x0600A1C4, 0x0600D040, 0x0600DE84, 0x0600ACA4, 0x0600B784, 0x0600C5D4,
};

s32 D_80B0298C[] = { 0x06005A80, 0x06006280, 0x06006A80, 0x00000000, 0x00000000 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01990.s")

// Note: if #275 gets merged before this, switch to using the IDs there.
s32 func_80B01A74(EnGiant* this) {
    switch (this->actor.params & 0xF) {
        case 2:
        case 6:
        case 10:
        case 14:
            // Odolwa's Remains
            if (!CHECK_QUEST_ITEM(0)) {
                return 1;
            }
            break;
        case 0:
        case 4:
        case 8:
        case 12:
            // Goht's Remains
            if (!CHECK_QUEST_ITEM(1)) {
                return 1;
            }
            break;
        case 3:
        case 7:
        case 11:
        case 15:
            // Gyorg's Remains
            if (!CHECK_QUEST_ITEM(2)) {
                return 1;
            }
            break;
        case 1:
        case 5:
        case 9:
        case 13:
            // Twinmold's Remains
            if (!CHECK_QUEST_ITEM(3)) {
                return 1;
            }
            break;
    }

    return 0;
}

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGiant* this = THIS;
    s32 param;

    param = this->actor.params & 0xF;
    this->actor.uncullZoneForward = 4000.0f;
    this->actor.uncullZoneScale = 2000.0f;
    this->actor.uncullZoneDownward = 2400.0f;
    Actor_SetScale(&this->actor, 0.32f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060079B0, &D_06002168, this->jointTable, this->morphTable, 16);
    func_80B01990(this, 7);
    this->unk_24C = 0;
    this->actionFunc = func_80B024D8;
    this->actor.draw = NULL;
    this->unk_24E = 0;
    this->actor.velocity.y = -10.0f;
    this->actor.minVelocityY = -10.0f;
    this->actor.gravity = -5.0f;
    switch (param) {
        case 1:
        case 5:
        case 9:
            this->unk_24A = 0x1C6;
            break;
        case 2:
        case 6:
        case 10:
            this->unk_24A = 0x1C7;
            break;
        case 3:
        case 7:
        case 11:
            this->unk_24A = 0x1C8;
            break;
        default:
            this->unk_24A = 0x1C5;
            break;
    }

    if (param >= 4 && param < 8) {
        if (!(gSaveContext.weekEventReg[0x19] & 2)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk_24A = 0x1C5;
        Actor_SetScale(&this->actor, 0.32f);
        this->actionFunc = func_80B023D0;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060116E4, 0.0f, SkelAnime_GetFrameCount(&D_060116E4.common) - 1.0f,
                             SkelAnime_GetFrameCount(&D_060116E4.common), 2, 0.0f);
        this->actor.draw = EnGiant_Draw;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
    }

    if (param >= 0xC && param < 0x10) {
        Actor_SetScale(&this->actor, 0.32f);
        this->actionFunc = func_80B024AC;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06013FE8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06013004.common), 0,
                             0.0f);
        this->actor.draw = EnGiant_Draw;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
        if (func_80B01A74(this)) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    if (param >= 4) {
        this->unk_24E = 0xFF;
    }

    this->unk_250 = 0xFFFF;
    if (param >= 8 && param < 0xC) {
        switch (gSaveContext.sceneSetupIndex) {
            case 0:
            case 10:
                this->unk_250 = 0x2183;
                break;
            case 1:
            case 2:
            case 3:
                this->unk_250 = 0x2182;
                break;
            default:
                this->unk_250 = 0x2181;
                break;
        }
    }
}

void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B020A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B0211C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B023D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B024AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B024D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B026C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Draw.s")
