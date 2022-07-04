/*
 * File: z_en_s_goro.c
 * Overlay: ovl_En_S_Goro
 * Description: Goron in Goron Shrine / Bomb Shop Goron
 */

/*
This actor appears to be used in three scenes.
-- Goron Shrine: Winter
       Three variants (one instance of each used in game).
       Main behavior determined by whether the Goron Elder's Son is asleep, and whether they themselves have been put to
sleep. One of them also has a dialogue tree that checks whether you have lit the chandelier (at least if the kid is not
crying)
-- Goron Shrine: Spring
       Six variants - one instance of each appearing in a circle around the elder on the upper level of the shrine if
you've beaten Goht during that cycle. Dialogue determined by whether you have talked to elder in that context as a goron
at least once during that cycle. They have a cheering animation used while the elder is talking to you, otherwise they
stand idle.
-- Bomb Shop
       Only one variant. Goron who sells you powder kegs in the bomb shop.
*/

#include "z_en_s_goro.h"
#include "../ovl_En_Gk/z_en_gk.h"
#include "../ovl_En_Jg/z_en_jg.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"
#include "objects/object_taisou/object_taisou.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnSGoro*)thisx)

#define SET_FLAG_ON(bitfield, flag) bitfield |= flag
#define SET_FLAG_OFF(bitfield, flag) bitfield &= ~flag
#define FLAG_IS_SET(bitfield, flag) (bitfield & flag)
#define CLEAR_FLAGS(bitfield) bitfield = 0U

#define IS_FINAL_NIGHT (gSaveContext.save.day == 3) && (gSaveContext.save.isNight)

#define ACTOR_GORON_ELDER ((EnJg*)this->otherGoron)
#define ACTOR_GORON_CHILD ((EnGk*)this->otherGoron)

#define EYETEX_IDX_OPEN 0
#define EYETEX_IDX_HALF 1
#define EYETEX_IDX_CLOSED 2
#define EYETEX_IDX_CLOSED2 3
#define EYETEX_IDX_MAX 3

#define ENSGORO_ANIM_IDLE_LIEDOWN_A 0
#define ENSGORO_ANIM_IDLE_LIEDOWN_B 1
#define ENSGORO_ANIM_UNROLL_A 2
#define ENSGORO_ANIM_UNROLL_B 3
#define ENSGORO_ANIM_ROLLUP 4
#define ENSGORO_ANIM_SHIVER_A 5
#define ENSGORO_ANIM_SHIVER_B 6
#define ENSGORO_ANIM_COVEREARS 11
#define ENSGORO_ANIM_TAISOU_CHEER 12
#define ENSGORO_ANIM_STAND_HANDTAP 13
#define ENSGORO_ANIM_SLEEPY 14
#define ENSGORO_ANIM_IDLE_STAND 15
#define ENSGORO_ANIM_MAXIDX 15

#define ENSGORO_ACTIONFLAG_ROLLEDUP 0x0001
#define ENSGORO_ACTIONFLAG_FACEPLAYER 0x0002
#define ENSGORO_ACTIONFLAG_EYESOPEN 0x0004
#define ENSGORO_ACTIONFLAG_EARSCOVERED 0x0008
#define ENSGORO_ACTIONFLAG_ENGAGED 0x0010
#define ENSGORO_ACTIONFLAG_LASTMESSAGE 0x0020
#define ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED 0x0040
#define ENSGORO_ACTIONFLAG_SNOREPHASE 0x0080 // Set by 80BBDC34 and 80BBDCFC, checked and cleared by 80BBD98C
#define ENSGORO_ACTIONFLAG_UNK0100 0x0100    // Not in use, I guess?
#define ENSGORO_ACTIONFLAG_HANDTAP 0x0200
#define ENSGORO_ACTIONFLAG_TIRED 0x0400
#define ENSGORO_ACTIONFLAG_SUPPRESS_SNORE 0x0800 // Set only by 80BBDCFC, checked and cleared by 80BBD98C

#define ENSGORO_BOMBBUYFLAG_TALKED_HUMAN 0x0001
#define ENSGORO_BOMBBUYFLAG_TALKED_GORONPK 0x0002
#define ENSGORO_BOMBBUYFLAG_TALKED_DEKU 0x0004
#define ENSGORO_BOMBBUYFLAG_TALKED_ZORA 0x0008
#define ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT 0x0010
#define ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT 0x0020
#define ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT 0x0040
#define ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT 0x0080
#define ENSGORO_BOMBBUYFLAG_TALKED_GORON 0x0100
#define ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT 0x0200
#define ENSGORO_BOMBBUYFLAG_YESBUY 0x0400

#define SCENEFLAG_TORCHES_LIT Flags_GetSwitch(playState, ((this->actor.params & 0x7F0) >> 4))
#define CHECK_WEEKEVENT(idx, bitmask) (gSaveContext.save.weekEventReg[idx] & bitmask)
#define SET_WEEKEVENT(idx, bitmask) gSaveContext.save.weekEventReg[idx] |= bitmask

#define CHECK_WEEKEVENT_GK_PACIFIED \
    CHECK_WEEKEVENT(0x16, 0x04) // Kid is asleep. Defo animation of shrine gorons set to shivering.
#define CHECK_WEEKEVENT_SPRING_TALK_JG \
    CHECK_WEEKEVENT(0x4D, 0x80) // You have talked to the Elder as goron while it is spring.

#define CHECK_WEEKEVENT_SGOROA_GKLOUD_NONGORON CHECK_WEEKEVENT(0x24, 0x01) // Talked to shrine A (non Goron), GK bawling
#define CHECK_WEEKEVENT_SGOROA_GKLOUD_GORON CHECK_WEEKEVENT(0x24, 0x02)    // Talked to shrine A (as Goron), GK bawling
#define CHECK_WEEKEVENT_SGOROA_GKQUIET_NONGORON \
    CHECK_WEEKEVENT(0x24, 0x04) // Talked to shrine A (non Goron), GK quiet, torches unlit
#define CHECK_WEEKEVENT_SGOROA_GKQUIET_GORON \
    CHECK_WEEKEVENT(0x24, 0x08) // Talked to shrine A (as Goron), GK quiet, torches unlit
#define CHECK_WEEKEVENT_SGOROA_GKQUIET_TORCHES \
    CHECK_WEEKEVENT(0x24, 0x10) // Talked to shrine A (any form), GK quiet, torches lit
