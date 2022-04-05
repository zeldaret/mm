/*
 * File: z_boss_06.c
 * Overlay: ovl_Boss_06
 * Description: Igos du Ikana window - curtains and ray effects
 */

#include "z_boss_06.h"
#include "overlays/actors/ovl_En_Knight/z_en_knight.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_knight/object_knight.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss06*)thisx)

void Boss06_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809F24A8(Boss06* this);
void func_809F24C8(Boss06* this, GlobalContext* globalCtx);
void func_809F2B64(Boss06* this, GlobalContext* globalCtx);
void func_809F2C44(Boss06* this, GlobalContext* globalCtx);
void func_809F2E14(Boss06* this, GlobalContext* globalCtx);
void func_809F2E34(Boss06* this, GlobalContext* globalCtx);
void func_809F2ED0(Boss06* this, GlobalContext* globalCtx);
void func_809F2EE8(Boss06* this, GlobalContext* globalCtx);

static Vec3f D_809F4370[128];
static EnKnight* D_809F4970;
static s32 D_809F4974;
static s32 D_809F4978;
static s32 D_809F497C;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

const ActorInit Boss_06_InitVars = {
    ACTOR_BOSS_06,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(Boss06),
    (ActorFunc)Boss06_Init,
    (ActorFunc)Boss06_Destroy,
    (ActorFunc)Boss06_Update,
    (ActorFunc)Boss06_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7FFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 90, 140, 10, { 0, 0, 0 } },
};

static Vec3f D_809F40EC[] = {
    { 1081.0f, 235.0f, 3224.0f },
    { 676.0f, 235.0f, 3224.0f },
};

void func_809F2120(s32 arg0, s32 arg1, s32 arg2) {
    D_809F4974 = arg0;
    D_809F4978 = arg1;
    D_809F497C = arg2;
}

f32 func_809F2140(void) {
    f32 temp_f2;

    D_809F4974 = (D_809F4974 * 171) % 30269;
    D_809F4978 = (D_809F4978 * 172) % 30307;
    D_809F497C = (D_809F497C * 170) % 30323;
    temp_f2 = (D_809F4974 / 30269.0f) + (D_809F4978 / 30307.0f) + (D_809F497C / 30323.0f);

    while (temp_f2 >= 1.0f) {
        temp_f2 -= 1.0f;
    }

    return fabsf(temp_f2);
}

void Boss06_Init(Actor* thisx, GlobalContext* globalCtx) {
    Boss06* this = THIS;
    u8* temp_v0;
    s32 i;

    D_809F4970 = (EnKnight*)this->actor.parent;
    this->actor.colChkInfo.damageTable = &sDamageTable;

    if ((KREG(64) != 0) || (gSaveContext.eventInf[5] & 0x80)) {
        this->actionFunc = func_809F2E14;
    } else {
        this->actionFunc = func_809F2B64;
    }

    Actor_SetScale(&this->actor, 0.1f);
    Math_Vec3f_Copy(&this->actor.world.pos, &D_809F40EC[ENBOSS06_GET_PARAMS(&this->actor)]);
    this->actor.shape.rot.y = -0x8000;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    temp_v0 = SEGMENTED_TO_VIRTUAL(&object_knight_Tex_019490);
    for (i = 0; i < ARRAY_COUNT(this->unk_200); i++) {
        this->unk_200[i] = temp_v0[i];
    }

    this->actor.flags &= ~ACTOR_FLAG_1;
}

void Boss06_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_809F23CC(Boss06* this) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->unk_1C9 == 0) && (D_809F4970->unk_68A == 0)) {
            if (this->actor.colChkInfo.damageEffect == 2) {
                func_809F24A8(this);
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);

                this->unk_1B0 = -(this->actor.world.pos.x - this->collider.info.bumper.hitPos.x);
                this->unk_1BC = this->unk_1B0 * 0.35f;

                this->unk_1B4 = -((this->actor.world.pos.y + 80.0f) - this->collider.info.bumper.hitPos.y);
                this->unk_1C0 = this->unk_1B4 * -0.35f;
            }
        }
    }
}

