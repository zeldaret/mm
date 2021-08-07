#include "z_en_kakasi.h"

#define FLAGS 0x02000019

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80970A10(EnKakasi* this, GlobalContext *globalCtx);
void func_8096FC8C(EnKakasi* this);
void func_8096FDE8(EnKakasi* this);

void func_8096F88C(GlobalContext *globalCtx, EnKakasi* this);

void func_8096FCC4(EnKakasi* this, GlobalContext* globalCtx);
void func_8096FE00(EnKakasi* this, GlobalContext* globalCtx);
void func_80970658(EnKakasi* this, GlobalContext* globalCtx);
void func_80970740(EnKakasi* this, GlobalContext* globalCtx);
void func_80970978(EnKakasi* this, GlobalContext* globalCtx);
void func_80970A9C(EnKakasi* this, GlobalContext* globalCtx);
void func_809714BC(EnKakasi* this, GlobalContext* globalCtx);
void func_80971AD4(EnKakasi* this, GlobalContext* globalCtx);
void func_809717D0(EnKakasi* this, GlobalContext* globalCtx);
void func_80971A64(EnKakasi* this, GlobalContext* globalCtx);
void func_8097185C(EnKakasi* this, GlobalContext* globalCtx);
void func_8097193C(EnKakasi* this, GlobalContext* globalCtx);
void func_80971064(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_DoNothing(EnKakasi* this, GlobalContext* globalCtx);
void func_80970F20(EnKakasi* this, GlobalContext* globalCtx);
void func_8097006C(EnKakasi* this, GlobalContext* globalCtx);
void func_809705E4(EnKakasi* this, GlobalContext* globalCtx);

void func_80971794(EnKakasi *this); // dig and leave setup
void func_80970008(EnKakasi* this);
void func_80971440(EnKakasi* this); // setup for digging anime
void func_80971A38(EnKakasi *this);
void func_80970FF8(EnKakasi *this);

void func_80971CE0(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, struct Actor* actor);


static ColliderCylinderInit D_80971D80 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};

const ActorInit En_Kakasi_InitVars = {
    ACTOR_EN_KAKASI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KA,
    sizeof(EnKakasi),
    (ActorFunc)EnKakasi_Init,
    (ActorFunc)EnKakasi_Destroy,
    (ActorFunc)EnKakasi_Update,
    (ActorFunc)EnKakasi_Draw,
};

Vec3f D_80971DCC[] = {
    {0.0f, 60.0f, 60.0f},
    {40.0f, 40.0f, 50.0f},
    {-40.0f, 40.0f, 50.0f},
    {40.0f, 20.0f, 110.0f},
    {-40.0f, 20.0f, 110.0f},
    {0.0f, 80.0f, 60.0f},
    {50.0f, 40.0f, -30.0f},
    {-50.0f, 40.0f, -30.0f},
    {0.0f, 50.0f, 60.0f},
};
Vec3f D_80971E38[] = {
    {0.0f, 55.0f, 60.0f,},
    {0.0f, 55.0f, 60.0f,},
    {-80.0f, 350.0f, 15.0f,},
    {80.0f, 45.0f, 15.0f,},
    {-10.0f, 350.0f, 65.0f,},
    {0.0f, 110.0f, 180.0f,},
    {0.0f, 60.0f, 70.0f,},
    {0.0f, 60.0f, 70.0f,},
    {-80.0f, 50.0f, 40.0f,},
    {0.0f, -10.0f, 50.0f,},
    {80.0f, 50.0f, 40.0f,},
    {0.0f, 120.0f, 40.0f,},
    {0.0f, 28.0f, -50.0f,},
    {0.0f, 60.0f, 50.0f,},
    {0.0f, 80.0f, 160.0f,},
};

Vec3f D_80971EEC[] = {
    {12.0f, 1.0f, 2.0f,},
    {12.0f, 1.0f, 2.0f,},
    {2.0f, -6.0f, 0.0f,},
    {12.0f, -6.0f, -10.0f,},
    {-88.0f, 14.0, -10.0f,},
    {0.0f, 0.0f, 0.0f,},
    {0.0f, 0.0f, 0.0f,},
    {0.0f, 0.0f, 0.0f,},
    {0.0f, -10.0f, 0.0f,},
    {0.0f, -10.0f, 0.0f,},
    {0.0f, -10.0f, 0.0f,},
    {0.0f, -10.0f, 0.0f,},
    {0.0f, -10.0f, 0.0f,},
    {0.0f, 0.0f, 0.0f,},
    {0.0f, 0.0f, 0.0f,},
};

Vec3f D_80971FA0[] = {
    {-50.0f, 160.0f, -40.0f,},
    {-50.0f, 160.0f, -40.0f,},
    {-120.0f, 80.0f, 60.0f,},
    {57.0f, 60.0f, 120.0f,},
    {27.0f, 80.0f, 60.0f,},
    {-3.0f, 50.0f, 70.0f,},
};

Vec3f D_80971FE8[] = {
    {0.0f, 0.0f, 0.0f,},
    {0.0f, 0.0f, 0.0f,},
    {-10.0f, -5.0f, 0.0f,},
    {10.0f, -10.0f, 7.0f,},
    {20.0f, 5.0f, 2.0f,},
    {10.0f, 5.0f, 2.0f,},
};

Vec3f D_80972030 = { -3.0f, 50.0f, 90.0f, };

// offest possition used for digging action func
Vec3f D_8097203C = { 10.0f, -15.0f, 2.0f, };

// rename: animations
AnimationHeaderCommon* D_80972048[] = { 
    0x06007444, 0x0600686C, 0x060081A4, 0x06007B90, 0x060071EC, 0x06007444, 0x0600686C, 0x060081A4,
    0x06000214,
};

