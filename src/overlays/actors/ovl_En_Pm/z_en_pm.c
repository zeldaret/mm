/*
 * File: z_en_pm.c
 * Overlay: ovl_En_Pm
 * Description: Postman
 */

#include "z_en_pm.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_mm/object_mm.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnPm*)thisx)

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AFA4D0(EnPm* this, GlobalContext* globalCtx);
void func_80AFA5FC(EnPm* this, GlobalContext* globalCtx);

// Game scripts
static UNK_TYPE D_80AFAD80[] = {
    0x0D000102, 0x3B030900, 0x0C00010B, 0x030C000D, 0x0100F902, 0x0D010F00, 0x12020F00, 0x00050105, 0x0A002E06,
    0x0E0F0000, 0x0508050A, 0x006D3102, 0x0D010D04, 0x25020D04, 0x0D151902, 0x0E300E38, 0x0D020E38, 0x0F000105,
    0x0E0E380F, 0x00020E0E, 0x300E383E, 0x0E0D040D, 0x15350E0D, 0x010D0401, 0x0A006F31, 0x020D040D, 0x1525020D,
    0x150D2719, 0x020E260E, 0x300D020E, 0x300E3801, 0x050E0E30, 0x0E383D0E, 0x0E260E30, 0x3C0E0D15, 0x0D27370E,
    0x0D040D15, 0x360A006C, 0x31020D27, 0x0D382502, 0x0D380E00, 0x19020E1A, 0x0E1E0D02, 0x0E1E0E26, 0x01050E0E,
    0x1E0E263B, 0x0E0E1A0E, 0x1E0B0E0D, 0x380E000A, 0x0E0D270D, 0x38380A00, 0x613D020D, 0x380E0031, 0x020E000E,
    0x0825020E, 0x080E1219, 0x020E120E, 0x1A0D020E, 0x1A0E1E01, 0x050E0E1A, 0x0E1E0D0E, 0x0E120E1A, 0x3A0E0E08,
    0x0E12100E, 0x0E000E08, 0x390E0D38, 0x0E000C05, 0x0A002E06, 0x0E0C000D, 0x0109050A, 0x006D3102, 0x09000903,
    0x25020903, 0x09111902, 0x0B2B0B39, 0x0D020B39, 0x0C000105, 0x0E0B390C, 0x00020E0B, 0x2B0B3934, 0x0E090309,
    0x11260E09, 0x00090301, 0x0A006F61, 0x02090309, 0x11550209, 0x11091F49, 0x02091F09, 0x233D0209, 0x23093131,
    0x020A390B, 0x0B25020B, 0x0B0B1919, 0x020B190B, 0x1D0D020B, 0x1D0B2B01, 0x050E0B1D, 0x0B2B320E, 0x0B190B1D,
    0x070E0B0B, 0x0B19300E, 0x0A390B0B, 0x2F0E0923, 0x0931290E, 0x091F0923, 0x030E0911, 0x091F280E, 0x09030911,
    0x270A006E, 0x25020931, 0x0A031902, 0x0A030A07, 0x0D020A07, 0x0A150105, 0x0E0A070A, 0x152B0E0A, 0x030A0704,
    0x0E09310A, 0x032A0A00, 0x6C61020A, 0x150A2355, 0x020A230A, 0x2749020A, 0x270A353D, 0x020A350A, 0x3931020A,
    0x390B0B25, 0x020B0B0B, 0x1919020B, 0x190B1D0D, 0x020B1D0B, 0x2B01050E, 0x0B1D0B2B, 0x330E0B19, 0x0B1D070E,
    0x0B0B0B19, 0x310E0A39, 0x0B0B2E0E, 0x0A350A39, 0x060E0A27, 0x0A352D0E, 0x0A230A27, 0x050E0A15, 0x0A232C05,
    0x0D000201, 0xCF011C08, 0x00A50309, 0x000C00FE, 0xC6030C00, 0x0D01008C, 0x020D010F, 0x007E0200, 0x00020001,
    0x050A006D, 0x31020000, 0x00042502, 0x0004001F, 0x1902011D, 0x01380D02, 0x01380200, 0x01050E01, 0x38020002,
    0x0E011D01, 0x384F0E00, 0x04001F4A, 0x0E000000, 0x04010A00, 0x6F3D0200, 0x04001F31, 0x02001F00, 0x3A250200,
    0x3A010219, 0x02010201, 0x1D0D0201, 0x1D013801, 0x050E011D, 0x01384E0E, 0x0102011D, 0x4D0E003A, 0x0102120E,
    0x001F003A, 0x4C0E0004, 0x001F4B05, 0x0A002E03, 0x04000E05, 0x0A002E06, 0x0E0C000D, 0x01140503, 0x09000C00,
    0xFE21030C, 0x000D0101, 0x0C020D01, 0x11001202, 0x11000005, 0x01050A00, 0x2E060E11, 0x00000508, 0x050A006D,
    0x31020D01, 0x0D042502, 0x0D040D0F, 0x19021023, 0x10390D02, 0x10391100, 0x01050E10, 0x39110002, 0x0E102310,
    0x39490E0D, 0x040D0F3F, 0x0E0D010D, 0x04010A00, 0x6F31020D, 0x040D0F25, 0x020D0F0D, 0x1E19020D, 0x340E2D0D,
    0x02100F10, 0x2301050E, 0x100F1023, 0x480E0D34, 0x0E2D430E, 0x0D0F0D1E, 0x410E0D04, 0x0D0F400A, 0x006C1902,
    0x0D1E0D34, 0x0D020D34, 0x0E320105, 0x0E0D340E, 0x32440E0D, 0x1E0D3442, 0x0A007068, 0x020E2D0F, 0x055C0C00,
    0x0231020F, 0x050F1425, 0x020F140F, 0x1919020F, 0x190F280D, 0x020F2810, 0x0F01050E, 0x0F28100F, 0x510E0F19,
    0x0F28110E, 0x0F140F19, 0x500E0F05, 0x0F141702, 0x0F050F14, 0x1B020F14, 0x0F320F02, 0x0F32100F, 0x03040000,
    0x0E0F3210, 0x0F470E0F, 0x140F3219, 0x0E0F050F, 0x14170E0E, 0x2D0F0546, 0x050A002E, 0x060E0C00, 0x0D011505,
    0x0D000301, 0x6F011C08, 0x013F011C, 0x10010C03, 0x09000C00, 0xFCED030C, 0x000D0100, 0xF6020D01, 0x0F000F02,
    0x12000600, 0x01050A00, 0x2E030400, 0x18050A00, 0x6D31020D, 0x000D0125, 0x020D050D, 0x0F19020E, 0x2D0E370D,
    0x020E370F, 0x0001050E, 0x0E370F00, 0x020E0E2D, 0x0E37340E, 0x0D050D0F, 0x260E0D00, 0x0D01010A, 0x006F4902,
    0x0D050D0F, 0x3D020D0F, 0x0D193102, 0x0D190D23, 0x25020E0F, 0x0E191902, 0x0E190E23, 0x0D020E23, 0x0E2D0105,
    0x0E0E230E, 0x2D320E0E, 0x190E2330, 0x0E0E0F0E, 0x192F0E0D, 0x190D2329, 0x0E0D0F0D, 0x19280E0D, 0x050D0F27,
    0x0A006E19, 0x020D230D, 0x2D0D020D, 0x2D0D3701, 0x050E0D2D, 0x0D372B0E, 0x0D230D2D, 0x2A0A006C, 0x3D020D37,
    0x0E053102, 0x0E050E0F, 0x25020E0F, 0x0E191902, 0x0E190E23, 0x0D020E23, 0x0E2D0105, 0x0E0E230E, 0x2D330E0E,
    0x190E2331, 0x0E0E0F0E, 0x192E0E0E, 0x050E0F2D, 0x0E0D370E, 0x052C050A, 0x002E0304, 0x00160503, 0x09000C00,
    0xFBE1020C, 0x000D0116, 0x030D0111, 0x00FDD202, 0x12000600, 0x01050A00, 0x2E030400, 0x18050A00, 0x2E060E0C,
    0x000D0115, 0x05030900, 0x0C00FBB3, 0x020C000D, 0x0116030D, 0x010F00FE, 0xD5021200, 0x06000105, 0x0A002E03,
    0x04001805, 0x0A002E03, 0x04001405, 0x05000000,
};