#define CHECK_WEEKEVENT_SGOROB_GKLOUD_NONGORON CHECK_WEEKEVENT(0x24, 0x20) // Talked to shrine B (non Goron), GK bawling
#define CHECK_WEEKEVENT_SGOROB_GKLOUD_GORON CHECK_WEEKEVENT(0x24, 0x40)    // Talked to shrine B (as Goron), GK bawling
#define CHECK_WEEKEVENT_SGOROB_GKQUIET_NONGORON CHECK_WEEKEVENT(0x24, 0x80) // Talked to shrine B (non Goron), GK quiet
#define CHECK_WEEKEVENT_SGOROB_GKQUIET_GORON CHECK_WEEKEVENT(0x25, 0x01)    // Talked to shrine B (as Goron), GK quiet
#define CHECK_WEEKEVENT_SGOROC_GKLOUD_GORON CHECK_WEEKEVENT(0x25, 0x02)     // Talked to shrine C (as Goron), GK bawling
#define CHECK_WEEKEVENT_SGOROC_GKQUIET_GORON CHECK_WEEKEVENT(0x25, 0x04)    // Talked to shrine C (as Goron), GK quiet
#define SET_WEEKEVENT_SGOROA_GKLOUD_NONGORON SET_WEEKEVENT(0x24, 0x01)
#define SET_WEEKEVENT_SGOROA_GKLOUD_GORON SET_WEEKEVENT(0x24, 0x02)
#define SET_WEEKEVENT_SGOROA_GKQUIET_NONGORON SET_WEEKEVENT(0x24, 0x04)
#define SET_WEEKEVENT_SGOROA_GKQUIET_GORON SET_WEEKEVENT(0x24, 0x08)
#define SET_WEEKEVENT_SGOROA_GKQUIET_TORCHES SET_WEEKEVENT(0x24, 0x10)
#define SET_WEEKEVENT_SGOROB_GKLOUD_NONGORON SET_WEEKEVENT(0x24, 0x20)
#define SET_WEEKEVENT_SGOROB_GKLOUD_GORON SET_WEEKEVENT(0x24, 0x40)
#define SET_WEEKEVENT_SGOROB_GKQUIET_NONGORON SET_WEEKEVENT(0x24, 0x80)
#define SET_WEEKEVENT_SGOROB_GKQUIET_GORON SET_WEEKEVENT(0x25, 0x01)
#define SET_WEEKEVENT_SGOROC_GKLOUD_GORON SET_WEEKEVENT(0x25, 0x02)
#define SET_WEEKEVENT_SGOROC_GKQUIET_GORON SET_WEEKEVENT(0x25, 0x04)

#define ACTOR_USAGE_CONTEXT (this->actor.params & 0x000F)
#define ENSGORO_INUSAGEGROUP_WSHRINE ACTOR_USAGE_CONTEXT < 3
#define ENSGORO_USAGE_SHRINE_WINTER_A 0
#define ENSGORO_USAGE_SHRINE_WINTER_B 1
#define ENSGORO_USAGE_SHRINE_WINTER_C 2
#define ENSGORO_USAGE_SHRINE_SPRING_A 3
#define ENSGORO_USAGE_SHRINE_SPRING_B 4
#define ENSGORO_USAGE_SHRINE_SPRING_C 5
#define ENSGORO_USAGE_SHRINE_SPRING_D 6
#define ENSGORO_USAGE_SHRINE_SPRING_E 7
#define ENSGORO_USAGE_SHRINE_SPRING_F 8
#define ENSGORO_USAGE_BOMBSHOP 9

void EnSGoro_Init(Actor* thisx, PlayState* playState);
void EnSGoro_Destroy(Actor* thisx, PlayState* playState);
void EnSGoro_Update(Actor* thisx, PlayState* playState);
void EnSGoro_Draw(Actor* thisx, PlayState* playState);

const ActorInit En_S_Goro_InitVars = { ACTOR_EN_S_GORO,
                                       ACTORCAT_NPC,
                                       FLAGS,
                                       OBJECT_OF1D_MAP,
                                       sizeof(EnSGoro),
                                       (ActorFunc)EnSGoro_Init,
                                       (ActorFunc)EnSGoro_Destroy,
                                       (ActorFunc)EnSGoro_Update,
                                       (ActorFunc)EnSGoro_Draw };

// D_80BBF820
static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER },
    { ELEMTYPE_UNK1, { 0x00000000, 0, 0 }, { 0xF7CFFFFF, 0, 0 }, TOUCH_ON, BUMP_ON, OCELEM_ON },
    { 0, 0, 0, { 0, 0, 0 } }
};

// D_80BBF84C
static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// D_80BBF858
static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// D_80BBF878
static AnimationInfoS sAnimationInfo[] = {
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },        // 0
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },       // 1
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, 0 },               // 2
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, -4 },              // 3
    { &gGoronUnrollAnim, -2.0f, 0, -1, ANIMMODE_ONCE, -4 },             // 4
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },               // 5
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },              // 6
    { &object_taisou_Anim_004DD4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },      // 7
    { &object_taisou_Anim_00283C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },      // 8
    { &object_taisou_Anim_007764, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },      // 9
    { &object_taisou_Anim_005790, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },      // 10
    { &gGoronCoverEarsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },            // 11
    { &object_taisou_Anim_002C48, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },     // 12
    { &gGoronStandingHandTappingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // 13
    { &gGoronSleepyAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },              // 14
    { &gGoronStandingIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -8 }         // 15
};

// D_80BBF978
static TexturePtr sEyeTextures[] = {
    gGoronEyeOpenTex, gGoronEyeHalfTex, gGoronEyeClosedTex, gGoronEyeClosed2Tex, NULL, NULL
};

u16 EnSGoro_ShrineGoron_NextTextID(EnSGoro*, PlayState*);
u16 EnSGoro_BombshopGoron_NextTextID(EnSGoro*, PlayState*);

s32 EnSGoro_SetPartnerActor_GoronElder(EnSGoro*, PlayState*);
s32 EnSGoro_SetPartnerActor_GoronChild(EnSGoro*, PlayState*);
s32 EnSGoro_CheckLullaby(EnSGoro*, PlayState*);
s32 EnSGoro_CheckGKBehavior(EnSGoro*, PlayState*);

void EnSGoro_ActionDefault(EnSGoro*, PlayState*);
void EnSGoro_ActionWinterShrineGoron(EnSGoro*, PlayState*);
void EnSGoro_ActionWinterShrineGoronTalking(EnSGoro*, PlayState*);
void EnSGoro_ActionSpringShrineGoron(EnSGoro*, PlayState*);
void EnSGoro_ActionSpringShrineGoronTalking(EnSGoro*, PlayState*);
void EnSGoro_ActionShopGoron(EnSGoro*, PlayState*);
void EnSGoro_ActionShopGoronFinishUnroll(EnSGoro*, PlayState*);
void EnSGoro_ActionShopGoronTalking(EnSGoro*, PlayState*);
void EnSGoro_ActionShopTakePayment(EnSGoro*, PlayState*);
void EnSGoro_ActionShopFinishTransaction(EnSGoro*, PlayState*);
void EnSGoro_ActionAsleep(EnSGoro*, PlayState*);
void EnSGoro_ActionAsleepMessageWait(EnSGoro*, PlayState*);

s32 EnSGoro_UpdateCheerAnimation(EnSGoro*, PlayState*);
s32 EnSGoro_UpdateRotationToPlayer(EnSGoro*, PlayState*);
s32 EnSGoro_UpdateAttentionTarget(EnSGoro*, PlayState*);
void EnSGoro_UpdateToHandtapAnimation(EnSGoro*);
void EnSGoro_UpdateSleepyAnimation(EnSGoro*);
void EnSGoro_UpdateToIdleAnimation(EnSGoro*);
void EnSGoro_UpdateEyes(EnSGoro*);
void EnSGoro_UpdateActorFocus(EnSGoro*);
void EnSGoro_UpdateSleeping(EnSGoro*, PlayState*);
void EnSGoro_UpdateCollider(EnSGoro*, PlayState*);

