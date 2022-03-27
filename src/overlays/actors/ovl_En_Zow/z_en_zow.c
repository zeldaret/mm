/*
 * File: z_en_zow.c
 * Overlay: ovl_En_Zow
 * Description: Great Bay - Zora Complaining About Water
 */

#include "z_en_zow.h"
#include "objects/object_zo/object_zo.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnZow*)thisx)

void EnZow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BDD350(EnZow* this, GlobalContext* globalCtx);
void func_80BDD570(EnZow* this, GlobalContext* globalCtx);
void func_80BDD634(EnZow* this, GlobalContext* globalCtx);
void func_80BDD6BC(EnZow* this, GlobalContext* globalCtx);
void func_80BDD79C(EnZow* this, GlobalContext* globalCtx);

const ActorInit En_Zow_InitVars = {
    ACTOR_EN_ZOW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZow),
    (ActorFunc)EnZow_Init,
    (ActorFunc)EnZow_Destroy,
    (ActorFunc)EnZow_Update,
    (ActorFunc)EnZow_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
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
    { 30, 40, 0, { 0, 0, 0 } },
};

Vec3f D_80BDDD1C = { 0.0f, 1.0f, 0.0f };

Vec3f D_80BDDD28 = { 0.0f, -1.0f, 0.0f };

void func_80BDC270(EnZowStruct* ptr, Vec3f* arg1, f32 arg2, f32 arg3, u8 arg4) {
    s16 i;

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            ptr->unk_14 = *arg1;
            ptr->unk_04 = arg2;
            ptr->unk_08 = arg3;
            ptr->unk_0F = arg4;
            break;
        }
    }
}

void func_80BDC2D8(EnZow* this, EnZowStruct* ptr, Vec3f* arg2) {
    s16 i;
    f32 temp;

    for (i = 0; i < ARRAY_COUNT(this->unk_2D0); i++, ptr++) {
        if (ptr->unk_00 == 0) {
            temp = this->actor.world.pos.y + this->actor.depthInWater;
            if (temp <= arg2->y) {
                continue;
            }
            ptr->unk_00 = 3;
            ptr->unk_14 = *arg2;
            ptr->unk_20 = *arg2;
            ptr->unk_2C = D_80BDDD1C;
            ptr->unk_04 = ((Rand_ZeroOne() - 0.5f) * 0.02f) + 0.12f;
            break;
        }
    }
}

void func_80BDC3C0(EnZowStruct* ptr, Vec3f* arg1, Vec3f* arg2, f32 arg3) {
    s16 i;

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 != 2) {
            ptr->unk_00 = 2;
            ptr->unk_14 = *arg1;
            ptr->unk_20 = D_80BDDD28;
            ptr->unk_2C = *arg2;
            ptr->unk_0F = (Rand_ZeroOne() * 100.0f) + 100.0f;
            ptr->unk_04 = arg3;
            break;
        }
    }
}

void func_80BDC50C(EnZowStruct* ptr) {
    s16 i;

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 == 1) {
            Math_ApproachF(&ptr->unk_04, ptr->unk_08, 0.2f, 0.8f);

            if (ptr->unk_0F > 20) {
                ptr->unk_0F -= 20;
            } else {
                ptr->unk_0F = 0;
            }

            if (ptr->unk_0F == 0) {
                ptr->unk_00 = 0;
            }
        }
    }
}

void func_80BDC5C8(EnZow* this, EnZowStruct* ptr) {
    f32 temp_f2;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2D0); i++, ptr++) {
        if (ptr->unk_00 == 3) {
            ptr->unk_14.x = ((Rand_ZeroOne() * 0.5f) - 0.25f) + ptr->unk_20.x;
            ptr->unk_14.z = ((Rand_ZeroOne() * 0.5f) - 0.25f) + ptr->unk_20.z;
            ptr->unk_14.y += ptr->unk_2C.y;

            temp_f2 = this->actor.world.pos.y + this->actor.depthInWater;
            if (temp_f2 <= ptr->unk_14.y) {
                ptr->unk_00 = 0;
                ptr->unk_14.y = temp_f2;
                func_80BDC270(ptr, &ptr->unk_14, 0.06f, 0.12f, 200);
            }
        }
    }
}

