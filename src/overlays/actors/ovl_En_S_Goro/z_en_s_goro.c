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

/*
Week Event Flags:
        0x16 Bit 2	--	Goron Elder's Son has been pacified (Winter)
        0x4D Bit 7	--	You have spoken to the Goron Elder in goron form during spring

        0x24 All Bits
        0x25 Bits 0 - 2
                Track whether or not you have ever spoken to each of the three winter shrine gorons
                in various forms. ("Ever" being since last time reset, of course)
*/

#include "z_en_s_goro.h"
#include "overlays/actors/ovl_En_Gk/z_en_gk.h" //Goron Elder's Son
#include "overlays/actors/ovl_En_Jg/z_en_jg.h" //Goron Elder
#include "objects/object_taisou/object_taisou.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)
#define THIS ((EnSGoro*)thisx)

#define EYETEX_INDEX_MAX 3
#define ENSGORO_OFTYPE_WSHRINE EN_S_GORO_GET_MAIN_TYPE(&this->actor) < 3

void EnSGoro_Init(Actor* thisx, PlayState* play);
void EnSGoro_Destroy(Actor* thisx, PlayState* play);
void EnSGoro_Update(Actor* thisx, PlayState* play);
void EnSGoro_Draw(Actor* thisx, PlayState* play);

