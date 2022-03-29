/*
 * File: z_en_gs.c
 * Overlay: ovl_En_Gs
 * Description: Gossip stone
 */

#include "z_en_gs.h"
#include "objects/object_gs/object_gs.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnGs*)thisx)

void EnGs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80997D14(EnGs* this, GlobalContext* globalCtx);
void func_80997D38(EnGs* this, GlobalContext* globalCtx);
void func_80997E4C(EnGs* this, GlobalContext* globalCtx);
void func_80998040(EnGs* this, GlobalContext* globalCtx);
void func_8099807C(EnGs* this, GlobalContext* globalCtx);
void func_80998300(EnGs* this, GlobalContext* globalCtx);
void func_809984F4(EnGs* this, GlobalContext* globalCtx);
void func_809985B8(EnGs* this, GlobalContext* globalCtx);
void func_80998704(EnGs* this, GlobalContext* globalCtx);
void func_8099874C(EnGs* this, GlobalContext* globalCtx);
void func_809989B4(EnGs* this, GlobalContext* globalCtx);
void func_809989F4(EnGs* this, GlobalContext* globalCtx);
s32 func_80998A48(EnGs* this, GlobalContext* globalCtx);
s32 func_80998BBC(EnGs* this, GlobalContext* globalCtx);
s32 func_80998D44(EnGs* this, GlobalContext* globalCtx);
s32 func_80998F9C(EnGs* this, GlobalContext* globalCtx);
s32 func_809995A4(EnGs* this, GlobalContext* globalCtx);
void func_80999A8C(EnGs* this, GlobalContext* globalCtx);
void func_80999AC0(EnGs* this);

const ActorInit En_Gs_InitVars = {
    ACTOR_EN_GS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GS,
    sizeof(EnGs),
    (ActorFunc)EnGs_Init,
    (ActorFunc)EnGs_Destroy,
    (ActorFunc)EnGs_Update,
    (ActorFunc)EnGs_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
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
    { 21, 48, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xE),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0xC),
    /* Zora boomerang */ DMG_ENTRY(0, 0xE),
    /* Normal arrow   */ DMG_ENTRY(0, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xD),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(0, 0xB),
    /* Ice arrow      */ DMG_ENTRY(0, 0xB),
    /* Light arrow    */ DMG_ENTRY(0, 0xB),
    /* Goron spikes   */ DMG_ENTRY(0, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0xE),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xE),
    /* Zora punch     */ DMG_ENTRY(0, 0xE),
    /* Spin attack    */ DMG_ENTRY(0, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0xE),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xC),
};

s8 func_80997A90(s16 arg0, s16 arg1) {
    s8 phi_v1;

    if ((arg0 == 0) || ((arg0 != 1) && (arg0 != 2) && (arg0 == 3))) {
        phi_v1 = 0;
    } else {
        phi_v1 = (gSaveContext.save.unk_EC4 >> (arg1 * 3)) & 7;
    }
    return phi_v1;
}

void func_80997AFC(s32 idx, Color_RGB8* arg1) {
    static Color_RGB8 D_8099A3F8[] = {
        { 255, 255, 255 },
        { 150, 255, 100 },
        { 255, 80, 40 },
        { 100, 150, 255 },
    };

    *arg1 = D_8099A3F8[idx];
}

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void EnGs_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGs* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_208 = -1;
    this->unk_204 = 1;
    this->unk_198 = this->actor.world.rot.z;
    this->unk_195 = ENGS_GET_1F(thisx);
    this->unk_196 = ENGS_GET_FE0(thisx);
    this->actor.params = ENGS_GET_F000(thisx);
    this->actor.world.rot.z = 0;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->actor.targetMode = 6;
    this->unk_216 = 0;
    this->unk_218 = 0;
    this->unk_200 = 1.0f;
    this->unk_194 = func_80997A90(this->actor.params, this->unk_198);

    func_80997AFC(this->unk_194, &this->unk_1FA);
    this->unk_1F4 = this->unk_1FA;
    Math_Vec3f_Copy(&this->unk_1B0[0], &D_801C5DB0);
    Math_Vec3f_Copy(&this->unk_1B0[1], &D_801C5DB0);
    SubS_FillCutscenesList(&this->actor, this->unk_212, ARRAY_COUNT(this->unk_212));
    func_801A5080(0);
    if (this->actor.params == ENGS_1) {
        Actor_SetScale(&this->actor, 0.15f);
        this->collider.dim.radius *= 1.5f;
        this->collider.dim.height *= 1.5f;
    }
    func_80997D14(this, globalCtx);
}

