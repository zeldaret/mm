/*
 * File: z_en_osn.c
 * Overlay: ovl_En_Osn
 * Description: Happy Mask Salesman
 */

#include "z_en_osn.h"
#include "objects/object_osn/object_osn.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnOsn*)thisx)

void EnOsn_Init(Actor* thisx, PlayState* play);
void EnOsn_Destroy(Actor* thisx, PlayState* play);
void EnOsn_Update(Actor* thisx, PlayState* play);
void EnOsn_Draw(Actor* thisx, PlayState* play);

typedef enum {
    /*  0 */ OSN_ANIM_IDLE,
    /*  1 */ OSN_ANIM_ARMS_OUT,
    /*  2 */ OSN_ANIM_BOWING,
    /*  3 */ OSN_ANIM_REMINISCE,
    /*  4 */ OSN_ANIM_HANDS_CLASPED,
    /*  5 */ OSN_ANIM_BELIEVE,
    /*  6 */ OSN_ANIM_THINK,
    /*  7 */ OSN_ANIM_SHAKE_HEAD,
    /*  8 */ OSN_ANIM_ORGAN_TALK,
    /*  9 */ OSN_ANIM_ORGAN_PLAY,
    /* 10 */ OSN_ANIM_SHAKE,
    /* 11 */ OSN_ANIM_CHOKE,
    /* 12 */ OSN_ANIM_DESPAIR,
    /* 13 */ OSN_ANIM_FAST_BOWS,
    /* 14 */ OSN_ANIM_HAND_OUT,
    /* 15 */ OSN_ANIM_LYING_DOWN_FACE_UP,
    /* 16 */ OSN_ANIM_LYING_DOWN_FACE_DOWN,
    /* 17 */ OSN_ANIM_MASK_LOOK_AT,
    /* 18 */ OSN_ANIM_TURN_AROUND_START,
    /* 19 */ OSN_ANIM_TURN_AROUND_LOOP,
    /* 20 */ OSN_ANIM_WALK_AWAY,
    /* 21 */ OSN_ANIM_MASK_LOOK_FROM_START,
    /* 22 */ OSN_ANIM_MASK_LOOK_FROM_LOOP,
    /* 23 */ OSN_ANIM_HAND_OUT_2,    // Exact same as OSN_ANIM_HAND_OUT
    /* 24 */ OSN_ANIM_WALK_AWAY_END, // Only the last frame of OSN_ANIM_WALK_AWAY
    /* 25 */ OSN_ANIM_MAX
} OsnAnimation;

ActorInit En_Osn_InitVars = {
    ACTOR_EN_OSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OSN,
    sizeof(EnOsn),
    (ActorFunc)EnOsn_Init,
    (ActorFunc)EnOsn_Destroy,
    (ActorFunc)EnOsn_Update,
    (ActorFunc)EnOsn_Draw,
};

