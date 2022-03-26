/*
 * File: z_obj_yasi.c
 * Overlay: ovl_Obj_Yasi
 * Description: Palm Tree
 */

#include "z_obj_yasi.h"
#include "objects/object_obj_yasi/object_obj_yasi.h"

#define FLAGS 0x00000000

#define THIS ((ObjYasi*)thisx)

#define CAN_DROP_NUT(thisx) (thisx->params < 0)

void ObjYasi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Yasi_InitVars = {
    ACTOR_OBJ_YASI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJ_YASI,
    sizeof(ObjYasi),
    (ActorFunc)ObjYasi_Init,
    (ActorFunc)ObjYasi_Destroy,
    (ActorFunc)ObjYasi_Update,
    (ActorFunc)ObjYasi_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ObjYasi_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_obj_yasi_Colheader_001428);

    this->dyna.actor.home.rot.y = 0;

    if (OBJYASI_IS_WIDE(thisx)) {
        this->dyna.actor.scale.x = 0.2f;
        this->dyna.actor.scale.z = 0.2f;
    }
}

void ObjYasi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjYasi_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;
    s16 temp;
    Vec3f dropPos;

    if (this->dyna.actor.home.rot.z != 0) {
        if (CAN_DROP_NUT(thisx)) {
            if (Rand_ZeroOne() < 0.5f) {
                dropPos.x = this->dyna.actor.world.pos.x;
                dropPos.y = this->dyna.actor.world.pos.y + 280.0f;
                dropPos.z = this->dyna.actor.world.pos.z;
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_NUTS_1);
            }
        }
        this->dyna.actor.home.rot.y = GET_PLAYER(globalCtx)->actor.shape.rot.y;
        this->dyna.actor.home.rot.x = 400;
        this->dyna.actor.home.rot.z = 0;
    }
    temp = (s16)(this->dyna.actor.shape.rot.x * 0.1f);
    this->dyna.actor.home.rot.x -= temp;
    this->dyna.actor.shape.rot.x +=
        BINANG_SUB(this->dyna.actor.home.rot.x, (s16)(this->dyna.actor.shape.rot.x * 0.08f));
}

void ObjYasi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;

    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                             MTXMODE_NEW);

    if (this->dyna.actor.shape.rot.x != 0) {
        Matrix_RotateY(this->dyna.actor.home.rot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_RotateY(BINANG_SUB(this->dyna.actor.shape.rot.y, this->dyna.actor.home.rot.y), MTXMODE_APPLY);
    } else {
        Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    }

    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Gfx_DrawDListOpa(globalCtx, object_obj_yasi_DL_000360);
}
