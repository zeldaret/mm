/*
 * File: z_en_knight.c
 * Overlay: ovl_En_Knight
 * Description: Igos du Ikana and his lackeys
 */

#include "z_en_knight.h"
#include "z64shrink_window.h"
#include "overlays/actors/ovl_Mir_Ray3/z_mir_ray3.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnKnight*)thisx)

void EnKnight_Init(Actor* thisx, PlayState* play);
void EnKnight_Destroy(Actor* thisx, PlayState* play);
void EnKnight_Update(Actor* thisx, PlayState* play);
void EnKnight_Draw(Actor* thisx, PlayState* play);

void func_809BD1AC(Actor* thisx, PlayState* play);
void func_809BD29C(Actor* thisx, PlayState* play);

void func_809B331C(EnKnight* this, PlayState* play);
void func_809B3394(EnKnight* this, PlayState* play);
void func_809B33F0(EnKnight* this, PlayState* play);
void func_809B35BC(EnKnight* this, PlayState* play);
void func_809B3618(EnKnight* this, PlayState* play);
void func_809B37C8(EnKnight* this, PlayState* play);
void func_809B3834(EnKnight* this, PlayState* play);
void func_809B389C(EnKnight* this, PlayState* play);
void func_809B3958(EnKnight* this, PlayState* play);
void func_809B3B94(EnKnight* this, PlayState* play);
void func_809B3DAC(EnKnight* this, PlayState* arg1);
void func_809B3E9C(EnKnight* this, PlayState* arg1);
void func_809B3F0C(EnKnight* this, PlayState* arg1);
void func_809B40E8(EnKnight* this, PlayState* play);
void func_809B41D8(EnKnight* this, PlayState* arg1);
void func_809B41F8(EnKnight* this, PlayState* play);
void func_809B42B8(EnKnight* this, PlayState* play);
void func_809B4308(EnKnight* this, PlayState* play);
void func_809B4880(EnKnight* this, PlayState* play);
void func_809B4C58(EnKnight* this, PlayState* play);
void func_809B4ED8(EnKnight* this, PlayState* play);
void func_809B5058(EnKnight* this, PlayState* play);
void func_809B52E8(EnKnight* this, PlayState* play);
void func_809B5698(EnKnight* this, PlayState* play);
void func_809B58D4(EnKnight* this, PlayState* play);
void func_809B59FC(EnKnight* this, PlayState* play);
void func_809B5B08(EnKnight* this, PlayState* play);
void func_809B5D54(EnKnight* this, PlayState* play);
void func_809B5ED0(EnKnight* this, PlayState* play);
void func_809B601C(EnKnight* this, PlayState* play);
void func_809B631C(EnKnight* this, PlayState* play);
void func_809B6528(EnKnight* this, PlayState* play);
void func_809B6764(EnKnight* this, PlayState* play);
void func_809B6C04(EnKnight* this, PlayState* play);
void func_809B6C54(EnKnight* this, PlayState* play);
void func_809B6D94(EnKnight* this, PlayState* play);
void func_809B6EC8(EnKnight* this, PlayState* arg1);
void func_809B6F40(EnKnight* this, PlayState* play);
void func_809B7190(EnKnight* this, PlayState* play);
void func_809B71DC(EnKnight* this, PlayState* play);
void func_809B7778(EnKnight* this, PlayState* play);
void func_809B7950(EnKnight* this, PlayState* play);
void func_809B842C(EnKnight* this, PlayState* play);
void func_809B8458(EnKnight* this, PlayState* play);
void func_809BA058(EnKnight* this, PlayState* play);
void func_809BA0CC(EnKnight* this, PlayState* play);
void func_809BA940(EnKnight* this, PlayState* play);
void func_809BA978(EnKnight* this, PlayState* play);

void func_809BD490(EnKnight* this, PlayState* play);
void func_809BD858(EnKnight* this, PlayState* play);

void func_809B329C(EnKnight* this, PlayState* play, s32 arg2);
void func_809B4024(EnKnight* this, PlayState* play, s16 arg2);
void func_809B47EC(EnKnight* this, PlayState* play, u8 arg2);

typedef struct {
    Vec3f unk0;
    Vec3f unkC;
    Vec3f unk18;
    char unk24[0x6];
    u8 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    f32 unk34;
    f32 unk38;
} EnKnightEffect; // size = 0x38

Vec3f D_809BDAF0 = { 0.0f, 0.0f, 0.0f };

u8 D_809BDAFC = 0;

u8 D_809BDB00 = 0;

// static DamageTable sDamageTable = {
static DamageTable D_809BDB04 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_809BDB24 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB44[1] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB68[1] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 32 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB8C = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_809BDB44),
    D_809BDB44, // sJntSphElementsInit,
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB9C = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_809BDB68),
    D_809BDB68, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDBAC[1] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDBD0 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_809BDBAC),
    D_809BDBAC, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809BDBE0[2] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7EFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7EFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 17 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDC28 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_809BDBE0),
    D_809BDBE0, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC38 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x10 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 15, 20, -10, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC64 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ALL,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7FFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, 0, { 0, 0, 0 } },
};

Color_RGBA8 D_809BDC90 = { 60, 50, 20, 255 };

Color_RGBA8 D_809BDC94 = { 40, 30, 30, 255 };

const ActorInit En_Knight_InitVars = {
    /**/ ACTOR_EN_KNIGHT,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_KNIGHT,
    /**/ sizeof(EnKnight),
    /**/ EnKnight_Init,
    /**/ EnKnight_Destroy,
    /**/ EnKnight_Update,
    /**/ EnKnight_Draw,
};

u16 D_809BDCB8[4] = { NA_SE_EN_BOSU_WALK, NA_SE_EN_YASE_WALK, NA_SE_EN_DEBU_WALK, 0 };
u16 D_809BDCC0[4] = { NA_SE_EN_BOSU_LAUGH_K, NA_SE_EN_YASE_PAUSE_K, NA_SE_EN_DEBU_PAUSE_K, 0 };
u16 D_809BDCC8[4] = { NA_SE_EN_BOSU_LAUGH_K, NA_SE_EN_YASE_LAUGH_K, NA_SE_EN_DEBU_LAUGH_K, 0 };
u16 D_809BDCD0[4] = { NA_SE_EN_BOSU_ATTACK_W, NA_SE_EN_YASE_ATTACK_W, NA_SE_EN_DEBU_ATTACK_W, 0 };
u16 D_809BDCD8[4] = { NA_SE_EN_BOSU_DAMAGE, NA_SE_EN_YASE_DAMAGE, NA_SE_EN_DEBU_DAMAGE, 0 };
u16 D_809BDCE0[4] = { NA_SE_EN_BOSU_DEAD, NA_SE_EN_YASE_DEAD, NA_SE_EN_DEBU_DEAD, 0 };
u16 D_809BDCE8[4] = { NA_SE_EN_BOSU_DEAD_VOICE, NA_SE_EN_YASE_DEAD_VOICE, NA_SE_EN_DEBU_DEAD_VOICE, 0 };

Color_RGBA8 D_809BDCF0 = { 60, 50, 20, 255 };

Color_RGBA8 D_809BDCF4 = { 40, 30, 30, 255 };

Color_RGBA8 D_809BDCF8 = { 170, 255, 255, 255 };

Color_RGBA8 D_809BDCFC = { 200, 200, 255, 255 };

Vec3f D_809BDD00 = { 0.0f, -1.0f, 0.0f };

Vec3f D_809BDD0C = { 100.0f, 0.0f, 0.0f };

Vec3f D_809BDD18 = { 0.0f, 600.0f, 0.0f };

Vec3f D_809BDD24 = { 0.0f, 600.0f, 1000.0f };

Vec3f D_809BDD30 = { 1000.0f, 0.0f, 0.0f };

s8 D_809BDD3C[0x20] = {
    -1, -1, -1, -1, 3, 4, 5, -1, -1, 6, 7, 8, -1, -1, -1, -1, -1, -1, 0, -1, 1, 2, -1, 9, 10, 11, 12, 13, 14, -1, 0, 0,
};

Vec3f D_809BDD5C = { 300.0f, 500.0f, 0.0f };

Vec3f D_809BDD68 = { 1000.0f, 0.0f, 0.0f };

Vec3f D_809BDD74 = { 700.0f, -500.0f, 0.0f };

Vec3f D_809BDD80 = { 300.0f, 500.0f, 0.0f };

EnKnight* D_809BEFD0;
EnKnight* D_809BEFD4;
EnKnight* D_809BEFD8;
EnKnight* D_809BEFDC;
EnKnight* D_809BEFE0;
MirRay3* D_809BEFE4;
EnKnightEffect D_809BEFE8[100];

// object

extern AnimationHeader D_060005A8;
extern AnimationHeader D_060009E0;
extern AnimationHeader D_06000D9C;
extern AnimationHeader D_06001CDC;
extern AnimationHeader D_06002174;
extern AnimationHeader D_06003008;
extern AnimationHeader D_060031F0;
extern AnimationHeader D_06003650;
extern AnimationHeader D_060040E0;
extern AnimationHeader D_06004620;
extern AnimationHeader D_06004974;
extern AnimationHeader D_06005D30;
extern AnimationHeader D_060079D4;
extern AnimationHeader D_06008390;
extern AnimationHeader D_06008524;
extern AnimationHeader D_060089E4;
extern AnimationHeader D_06008D80;
extern AnimationHeader D_06009538;
extern AnimationHeader D_06009D8C;
extern AnimationHeader D_0600A530;
extern AnimationHeader D_0600AFAC;
extern AnimationHeader D_0600B5D4;
extern AnimationHeader D_0600BCF4;
extern AnimationHeader D_0600C384;
extern AnimationHeader D_0600CDE0;
extern AnimationHeader D_0600DDCC;
extern AnimationHeader D_0600E15C;
extern AnimationHeader D_0600E45C;
extern AnimationHeader D_0600EA90;
extern AnimationHeader D_0600EF44;
extern AnimationHeader D_06010E98;
extern AnimationHeader D_06011298;
extern AnimationHeader D_06005E78;
extern AnimationHeader D_06006754;
extern AnimationHeader D_06006EF8;
extern AnimationHeader D_0600A88C;
extern AnimationHeader D_0600C7F0;
extern AnimationHeader D_0600D870;
extern AnimationHeader D_0600E7F4;
extern AnimationHeader D_0600FC78;
extern AnimationHeader D_0601024C;
extern AnimationHeader D_0602105C;
extern AnimationHeader D_06021B10;
extern AnimationHeader D_06021E34;
extern Gfx D_06013020[];
extern Gfx D_06012DB0[];
extern Gfx D_06012400[];
extern AnimatedMaterial D_06018BC4;
extern AnimationHeader D_06020950;
extern AnimationHeader D_06022728;
extern AnimationHeader D_06022CAC;
extern FlexSkeletonHeader D_06020374;
extern FlexSkeletonHeader D_060201A8;
extern Gfx D_060188F8[];
extern Gfx D_060189F0[];
extern Gfx D_06018AF0[];

extern Gfx D_08000000[];

void func_809B20F0(PlayState* play, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, s16 arg6) {
    s16 i;
    EnKnightEffect* eff;

    for (eff = play->specialEffects, i = 0; i < 100; i++, eff++) {
        if (eff->unk2A == 0) {
            eff->unk2A = 1;
            eff->unk0 = *arg1;
            eff->unkC = *arg2;
            eff->unk18 = *arg3;
            eff->unk30 = 0;
            eff->unk34 = (BREG(50) * 0.0001f + 0.001f) * arg4;
            eff->unk38 = (BREG(51) * 0.0001f + 0.001f) * arg5;
            eff->unk2E = arg6;
            eff->unk2C = 0;
            return;
        }
    }
}

void func_809B21F4(EnKnight* this, s32 arg1, ColliderJntSph* jntSph, Vec3f* pos) {
    f32 var_fv0 = (this == D_809BEFD0) ? 1.3076924f : 1.0f;

    if (this->actionFunc == func_809B52E8) {
        var_fv0 *= 2.0f;
    }

    jntSph->elements[arg1].dim.worldSphere.center.x = pos->x;
    jntSph->elements[arg1].dim.worldSphere.center.y = pos->y;
    jntSph->elements[arg1].dim.worldSphere.center.z = pos->z;
    jntSph->elements[arg1].dim.worldSphere.radius =
        jntSph->elements[arg1].dim.modelSphere.radius * var_fv0 * jntSph->elements[arg1].dim.scale;
}

void func_809B22CC(EnKnight* this, PlayState* play, u8 arg2) {
    u8 i;
    Vec3f pos;
    Vec3f vel;
    Vec3f acc;

    if (!(this->unk146 & arg2) && this->unk162 == 0 &&
        (this->unk2A4 > 1.0f || this->unk2A8 > 1.0f || arg2 == 0 || this->actor.speed > 1.0f)) {
        for (i = 0; i < 2; i++) {
            vel.x = Rand_CenteredFloat(3.0f);
            vel.y = Rand_ZeroFloat(1.0f);
            vel.z = Rand_CenteredFloat(3.0f);
            acc.y = -0.1f;
            acc.x = acc.z = 0.0f;
            pos.x = this->unk2AC[i].x + Rand_CenteredFloat(10.0f);
            pos.y = (Rand_ZeroFloat(5.0f) + this->actor.floorHeight) - 5.0f;
            pos.z = this->unk2AC[i].z + Rand_CenteredFloat(10.0f);
            func_800B0EB0(play, &pos, &vel, &acc, &D_809BDC90, &D_809BDC94, Rand_ZeroFloat(80.0f) + 150.0f, 10,
                          Rand_ZeroFloat(5.0f) + 14.0f);
        }
    }
}

void EnKnight_Init(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;
    s32 pad;
    s32 temp_v0_2;

    this->actor.targetMode = 5;
    this->actor.colChkInfo.mass = 0xFE;
    this->actor.colChkInfo.damageTable = &D_809BDB04;
    this->unk17C = 255.0f;
    this->unk146 = Rand_ZeroFloat(1000.0f);
    this->actor.flags |= 0x400;

    if (this->actor.params == 0x64) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 12.0f);
        SkelAnime_InitFlex(play, &this->unk194, &D_060201A8, &D_06003008, this->unk2C4, this->unk372, 29);
        Actor_SetScale(&this->actor, KREG(12) * 0.001f + 0.017f);
        func_809BA058(this, play);
        Collider_InitAndSetCylinder(play, &this->unk488, &this->actor, &D_809BDC38);
        Collider_InitAndSetCylinder(play, &this->unk634, &this->actor, &D_809BDC64);
        this->actor.colChkInfo.health = 0xA - BREG(40);
    } else if (this->actor.params >= 0xC8) {
        this->actor.update = func_809BD1AC;
        this->actor.draw = func_809BD29C;
        this->actor.flags &= ~1;
        if (1) {}
        if (this->actor.params == 0xC8) {
            SkelAnime_InitFlex(play, &this->unk194, &D_06020374, &D_060040E0, this->unk2C4, this->unk372, 0x1D);
            Actor_SetScale(&this->actor, KREG(13) * 0.001f + 0.013f);
        } else {
            SkelAnime_InitFlex(play, &this->unk194, &D_060201A8, &D_060040E0, this->unk2C4, this->unk372, 0x1D);
            Actor_SetScale(&this->actor, KREG(13) * 0.001f + 0.017f);
        }
        if (this->actor.params == 0xCA) {
            this->unk17C = BREG(79) + 100.0f;
        } else {
            this->unk17C = BREG(77) + 120.0f;
        }
    } else {
        this->actor.hintId = 0x16;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
        Collider_InitAndSetJntSph(play, &this->unk534, &this->actor, &D_809BDBD0, this->unk554);
        Collider_InitAndSetJntSph(play, &this->unk594, &this->actor, &D_809BDC28, this->unk5B4);
        if (this->actor.params == 0x23) {
            Collider_InitAndSetJntSph(play, &this->unk4D4, &this->actor, &D_809BDB8C, this->unk4F4);
            SkelAnime_InitFlex(play, &this->unk194, &D_06020374, &D_060040E0, this->unk2C4, this->unk372, 0x1D);
            this->actor.colChkInfo.health = 6 - BREG(40);
            Actor_SetScale(&this->actor, KREG(13) * 0.001f + 0.013f);
        } else {
            Collider_InitAndSetJntSph(play, &this->unk4D4, &this->actor, &D_809BDB9C, this->unk4F4);
            SkelAnime_InitFlex(play, &this->unk194, &D_060201A8, &D_060040E0, this->unk2C4, this->unk372, 0x1D);
            this->actor.colChkInfo.health = 0xE - BREG(41);
            Actor_SetScale(&this->actor, KREG(12) * 0.001f + 0.017f);
            this->unk290 = Rand_ZeroFloat(1.9999f);
        }
        this->unk18E = 3;
        this->unk180 = 180.0f;
        temp_v0_2 = D_809BDAFC & 3;
        D_809BDAFC++;
        this->unk6B4 = D_809BDCB8[temp_v0_2];
        this->unk6B6 = D_809BDCC0[temp_v0_2];
        this->unk6B8 = D_809BDCC8[temp_v0_2];
        this->unk6BC = D_809BDCD0[temp_v0_2];
        this->unk6BE = D_809BDCD8[temp_v0_2];
        this->unk6C0 = D_809BDCE0[temp_v0_2];
        this->unk6C2 = D_809BDCE8[temp_v0_2];
        if (this->actor.params != 0x23) {
            s32 i;
            play->specialEffects = D_809BEFE8;

            for (i = 0; i < ARRAY_COUNT(D_809BEFE8); i++) {
                D_809BEFE8[i].unk2A = 0;
            }

            D_809BEFD0 = this;
            D_809BEFE0 = NULL;
            D_809BEFDC = NULL;
            this->actor.shape.rot.y = -0x4000;
            D_809BEFD4 =
                (EnKnight*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KNIGHT, 1398.0f, 66.0f, 2730.0f,
                                       this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, 0x23);
            D_809BEFD8 =
                (EnKnight*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KNIGHT, 1398.0f, 66.0f, 2969.0f,
                                       this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, 0x23);
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0x12E, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0);
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0x12E, 0.0f, 0.0f, 0.0f, 0, 0, 0, 1);
        }
        if ((gSaveContext.eventInf[5] & 0x80) && !Flags_GetClear(play, play->roomCtx.curRoom.num)) {
            if (this == D_809BEFD0) {
                this->actor.world.pos.x = BREG(27) + 1376.0f;
                this->actor.world.pos.y = 45.0f;
                this->actor.world.pos.z = BREG(28) + 2864.0f;
                func_809B6528(this, play);
                this->unk194.curFrame = 25.0f;
                this->actor.flags &= ~1;
                D_809BDB00 = KREG(83) + 0x28;
            } else {
                func_809B3E9C(this, play);
                this->unk152 = 1;
                this->unk46C = this->unk470 = 1.0f;
                this->actor.gravity = -1.5f;
                this->unk6B0 = 60.0f;
            }
            play->envCtx.lightSettingOverride = 7;
            return;
        }
        func_809B631C(this, play);
        play->envCtx.lightSettingOverride = 0;
    }
}

