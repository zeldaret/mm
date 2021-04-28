#include "z_en_ginko_man.h"

#define FLAGS 0x00000009

#define THIS ((EnGinkoMan*)thisx)

void EnGinkoMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnGinkoMan_Update(EnGinkoMan* this, GlobalContext* globalCtx);
void EnGinkoMan_Draw(Actor* thisx, GlobalContext* globalCtx);
//void EnGinkoMan_Draw(EnGinkoMan* this, GlobalContext* globalCtx);

void func_80A64554(EnGinkoMan* this);
void func_80A65490(EnGinkoMan* this);
void func_80A6557C(EnGinkoMan* this);
void func_80A656C4(EnGinkoMan* this);
void func_80A65800(EnGinkoMan* this);

void func_80A645A4(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65590(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A646F4(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A656D8(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65844(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A654A4(EnGinkoMan* this, GlobalContext* globalCtx);
void func_80A65988(EnGinkoMan* this, GlobalContext* globalCtx);

const ActorInit En_Ginko_Man_InitVars = {
    ACTOR_EN_GINKO_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnGinkoMan),
    (ActorFunc)EnGinkoMan_Init,
    (ActorFunc)EnGinkoMan_Destroy,
    (ActorFunc)EnGinkoMan_Update,
    (ActorFunc)EnGinkoMan_Draw
};

// gets passed to func_800BDC5C as array ptr with index
ActorAnimationEntry D_80A65D60[] = {
{0x060008C0, 1.0f, 0.0f, 0.0f, 0, -4.0f,}, // smacking the floor
{0x060043F0, 1.0f, 0.0f, 0.0f, 0, -4.0f,}, // after stamp return
{0x06004F40, 1.0f, 0.0f, 0.0f, 2, -4.0f,}, // stamp reach
{0x06000AC4, 1.0f, 0.0f, 0.0f, 0, -4.0f,},
{0x06004A7C, 1.0f, 0.0f, 0.0f, 0, -4.0f,},
};

void EnGinkoMan_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;
    this->actor.targetMode = 1;
    this->actor.uncullZoneForward = 400.0f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 100;
    this->curTextId = 0;
    this->newAccountFlag = 0;
    this->unk260 = 0;
    this->unk25C = 0;
    this->unk25A = 0;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600C240, &D_060043F0, &this->limbDrawTbl, &this->transitionDrawTbl, 0x10);
    func_80A64554(this);
}

void EnGinkoMan_Destroy(Actor *thisx, GlobalContext *globalCtx) { }

// setup wait for dialogue
void func_80A64554(EnGinkoMan* this) {

    this->actor.flags |= 1;
    func_800BDC5C(&this->skelAnime, &D_80A65D60, 1);
    this->actionFunc = func_80A645A4;
}

//action func: waiting for dialogue?
void func_80A645A4(EnGinkoMan *this, GlobalContext *globalCtx) {
    s32 dYaw;
    s32 dYawABS;

    dYaw = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    func_80A65988(this, globalCtx);
    if (func_800B84D0(&this->actor, globalCtx)) {
        if ((gSaveContext.perm.bankRupees & 0xFFFF) == 0) {
            func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
            func_801518B0(globalCtx, 0x44CU, &this->actor);
            this->curTextId = 0x44C; // would you like to make an account
        } else {
            func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                func_801518B0(globalCtx, 0x467U, &this->actor);
                this->curTextId = 0x467; // "What's this? You need somethin' on a day like this?
            } else {
                func_801518B0(globalCtx, 0x466U, &this->actor);
                this->curTextId = 0x466; // What's this? You need somethin'?
            }
        }
        func_80A65490(this);
    } else {

        dYawABS = dYaw < 0 ? -dYaw : dYaw;
        if (dYawABS < 0x1555) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

#if NON_EQUIVELENT
// non-equiv: case 14 is possibly still non-equiv but def does not match, hard to tell 
// if else inside of jump tables makes mips2c confused, also late rodata
// action func: non-input dialogue
void func_80A646F4(EnGinkoMan *this, GlobalContext *globalCtx) {
    u32 tempEDC;
    s16* previousBankValue;

    if (func_80147624(globalCtx) == 0) {
      return;
    }
    
    //if (temp_t6 < 0x33) { //phi_a3_3 = globalCtx; //goto **(&jtbl_D_80A65DE0 + (temp_t6 * 4));
    switch (this->curTextId - 0x44C) {

    case 0: // "Hey there, little guy!  Won't you deposit some Rupees? (first dialogue)
        globalCtx = globalCtx;
        func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
        if ((gSaveContext.perm.weekEventReg[10] & 8) != 0) {
            func_801518B0(globalCtx, 0x44E, &this->actor);
            this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        } else {
            func_801518B0(globalCtx, 0x44D, &this->actor);
            this->curTextId = 0x44D; // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
        }
        break; 

    case 1: // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
        func_801518B0(globalCtx, 0x44E, &this->actor);
        this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        return;
    case 3: // "...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
        func_801518B0(globalCtx, 0x450, &this->actor);
        this->curTextId = 0x450; // "How much? How much?  [rupee prompt]
        return;

    case 7: // you deposited a tiny amount
    case 8: // you deposited a normal amount
    case 9: // you deposited alot
        if (this->newAccountFlag == 1) {
            this->newAccountFlag = 0;
            if (this->curTextId != 0x453) { // "That's it? That ain't nothing at all, big spender!
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            }
            func_801518B0(globalCtx, 0x461, &this->actor);
            this->curTextId = 0x461; // So, little guy, what's your name?
        } else { 
            if (this->curTextId == 0x453) { // "That's it? That ain't nothing at all, big spender!
                globalCtx = globalCtx;
                func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
            }
            globalCtx->msgCtx.bankRupees = gSaveContext.perm.bankRupees & 0xFFFF;
            func_801518B0(globalCtx, 0x45A, &this->actor);
            this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        }
        break;
    case 10: // "Is that so? Think about it, little guy!"
    case 13: // "Heyyy! You don't have that much!
        func_801518B0(globalCtx, 0x44E, &this->actor);
        this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        return;

    case 14: // "All right, little guy, now I've got a total of [rupees] from you!"

        /***** WARNING: this case is non-equivelent ****/
        
        tempEDC = gSaveContext.perm.bankRupees & 0xFFFF;
        if ((tempEDC >= 200) 
        && (this->previousBankValue < 200) 
        && ((gSaveContext.perm.weekEventReg[0x3B] & 0x40) == 0)) {
            //block_20:
            gSaveContext.perm.weekEventReg[0x3B] = gSaveContext.perm.weekEventReg[0x3B] | 0x40;
            func_801518B0(globalCtx, 0x45B, &this->actor);
            this->curTextId = 0x45B; // "What's this? You've already saved up 200 Rupees!?!
            return;
        } // bright pink arrow

        // branch likely when shouldn'tbe
        if ( (tempEDC >= 1000)
        && ((this->previousBankValue) < 1000)
        && (gSaveContext.perm.weekEventReg[0x3B] & 0x80) == 0) {
           //block_24:
            gSaveContext.perm.weekEventReg[0x3B] |= 0x80;
            func_801518B0(globalCtx, 0x45C, &this->actor);
            this->curTextId = 0x45C; // "What's this? You've already saved up 1000 Rupees!?!
            return;
        } // bright blue arrow

        if (( this->previousBankValue) >= 5000) { // added back in because missing
            if ((((s16) tempEDC ) < 5000) 
            && (( gSaveContext.perm.weekEventReg[0x3B] & 1) == 0)) {
                gSaveContext.perm.weekEventReg[0x3B] |= 1;
                func_801518B0(globalCtx, 0x45D, &this->actor);
                this->curTextId = 0x45D; // "What's this? You've already saved up 5000 Rupees?!
                return;
            } else { // olive arrow
                //block_28:
                if (this->previousBankValue < gSaveContext.perm.bankRupees) {
                //if (*previousBankValue < gSaveContext.perm.bankRupees) {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x45E, &this->actor);
                    this->curTextId = 0x45E; // "...Hang on there, little guy.  I can't take any more deposits.  Sorry..."
                    return;
                } else {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 0); // this is 460 just renamed for visual
                    func_801518B0(globalCtx, 0x460, &this->actor);
                    this->curTextId = 0x460; // "Come back and deposit some after you save up a bunch!"
                    return;
                }
            }
        }

        // bright green arrow
        func_800BDC5C(&this->skelAnime, D_80A65D60, 0); 
        func_801518B0(globalCtx, 0x460, &this->actor);
        this->curTextId = 0x460;  // "Come back and deposit some after you save up a bunch!" 
        break;

    case 15: // given 200 reward
    case 16: // given 1000 reward
    case 17: // given 5000 reward
        this->unk260 = 0;
        globalCtx = globalCtx;
        func_801477B4(globalCtx);
        func_80A6557C(this);
        func_80A65590(this, globalCtx);
        return;
    case 21: // So, little guy, what's your name?
        func_801518B0(globalCtx, 0x462, &this->actor);
        this->curTextId = 0x462; // Hmm... Link is it?
        return;
    case 22: // Hmm.. Link is it?
        func_801518B0(globalCtx, 0x463, &this->actor);
        this->curTextId = 0x463; // Got it... I won't forget your deposits. Let me stamp you
        return;
    case 23: // Got it... I won't forget your deposits. Let me stamp you
        func_801518B0(globalCtx, 0x464, &this->actor);
        this->curTextId = 0x464; // Hey, relax! It doesn't leave any marks
        return;
    case 24: // Hey, relax! It doesn't leave any marks
        //globalCtx->msgCtx.pad11F23 = 0x44;
        globalCtx->msgCtx.pad11F23[0] = 0x44;
        func_80A65800(this); // stamp player
        return;
    case 25: // "There! Now I'll know you when I see you!"
        globalCtx = globalCtx;
        func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
        globalCtx->msgCtx.bankRupees = gSaveContext.perm.bankRupees & 0xFFFF;
        func_801518B0(globalCtx, 0x45A, &this->actor);
        this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        return;
    case 26: // What's this? You need somethin'?
    case 27: // "What's this? You need somethin' on a day like this?  You haven't evacuated yet?
        func_801518B0(globalCtx, 0x468, &this->actor);
        this->curTextId = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
        return;
    case 29: // "Excuse me, but let me take a look at you..."
        func_80A65800(this); // stamp player
        return;
    case 30: // "Ah, yes...[Link].  If I remember, you're the little guy who deposited [rupees]."
    case 32: // "Ah, yes...[Link], right?  If I remember, you're the little guy who deposited [rupees]."
    case 50: // "Your deposits total [rupees]."
        if (this->unk25C == 0) {
            if ((u32) (gSaveContext.perm.bankRupees & 0xFFFF) >= 0x1388) {
                func_801518B0(globalCtx, 0x45F, &this->actor);
                this->curTextId = 0x45F; // "Excuuuse me! But I can't take anymore deposits!
            } else if (gSaveContext.perm.unk24.currentRupees == 0) {
                func_801518B0(globalCtx, 0x458, &this->actor);
                this->curTextId = 0x458; // "Hmm...You play mean jokes, little guy! You haven't even got a single Rupee!  
            } else {
                func_801518B0(globalCtx, 0x479, &this->actor);
                this->curTextId = 0x479; // "Well, are you gonna make a deposit?"
            }
        } else if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
            func_801518B0(globalCtx, 0x46D, &this->actor);
            // "Look, little guy, if it's 'cause of the bad rumors going around, forget it! They're just rumors!"
            this->curTextId = 0x46D;
        } else {
            func_801518B0(globalCtx, 0x46B, &this->actor);
            this->curTextId = 0x46B; // "So..."
        }
        this->unk25C = 0;
        return;
    case 31: // So...
        func_801518B0(globalCtx, 0x46E, &this->actor);
        this->curTextId = 0x46E; // "How much do you want?  [rupee prompt]
        return;
    case 33: // "Look, little guy, if it's 'cause of the bad rumors going around, forget it! They're just rumors!"
        func_801518B0(globalCtx, 0x46B, &this->actor);
        this->curTextId = 0x46B; // So...
        return;
    case 36: // "Is that so?  Come back and deposit some after saving up a bunch!"
        if (func_80147624(globalCtx) == 0) {
            return;
        }
        func_801477B4(globalCtx);
        this->unk260 = 0;
        func_80A64554(this); // change to waiting for approach
        return;
    case 42: // "...You haven't deposited that many Rupees, so that much isn't available for withdrawal. Do the math! 
        func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
    case 41: // "What's this?  Look, little guy, you can't hold this many rupees! You got that?"
    case 48: // "Is that so?  Think it over, little guy!  So what are you gonna do?"
    case 49: // duplicate of 48
        func_801518B0(globalCtx, 0x468, &this->actor);
        this->curTextId = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
        return;
    case 38: // "What's this? It's a waste to take out such a tiny bit!  ...But if you say so!"
    case 39: // Use it wisely...
    case 40: // "Aw, you're taking out all that?  If you spend it like that, it'll all be gone before you know it!"
        if ((gSaveContext.perm.bankRupees & 0xFFFF) == 0) {
            func_801518B0(globalCtx, 0x478, &this->actor);
            //  "Look, little guy, all the Rupees you deposited are gone, so you can't use that stamp anymore."
            this->curTextId = 0x478;
        } else {
            globalCtx->msgCtx.bankRupees = gSaveContext.perm.bankRupees & 0xFFFF;
            func_801518B0(globalCtx, 0x45A, &this->actor);
            this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        }
        break;
    case 43: // "...You know, at this time of day there's a 4 Rupee service charge on withdrawals!"
        func_801518B0(globalCtx, 0x471, &this->actor);
        this->curTextId = 0x471; // "Are you really withdrawing [rupees selected]? Y/n"
        this->unk25A = globalCtx->msgCtx.unk1206C;
        return;
    case 45: // "Look, little guy, all the Rupees you deposited are gone, so you can't use that stamp anymore."
        func_801518B0(globalCtx, 0x44F, &this->actor);
        this->curTextId = 0x44F; // "All right! So..."
        return;
    default:
        break;
    } // end switch

} // */
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A646F4.asm")
#endif

#if NON_MATCHING
// NON-MATCHING: lots of regalloc 
// ROM SHIFT: a couple redundant li 0x4806 added
// actionfunc: wait for player dialogue input
void func_80A64DC4(EnGinkoMan *this, GlobalContext *globalCtx) {

    // branch likely instead of branch, fixed by adding a fake if though
    // probably because its supposed to wrap around the whole switch, but hoping thats not the case
    if (func_80147624(globalCtx) == 0) {
      return;
    }

    switch (this->curTextId) {

    case 0x44E: // "...So, what'll it be?
        if (globalCtx->msgCtx.choiceIndex == 0) {
            if ( (gSaveContext.perm.bankRupees & 0xFFFF) >= 0x1388) {
                play_sound(0x4806);// NA_SE_SY_ERROR
                func_801518B0(globalCtx, 0x45F, &this->actor);
                this->curTextId = 0x45F; // bank full, cannot accept more
                return;
            }
            else {
                if (gSaveContext.perm.unk24.currentRupees > 0) {
                    func_8019F208(0x4806);
                    func_801518B0(globalCtx, 0x44F, &this->actor);
                    this->curTextId = 0x44F; // "All right! so..."
                } else {
                    play_sound(0x4806); // NA_SE_SY_ERROR
                    func_801518B0(globalCtx, 0x458, &this->actor);
                    this->curTextId = 0x458; // you haven't even gotten a single rup
                }
                return;
            } 
        }
        func_8019F230();
        func_801518B0(globalCtx, 0x451, &this->actor);
        this->curTextId = 0x451; // dont say that, come on, trust me!
        break;

    case 0x452: // Really? are you really depositing rupees?

        if (globalCtx->msgCtx.choiceIndex == 0){ // Selected: YES
            if (gSaveContext.perm.unk24.currentRupees < globalCtx->msgCtx.bankRupeesSelected) {
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x459, &this->actor);
                this->curTextId = 0x459; // HEY you dont have that much
                //return;
            } else {
                func_8019F208(0x4806);
                ////temp_v0_5 = globalCtx->msgCtx.bankRupeesSelected;
                if (globalCtx->msgCtx.bankRupeesSelected >= 100) {
                    func_801518B0(globalCtx, 0x455, &this->actor);
                    this->curTextId = 0x455; // You're really going to be give me that much? Rich little guy!
                } else if (globalCtx->msgCtx.bankRupeesSelected >= 10) {
                    func_801518B0(globalCtx, 0x454, &this->actor);
                    this->curTextId = 0x454; // Seriously? that's a lot. A lot!
                } else {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x453, &this->actor);
                    this->curTextId = 0x453; // That's it? That aint nothing at all
                }
                if ((gSaveContext.perm.bankRupees & 0xFFFF) == 0) {
                    this->newAccountFlag = 1;
                }
                func_801159EC((s16) -(s32) globalCtx->msgCtx.bankRupeesSelected);
                this->previousBankValue = gSaveContext.perm.bankRupees;

                gSaveContext.perm.bankRupees = ((gSaveContext.perm.bankRupees & 0xFFFF) 
                    + globalCtx->msgCtx.bankRupeesSelected) | (gSaveContext.perm.bankRupees & 0xFFFF0000);
            }
        }else{ // Selected: NO
            func_8019F230();
            func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            // different forms?
            if ((gSaveContext.perm.bankRupees & 0xFFFF) == 0) { // @B74
                func_801518B0(globalCtx, 0x456, &this->actor);
                this->curTextId = 0x456; // Is that so? think about it 
            } else {
                func_801518B0(globalCtx, 0x47D, &this->actor);
                this->curTextId = 0x47D; // is that so? think it over
            }
        }
        break;

    case 0x468:  // [Deposit rupees selected] // location: @C38
        // FAKE MATCH
        if (globalCtx->msgCtx.choiceIndex) {} // -5000 permuter score: regalloc and branch likely swapping

        if (globalCtx->msgCtx.choiceIndex == 2) {
            func_8019F230();
            func_801518B0(globalCtx, 0x470, &this->actor);
            this->curTextId = 0x470; // "Is that so? Come back and deposit some after saving up a bunch!"
        } else {
            func_8019F208();
            this->unk25C = globalCtx->msgCtx.choiceIndex;
            if (this->unk260 == 0) {                          // @C94
                this->unk260 = 1;
                func_801518B0(globalCtx, 0x469, &this->actor);
                this->curTextId = 0x469; // Excuse me, but let me look at you
            } else {
                func_801518B0(globalCtx, 0x47E, &this->actor);
                this->curTextId = 0x47E; // your deposits total X rupees
            }
        }
        break;

    case 0x471: // Are you really withdrawling [selected rupees]? // @CDC
        // 0xEDC: bankRupees
        if (globalCtx->msgCtx.choiceIndex == 0) {
            // s32 casts required for slt instead of sltu
            if ((s32)((gSaveContext.perm.bankRupees & 0xFFFF)) < ((s32)( globalCtx->msgCtx.bankRupeesSelected + this->unk25A))) { 
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->skelAnime, D_80A65D60, 0);       // @ D30
                func_801518B0(globalCtx, 0x476, &this->actor);
                this->curTextId = 0x476; // you dont have enough deposited to withdrawl
                return;
            }
            
            // an array of what though
            //if ((s32) *(&D_801C1E2C + (((u32) ((s32) gSaveContext.perm.inv.unk48 & D_801C1DD0) >> D_801C1E08) * 2))
               //< (globalCtx->msgCtx.bankRupeesSelected + gSaveContext.perm.unk24.currentRupees)) {
            if ( (D_801C1E2C[ ( gSaveContext.perm.inv.unk48 & D_801C1DD0) >> D_801C1E08])
               < (globalCtx->msgCtx.bankRupeesSelected + gSaveContext.perm.unk24.currentRupees)) {
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_801518B0(globalCtx, 0x475, &this->actor);
                this->curTextId = 0x475; // You can't hold that many in your wallet
                return;
            }
            func_8019F208(0x4806);

            if (globalCtx->msgCtx.bankRupeesSelected >= 100) {
                func_801518B0(globalCtx, 0x474, &this->actor);
                this->curTextId = 0x474; // Aw, you're taking out all that?
            } else if (globalCtx->msgCtx.bankRupeesSelected >= 10) {
                func_801518B0(globalCtx, 0x473, &this->actor);
                this->curTextId = 0x473; // use it wisely
            } else {
                func_801518B0(globalCtx, 0x472, &this->actor);
                this->curTextId = 0x472; // It's a waste to take out such a tiny bit
            }
            this->previousBankValue = (s16) gSaveContext.perm.bankRupees;
            //temp_v0_4 = gSaveContext.perm.bankRupees;
            gSaveContext.perm.bankRupees = (((gSaveContext.perm.bankRupees & 0xFFFF) - globalCtx->msgCtx.bankRupeesSelected) 
              - this->unk25A) | (gSaveContext.perm.bankRupees & 0xFFFF0000);
            func_801159EC( (s16) globalCtx->msgCtx.bankRupeesSelected, &gSaveContext); // cast req
            return;
        } else { 
            //func_8019F230(&gSaveContext);
            func_8019F230();
            func_801518B0(globalCtx, 0x47C, &this->actor);
            this->curTextId = 0x47C; // "Is that so? Think it over, little guy! So what are you gonna do?"
        }
    } // end switch
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A64DC4.asm")
#endif

