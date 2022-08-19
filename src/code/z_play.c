#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"

s32 gDbgCamEnabled = false;
u8 D_801D0D54 = 0;

// bss
extern s16 D_801F6C10;
extern Input D_801F6C18;
extern FbDemoStruct D_801F6C30;
extern u16* D_801F6D0C;
extern s32 D_801F6D10;
extern VisMono D_801F6D18;
extern Color_RGBA8 D_801F6D30;
extern Struct_80140E80 D_801F6D38;
extern Struct_80140E80* D_801F6D4C;
extern HiresoStruct D_801F6D50;
extern u8 D_801F6DFC;
extern u8 D_801F6DFD;

void func_80165460(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    s32 alpha;
    Gfx* gfx;
    Gfx* dlistHead;

    if (SREG(93) != 0) {
        alpha = SREG(92);

        if (D_801F6DFD == 0) {
            D_801F6DFD = 1;
        }
    } else if (SREG(91) != 0) {
        alpha = SREG(90);

        if (D_801F6DFD == 0) {
            D_801F6DFD = 1;
        }
    } else {
        alpha = 0;
        D_801F6DFD = 0;
    }

    if (D_801F6DFD != 0) {
        OPEN_DISPS(gfxCtx);

        dlistHead = POLY_OPA_DISP;
        gfx = Graph_GfxPlusOne(dlistHead);

        gSPDisplayList(OVERLAY_DISP++, gfx);

        this->pauseBgPreRender.fbuf = gfxCtx->curFrameBuffer;
        this->pauseBgPreRender.fbufSave = this->unk_18E64;

        if (D_801F6DFD == 2) {
            func_80170AE0(&this->pauseBgPreRender, &gfx, alpha);
        } else {
            D_801F6DFD = 2;
        }

        func_801705B4(&this->pauseBgPreRender, &gfx);

        gSPEndDisplayList(gfx++);

        Graph_BranchDlist(dlistHead, gfx);

        POLY_OPA_DISP = gfx;

        CLOSE_DISPS(gfxCtx);
    }
}

void func_80165608(void) {
    SREG(91) = 0;
    SREG(93) = 0;
    D_801F6DFD = 0;
}

void func_80165630(void) {
    SREG(91) = 0;
    SREG(93) = 0;
    D_801F6DFD = 0;
}

void func_80165658(u32 arg0) {
    SREG(90) = arg0;
}

void func_8016566C(u32 arg0) {
    SREG(90) = arg0;
    SREG(91) = 1;
}

void func_80165690(void) {
    SREG(91) = 0;
}

