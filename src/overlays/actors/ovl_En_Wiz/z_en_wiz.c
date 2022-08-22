/*
 * File: z_en_wiz.c
 * Overlay: ovl_En_Wiz
 * Description: Wizzrobe
 */

#include "z_en_wiz.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS                                                                                            \
    (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_1000 | ACTOR_FLAG_100000 | \
     ACTOR_FLAG_8000000 | ACTOR_FLAG_80000000)

#define THIS ((EnWiz*)thisx)

void EnWiz_Init(Actor* thisx, PlayState* play);
void EnWiz_Destroy(Actor* thisx, PlayState* play);
void EnWiz_Update(Actor* thisx, PlayState* play);
void EnWiz_Draw(Actor* thisx, PlayState* play);

void func_80A46280(EnWiz* this, PlayState* play);
void func_80A462F8(EnWiz* this, PlayState* play);
void func_80A46414(EnWiz* this, PlayState* play);
void func_80A4668C(EnWiz* this);
void func_80A46764(EnWiz* this, PlayState* play);
void func_80A468CC(EnWiz* this, PlayState* play);
void func_80A46990(EnWiz* this, PlayState* play);
void func_80A46C88(EnWiz* this);
void func_80A46CC4(EnWiz* this, PlayState* play);
void func_80A46DDC(EnWiz* this);
void func_80A46E24(EnWiz* this, PlayState* play);
void func_80A47000(EnWiz* this);
void func_80A470D8(EnWiz* this, PlayState* play);
void func_80A473B8(EnWiz* this, PlayState* play);
void func_80A4767C(EnWiz* this);
void func_80A476C8(EnWiz* this, PlayState* play);

const ActorInit En_Wiz_InitVars = {
    ACTOR_EN_WIZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWiz),
    (ActorFunc)EnWiz_Init,
    (ActorFunc)EnWiz_Destroy,
    (ActorFunc)EnWiz_Update,
    (ActorFunc)EnWiz_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[10] = {
static ColliderJntSphElementInit D_80A48B50[10] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A48CB8 = {
    {
        COLTYPE_HIT2,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_80A48B50),
    D_80A48B50, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A48CC8 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x08, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 35, 130, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A48CF4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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
static DamageTable D_80A48D14 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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

static AnimationHeader* D_80A48D34[] = {
    &object_wiz_Anim_0066C0, &object_wiz_Anim_0025F0, &object_wiz_Anim_002458,
    &object_wiz_Anim_0060E8, &object_wiz_Anim_0007B0, &object_wiz_Anim_002218,
};

static u8 D_80A48D4C[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE,
};

void EnWiz_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    SkelAnime_InitFlex(play, &this->skelAnime, &object_wiz_Skel_00B320, &object_wiz_Anim_0066C0, this->jointTable,
                       this->morphTable, 20);
    SkelAnime_InitFlex(play, &this->skelAnime2, &object_wiz_Skel_00B320, &object_wiz_Anim_0066C0, this->jointTable2,
                       this->morphTable2, 20);
    Actor_SetScale(&this->actor, 0.0f);
    this->unk_3C4 = 0;
    this->unk_3C2 = 0xFF;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 3;
    this->unk_450 = 1.0f;
    this->actor.shape.yOffset = 700.0f;
    Collider_InitAndSetJntSph(play, &this->unk_454, &this->actor, &D_80A48CB8, this->unk_474);
    Collider_InitAndSetCylinder(play, &this->unk_6F4, &this->actor, &D_80A48CC8);
    this->unk_388 = Rand_S16Offset(0, 7);
    this->switchFlag = this->actor.params & 0x7F;
    this->unk_74A = (this->actor.params >> 8) & 0xFF;

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
        this->actor.colChkInfo.damageTable = &D_80A48CF4;
        this->actor.colChkInfo.health = 8;
        this->actor.flags &= ~ACTOR_FLAG_100000;
    } else {
        this->actor.colChkInfo.damageTable = &D_80A48D14;
        this->actor.colChkInfo.health = 6;
    }

    if ((this->switchFlag >= 0) && (Flags_GetSwitch(play, this->switchFlag))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.hintId = 0x4B;
        this->unk_748 = 0x309;
        this->unk_454.elements->dim.modelSphere.radius = 0;
        this->unk_454.elements->dim.scale = 0.0f;
        this->unk_454.elements->dim.modelSphere.center.x = 0;
        this->unk_454.elements->dim.modelSphere.center.y = 0;
        this->unk_454.elements->dim.modelSphere.center.z = 0;
        this->actionFunc = func_80A46280;
    }
}

void EnWiz_Destroy(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    Collider_DestroyCylinder(play, &this->unk_6F4);
    Collider_DestroyJntSph(play, &this->unk_454);
    if (this->unk_74A != 2) {
        func_801A2ED8();
    }
}

void EnWiz_ChangeAnim(EnWiz* this, s32 animIndex, s32 arg2) {
    this->endFrame = Animation_GetLastFrame(D_80A48D34[animIndex]);
    Animation_Change(&this->skelAnime, D_80A48D34[animIndex], 1.0f, 0.0f, this->endFrame, D_80A48D4C[animIndex], -2.0f);
    if (arg2 != 0) {
        Animation_Change(&this->skelAnime2, D_80A48D34[animIndex], 1.0f, 0.0f, this->endFrame, D_80A48D4C[animIndex],
                         -2.0f);
    }
}

