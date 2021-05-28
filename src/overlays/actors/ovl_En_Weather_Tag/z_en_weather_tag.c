#include "z_en_weather_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnWeatherTag*)thisx)

//void EnWeatherTag_Init(EnWeatherTag* this, GlobalContext* globalCtx);
void EnWeatherTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80966A08(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966A68(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966AE4(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966B08(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966BF4(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966D20(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966E0C(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966E84(EnWeatherTag* this, GlobalContext* globalCtx);

void func_80966EF0(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966F74(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966FEC(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80967060(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80967148(EnWeatherTag* this, GlobalContext* globalCtx);
void func_809671A8(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80967250(EnWeatherTag* this, GlobalContext* globalCtx);
void func_809671B8(EnWeatherTag* this, GlobalContext* globalCtx);
void func_809672DC(EnWeatherTag* this, GlobalContext* globalCtx);
void func_809674C8(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80967608(EnWeatherTag* this, GlobalContext* globalCtx);

const ActorInit En_Weather_Tag_InitVars = {
    ACTOR_EN_WEATHER_TAG,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWeatherTag),
    (ActorFunc)EnWeatherTag_Init,
    (ActorFunc)EnWeatherTag_Destroy,
    (ActorFunc)EnWeatherTag_Update,
    (ActorFunc)EnWeatherTag_Draw,
};

void func_80966410(EnWeatherTag* this, EnWeatherTagActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnWeatherTag_Destroy(Actor *thisx, GlobalContext *globalCtx) { }

extern f32 D_801F4E74;

void EnWeatherTag_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnWeatherTag* this = (EnWeatherTag*) thisx;
    s32 pad;
    Path* path;
    s32 tempParams;

    this->actor.flags &= ~1;

    switch (this->actor.params & 0xF) {
        case 0:
            this->unk154 = 0;
            this->unk156 = (s16) this->actor.world.rot.x;
            this->unk158 = (s16) this->actor.world.rot.y;
            func_80966410(this, func_80966A08);
            break;
        case 1:
            if ((gSaveContext.perm.weekEventReg[0x34] & 0x20) != 0) {
                Actor_MarkForDeath(&this->actor);
            }
            func_80966410(this, func_80966B08);
            break;
        case 2:
            func_80966410(this, func_80966E0C);
            break;
        case 3:
            if (0) {} // this can move to diff locations and still match
            func_80966410(this, func_80966EF0);
            break;
        case 4:
            func_80966410(this, func_80966FEC);
            break;
        case 5:
            func_800BC154(globalCtx, &globalCtx->actorCtx, (Actor *) this, 7);
            globalCtx->unk18874 = 3;
            globalCtx->kankyoContext.unk1F = 5;
            globalCtx->kankyoContext.unk20 = 5;
            D_801F4E74 = 1.0f;
            func_80966410(this, &func_80966BF4);
            break;
        case 6:
            tempParams = this->actor.params >> 4 & 0xF;
            path = &globalCtx->setupPathList[(tempParams)];
            this->unk150 = Lib_SegmentedToVirtual(path->points);
            this->unk14C = path->count;
            func_80966410(this, func_809672DC);
            break;
        case 7:
            func_80966410(this, func_809674C8);
    }
}

//matches but unused params is suspicious
u8 func_80966608(EnWeatherTag *this, GlobalContext *globalCtx, s16 arg3, s32 arg4, u8 newUnk1F, u8 newUnk20, u16 newUnk24, u8 targetValue) {
    s32 pad;
    u8 returnVal = 0;

    // u8 cast req
    // in OOT this param was weatherrange
    if ((((u8) ((this->actor.params >> 8) & 0xFF)) * 100.0f) 
        > Actor_XZDistanceBetweenActors(&PLAYER->base, &this->actor)) {
        if (globalCtx->kankyoContext.unk1F == globalCtx->kankyoContext.unk20) {
            D_801BDBB8 = 1;
            if (! (globalCtx->kankyoContext.unk1E == 0)
                ||  ((globalCtx->kankyoContext.unk1F != 1) && (globalCtx->kankyoContext.unk21 == 0))) {
                D_801BDBB8 = 0;
                if (D_801BDBB0 != targetValue) {
                    D_801BDBB0 = targetValue;
                    globalCtx->kankyoContext.unk21 = 1;
                    globalCtx->kankyoContext.unk1F = newUnk1F;
                    globalCtx->kankyoContext.unk20 = newUnk20;
                    D_801BDBB4 = newUnk20;
                    globalCtx->kankyoContext.unk24 = newUnk24;
                    globalCtx->kankyoContext.unk22 = globalCtx->kankyoContext.unk24;
                }
                returnVal = 1;
            }
        }
    }
    return returnVal;
} //#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966608.asm")

s32 func_80966758(EnWeatherTag *this, GlobalContext *globalCtx, UNK_TYPE three, UNK_TYPE four, u8 five, u8 six, u16 seven);
// weirdly all the other functions pass more parameters than it usees, THREE and FOUR arent used..????
/*
// no where close with this one, just wanted some insignt into what it did 
}// */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966758.asm")


void func_8096689C(EnWeatherTag *this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_8096689C.asm")

void func_80966A08(EnWeatherTag *this, GlobalContext *globalCtx) {
    this->unk154 += this->unk158;
    if ((this->unk154) >= 0x8001) {
        this->unk154 = 0x8000;
        func_80966410(this, func_80966A68);
    }
    func_8096689C(this, globalCtx);
}

void func_80966A68(EnWeatherTag *this, GlobalContext *globalCtx) {
    this->unk154 -= (this->unk158 >> 1);
    if (this->unk154 == 0) {
        this->unk154 = 1;
        this->unk154 = 1;
    }
    if ((s16) this->unk154 < 0) {
        this->unk154 = 0;
        Actor_MarkForDeath((Actor *) this);
        func_80966410(this, func_80966AE4);
    }
    func_8096689C(this, globalCtx);
}

void func_80966AE4(EnWeatherTag *this, GlobalContext *globalCtx) {
    Actor_MarkForDeath((Actor *) this);
}

void func_80966B08(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966608(this, globalCtx, 0, 0, globalCtx->kankyoContext.unk1F, 5, 0x64, 2) != 0 
        || D_801BDBB0 == 2) {
        globalCtx->unk18874 = 3;
        func_80966410(this, func_80966D20);
        return;
    }
    if (D_801F4E74 <= 0.01f) {
        globalCtx->unk18874 = 1;
        return;
    }
    Math_SmoothStepToF(&D_801F4E74, 0.0f, 0.2f, 0.02f, 0.001f);

}

// action func
void func_80966BF4(EnWeatherTag *this, GlobalContext *globalCtx) {
    u8 newUnk20;
    CsCmdActorAction *tmpAction;

    if (func_800EE29C(globalCtx, 0x237) != 0) {
        tmpAction = globalCtx->csCtx.actorActions[func_800EE200(globalCtx, 0x237)];
        if (((s32) globalCtx->csCtx.frames >= (s32) tmpAction->startFrame) && ((s32) tmpAction->unk0 >= 2)) {
            switch(gSaveContext.perm.day) {
              case 0: 
              case 1: 
              default:
                newUnk20 = 0;
                break;
              case 2: 
                newUnk20 = 3;
                break;
              case 3: 
                newUnk20 = 4;
                break;
            }
            Math_SmoothStepToF(&D_801F4E74, 0.0f, 0.2f, 0.02f, 0.001f);
            if (globalCtx->kankyoContext.unk20 != newUnk20) {
                globalCtx->kankyoContext.unk21 = 1;
                globalCtx->kankyoContext.unk20 = newUnk20;
                globalCtx->kankyoContext.unk24 = 100;
                globalCtx->kankyoContext.unk22 = globalCtx->kankyoContext.unk24;
            }
        }
    }
}


// this matches NOW but what if the function called changes
void func_80966D20(EnWeatherTag *this, GlobalContext *globalCtx) {
    u8 phi_v0;
    s32 temp_v0;

    temp_v0 = gSaveContext.perm.day;
    switch (gSaveContext.perm.day) {
        case 0: 
        case 1: 
        default:
          phi_v0 = 0;
          break;
        case 2: 
          phi_v0 = 3;
          break;
        case 3: 
          phi_v0 = 4;
          break;
    }
    
    Math_SmoothStepToF(&D_801F4E74, 1.0f, 0.2f, 0.02f, 0.001f);
    if (func_80966758(this, globalCtx, 1, 0, 5, (s32) phi_v0, 100) != 0) {
        func_80966410(this, func_80966B08);
    }

    // ?
    if (D_801BDBB0 != 2) {
        func_80966410(this, func_80966B08);
    }
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966D20.asm")

void func_80966E0C(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966608(this, globalCtx, 0, 1, 0, 2, 0x3C, 3) != 0) {
        globalCtx->kankyoContext.unkF2[3] = 0x80;
        func_80966410(this, func_80966E84);
    }
}

void func_80966E84(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966758(this, globalCtx, 1, 0, 2, 0, 0x3C) != 0) {
        globalCtx->kankyoContext.unkF2[3] = 0;
        func_80966410(this, func_80966E0C);
    }
}

void func_80966EF0(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966608(this, globalCtx, 0, 1, 0, 2, 0x64, 4) != 0) {
        func_800FD78C(globalCtx);
        globalCtx->kankyoContext.unkF2[0] = 0x3C;
        func_80966410(this, func_80966F74);
    }
}

void func_80966F74(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966758(this, globalCtx, 1, 0, 2, 0, 0x64) != 0) {
        func_800FD858(globalCtx);
        globalCtx->kankyoContext.unkF2[0] = 0;
        func_80966410(this, func_80966EF0);
    }
}

void func_80966FEC(EnWeatherTag *this, GlobalContext *globalCtx) {
    s32 newParamByte;

    newParamByte = ((u8)(this->actor.params >> 8)) * 100;
    if (newParamByte > 0) {
        D_801F4E7A = (s16) newParamByte;
    }

    // pirates fortress..?
    if ((globalCtx->sceneNum == SCENE_KAIZOKU) && ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        func_80966410(this, func_80967060);
    }
}

#if NON_MATCHING
// non-matching: two instructions are swapped
void func_80967060(EnWeatherTag *this, GlobalContext *globalCtx) {
    Vec3f sp24;
    Vec3f sp18;

    sp24.x = 1055.0f;
    sp24.y = -145.0f;
    sp24.z = 181.0f;

    func_80169474(globalCtx, &sp24, &sp18);

    if ((globalCtx->view.fovy < 25.0f) 
      && (sp18.x >= 70.0f) && (sp18.x < 250.0f) 
      && (sp18.y >= 30.0f) && (sp18.y < 210.0f)) {
        func_80966410(this, func_80967148);
    }
} 
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967060.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809672DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809674C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Draw.asm")
