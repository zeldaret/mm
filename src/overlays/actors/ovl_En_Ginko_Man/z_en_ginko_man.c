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

// looks like an array of structs
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
    SkelAnime_InitSV(globalCtx, &this->anime, &D_0600C240, &D_060043F0, &this->unk18C, &this->unk1EC, 0x10);
    func_80A64554(this);
}

void EnGinkoMan_Destroy(Actor *thisx, GlobalContext *globalCtx) { }

// init extension
void func_80A64554(EnGinkoMan* this) {

    this->actor.flags |= 1;
    func_800BDC5C(&this->anime, &D_80A65D60, 1);
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
            func_800BDC5C(&this->anime, D_80A65D60, 0);
            func_801518B0(globalCtx, 0x44CU, &this->actor);
            this->lastText = 0x44C; // would you like to make an account
        } else {
            func_800BDC5C(&this->anime, D_80A65D60, 1);
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

//jump tables
// fuck this one is even bigger damn it
/*
void func_80A646F4(EnGinkoMan *this, GlobalContext *globalCtx) {
    GlobalContext *temp_a0;
    GlobalContext *temp_a3;
    s16 temp_v0;
    s16 temp_v0_4;
    s32 temp_v1_2;
    u32 temp_t6;
    u32 temp_v1;
    u8 temp_t0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    GlobalContext *phi_a3;
    GlobalContext *phi_a3_2;
    s16 phi_t6;
    GlobalContext *phi_a3_3;

    temp_a0 = globalCtx;
    globalCtx = globalCtx;
    temp_a3 = globalCtx;
    if (func_80147624(globalCtx) != 0) {
        temp_v0 = this->lastText;
        temp_t6 = temp_v0 - 0x44C;
        
        //if (temp_t6 < 0x33U) {
            //phi_a3_3 = temp_a3;
            //goto **(&jtbl_D_80A65DE0 + (temp_t6 * 4));
        switch (this->lastText - 0x44C)
        case 0:
            globalCtx = temp_a3;
            func_800BDC5C(&this->anime, (void *) D_80A65D60, 1);
            if ((gSaveContext.unkF02 & 8) == 0) {
                func_801518B0(globalCtx, 0x44DU, (Actor *) this);
                this->lastText = 0x44D;
                return;
            case 1:
                func_801518B0(temp_a3, 0x44EU, (Actor *) this);
                this->lastText = 0x44E;
                return;
            case 3:
                globalCtx = temp_a3;
                func_800BDC5C(&this->anime, (void *) D_80A65D60, 0);
                func_801518B0(globalCtx, 0x450U, (Actor *) this);
                this->lastText = 0x450;
                return;
            case 7:
            case 8:
            case 9:
                if (this->unk25E != 1) {
                    phi_a3_2 = temp_a3;
                    if (temp_v0 == 0x453) {
                        globalCtx = temp_a3;
                        func_800BDC5C(&this->anime, (void *) D_80A65D60, 0);
                        phi_a3_2 = globalCtx;
                    }
                    phi_a3_2->msgCtx.unk1207C = gSaveContext.perm.unkEDC & 0xFFFF;
                    func_801518B0(phi_a3_2, 0x45AU, (Actor *) this);
                    this->lastText = 0x45A;
                    return;
                case 10:
                case 13:
                    func_801518B0(temp_a3, 0x44EU, (Actor *) this);
                    this->lastText = 0x44E;
                    return;
                case 14:
                    temp_v1 = gSaveContext.perm.unkEDC & 0xFFFF;
                    if (temp_v1 < 0xC8U) {
block_20:
                        if (temp_v1 < 0x3E8U) {
block_24:
                            if (temp_v1 < 0x1388U) {
                                globalCtx = temp_a3;
                                func_800BDC5C(&this->anime, (void *) D_80A65D60, 0);
                                func_801518B0(globalCtx, 0x460U, (Actor *) this);
                                this->lastText = 0x460;
                                return;
                            case 15:
                            case 16:
                            case 17:
                                this->unk260 = 0;
                                globalCtx = temp_a3;
                                func_801477B4(temp_a3);
                                func_80A6557C(this);
                                func_80A65590(this, globalCtx);
                                return;
                            case 21:
                                func_801518B0(temp_a3, 0x462U, (Actor *) this);
                                this->lastText = 0x462;
                                return;
                            case 22:
                                func_801518B0(temp_a3, 0x463U, (Actor *) this);
                                this->lastText = 0x463;
                                return;
                            case 23:
                                func_801518B0(temp_a3, 0x464U, (Actor *) this);
                                this->lastText = 0x464;
                                return;
                            case 24:
                                temp_a3->msgCtx.pad11F23 = 0x44;
                                func_80A65800(this);
                                return;
                            case 25:
                                globalCtx = temp_a3;
                                func_800BDC5C(&this->anime, (void *) D_80A65D60, 0);
                                globalCtx->msgCtx.unk1207C = gSaveContext.perm.unkEDC & 0xFFFF;
                                func_801518B0(globalCtx, 0x45AU, (Actor *) this);
                                this->lastText = 0x45A;
                                return;
                            case 26:
                            case 27:
                                func_801518B0(temp_a3, 0x468U, (Actor *) this);
                                this->lastText = 0x468;
                                return;
                            case 29:
                                func_80A65800(this);
                                return;
                            case 30:
                            case 32:
                            case 50:
                                if (this->unk25C == 0) {
                                    if ((u32) (gSaveContext.perm.unkEDC & 0xFFFF) >= 0x1388U) {
                                        func_801518B0(temp_a3, 0x45FU, (Actor *) this);
                                        phi_t6 = (u16)0x45F;
block_50:
                                        this->lastText = phi_t6;
                                    } else if (gSaveContext.perm.unk24.unk16 == 0) {
                                        func_801518B0(temp_a3, 0x458U, (Actor *) this);
                                        this->lastText = 0x458;
                                    } else {
                                        func_801518B0(temp_a3, 0x479U, (Actor *) this);
                                        this->lastText = 0x479;
                                    }
                                } else if ((((s32) gSaveContext.perm.day % 5) == 3) && (gSaveContext.perm.isNight == 1)) {
                                    func_801518B0(temp_a3, 0x46DU, (Actor *) this);
                                    this->lastText = 0x46D;
                                } else {
                                    func_801518B0(temp_a3, 0x46BU, (Actor *) this);
                                    phi_t6 = (u16)0x46B;
                                    goto block_50;
                                }
                                this->unk25C = 0;
                                return;
                            case 31:
                                func_801518B0(temp_a3, 0x46EU, (Actor *) this);
                                this->lastText = 0x46E;
                                return;
                            case 33:
                                func_801518B0(temp_a3, 0x46BU, (Actor *) this);
                                this->lastText = 0x46B;
                                return;
                            case 36:
                                globalCtx = temp_a3;
                                if (func_80147624(temp_a3) == 0) {
                                default:
                                    return;
                                }
                                func_801477B4(globalCtx);
                                this->unk260 = 0;
                                func_80A64554(this);
                                return;
                            case 42:
                                globalCtx = temp_a3;
                                func_800BDC5C(&this->anime, (void *) D_80A65D60, 1);
                                phi_a3_3 = globalCtx;
                            case 41:
                            case 48:
                            case 49:
                                func_801518B0(phi_a3_3, 0x468U, (Actor *) this);
                                this->lastText = 0x468;
                                return;
                            case 38:
                            case 39:
                            case 40:
                                temp_v1_2 = gSaveContext.perm.unkEDC & 0xFFFF;
                                if (temp_v1_2 != 0) {
                                    temp_a3->msgCtx.unk1207C = temp_v1_2;
                                    func_801518B0(temp_a3, 0x45AU, (Actor *) this);
                                    this->lastText = 0x45A;
                                    return;
                                case 43:
                                    globalCtx = temp_a3;
                                    func_801518B0(temp_a3, 0x471U, (Actor *) this);
                                    this->lastText = 0x471;
                                    this->unk25A = (s16) globalCtx->msgCtx.pad1206C;
                                    return;
                                case 45:
                                    func_801518B0(temp_a3, 0x44FU, (Actor *) this);
                                    this->lastText = 0x44F;
                                default:
                                    return;
                                }
                                func_801518B0(temp_a3, 0x478U, (Actor *) this);
                                this->lastText = 0x478;
                                return;
                                return;
                                return;
                            }
                            temp_v0_4 = this->unk262;
                            if ((s32) temp_v0_4 >= 0x1388) {
block_28:
                                if ((s32) temp_v0_4 >= (s32) (s16) temp_v1) {
                                    globalCtx = temp_a3;
                                    func_800BDC5C(&this->anime, (void *) D_80A65D60, 0);
                                    func_801518B0(globalCtx, 0x460U, (Actor *) this);
                                    this->lastText = 0x460;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                    return;
                                }
                                globalCtx = temp_a3;
                                func_800BDC5C(&this->anime, (void *) D_80A65D60, 1);
                                func_801518B0(globalCtx, 0x45EU, (Actor *) this);
                                this->lastText = 0x45E;
                                return;
                            }
                            temp_t0 = gSaveContext.unkF34;
                            if ((temp_t0 & 1) != 0) {
                                goto block_28;
                            }
                            gSaveContext.unkF34 = (u8) (temp_t0 | 1);
                            func_801518B0(temp_a3, 0x45DU, (Actor *) this);
                            this->lastText = 0x45D;
                            return;
                        }
                        if ((s32) this->unk262 >= 0x3E8) {
                            goto block_24;
                        }
                        temp_v0_3 = gSaveContext.unkF33;
                        if ((temp_v0_3 & 0x80) != 0) {
                            goto block_24;
                        }
                        gSaveContext.unkF33 = (u8) (temp_v0_3 | 0x80);
                        func_801518B0(temp_a3, 0x45CU, (Actor *) this);
                        this->lastText = 0x45C;
                        return;
                    }
                    if ((s32) this->unk262 >= 0xC8) {
                        goto block_20;
                    }
                    temp_v0_2 = gSaveContext.unkF33;
                    if ((temp_v0_2 & 0x40) != 0) {
                        goto block_20;
                    }
                    gSaveContext.unkF33 = (u8) (temp_v0_2 | 0x40);
                    func_801518B0(temp_a3, 0x45BU, (Actor *) this);
                    this->lastText = 0x45B;
                    return;
                }
                this->unk25E = 0;
                phi_a3 = temp_a3;
                if (temp_v0 != 0x453) {
                    globalCtx = temp_a3;
                    func_800BDC5C(&this->anime, (void *) D_80A65D60, 1);
                    phi_a3 = globalCtx;
                }
                func_801518B0(phi_a3, 0x461U, (Actor *) this);
                this->lastText = 0x461;
                return;
                return;
                return;
            }
            func_801518B0(globalCtx, 0x44EU, (Actor *) this);
            this->lastText = 0x44E;
            return;
            return;
            return;
            return;
        }
    }
default:
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A646F4.asm")

// huge dialogue tree?
//working
// nowhere close: because its in a switch, all the if/else's are swapped or worse, what a mess
//  adding a fake condition can cause certain trouble areas to fix themselves, but this can be placed in multiple loc
///*
void func_80A64DC4(EnGinkoMan *this, GlobalContext *globalCtx) {

    // branch likely instead of branch, fixed by adding a fake if though
    if (func_80147624(globalCtx) == 0) {
      return;
    }

    switch (this->lastText) {

    case 0x44E: //if (this->lastText == 0x44E) {
    // "...So, what'll it be?
        if (globalCtx->msgCtx.unk12022 == 0) {
            if ( (gSaveContext.perm.unkEDC & 0xFFFF) >= 0x1388) {
                play_sound(0x4806);// NA_SE_SY_ERROR
                func_801518B0(globalCtx, 0x45F, &this->actor);
                this->lastText = 0x45F; // EXCUSE ME I cannot take anymore
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

    case 0x452: //if (this->lastText == 0x452) { // Really? are you really depositing rupees?
        if (globalCtx->msgCtx.unk12022 == 0){ // Selected: YES

            if (gSaveContext.perm.unk24.unk16 < globalCtx->msgCtx.unk12078) {
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->anime, D_80A65D60, 1);
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
                    func_800BDC5C(&this->anime, D_80A65D60, 1);
                    func_801518B0(globalCtx, 0x453, &this->actor);
                    this->lastText = 0x453; // That's it? That aint nothing at all
                }
                if ((gSaveContext.perm.unkEDC & 0xFFFF) == 0) {
                    // FAKE MATCH
                    if (gSaveContext.perm.unkEDC) {} // -4000 permuter score mostly regalloc
                    this->unk25E = 1;
                }
                func_801159EC((s16) -(s32) globalCtx->msgCtx.unk12078);
                this->unk262 =  gSaveContext.perm.unkEDC;

                gSaveContext.perm.unkEDC = ((gSaveContext.perm.unkEDC & 0xFFFF) 
                    + globalCtx->msgCtx.unk12078) | (gSaveContext.perm.unkEDC & 0xFFFF0000);
            }
        }else{ // Selected: NO
            func_8019F230();
            func_800BDC5C(&this->anime, D_80A65D60, 1);
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

    case 0x468: //if (this->lastText != 0x468) { // location: @C38
      // [Deposit rupees selected]
      //working
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

    case 0x471: //if (this->lastText != 0x471) { //return; //} // @CDC
    // Are you really withdrawling [selected rupees]?
        if (globalCtx->msgCtx.unk12022 == 0) {
            // think thi sis sltu instead of slt
            if (((u32)(gSaveContext.perm.unkEDC & 0xFFFF)) < ((u32)( globalCtx->msgCtx.unk12078 + this->unk25A))) { 
                play_sound(0x4806); // NA_SE_SY_ERROR
                func_800BDC5C(&this->anime, D_80A65D60, 0);       // @ D30
                func_801518B0(globalCtx, 0x476, &this->actor);
                this->lastText = 0x476; // you dont have enough deposited to withdrawl
                return;
            }
            //if (!D_801C1E08){}
            
            // an array of what though
            //if ((s32) *(&D_801C1E2C + (((u32) ((s32) gSaveContext.perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) * 2))
               //< (globalCtx->msgCtx.unk12078 + gSaveContext.perm.unk24.unk16)) {
            if ((s32) *(&D_801C1E2C + (((u32) ((s32) gSaveContext.perm.inv.pad48 & D_801C1DD0) >> D_801C1E08) * 2))
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
                this->lastText = 0x474; // Aw, you're talking out all that?
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
} // */
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/func_80A64DC4.asm")

void func_80A65364(EnGinkoMan *this, GlobalContext *globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->lastText){
            case 0x450: // "How much? How much?" [rupee prompt] Set the amount with [Control Stick] and
                if (globalCtx->msgCtx.unk12078 == 0) {
                    globalCtx = globalCtx;
                    func_800BDC5C(&this->anime, &D_80A65D60, 1);
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

    if ((this->anime.animCurrentSeg == &D_060008C0) 
      && (func_801378B8(&this->anime, this->anime.animFrameCount) != 0)) {
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
            func_800BDC5C(&this->anime, &D_80A65D60, 1);
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

void func_80A65800(EnGinkoMan* this) {
    func_800BDC5C(&this->anime, D_80A65D60, 2);
    this->actionFunc =  func_80A65844;
}

// action func: stamping and stamp checking
void func_80A65844(EnGinkoMan *this, GlobalContext *globalCtx) {
      
    if ((this->lastText == 0x464) // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
    && (func_801378B8(&this->anime, 10.0f))) {
        Audio_PlayActorSound2(this, 0x2993); // NA_SE_EV_HANKO "stamp"
    }

    if (func_801378B8(&this->anime, this->anime.animFrameCount)) {
        switch(this->lastText){
            case 0x464: // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
                func_800BDC5C(&this->anime, D_80A65D60, 1);
                func_801518B0(globalCtx, 0x465, &this->actor);
                this->lastText = 0x465; // "There! Now I'll know you when I see you!"
                break;

            case 0x469: // "Excuse me, but let me take a look at you..."
                func_800BDC5C(&this->anime, D_80A65D60, 1);
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
            if (this->anime.animCurrentSeg != &D_06004A7C) {
                this->unk264 = 0x28;
                func_800BDC5C(&this->anime, &D_80A65D60, 4);
            }
        }
    } else if ((this->unk264 == 0) && (this->anime.animCurrentSeg != &D_06000AC4)) {
        this->unk264 = 0x28;
        func_800BDC5C(&this->anime, &D_80A65D60, 3);
    }

    if (this->unk264 != 0) {
        this->unk264--;
    }
}

// update extension
//think this function adjusts his animation so that he faces the player while talking
void func_80A65A5C(EnGinkoMan *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->anime);

    if (this->anime.animCurrentSeg != &D_06004A7C) {
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
    SkelAnime_DrawSV(globalCtx, this->anime.skeleton, this->anime.limbDrawTbl, (s32) this->anime.dListCount, &func_80A65B44, &func_80A65C18, this);
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Draw.asm")
