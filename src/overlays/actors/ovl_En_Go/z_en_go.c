/*
 * File: z_en_go.c
 * Overlay: ovl_En_Go
 * Description: Goron
 */

#include "z_en_go.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"
#include "objects/object_hakugin_demo/object_hakugin_demo.h"
#include "objects/object_taisou/object_taisou.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnGo*)thisx)

void EnGo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A14798(EnGo* this, GlobalContext* globalCtx);
void func_80A149B0(EnGo* this, GlobalContext* globalCtx);
void func_80A14B30(EnGo* this, GlobalContext* globalCtx);
void func_80A14E14(EnGo* this, GlobalContext* globalCtx);
void func_80A14E74(EnGo* this, GlobalContext* globalCtx);
void func_80A14EB0(EnGo* this, GlobalContext* globalCtx);
void func_80A14FC8(EnGo* this, GlobalContext* globalCtx);
void func_80A153FC(EnGo* this, GlobalContext* globalCtx);
void func_80A157C4(EnGo* this, GlobalContext* globalCtx);
void func_80A15FEC(Actor* thisx, GlobalContext* globalCtx);

static s32 D_80A16100[] = {
    0x00150800, 0x40010022, 0x00150200, 0x180E0E10, 0x0C0F0E11, 0x0C0F0E12, 0x0C0F0E13, 0x0C0F0E14, 0x0C111502,
    0x100E0E15, 0x0C100015, 0x0400110E, 0x0E160C0F, 0x0E170C0F, 0x0E180C11, 0x15041610, 0x0E0E190C, 0x10001504,
    0x000D0100, 0x050E0E31, 0x0C100E0E, 0x2F0C1001, 0x00050E0E, 0x2D0C100E, 0x0E2B0C10,
};

static s32 D_80A16164[] = {
    0x00150800, 0x7E01004D, 0x00150400, 0x180E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C12, 0x16111508,
    0x100E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C17, 0x0F0E260C, 0x180F0E27, 0x0C170F0E, 0x280C180F,
    0x0E290C17, 0x0F0E2A0C, 0x16111508, 0x100E0E1A, 0x0C170F0E, 0x1B0C180F, 0x0E1C0C0F, 0x0E1D0C0F, 0x0E1E0C17,
    0x0F0E1F0C, 0x180F0E20, 0x0C170F0E, 0x210C0F0E, 0x220C1611, 0x15081000, 0x1504000D, 0x0100050E, 0x0E320C10,
    0x0E0E300C, 0x10010005, 0x0E0E2E0C, 0x100E0E2C, 0x0C100000,
};

static s32 D_80A16208[2] = { 0xE0E520C, 0x10000000 };

static s32 D_80A16210[17] = {
    0x160400,  0x38010010, 0xE0E430C, 0xF0E440C, 0xF0E450C,  0x11188010, 0x160800,   0x1B0E0E46, 0xC0F0E47,
    0xC0F0E48, 0xC0F0E49,  0xC0F0E4A, 0xC111608, 0x11188010, 0xE0E4B0C,  0x100E0E42, 0xC100000,
};

static s32 D_80A16254[11] = {
    0x160400,   0x22010009, 0xE0E4D0C, 0xF0E4E0C,  0x10001701, 0xC0E0E,
    0x4F0C0F0E, 0x500C1117, 0x1100E0E, 0x510C100E, 0xE4C0C10,
};

static s32 D_80A16280[52] = {
    0x1001200,  0x12200008, 0xE0C8E0C,  0x11122010, 0xE0C8F0C,  0x10001240, 0x1D0E0C,   0x800C1112, 0x40001280,
    0x742500,   0xC006F00,  0x13010045, 0xF0C810C,  0x19001300, 0x1280005E, 0x25000C00, 0x59001301, 0x2F0E0C,
    0x810C0F0C, 0x820C0500, 0x1A00,     0x1A300E0C, 0x830C1209, 0x700,      0xE0C84,    0x160C1113, 0x1100E0C,
    0x840C1031, 0xE0C850C,  0x1029FFF2, 0x130200,   0xF0E0C88,  0xC0F0C89,  0xC05000A,  0xFFE3FFE3, 0xE0C860C,
    0x11128019, 0x213019,   0xFFC02900, 0x2C0E0C8C, 0xC050000,  0x50000,    0x8006400,  0x6320E0C,  0x8D0C1030,
    0x14FF9C12, 0x6003400,  0x130034,   0x700000E,  0xC870C16,  0x100E0C8B, 0xC100000,
};

static s32 D_80A16350[27] = {
    0x584000,  0x2903000E, 0x2001301, 0x180058,   0x80005119, 0x1E0059,   0x1004919, 0x160059,  0x2004119,
    0xE0059,   0x4003919,  0x2F0E0D,  0x4D0C1210, 0xE0D480C,  0xF0D490C,  0xF0D4A0C, 0x5000000, 0xF000F30,
    0xE0D4B0C, 0x15090000, 0xE0D4D0C, 0x1210310E, 0xD4C0C12,  0x100E0D4E, 0xC19FFD8, 0xE0D4F0C, 0x19FFD500,
};

static s32 D_80A163BC[4] = { 0x100060E, 0xDFE0C12, 0x100E0DFF, 0xC121000 };
static s32 D_80A163CC[4] = { 0x100060E, 0xE000C12, 0x100E0E01, 0xC121000 };
static s32 D_80A163DC[4] = { 0x100060E, 0xE020C12, 0x100E0E03, 0xC121000 };
static s32 D_80A163EC[4] = { 0x100060E, 0xE040C12, 0x100E0E05, 0xC121000 };
static s32 D_80A163FC[4] = { 0x100060E, 0xE060C12, 0x100E0E07, 0xC121000 };
static s32 D_80A1640C[2] = { 0xE023A0C, 0x12100000 };

const ActorInit En_Go_InitVars = {
    ACTOR_EN_GO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGo),
    (ActorFunc)EnGo_Init,
    (ActorFunc)EnGo_Destroy,
    (ActorFunc)EnGo_Update,
    (ActorFunc)NULL,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 0 }, 100 },
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0xF7CFFFFF, 0x02, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, 0, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
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
    { 0, 0, 0, { 0, 0, 0 } },
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
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
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

static AnimationInfoS sAnimations[] = {
    { &object_oF1d_map_Anim_011D98, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_011D98, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_oF1d_map_Anim_012DE0, 2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_oF1d_map_Anim_012DE0, 2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_oF1d_map_Anim_012DE0, -2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_oF1d_map_Anim_003E28, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_003E28, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_oF1d_map_Anim_0039D8, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_oF1d_map_Anim_003650, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_oF1d_map_Anim_0135E8, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },

    { &object_taisou_Anim_004DD4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_0016C8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_00283C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_007764, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005EE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_002C48, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_0031D8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005790, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },

    { &object_hakugin_demo_Anim_001420, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_hakugin_demo_Anim_001A4C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hakugin_demo_Anim_002704, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_hakugin_demo_Anim_003378, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

EnGoStruct* func_80A10FD0(EnGoStruct ptr[], Vec3f arg1, Vec3f arg2, Vec3f arg3, f32 arg4, f32 arg5, s32 arg6) {
    s32 i;

    for (i = 16; i < 32; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 7;
            ptr->unk_01 = (Rand_ZeroOne() * (2.0f * (arg6 / 3.0f))) + (arg6 / 3.0f);
            ptr->unk_02 = ptr->unk_01;
            ptr->unk_10 = arg1;
            ptr->unk_1C = arg2;
            ptr->unk_28 = arg3;
            ptr->unk_34 = arg4;
            ptr->unk_38 = arg5;
            break;
        }
    }

    return ptr;
}

void func_80A11144(EnGoStruct ptr[], GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    s32 flag = false;
    f32 temp;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 32; i++, ptr++) {

        if (ptr->unk_00 == 7) {
            gDPPipeSync(POLY_XLU_DISP++);

            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_oF1d_map_DL_0031A0);
                flag = true;
            }

            Matrix_StatePush();

            temp = ((f32)ptr->unk_02 / ptr->unk_01);
            temp *= 255;

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, (u8)temp);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (ptr->unk_02 + (i * 3)) * 3,
                                        (ptr->unk_02 + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

            Matrix_InsertTranslation(ptr->unk_10.x, ptr->unk_10.y, ptr->unk_10.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk_34, ptr->unk_34, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_oF1d_map_DL_003258);

            Matrix_StatePop();
            if (globalCtx->state.gfxCtx) {}
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A1143C(EnGoStruct ptr[], Vec3f arg1, Vec3f arg2, Vec3f arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    s32 i;

    for (i = 16; i < 32; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = arg7 + 4;

            ptr->unk_01 = (Rand_ZeroOne() * (2.0f * (arg6 / 3.0f))) + (arg6 / 3.0f);
            ptr->unk_02 = ptr->unk_01;

            ptr->unk_10 = arg1;
            ptr->unk_1C = arg2;
            ptr->unk_28 = arg3;
            ptr->unk_34 = arg4;
            ptr->unk_38 = arg5;
            break;
        }
    }
}

