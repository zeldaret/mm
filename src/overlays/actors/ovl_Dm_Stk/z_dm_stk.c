/*
 * File: z_dm_stk.c
 * Overlay: ovl_Dm_Stk
 * Description: Skull Kid (cutscene)
 */

#include "z_dm_stk.h"

#define FLAGS 0x02000030

#define THIS ((DmStk*)thisx)

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AA16F4(DmStk* this, GlobalContext* globalCtx);
void func_80AA1704(DmStk* this, GlobalContext* globalCtx);
void func_80AA1714(DmStk* this, GlobalContext* globalCtx);
void func_80AA17F8(DmStk* this, GlobalContext* globalCtx);
void func_80AA18D8(DmStk* this, GlobalContext* globalCtx);
void func_80AA192C(DmStk* this, GlobalContext* globalCtx);
void func_80AA1998(DmStk* this, GlobalContext* globalCtx);
void func_80AA19EC(DmStk* this, GlobalContext* globalCtx);
void func_80AA1A50(DmStk* this, GlobalContext* globalCtx);
void func_80AA1AC8(DmStk* this, GlobalContext* globalCtx);
void func_80AA1B9C(DmStk* this, GlobalContext* globalCtx);
void func_80AA1C64(DmStk* this, GlobalContext* globalCtx);
void func_80AA2720(DmStk* this, GlobalContext* globalCtx);
void func_80AA27EC(DmStk* this, GlobalContext* globalCtx);

extern AnimationHeader D_0600055C;
extern AnimationHeader D_06001030;
extern AnimationHeader D_0600130C;
extern AnimationHeader D_06001374;
extern AnimationHeader D_06001EDC;
extern AnimationHeader D_06002774;
extern AnimationHeader D_06002CD8;
extern AnimationHeader D_06003068;
extern AnimationHeader D_060035C8;
extern AnimationHeader D_060039F0;
extern AnimationHeader D_06004554;
extern AnimationHeader D_06004580;
extern Gfx D_060046B0[];
extern AnimationHeader D_060049C8;
extern AnimationHeader D_060051C0;
extern Gfx D_060053C0[];
extern Gfx D_06005870[];
extern AnimationHeader D_06005F44;
extern Gfx D_06006BB0[];
extern AnimationHeader D_060070DC;
extern Gfx D_06007840[];
extern Gfx D_060079F0[];
extern Gfx D_060084C0[];
extern UNK_TYPE D_06008658;
extern Gfx D_060087B0[];
extern Gfx D_06008A80[];
extern Gfx D_060090C0[];
extern Gfx D_06009710[];
extern Gfx D_06009AC0[];
extern Gfx D_06009DA0[];
extern Gfx D_0600A530[];
extern Gfx D_0600A5C0[];
extern Gfx D_0600AE30[];
extern Gfx D_0600AEC0[];
extern AnimationHeader D_0600BB2C;
extern AnimationHeader D_0600C270;
extern AnimationHeader D_0600C964;
extern Gfx D_0600CAD0[];
extern AnimationHeader D_0600CBB8;
extern AnimationHeader D_0600D830;
extern AnimationHeader D_0600E6EC;
extern AnimationHeader D_0600EEC0;
extern AnimationHeader D_060101A4;
extern AnimationHeader D_06010B60;
extern AnimationHeader D_060110B4;
extern AnimationHeader D_06011FB0;
extern AnimationHeader D_06012A58;
extern FlexSkeletonHeader D_06013328;
extern AnimationHeader D_060141E4;
extern AnimationHeader D_06014920;
extern AnimationHeader D_06015028;
extern AnimationHeader D_06015C14;
extern AnimationHeader D_06016508;
extern Gfx D_06016620[];
extern AnimationHeader D_06016910;
extern AnimationHeader D_06018ED0;
extern AnimationHeader D_0601AA80;
extern AnimationHeader D_0601C114;
extern AnimationHeader D_0601C21C;
extern AnimationHeader D_0601D008;
extern AnimationHeader D_0601D07C;
extern AnimationHeader D_0601D3D0;
extern AnimationHeader D_0601DDE0;
extern AnimationHeader D_0601EF50;
extern AnimationHeader D_0601F9E4;
extern AnimationHeader D_06020CAC;
extern AnimationHeader D_0602200C;
extern AnimationHeader D_0602336C;
extern AnimationHeader D_060259F4;
extern AnimationHeader D_060266C8;
extern AnimationHeader D_06026CF4;
extern AnimationHeader D_06027CF4;
extern AnimationHeader D_06028F28;
extern AnimationHeader D_06029A04;
extern AnimationHeader D_0602A2D8;
extern AnimationHeader D_0602AD54;
extern AnimationHeader D_0602DC64;
extern AnimationHeader D_0602E9A0;
extern AnimationHeader D_0602FA70;
extern AnimationHeader D_0603021C;
extern AnimationHeader D_06031210;
extern AnimationHeader D_060322FC;
extern AnimationHeader D_06032AE0;
extern AnimationHeader D_0603323C;
extern AnimationHeader D_06034FD8;
extern AnimationHeader D_06036964;
extern AnimationHeader D_06037B94;
extern AnimationHeader D_0603967C;
extern AnimationHeader D_0603A8F8;

