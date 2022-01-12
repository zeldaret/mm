/*
 * File: z_en_osn.c
 * Overlay: ovl_En_Osn
 * Description: Happy Mask Salesman
 */

#include "z_en_osn.h"

#define FLAGS 0x00000019

#define THIS ((EnOsn*)thisx)

void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Osn_InitVars = {
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

ActorAnimationEntry sAnimations[0x19] = {
    { (AnimationHeader*)0x060201BC, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06002F74, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x060037C4, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06004320, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06004C8C, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x060094E4, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06009BB8, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x0600AC60, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06001614, 1.0f, 1.0f, 39.0f, 0, 0.0f },
    { (AnimationHeader*)0x06001034, 1.0f, 1.0f, 70.0f, 0, 0.0f },
    { (AnimationHeader*)0x0600AE9C, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06003A1C, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x060055F8, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06007220, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x0600A444, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x060000C4, 0.0f, 0.0f, 0.0f, 2, 0.0f },
    { (AnimationHeader*)0x060000C4, 0.0f, 1.0f, 1.0f, 2, 0.0f },
    { (AnimationHeader*)0x06006D48, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06001D6C, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { (AnimationHeader*)0x06002634, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06008D80, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { (AnimationHeader*)0x06005D78, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { (AnimationHeader*)0x06006564, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x0600A444, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { (AnimationHeader*)0x06008D80, 0.0f, 77.0f, 0.0f, 2, 0.0f },
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

Vec3f D_80AD2574 = { 0.0f, 0.0f, 0.0f };
Vec3s D_80AD2580 = { 0x9920, -0x384, -0x320 };

void* D_80AD2588 = (void*)0x060166F8;
void* D_80AD258C = (void*)0x06016EF8;
void* D_80AD2590 = (void*)0x060176F8;
void* D_80AD2594 = (void*)0x06017EF8;
void* D_80AD2598 = (void*)0x060182F8;

extern UNK_TYPE D_060192A0;
extern UNK_TYPE D_060201BC;
extern FlexSkeletonHeader D_060202F0;

void func_80AD1634(EnOsn*, GlobalContext*);                /* extern */
void func_80AD16A8(EnOsn*, GlobalContext*);                /* extern */
void func_80AD14C8(EnOsn*, GlobalContext*);                /* extern */
void func_80AD19A0(EnOsn* this, GlobalContext* globalCtx); /* extern */

void func_80AD0830(EnOsn* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80AD08B0(GlobalContext* globalCtx) {
    switch (Player_GetMask(globalCtx)) {
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
    s16 sp1E;
    s16 new_var;

    sp1E = this->anime.curFrame;
    new_var = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);
    if (this->unk_1EC == 0x12 && sp1E == new_var) {
        this->unk_1EC = 0x13;
        Actor_ChangeAnimation(&this->anime, sAnimations, 0x13);
    }
}

void func_80AD0A24(EnOsn* this) {
    s16 sp1E;
    s16 new_var;

    sp1E = this->anime.curFrame;
    new_var = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);
    if (this->unk_1EC == 0x15 && sp1E == new_var) {
        this->unk_1EC = 0x16;
        Actor_ChangeAnimation(&this->anime, sAnimations, 0x16);
    }
}

void func_80AD0AB0(EnOsn* this) {
    s16 sp1E;
    s16 new_var;

    sp1E = this->anime.curFrame;
    new_var = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);
    if (sp1E == new_var) {
        this->unk_1FC -= 8;
        if (this->unk_1FC < 8) {
            this->unk_1FC = 0;
            Actor_MarkForDeath(&this->actor);
        }
    }
}

s32 func_80AD0B38(EnOsn* this, GlobalContext* globalCtx) {
    switch (Player_GetMask(globalCtx)) {
        case 11:
            if ((this->unk_1F8 & 1) == 0) {
                this->unk_1F8 |= 1;
                return 0x1FD1U;
            }
            break;
        case 12:
            if ((this->unk_1F8 & 2) == 0) {
                this->unk_1F8 |= 2;
                return 0x1FD1U;
            }
            break;
        case 1:
            if ((this->unk_1F8 & 4) == 0) {
                this->unk_1F8 |= 4;
                return 0x1FD1U;
            }
            break;
        case 20:
            if ((this->unk_1F8 & 8) == 0) {
                this->unk_1F8 |= 8;
                return 0x1FD1U;
            }
            break;
        case 2:
            if ((this->unk_1F8 & 0x10) == 0) {
                this->unk_1F8 |= 0x10;
                return 0x1FD1U;
            }
            break;
        case 13:
            if ((this->unk_1F8 & 0x20) == 0) {
                this->unk_1F8 |= 0x20;
                return 0x1FD1U;
            }
            break;
        case 18:
            if ((this->unk_1F8 & 0x40) == 0) {
                this->unk_1F8 |= 0x40;
                return 0x1FD1U;
            }
            break;
        case 10:
            if ((this->unk_1F8 & 0x80) == 0) {
                this->unk_1F8 |= 0x80;
                return 0x1FD1U;
            }
            break;
        case 19:
            if ((this->unk_1F8 & 0x100) == 0) {
                this->unk_1F8 |= 0x100;
                return 0x1FD1U;
            }
            break;
        case 14:
            if ((this->unk_1F8 & 0x200) == 0) {
                this->unk_1F8 |= 0x200;
                return 0x1FD1U;
            }
            break;
        case 16:
            if ((this->unk_1F8 & 0x400) == 0) {
                this->unk_1F8 |= 0x400;
                return 0x1FD1U;
            }
            break;
        case 9:
            if ((this->unk_1F8 & 0x800) == 0) {
                this->unk_1F8 |= 0x800;
                return 0x1FD2U;
            }
            break;
        case 4:
            if ((this->unk_1F8 & 0x1000) == 0) {
                this->unk_1F8 |= 0x1000;
                return 0x1FD2U;
            }
            break;
        case 15:
            if ((this->unk_1F8 & 0x2000) == 0) {
                this->unk_1F8 |= 0x2000;
                return 0x1FD1U;
            }
            break;
        case 17:
            if ((this->unk_1F8 & 0x4000) == 0) {
                this->unk_1F8 |= 0x4000;
                return 0x1FD1U;
            }
            break;
        case 8:
            if ((this->unk_1F8 & 0x8000) == 0) {
                this->unk_1F8 |= 0x8000;
                return 0x1FD1U;
            }
            break;
        case 5:
            if ((this->unk_1F8 & 0x10000) == 0) {
                this->unk_1F8 |= 0x10000;
                return 0x1FD1U;
            }
            break;
        case 6:
            if ((this->unk_1F8 & 0x20000) == 0) {
                this->unk_1F8 |= 0x20000;
                return 0x1FD1U;
            }
            break;
        case 3:
            if ((this->unk_1F8 & 0x40000) == 0) {
                this->unk_1F8 |= 0x40000;
                return 0x1FD1U;
            }
            break;
        case 7:
            if ((this->unk_1F8 & 0x80000) == 0) {
                this->unk_1F8 |= 0x80000;
                return 0x1FD1U;
            }
            break;
        default:
            break;
    }
    this->unk_1EA |= 0x20;
    if (gSaveContext.day == 3 && gSaveContext.time >= CLOCK_TIME(5, 0) && gSaveContext.time < CLOCK_TIME(6, 0)) {
        return 0x2006U;
    }
    return 0x1FCDU;
}

s32 func_80AD0E10(EnOsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((gSaveContext.inventory.items[SLOT_OCARINA] != ITEM_NONE) && CHECK_QUEST_ITEM(QUEST_SONG_HEALING)) {
        if (this->unk_1EA & 1) {
            this->unk_1EA |= 0x20;
            if ((gSaveContext.inventory.items[SLOT_OCARINA] != ITEM_NONE) &&
                (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU)) {
                if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            return 0x1FAF;
        }

        if (player->transformation == PLAYER_FORM_DEKU) {
            if (this->unk_1EA & 4) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.time < CLOCK_TIME(6, 0))) {
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
                if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 8;
            if (gSaveContext.weekEventReg[0x4C] & 0x20) {
                return 0x1FC8;
            }

            gSaveContext.weekEventReg[0x4C] |= 0x20;
            return 0x1FCE;
        }

        if (player->transformation == PLAYER_FORM_ZORA) {
            if (this->unk_1EA & 0x10) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 0x10;
            if (gSaveContext.weekEventReg[0x4C] & 0x40) {
                return 0x1FC8;
            }
            gSaveContext.weekEventReg[0x4C] |= 0x40;
            return 0x1FD0;
        }

        if (Player_GetMask(globalCtx) == PLAYER_MASK_NONE) {
            if (this->unk_1EA & 2) {
                this->unk_1EA |= 0x20;
                if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                    (gSaveContext.time < CLOCK_TIME(6, 0))) {
                    return 0x2006;
                }
                return 0x1FCD;
            }
            this->unk_1EA |= 2;
            return 0x1FC8;
        }

        return func_80AD0B38(this, globalCtx);
    }

    this->unk_1EA |= 0x20;
    if ((gSaveContext.day == 3) && (gSaveContext.time >= CLOCK_TIME(5, 0)) && (gSaveContext.time < CLOCK_TIME(6, 0))) {
        return 0x2004;
    }

    return 0x1FAE;
}

void func_80AD10FC(EnOsn* this, GlobalContext* globalCtx) {
    switch (this->unk_1F4) {
        case 0x1FC8:
            this->unk_1F4 = 0x1FC9U;
            break;

        case 0x1FC9:
            this->unk_1F4 = 0x1FCAU;
            break;

        case 0x1FCA:
            if ((gSaveContext.day == 3 && gSaveContext.time >= CLOCK_TIME(5, 0)) &&
                gSaveContext.time < CLOCK_TIME(6, 0)) {
                this->unk_1F4 = 0x2007U;
            } else {
                this->unk_1F4 = 0x1FCBU;
            }
            break;

        case 0x1FCB:

        case 0x2007:
            this->unk_1F4 = 0x1FCCU;
            this->unk_1EA |= 0x20;
            break;

        case 0x1FCE:

        case 0x1FD0:
            this->unk_1F4 = 0x1FCFU;
            break;

        case 0x1FCF:
            this->unk_1F4 = 0x1FCAU;
            break;

        case 0x1FD1:

        case 0x1FD2:
            this->unk_1F4 = func_80AD08B0(globalCtx);
            break;

        case 0x1FD6:
            this->unk_1F4 = 0x1FD7U;
            break;

        case 0x1FD8:
            this->unk_1F4 = 0x1FD9U;
            break;

        case 0x1FDA:
            this->unk_1F4 = 0x1FDBU;
            break;

        case 0x1FDC:
            this->unk_1F4 = 0x1FDDU;
            break;

        case 0x1FDE:
            this->unk_1F4 = 0x1FDFU;
            break;

        case 0x1FE0:
            this->unk_1F4 = 0x1FE1U;
            break;

        case 0x1FE2:
            this->unk_1F4 = 0x1FE3U;
            break;

        case 0x1FE4:
            this->unk_1F4 = 0x1FE5U;
            break;

        case 0x1FE6:
            this->unk_1F4 = 0x1FE7U;
            break;

        case 0x1FE8:
            this->unk_1F4 = 0x1FE9U;
            break;

        case 0x1FEA:
            this->unk_1F4 = 0x1FEBU;
            break;

        case 0x1FEC:
            this->unk_1F4 = 0x1FEDU;
            break;

        case 0x1FEE:
            this->unk_1F4 = 0x1FEFU;
            break;

        case 0x1FF0:
            this->unk_1F4 = 0x1FF1U;
            break;

        case 0x1FF2:
            this->unk_1F4 = 0x1FF3U;
            break;

        case 0x1FF4:
            this->unk_1F4 = 0x1FF5U;
            break;

        case 0x1FF6:
            this->unk_1F4 = 0x1FF7U;
            break;

        case 0x1FF8:
            this->unk_1F4 = 0x1FF9U;
            break;

        case 0x1FFA:
            this->unk_1F4 = 0x1FFBU;
            break;

        case 0x1FFC:
            this->unk_1F4 = 0x1FFDU;
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
            this->unk_1F4 = 0x1FD3U;
            break;

        case 0x1FD9:

        case 0x1FE3:

        case 0x1FE9:

        case 0x1FEB:

        case 0x1FED:

        case 0x1FEF:

        case 0x1FF5:

        case 0x1FFD:
            this->unk_1F4 = 0x1FD4U;
            break;

        case 0x1FE5:
            this->unk_1F4 = 0x1FFEU;
            break;

        case 0x1FD3:

        case 0x1FD4:

        case 0x1FFE:
            this->unk_1F4 = 0x1FD5U;
            this->unk_1EA |= 0x20;
    }

    func_801518B0(globalCtx, this->unk_1F4, &this->actor);
}

void func_80AD1398(EnOsn* this) {
    this->cutscene = this->actor.cutscene;
    if (((gSaveContext.inventory.items[SLOT_OCARINA] == ITEM_NONE) ||
         (gSaveContext.inventory.items[gItemSlots[0x32]] == 0x32)) &&
        ((this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene),
          (gSaveContext.inventory.items[SLOT_OCARINA] != ITEM_NONE)) ||
         (gSaveContext.inventory.items[gItemSlots[0x32]] == 0x32))) {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
    }
}

void func_80AD144C(EnOsn* this, GlobalContext* globalCtx) {
    u32 sp1C;

    sp1C = Flags_GetSwitch(globalCtx, 0);
    this->cutscene = this->actor.cutscene;
    Actor_ChangeAnimation(&this->anime, sAnimations, 0);
    if (sp1C == 0) {
        this->actionFunc = func_80AD16A8;
    } else {
        this->actionFunc = func_80AD14C8;
    }
}

void func_80AD14C8(EnOsn* this, GlobalContext* globalCtx) {
    s16 temp_v1;
    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if ((gSaveContext.inventory.items[SLOT_OCARINA] != ITEM_NONE) &&
        (((*(gBitFlags + 0xD)) & gSaveContext.inventory.questItems) == 0)) {
        if (gSaveContext.inventory.questItems) {}
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->actionFunc = func_80AD1634;
            return;
        }
        if ((((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted != 0)) && (((s32)temp_v1) < 0x4000)) &&
            (temp_v1 >= -0x3FFF)) {
            func_800B863C(&this->actor, globalCtx);
            this->actor.textId = 0xFFFF;
        }
    } else {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->unk_1F4 = (s16)func_80AD0E10(this, globalCtx);
            func_801518B0(globalCtx, this->unk_1F4, &this->actor);
            this->actionFunc = func_80AD19A0;
        } else if ((((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted != 0)) && (temp_v1 < 0x4000)) &&
                   (temp_v1 >= -0x3FFF)) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
}

void func_80AD1634(EnOsn* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->actionFunc = func_80AD16A8;
        return;
    }
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    }
    ActorCutscene_SetIntentToPlay(this->cutscene);
}

