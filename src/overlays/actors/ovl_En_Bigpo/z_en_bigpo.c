#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);

// update functions
void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80B64190(Actor* thisx, GlobalContext* globalCtx);


void func_80B61AC8(EnBigpo* this);
void func_80B61B38(EnBigpo* this);
void func_80B61D74(EnBigpo* this);
void func_80B61E9C(EnBigpo* this);
void func_80B62034(EnBigpo* this);
void func_80B62154(EnBigpo* this);
void func_80B622E4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B624F4(EnBigpo* this);
void func_80B6275C(EnBigpo* this);

void func_80B62814(EnBigpo* this);
void func_80B62900(EnBigpo* this);
void func_80B629E4(EnBigpo* this);
void func_80B62AD4(EnBigpo* this);
void func_80B62E38(EnBigpo* this, GlobalContext* globalCtx);
void func_80B631F8(EnBigpo* this);
void func_80B632BC(EnBigpo* this);
void func_80B633E8(EnBigpo* this);
void func_80B63450(EnBigpo* this);
void func_80B636D0(EnBigpo* this);
void func_80B6383C(EnBigpo* this);
void func_80B638AC(EnBigpo* this);

void func_80B619FC(EnBigpo *this, GlobalContext *globalCtx);
void func_80B61AF8(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61B70(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61DA4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61F04(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62084(EnBigpo* this, GlobalContext* globalCtx);
void func_80B621CC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B623BC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B6259C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B627B4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61C04(EnBigpo *this, GlobalContext *globalCtx);
void func_80B61CFC(EnBigpo *this, GlobalContext *globalCtx);
void func_80B62830(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62920(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62A68(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62B10(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62F10(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63264(EnBigpo* this, GlobalContext* globalCtx);
void func_80B6330C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63410(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63474(EnBigpo* this, GlobalContext* globalCtx);
void func_80B636E4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63758(EnBigpo *this, GlobalContext *globalCtx);
void func_80B63A18(EnBigpo* this);
void func_80B63AC4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63C28(EnBigpo* this);
void func_80B63D0C(EnBigpo* this);
s32 func_80B63D88(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63964(EnBigpo* this);
void func_80B63980(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_DoNothing(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63854(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_Die(EnBigpo* this, GlobalContext* globalCtx);
void func_80B638D4(EnBigpo* this, GlobalContext* globalCtx);

// draw funcs
void func_80B64470(Actor* thisx, GlobalContext* globalCtx);
void func_80B6467C(Actor* thisx, GlobalContext* globalCtx);
void func_80B64880(Actor* thisx, GlobalContext* globalCtx);
void func_80B64B08(Actor* thisx, GlobalContext* globalCtx);
void func_80B64DFC(Actor* thisx, GlobalContext* globalCtx);
void func_80B64240(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor, Gfx **gfx);

extern AnimationHeader D_06001360;
extern SkeletonHeader D_06005C18;
extern AnimationHeader D_06000924;
extern AnimationHeader D_06000924;
extern AnimationHeader D_06000454;
extern Gfx D_060041A0;
extern Gfx D_06001BB0;
extern Gfx D_060058B8;
extern Gfx D_801AEFA0;
extern Gfx D_801AEF88;
extern Gfx D_060042C8;
extern Gfx D_060043F8;
extern Gfx D_0407D590; // called in En_Light too, so probably the fire flame

extern const ActorInit En_Bigpo_InitVars;

/*
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,
    (ActorFunc)NULL,
}; */

// cannot be renamed until Init matches
extern ColliderCylinderInit D_80B65010;
/* static ColliderCylinderInit D_80B65010 = { //glabel D_80B65010 // sCylinderInit 
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 35, 100, 10, { 0, 0, 0 } },
}; */

extern CollisionCheckInfoInit D_80B6503C;
//static CollisionCheckInfoInit D_80B6503C = { 0x0A000023, 0x00643200};
//static u32 D_80B6503C[] = { 0x0A000023, 0x00643200};

extern DamageTable D_80B65044;
/* static DamageTable D_80B65044 = {
    0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0xF0, 0x01, 0x01, 0x00, 0x01, 0x01, 0x42, 0x01, 0x01, 
    0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
}; */

static InitChainEntry D_80B65064;
/* static InitChainEntry D_80B65064[] = { //sInitChain
    ICHAIN_S8(hintId, 90, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
}; */

extern Vec3f D_80B6506C;
//static Vec3f D_80B6506C = { 0.0f, 3.0f, 0.0f};

extern u8 D_80B65078[];
/* static u8 D_80B65078[] = {
    0xFF, 0x04, 0xFF, 0x00, 
    0xFF, 0x01, 0xFF, 0x02, 
    0x05, 0x03, 0x00, 0x00, 
}; */

extern Vec3f D_80B65084;
/* static Vec3f D_80B65084[] = {
    { 2000.0f, 4000.0f, 0.0f,},
    {-1000.0f, 1500.0f, -1000.0f,},
    {-1000.0f, 1500.0f, 2000.0f,},
}; */

#ifdef NON_MATCHING
// non-matching: some instructions out of order but looks like it should be equiv
void EnBigpo_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    EnBigpoFireParticle* fires;
    s32 i;

    Actor_ProcessInitChain(&this->actor, &D_80B65064);

    // issue:  the params look-up wants to save the params to two t registers, one modified, one not
    // then it saves the param, and immediately re-loads it wtf
    // because its duping the globalcontext load instead of the params load, I can only assume its filling a void
    //parms = this->actor.params;
    this->switchFlags = (u8)(this->actor.params >> 8);
    this->actor.params &= 0xFF;
    //this->actor.params = (u8)this->actor.params;
    if (this->actor.params == ENBIGPO_POSSIBLEFIRE) {
        if (Flags_GetSwitch(globalCtx, this->switchFlags)) {
            Actor_MarkForDeath(&this->actor);
        } else  {
            this->actor.update = func_800BDFB0;
            func_80B6383C(this);
        }
        return;
    }
    
    // wants to re-load global context here from s6 in vanilla, but ido doesnt see the need now
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06005C18, &D_06000924, &this->limbDrawTbl, &this->transitionDrawTbl, 0xA);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80B65010);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B65044, &D_80B6503C);

    for (i = 0, fires = this->fires; i < 3; fires++, i++) {
        // wants to do use 3 light pointers, this is silly 
        fires->light = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->fires[i].info);
        //fires->light = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &fires->info);

        Lights_PointNoGlowSetInfo(&this->fires[i].info,
        //Lights_PointNoGlowSetInfo(&fires->info,
             this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
             0xFF, 0xFF, 0xFF, 0);
    }

    // not enough pointers, we need a separate pointer to 338 instead of 348
    //for (i = 0; i < 3; i++) {
        //this->fires[i].light = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->fires[i].info);
        //Lights_PointNoGlowSetInfo(&this->fires[i].info,
             //this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
             //0xFF, 0xFF, 0xFF, 0);
    //}

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 45.0f);
    this->actor.bgCheckFlags |= 0x400;
    this->unk218 = this->actor.home.pos.y + 100.0f;
    this->mainColor.r = 0xFF;
    this->mainColor.g = 0xFF;
    this->mainColor.b = 0xD2;
    this->mainColor.a = 0x00; // fully invible
    
    if ((this->switchFlags != 0xFF) && (Flags_GetSwitch(globalCtx, this->switchFlags))) {
        // has switch flag, and switch already set: already killed
        Actor_MarkForDeath(&this->actor);
    }

    if (this->actor.params == ENBIGPO_REGULAR) { // the well poe
        this->unk204 = 1;
        this->actor.flags &= -0x11;
        func_80B61AC8(this);
    } else if (this->actor.params == ENBIGPO_SUMMONED) { // dampe type
        func_80B63450(this);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Init.asm")
#endif

void EnBigpo_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    GlobalContext *gCtx2;
    s32 fireCount;

    if ((this->actor.params != ENBIGPO_POSSIBLEFIRE) && 
       (this->actor.params != ENBIGPO_CHOSENFIRE) &&
       (this->actor.params != ENBIGPO_REVEALEDFIRE) && (this->actor.params != ENBIGPO_UNK5)) {
        // if NOT a fire type, ENBIGPO_REGULAR and ENBIGPO_SUMMONED combat types only
        // req for matching
        if (1) {}
        gCtx2 = globalCtx;
        for(fireCount = 0; fireCount < 3; ++fireCount){
          LightContext_RemoveLight(gCtx2, &gCtx2->lightCtx, this->fires[fireCount].light);
        }
        Collider_DestroyCylinder(gCtx2, &this->collider);
    }
}

#if NON_EQUIVELENT
// non-equivelent: ido wont loop properly
// for/while want to add another branch, only goto sticks to one
// also wont increment pointers properly
// STILL WONT MATCH why
void func_80B61914(EnBigpo *this) {
    s32 secondi;
    EnBigpoFireParticle *fires;
    s32 i;

    i = 0;
    fires = this->fires;
  loop_1:
    fires->pos.x = (Math_SinS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.x;
    fires->pos.z = (Math_CosS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.z;
    this->actor.shape.rot.y += 0x5555;
    i = secondi;
    secondi += 0x20;
    fires += 1;
    if (secondi != 0x60) {
        goto loop_1;
    }

    //s32 i;
    //EnBigpoFireParticle* fires;// = this->fires;
    //for (i = 0; i < 3; i++){
    //for (fires = this->fires; fires != &this->fires[2]; fires++){
        //this->fires[i].pos.x = (Math_SinS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.x;
        //this->fires[i].pos.z = (Math_CosS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.z;
        ////fires[i].pos.x = (Math_SinS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.x;
        ////fires[i].pos.z = (Math_CosS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.z;
        //fires->pos.x = (Math_SinS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.x;
        //fires->pos.z = (Math_CosS(this->actor.shape.rot.y) * this->unk214) + this->actor.world.pos.z;
        //this->actor.shape.rot.y += 0x5555;
    //}
}
#else 
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61914.asm")
#endif

// play spinning sound
void func_80B619B4(EnBigpo *this) {
    s16 oldYaw = this->actor.shape.rot.y;
    this->actor.shape.rot.y += this->rotVelocity;
    if ((oldYaw < 0) && ( this->actor.shape.rot.y > 0)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_ROLL);
    }
}

void func_80B619FC(EnBigpo *this, GlobalContext *globalContext) {
    Camera *cam;
    if (this->unk20E != 0) {
        cam = Play_GetCamera(globalContext, this->unk20E);
        cam->eye.y -= this->actor.velocity.y;
        if (this->actor.velocity.y > 0.0f) {
            cam->eye.x -= 1.5f * Math_SinS(this->actor.yawTowardsPlayer);
            cam->eye.z -= 1.5f * Math_CosS(this->actor.yawTowardsPlayer);
        }
        func_8016970C(globalContext, this->unk20E, &this->actor.focus.pos, &cam->eye);
    }
}

// type 0 well type
void func_80B61AC8(EnBigpo *this) {
    // ! @ BUG: redundant: targetable flag was already set by init, nothing else calls this
    this->actor.flags &= ~1; // targetable OFF
    this->actionFunc = func_80B61AF8;
    this->unk214 = 200.0f;
}

// EnBigpo_WaitForProximity well poe?
void func_80B61AF8(EnBigpo *this, GlobalContext *globalCtx) {
    if (this->actor.xzDistToPlayer < 200.0f) {
        func_80B61B38(this);
    }
}

// start cutscene for well poe
void func_80B61B38(EnBigpo *this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_80B61B70;
}

// wait for cutscene queue
void func_80B61B70(EnBigpo *this, GlobalContext *globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_800B724C(globalCtx, &this->actor, 7);
        this->unk20E = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (this->actor.params == ENBIGPO_REGULAR) { // and SUMMONED, got switched earlier
            func_80B61C04(this, globalCtx);
        } else { // ENBIGPO_REVEALEDFIRE
            func_80B63758(this, globalCtx);
        }
    }else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

// spawn regular poe
void func_80B61C04(EnBigpo *this, GlobalContext *globalCtx) {
    s32 i;

    this->actor.draw = func_80B64B08;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    func_80B61914(this);

    for (i = 0; i < 3; i++) {
        this->fires[i].pos.y = this->actor.world.pos.y;
    }

    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.015f;
    this->actor.scale.z = 0.0f;

    if (this->unk20E != 0) {
        Vec3f newPos;
        newPos.x = ((this->actor.world.pos.x - this->fires[0].pos.x) * 1.8f) + this->actor.world.pos.x;
        newPos.y = this->actor.world.pos.y + 150.0f;
        newPos.z = ((this->actor.world.pos.z - this->fires[0].pos.z) * 1.8f) + this->actor.world.pos.z;
        func_8016970C(globalCtx, this->unk20E, &this->actor.focus.pos, &newPos);
    }
    this->actionFunc = func_80B61CFC;
}

void func_80B61CFC(EnBigpo *this, GlobalContext *globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.001f) != 0) {
        func_80B61D74(this);
    }
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
}

void func_80B61D74(EnBigpo *this) {
    this->rotVelocity = 0x1000;
    this->actionFunc = func_80B61DA4;
    this->unk214 = 200.0f;
    this->actor.velocity.y = 0.0f;
}

void func_80B61DA4(EnBigpo *this, GlobalContext *globalCtx) {
    s32 i;

    if (Math_StepToF(&this->unk214, 30.0f, 5.0f) != 0) {
        this->rotVelocity += 0x80;
        this->actor.velocity.y += 0.25f;
    }
    this->actor.shape.rot.y += this->rotVelocity;
    func_80B61914(this);

    if (1) {}
    for (i = 0; i < 3; i++){
        this->fires[i].pos.y += this->actor.velocity.y;
    }

    this->actor.world.pos.y += this->actor.velocity.y;
    func_80B619FC(this, globalCtx);
    if (this->actor.velocity.y >= 4.0f) {
        func_80B61E9C(this);
    }
}

void func_80B61E9C(EnBigpo *this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001360);
    this->actor.draw = func_80B64470;
    Actor_SetScale(&this->actor, 0.014f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    this->actionFunc = func_80B61F04;
}

void func_80B61F04(EnBigpo *this, GlobalContext *globalCtx) {
    s32 i;
    s32 alphaPlus; // color alpha + 10

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.rot.y += this->rotVelocity;
    alphaPlus = this->mainColor.a + 0xA; // decrease transparency
    func_80B61914(this);
    if (alphaPlus >= 0x5A) {
        this->rotVelocity += -0x80; 
        this->actor.velocity.y -= 0.25f;
        if (alphaPlus >= 0xB4) {
            Math_ScaledStepToS(&this->actor.world.rot.y, 0, 0x180);
        }
    }
    this->actor.world.pos.y += this->actor.velocity.y;

    for (i = 0; i < 3; i++){
        this->fires[i].pos.y += this->actor.velocity.y;
    }

    func_80B619FC(this, globalCtx);
    if (alphaPlus >= 0xFF) {
        this->mainColor.a = 0xFF; // max opacity
        func_80B62034(this);
    } else {
        this->mainColor.a = alphaPlus;
    }
}

// setup
void func_80B62034(EnBigpo *this) {
    this->idleTimer = 16;
    if (this->unk204 == 0) {
        func_801A2E54(0x38);
        this->unk204 = 1;
    }
    this->actionFunc = func_80B62084;
}

void func_80B62084(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *dampe;
    Camera *cam;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->idleTimer -= 1;
    if (this->idleTimer == 0) {
        cam = Play_GetCamera(globalCtx, this->unk20E);
        func_8016970C(globalCtx, 0, &cam->focalPoint, &cam->eye);
        this->unk20E = 0;
        if (this->actor.params == ENBIGPO_SUMMONED) {
            // if dampe exists, switch to viewing his running away cutscene
            dampe = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_NPC, ACTOR_EN_TK);
            if (dampe != 0) {
                dampe->params = this->actor.cutscene;
            } else {
                ActorCutscene_Stop(this->actor.cutscene);
            }
        } else { // ENBIGPO_REGULAR
            ActorCutscene_Stop(this->actor.cutscene);
        }
        func_800B724C(globalCtx, &this->actor, 6);
        func_80B624F4(this); // setup idle flying
    }
}


// setup spinning fade out
void func_80B62154(EnBigpo *this) {
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->rotVelocity = 0x2000;
    this->idleTimer = 32;
    this->actor.flags &= ~1; // targetable
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DISAPPEAR);
    this->actionFunc = func_80B621CC;
}

// spinning fade out
void func_80B621CC(EnBigpo *this, GlobalContext *globalCtx) {
    DECR(this->idleTimer);
    this->actor.shape.rot.y += this->rotVelocity;
    if (this->idleTimer < 0x10) {
        Math_ScaledStepToS(&this->rotVelocity, 0, 0x200);
    }
    this->mainColor.a = this->idleTimer * 7.96875f;
    if (this->idleTimer == 0) {
        this->mainColor.a = 0; // fully invisible
        func_80B622E4(this, globalCtx);
    }
}

// setup warp behind player
void func_80B622E4(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    f32 distance;
    s16 randomYaw;

    distance = (this->actor.xzDistToPlayer < 200.0f) ? ( 200.0f ) : ( this->actor.xzDistToPlayer );
    randomYaw = (Rand_Next() >> 0x14) + this->actor.yawTowardsPlayer;
    Audio_PlayActorSound2(&player->base, NA_SE_EN_STALKIDS_APPEAR);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001360);
    this->rotVelocity = 0x2000;
    this->actor.world.pos.x = (Math_SinS(randomYaw) * distance) + player->base.world.pos.x;
    this->actor.world.pos.z = (Math_CosS(randomYaw) * distance) + player->base.world.pos.z;
    this->actionFunc = func_80B623BC;
}

// action: spinning back into reality behind player?
void func_80B623BC(EnBigpo *this, GlobalContext *globalCtx) {
    this->idleTimer += 1;
    this->actor.shape.rot.y -= this->rotVelocity;
    if (this->idleTimer >= 16) {
        // after 16th frame, start slowing rotation
        Math_ScaledStepToS(&this->rotVelocity, 0, 0x200);
    }

    this->mainColor.a = this->idleTimer * 7.96875f;
    if (this->idleTimer == 32) {
        this->mainColor.a = 0xFF; // fully visible
        if (this->unk204 == 0) {
            func_801A2E54(0x38);
            this->unk204 = 1;
        }
        func_80B624F4(this);
    }
}

// setup fully appeared
void func_80B624F4(EnBigpo *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000924, -5.0f);
    // if poe missed attack, idle 4 seconds, otherwise its reappearing: attack immediately
    this->idleTimer = (this->actionFunc == func_80B62920) ? 80 : 0;
    this->unk212 = 40;
    this->actor.velocity.y = 0.0f;
    this->unk218 = this->actor.world.pos.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->collider.base.acFlags |= AC_ON; 
    this->collider.base.ocFlags1 |= OC1_ON;
    this->actor.flags |= 0x1; //targetable
    this->actionFunc = func_80B6259C;
}

// idle flying around
void func_80B6259C(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    DECR(this->idleTimer);
    this->unk212 = (this->unk212 == 0) ? 0x28 : (this->unk212 - 1);
    Math_StepToF(&this->unk218, player->base.world.pos.y + 100.0f, 1.5f);
    this->actor.world.pos.y = (sin_rad(this->unk212 * 0.15707964f) * 10.0f) + this->unk218;
    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.2f);
    func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 300.0f) {
        this->unk208 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    if ((Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk208, 0x200) != 0) && (Rand_ZeroOne() < 0.075f)) {
        // casts req
        this->unk208 += (s16)((((u32)Rand_Next() >> 0x14) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    
    // poe's break is done, time to attack
    if (this->idleTimer == 0) {
        func_80B6275C(this);
    }
}

// before it makes a bombing run, it has to spin up some speed
void func_80B6275C(EnBigpo *this) {
    this->collider.base.colType = COLTYPE_METAL;
    this->collider.base.acFlags |= AC_HARD;
    this->collider.info.bumper.dmgFlags &= ~0x8000;
    this->collider.base.atFlags |= AT_ON;
    this->rotVelocity = 0x800;
    this->actionFunc = func_80B627B4;
    this->actor.speedXZ = 0.0f;
}

// still spinning up to max speed
void func_80B627B4(EnBigpo *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->rotVelocity += 0x200;
    func_80B619B4(this); // play spin sound
    if (this->rotVelocity >= 0x3C00) {
        func_80B62814(this);
    }
}

// start bombing run
void func_80B62814(EnBigpo *this) {
    // set flying direction at player (not spinning direction)
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = func_80B62830;
}

// flying spin attack against player is active
void func_80B62830(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    s16 yawDiff;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 10.0f, 1.0f);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->base.world.pos.y, 0.3f, 7.5f, 1.0f);
    func_80B619B4(this); // play spinning sound
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    // because acFlags AC_HARD and COLTYPE_METAL, if we hit it means we contacted as attack
    if (((this->collider.base.atFlags & AT_HIT)) 
      || ( ((yawDiff < 0) ? -yawDiff : yawDiff) >= 0x4001) && (this->actor.xzDistToPlayer > 50.0f)) {
        // hit the player OR the poe has missed and flew past player
        func_80B62900(this);
    }
}

// start spinning down attack is finishing
void func_80B62900(EnBigpo *this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->actionFunc = func_80B62920;
}

// spin down to no spin
void func_80B62920(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->base.world.pos.y + 100.0f, 0.3f, 5.0f, 1.0f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (Math_ScaledStepToS(&this->rotVelocity, 0, 0x200) != 0) {
        // re-allow hittable after bombing run
        this->collider.base.colType = COLTYPE_HIT3;
        this->collider.base.acFlags &= ~AC_HARD;
        this->collider.info.bumper.dmgFlags |= 0x8000;
        func_80B624F4(this); // setup idle flying
    }
    func_80B619B4(this); // play spin sound
}

// change to stunned after hit 
void func_80B629E4(EnBigpo *this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000454, -6.0f);
    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->collider.base.acFlags &= ~AC_ON;
    func_800BE504(&this->actor, &this->collider.base);
    this->actionFunc = func_80B62A68;
    this->actor.speedXZ = 5.0f;
}

// check if just damaged or dead
void func_80B62A68(EnBigpo *this, GlobalContext *globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_80B62AD4(this);
        } else { 
            func_80B62154(this);
        }
    }
}