void func_801656A4(u8* arg0, u16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801656A4.s")

void func_80165DB8(s32 arg0) {
    SREG(92) = arg0;
}

void func_80165DCC(s32 arg0) {
    SREG(92) = arg0;
    SREG(93) = 1;
}

void func_80165DF0(void) {
    SREG(93) = 0;
}

void func_80165E04(void) {
    SREG(89) = 1;
}

void func_80165E1C(PreRender* prerender) {
    PreRender_ApplyFilters(prerender);
    func_801656A4(D_80780000, prerender->fbufSave, 0x140, 0x50, 0x40, 0xEF, 0xAF, 8);
}

s32 func_80165E7C(PlayState* this, s32 arg1) {
    s32 phi_v1 = arg1;

    if (arg1 == TRANS_TYPE_20) {
        if (!gSaveContext.save.isNight) {
            phi_v1 = TRANS_TYPE_03;
        } else {
            phi_v1 = TRANS_TYPE_02;
        }
    }
    if (phi_v1 != arg1) {
        this->transitionType = phi_v1;
    }
    return phi_v1;
}

void func_80165EC0(PlayState* this, s32 arg1) {
    PlayStruct_18BF0* ptr = &this->unk_18BF0;
    s32 sp20;

    bzero(ptr, sizeof(this->unk_18BF0));

    sp20 = -1;
    if (arg1 & 0x40) {
        sp20 = 3;
    } else if ((arg1 & 0x78) == 0x20) {
        sp20 = 4;
    } else if (!(arg1 & 0x60)) {
        switch (arg1) {
            case 1:
                sp20 = 1;
                break;
            case 0:
            case 8:
                sp20 = 2;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 13:
            case 17:
            case 18:
            case 19:
                sp20 = 0;
                break;
            case 9:
            case 10:
                this->transitionMode = TRANS_MODE_04;
                break;
            case 11:
                this->transitionMode = TRANS_MODE_10;
                break;
            case 12:
                this->transitionMode = TRANS_MODE_07;
                break;
            case 14:
                this->transitionMode = TRANS_MODE_12;
                break;
            case 15:
                this->transitionMode = TRANS_MODE_14;
                break;
            case 16:
                this->transitionMode = TRANS_MODE_16;
                break;
            case 21:
                sp20 = 5;
                break;
            case 22:
                sp20 = 6;
                break;
            default:
                sp20 = -1;
                __assert("../z_play.c", 1420);
        }
    } else {
        sp20 = -1;
        __assert("../z_play.c", 1423);
    }

    ptr->unk_00 = arg1;
    ptr->unk_02 = sp20;
    if (sp20 != -1) {
        func_80163C90(ptr);
    }
}

const char D_801DFA18[] = "来た!!!!!!!!!!!!!!!!!!!!!";
const char D_801DFA34[] = "all";
const char D_801DFA38[] = "a";
const char D_801DFA3C[] = "a";
const char D_801DFA40[] = "b";
const char D_801DFA44[] = "b";
const char D_801DFA48[] = "c";
const char D_801DFA4C[] = "c";
const char D_801DFA50[] = "d";
const char D_801DFA54[] = "d";
const char D_801DFA58[] = "e";
const char D_801DFA5C[] = "e";
const char D_801DFA60[] = "f";
const char D_801DFA64[] = "fa";
const char D_801DFA68[] = "fa";
const char D_801DFA6C[] = "fb";
const char D_801DFA70[] = "fb";
const char D_801DFA74[] = "fc";
const char D_801DFA78[] = "fc";
const char D_801DFA7C[] = "fd";
const char D_801DFA80[] = "fd";
const char D_801DFA84[] = "fe";
const char D_801DFA88[] = "fe";
const char D_801DFA8C[] = "fg";
const char D_801DFA90[] = "fg";
const char D_801DFA94[] = "fh";
const char D_801DFA98[] = "fh";
const char D_801DFA9C[] = "fi";
const char D_801DFAA0[] = "fi";
const char D_801DFAA4[] = "fj";
const char D_801DFAA8[] = "fj";
const char D_801DFAAC[] = "fk";
const char D_801DFAB0[] = "fk";
const char D_801DFAB4[] = "f";
const char D_801DFAB8[] = "g";
const char D_801DFABC[] = "g";
const char D_801DFAC0[] = "h";
const char D_801DFAC4[] = "h";
const char D_801DFAC8[] = "i";
const char D_801DFACC[] = "i";
const char D_801DFAD0[] = "all";
const char D_801DFAD4[] = "all";
const char D_801DFAD8[] = "a";
const char D_801DFADC[] = "b";
const char D_801DFAE0[] = "c";
const char D_801DFAE4[] = "d";
const char D_801DFAE8[] = "e";
const char D_801DFAEC[] = "f";
const char D_801DFAF0[] = "g";
const char D_801DFAF4[] = "h";
const char D_801DFAF8[] = "i";
const char D_801DFAFC[] = "f";
const char D_801DFB00[] = "fa";
const char D_801DFB04[] = "fb";
const char D_801DFB08[] = "fc";
const char D_801DFB0C[] = "fd";
const char D_801DFB10[] = "fe";
const char D_801DFB14[] = "ff";
const char D_801DFB18[] = "fg";
const char D_801DFB1C[] = "fh";
const char D_801DFB20[] = "fi";
const char D_801DFB24[] = "fj";
const char D_801DFB28[] = "fk";

void func_80166060(PlayState* this) {
    if (this->unk_18BF0.unk_02 != -1) {
        func_80163D80(&this->unk_18BF0, this);
    }
    this->unk_18BF0.unk_00 = -1;
}

Gfx* func_801660B8(PlayState* this, Gfx* gfx) {
    s32 phi_v1 = this->lightCtx.unkC * (5.0f / 64.0f);

    return Gfx_SetFogWithSync(gfx, this->lightCtx.unk7, this->lightCtx.unk8, this->lightCtx.unk9, 0,
                              this->lightCtx.unkA, (phi_v1 <= 1000) ? 1000 : phi_v1);
}

void Play_Destroy(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    if (D_801F6DFC != 0) {
        MsgEvent_SendNullTask();
        func_80178750();
        gfxCtx->curFrameBuffer = SysCfb_GetFbPtr(gfxCtx->framebufferIdx % 2);
        gfxCtx->zbuffer = SysCfb_GetZBuffer();
        gfxCtx->viMode = D_801FBB88;
        gfxCtx->viConfigFeatures = gViConfigFeatures;
        gfxCtx->xScale = gViConfigXScale;
        gfxCtx->yScale = gViConfigYScale;
        gfxCtx->updateViMode = true;
        D_801F6DFC = 0;
    }

    func_8016FC98(&D_801F6D50);
    this->state.gfxCtx->callback = NULL;
    this->state.gfxCtx->callbackParam = 0;
    func_80165630();

    if (SREG(94) != 0) {
        PreRender_ApplyFiltersSlowlyDestroy(&this->pauseBgPreRender);
        SREG(94) = 0;
    }

    SREG(89) = 0;
    PreRender_Destroy(&this->pauseBgPreRender);
    this->unk_18E58 = NULL;
    this->unk_18E5C = NULL;
    this->unk_18E60 = NULL;
    this->unk_18E64 = NULL;
    this->unk_18E68 = NULL;
    Effect_DestroyAll(this);
    EffectSS_Clear(this);
    CollisionCheck_DestroyContext(this, &this->colChkCtx);

    if (D_801F6D10 == 3) {
        func_8016424C(&D_801F6C30);
        D_801F6D10 = 0;
    }

    if ((this->transitionMode == TRANS_MODE_03) || (D_801D0D54 != 0)) {
        this->unk_18BF0.unk_234(&this->unk_18BF0.unk_08);
        func_80166060(this);
        this->transitionMode = TRANS_MODE_OFF;
    }

    ShrinkWindow_Destroy();
    TransitionFade_Destroy(&this->unk_18E48);
    VisMono_Destroy(&D_801F6D18);
    func_80140EA0(D_801F6D4C);
    D_801F6D4C = NULL;

    if (gSaveContext.save.weekEventReg[0x5C] & 0x80) {
        Actor_CleanupContext(&this->actorCtx, this);
    }
    gSaveContext.save.weekEventReg[0x5C] &= (u8)~0x80;

    func_80121F94(this);
    KaleidoScopeCall_Destroy(this);
    KaleidoManager_Destroy();
    ZeldaArena_Cleanup();
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801663C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166644.s")

f32 func_801668B4(PlayState* this, Vec3f* arg1, s32* arg2) {
    Player* player = GET_PLAYER(this);
    f32 sp38 = player->actor.world.pos.y;
    WaterBox* sp34;
    s32 sp30;

    if (!WaterBox_GetSurfaceImpl(this, &this->colCtx, arg1->x, arg1->z, &sp38, &sp34, &sp30)) {
        return BGCHECK_Y_MIN;
    }

    if (sp38 < arg1->y) {
        return BGCHECK_Y_MIN;
    }

    *arg2 = WaterBox_GetLightSettingIndex(&this->colCtx, sp34);
    return sp38;
}

void func_80166968(PlayState* this, Camera* camera) {
    static s16 D_801D0D58 = -1;
    static s16 sIsCameraUnderwater = false;
    s32 pad;
    s32 sp28;
    Player* player = GET_PLAYER(this);

    sIsCameraUnderwater = camera->stateFlags & CAM_STATE_UNDERWATER;
    if (func_801668B4(this, &camera->eye, &sp28) != BGCHECK_Y_MIN) {
        if (!sIsCameraUnderwater) {
            Camera_SetFlags(camera, CAM_STATE_UNDERWATER);
            D_801D0D58 = -1;
            Distortion_SetType(0x10);
            Distortion_SetCountdown(0x50);
        }

        func_801A3EC0(0x20);
        func_800F6834(this, sp28);

        if ((D_801D0D58 == -1) || (Quake_GetCountdown(D_801D0D58) == 0xA)) {
            s16 quake = Quake_Add(camera, 5);

            D_801D0D58 = quake;
            if (quake != 0) {
                Quake_SetSpeed(D_801D0D58, 0x226);
                Quake_SetQuakeValues(D_801D0D58, 1, 1, 0xB4, 0);
                Quake_SetCountdown(D_801D0D58, 1000);
            }
        }
        if (player->stateFlags3 & PLAYER_STATE3_8000) {
            Distortion_SetType(8);
            Distortion_ClearType(4);
        } else {
            Distortion_SetType(4);
            Distortion_ClearType(8);
        }
    } else {
        if (sIsCameraUnderwater) {
            Camera_ClearFlags(camera, CAM_STATE_UNDERWATER);
        }
        Distortion_ClearType(4);
        Distortion_ClearType(0x10);
        Distortion_ClearType(8);
        if (D_801D0D58 != 0) {
            Quake_RemoveFromIdx(D_801D0D58);
        }
        func_800F694C(this);
        func_801A3EC0(0);
    }
}

Input* D_801D0D60 = NULL;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Update.s")

void func_80167DE4(PlayState* play) {
    if (D_801F6DFC == 0) {
        if (play->pauseCtx.unk_1F0 != 0) {
            D_801F6DFC = 1;
            D_801F6D50.unk_00 = 0;
        }
    } else {
        if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_L) ||
            CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_B) ||
            CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_START) || (gIrqMgrResetStatus != 0)) {
            D_801F6DFC = 0;
            play->pauseCtx.unk_1F0 = 0;
            D_801F6D50.unk_00 = 0;
            play->msgCtx.msgLength = 0;
            play->msgCtx.msgMode = 0;
            play->msgCtx.currentTextId = 0;
            play->msgCtx.stateTimer = 0;
            play_sound(NA_SE_SY_CANCEL);
        }
    }
    if (D_801F6DFC != 0) {
        func_8016F5A8(play, &D_801F6D50, play->state.input);
        func_8015680C(play);
    } else {
        Play_Update(play);
    }
}