void func_80AD16A8(EnOsn* this, GlobalContext* globalCtx) {
    u8 pad;
    u32 temp_v0;

    if (func_800EE29C(globalCtx, 0x82)) {
        temp_v0 = func_800EE200(globalCtx, 0x82);
        this->unk_1F0 = 0;
        if (this->unk_1ED != globalCtx->csCtx.npcActions[temp_v0]->unk0) {
            this->unk_1ED = globalCtx->csCtx.npcActions[temp_v0]->unk0;
            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
                case 1:
                    this->unk_1EC = 2;
                    break;
                case 2:
                    this->unk_1EC = 1;
                    break;
                case 3:
                    this->unk_1EC = 7;
                    break;
                case 4:
                    this->unk_1EC = 3;
                    break;
                case 5:
                    this->unk_1EC = 6;
                    break;
                case 6:
                    this->unk_1EC = 5;
                    break;
                case 7:
                    this->unk_1EC = 4;
                    break;
                case 8:
                    this->unk_1EC = 0;
                    break;
                case 10:
                    this->unk_1EC = 8;
                    break;
                case 11:
                    this->unk_1EC = 9;
                    break;
                case 13:
                    this->unk_1EC = 0xA;
                    break;
                case 15:
                    this->unk_1EC = 0xB;
                    break;
                case 16:
                    this->unk_1EC = 0xC;
                    break;
                case 17:
                    this->unk_1EC = 0xD;
                    break;
                case 18:
                    this->unk_1EC = 0xE;
                    break;
                case 19:
                    this->unk_1EC = 0x11;
                    break;
                case 20:
                    this->unk_1EC = 0x12;
                    break;
                case 21:
                    this->unk_1EC = 0x14;
                    break;
                case 22:
                    this->unk_1EC = 0x15;
                    break;
                case 23:
                    this->unk_1EC = 0x17;
                    break;
                case 24:
                    this->unk_1EC = 0x18;
                    break;
                default:
                    this->unk_1EC = 0;
                    break;
            }
            Actor_ChangeAnimation(&this->anime, sAnimations, this->unk_1EC);
        }

        if ((this->unk_1EC == 5) && (globalCtx->sceneNum == 8) && (gSaveContext.sceneSetupIndex == 0xB) &&
            (globalCtx->csCtx.frames == 0x190)) {
            Actor_PlaySfxAtPos(&this->actor, 0x697DU);
        }
        if (this->unk_1EC == 0x12) {
            func_80AD0998(this);
        }
        if (this->unk_1EC == 0x15) {
            func_80AD0A24(this);
        }
        if (this->unk_1EC == 0x18) {
            func_80AD0AB0(this);
        }
        if ((this->unk_1EC == 0x14) &&
            (((Animation_OnFrame(&this->anime, 17.0f))) || (Animation_OnFrame(&this->anime, 27.0f)) ||
             (Animation_OnFrame(&this->anime, 37.0f)) || (Animation_OnFrame(&this->anime, 47.0f)) ||
             (Animation_OnFrame(&this->anime, 57.0f)) || (Animation_OnFrame(&this->anime, 67.0f)))) {
            Actor_PlaySfxAtPos(&this->actor, 0x29B3U);
        }
        func_800EDF24(&this->actor, globalCtx, temp_v0);
        return;
    }
    this->unk_1F0 = 1;
    this->unk_1ED = 0x63;
    func_80AD144C(this, globalCtx);
}