// setup death
void func_80B62AD4(EnBigpo *this) {
    this->idleTimer = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.hintId = 0xFF; // clear?
    this->collider.base.ocFlags1 &= 0xFFFE; //~0x1 what flag is this? OC_ON?
    this->actionFunc = func_80B62B10;
}

// time of death
void func_80B62B10(EnBigpo *this, GlobalContext *globalCtx) {
    Vec3f tempVec; 
    f32 unkTemp2; 
    s16 cam; 
    s16 unkTemp; 
    s16 modifiedTimer; 

    this->idleTimer += 1;
    if ( this->idleTimer < 8) {
        cam = func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x4800;
        if ((s32) this->idleTimer < 5) {
            unkTemp = (this->idleTimer << 0xC) - 0x4000;
            tempVec.y = (((Math_SinS(unkTemp) * 23.0f) + 40.0f) * 1.4000001f) + this->actor.world.pos.y;
            unkTemp2 = Math_CosS(unkTemp) * 32.2f;
            tempVec.x = (Math_SinS(cam) * unkTemp2) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * unkTemp2) + this->actor.world.pos.z;

        } else {
            tempVec.y = this->actor.world.pos.y + ((40.0f + (15.0f * (this->idleTimer - 5))) * 1.4000001f);
            tempVec.x = (Math_SinS(cam) * 32.2f) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * 32.2f) + this->actor.world.pos.z;
        }

        // not sure what we're turning this into, but its based on the timer
        modifiedTimer = (s32) ((f32) ((this->idleTimer * 10) + 80) * 1.4000001f);
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);
        tempVec.x = (2.0f * this->actor.world.pos.x) - tempVec.x;
        tempVec.z = (2.0f * this->actor.world.pos.z) - tempVec.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);
        tempVec.x = this->actor.world.pos.x;
        tempVec.z = this->actor.world.pos.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);

    } else if (this->idleTimer >= 28) {
        func_80B62E38(this, globalCtx);

    } else if (this->idleTimer >= 19) {
        this->actor.scale.x = (( (28 - this->idleTimer)) * 0.014f) * 0.1f;
        this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
        this->actor.world.pos.y += 5.0f;
    }

    if (this->idleTimer < 18) {
        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
    }
    if (this->idleTimer == 18) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    }
}