void func_80A456A0(EnWiz* this, PlayState* play) {
    Camera* camera;
    Vec3f sp58;
    Vec3f sp4C;

    if (this->unk_3CB < 6) {
        camera = Play_GetCamera(play, this->unk_74E);
        switch (this->unk_3CB) {
            case 0:
                this->unk_3B4 = 100;
                this->unk_3C8 = this->actor.world.rot.y;
                this->unk_3CB++;
                break;

            case 1:
                Math_Vec3f_Copy(&sp58, &this->actor.world.pos);
                Math_Vec3f_Copy(&sp4C, &this->actor.world.pos);
                sp58.x += Math_SinS(this->unk_3C8) * 200.0f;
                sp58.y += 100.0f;
                sp58.z += Math_CosS(this->unk_3C8) * 200.0f;
                sp4C.y += 80.0f;
                Math_ApproachF(&camera->eye.x, sp58.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, sp58.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, sp4C.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, sp4C.z, 0.3f, 30.0f);
                camera->eye.y = sp58.y;
                camera->at.y = sp4C.y;
                if ((fabsf(camera->eye.x - sp58.x) < 2.0f) && (fabsf(camera->eye.y - sp58.y) < 2.0f) &&
                    (fabsf(camera->eye.z - sp58.z) < 2.0f) && (fabsf(camera->at.x - sp4C.x) < 2.0f) &&
                    (fabsf(camera->at.y - sp4C.y) < 2.0f) && (fabsf(camera->at.z - sp4C.z) < 2.0f)) {
                    Player* player = GET_PLAYER(play);
                    s32 i;

                    this->actor.world.rot.y = this->actor.shape.rot.y =
                        Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos);

                    for (i = 0; i < this->unk_740; i++) {
                        this->unk_894[i].y = Math_Vec3f_Yaw(&this->unk_81C[i], &player->actor.world.pos);
                    }

                    EnWiz_ChangeAnim(this, 0, true);
                    this->unk_3CA = 0;
                    this->unk_3C6 = 0xFF;
                    Math_Vec3f_Copy(&this->unk_414, &this->actor.world.pos);
                    if (this->unk_3B6 == 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_UNARI);
                    } else {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
                    }

                    this->unk_3B4 = 40;
                    this->unk_3CB++;
                }
                break;

            case 2:
                if (this->unk_3B4 == 0) {
                    this->unk_3B4 = 20;
                    this->unk_3CB++;
                }
                break;

            case 3:
                Math_Vec3f_Copy(&sp58, &this->actor.world.pos);
                Math_Vec3f_Copy(&sp4C, &this->actor.world.pos);
                sp58.x += Math_SinS(this->actor.world.rot.y) * 160.0f;
                sp58.y += 70.0f;
                sp58.z += Math_CosS(this->actor.world.rot.y) * 140.0f;
                sp4C.x += -10.0f;
                sp4C.y += 100.0f;
                Math_ApproachF(&camera->eye.x, sp58.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, sp58.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, sp4C.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, sp4C.z, 0.3f, 30.0f);
                camera->eye.y = sp58.y;
                camera->at.y = sp4C.y;
                if (this->unk_3B4 == 0) {
                    this->unk_3B4 = 10;
                    this->unk_3CB++;
                    this->unk_3C8 = this->actor.world.rot.y;
                }
                break;

            case 4:
                if (this->unk_3B4 == 0) {
                    EnWiz_ChangeAnim(this, 1, false);
                    this->unk_3C0 = 0;
                    this->unk_3B4 = 34;
                    this->unk_3CB++;
                }
                break;

            case 5:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
                if (this->unk_3B4 == 0) {
                    this->unk_44C = this->unk_3C8 = 0;
                    this->unk_3CB = 6;
                } else {
                    Math_SmoothStepToS(&this->unk_3C0, 0x1388, 0x64, 0x3E8, 0x3E8);
                    this->actor.world.rot.y += this->unk_3C0;
                }

                Math_Vec3f_Copy(&sp58, &this->actor.world.pos);
                Math_Vec3f_Copy(&sp4C, &this->actor.world.pos);
                sp58.x += Math_SinS(this->unk_3C8) * 200.0f;
                sp58.y += 100.0f;
                sp58.z += Math_CosS(this->unk_3C8) * 200.0f;
                sp4C.y += 80.0f;
                Math_ApproachF(&camera->eye.x, sp58.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, sp58.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, sp4C.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, sp4C.z, 0.3f, 30.0f);
                camera->eye.y = sp58.y;
                camera->at.y = sp4C.y;
                break;
        }

        if (this->unk_3CC < 0xB) {
            this->unk_3CC++;
            if ((this->unk_74A != 2) && (this->unk_3CC == 0xB)) {
                func_801A2E54(0x38);
            }
        }
    }
}

