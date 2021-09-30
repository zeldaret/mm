#include "z_boss_07.h"
#include "overlays/actors/ovl_Obj_Tsubo/z_obj_tsubo.h"

#define FLAGS 0x00000035

#define THIS ((Boss07*)thisx)

// #define FACING_ANGLE(actor1, actor2) BINANG_SUB(BINANG_ROT180((actor1)->shape.rot.y), (actor2)->shape.rot.y)
#define FACING_ANGLE(actor1, actor2) ((s16)((actor1)->shape.rot.y - (actor2)->shape.rot.y + 0x8000))

void Boss07_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Destroy(Actor* thisx, GlobalContext* globalCtx);

void Boss07_Wrath_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Effects_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Remains_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Top_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Projectile_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Mask_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Incarnation_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Afterimage_Update(Actor* thisx, GlobalContext* globalCtx);

void Boss07_Wrath_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Effects_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Remains_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Top_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Projectile_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Mask_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Incarnation_Draw(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Afterimage_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809F4BB0(s32 arg0, ColliderJntSph* arg1, Vec3f* arg2);
s32 func_809FF678(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_809FF6B0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_809FF810(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx);
void func_80A07740(GlobalContext* globalCtx);
void func_809FBF94(Boss07* this, GlobalContext* globalCtx);
void func_80A03238(Boss07* this, GlobalContext* globalCtx, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, Vec3f* arg5,
                   Vec3f* arg6, f32 arg7, u8 arg8, f32 arg9);
void func_80A036C4(Boss07* this, GlobalContext* globalCtx, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5);
void func_80A03868(Boss07* this, GlobalContext* globalCtx);
void func_80A03F18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Boss07* this);
void func_809FAA44(Boss07* this, GlobalContext* globalCtx, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, Vec3f* arg5, f32 arg6,
                   f32 arg7, f32 arg8, f32 arg9, Vec3s* argA, s16 argB, f32 argC, s32 argD);
void func_809FB114(Boss07* this, GlobalContext* globalCtx, Vec3f* arg2, Vec3f* arg3, f32 arg4, s32 arg5);
s32 func_809FB504(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_809FB55C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_809FB728(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx);
void func_809FB7D4(Boss07* this, GlobalContext* globalCtx);
void func_809FBB9C(Boss07* this, GlobalContext* globalCtx, Vec3f* arg2);
void func_809FC8B0(u8* arg0, Boss07* this, GlobalContext* globalCtx);
void func_809FC960(u8* arg0, Boss07* this, GlobalContext* globalCtx);
void func_809FC4C0(Boss07* this, u8* arg1, f32 arg2);
void func_809F7688(Boss07* this, GlobalContext* globalCtx);
void func_809F783C(Boss07* this, GlobalContext* globalCtx);
void func_809FFE64(Boss07* this, GlobalContext* globalCtx);
void func_80A006F4(Boss07* this, GlobalContext* globalCtx);
void func_80A025AC(Boss07* this, GlobalContext* globalCtx);
void func_809FEE70(Boss07* this, GlobalContext* globalCtx);
void func_809F51E8(Boss07* this, GlobalContext* globalCtx, u8 arg2);
void func_809F52CC(Boss07* this, GlobalContext* globalCtx);
void func_809F5494(Boss07* this, GlobalContext* globalCtx);
void func_809F64F4(Boss07* this, GlobalContext* globalCtx);
void func_809F7AB4(Boss07* this, GlobalContext* globalCtx);
void func_809F99C4(Boss07* this, GlobalContext* globalCtx);

void func_809F8AB0(Boss07* this, GlobalContext* globalCtx);
void func_809F8E68(Boss07* this, GlobalContext* globalCtx);
void func_809F8658(Boss07* this, GlobalContext* globalCtx);
void func_809F7D2C(Boss07* this, GlobalContext* globalCtx);
void func_809F4D10(Vec3f* arg0, f32 arg1);
void func_809F4FAC(GlobalContext* globalCtx);
void func_809F4AE8(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4);
void func_80A02B30(Boss07* this, GlobalContext* globalCtx);
void func_809F536C(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2);
void func_809F94AC(Vec3f* arg0, f32 arg1, Boss07* this, GlobalContext* globalCtx);
void func_809F4FF8(GlobalContext* globalCtx, Vec3f* arg1, u8 arg2);
s32 func_809F4C40(Boss07* this, GlobalContext* globalCtx);
void func_809F4CBC(Boss07* this, f32 arg1);
void func_809F4D54(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3);
void func_809FCBC8(Boss07* this);
void func_80A07638(GlobalContext* globalCtx);
void func_809F9CEC(Boss07* this, GlobalContext* globalCtx);
void func_80A06500(Boss07* this, GlobalContext* globalCtx);
void func_80A06990(Boss07* this, GlobalContext* globalCtx);
void func_809F9E94(Boss07* this, GlobalContext* globalCtx);
void func_809F8DEC(Boss07* this, GlobalContext* globalCtx);
void func_809F9280(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3);

void func_809FD984(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3);
void func_809FD818(Boss07* this, GlobalContext* globalCtx, s16 arg2);
void func_809FE6B0(Boss07* this, GlobalContext* globalCtx);
void func_80A00484(Boss07* this, GlobalContext* globalCtx, u8 arg2, Actor* arg3);
void func_80A0021C(Boss07* this, GlobalContext* globalCtx);
void func_809FDB2C(Boss07* this, GlobalContext* globalCtx);
void func_809F5E14(Boss07* this, GlobalContext* globalCtx);
void func_809F7400(Boss07* this, GlobalContext* globalCtx, s16 arg2);
void func_809FCC70(Boss07* this, GlobalContext* globalCtx);
void func_809FD5F8(Boss07* this, GlobalContext* globalCtx);
void func_809FFA04(Boss07* this, GlobalContext* globalCtx);
void func_80A016E4(Boss07* this, GlobalContext* globalCtx);
void func_80A04878(Boss07* this, GlobalContext* globalCtx);
void func_80A04DE0(Boss07* this, GlobalContext* globalCtx);
void func_80A05AF8(Boss07* this, GlobalContext* globalCtx);

void func_809F5E88(Boss07* this, GlobalContext* globalCtx);
void func_809F65F4(Boss07* this, GlobalContext* globalCtx);
void func_809F748C(Boss07* this, GlobalContext* globalCtx);
void func_809F76D0(Boss07* this, GlobalContext* globalCtx);
void func_809F77A8(Boss07* this, GlobalContext* globalCtx);
void func_809F7968(Boss07* this, GlobalContext* globalCtx);
void func_809F7BC4(Boss07* this, GlobalContext* globalCtx);
void func_809F805C(Boss07* this, GlobalContext* globalCtx);
void func_809F86B8(Boss07* this, GlobalContext* globalCtx);
void func_809F87C8(Boss07* this, GlobalContext* globalCtx);
void func_809F8908(Boss07* this, GlobalContext* globalCtx);
void func_809F8B1C(Boss07* this, GlobalContext* globalCtx);
void func_809F8D04(Boss07* this, GlobalContext* globalCtx);
void func_809F8EC8(Boss07* this, GlobalContext* globalCtx);
void func_809F91D4(Boss07* this, GlobalContext* globalCtx);
void func_809F93DC(Boss07* this, GlobalContext* globalCtx);
void func_809FCCCC(Boss07* this, GlobalContext* globalCtx);
void func_809FD710(Boss07* this, GlobalContext* globalCtx);
void func_809FD89C(Boss07* this, GlobalContext* globalCtx);
void func_809FDAB0(Boss07* this, GlobalContext* globalCtx);
void func_809FDBA0(Boss07* this, GlobalContext* globalCtx);
void func_809FDF54(Boss07* this, GlobalContext* globalCtx);
void func_809FE0E4(Boss07* this, GlobalContext* globalCtx);
void func_809FE348(Boss07* this, GlobalContext* globalCtx);
void func_809FE524(Boss07* this, GlobalContext* globalCtx);
void func_809FE734(Boss07* this, GlobalContext* globalCtx);
void func_809FFA80(Boss07* this, GlobalContext* globalCtx);
void func_809FFEAC(Boss07* this, GlobalContext* globalCtx);
void func_80A00274(Boss07* this, GlobalContext* globalCtx);
void func_80A00554(Boss07* this, GlobalContext* globalCtx);
void func_80A00720(Boss07* this, GlobalContext* globalCtx);
void func_80A01750(Boss07* this, GlobalContext* globalCtx);
void func_80A0264C(Boss07* this, GlobalContext* globalCtx);
void func_80A04890(Boss07* this, GlobalContext* globalCtx);
void func_80A04E5C(Boss07* this, GlobalContext* globalCtx);
void func_80A05608(Boss07* this, GlobalContext* globalCtx);
void func_80A05B50(Boss07* this, GlobalContext* globalCtx);
void func_80A05DDC(Boss07* this, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A07980 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079A0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(4, 0xC),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079C0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(1, 0xE),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xC),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A079E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xE),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xE),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A07A00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(1, 0xE),
    /* Explosives     */ DMG_ENTRY(1, 0xB),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(1, 0xC),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0xD),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xA),
    /* Sword beam     */ DMG_ENTRY(1, 0xA),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xB),
};

const ActorInit Boss_07_InitVars = {
    ACTOR_BOSS_07,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS07,
    sizeof(Boss07),
    (ActorFunc)Boss07_Init,
    (ActorFunc)Boss07_Destroy,
    (ActorFunc)Boss07_Wrath_Update,
    (ActorFunc)Boss07_Wrath_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07A40[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07BCC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    11, D_80A07A40, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07BDC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 80, 200, 0, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A07C08[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 200 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07C2C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A07C08, // sJntSphElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C3C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C8C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07CDC[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 40 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07E68 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    11, D_80A07CDC, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07E78 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0x00300000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 30, -15, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07EA4 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 50, 100, -50, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07ED0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 40, 20, 15, { 0, 0, 0 } },
};

#endif

extern s16 D_80A07968[4][3];
extern s16 D_80A07950[4][3];
extern s16 D_80A07952[3];
extern DamageTable D_80A07980;
extern DamageTable D_80A079A0;
extern DamageTable D_80A079C0;
extern DamageTable D_80A079E0;
extern DamageTable D_80A07A00;
extern ColliderJntSphElementInit D_80A07A40[11];
extern ColliderJntSphInit D_80A07BCC;
extern ColliderCylinderInit D_80A07BDC;
extern ColliderJntSphElementInit D_80A07C08[1];
extern ColliderJntSphInit D_80A07C2C;
extern ColliderQuadInit D_80A07C3C;
extern ColliderQuadInit D_80A07C8C;
extern ColliderJntSphElementInit D_80A07CDC[11];
extern ColliderJntSphInit D_80A07E68;
extern ColliderCylinderInit D_80A07E78;
extern ColliderCylinderInit D_80A07EA4;
extern ColliderCylinderInit D_80A07ED0;
extern Color_RGBA8 D_80A07EFC;
extern Color_RGBA8 D_80A07F00;
extern Color_RGBA8 D_80A07F04;
extern Color_RGBA8 D_80A07F08;
extern Vec3f D_80A07F0C[4];
extern Vec3s D_80A07F3C[4];
extern s16 D_80A07F54[4];
extern EffTireMarkInit D_80A07F5C;
extern EffTireMarkInit D_80A07F64;
extern f32 D_80A07F6C[][3];
extern Vec3f D_80A07FA8;
extern Vec3f D_80A07FB4;
extern Vec3f D_80A07FC0;
extern Color_RGBA8 D_80A07FCC;
extern Color_RGBA8 D_80A07FD0;
extern Vec3f D_80A07FD4;
extern Vec3f D_80A07FE0;
extern s8 D_80A07FEC[32];
extern Vec3f D_80A0800C[11];
extern s8 D_80A08090[32];
extern Vec3f D_80A080B0;
extern s32 D_80A080BC[6];
extern s32 D_80A080D4[7];
extern s32 D_80A080F0[8];
extern s32 D_80A08110[12];
extern s32 D_80A08140[15];
extern u8 D_80A0817C[15];
extern AnimationHeader* D_80A0818C[3];
extern u8 D_80A08198[8];
extern u8 D_80A081A0[8];
extern s8 D_80A081A8[32];
extern s8 D_80A081C8[32];
extern Vec3f D_80A081E8[11];
extern s8 D_80A0826C[32];
extern Vec3s D_80A0828C[4];
extern Vec3s D_80A082A4[4];
extern Vec3f D_80A082BC;
extern Vec3f D_80A082C8;
extern Vec3f D_80A082D4;
extern void* D_80A082E0[2];

// extern Vec3f D_80A084D8;

extern Vec3f D_80A09A40;
extern u8 D_80A09A4C;
extern s32 D_80A09A50;
extern Boss07* D_80A09A54;
extern Boss07* D_80A09A58;
extern Boss07* D_80A09A5C;
extern Boss07* D_80A09A60[4];
extern u8 D_80A09A70;
extern u8 D_80A09A71;
extern Boss07Effect D_80A09A78[50];
extern s32 D_80A0A888;
extern s32 D_80A0A88C;
extern s32 D_80A0A890;

extern UNK_TYPE D_06000194;
extern UNK_TYPE D_06000428;
extern AnimationHeader D_06000D0C;
extern UNK_TYPE D_06002C40;
extern AnimationHeader D_06002D84;
extern UNK_TYPE D_06003854;
extern UNK_TYPE D_06003A64;
extern FlexSkeletonHeader D_060099A0;
extern AnimationHeader D_06009C7C;
extern UNK_TYPE D_06009EA8;
extern UNK_TYPE D_0600A194;
extern AnimationHeader D_0600A400;
extern AnimationHeader D_0600A6AC;
extern AnimationHeader D_0600AE40;
extern Gfx D_0600AFB0[];
extern UNK_TYPE D_0600B020;
extern UNK_TYPE D_0600C7D8;
extern Gfx D_0600CEE8[];
extern Gfx D_060149A0[];
extern Gfx D_06016090[];
extern Gfx D_06017DE0[];
extern Gfx D_06019328[];
extern SkeletonHeader D_06019C58;
extern AnimationHeader D_06019E48;
extern AnimationHeader D_0601DEB4;
extern AnimationHeader D_06022BB4;
extern AnimationHeader D_06023DAC;
extern UNK_TYPE D_06025018;
extern AnimationHeader D_06025878;
extern AnimationHeader D_06026204;
extern AnimationHeader D_060269EC;
extern AnimationHeader D_06026EA0;
extern UNK_TYPE D_06027270;
extern Gfx D_0602EE50[];
extern Gfx D_0602EEC8[];
extern Gfx D_0602EEF8[];
extern Gfx D_0602EF68[];
extern Gfx D_0602EF88[];
extern Gfx D_0602EFE8[];
extern Gfx D_0602F640[];
extern UNK_TYPE D_0602F840; // title card
extern UNK_TYPE D_06032040; // title card
extern FlexSkeletonHeader D_060335F0;
extern AnimationHeader D_06033F80;
extern AnimationHeader D_06034E64;
extern AnimationHeader D_060358C4;
extern AnimationHeader D_06036A7C;
extern AnimationHeader D_06037ADC;
extern AnimationHeader D_0603918C;
extern AnimationHeader D_0603B330;
extern AnimationHeader D_0603C4E0;
extern AnimationHeader D_0603CBD0;
extern AnimationHeader D_0603D224;
extern AnimationHeader D_0603D7F0;
extern AnimationHeader D_0603DD1C;
extern u16 D_0603DD30[];
extern u16 D_0603ED30[];
extern u16 D_0603F130[];
extern u16 D_06040130[];
extern u16 D_06040930[];
extern u16 D_06040B30[];
extern u16 D_06041B30[];
extern u16 D_06042330[];
extern u16 D_06043330[];

void func_809F4980(Actor* arg0) {
    Audio_PlayActorSound2(arg0, NA_SE_EN_FOLLOWERS_DAMAGE);
}

void func_809F49A0(s32 seedInit0, s32 seedInit1, s32 seedInit2) {
    D_80A0A888 = seedInit0;
    D_80A0A88C = seedInit1;
    D_80A0A890 = seedInit2;
}

f32 func_809F49C0(void) {
    // Wichmann-Hill algorithm
    f32 randFloat;

    D_80A0A888 = (D_80A0A888 * 171) % 30269;
    D_80A0A88C = (D_80A0A88C * 172) % 30307;
    D_80A0A890 = (D_80A0A890 * 170) % 30323;

    randFloat = (D_80A0A888 / 30269.0f) + (D_80A0A88C / 30307.0f) + (D_80A0A890 / 30323.0f);
    while (randFloat >= 1.0f) {
        randFloat -= 1.0f;
    }
    return fabsf(randFloat);
}

void func_809F4AE8(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4) {
    s32 i;
    Boss07Effect* effect = (Boss07Effect*)globalCtx->specialEffects;

    for (i = 0; i < 50; i++, effect++) {
        if (effect->unk_0 == 0) {
            effect->unk_0 = 1;
            effect->unk_4 = *arg1;
            effect->unk_10 = *arg2;
            effect->unk_1C = *arg3;
            effect->unk_34 = arg4 / 1000.0f;
            effect->unk_30 = 0;
            effect->unk_2C = 0;
            effect->unk_2 = Rand_ZeroFloat(1000.0f);
            break;
        }
    }
}

void func_809F4BB0(s32 arg0, ColliderJntSph* arg1, Vec3f* arg2) {
    arg1->elements[arg0].dim.worldSphere.center.x = arg2->x;
    arg1->elements[arg0].dim.worldSphere.center.y = arg2->y;
    arg1->elements[arg0].dim.worldSphere.center.z = arg2->z;
    arg1->elements[arg0].dim.worldSphere.radius =
        arg1->elements[arg0].dim.modelSphere.radius * arg1->elements[arg0].dim.scale;
}

s32 func_809F4C40(Boss07* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y)) < 0x3000) &&
        (ABS_ALT((s16)(this->actor.yawTowardsPlayer - (s16)(player->actor.shape.rot.y + 0x8000))) < 0x3000)) {
        return 1;
    }
    return 0;
}

void func_809F4CBC(Boss07* this, f32 arg1) {
    Math_ApproachZeroF(&this->actor.speedXZ, 1.0f, arg1);
    if (this->actor.bgCheckFlags & 0x18) {
        this->actor.speedXZ = 0.0f;
    }
}

void func_809F4D10(Vec3f* arg0, f32 arg1) {
    SysMatrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), 0);
    SysMatrix_GetStateTranslationAndScaledZ(arg1, arg0);
}

void func_809F4D54(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3) {
    u8 phi_s1;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;

    if (!(this->unk_14C & arg2) && ((arg2 == 0) || (this->actor.speedXZ > 1.0f))) {
        for (phi_s1 = 0; phi_s1 < 2; phi_s1++) {
            spA4.x = randPlusMinusPoint5Scaled(5.0f);
            spA4.y = Rand_ZeroFloat(2.0f) + 1.0f;
            spA4.z = randPlusMinusPoint5Scaled(5.0f);
            sp98.x = sp98.z = 0.0f;
            sp98.y = -0.1f;
            spB0.y = Rand_ZeroFloat(10.0f) + 3.0f;
            if (arg3) {
                spB0.x = randPlusMinusPoint5Scaled(150.0f) + this->actor.focus.pos.x;
                spB0.z = randPlusMinusPoint5Scaled(150.0f) + this->actor.focus.pos.z;
            } else {
                spB0.z = this->unk_1788[phi_s1].z + randPlusMinusPoint5Scaled(20.0f);
                spB0.x = this->unk_1788[phi_s1].x + randPlusMinusPoint5Scaled(20.0f);
            }
            func_800B0EB0(globalCtx, &spB0, &spA4, &sp98, &D_80A07EFC, &D_80A07F00, Rand_ZeroFloat(150.0f) + 350.0f, 10,
                          Rand_ZeroFloat(5.0f) + 14.0f);
        }
    }
}

void func_809F4FAC(GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (SQXZ(player->actor.world.pos) < SQ(80.0f)) {
        player->actor.world.pos.z = 90.0f;
    }
}

void func_809F4FF8(GlobalContext* globalCtx, Vec3f* arg1, u8 arg2) {
    u8 i;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;

    for (i = 0; i < arg2; i++) {
        spA4.x = randPlusMinusPoint5Scaled(3.0f);
        spA4.y = Rand_ZeroFloat(2.0f) + 1.0f;
        spA4.z = randPlusMinusPoint5Scaled(3.0f);
        sp98.x = sp98.z = 0.0f;
        sp98.y = -0.1f;
        spB0.x = randPlusMinusPoint5Scaled(30.0f) + arg1->x;
        spB0.y = randPlusMinusPoint5Scaled(30.0f) + (arg1->y + 15.0f);
        spB0.z = randPlusMinusPoint5Scaled(30.0f) + arg1->z;
        func_800B0EB0(globalCtx, &spB0, &spA4, &sp98, &D_80A07F04, &D_80A07F08, Rand_ZeroFloat(50.0f) + 100.0f, 10,
                      Rand_ZeroFloat(5.0f) + 14.0f);
    }
}

