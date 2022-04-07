/*
 * File: z_dm_char08.c
 * Overlay: ovl_Dm_Char08
 * Description: Large Great Bay Turtle
 */

#include "z_dm_char08.h"
#include "objects/object_kamejima/object_kamejima.h"

#define FLAGS (ACTOR_FLAG_2000000)

#define THIS ((DmChar08*)thisx)

void DmChar08_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AAFAC4(DmChar08* this, GlobalContext* globalCtx);
void func_80AAF610(DmChar08* this, GlobalContext* globalCtx);
void func_80AAF8F4(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFAE4(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFE78(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFA18(DmChar08* this, GlobalContext* globalCtx);
void func_80AAF79C(DmChar08* this, GlobalContext* globalCtx);
void func_80AAF884(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFB04(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFB94(DmChar08* this, GlobalContext* globalCtx);
void func_80AAF050(DmChar08* this);
void func_80AAFE88(DmChar08* this, GlobalContext* globalCtx);
void func_80AB023C(DmChar08* this, GlobalContext* globalCtx);
void func_80AB032C(DmChar08* this, GlobalContext* globalCtx);
void func_80AB01E8(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFBA4(DmChar08* this, GlobalContext* globalCtx);
void func_80AAFCCC(DmChar08* this, GlobalContext* globalCtx);
void func_80AB096C(DmChar08* this, GlobalContext* globalCtx);
void func_80AB0A10(DmChar08* this, GlobalContext* globalCtx);

typedef struct struct_80AB16BC {
    /* 0x00 */ AnimationHeader* animation;
    /* 0x04 */ f32 playSpeed;
    /* 0x08 */ f32 startFrame;
    /* 0x0C */ f32 endFrame;
    /* 0x10 */ u8 animMode;
    /* 0x14 */ f32 morphFrames;
} struct_80AB16BC; // Size = 0x18

void func_80AAF15C(SkelAnime* skelAnime, struct_80AB16BC* entry, u16 arg2);

const ActorInit Dm_Char08_InitVars = {
    ACTOR_DM_CHAR08,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAMEJIMA,
    sizeof(DmChar08),
    (ActorFunc)DmChar08_Init,
    (ActorFunc)DmChar08_Destroy,
    (ActorFunc)DmChar08_Update,
    (ActorFunc)DmChar08_Draw,
};

#include "overlays/ovl_Dm_Char08/ovl_Dm_Char08.c"


struct_80AB16BC D_80AB16BC[7] = {
    { &object_kamejima_Anim_0048B0, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_006980, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_012260, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_0100CC, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_0047B8, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_0119D4, 1.0f, 0.0f, -1.0f, 0, -24.0f },
    { &object_kamejima_Anim_014E8C, 1.0f, 0.0f, -1.0f, 0, -24.0f },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AB1764[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};


s16 D_80AB1770 = 0;
Color_RGBA8 D_80AB1774 = { 0xFA, 0xC8, 0xFA, 0x64 };
Color_RGBA8 D_80AB1778 = { 0x50, 0x50, 0x50, 0 };
Vec3f D_80AB177C = { 0.0f, -0.8f, 0.0f };
void *D_80AB1788[9] = {
    (void *)0x0600D2D8,
    (void *)0x0600CAD8,
    (void *)0x0600C6D8,
    (void *)0x0600CAD8,
    (void *)0x0600BED8,
    (void *)0x0600C2D8,
    (void *)0x0600C6D8,
    (void *)0x0600C2D8,
    (void *)0x0600CED8,
};

// Overly complicated eye update function?
void func_80AAF050(DmChar08* this) {
    switch (this->unk200) {
        case 0:
            this->unk201 = 0;
            if (this->unk1F8 > 0) {
                this->unk1F8 = this->unk1F8 - 1;
            } else {
                this->unk1F8 = 0;
            }
            if (this->unk1F8 < 4) {
                this->unk201 = this->unk1F8;
            }
            if (this->unk1F8 == 0) {
                this->unk1F8 = Rand_S16Offset(0x1E, 0x1E);
                return;
            }
        default:
            return;
        case 1:
            this->unk201 = 4;
            if (this->unk1F8 > 0) {
                this->unk1F8 = this->unk1F8 - 1;
            } else {
                this->unk1F8 = 0;
            }
            if (this->unk1F8 < 4) {
                this->unk201 = this->unk1F8 + 4;
            }
            if (this->unk1F8 == 0) {
                this->unk1F8 = Rand_S16Offset(0x1E, 0x1E);
                return;
            }
            break;
        case 2:
            this->unk201 = 2;
            return;
        case 3:
            this->unk201 = 4;
            return;
        case 5:
            this->unk201 = 8;
            break;
    }
}

void func_80AAF15C(SkelAnime* skelAnime, struct_80AB16BC* entry, u16 arg2) {
    f32 endFrame;

    entry += arg2;
    if (entry->endFrame < 0.0f) {
        endFrame = Animation_GetLastFrame(entry->animation);
    } else {
        endFrame = entry->endFrame;
    }
    Animation_Change(skelAnime, entry->animation, entry->playSpeed, entry->startFrame, endFrame, entry->animMode,
                     entry->morphFrames);
}

void DmChar08_Init(Actor* thisx, GlobalContext* globalCtx2) {
    DmChar08* this = (DmChar08*)thisx;
    GlobalContext* globalCtx = globalCtx2;

    this->dyna.actor.targetMode = 5;
    this->unk200 = 2;
    this->dyna.actor.targetArrowOffset = 120.0f;
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_kamejima_Skel_00E748, NULL, NULL, NULL, 0);
    Actor_ProcessInitChain(&this->dyna.actor, D_80AB1764);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    this->unk1F4 = 0;
    this->unk1FE = 0;
    this->unk1FF = 0;
    this->unk205 = 0;
    this->unk202 = 0;
    this->unk1FC = 0xFFFF;
    this->unk209 = 0;
    this->unk1E4 = this->dyna.actor.world.pos.y;
    this->unk1F0 = 0.0f;
    if (globalCtx->sceneNum == SCENE_31MISAKI) {
        if ((gSaveContext.save.weekEventReg[0x35] & 0x20) != 0) {
            DynaPolyActor_Init(&this->dyna, 3);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kamejima_Colheader_002470);
        } else {
            DynaPolyActor_Init(&this->dyna, 3);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kamejima_Colheader_002328);
        }
        this->unk209 = 1;
    } else if (globalCtx->sceneNum == SCENE_SEA) {
        DynaPolyActor_Init(&this->dyna, 3);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_80AB1690);
        this->unk209 = 1;
        if (&this->dyna.actor.world) {}
    }

    this->unk1A4 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_YASI, this->dyna.actor.world.pos.x + -80.0f,
                               this->dyna.actor.world.pos.y + 390.0f, this->dyna.actor.world.pos.z, 0, 0, 0, 1);
    this->unk1A8 =
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_YASI, this->dyna.actor.world.pos.x + 68.0f,
                    this->dyna.actor.world.pos.y + 368.0f, this->dyna.actor.world.pos.z - 174.0f, 0, 0x7530, 0, 1);
    switch (globalCtx->sceneNum) {
        case SCENE_31MISAKI:
            if ((gSaveContext.save.weekEventReg[0x35] & 0x20)) {
                this->dyna.actor.world.pos.x = -6480.0f;
                this->unk1E4 = -120.0f;
                this->dyna.actor.world.pos.z = 1750.0f;
                this->dyna.actor.world.rot.x = 0;
                this->dyna.actor.world.rot.y = -0x7234;
                this->dyna.actor.world.rot.z = 0;
                this->dyna.actor.shape.rot.x = 0;
                this->dyna.actor.shape.rot.y = -0x7234;
                this->dyna.actor.shape.rot.z = 0;
                this->unk1F0 = 1.0f;
                this->unk1FF = 2;
                this->unk202 = 2;
                this->unk203 = 0x63;
                this->unk200 = 1;
                this->unk207 = 0;
                this->unk208 = 0;
                this->dyna.actor.flags |= 1;
                if (gSaveContext.save.entranceIndex == 0x6A80) {
                    this->unk200 = 0;
                    this->actionFunc = func_80AAFAC4;
                } else {
                    this->actionFunc = func_80AAF8F4;
                }
            } else {
                this->actionFunc = func_80AAF610;
            }
            break;
        case SCENE_SEA:
            this->unk1FF = 2;
            this->unk202 = 2;
            this->unk203 = 0x63;
            this->unk200 = 0;
            this->unk207 = 0;
            this->unk208 = 0;
            this->dyna.actor.flags |= 1;
            this->actionFunc = func_80AAFAE4;
            this->unk1F0 = 1.0f;
            break;
        case SCENE_KONPEKI_ENT:
            this->unk1FF = 2;
            this->unk202 = 2;
            this->unk203 = 0x63;
            this->unk200 = 0;
            this->unk207 = 0;
            this->unk208 = 0;
            this->actionFunc = func_80AAFE78;
            this->unk1F0 = 1.0f;
            break;
    }
    func_80AAF15C(&this->skelAnime, &D_80AB16BC[this->unk202], 0);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/DmChar08_Destroy.s")

void func_80AAF610(DmChar08* this, GlobalContext* globalCtx) {
    Player* player;
    Player* player2;

    player = GET_PLAYER(globalCtx);
    player2 = GET_PLAYER(globalCtx);
    if ((player2->stateFlags2 & 0x8000000) &&
        ((player2->actor.world.pos.x > -5780.0f) && (player2->actor.world.pos.x < -5385.0f) &&
         (player2->actor.world.pos.z > 1120.0f) && (player2->actor.world.pos.z < 2100.0f))) {
        if (D_80AB1770 == 0) {
            play_sound(0x4807U);
            D_80AB1770 = 1;
        }
    } else {
        D_80AB1770 = 0;
    }
    if ((player->transformation == PLAYER_FORM_ZORA) && (globalCtx->msgCtx.ocarinaMode == 3) &&
        (globalCtx->msgCtx.unk1202E == 2)) {
        if ((player2->actor.world.pos.x > -5780.0f) && (player2->actor.world.pos.x < -5385.0f)) {
            if ((player2->actor.world.pos.z > 1120.0f) && (player2->actor.world.pos.z < 2100.0f)) {
                this->actionFunc = func_80AAF79C;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF79C.s")

// void func_80AAF79C(DmChar08 *this, GlobalContext *globalCtx) {
//     s8 temp_s0;
//     s16 phi_s0;
//
//    // temp_s0 = this->dyna.actor.cutscene;
//     //phi_s0 = this->dyna.actor.cutscene;
//     //if (((void)0, gSaveContext.save.weekEventReg[0x5D] & 0x8)) {
//     //    phi_s0 =
//     ActorCutscene_GetAdditionalCutscene(ActorCutscene_GetAdditionalCutscene(ActorCutscene_GetAdditionalCutscene(phi_s0)));
//     //}
//     phi_s0 = (((void)0, gSaveContext.save.weekEventReg[0x5D] & 0x8)) ?
//     ActorCutscene_GetAdditionalCutscene(ActorCutscene_GetAdditionalCutscene(ActorCutscene_GetAdditionalCutscene(phi_s0)))
//     : this->dyna.actor.cutscene; if (ActorCutscene_GetCanPlayNext(phi_s0) != 0) {
//         ActorCutscene_Start(phi_s0, &this->dyna.actor);
//         gSaveContext.save.weekEventReg[0x35] |= 0x20;
//         gSaveContext.save.weekEventReg[0x5D] |= 8;
//         DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
//         this->actionFunc = func_80AAF884;
//         return;
//     }
//     ActorCutscene_SetIntentToPlay(phi_s0);
// }

void func_80AAF884(DmChar08* this, GlobalContext* globalCtx) {

    if (globalCtx->csCtx.state == 0) {
        DynaPolyActor_Init(&this->dyna, 3);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kamejima_Colheader_002470);
        this->dyna.actor.flags |= 1;
        this->actionFunc = func_80AAF8F4;
    }
}

void func_80AAF8F4(DmChar08* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 sp28;

    if (fabsf(this->dyna.actor.xzDistToPlayer) < 200.0f) {
        this->actionFunc = func_80AAFA18;
    }
    this->unk1FA += 0xC8;
    sp28 = 50.0f;
    sp28 *= Math_SinS(this->unk1FA);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.x, -6400.0f, 0.2f, 2.0f, 0.1f);
    Math_SmoothStepToF(&this->unk1E4, -180.0f + sp28, 0.5f, 5.0f, 0.1f);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.z, 1750.0f, 0.5f, 20.0f, 0.1f);
    Math_SmoothStepToS(&this->dyna.actor.world.rot.y, -0x7234, 0xA, 0xDC, 1);
    Math_SmoothStepToS(&this->dyna.actor.shape.rot.y, -0x7234, 0xA, 0xDC, 1);
}

void func_80AAFA18(DmChar08* this, GlobalContext* globalCtx) {
    s16 nextCs;
    s16 nextCs2;
    s16 nextCs1;

    nextCs1 = ActorCutscene_GetAdditionalCutscene(this->dyna.actor.cutscene);
    nextCs2 = nextCs1;
    nextCs1 = ActorCutscene_GetAdditionalCutscene(nextCs1);

    nextCs = ((void)0, gSaveContext.save.weekEventReg[53] & 0x40) ? nextCs1 : nextCs2;

    if (ActorCutscene_GetCanPlayNext(nextCs) != 0) {
        gSaveContext.save.weekEventReg[53] |= 0x40;
        ActorCutscene_Start(nextCs, &this->dyna.actor);
        this->actionFunc = func_80AAFE78;
    } else {
        ActorCutscene_SetIntentToPlay(nextCs);
    }
}

void func_80AAFAC4(DmChar08* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->actionFunc = func_80AAF8F4;
    }
}

void func_80AAFAE4(DmChar08* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->actionFunc = func_80AAFB04;
    }
}

void func_80AAFB04(DmChar08* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((fabsf(this->dyna.actor.xzDistToPlayer) < 200.0f) && (player->actor.world.pos.y > 0.0f)) {
        globalCtx->nextEntranceIndex = 0x6A70;
        globalCtx->sceneLoadFlag = 0x14;
        Scene_SetExitFade(globalCtx);
        this->actionFunc = func_80AAFB94;
    }
}

void func_80AAFB94(DmChar08* this, GlobalContext* globalCtx) {
}

void func_80AAFBA4(DmChar08* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f velocity;

    velocity.x = (Rand_ZeroOne() - 0.5f) * 24.0f;
    velocity.y = -5.2f;
    velocity.z = 4.0f;
    D_80AB177C.x = 0.0f;
    D_80AB177C.y = 1.18f;
    D_80AB177C.z = 0.0f;
    for (i = 0; i < this->unk1FE; i++) {
        EffectSsDtBubble_SpawnCustomColor(globalCtx, &this->unk1C4, &velocity, &D_80AB177C, &D_80AB1774, &D_80AB1778,
                                          Rand_S16Offset(80, 130), 30, 0);
    }
}

void func_80AAFCCC(DmChar08* this, GlobalContext* globalCtx) {
    switch (globalCtx->sceneNum) {
        case SCENE_31MISAKI:
            if (!(gSaveContext.save.weekEventReg[0x37] & 0x80)) {
                switch (this->pad206) {
                    case 0:
                        return; // Must be a return
                    case 1:
                        Message_StartTextbox(globalCtx, 0x102A, &this->dyna.actor);
                        this->pad206++;
                        break;
                        ;
                    case 2:
                        if (Message_GetState(&globalCtx->msgCtx) == 2) {
                            Message_StartTextbox(globalCtx, 0x102B, &this->dyna.actor);
                            this->pad206 = 0;
                        }
                        break;
                }
            } else {
                switch (this->pad206) {
                    case 0:
                        break;
                    case 1:
                        Message_StartTextbox(globalCtx, 0x103B, &this->dyna.actor);
                        this->pad206++;
                        break;
                    case 2:
                        if (Message_GetState(&globalCtx->msgCtx) == 2) {
                            func_801477B4(globalCtx);
                            this->pad206 = 0;
                        }
                        break;
                }
            }
            break;
        case SCENE_SEA:
            switch (this->pad206) {
                case 0:
                    break;
                case 1:
                    Message_StartTextbox(globalCtx, 0x102E, &this->dyna.actor);
                    this->pad206++;
                    break;
                    ;
                case 2:
                    if (Message_GetState(&globalCtx->msgCtx) == 2) {
                        Message_StartTextbox(globalCtx, 0x102F, &this->dyna.actor);
                        this->pad206 = 0;
                    }
                    break;
            }
            break;
    }
}

void func_80AAFE78(DmChar08* this, GlobalContext* globalCtx) {
}

void func_80AAFE88(DmChar08* this, GlobalContext* globalCtx) {
    s32 actorActionIndex;
    CsCmdActorAction* csAction;
    f32 phi_f12;

    if (Cutscene_CheckActorAction(globalCtx, 0x1DAU) != 0) {
        actorActionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x1DA);
        if (this->unk1F6 != globalCtx->csCtx.actorActions[actorActionIndex]->action) {
            this->unk1F6 = globalCtx->csCtx.actorActions[actorActionIndex]->action;
            switch (globalCtx->csCtx.actorActions[actorActionIndex]->action) {
                case 1:
                    this->unk202 = 0;
                    break;
                case 3:
                    this->unk1FE = 2;
                    break;
                case 4:
                    this->unk202 = 2;
                    break;
                case 5:
                    this->unk202 = 1;
                    break;
                case 6:
                    this->unk200 = 0;
                    break;
                case 7:
                    this->unk200 = 2;
                    break;
                case 8:
                    this->unk202 = 6;
                    break;
                case 9:
                    this->unk202 = 2;
                    break;
                case 10:
                    this->unk202 = 4;
                    break;
                case 12:
                    this->unk202 = 5;
                    break;
                case 13:
                    this->unk1FE = 0;
                    break;
                case 14:
                    Actor_PlaySfxAtPos(&this->dyna.actor, 0x28DE);
                    this->unk202 = 2;
                    break;
            }
        }
        switch (globalCtx->csCtx.actorActions[actorActionIndex]->action) { /* switch 1; irregular */
            case 2:                                                        /* switch 1 */
                this->unk1FF = 1;
                phi_f12 = 2.0f * Environment_LerpWeight(globalCtx->csCtx.actorActions[actorActionIndex]->endFrame,
                                                        globalCtx->csCtx.actorActions[actorActionIndex]->startFrame,
                                                        globalCtx->csCtx.frames);
                if (phi_f12 > 1.0f) {
                    phi_f12 = 1.0f;
                }

                this->unk205 = (1.0f - phi_f12) * 255.0f;
                if (this->unk205 < 6) {
                    this->unk1FF = 2;
                }

                Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, actorActionIndex);
                break;
            case 5: /* switch 1 */
                Cutscene_ActorTranslateAndYawSmooth(&this->dyna.actor, globalCtx, actorActionIndex);
                break;
            case 14: /* switch 1 */
                Cutscene_ActorTranslate(&this->dyna.actor, globalCtx, actorActionIndex);
                Math_SmoothStepToS(&this->dyna.actor.world.rot.y,
                                   globalCtx->csCtx.actorActions[actorActionIndex]->rot.y, 0xA, 0xDC, (s16)1);
                this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
                break;
            default: /* switch 1 */
                Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, actorActionIndex);
                break;
        }
        this->unk1E4 = this->dyna.actor.world.pos.y;
        if ((this->unk1FF >= 2) || (globalCtx->csCtx.actorActions[actorActionIndex]->action == 2)) {
            Math_SmoothStepToF(&this->unk1F0, 1.0f, 0.02f, 0.1f, 0.00001f);
        }
    } else {
        this->unk1F6 = 0x63;
    }
}