static UNK_TYPE D_80AFB30C[] = {
    0x0A002E2E, 0x02000000, 0x0A220200, 0x0A000D19, 0x02000D00, 0x170D0200, 0x17001A01, 0x050E0017, 0x001A200E,
    0x000D0017, 0x5304001B, 0x0E000000, 0x0A520A00, 0x6D190200, 0x17001A0D, 0x02001A00, 0x2401050E, 0x001A0024,
    0x540E0017, 0x001A210A, 0x006F1902, 0x001A0024, 0x0D020024, 0x002E0105, 0x0E002400, 0x2E560E00, 0x1A002455,
    0x0A006C19, 0x02002E00, 0x380D0200, 0x38003B01, 0x050E0038, 0x003B220E, 0x002E0038, 0x570A0015, 0x25020038,
    0x003B1902, 0x003B0109, 0x0D020109, 0x01280105, 0x0E010901, 0x281C0E00, 0x3B010958, 0x0E003800, 0x3B240500,
};

static UNK_TYPE D_80AFB3C0[] = {
    0x0A006C19, 0x02000A00, 0x0D0D0200, 0x0D001701, 0x050E000D, 0x00175A0E, 0x000A000D, 0x230A0015,
    0x19020000, 0x000A0D02, 0x000A000D, 0x01050E00, 0x0A000D25, 0x0E000000, 0x0A590500,
};

static UNK_TYPE D_80AFB3FC[] = {
    0x0A006C19, 0x02120006, 0x000D0205, 0x00050A01, 0x050E0500, 0x050A5B0E, 0x12000600, 0x1D050000,
};

static UNK_TYPE D_80AFB41C[] = {
    0x0A006C0D, 0x02000000, 0x0A01050E, 0x0000000A, 0x5B050000,
};

static s32 D_80AFB430[] = {
    -1, 0, 4, 1,  0,  0, 1, 4,  -1, -1, 15, 5, 0, 3, -1, -1, 1, 2, 11, 3, -1, -1, -1, 0, 0, 0, 0, 0, 1,  12, -1,
    -1, 2, 0, 10, 11, 0, 3, 1,  0,  1,  2,  0, 1, 0, 1,  2,  3, 4, 3,  5, 14, 3,  1,  0, 6, 4, 1, 2, 6,  7,  8,
    2,  1, 0, 6,  7,  9, 8, -1, 0,  1,  10, 3, 1, 0, 11, 12, 8, 2, 2,  3, 0,  1,  1,  0, 6, 9, 1, 2, 12, 13,
};

// Game scripts
static UNK_TYPE D_80AFB5A0[] = {
    0x00560800, 0x45090000, 0x170E28BA, 0x0C090000, 0x180E28BB, 0x0C090000, 0x170E28BC, 0x0C090000, 0x180E28BD,
    0x0C090000, 0x170E28BE, 0x0C090000, 0x180E28BF, 0x0C090000, 0x170E28C0, 0x2D00012D, 0x000B0C09, 0x00001156,
    0x08100900, 0x00170E29, 0x5C0C0900, 0x00180E29, 0x5D0C0900, 0x00170E29, 0x5E2D0001, 0x2D000B0C, 0x09000010,
};

