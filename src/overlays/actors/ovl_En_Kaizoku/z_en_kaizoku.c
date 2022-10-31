/*
 * File: z_en_kaizoku.c
 * Overlay: ovl_En_Kaizoku
 * Description: Fighter pirate
 */

#include "z_en_kaizoku.h"
#include "z64snap.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_100000)

#define THIS ((EnKaizoku*)thisx)

void EnKaizoku_Init(Actor* thisx, PlayState* play);
void EnKaizoku_Destroy(Actor* thisx, PlayState* play);
void EnKaizoku_Update(Actor* thisx, PlayState* play);

void func_80B85F48(EnKaizoku* this);
s32 func_80B85EA0(PlayState* play, Actor* actor);
void func_80B87C7C(EnKaizoku* this);
void func_80B88CD8(EnKaizoku* this);
void func_80B87900(EnKaizoku* this);
void func_80B87E28(EnKaizoku* this);
void func_80B87F70(EnKaizoku* this);
void func_80B874D8(EnKaizoku* this, PlayState* play);
void func_80B85FA8(EnKaizoku* this, PlayState* play);
void func_80B85FA8(EnKaizoku* this, PlayState* play);
void func_80B8A718(Actor* thisx, PlayState* play);
void func_80B872A4(EnKaizoku* this);
void func_80B868B8(EnKaizoku* this, PlayState* play);
void func_80B86B74(EnKaizoku* this, PlayState* play);
void func_80B872F4(EnKaizoku* this, PlayState* play);
void func_80B88214(EnKaizoku* this);
void func_80B8833C(EnKaizoku* this);
void func_80B88770(EnKaizoku* this);
void func_80B88910(EnKaizoku* this);
void func_80B8760C(EnKaizoku* this, PlayState* play);
void func_80B8798C(EnKaizoku* this, PlayState* play);
void func_80B88CD8(EnKaizoku* this);
void func_80B87D3C(EnKaizoku* this, PlayState* play);
void func_80B87CF8(PlayState*, Vec3f*);
void func_80B87E9C(EnKaizoku* this, PlayState* play);
void func_80B87FDC(EnKaizoku* this, PlayState* play);
void func_80B88CD8(EnKaizoku* this);
void func_80B87E28(EnKaizoku* this);
void func_80B86B58(EnKaizoku* this);
void func_80B8971C(EnKaizoku* this, PlayState* play);
void func_80B894C0(EnKaizoku* this, PlayState* play);
void func_80B89280(EnKaizoku* this, PlayState* play);
void func_80B88D6C(EnKaizoku* this, PlayState* play);
void func_80B88964(EnKaizoku* this, PlayState* play);
void func_80B887AC(EnKaizoku* this, PlayState* play);
void func_80B88278(EnKaizoku* this, PlayState* play);
void func_80B88378(EnKaizoku* this, PlayState* play);

u16 D_80B8A8D0[] = {
    0x11A4, 0x11A5, 0x11A6, 0x11A7, 0x11A8, 0x11A9, 0x11AA, 0x11AB, 0x11AC, 0x11AD,
};