void func_80A115B4(EnGoStruct ptr[], GlobalContext* globalCtx) {
    static TexturePtr D_80A16644[] = {
        gDust8Tex, gDust7Tex, gDust6Tex, gDust5Tex, gDust4Tex, gDust3Tex, gDust2Tex, gDust1Tex,
    };
    static Color_RGBA8 D_80A16664[] = {
        { 255, 255, 255, 0 },
        { 170, 130, 90, 0 },
        { 0, 0, 0, 0 },
    };
    static Color_RGBA8 D_80A16670[] = {
        { 255, 255, 255, 0 },
        { 100, 60, 20, 0 },
        { 0, 0, 0, 0 },
    };
    s32 i;
    u8 flag = false;
    f32 temp;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 32; i++, ptr++) {
        if ((ptr->unk_00 >= 4) && (ptr->unk_00 < 7)) {
            if (!flag) {
                POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);
                gSPDisplayList(POLY_XLU_DISP++, object_oF1d_map_DL_014CF0);
                flag = true;
            }
            Matrix_StatePush();

            temp = (f32)ptr->unk_02 / ptr->unk_01;

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, D_80A16664[(s32)ptr->unk_00 - 4].r,
                            D_80A16664[(s32)ptr->unk_00 - 4].g, D_80A16664[(s32)ptr->unk_00 - 4].b, (u8)(temp * 255));
            gDPSetEnvColor(POLY_XLU_DISP++, D_80A16670[(s32)ptr->unk_00 - 4].r, D_80A16670[(s32)ptr->unk_00 - 4].g,
                           D_80A16670[(s32)ptr->unk_00 - 4].b, 0);

            Matrix_InsertTranslation(ptr->unk_10.x, ptr->unk_10.y, ptr->unk_10.z, MTXMODE_NEW);
            Matrix_Scale(ptr->unk_34, ptr->unk_34, 1.0f, MTXMODE_APPLY);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A16644[(s32)(temp * 7.0f)]));
            gSPDisplayList(POLY_XLU_DISP++, object_oF1d_map_DL_014D00);

            Matrix_StatePop();
        }
        if (globalCtx->state.gfxCtx) {}
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#ifdef NON_MATCHING
void func_80A118F8(EnGoStruct ptr[32], Vec3f arg1) {
    static u8 D_80A1667C[] = {
        3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2,
    };
    EnGoStruct* ptr2 = &ptr[16];
    s32 i;
    Vec3f spB4;
    Vec3f spA8;
    f32 temp_f20;

    for (i = 0; i < 16; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_10 = arg1;
            ptr->unk_10.y += 56.0f;

            ptr->unk_04.x = (Rand_ZeroOne() - 0.5f) * 5460.0f;
            ptr->unk_04.y = (Rand_ZeroOne() - 0.5f) * 5460.0f;
            ptr->unk_04.z = (Rand_ZeroOne() - 0.5f) * 5460.0f;

            temp_f20 = (Rand_ZeroOne() * 4.0f) + 6.0f;
            ptr->unk_28.x = Math_SinS(i * 0x1000) * temp_f20;
            ptr->unk_28.z = Math_CosS(i * 0x1000) * temp_f20;
            ptr->unk_28.y = (Rand_ZeroOne() * 3.0f) + 6.0f;

            ptr->unk_1C = gZeroVec3f;
            ptr->unk_1C.y = -0.8f;

            ptr->unk_01 = ptr->unk_02 = 1;
            ptr->unk_00 = D_80A1667C[i];

            spB4.x = ((Rand_ZeroOne() - 0.5f) * 80.0f) + ptr->unk_10.x;
            spB4.y = ((Rand_ZeroOne() - 0.5f) * 40.0f) + ptr->unk_10.y;
            spB4.z = ((Rand_ZeroOne() - 0.5f) * 80.0f) + ptr->unk_10.z;

            spA8 = gZeroVec3f;
            spA8.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

            func_80A1143C(ptr2, spB4, gZeroVec3f, spA8, 0.6f, 0.2f, 16, 0);
        }
    }
}
#else
static u8 D_80A1667C[] = {
    3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2,
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A118F8.s")
#endif

void func_80A11BF8(EnGoStruct ptr[], f32 arg1) {
    f32 test;
    f32 test2;
    f32 x;
    f32 z;

    ptr->unk_10.x += ptr->unk_28.x;
    ptr->unk_10.y += ptr->unk_28.y;
    ptr->unk_10.z += ptr->unk_28.z;

    ptr->unk_28.y += ptr->unk_1C.y;
    ptr->unk_34 += ptr->unk_38;

    if (ptr->unk_10.y < arg1) {
        ptr->unk_10.y = arg1;

        ptr->unk_00 = 4;
        ptr->unk_01 = (Rand_ZeroOne() * 8.0f) + 4.0f;
        ptr->unk_02 = ptr->unk_01;

        ptr->unk_28 = gZeroVec3f;
        ptr->unk_28.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        ptr->unk_34 = 0.4f;
        ptr->unk_38 = 0.1f;
        return;
    }

    if (ptr->unk_28.x != 0.0f) {
        x = ptr->unk_28.x / fabsf(ptr->unk_28.x);
        x *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&ptr->unk_28.x, x, (sREG(14) + 40) * 0.01f);
    }

    if (ptr->unk_28.z != 0.0f) {
        z = ptr->unk_28.z / fabsf(ptr->unk_28.z);
        z *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&ptr->unk_28.z, z, (sREG(14) + 40) * 0.01f);
    }

    ptr->unk_0A.x += ptr->unk_04.x;
    ptr->unk_0A.y += ptr->unk_04.y;
    ptr->unk_0A.z += ptr->unk_04.z;
}

#ifdef NON_MATCHING
void func_80A11EC0(EnGoStruct ptr[], GlobalContext* globalCtx, Gfx arg2[], Gfx arg3[], u8 arg4) {
    s32 i;
    u8 flag = false;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    for (i = 0; i < 16; i++, ptr++) {
        if (ptr->unk_00 == arg4) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, arg2);
                flag = true;
            }

            Matrix_StatePush();
            Matrix_InsertTranslation(ptr->unk_10.x, ptr->unk_10.y, ptr->unk_10.z, MTXMODE_NEW);
            Matrix_Scale(0.08f, 0.08f, 0.08f, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(ptr->unk_0A.z, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(ptr->unk_0A.x, MTXMODE_APPLY);
            Matrix_RotateY(ptr->unk_0A.y, MTXMODE_APPLY);

            if (1) {
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, arg3);
            }

            Matrix_StatePop();
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A11EC0.s")
#endif

void func_80A1203C(EnGo* this) {
    EnGoStruct* ptr = this->unk_3F8;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++, ptr++) {
        if (ptr->unk_00 != 0) {
            if (ptr->unk_02 == 0) {
                ptr->unk_00 = 0;
            } else if ((ptr->unk_00 > 0) && (ptr->unk_00 < 4)) {
                func_80A11BF8(ptr, this->actor.world.pos.y);
            } else {
                ptr->unk_10.x += ptr->unk_28.x;
                ptr->unk_10.y += ptr->unk_28.y;
                ptr->unk_10.z += ptr->unk_28.z;

                ptr->unk_28.x += ptr->unk_1C.x;
                ptr->unk_28.y += ptr->unk_1C.y;
                ptr->unk_28.z += ptr->unk_1C.z;

                ptr->unk_34 += ptr->unk_38;
                ptr->unk_02--;
            }
        }
    }
}