static UNK_TYPE D_80AFB60C[] = {
    0x0E27742D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB614[] = {
    0x0E27752D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB61C[] = {
    0x0E27772D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB624[] = {
    0x0E27782D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB62C[] = {
    0x0E27792D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB634[] = {
    0x0E27812D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB63C[] = {
    0x0E277A2D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB644[] = {
    0x0E27822D,
    0x000B0C11,
    0x58021000,
};

static UNK_TYPE D_80AFB650[] = {
    0x0E27832D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB658[] = {
    0x25002E00, 0x1A005280, 0x000C0E27, 0x7C2D000B, 0x0C115280, 0x12100E27, 0x7D2D000B, 0x0C12100E, 0x277C0C0E,
    0x00FF1E00, 0x33000000, 0x1800282C, 0xFFFF0900, 0x000E277E, 0x2D000B0C, 0x11528011, 0x56012A00, 0x2E12102C,
    0x277D0C2F, 0x00002D00, 0x0B0C1152, 0x8012100E, 0x277D2D00, 0x0B0C1152, 0x80121000,
};

static UNK_TYPE D_80AFB6BC[] = {
    0x0900000E, 0x27A50C09, 0x0000170E, 0x27A60C09, 0x0000180E, 0x27A70C09, 0x0000170E,
    0x27A80C09, 0x0000180E, 0x27A90C09, 0x0000170E, 0x27AA0C09, 0x0000180E, 0x27AB0C09,
    0x0000170E, 0x27AC0C09, 0x0000180E, 0x27AD2D00, 0x0B2D0008, 0x0C115908, 0x09000010,
};

static UNK_TYPE D_80AFB710[] = {
    0x25003E00, 0x230E2780, 0x0C0F27AE, 0x0C120600, 0x84000013, 0x0084115A, 0x042F0000,
    0x2E2D000B, 0x2D00310C, 0x115A0110, 0x0E27802D, 0x000B0C11, 0x5A011210,
};

static UNK_TYPE D_80AFB744[] = {
    0x0E23692D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB74C[] = {
    0x2CFFFF09, 0x00000E27, 0x7E2D000B, 0x0C115280, 0x1156012A, 0x002E1210,
};

static UNK_TYPE D_80AFB764[] = {
    0x2C277D2D,
    0x000B0C11,
    0x52801210,
};

const ActorInit En_Pm_InitVars = {
    ACTOR_EN_PM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnPm),
    (ActorFunc)EnPm_Init,
    (ActorFunc)EnPm_Destroy,
    (ActorFunc)EnPm_Update,
    (ActorFunc)EnPm_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 26 }, 100 },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &object_mm_Anim_002238, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_002238, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_mm_Anim_00A4E0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_mm_Anim_00B09C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_00B09C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_mm_Anim_00BA78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_mm_Anim_00C32C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_mm_Anim_0099B4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_000FC4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_00A8D8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_00099C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_001F84, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_mm_Anim_000468, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_mm_Anim_00C640, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

s32 func_80AF7B40(void) {
    if (gSaveContext.save.weekEventReg[90] & 1) {
        return 4;
    }

    if (gSaveContext.save.weekEventReg[89] & 0x40) {
        return 3;
    }

    if (gSaveContext.save.weekEventReg[89] & 8) {
        return 2;
    }

    if (gSaveContext.save.weekEventReg[86] & 1) {
        return 1;
    }

    return 0;
}

s32 func_80AF7BAC(EnPm* this) {
    switch (this->unk_38C) {
        case 0:
            if (gSaveContext.save.weekEventReg[86] & 1) {
                D_801F4E78 = gSaveContext.save.time;
                this->unk_38C++;
            }
            break;

        case 1:
            if (gSaveContext.save.weekEventReg[89] & 8) {
                D_801F4E78 = gSaveContext.save.time;
                this->unk_38C++;
            }
            break;

        case 2:
            if (gSaveContext.save.weekEventReg[89] & 0x40) {
                D_801F4E78 = 0;
                this->unk_38C++;
            }
            break;

        case 3:
            if (gSaveContext.save.weekEventReg[90] & 1) {
                D_801F4E78 = gSaveContext.save.time;
                this->unk_38C++;
            }
            break;
    }

    return true;
}

Actor* func_80AF7CB0(EnPm* this, GlobalContext* globalCtx, u8 actorCat, s16 actorId) {
    Actor* phi_s0 = NULL;
    Actor* actor;

    while (true) {
        actor = SubS_FindActor(globalCtx, phi_s0, actorCat, actorId);
        phi_s0 = actor;

        if (actor == NULL) {
            break;
        }

        if (((EnPm*)phi_s0 != this) && (actor->update != NULL)) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            phi_s0 = NULL;
            break;
        }

        phi_s0 = actor;
    }

    return phi_s0;
}

EnDoor* func_80AF7D60(GlobalContext* globalCtx, s32 arg1) {
    s32 phi_a1;

    switch (arg1) {
        case 1:
        case 2:
        case 32:
        case 33:
            phi_a1 = 1;
            break;

        case 34:
        case 35:
        case 36:
        case 37:
            phi_a1 = 10;
            break;

        case 10:
        case 11:
        case 12:
        case 13:
            phi_a1 = 11;
            break;

        default:
            return NULL;
    }

    return SubS_FindDoor(globalCtx, phi_a1);
}

Actor* func_80AF7DC4(EnPm* this, GlobalContext* globalCtx, s32 arg2) {
    Actor* phi_s0 = NULL;
    Actor* actor;

    while (true) {
        actor = SubS_FindActor(globalCtx, phi_s0, ACTORCAT_PROP, ACTOR_EN_PST);
        phi_s0 = actor;

        if (actor == NULL) {
            break;
        }

        if (((EnPm*)actor != this) && (actor->update != NULL) && (actor->params == (s16)arg2)) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            phi_s0 = NULL;
            break;
        }

        phi_s0 = actor;
    }

    return phi_s0;
}

void func_80AF7E6C(EnPm* this) {
    this->skelAnime.playSpeed = this->unk_35C;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80AF7E98(EnPm* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    switch (arg1) {
        case 0:
        case 1:
            if ((this->unk_384 != 0) && (this->unk_384 != 1)) {
                phi_v1 = true;
            }
            break;

        case 3:
        case 4:
            if ((this->unk_384 != 3) && (this->unk_384 != 4)) {
                phi_v1 = true;
            }
            break;

        default:
            if (arg1 != this->unk_384) {
                phi_v1 = true;
            }
            break;
    }

    if (phi_v1) {
        this->unk_384 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg1);
        this->unk_35C = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80AF7F68(EnPm* this, GlobalContext* globalCtx) {
    f32 temp;
    s32 pad;

    switch (this->unk_258) {
        case 9:
        case 20:
        case 21:
        case 22:
        case 24:
            temp = this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
            this->colliderSphere.dim.worldSphere.radius = temp;
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
            break;

        default:
            Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
            temp = this->actor.focus.pos.y - this->actor.world.pos.y;
            this->colliderCylinder.dim.height = temp;
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
            break;
    }
}

Actor* func_80AF8040(EnPm* this, GlobalContext* globalCtx) {
    Actor* actor;

    switch (this->unk_258) {
        case 16:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AN);
            break;

        case 17:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TEST3);
            break;

        case 28:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            actor = func_80AF7DC4(this, globalCtx, this->unk_258 - 3);
            break;

        case 19:
            actor = func_80AF7DC4(this, globalCtx, 4);
            break;

        case 18:
            actor = func_80AF7DC4(this, globalCtx, 4);
            break;

        default:
            actor = &GET_PLAYER(globalCtx)->actor;
            break;
    }

    return actor;
}

s32 func_80AF80F4(EnPm* this, s16 arg1) {
    s32 ret = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        ret = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }
    return ret;
}

s16 func_80AF8170(EnPm* this, s32 arg1) {
    s32 i;
    s16 cs = -1;

    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        cs = this->actor.child->cutscene;

        for (i = 0; i < arg1; i++) {
            cs = ActorCutscene_GetAdditionalCutscene(cs);
        }
    }
    return cs;
}

s32 func_80AF81E8(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, sp2A)) {
                break;
            }

        case 2:
        case 4:
        case 6:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)),
                                      this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
            if ((gSaveContext.save.weekEventReg[86] & 8) && (this->unk_378 == 3)) {
                ActorCutscene_Stop(sp2A);
            } else {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            }
            this->unk_378++;
            ret = true;
            break;

        case 7:
            ActorCutscene_Stop(sp2A);
            this->unk_378++;
            ret = true;
            break;
    }
    return ret;
}