// animation mode, passed to SkelAnime_ChangeAnim
u8  D_8097206C[] = {
    0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

void EnKakasi_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnKakasi* this = (EnKakasi*)thisx;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#ifdef NON_MATCHING
// the cutscene loop is wrong, however with the ugly loop:
//   its only regalloc and two instructions swapped
void EnKakasi_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnKakasi* this = (EnKakasi*)thisx;
    s16 zRot;

    int tempCutscene; // permuter swears this is an int, but why
    s32 i;// = 0;
    s16* cutscenePointer;// = this->actorCutscenes;
    //EnKakasi* cutscenePointer;// = this->actorCutscenes;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80971D80);
    SkelAnime_InitSV(globalCtx, &this->skelanime, D_060065B0, D_06000214, 0, 0, 0);

    this->unk250 = ((this->actor.params >> 8) & 0xFF) * 20.0f;
    if (this->unk250 < 40.0f) {
        this->unk250 = 40.0f;
    }

    zRot = this->actor.world.rot.z; // cannot optimize out, we load it before we set to zero
    this->actor.world.rot.z = 0;
    this->actor.targetMode = 0;
    this->unkHeight = (( zRot * 20.0f) + 60.0f);
    if ((this->actor.world.rot.x > 0) && (this->actor.world.rot.x < 8)) {
        this->actor.targetMode = this->actor.world.rot.x - 1;
    }

    this->unk194 = (this->actor.params & 1);
    this->actor.world.rot.x = 0;
    this->actor.flags |= 0x400;
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetScale(&this->actor, 0.01f);

    //for(tempCutscene = this->actor.cutscene; tempCutscene != -1; ++i ){
        //this->actorCutscenes[i] = tempCutscene;
        //tempCutscene = ActorCutscene_GetAdditionalCutscene(tempCutscene);
    //}

    // I'm not entirely convinced it's a for
    //cutscenePointer = this->actorCutscenes;
    //tempCutscene = this->actor.cutscene; // actor->cuscene : 0x38
    //while (tempCutscene != -1 ){
        ////*cutscenePointer = tempCutscene;
        ////tempCutscene = ActorCutscene_GetAdditionalCutscene(tempCutscene);
        //*cutscenePointer = ActorCutscene_GetAdditionalCutscene(cutscenePointer-1);
        //cutscenePointer++;
    //}

    // looks like we point at actor, and offset by the array last second???
    // BEST LOOP CANDIDATE
    cutscenePointer = this;
    tempCutscene = this->actor.cutscene; // actor->cuscene : 0x38
    while (tempCutscene != -1 ){
        ((EnKakasi*) cutscenePointer)->actorCutscenes[0] = tempCutscene;
        tempCutscene = ActorCutscene_GetAdditionalCutscene(tempCutscene);
        cutscenePointer++;
    }

    if (this->unk194 != 0) {
        if ((gSaveContext.weekEventReg[79] & 0x8)) {
          this->unk194 = 2;
          this->unk250 = 80.0f;
          func_80971794(this); //idle after dig
        } else {
            Actor_SetHeight(thisx, 60.0f);
            this->unkFunc = func_8096F88C;
            if ((gSaveContext.weekEventReg[83] & 0x1)) {
                func_8096FC8C(this);
            } else {
                func_8096FDE8(this);
            }
        }
    } else {
       func_80971794(this); //idle after dig
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/EnKakasi_Init.s")
#endif

// I messed up, now that I changed this the nonmatching cannot use it
// EnKakasi_SetAnimation
void func_8096F800(EnKakasi *this, s32 index) { // func_8096F800
    this->animeIndex = index;
    this->animeFrameCount = SkelAnime_GetFrameCount(D_80972048[this->animeIndex]);
    // 1: regular playback speed, 0: starting frame
    SkelAnime_ChangeAnim(&this->skelanime, (AnimationHeader*) D_80972048[this->animeIndex],
         1.0f, 0.0f, this->animeFrameCount, 
         D_8097206C[this->animeIndex], -4.0f);
}

// set by init, called... nowhere? left over from OOT?
void func_8096F88C(GlobalContext *globalCtx, EnKakasi* this) {
    func_8013A530(globalCtx, &this->actor, 0x7, 
        &this->actor.focus.pos, &this->actor.shape.rot, 280.0f, 1800.0f, -1);
}

// goes off every frame of idle if draw is set
void func_8096F8D8(EnKakasi *this) {
    if ((this->animeIndex == 1) || (this->animeIndex == 5)) {
        if ((func_801378B8(&this->skelanime, 1.0f) != 0) 
          || (func_801378B8(&this->skelanime, 8.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KAKASHI_SWING);
        }
    }
    if ((this->animeIndex == 2) || (this->animeIndex == 7)) {
        if ((func_801378B8(&this->skelanime, 4.0f) != 0) 
          || (func_801378B8(&this->skelanime, 8.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KAKASHI_SWING);
        }
        if ((func_801378B8(&this->skelanime, 1.0f) != 0) 
          || (func_801378B8(&this->skelanime, 9.0f) != 0) 
          || (func_801378B8(&this->skelanime, 16.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_IT_KAKASHI_JUMP);
        }
        if (func_801378B8(&this->skelanime, 18.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KAKASHI_ROLL);
        }
    }
    if ((this->animeIndex == 3) || (this->animeIndex == 4)) {
        if (func_801378B8( &this->skelanime, 1.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KAKASH_LONGI_ROLL);
        }
    }
}

// moves the player's position relative to scarecrow during song teach, also each frame of dance the night away
void func_8096FA18(EnKakasi *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    s16 sceneNum;

    sceneNum = globalCtx->sceneNum;
    if (sceneNum == SCENE_8ITEMSHOP) {
        player->actor.world.pos.x = -50.0f;
        player->actor.world.pos.z = 155.0f;
    } else if (sceneNum == SCENE_TENMON_DAI) {
        player->actor.world.pos.x = 60.0f;
        player->actor.world.pos.z = -190.0f;
    }

    Math_SmoothStepToS(&player->actor.shape.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 5, 0x3E8, 0);
}

// this goes off every frame of dancing the night away, and song teaching
void func_8096FAAC(EnKakasi *this, GlobalContext* globalCtx) {
    if (this->cutsceneCamera != 0) {
        Math_ApproachF(&this->unk214.x, this->unk238.x, 0.40000000596f, 4.0f);
        Math_ApproachF(&this->unk214.y, this->unk238.y, 0.40000000596f, 4.0f);
        Math_ApproachF(&this->unk214.z, this->unk238.z, 0.40000000596f, 4.0f);

        Math_ApproachF(&this->unk220.x, this->unk244.x, 0.40000000596f, 4.0f);
        Math_ApproachF(&this->unk220.y, this->unk244.y, 0.40000000596f, 4.0f);
        Math_ApproachF(&this->unk220.z, this->unk244.z, 0.40000000596f, 4.0f);
        
        Math_ApproachF(&this->unk20C, this->unk210, 0.3f, 10.0f);
        
        func_8016970C(globalCtx, this->cutsceneCamera, &this->unk220, &this->unk214);
        func_80169940(globalCtx, this->cutsceneCamera, this->unk20C);
    }
}

// goes off every frame of song teach
void func_8096FBB8(EnKakasi* this, GlobalContext* globalCtx) {
    if ((globalCtx->msgCtx.unk12048 == 0) || (globalCtx->msgCtx.unk12048 == 1) || (globalCtx->msgCtx.unk12048 == 2) 
      || (globalCtx->msgCtx.unk12048 == 3) || (globalCtx->msgCtx.unk12048 == 4)) {
        this->unk190++;
    }
    if ((this->unk190 != 0) && (this->animeIndex != 1)) {
        func_8096F800(this, 1);
    }
    if (this->unk190 >= 9) {
        this->unk190 = 8;
    }
    if (this->unk190 != 0) {
        Math_ApproachF(&this->skelanime.animPlaybackSpeed, 1.0f, 0.1f, 0.2f);
        this->actor.shape.rot.y = this->actor.shape.rot.y + 0x800;
    }
}

// init extension
void func_8096FC8C(EnKakasi *this) {
    func_8096F800(this, 7);
    this->actionFunc = func_8096FCC4;
}

// action func
// goes off every frame after scene reload after dancing all night action (fade from black, pause for dawn of day text, continue until he starts talking)
void func_8096FCC4(EnKakasi* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((gSaveContext.respawnFlag != -4) && (gSaveContext.respawnFlag != -8)) {
        if ((gSaveContext.time != 0x4000) && (gSaveContext.time != 0xC000) 
          && ((gSaveContext.eventInf[1] & 0x80) == 0)) {
            if (this->actor.textId == 0) {
            // "Oh, yeah!  How was it? It went by in an instant, right?  I'm still full of energy!"
                this->actor.textId = 0x1653;
                gSaveContext.weekEventReg[0x53] &= 0xFE;
                this->unk1AC = 5;
                player->stateFlags1 |= 0x20;
                this->actor.flags |= 0x10000;
            }
            if (func_800B84D0(&this->actor, globalCtx) != 0) {
                player->stateFlags1 &= ~0x20;
                this->unk196 = 2;
                this->actor.flags &= ~0x10000;
                this->actionFunc = func_8097006C;
            } else {
                func_800B8500(&this->actor, globalCtx, 9999.90039062f, 9999.90039062f, -1);
            }
        }
    }
}

// init extension standing
void func_8096FDE8(EnKakasi* this) {
    this->unk196 = 0;
    this->actionFunc = func_8096FE00; // regular idle func
}

// action func
//  EnKakasi_Idle
void func_8096FE00(EnKakasi* this, GlobalContext *globalCtx) {
    u32 saveContextDay;
    s16 passedValue1;
    s16 passedValue2;

    saveContextDay = gSaveContext.day;
    // "Yo! Hey, baby!  I'm a stylin' scarecrow wandering in search of pleasant music.
    // Time will pass in the blink of an eye if you dance with me."
    this->actor.textId = 0x1644;
    if (func_800B8718(this, globalCtx) != 0) {
        this->skelanime.animPlaybackSpeed = 1.0f;
        func_809705E4(this, globalCtx);
        return;
    }
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->skelanime.animPlaybackSpeed = 1.0f;
        func_80970008(this);
        return;
    }
    if ((globalCtx->actorCtx.unk5 & 0x4)) {
        func_800B8898(globalCtx, &this->actor, &passedValue1, &passedValue2);
        if ((this->actor.projectedPos.z > -20.0f) 
          && ((s32) passedValue1 > 0) && ((s32) passedValue1 < 0x140) 
          && ((s32) passedValue2 > 0) && ((s32) passedValue2 < 0xF0) && (this->animeIndex != 1)) {
            func_8096F800(this, 1);
            this->skelanime.animPlaybackSpeed = 2.0f;
        }
    } else if (Player_GetMask(globalCtx) == 0xE) { // wearing kamaro mask
        if (this->animeIndex != 1) {
            func_8096F800(this, 1);
            this->skelanime.animPlaybackSpeed = 2.0f;
        }
    } else if ((saveContextDay == 3) && (gSaveContext.isNight)) {
        this->skelanime.animPlaybackSpeed = 1.0f;
        if (this->animeIndex != 1) {
            func_8096F800(this, 1);
        }
    } else if (this->animeIndex != 8) {
        func_8096F800(this, 8);
    }
    if (this->actor.xzDistToPlayer < 120.0f) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
        func_800B874C(&this->actor, globalCtx, 100.0f, 80.0f);
    }
}

// goes off once when you start talking to him from idle, but NOT from day/night transition
void func_80970008(EnKakasi *this) {
    if (this->animeIndex != 1) {
        func_8096F800(this, 1);
    }

    this->unk1AC = 5;
    this->unk196 = 1;
    func_8096F800(this, 3);
    this->actionFunc = func_8097006C;
}

// action func
// goes off when just talking to him, includes talking after song teach failure
#if NON_MATCHING
// there is some out of order instructions around saveContextDay2
// also the control flow gets confused near 70% down, but it's only one instruction off
void func_8097006C(EnKakasi* this, GlobalContext* globalCtx) {
    // prob save context var
    //SaveContext* sCtx;// = &gSaveContext;
    u32 saveContextDay = gSaveContext.day; 
    f32 currentAnimeFrame = this->skelanime.animCurrentFrame;
    u32 saveContextDay2;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x7D0, 0);
    // "Yo! Hey, baby!  I'm a stylin' scarecrow wandering in search of pleasant music.
    // Time will pass in the blink of an eye if you dance with me."
    if ((this->actor.textId != 0x1644) && (this->animeFrameCount <= currentAnimeFrame) 
      && (this->animeIndex == 7)) {
        func_8096F800(this, 3);
        this->unkCounter1A4 = 0;
    }

    // "Oh, sorry. That's too bad. In that case, come back anytime if you do ...
                // "How's that? Pretty interesting, isn't it?  But I'm sure I'd like any song 
    if ((this->actor.textId == 0x1651) || (this->actor.textId == 0x1659)) {
        if ((this->animeFrameCount <= currentAnimeFrame) && (this->animeIndex != 3)) {
            if (++this->unkCounter1A4 >= 2) {
                this->unkCounter1A4 = 0;
                func_8096F800(this, 3);
            }
        }
    }

    if ((this->unk1A8 == 2) && (this->unk196 == 2)) {
        func_800B7298(globalCtx, &this->actor, 0x49);
        this->unk1A8 = 0;
    }

    if ((this->unk1AC == func_80152498(&globalCtx->msgCtx)) && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);
        if (this->unk1AC == 5) {
            // "No, no, daddy-o!  That song doesn't sing to my heart, baby!"
            if ((this->unk196 == 2) && (this->actor.textId == 0x1647)) {
                func_800B7298(globalCtx, &this->actor, 6);
            }

            // "Oh, yeah!  How was it? It went by in an instant, right?  I'm still full of energy!"
            if (this->actor.textId == 0x1653) {
                // this is the only way i've found to get savecontext to load twice and use the right v
                saveContextDay2 = gSaveContext.day; // I hope this is a fake match

                // 1A0 loads AFTER globalcontext from above in vanilla
                // also delay slot shenanigans
                //fake_label: ;
                if (this->animeIndex != 1) {
                    func_8096F800(this, 1);
                }
        
                //if ((gSaveContext.day == 3) && (gSaveContext.isNight != 0)) {
                if ((saveContextDay2 == 3) && (gSaveContext.isNight != 0)) {
                    // "But outside it seems to have gotten kind of...dangerous.
                    this->actor.textId = 0x164F;
                } else if (gSaveContext.isNight != 0) {
                    // "If you like, baby, we can forget the time and dance 'til dawn!"
                    this->actor.textId = 0x164E;
                } else {
                    // "If you like, baby, we can forget the time and dance until night!"
                    this->actor.textId = 0x1645;
                }

                func_80151938(globalCtx, this->actor.textId);
                return;

            // "Oh, sorry! That's too bad.  In that case, see you later!"
            // "Want to learn it?  No Yes"
                // "How's that? Pretty interesting, isn't it?  If you learn a new song ...
                    // "Oh, yeah!  In that case, forget the time.  Let's dance!"
            } else if ((this->actor.textId == 0x165D) || (this->actor.textId == 0x165F)
              || (this->actor.textId == 0x1660) || (this->actor.textId == 0x1652)) {
                goto dummy_label_845001; dummy_label_845001: ;
                func_800B7298(globalCtx, &this->actor, 4);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                    ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                    this->actionFunc = func_80970F20;
                    return;
                } else { 
                    if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
                        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                        this->actionFunc = func_80970F20;
                        return;
                    } else {
                        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
                        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
                        this->actionFunc = func_80970F20;
                        //return;
                    }
                }

            // "If you like, baby, we can forget the time and dance 'til dawn!"
            } else if ((this->actor.textId == 0x1645) || (this->actor.textId == 0x164E)) {
                this->actor.textId = 0x1650;
                if (this->animeIndex != 1) {
                    func_8096F800(this, 1);
                }
                this->unk1AC = 4;

            // "Yo! Hey, baby!  I'm a scarecrow wandering in search of music.
            // Time will pass in the blink of an eye if you dance with me."
            } else if (this->actor.textId == 0x1644) {
                if (this->animeIndex != 1) {
                    func_8096F800(this, 1);
                }
                if (gSaveContext.isNight != 0) {
                    // "If you like, baby, we can forget the time and dance 'til dawn!"
                    this->actor.textId = 0x164E;
                } else {
                    // "If you like, baby, we can forget the time and dance until night!"
                    this->actor.textId = 0x1645;
                }
  
                    // "But outside it seems to have gotten kind of...dangerous.
            } else if (this->actor.textId == 0x164F) {
                if (this->animeIndex != 1) {
                    func_8096F800(this, 1);
                }
                // Take care...
                this->actor.textId = 0x165A;
            // "Oh, sorry. That's too bad. In that case, come back anytime if you do ...
            } else if (this->actor.textId == 0x1651) {
                if (this->animeIndex != 1) {
                    func_8096F800(this, 1);
                }
                this->actor.textId = 0x1654;
            } else if (this->actor.textId == 0x1654) {
                this->actor.textId = 0x1655;
            } else if (this->actor.textId == 0x1655) {
                // "Do you want to learn it?  No Yes"
                this->actor.textId = 0x1656;
                this->unk1AC = 4;
            // "Oh, yeah!  Now listen up!  If you play that strange song...
            } else if (this->actor.textId == 0x1658) {
                // "How's that? Pretty interesting, isn't it?  But I'm sure I'd like any song 
                this->actor.textId = 0x1659;
            // Take care...
            } else if (this->actor.textId == 0x165A) {
                // "I know of a mysterious song that allows you to manipulate the flow ..
                this->actor.textId = 0x165B;
                // "I know of a mysterious song that allows you to manipulate the flow ..
            } else if (this->actor.textId == 0x165B) {
                // "Would you like to learn it?  No Yes"
                this->actor.textId = 0x165C;
                this->unk1AC = 4;

            // around here the control flow gets confused
            } else if (this->actor.textId == 0x165E) {
                // "How's that? Pretty interesting, isn't it?  If you learn a new song ...
                this->actor.textId = 0x165F;
                //return;
            }else{
                func_8096FDE8(this);
                //return;
            }
                //if (this->actor.textId == 0x165E) {
                    //this->actor.textId = 0x165F;
                    //return;
                //}else{
                    //func_8096FDE8(this);
                    //return;
                //}
                    //return;
            return;
        } else {
            this->unk1AC = 5;

            if (globalCtx->msgCtx.choiceIndex == 1) {
                func_8019F208(); // play 0x4808 sfx (decide) and calls func_801A75E8
                // "Do you want to learn it?  No Yes"
                if (this->actor.textId == 0x1656) {
                    // "Oh, yeah!  Now listen up!  If you play that strange song ...
                    this->actor.textId = 0x1658;
                // "Would you like to learn it?  No Yes"
                } else if (this->actor.textId == 0x165C) {
                    this->actor.textId = 0x165E;
                } else if ((saveContextDay == 3) && (gSaveContext.isNight != 0)) {
                    // "But outside it seems to have gotten kind of...dangerous.
                    this->actor.textId = 0x164F;
                } else {
                    // "Oh, yeah!  In that case, forget the time.  Let's dance!"
                    this->actor.textId = 0x1652;
                }
                func_8096F800(this, 2);
            } else {
                func_8019F230(); // play 0x480A sfx (cancel) and calls func_801A75E8
                // "Do you want to learn it?  No Yes"
                if (this->actor.textId == 0x1656) {
                    this->actor.textId = 0x1657;
                // "Would you like to learn it?  No Yes"
                } else if (this->actor.textId == 0x165C) {
                    // "Oh, sorry! That's too bad.  In that case, see you later!"
                    this->actor.textId = 0x165D;
                } else {
                  // "Oh, sorry. That's too bad. In that case, come back anytime if you do ...
                    this->actor.textId = 0x1651;
                }
                this->unkCounter1A4 = 0;
                if (this->animeIndex != 0) {
                    func_8096F800(this, 0);
                }
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8097006C.s")
#endif

// setup for.. ?
void func_809705E4(EnKakasi* this, GlobalContext* globalCtx) {
    // "Oh, baby!  That's a nice thing you got there!  Let me hear a song you wrote on that!"
    this->actor.textId = 0x1646;
    func_801518B0(globalCtx, this->actor.textId, &this->actor);
    this->cutsceneCamera = 0;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    func_8096F800(this, 4);
    this->unk196 = 2;
    this->actionFunc = func_80970658;
}

//action func
// goes off every frame he notices you have an ocarina and is still talking, not learning notes
void func_80970658(EnKakasi* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        func_80152434(globalCtx, 0x35);
        this->unk1A8 = 0;
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            this->actionFunc = func_80970740;//songteaching

        } else if (ActorCutscene_GetCanPlayNext((s16) this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay((s16) this->actorCutscenes[0]);
            this->actionFunc = func_80970740;//songteaching

        } else {
            this->unk1A8 = 1;
            ActorCutscene_StartAndSetUnkLinkFields((s16) this->actorCutscenes[0], &this->actor);
            this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
            Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
            this->actionFunc = func_80970740;//songteaching
        }
    }
}

// action func: each frame of songteaching
void func_80970740(EnKakasi* this, GlobalContext* globalCtx) {
    Vec3f tempVec;

    func_8096FA18(this, globalCtx); // move player in front of scarecrow
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    if (this->unk1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        this->unk1A8 = 1;
        this->unk1A8 = 1;
    }
  
    if (this->unk1A8 == 1) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80971DCC[(s16)this->unk190].x;
        this->unk238.y = D_80971DCC[(s16)this->unk190].y;
        this->unk238.z = D_80971DCC[(s16)this->unk190].z;

        Math_Vec3f_Copy(&tempVec,  &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home.pos, &tempVec, &this->unk238, 1);
        Math_Vec3f_Copy(&this->unk244, &this->unk22C);
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
        func_8096FBB8(this, globalCtx);

        if (globalCtx->msgCtx.unk1202A == 4) {
            this->unk190 = 0;
            this->unkCounter1A4 = 0;
            ActorCutscene_Stop(this->actorCutscenes[0]);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_YASE_DEAD);
            if (!this){}
            this->unk196 = 2;
            this->cutsceneCamera = 0;
            // "No, no, daddy-o!  That song doesn't sing to my heart, baby!"
            this->actor.textId = 0x1647;
            this->unk1A8 = 2;
            this->unk1AC = 5;
            func_8096F800(this, 0);
            this->actionFunc = func_8097006C;

        } else if (globalCtx->msgCtx.unk1202A == 3) {
            this->unk192 = 0x1E;
            this->skelanime.animPlaybackSpeed = 2.0f;
            func_8096F800(this, 2);
            this->actionFunc = func_80970978;//post-song-teach twirl
        }
    }
}

