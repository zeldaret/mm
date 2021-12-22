/*
 * File: z_en_nb.c
 * Overlay: ovl_En_Nb
 * Description: Anju's Grandma
 */

#include "z_en_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC0D84(EnNb* this, GlobalContext* globalCtx);
void func_80BC0EAC(EnNb* this, GlobalContext* globalCtx);

void func_80BC08E0(EnNb* this, GlobalContext* globalCtx);
void func_80BC0978(EnNb* this, GlobalContext* globalCtx);

s32 func_80BC00AC(EnNb* this, GlobalContext* globalCtx);
s32 func_80BC01DC(EnNb* this, GlobalContext* globalCtx);

s32 D_80BC13F0[] = {
    0x0C00031D, 0x0A00610A, 0x02060012, 0x00010504, 0x00030A00, 0x100A0212, 0x00060001, 0x05040004,
    0x050A0061, 0x4D0C0001, 0x1E020800, 0x0C001502, 0x0C000C0F, 0x0C020C0F, 0x12000304, 0x00030400,
    0x01040002, 0x04000100, 0x32200C02, 0x08001200, 0x03040003, 0x04000102, 0x08000C00, 0x13020C00,
    0x0C0F0B02, 0x0C0F1200, 0x03040003, 0x09010902, 0x09010500,
};

s32 D_80BC1464[] = {
    0x1B040800, 0x6A0A0010, 0x00080010, 0x00080000, 0x00080E29, 0x122D000E, 0x0C100E29, 0x012D000E, 0x0C100E29,
    0x020C0F29, 0x030C0500, 0x00000600, 0x22312D00, 0x0E121030, 0x1C04040E, 0x29040C20, 0x00030004, 0x150900C4,
    0x0900000F, 0x29050C15, 0x0900B930, 0x1D04040E, 0x290B0C20, 0x00030004, 0x150900A8, 0x0900000F, 0x290C0C15,
    0x09009D20, 0x00030017, 0x1B040400, 0x090E2911, 0x2D000E0C, 0x16100E29, 0x0A2D000E, 0x0C16101B, 0x0404003B,
    0x0E290D0C, 0x05000000, 0x0A00000E, 0x29102D00, 0x0E0C1216, 0x100E290E, 0x00320400, 0x590C0F29, 0x0F0C1206,
    0x000C0000, 0x13000C2F, 0x00002E2D, 0x002A2D00, 0x0E113204, 0x0C16100E, 0x29060C05, 0x000A0000, 0x00000E29,
    0x072D000E, 0x0C121610, 0x0E290800, 0x3202001E, 0x0C0F2909, 0x0C120600, 0x0C000013, 0x000C2F00, 0x002E2D00,
    0x292D000E, 0x1132020C, 0x16102D00, 0x0E0C1216, 0x10000000,
};

s32 D_80BC1574[] = {
    0x0900000E, 0x28C70C09, 0x0000170E, 0x28C80C09, 0x0000180E, 0x28C90C09, 0x0000170E,
    0x28CA0C09, 0x0000180E, 0x28CB0C09, 0x0000170E, 0x28CC0C09, 0x0000180E, 0x28CD0C09,
    0x0000170E, 0x28CE0C09, 0x0000180E, 0x28CF2D00, 0x012D000E, 0x0C090000, 0x10000000,
};

s32 D_80BC15C8[] = {
    0x0E23622D,
    0x000E0C10,
};

const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
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
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

ActorAnimationEntryS D_80BC1628[] = {
    { &object_nb_Anim_000990, 1.0f, 0, -1, 0, 0 },  { &object_nb_Anim_000990, 1.0f, 0, -1, 0, -4 },
    { &object_nb_Anim_000290, 1.0f, 0, -1, 2, 0 },  { &object_nb_Anim_000290, 1.0f, 0, -1, 0, -4 },
    { &object_nb_Anim_00052C, 1.0f, 0, -1, 0, -4 }, { &object_nb_Anim_0006D4, 1.0f, 0, -1, 2, -4 },
};

