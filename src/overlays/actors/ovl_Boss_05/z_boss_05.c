/*
 * File: z_boss_05.c
 * Overlay: ovl_Boss_05
 * Description: Bio Deku Baba
 */

#include "z_boss_05.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((Boss05*)thisx)

void Boss05_Init(Actor* thisx, PlayState* play);
void Boss05_Destroy(Actor* thisx, PlayState* play);
void Boss05_Update(Actor* thisx, PlayState* play);
void Boss05_Draw(Actor* thisx, PlayState* play);

void func_809EEDD0(Boss05* this, PlayState* play);
void func_809EEDE8(Boss05* this, PlayState* play);
void func_809EF9BC(Boss05* this, PlayState* play);
void func_809EFAB4(Boss05* this, PlayState* play);
void func_809F00CC(Boss05* this, PlayState* play);
void func_809F010C(Boss05* this, PlayState* play);
void func_809F01CC(Boss05* this, PlayState* play);
void func_809F0244(Boss05* this, PlayState* play);
void func_809F02D0(Boss05* this, PlayState* play);
void func_809F0374(Boss05* this, PlayState* play);
void func_809F0474(Boss05* this, PlayState* play);
void func_809F04C0(Boss05* this, PlayState* play);
void func_809F0538(Boss05* this, PlayState* arg1);
void func_809F0590(Boss05* this, PlayState* play);
void func_809F0650(Boss05* this, PlayState* arg1);
void func_809F06B8(Boss05* this, PlayState* play);
void func_809F0708(Boss05* this, PlayState* play);
void func_809F0780(Boss05* this, PlayState* play);
void func_809F0A0C(Boss05* this, PlayState* play);
void func_809F0A64(Boss05* this, PlayState* play);
void func_809F0ABC(Boss05* this, PlayState* play);
void func_809F0B0C(Boss05* this, PlayState* play);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809F1B2C[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1B74 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1B2C, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809F1B84[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1BA8 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1B84, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809F1BB8[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809F1BDC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_809F1BB8, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_809F1C00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(3, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(3, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(3, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
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
static DamageTable D_809F1C20 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x2),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit Boss_05_InitVars = {
    ACTOR_BOSS_05,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BOSS05,
    sizeof(Boss05),
    (ActorFunc)Boss05_Init,
    (ActorFunc)Boss05_Destroy,
    (ActorFunc)Boss05_Update,
    (ActorFunc)Boss05_Draw,
};

#endif

extern CollisionHeader D_809F1B00;
extern ColliderJntSphElementInit D_809F1B2C[2];
extern ColliderJntSphInit D_809F1B74;
extern ColliderJntSphElementInit D_809F1B84[1];
extern ColliderJntSphInit D_809F1BA8;
extern ColliderJntSphElementInit D_809F1BB8[1];
extern ColliderJntSphInit D_809F1BDC;
extern DamageTable D_809F1C00;
extern DamageTable D_809F1C20;

extern AnimationHeader D_060006A4;
extern AnimationHeader D_06000A5C;
extern AnimationHeader D_06000ABC;
extern FlexSkeletonHeader D_060024E0;
extern AnimationHeader D_06002F0C;
extern AnimationHeader D_06003448;
extern AnimatedMaterial D_06006240[];
extern FlexSkeletonHeader D_06006378;
extern AnimationHeader D_06006484;
extern AnimationHeader D_06006E50;
extern AnimationHeader D_06007488;
extern AnimationHeader D_06007908;

extern Color_RGBA8 D_809F1BEC;
extern Color_RGBA8 D_809F1BF0;
extern Vec3f D_809F1BF4;
// static Color_RGBA8 D_809F1BEC = { 0xAA, 0xFF, 0xFF, 0xFF };
// static Color_RGBA8 D_809F1BF0 = { 0xC8, 0xC8, 0xFF, 0xFF };
// static Vec3f D_809F1BF4 = { 0.0f, -1.0f, 0.0f };

void func_809EE4E0(Boss05* this, PlayState* play) {
    Vec3f sp8C;
    Vec3f sp80;
    s32 i;

    SoundSource_PlaySfxAtFixedWorldPos(play, &this->unk18C, 30, NA_SE_EV_ICE_BROKEN);
    for (i = 0; i < 8; i++) {
        sp80.x = randPlusMinusPoint5Scaled(7.0f);
        sp80.z = randPlusMinusPoint5Scaled(7.0f);
        sp80.y = Rand_ZeroFloat(6.0f) + 4.0f;
        sp8C.x = this->unk18C.x + sp80.x;
        sp8C.y = this->unk18C.y + sp80.y;
        sp8C.z = this->unk18C.z + sp80.z;
        EffectSsEnIce_Spawn(play, &sp8C, Rand_ZeroFloat(0.5f) + 0.7f, &sp80, &D_809F1BF4, &D_809F1BEC, &D_809F1BF0, 30);
    }
}

void func_809EE668(s32 elementIndex, ColliderJntSph* collider, Vec3f* pos) {
    collider->elements[elementIndex].dim.worldSphere.center.x = (s32)pos->x;
    collider->elements[elementIndex].dim.worldSphere.center.y = (s32)pos->y;
    collider->elements[elementIndex].dim.worldSphere.center.z = (s32)pos->z;

    collider->elements[elementIndex].dim.worldSphere.radius =
        (s32)(collider->elements[elementIndex].dim.modelSphere.radius * collider->elements[elementIndex].dim.scale);
}

void Boss05_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = THIS;
    CollisionHeader* colHeader = NULL;

    this->dyna.actor.targetMode = 3;
    this->dyna.actor.colChkInfo.mass = MASS_HEAVY;
    this->dyna.actor.colChkInfo.health = 2;
    this->unk160 = (s32)Rand_ZeroFloat(1000.0f);
    this->unk35C = 1.0f;
    this->dyna.actor.gravity = -0.3f;

    Actor_SetScale(&this->dyna.actor, 0.01f);

    if ((this->dyna.actor.params == 0) || (this->dyna.actor.params == 1)) {
        if (this->dyna.actor.world.rot.z == 0) {
            this->dyna.actor.world.rot.z = 0;
        }

        this->dyna.actor.shape.rot.z = 0;
        this->unk168 = this->dyna.actor.world.rot.z;
        this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z;
        this->dyna.actor.colChkInfo.damageTable = &D_809F1C00;

        DynaPolyActor_Init(&this->dyna, 0);
        CollisionHeader_GetVirtual(&D_809F1B00, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
        func_809EEDD0(this, play);

        SkelAnime_InitFlex(play, &this->unk268, &D_060024E0, &D_06000ABC, this->unk2AC, this->unk2E8, 10);
        SkelAnime_InitFlex(play, &this->unk3C8, &D_06006378, &D_06006484, this->unk40C, this->unk484, 20);
        this->unk4FC = Animation_GetLastFrame(&D_06006484);

        Collider_InitAndSetJntSph(play, &this->unk1C8, &this->dyna.actor, &D_809F1B74, this->unk1E8);
        Collider_InitAndSetJntSph(play, &this->unk368, &this->dyna.actor, &D_809F1BA8, this->unk388);

        if (Flags_GetClear(play, play->roomCtx.currRoom.num)) {
            this->dyna.actor.params = 2;
            this->actionFunc = func_809EF9BC;
            this->dyna.actor.flags &= ~ACTOR_FLAG_1;
            func_800BC154(play, &play->actorCtx, &this->dyna.actor, ACTORCAT_BG);
        }
    } else if (this->dyna.actor.params == 2) {
        this->actionFunc = func_809EF9BC;

        CollisionHeader_GetVirtual(&D_809F1B00, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

        SkelAnime_InitFlex(play, &this->unk268, &D_060024E0, &D_06000ABC, this->unk2AC, this->unk2E8, 10);
        this->dyna.actor.flags &= ~ACTOR_FLAG_1;
        func_800BC154(play, &play->actorCtx, &this->dyna.actor, ACTORCAT_BG);
    } else if (this->dyna.actor.params == 3) {
        this->actionFunc = func_809EFAB4;
        this->unk198 = 1.0f;

        SkelAnime_InitFlex(play, &this->unk268, &D_060024E0, &D_06000ABC, this->unk2AC, this->unk2E8, 10);
        SkelAnime_InitFlex(play, &this->unk3C8, &D_06006378, &D_06006484, this->unk40C, this->unk484, 0x14);
        this->unk4FC = Animation_GetLastFrame(&D_06006484);

        Collider_InitAndSetJntSph(play, &this->unk1C8, &this->dyna.actor, &D_809F1B74, this->unk1E8);
        Collider_InitAndSetJntSph(play, &this->unk368, &this->dyna.actor, &D_809F1BA8, this->unk388);

        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
        this->dyna.actor.colChkInfo.damageTable = &D_809F1C00;
    } else if (this->dyna.actor.params == 4) {
        func_809F00CC(this, play);
        this->dyna.actor.colChkInfo.mass = 90;

        SkelAnime_InitFlex(play, &this->unk3C8, &D_06006378, &D_06006484, this->unk40C, this->unk484, 20);

        Collider_InitAndSetJntSph(play, &this->unk368, &this->dyna.actor, &D_809F1BDC, this->unk388);

        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
        this->dyna.actor.colChkInfo.damageTable = &D_809F1C20;
        this->dyna.actor.flags |= ACTOR_FLAG_10 | ACTOR_FLAG_20;
    } else if (this->dyna.actor.params >= 10) {
        SkelAnime_InitFlex(play, &this->unk3C8, &D_06006378, &D_06006484, this->unk40C, this->unk484, 20);

        this->dyna.actor.gravity = 0.0f;
        this->dyna.actor.world.rot.y = (s32)Rand_ZeroFloat(0x8000);
        this->dyna.actor.speedXZ = Rand_ZeroFloat(3.0f) + 3.0f;
        this->dyna.actor.velocity.y = Rand_ZeroFloat(1.5f) + 1.5f;

        this->unk500 = (s32)randPlusMinusPoint5Scaled(700.0f);
        this->unk502 = (s32)randPlusMinusPoint5Scaled(1500.0f);
        this->unk162[0] = (s32)(Rand_ZeroFloat(30.0f) + 50.0f);

        this->dyna.actor.flags &= ~ACTOR_FLAG_1;
        this->actionFunc = func_809F0B0C;
    }
}

void Boss05_Destroy(Actor* thisx, PlayState* play) {
    Boss05* this = THIS;

    if ((this->dyna.actor.params == 2) || (this->dyna.actor.params == 0) || (this->dyna.actor.params == 1)) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

s32 func_809EECBC(Boss05* this, PlayState* play) {
    if (this->unk16C == 0) {
        s32 var_v0 = 0;
        ColliderJntSphElement* var_v1 = &this->unk1C8.elements[0];

        while (true) {
            var_v0 += 0x40;

            if (var_v1->info.bumperFlags & BUMP_HIT) {
                switch (this->dyna.actor.colChkInfo.damageEffect) {
                    case 2:
                        return 11;
                    case 3:
                        return 20;
                    case 4:
                        return 30;
                    default:
                        return 10;
                }
            }
            var_v1++;

            if (var_v0 == 0x80) {
                if (this->unk368.elements[0].info.bumperFlags & BUMP_HIT) {
                    u8 damage = this->dyna.actor.colChkInfo.damage;
                    this->dyna.actor.colChkInfo.health -= damage;
                    if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
                        Enemy_StartFinishingBlow(play, &this->dyna.actor);
                        return 2;
                    } else {
                        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
                        this->unk16C = 15;
                        this->unk15C = 0;
                        this->unk162[0] = 30;
                        return 0;
                    }
                }

                break;
            }
        }
    }

    return 0;
}

void func_809EEDD0(Boss05* this, PlayState* play) {
    this->actionFunc = func_809EEDE8;
}

extern Vec3s D_809F1C60[];
extern Vec3s D_809F1C8C[];
// Vec3s D_809F1C60[7] = {
//     { 0x3200, 0, 0 },
//     { -0x1E00, 0, 0 },
//     { -0x1400, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
// };

// Vec3s D_809F1C8C[7] = {
//     { -0x3200, 0, 0 },
//     { 0, 0, 0 },
//     { 0x1E00, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
// };

// The big one
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EEDE8.s")
// struct _m2c_stack_func_809EEDE8 {
//     /* 0x000 */ char pad0[0x5C];
//     /* 0x05C */ s16 *sp5C;
//     /* 0x060 */ s16 *sp60;
//     /* 0x064 */ char pad64[8];                      /* maybe part of sp60[3]? */
//     /* 0x06C */ Vec3s *sp6C;
//     /* 0x070 */ f32 sp70;
//     /* 0x074 */ s32 sp74;
//     /* 0x078 */ char pad78[8];                      /* maybe part of sp74[3]? */
//     /* 0x080 */ f32 sp80;
//     /* 0x084 */ char pad84[0x10];                   /* maybe part of sp80[5]? */
//     /* 0x094 */ Vec3f sp94;
//     /* 0x0A0 */ char padA0[4];
//     /* 0x0A4 */ f32 spA4;
//     /* 0x0A8 */ char padA8[0xC];                    /* maybe part of spA4[4]? */
//     /* 0x0B4 */ s32 spB4;
//     /* 0x0B8 */ s32 spB8;
//     /* 0x0BC */ s32 spBC;
//     /* 0x0C0 */ s32 spC0;
//     /* 0x0C4 */ s32 spC4;
//     /* 0x0C8 */ s32 spC8;
//     /* 0x0CC */ s32 spCC;
//     /* 0x0D0 */ s32 spD0;
//     /* 0x0D4 */ s32 spD4;
//     /* 0x0D8 */ Vec3s spD8;
//     /* 0x0DE */ char padDE[0x25];                   /* maybe part of spD8[7]? */
//     /* 0x103 */ u8 sp103;
//     /* 0x104 */ char pad104[4];                     /* maybe part of sp103[5]? */
//     /* 0x108 */ Player *sp108;
//     /* 0x10C */ char pad10C[4];
// };                                                  /* size = 0x110 */

// Vec3s D_809F1C60[7] = {
//     { 0x3200, 0, 0 },
//     { -0x1E00, 0, 0 },
//     { -0x1400, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
// };
// Vec3s D_809F1C8C[7] = {
//     { -0x3200, 0, 0 },
//     { 0, 0, 0 },
//     { 0x1E00, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
// };

extern Vec3s D_809F1C60[];
extern Vec3s D_809F1C8C[];

void func_809EEDE8(Boss05 *this, PlayState *play) {
    s32 pad;
    
    Player *sp108;
    
    s32 pad1;
    
    u8 sp103;
    Vec3s spD8[7];
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;

    s32 pad2;
    
    f32 spA4;
    Vec3f sp94;
    // f32 sp80;
    // s32 sp74;
    // f32 sp70;
    // Vec3s *sp6C;
    // s16 *sp60;
    // s16 *sp5C;
    // ? *temp_t5;
    // ? temp_t2_2;
    // ? temp_t4;
    // ? temp_t5_4;
    // Boss05 *temp_v0_6;
    // Boss05 *temp_v0_7;
    // Player *temp_v1;
    // ActorContext *temp_s0_2;
    // CollisionCheckContext *temp_s0_3;
    // CollisionCheckContext *temp_s0_4;
    // SkelAnime *temp_s0;
    // Vec3s *var_s1;
    // f32 *temp_s1;
    // f32 temp_ft4;
    f32 var_fv1;
    // s16 var_s4;
    // s16 var_s5;
    s16 var_s6;
    s16 var_s7;
    // s32 temp_lo;
    // s32 temp_v0_5;
    // s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s3;
    // s32 var_s3_2;
    s32 var_s4_2;
    s32 var_v1;
    // u8 temp_v0;
    // u8 temp_v0_2;
    // void *temp_t1;
    // void *temp_t1_2;
    // void *temp_t2;
    // void *temp_t2_3;
    // void *temp_t2_4;
    // void *temp_t3;
    // void *temp_t3_2;
    // void *temp_t5_2;
    // void *temp_t5_3;
    // void *temp_t6;
    // void *temp_t6_2;
    // void *temp_t7;
    // void *temp_t8;
    // void *temp_t8_2;
    // void *temp_t9;
    // void *temp_t9_2;
    // void *temp_t9_3;
    // Vec3s *temp_v0_3;
    // Vec3s *temp_v0_4;

    
    
    sp108 = GET_PLAYER(play);
    sp103 = 0;
    // var_s3 = 0;
    // temp_v0 = this->unk174;
    this->dyna.actor.hintId = 8;
    // var_s0 = 0;
    // var_s1 = spD8;
    if (this->unk174 == 0) {
        spD4 = 0x3E8;
        spD0 = 0x3E80;
        spCC = 0x7D0;
        spC8 = 0x5DC;
        spC4 = 0x1770;
        spC0 = 0xBB8;
        spBC = 0x514;
        spB8 = 0x5208;
        spB4 = 0xDAC;
        var_s6 = 0xA;
        var_s7 = 0x300;
        if (this->unk16C != 0) {
            spD4 = 0x1B58;
            spCC = 0x1770;
            spC0 = 0x1770;
            spBC = 0x1C84;
            spB4 = 0x1964;
            var_s6 = 1;
            var_s7 = 0x1000;
        }
    } else {
        if (this->unk174 == 3) {
            spD4 = 0x1B58;
            spD0 = 0x3E80;
            spCC = 0x1388;
            spC8 = 0x5DC;
            spC4 = 0x2328;
            spC0 = 0x1388;
            spBC = 0x1C84;
            spB8 = 0x5208;
            spB4 = 0x157C;
            var_s6 = 1;
            var_s7 = 0x1000;
        } else {
            var_s6 = 0;
            var_s7 = 0;
            spB4 = 0;
            spB8 = 0;
            spBC = 0;
            spC0 = 0;
            spC4 = 0;
            spC8 = 0;
            spCC = 0;
            spD0 = 0;
            spD4 = 0;
        }
    }

    for (var_s3 = 0; var_s3 < 7; var_s3++) {
        if ((this->unk174 == 0) || (this->unk174 == 3)) {
            if (var_s3 < 3) {
                spD8[var_s3].y = 0;
                spD8[var_s3].x = (s32) (Math_SinS((this->unk160 * spD4) + (var_s3 * spD0)) * spCC);
            } else {
                spD8[var_s3].x = 0;
                spD8[var_s3].y = (s32) (Math_SinS((this->unk160 * spC8) + (var_s3 * spC4)) * spC0);
            }

            if ((var_s3 == 4) || (var_s3 == 6)) {
                spD8[var_s3].z = (s32) (2.0f * (Math_SinS((this->unk160 * spBC) + var_s3 * spB8) * spB4));
            } else {
                spD8[var_s3].z = (s32) (Math_SinS((this->unk160 * spBC) + var_s3 * spB8) * spB4);
            }
        } else if (this->unk174 == 1) {
            var_s6 = 5;
            var_s7 = 0x1000;
            spD8[var_s3].x = D_809F1C60[var_s3].x;
            spD8[var_s3].y = D_809F1C60[var_s3].y;
            spD8[var_s3].z = D_809F1C60[var_s3].z;
        } else if (this->unk174 == 2) {
            var_s6 = 1;
            var_s7 = 0x2000;
            spD8[var_s3].x = D_809F1C8C[var_s3].x;
            spD8[var_s3].y = D_809F1C8C[var_s3].y;
            spD8[var_s3].z = D_809F1C8C[var_s3].z;
        }

        Math_ApproachS(&this->unk19E[var_s3].x, spD8[var_s3].x, var_s6, var_s7);
        Math_ApproachS(&this->unk19E[var_s3].y, spD8[var_s3].y, var_s6, var_s7);
        Math_ApproachS(&this->unk19E[var_s3].z, spD8[var_s3].z, var_s6, var_s7);

    }

    spA4 = (sp108->actor.world.pos.y - this->dyna.actor.world.pos.y) + 10.0f;
    if (spA4 < 0.0f) {
        Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, var_s6, var_s7);
    }

    SkelAnime_Update(&this->unk3C8);
    Math_ApproachF(&this->unk35C, 1.0f, 0.1f, 0.1f);
    if (this->unk15C != 0xA) {
        Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 0x14, 0x800);
    }

    switch (this->unk15C) {                         /* irregular */
    case 0:
        this->unk174 = 0;
        this->unk3C8.playSpeed = 1.0f;
        if (spA4 < 0.0f) {
            if (sp108->actor.speedXZ > 10.0f) {
                var_fv1 = 220.0f;
            } else {
                var_fv1 = 150.0f;
            }
            if ((this->unk162[0] == 0) && (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= var_fv1)) {
                this->unk15C = 1;
                this->unk162[0] = 0xA;
            }
            this->unk15E = 0;
            // goto block_42;
        } else {
            
            sp103 = 1;
            if (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= 40.0f) {
                this->unk15E++;
                if (this->unk15E > 0x1E) {
                    this->unk15C = 0xA;
                    this->unk162[0] = 0x1E;
                    Actor_PlaySfxAtPos(&this->dyna.actor, 0x3861U);
                }
            } else {
    // block_42:
                this->unk15E = 0;
            }
        }
        if (!(this->unk160 & 3) && (Rand_ZeroOne() < 0.5f)) {
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
        }
        break;

    case 10:
        if (!(this->unk160 & 1)) {
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
        }
        this->unk19C = (this->unk162[0] & 1) << 9;
        this->unk174 = 3;
        this->unk3C8.playSpeed = 4.0f;
        Math_ApproachS(&this->dyna.actor.shape.rot.x, -0x8000, 2, 0x2000);
        Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, 2, 0x2000);
        if (this->unk162[0] == 0) {
            this->unk15E = 0;
            this->unk15C = 0;
            this->unk162[0] = 0x64;
        }
        if (this->unk162[0] == 0x1B) {
            Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
            sp94.y += 40.0f;
            EffectSsGSplash_Spawn(play, &sp94, NULL, NULL, 1, 0x7D0);
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x2808U);
        }
        break;

    case 1:
        if (Animation_OnFrame(&this->unk3C8, this->unk4FC)) {
            this->unk3C8.playSpeed = 0.0f;
        }
        this->unk174 = 1;
        if (this->unk162[0] == 0) {
            this->unk15C = 2;
            this->unk162[0] = 0x14;
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x3861U);
        }
        break;

    case 2:
        if (!(this->unk160 & 1)) {
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
        }
        this->unk19C = (this->unk162[0] & 1) << 9;
        this->unk3C8.playSpeed = 4.0f;
        Math_ApproachF(&this->unk35C, 1.5f, 1.0f, 0.7f);
        this->unk174 = 2;
        if (this->unk162[0] == 0) {
            this->unk15C = 0;
            this->unk162[0] = 0x1E;
        }
        break;
    }

    var_s4_2 = func_809EECBC(this, play);
    if ((var_s4_2 != 0) || (this->unk168 == 1)) {
        this->dyna.actor.params = 2;
        this->actionFunc = func_809EF9BC;
        this->dyna.actor.flags &= ~1;
        func_800BC154(play, &play->actorCtx, &this->dyna.actor, 1);
        if (this->unk168 != 0) {
            var_s4_2 = 0xA;
        }
        if (var_s4_2 >= 0xA) {
            Boss05 *temp_v0_6 = (Boss05*)Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, 0x12D, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 3);
            if (temp_v0_6 != NULL) {
                Player* temp_v1 = GET_PLAYER(play);
                if (&this->dyna.actor == temp_v1->targetActor) {
                    temp_v1->targetActor = &temp_v0_6->dyna.actor;
                    play->actorCtx.targetContext.arrowPointedActor = &temp_v0_6->dyna.actor;
                    play->actorCtx.targetContext.targetedActor = &temp_v0_6->dyna.actor;
                }

                for (var_s0_2 = 0; var_s0_2 < 10; var_s0_2++) {
                    temp_v0_6->unk268.jointTable[var_s0_2] = this->unk268.jointTable[var_s0_2];
                }

                for (var_s0_2 = 0; var_s0_2 < 20; var_s0_2++) {
                    temp_v0_6->unk3C8.jointTable[var_s0_2] = this->unk3C8.jointTable[var_s0_2];
                }

                Actor_PlaySfxAtPos(&this->dyna.actor, 0x381EU);
                if (var_s4_2 >= 0xB) {
                    temp_v0_6->unk188 = var_s4_2 - 0xA;
                }
            }
        } else if (var_s4_2 == 2) {
            for (var_s3 = 0; var_s3 < 2; var_s3++) {
                Boss05 *temp_v0_6 = (Boss05*)Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, 0x12D, this->unk324.x, this->unk324.y, this->unk324.z, this->unk330.x, this->unk330.y, this->unk330.z, var_s3 + 0xA);
                if (temp_v0_6 != NULL) {
                    
                    for (var_v1 = 0; var_v1 < 20; var_v1++) {
                        temp_v0_6->unk3C8.jointTable[var_v1] = this->unk3C8.jointTable[var_v1];
                    }

                    temp_v0_6->unk162[0] = (s32) (Rand_ZeroFloat(20.0f) + 20.0f);
                }
            }
            Actor_PlaySfxAtPos(&this->dyna.actor, 0x381FU);
        }
        
    }

    if (sp103 == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk1C8.base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk368.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk1C8.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk368.base);
}
// void func_809EEDE8(Boss05 *this, PlayState *play) {
//     Player *sp108;
//     u8 sp103;
//     Vec3s spD8;
//     s32 spD4;
//     s32 spD0;
//     s32 spCC;
//     s32 spC8;
//     s32 spC4;
//     s32 spC0;
//     s32 spBC;
//     s32 spB8;
//     s32 spB4;
//     f32 spA4;
//     Vec3f sp94;
//     f32 sp80;
//     s32 sp74;
//     f32 sp70;
//     Vec3s *sp6C;
//     s16 *sp60;
//     s16 *sp5C;
//     // ? *temp_t5;
//     // ? temp_t2_2;
//     // ? temp_t4;
//     // ? temp_t5_4;
//     Boss05 *temp_v0_6;
//     Boss05 *temp_v0_7;
//     Player *temp_v1;
//     ActorContext *temp_s0_2;
//     // CollisionCheckContext *temp_s0_3;
//     // CollisionCheckContext *temp_s0_4;
//     SkelAnime *temp_s0;
//     Vec3s *var_s1;
//     // f32 *temp_s1;
//     f32 temp_ft4;
//     f32 var_fv1;
//     s16 var_s4;
//     s16 var_s5;
//     s16 var_s6;
//     s16 var_s7;
//     s32 temp_lo;
//     s32 temp_v0_5;
//     s32 var_s0;
//     s32 var_s0_2;
//     s32 var_s0_3;
//     s32 var_s3;
//     s32 var_s3_2;
//     s32 var_s4_2;
//     s32 var_v1;
//     u8 temp_v0;
//     u8 temp_v0_2;
//     // void *temp_t1;
//     // void *temp_t1_2;
//     // void *temp_t2;
//     // void *temp_t2_3;
//     // void *temp_t2_4;
//     // void *temp_t3;
//     // void *temp_t3_2;
//     // void *temp_t5_2;
//     // void *temp_t5_3;
//     // void *temp_t6;
//     // void *temp_t6_2;
//     // void *temp_t7;
//     // void *temp_t8;
//     // void *temp_t8_2;
//     // void *temp_t9;
//     // void *temp_t9_2;
//     // void *temp_t9_3;
//     Vec3s *temp_v0_3;
//     Vec3s *temp_v0_4;