void func_80A45CD8(EnWiz* this, PlayState* play) {
    Actor* prop;
    s32 i;
    s32 j;
    s16 var_s0;
    s16 var_v1;
    s16 var_fp;

    for (i = 0; i < ARRAY_COUNT(this->unk_420); i++) {
        this->unk_420[i] = NULL;
    }

    prop = play->actorCtx.actorLists[ACTORCAT_PROP].first;
    i = 0;
    while (prop != NULL) {
        if (prop->id != ACTOR_EN_WIZ_BROCK) {
            prop = prop->next;
            continue;
        }

        this->unk_420[i] = prop;
        i++;
        if (this->unk_3B0 != 6) {
            var_v1 = this->unk_74A;
            if (var_v1 == 2) {
                var_v1 = 0;
            }
            prop->colChkInfo.health = var_v1 + 1;
            prop = prop->next;
        } else {
            prop->colChkInfo.health = 0;
            prop = prop->next;
        }
    }

    if (this->unk_3B0 != 5) {
        this->unk_740 = i;
        if (i < 0) {
            i = 0;
        } else if (this->unk_740 > 10) {
            this->unk_740 = 10;
        }

        var_fp = Rand_ZeroFloat(i);
        while ((this->unk_748 == var_fp) || ((s16)i == var_fp)) {
            var_fp = Rand_ZeroFloat(i);
            if (1) {}
        }

        this->unk_748 = var_fp;
        switch (this->unk_3B6) {
            case 0:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_420[var_fp]->world.pos);
                break;

            case 1:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_420[0]->world.pos);
                for (i = 0, var_s0 = 128; i < this->unk_740; i++, var_s0 -= 10) {
                    Math_Vec3f_Copy(&this->unk_81C[i], &this->actor.world.pos);
                    this->unk_7F2[i] = var_s0;
                }
                break;

            default:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_420[var_fp]->world.pos);
                for (i--; i >= 0; i--) {
                    if (var_fp != i) {
                        Math_Vec3f_Copy(&this->unk_81C[i], &this->unk_420[i]->world.pos);
                        this->unk_894[i] = this->actor.world.rot;
                        this->unk_7F2[i] = 0x64;
                        this->unk_806[i] = i;
                        for (j = 0; j < ARRAY_COUNT(this->jointTable); j++) {
                            this->jointTable3[i][j] = this->jointTable[j];
                        }
                    } else {
                        Math_Vec3f_Copy(&this->unk_81C[i], &gZeroVec3f);
                    }
                }
                break;
        }
    }
}

void func_80A460A4(EnWiz* this) {
    s32 i;
    s32 j;
    s32 playSfx = false;

    for (i = 0; i < this->unk_740; i++) {
        if (this->unk_81C[i].x != 0.0f && this->unk_81C[i].z != 0.0f) {
            f32 diffX;
            f32 diffZ;

            j = this->unk_806[i];
            diffX = this->unk_420[j]->world.pos.x - this->unk_81C[i].x;
            diffZ = this->unk_420[j]->world.pos.z - this->unk_81C[i].z;
            playSfx++;

            if (sqrtf(SQ(diffX) + SQ(diffZ)) < 30.0f) {
                this->unk_806[i]--;
                if (this->unk_806[i] < 0) {
                    this->unk_806[i] = this->unk_740 - 1;
                }
            }

            j = this->unk_806[i];
            Math_ApproachF(&this->unk_81C[i].x, this->unk_420[j]->world.pos.x, 0.3f, 30.0f);
            Math_ApproachF(&this->unk_81C[i].y, this->unk_420[j]->world.pos.y, 0.3f, 30.0f);
            Math_ApproachF(&this->unk_81C[i].z, this->unk_420[j]->world.pos.z, 0.3f, 30.0f);
            this->unk_894[i].y = Math_Vec3f_Yaw(&this->unk_81C[i], &this->unk_420[j]->world.pos);
        }
    }

    if (playSfx) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    }
}

void func_80A46280(EnWiz* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetFlag(this->actor.cutscene, &this->actor);
        this->unk_74E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
        this->actor.flags |= ACTOR_FLAG_100000;
        func_80A462F8(this, play);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80A462F8(EnWiz* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;
    s16 angle;

    this->unk_3B0 = 1;

    if (this->unk_3B2 == 0) {
        func_80A45CD8(this, play);

        if (this->unk_3CB != 0) {
            angle = Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos);
            this->actor.shape.rot.y = angle;
            this->actor.world.rot.y = angle;
            for (i = 0; i < this->unk_740; i++) {
                this->unk_894[i].y = Math_Vec3f_Yaw(&this->unk_81C[i], &player->actor.world.pos);
            }

            EnWiz_ChangeAnim(this, 0, true);
            this->unk_3CA = 0;
            this->unk_3C6 = 0xFF;
            Math_Vec3f_Copy(&this->unk_414, &this->actor.world.pos);

            if (this->unk_3B6 == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_UNARI);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
            }
        }

        this->actionFunc = func_80A46414;
    }
}

