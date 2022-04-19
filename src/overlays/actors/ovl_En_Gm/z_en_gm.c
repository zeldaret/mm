/*
 * File: z_en_gm.c
 * Overlay: ovl_En_Gm
 * Description: Gorman
 */

#include "z_en_gm.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_in2/object_in2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnGm*)thisx)

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80950CDC(EnGm* this, GlobalContext* globalCtx);
void func_80950DB8(EnGm* this, GlobalContext* globalCtx);

static u32 D_80951820[] = {
    0x0D000101, 0x360A0061, 0x25020600, 0x09001902, 0x0900090A, 0x0D02090A, 0x090F0105, 0x0E090A09, 0x0F0F0E09,
    0x00090A18, 0x0E060009, 0x00060A00, 0x6C490209, 0x0A090F3D, 0x02090F0A, 0x0031020A, 0x000A0525, 0x020C0F0C,
    0x1419020C, 0x140C320D, 0x020C320C, 0x3701050E, 0x0C320C37, 0x0C0E0C14, 0x0C32160E, 0x0C0F0C14, 0x0B0E0A00,
    0x0A050A0E, 0x090F0A00, 0x150E090A, 0x090F090B, 0x00120085, 0x020A000A, 0x0579020A, 0x050A0A6D, 0x020A0A0A,
    0x1E61020A, 0x1E0A2855, 0x020A280A, 0x2D49020A, 0x2D0A373D, 0x020A370B, 0x2D31020B, 0x2D0B3725, 0x020B370C,
    0x0019020C, 0x000C0F0D, 0x020C0F0C, 0x1401050E, 0x0C0F0C14, 0x110E0C00, 0x0C0F1D0E, 0x0B370C00, 0x130E0B2D,
    0x0B371C0E, 0x0A370B2D, 0x020E0A2D, 0x0A371B0E, 0x0A280A2D, 0x120E0A1E, 0x0A281A0E, 0x0A0A0A1E, 0x010E0A05,
    0x0A0A190E, 0x0A000A05, 0x100A0015, 0x31020C37, 0x0D002502, 0x0D000D19, 0x19020D19, 0x15050D02, 0x15370505,
    0x01050E15, 0x37050505, 0x0E0D1915, 0x05030E0D, 0x000D191E, 0x0E0C370D, 0x0014050D, 0x000200AB, 0x01320100,
    0x880A0061, 0x31020600, 0x12002502, 0x12001500, 0x19021500, 0x150A0D02, 0x150A150F, 0x01050E15, 0x0A150F0F,
    0x0E150015, 0x0A180E12, 0x00150006, 0x0E060012, 0x00070A00, 0x6C250215, 0x0A150F19, 0x02150F15, 0x190D0215,
    0x19151E01, 0x050E1519, 0x151E0E0E, 0x150F1519, 0x170E150A, 0x150F0D0A, 0x00152502, 0x151E152D, 0x1902152D,
    0x160A0D02, 0x160A0600, 0x01050E16, 0x0A060005, 0x0E152D16, 0x0A1E0E15, 0x1E152D14, 0x050A0061, 0x19020600,
    0x12000D02, 0x12000600, 0x01050E00, 0x00000008, 0x0E060012, 0x00070505,
};

static s32 D_80951A0C[] = {
    -1, 1, 4, 1, -1, 1, -1, -1, -1, 0, 2, 3, 5, 6, 8, 1, 0, 8, 3, 6, 0, 1, 4, 7, 0, 1, 2, 4, 5, 7, 1,
};

static s32 D_80951A88[] = { 0x0E2AB92D, 0x000A0C10 };

static s32 D_80951A90[] = { 0x0E2ABA2D, 0x000A0C10 };

static s32 D_80951A98[] = {
    0x00564000, 0x1A090000, 0x0E2AA40C, 0x09000017, 0x0E2AA52D, 0x000A0C09, 0x00001211, 0x56401009,
    0x00000E2A, 0xEC0C0900, 0x00170E2A, 0xED0C0900, 0x00180E2A, 0xEE2D000A, 0x0C090000, 0x12100000,
};

static s32 D_80951AD8[] = {
    0x00562000, 0xA1090000, 0x0E2AA60C, 0x09000017, 0x0E2AA70C, 0x09000018, 0x0E2AA80C, 0x09000017,
    0x0E2AA90C, 0x09000018, 0x0E2AAA0C, 0x09000017, 0x0E2AAB0C, 0x09000018, 0x0E2AAC0C, 0x09000017,
    0x0E2AAD0C, 0x0F2AAE0C, 0x09000017, 0x0E2AAF0C, 0x09000017, 0x0E2AB00C, 0x09000018, 0x0E2AB10C,
    0x09000017, 0x0E2AB20C, 0x09000017, 0x0E2AB30C, 0x09000017, 0x0E2AB40C, 0x09000018, 0x0E2AB50C,
    0x09000017, 0x0E2AB60C, 0x09000018, 0x0E2AB70C, 0x09000017, 0x0E2AB82D, 0x00082D00, 0x092D000A,
    0x0C115620, 0x12100900, 0x000E2AEA, 0x0C090000, 0x170E2AEB, 0x2D00082D, 0x000A0C09, 0x00001210,
};

static s32 D_80951B98[] = {
    0x004B0100, 0x42090000, 0x0900000E, 0x2B010C09, 0x0000170E, 0x2B020C09, 0x0000180E,
    0x2B030C09, 0x0000170E, 0x2B040C0F, 0x2B050C09, 0x0000180E, 0x2B060C09, 0x0000170E,
    0x2B072D00, 0x0A0C114B, 0x01150900, 0x0012100E, 0x2B082D00, 0x0A0C1210,
};

static s32 D_80951BE8[] = {
    0x09000000, 0x32010031, 0x00338000, 0x2C004B02, 0x000D0E2B, 0x132D000A, 0x0C114B02, 0x1900150E, 0x2B140C0F,
    0x2B150C0F, 0x2B160C0F, 0x2B170C0F, 0x2B180C15, 0x09000012, 0x100E2B12, 0x2D000A0C, 0x10000000,
};