s32 EnSGoro_CalculateTranslateRotate(s16, s16, Vec3f*, Vec3s*, s32, s32);
s32 EnSGoro_OverrideLimbDraw(PlayState* playState, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnSGoro_TransformLimbDraw(PlayState*, s32, Actor*);
void EnSGoro_DrawUnrolled(EnSGoro*, PlayState*);
void EnSGoro_DrawRolledUp(EnSGoro*, PlayState*);

// func_80BBCA80 -- Action subfunc. Called by 80BBE73C, 80BBE904, 80BBE844, 80BBE9F8, 80BBECBC
// Dialogue tree for EnSGoro when use in Goron Shrine or "Taisou" contexts. Returns ID of next message to display.
u16 EnSGoro_ShrineGoron_NextTextID(EnSGoro* this, PlayState* playState) {

    Player* player = GET_PLAYER(playState);

    switch (ACTOR_USAGE_CONTEXT) {

        case ENSGORO_USAGE_SHRINE_WINTER_A:
            if (!CHECK_WEEKEVENT_GK_PACIFIED) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!CHECK_WEEKEVENT_SGOROA_GKLOUD_GORON) {
                        switch (this->textID) {
                            case EnSGoro_Msg_WShrineA_Goron_GKLoud_00:
                                return EnSGoro_Msg_WShrineA_Goron_GKLoud_01;
                            case EnSGoro_Msg_WShrineA_Goron_GKLoud_01:
                                return EnSGoro_Msg_WShrineA_Goron_GKLoud_02;
                            case EnSGoro_Msg_WShrineA_Goron_GKLoud_02:
                                SET_WEEKEVENT_SGOROA_GKLOUD_GORON;
                                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                                return EnSGoro_Msg_WShrineA_Goron_GKLoud_03;
                            default:
                                return EnSGoro_Msg_WShrineA_Goron_GKLoud_00;
                        }
                    } else {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_WShrineA_Goron_GKLoud_03;
                    }
                } else {
                    if (!CHECK_WEEKEVENT_SGOROA_GKLOUD_NONGORON) {
                        SET_WEEKEVENT_SGOROA_GKLOUD_NONGORON;
                        return EnSGoro_Msg_WShrineA_NonGoron_GKLoud;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineA_TalkAgain_NonGoron_GKLoud;
                }
            } else {
                if (!SCENEFLAG_TORCHES_LIT) {
                    if (player->transformation == PLAYER_FORM_GORON) {
                        if (!CHECK_WEEKEVENT_SGOROA_GKQUIET_GORON) {
                            if (this->textID == EnSGoro_Msg_WShrineA_Goron_GKQuiet_00) {
                                SET_WEEKEVENT_SGOROA_GKQUIET_GORON;
                                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                                return EnSGoro_Msg_WShrineA_Goron_GKQuiet_01;
                            }
                            return EnSGoro_Msg_WShrineA_Goron_GKQuiet_00;
                        }
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_WShrineA_TalkAgain_Goron_GKQuiet;
                    }
                    if (!CHECK_WEEKEVENT_SGOROA_GKQUIET_NONGORON) {
                        if (this->textID == EnSGoro_Msg_WShrineA_NonGoron_GKQuiet_00) {
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                            SET_WEEKEVENT_SGOROA_GKQUIET_NONGORON;
                            return EnSGoro_Msg_WShrineA_NonGoron_GKQuiet_01;
                        }
                        return EnSGoro_Msg_WShrineA_NonGoron_GKQuiet_00;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineA_TalkAgain_NonGoron_GKQuiet;
                }
                if (!CHECK_WEEKEVENT_SGOROA_GKQUIET_TORCHES) {
                    if (this->textID == EnSGoro_Msg_WShrineA_TorchOkay_00) {
                        SET_WEEKEVENT_SGOROA_GKQUIET_TORCHES;
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_WShrineA_TorchOkay_01;
                    }
                    return EnSGoro_Msg_WShrineA_TorchOkay_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_WShrineA_TalkAgain_TorchOkay;
            }
            break;

        case ENSGORO_USAGE_SHRINE_WINTER_B:
            if (!CHECK_WEEKEVENT_GK_PACIFIED) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!CHECK_WEEKEVENT_SGOROB_GKLOUD_GORON) {
                        switch (this->textID) {
                            case EnSGoro_Msg_WShrineB_Goron_GKLoud_00:
                                return EnSGoro_Msg_WShrineB_Goron_GKLoud_01;
                            case EnSGoro_Msg_WShrineB_Goron_GKLoud_01:
                                SET_WEEKEVENT_SGOROB_GKLOUD_GORON;
                                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                                return EnSGoro_Msg_WShrineB_Goron_GKLoud_02;
                            default:
                                return EnSGoro_Msg_WShrineB_Goron_GKLoud_00;
                        }
                    } else {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_WShrineB_Goron_GKLoud_02;
                    }
                } else {
                    if (!CHECK_WEEKEVENT_SGOROB_GKLOUD_NONGORON) {
                        SET_WEEKEVENT_SGOROB_GKLOUD_NONGORON;
                        return EnSGoro_Msg_WShrineB_NonGoron_GKLoud;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineB_TalkAgain_NonGoron_GKLoud;
                }
            } else if (player->transformation == PLAYER_FORM_GORON) {
                if (!CHECK_WEEKEVENT_SGOROB_GKQUIET_GORON) {
                    switch (this->textID) {
                        case EnSGoro_Msg_WShrineB_Goron_GKQuiet_00:
                            return EnSGoro_Msg_WShrineB_Goron_GKQuiet_01;
                        case EnSGoro_Msg_WShrineB_Goron_GKQuiet_01:
                            SET_WEEKEVENT_SGOROB_GKQUIET_GORON;
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                            return EnSGoro_Msg_WShrineB_Goron_GKQuiet_02;
                        default:
                            return EnSGoro_Msg_WShrineB_Goron_GKQuiet_00;
                    }
                } else {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineB_TalkAgain_Goron_GKQuiet;
                }
            } else {
                if (!CHECK_WEEKEVENT_SGOROB_GKQUIET_NONGORON) {
                    switch (this->textID) {
                        case EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_00:
                            return EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_01;
                        case EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_01:
                            return EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_02;
                        case EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_02:
                            return EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_03;
                        case EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_03:
                            SET_WEEKEVENT_SGOROB_GKQUIET_NONGORON;
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                            return EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_04;
                        default:
                            return EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_00;
                    }
                } else {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineB_TalkAgain_NonGoron_GKQuiet;
                }
            }
            break;

        case ENSGORO_USAGE_SHRINE_WINTER_C:
            if (!CHECK_WEEKEVENT_GK_PACIFIED) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!CHECK_WEEKEVENT_SGOROC_GKLOUD_GORON) {
                        switch (this->textID) {
                            case EnSGoro_Msg_WShrineC_Goron_GKLoud_00:
                                return EnSGoro_Msg_WShrineC_Goron_GKLoud_01;
                            case EnSGoro_Msg_WShrineC_Goron_GKLoud_01:
                                return EnSGoro_Msg_WShrineC_Goron_GKLoud_02;
                            case EnSGoro_Msg_WShrineC_Goron_GKLoud_02:
                                SET_WEEKEVENT_SGOROC_GKLOUD_GORON;
                                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                                return EnSGoro_Msg_WShrineC_Goron_GKLoud_03;
                            default:
                                return EnSGoro_Msg_WShrineC_Goron_GKLoud_00;
                        }
                    } else {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_WShrineC_TalkAgain_Goron_GKLoud;
                    }
                } else {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineC_NonGoron_GKLoud;
                }
            } else if (player->transformation == PLAYER_FORM_GORON) {
                if (!CHECK_WEEKEVENT_SGOROC_GKQUIET_GORON) {
                    switch (this->textID) {
                        case EnSGoro_Msg_WShrineC_Goron_GKQuiet_00:
                            return EnSGoro_Msg_WShrineC_Goron_GKQuiet_01;
                        case EnSGoro_Msg_WShrineC_Goron_GKQuiet_01:
                            SET_WEEKEVENT_SGOROC_GKQUIET_GORON;
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                            return EnSGoro_Msg_WShrineC_Goron_GKQuiet_02;
                        default:
                            return EnSGoro_Msg_WShrineC_Goron_GKQuiet_00;
                    }
                } else {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_WShrineC_TalkAgain_Goron_GKQuiet;
                }
            } else {
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_WShrineC_NonGoron_GKQuiet;
            }
            break;

        case ENSGORO_USAGE_SHRINE_SPRING_A:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    if (this->textID == EnSGoro_Msg_SShrineA_Goron_JGTalked_00) {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_SShrineA_Goron_JGTalked_01;
                    }
                    return EnSGoro_Msg_SShrineA_Goron_JGTalked_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineA_Goron_JGWaiting;
            }
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_SShrineA_NonGoron;

        case ENSGORO_USAGE_SHRINE_SPRING_B:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    if (this->textID == EnSGoro_Msg_SShrineB_Goron_JGTalked_00) {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_SShrineB_Goron_JGTalked_01;
                    }
                    return EnSGoro_Msg_SShrineB_Goron_JGTalked_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineB_Goron_JGWaiting;
            }
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_SShrineB_NonGoron;

        case ENSGORO_USAGE_SHRINE_SPRING_C:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    if (this->textID == EnSGoro_Msg_SShrineC_Goron_JGTalked_00) {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_SShrineC_Goron_JGTalked_01;
                    }
                    return EnSGoro_Msg_SShrineC_Goron_JGTalked_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineC_Goron_JGWaiting;
            }
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_SShrineC_NonGoron;

        case ENSGORO_USAGE_SHRINE_SPRING_D:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    if (this->textID == EnSGoro_Msg_SShrineD_Goron_JGTalked_00) {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_SShrineD_Goron_JGTalked_01;
                    }
                    return EnSGoro_Msg_SShrineD_Goron_JGTalked_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineD_Goron_JGWaiting;
            }
            switch (this->textID) {
                case EnSGoro_Msg_SShrineD_NonGoron_00:
                    return EnSGoro_Msg_SShrineD_NonGoron_01;
                case EnSGoro_Msg_SShrineD_NonGoron_01:
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_SShrineD_NonGoron_02;
                default:
                    return EnSGoro_Msg_SShrineD_NonGoron_00;
            }
            break;

        case ENSGORO_USAGE_SHRINE_SPRING_E:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    if (this->textID == EnSGoro_Msg_SShrineE_Goron_JGTalked_00) {
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_SShrineE_Goron_JGTalked_01;
                    }
                    return EnSGoro_Msg_SShrineE_Goron_JGTalked_00;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineE_Goron_JGWaiting;
            }
            if (this->textID == EnSGoro_Msg_SShrineE_NonGoron_00) {
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_SShrineE_NonGoron_01;
            }
            return EnSGoro_Msg_SShrineE_NonGoron_00;

        case ENSGORO_USAGE_SHRINE_SPRING_F:
            if (player->transformation == PLAYER_FORM_GORON) {
                if (CHECK_WEEKEVENT_SPRING_TALK_JG) {
                    switch (this->textID) {
                        case EnSGoro_Msg_SShrineF_Goron_JGTalked_00:
                            return EnSGoro_Msg_SShrineF_Goron_JGTalked_01;
                        case EnSGoro_Msg_SShrineF_Goron_JGTalked_01:
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                            return EnSGoro_Msg_SShrineF_Goron_JGTalked_02;
                        default:
                            return EnSGoro_Msg_SShrineF_Goron_JGTalked_00;
                    }
                } else {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_SShrineF_Goron_JGWaiting;
                }
            } else {
                if (this->textID == EnSGoro_Msg_SShrineF_NonGoron_00) {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_SShrineF_NonGoron_01;
                }
                return EnSGoro_Msg_SShrineF_NonGoron_00;
            }
            break;

        default:
            return EnSGoro_Msg_None;
    }
}

