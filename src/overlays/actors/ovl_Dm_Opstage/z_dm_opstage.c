/*
 * File: z_dm_opstage.c
 * Overlay: ovl_Dm_Opstage
 * Description: Lost Woods cutscene objects
 */

#include "z_dm_opstage.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmOpstage*)thisx)

void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A9FA58(DmOpstage* this, GlobalContext* globalCtx);

void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc);

#if 0
const ActorInit Dm_Opstage_InitVars = {
    ACTOR_DM_OPSTAGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO, 
    sizeof(DmOpstage), 
    (ActorFunc)DmOpstage_Init,
    (ActorFunc)DmOpstage_Destroy,
    (ActorFunc)DmOpstage_Update, 
    (ActorFunc)DmOpstage_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A9FD30[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A9FD30[];

extern UNK_TYPE D_06000978;
extern UNK_TYPE D_06001C98;
// Draw
extern Gfx D_06000970;
extern Gfx D_06002870;
extern Gfx D_06002878;
extern Gfx D_06003060;
extern Gfx D_06003068;
extern Gfx D_06003720;
extern Gfx D_06003728;
// /Draw
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_SetupAction.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Init.s")

void DmOpstage_Init(Actor *thisx, GlobalContext *globalCtx) {
    s32 phi_v0;
    DmOpstage *this = (DmOpstage *) thisx;

    Actor_ProcessInitChain(&this->dyna.actor, D_80A9FD30);
    DmOpstage_SetupAction(this, func_80A9FA58);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    //temp_v0 = this->dyna.actor.params & 0xFF; 
    phi_v0 = this->dyna.actor.params & 0xFF;
    //phi_v0 = temp_v0;
    if (phi_v0 == 0) { 
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, (CollisionHeader *) &D_06001C98);
        phi_v0 = this->dyna.actor.params & 0xFF;
    }
    if (phi_v0 > 0) { 
        this->unk1A4 = this->dyna.actor.world.pos.x;
        this->unk1A8 = this->dyna.actor.world.pos.y;
        this->unk1AC = this->dyna.actor.world.pos.z;
        this->dyna.actor.world.pos.x = 0.0f;
        this->dyna.actor.world.pos.y = 0.0f;
        this->dyna.actor.world.pos.z = 0.0f;
        //this->unk1A8 = temp_ft1;
        //this->unk1AC = temp_ft2;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Destroy.s")

void DmOpstage_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    DmOpstage *this = THIS;

    if ((this->dyna.actor.params & 0xFF) == 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/func_80A9FA58.s")
/* matches!
void func_80A9FA58(DmOpstage *this, GlobalContext *globalCtx) {
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = this->dyna.actor.params;
    if ((temp_v0 & 0xFF) == 0) {
        if (Cutscene_CheckActorAction(globalCtx, 0x73U) != 0) {
            temp_v0_2 = Cutscene_GetActorActionIndex(globalCtx, 0x73U);
            if (globalCtx->csCtx.actorActions[temp_v0_2]->action == 2) {
                this->dyna.actor.scale.x = 0.075f;
                this->dyna.actor.scale.z = 0.3f;
            } else {
                this->dyna.actor.scale.x = 0.1f;
                this->dyna.actor.scale.z = 0.1f;
            }
            Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, temp_v0_2);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, (((temp_v0 >> 8) & 0xFF) + 0x74) & 0xFFFF) != 0) {
        Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, ((((s16) this->dyna.actor.params >> 8) & 0xFF) + 0x74) & 0xFFFF));
    }
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Update.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Opstage/DmOpstage_Draw.s")

void DmOpstage_Draw(Actor *thisx, GlobalContext *globalCtx) {
    s32 temp_v1;
    s32 phi_v1;
    DmOpstage *this = (DmOpstage *) thisx;

    temp_v1 = this->dyna.actor.params & 0xFF;
    phi_v1 = temp_v1;
    if (temp_v1 > 0) {
        Matrix_Translate(this->dyna.actor.world.pos.x + this->unk1A4, this->dyna.actor.world.pos.y + this->unk1A8, this->dyna.actor.world.pos.z + this->unk1AC, MTXMODE_NEW);
        Matrix_RotateYS(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
        phi_v1 = this->dyna.actor.params & 0xFF;
    }
    switch (phi_v1) {                               /* irregular */
    case 0:
        Gfx_DrawDListOpa(globalCtx, (Gfx *) &D_06000978);
        Gfx_DrawDListXlu(globalCtx, &D_06000970);
        return;
    case 1:
        Gfx_DrawDListOpa(globalCtx, &D_06002878);
        Gfx_DrawDListXlu(globalCtx, &D_06002870);
        return;
    case 2:
        Gfx_DrawDListOpa(globalCtx, &D_06003068);
        Gfx_DrawDListXlu(globalCtx, &D_06003060);
        return;
    case 3:
        Gfx_DrawDListOpa(globalCtx, &D_06003728);
        Gfx_DrawDListXlu(globalCtx, &D_06003720);
        return;
    }
}