static s32 D_80951C2C[] = { 0x0E295A2D, 0x000A0C10 };

static s32 D_80951C34[] = { 0x0E29622D, 0x000A0C10 };

const ActorInit En_Gm_InitVars = {
    ACTOR_EN_GM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IN2,
    sizeof(EnGm),
    (ActorFunc)EnGm_Init,
    (ActorFunc)EnGm_Destroy,
    (ActorFunc)EnGm_Update,
    (ActorFunc)EnGm_Draw,
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
    { 14, 62, 0, { 0, 0, 0 } },
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

static AnimationInfoS D_80951CC0[] = {
    { &object_in2_Anim_009CDC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_in2_Anim_009CDC, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_in2_Anim_00A5E0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_in2_Anim_00A70C, 1.0f, 0, 1, ANIMMODE_LOOP, 0 },
    { &object_in2_Anim_008090, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_in2_Anim_00898C, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_in2_Anim_009450, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_in2_Anim_00AD18, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_in2_Anim_00AD18, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_in2_Anim_00B8B0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_in2_Anim_00BA80, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_in2_Anim_00C03C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_in2_Anim_00B990, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

Actor* func_8094DEE0(EnGm* this, GlobalContext* globalCtx, u8 arg2, s16 arg3) {
    Actor* foundActor = NULL;
    Actor* actor;

    while (true) {
        actor = SubS_FindActor(globalCtx, foundActor, arg2, arg3);
        foundActor = actor;
        if (actor == NULL) {
            break;
        }

        if ((this != (EnGm*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = actor;
    }

    return foundActor;
}

EnDoor* func_8094DF90(GlobalContext* globalCtx, s32 arg1) {
    s32 phi_a1;

    switch (arg1) {
        case 9:
        case 13:
        case 15:
            phi_a1 = 11;
            break;

        case 10:
        case 11:
        case 16:
        case 17:
            phi_a1 = 17;
            break;

        case 12:
        case 14:
        case 20:
            phi_a1 = 10;
            break;

        case 18:
        case 19:
            phi_a1 = 19;
            break;

        default:
            phi_a1 = -1;
    }

    return SubS_FindDoor(globalCtx, phi_a1);
}

s32 func_8094DFF8(EnGm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (this->unk_262 < 0) {
        return false;
    }

    if (this->unk_262 >= 0) {
        this->skelAnime.playSpeed = this->unk_3A8;
        ret = SkelAnime_Update(&this->skelAnime);
    }

    return ret;
}

s32 func_8094E054(EnGm* this, GlobalContext* globalCtx, s32 arg2) {
    s8 tmp = this->unk_262;
    s32 phi_v1 = false;
    s32 ret = false;

    if ((arg2 == 0) || (arg2 == 1)) {
        if ((this->unk_3E8 != 0) && (this->unk_3E8 != 1)) {
            phi_v1 = true;
        }
    } else if (arg2 != this->unk_3E8) {
        phi_v1 = true;
    }

    if (phi_v1) {
        if (tmp >= 0) {
            this->unk_3E8 = arg2;
            ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80951CC0, arg2);
            this->unk_3A8 = this->skelAnime.playSpeed;
        }
    }

    return ret;
}

s32 func_8094E0F8(EnGm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_260 != globalCtx->roomCtx.currRoom.num) && (globalCtx->roomCtx.unk31 == 0)) {
        this->unk_260 = globalCtx->roomCtx.currRoom.num;
        this->unk_262 = SubS_GetObjectIndex(OBJECT_IN2, globalCtx);
        this->actor.draw = NULL;
        this->unk_3FC = 1;
    }

    if (this->unk_3FC == 0) {
        return false;
    }

    if ((this->unk_262 < 0) || !SubS_IsObjectLoaded(this->unk_262, globalCtx)) {
        ret = true;
    } else {
        this->actor.draw = EnGm_Draw;
        if (this->unk_258 == 2) {
            this->unk_268 = NULL;
            this->unk_3B8 = 0;
        }
        this->unk_3FC = 0;
    }

    return ret;
}

void func_8094E1DC(EnGm* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp;

    if (this->unk_258 == 7) {
        temp = this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
        this->colliderSphere.dim.worldSphere.radius = temp;
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }
}

void func_8094E278(GlobalContext* globalCtx) {
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_DM_CHAR07, 115.0f, 32.0f, -121.0f, 0, 0, 0, 3);
}

void func_8094E2D0(EnGm* this) {
    s32 phi_a1 = false;

    if (this->unk_3A4 & 0x100) {
        if (DECR(this->unk_3CC) == 0) {
            switch (this->unk_3CA) {
                case 1:
                    if ((this->unk_3CE == 5) || (this->unk_3CE == 2)) {
                        phi_a1 = true;
                        this->unk_3CE = 5;
                    }
                    break;

                case 2:
                    if ((this->unk_3CE == 4) || (this->unk_3CE == 2)) {
                        phi_a1 = true;
                        this->unk_3CE = 4;
                    }
                    break;

                case 3:
                    if (this->unk_3CE == 2) {
                        phi_a1 = true;
                        this->unk_3CE = 2;
                    }
                    break;

                case 4:
                    if (this->unk_3CE == 1) {
                        phi_a1 = true;
                        this->unk_3CE = 1;
                    }
                    break;
            }

            if (!phi_a1 && ((this->unk_3CE == 4) || (this->unk_3CE == 5))) {
                this->unk_3CE = 1;
            }

            if (!phi_a1) {
                this->unk_3CE++;
                if (this->unk_3CE >= 4) {
                    if (this->unk_3CA == 0) {
                        this->unk_3CC = Rand_S16Offset(30, 30);
                    } else {
                        this->unk_3CC = 8;
                    }
                    this->unk_3CE = 0;
                }
            }
        }
    }
}

s32 func_8094E454(EnGm* this, s16 arg1) {
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

s16 func_8094E4D0(EnGm* this, s32 arg1) {
    s32 i;
    s16 cutscene = this->actor.cutscene;

    for (i = 0; i < arg1; i++) {
        cutscene = ActorCutscene_GetAdditionalCutscene(cutscene);
    }

    return cutscene;
}

s32 func_8094E52C(EnGm* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_8094E4D0(this, 0);
    s32 ret = false;

    switch (this->unk_3E0) {
        case 0:
            if (!func_8094E454(this, sp2A)) {
                break;
            }

        case 2:
            if (!(gSaveContext.save.weekEventReg[86] & 0x40) && (this->unk_3E0 == 2)) {
                ActorCutscene_Stop(sp2A);
            } else {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            }
            this->unk_3E0++;
            ret = true;
            break;

        case 1:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)),
                                      this->actor.child);
            }
            this->unk_3E0++;
            ret = true;
            break;

        case 3:
            ActorCutscene_Stop(sp2A);
            this->unk_3E0++;
            ret = true;
            break;
    }

    return ret;
}