//     sp103 = 0;
//     var_s3 = 0;
//     sp108 = GET_PLAYER(play);
//     temp_v0 = this->unk174;
//     this->dyna.actor.hintId = 8;
//     var_s0 = 0;
//     var_s1 = &spD8;
//     if (temp_v0 == 0) {
//         spD4 = 0x3E8;
//         spD0 = 0x3E80;
//         spCC = 0x7D0;
//         spC8 = 0x5DC;
//         spC4 = 0x1770;
//         spC0 = 0xBB8;
//         spBC = 0x514;
//         spB8 = 0x5208;
//         spB4 = 0xDAC;
//         var_s6 = 0xA;
//         var_s7 = 0x300;
//         if (this->unk16C != 0) {
//             spD4 = 0x1B58;
//             spCC = 0x1770;
//             spC0 = 0x1770;
//             spBC = 0x1C84;
//             spB4 = 0x1964;
//             var_s6 = 1;
//             var_s7 = 0x1000;
//         }
//     } else {
//         var_s7 = 0;
//         if (temp_v0 == 3) {
//             spD4 = 0x1B58;
//             spD0 = 0x3E80;
//             spCC = 0x1388;
//             spC8 = 0x5DC;
//             spC4 = 0x2328;
//             spC0 = 0x1388;
//             spBC = 0x1C84;
//             spB8 = 0x5208;
//             spB4 = 0x157C;
//             var_s6 = 1;
//             var_s7 = 0x1000;
//         } else {
//             var_s6 = 0;
//             spB4 = 0;
//             spB8 = 0;
//             spBC = 0;
//             spC0 = 0;
//             spC4 = 0;
//             spC8 = 0;
//             spCC = 0;
//             spD0 = 0;
//             spD4 = 0;
//         }
//     }
//     sp5C = &this->unk19E[0].z;
//     sp60 = &this->unk19E[0].y;
//     sp6C = this->unk19E;
//     do {
//         // temp_v0_2 = this->unk174;
//         if ((this->unk174 == 0) || (this->unk174 == 3)) {
//             temp_lo = var_s3 * spB8;
//             var_s5 = var_s7;
//             var_s4 = var_s6;
//             sp70 = (f32) spB4;
//             if (var_s3 < 3) {
//                 var_s1->y = 0;
//                 sp74 = temp_lo;
//                 sp80 = (f32) spCC;
//                 var_s1->x = (s32) (Math_SinS((this->unk160 * spD4) + (var_s3 * spD0)) * sp80);
//             } else {
//                 var_s1->x = 0;
//                 sp74 = temp_lo;
//                 sp80 = (f32) spC0;
//                 var_s1->y = (s32) (Math_SinS((s16) ((this->unk160 * spC8) + (var_s3 * spC4))) * sp80);
//             }
//             if ((var_s3 == 4) || (var_s3 == 6)) {
//                 var_s1->z = (s32) (2.0f * (Math_SinS((this->unk160 * spBC) + temp_lo) * sp70));
//             } else {
//                 var_s1->z = (s32) (Math_SinS((this->unk160 * spBC) + temp_lo) * sp70);
//             }
//         } else {
//             if (this->unk174 == 1) {
//                 temp_v0_3 = var_s0 + D_809F1C60;
//                 var_s6 = 5;
//                 var_s7 = 0x1000;
//                 var_s1->x = temp_v0_3->x;
//                 var_s1->y = temp_v0_3->y;
//                 var_s1->z = temp_v0_3->z;
//             } else if (this->unk174 == 2) {
//                 temp_v0_4 = var_s0 + D_809F1C8C;
//                 var_s6 = 1;
//                 var_s7 = 0x2000;
//                 var_s1->x = temp_v0_4->x;
//                 var_s1->y = temp_v0_4->y;
//                 var_s1->z = temp_v0_4->z;
//             }
//             var_s5 = var_s7;
//             var_s4 = var_s6;
//         }
//         Math_ApproachS(&sp6C->x, var_s1->x, var_s4, var_s5);
//         Math_ApproachS(sp60, var_s1->y, var_s4, var_s5);
//         Math_ApproachS(sp5C, var_s1->z, var_s4, var_s5);
//         var_s3 += 1;
//         sp5C += 6;
//         sp60 += 6;
//         sp6C += 6;
//         var_s0 += 6;
//         var_s1 += 6;
//     } while (var_s3 < 7);