Vec3f D_80B8A8E4[] = {
    { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { 41.0f, 55.0f, 11.0f },
    { 41.0f, 55.0f, 11.0f },   { 70.0f, 45.0f, 35.0f },   { 80.0f, 45.0f, 25.0f },   { 0.0f, 0.0f, 0.0f },
    { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { 41.0f, 55.0f, 11.0f },
    { 41.0f, 55.0f, 11.0f },   { 70.0f, 45.0f, 25.0f },   { 80.0f, 45.0f, 25.0f },   { 0.0f, 0.0f, 0.0f },
    { 90.0f, 9.0f, -30.0f },   { 90.0f, 9.0f, -30.0f },   { 90.0f, 9.0f, -30.0f },   { -41.0f, 55.0f, -11.0f },
    { -41.0f, 55.0f, -11.0f }, { -70.0f, 45.0f, -25.0f }, { -80.0f, 45.0f, -25.0f }, { 0.0f, 0.0f, 0.0f },
};

Vec3f D_80B8AA04[] = {
    { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { -470.0f, 30.0f, -140.0f },
    { -470.0f, 30.0f, -140.0f }, { -410.0f, 80.0f, -130.0f }, { -410.0f, 80.0f, -130.0f }, { 0.0f, 0.0f, 0.0f },
    { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { -470.0f, 30.0f, -140.0f },
    { -470.0f, 30.0f, -140.0f }, { -410.0f, 80.0f, -130.0f }, { -410.0f, 80.0f, -130.0f }, { 0.0f, 0.0f, 0.0f },
    { -120.0f, 60.0f, 20.0f },   { -120.0f, 60.0f, 20.0f },   { -120.0f, 60.0f, 20.0f },   { 470.0f, 30.0f, 140.0f },
    { 470.0f, 30.0f, 140.0f },   { 410.0f, 80.0f, 130.0f },   { 410.0f, 80.0f, 130.0f },   { 0.0f, 0.0f, 0.0f },
};

Color_RGBA8 D_80B8AB24[] = {
    { 255, 255, 90, 255 },
    { 55, 25, 80, 255 },
    { 5, 195, 110, 255 },
};

Color_RGBA8 D_80B8AB30[] = {
    { 255, 130, 10, 255 },
    { 185, 130, 210, 255 },
    { 135, 195, 80, 255 },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};

ActorInit En_Kaizoku_InitVars = {
    ACTOR_EN_KAIZOKU,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_KZ,
    sizeof(EnKaizoku),
    (ActorFunc)EnKaizoku_Init,
    (ActorFunc)EnKaizoku_Destroy,
    (ActorFunc)EnKaizoku_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

u32 D_80B8ABF8[] = {
    0x0600F8E4, 0x0600EF9C, 0x0600E1C8, 0x0600DBE4, 0x060058B8, 0x06004860, 0x06002730,
    0x06001578, 0x06001390, 0x060003CC, 0x06000F5C, 0x0600E8BC, 0x0600ED1C, 0x06005644,
    0x0600F288, 0x060043E4, 0x06003A3C, 0x06002BA0, 0x06001E9C,
};

u8 D_80B8AC44[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE,
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP,
};

Color_RGBA8 D_80B8AC58 = { 200, 160, 120, 255};
Color_RGBA8 D_80B8AC5C = { 130, 90, 50, 255 };

Vec3f D_80B8AC60 = { 0.0f, -1.5f, 0.0f };
Vec3f D_80B8AC6C = { 0.0f, -0.2f, 0.0f };
Vec3f D_80B8AC78 = { 300.0f, 0.0f, 0.0f };
Vec3f D_80B8AC84 = { 0.0f, -3000.0f, 0.0f };
Vec3f D_80B8AC90 = { 400.0f, 0.0f, 0.0f };
Vec3f D_80B8AC9C = { 1600.0f, -4000.0f, 0.0f };
Vec3f D_80B8ACA8 = { -3000.0f, -2000.0f, 1300.0f };
Vec3f D_80B8ACB4 = { -3000.0f, -2000.0f, -1300.0f };
Vec3f D_80B8ACC0 = { 1000.0f, 1000.0f, 0.0f };

u32 D_80B8ACCC[] = {
    0x060093B8, 0x06009978, 0x0600A0F8, 0x06009978,
};

extern AnimationHeader D_060058B8;

extern FlexSkeletonHeader D_0600D828;

void EnKaizoku_Init(Actor* thisx, PlayState* play) {
    EnKaizoku* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);
    EffectBlureInit1 blureInit;

    this->actor.hintId = TATL_HINT_ID_PIRATE;
    this->actor.targetMode = 3;
    this->actor.colChkInfo.mass = 80;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, 0.0f);
    this->unk_2CA = this->actor.world.rot.z;
    this->actor.colChkInfo.health = 8;
    this->unk_2D4 = this->actor.params & 0x3F;
    this->unk_2BC = (this->actor.params >> 6) & 0x7F;

    if (this->unk_2CA >= 2) {
        this->unk_2CA = 0;
    } else if (this->unk_2CA == 2) {
        this->unk_2CA = 0;
    }

    this->unk_2EC = this->actor.world.rot.z;
    this->actor.world.rot.z = 0;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600D828, &D_060058B8, this->jointTable, this->morphTable, KAIZOKU_LIMB_MAX);
    Collider_InitAndSetCylinder(play, &this->unk_3D4, &this->actor, &sCylinderInit);
    Collider_InitAndSetQuad(play, &this->unk_420, &this->actor, &sQuadInit);
    blureInit.p1StartColor[0] = blureInit.p1StartColor[1] = blureInit.p1StartColor[2] = blureInit.p1StartColor[3] =
        blureInit.p2StartColor[0] = blureInit.p2StartColor[1] = blureInit.p2StartColor[2] = blureInit.p1EndColor[0] =
            blureInit.p1EndColor[1] = blureInit.p1EndColor[2] = blureInit.p2EndColor[0] = blureInit.p2EndColor[1] =
                blureInit.p2EndColor[2] = 255;
    blureInit.p2StartColor[3] = 64;
    blureInit.p1EndColor[3] = blureInit.p2EndColor[3] = 0;
    blureInit.elemDuration = 8;
    blureInit.unkFlag = 0;
    blureInit.calcMode = 2;
    Effect_Add(play, &this->unk_3D0, EFFECT_BLURE1, 0, 0, &blureInit);
    Actor_SetScale(&this->actor, 0.0125f);
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~ACTOR_FLAG_1;
    if (this->unk_2BC == 127) {
        this->unk_2BC = -1;
    }

    if (this->unk_2BC >= 0 && Flags_GetSwitch(play, this->unk_2BC)) {
        Actor_Kill(&this->actor);
        return;
    }

    this->unk_3D4.dim.radius = 20;
    this->unk_3D4.dim.height = 65;
    this->unk_3D4.dim.yShift = 0;
    this->unk_2D6 = this->actor.cutscene;
    this->actor.world.pos.y = player->actor.world.pos.y + 160.0f;
    this->unk_144 = func_80B85EA0;
    this->actor.flags |= ACTOR_FLAG_400;
    func_80B85F48(this);
}

void EnKaizoku_Destroy(Actor* thisx, PlayState* play) {
    EnKaizoku* this = THIS;

    Effect_Destroy(play, this->unk_3D0);
    Collider_DestroyCylinder(play, &this->unk_3D4);
    Collider_DestroyQuad(play, &this->unk_420);
    Audio_RestorePrevBgm();
}

s32 func_80B85858(EnKaizoku* this, PlayState* play) {
    Actor* itemAction;
    Player* player = GET_PLAYER(play);
    s16 sp1E = this->unk_2B0;

    for (itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first; itemAction != NULL;
         itemAction = itemAction->next) {
        //! FAKE:
        if (1) {}
        if ((itemAction->id == ACTOR_ARMS_HOOK || itemAction->id == ACTOR_EN_ARROW) && player->unk_D57) {
            if ((itemAction->id != ACTOR_ARMS_HOOK || this->unk_2B0 != 13) && this->unk_2B0 != 6) {
                func_80B87C7C(this);
            }
            break;
        }
    }

    if (sp1E != this->unk_2B0) {
        return true;
    } else {
        return false;
    }
}

void func_80B85900(EnKaizoku* this) {
    if (this->unk_2B0 == 1) {
        this->unk_57A = Math_SinS(this->unk_2B4 * 0x1068) * 8920.0f;
    } else if (this->unk_2B0 != 13) {
        if (this->unk_2B0 == 9 || this->unk_2B0 == 11) {
            Math_SmoothStepToS(&this->unk_57A, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 1, 500, 0);
            this->unk_57A = CLAMP(this->unk_57A, -0x256F, 0x256F);
        } else {
            this->unk_57A = 0;
        }
    }
}

s32 func_80B85A00(EnKaizoku* this, PlayState* play, s16 arg2) {
    Player* player = GET_PLAYER(play);
    s16 sp32 = ABS_ALT(this->actor.wallYaw - this->actor.shape.rot.y);
    s16 sp30 = ABS_ALT(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    Actor* sp2C;

    if (func_800BE184(play, &this->actor, 100.0f, 0x2710, 0x4000, this->actor.shape.rot.y)) {
        if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            if (this->unk_2B0 != 2) {
                func_80B874D8(this, play);
            }
            return 1;
        } else {
            func_80B87900(this);
            return 1;
        }
    } else if (func_800BE184(play, &this->actor, 100.0f, 0x5DC0, 0x2AA8, this->actor.shape.rot.y)) {
        this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        if ((this->actor.bgCheckFlags & 8) && (ABS_ALT(sp32) < 12000) && (this->actor.xzDistToPlayer < 90.0f)) {
            if (this->unk_2B0 != 6) {
                func_80B87C7C(this);
            }
            return 1;
        } else if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            if (this->unk_2B0 != 2) {
                func_80B874D8(this, play);
            }
        } else if (this->actor.xzDistToPlayer < BREG(11) + 180.0f) {
            func_80B87900(this);
        } else if (this->unk_2B0 != 7) {
            func_80B87E28(this);
        }
        return 1;
    }

    sp2C = Actor_FindNearby(play, &this->actor, -1, ACTORCAT_EXPLOSIVES, 80.0f);
    if (sp2C != NULL) {
        this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        if (((this->actor.bgCheckFlags & 8) && (sp32 < 12000)) || (sp2C->id == ACTOR_EN_BOM_CHU)) {
            if (sp2C->id == ACTOR_EN_BOM_CHU && Actor_DistanceBetweenActors(&this->actor, sp2C) < 80.0f &&
                (s16)(this->actor.shape.rot.y - sp2C->world.rot.y + 0x8000) < 0x4000) {
                if (this->unk_2B0 != 6) {
                    func_80B87C7C(this);
                }
            } else {
                func_80B87900(this);
            }
            return 1;
        }
        if (this->unk_2B0 != 7) {
            func_80B87E28(this);
        }
        return 1;
    }

    if (arg2) {
        s16 sp2A;

    label:;
        if (sp30 >= 10000) {
            func_80B87900(this);
        } else {
            sp2A = player->actor.shape.rot.y - this->actor.shape.rot.y;
            if (this->actor.xzDistToPlayer <= 65.0f && !Actor_OtherIsTargeted(play, &this->actor) &&
                ABS_ALT(sp2A) < 0x5000) {
                if (this->unk_2B0 != 9) {
                    func_80B87F70(this);
                    return 1;
                }
            } else if (this->unk_2B0 != 3) {
                func_80B88CD8(this);
            }
        }
        return 1;
    }
    return 0;
}


void func_80B85E18(EnKaizoku* this, s32 arg1) {
    this->unk_2E4 = arg1;
    this->unk_2DC = Animation_GetLastFrame(D_80B8ABF8[this->unk_2E4]);
    Animation_Change(&this->skelAnime, D_80B8ABF8[this->unk_2E4], 1.0f, 0.0f, this->unk_2DC, D_80B8AC44[this->unk_2E4],
                     0.0f);
}

s32 func_80B85EA0(PlayState* play, Actor* actor) {
    s32 ret;

    ret = Snap_ValidatePictograph(play, actor, PICTOGRAPH_PIRATE_GOOD, &actor->focus.pos, &actor->shape.rot, 10.0f, 400.0f, -1);
    ret |= Snap_ValidatePictograph(play, actor, PICTOGRAPH_PIRATE_TOO_FAR, &actor->focus.pos, &actor->shape.rot, 10.0f, 1200.0f, -1);
    return ret;
}

void func_80B85F48(EnKaizoku* this) {
    Math_Vec3f_Copy(&this->unk_2F8, &gZeroVec3f);
    Math_Vec3f_Copy(&this->unk_304, &gZeroVec3f);
    this->unk_2D8 = 1;
    this->unk_2B0 = 0;
    this->actionFunc = func_80B85FA8;
}


void func_80B85FA8(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 curFrame = this->skelAnime.curFrame;
    s32 sp54;

    switch (this->unk_59C) {
        case 0:
            if (!(this->actor.xzDistToPlayer < 200.0f)) {
                break;
            }

            if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
                ActorCutscene_SetIntentToPlay(this->unk_2D6);
                return;
            }

            ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
            func_800B7298(play, &this->actor, 0x15);
            this->unk_59E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
            this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;

            sp54 = (this->unk_2CA * 4) + this->unk_2C8;
            if (this->unk_2EC != 2) {
                player->actor.world.pos.x = this->actor.home.pos.x + 90.0f;
                player->actor.world.pos.z = this->actor.home.pos.z + 30.0f;
            } else {
                player->actor.world.pos.x = this->actor.home.pos.x - 90.0f;
                player->actor.world.pos.z = this->actor.home.pos.z - 30.0f;
            }

            player->actor.speedXZ = 0.0f;
            this->actor.world.pos.x = this->actor.home.pos.x;
            this->actor.world.pos.z = this->actor.home.pos.z;
            Message_StartTextbox(play, D_80B8A8D0[sp54], &this->actor);
            this->unk_2C8 += 1;
            this->actor.flags &= ~1;
            player->actor.shape.rot.y = player->actor.world.rot.y =
                Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.world.pos);
            Math_Vec3f_Copy(&this->unk_5A4, &this->unk_5C8);
            Math_Vec3f_Copy(&this->unk_5B0, &this->unk_5D4);
            this->unk_5BC.x = -0.11f;
            this->actor.draw = func_80B8A718;
            this->unk_598 = 0;
            func_801A0238(0, 0xA);
            this->unk_59C += 1;

        case 1:
            player->actor.shape.rot.y = player->actor.world.rot.y =
                Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.world.pos);
            this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;

            if (this->unk_2EC != 2) {
                player->actor.world.pos.x = this->actor.home.pos.x + 90.0f;
                player->actor.world.pos.z = this->actor.home.pos.z + 30.0f;
            } else {
                player->actor.world.pos.x = this->actor.home.pos.x - 90.0f;
                player->actor.world.pos.z = this->actor.home.pos.z - 30.0f;
            }

            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                func_801477B4(play);
                func_80B85E18(this, 0xB);
                this->unk_598 = 0;
                this->unk_59C += 1;
                this->actor.gravity = -2.0f;
            }
            break;

        case 2:
            if (this->actor.bgCheckFlags & 1) {
                if (this->unk_2D8 != 0) {
                    this->unk_2D8 = 0;
                    this->actor.world.pos.y = this->actor.floorHeight;
                    this->actor.velocity.y = 0.0f;
                    func_800B7298(play, &this->actor, 4);
                    Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_58C, 3.0f, 2, 2.0f, 0, 0, 0);
                    Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_580, 3.0f, 2, 2.0f, 0, 0, 0);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIRATE_ONGND);
                }

                if (curFrame >= 11.0f) {
                    this->unk_59C++;
                    this->unk_598 = 0;
                    this->unk_5BC.x = 0.0f;
                }
            }
            break;

        case 3:
            if (this->unk_2DC <= curFrame) {
                sp54 = this->unk_2CA * 4 + this->unk_2C8;
                if (Player_GetMask(play) == PLAYER_MASK_STONE) {
                    if (D_80B8A8D0[sp54] == 0x11A5) {
                        sp54 = 8;
                    } else if (D_80B8A8D0[sp54] == 0x11A9) {
                        sp54 = 9;
                    }
                }

                Message_StartTextbox(play, D_80B8A8D0[sp54], &this->actor);
                func_80B85E18(this, 0xC);
                this->unk_2C8++;
                this->unk_598 = 0;
                this->unk_59C++;
            }
            break;

        case 4:
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                func_801477B4(play);
                this->unk_598 = 0;
                this->unk_59C++;
                func_801A0238(0x7F, 0);
                Audio_PlayBgm_StorePrevBgm(0x38);
                func_80B85E18(this, 0xD);
            }
            break;

        case 5:
            Math_ApproachF(&this->unk_5E0, 2.0f, 0.2f, 1.0f);
            if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOSU_SWORD);
            }
            if (curFrame >= 30.0f) {
                this->unk_598 = 0;
                this->unk_59C++;
            }
            break;

        case 6:
            Math_ApproachF(&this->unk_5E0, 5.0f, 0.3f, 1.0f);
            if (this->unk_2DC <= curFrame) {
                this->unk_598 = 7;
                this->unk_2F8.x = 1.0f;
                this->unk_59C++;
                this->unk_2F8.y = 1.0f;
                this->unk_2F8.z = 1.0f;
                this->unk_304.x = 1.0f;
                this->unk_304.y = 1.0f;
                this->unk_304.z = 1.0f;
            }
            break;

        case 7:
            if (this->unk_598 == 0) {
                func_800B7298(play, &this->actor, 6);
                ActorCutscene_Stop(this->unk_2D6);
                this->unk_59C = 0;
                this->unk_59E = 0;
                this->actor.flags &= ~ACTOR_FLAG_100000;
                this->actor.flags &= ~ACTOR_FLAG_8000000;
                this->actor.flags |= ACTOR_FLAG_1;
                func_80B872A4(this);
            }
            break;
    }

    if (this->unk_59C < 7) {
        s32 temp_v0_3 = this->unk_2EC * 8;

        temp_v0_3 += this->unk_59C;
        this->unk_5C8.x = D_80B8A8E4[temp_v0_3].x + this->actor.home.pos.x;
        this->unk_5C8.y = D_80B8A8E4[temp_v0_3].y + player->actor.world.pos.y;
        this->unk_5C8.z = D_80B8A8E4[temp_v0_3].z + this->actor.home.pos.z;

        this->unk_5D4.x = D_80B8AA04[temp_v0_3].x + this->actor.home.pos.x;
        this->unk_5D4.y = D_80B8AA04[temp_v0_3].y + player->actor.world.pos.y;
        this->unk_5D4.z = D_80B8AA04[temp_v0_3].z + this->actor.home.pos.z;
    }

    if (this->unk_59C >= 5) {
        if (curFrame >= 6.0f) {
            Math_ApproachF(&this->unk_2F8.x, 1.0f, 0.3f, 0.3f);
            this->unk_2F8.z = this->unk_2F8.y = this->unk_2F8.x;
        }

        if (curFrame >= 22.0f) {
            Math_ApproachF(&this->unk_304.x, 1.0f, 0.3f, 0.3f);
            this->unk_304.z = this->unk_304.y = this->unk_304.x;
        }
    }

    if (this->unk_59C >= 5) {
        Math_ApproachF(&this->unk_5A4.x, this->unk_5C8.x, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->unk_5A4.y, this->unk_5C8.y, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->unk_5A4.z, this->unk_5C8.z, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->unk_5B0.x, this->unk_5D4.x, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->unk_5B0.y, this->unk_5D4.y, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->unk_5B0.z, this->unk_5D4.z, 0.5f, this->unk_5E0);
    } else {
        Math_Vec3f_Copy(&this->unk_5A4, &this->unk_5C8);
        Math_Vec3f_Copy(&this->unk_5B0, &this->unk_5D4);
    }

    if (this->unk_59E != 0) {
        this->unk_5BC.y = 1.0f;
        this->unk_5BC.z = 0.0f;
        Play_SetCameraAtEyeUp(play, this->unk_59E, &this->unk_5B0, &this->unk_5A4, &this->unk_5BC);
    }
}

