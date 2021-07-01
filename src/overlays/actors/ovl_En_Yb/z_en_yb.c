#include "z_en_yb.h"

#define FLAGS 0x02000019

#define THIS ((EnYb*)thisx)

//void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnYb_Init(EnYb* this, GlobalContext* globalCtx);
void EnYb_Draw(EnYb* this, GlobalContext* globalCtx);

void func_80BFAC88(EnYb* this, GlobalContext* globalCtx);
void func_80BFAE80(EnYb* this, GlobalContext* globalCtx);
void func_80BFA730(EnYb* this, GlobalContext* globalCtx);
void func_80BFA91C(EnYb* this, GlobalContext* globalCtx);
void func_80BFA9D4(EnYb* this, GlobalContext* globalCtx);
void func_80BFAB4C(EnYb* this, GlobalContext* globalCtx);
void func_80BFABF0(EnYb* this, GlobalContext* globalCtx);
void func_80BFA868(EnYb* this, GlobalContext* globalCtx);

void func_80BFA634(EnYb* this, GlobalContext* globalCtx);
s32 func_80BFA5CC(EnYb* this, GlobalContext* globalCtx); 
void func_80BFA67C(EnYb* this);

// custom shadow function neat
//typedef void(*ActorShadowFunc)(struct Actor* actor, struct Lights* mapper, struct GlobalContext* globalCtx);
void func_80BFA350(struct Actor* actor, struct Lights* mapper, struct GlobalContext* globalCtx);

void func_80BFA444(GlobalContext* globalCtx, EnYb* this, s16 arg3, s16 arg4, f32 arg5);

/*
const ActorInit En_Yb_InitVars = {
    ACTOR_EN_YB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_YB,
    sizeof(EnYb),
    (ActorFunc)EnYb_Init,
    (ActorFunc)EnYb_Destroy,
    (ActorFunc)EnYb_Update,
    (ActorFunc)EnYb_Draw,
};
*/

extern u32 D_80BFB2B0;

extern u32 D_06005F48;
extern u32 D_06000200;
extern u32 D_80BFB2E8;

extern u8 D_801C20BB; // item location for something