//     temp_ft4 = (sp108->actor.world.pos.y - this->dyna.actor.world.pos.y) + 10.0f;
//     spA4 = temp_ft4;
//     if (temp_ft4 < 0.0f) {
//         Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, var_s4, var_s5);
//     }
//     // temp_s0 = &this->unk3C8;
//     SkelAnime_Update(&this->unk3C8);
//     // temp_s1 = &this->unk35C;
//     Math_ApproachF(&this->unk35C, 1.0f, 0.1f, 0.1f);
//     if (this->unk15C != 0xA) {
//         Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 0x14, 0x800);
//     }

//     switch (this->unk15C) {                         /* irregular */
//     case 0:
//         this->unk174 = 0;
//         this->unk3C8.playSpeed = 1.0f;
//         if (spA4 < 0.0f) {
//             if (sp108->actor.speedXZ > 10.0f) {
//                 var_fv1 = 220.0f;
//             } else {
//                 var_fv1 = 150.0f;
//             }
//             if ((this->unk162[0] == 0) && (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= var_fv1)) {
//                 this->unk15C = 1;
//                 this->unk162[0] = 0xA;
//             }
//             goto block_42;
//         }
//         sp103 = 1;
//         if (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= 40.0f) {
//             this->unk15E++;
//             if (this->unk15E >= 0x1F) {
//                 this->unk15C = 0xA;
//                 this->unk162[0] = 0x1E;
//                 Actor_PlaySfxAtPos(&this->dyna.actor, 0x3861U);
//             }
//         } else {
// block_42:
//             this->unk15E = 0;
//         }
//         if (!(this->unk160 & 3) && (Rand_ZeroOne() < 0.5f)) {
//             Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
//         }
//         break;
//     case 10:
//         if (!(this->unk160 & 1)) {
//             Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
//         }
//         this->unk19C = (this->unk162[0] & 1) << 9;
//         this->unk174 = 3;
//         this->unk3C8.playSpeed = 4.0f;
//         Math_ApproachS(&this->dyna.actor.shape.rot.x, -0x8000, 2, 0x2000);
//         Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, 2, 0x2000);
//         if (this->unk162[0] == 0) {
//             this->unk162[0] = 0x64;
//             this->unk15E = 0;
//             this->unk15C = 0;
//         }
//         if (this->unk162[0] == 0x1B) {
//             Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
//             sp94.y += 40.0f;
//             EffectSsGSplash_Spawn(play, &sp94, NULL, NULL, (s16) 1, (s16) 0x7D0);
//             Actor_PlaySfxAtPos(&this->dyna.actor, 0x2808U);
//         }
//         break;
//     case 1:
//         if (Animation_OnFrame(temp_s0, this->unk4FC)) {
//             this->unk3C8.playSpeed = 0.0f;
//         }
//         this->unk174 = 1;
//         if (this->unk162[0] == 0) {
//             this->unk15C = 2;
//             this->unk162[0] = 0x14;
//             Actor_PlaySfxAtPos(&this->dyna.actor, 0x3861U);
//         }
//         break;
//     case 2:
//         if (!(this->unk160 & 1)) {
//             Actor_PlaySfxAtPos(&this->dyna.actor, 0x3860U);
//         }
//         this->unk19C = (this->unk162[0] & 1) << 9;
//         this->unk3C8.playSpeed = 4.0f;
//         Math_ApproachF(&this->unk35C, 1.5f, 1.0f, 0.7f);
//         this->unk174 = 2;
//         if (this->unk162[0] == 0) {
//             this->unk15C = 0;
//             this->unk162[0] = 0x1E;
//         }
//         break;
//     }