// func_80BBD348 -- Action subfunc. Called by 80BBEAD8
// Dialogue tree for bomb shop goron. Returns ID of next message to display.
u16 EnSGoro_BombshopGoron_NextTextID(EnSGoro* this, PlayState* playState) {

    Player* player = GET_PLAYER(playState);

    switch (this->textID) {
        case EnSGoro_Msg_None:
            switch (player->transformation) {

                case PLAYER_FORM_GORON:
                    // Powder keg in powder keg slot?
                    if (INV_CONTENT(ITEM_POWDER_KEG) == ITEM_POWDER_KEG) {
                        if (IS_FINAL_NIGHT) {
                            if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT)) {
                                SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT);
                                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
                                return EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_00;
                            }
                            return EnSGoro_Msg_Shop_TalkAgain_GoronPK_LastNight;
                        }
                        if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORONPK)) {
                            SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORONPK);
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
                            return EnSGoro_Msg_Shop_Intro_GoronPK_00;
                        }
                        return EnSGoro_Msg_Shop_TalkAgain_GoronPK;
                    }

                    // No powder keg
                    if (IS_FINAL_NIGHT) {
                        if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT)) {
                            SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT);
                            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
                            return EnSGoro_Msg_Shop_GoronNoPK_LastNight_00;
                        }
                        return EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_LastNight_00;
                    }
                    if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORON)) {
                        SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_GORON);
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
                        return EnSGoro_Msg_Shop_GoronNoPK_00;
                    }
                    return EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_00;

                case PLAYER_FORM_ZORA:
                    if (IS_FINAL_NIGHT) {
                        if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT)) {
                            SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT);
                            return EnSGoro_Msg_Shop_NonGoron_LastNight_00;
                        }
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
                        return EnSGoro_Msg_Shop_TalkAgain_NonGoron_LastNight;
                    }
                    if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_ZORA)) {
                        SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_ZORA);
                        return EnSGoro_Msg_Shop_NonGoron_00;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
                    return EnSGoro_Msg_Shop_TalkAgain_NonGoron;

                case PLAYER_FORM_DEKU:
                    if (IS_FINAL_NIGHT) {
                        if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT)) {
                            SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT);
                            return EnSGoro_Msg_Shop_NonGoron_LastNight_00;
                        }
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_Shop_TalkAgain_NonGoron_LastNight;
                    }
                    if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_DEKU)) {
                        SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_DEKU);
                        return EnSGoro_Msg_Shop_NonGoron_00;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_Shop_TalkAgain_NonGoron;

                case PLAYER_FORM_HUMAN:
                    if (IS_FINAL_NIGHT) {
                        if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT)) {
                            SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT);
                            return EnSGoro_Msg_Shop_NonGoron_LastNight_00;
                        }
                        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                        return EnSGoro_Msg_Shop_TalkAgain_NonGoron_LastNight;
                    }
                    if (!FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_HUMAN)) {
                        SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_TALKED_HUMAN);
                        return EnSGoro_Msg_Shop_NonGoron_00;
                    }
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    return EnSGoro_Msg_Shop_TalkAgain_NonGoron;
            }

        case EnSGoro_Msg_Shop_NonGoron_00:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_NonGoron_01;
        case EnSGoro_Msg_Shop_NonGoron_01:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_NonGoron_02;
        case EnSGoro_Msg_Shop_NonGoron_02:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
            return EnSGoro_Msg_Shop_NonGoron_03;

        case EnSGoro_Msg_Shop_NonGoron_LastNight_00:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_NonGoron_LastNight_01;
        case EnSGoro_Msg_Shop_NonGoron_LastNight_01:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_NonGoron_LastNight_02;
        case EnSGoro_Msg_Shop_NonGoron_LastNight_02:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
            return EnSGoro_Msg_Shop_NonGoron_LastNight_03;

        case EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_00:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_01;
        case EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_01:
            return EnSGoro_Msg_Shop_GoronPK_Common;
        case EnSGoro_Msg_Shop_Intro_GoronPK_00:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_Intro_GoronPK_01;
        case EnSGoro_Msg_Shop_Intro_GoronPK_01:
            return EnSGoro_Msg_Shop_GoronPK_Common;
        case EnSGoro_Msg_Shop_TalkAgain_GoronPK:
            return EnSGoro_Msg_Shop_GoronPK_Common;
        case EnSGoro_Msg_Shop_TalkAgain_GoronPK_LastNight:
            return EnSGoro_Msg_Shop_GoronPK_Common;

        case EnSGoro_Msg_Shop_GoronNoPK_LastNight_00:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_GoronNoPK_LastNight_01;
        case EnSGoro_Msg_Shop_GoronNoPK_LastNight_01:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_Shop_GoronNoPK_LastNight_02;
        case EnSGoro_Msg_Shop_GoronNoPK_00:
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP);
            return EnSGoro_Msg_Shop_GoronNoPK_01;
        case EnSGoro_Msg_Shop_GoronNoPK_01:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_Shop_GoronNoPK_02;
        case EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_00:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_01;
        case EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_LastNight_00:
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_LastNight_01;

        case EnSGoro_Msg_Shop_GoronPK_Common:
            if (FLAG_IS_SET(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_YESBUY)) {
                if (AMMO(ITEM_POWDER_KEG) != 0) {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    play_sound(NA_SE_SY_ERROR);
                    return EnSGoro_Msg_Shop_GoronPK_NoSpace;
                }
                this->powderKegPrice = playState->msgCtx.unk1206C;
                if (gSaveContext.save.playerData.rupees < this->powderKegPrice) {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
                    play_sound(NA_SE_SY_ERROR);
                    return EnSGoro_Msg_Shop_GoronPK_TooPoor;
                }
                if (IS_FINAL_NIGHT) {
                    SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                    func_8019F208();
                    return EnSGoro_Msg_Shop_GoronPK_YesBuy_LastNight;
                }
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                func_8019F208();
                return EnSGoro_Msg_Shop_GoronPK_YesBuy;
            }
            if (IS_FINAL_NIGHT) {
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                return EnSGoro_Msg_Shop_GoronPK_NoBuy_LastNight;
            }
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            return EnSGoro_Msg_Shop_GoronPK_NoBuy;
    }
    return EnSGoro_Msg_None;
}