void func_80BDC6F8(EnZow* this, EnZowStruct* ptr) {
    s16 i;
    f32 temp_f0_2;

    for (i = 0; i < ARRAY_COUNT(this->unk_2D0); i++, ptr++) {
        if (ptr->unk_00 == 2) {
            ptr->unk_14.x += ptr->unk_2C.x;
            ptr->unk_14.y += ptr->unk_2C.y;
            ptr->unk_14.z += ptr->unk_2C.z;

            if (ptr->unk_2C.y >= -20.0f) {
                ptr->unk_2C.y += ptr->unk_20.y;
            } else {
                ptr->unk_2C.y = -20.0f;
                ptr->unk_20.y = 0.0f;
            }

            temp_f0_2 = this->actor.world.pos.y + this->actor.depthInWater;
            if (ptr->unk_14.y < temp_f0_2) {
                ptr->unk_00 = 0;
                ptr->unk_14.y = temp_f0_2;
                func_80BDC270(ptr, &ptr->unk_14, 0.06f, 0.12f, 200);
            }
        }
    }
}

void func_80BDC830(EnZowStruct* ptr, GlobalContext* globalCtx) {
    s16 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    u8 flag = false;

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 == 1) {
            if (!flag) {
                gDPPipeSync(POLY_XLU_DISP++);
                gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_00D220);
                gDPSetEnvColor(POLY_XLU_DISP++, 155, 155, 155, 0);
                if (1) {}
                flag = true;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, ptr->unk_0F);

            Matrix_InsertTranslation(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, MTXMODE_NEW);
            Matrix_Scale(ptr->unk_04, 1.0f, ptr->unk_04, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_00D288);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BDC9DC(EnZowStruct* ptr, GlobalContext* globalCtx) {
    s16 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    u8 flag = false;

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 == 3) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_0029F0);
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 150, 150, 150, 0);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
                if (1) {}
                flag = true;
            }

            Matrix_InsertTranslation(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_002A50);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BDCB84(EnZowStruct* ptr, GlobalContext* globalCtx) {
    s16 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    u8 flag = false;

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 15; i++, ptr++) {
        if (ptr->unk_00 == 2) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_002BA0);
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 200, 0);
                if (1) {}
                flag = true;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 180, 180, 180, ptr->unk_0F);

            Matrix_InsertTranslation(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_zo_DL_002C10);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BDCD38(EnZow* this, EnZowStruct* ptr, f32 arg2, f32 arg3, u8 arg4) {
    static Vec3f D_80BDDD34 = { 0.0f, 0.0f, 0.0f };

    D_80BDDD34.x = this->actor.world.pos.x;
    D_80BDDD34.y = this->actor.world.pos.y + this->actor.depthInWater;
    D_80BDDD34.z = this->actor.world.pos.z;
    func_80BDC270(ptr, &D_80BDDD34, arg2, arg3, arg4);
}

void func_80BDCDA8(EnZow* this, EnZowStruct* ptr) {
    Vec3f sp84;
    Vec3f sp78;
    f32 temp_f20;
    f32 temp_f22;
    s32 i;

    for (i = 0; i < 10; i++) {
        temp_f20 = (Rand_ZeroOne() * 1.5f) + 0.5f;
        temp_f22 = Rand_ZeroOne() * 6.28f;

        sp78.y = (Rand_ZeroOne() * 3.0f) + 3.0f;
        sp78.x = __sinf(temp_f22) * temp_f20;
        sp78.z = __cosf(temp_f22) * temp_f20;

        sp84 = this->actor.world.pos;
        sp84.x += sp78.x * 6.0f;
        sp84.z += sp78.z * 6.0f;
        sp84.y += this->actor.depthInWater;

        func_80BDC3C0(ptr, &sp84, &sp78, 0.08f);
    }
}

void EnZow_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZow* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80BDD79C;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZoraSkel, &gZoraIdleAnim, this->jointTable, this->morphTable, 20);
    Animation_PlayOnce(&this->skelAnime, &gZoraSurfacingAnim);
    this->unk_2C8 = 1;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.shape.rot.z = 0;
    this->unk_2CA = 0;
    this->unk_2CC = 0;
    this->unk_2CE = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.textId = 0;
    this->actor.world.rot.z = this->actor.shape.rot.z;
    this->actor.flags &= ~ACTOR_FLAG_1;
}

void EnZow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZow* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

AnimationHeader* sAnimations[] = { &object_zo_Anim_004168, &gZoraSurfacingAnim, &gZoraSurfacingAnim };

void func_80BDD04C(EnZow* this, s16 arg1, u8 arg2) {
    if ((arg1 >= 0) && (arg1 < 3)) {
        if (arg1 < 2) {
            Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[arg1]),
                             arg2, -5.0f);
        } else {
            Animation_Change(&this->skelAnime, sAnimations[arg1], -1.0f, Animation_GetLastFrame(sAnimations[arg1]),
                             0.0f, arg2, 0.0f);
        }
        this->unk_2C8 = arg1;
    }
}