void func_809F51E8(Boss07* this, GlobalContext* globalCtx, u8 arg2) {
    Player* player = PLAYER;

    if ((this->unk_15C == 0) && (((this->actionFunc != func_809F7968) && (this->actionFunc != func_809F76D0) &&
                                  (this->actionFunc != func_809F77A8)) ||
                                 (arg2 != 0))) {
        if (Rand_ZeroOne() < 0.5f) {
            func_809F783C(this, globalCtx);
        } else {
            func_809F7688(this, globalCtx);
        }
        this->unk_158 = 10;
        this->unk_F7E = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->unk_394 = 0;
        }
    }
}

void func_809F52CC(Boss07* this, GlobalContext* globalCtx) {
    Actor* phi_v0 = globalCtx->actorCtx.actorList[ACTORCAT_EXPLOSIVES].first;

    while (phi_v0 != NULL) {
        f32 dx = phi_v0->world.pos.x - this->actor.world.pos.x;
        f32 dy = phi_v0->world.pos.y - this->actor.world.pos.y;
        f32 dz = phi_v0->world.pos.z - this->actor.world.pos.z;

        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 200.0f) {
            func_809F51E8(this, globalCtx, 0);
            return;
        }
        phi_v0 = phi_v0->next;
    }
}

void func_809F536C(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2) {
    s32 i;
    f32 push;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f sp50;

    sp50.x = 0.0f;

    for (i = 0; i < D_80A09A50; i++, arg1++, arg2++) {
        dx = arg1->x - arg0->x;
        dy = arg1->y - arg0->y;
        dz = arg1->z - arg0->z;

        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 300.0f) {

            push = 300.0f - sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
            push = CLAMP_MAX(push, 200.0f);

            sp50.y = push;
            sp50.z = push;
            SysMatrix_InsertYRotation_f(Math_Acot2F(dz, dx), 0);
            SysMatrix_MultiplyVector3fByState(&sp50, arg2);
        }
    }
}

void func_809F5494(Boss07* this, GlobalContext* globalCtx) {
    Actor* phi_s0 = globalCtx->actorCtx.actorList[3].first;

    while (phi_s0 != NULL) {
        if (phi_s0->params == 1) {
            func_809F536C(&phi_s0->world.pos, this->unk_7AC, this->unk_C5C);
            func_809F536C(&phi_s0->world.pos, this->unk_FB8, this->unk_1468);
        }
        phi_s0 = phi_s0->next;
    }
}

#ifdef NON_MATCHING
void Boss07_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;

    if (this->actor.params == 150) {
        this->actor.update = Boss07_Effects_Update;
        this->actor.draw = Boss07_Effects_Draw;
        this->actor.flags &= ~1;
        D_80A09A58 = this;
        D_80A09A70 = 0;
        globalCtx->envCtx.unk_C3 = 0;
        globalCtx->envCtx.unk_E0 = 2;
    } else {
        if (this->actor.params == 0) {
            Boss07Effect* effect;

            this->actor.params = 10;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_07, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 150);
            globalCtx->specialEffects = D_80A09A78;
            for (effect = D_80A09A78; effect < &D_80A09A78[50]; effect++) {
                effect->unk_0 = 0;
            }
            for (i = 0; i < 4; i++) {
                D_80A09A60[i] = NULL;
            }
        }
        this->actor.targetMode = 5;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        this->actor.gravity = -2.5f;
        if (this->actor.params >= 200) {
            this->actor.update = Boss07_Remains_Update;
            this->actor.draw = Boss07_Remains_Draw;
            D_80A09A60[(u32)this->actor.params - 200] = this;
            if (gSaveContext.eventInf[6] & 2) {
                Actor_SetScale(&this->actor, 0.03f);
                this->actor.world.pos.x = D_80A07F3C[this->actor.params - 200].x;
                this->actor.world.pos.y = 370.0f;
                this->actor.world.pos.z = D_80A07F3C[this->actor.params - 200].z;
                this->actor.shape.rot.y = D_80A07F3C[this->actor.params - 200].y;
                func_80A04DE0(this, globalCtx);
            } else {
                func_80A04878(this, globalCtx);
            }
            this->actor.flags &= ~1;
            this->actor.colChkInfo.damageTable = &D_80A079E0;
        } else if (this->actor.params == 180) {
            this->actor.update = Boss07_Top_Update;
            this->actor.draw = Boss07_Top_Draw;

            func_80A05AF8(this, globalCtx);
            this->actor.colChkInfo.damageTable = &D_80A07A00;
            ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, KREG(55) + 9.0f);
            this->actor.shape.shadowAlpha = 180;
            Collider_InitAndSetCylinder(globalCtx, &this->cyl2, &this->actor, &D_80A07ED0);
            Effect_Add(globalCtx, &this->effectIndex, 4, 0, 0, &D_80A07F5C);
            this->actor.flags &= ~1;
        } else if ((this->actor.params == 100) || (this->actor.params == 101)) {
            this->actor.update = Boss07_Projectile_Update;
            this->actor.draw = Boss07_Projectile_Draw;
            this->actor.flags &= ~1;
            Collider_InitAndSetCylinder(globalCtx, &this->cyl2, &this->actor, &D_80A07E78);
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_ENEMY);
            this->unk_181C = Rand_ZeroFloat(3.99f);
        } else if ((this->actor.params == 10) || (this->actor.params == 11)) {
            this->actor.colChkInfo.damageTable = &D_80A07980;
            ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 15.0f);
            SkelAnime_Init(globalCtx, &this->skelAnime1, &D_06019C58, &D_06019E48, this->jointTable1, this->morphTable1,
                           19);
            if (this->actor.params == 10) {
                this->actor.update = Boss07_Mask_Update;
                this->actor.draw = Boss07_Mask_Draw;
                Effect_Add(globalCtx, &this->effectIndex, 4, 0, 0, &D_80A07F64);
                D_80A09A5C = this;
                if (gSaveContext.eventInf[6] & 2) {
                    this->actor.world.pos.x = 0.0f;
                    this->actor.world.pos.y = sREG(17) + 277.0f;
                    this->actor.world.pos.z = -922.5f;
                    func_809FFA04(this, globalCtx);
                    this->unk_164.x = 0.0f;
                    this->unk_164.y = 200.0f;
                    this->unk_164.z = 0.0f;
                    this->unk_170 = 0.0f;
                    this->timers[0] = 50;
                    this->timers[2] = 200;
                    this->unk_1888 = 50;
                    this->actor.flags |= 1;
                    D_80A09A71 = 20;
                } else {
                    func_80A016E4(this, globalCtx);
                }
                Collider_InitAndSetQuad(globalCtx, &this->quad1, &this->actor, &D_80A07C3C);
                Collider_InitAndSetQuad(globalCtx, &this->quad2, &this->actor, &D_80A07C8C);
                this->actor.colChkInfo.health = 14;
                for (i = 0; i < 4; i++) {
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_07, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                                D_80A07F54[i]);
                }
            }
        } else if ((this->actor.params == 20) || (this->actor.params == 21)) {
            Actor_SetScale(&this->actor, 0.015000001f);
            SkelAnime_InitSV(globalCtx, &this->skelAnime1, &D_060099A0, &D_0600A6AC, this->jointTable1,
                             this->morphTable1, 25);
            if (this->actor.params == 21) {
                this->timers[0] = this->actor.world.rot.z;
                this->actor.world.rot.z = 0;
                this->actor.update = Boss07_Afterimage_Update;
                this->actor.draw = Boss07_Afterimage_Draw;
                this->actor.flags &= ~1;
            } else {
                this->actor.colChkInfo.damageTable = &D_80A079A0;
                this->actor.colChkInfo.health = 30;
                this->actor.update = Boss07_Incarnation_Update;
                this->actor.draw = Boss07_Incarnation_Draw;
                Collider_InitAndSetJntSph(globalCtx, &this->sph1, &this->actor, &D_80A07E68, this->sphElems1);
                ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 80.0f);
                this->unk_ABD2 = this->actor.shape.rot.z;
                if (this->unk_ABD2 != 0) {
                    func_809FCC70(this, globalCtx);
                } else {
                    func_809FD5F8(this, globalCtx);
                    this->unk_14A = 1;
                    this->unk_17B8[1] = 1.0f;
                    this->unk_17B8[2] = 1.0f;
                    this->unk_17B8[3] = 1.0f;
                    this->unk_17B8[0] = 1.0f;
                    globalCtx->envCtx.unk_DC = 0.0f;
                }
                this->unk_17E0 = 1.0f;
                this->unk_17E4 = 1.0f;
                this->unk_17F0 = 1.0f;
                this->unk_17F4 = 1.0f;
            }
        } else {
            D_80A09A54 = this;
            this->actor.colChkInfo.health = 40;
            this->actor.colChkInfo.damageTable = &D_80A079C0;
            Actor_SetScale(&this->actor, 0.01f);
            this->unk_ABD2 = this->actor.shape.rot.z;
            if (this->unk_ABD2 != 0) {
                func_809F5E14(this, globalCtx);
            } else {
                func_809F7400(this, globalCtx, 50);
                this->unk_77C = 1.0f;
                Audio_QueueSeqCmd(0x8069);
            }
            SkelAnime_InitSV(globalCtx, &this->skelAnime1, &D_060335F0, &D_0603CBD0, this->jointTable1,
                             this->morphTable1, 28);
            Collider_InitAndSetJntSph(globalCtx, &this->sph1, &this->actor, &D_80A07BCC, this->sphElems1);
            Collider_InitAndSetJntSph(globalCtx, &this->sph2, &this->actor, &D_80A07C2C, this->sphElems2);
            Collider_InitAndSetCylinder(globalCtx, &this->cyl1, &this->actor, &D_80A07BDC);
            this->unk_17E0 = 1.0f;
            this->unk_794 = 0.7f;
            this->unk_FA0 = 0.7f;
            this->unk_798 = 2.0f;
            this->unk_FA4 = 2.0f;
            this->unk_79C = 0.0f;
            this->unk_FA8 = 0.0f;
            this->unk_790 = -15.0f;
            this->unk_F9C = -15.0f;

            D_80A09A50 = 44;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Init.s")
#endif

void Boss07_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    switch (this->actor.params) {
        case 30:
            Collider_DestroyQuad(globalCtx, &this->quad1);
            Collider_DestroyQuad(globalCtx, &this->quad2);
        case 180:
            Effect_Destroy(globalCtx, this->effectIndex);
            break;
    }
}

void func_809F5E14(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F5E88;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_06023DAC, 0.0f);
    this->actor.flags &= ~1;
    this->unk_17D8 = 0x7F00;
    this->unk_15C = 20;
    this->unk_17E8 = 5120.0f;
}

#ifdef NON_MATCHING
void func_809F5E88(Boss07* this, GlobalContext* globalCtx) {
    this->unk_15C = 20;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_ABC8++;
    SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_RotateY(this->actor.shape.rot.y, 1);
    switch (this->unk_ABD0) {
        case 0:
            this->unk_ABC8 = 0;
            this->unk_ABD0 = 1;
            this->unk_ABF8.z = 0.f;
            this->unk_ABEC.x = 0.0;
            this->unk_ABEC.y = gGameInfo->data[1265] + 100.0f - 30.0f + 80.0f;
            this->unk_ABEC.z = gGameInfo->data[1266] + 270.0f - 150.0f + 30.0f - 50.0f;
            this->unk_ABF8.x = 0.0f;
            this->unk_ABF8.y = 180.0f;
        case 1:
            if (this->unk_ABC8 < 40) {
                D_80A09A4C = 3;
            }
            if (this->unk_ABC8 > 20) {
                if (this->unk_ABC8 == 21) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_GROW_HEAD_OLD);
                }
                Math_ApproachS(&this->unk_17D8, 0, 5, 0x1000);
                this->unk_17DA = Math_SinS(this->unk_ABC8 * 0x1000) * this->unk_17E8;
                this->unk_17DC = Math_SinS(this->unk_ABC8 * 0xB00) * this->unk_17E8 * 0.5f;
                if (this->unk_ABC8 > 40) {
                    Math_ApproachZeroF(&this->unk_17E8, 1.0f, 200.0f);
                }
            }
            if (this->unk_ABC8 >= 0x3D) {
                Player* player = PLAYER;
                s32 phi_v1 = 0;

                if (player->transformation == 1) {
                    phi_v1 = 1;
                } else if (player->transformation == 0) {
                    phi_v1 = 2;
                } else if (player->transformation == 2) {
                    phi_v1 = 3;
                } else if (player->transformation == 3) {
                    phi_v1 = 4;
                }

                Math_ApproachF(&this->unk_ABEC.y, D_80A07F6C[phi_v1][0], 0.075f, this->unk_AC0C * 7.0f);
                Math_ApproachF(&this->unk_ABEC.z, D_80A07F6C[phi_v1][1], 0.075f, this->unk_AC0C * 17.0f);
                Math_ApproachF(&this->unk_ABF8.y, D_80A07F6C[phi_v1][2], 0.075f, this->unk_AC0C * 7.0f);
                Math_ApproachF(&this->unk_AC0C, 1.0f, 1.0f, 0.01f);
                if (this->unk_ABC8 == 70) {
                    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06025018, -15.0f);
                    this->unk_1D4 = SkelAnime_GetFrameCount(&D_06025018);
                    func_8019FE1C(&this->actor.projectedPos, NA_SE_EV_ICE_PILLAR_RISING, 1.0f);
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_SHOUT);
                }
                if (this->unk_ABC8 >= 110) {
                    Math_ApproachF(&this->unk_77C, 1.0f, 1.0f, 0.05f);
                    this->unk_794 = 0.79999995f;
                    this->unk_FA0 = 0.79999995f;
                    this->unk_798 = 1.0f;
                    this->unk_FA4 = 1.0f;
                }
                if (this->unk_ABC8 == 127) {
                    this->unk_77C = 1.0f;
                }
                if (this->unk_ABC8 == 120) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST3_ROD_HOP2_OLD);
                    func_8019F1C0(&D_80A09A40, NA_SE_EN_LAST3_VOICE_KICK_OLD);
                    func_8019FE74(&D_801D6654, 0.0f, 0x3C);
                }
                if (this->unk_ABC8 == 112) {
                    Audio_QueueSeqCmd(0x8069);
                }
                if (this->unk_ABC8 == 137) {
                    Actor_TitleCardCreate(globalCtx, &globalCtx->actorCtx.titleCtxt,
                                          Lib_SegmentedToVirtual(&D_06032040), 0xA0, 0xB4, 0x80, 0x28);
                }
                if (func_801378B8(&this->skelAnime1, this->unk_1D4)) {
                    s32 i;
                    Camera* sp48 = Play_GetCamera(globalCtx, 0);

                    this->unk_ABD0 = 0;
                    func_809F7400(this, globalCtx, 50);
                    sp48->eye = this->unk_ABD4;
                    sp48->eyeNext = this->unk_ABD4;
                    sp48->at = this->unk_ABE0;
                    func_80169AFC(globalCtx, this->unk_ABD2, 0);
                    this->unk_ABD2 = 0;
                    func_800EA0EC(globalCtx, &globalCtx->csCtx);
                    func_800B7298(globalCtx, &this->actor, 6);
                    this->actor.flags |= 1;
                    func_80165690();
                    if (D_80A09A60[0] != NULL) {
                        for (i = 0; i < 4; i++) {
                            func_800BC154(globalCtx, &globalCtx->actorCtx, &D_80A09A60[i]->actor, 9);
                        }
                    }
                }
            }
            break;
    }
    SysMatrix_MultiplyVector3fByState(&this->unk_ABEC, &this->unk_ABD4);
    SysMatrix_MultiplyVector3fByState(&this->unk_ABF8, &this->unk_ABE0);
    if (this->unk_ABD2 != 0) {
        ShrinkWindow_SetLetterboxTarget(0x1B);
        Play_CameraSetAtEye(globalCtx, this->unk_ABD2, &this->unk_ABE0, &this->unk_ABD4);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5E88.s")
#endif

void func_809F64F4(Boss07* this, GlobalContext* globalCtx) {
    s32 i;

    Audio_QueueSeqCmd(0x100100FF);
    func_809F4FAC(globalCtx);
    this->actionFunc = func_809F65F4;
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06022BB4, 0.0f);
    this->actor.flags &= ~1;
    this->unk_ABD0 = 0;
    this->unk_ABC8 = 0;
    if (D_80A09A60[0] != NULL) {
        for (i = 0; i < 4; i++) {
            D_80A09A60[i]->unk_14E = 2;
        }
    }
    this->unk_15C = 1000;
}