void func_80AD19A0(EnOsn* this, GlobalContext* globalCtx) {
    u8 temp_v0;

    temp_v0 = Message_GetState(&globalCtx->msgCtx);
    if ((temp_v0 == 6 || temp_v0 == 5) && func_80147624(globalCtx)) {
        if (this->unk_1EA & 0x20) {
            this->unk_1EA &= 0xFFDF;
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->actionFunc = func_80AD14C8;
        } else {
            func_80AD10FC(this, globalCtx);
        }
    }
}

void EnOsn_Idle(EnOsn* this, GlobalContext* globalCtx) {
}

void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOsn* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->anime, &D_060202F0, (AnimationHeader*)(&D_060201BC), 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->unk_1FC = -1;
    switch (this->actor.params & 3) {
        case 0:
            if (((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC030)) ||
                (gSaveContext.entranceIndex == 0xC060)) {
                this->unk_1EA = (u16)(this->unk_1EA | 1);
            }
            this->unk_1F0 = 1;
            if (globalCtx->sceneNum == 0x63) {
                if ((gSaveContext.entranceIndex == 0xC020) || (gSaveContext.entranceIndex == 0xC060)) {
                    this->actionFunc = func_80AD16A8;
                    return;
                }
                if (gSaveContext.entranceIndex == 0xC030) {
                    func_80AD1398(this);
                    this->actionFunc = func_80AD1634;
                    return;
                }
                func_80AD144C(this, globalCtx);
                return;
            }
            func_80AD144C(this, globalCtx);
            return;

        case 1:
            this->unk_1EC = 0xF;
            Actor_ChangeAnimation(&this->anime, sAnimations, this->unk_1EC);
            this->actionFunc = EnOsn_Idle;
            return;

        case 2:
            this->unk_1EC = 0x10;
            Actor_ChangeAnimation(&this->anime, sAnimations, this->unk_1EC);
            this->actionFunc = EnOsn_Idle;
            return;

        case 3:
            this->actor.flags &= -2;
            this->actionFunc = func_80AD16A8;
            return;

        default:
            Actor_MarkForDeath(&this->actor);
            return;
    }
}