void func_80A1213C(EnGo* this, GlobalContext* globalCtx) {
    func_80A11EC0(this->unk_3F8, globalCtx, object_oF1d_map_DL_0003D0, object_oF1d_map_DL_000458, 1);
    func_80A11EC0(this->unk_3F8, globalCtx, object_oF1d_map_DL_0008C0, object_oF1d_map_DL_000948, 2);
    func_80A11EC0(this->unk_3F8, globalCtx, object_oF1d_map_DL_000D50, object_oF1d_map_DL_000DD8, 3);
    func_80A11144(this->unk_3F8, globalCtx);
    func_80A115B4(this->unk_3F8, globalCtx);
}

s32 func_80A121F4(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((player->transformation == PLAYER_FORM_GORON) && (player->stateFlags3 & 0x2000000)) {
        return false;
    }
    return true;
}

s32 func_80A1222C(EnGo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 ret = false;

    if (((player->transformation == PLAYER_FORM_GORON) && (globalCtx->msgCtx.ocarinaMode == 3) &&
         (globalCtx->msgCtx.unk1202E == 1) && (this->unk_3EC == 0) && (this->actor.xzDistToPlayer < 400.0f)) ||
        (!(gSaveContext.save.weekEventReg[22] & 4) && (globalCtx->sceneNum == SCENE_16GORON_HOUSE) &&
         (gSaveContext.sceneSetupIndex == 0) && (this->unk_3EC == 0) && (globalCtx->csCtx.currentCsIndex == 1))) {
        ret = true;
    }
    return ret;
}

s32 func_80A122EC(EnGo* this) {
    static Vec3f D_80A1668C = { 0.0f, 100.0f, 160.0f };
    s32 pad;
    f32 sp20 = 58.0f;

    if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A1668C,
                                      &this->actor.focus.pos);
    } else {
        if ((this->unk_390 & 0x200) || (this->unk_390 & 0x100)) {
            sp20 = this->actor.shape.yOffset;
        }
        Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
        this->actor.focus.pos.y += sp20;
    }

    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
    return false;
}

void func_80A123A0(EnGo* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = sp2C.x;
    this->colliderSphere.dim.worldSphere.center.y = sp2C.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = sp2C.z;

    this->colliderSphere.dim.modelSphere.radius = 48;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    if (func_80A121F4(globalCtx)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
}

void func_80A124A0(EnGo* this, GlobalContext* globalCtx) {
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
}

void func_80A124FC(EnGo* this, GlobalContext* globalCtx) {
    Vec3f sp1C;

    Math_Vec3f_Copy(&sp1C, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = sp1C.x;
    this->colliderSphere.dim.worldSphere.center.y = sp1C.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = sp1C.z;

    this->colliderSphere.dim.modelSphere.radius = 20;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
}

void func_80A125BC(EnGo* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);

    this->colliderCylinder.dim.radius = 46;
    this->colliderCylinder.dim.height = 78;

    if (this->unk_3C6 == 0) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
}

void func_80A12660(EnGo* this, GlobalContext* globalCtx) {
    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);
    this->colliderCylinder.dim.radius = 24;
    this->colliderCylinder.dim.height = 62;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
}

void func_80A126BC(EnGo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags2 & 0x4000)) {
        if (this->unk_3C6 != 0) {
            this->unk_3C6--;
        }
    }

    if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
        func_80A124A0(this, globalCtx);
    } else if (this->unk_390 & 0x100) {
        func_80A123A0(this, globalCtx);
    } else if (this->unk_390 & 0x200) {
        func_80A124FC(this, globalCtx);
    } else if (this->unk_390 & 0x400) {
        func_80A125BC(this, globalCtx);
    } else {
        func_80A12660(this, globalCtx);
    }
}

s32 func_80A12774(EnGo* this, GlobalContext* globalCtx) {
    if (!(this->unk_390 & 7) || !Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        return false;
    }

    if ((ENGO_GET_F(&this->actor) != ENGO_F_8) && (ENGO_GET_F(&this->actor) != ENGO_F_1)) {
        if (!(this->unk_390 & 0x200)) {
            this->unk_390 |= 8;
        }
    }

    if ((ENGO_GET_F(&this->actor) == ENGO_F_5) || (ENGO_GET_F(&this->actor) == ENGO_F_6) ||
        (ENGO_GET_F(&this->actor) == ENGO_F_7)) {
        this->unk_3BC = 0;
        this->unk_3BE = 0;
        this->unk_390 |= 0x20;
    }

    SubS_UpdateFlags(&this->unk_390, 0, 7);
    this->unk_3C0 = 0;
    this->unk_3C4 = 0;
    this->unk_18C = this->actionFunc;
    this->actionFunc = func_80A157C4;
    return true;
}

s32 func_80A12868(EnGo* this, GlobalContext* globalCtx) {
    this->unk_390 &= ~0x800;
    this->unk_390 &= ~0x1000;
    this->unk_390 &= ~0x2000;

    if ((this->colliderCylinder.base.atFlags & AT_HIT) || (this->colliderSphere.base.atFlags & AT_HIT)) {
        this->colliderCylinder.base.atFlags &= ~AT_HIT;
        this->colliderSphere.base.atFlags &= ~AT_HIT;
        this->unk_390 |= 0x800;
        this->unk_3C6 = 0x28;
    }

    if ((this->colliderCylinder.base.acFlags & AC_HIT) || (this->colliderSphere.base.acFlags & AC_HIT)) {
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        this->colliderSphere.base.acFlags &= ~AC_HIT;
        this->unk_390 |= 0x1000;
    }

    if ((this->colliderCylinder.base.ocFlags1 & OC1_HIT) || (this->colliderSphere.base.ocFlags1 & OC1_HIT)) {
        this->colliderCylinder.base.ocFlags1 &= ~OC1_HIT;
        this->colliderSphere.base.ocFlags1 &= ~OC1_HIT;
        this->unk_390 |= 0x2000;
    }

    return false;
}

s32 func_80A12954(EnGo* this, GlobalContext* globalCtx) {
    if ((ENGO_GET_F(&this->actor) == ENGO_F_4) && (globalCtx->csCtx.state != 0) && (this->actor.draw != NULL) &&
        (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA2) && (gSaveContext.sceneSetupIndex == 1) &&
        (globalCtx->csCtx.currentCsIndex == 0)) {
        if (this->unk_3F0 == 0) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_394 = 255;
            this->unk_3F0 = 1;
            this->unk_18C = this->actionFunc;
        }
        SubS_UpdateFlags(&this->unk_390, 0, 7);
        this->actionFunc = func_80A14FC8;
    } else if (this->unk_3F0 != 0) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->unk_394 = 255;
        this->unk_3F0 = 0;
        SubS_UpdateFlags(&this->unk_390, 3, 7);
        this->actionFunc = this->unk_18C;
    }

    return false;
}

s32 func_80A12A64(EnGo* this, GlobalContext* globalCtx) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = 0;

    if ((this->unk_3DC >= 18) && (this->unk_289 >= 0)) {
        objIdx2 = this->unk_289;
    } else if ((this->unk_3DC >= 10) && (this->unk_288 >= 0)) {
        objIdx2 = this->unk_288;
    } else if (this->unk_3DC < 10) {
        objIdx2 = this->actor.objBankIndex;
    }

    if (objIdx2 >= 0) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[objIdx2].segment);
        this->skelAnime.playSpeed = this->unk_398;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[objIdx].segment);
    }

    return ret;
}

s32 func_80A12B78(EnGo* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        if (this->unk_3DC == 4) {
            if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_CIRCLE);
            }

            if (Animation_OnFrame(&this->skelAnime, 22.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SIT_IMT);
            }
        } else if ((this->unk_3DC == 2) || (this->unk_3DC == 3)) {
            if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_CIRCLE_OFF);
            }

            if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_STAND_IMT);
            }
        }
    }
    return 0;
}