s32 func_8094E69C(EnGm* this, GlobalContext* globalCtx) {
    Camera* camera;
    s16 sp4A = func_8094E4D0(this, 0);
    s16 sp48;
    Vec3f sp3C;
    Vec3f sp30;
    s32 ret = false;

    switch (this->unk_3E0) {
        case 0:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
            func_8094E054(this, globalCtx, 2);
            this->unk_3E2 = 0;
            this->unk_3E0++;
            break;

        case 1:
            if ((this->actor.child != NULL) || (this->actor.child->update != NULL)) {
                Math_Vec3f_Copy(&sp3C, &this->actor.child->world.pos);
                Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
                sp48 = Math_Vec3f_Yaw(&sp30, &sp3C);
                this->unk_3E2++;
                if (((this->actor.shape.rot.y / 364) != (sp48 / 364)) && (this->unk_3E2 < 20)) {
                    Math_ApproachS(&this->actor.shape.rot.y, sp48, 3, 0x2AA8);
                } else {
                    this->actor.shape.rot.y = sp48;
                    this->unk_3A4 |= 0x20;
                    this->unk_3E2 = 0;
                    this->unk_3E0++;
                    ret = true;
                }
            } else {
                this->unk_3A4 |= 0x20;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                this->unk_3E0++;
                ret = true;
            }
            break;

        case 2:
            if (func_8094E454(this, sp4A)) {
                case 4:
                case 6:
                    camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp4A));
                    Camera_SetTargetActor(camera, &this->actor);
                    this->unk_3E0++;
                    ret = true;
            }
            break;

        case 3:
        case 5:
        case 7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                camera = Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp4A));
                Camera_SetTargetActor(camera, this->actor.child);
            }
            this->unk_3E0++;
            ret = true;
            break;

        case 8:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
            ActorCutscene_Stop(sp4A);
            this->unk_3E2 = 0;
            this->unk_3E0++;
            break;
        case 9:
            sp48 = this->actor.world.rot.y;
            this->unk_3E2++;
            if (((this->actor.shape.rot.y / 364) != (sp48 / 364)) && (this->unk_3E2 < 20)) {
                Math_ApproachS(&this->actor.shape.rot.y, sp48, 3, 0x2AA8);
                this->unk_3A4 &= ~0x20;
            } else {
                func_8094E054(this, globalCtx, 1);
                this->actor.shape.rot.y = sp48;
                this->unk_3E0++;
                this->unk_3E2 = 0;
                ret = true;
            }
            break;
    }
    return ret;
}

s32 func_8094EA34(EnGm* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Actor* al;
    Actor* toto;

    al = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
    toto = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);
    if ((al == NULL) || (al->update == NULL) || (toto == NULL) || (toto->update == NULL)) {
        this->unk_3E0++;
        return true;
    }

    switch (this->unk_3E0) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 10:
        case 14:
        case 16:
            this->unk_3E0++;
            break;

        case 7:
        case 9:
        case 12:
            this->actor.child = toto;
            this->unk_3E0++;
            break;

        case 1:
        case 3:
        case 5:
        case 8:
        case 11:
        case 13:
        case 15:
        case 17:
            this->actor.child = al;
            this->unk_3E0++;
            break;

        default:
            this->unk_3E0++;
            break;
    }

    return true;
}

s32 func_8094EB1C(EnGm* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s32 ret = false;
    s16 oldYaw;

    switch (this->unk_3E0) {
        case 0:
            if ((gSaveContext.save.weekEventReg[50] & 1) || (gSaveContext.save.weekEventReg[51] & 0x80) ||
                (gSaveContext.save.weekEventReg[75] & 2)) {
                ret = true;
                break;
            }
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
            func_8094E054(this, globalCtx, 2);
            this->unk_3E2 = 0;
            this->unk_3E0++;

        case 1:
            oldYaw = this->actor.yawTowardsPlayer;
            this->unk_3E2++;
            if (((this->actor.shape.rot.y / 364) != (oldYaw / 364)) && (this->unk_3E2 < 20)) {
                Math_ApproachS(&this->actor.shape.rot.y, oldYaw, 3, 0x2AA8);
            } else {
                this->actor.shape.rot.y = oldYaw;
                this->unk_3A4 |= 0x20;
                this->unk_3E2 = 0;
                this->unk_3E0++;
                ret = true;
            }
            break;

        case 2:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
            this->unk_3E2 = 0;
            this->unk_3E0++;

        case 3:
            oldYaw = this->actor.world.rot.y;
            this->unk_3E2++;
            if (((this->actor.shape.rot.y / 364) != (oldYaw / 364)) && (this->unk_3E2 < 20)) {
                Math_ApproachS(&this->actor.shape.rot.y, oldYaw, 3, 0x2AA8);
                this->unk_3A4 &= ~0x20;
            } else {
                func_8094E054(this, globalCtx, 1);
                this->actor.shape.rot.y = oldYaw;
                this->unk_3E2 = 0;
                this->unk_3E0++;
                ret = true;
            }
            break;
    }
    return ret;
}