const ActorInit En_S_Goro_InitVars = {
    ACTOR_EN_S_GORO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnSGoro),
    (ActorFunc)EnSGoro_Init,
    (ActorFunc)EnSGoro_Destroy,
    (ActorFunc)EnSGoro_Update,
    (ActorFunc)EnSGoro_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON, BUMP_ON, OCELEM_ON },
    { 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

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

static AnimationInfoS sAnimationInfo[] = {
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gGoronUnrollAnim, -2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_taisou_Anim_004DD4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_00283C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_007764, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005790, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronCoverEarsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_002C48, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gGoronStandingHandTappingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gGoronSleepyAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gGoronStandingIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
};

static TexturePtr sEyeTextures[] = {
    gGoronEyeOpenTex,
    gGoronEyeHalfTex,
    gGoronEyeClosedTex,
    gGoronEyeClosed2Tex,
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
s32 EnSGoro_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnSGoro_TransformLimbDraw(PlayState*, s32, Actor*);
void EnSGoro_DrawUnrolled(EnSGoro*, PlayState*);
void EnSGoro_DrawRolledUp(EnSGoro*, PlayState*);

/*
        Dialogue tree for EnSGoro when use in Goron Shrine context. Returns ID of next message to display.
*/
u16 EnSGoro_ShrineGoron_NextTextID(EnSGoro* this, PlayState* play) {

    Player* player = GET_PLAYER(play);

    switch (EN_S_GORO_GET_MAIN_TYPE(&this->actor)) {

        case ENSGORO_TYPE_SHRINE_WINTER_A:
            if (!(gSaveContext.save.weekEventReg[0x16] & 0x04)) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!(gSaveContext.save.weekEventReg[0x24] & 0x02)) {
                        switch (this->textID) {
                            case 0xCFB:
                                return 0xCFC;
                            case 0xCFC:
                                return 0xCFD;
                            case 0xCFD:
                                gSaveContext.save.weekEventReg[0x24] |= 0x02;
                                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                                return 0xCFE;
                            default:
                                return 0xCFB;
                        }
                    } else {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xCFE;
                    }
                } else {
                    if (!(gSaveContext.save.weekEventReg[0x24] & 0x01)) {
                        gSaveContext.save.weekEventReg[0x24] |= 0x01;
                        return 0xCF9;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xCFA;
                }
            } else {
                // Scene flag - Checks whether the chandelier has been lit
                if (!Flags_GetSwitch(play, EN_S_GORO_SCENEFLAG_INDEX(&this->actor))) {
                    if (player->transformation == PLAYER_FORM_GORON) {
                        if (!(gSaveContext.save.weekEventReg[0x24] & 0x08)) {
                            if (this->textID == 0xD02) {
                                gSaveContext.save.weekEventReg[0x24] |= 0x08;
                                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                                return 0xD03;
                            }
                            return 0xD02;
                        }
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xD04;
                    }
                    if (!(gSaveContext.save.weekEventReg[0x24] & 0x04)) {
                        if (this->textID == 0xCFF) {
                            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                            gSaveContext.save.weekEventReg[0x24] |= 0x04;
                            return 0xD00;
                        }
                        return 0xCFF;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD01;
                }
                if (!(gSaveContext.save.weekEventReg[0x24] & 0x10)) {
                    if (this->textID == 0xD05) {
                        gSaveContext.save.weekEventReg[0x24] |= 0x10;
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xD06;
                    }
                    return 0xD05;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xD07;
            }
            break;

        case ENSGORO_TYPE_SHRINE_WINTER_B:
            if (!(gSaveContext.save.weekEventReg[0x16] & 0x04)) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!(gSaveContext.save.weekEventReg[0x24] & 0x40)) {
                        switch (this->textID) {
                            case 0xD15:
                                return 0xD16;
                            case 0xD16:
                                gSaveContext.save.weekEventReg[0x24] |= 0x40;
                                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                                return 0xD17;
                            default:
                                return 0xD15;
                        }
                    } else {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xD17;
                    }
                } else {
                    if (!(gSaveContext.save.weekEventReg[0x24] & 0x20)) {
                        gSaveContext.save.weekEventReg[0x24] |= 0x20;
                        return 0xD13;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD14;
                }
            } else if (player->transformation == PLAYER_FORM_GORON) {
                if (!(gSaveContext.save.weekEventReg[0x25] & 0x01)) {
                    switch (this->textID) {
                        case 0xD1E:
                            return 0xD1F;
                        case 0xD1F:
                            gSaveContext.save.weekEventReg[0x25] |= 0x01;
                            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                            return 0xD20;
                        default:
                            return 0xD1E;
                    }
                } else {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD21;
                }
            } else {
                if (!(gSaveContext.save.weekEventReg[0x24] & 0x80)) {
                    switch (this->textID) {
                        case 0xD18:
                            return 0xD19;
                        case 0xD19:
                            return 0xD1A;
                        case 0xD1A:
                            return 0xD1B;
                        case 0xD1B:
                            gSaveContext.save.weekEventReg[0x24] |= 0x80;
                            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                            return 0xD1C;
                        default:
                            return 0xD18;
                    }
                } else {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD1D;
                }
            }
            break;

        case ENSGORO_TYPE_SHRINE_WINTER_C:
            if (!(gSaveContext.save.weekEventReg[0x16] & 0x04)) {
                if (player->transformation == PLAYER_FORM_GORON) {
                    if (!(gSaveContext.save.weekEventReg[0x25] & 0x02)) {
                        switch (this->textID) {
                            case 0xD09:
                                return 0xD0A;
                            case 0xD0A:
                                return 0xD0B;
                            case 0xD0B:
                                gSaveContext.save.weekEventReg[0x25] |= 0x02;
                                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                                return 0xD0C;
                            default:
                                return 0xD09;
                        }
                    } else {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xD0D;
                    }
                } else {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD08;
                }
            } else if (player->transformation == PLAYER_FORM_GORON) {
                if (!(gSaveContext.save.weekEventReg[0x25] & 0x04)) {
                    switch (this->textID) {
                        case 0xD0E:
                            return 0xD0F;
                        case 0xD0F:
                            gSaveContext.save.weekEventReg[0x25] |= 0x04;
                            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                            return 0xD10;
                        default:
                            return 0xD0E;
                    }
                } else {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xD11;
                }
            } else {
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xD12;
            }
            break;

        case ENSGORO_TYPE_SHRINE_SPRING_A:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    if (this->textID == 0xDE3) {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xDE4;
                    }
                    return 0xDE3;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDE2;
            }
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0xDE1;

        case ENSGORO_TYPE_SHRINE_SPRING_B:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    if (this->textID == 0xDE7) {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xDE8;
                    }
                    return 0xDE7;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDE6;
            }
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0xDE5;

        case ENSGORO_TYPE_SHRINE_SPRING_C:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    if (this->textID == 0xDEB) {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xDEC;
                    }
                    return 0xDEB;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDEA;
            }
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0xDE9;

        case ENSGORO_TYPE_SHRINE_SPRING_D:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    if (this->textID == 0xDF1) {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xDF2;
                    }
                    return 0xDF1;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDF0;
            }
            switch (this->textID) {
                case 0xDED:
                    return 0xDEE;
                case 0xDEE:
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xDEF;
                default:
                    return 0xDED;
            }
            break;

        case ENSGORO_TYPE_SHRINE_SPRING_E:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    if (this->textID == 0xDF6) {
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0xDF7;
                    }
                    return 0xDF6;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDF5;
            }
            if (this->textID == 0xDF3) {
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0xDF4;
            }
            return 0xDF3;

        case ENSGORO_TYPE_SHRINE_SPRING_F:
            if (player->transformation == PLAYER_FORM_GORON) {
                if ((gSaveContext.save.weekEventReg[0x4D] & 0x80)) {
                    switch (this->textID) {
                        case 0xDFB:
                            return 0xDFC;
                        case 0xDFC:
                            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                            return 0xDFD;
                        default:
                            return 0xDFB;
                    }
                } else {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xDFA;
                }
            } else {
                if (this->textID == 0xDF8) {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0xDF9;
                }
                return 0xDF8;
            }
            break;

        default:
            return 0x0;
    }
}

