/*
 * File: z_obj_kendo_kanban.c
 * Overlay: ovl_Obj_Kendo_Kanban
 * Description: Swordsman's School - Cuttable Board
 */

#include "z_obj_kendo_kanban.h"
#include "objects/object_dora/object_dora.h"

#define FLAGS 0x00000000

#define THIS ((ObjKendoKanban*)thisx)

void ObjKendoKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B65880(ObjKendoKanban* this);
void func_80B65894(ObjKendoKanban* this, GlobalContext* globalCtx);
void func_80B658A4(ObjKendoKanban* this, GlobalContext* globalCtx);
void func_80B65CE0(ObjKendoKanban* this, GlobalContext* globalCtx);
void func_80B65D68(ObjKendoKanban* this, GlobalContext* globalCtx);
void func_80B65DA8(ObjKendoKanban* this, GlobalContext* globalCtx);
s32 func_80B6618C(ObjKendoKanban* this, GlobalContext* globalCtx);

const ActorInit Obj_Kendo_Kanban_InitVars = {
    ACTOR_OBJ_KENDO_KANBAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjKendoKanban),
    (ActorFunc)ObjKendoKanban_Init,
    (ActorFunc)ObjKendoKanban_Destroy,
    (ActorFunc)ObjKendoKanban_Update,
    (ActorFunc)ObjKendoKanban_Draw,
};

Vec3f D_80B66660 = { -1.5f, 10.0f, 0.5f };
Vec3f D_80B6666C = { 1.5f, 10.0f, 0.5f };
Vec3f D_80B66678 = { 0.0f, 4.0f, -1.0f };
Vec3f D_80B66684 = { 1.0f, 7.0f, 4.0f };
Vec3f D_80B66690 = { -150.0f, 425.0f, 40.0f };
Vec3f D_80B6669C = { 150.0f, 425.0f, 40.0f };
Vec3f D_80B666A8 = { 0.0f, 140.0f, 40.0f };
Vec3f D_80B666B4 = { 0.0f, 565.0f, 40.0f };

Gfx* D_80B666C0 = object_dora_DL_002080;
Gfx* D_80B666C4 = object_dora_DL_002180;
Gfx* D_80B666C8 = object_dora_DL_002380;
Gfx* D_80B666CC = object_dora_DL_002280;

Vec3f D_80B666D0 = { -300.0f, 850.0f, 40.0f };
Vec3f D_80B666DC = { 10.0f, 850.0f, 40.0f };
Vec3f D_80B666E8 = { 300.0f, 850.0f, 40.0f };
Vec3f D_80B666F4 = { -300.0f, 310.0f, 40.0f };
Vec3f D_80B66700 = { 0.0f, 280.0f, 40.0f };
Vec3f D_80B6670C = { 300.0f, 250.0f, 40.0f };
Vec3f D_80B66718 = { -300.0f, 10.0f, 40.0f };
Vec3f D_80B66724 = { 0.0f, 10.0f, 40.0f };
Vec3f D_80B66730 = { 300.0f, 10.0f, 40.0f };

