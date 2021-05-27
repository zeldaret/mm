#include "z_obj_mu_pict.h"

#define FLAGS 0x00000009

#define THIS ((ObjMuPict*)thisx)

void ObjMuPict_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C06B5C(ObjMuPict* this);
void func_80C06B70(ObjMuPict* this, GlobalContext* globalCtx);
void func_80C06C54(ObjMuPict* this);
void func_80C06C68(ObjMuPict* this, GlobalContext* globalCtx);
void func_80C06CC4(ObjMuPict* this);
void func_80C06CD8(ObjMuPict* this, GlobalContext* globalCtx);
void func_80C06D90(ObjMuPict* this, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mu_Pict_InitVars = {
    ACTOR_OBJ_MU_PICT,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMuPict),
    (ActorFunc)ObjMuPict_Init,
    (ActorFunc)ObjMuPict_Destroy,
    (ActorFunc)ObjMuPict_Update,
    (ActorFunc)ObjMuPict_Draw,
};
*/

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Init.asm")
void ObjMuPict_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMuPict* this = THIS;
    if ((gSaveContext.weekEventReg[75] & 0x20) == 0) {
        if ((gSaveContext.weekEventReg[52] & 0x20) == 0) {
            Actor_MarkForDeath(&this->actor);
        }
    }
    func_80C06D90(this, globalCtx);
    this->unk14A = ((this->actor.params & 0xF000) >> 0xC);
    this->actor.targetMode = 6;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    this->unk148 = 0;
    func_80C06B5C(this);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Destroy.asm")
void ObjMuPict_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06B5C.asm")
void func_80C06B5C(ObjMuPict* this) {
    this->actionFunc = func_80C06B70;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06B70.asm")
// void func_80C06B70(ObjMuPict* this, GlobalContext* globalCtx) {
//     s16 sp26;
//     s16 temp_v1;
//     s32 phi_v0;

//     temp_v1 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
//     sp26 = temp_v1;
//     if (func_800B84D0(this, globalCtx)) {
//         if (this->actor.cutscene < 0) {
//             if (ActorCutscene_GetCurrentIndex(this) == 0x7C) {
//                 ActorCutscene_Stop(0x7C);
//             }
//             ActorCutscene_SetIntentToPlay(this->actor.cutscene);
//             func_80C06DC8(this, globalCtx);
//             func_80C06C54(this);
//             return;
//         }
//         func_80C06DC8(this, globalCtx);
//         func_80C06CC4(this);
//         return;
//     }
//     phi_v0 = ABS_ALT(temp_v1);
//     if (phi_v0 < 0x2AAA) {
//         func_800B8614(this, globalCtx, 80.0f);
//     }
// }

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06C54.asm")
void func_80C06C54(ObjMuPict* this) {
    this->actionFunc = func_80C06C68;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06C68.asm")
void func_80C06C68(ObjMuPict* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene) != 0) {
        ActorCutscene_Start(this->actor.cutscene, this);
        func_80C06CC4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06CC4.asm")
void func_80C06CC4(ObjMuPict* this) {
    this->actionFunc = func_80C06CD8;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06CD8.asm")

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06D90.asm")
void func_80C06D90(ObjMuPict* this, GlobalContext* globalCtx) {
    struct Actor* actorPtr = globalCtx->actorCtx.actorList[4].first;

    while (actorPtr != 0) {
        if (actorPtr->id == ACTOR_EN_HGO) {
            this->actor.parent = actorPtr;
            return;
        }
        actorPtr = actorPtr->next;
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06DC8.asm")
void func_80C06DC8(ObjMuPict* this, GlobalContext* globalCtx) {
    if (this->unk14A == 0) {
        if (this->unk148 == 0) {
            this->unk148 = 1;
            func_801518B0(globalCtx, 0x159A, &this->actor);
            this->unk14C = 0x159A;
        } else {
            func_801518B0(globalCtx, 0x159D, &this->actor);
            this->unk14C = 0x159D;
        }
    } else if (this->unk148 == 0) {
        this->unk148 = 1;
        func_801518B0(globalCtx, 0x15A0, &this->actor);
        this->unk14C = 0x15A0;
    } else {

        func_801518B0(globalCtx, 0x15A3, &this->actor);
        this->unk14C = 0x15A3;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06E88.asm")
// void func_80C06E88(ObjMuPict* this, GlobalContext* globalCtx) {
//     u32 temp_t7;

//     if (func_80147624(globalCtx) != 0) {
//         temp_t7 = (u16)this->unk14C - 0x159A;
//         switch (temp_t7 < 0xAU) {
//                 // goto **(&jtbl_D_80C0701C + (temp_t7 * 4));
//             case 0:
//                 func_801518B0(globalCtx, 0x159BU, &this->actor);
//                 this->unk14C = 0x159B;
//                 break;
//             case 1:
//                 func_801518B0(globalCtx, 0x159CU, &this->actor);
//                 this->unk14C = 0x159C;
//                 break;
//             case 3:
//                 func_801518B0(globalCtx, 0x159EU, &this->actor);
//                 this->unk14C = 0x159E;
//                 break;
//             case 4:
//                 func_801518B0(globalCtx, 0x159FU, &this->actor);
//                 this->unk14C = 0x159F;
//                 break;
//             case 6:
//                 func_801518B0(globalCtx, 0x15A1U, &this->actor);
//                 this->unk14C = 0x15A1;
//                 break;
//             case 7:
//                 func_801518B0(globalCtx, 0x15A2U, &this->actor);
//                 this->unk14C = 0x15A2;
//                 break;
//             case 9:
//                 func_801518B0(globalCtx, 0x15A4U, &this->actor);
//                 this->unk14C = 0x15A4;
//                 break;
//         }
//     }
// }

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Update.asm")
void ObjMuPict_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMuPict* this = THIS;
    this->actionFunc(this, globalCtx);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Draw.asm")
void ObjMuPict_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