s32 func_80A12C48(EnGo* this, GlobalContext* globalCtx, s32 arg2) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = false;

    if ((arg2 >= 18) && (this->unk_289 >= 0)) {
        objIdx2 = this->unk_289;
    } else if ((arg2 >= 10) && (this->unk_288 >= 0)) {
        objIdx2 = this->unk_288;
    } else if (arg2 < 10) {
        objIdx2 = this->actor.objBankIndex;
    }

    if (objIdx2 >= 0) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[objIdx2].segment);
        this->unk_3DC = arg2;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg2);
        this->unk_398 = this->skelAnime.playSpeed;
        gSegments[6] = PHYSICAL_TO_VIRTUAL2(globalCtx->objectCtx.status[objIdx].segment);
    }

    return ret;
}

void func_80A12D6C(EnGo* this) {
    if ((this->unk_390 & 0x20) && (DECR(this->unk_3BC) == 0)) {
        this->unk_3BE++;
        if (this->unk_3BE >= 4) {
            this->unk_3BC = Rand_S16Offset(30, 30);
            this->unk_3BE = 0;
        }
    }
}

void func_80A12DF4(EnGo* this, GlobalContext* globalCtx) {
    if (this->unk_3D4 == 0) {
        func_80A12C48(this, globalCtx, 9);
        this->unk_3D4++;
    } else if ((this->unk_3D4 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A12C48(this, globalCtx, 6);
        this->unk_3D4++;
    }
}

s32 func_80A12E80(EnGo* this, GlobalContext* globalCtx) {
    u16 temp = globalCtx->msgCtx.currentTextId;
    Player* player = GET_PLAYER(globalCtx);

    if (ENGO_GET_F(&this->actor) != ENGO_F_4) {
        return false;
    }

    if (player->stateFlags1 & 0x40) {
        if (this->unk_392 != temp) {
            switch (temp) {
                case 0xE1A:
                    this->unk_390 |= 8;
                    this->unk_38C = this->actor.child;
                    break;

                case 0xE1D:
                case 0xE25:
                    if (ENGO_GET_70(&this->actor) == ENGO_70_1) {
                        this->unk_38C = &GET_PLAYER(globalCtx)->actor;
                    }
                    break;

                case 0xE27:
                    if (ENGO_GET_70(&this->actor) == ENGO_70_1) {
                        this->unk_38C = this->actor.child;
                    }

                case 0xE16:
                case 0xE1E:
                    this->unk_190 = func_80A12DF4;
                    break;

                case 0xE1F:
                    if (ENGO_GET_70(&this->actor) == ENGO_70_0) {
                        this->unk_38C = &GET_PLAYER(globalCtx)->actor;
                    }
                    break;
            }
        }
        this->unk_3F4 = 1;
        this->unk_392 = temp;
    } else if (this->unk_3F4 != 0) {
        this->unk_3F4 = 0;
        this->unk_190 = NULL;
        this->unk_392 = 0;
        func_80A12C48(this, globalCtx, 5);
        this->unk_390 &= ~8;
    }

    if (this->unk_190 != NULL) {
        this->unk_190(this, globalCtx);
    }

    return false;
}

s32 func_80A12FE8(EnGo* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;

    Math_Vec3f_Copy(&sp40, &this->unk_38C->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    sp32 = Math_Vec3f_Yaw(&sp34, &sp40);

    Math_ApproachS(&this->unk_3B2, (sp32 - this->unk_3B6) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_3B2 = CLAMP(this->unk_3B2, -0x1FFE, 0x1FFE);

    Math_ApproachS(&this->unk_3B6, (sp32 - this->unk_3B2) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_3B6 = CLAMP(this->unk_3B6, -0x1C70, 0x1C70);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_38C->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_38C)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_38C->focus.pos);
    }

    Math_ApproachS(&this->unk_3B0, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_3B4, 4, 0x2AA8);
    this->unk_3B0 = CLAMP(this->unk_3B0, -0x1554, 0x1554);

    Math_ApproachS(&this->unk_3B4, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_3B0, 4, 0x2AA8);
    this->unk_3B4 = CLAMP(this->unk_3B4, -0xE38, 0xE38);

    return false;
}

s32 func_80A131F8(EnGo* this, GlobalContext* globalCtx) {
    if (this->unk_3F4 == 0) {
        this->unk_38C = &GET_PLAYER(globalCtx)->actor;
    }

    func_80A12E80(this, globalCtx);

    if (this->unk_390 & 8) {
        this->unk_390 &= ~0x40;
        this->unk_390 |= 0x10;
        func_80A12FE8(this, globalCtx);
    } else if (this->unk_390 & 0x10) {
        this->unk_390 &= ~0x10;
        this->unk_3B0 = 0;
        this->unk_3B2 = 0;
        this->unk_3B4 = 0;
        this->unk_3B6 = 0;
        this->unk_3BA = 0x14;
    } else if (DECR(this->unk_3BA) == 0) {
        this->unk_390 |= 0x40;
        this->unk_3BA = 0x14;
    }

    return true;
}

void func_80A132C8(EnGo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 temp_v1 = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    if ((fabsf(this->actor.playerHeightRel) > 20.0f) || (this->actor.xzDistToPlayer > 300.0f)) {
        SubS_UpdateFlags(&this->unk_390, 3, 7);
    } else if ((player->transformation != PLAYER_FORM_GORON) || (ABS_ALT(temp_v1) >= 0x1C70) ||
               (gSaveContext.save.weekEventReg[21] & 4) || (gSaveContext.save.weekEventReg[21] & 8)) {
        SubS_UpdateFlags(&this->unk_390, 3, 7);
    } else {
        SubS_UpdateFlags(&this->unk_390, 4, 7);
    }
}

void func_80A133A8(EnGo* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.weekEventReg[21] & 8) {
        SubS_UpdateFlags(&this->unk_390, 3, 7);
    } else {
        SubS_UpdateFlags(&this->unk_390, 4, 7);
    }
}

Actor* func_80A13400(EnGo* this, GlobalContext* globalCtx) {
    Actor* actor;
    Actor* retActor = NULL;

    while (true) {
        actor = SubS_FindActor(globalCtx, retActor, ACTORCAT_NPC, ACTOR_EN_GO);
        retActor = actor;

        if ((actor != NULL) && ((EnGo*)actor != this) && (ENGO_GET_F(actor) == ENGO_F_4) &&
            (ENGO_GET_70(actor) == ENGO_70_0)) {
            return retActor;
        }

        if (actor == NULL) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            break;
        }
        retActor = actor;
    }

    return NULL;
}

void func_80A134B0(EnGo* this, GlobalContext* globalCtx, s32 arg2) {
    if ((gSaveContext.save.weekEventReg[18] & 0x80) || (globalCtx->actorCtx.unk5 & 1) || arg2) {
        this->colliderSphere.dim.modelSphere.radius = 300;
    } else {
        this->colliderSphere.dim.modelSphere.radius = 380;
    }
}

s32 func_80A134F4(EnGo* this, s16 arg1) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        return true;
    }
    ActorCutscene_SetIntentToPlay(arg1);
    return false;
}

s32 func_80A13564(EnGo* this, f32 arg1, f32 arg2, s32 arg3) {
    s32 pad;
    f32 temp_f0 = 1.0f;
    f32 temp_f14 = this->actor.velocity.y + this->actor.gravity;
    s32 ret;

    if (this->actor.bgCheckFlags & 2) {
        ret = true;
    } else {
        if (temp_f14 > 0.0f) {
            temp_f0 = temp_f14 / arg1;
            this->actor.shape.rot.x += (s16)(9100.0f * temp_f0);
            this->unk_3AE = 0;
        } else if ((s32)this->actor.velocity.y == 0) {
            if (arg3 >= this->unk_3AE) {
                temp_f0 = (f32)this->unk_3AE / arg3;
            } else {
                this->actor.gravity = -6.0f;
            }
            this->unk_3AE++;
        } else if (this->unk_3AE == 0) {
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
            temp_f0 = temp_f14 / arg1;
        }
        ret = false;
    }

    this->unk_3A8 = (1.0f - temp_f0) * arg2;
    this->actor.scale.x = this->unk_3A4 - this->unk_3A8;
    this->actor.scale.y = this->unk_3A4 + this->unk_3A8;

    if (this->actor.scale.y < this->actor.scale.x) {
        this->actor.scale.z = this->actor.scale.x;
    } else {
        this->actor.scale.z = this->actor.scale.y;
    }
    return ret;
}