// func_80BBD8F0 -- Action subfunc (called by 80BBE498)
// Links to actor of type EN_JG (Goron Elder), returns whether operation successful.
s32 EnSGoro_SetPartnerActor_GoronElder(EnSGoro* this, PlayState* playState) {
    this->otherGoron = SubS_FindActor(playState, this->otherGoron, ACTORCAT_NPC, ACTOR_EN_JG);
    if (this->otherGoron)
        return true;
    return false;
}

// func_80BBD93C -- Action subfunc. Called by 80BBE73C
// Links to actor of type EN_GK (Goron Elder's Son), returns whether operation successful.
s32 EnSGoro_SetPartnerActor_GoronChild(EnSGoro* this, PlayState* playState) {
    this->otherGoron = NULL;
    this->otherGoron = SubS_FindActor(playState, this->otherGoron, ACTORCAT_NPC, ACTOR_EN_GK);
    if (this->otherGoron)
        return true;
    return false;
}

// func_80BBD98C -- Action subfunc. Called by 80BBEFA0, 80BBF01C
// Looks like it manages the snoring cycle for when rolled up and asleep?
void EnSGoro_UpdateSleeping(EnSGoro* this, PlayState* playState) {

    s16 curFrame = this->skelAnime.curFrame;

    this->snorePhase += 0x400;
    this->scaleFactor = Math_SinS(this->snorePhase) * 0.01f * 0.1f;
    this->actor.scale.y = 0.01f - this->scaleFactor;
    this->actor.scale.z = 0.01f - this->scaleFactor;
    this->actor.scale.x = this->scaleFactor + 0.01f;

    if (!FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_SUPPRESS_SNORE)) {
        if (this->snorePhase == 0) {
            if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_SNOREPHASE)) {
                SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_SNOREPHASE);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE2);
            } else {
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_SNOREPHASE);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE1);
            }
        }
    } else {
        if (CHECK_WEEKEVENT_GK_PACIFIED) {
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_SUPPRESS_SNORE);
        }
    }

    if (!FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP) && (curFrame == 0)) {
        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP);
        this->actor.shape.yOffset = EN_S_GORO_ROLLEDUP_YOFFSET;
    }

    this->actor.shape.yOffset = (this->actor.scale.y / 0.01f) * EN_S_GORO_ROLLEDUP_YOFFSET;
}

// func_80BBDACC -- Action subfunc. Called by 80BBE904
s32 EnSGoro_UpdateCheerAnimation(EnSGoro* this, PlayState* playState) {
    if (this->animInfoIndex == ENSGORO_ANIM_IDLE_STAND) {
        if (ACTOR_GORON_ELDER->flags & 0x1) {
            this->loadedObjIndex = Object_GetIndex(&playState->objectCtx, OBJECT_TAISOU);
            if (this->loadedObjIndex >= 0) {
                gSegments[6] = (u32)playState->objectCtx.status[this->loadedObjIndex].segment + 0x80000000;
                this->animInfoIndex = ENSGORO_ANIM_TAISOU_CHEER;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
                return true;
            }
        }
    } else if ((this->animInfoIndex == ENSGORO_ANIM_TAISOU_CHEER) && !(ACTOR_GORON_ELDER->flags & 0x1)) {
        this->loadedObjIndex = Object_GetIndex(&playState->objectCtx, OBJECT_OF1D_MAP);
        if (this->loadedObjIndex >= 0) {
            gSegments[6] = (u32)playState->objectCtx.status[this->loadedObjIndex].segment + 0x80000000;
            this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            this->skelAnime.curFrame = this->skelAnime.endFrame;
            return true;
        }
    }
    return false;
}

// func_80BBDC34 -- Action subfunc. Called by 80BBE73C
s32 EnSGoro_CheckLullaby(EnSGoro* this, PlayState* playState) {

    s32 actorUse;
    Player* player = GET_PLAYER(playState);

    if ((player->transformation == PLAYER_FORM_GORON) && (playState->msgCtx.ocarinaMode == 3)) {
        if (playState->msgCtx.unk1202E == 1) {
            this->animInfoIndex = ENSGORO_ANIM_ROLLUP;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);

            actorUse = ACTOR_USAGE_CONTEXT;
            this->snorePhase = 0x400 << (actorUse + 1);
            if (!(actorUse % 2))
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_SNOREPHASE);
            this->actionFunc = EnSGoro_ActionAsleep;
            return true;
        }
    }
    return false;
}

// func_80BBDCFC -- Action subfunc. Called by 80BBE73C
s32 EnSGoro_CheckGKBehavior(EnSGoro* this, PlayState* playState) {

    s32 actorUse;

    if (!EnSGoro_SetPartnerActor_GoronChild(this, playState))
        return false;
    if ((!FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED)) &&
        (FLAG_IS_SET(ACTOR_GORON_CHILD->unk_1E4, 0x80) || CHECK_WEEKEVENT_GK_PACIFIED)) {

        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED);
        this->animInfoIndex = ENSGORO_ANIM_ROLLUP;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);

        actorUse = ACTOR_USAGE_CONTEXT;
        this->snorePhase = 0x400 << (actorUse + 1);
        if (!(actorUse % 2))
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_SNOREPHASE);
        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_SUPPRESS_SNORE);
        this->actionFunc = EnSGoro_ActionAsleep;
        return true;
    }
    return false;
}