s32 func_80BDD154(EnZow* this, GlobalContext* globalCtx) {
    if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && Actor_IsFacingPlayer(&this->actor, 0x3000) &&
        (this->actor.xzDistToPlayer < 170.0f) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
        return true;
    }
    return false;
}

void func_80BDD1E0(EnZow* this, GlobalContext* globalCtx) {
    u16 phi_a1;

    if (ENZOW_GET_F(&this->actor) == ENZOW_F_1) {
        if (gSaveContext.save.weekEventReg[55] & 0x80) {
            if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
                if (gSaveContext.save.weekEventReg[78] & 4) {
                    phi_a1 = 0x12FD;
                } else {
                    phi_a1 = 0x12FA;
                    gSaveContext.save.weekEventReg[78] |= 4;
                }
            } else if (gSaveContext.save.weekEventReg[78] & 0x10) {
                phi_a1 = 0x1301;
            } else {
                gSaveContext.save.weekEventReg[78] |= 0x10;
                phi_a1 = 0x12FF;
            }
        } else if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            if (gSaveContext.save.weekEventReg[78] & 8) {
                phi_a1 = 0x12F8;
            } else {
                phi_a1 = 0x12F3;
                gSaveContext.save.weekEventReg[78] |= 8;
            }
        } else if (gSaveContext.save.weekEventReg[78] & 0x10) {
            phi_a1 = 0x1301;
        } else {
            gSaveContext.save.weekEventReg[78] |= 0x10;
            phi_a1 = 0x12FF;
        }
    } else if (gSaveContext.save.weekEventReg[55] & 0x80) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            phi_a1 = 0x12EC;
        } else {
            phi_a1 = 0x12F1;
        }
    } else if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[78] & 2) {
            phi_a1 = 0x12EB;
        } else {
            phi_a1 = 0x12E8;
            gSaveContext.save.weekEventReg[78] |= 2;
        }
    } else {
        phi_a1 = 0x12EF;
    }
    Message_StartTextbox(globalCtx, phi_a1, &this->actor);
}

void func_80BDD350(EnZow* this, GlobalContext* globalCtx) {
    if (this->unk_2CA & 2) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_WATER);
        func_80BDCDA8(this, this->unk_2D0);
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->skelAnime.playSpeed = 0.0f;
        this->actor.velocity.y = -4.0f;
    }

    if (this->actor.depthInWater > 120.0f) {
        Math_ApproachF(&this->actor.velocity.y, 0.0f, 0.4f, 0.6f);
        if (this->actor.velocity.y > -0.1f) {
            this->actor.velocity.y = 0.0f;
            this->actionFunc = func_80BDD79C;
        }
    }

    if ((this->actor.bgCheckFlags & 1) || (this->actor.depthInWater > 180.0f)) {
        this->actor.velocity.y = 0.0f;
        this->actionFunc = func_80BDD79C;
    }

    if (this->skelAnime.playSpeed <= 0.0f) {
        if (this->unk_2CE >= 6) {
            this->unk_2CE -= 5;
            return;
        } else {
            this->unk_2CE = 0;
        }
    }
}

void func_80BDD490(EnZow* this, GlobalContext* globalCtx) {
    this->actor.velocity.y = 0.0f;
    if (this->actor.xzDistToPlayer > 440.0f) {
        this->actionFunc = func_80BDD350;
        func_80BDD04C(this, 2, 2);
    } else if (this->unk_2CA & 2) {
        func_80BDD04C(this, 0, 0);
    }

    if ((globalCtx->gameplayFrames & 7) == 0) {
        func_80BDCD38(this, this->unk_2D0, 0.2f, 1.0f, 200);
    }

    if (this->unk_2CE < 245) {
        this->unk_2CE += 10;
    } else {
        this->unk_2CE = 255;
    }
}

void func_80BDD570(EnZow* this, GlobalContext* globalCtx) {
    func_80BDD490(this, globalCtx);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x12E8:
                    case 0x12E9:
                    case 0x12EC:
                    case 0x12ED:
                    case 0x12EF:
                    case 0x12F1:
                    case 0x12F3:
                    case 0x12F4:
                    case 0x12F5:
                    case 0x12F6:
                    case 0x12F8:
                    case 0x12FA:
                    case 0x12FB:
                    case 0x12FD:
                    case 0x12FF:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    default:
                        func_801477B4(globalCtx);
                        break;
                }
            }
            break;

        case 2:
            this->actionFunc = func_80BDD634;
            break;
    }
}

