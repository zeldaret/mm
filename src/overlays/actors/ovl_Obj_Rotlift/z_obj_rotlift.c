/*
 * File: z_obj_rotlift.c
 * Overlay: ovl_Obj_Rotlift
 * Description: Deku Moon Dungeon - Spiked Rotating Platforms
 */

#include "z_obj_rotlift.h"
#include "objects/object_rotlift/object_rotlift.h"

#define FLAGS 0x00000000

#define THIS ((ObjRotlift*)thisx)

void ObjRotlift_Init(Actor* thisx, GlobalContext* globalCtx2);
void ObjRotlift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B95E20(ObjRotlift* this);

const ActorInit Obj_Rotlift_InitVars = {
    ACTOR_OBJ_ROTLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ROTLIFT,
    sizeof(ObjRotlift),
    (ActorFunc)ObjRotlift_Init,
    (ActorFunc)ObjRotlift_Destroy,
    (ActorFunc)ObjRotlift_Update,
    (ActorFunc)ObjRotlift_Draw,
};

struct AnimatedThing D_80B96160[] = {
    {
        object_rotlift_DL_000400,
        object_rotlift_Matanimheader_001F98,
        &object_rotlift_Colheader_002190,
    },
    {
        object_rotlift_DL_002CE0,
        object_rotlift_Matanimheader_004A08,
        &object_rotlift_Colheader_004DF0,
    },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void func_80B95E20(ObjRotlift* this) {
    Actor* actor;
    Actor** actorUpdate;
    f32 rotShift;
    s32 i;
    actorUpdate = this->actorPtr;

    for (i = 0, rotShift = 300.0f; i < 2; i++, actorUpdate++) {
        actor = *actorUpdate;
        if (actor->update == NULL) {
            *actorUpdate = NULL;
        } else {
            actor->world.pos.x = (Math_SinS(this->dyna.actor.shape.rot.y) * rotShift) + this->dyna.actor.world.pos.x;
            actor->world.pos.y = this->dyna.actor.world.pos.y + (380.0f * this->dyna.actor.scale.y);
            actor->world.pos.z = (Math_CosS(this->dyna.actor.shape.rot.y) * rotShift) + this->dyna.actor.world.pos.z;
            actor->shape.rot.y = this->dyna.actor.shape.rot.y;
        }
        rotShift -= 600.0f;
    }
}

void ObjRotlift_Init(Actor* thisx, GlobalContext* globalCtx2) {
    ObjRotlift* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 params;
    s32 spawnParams;
    s32 i;
    AnimatedThing* animated;
    Actor** actor;

    params = OBJROTLIFT_GET_1(thisx);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    if (params == 0) {
        for (actor = this->actorPtr, i = 0; i < 2; i++, actor++) {
            if (!(OBJROTLIFT_GET_4000(thisx)) || (i)) {
                spawnParams = 0;
            } else {
                spawnParams = 0x100;
            }
            *actor = Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_OBJ_ETCETERA,
                                        this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                        this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                                        this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, spawnParams);
        }
        func_80B95E20(this);
    }
    DynaPolyActor_Init(&this->dyna, 3);

    animated = &D_80B96160[params];
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, animated->colHeader);
    animated->animMat = Lib_SegmentedToVirtual(animated->animMat);
}

void ObjRotlift_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjRotlift* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjRotlift_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjRotlift* this = THIS;
    s16 dirShift;
    s32 direction;

    if (OBJROTLIFT_GET_1(thisx) == 0) {
        func_80B95E20(this);
    }
    if (OBJROTLIFT_GET_PARAMS(thisx) >= 0) {
        direction = -0xC8;
    } else {
        direction = 0xC8;
    }
    dirShift = direction;
    this->dyna.actor.shape.rot.y += dirShift;
}

void ObjRotlift_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjRotlift* this = THIS;
    s32 pad;
    AnimatedThing* animated;

    animated = &D_80B96160[OBJROTLIFT_GET_1(thisx)];
    AnimatedMat_Draw(globalCtx, animated->animMat);
    Gfx_DrawDListOpa(globalCtx, animated->dList);
}