void func_809F24A8(Boss06* this) {
    this->actionFunc = func_809F24C8;
    this->unk_A28 = 0.0f;
    this->unk_1AC = 0.0f;
}

#ifdef NON_MATCHING
// Weird loading of 1
void func_809F24C8(Boss06* this, GlobalContext* globalCtx) {
    s16 sp4E = 0;
    Player* player = GET_PLAYER(globalCtx);
    Actor* temp_s0;
    Actor* temp_v0_2;
    Actor* child;

    this->unk_1CA++;

    switch (this->unk_1C9) {
        case 0:
            if (ActorCutscene_GetCurrentIndex() != -1) {
                break;
            }

            Cutscene_Start(globalCtx, &globalCtx->csCtx);
            func_800B7298(globalCtx, &this->actor, 7);
            this->unk_A00 = Play_CreateSubCamera(globalCtx);
            Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
            Play_CameraChangeStatus(globalCtx, this->unk_A00, 7);
            D_809F4970->unk_151 = 1;
            this->unk_1C9 = 1;
            this->unk_1C8 = 1;
            this->unk_1E0 = 255.0f;
            this->unk_1DC = 0.0f;

            temp_s0 = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
            while (temp_s0 != NULL) {
                if (temp_s0->id == ACTOR_EN_ARROW) {
                    Actor_MarkForDeath(temp_s0);
                }
                temp_s0 = temp_s0->next;
            }

        case 1:
            if (this->unk_1CA >= 10) {
                Math_ApproachF(&this->unk_1E4, 30.0f, 0.2f, 1.0f);
                globalCtx->envCtx.fillScreen = 1;
                globalCtx->envCtx.screenFillColor[2] = 0;
                globalCtx->envCtx.screenFillColor[1] = 0;
                globalCtx->envCtx.screenFillColor[0] = 0;
                globalCtx->envCtx.screenFillColor[3] = this->unk_A2C;
                Math_ApproachF(&this->unk_A2C, 75.0f, 1.0f, 3.0f);
            }

            if (this->unk_1CA >= 30) {
                play_sound(NA_SE_EV_S_STONE_FLASH);
            }

            if (this->unk_1CA >= 60) {
                globalCtx->envCtx.fillScreen = 0;
                this->unk_1C8 = 0;
                this->unk_1DC = 0.0f;
                this->unk_1D8 = 0.0f;
                if (this->unk_1CA == 60) {
                    D_809F4970->unk_154++;
                    func_800B7298(globalCtx, &this->actor, 0x84);
                    player->actor.shape.rot.y = 0;
                    player->actor.world.rot.y = player->actor.shape.rot.y;
                }

                this->unk_A04.x = player->actor.world.pos.x + 20.0f;
                this->unk_A04.y = player->actor.world.pos.y + 20.0f;
                this->unk_A04.z = player->actor.world.pos.z + 30.0f;

                this->unk_A10.x = player->actor.world.pos.x;
                this->unk_A10.y = player->actor.world.pos.y + 26.0f;
                this->unk_A10.z = player->actor.world.pos.z;

                if (this->unk_1CA >= 75) {
                    temp_v0_2 = globalCtx->actorCtx.actorLists[ACTORCAT_BOSS].first;
                    while (temp_v0_2 != NULL) {
                        if ((temp_v0_2->id == ACTOR_EN_KNIGHT) && (&D_809F4970->actor == temp_v0_2) &&
                            (D_809F4970->unk_680 != 0)) {
                            this->unk_A04.x = 1307.0f;
                            this->unk_A04.y = 142.0f;
                            this->unk_A04.z = 2897.0f;

                            this->unk_A10.x = 1376.0f;
                            this->unk_A10.y = 132.0f;
                            this->unk_A10.z = 2860.0f;

                            if (this->unk_1CA == 75) {
                                D_809F4970->unk_148 = 1;
                            }
                            sp4E = 17;
                            break;
                        }
                        temp_v0_2 = temp_v0_2->next;
                    }
                }

                if ((s16)(sp4E + 80) < this->unk_1CA) {
                    this->unk_1C9 = 2;
                    this->unk_1CA = 0;
                    this->unk_1B4 = 0.0f;
                    this->unk_1B0 = 0.0f;
                    this->unk_144 = 2;
                    this->unk_1A4 = 0.0f;
                    this->unk_1A0 = 0.0f;
                    this->unk_1DC = 18.0f;
                    this->unk_1E0 = 255.0f;
                    this->unk_19C = 1.0f;

                    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_MIR_RAY2,
                                       this->actor.world.pos.x, this->actor.world.pos.y - 200.0f,
                                       this->actor.world.pos.z - 170.0f, 15, 0, 0, 1);

                    if (ENBOSS06_GET_PARAMS(&this->actor) == 0) {
                        this->unk_A04.x = this->actor.world.pos.x - 200.0f;
                    } else {
                        this->unk_A04.x = this->actor.world.pos.x + 200.0f;
                    }
                    this->unk_A04.y = (this->actor.world.pos.y - 200.0f) + 100.0f;
                    this->unk_A04.z = this->actor.world.pos.z - 200.0f;

                    this->unk_A10.x = this->actor.world.pos.x;
                    this->unk_A10.y = this->actor.world.pos.y + 80.0f;
                    this->unk_A10.z = this->actor.world.pos.z;
                }
            } else {
                this->unk_A10.z = this->actor.world.pos.z;
                this->unk_A04.y = this->actor.world.pos.y + 60.0f;
                this->unk_A04.x = this->actor.world.pos.x;

                this->unk_A04.z = this->actor.world.pos.z - 210.0f;
                this->unk_A10.y = this->actor.world.pos.y + 80.0f;
                this->unk_A10.x = this->actor.world.pos.x;
            }
            break;

        case 2:
            child = this->actor.child;

            if (this->unk_1CA == 1) {
                this->unk_A1C.x = fabsf(this->unk_A10.x - child->world.pos.x);
                this->unk_A1C.y = fabsf(this->unk_A10.y - child->world.pos.y);
                this->unk_A1C.z = fabsf(this->unk_A10.z - child->world.pos.z);
            }

            Math_ApproachF(&this->unk_A10.x, child->world.pos.x, 0.15f, this->unk_A1C.x * this->unk_A28);
            Math_ApproachF(&this->unk_A10.y, child->world.pos.y, 0.15f, this->unk_A1C.y * this->unk_A28);
            Math_ApproachF(&this->unk_A10.z, child->world.pos.z, 0.15f, this->unk_A1C.z * this->unk_A28);
            Math_ApproachF(&this->unk_A28, 1.0f, 1.0f, 0.001f);

            if (this->unk_1CA > 80) {
                func_809F2ED0(this, globalCtx);
                func_80169AFC(globalCtx, this->unk_A00, 0);
                this->unk_A00 = 0;
                Cutscene_End(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                D_809F4970->unk_151 = 0;
            }
            break;
    }

    if (this->unk_A00 != 0) {
        ShrinkWindow_SetLetterboxTarget(27);
        Play_CameraSetAtEye(globalCtx, this->unk_A00, &this->unk_A10, &this->unk_A04);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F24C8.s")
#endif

void func_809F2B64(Boss06* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F2C44;
    this->unk_144 = 3;
    this->unk_1A8 = 110.0f;
    this->unk_1E0 = 200;
    this->unk_1DC = 15.0f;
    this->unk_1E4 = 30.0f;
    this->unk_1AC = 0.0f;
    this->unk_19C = 1.0f;
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_MIR_RAY2, this->actor.world.pos.x,
                       this->actor.world.pos.y - 200.0f, this->actor.world.pos.z - 170.0f, 15, 0, 0, 1);
    D_809F4970->unk_154++;
}

void func_809F2C44(Boss06* this, GlobalContext* globalCtx) {
    if (D_809F4970->unk_153 != 0) {
        this->unk_A28 = 0.008f;
        Math_ApproachF(&this->unk_1E4, 0.0f, 0.2f, this->unk_A28 * 30.0f);
        Math_ApproachF(&this->unk_1AC, -70.0f, 0.2f, this->unk_A28 * 70.0f);
        Math_ApproachF(&this->unk_1A8, 0.0f, 0.2f, this->unk_A28 * 110.0f);
        Math_ApproachF(&this->unk_1A0, -900.0f, 0.2f, this->unk_A28 * 900.0f);
        Math_ApproachF(&this->unk_1A4, 1350.0f, 0.2f, this->unk_A28 * 1350.0f);
        Math_ApproachF(&this->unk_1E0, 100.0f, 0.2f, this->unk_A28 * 100.0f);

        if (this->unk_1E4 < 5.0f) {
            Math_ApproachF(&this->unk_19C, 0.0f, 1.0f, 0.03f);
        }

        if ((this->unk_1E4 > 0.1f) && ENBOSS06_GET_PARAMS(&this->actor) == 0) {
            play_sound(NA_SE_EV_CURTAIN_DOWN - SFX_FLAG);
        }
    }

    if (D_809F4970->unk_153 == 2) {
        Actor_MarkForDeath(this->actor.child);
        this->actor.child = NULL;
        func_809F2E14(this, globalCtx);
    }
}

void func_809F2E14(Boss06* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F2E34;
    this->unk_144 = 1;
}

void func_809F2E34(Boss06* this, GlobalContext* globalCtx) {
    this->unk_1E0 = 200.0f;
    this->unk_1DC = 15.0f;
    func_809F23CC(this);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->collider.dim.pos.z = (this->actor.world.pos.z - 50.0f) + 100.0f;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_809F2ED0(Boss06* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809F2EE8;
}

void func_809F2EE8(Boss06* this, GlobalContext* globalCtx) {
    this->unk_1E0 = 100.0f;
    this->unk_1DC = 13.0f;
}

void Boss06_Update(Actor* thisx, GlobalContext* globalCtx) {
    Boss06* this = THIS;
    s32 i;
    Vec3f sp7C;
    f32 temp_f22;
    f32 phi_f26;
    f32 phi_f24;

    this->actionFunc(this, globalCtx);

    if (this->unk_146 != 0) {
        this->unk_146--;
    }

    if (this->unk_148 != 0) {
        this->unk_148--;
    }

    if (this->unk_1E4 > 0.0f) {
        if (ENBOSS06_GET_PARAMS(&this->actor) == 0) {
            D_801F4E32 = 1;
            D_801F4E38.x = this->actor.world.pos.x + this->unk_1B0;
            D_801F4E38.y = this->actor.world.pos.y + 80.0f + this->unk_1B4 + this->unk_1AC;
            D_801F4E38.z = this->actor.world.pos.z;
            D_801F4E44 = this->unk_1E4;
            D_801F4E48 = 10.0f;
            D_801F4E4C = 0;
        } else {
            D_801F4E4E = 1;
            D_801F4E50.x = this->actor.world.pos.x + this->unk_1B0;
            D_801F4E50.y = this->actor.world.pos.y + 80.0f + this->unk_1B4 + this->unk_1AC;
            D_801F4E50.z = this->actor.world.pos.z;
            D_801F4E5C = this->unk_1E4;
            D_801F4E60 = 10.0f;
            D_801F4E64 = 0;
        }
    } else if (ENBOSS06_GET_PARAMS(&this->actor) == 0) {
        D_801F4E32 = 0;
    } else {
        D_801F4E4E = 0;
    }

    if ((this->unk_1C8 != 0) && (this->unk_1C8 != 0)) {
        play_sound(NA_SE_EV_FIRE_PLATE - SFX_FLAG);
        this->unk_1CC += 0.6f;
        this->unk_1D0 += 0.1f;
        this->unk_1D4 += 0.0200000014156f;
        this->unk_1D8 += 0.00016f;
        this->unk_1DC += 0.4f;
        Math_ApproachZeroF(&this->unk_1B0, 1.0f, 0.7f);
        Math_ApproachZeroF(&this->unk_1B4, 1.0f, 0.7f);

        phi_f26 = 0.0f;
        phi_f24 = 0.0f;

        for (i = 0; i < 1024; i++) {
            temp_f22 =
                (((__sinf(phi_f24) * this->unk_1D4) + 1.0f) * ((__sinf(phi_f26) * this->unk_1D0) + this->unk_1D0)) +
                this->unk_1CC;

            phi_f26 += (M_PI / 64);
            phi_f24 += 0.030679617f;

            Matrix_InsertZRotation_f(i * (M_PI / 512), MTXMODE_NEW);
            Matrix_GetStateTranslationAndScaledY(temp_f22, &sp7C);

            sp7C.x += 32.0f + this->unk_1BC;
            sp7C.y += 32.0f + this->unk_1C0;

            if ((i % 8) == 0) {
                Math_Vec3f_Copy(&D_809F4370[i / 8], &sp7C);
            }

            if ((sp7C.x >= 0.0f) && (sp7C.y >= 0.0f) && (sp7C.x < 64.0f) && (sp7C.y < 64.0f)) {
                s32 x = sp7C.x;
                s32 idx = ((s32)sp7C.y << 5);

                idx += (x / 2);

                if ((x % 2) != 0) {
                    this->unk_200[idx] &= 0xF0;
                } else {
                    this->unk_200[idx] &= 0xF;
                }
            }
        }
    }
}

void Boss06_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Boss06* this = THIS;
    s32 i;
    f32 spE0 = 0.0f;
    s16 temp_s0;
    s16 temp_f10;
    Vtx* temp_v0_2;
    u16 temp_v0;
    u16 pad;
    u8 spD3;
    u8 spD2;
    s32 maxColor = 255; // Possible FAKE MATCH
    f32 sp68;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    temp_v0 = gSaveContext.save.time;
    if (temp_v0 > CLOCK_TIME(12, 0)) {
        temp_v0 = 0xFFFF - temp_v0;
    }
    sp68 = (f32)temp_v0 / 0x8000;
    spD3 = ((10.0f * sp68) + 105.0f) * this->unk_19C;
    spD2 = ((40.0f * sp68) + 55.0f) * this->unk_19C;

    if (this->unk_144 & 2) {
        temp_s0 = Math_SinS(D_809F4970->unk_144) * 1000.0f;
        temp_f10 = (Math_CosS(D_809F4970->unk_144) * -2000.0f) - 2000.0f;
        temp_v0_2 = SEGMENTED_TO_VIRTUAL(&object_knight_Vtx_018BD0);

        temp_v0_2[0].v.ob[1] = (s16)this->unk_1A0 + 0xE92;
        temp_v0_2[3].v.ob[1] = (s16)this->unk_1A0 + 0xE92;
        temp_v0_2[4].v.ob[1] = (s16)this->unk_1A0 + 0xE92;
        temp_v0_2[7].v.ob[1] = (s16)this->unk_1A0 + 0xE92;

        temp_v0_2[5].v.ob[0] = temp_s0 + 0x2A3;
        temp_v0_2[5].v.ob[2] = (temp_f10 + (s16)this->unk_1A4) - 0x708;

        temp_v0_2[6].v.ob[0] = temp_s0 - 0x2A3;
        temp_v0_2[6].v.ob[2] = (temp_f10 + (s16)this->unk_1A4) - 0x708;

        temp_v0_2[9].v.ob[0] = temp_s0 + 0x2A3;
        temp_v0_2[9].v.ob[2] = temp_f10 - 0x1C2;

        temp_v0_2[11].v.ob[0] = temp_s0 - 0x2A3;
        temp_v0_2[11].v.ob[2] = temp_f10 - 0x1C2;

        temp_v0_2[12].v.ob[0] = temp_s0 + 0x2A3;
        temp_v0_2[12].v.ob[2] = temp_f10 - 0x1C2;

        temp_v0_2[14].v.ob[0] = temp_s0 - 0x339;
        temp_v0_2[14].v.ob[2] = temp_f10 - 0x79E;

        temp_v0_2[15].v.ob[0] = temp_s0 - 0x339;
        temp_v0_2[15].v.ob[2] = temp_f10;

        temp_v0_2[16].v.ob[0] = temp_s0 + 0x339;
        temp_v0_2[16].v.ob[2] = temp_f10;

        temp_v0_2[17].v.ob[0] = temp_s0 + 0x339;
        temp_v0_2[17].v.ob[2] = temp_f10 - 0x79E;

        if (this->actor.child != NULL) {
            Actor* child = this->actor.child;

            child->world.pos.x = this->actor.world.pos.x + (temp_s0 * 0.1f);
            child->world.pos.z = (this->actor.world.pos.z - 170.0f) + (temp_f10 * 0.1f);
        }

        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_knight_Matanimheader_019360));
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y - 234.0f,
                                 this->actor.world.pos.z + 30.0f, 0);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, 0.0f, -1112.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 155, 255, maxColor, (u8)((140.0f * sp68) + 115.0f), spD3);
        gSPDisplayList(POLY_XLU_DISP++, object_knight_DL_018CF0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 255, maxColor, (u8)((100.0f * sp68) + 65.0f), spD2);
        gSPDisplayList(POLY_XLU_DISP++, object_knight_DL_018DE0);

        if (1) {}
    }

    if (this->unk_144 & 1) {
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&this->unk_200));

        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y + this->unk_1A8,
                                 this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, 0.0f, MTXMODE_APPLY);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_knight_DL_0193B0);

        if (this->unk_1D8 > 0.0f) {
            Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y + 84.0f,
                                     this->actor.world.pos.z - 2.0f, MTXMODE_NEW);
            Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
            func_809F2120(1, 0x71A5, 0x263A);

            gDPSetEnvColor(POLY_XLU_DISP++, 255, 10, 0, 0);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 128, 255, 255, 0, 230);

            for (i = 0; i < ARRAY_COUNT(D_809F4370); i++) {
                if ((fabsf(D_809F4370[i].x - 32.0f) < 30.0f) && (fabsf(D_809F4370[i].y - 32.0f) < 30.0f)) {
                    Matrix_StatePush();

                    gSPSegment(POLY_XLU_DISP++, 0x08,
                               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                                ((globalCtx->gameplayFrames + (i * 10)) * -20) % 512, 0x20, 0x80));

                    Matrix_InsertTranslation((D_809F4370[i].x - 32.0f) * -2.4f, (D_809F4370[i].y - 32.0f) * -2.4f, 0.0f,
                                             MTXMODE_APPLY);
                    Matrix_InsertZRotation_f(i * (M_PI / 64), MTXMODE_APPLY);

                    if (func_809F2140() < 0.5f) {
                        Matrix_InsertYRotation_f(M_PI, MTXMODE_APPLY);
                    }

                    Matrix_Scale(-0.02f / 10.0f, -this->unk_1D8, 1.0f, MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);

                    Matrix_StatePop();
                }
            }
        } else {
            spE0 = 7.0f;
        }
    }

    if (this->unk_1DC > 0.0f) {
        u8 temp_s2 = (this->unk_1E0 - 50.0f) + (50.0f * sp68);

        Matrix_InsertTranslation(this->actor.world.pos.x + this->unk_1B0,
                                 this->actor.world.pos.y + 84.0f + this->unk_1B4,
                                 (this->actor.world.pos.z - 2.0f) + spE0, MTXMODE_NEW);

        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)((140.0f * sp68) + 115.0f), temp_s2);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 205, (u8)((100.0f * sp68) + 65.0f), 128);

        Matrix_Scale(this->unk_1DC, this->unk_1DC, 1.0f, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(globalCtx->gameplayFrames * 64, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