Actor* func_80BBFDB0(EnNb* this, GlobalContext* globalCtx, u8 actorCategory, s16 actorId) {
    Actor* thisx;
    Actor* actor = NULL;

    while (true) {
        actor = func_ActorCategoryIterateById(globalCtx, actor, actorCategory, actorId);
        if (actor == NULL) {
            break;
        }

        thisx = &this->actor;
        if ((actor != thisx) && (actor->update != NULL)) {
            break;
        }

        if (actor->next == NULL) {
            actor = NULL;
            break;
        }

        actor = actor->next;
    }

    return actor;
}

void func_80BBFE60(EnNb* this) {
    this->skelAnime.playSpeed = this->unk_268;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80BBFE8C(EnNb* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 phi_t0 = 0;

    if ((arg1 == 0) || (arg1 == 1)) {
        if ((this->unk_290 != 0) && (this->unk_290 != 1)) {
            phi_v1 = true;
        }
    } else if (arg1 != this->unk_290) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_290 = arg1;
        phi_t0 = func_8013BC6C(&this->skelAnime, D_80BC1628, arg1);
        this->unk_268 = this->skelAnime.playSpeed;
    }

    return phi_t0;
}

void func_80BBFF24(EnNb* this, GlobalContext* globalCtx) {
    f32 diff;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);

    diff = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = diff;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

Actor* func_80BBFF90(EnNb* this, GlobalContext* globalCtx) {
    Actor* phi_v1;

    if (this->unk_1DC == 2) {
        phi_v1 = func_80BBFDB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AN);
    } else {
        phi_v1 = &GET_PLAYER(globalCtx)->actor;
    }
    return phi_v1;
}

s32 func_80BBFFD4(EnNb* this, s16 arg1) {
    s32 sp1C = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        sp1C = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }

    return sp1C;
}

s16 func_80BC0050(EnNb* this, s32 arg1) {
    s16 cutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < arg1; i++) {
        cutscene = ActorCutscene_GetAdditionalCutscene(cutscene);
    }

    return cutscene;
}

s32 func_80BC00AC(EnNb* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80BC0050(this, 0);
    s32 phi_v1 = 0;

    switch (this->unk_288) {
        case 0x0:
            if (func_80BBFFD4(this, sp2A) != 0) {
                case 0x2:
                case 0x4:
                case 0x6:
                case 0x8:
                    func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
                    this->unk_288++;
                    phi_v1 = 1;
            }
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), this->actor.child);
            }
            this->unk_288++;
            phi_v1 = 1;
            break;

        case 0x9:
            ActorCutscene_Stop(sp2A);
            this->unk_288++;
            phi_v1 = 1;
            break;
    }

    return phi_v1;
}

s32 func_80BC01DC(EnNb* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s32 sp2C = 0;

    switch (this->unk_288) {
        case 0x0:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_ALL_NIGHT) {
                this->unk_288 = 1;
            } else {
                this->unk_288 = 5;
            }
            break;

        case 0x1:
            func_8016A268(globalCtx, 1, 0, 0, 0, 0);
            this->unk_286 = 0x28;
            this->unk_288 = (u16)((s16)this->unk_288 + 1);
            break;

        case 0x2:
            gGameInfo->data[0x224] = (s16)(s32)(255.0f - (((f32)ABS_ALT(20 - this->unk_286) / 20.0f) * 255.0f));

            if (this->unk_286 == 0x14) {
                if ((gSaveContext.eventInf[4] & 4) != 0) {
                    globalCtx->interfaceCtx.unk_31B = 0;
                } else {
                    globalCtx->interfaceCtx.unk_31B = 1;
                }
                globalCtx->interfaceCtx.unk_31A = 6;
                gGameInfo->data[0x59B] = 0xFF;
            }

            if (DECR(this->unk_286) == 0) {
                this->unk_288++;
            }
            break;

        case 0x3:
            globalCtx->interfaceCtx.unk_31A = 4;
            this->unk_288++;
            sp2C = 1;
            break;

        case 0x4:
            globalCtx->interfaceCtx.unk_31A = 5;
            this->unk_288++;
            /* fallthrough */
        case 0x5:
            if (!(gSaveContext.eventInf[4] & 4)) {
                gSaveContext.time = CLOCK_TIME(8, 0);
                Sram_IncrementDay();
            } else {
                func_800FE658(120.0f);
            }

            this->unk_288++;
            globalCtx->nextEntranceIndex = 0xBC20;
            gSaveContext.nextCutsceneIndex = 0;
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 2;
            gSaveContext.nextTransition = 6;
            gSaveContext.eventInf[4] |= 8;
            break;
    }

    return sp2C;
}