void func_80B86804(EnKaizoku* this, PlayState* play) {
    if (this->unk_59E == 0) {
        if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
            ActorCutscene_SetIntentToPlay(this->unk_2D6);
            return;
        }
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
    }

    func_800B7298(play, &this->actor, 0x60);
    this->unk_59E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
    this->unk_2B2 = 30;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_598 = 0;
    this->unk_59C = 0;
    this->unk_2D8 = 0;
    this->unk_2B0 = 0;
    this->actionFunc = func_80B868B8;
    this->actor.speedXZ = 0.0f;
}

void func_80B868B8(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 4000, 1);
    this->unk_5A4.x = Math_SinS(this->actor.yawTowardsPlayer) * 155.0f + this->actor.world.pos.x;
    this->unk_5A4.y = this->actor.world.pos.y + 10.0f;
    this->unk_5A4.z = Math_CosS(this->actor.yawTowardsPlayer) * 115.0f + this->actor.world.pos.z;

    this->unk_5B0.x = Math_SinS(this->actor.yawTowardsPlayer) + this->actor.world.pos.x;
    this->unk_5B0.y = this->actor.world.pos.y + 30.0f;
    this->unk_5B0.z = Math_CosS(this->actor.yawTowardsPlayer) * 11.0f + this->actor.world.pos.z;

    switch (this->unk_59C) {
        case 0:
            if (this->unk_2DC <= curFrame) {
                func_80B85E18(this, 14);
                this->unk_2C8 = 3;
                this->unk_598 = 0;
                this->unk_59C++;
            }
            break;

        case 1:
            if (this->unk_2DC <= curFrame) {
                s32 textId;

                func_80B85E18(this, 15);
                textId = this->unk_2CA * 4 + this->unk_2C8;
                Message_StartTextbox(play, D_80B8A8D0[textId], &this->actor);
                Actor_PlaySfxAtPos(&this->actor, 0x39B9);
                this->unk_598 = 0;
                this->unk_59C++;
            }
            break;

        case 2:
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                func_801477B4(play);
                func_800B7298(play, &this->actor, 6);
                ActorCutscene_Stop(this->unk_2D6);
                this->unk_59E = 0;
                play->nextEntrance = play->setupExitList[this->unk_2D4];
                gSaveContext.nextCutsceneIndex = 0;
                Scene_SetExitFade(play);
                play->transitionTrigger = TRANS_TRIGGER_START;
                this->unk_59C++;
                this->unk_2B0 = 16;
            }

            break;
    }

    if (this->unk_59E != 0) {
        this->unk_5BC.x = 0.0f;
        this->unk_5BC.y = 1.0f;
        this->unk_5BC.z = 0.0f;
        Play_SetCameraAtEyeUp(play, this->unk_59E, &this->unk_5B0, &this->unk_5A4, &this->unk_5BC);
    }
}

void func_80B86B58(EnKaizoku* this) {
    this->unk_2D8 = 0;
    this->unk_2B0 = 0;
    this->actionFunc = func_80B86B74;
}