s32 func_80AF8348(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, sp2A)) {
                break;
            }

        case 2:
        case 4:
        case 6:
        case 8:
            Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)),
                                      this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 9:
            ActorCutscene_Stop(sp2A);
            this->unk_378++;
            ret = true;
            break;
    }

    return ret;
}

s32 func_80AF8478(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            func_80AF7E98(this, 2);
            this->unk_356 &= ~0x20;
            this->unk_356 |= 0x200;
            this->unk_378++;
            break;

        case 1:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 4);
                this->unk_356 &= ~0x200;
                this->unk_356 |= 0x20;
                this->unk_378++;
                ret = true;
            }
            break;
    }
    return ret;
}

UNK_TYPE* func_80AF8540(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 28:
            this->unk_37C = func_80AF8348;
            return D_80AFB6BC;

        case 29:
            return D_80AFB710;

        case 16:
            this->unk_37C = func_80AF81E8;
            return D_80AFB5A0;

        case 17:
            return D_80AFB644;

        case 24:
            if (this->unk_356 & 0x2000) {
                this->unk_37C = func_80AF8478;
                return D_80AFB74C;
            } else if (this->unk_356 & 0x4000) {
                return D_80AFB764;
            } else {
                this->unk_37C = func_80AF8478;
                return D_80AFB658;
            }
            break;

        case 25:
            return D_80AFB650;

        default:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
                return D_80AFB744;
            }

            switch (this->unk_258) {
                case 9:
                    return D_80AFB614;

                case 14:
                    return D_80AFB624;

                case 20:
                    return D_80AFB61C;

                case 21:
                    return D_80AFB634;

                case 22:
                    return D_80AFB63C;

                case 18:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                    return D_80AFB62C;

                default:
                    return D_80AFB60C;
            }
            break;
    }
}

s32 func_80AF86F0(EnPm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_356 & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        SubS_UpdateFlags(&this->unk_356, 0, 7);
        this->unk_398 = 0;
        this->unk_378 = 0;
        this->unk_37C = NULL;
        this->actor.child = this->unk_268;
        this->unk_25C = func_80AF8540(this, globalCtx);
        if ((this->unk_258 != 24) && (this->unk_258 != 9) && (this->unk_258 != 20) && (this->unk_258 != 21) &&
            (this->unk_258 != 22)) {
            this->unk_356 |= 0x20;
        }
        this->actionFunc = func_80AFA5FC;
        ret = true;
    }
    return ret;
}

s32 func_80AF87C4(EnPm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((globalCtx->csCtx.state != 0) && (globalCtx->sceneNum == SCENE_00KEIKOKU) &&
        (gSaveContext.sceneSetupIndex == 9) && (globalCtx->curSpawn == 1)) {
        if (!this->unk_380) {
            func_80AF7E98(this, 0);
            this->unk_258 = 255;
            this->unk_380 = true;
            this->actor.speedXZ = 4.0f;
            this->actor.gravity = -1.0f;
        }
        ret = true;
    } else if (this->unk_380) {
        this->unk_258 = 0;
        this->unk_380 = false;
        this->actor.speedXZ = 0.0f;
    }
    return ret;
}