/*
        Dialogue tree for bomb shop goron. Returns ID of next message to display.
*/
u16 EnSGoro_BombshopGoron_NextTextID(EnSGoro* this, PlayState* play) {

    Player* player = GET_PLAYER(play);

    switch (this->textID) {
        case 0x0:
            switch (player->transformation) {

                case PLAYER_FORM_GORON:
                    // Powder keg in powder keg slot?
                    if (INV_CONTENT(ITEM_POWDER_KEG) == ITEM_POWDER_KEG) {
                        if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                            if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT)) {
                                this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT;
                                this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
                                return 0x677;
                            }
                            return 0x67A;
                        }
                        if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_GORONPK)) {
                            this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_GORONPK;
                            this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
                            return 0x66E;
                        }
                        return 0x679;
                    }

                    // No powder keg
                    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                        if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT)) {
                            this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT;
                            this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
                            return 0x67E;
                        }
                        return 0x683;
                    }
                    if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_GORON)) {
                        this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_GORON;
                        this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
                        return 0x67B;
                    }
                    return 0x681;

                case PLAYER_FORM_ZORA:
                    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                        if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT)) {
                            this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT;
                            return 0x668;
                        }
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        this->actionFlags |= ENSGORO_ACTIONFLAG_TIRED;
                        return 0x66D;
                    }
                    if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_ZORA)) {
                        this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_ZORA;
                        return 0x664;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    this->actionFlags |= ENSGORO_ACTIONFLAG_TIRED;
                    return 0x66C;

                case PLAYER_FORM_DEKU:
                    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                        if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT)) {
                            this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT;
                            return 0x668;
                        }
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0x66D;
                    }
                    if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_DEKU)) {
                        this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_DEKU;
                        return 0x664;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0x66C;

                case PLAYER_FORM_HUMAN:
                    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                        if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT)) {
                            this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT;
                            return 0x668;
                        }
                        this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                        return 0x66D;
                    }
                    if (!(this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_TALKED_HUMAN)) {
                        this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_TALKED_HUMAN;
                        return 0x664;
                    }
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    return 0x66C;
            }

        case 0x664:
            this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x665;
        case 0x665:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x666;
        case 0x666:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            this->actionFlags |= ENSGORO_ACTIONFLAG_TIRED;
            return 0x667;

        case 0x668:
            this->actionFlags |= ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x669;
        case 0x669:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x66A;
        case 0x66A:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            this->actionFlags |= ENSGORO_ACTIONFLAG_TIRED;
            return 0x66B;

        case 0x677:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x678;
        case 0x678:
            return 0x670;
        case 0x66E:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x66F;
        case 0x66F:
            return 0x670;
        case 0x679:
            return 0x670;
        case 0x67A:
            return 0x670;

        case 0x67E:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x67F;
        case 0x67F:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0x680;
        case 0x67B:
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_HANDTAP;
            return 0x67C;
        case 0x67C:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0x67D;
        case 0x681:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0x682;
        case 0x683:
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0x684;

        case 0x670:
            if ((this->bombbuyFlags & ENSGORO_BOMBBUYFLAG_YESBUY)) {
                if (AMMO(ITEM_POWDER_KEG) != 0) {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    play_sound(NA_SE_SY_ERROR);
                    return 0x673;
                }
                this->powderKegPrice = play->msgCtx.unk1206C;
                if (gSaveContext.save.playerData.rupees < this->powderKegPrice) {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    this->actionFlags |= ENSGORO_ACTIONFLAG_TIRED;
                    play_sound(NA_SE_SY_ERROR);
                    return 0x674;
                }
                if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                    this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                    func_8019F208();
                    return 0x676;
                }
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                func_8019F208();
                return 0x675;
            }
            if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
                this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
                return 0x672;
            }
            this->actionFlags |= ENSGORO_ACTIONFLAG_LASTMESSAGE;
            return 0x671;
    }
    return 0x0;
}

/*
        Links to actor of type EN_JG (Goron Elder), returns whether operation successful.
*/
s32 EnSGoro_SetPartnerActor_GoronElder(EnSGoro* this, PlayState* play) {
    this->otherGoron = SubS_FindActor(play, this->otherGoron, ACTORCAT_NPC, ACTOR_EN_JG);
    if (this->otherGoron) {
        return true;
    }
    return false;
}

/*
        Links to actor of type EN_GK (Goron Elder's Son), returns whether operation successful.
*/
s32 EnSGoro_SetPartnerActor_GoronChild(EnSGoro* this, PlayState* play) {
    this->otherGoron = NULL;
    this->otherGoron = SubS_FindActor(play, this->otherGoron, ACTORCAT_NPC, ACTOR_EN_GK);
    if (this->otherGoron) {
        return true;
    }
    return false;
}