void EnKnight_Destroy(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;
}

void func_809B2DD0(EnKnight* this, PlayState* play) {
    Player* player;
    Actor* explosive;
    f32 px;
    f32 pz;
    f32 dx;
    f32 dz;

    if (this->unk162 == 0) {
        player = GET_PLAYER(play);

        explosive = play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
        while (explosive != NULL) {
            px = this->actor.world.pos.x;
            pz = this->actor.world.pos.z;
            dx = explosive->world.pos.x - px;
            dz = explosive->world.pos.z - pz;
            if (sqrtf(SQ(dx) + SQ(dz)) < 100.0f) {
                this->unk440.x = px - dx * 100.0f;
                this->unk440.z = pz - dz * 100.0f;
                func_809B47EC(this, play, 0);
            }
            explosive = explosive->next;
        }

        if (D_809BEFE4 != NULL && D_809BEFE4->unk_214 > 0.1f && this->actor.xzDistToPlayer <= (BREG(70) + 300.0f)) {
            px = this->actor.world.pos.x;
            pz = this->actor.world.pos.z;
            dx = player->actor.world.pos.x - px;
            dz = player->actor.world.pos.z - pz;
            this->unk440.x = px - dx * 100.0f;
            this->unk440.z = pz - dz * 100.0f;
            func_809B47EC(this, play, 1);
        }
    }
}

s32 func_809B2F54(EnKnight* this, PlayState* play) {
    f32 var_fv0;
    s32 sp20 = false;
    Player* player = GET_PLAYER(play);

    var_fv0 = (this == D_809BEFD0) ? 1.3076924f : 1.0f;

    if (this->actor.xzDistToPlayer <= 90.0f * var_fv0 && !(this->unk146 & 7)) {
        if (Rand_ZeroOne() < 0.5f && D_809BEFDC != (EnKnight*)player->actor.parent) {
            func_809B389C(this, play);
        } else if (Rand_ZeroOne() < 0.5f) {
            func_809B329C(this, play, false);
        } else {
            func_809B35BC(this, play);
        }
        sp20 = true;
    }

    if (this == D_809BEFD0 && this->unk162 == 0 && (this->unk14A[2] == 0 || BREG(15) == 1)) {
        if (KREG(71) + 100.0f < this->actor.xzDistToPlayer) {
            sp20 = true;
            if (this->actor.xzDistToPlayer < KREG(72) + 300.0f) {
                if (Rand_ZeroOne() > 0.5f) {
                    func_809B6EC8(this, play);
                } else {
                    func_809B6C04(this, play);
                }
            } else {
                func_809B6C04(this, play);
            }
        }
    }
    return sp20;
}

s32 func_809B316C(EnKnight* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v1 = this->unk172;
    s16 var_a0 = temp_v1 - this->actor.shape.rot.y;

    if (ABS_ALT(var_a0) < 0x3000) {
        s16 var_a0 = temp_v1 - (s16)(player->actor.shape.rot.y + 0x8000);
        s32 var_v0 = ABS_ALT(var_a0);

        if (var_v0 < 0x3000) {
            return 1;
        }
    }
    return 0;
}

s32 func_809B31E8(EnKnight* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 var_v1 = this->unk172 - (s16)(player->actor.focus.rot.y + 0x8000);

    if (ABS_ALT(var_v1) < (s16)(KREG(91) * 0x100 + 0x400)) {
        s16 var_a1 = (s16) - this->unk170 - player->actor.focus.rot.x;
        s32 var_v0 = ABS_ALT(var_a1);

        if (var_v0 < (s16)(KREG(92) * 0x100 + 0x300)) {
            return 1;
        }
    }
    return 0;
}

void func_809B329C(EnKnight* this, PlayState* play, s32 arg2) {
    Animation_MorphToLoop(&this->unk194, &D_06020950, -5.0f);
    this->actionFunc = func_809B331C;
    if (this == D_809BEFD0) {
        if (arg2) {
            this->unk14A[0] = 0;
        } else {
            this->unk14A[0] = 6;
        }
    } else {
        this->unk14A[0] = 15;
    }
}

void func_809B331C(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0x500);
    if (this->unk14A[0] == 0) {
        func_809B3394(this, play);
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
}

void func_809B3394(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_06011298, 0.0f);
    this->unk1D8 = Animation_GetLastFrame(&D_06011298);
    this->actionFunc = func_809B33F0;
}

void func_809B33F0(EnKnight* this, PlayState* play) {
    Vec3f sp2C;

    this->unk186 = 0;
    if (this->unk194.curFrame >= 3.0f && this->unk194.curFrame <= 6.0f) {
        this->unk450 = 255.0f;
        this->unk454 = -19.0f;
        this->unk458 = 46.0f;
        this->unk45C = 17.0f;
        this->unk460 = -0.5497787f;
        this->unk464 = 2.9059734f;
        this->unk468 = -1.1780972f;
    }
    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk194.curFrame >= 2.0f && this->unk194.curFrame <= 5.0f) {
        Matrix_RotateYS(this->actor.world.rot.y, MTXMODE_NEW);
        Matrix_MultVecZ(5.0f, &sp2C);
        this->unk2A4 = sp2C.x;
        this->unk2A8 = sp2C.z;
    }
    if (Animation_OnFrame(&this->unk194, 1.0f)) {
        Actor_PlaySfx(&this->actor, this->unk6BC);
    }
    if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
        if (Rand_ZeroOne() < 0.5f && this->actor.xzDistToPlayer <= 100.0f) {
            func_809B35BC(this, play);
        } else {
            func_809B3E9C(this, play);
        }
    }
    this->unk190 = 1;
}

void func_809B35BC(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_06022728, -5.0f);
    this->unk1D8 = Animation_GetLastFrame(&D_06022728);
    this->actionFunc = func_809B3618;
}

void func_809B3618(EnKnight* this, PlayState* play) {
    Vec3f sp2C;

    this->unk186 = 0;
    if (this == D_809BEFD0) {
        Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0x800);
    }
    if (this->unk194.curFrame >= 12.0f && this->unk194.curFrame <= 15.0f) {
        this->unk450 = 255.0f;
        this->unk454 = -20.0f;
        this->unk458 = 47.0f;
        this->unk45C = 0.0f;
        this->unk460 = 3.1415927f;
        this->unk464 = 0.f;
        this->unk468 = 0.47123894f;
    }
    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk194.curFrame >= 12.0f && this->unk194.curFrame <= 15.0f) {
        Matrix_RotateYS(this->actor.world.rot.y, MTXMODE_NEW);
        Matrix_MultVecZ(5.0f, &sp2C);
        this->unk2A4 = sp2C.x;
        this->unk2A8 = sp2C.z;
    }
    if (Animation_OnFrame(&this->unk194, 12.0f)) {
        Actor_PlaySfx(&this->actor, this->unk6BC);
    }
    if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
        func_809B37C8(this, play);
    }
    if (this->unk194.curFrame >= 12.0f) {
        this->unk190 = 1;
    }
}

void func_809B37C8(EnKnight* this, PlayState* play) {
    Animation_MorphToLoop(&this->unk194, &D_06022CAC, 0.0f);
    this->actionFunc = func_809B3834;
    if (this == D_809BEFD0) {
        this->unk14A[0] = 6;
    } else {
        this->unk14A[0] = 15;
    }
}

void func_809B3834(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
}

void func_809B389C(EnKnight* this, PlayState* play) {
    if (Rand_ZeroOne() < 0.5f) {
        Animation_MorphToPlayOnce(&this->unk194, &D_0600C384, -2.0f);
        this->unk1D8 = Animation_GetLastFrame(&D_0600C384);
    } else {
        Animation_MorphToPlayOnce(&this->unk194, &D_0600BCF4, -2.0f);
        this->unk1D8 = Animation_GetLastFrame(&D_0600BCF4);
    }
    this->actionFunc = func_809B3958;
    this->unk14A[0] = 20;
}

void func_809B3958(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
        if (Rand_ZeroOne() < 0.6f && this->actor.xzDistToPlayer <= 100.0f) {
            if (Rand_ZeroOne() < 0.5f) {
                func_809B389C(this, play);
            } else {
                func_809B329C(this, play, 0);
            }
        } else {
            func_809B3E9C(this, play);
        }
    }
    Math_ApproachS(&this->actor.world.rot.y, this->unk172, 5, 0x500);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] == 16) {
        this->unk190 = 1;
    }
}

void func_809B3A7C(EnKnight* this, PlayState* play) {
    s32 i;
    Vec3f sp28;

    if (this->actor.xzDistToPlayer <= 200.0f) {
        Animation_MorphToPlayOnce(&this->unk194, &D_0600AFAC, -3.0f);
        this->unk1D8 = Animation_GetLastFrame(&D_0600AFAC);
        this->actionFunc = func_809B3B94;
        Matrix_RotateYS(this->unk172, MTXMODE_NEW);
        Matrix_MultVecZ(KREG(49) + 7.0f, &sp28);
        this->unk2A4 = sp28.x;
        this->unk2A8 = sp28.z;
        this->actor.velocity.y = 10.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_TEKU_JUMP);
        this->unk14A[0] = 15;

        for (i = 0; i < 5; i++) {
            func_809B22CC(this, play, 0);
        }
    }
}

void func_809B3B94(EnKnight* this, PlayState* play) {
    if (this->unk14A[0] >= 2 && this->unk14A[0] < 6) {
        this->unk450 = 255.0f;
        this->unk454 = -19.0f;
        this->unk458 = 46.0f;
        this->unk45C = 17.0f;
        this->unk460 = -0.5497787f;
        this->unk464 = 2.9059734f;
        this->unk468 = -1.1780972f;
    }
    SkelAnime_Update(&this->unk194);
    if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
        Animation_MorphToPlayOnce(&this->unk194, &D_0600B5D4, 0.0f);
        Actor_PlaySfx(&this->actor, this->unk6BC);
        this->unk1D8 = 1000.0f;
    }
    this->actor.speed = 0.0f;
    if (this->actor.velocity.y <= 0.0f && this->actor.bgCheckFlags & 1) {
        this->unk2A8 = 0.0f;
        this->unk2A4 = 0.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
    }
    if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
    }
    this->unk190 = 1;
}

void func_809B3CD0(EnKnight* this, PlayState* play) {
    if (this == D_809BEFD0 && this->actor.xzDistToPlayer <= 120.0f && Rand_ZeroOne() < 0.1f) {
        func_809B59FC(this, play);
        return;
    }
    if (this->actionFunc != func_809B3DAC) {
        this->unk424 = this->actionFunc;
        Animation_MorphToPlayOnce(&this->unk194, &D_060031F0, -2.0f);
        this->unk1D8 = Animation_GetLastFrame(&D_060031F0);
        this->actionFunc = func_809B3DAC;
    }
    this->unk14A[0] = 5;
}

void func_809B3DAC(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0x800);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] != 0) {
        this->unk191 = 1;
    } else if (this->unk424 == func_809B4880) {
        func_809B47EC(this, play, 1);
    } else {
        func_809B3E9C(this, play);
        if (this == D_809BEFD0 && Rand_ZeroOne() < 0.4f) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_CYNICAL);
        }
    }
    this->unk192 = 1;
}

void func_809B3E9C(EnKnight* this, PlayState* play) {
    Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
    this->actionFunc = func_809B3F0C;
    this->unk14A[0] = Rand_ZeroFloat(50.0f) + 20.0f;
}

void func_809B3F0C(EnKnight* this, PlayState* play) {
    s16 temp_v1;
    s32 var_a0;

    SkelAnime_Update(&this->unk194);
    temp_v1 = this->unk172 - this->actor.shape.rot.y;
    var_a0 = (this == D_809BEFD0) ? 0x7FFF : 0x6000;
    if (ABS_ALT(temp_v1) < var_a0) {
        func_809B41D8(this, play);
    } else {
        if (!(this->unk146 & 7) && Rand_ZeroOne() < 0.75f) {
            this->unk186 = Rand_CenteredFloat(28672.0f);
        }
        if (this->unk14A[0] == 0) {
            func_809B4024(this, play, 0x4000);
        }
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    this->unk192 = 1;
}

void func_809B4024(EnKnight* this, PlayState* play, s16 arg2) {
    this->actionFunc = func_809B40E8;
    Animation_MorphToPlayOnce(&this->unk194, &D_0600EF44, -2.0f);
    if (Rand_ZeroOne() < 0.5f) {
        this->unk15A = this->actor.shape.rot.y + arg2;
        this->unk186 = 0x3800;
    } else {
        this->unk15A = this->actor.shape.rot.y - arg2;
        this->unk186 = -0x3800;
    }
    this->unk15C = (arg2 == 0x4000) ? 0 : 0x800;
    this->unk14A[0] = 0x14;
}

void func_809B40E8(EnKnight* this, PlayState* play) {
    s16 temp_v0;

    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] < 0xF) {
        Math_ApproachS(&this->actor.world.rot.y, this->unk15A, 2, this->unk15C);
        Math_ApproachS(&this->unk15C, 0x800, 1, 0x200);
    }
    temp_v0 = this->unk172 - this->actor.shape.rot.y;
    if (ABS_ALT(temp_v0) < 0x6000) {
        func_809B41D8(this, play);
    } else if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
    }
    this->unk18C = 0x3000;
    this->unk18E = 2;
}

void func_809B41D8(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B41F8;
    this->unk14A[0] = 0xA;
}

void func_809B41F8(EnKnight* this, PlayState* play) {
    s16 temp_v0;

    SkelAnime_Update(&this->unk194);
    temp_v0 = this->unk172 - this->actor.shape.rot.y;
    if (temp_v0 > 0x3800) {
        this->unk186 = 0x3800;
    } else if (temp_v0 < -0x3800) {
        this->unk186 = -0x3800;
    } else {
        this->unk186 = temp_v0;
    }
    if (this->unk14A[0] == 0) {
        func_809B42B8(this, play);
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    this->unk18C = 0x3000;
    this->unk18E = 2;
    this->unk192 = 1;
}

void func_809B42B8(EnKnight* this, PlayState* play) {
    Animation_MorphToLoop(&this->unk194, &D_06004620, -5.0f);
    this->actionFunc = func_809B4308;
    this->actor.speed = 0.0f;
}

void func_809B4308(EnKnight* this, PlayState* play) {
    f32 sp5C;
    f32 dx;
    f32 dz;
    f32 var_fv0;
    Vec3f sp44;
    Vec3f sp38;
    s16 temp_v0;
    s16 sp34;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->unk194);
    if (!(this->unk146 & 0x3F) && Rand_ZeroOne() < 0.5f) {
        if (Rand_ZeroOne() < 0.6666f) {
            Actor_PlaySfx(&this->actor, this->unk6B6);
        } else {
            Actor_PlaySfx(&this->actor, this->unk6B8);
        }
    }
    if (this != D_809BEFD0 && this->actor.xzDistToPlayer > 150.0f) {
        Matrix_RotateYS(player->actor.world.rot.y, MTXMODE_NEW);
        if (this == D_809BEFD4) {
            sp44.x = 100.0f;
        } else {
            sp44.x = -100.0f;
        }
        sp44.y = 0.0f;
        sp44.z = 100.0f;
        Matrix_MultVec3f(&sp44, &sp38);
        this->unk440.x = player->actor.world.pos.x + sp38.x;
        this->unk440.z = player->actor.world.pos.z + sp38.z;
        dx = this->unk440.x - this->actor.world.pos.x;
        dz = this->unk440.z - this->actor.world.pos.z;
        sp34 = Math_FAtan2F(dz, dx);
    } else {
        sp34 = this->unk172;
    }
    Math_ApproachS(&this->actor.world.rot.y, sp34, 5, 0xA00);
    Math_ApproachS(&this->actor.shape.rot.y, this->unk172, 5, 0x500);
    sp5C = this->actor.speed;
    var_fv0 = (this == D_809BEFD0) ? 1.3076924f : 1.0f;
    if (this->actor.xzDistToPlayer <= (150.0f * var_fv0)) {
        if (this->actor.xzDistToPlayer <= (80.0f * var_fv0)) {
            if (this->actor.xzDistToPlayer <= (40.0f * var_fv0)) {
                Math_ApproachF(&this->actor.speed, -2.5f, 1.0f, 1.0f);
            } else {
                Math_ApproachF(&this->actor.speed, 0.0f, 1.0f, 1.0f);
            }
        } else {
            Math_ApproachF(&this->actor.speed, 2.5f, 1.0f, 1.0f);
        }
    } else {
        Math_ApproachF(&this->actor.speed, 5.0f, 1.0f, 1.0f);
        if ((Animation_OnFrame(&this->unk194, 0.0f) != 0) || (Animation_OnFrame(&this->unk194, 5.0f) != 0)) {
            Actor_PlaySfx(&this->actor, this->unk6B4);
        }
        func_809B22CC(this, play, 3);
    }
    if ((this->actor.speed > 3.0f) && (sp5C <= 3.0f)) {
        Animation_MorphToLoop(&this->unk194, &D_06003650, -3.0f);
        if (Rand_ZeroOne() < 0.25f) {
            func_809B3A7C(this, play);
        }
    }
    if (this->actionFunc == func_809B4308) {
        if ((this->actor.speed < 4.0f) && (sp5C >= 4.0f)) {
            Animation_MorphToLoop(&this->unk194, &D_06004620, -5.0f);
            if (Rand_ZeroOne() < 0.25f) {
                func_809B3A7C(this, play);
            }
        }
        if ((this->actor.speed < 1.0f) && (sp5C >= 1.0f)) {
            Animation_MorphToLoop(&this->unk194, &D_060040E0, -10.0f);
        }
        if ((this->actor.speed >= 1.0f) && (sp5C < 1.0f)) {
            Animation_MorphToLoop(&this->unk194, &D_06004620, -5.0f);
        }
    }
    temp_v0 = sp34 - this->actor.shape.rot.y;
    if (ABS_ALT(temp_v0) < 0x6000) {
        if (temp_v0 >= 0x3801) {
            this->unk186 = 0x3800;
        } else if (temp_v0 < -0x3800) {
            this->unk186 = -0x3800;
        } else {
            this->unk186 = temp_v0;
        }
        if (func_809B2F54(this, play) != 0) {
            return;
        }
    } else {
        func_809B3E9C(this, play);
    }
    this->unk192 = 1;
}