void func_80AF8890(EnPm* this, Gfx** gfx, s32 arg2) {
    Matrix_StatePush();

    switch (arg2) {
        case 0:
            if (this->unk_356 & 0x800) {
                gSPDisplayList((*gfx)++, object_mm_DL_008348);
            }
            break;

        case 1:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0085C8);
            }
            break;

        case 2:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0083E0);
            }
            break;
    }

    Matrix_StatePop();
}

void func_80AF898C(EnPm* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;

    Math_Vec3f_Copy(&sp40, &this->unk_268->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_372, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_372 = CLAMP(this->unk_372, -0x1FFE, 0x1FFE);
    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    if (this->unk_268->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_268)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_268->focus.pos);
    }
    Math_ApproachS(&this->unk_370, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    this->unk_370 = CLAMP(this->unk_370, -0x1554, 0x1554);
}

void func_80AF8AC8(EnPm* this) {
    if ((this->unk_356 & 0x20) && (this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        if (DECR(this->unk_376) == 0) {
            func_80AF898C(this);
            this->unk_356 &= ~0x200;
            this->unk_356 |= 0x80;
            return;
        }
    }

    if (this->unk_356 & 0x80) {
        this->unk_356 &= ~0x80;
        this->unk_370 = 0;
        this->unk_372 = 0;
        this->unk_376 = 20;
    } else if (DECR(this->unk_376) == 0) {
        this->unk_356 |= 0x200;
    }
}

void func_80AF8BA8(s32 arg0) {
    static u16 D_80AFB8D4[] = {
        0x1B02, 0x1B04, 0x1B08, 0x1B10, 0x1B20, 0x0000,
    };
    static u16 D_80AFB8E0[] = {
        0x1B40, 0x1B80, 0x1C01, 0x1C02, 0x1C04, 0x0000,
    };
    s32 temp;

    if (!(gSaveContext.save.weekEventReg[88] & 2)) {
        if (gSaveContext.save.weekEventReg[D_80AFB8D4[arg0] >> 8] &
            (D_80AFB8D4[arg0] & (1 | 2 | 4 | 0x38 | 0x40 | 0x80))) {
            switch (gSaveContext.save.day) {
                case 2:
                    gSaveContext.save.weekEventReg[28] |= 8;
                    break;

                case 3:
                    gSaveContext.save.weekEventReg[28] |= 0x10;
                    break;
            }
            gSaveContext.save.weekEventReg[51] |= 2;
            gSaveContext.save.weekEventReg[90] |= 8;
        }
    }

    temp = gSaveContext.save.weekEventReg[D_80AFB8E0[arg0] >> 8];
    gSaveContext.save.weekEventReg[D_80AFB8E0[arg0] >> 8] =
        temp | (D_80AFB8E0[arg0] & (1 | 2 | 4 | 0x38 | 0x40 | 0x80));
}

void func_80AF8C68(EnPm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28 = Message_GetState(&globalCtx->msgCtx);
    u16 temp_a0 = globalCtx->msgCtx.currentTextId;

    if ((player->targetActor == &this->actor) && ((temp_a0 < 255) || (temp_a0 > 512)) && (sp28 == 3) &&
        (this->unk_388 == 3)) {
        if ((globalCtx->state.frames % 3) == 0) {
            if (this->unk_360 == 120.0f) {
                this->unk_360 = 0.0f;
            } else {
                this->unk_360 = 120.0f;
            }
        }
    } else {
        this->unk_360 = 0.0f;
    }
    Math_SmoothStepToF(&this->unk_364, this->unk_360, 0.8f, 40.0f, 10.0f);
    Matrix_InsertTranslation(this->unk_364, 0.0f, 0.0f, MTXMODE_APPLY);
    this->unk_388 = sp28;
}

s32 func_80AF8D84(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_384) {
        case 10:
            func_80AF7E98(this, 9);
            break;

        case 7:
            func_80AF7E98(this, 0);
            break;
    }
    return true;
}

s32 func_80AF8DD4(EnPm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 temp = globalCtx->msgCtx.currentTextId;
    s32 pad;

    if (player->stateFlags1 & (0x400 | 0x40)) {
        this->unk_356 |= 0x400;
        if (this->unk_358 != temp) {
            if ((this->unk_384 == 0) || (this->unk_384 == 1)) {
                func_80AF7E98(this, 7);
            }
            if ((temp == 0x277C) || (temp == 0x277D)) {
                func_80AF7E98(this, 10);
            }
        }
        this->unk_358 = temp;
    } else {
        if (this->unk_356 & 0x400) {
            this->unk_358 = 0;
            this->unk_356 &= ~0x400;
            func_80AF8D84(this, globalCtx);
        }
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, globalCtx);
    }

    return 0;
}

