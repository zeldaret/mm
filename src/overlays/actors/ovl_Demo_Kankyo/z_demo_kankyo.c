#include "z_demo_kankyo.h"

#define FLAGS 0x00000030

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

void DemoKakyo_MoonSparklesActionFunc(DemoKankyo* this, GlobalContext* globalCtx);

extern Gfx D_0407AB58[];
extern Gfx D_06001000[]; // wait, 06 address? nvm this is the bubble
extern Gfx D_04023428[];

static u8 sLostWoodsSparklesMutex = 0; // make sure only one can exist at once
static s16 D_808D03C4 = 0;

const ActorInit Demo_Kankyo_InitVars = {
    ACTOR_DEMO_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoKankyo),
    (ActorFunc)DemoKankyo_Init,
    (ActorFunc)DemoKankyo_Destroy,
    (ActorFunc)DemoKankyo_Update,
    (ActorFunc)DemoKankyo_Draw,
};

// object E is bubble, which exists in giants chamber
static s32 sObjectBubbleIndex = 0x1000E;

void DemoKankyo_SetupAction(DemoKankyo* this, DemoKankyoActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DemoKakyo_LostWoodsSparkleActionFunc(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    f32 static130;
    f32 diffX;
    f32 distATanX; // not Vec3f stack order is wrong
    f32 distATanY;
    f32 distATanZ;
    f32 distance;
    f32 spBC; // vec3f?
    f32 spB8;
    f32 spB4;
    f32 diffY;
    f32 diffZ;
    f32 randResult;
    Player* player = PLAYER;

    if (globalCtx->roomCtx.unk7A[1] != 0) {
        if (globalCtx->envCtx.unk_F2[3] != 0) {
            globalCtx->envCtx.unk_F2[3]--;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (globalCtx->envCtx.unk_F2[3] < DEMOKANKYO_PARTICLE_COUNT) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
    //for (i = 0; i < 2; i++) { // testing
        static130 = 130.0f;
        
        diffX = globalCtx->view.at.x - globalCtx->view.eye.x;
        diffY = globalCtx->view.at.y - globalCtx->view.eye.y;
        diffZ = globalCtx->view.at.z - globalCtx->view.eye.z;
        distance = sqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
        distATanX = diffX / distance;
        distATanY = diffY / distance;
        distATanZ = diffZ / distance;

        switch (this->particles[i].state) {
            case 0: // init, changes to state 1 at the end
                this->particles[i].pos.x = globalCtx->view.eye.x + (distATanX * 80.0f);
                this->particles[i].pos.y = globalCtx->view.eye.y + (distATanY * 80.0f);
                this->particles[i].pos.z = globalCtx->view.eye.z + (distATanZ * 80.0f);
    
                this->particles[i].vel.x = (Rand_ZeroOne() - 0.5f) * 160.0f;
                this->particles[i].vel.y = 30.0f; // starts random direction pointed upwards, velocity?
                this->particles[i].vel.z = (Rand_ZeroOne() - 0.5f) * 160.0f;
                this->particles[i].unk_38 = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].alpha = 0;
                this->particles[i].unk_3C = Rand_ZeroOne() * 65535; // random 0 to max of u16
                this->particles[i].unk_44 = 0.1f;

                // random angle?
                this->particles[i].unk_28.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.z = Rand_ZeroOne() * 360.0f;
                this->particles[i].pad50 = 0;
                this->particles[i].state += 1; // set to 1
                break;

            case 1:
            case 2: // think case 2 is the particles that gather together as a snake
                this->particles[i].unk_3C += 1;
                spBC = globalCtx->view.eye.x + (distATanX * 80.0f);
                spB8 = globalCtx->view.eye.y + (distATanY * 80.0f);
                spB4 = globalCtx->view.eye.z + (distATanZ * 80.0f);
                this->particles[i].velPrevious.x = this->particles[i].vel.x;
                this->particles[i].velPrevious.y = this->particles[i].vel.y;
                this->particles[i].velPrevious.z = this->particles[i].vel.z;
                if (this->particles[i].state == 1) {
                    if (i < 32) {
                        if (Rand_ZeroOne() < 0.5f) {
                            this->particles[i].unk_48 = (s16)(Rand_ZeroOne() * 200.0f) + 200;
                        } else {
                            this->particles[i].unk_48 = -200 - (s16)(Rand_ZeroOne() * 200.0f);
                        }
                        this->particles[i].unk_4A = (s16)(Rand_ZeroOne() * 50.0f) + 15;
                        this->particles[i].unk_4C = ((Rand_ZeroOne() * 10.0f) + 10.0f) * 0.01f;
                        randResult = Rand_ZeroOne();
                        if (randResult < 0.2f) {
                            D_808D03C4 = 1;
                        } else if (randResult < 0.2f) {
                            D_808D03C4 = 3;
                        } else if (randResult < 0.4f) {
                            D_808D03C4 = 7;
                        } else {
                            D_808D03C4 = 0xF;
                        }
                        if ((D_808D03C4 & i) == 0) {
                            this->particles[i].vel.y = 0.0f;
                        }
                        this->particles[i].state = 2;
                        this->particles[i].unk_38 = 0.0f;
                    }

                    Math_SmoothStepToF(&this->particles[i].unk_44, 0.1, 0.1f, 0.001f, 0.00001f);
                    Math_SmoothStepToF(&this->particles[i].speed, this->particles[i].unk_38, 0.5f, 0.2f, 0.02f);
                    this->particles[i].vel.x += __sinf(this->particles[i].unk_28.x) * this->particles[i].speed;
                    this->particles[i].vel.y += __sinf(this->particles[i].unk_28.y) * this->particles[i].speed;
                    this->particles[i].vel.z += __sinf(this->particles[i].unk_28.z) * this->particles[i].speed;

                    switch ((i >> 1) & 3) {
                        case 0:
                            this->particles[i].unk_28.x += 0.008f;
                            this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += 0.015f;
                            break;

                        case 1:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.005f * Rand_ZeroOne());
                            break;

                        case 2:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.4f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.004f * Rand_ZeroOne());
                            break;

                        case 3:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.08f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.05f * Rand_ZeroOne());
                            break;
                    }
                } else if (this->particles[i].state == 2) {
                    if ((D_808D03C4 & i) == 0) {
                        Math_SmoothStepToF(&this->particles[i].unk_44, 0.25f, 0.1f, 0.001f, 0.00001f);

                        Math_SmoothStepToF(&this->particles[i].pos.x, player->actor.world.pos.x, 0.5f, 1.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].pos.y, player->actor.world.pos.y + 50.0f, 0.5f, 1.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].pos.z, player->actor.world.pos.z, 0.5f, 1.0f, 0.2f);

                        Math_SmoothStepToF(&this->particles[i].vel.x,
                                           Math_SinS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A,
                                           0.5f, 2.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].vel.z,
                                           Math_CosS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A,
                                           0.5f, 2.0f, 0.2f);
                        this->particles[i].unk_3E += this->particles[i].unk_48;
                        this->particles[i].vel.y += __sinf(this->particles[i].unk_28.y);
                        this->particles[i].unk_28.x += 0.2f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += this->particles[i].unk_4C;
                        this->particles[i].unk_28.z += 0.1f * Rand_ZeroOne();

                        this->particles[i].vel.x = Math_SinS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A;
                        this->particles[i].vel.z = Math_CosS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A;
                    } else {
                        Math_SmoothStepToF(&this->particles[i].unk_44, 0.1, 0.1f, 0.001f, 0.00001f);
                        Math_SmoothStepToF(&this->particles[i].speed, 1.5f, 0.5f, 0.1f, 0.0002f);

                        this->particles[i].vel.x = this->particles[i - 1].velPrevious.x + (this->particles[i - 1].pos.x - this->particles[i].pos.x);
                        this->particles[i].vel.y = this->particles[i - 1].velPrevious.y + (this->particles[i - 1].pos.y - this->particles[i].pos.y);
                        this->particles[i].vel.z = this->particles[i - 1].velPrevious.z + (this->particles[i - 1].pos.z - this->particles[i].pos.z);
                    }
                }

                if ((this->particles[i].state != 2) &&
                    ((((this->particles[i].pos.x + this->particles[i].vel.x) - spBC) > static130) ||
                     (((this->particles[i].pos.x + this->particles[i].vel.x) - spBC) < -static130) ||
                     (((this->particles[i].pos.y + this->particles[i].vel.y) - spB8) > static130) ||
                     (((this->particles[i].pos.y + this->particles[i].vel.y) - spB8) < -static130) ||
                     (((this->particles[i].pos.z + this->particles[i].vel.z) - spB4) > static130) ||
                     (((this->particles[i].pos.z + this->particles[i].vel.z) - spB4) < -static130))) {
                    if (((this->particles[i].vel.x + this->particles[i].pos.x) - spBC) > static130) {
                        this->particles[i].vel.x = 0.0f;
                        this->particles[i].pos.x = spBC - static130;
                    }

                    if (((this->particles[i].pos.x + this->particles[i].vel.x) - spBC) < -static130) {
                        this->particles[i].vel.x = 0.0f;
                        this->particles[i].pos.x = spBC + static130;
                    }

                    if (((this->particles[i].pos.y + this->particles[i].vel.y) - spB8) > 50.0f) {
                        this->particles[i].vel.y = 0.0f;
                        this->particles[i].pos.y = spB8 - 50.0f;
                    }

                    if (((this->particles[i].pos.y + this->particles[i].vel.y) - spB8) < -50.0f) {
                        this->particles[i].vel.y = 0.0f;
                        this->particles[i].pos.y = spB8 + 50.0f;
                    }

                    if (((this->particles[i].pos.z + this->particles[i].vel.z) - spB4) > static130) {
                        this->particles[i].vel.z = 0.0f;
                        this->particles[i].pos.z = spB4 - static130;
                    }

                    if (((this->particles[i].pos.z + this->particles[i].vel.z) - spB4) < -static130) {
                        this->particles[i].vel.z = 0.0f;
                        this->particles[i].pos.z = spB4 + static130;
                    }
                }
                break;

            case 3: // reset? ready for again?
                this->particles[i].state = 0;
                break;
        }
    }
}

