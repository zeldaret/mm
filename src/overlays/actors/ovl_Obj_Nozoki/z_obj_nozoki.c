/*
 * File: z_obj_nozoki.c
 * Overlay: ovl_Obj_Nozoki
 * Description: Sakon's Hideout Objects (Sun's Mask, doors, etc)
 */

#include "z_obj_nozoki.h"
#include "objects/object_secom_obj/object_secom_obj.h"
#include "prevent_bss_reordering.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjNozoki*)thisx)

void ObjNozoki_Init(Actor* thisx, PlayState* play);
void ObjNozoki_Destroy(Actor* thisx, PlayState* play);
void ObjNozoki_Update(Actor* thisx, PlayState* play);

void ObjNozoki_SetupAction(ObjNozoki* this, ObjNozokiActionFunc actionFunc);
void func_80BA2514(ObjNozoki* this, PlayState* play);
void func_80BA27C4(ObjNozoki* this, PlayState* play);
void func_80BA28DC(ObjNozoki* this, PlayState* play);
void func_80BA2AB4(ObjNozoki* this, PlayState* play);
void func_80BA2BA4(ObjNozoki* this, PlayState* play);
void func_80BA2C94(ObjNozoki* this, PlayState* play);
void func_80BA3044(ObjNozoki* this, PlayState* play);
void func_80BA311C(ObjNozoki* this, PlayState* play);
void func_80BA3230(ObjNozoki* this, PlayState* play);
void func_80BA3344(ObjNozoki* this, PlayState* play);
void ObjNozoki_Draw(Actor* thisx, PlayState* play);

s32 D_80BA36B0;
s32 D_80BA36B4;
f32 D_80BA36B8;

const ActorInit Obj_Nozoki_InitVars = {
    ACTOR_OBJ_NOZOKI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjNozoki),
    (ActorFunc)ObjNozoki_Init,
    (ActorFunc)ObjNozoki_Destroy,
    (ActorFunc)ObjNozoki_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

s16 D_80BA34B8[] = { OBJECT_SECOM_OBJ, OBJECT_GI_MSSA, OBJECT_SECOM_OBJ, OBJECT_SECOM_OBJ };

Vec3f D_80BA34C0 = { 0.0f, 0.0f, -1110.0f };

Vec3f D_80BA34CC = { 0.0f, 0.0f, 38.0f };

f32 D_80BA34D8[] = { 100.0f, 9999.0f, 9999.0f };

f32 D_80BA34E4[] = { 0.5f, 0.25f, 1.0f };

void ObjNozoki_SetupAction(ObjNozoki* this, ObjNozokiActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ObjNozoki_Init(Actor* thisx, PlayState* play) {
    ObjNozoki* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->unk_15F = this->dyna.actor.cutscene;

    if (play->sceneNum == SCENE_AYASHIISHOP) {
        this->unk_15C = 4;
        ObjNozoki_SetupAction(this, func_80BA3230);
        this->dyna.actor.colChkInfo.cylRadius = -40;
    } else {
        this->unk_15C = OBJNOZOKI_GET_180(&this->dyna.actor);
        if (this->unk_15C == 0) {
            DynaPolyActor_Init(&this->dyna, 0);
        }
        ObjNozoki_SetupAction(this, func_80BA2514);
    }
}

void ObjNozoki_Destroy(Actor* thisx, PlayState* play) {
    ObjNozoki* this = THIS;

    if (this->unk_15C == 0) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80BA2514(ObjNozoki* this, PlayState* play) {
    s32 sp24 = Object_GetIndex(&play->objectCtx, D_80BA34B8[this->unk_15C]);

    if (sp24 < 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (Object_IsLoaded(&play->objectCtx, sp24)) {
        this->dyna.actor.objBankIndex = sp24;
        this->dyna.actor.draw = ObjNozoki_Draw;

        if (this->unk_15C == 0) {
            Actor_SetObjectDependency(play, &this->dyna.actor);
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_secom_obj_Colheader_0001C0);
            if (ActorCutscene_GetAdditionalCutscene(this->unk_15F) >= 0) {
                this->dyna.actor.params |= OBJNOZOKI_400;
            }
            ObjNozoki_SetupAction(this, func_80BA27C4);
        } else if (this->unk_15C == 1) {
            Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.world.pos, this->dyna.actor.shape.rot.y, &D_80BA34C0,
                                          &this->dyna.actor.home.pos);
            Actor_SetScale(&this->dyna.actor, 0.6f);
            this->dyna.actor.flags |= ACTOR_FLAG_20;
            ObjNozoki_SetupAction(this, func_80BA2BA4);
        } else if (this->unk_15C == 2) {
            Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.home.pos, this->dyna.actor.shape.rot.y, &D_80BA34CC,
                                          &this->dyna.actor.focus.pos);
            Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.focus.pos);
            ObjNozoki_SetupAction(this, func_80BA3044);
        } else {
            ObjNozoki_SetupAction(this, func_80BA311C);
        }
    }
}