UNK_PTR func_80BC045C(EnNb* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[4] & 8) {
        this->unk_28C = func_80BC01DC;
        return &D_80BC1464;
    }

    if (this->unk_1DC == 2) {
        this->unk_28C = func_80BC00AC;
        return &D_80BC1574;
    }

    if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
        return &D_80BC15C8;
    }

    this->unk_28C = func_80BC01DC;
    return &D_80BC1464;
}

s32 func_80BC04FC(EnNb* this, GlobalContext* globalCtx) {
    s32 phi_v1 = 0;

    if ((this->unk_262 % 8) != 0) {
        if (func_800B84D0(&this->actor, globalCtx) != 0) {
            this->unk_262 |= 0x20;
            func_8013AED4(&this->unk_262, 0, 7);
            this->unk_288 = 0;
            this->unk_28C = NULL;
            this->actor.child = this->unk_1E8;
            this->unk_1E0 = func_80BC045C(this, globalCtx);
            this->unk_262 |= 0x20;
            this->actionFunc = func_80BC0EAC;
            phi_v1 = 1;
        }
    }
    return phi_v1;
}

void func_80BC05A8(EnNb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28 = func_80152498(&globalCtx->msgCtx);
    u16 temp_a0 = globalCtx->msgCtx.unk11F04;

    if ((&this->actor == player->targetActor) && ((temp_a0 < 0xFF) || (temp_a0 > 0x200)) && (sp28 == 3) &&
        (this->unk_298 == 3)) {
        if ((globalCtx->state.frames % 3) == 0) {
            if (this->unk_26C == 120.0f) {
                this->unk_26C = 0.0f;
            } else {
                this->unk_26C = 120.0f;
            }
        }
    } else {
        this->unk_26C = 0.0f;
    }

    Math_SmoothStepToF(&this->unk_270, this->unk_26C, 0.8f, 40.0f, 10.0f);
    Matrix_InsertTranslation(this->unk_270, 0.0f, 0.0f, 1);
    this->unk_298 = sp28;
}

