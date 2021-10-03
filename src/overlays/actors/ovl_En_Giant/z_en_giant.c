#include "z_en_giant.h"

#define FLAGS 0x00000030

#define THIS ((EnGiant*)thisx)

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx);

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
extern AnimationHeader D_06008394;
extern AnimationHeader D_060096E4;
extern AnimationHeader D_0600A1C4;
extern AnimationHeader D_0600ACA4;
extern AnimationHeader D_0600B784;
extern AnimationHeader D_0600C5D4;
extern AnimationHeader D_0600D040;
extern AnimationHeader D_0600DE84;
extern AnimationHeader D_060102A4;
extern AnimationHeader D_060116E4;
extern AnimationHeader D_06012A38;
extern AnimationHeader D_06013004;
extern AnimationHeader D_06013FE8;
extern AnimationHeader D_06015334;
extern AnimationHeader D_06017944;

AnimationHeader* D_80B02950[] = {
    &D_06008394, &D_060096E4, &D_060102A4, &D_060116E4, &D_06012A38, &D_06013004, &D_06013FE8, &D_06015334,
    &D_06017944, &D_0600A1C4, &D_0600D040, &D_0600DE84, &D_0600ACA4, &D_0600B784, &D_0600C5D4,
};

s32 D_80B0298C[] = { 0x06005A80, 0x06006280, 0x06006A80, 0x00000000, 0x00000000 };

void func_80B01990(EnGiant* this, s16 arg1) {
    if ((arg1 >= 0) && (arg1 < 0xF)) {
        if (((this->unk_248 == 8) && (arg1 != 8)) || ((arg1 == 8) && (this->unk_248 != 8))) {
            SkelAnime_ChangeAnim(&this->skelAnime, D_80B02950[arg1], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80B02950[arg1]->common), 2, 10.0f);
        } else {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, D_80B02950[arg1]);
        }
        this->unk_248 = arg1;
    }
}

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

    this->sfxId = 0xFFFF;
    if (type >= GIANT_TYPE_MOUNTAIN_3 && type < GIANT_TYPE_MOUNTAIN_4) {
        switch (gSaveContext.sceneSetupIndex) {
            case 0:
            case 10:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE2 - SFX_FLAG;
                break;
            case 1:
            case 2:
            case 3:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE1 - SFX_FLAG;
                break;
            default:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE0 - SFX_FLAG;
                break;
        }
    }
}

void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80B01E84(EnGiant* this, s16 arg1) {
    s16 temp_v0 = arg1 + 1;

    if (this->unk_248 != temp_v0) {
        if (this->unk_248 != arg1) {
            func_80B01990(this, arg1);
        } else {
            func_80B01990(this, temp_v0);
        }
    }
}

void func_80B01EE8(EnGiant* this) {
    switch (this->unk_24C) {
        case 1:
            func_80B01990(this, 7);
            break;
        case 2:
            func_80B01990(this, 8);
            break;
        case 5:
            func_80B01990(this, 5);
            break;
        case 6:
            func_80B01990(this, 2);
            break;
        case 7:
            func_80B01990(this, 7);
            this->unk_24E = 0;
            break;
        case 8:
            func_80B01990(this, 9);
            break;
        case 9:
            func_80B01990(this, 11);
            break;
        case 10:
            func_80B01990(this, 12);
            break;
        case 11:
            func_80B01990(this, 14);
            break;
        case 12:
            func_80B01990(this, 7);
            break;
        case 13:
            func_80B01990(this, 8);
            break;
        case 14:
            if (this->unk_248 != 8) {
                func_80B01990(this, 8);
            }
            break;
        case 15:
            SkelAnime_ChangeAnim(&this->skelAnime, &D_060116E4, 0.0f,
                                 SkelAnime_GetFrameCount(&D_060116E4.common) - 1.0f,
                                 SkelAnime_GetFrameCount(&D_060116E4.common), 2, 0.0f);
            break;
    }
}