void func_80B86B74(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 textId;
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_59C < 2) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xFA0, 1);
        player->actor.world.pos.x = this->actor.home.pos.x + 90.0f;
        player->actor.world.pos.z = this->actor.home.pos.z + 30.0f;
        this->actor.world.pos.x = this->actor.home.pos.x;
        this->actor.world.pos.z = this->actor.home.pos.z;
        this->unk_5C8.x = player->actor.world.pos.x + 39.0f;
        this->unk_5C8.y = player->actor.world.pos.y + 4.0f;
        this->unk_5C8.z = player->actor.world.pos.z - 41.0f;
        this->unk_5D4.x = player->actor.world.pos.x - 150.0f;
        this->unk_5D4.y = player->actor.world.pos.y + 60.0f;
        this->unk_5D4.z = player->actor.world.pos.z + 50.0f;
    }

    player->actor.shape.rot.y = player->actor.world.rot.y =
        Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.world.pos);
    switch (this->unk_59C) {
        case 0:
            func_80B85E18(this, 0x11);
            this->unk_2C8 = 2;
            textId = this->unk_2CA * 4 + this->unk_2C8;
            Message_StartTextbox(play, D_80B8A8D0[textId], &this->actor);
            this->unk_2D9 = 0;
            this->unk_598 = 0;
            this->unk_59C++;
            break;

        case 1:
            if (this->unk_2DC <= curFrame) {
                if (this->unk_2D9 == 0) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIRATE_DAMM_BREATH);
                    this->unk_2D9 = 1;
                } else {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIRATE_BREATH);
                }
            }

            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                func_801477B4(play);
                func_80B85E18(this, 0x12);
                func_800B7298(play, &this->actor, 0x85);
                this->unk_5A0 = 0;
                this->unk_598 = 0;
                this->unk_59C++;
            }
            break;

        case 2:
            this->unk_5C8.x = player->actor.world.pos.x + 77.0f;
            this->unk_5C8.y = player->actor.world.pos.y + 84.0f;
            this->unk_5C8.z = player->actor.world.pos.z - 71.0f;

            this->unk_5D4.x = player->actor.world.pos.x - 110.0f;
            this->unk_5D4.y = player->actor.world.pos.y;
            this->unk_5D4.z = player->actor.world.pos.z + 30.0f;
            this->unk_5A0++;
            if (curFrame >= 1.0f) {
                Math_ApproachZeroF(&this->unk_2F8.x, 0.3f, 0.3f);
                Math_ApproachZeroF(&this->unk_304.x, 0.3f, 0.3f);
                this->unk_2F8.z = this->unk_2F8.y = this->unk_2F8.x;
                this->unk_304.z = this->unk_304.y = this->unk_304.x;
            }
            if (this->unk_5A0 == 0x12) {
                Actor* temp_v0_2;

                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIRATE_SHOUT);
                temp_v0_2 = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW, this->actor.world.pos.x,
                                        this->actor.world.pos.y + 10.0f, this->actor.world.pos.z,
                                        this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, -8);
                if (temp_v0_2 != NULL) {
                    temp_v0_2->gravity = -10.0f;
                    play->envCtx.fillScreen = 1;
                }
            }
            if (this->unk_5A0 >= 0x12) {
                Math_ApproachF(&this->unk_5EC, 60.0f, 1.0f, 20.0f);
                this->unk_5E8 = this->unk_5EC / 60.0f;
                play->envCtx.screenFillColor[3] = this->unk_5E8 * 255.0f;
                play->envCtx.screenFillColor[0] = play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[2] =
                    0xFF;
            }
            if (this->unk_2DC <= curFrame && this->unk_5A0 >= 0x28) {
                this->actor.draw = NULL;
                this->unk_598 = 10;
                Math_Vec3f_Copy(&this->unk_2F8, &gZeroVec3f);
                Math_Vec3f_Copy(&this->unk_304, &gZeroVec3f);
                this->unk_59C++;
            }
            break;

        case 3:
            if (this->unk_598 == 0) {
                Math_ApproachZeroF(&this->unk_5EC, 0.5f, 10.0f);
                this->unk_5E8 = this->unk_5EC / 60.0f;
                play->envCtx.screenFillColor[3] = this->unk_5E8 * 255.0f;
                if (play->envCtx.screenFillColor[3] < 10) {
                    play->envCtx.screenFillColor[0] = 0;
                    play->envCtx.screenFillColor[1] = 0;
                    play->envCtx.screenFillColor[2] = 0;
                    play->envCtx.screenFillColor[3] = 0;
                    play->envCtx.fillScreen = 0;
                    this->unk_59C = 0;
                    this->unk_59E = 0;
                    func_800B7298(play, &this->actor, 6);
                    ActorCutscene_Stop(this->unk_2D6);
                    if (this->unk_2BC >= 0) {
                        Flags_SetSwitch(play, this->unk_2BC);
                    }
                    Actor_Kill(&this->actor);
                }
            }
            break;
    }
    Math_ApproachF(&this->unk_5A4.x, this->unk_5C8.x, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5A4.y, this->unk_5C8.y, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5A4.z, this->unk_5C8.z, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5B0.x, this->unk_5D4.x, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5B0.y, this->unk_5D4.y, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5B0.z, this->unk_5D4.z, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5E0, 10.0f, 0.5f, 100.0f);

    if (this->unk_59E != 0) {
        this->unk_5BC.x = 0.0f;
        this->unk_5BC.z = 0.0f;
        this->unk_5BC.y = 1.0f;
        Play_SetCameraAtEyeUp(play, this->unk_59E, &this->unk_5B0, &this->unk_5A4, &this->unk_5BC);
    }
}

void func_80B872A4(EnKaizoku* this) {
    this->actor.speedXZ = 0.0f;
    func_80B85E18(this, 0);
    this->unk_2B0 = 1;
    this->actionFunc = func_80B872F4;
    this->actor.shape.shadowScale = 90.0f;
}

void func_80B872F4(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp1A;

    if (this->unk_2B4 == 0 && !func_80B85858(this, play) && !func_80B85A00(this, play, 0)) {
        sp1A = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (this->actor.xzDistToPlayer < 100.0f && player->meleeWeaponState != 0 && sp1A >= 0x1F40) {
            this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            func_80B88CD8(this);
            return;
        }

        if (Actor_IsFacingPlayer(&this->actor, 0xBB8)) {
            if (this->actor.xzDistToPlayer < 400.0f && this->actor.xzDistToPlayer > 150.0f) {
                if (Rand_ZeroOne() < 0.7f) {
                    if (Rand_ZeroOne() > 0.5f || ABS_ALT(sp1A) < 0x3000) {
                        func_80B88214(this);
                    } else {
                        func_80B88910(this);
                    }
                    return;
                }
            }

            if (Rand_ZeroOne() > 0.1f) {
                func_80B8833C(this);
                return;
            } else {
                func_80B88CD8(this);
                return;
            }
        }
        func_80B88770(this);
    }
}

void func_80B874D8(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    func_80B85E18(this, 3);
    if (Math_SinS(player->actor.shape.rot.y - this->actor.shape.rot.y) > 0.0f) {
        this->actor.speedXZ = -10.0f;
    } else if (Math_SinS(player->actor.shape.rot.y - this->actor.shape.rot.y) < 0.0f) {
        this->actor.speedXZ = 10.0f;
    } else if (Rand_ZeroOne() > 0.5f) {
        this->actor.speedXZ = 10.0f;
    } else {
        this->actor.speedXZ = -10.0f;
    }
    this->skelAnime.playSpeed = 1.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_2B2 = 6;
    this->unk_2B0 = 2;
    this->unk_2E0 = 0.0f;
    this->actionFunc = func_80B8760C;
}

void func_80B8760C(EnKaizoku* this, PlayState* play) {
    s16 var_v0;
    s32 temp_ft0;
    s32 temp_ft1;

    this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x3A98;
    if ((this->actor.bgCheckFlags & 8) ||
        !Actor_TestFloorInDirection(&this->actor, play, this->actor.speedXZ, this->actor.shape.rot.y + 0x4000)) {
        if (this->actor.bgCheckFlags & 8) {
            if (this->actor.speedXZ >= 0.0f) {
                var_v0 = this->actor.shape.rot.y + 0x4000;
            } else {
                var_v0 = this->actor.shape.rot.y - 0x4000;
            }
            var_v0 = this->actor.wallYaw - var_v0;
        } else {
            this->actor.speedXZ *= -0.8f;
            var_v0 = 0;
        }

        if (ABS_ALT(var_v0) > 0x4000) {
            func_80B87C7C(this);
            return;
        }
    }

    if (this->actor.xzDistToPlayer <= 65.0f) {
        Math_ApproachF(&this->unk_2E0, -4.0f, 1.0f, 1.5f);
    } else if (this->actor.xzDistToPlayer > 40.0f) {
        Math_ApproachF(&this->unk_2E0, 4.0f, 1.0f, 1.5f);
    } else {
        Math_ApproachZeroF(&this->unk_2E0, 1.0f, 6.65f);
    }

    if (this->unk_2E0 != 0.0f) {
        this->actor.world.pos.x += Math_SinS(this->actor.yawTowardsPlayer) * this->unk_2E0;
        this->actor.world.pos.z += Math_CosS(this->actor.yawTowardsPlayer) * this->unk_2E0;
    }

    this->skelAnime.playSpeed = 1.0f;
    temp_ft0 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
    temp_ft1 = this->skelAnime.curFrame + this->skelAnime.playSpeed;
    if (this->skelAnime.curFrame != 0.0f && ((temp_ft0 < 0 && temp_ft1 > 0) || (temp_ft0 < 5 && temp_ft1 >= 6))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GERUDOFT_WALK);
    }

    if (!(play->gameplayFrames & 0x5F)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PIRATE_BREATH);
    }

    if (this->unk_2B2 == 0) {
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        if (!func_80B85858(this, play)) {
            if (this->actor.xzDistToPlayer <= 70.0f) {
                func_80B87F70(this);
            } else {
                func_80B87E28(this);
            }
        }
    } else {
        if (this->actor.speedXZ >= 0.0f) {
            this->actor.shape.rot.y += 0x4000;
        } else {
            this->actor.shape.rot.y -= 0x4000;
        }
    }
}

void func_80B87900(EnKaizoku* this) {
    func_80B85E18(this, 7);

    if (this->unk_2D2 != 0) {
        this->unk_2D2 = -1;
    }
    this->unk_2D8 = 0;
    this->actor.speedXZ = 0.0f;
    this->unk_2B2 = Rand_S16Offset(10, 10);
    this->unk_3D4.base.acFlags |= AC_HARD;
    this->unk_2B4 = 12;
    this->unk_2B0 = 12;
    this->actionFunc = func_80B8798C;
}

