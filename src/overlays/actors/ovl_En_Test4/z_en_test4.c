/*
 * File: z_en_test4.c
 * Overlay: ovl_En_Test4
 * Description: 
 */

#include "z_en_test4.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

#define FLAGS 0x00100030

#define THIS ((EnTest4*)thisx)

void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx);
void func_80A42F20(EnTest4* this, GlobalContext* globalCtx);

const ActorInit En_Test4_InitVars = {
    ACTOR_EN_TEST4,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest4),
    (ActorFunc)EnTest4_Init,
    (ActorFunc)EnTest4_Destroy,
    (ActorFunc)EnTest4_Update,
    (ActorFunc)NULL,
};

s32 D_80A43340 = 0;
s16 D_80A43344[] = {0x1BB4, 0x1BB5, 0x1BB6};
s16 D_80A4334C[] = {0x1BB2, 0x1BB2, 0x1BB3};
s16 D_80A43354[] = {0x1BB4, 0x1BB5, 0x1BB6};
s16 D_80A4335C[] = {0x1BB2, 0x1BB2, 0x1BB3};
u16 D_80A43364[] = {CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)};


extern s32 D_801BDA9C;


s16 D_80A434D0[2];
s16 D_80A434D4;

void func_80A41D70(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_144 != 0) {
        func_80151A68(globalCtx, D_80A43344[CURRENT_DAY-1]);
    } else if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        if (globalCtx->actorCtx.unk5 & 2) {
            Sram_IncrementDay();
            gSaveContext.time = CLOCK_TIME(6, 0);
            func_80151A68(globalCtx, D_80A4334C[CURRENT_DAY-1]);
        } else {
            this->unk_144 = 0;
            this->unk_146 = gSaveContext.time += CLOCK_TIME(0, 1);
        }

        func_8010EE74(globalCtx, CURRENT_DAY);
        D_801BDBC8 = 0xFE;
        func_800FB758(globalCtx);
        func_800FEAF4(&globalCtx->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((D_80A434D0[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
            this->actionFunc = func_80A42F20;
            D_80A434D4 = D_80A434D0[this->unk_144];
            this->unk_145 = 0;
            gSaveContext.eventInf[1] |= 0x80;
        } else if (this->unk_144 == 0) {
            play_sound(0x2813);
        } else {
            func_8019F128(0x28AE);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        this->unk_146 = gSaveContext.time += CLOCK_TIME(0, 1);
    }
}

void func_80A41FA4(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_144 != 0) {
        func_80151A68(globalCtx, D_80A43354[CURRENT_DAY-1]);
    } else if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        Sram_IncrementDay();
        gSaveContext.time = 0x4000;
        func_8010EE74(globalCtx, CURRENT_DAY);
        func_80151A68(globalCtx, D_80A4335C[CURRENT_DAY-1]);
        D_801BDBC8 = 0xFE;
        func_800FB758(globalCtx);
        func_800FEAF4(&globalCtx->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((D_80A434D0[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
            this->actionFunc = func_80A42F20;
            D_80A434D4 = D_80A434D0[this->unk_144];
            this->unk_145 = 0;
            gSaveContext.eventInf[1] |= 0x80;
        } else if (this->unk_144 == 0) {
            play_sound(0x2813U);
        } else {
            func_8019F128(0x28AE);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        this->unk_146 = gSaveContext.time += 0x2D;
    }
}

void func_80A42198(EnTest4* this) {
    if ((gSaveContext.time >= 0x4000) && (gSaveContext.time < 0xC001)) {
        if (gSaveContext.time < 0xBAAA) {
            this->unk_148 = 0xBAAA;
        } else if (gSaveContext.time < 0xBBBB) {
            this->unk_148 = 0xBBBB;
        } else if (gSaveContext.time < 0xBCCC) {
            this->unk_148 = 0xBCCC;
        } else if (gSaveContext.time < 0xBDDD) {
            this->unk_148 = 0xBDDD;
        } else if (gSaveContext.time < 0xBEEE) {
            this->unk_148 = 0xBEEE;
        } else {
            this->unk_148 = 0;
        }
    } else if (gSaveContext.time >= 0x4001) {
        this->unk_148 = 0;
    } else if (gSaveContext.time < 0x1C7) {
        this->unk_148 = 0x1C7;
    } else if (gSaveContext.time < 0x38E) {
        this->unk_148 = 0x38E;
    } else if (gSaveContext.time < 0x555) {
        this->unk_148 = 0x555;
    } else if (gSaveContext.time < 0x71C) {
        this->unk_148 = 0x71C;
    } else if (gSaveContext.time < 0x8E3) {
        this->unk_148 = 0x8E3;
    } else if (gSaveContext.time < 0xAAA) {
        this->unk_148 = 0xAAA;
    } else if (gSaveContext.time < 0xC71) {
        this->unk_148 = 0xC71;
    } else if (gSaveContext.time < 0xE38) {
        this->unk_148 = 0xE38;
    } else if (gSaveContext.time < 0xFFF) {
        this->unk_148 = 0xFFF;
    } else if (gSaveContext.time < 0x11C6) {
        this->unk_148 = 0x11C6;
    } else if (gSaveContext.time < 0x138D) {
        this->unk_148 = 0x138D;
    } else if (gSaveContext.time < 0x1555) {
        this->unk_148 = 0x1555;
    } else if (gSaveContext.time < 0x171C) {
        this->unk_148 = 0x171C;
    } else if (gSaveContext.time < 0x18E3) {
        this->unk_148 = 0x18E3;
    } else if (gSaveContext.time < 0x1AAA) {
        this->unk_148 = 0x1AAA;
    } else if (gSaveContext.time < 0x1C71) {
        this->unk_148 = 0x1C71;
    } else if (gSaveContext.time < 0x1E38) {
        this->unk_148 = 0x1E38;
    } else if (gSaveContext.time < 0x2000) {
        this->unk_148 = 0x2000;
    } else if (gSaveContext.time < 0x21C7) {
        this->unk_148 = 0x21C7;
    } else if (gSaveContext.time < 0x238E) {
        this->unk_148 = 0x238E;
    } else if (gSaveContext.time < 0x2555) {
        this->unk_148 = 0x2555;
    } else if (gSaveContext.time < 0x271C) {
        this->unk_148 = 0x271C;
    } else if (gSaveContext.time < 0x28E3) {
        this->unk_148 = 0x28E3;
    } else if (gSaveContext.time < 0x2AAA) {
        this->unk_148 = 0x2AAA;
    } else if (gSaveContext.time < 0x2C71) {
        this->unk_148 = 0x2C71;
    } else if (gSaveContext.time < 0x2E38) {
        this->unk_148 = 0x2E38;
    } else if (gSaveContext.time < 0x2FFF) {
        this->unk_148 = 0x2FFF;
    } else if (gSaveContext.time < 0x31C6) {
        this->unk_148 = 0x31C6;
    } else if (gSaveContext.time < 0x338D) {
        this->unk_148 = 0x338D;
    } else if (gSaveContext.time < 0x3555) {
        this->unk_148 = 0x3555;
    } else if (gSaveContext.time < 0x3638) {
        this->unk_148 = 0x3638;
    } else if (gSaveContext.time < 0x371C) {
        this->unk_148 = 0x371C;
    } else if (gSaveContext.time < 0x37FF) {
        this->unk_148 = 0x37FF;
    } else if (gSaveContext.time < 0x38E3) {
        this->unk_148 = 0x38E3;
    } else if (gSaveContext.time < 0x39C6) {
        this->unk_148 = 0x39C6;
    } else if (gSaveContext.time < 0x3AAA) {
        this->unk_148 = 0x3AAA;
    } else if (gSaveContext.time < 0x3B32) {
        this->unk_148 = 0x3B32;
    } else if (gSaveContext.time < 0x3BBB) {
        this->unk_148 = 0x3BBB;
    } else if (gSaveContext.time < 0x3C43) {
        this->unk_148 = 0x3C43;
    } else if (gSaveContext.time < 0x3CCC) {
        this->unk_148 = 0x3CCC;
    } else if (gSaveContext.time < 0x3D55) {
        this->unk_148 = 0x3D55;
    } else if (gSaveContext.time < 0x3DDD) {
        this->unk_148 = 0x3DDD;
    } else if (gSaveContext.time < 0x3E66) {
        this->unk_148 = 0x3E66;
    } else if (gSaveContext.time < 0x3EEE) {
        this->unk_148 = 0x3EEE;
    } else if (gSaveContext.time < 0x3F77) {
        this->unk_148 = 0x3F77;
    } else if (gSaveContext.time < 0x4000) {
        this->unk_148 = 0x4000;
    }
}

void func_80A425E4(EnTest4* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3F64 = 1000.0f;

    if ((gSaveContext.time >= 0x4000) && (gSaveContext.time < 0xC000)) {
        if (gSaveContext.time < 0xBAAA) {
            this->unk_148 = 0xBAAA;
        } else if (gSaveContext.time < 0xBBBB) {
            this->unk_148 = 0xBBBB;
        } else if (gSaveContext.time < 0xBCCC) {
            this->unk_148 = 0xBCCC;
        } else if (gSaveContext.time < 0xBDDD) {
            this->unk_148 = 0xBDDD;
        } else if (gSaveContext.time < 0xBEEE) {
            this->unk_148 = 0xBEEE;
        } else {
            this->unk_148 = 0x3AAA;
        }
    } else {
        if (gSaveContext.time < 0x3AAA) {
            this->unk_148 = 0x3AAA;
        } else if (gSaveContext.time < 0x3BBB) {
            this->unk_148 = 0x3BBB;
        } else if (gSaveContext.time < 0x3CCC) {
            this->unk_148 = 0x3CCC;
            gSaveContext.unk_3F64 -= 50.0f;
        } else if (gSaveContext.time < 0x3DDD) {
            this->unk_148 = 0x3DDD;
            gSaveContext.unk_3F64 -= 100.0f;
        } else if (gSaveContext.time < 0x3EEE) {
            this->unk_148 = 0x3EEE;
            gSaveContext.unk_3F64 -= 150.0f;
        } else if (gSaveContext.time < 0x4000) {
            this->unk_148 = 0xBAAA;
            gSaveContext.unk_3F64 -= 200.0f;
        } else {
            this->unk_148 = 0xBAAA;
        }

        if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0) || (CURRENT_DAY == 3) || (gSaveContext.time >= CLOCK_TIME(17, 0))) {
            gSaveContext.unk_3F64 = 1000.0f;
        }
        if (gSaveContext.unk_3F64 != 1000.0f) {
            gSaveContext.unk_3F60 = 1;
        }
    }
}

#ifdef NON_MATCHING
void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTest4* this = THIS;
    Player* player = PLAYER;
    s8 temp_v0;

    temp_v0 = this->actor.cutscene;
    D_80A434D0[0] = temp_v0;
    if (temp_v0 >= 0) {
        ActorCutscene* temp_v0_2 = ActorCutscene_GetCutscene(D_80A434D0[0]);

        gSaveContext.eventInf[5] |= 0x04;
        D_80A434D0[1] = temp_v0_2->additionalCutscene;
    } else {
        gSaveContext.eventInf[5] &= (u8)~0x04;
        D_80A434D0[1] = D_80A434D0[0];
    }

    if ((D_80A43340 != 0) || ((gSaveContext.eventInf[2] & 0x80) != 0)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        D_80A43340 = 1;
        this->actor.room = -1;
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
        if (CURRENT_DAY == 0) {
            if (gSaveContext.time < 0x402D) {
                gSaveContext.time = 0x4000;
                gSaveContext.gameMode = 0;
                do {
                    GameState* state = &globalCtx->state; 
                    state->running = false;
                } while(0);
                SET_NEXT_GAMESTATE(&globalCtx->state, Daytelop_Init, DaytelopContext);
                this->unk_144 = 1;
                gSaveContext.time = 0x4000;
                Actor_MarkForDeath(&this->actor);
            } else {
                gSaveContext.day = 1;
                pad = gSaveContext.day;
                gSaveContext.daysElapsed = pad;
                this->unk_144 = 1;
                this->unk_146 = gSaveContext.time;
                this->actionFunc = func_80A42AB8;
            }
        } else {
            if (gSaveContext.time == 0x4000) {
                this->unk_144 = 0;
                func_80A41D70(this, globalCtx);
                if (((gSaveContext.cutsceneTrigger) == 0) && (D_80A434D0[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                    player->stateFlags1 |= 0x200;
                }
            } else {
                if ((gSaveContext.time >= 0xC001) || (gSaveContext.time < 0x4000)) {
                    this->unk_144 = 0;
                } else {
                    this->unk_144 = 1;
                }
                this->unk_146 = gSaveContext.time;
                this->actionFunc = func_80A42AB8;
            }
        }
    }

    if (CURRENT_DAY == 3) {
        func_80A42198(this);
    } else {
        func_80A425E4(this, globalCtx);
    }

    this->unk_14A = gSaveContext.time;
    if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/EnTest4_Init.s")
#endif

void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

#ifdef NON_EQUIVALENT
void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx) {
    //static s16 D_80A43364[] = {0x4000, 0xC000, 0, 0, 0, 0};
    Player* player;
    s16 temp_a2;
    s16 new_var2;
    s16 temp_a3;
    s32 temp_v1_3;
    s8 new_var;
    u16 temp_a0;

    player = PLAYER;
    if ((globalCtx->unk_18B4A == 0) && ((func_801690CC(globalCtx) == 0)) && (globalCtx->numSetupActors <= 0) && (globalCtx->roomCtx.unk31 == 0) && (func_8016A168() == 0)) {
        u16 time = gSaveContext.time;

        temp_a2 = time - D_80A43364[this->unk_144];
        temp_a0 = D_80A43364[this->unk_144];
        //temp_a3 = this->unk_146 - D_80A43364[this->unk_144];
        new_var = this->unk_144;
        temp_v1_3 = this->unk_14A - this->unk_148;
        //temp_a3 = this->unk_146 - D_80A43364[new_var];
        new_var2 = D_80A43364[new_var];
        temp_a3 = this->unk_146 - new_var2;
        //temp_v1_3 = this->unk_14A - this->unk_148;
        new_var = time - this->unk_148;
        if (((temp_a2) * (temp_a3)) <= 0) {
            gSaveContext.unk_3CA7 = 1;
            if (globalCtx->actorCtx.unk5 & 0x04) {
                globalCtx->actorCtx.unk5 &= ~0x04;
            }
            goto dummy_label_821378; dummy_label_821378: ;
            //if (D_80A43364[this->unk_144] != 0x4000) {
            //if (D_80A43364[new_var] != 0x4000)
            if (new_var2 != 0x4000)
            {
                func_80A41FA4(this, globalCtx);
            } else {
                if (CURRENT_DAY == 3) {
                    func_8011C808(globalCtx);
                    Actor_MarkForDeath((Actor* ) this);
                    gSaveContext.eventInf[1] |= 0x80;
                } else {
                    if ((((D_80A434D0)[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) && (CURRENT_DAY != 3)) {
                        func_80A41FA4(this, globalCtx);
                    } else {
                        EnHorse *new_var3;

                        gSaveContext.unk_3F64 = 0.0f;
                        func_80169DCC(globalCtx, 0, Entrance_CreateIndexFromSpawn(0), player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                        func_80169EFC(globalCtx);
                        //temp_v1_3 = ((s32*)(player->unk_390))[0x150/4];
                        new_var3 = player->rideActor;
                        if ((player->stateFlags1 & 0x800000) && (((new_var3->unk_150 == 0)) || (new_var3->unk_150 == 2))) {
                            if (CURRENT_DAY < 3)
                            //if (3 > CURRENT_DAY)
                            {
                                D_801BDA9C = 1;
                            } else {
                                D_801BDA9C = 0;
                            }
                        }
                        gSaveContext.respawnFlag = -4;
                        gSaveContext.eventInf[2] |= 0x80;
                        Actor_MarkForDeath((Actor* ) this);
                    }
                }
            }

            if ((D_80A434D0[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                player->stateFlags1 |= 0x200;
                this->unk_146 = gSaveContext.time;
            } else {
                if (this->unk_144 == 0) {
                    this->unk_144 = 1;
                } else {
                    this->unk_144 = 0;
                }

                this->unk_146 = gSaveContext.time += 0x2D;
            }
            return;
        }

        // if (((gSaveContext.time - this->unk_148) * (this->unk_14A - this->unk_148)) <= 0)
        //if (((gSaveContext.time - this->unk_148) * temp_v1_3) <= 0)
        if ((new_var * temp_v1_3) <= 0)
        {
            func_801A0124(&this->actor.projectedPos, (this->actor.params >> 5) & 0xF);
            this->unk_14A = gSaveContext.time;

            if (CURRENT_DAY == 3) {
                if ((this->unk_148 == 0) && ((gSaveContext.inventory.items[ITEM_OCARINA] == ITEM_NONE) || (globalCtx->sceneNum == 0x6F))) {
                    s32 phi_v0;

                    if ((globalCtx->actorCtx.unk5 & 2)) {
                        phi_v0 = 0xCFF;
                    } else {
                        phi_v0 = 0xBFF;
                    }
                    func_80169DCC(globalCtx, 1, gSaveContext.entranceIndex, player->unk_3CE, phi_v0, &player->unk_3C0, player->unk_3CC);

                    if ((globalCtx->sceneNum == 0x29) || (globalCtx->sceneNum == 0x2D)) {
                        globalCtx->nextEntranceIndex = 0x5400;
                    } else {
                        globalCtx->nextEntranceIndex = 0xD800;
                    }
                    gSaveContext.unk_3F4A = 0xFFF1;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 2;
                    player->stateFlags1 |= 0x200;
                    Actor_MarkForDeath((Actor* ) this);
                }
                func_80A42198(this);
            } else {
                func_80A425E4(this, globalCtx);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42AB8.s")
#endif

void func_80A42F20(EnTest4* this, GlobalContext* globalCtx) {
    if (!this->unk_145) {
        if (D_80A434D4 >= 0) {
            if (ActorCutscene_GetCanPlayNext(D_80A434D4) == 0) {
                ActorCutscene_SetIntentToPlay(D_80A434D4);
            } else {
                ActorCutscene_Start(D_80A434D4, &this->actor);
                this->unk_145 = 1;
            }
        } else {
            this->unk_145 = 1;
        }
        return;
    } else if (this->unk_145 < 0x3C) {
        this->unk_145++;
        if (this->unk_145 == 0xA) {
            if (this->unk_144 == 0) {
                play_sound(0x2813);
            } else {
                func_8019F128(0x28AE);
            }
        }
        if (this->unk_145 == 0x3C) {
            Player* player = PLAYER;

            gSaveContext.time += CLOCK_TIME(0, 1);
            this->unk_146 = gSaveContext.time;
            globalCtx->numSetupActors = -globalCtx->numSetupActors;
            player->stateFlags1 &= ~0x200;
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        if (D_80A434D4 >= 0) {
            ActorCutscene_Stop(D_80A434D4);
        }
        gSaveContext.unk_3F22 = 0;
        gSaveContext.eventInf[1] &= (u8)~0x80;
        Interface_ChangeAlpha(50);
    }
}

void func_80A430C8(EnTest4* this, GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 2) && (gSaveContext.time >= CLOCK_TIME(7, 0)) && (gSaveContext.time < CLOCK_TIME(17, 30)) && (globalCtx->envCtx.unk_F2[2] == 0)) {
        D_801BDBB0 = 1;
        func_800FD78C(globalCtx);
        globalCtx->envCtx.unk_E3 = 1;
        globalCtx->envCtx.unk_F2[0] = 0x3C;
    } else {
        if (globalCtx->envCtx.unk_F2[0] != 0) {
            if ((globalCtx->state.frames % 4) == 0) {
                globalCtx->envCtx.unk_F2[0]--;
                if ((globalCtx->envCtx.unk_F2[0]) == 8) {
                    func_800FD858(globalCtx);
                }
            }
        }
    }

    if (D_801BDBB0 == 1) {
        this->unk_14C = 1;
    }
}

void func_80A431C8(EnTest4* this, GlobalContext* globalCtx) {
    if (((gSaveContext.time >= 0xBAAA) && (gSaveContext.time < 0xF555) && (globalCtx->envCtx.unk_F2[0] != 0)) || (globalCtx->envCtx.unk_F2[2] != 0)) {
        D_801BDBB0 = 0;
        globalCtx->envCtx.unk_E3 = 2;
    }
    if (D_801BDBB0 == 0) {
        this->unk_14C = 0;
    }
}

void func_80A4323C(EnTest4* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    temp_v0 = ((s32) this->actor.params >> 0xA) * 0x64;
    if (temp_v0 > 0) {
        D_801F4E7A = (s16) temp_v0;
    }
}

void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTest4* this = THIS;
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 2)) {
        this->actionFunc(this, globalCtx);
        if (func_800FE4B8(globalCtx) != 0) {
            switch (this->unk_14C) {
            case 0:
                func_80A430C8(this, globalCtx);
                break;
            case 1:
                func_80A431C8(this, globalCtx);
                break;
            }
        }
        func_80A4323C(this, globalCtx);
    }
}
