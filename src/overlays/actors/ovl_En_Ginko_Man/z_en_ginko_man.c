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

// gets passed to other functions as is
UNK_TYPE D_80A65D60[] = {
0x060008C0, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x060043F0, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x06004F40, 0x3F800000, 0x00000000, 0x00000000, 0x02000000, 0xC0800000,
0x06000AC4, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x06004A7C, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000,
0x00000000, 0x00000000,
};

void EnGinkoMan_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnGinkoMan* this = THIS;
    this->actor.targetMode = 1;
    this->actor.uncullZoneForward = 400.0f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 100;
    this->lastText = 0;
    this->unk25E = 0;
    this->unk260 = 0;
    this->unk25C = 0;
    this->unk25A = 0;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600C240, &D_060043F0, &this->unk18C, &this->unk1EC, 0x10);
    func_80A64554(this);
}

void EnGinkoMan_Destroy(Actor *thisx, GlobalContext *globalCtx) { }

// init extension
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
        if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) {
            func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
            func_801518B0(globalCtx, 0x44CU, &this->actor);
            this->lastText = 0x44C; // would you like to make an account
        } else {
            func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                func_801518B0(globalCtx, 0x467U, &this->actor);
                this->lastText = 0x467; // "What's this? You need somethin' on a day like this?
            } else {
                func_801518B0(globalCtx, 0x466U, &this->actor);
                this->lastText = 0x466; // What's this? You need somethin'?
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

// action func: non-imput dialogue
// if else inside of jump tables
// case 14 is possibly still non-equiv but def does not match
///*
void func_80A646F4(EnGinkoMan *this, GlobalContext *globalCtx) {
    u32 tempEDC;
    //u8 weekEventReg;
    s16* unk262;

    if (func_80147624(globalCtx) == 0) {
      return;
    }
    
    //if (temp_t6 < 0x33) { //phi_a3_3 = globalCtx; //goto **(&jtbl_D_80A65DE0 + (temp_t6 * 4));
    switch (this->lastText - 0x44C) {

    case 0: // "Hey there, little guy!  Won't you deposit some Rupees? (first dialogue)
        globalCtx = globalCtx;
        func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
        if ((gSaveContext.perm.weekEventReg[10] & 8) != 0) {
            func_801518B0(globalCtx, 0x44E, &this->actor);
            this->lastText = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        } else {
            func_801518B0(globalCtx, 0x44D, &this->actor);
            this->lastText = 0x44D; // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
        }
        break; 

    case 1: // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
        func_801518B0(globalCtx, 0x44E, &this->actor);
        this->lastText = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        return;
    case 3: // "...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
        func_801518B0(globalCtx, 0x450, &this->actor);
        this->lastText = 0x450; // "How much? How much?  [rupee prompt]
        return;

    case 7: // you deposited a tiny amount
    case 8: // you deposited a normal amount
    case 9: // you deposited alot
        if (this->unk25E == 1) {
            this->unk25E = 0;
            if (this->lastText != 0x453) { // "That's it? That ain't nothing at all, big spender!
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            }
            func_801518B0(globalCtx, 0x461, &this->actor);
            this->lastText = 0x461; // So, little guy, what's your name?
        } else { 
            if (this->lastText == 0x453) { // "That's it? That ain't nothing at all, big spender!
                globalCtx = globalCtx;
                func_800BDC5C(&this->skelAnime, D_80A65D60, 0);
            }
            globalCtx->msgCtx.unk1207C = gSaveContext.perm.unkEDC & 0xFFFF;
            func_801518B0(globalCtx, 0x45A, &this->actor);
            this->lastText = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        }
        break;
    case 10: // "Is that so? Think about it, little guy!"
    case 13: // "Heyyy! You don't have that much!
        func_801518B0(globalCtx, 0x44E, &this->actor);
        this->lastText = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
        return;

    case 14: // "All right, little guy, now I've got a total of [rupees] from you!"
        tempEDC = gSaveContext.perm.unkEDC & 0xFFFF;
        if ((tempEDC >= 200) 
        && (this->unk262 < 200) 
        && ((gSaveContext.perm.weekEventReg[0x3B] & 0x40) == 0)) {
            //block_20:
            gSaveContext.perm.weekEventReg[0x3B] = gSaveContext.perm.weekEventReg[0x3B] | 0x40;
            func_801518B0(globalCtx, 0x45B, &this->actor);
            this->lastText = 0x45B; // "What's this? You've already saved up 200 Rupees!?!
            return;
        } // bright pink arrow

        // branch likely when shouldn'tbe
        //unk262 = & this->unk262;
        if ( (tempEDC >= 1000)
        && ((this->unk262) < 1000)
        //&& ((*unk262) < 0x3E8)
        && (gSaveContext.perm.weekEventReg[0x3B] & 0x80) == 0) {
           //block_24:
            gSaveContext.perm.weekEventReg[0x3B] |= 0x80;
            func_801518B0(globalCtx, 0x45C, &this->actor);
            this->lastText = 0x45C; // "What's this? You've already saved up 1000 Rupees!?!
            return;
        } // bright blue arrow


        if (( this->unk262) >= 5000) { // added back in because missing
        //if ((*unk262) >= 0x1388) { // added back in because missing
            if ((((s16) tempEDC ) < 5000) 
            && (( gSaveContext.perm.weekEventReg[0x3B] & 1) == 0)) {
                gSaveContext.perm.weekEventReg[0x3B] |= 1;
                func_801518B0(globalCtx, 0x45D, &this->actor);
                this->lastText = 0x45D; // "What's this? You've already saved up 5000 Rupees?!
                return;
            } else { // olive arrow
                //block_28:
                if (this->unk262 < gSaveContext.perm.unkEDC) {
                //if (*unk262 < gSaveContext.perm.unkEDC) {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x45E, &this->actor);
                    this->lastText = 0x45E; // "...Hang on there, little guy.  I can't take any more deposits.  Sorry..."
                    return;
                } else {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 0); // this is 460 just renamed for visual
                    func_801518B0(globalCtx, 0x460, &this->actor);
                    this->lastText = 0x460; // "Come back and deposit some after you save up a bunch!"
                    return;
                }

            }
        }

        // bright green arrow
        func_800BDC5C(&this->skelAnime, D_80A65D60, 0); 
        func_801518B0(globalCtx, 0x460, &this->actor);
        this->lastText = 0x460;  // "Come back and deposit some after you save up a bunch!" 
        break;
  
        break; //catchall until I get this shit straight
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
        this->lastText = 0x462; // Hmm... Link is it?
        return;
    case 22: // Hmm.. Link is it?
        func_801518B0(globalCtx, 0x463, &this->actor);
        this->lastText = 0x463; // Got it... I won't forget your deposits. Let me stamp you
        return;
    case 23: // Got it... I won't forget your deposits. Let me stamp you
        func_801518B0(globalCtx, 0x464, &this->actor);
        this->lastText = 0x464; // Hey, relax! It doesn't leave any marks
        return;
    case 24: // Hey, relax! It doesn't leave any marks
        //globalCtx->msgCtx.pad11F23 = 0x44;
        globalCtx->msgCtx.pad11F23[0] = 0x44;
        func_80A65800(this); // stamp player
        return;
    case 25: // "There! Now I'll know you when I see you!"
        globalCtx = globalCtx;
        func_800BDC5C(&this->skelAnime, (void *) D_80A65D60, 0);
        globalCtx->msgCtx.unk1207C = gSaveContext.perm.unkEDC & 0xFFFF;
        func_801518B0(globalCtx, 0x45A, &this->actor);
        this->lastText = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        return;
    case 26:
    case 27:
        func_801518B0(globalCtx, 0x468, &this->actor);
        this->lastText = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
        return;
    case 29:
        func_80A65800(this); // stamp player
        return;
    case 30:
    case 32:
    case 50:
        if (this->unk25C == 0) {
            if ((u32) (gSaveContext.perm.unkEDC & 0xFFFF) >= 0x1388) {
                func_801518B0(globalCtx, 0x45F, &this->actor);
                this->lastText = 0x45F; // "Excuuuse me! But I can't take anymore deposits!
            } else if (gSaveContext.perm.unk24.unk16 == 0) {
                func_801518B0(globalCtx, 0x458, &this->actor);
                this->lastText = 0x458; // "Hmm...You play mean jokes, little guy! You haven't even got a single Rupee!  
            } else {
                func_801518B0(globalCtx, 0x479, &this->actor);
                this->lastText = 0x479; // "Well, are you gonna make a deposit?"
            }
        } else if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
            func_801518B0(globalCtx, 0x46D, &this->actor);
            // "Look, little guy, if it's 'cause of the bad rumors going around, forget it! They're just rumors!"
            this->lastText = 0x46D;
        } else {
            func_801518B0(globalCtx, 0x46B, &this->actor);
            this->lastText = 0x46B; // "So..."
        }
        this->unk25C = 0;
        return;
    case 31:
        func_801518B0(globalCtx, 0x46E, &this->actor);
        this->lastText = 0x46E; // "How much do you want?  [rupee prompt]
        return;
    case 33:
        func_801518B0(globalCtx, 0x46B, &this->actor);
        this->lastText = 0x46B; // So...
        return;
    case 36:
        if (func_80147624(globalCtx) == 0) {
            return;
        }
        func_801477B4(globalCtx);
        this->unk260 = 0;
        func_80A64554(this);
        return;
    case 42:
        func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
    case 41:
    case 48:
    case 49:
        func_801518B0(globalCtx, 0x468, &this->actor);
        this->lastText = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
        return;
    case 38:
    case 39:
    case 40:
        if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) {
            func_801518B0(globalCtx, 0x478, &this->actor);
            //  "Look, little guy, all the Rupees you deposited are gone, so you can't use that stamp anymore."
            this->lastText = 0x478;
        } else {
            globalCtx->msgCtx.unk1207C = gSaveContext.perm.unkEDC & 0xFFFF;
            func_801518B0(globalCtx, 0x45A, &this->actor);
            this->lastText = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
        }
        break;
    case 43:
        func_801518B0(globalCtx, 0x471, &this->actor);
        this->lastText = 0x471; // "Are you really withdrawing [rupees selected]? Y/n"
        this->unk25A = globalCtx->msgCtx.unk1206C;
        return;
    case 45:
        func_801518B0(globalCtx, 0x44F, &this->actor);
        this->lastText = 0x44F; // "All right! So..."
        return;
    default:
        break;
    } // end switch

} // */
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A646F4.asm")