// setup finallize death? 
void func_80B62E38(EnBigpo *this, GlobalContext *globalCtx) {
    this->actor.draw = func_80B64880;
    this->actor.shape.shadowDraw = NULL;
    this->actor.world.pos.x = this->drawMtxF.wx;
    this->actor.world.pos.y = this->drawMtxF.wy;
    this->actor.world.pos.z = this->drawMtxF.wz;

    Actor_SetScale(&this->actor, 0.014f);
    this->actor.gravity = -1.0f;
    this->actor.shape.yOffset = 1500.0f;
    this->actor.shape.rot.x = -0x8000;
    this->actor.velocity.y = 0.0f;
    this->actor.world.pos.y -= 15.0f;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_MISC);
    this->actor.flags &= ~0x5; // targetable OFF, enemy music OFF
    this->actor.bgCheckFlags &= ~0x400;
    this->actionFunc = func_80B62F10;
}

// falling to the floor? where is height change?
void func_80B62F10(EnBigpo *this, GlobalContext *globalCtx) {
    // gravity was changed, should be falling to the floor
    // if hit the floor, or the bottom?
    if (((this->actor.bgCheckFlags & 1)) || (this->actor.floorHeight == -32000.0f)) {
        if (this->switchFlags != 0xFF) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlags);
        }
        
        // think this is the scoopable soul
        EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 
            6.0f, 0, 1, 1, 0xF, OBJECT_BIGPO, 10, &D_060041A0);
        func_80B631F8(this);
    }
}