void EnGs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    func_80165690();
}

void func_80997D14(EnGs* this, GlobalContext* globalCtx) {
    this->unk_19A &= ~0x200;
    this->actionFunc = func_80997D38;
}

void func_80997D38(EnGs* this, GlobalContext* globalCtx) {
    static f32 D_8099A408[] = { 40.0f, 60.0f, 40.0f, 40.0f };

    if (Message_GetState(&globalCtx->msgCtx) == 0) {
        if (this->actor.xzDistToPlayer <= D_8099A408[this->actor.params]) {
            func_8013E8F8(&this->actor, globalCtx, D_8099A408[this->actor.params], D_8099A408[this->actor.params], 0,
                          0x2000, 0x2000);
        }
    }

    if (this->actor.params != ENGS_2) {
        func_800B874C(&this->actor, globalCtx, 100.0f, 100.0f);
    }
}

void func_80997DEC(EnGs* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) == PLAYER_MASK_TRUTH) {
        this->unk_210 = 0x20D1;
    } else {
        this->unk_210 = 0x20D0;
    }
    this->unk_19A |= 0x200;
    this->actionFunc = func_80997E4C;
}

void func_80997E4C(EnGs* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
            break;

        case 1:
        case 2:
        case 3:
            break;

        case 4:
        case 5:
        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x20D0:
                        func_80997D14(this, globalCtx);
                        break;

                    case 0x20D1:
                        switch (this->actor.params) {
                            case ENGS_0:
                                this->unk_210 = this->unk_195 + 0x20D3;
                                if (this->unk_210 >= 0x20D4) {
                                    s32 temp_v1 = this->unk_210 - 0x20D4;

                                    if ((this->unk_210 < 0x20E8) &&
                                        ((temp_v1 + ITEM_MASK_TRUTH) == INV_CONTENT(temp_v1 + ITEM_MASK_TRUTH))) {
                                        this->unk_210 = temp_v1 + 0x2103;
                                    }
                                }
                                break;

                            case ENGS_3:
                                this->unk_210 = this->unk_195 + 0x20B0;
                                break;

                            case ENGS_1:
                                this->unk_210 = this->unk_195 + 0x20F3;
                                break;

                            case ENGS_2:
                                this->unk_210 = this->unk_195 + 0x20F7;
                                break;
                        }
                        func_80151938(globalCtx, this->unk_210);
                        break;

                    default:
                        func_80997D14(this, globalCtx);
                        break;
                }
            }
            break;
    }
}

void func_80997FF0(EnGs* this, GlobalContext* globalCtx) {
    if (SubS_StartActorCutscene(&this->actor, globalCtx->playerActorCsIds[0], -1, SUBS_CUTSCENE_NORMAL)) {
        func_80998040(this, globalCtx);
    }
}

void func_80998040(EnGs* this, GlobalContext* globalCtx) {
    func_80152434(globalCtx, 1);
    this->actionFunc = func_8099807C;
}

void func_8099807C(EnGs* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.ocarinaMode) {
        case 3:
            switch (globalCtx->msgCtx.unk1202E) {
                case 7:
                case 8:
                    if (!Flags_GetSwitch(globalCtx, this->unk_196)) {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, this->actor.world.pos.x,
                                    this->actor.world.pos.y + 40.0f, this->actor.world.pos.z, 0, 0, 0, 2);
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BUTTERFRY_TO_FAIRY);
                        Flags_SetSwitch(globalCtx, this->unk_196);
                    }
                    break;

                case 10:
                    if (!Flags_GetSwitch(globalCtx, this->unk_196)) {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, this->actor.world.pos.x,
                                    this->actor.world.pos.y + 40.0f, this->actor.world.pos.z, 0, 0, 0, 7);
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BUTTERFRY_TO_FAIRY);
                        Flags_SetSwitch(globalCtx, this->unk_196);
                    }
                    break;

                case 0:
                    if ((this->actor.params == ENGS_1) && (gSaveContext.save.playerForm == PLAYER_FORM_DEKU)) {
                        this->unk_194 = 1;
                        this->unk_19C = 5;
                        this->unk_19A |= 1;
                        func_80999AC0(this);
                        func_809984F4(this, globalCtx);
                    }
                    break;

                case 2:
                    if ((this->actor.params == ENGS_1) && (gSaveContext.save.playerForm == PLAYER_FORM_ZORA)) {
                        this->unk_194 = 3;
                        this->unk_19C = 5;
                        this->unk_19A |= 1;
                        func_80999AC0(this);
                        func_809984F4(this, globalCtx);
                    }
                    break;

                case 1:
                    if ((this->actor.params == ENGS_1) && (gSaveContext.save.playerForm == PLAYER_FORM_GORON)) {
                        this->unk_194 = 2;
                        this->unk_19C = 5;
                        this->unk_19A |= 1;
                        func_80999AC0(this);
                        func_809984F4(this, globalCtx);
                    }
                    break;
            }
            break;

        case 0:
        case 4:
            func_80998300(this, globalCtx);

        case 26:
            func_80997D14(this, globalCtx);
            break;
    }
}