void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOsn* this = THIS;

    SkelAnime_Free(&this->anime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    u32 pad1;
    u16 pad2;
    u32 sp34;
    EnOsn* this = THIS;

    sp34 = Flags_GetSwitch(globalCtx, 0);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    SkelAnime_Update(&this->anime);
    if ((this->actor.params & 3) == 0) {
        if (sp34 != 0) {
            this->actor.flags |= 1;
            func_80AD0830(this, globalCtx);
            this->actor.draw = EnOsn_Draw;
        } else {
            this->actor.draw = 0;
            this->actor.flags &= -2;
        }
    }
    func_800E9250(globalCtx, &this->actor, (Vec3s*)this->unk_1D8, (Vec3s*)&this->unk_1D8[6], this->actor.focus.pos);
}

s32 func_80AD1DA8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor,
                  Gfx** gfx) {
    EnOsn* this = (EnOsn*)actor;

    if (this->unk_1F0 && limbIndex == 0xB) {
        Matrix_InsertXRotation_s(this->unk_1DA, 1);
    }
    if ((this->unk_1EC == 9 || this->unk_1EC == 8) && limbIndex == 0xA) {
        *dList = 0;
    }
    return 0;
}

void func_80AD1E28(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor, Gfx** gfx) {
    EnOsn* this = (EnOsn*)actor;
    Vec3f sp30 = D_80AD2574;
    Vec3s sp28 = D_80AD2580;

    if (limbIndex == 0xB) {
        Matrix_MultiplyVector3fByState(&sp30, &actor->focus.pos);
    }
    if (((this->unk_1EC == 0x11) || (this->unk_1EC == 0x15) || (this->unk_1EC == 0x16)) && (limbIndex == 6)) {
        Matrix_StatePush();
        Matrix_InsertTranslation(-400.0f, 1100.0f, -200.0f, 1);
        Matrix_InsertXRotation_s(sp28.x, 1);
        Matrix_RotateY(sp28.y, 1);
        Matrix_InsertZRotation_s(sp28.z, 1);

        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, &D_060192A0);
        Matrix_StatePop();
    }
}

s32 func_80AD1DA8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor,
                  Gfx** gfx);
void func_80AD1E28(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor, Gfx** gfx);

void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* temp_s0;
    EnOsn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_1FC == 0xFF) {
        func_8012C28C(globalCtx->state.gfxCtx);
        if ((this->unk_1EC == 0xB) || (this->unk_1EC == 0xC) || (this->unk_1EC == 0x17) ||
            (globalCtx->msgCtx.unk11F04 == 0x1FCA)) {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD258C));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD2594));
        } else if ((this->unk_1EC == 7) || (this->unk_1EC == 3) || (this->unk_1EC == 0xD)) {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD2590));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD2598));
        } else {
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD2588));
            gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD2594));
        }
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        POLY_OPA_DISP =
            SkelAnime_DrawFlex(globalCtx, this->anime.skeleton, this->anime.jointTable, this->anime.dListCount,
                               func_80AD1DA8, func_80AD1E28, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD2588));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD2594));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->unk_1FC);
        Scene_SetRenderModeXlu(globalCtx, 1, 2U);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->anime.skeleton, this->anime.jointTable, this->anime.dListCount,
                               func_80AD1DA8, func_80AD1E28, &this->actor, POLY_XLU_DISP);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
