/*
 * File: z_demo_kankyo.c
 * Overlay: ovl_Demo_Kankyo
 * Description: Background Lost Woods/Giant's Chamber/Moon Particles
 */

#include "z_demo_kankyo.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_bubble/object_bubble.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

void DemoKakyo_MoonSparklesActionFunc(DemoKankyo* this, GlobalContext* globalCtx);

static u8 sLostWoodsSparklesMutex = false; // make sure only one can exist at once
static s16 sLostWoodsSkyFishParticleNum = 0;

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

static s32 sObjectBubbleIndex = OBJECT_BUBBLE | 0x10000;

void DemoKankyo_SetupAction(DemoKankyo* this, DemoKankyoActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DemoKakyo_LostWoodsSparkleActionFunc(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    f32 randSkyfishParticleNum;
    f32 repositionLimit; // Distance from posCenter when particles are relocated. Always set to 130.0f
    f32 eyeToAtNormX;
    f32 eyeToAtNormY;
    f32 eyeToAtNormZ;
    f32 eyeToAtMag;
    f32 posCenterX;
    f32 posCenterY;
    f32 posCenterZ;
    Vec3f eyeToAt;
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->roomCtx.unk7A[1] != 0) {
        if (globalCtx->envCtx.unk_F2[3] != 0) {
            globalCtx->envCtx.unk_F2[3]--;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (globalCtx->envCtx.unk_F2[3] < DEMOKANKYO_PARTICLE_COUNT) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    // note: DemoKankyo can crash if placed in an area that snows (ObjectKankyo)
    // because they both use unk_F2 as a particle counter,
    // causing DemoKankyo to write beyond its particle array boundry
    // this crash can occur if the two actors are in different scenes connected by an exit
    // e.g. if you add DemoKankyo to GoronShrine, you will crash entering/leaving through door
    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
        repositionLimit = 130.0f;

        eyeToAt.x = globalCtx->view.at.x - globalCtx->view.eye.x;
        eyeToAt.y = globalCtx->view.at.y - globalCtx->view.eye.y;
        eyeToAt.z = globalCtx->view.at.z - globalCtx->view.eye.z;
        eyeToAtMag = sqrtf(SQXYZ(eyeToAt));
        eyeToAtNormX = eyeToAt.x / eyeToAtMag;
        eyeToAtNormY = eyeToAt.y / eyeToAtMag;
        eyeToAtNormZ = eyeToAt.z / eyeToAtMag;

        switch (this->particles[i].state) {
            case DEMO_KANKYO_STATE_INIT:
                this->particles[i].posBase.x = globalCtx->view.eye.x + (eyeToAtNormX * 80.0f);
                this->particles[i].posBase.y = globalCtx->view.eye.y + (eyeToAtNormY * 80.0f);
                this->particles[i].posBase.z = globalCtx->view.eye.z + (eyeToAtNormZ * 80.0f);

                this->particles[i].posOffset.x = (Rand_ZeroOne() - 0.5f) * 160.0f;
                this->particles[i].posOffset.y = 30.0f;
                this->particles[i].posOffset.z = (Rand_ZeroOne() - 0.5f) * 160.0f;

                this->particles[i].speedTarget = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].alpha = 0;
                this->particles[i].alphaClock = Rand_ZeroOne() * 65535; // random 0 to max of u16
                this->particles[i].scale = 0.1f;

                // speedClock is angles in radians,
                // should have used Rand_ZeroOne() * 2 * M_PI
                // however, due to properties of sine waves, this is effectively still random
                this->particles[i].speedClock.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].speedClock.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].speedClock.z = Rand_ZeroOne() * 360.0f;
                this->particles[i].pad50 = 0;
                this->particles[i].state += DEMO_KANKYO_STATE_SINGLE;
                break;

            case DEMO_KANKYO_STATE_SINGLE:
            case DEMO_KANKYO_STATE_SKYFISH:
                this->particles[i].alphaClock++;
                posCenterX = globalCtx->view.eye.x + (eyeToAtNormX * 80.0f);
                posCenterY = globalCtx->view.eye.y + (eyeToAtNormY * 80.0f);
                posCenterZ = globalCtx->view.eye.z + (eyeToAtNormZ * 80.0f);
                this->particles[i].posOffsetPrev.x = this->particles[i].posOffset.x;
                this->particles[i].posOffsetPrev.y = this->particles[i].posOffset.y;
                this->particles[i].posOffsetPrev.z = this->particles[i].posOffset.z;

                if (this->particles[i].state == DEMO_KANKYO_STATE_SINGLE) {

                    // The first 32 particles will become skyfish particles
                    // This block is also init code and only runs once
                    if (i < 32) {
                        if (Rand_ZeroOne() < 0.5f) {
                            this->particles[i].LostWoodsSkyFishSpeedXZ = (s16)(Rand_ZeroOne() * 200.0f) + 200;
                        } else {
                            this->particles[i].LostWoodsSkyFishSpeedXZ = -200 - (s16)(Rand_ZeroOne() * 200.0f);
                        }
                        this->particles[i].LostWoodsSkyFishPosOffsetMax = (s16)(Rand_ZeroOne() * 50.0f) + 15;
                        this->particles[i].LostWoodsSkyFishSpeedY = ((Rand_ZeroOne() * 10.0f) + 10.0f) * 0.01f;

                        // Only the 31st particle matters as sLostWoodsSkyFishParticleNum will be overwritten
                        // every particle until the last skyfish particle is initialized
                        randSkyfishParticleNum = Rand_ZeroOne();
                        if (randSkyfishParticleNum < 0.2f) {
                            sLostWoodsSkyFishParticleNum = 1;
                        } else if (randSkyfishParticleNum < 0.2f) {
                            // This case is never taken as the else-if conditional is identical to the previous one
                            sLostWoodsSkyFishParticleNum = 3;
                        } else if (randSkyfishParticleNum < 0.4f) {
                            sLostWoodsSkyFishParticleNum = 7;
                        } else {
                            sLostWoodsSkyFishParticleNum = 15;
                        }

                        if ((i & sLostWoodsSkyFishParticleNum) == 0) {
                            // Head particle
                            this->particles[i].posOffset.y = 0.0f;
                        }
                        this->particles[i].state = DEMO_KANKYO_STATE_SKYFISH;
                        this->particles[i].speedTarget = 0.0f;
                    }

                    Math_SmoothStepToF(&this->particles[i].scale, 0.1, 0.1f, 0.001f, 0.00001f);
                    Math_SmoothStepToF(&this->particles[i].speed, this->particles[i].speedTarget, 0.5f, 0.2f, 0.02f);
                    this->particles[i].posOffset.x +=
                        __sinf(this->particles[i].speedClock.x) * this->particles[i].speed;
                    this->particles[i].posOffset.y +=
                        __sinf(this->particles[i].speedClock.y) * this->particles[i].speed;
                    this->particles[i].posOffset.z +=
                        __sinf(this->particles[i].speedClock.z) * this->particles[i].speed;

                    switch ((i >> 1) & 3) {
                        case 0:
                            this->particles[i].speedClock.x += 0.008f;
                            this->particles[i].speedClock.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].speedClock.z += 0.015f;
                            break;

                        case 1:
                            this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].speedClock.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].speedClock.z += 0.005f * Rand_ZeroOne();
                            break;

                        case 2:
                            this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].speedClock.y += 0.4f * Rand_ZeroOne();
                            this->particles[i].speedClock.z += 0.004f * Rand_ZeroOne();
                            break;

                        case 3:
                            this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].speedClock.y += 0.08f * Rand_ZeroOne();
                            this->particles[i].speedClock.z += 0.05f * Rand_ZeroOne();
                            break;
                    }

                } else if (this->particles[i].state == DEMO_KANKYO_STATE_SKYFISH) {
                    if ((i & sLostWoodsSkyFishParticleNum) == 0) {
                        // Head particle
                        Math_SmoothStepToF(&this->particles[i].scale, 0.25f, 0.1f, 0.001f, 0.00001f);

                        Math_SmoothStepToF(&this->particles[i].posBase.x, player->actor.world.pos.x, 0.5f, 1.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].posBase.y, player->actor.world.pos.y + 50.0f, 0.5f, 1.0f,
                                           0.2f);
                        Math_SmoothStepToF(&this->particles[i].posBase.z, player->actor.world.pos.z, 0.5f, 1.0f, 0.2f);

                        Math_SmoothStepToF(&this->particles[i].posOffset.x,
                                           Math_SinS(this->particles[i].LostWoodsSkyFishSpeedXZClock - 0x8000) *
                                               this->particles[i].LostWoodsSkyFishPosOffsetMax,
                                           0.5f, 2.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].posOffset.z,
                                           Math_CosS(this->particles[i].LostWoodsSkyFishSpeedXZClock - 0x8000) *
                                               this->particles[i].LostWoodsSkyFishPosOffsetMax,
                                           0.5f, 2.0f, 0.2f);
                        this->particles[i].LostWoodsSkyFishSpeedXZClock += this->particles[i].LostWoodsSkyFishSpeedXZ;
                        this->particles[i].posOffset.y += __sinf(this->particles[i].speedClock.y);
                        this->particles[i].speedClock.x += 0.2f * Rand_ZeroOne(); // unused calculation
                        this->particles[i].speedClock.y += this->particles[i].LostWoodsSkyFishSpeedY;
                        this->particles[i].speedClock.z += 0.1f * Rand_ZeroOne(); // unused calculation

                        this->particles[i].posOffset.x =
                            Math_SinS(this->particles[i].LostWoodsSkyFishSpeedXZClock - 0x8000) *
                            this->particles[i].LostWoodsSkyFishPosOffsetMax;
                        this->particles[i].posOffset.z =
                            Math_CosS(this->particles[i].LostWoodsSkyFishSpeedXZClock - 0x8000) *
                            this->particles[i].LostWoodsSkyFishPosOffsetMax;
                    } else {
                        // Tail Particles
                        Math_SmoothStepToF(&this->particles[i].scale, 0.1, 0.1f, 0.001f, 0.00001f);

                        // Unused calculation, speed only used in posOffset calculations,
                        // but posOffset gets overwritten for tail particles immediately below
                        Math_SmoothStepToF(&this->particles[i].speed, 1.5f, 0.5f, 0.1f, 0.0002f);

                        // particles in the skyfish's tail are moved to the previous position of the particle directly
                        // in front
                        this->particles[i].posOffset.x =
                            this->particles[i - 1].posOffsetPrev.x +
                            (this->particles[i - 1].posBase.x - this->particles[i].posBase.x);
                        this->particles[i].posOffset.y =
                            this->particles[i - 1].posOffsetPrev.y +
                            (this->particles[i - 1].posBase.y - this->particles[i].posBase.y);
                        this->particles[i].posOffset.z =
                            this->particles[i - 1].posOffsetPrev.z +
                            (this->particles[i - 1].posBase.z - this->particles[i].posBase.z);
                    }
                }

                if ((this->particles[i].state != DEMO_KANKYO_STATE_SKYFISH) &&
                    ((((this->particles[i].posBase.x + this->particles[i].posOffset.x) - posCenterX) >
                      repositionLimit) ||
                     (((this->particles[i].posBase.x + this->particles[i].posOffset.x) - posCenterX) <
                      -repositionLimit) ||
                     (((this->particles[i].posBase.y + this->particles[i].posOffset.y) - posCenterY) >
                      repositionLimit) ||
                     (((this->particles[i].posBase.y + this->particles[i].posOffset.y) - posCenterY) <
                      -repositionLimit) ||
                     (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - posCenterZ) >
                      repositionLimit) ||
                     (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - posCenterZ) <
                      -repositionLimit))) {
                    if (((this->particles[i].posOffset.x + this->particles[i].posBase.x) - posCenterX) >
                        repositionLimit) {
                        this->particles[i].posOffset.x = 0.0f;
                        this->particles[i].posBase.x = posCenterX - repositionLimit;
                    }

                    if (((this->particles[i].posBase.x + this->particles[i].posOffset.x) - posCenterX) <
                        -repositionLimit) {
                        this->particles[i].posOffset.x = 0.0f;
                        this->particles[i].posBase.x = posCenterX + repositionLimit;
                    }

                    if (((this->particles[i].posBase.y + this->particles[i].posOffset.y) - posCenterY) > 50.0f) {
                        this->particles[i].posOffset.y = 0.0f;
                        this->particles[i].posBase.y = posCenterY - 50.0f;
                    }

                    if (((this->particles[i].posBase.y + this->particles[i].posOffset.y) - posCenterY) < -50.0f) {
                        this->particles[i].posOffset.y = 0.0f;
                        this->particles[i].posBase.y = posCenterY + 50.0f;
                    }

                    if (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - posCenterZ) >
                        repositionLimit) {
                        this->particles[i].posOffset.z = 0.0f;
                        this->particles[i].posBase.z = posCenterZ - repositionLimit;
                    }

                    if (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - posCenterZ) <
                        -repositionLimit) {
                        this->particles[i].posOffset.z = 0.0f;
                        this->particles[i].posBase.z = posCenterZ + repositionLimit;
                    }
                }
                break;

            case DEMO_KANKYO_STATE_DISABLED:
                this->particles[i].state = DEMO_KANKYO_STATE_INIT;
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