void func_80998300(EnGs* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        ActorCutscene_Stop(globalCtx->playerActorCsIds[0]);
    }
}

f32 func_80998334(EnGs* this, GlobalContext* globalCtx, f32* arg2, f32* arg3, s16* arg4, f32 arg5, f32 arg6, f32 arg7,
                  s32 arg8, s32 arg9) {
    f32 sp2C = Math_SmoothStepToF(arg2, *arg3, arg5, arg6, arg7);

    if (arg9 == 0) {
        sp2C = Math_SmoothStepToF(arg2, *arg3, arg5, arg6, arg7);
        this->unk_1B0[0].x = (__sinf(DEGF_TO_RADF((*arg4 % arg8) * (1.0f / arg8) * 360.0f)) * *arg2) + 1.0f;
        this->unk_1B0[0].y = 1.0f - (__sinf(DEGF_TO_RADF((*arg4 % arg8) * (1.0f / arg8) * 360.0f)) * *arg2);
        (*arg4)++;
    }
    return sp2C;
}

void func_809984F4(EnGs* this, GlobalContext* globalCtx) {
    EnGs* gossipStone = NULL;

    do {
        gossipStone = (EnGs*)SubS_FindActor(globalCtx, &gossipStone->actor, ACTORCAT_PROP, ACTOR_EN_GS);
        if (gossipStone != NULL) {
            if ((this != gossipStone) && (this->unk_194 == gossipStone->unk_194)) {
                gossipStone->unk_19A |= 1;
                func_80999AC0(gossipStone);
                gossipStone->unk_19C = 3;
                func_80998704(gossipStone, globalCtx);
            }
            gossipStone = (EnGs*)gossipStone->actor.next;
        }
    } while (gossipStone != NULL);

    func_800B7298(globalCtx, &this->actor, 7);
    this->actionFunc = func_809985B8;
}

void func_809985B8(EnGs* this, GlobalContext* globalCtx) {
    EnGs* gossipStone;
    Vec3f sp38;

    if (SubS_StartActorCutscene(&this->actor, this->unk_212[0], -1, SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
        Player* player = GET_PLAYER(globalCtx);

        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_GetStateTranslationAndScaledZ(160.0f, &sp38);
        Math_Vec3f_Sum(&player->actor.world.pos, &sp38, &player->actor.world.pos);
        Math_Vec3f_Copy(&player->actor.prevPos, &player->actor.world.pos);
        this->unk_200 = 0.0f;
        gSaveContext.save.unk_EC4 = ((u32)gSaveContext.save.unk_EC4 & ~(7 << (this->unk_198 * 3))) |
                                    ((this->unk_194 & 7) << (this->unk_198 * 3));
        gossipStone = NULL;

        do {
            gossipStone = (EnGs*)SubS_FindActor(globalCtx, &gossipStone->actor, ACTORCAT_PROP, ACTOR_EN_GS);
            if (gossipStone != NULL) {
                if ((gossipStone != this) && (gossipStone->actor.params == ENGS_2) &&
                    (gossipStone->unk_198 == this->unk_198)) {
                    gossipStone->unk_194 = this->unk_194;
                    gossipStone->unk_200 = 0.0f;
                }
                gossipStone = (EnGs*)gossipStone->actor.next;
            }
        } while (gossipStone != NULL);

        func_80998704(this, globalCtx);
    }
}

void func_80998704(EnGs* this, GlobalContext* globalCtx) {
    this->unk_19D = 0;
    this->unk_19A &= ~(0x100 | 0x4);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_G_STONE_CHANGE_COLOR);
    this->actionFunc = func_8099874C;
}