// action func
// every frame of his post-song-learn twirl
// uncompresed rom: 8041D378
void func_80970978(EnKakasi* this, GlobalContext *globalCtx) {
    f32 tempAnimeFrame;
    s16 temp192;
  
    // 192 at this spot is 1D and counts down per frame until zero
    temp192 = this->unk192;
    tempAnimeFrame = this->skelanime.animCurrentFrame;
    if (temp192 == 0 && this->animeIndex != 4) {
        func_8096F800(this, 4);
        this->skelanime.animPlaybackSpeed = 2.0f;
        temp192 = this->unk192;
    }
    if ((temp192 == 0) && (this->animeIndex == 4) && (this->animeFrameCount <= tempAnimeFrame)) {
        func_80970A10(this, globalCtx);
    }
}

// goes off at the very tail end of song teaching twirl, when he starts speaking again
void func_80970A10(EnKakasi *this, GlobalContext *globalCtx) {
    ActorCutscene_Stop(this->actorCutscenes[0]);
    globalCtx->msgCtx.unk1202A = 4;
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    func_8096F800(this, 2);
    this->cutsceneCamera = 0;
    this->unk1AC = 5;
    this->unk1A8 = 1;
    this->actionFunc = func_80970A9C;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
}

// action func
//  think this is the post-song teaching action func
void func_80970A9C(EnKakasi* this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    f32 tempAnimFrame; // needed to get the frame to load earlier?
    Vec3f vec3fCopy;

    tempAnimFrame = this->skelanime.animCurrentFrame;
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    Math_SmoothStepToS(&player->actor.shape.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 5, 0x3E8, 0);

    // this is setup, only goes off first frame
    if ((s16) this->unk190 == 0) {
        func_801477B4(globalCtx);
        func_800B7298(globalCtx, &this->actor, 0x56);
        // "Yow! Oh, yeah!  That's a nice tune, baby.  By the way..."
        this->actor.textId = 0x1648;
        func_801518B0(globalCtx, (this->actor.textId), &this->actor);
        this->unk1A8 = 0;
        this->unk190 = 1;
    }
    
    // "Yow! Oh, yeah!  That's a nice tune, baby.  By the way..."
    if ((this->actor.textId == 0x1648) && (this->animeIndex == 2) && (this->animeFrameCount <= tempAnimFrame)) {
        this->unkCounter1A4++;
        if (this->unkCounter1A4>= 2) {
            func_8096F800(this, 0); // reach this point when he finishes dancing idle
        }
    }
    if ((this->actor.textId == 0x164B) && (this->animeIndex == 0) && (this->animeFrameCount <= tempAnimFrame)) {
        this->unkCounter1A4++;
        if (this->unkCounter1A4 >= 2) {
            func_8096F800(this, 3);
        }
    }

    if (this->unk1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        func_800B7298(globalCtx, &this->actor, 0x56);
        this->unk1A8 = 1;
    }

    if (this->cutsceneCamera != 0) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        func_8096FA18(this, globalCtx); // move player in front of scarecrow
        this->unk238.x = D_80971FA0[this->unk190].x;
        this->unk238.y = D_80971FA0[this->unk190].y;
        this->unk238.z = D_80971FA0[this->unk190].z;
        Math_Vec3f_Copy(&vec3fCopy, &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home.pos, &vec3fCopy, &this->unk238, 1);
        this->unk244.x = D_80971FE8[(s16) this->unk190].x + this->unk22C.x;
        this->unk244.y = D_80971FE8[(s16) this->unk190].y + this->unk22C.y;
        this->unk244.z = D_80971FE8[(s16) this->unk190].z + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }

    func_8096FAAC(this, globalCtx);

    if ((this->unk1A8 != 0) && (func_80152498(&globalCtx->msgCtx) == this->unk1AC) 
    && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);

        if (this->unk1AC == 5) {
            this->unk190++;
            if ((s32) (s16) this->unk190 >= 6) {
                this->unk190 = 5;
            }

            // "Yow! Oh, yeah!  That's a nice tune, baby.  By the way..."
            if (this->actor.textId == 0x1648) {
                func_800B7298(globalCtx, &this->actor, 7);
                // "I know of a mysterious song that allows you to manipulate the flow of time..."
                this->actor.textId = 0x1649;
                if (this->animeIndex != 0) {
                    func_8096F800(this, 0);
                }

            // "I know of a mysterious song that allows you to manipulate the flow of time..."
            } else if (this->actor.textId == 0x1649) {
                // "Want to learn it?  No Yes"
                this->actor.textId = 0x1660;
                this->unk1AC = 4;

            // "Oh, yeah!  Now listen up!  If you play that mysterious song ...
            } else if (this->actor.textId == 0x164A) {
                // "How's that? Pretty interesting, isn't it?  But I like the song you played ..
                this->actor.textId = 0x164B;

            // "How's that? Pretty interesting, isn't it?  But I like the song you played ..
            } else if (this->actor.textId == 0x164B) {
                // "If you want to see me again, play that song you wrote for me here ...
                this->actor.textId = 0x164C;
                func_8096F800(this, 4);

            } else {
                // "If you want to see me again, play that song you wrote for me here ...
                // "Oh, sorry. That's too bad.  If you'd like to see me again, play ...
                if ((this->actor.textId == 0x164C) || (this->actor.textId == 0x1661)){
                    func_80971440(this); //setup for digging anime
                    return;
                }
            }

        } else {
            this->unk1AC = 5;
            // 16929 / 4908 / (12021)
            if (globalCtx->msgCtx.choiceIndex == 1) {
                func_8019F208(); // play 0x4808 sfx (decide) and calls func_801A75E8
                // "Oh, yeah!  Now listen up!  If you play that mysterious song ...
                this->actor.textId = 0x164A;
            } else {
                func_8019F230(); // play 0x480A sfx (cancel) and calls func_801A75E8
                // "Oh, sorry. That's too bad.  If you'd like to see me again, play ...
                this->actor.textId = 0x1661;
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
} // */

// action func
// goes off once at the start of dancing the night away, one frame, like a setup action func
void func_80970F20(EnKakasi* this, GlobalContext *globalCtx) {
    u32 currentDay = gSaveContext.day;

    this->unk196 = 3;
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
    } else if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
    } else  {

        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if ((currentDay == 3) && (gSaveContext.isNight)) {
            func_80971440(this); //setup for digging anime
        } else {
            func_801A2BB8(0x3E);
            func_80970FF8(this);
        }
    }
}