// func_80BBDDF8 -- Action subfunc. Called by 80BBECBC
void EnSGoro_UpdateToHandtapAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex != ENSGORO_ANIM_STAND_HANDTAP) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_STAND_HANDTAP;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

// func_80BBDE78 -- Action subfunc. Called by 80BBECBC
void EnSGoro_UpdateSleepyAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if (this->animInfoIndex != ENSGORO_ANIM_SLEEPY) {
        if (curFrame == lastFrame) {
            this->animInfoIndex = ENSGORO_ANIM_SLEEPY;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        }
    } else if (curFrame == lastFrame) {
        SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED);
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

// func_80BBDF28 -- Action subfunc. Called by 80BBEAD8, 80BBECBC
void EnSGoro_UpdateToIdleAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex != ENSGORO_ANIM_IDLE_STAND) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

// func_80BBDFA8 -- Update func
void EnSGoro_UpdateCollider(EnSGoro* this, PlayState* playState) {

    Vec3f world_pos = this->actor.world.pos;
    f32 radius = EN_S_GORO_COLLIDER_RADIUS;
    f32 height = EN_S_GORO_COLLIDER_HEIGHT;

    this->collider.dim.pos.x = (s16)world_pos.x;
    this->collider.dim.pos.y = (s16)world_pos.y;
    this->collider.dim.pos.z = (s16)world_pos.z;
    this->collider.dim.radius = (s16)radius;
    this->collider.dim.height = (s16)height;

    if ((s32)this != -0x190) {
        CollisionCheck_SetOC(playState, &playState->colChkCtx, &this->collider.base);
    }
}

// func_80BBE05C -- Update func
void EnSGoro_UpdateEyes(EnSGoro* this) {

    s16 eyeCtr;

    if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN)) {
        if (this->eyeTimer == 0) {
            eyeCtr = 0;
        } else {
            this->eyeTimer--;
            eyeCtr = this->eyeTimer;
        }

        if (eyeCtr == 0) {
            this->eyeTexIndex++;
            if (this->eyeTexIndex >= EYETEX_IDX_MAX) {
                this->eyeTimer = Rand_S16Offset(30, 30);
                this->eyeTexIndex = EYETEX_IDX_OPEN;
            }
        }
    }
}

// func_80BBE0E4 -- Update func
void EnSGoro_UpdateActorFocus(EnSGoro* this) {

    f32 y_delta;

    if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP))
        y_delta = this->actor.shape.yOffset;
    else
        y_delta = 58.0f;

    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = this->actor.world.pos.y + y_delta;
    this->actor.focus.pos.z = this->actor.world.pos.z;
    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
}

// func_80BBE144 -- Update func. Called by func_80BBE374
s32 EnSGoro_UpdateRotationToPlayer(EnSGoro* this, PlayState* playState) {

    Player* player = GET_PLAYER(playState);
    Vec3f playerPos;
    Vec3f thisPos;
    s16 target;
    s32 pval;

    target = (this->actor.yawTowardsPlayer - this->bodyRotY) - this->actor.shape.rot.y;
    Math_SmoothStepToS(&this->headRotY, target, 4, 0x2AA8, 1);
    if (this->headRotY < -0x1FFE)
        this->headRotY = -0x1FFE;
    else {
        if (this->headRotY >= 0x1FFF)
            pval = 0x1FFE;
        else
            pval = this->headRotY;
        this->headRotY = pval;
    }

    target = (this->actor.yawTowardsPlayer - this->headRotY) - this->actor.shape.rot.y;
    Math_SmoothStepToS(&this->bodyRotY, target, 4, 0x2AA8, 1);
    if (this->bodyRotY < -0x1C70)
        this->bodyRotY = -0x1C70;
    else {
        if (this->bodyRotY >= 0x1C71)
            pval = 0x1C70;
        else
            pval = this->bodyRotY;
        this->bodyRotY = pval;
    }

    playerPos = player->actor.world.pos;
    playerPos.y = player->bodyPartsPos[7].y + 3.0f;
    thisPos = this->actor.world.pos;
    thisPos.y += 70.0f;

    target = Math_Vec3f_Pitch(&thisPos, &playerPos) - this->bodyRotZ;
    Math_SmoothStepToS(&this->headRotZ, target, 4, 0x2AA8, 1);
    if (this->headRotZ < -0x1C70)
        this->headRotZ = -0x1C70;
    else {
        if (this->headRotZ >= 0x1C71)
            pval = 0x1C70;
        else
            pval = this->headRotZ;
        this->headRotZ = pval;
    }

    target = Math_Vec3f_Pitch(&thisPos, &playerPos) - this->headRotZ;
    Math_SmoothStepToS(&this->bodyRotZ, target, 4, 0x2AA8, 1);
    if (this->bodyRotZ < -0x1C70)
        this->bodyRotZ = -0x1C70;
    else {
        if (this->bodyRotZ >= 0x1C71)
            pval = 0x1C70;
        else
            pval = this->bodyRotZ;
        this->bodyRotZ = pval;
    }

    return true;
}

// func_80BBE374 -- Update func. Called by Update if anim is not Sleepy
s32 EnSGoro_UpdateAttentionTarget(EnSGoro* this, PlayState* playState) {

    s16 delay_counter;

    if (this->frameTimer == 0)
        delay_counter = 0;
    else
        delay_counter = --this->frameTimer;

    if (delay_counter != 0) {
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_EARSCOVERED) &&
            FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN)) {
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN);
            this->eyeTexIndex = EYETEX_IDX_CLOSED2;
        }
        SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER);
        this->headRotZ = 0;
        this->headRotY = 0;
        this->bodyRotZ = 0;
        this->bodyRotY = 0;
        return true;
    }

    if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED)) {
        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER);
        EnSGoro_UpdateRotationToPlayer(this, playState);
    } else if (!FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_EARSCOVERED) &&
               Actor_IsFacingAndNearPlayer(&this->actor, 120.0f, 0x3FFC)) {
        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER);
        EnSGoro_UpdateRotationToPlayer(this, playState);
    } else {
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER)) {
            this->frameTimer = 20;
        }
        SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER);
        this->headRotZ = 0;
        this->headRotY = 0;
        this->bodyRotZ = 0;
        this->bodyRotY = 0;
    }
    return true;
}

// func_80BBE498 -- Action func. Default on actor init
void EnSGoro_ActionDefault(EnSGoro* this, PlayState* playState) {
    if (Object_IsLoaded(&playState->objectCtx, this->loadedObjIndex)) {
        CLEAR_FLAGS(this->actionFlags);
        if (ENSGORO_INUSAGEGROUP_WSHRINE) {
            if (CHECK_WEEKEVENT_GK_PACIFIED) {
                // Block A cont (0x80bbe504)
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED);
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN);
                this->animInfoIndex = ENSGORO_ANIM_SHIVER_A;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            } else {
                // Block B (0x80bbe53c)
                this->eyeTexIndex = EYETEX_IDX_CLOSED2;
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_EARSCOVERED);
                this->animInfoIndex = ENSGORO_ANIM_COVEREARS;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            }
        } else {
            // Block C (0x80bbe56c)
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN);
            this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        }

        // Block D (0x80bbe594)
        this->scaleFactor = 0.01f;
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.gravity = -1.0f;
        SET_FLAG_ON(this->actor.flags, ACTOR_FLAG_10);
        SET_FLAG_ON(this->actor.flags, ACTOR_FLAG_2000000);
        this->actor.targetMode = 1;

        switch (ACTOR_USAGE_CONTEXT) {
            case ENSGORO_USAGE_SHRINE_WINTER_A:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_USAGE_SHRINE_WINTER_B:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_USAGE_SHRINE_WINTER_C:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_A:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_B:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_C:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_D:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_E:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_SHRINE_SPRING_F:
                if (EnSGoro_SetPartnerActor_GoronElder(this, playState)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_USAGE_BOMBSHOP:
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP);
                this->actionFunc = EnSGoro_ActionShopGoron;
                this->actor.shape.yOffset = EN_S_GORO_ROLLEDUP_YOFFSET;
                return;
            default:
                Actor_MarkForDeath(&this->actor);
                return;
        }
    }
}