void func_80A136B8(GlobalContext* globalCtx, s16 arg1, s16 arg2, s16 arg3) {
    s16 sp26 = Quake_Add(Play_GetCamera(globalCtx, CAM_ID_MAIN), 3);

    Quake_SetCountdown(sp26, arg3);
    Quake_SetSpeed(sp26, arg1);
    Quake_SetQuakeValues(sp26, arg2, 0, 0, 0);
}

void func_80A13728(EnGo* this, GlobalContext* globalCtx) {
    func_80A136B8(globalCtx, 0x6C77, 7, 20);
    globalCtx->actorCtx.unk2 = 4;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 0);
    EffectSsBlast_SpawnWhiteShockwave(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
}

void func_80A137C0(EnGo* this, GlobalContext* globalCtx, f32 arg2, f32 arg3) {
    u32 frames1;
    u32 frames2;

    if (this->unk_390 & 0x400) {
        Matrix_StatePush();

        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C2DC(globalCtx->state.gfxCtx);

        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_Scale(arg2 * 0.7f, arg2 * 0.8f, arg2, MTXMODE_APPLY);
        func_800B8118(&this->actor, globalCtx, 0);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        frames1 = globalCtx->gameplayFrames % 256;
        frames2 = (globalCtx->gameplayFrames * 2) % 256;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, frames1, 0x20, 0x10, 1, 0, frames2, 0x40, 0x20));
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, (u8)arg3);
        gSPDisplayList(POLY_XLU_DISP++, &gameplay_keep_DL_050D10);

        CLOSE_DISPS(globalCtx->state.gfxCtx);

        Matrix_StatePop();
    }
}

void func_80A139E4(EnGo* this) {
    static Vec3f D_80A16698 = { 0.0f, 0.06f, 0.0f };
    Vec3f sp54;
    Vec3f sp48;
    s16 sp46 = Rand_ZeroOne() * 360.0f * 182.0f;

    Math_Vec3f_Copy(&sp54, &gZeroVec3f);
    sp54.z = 28.0f;
    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, sp46, &sp54, &sp48);
    sp48.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
    sp48.y += this->actor.floorHeight;
    func_80A10FD0(&this->unk_3F8[16], sp48, D_80A16698, gZeroVec3f, 0.01f, 0.002f, 16);
}

s32 func_80A13B1C(EnGo* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s32 ret = false;

    switch (this->unk_3C0) {
        case 0:
            this->unk_3B8 = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            if (func_80A134F4(this, this->unk_3B8)) {
                this->unk_3C4 = 1;
                this->unk_3C0 = 1;
            } else {
                break;
            }

        case 1:
            if (ActorCutscene_GetCurrentIndex() != this->unk_3B8) {
                this->unk_3B8 = ActorCutscene_GetAdditionalCutscene(this->unk_3B8);
                this->unk_3C0 = 2;
            } else {
                break;
            }

        case 2:
            if (func_80A134F4(this, this->unk_3B8)) {
                this->unk_3C0 = 3;
            } else {
                break;
            }

        case 3:
            if (ActorCutscene_GetCanPlayNext(0x7C)) {
                ActorCutscene_StartAndSetUnkLinkFields(0x7C, NULL);
                this->unk_3C0 = 4;
            } else if (ActorCutscene_GetCurrentIndex() == this->unk_3B8) {
                ActorCutscene_SetIntentToPlay(0x7C);
            }
    }

    switch (this->unk_3C4) {
        case 1:
            func_80A12C48(this, globalCtx, 4);
            this->unk_390 |= 0x4000;
            this->unk_3C4++;
            break;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->unk_390 &= ~0x4000;
                this->unk_390 &= ~0x80;
                this->unk_390 |= 0x200;
                this->unk_3C4++;
                this->unk_3C2 = 0;
                this->actor.shape.yOffset = 14.0f;
            }
            break;

        case 3:
            this->unk_3C2++;
            if (this->unk_3C2 >= 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_JUMP);
                this->actor.velocity.y = 10.0f;
                this->actor.gravity = -1.0f;
                this->unk_3C4++;
            }
            break;

        case 4:
            if (func_80A13564(this, 10.0f, 0.004f, 6)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_LAND_BIG);
                func_80A13728(this, globalCtx);
                this->unk_3C4++;
                this->unk_3C2 = 0;
                gSaveContext.save.weekEventReg[88] |= 0x40;
            }
            break;

        case 5:
            this->unk_3C2++;
            if (this->unk_3C2 >= 10) {
                func_80A12C48(this, globalCtx, 5);
                this->actor.shape.rot.x = 0;
                this->unk_390 &= ~0x200;
                this->unk_390 |= 0x80;
                this->unk_3C4++;
            }
            break;

        case 6:
            this->unk_3C0++;
            if (this->unk_3C0 >= 65) {
                switch (player->transformation) {
                    case 4:
                        gSaveContext.save.weekEventReg[88] |= 0x80;
                        break;

                    case 1:
                        gSaveContext.save.weekEventReg[89] |= 4;
                        break;

                    case 2:
                        gSaveContext.save.weekEventReg[89] |= 2;
                        break;

                    case 3:
                        gSaveContext.save.weekEventReg[89] |= 1;
                        break;
                }
                ret = true;
            }
            break;
    }

    Actor_MoveWithGravity(&this->actor);
    return ret;
}

s32 func_80A13E80(EnGo* this, GlobalContext* globalCtx) {
    static Vec3f D_80A166A4 = { 0.0f, 200.0f, 280.0f };
    s32 pad;
    Vec3f sp48;
    s32 ret = false;

    switch (this->unk_3C0) {
        case 0:
            this->unk_3B8 = this->actor.cutscene;
            if (func_80A134F4(this, this->unk_3B8)) {
                this->unk_3C0++;
            }
            break;

        case 1:
            func_80A12C48(this, globalCtx, 7);
            this->unk_3C0++;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, 16.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_HAND_HIT);
            }

            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80A12C48(this, globalCtx, 1);
                Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A166A4, &sp48);
                gSaveContext.powderKegTimer = 2400;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, sp48.x, sp48.y, sp48.z, 1, 0, 0, 0);
                func_80A134B0(this, globalCtx, 1);
                this->unk_3C2 = 0;
                this->unk_3C0++;
            }
            break;

        case 3:
            if (this->unk_3C2 >= 60) {
                ActorCutscene_Stop(this->unk_3B8);
                this->unk_3C2 = 0;
                this->unk_3C0 = 0;
                ret = true;
            } else {
                this->unk_3C2++;
            }
            break;
    }

    return ret;
}

void func_80A14018(EnGo* this, GlobalContext* globalCtx) {
    static Vec3f D_80A166B0 = { 0.0f, 0.0f, 40.0f };
    static s32 D_80A166BC[] = { 11, 10, 12, 13, 14, 17 };
    Vec3f sp2C;
    s32 phi_v0 = ENGO_GET_70(&this->actor) % 6;

    if (phi_v0 < 4) {
        phi_v0 = ((gSaveContext.eventInf[2] & 0xF) + phi_v0) % 4;
    }

    func_80A12C48(this, globalCtx, D_80A166BC[phi_v0]);

    if (this->unk_3DC == 14) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A166B0, &sp2C);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp2C);
    }
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->unk_3A4);
    this->unk_3EC = 0;
    this->unk_390 = 0;
    this->unk_390 |= (0x40 | 0x20);
    this->actor.gravity = 0.0f;
}

void func_80A14104(EnGo* this, GlobalContext* globalCtx) {
    static s32 D_80A166D4[] = { 15, 16 };
    s16 temp;

    func_80A12C48(this, globalCtx, D_80A166D4[ENGO_GET_70(&this->actor) % 2]);
    temp = Rand_ZeroOne() * this->skelAnime.endFrame;
    this->skelAnime.curFrame = temp;
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->unk_3A4);
    this->unk_3EC = 0;
    this->unk_390 = 0;
    this->unk_390 |= 0x40;
    this->unk_390 |= 0x20;
    this->actor.gravity = 0.0f;
}

void func_80A141D4(EnGo* this, GlobalContext* globalCtx) {
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit1);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->unk_3DC = -1;
    func_80A12C48(this, globalCtx, 5);
    this->unk_3EC = 0;
    this->unk_39C = (this->unk_3A4 / 0.01f) * 0.9f;
    this->unk_3BE = 2;
    this->unk_390 = 0;
    this->unk_390 |= 0x40;
    this->unk_390 |= 0x400;
    this->unk_3A0 = 100.0f;
}