const ActorInit Dm_Stk_InitVars = {
    ACTOR_DM_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER | AC_TYPE_ENEMY,
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
    { 14, 38, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(1, 0xF),
    /* Light ray      */ DMG_ENTRY(1, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0xF),
    /* Unblockable    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static ActorAnimationEntry sAnimations[] = {
    { &D_0601C21C, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_0601D3D0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06001030, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0601D008, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0601D008, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_06015C14, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060070DC, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_0600D830, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0600055C, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0600130C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0600C270, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0600CBB8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0601AA80, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0601D07C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06016910, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06018ED0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0601DDE0, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0601EF50, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0602DC64, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0602E9A0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0602DC64, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0602E9A0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060035C8, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_060049C8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060259F4, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_060266C8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06026CF4, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0601C114, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &D_06004580, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06020CAC, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0602200C, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0602336C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06002774, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06003068, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060101A4, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06010B60, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0602A2D8, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0601F9E4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &D_06029A04, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_0602AD54, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &D_0600BB2C, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0600C964, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060110B4, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06011FB0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06012A58, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_060141E4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0600E6EC, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0600EEC0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06027CF4, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06028F28, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0603323C, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_06031210, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_060322FC, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06032AE0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_0603021C, 1.0f, 0.0f, -1.0f, 0, 0.0f }, { &D_06036964, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &D_06016508, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06015028, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06014920, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0602FA70, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06037B94, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0603967C, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &D_0603967C, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_0603A8F8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06034FD8, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06005F44, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06002CD8, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_060039F0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06004554, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_060051C0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &D_06001374, 1.0f, 0.0f, -1.0f, 2, 0.0f }, { &D_06001EDC, 1.0f, 0.0f, -1.0f, 0, 0.0f },
};

void func_80A9FDB0(DmStk* this, GlobalContext* globalCtx) {
    s32 objectIdx;

    if (((this->unk_2E0 >= 0) && (this->unk_2E0 <= 5)) || (this->unk_2E0 == 32) || (this->unk_2E0 == 33) ||
        (this->unk_2E0 == 40) || (this->unk_2E0 == 41)) {
        objectIdx = this->unk_336;
    } else if (this->unk_2E0 > 64) {
        objectIdx = this->unk_338;
    } else {
        objectIdx = this->unk_337;
    }

    if (objectIdx >= 0) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[objectIdx].segment);
    }
}

void func_80A9FE3C(DmStk* this, GlobalContext* globalCtx, SkelAnime* skelAnime, ActorAnimationEntry* animation,
                   u16 index) {
    func_80A9FDB0(this, globalCtx);

    animation += index;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame,
                     (animation->frameCount < 0.0f) ? Animation_GetLastFrame(&animation->animation->common)
                                                    : animation->frameCount,
                     animation->mode, animation->morphFrames);
}

void func_80A9FED8(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames + 20) {
        case 1195:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
            break;

        case 1232:
        case 1241:
        case 1252:
        case 1255:
        case 1257:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 1285:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 1343:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 1410:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 1603:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 1610:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_REVERSE);
            break;

        case 2095:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_SURPRISED);
            break;

        case 2190:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_JUMP);
            break;

        case 2212:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;

        case 2214:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 2250:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL06_SURPRISED);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
            break;

        case 2255:
        case 2266:
        case 2277:
        case 2288:
        case 2299:
        case 2310:
        case 2321:
        case 2332:
        case 2343:
        case 2354:
        case 2365:
        case 2376:
        case 2387:
        case 2398:
        case 2409:
        case 2420:
        case 2431:
        case 2442:
        case 2453:
        case 2464:
        case 2475:
        case 2486:
        case 2497:
        case 2508:
        case 2519:
        case 2530:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;
    }
}

void func_80AA00CC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 535) {
        func_8019F128(NA_SE_EV_CLOCK_TOWER_BELL);
    }
}

void func_80AA0100(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 78:
        case 89:
        case 100:
        case 111:
        case 122:
        case 133:
        case 144:
        case 155:
        case 166:
        case 177:
        case 188:
        case 199:
        case 210:
        case 221:
        case 232:
        case 243:
        case 254:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 173:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;
    }
}

void func_80AA0158(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 18:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_GASAGOSO);
            break;

        case 90:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 142:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_EVIL_POWER);
            break;
    }
}

void func_80AA01C0(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 415:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 100);
            break;

        case 785:
            func_8019F128(NA_SE_SY_STALKIDS_PSYCHO);
            func_8019FE74(&D_801D6654, 0.0f, 150);
            break;

        case 560:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 890:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL21_PSYCHO_VOICE);
            break;
    }
}

void func_80AA0264(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (globalCtx->csCtx.frames) {
        case 10:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 50);
            break;

        case 71:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_BODY);
            break;

        case 365:
            func_801A0654(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 0);
            break;

        case 650:
            func_8019FE74(&D_801D6654, 0.0f, 80);
            break;

        case 265:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 126:
            Audio_PlayActorSound2(&player->actor, NA_SE_VO_DUMMY_150);
            break;

        case 197:
            Audio_PlayActorSound2(&player->actor, NA_SE_VO_DUMMY_134);
            break;

        case 207:
            Audio_PlayActorSound2(&player->actor, NA_SE_VO_DUMMY_135);
            break;

        case 217:
            Audio_PlayActorSound2(&player->actor, NA_SE_VO_DUMMY_136);
            break;
    }

    if (player) {}

    if ((globalCtx->csCtx.frames >= 263) && (globalCtx->csCtx.frames < 698)) {
        Audio_PlayActorSound2(&player->actor, NA_SE_EN_STALKIDS_BODY_LEV - SFX_FLAG);
    }
}

void func_80AA0420(DmStk* this, GlobalContext* globalCtx) {
    static s32 D_80AA3CB8 = 0;

    switch (globalCtx->csCtx.frames) {
        case 140:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 258:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_TURN);
            break;

        case 524:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 534:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 678:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if ((this->unk_2E0 == 31) && (globalCtx->csCtx.frames < 700)) {
        if (Animation_OnFrame(&this->skelAnime, 5.0f) || Animation_OnFrame(&this->skelAnime, 25.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA1);
        } else if (Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 40.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA2);
        }
    }

    if (globalCtx->csCtx.frames >= 700) {
        if (D_80AA3CB8 < 128) {
            if ((D_80AA3CB8 & 0x1F) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((D_80AA3CB8 & 0x1F) == 16) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }
            D_80AA3CB8++;
        }
    } else {
        D_80AA3CB8 = 0;
    }
}

void func_80AA05F0(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 3) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL06_SURPRISED);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    }
}

void func_80AA0634(DmStk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.frames >= 642) && (globalCtx->csCtx.frames < 845)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_NE_STAL23_COLD - SFX_FLAG);
    }
}

void func_80AA066C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 58:
        case 61:
        case 68:
        case 72:
        case 77:
        case 79:
            Audio_PlayActorSound2(&this->actor, NA_SE_PL_WALK_WATER2);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 186:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_NUTS_UP);
            break;

        case 230:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL22_LAUGH_KID_L);
            break;
    }
}

void func_80AA071C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 660:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;
    }
}

void func_80AA076C(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (globalCtx->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 45:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 93:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 245:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 269:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL11_LAUGH_SHY2);
            break;

        case 327:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 455:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 1730:
            Audio_QueueSeqCmd(0x141400FF);
            break;

        case 1395:
            func_800B8E58(&player->actor, NA_SE_VO_DUMMY_34);
            break;

        case 1850:
            Audio_QueueSeqCmd(0x42320000);
            break;

        case 2000:
            func_801A5BD0(0x7F);
            break;
    }

    if (this->unk_2E0 == 0) {
        if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 17.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }

        if (Animation_OnFrame(&this->skelAnime, 28.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
        }
    } else if (this->unk_2E0 == 71) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
            Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 18.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }
    } else if ((this->unk_2E0 == 70) &&
               (Animation_OnFrame(&this->skelAnime, 16.0f) || Animation_OnFrame(&this->skelAnime, 23.0f))) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_NOSE);
    }
}

void func_80AA09DC(DmStk* this, GlobalContext* globalCtx) {
    static s32 D_80AA3CBC = 0;

    switch (globalCtx->csCtx.frames) {
        case 40:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 234:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 244:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 388:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if (globalCtx->csCtx.frames >= 408) {
        if (D_80AA3CBC < 128) {
            if ((D_80AA3CBC & 0x1F) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((D_80AA3CBC & 0x1F) == 16) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }
            D_80AA3CBC++;
        }
    } else {
        D_80AA3CBC = 0;
    }
}

void func_80AA0B08(DmStk* this, GlobalContext* globalCtx) {
    this->unk_310.x = this->actor.projectedPos.x;
    this->unk_310.y = this->actor.projectedPos.y;
    this->unk_310.z = this->actor.projectedPos.z;

    switch (globalCtx->csCtx.frames) {
        case 64:
            func_8019F1C0(&this->unk_310, NA_SE_EN_STAL06_SURPRISED);
            break;

        case 327:
        case 332:
        case 335:
        case 344:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 367:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            break;

        case 470:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_HEADACHE);
            break;

        case 486:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            func_8019F1C0(&this->unk_310, NA_SE_EN_STAL08_CRY_BIG);
            break;

        case 496:
            func_8019F1C0(&this->unk_310, NA_SE_EN_STAL09_SCREAM);
            break;

        case 590:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 592:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 594:
            func_8019F1C0(&this->unk_310, NA_SE_EN_STAL24_SCREAM2);
            break;
    }

    if (1) {}

    if ((globalCtx->csCtx.frames >= 62) && (globalCtx->csCtx.frames < 273)) {
        if ((Rand_ZeroOne() < 0.75f) && ((globalCtx->state.frames % 2) != 0)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_EARTHQUAKE);
        }
    }

    if ((globalCtx->csCtx.frames >= 498) && (globalCtx->csCtx.frames < 577)) {
        if ((globalCtx->state.frames % 4) == 0) {
            if ((globalCtx->state.frames & 4) != 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            } else {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            }
        }
    }

    if (globalCtx->csCtx.frames >= 290) {
        func_8019F128(NA_SE_EV_KYOJIN_VOICE_SUCCESS - SFX_FLAG);
    }
}

void func_80AA0DA8(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 551:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 711:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 716:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

void func_80AA0E1C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 311:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 365:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 372:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

void func_80AA0E90(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0) {
        switch (globalCtx->sceneNum) {
            case SCENE_LOST_WOODS:
                if (gSaveContext.sceneSetupIndex == 1) {
                    func_80A9FED8(this, globalCtx);
                } else if (gSaveContext.sceneSetupIndex == 0) {
                    func_80AA0100(this, globalCtx);
                } else if ((gSaveContext.sceneSetupIndex == 2) && (globalCtx->csCtx.unk_12 == 0)) {
                    func_80AA0158(this, globalCtx);
                }
                break;

            case SCENE_CLOCKTOWER:
                if (gSaveContext.sceneSetupIndex == 1) {
                    func_80AA00CC(this, globalCtx);
                }
                break;

            case SCENE_OPENINGDAN:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.unk_12 == 0) {
                        func_80AA01C0(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 1) {
                        func_80AA0264(this, globalCtx);
                    }
                }
                break;

            case SCENE_OKUJOU:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.unk_12 == 0) {
                        func_80AA0420(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 1) {
                        func_80AA05F0(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 2) {
                        func_80AA09DC(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 3) {
                        func_80AA0B08(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 2) {
                    if (globalCtx->csCtx.unk_12 == 0) {
                        func_80AA0DA8(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 1) {
                        func_80AA0E1C(this, globalCtx);
                    }
                }
                break;

            case SCENE_00KEIKOKU:
                if (gSaveContext.sceneSetupIndex == 3) {
                    if (globalCtx->csCtx.unk_12 == 0) {
                        func_80AA0634(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 2) {
                        func_80AA066C(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 7) {
                    if (globalCtx->csCtx.unk_12 == 0) {
                        func_80AA071C(this, globalCtx);
                    } else if (globalCtx->csCtx.unk_12 == 1) {
                        func_80AA076C(this, globalCtx);
                    }
                }
                break;
        }
    }

    if (this->unk_2E0 == 1) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_WALK);
        }
    } else if (this->unk_2E0 == 19) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 13.0f) ||
            Animation_OnFrame(&this->skelAnime, 20.0f) || Animation_OnFrame(&this->skelAnime, 27.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_PL_CALM_HIT);
        }
    } else if (this->unk_2E0 == 14) {
        if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_PL_PUT_OUT_ITEM);
        }
    } else if (this->unk_2E0 == 15) {
        if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_UNSKILLFUL_OCARINA);
        }

        if (Animation_OnFrame(&this->skelAnime, 45.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL01_LAUGH);
        }
    }
}

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmStk* this = THIS;

    this->unk_33B = 1;
    if (this->actor.params != 1) {
        this->unk_33A = 0;
        this->unk_336 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK);
        this->unk_337 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK2);
        this->unk_338 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK3);
        if (this->unk_336 < 0) {
            Actor_MarkForDeath(&this->actor);
        }

        this->unk_328 = 0;
        this->unk_339 = 0;
        this->unk_32C = 1;
        this->unk_2E0 = 3;
        this->unk_2E8 = globalCtx->lightCtx.unk7;
        this->unk_2EC = globalCtx->lightCtx.unk8;
        this->unk_2F0 = globalCtx->lightCtx.unk9;

        if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
            this->unk_2E4 = 0;
            this->unk_2F8 = 0;
            this->unk_2FC = 1000;
            this->unk_300 = 1.0f;
            this->actionFunc = func_80AA1704;
        } else if (globalCtx->sceneNum == SCENE_OKUJOU) {
            this->unk_2E4 = 255;
            this->unk_2F8 = 996;
            this->unk_2FC = 1000;
            this->unk_300 = 0.7f;
            this->unk_335 = 0;

            Collider_InitCylinder(globalCtx, &this->collider);

            if (gSaveContext.entranceIndex == 0x2C00) {
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        func_8010E9F0(3, 300);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }

                    if (gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = func_80AA18D8;
                    } else {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = func_80AA1998;
                    }

                } else if (gSaveContext.sceneSetupIndex == 3) {
                    this->unk_2E0 = 38;
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        func_8010E9F0(3, 60);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }
                    this->actor.world.pos.y = 120.0f;
                    sCylinderInit.base.colType = COLTYPE_WOOD;
                    this->actionFunc = func_80AA27EC;
                } else {
                    this->unk_2E0 = 38;
                    this->actionFunc = func_80AA16F4;
                }
            } else {
                this->unk_33A = 1;
                this->unk_2E0 = 38;
                this->actor.world.pos.y = 120.0f;
                sCylinderInit.base.colType = COLTYPE_WOOD;
                this->actionFunc = func_80AA27EC;
            }

            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

        } else if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 0)) {
            if (!(globalCtx->actorCtx.unk5 & 2)) {
                Actor_MarkForDeath(&this->actor);
            }
            this->unk_32C = 2;
            this->unk_2E4 = 255;
            this->unk_2F8 = 996;
            this->unk_2FC = 1000;
            this->unk_300 = 0.7f;
            this->unk_2E0 = 5;
            this->actionFunc = func_80AA1714;
        } else {
            if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && !Cutscene_IsPlayingCs(globalCtx)) {
                Actor_MarkForDeath(&this->actor);
            }
            this->unk_32C = 2;
            this->unk_2E4 = 255;
            this->unk_2F8 = 996;
            this->unk_2FC = 1000;
            this->unk_300 = 0.7f;
            this->actionFunc = func_80AA1704;
        }

        this->unk_32D = 9;
        this->unk_32E = 0;
        this->unk_32F = 0;
        this->unk_330 = 0;
        this->unk_2E4 = this->unk_2E4;
        this->actor.targetArrowOffset = 1100.0f;
        this->unk_334 = 99;
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06013328, NULL, NULL, NULL, 0);
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
    }

    Actor_SetScale(&this->actor, 0.01f);

    if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (globalCtx->csCtx.unk_12 > 0)) {
        globalCtx->envCtx.unk_17 = 15;
        globalCtx->envCtx.unk_18 = 15;
    }
}

void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AA16F4(DmStk* this, GlobalContext* globalCtx) {
}

void func_80AA1704(DmStk* this, GlobalContext* globalCtx) {
}

void func_80AA1714(DmStk* this, GlobalContext* globalCtx) {
    Vec3f sp1C;

    if (!(gSaveContext.weekEventReg[74] & 0x20)) {
        func_80169474(globalCtx, &this->actor.world.pos, &sp1C);
        if (globalCtx->view.fovy < 25.0f) {
            if ((sp1C.x >= 70.0f) && (sp1C.x < 250.0f) && (sp1C.y >= 30.0f) && (sp1C.y < 210.0f)) {
                func_800FE484();
                this->actionFunc = func_80AA17F8;
            }
        }
    }
}

void func_80AA17F8(DmStk* this, GlobalContext* globalCtx) {
    s16 sp1E = this->actor.cutscene;
    s16 sp1C = ActorCutscene_GetAdditionalCutscene(sp1E);
    s16 sp18 = ActorCutscene_GetAdditionalCutscene(sp1C);
    s16 cutscene;

    if (gSaveContext.day < 3) {
        cutscene = sp1E;
    } else if ((gSaveContext.weekEventReg[8] & 0x40) ||
               ((CURRENT_DAY == 3) && (gSaveContext.time < CLOCK_TIME(6, 0)))) {
        cutscene = sp18;
    } else {
        cutscene = sp1C;
    }

    if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_Start(cutscene, &this->actor);
        func_800FE498();
        this->actionFunc = func_80AA1704;
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

void func_80AA18D8(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(9)) {
        ActorCutscene_Start(9, &this->actor);
        this->actionFunc = func_80AA192C;
    } else {
        ActorCutscene_SetIntentToPlay(9);
    }
}

void func_80AA192C(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->unk_2E0 = 33;
        this->unk_32D = 3;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
        this->actionFunc = func_80AA2720;
    }
}

void func_80AA1998(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(0xB)) {
        ActorCutscene_Start(0xB, &this->actor);
        this->actionFunc = func_80AA19EC;
    } else {
        ActorCutscene_SetIntentToPlay(0xB);
    }
}

void func_80AA19EC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->unk_2E0 = 38;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
        this->actionFunc = func_80AA27EC;
    }
}

void func_80AA1A50(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(0xA)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_DAMAGE);
        ActorCutscene_Start(0xA, &this->actor);
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        this->actor.shape.rot.y = this->actor.shape.rot.x;
        this->actor.world.rot.y = this->actor.shape.rot.x;
        this->actionFunc = func_80AA1AC8;
    } else {
        ActorCutscene_SetIntentToPlay(0xA);
    }
}

void func_80AA1AC8(DmStk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (globalCtx->csCtx.frames > 20)) {
        this->actionFunc = func_80AA27EC;
    }
}

void func_80AA1AF8(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sin;

    this->unk_32A += 0x4B0;
    sin = Math_SinS(this->unk_32A) * 10.0f;
    Math_SmoothStepToF(&this->actor.world.pos.y, 160.0f + sin, 0.2f, 1.0f, 0.0001f);

    this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->actor.world.rot.x = 0x1B58;
    this->actor.shape.rot.x = this->actor.world.rot.x;
}

void func_80AA1B9C(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80AA1AF8(this, globalCtx);
    this->unk_339++;
    if (this->unk_339 >= 3) {
        this->unk_339 = 0;
        if (!(player->stateFlags2 & 0x8000000)) {
            Message_StartTextbox(globalCtx, 0x2013, &this->actor);
        }
    }

    this->unk_2E0 = 39;
    func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    this->actionFunc = func_80AA1C64;
}

void func_80AA1C64(DmStk* this, GlobalContext* globalCtx) {
    func_80AA1AF8(this, globalCtx);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_2E0 = 38;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
        this->actionFunc = func_80AA27EC;
    }

    if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->actionFunc = func_80AA1B9C;
    }
}

void func_80AA1D1C(DmStk* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp_v0;

    if (func_800EE29C(globalCtx, 0x6B)) {
        temp_v0 = func_800EE200(globalCtx, 0x6B);

        if (globalCtx->csCtx.frames == globalCtx->csCtx.npcActions[temp_v0]->startFrame) {
            if (this->unk_334 != globalCtx->csCtx.npcActions[temp_v0]->action) {
                this->unk_334 = globalCtx->csCtx.npcActions[temp_v0]->action;
                if (globalCtx->sceneNum == SCENE_CLOCKTOWER) {
                    this->unk_32D = 6;
                } else {
                    this->unk_32D = 9;
                }

                switch (globalCtx->csCtx.npcActions[temp_v0]->action) {
                    case 0:
                    case 1:
                        this->unk_2E0 = 3;
                        break;

                    case 2:
                        this->unk_2E0 = 1;
                        break;

                    case 3:
                        this->unk_2E0 = 20;
                        break;

                    case 4:
                        this->unk_2E0 = 18;
                        break;

                    case 6:
                        this->unk_2E0 = 16;
                        this->unk_32D = 3;
                        break;

                    case 7:
                        this->unk_2E0 = 14;
                        this->unk_32D = 3;
                        break;

                    case 8:
                        this->unk_2E0 = 0;
                        break;

                    case 9:
                        this->unk_2E0 = 3;
                        this->unk_32E = 1;
                        break;

                    case 12:
                        this->unk_2E0 = 12;
                        this->unk_32D = 3;
                        break;

                    case 13:
                        this->unk_2E0 = 27;
                        this->unk_32D = 3;
                        break;

                    case 14:
                        this->unk_2E0 = 22;
                        break;

                    case 15:
                        this->unk_2E0 = 23;
                        break;

                    case 16:
                        this->unk_2E0 = 28;
                        break;

                    case 17:
                        this->unk_2E0 = 7;
                        break;

                    case 18:
                        this->unk_2E0 = 8;
                        break;

                    case 19:
                        this->unk_2E0 = 10;
                        break;

                    case 20:
                        this->unk_2E0 = 24;
                        break;

                    case 21:
                        this->unk_2E0 = 26;
                        break;

                    case 22:
                        this->unk_2E0 = 29;
                        if (gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->unk_32D = 3;
                        }
                        break;

                    case 23:
                        this->unk_2E0 = 30;
                        this->unk_32D = 4;
                        break;

                    case 24:
                        this->unk_2E0 = 32;
                        if (gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->unk_32D = 3;
                        }
                        break;

                    case 25:
                        Actor_MarkForDeath(&this->actor);
                        break;

                    case 26:
                        this->unk_2E0 = 34;
                        if (gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->unk_32D = 3;
                        }
                        break;

                    case 27:
                        this->unk_2E0 = 36;
                        if (gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->unk_32D = 3;
                        }
                        break;

                    case 28:
                        this->unk_2E0 = 37;
                        this->unk_32D = 4;
                        break;

                    case 30:
                        this->unk_2E0 = 38;
                        break;

                    case 31:
                        this->unk_2E0 = 39;
                        break;

                    case 32:
                        this->unk_2E0 = 42;
                        break;

                    case 33:
                        this->unk_2E0 = 44;
                        break;

                    case 34:
                        this->unk_2E0 = 46;
                        break;

                    case 35:
                        this->unk_2E0 = 48;
                        break;

                    case 36:
                        this->unk_2E0 = 50;
                        break;

                    case 37:
                        this->unk_2E0 = 51;
                        break;

                    case 38:
                        this->unk_2E0 = 52;
                        break;

                    case 39:
                        this->unk_2E0 = 54;
                        break;

                    case 40:
                        this->unk_2E0 = 55;
                        break;

                    case 41:
                        this->unk_2E0 = 40;
                        break;

                    case 42:
                        this->unk_2E0 = 5;
                        break;

                    case 43:
                        this->unk_2E0 = 56;
                        break;

                    case 44:
                        this->unk_2E0 = 57;
                        break;

                    case 45:
                        this->unk_2E0 = 58;
                        this->unk_32F = 1;
                        break;

                    case 46:
                        this->unk_32D = 6;
                        this->unk_2E0 = 59;
                        break;

                    case 47:
                        this->unk_2E0 = 60;
                        break;

                    case 48:
                        this->unk_2E0 = 60;
                        break;

                    case 49:
                        this->unk_2E0 = 65;
                        break;

                    case 50:
                        this->unk_2E0 = 66;
                        break;

                    case 51:
                        this->unk_2E0 = 68;
                        break;

                    case 52:
                        this->unk_2E0 = 70;
                        break;

                    case 53:
                        this->unk_2E0 = 60;
                        break;

                    case 54:
                        this->unk_2E0 = 61;
                        break;

                    case 55:
                        this->unk_2E0 = 62;
                        break;

                    case 56:
                        this->unk_2E0 = 64;
                        break;

                    case 57:
                        this->unk_2E0 = 65;
                        break;

                    case 58:
                        this->unk_2E0 = 66;
                        break;

                    case 59:
                        this->unk_2E0 = 68;
                        break;

                    case 60:
                        this->unk_2E0 = 70;
                        break;

                    case 5:
                    case 10:
                        break;

                    default:
                        this->unk_2E0 = 0;
                        break;
                }

                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
            }
        }

        func_800EDF24(&this->actor, globalCtx, temp_v0);
    } else {
        this->unk_334 = 99;
    }

    if (this->unk_32E == 1) {
        Math_SmoothStepToF(&this->unk_300, 0.7f, 0.1f, 0.007f, 0.005f);
        if (this->unk_300 < 0.71f) {
            this->unk_300 = 0.7f;
            this->unk_2F8 = 800;
            this->unk_32E++;
        }
        this->unk_2E8 = globalCtx->lightCtx.unk7 * this->unk_300;
        this->unk_2EC = globalCtx->lightCtx.unk8 * this->unk_300;
        this->unk_2F0 = globalCtx->lightCtx.unk9 * this->unk_300;

    } else if (this->unk_32E == 2) {
        if (this->unk_2F8 < 996) {
            this->unk_2F8 += 10;
        }

        if (this->unk_2F8 > 996) {
            this->unk_32E++;
            this->unk_2F8 = 996;
        }
    } else if (this->unk_32E == 3) {
        if (this->unk_2E4 < 128) {
            this->unk_2E4 += 3;
        }

        if (this->unk_2E4 < 255) {
            this->unk_2E4 += 20;
        } else {
            this->unk_2E4 = 255;
            this->unk_32E = 0;
        }
    }

    if (this->unk_32F == 1) {
        if (this->unk_330 > 40) {
            this->unk_32C = 3;
        }

        this->unk_330++;
        if (this->unk_330 >= 44) {
            this->unk_2E4 -= 35;
            if (this->unk_2E4 < 0) {
                this->unk_2E4 = 0;
                this->unk_32F = 0;
                gSaveContext.weekEventReg[12] |= 4;
                if (!(globalCtx->actorCtx.unk5 & 2)) {
                    Actor_MarkForDeath(&this->actor);
                } else {
                    this->unk_33B = 0;
                }
            }
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->unk_2E0) {
            case 2:
            case 8:
            case 10:
            case 12:
            case 14:
            case 16:
            case 18:
            case 20:
            case 22:
            case 24:
            case 30:
            case 32:
            case 34:
            case 40:
            case 42:
            case 44:
            case 46:
            case 48:
            case 52:
            case 62:
            case 66:
            case 68:
            case 70:
                this->unk_2E0++;
                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
                break;

            case 26:
                this->unk_2E0 = 3;
                this->unk_32C = 1;
                this->unk_32D = 9;
                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->unk_2E0], 0);
                break;
        }
    }

    if (((this->unk_2E0 == 24) && (this->skelAnime.curFrame >= 16.0f)) || (this->unk_2E0 == 25) ||
        (this->unk_2E0 == 26)) {
        this->unk_32C = 9;
        this->unk_32D = 2;
    } else if (((this->unk_2E0 >= 50) && (this->unk_2E0 < 56)) || ((this->unk_2E0 > 58) && (this->unk_2E0 <= 60)) ||
               ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 7))) {
        this->unk_32C = 0;
        if ((this->unk_2E0 == 52) || (this->unk_2E0 == 53)) {
            this->unk_32D = 5;
        }
    }

    if (this->unk_2E0 == 64) {
        this->unk_32C = 0;
    }
}

void func_80AA26CC(DmStk* this, GlobalContext* globalCtx) {
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80AA2720(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->csCtx.state == 0) {
        func_80AA1AF8(this, globalCtx);
        this->actor.flags |= 1;
        this->unk_328++;
        if (this->unk_328 > 800) {
            this->unk_328 = 0;
            if (!(player->stateFlags2 & 0x8000000)) {
                Message_StartTextbox(globalCtx, 0x2014, &this->actor);
            }
        }
        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->unk_335 = 1;
            this->actionFunc = func_80AA1A50;
        }
    }
}

void func_80AA27EC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        func_80AA1AF8(this, globalCtx);
        this->actor.flags |= 1;

        if (this->unk_2E0 == 33) {
            this->actor.targetArrowOffset = 3100.0f;
        } else {
            this->actor.targetArrowOffset = 200.0f;
        }

        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->unk_335 = 1;
            this->actionFunc = func_80AA1B9C;
        }
    }
}

void DmStk_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmStk* this = THIS;
    u16 time;

    if (this->actor.params != 1) {
        if (this->unk_2E0 == 33) {
            Actor_SetHeight(&this->actor, 40.0f);
        } else {
            Actor_SetHeight(&this->actor, 6.0f);
        }

        func_80A9FDB0(this, globalCtx);

        if (this->unk_2E0 != 61) {
            SkelAnime_Update(&this->skelAnime);
        }

        this->unk_2E4 = this->unk_2E4;

        this->actionFunc(this, globalCtx);

        if (globalCtx->sceneNum == SCENE_OKUJOU) {
            func_80AA26CC(this, globalCtx);
        }

        func_80AA1D1C(this, globalCtx);
        func_80AA0E90(this, globalCtx);

        switch (this->unk_33A) {
            case 1:
                if (func_800B8718(&this->actor, globalCtx)) {
                    this->unk_33A = 2;
                } else {
                    func_800B874C(&this->actor, globalCtx, this->actor.xzDistToPlayer,
                                  fabsf(this->actor.playerHeightRel));
                }
                break;

            case 2:
                if (ActorCutscene_GetCanPlayNext(0x10)) {
                    this->unk_33A = 3;
                    ActorCutscene_Start(0x10, &this->actor);
                    this->actionFunc = func_80AA27EC;
                } else {
                    ActorCutscene_SetIntentToPlay(0x10);
                }
                break;

            case 3:
                if (globalCtx->csCtx.state == 0) {
                    this->unk_33A = 4;
                }
                break;
        }

        if ((globalCtx->actorCtx.unk5 & 2) && (globalCtx->msgCtx.unk11F22 != 0) &&
            (globalCtx->msgCtx.unk11F04 == 0x5E6) && !FrameAdvance_IsEnabled(globalCtx) &&
            (globalCtx->sceneLoadFlag == 0) && (ActorCutscene_GetCurrentIndex() == -1) &&
            (globalCtx->csCtx.state == 0)) {
            time = gSaveContext.time;
            gSaveContext.time = (u16)REG(15) + time;
            if (REG(15) != 0) {
                time = gSaveContext.time;
                gSaveContext.time = (u16)gSaveContext.unk_14 + time;
            }
        }
    }

    if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (globalCtx->csCtx.unk_12 > 0)) {
        globalCtx->envCtx.unk_17 = 15;
        globalCtx->envCtx.unk_18 = 15;
    }
}

s32 DmStk_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    if (limbIndex == 15) {
        if ((this->unk_32D == 0) || (this->unk_32D == 1) || (this->unk_32D == 3)) {
            *dList = NULL;
        }
    } else if (limbIndex == 12) {
        switch (this->unk_32D) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
                *dList = NULL;
                break;

            case 9:
                if (this->unk_2E4 == 255) {
                    *dList = NULL;
                }
                break;
        }
    } else if (limbIndex == 17) {
        *dList = NULL;
    }

    return false;
}

void DmStk_PostLimbDraw2(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    s32 pad2;
    DmStk* this = THIS;

    if (limbIndex == 17) {
        Matrix_GetStateTranslation(&this->unk_304);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((this->unk_2E0 == 69) || (this->unk_2E0 == 11) || (this->unk_2E0 == 71)) {
            gSPDisplayList(POLY_OPA_DISP++, D_0600AEC0);
            gSPDisplayList(POLY_OPA_DISP++, D_0600AE30);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, D_0600A5C0);
            gSPDisplayList(POLY_OPA_DISP++, D_0600A530);
        }

        switch (this->unk_32C) {
            case 0:
                break;

            case 1:
                if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1) &&
                    (globalCtx->csCtx.frames < 1400)) {
                    if (this->unk_2F8 == this->unk_2FC) {
                        this->unk_2FC = this->unk_2F8;
                    }
                    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, this->unk_2E8, this->unk_2EC, this->unk_2F0,
                                               this->unk_2F4, this->unk_2F8, this->unk_2FC);
                    gSPDisplayList(POLY_OPA_DISP++, D_06006BB0);
                    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
                } else {
                    gSPDisplayList(POLY_OPA_DISP++, D_06006BB0);
                }
                break;

            case 2:
                gSPDisplayList(POLY_OPA_DISP++, D_06006BB0);
                gSPDisplayList(POLY_OPA_DISP++, D_06005870);

                if (func_800EE29C(globalCtx, 0x201) &&
                    (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x201)]->action == 2) &&
                    (this->unk_337 >= 0)) {
                    Matrix_StatePush();
                    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);
                    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_337].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->unk_337].segment);

                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06008658));
                    func_800BDFC0(globalCtx, D_06007840);
                    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_336].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->unk_336].segment);

                    Matrix_StatePop();
                }
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

    } else if (limbIndex == 15) {

        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (this->unk_32D != 5) {
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }

        switch (this->unk_32D) {
            case 0:
                gSPDisplayList(POLY_OPA_DISP++, D_06009AC0);
                gSPDisplayList(POLY_OPA_DISP++, D_060046B0);
                break;

            case 1:
                gSPDisplayList(POLY_OPA_DISP++, D_06009710);
                gSPDisplayList(POLY_OPA_DISP++, D_060053C0);
                break;

            case 3:
                gSPDisplayList(POLY_OPA_DISP++, D_06009DA0);

                if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, D_0600CAD0);
                }
                break;

            case 5:
                Matrix_InsertTranslation(-20.0f, -660.0f, 860.0f, MTXMODE_APPLY);
                Matrix_RotateY(0x6142, MTXMODE_APPLY);
                Matrix_InsertXRotation_s(-0x1988, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, D_06006BB0);
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

    } else if (limbIndex == 12) {

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        switch (this->unk_32D) {
            case 0:
                break;

            case 1:
                gSPDisplayList(POLY_OPA_DISP++, D_060084C0);
                break;

            case 2:
                gSPDisplayList(POLY_OPA_DISP++, D_060090C0);
                gSPDisplayList(POLY_OPA_DISP++, D_060079F0);
                break;

            case 3:
                if ((globalCtx->sceneNum != SCENE_LOST_WOODS) || (gSaveContext.sceneSetupIndex != 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, D_0600CAD0);
                }
                gSPDisplayList(POLY_OPA_DISP++, D_060090C0);
                break;

            case 4:
                gSPDisplayList(POLY_OPA_DISP++, D_060090C0);
                break;

            case 6:
                gSPDisplayList(POLY_OPA_DISP++, D_06008A80);
                gSPDisplayList(POLY_OPA_DISP++, D_06016620);
                break;

            case 9:
                if (this->unk_2E4 == 255) {
                    gSPDisplayList(POLY_OPA_DISP++, D_060087B0);
                }
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void DmStk_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    DmStk_PostLimbDraw2(globalCtx, limbIndex, dList, rot, &this->actor, NULL);
}

void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmStk* this = THIS;

    if (this->unk_33B != 0) {
        if (this->actor.params == 1) {
            func_800BDFC0(globalCtx, D_06006BB0);
            return;
        }

        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_336].segment);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        this->unk_2E4 = this->unk_2E4;
        func_8012C28C(globalCtx->state.gfxCtx);

        if (this->unk_2E4 < 255) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            Scene_SetRenderModeXlu(globalCtx, 1, 2);

            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_2E4);

            POLY_XLU_DISP =
                SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, DmStk_PostLimbDraw2, &this->actor, POLY_XLU_DISP);
        } else {
            Scene_SetRenderModeXlu(globalCtx, 0, 1);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, DmStk_OverrideLimbDraw, DmStk_PostLimbDraw, &this->actor);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