void func_809B47EC(EnKnight* this, PlayState* play, u8 arg2) {
    if (this->actionFunc != func_809B4880) {
        Animation_MorphToLoop(&this->unk194, &D_06003650, -5.0f);
        this->unk_148 = 0;
        this->actionFunc = func_809B4880;
    }
    this->unk14A[0] = Rand_ZeroFloat(15.0f) + 10.0f;
    this->unk292 = arg2;
}

void func_809B4880(EnKnight* this, PlayState* play) {
    f32 dx;
    f32 dz;

    SkelAnime_Update(&this->unk194);
    this->unk186 = 0;
    switch (this->unk_148) {
        case 0:
            Math_ApproachF(&this->actor.speed, 5.0f, 1.0f, 1.0f);
            dx = this->unk440.x - this->actor.world.pos.x;
            dz = this->unk440.z - this->actor.world.pos.z;
            Math_ApproachS(&this->actor.world.rot.y, Math_FAtan2F(dz, dx), 5, 0xA00);
            if (Animation_OnFrame(&this->unk194, 0.0f) || Animation_OnFrame(&this->unk194, 5.0f)) {
                Actor_PlaySfx(&this->actor, this->unk6B4);
            }
            func_809B22CC(this, play, 3);
            if (this->unk292 != 0 && ((D_809BEFE4 != NULL && D_809BEFE4->unk_214 < 0.1f) ||
                                      BREG(70) + 300.0f < this->actor.xzDistToPlayer || this->unk291 != 0)) {
                if (this->unk291 != 0) {
                    this->unk_148 = 3;
                    this->unk2A1 = 30;
                    Animation_MorphToLoop(&this->unk194, &D_0600E45C, -2.0f);
                    this->unk1D8 = Animation_GetLastFrame(&D_0600E45C);
                    Actor_PlaySfx(&this->actor, NA_SE_EN_STAL_FREEZE_LIGHTS);
                } else {
                    this->unk_148 = 1;
                    Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
                    this->unk1D8 = 1000.0f;
                }
            }
            break;
        case 1:
            if (this->unk291 != 0) {
                this->unk_148 = 2;
                Animation_MorphToPlayOnce(&this->unk194, &D_060031F0, -2.0f);
                Actor_PlaySfx(&this->actor, this->unk6B6);
            }
            goto block_24;
        case 2:
            if (this->unk291 == 0) {
                this->unk_148 = 1;
                Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
            }
            if (this->unk291 >= 8) {
                Math_ApproachF(&this->unk474, 1.0f, 1.0f, 0.5f);
            }
            goto block_24;
        case 3:
            if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
                this->unk_148 = 2;
                Animation_MorphToPlayOnce(&this->unk194, &D_060031F0, -2.0f);
                this->unk1D8 = 1000.0f;
            }
            goto block_24;

        block_24:
            this->unk594.base.colType = 0xA;
            Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
            if (this->unk1D8 > 10.0f) {
                Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0xE00);
            }
            if (D_809BEFE4 != NULL && D_809BEFE4->unk_214 > 0.1f) {
                this->unk14A[0] = Rand_ZeroFloat(15.0f) + 10.0f;
            }
            this->unk192 = 1;
            break;
    }
    if (this->unk14A[0] == 0) {
        func_809B4024(this, play, 0x7000);
    }
}

void func_809B4BFC(EnKnight* this, PlayState* play) {
    Animation_MorphToLoop(&this->unk194, &D_0600CDE0, -25.0f);
    Actor_PlaySfx(&this->actor, this->unk6B6);
    this->actionFunc = func_809B4C58;
    this->unk14A[0] = 35;
}

void func_809B4C58(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    this->unk186 = 0;
    Math_ApproachF(&this->unk180, 180.0f, 1.0f, 10.0f);

    if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
    }

    if (((s16)(BREG(74) + 10) < this->unk14A[0]) && !((BREG(76) + 3) & this->unk146)) {
        EnKnight* temp_v0 = (EnKnight*)Actor_SpawnAsChild(
            &play->actorCtx, &this->actor, play, ACTOR_EN_KNIGHT, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, this->actor.world.rot.x, this->actor.world.rot.y, this->actor.world.rot.z,
            (this == D_809BEFD0) ? 0x00C9 : 0x00C8);

        if (temp_v0 != NULL) {
            s32 i;

            for (i = 0; i < 29; i++) {
                temp_v0->unk194.jointTable[i] = this->unk194.jointTable[i];
                temp_v0->unk194.skeleton = this->unk194.skeleton;
                temp_v0->unk194.dListCount = this->unk194.dListCount;
            }
        }
    }
}

void func_809B4E84(EnKnight* this, PlayState* play, u16 arg2) {
    this->actionFunc = func_809B4ED8;
    this->unk14A[0] = arg2;
    this->unk14A[1] = 0x1E;
    Actor_SetColorFilter(&this->actor, 0, 0x78, 0, arg2);
}

void func_809B4ED8(EnKnight* this, PlayState* play) {
    if (this->unk14A[1] > 0 && this->unk14A[1] < 23) {
        if (this->unk14A[1] == 1) {
            D_809BEFE0 = NULL;
        } else {
            D_809BEFE0 = this;
        }
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] < 20) {
        if (this->unk14A[0] % 2 != 0) {
            this->unk184 = 0x708;
        } else {
            this->unk184 = -0x708;
        }
    } else {
        this->unk186 = 0;
    }
    if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
    }
}

void func_809B4F90(EnKnight* this, PlayState* arg1) {
    Vec3f sp2C;
    s16 temp_v0;

    this->actionFunc = func_809B5058;
    temp_v0 = this->unk172 - this->actor.shape.rot.y;
    if (ABS_ALT(temp_v0) < 0x4000) {
        Animation_MorphToPlayOnce(&this->unk194, &D_06004974, 0.0f);
        this->unk_148 = 0;
    } else {
        Animation_MorphToPlayOnce(&this->unk194, &D_06000D9C, 0.0f);
        this->unk_148 = 1;
    }
    Matrix_RotateYS(this->unk172, MTXMODE_NEW);
    Matrix_MultVecZ(-15.0f, &sp2C);
    this->unk2A4 = sp2C.x;
    this->unk2A8 = sp2C.z;
    this->unk14A[0] = 10;
}

void func_809B5058(EnKnight* this, PlayState* play) {
    f32 rand = Rand_ZeroOne();

    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] == 0) {
        if (this == D_809BEFD0 && this->actor.xzDistToPlayer < 150.0f) {
            if (rand < 0.25f) {
                func_809B35BC(this, play);
            } else if (rand < 0.5f) {
                func_809B329C(this, play, 0);
            } else if (rand < 0.75f) {
                func_809B59FC(this, play);
            } else {
                func_809B3CD0(this, play);
            }
        } else if (this->unk_148 == 0) {
            func_809B3E9C(this, play);
        } else {
            func_809B4024(this, play, 0x6000);
        }
    }
    if (this == D_809BEFD0 && this->unk14A[0] < 4) {
        this->unk192 = 1;
    }
}

void func_809B51DC(EnKnight* this, PlayState* play) {
    Vec3f sp2C;
    s16 temp_v0;

    this->actionFunc = func_809B52E8;
    temp_v0 = this->unk172 - this->actor.shape.rot.y;
    if (ABS_ALT(temp_v0) < 0x4000) {
        Animation_MorphToPlayOnce(&this->unk194, &D_06001CDC, 0.0f);
        this->unk1D8 = 1.0f;
    } else {
        Animation_MorphToPlayOnce(&this->unk194, &D_06005D30, 0.0f);
        this->unk1D8 = -1.0f;
    }
    Matrix_RotateYS(this->unk172, MTXMODE_NEW);
    Matrix_MultVecZ(KREG(29) + -15.0f, &sp2C);
    this->unk2A4 = sp2C.x;
    this->unk2A8 = sp2C.z;
    this->unk14A[0] = 35;
    this->unk14A[1] = 150;
    this->actor.colChkInfo.damageTable = &D_809BDB24;
}

void func_809B52E8(EnKnight* this, PlayState* play) {
    s32 pad;
    f32 temp_fv0;
    f32 var_fv0;
    Vec3f sp40;
    CollisionPoly* sp3C;
    f32 temp_fv1;
    f32 temp;
    f32 temp_ft4;
    s16 var_v0;

    if (this->unk14A[0] < (s16)(KREG(6) + 25)) {
        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
        if (this == D_809BEFD0) {
            var_fv0 = -75.0f;
        } else {
            var_fv0 = -65.0f;
        }
        Matrix_MultVecZ((KREG(9) + 1.0f) * (var_fv0 * this->unk1D8), &sp40);
        sp40.x += this->actor.world.pos.x;
        sp40.y += this->actor.world.pos.y + 300.0f;
        sp40.z += this->actor.world.pos.z;
        temp_fv0 = BgCheck_EntityRaycastFloor1(&play->colCtx, &sp3C, &sp40);
        if (temp_fv0 > -10.0f && temp_fv0 != this->actor.floorHeight) {
            temp_fv1 = sp40.x - this->actor.world.pos.x;
            temp = temp_fv0 - this->actor.world.pos.y;
            temp_ft4 = sp40.z - this->actor.world.pos.z;
            Math_ApproachS(&this->actor.shape.rot.x,
                           Math_Atan2S(temp, sqrtf(SQ(temp_fv1) + SQ(temp_ft4))) * (s32)this->unk1D8, 1, 0x800);
        } else {
            Math_ApproachS(&this->actor.shape.rot.x, 0, 1, 0x800);
        }
    }
    if (this->unk14A[1] >= 0x78 && this->unk14A[1] < 0x8C) {
        if (this->unk14A[1] == 0x78) {
            D_809BEFE0 = NULL;
        } else {
            D_809BEFE0 = this;
        }
    }
    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    Math_ApproachZeroF(&this->unk180, 1.0f, 10.0f);
    if (this->unk1D8 > 0.0f) {
        var_v0 = 0x14;
    } else {
        var_v0 = KREG(8) + 8;
    }
    if (var_v0 == this->unk14A[0]) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
        this->actor.flags &= ~1;
        if (this->unk2A0 == 0xA) {
            this->unk2A2 = 0;
        }
    }
    if (this->unk14A[1] == 0 && D_809BEFD0->actionFunc != func_809B7950) {
        this->actor.flags |= 1;
        func_809B4BFC(this, play);
        if (this == D_809BEFD0) {
            this->actor.colChkInfo.health = 0xE - BREG(41);
        } else {
            this->actor.colChkInfo.health = 6 - BREG(40);
        }
        this->unk594.elements[0].info.bumperFlags &= ~2;
        this->unk594.elements[1].info.bumperFlags &= ~2;
        this->actor.colChkInfo.damageTable = &D_809BDB04;
        this->unk156 = 0x19;
    }
}

void func_809B5634(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B5698;
    this->unk14A[2] = 0x32;
    this->unk2A1 = 0x14;
    if (this == D_809BEFD0) {
        Audio_RestorePrevBgm();
    }
    Audio_PlaySfx_AtPos(&this->unk6C8, this->unk6C2);
}

void func_809B5698(EnKnight* this, PlayState* play) {
    Vec3f sp44;
    Vec3f sp38;
    s16 sp36;

    if (this->unk14A[2] >= 0xA && this->unk14A[2] < 0x28) {
        if (this->unk14A[2] == 0xA) {
            D_809BEFE0 = NULL;
        } else {
            D_809BEFE0 = this;
        }
    }
    if (this->unk14A[2] == 0) {
        this->unk152 = 0;
        this->actor.draw = NULL;
        this->actor.world.pos.y = 1000.0f;
        this->actor.world.pos.x = 1300.0f;
        this->actor.world.pos.z = 2864.0f;
        this->actor.gravity = 0.0f;
    }
    Math_ApproachZeroF(&this->actor.scale.y, 0.1f, 0.0015f);
    if (this->unk14A[2] != 0) {
        sp36 = (s32)Rand_ZeroFloat(14.9f);
        sp44 = D_809BDAF0;
        sp44.y = 0.03f;
        sp38.x = this->unk1DC[sp36].x + Rand_CenteredFloat(20.0f);
        sp38.y = this->unk1DC[sp36].y - 5.0f;
        sp38.z = this->unk1DC[sp36].z + Rand_CenteredFloat(20.0f);
        EffectSsKFire_Spawn(play, &sp38, &D_809BDAF0, &sp44, Rand_ZeroFloat(20.0f) + 20.0f, 0);
        Actor_PlaySfx(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
    }
    if (this->unk14A[2] == 0) {
        this->actor.flags &= ~1;
        if (this == D_809BEFD0) {
            if (CutsceneManager_IsNext(this->actor.csId)) {
                CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
                this->actionFunc = func_809B58D4;
            } else {
                CutsceneManager_Queue(this->actor.csId);
            }
        } else {
            this->actionFunc = func_809B58D4;
        }
        Actor_ChangeCategory(play, &play->actorCtx, &this->actor, 5);
        this->unk14A[0] = 30;
    }
}

void func_809B58D4(EnKnight* this, PlayState* play) {
    if (this == D_809BEFD0 && this->unk14A[0] == 0) {
        Actor_Kill(&this->actor);
        Actor_Kill(&D_809BEFD4->actor);
        Actor_Kill(&D_809BEFD8->actor);
    }
}

void func_809B592C(EnKnight* this, PlayState* play) {
    s32 var_s0;
    Vec3f sp28;

    this->actionFunc = func_809B5B08;
    Animation_MorphToPlayOnce(&this->unk194, &D_06002174, 0.0f);
    Matrix_RotateYS(this->unk172, MTXMODE_NEW);
    Matrix_MultVecZ(-15.0f, &sp28);
    this->unk2A4 = sp28.x;
    this->unk2A8 = sp28.z;
    this->actor.velocity.y = 7.5f;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        func_809B22CC(this, play, 0);
    }
    Actor_PlaySfx(&this->actor, NA_SE_EN_TEKU_JUMP);
    this->unk_148 = 0;
    this->unk156 = 0xA;
}

void func_809B59FC(EnKnight* this, PlayState* play) {
    s32 var_s0;
    Vec3f sp28;

    this->actionFunc = func_809B5B08;
    Animation_MorphToPlayOnce(&this->unk194, &D_06002174, 0.0f);
    Matrix_RotateYS(this->unk172, MTXMODE_NEW);
    Matrix_MultVecZ(KREG(90) + 14.0f, &sp28);
    this->unk2A4 = sp28.x;
    this->unk2A8 = sp28.z;
    this->actor.velocity.y = KREG(91) + 13.0f;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        func_809B22CC(this, play, 0);
    }
    Actor_PlaySfx(&this->actor, NA_SE_EN_MIBOSS_JUMP1);
    this->unk_148 = 1;
    this->unk156 = 0x14;
}

void func_809B5B08(EnKnight* this, PlayState* play) {
    if (this->unk_148 == 1) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_MIBOSS_JUMP2 - SFX_FLAG);
    }

    SkelAnime_Update(&this->unk194);
    this->actor.speed = 0.0f;

    if (this == D_809BEFD0) {
        Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0x1000);
        if (this->unk156 == 0xD) {
            if (this->unk_148 == 1) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_LAUGH_DEMO);
            } else {
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_CYNICAL);
            }
        }
    }

    if (this->actor.velocity.y <= 0.0f && (this->actor.bgCheckFlags & 1)) {
        this->unk2A4 = this->unk2A8 = 0.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        if (this->unk_148 == 1) {
            if (this->unk162 != 0) {
                if (Rand_ZeroOne() < 0.5f) {
                    func_809B3A7C(this, play);
                } else {
                    func_809B329C(this, play, 0);
                }
            } else if (Rand_ZeroOne() < 0.5f) {
                func_809B3A7C(this, play);
            } else {
                func_809B6EC8(this, play);
            }
        } else if (this == D_809BEFD0 && Rand_ZeroOne() < 0.3f) {
            if (Rand_ZeroOne() < 0.5f || this->unk162 != 0) {
                func_809B3A7C(this, play);
            } else {
                func_809B6EC8(this, play);
            }
        } else {
            func_809B3E9C(this, play);
        }
    }
}

void func_809B5D38(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B5D54;
    this->unk_148 = 0;
}

void func_809B5D54(EnKnight* this, PlayState* play) {
    this->unk_680 = 1;
    if (this->unk_148 != 0) {
        SkelAnime_Update(&this->unk194);
    }
    switch (this->unk_148) {
        case 0:
            break;
        case 1:
            if (this->unk290 == 0) {
                Animation_MorphToPlayOnce(&this->unk194, &D_060009E0, 0.0f);
            } else {
                Animation_MorphToPlayOnce(&this->unk194, &D_060005A8, 0.0f);
            }
            Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_STAND);
            this->unk290 = 1 - this->unk290;
            this->unk_148 = 2;
            this->unk14A[0] = 2;
            /* fallthrough */
        case 2:
            if (this->unk14A[0] == 1) {
                if (this->unk290 == 0) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SHOCK);
                } else {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SHIT);
                }
            }
            if (this->unk_151 == 0) {
                func_809B6528(this, play);
                this->unk194.curFrame = 25.0f;
            }
            break;
    }
    this->unk18A = 0;
    this->unk184 = this->unk186 = this->unk188 = this->unk18A;
}

void func_809B5E90(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B5ED0;
    Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
}

void func_809B5ED0(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);

    if (D_809BEFE0 == NULL) {
        func_809B3E9C(this, play);
    } else {
        f32 dx = D_809BEFE0->actor.focus.pos.x - this->actor.world.pos.x;
        f32 dz = D_809BEFE0->actor.focus.pos.z - this->actor.world.pos.z;
        s16 temp_v1 = Math_FAtan2F(dz, dx) - this->actor.shape.rot.y;

        if (temp_v1 > 0x3800) {
            this->unk186 = 0x3800;
        } else if (temp_v1 < -0x3800) {
            this->unk186 = -0x3800;
        } else {
            this->unk186 = temp_v1;
        }
        this->unk18C = 0x3000;
        this->unk18E = 2;
    }
}

void func_809B5FA8(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B601C;
    Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
    this->unk_148 = 0;
    this->unk14A[0] = Rand_ZeroFloat(10.0f) + 65.0f;
}