void func_80A1428C(EnGo* this, GlobalContext* globalCtx) {
    s16 temp;
    Vec3f sp30;
    Vec3f sp24;

    Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
    if (this->unk_284 != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_2000000;
        SubS_CopyPointFromPathCheckBounds(this->unk_284, 0, &sp24);
        temp = Math_Vec3f_Yaw(&sp30, &sp24);
        this->actor.shape.rot.y = temp;
        this->actor.world.rot.y = temp;
    }
    this->unk_390 = 0;
    this->unk_390 |= 0x100;
    this->actor.shape.yOffset = 46.0f;
    this->actor.gravity = -1.0f;
}

void func_80A14324(EnGo* this, GlobalContext* globalCtx) {
    func_80A12C48(this, globalCtx, 8);
    Actor_SetScale(&this->actor, this->unk_3A4);
    this->unk_390 = 0;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->unk_390, 3, 7);
    this->unk_3EC = 0;
    this->unk_390 |= 0x40;
    this->unk_3BC = 0;
    this->unk_3BE = 4;
    this->unk_39C = 0.0f;
    this->unk_3A0 = 0.0f;
}

void func_80A143A8(EnGo* this, GlobalContext* globalCtx) {
    func_80A12C48(this, globalCtx, 5);
    Actor_SetScale(&this->actor, this->unk_3A4);
    this->unk_390 = 0;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->unk_390, 3, 7);
    this->unk_3EC = 0;
    this->unk_390 |= 0x40;
    this->unk_390 |= 0x20;
    this->unk_3BC = 0;
    this->unk_3BE = 0;
    this->unk_39C = 0.0f;
    this->unk_3A0 = 0.0f;
}

void func_80A14430(EnGo* this, GlobalContext* globalCtx) {
    if (((gSaveContext.save.entranceIndex == 0xD000) || (gSaveContext.save.entranceIndex == 0xD020)) &&
        (gSaveContext.save.weekEventReg[33] & 0x80)) {
        func_80A14018(this, globalCtx);
        this->actionFunc = func_80A149B0;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80A1449C(EnGo* this, GlobalContext* globalCtx) {
    if ((gSaveContext.save.entranceIndex == 0xD010) || (gSaveContext.save.entranceIndex == 0x1C00)) {
        func_80A14104(this, globalCtx);
        this->actionFunc = func_80A149B0;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80A144F4(EnGo* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.day >= 2) {
        this->unk_284 = SubS_GetDayDependentPath(globalCtx, ENGO_GET_7F80(&this->actor), 0xFF, &this->unk_3E4);
        if (this->unk_284 != NULL) {
            this->unk_3E4 = 1;
        }
        func_80A1428C(this, globalCtx);
        this->actionFunc = func_80A153FC;
        this->unk_3D8 = func_80A13B1C;
    } else {
        func_80A143A8(this, globalCtx);
        this->actionFunc = func_80A149B0;
        this->unk_3D8 = func_80A13B1C;
    }
}

void func_80A145AC(EnGo* this, GlobalContext* globalCtx) {
    if ((ENGO_GET_70(&this->actor) == ENGO_70_1) &&
        (((globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA2) && (gSaveContext.sceneSetupIndex == 1) &&
          (globalCtx->csCtx.currentCsIndex == 0)) ||
         !(gSaveContext.save.weekEventReg[21] & 8))) {
        this->actor.child = func_80A13400(this, globalCtx);
        this->actor.child->child = &this->actor;
        func_80A141D4(this, globalCtx);
        this->actionFunc = func_80A14E14;
    } else {
        func_80A143A8(this, globalCtx);
        this->actionFunc = func_80A149B0;
    }
}

void func_80A14668(EnGo* this, GlobalContext* globalCtx) {
    if (!(gSaveContext.save.weekEventReg[22] & 4)) {
        func_80A14324(this, globalCtx);
        this->actionFunc = func_80A149B0;
    } else {
        func_80A143A8(this, globalCtx);
        this->actionFunc = func_80A149B0;
    }
}

void func_80A146CC(EnGo* this, GlobalContext* globalCtx) {
    func_80A134B0(this, globalCtx, 0);
    func_80A12C48(this, globalCtx, 0);
    this->unk_3A4 *= 5.0f;
    Actor_SetScale(&this->actor, this->unk_3A4);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.targetMode = 3;
    this->unk_390 = 0;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->unk_390, 3, 7);
    this->unk_390 |= 0x40;
    this->unk_390 |= 0x20;
    this->unk_3D8 = func_80A13E80;
    this->actionFunc = func_80A149B0;
}

void func_80A14798(EnGo* this, GlobalContext* globalCtx) {
    EffectTireMarkInit sp38 = {
        0,
        62,
        { 0, 0, 15, 100 },
    };

    if ((this->unk_288 < 0) || SubS_IsObjectLoaded(this->unk_288, globalCtx) || (this->unk_289 < 0) ||
        SubS_IsObjectLoaded(this->unk_289, globalCtx)) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_oF1d_map_Skel_011AC8, NULL, this->jointTable,
                           this->morphTable, 18);

        this->unk_3DC = -1;
        func_80A12C48(this, globalCtx, 2);
        this->actor.draw = func_80A15FEC;

        Collider_InitAndSetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
        Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit2);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        Effect_Add(globalCtx, &this->unk_3E8, EFFECT_TIRE_MARK, 0, 0, &sp38);

        this->actor.targetMode = 1;
        this->unk_3A4 = 0.01f;
        this->unk_3D8 = NULL;

        switch (ENGO_GET_F(&this->actor)) {
            case ENGO_F_1:
                func_80A14430(this, globalCtx);
                break;

            case ENGO_F_2:
                func_80A1449C(this, globalCtx);
                break;

            case ENGO_F_3:
                func_80A144F4(this, globalCtx);
                break;

            case ENGO_F_4:
                func_80A145AC(this, globalCtx);
                break;

            case ENGO_F_5:
            case ENGO_F_6:
            case ENGO_F_7:
                func_80A14668(this, globalCtx);
                break;

            case ENGO_F_8:
                func_80A146CC(this, globalCtx);
                break;

            default:
                Actor_MarkForDeath(&this->actor);
                break;
        }
    }
}

void func_80A149B0(EnGo* this, GlobalContext* globalCtx) {
    s16 sp26 = this->actor.world.rot.y;

    if ((ENGO_GET_F(&this->actor) == ENGO_F_2) && (gSaveContext.save.entranceIndex == 0xD010)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_CHEER - SFX_FLAG);
    } else if (ENGO_GET_F(&this->actor) != ENGO_F_8) {
        if (func_80A1222C(this, globalCtx)) {
            SubS_UpdateFlags(&this->unk_390, 0, 7);
            this->unk_3EC = 1;
            this->actionFunc = func_80A14B30;
        } else if (ENGO_GET_F(&this->actor) == ENGO_F_4) {
            switch (ENGO_GET_70(&this->actor)) {
                case ENGO_70_0:
                    func_80A132C8(this, globalCtx);
                    break;

                case ENGO_70_1:
                    func_80A133A8(this, globalCtx);
                    break;
            }
        } else if (ENGO_GET_F(&this->actor) == ENGO_F_1) {
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3FFC) {
                SubS_UpdateFlags(&this->unk_390, 3, 7);
            } else {
                SubS_UpdateFlags(&this->unk_390, 0, 7);
            }
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, sp26, 4, 0x2AA8);
}