static ColliderTrisElementInit sTrisElementsInit[] = {
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -300.0f, 850.0f, 40.0f }, { -300.0f, 10.0f, 40.0f }, { 300.0f, 850.0f, 40.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 300.0f, 850.0f, 40.0f }, { 300.0f, 10.0f, 40.0f }, { -300.0f, 10.0f, 40.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 33, 80, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

Vec3f D_80B6681C = { 0.0f, 0.0f, 0.0f };
Vec3f D_80B66828 = { 1.0f, 0.0f, 0.0f };

void ObjKendoKanban_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    ObjKendoKanban* this = THIS;
    Vec3f sp70[3];
    s32 i;
    s32 j;

    Actor_SetScale(&this->actor, 0.1f);

    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTrisElements);

    Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                          &this->actor.shape.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->colliderTrisElements); i++) {
        for (j = 0; j < ARRAY_COUNT(sp70); j++) {
            Matrix_MultiplyVector3fByState(&sTrisElementsInit[i].dim.vtx[j], &sp70[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &sp70[0], &sp70[1], &sp70[2]);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->unk_30C = OBJKENDOKANBAN_GET_F(&this->actor);
    this->actor.gravity = -2.0f;
    this->unk_2CC = D_80B6681C;
    this->unk_2D8 = D_80B6681C;
    this->unk_2E4 = D_80B6681C;
    this->unk_2F0 = D_80B66828;
    this->unk_302 = 0;
    this->unk_304 = 0;
    this->unk_2FC = -1;
    this->unk_300 = 0;
    this->unk_308 = 0;

    for (i = 0; i < ARRAY_COUNT(this->unk_26C); i++) {
        this->unk_26C[i] = this->unk_29C[i] = D_80B6681C;
    }

    this->unk_30A = 0;
    if (this->unk_30C == OBJKENDOKANBAN_F_0) {
        func_80B65880(this);
    } else {
        func_80B658A4(this, globalCtx);
    }
}

void ObjKendoKanban_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjKendoKanban* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroyTris(globalCtx, &this->colliderTris);
}

void func_80B65880(ObjKendoKanban* this) {
    this->actionFunc = func_80B65894;
}

void func_80B65894(ObjKendoKanban* this, GlobalContext* globalCtx) {
}

void func_80B658A4(ObjKendoKanban* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_30C == OBJKENDOKANBAN_F_0) {
        if ((player->swordAnimation == 0) || (player->swordAnimation == 1) || (player->swordAnimation == 0x14)) {
            this->unk_30C = (OBJKENDOKANBAN_F_4 | OBJKENDOKANBAN_F_1);
            this->unk_304 = 0x71C;
            this->actor.velocity = D_80B6666C;
            this->unk_2CC = D_80B6669C;

            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_KENDO_KANBAN,
                               this->actor.home.pos.x - 5.0f, this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                               0xA);

            this->unk_29C[0] = D_80B666DC;
            this->unk_29C[1] = D_80B666E8;
            this->unk_29C[2] = D_80B66730;
            this->unk_29C[3] = D_80B66724;
        } else {
            this->unk_30C = (OBJKENDOKANBAN_F_8 | OBJKENDOKANBAN_F_4);
            this->unk_304 = -0x71C;
            this->actor.velocity = D_80B66678;
            this->unk_2CC = D_80B666A8;

            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_KENDO_KANBAN,
                               this->actor.home.pos.x, this->actor.home.pos.y + 5.0f, this->actor.home.pos.z, 0, 0, 0,
                               3);

            this->unk_29C[0] = D_80B666F4;
            this->unk_29C[1] = D_80B6670C;
            this->unk_29C[2] = D_80B66730;
            this->unk_29C[3] = D_80B66718;
        }
    } else if (this->unk_30C == (OBJKENDOKANBAN_F_8 | OBJKENDOKANBAN_F_2)) {
        this->unk_304 = 0x71C;
        this->actor.velocity = D_80B66660;
        this->unk_2CC = D_80B66690;

        this->unk_29C[0] = D_80B666D0;
        this->unk_29C[1] = D_80B666DC;
        this->unk_29C[2] = D_80B66724;
        this->unk_29C[3] = D_80B66718;
    } else if (this->unk_30C == (OBJKENDOKANBAN_F_2 | OBJKENDOKANBAN_F_1)) {
        this->unk_304 = 0x71C;
        this->actor.velocity = D_80B66684;
        this->unk_2CC = D_80B666B4;

        this->unk_29C[0] = D_80B666D0;
        this->unk_29C[1] = D_80B666E8;
        this->unk_29C[2] = D_80B6670C;
        this->unk_29C[3] = D_80B666F4;
    }

    this->unk_30A = 0;
    this->actionFunc = func_80B65CE0;
}

void func_80B65CE0(ObjKendoKanban* this, GlobalContext* globalCtx) {
    this->actor.velocity.y += this->actor.gravity;
    Actor_UpdatePos(&this->actor);
    this->unk_302 += this->unk_304;
    func_80B65DA8(this, globalCtx);
    if (this->actor.world.pos.y < -200.0f) {
        this->actor.world.pos.y = -200.0f;
    }
}

void func_80B65D54(ObjKendoKanban* this) {
    this->actionFunc = func_80B65D68;
}

void func_80B65D68(ObjKendoKanban* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (func_80B6618C(this, globalCtx) == 1) {
        player->unk_AC0 = 700.0f;
    }
}