// never goes off in the shop
void func_80970FF8(EnKakasi *this) {
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    func_8096F800(this, 4);
    Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
    func_8016566C(0xB4);
    this->actionFunc = func_80971064;
}

//action func
// guessing since this ends with a worthless action func it leads to the actor leaving
// no? it never goes off while he's leaving the hell? 8041DA64
void func_80971064(EnKakasi* this, GlobalContext* globalCtx) {
    //EnKakasi* this= (EnKakasi*)thisx; // matches without, leaving as EnKakasi* this for now
    f32 currentFrame;
    Vec3f localVec3f;
    Player* player;

    currentFrame = this->skelanime.animCurrentFrame;
    func_8096FA18(this, globalCtx); // move player in front of scarecrow
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    this->unk22C.y = this->actor.home.pos.y + 50.0f;

    this->unk238.x = D_80971E38[this->unk190].x;
    this->unk238.y = D_80971E38[this->unk190].y;
    this->unk238.z = D_80971E38[this->unk190].z;
    Math_Vec3f_Copy(&localVec3f, &this->unk238);
    OLib_DbCameraVec3fSum(&this->actor.home.pos, &localVec3f, &this->unk238, 1);

    // we assign unk244 here but then under the next condition we set unk220->unk244?
    // bug? think this condition was supposed to important, was optimized out without knowing
    if (1) {
        this->unk244.x = D_80971EEC[this->unk190].x + this->unk22C.x;
        this->unk244.y = D_80971EEC[this->unk190].y + this->unk22C.y;
        this->unk244.z = D_80971EEC[this->unk190].z + this->unk22C.z;
    }
    if ((this->unk190 != 6) && (this->unk190 != 7)) {
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }
    if ((this->unk190 >= 7) && (this->unk190 != 0xE)) {
        this->actor.shape.rot.y = this->actor.shape.rot.y + 0x800;
    }

    func_8096FAAC(this, globalCtx);
    switch (this->unk190) {
        case 0:
            this->unk204 = 0x28;
            this->unk190++;
            return;
        case 1:
            if ((this->unk204 == 0) && (this->animeFrameCount <= currentFrame)) {
                this->unk204 = 0x14;
                this->unk190++;
                func_8096F800(this, 1);
            }
            return;
        case 2:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 3:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 4:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 5:
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 6:
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 7:
            if (this->unk204 == 0) {
                this->unk204 = 0xA;
                this->unk190++;
            }  
            return;
        case 8:
            if (this->unk204 == 0) {
                this->unk190++;
                this->unk204 = 0xA;
                if (this->unk190 == 0xE) {
                    func_800B7298(globalCtx, &this->actor, 0x49);
                    func_80165690();
                    this->unk204 = 0x14;
                }
            }
            return;
        case 14:
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
            if (this->unk204 == 0) {
                player = PLAYER;
                func_80169DCC(globalCtx, 0, Entrance_CreateIndexFromSpawn(0), 
                    player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                func_80169EFC(globalCtx);

                if(0){}
                if ((gSaveContext.time >= 0xC001) || (gSaveContext.time < 0x4000)) {
                    gSaveContext.time = 0x4000;
                    gSaveContext.respawnFlag = -4;
                    gSaveContext.eventInf[2] |= 0x80;
                } else {
                    gSaveContext.time = 0xC000;
                    gSaveContext.respawnFlag = -8;
                }
                gSaveContext.weekEventReg[0x53] |= 1;
                this->unk190 = 0;
                this->actionFunc = EnKakasi_DoNothing;
            }
            return;
    }
    return;
}

void EnKakasi_DoNothing(EnKakasi* this, GlobalContext* globalCtx) { }

// setup for digging animation
void func_80971440(EnKakasi *this){
    if (this->animeIndex != 1) {
        func_8096F800(this, 1);
    }
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    this->unk210 = 60.0f;
    this->unk20C = 60.0f;
    Math_Vec3f_Copy(&this->unk22C,  &this->actor.home.pos);
    this->unk196 = 4;
    this->actionFunc = func_809714BC;
}

// action func
// this is him digging away after song teach
void func_809714BC(EnKakasi* this, GlobalContext *globalCtx) {
    Vec3f tempunk238; // two are required as one is sp40 and one sp4C
    Vec3f tempWorldPos;

    if (this->cutsceneCamera != 0) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80972030.x;
        this->unk238.y = D_80972030.y;
        this->unk238.z = D_80972030.z;

        Math_Vec3f_Copy( &tempunk238, &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home.pos, &tempunk238, &this->unk238, 1);
        this->unk244.x = ((float)D_8097203C.x) + this->unk22C.x; //float cast is req to stop regalloc
        this->unk244.y = ((float)D_8097203C.y) + this->unk22C.y;
        this->unk244.z = ((float)D_8097203C.z) + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
    }

    if (this->unkCounter1A4 < 0xF) {
        this->unkCounter1A4++;
        return;
    }

    this->actor.shape.rot.y = this->actor.shape.rot.y + 0x3000;
    Math_SmoothStepToS(&this->unk190, 0x1F4, 5, 0x32, 0);
    if ((globalCtx->gameplayFrames & 3) == 0) {
        Math_Vec3f_Copy( &tempWorldPos,  &this->actor.world.pos);
        tempWorldPos.y = this->actor.floorHeight;
        tempWorldPos.x += randPlusMinusPoint5Scaled(2.0f);
        tempWorldPos.z += randPlusMinusPoint5Scaled(2.0f);

        if (globalCtx->sceneNum == SCENE_8ITEMSHOP) {
            EffectSsGSplash_Spawn(globalCtx, &tempWorldPos, 0, 0, 0, (s32) (randPlusMinusPoint5Scaled(100.0f) + 200.0f));
            func_800F0568(globalCtx, &tempWorldPos, 0x32, NA_SE_EV_BOMB_DROP_WATER);

        } else {
            func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos,
                 this->actor.shape.shadowScale - 20.0f, 5,
                 4.0f, 0xC8, 0xA, 1);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
    }

    Math_ApproachF(&this->actor.shape.yOffset, -6000.0f, 0.5f, 200.0f);
    if (fabsf(this->actor.shape.yOffset + 6000.0f) < 10.0f) {
        gSaveContext.weekEventReg[79] |= 8;
        func_800B7298(globalCtx, &this->actor, 6);
        ActorCutscene_Stop(this->actorCutscenes[0]);
        this->unk194 = 2;
        this->unk250 = 80.0f;
        func_80971794(this); // idle after dig
    }
}