/*
        Looks like it manages the snoring cycle for when rolled up and asleep?
*/
void EnSGoro_UpdateSleeping(EnSGoro* this, PlayState* play) {

    s16 curFrame = this->skelAnime.curFrame;

    this->snorePhase += 0x400;
    this->scaleFactor = Math_SinS(this->snorePhase) * 0.01f * 0.1f;
    this->actor.scale.y = 0.01f - this->scaleFactor;
    this->actor.scale.z = 0.01f - this->scaleFactor;
    this->actor.scale.x = this->scaleFactor + 0.01f;

    if (!(this->actionFlags & ENSGORO_ACTIONFLAG_SUPPRESS_SNORE)) {
        if (this->snorePhase == 0) {
            if ((this->actionFlags & ENSGORO_ACTIONFLAG_SNOREPHASE)) {
                this->actionFlags &= ~ENSGORO_ACTIONFLAG_SNOREPHASE;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE2);
            } else {
                this->actionFlags |= ENSGORO_ACTIONFLAG_SNOREPHASE;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE1);
            }
        }
    } else {
        if ((gSaveContext.save.weekEventReg[0x16] & 0x04)) {
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_SUPPRESS_SNORE;
        }
    }

    if (!(this->actionFlags & ENSGORO_ACTIONFLAG_ROLLEDUP) && (curFrame == 0)) {
        this->actionFlags |= ENSGORO_ACTIONFLAG_ROLLEDUP;
        this->actor.shape.yOffset = EN_S_GORO_ROLLEDUP_YOFFSET;
    }

    this->actor.shape.yOffset = (this->actor.scale.y / 0.01f) * EN_S_GORO_ROLLEDUP_YOFFSET;
}

s32 EnSGoro_UpdateCheerAnimation(EnSGoro* this, PlayState* play) {
    if (this->animInfoIndex == ENSGORO_ANIM_IDLE_STAND) {
        if (((EnJg*)this->otherGoron)->flags & 0x1) {
            this->loadedObjIndex = Object_GetIndex(&play->objectCtx, OBJECT_TAISOU);
            if (this->loadedObjIndex >= 0) {
                gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->loadedObjIndex].segment);
                this->animInfoIndex = ENSGORO_ANIM_TAISOU_CHEER;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
                return true;
            }
        }
    } else if ((this->animInfoIndex == ENSGORO_ANIM_TAISOU_CHEER) && !(((EnJg*)this->otherGoron)->flags & 0x1)) {
        this->loadedObjIndex = Object_GetIndex(&play->objectCtx, OBJECT_OF1D_MAP);
        if (this->loadedObjIndex >= 0) {
            gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->loadedObjIndex].segment);
            this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            this->skelAnime.curFrame = this->skelAnime.endFrame;
            return true;
        }
    }
    return false;
}

s32 EnSGoro_CheckLullaby(EnSGoro* this, PlayState* play) {

    s32 actorUse;
    Player* player = GET_PLAYER(play);

    if ((player->transformation == PLAYER_FORM_GORON) && (play->msgCtx.ocarinaMode == 3)) {
        if (play->msgCtx.unk1202E == 1) {
            this->animInfoIndex = ENSGORO_ANIM_ROLLUP;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);

            actorUse = EN_S_GORO_GET_MAIN_TYPE(&this->actor);
            this->snorePhase = 0x400 << (actorUse + 1);
            if (!(actorUse % 2)) {
                this->actionFlags |= ENSGORO_ACTIONFLAG_SNOREPHASE;
            }
            this->actionFunc = EnSGoro_ActionAsleep;
            return true;
        }
    }
    return false;
}

s32 EnSGoro_CheckGKBehavior(EnSGoro* this, PlayState* play) {

    s32 actorUse;

    if (!EnSGoro_SetPartnerActor_GoronChild(this, play)) {
        return false;
    }
    if ((!(this->actionFlags & ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED)) &&
        ((((EnGk*)this->otherGoron)->unk_1E4 & 0x80) || (gSaveContext.save.weekEventReg[0x16] & 0x04))) {

        this->actionFlags |= ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED;
        this->animInfoIndex = ENSGORO_ANIM_ROLLUP;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);

        actorUse = EN_S_GORO_GET_MAIN_TYPE(&this->actor);
        this->snorePhase = 0x400 << (actorUse + 1);
        if (!(actorUse % 2)) {
            this->actionFlags |= ENSGORO_ACTIONFLAG_SNOREPHASE;
        }
        this->actionFlags |= ENSGORO_ACTIONFLAG_SUPPRESS_SNORE;
        this->actionFunc = EnSGoro_ActionAsleep;
        return true;
    }
    return false;
}