// EnBigpo_AdjustAlpha
void func_80B62FCC(EnBigpo *this, s32 alphaDiff) {
    s32 newAlpha;
    f32 lowerAlpha;
    f32 newXYScale;
    
    newAlpha = this->mainColor.a + alphaDiff;

    this->mainColor.a = (newAlpha < 0) ? (0) : ((newAlpha >= 0x100) ? 0xFF : newAlpha );

    lowerAlpha = this->mainColor.a * 0.003921569f;
    if (alphaDiff < 0) {
        newXYScale = (0.0056000003f * lowerAlpha) + 0.0014000001f;
        this->actor.scale.x = newXYScale;
        this->actor.scale.z = newXYScale;
        this->actor.scale.y = (0.007f - (0.007f * lowerAlpha)) + 0.007f;
        lowerAlpha = lowerAlpha;
    } else {
        Actor_SetScale(&this->actor, lowerAlpha * 0.007f);
        this->actor.world.pos.y = this->unk218 + (lowerAlpha * 15.0f);
        lowerAlpha = 1.0f;
    }

    this->mainColor.r = 255.0f * lowerAlpha;
    this->mainColor.g = 200.0f * lowerAlpha;
    this->mainColor.b = 0;
}

// this is called after the bigpo scoop is spawned I think
void func_80B631F8(EnBigpo *this) {
    this->actor.draw = func_80B6467C;
    this->actor.shape.yOffset = 0.0f;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.y = 0;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->mainColor.a = 0; // fully invisible
    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.0f;
    this->unk218 = this->actor.world.pos.y;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_METAL_BOX_BOUND); // misnamed?
    this->actionFunc = func_80B63264;
}