// setup hiding in the ground
void func_80971794(EnKakasi *this) {
    this->actor.shape.yOffset = -7000.0;
    this->actor.draw = NULL;
    this->actor.flags |= 0x8000000;
    this->unk196 = 5;
    this->actionFunc = func_809717D0;
}

// action func
// resting in the ground after you he leaves having learned a song
void func_809717D0(EnKakasi* this, GlobalContext* globalCtx) {
    //if (((*(&gSaveContext + 0xF47) & 8) != 0) && (this->actor.xzDistToPlayer < this->unk250)) {
    if (((gSaveContext.weekEventReg[79] & 0x8)) 
        && (this->actor.xzDistToPlayer < this->unk250)
        && ((gGameInfo->data[2401] != 0) || (globalCtx->msgCtx.unk1202A == 0xD)) ) {
            this->actor.flags &= 0xF7FFFFFF;
            globalCtx->msgCtx.unk1202A = 4;
            this->actionFunc = func_8097185C;
    }
}

//action func
void func_8097185C(EnKakasi* this, GlobalContext *globalCtx) {
    s32 cutsceneIndex;

    cutsceneIndex = 0;
    if (this->unk194 == 2) {
        cutsceneIndex = 1;
    }
    
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[cutsceneIndex]);

    } else if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[cutsceneIndex]) == 0) {
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[cutsceneIndex]);

    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[cutsceneIndex], &this->actor);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actor.draw = EnKakasi_Draw;
        this->unk196 = 6;
        this->actionFunc = func_8097193C;
    }
}

