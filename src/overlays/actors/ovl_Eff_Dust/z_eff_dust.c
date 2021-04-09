/**
 * File z_eff_dust.c
 * Overlay: ovl_Eff_Dust
 * Description: Dust effects
 */

#include "z_eff_dust.h"

#define FLAGS 0x00000030

#define THIS ((EffDust*)thisx)

void EffDust_Init(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Update(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Draw(Actor* thisx, GlobalContext* globalCtx);


void func_80918D64(EffDust* this, GlobalContext* globalCtx);
void func_80918FE4(EffDust* this, GlobalContext* globalCtx);
void func_80919230(EffDust* this, GlobalContext* globalCtx);

void func_80919768(Actor* thisx, GlobalContext* globalCtx);
void func_809199FC(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Eff_Dust_InitVars = {
    ACTOR_EFF_DUST,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EffDust),
    (ActorFunc)EffDust_Init,
    (ActorFunc)EffDust_Destroy,
    (ActorFunc)EffDust_Update,
    (ActorFunc)EffDust_Draw
};

void func_80918B40(EffDust* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->distanceTraveled); i++) {
        this->initialPositions[i].z = 0.0f;
        this->initialPositions[i].y = 0.0f;
        this->initialPositions[i].x = 0.0f;

        this->distanceTraveled[i] = 1.0f;
    }
    this->index = 0;
}