void DemoKakyo_GiantObjectCheck(DemoKankyo* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objectId)) {
        this->isSafeToDrawGiants = true;
        this->actor.objBankIndex = this->objectId;
        DemoKankyo_SetupAction(this, DemoKakyo_MoonSparklesActionFunc);
    }
}

// used by Moon AND giants
void DemoKakyo_MoonSparklesActionFunc(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f viewDiff;
    f32 distATanX; // not Vec3f, stack misorder
    f32 distATanY;
    f32 distATanZ;
    f32 distance;
    f32 value160161;
    f32 temp_f2_3;
    f32 pad0;
    Vec3f newEye;
    f32 halfScreenHeight;
    s32 pad1;
    Vec3f newPos;

    if (globalCtx->envCtx.unk_F2[3] < DEMOKANKYO_PARTICLE_COUNT) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    viewDiff.x = globalCtx->view.at.x - globalCtx->view.eye.x;
    viewDiff.y = globalCtx->view.at.y - globalCtx->view.eye.y;
    viewDiff.z = globalCtx->view.at.z - globalCtx->view.eye.z;
    distance = sqrtf(SQ(viewDiff.x) + SQ(viewDiff.y) + SQ(viewDiff.z));
    distATanX = viewDiff.x / distance;
    distATanY = viewDiff.y / distance;
    distATanZ = viewDiff.z / distance;

    halfScreenHeight = 120.0f; // not sure why this is static here

    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
        switch (this->particles[i].state) {
            case 0: // init, changes to state 1 at the end
                this->particles[i].pos.x = globalCtx->view.eye.x + (distATanX * halfScreenHeight);
                this->particles[i].pos.y = globalCtx->view.eye.y + (distATanY * halfScreenHeight);
                this->particles[i].pos.z = globalCtx->view.eye.z + (distATanZ * halfScreenHeight);
                this->particles[i].vel.x = (Rand_ZeroOne() - 0.5f) * (halfScreenHeight + halfScreenHeight);
                this->particles[i].vel.y = (Rand_ZeroOne() - 0.5f) * (halfScreenHeight + halfScreenHeight);
                this->particles[i].vel.z = (Rand_ZeroOne() - 0.5f) * (halfScreenHeight + halfScreenHeight);
                this->particles[i].unk_38 = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].alpha = 0;
                this->particles[i].unk_3C = (Rand_ZeroOne() * 65535);
                this->particles[i].unk_44 = 0.2f;
                this->particles[i].unk_28.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.z = Rand_ZeroOne() * 360.0f;
                this->particles[i].pad50 = 0;
                this->particles[i].state += 1;
                break;

            case 1:
            case 2:
                this->particles[i].unk_3C += 1;

                if (this->actor.params == DEMO_KANKYO_TYPE_MOON) { // not giants
                    this->particles[i].pos.y = globalCtx->view.eye.y + (distATanY * halfScreenHeight) + 80.0f;
                }

                newEye.x = globalCtx->view.eye.x + (distATanX * halfScreenHeight);
                newEye.y = globalCtx->view.eye.y + (distATanY * halfScreenHeight);
                newEye.z = globalCtx->view.eye.z + (distATanZ * halfScreenHeight);
                Math_SmoothStepToF(&this->particles[i].unk_44, 0.2f, 0.1f, 0.001f, 0.00001f);
                Math_SmoothStepToF(&this->particles[i].speed, this->particles[i].unk_38, 0.5f, 0.2f, 0.02f);

                this->particles[i].vel.x += __sinf(this->particles[i].unk_28.x) * this->particles[i].speed;
                this->particles[i].vel.y += __sinf(this->particles[i].unk_28.y) * this->particles[i].speed;
                this->particles[i].vel.z += __sinf(this->particles[i].unk_28.z) * this->particles[i].speed;

                switch ((i >> 1) & 3) {
                    case 0:
                        this->particles[i].unk_28.x += 0.008f;
                        this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.015f;
                        break;

                    case 1:
                        this->particles[i].unk_28.x += 0.01f  * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.05f  * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.005f * Rand_ZeroOne();
                        break;

                    case 2:
                        this->particles[i].unk_28.x += 0.01f  * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.4f   * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.004f * Rand_ZeroOne();
                        break;

                    case 3:
                        this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.08f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.05f * Rand_ZeroOne();
                        break;
                }

                if (((this->particles[i].pos.x + this->particles[i].vel.x) - newEye.x) > halfScreenHeight) {
                    this->particles[i].pos.x = newEye.x - halfScreenHeight;
                }

                if (((this->particles[i].pos.x + this->particles[i].vel.x) - newEye.x) < -halfScreenHeight) {
                    this->particles[i].pos.x = newEye.x + halfScreenHeight;
                }

                newPos.x = this->particles[i].pos.x + this->particles[i].vel.x;
                newPos.y = this->particles[i].pos.y + this->particles[i].vel.y;
                newPos.z = this->particles[i].pos.z + this->particles[i].vel.z;
                temp_f2_3 = Math_Vec3f_DistXZ(&newPos, &globalCtx->view.eye) / 200.0f;
                temp_f2_3 = CLAMP(temp_f2_3, 0.0f, 1.0f);
                value160161 = 100.0f + temp_f2_3 + 60.0f; // range 160 to 161...?

                if (value160161 < ((this->particles[i].pos.y + this->particles[i].vel.y) - newEye.y)) {
                    this->particles[i].pos.y = newEye.y - value160161;
                }

                if (((this->particles[i].pos.y + this->particles[i].vel.y) - newEye.y) < -value160161) {
                    this->particles[i].pos.y = newEye.y + value160161;
                }

                if (((this->particles[i].pos.z + this->particles[i].vel.z) - newEye.z) > halfScreenHeight) {
                    this->particles[i].pos.z = newEye.z - halfScreenHeight;
                }

                if (((this->particles[i].pos.z + this->particles[i].vel.z) - newEye.z) < -halfScreenHeight) {
                    this->particles[i].pos.z = newEye.z + halfScreenHeight;
                }

                break;

            case 3:
                this->particles[i].state = 0;
                break;
        }
    }
}

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;
    s32 pad;
    s32 i;
    s32 oID;

    // This must be a single line to match, possibly a macro?
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(this->particles); i++) { this->particles[i].state = 0; }
    // clang-format on

    if (0) {};

    switch (this->actor.params) {
        case DEMO_KANKYO_TYPE_LOSTWOODS:
            oID = 0;
            this->actor.room = -1;
            if (sLostWoodsSparklesMutex == false) {
                DemoKankyo_SetupAction(this, DemoKakyo_LostWoodsSparkleActionFunc);
                sLostWoodsSparklesMutex = true;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
            break;

        case DEMO_KANKYO_TYPE_GIANTS:
            this->isSafeToDrawGiants = false;
            oID = Object_GetIndex(&globalCtx->objectCtx, sObjectBubbleIndex);
            DemoKankyo_SetupAction(this, DemoKakyo_GiantObjectCheck);
            break;

        case DEMO_KANKYO_TYPE_MOON:
            oID = 0;
            this->isSafeToDrawGiants = true;
            DemoKankyo_SetupAction(this, DemoKakyo_MoonSparklesActionFunc);
            break;

        default:
            // ! @ BUG: this causes a crash because the actionfunc is never set
            oID = -1;
            break;
    }

    if (oID >= 0) {
        this->objectId = oID;
    }
}