//action func
void func_8097193C(EnKakasi* this, GlobalContext *globalCtx) {
    this->actor.shape.rot.y += 0x3000;

    if (this->animeIndex != 1) {
        func_8096F800(this, 1);
    }
    if (this->actor.shape.yOffset < -10.0f) {
        if ((globalCtx->gameplayFrames & 7) == 0) {
            func_800BBDAC(globalCtx, &this->actor, 
                &this->actor.world.pos, this->actor.shape.shadowScale - 20.0f,
                0xA, 8.0f, 500, 0xA, 1);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
        Math_ApproachF(&this->actor.shape.yOffset, 0.0f, 0.5f, 200.0f);
        return;
    }
    func_80971A38(this);
}

void func_80971A38(EnKakasi *this) {
    this->actor.textId = 0x164D;
    this->unk196 = 7;
    this->actionFunc = func_80971A64;
    this->actor.shape.yOffset = 0.0f;
}

// action func
void func_80971A64(EnKakasi* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80971AD4;
    } else {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

// action func
void func_80971AD4(EnKakasi* this, GlobalContext *globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
    
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);
        func_80971A38(this);
    }
}

void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = (EnKakasi*)thisx;
    s32 pad;

    SkelAnime_FrameUpdateMatrix(&this->skelanime);
    if (this->actor.draw != 0) {
        func_8096F8D8(this);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    DECR(this->unk192);
    DECR(this->unk204);

    if ((s16) this->unk196 != 5) {
        if (( this->unk1BC.x != 0.0f) || (this->unk1BC.z != 0.0f)) {
            Math_Vec3f_Copy( &this->actor.focus.pos,  &this->unk1BC);
            this->actor.focus.pos.y += 10.0f;
            if (this->cutsceneCamera == 0) {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            } else {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.home.rot);
            }
        }
    } else {
        Actor_SetHeight(&this->actor,  this->unkHeight);
    }

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 0x1C);
    if (this->actor.draw != 0) {
        Collider_UpdateCylinder( &this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

// post limb draw func
void func_80971CE0(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor) {
    EnKakasi* this = (EnKakasi*) actor;
    if (limbIndex == 4) {
        // what is D_801D15B0 ? we didn't have to define it, we store the output though
        SysMatrix_MultiplyVector3fByState(&D_801D15B0, &this->unk1BC); //first is src, second is dest
    }
}

void EnKakasi_Draw(Actor* thisx, GlobalContext *globalCtx) { 
    EnKakasi* this = (EnKakasi*)thisx;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelanime.skeleton,
       this->skelanime.limbDrawTbl, (s32) this->skelanime.dListCount, NULL, func_80971CE0, &this->actor);

}
