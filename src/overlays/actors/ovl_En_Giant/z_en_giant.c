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
// This is checking that a Giant is NOT freed...
s32 func_80B01A74(EnGiant* this) {
    switch (GIANT_TYPE(&this->actor)) {
        case GIANT_TYPE_SWAMP_1:
        case GIANT_TYPE_SWAMP_2:
        case GIANT_TYPE_SWAMP_3:
        case GIANT_TYPE_SWAMP_4:
            // Odolwa's Remains
            if (!CHECK_QUEST_ITEM(0)) {
                return 1;
            }
            break;
        case GIANT_TYPE_MOUNTAIN_1:
        case GIANT_TYPE_MOUNTAIN_2:
        case GIANT_TYPE_MOUNTAIN_3:
        case GIANT_TYPE_MOUNTAIN_4:
            // Goht's Remains
            if (!CHECK_QUEST_ITEM(1)) {
                return 1;
            }
            break;
        case GIANT_TYPE_OCEAN_1:
        case GIANT_TYPE_OCEAN_2:
        case GIANT_TYPE_OCEAN_3:
        case GIANT_TYPE_OCEAN_4:
            // Gyorg's Remains
            if (!CHECK_QUEST_ITEM(2)) {
                return 1;
            }
            break;
        case GIANT_TYPE_CANYON_1:
        case GIANT_TYPE_CANYON_2:
        case GIANT_TYPE_CANYON_3:
        case GIANT_TYPE_CANYON_4:
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
    s32 type = GIANT_TYPE(thisx);

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
    switch (type) {
        case GIANT_TYPE_CANYON_1:
        case GIANT_TYPE_CANYON_2:
        case GIANT_TYPE_CANYON_3:
            this->unk_24A = 0x1C6;
            break;
        case GIANT_TYPE_SWAMP_1:
        case GIANT_TYPE_SWAMP_2:
        case GIANT_TYPE_SWAMP_3:
            this->unk_24A = 0x1C7;
            break;
        case GIANT_TYPE_OCEAN_1:
        case GIANT_TYPE_OCEAN_2:
        case GIANT_TYPE_OCEAN_3:
            this->unk_24A = 0x1C8;
            break;
        default:
            this->unk_24A = 0x1C5;
            break;
    }

    if (type >= GIANT_TYPE_MOUNTAIN_2 && type < GIANT_TYPE_MOUNTAIN_3) {
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

    if (type >= GIANT_TYPE_MOUNTAIN_4 && type < GIANT_TYPE_MAX) {
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

    if (type >= GIANT_TYPE_MOUNTAIN_2) {
        this->unk_24E = 0xFF;
    }

    this->unk_250 = 0xFFFF;
    if (type >= GIANT_TYPE_MOUNTAIN_3 && type < GIANT_TYPE_MOUNTAIN_4) {
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