void func_80B8798C(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v0;

    this->unk_2D8 = 1;
    if (this->unk_2B2 == 0) {
        this->skelAnime.playSpeed = 1.0f;
    }
    if (this->unk_2B4 == 0) {
        this->unk_2D8 = 0;
        temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (ABS_ALT(temp_v0) <= 0x4000 && this->actor.xzDistToPlayer < 40.0f &&
            fabsf(this->actor.playerHeightRel) < 50.0f) {
            if (func_800BE184(play, &this->actor, 100.0f, 10000, 0x4000, this->actor.shape.rot.y)) {
                if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B874D8(this, play);
                } else if (!(play->gameplayFrames & 1)) {
                    func_80B87900(this);
                } else {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B87E28(this);
                }
            } else {
                temp_v0 = player->actor.shape.rot.y - this->actor.shape.rot.y;
                if (ABS_ALT(temp_v0) < 0x4000) {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B87F70(this);
                } else {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B88CD8(this);
                }
            }
        } else {
            this->unk_3D4.base.acFlags &= ~AC_HARD;
            func_80B88CD8(this);
        }
    } else if (this->unk_2B2 == 0 &&
               func_800BE184(play, &this->actor, 100.0f, 10000, 0x4000, this->actor.shape.rot.y)) {
        if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            this->unk_3D4.base.acFlags &= ~AC_HARD;
            func_80B874D8(this, play);
        } else if (!func_80B85858(this, play)) {
            if (!(play->gameplayFrames & 1)) {
                if (this->actor.xzDistToPlayer < 100.0f && Rand_ZeroOne() > 0.7f) {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B87C7C(this);
                } else {
                    this->unk_3D4.base.acFlags &= ~AC_HARD;
                    func_80B87E28(this);
                }
            } else {
                func_80B87900(this);
            }
        }
    }
}

void func_80B87C7C(EnKaizoku* this) {
    func_80B85E18(this, 8);
    this->actor.speedXZ = 6.5f;
    this->actor.velocity.y = 15.0f;
    Actor_PlaySfxAtPos(&this->actor, 0x386C);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_3D4.info.elemType = 4;
    this->unk_3D4.base.colType = 10;
    this->unk_420.info.elemType = 4;
    this->unk_2B0 = 6;
    this->actionFunc = func_80B87D3C;
}


void func_80B87CF8(PlayState* arg0, Vec3f* arg1) {
    EffectSsKirakira_SpawnSmall(arg0, arg1, &D_80B8AC60, &D_80B8AC6C, &D_80B8AC58, &D_80B8AC5C);
}

void func_80B87D3C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xFA0, 1);
    if (this->actor.velocity.y >= 5.0f) {
        func_80B87CF8(play, &this->unk_58C);
        func_80B87CF8(play, &this->unk_580);
    }

    this->unk_2D8 = 0;
    if (this->unk_2DC <= curFrame && (this->actor.bgCheckFlags & 3)) {
        this->unk_3D4.info.elemType = 1;
        this->unk_3D4.base.colType = 3;
        this->unk_420.info.elemType = 2;
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.pos.y = this->actor.floorHeight;
        func_80B87F70(this);
    }
}

void func_80B87E28(EnKaizoku* this) {
    func_80B85E18(this, 8);
    this->actor.speedXZ = -8.0f;
    Actor_PlaySfxAtPos(&this->actor, 0x386C);
    this->unk_3D4.info.elemType = ELEMTYPE_UNK4;
    this->unk_3D4.base.colType = COLTYPE_NONE;
    this->unk_420.info.elemType = ELEMTYPE_UNK4;
    this->unk_2B0 = 7;
    this->actionFunc = func_80B87E9C;
    this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
}

void func_80B87E9C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    this->unk_2D8 = 0;
    if (this->unk_2DC <= curFrame) {
        if (this->actor.xzDistToPlayer < 170.0f && this->actor.xzDistToPlayer > 140.0f && Rand_ZeroOne() < 0.2f) {
            func_80B88910(this);
        } else {
            func_80B87900(this);
        }
    }
    if (!(play->state.frames & 0x5F)) {
        Actor_PlaySfxAtPos(&this->actor, 0x39B7U);
    }
}

void func_80B87F70(EnKaizoku* this) {
    func_80B85E18(this, 9);
    this->unk_2D0 = 0;
    this->unk_420.base.atFlags &= ~AT_BOUNCED;
    this->actor.speedXZ = 0.0f;
    AudioSfx_StopByPosAndId(&this->actor.projectedPos, 0x39B7);
    this->unk_2B0 = 9;
    this->actionFunc = func_80B87FDC;
}

void func_80B87FDC(EnKaizoku* this, PlayState* play2) {
    PlayState* play = play2;
    f32 curFrame;
    s16 sp2E;
    s16 sp2C;
    Player* player = GET_PLAYER(play2);

    curFrame = this->skelAnime.curFrame;
    sp2E = ABS_ALT(player->actor.shape.rot.y - this->actor.shape.rot.y);
    sp2C = ABS_ALT(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    this->actor.speedXZ = 0.0f;

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        Actor_PlaySfxAtPos(&this->actor, 0x3998);
        this->unk_2D2 = 1;
    } else if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        this->unk_2D2 = -1;
    }

    if (this->unk_420.base.atFlags & AT_BOUNCED) {
        this->unk_2D2 = -1;
        this->unk_420.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        func_80B87E28(this);
        return;
    }

    this->unk_2D8 = 0;
    if (this->unk_2DC <= curFrame) {
        if (!Actor_IsFacingPlayer(&this->actor, 0x1554)) {
            func_80B872A4(this);

            if (sp2C >= 0x4001) {
                this->unk_2B4 = 0x14;
            }
        } else {
            if (Rand_ZeroOne() > 0.7f || this->actor.xzDistToPlayer >= 120.0f) {
                func_80B872A4(this);
                return;
            }

            this->actor.world.rot.y = this->actor.yawTowardsPlayer;

            if (gGameInfo->data[0x96C] * 0.1f + 0.39999998f < Rand_ZeroOne()) {
                func_80B87900(this);
            } else if (sp2E < 0x2711) {
                if (sp2C >= 0x4001) {
                    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                    func_80B88CD8(this);
                } else {
                    func_80B85A00(this, play, 1);
                }
            } else {
                func_80B88CD8(this);
            }
        }
    }
}

void func_80B88214(EnKaizoku* this) {
    func_80B85E18(this, 8);
    this->unk_2B2 = 0;
    this->actor.speedXZ = 10.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Actor_PlaySfxAtPos(&this->actor, 0x386C);
    this->unk_2B0 = 5;
    this->actionFunc = func_80B88278;
}

void func_80B88278(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    this->unk_2D8 = 0;
    if (this->unk_2DC <= curFrame) {
        this->actor.speedXZ = 0.0f;
        if (!Actor_IsFacingPlayer(&this->actor, 0x1554)) {
            func_80B872A4(this);
            this->unk_2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
        } else {
            func_80B87F70(this);
        }
    }
    if (!(play->gameplayFrames & 0x5F)) {
        Actor_PlaySfxAtPos(&this->actor, 0x39B7);
    }
}

void func_80B8833C(EnKaizoku* this) {
    func_80B85E18(this, 4);
    this->unk_2B0 = 4;
    this->actionFunc = func_80B88378;
}

void func_80B88378(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 sp30;
    s32 sp2C;
    s16 sp2A;

    if (!func_80B85858(this, play)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0x2EE, 0);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.xzDistToPlayer <= 40.0f) {
            Math_ApproachF(&this->actor.speedXZ, -8.0f, 1.0f, 1.5f);
        } else if (this->actor.xzDistToPlayer > 55.0f) {
            Math_ApproachF(&this->actor.speedXZ, 8.0f, 1.0f, 1.5f);
        } else {
            Math_ApproachZeroF(&this->actor.speedXZ, 2.0f, 6.65f);
        }

        this->skelAnime.playSpeed = 1.0f;
        sp2A = ABS_ALT(player->actor.shape.rot.y - this->actor.shape.rot.y);
        if (this->actor.xzDistToPlayer < 150.0f && player->meleeWeaponState != 0 && sp2A >= 0x2000) {
            this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            if (Rand_ZeroOne() > 0.7f) {
                func_80B88CD8(this);
                return;
            }
        }

        sp30 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
        sp2C = this->skelAnime.curFrame + this->skelAnime.playSpeed;
        if (!Actor_IsFacingPlayer(&this->actor, 0x11C7)) {
            if (Rand_ZeroOne() > 0.5f) {
                func_80B88CD8(this);
            } else {
                func_80B872A4(this);
            }
        } else if (this->actor.xzDistToPlayer < 90.0f) {
            if ((Rand_ZeroOne() > 0.03f) || ((this->actor.xzDistToPlayer <= 65.0f) && (sp2A < 0x4000))) {
                func_80B87F70(this);
            } else if (Actor_OtherIsTargeted(play, &this->actor) && (Rand_ZeroOne() > 0.5f)) {
                func_80B87E28(this);
            } else {
                func_80B88CD8(this);
            }
        }

        if (!func_80B85A00(this, play, 0)) {
            if (this->actor.xzDistToPlayer < 210.0f && this->actor.xzDistToPlayer > 150.0f &&
                Actor_IsFacingPlayer(&this->actor, 0x1388)) {
                if (Actor_IsTargeted(play, &this->actor)) {
                    if (Rand_ZeroOne() > 0.5f) {
                        func_80B88214(this);
                    } else {
                        func_80B88910(this);
                    }
                } else {
                    func_80B88CD8(this);
                    return;
                }
            }

            if (!(play->gameplayFrames & 0x5F)) {
                Actor_PlaySfxAtPos(&this->actor, 0x39B7U);
            }

            if (this->skelAnime.curFrame != 0.0f && ((sp30 < 0 && sp2C > 0) || (sp30 < 4 && sp2C >= 5))) {
                Actor_PlaySfxAtPos(&this->actor, 0x39A0U);
            }
        }
    }
}