void func_80A14B30(EnGo* this, GlobalContext* globalCtx) {
    s16 sp26 = this->actor.world.rot.y;
    u16 sfxId;

    if (func_80A1222C(this, globalCtx)) {
        this->unk_3EC = 1;
    }

    if (this->unk_390 & 0x4000) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->unk_390 &= ~0x4000;
            this->unk_390 |= 0x200;
            if (this->unk_3EC != 0) {
                this->unk_3AE = 0;
            }
            this->actor.shape.yOffset = 14.0f;
        }
    } else if (this->unk_390 & 0x8000) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->unk_390 |= 0x80;
            this->unk_390 &= ~0x8000;
        }
    } else if (this->unk_390 & 0x200) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.playerHeightRel < 20.0f) && (this->unk_3EC == 0)) {
            func_80A12C48(this, globalCtx, 3);
            this->unk_390 &= ~0x80;
            this->unk_390 &= ~0x200;
            this->unk_390 |= 0x8000;
            this->actor.shape.yOffset = 0.0f;
        } else if ((this->unk_3EC != 0) && (gSaveContext.save.weekEventReg[22] & 4)) {
            this->actor.scale.x = this->unk_3A4 - (Math_SinS(this->unk_3AE) * 0.001f);
            this->actor.scale.y = (Math_SinS(this->unk_3AE) * 0.001f) + this->unk_3A4;
            this->actor.scale.z = (Math_SinS(this->unk_3AE) * 0.001f) + this->unk_3A4;
            if (this->unk_3AE == 0) {
                this->unk_3EC = -this->unk_3EC;
                if (this->unk_3EC > 0) {
                    sfxId = NA_SE_EN_GOLON_SNORE1;
                } else {
                    sfxId = NA_SE_EN_GOLON_SNORE2;
                }
                Actor_PlaySfxAtPos(&this->actor, sfxId);
            }
            this->unk_3AE += 0x400;
            this->actor.shape.yOffset = (this->actor.scale.y / this->unk_3A4) * 14.0f;
            SubS_UpdateFlags(&this->unk_390, 3, 7);
        }
    } else if ((this->actor.xzDistToPlayer >= 240.0f) || (this->actor.playerHeightRel >= 20.0f) ||
               (this->unk_3EC != 0)) {
        func_80A12C48(this, globalCtx, 4);
        this->unk_390 &= ~0x80;
        this->unk_390 &= ~0x200;
        this->unk_390 |= 0x4000;
        this->actor.shape.yOffset = 0.0f;
    }

    SubS_FillLimbRotTables(globalCtx, this->unk_3CE, this->unk_3C8, ARRAY_COUNT(this->unk_3CE));
    Math_ApproachS(&this->actor.shape.rot.y, sp26, 4, 0x2AA8);
}

void func_80A14E14(EnGo* this, GlobalContext* globalCtx) {
    Actor* actor = this->colliderCylinder.base.ac;

    if ((this->unk_390 & 0x1000) && (((actor != NULL) && (actor->id == ACTOR_OBJ_AQUA) && (actor->params & 1)) ||
                                     (this->actor.colChkInfo.damageEffect == 2))) {
        this->actionFunc = func_80A14E74;
    }
}

void func_80A14E74(EnGo* this, GlobalContext* globalCtx) {
    if (func_80A134F4(this, this->actor.cutscene)) {
        this->actionFunc = func_80A14EB0;
    }
}

void func_80A14EB0(EnGo* this, GlobalContext* globalCtx) {
    EnGo* sp24 = (EnGo*)this->actor.child;

    if ((s32)(this->unk_39C * 3.0f) != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
        Math_ApproachF(&this->unk_39C, 0.0f, 0.02f, 1.0f);
        this->unk_3A0 = (this->unk_39C / 0.9f) * 100.0f;
        func_80A139E4(this);
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        func_80A143A8(this, globalCtx);
        if ((ENGO_GET_F(&this->actor) == ENGO_F_4) && (ENGO_GET_70(&this->actor) == ENGO_70_1)) {
            SubS_UpdateFlags(&this->unk_390, 4, 7);
            func_80A143A8(sp24, globalCtx);
            sp24->actionFunc = func_80A149B0;
        }
        this->actionFunc = func_80A149B0;
    }
}

void func_80A14FC8(EnGo* this, GlobalContext* globalCtx) {
    s32 sp38[] = {
        0, 2, 6, 20, 18, 5, 5, 15,
    };
    u16 actorActionCmd = 0;
    s32 sp30;
    s32 actionIndex;

    switch (ENGO_GET_70(&this->actor)) {
        case ENGO_70_0:
            actorActionCmd = 128;
            break;

        case ENGO_70_1:
            actorActionCmd = 129;
            break;
    }

    if ((actorActionCmd == 128) || (actorActionCmd == 129)) {
        if (Cutscene_CheckActorAction(globalCtx, actorActionCmd)) {
            actionIndex = Cutscene_GetActorActionIndex(globalCtx, actorActionCmd);
            sp30 = globalCtx->csCtx.actorActions[actionIndex]->action;

            if (this->unk_394 != (u8)sp30) {
                this->unk_394 = sp30;
                func_80A12C48(this, globalCtx, sp38[sp30]);
                this->unk_390 = 0;
                this->unk_390 |= 0x20;
                this->unk_3BE = 0;
                this->unk_39C = 0.0f;
                this->unk_3A0 = 0.0f;

                switch (sp30) {
                    case 1:
                        this->unk_390 |= 0x80;
                        this->skelAnime.curFrame = this->skelAnime.endFrame;
                        break;

                    case 5:
                    case 6:
                        func_80A141D4(this, globalCtx);
                        break;
                }
            }

            switch (this->unk_394) {
                case 3:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (this->unk_3DC == 20)) {
                        func_80A12C48(this, globalCtx, 21);
                    }
                    break;

                case 4:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (this->unk_3DC == 18)) {
                        func_80A12C48(this, globalCtx, 19);
                    }
                    break;

                case 6:
                    if ((s32)(this->unk_39C * 3.0f) != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
                        Math_ApproachF(&this->unk_39C, 0.0f, 0.02f, 1.0f);
                        this->unk_3A0 = (this->unk_39C / 0.9f) * 100.0f;
                        func_80A139E4(this);
                    } else if (this->unk_390 & 0x400) {
                        func_80A143A8(this, globalCtx);
                    }
                    break;
            }

            if (actorActionCmd == 128) {
                switch (globalCtx->csCtx.frames) {
                    case 55:
                    case 100:
                    case 130:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);
                        break;

                    case 185:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WAKE_UP);
                        break;

                    case 250:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_EYE_BIG);
                        break;

                    case 465:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IWAIGORON_SOLO);
                        break;

                    case 490:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_VOICE_EATFULL);
                        break;
                }
            } else if (actorActionCmd == 129) {
                switch (globalCtx->csCtx.frames) {
                    case 360:
                    case 390:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);
                        break;

                    case 430:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WAKE_UP);
                        break;

                    case 450:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_EYE_BIG);
                        break;

                    case 480:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_VOICE_EATFULL);
                        break;
                }
            }

            SubS_FillLimbRotTables(globalCtx, this->unk_3CE, this->unk_3C8, ARRAY_COUNT(this->unk_3CE));
            Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
        }
    }
}

void func_80A153FC(EnGo* this, GlobalContext* globalCtx) {
    Vec3s* sp5C;
    Vec3f sp50;
    Vec3f sp44;

    if ((this->unk_390 & 0x1000) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SNOWBALL_BROKEN);

        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;

        func_80A118F8(this->unk_3F8, this->actor.world.pos);
        this->actor.shape.rot.x = 0;
        this->actor.speedXZ = 0.0f;

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);

        if (gSaveContext.save.day == 3) {
            func_80A141D4(this, globalCtx);
            this->actionFunc = func_80A14E14;
        } else {
            func_80A143A8(this, globalCtx);
            this->actionFunc = func_80A149B0;
        }
    } else if (this->unk_284 != NULL) {
        if (this->unk_390 & 0x800) {
            func_800B8E58(GET_PLAYER(globalCtx), NA_SE_PL_BODY_HIT);
            func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
        }

        sp5C = Lib_SegmentedToVirtual(this->unk_284->points);
        if (SubS_HasReachedPoint(&this->actor, this->unk_284, this->unk_3E4)) {
            if (this->unk_3E4 >= (this->unk_284->count - 1)) {
                this->unk_3E4 = 0;
            } else {
                this->unk_3E4++;
            }
        }

        Math_Vec3s_ToVec3f(&sp44, &sp5C[this->unk_3E4]);
        Math_Vec3f_Copy(&sp50, &this->actor.world.pos);
        Math_ApproachS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&sp50, &sp44), 4, 0x38E);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (this->actor.bgCheckFlags & 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BIGBALL_ROLL - SFX_FLAG);
            func_800AE930(&globalCtx->colCtx, Effect_GetByIndex(this->unk_3E8), &this->actor.world.pos, 18.0f,
                          this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
        } else {
            func_800AEF44(Effect_GetByIndex(this->unk_3E8));
        }

        this->actor.speedXZ = 4.0f;
        this->actor.shape.rot.x += (s16)(this->actor.speedXZ * 546.0f);
        Actor_MoveWithGravity(&this->actor);
    }
}