void func_80B65DA8(ObjKendoKanban* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    s32 pad[2];
    Vec3f sp48;
    s32 pad2;
    s32 index = 0;
    s32 i;
    f32 sp38;

    sp5C = this->unk_26C[0];
    sp48 = this->actor.world.pos;

    sp48.x -= this->unk_2D8.x;
    sp48.y -= this->unk_2D8.y;
    sp48.z -= this->unk_2D8.z;

    sp38 = (this->unk_2F0.x * sp48.z) + (this->unk_2F0.z * -sp48.x);

    if (sp38 < 0.0f) {
        this->unk_304 += 0x64;
    } else {
        this->unk_304 -= 0x64;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_26C); i++) {
        if (this->unk_26C[i].y < sp5C.y) {
            sp5C = this->unk_26C[i];
            index = i;
        }
    }

    if (index != this->unk_2FC) {
        this->unk_300 = 1;
        this->unk_2FC = index;
        this->unk_2E4 = this->unk_29C[index];

        Matrix_StatePush();
        Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                              &this->actor.shape.rot);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_MultiplyVector3fByState(&this->unk_2E4, &this->actor.world.pos);
        this->actor.world.pos = sp5C;
        this->actor.prevPos = this->actor.world.pos;
        Matrix_StatePop();
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->actor.bgCheckFlags & 1) {
        this->actor.velocity.x *= 0.8f;
        this->actor.velocity.z *= 0.8f;
    }

    if (this->unk_300 == 1) {
        if (this->unk_308 >= 7) {
            s16 temp_v0_3 = this->unk_302 & 0x3FFF;

            if (temp_v0_3 >= 0x2000) {
                temp_v0_3 -= 0x4000;
            }
            this->unk_302 -= temp_v0_3;
            this->unk_304 = 0;
            func_80B65D54(this);
            return;
        }

        if (this->actor.bgCheckFlags & 2) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WOODPLATE_BOUND);
            this->unk_300 = 0;
            this->actor.velocity.y *= 0.5f;
        } else if (this->actor.bgCheckFlags & 1) {
            this->unk_308++;
            this->unk_300 = 0;
            this->actor.velocity.x *= 0.3f;
            this->actor.velocity.z *= 0.3f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WOODPLATE_BOUND);

            if (sp38 > 0.0f) {
                if (this->unk_304 > 0) {
                    this->unk_304 *= 1.2f;
                } else {
                    this->unk_304 *= -0.6f;
                }
            } else if (this->unk_304 < 0) {
                this->unk_304 *= 1.2f;
            } else {
                this->unk_304 *= -0.6f;
            }
        }
    }
}

s32 func_80B6618C(ObjKendoKanban* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 phi_v0;
    s32 phi_v1 = 0;
    s32 i;
    f32 x;
    f32 z;
    f32 x2;
    f32 z2;

    for (i = 0; i < ARRAY_COUNT(this->unk_26C); i++) {
        if (i != 3) {
            phi_v0 = i + 1;
        } else {
            phi_v0 = 0;
        }

        z = this->unk_26C[i].z - player->actor.world.pos.z;
        x = this->unk_26C[i].x - player->actor.world.pos.x;

        z2 = (this->unk_26C[phi_v0].z - player->actor.world.pos.z);
        x2 = (this->unk_26C[phi_v0].x - player->actor.world.pos.x);

        if ((x * z2) < (z * x2)) {
            if (phi_v1 == 0) {
                phi_v1 = 1;
            } else if (phi_v1 != 1) {
                return false;
            }
        } else if (phi_v1 == 0) {
            phi_v1 = -1;
        } else if (phi_v1 != -1) {
            return false;
        }
    }
    return true;
}

void func_80B66304(ObjKendoKanban* this, GlobalContext* globalCtx) {
    if ((this->actionFunc != func_80B65CE0) && (this->actionFunc != func_80B65D68)) {
        if (this->colliderTris.base.acFlags & AC_HIT) {
            this->colliderTris.base.acFlags &= ~AC_HIT;
            func_80B658A4(this, globalCtx);
        }

        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
        this->colliderCylinder.dim.pos.z -= (s16)(20.0f * Math_CosS(this->actor.shape.rot.y));
        this->colliderCylinder.dim.pos.x -= (s16)(20.0f * Math_SinS(this->actor.shape.rot.y));

        if (this->actionFunc == func_80B65894) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
        }

        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }
}

void ObjKendoKanban_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjKendoKanban* this = THIS;

    this->actionFunc(this, globalCtx);

    func_80B66304(this, globalCtx);
}

#ifdef NON_MATCHING
void ObjKendoKanban_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjKendoKanban* this = THIS;
    s32 i;
    Gfx* poly;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_30C == OBJKENDOKANBAN_F_0) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_dora_DL_000180);
    } else {
        Matrix_InsertRotationAroundUnitVector_s(this->unk_302, &this->unk_2F0, MTXMODE_APPLY);
        Matrix_InsertTranslation(-this->unk_2E4.x, -this->unk_2E4.y, -this->unk_2E4.z, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (this->unk_30C & OBJKENDOKANBAN_F_1) {
            gSPDisplayList(POLY_OPA_DISP++, D_80B666C0);
        }

        if (this->unk_30C & OBJKENDOKANBAN_F_2) {
            gSPDisplayList(POLY_OPA_DISP++, D_80B666C4);
        }

        if (this->unk_30C & OBJKENDOKANBAN_F_4) {
            gSPDisplayList(POLY_OPA_DISP++, D_80B666C8);
        }

        if (this->unk_30C & OBJKENDOKANBAN_F_8) {
            gSPDisplayList(POLY_OPA_DISP++, D_80B666CC);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_26C); i++) {
        Matrix_MultiplyVector3fByState(&this->unk_29C[i], &this->unk_26C[i]);
    }

    Matrix_MultiplyVector3fByState(&this->unk_2CC, &this->unk_2D8);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/ObjKendoKanban_Draw.s")
#endif