void func_80B88770(EnKaizoku* this) {
    func_80B85E18(this, 3);
    this->unk_2B0 = 0xA;
    this->actionFunc = func_80B887AC;
}

void func_80B887AC(EnKaizoku* this, PlayState* play) {
    s16 temp_v0;
    s16 var_a2;

    if (!func_80B85858(this, play) && !func_80B85A00(this, play, 0)) {
        temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (temp_v0 > 0) {
            var_a2 = (s16)(temp_v0 * 0.25f) + 0x7D0;
        } else {
            var_a2 = (s16)(temp_v0 * 0.25f) - 0x7D0;
        }
        this->actor.shape.rot.y += var_a2;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->skelAnime.playSpeed = 1.0f;

        if (Actor_IsFacingPlayer(&this->actor, 0x1388)) {
            if (Rand_ZeroOne() > 0.8f) {
                func_80B88CD8(this);
            } else {
                func_80B8833C(this);
            }
        }
        if (!(play->gameplayFrames & 0x5F)) {
            Actor_PlaySfxAtPos(&this->actor, 0x39B7U);
        }
    }
}

void func_80B88910(EnKaizoku* this) {
    func_80B85E18(this, 10);
    this->unk_420.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
    this->unk_2D0 = 0;
    this->unk_2B0 = 11;
    this->actionFunc = func_80B88964;
    this->actor.speedXZ = 0.0f;
}

void func_80B88964(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 curFrame = this->skelAnime.curFrame;
    s16 v1;
    s16 a0;
    s32 pad;

    if (this->unk_2D0 < 2) {
        if (this->unk_420.base.atFlags & AT_BOUNCED) {
            this->unk_420.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
            this->unk_2D0 = 1;
            this->skelAnime.playSpeed = 1.0f;
        }
    }

    if (this->skelAnime.curFrame <= 8.0f) {
        this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    } else {
        if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
            Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_58C, 3.0f, 2, 2.0f, 0, 0, 0);
            Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_580, 3.0f, 2, 2.0f, 0, 0, 0);
            this->unk_2D2 = 1;
            this->actor.speedXZ = 10.0f;
            Actor_PlaySfxAtPos(&this->actor, 0x3998U);
        } else if (Animation_OnFrame(&this->skelAnime, 21.0f)) {
            this->actor.speedXZ = 0.0f;
        } else if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
            this->unk_2D2 = -1;
        }
    }

    this->unk_2D8 = 0;
    if (this->unk_2DC <= curFrame && this->unk_2D0 < 2) {
        if (!Actor_IsFacingPlayer(&this->actor, 0x1554)) {
            func_80B872A4(this);
            this->unk_2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
            this->unk_2B4 = 46;
            return;
        }

        if (this->unk_2D0 != 0) {
            func_80B87E28(this);
            return;
        }

        if ((Rand_ZeroOne() > 0.7f) || (this->actor.xzDistToPlayer >= 120.0f)) {
            func_80B872A4(this);
            this->unk_2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
            return;
        }

        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        if (gGameInfo->data[0x96C] * 0.1f + 0.39999998f < Rand_ZeroOne()) {
            func_80B87900(this);
            return;
        }

        v1 = ABS_ALT(player->actor.shape.rot.y - this->actor.shape.rot.y);
        if (v1 <= 0x2710) {

            a0 = ABS_ALT(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
            if (a0 > 0x4000) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                func_80B88CD8(this);
            } else {
                func_80B85A00(this, play, 1);
            }
        } else {
            func_80B88CD8(this);
        }
    }
}

void func_80B88CD8(EnKaizoku* this) {
    func_80B85E18(this, 3);
    this->actor.speedXZ = randPlusMinusPoint5Scaled(12.0f);
    this->skelAnime.playSpeed = 1.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_2B2 = Rand_ZeroOne() * 30.0f + 30.0f;
    this->unk_2B0 = 3;
    this->actionFunc = func_80B88D6C;
    this->unk_2E0 = 0.0f;
}

void func_80B88D6C(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp2A;
    s32 temp_ft4;
    s32 temp_ft5;
    s16 yaw;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xFA0, 1);
    if (!func_80B85858(this, play) && !func_80B85A00(this, play, 0)) {
        this->actor.world.rot.y = this->actor.shape.rot.y + 0x4000;
        sp2A = player->actor.shape.rot.y + 0x8000;
        if (Math_SinS(sp2A - this->actor.shape.rot.y) >= 0.0f) {
            this->actor.speedXZ -= 0.25f;
            if (this->actor.speedXZ < -8.0f) {
                this->actor.speedXZ = -8.0f;
            }
        } else if (Math_SinS((sp2A - this->actor.shape.rot.y)) < 0.0f) {
            this->actor.speedXZ += 0.25f;
            if (this->actor.speedXZ > 8.0f) {
                this->actor.speedXZ = 8.0f;
            }
        }

        if ((this->actor.bgCheckFlags & 8) ||
            !Actor_TestFloorInDirection(&this->actor, play, this->actor.speedXZ, this->actor.shape.rot.y + 0x4000)) {

            if (this->actor.bgCheckFlags & 8) {
                if (this->actor.speedXZ >= 0.0f) {
                    yaw = this->actor.shape.rot.y + 0x4000;
                } else {
                    yaw = this->actor.shape.rot.y - 0x4000;
                }
                yaw = this->actor.wallYaw - (yaw);
            } else {
                this->actor.speedXZ *= -0.8f;
                yaw = 0;
            }

            if (ABS_ALT(yaw) > 0x4000) {
                this->actor.speedXZ *= -0.8f;
                if (this->actor.speedXZ < 0.0f) {
                    this->actor.speedXZ -= 0.5f;
                } else {
                    this->actor.speedXZ += 0.5f;
                }
            }
        }

        if (this->actor.xzDistToPlayer <= 65.0f) {
            Math_ApproachF(&this->unk_2E0, -4.0f, 1.0f, 1.5f);
        } else if (this->actor.xzDistToPlayer > 40.0f) {
            Math_ApproachF(&this->unk_2E0, 4.0f, 1.0f, 1.5f);
        } else {
            Math_ApproachZeroF(&this->unk_2E0, 1.0f, 6.65f);
        }

        if (this->unk_2E0 != 0.0f) {
            this->actor.world.pos.x += Math_SinS(this->actor.shape.rot.y) * this->unk_2E0;
            this->actor.world.pos.z += Math_CosS(this->actor.shape.rot.y) * this->unk_2E0;
        }

        temp_ft4 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
        temp_ft5 = this->skelAnime.curFrame + this->skelAnime.playSpeed;
        if (this->skelAnime.curFrame != 0.0f) {
            if (((temp_ft4 < 0 && temp_ft5 > 0) || (temp_ft4 < 5 && temp_ft5 > 5))) {
                Actor_PlaySfxAtPos(&this->actor, 0x39A0U);
            }
        }

        if (!(play->gameplayFrames & 0x5F)) {
            Actor_PlaySfxAtPos(&this->actor, 0x39B7U);
        }

        if (this->actor.xzDistToPlayer <= 65.0f) {
            func_80B87F70(this);
        } else if (this->unk_2B2 == 0) {
            if (Actor_OtherIsTargeted(play, &this->actor) && (Rand_ZeroOne() > 0.5f)) {
                func_80B87E28(this);
            } else {
                func_80B872A4(this);
            }
        }
    }
}

void func_80B891B8(EnKaizoku* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->unk_2B0 == 11) {
        func_80B85E18(this, 5);
    }

    if ((this->unk_2BA == 11 || this->unk_2BA == 10) && this->unk_2B8 == 0) {
        this->unk_2B8 = 0;
        this->unk_2BA = 0;
    }

    Actor_PlaySfxAtPos(&this->actor, 0x389E);
    this->unk_2D8 = 1;

    if ((this->unk_2BA != 11) && (this->unk_2BA != 10)) {
        this->unk_2B6 = 40;
    }

    this->unk_2B0 = 13;
    this->actionFunc = func_80B89280;
}

void func_80B89280(EnKaizoku* this, PlayState* play) {
    if (this->unk_2BA == 11) {
        if (this->unk_2B8 != 0 && this->unk_2B8 < 60) {
            this->unk_2BA = 10;
        }
    }

    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }
    }

    if ((this->unk_2B6 == 0) && (this->unk_2B8 == 0) && !CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_2000) &&
        (this->actor.bgCheckFlags & 1)) {
        this->unk_2D8 = 0;
        func_80B85A00(this, play, 1);

        if (this->unk_2BA == 11 || this->unk_2BA == 10) {
            Actor_SpawnIceEffects(play, &this->actor, this->unk_310, 15, 2, 0.7f, 0.4f);
            this->unk_2B8 = 0;
            this->unk_2BA = 0;
            this->actor.flags |= 0x400;
        }
    }
}