#ifdef NON_MATCHING
void func_809F65F4(Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    s32 spC0 = 0;
    Vec3f spB4;
    Vec3f spA8 = D_80A07FA8;
    f32 spA4;
    f32 spA0;
    Camera* temp_s0;
    spA4 = 0.0f;
    spA0 = 0.1f;

    temp_s0 = Play_GetCamera(globalCtx, 0);
    this->unk_15C = 1000;
    func_809F4CBC(this, 1.0f);
    switch (this->unk_ABD0) {
        case 0:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                func_800EA0D4(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 1);
                this->unk_ABD2 = func_801694DC(globalCtx);
                func_80169590(globalCtx, 0, 1);
                func_80169590(globalCtx, this->unk_ABD2, 7);
                Audio_PlayActorSound2(&this->actor, 0x39B8);
            }
        case 1:
            this->unk_ABC8 = 0;
            this->unk_ABD0 = 2;
            this->unk_ABD4.x = temp_s0->eye.x;
            this->unk_ABD4.y = temp_s0->eye.y;
            this->unk_ABD4.z = temp_s0->eye.z;
            this->unk_ABE0.x = temp_s0->at.x;
            this->unk_ABE0.y = temp_s0->at.y;
            this->unk_ABE0.z = temp_s0->at.z;
            this->unk_AC04 = this->actor.shape.rot.y * M_PI / 0x8000;
            this->unk_AC08 = this->unk_AC0C = D_80A09A58->unk_180C = 0.0f;
            func_809F49A0(1, 0x71AC, 0x263A);
            for (i = 0; i < 30; i++) {
                this->unk_AB50[i] = func_809F49C0() - 1.0f;
            }
            func_8016566C(150);
        case 2:
            if (this->unk_ABC8 == 20) {
                func_8019F1C0(&D_80A09A40, 0x39E3);
            }
            if (this->unk_ABC8 == 40) {
                func_8019F1C0(&D_80A09A40, 0x39E3);
            }
            if (this->unk_ABC8 == 60) {
                func_8019F1C0(&D_80A09A40, 0x39E3);
            }
            if (this->unk_ABC8 == 0x50) {
                func_8019F1C0(&D_80A09A40, 0x39E3);
            }
            spB4.x = 0.0f;
            spB4.y = -90.0f;
            spB4.z = 350.0f;
            this->unk_ABF8.x = this->actor.focus.pos.x;
            this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f;
            this->unk_ABF8.z = this->actor.focus.pos.z;

            if ((this->unk_ABC8 >= 50) && (this->unk_ABC8 < 80)) {
                if (this->unk_ABC8 == 50) {
                    func_8019F1C0(&D_80A09A40, 0x39AF);
                }
                spB4.x = 30.0f;
                spB4.z = 120.0f;
                this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->unk_ABC8 >= 80) && (this->unk_ABC8 < 110)) {
                if (this->unk_ABC8 == 80) {
                    this->skelAnime1.animCurrentFrame -= 30.0f;
                    func_8019F1C0(&D_80A09A40, 0x39B4);
                }
                spB4.x = -10.0f;
                spB4.z = 150.0f;
                this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->unk_ABC8 >= 110) && (this->unk_ABC8 < 140)) {
                if (this->unk_ABC8 == 110) {
                    func_8019F1C0(&D_80A09A40, 0x39B5);
                }
                spB4.x = -70.0f;
                spB4.z = 110.0f;
                this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            }
            if (this->unk_ABC8 >= (gGameInfo->data[1551] + 140)) {
                this->unk_ABD0 = 4;
                this->unk_AC14 = gGameInfo->data[1552] + 270.0f + 50.0f;
                func_8019F1C0(&D_80A09A40, 0x39BF);
            } else {
                break;
            }
        case 4:
            if ((this->unk_ABC8 >= (gGameInfo->data[1626] + 260)) && (this->unk_ABC8 < (gGameInfo->data[1627] + 370))) {
                spC0 = gGameInfo->data[1262] + 1;
                this->unk_AC04 = this->actor.shape.rot.y * M_PI / 0x8000;
                spB4.x = 0.0f;
                spB4.y = this->unk_AC14 + -190.0f;
                spB4.z = gGameInfo->data[1553] + 390.0f - 380.0f;

                this->unk_ABF8.x = this->actor.focus.pos.x;
                this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f - 60.0f + 130.0f + gGameInfo->data[1554];
                this->unk_ABF8.z = this->actor.focus.pos.z;

                spA0 = 1.0f;

                Math_ApproachF(&this->unk_AC14, gGameInfo->data[1555] + 240.0f, 0.05f,
                               1.0f + (gGameInfo->data[1556] * 0.1f));
                spA4 = 2000.0f;
                this->unk_1D8 = gGameInfo->data[1329] + 10;
                this->unk_AB48 = 1;
                func_8019F1C0(&D_80A09A40, 0x205B);
            } else {
                spB4.x = 0.0f;
                spB4.y = -190.0f;
                spB4.z = 390.0f;
                this->unk_ABF8.x = this->actor.focus.pos.x;
                this->unk_ABF8.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                this->unk_ABF8.z = this->actor.focus.pos.z;
                this->unk_1D8 = 0;
                if (this->unk_ABC8 > 330) {
                    spA4 = 2000.0f;
                    spA0 = 1.0f;
                }
                Math_ApproachZeroF(&this->actor.world.pos.x, 0.1f, this->unk_AC0C);
                Math_ApproachZeroF(&this->actor.world.pos.z, 0.1f, this->unk_AC0C);
                Math_ApproachF(&this->unk_AC0C, 5.0f, 1.0f, 0.1f);
            }
            if (this->unk_ABC8 >= 260) {
                f32 sp98;
                f32 sp94;
                s16 temp_a0;

                if (this->unk_ABC8 == 260) {
                    func_801A479C(&D_80A09A40, 0x39B6, 0x3C);
                }
                globalCtx->envCtx.unk_E5 = 1;
                globalCtx->envCtx.unk_E6[0] = globalCtx->envCtx.unk_E6[1] = globalCtx->envCtx.unk_E6[2] = 0xFF;
                if (this->unk_ABC8 < 350) {
                    sp98 = 0.5f;
                    sp94 = 0.02f;
                    globalCtx->envCtx.unk_E6[3] = 0;
                } else {
                    sp98 = 5.0f;
                    sp94 = 0.1f;
                    temp_a0 = (this->unk_ABC8 * 2) - 700;
                    temp_a0 = CLAMP_MAX(temp_a0, 250);
                    globalCtx->envCtx.unk_E6[3] = temp_a0;
                    if (this->unk_ABC8 == 400) {
                        func_8019FE74(&D_801D6654, 0.0f, 90);
                    }
                    if (this->unk_ABC8 == (gGameInfo->data[1342] + 440)) {
                        globalCtx->nextEntranceIndex = 0x5400;
                        gSaveContext.nextCutsceneIndex = 0xFFF7;
                        globalCtx->sceneLoadFlag = 0x14;
                    }
                }
                if (this->unk_ABC8 > 300) {
                    D_80A09A58->unk_1808 = 1;
                    Math_ApproachF(&D_80A09A58->unk_180C, 30.0f, 0.1f, 1.5f);
                    D_80A09A58->unk_1810 = this->unk_334[2];
                    Math_ApproachF(&this->unk_AB4C, 1.0f, 0.1f, 0.05f);
                    for (i = 0; i < 30; i++) {
                        Math_ApproachF(&this->unk_AB50[i], sp98, 1.0f, sp94);
                    }
                    Math_ApproachF(&globalCtx->envCtx.unk_DC, 1.0f, 1.0f, 0.1f);
                }
            }
            this->unk_AC04 += this->unk_AC08;
            this->unk_AC08 += 0.0004f;
            if (this->unk_AC08 > 0.02f) {
                this->unk_AC08 = 0.02f;
            }
            if (this->unk_ABC8 >= (gGameInfo->data[1629] + 180)) {
                Vec3f sp84 = D_80A07FB4;
                Vec3f sp78 = D_80A07FC0;
                Vec3f sp6C;
                f32 sp68;

                play_sound(0x2159);
                sp68 = (spC0 == 0) ? 2.0f : (gGameInfo->data[1301] * 0.01f) + 0.2f;
                spA8.x = Math_SinS(this->unk_ABC8 * 0x7000) * sp68;
                spA8.y = Math_SinS(this->unk_ABC8 * 0x5000) * sp68 * 2.5f;
                spA8.z = Math_CosS(this->unk_ABC8 * 0x8000) * sp68;
                for (i = 0; i < 2; i++) {
                    sp6C.x = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.x;
                    sp6C.y = Rand_ZeroFloat(50.0f) + this->actor.world.pos.y + 200.0f;
                    sp6C.z = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.z;
                    EffectSsHahen_Spawn(globalCtx, &sp6C, &sp84, &sp78, 0, Rand_ZeroFloat(5.0f) + 20.0f, -1, 0xA, NULL);
                }
            }
            if (this->unk_ABC8 >= (gGameInfo->data[1630] + 290)) {
                this->unk_1D8 = gGameInfo->data[1334] + 25;
                Math_ApproachZeroF(&this->unk_77C, 1.0f, 0.015f);
            }
            break;
    }
    SysMatrix_InsertYRotation_f(this->unk_AC04, 0);
    SysMatrix_MultiplyVector3fByState(&spB4, &this->unk_ABEC);
    this->unk_ABEC.x += this->actor.focus.pos.x;
    this->unk_ABEC.y += this->actor.focus.pos.y;
    this->unk_ABEC.z += this->actor.focus.pos.z;

    Math_ApproachF(&this->unk_ABD4.x, this->unk_ABEC.x, spA0, 40.0f + spA4);
    Math_ApproachF(&this->unk_ABD4.y, this->unk_ABEC.y, spA0, 40.0f + spA4);
    Math_ApproachF(&this->unk_ABD4.z, this->unk_ABEC.z, spA0, 40.0f + spA4);

    Math_ApproachF(&this->unk_ABE0.x, this->unk_ABF8.x, spA0, 70.0f + spA4);
    Math_ApproachF(&this->unk_ABE0.y, this->unk_ABF8.y, spA0, 70.0f + spA4);
    Math_ApproachF(&this->unk_ABE0.z, this->unk_ABF8.z, spA0, 70.0f + spA4);
    if (this->unk_ABD2 != 0) {
        Vec3f sp5C;

        sp5C.x = this->unk_ABE0.x + spA8.x;
        sp5C.y = this->unk_ABE0.y + spA8.y;
        sp5C.z = this->unk_ABE0.z + spA8.z;
        Play_CameraSetAtEye(globalCtx, this->unk_ABD2, &sp5C, &this->unk_ABD4);
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_ABC8++;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F65F4.s")
#endif

void func_809F7400(Boss07* this, GlobalContext* globalCtx, s16 arg2) {
    this->actionFunc = func_809F748C;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_0603CBD0, -10.0f);
    if (arg2 != 0) {
        this->timers[0] = arg2;
    } else {
        this->timers[0] = Rand_ZeroFloat(30.0f);
    }
    this->actor.flags |= 1;
}

void func_809F748C(Boss07* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    if ((this->actor.xzDistToPlayer <= 200.0f) && (player->actor.world.pos.y < 10.0f)) {
        if (Rand_ZeroOne() < 0.3f) {
            this->actor.xzDistToPlayer = 250.0f;
        }
        func_809F7D2C(this, globalCtx);
    } else if (this->timers[0] == 0) {
        if (gGameInfo->data[1326] == 1) {
            func_809F8E68(this, globalCtx);
        } else if ((s8)this->actor.colChkInfo.health >= 28) {
            func_809F7D2C(this, globalCtx);
        } else if (((s8)this->actor.colChkInfo.health <= 12) && (Rand_ZeroOne() < 0.65f)) {
            func_809F8E68(this, globalCtx);
        } else if (Rand_ZeroOne() < 0.3f) {
            func_809F8658(this, globalCtx);
        } else {
            func_809F7D2C(this, globalCtx);
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    this->unk_174 = 1;
}

void func_809F7688(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F76D0;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06025878, -5.0f);
    this->unk_14C = 0;
}

void func_809F76D0(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    if (this->unk_14C == 1) {
        this->actor.velocity.y = 35.0f;
        this->actor.world.rot.y = Math_Acot2F(-this->actor.world.pos.z, -this->actor.world.pos.x) * (0x8000 / M_PI);
        this->actionFunc = func_809F77A8;
        this->actor.speedXZ = 20.0f;
    }
}

void func_809F77A8(Boss07* this, GlobalContext* globalCtx) {
    Audio_PlayActorSound2(&this->actor, 0x3014);
    if (this->unk_14C == 13) {
        func_8019F1C0(&D_80A09A40, 0x3A57);
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    if (this->actor.bgCheckFlags & 1) {
        func_809F7400(this, globalCtx, 1);
        this->unk_156 = 5;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x4000);
}

void func_809F783C(Boss07* this, GlobalContext* globalCtx) {
    f32 dx;
    f32 dz;
    s16 temp;
    Vec3f sp30;
    s32 pad;

    this->actionFunc = func_809F7968;
    this->actor.velocity.y = 25.0f;
    dx = 0.0f - this->actor.world.pos.x;
    dz = 0.0f - this->actor.world.pos.z;
    // temp2 = ;
    temp = this->actor.yawTowardsPlayer - (s16)(Math_Acot2F(dz, dx) * (0x8000 / M_PI));
    if (temp < 0) {
        dx = 200.0f;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603D224, -5.0f);
    } else {
        dx = -200.0f;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603D7F0, -5.0f);
    }
    Matrix_RotateY(this->actor.yawTowardsPlayer, 0);
    SysMatrix_GetStateTranslationAndScaledX(dx, &sp30);
    dx = sp30.x - this->actor.world.pos.x;
    dz = sp30.z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Acot2F(dz, dx) * (0x8000 / M_PI);
    this->unk_14C = 0;
    this->actor.speedXZ = 17.0f;
}

void func_809F7968(Boss07* this, GlobalContext* globalCtx) {
    Audio_PlayActorSound2(&this->actor, 0x3014);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    if ((this->unk_14C == 10) && (Rand_ZeroOne() < 0.5f)) {
        func_8019F1C0(&D_80A09A40, 0x3A57);
    }
    if ((this->actor.velocity.y < 0.0f) && (this->actor.bgCheckFlags & 1)) {
        if (Rand_ZeroOne() < 0.3f) {
            func_809F51E8(this, globalCtx, 1);
        } else {
            func_809F7400(this, globalCtx, 1);
            this->actor.speedXZ = 5.0f;
        }
        this->unk_156 = 5;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x4000);
}

void func_809F7AB4(Boss07* this, GlobalContext* globalCtx) {
    f32 phi_f12;
    f32 phi_f14;
    s32 pad;
    s16 sp22;

    this->actionFunc = func_809F7BC4;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_0603DD1C, -5.0f);
    phi_f14 = -this->actor.world.pos.x;
    phi_f12 = -this->actor.world.pos.z;
    sp22 = this->actor.yawTowardsPlayer - (s16)(Math_Acot2F(phi_f12, phi_f14) * (0x8000 / M_PI));
    Matrix_RotateY(this->actor.shape.rot.y, 0);
    if (sp22 < 0) {
        this->skelAnime1.animPlaybackSpeed = 1.0f;
        phi_f14 = 300.0f;
    } else {
        this->skelAnime1.animPlaybackSpeed = -1.0f;
        phi_f14 = -300.0f;
    }
    SysMatrix_GetStateTranslationAndScaledX(phi_f14, &this->unk_164);
    this->unk_164.x += this->actor.world.pos.x;
    this->unk_164.z += this->actor.world.pos.z;
    this->timers[1] = 21;
    this->unk_158 = 10;
    this->unk_170 = 0.0f;
    this->unk_ABCC = 0;
}

void func_809F7BC4(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    if (this->unk_14C == 20) {
        Audio_PlayActorSound2(this, 0x3A53);
    }
    this->unk_ABCC++;
    if ((this->unk_ABCC % 16) == 0) {
        func_8019F1C0(&D_80A09A40, 0x39E3);
    }
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    Math_ApproachF(&this->actor.world.pos.x, this->unk_164.x, 0.8f, this->unk_170);
    Math_ApproachF(&this->actor.world.pos.z, this->unk_164.z, 0.8f, this->unk_170);
    Math_ApproachF(&this->unk_170, 20.0f, 1.0f, 10.0f);
    if (this->timers[1] == 0) {
        if (Rand_ZeroOne() < 0.3f) {
            func_809F7AB4(this, globalCtx);
        } else {
            func_809F7400(this, globalCtx, 1);
        }
    }
}

void func_809F7D2C(Boss07* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->actionFunc = func_809F805C;
    this->timers[1] = 0;
    if (player->stateFlags3 & 0x100) {
        this->unk_14E = 4;
    } else if (this->actor.xzDistToPlayer <= 300.0f) {
        if (this->actor.xzDistToPlayer <= 200.0f) {
            this->unk_14E = 7;
        } else {
            this->unk_14E = 4;
        }
    } else {
        this->unk_14E = Rand_ZeroFloat(6.99f);
        if (((s8)this->actor.colChkInfo.health >= 28) && ((this->unk_14E == 1) || (this->unk_14E == 2))) {
            this->unk_14E = 0;
        }
    }
    switch (this->unk_14E) {
        case 0:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06033F80, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_06033F80);
            break;
        case 1:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06034E64, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_06034E64);
            break;
        case 2:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_060358C4, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_060358C4);
            break;
        case 3:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06036A7C, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_06036A7C);
            break;
        case 4:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603C4E0, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_0603C4E0);
            func_809F4D10(&this->unk_164, 650.0f);
            this->unk_170 = 0.0f;
            break;
        case 5:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06037ADC, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_06037ADC);
            break;
        case 6:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603918C, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_0603918C);
            break;
        case 7:
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06026204, -5.0f);
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_06026204);
            break;
    }
    this->unk_14C = 0;
}

void func_809F805C(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.79999995f;
    this->unk_FA0 = 0.79999995f;
    this->unk_790 = -5.0f;
    this->unk_F9C = -5.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    this->unk_798 = 1.0f;
    this->unk_FA4 = 1.0f;
    if (this->unk_14C >= 0x15) {
        this->unk_174 = 1;
    }
    switch (this->unk_14E) {
        case 0:
            if (this->unk_14C == (s16)(gGameInfo->data[1340] + 1)) {
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            if ((this->unk_14C >= 0xF) && (this->unk_14C < 0x12)) {
                this->unk_79C = 500.0f;
            }
            if (this->unk_14C == 9) {
                this->unk_14F = 0xB;
            }
            if (this->unk_14C == 1) {
                Audio_PlayActorSound2(this, 0x39CD);
            }
            if (this->unk_14C == 0xA) {
                Audio_PlayActorSound2(this, 0x39CA);
            }
            break;
        case 1:
            if (this->unk_14C == (s16)(gGameInfo->data[1339] + 3)) {
                func_8019F1C0(&D_80A09A40, 0x3A56);
            }
            if ((this->unk_14C >= 8) && (this->unk_14C < 0x38)) {
                this->unk_79C = 300.0f;
                this->unk_FA8 = 300.0f;
                if ((((this->unk_14C + 2) & 3) == 0) && (Rand_ZeroOne() < 0.5f)) {
                    play_sound(0x39CB);
                }
                if ((this->unk_14C & 3) == 0) {
                    Audio_PlayActorSound2(this, 0x39CA);
                }
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            }
            break;
        case 2:
            if (this->unk_14C == (s16)(gGameInfo->data[1332] + 5)) {
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            if ((this->unk_14C >= 0x20) && (this->unk_14C < 0x27)) {
                this->unk_79C = 300.0f;
                this->unk_FA8 = 300.0f;
            }
            if (this->unk_14C == 0x1C) {
                this->unk_14F = 0xB;
            }
            if (this->unk_14C == 0xA) {
                Audio_PlayActorSound2(this, 0x39CD);
            }
            if (this->unk_14C == 0x20) {
                Audio_PlayActorSound2(this, 0x39CA);
            }
            break;
        case 3:
            if (this->unk_14C == (s16)(gGameInfo->data[1332] + 5)) {
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            if ((this->unk_14C >= 0x1F) && (this->unk_14C < 0x24)) {
                this->unk_79C = 1200.0f;
            }
            if (this->unk_14C == 0x17) {
                this->unk_14F = 0xB;
            }
            Math_ApproachF(&this->unk_184, -0.1f, 0.5f, 0.1f);
            Math_ApproachF(&this->unk_188, 0.3f, 0.5f, 0.1f);
            if (this->unk_14C == 5) {
                Audio_PlayActorSound2(this, 0x39CD);
            }
            if (this->unk_14C == 0x1E) {
                Audio_PlayActorSound2(this, 0x39CA);
            }
            break;
        case 4:
            if ((this->unk_14C >= 0x11) && (this->unk_14C < 0x29)) {
                this->unk_79C = 200.0f;
                this->unk_FA8 = 200.0f;
                if ((this->unk_14C % 8) == 0) {
                    func_8019F1C0(&D_80A09A40, 0x3A54);
                }
                Audio_PlayActorSound2(this, 0x31CC);
                Math_ApproachF(&this->actor.world, this->unk_164.x, 0.1f, this->unk_170);
                Math_ApproachF(&this->actor.world.pos.z, this->unk_164.z, 0.1f, this->unk_170);
                Math_ApproachF(&this->unk_170, 20.0f, 1.0f, 4.0f);
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x2000);
                this->unk_174 = 0;
            }
            break;
        case 7:
            this->unk_174 = 0;
            if (this->unk_14C == 3) {
                Audio_PlayActorSound2(this, 0x3A53);
            }
            break;
        case 5:
            this->unk_FA0 = 0.7f;
            this->unk_794 = 0.7f;
            this->unk_790 = -15.0f;
            this->unk_F9C = -15.0f;
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            this->unk_174 = 1;
            break;
        case 6:
            if (this->unk_14C == (s16)(gGameInfo->data[1333] + 5)) {
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            if ((this->unk_14C >= 0xE) && (this->unk_14C < 0x13)) {
                this->unk_79C = 150.0f;
            }
            if ((this->unk_14C >= 0x17) && (this->unk_14C < 0x1D)) {
                this->unk_FA8 = 200.0f;
            }
            if ((this->unk_14C >= 0x2B) && (this->unk_14C < 0x31)) {
                this->unk_79C = 200.0f;
            }
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            if (this->unk_14C == 0x14) {
                Audio_PlayActorSound2(this, 0x39CD);
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            if (this->unk_14C == 5) {
                Audio_PlayActorSound2(this, 0x39CE);
            }
            if (this->unk_14C == 0x29) {
                Audio_PlayActorSound2(this, 0x39CA);
                func_8019F1C0(&D_80A09A40, 0x3A55);
            }
            break;
    }
    if (func_801378B8(&this->skelAnime1, this->unk_1D4) || (this->timers[1] == 1)) {
        func_809F7400(this, globalCtx, 0);
    }
}

void func_809F8658(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F86B8;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06026EA0, -5.0f);
    this->unk_1D4 = SkelAnime_GetFrameCount(&D_06026EA0);
    this->unk_14C = 0;
}

void func_809F86B8(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x800, 3, 0x2000);
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.79999995f;
    this->unk_FA0 = 0.79999995f;
    this->unk_798 = 1.0f;
    this->unk_FA4 = 1.0f;
    this->unk_790 = -5.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    this->unk_F9C = -15.0f;
    if ((this->unk_14C >= 0xE) && (this->unk_14C < 0x13)) {
        this->unk_79C = 500.0f;
    }
    if (this->unk_14C >= 0x12) {
        func_809F7400(this, globalCtx, Rand_ZeroFloat(20.0f) + 20.0f);
        play_sound(0x39ED);
    }
}

void func_809F87C8(Boss07* this, GlobalContext* globalCtx) {
    s32 sp2C;
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_809F4CBC(this, 2.0f);
    player->actor.world.pos = this->unk_F80;
    this->actor.flags &= ~1;
    this->unk_15A = 20;
    this->unk_F7C += 1;
    if (this->unk_14C > (s16)(0x2E - this->unk_F7E)) {
        func_8019F1C0(&D_80A09A40, 0x3A56);
        play_sound(0x39F1);
        this->actionFunc = func_809F8908;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06027270, -5.0f);
        this->unk_1D4 = SkelAnime_GetFrameCount(&D_06027270);
        this->unk_14C = 0;
    }
    if ((func_800B64FC(globalCtx, 1000.0f, &this->actor.world, &sp2C) >= 0.0f) && (sp2C == 1)) {
        func_809F8AB0(this, globalCtx);
    }
}

void func_809F8908(Boss07* this, GlobalContext* globalCtx) {
    Player* sp3C = PLAYER;
    f32 phi_f0;
    f32 phi_f2;
    s32 sp30;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_15A = 20;
    if (this->unk_14C == 6) {
        this->unk_F7E = 0;
        if (&this->actor == sp3C->actor.parent) {
            sp3C->unk_AE8 = 101;
            sp3C->actor.parent = NULL;
            sp3C->unk_394 = 0;
            if (sp3C->transformation == 3) {
                phi_f0 = 23.0f;
                phi_f2 = 20.0f;
            } else if (sp3C->transformation == 1) {
                phi_f0 = 15.0f;
                phi_f2 = 10.0f;
            } else if (sp3C->transformation == 0) {
                phi_f0 = 10.0f;
                phi_f2 = 3.0f;
            } else {
                phi_f0 = 20.0f;
                phi_f2 = 15.0f;
            }
            func_800B8D50(globalCtx, NULL, phi_f0, this->actor.yawTowardsPlayer + 0x9000, phi_f2, 0x10);
        }
    }
    if (this->unk_14C < 7) {
        sp3C->actor.world.pos = this->unk_F80;
        if ((func_800B64FC(globalCtx, 1000.0f, &this->actor.world, &sp30) >= 0.0f) && (sp30 == 1)) {
            func_809F8AB0(this, globalCtx);
        }
    }
    if (func_801378B8(&this->skelAnime1, this->unk_1D4) != 0) {
        func_809F7400(this, globalCtx, 0);
    }
}

void func_809F8AB0(Boss07* this, GlobalContext* globalCtx) {
    s32 temp_v0;
    s32 temp_v1;

    this->actionFunc = func_809F8B1C;

    temp_v0 = this->unk_F7E + 10;
    this->unk_780 = this->unk_784 = temp_v0;

    temp_v1 = D_80A09A50 - 1;
    if (temp_v1 < temp_v0) {
        this->unk_780 = this->unk_784 = temp_v1;
    }
    this->unk_14C = 0;
    play_sound(0x28E1);
}

void func_809F8B1C(Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_809F4CBC(this, 2.0f);
    player->actor.world.pos = this->unk_F80;
    this->actor.flags &= ~1;
    this->unk_15A = 20;
    if (this->unk_14C <= (s16)(46 - this->unk_F7E)) {
        this->unk_F7C++;
    }
    for (i = 0; i < 4; i++) {
        if (this->unk_784 != 0) {
            this->unk_784--;
        }
    }
    if (this->unk_784 == 0) {
        Math_ApproachF(&globalCtx->envCtx.unk_DC, 1.0f, 1.0f, 0.3f);
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        play_sound(0x309A);
    } else {
        this->unk_32C = 0.01f;
    }
    if (this->unk_32C > 4.0f) {
        this->actionFunc = func_809F8D04;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603B330, -10.0f);
        this->unk_1D4 = SkelAnime_GetFrameCount(&D_0603B330);
        this->unk_F7E = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->unk_394 = 0;
        }
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                    this->actor.focus.pos.y - 10.0f, this->actor.focus.pos.z, 0, 0, 0, 4);
        this->unk_14C = 0;
    }
}