void func_80A46414(EnWiz* this, PlayState* play) {
    Vec3f sp3C = { 0.006f, 0.006f, 0.006f };
    Player* player = GET_PLAYER(play);

    func_80A456A0(this, play);
    if (this->unk_3CB >= 2) {
        SkelAnime_Update(&this->skelAnime);
        if ((this->unk_3B6 == 0) && (this->unk_3CB >= 6) &&
            ((this->actor.xzDistToPlayer < 200.0f) ||
             ((player->unk_D57 != 0) &&
              ((ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x7D0)) &&
              (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, BINANG_ADD(player->actor.shape.rot.y, 0x8000))) <
               0x7D0)))) {
            func_80A47000(this);
        } else {
            Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0xBB8, 0);

            if (this->unk_3B6 == 0) {
                Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 0xA, 0xA, 0xA);
                if (this->unk_3CA == 0) {
                    this->unk_3B2 = 0x14;
                    this->unk_3CA = 1;
                }
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
            }

            if (this->unk_3B2 == 0) {
                Math_ApproachF(&this->unk_3D4, 0.015f, 0.05f, 0.01f);
                Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
            }

            if (this->unk_3D4 < 0.0138f) {
            } else {
                this->unk_3B0 = 7;
                this->actor.flags &= ~ACTOR_FLAG_8000000;
                this->unk_454.elements->info.bumper.dmgFlags = 0x01013A22;
                Math_Vec3f_Copy(&this->unk_3F0, &sp3C);
                this->unk_3C6 = 0;
                if (this->unk_3CB == 6) {
                    this->unk_3B2 = 0;
                    this->unk_3B4 = 20;
                    func_80A47000(this);
                } else if (this->unk_3CB >= 7) {
                    if (this->unk_3B6 == 1) {
                        this->actionFunc = func_80A468CC;
                    } else {
                        func_80A4668C(this);
                    }
                }
            }
        }
    }
}

void func_80A4668C(EnWiz* this) {
    EnWiz_ChangeAnim(this, 2, 0);
    Math_ApproachF(&this->unk_3D4, 0.015f, 0.05f, 0.001f);
    this->unk_3C0 = 0;
    this->unk_44C = 0;
    this->unk_3B0 = 9;
    if (this->unk_3B6 >= 2) {
        Animation_Change(&this->skelAnime2, &object_wiz_Anim_0025F0, 1.0f, 0.0f,
                         Animation_GetLastFrame(&object_wiz_Anim_0025F0), ANIMMODE_LOOP, 0.0f);
        this->unk_3B6 = 3;
    }

    Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
    this->actionFunc = func_80A46764;
}

void func_80A46764(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
    Math_ApproachF(&this->unk_3D4, 0.015f, 0.05f, 0.001f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    this->actor.world.rot.y += this->unk_3C0;
    if (this->unk_3B6 >= 3) {
        func_80A460A4(this);
    } else {
        for (i = 0; i < this->unk_740; i++) {
            this->unk_894[i].y += this->unk_3C0;
        }
    }

    Math_SmoothStepToS(&this->unk_3C0, 0x1388, 0x64, 0x3E8, 0x3E8);
    Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 0x14, 0x32, 0xA);
    if (this->endFrame <= curFrame) {
        if (this->unk_44C < 10) {
            this->unk_44C++;
        }
    }

    if ((this->unk_44C >= 3) && (this->unk_3BA == 0)) {
        this->unk_3C6 = 0;
        func_80A46C88(this);
    }
}

void func_80A468CC(EnWiz* this, PlayState* play) {
    s16 temp_v0 = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

    if (!ActorCutscene_GetCanPlayNext(temp_v0)) {
        ActorCutscene_SetIntentToPlay(temp_v0);
    } else {
        ActorCutscene_StartAndSetFlag(temp_v0, &this->actor);
        this->unk_74E = ActorCutscene_GetCurrentSubCamId(temp_v0);
        this->actor.flags |= ACTOR_FLAG_100000;
        EnWiz_ChangeAnim(this, 2, false);
        this->unk_3B0 = 2;
        this->unk_744 = 1;
        this->unk_3BC = 0;
        Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
        this->actionFunc = func_80A46990;
    }
}

void func_80A46990(EnWiz* this, PlayState* play) {
    Camera* camera;
    s32 i;

    Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
    camera = Play_GetCamera(play, this->unk_74E);
    Math_Vec3f_Copy(&camera->at, &this->actor.focus.pos);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    if (this->unk_420[this->unk_744] != NULL) {
        f32 diffX = this->actor.world.pos.x - this->unk_420[this->unk_744]->world.pos.x;
        f32 diffZ = this->actor.world.pos.z - this->unk_420[this->unk_744]->world.pos.z;
        s32 pad;

        if (sqrtf(SQ(diffX) + SQ(diffZ)) < 30.0f) {
            if (this->unk_3BC == 0) {
                this->unk_744++;
                if (this->unk_744 >= this->unk_740) {
                    this->unk_3BC = 1;
                    this->unk_744 = 0;
                }
            } else {
                f32 diffX = this->actor.world.pos.x - this->unk_81C[this->unk_740].x;
                f32 diffZ = this->actor.world.pos.z - this->unk_81C[this->unk_740].z;
                s32 pad;
                s32 i;

                this->actor.flags |= ACTOR_FLAG_8000000;
                if (sqrtf(SQ(diffX) + SQ(diffZ)) < 20.0f) {
                    for (i = 0; i < this->unk_740; i++) {
                        Math_Vec3f_Copy(&this->unk_81C[i], &gZeroVec3f);
                    }

                    this->unk_744 = 0;
                    this->unk_740 = 0;
                    this->unk_3B6 = 2;
                    this->unk_3B2 = 0;
                    ActorCutscene_Stop(ActorCutscene_GetAdditionalCutscene(this->actor.cutscene));
                    this->actor.flags &= ~ACTOR_FLAG_100000;
                    func_80A47000(this);
                    return;
                }
            }
        }
    }

    Math_Vec3f_Copy(this->unk_81C, &this->actor.world.pos);
    this->unk_894[0].y = this->actor.world.rot.y;
    Math_ApproachF(&this->actor.world.pos.x, this->unk_420[this->unk_744]->world.pos.x, 0.3f, 30.0f);
    Math_ApproachF(&this->actor.world.pos.y, this->unk_420[this->unk_744]->world.pos.y, 0.3f, 30.0f);
    Math_ApproachF(&this->actor.world.pos.z, this->unk_420[this->unk_744]->world.pos.z, 0.3f, 30.0f);
    for (i = this->unk_740; i > 0; i--) {
        Math_Vec3f_Copy(&this->unk_81C[i], &this->unk_81C[i - 1]);
        this->unk_894[i].y = this->unk_894[i - 1].y;
    }

    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_420[this->unk_744]->world.pos);
}