s32* func_8094EDBC(EnGm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 1:
            this->unk_3E4 = func_8094E52C;
            return D_80951A98;

        case 2:
            this->unk_3E4 = func_8094EA34;
            return D_80951AD8;

        case 3:
            this->unk_3E4 = func_8094E69C;
            return D_80951B98;

        case 5:
            this->unk_3E4 = func_8094EB1C;
            return D_80951BE8;

        case 7:
            return D_80951C2C;

        case 8:
            return D_80951C34;

        case 6:
        case 21:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 30:
            return D_80951A88;

        case 12:
        case 17:
        case 19:
        case 20:
        case 22:
        case 28:
        case 29:
            return D_80951A90;

        default:
            break;
    }
    return NULL;
}

s32 func_8094EE84(EnGm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (this->unk_3A4 & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            SubS_UpdateFlags(&this->unk_3A4, 0, 7);
            this->unk_3E0 = 0;
            this->unk_3E4 = NULL;
            this->actor.child = this->unk_268;
            this->unk_264 = func_8094EDBC(this, globalCtx);

            if ((this->unk_258 == 5) && !(gSaveContext.save.weekEventReg[50] & 1) &&
                !(gSaveContext.save.weekEventReg[51] & 0x80) && !(gSaveContext.save.weekEventReg[75] & 2)) {
                this->unk_3A4 |= 0x20;
            } else if ((this->unk_258 != 1) && (this->unk_258 != 5) && (this->unk_258 != 7)) {
                this->unk_3A4 |= 0x20;
            }

            if ((this->unk_258 == 3) && (gSaveContext.save.weekEventReg[75] & 1)) {
                this->unk_3A4 &= ~0x20;
            }

            this->actionFunc = func_80950DB8;
            ret = true;
        }
    }
    return ret;
}

s32 func_8094EFC4(EnGm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (globalCtx->csCtx.state != 0) {
        if (this->unk_3F8 == 0) {
            if ((globalCtx->sceneNum == SCENE_MILK_BAR) && (gSaveContext.sceneSetupIndex == 2)) {
                func_8094E054(this, globalCtx, 0);
                this->unk_258 = 255;
            }
            this->unk_259 = 255;
            this->unk_3F8 = 1;
        }
        ret = true;
    } else if (this->unk_3F8 != 0) {
        if (globalCtx->sceneNum == SCENE_MILK_BAR) {
            this->unk_400 = 0;
        }
        this->unk_3F8 = 0;
    }
    return ret;
}

Actor* func_8094F074(EnGm* this, GlobalContext* globalCtx) {
    Actor* actor;

    switch (this->unk_258) {
        case 1:
            actor = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_RECEPGIRL);
            break;

        case 2:
            actor = this->unk_268;
            break;

        case 3:
            actor = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TAB);
            break;

        default:
            actor = &GET_PLAYER(globalCtx)->actor;
            break;
    }

    return actor;
}

void func_8094F0E0(EnGm* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;

    Math_Vec3f_Copy(&sp40, &this->unk_268->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    sp32 = Math_Vec3f_Yaw(&sp34, &sp40);
    Math_ApproachS(&this->unk_3BE, (sp32 - this->unk_3C2) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_3BE = CLAMP(this->unk_3BE, -0x1FFE, 0x1FFE);

    Math_ApproachS(&this->unk_3C2, (sp32 - this->unk_3BE) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_3C2 = CLAMP(this->unk_3C2, -0x1C70, 0x1C70);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_268->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_268)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_268->focus.pos);
    }

    Math_ApproachS(&this->unk_3BC, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_3C0, 4, 0x2AA8);
    this->unk_3BC = CLAMP(this->unk_3BC, -0x1554, 0x1554);

    Math_ApproachS(&this->unk_3C0, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_3BC, 4, 0x2AA8);
    this->unk_3C0 = CLAMP(this->unk_3C0, -0xE38, 0xE38);
}

void func_8094F2E8(EnGm* this) {
    if ((this->unk_3A4 & 0x20) && (this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        if (DECR(this->unk_3C6) == 0) {
            func_8094F0E0(this);
            this->unk_3A4 &= ~0x200;
            this->unk_3A4 |= 0x80;
            return;
        }
    }

    if (this->unk_3A4 & 0x80) {
        this->unk_3A4 &= ~0x80;
        this->unk_3BC = 0;
        this->unk_3BE = 0;
        this->unk_3C0 = 0;
        this->unk_3C2 = 0;
        this->unk_3C6 = 20;
    } else if (DECR(this->unk_3C6) == 0) {
        this->unk_3A4 |= 0x200;
    }
}

void func_8094F3D0(EnGm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28 = Message_GetState(&globalCtx->msgCtx);
    s32 var = globalCtx->msgCtx.currentTextId;

    if ((&this->actor == player->targetActor) && ((var < 0xFF) || (var > 0x200)) && (sp28 == 3) &&
        (this->unk_3F0 == 3)) {
        if ((globalCtx->state.frames % 3) == 0) {
            if (this->unk_3AC == 120.0f) {
                this->unk_3AC = 0.0f;
            } else {
                this->unk_3AC = 120.0f;
            }
        }
    } else {
        this->unk_3AC = 0.0f;
    }
    Math_SmoothStepToF(&this->unk_3B0, this->unk_3AC, 0.8f, 40.0f, 10.0f);
    Matrix_InsertTranslation(this->unk_3B0, 0.0f, 0.0f, MTXMODE_APPLY);
    this->unk_3F0 = sp28;
}

s32 func_8094F4EC(EnGm* this, GlobalContext* globalCtx) {
    if ((this->unk_258 != 6) && (this->unk_3E8 == 12)) {
        this->unk_3A4 &= ~0x2000;
        func_8094E054(this, globalCtx, 8);
    }
    return true;
}

s32 func_8094F53C(EnGm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 sp32 = globalCtx->msgCtx.currentTextId;
    Actor* al = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
    Actor* toto = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);

    if (player->stateFlags1 & 0x440) {
        this->unk_3A4 |= 0x400;
        if (this->unk_3A6 != sp32) {
            switch (sp32) {
                case 0x2B13:
                    func_8094E054(this, globalCtx, 2);
                    break;

                case 0x2B14:
                case 0x2B18:
                    func_8094E054(this, globalCtx, 0);
                    break;

                case 0x2B16:
                    func_8094E054(this, globalCtx, 1);
                    break;

                case 0x2B15:
                    func_8094E054(this, globalCtx, 5);
                    break;

                case 0x2B17:
                    func_8094E054(this, globalCtx, 6);
                    break;

                default:
                    if ((this->unk_3E8 == 7) || (this->unk_3E8 == 8)) {
                        this->unk_3A4 |= 0x2000;
                        func_8094E054(this, globalCtx, 12);
                    }
                    break;
            }

            switch (sp32) {
                case 0x2AA6:
                case 0x2AAF:
                case 0x2AB4:
                    if ((al != NULL) && (al->update != NULL)) {
                        this->unk_268 = al;
                    }
                    break;

                case 0x2AAD:
                case 0x2AB0:
                case 0x2AB2:
                    if ((toto != NULL) && (toto->update != NULL)) {
                        this->unk_268 = toto;
                    }
                    break;
            }

            if (sp32 == 0x2AA8) {
                this->unk_3C8 = 0;
                this->unk_3CA = 0;
                this->unk_3CC = 8;
            }
        }
        this->unk_3A6 = sp32;
    } else if (this->unk_3A4 & 0x400) {
        this->unk_18C = NULL;
        this->unk_3A6 = 0;
        this->unk_3A4 &= ~0x400;
        this->unk_3CA = this->unk_3C8;
        this->unk_3CC = 4;
        func_8094F4EC(this, globalCtx);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, globalCtx);
    }

    if ((this->unk_3E8 == 6) && !(globalCtx->actorCtx.unk5 & 0x20) && Animation_OnFrame(&this->skelAnime, 20.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HANKO);
    }

    return false;
}

