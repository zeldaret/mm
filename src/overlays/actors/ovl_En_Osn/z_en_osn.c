/*
 * File: z_en_osn.c
 * Overlay: ovl_En_Osn
 * Description: Happy Mask Salesman
 */

#include "z_en_osn.h"
#include "objects/object_osn/object_osn.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

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

static AnimationInfo sAnimations[] = {
    { &object_osn_Anim_0201BC, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_002F74, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_0037C4, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_004320, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_004C8C, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_0094E4, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_009BB8, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_00AC60, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_001614, 1.0f, 1.0f, 39.0f, 0, 0.0f }, { &object_osn_Anim_001034, 1.0f, 1.0f, 70.0f, 0, 0.0f },
    { &object_osn_Anim_00AE9C, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_003A1C, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_0055F8, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_007220, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_00A444, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_0000C4, 0.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_osn_Anim_0000C4, 0.0f, 1.0f, 1.0f, 2, 0.0f },  { &object_osn_Anim_006D48, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_001D6C, 1.0f, 0.0f, 0.0f, 2, 0.0f },  { &object_osn_Anim_002634, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_008D80, 1.0f, 0.0f, 0.0f, 2, 0.0f },  { &object_osn_Anim_005D78, 1.0f, 0.0f, 0.0f, 2, 0.0f },
    { &object_osn_Anim_006564, 1.0f, 0.0f, 0.0f, 0, 0.0f },  { &object_osn_Anim_00A444, 1.0f, 0.0f, 0.0f, 0, 0.0f },
    { &object_osn_Anim_008D80, 0.0f, 77.0f, 0.0f, 2, 0.0f },
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

void func_80AD1634(EnOsn*, GlobalContext*);
void func_80AD16A8(EnOsn*, GlobalContext*);
void func_80AD14C8(EnOsn*, GlobalContext*);
void func_80AD19A0(EnOsn* this, GlobalContext* globalCtx);

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
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);

    if (this->unk_1EC == 0x12 && curFrame == lastFrame) {
        this->unk_1EC = 0x13;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0x13);
    }
}

void func_80AD0A24(EnOsn* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);

    if (this->unk_1EC == 0x15 && curFrame == lastFrame) {
        this->unk_1EC = 0x16;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0x16);
    }
}

void func_80AD0AB0(EnOsn* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->unk_1EC].animation);

    if (curFrame == lastFrame) {
        this->unk_1FA -= 8;
        if (this->unk_1FA < 8) {
            this->unk_1FA = 0;
            Actor_MarkForDeath(&this->actor);
        }
    }
}

s32 func_80AD0B38(EnOsn* this, GlobalContext* globalCtx) {
    switch (Player_GetMask(globalCtx)) {
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
    if (gSaveContext.save.day == 3 && gSaveContext.save.time >= CLOCK_TIME(5, 0) &&
        gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        return 0x2006;
    }
    return 0x1FCD;
}

s32 func_80AD0E10(EnOsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

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

        if (Player_GetMask(globalCtx) == PLAYER_MASK_NONE) {
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

        return func_80AD0B38(this, globalCtx);
    }

    this->unk_1EA |= 0x20;
    if ((gSaveContext.save.day == 3) && (gSaveContext.save.time >= CLOCK_TIME(5, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
        return 0x2004;
    }

    return 0x1FAE;
}

void func_80AD10FC(EnOsn* this, GlobalContext* globalCtx) {
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
            this->unk_1F4 = func_80AD08B0(globalCtx);
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

    Message_StartTextbox(globalCtx, this->unk_1F4, &this->actor);
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

void func_80AD144C(EnOsn* this, GlobalContext* globalCtx) {
    u32 sp1C = Flags_GetSwitch(globalCtx, 0);
    this->cutscene = this->actor.cutscene;

    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    if (sp1C == 0) {
        this->actionFunc = func_80AD16A8;
    } else {
        this->actionFunc = func_80AD14C8;
    }
}

void func_80AD14C8(EnOsn* this, GlobalContext* globalCtx) {
    s16 temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (gSaveContext.save.inventory.items[SLOT_OCARINA] != ITEM_NONE && !CHECK_QUEST_ITEM(QUEST_SONG_HEALING)) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->actionFunc = func_80AD1634;
        } else if ((((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) && (temp_v1 < 0x4000)) &&
                   (temp_v1 > -0x4000)) {
            func_800B863C(&this->actor, globalCtx);
            this->actor.textId = 0xFFFF;
        }
    } else {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->unk_1F4 = func_80AD0E10(this, globalCtx);
            Message_StartTextbox(globalCtx, this->unk_1F4, &this->actor);
            this->actionFunc = func_80AD19A0;
        } else if ((((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) && (temp_v1 < 0x4000)) &&
                   (temp_v1 > -0x4000)) {
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
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 130)) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 130);
        this->unk_1F0 = 0;
        if (this->unk_1ED != globalCtx->csCtx.actorActions[actionIndex]->action) {
            this->unk_1ED = globalCtx->csCtx.actorActions[actionIndex]->action;
            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
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
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_1EC);
        }

        if ((this->unk_1EC == 5) && (globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 0xB) &&
            (globalCtx->csCtx.frames == 400)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_OMVO00);
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
            (((Animation_OnFrame(&this->skelAnime, 17.0f))) || (Animation_OnFrame(&this->skelAnime, 27.0f)) ||
             (Animation_OnFrame(&this->skelAnime, 37.0f)) || (Animation_OnFrame(&this->skelAnime, 47.0f)) ||
             (Animation_OnFrame(&this->skelAnime, 57.0f)) || (Animation_OnFrame(&this->skelAnime, 67.0f)))) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OMENYA_WALK);
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    } else {
        this->unk_1F0 = 1;
        this->unk_1ED = 0x63;
        func_80AD144C(this, globalCtx);
    }
}