// non-equiv: the initsv function is fucked what the fuck
//#ifdef NON_EQUIVELENT
void EnYb_Init(EnYb *this, GlobalContext *globalCtx) {
    s16 tempCutscene;
    s32 i;

    Actor_SetScale((Actor *) this, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, func_80BFA350, 20.0f);

    // what the fuck is this doing
    // theory: because this actor uses the same animation as player, his skeleton has something weird
    //SkelAnime_InitSV(arg1, anime, 0x6005F48, 0x6000200, (this->unk188) & ~0xF, (this->unk2A0) & ~0xF, 0x16);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06005F48, &D_06000200,
         &this->limbDrawTbl, &this->transitionDrawTable, ENYB_LIMBCOUNT);

    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06000200);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, (Actor *) this, &D_80BFB2B0);
    this->actor.colChkInfo.mass = 0xFF;
    this->actionFunc = func_80BFAC88;
    this->unk412 = 3;
    this->actor.minVelocityY = -9.0f;
    this->actor.gravity = -1.0f;

    // this might not be defined correctly yet
    func_80BFA444(globalCtx, this, 2, 0, 0.0f);

    tempCutscene = this->actor.cutscene;
    for (i = 0; i < 2; ++i) {
        this->unk416[i] = tempCutscene;
        if (tempCutscene != -1) {
            this->actor.cutscene = tempCutscene;
            tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->unk41A = -1;
    this->actor.cutscene = (s8) this->unk416[0];
    if ((s32) gSaveContext.time < 0x4000) {
        this->unk414 = 0xFF;
    } else {
        this->unk414 = 0;
        this->actionFunc = func_80BFAE80;
        this->actor.flags &= -2;
    }

    // already healed?
    if ((gSaveContext.weekEventReg[0x52] & 4)) {
        Actor_MarkForDeath((Actor *) this);
    }
}
//#else
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Init.asm")
//#endif

void EnYb_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnYb* this = (EnYb*) thisx;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BFA2FC(GlobalContext *globalCtx) {
    if (gSaveContext.inventory.items[D_801C20BB] == 0x43) {
        func_80151BB4(globalCtx, 0x34);
    }
    func_80151BB4(globalCtx, 0xF);
}

// custom shadow draw function
// non-matching: just stack offset
#ifdef NON_MATCHING
void func_80BFA350(struct Actor *actor, struct Lights *mapper, struct GlobalContext *globalCtx) {
    EnYb* this = (EnYb*) actor;
    Vec3f sp34; // currently 30
    s32 pad;
    f32 tempValue;
    //s32 pad[2];

    if (this->unk414 > 0) {
        if (this->unk412 == 2) {
            // this solves all regalloc
            //actor->scale.x = (((27.0f - this->unk404.y) + actor->world.pos.y) * 0.00044444448f) + 0.01f;
            tempValue = (((27.0f - this->unk404.y) + actor->world.pos.y) * 0.00044444448f) + 0.01f;
            actor->scale.x = tempValue;
        }
        Math_Vec3f_Copy(&sp34, &actor->world.pos);
        Math_Vec3f_Copy(&actor->world.pos, &this->unk404);
        func_800B4AEC(globalCtx, (Actor *) actor, 50.0f);

        if (sp34.y < this->actor.floorHeight) {
            actor->world.pos.y = this->actor.floorHeight;
        } else {
            actor->world.pos.y = sp34.y;
        }

        func_800B3FC0((Actor *) actor, mapper, globalCtx);
        Math_Vec3f_Copy(&actor->world.pos,  &sp34);
        actor->scale.x = 0.01f;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA350.asm")
#endif

extern AnimationHeaderCommon D_80BFB2E0[];

// weird data
// fuck it, doing it later, we need song
/*
void func_80BFA444(GlobalContext *globalCtx, EnYb *this, s16 arg3, s16 arg4, f32 arg5) {
    //AnimationHeaderCommon **sp34;
    //AnimationHeaderCommon **temp_v1;
    //AnimationHeaderCommon **temp_v1_2;
    //AnimationHeaderCommon **temp_v1_3;
    u8 temp_a3;

    temp_a3 = arg4 & 0xFF;
    if ((arg3 >= 0) && (arg3 < 3)) {
        if ((arg3 != this->unk412) || (arg4 != 0)) {
            if ( arg3 > 0) {
                if (temp_a3 == 0) {
                    temp_v1 = &D_80BFB2E0[arg3];
                    sp34 = temp_v1;
                    SkelAnime_ChangeLinkAnim(globalCtx, &this->skelAnime,
                         temp_v1->unk-4, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(temp_v1->unk-4), 0, arg5);
                } else {
                    temp_v1_2 = &(&D_80BFB2E0)[arg3];
                    sp34 = temp_v1_2;
                    SkelAnime_ChangeLinkAnim(globalCtx, &this->skelAnime, (LinkAnimationHeader *) temp_v1_2->unk-4, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(temp_v1_2->unk-4), 0, arg5);
                }
            } else {
                temp_v1_3 = &(&D_80BFB2DC)[arg3];
                sp34 = temp_v1_3;
                arg4 = temp_a3;
                SkelAnime_ChangeAnim(&this->skelAnime, (AnimationHeader *) *temp_v1_3, 1.0f, 0.0f, (f32) SkelAnime_GetFrameCount(*temp_v1_3), (f32) arg4, arg5);
            }
            this->unk412 = arg3;
        }
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA444.asm")

// check if dialogue is possible to start?
s32 func_80BFA5CC(EnYb *this, GlobalContext *globalCtx) {
    if ((this->actor.xzDistToPlayer < 100.0f) 
      && (Actor_IsLinkFacingActor((Actor *) this, 0x3000, globalCtx))     
      && (Actor_IsActorFacingLink((Actor *) this, 0x3000))) {
        return 1;
    } else {
        return 0;
    }
}

void func_80BFA634(EnYb *this, GlobalContext *globalCtx) {
    if (this->unk412 <= 0) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    } else {
        func_801360E0(globalCtx, &this->skelAnime);
    }
}

// this would suggest the cutscenes array is not that big
// cutscene related
void func_80BFA67C(EnYb *this) {
    if (this->unk41A != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->unk416[this->unk41A]) {
            ActorCutscene_Stop(this->unk416[this->unk41A]);
        }
        this->unk41A = -1;
    }
}

// zero is the only input...? only called from Idle?
void func_80BFA6E0(EnYb *this, s16 arg1) {
    func_80BFA67C(this);
    this->unk41A = arg1;
}

void func_80BFA710(EnYb* this) { 
    func_800B9084(&this->actor); // sets flag 20 of unk39 in actor
}

// dissapearing? we come here after he says "I'm counting on you" and leaves
void func_80BFA730(EnYb *this, GlobalContext *globalCtx) {
    s32 pad;
    Vec3f sp60;
    s32 i;

    func_80BFA634(this, globalCtx);
    for (i = 3; i >= 0; i--) {
        sp60.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
        sp60.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
        func_800B3030(globalCtx, &sp60, &D_80BFB2E8, &D_80BFB2E8, 0x64, 0, 2);
    }

    func_800F0568(globalCtx, &this->actor.world.pos, 0x14, 0x3878);
    if (this->unk414 >= 0xB) {
        this->unk414 -= 10;
    } else {
        Actor_MarkForDeath((Actor *) this);
    }
}

void func_80BFA868(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if (func_800B84D0((Actor *) this, globalCtx) != 0) { // is talking?
        this->actor.flags &= ~ 0x10000;
        this->actionFunc = func_80BFA9D4;
        //[sound 6954] I am counting on you.
        //[sound 6955](Translation) I am counting on you.
        func_801518B0(globalCtx, 0x147D, (Actor *) this);
        func_80BFA2FC(globalCtx);
    } else {
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

void func_80BFA91C(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    // what parent? when would kamaro be spawned by another actor?
    if (Actor_HasParent((Actor *) this, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BFA868;
        this->actor.flags |= 0x10000;
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        func_800B8A1C((Actor *) this, globalCtx, 0x89, 10000.0f, 100.0f);
    }
    func_80BFA710(this);
}


void func_80BFA9D4(EnYb *this, GlobalContext *globalCtx) {
    //u16 temp_v0;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_80BFA634(this, globalCtx);

    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        switch (globalCtx->msgCtx.unk11F04) {
          case 0x147D:
              //[sound 6954] I am counting on you.
              //[sound 6955](Translation) I am counting on you.
              func_801477B4(globalCtx);
              this->actionFunc = func_80BFA730;
              gSaveContext.weekEventReg[0x52] |= 0x4;
              break;
          case 0x147C:
              // Spread my dance across the world...  Train its followers...
              //(Translation) I have taught it to you, now make it into a popular dance craze!
              if (func_8012403C(globalCtx) == 0xE) { // wearing mask of type?
                  func_801477B4(globalCtx);
                  this->actionFunc = func_80BFAC88;

              } else if (gSaveContext.inventory.items[D_801C20BB] == 0x43) {
                  //[sound 6954] I am counting on you.
                  //[sound 6955](Translation) I am counting on you.
                  func_80151938(globalCtx, 0x147D);
                  func_80BFA2FC(globalCtx);

              } else {
                  func_801477B4(globalCtx);
                  this->actionFunc = func_80BFA91C;
                  func_80BFA91C(this, globalCtx);
              }
              break;
          default:     
              func_801477B4(globalCtx);
              this->actionFunc = func_80BFAC88;
              break;
      }
    }
    func_80BFA710(this);
}

// finish dancing
void func_80BFAB4C(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);
    if (func_800B84D0((Actor *) this, globalCtx) != 0) {
        this->actionFunc = func_80BFA9D4;
        // Spread my dance across the world...  Train its followers...
        //(Translation) I have taught it to you, now make it into a popular dance craze!
        func_801518B0(globalCtx, 0x147C, (Actor *) this);
        this->actor.flags &= ~ 0x10000;
    } else {
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

// dancing countdown
void func_80BFABF0(EnYb *this, GlobalContext *globalCtx) {
    func_80BFA634(this, globalCtx);

    if (this->unk41C > 0) {
        this->unk41C--;
    } else {
        func_80BFA67C(this);
        this->actionFunc = func_80BFAB4C;
        this->actor.flags |= 0x10000;
        func_800B8500((Actor *) this, globalCtx, 1000.0f, 1000.0f, -1);
    }
    func_80BFA710(this);
}

// default auctionfunc
// EnYb_Idle
void func_80BFAC88(EnYb *this, GlobalContext *globalCtx) {
    s32 pad;
    ActorPlayer *player = PLAYER;

    func_80BFA634(this, globalCtx); // update skeleton?
    if ((this->actor.xzDistToPlayer < 180.0f) && (fabsf(this->actor.yDistToPlayer) < 50.0f) 
      && (globalCtx->msgCtx.unk1202A == 3) && (globalCtx->msgCtx.unk1202E == 7) && (gSaveContext.playerForm == 4)) {
        this->actionFunc = func_80BFABF0;
        this->unk41C = 0xC8;
        func_80BFA6E0(this, 0);
    } else if (func_800B84D0((Actor *) this, globalCtx)) { // acotr is talking
        func_80BFA2FC(globalCtx);
        this->actionFunc = func_80BFA9D4;
        if (func_8012403C(globalCtx) == 0xE) {
            // Spread my dance across the world...  Train its followers...
            //(Translation) I have taught it to you, now make it into a popular dance craze!
            func_801518B0(globalCtx, 0x147C, (Actor *) this);
        } else {
            // "[sound 6954] I am no longer part of the living...My sadness to the moon...
            // regular talk to him first dialogue
            func_801518B0(globalCtx, 0x147B, (Actor *) this);
        }
    } else if (func_80BFA5CC(this, globalCtx) != 0) { // check if player can start dialogue
        func_800B8614((Actor *) this, globalCtx, 120.0f);
    }

    if ((this->unk410 & 1) != 0) {
        if ((player->unkA70 * 0x10) >= 0) {
            this->unk410 &= ~1;
        }
    } else if (((player->unkA70 * 0x10) < 0) && (this->actor.xzDistToPlayer < 180.0f) && (fabsf(this->actor.yDistToPlayer) < 50.0f)) {
        this->unk410 |= 1;
        Audio_PlayActorSound2((Actor *) this, NA_SE_SY_TRE_BOX_APPEAR);
    }

    func_80BFA710(this); // sets a single actor flag in player
}

void func_80BFAE80(EnYb *this, GlobalContext *globalCtx) {
    if (gSaveContext.time < 0x4000) {
        func_80BFA634(this, globalCtx);
        this->unk414 += 5;
        if (this->unk414 >= 0xFB) {
            this->unk414 = 0xFF;
            this->actor.flags |= 1;
            this->actionFunc = func_80BFAC88;
        }
        func_80BFA710(this);
    }
}

void EnYb_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnYb* this = (EnYb*) thisx;
    s32 pad;

    if ((this->actor.flags & 1) == 1) {
        Collider_UpdateCylinder((Actor *) this, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
    if ((this->actor.flags & 1) == 1) {
        Actor_SetVelocityAndMoveYRotationAndGravity((Actor *) this);
        func_800B78B8(globalCtx, &this->actor, 40.0f, 25.0f, 40.0f, 5);
    }

    this->actionFunc(this, globalCtx);

    if ((this->unk41A != -1) && (ActorCutscene_GetCurrentIndex() != this->unk416[this->unk41A])) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk416[this->unk41A]);
        } else if (ActorCutscene_GetCanPlayNext(this->unk416[this->unk41A]) != 0) {
            if (this->unk41A == 0) {
                ActorCutscene_StartAndSetUnkLinkFields(this->unk416[this->unk41A], (Actor *) this);
                return;
            }
        } else {
            ActorCutscene_SetIntentToPlay(this->unk416[this->unk41A]);
        }
    }
}

extern Vec3f D_80BFB2F4;
extern Vec3f D_80BFB300;

// two separate post limb draw functions reasons unknown
void func_80BFB074(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor) {
    EnYb* this = (EnYb*) actor;
    if (limbIndex == 0xB) {
        SysMatrix_MultiplyVector3fByState(&D_80BFB2F4, &this->actor.focus.pos);
    }
    if (limbIndex == 3) {
        SysMatrix_MultiplyVector3fByState(&D_801D15B0, &this->unk404);
    }
}

void func_80BFB0E0(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor) {
    EnYb* this = (EnYb*) actor;
    if (limbIndex == 0xB) {
        SysMatrix_MultiplyVector3fByState(&D_80BFB300, &this->actor.focus.pos);
    }
    if (limbIndex == 3) {
        SysMatrix_MultiplyVector3fByState(&D_801D15B0, &this->unk404);
    }
}

void EnYb_Draw(EnYb *this, GlobalContext *globalCtx) {

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk414 != 0) {
        if (this->unk414 < 0xFF) {
            if (this->unk414 >= 0x81) {
                func_8012C2B4(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 2, 2);
            } else {
                func_8012C304(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 1, 2);
            }
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk414);

            if (!(&globalCtx->state)){}

            POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, 0, func_80BFB0E0, this, POLY_XLU_DISP);
        } else {
            func_8012C28C(globalCtx->state.gfxCtx);
            Scene_SetRenderModeXlu(globalCtx, 0, 1);
            SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, 0, func_80BFB074, this);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