void func_80BDD634(EnZow* this, GlobalContext* globalCtx) {
    func_80BDD490(this, globalCtx);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BDD570;
        func_80BDD1E0(this, globalCtx);
    } else if (func_80BDD154(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 180.0f);
    }
}

void func_80BDD6BC(EnZow* this, GlobalContext* globalCtx) {
    if (this->unk_2CE < 245) {
        this->unk_2CE += 10;
    } else {
        this->unk_2CE = 255;
    }

    if (this->actor.depthInWater < 54.0f) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OUT_OF_WATER);
        func_80BDCDA8(this, this->unk_2D0);
        func_80BDD04C(this, 1, 2);
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.velocity.y = 0.0f;
        this->actionFunc = func_80BDD634;
    } else if (this->actor.depthInWater < 80.0f) {
        Math_ApproachF(&this->actor.velocity.y, 2.0f, 0.4f, 0.6f);
    }
}

void func_80BDD79C(EnZow* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 400.0f) {
        this->actor.velocity.y = 4.0f;
        this->actionFunc = func_80BDD6BC;
    }

    if (this->unk_2CE >= 6) {
        this->unk_2CE -= 5;
    } else {
        this->unk_2CE = 0;
    }

    if (this->actor.depthInWater > 180.0f) {
        this->actor.world.pos.y = this->actor.world.pos.y + -180.0f + this->actor.depthInWater;
    }
}

void EnZow_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZow* this = THIS;
    Vec3f sp34;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 15.0f, 30.0f, 5);

    if (this->unk_2CE != 0) {
        this->unk_2CA &= ~2;
        if (SkelAnime_Update(&this->skelAnime)) {
            this->unk_2CA |= 2;
        }
    } else {
        this->unk_2CA |= 2;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    this->actionFunc(this, globalCtx);

    if (this->unk_2CE != 0) {
        if ((globalCtx->state.frames & 8) != 0) {
            sp34 = this->actor.world.pos;
            sp34.y += ((Rand_ZeroOne() - 0.5f) * 10.0f) + 18.0f;
            sp34.x += (Rand_ZeroOne() - 0.5f) * 28.0f;
            sp34.z += (Rand_ZeroOne() - 0.5f) * 28.0f;
            func_80BDC2D8(this, this->unk_2D0, &sp34);
        }

        if (DECR(this->unk_2C6) == 0) {
            this->unk_2C6 = Rand_S16Offset(60, 60);
        }

        this->unk_2C4 = this->unk_2C6;
        if (this->unk_2C4 >= 3) {
            this->unk_2C4 = 0;
        }
    }

    this->actor.shape.shadowAlpha = this->unk_2CE;
    func_80BDC50C(this->unk_2D0);
    func_80BDC5C8(this, this->unk_2D0);
    func_80BDC6F8(this, this->unk_2D0);
}

Gfx* func_80BDDA7C(GraphicsContext* gfxCtx) {
    Gfx* gfx = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gSPEndDisplayList(gfx);

    return gfx;
}

Vec3f D_80BDDD4C = { 400.0f, 0.0f, 0.0f };

void func_80BDDAA0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&D_80BDDD4C, &thisx->focus.pos);
    }
}

void func_80BDDAE0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    func_80BDDAA0(globalCtx, limbIndex, dList, rot, thisx);
}

void EnZow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    TexturePtr sp54[] = {
        gZoraEyeOpenTex,
        gZoraEyeHalfTex,
        gZoraEyeClosedTex,
    };
    EnZow* this = THIS;

    Matrix_StatePush();

    func_80BDC830(this->unk_2D0, globalCtx);
    func_80BDC9DC(this->unk_2D0, globalCtx);
    func_80BDCB84(this->unk_2D0, globalCtx);

    Matrix_StatePop();

    if (this->unk_2CE != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (this->unk_2CE >= 255) {
            func_8012C28C(globalCtx->state.gfxCtx);

            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sp54[this->unk_2C4]));
            gSPSegment(POLY_OPA_DISP++, 0x0C, func_80BDDA7C(globalCtx->state.gfxCtx));

            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, NULL, func_80BDDAA0, &this->actor);
        } else {
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sp54[this->unk_2C4]));

            func_800BDAA0(globalCtx, &this->skelAnime, NULL, func_80BDDAE0, &this->actor, this->unk_2CE);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