//     temp_v0_5 = func_809EECBC(this, play);
//     var_s4_2 = temp_v0_5;
//     if ((temp_v0_5 != 0) || (this->unk168 == 1)) {
//         this->dyna.actor.params = 2;
//         this->actionFunc = func_809EF9BC;
//         this->dyna.actor.flags &= ~1;
//         temp_s0_2 = &play->actorCtx;
//         func_800BC154(play, temp_s0_2, &this->dyna.actor, 1);
//         if (this->unk168 != 0) {
//             var_s4_2 = 0xA;
//         }
//         if (var_s4_2 >= 0xA) {
//             temp_v0_6 = (Boss05*)Actor_SpawnAsChild(temp_s0_2, &this->dyna.actor, play, 0x12D, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 3);
//             if (temp_v0_6 != NULL) {
//                 var_s0_2 = 0;
//                 temp_v1 = GET_PLAYER(play);
//                 if (&this->dyna.actor == temp_v1->targetActor) {
//                     temp_v1->targetActor = temp_v0_6;
//                     play->actorCtx.targetContext.arrowPointedActor = temp_v0_6;
//                     play->actorCtx.targetContext.targetedActor = temp_v0_6;
//                 }

//                 // do {
//                 //     temp_t5 = this->unk268.jointTable + var_s0_2;
//                 //     temp_t4 = (unaligned s32) temp_t5->unk0;
//                 //     temp_t1 = temp_v0_6->unk288 + var_s0_2;
//                 //     var_s0_2 += 6;
//                 //     temp_t1->unk0 = (unaligned s32) temp_t4;
//                 //     temp_t1->unk4 = (u16) temp_t5->unk4;
//                 // } while (var_s0_2 < 0x3C);

//                 for (var_s0_2 = 0; var_s0_2 < 10; var_s0_2++) {
//                     temp_v0_6->unk268.jointTable[var_s0_2] = this->unk268.jointTable[var_s0_2];
//                 }

//                 for (var_s0_3 = 0; var_s0_3 < 20; var_s0_3++) {
//                     temp_v0_6->unk3C8.jointTable[var_s0_3] = this->unk3C8.jointTable[var_s0_3];
//                 }