void EnSGoro_UpdateToHandtapAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex != ENSGORO_ANIM_STAND_HANDTAP) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_STAND_HANDTAP;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

void EnSGoro_UpdateSleepyAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if (this->animInfoIndex != ENSGORO_ANIM_SLEEPY) {
        if (curFrame == lastFrame) {
            this->animInfoIndex = ENSGORO_ANIM_SLEEPY;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        }
    } else if (curFrame == lastFrame) {
        this->actionFlags &= ~ENSGORO_ACTIONFLAG_TIRED;
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

void EnSGoro_UpdateToIdleAnimation(EnSGoro* this) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex != ENSGORO_ANIM_IDLE_STAND) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
    }
}

void EnSGoro_UpdateCollider(EnSGoro* this, PlayState* play) {

    Vec3f world_pos = this->actor.world.pos;
    f32 radius = 24.0f;
    f32 height = 62.0f;

    this->collider.dim.pos.x = world_pos.x;
    this->collider.dim.pos.y = world_pos.y;
    this->collider.dim.pos.z = world_pos.z;
    this->collider.dim.radius = radius;
    this->collider.dim.height = height;

    if ((s32)this != -0x190) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnSGoro_UpdateEyes(EnSGoro* this) {

    s16 eyeCtr;

    if ((this->actionFlags & ENSGORO_ACTIONFLAG_EYESOPEN)) {
        if (this->eyeTimer == 0) {
            eyeCtr = 0;
        } else {
            this->eyeTimer--;
            eyeCtr = this->eyeTimer;
        }

        if (eyeCtr == 0) {
            this->eyeTexIndex++;
            if (this->eyeTexIndex >= EYETEX_INDEX_MAX) {
                this->eyeTimer = Rand_S16Offset(30, 30);
                this->eyeTexIndex = ENSGORO_EYETEX_OPEN;
            }
        }
    }
}

void EnSGoro_UpdateActorFocus(EnSGoro* this) {

    f32 yDelta;

    if ((this->actionFlags & ENSGORO_ACTIONFLAG_ROLLEDUP)) {
        yDelta = this->actor.shape.yOffset;
    } else {
        yDelta = 58.0f;
    }

    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = this->actor.world.pos.y + yDelta;
    this->actor.focus.pos.z = this->actor.world.pos.z;
    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
}

s32 EnSGoro_UpdateRotationToPlayer(EnSGoro* this, PlayState* play) {

    Player* player = GET_PLAYER(play);
    Vec3f playerPos;
    Vec3f thisPos;
    s16 target = (this->actor.yawTowardsPlayer - this->bodyRotY) - this->actor.shape.rot.y;
    s32 pval;

    Math_SmoothStepToS(&this->headRotY, target, 4, 0x2AA8, 1);
    if (this->headRotY < -0x1FFE) {
        this->headRotY = -0x1FFE;
    } else {
        if (this->headRotY >= 0x1FFF) {
            pval = 0x1FFE;
        } else {
            pval = this->headRotY;
        }
        this->headRotY = pval;
    }

    target = (this->actor.yawTowardsPlayer - this->headRotY) - this->actor.shape.rot.y;
    Math_SmoothStepToS(&this->bodyRotY, target, 4, 0x2AA8, 1);
    if (this->bodyRotY < -0x1C70) {
        this->bodyRotY = -0x1C70;
    } else {
        if (this->bodyRotY > 0x1C70) {
            pval = 0x1C70;
        } else {
            pval = this->bodyRotY;
        }
        this->bodyRotY = pval;
    }

    playerPos = player->actor.world.pos;
    playerPos.y = player->bodyPartsPos[7].y + 3.0f;
    thisPos = this->actor.world.pos;
    thisPos.y += 70.0f;

    target = Math_Vec3f_Pitch(&thisPos, &playerPos) - this->bodyRotZ;
    Math_SmoothStepToS(&this->headRotZ, target, 4, 0x2AA8, 1);
    if (this->headRotZ < -0x1C70) {
        this->headRotZ = -0x1C70;
    } else {
        if (this->headRotZ >= 0x1C71) {
            pval = 0x1C70;
        } else {
            pval = this->headRotZ;
        }
        this->headRotZ = pval;
    }

    target = Math_Vec3f_Pitch(&thisPos, &playerPos) - this->headRotZ;
    Math_SmoothStepToS(&this->bodyRotZ, target, 4, 0x2AA8, 1);
    if (this->bodyRotZ < -0x1C70) {
        this->bodyRotZ = -0x1C70;
    } else {
        if (this->bodyRotZ >= 0x1C71) {
            pval = 0x1C70;
        } else {
            pval = this->bodyRotZ;
        }
        this->bodyRotZ = pval;
    }

    return true;
}

s32 EnSGoro_UpdateAttentionTarget(EnSGoro* this, PlayState* play) {

    s16 delay_counter;

    if (this->frameTimer == 0) {
        delay_counter = 0;
    } else {
        delay_counter = --this->frameTimer;
    }

    if (delay_counter != 0) {
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_EARSCOVERED) && (this->actionFlags & ENSGORO_ACTIONFLAG_EYESOPEN)) {
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_EYESOPEN;
            this->eyeTexIndex = ENSGORO_EYETEX_CLOSED2;
        }
        this->actionFlags &= ~ENSGORO_ACTIONFLAG_FACEPLAYER;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->bodyRotZ = 0;
        this->bodyRotY = 0;
        return true;
    }

    if ((this->actionFlags & ENSGORO_ACTIONFLAG_ENGAGED)) {
        this->actionFlags |= ENSGORO_ACTIONFLAG_FACEPLAYER;
        EnSGoro_UpdateRotationToPlayer(this, play);
    } else if (!(this->actionFlags & ENSGORO_ACTIONFLAG_EARSCOVERED) &&
               Actor_IsFacingAndNearPlayer(&this->actor, 120.0f, 0x3FFC)) {
        this->actionFlags |= ENSGORO_ACTIONFLAG_FACEPLAYER;
        EnSGoro_UpdateRotationToPlayer(this, play);
    } else {
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_FACEPLAYER)) {
            this->frameTimer = 20;
        }
        this->actionFlags &= ~ENSGORO_ACTIONFLAG_FACEPLAYER;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->bodyRotZ = 0;
        this->bodyRotY = 0;
    }
    return true;
}