void func_809B601C(EnKnight* this, PlayState* play) {
    f32 dx;
    f32 dz;
    s16 temp_v1_2;
    EnKnight* var_t0;
    Player* sp2C = GET_PLAYER(play);

    SkelAnime_Update(&this->unk194);

    var_t0 = (this == D_809BEFD4) ? D_809BEFD8 : D_809BEFD4;

    switch (this->unk_148) {
        case 0:
            Math_ApproachS(&this->actor.world.rot.y, this->unk172, 2, 0x500);
            Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
            if (this->unk14A[0] < 0x28 && this->unk14A[0] >= 0x10) {
                dx = var_t0->actor.focus.pos.x - this->actor.world.pos.x;
                dz = var_t0->actor.focus.pos.z - this->actor.world.pos.z;
                temp_v1_2 = Math_FAtan2F(dz, dx) - this->actor.shape.rot.y;

                if (temp_v1_2 > 0x3800) {
                    this->unk186 = 0x3800;
                } else if (temp_v1_2 < -0x3800) {
                    this->unk186 = -0x3800;
                } else {
                    this->unk186 = temp_v1_2;
                }

                this->unk18C = 0x3000;
                this->unk18E = 2;
            } else {
                this->unk186 = 0;
            }

            if (this->unk14A[0] == 0 && func_801A46F8() == 1) {
                Animation_MorphToLoop(&this->unk194, &D_0600DDCC, -3.0f);
                this->unk_148 = 1;
                this->unk14A[0] = 0xC8;
            }

            if (!(sp2C->stateFlags3 & PLAYER_STATE3_20000000)) {
                this->unk_148 = 2;
                this->unk14A[0] = 0xA;
            }
            break;
        case 1:
            this->actor.speed = KREG(38) + 1.0f;

            if (this == D_809BEFD4) {
                this->actor.world.rot.y = (this->actor.world.rot.y + KREG(39) * 0x100) + 0x100;
            } else {
                this->actor.world.rot.y = (this->actor.world.rot.y - KREG(39) * 0x100) - 0x100;
            }

            if (this->unk14A[0] == 0 || !(sp2C->stateFlags3 & PLAYER_STATE3_20000000)) {
                this->unk_148 = 2;
                this->unk14A[0] = 0xA;
            }
            goto block_29;
        case 2:
            if (this->unk14A[0] == 0) {
                func_809B3E9C(this, play);
            }
            goto block_29;

        block_29:
            if (Animation_OnFrame(&this->unk194, KREG(53) + 1.0f) ||
                Animation_OnFrame(&this->unk194, KREG(54) + 11.0f)) {
                Actor_PlaySfx(&this->actor, this->unk6B4);
            }
            break;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x500);
}

void func_809B631C(EnKnight* this, PlayState* play) {
    if (this == D_809BEFD0) {
        this->actionFunc = func_809B8458;
        Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
    } else {
        this->actionFunc = func_809B842C;
    }
    this->actor.world.pos.y = 1000.0f;
}

void func_809B638C(EnKnight* this, PlayState* play, s16 arg2) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s16 var_a1;

    Math_Vec3f_Copy(&sp4C, &this->unk434);
    Matrix_RotateYS(this->unk184 + this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->actor.shape.rot.x + arg2, MTXMODE_APPLY);
    Matrix_MultVecZ(BREG(48) + 20.0f, &sp40);
    var_a1 = (this->unk14A[0] < 0x28) ? 0 : 0xC8;
    Math_ApproachS(&this->unk160, var_a1, 1, 5);
    if (this->unk160 >= 0x3D) {
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FREEZAD_BREATH - SFX_FLAG);
    }
    sp34.x = sp34.y = sp34.z = 0.0f;
    func_809B20F0(play, &sp4C, &sp40, &sp34, 2.0f, 25.0f, this->unk160);
    sp4C.x -= sp40.x * 0.5f;
    sp4C.y -= sp40.y * 0.5f;
    sp4C.z -= sp40.z * 0.5f;
    func_809B20F0(play, &sp4C, &sp40, &sp34, 2.0f, 25.0f, this->unk160);
}

void func_809B6528(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_0600A530, -5.0f);
    this->actionFunc = func_809B6764;
    this->unk_148 = 0;
}

void func_809B6574(PlayState* play, u8 arg1) {
    Player* player = GET_PLAYER(play);
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;
    u8 var_s1;

    for (var_s1 = 0; var_s1 < arg1; var_s1++) {
        spA4.x = Rand_CenteredFloat(3.0f);
        spA4.y = Rand_ZeroFloat(2.0f) + 1.0f;
        spA4.z = Rand_CenteredFloat(3.0f);
        sp98.x = sp98.z = 0.0f;
        sp98.y = -0.1f;
        spB0.x = player->actor.world.pos.x + Rand_CenteredFloat(30.0f);
        spB0.y = player->actor.world.pos.y + 20.0f + Rand_CenteredFloat(30.0f);
        spB0.z = player->actor.world.pos.z + Rand_CenteredFloat(30.0f);
        func_800B0EB0(play, &spB0, &spA4, &sp98, &D_809BDCF0, &D_809BDCF4, Rand_ZeroFloat(50.0f) + 100.0f, 0xA,
                      Rand_ZeroFloat(5.0f) + 14.0f);
    }
}

void func_809B6764(EnKnight* this, PlayState* play) {
    s16 temp_v1;
    s16 sp54 = 0;
    Player* player = GET_PLAYER(play);
    Vec3f sp44;
    Vec3f sp38;

    SkelAnime_Update(&this->unk194);

    temp_v1 = this->unk172 - this->actor.shape.rot.y;
    if (temp_v1 > 0x3800) {
        this->unk186 = 0x3800;
    } else if (temp_v1 < -0x3800) {
        this->unk186 = -0x3800;
    } else {
        this->unk186 = temp_v1;
    }

    switch (this->unk_148) {
        case 0:
            if (this->actor.xzDistToPlayer < 35.0f) {
                if (player->actor.world.pos.z < this->actor.world.pos.z) {
                    this->unk_148 = 1;
                } else {
                    this->unk_148 = 5;
                }
                this->unk14A[0] = 8;
                Actor_PlaySfx(&this->actor, this->unk6BC);
            }
            if (player->unk_D57 == 4 && func_809B31E8(this, play) != 0) {
                this->unk_148 = 0xA;
                Animation_MorphToPlayOnce(&this->unk194, &D_06008524, 0.0f);
                this->unk1D8 = Animation_GetLastFrame(&D_06008524);
            }
            break;
        case 1:
            if (this->unk14A[0] == 0) {
                this->unk_148++;
                this->unk14A[0] = 0x14;
            } else {
                Math_ApproachS(&this->unk17A, 0x3C00, 1, 0x1770);
                Math_ApproachS(&this->unk176, 0x1400, 1, 0x1770);
                if (this->unk14A[0] == 7) {
                    sp54 = -0x2000;
                }
                break;
            }
        case 2:
            Math_ApproachS(&this->unk17A, 0, 1, 0xBB8);
            Math_ApproachS(&this->unk176, 0, 1, 0xBB8);
            if (this->unk14A[0] == 0) {
                this->unk_148 = 0;
            }
            break;
        case 5:
            if (this->unk14A[0] == 0) {
                this->unk_148++;
                this->unk14A[0] = 0x14;
            } else {
                Math_ApproachS(&this->unk178, 0x3C00, 1, 0x1770);
                Math_ApproachS(&this->unk174, 0x1400, 1, 0x1770);
                if (this->unk14A[0] == 7) {
                    sp54 = 0x2000;
                }
                break;
            }
        case 6:
            Math_ApproachS(&this->unk178, 0, 1, 0xBB8);
            Math_ApproachS(&this->unk174, 0, 1, 0xBB8);
            if (this->unk14A[0] == 0) {
                this->unk_148 = 0;
            }
            break;
        case 10:
            if (Animation_OnFrame(&this->unk194, this->unk1D8) != 0) {
                this->unk_148 = 0xB;
                Animation_MorphToPlayOnce(&this->unk194, &D_060089E4, 0.0f);
                this->unk1D8 = Animation_GetLastFrame(&D_060089E4);
            }
            break;
        case 11:
            if (Animation_OnFrame(&this->unk194, this->unk1D8) != 0) {
                Animation_MorphToPlayOnce(&this->unk194, &D_0600A530, -15.0f);
                this->unk_148 = 0;
            }
            break;
    }

    if (this->unk_148 >= 0xA) {
        sp44.x = this->actor.world.pos.x + 40.0f;
        sp44.y = this->actor.world.pos.y + 70.0f;
        sp44.z = this->actor.world.pos.z;
        func_809B21F4(this, 0, &this->unk534, &sp44);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk534.base);
    }

    if (D_809BEFD4->actor.draw == NULL && D_809BEFD8->actor.draw == NULL) {
        func_809B7190(this, play);
        this->unk17A = this->unk178 = this->unk176 = this->unk174 = 0;
    }

    if (sp54 != 0) {
        Math_Vec3f_Copy(&sp38, &player->actor.world.pos);
        sp38.y += 25.0f;
        EffectSsHitmark_SpawnFixedScale(play, 0, &sp38);
        func_800B8D50(play, NULL, KREG(53) + 12.0f, this->actor.shape.rot.y + sp54, KREG(54) + 7.0f, 0x10);
        func_809B6574(play, 0xC);
        Actor_PlaySfx(&this->actor, NA_SE_EV_BLOCK_SHAKE);
    }
}

void func_809B6C04(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_06003008, -5.0f);
    this->actionFunc = func_809B6C54;
    this->unk14A[0] = 0x32;
}

void func_809B6C54(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
    if (Animation_OnFrame(&this->unk194, 19.0f)) {
        this->unk162 = 1;
        D_809BEFDC = (EnKnight*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KNIGHT, this->actor.world.pos.x,
                                            this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                            this->actor.shape.rot.y, this->actor.shape.rot.z, 0x64);
        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HEAD_SHORT);
    }
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    if (this->unk14A[0] == 0) {
        func_809B3E9C(this, play);
        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_LAUGH_DEMO);
    }
}

void func_809B6D38(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_060079D4, -10.0f);
    this->actionFunc = func_809B6D94;
    this->unk_148 = 0;
    this->unk14A[0] = 0x3C;
    this->unk194.playSpeed = 0.0f;
}

void func_809B6D94(EnKnight* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->unk156 = 5;
    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);

    switch (this->unk_148) {
        case 1:
            this->unk_148 = 2;
            this->unk14A[0] = 0x28;
            this->unk194.playSpeed = 1.0f;
            /* fallthrough */
        case 2:
            if (this->unk14A[0] == 0x22) {
                this->unk162 = 0;
                Actor_Kill(&D_809BEFDC->actor);
                D_809BEFDC = NULL;
                this->actor.flags |= 1;
                player->lockOnActor = &this->actor;
                play->actorCtx.targetCtx.arrowPointedActor = &this->actor;
                play->actorCtx.targetCtx.lockOnActor = &this->actor;
            }
            if (this->unk14A[0] == 0xF) {
                func_809B3E9C(this, play);
                this->unk14A[2] = Rand_ZeroFloat(100.0f) + 150.0f;
            }
            /* fallthrough */
        case 0:
            return;
    }
}

void func_809B6EC8(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_06009538, -5.0f);
    this->unk1D8 = Animation_GetLastFrame(&D_06009538);
    this->actionFunc = func_809B6F40;
    this->unk_148 = 0;
    this->unk14A[0] = KREG(57) + 0x96;
    this->unk160 = 0;
}

void func_809B6F40(EnKnight* this, PlayState* play) {
    s16 temp_v0;

    SkelAnime_Update(&this->unk194);
    Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
    Math_ApproachS(&this->actor.world.rot.y, this->unk172, 5, 0x500);

    temp_v0 = this->unk172 - this->actor.shape.rot.y;
    if (ABS_ALT(temp_v0) < 0x6000) {
        if (temp_v0 > 0x3800) {
            this->unk186 = 0x3800;
        } else if (temp_v0 < -0x3800) {
            this->unk186 = -0x3800;
        } else {
            this->unk186 = temp_v0;
        }
    }

    switch (this->unk_148) {
        case 0:
            if (Animation_OnFrame(&this->unk194, this->unk1D8) != 0) {
                this->unk_148 = 1;
                Animation_MorphToLoop(&this->unk194, &D_06008D80, 0.0f);
            }
            func_809B638C(this, play, 0x1600);
            break;
        case 1:
            func_809B638C(this, play, 0x1600);
            if (KREG(21) == 0) {
                this->unk186 =
                    Math_SinS((KREG(84) + 0x11DC) * this->unk146) * (KREG(85) * 0x800 + 0x1800) + this->unk186;
            }
            if (this->unk14A[0] == 0) {
                this->unk_148 = 2;
                Animation_MorphToPlayOnce(&this->unk194, &D_0600E15C, -5.0f);
                this->unk1D8 = Animation_GetLastFrame(&D_0600E15C);
            }
            break;
        case 2:
            func_809B638C(this, play, 0x1600);
            if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
                func_809B3E9C(this, play);
                this->unk14A[2] = Rand_ZeroFloat(150.0f) + 150.0f;
            }
            break;
    }

    this->unk192 = 1;
}

void func_809B7190(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809B71DC;
    this->unk684 = 0;
    this->unk688 = 0;
    this->unk6A4 = 0.0f;
    AudioSeq_QueueSeqCmd(0x101400FF);
}

void func_809B71DC(EnKnight* this, PlayState* play) {
    f32 temp_fa0;
    Camera* sp30;
    f32 temp_fv0;

    this->unk684++;
    SkelAnime_Update(&this->unk194);

    switch (this->unk688) {
        case 0:
            if (CutsceneManager_GetCurrentCsId() != -1) {
                break;
            }
            Cutscene_StartManual(play, &play->csCtx);
            Player_SetCsActionWithHaltedActors(play, &this->actor, 7);
            this->unk_68A = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, 0, 1);
            Play_ChangeCameraStatus(play, this->unk_68A, 7);
            this->actor.flags &= ~1;
            this->unk684 = 0;
            this->unk688 = 1;
            this->unk68C.x = 1342.0f;
            this->unk68C.y = 56.0f;
            this->unk68C.z = 2810.0f;
            this->unk698.x = 1400.0f;
            this->unk698.y = 57.0f;
            this->unk698.z = 2870.0f;
            this->unk6B0 = 60.0f;
            /* Fallthrough */
        case 1:
            if (this->unk684 == (u32)(sREG(64) + 0xD)) {
                Animation_MorphToPlayOnce(&this->unk194, &D_06009D8C, sREG(65));
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_STAND);
            }
            if (this->unk684 != (u32)(sREG(66) + 0x17)) {
                break;
            }
            this->unk68C.x = 1253.0f;
            this->unk68C.y = 79.0f;
            this->unk68C.z = 2903.0f;
            this->unk698.x = 1354.0f;
            this->unk698.y = 83.0f;
            this->unk698.z = 2865.0f;
            Animation_MorphToPlayOnce(&this->unk194, &D_06009D8C, 0.0f);
            this->unk684 = 0;
            this->unk688 = 2;
            /* Fallthrough */
        case 2:
            this->unk6A4 = sREG(67) * 0.001f + 0.05f;
            Math_ApproachF(&this->unk698.y, 119.0f, 0.2f, this->unk6A4 * 36.0f);
            if (this->unk684 >= (u32)(sREG(68) + 0xA)) {
                if (this->unk684 == (u32)(sREG(68) + 0xA)) {
                    this->unk14A[1] = 0x11;
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SWORD);
                }

                temp_fv0 = Math_SinS(this->unk14A[1] * 0x6000);
                temp_fa0 = (temp_fv0 * this->unk14A[1] * 0.0175f) + (this->unk14A[1] * 0.0175f) + 1.0f;

                Math_ApproachF(&this->unk46C, temp_fa0, 1.0f, 0.5f);
                Math_ApproachF(&this->unk470, temp_fa0, 1.0f, 0.5f);
            }
            if (this->unk684 == (u32)(sREG(69) + 0x32)) {
                Animation_MorphToPlayOnce(&this->unk194, &D_06008390, sREG(65) + -10.0f);
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_ATTACK_K);
            }
            if (this->unk684 >= (u32)(sREG(69) + 0x32)) {
                Math_ApproachF(&this->unk6B0, sREG(70) + 40.0f, 0.2f, sREG(71) * 0.1f + 3.0f);
            }
            if (this->unk684 >= (u32)(sREG(72) + 0x5A)) {
                sp30 = Play_GetCamera(play, 0);
                this->unk688 = 0;
                func_809B3E9C(this, play);
                this->unk14A[2] = 0x12C;
                this->unk152 = 1;
                this->actor.flags |= 1;
                this->actor.gravity = -1.5f;
                sp30->eye = this->unk68C;
                sp30->eyeNext = this->unk68C;
                sp30->at = this->unk698;
                func_80169AFC(play, this->unk_68A, 0);
                this->unk_68A = 0;
                Cutscene_StopManual(play, &play->csCtx);
                Player_SetCsActionWithHaltedActors(play, &this->actor, 6);
                D_809BDB00 = 1;
            }
            break;
    }

    if (this->unk_68A != 0) {
        ShrinkWindow_SetLetterboxTarget(27);
        Play_SetCameraAtEye(play, this->unk_68A, &this->unk698, &this->unk68C);
        Play_SetCameraFov(play, this->unk_68A, this->unk6B0);
    }
}

void func_809B7708(EnKnight* this, PlayState* play) {
    if (this->actionFunc != func_809B52E8 && this->actionFunc != func_809B5698 && this->actionFunc != func_809B58D4) {
        Animation_MorphToLoop(&this->unk194, &D_060040E0, -5.0f);
        this->actionFunc = func_809B7778;
    }
}

void func_809B7778(EnKnight* this, PlayState* play) {
    Vec3f sp2C;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->unk194);
    this->unk186 = 0;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.speed = 0.0f;
    if (D_809BEFD0->unk_148 == 0) {
        if (this == D_809BEFD4) {
            Matrix_RotateYS(D_809BEFD0->actor.shape.rot.y + 0x1400, MTXMODE_NEW);
        } else {
            Matrix_RotateYS(D_809BEFD0->actor.shape.rot.y - 0x1400, MTXMODE_NEW);
        }
        Matrix_MultVecZ((KREG(19) + 350.0f) - 220.0f, &sp2C);
        this->actor.world.pos.x = player->actor.world.pos.x + sp2C.x;
        this->actor.world.pos.z = player->actor.world.pos.z + sp2C.z;
    }
    if (D_809BEFD0->actionFunc != func_809B7950) {
        func_809B3E9C(this, play);
    }
}