s32 func_8094F7D0(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2, u8 arg3, s16 arg4) {
    u8 sp4F = ENGM_GET_FF(&this->actor);
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* actor;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    actor = func_8094DEE0(this, globalCtx, arg3, arg4);

    if (D_80951A0C[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80951A0C[arg2->unk0]);
    }

    if ((actor != NULL) && (actor->update != NULL)) {
        if (this->unk_234 != NULL) {
            sp48 = Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp3C, &sp48[this->unk_234->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &sp48[this->unk_234->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }
    return ret;
}

s32 func_8094F904(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp56 = gSaveContext.save.time - 0x3FFC;
    u8 sp55 = ENGM_GET_FF(&this->actor);
    EnDoor* door;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    door = func_8094DF90(globalCtx, arg2->unk0);

    if (D_80951A0C[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp55, D_80951A0C[arg2->unk0]);
    }

    if ((door != NULL) && (door->dyna.actor.update != NULL)) {
        if (this->unk_234 != NULL) {
            sp4C = Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp40, &sp4C[0]);
            Math_Vec3s_ToVec3f(&sp34, &sp4C[1]);
            Math_Vec3f_Copy(&this->unk_278, &sp40);
            Math_Vec3f_Copy(&this->unk_284, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, door->dyna.actor.shape.rot.y)) <= 0x4000) {
                this->unk_261 = -75;
            } else {
                this->unk_261 = 75;
            }

            this->unk_3B8 = arg2->unk8 - arg2->unk4;
            this->unk_3BA = sp56 - arg2->unk4;
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_3A4 |= 0x100;
            this->unk_3A4 |= 0x200;
            func_8094E054(this, globalCtx, 7);
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }
    return ret;
}

s32 func_8094FAC4(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    u16 sp2E = gSaveContext.save.time - 0x3FFC;
    u16 phi_v1;
    u8 sp2B = ENGM_GET_FF(&this->actor);
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    if (D_80951A0C[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp2B, D_80951A0C[arg2->unk0]);
    }

    if ((this->unk_234 != NULL) && (this->unk_234->count < 3)) {
        this->unk_234 = NULL;
    }

    if (this->unk_234 != NULL) {
        if ((this->unk_258 < 9) && (this->unk_258 != 0) && (this->unk_3C4 >= 0)) {
            phi_v1 = sp2E;
        } else {
            phi_v1 = arg2->unk4;
        }

        if (arg2->unk8 < phi_v1) {
            this->unk_248 = (phi_v1 - arg2->unk8) + 0xFFFF;
        } else {
            this->unk_248 = arg2->unk8 - phi_v1;
        }

        this->unk_254 = sp2E - phi_v1;
        phi_v1 = this->unk_234->count - 2;
        this->unk_24C = this->unk_248 / phi_v1;
        this->unk_250 = (this->unk_254 / this->unk_24C) + 2;
        this->unk_3A4 &= ~0x8;
        this->unk_3A4 &= ~0x10;
        SubS_UpdateFlags(&this->unk_3A4, 3, 7);
        this->unk_3A4 |= 0x100;
        this->unk_3A4 |= 0x200;
        func_8094E054(this, globalCtx, 7);
        this->actor.gravity = -1.0f;
        ret = true;
    }
    return ret;
}

s32 func_8094FCC4(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80951D90 = { 64.0f, 0.0f, -122.0f };
    s32 ret = false;

    if (func_8094F7D0(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_TAB)) {
        if (this->unk_258 == 0) {
            Math_Vec3f_Copy(&this->actor.world.pos, &D_80951D90);
            SubS_UpdateFlags(&this->unk_3A4, 3, 7);
            func_8094E054(this, globalCtx, 0);
        } else {
            func_8094E054(this, globalCtx, 9);
            this->skelAnime.moveFlags = 0x10;
        }
        this->unk_3A4 |= 0x100;
        this->unk_3A4 |= 0x200;
        ret = true;
    }
    return ret;
}

s32 func_8094FD88(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_8094F7D0(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_RECEPGIRL)) {
        func_8094E054(this, globalCtx, 11);
        SubS_UpdateFlags(&this->unk_3A4, 3, 7);
        this->unk_3A4 |= 0x100;
        this->unk_3A4 |= 0x200;
        ret = true;
    }
    return ret;
}