void func_80A46C88(EnWiz* this) {
    EnWiz_ChangeAnim(this, 3, 0);
    this->unk_44C = 0;
    this->actionFunc = func_80A46CC4;
}

void func_80A46CC4(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xC8, 0x1F40, 0x1388);
    if (this->unk_3B6 >= 3) {
        func_80A460A4(this);
    } else {
        for (i = 0; i < this->unk_740; i++) {
            Math_SmoothStepToS(&this->unk_894[i].y, this->actor.yawTowardsPlayer, 0xC8, 0x1F40, 0x1388);
        }
    }

    if (this->endFrame <= curFrame) {
        this->unk_44C++;
        if (this->unk_44C >= 2) {
            func_80A46DDC(this);
        }
    }

    Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 0xA, 0xA, 0xA);
}

void func_80A46DDC(EnWiz* this) {
    EnWiz_ChangeAnim(this, 4, 0);
    this->unk_3B2 = 0;
    this->unk_3CA = 0;
    this->unk_3B0 = 8;
    this->actionFunc = func_80A46E24;
}

void func_80A46E24(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_3B6 >= 3) {
        func_80A460A4(this);
    }

    if (this->unk_3B2 == 0) {
        if ((Animation_OnFrame(&this->skelAnime, 6.0f)) && (this->unk_3BA == 0)) {
            Player* player = GET_PLAYER(play);
            Vec3f sp54;
            s32 sp50 = this->unk_74A;

            Math_Vec3f_Copy(&sp54, &this->actor.world.pos);
            sp54.x += Math_SinS(this->actor.world.rot.y) * 40.0f;
            sp54.y += 60.0f;
            sp54.z += Math_CosS(this->actor.world.rot.y) * 40.0f;
            if (sp50 == 2) {
                sp50 = 0;
            }

            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_WIZ_FIRE, sp54.x, sp54.y, sp54.z,
                               Math_Vec3f_Pitch(&sp54, &player->actor.world.pos),
                               Math_Vec3f_Yaw(&sp54, &player->actor.world.pos), 0, sp50 * 4);
            this->unk_3BA = 1;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_ATTACK);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_MAGIC_FIRE);
        }

        if ((curFrame >= 8.0f) && (this->unk_3CA == 0)) {
            this->unk_3B2 = 3;
            this->unk_3CA = 1;
        }

        if (this->endFrame <= curFrame) {
            func_80A47000(this);
        }
    }
}

void func_80A47000(EnWiz* this) {
    if (this->unk_3B0 != 4) {
        this->unk_3C0 = 0x2710;
        this->unk_3B2 = 0;
        EnWiz_ChangeAnim(this, 0, 0);
        this->unk_3B0 = 3;
    } else {
        this->unk_3C0 = 0x2710;
        this->actor.world.rot.y += this->unk_3C0;
    }

    this->unk_3C6 = 0;
    this->actor.flags |= ACTOR_FLAG_8000000;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    Math_SmoothStepToS(&this->unk_3C0, 0x1388, 0x64, 0x3E8, 0x3E8);
    this->actor.world.rot.y += this->unk_3C0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_80A470D8;
}

void func_80A470D8(EnWiz* this, PlayState* play) {
    s32 i;

    Math_SmoothStepToS(&this->unk_3C0, 0, 0xA, 0xBB8, 0x14);
    this->actor.world.rot.y += this->unk_3C0;
    if ((this->unk_3B6 == 0) || (this->unk_3B0 == 4)) {
        Math_ApproachZeroF(&this->unk_3D4, 0.3f, 0.01f);
        Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 5, 0x32, 0);
    } else {
        Math_ApproachZeroF(&this->unk_3D4, 0.3f, 0.001f);
        Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 0xA, 0x32, 0);
        for (i = 0; i < this->unk_740; i++) {
            this->unk_894[i].y += this->unk_3C0;
        }
    }

    Math_Vec3f_Copy(&this->unk_3F0, &gZeroVec3f);
    if (this->unk_3D4 < 0.001f) {
        this->unk_3D4 = 0.0f;
        if ((this->unk_3CB == 6) && (this->unk_3B4 == 0)) {
            this->unk_3CB = 7;
            ActorCutscene_Stop(this->actor.cutscene);
            this->actor.flags &= ~ACTOR_FLAG_100000;
        }

        if (this->unk_3CB != 6) {
            this->unk_3C2 = 0;
            if (this->unk_3B6 == 0) {
                this->unk_454.elements->info.bumper.dmgFlags = 0x01000202;
            }

            this->actor.flags |= ACTOR_FLAG_1;
            this->actionFunc = func_80A462F8;
        }
    }
}

