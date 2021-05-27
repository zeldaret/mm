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
void func_80966BF4(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966D20(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966B08(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966E84(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966E0C(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966F74(EnWeatherTag* this, GlobalContext* globalCtx);
void func_80966EF0(EnWeatherTag* this, GlobalContext* globalCtx);
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

// based on another function, param2 is never used though, so probably globalCtx
//u8 func_80966608(EnWeatherTag *this, GlobalContext* globalCtx, s16 param3, s32 parm4, u8 param5, u8 param6, u16 param7);
// // the snare of ifs is a mess
///*
u8 func_80966608(EnWeatherTag *this, GlobalContext *globalCtx, s16 param3, s32 parm4, u8 param5, u8 param6, u16 param7, u8 arg7) {
    //Actor *player;
    f32 paramSecondByte;
    u8 returnVal;
    f32 distance;
    s32 DTemp;

    // dont think we have space for player as a temp
    //player = globalCtx->actorCtx.actorList[2].first;
    //player = PLAYER;
    //distance = Actor_XZDistanceBetweenActors(player, &this->actor);

    // this has to be moved early since I can't get the compiler to run it sooner
    distance = Actor_XZDistanceBetweenActors(&PLAYER->base, &this->actor);

    paramSecondByte = (f32) ((this->actor.params >> 8) & 0xFF);
    //if (paramSecondByte < 0) {
    if (((this->actor.params >> 8) & 0xFF) < 0) {
        paramSecondByte += 4294967296.0f; // 4F80
    }
    returnVal = 0;
    //if (Actor_XZDistanceBetweenActors(player, &this->actor) < (paramSecondByte * 100.0f)) {
    if (distance < (paramSecondByte * 100.0f)) {
        //returnVal = 0;
        if (globalCtx->kankyoContext.unk1F == globalCtx->kankyoContext.unk20) { // 7024/7023
            D_801BDBB8 = 1;
            DTemp = D_801BDBB0; // forcing load early
            if (globalCtx->kankyoContext.unk1E == 0) { // 7022
                //returnVal = 0;
                if (globalCtx->kankyoContext.unk1F != 1) { // 7023
                    //returnVal = 0;
                    if (globalCtx->kankyoContext.unk21 == 0  // 7025
                      || globalCtx->kankyoContext.unk1E != 0) {
                  //block_7:
                        D_801BDBB8 = 0;
                        returnVal = 1;
                        //if (arg7 != D_801BDBB0) {
                        //if (arg7 != DTemp) {
                        if (arg7 == DTemp) {
                            return 1;
                        } else {
                            D_801BDBB0 = arg7;
                            globalCtx->kankyoContext.unk21 = (u8) (u8)1;
                            globalCtx->kankyoContext.unk1F = param5;
                            globalCtx->kankyoContext.unk20 = param6;
                            D_801BDBB4 = (s8) param6;
                            globalCtx->kankyoContext.unk24 = param7;
                            globalCtx->kankyoContext.unk22 = globalCtx->kankyoContext.unk24;
                        }
                          
                    }
                }
            //} else {
                //goto block_7;
            }
        }
    }
    return returnVal;
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966608.asm")

s32 func_80966758(EnWeatherTag *this, GlobalContext *globalCtx, UNK_TYPE three, UNK_TYPE four, u8 five, u8 six, u16 seven);
// weirdly all the other functions pass more parameters than it usees, THREE and FOUR arent used..????
/*
// no where close with this one, just wanted some insignt into what it did 
s32 func_80966758(EnWeatherTag *this, GlobalContext *globalCtx, s32 three, s32 four, u8 five, s32 six, s32 seven) {
    Actor *player;
    f32 tmpParamsF;
    s32 tmpParams;
    u8 temp_a0_2;
    s32 returnVal;
    s32 dist;

    //player = globalCtx->actorCtx.actorList[2].first;
    player = PLAYER; 
    dist = Actor_XZDistanceBetweenActors(player, &this->actor);

    //tmpParams = ((s32) this->actor.params >> 8) & 0xFF;
    //tmpParamsF = (f32) tmpParams;
    tmpParamsF = (f32) ((this->actor.params >> 8) & 0xFF);
    //if (tmpParams < 0) {
    if (tmpParamsF < 0) {
        tmpParamsF += 4294967296.0f;
    }
    returnVal = 0;
    //if ((tmpParamsF * 100.0f) < Actor_XZDistanceBetweenActors(player, (Actor *) this)) {
    if ((tmpParamsF * 100.0f) < dist) {
        //returnVal = (s32) zero;
        if (globalCtx->kankyoContext.unk20 == globalCtx->kankyoContext.unk1F) {
            D_801BDBB8 = 1;
            if (globalCtx->kankyoContext.unk1E == 0) {
                //returnVal = (s32) zero;
                if (globalCtx->kankyoContext.unk1F != 1) {
                    //returnVal = (s32) zero;
                    if (globalCtx->kankyoContext.unk21 == 0 
                      || globalCtx->kankyoContext.unk1E != 0) {
                        block_7:
                        D_801BDBB8 = 0;
                        D_801BDBB0 = 0;
                        globalCtx->kankyoContext.unk21 = 1;
                        globalCtx->kankyoContext.unk1F = five;
                        globalCtx->kankyoContext.unk20 = six;
                        D_801BDBB4 = six;
                        globalCtx->kankyoContext.unk24 = seven;
                        globalCtx->kankyoContext.unk22 = globalCtx->kankyoContext.unk24;
                        //returnVal = 1 & 0xFF;
                        returnVal = 1;
                    }
                }
            //} else {
                //goto block_7;
            }
        }
    }
    return returnVal;
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

/*
// weird out of order at the top
void func_80966B08(EnWeatherTag *this, GlobalContext *globalCtx) {
    if (func_80966608(this, 0, 0, (s32) globalCtx->kankyoContext.unk1F, 5, 100, 2) != 0
      || D_801BDBB0 == 2) {
        block_2:
        globalCtx->unk18874 = 3;
        func_80966410(this, func_80966D20);
        return;
    }
    //if (D_801BDBB0 == 2) {
        //goto block_2;
    //}
    if (D_801F4E74 <= 0.01f) {
        globalCtx->unk18874 = 1;
        return;
    }
    Math_SmoothStepToF(&D_801F4E74, 0.0f, 0.2f, 0.02f, 0.001f);
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966B08.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966F74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966FEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809672DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809674C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Draw.asm")
