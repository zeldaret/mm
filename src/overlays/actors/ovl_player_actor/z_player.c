/*
 * File: z_player.c
 * Overlay: ovl_player_actor
 * Description: Player
 */

#include "global.h"
#include "z64rumble.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#include "objects/object_link_boy/object_link_boy.h"
#include "objects/object_link_goron/object_link_goron.h"
#include "objects/object_link_zora/object_link_zora.h"
#include "objects/object_link_nuts/object_link_nuts.h"
#include "objects/object_link_child/object_link_child.h"

#define THIS ((Player*)thisx)

extern UNK_TYPE D_06008860;
extern Gfx D_0600BDD8[];
extern AnimationHeader D_060178D0;

void Player_Init(Actor* thisx, PlayState* play);
void Player_Destroy(Actor* thisx, PlayState* play);
void Player_Update(Actor* thisx, PlayState* play);
void Player_Draw(Actor* thisx, PlayState* play);


void func_80844EF8(Player* player, PlayState* play, Input* input);
s32 func_8085B134(PlayState* play);
void func_8085B170(PlayState* play, Player* player);



extern LinkAnimationHeader* D_8085BE84[6];


extern f32 D_8085D3FC[2];
extern Input* D_80862B44;

extern Vec3f D_80862AF0;                            /* type too large by 8 */
extern f32 D_80862AF4;
extern f32 D_80862AF8;
extern f32 D_80862AFC;
extern s16 D_80862B00;
extern s16 D_80862B02;
extern s32 D_80862B04;
extern u32 D_80862B08;
extern s32 D_80862B0C;
extern u32 D_80862B10;
extern s16 D_80862B14;
extern s16 D_80862B16;
extern f32 D_80862B18;
extern s32 D_80862B1C;
extern s32 D_80862B20;
extern s32 D_80862B24;
extern s16 D_80862B28;
extern s32 D_80862B2C;
extern Vec3f D_80862B30;
extern f32 D_80862B3C;
extern u32 D_80862B40;
extern Input* D_80862B44;
extern s32 D_80862B48;
extern s32 D_80862B4C;
extern UNK_TYPE D_80862B50;
extern s32 D_80862B6C;
extern f32 D_8085C3E4;

extern f32 D_8085D404[3];
extern f32 D_8085C3E8;
extern u16 D_8085C3EC[4];

extern u8 D_8085D174[];

extern f32 D_8085D35C;
extern f32 D_8085D360;
extern Vec3f D_8085D364;
extern Vec3f D_8085D370;
extern Color_RGBA8 D_8085D37C;
extern Color_RGBA8 D_8085D380;
extern UNK_TYPE D_8085D384;
extern f32 D_8085D3E0[5];
extern Color_RGBA8 D_8085D3F4;
extern Color_RGBA8 D_8085D3F8;
extern f32 D_8085D3FC[2];
extern f32 D_8085D404[3];
extern f32 D_8085D410[3];

void func_808508C8(Player* this, PlayState* play);
void func_80854430(Player* this, PlayState* play);
void func_8084D820(Player* this, PlayState* play);
void func_808561B0(Player* this, PlayState* play);
void func_80853D68(Player* this, PlayState* play);
void func_80857BE8(Player* this, PlayState* play);

s32 func_8082DA90(PlayState* play) {
    return play->sceneLoadFlag != 0 || play->unk_18B4A != 0;
}

void func_8082DABC(Player* this) {
    this->linearVelocity = 0.0f;
    this->actor.speedXZ = 0.0f;
}

void func_8082DAD4(Player* this) {
    func_8082DABC(this);
    this->unk_AA5 = 0;
}

s32 func_8082DAFC(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return CHECK_FLAG_ALL(player->actor.flags, 0x100);
}

void func_8082DB18(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayOnce(play, &this->skelAnime, anim);
}

void func_8082DB3C(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayLoop(play, &this->skelAnime, anim);
}

void func_8082DB60(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayLoopSetSpeed(play, &this->skelAnime, anim, 2.0f/3.0f);
}

void func_8082DB90(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 2.0f/3.0f);
}

void func_8082DBC0(PlayState* play, Player* this, LinkAnimationHeader* anim) {
    LinkAnimation_Change(play, &this->skelAnime, anim, -2.0f/3.0f, Animation_GetLastFrame(anim), 0.0f, 2, 0.0f);
}

void func_8082DC28(Player* this) {
    this->skelAnime.jointTable[1].y = 0;
}


void func_8082DC38(Player* this) {
    this->stateFlags2 &= ~0x20000;
    this->meleeWeaponState = 0;
    this->meleeWeaponInfo[2].active = false;
    this->meleeWeaponInfo[1].active = false;
    this->meleeWeaponInfo[0].active = false;
}

void func_8082DC64(PlayState* play, Player* this) {
    if ((this->unk_3BC != -1) && (play->cameraPtrs[this->unk_3BC] != 0)) {
        this->unk_3BC = -1;
    }
    this->stateFlags2 &= ~0xC00;
}

void func_8082DCA0(PlayState* play, Player* this) {
    Actor* heldActor;

    heldActor = this->heldActor;
    if (heldActor != NULL) {
        if (!Player_IsHoldingHookshot(this)) {
            this->actor.child = NULL;
            this->heldActor = NULL;
            this->interactRangeActor = NULL;
            heldActor->parent = NULL;
            this->stateFlags1 &= ~0x800;
        }
    }

    if (Player_GetExplosiveHeld(this) >= 0) {
        func_8082F8BC(play, this, 0);
        this->heldItemId = 0xFE;
    }
}