s32 func_80BA26A8(ObjNozoki* this) {
    if (this->unk_15F < 0) {
        return true;
    }

    if (ActorCutscene_GetCanPlayNext(this->unk_15F)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_15F, &this->dyna.actor);
        return true;
    }

    ActorCutscene_SetIntentToPlay(this->unk_15F);
    return false;
}

s32 func_80BA2708(ObjNozoki* this, PlayState* play) {
    Actor* enemy = play->actorCtx.actorLists[ACTORCAT_ENEMY].first;
    Vec3f sp30;

    while (enemy != NULL) {
        Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &sp30, &enemy->world.pos);
        if (sp30.z >= 0.0f) {
            return false;
        }
        enemy = enemy->next;
    }

    return true;
}

void func_80BA2790(ObjNozoki* this) {
    ObjNozoki_SetupAction(this, func_80BA28DC);
    this->dyna.actor.velocity.y = 0.0f;
    this->unk_15E = 0;
}

void func_80BA27C4(ObjNozoki* this, PlayState* play) {
    if (!(play->actorCtx.unk5 & 0x20)) {
        if (OBJNOZOKI_GET_200(&this->dyna.actor)) {
            if (!func_80BA2708(this, play)) {
                return;
            }
        } else {
            if (D_80BA36B0 != 0) {
                play->actorCtx.unk5 |= 0x80;
            }

            if (!Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
                return;
            }
        }

        if ((D_80BA36B0 == 0) || func_80BA26A8(this)) {
            func_80BA2790(this);
            if (D_80BA36B0 == 0) {
                this->unk_15E = 25;
                play_sound(NA_SE_SY_SECOM_WARNING);
            } else {
                this->unk_15E = ActorCutscene_GetLength(this->unk_15F);
                if (this->unk_15E < 0) {
                    this->unk_15E = 50;
                }
                play->actorCtx.unk5 |= 0x10;
            }
        }
        GET_PLAYER(play)->linearVelocity = 0.0f;
    }
}

void func_80BA28DC(ObjNozoki* this, PlayState* play) {
    if (this->unk_15E != 0) {
        if (DECR(this->unk_15E) == 0) {
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_OPEN);
        }
        return;
    }

    if (!(play->actorCtx.unk5 & 0x20)) {
        Math_StepToF(&this->dyna.actor.velocity.y, 15.0f, 3.0f);
        Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 200.0f, this->dyna.actor.velocity.y);

        if (OBJNOZOKI_GET_200(&this->dyna.actor)) {
            if (!Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
                return;
            }
        } else if (Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
            s32 cs = this->dyna.actor.cutscene;

            if (cs == this->unk_15F) {
                if (OBJNOZOKI_GET_400(&this->dyna.actor)) {
                    Vec3f sp28;

                    Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &sp28, &GET_PLAYER(play)->actor.world.pos);
                    if (sp28.z < -20.0f) {
                        this->unk_15F = ActorCutscene_GetAdditionalCutscene(this->unk_15F);
                    }
                }
            } else if (D_80BA36B4 == 0) {
                if (func_80BA26A8(this)) {
                    D_80BA36B4 = 1;
                }
            } else if (ActorCutscene_GetCurrentIndex() != this->unk_15F) {
                this->unk_15F = cs;
                this->dyna.actor.params &= ~OBJNOZOKI_400;
                Audio_QueueSeqCmd(0x881A);
            }
            return;
        }
    }

    ObjNozoki_SetupAction(this, func_80BA2AB4);
    this->dyna.actor.velocity.y = 0.0f;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_CLOSE);
}

void func_80BA2AB4(ObjNozoki* this, PlayState* play) {
    this->dyna.actor.velocity.y = 30.0f;

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 30.0f) && (D_80BA36B0 == 0)) {
        ObjNozoki_SetupAction(this, func_80BA27C4);
        D_80BA36B0 = 1;
    }

    if (!(play->actorCtx.unk5 & 0x20)) {
        if (!(OBJNOZOKI_GET_200(&this->dyna.actor)) &&
            Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
            func_80BA2790(this);
        }
    }
}