void func_80B020A0(EnGiant* this) {
    switch (this->unk_24C) {
        case 6:
            if (this->skelAnime.animCurrentFrame >= 90.0f && this->unk_24E > 0) {
                this->unk_24E -= 0xC;
            }
            break;
        case 14:
            this->unk_24E -= 0xC;
            break;
        default:
            if (this->unk_24E < 0xFF) {
                this->unk_24E += 8;
            }
            break;
    }
}

void func_80B0211C(EnGiant* this) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (this->unk_248 != 2 || this->unk_24C != 6)) {
        func_80B01990(this, this->unk_248);
        switch (this->unk_24C) {
            case 3:
                func_80B01E84(this, 0);
                break;
            case 4:
                func_80B01E84(this, 3);
                break;
            case 5:
                func_80B01E84(this, 5);
                break;
            case 6:
                func_80B01E84(this, 2);
                break;
            case 8:
                func_80B01990(this, 10);
                break;
            case 9:
            case 11:
                func_80B01990(this, 7);
                break;
            case 10:
                func_80B01990(this, 13);
                break;
        }
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
}

void func_80B02234(EnGiant* this) {
    if (this->actor.draw != NULL && this->unk_24E > 0) {
        if (this->unk_248 == 8 && (func_801378B8(&this->skelAnime, 40.0f) || func_801378B8(&this->skelAnime, 100.0f))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KYOJIN_WALK);
        }
        if (this->unk_248 == 2 && func_801378B8(&this->skelAnime, 40.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KYOJIN_VOICE_FAIL);
        }
        if (this->sfxId != 0xFFFF &&
            ((this->unk_248 == 9 && this->skelAnime.animCurrentFrame >= 18.0f) || this->unk_248 == 0xA)) {
            func_800B9010(&this->actor, this->sfxId);
        }
        if ((this->unk_248 == 0xC && this->skelAnime.animCurrentFrame >= 18.0f) || this->unk_248 == 0xD) {
            func_800B9010(&this->actor, NA_SE_EV_KYOJIN_SIGN - SFX_FLAG);
        }
    }
}

void func_80B02354(EnGiant* this, GlobalContext* globalCtx, u32 arg2) {
    CsCmdActorAction* actorAction = globalCtx->csCtx.npcActions[arg2];
    f32 floatUnk10 = actorAction->unk10;
    s32 pad[2];
    f32 floatUnk1C = actorAction->unk1C;
    f32 functionTemp;

    functionTemp = func_800F5A8C(actorAction->endFrame, actorAction->startFrame, globalCtx->csCtx.frames, globalCtx);
    this->actor.world.pos.y = ((floatUnk1C - floatUnk10) * functionTemp) + floatUnk10;
}

void func_80B023D0(EnGiant* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, this->unk_24A)) {
        func_80B02354(this, globalCtx, func_800EE200(globalCtx, this->unk_24A));
        if (this->unk_24C != globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0) {
            this->unk_24C = globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0;
            func_80B01EE8(this);
        }
        func_80B020A0(this);
    }
    func_80B02234(this);
    if (this->unk_24C == 5) {
        func_800B9010(&this->actor, 0x1063);
    }
    func_80B0211C(this);
}

void func_80B024AC(EnGiant* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80B024D8(EnGiant* this, GlobalContext* globalCtx) {
    this->actor.draw = EnGiant_Draw;
    if (func_800EE29C(globalCtx, this->unk_24A)) {
        func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, this->unk_24A));
        if (this->unk_24C != globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0) {
            this->unk_24C = globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0;
            func_80B01EE8(this);
        }
        func_80B020A0(this);
    }
    if ((GIANT_TYPE(&this->actor) < GIANT_TYPE_MOUNTAIN_2) && (func_80B01A74(this) != 0)) {
        this->actor.draw = NULL;
    }
    func_80B02234(this);
    func_80B0211C(this);
}

void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGiant* this = THIS;
    s32 phi_v0;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (this->unk_296 == 0) {
        phi_v0 = 0;
    } else {
        this->unk_296--;
        phi_v0 = this->unk_296;
    }
    if (!phi_v0) {
        this->unk_296 = Rand_S16Offset(60, 60);
    }
    this->unk_294 = this->unk_296;
    if (this->unk_294 >= 3) {
        this->unk_294 = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B026C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Draw.s")
