/*
 * File: z_en_test4.c
 * Overlay: ovl_En_Test4
 * Description: 
 */

#include "z_en_test4.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"

#define FLAGS 0x00100030

#define THIS ((EnTest4*)thisx)

void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx);
void func_80A42F20(EnTest4* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern s32 D_80A43340;
extern s16 D_80A434D0;
extern s16 D_801F4E7A;
extern u8 D_801BDBB0;


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A41D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A41FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A425E4.s")

#ifdef MIPS2C_OUTPUT
void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx) {
    Actor* sp24;
    ActorCutscene* temp_v0_2;
    s8 temp_v0;
    u16 temp_v0_3;
    SaveContext* phi_v1;

    temp_v0 = thisx->cutscene;
    D_80A434D0 = (s16) temp_v0;
    if ((s32) temp_v0 >= 0) {
        sp24 = globalCtx->actorCtx.actorList[2].first;
        temp_v0_2 = ActorCutscene_GetCutscene(D_80A434D0);
        gSaveContext.unk_1011 = (u8) (gSaveContext.unk_1011 | 4);
        *(&D_80A434D0 + 2) = (s16) temp_v0_2->additionalCutscene;
    } else {
        gSaveContext.unk_1011 = (u8) (gSaveContext.unk_1011 & 0xFB);
        *(&D_80A434D0 + 2) = (s16) D_80A434D0;
    }
    phi_v1 = &gSaveContext;
    if ((D_80A43340 != 0) || ((gSaveContext.unk_100E & 0x80) != 0)) {
        Actor_MarkForDeath(thisx);
        phi_v1 = &gSaveContext;
    } else {
        D_80A43340 = 1;
        thisx->room = -1;
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
        if (((s32) gSaveContext.day % 5) == 0) {
            if ((s32) gSaveContext.time < 0x402D) {
                gSaveContext.time = 0x4000;
                gSaveContext.gameMode = 0;
                globalCtx->state.running = 0;
                globalCtx->state.nextGameStateInit = Daytelop_Init;
                globalCtx->state.nextGameStateSize = 0x248;
                thisx->unk_144 = (s8) 1;
                gSaveContext.time = 0x4000;
                Actor_MarkForDeath(thisx);
                phi_v1 = &gSaveContext;
            } else {
                gSaveContext.day = 1;
                gSaveContext.daysElapsed = 1;
                thisx->unk_144 = (s8) 1;
                thisx->unk_150 = func_80A42AB8;
                thisx->unk_146 = (u16) gSaveContext.time;
            }
        } else {
            temp_v0_3 = gSaveContext.time;
            if (temp_v0_3 == 0x4000) {
                thisx->unk_144 = 0;
                sp24 = globalCtx->actorCtx.actorList[2].first;
                func_80A41D70(thisx, globalCtx, globalCtx->actorCtx.actorList[2].first);
                phi_v1 = &gSaveContext;
                if ((gSaveContext.cutsceneTrigger == 0) && ((s32) *(&D_80A434D0 + (thisx->unk_144 * 2)) >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                    globalCtx->actorCtx.actorList[2].first->unk_A6C = (s32) (globalCtx->actorCtx.actorList[2].first->unk_A6C | 0x200);
                }
            } else {
                if (((s32) temp_v0_3 >= 0xC001) || ((s32) temp_v0_3 < 0x4000)) {
                    thisx->unk_144 = 0;
                } else {
                    thisx->unk_144 = (s8) 1;
                }
                thisx->unk_150 = func_80A42AB8;
                thisx->unk_146 = (u16) gSaveContext.time;
            }
        }
    }
    if (((s32) phi_v1->day % 5) == 3) {
        func_80A42198(thisx);
    } else {
        func_80A425E4(thisx, globalCtx);
    }
    thisx->unk_14A = (u16) gSaveContext.time;
    if (((s32) *(&D_80A434D0 + (thisx->unk_144 * 2)) < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/EnTest4_Init.s")
#endif

void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42F20.s")

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