void func_80B63264(EnBigpo *this, GlobalContext *globalCtx) {
    this->unk218 += 2.0f;
    func_80B62FCC(this, 0x14); // increase visibility
    if (this->mainColor.a == 0xFF) { // fully visible
        func_80B632BC(this);
    }
}

void func_80B632BC(EnBigpo *this) {
    this->unk218 = this->actor.world.pos.y;
    Actor_SetHeight(&this->actor, -10.0f);
    this->idleTimer = 400;
    this->actor.flags |= 1;
    this->actionFunc = func_80B6330C;
}


void func_80B6330C(EnBigpo *this, GlobalContext *globalCtx) {
    DECR(this->idleTimer);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
    } else if (this->idleTimer == 0) {
        // took too long, soul is leaving
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
        func_80B633E8(this);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0xBA, 35.0f, 60.0f);
        this->actor.world.pos.y = (sin_rad((f32) this->idleTimer * 0.15707964f) * 5.0f) + this->unk218;
    }
}

// start fade to nothing
void func_80B633E8(EnBigpo *this) {
    this->actor.flags &= ~0x10001;
    this->actionFunc = func_80B63410;
}

// soul is fading away
void func_80B63410(EnBigpo *this, GlobalContext *globalCtx) {
    func_80B62FCC(this, -0xD);
    if (this->mainColor.a == 0) { // fully invisible
        Actor_MarkForDeath(&this->actor);
    }
}

// type ENBIGPO_SUMMONED
void func_80B63450(EnBigpo *this) {
    this->actor.flags &= ~1; // targetable OFF
    this->actionFunc = func_80B63474;
}

// EnBigpo_RandomizeDampePoFires
void func_80B63474(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *enemyPtr;
    EnBigpo* randomFirePo;
    s32 fireIndex;
    s32 randomIndex;
    s32 fireCount = 0;

    // count the number of possible fires we can use
    for (enemyPtr = FIRSTENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
      if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)) {
        fireCount++;
      }
    }

    // if not enough fires exist, just starting fighting already
    if (fireCount < 3) {
        this->actor.draw = func_80B64470;
        Actor_SetScale(&this->actor, 0.014f);
        func_80B622E4(this, globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
        this->actor.world.pos.y += 100.0f;
        return;
    }

    // for available possiblefires, pick three to be random fires
    for (fireIndex = 0; fireIndex < 3 ; ++fireIndex, --fireCount) {
        enemyPtr = FIRSTENEMY;
        randomIndex = ((s32) Rand_ZeroFloat(fireCount)) % fireCount;

        // cannot be for because enemyPtr must be initilized before randomIndex
        while(enemyPtr != NULL) {
            if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)){
                if (randomIndex == 0) {
                    randomFirePo = (EnBigpo*) enemyPtr;
                    randomFirePo->actor.params = ENBIGPO_CHOSENFIRE;
                    Math_Vec3f_Copy(&this->fires[fireIndex].pos, &randomFirePo->actor.world.pos);
                    randomFirePo->actor.parent = (Actor*) this;
                    randomFirePo->actor.update = func_80B64190;
                    func_800BC154(globalCtx, &globalCtx->actorCtx, &randomFirePo->actor, ACTORCAT_PROP);
                    randomFirePo->unk20C = fireIndex;
                    randomFirePo->actor.flags &= ~0x1; // targetable OFF
                    // make invisible by size:0
                    Actor_SetScale(&randomFirePo->actor, 0);

                    // we seem to be chaining fires.. not sure why
                    if (this->actor.child == NULL) {
                        this->actor.child = &randomFirePo->actor;
                    } else {
                        randomFirePo->actor.child = this->actor.child;
                        this->actor.child = &randomFirePo->actor;
                    }
                    break;
                } else {
                    randomIndex--;
                }
            }
          enemyPtr = enemyPtr->next;
        }
    }

    // remove unused fires
    for (enemyPtr = FIRSTENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
        if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)) {
            randomFirePo = (EnBigpo* ) enemyPtr;
            randomFirePo->actionFunc = EnBigpo_Die;
            randomFirePo->actor.update = func_80B64190; // one frame to draw before death?
        }
    }

    func_80B636D0(this);
}

void func_80B636D0(EnBigpo *this) {
    this->actionFunc = func_80B636E4;
}

// count fires already found
void func_80B636E4(EnBigpo *this, GlobalContext *globalCtx) {
    EnBigpo* childPoh;
    s32 i = 0;

    for (childPoh = (EnBigpo*) this->actor.child; childPoh; childPoh = (EnBigpo*)childPoh->actor.child) {
        if ((childPoh->actor.params == ENBIGPO_REVEALEDFIRE) && (childPoh->actionFunc == func_80B63980)) {
            i++;
        }
    }

    if (i == 3) { // all fires found
        func_80B61B38(this);
    }
}

// setup: place swirling flame start positions?
void func_80B63758(EnBigpo *this, GlobalContext *globalCtx) {
    EnBigpo *childPoh;
    Vec3f newPos;

    this->idleTimer = 39;
    for (childPoh = (EnBigpo *) this->actor.child; childPoh; childPoh = (EnBigpo*)childPoh->actor.child) {
        func_80B63A18(childPoh);
    }

    // set new starting position for flames?
    if (this->unk20E != 0) {
        newPos.x = (Math_SinS(this->actor.yawTowardsPlayer) * 360.0f) + this->actor.world.pos.x;
        newPos.y = this->actor.world.pos.y + 150.0f;
        newPos.z = (Math_CosS(this->actor.yawTowardsPlayer) * 360.0f) + this->actor.world.pos.z;
        func_8016970C(globalCtx, this->unk20E, &this->actor.focus.pos, &newPos);
    }

    this->actionFunc = EnBigpo_DoNothing;
}