void func_80167F0C(PlayState* this) {
    Gfx* sp34;
    Gfx* sp30;
    GraphicsContext* gfxCtx;

    if ((this->pauseCtx.state != 0) || (this->pauseCtx.debugEditor != 0)) {
        KaleidoScopeCall_Draw(this);
    }

    if (gSaveContext.gameMode == 0) {
        func_8011F0E0(this);
    }

    if (((this->pauseCtx.state == 0) && (this->pauseCtx.debugEditor == 0)) || (this->msgCtx.currentTextId != 0xFF)) {
        func_80156758(this);
    }

    if (this->gameOverCtx.state != 0) {
        GameOver_FadeLights(this);
    }

    if (gSaveContext.screenScaleFlag != 0) {
        gfxCtx = this->state.gfxCtx;
        D_801F6D4C->scale = gSaveContext.screenScale / 1000.0f;

        OPEN_DISPS(gfxCtx);

        sp30 = POLY_OPA_DISP;
        sp34 = Graph_GfxPlusOne(sp30);
        gSPDisplayList(OVERLAY_DISP++, sp34);

        func_80141778(D_801F6D4C, &sp34, this->unk_18E60, gfxCtx);

        gSPEndDisplayList(sp34++);
        Graph_BranchDlist(sp30, sp34);
        POLY_OPA_DISP = sp34;

        CLOSE_DISPS(gfxCtx);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Draw.s")

void func_80168DAC(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    {
        GraphicsContext* gfxCtx2 = this->state.gfxCtx;

        if (D_801F6DFC != 0) {
            if (D_801FBBD4 != 1) {
                MsgEvent_SendNullTask();
                func_80178818();
                gfxCtx2->curFrameBuffer = SysCfb_GetFbPtr(gfxCtx2->framebufferIdx % 2);
                gfxCtx2->zbuffer = SysCfb_GetZBuffer();
                gfxCtx2->viMode = D_801FBB88;
                gfxCtx2->viConfigFeatures = gViConfigFeatures;
                gfxCtx2->xScale = gViConfigXScale;
                gfxCtx2->yScale = gViConfigYScale;
                gfxCtx2->updateViMode = true;
            }
        } else {
            if (D_801FBBD4 != 0) {
                MsgEvent_SendNullTask();
                func_80178750();
                gfxCtx2->curFrameBuffer = SysCfb_GetFbPtr(gfxCtx2->framebufferIdx % 2);
                gfxCtx2->zbuffer = SysCfb_GetZBuffer();
                gfxCtx2->viMode = D_801FBB88;
                gfxCtx2->viConfigFeatures = gViConfigFeatures;
                gfxCtx2->xScale = gViConfigXScale;
                gfxCtx2->yScale = gViConfigYScale;
                gfxCtx2->updateViMode = true;
            }
        }
    }

    if ((D_801F6DFC != 0) && ((SREG(2) != 2) || (gZBufferPtr == NULL))) {
        func_8016F1A8(&D_801F6D50, gfxCtx);
        func_80156758(this);
    } else {
        Play_Draw(this);
    }
}

void Play_Main(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    D_801D0D60 = &this->state.input[0];

    DebugDisplay_Init();

    {
        GraphicsContext* gfxCtx = this->state.gfxCtx;

        if (1) {
            this->state.gfxCtx = NULL;
        }
        func_80167DE4(this);
        this->state.gfxCtx = gfxCtx;
    }

    {
        Input sp28 = this->state.input[0];

        if (1) {
            this->state.input[0] = D_801F6C18;
        }
        func_80168DAC(this);
        this->state.input[0] = sp28;
    }

    ActorCutscene_Update();
    ActorCutscene_ClearWaiting();
}

s32 Play_InCsMode(PlayState* this) {
    return (this->csCtx.state != 0) || Player_InCsMode(this);
}

f32 func_80169100(PlayState* play, MtxF* mtx, CollisionPoly** poly, s32* bgId, Vec3f* feetPos) {
    f32 floorHeight = BgCheck_EntityRaycastFloor3(&play->colCtx, poly, bgId, feetPos);

    if (floorHeight > BGCHECK_Y_MIN) {
        func_800C0094(*poly, feetPos->x, floorHeight, feetPos->z, mtx);
    } else {
        mtx->xy = 0.0f;
        mtx->zx = 0.0f;
        mtx->yx = 0.0f;
        mtx->xx = 0.0f;
        mtx->wz = 0.0f;
        mtx->xz = 0.0f;
        mtx->wy = 0.0f;
        mtx->wx = 0.0f;
        mtx->zz = 0.0f;
        mtx->yz = 0.0f;
        mtx->zy = 0.0f;
        mtx->yy = 1.0f;
        mtx->xw = feetPos->x;
        mtx->yw = feetPos->y;
        mtx->zw = feetPos->z;
        mtx->ww = 1.0f;
    }
    return floorHeight;
}

void func_801691F0(PlayState* this, MtxF* mtx, Vec3f* feetPos) {
    CollisionPoly* poly;
    s32 bgId;

    func_80169100(this, mtx, &poly, &bgId, feetPos);
}

void* Play_LoadScene(PlayState* this, RomFile* entry) {
    size_t size = entry->vromEnd - entry->vromStart;
    void* sp18 = THA_AllocEndAlign16(&this->state.heap, size);

    DmaMgr_SendRequest0(sp18, entry->vromStart, size);
    return sp18;
}

void func_8016927C(PlayState* this, s16 skyboxId) {
    func_801434E4(&this->state, &this->skyboxCtx, skyboxId);
    Kankyo_Init(this, &this->envCtx, 0);
}

void func_801692C4(PlayState* this, s32 spawn) {
    this->curSpawn = spawn;
    this->linkActorEntry = NULL;
    this->actorCsCamList = NULL;
    this->setupEntranceList = NULL;
    this->setupExitList = NULL;
    this->unk_18868 = NULL;
    this->setupPathList = NULL;
    this->sceneMaterialAnims = NULL;
    this->roomCtx.unk74 = NULL;
    this->numSetupActors = 0;
    Object_InitBank(&this->state, &this->objectCtx);
    LightContext_Init(this, &this->lightCtx);
    Door_InitContext(&this->state, &this->doorCtx);
    Room_Init(this, &this->roomCtx);
    gSaveContext.worldMapArea = 0;
    Scene_ProcessHeader(this, this->sceneSegment);
    func_8016927C(this, this->skyboxId);
}

void Play_SceneInit(PlayState* this, s32 scene, s32 spawn) {
    s32 pad;
    SceneTableEntry* sp1C = &gSceneTable[scene];

    sp1C->unk_D = 0;
    this->loadedScene = sp1C;
    this->sceneNum = scene;
    this->sceneConfig = sp1C->drawConfig;
    this->sceneSegment = Play_LoadScene(this, &sp1C->segment);
    sp1C->unk_D = 0;
    gSegments[0x02] = VIRTUAL_TO_PHYSICAL(this->sceneSegment);
    func_801692C4(this, spawn);
    Room_AllocateAndLoad(this, &this->roomCtx);
}

void Play_GetScreenPos(PlayState* this, Vec3f* worldPos, Vec3f* screenPos) {
    f32 invW;

    // screenPos temporarily stores the projectedPos
    Actor_GetProjectedPos(this, worldPos, screenPos, &invW);

    screenPos->x = (SCREEN_WIDTH / 2) + (screenPos->x * invW * (SCREEN_WIDTH / 2));
    screenPos->y = (SCREEN_HEIGHT / 2) - (screenPos->y * invW * (SCREEN_HEIGHT / 2));
}

s16 Play_CreateSubCamera(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] == NULL) {
            break;
        }
    }

    // if no subCameras available
    if (subCamId == NUM_CAMS) {
        return CAM_ID_NONE;
    }

    this->cameraPtrs[subCamId] = &this->subCameras[subCamId - CAM_ID_SUB_FIRST];
    Camera_Init(this->cameraPtrs[subCamId], &this->view, &this->colCtx, this);
    this->cameraPtrs[subCamId]->camId = subCamId;

    return subCamId;
}