void func_80AB01E8(DmChar08* this, GlobalContext* globalCtx) {
    if (this->unk202 != this->unk203) {
        this->unk203 = this->unk202;
        func_80AAF15C(&this->skelAnime, &D_80AB16BC[this->unk202], 0);
    }
}

void func_80AB023C(DmChar08* this, GlobalContext* globalCtx) {
    if ((globalCtx->msgCtx.currentTextId != this->unk1FC) && (globalCtx->msgCtx.currentTextId != 0)) {
        this->unk1FC = globalCtx->msgCtx.currentTextId;
        this->unk208 = 0;
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x1025:
                this->unk207 = 1;
                return;
            case 0x1026:
                this->unk207 = 2;
                return;
            case 0x1027:
                this->unk207 = 3;
                return;
            case 0x1028:
                this->unk207 = 4;
                return;
            case 0x1029:
                this->unk207 = 0xA;
                return;
            case 0x102C:
                this->unk207 = 5;
                return;
            case 0x102D:
                this->unk207 = 8;
                return;
            case 0x102A:
                this->unk207 = 6;
                return;
            case 0x102B:
                this->unk207 = 2;
                return;
            case 0x102E:
                this->unk207 = 9;
                return;
            case 0x102F:
                this->unk207 = 7;
                return;
            case 0x103B:
                this->unk207 = 6;
                return;
            case 0x1030:
                this->unk207 = 4;
                break;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB032C.s")
void func_80AB032C(DmChar08* this, GlobalContext* globalCtx) {
    switch (this->unk207) {         /* switch 1 */
        case 1:                     /* switch 1 */
            switch (this->unk208) { /* switch 5; irregular */
                case 0:             /* switch 5 */
                    this->unk202 = 6;
                    this->unk200 = 2;
                    this->unk208 = this->unk208 + 1;
                    break;
                case 1: /* switch 5 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 2:                     /* switch 1 */
            switch (this->unk208) { /* switch 6; */
                case 0:             /* switch 6 */
                    this->unk202 = 4;
                    this->unk200 = 2;
                    this->unk208 = this->unk208 + 1;
                    break;
                    ;
                case 1: /* switch 6 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 3;
                        this->unk200 = 0;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 2: /* switch 6 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 3:                     /* switch 1 */
        case 4:                     /* switch 1 */
        case 8:                     /* switch 1 */
            switch (this->unk208) { /* switch 2 */
                case 0:             /* switch 2 */
                    this->unk202 = 3;
                    if (this->unk207 >= 5) {
                        this->unk200 = 2;
                    } else {
                        this->unk200 = 0;
                    }
                    this->unk208 = 2;
                    break;
                case 2: /* switch 2 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 5;
                        this->unk200 = 2;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 3: /* switch 2 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        if (this->unk207 != 4) {
                            this->unk202 = 2;
                            this->unk200 = 0;
                            this->unk207 = 0;
                            this->unk208 = 0;
                            break;
                            ;
                        }
                        this->unk202 = 3;
                        this->unk200 = 0;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 4: /* switch 2 */
                case 5: /* switch 2 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 6: /* switch 2 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 5:                     /* switch 1 */
            switch (this->unk208) { /* switch 3 */
                case 0:             /* switch 3 */
                    this->unk202 = 3;
                    this->unk200 = 0;
                    this->unk208 = this->unk208 + 1;
                    break;
                    ;
                case 2: /* switch 3 */
                case 3: /* switch 3 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 4: /* switch 3 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 5;
                        this->unk200 = 2;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 5: /* switch 3 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 6:                     /* switch 1 */
            switch (this->unk208) { /* switch 7 */
                case 0:             /* switch 7 */
                    this->unk202 = 3;
                    this->unk200 = 5;
                    this->unk208 = this->unk208 + 1;
                    return;
                case 1: /* switch 7 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 2: /* switch 7 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 7:                     /* switch 1 */
            switch (this->unk208) { /* switch 8 */
                case 0:             /* switch 8 */
                    this->unk202 = 5;
                    this->unk200 = 2;
                    this->unk208 = this->unk208 + 1;
                    return;
                case 1: /* switch 8 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 3;
                        this->unk200 = 2;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 2: /* switch 8 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 9:                     /* switch 1 */
            switch (this->unk208) { /* switch 4 */
                case 0:             /* switch 4 */
                    this->unk202 = 3;
                    this->unk200 = 0;
                    this->unk208 = this->unk208 + 1;
                    return;
                case 1: /* switch 4 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk208 = this->unk208 + 1;
                    }
                    if ((Message_GetState(&globalCtx->msgCtx) == 6) && (Message_ShouldAdvance(globalCtx) != 0)) {
                        this->unk208 = 3;
                    }
                    break;
                case 2: /* switch 4 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk208 = this->unk208 + 1;
                    }
                    if ((Message_GetState(&globalCtx->msgCtx) == 6) && (Message_ShouldAdvance(globalCtx) != 0)) {
                        this->unk208 = 3;
                    }
                    break;
                case 3: /* switch 4 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 4;
                        this->unk200 = 2;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 4: /* switch 4 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
        case 10:                    /* switch 1 */
            switch (this->unk208) { /* switch 9 */
                case 0:             /* switch 9 */
                    this->unk202 = 3;
                    this->unk200 = 0;
                    this->unk208 = this->unk208 + 1;
                    break;
                case 1: /* switch 9 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 5;
                        this->unk200 = 2;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 2: /* switch 9 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 3;
                        this->unk200 = 0;
                        this->unk208 = this->unk208 + 1;
                    }
                    break;
                case 3: /* switch 9 */
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
                        this->unk202 = 2;
                        this->unk200 = 0;
                        this->unk207 = 0;
                        this->unk208 = 0;
                    }
                    break;
            }
            break;
    }
}

void func_80AB096C(DmChar08* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (globalCtx->sceneNum == SCENE_31MISAKI) &&
        (gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.currentCsIndex == 0)) {
        if ((globalCtx->csCtx.frames >= 890) && (globalCtx->csCtx.frames < 922)) {
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_EARTHQUAKE_LAST2 - SFX_FLAG);
        }
    }
    if ((this->unk202 == 1) && Animation_OnFrame(&this->skelAnime, 16.0f)) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BIG_TORTOISE_SWIM);
    }
}



// not today
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0A10.s")
void func_80AB0A10(DmChar08* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f0;
    f32 phi_f2;
    f32 phi_f0;
    f32 phi_f12;
    s32 i;

    if (player->actor.world.pos.x > 0.0f) {
        temp_f0 = this->skelAnime.curFrame;
        if (temp_f0 <= 19.0f) {
            phi_f12 = 19.0f;
            phi_f2 = temp_f0 / 19.0f;
        } else {
            phi_f2 = (29.0f - temp_f0) / 9.0f;
            phi_f12 = 29.0f;
        }

        D_80AB1690.polyList = D_80AB1690Polygons;

        for (i = 0; i < ARRAY_COUNT(D_80AB1690Vertices); i++) {
            D_80AB1690Vertices[i].x = D_80AB1648[i].x;
        }

        D_80AB1690Vertices[0].y = (100.0f * phi_f2) + 900.0f;
        D_80AB1690Vertices[1].y = (100.0f * phi_f2) + 900.0f;
        D_80AB1690Vertices[2].y = (500.0f * phi_f2) + -200.0f;
        D_80AB1690Vertices[3].y = (900.0f * phi_f2) + -800.0f;
        D_80AB1690Vertices[5].y = 0x4B0;
        D_80AB1690Vertices[9].y = 0x6A4;
    } else {
        phi_f0 = this->skelAnime.curFrame + 26.0f;
        if (phi_f0 > 29.0f) {
            phi_f12 = 29.0f;
            phi_f0 -= 29.0f;
        }

        if (phi_f0 <= 18.0f) {
            phi_f2 = phi_f0 / 18.0f;
        } else {
            phi_f2 = (29.0f - phi_f0) / 10.0f;
        }

        D_80AB1690.polyList = D_80AB14D0;

        for (i = 0; i < ARRAY_COUNT(D_80AB1690Vertices); i++) {
            D_80AB1690Vertices[i].x = -D_80AB1648[i].x;
        }

        D_80AB1690Vertices[0].y = (500.0f * phi_f2) + 720.0f;
        D_80AB1690Vertices[1].y = (660.0f * phi_f2) + 420.0f;
        D_80AB1690Vertices[2].y = (1130.0f * phi_f2) + -430.0f;
        D_80AB1690Vertices[3].y = (1430.0f * phi_f2) + -1060.0f;
        D_80AB1690Vertices[5].y = 0x4B0;
        D_80AB1690Vertices[9].y = 0x6A4;
    }
    func_800C6554(globalCtx, &globalCtx->colCtx.dyna);
}


void DmChar08_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmChar08* this = (DmChar08*)thisx;
    this->dyna.actor.focus.pos.x = this->unk1D0.x;
    this->dyna.actor.focus.pos.y = this->unk1D0.y + this->dyna.actor.targetArrowOffset;
    this->dyna.actor.focus.pos.z = this->unk1D0.z;
    this->dyna.actor.focus.rot.x = this->dyna.actor.world.rot.x;
    this->dyna.actor.focus.rot.y = this->dyna.actor.world.rot.y;
    this->dyna.actor.focus.rot.z = this->dyna.actor.world.rot.z;
    if (Actor_ProcessTalkRequest(&this->dyna.actor, &globalCtx->state) != 0) {
        this->pad206 = 1;
    }
    func_80AAF050(this);
    this->actionFunc(this, globalCtx);
    func_80AAFE88(this, globalCtx);
    func_80AB023C(this, globalCtx);
    func_80AB032C(this, globalCtx);
    func_80AB01E8(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    func_80AAFBA4(this, globalCtx);
    this->dyna.actor.world.pos.y = this->unk1E4;
    if (globalCtx->sceneNum == SCENE_31MISAKI) {
        if (this->dyna.actor.xzDistToPlayer > 1300.0f) {
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        } else {
            func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        }
    }
    if (this->unk1FF != 0) {
        func_80AAFCCC(this, globalCtx);
        func_800B8614(&this->dyna.actor, globalCtx, 400.0f);
    }
    func_80AB096C(this, globalCtx);
    func_80AB0A10(this, globalCtx);
}

s32 func_80AB0E3C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((globalCtx->csCtx.state == 0) && (globalCtx->sceneNum == SCENE_31MISAKI) &&
        (limbIndex == OBJECT_KAMEJIMA_LIMB_15)) {
        rot->z = -0x5E24;
    }
    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0E7C.s")
void func_80AB0E7C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmChar08* this = THIS;
    Vec3f src;

    if (limbIndex == 2) {
        src.x = 800.0f;
        src.y = 2600.0f;
        src.z = -800.0f;
        Matrix_MultiplyVector3fByState(&src, &this->unk1AC);
        src.x = 2600.0f;
        src.y = 2500.0f;
        src.z = 700.0f;
        Matrix_MultiplyVector3fByState(&src, &this->unk1B8);
    } else if (limbIndex == 8) {
        src.x = 1600.0f;
        src.y = -200.0f;
        src.z = 0.0f;
        Matrix_MultiplyVector3fByState(&src, &this->unk1C4);
    } else if (limbIndex == 6) {
        src.x = 600.0f;
        src.y = 700.0f;
        src.z = 0.0f;
        Matrix_MultiplyVector3fByState(&src, &this->unk1D0);
    }
}

#ifdef NON_MATCHING
void func_80AB0F90(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    DmChar08* this = THIS;

    switch (limbIndex) {
        case 4:
            Matrix_StatePop();
            temp_f12 = ((1.0f - 0.7f) * this->unk1F0) + 0.7f;
            Matrix_Scale(temp_f12, temp_f12, 1.0f, 1);
            Matrix_StatePush();
            return;
        case 17:
        case 18:
        case 21:
        case 22:
            Matrix_StatePop();
            temp_f12_2 = (this->unk1F0 * 0.4f) + 0.6f;
            Matrix_Scale(temp_f12_2, temp_f12_2, temp_f12_2, 1);
            Matrix_StatePush();
            return;
        case 19:
        case 23:
            temp_f12_3 = (this->unk1F0 * 0.4f) + 0.6f;
            Matrix_Scale(temp_f12_3, temp_f12_3, temp_f12_3, 1);
            return;
        case 14:
            Matrix_StatePop();
            temp_f12_4 = (this->unk1F0 * 0.52f) + 0.48f;
            Matrix_Scale(temp_f12_4, temp_f12_4, temp_f12_4, 1);
            Matrix_StatePush();
            return;
        case 10:
        case 12:
            temp_f12_5 = (this->unk1F0 * 0.55f) + 0.45f;
            Matrix_Scale(temp_f12_5, (this->unk1F0 * 0.2f) + 0.8f, temp_f12_5, 1);
            /* fallthrough */
        default:
            return;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0F90.s")
#endif

void func_80AB0F90(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx); /* extern */

void DmChar08_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmChar08* this = (DmChar08*)thisx;
    s32 pad;
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AB1788[this->unk201]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AB1788[this->unk201]));
    if ((this->unk1FF > 0) || (globalCtx->csCtx.state != 0)) {
        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, func_80AB0E3C, func_80AB0E7C, func_80AB0F90,
                                       &this->dyna.actor);
        this->unk1A4->world.pos.x = this->unk1AC.x;
        this->unk1A4->world.pos.y = this->unk1AC.y;
        this->unk1A4->world.pos.z = this->unk1AC.z;
        this->unk1A8->world.pos.x = this->unk1B8.x;
        this->unk1A8->world.pos.y = this->unk1B8.y;
        this->unk1A8->world.pos.z = this->unk1B8.z;
    }
    if (this->unk1FF == 0) {
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_kamejima_DL_004E70);
        return;
    }
    if (this->unk1FF == 1) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        Scene_SetRenderModeXlu(globalCtx, 2, 2);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk205);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_kamejima_DL_004E70);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