void func_8099874C(EnGs* this, GlobalContext* globalCtx) {
    s32 phi_v0 = 0;

    switch (this->unk_19C) {
        case 0:
            phi_v0 = func_80998A48(this, globalCtx);
            break;

        case 1:
            phi_v0 = func_80998BBC(this, globalCtx);
            break;

        case 2:
            phi_v0 = func_80998D44(this, globalCtx);
            break;

        case 3:
        case 5:
            phi_v0 = func_80998F9C(this, globalCtx);
            break;

        case 4:
            phi_v0 = func_809995A4(this, globalCtx);
            break;
    }

    if (phi_v0 == 0) {
        this->unk_216 = 0;
        if ((this->unk_19C == 5) && (this->unk_194 != 0)) {
            s32 i;

            ActorCutscene_Stop(this->unk_212[0]);
            phi_v0 = 1;

            for (i = 0; i < 4; i++) {
                if (((gSaveContext.save.unk_EC4 >> (i * 3)) & 7) != (u32)this->unk_194) {
                    phi_v0 = 0;
                }
            }

            if (phi_v0 != 0) {
                this->unk_20C = -1;
                switch (this->unk_194) {
                    case 1:
                        if (!(gSaveContext.save.weekEventReg[77] & 8)) {
                            this->unk_20C = 6;
                            gSaveContext.save.weekEventReg[77] |= 8;
                        }
                        break;

                    case 3:
                        if (!(gSaveContext.save.weekEventReg[77] & 0x10)) {
                            this->unk_20C = 6;
                            gSaveContext.save.weekEventReg[77] |= 0x10;
                        }
                        break;

                    case 2:
                        if (!(gSaveContext.save.weekEventReg[77] & 0x20)) {
                            this->unk_20C = 6;
                            gSaveContext.save.weekEventReg[77] |= 0x20;
                        }
                        break;
                }

                if (!(gSaveContext.save.weekEventReg[90] & 0x10)) {
                    gSaveContext.save.weekEventReg[90] |= 0x10;
                    this->unk_20C = 12;
                }

                if (this->unk_20C > 0) {
                    func_809989B4(this, globalCtx);
                } else {
                    func_80997D14(this, globalCtx);
                }
            } else {
                func_80997D14(this, globalCtx);
            }
        } else {
            func_80997D14(this, globalCtx);
        }
    }
}

void func_809989B4(EnGs* this, GlobalContext* globalCtx) {
    Actor_PickUp(&this->actor, globalCtx, this->unk_20C, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_809989F4;
}

void func_809989F4(EnGs* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80997D14(this, globalCtx);
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->unk_20C, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    }
}

s32 func_80998A48(EnGs* this, GlobalContext* globalCtx) {
    s32 sp3C = -1;

    if (this->unk_19D == 0) {
        this->unk_216 = 200;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);

        this->unk_1D4 = 0;
        this->unk_19A |= 1;
        this->unk_21C = 5;
        this->unk_21E = 40;
        this->unk_197++;
        this->unk_197 &= 0xF;
        this->unk_19D = 1;

        this->unk_1DC = 0.5f;
        this->unk_1E0 = 0.0f;
    } else if (this->unk_19D == 1) {
        if (func_80998334(this, globalCtx, &this->unk_1DC, &this->unk_1E0, &this->unk_1D4, 0.8f, 0.007f, 0.001f, 7,
                          0) == 0.0f) {
            if ((this->actor.params != ENGS_0) && !Play_InCsMode(globalCtx) &&
                (Message_GetState(&globalCtx->msgCtx) == 0)) {
                this->unk_216 = 0;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIVE_LUPY_COUNT);
                Message_StartTextbox(globalCtx, 0x20D2, NULL);
            }
            this->unk_19A &= ~1;
            sp3C = 0;
        }
    }
    return sp3C;
}

s32 func_80998BBC(EnGs* this, GlobalContext* globalCtx) {
    s32 sp34 = -1;

    if (this->unk_19D == 0) {
        this->unk_216 = 200;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
        this->unk_1DC = 0.3f;
        this->unk_1E0 = 0.0f;

        this->unk_1D4 = 0;
        this->unk_19A |= 1;
        this->unk_21C = 5;
        this->unk_21E = 40;
        this->unk_197--;
        this->unk_197 &= 0xF;
        this->unk_19D = 1;
    } else if (this->unk_19D == 1) {
        this->unk_19E[0].z = (this->unk_1D4 % 8) * 0.125f * 360.0f * (0x10000 / 360.0f);
        this->unk_19E[1].z = -this->unk_19E[0].z;
        if (func_80998334(this, globalCtx, &this->unk_1DC, &this->unk_1E0, &this->unk_1D4, 0.8f, 0.005f, 0.001f, 7,
                          0) == 0.0f) {
            this->unk_19A &= ~1;
            sp34 = 0;
        }
    }
    return sp34;
}