void func_809F8D04(Boss07* this, GlobalContext* globalCtx) {
    s32 i;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_15A = 20;
    for (i = 0; i < 2; i++) {
        if (this->unk_780 != 0) {
            this->unk_780--;
        }
    }
    if (this->unk_14C < 70) {
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        Math_ApproachF(&this->unk_330, 2.5f, 0.5f, 2.0f);
        play_sound(0x309A);
        Math_ApproachF(&globalCtx->envCtx.unk_DC, 1.0f, 1.0f, 0.3f);
    }
    if (func_801378B8(&this->skelAnime1, this->unk_1D4)) {
        func_809F51E8(this, globalCtx, 1);
    }
}

void func_809F8DEC(Boss07* this, GlobalContext* globalCtx) {
    if (this->actionFunc != func_809F91D4) {
        this->actionFunc = func_809F91D4;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0603B330, -10.0f);
        this->unk_1D4 = SkelAnime_GetFrameCount(&D_0603B330);
    }
    this->unk_158 = 10;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE_OLD);
}

void func_809F8E68(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F8EC8;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_060269EC, -5.0f);
    this->unk_1D4 = SkelAnime_GetFrameCount(&D_060269EC);
    this->unk_14C = 0;
}

#ifdef NON_MATCHING
void func_809F8EC8(Boss07* this, GlobalContext* globalCtx) {
    this->unk_15A = 20;
    if (this->unk_14C < (s16)(gGameInfo->data[1288] + 14)) {
        this->unk_778 += 6;
        if (this->unk_778 > 44) {
            this->unk_778 = 44;
        }
    }
    if (this->unk_14C == 8) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, 180);
    }
    if (this->unk_14C == 10) {
        Audio_PlayActorSound2(this, 0x39CA);
    }
    if (this->unk_14C == (s16)(gGameInfo->data[1288] + 18)) {
        Audio_PlayActorSound2(this, 0x3A54);
    }
    if ((this->unk_14C < (s16)(gGameInfo->data[1288] + 14)) || ((s16)(gGameInfo->data[1289] + 17) < this->unk_14C)) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    }
    if ((this->unk_14C >= (s16)(gGameInfo->data[1288] + 14)) &&
        ((this->unk_14C <= (s16)(gGameInfo->data[1289] + 17)) ||
         ((s16)(gGameInfo->data[1290] + 21) <= this->unk_14C))) {
        this->unk_778 -= gGameInfo->data[1287] + 5;
        if (this->unk_778 < 0) {
            this->unk_778 = 0;
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, gGameInfo->data[1256] * 0x100 + this->actor.yawTowardsPlayer + 0xF00, 3,
                   0x2000);
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.79999995f;
    this->unk_FA0 = 0.79999995f;
    this->unk_798 = 1.0f;
    this->unk_FA4 = 1.0f;
    this->unk_790 = -5.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    this->unk_F9C = -15.0f;
    if (((s16)(gGameInfo->data[1291] + 12) <= this->unk_14C) && (this->unk_14C <= (s16)(gGameInfo->data[1292] + 17))) {
        this->unk_79C = gGameInfo->data[1254] + 500.0f;
    }
    if (this->unk_14C >= (s16)(gGameInfo->data[1293] + 36)) {
        func_809F7400(this, globalCtx, Rand_ZeroFloat(20.0f) + 20.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8EC8.s")
#endif

void func_809F91D4(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_8019F1C0(&D_80A09A40, 0x301B);
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    if (func_801378B8(&this->skelAnime1, this->unk_1D4)) {
        func_809F51E8(this, globalCtx, 1);
    }
}

void func_809F9280(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3) {
    if ((s8)this->actor.colChkInfo.health >= 0) {
        this->actor.colChkInfo.health -= arg2;
    }
    if ((s8)this->actor.colChkInfo.health <= 0) {
        if (gGameInfo->data[1267] != 0) {
            func_8019F1C0(&D_80A09A40, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        }
        this->unk_148 = 1;
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE2_OLD);
        if (this->actionFunc != func_809F93DC) {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0601DEB4, -10.0f);
            this->actionFunc = func_809F93DC;
            this->unk_1D4 = SkelAnime_GetFrameCount(&D_0601DEB4);
            this->unk_ABCC = 0;
        } else if (arg3 == 14) {
            if (this->skelAnime1.animCurrentFrame <= (this->unk_1D4 - 5.0f)) {
                this->unk_158 = 30;
            } else {
                SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_0601DEB4, -5.0f);
            }
        }
    }
}

void func_809F93DC(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    this->unk_ABCC++;
    if ((this->unk_ABCC % 16) == 0) {
        Audio_PlayActorSound2(&this->actor, 0x39E3);
    }
    func_809F4CBC(this, 2.0f);
    this->unk_794 = 0.7f;
    this->unk_FA0 = 0.7f;
    this->unk_790 = -15.0f;
    this->unk_F9C = -15.0f;
    this->unk_798 = 2.0f;
    this->unk_FA4 = 2.0f;
    this->unk_79C = 0.0f;
    this->unk_FA8 = 0.0f;
    if (func_801378B8(&this->skelAnime1, this->unk_1D4)) {
        func_809F51E8(this, globalCtx, 1);
    }
}

void func_809F94AC(Vec3f* arg0, f32 arg1, Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    s32 sp98 = -1;
    Player* player = PLAYER;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f sp7C;

    if ((arg1 >= 50.0f) && (this->unk_15A == 0)) {
        Actor* phi_s1 = globalCtx->actorCtx.actorList[6].first;

        while (phi_s1 != NULL) {
            if (phi_s1->id == ACTOR_OBJ_TSUBO) {
                for (i = 10; i < D_80A09A50; i += 3) {
                    dx = phi_s1->world.pos.x - arg0[i].x;
                    dy = phi_s1->world.pos.y + 10.0f - arg0[i].y;
                    dz = phi_s1->world.pos.z - arg0[i].z;

                    if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < (gGameInfo->data[1286] + 60.0f)) {
                        ((ObjTsubo*)phi_s1)->unk19B = 1;
                        func_809F4FF8(globalCtx, &phi_s1->world.pos, 10);
                    }
                }
            }
            phi_s1 = phi_s1->next;
        }
    }
    if ((arg1 >= 50.0f) && (this->unk_15A == 0) && (!(player->stateFlags3 & 0x100) || (this->unk_14E == 4))) {
        if ((func_800B64FC(globalCtx, 1000.0f, &this->actor.world.pos, &sp98) >= 0.0f) && (sp98 != 1)) {
            sp98 = -1;
        }
        for (i = 10; i < D_80A09A50; i += 3) {
            dx = player->actor.world.pos.x - arg0[i].x;
            dy = player->actor.world.pos.y + 30.0f - arg0[i].y;
            dz = player->actor.world.pos.z - arg0[i].z;

            dy *= 1.75f;

            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 140.0f) {
                if ((this->actionFunc == func_809F86B8) && (sp98 != 1) && !(player->stateFlags3 & 0x1000) &&
                    (520.0f <= this->actor.xzDistToPlayer) && (this->actor.xzDistToPlayer <= 900.0f)) {
                    if (globalCtx->grabPlayer(globalCtx, player)) {
                        f32 dx1;
                        f32 dy1;
                        f32 dz1;
                        f32 dxz1;

                        player->actor.parent = &this->actor;
                        func_801A5CFC(NA_SE_VO_LI_DAMAGE_S, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                      &D_801DB4B8);
                        this->unk_F7C = 0;
                        this->unk_F7E = ((this->actor.xzDistToPlayer - 300.0f) / 22.0f) + 10.0f;
                        dx1 = player->actor.world.pos.x - this->unk_7A0.x;
                        dy1 = player->actor.world.pos.y - this->unk_7A0.y + 50.0f;
                        dz1 = player->actor.world.pos.z - this->unk_7A0.z;
                        dxz1 = sqrtf(SQ(dx1) + SQ(dz1));
                        this->unk_F8C = Math_Acot2F(dz1, dx1);
                        this->unk_F90 = -Math_Acot2F(dxz1, dy1);
                        this->actionFunc = func_809F87C8;
                        this->unk_14C = 0;
                        this->unk_79C = 0.0f;
                        play_sound(NA_SE_EN_LAST3_GET_LINK_OLD);
                    }
                } else if ((player->stateFlags1 & 0x400000) && func_809F4C40(this, globalCtx)) {
                    player->unk_B80 = 10.0f;
                    player->unk_B84 = this->actor.yawTowardsPlayer;
                    play_sound(NA_SE_IT_SHIELD_BOUND);
                    this->unk_15A = 4;
                } else {
                    func_800B8D50(globalCtx, NULL, 5.0f, this->actor.shape.rot.y, 0.0f, 8);
                    this->unk_15A = 20;
                }
                sp7C = player->actor.world.pos;

                sp7C.x += randPlusMinusPoint5Scaled(30.0f);
                sp7C.y += randPlusMinusPoint5Scaled(30.0f) + 20.0f;
                sp7C.z += randPlusMinusPoint5Scaled(30.0f);
                EffectSsHitMark_SpawnFixedScale(globalCtx, 0, &sp7C);
                func_809F4FF8(globalCtx, &player->actor.world.pos, 7);
                return;
            }
        }
    }
}

void func_809F99C4(Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    s32 j;
    u8 pad;
    Player* player = PLAYER;

    if (this->unk_15C == 0) {
        if (this->sph2.elements[0].info.toucherFlags & 2) {
            this->sph2.elements[0].info.toucherFlags &= ~2;
            player->unk_B84 = this->actor.yawTowardsPlayer;
            player->unk_B80 = 20.0f;
            func_809F4FF8(globalCtx, &player->actor.world, 12);
            play_sound(0x1829);
        }
        for (i = 0; i < 11; i++) {
            if (this->sph1.elements[i].info.bumperFlags & 2) {
                for (j = 0; j < 11; j++) {
                    this->sph1.elements[j].info.bumperFlags &= ~2;
                }
                if (this->unk_1804 == 10) {
                    this->unk_1806 = 0;
                }
                switch (this->actor.colChkInfo.damageEffect) {
                    case 3:
                        this->unk_1805 = 10;
                        break;
                    case 2:
                        this->unk_1805 = 1;
                        break;
                    case 4:
                        this->unk_1805 = 20;
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                        break;
                    case 10:
                        this->unk_1805 = 40;
                        Audio_PlayActorSound2(&this->actor, 0x389E);
                        break;
                    case 9:
                        this->unk_1805 = 30;
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 3, 4);
                        break;
                }
                pad = this->actor.colChkInfo.damage;
                if ((this->actionFunc == func_809F91D4) || (this->actionFunc == func_809F93DC)) {
                    if ((this->actionFunc == func_809F91D4) && (this->actor.colChkInfo.damageEffect != 0xE) &&
                        (this->actor.colChkInfo.damageEffect != 0xD) && (this->actor.colChkInfo.damageEffect != 9) &&
                        (this->actor.colChkInfo.damageEffect != 0xC)) {
                        func_809F8DEC(this, globalCtx);
                        this->unk_15C = 6;
                    } else {
                        this->unk_15E = 15;
                        this->unk_15C = (this->actor.colChkInfo.damageEffect == 0xC) ? 15 : 5;
                        func_809F9280(this, globalCtx, pad, this->actor.colChkInfo.damageEffect);
                    }
                } else {
                    this->unk_15C = 15;
                    func_809F8DEC(this, globalCtx);
                    this->unk_F7E = 0;
                    if (&this->actor == player->actor.parent) {
                        player->unk_AE8 = 101;
                        player->actor.parent = NULL;
                        player->unk_394 = 0;
                    }
                }
                break;
            }
        }
    }
}

void func_809F9CEC(Boss07* this, GlobalContext* globalCtx) {
    Vec3f sp8C;
    Vec3f sp80;
    s32 i;

    Audio_PlaySoundAtPosition(globalCtx, this->unk_334, 0x1E, NA_SE_EV_ICE_BROKEN);
    for (i = 0; i < 30; i++) {
        sp80.x = randPlusMinusPoint5Scaled(7.0f);
        sp80.z = randPlusMinusPoint5Scaled(7.0f);
        sp80.y = Rand_ZeroFloat(6.0f) + 4.0f;

        sp8C.x = this->unk_334[i / 2].x + sp80.x;
        sp8C.y = this->unk_334[i / 2].y + sp80.y;
        sp8C.z = this->unk_334[i / 2].z + sp80.z;
        EffectSsEnIce_Spawn(globalCtx, &sp8C, Rand_ZeroFloat(1.0f) + 1.5f, &sp80, &D_80A07FD4, &D_80A07FCC, &D_80A07FD0,
                            30);
    }
}

void func_809F9E94(Boss07* this, GlobalContext* globalCtx) {
    DECR(this->unk_1806);

    switch (this->unk_1805) {
        case 0:
            this->unk_1804 = 0;
            this->unk_1806 = 0;
            this->unk_1800 = 0.0f;
            break;
        case 1:
            this->unk_1804 = 0;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
            func_800BCB70(&this->actor, 0x4000, 120, 0, 60);
        case 2:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_1800, 1.0f, 0.02f);
                if (this->unk_1800 == 0.0f) {
                    this->unk_1805 = 0;
                }
            } else {
                Math_ApproachF(&this->unk_17F8, 1.0f, 0.1f, 0.5f);
            }
            break;
        case 10:
            this->unk_1804 = 11;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17FC = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
        case 11:
            if (this->unk_1806 == 0) {
                func_809F9CEC(this, globalCtx);
                this->unk_1805 = 0;
            } else {
                if (this->unk_1806 == 50) {
                    this->unk_1804 = 10;
                }
                Math_ApproachF(&this->unk_17F8, 1.0f, 1.0f, 0.08f);
                Math_ApproachF(&this->unk_17FC, 1.0f, 0.05f, 0.05f);
            }
            break;
        case 20:
            this->unk_1804 = 20;
            this->unk_1806 = 40;
            this->unk_17F8 = 1.0f;
            goto test_label;
        case 30:
            this->unk_1804 = 21;
            this->unk_1806 = 40;
            this->unk_17F8 = 3.0f;
        test_label:
            this->unk_1800 = 1.0f;
            this->unk_1805 = 21;
        case 21:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_17F8, 1.0f, 0.03f);
                if (this->unk_17F8 == 0.0f) {
                    this->unk_1805 = 0;
                    this->unk_1800 = 0.0f;
                }
            } else {
                Math_ApproachF(&this->unk_17F8, 1.5f, 0.5f, 0.5f);
            }
            break;
        case 40:
            this->unk_1804 = 30;
            this->unk_1806 = 50;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = (gGameInfo->data[1266] * 0.1f) + 1.0f;
            this->unk_1805++;
        case 41:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_17F8, 1.0f, 0.05f);
                if (this->unk_17F8 == 0.0f) {
                    this->unk_1805 = 0;
                    this->unk_1800 = 0.0f;
                }
            }
            break;
    }
}

void Boss07_Wrath_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;
    Player* sp78 = PLAYER;

    globalCtx->envCtx.unk_C1 = 2;
    globalCtx->envCtx.unk_C2 = 0;
    this->actor.hintId = 52;
    Math_ApproachF(&globalCtx->envCtx.unk_DC, 0.0f, 1.0f, 0.03f);
    this->unk_149 = 1;
    Math_Vec3f_Copy(&D_80A09A40, &this->actor.projectedPos);
    if (gGameInfo->data[1311] == 0) {
        this->unk_174 = 0;
        this->unk_14C += 1;
        Actor_SetScale(&this->actor, 0.015f);
        Math_ApproachZeroF(&this->unk_184, 1.0f, 0.02f);
        Math_ApproachZeroF(&this->unk_188, 1.0f, 0.02f);
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        DECR(this->unk_15A);
        DECR(this->unk_158);
        DECR(this->unk_15C);
        DECR(this->unk_15E);
        DECR(this->unk_156);

        Math_ApproachZeroF(&this->unk_32C, 1.0f, 0.2f);
        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, globalCtx);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 100.0f, 100.0f, 5);
        if (this->unk_14F != 0) {
            this->unk_14F--;
            if ((this->actionFunc == func_809F805C) && (this->unk_14F == 0)) {
                play_sound(NA_SE_EN_LAST3_ROD_FLOOR_OLD);
            }
        }
    } else {
        D_80A09A50 = 45;
    }
    func_809F94AC(this->unk_7AC, this->unk_79C, this, globalCtx);
    func_809F94AC(this->unk_FB8, this->unk_FA8, this, globalCtx);
    if (this->unk_158 != 0) {
        for (i = 0; i < 11; i++) {
            this->sph1.elements[i].info.bumperFlags &= ~2;
        }
    }
    func_809F99C4(this, globalCtx);
    if (this->unk_15C != 0) {
        this->unk_778 = 0;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->sph1.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->sph1.base);
    if ((this->actionFunc == func_809F805C) && (this->unk_14E == 7) && (this->unk_14C >= 6)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->sph2.base);
    } else {
        if ((this->unk_174 != 0) && func_809F4C40(this, globalCtx)) {
            if ((sp78->unk_D57 == 4) && (sp78->itemActionParam != 0xC)) {
                if ((this->actor.xzDistToPlayer >= 400.0f) && (Rand_ZeroOne() < 0.5f)) {
                    func_809F7AB4(this, globalCtx);
                } else {
                    func_809F51E8(this, globalCtx, 0);
                }
            }
            if ((sp78->unk_ADC != 0) && (this->actor.xzDistToPlayer <= 150.0f)) {
                func_809F51E8(this, globalCtx, 0);
            }
        }
        if ((this->actionFunc != func_809F91D4) && (this->actionFunc != func_809F93DC)) {
            if ((sp78->stateFlags3 & 0x00001000) && !(sp78->stateFlags3 & 0x00080000) &&
                (this->actor.xzDistToPlayer <= 250.0f)) {
                func_809F51E8(this, globalCtx, 0);
            }
        }
    }
    if (this->unk_174 != 0) {
        func_809F52CC(this, globalCtx);
    }
    func_809F5494(this, globalCtx);
    if ((gGameInfo->data[1336] != 0) || (this->unk_148 != 0)) {
        gGameInfo->data[1336] = 0;
        this->unk_148 = 0;
        func_809F64F4(this, globalCtx);
    }
    if (this->unk_1D8 != 0) {
        u16* sp74 = SEGMENTED_TO_VIRTUAL(D_06040930);
        u16* sp70 = SEGMENTED_TO_VIRTUAL(D_0603ED30);
        u16* sp6C = SEGMENTED_TO_VIRTUAL(D_06040130);
        u16* sp68 = SEGMENTED_TO_VIRTUAL(D_06041B30);
        u16* sp64 = SEGMENTED_TO_VIRTUAL(D_0603F130);
        u16* sp60 = SEGMENTED_TO_VIRTUAL(D_06042330);
        u16* sp5C = SEGMENTED_TO_VIRTUAL(D_06040B30);
        u16* sp58 = SEGMENTED_TO_VIRTUAL(D_06043330);
        u16* sp54 = SEGMENTED_TO_VIRTUAL(D_0603DD30);

        for (i = 0; i < this->unk_1D8; i++) {
            s32 sp50;
            s32 sp4C;
            s32 sp48;
            s32 sp44;

            sp44 = Rand_ZeroFloat(255.99f);
            sp4C = Rand_ZeroFloat(511.99f);
            sp48 = Rand_ZeroFloat(1023.99f);
            sp50 = Rand_ZeroFloat(2047.99f);

            sp74[sp44] = sp70[sp4C] = sp6C[sp48] = sp68[sp48] = sp64[sp50] = sp60[sp50] = sp5C[sp50] = sp58[sp50] =
                sp54[sp50] = 0;
        }
    }
    func_809F9E94(this, globalCtx);
    if ((this->unk_156 == 1) || (this->unk_156 == 4)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
    }
    if (sp78->actor.world.pos.y > 100.0f) {
        if (sp78->actor.world.pos.z < gGameInfo->data[1330] + -850.0f) {
            sp78->actor.world.pos.z = gGameInfo->data[1330] + -850.0f;
        }
    }
    if (sp78->actor.world.pos.y < -300.0f) {
        sp78->actor.world.pos.x = sp78->actor.world.pos.y = sp78->actor.world.pos.z = 0.0f;
    }
}