void EnSGoro_ActionDefault(EnSGoro* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->loadedObjIndex)) {
        this->actionFlags = 0U;
        if (ENSGORO_OFTYPE_WSHRINE) {
            if ((gSaveContext.save.weekEventReg[0x16] & 0x04)) {
                this->actionFlags |= ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED;
                this->actionFlags |= ENSGORO_ACTIONFLAG_EYESOPEN;
                this->animInfoIndex = ENSGORO_ANIM_SHIVER_A;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            } else {
                this->eyeTexIndex = ENSGORO_EYETEX_CLOSED2;
                this->actionFlags |= ENSGORO_ACTIONFLAG_EARSCOVERED;
                this->animInfoIndex = ENSGORO_ANIM_COVEREARS;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            }
        } else {
            this->actionFlags |= ENSGORO_ACTIONFLAG_EYESOPEN;
            this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        }

        this->scaleFactor = 0.01f;
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.gravity = -1.0f;
        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        this->actor.targetMode = 1;

        switch (EN_S_GORO_GET_MAIN_TYPE(&this->actor)) {
            case ENSGORO_TYPE_SHRINE_WINTER_A:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_TYPE_SHRINE_WINTER_B:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_TYPE_SHRINE_WINTER_C:
                this->actionFunc = EnSGoro_ActionWinterShrineGoron;
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_A:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_B:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_C:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_D:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_E:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_SHRINE_SPRING_F:
                if (EnSGoro_SetPartnerActor_GoronElder(this, play)) {
                    this->actionFunc = EnSGoro_ActionSpringShrineGoron;
                    return;
                }
                return;
            case ENSGORO_TYPE_BOMBSHOP:
                this->actionFlags |= ENSGORO_ACTIONFLAG_ROLLEDUP;
                this->actionFunc = EnSGoro_ActionShopGoron;
                this->actor.shape.yOffset = EN_S_GORO_ROLLEDUP_YOFFSET;
                return;
            default:
                Actor_MarkForDeath(&this->actor);
                return;
        }
    }
}