void func_8082DD2C(PlayState* arg0, Player* arg1) {
    if ((arg1->stateFlags1 & 0x800) && (arg1->heldActor == NULL)) {
        if (arg1->interactRangeActor != NULL) {
            if (arg1->getItemId == 0) {
                arg1->stateFlags1 &= ~0x800;
                arg1->interactRangeActor = NULL;
            }
        } else {
            arg1->stateFlags1 &= ~0x800;
        }
    }

    func_8082DC38(arg1);
    arg1->unk_AA5 = 0;
    func_8082DC64(arg0, arg1);
    func_800E0238(Play_GetCamera(arg0, 0));
    arg1->stateFlags1 &= ~0x306004;
    arg1->stateFlags2 &= ~0x90;
    arg1->unk_ADD = 0;
    arg1->unk_ADC = 0;
    arg1->actor.shape.rot.x = 0;
    arg1->actor.shape.rot.z = 0;
    arg1->unk_ABC = 0.0f;
    arg1->unk_AC0 = 0.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DE14.s")

void func_8082DE50(PlayState* play, Player* this) {
    func_8082DD2C(play, this);
    func_8082DCA0(play, this);
}

#ifdef NON_MATCHING
s32 func_8082DE88(Player* arg0, s32 arg1, s32 arg2) {
    s16 temp_v0;

    temp_v0 = arg0->unk_D64 - D_80862B00;
    arg0->unk_AE8 += arg1 + (s32) (ABS_ALT(temp_v0) * fabsf(D_80862AFC) * 0.0000025415802f);
    if (D_80862B44->press.button & 0xC000) {
        arg0->unk_AE8 += 5;
    }
    return arg0->unk_AE8 >= arg2;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DE88.s")
#endif

void func_8082DF2C(PlayState* play) {
    if (play->actorCtx.freezeFlashTimer == 0) {
        play->actorCtx.freezeFlashTimer = 1;
    }
}

void func_8082DF48(PlayState* play, Player* this, u8 sourceIntensity, u8 decayTimer, u8 decayStep, s32 distSq) {
    if (this == GET_PLAYER(play)) {
        Rumble_Request(distSq, sourceIntensity, decayTimer, decayStep);
    }
}

void func_8082DF8C(Player* arg0, u16 arg1) {
    u16 var_v0;

    if (arg0->currentMask == PLAYER_MASK_GIANT) {
        func_8019F830(&arg0->actor.projectedPos, arg1);
        return;
    }

    if (arg0->actor.id == ACTOR_PLAYER) {
        if (arg0->currentMask == PLAYER_MASK_SCENTS) {
            var_v0 = 0xE0;
        } else {
            var_v0 = arg0->ageProperties->unk_92;
        }

        func_800B8E58(arg0, var_v0 + arg1);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E0F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E5A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EAC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EB18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ECCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ECE0.s")

LinkAnimationHeader* func_8082ED20(Player* this) {
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->actor.id != ACTOR_PLAYER)) {
        return &gameplay_keep_Linkanim_00E410;
    }
    if (this->transformation == PLAYER_FORM_GORON) {
        return &gameplay_keep_Linkanim_00E260;
    }
    if (this->currentMask == PLAYER_MASK_SCENTS) {
        return &gameplay_keep_Linkanim_00D0B0;
    }
    return D_8085BE84[this->modelAnimType];
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ED94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EEA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EFE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F02C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F43C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FA5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FBE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FDC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FE0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808302CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808304BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808305BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808306F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808308DC.s")

void func_808309CC(PlayState* play, Player* this);
/*
void func_808309CC(PlayState* play, Player* player) {
    if (player->unk_AC4 == func_80848808) {
        func_808308DC(play, &player->actor);
    }
    func_8082F43C(play, player, D_8085C9F0[player->itemActionParam]);
    player->unk_ACC = 0;
    player->unk_AA4 = 0;
    func_8082DCA0(play, player);
    player->stateFlags3 &= 0xBFFFFFFF;
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808309CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830E30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083133C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808313A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808313F0.s")

void func_80831454(Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831454.s")

s32 func_80831494(PlayState* play, Player* this, void (*arg2)(Player*, PlayState* play), s32 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083172C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808317C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808318C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083213C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083216C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808323C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083249C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808324EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832CAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808331FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808332A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808333CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808334D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808335B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808335F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083375C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808339B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808339D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808340AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808340D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808341F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808344C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083456C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808345A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808345C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808353DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808354A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808355D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083562C.s")

void func_80835BC8(Player* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083604C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808365DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083692C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808369F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808370D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808373A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808373F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083784C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808378FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083798C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808379C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808381A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808381F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083827C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083868C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808387A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808388B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808389BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808391D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808395F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808396B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AD04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AD8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083ADB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083ADF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B3B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083BB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083BF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C6E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C85C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CB04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D6DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DEE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DF38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E2F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F57C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F8A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FD80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FE90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808400CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808401F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808409A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808411D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808412A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808412BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808414E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808415A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808415E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841624.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841744.s")

extern InitChainEntry D_8085D2C0[];

extern Vec3s D_8085D2C4;
extern Vec3s D_8085D2C4;

extern ColliderCylinderInit D_8085C2EC;
extern ColliderCylinderInit D_8085C318;
extern ColliderQuadInit D_8085C344;
extern ColliderQuadInit D_8085C394;
extern FlexSkeletonHeader D_060177B8;

void Player_InitCommon(Player* this, PlayState* play, FlexSkeletonHeader* skelHeader) {
    Actor_ProcessInitChain(&this->actor, D_8085D2C0);
    this->currentYaw = this->actor.world.rot.y;

    if ((((this->actor.params & 0xF00) >> 8) != 0xC) && ((gSaveContext.respawnFlag != 2) || (gSaveContext.respawn[1].playerParams != 0xCFF))) {
        func_808309CC(play, this);
        SkelAnime_InitLink(play, &this->skelAnime, skelHeader, D_8085BE84[this->modelAnimType], 9, (void*)this->unk_74C, (void*)this->unk_7EB, 0x16);
        this->skelAnime.baseTransl = D_8085D2C4;

        SkelAnime_InitLink(play, &this->unk_284, skelHeader, func_8082ED20(this), 9, (void*)this->unk_929, (void*)this->unk_9C8, 0x16);
        this->unk_284.baseTransl = D_8085D2C4;

        if (this->transformation == 1) {
            SkelAnime_InitFlex(play, &this->unk_2C8, &D_060177B8, &D_060178D0, this->jointTable, this->morphTable, 5);
        }

        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, this->ageProperties->unk_04);
    }

    this->unk_3BC = -1;
    Collider_InitAndSetCylinder(play, &this->cylinder, &this->actor, &D_8085C2EC);
    Collider_InitAndSetCylinder(play, &this->shieldCylinder, &this->actor, &D_8085C318);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[0], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[1], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->shieldQuad, &this->actor, &D_8085C394);
}

void func_80841A50(PlayState* play, Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841A50.s")


extern LinkAnimationHeader D_0400CF98;
extern LinkAnimationHeader D_0400D0A8;
extern LinkAnimationHeader D_0400D0B0;
extern LinkAnimationHeader D_0400D0C8;
extern LinkAnimationHeader D_0400D0D0;
extern LinkAnimationHeader D_0400D100;
extern LinkAnimationHeader D_0400D218;
extern LinkAnimationHeader D_0400D220;
extern LinkAnimationHeader D_0400D228;
extern LinkAnimationHeader D_0400D3E8;
extern LinkAnimationHeader D_0400D3F8;
extern LinkAnimationHeader D_0400D420;
extern LinkAnimationHeader D_0400D488;
extern LinkAnimationHeader D_0400D490;
extern LinkAnimationHeader D_0400D4A8;
extern LinkAnimationHeader D_0400D4B0;
extern LinkAnimationHeader D_0400D4B8;
extern LinkAnimationHeader D_0400D4C0;
extern LinkAnimationHeader D_0400D4D8;
extern LinkAnimationHeader D_0400D4F0;
extern LinkAnimationHeader D_0400D4F8;
extern LinkAnimationHeader D_0400D500;
extern LinkAnimationHeader D_0400D5A8;
extern LinkAnimationHeader D_0400D5B0;
extern LinkAnimationHeader D_0400D638;
extern LinkAnimationHeader D_0400D660;
extern LinkAnimationHeader D_0400D698;
extern LinkAnimationHeader D_0400D8B0;
extern LinkAnimationHeader D_0400D9C8;
extern LinkAnimationHeader D_0400D9D0;
extern LinkAnimationHeader D_0400D9D8;
extern LinkAnimationHeader D_0400DA60;
extern LinkAnimationHeader D_0400DA68;
extern LinkAnimationHeader D_0400DA70;
extern LinkAnimationHeader D_0400DA88;
extern LinkAnimationHeader D_0400DAA0;
extern LinkAnimationHeader D_0400DAA8;
extern LinkAnimationHeader D_0400DAC0;
extern LinkAnimationHeader D_0400DAC8;
extern LinkAnimationHeader D_0400DAD0;
extern LinkAnimationHeader D_0400DAD8;
extern LinkAnimationHeader D_0400DAE0;
extern LinkAnimationHeader D_0400DAF0;
extern LinkAnimationHeader D_0400DB10;
extern LinkAnimationHeader D_0400DB18;
extern LinkAnimationHeader D_0400DB30;
extern LinkAnimationHeader D_0400DB68;
extern LinkAnimationHeader D_0400DBB0;
extern LinkAnimationHeader D_0400DBE8;
extern LinkAnimationHeader D_0400DC20;
extern LinkAnimationHeader D_0400DC28;
extern LinkAnimationHeader D_0400DC30;
extern LinkAnimationHeader D_0400DC48;
extern LinkAnimationHeader D_0400DC60;
extern LinkAnimationHeader D_0400DC78;
extern LinkAnimationHeader D_0400DC80;
extern LinkAnimationHeader D_0400DC88;
extern LinkAnimationHeader D_0400DCA8;
extern LinkAnimationHeader D_0400DCD0;
extern LinkAnimationHeader D_0400DCF8;
extern LinkAnimationHeader D_0400DD10;
extern LinkAnimationHeader D_0400DD30;
extern LinkAnimationHeader D_0400DD38;
extern LinkAnimationHeader D_0400DD40;
extern LinkAnimationHeader D_0400DD70;
extern LinkAnimationHeader D_0400DD78;
extern LinkAnimationHeader D_0400DD80;
extern LinkAnimationHeader D_0400DDF0;
extern LinkAnimationHeader D_0400DDF8;
extern LinkAnimationHeader D_0400DE00;
extern LinkAnimationHeader D_0400DE08;
extern LinkAnimationHeader D_0400DE10;
extern LinkAnimationHeader D_0400DE28;
extern LinkAnimationHeader D_0400DE30;
extern LinkAnimationHeader D_0400DE50;
extern LinkAnimationHeader D_0400DE60;
extern LinkAnimationHeader D_0400DEA0;
extern LinkAnimationHeader D_0400DEA8;
extern LinkAnimationHeader D_0400DF78;
extern LinkAnimationHeader D_0400DF90;
extern LinkAnimationHeader D_0400DF98;
extern LinkAnimationHeader D_0400DFA0;
extern LinkAnimationHeader D_0400DFA8;
extern LinkAnimationHeader D_0400DFB0;
extern LinkAnimationHeader D_0400DFB8;
extern LinkAnimationHeader D_0400DFC0;
extern LinkAnimationHeader D_0400DFC8;
extern LinkAnimationHeader D_0400DFD0;
extern LinkAnimationHeader D_0400DFD8;
extern LinkAnimationHeader D_0400DFE0;
extern LinkAnimationHeader D_0400DFE8;
extern LinkAnimationHeader D_0400DFF0;
extern LinkAnimationHeader D_0400DFF8;
extern LinkAnimationHeader D_0400E000;
extern LinkAnimationHeader D_0400E008;
extern LinkAnimationHeader D_0400E050;
extern LinkAnimationHeader D_0400E060;
extern LinkAnimationHeader D_0400E070;
extern LinkAnimationHeader D_0400E080;
extern LinkAnimationHeader D_0400E088;
extern LinkAnimationHeader D_0400E098;
extern LinkAnimationHeader D_0400E1F0;
extern LinkAnimationHeader D_0400E200;
extern LinkAnimationHeader D_0400E208;
extern LinkAnimationHeader D_0400E260;
extern LinkAnimationHeader D_0400E270;
extern LinkAnimationHeader D_0400E278;
extern LinkAnimationHeader D_0400E290;
extern LinkAnimationHeader D_0400E298;
extern LinkAnimationHeader D_0400E2A0;
extern LinkAnimationHeader D_0400E2B8;
extern LinkAnimationHeader D_0400E2C0;
extern LinkAnimationHeader D_0400E2C8;
extern LinkAnimationHeader D_0400E2D8;
extern LinkAnimationHeader D_0400E2E8;
extern LinkAnimationHeader D_0400E2F0;
extern LinkAnimationHeader D_0400E2F8;
extern LinkAnimationHeader D_0400E398;
extern LinkAnimationHeader D_0400E3A0;
extern LinkAnimationHeader D_0400E3A8;
extern LinkAnimationHeader D_0400E3B0;
extern LinkAnimationHeader D_0400E3B8;
extern LinkAnimationHeader D_0400E3C0;
extern LinkAnimationHeader D_0400E3D8;
extern LinkAnimationHeader D_0400E408;
extern LinkAnimationHeader D_0400E410;
extern LinkAnimationHeader D_0400E418;

// extern void (*D_8085D2CC[0x10])(PlayState*, Player*, s32);
extern void (*D_8085D2CC[0x10])();
extern PlayerAgeProperties D_8085BA38[PLAYER_FORM_MAX];
extern LinkAnimationHeader* D_8085D160[PLAYER_FORM_MAX];
extern UNK_TYPE D_8085D30C;
extern UNK_TYPE D_8085D330;
extern Vec3f D_8085D340;

s32 func_8085B1F0(PlayState* play, Player* player);
s32 func_8085B28C(PlayState* play, Player* player, s32 mode);
void func_8085B384(Player* player, PlayState* play, Player*);
s32 func_8085B3E0(PlayState* play, s32 damage);
void func_8085B460(PlayState* play, Actor* actor, Player* player);
void func_8085B74C(PlayState* play);
void func_8085B820(PlayState* play, s16 arg1, Actor* actor);
s32 func_8085B854(PlayState* play, Player* player, s32 itemId, s32 arg3);
s32 func_8085B930(PlayState* play, void* talkAnim, s32 arg2);
void func_8085B08C(Player* arg0, PlayState* play);
void func_80855818(Player* arg0, PlayState* play);

#if 0
void Player_Init(Actor* thisx, PlayState* play) {
    s32 sp60;
    s8* sp44;
    PosRot* sp40;
    PosRot* temp_a0_2;
    RespawnData* temp_t8;
    RespawnData* temp_t9_2;
    SaveContext* var_v1;
    s16 temp_v0;
    s16 temp_v0_6;
    s16 temp_v1_3;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0_2;
    s32 var_v0_3;
    s8 temp_v0_2;
    s8* temp_a0;
    s8* temp_v1_2;
    u32 temp_t7;
    u32 temp_t9;
    u8 temp_t1;
    u8 temp_t6;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 var_v0;
    void* temp_v0_3;
    Player* this = (Player* ) thisx;

    play->playerInit = Player_InitCommon;
    play->playerUpdate = func_80844EF8;
    play->unk_18770 = func_8085B170;
    play->startPlayerFishing = func_8085B134;
    play->grabPlayer = func_8085B1F0;
    play->startPlayerCutscene = func_8085B28C;
    play->func_18780 = func_8085B384;
    play->damagePlayer = func_8085B3E0;
    play->talkWithPlayer = func_8085B460;
    play->unk_1878C = func_8085B74C;
    play->unk_18790 = func_8085B820;
    play->unk_18794 = func_8085B854;
    play->setPlayerTalkAnim = func_8085B930;

    gActorOverlayTable[0].initInfo->objectId = 1;
    temp_v0 = this->actor.shape.rot.x;
    this->actor.room = -1;
    this->unk_A86 = -1;
    temp_t1 = temp_v0 - 1;
    if (temp_v0 != 0) {
        this->transformation = temp_t1;
        temp_v0_2 = Object_GetIndex(&play->objectCtx, gPlayerFormObjectIndices[temp_t1 & 0xFF]);
        this->actor.objBankIndex = temp_v0_2;
        if (temp_v0_2 < 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        Actor_SetObjectDependency(play, &this->actor);
    } else {
        temp_t6 = gSaveContext.save.playerForm;
        temp_v1 = temp_t6 & 0xFF;
        this->transformation = temp_t6;
        if (temp_v1 == 4) {
            var_v0 = gSaveContext.save.equippedMask;
            if (var_v0 == 0x14) {
                gSaveContext.save.equippedMask = 0;
                var_v0 = 0;
            }
            this->currentMask = var_v0;
        } else {
            this->currentMask = temp_v1 + 0x15;
            gSaveContext.save.equippedMask = 0;
        }
        Inventory_UpdateDeitySwordEquip(play);
        this->unk_B28 = 0;
        this->unk_B90 = 0;
        this->unk_B92 = 0;
        this->unk_B94 = 0;
        this->unk_B96 = 0;
        this->stateFlags1 &= 0xFCFFEFF7;
        this->stateFlags2 &= 0xBEFDFFFF;
        this->stateFlags3 &= 0xFC424437;
        this->unk_B08[0] = 0.0f;
        this->unk_B08[1] = 0.0f;
    }
    if (this->transformation == 2) {
        if ((this->stateFlags1 * 0x10) < 0) {
            this->unk_B08[2] = 1.0f;
        } else {
            this->unk_B08[2] = 0.0f;
        }
    }
    this->actor.flags &= 0xFBFDFFFF;
    if (this->transformation != 3) {
        this->actor.flags |= 0x04000000;
        if (this->transformation == 1) {
            this->actor.flags |= 0x20000;
        }
    }
    this->ageProperties = &D_8085BA38[this->transformation];
    this->heldItemActionParam = 0;
    this->itemActionParam = 0;
    this->heldItemId = 0xFF;
    // todo: declaration
    func_80831990(play, &this->actor, 0xFFU);
    Player_SetEquipmentData(play, this);
    this->prevBoots = this->currentBoots;
    Player_InitCommon(&this->actor, play, gPlayerSkeletons[this->transformation]);
    if (this->actor.shape.rot.z != 0) {
        this->actor.shape.rot.z = 0;
        // todo: declaration
        func_8082F938((Player* ) play, this, 0, 4);
        #if 0
        temp_v0_3 = Effect_GetByIndex(this->meleeWeaponEffectIndex[2]);
        if (this->transformation == 1) {
            temp_v0_3->unk_606 = (unaligned s32) D_8085D338;
        } else {
            temp_v0_3->unk_606 = (unaligned s32) D_8085D33C;
        }
        #endif
        if ((this->csMode == 9) || (this->csMode == 0x5D)) {
            // todo: declaration
            func_80831494(play, this, func_8085B08C, 0);
            this->stateFlags1 |= 0x20000000;
            return;
        }
        // todo: declaration
        func_80831494(play, this, func_80855818, 0);
        this->actor.shape.rot.y = this->currentYaw;
        if (this->prevMask != 0) {
            // todo: declaration
            func_8082DB90(play, this, &D_0400D0A8);
        } else {
            if (this->transformation == 4) {
                LinkAnimation_Change(play, &this->skelAnime, D_8085D160[this->transformation], -0.6666667f, 9.0f, 0.0f, (u8) 2, 0.0f);
            } else {
                // todo: declaration
                func_8082DB60(play, this, &D_0400D0D0);
            }
        }
        this->stateFlags1 |= 0x30000000;
        this->stateFlags3 |= 0x20000;
        this->unk_B08[7] = 3.0f;
        return;
    }
    this->prevMask = this->currentMask;
    Effect_Add(play, this->meleeWeaponEffectIndex, 2, 0U, (u8) 0, &D_8085D30C);
    Effect_Add(play, &this->meleeWeaponEffectIndex[1], 2, 0U, (u8) 0, &D_8085D30C);
    // todo: declaration
    func_8082F938((Player* ) play, this, 0, 4);
    #if 0
    if (this->transformation == 1) {
        *(&D_8085D330 + 4) = (unaligned s32) D_8085D338;
    } else {
        *(&D_8085D330 + 4) = (unaligned s32) D_8085D33C;
    }
    #endif
    Effect_Add(play, &this->meleeWeaponEffectIndex[2], 4, 0U, (u8) 0, &D_8085D330);
    if (this->actor.shape.rot.x != 0) {
        this->actor.shape.rot.x = 0;
        this->csMode = 0x44;
        // todo: declaration
        func_80831494(play, this, func_8085B08C, 0);
        this->stateFlags1 |= 0x20000000;
        return;
    }
    play->unk_1887C = 0;
    play->unk_1887D = 0;
    play->unk_1887E = 0;
    this->giObjectSegment = ZeldaArena_Malloc(0x2000U);
    this->maskObjectSegment = ZeldaArena_Malloc(0x3800U);
    temp_a0 = &this->unk_404[0x24];
    Lights_PointNoGlowSetInfo((LightInfo* ) temp_a0, (s16) (s32) this->actor.world.pos.x, (s16) (s32) this->actor.world.pos.y, (s16) (s32) this->actor.world.pos.z, (u8) 0xFF, (u8) 0x80, (u8) 0, (s16) -1);
    #if 0
    this->unk_504 = LightContext_InsertLight(play, &play->lightCtx, (LightInfo* ) temp_a0);
    #endif
    Play_AssignPlayerActorCsIdsFromScene(&play->state, (s32) this->actor.cutscene);
    var_a2 = gSaveContext.respawnFlag;
    if (var_a2 != 0) {
        if (var_a2 == -3) {
            this->actor.params = gSaveContext.respawn[3].playerParams;
        } else {
            if ((var_a2 == 1) || (var_a2 == -1)) {
                this->unk_D6A = -2;
            }
            if (var_a2 != -7) {
                temp_a0_2 = &this->actor.world;
                if ((var_a2 == -8) || (var_a2 == -5) || (var_a2 == -4)) {
                    var_a2 = 1;
                }
                if ((var_a2 < 0) && (var_a2 != -1) && (var_a2 != -6)) {
                    var_v1 = &gSaveContext;
                } else {
                    var_v0_2 = var_a2 - 1;
                    if (var_a2 < 0) {
                        var_v0_2 = 2;
                    }
                    temp_v1_2 = &gSaveContext + (var_v0_2 << 5);
                    sp40 = temp_a0_2;
                    Math_Vec3f_Copy(&temp_a0_2->pos, &gSaveContext.respawn[var_v0_2].pos);
                    Math_Vec3f_Copy(&this->actor.home.pos, &sp40->pos);
                    Math_Vec3f_Copy(&this->actor.prevPos, &sp40->pos);
                    Math_Vec3f_Copy(&this->actor.focus.pos, &sp40->pos);
                    var_v1 = (SaveContext* ) temp_v1_2;
                    this->unk_B68 = (s16) (s32) this->actor.world.pos.y;
                    temp_v0_6 = var_v1->respawn[0].yaw;
                    this->actor.shape.rot.y = temp_v0_6;
                    this->currentYaw = temp_v0_6;
                    this->actor.params = var_v1->respawn[0].playerParams;
                }
                play->actorCtx.flags.switches[2] = var_v1->respawn[0].tempSwitchFlags;
                play->actorCtx.flags.collectible[1] = var_v1->respawn[0].unk_18;
                play->actorCtx.flags.collectible[2] = var_v1->respawn[0].tempCollectFlags;
            }
        }
    }
    if ((var_a2 == 4) || (var_a1 = 0, (gSaveContext.respawnFlag == -4))) {
        var_a1 = 1;
    }
    if (func_801226E0(play, var_a1) == 0) {
        gSaveContext.respawn[0].playerParams = (this->actor.params & 0xFF) | 0xD00;
    }
    gSaveContext.respawn[0].data = 1;
    if (var_a2 == 0) {
        temp_t9_2 = gSaveContext.respawn;
        temp_t8 = &gSaveContext.respawn[2];
        temp_t8->pos.x = temp_t9_2->pos.x;
        temp_t8->pos.y = temp_t9_2->pos.y;
        temp_t8->pos.z = temp_t9_2->pos.z;
        temp_t8->yaw = (s32) temp_t9_2->yaw;
        temp_t8->entranceIndex = (s32) temp_t9_2->entranceIndex;
        temp_t8->tempSwitchFlags = temp_t9_2->tempSwitchFlags;
        temp_t8->unk_18 = temp_t9_2->unk_18;
        temp_t8->tempCollectFlags = temp_t9_2->tempCollectFlags;
    }
    gSaveContext.respawn[2].playerParams = (gSaveContext.respawn[2].playerParams & 0xFF) | 0xD00;
    var_v0_3 = (s32) (this->actor.params & 0xF00) >> 8;
    if (((var_v0_3 == 5) || (var_v0_3 == 6)) && (gSaveContext.save.cutscene >= 0xFFF0)) {
        var_v0_3 = 0xD;
    }
    D_8085D2CC[var_v0_3](play, this, var_a2);
    if ((this->actor.draw != NULL) && (gSaveContext.save.hasTatl != 0)) {
        if ((((gSaveContext.gameMode == 0)) || (gSaveContext.gameMode == 3)) && (play->sceneNum != 8)) {
            // todo: declaration
            this->tatlActor = func_80835C64(play, &this->actor, &this->actor.world.pos, &D_8085D340, 0);
            temp_v1_3 = (s16) gSaveContext.dogParams;
            if (temp_v1_3 != 0) {
                gSaveContext.dogParams = temp_v1_3 | 0x8000;
            }
            if (gSaveContext.powderKegTimer != 0) {
                this->nextModelGroup = Player_ActionToModelGroup(this, PLAYER_AP_POWDER_KEG);
                this->heldItemId = 0xC;
                func_8082F8BC(play, this, PLAYER_AP_POWDER_KEG);
                // todo: declaration
                func_808313F0(this, play);
            } else if (gSaveContext.unk_1014 != 0) {
                // todo: declaration
                func_8082F5FC(this, Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0xB9, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, (s16) 0, (s16) (s32) this->actor.shape.rot.y, (s16) 0, 0x8000));
            // todo: declaration
                func_808313F0(this, play);
            }
        }
    }
    Minimap_SavePlayerRoomInitInfo(play);
    // todo: declaration
    func_80841A50(play, this);
    this->unk_3CF = 0;
    gGameInfo->data[0x220] = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Init.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80842510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808425B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808426F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808430E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80843178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80843EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808442D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808445C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808446F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844D80.s")



#if 0
// Player_UpdateCommon
void func_80844EF8(Player* player, PlayState* play, Input* input) {
    s32 sp58;
    f32 sp50;
    f32 sp44;
    PosRot* sp38;
    CollisionCheckContext* sp34;
    ColliderCylinder* sp2C;                         /* compiler-managed */
    ColliderCylinder* sp28;
    PlayerFunc748 temp_v0_15;
    PlayerFunc748 temp_v0_21;
    PlayerFunc748 temp_v0_22;
    Actor* temp_v0_13;
    Actor* temp_v0_16;
    ColliderCylinder* temp_a1_3;
    ColliderCylinder* temp_a1_4;
    ColliderCylinder* temp_a1_5;
    CollisionCheckContext* temp_a1_6;
    CsCmdActorAction* temp_v0_14;
    LinkAnimationHeader* var_a2_2;
    LinkAnimationHeader* var_v0_2;
    PosRot* temp_a1;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    f32 var_fv0_5;
    f32 var_fv1;
    f32 var_fv1_2;
    s16 temp_v0_19;
    s16 temp_v0_9;
    s32 temp_v0_17;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;
    s8 temp_v0;
    s8 temp_v0_10;
    s8 temp_v0_11;
    s8 temp_v0_4;
    s8 temp_v0_8;
    s8 temp_v1_2;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v1_7;
    u32 temp_a0;
    u32 temp_t7;
    u32 temp_v1_3;
    u32 temp_v1_4;
    u8 temp_a1_2;
    u8 temp_v0_12;
    u8 temp_v0_18;
    u8 temp_v0_20;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 temp_v1;
    u8 temp_v1_5;
    u8 temp_v1_6;

    D_80862B44 = input;
    temp_v0 = player->unk_D6A;
    if (temp_v0 < 0) {
        player->unk_D6A = temp_v0 + 1;
        if (player->unk_D6A == 0) {
            player->unk_D6A = 1;
            play_sound(0x5806U);
        }
    }
    temp_a1 = &player->actor.home;
    sp38 = temp_a1;
    Math_Vec3f_Copy(&player->actor.prevPos, &temp_a1->pos);
    sp44 = fabsf(player->linearVelocity);
    temp_fv1 = (fabsf(Math_SinS(player->unk_B6C) * 800.0f) + 100.0f) * sp44;

    if (temp_fv1 < 300.0f) {
        var_fv0 = 300.0f;
    } else {
        var_fv0 = temp_fv1;
    }

    Math_StepToF(&player->unk_AC0, 0.0f, var_fv0);
    temp_v1 = player->unk_D57;
    if (temp_v1 != 0) {
        player->unk_D57 = temp_v1 - 1;
    }
    temp_v0_2 = player->unk_B5E;
    if (temp_v0_2 != 0) {
        player->unk_B5E = temp_v0_2 - 1;
    }
    temp_v0_3 = player->unk_D6B;
    if (temp_v0_3 != 0) {
        player->unk_D6B = temp_v0_3 - 1;
    }
    temp_v0_4 = player->invincibilityTimer;
    if (temp_v0_4 < 0) {
        player->invincibilityTimer = temp_v0_4 + 1;
    } else if (temp_v0_4 > 0) {
        player->invincibilityTimer = temp_v0_4 - 1;
    }
    temp_v0_5 = player->unk_B64;
    if (temp_v0_5 != 0) {
        player->unk_B64 = temp_v0_5 - 1;
    }
    temp_v0_6 = player->unk_B60;
    if (temp_v0_6 != 0) {
        player->unk_B60 = temp_v0_6 - 1;
    }
    temp_v0_7 = gSaveContext.jinxTimer;
    if (temp_v0_7 != 0) {
        gSaveContext.jinxTimer = temp_v0_7 - 1;
    }
    func_80122C20(play, &player->unk_3D0);
    if ((player->transformation == 0) && (func_8082FBE8(player) != 0)) {
        func_80844D80(play, player);
    }
    if (player->transformation == 2) {
        var_v0 = 0;
        if (player->stateFlags1 & 0x800000) {
            var_v0 = 1;
        }
        Math_StepToF(&player->unk_B08[2], (f32) var_v0, D_8085D3FC[var_v0]);
    }
    func_80832888(player, play);
    if (play->roomCtx.currRoom.enablePosLights != 0) {
        Lights_PointSetColorAndRadius((LightInfo* ) player->unk_508, 0xFFU, 0xFFU, 0xFFU, (s16) 0x3C);
    } else {
        player->unk_514 = -1;
    }
    temp_v0_8 = player->itemActionParam;
    if ((temp_v0_8 == 7) && (player->unk_B28 != 0)) {
        func_808442D8(play, &player->actor);
    } else if (temp_v0_8 == 2) {
        temp_v0_9 = player->unk_B28;
        if (temp_v0_9 < 0) {
            player->unk_B28 = temp_v0_9 + 1;
        }
    }
    if (player->unk_B65 != 0) {
        func_808445C4(play, &player->actor);
    }
    if (player->isBurning != 0) {
        func_808341F4(play, player);
    }
    if (player->stateFlags2 & 0x8000) {
        if (!(player->actor.bgCheckFlags & 1)) {
            func_8082DABC(player);
            Actor_MoveWithGravity(&player->actor);
        }
        func_80843178(play, player);
        sp28 = &player->cylinder;
        sp2C = &player->shieldCylinder;
    } else {
        temp_v0_10 = player->prevBoots;
        temp_v1_2 = player->currentBoots;
        sp2C = player->unk_508;
        if (temp_v0_10 != temp_v1_2) {
            if (temp_v1_2 == 5) {
                if (player->stateFlags1 & 0x800000) {
                    func_8082DC64(play, player);
                    if (player->ageProperties->unk_2C < player->actor.depthInWater) {
                        player->stateFlags2 |= 0x400;
                    }
                }
            } else if ((player->stateFlags1 & 0x800000) && ((temp_v0_10 == 5) || (player->actor.bgCheckFlags & 1))) {
                func_8083B930(play, player);
                player->stateFlags2 &= ~0x400;
                if (player->unk_748 == func_808508C8) {
                    player->unk_AE8 = 0x14;
                }
            }
            player->prevBoots = player->currentBoots;
        }
        if ((player->actor.parent == NULL) && (player->stateFlags1 & 0x800000)) {
            player->actor.parent = player->rideActor;
            func_80837BD0(play, player);
            player->unk_AE8 = -1;
            func_8082DB18(play, player, &D_0400E088);
            func_8082E920(play, player, 0x9B);
        }
        temp_v0_11 = player->unk_ADC;

        if (temp_v0_11 == 0) {
            player->unk_ADD = 0;
        } else if (temp_v0_11 < 0) {
            player->unk_ADC = temp_v0_11 + 1;
        } else {
            player->unk_ADC = temp_v0_11 - 1;
        }

        if (!(player->stateFlags3 & 0x2000)) {
            Math_ScaledStepToS(&player->unk_AAA, 0, 0x190);
        }
        temp_v0_12 = player->transformation;

        if (((s32) temp_v0_12 > 0) && ((s32) temp_v0_12 < 4)) {
            func_800BBB74(&player->eyeTexId, 0x14, 0x50, 3);
        } else {
            func_800BBAC0(&player->eyeTexId, 0x14, 0x50, 6);
        }

        if (play->gameplayFrames & 0x20) {
            var_a2 = 0;
        } else {
            var_a2 = 3;
        }
        player->actor.shape.face = var_a2 + player->eyeTexId;
        if (player->currentMask == 4) {
            func_80124420(player);
        }
        if (func_800B7118(player) != 0) {
            func_808484F0(player);
        }
        if ((play->unk_18844 == 0) && !(player->skelAnime.moveFlags & 0x80)) {
            if (!(player->stateFlags1 & 2) && (player->actor.parent == NULL)) {
                func_80844784(play, player);
            }
            func_80843178(play, player);
        } else {
            D_80862B08 = 0;
            player->unk_D5E = 0;
            if (player->stateFlags1 & 0x800000) {
                temp_v0_13 = player->rideActor;
                player->actor.floorPoly = temp_v0_13->floorPoly;
                player->actor.floorBgId = temp_v0_13->floorBgId;
            }
            D_80862B10 = 0;
            player->unk_B80 = 0.0f;
        }
        func_8083562C(play, &player->actor, player->actor.floorPoly, (s32) player->actor.floorBgId);
        temp_v1_3 = D_80862B10;
        temp_t7 = temp_v1_3 - 1;
        if (temp_v1_3 != 0) {
            D_80862B10 = temp_t7;
            if (D_80862B14 == 0) {
                var_fv1 = D_8085D404[temp_t7];
                if (!(player->stateFlags1 & 0x800000)) {
                    var_fv1 *= 0.25f;
                }
            } else {
                var_fv1 = D_8085D410[D_80862B10];
            }
            sp50 = var_fv1;
            Math_StepToF(&player->unk_B80, var_fv1, var_fv1 * 0.1f);

            if (player->stateFlags1 & 0x800000) {
                var_fv0_2 = 400.0f;
            } else {
                var_fv0_2 = 800.0f;
            }
            Math_ScaledStepToS(&player->unk_B84, D_80862B16, (s16) (s32) (var_fv0_2 * var_fv1));
        } else if (player->unk_B80 != 0.0f) {
            if (player->stateFlags1 & 0x800000) {
                var_fv0_3 = 0.5f;
            } else {
                var_fv0_3 = 2.0f;
            }
            Math_StepToF(&player->unk_B80, 0.0f, var_fv0_3);
        }

        if (!(player->stateFlags1 & 0x20000080) && !(player->stateFlags3 & 0x80) && (player->unk_748 != func_80854430)) {
            func_8083BB4C(play, player);
            if (Play_InCsMode(play) == 0) {
                if ((player->actor.id == 0) && (!(player->stateFlags1 & 0x80000000)) && (gSaveContext.save.playerData.health == 0) && (func_808323C0(&player->actor, play->playerActorCsIds[6]) != 0)) {
                    if (player->stateFlags3 & 0x01000000) {
                        func_808355D8(play, player, &D_0400E2D8);
                    } else {
                        temp_v1_4 = player->stateFlags1;
                        if (temp_v1_4 & 0x206004) {
                            func_8082DD2C(play, player, &D_0400E2D8);
                            func_80833AA0(player, play);
                        } else if ((player->actor.bgCheckFlags & 1) || ((temp_v1_4 & 80000000))) {
                            if (func_801242B4(player) != 0) {
                                var_a2_2 = &D_0400DFE8;
                            } else {
                                var_v0_2 = &D_0400D698;
                                if (player->unk_B65 != 0) {
                                    var_v0_2 = &D_0400DC28;
                                }
                                var_a2_2 = var_v0_2;
                            }
                            func_80831F34(play, player, var_a2_2);
                        }
                    }
                } else {
                    if ((player->actor.parent == NULL) && ((func_8082DA90(play) != 0) || (player->unk_D6B != 0) || (func_80834600(player, play) == 0))) {
                        func_8083827C(player, play);
                    } else {
                        player->unk_B68 = (s16) (s32) player->actor.world.pos.y;
                    }
                    func_808446F4(play, player);
                }
            }
        } else if (!(player->actor.bgCheckFlags & 1) && (player->unk_748 == func_8084D820) && (player->unk_397 == 4)) {
            player->actor.world.pos.y = player->actor.prevPos.y;
        }
        temp_a1_2 = play->csCtx.state;
        if (temp_a1_2 != 0) {
            temp_v1_5 = player->csMode;
            if ((temp_v1_5 != 5) && !(player->stateFlags1 & 0x800000)) {
                temp_a0 = player->stateFlags2;
                if (!(temp_a0 & 0x80) && (player->actor.id == 0)) {
                    temp_v0_14 = play->csCtx.playerAction;
                    if ((temp_v0_14 != NULL) && (*(&D_8085D384 + temp_v0_14->action) != 0)) {
                        func_800B7298(play, NULL, 5U);
                        func_8082DABC(player);
                    } else if ((temp_v1_5 == 0) && !(temp_a0 & 0x08000400) && (temp_a1_2 != 3)) {
                        func_800B7298(play, NULL, 0x14U);
                        func_8082DABC(player);
                    }
                }
            }
        }
        temp_v1_6 = player->csMode;
        if (temp_v1_6 != 0) {
            temp_v0_15 = player->unk_748;
            if ((temp_v1_6 != 6) || !(player->stateFlags1 & 0x04206004)) {
                if (temp_v0_15 != func_8085B08C) {
                    player->unk_AA5 = 4;
                    if (temp_v1_6 == 5) {
                        func_808387A0(play, player);
                        func_8082DAD4(player);
                    }
                }
            } else if (temp_v0_15 != func_8085B08C) {
                func_8085AACC(play, player, 0, play);
            }
        } else {
            player->unk_395 = 0;
        }
        func_8083BF54(play, &player->actor);
        Lights_PointSetPosition((LightInfo* ) sp2C, (s16) (s32) player->actor.world.pos.x, (s16) (s32) (player->actor.world.pos.y + 40.0f), (s16) (s32) player->actor.world.pos.z);
        temp_v0_16 = player->unk_730;
        if (((temp_v0_16 == NULL) || (player->targetActor == temp_v0_16) || (temp_v0_16->hintId == 0xFF)) && (player->tatlTextId == 0)) {
            player->stateFlags2 &= 0xFFDFFFFD;
        }
        player->stateFlags1 &= 0xFFBFEFEF;
        player->stateFlags2 &= 0xFBBEAC92;
        player->stateFlags3 &= 0xE1EFE6AF;
        func_808425B4(player);
        func_8082EB38(play, player);
        if (player->stateFlags1 & 0x800000) {
            D_8085C3E4 = 0.5f;
        } else {
            D_8085C3E4 = 1.0f;
        }
        D_8085C3E8 = 1.0f / D_8085C3E4;
        D_80862B4C = 0;
        D_80862B48 = 0;
        temp_v0_17 = Play_InCsMode(play);
        var_v1 = temp_v0_17;
        D_80862B2C = (s32) player->currentMask;
        if (!(player->stateFlags3 & 4)) {
            sp58 = temp_v0_17;
            player->unk_748(player, play);
            var_v1 = sp58;
        }
        if (var_v1 == 0) {
            func_808426F0(play, player);
        }
        func_80843EC0(play, player);
        temp_v0_18 = player->skelAnime.moveFlags;
        if (temp_v0_18 & 8) {
            if (temp_v0_18 & 4) {
                var_fv0_4 = 1.0f;
            } else {
                var_fv0_4 = player->ageProperties->unk_08;
            }
            AnimationContext_SetMoveActor(play, &player->actor, &player->skelAnime, var_fv0_4);
        }
        func_80832578(player, play);
        if (player->actor.flags & 0x100) {
            player->targetActorDistance = 0.0f;
        } else {
            player->targetActor = NULL;
            player->exchangeItemId = 0;
            player->targetActorDistance = 3.4028235e38f;
        }
        if (!(player->actor.flags & 0x30000000) && (player->unk_AA5 != 5)) {
            player->unk_A90 = NULL;
            player->unk_A94 = 3.4028235e38f;
        }
        if (!(player->stateFlags1 & 0x800)) {
            player->interactRangeActor = NULL;
            player->getItemDirection = 0x6000;
        }
        if (player->actor.parent == NULL) {
            player->rideActor = NULL;
        }
        player->tatlTextId = 0;
        player->unk_B2B = -1;
        player->unk_AA0 = 3.4028235e38f;
        player->doorType = 0;
        player->unk_B75 = 0;
        player->unk_A78 = NULL;
        Math_StepToF(&player->windSpeed, 0.0f, 0.5f);
        if ((player->unk_B62 != 0) || ((gSaveContext.unk_3F28 == 0) && (gSaveContext.save.playerData.magic != 0) && (player->stateFlags1 & 0x10))) {
            func_8082F1AC(&play->state, player);
        }
        temp_fv0 = player->actor.world.pos.y - player->actor.prevPos.y;
        var_fv1_2 = ((player->bodyPartsPos[3].y + player->bodyPartsPos[6].y) * 0.5f) + temp_fv0;
        var_fv0_5 = temp_fv0 + (player->bodyPartsPos[7].y + 10.0f);
        if (player->cylinder.info.toucher.dmgFlags == 0x80000) {
            player->cylinder.dim.height = 0x50;
            var_fv1_2 = ((var_fv0_5 + var_fv1_2) * 0.5f) - 40.0f;
        } else {
            player->cylinder.dim.height = (s16) (s32) (var_fv0_5 - var_fv1_2);
            temp_v0_19 = player->cylinder.dim.height;
            if (temp_v0_19 < 0) {
                temp_fa0 = var_fv0_5;
                var_fv0_5 = var_fv1_2;
                var_fv1_2 = temp_fa0;
                player->cylinder.dim.height = -temp_v0_19;
            }
        }
        temp_fa0_2 = player->actor.world.pos.y;
        player->cylinder.dim.yShift = (s16) (s32) (var_fv1_2 - temp_fa0_2);
        if (player->unk_B62 != 0) {
            player->shieldCylinder.base.acFlags = 0;
            player->shieldCylinder.info.toucher.dmgFlags = 0x80000;
            player->shieldCylinder.info.toucherFlags = 1;
            player->shieldCylinder.info.bumperFlags = 0;
            player->shieldCylinder.dim.height = 0x50;
            player->shieldCylinder.dim.radius = 0x32;
            temp_a1_3 = &player->shieldCylinder;
            player->shieldCylinder.dim.yShift = (s16) (s32) ((((var_fv0_5 + var_fv1_2) * 0.5f) - 40.0f) - temp_fa0_2);
            sp2C = temp_a1_3;
            Collider_UpdateCylinder(&player->actor, temp_a1_3);
            CollisionCheck_SetAT(play, &play->colChkCtx, &sp2C->base);
        } else if (player->stateFlags1 & 0x400000) {
            temp_v0_20 = player->transformation;
            if ((temp_v0_20 == 1) || (temp_v0_20 == 3)) {
                player->shieldCylinder.base.acFlags = 0x15;
                player->shieldCylinder.info.toucher.dmgFlags = 0x100000;
                player->shieldCylinder.info.toucherFlags = 0;
                player->shieldCylinder.info.bumperFlags = 1;
                if (temp_v0_20 == 1) {
                    player->shieldCylinder.dim.height = 0x23;
                } else {
                    player->shieldCylinder.dim.height = 0x1E;
                }
                temp_a1_4 = &player->shieldCylinder;
                if (player->transformation == 1) {
                    player->shieldCylinder.dim.radius = 0x1E;
                } else {
                    player->shieldCylinder.dim.radius = 0x14;
                }
                player->shieldCylinder.dim.yShift = 0;
                sp2C = temp_a1_4;
                Collider_UpdateCylinder(&player->actor, temp_a1_4);
                CollisionCheck_SetAC(play, &play->colChkCtx, &sp2C->base);
                player->cylinder.dim.yShift = 0;
                player->cylinder.dim.height = player->shieldCylinder.dim.height;
            } else {
                player->cylinder.dim.height = (s16) (s32) ((f32) player->cylinder.dim.height * 0.8f);
            }
        }
        temp_a1_5 = &player->cylinder;
        sp2C = &player->shieldCylinder;
        sp28 = temp_a1_5;
        Collider_UpdateCylinder(&player->actor, temp_a1_5);
        if (!(player->stateFlags2 & 0x4000)) {
            if (!(player->stateFlags1 & 0x806084) && !(player->stateFlags3 & 0x10000000)) {
                temp_v0_21 = player->unk_748;
                if ((temp_v0_21 != func_808561B0) && (temp_v0_21 != func_80853D68) && (player->actor.draw != NULL)) {
                    if ((player->actor.id != 0) && (player->csMode == 0x6E)) {
                        player->cylinder.dim.radius = 8;
                    }
                    CollisionCheck_SetOC(play, &play->colChkCtx, &sp28->base);
                }
            }
            if (!(player->stateFlags1 & 0x04000080) && (player->invincibilityTimer <= 0)) {
                temp_v0_22 = player->unk_748;
                if ((temp_v0_22 != func_808561B0) && ((temp_v0_22 != func_80857BE8) || (player->unk_AE7 != 1))) {
                    temp_a1_6 = &play->colChkCtx;
                    if (player->cylinder.base.atFlags != 0) {
                        sp34 = temp_a1_6;
                        CollisionCheck_SetAT(play, temp_a1_6, &sp28->base);
                    }
                    CollisionCheck_SetAC(play, temp_a1_6, &sp28->base);
                }
            }
        }
        AnimationContext_SetNextQueue(play);
    }
    func_801229FC(player);
    Math_Vec3f_Copy(&sp38->pos, &player->actor.world.pos);

    if ((player->stateFlags1 & 0x30000080) || (player != GET_PLAYER(play))) {
        player->actor.colChkInfo.mass = 0xFF;
    } else {
        player->actor.colChkInfo.mass = *(D_8085D174 + player->transformation);
    }

    player->stateFlags3 &= ~0x404;
    Collider_ResetCylinderAC(play, &sp28->base);
    Collider_ResetCylinderAC(play, &sp2C->base);
    Collider_ResetCylinderAT(play, &sp2C->base);
    Collider_ResetQuadAT(play, &player->meleeWeaponQuads[0].base);
    Collider_ResetQuadAT(play, &player->meleeWeaponQuads[1].base);
    Collider_ResetQuadAC(play, &player->shieldQuad.base);
    temp_v1_7 = player->actor.bgCheckFlags;
    if (!(temp_v1_7 & 1) || (temp_v1_7 & 2) || (player->actor.floorBgId != 0x32)) {
        player->unk_AC0 = 0.0f;
    }
    player->actor.shape.yOffset = player->unk_ABC + player->unk_AC0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844EF8.s")
#endif

extern Vec3f D_8085D41C;

#ifdef NON_MATCHING
// in-function static bss
void Player_Update(Actor* thisx, PlayState* play) {
    static Vec3f D_80862AF0; // sDogSpawnPos
    Player* this = (Player* ) thisx;
    s32 dogParams;
    s32 pad;
    Input input;
    s32 pad2;

    this->stateFlags3 &= ~0x10;
    if (gSaveContext.dogParams < 0) {
        if (Object_GetIndex(&play->objectCtx, 0x132) < 0) {
            gSaveContext.dogParams = 0;
        } else {
            Actor* dog;

            gSaveContext.dogParams &= (u16)~0x8000;
            func_80835BC8(this, &this->actor.world.pos, &D_8085D41C, &D_80862AF0);

            dogParams = gSaveContext.dogParams;

            dog = Actor_Spawn(&play->actorCtx, play, 0xE2, D_80862AF0.x, D_80862AF0.y, D_80862AF0.z, 0, this->actor.shape.rot.y, 0, dogParams | 0x8000);
            if (dog != NULL) {
                dog->room = -1;
            }
        }
    }

    if ((this->interactRangeActor != NULL) && (this->interactRangeActor->update == NULL)) {
        this->interactRangeActor = NULL;
    }

    if ((this->heldActor != NULL) && (this->heldActor->update == NULL)) {
        func_8082DCA0(play, this);
    }

    if ((play->actorCtx.unk268 != 0) && (this == GET_PLAYER(play))) {
        input = play->actorCtx.unk_26C;
    } else if ((this->csMode == 5) || (this->stateFlags1 & 0x20000020) || (this != GET_PLAYER(play)) || (func_8082DA90(play) != 0) || (gSaveContext.save.playerData.health == 0)) {
        bzero(&input, sizeof(Input));
        this->unk_B68 = this->actor.world.pos.y;
    } else {
        input = play->state.input[0];
        if (this->unk_B5E != 0) {
            input.cur.button &= ~0xC008;
            input.press.button &= ~0xC008;
        }
    }

    func_80844EF8(this, play, &input);
    play->actorCtx.unk268 = 0;
    bzero(&play->actorCtx.unk_26C, sizeof(Input));

    gGameInfo->data[0x214] = this->actor.world.pos.x;
    gGameInfo->data[0x215] = this->actor.world.pos.y;
    gGameInfo->data[0x216] = this->actor.world.pos.z;
    gGameInfo->data[0x217] = this->actor.world.rot.y;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Update.s")
#endif

void Player_DrawGameplay(PlayState* play, Player* this, s32 lod, Gfx* cullDList, OverrideLimbDrawFlex overrideLimbDraw) {
    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0C, cullDList);
    gSPSegment(POLY_XLU_DISP++, 0x0C, cullDList);

    Player_DrawImpl(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, lod, this->transformation, 0, this->actor.shape.face, overrideLimbDraw, func_80128BD0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80846460(Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80846460.s")


extern struct_80124618 D_8085D510[2];
extern struct_80124618 D_8085D520[2];
extern struct_80124618 D_8085D530[2];
extern struct_80124618 D_8085D540[2];
extern struct_80124618* D_8085D550[3];
extern struct_80124618* D_8085D55C[3];
extern struct_80124618* D_8085D568[3];
extern Gfx* D_8085D574[3];


extern Color_RGB8 D_8085D580;
extern Color_RGB8 D_8085D584;
extern Gfx D_0600C540[];

extern UNK_TYPE D_06013138;

extern UNK_TYPE D_0400E318;
extern UNK_TYPE D_0400E330;
extern UNK_TYPE D_0400E348;
extern UNK_TYPE D_0400E430;
extern Gfx D_04050D10[];
extern Gfx D_040528B0[];
extern Gfx D_060127B0[];
extern Gfx D_060134D0[];
extern UNK_TYPE D_06014684;

#if 0
void Player_Draw(Actor* thisx, PlayState* play) {
    Player* this = (Player* ) thisx;
    s32 spEC;
    struct_80124618** spE8;
    struct_80124618** spE4;
    f32 spE0;
    Gfx** spDC;
    s32 spD8;
    Gfx* spCC;
    //GraphicsContext* spC4;
    Color_RGB8 spBC;
    f32 spB8;
    f32 spB4;
    u8 sp9B;
    s32 (*sp84)(PlayState*, s32, Gfx**, Vec3f*, Vec3s*, Actor*);
    s32 sp80;
    Vec3f sp74;
    s16 sp70;
    f32 sp64;
    Vec3f* sp48;
    //GraphicsContext* temp_s0;
    //GraphicsContext* var_a0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv1;
    s16 temp_s0_2;
    s16 temp_v0_10;
    s16 temp_v0_7;
    s8 temp_v1;
    u32 temp_v0_15;
    u32 temp_v1_2;

    spEC = 0;
    Math_Vec3f_Copy(&this->unk_D6C, this->bodyPartsPos);
    if (this->stateFlags3 & 0x40100) {
        spE8 = D_8085D550;
        // temp_s0 = play->state.gfxCtx;

        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Push();
        func_8012C268(play);
        spEC = 1;
        if (this->stateFlags3 & 0x40000) {
            Matrix_SetTranslateRotateYXZ(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, &gZeroVec3s);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            spE8 = D_8085D568;
            spE0 = 0.0f;
        } else {
            Matrix_Translate(0.0f, -this->unk_ABC, 0.0f, MTXMODE_APPLY);
            temp_ft2 = (f32) (this->unk_AE8 - 6);
            spE0 = temp_ft2;
            if (temp_ft2 < 0.0f) {
                spE8 = D_8085D55C;
                spE0 = (f32) this->unk_B86;
            }
        }
        spDC = D_8085D574;
        sp48 = &this->unk_AF0[1];
        spD8 = 0;
        spE4 = spE8;
        do {
            Matrix_Push();
            func_80124618(*spE4, spE0, sp48);
            Matrix_Scale(this->unk_AF0[1].x, this->unk_AF0[1].y, this->unk_AF0[1].z, MTXMODE_APPLY);

            #if 0
            temp_v0_2 = temp_s0->polyOpa.p;
            temp_s0->polyOpa.p = temp_v0_2 + 8;
            temp_v0_2->words.w0 = 0xDA380003;
            spCC = temp_v0_2;
            spCC->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
            #endif
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            #if 0
            temp_v0_3 = temp_s0->polyOpa.p;
            temp_s0->polyOpa.p = temp_v0_3 + 8;
            temp_v0_3->words.w0 = 0xDE000000;
            temp_v0_3->words.w1 = *spDC;
            #endif
            gSPDisplayList(POLY_OPA_DISP++, *spDC);

            Matrix_Pop();
            spD8 = spD8 + 1;
            spDC += 4;
            spE4 += 4;
        } while (spD8 != 3);
        Matrix_Pop();

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if ((this->stateFlags2 & 0x20000000) && (this->unk_ABC > -3900.0f)) {
        OPEN_DISPS(play->state.gfxCtx);

        //spC4 = play->state.gfxCtx;
        if (spEC == 0) {
            func_8012C268(play);
        }

        func_8012C2DC(play->state.gfxCtx);
        func_800B8050(&this->actor, play, 0);
        func_800B8118(&this->actor, play, 0);
        func_80122868(play, this);
        if (this->stateFlags3 & 0x1000) {
            temp_fv0 = this->unk_ABC;
            spB8 = temp_fv0 + 1.0f;
            spB4 = 1.0f - (temp_fv0 * 0.5f);
            func_80846460(this);
            Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (1200.0f * this->actor.scale.y * spB8), this->actor.world.pos.z, MTXMODE_NEW);
            if (this->unk_B86 != 0) {
                Matrix_RotateYS(this->unk_B28, MTXMODE_APPLY);
                Matrix_RotateXS(this->unk_B86, MTXMODE_APPLY);
                Matrix_RotateYS((s16) (this->unk_B28 * -1), MTXMODE_APPLY);
            }
            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
            Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
            if (spB8 < spB4) {
                var_fv1 = spB4;
            } else {
                var_fv1 = spB8;
            }
            Matrix_Scale(this->actor.scale.x * spB4 * 1.15f, this->actor.scale.y * spB8 * 1.15f, var_fv1 * this->actor.scale.z * 1.15f, MTXMODE_APPLY);
            Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
            Scene_SetRenderModeXlu(play, 0, 1U);
            Lib_LerpRGB(&D_8085D580, &D_8085D584, this->unk_B08[2], &spBC);

            #if 0
            temp_v0_4 = spC4->polyOpa.p;
            spC4->polyOpa.p = temp_v0_4 + 8;
            temp_v0_4->words.w0 = 0xFB000000;
            temp_v0_4->words.w1 = ((u8) spBC.r << 0x18) | (spBC.g << 0x10) | (spBC.b << 8) | 0xFF;
            #endif
            gDPSetEnvColor(POLY_OPA_DISP++, (u8) spBC.r, spBC.g, spBC.b, 255);

            #if 0
            temp_v0_5 = spC4->polyOpa.p;
            spC4->polyOpa.p = temp_v0_5 + 8;
            temp_v0_5->words.w0 = 0xDA380003;
            temp_v0_5->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
            #endif
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            #if 0
            temp_v0_6 = spC4->polyOpa.p;
            spC4->polyOpa.p = temp_v0_6 + 8;
            temp_v0_6->words.w0 = 0xDE000000;
            temp_v0_6->words.w1 = (u32) &D_0600BDD8;
            #endif
            gSPDisplayList(POLY_OPA_DISP++, D_0600BDD8);


            temp_v0_7 = this->unk_B88;

            if (temp_v0_7 != 0) {
                if (temp_v0_7 < 3) {
                    func_80124618(D_8085D540, (f32) temp_v0_7, this->unk_AF0);
                    Matrix_Scale(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, MTXMODE_APPLY);
                    #if 0
                    temp_v0_8 = spC4->polyOpa.p;
                    spC4->polyOpa.p = temp_v0_8 + 8;
                    temp_v0_8->words.w0 = 0xDA380003;
                    temp_v0_8->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                    #endif
                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
                #if 0
                temp_v0_9 = spC4->polyOpa.p;
                spC4->polyOpa.p = temp_v0_9 + 8;
                temp_v0_9->words.w0 = 0xDE000000;
                temp_v0_9->words.w1 = (u32) &D_0600C540;
                #endif
                gSPDisplayList(POLY_OPA_DISP++, D_0600C540);
            }

            func_80122BA4(play, &this->unk_3D0, 1, 0xFF);
            func_80122BA4(play, &this->unk_3D0, 2, 0xFF);
            temp_v0_10 = this->unk_B88;

            if (temp_v0_10 < 3) {
                temp_v1 = this->unk_AE7;
                if (temp_v1 >= 5) {
                    temp_fa1 = (f32) (temp_v1 - 4) * 0.02f;

                    if (temp_v0_10 != 0) {
                        sp9B = (temp_v0_10 * -0x55) + 0xFF;
                    } else {
                        sp9B = (200.0f * temp_fa1);
                    }

                    if (temp_v0_10 != 0) {
                        var_fa1 = 0.65f;
                    } else {
                        var_fa1 = temp_fa1 * 1.0f;
                    }

                    Matrix_Scale(1.0f, var_fa1, var_fa1, MTXMODE_APPLY);

                    #if 0
                    temp_v0_11 = spC4->polyXlu.p;
                    spC4->polyXlu.p = temp_v0_11 + 8;
                    temp_v0_11->words.w0 = 0xDA380003;
                    temp_v0_11->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                    #endif
                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&D_06013138));

                    #if 0
                    temp_v0_12 = spC4->polyXlu.p;
                    spC4->polyXlu.p = temp_v0_12 + 8;
                    temp_v0_12->words.w0 = 0xFB000000;
                    temp_v0_12->words.w1 = sp9B | 0x9B000000;
                    #endif
                    gDPSetEnvColor(POLY_XLU_DISP++, 155, 0, 0, sp9B);

                    #if 0
                    temp_v0_13 = spC4->polyXlu.p;
                    spC4->polyXlu.p = temp_v0_13 + 8;
                    temp_v0_13->words.w1 = (u32) &D_060127B0;
                    temp_v0_13->words.w0 = 0xDE000000;
                    #endif
                    gSPDisplayList(POLY_XLU_DISP++, D_060127B0);

                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&D_06014684));

                    #if 0
                    temp_v0_14 = spC4->polyXlu.p;
                    spC4->polyXlu.p = temp_v0_14 + 8;
                    temp_v0_14->words.w1 = (u32) &D_060134D0;
                    temp_v0_14->words.w0 = 0xDE000000;
                    #endif
                    gSPDisplayList(POLY_XLU_DISP++, D_060134D0);
                }
            }
        } else if ((this->transformation == 1) && (this->stateFlags1 & 0x400000)) {
            func_80846460(this);
            SkelAnime_DrawFlexOpa(play, this->unk_2C8.skeleton, this->unk_2C8.jointTable, this->unk_2C8.dListCount, NULL, NULL, NULL);
        } else {
            sp84 = func_80125D4C;

            if ((this->csMode != 0) || (this->actor.projectedPos.z < 320.0f)) {
                sp80 = 0;
            } else {
                sp80 = 1;
            }

            if (this->stateFlags1 & 0x100000) {
                SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->actor.focus.pos, &sp74);
                if (sp74.z < -4.0f) {
                    sp84 = func_801262C8;
                }
            }

            if (this->stateFlags2 & 0x04000000) {
                temp_v0_15 = play->gameplayFrames;
                temp_s0_2 = temp_v0_15 * 0x258;
                sp70 = temp_v0_15 * 0x3E8;
                Matrix_Push();
                this->actor.scale.y = -this->actor.scale.y;
                Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y + (2.0f * this->actor.depthInWater) + (this->unk_ABC * this->actor.scale.y), this->actor.world.pos.z, &this->actor.shape.rot);
                Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
                Matrix_RotateXS(temp_s0_2, MTXMODE_APPLY);
                Matrix_RotateYS(sp70, MTXMODE_APPLY);
                Matrix_Scale(1.1f, 0.95f, 1.05f, MTXMODE_APPLY);
                Matrix_RotateYS(-sp70, MTXMODE_APPLY);
                Matrix_RotateXS(-temp_s0_2, MTXMODE_APPLY);
                Player_DrawGameplay(play, &this->actor, sp80, gCullFrontDList, sp84);
                this->actor.scale.y = -this->actor.scale.y;
                Matrix_Pop();
            }

            #if 0
            temp_v0_16 = spC4->polyOpa.p;
            spC4->polyOpa.p = temp_v0_16 + 8;
            temp_v0_16->words.w1 = 0;
            temp_v0_16->words.w0 = 0xD9FFF9FF;
            temp_v0_17 = spC4->polyXlu.p;
            spC4->polyXlu.p = temp_v0_17 + 8;
            temp_v0_17->words.w1 = 0;
            temp_v0_17->words.w0 = 0xD9FFF9FF;
            #endif
            gSPClearGeometryMode(POLY_OPA_DISP++, G_CULL_BOTH);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BOTH);

            if ((this->transformation == 2) && (this->unk_B62 != 0) && !(this->stateFlags3 & 0x8000)) {
                Matrix_Push();
                Matrix_RotateXS(-0x4000, MTXMODE_APPLY);
                Matrix_Translate(0.0f, 0.0f, -1800.0f, MTXMODE_APPLY);
                Player_DrawZoraShield(play, this);
                Matrix_Pop();
            }

            Player_DrawGameplay(play, &this->actor, sp80, gCullBackDList, sp84);
        }

        func_801229A0(play, this);

        if (this->stateFlags2 & 0x4000) {
            temp_fa0 = this->unk_B48;
            #if 0
            temp_v0_18 = spC4->polyXlu.p;
            spC4->polyXlu.p = temp_v0_18 + 8;
            temp_v0_18->words.w0 = 0xDB060020;
            temp_v1_2 = play->gameplayFrames;
            temp_v0_18->words.w1 = Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0U, -(s32) temp_v1_2 & 0x7F, 0x20, 0x20, 1, 0U, ((s32) temp_v1_2 * -2) & 0x7F, 0x20, 0x20);
            #endif
            temp_v1_2 = play->gameplayFrames;
            gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0U, -(s32) temp_v1_2 & 0x7F, 0x20, 0x20, 1, 0U, ((s32) temp_v1_2 * -2) & 0x7F, 0x20, 0x20));

            Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);

            #if 0
            temp_v0_19 = spC4->polyXlu.p;
            spC4->polyXlu.p = temp_v0_19 + 8;
            temp_v0_19->words.w0 = 0xDA380003;
            temp_v0_19->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
            #endif
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            #if 0
            temp_v0_20 = spC4->polyXlu.p;
            spC4->polyXlu.p = temp_v0_20 + 8;
            temp_v0_20->words.w1 = 0x003264FF;
            temp_v0_20->words.w0 = 0xFB000000;
            #endif
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0x32, 0x64, 255);

            #if 0
            temp_v0_21 = spC4->polyXlu.p;
            spC4->polyXlu.p = temp_v0_21 + 8;
            temp_v0_21->words.w1 = (u32) &D_04050D10;
            temp_v0_21->words.w0 = 0xDE000000;
            #endif
            gSPDisplayList(POLY_XLU_DISP++, D_04050D10);
        }

        if (this->unk_B2A > 0) {
            Player_DrawGetItem(play, this);
        }

        func_80122D44(play, &this->unk_3D0);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    play->actorCtx.unk5 &= 0xFFF7;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Draw.s")
#endif

void Player_Destroy(Actor* thisx, PlayState* play) {
    Player* this = (Player* ) thisx;

    Effect_Destroy(play, this->meleeWeaponEffectIndex[0]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[1]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[2]);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyCylinder(play, &this->cylinder);
    Collider_DestroyCylinder(play, &this->shieldCylinder);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->shieldQuad);
    ZeldaArena_Free(this->giObjectSegment);
    ZeldaArena_Free(this->maskObjectSegment);
    func_80115D5C(&play->state);
    func_80831454(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084748C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808475B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808477D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808479F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808481CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808482E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808484CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808484F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808487B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084894C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808490B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808491B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084923C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808492C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808496AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808497A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A26C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AEEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B0EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B4A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BE40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CA24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E4E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E65C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084ED9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084EE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084EF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F1B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F4E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FE7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808505D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808508C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808513EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808516B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808519FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808521E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085255C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808525C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085269C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808530E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808534C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808540A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085421C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085437C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085439C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808546D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808548B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808550D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808553F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808561B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808566C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085687C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808573A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808576BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808577E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808591BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085929C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808594D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808595B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085968C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085978C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808599DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859FF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A1D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A40C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A66C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085ABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AD5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085ADA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B930.s")