// func_80BBE73C -- Action func.
void EnSGoro_ActionWinterShrineGoron(EnSGoro* this, PlayState* playState) {
    if (!EnSGoro_CheckLullaby(this, playState) && !EnSGoro_CheckGKBehavior(this, playState)) {
        if (Actor_ProcessTalkRequest(&this->actor, &playState->state)) {
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
            if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_EARSCOVERED)) {
                SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_EYESOPEN);
                this->eyeTexIndex = EYETEX_IDX_OPEN;
            }
            this->textID = EnSGoro_ShrineGoron_NextTextID(this, playState);
            Message_StartTextbox(playState, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionWinterShrineGoronTalking;
        } else if ((this->actor.xzDistToPlayer < 250.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, playState);
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, (s16)0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

// func_80BBE844 -- Action func.
void EnSGoro_ActionWinterShrineGoronTalking(EnSGoro* this, PlayState* playState) {
    if ((Message_GetState(&playState->msgCtx) == 6) && (Message_ShouldAdvance(playState))) {
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
            this->actionFunc = EnSGoro_ActionWinterShrineGoron;
            return;
        }
        this->textID = EnSGoro_ShrineGoron_NextTextID(this, playState);
        Message_StartTextbox(playState, this->textID, &this->actor);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, (s16)0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// func_80BBE904 -- Action func.
void EnSGoro_ActionSpringShrineGoron(EnSGoro* this, PlayState* playState) {
    if ((ACTOR_USAGE_CONTEXT == ENSGORO_USAGE_SHRINE_SPRING_F) || !EnSGoro_UpdateCheerAnimation(this, playState)) {
        if (Actor_ProcessTalkRequest(&this->actor, &playState->state)) {
            SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
            this->textID = EnSGoro_ShrineGoron_NextTextID(this, playState);
            Message_StartTextbox(playState, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionSpringShrineGoronTalking;
        } else if ((this->actor.xzDistToPlayer < 250.0f) || (this->actor.isTargeted)) {
            func_800B863C(&this->actor, playState);
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, (s16)0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

// func_80BBE9F8 -- Action func.
void EnSGoro_ActionSpringShrineGoronTalking(EnSGoro* this, PlayState* playState) {
    if ((Message_GetState(&playState->msgCtx) == 5) && Message_ShouldAdvance(playState)) {
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
            playState->msgCtx.msgMode = 0x43;
            playState->msgCtx.unk12023 = 4;
            this->actionFunc = EnSGoro_ActionSpringShrineGoron;
            return;
        }
        this->textID = EnSGoro_ShrineGoron_NextTextID(this, playState);
        Message_StartTextbox(playState, this->textID, &this->actor);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, (s16)0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// func_80BBEAD8 -- Action func.
void EnSGoro_ActionShopGoron(EnSGoro* this, PlayState* playState) {
    if (!FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP)) {
        EnSGoro_UpdateToIdleAnimation(this);
    }
    if (Actor_ProcessTalkRequest(&this->actor, &playState->state)) {
        SET_FLAG_ON(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
        this->textID = EnSGoro_BombshopGoron_NextTextID(this, playState);
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP)) {
            SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP);
            this->animInfoIndex = ENSGORO_ANIM_UNROLL_A;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            this->actionFunc = EnSGoro_ActionShopGoronFinishUnroll;
        } else {
            Message_StartTextbox(playState, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionShopGoronTalking;
        }
    } else if ((this->actor.xzDistToPlayer < 250.0f) || this->actor.isTargeted) {
        func_800B863C(&this->actor, playState);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, (s16)0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// func_80BBEBF8 -- Action func.
void EnSGoro_ActionShopGoronFinishUnroll(EnSGoro* this, PlayState* playState) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex == ENSGORO_ANIM_UNROLL_A) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        Message_StartTextbox(playState, this->textID, &this->actor);
        this->actionFunc = EnSGoro_ActionShopGoronTalking;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, (s16)0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// func_80BBECBC -- Action func.
void EnSGoro_ActionShopGoronTalking(EnSGoro* this, PlayState* playState) {

    u8 msgState = Message_GetState(&playState->msgCtx);

    if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_HANDTAP)) {
        EnSGoro_UpdateToHandtapAnimation(this);
    } else if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_TIRED)) {
        EnSGoro_UpdateSleepyAnimation(this);
    } else {
        EnSGoro_UpdateToIdleAnimation(this);
    }

    if (msgState == 6) {
        if (Message_ShouldAdvance(playState)) {
            if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
                SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_LASTMESSAGE);
                SET_FLAG_OFF(this->actionFlags, ENSGORO_ACTIONFLAG_ENGAGED);
                this->textID = EnSGoro_Msg_None;
                this->actionFunc = EnSGoro_ActionShopGoron;
                return;
            }
            this->textID = EnSGoro_BombshopGoron_NextTextID(this, playState);
            Message_StartTextbox(playState, this->textID, &this->actor);
        }
    } else if ((msgState == 4) && (Message_ShouldAdvance(playState))) {
        switch (playState->msgCtx.choiceIndex) {
            case 0:
                SET_FLAG_ON(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_YESBUY);
                break;
            case 1:
                func_8019F230();
                SET_FLAG_OFF(this->bombbuyFlags, ENSGORO_BOMBBUYFLAG_YESBUY);
                break;
        }

        this->textID = EnSGoro_BombshopGoron_NextTextID(this, playState);
        if ((this->textID == EnSGoro_Msg_Shop_GoronPK_YesBuy) ||
            (this->textID == EnSGoro_Msg_Shop_GoronPK_YesBuy_LastNight)) {
            playState->msgCtx.msgMode = 0x43;
            playState->msgCtx.unk12023 = 4;
            Actor_PickUp(&this->actor, playState, 0x34, 300.0f,
                         300.0f); // 0x34 is probably powder keg, but not currently listed in enum...
            this->actionFunc = EnSGoro_ActionShopTakePayment;
        } else {
            Message_StartTextbox(playState, this->textID, &this->actor);
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, (s16)0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// func_80BBEEB4 -- Action func.
void EnSGoro_ActionShopTakePayment(EnSGoro* this, PlayState* playState) {
    if (Actor_HasParent(&this->actor, playState)) {
        this->actor.parent = NULL;
        func_801159EC(this->powderKegPrice * -1);
        this->actionFunc = EnSGoro_ActionShopFinishTransaction;
        return;
    }
    Actor_PickUp(&this->actor, playState, 0x34, 300.0f, 300.0f);
}

// func_80BBEF34 -- Action func.
void EnSGoro_ActionShopFinishTransaction(EnSGoro* this, PlayState* playState) {
    if (Actor_ProcessTalkRequest(&this->actor, &playState->state)) {
        Message_StartTextbox(playState, this->textID, &this->actor);
        this->actionFunc = EnSGoro_ActionShopGoronTalking;
        return;
    }
    func_800B85E0(&this->actor, playState, 400.0f, -1);
}

// func_80BBEFA0 -- Action func.
void EnSGoro_ActionAsleep(EnSGoro* this, PlayState* playState) {
    if (Actor_ProcessTalkRequest(&this->actor, &playState->state)) {
        Message_StartTextbox(playState, EnSGoro_Msg_Asleep, &this->actor);
        this->actionFunc = EnSGoro_ActionAsleepMessageWait;
    } else if (this->actor.isTargeted) {
        func_800B863C(&this->actor, playState);
    }
    EnSGoro_UpdateSleeping(this, playState);
}

// func_80BBF01C -- Action func.
void EnSGoro_ActionAsleepMessageWait(EnSGoro* this, PlayState* playState) {
    if (Message_GetState(&playState->msgCtx) == 6) {
        if (Message_ShouldAdvance(playState)) {
            playState->msgCtx.msgMode = 0x43;
            playState->msgCtx.unk12023 = 4;
            this->actionFunc = EnSGoro_ActionAsleep;
        }
    }
    EnSGoro_UpdateSleeping(this, playState);
}

void EnSGoro_Init(Actor* thisx, PlayState* playState) {

    EnSGoro* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(playState, &this->skelAnime, &gGoronSkel, &gGoronUnrollAnim, this->jointTable, this->morphTable,
                       EN_S_GORO_LIMBCOUNT);
    Collider_InitCylinder(playState, &this->collider);
    Collider_SetCylinder(playState, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    if (this->actor.update != NULL) {
        const s16 id = OBJECT_OF1D_MAP;
        s32 obj_idx = Object_GetIndex(&playState->objectCtx, id);
        this->loadedObjIndex = obj_idx;
        if (obj_idx < 0) {
            Actor_MarkForDeath(&this->actor);
        }
    }
    this->actor.draw = EnSGoro_Draw;
    this->actionFunc = EnSGoro_ActionDefault;
}

void EnSGoro_Destroy(Actor* thisx, PlayState* playState) {

    EnSGoro* this = THIS;

    Collider_DestroyCylinder(playState, &this->collider);
}

void EnSGoro_Update(Actor* thisx, PlayState* playState) {

    EnSGoro* this = (EnSGoro*)thisx;

    this->actionFunc(this, playState);
    Actor_UpdateBgCheckInfo(playState, &this->actor, 30.0f, 12.0f, 0.0f, 5U);
    gSegments[6] = (u32)((u32)playState->objectCtx.status[this->loadedObjIndex].segment + 0x80000000);
    SkelAnime_Update(&this->skelAnime);
    if (this->animInfoIndex != ENSGORO_ANIM_SLEEPY) {
        EnSGoro_UpdateAttentionTarget(this, playState);
    }
    EnSGoro_UpdateEyes(this);
    EnSGoro_UpdateActorFocus(this);
    EnSGoro_UpdateCollider(this, playState);
}

// func_80BBF298 - Draw function. Called by EnSGoro_TransformLimbDraw
s32 EnSGoro_CalculateTranslateRotate(s16 amt_z, s16 amt_y, Vec3f* translate, Vec3s* rotate, s32 delay_mode,
                                     s32 offset_rotate) {

    Vec3f zeroProduct;
    Vec3f zeroVec;
    Vec3s targetVec;
    MtxF rotMtx;

    zeroVec = gZeroVec3f;

    Matrix_MultVec3f(&zeroVec, &zeroProduct);
    Matrix_Get(&rotMtx);
    Matrix_MtxFToYXZRot(&rotMtx, &targetVec, 0);

    *translate = zeroProduct;

    if (!delay_mode && !offset_rotate) {
        rotate->x = targetVec.x;
        rotate->y = targetVec.y;
        rotate->z = targetVec.z;
        return true;
    }

    if (offset_rotate) {
        targetVec.z = amt_z;
        targetVec.y = amt_y;
    }

    Math_SmoothStepToS(&rotate->x, targetVec.x, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&rotate->y, targetVec.y, 3, 0x2AA8, 0xB6);
    Math_SmoothStepToS(&rotate->z, targetVec.z, 3, 0x2AA8, 0xB6);
    return true;
}

// func_80BBF3D0
s32 EnSGoro_OverrideLimbDraw(PlayState* playState, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

// func_80BBF3EC - Draw function. Calls func_80BBF298
void EnSGoro_TransformLimbDraw(PlayState* playState, s32 limbIndex, Actor* thisx) {

    s32 delayMode;
    s32 addPlayerFaceRotation;
    EnSGoro* this = THIS;

    if (limbIndex != GORON_LIMB_BODY) {
        if ((limbIndex == GORON_LIMB_HEAD) && (this->animInfoIndex != ENSGORO_ANIM_SLEEPY)) {
            if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER))
                addPlayerFaceRotation = true;
            else
                addPlayerFaceRotation = false;
            if (this->frameTimer != 0)
                delayMode = true;
            else
                delayMode = false;

            EnSGoro_CalculateTranslateRotate(this->headRotZ + this->bodyRotZ + 0x4000,
                                             this->headRotY + this->bodyRotY + this->actor.shape.rot.y + 0x4000,
                                             &this->headTranslate, &this->headRotate, delayMode, addPlayerFaceRotation);

            Matrix_Pop();
            Matrix_Translate(this->headTranslate.x, this->headTranslate.y, this->headTranslate.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->headRotate.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->headRotate.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->headRotate.z, MTXMODE_APPLY);
            Matrix_Push();
        }
    } else if (this->animInfoIndex != ENSGORO_ANIM_SLEEPY) {
        if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_FACEPLAYER))
            addPlayerFaceRotation = true;
        else
            addPlayerFaceRotation = false;
        if (this->frameTimer != 0)
            delayMode = true;
        else
            delayMode = false;

        EnSGoro_CalculateTranslateRotate(this->bodyRotZ + 0x4000, this->bodyRotY + this->actor.shape.rot.y + 0x4000,
                                         &this->bodyTranslate, &this->bodyRotate, delayMode, addPlayerFaceRotation);

        Matrix_Pop();
        Matrix_Translate(this->bodyTranslate.x, this->bodyTranslate.y, this->bodyTranslate.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->bodyRotate.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->bodyRotate.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->bodyRotate.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

// func_80BBF5F0 - Draw function. Called by EnSGoro_Draw if actionFlags lowest bit is not set.
void EnSGoro_DrawUnrolled(EnSGoro* this, PlayState* playState) {

    SkelAnime* skelAnime;

    OPEN_DISPS(playState->state.gfxCtx);
    func_8012C28C(playState->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 8, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    gDPPipeSync(POLY_OPA_DISP++);

    skelAnime = &this->skelAnime;
    SkelAnime_DrawTransformFlexOpa(playState, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                   EnSGoro_OverrideLimbDraw, NULL, EnSGoro_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(playState->state.gfxCtx);
}

// func_80BBF6BC - Draw function. Called by EnSGoro_Draw if actionFlags lowest bit is set.
void EnSGoro_DrawRolledUp(EnSGoro* this, PlayState* playState) {

    OPEN_DISPS(playState->state.gfxCtx);
    func_8012C28C(playState->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                     this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Translate(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_Translate(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(playState->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gGoronRolledUpDL);

    CLOSE_DISPS(playState->state.gfxCtx);
}

void EnSGoro_Draw(Actor* thisx, PlayState* playState) {

    EnSGoro* this = (EnSGoro*)thisx;

    if (FLAG_IS_SET(this->actionFlags, ENSGORO_ACTIONFLAG_ROLLEDUP)) {
        EnSGoro_DrawRolledUp(this, playState);
        return;
    }
    EnSGoro_DrawUnrolled(this, playState);
}
