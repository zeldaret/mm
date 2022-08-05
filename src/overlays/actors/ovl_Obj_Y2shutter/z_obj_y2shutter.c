/*
 * File: z_obj_y2shutter.c
 * Overlay: ovl_Obj_Y2shutter
 * Description: Pirates' Fortress sliding grate
 */

#include "z_obj_y2shutter.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjY2shutter*)thisx)

void ObjY2shutter_Init(Actor* thisx, PlayState* play);
void ObjY2shutter_Destroy(Actor* thisx, PlayState* play);
void ObjY2shutter_Update(Actor* thisx, PlayState* play);
void ObjY2shutter_Draw(Actor* thisx, PlayState* play);

typedef struct ShutterInfo {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ CollisionHeader* colHeader;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
} ShutterInfo; // size = 0x20

const ActorInit Obj_Y2shutter_InitVars = {
    ACTOR_OBJ_Y2SHUTTER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2shutter),
    (ActorFunc)ObjY2shutter_Init,
    (ActorFunc)ObjY2shutter_Destroy,
    (ActorFunc)ObjY2shutter_Update,
    (ActorFunc)ObjY2shutter_Draw,
};

ShutterInfo sShutterInfo[] = {
    { gPirateBarredShutterDL, &gPirateBarredShutterCol, 120.0f, 20.0f, 3.0f, -20.0f, 3.0f, 4, 8, 160 },
    { gPirateGratedShutterDL, &gPirateGratedShutterCol, 150.0f, 1.0f, 0.04f, -1.0f, 0.04f, 6, 0xC, 160 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ObjY2shutter_Init(Actor* thisx, PlayState* play) {
    s32 pad[2];
    ShutterInfo* info = &sShutterInfo[OBJY2SHUTTER_GET_SHUTTER_TYPE(thisx)];
    ObjY2shutter* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(play, &this->dyna, info->colHeader);
}

void ObjY2shutter_Destroy(Actor* thisx, PlayState* play) {
    ObjY2shutter* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80B9AA20(ObjY2shutter* this, ShutterInfo* info, ShutterType shutterType) {
    this->unk_15C = info->unk_1E;
    this->unk_15F = info->unk_1C;
    if (shutterType == BARRED_SHUTTER) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_OPEN);
    }
}

void ObjY2shutter_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjY2shutter* this = THIS;
    ShutterType shutterType = OBJY2SHUTTER_GET_SHUTTER_TYPE(&this->dyna.actor);
    ShutterInfo* info = &sShutterInfo[shutterType];
    f32 sp2C = this->dyna.actor.world.pos.y;
    f32 sp28 = 0.0f;
    f32 sp24 = 0.0f;

    sShutterInfo[0].unk_1E = DREG(84) + 0xA0;
    sShutterInfo[1].unk_1E = DREG(85) + 0xA0;

    if (((shutterType == BARRED_SHUTTER) && (DREG(86) != 0)) || ((shutterType != BARRED_SHUTTER) && (DREG(87) != 0))) {
        if (shutterType == BARRED_SHUTTER) {
            DREG(86) = 0;
        } else {
            DREG(87) = 0;
        }
        if (Flags_GetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor))) {
            Flags_UnsetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
        } else {
            Flags_SetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
        }
    }
    if (this->unk_15F == 0) {
        if (Flags_GetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor))) {
            s16 cutscene = this->dyna.actor.cutscene;

            if (this->unk_15C == 0) {
                if ((cutscene >= 0) && !ActorCutscene_GetCanPlayNext(cutscene)) {
                    ActorCutscene_SetIntentToPlay(cutscene);
                } else if (cutscene >= 0) {
                    ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->dyna.actor);
                    this->unk_15C = -1;
                } else {
                    func_80B9AA20(this, info, shutterType);
                }
            } else if (this->unk_15C < 0) {
                if (func_800F22C4(cutscene, &this->dyna.actor)) {
                    func_80B9AA20(this, info, shutterType);
                }
            } else {
                sp2C = this->dyna.actor.home.pos.y + info->unk_8;
                sp28 = info->unk_C;
                sp24 = info->unk_10;
                if (this->unk_15C < 2) {
                    Flags_UnsetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
                } else {
                    this->unk_15C--;
                }
            }
        } else if (this->unk_15C != 0) {
            this->unk_15C = 0;
            this->unk_15F = info->unk_1C;
            if (shutterType == 0) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_CLOSE);
            }
        } else {
            sp2C = this->dyna.actor.home.pos.y;
            sp28 = info->unk_14;
            sp24 = info->unk_18;
        }
    }
    Math_StepToF(&this->dyna.actor.velocity.y, sp28, sp24);
    this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
    if (((this->dyna.actor.world.pos.y - sp2C) * sp28) >= 0.0f) {
        this->dyna.actor.world.pos.y = sp2C;
        this->dyna.actor.velocity.y = 0.0f;
        if (!this->unk_15E) {
            this->unk_15E = true;
            this->unk_15F = info->unk_1D;
            if (shutterType != BARRED_SHUTTER) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_STOP);
            }
        }
    } else {
        this->unk_15E = false;
        if (shutterType != 0) {
            func_800B9010(&this->dyna.actor, NA_SE_EV_METALDOOR_SLIDE - SFX_FLAG);
        }
    }
    if (DECR(this->unk_15F) != 0) {
        this->dyna.actor.shape.yOffset = 2.0f * (this->unk_15F & 1) * this->unk_15F;
    }
}

void ObjY2shutter_Draw(Actor* thisx, PlayState* play) {
    ObjY2shutter* this = THIS;
    ShutterInfo* info = &sShutterInfo[(OBJY2SHUTTER_GET_SHUTTER_TYPE(&this->dyna.actor))];

    Gfx_DrawDListOpa(play, info->dList);
}