//                 // var_s0_3 = 0;
//                 // do {
//                 //     temp_t9 = this->unk3C8.jointTable + var_s0_3;
//                 //     temp_t7 = temp_v0_6->unk3E8 + var_s0_3;
//                 //     temp_t7->unk0 = (unaligned s32) temp_t9->unk0;
//                 //     temp_t7->unk4 = (u16) temp_t9->unk4;
//                 //     temp_t6 = this->unk3C8.jointTable + var_s0_3;
//                 //     temp_t3 = temp_v0_6->unk3E8 + var_s0_3;
//                 //     temp_t3->unk6 = (unaligned s32) temp_t6->unk6;
//                 //     temp_t3->unkA = (u16) temp_t6->unkA;
//                 //     temp_t5_2 = this->unk3C8.jointTable + var_s0_3;
//                 //     temp_t2 = temp_v0_6->unk3E8 + var_s0_3;
//                 //     temp_t2->unkC = (unaligned s32) temp_t5_2->unkC;
//                 //     temp_t2->unk10 = (u16) temp_t5_2->unk10;
//                 //     temp_t9_2 = this->unk3C8.jointTable + var_s0_3;
//                 //     temp_t2_2 = (unaligned s32) temp_t9_2->unk12;
//                 //     temp_t8 = temp_v0_6->unk3E8 + var_s0_3;
//                 //     var_s0_3 += 0x18;
//                 //     temp_t8->unk12 = (unaligned s32) temp_t2_2;
//                 //     temp_t8->unk16 = (u16) temp_t9_2->unk16;
//                 // } while (var_s0_3 != 0x78);


//                 Actor_PlaySfxAtPos(&this->dyna.actor, 0x381EU);
//                 if (var_s4_2 >= 0xB) {
//                     temp_v0_6->unk188 = (s8) (var_s4_2 - 0xA);
//                 }
//             }
//         } else {
//             var_s3_2 = 0;
//             if (var_s4_2 == 2) {
//                 for (var_s3_2 = 0; var_s3_2 < 2; var_s3_2++) {
//                     temp_v0_7 = (Boss05*)Actor_SpawnAsChild(temp_s0_2, &this->dyna.actor, play, 0x12D, this->unk324.x, this->unk324.y, this->unk324.z, this->unk330.x, this->unk330.y, this->unk330.z, var_s3_2 + 0xA);
//                     if (temp_v0_7 != NULL) {
                        
//                         for (var_v1 = 0; var_v1 < 20; var_v1++) {
//                             temp_v0_6->unk3C8.jointTable[var_v1] = this->unk3C8.jointTable[var_v1];
//                         }

//                         temp_v0_7->unk162[0] = (s32) (Rand_ZeroFloat(20.0f) + 20.0f);
//                     }
//                 }
//                 // do {
//                 //     temp_v0_7 = (Boss05*)Actor_SpawnAsChild(temp_s0_2, &this->dyna.actor, play, 0x12D, this->unk324.x, this->unk324.y, this->unk324.z, this->unk330.x, this->unk330.y, this->unk330.z, var_s3_2 + 0xA);
//                 //     if (temp_v0_7 != NULL) {
                        
//                 //         for (var_v1 = 0; var_v1 < 20; var_v1++) {
//                 //             temp_v0_6->unk3C8.jointTable[var_v1] = this->unk3C8.jointTable[var_v1];
//                 //         }

//                 //         // var_v1 = 0;
//                 //         // do {
//                 //         //     temp_t2_3 = this->unk3C8.jointTable + var_v1;
//                 //         //     temp_t9_3 = temp_v0_7->unk3E8 + var_v1;
//                 //         //     temp_t9_3->unk0 = (unaligned s32) temp_t2_3->unk0;
//                 //         //     temp_t9_3->unk4 = (u16) temp_t2_3->unk4;
//                 //         //     temp_t8_2 = this->unk3C8.jointTable + var_v1;
//                 //         //     temp_t6_2 = temp_v0_7->unk3E8 + var_v1;
//                 //         //     temp_t6_2->unk6 = (unaligned s32) temp_t8_2->unk6;
//                 //         //     temp_t6_2->unkA = (u16) temp_t8_2->unkA;
//                 //         //     temp_t3_2 = this->unk3C8.jointTable + var_v1;
//                 //         //     temp_t5_3 = temp_v0_7->unk3E8 + var_v1;
//                 //         //     temp_t5_3->unkC = (unaligned s32) temp_t3_2->unkC;
//                 //         //     temp_t5_3->unk10 = (u16) temp_t3_2->unk10;
//                 //         //     temp_t2_4 = this->unk3C8.jointTable + var_v1;
//                 //         //     temp_t5_4 = (unaligned s32) temp_t2_4->unk12;
//                 //         //     temp_t1_2 = temp_v0_7->unk3E8 + var_v1;
//                 //         //     var_v1 += 0x18;
//                 //         //     temp_t1_2->unk12 = (unaligned s32) temp_t5_4;
//                 //         //     temp_t1_2->unk16 = (u16) temp_t2_4->unk16;
//                 //         // } while (var_v1 != 0x78);

//                 //         temp_v0_7->unk162[0] = (s32) (Rand_ZeroFloat(20.0f) + 20.0f);
//                 //     }
//                 //     var_s3_2 += 1;
//                 // } while (var_s3_2 != 2);

//                 Actor_PlaySfxAtPos(&this->dyna.actor, 0x381FU);
//             }
//         }
//     }

//     if (sp103 == 0) {
//         CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk1C8.base);
//         CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk368.base);
//     }

//     CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk1C8.base);
//     CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk368.base);
// }


void func_809EF9BC(Boss05* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_fv0 = sqrtf(this->dyna.actor.xyzDistToPlayerSq);
    s16 var_a1;

    if ((temp_fv0 < 50.0f) && (player->actor.bgCheckFlags & 1)) {
        var_a1 = (s32)(temp_fv0 * 80.0f);
        var_a1 = CLAMP_MAX(var_a1, 0x7D0);
        // if (var_a1 > 0x7D0) {
        //     var_a1 = 0x7D0;
        // }
        Math_ApproachS(&this->unk178, var_a1, 0x14, 0x7D0);
        Math_ApproachS(&this->unk176, this->dyna.actor.yawTowardsPlayer, 0x14, 0xFA0);
        if (!(this->unk160 & 0xF)) {
            EffectSsGRipple_Spawn(play, &this->dyna.actor.world.pos, 0x1F4, 0x3E8, 0);
        }
    } else {
        Math_ApproachS(&this->unk178, 0, 0x14, 0x100);
    }
}

void func_809EFAB4(Boss05* this, PlayState* play) {
    s32 i;
    Vec3f sp80;
    Vec3f sp74;
    Boss05* temp_v0;
    Player* player;

    Actor_MoveWithGravity(&this->dyna.actor);
    this->dyna.actor.world.pos.y -= 85.0f;
    this->dyna.actor.prevPos.y -= 85.0f;
    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f, 0x44U);
    this->dyna.actor.world.pos.y += 85.0f;
    this->dyna.actor.prevPos.y += 85.0f;

    if (this->dyna.actor.bgCheckFlags & 0x20) {
        this->dyna.actor.gravity = -0.3f;
        this->dyna.actor.terminalVelocity = -5.0f;
    } else {
        this->dyna.actor.gravity = -2.0f;
        this->dyna.actor.terminalVelocity = -20.0f;
    }

    if (this->dyna.actor.bgCheckFlags & 0x40) {
        this->dyna.actor.velocity.y = -3.0f;
        this->dyna.actor.gravity = -0.3f;
        this->dyna.actor.terminalVelocity = -5.0f;
        Math_Vec3f_Copy(&sp80, &this->dyna.actor.world.pos);
        sp80.y += 20.0f;
        EffectSsGSplash_Spawn(play, &this->dyna.actor.world.pos, NULL, NULL, 1, 1000);
        this->unk162[2] = 20;
    }

    if (this->unk162[2] != 0) {
        for (i = 0; i < 3; i++) {
            sp74.x = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.x;
            sp74.y = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.y;
            sp74.z = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.z;
            EffectSsBubble_Spawn(play, &sp74, 20.0f, 10.0f, 20.0f, 0.13f);
        }
    }

    if (this->dyna.actor.bgCheckFlags & 1) {
        if ((this->unk189 == 0xA) && (this->unk17A != 0)) {
            this->unk17A = 0;
        }

        Math_ApproachZeroF(&this->unk198, 1.0f, 0.05f);

        if (this->unk198 == 0.0f) {
            temp_v0 = (Boss05*)Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, 0x12D, this->unk324.x,
                                                  this->unk324.y, this->unk324.z, this->unk330.x, this->unk330.y,
                                                  this->unk330.z, 4);

            if (temp_v0 != NULL) {
                player = GET_PLAYER(play);
                if (&this->dyna.actor == player->unk_730) {
                    player->unk_730 = temp_v0;
                    play->actorCtx.targetContext.arrowPointedActor = temp_v0;
                    play->actorCtx.targetContext.targetedActor = temp_v0;
                }

                for (i = 0; i < 20; i++) {
                    temp_v0->unk3C8.jointTable[i] = this->unk3C8.jointTable[i];
                }

                Actor_PlaySfxAtPos(&temp_v0->dyna.actor, NA_SE_EN_MIZUBABA_TRANSFORM);
            }
            Actor_MarkForDeath(&this->dyna.actor);
        }
    }
}