s16 Play_GetActiveCamId(PlayState* this) {
    return this->activeCamId;
}

s32 Play_ChangeCameraStatus(PlayState* this, s16 camId, s16 status) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (status == CAM_STATUS_ACTIVE) {
        this->activeCamId = camIdx;
    }

    return Camera_ChangeStatus(this->cameraPtrs[camIdx], status);
}

void Play_ClearCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (this->cameraPtrs[camIdx] != NULL) {
        Camera_ChangeStatus(this->cameraPtrs[camIdx], CAM_STATUS_INACTIVE);
        this->cameraPtrs[camIdx] = NULL;
    }
}

void Play_ClearAllSubCameras(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] != NULL) {
            Play_ClearCamera(this, subCamId);
        }
    }

    this->activeCamId = CAM_ID_MAIN;
}

Camera* Play_GetCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    return this->cameraPtrs[camIdx];
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEye(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->atActorOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEyeUp(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_UP, up);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->atActorOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return true if the fov was successfully set
 */
s32 Play_SetCameraFov(PlayState* this, s16 camId, f32 fov) {
    s32 successfullySet = Camera_SetViewParam(this->cameraPtrs[camId], CAM_VIEW_FOV, &fov) & 1;

    if (1) {}
    return successfullySet;
}

s32 Play_SetCameraRoll(PlayState* this, s16 camId, s16 roll) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    camera->roll = roll;

    return 1;
}

