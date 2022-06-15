/*
 * File: z_item_b_heart.c
 * Overlay: ovl_Item_B_Heart
 * Description: Heart Container
 */

#include "z_item_b_heart.h"
#include "objects/object_gi_hearts/object_gi_hearts.h"

#define FLAGS 0x00000000

#define THIS ((ItemBHeart*)thisx)

void ItemBHeart_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemBHeart_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemBHeart_Update(Actor* thisx, GlobalContext* globalCtx);
void ItemBHeart_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808BCF54(ItemBHeart* this, GlobalContext* globalCtx);

const ActorInit Item_B_Heart_InitVars = {
    ACTOR_ITEM_B_HEART,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_GI_HEARTS,
    sizeof(ItemBHeart),
    (ActorFunc)ItemBHeart_Init,
    (ActorFunc)ItemBHeart_Destroy,
    (ActorFunc)ItemBHeart_Update,
    (ActorFunc)ItemBHeart_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ItemBHeart_Init(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* this = THIS;

    if (Flags_GetCollectible(globalCtx, 0x1F)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.8f);

    if (this->actor.params == 0x23) {
        this->unk_168 = 0.1f;
    } else {
        this->unk_168 = 1.0f;
    }

    this->actor.world.pos.y += (20.0f * this->unk_168);
}

void ItemBHeart_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ItemBHeart_Update(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* this = THIS;

    func_808BCF54(this, globalCtx);

    if (!(this->unk_168 < 0.5f)) {
        if (Actor_HasParent(&this->actor, globalCtx)) {
            Flags_SetCollectible(globalCtx, 0x1F);
            Actor_MarkForDeath(&this->actor);
        } else {
            Actor_PickUp(&this->actor, globalCtx, GI_HEART_CONTAINER, 30.0f, 80.0f);
        }
    }
}

void func_808BCF54(ItemBHeart* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 0x400;
    Math_ApproachF(&this->unk_164, 0.4f, 0.1f, 0.01f);
    Actor_SetScale(&this->actor, this->unk_164 * this->unk_168);
}

void ItemBHeart_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* this = THIS;
    Actor* blueWarpActor;
    u8 flag = false;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    blueWarpActor = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (blueWarpActor != NULL) {
        if ((blueWarpActor->id == ACTOR_DOOR_WARP1) && (blueWarpActor->projectedPos.z > this->actor.projectedPos.z)) {
            flag = true;
            break;
        }
        blueWarpActor = blueWarpActor->next;
    }

    if (flag || thisx->world.rot.y != 0) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_gi_hearts_DL_001290);
        gSPDisplayList(POLY_XLU_DISP++, object_gi_hearts_DL_001470);
    } else {
        func_8012C28C(globalCtx->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_gi_hearts_DL_001290);
        gSPDisplayList(POLY_OPA_DISP++, object_gi_hearts_DL_001470);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