void EnBigpo_DoNothing(EnBigpo *this, GlobalContext *globalCtx) {
}

// type 2
void func_80B6383C(EnBigpo *this) {
    this->actor.draw = NULL;
    this->actionFunc = func_80B63854;
}

// wait until fire is revealed by dampe, then start drawing fire
void func_80B63854(EnBigpo *this, GlobalContext *globalCtx) {
    if (this->actor.params == ENBIGPO_REVEALEDFIRE) {
        func_80B638AC(this);
    }
}

void EnBigpo_Die(EnBigpo *this, GlobalContext *globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

// changes draw and action function?
void func_80B638AC(EnBigpo *this) {
    this->actor.draw = func_80B64DFC;
    this->idleTimer = 0xF;
    this->actionFunc = func_80B638D4;
}

void func_80B638D4(EnBigpo *this, GlobalContext *globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.0005f) != 0) {
        this->idleTimer--;
        if (this->idleTimer == 0) {
            func_80B63964(this);
        }
    }
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
}

void func_80B63964(EnBigpo *this) {
    this->idleTimer = 0x2710;
    this->actionFunc = func_80B63980;
}

void func_80B63980(EnBigpo *this, GlobalContext *globalCtx) {
    if (this->idleTimer > 0) {
        if (this->idleTimer == 0) {
            // ! @ BUG: unreachable code?
            this->actor.params = ENBIGPO_UNK5;
            return;
        }
    } else {
        if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.001f) != 0) {
            this->actor.params = ENBIGPO_CHOSENFIRE;
            func_80B6383C(this);
        }
        this->actor.scale.z = this->actor.scale.x;
        this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
    }
}

// setup: start flame swirl cutscene for dampe poe
void func_80B63A18(EnBigpo *this) {
    s16 h;

    this->idleTimer = 40;
    h = this->actor.parent->yawTowardsPlayer + this->unk20C * 0x5555;
    this->actor.home.pos.x = Math_SinS(h) * 30.0f + this->actor.parent->world.pos.x;
    this->actor.home.pos.y = this->actor.parent->world.pos.y;
    this->actor.home.pos.z = Math_CosS(h) * 30.0f + this->actor.parent->world.pos.z;
    this->actionFunc = func_80B63AC4;
}

// every frame, swirl the flames toward big poe as summoned
void func_80B63AC4(EnBigpo *this, GlobalContext *globalCtx) {
    Vec3f posDiff;
    f32 magnitude; // placeholder name

    this->idleTimer--;
    if (this->idleTimer == 0) {
        EnBigpo* parentPoh = (EnBigpo*) this->actor.parent;
        Actor_SetSwitchFlag(globalCtx, this->switchFlags);
        Math_Vec3f_Copy(&parentPoh->fires[this->unk20C].pos, &this->actor.world.pos);
        Actor_MarkForDeath(&this->actor);
        if (this->unk20C == 0) {
            parentPoh->actor.draw = func_80B64B08;
            Actor_SetScale(&parentPoh->actor, 0.01f);
            func_80B61D74(parentPoh);
            parentPoh->unk214 = 30.0f;
        }
    } else {
        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.home.pos, &posDiff);
        magnitude = Math3D_Vec3fMagnitude(&posDiff);
        if (magnitude > 0.0001f) {
            Math_Vec3f_Scale(&posDiff, 1.0f / magnitude);
        }
        magnitude = magnitude / this->idleTimer;
        this->actor.world.pos.x -= magnitude * posDiff.x;
        this->actor.world.pos.y -= magnitude * posDiff.y;
        this->actor.world.pos.z -= magnitude * posDiff.z;
    }
}

void func_80B63C28(EnBigpo *this) {
    s32 bplus5;
    s32 bminus5;

    if (this->actionFunc == func_80B62A68 ) {
        if ((this->actor.colorFilterTimer & 2)) {
            this->mainColor.r = 0;
            this->mainColor.g = 0;
            this->mainColor.b = 0;
        } else { 
            this->mainColor.r = 0x50;
            this->mainColor.g = 0xFF;
            this->mainColor.b = 0xE1;
        }
    } else {
        this->mainColor.r = (this->mainColor.r + 5 >= 0x100) ? (0xFF) : (this->mainColor.r + 5);
        this->mainColor.g = (this->mainColor.g + 5 >= 0x100) ? (0xFF) : (this->mainColor.g + 5);

        // this might be a triple ternary but it matches and is easier to read spread out
        bplus5 = this->mainColor.b + 5;
        if (this->mainColor.b >= 0xD3) {
            bminus5 = this->mainColor.b - 5;
            if (bminus5 < 0xD2) {
                this->mainColor.b = 0xD2;
            } else {
                this->mainColor.b = (u8) bminus5;
            }
        } else {
             if (bplus5 >= 0xD3) {
                this->mainColor.b = 0xD2;
            } else {
                this->mainColor.b = (u8) bplus5;
            }
        }
    }
}

// randomize color?
void func_80B63D0C(EnBigpo *this) {
    f32 rand = Rand_ZeroOne();
    this->unk294.r = ((s32)(rand * 30.0f)) + 0xE1;
    this->unk294.g = ((s32)(rand * 100.0f)) + 0x9B;
    this->unk294.b = ((s32)(rand * 160.0f)) + 0x5F;
    this->unk294.a = ((s32)(rand * 30.0f)) + 0xDC;
}

// might be true/false
// only called by update
// EnBigpo_CheckHit
s32 func_80B63D88(EnBigpo *this, GlobalContext *globalCtx) {
    if (((this->collider.base.acFlags & AC_HIT) != 0) && ((this->collider.base.acFlags & AC_HARD) == 0)) {
        this->collider.base.acFlags &= ~AC_HIT;
        
        if (this->actor.colChkInfo.damageEffect == 0xF) {
          return true;
        }
        
        if (func_800BE22C(&this->actor) == 0) { // guess: get health == 0 ?
            this->actor.flags &= ~1; // targetable OFF
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DEAD);
            func_800BBA88(globalCtx, &this->actor);
            if (this->actor.params == ENBIGPO_SUMMONED) { // dampe type
                func_801A2ED8();
            }
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DAMAGE);
        }

        // think this is the light arrow effect version fo clear tag, not black smoke
        if (this->actor.colChkInfo.damageEffect == 4) {
            this->unk21C = 4.0f;
            this->unk220 = 1.0f;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, 
                this->collider.info.bumper.hitPos.x,
                this->collider.info.bumper.hitPos.y,
                this->collider.info.bumper.hitPos.z,
                 0, 0, 0, 0x0004);
        }
        func_80B629E4(this);
        return true;
    }
    return false;
}