static AnimationInfo sAnimationInfo[] = {
    { &gHappyMaskSalesmanIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanArmsOutAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanBowingAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanReminisceAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanHandsClaspedAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanBelieveAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanThinkAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanShakeHeadAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmOrganTalkAnim, 1.0f, 1.0f, 39.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanOrganPlayAnim, 1.0f, 1.0f, 70.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanShakeAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanChokeAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanDespairAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanFastBowsAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanHandOutAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanLyingDownAnim, 0.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gHappyMaskSalesmanLyingDownAnim, 0.0f, 1.0f, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gHappyMaskSalesmanMaskLookAtAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanTurnStartAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gHappyMaskSalesmanTurnLoopAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanWalkAwayAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gHappyMaskSalesmanMaskLookFromStartAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gHappyMaskSalesmanMaskLookFromLoopAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanHandOutAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gHappyMaskSalesmanWalkAwayAnim, 0.0f, 77.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

void func_80AD1634(EnOsn*, PlayState*);
void func_80AD16A8(EnOsn*, PlayState*);
void func_80AD14C8(EnOsn*, PlayState*);
void func_80AD19A0(EnOsn* this, PlayState* play);

void EnOsn_UpdateCollider(EnOsn* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

s32 func_80AD08B0(PlayState* play) {
    switch (Player_GetMask(play)) {
        case PLAYER_MASK_GREAT_FAIRY:
            return 0x1FD6;

        case PLAYER_MASK_GIBDO:
            return 0x1FD8;

        case PLAYER_MASK_TRUTH:
            return 0x1FDA;

        case PLAYER_MASK_GIANT:
            return 0x1FDC;

        case PLAYER_MASK_KAFEIS_MASK:
            return 0x1FDE;

        case PLAYER_MASK_DON_GERO:
            return 0x1FE0;

        case PLAYER_MASK_BLAST:
            return 0x1FE2;

        case PLAYER_MASK_COUPLE:
            return 0x1FE4;

        case PLAYER_MASK_SCENTS:
            return 0x1FE6;

        case PLAYER_MASK_KAMARO:
            return 0x1FE8;

        case PLAYER_MASK_STONE:
            return 0x1FEA;

        case PLAYER_MASK_POSTMAN:
            return 0x1FEC;

        case PLAYER_MASK_BUNNY:
            return 0x1FEE;

        case PLAYER_MASK_CAPTAIN:
            return 0x1FF0;

        case PLAYER_MASK_BREMEN:
            return 0x1FF2;

        case PLAYER_MASK_CIRCUS_LEADER:
            return 0x1FF4;

        case PLAYER_MASK_KEATON:
            return 0x1FF6;

        case PLAYER_MASK_GARO:
            return 0x1FF8;

        case PLAYER_MASK_ALL_NIGHT:
            return 0x1FFA;

        case PLAYER_MASK_ROMANI:
            return 0x1FFC;

        default:
            return 0;
    }
}

void func_80AD0998(EnOsn* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animIndex].animation);

    if ((this->animIndex == OSN_ANIM_TURN_AROUND_START) && (curFrame == lastFrame)) {
        this->animIndex = OSN_ANIM_TURN_AROUND_LOOP;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, OSN_ANIM_TURN_AROUND_LOOP);
    }
}

void func_80AD0A24(EnOsn* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animIndex].animation);

    if ((this->animIndex == OSN_ANIM_MASK_LOOK_FROM_START) && (curFrame == lastFrame)) {
        this->animIndex = OSN_ANIM_MASK_LOOK_FROM_LOOP;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, OSN_ANIM_MASK_LOOK_FROM_LOOP);
    }
}

void func_80AD0AB0(EnOsn* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animIndex].animation);

    if (curFrame == lastFrame) {
        this->alpha -= 8;
        if (this->alpha < 8) {
            this->alpha = 0;
            Actor_Kill(&this->actor);
        }
    }
}