/*
 * used by Moon AND giants types
 */
void DemoKakyo_MoonSparklesActionFunc(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f eyeToAt;
    f32 eyeToAtNormX;
    f32 eyeToAtNormY;
    f32 eyeToAtNormZ;
    f32 eyeToAtMag;
    f32 halfScreenWidth;
    f32 randZeroOne;
    f32 pad0;
    Vec3f newEye;
    f32 halfScreenHeight;
    s32 pad1;
    Vec3f worldPos;

    if (globalCtx->envCtx.unk_F2[3] < DEMOKANKYO_PARTICLE_COUNT) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    eyeToAt.x = globalCtx->view.at.x - globalCtx->view.eye.x;
    eyeToAt.y = globalCtx->view.at.y - globalCtx->view.eye.y;
    eyeToAt.z = globalCtx->view.at.z - globalCtx->view.eye.z;
    eyeToAtMag = sqrtf(SQXYZ(eyeToAt));
    eyeToAtNormX = eyeToAt.x / eyeToAtMag;
    eyeToAtNormY = eyeToAt.y / eyeToAtMag;
    eyeToAtNormZ = eyeToAt.z / eyeToAtMag;

    halfScreenHeight = SCREEN_HEIGHT / 2;

    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
        switch (this->particles[i].state) {
            case DEMO_KANKYO_STATE_INIT:
                this->particles[i].posBase.x = globalCtx->view.eye.x + (eyeToAtNormX * halfScreenHeight);
                this->particles[i].posBase.y = globalCtx->view.eye.y + (eyeToAtNormY * halfScreenHeight);
                this->particles[i].posBase.z = globalCtx->view.eye.z + (eyeToAtNormZ * halfScreenHeight);

                this->particles[i].posOffset.x = (Rand_ZeroOne() - 0.5f) * (2.0f * halfScreenHeight);
                this->particles[i].posOffset.y = (Rand_ZeroOne() - 0.5f) * (2.0f * halfScreenHeight);
                this->particles[i].posOffset.z = (Rand_ZeroOne() - 0.5f) * (2.0f * halfScreenHeight);

                this->particles[i].speedTarget = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].alpha = 0;
                this->particles[i].alphaClock = (Rand_ZeroOne() * 65535);
                this->particles[i].scale = 0.2f;

                // speedClock is angles in radians,
                // should have used Rand_ZeroOne() * 2 * M_PI
                // however, due to properties of sine waves, this is effectively still random
                this->particles[i].speedClock.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].speedClock.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].speedClock.z = Rand_ZeroOne() * 360.0f;

                this->particles[i].pad50 = 0;
                this->particles[i].state += DEMO_KANKYO_STATE_SINGLE;
                break;

            case DEMO_KANKYO_STATE_SINGLE:
            case DEMO_KANKYO_STATE_SKYFISH:
                this->particles[i].alphaClock++;

                if (this->actor.params == DEMO_KANKYO_TYPE_MOON) { // this function gets reused for giants too
                    this->particles[i].posBase.y =
                        globalCtx->view.eye.y + (eyeToAtNormY * halfScreenHeight) + (SCREEN_HEIGHT / 3);
                }

                newEye.x = globalCtx->view.eye.x + (eyeToAtNormX * halfScreenHeight);
                newEye.y = globalCtx->view.eye.y + (eyeToAtNormY * halfScreenHeight);
                newEye.z = globalCtx->view.eye.z + (eyeToAtNormZ * halfScreenHeight);

                Math_SmoothStepToF(&this->particles[i].scale, 0.2f, 0.1f, 0.001f, 0.00001f);
                Math_SmoothStepToF(&this->particles[i].speed, this->particles[i].speedTarget, 0.5f, 0.2f, 0.02f);

                this->particles[i].posOffset.x += __sinf(this->particles[i].speedClock.x) * this->particles[i].speed;
                this->particles[i].posOffset.y += __sinf(this->particles[i].speedClock.y) * this->particles[i].speed;
                this->particles[i].posOffset.z += __sinf(this->particles[i].speedClock.z) * this->particles[i].speed;

                switch ((i >> 1) & 3) {
                    case 0:
                        this->particles[i].speedClock.x += 0.008f;
                        this->particles[i].speedClock.y += 0.05f * Rand_ZeroOne();
                        this->particles[i].speedClock.z += 0.015f;
                        break;

                    case 1:
                        this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].speedClock.y += 0.05f * Rand_ZeroOne();
                        this->particles[i].speedClock.z += 0.005f * Rand_ZeroOne();
                        break;

                    case 2:
                        this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].speedClock.y += 0.4f * Rand_ZeroOne();
                        this->particles[i].speedClock.z += 0.004f * Rand_ZeroOne();
                        break;

                    case 3:
                        this->particles[i].speedClock.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].speedClock.y += 0.08f * Rand_ZeroOne();
                        this->particles[i].speedClock.z += 0.05f * Rand_ZeroOne();
                        break;
                }

                if (((this->particles[i].posBase.x + this->particles[i].posOffset.x) - newEye.x) > halfScreenHeight) {
                    this->particles[i].posBase.x = newEye.x - halfScreenHeight;
                }

                if (((this->particles[i].posBase.x + this->particles[i].posOffset.x) - newEye.x) < -halfScreenHeight) {
                    this->particles[i].posBase.x = newEye.x + halfScreenHeight;
                }

                worldPos.x = this->particles[i].posBase.x + this->particles[i].posOffset.x;
                worldPos.y = this->particles[i].posBase.y + this->particles[i].posOffset.y;
                worldPos.z = this->particles[i].posBase.z + this->particles[i].posOffset.z;

                randZeroOne = Math_Vec3f_DistXZ(&worldPos, &globalCtx->view.eye) / 200.0f;
                randZeroOne = CLAMP(randZeroOne, 0.0f, 1.0f);
                halfScreenWidth = 100.0f + randZeroOne + 60.0f; // range 160 to 161...? thats about half screen width

                // I think this code is shifting the particles 1 frame -> half screen at a time to keep it in-view
                if (halfScreenWidth < ((this->particles[i].posBase.y + this->particles[i].posOffset.y) - newEye.y)) {
                    this->particles[i].posBase.y = newEye.y - halfScreenWidth;
                }

                if (((this->particles[i].posBase.y + this->particles[i].posOffset.y) - newEye.y) < -halfScreenWidth) {
                    this->particles[i].posBase.y = newEye.y + halfScreenWidth;
                }

                if (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - newEye.z) > halfScreenHeight) {
                    this->particles[i].posBase.z = newEye.z - halfScreenHeight;
                }

                if (((this->particles[i].posBase.z + this->particles[i].posOffset.z) - newEye.z) < -halfScreenHeight) {
                    this->particles[i].posBase.z = newEye.z + halfScreenHeight;
                }

                break;

            case DEMO_KANKYO_STATE_DISABLED:
                this->particles[i].state = DEMO_KANKYO_STATE_INIT;
                break;
        }
    }
}

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;
    s32 pad;
    s32 i;
    s32 objId;

    // This must be a single line to match, possibly a macro?
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(this->particles); i++) { this->particles[i].state = DEMO_KANKYO_STATE_INIT; }
    // clang-format on

    if (1) {};

    switch (this->actor.params) {
        case DEMO_KANKYO_TYPE_LOSTWOODS:
            objId = OBJECT_UNSET_0;
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
            objId = Object_GetIndex(&globalCtx->objectCtx, sObjectBubbleIndex);
            DemoKankyo_SetupAction(this, DemoKakyo_GiantObjectCheck);
            break;

        case DEMO_KANKYO_TYPE_MOON:
            objId = OBJECT_UNSET_0;
            this->isSafeToDrawGiants = true;
            DemoKankyo_SetupAction(this, DemoKakyo_MoonSparklesActionFunc);
            break;

        default:
            //! @bug: this causes a crash because the actionfunc is never set
            objId = -1;
            break;
    }

    if (objId > -1) {
        this->objectId = objId;
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
    GlobalContext* globalCtx = globalCtx2;
    DemoKankyo* this = THIS;
    s16 i;
    f32 scaleAlpha;
    Vec3f worldPos;
    Vec3f screenPos;

    // if not underwater
    if (!(globalCtx->cameraPtrs[CAM_ID_MAIN]->flags2 & 0x100)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);

        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gSun1Tex));
        gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB10);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            worldPos.x = this->particles[i].posBase.x + this->particles[i].posOffset.x;
            worldPos.y = this->particles[i].posBase.y + this->particles[i].posOffset.y;
            worldPos.z = this->particles[i].posBase.z + this->particles[i].posOffset.z;

            func_80169474(globalCtx, &worldPos, &screenPos); // unnamed Play_ function, func_800C016C from OoT

            // checking if particle is on screen
            if (screenPos.x >= 0.0f && screenPos.x < SCREEN_WIDTH && screenPos.y >= 0.0f &&
                screenPos.y < SCREEN_HEIGHT) {
                Matrix_InsertTranslation(worldPos.x, worldPos.y, worldPos.z, MTXMODE_NEW);
                scaleAlpha = this->particles[i].alpha / 50.0f;
                if (scaleAlpha > 1.0f) {
                    scaleAlpha = 1.0f;
                }

                Matrix_Scale(this->particles[i].scale * scaleAlpha, this->particles[i].scale * scaleAlpha,
                             this->particles[i].scale * scaleAlpha, MTXMODE_APPLY);

                // adjust transparency of this particle
                if (i < 32) {
                    // Skyfish particles
                    if (this->particles[i].state != DEMO_KANKYO_STATE_SKYFISH) {
                        // still initializing
                        if (this->particles[i].alpha > 0) { // NOT DECR
                            this->particles[i].alpha--;
                        }
                    } else if (this->particles[i].alpha < 100) {
                        this->particles[i].alpha++;
                    }
                } else if (this->particles[i].state != DEMO_KANKYO_STATE_SKYFISH) {
                    if ((this->particles[i].alphaClock & 31) < 16) {
                        if (this->particles[i].alpha < 235) {
                            this->particles[i].alpha += 20;
                        }
                    } else if (this->particles[i].alpha > 20) {
                        this->particles[i].alpha -= 20;
                    }
                } else if ((this->particles[i].alphaClock & 15) < 8) {
                    if (this->particles[i].alpha < 255) {
                        this->particles[i].alpha += 100;
                    }
                } else if (this->particles[i].alpha > 10) {
                    this->particles[i].alpha -= 10;
                }

                gDPPipeSync(POLY_XLU_DISP++);

                switch (i & 1) {
                    case 0: // gold particles
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 155, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 250, 180, 0, this->particles[i].alpha);
                        break;

                    case 1: // silver particles
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, this->particles[i].alpha);
                        break;
                }

                Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
                Matrix_InsertZRotation_f(DEGF_TO_RADF(globalCtx->state.frames * 20.0f), MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB58);
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