s32 func_80AF8ED4(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2, u8 actorCat, s16 actorId) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* sp2C;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    sp2C = func_80AF7CB0(this, globalCtx, actorCat, actorId);
    if (D_80AFB430[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80AFB430[arg2->unk0]);
    }

    if ((sp2C != NULL) && (sp2C->update != NULL)) {
        if (this->unk_234 != NULL) {
            sp48 = Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp3C, &sp48[this->unk_234->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &sp48[this->unk_234->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

s32 func_80AF9008(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp56 = gSaveContext.save.time - 0x3FFC;
    u8 sp55 = this->actor.params & 0xFF;
    EnDoor* door;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s16 temp;
    s32 ret = false;

    this->unk_234 = NULL;
    door = func_80AF7D60(globalCtx, arg2->unk0);
    if (D_80AFB430[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp55, D_80AFB430[arg2->unk0]);
    }

    if ((door != NULL) && (door->dyna.actor.update != NULL)) {
        if (this->unk_234 != 0) {
            sp4C = Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp40, &sp4C[0]);
            Math_Vec3s_ToVec3f(&sp34, &sp4C[1]);
            Math_Vec3f_Copy(&this->unk_26C, &sp40);
            Math_Vec3f_Copy(&this->unk_278, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
            temp = this->actor.world.rot.y - door->dyna.actor.shape.rot.y;
            if (ABS_ALT(temp) <= 0x4000) {
                this->unk_260 = -0x4B;
            } else {
                this->unk_260 = 0x4B;
            }

            this->unk_36C = arg2->unk8 - arg2->unk4;
            this->unk_36E = sp56 - arg2->unk4;
            this->actor.flags &= ~ACTOR_FLAG_1;
            if (gSaveContext.save.weekEventReg[90] & 8) {
                this->unk_356 |= 0x800;
            }
            this->unk_356 |= 0x9000;
            this->unk_356 |= 0x200;
            func_80AF7E98(this, 0);
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }
    return ret;
}

s32 func_80AF91E8(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp2E = (u16)(gSaveContext.save.time - 0x3FFC);
    u16 phi_v1;
    u8 sp2B = this->actor.params & 0xFF;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;

    if (D_80AFB430[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp2B, D_80AFB430[arg2->unk0]);
    }

    if ((this->unk_234 != NULL) && (this->unk_234->count < 3)) {
        this->unk_234 = NULL;
    }

    if (this->unk_234 != 0) {
        if ((this->unk_258 < 38) && (this->unk_258 != 0) && (this->unk_374 >= 0)) {
            phi_v1 = sp2E;
        } else {
            phi_v1 = arg2->unk4;
        }

        if (arg2->unk8 < phi_v1) {
            this->unk_248 = (phi_v1 - arg2->unk8) + 0xFFFF;
        } else {
            this->unk_248 = arg2->unk8 - phi_v1;
        }

        this->unk_254 = sp2E - phi_v1;
        phi_v1 = this->unk_234->count - 2;
        this->unk_24C = this->unk_248 / phi_v1;
        this->unk_250 = (this->unk_254 / this->unk_24C) + 2;
        this->unk_356 &= ~8;
        this->unk_356 &= ~0x10;
        if (this->unk_258 == 27) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ROOM_CARTAIN);
            Flags_UnsetSwitch(globalCtx, 0);
        }

        switch (arg2->unk0) {
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;

            case 82:
                func_80AF7E98(this, 0);
                break;

            case 91:
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 12);
                break;

            default:
                SubS_UpdateFlags(&this->unk_356, 3, 7);
                func_80AF7E98(this, 0);
                if (gSaveContext.save.weekEventReg[90] & 8) {
                    this->unk_356 |= 0x800;
                }
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;
                break;
        }

        this->actor.gravity = -1.0f;
        ret = true;
    }

    return ret;
}

s32 func_80AF94AC(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    if (D_80AFB430[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80AFB430[arg2->unk0]);
    }

    if ((this->unk_234 != 0) && (this->unk_234->count >= 2)) {
        sp30 = Lib_SegmentedToVirtual(this->unk_234->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[0]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[1]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);
        if (arg2->unk0 == 24) {
            Flags_UnsetSwitch(globalCtx, 0);
            Flags_UnsetSwitch(globalCtx, 1);
            this->unk_394 = 0;
            this->unk_368 = 60.0f;
            func_80AF7E98(this, 9);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF95E8(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;
    s32 phi_a3 = -1;

    switch (arg2->unk0) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            phi_a3 = arg2->unk0 - 3;
            break;

        case 19:
            phi_a3 = 4;
            break;
    }

    if ((phi_a3 >= 0) && !func_80AF7DC4(this, globalCtx, phi_a3)) {
        return ret;
    }

    this->unk_234 = NULL;
    phi_a3 = D_80AFB430[arg2->unk0];
    if (phi_a3 >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp4F, phi_a3);
    }

    if ((this->unk_234 != 0) && (this->unk_234->count >= 2)) {
        sp30 = Lib_SegmentedToVirtual(this->unk_234->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[this->unk_234->count - 1]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[this->unk_234->count - 2]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (arg2->unk0) {
            case 27:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ROOM_CARTAIN);
                Flags_SetSwitch(globalCtx, 0);
                this->unk_36C = 20;
                SubS_UpdateFlags(&this->unk_356, 3, 7);
                func_80AF7E98(this, 3);
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 19:
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 11);
                break;

            case 18:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x800;
                func_80AF7E98(this, 5);
                break;

            case 23:
                if (gSaveContext.save.weekEventReg[90] & 8) {
                    this->unk_356 |= 0x800;
                }
                gSaveContext.save.weekEventReg[60] |= 4;

            default:
                if (arg2->unk0 == 0x1D) {
                    this->actor.world.rot.y = BINANG_ROT180(this->actor.world.rot.y);
                }
                SubS_UpdateFlags(&this->unk_356, 3, 7);
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 3);
                break;
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF98A0(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_MM3, 116.0f, 26.0f, -219.0f, 0,
                           -0x3F46, 0, 0) != NULL) {
        Actor_MarkForDeath(&this->actor);
        ret = true;
    }
    return ret;
}

s32 func_80AF992C(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80AFB8EC = { 116.0f, 26.0f, -219.0f };
    static Vec3s D_80AFB8F8 = { 0x0000, 0xC0BA, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80AFB8EC);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80AFB8F8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    SubS_UpdateFlags(&this->unk_356, 3, 7);
    this->actor.targetMode = 6;
    this->actor.gravity = -1.0f;
    this->unk_368 = 80.0f;
    if (arg2->unk0 == 14) {
        this->unk_356 &= ~0x200;
        func_80AF7E98(this, 13);
    } else {
        this->unk_356 &= ~0x200;
        func_80AF7E98(this, 8);
    }
    return true;
}

s32 func_80AF9A0C(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_AN)) {
        SubS_UpdateFlags(&this->unk_356, 3, 7);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9AB0(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_TEST3)) {
        SubS_UpdateFlags(&this->unk_356, 3, 7);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9B54(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_AL)) {
        SubS_UpdateFlags(&this->unk_356, 3, 7);
        this->unk_356 |= 0x9000;
        this->unk_356 |= 0x20;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9BF8(EnPm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.targetMode = 0;
    this->unk_394 = 0;
    this->unk_356 = 0;
    this->unk_368 = 40.0f;

    switch (arg2->unk0) {
        case 16:
            ret = func_80AF9A0C(this, globalCtx, arg2);
            break;

        case 17:
            ret = func_80AF9AB0(this, globalCtx, arg2);
            break;

        case 28:
            ret = func_80AF9B54(this, globalCtx, arg2);
            break;

        case 24:
            ret = func_80AF94AC(this, globalCtx, arg2);
            break;

        case 29:
            ret = func_80AF95E8(this, globalCtx, arg2);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            ret = func_80AF9008(this, globalCtx, arg2);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 18:
        case 19:
        case 23:
        case 25:
        case 27:
            ret = func_80AF95E8(this, globalCtx, arg2);
            break;

        case 8:
            ret = func_80AF98A0(this, globalCtx, arg2);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
            ret = func_80AF992C(this, globalCtx, arg2);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            ret = func_80AF91E8(this, globalCtx, arg2);
            break;

        default:
            ret = false;
            break;
    }
    return ret;
}

s32 func_80AF9D04(EnPm* this, GlobalContext* globalCtx) {
    EnDoor* door = (EnDoor*)func_80AF7D60(globalCtx, this->unk_258);
    Vec3f sp38;
    Vec3f* sp28;
    f32 temp;

    if (!func_8013AD6C(globalCtx) && (this->unk_374 != 0)) {
        if ((door != NULL) && (door->dyna.actor.update != NULL)) {
            if (((f32)this->unk_36E / this->unk_36C) <= 0.9f) {
                door->unk_1A7 = this->unk_260;
            } else {
                door->unk_1A7 = 0;
            }
        }
        this->unk_36E = CLAMP(this->unk_36E, 0, this->unk_36C);
        temp = Math_Vec3f_DistXZ(&this->unk_26C, &this->unk_278) / this->unk_36C;
        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_36E * temp;
        Lib_Vec3f_TranslateAndRotateY(&this->unk_26C, this->actor.world.rot.y, &sp38, &this->actor.world.pos);
        this->unk_36E += this->unk_374;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
        }
    }
    return false;
}

s32 func_80AF9E7C(EnPm* this, GlobalContext* globalCtx) {
    f32 sp7C[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54;
    s32 sp50;

    sp50 = 0;
    sp54 = 0;

    func_8013AF00(sp7C, 3, this->unk_234->count + 3);
    if (!(this->unk_356 & 8)) {
        sp58 = gZeroVec3f;
        func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &sp58, this->unk_374);
        func_8013B878(globalCtx, this->unk_234, this->unk_250, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->unk_356 |= 8;
    } else {
        sp58 = this->unk_238;
    }

    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;

    if (func_8013AD6C(globalCtx)) {
        sp54 = this->unk_254;
        sp50 = this->unk_250;
        sp58 = this->actor.world.pos;
    }

    this->unk_238 = gZeroVec3f;

    if (func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &this->unk_238, this->unk_374)) {
        this->unk_356 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->unk_238;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (func_8013AD6C(globalCtx)) {
        this->unk_254 = sp54;
        this->unk_250 = sp50;
        this->unk_238 = sp58;
    } else if ((this->unk_258 != 91) &&
               (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }

    if ((this->unk_356 & 0x10) && (this->unk_258 == 90)) {
        u8 val = gSaveContext.save.weekEventReg[89] | 0x40;

        gSaveContext.save.weekEventReg[89] = val;
        if (val == 0) {
            gSaveContext.save.weekEventReg[89] |= 0x40;
        }
    }

    return false;
}

s32 func_80AFA170(EnPm* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    Vec3f sp28;

    switch (this->unk_258) {
        case 28:
            if (gSaveContext.save.time >= CLOCK_TIME(1, 39)) {
                gSaveContext.save.weekEventReg[89] |= 8;
            }

        case 16:
        case 17:
        case 18:
            if ((this->unk_384 == 5) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 6);
                this->unk_36C = 40;
            } else if ((this->unk_384 == 6) && (DECR(this->unk_36C) == 0)) {
                this->unk_356 &= ~0x800;
                func_80AF7E98(this, 4);
            }
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 19:
            if ((this->unk_384 == 11) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 4);
            }

            if ((this->unk_384 == 11) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMACHINE_HIT_OPEN);
            }

            if (this->unk_258 == 19) {
                func_80AF8BA8(4);
            } else {
                func_80AF8BA8(this->unk_258 - 3);
            }
            break;
    }

    if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        Math_Vec3f_Copy(&sp34, &this->unk_268->world.pos);
        Math_Vec3f_Copy(&sp28, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp28, &sp34);
    }

    return true;
}