s32* func_80A15684(EnGo* this, GlobalContext* globalCtx) {
    static s32 D_80A16704[] = {
        D_80A16100,
        D_80A16164,
    };

    if (this->unk_3EC != 0) {
        return D_80A1640C;
    }

    if (ENGO_GET_F(&this->actor) == ENGO_F_1) {
        switch (ENGO_GET_70(&this->actor) % 6) {
            case ENGO_70_0:
                return D_80A163BC;
            case ENGO_70_1:
                return D_80A163CC;
            case ENGO_70_2:
                return D_80A163DC;
            case ENGO_70_3:
                return D_80A163EC;
            case ENGO_70_4:
                return D_80A163FC;
            case ENGO_70_5:
                return D_80A163FC;
        }
    }

    switch (ENGO_GET_F(&this->actor)) {
        case ENGO_F_3:
            return D_80A16350;
        case ENGO_F_4:
            return D_80A16704[ENGO_GET_70(&this->actor)];
        case ENGO_F_5:
            return D_80A16208;
        case ENGO_F_6:
            return D_80A16254;
        case ENGO_F_7:
            return D_80A16210;
        case ENGO_F_8:
            return D_80A16280;
        default:
            return D_80A16208;
    }
}

void func_80A157C4(EnGo* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;

    if (!func_8010BF58(&this->actor, globalCtx, func_80A15684(this, globalCtx), this->unk_3D8, &this->unk_28C)) {
        if ((ENGO_GET_F(&this->actor) != ENGO_F_1) && !(this->unk_390 & 0x200)) {
            Math_Vec3f_Copy(&sp40, &this->unk_38C->world.pos);
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp34, &sp40), 4, 0x2AA8);
        }
        SubS_FillLimbRotTables(globalCtx, this->unk_3CE, this->unk_3C8, ARRAY_COUNT(this->unk_3CE));
        return;
    }

    if ((ENGO_GET_F(&this->actor) == ENGO_F_5) || (ENGO_GET_F(&this->actor) == ENGO_F_6) ||
        (ENGO_GET_F(&this->actor) == ENGO_F_7)) {
        this->unk_3BC = 0;
        this->unk_390 &= ~0x20;
        this->unk_3BE = 4;
    }

    this->unk_390 &= ~0x8;
    SubS_UpdateFlags(&this->unk_390, 3, 7);
    this->unk_28C = 0;
    this->unk_390 |= 0x40;
    this->actionFunc = this->unk_18C;
}

void EnGo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;

    this->unk_288 = SubS_GetObjectIndex(OBJECT_TAISOU, globalCtx);
    this->unk_289 = SubS_GetObjectIndex(OBJECT_HAKUGIN_DEMO, globalCtx);
    this->actionFunc = func_80A14798;
}

void EnGo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
    Effect_Destroy(globalCtx, this->unk_3E8);
}

void EnGo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;
    f32 phi_f0;

    func_80A12868(this, globalCtx);
    if (!func_80A12774(this, globalCtx)) {
        func_80A12954(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);

    if (!(this->unk_390 & 0x400)) {
        func_80A12D6C(this);
        func_80A12A64(this, globalCtx);
        func_80A131F8(this, globalCtx);
        func_80A12B78(this, globalCtx);
    }

    if (!(this->unk_390 & 0x100) && !(this->unk_390 & 0x200) && !(this->unk_390 & 0x400)) {
        if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
            phi_f0 = this->colliderSphere.dim.worldSphere.radius + 60;
        } else {
            phi_f0 = this->colliderCylinder.dim.radius + 40;
        }
        func_8013C964(&this->actor, globalCtx, phi_f0, 20.0f, 0, this->unk_390 & 7);
    } else if ((this->unk_390 & 0x200) && (this->unk_3EC != 0)) {
        phi_f0 = this->colliderCylinder.dim.radius + 40;
        func_8013C964(&this->actor, globalCtx, phi_f0, 20.0f, 0, this->unk_390 & 7);
    }

    if ((ENGO_GET_F(&this->actor) != ENGO_F_8) && (ENGO_GET_F(&this->actor) != ENGO_F_2) &&
        (ENGO_GET_F(&this->actor) != ENGO_F_1)) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    }

    func_80A122EC(this);
    func_80A126BC(this, globalCtx);
    func_80A1203C(this);
}

void func_80A15B80(EnGo* this, GlobalContext* globalCtx) {
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                             this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);

    if (this->unk_390 & 0x100) {
        Matrix_Scale(this->actor.scale.x * 8.0f, this->actor.scale.y * 8.0f, this->actor.scale.z * 8.0f, MTXMODE_APPLY);
    } else {
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    }

    Matrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, (this->unk_390 & 0x100) ? object_oF1d_map_DL_001560 : object_oF1d_map_DL_0091A8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 EnGo_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3f sp30;
    s32 idx;

    if ((ENGO_GET_F(&this->actor) == ENGO_F_8) && (limbIndex == 10)) {
        limbIndex = limbIndex;
        Matrix_GetStateTranslation(&sp30);
        sp30.y = this->actor.world.pos.y;
        Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp30);
    }

    switch (limbIndex) {
        case 10:
            idx = 0;
            break;

        case 11:
            idx = 1;
            break;

        case 14:
            idx = 2;
            break;

        default:
            idx = 9;
            break;
    }

    if ((this->unk_390 & 0x80) && (idx < 9)) {
        rot->y += (s16)(Math_SinS(this->unk_3CE[idx]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->unk_3C8[idx]) * 200.0f);
    }
    return false;
}

void EnGo_TransfromLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnGo* this = THIS;
    u16 temp_v0;
    s32 phi_v1;
    s32 phi_v0;

    if (this->unk_390 & 0x40) {
        phi_v1 = false;
    } else {
        phi_v1 = true;
    }

    if (this->unk_390 & 0x10) {
        phi_v0 = true;
    } else {
        phi_v0 = false;
    }

    if (!phi_v1) {
        phi_v0 = false;
    }

    switch (limbIndex) {
        case 17:
            func_8013AD9C(this->unk_3B0 + this->unk_3B4 + 0x4000,
                          this->unk_3B2 + this->unk_3B6 + this->actor.shape.rot.y + 0x4000, &this->unk_290,
                          &this->unk_2A8, phi_v1, phi_v0);
            Matrix_StatePop();
            Matrix_InsertTranslation(this->unk_290.x, this->unk_290.y, this->unk_290.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_2A8.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_2A8.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_2A8.z, MTXMODE_APPLY);
            Matrix_StatePush();
            break;

        case 10:
            func_8013AD9C(this->unk_3B4 + 0x4000, this->unk_3B6 + this->actor.shape.rot.y + 0x4000, &this->unk_29C,
                          &this->unk_2AE, phi_v1, phi_v0);
            Matrix_StatePop();
            Matrix_InsertTranslation(this->unk_29C.x, this->unk_29C.y, this->unk_29C.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_2AE.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_2AE.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_2AE.z, MTXMODE_APPLY);
            Matrix_StatePush();
            break;
    }
}

void func_80A15FEC(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80A1670C[] = {
        object_oF1d_map_Tex_010438, object_oF1d_map_Tex_010C38, object_oF1d_map_Tex_011038,
        object_oF1d_map_Tex_010C38, object_oF1d_map_Tex_010838,
    };
    EnGo* this = THIS;

    if (!(this->unk_390 & 0x300)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A1670C[this->unk_3BE]));

        if (this->unk_3DC == 14) {
            Matrix_InsertTranslation(0.0f, 0.0f, -4000.0f, MTXMODE_APPLY);
        }
        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGo_OverrideLimbDraw, NULL, EnGo_TransfromLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        func_80A15B80(this, globalCtx);
    }
    func_80A137C0(this, globalCtx, this->unk_39C, this->unk_3A0);
    func_80A1213C(this, globalCtx);
}
