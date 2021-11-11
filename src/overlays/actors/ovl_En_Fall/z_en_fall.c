/*
 * File: z_en_fall.c
 * Overlay: ovl_En_Fall
 * Description: The Moon and related effects
 */

#include "z_en_fall.h"

#define FLAGS 0x00000030

#define THIS ((EnFall*)thisx)

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A6C3FC(EnFall* this, GlobalContext* globalCtx);
void func_80A6C9A8(EnFall* this, GlobalContext* globalCtx);
void func_80A6CA9C(EnFall* this, GlobalContext* globalCtx);
void func_80A6CB74(EnFall* this, GlobalContext* globalCtx);
void func_80A6CD38(EnFall* this, GlobalContext* globalCtx);
void func_80A6CD74(EnFall* this, GlobalContext* globalCtx);
void func_80A6CF60(EnFall* this, GlobalContext* globalCtx);
void func_80A6CF70(EnFall* this, GlobalContext* globalCtx);
void func_80A6D220(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D88C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DD3C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D698(Actor* thisx, GlobalContext* globalCtx);
void func_80A6E07C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC20(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC40(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D75C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6E214(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D98C(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)NULL,
};

#endif

extern UNK_TYPE D_06000198;
extern UNK_TYPE D_060004C0;
extern UNK_TYPE D_060010E0;
extern UNK_TYPE D_060011D0;
extern UNK_TYPE D_06001220;
extern UNK_TYPE D_06002970;
extern UNK_TYPE D_06004E38;
extern UNK_TYPE D_060077F0;

void func_80A6BF90(EnFall* this, GlobalContext* globalCtx) {
    u16 temp_v0;
    u16 temp_v1;
    f32 phi_f0;

    temp_v0 = gSaveContext.time;
    temp_v1 = this->unk_144;
    if (temp_v0 < temp_v1) {
        phi_f0 = 1.0f - (((f32)temp_v1 - (f32)temp_v0) * (1.0f / 0x10000));
    } else {
        phi_f0 = ((f32)temp_v0 - (f32)temp_v1) * (1.0f / 0x10000);
    }
    switch (CURRENT_DAY) {
        case 0:
            Actor_SetScale(&this->actor, this->unk_14C * 1.2f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 1:
            Actor_SetScale(&this->actor, this->unk_14C * 2.4f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 2:
            Actor_SetScale(&this->actor, this->unk_14C * 3.6f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 3:
            Actor_SetScale(&this->actor, this->unk_14C * 3.6f);
            if (EN_FALL_TYPE(&this->actor) == 0xC) {
                this->actor.world.pos.y = this->actor.home.pos.y + (phi_f0 * 6700.0f * (this->unk_14C * 6.25f));
            } else {
                this->actor.world.pos.y = this->actor.home.pos.y - (phi_f0 * 6700.0f * (this->unk_14C * 6.25f));
            }
            break;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C1DC.s")

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 objectIndex;

    this->unk_150 = 0.0f;
    this->unk_154 = 0;
    switch (EN_FALL_SCALE(&this->actor)) {
        case 1:
            this->unk_14C = 0.08f;
            break;
        case 2:
            this->unk_14C = 0.04f;
            break;
        case 3:
            this->unk_14C = 0.02f;
            break;
        case 4:
            this->unk_14C = 0.01f;
            break;
        default:
            this->unk_14C = 0.16f;
            break;
    }
    switch (EN_FALL_TYPE(&this->actor)) {
        case 5:
        case 6:
        case 12:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_LODMOON);
            break;
        case 8:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MOONSTON);
            break;
        case 10:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL2);
            break;
        default:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL);
            break;
    }
    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->unk_148 = objectIndex;
    this->actionFunc = func_80A6C3FC;
}

void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

Actor* func_80A6C3AC(GlobalContext* globalCtx) {
    Actor* temp_v1;

    temp_v1 = globalCtx->actorCtx.actorList[ACTORCAT_ITEMACTION].first;
    while (temp_v1 != NULL) {
        if (temp_v1->id == ACTOR_EN_FALL && EN_FALL_TYPE(temp_v1) == 0) {
            return temp_v1;
        }
        temp_v1 = temp_v1->next;
    }
    return NULL;
}

void func_80A6C3FC(EnFall* this, GlobalContext* globalCtx) {
    Actor* temp_v0;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_148)) {
        this->actor.objBankIndex = this->unk_148;
        this->actionFunc = func_80A6CD74;
        switch (EN_FALL_TYPE(&this->actor)) {
            case 1:
                this->actor.draw = func_80A6D88C;
                this->actionFunc = func_80A6CD38;
                Actor_SetScale(&this->actor, this->unk_14C);
                break;
            case 7:
                this->actor.draw = func_80A6D88C;
                this->actionFunc = func_80A6CB74;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                if ((gSaveContext.weekEventReg[0x19] & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 9:
                this->actionFunc = func_80A6CD38;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                this->actor.draw = func_80A6D88C;
                if ((gSaveContext.weekEventReg[0x19] & 2) != 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 2:
                this->actor.draw = func_80A6D88C;
                Actor_SetScale(&this->actor, this->unk_14C * 5.3999996f);
                this->actionFunc = func_80A6C9A8;
                break;
            case 3:
                this->actor.update = func_80A6D220;
                this->actor.draw = func_80A6DD3C;
                this->unk_14C = 1.0f;
                this->actor.shape.rot.z = 0;
                this->unk_150 = 0.0f;
                this->unk_158 = 0x64;
                this->actor.shape.rot.x = this->actor.shape.rot.z;
                break;
            case 4:
                this->actor.update = func_80A6D698;
                this->actor.draw = func_80A6E07C;
                this->unk_14C = 1.0f;
                func_80A6C1DC(this);
                Actor_SetScale(&this->actor, 1.0f);
                this->actor.shape.rot.x = 0;
                break;
            case 5:
                this->actor.draw = func_80A6DC20;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
            case 6:
            case 12:
                this->actor.draw = func_80A6DC40;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
            case 8:
                this->actor.update = EnFall_Update;
                this->actor.draw = NULL;
                this->actionFunc = func_80A6CF70;
                Actor_SetScale(&this->actor, 0.02f);
                if ((globalCtx->actorCtx.unk5 & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                temp_v0 = func_80A6C3AC(globalCtx);
                this->actor.child = temp_v0;
                if (temp_v0 == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 10:
                this->actor.draw = NULL;
                this->actionFunc = func_80A6CA9C;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                break;
            case 11:
                this->actor.update = func_80A6D75C;
                this->actor.draw = func_80A6E214;
                Actor_SetScale(&this->actor, 0.2f);
                break;
            default:
                this->actor.draw = func_80A6D88C;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C9A8.s")

void func_80A6CA9C(EnFall* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x85)) {
        switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0) {
            case 3:
                if (this->unk_150 == 0.0f) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EV_MOON_EYE_FLASH);
                }
                this->unk_150 += 0.033333335f;
                if (this->unk_150 > 1.0f) {
                    this->unk_150 = 1.0f;
                }
                break;
            case 4:
                this->actor.draw = func_80A6D98C;
                break;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CB74.s")

void func_80A6CD38(EnFall* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0 && globalCtx->sceneNum == SCENE_OKUJOU) {
        func_800B9010(&this->actor, NA_SE_EV_MOON_FALL - SFX_FLAG);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CD74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6CF70.s")

void EnFall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    this->actionFunc(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D75C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DA7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6DD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E37C.s")