s32 func_80AFA334(EnPm* this, GlobalContext* globalCtx) {
    s16 temp_v0;

    switch (this->unk_258) {
        case 14:
        case 24:
            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            if (ABS_ALT(temp_v0) < 0x4000) {
                SubS_UpdateFlags(&this->unk_356, 3, 7);
            } else {
                SubS_UpdateFlags(&this->unk_356, 0, 7);
            }
            break;

        case 27:
            if (DECR(this->unk_36C) == 0) {
                Flags_SetSwitch(globalCtx, 1);
            }
            break;

        case 9:
        case 20:
        case 21:
        case 22:
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_NP_SLEEP_OUT);
            }
            break;

        case 29:
            break;
    }

    return false;
}

void func_80AFA438(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 16:
        case 17:
        case 18:
        case 28:
            func_80AFA170(this, globalCtx);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            func_80AF9D04(this, globalCtx);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 27:
        case 29:
            func_80AFA334(this, globalCtx);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            func_80AF9E7C(this, globalCtx);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80AFA4D0(EnPm* this, GlobalContext* globalCtx) {
    static UNK_PTR D_80AFB900[] = {
        D_80AFAD80, D_80AFB30C, D_80AFB3C0, D_80AFB3FC, D_80AFB41C,
    };
    u16 time = gSaveContext.save.time;
    u16 sp3C = 0;
    u32* unk_14 = &gSaveContext.save.daySpeed;
    struct_80133038_arg2 sp2C;

    this->unk_374 = REG(15) + *unk_14;
    if (this->unk_38C != 0) {
        time = gSaveContext.save.time - D_801F4E78;
        sp3C = gSaveContext.save.time;
        gSaveContext.save.time = time;
    }

    if (!func_80133038(globalCtx, D_80AFB900[this->unk_38C], &sp2C) ||
        ((this->unk_258 != sp2C.unk0) && !func_80AF9BF8(this, globalCtx, &sp2C))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp2C.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }

    this->unk_258 = sp2C.unk0;
    this->unk_268 = func_80AF8040(this, globalCtx);
    func_80AFA438(this, globalCtx);
    if (this->unk_38C != 0) {
        gSaveContext.save.time = sp3C;
    }
}

void func_80AFA5FC(EnPm* this, GlobalContext* globalCtx) {
    s16 yaw;
    Vec3f sp38;
    Vec3f sp2C;

    if (func_8010BF58(&this->actor, globalCtx, this->unk_25C, this->unk_37C, &this->unk_264)) {
        SubS_UpdateFlags(&this->unk_356, 3, 7);
        this->unk_356 &= ~0x20;
        this->unk_356 |= 0x200;
        this->actor.child = NULL;
        this->unk_376 = 20;
        this->unk_264 = 0;
        this->actionFunc = func_80AFA4D0;
        return;
    }

    if ((this->unk_258 != 9) && (this->unk_258 != 14) && (this->unk_258 != 16) && (this->unk_258 != 17) &&
        (this->unk_258 != 20) && (this->unk_258 != 21) && (this->unk_258 != 22) && (this->unk_258 != 24) &&
        (this->unk_258 != 25)) {
        if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
            Math_Vec3f_Copy(&sp38, &this->unk_268->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            yaw = Math_Vec3f_Yaw(&sp2C, &sp38);
            Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
        }
    }
}

void func_80AFA724(EnPm* this, GlobalContext* globalCtx) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }
}

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_mm_Skel_0096E8, NULL, this->jointTable, this->morphTable,
                       16);
    this->unk_384 = -1;
    func_80AF7E98(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_38C = func_80AF7B40();
    this->unk_258 = 0;
    this->unk_356 = 0;
    this->actionFunc = func_80AFA4D0;
    this->actionFunc(this, globalCtx);
}

