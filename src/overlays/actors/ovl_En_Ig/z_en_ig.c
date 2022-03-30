/*
 * File: z_en_ig.c
 * Overlay: ovl_En_Ig
 * Description: The Goron named the same as the player
 */

#include "z_en_ig.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_dai/object_dai.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnIg*)thisx)

void EnIg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BF2AF8(EnIg* this, GlobalContext* globalCtx);
void func_80BF2BD4(EnIg* this, GlobalContext* globalCtx);

static s32 D_80BF3260[] = {
    0x0D000100, 0xB10A006C, 0x4E020F19, 0x0F2D4202, 0x0F2D0F32, 0x36004B10, 0x1050210,  0x32103725,
    0x02103711, 0x0F190211, 0x0F12000D, 0x02120006, 0x0001050E, 0x12000600, 0x040E110F, 0x0600020E,
    0x1037110F, 0x0B0E1032, 0x1037060E, 0x0F2D0F32, 0x050E0F19, 0x0F2D0A0A, 0x00615A02, 0x0F2D0F32,
    0x4E020F32, 0x100A4202, 0x100A101E, 0x36004B10, 0x1902101E, 0x10320D02, 0x10321037, 0x01050E10,
    0x32103708, 0x0E101E10, 0x320D0210, 0x1E10320D, 0x02103210, 0x3701050E, 0x10321037, 0x090E101E,
    0x10320E0E, 0x100A101E, 0x030E0F32, 0x100A0C0E, 0x0F2D0F32, 0x07050500,
};

static s32 D_80BF3318[] = { -1, -1, 3, 1, 3, 1, 2, 0, 3, 5, 0, 3, 1, 2, 4 };

static s32 D_80BF3354[] = {
    0x0E28B00C,
    0x10000000,
};

static s32 D_80BF335C[] = {
    0x09000000, 0x4B10001F, 0x170E28B1, 0x0C090000, 0x180E28B2, 0x0C090000, 0x170E28B3, 0x2D000111, 0x37020C09,
    0x00001000, 0x5610002F, 0x170E28B1, 0x0C090000, 0x180E28B5, 0x0C090000, 0x170E28B6, 0x0C090000, 0x180E28B7,
    0x0C090000, 0x170E28B8, 0x2D00010C, 0x09000011, 0x56101009, 0x0000180E, 0x29560C09, 0x0000170E, 0x29570C09,
    0x0000180E, 0x29580C09, 0x0000170E, 0x29592D00, 0x010C0900, 0x00121000,
};

static s32 D_80BF33E0[] = {
    0x0E28B90C,
    0x10000000,
};

static s32 D_80BF33E8[] = {
    0x0E28B40C,
    0x10000000,
};

static s32 D_80BF33F0[] = {
    0x0E295B0C,
    0x10000000,
};

const ActorInit En_Ig_InitVars = {
    ACTOR_EN_IG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnIg),
    (ActorFunc)EnIg_Init,
    (ActorFunc)EnIg_Destroy,
    (ActorFunc)EnIg_Update,
    (ActorFunc)EnIg_Draw,
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
    { 28, 62, 0, { 0, 0, 0 } },
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
    { 0, { { 0, 0, 0 }, 20 }, 100 },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &object_dai_Anim_0048B4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dai_Anim_0048B4, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dai_Anim_005100, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dai_Anim_005100, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dai_Anim_0010F8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dai_Anim_001E44, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dai_Anim_0014BC, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dai_Anim_003CAC, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dai_Anim_0040E0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dai_Anim_0040E0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