#ifdef NON_MATCHING
void func_809FAA44(Boss07 *this, GlobalContext *globalCtx, Vec3f *arg2, Vec3f *arg3, Vec3f *arg4, Vec3f *arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, Vec3s *argA, s16 argB, f32 argC, s32 argD) {
    s32 i;
    s32 phi_s6;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f22;
    f32 phi_f0;
    Vec3f* temp;
    s32 pad;
    Vec3f spB8 = D_80A07FE0;
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;

    spB8.z = 22.0f * argC;
    temp = arg5;
    for(i = 0; i < (s16)D_80A09A50; i++, temp++) {
        if(i == 0) {
            arg3[0] = *arg2;
        } else {
            Math_ApproachF(&temp->x, 0.0f, 1.0f, arg8);
            Math_ApproachF(&temp->y, 0.0f, 1.0f, arg8);
            Math_ApproachF(&temp->z, 0.0f, 1.0f, arg8);
        }
    }
    spAC.z = 20.0f;
    Matrix_RotateY(argA->y, 0);
    SysMatrix_InsertXRotation_s(argA->x, 1);
    SysMatrix_InsertZRotation_s(argA->z, 1);
    Matrix_RotateY(0x4000, 1);
    SysMatrix_GetStateTranslationAndScaledZ(spAC.z, &sp94);
    if (argB != 0) {
        spAC.z = 200.0f;
        SysMatrix_InsertYRotation_f(this->unk_F8C, 0);
        SysMatrix_RotateStateAroundXAxis(this->unk_F90);
    } else {
        spAC.z = arg9;
    }
    SysMatrix_GetStateTranslationAndScaledZ(spAC.z, &sp7C);

    for(i = 1, phi_s6 = 0; i < (s16)D_80A09A50; i++) {
        if(i < 6) {
            sp88.x = (6 - i) * sp94.x * 0.2f;
            sp88.y = (6 - i) * sp94.y * 0.2f;
            sp88.z = (6 - i) * sp94.z * 0.2f; 
        } else if (argB != 0) {
            if(argB <= i && i < (s16)(argB + this->unk_F7C)) {
                sp88.y = 0.0f;
                sp88.x = __sinf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (phi_s6 * 1.4f)) * 100.0f;
                sp88.z = __cosf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (phi_s6 * 1.4f)) * 100.0f;
                sp7C = D_801D15B0;
                phi_s6++;
            }
        } else {
            sp88 = D_801D15B0;
        }
        temp_f24 = (arg3 + i)->x + (arg5 + i)->x - (arg3 + i - 1)->x + sp88.x + sp7C.x;
        phi_f0 = (arg3 + i)->y + (arg5 + i)->y + arg6 + sp88.y + sp7C.y;
        phi_f0 = CLAMP_MIN(phi_f0, 2.0f);
        temp_f26 = phi_f0 - (arg3 + i - 1)->y;
        temp_f20 = (arg3 + i)->z + (arg5 + i)->z - (arg3 + i - 1)->z + sp88.z + sp7C.z;
        temp_f22 = Math_Acot2F(temp_f20, temp_f24);
        temp_f20 = -Math_Acot2F(sqrtf(SQ(temp_f24) + SQ(temp_f20)), temp_f26);
        (arg4 + i - 1)->y = temp_f22;
        (arg4 + i - 1)->x = temp_f20;
        SysMatrix_InsertYRotation_f(temp_f22, 0);
        SysMatrix_RotateStateAroundXAxis(temp_f20);
        SysMatrix_GetStateTranslationAndScaledZ(spB8.z, &spA0);
        temp_f24 = (arg3 + i)->x;
        temp_f26 = (arg3 + i)->y;
        temp_f20 = (arg3 + i)->z;
        (arg3 + i)->x = (arg3 + i - 1)->x + spA0.x;
        (arg3 + i)->y = (arg3 + i - 1)->y + spA0.y;
        (arg3 + i)->z = (arg3 + i - 1)->z + spA0.y;
        if((i != 0) && (i == argB)) {
            spAC.x = 15.0f;
            spAC.y = -30.0f;
            spAC.z = -12.0f;
            SysMatrix_MultiplyVector3fByState(&spAC, &spA0);
            this->unk_F80.x = (arg3 + i)->x + spA0.x;
            this->unk_F80.y = (arg3 + i)->y + spA0.y;
            this->unk_F80.z = (arg3 + i)->z + spA0.z;
        } else if ((argD == 0) && (this->actionFunc == func_809F8EC8)) {
            if (i == gGameInfo->data[1338] + D_80A09A50 - this->unk_778 + 1) {
                spAC.x = gGameInfo->data[1308];
                spAC.y = gGameInfo->data[1309];
                spAC.z = gGameInfo->data[1310];
                SysMatrix_MultiplyVector3fByState(&spAC, &spA0);
                this->unk_F80.x = (arg3 + i)->x + spA0.x;
                this->unk_F80.y = (arg3 + i)->y + spA0.y;
                this->unk_F80.z = (arg3 + i)->z + spA0.z;
            }
        }
        (arg5 + i)->x = ((arg3 + i)->x - temp_f24) * arg7;
        (arg5 + i)->y = ((arg3 + i)->y - temp_f26) * arg7;
        (arg5 + i)->z = ((arg3 + i)->z - temp_f20) * arg7;
        if((arg5 + i)->x > 200.0f) {
            (arg5 + i)->x = 200.0f;
        }
        if((arg5 + i)->x < -200.0f) {
            (arg5 + i)->x = -200.0f;
        }
        if((arg5 + i)->y > 200.0f) {
            (arg5 + i)->y = 200.0f;
        }
        if((arg5 + i)->y < -200.0f) {
            (arg5 + i)->y = -200.0f;
        }
        if((arg5 + i)->z > 200.0f) {
            (arg5 + i)->z = 200.0f;
        }
        if((arg5 + i)->z < -200.0f) {
            (arg5 + i)->z = -200.0f;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FAA44.s")
#endif

#ifdef NON_MATCHING
void func_809FB114(Boss07 *this, GlobalContext *globalCtx, Vec3f *arg2, Vec3f *arg3, f32 arg4, s32 arg5) {
    s32 phi_s6;
    s32 phi_s1;
    f32 phi_f12;
    f32 one = 1.0f;
    f32 two = 2.0f;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, D_0602EEC8);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, gGameInfo->data[1584] + 45, 35, 75, 255);
    phi_s6 = (arg5 == 0) ? this->unk_778 : 0;
    for(phi_s1 = 0; phi_s1 <= (D_80A09A50 - phi_s6) - 1; phi_s1++) {
        SysMatrix_InsertTranslation(arg2[phi_s1].x, 0.0f, arg2[phi_s1].z, 0);
        Matrix_Scale(1.0f, 0.0f, 1.0f, 1);
        SysMatrix_InsertYRotation_f(arg3[phi_s1].y, 1);
        SysMatrix_RotateStateAroundXAxis(arg3[phi_s1].x);
        phi_f12 = (phi_s1 > 24) ? 0.025f : ((24 - phi_s1) * one * 0.001f) + 0.025f;
        Matrix_Scale(phi_f12, phi_f12, ((two * arg4) + 0.5f) * 0.01f, 1);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
        gSPDisplayList(POLY_OPA_DISP++, D_0602EEF8);
    }
    gSPDisplayList(POLY_OPA_DISP++, D_0602EE50);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);
    for(phi_s1 = 0; phi_s1 < (D_80A09A50 - phi_s6) - 1; phi_s1++) {
        SysMatrix_InsertTranslation(arg2[phi_s1].x, arg2[phi_s1].y, arg2[phi_s1].z, 0);
        SysMatrix_InsertYRotation_f(arg3[phi_s1].y, 1);
        SysMatrix_RotateStateAroundXAxis(arg3[phi_s1].x);
        phi_f12 = (phi_s1 > 24) ? 0.025f : ((24 - phi_s1) * one * 0.001f) + 0.025f;
        Matrix_Scale(phi_f12, phi_f12, ((two * arg4) + 0.5f) * 0.01f, 1);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
        gSPDisplayList(POLY_OPA_DISP++, D_0602EEF8);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB114.s")
#endif

s32 func_809FB504(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    Boss07* this = THIS;

    if (limbIndex == 26) {
        rot->x += this->unk_17DA;
        rot->y += this->unk_17D8;
        rot->z += this->unk_17DC;
    }
    return false;
}

void func_809FB55C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    Boss07* this = THIS;
    s8 sp6B;
    Vec3f sp5C;
    MtxF sp1C;

    sp6B = D_80A08090[limbIndex];
    if (sp6B >= 0) {
        SysMatrix_GetStateTranslation(&this->unk_334[sp6B]);
    }
    sp6B = D_80A07FEC[limbIndex];
    if (sp6B >= 0) {
        if (this->unk_158 != 0) {
            SysMatrix_GetStateTranslationAndScaledZ(100000.0f, &sp5C);
        } else {
            SysMatrix_MultiplyVector3fByState(&D_80A0800C[sp6B], &sp5C);
        }
        func_809F4BB0(sp6B, &this->sph1, &sp5C);
    }
    if (limbIndex == 26) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
    if (limbIndex == 19) {
        SysMatrix_MultiplyVector3fByState(&D_80A080B0, &this->unk_7A0);
    }
    if (limbIndex == 17) {
        SysMatrix_CopyCurrentState(&sp1C);
        func_8018219C(&sp1C, &this->unk_788, 0);
    }
    if (limbIndex == 24) {
        SysMatrix_MultiplyVector3fByState(&D_80A080B0, &this->unk_FAC);
    }
    if (limbIndex == 22) {
        SysMatrix_CopyCurrentState(&sp1C);
        func_8018219C(&sp1C, &this->unk_F94, 0);
    }
    if (limbIndex == 12) {
        SysMatrix_GetStateTranslation(&sp5C);
        func_809F4BB0(0, &this->sph2, &sp5C);
    }
}

void func_809FB728(GlobalContext *globalCtx, s32 limbIndex, Actor *thisx) {
    Boss07* this = THIS;

    if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 7) || (limbIndex == 9) || (limbIndex == 0xB) || (limbIndex == 0xC) || (limbIndex == 0x10) || (limbIndex == 0x12) || (limbIndex == 0x13) || (limbIndex == 0x15) || (limbIndex == 0x17) || (limbIndex == 0x18) || (limbIndex == 0x1A)) {
        Matrix_Scale(1.0f, this->unk_17E0, this->unk_17E0, 1);
    }
}

#ifdef NON_MATCHING
void func_809FB7D4(Boss07 *this, GlobalContext *globalCtx) {
    s32 i;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    if ((this->unk_32C > 0.0f) || (this->unk_330 > 0.0f)) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);

        if (this->unk_32C > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, D_04023348);
            for(i = 0; i < 15; i++) {
                SysMatrix_InsertTranslation(this->unk_334[i].x, this->unk_334[i].y, this->unk_334[i].z, 0);
                SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
                Matrix_Scale(this->unk_32C, this->unk_32C, this->unk_32C, 1);
                SysMatrix_InsertZRotation_f(Rand_ZeroFloat(2.0f * M_PI), 1);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), 2);
                gSPDisplayList(POLY_XLU_DISP++, D_04023428);
            }
            for(i = this->unk_780; i >= this->unk_784; i--) {
                SysMatrix_InsertTranslation(this->unk_7AC[i].x, this->unk_7AC[i].y, this->unk_7AC[i].z, 0);
                SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
                Matrix_Scale(1.5f, 1.5f, 1.5f, 1);
                SysMatrix_InsertZRotation_f(Rand_ZeroFloat(2.0f * M_PI), 1);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), 2);
                gSPDisplayList(POLY_XLU_DISP++, D_04023428);
            }
        }
        if (this->unk_330 > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, D_040233B8);
            for(i = 0; i < 30; i++) {
                SysMatrix_InsertTranslation(this->unk_334[i / 2].x + randPlusMinusPoint5Scaled(30.0f), this->unk_334[i / 2].y + randPlusMinusPoint5Scaled(30.0f), this->unk_334[i / 2].z + randPlusMinusPoint5Scaled(30.0f), 0);
                Matrix_Scale(this->unk_330, this->unk_330, this->unk_330, 1);
                SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(2.0f * M_PI));
                SysMatrix_InsertZRotation_f(Rand_ZeroFloat(2.0f * M_PI), 1);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), 2);
                gSPDisplayList(POLY_XLU_DISP++, D_04023428);
            }
        }
    }
    CLOSE_DISPS(gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB7D4.s")
#endif

#ifdef NON_MATCHING
void func_809FBB9C(Boss07 *this, GlobalContext *globalCtx, Vec3f *arg2) {
    s32 i;
    f32 temp_f12_2;
    f32 temp_f20;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    
    
    if (this->unk_AB4C > 0.0f) {
        func_809F49A0(1, 0x71B8, 0x263A);
        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
        gDPSetCombineMode(POLY_XLU_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        for(i = 0; i < 30; i++) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, D_80A07950[0][0], D_80A07950[0][1], D_80A07950[0][2], 40);
            temp_f20 = (func_809F49C0() * 40.0f) - 30.0f;
            SysMatrix_InsertTranslation(this->unk_334[2].x, this->unk_334[2].y - 30.0f + 50.0f + temp_f20 + 25.0f, this->unk_334[2].z, 0);
            SysMatrix_InsertTranslation(arg2->x, arg2->y + temp_f20, arg2->z, 0);
            SysMatrix_InsertYRotation_f(func_809F49C0() * M_PI * 2.0f, 1);
            SysMatrix_RotateStateAroundXAxis(-0.024999999f * temp_f20);
            SysMatrix_InsertZRotation_f(func_809F49C0() * M_PI * 2.0f, 1);
            if (this->unk_AB50[i] > 0.0f) {
                Matrix_Scale(this->unk_AB50[i], 1.0f, 12.0f, 1);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
                gSPDisplayList(POLY_XLU_DISP++, D_0602EFE8);
            }
        }
        func_8012C2DC(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_XLU_DISP++, D_04023348);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, gGameInfo->data[1554] + 220, gGameInfo->data[1552] + 170);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, gGameInfo->data[1558] + 100, 128);

        SysMatrix_InsertTranslation(this->unk_334[2].x, this->unk_334[2].y, this->unk_334[2].z, 0);
        SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
        SysMatrix_InsertZRotation_s(globalCtx->gameplayFrames * 0x80, 1);
        temp_f12_2 = (gGameInfo->data[1553] + 800) * 0.01f * this->unk_AB4C;
        Matrix_Scale(temp_f12_2, temp_f12_2, 1.0f, 1);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
        gSPDisplayList(POLY_XLU_DISP++, D_04023428);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBB9C.s")
#endif

#ifdef NON_MATCHING
void func_809FBF94(Boss07* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    f32 sp54;
    f32 sp50;
    Player* sp4C = PLAYER;
    // GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (this->unk_AB44 > 0.0f) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)(gGameInfo->data[1588] + 255));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);
        gSPDisplayList(POLY_XLU_DISP++, D_04023348);

        if (sp4C->transformation == 1) {
            sp54 = -10.0f;
            sp50 = -20.0f;
        } else {
            sp54 = sp50 = 0.0f;
        }
        if (sp4C->transformation == 0) {
            sp54 -= 43.0f;
        }

        SysMatrix_InsertTranslation(sp4C->actor.world.pos.x,
                                    sp4C->actor.world.pos.y + func_800B6FC8(sp4C) - 20.0f + sp54 +
                                        gGameInfo->data[1596],
                                    sp4C->actor.world.pos.z + gGameInfo->data[1597] - 15.0f + sp50, 0);
        SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);

        Matrix_Scale(this->unk_AB44, this->unk_AB44, this->unk_AB44, 1);
        SysMatrix_InsertZRotation_s(globalCtx->gameplayFrames * 0x40, 1);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
        gSPDisplayList(POLY_XLU_DISP++, D_04023428);
    }
    CLOSE_DISPS(gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBF94.s")
#endif

void Boss07_Wrath_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    u8* sp54 = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(u8[0x40][0x40]));

    OPEN_DISPS(globalCtx->state.gfxCtx);
    Vec3f sp58;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SysMatrix_InsertYRotation_f(this->unk_184, 1);
    SysMatrix_RotateStateAroundXAxis(this->unk_188);
    func_801343C0(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, (s32)this->skelAnime1.dListCount,
                  func_809FB504, func_809FB55C, func_809FB728, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    if (((gGameInfo->data[1311] == 0) || (gGameInfo->data[1311] == 2)) && (this->unk_149 != 0)) {
        func_809FAA44(this, globalCtx, &this->unk_7A0, this->unk_7AC, this->unk_A04, this->unk_C5C, this->unk_790,
                      this->unk_794, this->unk_798, this->unk_79C, &this->unk_788, this->unk_F7E, this->unk_77C, 0);
        func_809FAA44(this, globalCtx, &this->unk_FAC, this->unk_FB8, this->unk_1210, this->unk_1468, this->unk_F9C,
                      this->unk_FA0, this->unk_FA4, this->unk_FA8, &this->unk_F94, 0, this->unk_77C, 1);
    }
    func_809FB114(this, globalCtx, this->unk_7AC, this->unk_A04, this->unk_77C, 0);
    func_809FB114(this, globalCtx, this->unk_FB8, this->unk_1210, this->unk_77C, 1);
    if (this->unk_AB48 == 0) {
        func_809FC8B0(sp54, this, globalCtx);
        func_809FC960(sp54, this, globalCtx);
    }
    func_809FB7D4(this, globalCtx);
    sp58.x = this->unk_334[2].x;
    sp58.y = this->unk_334[2].y - 30.0f + 50.0f;
    sp58.z = this->unk_334[2].z;
    func_809FBB9C(this, globalCtx, &sp58);
    func_800BE680(globalCtx, &this->actor, this->unk_334, 0xF, this->unk_17F8, this->unk_17FC, this->unk_1800,
                  this->unk_1804);
    this->unk_149 = 0;
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_809FC4C0(Boss07* this, u8* shadowTexture, f32 arg2) {
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_v0;
    s32 phi_a0;
    s32 phi_a3;
    s32 j = 0;
    s32 i;
    Vec3f lerp;
    Vec3f sp74;
    Vec3f sp68;

    for (i = 0; i < 15; i++) {
        if ((arg2 == 0.0f) || ((j = D_80A08140[i]) >= 0)) {
            if (arg2 > 0.0f) {
                VEC3F_LERPIMPDST(&lerp, &this->unk_334[i], &this->unk_334[j], arg2);

                sp74.x = lerp.x - this->actor.world.pos.x;
                sp74.y = lerp.y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 100.0f;
                sp74.z = lerp.z - this->actor.world.pos.z;
            } else {
                sp74.x = this->unk_334[i].x - this->actor.world.pos.x;
                sp74.y = this->unk_334[i].y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 100.0f;
                sp74.z = this->unk_334[i].z - this->actor.world.pos.z;
            }
            SysMatrix_MultiplyVector3fByState(&sp74, &sp68);

            sp68.x *= 0.2f;
            sp68.y *= 0.2f;
            temp_t0 = (u16)(s32)(sp68.x + 32.0f);
            temp_t1 = (u16)((s32)sp68.y << 6);

            if (D_80A0817C[i] == 2) {
                for (j = 0, phi_a3 = -0x180; j < 12; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -D_80A08110[j]; phi_a0 < D_80A08110[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTexture[temp_v0] = 255;
                        }
                    }
                }
            } else if (D_80A0817C[i] == 1) {
                for (j = 0, phi_a3 = -0x100; j < 8; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -D_80A080F0[j]; phi_a0 < D_80A080F0[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTexture[temp_v0] = 255;
                        }
                    }
                }
            } else if (D_80A0817C[i] == 0) {
                for (j = 0, phi_a3 = -0xC0; j < 7; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -D_80A080D4[j]; phi_a0 < D_80A080D4[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTexture[temp_v0] = 255;
                        }
                    }
                }
            } else {
                for (j = 0, phi_a3 = -0x80; j < 6; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -D_80A080BC[j]; phi_a0 < D_80A080BC[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTexture[temp_v0] = 255;
                        }
                    }
                }
            }
        }
    }
}