void func_80BA2B64(ObjNozoki* this, PlayState* play, s32 arg2, s32 arg3) {
    this->unk_15D = arg2;
    this->unk_15E = 80;
    Flags_UnsetSwitch(play, arg3);
}

void func_80BA2BA4(ObjNozoki* this, PlayState* play) {
    if (!Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
        this->dyna.actor.shape.rot.x = -0x1F40;
        this->unk_15E = 80;
    } else if (DECR(this->unk_15E) == 0) {
        ObjNozoki_SetupAction(this, func_80BA2C94);
    }
}

s32 func_80BA2C28(ObjNozoki* this) {
    s32 i;
    s16 cs = this->unk_15F;

    for (i = 0; i < 3; i++) {
        if (ActorCutscene_GetCurrentIndex() == cs) {
            return i;
        }
        cs = ActorCutscene_GetAdditionalCutscene(cs);
    }

    return -1;
}

void func_80BA2C94(ObjNozoki* this, PlayState* play) {
    s32 temp_v0 = func_80BA2C28(this);
    f32 sp38;
    f32 sp34;
    f32 temp_f0;

    if (temp_v0 >= 0) {
        D_80BA36B4 = temp_v0;
    }

    if ((temp_v0 < 0) && Play_InCsMode(play)) {
        return;
    }

    if (D_80BA36B8 < D_80BA34D8[D_80BA36B4]) {
        sp38 = this->dyna.actor.home.pos.y - this->dyna.actor.world.pos.y;

        if ((this->unk_15D != 1) && Flags_GetSwitch(play, this->dyna.actor.world.rot.z)) {
            func_80BA2B64(this, play, 1, this->dyna.actor.world.rot.x);
        } else if ((this->unk_15D != 2) && Flags_GetSwitch(play, this->dyna.actor.world.rot.x)) {
            func_80BA2B64(this, play, 2, this->dyna.actor.world.rot.z);
        } else if (DECR(this->unk_15E) == 0) {
            this->unk_15D = 0;
            Flags_UnsetSwitch(play, this->dyna.actor.world.rot.z);
            Flags_UnsetSwitch(play, this->dyna.actor.world.rot.x);
        }

        Math_StepToF(&this->dyna.actor.speedXZ, D_80BA34E4[this->unk_15D], 0.1f);

        if ((play->actorCtx.unk5 & 0x40) || (play->actorCtx.unk5 & 0x20)) {
            temp_f0 = 0.5f;
        } else {
            temp_f0 = this->dyna.actor.speedXZ;
        }

        sp34 = Math_Vec3f_StepToXZ(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos, temp_f0);

        D_80BA36B8 += this->dyna.actor.speedXZ;

        if (play->actorCtx.unk5 & 0x40) {
            if (sp34 <= 5.0f) {
                Actor_MarkForDeath(&this->dyna.actor);
            }
        } else if (!(play->actorCtx.unk5 & 0x20) && (GET_PLAYER(play)->actor.id == ACTOR_PLAYER) &&
                   Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG2(&this->dyna.actor)) && (sp38 < 20.0f)) {
            static Vec3f D_80BA34F0 = { 0.0f, 0.0f, 50.0f };

            play->actorCtx.unk5 |= 0x40;
            Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.home.pos, this->dyna.actor.shape.rot.y, &D_80BA34F0,
                                          &this->dyna.actor.world.pos);
            this->dyna.actor.shape.rot.x = -0x1F40;
        } else if (sp34 < 50.0f) {
            play->actorCtx.unk5 |= 0x20;

            if (sp34 < 20.0f) {
                this->dyna.actor.velocity.y -= 0.4f;
                this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;

                sp38 = this->dyna.actor.home.pos.y - this->dyna.actor.world.pos.y;
                if (sp38 >= 100.0f) {
                    Actor_MarkForDeath(&this->dyna.actor);
                }

                this->dyna.actor.shape.rot.x = -0x1F40 - (s16)(sp38 * 400.0f);
            }
        }
    }

    this->dyna.actor.velocity.x += this->dyna.actor.speedXZ * 0.66f;
    if (this->dyna.actor.velocity.x >= 0x10000) {
        this->dyna.actor.velocity.x -= 0x10000;
    }

    play->roomCtx.unk7A[0] = this->dyna.actor.velocity.x;

    func_8019FAD8(&D_801DB4A4, NA_SE_EV_SECOM_CONVEYOR - SFX_FLAG, this->dyna.actor.speedXZ);
}