// actionfunc: accept dialogue input
//working
// NON-MATCHING: lots of regalloc 
// ROM SHIFT a couple redundant li 0x4806 added
#if NON_MATCHING
void func_80A64DC4(EnGinkoMan *this, GlobalContext *globalCtx) {

    // branch likely instead of branch, fixed by adding a fake if though
    if (func_80147624(globalCtx) == 0) {
      return;
    }

    switch (this->lastText) {

    case 0x44E: // "...So, what'll it be?
        if (globalCtx->msgCtx.unk12022 == 0) {
            if ( (gSaveContext.perm.unkEDC & 0xFFFF) >= 0x1388) {
                play_sound(0x4806);// NA_SE_SY_ERROR
                func_801518B0(globalCtx, 0x45F, &this->actor);
                this->lastText = 0x45F; // bank full, cannot accept more
                return;
            }
            else {
                if (gSaveContext.perm.unk24.unk16 > 0) {
                    func_8019F208(0x4806);
                    func_801518B0(globalCtx, 0x44F, &this->actor);
                    this->lastText = 0x44F; // All right! so...
                } else {
                    play_sound(0x4806); // NA_SE_SY_ERROR
                    func_801518B0(globalCtx, 0x458, &this->actor);
                    this->lastText = 0x458; // you haven't even gotten a single rup
                }
                return;
            } 
        }
        func_8019F230();
        func_801518B0(globalCtx, 0x451, &this->actor);
        this->lastText = 0x451; // dont say that, come on, trust me!
        break;

    case 0x452: // Really? are you really depositing rupees?

        if (globalCtx->msgCtx.unk12022 == 0){ // Selected: YES
            if (gSaveContext.perm.unk24.unk16 < globalCtx->msgCtx.unk12078) {
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x459, &this->actor);
                this->lastText = 0x459; // HEY you dont have that much
                //return;
            } else {
                func_8019F208(0x4806);// NA_SE_SY_ERROR
                ////temp_v0_5 = globalCtx->msgCtx.unk12078;
                if (globalCtx->msgCtx.unk12078 >= 100) {
                    func_801518B0(globalCtx, 0x455, &this->actor);
                    this->lastText = 0x455; // You're really going to be give me that much? Rich little guy!
                } else if (globalCtx->msgCtx.unk12078 >= 10) {
                    func_801518B0(globalCtx, 0x454, &this->actor);
                    this->lastText = 0x454; // Seriously? that's a lot. A lot!
                } else {
                    func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x453, &this->actor);
                    this->lastText = 0x453; // That's it? That aint nothing at all
                }
                if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) {
                    this->unk25E = 1;
                }
                func_801159EC((s16) -(s32) globalCtx->msgCtx.unk12078);
                this->unk262 =  gSaveContext.perm.unkEDC;

                gSaveContext.perm.unkEDC = ((gSaveContext.perm.unkEDC & 0xFFFF) 
                    + globalCtx->msgCtx.unk12078) | (gSaveContext.perm.unkEDC & 0xFFFF0000);
            }
        }else{ // Selected: NO
            func_8019F230();
            func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
            // different forms?
            if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) { // @B74
                func_801518B0(globalCtx, 0x456, &this->actor);
                this->lastText = 0x456; // Is that so? think about it 
            } else {
                func_801518B0(globalCtx, 0x47D, &this->actor);
                this->lastText = 0x47D; // is that so? think it over
            }
        }
        break;

    case 0x468:  // [Deposit rupees selected] // location: @C38
        // FAKE MATCH
        if (globalCtx->msgCtx.unk12022) {} // -5000 permuter score: regalloc and branch likely swapping

        if (globalCtx->msgCtx.unk12022 == 2) {
            func_8019F230();
            func_801518B0(globalCtx, 0x470, &this->actor);
            this->lastText = 0x470; // "Is that so? Come back and deposit some after saving up a bunch!"
        } else {
            func_8019F208();
            this->unk25C = globalCtx->msgCtx.unk12022;
            if (this->unk260 == 0) {                          // @C94
                this->unk260 = 1;
                func_801518B0(globalCtx, 0x469, &this->actor);
                this->lastText = 0x469; // Excuse me, but let me look at you
            } else {
                func_801518B0(globalCtx, 0x47E, &this->actor);
                this->lastText = 0x47E; // your deposits total X rupees
            }
        }
        break;

    case 0x471: // Are you really withdrawling [selected rupees]? // @CDC
        if (globalCtx->msgCtx.unk12022 == 0) {
            // s32 casts required for slt instead of sltu
            if ((s32)((gSaveContext.perm.unkEDC & 0xFFFF)) < ((s32)( globalCtx->msgCtx.unk12078 + this->unk25A))) { 
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->skelAnime, D_80A65D60, 0);       // @ D30
                func_801518B0(globalCtx, 0x476, &this->actor);
                this->lastText = 0x476; // you dont have enough deposited to withdrawl
                return;
            }
            
            // an array of what though
            //if ((s32) *(&D_801C1E2C + (((u32) ((s32) gSaveContext.perm.inv.unk48 & D_801C1DD0) >> D_801C1E08) * 2))
               //< (globalCtx->msgCtx.unk12078 + gSaveContext.perm.unk24.unk16)) {
            if ( (D_801C1E2C[ ( gSaveContext.perm.inv.unk48 & D_801C1DD0) >> D_801C1E08])
               < (globalCtx->msgCtx.unk12078 + gSaveContext.perm.unk24.unk16)) {
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_801518B0(globalCtx, 0x475, &this->actor);
                this->lastText = 0x475; // You can't hold that many in your wallet
                return;
            }
            func_8019F208(0x4806);

            //temp_v0_3 = globalCtx->msgCtx.unk12078;
            if (globalCtx->msgCtx.unk12078 >= 100) {
                func_801518B0(globalCtx, 0x474, &this->actor);
                this->lastText = 0x474; // Aw, you're taking out all that?
            } else if (globalCtx->msgCtx.unk12078 >= 10) {
                func_801518B0(globalCtx, 0x473, &this->actor);
                this->lastText = 0x473; // use it wisely
            } else {
                func_801518B0(globalCtx, 0x472, &this->actor);
                this->lastText = 0x472; // It's a waste to take out such a tiny bit
            }
            this->unk262 = (s16) gSaveContext.perm.unkEDC;
            //temp_v0_4 = gSaveContext.perm.unkEDC;
            gSaveContext.perm.unkEDC = (((gSaveContext.perm.unkEDC & 0xFFFF) - globalCtx->msgCtx.unk12078) 
              - this->unk25A) | (gSaveContext.perm.unkEDC & 0xFFFF0000);
            func_801159EC( (s16) globalCtx->msgCtx.unk12078, &gSaveContext); // cast req
            return;
        } else { 
            //func_8019F230(&gSaveContext);
            func_8019F230();
            func_801518B0(globalCtx, 0x47C, &this->actor);
            this->lastText = 0x47C; // "Is that so? Think it over, little guy! So what are you gonna do?"
        }
    } // end switch
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A64DC4.asm")
#endif