void func_809EFE50(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss05* this = THIS;
    u8 var_a2 = 0;
    ColliderInfo* temp;

    if ((this->unk16A == 0) && (this->unk368.elements[0].info.bumperFlags & BUMP_HIT)) {
        this->unk368.elements[0].info.bumperFlags &= ~BUMP_HIT;
        temp = this->unk368.elements[0].info.acHitInfo;
        if (temp->toucher.dmgFlags & 0x300000) { // (DMG_NORMAL_SHIELD | DMG_LIGHT_RAY)
            this->unk338 = -12.0f;
            this->unk348 = this->dyna.actor.yawTowardsPlayer;
            this->unk16A = 6;
            return;
        }

        this->unk16A = 0xA;
        this->dyna.actor.speedXZ = 0.0f;
        this->unk338 = -20.0f;
        this->unk348 = this->dyna.actor.yawTowardsPlayer;

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);

        switch (this->dyna.actor.colChkInfo.damageEffect) {
            case 1:
                func_809F0A0C(this, play);
                break;

            case 2:
                this->unk188 = 1;
                var_a2 = 1;
                break;

            case 3:
                func_809F0A64(this, play);
                this->unk188 = 0xA;
                break;

            case 4:
                this->unk188 = 0x14;
                var_a2 = 1;
                break;

            default:
                var_a2 = 1;
                break;
        }

        if (var_a2 != 0) {
            u8 damage; // Probably fake?

            if ((this->actionFunc == func_809F0ABC) && (this->unk189 == 0xA) && (this->unk17A != 0)) {
                func_809EE4E0(this, play);
                this->unk188 = 0;
            }

            damage = this->dyna.actor.colChkInfo.damage;
            this->dyna.actor.colChkInfo.health -= damage;
            if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
                Enemy_StartFinishingBlow(play, &this->dyna.actor);
            }
            func_809F0708(this, play);
            this->unk16C = 0xF;
        }
    }
}

s32 func_809F0014(Boss05* this, PlayState* play) {
    s16 var_v1 = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;

    if (ABS_ALT(var_v1) < 0x3000) {
        return true;
    } else {
        return false;
    }
}

void func_809F0058(Boss05* this, PlayState* play) {
    if (func_809F0014(this, play) && (this->dyna.actor.xyzDistToPlayerSq <= SQ(200.0f)) &&
        (fabsf(this->dyna.actor.playerHeightRel) < 70.0f)) {
        func_809F0474(this, play);
    }
}

void func_809F00CC(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F010C;
    Animation_MorphToPlayOnce(&this->unk3C8, &D_06006E50, -5.0f);
}

void func_809F010C(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->unk3C8);
    Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 2, 0x400);
    Math_ApproachS(&this->dyna.actor.shape.rot.z, 0, 2, 0x400);
    Math_ApproachF(&this->unk360, 1.0f, 1.0f, 0.5f);
    Math_ApproachF(&this->unk364, 1.0f, 1.0f, 0.14f);
    if (this->unk364 == 1.0f) {
        func_809F01CC(this, play);
    }
}

void func_809F01CC(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F0244;
    Animation_MorphToLoop(&this->unk3C8, &D_06007488, -10.0f);
    this->unk162[0] = (s32)(Rand_ZeroFloat(25.0f) + 25.0f);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA1_MOUTH);
}

void func_809F0244(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->unk3C8);
    Math_ApproachZeroF(&this->dyna.actor.speedXZ, 1.0f, 2.5f);
    Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 2, 0x400);
    Math_ApproachS(&this->dyna.actor.shape.rot.z, 0, 2, 0x400);

    if (this->unk162[0] == 0) {
        func_809F02D0(this, play);
    }

    func_809F0058(this, play);
}

void func_809F02D0(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F0374;
    Animation_MorphToLoop(&this->unk3C8, &D_06007908, 0.0f);
    this->unk162[0] = (s32)(Rand_ZeroFloat(80.0f) + 60.0f);
    this->unk34C = randPlusMinusPoint5Scaled(400.0f) + this->dyna.actor.world.pos.x;
    this->unk354 = randPlusMinusPoint5Scaled(400.0f) + this->dyna.actor.world.pos.z;
    this->unk358 = 0.0f;
}

void func_809F0374(Boss05* this, PlayState* play) {
    f32 sp24;
    f32 sp20;

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_WALK - SFX_FLAG);
    SkelAnime_Update(&this->unk3C8);
    Math_ApproachF(&this->dyna.actor.speedXZ, 5.0f, 1.0f, 2.0f);
    sp24 = this->unk34C - this->dyna.actor.world.pos.x;
    sp20 = this->unk354 - this->dyna.actor.world.pos.z;
    Math_ApproachS(&this->dyna.actor.world.rot.y, Math_Atan2S(sp24, sp20), 5, (s32)this->unk358);
    Math_ApproachF(&this->unk358, 2000.0f, 1.0f, 100.0f);

    if ((this->unk162[0] == 0) || ((SQ(sp24) + SQ(sp20)) < 2500.0f)) {
        func_809F01CC(this, play);
    }

    func_809F0058(this, play);
}

void func_809F0474(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F04C0;
    Animation_MorphToPlayOnce(&this->unk3C8, &D_06003448, 0.0f);
    this->unk162[0] = 20;
}

void func_809F04C0(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->unk3C8);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_VOICE - SFX_FLAG);
    Math_ApproachZeroF(&this->dyna.actor.speedXZ, 1.0f, 2.5f);
    Math_ApproachS(&this->dyna.actor.world.rot.y, this->dyna.actor.yawTowardsPlayer, 5, 0x1000);
    if (this->unk162[0] == 0) {
        func_809F0538(this, play);
    }
}

void func_809F0538(Boss05* this, PlayState* arg1) {
    this->actionFunc = func_809F0590;
    Animation_MorphToLoop(&this->unk3C8, &D_06000A5C, 0.0f);
    this->unk162[0] = 60;
    this->unk358 = 0.0f;
}

void func_809F0590(Boss05* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_VOICE - SFX_FLAG);
    SkelAnime_Update(&this->unk3C8);
    Math_ApproachF(&this->dyna.actor.speedXZ, 8.0f, 1.0f, 4.0f);
    Math_ApproachS(&this->dyna.actor.world.rot.y, this->dyna.actor.yawTowardsPlayer, 5, (s32)this->unk358);
    Math_ApproachF(&this->unk358, 4000.0f, 1.0f, 400.0f);
    if ((this->unk162[0] == 0) || (this->dyna.actor.xyzDistToPlayerSq <= 22500.0f)) {
        func_809F0650(this, play);
    }
}

void func_809F0650(Boss05* this, PlayState* arg1) {
    this->actionFunc = func_809F06B8;
    Animation_MorphToPlayOnce(&this->unk3C8, &D_060006A4, 0.0f);
    this->unk4FC = Animation_GetLastFrame(&D_060006A4);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_ATTACK);
}

void func_809F06B8(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->unk3C8);
    if (Animation_OnFrame(&this->unk3C8, this->unk4FC)) {
        func_809F01CC(this, play);
    }
}

void func_809F0708(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F0780;
    Animation_MorphToPlayOnce(&this->unk3C8, &D_06002F0C, 0.0f);
    this->unk4FC = Animation_GetLastFrame(&D_060006A4);
    Actor_SetColorFilter(&this->dyna.actor, 0x4000U, 120, 0, 30);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0780.s")
void func_809F0780(Boss05* this, PlayState* play) {
    s32 i;
    s32 j;
    Vec3f sp7C;
    Boss05* temp_v0;

    SkelAnime_Update(&this->unk3C8);
    if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
        if (Animation_OnFrame(&this->unk3C8, 22.0f)) {
            for (i = 0; i < 14; i++) {
                temp_v0 = (Boss05*)Actor_SpawnAsChild(
                    &play->actorCtx, &this->dyna.actor, play, 0x12D, this->dyna.actor.world.pos.x,
                    this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                    this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, i + 0xA);

                if (temp_v0 != NULL) {
                    for (j = 0; j < 20; j++) {
                        temp_v0->unk3C8.jointTable[j] = this->unk3C8.jointTable[j];
                    }
                }
            }

            for (i = 0; i < 20; i++) {
                sp7C.x = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.x;
                sp7C.y = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.y;
                sp7C.z = randPlusMinusPoint5Scaled(40.0f) + this->dyna.actor.world.pos.z;
                EffectSsBubble_Spawn(play, &sp7C, 20.0f, 10.0f, 20.0f, 0.13f);
            }

            SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 40, 0x381F);
            Actor_MarkForDeath(&this->dyna.actor);
            Item_DropCollectibleRandom(play, NULL, &this->dyna.actor.world.pos, 0xE0);
        }
    } else if (Animation_OnFrame(&this->unk3C8, this->unk4FC)) {
        func_809F0474(this, play);
    }
}

void func_809F0A0C(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F0ABC;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
    this->unk162[0] = 40;
    Actor_SetColorFilter(&this->dyna.actor, 0, 120, 0, 40);
}

void func_809F0A64(Boss05* this, PlayState* play) {
    this->actionFunc = func_809F0ABC;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
    this->unk162[0] = 80;
    Actor_SetColorFilter(&this->dyna.actor, 0, 120, 0, 80);
}

void func_809F0ABC(Boss05* this, PlayState* play) {
    Math_ApproachZeroF(&this->dyna.actor.speedXZ, 1.0f, 2.5f);
    if (this->unk162[0] == 0) {
        func_809F01CC(this, play);
    }
}

void func_809F0B0C(Boss05* this, PlayState* play) {
    Actor_MoveWithGravity(&this->dyna.actor);

    if (this->unk15C == 0) {
        Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f, 0x44);
        if (this->dyna.actor.bgCheckFlags & 0x20) {
            this->unk15C = 1;
        } else {
            this->unk15C = 2;
        }
    }

    if (this->unk15C == 1) {
        Math_ApproachF(&this->dyna.actor.velocity.y, 1.0f, 1.0f, 0.1f);
        Math_ApproachZeroF(&this->dyna.actor.speedXZ, 0.5f, 0.5f);
        this->dyna.actor.shape.rot.x += this->unk500;
        this->dyna.actor.shape.rot.y += this->unk502;

        if (this->unk162[0] == 0) {
            Actor_MarkForDeath(&this->dyna.actor);
        }
    } else {
        switch (this->unk15C) {
            case 2:
                this->dyna.actor.velocity.y = Rand_ZeroFloat(3.0f) + 3.0f;
                this->dyna.actor.speedXZ = randPlusMinusPoint5Scaled(5.0f) + 5.0f;
                this->dyna.actor.world.rot.y = (s32)Rand_ZeroFloat(0x10000);
                this->dyna.actor.gravity = -1.0f;
                this->unk15C = 3;
                break;

            case 3:
                Actor_MoveWithGravity(&this->dyna.actor);

                if (this->unk324.y < (this->dyna.actor.floorHeight - 30.0f)) {
                    Actor_MarkForDeath(&this->dyna.actor);
                }
                break;

            default:
                break;
        }
    }
}