s32 func_80AD0B38(EnOsn* this, PlayState* play) {
    switch (Player_GetMask(play)) {
        case PLAYER_MASK_GREAT_FAIRY:
            if (!(this->unk_1F6 & 1)) {
                this->unk_1F6 |= 1;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_GIBDO:
            if (!(this->unk_1F6 & 2)) {
                this->unk_1F6 |= 2;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_TRUTH:
            if (!(this->unk_1F6 & 4)) {
                this->unk_1F6 |= 4;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_GIANT:
            if (!(this->unk_1F6 & 8)) {
                this->unk_1F6 |= 8;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_KAFEIS_MASK:
            if (!(this->unk_1F6 & 0x10)) {
                this->unk_1F6 |= 0x10;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_DON_GERO:
            if (!(this->unk_1F6 & 0x20)) {
                this->unk_1F6 |= 0x20;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_BLAST:
            if (!(this->unk_1F6 & 0x40)) {
                this->unk_1F6 |= 0x40;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_COUPLE:
            if (!(this->unk_1F6 & 0x80)) {
                this->unk_1F6 |= 0x80;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_SCENTS:
            if (!(this->unk_1F6 & 0x100)) {
                this->unk_1F6 |= 0x100;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_KAMARO:
            if (!(this->unk_1F6 & 0x200)) {
                this->unk_1F6 |= 0x200;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_STONE:
            if (!(this->unk_1F6 & 0x400)) {
                this->unk_1F6 |= 0x400;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_POSTMAN:
            if (!(this->unk_1F6 & 0x800)) {
                this->unk_1F6 |= 0x800;
                return 0x1FD2;
            }
            break;

        case PLAYER_MASK_BUNNY:
            if (!(this->unk_1F6 & 0x1000)) {
                this->unk_1F6 |= 0x1000;
                return 0x1FD2;
            }
            break;

        case PLAYER_MASK_CAPTAIN:
            if (!(this->unk_1F6 & 0x2000)) {
                this->unk_1F6 |= 0x2000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_BREMEN:
            if (!(this->unk_1F6 & 0x4000)) {
                this->unk_1F6 |= 0x4000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_CIRCUS_LEADER:
            if (!(this->unk_1F6 & 0x8000)) {
                this->unk_1F6 |= 0x8000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_KEATON:
            if (!(this->unk_1F6 & 0x10000)) {
                this->unk_1F6 |= 0x10000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_GARO:
            if (!(this->unk_1F6 & 0x20000)) {
                this->unk_1F6 |= 0x20000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_ALL_NIGHT:
            if (!(this->unk_1F6 & 0x40000)) {
                this->unk_1F6 |= 0x40000;
                return 0x1FD1;
            }
            break;

        case PLAYER_MASK_ROMANI:
            if (!(this->unk_1F6 & 0x80000)) {
                this->unk_1F6 |= 0x80000;
                return 0x1FD1;
            }
            break;

        default:
            break;
    }
    this->unk_1EA |= 0x20;
    if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
        return 0x2006;
    }
    return 0x1FCD;
}

s32 func_80AD0E10(EnOsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((gSaveContext.save.inventory.items[SLOT_OCARINA] != ITEM_NONE) && CHECK_QUEST_ITEM(QUEST_SONG_HEALING)) {
        if (this->unk_1EA & 1) {
            this->unk_1EA |= 0x20;
            if ((gSaveContext.save.inventory.items[SLOT_OCARINA] != ITEM_NONE) &&
                (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU)) {
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            return 0x1FAF;
        }

        if (player->transformation == PLAYER_FORM_DEKU) {
            if (this->unk_1EA & 4) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 4;
            return 0x1FC8;
        }

        if (player->transformation == PLAYER_FORM_GORON) {
            if (this->unk_1EA & 8) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 8;
            if (gSaveContext.save.weekEventReg[76] & 0x20) {
                return 0x1FC8;
            }

            gSaveContext.save.weekEventReg[76] |= 0x20;
            return 0x1FCE;
        }

        if (player->transformation == PLAYER_FORM_ZORA) {
            if (this->unk_1EA & 0x10) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 0x10;
            if (gSaveContext.save.weekEventReg[76] & 0x40) {
                return 0x1FC8;
            }
            gSaveContext.save.weekEventReg[76] |= 0x40;
            return 0x1FD0;
        }

        if (Player_GetMask(play) == PLAYER_MASK_NONE) {
            if (this->unk_1EA & 2) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 2;
            return 0x1FC8;
        }

        return func_80AD0B38(this, play);
    }

    this->unk_1EA |= 0x20;
    if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
        return 0x2004;
    }

    return 0x1FAE;
}

void func_80AD10FC(EnOsn* this, PlayState* play) {
    switch (this->unk_1F4) {
        case 0x1FC8:
            this->unk_1F4 = 0x1FC9;
            break;

        case 0x1FC9:
            this->unk_1F4 = 0x1FCA;
            break;

        case 0x1FCA:
            if ((gSaveContext.save.day == 3 && gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
                gSaveContext.save.time < CLOCK_TIME(6, 0)) {
                this->unk_1F4 = 0x2007;
            } else {
                this->unk_1F4 = 0x1FCB;
            }
            break;

        case 0x1FCB:
        case 0x2007:
            this->unk_1F4 = 0x1FCC;
            this->unk_1EA |= 0x20;
            break;

        case 0x1FCE:
        case 0x1FD0:
            this->unk_1F4 = 0x1FCF;
            break;

        case 0x1FCF:
            this->unk_1F4 = 0x1FCA;
            break;

        case 0x1FD1:
        case 0x1FD2:
            this->unk_1F4 = func_80AD08B0(play);
            break;

        case 0x1FD6:
            this->unk_1F4 = 0x1FD7;
            break;

        case 0x1FD8:
            this->unk_1F4 = 0x1FD9;
            break;

        case 0x1FDA:
            this->unk_1F4 = 0x1FDB;
            break;

        case 0x1FDC:
            this->unk_1F4 = 0x1FDD;
            break;

        case 0x1FDE:
            this->unk_1F4 = 0x1FDF;
            break;

        case 0x1FE0:
            this->unk_1F4 = 0x1FE1;
            break;

        case 0x1FE2:
            this->unk_1F4 = 0x1FE3;
            break;

        case 0x1FE4:
            this->unk_1F4 = 0x1FE5;
            break;

        case 0x1FE6:
            this->unk_1F4 = 0x1FE7;
            break;

        case 0x1FE8:
            this->unk_1F4 = 0x1FE9;
            break;

        case 0x1FEA:
            this->unk_1F4 = 0x1FEB;
            break;

        case 0x1FEC:
            this->unk_1F4 = 0x1FED;
            break;

        case 0x1FEE:
            this->unk_1F4 = 0x1FEF;
            break;

        case 0x1FF0:
            this->unk_1F4 = 0x1FF1;
            break;

        case 0x1FF2:
            this->unk_1F4 = 0x1FF3;
            break;

        case 0x1FF4:
            this->unk_1F4 = 0x1FF5;
            break;

        case 0x1FF6:
            this->unk_1F4 = 0x1FF7;
            break;

        case 0x1FF8:
            this->unk_1F4 = 0x1FF9;
            break;

        case 0x1FFA:
            this->unk_1F4 = 0x1FFB;
            break;

        case 0x1FFC:
            this->unk_1F4 = 0x1FFD;
            break;

        case 0x1FD7:
        case 0x1FDB:
        case 0x1FDD:
        case 0x1FDF:
        case 0x1FE1:
        case 0x1FE7:
        case 0x1FF1:
        case 0x1FF3:
        case 0x1FF7:
        case 0x1FF9:
        case 0x1FFB:
            this->unk_1F4 = 0x1FD3;
            break;

        case 0x1FD9:
        case 0x1FE3:
        case 0x1FE9:
        case 0x1FEB:
        case 0x1FED:
        case 0x1FEF:
        case 0x1FF5:
        case 0x1FFD:
            this->unk_1F4 = 0x1FD4;
            break;

        case 0x1FE5:
            this->unk_1F4 = 0x1FFE;
            break;

        case 0x1FD3:
        case 0x1FD4:
        case 0x1FFE:
            this->unk_1F4 = 0x1FD5;
            this->unk_1EA |= 0x20;
    }

    Message_StartTextbox(play, this->unk_1F4, &this->actor);
}

void func_80AD1398(EnOsn* this) {
    this->cutscene = this->actor.cutscene;
    if ((gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) ||
        (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU)) {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);

        if ((gSaveContext.save.inventory.items[SLOT_OCARINA] != ITEM_NONE) ||
            (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU)) {
            this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
        }
    }
}

void func_80AD144C(EnOsn* this, PlayState* play) {
    u32 isFlagSet = Flags_GetSwitch(play, 0);
    this->cutscene = this->actor.cutscene;

    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, 0);
    if (isFlagSet == 0) {
        this->actionFunc = func_80AD16A8;
    } else {
        this->actionFunc = func_80AD14C8;
    }
}

void func_80AD14C8(EnOsn* this, PlayState* play) {
    s16 yaw = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if ((gSaveContext.save.inventory.items[SLOT_OCARINA] != ITEM_NONE) && !CHECK_QUEST_ITEM(QUEST_SONG_HEALING)) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->actionFunc = func_80AD1634;
        } else if (((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) && (yaw < 0x4000) &&
                   (yaw > -0x4000)) {
            func_800B863C(&this->actor, play);
            this->actor.textId = 0xFFFF;
        }
    } else {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->unk_1F4 = func_80AD0E10(this, play);
            Message_StartTextbox(play, this->unk_1F4, &this->actor);
            this->actionFunc = func_80AD19A0;
        } else if (((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) && (yaw < 0x4000) &&
                   (yaw > -0x4000)) {
            func_800B863C(&this->actor, play);
        }
    }
}

void func_80AD1634(EnOsn* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->actionFunc = func_80AD16A8;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void func_80AD16A8(EnOsn* this, PlayState* play) {
    u8 pad;
    s32 actionIndex;

    if (Cutscene_CheckActorAction(play, 130)) {
        actionIndex = Cutscene_GetActorActionIndex(play, 130);
        this->shouldRotateHead = false;
        if (this->csAction != play->csCtx.actorActions[actionIndex]->action) {
            this->csAction = play->csCtx.actorActions[actionIndex]->action;
            switch (play->csCtx.actorActions[actionIndex]->action) {
                case 1:
                    this->animIndex = OSN_ANIM_BOWING;
                    break;

                case 2:
                    this->animIndex = OSN_ANIM_ARMS_OUT;
                    break;

                case 3:
                    this->animIndex = OSN_ANIM_SHAKE_HEAD;
                    break;

                case 4:
                    this->animIndex = OSN_ANIM_REMINISCE;
                    break;

                case 5:
                    this->animIndex = OSN_ANIM_THINK;
                    break;

                case 6:
                    this->animIndex = OSN_ANIM_BELIEVE;
                    break;

                case 7:
                    this->animIndex = OSN_ANIM_HANDS_CLASPED;
                    break;

                case 8:
                    this->animIndex = OSN_ANIM_IDLE;
                    break;

                case 10:
                    this->animIndex = OSN_ANIM_ORGAN_TALK;
                    break;

                case 11:
                    this->animIndex = OSN_ANIM_ORGAN_PLAY;
                    break;

                case 13:
                    this->animIndex = OSN_ANIM_SHAKE;
                    break;

                case 15:
                    this->animIndex = OSN_ANIM_CHOKE;
                    break;

                case 16:
                    this->animIndex = OSN_ANIM_DESPAIR;
                    break;

                case 17:
                    this->animIndex = OSN_ANIM_FAST_BOWS;
                    break;

                case 18:
                    this->animIndex = OSN_ANIM_HAND_OUT;
                    break;

                case 19:
                    this->animIndex = OSN_ANIM_MASK_LOOK_AT;
                    break;

                case 20:
                    this->animIndex = OSN_ANIM_TURN_AROUND_START;
                    break;

                case 21:
                    this->animIndex = OSN_ANIM_WALK_AWAY;
                    break;

                case 22:
                    this->animIndex = OSN_ANIM_MASK_LOOK_FROM_START;
                    break;

                case 23:
                    this->animIndex = OSN_ANIM_HAND_OUT_2;
                    break;

                case 24:
                    this->animIndex = OSN_ANIM_WALK_AWAY_END;
                    break;

                default:
                    this->animIndex = OSN_ANIM_IDLE;
                    break;
            }
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, this->animIndex);
        }

        if ((this->animIndex == OSN_ANIM_BELIEVE) && (play->sceneId == SCENE_SPOT00) &&
            (gSaveContext.sceneLayer == 0xB) && (play->csCtx.frames == 400)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_OMVO00);
        }

        if (this->animIndex == OSN_ANIM_TURN_AROUND_START) {
            func_80AD0998(this);
        }

        if (this->animIndex == OSN_ANIM_MASK_LOOK_FROM_START) {
            func_80AD0A24(this);
        }

        if (this->animIndex == OSN_ANIM_WALK_AWAY_END) {
            func_80AD0AB0(this);
        }

        if ((this->animIndex == OSN_ANIM_WALK_AWAY) &&
            (((Animation_OnFrame(&this->skelAnime, 17.0f))) || (Animation_OnFrame(&this->skelAnime, 27.0f)) ||
             (Animation_OnFrame(&this->skelAnime, 37.0f)) || (Animation_OnFrame(&this->skelAnime, 47.0f)) ||
             (Animation_OnFrame(&this->skelAnime, 57.0f)) || (Animation_OnFrame(&this->skelAnime, 67.0f)))) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OMENYA_WALK);
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    } else {
        this->shouldRotateHead = true;
        this->csAction = 0x63;
        func_80AD144C(this, play);
    }
}

void func_80AD19A0(EnOsn* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (((talkState == TEXT_STATE_DONE) || (talkState == TEXT_STATE_5)) && Message_ShouldAdvance(play)) {
        if (this->unk_1EA & 0x20) {
            this->unk_1EA &= ~0x20;
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.stateTimer = 4;
            this->actionFunc = func_80AD14C8;
        } else {
            func_80AD10FC(this, play);
        }
    }
}

void EnOsn_DoNothing(EnOsn* this, PlayState* play) {
}

void EnOsn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnOsn* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gHappyMaskSalesmanSkel, &gHappyMaskSalesmanIdleAnim, NULL, NULL, 0);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->alpha = 255;

    switch (ENOSN_GET_3(&this->actor)) {
        case 0:
            if (((gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 2)) ||
                 (gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 3))) ||
                (gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 6))) {
                this->unk_1EA |= 1;
            }
            this->shouldRotateHead = true;
            if (play->sceneId == SCENE_INSIDETOWER) {
                if ((gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 2)) ||
                    (gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 6))) {
                    this->actionFunc = func_80AD16A8;
                } else if (gSaveContext.save.entrance == ENTRANCE(CLOCK_TOWER_INTERIOR, 3)) {
                    func_80AD1398(this);
                    this->actionFunc = func_80AD1634;
                } else {
                    func_80AD144C(this, play);
                }
            } else {
                func_80AD144C(this, play);
            }
            break;

        case 1:
            this->animIndex = OSN_ANIM_LYING_DOWN_FACE_UP;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, this->animIndex);
            this->actionFunc = EnOsn_DoNothing;
            break;

        case 2:
            this->animIndex = OSN_ANIM_LYING_DOWN_FACE_DOWN;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, this->animIndex);
            this->actionFunc = EnOsn_DoNothing;
            break;

        case 3:
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actionFunc = func_80AD16A8;
            break;

        default:
            Actor_Kill(&this->actor);
            break;
    }
}

void EnOsn_Destroy(Actor* thisx, PlayState* play) {
    EnOsn* this = THIS;

    SkelAnime_Free(&this->skelAnime, play);
    Collider_DestroyCylinder(play, &this->collider);
}

void EnOsn_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnOsn* this = THIS;
    u32 isFlagSet;

    isFlagSet = Flags_GetSwitch(play, 0);
    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    SkelAnime_Update(&this->skelAnime);

    if (!ENOSN_GET_3(&this->actor)) {
        if (isFlagSet) {
            this->actor.flags |= ACTOR_FLAG_1;
            EnOsn_UpdateCollider(this, play);
            this->actor.draw = EnOsn_Draw;
        } else {
            this->actor.draw = NULL;
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
    }

    Actor_TrackPlayer(play, &this->actor, &this->headRot, &this->torsoRot, this->actor.focus.pos);
}

s32 EnOsn_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                           Gfx** gfx) {
    EnOsn* this = (EnOsn*)thisx;

    if (this->shouldRotateHead && (limbIndex == HAPPY_MASK_SALESMAN_LIMB_HEAD)) {
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
    }
    if (((this->animIndex == OSN_ANIM_ORGAN_PLAY) || (this->animIndex == OSN_ANIM_ORGAN_TALK)) &&
        (limbIndex == HAPPY_MASK_SALESMAN_LIMB_BACKPACK)) {
        *dList = NULL;
    }
    return false;
}

void EnOsn_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnOsn* this = (EnOsn*)thisx;
    Vec3f headOffset = { 0.0f, 0.0f, 0.0f };
    Vec3s leftHandRot = { 0x9920, -0x384, -0x320 };

    if (limbIndex == HAPPY_MASK_SALESMAN_LIMB_HEAD) {
        Matrix_MultVec3f(&headOffset, &this->actor.focus.pos);
    }
    if (((this->animIndex == OSN_ANIM_MASK_LOOK_AT) || (this->animIndex == OSN_ANIM_MASK_LOOK_FROM_START) ||
         (this->animIndex == OSN_ANIM_MASK_LOOK_FROM_LOOP)) &&
        (limbIndex == HAPPY_MASK_SALESMAN_LIMB_LEFT_HAND)) {
        Matrix_Push();
        Matrix_Translate(-400.0f, 1100.0f, -200.0f, MTXMODE_APPLY);
        Matrix_RotateXS(leftHandRot.x, MTXMODE_APPLY);
        Matrix_RotateYS(leftHandRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(leftHandRot.z, MTXMODE_APPLY);

        gSPMatrix((*gfx)++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, &gHappyMaskSalesmanMajorasMaskDL);
        Matrix_Pop();
    }
}

void EnOsn_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sEyeClosedHappyTex = gHappyMaskSalesmanEyeClosedHappyTex;
    static TexturePtr sEyeOpenTex = gHappyMaskSalesmanEyeOpenTex;
    static TexturePtr sEyeClosedAngryTex = gHappyMaskSalesmanEyeClosedAngryTex;
    static TexturePtr sSmileTex = gHappyMaskSalesmanSmileTex;
    static TexturePtr sFrownTex = gHappyMaskSalesmanFrownTex;
    s32 pad;
    EnOsn* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->alpha == 255) {
        func_8012C28C(play->state.gfxCtx);
        if ((this->animIndex == OSN_ANIM_CHOKE) || (this->animIndex == OSN_ANIM_DESPAIR) ||
            (this->animIndex == OSN_ANIM_HAND_OUT_2) || (play->msgCtx.currentTextId == 0x1FCA)) {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeOpenTex));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sSmileTex));
        } else if ((this->animIndex == OSN_ANIM_SHAKE_HEAD) || (this->animIndex == OSN_ANIM_REMINISCE) ||
                   (this->animIndex == OSN_ANIM_FAST_BOWS)) {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeClosedAngryTex));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sFrownTex));
        } else {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeClosedHappyTex));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sSmileTex));
        }
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
        Scene_SetRenderModeXlu(play, 0, 1);
        POLY_OPA_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnOsn_OverrideLimbDraw, EnOsn_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(play->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeClosedHappyTex));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(sSmileTex));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->alpha);
        Scene_SetRenderModeXlu(play, 1, 2);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnOsn_OverrideLimbDraw, EnOsn_PostLimbDraw, &this->actor, POLY_XLU_DISP);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