void func_809FC8B0(u8* arg0, Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    s32* temp = (s32*)arg0;

    for (i = 0; i < 0x400; i++, temp++) {
        *temp = 0;
    }
    SysMatrix_SetStateXRotation(1.0f);
    for (i = 0; i < 6; i++) {
        func_809FC4C0(this, arg0, i / 5.0f);
    }
}

#ifdef NON_MATCHING
void func_809FC960(u8* arg0, Boss07* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    GraphicsContext* pad3 = globalCtx->state.gfxCtx;

    OPEN_DISPS(pad3);
    f32 phi_f0;

    func_8012C28C(globalCtx->state.gfxCtx);
    phi_f0 = (400.0f - this->actor.world.pos.y) * 0.0025f;
    phi_f0 = CLAMP_MIN(phi_f0, 0.0f);
    phi_f0 = CLAMP_MAX(phi_f0, 1.0f);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(s32)(phi_f0 * 80.0f) & 0xFF);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z - 20.0f, 0);
    Matrix_Scale(1.75f, 1.0f, 1.75f, 1);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
    gSPDisplayList(POLY_OPA_DISP++, D_0602EF68);
    gDPLoadTextureBlock(POLY_OPA_DISP++, arg0, G_IM_FMT_I, G_IM_SIZ_8b, 0x40, 0x40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(POLY_OPA_DISP++, D_0602EF88);
    CLOSE_DISPS(pad3);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC960.s")
#endif

void func_809FCBC8(Boss07* this) {
    s32 phi_v0 = (Rand_ZeroOne() < 0.5f) ? 0x4000 : -0x4000;

    Matrix_RotateY(this->actor.yawTowardsPlayer + phi_v0, MTXMODE_NEW);
    SysMatrix_GetStateTranslationAndScaledZ(200.0f, &this->unk_164);
    this->timers[1] = 30;
    this->unk_164.x += this->actor.world.pos.x;
    this->unk_164.z += this->actor.world.pos.z;
    this->unk_170 = 20000.0f;
}

void func_809FCC70(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809FCCCC;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_06002D84, 0.0f);
    this->actor.flags &= ~1;
    this->unk_17D8 = 0x6E00;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCCCC.s")

void func_809FD5F8(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809FD710;
    this->unk_14E = Rand_ZeroFloat(2.999f);
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, D_80A0818C[this->unk_14E], -10.0f);
    this->actor.flags |= 1;
    this->timers[0] = Rand_ZeroFloat(50.0f) + 50.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD710.s")

void func_809FD818(Boss07* this, GlobalContext* globalCtx, s16 arg2) {
    if (this->actionFunc != func_809FD89C) {
        this->actionFunc = func_809FD89C;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06009C7C, -10.0f);
        this->unk_1D4 = SkelAnime_GetFrameCount(&D_06009C7C);
    }
    this->unk_158 = 10;
    this->timers[0] = arg2;
    this->timers[1] = 12;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD89C.s")

void func_809FD984(Boss07* this, GlobalContext* globalCtx, u8 arg2, u8 arg3) {
    if (this->actionFunc != func_809FDAB0) {
        this->actionFunc = func_809FDAB0;
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06000D0C, -2.0f);
        this->unk_1D4 = SkelAnime_GetFrameCount(&D_06000D0C);
    } else if (arg3 == 14) {
        if (this->skelAnime1.animCurrentFrame <= (this->unk_1D4 - 5.0f)) {
            this->unk_158 = 30;
            this->unk_15C = 30;
        } else {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, (AnimationHeader*)&D_06000D0C, -2.0f);
        }
    }

    if (this->actor.colChkInfo.health != 0) {
        this->actor.colChkInfo.health -= arg2;
        if ((s8)this->actor.colChkInfo.health <= 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_DEAD_OLD);
            this->unk_148 = 1;
            this->unk_15C = 100;
            this->unk_158 = 100;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            return;
        }
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_DAMAGE2_OLD);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDAB0.s")

void func_809FDB2C(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_0600A400, -2.0f);
    this->actionFunc = func_809FDBA0;
    this->timers[0] = Rand_ZeroFloat(100.0f) + 150.0f;
    func_809FCBC8(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE524.s")

void func_809FE6B0(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809FE734;
    func_809F4FAC(globalCtx);
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime1, &D_06000D0C, -2.0f);
    this->unk_1D4 = SkelAnime_GetFrameCount(&D_06000D0C);
    this->unk_ABD0 = 0;
    this->unk_ABC8 = 0;
    this->actor.flags &= ~1;
    this->unk_15C = 20;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FEE70.s")

void Boss07_Afterimage_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    if (DECR(this->timers[0]) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

#ifdef NON_MATCHING
void Boss07_Incarnation_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;
    s32 pad;

    this->actor.hintId = 51;
    this->unk_14C++;
    Math_Vec3f_Copy(&D_80A09A40, &this->actor.projectedPos);
    if (this->unk_14A == 1) {
        Math_ApproachF(&globalCtx->envCtx.unk_DC, 1.0f, 1.0f, 0.1f);
        if (globalCtx->envCtx.unk_DC == 1.0f) {
            globalCtx->envCtx.unk_DC = 0.0f;
            this->unk_14B++;
            if (this->unk_14B >= 8) {
                this->unk_14B = 0;
            }
        }
        globalCtx->envCtx.unk_C2 = D_80A08198[this->unk_14B];
        globalCtx->envCtx.unk_C1 = D_80A081A0[this->unk_14B];
    }
    Math_ApproachF(&globalCtx->envCtx.unk_DC, 0.0f, 1.0f, 0.03f);
    if (gGameInfo->data[1311] == 0) {
        this->unk_174 = 0;
        this->actor.shape.shadowAlpha = 130;
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        DECR(this->unk_15C);
        DECR(this->unk_15E);
        DECR(this->unk_158);
        DECR(this->unk_18D6);

        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, globalCtx);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 200.0f, 100.0f, 5);
        if ((this->unk_148 != 0) || (gGameInfo->data[1336] != 0)) {
            gGameInfo->data[1336] = 0;
            this->unk_148 = 0;
            Audio_QueueSeqCmd(0x100100FF);
            func_809FE6B0(this, globalCtx);
        }
    }
    if (this->unk_158 != 0) {
        for (i = 0; i < 11; i++) {
            this->sph1.elements[i].info.bumperFlags &= ~2;
        }
    }
    func_809FEE70(this, globalCtx);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->sph1.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->sph1.base);
    if (this->actionFunc != func_809FE524) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x1000);
    }
    if ((this->unk_18D6 != 0) && !(this->unk_14C & 1)) {
        Boss07* temp_v0_12 = (Boss07*)Actor_SpawnAsChild(
            &globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_07, this->actor.world.pos.x,
            this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x, this->actor.world.rot.y, 7, 21);
        if (temp_v0_12 != NULL) {
            for (i = 0; i < 25; i++) {
                temp_v0_12->skelAnime1.limbDrawTbl[i] = this->skelAnime1.limbDrawTbl[i];
            }
        }
    }
    func_809F9E94(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Incarnation_Update.s")
#endif

void Boss07_Afterimage_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    Boss07* sp34 = (Boss07*)this->actor.parent;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 100, 155, 900, 1099);
    SkelAnime_DrawSV(globalCtx, sp34->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, sp34->skelAnime1.dListCount,
                     NULL, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_809FF678(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == 24) {
        rot->y += this->unk_17D8;
    }
    return false;
}

void func_809FF6B0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss07* this = THIS;
    Vec3f sp28;
    s8 i;

    if (limbIndex == 0x18) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
    i = D_80A0826C[limbIndex];
    if (i >= 0) {
        SysMatrix_GetStateTranslation(&this->unk_334[i]);
    }
    i = D_80A081A8[limbIndex];
    if (i >= 0) {
        if (this->unk_158 != 0) {
            SysMatrix_GetStateTranslationAndScaledZ(100000.0f, &sp28);
        } else {
            SysMatrix_MultiplyVector3fByState(&D_80A081E8[i], &sp28);
        }
        func_809F4BB0(i, &this->sph1, &sp28);
    }
    if (limbIndex == 8) {
        SysMatrix_GetStateTranslation(&this->unk_1788[0]);
    }
    if (limbIndex == 0x17) {
        SysMatrix_GetStateTranslation(&this->unk_1788[1]);
    }
    if (limbIndex == 0xD) {
        SysMatrix_GetStateTranslation(&this->unk_17AC);
    }
    if (limbIndex == 0x12) {
        SysMatrix_GetStateTranslation(&this->unk_17A0);
    }
    i = D_80A081C8[limbIndex];
    if (i >= 0) {
        f32 temp_f12 = this->unk_17B8[i];

        Matrix_Scale(temp_f12, temp_f12, temp_f12, 1);
    }
}

void func_809FF810(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == 3) {
        Matrix_Scale(this->unk_17F4, this->unk_17F0, 1.0f, 1);
    }
    if ((limbIndex == 0xA) || (limbIndex == 0xC) || (limbIndex == 0xD) || (limbIndex == 0xF) || (limbIndex == 0x11) ||
        (limbIndex == 0x12)) {
        Matrix_Scale(1.0f, this->unk_17E0, this->unk_17E0, 1);
    }
    if ((limbIndex == 5) || (limbIndex == 7) || (limbIndex == 8) || (limbIndex == 0x14) || (limbIndex == 0x16) ||
        (limbIndex == 0x17)) {
        Matrix_Scale(1.0f, this->unk_17E4, this->unk_17E4, 1);
    }
}

void Boss07_Incarnation_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    func_801343C0(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, this->skelAnime1.dListCount,
                  func_809FF678, func_809FF6B0, func_809FF810, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    func_800BE680(globalCtx, &this->actor, this->unk_334, 0xF, this->unk_17F8, this->unk_17FC, this->unk_1800,
                  this->unk_1804);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_809FFA04(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809FFA80;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_06019E48, -20.0f);
    this->timers[2] = Rand_ZeroFloat(150.0f) + 60.0f;
    this->unk_1870 = 1.0f;
}

void func_809FFA80(Boss07* this, GlobalContext* globalCtx) {
    s16 sp36;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 pad;
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_FLOAT_OLD - SFX_FLAG);
    if (this->timers[0] == 0) {
        if (this->timers[2] == 0) {
            if (((s8)this->actor.colChkInfo.health < 9) && (player->transformation != 0) && (Rand_ZeroOne() < 0.75f)) {
                func_80A006F4(this, globalCtx);
            } else {
                func_809FFE64(this, globalCtx);
            }
        } else if (Rand_ZeroOne() < 0.15f) {
            this->unk_18C = 2.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
        } else {
            func_809F4D10(&this->unk_164, 500.0f);
            this->unk_164.y = Rand_ZeroFloat(350.0f) + 100.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 20.0f;
            this->unk_170 = 0.0f;
            this->unk_18C = Rand_ZeroFloat(12.0f) + 3.0f;
        }
    }
    sp30 = this->unk_164.x - this->actor.world.pos.x;
    sp2C = this->unk_164.y - this->actor.world.pos.y;
    sp28 = this->unk_164.z - this->actor.world.pos.z;
    sp34 = Math_Atan2S(sp30, sp28);
    sp36 = Math_Atan2S(sp2C, sqrtf(SQ(sp30) + SQ(sp28)));
    sp36 += (s16)(Math_SinS(this->unk_14C * 0x1388) * 4000.0f);
    Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->unk_170);
    Math_ApproachS(&this->actor.world.rot.x, sp36, 5, this->unk_170);
    Math_ApproachF(&this->unk_170, 2000.0f, 1.0f, 100.0f);
    Math_ApproachF(&this->actor.speedXZ, this->unk_18C, 1.0f, 1.0f);
    if (this->timers[1] != 0) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x3000);
    } else if (this->unk_18C < 7.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x2000);
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x2000);
    }
    if ((player->unk_D57 == 4) && (Rand_ZeroOne() < 0.8f)) {
        this->timers[1] = 20;
    }
    Math_ApproachS(&this->actor.shape.rot.x, 0, 0xA, 0x200);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if ((this->unk_148 != 0) || (gGameInfo->data[1336] != 0)) {
        gGameInfo->data[1336] = 0;
        this->unk_148 = 0;
        Audio_QueueSeqCmd(0x100100FF);
        func_80A025AC(this, globalCtx);
    }
}

void func_809FFE64(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809FFEAC;
    this->unk_14E = 0;
    this->unk_ABD0 = 0;
    this->timers[0] = 30;
    this->unk_18D4 = 0;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_ATTACK_OLD);
}

void func_809FFEAC(Boss07* this, GlobalContext* globalCtx) {
    s16 sp36;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    Player* sp20 = PLAYER;

    this->actor.shape.rot.z -= this->unk_18D4;
    switch (this->unk_14E) {
        case 0:
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            func_809F4CBC(this, 1.0f);
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x100);
            Math_ApproachS(&this->unk_18D4, 0x2000, 1, 0x100);
            if (this->timers[0] == 0) {
                this->unk_14E = 1;
                this->actor.world.rot.x = 0;
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->timers[0] = 100;
                this->timers[1] = 20;
                this->unk_170 = 0.0f;
            }
            break;
        case 1:
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x400);
            Math_ApproachS(&this->unk_18D4, 0x2000, 1, 0x200);
            if (this->timers[1] != 0) {
                this->unk_164.x = sp20->actor.world.pos.x;
                this->unk_164.y = sp20->actor.world.pos.y + 10.0f;
                this->unk_164.z = sp20->actor.world.pos.z;
            } else {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_ROLLING_OLD - SFX_FLAG);
            }
            sp30 = this->unk_164.x - this->actor.world.pos.x;
            sp2C = this->unk_164.y - this->actor.world.pos.y;
            sp28 = this->unk_164.z - this->actor.world.pos.z;
            sp34 = Math_Atan2S(sp30, sp28);
            sp24 = sqrtf(SQ(sp30) + SQ(sp28));
            sp36 = Math_Atan2S(sp2C, sp24);
            Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->unk_170);
            Math_ApproachS(&this->actor.world.rot.x, sp36, 0xA, this->unk_170);
            Math_ApproachF(&this->unk_170, 3000.0f, 1.0f, 100.0f);
            Math_ApproachF(&this->actor.speedXZ, 20.0f, 1.0f, 2.0f);
            if (((this->unk_ABD0 == 0) && (sp24 < 100.0f)) || (this->timers[0] == 0)) {
                if (Rand_ZeroOne() < 0.25f) {
                    this->unk_14E = 2;
                    this->timers[0] = 30;
                } else {
                    func_809F4D10(&this->unk_164, 500.0f);
                    this->unk_164.y = Rand_ZeroFloat(100.0f) + 100.0f;
                    if (Rand_ZeroOne() < 0.3f) {
                        this->timers[1] = 20;
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_ATTACK_2ND_OLD);
                        this->unk_ABD0 = 1;
                    } else {
                        this->timers[1] = 0;
                        this->unk_ABD0 = 0;
                    }
                    this->timers[0] = 50;
                    this->unk_170 = 0.0f;
                }
            }
            break;
        case 2:
            Math_ApproachS(&this->unk_18D4, 0, 1, 0x100);
            Math_ApproachS(&this->actor.world.rot.x, 0x2000, 0xA, 0x7D0);
            func_809F4CBC(this, 0.5f);
            if (this->timers[0] == 0) {
                func_809FFA04(this, globalCtx);
            }
    }
}

void func_80A0021C(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A00274;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime1, &D_0600AE40, -10.0f);
    this->timers[0] = 100;
    this->unk_170 = 0.0f;
}

void func_80A00274(Boss07* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    func_8019F1C0(&D_80A09A40, NA_SE_EN_COMMON_WEAKENED - SFX_FLAG);
    func_809F4CBC(this, 0.5f);
    Math_ApproachS(&this->actor.shape.rot.x, -0x1000 + 0x4B0 * Math_SinS(this->unk_14C * 0xBB8), 5, 0x800);
    Math_ApproachS(&this->actor.shape.rot.z, -0x1000 + 0x3E8 * Math_SinS(this->unk_14C * 0x9C4), 5, 0x800);
    if (this->actor.world.pos.y > 51.0f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    }
    Math_ApproachF(&this->actor.world.pos.y, 50.0f + 10.0f * Math_SinS(this->unk_14C * 0x5DC), 0.1f, this->unk_170);
    Math_ApproachF(&this->unk_170, 15.0f, 1.0f, 1.0f);

    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->unk_1884 = 1;
    }
    if (this->timers[0] == 0) {
        func_809FFA04(this, globalCtx);
        this->timers[2] = 100;
    }
}

void func_80A00484(Boss07* this, GlobalContext* globalCtx, u8 arg2, Actor* arg3) {
    Player* player = PLAYER;

    this->actionFunc = func_80A00554;
    this->timers[0] = 40;
    if (arg2) {
        this->actor.speedXZ = 30.0f;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
        this->unk_18D4 = 0x1500;
    } else {
        if (player->stateFlags3 & 0x200) {
            this->actor.speedXZ = 20.0f;
            this->actor.velocity.y = 20.0f;
        } else {
            this->actor.speedXZ = 13.0f;
            this->actor.velocity.y = 10.0f;
            if (arg3 != NULL) {
                this->actor.world.rot.y = arg3->world.rot.y;
            }
        }
        this->unk_18D4 = 0x1000;
    }
    this->actor.colChkInfo.health -= arg2;
    if ((s8)this->actor.colChkInfo.health <= 0) {
        this->timers[0] = 30;
    }
    this->timers[1] = 30;
}

void func_80A00554(Boss07* this, GlobalContext* globalCtx) {
    this->unk_15C = 20;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
    if (this->actor.bgCheckFlags & 1) {
        func_809F4CBC(this, 1.0f);
        Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 1, 0x1000);
        Math_ApproachS(&this->unk_18D4, 0, 1, 0x100);
    } else {
        this->actor.shape.rot.x += 0x2000;
    }
    this->actor.shape.rot.z += this->unk_18D4;
    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->unk_1884 = 1;
    }
    if ((this->timers[0] == 15) && ((s8)this->actor.colChkInfo.health < 10)) {
        this->unk_774 = 1;
    }
    if (this->timers[0] == 0) {
        func_809FFA04(this, globalCtx);
        if ((s8)this->actor.colChkInfo.health <= 0) {
            this->unk_148 = 1;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            func_801A72CC(&this->actor.projectedPos);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_DEAD_OLD);
        } else {
            this->unk_164.x = this->actor.world.pos.x;
            this->unk_164.y = 200.0f;
            this->unk_164.z = this->actor.world.pos.z;
            this->actor.world.rot.x = 0x3000;
            this->timers[0] = 50;
            this->timers[2] = 100;
            this->unk_18C = 6.0f;
            this->unk_170 = 0.0f;
        }
    }
}

void func_80A006D0(Boss07* this) {
    this->unk_188C = 0.0f;
    this->unk_1890 = 0.0f;
    this->unk_1894 = 0.0f;
    this->unk_1898 = 0.0f;
    this->unk_18C0 = 0.0f;
}

void func_80A006F4(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A00720;
    this->unk_14E = 0;
    this->timers[0] = 30;
    this->unk_170 = 0.0f;
}