void Boss05_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = (Boss05*)thisx;
    s16 var_v0;

    this->unk160++;

    for (var_v0 = 0; var_v0 < 3; var_v0++) {
        if (this->unk162[var_v0] != 0) {
            this->unk162[var_v0]--;
        }
    }

    if (this->unk16A != 0) {
        this->unk16A--;
    }

    if (this->unk16C != 0) {
        this->unk16C--;
    }
    if (this->unk168 != 0) {
        this->unk168--;
    }

    if (this->unk17A != 0) {
        this->unk17A--;
    }

    this->actionFunc(this, play);

    if (this->dyna.actor.params == 4) {
        Actor_MoveWithGravity(&this->dyna.actor);
        Matrix_RotateYS(this->unk348, MTXMODE_NEW);
        Matrix_MultVecZ(this->unk338, &this->unk33C);
        this->dyna.actor.world.pos.x += this->unk33C.x;
        this->dyna.actor.world.pos.z += this->unk33C.z;
        Math_ApproachZeroF(&this->unk338, 1.0f, 1.0f);
        Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f, 0x45);
        func_809EFE50(&this->dyna.actor, play);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk368.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk368.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk368.base);
        this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
    }

    switch (this->unk188) {
        case 0:
            this->unk189 = 0;
            this->unk17A = 0;
            this->unk184 = 0.0f;
            break;

        case 1:
            this->unk189 = 0;
            this->unk17A = 80;
            this->unk184 = 1.0f;
            this->unk188++;
            this->unk17C = 0.0f;
            // fallthrough
        case 2:
            if (this->unk17A == 0) {
                Math_ApproachZeroF(&this->unk184, 1.0f, 0.02f);
                if (this->unk184 == 0.0f) {
                    this->unk188 = 0;
                }
            } else {
                Math_ApproachF(&this->unk17C, 1.0f, 0.1f, 0.5f);
            }
            break;

        case 10:
            this->unk189 = 0xA;
            this->unk17A = 80;
            this->unk184 = 1.0f;
            this->unk188++;
            this->unk17C = 0.0f;
            this->unk180 = 2.0f;
            // fallthrough
        case 11:
            if (this->unk17A == 0) {
                func_809EE4E0(this, play);
                this->unk188 = 0;
            } else {
                Math_ApproachF(&this->unk17C, 1.0f, 1.0f, 0.25f);
                Math_ApproachF(&this->unk180, 1.0f, 0.1f, 0.1f);
            }
            break;

        case 20:
            this->unk189 = 0x14;
            this->unk17A = 80;
            this->unk184 = 1.0f;
            this->unk188++;
            this->unk17C = 0.0f;
            break;

        case 21:
            if (this->unk17A == 0) {
                Math_ApproachZeroF(&this->unk17C, 1.0f, 0.03f);

                if (this->unk17C == 0.0f) {
                    this->unk188 = 0;
                    this->unk184 = 0.0f;
                }
            } else {
                Math_ApproachF(&this->unk17C, 1.0f, 0.5f, 0.5f);
            }
            break;
    }
}

extern u8 D_809F1CB8[];

s32 func_809F1050(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;
    s8 temp_v1;

    if (limbIndex == KREG(32)) {
        if (!(this->unk160 & 3)) {
            *dList = NULL;
        }
        rot->x += KREG(33) * 0x100;
        rot->y += KREG(34) * 0x100;
        rot->z += KREG(35) * 0x100;
    }

    if ((thisx->params == 1) && (limbIndex == 9)) {
        *dList = NULL;
    }

    if (limbIndex == 2) {
        rot->x += this->unk19C;
    }

    temp_v1 = D_809F1CB8[limbIndex];
    if (temp_v1 >= 0) {
        rot->x = rot->x + this->unk19E[temp_v1].x;
        rot->y = rot->y + this->unk19E[temp_v1].y;
        rot->z = rot->z + this->unk19E[temp_v1].z;
    }

    return false;
}

extern Vec3f D_809F1CC4;

void func_809F1170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;
    MtxF sp3C;
    Vec3f sp30;
    Vec3f sp24;

    if (limbIndex == 4) {
        Matrix_MultVec3f(&D_809F1CC4, &this->unk324);

        if (this->actionFunc == func_809EFAB4) {
            Matrix_MultVec3f(&D_809F1CC4, &this->dyna.actor.focus.pos);
        }

        Matrix_Get(&sp3C);
        Matrix_MtxFToYXZRot(&sp3C, &this->unk330, false);
        this->unk330.x += 0xF00;
    }

    if (limbIndex == 2) {
        Matrix_MultZero(&sp30);
        func_809EE668(0, &this->unk1C8, &sp30);
    }

    if (limbIndex == 3) {
        Matrix_MultVecY(-500.0f, &sp24);
        func_809EE668(1, &this->unk1C8, &sp24);

        if (this->actionFunc == func_809EEDE8) {
            Matrix_MultVecY(1500.0f, &thisx->focus.pos);
        }
    }
}

s32 func_809F1284(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

extern Vec3f D_809F1CD0;
extern Vec3f D_809F1CDC;
extern Vec3f D_809F2110; // bss

void func_809F12A0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex == 1) {
        Matrix_MultVec3f(&D_809F1CD0, &D_809F2110);
        func_809EE668(0, &this->unk368, &D_809F2110);
        if (thisx->params == 4) {
            Matrix_MultVec3f(&D_809F1CDC, &thisx->focus.pos);
        }
        if (this->unk188 != 0) {
            Matrix_MultVec3f(&D_809F1CDC, &this->unk18C);
            if (this->unk189 == 0) {
                this->unk18C.y -= 15.0f;
            }
        }
    }
}

void func_809F135C(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss05* this = THIS;

    if ((limbIndex == 2) || (limbIndex == 3)) {
        Matrix_Scale(this->unk35C, 1.0f, this->unk35C, MTXMODE_APPLY);
    }

    if (limbIndex == 1) {
        Matrix_Scale(this->unk360, this->unk360, this->unk360, MTXMODE_APPLY);
    }

    if ((limbIndex >= 4) && (limbIndex < 20)) {
        Matrix_Scale(this->unk364, this->unk364, this->unk364, MTXMODE_APPLY);
    }
}

s32 func_809F1404(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex >= 3) && (limbIndex < 9)) {
        *dList = NULL;
    }

    return false;
}

s32 func_809F1430(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 9)) {
        *dList = NULL;
    }

    return false;
}

void func_809F1464(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss05* this = THIS;

    if ((limbIndex >= 3) && (limbIndex < 9)) {
        Matrix_Scale(this->unk198, this->unk198, this->unk198, MTXMODE_APPLY);
    }
}

extern s32 D_809F1CE8[];

s32 func_809F14AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex != D_809F1CE8[thisx->params - 10]) {
        *dList = NULL;
    } else if (this->unk15C >= 2) {
        rot->x += this->unk160 * 0x3000;
        rot->y += this->unk160 * 0x1A00;
        rot->z += this->unk160 * 0x2000;
    }
    return false;
}

void func_809F1550(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex != D_809F1CE8[thisx->params - 10]) {
        Matrix_MultZero(&this->unk324);
    }
}

void Boss05_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->actionFunc == func_809EEDE8) {
        SkelAnime_DrawFlexOpa(play, this->unk268.skeleton, this->unk268.jointTable, this->unk268.dListCount,
                              func_809F1050, func_809F1170, &this->dyna.actor);

        if (this->unk16C & 1) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }

        Matrix_Translate(this->unk324.x, this->unk324.y, this->unk324.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk330.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk330.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk330.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(D_06006240));

        SkelAnime_DrawTransformFlexOpa(play, this->unk3C8.skeleton, this->unk3C8.jointTable, this->unk3C8.dListCount,
                                       func_809F1284, func_809F12A0, func_809F135C, &this->dyna.actor);
    } else if (this->dyna.actor.params == 2) {
        Matrix_Translate(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                         MTXMODE_NEW);
        Matrix_RotateYS(this->unk176, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk178, MTXMODE_APPLY);
        Matrix_RotateYS(-this->unk176, MTXMODE_APPLY);
        Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        SkelAnime_DrawFlexOpa(play, this->unk268.skeleton, this->unk268.jointTable, this->unk268.dListCount,
                              func_809F1404, NULL, &this->dyna.actor);
    } else if (this->dyna.actor.params == 3) {
        SkelAnime_DrawTransformFlexOpa(play, this->unk268.skeleton, this->unk268.jointTable, this->unk268.dListCount,
                                       func_809F1430, func_809F1170, func_809F1464, &this->dyna.actor);

        Matrix_Translate(this->unk324.x, this->unk324.y, this->unk324.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk330.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk330.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk330.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(D_06006240));

        SkelAnime_DrawTransformFlexOpa(play, this->unk3C8.skeleton, this->unk3C8.jointTable, this->unk3C8.dListCount,
                                       func_809F1284, func_809F12A0, func_809F135C, &this->dyna.actor);

        Actor_DrawDamageEffects(play, &this->dyna.actor, &this->unk18C, 1, this->unk17C, this->unk180, this->unk184,
                                this->unk189);
    } else if (this->dyna.actor.params == 4) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(D_06006240));

        if (this->unk16C & 1) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }

        SkelAnime_DrawTransformFlexOpa(play, this->unk3C8.skeleton, this->unk3C8.jointTable, this->unk3C8.dListCount,
                                       func_809F1284, func_809F12A0, func_809F135C, &this->dyna.actor);

        Actor_DrawDamageEffects(play, &this->dyna.actor, &this->unk18C, 1, this->unk17C, this->unk180, this->unk184,
                                this->unk189);
    } else if (this->dyna.actor.params >= 0xA) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(D_06006240));

        SkelAnime_DrawFlexOpa(play, this->unk3C8.skeleton, this->unk3C8.jointTable, this->unk3C8.dListCount,
                              func_809F14AC, func_809F1550, &this->dyna.actor);
    }

    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}