void func_80AD19A0(EnOsn* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if ((temp_v0 == 6 || temp_v0 == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_1EA & 0x20) {
            this->unk_1EA &= ~0x20;
            globalCtx->msgCtx.msgMode = 0x43;
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
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_osn_Skel_0202F0, &object_osn_Anim_0201BC, 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->unk_1FA = 255;
    switch (ENOSN_GET_3(&this->actor)) {
        case 0:
            if (((gSaveContext.save.entranceIndex == 0xC020) || (gSaveContext.save.entranceIndex == 0xC030)) ||
                (gSaveContext.save.entranceIndex == 0xC060)) {
                this->unk_1EA |= 1;
            }
            this->unk_1F0 = 1;
            if (globalCtx->sceneNum == SCENE_INSIDETOWER) {
                if ((gSaveContext.save.entranceIndex == 0xC020) || (gSaveContext.save.entranceIndex == 0xC060)) {
                    this->actionFunc = func_80AD16A8;
                    return;
                }
                if (gSaveContext.save.entranceIndex == 0xC030) {
                    func_80AD1398(this);
                    this->actionFunc = func_80AD1634;
                    return;
                }
                func_80AD144C(this, globalCtx);
                return;
            }
            func_80AD144C(this, globalCtx);
            break;

        case 1:
            this->unk_1EC = 0xF;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_1EC);
            this->actionFunc = EnOsn_Idle;
            break;

        case 2:
            this->unk_1EC = 0x10;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, this->unk_1EC);
            this->actionFunc = EnOsn_Idle;
            break;

        case 3:
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actionFunc = func_80AD16A8;
            break;

        default:
            Actor_MarkForDeath(&this->actor);
    }
}

void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOsn* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOsn* this = THIS;
    u32 sp34;

    sp34 = Flags_GetSwitch(globalCtx, 0);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    if (!(ENOSN_GET_3(&this->actor))) {
        if (sp34 != 0) {
            this->actor.flags |= ACTOR_FLAG_1;
            func_80AD0830(this, globalCtx);
            this->actor.draw = EnOsn_Draw;
        } else {
            this->actor.draw = NULL;
            this->actor.flags &= ~ACTOR_FLAG_1;
        }
    }
    func_800E9250(globalCtx, &this->actor, &this->unk_1D8, &this->unk_1DE, this->actor.focus.pos);
}

s32 EnOsn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                           Gfx** gfx) {
    EnOsn* this = (EnOsn*)thisx;

    if (this->unk_1F0 && limbIndex == 11) {
        Matrix_InsertXRotation_s(this->unk_1D8.y, MTXMODE_APPLY);
    }
    if ((this->unk_1EC == 9 || this->unk_1EC == 8) && limbIndex == 10) {
        *dList = NULL;
    }
    return false;
}

void EnOsn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnOsn* this = (EnOsn*)thisx;
    Vec3f sp30 = { 0.0f, 0.0f, 0.0f };
    Vec3s sp28 = { 0x9920, -0x384, -0x320 };

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&sp30, &thisx->focus.pos);
    }
    if (((this->unk_1EC == 17) || (this->unk_1EC == 21) || (this->unk_1EC == 22)) && (limbIndex == 6)) {
        Matrix_StatePush();
        Matrix_InsertTranslation(-400.0f, 1100.0f, -200.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(sp28.x, MTXMODE_APPLY);
        Matrix_RotateY(sp28.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(sp28.z, MTXMODE_APPLY);

        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, &object_osn_DL_0192A0);
        Matrix_StatePop();
    }
}

void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80AD2588 = object_osn_Tex_0166F8;
    static TexturePtr D_80AD258C = object_osn_Tex_016EF8;
    static TexturePtr D_80AD2590 = object_osn_Tex_0176F8;
    static TexturePtr D_80AD2594 = object_osn_Tex_017EF8;
    static TexturePtr D_80AD2598 = object_osn_Tex_0182F8;
    s32 pad;
    EnOsn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_1FA == 0xFF) {
        func_8012C28C(globalCtx->state.gfxCtx);
        if ((this->unk_1EC == 0xB) || (this->unk_1EC == 0xC) || (this->unk_1EC == 0x17) ||
            (globalCtx->msgCtx.currentTextId == 0x1FCA)) {
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
        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnOsn_OverrideLimbDraw, EnOsn_PostLimbDraw,
                                           &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD2588));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD2594));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->unk_1FA);
        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnOsn_OverrideLimbDraw, EnOsn_PostLimbDraw,
                                           &this->actor, POLY_XLU_DISP);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