s32 func_80998D44(EnGs* this, GlobalContext* globalCtx) {
    s32 sp3C = -1;
    f32 step;

    if (this->unk_19D == 0) {
        this->unk_216 = 200;
        this->unk_1DC = this->unk_1B0[0].y - 1.0f;
        this->unk_1E0 = -0.8f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_G_STONE_CRUSH);
        this->unk_19A |= 1;
        this->unk_21C = 40;
        this->unk_21E = 11;
        this->unk_19D++;
    } else if (this->unk_19D == 1) {
        step = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 1.0f, 0.4f, 0.001f);
        this->unk_1B0[0].y = this->unk_1DC + 1.0f;
        if (step == 0.0f) {
            this->unk_216 = 0;
            this->unk_1D4 = 0;
            this->unk_19D++;
        }
    } else if (this->unk_19D == 2) {
        this->unk_1D4++;
        if (this->unk_1D4 >= 100) {
            this->unk_216 = 200;
            this->unk_19D++;
            this->unk_1DC = this->unk_1B0[0].y - 1.0f;
            this->unk_1E0 = 0.0f;
        }
    } else if (this->unk_19D == 3) {
        step = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 1.0f, 0.5f, 0.001f);
        this->unk_1B0[0].y = this->unk_1DC + 1.0f;
        if (step == 0.0f) {
            this->unk_216 = 0;
            this->unk_1E0 = 0.0f;
            this->unk_1D4 = 0;
            this->unk_21C = 10;
            this->unk_21E = 10;
            this->unk_1DC = 0.5f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
            this->unk_19D += 1;
        }
    } else if ((this->unk_19D == 4) && (func_80998334(this, globalCtx, &this->unk_1DC, &this->unk_1E0, &this->unk_1D4,
                                                      1.0f, 0.03f, 0.001f, 5, 0) == 0.0f)) {
        this->unk_19A &= ~1;
        sp3C = 0;
    }
    return sp3C;
}

s32 func_80998F9C(EnGs* this, GlobalContext* globalCtx) {
    s32 sp4C = -1;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    s32 phi_v0_2;
    u16 sp3A = this->unk_19E[0].y;

    if (this->unk_19D == 0) {
        this->unk_1DC = 0;
        this->unk_1E0 = 90.0f;
        this->unk_1E4 = 0.1f;
        this->unk_1E8 = 2.0f;
        this->unk_1EC = 0.0f;

        this->unk_19D = 1;
        this->unk_21C = 2;
        this->unk_21E = 40;
        this->unk_216 = 200;
    }

    if (this->unk_19D == 1) {
        Math_SmoothStepToF(&this->unk_1E4, this->unk_1E8, 1.0f, 0.1f, 0.001f);
        sp48 = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 1.0f, this->unk_1E4, 0.001f);
        this->unk_19E[0].y += (s32)(this->unk_1DC * (0x10000 / 360.0f));
        if (sp48 == 0.0f) {
            this->unk_1D4 = 0;
            this->unk_19D = 2;
        }
    }

    if (this->unk_19D == 2) {
        this->unk_19E[0].y += (s32)(this->unk_1DC * (0x10000 / 360.0f));
        if ((this->unk_1D4++ <= 40) ^ 1) {
            this->unk_1DC = this->unk_1B0[0].y - 1.0f;
            this->unk_1E0 = 1.5f;
            this->unk_1E4 = this->unk_1B0[1].y - 1.0f;
            this->unk_1E8 = -0.3f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_STONE_GROW_UP);
            this->unk_19D = 3;
        }
    }

    if (this->unk_19D == 3) {
        this->unk_19E[0].y += 0x4000;
        sp48 = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 0.8f, 0.2f, 0.001f);
        Math_SmoothStepToF(&this->unk_1E4, this->unk_1E8, 0.8f, 0.2f, 0.001f);
        this->unk_1B0[0].x = this->unk_1E4 + 1.0f;
        this->unk_1B0[0].y = this->unk_1DC + 1.0f;
        if (sp48 == 0.0f) {
            this->unk_1DC = 2.0f * M_PI / 9.0000002;
            this->unk_1E0 = M_PI / 9.0000002;
            this->unk_19D = 4;
        }
    }

    if (this->unk_19D == 4) {
        sp48 = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 0.8f, 16384.0f, 3640.0f);
        this->unk_19E[0].y += (s16)this->unk_1DC;
        if (sp48 == 0.0f) {
            phi_v0_2 = this->unk_19E[0].y;
            if (phi_v0_2 > 0) {
                phi_v0_2 += 0xFFFF0000;
            }
            this->unk_1DC = phi_v0_2;
            this->unk_1E0 = 0;
            this->unk_19D = 5;
        }
    }

    if (this->unk_19D == 5) {
        phi_v0_2 = this->unk_19E[0].y;
        if (phi_v0_2 > 0) {
            phi_v0_2 += 0xFFFF0001;
        }
        this->unk_1DC = phi_v0_2;

        sp48 = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 0.8f, 3640.0f, 0.001f);
        this->unk_19E[0].y = (s32)this->unk_1DC;
        if (sp48 == 0.0f) {
            this->unk_19E[0].y = 0;
            this->unk_1D4 = 0;
            this->unk_1DC = this->unk_1B0[0].y - 1.0f;
            this->unk_1E0 = 0.0f;
            this->unk_1E4 = this->unk_1B0[0].x - 1.0f;
            this->unk_1E8 = 0.0f;
            this->unk_1F0 = 0.0f;
            this->unk_1EC = 0.5f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
            this->unk_21C = 20;
            this->unk_21E = 2;
            this->unk_19D = 6;
        }
    }

    if (this->unk_19D == 6) {
        sp48 = Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 0.8f, 0.1f, 0.001f);
        sp44 = Math_SmoothStepToF(&this->unk_1E4, this->unk_1E8, 0.8f, 0.1f, 0.001f);
        sp40 = Math_SmoothStepToF(&this->unk_1EC, this->unk_1F0, 0.8f, 0.02f, 0.001f);
        this->unk_1B0[0].x = this->unk_1E4 + 1.0f;
        this->unk_1B0[0].y = this->unk_1DC + 1.0f;
        this->unk_1B0[0].x += __sinf(DEGF_TO_RADF((this->unk_1D4 % 10) * 0.1f * 360.0f)) * this->unk_1EC;
        this->unk_1B0[0].y += __sinf(DEGF_TO_RADF((this->unk_1D4 % 10) * 0.1f * 360.0f)) * this->unk_1EC;
        this->unk_1D4++;
        if ((sp48 == 0.0f) && (sp44 == 0.0f) && (sp40 == 0.0f)) {
            this->unk_216 = 0;
            sp4C = 0;
        }
    }

    if ((u16)this->unk_19E[0].y < sp3A) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_STONE_ROLLING);
    }

    return sp4C;
}