Actor* func_80BF1150(EnIg* this, GlobalContext* globalCtx, u8 actorCat, s16 actorId) {
    Actor* foundActor = NULL;
    Actor* temp_v0;

    while (true) {
        foundActor = SubS_FindActor(globalCtx, foundActor, actorCat, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnIg*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        temp_v0 = foundActor->next;
        if (temp_v0 == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = temp_v0;
    }

    return foundActor;
}

EnDoor* func_80BF1200(GlobalContext* globalCtx, s32 arg1) {
    s32 phi_a1;

    switch (arg1) {
        case 5:
        case 6:
        case 7:
        case 9:
            phi_a1 = 11;
            break;

        case 8:
            phi_a1 = 15;
            break;

        default:
            phi_a1 = -1;
            break;
    }
    return SubS_FindDoor(globalCtx, phi_a1);
}

void func_80BF1258(EnIg* this) {
    this->skelAnime.playSpeed = this->unk_3D4;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80BF1284(EnIg* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    switch (arg1) {
        case 0:
        case 1:
            if ((this->unk_3FC != 0) && (this->unk_3FC != 1)) {
                phi_v1 = true;
            }
            break;

        case 2:
        case 3:
            if ((this->unk_3FC != 2) && (this->unk_3FC != 3)) {
                phi_v1 = true;
            }
            break;

        default:
            if (arg1 != this->unk_3FC) {
                phi_v1 = true;
            }
            break;
    }

    if (phi_v1) {
        this->unk_3FC = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg1);
        this->unk_3D4 = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80BF1354(EnIg* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    this->collider2.dim.worldSphere.radius = this->collider2.dim.modelSphere.radius * this->collider2.dim.scale;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
}

void func_80BF13E4(EnIg* this) {
    if ((this->unk_3D0 & 0x100) && (DECR(this->unk_3F0) == 0)) {
        this->unk_3F2++;
        if (this->unk_3F2 >= 4) {
            this->unk_3F0 = Rand_S16Offset(30, 30);
            this->unk_3F2 = 0;
        }
    }
}

Actor* func_80BF146C(EnIg* this, GlobalContext* globalCtx) {
    Actor* retActor;

    if (this->unk_298.unk0 == 3) {
        retActor = func_80BF1150(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AN);
    } else {
        retActor = &GET_PLAYER(globalCtx)->actor;
    }
    return retActor;
}

void func_80BF14B0(EnIg* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;

    Math_Vec3f_Copy(&sp40, &this->unk_2A8->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_3EA, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_3EA = CLAMP(this->unk_3EA, -0x1C70, 0x1C70);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_2A8->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_2A8)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_2A8->focus.pos);
    }

    Math_ApproachS(&this->unk_3E8, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    this->unk_3E8 = CLAMP(this->unk_3E8, -0xE38, 0xE38);
}

void func_80BF15EC(EnIg* this) {
    if ((this->unk_3D0 & 0x20) && (this->unk_2A8 != 0)) {
        if (DECR(this->unk_3EE) == 0) {
            func_80BF14B0(this);
            this->unk_3D0 &= ~0x200;
            this->unk_3D0 |= 0x80;
            return;
        }
    }

    if (this->unk_3D0 & 0x80) {
        this->unk_3D0 &= ~0x80;
        this->unk_3E4 = 0;
        this->unk_3E6 = 0;
        this->unk_3E8 = 0;
        this->unk_3EA = 0;
        this->unk_3EE = 20;
        return;
    }

    if (DECR(this->unk_3EE) == 0) {
        this->unk_3D0 |= 0x200;
    }
}

s32 func_80BF16C8(EnIg* this, s16 arg1) {
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

s16 func_80BF1744(EnIg* this, s32 arg1) {
    s16 cs = -1;
    s32 i;

    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        cs = this->actor.child->cutscene;
        for (i = 0; i < arg1; i++) {
            cs = ActorCutscene_GetAdditionalCutscene(cs);
        }
    }
    return cs;
}

s32 func_80BF17BC(EnIg* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A;
    s32 ret;

    sp2A = func_80BF1744(this, 0);
    ret = false;

    switch (this->unk_3F6) {
        case 0:
            if (func_80BF16C8(this, sp2A)) {
                case 2:
                case 4:
                    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                        Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)),
                                              this->actor.child);
                    }
                    this->unk_3F6++;
                    ret = true;
            }
            break;

        case 1:
        case 3:
            if (!(gSaveContext.save.weekEventReg[75] & 0x10) && (this->unk_3F6 == 3)) {
                ActorCutscene_Stop(sp2A);
                this->unk_3F6 = 5;
            } else {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            }
            this->unk_3F6++;
            ret = true;
            break;

        case 5:
            ActorCutscene_Stop(sp2A);
            this->unk_3F6++;
            ret = true;
            break;
    }
    return ret;
}

s32* func_80BF1920(EnIg* this, GlobalContext* globalCtx) {
    switch (this->unk_298.unk0) {
        case 3:
            this->unk_3F8 = func_80BF17BC;
            return D_80BF335C;

        case 4:
            return D_80BF33F0;

        case 2:
        case 11:
        case 14:
            return D_80BF33E0;

        case 10:
        case 12:
            return D_80BF3354;

        case 13:
            return D_80BF33E8;

        default:
            return NULL;
    }
}