#ifdef NON_MATCHING
void func_80A00720(Boss07* this, GlobalContext* globalCtx) {
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f12;
    f32 sp180;
    f32 phi_f24;
    s16 phi_s0;
    s16 sp178;
    Vec3f sp16C;
    Vec3f sp160;
    Player* player = PLAYER;
    CollisionPoly* sp158;
    Vec3f sp14C;
    u8 sp14B = 0;
    u32 sp144;

    this->unk_15C = 20;
    func_809F4CBC(this, 0.5f);
    Math_ApproachF(&this->actor.world.pos.y, 300.0f, 0.05f, 1.0f);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if ((player->unk_730 != NULL) && (player->stateFlags1 & 0x400000)) {
        phi_f24 = (player->transformation == 4) ? 20 : 30.0f;
    } else {
        phi_f24 = (player->transformation == 4) ? 8.0f : 15.0f;
    }
    phi_s0 = (player->stateFlags1 & 0x400000) ? 1 : 10;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, phi_s0, this->unk_170);
    temp_f20 = player->actor.world.pos.x - this->actor.world.pos.x;
    temp_f12 = player->actor.world.pos.y - this->actor.world.pos.y + phi_f24;
    temp_f22 = player->actor.world.pos.z - this->actor.world.pos.z;
    Math_ApproachS(&this->actor.shape.rot.x, -Math_Atan2S(temp_f12, sqrtf(SQ(temp_f20) + SQ(temp_f22))), phi_s0,
                   this->unk_170);
    Math_ApproachF(&this->unk_170, 4000.0f, 1.0f, 200.0f);
    this->unk_1874 = 1;
    switch (this->unk_14E) {
        case 0:
            if (this->timers[0] == 25) {
                func_8019F1C0(&D_80A09A40, NA_SE_EN_LAST1_BLOW_OLD);
            }
            if (this->timers[0] == 0) {
                this->unk_14E = 1;
                this->timers[0] = 6;
                this->unk_1898 = 1.0f;
            }
            break;
        case 1:
            Math_ApproachF(&this->unk_188C, 1.0f, 1.0f, 0.2f);
            if (this->timers[0] == 0) {
                this->unk_14E = 2;
                this->timers[0] = 8;
            }
            break;
        case 2:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
            Math_ApproachF(&this->unk_1890, 1.0f, 0.2f, 0.2f);
            if (this->timers[0] == 0) {
                this->unk_14E = 3;
                this->timers[0] = 100;
            }
            break;
        case 3:
        case 4:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
        case 5:
            Math_ApproachF(&this->unk_1890, 1.0f, 0.2f, 0.2f);
            temp_f20 = player->actor.world.pos.x - this->unk_189C.x;
            temp_f12 = player->actor.world.pos.y - this->unk_189C.y + 20.0f;
            temp_f22 = player->actor.world.pos.z - this->unk_189C.z;
            sp180 = sqrtf(SQ(temp_f20) + SQ(temp_f12) + SQ(temp_f22));
            Math_ApproachF(&this->unk_1894, sp180 * 0.2f, 1.0f, 7.0f);

            if (func_800C55C4(&globalCtx->colCtx, &this->unk_189C, &this->unk_18A8, &sp14C, &sp158, 1, 1, 1, 1,
                              &sp144) &&
                (this->unk_14E != 5)) {
                Vec3f sp138;
                Vec3f sp12C;
                Vec3f sp120;

                sp138.x = randPlusMinusPoint5Scaled(20.0f) + sp14C.x;
                sp138.y = randPlusMinusPoint5Scaled(20.0f) + sp14C.y;
                sp138.z = randPlusMinusPoint5Scaled(20.0f) + sp14C.z;
                sp12C.x = 0.0f;
                sp12C.y = 6.0f;
                sp12C.z = 0.0f;
                sp120.x = sp12C.x * -0.05f;
                sp120.y = sp12C.y * -0.05f;
                sp120.z = sp12C.z * -0.05f;
                func_809F4AE8(globalCtx, &sp138, &sp12C, &sp120, Rand_ZeroFloat(10.0f) + 25.0f);
                sp14B = true;
            }
            sp16C.x = player->actor.world.pos.x - this->unk_189C.x;
            sp16C.y = player->actor.world.pos.y - this->unk_189C.y + 10.0f;
            sp16C.z = player->actor.world.pos.z - this->unk_189C.z;
            SysMatrix_InsertXRotation_s(-this->actor.shape.rot.x, 0);
            Matrix_RotateY(-this->actor.shape.rot.y, 1);
            SysMatrix_MultiplyVector3fByState(&sp16C, &sp160);
            if ((fabsf(sp160.x) < 20.0f) && (fabsf(sp160.y) < 50.0f) && (sp160.z > 40.0f) &&
                (sp160.z <= (this->unk_1894 * 20))) {
                if (func_8012405C(globalCtx) && (player->transformation == 4) && (player->stateFlags1 & 0x400000) &&
                    (FACING_ANGLE(&player->actor, &this->actor) < 0x2000) &&
                    (FACING_ANGLE(&player->actor, &this->actor) > -0x2000)) {
                    Vec3s sp118;

                    this->unk_1894 = sp180 * 0.05f;
                    Math_ApproachF(&this->unk_18C0, sp180 * 0.2f, 1.0f, 7.0f);
                    func_8018219C(&player->shieldMf, &sp118, 0);
                    sp118.y += 0x8000;
                    sp118.x = -sp118.x;
                    if (this->unk_14E == 3) {
                        this->unk_14E = 4;
                        this->unk_18C4 = sp118.x;
                        this->unk_18C6 = sp118.y;
                    } else {
                        player->unk_B84 = this->actor.yawTowardsPlayer;
                        player->unk_B80 = this->unk_1898 * 0.5f;
                        D_80A09A58->unk_1808 = 1;
                        D_80A09A58->unk_180C = this->unk_1898 * 30.0f;
                        D_80A09A58->unk_1810 = this->unk_18A8;
                        Math_ApproachS(&this->unk_18C4, sp118.x, 2, 0x2000);
                        Math_ApproachS(&this->unk_18C6, sp118.y, 2, 0x2000);
                        sp16C.x = this->actor.world.pos.x - this->unk_18A8.x;
                        sp16C.y = this->actor.world.pos.y - this->unk_18A8.y;
                        sp16C.z = this->actor.world.pos.z - this->unk_18A8.z;
                        sp180 = sqrtf(SQXYZ(sp16C));
                        SysMatrix_InsertXRotation_s(-this->unk_18C4, 0);
                        Matrix_RotateY(-this->unk_18C6, 1);
                        SysMatrix_StatePush();
                        SysMatrix_MultiplyVector3fByState(&sp16C, &sp160);
                        if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                            (sp160.z <= (this->unk_18C0 * 16.666668f)) && (this->unk_14E != 5)) {
                            s32 phi_s0_2;
                            Vec3f sp108;
                            Vec3f spFC;
                            Vec3f spF0;

                            this->unk_18D8 += 2;
                            this->unk_18C0 = sp180 * 0.062f;
                            if (this->unk_18D8 < 10) {
                                sp108.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(40.0f);
                                sp108.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(40.0f);
                                sp108.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(40.0f);
                                spFC.x = 0.0f;
                                spFC.y = 6.0f;
                                spFC.z = 0.0f;
                                spF0.x = spFC.x * -0.05f;
                                spF0.y = spFC.y * -0.05f;
                                spF0.z = spFC.z * -0.05f;
                                func_809F4AE8(globalCtx, &sp108, &spFC, &spF0, Rand_ZeroFloat(10.0f) + 25.0f);
                                this->unk_15E |= 0xA;
                            } else {
                                this->unk_15C = 50;
                                this->unk_15E = 15;
                                func_801A72CC(&this->actor.projectedPos);
                                Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_DAMAGE2_OLD);
                                func_80A00484(this, globalCtx, 2, NULL);
                                func_80A006D0(this);
                                for (phi_s0_2 = 0; phi_s0_2 < 20; phi_s0_2++) {
                                    sp108.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(50.0f);
                                    sp108.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(50.0f);
                                    sp108.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(50.0f);
                                    spFC.x = randPlusMinusPoint5Scaled(20.0f);
                                    spFC.y = randPlusMinusPoint5Scaled(20.0f);
                                    spFC.z = randPlusMinusPoint5Scaled(20.0f);
                                    spF0.x = spFC.x * -0.05f;
                                    spF0.y = spFC.y * -0.05f;
                                    spF0.z = spFC.z * -0.05f;
                                    func_809F4AE8(globalCtx, &sp108, &spFC, &spF0, Rand_ZeroFloat(10.0f) + 25.0f);
                                }
                                if ((s8)this->actor.colChkInfo.health <= 0) {
                                    this->unk_18D6 = 200;
                                } else {
                                    this->unk_18D6 = 60;
                                }
                            }
                        }
                        SysMatrix_StatePop();
                        for (sp178 = 0; sp178 < 4; sp178++) {
                            if (D_80A09A60[sp178]->unk_14E < 2) {
                                sp16C.x = D_80A09A60[sp178]->actor.world.pos.x - this->unk_18A8.x;
                                sp16C.y = D_80A09A60[sp178]->actor.world.pos.y - this->unk_18A8.y;
                                sp16C.z = D_80A09A60[sp178]->actor.world.pos.z - this->unk_18A8.z;
                                sp180 = sqrtf(SQXYZ(sp16C));
                                SysMatrix_MultiplyVector3fByState(&sp16C, &sp160);
                                if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                                    (sp160.z <= (this->unk_18C0 * 16.666668f)) && (this->unk_14E != 5)) {
                                    s32 pad;
                                    Vec3f spE0;
                                    Vec3f spD4;
                                    Vec3f spC8;

                                    this->unk_18D8 += 2;
                                    this->unk_18C0 = sp180 * 0.062f;
                                    if (this->unk_18D8 < 5) {
                                        spE0.x =
                                            D_80A09A60[sp178]->actor.world.pos.x + randPlusMinusPoint5Scaled(40.0f);
                                        spE0.y =
                                            D_80A09A60[sp178]->actor.world.pos.y + randPlusMinusPoint5Scaled(40.0f);
                                        spE0.z =
                                            D_80A09A60[sp178]->actor.world.pos.z + randPlusMinusPoint5Scaled(40.0f);
                                        spD4.x = 0.0f;
                                        spD4.y = 6.0f;
                                        spD4.z = 0.0f;
                                        spC8.x = spD4.x * -0.05f;
                                        spC8.y = spD4.y * -0.05f;
                                        spC8.z = spD4.z * -0.05f;

                                        func_809F4AE8(globalCtx, &spE0, &spD4, &spC8, Rand_ZeroFloat(10.0f) + 25.0f);
                                        D_80A09A60[sp178]->unk_15E |= 0xA;
                                    } else {
                                        D_80A09A60[sp178]->unk_14E = 2;
                                        D_80A09A60[sp178]->unk_18D6 = 60;
                                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FOLLOWERS_DEAD);
                                        for (pad = 0; pad < 20; pad++) {
                                            spE0.x =
                                                D_80A09A60[sp178]->actor.world.pos.x + randPlusMinusPoint5Scaled(50.0f);
                                            spE0.y =
                                                D_80A09A60[sp178]->actor.world.pos.y + randPlusMinusPoint5Scaled(50.0f);
                                            spE0.z =
                                                D_80A09A60[sp178]->actor.world.pos.z + randPlusMinusPoint5Scaled(50.0f);
                                            spD4.x = randPlusMinusPoint5Scaled(20.0f);
                                            spD4.y = randPlusMinusPoint5Scaled(20.0f);
                                            spD4.z = randPlusMinusPoint5Scaled(20.0f);
                                            spC8.x = spD4.x * -0.05f;
                                            spC8.y = spD4.y * -0.05f;
                                            spC8.z = spD4.z * -0.05f;
                                            func_809F4AE8(globalCtx, &spE0, &spD4, &spC8,
                                                          Rand_ZeroFloat(10.0f) + 25.0f);
                                        }
                                    }
                                }
                            }
                        }
                        if (func_800C55C4(&globalCtx->colCtx, &this->unk_18A8, &this->unk_18B4, &sp14C, &sp158, 1, 1, 1,
                                          1, &sp144) &&
                            (this->unk_14E != 5)) {
                            Vec3f spBC;
                            Vec3f spB0;
                            Vec3f spA4;

                            sp14B = true;
                            spBC.x = randPlusMinusPoint5Scaled(20.0f) + sp14C.x;
                            spBC.y = randPlusMinusPoint5Scaled(20.0f) + sp14C.y;
                            spBC.z = randPlusMinusPoint5Scaled(20.0f) + sp14C.z;
                            spB0.x = 0.0f;
                            spB0.y = 6.0f;
                            spB0.z = 0.0f;
                            spA4.x = spB0.x * -0.05f;
                            spA4.y = spB0.y * -0.05f;
                            spA4.z = spB0.z * -0.05f;

                            func_809F4AE8(globalCtx, &spBC, &spB0, &spA4, Rand_ZeroFloat(10.0f) + 25.0f);
                        }
                    }
                } else if (!player->isBurning && (this->unk_14E != 5)) {
                    s32 pad2;

                    func_800B8D50(globalCtx, &this->actor, 5.0f, this->actor.shape.rot.y, 0.0f, 0x10);
                    for (pad2 = 0; pad2 < 18; pad2++) {
                        player->flameTimers[pad2] = Rand_S16Offset(0, 200);
                    }
                    player->isBurning = true;
                    func_800B8E58(&player->actor, player->ageProperties->unk_92 + NA_SE_VO_LI_DEMO_DAMAGE);
                }
            }
            if (sp14B) {
                if (sp14C.y == 0.0f) {
                    temp_f20 = this->unk_18E0.x - sp14C.x;
                    temp_f22 = this->unk_18E0.z - sp14C.z;
                    func_800AE930(&globalCtx->colCtx, Effect_GetParams(this->effectIndex), &sp14C, 15.0f,
                                  Math_Atan2S(temp_f20, temp_f22), sp158, sp144);
                    this->unk_18EC = 1;
                }
                this->unk_18E0 = sp14C;
            }
            if (this->unk_14E != 5) {
                if (this->timers[0] == 0) {
                    this->unk_14E = 5;
                    this->timers[0] = 20;
                }
            } else {
                Math_ApproachZeroF(&this->unk_1898, 1.0f, 0.05f);
                if (this->timers[0] == 0) {
                    func_809FFA04(this, globalCtx);
                    this->timers[2] = 100;
                    func_80A006D0(this);
                }
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00720.s")
#endif

void func_80A016E4(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A01750;
    this->actor.world.pos.x = 0.0f;
    this->actor.world.pos.y = 300.0f;
    this->actor.world.pos.z = -922.5f;
    this->unk_160 = KREG(75) + 150;
    func_8016566C(this->unk_160);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A01750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A025AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0264C.s")

void func_80A02B30(Boss07* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    ColliderInfo* hitbox;
    u8 sp27;
    Actor* hit;

    if (this->unk_15C == 0) {
        if (this->quad1.base.acFlags & 2) {
            this->quad1.base.acFlags &= ~2;
            this->unk_186C = 7;
        }
        if (this->quad2.base.acFlags & 2) {
            this->quad2.base.acFlags &= ~2;
            this->unk_186C = 15;
            if ((this->actionFunc == func_80A00274) || (player->stateFlags3 & 0x200)) {
                hit = this->quad2.base.ac;
                hitbox = this->quad2.info.acHitInfo;
                sp27 = (hitbox->toucher.dmgFlags & 0xF7CFFFFF) ? this->actor.colChkInfo.damage : 0;
                this->unk_15C = 50;
                this->unk_15E = 15;
                func_801A72CC(&this->actor.projectedPos);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_DAMAGE2_OLD);
                func_80A00484(this, globalCtx, sp27, hit);
            } else {
                this->unk_15C = 15;
                func_801A72CC(&this->actor.projectedPos);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST1_DAMAGE1_OLD);
                func_80A0021C(this, globalCtx);
            }
        }
    }
}

void Boss07_Mask_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;
    Player* spA8 = PLAYER;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    f32 sp68;

    this->actor.hintId = 50;
    if (D_80A09A71 != 0) {
        D_80A09A71--;
        if (D_80A09A71 == 0) {
            Audio_QueueSeqCmd(0x806B);
        }
    }
    Math_Vec3f_Copy(&D_80A09A40, &this->actor.projectedPos);
    if ((D_80A09A58 == NULL) || (D_80A09A58->unk_ABD2 == 0)) {
        this->unk_149 = 1;
        globalCtx->envCtx.unk_C1 = 2;
        globalCtx->envCtx.unk_C2 = 0;
        Math_ApproachF(&globalCtx->envCtx.unk_DC, this->unk_1898, 1.0f, 0.1f);
        this->unk_14C += 1;
        if (gGameInfo->data[1311] == 0) {
            this->unk_174 = 0;
            this->unk_1884 = 0;
            this->unk_1874 = 0;
            Actor_SetScale(&this->actor, 0.1f);
            this->actor.focus.pos = this->actor.world.pos;
            for (i = 0; i < 3; i++) {
                DECR(this->timers[i]);
            }
            DECR(this->unk_186C);
            DECR(this->unk_15C);
            DECR(this->unk_15E);
            DECR(this->unk_18D6);
            DECR(this->unk_18D8);

            this->unk_18EC = 0;
            this->actionFunc(this, globalCtx);
            if ((this->unk_18EC == 0) && (this->unk_18ED != 0)) {
                func_800AEF44(Effect_GetParams(this->effectIndex));
            }
            this->unk_18ED = this->unk_18EC;
            if (this->actionFunc != func_80A01750) {
                if (this->actionFunc != func_80A00554) {
                    Actor_SetVelocityXYRotation(&this->actor);
                    Actor_ApplyMovement(&this->actor);
                } else {
                    if (this->actor.bgCheckFlags & 1) {
                        this->actor.velocity.y = 0.0f;
                    }
                    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
                }
                if (this->unk_1888 == 0) {
                    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 60.0f, 100.0f, 5);
                } else {
                    this->unk_1888--;
                }
            }
        } else {
            this->actor.colChkInfo.health = 0;
        }
        func_80A02B30(this, globalCtx);
        SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                    MTXMODE_NEW);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
        sp6C.x = -55.0f;
        sp6C.y = 55.0f;
        sp6C.z = 10.0f;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp9C);
        sp6C.x = -55.0f;
        sp6C.y = -55.0f;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp90);
        sp6C.x = 55.0f;
        sp6C.y = 55.0f;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp84);
        sp6C.x = 55.0f;
        sp6C.y = -55.0f;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp78);
        Collider_SetQuadVertices(&this->quad1, &sp9C, &sp90, &sp84, &sp78);

        sp68 = (spA8->stateFlags3 & 0x200) ? 70.0f : 40.0f;
        sp6C.x = -sp68;
        sp6C.y = sp68;
        sp6C.z = -10.0f;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp9C);
        sp6C.x = -sp68;
        sp6C.y = -sp68;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp90);
        sp6C.x = sp68;
        sp6C.y = sp68;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp84);
        sp6C.x = sp68;
        sp6C.y = -sp68;
        SysMatrix_MultiplyVector3fByState(&sp6C, &sp78);
        Collider_SetQuadVertices(&this->quad2, &sp9C, &sp90, &sp84, &sp78);

        if (spA8->stateFlags3 & 0x200) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->quad2.base);
        } else {
            if ((this->actionFunc != func_80A00274) && (this->actionFunc != func_80A00554)) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->quad1.base);
            }
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->quad2.base);
            if (this->actionFunc == func_809FFEAC) {
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->quad1.base);
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->quad2.base);
            }
        }
        if (this->unk_18D6 != 0) {
            Vec3f sp5C;
            Vec3f sp50;
            Vec3f sp44;
            f32 sp40 = (this->actionFunc == func_80A0264C) ? 130.0f : 80.0f;

            sp5C.x = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.x;
            sp5C.y = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.y;
            sp5C.z = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.z;
            sp50.x = 0.0f;
            sp50.y = 5.0f;
            sp50.z = 0.0f;
            sp44.x = sp50.x * -0.05f;
            sp44.y = sp50.y * -0.05f;
            sp44.z = sp50.z * -0.05f;
            func_809F4AE8(globalCtx, &sp5C, &sp50, &sp44, Rand_ZeroFloat(10.0f) + 25.0f);
            func_8019F1C0(&D_80A09A40, NA_SE_EV_BURN_OUT - SFX_FLAG);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A036C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03F18.s")

#ifdef NON_MATCHING
void Boss07_Mask_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;
    s32 phi_s6;
    f32 temp_f20;
    f32 temp_f22;
    f32 phi_f24;
    f32 pad2;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    temp_f20 = this->unk_186C * (M_PI / 4.0f) * 0.06666667f;
    temp_f22 = Math_SinS(this->unk_186C * 0x3500) * temp_f20 * 0.5f;
    SysMatrix_InsertYRotation_f(Math_SinS(this->unk_186C * 0x4500) * temp_f20, 1);
    SysMatrix_RotateStateAroundXAxis(temp_f22);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    gSPSegment(POLY_OPA_DISP++, 8, Lib_SegmentedToVirtual(D_80A082E0[this->unk_1884]));
    SkelAnime_Draw(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, NULL, func_80A03F18,
                   &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    gSPDisplayList(POLY_OPA_DISP++, D_0600AFB0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);

    phi_s6 = ((this->actionFunc == func_809FFA80) &&
              (ABS_ALT((s16)(this->actor.world.rot.y - this->actor.shape.rot.y)) > 0x4000))
                 ? 1
                 : 0;

    Matrix_RotateY(this->actor.shape.rot.y, 0);
    SysMatrix_InsertXRotation_s(this->actor.shape.rot.x, 1);
    SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, 1);
    SysMatrix_GetStateTranslationAndScaledZ(-3.0f, &sp90);
    spA8.x = 0.0f;
    spA8.y = 20.0f;
    spA8.z = -2.0f;
    phi_f24 = 0.0f;
    for (i = 0; i < 25; i++) {
        SysMatrix_StatePush();
        SysMatrix_StatePush();
        SysMatrix_InsertZRotation_f(phi_f24, 1);
        SysMatrix_MultiplyVector3fByState(&spA8, &sp9C);
        this->unk_19F0[i].unk_0.x = this->unk_1878.x + sp9C.x;
        this->unk_19F0[i].unk_0.y = this->unk_1878.y + sp9C.y;
        this->unk_19F0[i].unk_0.z = this->unk_1878.z + sp9C.z;

        pad2 = (1 - (i * 0.008f)) * this->unk_1870;
        SysMatrix_StatePop();
        if (this->unk_149 != 0) {
            func_80A03238(this, globalCtx, &this->unk_19F0[i].unk_0, this->unk_19F0[i].unk_C, this->unk_19F0[i].unk_84,
                          this->unk_19F0[i].unk_FC, &sp90, pad2, phi_s6, phi_f24);
        }
        func_80A036C4(this, globalCtx, this->unk_19F0[i].unk_C, this->unk_19F0[i].unk_84, pad2, i * 0.9f);
        phi_f24 += 0.5f;
        spA8.y += 1.0f;

        SysMatrix_StatePop();
    }
    func_80A03868(this, globalCtx);
    this->unk_149 = 0;
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Mask_Draw.s")
#endif

#ifdef NON_MATCHING
void Boss07_Projectile_Update(Actor* thisx, GlobalContext* globalCtx2) {
    s32 i;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    Player* player = PLAYER;

    this->unk_14C++;
    if (this->actor.params == 100) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FOLLOWERS_BEAM - SFX_FLAG);
    }
    if (gGameInfo->data[1311] == 0) {
        Actor_SetScale(&this->actor, 3.5f);
        if (this->unk_14E == 0) {
            sp58 = player->actor.world.pos.x - this->actor.world.pos.x;
            sp54 = player->actor.world.pos.y - this->actor.world.pos.y + 20.0f;
            sp50 = player->actor.world.pos.z - this->actor.world.pos.z;

            this->actor.world.rot.y = Math_Atan2S(sp58, sp50);
            this->actor.world.rot.x = Math_Atan2S(sp54, sqrtf(SQ(sp58) + SQ(sp50)));
            this->unk_14E = 1;
            this->actor.speedXZ = 30.0f;
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_ENEMY);
            if (this->actor.params == 101) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_LAST2_FIRE_OLD);
            }
        }
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        Actor_SetVelocityXYRotation(&this->actor);
        Actor_ApplyMovement(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 31.0f, 100.0f, 7);
        this->actor.shape.rot.z += 0x1200;
        if ((this->actor.bgCheckFlags & 0x19) || (this->cyl2.base.atFlags & 2) || (this->cyl2.base.atFlags & 2) ||
            (D_80A09A70 != 0)) {
            Actor_MarkForDeath(&this->actor);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, this->unk_181C,
                        CLEAR_TAG_SMALL_LIGHT_RAYS);
        }
        Collider_UpdateCylinder(&this->actor, &this->cyl2);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->cyl2.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->cyl2.base);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Projectile_Update.s")