void func_809B78A4(EnKnight* this, PlayState* play) {
    this->unk684 = 0;
    this->unk688 = 0;
    this->unk6A4 = 0.0f;
    AudioSeq_QueueSeqCmd(0x100A00FF);
    if (this->actionFunc != func_809B6764) {
        this->unk_148 = 1;
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    } else {
        this->unk_148 = 0;
    }
    func_809B7708(D_809BEFD4, play);
    func_809B7708(D_809BEFD8, play);
    this->unk424 = this->actionFunc;
    this->actionFunc = func_809B7950;
}

void func_809B7950(EnKnight* this, PlayState* play) {
    Vec3f sp44;
    Player* sp40 = GET_PLAYER(play);
    Camera* var_v1;
    s32 pad;

    this->unk186 = 0;
    this->actor.speed = 0.0f;
    this->unk684 += 1;
    this->unk2A4 = 0.0f;
    this->unk2A8 = 0.0f;

    SkelAnime_Update(&this->unk194);

    switch (this->unk688) {
        case 0:
            if (CutsceneManager_GetCurrentCsId() == -1) {
                Cutscene_StartManual(play, &play->csCtx);
                Player_SetCsActionWithHaltedActors(play, &this->actor, 7);
                this->unk_68A = Play_CreateSubCamera(play);
                Play_ChangeCameraStatus(play, 0, 1);
                Play_ChangeCameraStatus(play, this->unk_68A, 7);
                this->actor.flags &= ~1;
                this->unk684 = 0;
                this->unk688 = 1;
                this->unk6B0 = 60.0f;
                if (this->unk424 == func_809B6764) {
                    Animation_MorphToPlayOnce(&this->unk194, &D_0600EA90, 0.0f);
                } else {
                    Animation_MorphToPlayOnce(&this->unk194, &D_0600E7F4, 0.0f);
                }
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_STAND);
                case 1:
                    Matrix_RotateYS(KREG(29) + this->actor.shape.rot.y + 0x1B58, MTXMODE_NEW);
                    Matrix_MultVecZ(KREG(16) + 90.0f, &sp44);

                    this->unk68C.x = this->actor.world.pos.x + sp44.x;
                    this->unk68C.y = this->actor.world.pos.y + KREG(17) + 40.0f;
                    this->unk68C.z = this->actor.world.pos.z + sp44.z;

                    this->unk698.x = this->actor.focus.pos.x;
                    this->unk698.y = this->actor.focus.pos.y + KREG(18) - 10.0f;
                    this->unk698.z = this->actor.focus.pos.z;

                    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);

                    sp40->actor.world.rot.y = sp40->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;

                    Matrix_MultVecZ((KREG(19) + 350.0f) - 220.0f, &sp44);

                    sp40->actor.world.pos.x = this->actor.world.pos.x + sp44.x;
                    sp40->actor.world.pos.z = this->actor.world.pos.z + sp44.z;

                    if (this->unk684 == (u32)(KREG(31) + 0x19)) {
                        this->unk688 = 2;
                        this->unk684 = 0;
                        this->unk6A4 = KREG(20) + 80.0f;
                    }
            }
            break;
        case 2:
            Matrix_RotateYS(sp40->actor.shape.rot.y, MTXMODE_NEW);
            Matrix_RotateXS(KREG(26) - 0x7D0, MTXMODE_APPLY);
            Matrix_MultVecZ(this->unk6A4, &sp44);
            if (this->unk684 >= 0x1A) {
                Math_ApproachF(&this->unk6A4, 40.0f, 0.2f, 2.0f);
            }

            this->unk68C.x = sp40->actor.world.pos.x + sp44.x;
            this->unk68C.y = KREG(21) + (sp40->actor.world.pos.y + sp44.y) + 44.0f;
            this->unk68C.z = sp40->actor.world.pos.z + sp44.z;

            this->unk698.x = sp40->actor.world.pos.x;
            this->unk698.y = (sp40->actor.world.pos.y + KREG(22) + 44.0f) - 5.0f;
            this->unk698.z = sp40->actor.world.pos.z;

            if (this->unk684 == (u32)(KREG(48) + 0x55)) {
                this->unk688 = 3;
                this->unk684 = 0;
                this->unk1D8 = 1000.0f;
            }
            break;
        case 3:
            if (this->unk684 == 7) {
                if (this->unk424 == func_809B6764) {
                    Animation_MorphToPlayOnce(&this->unk194, &D_06006EF8, 0.0f);
                    this->unk1D8 = Animation_GetLastFrame(&D_06006EF8);
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_STAND_RAPID);
                } else {
                    Animation_MorphToPlayOnce(&this->unk194, &D_06006754, 0.0f);
                    this->unk1D8 = Animation_GetLastFrame(&D_06006754);
                }
                Message_StartTextbox(play, 0x153E, NULL);
            }

            Matrix_RotateYS(KREG(29) + this->actor.shape.rot.y + 0x1B58, MTXMODE_NEW);
            Matrix_MultVecZ(KREG(16) + 90.0f, &sp44);

            this->unk68C.x = this->actor.world.pos.x + sp44.x;
            this->unk68C.y = this->actor.world.pos.y + KREG(17) + 40.0f;
            this->unk68C.z = this->actor.world.pos.z + sp44.z;

            if (this->unk684 < (u32)(KREG(24) + 0x23)) {
                this->unk698.x = this->actor.focus.pos.x;
                this->unk698.y = this->actor.focus.pos.y + KREG(18) - 10.0f;
                this->unk698.z = this->actor.focus.pos.z;
            }

            if (Animation_OnFrame(&this->unk194, this->unk1D8) != 0) {
                Animation_MorphToLoop(&this->unk194, &D_0600C7F0, 0.0f);
                this->unk1D8 = 1000.0f;
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HAND);
            }

            if (this->unk684 == (u32)(KREG(25) + 0x78)) {
                this->unk688 = 4;
                this->unk684 = 0;
                Animation_MorphToPlayOnce(&this->unk194, &D_0600C7F0, 0.0f);
            }
            break;
        case 4:
            Matrix_RotateYS(KREG(29) * 0x100 + this->actor.shape.rot.y + 0x2400, MTXMODE_NEW);
            Matrix_MultVecZ(KREG(16) + 230.0f, &sp44);

            this->unk68C.x = this->actor.world.pos.x + sp44.x;
            this->unk68C.y = this->actor.world.pos.y + KREG(17) + 40.0f;
            this->unk68C.z = this->actor.world.pos.z + sp44.z;

            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
            Matrix_MultVecZ(KREG(49) + 65.0f, &sp44);

            this->unk698.x = this->actor.world.pos.x + sp44.x;
            this->unk698.y = (this->actor.world.pos.y + KREG(50) + 50.0f) - 20.0f;
            this->unk698.z = this->actor.world.pos.z + sp44.z;

            if (this->unk684 == 0x3C) {
                Message_StartTextbox(play, 0x153FU, NULL);
            }
            if (this->unk684 == (u32)(BREG(16) + 0x78)) {
                Message_CloseTextbox(play);
            }
            if (this->unk684 == (u32)(BREG(17) + 0xA0)) {
                Message_StartTextbox(play, 0x1542, NULL);
                Animation_MorphToLoop(&this->unk194, &D_0600A88C, 0.0f);
            }
            if (this->unk684 == (u32)(BREG(18) + 0xAA)) {
                Player_SetCsActionWithHaltedActors(play, &this->actor, 4);
            }
            if ((this->unk684 >= 0x9D) && (this->unk684 < 0xDD)) {
                if (!(this->unk684 & 1)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_WALK);
                }
                if (!(this->unk684 & 3)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SIT);
                }
            }
            if (this->unk684 == (u32)(BREG(19) + 0xDC)) {
                Animation_MorphToPlayOnce(&this->unk194, &D_06021E34, -3.0f);
            }
            if (this->unk684 == (u32)(BREG(20) + 0xE6)) {
                Message_StartTextbox(play, 0x1540, NULL);
            }
            if (this->unk684 == (u32)(BREG(20) + 0xF0)) {
                Animation_MorphToLoop(&this->unk194, &D_06005E78, 0.0f);
            }

            if (this->unk684 == (u32)(BREG(21) + 0x140)) {
                if (this->unk424 == func_809B6764) {
                    Animation_MorphToPlayOnce(&this->unk194, &D_0601024C, 0.0f);
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SIT);
                } else {
                    Animation_MorphToPlayOnce(&this->unk194, &D_0602105C, 0.0f);
                }
                Message_CloseTextbox(play);
            }

            if (this->unk684 >= (u32)(BREG(22) + 0x154)) {
                var_v1 = Play_GetCamera(play, 0);

                this->unk688 = 0;
                if (this->unk424 == func_809B6764) {
                    func_809B6528(this, play);
                    this->unk194.curFrame = 25.0f;
                } else {
                    func_809B3E9C(this, play);
                    this->actor.flags |= 1;
                }

                var_v1->eye = this->unk68C;
                var_v1->eyeNext = this->unk68C;
                var_v1->at = this->unk698;

                func_80169AFC(play, this->unk_68A, 0);
                this->unk_68A = 0;
                Cutscene_StopManual(play, &play->csCtx);
                Player_SetCsActionWithHaltedActors(play, &this->actor, 6);
                D_809BDB00 = 5;
            }
            break;
    }

    if (this->unk_68A != 0) {
        ShrinkWindow_SetLetterboxTarget(27);
        Play_SetCameraAtEye(play, this->unk_68A, &this->unk698, &this->unk68C);
        Play_SetCameraFov(play, this->unk_68A, this->unk6B0);
    }
}

void func_809B842C(EnKnight* this, PlayState* play) {
    SkelAnime_Update(&this->unk194);
}

void func_809B8458(EnKnight* this, PlayState* play) {
    f32 sp64 = 0.0f;
    Player* sp60 = GET_PLAYER(play);
    Camera* temp_v0_2;
    Vec3f sp50;
    Vec3f sp44;
    f32 temp_fv1;

    this->unk684++;
    SkelAnime_Update(&this->unk194);

    switch (this->unk688) {
        case 0:
            if (Flags_GetClear(play, play->roomCtx.curRoom.num) || (CutsceneManager_GetCurrentCsId() != -1) ||
                !(sp60->actor.world.pos.x >= 870.0f)) {
                break;
            }

            Cutscene_StartManual(play, &play->csCtx);
            Player_SetCsActionWithHaltedActors(play, &this->actor, 7);
            this->unk_68A = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, 0, 1);
            Play_ChangeCameraStatus(play, this->unk_68A, 7);
            this->actor.flags &= ~1;
            this->unk684 = 0;
            this->unk688 = 1;
            this->unk6B0 = 60.0f;
            this->unk68C.x = 621.0f;
            this->unk68C.y = 54.0f;
            this->unk68C.z = 2865.0f;
            this->unk698.x = 661.0f;
            this->unk698.y = 110.0f;
            this->unk698.z = 2939.0f;
            AudioSeq_QueueSeqCmd(0x105000FF);
            /* Fallthrough */
        case 1:
            sp60->actor.world.pos.x = 870.0f;
            sp60->actor.world.pos.z = 2865.0f;
            this->unk6AC = 0x4000;
            this->unk68C.x = sp60->actor.world.pos.x + BREG(16) + 100.0f;
            this->unk68C.y = sp60->actor.world.pos.y + BREG(17) + 20.0f;
            this->unk68C.z = sp60->actor.world.pos.z + BREG(18);
            this->unk698.x = sp60->actor.world.pos.x + BREG(19);
            this->unk698.y = sp60->actor.world.pos.y + BREG(20) + 40.0f;
            this->unk698.z = sp60->actor.world.pos.z + BREG(21);

            if (this->unk684 >= (u32)(BREG(22) + 0x14)) {
                sp64 = 0.5f;
                Audio_PlaySfx(NA_SE_EV_EARTHQUAKE - SFX_FLAG);
            }

            if (this->unk684 == (u32)(BREG(22) + 0x1E)) {
                Player_SetCsActionWithHaltedActors(play, &this->actor, 0x15);
            }

            if (this->unk684 == (u32)(BREG(22) + 0x32)) {
                Message_StartTextbox(play, 0x1518, NULL);
            }

            if (this->unk684 != (u32)(BREG(23) + 0x96)) {
                break;
            }

            Message_CloseTextbox(play);

            this->unk688 = 2;
            this->unk684 = 0;
            this->unk_153 = 1;
            play->envCtx.lightSettingOverride = 1;
            play->envCtx.lightBlendOverride = 0;
            D_809BEFD0->unk_154 = 0;
            /* Fallthrough */
        case 2:
            this->unk_144 = 0x8000;

            if (this->unk684 == 10) {
                Player_SetCsActionWithHaltedActors(play, &this->actor, 4);
            }

            if (this->unk684 >= 10) {
                Math_ApproachS(&this->unk6AC, 0, 2, 0x1000);
            }

            this->unk68C.x = 896.0f;
            this->unk68C.y = 4.0f;
            this->unk68C.z = 2752.0f;
            this->unk698.x = 894.0f;
            this->unk698.y = 46.0f;
            this->unk698.z = 2860.0f;

            if (this->unk684 == (u32)(BREG(65) + 0x28)) {
                Message_StartTextbox(play, 0x1519, NULL);
            }
            if ((u32)(BREG(94) + 0x82) >= this->unk684) {
                sp64 = 0.5f;
                Audio_PlaySfx(NA_SE_EV_EARTHQUAKE - SFX_FLAG);
            }
            if (this->unk684 == (u32)(BREG(65) + 0x8C)) {
                Message_CloseTextbox(play);
            }
            if (this->unk684 == (u32)(BREG(65) + 0xAA)) {
                Message_StartTextbox(play, 0x151AU, NULL);
            }
            if ((this->unk684 >= 0xAA) && (this->unk684 < 0xBF)) {
                this->unk430 = KREG(42) + 200.0f;
            }
            if ((this->unk684 == 0x00000096) || (this->unk684 == 0x000000B4)) {
                Actor_PlaySfx(&this->actor, this->unk6B4);
            }

            if (this->unk684 != (u32)(BREG(24) + 0xBE)) {
                break;
            }

            this->unk688 = 3;
            this->unk684 = 0;
            Player_SetCsActionWithHaltedActors(play, &this->actor, 0x85);
            /* Fallthrough */
        case 3:
            Math_ApproachS(&this->unk6AC, 0x4000, 2, 0x1000);
            if (this->unk684 != (u32)(BREG(26) + 0xF)) {
                break;
            }
            this->unk688 = 4;
            this->unk684 = 0;
            Animation_MorphToPlayOnce(&this->unk194, &D_06010E98, 0.0f);
            this->unk1D8 = Animation_GetLastFrame(&D_06010E98);
            /* Fallthrough */
        case 4:
            this->unk6A4 = BREG(29) * 0.01f + 0.1f;
            Math_ApproachF(&this->unk68C.x, 1076.0f, 0.5f, this->unk6A4 * 180.0f);
            Math_ApproachF(&this->unk68C.y, 20.0f, 0.5f, this->unk6A4 * 16.0f);
            Math_ApproachF(&this->unk68C.z, 2741.0f, 0.5f, this->unk6A4 * 11.0f);
            Math_ApproachF(&this->unk698.x, 1155.0f, 0.5f, this->unk6A4 * 261.0f);
            Math_ApproachF(&this->unk698.y, 50.0f, 0.5f, this->unk6A4 * 4.0f);
            Math_ApproachF(&this->unk698.z, 2822.0f, 0.5f, this->unk6A4 * 38.0f);

            this->actor.world.pos.x = BREG(27) + 1376.0f;
            this->actor.world.pos.y = 45.0f;
            this->actor.world.pos.z = BREG(28) + 2864.0f;

            if (this->unk684 != (u32)(BREG(29) + 0x14)) {
                break;
            }

            this->unk688 = 5;
            this->unk684 = 0;
            Animation_MorphToLoop(&D_809BEFD8->unk194, &D_06021B10, 0.0f);
            D_809BEFD8->actor.world.pos.x = BREG(30) + 1363.0f + 120.0f;
            Message_StartTextbox(play, 0x1533, NULL);
            this->unk6B0 = 30.0f;
            play->envCtx.lightSettingOverride = 2;
            /* Fallthrough */
        case 5:
            if (this->unk684 == (u32)(BREG(71) + 2)) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_SIT);
            }
            if ((this->unk684 == (u32)(BREG(72) + 0xA)) || (this->unk684 == (u32)(BREG(73) + 0x19)) ||
                (this->unk684 == (u32)(BREG(74) + 0x28))) {
                Actor_PlaySfx(&D_809BEFD8->actor, D_809BEFD8->unk6B4);
            }
            if ((this->unk684 >= 9) && (this->unk684 < 0x2C)) {
                this->unk430 = KREG(42) + 200.0f;
            }
            if (Animation_OnFrame(&this->unk194, this->unk1D8)) {
                Animation_MorphToLoop(&this->unk194, &D_0600FC78, 0.0f);
                this->unk1D8 = 1000.0f;
            }
            this->unk68C.x = 1349.0f;
            this->unk68C.y = 126.0f;
            this->unk68C.z = 2740.0f;
            this->unk698.x = 1377.0f;
            this->unk698.y = 121.0f;
            this->unk698.z = 2851.0f;
            Math_ApproachF(&D_809BEFD8->actor.world.pos.x, BREG(30) + 1363.0f + 30.0f, 1.0f, BREG(32) + 2.0f);
            D_809BEFD8->actor.world.pos.y = 45.0f;
            D_809BEFD8->actor.world.pos.z = BREG(31) + 2864.0f + 60.0f;
            if (this->unk684 == (u32)(BREG(35) + 0x2D)) {
                Animation_MorphToPlayOnce(&D_809BEFD8->unk194, &D_0600D870, -10.0f);
                Actor_PlaySfx(&D_809BEFD8->actor, NA_SE_EN_DEBU_PAUSE_K);
            }
            if (this->unk684 != (u32)(BREG(33) + 0x50)) {
                break;
            }
            this->unk688 = 6;
            this->unk684 = 0;
            Animation_MorphToLoop(&D_809BEFD4->unk194, &D_06021B10, 0.0f);
            D_809BEFD4->actor.world.pos.x = BREG(30) + 1363.0f + 120.0f;
            D_809BEFD8->actor.world.pos.z = 3164.0f;
            Message_StartTextbox(play, 0x151B, NULL);
            play->envCtx.lightSettingOverride = 3;
            /* Fallthrough */
        case 6:
            if ((this->unk684 == (u32)(BREG(72) + 0xA)) || (this->unk684 == (u32)(BREG(73) + 0x19)) ||
                (this->unk684 == (u32)(BREG(74) + 0x28))) {
                Actor_PlaySfx(&D_809BEFD4->actor, D_809BEFD4->unk6B4);
            }
            if ((this->unk684 >= 0xA) && (this->unk684 < 0x22)) {
                this->unk430 = KREG(42) + 200.0f;
            }
            this->unk68C.x = 1343.0f;
            this->unk68C.y = 146.0f;
            this->unk68C.z = 2975.0f;
            this->unk698.x = 1372.0f;
            this->unk698.y = 122.0f;
            this->unk698.z = 2867.0f;
            Math_ApproachF(&D_809BEFD4->actor.world.pos.x, BREG(30) + 1363.0f + 30.0f, 1.0f, BREG(32) + 2.0f);
            D_809BEFD4->actor.world.pos.y = 45.0f;
            D_809BEFD4->actor.world.pos.z = (BREG(31) + 2864.0f) - 60.0f;
            if (this->unk684 == (u32)(BREG(35) + 0x2D)) {
                Animation_MorphToPlayOnce(&D_809BEFD4->unk194, &D_0600D870, -10.0f);
                Actor_PlaySfx(&D_809BEFD4->actor, NA_SE_EN_YASE_PAUSE_K);
            }
            if (this->unk684 != (u32)(BREG(33) + 0x50)) {
                break;
            }
            this->unk688 = 7;
            this->unk684 = 0;
            D_809BEFD4->actor.world.pos.z = ((BREG(31) + 2864.0f) - 60.0f) - 10.0f;
            D_809BEFD8->actor.world.pos.z = BREG(31) + 2864.0f + 60.0f + 10.0f;
            D_809BEFD4->actor.world.pos.x = (BREG(30) + 1363.0f + 30.0f) - 40.0f;
            D_809BEFD8->actor.world.pos.x = (BREG(30) + 1363.0f + 30.0f) - 40.0f;
            this->unk68C.x = 1339.0f;
            this->unk68C.y = 117.0f;
            this->unk68C.z = 2864.0f;
            this->unk698.x = 1452.0f;
            this->unk698.y = 120.0f;
            this->unk698.z = 2864.0f;
            this->unk6A4 = 0.0f;
            Message_StartTextbox(play, 0x1534, NULL);
            this->unk6B0 = 60.0f;
            play->envCtx.lightSettingOverride = 4;
            /* Fallthrough */
        case 7:
            if (this->unk684 >= (u32)(BREG(37) + 0x14)) {
                if (this->unk684 == (u32)(BREG(37) + 0x14)) {
                    Animation_MorphToPlayOnce(&this->unk194, &D_06009D8C, 0.0f);
                    this->unk1D8 = Animation_GetLastFrame(&D_06009D8C);
                    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_STAND);
                }
                if (Animation_OnFrame(&this->unk194, this->unk1D8) != 0) {
                    Animation_MorphToLoop(&this->unk194, &D_06008390, 0.0f);
                    this->unk1D8 = 1000.0f;
                }
            }
            if (this->unk684 < (u32)(BREG(87) + 0x14)) {
                this->unk430 = 200.0f;
            }
            if (this->unk684 == (u32)(BREG(37) + 0x19)) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HAND);
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_ATTACK);
            }
            if (this->unk684 == (u32)(BREG(44) + 0x28)) {
                Animation_MorphToLoop(&D_809BEFD4->unk194, &D_0600CDE0, -5.0f);
                Animation_MorphToLoop(&D_809BEFD8->unk194, &D_0600CDE0, -5.0f);
            }
            if (this->unk684 == 0x00000028) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HEAD_MID);
            }
            if (this->unk684 == 0x0000002D) {
                Actor_PlaySfx(&D_809BEFD8->actor, NA_SE_EN_DEBU_LAUGH_K);
            }
            if (this->unk684 == 0x00000032) {
                Actor_PlaySfx(&D_809BEFD4->actor, NA_SE_EN_YASE_LAUGH_K);
            }
            Math_ApproachF(&this->unk68C.x, 1196.0f, 0.1f, this->unk6A4 * 143.0f);
            Math_ApproachF(&this->unk68C.y, 52.0f, 0.1f, this->unk6A4 * 65.0f);
            Math_ApproachF(&this->unk698.x, 1302.0f, 0.1f, this->unk6A4 * 150.0f);
            Math_ApproachF(&this->unk698.y, 90.0f, 0.1f, this->unk6A4 * 30.0f);
            Math_ApproachF(&this->unk6A4, BREG(45) * 0.01f + 0.1f, 1.0f, BREG(45) * 0.0001f + 0.01f);

            if (this->unk684 != (u32)(BREG(18) + 0x3C)) {
                break;
            }

            this->unk688 = 8;
            this->unk684 = 0;

            this->unk68C.x = 1309.0f;
            this->unk68C.y = 103.0f;
            this->unk68C.z = 2790.0f;

            this->unk698.x = 1421.0f;
            this->unk698.y = 103.0f;
            this->unk698.z = 2790.0f;

            play->envCtx.lightSettingOverride = 5;
            Actor_PlaySfx(&D_809BEFD4->actor, NA_SE_EN_YASE_LAUGH_K);
            /* Fallthrough */
        case 8:
            if (this->unk684 == 0x0000000F) {
                this->unk68C.x = 1309.0f;
                this->unk68C.y = 103.0f;
                this->unk68C.z = 2930.0f;
                this->unk698.x = 1421.0f;
                this->unk698.y = 103.0f;
                this->unk698.z = 2930.0f;
                Actor_PlaySfx(&D_809BEFD8->actor, NA_SE_EN_DEBU_LAUGH_K);
                Actor_PlaySfx(&D_809BEFD4->actor, NA_SE_EN_YASE_LAUGH_K);
            }
            if (this->unk684 == 0x0000001E) {
                this->unk68C.x = 1324.0f;
                this->unk68C.y = 144.0f;
                this->unk68C.z = 2864.0f;
                this->unk698.x = 1436.0f;
                this->unk698.y = 144.0f;
                this->unk698.z = 2864.0f;
                play->envCtx.lightSettingOverride = 6;
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_LAUGH_DEMO_K);
                Actor_PlaySfx(&D_809BEFD8->actor, NA_SE_EN_DEBU_LAUGH_K);
                Actor_PlaySfx(&D_809BEFD4->actor, NA_SE_EN_YASE_LAUGH_K);
            }
            if (this->unk684 == (u32)(BREG(19) + 0x37)) {
                temp_v0_2 = Play_GetCamera(play, 0);
                this->unk688 = 0;

                func_809B6528(this, play);
                func_809B41D8(D_809BEFD4, play);
                func_809B41D8(D_809BEFD8, play);

                D_809BEFD8->actor.gravity = -1.5f;
                D_809BEFD4->actor.gravity = D_809BEFD8->actor.gravity;
                D_809BEFD8->unk152 = 1;
                D_809BEFD4->unk152 = D_809BEFD8->unk152;

                temp_v0_2->eye = this->unk68C;
                temp_v0_2->eyeNext = this->unk68C;
                temp_v0_2->at = this->unk698;

                func_80169AFC(play, this->unk_68A, 0);
                this->unk_68A = 0;
                Cutscene_StopManual(play, &play->csCtx);
                Player_SetCsActionWithHaltedActors(play, &this->actor, 6);
                D_809BDB00 = 1;
                this->unk_153 = 2;
                Message_CloseTextbox(play);
                play->envCtx.lightSettingOverride = 7;
                gSaveContext.eventInf[5] |= 0x80;
            }
            break;
    }

    if (this->unk_68A != 0) {
        ShrinkWindow_SetLetterboxTarget(27);
        temp_fv1 = Math_SinS(this->unk146 * 0x6000) * 0.5f * sp64;

        sp50.x = this->unk68C.x;
        sp50.y = this->unk68C.y + temp_fv1;
        sp50.z = this->unk68C.z;
        sp44.x = this->unk698.x;
        sp44.y = this->unk698.y + 2.0f * temp_fv1;
        sp44.z = this->unk698.z;
        Play_SetCameraAtEye(play, this->unk_68A, &sp44, &sp50);
        Play_SetCameraFov(play, this->unk_68A, this->unk6B0);
        sp60->actor.world.rot.y = sp60->actor.shape.rot.y = this->unk6AC;
    }

    Math_ApproachF(&this->unk42C, this->unk430, 1.0f, 2.0f * KREG(41) + 200.0f);
    this->unk428 = Math_SinS((KREG(40) * 0x100 + 0x3F00) * this->unk146) * this->unk42C + this->unk42C;
    Math_ApproachZeroF(&this->unk42C, 1.0f, KREG(41) + 100.0f);

    if ((this->unk430 >= 50.0f) && !(this->unk146 & 1) && (Rand_ZeroOne() < 0.5f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_TALK);
    }
}