void func_80B893CC(EnKaizoku* this, PlayState* play) {
    Vec3f sp34;

    Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecZ(-10.0f, &sp34);
    Math_Vec3f_Copy(&this->unk_3C4, &sp34);
    this->unk_2B4 = 0;
    this->unk_2D8 = 0;
    this->actor.speedXZ = 0.0f;
    func_80B85E18(this, 5);

    if ((this->unk_2BA == 11 || this->unk_2BA == 10) && this->unk_2B8 != 0) {
        Actor_SpawnIceEffects(play, &this->actor, this->unk_310, 15, 2, 0.7f, 0.4f);
        this->unk_2B8 = 0;
        this->unk_2BA = 0;
        this->actor.flags |= ACTOR_FLAG_400;
    }

    Actor_PlaySfxAtPos(&this->actor, 0x3999U);
    this->unk_2B0 = 14;
    this->actionFunc = func_80B894C0;
}

void func_80B894C0(EnKaizoku* this, PlayState* play) {
    s16 temp_v0;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 4500, 0);
    if (!func_80B85858(this, play) && !func_80B85A00(this, play, 0) && this->unk_3C4.x < 1.0f &&
        this->unk_3C4.z < 1.0f) {
        temp_v0 = this->actor.wallYaw - this->actor.shape.rot.y;
        if (this->actor.bgCheckFlags & 8) {
            if (ABS_ALT(temp_v0) < 0x3000 && (this->actor.xzDistToPlayer < 90.0f)) {
                func_80B87C7C(this);
                return;
            }
        }

        if (this->actor.xzDistToPlayer <= 65.0f && (play->gameplayFrames & 7)) {
            this->unk_420.info.elemType = 2;
            func_80B87F70(this);
        } else {
            func_80B87E28(this);
        }
    }
}

void func_80B8960C(EnKaizoku* this, PlayState* play) {
    Vec3f sp24;

    this->actor.flags |= ACTOR_FLAG_100000;
    Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecZ(-10.0f, &sp24);
    Math_Vec3f_Copy(&this->unk_3C4, &sp24);
    func_80B85E18(this, 16);

    if (((this->unk_2BA == 11) || (this->unk_2BA == 10)) && (this->unk_2B8 == 0)) {
        this->unk_2BA = 0;
    }
    this->actor.speedXZ = 0.0f;
    this->unk_2D8 = 1;
    func_800B7298(play, &this->actor, 0x7B);
    Enemy_StartFinishingBlow(play, &this->actor);
    Actor_PlaySfxAtPos(&this->actor, 0x399A);
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.flags &= ~ACTOR_FLAG_400;
    this->unk_598 = 0;
    this->unk_59C = 0;
    this->unk_2B0 = 15;
    this->actionFunc = func_80B8971C;
}

void func_80B8971C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    Player* player;

    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
    }

    if (this->unk_2BA == 11 || this->unk_2BA == 10) {
        if (this->unk_2B8 == 0) {
            return;
        }
        Actor_SpawnIceEffects(play, &this->actor, this->unk_310, 0xF, 2, 0.7f, 0.4f);
        this->unk_2B8 = 0;
        this->unk_2BA = 0;
    }

    if (curFrame >= 25.0f) {
        player = GET_PLAYER(play);
        if (this->unk_59E == 0) {
            if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
                ActorCutscene_SetIntentToPlay(this->unk_2D6);
                return;
            }
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
            this->unk_59E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
        }

        Math_Vec3f_Copy(&this->unk_3C4, &gZeroVec3f);
        player->actor.world.pos.x = this->actor.home.pos.x + 90.0f;
        player->actor.world.pos.z = this->actor.home.pos.z + 30.0f;
        this->actor.world.pos.x = this->actor.home.pos.x;
        this->actor.world.pos.z = this->actor.home.pos.z;

        this->unk_5A4.x = this->unk_5C8.x = player->actor.world.pos.x + 39.0f;
        this->unk_5A4.y = this->unk_5C8.y = player->actor.world.pos.y + 4.0f;
        this->unk_5A4.z = this->unk_5C8.z = player->actor.world.pos.z - 41.0f;

        this->unk_5B0.x = this->unk_5D4.x = player->actor.world.pos.x - 150.0f;
        this->unk_5B0.y = this->unk_5D4.y = player->actor.world.pos.y + 60.0f;
        this->unk_5B0.z = this->unk_5D4.z = player->actor.world.pos.z + 50.0f;

        player->actor.shape.rot.y = player->actor.world.rot.y =
            Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.world.pos);

        if (this->unk_59E != 0) {
            this->unk_5BC.x = 0.0f;
            this->unk_5BC.y = 1.0f;
            this->unk_5BC.z = 0.0f;
            Play_SetCameraAtEyeUp(play, this->unk_59E, &this->unk_5B0, &this->unk_5A4, &this->unk_5BC);
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xFA0, 1);
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_2DC <= curFrame) {
        this->unk_2D8 = 0;
        func_80B86B58(this);
    } else if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        Actor_PlaySfxAtPos(&this->actor, 0x387A);
    }
}

void func_80B89A08(EnKaizoku* this, PlayState* play) {
    s32 sp64 = 0;
    Vec3f sp58;
    s32 i;
    Vec3f sp48;
    Player* player;

    if (gSaveContext.save.playerData.health <= 16) {
        this->unk_420.info.toucher.damage = 0;
    } else {
        this->unk_420.info.toucher.damage = 4;
    }

    if (!(this->unk_420.base.atFlags & AT_BOUNCED) && (this->unk_420.base.atFlags & AT_HIT)) {
        if (gSaveContext.save.playerData.health <= 16 && this->unk_2B0 != 16) {
            this->unk_2D0 = 2;
            this->unk_59E = 0;
            this->actor.flags |= 0x100000;

            if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
                ActorCutscene_SetIntentToPlay(this->unk_2D6);
                this->actionFunc = func_80B86804;
            } else {
                ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
                this->unk_59E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
                this->actionFunc = func_80B86804;
            }
            return;
        } else if ((this->unk_2B0 == 11) && (this->unk_420.base.at == &GET_PLAYER(play)->actor)) {
            func_800B8D98(play, &this->actor, 3.0f, this->actor.yawTowardsPlayer, 1.0f);
            Health_ChangeBy(play, -12);
            if ((gSaveContext.save.playerData.health <= 16) && (this->unk_2B0 != 16)) {
                Health_ChangeBy(play, 16);
                this->unk_2D0 = 2;
                this->unk_59E = 0;
                this->actor.flags |= ACTOR_FLAG_100000;

                if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
                    ActorCutscene_SetIntentToPlay(this->unk_2D6);
                    this->actionFunc = func_80B86804;
                } else {
                    ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
                    this->unk_59E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
                    this->actionFunc = func_80B86804;
                }
                return;
            }
        }

        if (this->unk_420.base.at->id == ACTOR_OBJ_TARU) {
            this->unk_420.base.at->home.rot.z = 1;
        }
    }

    if ((this->actor.bgCheckFlags & 8) && this->actor.wallBgId != BG_ACTOR_MAX &&
        (this->unk_2B0 == 2 || this->unk_2B0 == 3 || this->unk_2B0 == 4 || this->unk_2B0 == 1)) {
        func_80B87F70(this);
    }

    if ((this->unk_3D4.base.acFlags & AC_HIT) && this->unk_2B0 > 0 && this->unk_2D0 < 2 && this->unk_2B0 != 6 &&
        this->unk_2B0 != 12 && this->unk_2B0 != 14 && this->unk_2B0 != 15) {
        Actor_SetDropFlag(&this->actor, &this->unk_3D4.info);
        AudioSfx_StopByPosAndId(&this->actor.projectedPos, 0x39B7);

        switch (this->actor.colChkInfo.damageEffect) {
            case 5:
                if ((this->unk_2BA != 11 && this->unk_2BA != 10) || this->unk_2B8 == 0) {
                    this->unk_2B8 = 40;
                    this->unk_2BA = 31;
                }
                /* fallthrough */
            case 1:
                if ((this->unk_2BA != 11 && this->unk_2BA != 10) || this->unk_2B8 == 0) {
                    Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
                    this->unk_3D4.info.elemType = 1;
                    this->unk_3D4.base.colType = 3;
                    this->unk_420.info.elemType = 2;
                    func_80B891B8(this);
                }
                break;

            case 15:
                if (this->unk_2B0 != 5 && this->unk_2B0 != 7 && this->unk_2B0 < 14) {
                    sp64 = 1;
                }
                break;

            case 14:
                sp64 = 1;
                break;

            case 13:
                if (this->unk_2B0 == 13) {
                    sp64 = 1;
                } else if (this->unk_2B0 != 6) {
                    func_80B87C7C(this);
                }
                break;

            case 2:
                if (this->unk_2B0 != 5 && this->unk_2B0 != 7 && this->unk_2B0 < 14) {
                    this->unk_2B8 = 40;
                    this->unk_2BA = 0;
                    sp64 = 1;
                }
                break;

            case 3:
                if ((this->unk_2BA != 11 && this->unk_2BA != 10) || this->unk_2B8 == 0) {
                    Actor_ApplyDamage(&this->actor);
                    this->unk_3D4.info.elemType = 1;
                    this->unk_3D4.base.colType = 3;
                    this->unk_420.info.elemType = 4;
                    this->unk_2B8 = 80;
                    this->unk_2BA = 11;
                    this->unk_2C0 = 0.0f;
                    this->unk_2C4 = 1.5f;
                    this->actor.flags &= ~0x400;
                    if (this->actor.colChkInfo.health <= 0) {
                        func_80B8960C(this, play);
                    } else {
                        func_80B891B8(this);
                    }
                }
                break;

            case 4:
                if ((this->unk_2BA != 11 && this->unk_2BA != 10) || this->unk_2B8 == 0) {
                    this->unk_2B8 = 20;
                    this->unk_2BA = 20;
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                    sp64 = 1;
                }
                break;
        }

        if (sp64) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ApplyDamage(&this->actor);
            if (this->actor.colChkInfo.health <= 0) {
                func_80B8960C(this, play);
                return;
            }
            this->unk_3D4.info.elemType = 1;
            this->unk_3D4.base.colType = 3;
            this->unk_420.info.elemType = 4;
            Math_Vec3f_Copy(&sp58, &this->actor.focus.pos);
            for (i = 0; i < 3; i++) {
                sp58.y += Rand_ZeroFloat(20.0f);
                CollisionCheck_BlueBlood(play, NULL, &sp58);
            }
            func_80B893CC(this, play);
        }
    } else if (this->unk_3D4.base.acFlags & AC_HIT) {
        if (this->unk_2B0 != 6 && this->unk_2B0 != 14 && this->unk_2B0 != 15) {
            player = GET_PLAYER(play);
            sp48.x = this->unk_3D4.info.bumper.hitPos.x;
            sp48.y = this->unk_3D4.info.bumper.hitPos.y;
            sp48.z = this->unk_3D4.info.bumper.hitPos.z;
            if (player->transformation != 4) {
                player->unk_B84 = this->actor.yawTowardsPlayer;
                player->unk_B80 = 15.0f;
            }
            this->unk_3D4.base.acFlags &= ~AC_HIT;
            Actor_PlaySfxAtPos(&this->actor, 0x1806);
            EffectSsHitmark_SpawnFixedScale(play, 3, &sp48);
            CollisionCheck_SpawnShieldParticlesMetal(play, &sp48);
        }
    }
}