#endif

void Boss07_Projectile_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, D_80A07968[this->unk_181C][0], D_80A07968[this->unk_181C][1],
                    D_80A07968[this->unk_181C][2], 255);
    gDPSetEnvColor(POLY_XLU_DISP++, D_80A07950[this->unk_181C][0], D_80A07950[this->unk_181C][1],
                   D_80A07950[this->unk_181C][2], 128);
    SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, 0.0f, 1);
    SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
    SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, 1);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
    gSPDisplayList(POLY_XLU_DISP++, D_04023348);
    gSPDisplayList(POLY_XLU_DISP++, D_04023428);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04768.s")

void func_80A04878(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A04890;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04890.s")

void func_80A04DE0(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A04E5C;
    this->actor.gravity = -0.75f;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 40.0f);
    Collider_InitAndSetCylinder(globalCtx, &this->cyl2, &this->actor, &D_80A07EA4);
    this->actor.colChkInfo.health = 5;
    this->unk_14E = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A055E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05608.s")

void Boss07_Remains_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    s32 i;

    this->unk_14C++;
    for (i = 0; i < 3; i++) {
        if (this->timers[i] != 0) {
            this->timers[i]--;
        }
    }
    if (this->unk_18D6 != 0) {
        this->unk_18D6--;
    }
    if (this->unk_15C != 0) {
        this->unk_15C--;
    }
    if (this->unk_15E != 0) {
        this->unk_15E--;
    }
    this->actionFunc(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.world.pos.x += this->unk_18CC;
    this->actor.world.pos.z += this->unk_18D0;
    Math_ApproachZeroF(&this->unk_18CC, 1.0f, 1.0f);
    Math_ApproachZeroF(&this->unk_18D0, 1.0f, 1.0f);
}

void Boss07_Remains_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;
    f32 sp64;
    f32 sp60;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    sp64 = this->unk_15C * (M_PI / 4.0f) * 0.06666667f;
    sp60 = Math_SinS(this->unk_15C * 0x3500) * sp64 * 0.5f;
    SysMatrix_InsertYRotation_f(Math_SinS(this->unk_15C * 0x4500) * sp64, 1);
    SysMatrix_RotateStateAroundXAxis(sp60);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
    switch (this->actor.params) {
        case 200:
            gSPDisplayList(POLY_OPA_DISP++, D_060149A0);
            break;
        case 201:
            gSPDisplayList(POLY_OPA_DISP++, D_06016090);
            break;
        case 202:
            gSPDisplayList(POLY_OPA_DISP++, D_06017DE0);
            break;
        case 203:
            gSPDisplayList(POLY_OPA_DISP++, D_06019328);
            break;
    }
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    if (this->actionFunc == func_80A04890) {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, 200);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 100, 128);

        SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
        Matrix_Scale(this->unk_188C, this->unk_188C, 0.0f, 1);
        SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
        SysMatrix_InsertZRotation_s(this->unk_18C8, 1);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
        gSPDisplayList(POLY_XLU_DISP++, D_04023348);
        gSPDisplayList(POLY_XLU_DISP++, D_04023428);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A05AF8(Boss07* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A05B50;
    this->actor.gravity = 0.0f;
    this->unk_17C = (sREG(42) * 0.01f) + 0.9f;
    this->timers[0] = 200;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05DDC.s")

void func_80A06500(Boss07* this, GlobalContext* globalCtx) {
    s32 i;
    Boss07* phi_a2;
    f32 dx;
    f32 dy;
    f32 dz;

    if (this->unk_158 == 0) {
        phi_a2 = (Boss07*)globalCtx->actorCtx.actorList[ACTORCAT_BOSS].first;

        while (phi_a2 != NULL) {
            if ((this != phi_a2) && (phi_a2->actor.params == 180) && (phi_a2->unk_158 == 0)) {
                dx = phi_a2->actor.world.pos.x - this->actor.world.pos.x;
                dy = phi_a2->actor.world.pos.y - this->actor.world.pos.y;
                dz = phi_a2->actor.world.pos.z - this->actor.world.pos.z;

                if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < (gGameInfo->data[1564] + 50.0f)) {
                    phi_a2->unk_158 = this->unk_158 = 10;
                    this->actor.world.rot.y = Math_Atan2S(dx, dz);
                    phi_a2->actor.world.rot.y = this->actor.world.rot.y + 0x7FFF;
                    if (this->timers[0] > 0) {
                        this->actor.speedXZ = -10.0f;
                    } else {
                        this->actor.speedXZ = -5.0f;
                        this->unk_17C = (gGameInfo->data[1625] * 0.01f) + 0.2f;
                        this->unk_180 = 0x800;
                    }
                    if (phi_a2->timers[0] > 0) {
                        phi_a2->actor.speedXZ = -10.0f;
                    } else {
                        phi_a2->actor.speedXZ = -5.0f;
                        phi_a2->unk_17C = (gGameInfo->data[1625] * 0.01f) + 0.2f;
                        phi_a2->unk_180 = 0x800;
                    }
                    CollisionCheck_SpawnShieldParticles(globalCtx, &this->actor.focus.pos);
                    CollisionCheck_SpawnShieldParticles(globalCtx, &phi_a2->actor.focus.pos);
                    if (this->timers[0] > 80) {
                        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((gGameInfo->data[1565] + 20) * 256.0f);
                        for (i = 0; i < 5; i++) {
                            DECR(this->timers[0]);
                            DECR(this->timers[1]);
                        }
                    }
                    if (phi_a2->timers[0] > 80) {
                        phi_a2->actor.shape.rot.z = randPlusMinusPoint5Scaled((gGameInfo->data[1565] + 20) * 256.0f);
                        for (i = 0; i < 5; i++) {
                            DECR(phi_a2->timers[0]);
                            DECR(phi_a2->timers[1]);
                        }
                    }
                    Audio_PlayActorSound2(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
                    return;
                }
            }
            phi_a2 = (Boss07*)phi_a2->actor.next;
        }
    }
}

void func_80A06990(Boss07* this, GlobalContext* globalCtx) {
    s32 sp3C;
    s32 sp38 = 0;
    Player* player = PLAYER;
    s32 pad[3];

    if (this->cyl2.base.acFlags & 2) {
        this->cyl2.base.acFlags &= ~2;
        if (this->unk_15C == 0) {
            this->unk_15C = 5;
            if ((this->actor.colChkInfo.damageEffect == 13) || (this->actor.colChkInfo.damageEffect == 10)) {
                if (this->actor.colChkInfo.damageEffect == 13) {
                    player->unk_B84 = this->actor.yawTowardsPlayer;
                    player->unk_B80 = 20.0f;
                }
                if (this->timers[0] > 40) {
                    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                    if (player->transformation == 0) {
                        this->actor.speedXZ = -30.0f;
                        this->actor.velocity.y = 10.0f;
                        if ((s16)(gGameInfo->data[1583] + 100) < this->timers[0]) {
                            this->timers[0] = gGameInfo->data[1583] + 100;
                            this->timers[1] = gGameInfo->data[1613] + 170;
                        }
                    } else if (this->actor.colChkInfo.damageEffect == 10) {
                        this->actor.speedXZ = -15.0f;
                    } else {
                        this->actor.speedXZ = -7.0f;
                    }
                }
            } else if (this->actor.colChkInfo.damageEffect == 12) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->actor.speedXZ = 2.0f * -player->actor.speedXZ;
                sp38 = 1;
            } else if (this->actor.colChkInfo.damageEffect == 11) {
                this->actor.world.rot.y = Math_Atan2S(this->cyl2.base.ac->world.pos.x - this->actor.world.pos.x,
                                                      this->cyl2.base.ac->world.pos.z - this->actor.world.pos.z);
                this->actor.speedXZ = -20.0f;
                this->actor.velocity.y = gGameInfo->data[1591] + 15.0f;
                sp38 = 1;
            }
        }
    }
    if (this->actor.bgCheckFlags & 1) {
        if ((func_800B64FC(globalCtx, 5.0f, &this->actor.world.pos, &sp3C) >= 0.0f) && (sp3C == 0)) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->actor.velocity.y = gGameInfo->data[1591] + 25.0f;
            sp38 = 1;
        }
    }
    if (sp38 && (this->timers[0] > 90)) {
        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((gGameInfo->data[1565] + 30) * 256.0f);
        this->timers[0] = Rand_ZeroFloat(10.0f) + 70.0f;
        this->timers[1] = this->timers[0] + 70;
    }
}

void Boss07_Top_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    this->unk_14C++;
    DECR(this->timers[0]);
    DECR(this->timers[1]);
    DECR(this->unk_15E);
    DECR(this->unk_15C);
    DECR(this->unk_158);
    this->actionFunc(this, globalCtx);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 25.0f;
    func_80A06990(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->cyl2);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->cyl2.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->cyl2.base);
    func_80A06500(this, globalCtx);
    this->unk_178 -= this->unk_17C;
    if (this->unk_178 < -2.0f * M_PI) {
        this->unk_178 += 2.0f * M_PI;
    }
    if (D_80A09A54->actionFunc == func_809F65F4) {
        Actor_MarkForDeath(&this->actor);
    }
    Math_ApproachF(&this->actor.scale.x, (sREG(77) * 0.001f) + 0.06f, 1.0f, 0.012f);
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void Boss07_Top_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 780, 1099);
    }
    SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_RotateY(this->actor.shape.rot.y, 1);
    SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, 1);
    SysMatrix_InsertYRotation_f(this->unk_178, 1);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), 2);
    gSPDisplayList(POLY_OPA_DISP++, D_0602F640);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#ifdef NON_MATCHING
void Boss07_Effects_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    func_80A07638(globalCtx);

    if (D_80A09A4C != 0) {
        D_80A09A4C--;
        play_sound(NA_SE_EN_LAST2_HEARTBEAT_OLD - SFX_FLAG);
    }
    if (this->unk_1808 != 0) {
        D_801F4E32 = 1;
        D_801F4E38 = this->unk_1810;
        D_801F4E44 = this->unk_180C;
        D_801F4E48 = 10.0f;
        D_801F4E4C = 0;
        this->unk_1808 = 0;
    } else {
        D_801F4E32 = 0;
    }
    this->unk_ABC8++;
    switch (this->unk_ABD0) {
        case 0:
            if ((D_80A09A5C != NULL) && (D_80A09A5C->unk_774 != 0)) {
                this->unk_ABD0 = 1;
                this->unk_ABC8 = 0;
            }
            break;
        case 1:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                func_800EA0D4(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 7);
                this->unk_ABD2 = func_801694DC(globalCtx);
                func_80169590(globalCtx, 0, 1);
                func_80169590(globalCtx, this->unk_ABD2, 7);
                this->unk_ABC8 = 0;
                this->unk_ABD0 = 2;
                func_8016566C(150);
                this->unk_ABD4.x = D_80A09A60[0]->actor.world.pos.x * 0.7f;
                this->unk_ABD4.y = D_80A09A60[0]->actor.world.pos.y * 0.7f;
                this->unk_ABD4.z = D_80A09A60[0]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 2:
            if (this->unk_ABC8 == 20) {
                D_80A09A60[0]->unk_14E = 20;
            }
            this->unk_ABE0.x = D_80A09A60[0]->actor.world.pos.x;
            this->unk_ABE0.y = D_80A09A60[0]->actor.world.pos.y;
            this->unk_ABE0.z = D_80A09A60[0]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->unk_ABD0 = 3;
                this->unk_ABC8 = 0;
                this->unk_ABD4.x = D_80A09A60[1]->actor.world.pos.x * 0.7f;
                this->unk_ABD4.y = D_80A09A60[1]->actor.world.pos.y * 0.7f;
                this->unk_ABD4.z = D_80A09A60[1]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 3:
            if (this->unk_ABC8 == 20) {
                D_80A09A60[1]->unk_14E = 20;
            }
            this->unk_ABE0.x = D_80A09A60[1]->actor.world.pos.x;
            this->unk_ABE0.y = D_80A09A60[1]->actor.world.pos.y;
            this->unk_ABE0.z = D_80A09A60[1]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->unk_ABD0 = 4;
                this->unk_ABC8 = 0;
                this->unk_ABD4.x = D_80A09A60[2]->actor.world.pos.x * 0.7f;
                this->unk_ABD4.y = D_80A09A60[2]->actor.world.pos.y * 0.7f;
                this->unk_ABD4.z = D_80A09A60[2]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 4:
            if (this->unk_ABC8 == 20) {
                D_80A09A60[2]->unk_14E = 20;
            }
            this->unk_ABE0.x = D_80A09A60[2]->actor.world.pos.x;
            this->unk_ABE0.y = D_80A09A60[2]->actor.world.pos.y;
            this->unk_ABE0.z = D_80A09A60[2]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->unk_ABD0 = 5;
                this->unk_ABC8 = 0;
                this->unk_ABD4.x = D_80A09A60[3]->actor.world.pos.x * 0.7f;
                this->unk_ABD4.y = D_80A09A60[3]->actor.world.pos.y * 0.7f;
                this->unk_ABD4.z = D_80A09A60[3]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 5:
            if (this->unk_ABC8 == 20) {
                D_80A09A60[3]->unk_14E = 20;
            }
            this->unk_ABE0.x = D_80A09A60[3]->actor.world.pos.x;
            this->unk_ABE0.y = D_80A09A60[3]->actor.world.pos.y;
            this->unk_ABE0.z = D_80A09A60[3]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                Camera* temp_v0_3 = Play_GetCamera(globalCtx, 0);
                s32 i;

                this->unk_ABD0 = 6;
                this->unk_ABC8 = 0;
                temp_v0_3->eye = this->unk_ABD4;
                temp_v0_3->eyeNext = this->unk_ABD4;
                temp_v0_3->at = this->unk_ABE0;
                func_80169AFC(globalCtx, this->unk_ABD2, 0);
                this->unk_ABD2 = 0;
                func_800EA0EC(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                func_80165690();
                for (i = 0; i < 4; i++) {
                    func_800BC154(globalCtx, &globalCtx->actorCtx, &D_80A09A60[i]->actor, 5);
                }
            }
            break;
        case 6:
            break;
    }
    if (this->unk_ABD2 != 0) {
        if (this->unk_ABC8 < 20) {
            s32 j;

            for (j = 0; j < 4; j++) {
                if ((this->unk_ABC8 & 1) != 0) {
                    D_80A09A60[j]->actor.world.pos.x += 2.0f;
                    D_80A09A60[j]->actor.world.pos.z += 2.0f;
                } else {
                    D_80A09A60[j]->actor.world.pos.x -= 2.0f;
                    D_80A09A60[j]->actor.world.pos.z -= 2.0f;
                }
            }
        }
        ShrinkWindow_SetLetterboxTarget(27);
        Play_CameraSetAtEye(globalCtx, this->unk_ABD2, &this->unk_ABE0, &this->unk_ABD4);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Effects_Update.s")
#endif

void Boss07_Effects_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss07* this = THIS;

    func_80A07740(globalCtx);
    func_809FBF94(this, globalCtx);
}

void func_80A07638(GlobalContext* globalCtx) {
    Boss07Effect* effect = (Boss07Effect*)globalCtx->specialEffects;
    s32 i;

    for (i = 0; i < 50; i++, effect++) {
        if (effect->unk_0 != 0) {
            effect->unk_2++;

            effect->unk_4.x += effect->unk_10.x;
            effect->unk_4.y += effect->unk_10.y;
            effect->unk_4.z += effect->unk_10.z;

            effect->unk_10.x += effect->unk_1C.x;
            effect->unk_10.y += effect->unk_1C.y;
            effect->unk_10.z += effect->unk_1C.z;
            if (effect->unk_0 == 1) {
                if (effect->unk_30 != 0) {
                    effect->unk_2C -= (i & 7) + 13;
                    if (effect->unk_2C <= 0) {
                        effect->unk_2C = 0;
                        effect->unk_0 = 0;
                    }
                } else {
                    effect->unk_2C += 300;
                    if (effect->unk_2C >= 255) {
                        effect->unk_2C = 255;
                        effect->unk_30++;
                    }
                }
            }
        }
    }
}

void func_80A07740(GlobalContext* globalCtx) {
    Boss07Effect* effect = (Boss07Effect*)globalCtx->specialEffects;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 i;

    OPEN_DISPS(gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    for (i = 0; i < 50; i++, effect++) {
        if (effect->unk_0 > 0) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 20, 0, effect->unk_2C);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 215, 255, 128);
            gSPSegment(POLY_XLU_DISP++, 8,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (3 * effect->unk_2) & 0x7F,
                                        (15 * -effect->unk_2) & 0xFF, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));
            SysMatrix_InsertTranslation(effect->unk_4.x, effect->unk_4.y, effect->unk_4.z, 0);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(effect->unk_34, effect->unk_34, 1.0f, 1);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), 2);
            gSPDisplayList(POLY_XLU_DISP++, D_0600CEE8);
        }
    }
    CLOSE_DISPS(gfxCtx);
}