void EnBigpo_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    s32 pad;
    Collider* thisCollider;

    if ((this->actor.flags & 0x2000) == 0x2000) {
        this->unk212 = 0;
        this->unk218 = this->actor.world.pos.y;
    }

    if (func_80B63D88(this, globalCtx) == 0) {
        if ((this->actor.isTargeted != 0) && (this->actionFunc != func_80B621CC) 
          && ((this->collider.base.acFlags & AC_HARD) == 0) && (this->actor.category == ACTORCAT_ENEMY)) {
            this->unk20C += 1;
        } else {
            this->unk20C = 0;
        }
        if (this->unk20C == 0x28) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
            func_80B62154(this);
        }
    }

    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != func_80B61F04) && (this->actionFunc != func_80B61DA4)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
    if (this->actionFunc == func_80B62F10) {
        func_800B78B8(globalCtx, &this->actor, 0.0f, 27.0f, 60.0f, 4);
    }

    if (this->actor.draw == func_80B6467C) {
        Actor_SetHeight(&this->actor, -10.0f);
    } else {
        Actor_SetHeight(&this->actor, 42.0f);
    }

    func_80B63C28(this); // modifies a color
    func_80B63D0C(this); // randomizes a second color

    this->actor.shape.shadowAlpha = this->mainColor.a;
    thisCollider = &this->collider.base;
    Collider_UpdateCylinder(&this->actor, thisCollider);
    if ((this->collider.base.ocFlags1 & OC1_ON)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, thisCollider);
    }
    if ((this->collider.base.atFlags & AT_ON)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, thisCollider);
    }
    if ((this->collider.base.acFlags & AC_ON)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, thisCollider);
    }

    if (this->unk21C > 0.0f) {
        Math_StepToF(&this->unk21C, 0.0f, 0.05f);
        if (this->mainColor.a != 0xFF) { // NOT fully visible
            if (this->mainColor.a * 0.003921569f < this->mainColor.a) {
                this->unk21C = this->mainColor.a * 0.003921569f;
            }
        }
        this->unk220 = ((this->unk21C + 1.0f) * 0.5f);
        this->unk220 = (this->unk220 > 1.0f) ? 1.0f : this->unk220;
    }
}

// alternative update func
// actionfunc for dampe fire po
void func_80B64190(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    this->actor.shape.rot.y = func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000;
    this->actionFunc(this, globalCtx);
}

//OverrideLimbDraw2 type
s32 func_80B641E8(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, 
  Vec3f *pos, Vec3s *rot, struct Actor *actor, Gfx **gfx) {
    EnBigpo* this = (EnBigpo*) actor;
    // not fully invisible
    if ((! ((this->mainColor.a != 0x00) && (limbIndex != 7))) 
      || ((this->actionFunc == func_80B62B10) && ((s32) this->idleTimer >= 2))) {
        *dList = NULL;
    }
    return 0;
}

//PostLimbDraw2
#ifdef NON_EQUIVELENT
// non-equivelent: the actual draw macros arent matching
void func_80B64240(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor, Gfx **gfx) {
    EnBigpo* this = (EnBigpo*) actor;

    Vec3f unusedVec;
    s8 limbByte;
    Vec3f *v1ptr;
    Vec3f *v2ptr;
    s32 i;

    //OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->actionFunc == func_80B62B10) && (this->idleTimer >= 2) && (limbIndex == 8)) {

        OPEN_DISPS(globalCtx->state.gfxCtx);
        // this is broken

        gSPMatrix(*gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx),
           G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(*gfx++, &D_060058B8);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 7) {
        SysMatrix_GetStateTranslationAndScaledY(1400.0f, &unusedVec);
        if ((this->actionFunc == func_80B62B10 ) && (this->idleTimer >= 0x13)) {
            if (actor->scale.x != 0.0f) {
                Matrix_Scale(0.014f / actor->scale.x, 0.014f / actor->scale.x, 0.014f / actor->scale.x, 1);
            }
        }
        SysMatrix_CopyCurrentState(&this->drawMtxF);
    }

    limbByte = D_80B65078[limbIndex];
    if (limbByte != -1) {
        if (limbByte < 3) {
            SysMatrix_GetStateTranslation(&this->unk224[limbByte]);
            return;
        }
        if (limbByte == 3) {
            SysMatrix_GetStateTranslationAndScaledX(3000.0f, &this->unk224[limbByte]);
            return;
        }
        if (limbByte == 4) {
            SysMatrix_GetStateTranslationAndScaledY(-2000.0f, &this->unk224[limbByte]);
            return;

        }
        v2ptr = &this->unk224[limbByte+1];
        v1ptr = &D_80B65084;
        SysMatrix_GetStateTranslationAndScaledX(-4000.0f, &this->unk224[limbByte]);
        
        for (i = limbByte + 1; i < 9; i++) { //loop_18:
            SysMatrix_MultiplyVector3fByState(v1ptr, v2ptr);
            v2ptr++;
            v1ptr++;
        }
    }
    //CLOSE_DISPS(globalCtx->state.gfxCtx);

}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64240.asm")
#endif

// used if enough fires, for main po?
void func_80B64470(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    Gfx* dispHead;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    
    if ((this->mainColor.a == 0xFF) || (this->mainColor.a == 0)) {
        // fully visible OR fully transparent
        dispHead = POLY_OPA_DISP;
        gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]);
        gSPSegment(dispHead + 1, 0x0C, &D_801AEFA0);
        gSPSegment(dispHead + 2, 0x08, 
            Gfx_EnvColor(globalCtx->state.gfxCtx, this->mainColor.r, this->mainColor.g,
                         this->mainColor.b, this->mainColor.a));
        POLY_OPA_DISP = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                    func_80B641E8, func_80B64240, &this->actor, dispHead + 3);

    } else {
        dispHead = POLY_XLU_DISP;
        gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]);
        gSPSegment(dispHead + 1, 0x0C, &D_801AEF88);
        gSPSegment(dispHead + 2, 0x08, 
            Gfx_EnvColor(globalCtx->state.gfxCtx, this->mainColor.r, this->mainColor.g,
                         this->mainColor.b, this->mainColor.a));
        POLY_XLU_DISP = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                    func_80B641E8, func_80B64240, &this->actor, dispHead + 3);
    }

    func_800BE680(globalCtx, &this->actor, &this->unk224, 9,
         this->actor.scale.x * 71.428566f * this->unk220, 0, this->unk21C, 0x14);

    SysMatrix_SetCurrentState(&this->drawMtxF);
    func_80B64880(&this->actor, globalCtx);
    if (this->actionFunc == func_80B61F04 ) {
        func_80B64B08(&this->actor, globalCtx);
    }
  
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// draw func
void func_80B6467C(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08, 
        Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 
            0, 0, 0, 0x20, 0x40, 1, 0, 
            (globalCtx->gameplayFrames * -0xF) & 0x1FF, 0x20, 0x80));

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xFF, 0xFF, 0xAA, this->mainColor.a);

    gDPSetEnvColor(POLY_XLU_DISP++, this->mainColor.r, this->mainColor.g, this->mainColor.b, 0xFF);

    Lights_PointNoGlowSetInfo(&this->fires[0].info,
         this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
         this->mainColor.r, this->mainColor.g, this->mainColor.b, this->mainColor.a * 2);

    Matrix_RotateY((func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000), 1);

    gSPMatrix(POLY_XLU_DISP++, 
        Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, &D_06001BB0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);

}