void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    Actor_MarkForDeath(&this->actor);
}

void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    this->actionFunc(this, globalCtx);
}

void DemoKakyo_DrawLostWoodsSparkle(Actor* thisx, GlobalContext* globalCtx2) {
    DemoKankyo* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s16 i;
    f32 scaleAlpha;
    Vec3f spA4;
    Vec3f sp98;

    if (!(globalCtx->cameraPtrs[0]->flags2 & 0x100)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);

        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(&D_04079B10));
        gSPDisplayList(POLY_XLU_DISP++, D_0407AB10);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            spA4.x = this->particles[i].pos.x + this->particles[i].vel.x;
            spA4.y = this->particles[i].pos.y + this->particles[i].vel.y;
            spA4.z = this->particles[i].pos.z + this->particles[i].vel.z;

            // if we disable this, then no particles are shown, likely has to do with their opacity
            func_80169474(globalCtx, &spA4, &sp98); // unamed Play_ function
  
            if ((sp98.x >= 0.0f) && (sp98.x < 320.0f) && (sp98.y >= 0.0f) && (sp98.y < 240.0f)) {
                SysMatrix_InsertTranslation(spA4.x, spA4.y, spA4.z, MTXMODE_NEW);
                scaleAlpha = this->particles[i].alpha / 50.0f;
                if (scaleAlpha > 1.0f) {
                    scaleAlpha = 1.0f;
                }

                Matrix_Scale(this->particles[i].unk_44 * scaleAlpha, this->particles[i].unk_44 * scaleAlpha,
                             this->particles[i].unk_44 * scaleAlpha, MTXMODE_APPLY);
                // what a weird mess
                if (i < 32) {
                    if (this->particles[i].state != 2) {
                        if (this->particles[i].alpha > 0) { // NOT DECR
                            this->particles[i].alpha--;
                        }
                    } else if (this->particles[i].alpha < 100) {
                        this->particles[i].alpha++;
                    }
                } else if (this->particles[i].state != 2) {
                    if ((this->particles[i].unk_3C & 0x1F) < 16) {
                        if (this->particles[i].alpha < 0xEB) {
                            this->particles[i].alpha += 20;
                        }
                    } else if (this->particles[i].alpha > 20) {
                        this->particles[i].alpha -= 20;
                    }
                } else if ((this->particles[i].unk_3C & 0xF) < 8) {
                    if (this->particles[i].alpha < 0xFF) {
                        this->particles[i].alpha += 100;
                    }
                } else if (this->particles[i].alpha > 10) {
                    this->particles[i].alpha -= 10;
                }

                gDPPipeSync(POLY_XLU_DISP++);


                switch (i & 1) {
                    case 0:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 155, this->particles[i].alpha); // gold particles
                        gDPSetEnvColor(POLY_XLU_DISP++, 250, 180, 0, this->particles[i].alpha);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, this->particles[i].alpha); // silver particles
                        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, this->particles[i].alpha);
                        break;
                }

                SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_APPLY);
                SysMatrix_InsertZRotation_f(globalCtx->state.frames * 20.0f * 0.017453292f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_0407AB58);
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