s32 func_80BF19A0(EnIg* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (this->unk_3D0 & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            SubS_UpdateFlags(&this->unk_3D0, 0, 7);
            this->unk_3F6 = 0;
            this->unk_3F8 = NULL;
            this->actor.child = this->unk_2A8;
            this->unk_298.unk4 = func_80BF1920(this, globalCtx);
            if ((this->unk_298.unk0 != 2) && (this->unk_298.unk0 != 3) && (this->unk_298.unk0 != 4)) {
                this->unk_3D0 |= 0x20;
            }
            this->actionFunc = func_80BF2BD4;
            ret = true;
        }
    }
    return ret;
}

void func_80BF1A60(EnIg* this, GlobalContext* globalCtx) {
    if (this->unk_3F4 == 0) {
        func_80BF1284(this, 4);
        this->unk_3F4++;
    } else if ((this->unk_3F4 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80BF1284(this, 5);
        this->unk_3F4++;
    }
}

s32 func_80BF1AE0(EnIg* this, GlobalContext* globalCtx) {
    switch (this->unk_298.unk0) {
        case 3:
            func_80BF1284(this, 0);
            break;

        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            func_80BF1284(this, 2);
            break;
    }
    return true;
}

s32 func_80BF1B40(EnIg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 temp = globalCtx->msgCtx.currentTextId;
    s32 pad;

    if (player->stateFlags1 & 0xC40) {
        this->unk_3D0 |= 0x400;
        if (this->unk_3D2 != temp) {
            if ((this->unk_3FC == 2) || (this->unk_3FC == 3)) {
                func_80BF1284(this, 0);
            }

            if ((temp == 0x28B0) || (temp == 0x28B7)) {
                this->unk_18C = func_80BF1A60;
                this->unk_3F4 = 0;
            }
        }
        this->unk_3D2 = temp;
    } else if (this->unk_3D0 & 0x400) {
        this->unk_3D2 = 0;
        this->unk_3D0 &= ~0x400;
        if (1) {}
        func_80BF1AE0(this, globalCtx);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, globalCtx);
    }

    return false;
}