void func_80A65364(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->lastText){
            case 0x450: // "How much? How much?" [rupee prompt] Set the amount with [Control Stick] and
                if (globalCtx->msgCtx.unk12078 == 0) {
                    globalCtx = globalCtx;
                    func_800BDC5C(&this->skelAnime, &D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x457, &this->actor);
                    this->lastText = 0x457; // Zero Rupees? Cruel joke!
                } else {
                    func_801518B0(globalCtx, 0x452, &this->actor);
                    this->lastText = 0x452; // Really? are you really depositing [x]? Y/n
                }
                break;

            case 0x46E: // "How much do you want?"  [rupee prompt] Set the amount with [Control Stick]
                if (globalCtx->msgCtx.unk12078 == 0) {
                    func_801518B0(globalCtx, 0x46F, &this->actor);
                    this->lastText = 0x46F; // "Zero Rupees?!?  That's a cruel joke!"
                } else if (gSaveContext.perm.isNight == 1) {
                    func_801518B0(globalCtx, 0x477, &this->actor);
                    this->lastText = 0x477; // "...You know, at this time of day there's a 4 Rupee service charge...
                } else {
                    func_801518B0(globalCtx, 0x471, &this->actor);
                    this->lastText = 0x471; // "Are you really withdrawing [rupees selected]? Y/n
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
            func_80A64554(this);
            break;
        case 4:
            func_80A64DC4(this, globalCtx);
            break;
        case 5:
            func_80A646F4(this, globalCtx);
            break;
        case 6:
            if (func_80147624(globalCtx) != 0) {
                this->unk260 = 0;
                func_80A64554(this);
                break;
            case 14:
                func_80A65364(this, globalCtx);
            }
        default:
        case 0:
        //block_8:
        break;
    }

    if ((this->skelAnime.animCurrentSeg == &D_060008C0) 
      && (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0)) {
        Audio_PlayActorSound2(this, 0x2992); // NA_SE_EV_BANK_MAN_HAND_HIT
    }
}