void func_809B9A18(EnKnight* arg0, PlayState* arg1) {
    s32 var_s0;
    s32 var_s4;
    Vec3f sp4C;
    Player* temp_v0 = GET_PLAYER(arg1);

    if (arg0->unk534.elements[0].info.bumperFlags & 2) {
        arg0->unk534.elements[0].info.bumperFlags &= 0xFFFD;
        arg0->unk193 = 5;
        if ((temp_v0->meleeWeaponState != 0) && (temp_v0->meleeWeaponAnimation >= 0x1E) && (arg0->unk478 == 0)) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_REFLECT_SW);
            CollisionCheck_SpawnShieldParticlesMetal(arg1, &arg0->unk47C);
            arg0->unk478 = 5;
        }
        Matrix_RotateYS(arg0->unk172, MTXMODE_NEW);
        Matrix_MultVecZ((arg0 == D_809BEFD0) ? -6.0f : -4.0f, &sp4C);
        arg0->unk2A4 = sp4C.x;
        arg0->unk2A8 = sp4C.z;
        return;
    }

    for (var_s4 = 0; var_s4 < 2; var_s4++) {
        if (arg0->unk156 != 0) {
            continue;
        }

        if (arg0->unk594.elements[var_s4].info.bumperFlags & 2) {
            arg0->unk594.elements[var_s4].info.bumperFlags &= ~2;

            switch (arg0->actor.colChkInfo.damageEffect) {
                case 3:
                    arg0->unk2A1 = 0x0A;
                    func_809B4E84(arg0, arg1, 0x0050);
                    Actor_PlaySfx(&arg0->actor, NA_SE_EN_COMMON_FREEZE);
                    arg0->unk156 = 0x000F;
                    break;
                case 1:
                    func_809B4E84(arg0, arg1, 0x0028);
                    Actor_PlaySfx(&arg0->actor, NA_SE_EN_COMMON_FREEZE);
                    arg0->unk156 = 0x000F;
                    break;
                case 2:
                    arg0->unk2A1 = 1;
                    break;
                case 4:
                    arg0->unk2A1 = 0x14;
                    break;
                case 14:
                    arg0->unk291 = 0x0A;
                    break;
                case 10:
                    arg0->unk2A1 = 0x28;
                    func_809B4E84(arg0, arg1, 0x0028);
                    Actor_PlaySfx(&arg0->actor, NA_SE_EN_COMMON_FREEZE);
                    arg0->unk156 = 0x000F;
                    break;
                case 13:
                    if (arg0->actor.bgCheckFlags & 1) {
                        Matrix_RotateYS(arg0->unk172, MTXMODE_NEW);
                        Matrix_MultVecZ(-4.0f, &sp4C);
                        arg0->unk2A4 = sp4C.x;
                        arg0->unk2A8 = sp4C.z;
                        arg0->actor.velocity.y = 5.0f;

                        for (var_s0 = 0; var_s0 < 5; var_s0++) {
                            func_809B22CC(arg0, arg1, 0);
                        }
                    }
                    break;
            }
            if (arg0->actor.colChkInfo.damage != 0) {
                arg0->actor.colChkInfo.health -= arg0->actor.colChkInfo.damage;
                if ((s8)arg0->actor.colChkInfo.health <= 0) {
                    func_809B51DC(arg0, arg1);
                    Enemy_StartFinishingBlow(arg1, &arg0->actor);
                    Actor_PlaySfx(&arg0->actor, arg0->unk6C0);
                } else if (arg0->actor.colChkInfo.damageEffect != 3) {
                    func_809B4F90(arg0, arg1);
                    Actor_PlaySfx(&arg0->actor, arg0->unk6BE);
                }
                arg0->unk156 = 0x000A;
                arg0->unk158 = 0x000F;
            }
            arg0->unk192 = 0;
        }
    }
}

void func_809B9D24(EnKnight* this, PlayState* play) {
    if (this->unk156 == 0) {
        s32 i;

        for (i = 0; i < 2; i++) {
            ColliderJntSphElement* temp_v0 = &this->unk594.elements[i];
            ColliderInfo* acHitInfo;

            if (temp_v0->info.bumperFlags & 2) {
                temp_v0->info.bumperFlags &= ~2;

                acHitInfo = temp_v0->info.acHitInfo;

                this->unk156 = 10;
                if (acHitInfo->toucher.dmgFlags & 0x200000) {
                    this->unk158 = 15;
                    this->unk156 = 1000;
                    func_809B5634(this, play);
                }
            }
        }
    }
}

void func_809B9E00(EnKnight* this, PlayState* play) {
    Vec3f sp94;
    Vec3f sp88;
    s32 i;

    SoundSource_PlaySfxAtFixedWorldPos(play, &this->unk1DC[0], 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < 15; i++) {
        sp88.x = Rand_CenteredFloat(7.0f);
        sp88.z = Rand_CenteredFloat(7.0f);
        sp88.y = Rand_ZeroFloat(6.0f) + 4.0f;
        sp94.x = sp88.x + this->unk1DC[i].x;
        sp94.y = sp88.y + this->unk1DC[i].y;
        sp94.z = sp88.z + this->unk1DC[i].z;
        EffectSsEnIce_Spawn(play, &sp94, Rand_ZeroFloat(0.5f) + 0.7f, &sp88, &D_809BDD00, &D_809BDCF8, &D_809BDCFC,
                            0x1E);
    }
}

void func_809B9F8C(EnKnight* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->unk156 == 0) {
        if (this->unk634.base.acFlags & AC_HIT) {
            this->unk634.base.acFlags &= ~AC_HIT;
            this->unk156 = 0xF;
            if (&this->actor == player->actor.parent) {
                player->av2.actionVar2 = 101;
                player->actor.parent = NULL;
                player->csAction = 0;
                Play_DisableMotionBlur();
                func_800B8D50(play, &this->actor, 10.0f, D_809BEFD0->unk172, 5.0f, 16);
                func_809BA058(this, play);
                this->unk_148 = 1;
                this->unk14A[1] = 0x1E;
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_LAUGH_DEMO_K);
            }
        }
    }
}

void func_809BA058(EnKnight* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->unk194, &D_06003008, 0.0f);
    this->unk194.curFrame = 19.0f;
    this->actionFunc = func_809BA0CC;
    this->unk_148 = 0;
    this->unk14A[1] = KREG(77) + 0xC8;
    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
}

void func_809BA0CC(EnKnight* this, PlayState* play) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 pad;
    f32 sp3C;
    s16 sp3A;
    s16 sp38;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->unk194);
    Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HEAD_FLOAT - SFX_FLAG);

    switch (this->unk_148) {
        case 0:
            this->unk_148 = 1;
            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
            Matrix_MultVecZ(500.0f, &this->unk440);
            this->unk440.x += this->actor.world.pos.x;
            this->unk440.y = this->actor.world.pos.y + 500.0f;
            this->unk440.z += this->actor.world.pos.z;
            this->actor.world.rot.x = KREG(39) * 0x1000 + 0x2000;
            this->unk14A[0] = 0x14;
            D_809BEFD0->actor.flags &= ~1;
            player->lockOnActor = &this->actor;
            play->actorCtx.targetCtx.arrowPointedActor = &this->actor;
            play->actorCtx.targetCtx.lockOnActor = &this->actor;
            Math_Vec3f_Copy(&this->actor.world.pos, &D_809BEFD0->actor.world.pos);
            Math_Vec3s_Copy(&this->actor.world.rot, &D_809BEFD0->actor.world.rot);
            Math_Vec3s_Copy(&this->actor.shape.rot, &D_809BEFD0->actor.world.rot);
            this->unk156 = 0xA;
            this->unk152 = 1;
            return;
        case 1:
            this->unk428 = (Math_SinS((KREG(40) * 0x100 + 0x1200) * this->unk146) * 1000.0f) + 1000.0f;
            sp4C = this->unk440.x - this->actor.world.pos.x;
            sp48 = this->unk440.y - this->actor.world.pos.y;
            sp44 = this->unk440.z - this->actor.world.pos.z;
            sp3C = sqrtf(SQ(sp4C) + SQ(sp48) + SQ(sp44));

            if ((this->unk14A[1] == 1) || (KREG(5) != 0)) {
                KREG(5) = 0;
                if (D_809BEFD0->actionFunc != func_809B52E8 && D_809BEFD0->actionFunc != func_809B5698) {
                    this->unk14A[1] = 0;
                    func_809B6D38(D_809BEFD0, play);
                    Animation_MorphToPlayOnce(&this->unk194, &D_060079D4, -10.0f);
                    this->unk152 = 0;
                    this->unk194.playSpeed = 0.0f;
                } else {
                    this->unk14A[1] = 0x32;
                }
            }
            if (this->unk14A[1] == 0) {
                Math_Vec3f_Copy(&this->unk440, &D_809BEFD0->actor.world.pos);
                this->unk440.y += 100.0f;
                if (sp3C < 100.0f) {
                    Math_ApproachF(&this->actor.speed, (f32)sREG(48) + 1.5f, 1.0f, 0.3f);
                }
                if (sp3C < 30.0f) {
                    this->unk_148 = 2;
                    this->unk14A[0] = 0x32;
                    this->unk156 = 0x3E8;
                    break;
                }
            } else {
                Math_ApproachF(&this->actor.speed, sREG(48) + 5.0f, 1.0f, 5.0f);
                if (this->unk14A[0] == 0 || sp3C < 50.0f) {
                    this->unk14A[0] = Rand_ZeroFloat(50.0f) + 50.0f;
                    if (Rand_ZeroOne() < 0.2f) {
                        Math_Vec3f_Copy(&this->unk440, &player->actor.world.pos);
                        this->unk440.y += 25.0f;
                    } else {
                        this->unk440.x = Rand_CenteredFloat(500.0f) + player->actor.world.pos.x;
                        this->unk440.y = Rand_ZeroFloat(100.0f) + player->actor.world.pos.y + 50.0f;
                        this->unk440.z = Rand_CenteredFloat(500.0f) + player->actor.world.pos.z;
                    }
                }
            }
            sp38 = Math_Atan2S(sp4C, sp44);
            sp3A = Math_Atan2S(sp48, sqrtf(SQ(sp4C) + SQ(sp44)));
            Math_ApproachS(&this->actor.world.rot.y, sp38, 0xA, 0x800);
            Math_ApproachS(&this->actor.world.rot.x, sp3A, 0xA, 0x800);
            Math_ApproachF(&this->unk164.x, 300.0f, 0.1f, 3.0f);
            Math_ApproachF(&this->unk164.y, -3800.0f, 0.1f, 38.0f);
            Math_ApproachF(&this->unk164.z, -900.0f, 0.1f, 9.0f);
            Math_ApproachS(&this->actor.shape.rot.y, this->unk172, 0xA, 0x200);
            Math_ApproachS(&this->actor.shape.rot.x, this->unk170, 0xA, 0x200);
            if (this->unk14A[1] == 0x28) {
                func_809BA940(this, play);
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_CYNICAL);
            }
            break;
        case 2:
        case 3:
            this->unk156 = 10;
            Math_ApproachZeroF(&this->actor.speed, 1.0f, 0.1f);
            Math_ApproachS(&this->actor.shape.rot.y, D_809BEFD0->actor.world.rot.y, 5, 0x800);
            Math_ApproachS(&this->actor.shape.rot.x, 0, 5, 0x800);
            Math_ApproachZeroF(&this->unk164.x, 0.5f, (sREG(73) * 0.01f + 0.05f) * 300.0f);
            Math_ApproachZeroF(&this->unk164.y, 0.5f, (sREG(73) * 0.01f + 0.05f) * 3800.0f);
            Math_ApproachZeroF(&this->unk164.z, 0.5f, (sREG(73) * 0.01f + 0.05f) * 900.0f);
            Math_ApproachF(&this->actor.world.pos.x, D_809BEFD0->actor.world.pos.x, 0.5f, sREG(74) * 0.1f + 4.0f);
            Math_ApproachF(&this->actor.world.pos.y, D_809BEFD0->actor.world.pos.y, 0.5f, sREG(74) * 0.1f + 4.0f);
            Math_ApproachF(&this->actor.world.pos.z, D_809BEFD0->actor.world.pos.z, 0.5f, sREG(74) * 0.1f + 4.0f);
            if (this->unk_148 == 2) {
                if ((fabsf(this->actor.world.pos.x - D_809BEFD0->actor.world.pos.x) < 30.0f) &&
                    (fabsf(this->actor.world.pos.z - D_809BEFD0->actor.world.pos.z) < 30.0f) &&
                    (fabsf(this->actor.world.pos.y - D_809BEFD0->actor.world.pos.y) < sREG(75) * 0.1f + 30.0f)) {
                    this->unk_148 = 3;
                    D_809BEFD0->unk_148 = 1;
                    this->unk194.playSpeed = 1.0f;
                }
            }
            break;
    }
}