// action func: wait for rupee count set
void func_80A65364(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->curTextId){
            case 0x450: // "How much? How much?" [rupee prompt] Set the amount with [Control Stick] and
                if (globalCtx->msgCtx.bankRupeesSelected == 0) {
                    globalCtx = globalCtx;
                    func_800BDC5C(&this->skelAnime, &D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x457, &this->actor);
                    this->curTextId = 0x457; // Zero Rupees? Cruel joke!
                } else {
                    func_801518B0(globalCtx, 0x452, &this->actor);
                    this->curTextId = 0x452; // Really? are you really depositing [x]? Y/n
                }
                break;

            case 0x46E: // "How much do you want?"  [rupee prompt] Set the amount with [Control Stick]
                if (globalCtx->msgCtx.bankRupeesSelected == 0) {
                    func_801518B0(globalCtx, 0x46F, &this->actor);
                    this->curTextId = 0x46F; // "Zero Rupees?!?  That's a cruel joke!"
                } else if (gSaveContext.perm.isNight == 1) {
                    func_801518B0(globalCtx, 0x477, &this->actor);
                    this->curTextId = 0x477; // "...You know, at this time of day there's a 4 Rupee service charge...
                } else {
                    func_801518B0(globalCtx, 0x471, &this->actor);
                    this->curTextId = 0x471; // "Are you really withdrawing [rupees selected]? Y/n
                    this->unk25A = 0;
                }
                break;
        }
    }
}