s32 func_8094FE10(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;
    Actor* al;

    al = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
    if (func_8094F7D0(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_TOTO) && (al != NULL) && (al->update != NULL)) {
        func_8094E054(this, globalCtx, 11);
        SubS_UpdateFlags(&this->unk_3A4, 3, 7);
        this->unk_268 = al;
        if (!(gSaveContext.save.weekEventReg[86] & 0x20)) {
            this->unk_3C8 = 2;
            this->unk_3CA = 2;
            this->unk_3CC = 8;
        }
        this->unk_3A4 |= (0x100 | 0x20);
        this->unk_3A4 |= 0x200;
        ret = true;
    }
    return ret;
}

s32 func_8094FF04(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80951D9C = { 64.0f, 0.0f, -122.0f };
    u8 sp4F = ENGM_GET_FF(&this->actor);
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;

    if (D_80951A0C[arg2->unk0] >= 0) {
        this->unk_234 = SubS_GetAdditionalPath(globalCtx, sp4F, D_80951A0C[arg2->unk0]);
    }

    if (this->unk_234 != NULL) {
        sp48 = Lib_SegmentedToVirtual(this->unk_234->points);
        Math_Vec3s_ToVec3f(&sp3C, &sp48[this->unk_234->count - 2]);
        Math_Vec3s_ToVec3f(&sp30, &sp48[this->unk_234->count - 1]);
        this->actor.shape.shadowDraw = NULL;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
        if (this->unk_258 == 0) {
            Math_Vec3f_Copy(&this->actor.world.pos, &D_80951D9C);
            SubS_UpdateFlags(&this->unk_3A4, 3, 7);
            this->unk_3C8 = 4;
            this->unk_3CA = 4;
            this->unk_3CC = 8;
            func_8094E054(this, globalCtx, 0);
            func_8094E278(globalCtx);
        } else {
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            func_8094E054(this, globalCtx, 9);
            this->skelAnime.moveFlags = 0x10;
        }
        this->unk_400 = 0;
        this->unk_3A4 |= 0x100;
        this->unk_3A4 |= 0x200;
        ret = true;
    }
    return ret;
}

s32 func_80950088(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80951DA8 = { 278.0f, 0.0f, 223.0f };
    static Vec3s D_80951DB4 = { 0x0000, 0xC000, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80951DA8);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80951DB4);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    SubS_UpdateFlags(&this->unk_3A4, 3, 7);
    this->unk_3A4 |= (0x2000 | 0x100);
    this->unk_3A4 |= 0x200;
    func_8094E054(this, globalCtx, 12);
    return true;
}

s32 func_80950120(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80951DBC = { -525.0f, 214.0f, 515.0f };
    static Vec3s D_80951DC8 = { 0x0000, 0x38E0, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80951DBC);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80951DC8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    SubS_UpdateFlags(&this->unk_3A4, 3, 7);
    this->unk_3A4 |= (0x800 | 0x100);
    this->unk_3A4 |= 0x200;
    func_8094E054(this, globalCtx, 4);
    return true;
}

s32 func_809501B8(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    static Vec3f D_80951DD0 = { -334.0f, 225.0f, 903.0f };
    static Vec3s D_80951DDC = { 0x0000, 0x7FFF, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80951DD0);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80951DDC);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    this->actor.targetMode = 6;
    SubS_UpdateFlags(&this->unk_3A4, 3, 7);
    this->unk_3A4 |= (0x1000 | 0x100);
    this->unk_3A4 |= 0x200;
    this->unk_3C8 = 3;
    this->unk_3CA = 3;
    this->unk_3CC = 8;
    this->actor.targetMode = 6;
    this->unk_3B4 = 60.0f;
    func_8094E054(this, globalCtx, 10);
    return true;
}

s32 func_80950280(EnGm* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 phi_v1;

    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.targetMode = 0;
    this->unk_3A4 = 0;
    this->unk_3C8 = 0;
    this->unk_3CA = 0;
    this->unk_3CC = 8;
    this->unk_3B4 = 40.0f;

    switch (arg2->unk0) {
        case 1:
            phi_v1 = func_8094FD88(this, globalCtx, arg2);
            break;

        case 2:
            phi_v1 = func_8094FE10(this, globalCtx, arg2);
            break;

        case 3:
            phi_v1 = func_8094FCC4(this, globalCtx, arg2);
            break;

        case 5:
            phi_v1 = func_8094FF04(this, globalCtx, arg2);
            break;

        case 6:
            phi_v1 = func_80950088(this, globalCtx, arg2);
            break;

        case 7:
            phi_v1 = func_809501B8(this, globalCtx, arg2);
            break;

        case 8:
            phi_v1 = func_80950120(this, globalCtx, arg2);
            break;

        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            phi_v1 = func_8094F904(this, globalCtx, arg2);
            break;

        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            phi_v1 = func_8094FAC4(this, globalCtx, arg2);
            break;

        default:
            phi_v1 = false;
            break;
    }

    return phi_v1;
}

s32 func_80950388(EnGm* this, GlobalContext* globalCtx) {
    Vec3f sp2C;
    Vec3f sp20;

    if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        Math_Vec3f_Copy(&sp2C, &this->unk_268->world.pos);
        Math_Vec3f_Copy(&sp20, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp20, &sp2C);
    }

    return false;
}

s32 func_809503F8(EnGm* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->unk_3E8 == 9) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
            SubS_UpdateFlags(&this->unk_3A4, 3, 7);
            func_8094E054(this, globalCtx, 0);
        } else {
            AnimationContext_SetMoveActor(globalCtx, &this->actor, &this->skelAnime, 1.0f);
        }
    }
    return false;
}