void EnSGoro_ActionWinterShrineGoron(EnSGoro* this, PlayState* play) {
    if (!EnSGoro_CheckLullaby(this, play) && !EnSGoro_CheckGKBehavior(this, play)) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->actionFlags |= ENSGORO_ACTIONFLAG_ENGAGED;
            if ((this->actionFlags & ENSGORO_ACTIONFLAG_EARSCOVERED)) {
                this->actionFlags |= ENSGORO_ACTIONFLAG_EYESOPEN;
                this->eyeTexIndex = ENSGORO_EYETEX_OPEN;
            }
            this->textID = EnSGoro_ShrineGoron_NextTextID(this, play);
            Message_StartTextbox(play, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionWinterShrineGoronTalking;
        } else if ((this->actor.xzDistToPlayer < 250.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, play);
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void EnSGoro_ActionWinterShrineGoronTalking(EnSGoro* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 6) && (Message_ShouldAdvance(play))) {
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_LASTMESSAGE;
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_ENGAGED;
            this->actionFunc = EnSGoro_ActionWinterShrineGoron;
            return;
        }
        this->textID = EnSGoro_ShrineGoron_NextTextID(this, play);
        Message_StartTextbox(play, this->textID, &this->actor);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnSGoro_ActionSpringShrineGoron(EnSGoro* this, PlayState* play) {
    if ((EN_S_GORO_GET_MAIN_TYPE(&this->actor) == ENSGORO_TYPE_SHRINE_SPRING_F) ||
        !EnSGoro_UpdateCheerAnimation(this, play)) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->actionFlags |= ENSGORO_ACTIONFLAG_ENGAGED;
            this->textID = EnSGoro_ShrineGoron_NextTextID(this, play);
            Message_StartTextbox(play, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionSpringShrineGoronTalking;
        } else if ((this->actor.xzDistToPlayer < 250.0f) || (this->actor.isTargeted)) {
            func_800B863C(&this->actor, play);
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void EnSGoro_ActionSpringShrineGoronTalking(EnSGoro* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_LASTMESSAGE;
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_ENGAGED;
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.unk12023 = 4;
            this->actionFunc = EnSGoro_ActionSpringShrineGoron;
            return;
        }
        this->textID = EnSGoro_ShrineGoron_NextTextID(this, play);
        Message_StartTextbox(play, this->textID, &this->actor);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnSGoro_ActionShopGoron(EnSGoro* this, PlayState* play) {
    if (!(this->actionFlags & ENSGORO_ACTIONFLAG_ROLLEDUP)) {
        EnSGoro_UpdateToIdleAnimation(this);
    }
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFlags |= ENSGORO_ACTIONFLAG_ENGAGED;
        this->textID = EnSGoro_BombshopGoron_NextTextID(this, play);
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_ROLLEDUP)) {
            this->actionFlags &= ~ENSGORO_ACTIONFLAG_ROLLEDUP;
            this->animInfoIndex = ENSGORO_ANIM_UNROLL_A;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
            this->actionFunc = EnSGoro_ActionShopGoronFinishUnroll;
        } else {
            Message_StartTextbox(play, this->textID, &this->actor);
            this->actionFunc = EnSGoro_ActionShopGoronTalking;
        }
    } else if ((this->actor.xzDistToPlayer < 250.0f) || this->actor.isTargeted) {
        func_800B863C(&this->actor, play);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnSGoro_ActionShopGoronFinishUnroll(EnSGoro* this, PlayState* play) {

    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimationInfo[this->animInfoIndex].animation);

    if ((this->animInfoIndex == ENSGORO_ANIM_UNROLL_A) && (curFrame == lastFrame)) {
        this->animInfoIndex = ENSGORO_ANIM_IDLE_STAND;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, this->animInfoIndex);
        Message_StartTextbox(play, this->textID, &this->actor);
        this->actionFunc = EnSGoro_ActionShopGoronTalking;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnSGoro_ActionShopGoronTalking(EnSGoro* this, PlayState* play) {

    u8 msgState = Message_GetState(&play->msgCtx);

    if ((this->actionFlags & ENSGORO_ACTIONFLAG_HANDTAP)) {
        EnSGoro_UpdateToHandtapAnimation(this);
    } else if ((this->actionFlags & ENSGORO_ACTIONFLAG_TIRED)) {
        EnSGoro_UpdateSleepyAnimation(this);
    } else {
        EnSGoro_UpdateToIdleAnimation(this);
    }

    if (msgState == 6) {
        if (Message_ShouldAdvance(play)) {
            if ((this->actionFlags & ENSGORO_ACTIONFLAG_LASTMESSAGE)) {
                this->actionFlags &= ~ENSGORO_ACTIONFLAG_LASTMESSAGE;
                this->actionFlags &= ~ENSGORO_ACTIONFLAG_ENGAGED;
                this->textID = 0x0;
                this->actionFunc = EnSGoro_ActionShopGoron;
                return;
            }
            this->textID = EnSGoro_BombshopGoron_NextTextID(this, play);
            Message_StartTextbox(play, this->textID, &this->actor);
        }
    } else if ((msgState == 4) && (Message_ShouldAdvance(play))) {
        switch (play->msgCtx.choiceIndex) {
            case 0:
                this->bombbuyFlags |= ENSGORO_BOMBBUYFLAG_YESBUY;
                break;
            case 1:
                func_8019F230();
                this->bombbuyFlags &= ~ENSGORO_BOMBBUYFLAG_YESBUY;
                break;
        }

        this->textID = EnSGoro_BombshopGoron_NextTextID(this, play);
        if ((this->textID == 0x675) || (this->textID == 0x676)) {
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.unk12023 = 4;
            Actor_PickUp(&this->actor, play, GI_POWDER_KEG, 300.0f, 300.0f);
            this->actionFunc = EnSGoro_ActionShopTakePayment;
        } else {
            Message_StartTextbox(play, this->textID, &this->actor);
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnSGoro_ActionShopTakePayment(EnSGoro* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        func_801159EC(this->powderKegPrice * -1);
        this->actionFunc = EnSGoro_ActionShopFinishTransaction;
    } else {
        Actor_PickUp(&this->actor, play, GI_POWDER_KEG, 300.0f, 300.0f);
    }
}

void EnSGoro_ActionShopFinishTransaction(EnSGoro* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        Message_StartTextbox(play, this->textID, &this->actor);
        this->actionFunc = EnSGoro_ActionShopGoronTalking;
        return;
    }
    func_800B85E0(&this->actor, play, 400.0f, -1);
}

void EnSGoro_ActionAsleep(EnSGoro* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        Message_StartTextbox(play, 0x23A, &this->actor);
        this->actionFunc = EnSGoro_ActionAsleepMessageWait;
    } else if (this->actor.isTargeted) {
        func_800B863C(&this->actor, play);
    }
    EnSGoro_UpdateSleeping(this, play);
}

void EnSGoro_ActionAsleepMessageWait(EnSGoro* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == 6) {
        if (Message_ShouldAdvance(play)) {
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.unk12023 = 4;
            this->actionFunc = EnSGoro_ActionAsleep;
        }
    }
    EnSGoro_UpdateSleeping(this, play);
}

void EnSGoro_Init(Actor* thisx, PlayState* play) {

    EnSGoro* this = THIS;
    SkelAnime* skelAnime = &this->skelAnime;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, skelAnime, &gGoronSkel, &gGoronUnrollAnim, this->jointTable, this->morphTable,
                       GORON_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    if (this->actor.update != NULL) {
        s32 objIndex = Object_GetIndex(&play->objectCtx, OBJECT_OF1D_MAP);
        this->loadedObjIndex = objIndex;
        if (objIndex < 0) {
            Actor_MarkForDeath(&this->actor);
        }
    }
    this->actor.draw = EnSGoro_Draw;
    this->actionFunc = EnSGoro_ActionDefault;
}

void EnSGoro_Destroy(Actor* thisx, PlayState* play) {

    EnSGoro* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnSGoro_Update(Actor* thisx, PlayState* play) {

    EnSGoro* this = (EnSGoro*)thisx;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 5U);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->loadedObjIndex].segment);
    SkelAnime_Update(&this->skelAnime);
    if (this->animInfoIndex != ENSGORO_ANIM_SLEEPY) {
        EnSGoro_UpdateAttentionTarget(this, play);
    }
    EnSGoro_UpdateEyes(this);
    EnSGoro_UpdateActorFocus(this);
    EnSGoro_UpdateCollider(this, play);
}

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