s32 func_80BF1C44(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2, s32 arg3, s32 arg4) {
    u8 sp4F = ENIG_GET_FF(&this->actor);
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* sp2C;
    s32 pad;
    s32 sp24 = false;

    sp2C = func_80BF1150(this, globalCtx, arg3, arg4);
    this->unk_274 = NULL;

    if (D_80BF3318[arg2->unk0] >= 0) {
        this->unk_274 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80BF3318[arg2->unk0]);
    }

    if ((sp2C != NULL) && (sp2C->update != NULL)) {
        if (this->unk_274 != NULL) {
            sp48 = Lib_SegmentedToVirtual(this->unk_274->points);
            Math_Vec3s_ToVec3f(&sp3C, &sp48[this->unk_274->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &sp48[this->unk_274->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            sp24 = true;
        }
    }
    return sp24;
}

s32 func_80BF1D78(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 sp2C = 0;

    if (func_80BF1C44(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_AN)) {
        func_80BF1284(this, 0);
        SubS_UpdateFlags(&this->unk_3D0, 3, 7);
        this->unk_3D0 |= 0x20;
        this->unk_3D0 |= 0x100;
        sp2C = true;
    }
    return sp2C;
}

s32 func_80BF1DF4(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp56 = gSaveContext.save.time - 0x3FFC;
    u8 sp55 = ENIG_GET_FF(&this->actor);
    EnDoor* door;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad;
    s32 ret = false;

    this->unk_274 = NULL;
    door = func_80BF1200(globalCtx, arg2->unk0);

    if (D_80BF3318[arg2->unk0] >= 0) {
        this->unk_274 = SubS_GetAdditionalPath(globalCtx, sp55, D_80BF3318[arg2->unk0]);
    }

    if ((door != NULL) && (door->dyna.actor.update != NULL)) {
        if (this->unk_274 != NULL) {
            sp4C = Lib_SegmentedToVirtual(this->unk_274->points);
            Math_Vec3s_ToVec3f(&sp40, &sp4C[0]);
            Math_Vec3s_ToVec3f(&sp34, &sp4C[1]);
            Math_Vec3f_Copy(&this->unk_2B0, &sp40);
            Math_Vec3f_Copy(&this->unk_2BC, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, door->dyna.actor.shape.rot.y)) <= 0x4000) {
                this->unk_2A4 = -75;
            } else {
                this->unk_2A4 = 75;
            }

            this->unk_3E0 = arg2->unk8 - arg2->unk4;
            this->unk_3E2 = sp56 - arg2->unk4;
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_3D0 |= 0x100;
            func_80BF1284(this, 3);
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }
    return ret;
}

s32 func_80BF1FA8(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp2E = gSaveContext.save.time - 0x3FFC;
    u16 phi_v1;
    u8 sp2B = ENIG_GET_FF(&this->actor);
    s32 temp_t8;
    s32 ret = false;

    this->unk_274 = NULL;

    if (D_80BF3318[arg2->unk0] >= 0) {
        this->unk_274 = SubS_GetAdditionalPath(globalCtx, sp2B, D_80BF3318[arg2->unk0]);
    }

    if ((this->unk_274 != NULL) && (this->unk_274->count < 3)) {
        this->unk_274 = NULL;
    }

    if (this->unk_274 != NULL) {
        temp_t8 = this->unk_298.unk0;
        if ((temp_t8 < 10) && (temp_t8 != 0) && (this->unk_3EC >= 0)) {
            phi_v1 = sp2E;
        } else {
            phi_v1 = arg2->unk4;
        }

        if (arg2->unk8 < phi_v1) {
            this->unk_288 = (phi_v1 - arg2->unk8) + 0xFFFF;
        } else {
            this->unk_288 = arg2->unk8 - phi_v1;
        }

        this->unk_294 = sp2E - phi_v1;

        phi_v1 = (this->unk_274->count - 2) & 0xFFFF;

        this->unk_28C = this->unk_288 / phi_v1;
        this->unk_290 = (this->unk_294 / this->unk_28C) + 2;

        this->unk_3D0 &= ~0x8;
        this->unk_3D0 &= ~0x10;
        SubS_UpdateFlags(&this->unk_3D0, 3, 7);
        this->unk_3D0 |= 0x100;
        func_80BF1284(this, 2);
        this->actor.gravity = -1.0f;
        ret = true;
    }
    return ret;
}

s32 func_80BF219C(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u8 sp4F = ENIG_GET_FF(&this->actor);
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;

    this->unk_274 = NULL;

    if (D_80BF3318[arg2->unk0] >= 0) {
        this->unk_274 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80BF3318[arg2->unk0]);
    }

    if ((this->unk_274 != 0) && (this->unk_274->count >= 2)) {
        sp30 = Lib_SegmentedToVirtual(this->unk_274->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[this->unk_274->count - 1]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[this->unk_274->count - 2]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (arg2->unk0) {
            case 2:
                this->actor.home.rot.y = this->actor.world.rot.y;
                this->actor.home.rot.y += 0x8000;
                SubS_UpdateFlags(&this->unk_3D0, 3, 7);
                this->unk_3D0 |= 0x100;
                func_80BF1284(this, 1);
                break;

            case 4:
                this->actor.world.rot.y += 0x8000;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                SubS_UpdateFlags(&this->unk_3D0, 3, 7);
                this->unk_3D0 |= 0x100;
                func_80BF1284(this, 8);
                break;
        }
        ret = true;
    }
    return ret;
}

s32 func_80BF2368(EnIg* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    this->actor.targetMode = 0;
    this->unk_3D0 = 0;
    this->actor.flags |= ACTOR_FLAG_1;

    switch (arg2->unk0) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            ret = func_80BF1DF4(this, globalCtx, arg2);
            break;

        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            ret = func_80BF1FA8(this, globalCtx, arg2);
            break;

        case 2:
        case 4:
            ret = func_80BF219C(this, globalCtx, arg2);
            break;

        case 3:
            ret = func_80BF1D78(this, globalCtx, arg2);
            break;
    }
    return ret;
}

s32 func_80BF2400(EnIg* this, GlobalContext* globalCtx) {
    Vec3f sp2C;
    Vec3f sp20;

    if ((this->unk_2A8 != NULL) && (this->unk_2A8->update != NULL)) {
        Math_Vec3f_Copy(&sp2C, &this->unk_2A8->world.pos);
        Math_Vec3f_Copy(&sp20, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp20, &sp2C);
    }

    return true;
}