// draw, giants and moon
void DemoKankyo_DrawMoonAndGiant(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DemoKankyo* this = THIS;
    s16 i;
    f32 alphaScale;

    if (this->isSafeToDrawGiants != false) {
        Vec3f worldPos;
        Vec3f screenPos;
        s32 pad;
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

        OPEN_DISPS(gfxCtx);
        func_8012C2DC(gfxCtx);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            worldPos.x = this->particles[i].posBase.x + this->particles[i].posOffset.x;
            worldPos.y = this->particles[i].posBase.y + this->particles[i].posOffset.y;
            worldPos.z = this->particles[i].posBase.z + this->particles[i].posOffset.z;

            func_80169474(globalCtx, &worldPos, &screenPos); // unnamed Play_ function, func_800C016C from OoT

            // checking if particle is on screen
            if (screenPos.x >= 0.0f && screenPos.x < SCREEN_WIDTH && screenPos.y >= 0.0f &&
                screenPos.y < SCREEN_HEIGHT) {
                Matrix_InsertTranslation(worldPos.x, worldPos.y, worldPos.z, MTXMODE_NEW);
                alphaScale = this->particles[i].alpha / 50.0f;
                if (alphaScale > 1.0f) {
                    alphaScale = 1.0f;
                }
                Matrix_Scale(this->particles[i].scale * alphaScale, this->particles[i].scale * alphaScale,
                             this->particles[i].scale * alphaScale, MTXMODE_APPLY);
                alphaScale = Math_Vec3f_DistXYZ(&worldPos, &globalCtx->view.eye) / 300.0f;
                alphaScale = (alphaScale > 1.0f) ? 0.0f : (1.0f - alphaScale) > 1.0f ? 1.0f : 1.0f - alphaScale;

                if (this->actor.params == DEMO_KANKYO_TYPE_GIANTS) {
                    this->particles[i].alpha = 255.0f * alphaScale;
                } else {
                    this->particles[i].alpha = 160.0f * alphaScale;
                }

                gDPPipeSync(POLY_XLU_DISP++);

                switch (i & 1) { // half/half slightly different shades of yellow/tan
                    case 0:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 230, 230, 220, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 230, 230, 30, this->particles[i].alpha);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 200, 190, this->particles[i].alpha);
                        gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 30, this->particles[i].alpha);
                        break;
                }

                gSPDisplayList(POLY_XLU_DISP++, &gLightOrb1DL);

                Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

                Matrix_InsertZRotation_f(DEGF_TO_RADF(globalCtx->state.frames * 20.0f), MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (this->actor.params == DEMO_KANKYO_TYPE_GIANTS) {
                    gSPDisplayList(POLY_XLU_DISP++, object_bubble_DL_001000);
                } else {
                    gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
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
            DemoKankyo_DrawMoonAndGiant(&this->actor, globalCtx);
            break;
    }
}