s32 EnSGoro_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnSGoro_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {

    s32 delayMode;
    s32 addPlayerFaceRotation;
    EnSGoro* this = THIS;

    if (limbIndex != GORON_LIMB_BODY) {
        if ((limbIndex == GORON_LIMB_HEAD) && (this->animInfoIndex != ENSGORO_ANIM_SLEEPY)) {
            if ((this->actionFlags & ENSGORO_ACTIONFLAG_FACEPLAYER)) {
                addPlayerFaceRotation = true;
            } else {
                addPlayerFaceRotation = false;
            }
            if (this->frameTimer != 0) {
                delayMode = true;
            } else {
                delayMode = false;
            }

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
        if ((this->actionFlags & ENSGORO_ACTIONFLAG_FACEPLAYER)) {
            addPlayerFaceRotation = true;
        } else {
            addPlayerFaceRotation = false;
        }
        if (this->frameTimer != 0) {
            delayMode = true;
        } else {
            delayMode = false;
        }

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

void EnSGoro_DrawUnrolled(EnSGoro* this, PlayState* play) {

    SkelAnime* skelAnime;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    gDPPipeSync(POLY_OPA_DISP++);

    skelAnime = &this->skelAnime;
    SkelAnime_DrawTransformFlexOpa(play, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                   EnSGoro_OverrideLimbDraw, NULL, EnSGoro_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnSGoro_DrawRolledUp(EnSGoro* this, PlayState* play) {

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                     this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Translate(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_Translate(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gGoronRolledUpDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnSGoro_Draw(Actor* thisx, PlayState* play) {

    EnSGoro* this = (EnSGoro*)thisx;

    if ((this->actionFlags & ENSGORO_ACTIONFLAG_ROLLEDUP)) {
        EnSGoro_DrawRolledUp(this, play);
        return;
    }
    EnSGoro_DrawUnrolled(this, play);
}