void func_809BA940(EnKnight* this, PlayState* play) {
    this->actionFunc = func_809BA978;
    this->unk_148 = 0;
    this->unk14A[0] = BREG(16) + 0x3C;
    this->unk14A[2] = 0xFA;
}

void func_809BA978(EnKnight* this, PlayState* play) {
    Vec3f sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 sp40;
    Player* player = GET_PLAYER(play);
    s32 pad;

    Matrix_RotateYS(player->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_MultVecZ(7.0f, &sp54);

    if (player->transformation == 1) {
        sp54.y = 67.0f;
    } else if (player->transformation == 0) {
        sp54.y = 85.0f;
    } else if (player->transformation == 2) {
        sp54.y = 60.0f;
    } else if (player->transformation == 3) {
        sp54.y = 34.0f;
    } else {
        sp54.y = 40.0f;
    }

    sp50 = player->actor.world.pos.x - this->actor.world.pos.x;
    sp4C = BREG(17) + (player->actor.world.pos.y + 100.0f) - this->actor.world.pos.y;
    sp48 = player->actor.world.pos.z - this->actor.world.pos.z;

    if (this->unk_148 != 1) {
        f32 var_fv1 = (this->unk_148 == 2) ? 3000.0f : 1000.0f;

        this->unk428 = Math_SinS((KREG(40) * 0x100 + 0x1200) * this->unk146) * 1000.0f + var_fv1;
    }

    sp44 = sqrtf(SQ(sp50) + SQ(sp48));

    switch (this->unk_148) {
        case 0:
            Math_ApproachF(&this->actor.speed, BREG(18) + 10.0f, 1.0f, 1.0f);
            sp40 = Math_Atan2S(sp50, sp48);
            sp42 = Math_Atan2S(sp4C, sp44);
            Math_ApproachS(&this->actor.world.rot.y, sp40, 0xA, 0x800);
            Math_ApproachS(&this->actor.world.rot.x, sp42, 0xA, 0x800);

            if (this->unk14A[2] == 0) {
                func_809BA058(this, play);
                this->unk_148 = 1;
                this->unk14A[1] = 0x1E;
                break;
            }

            if (this->unk14A[0] == 0 && sp44 < BREG(19) + 100.0f) {
                this->unk_148 = 1;
                this->unk14A[2] = 0x3C;
                this->unk6A4 = 0.0f;
            }
            break;
        case 1:
            this->unk152 = 0;
            Math_ApproachS(&this->unk428, 0xFA0, 5, 0x1000);
            Math_ApproachZeroF(&this->actor.speed, 1.0f, 1.0f);
            Math_ApproachF(&this->actor.world.pos.x, player->actor.world.pos.x + sp54.x, 1.0f, this->unk6A4);
            Math_ApproachF(&this->actor.world.pos.y, player->actor.world.pos.y + sp54.y, 1.0f, this->unk6A4);
            Math_ApproachF(&this->actor.world.pos.z, player->actor.world.pos.z + sp54.z, 1.0f, this->unk6A4);
            Math_ApproachF(&this->unk6A4, BREG(20) + 20.0f, 1.0f, BREG(21) + 0.5f);

            if (this->unk14A[2] == 0 || (player->stateFlags3 & 0x1000)) {
                func_809BA058(this, play);
                this->unk_148 = 1;
                this->unk14A[1] = 0x1E;
                break;
            }

            if (sp44 < BREG(22) + 20.0f) {
                if (play->grabPlayer(play, player) != 0) {
                    Play_EnableMotionBlur(0x96);
                    player->actor.parent = &this->actor;
                    AudioSfx_PlaySfx(NA_SE_VO_LI_DAMAGE_S, &player->actor.projectedPos, 4,
                                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                    this->actor.flags &= ~1;
                    this->unk_148 = 2;
                    this->unk14A[0] = 0x50;
                } else {
                    this->unk14A[2] = 0;
                }
            }
            break;
        case 2:
            if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A) ||
                CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {

                if (1) {}
                if (this->unk14A[0] != 0) {
                    this->unk14A[0]--;
                    if (1) {}
                }
                if (this->unk14A[0] != 0) {
                    this->unk14A[0]--;
                }
                if (this->unk14A[0] != 0) {
                    this->unk14A[0]--;
                }
                if (this->unk14A[0] != 0) {
                    this->unk14A[0]--;
                }
                if (this->unk14A[0] != 0) {
                    this->unk14A[0]--;
                }
            }
            Math_ApproachF(&this->actor.world.pos.x, player->actor.world.pos.x + sp54.x, 1.0f, this->unk6A4);
            Math_ApproachF(&this->actor.world.pos.y, player->actor.world.pos.y + sp54.y, 1.0f, this->unk6A4);
            Math_ApproachF(&this->actor.world.pos.z, player->actor.world.pos.z + sp54.z, 1.0f, this->unk6A4);
            Math_ApproachF(&this->unk6A4, BREG(20) + 20.0f, 1.0f, BREG(21) + 0.5f);
            Math_ApproachS(&this->actor.shape.rot.y, player->actor.shape.rot.y + 0x8000, 2, 0x1000);
            Math_ApproachS(&this->actor.shape.rot.x, BREG(83) * 0x800 + 0x4000, 2, 0x1000);
            player->av2.actionVar2 = 90;
            Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HEAD_BITE - SFX_FLAG);
            if (this->unk14A[0] == 0 && &this->actor == player->actor.parent) {
                player->av2.actionVar2 = 101;
                player->actor.parent = NULL;
                player->csAction = 0;
                Play_DisableMotionBlur();
                func_809BA058(this, play);
                this->unk_148 = 1;
                this->unk14A[1] = 0x1E;
                Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_LAUGH_DEMO_K);
            }
            break;
    }

    if (this->unk_148 != 2) {
        Math_ApproachS(&this->actor.shape.rot.y, this->unk172, 0xA, 0x200);
        Math_ApproachS(&this->actor.shape.rot.x, this->unk170, 0xA, 0x200);
        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_HEAD_FLOAT - SFX_FLAG);
    }
}

void EnKnight_Update(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;
    Input* input;
    PlayState* play2 = play;
    Player* sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    u8 var_a0;
    s32 var_v1;

    sp78 = GET_PLAYER(play);
    Math_Vec3f_Copy(&this->unk6C8, &this->actor.projectedPos);
    sp74 = sp78->actor.world.pos.x - this->actor.focus.pos.x;
    sp70 = KREG(93) + ((sp78->actor.world.pos.y + 34.0f) - this->actor.focus.pos.y);
    sp6C = sp78->actor.world.pos.z - this->actor.focus.pos.z;

    this->unk172 = Math_FAtan2F(sp6C, sp74);
    this->unk170 = Math_Atan2S(-sp70, sqrtf(SQ(sp74) + SQ(sp6C)));

    this->unk146++;

    if (this == D_809BEFDC) {
        for (var_a0 = 0; var_a0 < 3; var_a0++) {
            if (this->unk14A[var_a0] != 0) {
                this->unk14A[var_a0]--;
            }
        }

        if (this->unk156 != 0) {
            this->unk156--;
        }
        if (this->unk158 != 0) {
            this->unk158--;
        }
        this->actionFunc(this, play);
        Math_ApproachS(&this->unk184, this->unk186, 5, 0x2000);
        this->unk186 = 0;
        Actor_UpdateVelocityWithoutGravity(&this->actor);
        Actor_UpdatePos(&this->actor);
        this->actor.world.pos.x += this->unk2A4;
        this->actor.world.pos.z += this->unk2A8;
        Math_ApproachZeroF(&this->unk2A4, 1.0f, KREG(86) + 2.0f);
        Math_ApproachZeroF(&this->unk2A8, 1.0f, KREG(86) + 2.0f);
        if (this->unk152 != 0) {
            Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 20.0f, 100.0f, 5);
        }
        func_809B9F8C(this, play);

        this->unk488.dim.pos.x = (s32)this->actor.focus.pos.x;
        this->unk488.dim.pos.y = (s32)this->actor.focus.pos.y;
        this->unk488.dim.pos.z = (s32)this->actor.focus.pos.z;

        if (this->actionFunc == func_809BA978) {
            if (this->unk_148 < 2) {
                if (this->unk_148 == 0) {
                    CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk488.base);
                }
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk488.base);
            } else {
                this->unk634.dim.radius = KREG(34) + 0x14;
                this->unk634.dim.height = KREG(35) + 0x28;
                this->unk634.dim.yShift = 0;
                this->unk634.dim.pos.x = (s32)sp78->actor.world.pos.x;
                this->unk634.dim.pos.y = (s32)sp78->actor.world.pos.y;
                this->unk634.dim.pos.z = (s32)sp78->actor.world.pos.z;
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk634.base);
            }
        } else {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk488.base);
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk488.base);
        }

        if ((this->actionFunc != func_809BA978 || this->unk_148 != 2) && !(BREG(76) & this->unk146)) {
            EnKnight* temp_v0_5 = (EnKnight*)Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_KNIGHT,
                                                                this->actor.world.pos.x, this->actor.world.pos.y,
                                                                this->actor.world.pos.z, this->actor.shape.rot.x,
                                                                this->actor.shape.rot.y, this->actor.shape.rot.z, 0xCA);
            if (temp_v0_5 != NULL) {
                for (var_v1 = 0; var_v1 < 29; var_v1++) {
                    temp_v0_5->unk194.jointTable[var_v1] = this->unk194.jointTable[var_v1];
                    temp_v0_5->unk194.skeleton = this->unk194.skeleton;
                    temp_v0_5->unk194.dListCount = this->unk194.dListCount;
                }
                Math_Vec3f_Copy(&temp_v0_5->unk164, &this->unk164);
            }
        }
    } else {
        this->unk_680 = 0;

        if (this == D_809BEFD0) {
            Actor* var_v0;

            D_809BEFE4 = NULL;
            for (var_v0 = play->actorCtx.actorLists[7].first; var_v0 != NULL; var_v0 = var_v0->next) {
                if (var_v0->id == ACTOR_MIR_RAY3) {
                    D_809BEFE4 = (MirRay3*)var_v0;
                    break;
                }
            }

            this->unk_144 = gSaveContext.save.time;
            Math_ApproachS(&this->unk428, 0, 2, 0x0200);
        } else if (D_809BEFD0->unk_154 == 0) {
            this->actor.hintId = 0x1D;
        } else {
            this->actor.hintId = 0x1E;
        }

        if (D_809BEFD0->unk_151 != 0) {
            if ((this == D_809BEFD0) && (this->actionFunc == func_809B6764)) {
                func_809B5D38(this, play);
            }
            if (!((this == D_809BEFD0) && (this->actionFunc == func_809B5D54))) {
                return;
            }
        }

        this->unk190 = 0;
        this->unk191 = 0;
        this->unk192 = 0;
        this->unk594.base.colType = 3;
        if (((KREG(63) == 0) && (this != D_809BEFD0)) || ((KREG(63) != 2) && (this == D_809BEFD0))) {
            for (var_a0 = 0; var_a0 < 3; var_a0++) {
                if (this->unk14A[var_a0] != 0) {
                    this->unk14A[var_a0]--;
                }
            }

            if (this->unk156 != 0) {
                this->unk156--;
            }
            if (this->unk158 != 0) {
                this->unk158--;
            }
            if (this->unk478 != 0) {
                this->unk478--;
            }
            if (this->unk2A2 != 0) {
                this->unk2A2--;
            }
            if (this->unk15E != 0) {
                this->unk15E--;
            }
            if (this->unk291 != 0) {
                this->unk291--;
            }

            Math_ApproachZeroF(&this->unk474, 1.0f, 0.2f);

            if ((this->actionFunc != func_809B52E8) && (this->actionFunc != func_809B5698)) {
                Math_ApproachS(&this->actor.shape.rot.x, 0, 0x000A, 0x0200);
            }

            this->actionFunc(this, play);

            Actor_MoveWithGravity(&this->actor);

            this->actor.world.pos.x += this->unk2A4;
            this->actor.world.pos.z += this->unk2A8;

            if ((this->unk192 != 0) || (this->actionFunc == func_809B4880)) {
                func_809B2DD0(this, play);

                if ((this->unk192 != 0) && (D_809BEFE0 != NULL) && (this != D_809BEFE0)) {
                    func_809B5E90(this, play);
                } else if ((this != D_809BEFD0) && (sp78->stateFlags3 & 0x20000000)) {
                    func_809B5FA8(this, play);
                }
            }
        }

        if (this->unk152 != 0) {
            Actor_UpdateBgCheckInfo(play, &this->actor, 100.0f, 50.0f, 150.0f, 5);
        }

        if (this->actor.bgCheckFlags & 1) {
            if (this->actor.velocity.y <= 0.0f) {
                this->actor.velocity.y = -2.0f;
            }
            Math_ApproachZeroF(&this->unk2A4, 1.0f, 1.0f);
            Math_ApproachZeroF(&this->unk2A8, 1.0f, 1.0f);
        }

        Math_ApproachS(&this->unk184, this->unk186, this->unk18E, this->unk18C);
        this->unk18C = 0x1000;
        this->unk18E = 3;
        Math_ApproachS(&this->unk188, this->unk18A, this->unk18E, this->unk18C);
        this->unk18A = 0;

        if (this->actionFunc != func_809B4308) {
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x0A00);
        }

        if (this->actionFunc != func_809B842C && this->actionFunc != func_809B5698 &&
            this->actionFunc != func_809B58D4 && this->actionFunc != func_809B6764 &&
            this->actionFunc != func_809B6C54 && this->actionFunc != func_809B6D94 && !Play_InCsMode(play)) {

            if (this->actionFunc != func_809B52E8) {
                func_809B9A18(this, play);

                if (this->unk190 != 0) {
                    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk4D4.base);
                    CollisionCheck_SetAT(play, &play2->colChkCtx, &this->unk4D4.base);
                }

                if (this->unk191 != 0) {
                    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk534.base);
                }

                if (this->unk162 == 0) {
                    if (this->unk193 == 0) {
                        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk594.base);
                    } else {
                        this->unk193--;
                    }
                    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk594.base);

                    if (this->unk192 != 0 &&
                        (sp78->unk_D57 != 0 || (sp78->unk_ADC != 0 && this->actor.xzDistToPlayer <= 120.0f)) &&
                        func_809B316C(this, play)) {
                        f32 var_fv1 = (this == D_809BEFD0) ? 0.65f : 0.25f;

                        if ((Rand_ZeroOne() < var_fv1) && (sp78->unk_ADC != 0) && (this->actionFunc != func_809B3DAC) &&
                            !(this->actor.bgCheckFlags & 8)) {
                            func_809B592C(this, play);
                        } else {
                            func_809B3CD0(this, play);
                        }
                    }
                }
            } else {
                func_809B9D24(this, play);
                CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk594.base);
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk594.base);
            }
        }

        input = &play->state.input[3];
        if (CHECK_BTN_ALL(input->press.button, BTN_L) && this == D_809BEFD0) {
            func_809B5634(D_809BEFD4, play);
            func_809B5634(D_809BEFD8, play);
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_R) && this == D_809BEFD0) {
            this->unk2A1 = KREG(17);
        }

        switch (this->unk2A1) {
            case 0:
                this->unk2A0 = 0;
                this->unk2A2 = 0;
                this->unk29C = 0.0f;
                break;
            case 1:
                this->unk2A0 = 0;
                this->unk2A2 = 0x0050;
                this->unk2A1++;
                this->unk29C = 1.0f;
                this->unk294 = 0.0f;
                Actor_SetColorFilter(&this->actor, 0x4000, 0x0078, 0, 0x003C);
                /* fallthrough */
            case 2:
                if (this->unk2A2 == 0) {
                    Math_ApproachZeroF(&this->unk29C, 1.0f, 0.02f);
                    if (this->unk29C == 0.0f) {
                        this->unk2A1 = 0;
                    }
                } else {
                    Math_ApproachF(&this->unk294, 0.5f, 0.1f, 0.5f);
                }
                break;
            case 10:
                this->unk2A0 = 0x0B;
                this->unk2A2 = 0x0050;
                this->unk2A1++;
                this->unk29C = 1.0f;
                this->unk294 = 0.0f;
                this->unk298 = 1.0f;
                /* fallthrough */
            case 11:
                if (this->unk2A2 == 0) {
                    func_809B9E00(this, play);
                    this->unk2A1 = 0;
                } else {
                    if (this->unk2A2 == 0x0032) {
                        this->unk2A0 = 0x0A;
                    }
                    Math_ApproachF(&this->unk294, 0.5f, 1.0f, 0.08f);
                    Math_ApproachF(&this->unk298, 0.5f, 0.05f, 0.05f);
                }
                break;
            case 20:
                this->unk2A0 = 0x14;
                this->unk2A2 = 0x0028;
                this->unk2A1++;
                this->unk29C = 1.0f;
                this->unk294 = 0.0f;
                /* fallthrough */
            case 21:
                if (this->unk2A2 == 0) {
                    Math_ApproachZeroF(&this->unk294, 1.0f, 0.03f);
                    if (this->unk294 == 0.0f) {
                        this->unk2A1 = 0;
                        this->unk29C = 0.0f;
                    }
                } else {
                    Math_ApproachF(&this->unk294, 0.75f, 0.5f, 0.5f);
                }
                break;
            case 30:
                this->unk2A0 = 0x14;
                this->unk2A2 = 0x000A;
                this->unk2A1++;
                this->unk29C = 0.5f;
                /* fallthrough */
            case 31:
                if (this->unk2A2 == 0) {
                    Math_ApproachZeroF(&this->unk294, 1.0f, 0.03f);
                    if (this->unk294 == 0.0f) {
                        this->unk2A1 = 0;
                        this->unk29C = 0.0f;
                    }
                } else {
                    Math_ApproachF(&this->unk294, 0.5f, 0.5f, 0.3f);
                }
                break;
            case 40:
                this->unk2A0 = 0x1E;
                this->unk2A2 = 0x0032;
                this->unk29C = 1.0f;
                this->unk294 = (KREG(18) * 0.1f) + 0.5f;
                this->unk2A1++;
                /* fallthrough */
            case 41:
                if (this->unk2A2 == 0) {
                    Math_ApproachZeroF(&this->unk294, 1.0f, 0.05f);
                    if (this->unk294 == 0.0f) {
                        this->unk2A1 = 0;
                        this->unk29C = 0.0f;
                    }
                }
                break;
        }

        this->unk430 = 0.0f;

        if (this == D_809BEFD0) {
            if (D_809BDB00 != 0) {
                D_809BDB00--;
                if (D_809BDB00 == 0) {
                    Audio_PlayBgm_StorePrevBgm(NA_BGM_MINI_BOSS);
                }
            }
            if (this->unk162 != 0) {
                Math_ApproachF(&this->unk17C, 60.0f, 1.0f, 8.0f);
            } else {
                Math_ApproachF(&this->unk17C, 255.0f, 1.0f, 8.0f);
            }
            func_809BD490(this, play);
            if (this->unk_154 != 0) {
                u16 var_v0_2;

                play->envCtx.lightSettingOverride = 0;
                play->envCtx.lightBlendOverride = 2;
                if (this->unk_154 == 1) {
                    play->envCtx.lightSetting = 8;
                    play->envCtx.prevLightSetting = 0x0C;
                } else {
                    play->envCtx.lightSetting = 0;
                    play->envCtx.prevLightSetting = 0x0A;
                }
                var_v0_2 = gSaveContext.save.time;
                if ((s32)var_v0_2 > 0x8000) {
                    var_v0_2 = (0xFFFF - var_v0_2) & 0xFFFF;
                }
                play->envCtx.lightBlend = var_v0_2 * 0.000030517578f;
            }
            if ((this->unk6C4 == 0) && (this->unk162 == 0) && (Player_GetMask(play) == 0x0F) &&
                ((this->actionFunc == func_809B6764) || (this->unk192 != 0)) &&
                (this->actor.xzDistToPlayer < (KREG(82) + 130.0f)) && (func_809B316C(this, play) != 0)) {
                this->unk6C4 = 1;
                func_809B78A4(this, play);
            }
        }
        this->actor.shape.shadowAlpha = (this->unk180 * this->unk17C) / 255.0f;
    }
}