void func_80BA3044(ObjNozoki* this, PlayState* play) {
    Vec3f* sp1C = &this->dyna.actor.focus.pos;

    if (this->unk_15D == 0) {
        if (play->actorCtx.unk5 & 0x40) {
            this->unk_15D = 1;
            this->unk_15E = 20;
            Math_Vec3f_Copy(&this->dyna.actor.world.pos, sp1C);
        } else if (!(play->actorCtx.unk5 & 0x20) &&
                   Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
            sp1C = &this->dyna.actor.home.pos;
        }
    } else if (DECR(this->unk_15E) == 0) {
        sp1C = &this->dyna.actor.home.pos;
    }

    Math_Vec3f_StepToXZ(&this->dyna.actor.world.pos, sp1C, 8.0f);
}

void func_80BA311C(ObjNozoki* this, PlayState* play) {
    if (this->unk_15D == 0) {
        if (Flags_GetSwitch(play, OBJNOZOKI_GET_SWITCHFLAG1(&this->dyna.actor))) {
            this->unk_15D = 1;
            this->unk_15E = 70;
        }
    } else if (this->unk_15D == 1) {
        if (D_80BA36B8 > 40.0f) {
            this->unk_15D = 2;
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_PL_SIT_ON_HORSE);
        } else if (this->unk_15E != 0) {
            if (DECR(this->unk_15E) == 0) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_CONVEYOR_SHUTTER_OPEN);
            }
        } else {
            Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 50.0f, 4.0f);
        }
    } else {
        Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 4.0f);
    }
}

void func_80BA3230(ObjNozoki* this, PlayState* play) {
    if (gSaveContext.save.weekEventReg[64] & 0x20) {
        Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;
        Actor* test3 = SubS_FindActor(play, npc, ACTORCAT_NPC, ACTOR_EN_TEST3);

        if ((test3 != NULL) && (test3->draw != NULL)) {
            if ((play->curSpawn == 3) && !(gSaveContext.save.weekEventReg[64] & 0x40)) {
                this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10000);
                this->dyna.actor.textId = 0x297A;
            } else {
                this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
                if (gSaveContext.save.weekEventReg[64] & 0x40) {
                    this->dyna.actor.textId = 0;
                } else {
                    this->dyna.actor.textId = 0x2979;
                }
            }

            if (Actor_ProcessTalkRequest(&this->dyna.actor, &play->state)) {
                ObjNozoki_SetupAction(this, func_80BA3344);
            } else {
                func_800B8614(&this->dyna.actor, play, 50.0f);
            }
        }
    }
}

void func_80BA3344(ObjNozoki* this, PlayState* play) {
    if ((play->curSpawn == 3) && !(gSaveContext.save.weekEventReg[64] & 0x40)) {
        if (Actor_TextboxIsClosing(&this->dyna.actor, play)) {
            gSaveContext.save.weekEventReg[64] |= 0x40;
            this->dyna.actor.flags &= ~ACTOR_FLAG_10000;
            ObjNozoki_SetupAction(this, func_80BA3230);
        }
    } else if ((this->dyna.actor.textId == 0) || Actor_TextboxIsClosing(&this->dyna.actor, play)) {
        play->nextEntranceIndex = 0xE20;
        play->transitionTrigger = TRANS_TRIGGER_START;
    }
}

void ObjNozoki_Update(Actor* thisx, PlayState* play) {
    ObjNozoki* this = THIS;

    this->actionFunc(this, play);
}

Gfx* D_80BA34FC[] = {
    object_secom_obj_DL_000080,
    (Gfx*)0x0A0001A0, //! @bug This dlist should point to a dlist in OBJECT_GI_MSSA, but the segment and the offset are
                      //! wrong. This doesn't have side effects because of the extra check in the Draw function
    object_secom_obj_DL_001230,
    object_secom_obj_DL_001300,
};

void ObjNozoki_Draw(Actor* thisx, PlayState* play) {
    ObjNozoki* this = THIS;

    if (this->unk_15C == 1) {
        GetItem_Draw(play, GID_39);
    } else {
        Gfx_DrawDListOpa(play, D_80BA34FC[this->unk_15C]);
    }
}