void func_80BC06C4(EnNb* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    Player* player;

    Math_Vec3f_Copy(&sp40, &this->unk_1E8->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_27E, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->unk_27E = CLAMP(this->unk_27E, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_1E8->id == 0) {
        player = (Player*)this->unk_1E8;

        sp40.y = player->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1E8->focus.pos);
    }

    Math_ApproachS(&this->unk_27C, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->unk_27C = CLAMP(this->unk_27C, -0x1554, 0x1554);
}

void func_80BC0800(EnNb* this) {
    if (this->unk_262 & 0x20) {
        if ((this->unk_1E8 != NULL) && (this->unk_1E8->update != NULL)) {
            if (DECR(this->unk_282) == 0) {
                func_80BC06C4(this);
                this->unk_262 &= ~0x400;
                this->unk_262 |= 0x100;
                return;
            }
        }
    }

    if ((this->unk_262 & 0x100) != 0) {
        this->unk_262 &= ~0x100;
        this->unk_27C = 0;
        this->unk_27E = 0;
        this->unk_282 = 0x14;
    } else if (DECR(this->unk_282) == 0) {
        this->unk_262 |= 0x400;
    }
}

void func_80BC08E0(EnNb* this, GlobalContext* globalCtx) {
    if (this->unk_284 == 0) {
        func_80BBFE8C(this, 2);
        this->unk_262 |= 0x400;
        this->unk_284++;
        return;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80BBFE8C(this, 1);
        this->unk_262 &= 0xFBFF;
        this->unk_284++;
    }
}

void func_80BC0978(EnNb* this, GlobalContext* globalCtx) {
    if (this->unk_284 == 0) {
        func_80BBFE8C(this, 5);
        this->unk_262 &= ~0x20;
        this->unk_262 |= 0x400;
        this->unk_284 += 1;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80BBFE8C(this, 3);
        this->unk_262 &= 0xFBFF;
        this->unk_284 += 1;
    }
}

s32 func_80BC0A18(EnNb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 sp1A = globalCtx->msgCtx.unk11F04;

    if (player->stateFlags1 & 0x40) {
        this->unk_262 |= 0x80;
        if (this->unk_264 != sp1A) {
            switch (sp1A) {
                case 0x28CF:
                    this->unk_262 |= 0x20;
                    func_80BBFE8C(this, 3);
                    break;

                case 0x2904:
                case 0x290B:
                    this->unk_18C = func_80BC08E0;
                    this->unk_284 = 0;
                    break;

                case 0x28CD:
                    this->unk_18C = func_80BC0978;
                    this->unk_284 = 0;
                    break;

                case 0x28CB:
                    func_80BBFE8C(this, 4);
                    break;

                case 0x28C7:
                case 0x2901:
                case 0x2902:
                case 0x2906:
                case 0x290D:
                case 0x2912:
                    func_80BBFE8C(this, 3);
                    break;
            }
        }
        this->unk_264 = sp1A;
    } else if (this->unk_262 & 0x80) {
        this->unk_18C = NULL;
        this->unk_264 = 0;
        this->unk_262 &= ~0x80;
        func_80BBFE8C(this, 1);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, globalCtx);
    }

    return 0;
}

s32 func_80BC0B98(EnNb* this, GlobalContext* globalCtx, UNK_TYPE arg2) {
    s32 sp24 = 0;

    if (func_80BBFDB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
        func_8013AED4(&this->unk_262, 3, 7);
        this->unk_262 |= 0x20;
        func_80BBFE8C(this, 0);
        sp24 = 1;
    }

    return sp24;
}

s32 func_80BC0C0C(EnNb* this, GlobalContext* globalCtx, UNK_TYPE arg2) {
    if (!(gSaveContext.eventInf[4] & 8)) {
        func_8013AED4(&this->unk_262, 3, 7);
    } else {
        func_8013AED4(&this->unk_262, 4, 7);
    }
    func_80BBFE8C(this, 0);

    return 1;
}

s32 func_80BC0C80(EnNb* this, GlobalContext* globalCtx, u8* arg2) {
    s32 phi_v0;

    this->actor.flags |= 1;
    this->actor.targetMode = 0;
    this->unk_262 = 0;
    this->unk_274 = 40.0f;

    switch (*arg2) {
        default:
            phi_v0 = 0;
            break;

        case 0x1:
        case 0x3:
        case 0x4:
            phi_v0 = func_80BC0C0C(this, globalCtx, arg2);
            break;

        case 0x2:
            phi_v0 = func_80BC0B98(this, globalCtx, arg2);
            break;
    }
    return phi_v0;
}

s32 func_80BC0D08(EnNb* this, GlobalContext* globalCtx) {
    return 0;
}