void func_80A6557C(EnGinkoMan* this) {
    this->actionFunc =  func_80A65590;
}

// savecontext shinanigans
// action func: give wallet checks
// NON_EQUIVELENET nowhere close
/*
void func_80A65590(EnGinkoMan *this, GlobalContext *globalCtx) {
    SaveContext* sCtx = &gSaveContext;

    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        this->actor.parent = NULL;
        func_80A656C4(this);
    } else if (this->lastText == 0x45B) { // "Whats this, you already saved up 200?"
        if ((sCtx->perm.weekEventReg[0xA] & 8) != 0) {
        //if ((gSaveContext.perm.weekEventReg[0xA] & 8) != 0) {
            func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
        } else {
            // hang on, pad48 is an array, are we looking for one value?
            //func_800B8A1C(&this->actor, globalCtx,
                 //((u32) ((s32) gSaveContext.perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) + 8, 500.0f, 100.0f);
            func_800B8A1C(&this->actor, globalCtx,
                 ((u32) ((s32) sCtx->perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) + 8, 500.0f, 100.0f);
        }
    } else if (this->lastText == 0x45C) { // "Whats this, you already saved up 5000?"
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    } else if ((sCtx->perm.weekEventReg[0x3B] & 8) == 0) {
    //} else if ((gSaveContext.perm.weekEventReg[0x3B] & 8) == 0) {
        func_800B8A1C(&this->actor, globalCtx, 12, 500.0f, 100.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 2, 500.0f, 100.0f);
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A65590.asm")

//setup
void func_80A656C4(EnGinkoMan* this) {
    this->actionFunc =  func_80A656D8;
}

# if NON_MATCHING
// NON_MATCHING: minor regalloc at globalCtx into func_80152498
void func_80A656D8(EnGinkoMan* this, GlobalContext *globalCtx) {
    GlobalContext* gCtx;// = globalCtx;

    if (func_800B84D0(&this->actor, globalCtx)) {
        //if (((tempSCTXunkF02 & 8) == 0) && (this->lastText == 0x45B)) {
        if (((gSaveContext.perm.weekEventReg[0xA] & 8) == 0) && (this->lastText == 0x45B)) {
            // "What's this? You've already saved up 200 Rupees!?!  Well, little guy, here's your special gift. Take it!"
            gSaveContext.perm.weekEventReg[0xA] |= 8;
            func_801518B0(globalCtx, 0x47A, &this->actor);
            if (1) { // might be fake, but it solves almost everything
                 // "See! Doesn't it hold more than your old one? Fill it up and bring it all in to deposit!"
                this->lastText = 0x47A;
            }
        } else {
            func_800BDC5C(&this->skelAnime, &D_80A65D60, 1);
            func_801518B0(globalCtx, 0x47B, &this->actor);
            this->lastText = 0x47B; // "Is that so?  Think it over, little guy!  So what are you gonna do?"
        }
        func_80A65490(this);
    } else if (this->lastText == 0x45D) { // saved up 5000 rupees for HP
        //if ((func_80152498(&globalCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
        gCtx = globalCtx;
        if ((func_80152498(&gCtx->msgCtx, globalCtx) == 6) && (func_80147624(globalCtx) != 0)) {
            if ((gSaveContext.perm.weekEventReg[0x3B] & 8) == 0) {
                gSaveContext.perm.weekEventReg[0x3B] |= 8;
            }
            func_80A64554(this);
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
      
    if ((this->lastText == 0x464) // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
    && (func_801378B8(&this->skelAnime, 10.0f))) {
        Audio_PlayActorSound2(this, 0x2993); // NA_SE_EV_HANKO "stamp"
    }

    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        switch(this->lastText){
            case 0x464: // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x465, &this->actor);
                this->lastText = 0x465; // "There! Now I'll know you when I see you!"
                break;

            case 0x469: // "Excuse me, but let me take a look at you..."
                func_800BDC5C(&this->skelAnime, D_80A65D60, 1);
                globalCtx->msgCtx.unk1207C = (gSaveContext.perm.unkEDC & 0xFFFF); 
                // perm.day case req for div vs divu
                if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                    func_801518B0(globalCtx, 0x46C, &this->actor);
                    this->lastText = 0x46C; // "Ah, yes...[Link], right?
                } else {
                    func_801518B0(globalCtx, 0x46A, &this->actor);
                    this->lastText = 0x46A; // "Ah, yes...[Link].
                }
                break;
        }

        func_80A65490(this);
    }
}

// called from another action function
void func_80A65988(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (this->actor.xzDistToPlayer > 160.0f) {
        if (this->unk264 == 0) {
            if (this->skelAnime.animCurrentSeg != &D_06004A7C) {
                this->unk264 = 0x28;
                func_800BDC5C(&this->skelAnime, &D_80A65D60, 4);
            }
        }
    } else if ((this->unk264 == 0) && (this->skelAnime.animCurrentSeg != &D_06000AC4)) {
        this->unk264 = 0x28;
        func_800BDC5C(&this->skelAnime, &D_80A65D60, 3);
    }

    if (this->unk264 != 0) {
        this->unk264--;
    }
}

// update extension
//think this function adjusts his animation so that he faces the player while talking
void func_80A65A5C(EnGinkoMan *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->skelAnime.animCurrentSeg != &D_06004A7C) {
        func_800E9250(globalCtx, &this->actor, &this->unk24C, &this->unk252,
           this->actor.focus.pos);
    } else {
        func_800E8F08(&this->unk24C, &this->unk252);
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
        SysMatrix_InsertXRotation_s(this->unk24C.y, 1);
        SysMatrix_InsertZRotation_s(this->unk24C.x, 1);
        SysMatrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, 1);
    } else if (limbIndex == 8) {
        SysMatrix_InsertXRotation_s(-this->unk252.y, 1);
        SysMatrix_InsertZRotation_s(-this->unk252.x, 1);
    }
    return 0;
}

// post limbdraw
void func_80A65C18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {}

// putting this here now, haven't worked on it yet
/*
void EnGinkoMan_Draw(EnGinkoMan *this, GlobalContext *globalCtx) {
    Gfx *sp38;
    Gfx *sp34;
    Gfx *this->lastText;
    Gfx *temp_v0_2;
    Gfx *temp_v0_3;
    GraphicsContext *gcCtx;
    GraphicsContext *temp_s0;

    gcCtx = globalCtx->state.gfxCtx;
    temp_s0 = gcCtx;
    func_8012C28C(gcCtx);
    this->lastText = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = this->lastText + 8;
    this->lastText->words.w0 = 0xDB060020;
    sp38 = this->lastText;
    sp38->words.w1 = Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0);
    temp_v0_2 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_2 + 8;
    temp_v0_2->words.w0 = 0xDB060024;
    sp34 = temp_v0_2;
    sp34->words.w1 = Gfx_EnvColor(globalCtx->state.gfxCtx, 0x32, 0x50, 0, 0);
    temp_v0_3 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_3 + 8;
    temp_v0_3->words.w1 = 0;
    temp_v0_3->words.w0 = 0xE7000000;
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, &func_80A65B44, &func_80A65C18, this);
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Draw.asm")