// typedef struct Boss05 {
//     /* 0x000 */ DynaPolyActor dyna;
//     /* 0x15C */ u8 unk15C;
//     /* 0x15D */ char pad15D[1];
//     /* 0x15E */ s16 unk15E;                         /* inferred */
//     /* 0x160 */ s16 unk160;
//     /* 0x162 */ s16 unk162[3];
//     /* 0x168 */ s16 unk168;
//     /* 0x16A */ s16 unk16A;
//     /* 0x16C */ s16 unk16C;
//     /* 0x16E */ char pad16E[2];
//     /* 0x170 */ void (*actionFunc)(Boss05 *, PlayState *);
//     /* 0x174 */ u8 unk174;                          /* inferred */
//     /* 0x175 */ char pad175[1];
//     /* 0x176 */ s16 unk176;
//     /* 0x178 */ s16 unk178;
//     /* 0x17A */ s16 unk17A;
//     /* 0x17C */ f32 unk17C;
//     /* 0x180 */ f32 unk180;
//     /* 0x184 */ f32 unk184;
//     /* 0x188 */ u8 unk188;
//     /* 0x189 */ u8 unk189;
//     /* 0x18A */ char pad18A[2];                     /* maybe part of unk189[3]? */
//     /* 0x18C */ Vec3f unk18C;
//     /* 0x198 */ f32 unk198;
//     /* 0x19C */ s16 unk19C;                         /* inferred */
//     /* 0x19E */ s16 unk19E;                         /* inferred */
//     /* 0x1A0 */ s16 unk1A0;                         /* inferred */
//     /* 0x1A2 */ s16 unk1A2;                         /* inferred */
//     /* 0x1A4 */ char pad1A4[0x24];                  /* maybe part of unk1A2[0x13]? */
//     /* 0x1C8 */ ColliderJntSph unk1C8;
//     /* 0x1E8 */ ColliderJntSphElement unk1E8[2];
//     /* 0x268 */ SkelAnime unk268;
//     /* 0x2AC */ Vec3s unk2AC[0xA];
//     /* 0x2E8 */ Vec3s unk2E8[0xA];
//     /* 0x324 */ Vec3f unk324;
//     /* 0x330 */ Vec3s unk330;
//     /* 0x336 */ s8 unk336[2];
//     /* 0x338 */ f32 unk338;
//     /* 0x33C */ Vec3f unk33C;
//     /* 0x348 */ s16 unk348;
//     /* 0x34A */ s8 unk34A[2];
//     /* 0x34C */ f32 unk34C;
//     /* 0x350 */ s8 unk350[4];
//     /* 0x354 */ f32 unk354;
//     /* 0x358 */ f32 unk358;
//     /* 0x35C */ f32 unk35C;
//     /* 0x360 */ f32 unk360;
//     /* 0x364 */ f32 unk364;
//     /* 0x368 */ ColliderJntSph unk368;
//     /* 0x388 */ ColliderJntSphElement unk388[1];
//     /* 0x3C8 */ SkelAnime unk3C8;
//     /* 0x40C */ Vec3s unk40C[0x14];
//     /* 0x484 */ Vec3s unk484[0x14];
//     /* 0x4FC */ f32 unk4FC;
//     /* 0x500 */ s16 unk500;
//     /* 0x502 */ s16 unk502;
//     /* 0x504 */ char pad504[4];                     /* maybe part of unk502[3]? */
// } Boss05;                                           /* size = 0x508 */

// static BgCamInfo D_809F1A20 = { 0, 0, NULL };
// static SurfaceType D_809F1A28 = { { 0x10000, 0x7C8 } };
// static CollisionPoly D_809F1A30[0xA];               /* unable to generate initializer */
// static Vec3s D_809F1AD0[8] = {
//     { -0xDAC, 0, -0xDAC },
//     { -0xDAC, 0, 0xDAC },
//     { 0xDAC, 0, 0xDAC },
//     { 0xDAC, 0, -0xDAC },
//     { 0xDAC, -0xFA0, -0xDAC },
//     { -0xDAC, -0xFA0, -0xDAC },
//     { 0xDAC, -0xFA0, 0xDAC },
//     { -0xDAC, -0xFA0, 0xDAC },
// };
// static ? D_809F1C60;                                /* unable to generate initializer */
// static ? D_809F1C8C;                                /* unable to generate initializer */
// static ? D_809F1CB8;                                /* unable to generate initializer */
// static s32 D_809F1CC0[1] = { 0x06FFFF00 };
// static Vec3f D_809F1CC4 = { 0.0f, -1400.0f, 600.0f };
// static Vec3f D_809F1CD0 = { 1600.0f, -300.0f, 0.0f };
// static Vec3f D_809F1CDC[5] = {
//     { 700.0f, 0.0f, 0.0f },
//     { 3e-45.0f, 4e-45.0f, 1e-45.0f },
//     { 6e-45.0f, 7e-45.0f, 1e-44.0f },
//     { 1.1e-44f, 1.4e-44f, 1.5e-44f },
//     { 1.8e-44f, 2e-44.0f, 2.2e-44f },
// }; /* extra bytes: 8 */
// static Vec3f D_809F2110;
// CollisionHeader D_809F1B00 = {
//     { -0xDAC, -0xFA0, -0xDAC },
//     { 0xDAC, 0, 0xDAC },
//     8,
//     D_809F1AD0,
//     0xA,
//     D_809F1A30,
//     &D_809F1A28,
//     &D_809F1A20,
//     0,
//     NULL,
// };
// ColliderJntSphElementInit D_809F1B2C[2] = {
//     {
//         { 3, { 0xF7CFFFFF, 0, 8 }, { 0xF7CFFFFF, 0, 0 }, 9, 1, 1 },
//         { 0, { { 0, 0, 0 }, 0xF }, 0x64 },
//     },
//     {
//         { 3, { 0xF7CFFFFF, 0, 8 }, { 0xF7CFFFFF, 0, 0 }, 9, 1, 1 },
//         { 0, { { 0, 0, 0 }, 0xF }, 0x64 },
//     },
// };
// ColliderJntSphInit D_809F1B74 = { { 3, 0x11, 9, 9, 0x10, 0 }, 2, D_809F1B2C };
// ColliderJntSphElementInit D_809F1B84[1] = {
//     {
//         { 3, { 0xF7CFFFFF, 0, 8 }, { 0xF7CFFFFF, 0, 0 }, 9, 1, 1 },
//         { 0, { { 0, 0, 0 }, 0x14 }, 0x64 },
//     },
// };
// ColliderJntSphInit D_809F1BA8 = { { 3, 0x11, 9, 9, 0x10, 0 }, 1, D_809F1B84 };
// ColliderJntSphElementInit D_809F1BB8[1] = {
//     {
//         { 3, { 0xF7CFFFFF, 0, 8 }, { 0xF7FFFFFF, 0, 0 }, 9, 1, 1 },
//         { 0, { { 0, 0, 0 }, 0xF }, 0x64 },
//     },
// };
// ColliderJntSphInit D_809F1BDC = { { 3, 0x11, 9, 9, 0x10, 0 }, 1, D_809F1BB8 };
// Color_RGBA8 D_809F1BEC = { 0xAA, 0xFF, 0xFF, 0xFF };
// Color_RGBA8 D_809F1BF0 = { 0xC8, 0xC8, 0xFF, 0xFF };
// Vec3f D_809F1BF4 = { 0.0f, -1.0f, 0.0f };
// DamageTable D_809F1C00 = {
//     {
//         0,
//         0xF1,
//         0,
//         0xF1,
//         0xF1,
//         0xF3,
//         0,
//         3,
//         0xF2,
//         0xE1,
//         0xF1,
//         0x21,
//         0x31,
//         0x43,
//         0xF1,
//         0xF1,
//         0xF3,
//         0xF2,
//         0,
//         0xF1,
//         0,
//         0,
//         0xF1,
//         0xF1,
//         0xF1,
//         0,
//         0,
//         0,
//         0,
//         0,
//         0,
//         0xF1,
//     },
// };
// DamageTable D_809F1C20 = {
//     {
//         0x10,
//         0xF3,
//         0,
//         0xF1,
//         0xF1,
//         0xF1,
//         0,
//         0x10,
//         0xF1,
//         0xF1,
//         0xF1,
//         0x22,
//         0x32,
//         0x42,
//         0xF1,
//         0x10,
//         0xF1,
//         0xF2,
//         0x10,
//         0xF1,
//         0,
//         0,
//         0xF1,
//         0xF1,
//         0xF1,
//         0,
//         0,
//         0x21,
//         0,
//         0,
//         0,
//         0xF1,
//     },
// };