void func_809BC2C4(EnKnight* this, PlayState* play) {
    f32 var_fv0;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&D_06018BC4));

    gSPDisplayList(POLY_XLU_DISP++, D_08000000);

    if (this == D_809BEFD0) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)(sREG(11) + 0xB4), 255, 255,
                        (u8)((sREG(14) * 0.1f + 1.0f) * this->unk450));
    } else {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (u8)((sREG(14) * 0.1f + 1.0f) * this->unk450));
    }

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Translate(this->unk454, this->unk458, this->unk45C, MTXMODE_APPLY);
    Matrix_RotateXFApply(this->unk460);
    Matrix_RotateZF(this->unk468, MTXMODE_APPLY);
    Matrix_RotateYF(this->unk464, MTXMODE_APPLY);

    var_fv0 = (this == D_809BEFD0) ? (17.0f / 13) : 1.0f;
    Matrix_Scale(0.021f * var_fv0, 0.021f * var_fv0, 0.021f * var_fv0, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    switch (this->unk44C) {
        case 0:
            gSPDisplayList(POLY_XLU_DISP++, D_06018AF0);
            break;
        case 1:
            gSPDisplayList(POLY_XLU_DISP++, D_060189F0);
            break;
        default:
        case 2:
            gSPDisplayList(POLY_XLU_DISP++, D_060188F8);
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 func_809BC67C(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKnight* this = THIS;

    if (limbIndex == 15) {
        rot->x += (f32)this->unk184;
    }
    if (limbIndex == 18) {
        rot->z += this->unk428;
    } else if (limbIndex == 19) {
        rot->z -= this->unk428;
    }

    if (limbIndex != 18 && limbIndex != 19) {
        *dList = NULL;
    }
    return 0;
}

s32 func_809BC720(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnKnight* this = THIS;

    if (limbIndex == 0xF) {
        rot->x += (f32)this->unk184;
        rot->z += this->unk188;
    }
    if (this == D_809BEFD0) {
        if (limbIndex == 0x12) {
            rot->z += this->unk428;
        } else if (limbIndex == 0x13) {
            rot->z -= this->unk428;
        }
        if (limbIndex == 0x17) {
            rot->z -= this->unk174;
        }
        if (limbIndex == 0x18) {
            rot->z -= this->unk178;
        }
        if (limbIndex == 0x1A) {
            rot->z -= this->unk176;
        }
        if (limbIndex == 0x1B) {
            rot->z -= this->unk17A;
        }
        if ((limbIndex == 0x12 || limbIndex == 0x13) && this->unk162 != 0) {
            *dList = NULL;
        }
    } else if (this == D_809BEFD8) {
        if (limbIndex == 0xF) {
            *dList = D_06013020;
        } else if (limbIndex == 0x12) {
            *dList = D_06012DB0;
        } else if (limbIndex == 0x13) {
            *dList = D_06012400;
        }
    }
    return 0;
}

void func_809BC8B4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnKnight* this = THIS;
    Vec3f sp28;

    if (this->actionFunc == func_809B5698 || this->unk29C > 0.0f) {
        s8 temp_v0 = D_809BDD3C[limbIndex];
        if (temp_v0 >= 0) {
            Matrix_MultZero(&this->unk1DC[temp_v0]);
        }
    }
    if (limbIndex == 15) {
        Matrix_MultVec3f(&D_809BDD0C, &this->actor.focus.pos);
        Matrix_MultVec3f(&D_809BDD5C, &this->unk434);
    }
    if (limbIndex == 20) {
        Matrix_MultVec3f(&D_809BDD68, &sp28);
        func_809B21F4(this, 0, &this->unk594, &sp28);
    }
    if (limbIndex == 21) {
        Matrix_MultVec3f(&D_809BDD74, &sp28);
        func_809B21F4(this, 1, &this->unk594, &sp28);
    }
    if (limbIndex == 6 && this->actionFunc != func_809B6764) {
        Matrix_MultVec3f(&D_809BDD18, &sp28);
        func_809B21F4(this, 0, &this->unk534, &sp28);
        Matrix_MultVec3f(&D_809BDD24, &this->unk47C);
    }
    if (limbIndex == 11) {
        Matrix_MultVec3f(&D_809BDD30, &sp28);
        func_809B21F4(this, 0, &this->unk4D4, &sp28);
    }
    if (limbIndex == 28) {
        Matrix_MultZero(this->unk2AC);
    }
    if (limbIndex == 25) {
        Matrix_MultZero(&this->unk2AC[1]);
    }
}

void func_809BCA80(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnKnight* this = THIS;

    if (limbIndex == 15) {
        Matrix_MultVec3f(&D_809BDD80, &this->actor.focus.pos);
        Math_Vec3f_Copy(&this->unk434, &this->actor.focus.pos);
    }
}

void func_809BCAD8(PlayState* play, s32 limbIndex, Actor* thisx, Gfx** gfx) {
    EnKnight* this = THIS;

    if (this == D_809BEFD0) {
        if (limbIndex == 6) {
            Matrix_Scale(this->unk470, this->unk470, this->unk470, MTXMODE_APPLY);
        } else if (limbIndex == 11) {
            Matrix_Scale(this->unk46C, this->unk46C, this->unk46C, MTXMODE_APPLY);
        }
    }
}

Gfx* func_809BCB54(GraphicsContext* gfxCtx) {
    Gfx* gfx = GRAPH_ALLOC(gfxCtx, 2 * sizeof(Gfx));
    gSPEndDisplayList(gfx);
    return gfx;
}

Gfx* func_809BCB78(GraphicsContext* gfxCtx, u8 alpha) {
    Gfx* dList = GRAPH_ALLOC(gfxCtx, 6 * sizeof(Gfx));
    Gfx* gfx = dList;

    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, COMBINED, 0, ENVIRONMENT,
                      0);
    gDPSetEnvColor(gfx++, 255, 255, 255, alpha);
    gDPSetRenderMode(gfx++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
    gSPClearGeometryMode(gfx++, G_CULL_BACK);
    gSPEndDisplayList(gfx++);
    return dList;
}

void EnKnight_Draw(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;
    f32 temp_fa0;
    s32 sp6C = false;

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0A, func_809BCB54(play->state.gfxCtx));
    gSPSegment(POLY_XLU_DISP++, 0x0A, func_809BCB54(play->state.gfxCtx));

    if (this->unk17C >= 254.0f) {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x09, func_809BCB54(play->state.gfxCtx));
    } else {
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x09, func_809BCB78(play->state.gfxCtx, (u32)this->unk17C));
        sp6C = true;
    }

    if (this->unk158 & 1) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }

    if (this->actionFunc == func_809B5698) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 255, 900, 1099);
    }

    if (this == D_809BEFDC) {
        Matrix_Translate(this->unk164.x, this->unk164.y, this->unk164.z, MTXMODE_APPLY);
        SkelAnime_DrawFlexOpa(play, this->unk194.skeleton, this->unk194.jointTable, this->unk194.dListCount,
                              func_809BC67C, func_809BCA80, &this->actor);
    } else {
        if (this == D_809BEFD0 && sp6C) {
            POLY_XLU_DISP =
                SubS_DrawTransformFlex(play, this->unk194.skeleton, this->unk194.jointTable, this->unk194.dListCount,
                                       func_809BC720, func_809BC8B4, func_809BCAD8, &this->actor, POLY_XLU_DISP);
        } else {
            POLY_OPA_DISP =
                SubS_DrawTransformFlex(play, this->unk194.skeleton, this->unk194.jointTable, this->unk194.dListCount,
                                       func_809BC720, func_809BC8B4, func_809BCAD8, &this->actor, POLY_OPA_DISP);
        }

        if (this->unk450 > 0.0f) {
            func_809BC2C4(this, play);
            Math_ApproachZeroF(&this->unk450, 1.0f, 40.0f);
            this->unk44C++;
            if (this->unk44C >= 3) {
                this->unk44C = 2;
            }
        } else {
            this->unk44C = 0;
        }

        Actor_DrawDamageEffects(play, &this->actor, this->unk1DC, 15, this->unk294, this->unk298, this->unk29C,
                                this->unk2A0);

        if (this->unk474 > 0.01f) {
            Gfx_SetupDL25_Xlu(play->state.gfxCtx);

            gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(sREG(18) + 0xDC), (u8)(sREG(16) + 0xAA));
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(sREG(22) + 0x64), 128);

            Matrix_Translate(this->unk47C.x, this->unk47C.y, this->unk47C.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_RotateZS(play->gameplayFrames * 0x80, MTXMODE_APPLY);

            temp_fa0 = (sREG(17) + 600) * 0.01f * this->unk474;
            Matrix_Scale(temp_fa0, temp_fa0, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
        }
    }

    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);

    if (this == D_809BEFD0) {
        func_809BD858(this, play);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_809BD1AC(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;
    f32 var_fv0;

    if (this->actor.params == 0xCA) {
        var_fv0 = BREG(75) + 15.0f;
    } else {
        var_fv0 = BREG(78) + 8.0f;
    }
    Math_ApproachZeroF(&this->unk17C, 1.0f, var_fv0);
    if (this->unk17C < 0.1f) {
        Actor_Kill(&this->actor);
    }
}

s32 func_809BD260(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnKnight* this = THIS;

    if (this->actor.params == 0xCA && limbIndex != 18 && limbIndex != 19) {
        *dList = NULL;
    }
    return 0;
}

void func_809BD29C(Actor* thisx, PlayState* play) {
    EnKnight* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gSPSegment(POLY_XLU_DISP++, 0x09, func_809BCB78(play->state.gfxCtx, this->unk17C));
    gSPSegment(POLY_XLU_DISP++, 0x0A, func_809BCB78(play->state.gfxCtx, this->unk17C));
    Matrix_Translate(this->unk164.x, this->unk164.y, this->unk164.z, MTXMODE_APPLY);
    POLY_XLU_DISP = SkelAnime_DrawFlex(play, this->unk194.skeleton, this->unk194.jointTable, this->unk194.dListCount,
                                       func_809BD260, NULL, &this->actor, POLY_XLU_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_809BD490(EnKnight* this, PlayState* play) {
    EnKnightEffect* var_s0 = play->specialEffects;
    Player* player = GET_PLAYER(play);
    s32 var_s4;

    for (var_s4 = 0; var_s4 < 100; var_s4++, var_s0++) {
        if (var_s0->unk2A != 0) {
            var_s0->unk0.x += var_s0->unkC.x;
            var_s0->unk0.y += var_s0->unkC.y;
            var_s0->unk0.z += var_s0->unkC.z;

            var_s0->unk2C++;

            var_s0->unkC.x += var_s0->unk18.x;
            var_s0->unkC.y += var_s0->unk18.y;
            var_s0->unkC.z += var_s0->unk18.z;

            var_s0->unk18.y = BREG(56) * 0.01f + 1.0f;

            if (var_s0->unk2A == (u32)1) { // fake
                Math_ApproachF(&var_s0->unk34, (KREG(59) * 0.01f + 1.0f) * var_s0->unk38, 0.1f, var_s0->unk38 * 0.1f);

                if (((s16)(BREG(60) + 0x6E) >= var_s0->unk2E) ||
                    (var_s0->unk0.y < (BREG(62) + (this->actor.floorHeight + 30.0f)))) {
                    if ((s16)(BREG(60) + 0x6E) < var_s0->unk2E) {
                        var_s0->unk2E = BREG(60) + 0x6E;
                    }
                    var_s0->unk18.y = BREG(61) * 0.01f + 0.3f;

                    var_s0->unkC.x *= 0.85f + BREG(59) * 0.01f;
                    var_s0->unkC.z *= 0.85f + BREG(59) * 0.01f;

                    var_s0->unk38 = (BREG(58) * 0.1f + 2.0f) * 0.025f;

                    if (var_s0->unkC.y < 0.0f) {
                        var_s0->unkC.y = 0.0f;
                    }
                }
                var_s0->unk2E -= (s16)(BREG(49) + 0xA);
                if (var_s0->unk2E <= 0) {
                    var_s0->unk2E = 0;
                    var_s0->unk2A = 0;
                }
                if (this->unk15E == 0) {
                    f32 temp_fv0_3 = player->actor.world.pos.x - var_s0->unk0.x;
                    f32 temp_fv1_2 = (player->actor.world.pos.y + 25.0f) - var_s0->unk0.y;
                    f32 temp_fa0_2 = player->actor.world.pos.z - var_s0->unk0.z;
                    if ((SQ(temp_fv0_3) + SQ(temp_fv1_2) + SQ(temp_fa0_2)) <
                        ((BREG(57) * 0.1f + 1.0f) * ((2500.0f * var_s0->unk34) / 0.025f))) {
                        this->unk15E = 10;
                        func_800B8D10(play, &this->actor, 0.0f, 0, 0.0f, 1, 4);
                    }
                }
            }
        }
    }
}

void func_809BD858(EnKnight* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s16 i;
    u8 materialFlag = 0;
    EnKnightEffect* eff = play->specialEffects;

    OPEN_DISPS(gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gDPSetColorDither(POLY_XLU_DISP++, G_CD_BAYER);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_PATTERN);

    for (i = 0; i < 100; i++, eff++) {
        if (eff->unk2A != 1) {
            continue;
        }

        gDPPipeSync(POLY_XLU_DISP++);

        if (materialFlag == 0) {
            gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamMaterialDL);
            gDPSetEnvColor(POLY_XLU_DISP++, 155, 145, 155, 128);
            materialFlag++;
        }

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 155, 155, 255, eff->unk2E);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, (eff->unk2C + (i * 3)) * 3, (eff->unk2C + (i * 3)) * 15, 32,
                                    64, 1, 0, 0, 32, 32));

        Matrix_Translate(eff->unk0.x, eff->unk0.y, eff->unk0.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(eff->unk34, eff->unk34, 1.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamModelDL);
    }

    CLOSE_DISPS(gfxCtx);
}