// draw func
// non-equivelent: this is an odd draw function, diff is nowhere close
// set as poe is dying
#ifdef NON_EQUIVELENT
void func_80B64880(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;

    Vec3f vec1;
    Vec3f vec2;
    Camera *cam;
    f32 magnitude;
    f32 magnitude2;
    Gfx *dispHead;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    cam = globalCtx->cameraPtrs[globalCtx->activeCamera];
    if (cam != NULL) {
        Math_Vec3f_Diff(&cam->eye, &cam->focalPoint, &vec1);
        magnitude = Math3D_Vec3fMagnitude(&vec1);
        magnitude2 = (magnitude > 1.0f) ? (20.0f / magnitude) : (20.0f);
        Math_Vec3f_Scale(&vec1, magnitude2);
    } else {
        Math_Vec3f_Copy(&vec1, &D_801D15B0);
    }
    
    // fully visible OR fully transparent
    if ((this->mainColor.a == 0xFF) || (this->mainColor.a == 0)) {
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        dispHead = POLY_OPA_DISP;
    } else {
        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        dispHead = POLY_XLU_DISP;
    }

    gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]);

    gSPSegment(dispHead + 1, 0x0A, Gfx_EnvColor(globalCtx->state.gfxCtx, 0xA0, 0, 0xFF, (s32) this->mainColor.a));

    SysMatrix_GetStateTranslationAndScaledY(1400.0f, &vec2);
    Lights_PointGlowSetInfo(&this->fires[0].info, (s16) (vec2.x + vec1.x),
         (s16) (vec2.y + vec1.y), (s16) (vec2.z + vec1.z),
         (s32) this->unk294.r, (s32) this->unk294.g, (s32) this->unk294.b, (s32) this->unk294.a); // radius?

    gDPSetEnvColor(dispHead + 2, this->unk294.r, this->unk294.g, this->unk294.b, this->mainColor.a);

    gSPMatrix(dispHead + 3, Matrix_NewMtx(globalCtx->state.gfxCtx),
       G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(dispHead + 4, &D_060042C8);

    gSPDisplayList(dispHead + 5, &D_060043F8);

    // fully transparent OR fully invisible
    if ((this->mainColor.a == 0xFF) || (this->mainColor.a == 0)) {
        POLY_OPA_DISP += 6;
    } else {
        POLY_XLU_DISP += 6;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64880.asm")
#endif

#ifdef NON_MATCHING
// non-matching: instructions out of order
// regular big poe draw, switched to after dampe summon
void func_80B64B08(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    s32 pad[3];
    s16 sp66;
    s32 pad2;
    MtxF *mtfxPtr;
    s32 i;
    EnBigpo* this2;
    EnBigpoFireParticle* fires;
    EnBigpoFireParticle* fires2;

    mtfxPtr = SysMatrix_GetCurrentState();
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    fires2 = this->fires;
    Matrix_RotateY((func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000), 0);
    if (this->actionFunc == func_80B61F04 ) {
        Matrix_Scale(0.01f, 0.01f, 0.01f, 1);
        sp66 = 0x1F4;
    } else {
        Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1);
        sp66 = (s16)(thisx->scale.x * 500.0f * 100.0f);
    }
    gSPSegment(POLY_XLU_DISP++, 0x08, 
        Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0U, 0U, 0x20, 0x40, 1, 0, 
        ((s32) globalCtx->gameplayFrames * -0x14) & 0x1FF, 0x20, 0x80));

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xAA, 0xFF, 0xFF, 0xFF - this->mainColor.a);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0xFF, 0xFF);

    //fires = this->fires;
    //this2 = this;

    // out of order here
    //3704:    move    s3,zero          | 3704:    addiu   s1,s7,0x338
    //3708:    move    s0,s7            r 3708:    move    s3,zero                        
    //370c:    addiu   s1,s7,0x338      | 370c:    move    s0,s7                          

    //for (i = 0, fires = this->fires, this2 = this; i < 3; i++, fires++) {
    for (this2 = this, fires = this->fires, i = 0; i < 3; i++, fires++) {
        Lights_PointNoGlowSetInfo(&this->fires[i].info, 
            this2->fires[i].pos.x, this2->fires[i].pos.y, this2->fires[i].pos.z, 
            0xAA, 0xFF, 0xFF, sp66);
        mtfxPtr->wx = fires->pos.x;
        mtfxPtr->wy = fires->pos.y;
        mtfxPtr->wz = fires->pos.z;

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
           G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        
        gSPDisplayList(POLY_XLU_DISP++, &D_0407D590); // flame display list?
 
    // out of order here
    //37e0:    addiu   s1,s1,0x20       r 37e0:    addiu   s4,s4,0x20
    //37e4:    ...
    //37e8:    addiu   s4,s4,0x20       r 37e8:    addiu   s1,s1,0x20
    }
    
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64B08.asm")
#endif

// draw func for the fires in dampes house
void func_80B64DFC(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*) thisx;
    EnBigpo *parent = (EnBigpo*) thisx->parent;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx,
       0, 0, 0, 0x20, 0x40, 1, 0, ((s32) globalCtx->gameplayFrames * -0x14) & 0x1FF, 0x20, 0x80));

    // flame color is static
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xAA, 0xFF, 0xFF, 0xFF);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0xFF, 0xFF);

    Lights_PointNoGlowSetInfo(&parent->fires[this->unk20C].info, 
        thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z,
        0xAA, 0xFF, 0xFF, (s32) (thisx->scale.x * 500.0f * 100.0f));

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
       G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, &D_0407D590); // flame display list?

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