s32 func_80950490(EnGm* this, GlobalContext* globalCtx) {
    static s32 D_80951DE4[] = {
        1, 5, 5, 1, 6, 5, 1, 5, 6, 1, 5, 6,
    };
    s32 pad;

    if ((gSaveContext.save.weekEventReg[50] & 1) || (gSaveContext.save.weekEventReg[51] & 0x80)) {
        if (this->unk_400 == 0) {
            this->unk_3C8 = 1;
            this->unk_3CA = 1;
            this->unk_3CC = 8;
            this->unk_400 = 1;
            func_8094E054(this, globalCtx, 3);
        }
        return false;
    }

    this->unk_400 = 0;

    switch (this->unk_3E8) {
        case 9:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
                SubS_UpdateFlags(&this->unk_3A4, 3, 7);
                this->unk_3C8 = 4;
                this->unk_3CA = 4;
                this->unk_3CC = 8;
                func_8094E054(this, globalCtx, 0);
                func_8094E278(globalCtx);
            } else {
                AnimationContext_SetMoveActor(globalCtx, &this->actor, &this->skelAnime, 1.0f);
            }
            break;

        case 5:
        case 6:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_8094E054(this, globalCtx, D_80951DE4[this->unk_3F4]);
                this->unk_3F4++;
                this->unk_3F4 %= 12;
                this->unk_3DE = Rand_S16Offset(30, 30);
            }
            break;

        default:
            if (DECR(this->unk_3DE) == 0) {
                func_8094E054(this, globalCtx, D_80951DE4[this->unk_3F4]);
                this->unk_3F4++;
                this->unk_3F4 %= 12;
                this->unk_3DE = Rand_S16Offset(30, 30);
            }
            break;
    }
    return false;
}

s32 func_80950690(EnGm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Actor* al;
    Actor* toto;

    switch (this->unk_258) {
        case 2:
            al = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
            toto = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);
            if ((al != NULL) && (al->update != NULL) && (toto != NULL) && (toto->update != NULL) &&
                !(player->stateFlags1 & 0x40)) {
                if (DECR(this->unk_3B8) == 0) {
                    if (al == this->unk_268) {
                        this->unk_268 = toto;
                    } else {
                        this->unk_268 = al;
                    }
                    this->unk_3B8 = Rand_S16Offset(60, 60);
                }
            }
            break;

        case 7:
            this->unk_3D0 += 992;
            if (DECR(this->unk_3B8) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_GO_SLEEP);
                this->unk_3B8 = 30;
            }
            break;

        case 8:
            break;
    }

    SubS_FillLimbRotTables(globalCtx, this->unk_3D8, this->unk_3D2, ARRAY_COUNT(this->unk_3D8));

    return false;
}

s32 func_80950804(EnGm* this, GlobalContext* globalCtx) {
    EnDoor* door;
    Vec3f sp38;
    s32 pad;
    f32 temp_f0;

    door = func_8094DF90(globalCtx, this->unk_258);
    if (!func_8013AD6C(globalCtx) && (this->unk_3C4 != 0)) {
        if ((door != NULL) && (door->dyna.actor.update != NULL)) {
            if ((this->unk_3BA / (f32)this->unk_3B8) <= 0.9f) {
                door->unk_1A7 = this->unk_261;
            } else {
                door->unk_1A7 = 0;
            }
        }

        this->unk_3BA = CLAMP(this->unk_3BA, 0, this->unk_3B8);
        temp_f0 = Math_Vec3f_DistXZ(&this->unk_278, &this->unk_284) / this->unk_3B8;
        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_3BA * temp_f0;
        Lib_Vec3f_TranslateAndRotateY(&this->unk_278, this->actor.world.rot.y, &sp38, &this->actor.world.pos);
        this->unk_3BA += this->unk_3C4;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 13.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_PIRATE_WALK);
        }
    }

    return false;
}

s32 func_8095097C(EnGm* this, GlobalContext* globalCtx) {
    f32 sp7C[0x109];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54 = 0;
    s32 sp50 = 0;
    s32 pad2;

    func_8013AF00(sp7C, 3, this->unk_234->count + 3);

    if (!(this->unk_3A4 & 8)) {
        sp58 = gZeroVec3f;
        func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &sp58, this->unk_3C4);
        func_8013B878(globalCtx, this->unk_234, this->unk_250, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->unk_3A4 |= 8;
    } else {
        sp58 = this->unk_238;
    }

    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;

    if (func_8013AD6C(globalCtx)) {
        sp54 = this->unk_254;
        sp50 = this->unk_250;
        sp58 = this->actor.world.pos;
    }

    this->unk_238 = gZeroVec3f;

    if (func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &this->unk_238, this->unk_3C4)) {
        this->unk_3A4 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->unk_238;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (func_8013AD6C(globalCtx)) {
        this->unk_254 = sp54;
        this->unk_250 = sp50;
        this->unk_238 = sp58;
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_PIRATE_WALK);
    }
    return false;
}

void func_80950C24(EnGm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 1:
            func_80950388(this, globalCtx);
            break;

        case 2:
        case 6:
        case 7:
        case 8:
            func_80950690(this, globalCtx);
            break;

        case 3:
            func_809503F8(this, globalCtx);
            break;

        case 5:
            func_80950490(this, globalCtx);
            break;

        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            func_80950804(this, globalCtx);
            break;

        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            func_8095097C(this, globalCtx);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80950CDC(EnGm* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.save.daySpeed;
    struct_80133038_arg2 sp20;

    this->unk_3C4 = REG(15) + *unk_14;

    if (!func_80133038(globalCtx, (void*)&D_80951820, &sp20) ||
        ((this->unk_258 != sp20.unk0) && !func_80950280(this, globalCtx, &sp20))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp20.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->unk_258 = sp20.unk0;
    this->unk_268 = func_8094F074(this, globalCtx);
    func_80950C24(this, globalCtx);
}

void func_80950DB8(EnGm* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    Actor* al;

    if (func_8010BF58(&this->actor, globalCtx, this->unk_264, this->unk_3E4, &this->unk_25C)) {
        SubS_UpdateFlags(&this->unk_3A4, 3, 7);
        al = func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
        if ((this->unk_258 == 2) && (al != NULL) && (al->update != NULL)) {
            this->unk_268 = al;
            this->unk_3B8 = Rand_S16Offset(60, 60);
        } else {
            this->unk_3A4 &= ~0x20;
        }
        this->unk_3A4 |= 0x200;
        this->unk_3C6 = 20;
        this->unk_25C = 0;
        this->actionFunc = func_80950CDC;
    } else if ((this->unk_258 != 1) && (this->unk_258 != 2) && (this->unk_258 != 3) && (this->unk_258 != 5) &&
               (this->unk_258 != 7)) {
        if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
            Math_Vec3f_Copy(&sp40, &this->unk_268->world.pos);
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp34, &sp40), 4, 0x2AA8);
        }
    }
    SubS_FillLimbRotTables(globalCtx, this->unk_3D8, this->unk_3D2, ARRAY_COUNT(this->unk_3D8));
}