s32 func_80BF2470(EnIg* this, GlobalContext* globalCtx) {
    EnDoor* door = func_80BF1200(globalCtx, this->unk_298.unk0);
    Vec3f sp38;
    f32 temp;
    s32 pad;

    if (!func_8013AD6C(globalCtx) && (this->unk_3EC != 0)) {
        if ((door != NULL) && (door->dyna.actor.update != NULL)) {
            if (((f32)this->unk_3E2 / this->unk_3E0) <= 0.9f) {
                door->unk_1A7 = this->unk_2A4;
            } else {
                door->unk_1A7 = 0;
            }
        }
        this->unk_3E2 = CLAMP(this->unk_3E2, 0, this->unk_3E0);
        temp = Math_Vec3f_DistXZ(&this->unk_2B0, &this->unk_2BC) / this->unk_3E0;
        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_3E2 * temp;
        Lib_Vec3f_TranslateAndRotateY(&this->unk_2B0, this->actor.world.rot.y, &sp38, &this->actor.world.pos);
        this->unk_3E2 += this->unk_3EC;
        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 13.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_PIRATE_WALK);
        }
    }
    return false;
}

s32 func_80BF25E8(EnIg* this, GlobalContext* globalCtx) {
    f32 sp7C[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54 = 0;
    s32 sp50 = 0;
    s32 pad;

    func_8013AF00(sp7C, 3, this->unk_274->count + 3);
    if (!(this->unk_3D0 & 8)) {
        sp58 = gZeroVec3f;
        func_8013B6B0(this->unk_274, &this->unk_284, &this->unk_294, this->unk_28C, this->unk_288, &this->unk_290, sp7C,
                      &sp58, this->unk_3EC);
        func_8013B878(globalCtx, this->unk_274, this->unk_290, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->unk_3D0 |= 8;
    } else {
        sp58 = this->unk_278;
    }

    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;

    if (func_8013AD6C(globalCtx)) {
        sp54 = this->unk_294;
        sp50 = this->unk_290;
        sp58 = this->actor.world.pos;
    }

    this->unk_278 = gZeroVec3f;

    if (func_8013B6B0(this->unk_274, &this->unk_284, &this->unk_294, this->unk_28C, this->unk_288, &this->unk_290, sp7C,
                      &this->unk_278, this->unk_3EC)) {
        this->unk_3D0 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->unk_278;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (func_8013AD6C(globalCtx)) {
        this->unk_294 = sp54;
        this->unk_290 = sp50;
        this->unk_278 = sp58;
    } else if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_PIRATE_WALK);
    }
    return false;
}

s32 func_80BF2890(EnIg* this, GlobalContext* globalCtx) {
    if ((this->unk_3D0 & 0x100) && (this->unk_3F2 == 2)) {
        this->unk_3D0 &= ~0x100;
    }

    if (!(this->unk_3D0 & 0x100) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_408 != 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE1);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SNORE2);
        }
        this->unk_408 ^= 1;
    }
    return true;
}

s32 func_80BF293C(EnIg* this, GlobalContext* globalCtx) {
    if (this->actor.world.rot.y != this->actor.home.rot.y) {
        if ((this->actor.world.rot.y / 182) != (this->actor.home.rot.y / 182)) {
            Math_ApproachS(&this->actor.world.rot.y, this->actor.home.rot.y, 3, 0x2AA8);
        } else {
            this->actor.world.rot.y = this->actor.home.rot.y;
            func_80BF1284(this, 7);
        }
    } else if ((this->unk_3FC == 7) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_UpdateFlags(&this->unk_3D0, 3, 7);
        func_80BF1284(this, 9);
    }
    return true;
}