// setup
void func_80A65490(EnGinkoMan* this) {
    this->actionFunc = func_80A654A4;
}

//action func
void func_80A654A4(EnGinkoMan *this, GlobalContext *globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 2:
            func_80A64554(this); // change to waiting for appraoch
            break;
        case 4:
            func_80A64DC4(this, globalCtx); // wait for player dilogue choice
            break;
        case 5:
            func_80A646F4(this, globalCtx); // wait for non-input dialogue
            break;
        case 6:
            if (func_80147624(globalCtx) != 0) {
                this->unk260 = 0;
                func_80A64554(this); // change to waiting for approach
            }
            break;
        case 14:
            func_80A65364(this, globalCtx); // wait for rupee count set
            break;
        case 0:
        default:
            break;
    }

    if ((this->skelAnime.animCurrentSeg == &D_060008C0) 
      && (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0)) {
        Audio_PlayActorSound2(this, 0x2992); // NA_SE_EV_BANK_MAN_HAND_HIT
    }
}

void func_80A6557C(EnGinkoMan* this) {
    this->actionFunc = func_80A65590;
}

// action func: give wallet checks
void func_80A65590(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        // ? when would bank have a parent?
        this->actor.parent = NULL;
        func_80A656C4(this);
    } else if (this->curTextId == 0x45B) { // "Whats this, you already saved up 200?"
        if (((&gSaveContext)->perm.weekEventReg[10] & 8) == 0) {
            func_800B8A1C(&this->actor, globalCtx,
                 ((u32) ((s32) (&gSaveContext)->perm.inv.unk48 & D_801C1DD0) >> D_801C1E08) + 8, 500.0f, 100.0f);
        } else {
            func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
        }
    } else if (this->curTextId == 0x45C) { // "Whats this, you already saved up 5000?"
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    } else if (((&gSaveContext)->perm.weekEventReg[0x3B] & 8) == 0) {
        func_800B8A1C(&this->actor, globalCtx, 12, 500.0f, 100.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    }
}