void func_80950F2C(EnGm* this, GlobalContext* globalCtx) {
    s32 sp50[] = { 0, 0, 3, 2 };
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Vec3f sp3C;
    Vec3f sp30;
    s32 sp2C;
    s16 yaw;

    if (Cutscene_CheckActorAction(globalCtx, 526)) {
        sp2C = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 526)]->action;
        if (this->unk_259 != (sp2C & 0xFF)) {
            if (sp2C == 3) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
            }
            this->unk_259 = sp2C;
            func_8094E054(this, globalCtx, sp50[sp2C]);
        }

        if ((this->unk_259 == 3) && (this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
            Math_Vec3f_Copy(&sp3C, &player->actor.world.pos);
            Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
            yaw = Math_Vec3f_Yaw(&sp30, &sp3C);
            if ((this->actor.shape.rot.y / 0x16C) != (yaw / 0x16C)) {
                Math_ApproachS(&this->actor.shape.rot.y, yaw, 3, 0x2AA8);
                this->unk_3A4 &= ~0x20;
            } else {
                this->actor.shape.rot.y = yaw;
            }
        }
    }
}

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;

    if (func_8094DEE0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_GM)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 22.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_in2_Skel_0078B0, NULL, this->jointTable, this->morphTable,
                       20);
    this->unk_3E8 = -1;
    func_8094E054(this, globalCtx, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.room = -1;
    this->unk_260 = -128;
    this->unk_3FC = 0;
    this->unk_258 = 0;
    this->actionFunc = func_80950CDC;
    this->actionFunc(this, globalCtx);
}

void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
}

void EnGm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;

    if (!func_8094E0F8(this, globalCtx)) {
        if (!func_8094EE84(this, globalCtx) && func_8094EFC4(this, globalCtx)) {
            func_80950F2C(this, globalCtx);
            func_8094DFF8(this, globalCtx);
            func_8094E2D0(this);
            return;
        }

        this->actionFunc(this, globalCtx);

        func_8094F53C(this, globalCtx);

        if (this->unk_258 != 0) {
            func_8094DFF8(this, globalCtx);
            func_8094E2D0(this);
            func_8094F2E8(this);
            func_8013C964(&this->actor, globalCtx, this->unk_3B4, 30.0f, 0, this->unk_3A4 & 7);
            if ((this->unk_258 != 3) && (this->unk_258 != 5) && (this->unk_258 != 8)) {
                Actor_MoveWithGravity(&this->actor);
                Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
            }
            func_8094E1DC(this, globalCtx);
        }
    }
}

s32 EnGm_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnGm* this = THIS;
    s32 phi_v0;

    if (limbIndex == 16) {
        func_8094F3D0(this, globalCtx);
    }

    switch (limbIndex) {
        case 9:
            phi_v0 = 0;
            break;

        case 10:
            phi_v0 = 1;
            break;

        case 13:
            phi_v0 = 2;
            break;

        default:
            phi_v0 = 9;
            break;
    }

    if ((this->unk_3A4 & 0x2000) && (phi_v0 < 9)) {
        rot->y += (s16)(Math_SinS(this->unk_3D8[phi_v0]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->unk_3D2[phi_v0]) * 200.0f);
    }

    return false;
}

void EnGm_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80951E24 = { 1400.0f, 0.0f, 0.0f };
    EnGm* this = THIS;
    s32 pad[4];
    Vec3f sp30;
    s32 pad2;

    if ((ActorCutscene_GetCurrentIndex() == -1) && (limbIndex == 16)) {
        Matrix_MultiplyVector3fByState(&D_80951E24, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((limbIndex == 15) && (this->unk_3A4 & 0x800)) {
        gSPDisplayList(POLY_OPA_DISP++, object_in2_DL_007528);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (limbIndex == 9) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp30);
        Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp30);
    }
}

void EnGm_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnGm* this = THIS;
    s32 phi_v0 = 1;
    s32 phi_v1 = 0;

    if (!(this->unk_3A4 & 0x200)) {
        if (this->unk_3A4 & 0x80) {
            phi_v0 = 1;
            phi_v1 = 1;
        } else {
            phi_v0 = 0;
            phi_v1 = 1;
        }
    } else {
        phi_v0 = 0;
    }

    if (limbIndex == 16) {
        func_8013AD9C(BINANG_ADD(this->unk_3BC + this->unk_3C0, 0x4000),
                      BINANG_ADD(this->unk_3BE + this->unk_3C2 + this->actor.shape.rot.y, 0x4000), &this->unk_290,
                      &this->unk_2A8, phi_v1, phi_v0);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_290.x, this->unk_290.y, this->unk_290.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_2A8.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_2A8.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2A8.z, MTXMODE_APPLY);
        Matrix_StatePush();
    } else if (limbIndex == 9) {
        func_8013AD9C(BINANG_ADD(this->unk_3C0, 0x4000), BINANG_ADD(this->unk_3C2 + this->actor.shape.rot.y, 0x4000),
                      &this->unk_29C, &this->unk_2AE, phi_v1, phi_v0);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_29C.x, this->unk_29C.y, this->unk_29C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_2AE.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_2AE.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2AE.z, MTXMODE_APPLY);
        Matrix_StatePush();
    }
}

void EnGm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80951E30[] = { object_in2_Tex_0054A8, object_in2_Tex_005028, object_in2_Tex_006828,
                                       object_in2_Tex_005028, object_in2_Tex_005CE8, object_in2_Tex_006C68 };
    EnGm* this = THIS;

    if ((this->unk_258 != 0) && (this->unk_262 >= 0)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80951E30[this->unk_3CE]));

        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGm_OverrideLimbDraw, EnGm_PostLimbDraw,
                                       EnGm_TransformLimbDraw, &this->actor);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