void Play_CopyCamera(PlayState* this, s16 destCamId, s16 srcCamId) {
    s16 srcCamId2 = (srcCamId == CAM_ID_NONE) ? this->activeCamId : srcCamId;
    s16 destCamId1 = (destCamId == CAM_ID_NONE) ? this->activeCamId : destCamId;

    Camera_Copy(this->cameraPtrs[destCamId1], this->cameraPtrs[srcCamId2]);
}

// Same as Play_ChangeCameraSetting but also calls Camera_InitPlayerSettings
s32 func_80169A50(PlayState* this, s16 camId, Player* player, s16 setting) {
    Camera* camera;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    camera = this->cameraPtrs[camIdx];
    Camera_InitPlayerSettings(camera, player);
    return Camera_ChangeSetting(camera, setting);
}

s32 Play_ChangeCameraSetting(PlayState* this, s16 camId, s16 setting) {
    return Camera_ChangeSetting(Play_GetCamera(this, camId), setting);
}

// Related to bosses and fishing
void func_80169AFC(PlayState* this, s16 camId, s16 timer) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    s16 i;

    Play_ClearCamera(this, camIdx);

    for (i = CAM_ID_SUB_FIRST; i < NUM_CAMS; i++) {
        if (this->cameraPtrs[i] != NULL) {
            Play_ClearCamera(this, i);
        }
    }

    if (timer <= 0) {
        Play_ChangeCameraStatus(this, CAM_ID_MAIN, CAM_STATUS_ACTIVE);
        this->cameraPtrs[CAM_ID_MAIN]->childCamId = this->cameraPtrs[CAM_ID_MAIN]->doorTimer2 = 0;
    }
}

s16 Play_GetCameraUID(PlayState* this, s16 camId) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return camera->uid;
    } else {
        return -1;
    }
}

// Unused in both MM and OoT, purpose is very unclear
s16 func_80169BF8(PlayState* this, s16 camId, s16 uid) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return 0;
    } else if (camera->uid != uid) {
        return 0;
    } else if (camera->status != CAM_STATUS_ACTIVE) {
        return 2;
    } else {
        return 1;
    }
}

u16 Play_GetActorCsCamSetting(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return actorCsCamList->setting;
}

Vec3s* Play_GetActorCsCamFuncData(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return Lib_SegmentedToVirtual(actorCsCamList->actorCsCamFuncData);
}

/**
 * Converts the number of a scene to its "original" equivalent, the default version of the area which the player first
 * enters.
 */
s16 Play_GetOriginalSceneNumber(s16 sceneNum) {
    // Inverted Stone Tower Temple -> Stone Tower Temple
    if (sceneNum == SCENE_INISIE_R) {
        return SCENE_INISIE_N;
    }

    // Purified Southern Swamp -> Poisoned Sothern Swamp
    if (sceneNum == SCENE_20SICHITAI2) {
        return SCENE_20SICHITAI;
    }

    // Spring Mountain Village -> Winter Mountain Village
    if (sceneNum == SCENE_10YUKIYAMANOMURA2) {
        return SCENE_10YUKIYAMANOMURA;
    }

    // Spring Goron Village -> Winter Goron Village
    if (sceneNum == SCENE_11GORONNOSATO2) {
        return SCENE_11GORONNOSATO;
    }

    // Spring Path to Goron Village -> Winter Path to Goron Village
    if (sceneNum == SCENE_17SETUGEN2) {
        return SCENE_17SETUGEN;
    }

    // Inverted Stone Tower -> Stone Tower
    if (sceneNum == SCENE_F41) {
        return SCENE_F40;
    }

    return sceneNum;
}

/**
 * Copies the flags set in ActorContext over to the current scene's CycleSceneFlags, usually using the original scene
 * number. Exception for Inverted Stone Tower Temple, which uses its own.
 */
void Play_SaveCycleSceneFlags(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    CycleSceneFlags* cycleSceneFlags;

    cycleSceneFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneNumber(this->sceneNum)];
    cycleSceneFlags->chest = this->actorCtx.flags.chest;
    cycleSceneFlags->switch0 = this->actorCtx.flags.switches[0];
    cycleSceneFlags->switch1 = this->actorCtx.flags.switches[1];

    if (this->sceneNum == SCENE_INISIE_R) { // Inverted Stone Tower Temple
        cycleSceneFlags = &gSaveContext.cycleSceneFlags[this->sceneNum];
    }

    cycleSceneFlags->collectible = this->actorCtx.flags.collectible[0];
    cycleSceneFlags->clearedRoom = this->actorCtx.flags.clearedRoom;
}

void Play_SetRespawnData(GameState* thisx, s32 respawnMode, u16 entrance, s32 roomIndex, s32 playerParams, Vec3f* pos,
                         s16 yaw) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[respawnMode].entrance = Entrance_Create(entrance >> 9, 0, entrance & 0xF);
    gSaveContext.respawn[respawnMode].roomIndex = roomIndex;
    gSaveContext.respawn[respawnMode].pos = *pos;
    gSaveContext.respawn[respawnMode].yaw = yaw;
    gSaveContext.respawn[respawnMode].playerParams = playerParams;
    gSaveContext.respawn[respawnMode].tempSwitchFlags = this->actorCtx.flags.switches[2];
    gSaveContext.respawn[respawnMode].unk_18 = this->actorCtx.flags.collectible[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = this->actorCtx.flags.collectible[2];
}

void Play_SetupRespawnPoint(GameState* thisx, s32 respawnMode, s32 playerParams) {
    PlayState* this = (PlayState*)thisx;
    Player* player = GET_PLAYER(this);

    if (this->sceneNum != SCENE_KAKUSIANA) { // Grottos
        Play_SetRespawnData(&this->state, respawnMode, (u16)((void)0, gSaveContext.save.entrance),
                            this->roomCtx.currRoom.num, playerParams, &player->actor.world.pos,
                            player->actor.shape.rot.y);
    }
}