void EnKaizoku_Update(Actor* thisx, PlayState* play2) {
    EnKaizoku* this = THIS;
    PlayState* play = play2;
    Vec3f sp34;
    s32 pad;

    if (this->unk_2D8 == 0) {
        SkelAnime_Update(&this->skelAnime);
    }

    if (this->unk_2B0 != 0) {
        func_80B85900(this);
    }

    if (this->unk_2CE != 0) {
        this->unk_2CE--;
    }
    if (this->unk_2B2 != 0) {
        this->unk_2B2--;
    }
    if (this->unk_2B4 != 0) {
        this->unk_2B4--;
    }
    if (this->unk_2B6 != 0) {
        this->unk_2B6--;
    }
    if (this->unk_598 != 0) {
        this->unk_598--;
    }
    if (this->unk_2B8 != 0) {
        this->unk_2B8--;
    }

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    if (this->unk_2B0 != 0) {
        func_80B89A08(this, play);
    }
    if (this->unk_2B0 != 0) {
        Actor_SetFocus(&this->actor, 60.0f);
    }

    Actor_SetScale(&this->actor, 0.0125f);
    if (this->unk_2CE == 0) {
        this->unk_2CC += 1;
        if (this->unk_2CC >= 4) {
            this->unk_2CC = 0;
            this->unk_2CE = Rand_S16Offset(20, 60);
        }
    }

    if (this->actor.bgCheckFlags & 1) {
        Matrix_RotateYS(this->actor.shape.rot.y + this->unk_2F4, 0);
        Matrix_MultVecZ(this->unk_2F0, &sp34);
        this->actor.world.pos.x += this->unk_3C4.x + sp34.x;
        this->actor.world.pos.z += this->unk_3C4.z + sp34.z;
        Math_ApproachZeroF(&this->unk_3C4.x, 1.0f, 2.0f);
        Math_ApproachZeroF(&this->unk_3C4.z, 1.0f, 2.0f);
        Math_ApproachZeroF(&this->unk_2F0, 1.0f, 5.0f);
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 35.0f, 40.0f, 35.0f, 31);
    Collider_UpdateCylinder(&this->actor, &this->unk_3D4);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_3D4.base);
    if (this->unk_2D0 < 2 && this->unk_2B0 != 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_3D4.base);
    }
    if (this->unk_2D2 > 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_420.base);
    }
}


s32 func_80B8A318(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKaizoku* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    if (limbIndex == KAIZOKU_LIMB_05) {
        *dList = NULL;
    }

    if (limbIndex == KAIZOKU_LIMB_03) {
        rot->z += this->unk_578;
        rot->x += this->unk_57A;
        rot->y += this->unk_57C;
    } else if (limbIndex == KAIZOKU_LIMB_06) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, D_80B8AB24[this->unk_2EC].r, D_80B8AB24[this->unk_2EC].g,
                       D_80B8AB24[this->unk_2EC].b, 255);
    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, D_80B8AB30[this->unk_2EC].r, D_80B8AB30[this->unk_2EC].g,
                       D_80B8AB30[this->unk_2EC].b, 255);
    }

    CLOSE_DISPS(play->state.gfxCtx);
    return false;
}


void func_80B8A468(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f sp4C;
    Vec3f sp40;
    EnKaizoku* this = THIS;

    if (limbIndex == KAIZOKU_LIMB_0B) {
        Matrix_MultVec3f(&D_80B8AC9C, &this->unk_420.dim.quad[1]);
        Matrix_MultVec3f(&D_80B8ACA8, &this->unk_420.dim.quad[0]);
        Matrix_MultVec3f(&D_80B8ACB4, &this->unk_420.dim.quad[3]);
        Matrix_MultVec3f(&D_80B8ACC0, &this->unk_420.dim.quad[2]);
        Collider_SetQuadVertices(&this->unk_420, &this->unk_420.dim.quad[0], &this->unk_420.dim.quad[1],
                                 &this->unk_420.dim.quad[2], &this->unk_420.dim.quad[3]);
        Matrix_MultVec3f(&D_80B8AC84, &sp4C);
        Matrix_MultVec3f(&D_80B8AC90, &sp40);
        if (this->unk_2D2 == 1 && (this->unk_2B0 == 9 || this->unk_2B0 == 11)) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->unk_3D0), &sp4C, &sp40);
        } else if (this->unk_2D2 != 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->unk_3D0));
            this->unk_2D2 = 0;
        }
    } else {
        Actor_SetFeetPos(&this->actor, limbIndex, KAIZOKU_LIMB_13, &D_80B8AC78, KAIZOKU_LIMB_16, &D_80B8AC78);
    }
    if (limbIndex == KAIZOKU_LIMB_13) {
        Matrix_MultVec3f(&D_80B8AC78, &this->unk_58C);
    } else if (limbIndex == KAIZOKU_LIMB_16) {
        Matrix_MultVec3f(&D_80B8AC78, &this->unk_580);
    }

    if (limbIndex == KAIZOKU_LIMB_02 || limbIndex == KAIZOKU_LIMB_06 || limbIndex == KAIZOKU_LIMB_07 || limbIndex == KAIZOKU_LIMB_08 || limbIndex == KAIZOKU_LIMB_0A || limbIndex == KAIZOKU_LIMB_0C ||
        limbIndex == KAIZOKU_LIMB_0D || limbIndex == KAIZOKU_LIMB_0F || limbIndex == KAIZOKU_LIMB_11 || limbIndex == KAIZOKU_LIMB_12 || limbIndex == KAIZOKU_LIMB_13 ||
        limbIndex == KAIZOKU_LIMB_14 || limbIndex == KAIZOKU_LIMB_15 || limbIndex == KAIZOKU_LIMB_16 || limbIndex == KAIZOKU_LIMB_17) {
        Matrix_MultZero(&this->unk_310[this->unk_2E8]);
        if (++this->unk_2E8 >= 0xF) {
            this->unk_2E8 = 0;
        }
    }
}

void func_80B8A6B0(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnKaizoku* this = THIS;

    if (limbIndex == KAIZOKU_LIMB_0B) {
        Matrix_Scale(this->unk_2F8.x, this->unk_2F8.y, this->unk_2F8.z, MTXMODE_APPLY);
    }
    if (limbIndex == KAIZOKU_LIMB_10) {
        Matrix_Scale(this->unk_304.x, this->unk_304.y, this->unk_304.z, MTXMODE_APPLY);
    }
}

extern u32 D_80B8ACCC[];

void func_80B8A718(Actor* thisx, PlayState* play) {
    f32 pad[4];
    f32 sp34;
    EnKaizoku* this = THIS;

    func_8012C2DC(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80B8ACCC[this->unk_2CC]));
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, func_80B8A318, func_80B8A468, func_80B8A6B0,
                                   &this->actor);
    if (this->unk_2B8 != 0) {
        sp34 = this->unk_2B8 * 0.05f;
        if (this->unk_2BA == 0xB || this->unk_2BA == 0xA) {
            this->unk_2C0 += 0.3f;
            if (this->unk_2C0 > 0.5f) {
                this->unk_2C0 = 0.5f;
            }
            Math_ApproachF(&this->unk_2C4, this->unk_2C0, 0.1f, 0.04f);
        } else {
            this->unk_2C0 = 0.8f;
            this->unk_2C4 = 0.8f;
        }
        Actor_DrawDamageEffects(play, &this->actor, this->unk_310, ARRAY_COUNT(this->unk_310), this->unk_2C0, this->unk_2C4, sp34,
                                this->unk_2BA);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