void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
}

void EnPm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    if (!func_80AF86F0(this, globalCtx) && func_80AF87C4(this, globalCtx)) {
        func_80AFA724(this, globalCtx);
        func_80AF7E6C(this);
        func_80AF8AC8(this);
    } else {
        this->actionFunc(this, globalCtx);
        func_80AF7BAC(this);
        if (this->unk_258 != 0) {
            func_80AF8DD4(this, globalCtx);
            func_80AF7E6C(this);
            func_80AF8AC8(this);
            func_8013C964(&this->actor, globalCtx, this->unk_368, 30.0f, this->unk_394, this->unk_356 & 7);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
            func_80AF7F68(this, globalCtx);
        }
    }
}

s32 EnPm_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnPm* this = THIS;

    if (limbIndex == 15) {
        func_80AF8C68(this, globalCtx);
    }
    return false;
}

void EnPm_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnPm* this = THIS;
    s32 pad;
    Vec3f sp2C;

    switch (limbIndex) {
        case 15:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->actor.focus.pos);
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            }
            if ((this->unk_356 & 0x8000) && !(gSaveContext.save.weekEventReg[90] & 4)) {
                func_80AF8890(this, gfx, 1);
            }
            break;

        case 11:
            if (this->unk_356 & 0x800) {
                func_80AF8890(this, gfx, 0);
            }
            break;

        case 8:
            if ((this->unk_258 == 9) || (this->unk_258 == 20) || (this->unk_258 == 21) || (this->unk_258 == 22)) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            } else if (this->unk_258 == 24) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            }
            func_80AF8890(this, gfx, 2);
            break;
    }
}

void EnPm_TransformLimbDraw(GlobalContext* globalCtx, s32 arg1, Actor* thisx, Gfx** gfx) {
    EnPm* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_356 & 0x200)) {
        if (this->unk_356 & 0x80) {
            phi_v1 = 1;
        } else {
            phi_v1 = 0;
        }
        phi_v0 = 1;
    } else {
        phi_v1 = 0;
        phi_v0 = 0;
    }

    if (arg1 == 15) {
        func_8013AD9C(this->unk_370 + 0x4000, this->unk_372 + this->actor.shape.rot.y + 0x4000, &this->unk_284,
                      &this->unk_290, phi_v0, phi_v1);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_284.x, this->unk_284.y, this->unk_284.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_290.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_290.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_290.z, MTXMODE_APPLY);
        Matrix_StatePush();
    }
}

void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80AFB914[] = {
        object_mm_Tex_002950,
        object_mm_Tex_002750,
    };
    EnPm* this = THIS;
    s32 pad;

    if (this->unk_258 != 0) {
        func_8012C28C(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AFB914[0]));

        POLY_OPA_DISP = SubS_DrawTransformFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnPm_OverrideLimbDraw, EnPm_PostLimbDraw,
                                               EnPm_TransformLimbDraw, &this->actor, POLY_OPA_DISP);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