// draw, giants and moon
void func_808CFE04(Actor* thisx, GlobalContext* globalCtx2) {
    DemoKankyo* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s16 i;
    f32 alphaScale;

    if (this->isSafeToDrawGiants != false) {
        Vec3f spB4;
        Vec3f spA8;
        s32 pad;
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

        OPEN_DISPS(gfxCtx);
        func_8012C2DC(gfxCtx);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            spB4.x = this->particles[i].pos.x + this->particles[i].vel.x;
            spB4.y = this->particles[i].pos.y + this->particles[i].vel.y;
            spB4.z = this->particles[i].pos.z + this->particles[i].vel.z;
            func_80169474(globalCtx, &spB4, &spA8);
            if ((spA8.x >= 0.0f) && (spA8.x < 320.0f) && (spA8.y >= 0.0f) && (spA8.y < 240.0f)) {
                SysMatrix_InsertTranslation(spB4.x, spB4.y, spB4.z, MTXMODE_NEW);
                alphaScale = this->particles[i].alpha / 50.0f;
                if (alphaScale > 1.0f) {
                    alphaScale = 1.0f;
                }
                Matrix_Scale(this->particles[i].unk_44 * alphaScale, this->particles[i].unk_44 * alphaScale,
                             this->particles[i].unk_44 * alphaScale, MTXMODE_APPLY);
                alphaScale = Math_Vec3f_DistXYZ(&spB4, &globalCtx->view.eye) / 300.0f;
                alphaScale = (alphaScale > 1.0f) ? 0.0f : (1.0f - alphaScale) > 1.0f ? 1.0f : 1.0f - alphaScale;

                if (this->actor.params == DEMO_KANKYO_TYPE_GIANTS) {
                    this->particles[i].alpha = 255.0f * alphaScale;
                } else {
                    this->particles[i].alpha = 160.0f * alphaScale;
                }

                gDPPipeSync(POLY_XLU_DISP++);

                switch (i & 1) {
                    case 0:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 230, 230, 220, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 230, 230, 30, this->particles[i].alpha);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 200, 190, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 30, this->particles[i].alpha);
                        break;
                }

                gSPDisplayList(POLY_XLU_DISP++, &D_04023348);

                SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_APPLY); 
                // macro?
                SysMatrix_InsertZRotation_f(globalCtx->state.frames * 20.0f * 0.017453292f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (this->actor.params == DEMO_KANKYO_TYPE_GIANTS) {
                    gSPDisplayList(POLY_XLU_DISP++, D_06001000);
                } else {
                    gSPDisplayList(POLY_XLU_DISP++, D_04023428);
                }
            }
        }

        CLOSE_DISPS(gfxCtx);
    }
}

void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    switch (this->actor.params) {
        case DEMO_KANKYO_TYPE_LOSTWOODS:
            DemoKakyo_DrawLostWoodsSparkle(&this->actor, globalCtx);
            break;

        case DEMO_KANKYO_TYPE_GIANTS:
        case DEMO_KANKYO_TYPE_MOON:
            func_808CFE04(this, globalCtx);
            break;
    }
}