void func_80A47298(EnWiz* this, PlayState* play) {
    EnWiz_ChangeAnim(this, 5, 0);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
    this->unk_3B2 = 0x14;

    if ((this->unk_3B6 != 0) && (this->actor.colChkInfo.health <= 0)) {
        Enemy_StartFinishingBlow(play, &this->actor);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DEAD);
        this->unk_3B2 = 0;
        this->actor.flags &= ~ACTOR_FLAG_1;
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DAMAGE);
    }

    this->unk_3D4 = 0.015f;
    this->unk_740 = 0;
    this->unk_3C6 = 0;
    if ((this->drawDmgEffTimer != 0) &&
        ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) || (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_LIGHT_ORBS))) {
        this->unk_3B2 = 0;
    }

    this->unk_3C0 = 0x4E20;
    if ((this->drawDmgEffTimer != 0) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX)) {
        this->unk_3C0 = 0;
        this->unk_3B2 = 0;
    }

    this->unk_3B0 = 4;
    this->actionFunc = func_80A473B8;
}

void func_80A473B8(EnWiz* this, PlayState* play) {
    s32 i;

    if ((this->drawDmgEffTimer < 50) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX)) {
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 1.0f, 0.7f);
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->unk_3C0 = 0x4E20;
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
    }

    if ((this->drawDmgEffTimer != 0) && (this->drawDmgEffTimer < 30) &&
        ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) || (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_LIGHT_ORBS))) {
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    } else if ((this->unk_750 == 0) && (this->unk_3B6 != 0) && (this->actor.colChkInfo.health <= 0)) {
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
        this->unk_750 = 1;
    }

    this->actor.world.rot.y += this->unk_3C0;
    Math_SmoothStepToS(&this->unk_3C0, 0, 0xA, 0xBB8, 0x14);
    for (i = 0; i < this->unk_740; i++) {
        this->unk_894[i].y += this->unk_3C0;
    }

    if ((this->unk_3B2 == 1) || ((this->actor.velocity.y < 0.0f) &&
                                 (this->actor.world.pos.y < (this->unk_420[this->unk_748]->world.pos.y + 11.0f)))) {
        this->unk_3B2 = 0;
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        this->drawDmgEffTimer = this->unk_3B2;
        this->drawDmgEffType = this->unk_3B2;
        if (this->actor.colChkInfo.health <= 0) {
            if (this->unk_3B6 == 0) {
                this->unk_3B6 = 1;
                if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
                    this->actor.colChkInfo.health = 8;
                } else {
                    this->actor.colChkInfo.health = 6;
                }

                func_80A47000(this);
            } else {
                func_80A4767C(this);
            }
        } else {
            func_80A47000(this);
        }

        this->actor.flags |= ACTOR_FLAG_8000000;
    }

    Math_SmoothStepToS(&this->unk_3C4, this->unk_3C6, 0x14, 0x32, 0xA);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 35.0f, 40.0f, 40.0f, 0x1F);
}

void func_80A4767C(EnWiz* this) {
    EnWiz_ChangeAnim(this, 5, 0);
    this->unk_3C0 = 0x2710;
    this->unk_3B0 = 5;
    this->unk_3B2 = 0;
    this->actionFunc = func_80A476C8;
}

void func_80A476C8(EnWiz* this, PlayState* play) {
    s32 i;

    this->actor.world.rot.y += this->unk_3C0;
    Math_SmoothStepToS(&this->unk_3C0, 0, 0xA, 0xBB8, 0x14);
    if (this->unk_3C0 < 0x1E) {
        Math_SmoothStepToS(&this->unk_3C2, 0, 0xA, 0x1E, 0x14);
        for (i = 0; i < this->unk_740; i++) {
            Math_SmoothStepToS(&this->unk_7F2[i], 0, 0xA, 0x1E, 0x14);
        }

        this->unk_3B0 = 6;
    }

    if (this->unk_3C2 < 0x1E) {
        func_80A45CD8(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EN_EXTINCT);
        Actor_MarkForDeath(&this->actor);
        if (this->switchFlag >= 0) {
            Flags_SetSwitch(play, this->switchFlag);
        }
    }
}

static Color_RGBA8 D_80A48D60 = { 250, 250, 250, 255 };

static Color_RGBA8 D_80A48D64 = { 180, 180, 180, 255 };