// Override respawn data in Sakon's Hideout
void func_80169ECC(PlayState* this) {
    if (this->sceneNum == SCENE_SECOM) {
        this->nextEntrance = ENTRANCE(IKANA_CANYON, 6);
        gSaveContext.respawnFlag = -7;
    }
}

// Gameplay_TriggerVoidOut ?
// Used by Player, Ikana_Rotaryroom, Bji01, Kakasi, LiftNuts, Test4, Warptag, WarpUzu, Roomtimer
void func_80169EFC(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempSwitchFlags = this->actorCtx.flags.switches[2];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].unk_18 = this->actorCtx.flags.collectible[1];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempCollectFlags = this->actorCtx.flags.collectible[2];
    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_02;
}

// Gameplay_LoadToLastEntrance ?
// Used by game_over and Test7
void func_80169F78(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_TOP].entrance;
    gSaveContext.respawnFlag = -1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_02;
}

// Gameplay_TriggerRespawn ?
// Used for void by Wallmaster, Deku Shrine doors. Also used by Player, Kaleido, DoorWarp1
void func_80169FDC(GameState* thisx) {
    func_80169F78(thisx);
}

// Used by Kankyo to determine how to change the lighting, e.g. for game over.
s32 func_80169FFC(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->roomCtx.currRoom.mesh->type0.type != 1;
}

s32 FrameAdvance_IsEnabled(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->frameAdvCtx.enabled != 0;
}

// Unused, unchanged from OoT, which uses it only in one Camera function.
/**
 * @brief Tests if \p actor is a door and the sides are different rooms.
 *
 * @param[in] thisx GameState, promoted to play inside.
 * @param[in] actor Actor to test.
 * @param[out] yaw Facing angle of the actor, or reverse if in the back room.
 * @return true if \p actor is a door and the sides are in different rooms, false otherwise
 */
s32 func_8016A02C(GameState* thisx, Actor* actor, s16* yaw) {
    PlayState* this = (PlayState*)thisx;
    TransitionActorEntry* transitionActor;
    s8 frontRoom;

    if (actor->category != ACTORCAT_DOOR) {
        return false;
    }

    transitionActor = &this->doorCtx.transitionActorList[(u16)actor->params >> 10];
    frontRoom = transitionActor->sides[0].room;
    if (frontRoom == transitionActor->sides[1].room) {
        return false;
    }

    if (frontRoom == actor->room) {
        *yaw = actor->shape.rot.y;
    } else {
        *yaw = actor->shape.rot.y + 0x8000;
    }

    return true;
}

// Unused
/**
 * @brief Tests if \p pos is underwater.
 *
 * @param[in] play PlayState
 * @param[in] pos position to test
 * @return true if inside a waterbox and not above a void.
 */
s32 Play_IsUnderwater(PlayState* this, Vec3f* pos) {
    WaterBox* waterBox;
    CollisionPoly* poly;
    Vec3f waterSurfacePos;
    s32 bgId;

    waterSurfacePos = *pos;

    if ((WaterBox_GetSurface1(this, &this->colCtx, waterSurfacePos.x, waterSurfacePos.z, &waterSurfacePos.y,
                              &waterBox) == true) &&
        (pos->y < waterSurfacePos.y) &&
        (BgCheck_EntityRaycastFloor3(&this->colCtx, &poly, &bgId, &waterSurfacePos) != BGCHECK_Y_MIN)) {
        return true;
    } else {
        return false;
    }
}

s32 Play_IsDebugCamEnabled(void) {
    return gDbgCamEnabled;
}

// A mapping from playerActorCsIds to sGlobalCamDataSettings indices.
s16 D_801D0D64[] = { -3, -2, -4, -5, -7, -11, -8, -9, -6, -16 };

// Used by Player
/**
 * Extract the common actor cutscene ids used by Player from the scene and set the actor cutscene ids in
 * this->playerActorCsIds. If a playerActorCsId is not present in the scene, then that particular id is set
 * to -1. Otherwise, if there is an ActorCutscene where csCamSceneDataId matches the appropriate element of D_801D0D64,
 * set the corresponding playerActorCsId (and possibly change its priority for the zeroth one)
 */
void Play_AssignPlayerActorCsIdsFromScene(GameState* thisx, s32 startActorCsId) {
    PlayState* this = (PlayState*)thisx;
    s32 i;
    s16* curPlayerActorCsId = this->playerActorCsIds;
    s16* phi_s1 = D_801D0D64;

    for (i = 0; i < ARRAY_COUNT(this->playerActorCsIds); i++, curPlayerActorCsId++, phi_s1++) {
        ActorCutscene* actorCutscene;
        s32 curActorCsId;

        *curPlayerActorCsId = -1;

        for (curActorCsId = startActorCsId; curActorCsId != -1; curActorCsId = actorCutscene->additionalCutscene) {
            actorCutscene = ActorCutscene_GetCutscene(curActorCsId);

            if (actorCutscene->csCamSceneDataId == *phi_s1) {
                if ((actorCutscene->csCamSceneDataId == -3) &&
                    (actorCutscene->priority == 700)) { // override ocarina cs priority
                    actorCutscene->priority = 550;
                }
                *curPlayerActorCsId = curActorCsId;
                break;
            }
        }
    }
}

// These regs are used by Gameplay_Draw, and several actors, purpose as yet unclear.
void func_8016A268(GameState* thisx, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    MREG(64) = arg1;
    MREG(65) = arg2;
    MREG(66) = arg3;
    MREG(67) = arg4;
    MREG(68) = arg5;
}