/*
void EffDust_Init(Actor* thisx, GlobalContext* globalCtx) {
    EffDust* this = THIS;
    u32 sp18 = this->actor.params;

    func_80918B40(this);
    switch (sp18) {
    case 0:
        this->actionFunc = func_80918D64;
        this->actor.draw = func_80919768;
        this->dx = 1.0f;
        this->dy = 1.0f;
        this->dz = 1.0f;
        this->scalingFactor = 0.2f;
        break;
    case 1:
        this->actionFunc = func_80918FE4;
        this->actor.draw = func_80919768;
        this->dy = 1.0f;
        this->dx = 0.8f;
        this->dz = 0.8f;
        this->scalingFactor = 0.5f;
        break;
    case 2:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 15.0f;
        break;
    case 4:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 10.0f;
        break;
    case 5:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 20.0f;
        break;
    default:
        StartHeap_Free(this);
        break;
    }
    this->life = 10;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/EffDust_Init.asm")

void EffDust_Destroy(Actor *thisx, GlobalContext *globalCtx) {
}

void func_80918D64(EffDust *this, GlobalContext *globalCtx) {
    s16 theta;
    s16 fi;
    s32 i;
    s32 j;
    f32* distanceTraveled = this->distanceTraveled;

    for (i = 0; i < ARRAY_COUNT(this->distanceTraveled); i++) {
        if ((*distanceTraveled) < 1.0f) {
            *distanceTraveled += 0.05f;
        }
        distanceTraveled++;
    }

    if (this->actor.home.rot.z != 0) {
        for (j = 0; j < 3; j++) {
            i = this->index & 0x3F;
            if (this->distanceTraveled[i] >= 1.0f) {
                // Spherical coordinate system.
                fi = randPlusMinusPoint5Scaled(0x10000);
                theta = Rand_ZeroFloat(0x1000);
                this->initialPositions[i].x = -(f32) this->actor.home.rot.z * Math_CosS(fi) * Math_CosS(theta);
                this->initialPositions[i].y = -(f32) this->actor.home.rot.z * Math_SinS(fi) * Math_CosS(theta);
                this->initialPositions[i].z = -(f32) this->actor.home.rot.z * Math_SinS(theta);
                this->distanceTraveled[i] = 0.0f;
                this->index++;
            }
        }
    }
}

void func_80918FE4(EffDust *this, GlobalContext *globalCtx) {
    s16 theta;
    s16 fi;
    f32* distanceTraveled = this->distanceTraveled;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(this->distanceTraveled); i++) {
        if ((*distanceTraveled) < 1.0f) {
            *distanceTraveled += 0.03f;
        }
        distanceTraveled++;
    }

    for (j = 0; j < 2; j++){
        i = this->index & 0x3F;
        if (this->distanceTraveled[i] >= 1.0f) {
            // Spherical coordinate system.
            fi = randPlusMinusPoint5Scaled(0x10000);
            theta = Rand_ZeroFloat(0x2000);
            this->initialPositions[i].x = 400.0f * Math_CosS(fi) * Math_CosS(theta);
            this->initialPositions[i].y = 400.0f * Math_SinS(theta);
            this->initialPositions[i].z = 400.0f * Math_SinS(fi) * Math_CosS(theta);
            this->distanceTraveled[i] = 0.0f;
            this->index++;
        }
    }
}

void func_80919230(EffDust *this, GlobalContext *globalCtx) {
    s16 theta;
    ActorPlayer* player = PLAYER;
    Actor* parent = this->actor.parent;
    f32 *distanceTraveled = this->distanceTraveled;
    s32 i;
    s32 j;

    if (parent == NULL || parent->update == NULL || !(player->stateFlags1 & 0x1000)) {
        if (this->life != 0) {
            this->life--;
        } else {
            Actor_MarkForDeath(&this->actor);
        }

        for (i = 0; i < 64; i++) {
            if ((*distanceTraveled) < 1.0f) {
                *distanceTraveled += 0.2f;
            }
            distanceTraveled++;
        }

        return;
    }

    for (i = 0; i < 64; i++) {
        if ((*distanceTraveled) < 1.0f) {
            *distanceTraveled += 0.1f;
        }
        distanceTraveled++;
    }

    this->actor.world.pos = parent->world.pos;

    for (j = 0; j < 3; j++) {
        i = this->index & 0x3F;

        if (this->distanceTraveled[i] >= 1.0f) {
            theta = randPlusMinusPoint5Scaled(0x10000);
            switch (this->actor.params) {
                case 2:
                    this->initialPositions[i].x = (Rand_ZeroOne() * 4500.0f) + 700.0f;
                    if (this->initialPositions[i].x > 3000.0f) {
                        this->initialPositions[i].y = (3000.0f * Rand_ZeroOne()) * Math_SinS(theta);
                        this->initialPositions[i].z = (3000.0f * Rand_ZeroOne()) * Math_CosS(theta);
                    } else {
                        this->initialPositions[i].y = 3000.0f * Math_SinS(theta);
                        this->initialPositions[i].z = 3000.0f * Math_CosS(theta);
                    }
                    break;

                case 3:
                    this->initialPositions[i].x = (Rand_ZeroOne() * 2500.0f) + 700.0f;
                    if (this->initialPositions[i].x > 2000.0f) {
                        this->initialPositions[i].y = (2000.0f * Rand_ZeroOne()) * Math_SinS(theta);
                        this->initialPositions[i].z = (2000.0f * Rand_ZeroOne()) * Math_CosS(theta);
                    } else {
                        this->initialPositions[i].y = 2000.0f * Math_SinS(theta);
                        this->initialPositions[i].z = 2000.0f * Math_CosS(theta);
                    }
                    break;

                case 4:
                    this->initialPositions[i].x = (Rand_ZeroOne() * 8500.0f) + 1700.0f;
                    if (this->initialPositions[i].x > 5000.0f) {
                        this->initialPositions[i].y = (4000.0f * Rand_ZeroOne()) * Math_SinS(theta);
                        this->initialPositions[i].z = (4000.0f * Rand_ZeroOne()) * Math_CosS(theta);
                    } else {
                        this->initialPositions[i].y = 4000.0f * Math_SinS(theta);
                        this->initialPositions[i].z = 4000.0f * Math_CosS(theta);
                    }
                    break;
            }

            this->distanceTraveled[i] = 0.0f;
            this->index++;
        }
    }
}

void EffDust_Update(Actor* thisx, GlobalContext* globalCtx) {
    EffDust* this = THIS;

    this->actionFunc(this, globalCtx);
}


Gfx D_80919DB0[] = {
    gsSPEndDisplayList(),
};

extern Gfx D_04054A90[];

#ifdef NON_MATCHING
void func_80919768(Actor *thisx, GlobalContext *globalCtx2) {
    //EffDust* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    GraphicsContext *gfxCtx;
    Vec3f *initialPositions;
    f32 *distanceTraveled;
    //Vec3f *new_var;
    Camera* cam = ACTIVE_CAM;
    f32 aux;
    s32 i;
    //f32 aux;
    s16 sp92;
    Vec3f sp84;
    //MtxF *temp_s0;

    gfxCtx = globalCtx->state.gfxCtx;

    sp84 = cam->eye;
    sp92 = Math_Vec3f_Yaw(&sp84, &THIS->actor.world.pos); // & 0xFFFF;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(gfxCtx);

    gDPPipeSync(POLY_XLU_DISP++);

    initialPositions = THIS->initialPositions;
    distanceTraveled = THIS->distanceTraveled;

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 255, 0);

    gSPSegment(POLY_XLU_DISP++, 0x08, D_80919DB0);

    for (i = 0; i < 64; i++) {
        if (*distanceTraveled < 1.0f) {
            //temp_s0 = &globalCtx->mf_187FC;
            aux = 1.0f - SQ(*distanceTraveled);
            SysMatrix_InsertTranslation(THIS->actor.world.pos.x, THIS->actor.world.pos.y, THIS->actor.world.pos.z, MTXMODE_NEW);
            Matrix_RotateY(sp92, MTXMODE_APPLY);

            //new_var = initialPositions;
            SysMatrix_InsertTranslation(initialPositions->x * ((THIS->dx * aux) + (1.0f - THIS->dx)), 
                                        initialPositions->y * ((THIS->dy * aux) + (1.0f - THIS->dy)), 
                                        initialPositions->z * ((THIS->dz * aux) + (1.0f - THIS->dz)), 
                                        MTXMODE_APPLY);
            Matrix_Scale(THIS->scalingFactor, THIS->scalingFactor, THIS->scalingFactor, MTXMODE_APPLY);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPClearGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);

            gSPDisplayList(POLY_XLU_DISP++, D_04054A90);

            gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);
        }
        initialPositions++;
        distanceTraveled++;
    }

    CLOSE_DISPS(gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_80919768.asm")
#endif

void func_809199FC(Actor *thisx, GlobalContext *globalCtx2) {
    EffDust* this = THIS;
    GlobalContext *globalCtx = globalCtx2;
    GraphicsContext *temp_s1;
    f32 temp_f20;
    f32 *distanceTraveled;
    Vec3f *initialPositions;
    ActorPlayer *player;
    s32 i;

    temp_s1 = globalCtx->state.gfxCtx;

    player = PLAYER;

    OPEN_DISPS(temp_s1);

    func_8012C28C(temp_s1);

    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);

    if (player->unkB08 >= 0.85f) {
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    } else {
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 255, 0);
    }

    gSPSegment(POLY_XLU_DISP++, 0x08, D_80919DB0);

    initialPositions = this->initialPositions;
    distanceTraveled = this->distanceTraveled;

    for (i = 0; i < 0x40; i++) {
        if (*distanceTraveled < 1.0f) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, ((*distanceTraveled * 255.0f)));

            temp_f20 = 1.0f - SQ(*distanceTraveled);
            SysMatrix_InsertMatrix(&player->mf_CC4, 0);
            SysMatrix_InsertTranslation(initialPositions->x * ((this->dx * temp_f20) + (1.0f - this->dx)), 
                                        ((1.0f - *distanceTraveled) * initialPositions->y) + 320.0f, 
                                        ((1.0f - *distanceTraveled) * initialPositions->z) + -20.0f, 
                                        1);
            Matrix_Scale(*distanceTraveled * this->scalingFactor, 
                         *distanceTraveled * this->scalingFactor, 
                         *distanceTraveled * this->scalingFactor, 
                         (u8)1U);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(temp_s1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPClearGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);

            gSPDisplayList(POLY_XLU_DISP++, D_04054A90);

            gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);
        }
        initialPositions++;
        distanceTraveled++;
    }

    CLOSE_DISPS(temp_s1);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_809199FC.asm")

void EffDust_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EffDust* this = THIS;

    this->drawFunc(thisx, globalCtx);
}