void func_80A477E8(EnWiz* this, PlayState* play) {
    s32 i;
    s32 attackDealsDamage = false;

    if (this->unk_6F4.base.acFlags & AC_HIT) {
        this->unk_454.base.acFlags &= ~AC_HIT;
        if (this->unk_3B0 < 7) {
            return;
        }

        switch (this->actor.colChkInfo.damageEffect) {
            case 0xF:
                attackDealsDamage = true;
                break;

            case 2:
                if (this->unk_74A == 1) {
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                }

                attackDealsDamage = true;
                break;

            case 3:
                if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
                    this->drawDmgEffTimer = 80;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_SFX;
                    this->drawDmgEffScale = 0.0f;
                    this->drawDmgEffFrozenSteamScale = 1.5f;
                }

                Actor_ApplyDamage(&this->actor);
                func_80A47298(this, play);
                break;

            case 4:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    (this->drawDmgEffTimer == 0)) {
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    attackDealsDamage = true;
                }
                break;
        }

        this->unk_3C2 = 0xFF;
        if (attackDealsDamage) {
            Actor_ApplyDamage(&this->actor);
            func_80A47298(this, play);
            return;
        }
    }

    if ((this->unk_740 != 0) && (this->unk_3B6 != 1)) {
        for (i = 0; i < this->unk_740; i++) {
            Vec3f accel;
            Vec3f velocity;
            Vec3f pos;
            f32 temp_fs0;
            s32 j;

            if ((iREG(50) != 0) || (this->unk_454.elements[i + 1].info.bumperFlags & BUMP_HIT)) {
                this->unk_3B6 = 2;
                this->unk_454.base.acFlags &= ~BUMP_HIT;
                if (this->unk_81C[i].x != .0f || this->unk_81C[i].z != .0f) {
                    for (j = 0; j < 9; j++) {
                        accel.x = 0.0f;
                        accel.y = 1.0f;
                        accel.z = 0.0f;
                        velocity.x = 0.0f;
                        velocity.y = 1.0f;
                        velocity.z = 0.0f;
                        temp_fs0 = Rand_S16Offset(20, 10);
                        Math_Vec3f_Copy(&pos, &this->unk_81C[i]);
                        pos.x += (f32)Rand_S16Offset(20, 20) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
                        pos.y += 70.0f + randPlusMinusPoint5Scaled(30.0f);
                        pos.z += (f32)Rand_S16Offset(20, 20) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
                        func_800B0DE0(play, &pos, &velocity, &accel, &D_80A48D60, &D_80A48D64, Rand_S16Offset(350, 100),
                                      temp_fs0);
                    }

                    SoundSource_PlaySfxAtFixedWorldPos(play, &this->unk_81C[i], 50, NA_SE_EN_WIZ_LAUGH);
                    Math_Vec3f_Copy(&this->unk_81C[i], &gZeroVec3f);
                }
            }
        }
    }
}

void EnWiz_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;
    s32 i;
    s32 j;

    if (this->unk_3B0 != 1) {
        SkelAnime_Update(&this->skelAnime);
        SkelAnime_Update(&this->skelAnime2);
    }

    Actor_SetFocus(&this->actor, 60.0f);
    Actor_SetScale(&this->actor, this->unk_3D4);
    func_80A477E8(this, play);
    this->actionFunc(this, play);

    this->actor.shape.rot.y = this->actor.world.rot.y;

    DECR(this->unk_3B2);
    DECR(this->unk_3B4);
    DECR(this->drawDmgEffTimer);

    this->unk_6F4.dim.radius = 35;
    this->unk_6F4.dim.height = 130;
    this->unk_6F4.dim.yShift = 0;
    if (this->unk_3B0 >= 7) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_454.base);
        Collider_UpdateCylinder(&this->actor, &this->unk_6F4);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_6F4.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_6F4.base);
    }

    Math_ApproachF(&this->unk_3E4, this->unk_3F0.x, 0.3f, 0.002f);
    Math_ApproachF(&this->unk_3E8, this->unk_3F0.y, 0.3f, 0.002f);
    Math_ApproachF(&this->unk_3EC, this->unk_3F0.z, 0.3f, 0.002f);

    if (this->unk_3B6 == 0) {
        this->unk_740 = 0;
    } else if (this->unk_3B6 == 3) {
        for (i = 0; i < this->unk_740; i++) {
            for (j = 0; j < ARRAY_COUNT(this->jointTable2); j++) {
                this->jointTable3[i][j] = this->jointTable2[j];
            }
        }
    } else {
        for (i = 0; i < this->unk_740; i++) {
            for (j = 0; j < ARRAY_COUNT(this->jointTable); j++) {
                this->jointTable3[i][j] = this->jointTable[j];
            }
        }
    }
}

void func_80A47FCC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    EnWiz* this = THIS;

    if (limbIndex == 9) {
        sp24.x = 7300.0f;
        sp24.y = -1500.0f;
        if (this->unk_3B0 != 9) {
            sp24.y = 0.0f;
            sp24.x = 5300.0f;
        }

        Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultVec3f(&sp24, &this->unk_3D8);
    }

    Collider_UpdateSpheres(limbIndex, &this->unk_454);

    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) ||
        (limbIndex == 7) || (limbIndex == 0xA) || (limbIndex == 0xB) || (limbIndex == 0xC) || (limbIndex == 0xF) ||
        (limbIndex == 0x12) || (limbIndex == 0xD)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