void func_80999584(Color_RGB8* arg0, Color_RGB8* arg1) {
    arg0->r = arg1->r;
    arg0->g = arg1->g;
    arg0->b = arg1->b;
}

s32 func_809995A4(EnGs* this, GlobalContext* globalCtx) {
    static Color_RGB8 flashColours[] = {
        { 255, 50, 50 },
        { 50, 50, 255 },
        { 255, 255, 255 },
    };
    static Vec3f dustAccel = { 0.0f, -0.3f, 0.0f };
    static Color_RGBA8 dustPrim = { 200, 200, 200, 128 };
    static Color_RGBA8 dustEnv = { 100, 100, 100, 0 };
    static Vec3f bomb2Velocity = { 0.0f, 0.0f, 0.0f };
    static Vec3f bomb2Accel = { 0.0f, 0.0f, 0.0f };
    s32 sp7C = -1;

    if (this->unk_19D == 0) {
        this->unk_19A |= 0x100;
        this->unk_1D4 = 40;
        this->unk_19D++;
    }

    if (this->unk_19D == 1) {
        if (this->unk_1D4-- == 0) {
            this->unk_1D4 = 80;
            this->unk_19A |= 4;
            this->unk_19D++;
        }
    }

    if (this->unk_19D == 2) {
        u8 pad;

        this->unk_1D4--;
        func_80999584(&this->unk_1FA, &flashColours[2]);
        if (this->unk_1D4 < 80) {
            if ((this->unk_1D4 % 20) < 8) {
                if (this->unk_1D4 < 20) {
                    if ((this->unk_1D4 % 20) == 7) {
                        func_80999584(&this->unk_1FA, &flashColours[0]);
                        this->unk_1F4 = this->unk_1FA;
                        play_sound(NA_SE_SY_WARNING_COUNT_E);
                        this->unk_200 = 0.0f;
                    }
                } else if ((this->unk_1D4 % 20) == 7) {
                    func_80999584(&this->unk_1FA, &flashColours[1]);
                    this->unk_1F4 = this->unk_1FA;
                    play_sound(NA_SE_SY_WARNING_COUNT_N);
                    this->unk_200 = 0.0f;
                }
            }
        }

        if (this->unk_1D4 <= 0) {
            this->unk_19A &= ~4;
            this->unk_21C = 3;
            this->unk_21E = 40;
            this->unk_1D4 = 0;
            this->unk_19D++;
        }
    }

    if (this->unk_19D == 3) {
        u8 i;
        Vec3f sp6C;
        Vec3f sp60;

        for (i = 0; i < 3; i++) {
            sp60.x = randPlusMinusPoint5Scaled(15.0f);
            sp60.y = Rand_ZeroFloat(-1.0f);
            sp60.z = randPlusMinusPoint5Scaled(15.0f);

            sp6C.x = this->actor.world.pos.x + (2.0f * sp60.x);
            sp6C.y = this->actor.world.pos.y + 7.0f;
            sp6C.z = this->actor.world.pos.z + (2.0f * sp60.z);

            func_800B0EB0(globalCtx, &sp6C, &sp60, &dustAccel, &dustPrim, &dustEnv, Rand_ZeroFloat(50.0f) + 200.0f, 40,
                          15);
        }

        func_800B9010(&this->actor, NA_SE_EV_FIRE_PILLAR - SFX_FLAG);

        if ((this->unk_1D4++ < 40) ^ 1) {
            this->unk_19A |= 0x10;

            this->actor.uncullZoneForward = 12000.0f;
            this->actor.gravity = 0.3f;
            this->unk_1DC = 0.0f;

            this->unk_19D++;
            this->unk_21C = 5;
            this->unk_21E = 20;
            this->unk_19A |= 1;
            this->unk_216 = 200;
            this->unk_1E0 = (this->unk_197 >> 2) * 0x444;
        }
    }

    if (this->unk_19D == 4) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 3);
        if (this->actor.bgCheckFlags & (0x10 | 0x8)) {
            Vec3f sp54;

            sp54.x = this->actor.world.pos.x;
            sp54.y = this->actor.world.pos.y;
            sp54.z = this->actor.world.pos.z;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
            EffectSsBomb2_SpawnLayered(globalCtx, &sp54, &bomb2Velocity, &bomb2Accel, 100, 20);
            this->unk_1D4 = 10;
            this->unk_19A |= 8;
            this->unk_216 = 0;
            this->actionFunc = func_80999A8C;
        } else {
            func_800B9010(&this->actor, NA_SE_EV_STONE_LAUNCH - SFX_FLAG);
        }

        Actor_MoveWithGravity(&this->actor);
        Math_SmoothStepToF(&this->unk_1DC, this->unk_1E0, 0.5f, 364.0f, 0.0f);

        this->unk_19E[1].y += (s16)this->unk_1DC;

        if ((this->actor.world.pos.y - this->actor.home.pos.y) >= 4000.0f) {
            this->unk_216 = 0;
        }

        if (this->actor.playerHeightRel < -12000.0f) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 0);
            Actor_MarkForDeath(&this->actor);
            sp7C = 0;
        }
    }

    return sp7C;
}