//setup 
void func_80A656C4(EnGinkoMan* this) {
    this->actionFunc = func_80A656D8;
}

# if NON_MATCHING
// NON_MATCHING: minor regalloc at globalCtx into func_80152498
void func_80A656D8(EnGinkoMan* this, GlobalContext *globalCtx) {
    GlobalContext* gCtx;// = globalCtx;

    if (func_800B84D0(&this->actor, globalCtx)) {
        if (((gSaveContext.perm.weekEventReg[0xA] & 8) == 0) && (this->curTextId == 0x45B)) {
            // "What's this? You've already saved up 200 Rupees!?!  Well, little guy, here's your special gift. Take it!"
            gSaveContext.perm.weekEventReg[0xA] |= 8;
            func_801518B0(globalCtx, 0x47A, &this->actor);
            if (1) { // might be fake, but it solves almost everything
                this->curTextId = 0x47A; // "See! Doesn't it hold more than your old one?
            }
        } else {
            func_800BDC5C(&this->skelAnime, &D_80A65D60, 1);
            func_801518B0(globalCtx, 0x47B, &this->actor);
            this->curTextId = 0x47B; // "Is that so?  Think it over, little guy!  So what are you gonna do?"
        }
        func_80A65490(this);
    } else if (this->curTextId == 0x45D) { // saved up 5000 rupees for HP
        //if ((func_80152498(&globalCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
        gCtx = globalCtx;
        if ((func_80152498(&gCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
            if ((gSaveContext.perm.weekEventReg[0x3B] & 8) == 0) {
                gSaveContext.perm.weekEventReg[0x3B] |= 8;
            }
            func_80A64554(this); // change to waiting for approach
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 500.0f, -1);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A656D8.asm")
#endif

// setup: stamp player
void func_80A65800(EnGinkoMan* this) {
    func_800BDC5C(&this->skelAnime, D_80A65D60, 2);
    this->actionFunc =  func_80A65844;
}

// action func: stamping and stamp checking
void func_80A65844(EnGinkoMan *this, GlobalContext *globalCtx) {
    if ((this->curTextId == 0x464) // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
      && (func_801378B8(&this->skelAnime, 10.0f))) {
        Audio_PlayActorSound2(this, 0x2993); // NA_SE_EV_HANKO "stamp"
    }

    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        switch(this->curTextId){
            case 0x464: // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x465, &this->actor);
                this->curTextId = 0x465; // "There! Now I'll know you when I see you!"
                break;

            case 0x469: // "Excuse me, but let me take a look at you..."
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                globalCtx->msgCtx.bankRupees = (gSaveContext.perm.bankRupees & 0xFFFF); 
                // perm.day cast req for div vs divu
                if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                    func_801518B0(globalCtx, 0x46C, &this->actor);
                    this->curTextId = 0x46C; // "Ah, yes...[Link], right?
                } else {
                    func_801518B0(globalCtx, 0x46A, &this->actor);
                    this->curTextId = 0x46A; // "Ah, yes...[Link].
                }
                break;
        }

        func_80A65490(this);
    }
}

// changes between two animations
void func_80A65988(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (this->actor.xzDistToPlayer > 160.0f) {
        if (this->animTimer == 0) {
            if (this->skelAnime.animCurrentSeg != &D_06004A7C) { // not 4
                this->animTimer = 0x28;
                func_800BDC5C(&this->skelAnime, &D_80A65D60, 4);
            }
        }
    } else if ((this->animTimer == 0) && (this->skelAnime.animCurrentSeg != &D_06000AC4)) { // not 3
        this->animTimer = 0x28;
        func_800BDC5C(&this->skelAnime, &D_80A65D60, 3);
    }

    if (this->animTimer != 0) {
        this->animTimer--;
    }
}

// update extension
//think this function adjusts his animation so that he faces the player while talking
void func_80A65A5C(EnGinkoMan *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->skelAnime.animCurrentSeg != &D_06004A7C) { //not 4
        func_800E9250(globalCtx, &this->actor, &this->limb15Rot, &this->limb8Rot,
           this->actor.focus.pos);
    } else {
        func_800E8F08(&this->limb15Rot, &this->limb8Rot);
    }
}

void EnGinkoMan_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;

    this->actionFunc(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    func_80A65A5C(this, globalCtx);
}

//override limbdraw
s32 func_80A65B44(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor){
    EnGinkoMan* this = (EnGinkoMan*) actor;
    if (limbIndex == 15) {
        *dList = &D_0600B1D8; 
    }
    if (limbIndex == 15) {
        SysMatrix_InsertTranslation(1500.0f, 0.0f, 0.0f, 1);
        SysMatrix_InsertXRotation_s(this->limb15Rot.y, 1);
        SysMatrix_InsertZRotation_s(this->limb15Rot.x, 1);
        SysMatrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, 1);
    } else if (limbIndex == 8) {
        SysMatrix_InsertXRotation_s(-this->limb8Rot.y, 1);
        SysMatrix_InsertZRotation_s(-this->limb8Rot.x, 1);
    }
    return 0;
}

// post limbdraw
void func_80A65C18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {}

void EnGinkoMan_Draw(Actor* thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, &func_80A65B44, &func_80A65C18, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