void func_80BF2A50(EnIg* this, GlobalContext* globalCtx) {
    switch (this->unk_298.unk0) {
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            func_80BF25E8(this, globalCtx);
            break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            func_80BF2470(this, globalCtx);
            break;

        case 2:
            func_80BF293C(this, globalCtx);
            break;

        case 3:
            func_80BF2400(this, globalCtx);
            break;

        case 4:
            func_80BF2890(this, globalCtx);
            break;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80BF2AF8(EnIg* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.save.daySpeed;
    struct_80133038_arg2 sp20;

    this->unk_3EC = REG(15) + *unk_14;

    if (!func_80133038(globalCtx, D_80BF3260, &sp20) ||
        ((this->unk_298.unk0 != sp20.unk0) && !func_80BF2368(this, globalCtx, &sp20))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp20.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->unk_2A8 = func_80BF146C(this, globalCtx);
    this->unk_298.unk0 = sp20.unk0;
    func_80BF2A50(this, globalCtx);
}

void func_80BF2BD4(EnIg* this, GlobalContext* globalCtx) {
    s16 yaw;
    Vec3f sp38;
    Vec3f sp2C;

    if (func_8010BF58(&this->actor, globalCtx, this->unk_298.unk4, this->unk_3F8, &this->unk_298.unk8)) {
        SubS_UpdateFlags(&this->unk_3D0, 3, 7);
        this->unk_3D0 &= ~0x20;
        this->unk_3D0 |= 0x200;
        this->unk_3EE = 20;
        this->unk_298.unk8 = 0;
        this->actionFunc = func_80BF2AF8;
    } else if (((this->unk_298.unk0 != 2) && (this->unk_298.unk0 != 4)) &&
               ((this->unk_2A8 != NULL) && (this->unk_2A8->update != NULL))) {
        Math_Vec3f_Copy(&sp38, &this->unk_2A8->world.pos);
        Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
        yaw = Math_Vec3f_Yaw(&sp2C, &sp38);
        Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
    }
}

void EnIg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnIg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 28.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dai_Skel_0130D0, NULL, this->jointTable, this->morphTable,
                       19);
    this->unk_3FC = -1;
    func_80BF1284(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(globalCtx, &this->collider2, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_298.unk0 = 0;
    this->actor.gravity = 0.0f;
    this->actionFunc = func_80BF2AF8;
    this->actionFunc(this, globalCtx);
}

void EnIg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnIg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroySphere(globalCtx, &this->collider2);
}

void EnIg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnIg* this = THIS;

    func_80BF19A0(this, globalCtx);

    this->actionFunc(this, globalCtx);

    func_80BF1B40(this, globalCtx);

    if (this->unk_298.unk0 != 0) {
        func_80BF1258(this);
        func_80BF13E4(this);
        func_80BF15EC(this);
        func_8013C964(&this->actor, globalCtx, 60.0f, 30.0f, 0, this->unk_3D0 & 7);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        func_80BF1354(this, globalCtx);
    }
}

s32 EnIg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnIg* this = THIS;

    if (limbIndex == 10) {
        *dList = NULL;
    }
    return false;
}

void EnIg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80BF351C = { 1800.0f, -2000.0f, 0.0f };
    static Vec3f D_80BF3528 = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnIg* this = THIS;
    Vec3f sp2C;

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&D_80BF3528, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);

        gSPDisplayList((*gfx)++, object_dai_DL_008710);
        gSPDisplayList((*gfx)++, object_dai_DL_0087B8);
    }

    if (limbIndex == 12) {
        gSPDisplayList((*gfx)++, object_dai_DL_0089D8);
    }

    if (limbIndex == 9) {
        gSPDisplayList((*gfx)++, object_dai_DL_008B00);
        Matrix_MultiplyVector3fByState(&D_80BF351C, &sp2C);
        Math_Vec3f_ToVec3s(&this->collider2.dim.worldSphere.center, &sp2C);
    }

    if (limbIndex == 10) {
        Matrix_CopyCurrentState(&this->unk_190);
    }
}

void EnIg_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx, Gfx** gfx) {
    EnIg* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_3D0 & 0x200)) {
        if (this->unk_3D0 & 0x80) {
            phi_v1 = 1;
        } else {
            phi_v1 = 0;
        }
        phi_v0 = 1;
    } else {
        phi_v1 = 0;
        phi_v0 = 0;
    }

    if (limbIndex == 9) {
        func_8013AD9C(this->unk_3E8 + 0x4000, this->unk_3EA + this->actor.shape.rot.y + 0x4000, &this->unk_2D4,
                      &this->unk_2E6, phi_v0, phi_v1);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_2D4.x, this->unk_2D4.y, this->unk_2D4.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_2E6.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_2E6.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2E6.z, MTXMODE_APPLY);
        Matrix_StatePush();
    }
}

void EnIg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80BF3534[] = {
        object_dai_Tex_0107B0, object_dai_Tex_010FB0, object_dai_Tex_0117B0,
        object_dai_Tex_011FB0, object_dai_Tex_0127B0,
    };
    s32 pad;
    EnIg* this = THIS;

    if (this->unk_298.unk0 != 0) {
        func_8012C28C(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BF3534[this->unk_3F2]));

        POLY_OPA_DISP = SubS_DrawTransformFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnIg_OverrideLimbDraw, EnIg_PostLimbDraw,
                                               EnIg_TransformLimbDraw, &this->actor, POLY_OPA_DISP);
        Matrix_SetCurrentState(&this->unk_190);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_dai_DL_00C538);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