void func_80999A8C(EnGs* this, GlobalContext* globalCtx) {
    if (this->unk_1D4-- <= 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80999AC0(EnGs* this) {
    static Vec3s D_8099A450 = { 0, 0, 0 };
    static Vec3f D_8099A458 = { 1.0f, 1.0f, 1.0f };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_19E); i++) {
        this->unk_19E[i] = D_8099A450;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_1B0); i++) {
        this->unk_1B0[i] = D_8099A458;
    }
}

void func_80999B34(EnGs* this) {
    if (this->unk_216 > 0) {
        if (this->unk_218 == 0) {
            func_8016566C(this->unk_216);
            this->unk_218 = this->unk_216;
        } else {
            func_80165658(this->unk_218);
        }
    } else if (this->unk_218 > 0) {
        Math_StepToS(&this->unk_218, this->unk_216, 20);
        func_80165658(this->unk_218);
        if (this->unk_218 <= 0) {
            func_80165690();
        }
    }
}

void func_80999BC8(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnGs* this = THIS;
    s32 pad;

    if (this->actor.isTargeted && !func_801A5100()) {
        this->unk_19D = 0;
        this->unk_19A |= 1;
        func_80999AC0(this);
        this->unk_19C = 0;
        func_80998704(this, globalCtx);
        this->unk_208 = 0;
    }

    if (this->actor.params == ENGS_1) {
        Actor_SetFocus(&this->actor, 34.5f);
    } else {
        Actor_SetFocus(&this->actor, 23.0f);
    }

    if (this->unk_21A > 0) {
        this->unk_21A--;
        if (this->unk_21A <= 0) {
            this->unk_21A = 0;
        }
    }

    if (!(this->unk_19A & (0x200 | 0x10)) && (this->unk_21A == 0)) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->unk_19D = 0;
            this->collider.base.acFlags &= ~AC_HIT;

            switch (this->actor.colChkInfo.damageEffect) {
                case 15:
                    this->unk_19A |= 1;
                    func_80999AC0(this);
                    this->unk_19C = 0;
                    func_80998704(this, globalCtx);
                    this->unk_21A = 5;
                    break;

                case 14:
                    this->unk_19A |= 1;
                    func_80999AC0(this);
                    this->unk_19C = 1;
                    func_80998704(this, globalCtx);
                    this->unk_21A = 5;
                    break;

                case 13:
                    func_80999AC0(this);
                    this->unk_19C = 2;
                    func_80998704(this, globalCtx);
                    this->unk_21A = 5;
                    break;

                case 12:
                    this->unk_19A |= 2;
                    func_80999AC0(this);
                    this->unk_19C = 4;
                    func_80998704(this, globalCtx);
                    this->unk_21A = 5;
                    break;

                case 11:
                    this->unk_19A |= 1;
                    func_80999AC0(this);
                    this->unk_19C = 3;
                    func_80998704(this, globalCtx);
                    this->unk_21A = 5;
                    break;
            }
        }

        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    this->actionFunc(this, globalCtx);
}