void func_80BC0D1C(EnNb* this, GlobalContext* globalCtx) {
    if ((this->unk_1DC == 1) || (this->unk_1DC == 2) || (this->unk_1DC == 3) || (this->unk_1DC == 4)) {
        func_80BC0D08(this, globalCtx);
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80BC0D84(EnNb* this, GlobalContext* globalCtx) {
    s32 pad;
    struct_80133038_arg2 sp20;

    this->unk_280 = gGameInfo->data[0xF] + ((void)0, gSaveContext.unk_14);

    if (gSaveContext.eventInf[4] & 8) {
        sp20.unk0 = 1;
        func_80BC0C80(this, globalCtx, &sp20.unk0);
        this->actor.shape.shadowDraw = func_800B3FC0;
        this->actor.flags |= 1;
    } else if ((func_80133038(globalCtx, D_80BC13F0, &sp20) == 0) ||
               ((this->unk_1DC != sp20.unk0) && (func_80BC0C80(this, globalCtx, &sp20.unk0) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~1;
        sp20.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = func_800B3FC0;
        this->actor.flags |= 1;
    }

    this->unk_1DC = sp20.unk0;
    this->unk_1E8 = func_80BBFF90(this, globalCtx);
    func_80BC0D1C(this, globalCtx);
}

void func_80BC0EAC(EnNb* this, GlobalContext* globalCtx) {
    if (func_8010BF58(&this->actor, globalCtx, (s32*)this->unk_1E0, this->unk_28C, &this->unk_1E4) != 0) {
        if ((gSaveContext.eventInf[4] & 8) != 0) {
            gSaveContext.eventInf[4] &= (u8)~0x04;
            gSaveContext.eventInf[4] &= (u8)~0x08;
        }
        func_8013AED4(&this->unk_262, 3, 7);
        if (this->unk_1DC != 2) {
            this->unk_262 &= ~0x20;
        }
        this->actor.child = NULL;
        this->unk_262 |= 0x400;
        this->unk_282 = 0x14;
        this->unk_1E4 = 0;
        this->actionFunc = func_80BC0D84;
    }
}

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_nb_Skel_008C40, NULL, this->jointTable, this->morphTable,
                       8);

    this->unk_290 = -1;
    func_80BBFE8C(this, 0);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_262 = 0;

    if (gSaveContext.eventInf[4] & 8) {
        func_8013AED4(&this->unk_262, 4, 7);
    } else {
        gSaveContext.eventInf[4] &= 0xFB;
        gSaveContext.eventInf[4] &= 0xF7;
    }

    this->actionFunc = func_80BC0D84;
    this->actionFunc(this, globalCtx);
}

void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    globalCtx->interfaceCtx.unk_31A = 3;
}

void EnNb_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    func_80BC04FC(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80BC0A18(this, globalCtx);

    if (this->unk_1DC != 0) {
        func_80BBFE60(this);
        func_80BC0800(this);
        if (Actor_IsActorFacingLink(&this->actor, 0x38E0)) {
            func_8013C964(&this->actor, globalCtx, this->unk_274, 30.0f, 0, this->unk_262 & 7);
        }
        func_80BBFF24(this, globalCtx);
    }
}

// OverrideLimbDraw
s32 func_80BC1174(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 5) {
        func_80BC05A8((EnNb*)thisx, globalCtx);
    }
    return 0;
}

// PostLimbDraw
void func_80BC11B4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;
    Vec3f sp18;

    if ((ActorCutscene_GetCurrentIndex() == -1) && (limbIndex == 5)) {
        Matrix_MultiplyVector3fByState(&D_801D15B0, &sp18);
        Math_ApproachF(&thisx->focus.pos.x, sp18.x, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.y, sp18.y, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.z, sp18.z, 0.6f, 10000.0f);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

// UnkActorDraw
void func_80BC1278(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnNb* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_262 & 0x400)) {
        phi_v1 = false;
        if (this->unk_262 & 0x100) {
            phi_v1 = true;
            phi_v0 = true;
        } else {
            phi_v0 = true;
        }
    } else {
        phi_v1 = false;
        phi_v0 = false;
    }

    if (limbIndex == 5) {
        func_8013AD9C(this->unk_27C + 0x4000, this->unk_27E + this->actor.shape.rot.y + 0x4000, &this->unk_1F0,
                      &this->unk_1FC, phi_v0, phi_v1);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_1F0.x, this->unk_1F0.y, this->unk_1F0.z, 0);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        Matrix_RotateY(this->unk_1FC.y, 1);
        Matrix_InsertXRotation_s(this->unk_1FC.x, 1);
        Matrix_InsertZRotation_s(this->unk_1FC.z, 1);
        Matrix_StatePush();
    }
}

void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    if (this->unk_1DC != 0) {
        func_8012C5B0(globalCtx->state.gfxCtx);
        func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                      func_80BC1174, func_80BC11B4, func_80BC1278, &this->actor);
    }
}