void Play_Init(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    s32 pad;
    s32 temp;
    s32 sp94;
    Player* player;
    s32 spawn;
    s32 i;
    u8 sp87;
    u32 temp_v0_12;
    s32 scene;
    s16 params;

    if ((gSaveContext.respawnFlag == -4) || (gSaveContext.respawnFlag == -0x63)) {
        if (gSaveContext.eventInf[2] & 0x80) {
            gSaveContext.eventInf[2] &= (u8)~0x80;
            this->state.running = false;
            {
                GameState* state = &this->state;

                SET_NEXT_GAMESTATE(state, Daytelop_Init, DaytelopContext);
            }
            return;
        }

        gSaveContext.unk_3CA7 = 1;
        if (gSaveContext.respawnFlag == ~0x62) {
            gSaveContext.respawnFlag = 2;
        }
    } else {
        gSaveContext.unk_3CA7 = 0;
    }

    if (gSaveContext.save.entrance == -1) {
        gSaveContext.save.entrance = 0;
        this->state.running = false;
        {
            GameState* state = &this->state;

            SET_NEXT_GAMESTATE(state, Opening_Init, OpeningContext);
        }
        return;
    }

    if ((gSaveContext.nextCutsceneIndex == 0xFFEF) || (gSaveContext.nextCutsceneIndex == 0xFFF0)) {
        scene = gSaveContext.save.entrance >> 9;
        spawn = (gSaveContext.save.entrance >> 4) & 0x1F;

        if (gSaveContext.save.weekEventReg[33] & 0x80) {
            if (scene == ENTR_SCENE_MOUNTAIN_VILLAGE_WINTER) {
                scene = ENTR_SCENE_MOUNTAIN_VILLAGE_SPRING;
            } else if (scene == ENTR_SCENE_GORON_VILLAGE_WINTER) {
                scene = ENTR_SCENE_GORON_VILLAGE_SPRING;
            } else if (scene == ENTR_SCENE_PATH_TO_GORON_VILLAGE_WINTER) {
                scene = ENTR_SCENE_PATH_TO_GORON_VILLAGE_SPRING;
            } else if ((scene == ENTR_SCENE_SNOWHEAD) || (scene == ENTR_SCENE_PATH_TO_SNOWHEAD) ||
                       (scene == ENTR_SCENE_PATH_TO_MOUNTAIN_VILLAGE) || (scene == ENTR_SCENE_GORON_SHRINE) ||
                       (scene == ENTR_SCENE_GORON_RACETRACK)) {
                gSaveContext.nextCutsceneIndex = 0xFFF0;
            }
        }

        if (gSaveContext.save.weekEventReg[20] & 2) {
            if (scene == ENTR_SCENE_SOUTHERN_SWAMP_POISONED) {
                scene = ENTR_SCENE_SOUTHERN_SWAMP_CLEARED;
            } else if (scene == ENTR_SCENE_WOODFALL) {
                gSaveContext.nextCutsceneIndex = 0xFFF1;
            }
        }

        if ((gSaveContext.save.weekEventReg[52] & 0x20) && (scene == ENTR_SCENE_IKANA_CANYON)) {
            gSaveContext.nextCutsceneIndex = 0xFFF2;
        }

        if ((gSaveContext.save.weekEventReg[55] & 0x80) &&
            ((scene == ENTR_SCENE_GREAT_BAY_COAST) || (scene == ENTR_SCENE_ZORA_CAPE))) {
            gSaveContext.nextCutsceneIndex = 0xFFF0;
        }

        if (INV_CONTENT(ITEM_OCARINA) != ITEM_OCARINA) {
            if ((scene == ENTR_SCENE_TERMINA_FIELD) &&
                (((void)0, gSaveContext.save.entrance) != ENTRANCE(TERMINA_FIELD, 10))) {
                gSaveContext.nextCutsceneIndex = 0xFFF4;
            }
        }
        gSaveContext.save.entrance = Entrance_Create(scene, spawn, ((void)0, gSaveContext.save.entrance) & 0xF);
    }

    GameState_Realloc(&this->state, 0);
    KaleidoManager_Init(this);
    ShrinkWindow_Init();
    View_Init(&this->view, gfxCtx);
    func_801A3EC0(0);
    Quake_Init();
    Distortion_Init(this);

    for (i = 0; i < ARRAY_COUNT(this->cameraPtrs); i++) {
        this->cameraPtrs[i] = NULL;
    }

    Camera_Init(&this->mainCamera, &this->view, &this->colCtx, this);
    Camera_ChangeStatus(&this->mainCamera, CAM_STATUS_ACTIVE);

    for (i = 0; i < ARRAY_COUNT(this->subCameras); i++) {
        Camera_Init(&this->subCameras[i], &this->view, &this->colCtx, this);
        Camera_ChangeStatus(&this->subCameras[i], CAM_STATUS_INACTIVE);
    }

    this->cameraPtrs[CAM_ID_MAIN] = &this->mainCamera;
    this->cameraPtrs[CAM_ID_MAIN]->uid = CAM_ID_MAIN;
    this->activeCamId = CAM_ID_MAIN;

    func_800DFF18(&this->mainCamera, 0x7F);
    Sram_Alloc(&this->state, &this->sramCtx);
    func_801AAAA0(this);
    Message_Init(this);
    GameOver_Init(this);
    SoundSource_InitAll(this);
    EffFootmark_Init(this);
    Effect_Init(this);
    EffectSS_Init(this, 100);
    CollisionCheck_InitContext(this, &this->colChkCtx);
    AnimationContext_Reset(&this->animationCtx);
    Cutscene_Init(this, &this->csCtx);

    if (gSaveContext.nextCutsceneIndex != 0xFFEF) {
        gSaveContext.save.cutscene = gSaveContext.nextCutsceneIndex;
        gSaveContext.nextCutsceneIndex = 0xFFEF;
    }

    if (gSaveContext.save.cutscene == 0xFFFD) {
        gSaveContext.save.cutscene = 0;
    }

    if (gSaveContext.nextDayTime != 0xFFFF) {
        gSaveContext.save.time = gSaveContext.nextDayTime;
        gSaveContext.skyboxTime = gSaveContext.nextDayTime;
    }

    if ((gSaveContext.save.time >= CLOCK_TIME(18, 0)) || (gSaveContext.save.time < CLOCK_TIME(6, 30))) {
        gSaveContext.save.isNight = true;
    } else {
        gSaveContext.save.isNight = false;
    }

    func_800EDDB0(this);

    if (((gSaveContext.gameMode != 0) && (gSaveContext.gameMode != 1)) || (gSaveContext.save.cutscene >= 0xFFF0)) {
        gSaveContext.unk_3DC0 = 0;
        func_80115D5C(&this->state);
        gSaveContext.sceneSetupIndex = (gSaveContext.save.cutscene & 0xF) + 1;
        gSaveContext.save.cutscene = 0;
    } else {
        gSaveContext.sceneSetupIndex = 0;
    }

    sp87 = gSaveContext.sceneSetupIndex;

    //! FAKE: temp. Also introduces a warning.
    Play_SceneInit(
        this,
        Entrance_GetSceneNumAbsolute(((void)0, gSaveContext.save.entrance) +
                                     ((void)0, (temp = gSaveContext.sceneSetupIndex))),
        Entrance_GetSpawnNum(((void)0, gSaveContext.save.entrance) + ((void)0, (temp = gSaveContext.sceneSetupIndex))));
    KaleidoScopeCall_Init(this);
    func_80121FC4(this);

    if (gSaveContext.nextDayTime != 0xFFFF) {
        if (gSaveContext.nextDayTime == 0x8000) {
            gSaveContext.save.day++;
            gSaveContext.save.daysElapsed++;
            gSaveContext.dogIsLost = true;
            gSaveContext.nextDayTime = -2;
        } else {
            gSaveContext.nextDayTime = -3;
        }
    }

    func_80165608();

    SREG(94) = 0;
    SREG(89) = 0;

    PreRender_Init(&this->pauseBgPreRender);
    PreRender_SetValuesSave(&this->pauseBgPreRender, D_801FBBCC, D_801FBBCE, NULL, NULL, NULL);
    PreRender_SetValues(&this->pauseBgPreRender, D_801FBBCC, D_801FBBCE, NULL, NULL);

    this->unk_18E64 = D_801FBB90;
    this->unk_18E5C = D_80780000;
    this->unk_18E68 = D_80784600;
    this->unk_18E58 = D_80784600;
    this->unk_18E60 = D_80784600;
    D_801F6D10 = 0;
    this->transitionMode = TRANS_MODE_OFF;
    D_801D0D54 = 0;

    FrameAdvance_Init(&this->frameAdvCtx);
    Rand_Seed(osGetTime());
    Matrix_Init(&this->state);

    this->state.main = Play_Main;
    this->state.destroy = Play_Destroy;

    this->transitionTrigger = TRANS_TRIGGER_END;
    this->unk_18876 = 0;
    this->bgCoverAlpha = 0;
    this->unk_18845 = 0;
    this->unk_18844 = 0;

    if (gSaveContext.gameMode != 1) {
        if (gSaveContext.nextTransitionType == TRANS_NEXT_TYPE_DEFAULT) {
            this->transitionType =
                (Entrance_GetTransitionFlags(((void)0, gSaveContext.save.entrance) + sp87) >> 7) & 0x7F;
        } else {
            this->transitionType = gSaveContext.nextTransitionType;
            gSaveContext.nextTransitionType = TRANS_NEXT_TYPE_DEFAULT;
        }
    } else {
        this->transitionType = TRANS_TYPE_02;
    }

    TransitionFade_Init(&this->unk_18E48);
    TransitionFade_SetType(&this->unk_18E48, 3);
    TransitionFade_SetColor(&this->unk_18E48, RGBA8(160, 160, 160, 255));
    TransitionFade_Start(&this->unk_18E48);
    VisMono_Init(&D_801F6D18);

    D_801F6D30.a = 0;
    D_801F6D4C = &D_801F6D38;
    func_80140E80(D_801F6D4C);
    D_801F6D4C->lodProportion = 0.0f;
    D_801F6D4C->mode = 1;
    D_801F6D4C->primColor.r = 0;
    D_801F6D4C->primColor.g = 0;
    D_801F6D4C->primColor.b = 0;
    D_801F6D4C->primColor.a = 0;
    D_801F6D4C->envColor.r = 0;
    D_801F6D4C->envColor.g = 0;
    D_801F6D4C->envColor.b = 0;
    D_801F6D4C->envColor.a = 0;
    EnvFlags_UnsetAll(this);
    THA_GetSize(&this->state.heap);
    sp94 = THA_GetSize(&this->state.heap);
    temp_v0_12 = (u32)THA_AllocEndAlign16(&this->state.heap, sp94);
    ZeldaArena_Init(((temp_v0_12 + 8) & ~0xF), (sp94 - ((temp_v0_12 + 8) & ~0xF)) + temp_v0_12);
    Actor_InitContext(this, &this->actorCtx, this->linkActorEntry);

    while (Room_HandleLoadCallbacks(this, &this->roomCtx) == 0) {}

    if ((CURRENT_DAY != 0) && ((this->roomCtx.currRoom.unk3 == 1) || (this->roomCtx.currRoom.unk3 == 5))) {
        Actor_Spawn(&this->actorCtx, this, 0x15A, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0);
    }

    player = GET_PLAYER(this);

    Camera_InitPlayerSettings(&this->mainCamera, player);
    gDbgCamEnabled = false;

    if ((player->actor.params & 0xFF) != 0xFF) {
        Camera_ChangeDataIdx(&this->mainCamera, player->actor.params & 0xFF);
    }

    func_800F15D8(&this->mainCamera);
    func_801129E4(this);
    func_800FB758(this);
    gSaveContext.seqIndex = this->soundCtx.seqIndex;
    gSaveContext.nightSeqIndex = this->soundCtx.nightSeqIndex;
    AnimationContext_Update(this, &this->animationCtx);
    func_800EDBE0(this);
    gSaveContext.respawnFlag = 0;
    D_801F6DFC = 0;
    func_8016FC78(&D_801F6D50);
}

// play_hireso need to confirm still
u16 D_801D0D78[] = { 0, 0, 0, 0 };