void EnGs_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGs* this = THIS;

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        globalCtx->msgCtx.msgMode = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        this->collider.base.acFlags &= ~AC_HIT;
        func_80997DEC(this, globalCtx);
    } else if (func_800B8718(&this->actor, &globalCtx->state)) {
        this->unk_19A |= 0x200;
        this->collider.base.acFlags &= ~AC_HIT;
        if (this->actor.cutscene != -1) {
            this->actionFunc = func_80997FF0;
        } else {
            func_80998040(this, globalCtx);
        }
    } else {
        s16 sp2E;
        s16 sp2C;

        if ((this->actor.flags & ACTOR_FLAG_40) || (this->unk_19A & 0x100) || (this->unk_19A & 0x200)) {
            func_80999BC8(&this->actor, globalCtx);
            Actor_GetScreenPos(globalCtx, &this->actor, &sp2E, &sp2C);
            if ((this->actor.xyzDistToPlayerSq > SQ(400.0f)) || (sp2E < 0) || (sp2E > SCREEN_WIDTH) || (sp2C < 0) ||
                (sp2C > SCREEN_HEIGHT)) {
                this->unk_216 = 0;
            } else if (this->unk_21C > 0) {
                func_800BC848(&this->actor, globalCtx, this->unk_21C, this->unk_21E);
            }
        } else {
            this->unk_216 = 0;
        }

        if (this->unk_200 < 1.0f) {
            if (this->unk_19A & 4) {
                Math_StepToF(&this->unk_200, 1.0f, 0.06f);
            } else {
                Math_StepToF(&this->unk_200, 1.0f, 0.02f);
            }
            func_80997AFC(this->unk_194, &this->unk_1F7);
            Lib_LerpRGB(&this->unk_1F4, &this->unk_1F7, this->unk_200, &this->unk_1FA);
            if (this->unk_200 >= 1.0f) {
                this->unk_1F4 = this->unk_1FA;
            }
        }

        if (this->unk_21C > 0) {
            this->unk_21C = 0;
        }

        func_80999B34(this);
    }
}

void EnGs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGs* this = THIS;
    u32 frames;

    if (this->unk_19A & 8) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    frames = globalCtx->gameplayFrames;

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_StatePush();

    if (this->unk_19A & 1) {
        Matrix_RotateY(this->unk_19E[0].y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_19E[0].x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_19E[0].z, MTXMODE_APPLY);
        Matrix_Scale(this->unk_1B0[0].x, this->unk_1B0[0].y, this->unk_1B0[0].z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_19E[1].y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_19E[1].x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_19E[1].z, MTXMODE_APPLY);
    }

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_gs_DL_000950);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_1FA.r, this->unk_1FA.g, this->unk_1FA.b, 255);
    gSPDisplayList(POLY_OPA_DISP++, object_gs_DL_0009D0);
    gSPDisplayList(POLY_OPA_DISP++, object_gs_DL_000A60);

    Matrix_StatePop();

    if (this->unk_19A & 2) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
        Matrix_Scale(0.05f, -0.05f, 1.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, -frames * 20, 0x20, 0x80));
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 0, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
        gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