void func_80A48138(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnWiz* this = THIS;

    if (this->unk_3B0 != 6) {
        if (limbIndex == 9) {
            sp4C.x = 7300.0f;
            sp4C.y = -1500.0f;
            if (this->unk_3B0 != 9) {
                sp4C.y = 0.0f;
                sp4C.x = 5300.0f;
            }

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &this->unk_3D8);
        }
    } else {
        if (this->unk_3B2 == 0) {
            Vec3f sp38;

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &sp38);
            sp38.x += randPlusMinusPoint5Scaled(4.0f);
            sp38.y += randPlusMinusPoint5Scaled(7.0f);
            sp38.z += randPlusMinusPoint5Scaled(5.0f);
            func_800B3030(play, &sp38, &gZeroVec3f, &gZeroVec3f, ((Rand_ZeroFloat(1.0f) * 50.0f) + 70.0f), 10, 1);
            SoundSource_PlaySfxAtFixedWorldPos(play, &sp38, 10, NA_SE_EN_EXTINCT);
        }

        if ((limbIndex >= 0x13) && (this->unk_3B2 == 0)) {
            this->unk_3B2 = 4;
        }
    }

    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) ||
        (limbIndex == 7) || (limbIndex == 0xA) || (limbIndex == 0xB) || (limbIndex == 0xC) || (limbIndex == 0xF) ||
        (limbIndex == 0x12) || (limbIndex == 0xD)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

void EnWiz_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);

    if ((this->unk_3B0 == 6) || (this->unk_3C2 != 0xFF)) {
        Scene_SetRenderModeXlu(play, 1, 2);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_3C2);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               NULL, func_80A48138, &this->actor, POLY_XLU_DISP);
    } else {
        Scene_SetRenderModeXlu(play, 0, 1);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, this->unk_3C2);
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                              NULL, func_80A47FCC, &this->actor);
    }

    if (this->drawDmgEffTimer != 0) {
        f32 drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;

        if ((this->drawDmgEffType == 0xB) || (this->drawDmgEffType == 0xA)) {
            this->drawDmgEffScale += 0.3f;
            if (this->drawDmgEffScale > 0.5f) {
                this->drawDmgEffScale = 0.5f;
            }

            Math_ApproachF(&this->drawDmgEffFrozenSteamScale, this->drawDmgEffScale, 0.1f, 0.04f);
        } else {
            this->drawDmgEffScale = 0.8f;
            this->drawDmgEffFrozenSteamScale = 0.8f;
        }

        Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, drawDmgEffAlpha,
                                this->drawDmgEffType);
    }

    if (this->unk_740 > 0) {
        s32 i;
        s16 var_v0;

        Matrix_Push();

        var_v0 = this->unk_740;
        if (this->unk_3B6 == 1) {
            var_v0 = 10;
        }

        for (i = 0; i < var_v0; i++) {
            func_8012C28C(play->state.gfxCtx);
            func_8012C2DC(play->state.gfxCtx);

            if (this->unk_81C[i].x != 0.0f && this->unk_81C[i].z != 0.0f) {
                Matrix_Translate(this->unk_81C[i].x, this->unk_81C[i].y + 10.0f, this->unk_81C[i].z, MTXMODE_NEW);
                Matrix_Scale(this->unk_3D4, this->unk_3D4, this->unk_3D4, MTXMODE_APPLY);
                Matrix_RotateYS(this->unk_894[i].y, MTXMODE_APPLY);
                Matrix_RotateXS(this->unk_894[i].x, MTXMODE_APPLY);
                Matrix_RotateZS(this->unk_894[i].z, MTXMODE_APPLY);
                Scene_SetRenderModeXlu(play, 1, 2);
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_7F2[i]);
                POLY_XLU_DISP =
                    SkelAnime_DrawFlex(play, this->skelAnime2.skeleton, this->jointTable3[i],
                                       this->skelAnime2.dListCount, NULL, NULL, &this->actor, POLY_XLU_DISP);
                this->unk_454.elements[i + 1].dim.worldSphere.center.x = this->unk_81C[i].x;
                this->unk_454.elements[i + 1].dim.worldSphere.center.y = this->unk_81C[i].y + 50.0f;
                this->unk_454.elements[i + 1].dim.worldSphere.center.z = this->unk_81C[i].z;
                this->unk_454.elements[i + 1].dim.worldSphere.radius = this->unk_454.elements->dim.modelSphere.radius;
                this->unk_454.elements[i + 1].dim.scale = this->unk_454.elements->dim.scale;
            }
        }

        Matrix_Pop();
    }

    func_8012C2DC(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    if (this->unk_3B6 == 0) {
        Matrix_Push();

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&object_wiz_Matanimheader_00211C));
        Matrix_Translate(this->unk_414.x, this->unk_414.y, this->unk_414.z, MTXMODE_NEW);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->unk_3C4);

        if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 100, 255);
        } else {
            gDPSetEnvColor(POLY_XLU_DISP++, 50, 0, 255, 255);
        }

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_001860);

        Matrix_Pop();
    }

    Matrix_Translate(this->unk_3D8.x, this->unk_3D8.y, this->unk_3D8.z, MTXMODE_NEW);
    Matrix_Scale(this->unk_3E4, this->unk_3E8, this->unk_3EC, MTXMODE_APPLY);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0,
                                ((this->unk_388 * 10) - (play->state.frames * 20)) % 512, 32, 128));
    gDPPipeSync(POLY_XLU_DISP++);

    if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 50, 0, 255);
    } else {
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 170, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 255, 255);
    }

    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);

    CLOSE_DISPS(play->state.gfxCtx);
}
