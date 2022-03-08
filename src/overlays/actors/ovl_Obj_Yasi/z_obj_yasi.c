/*
 * File: z_obj_yasi.c
 * Overlay: ovl_Obj_Yasi
 * Description: Palm Tree
 */

#include "z_obj_yasi.h"
#include "objects/object_obj_yasi/object_obj_yasi.h"

#define FLAGS 0x00000000

#define THIS ((ObjYasi*)thisx)

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

extern s32 D_06000360;
extern CollisionHeader D_06001428;

static InitChainEntry sInitChain[] = 
{
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ObjYasi_Init(Actor *thisx, GlobalContext *globalCtx) 
{
    ObjYasi* this = THIS;
    Actor_ProcessInitChain(this, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_06001428);

    this->dyna.actor.home.rot.y = 0;

    if ((this->dyna.actor.params & 1) != 0) 
    {
        this->dyna.actor.scale.x = 0.2f;
        this->dyna.actor.scale.z = 0.2f;
    }
}

void ObjYasi_Destroy(Actor *thisx, GlobalContext *globalCtx) 
{
    ObjYasi* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjYasi_Update(Actor *thisx, GlobalContext *globalCtx) 
{
    ObjYasi* this = THIS;
    f32 sp20;
    f32 temp_f0;
    s16 temp_v0;
    ObjYasi *phi_a3;

    
    if (this->dyna.actor.home.rot.z != 0) 
    {
        if (this->dyna.actor.params < 0) 
        {
            
            if (Rand_ZeroOne() < 0.5f) 
            {
                Item_DropCollectible(globalCtx, &this->dyna.actor.world.pos, 0xCU);
            }
        }
        
        this->dyna.actor.home.rot.x = 0x190;
        this->dyna.actor.home.rot.z = 0;
        this->dyna.actor.home.rot.y = globalCtx->actorCtx.actorLists[2].first->shape.rot.y;
        phi_a3 = this;
    }
    temp_v0 = phi_a3->dyna.actor.shape.rot.x;
    temp_f0 = (f32) temp_v0;
    phi_a3->dyna.actor.home.rot.x -= (s16) (s32) (temp_f0 * 0.1f);
    phi_a3->dyna.actor.shape.rot.x += (temp_v0 - (s32) (temp_f0 * 0.08f));
}

void ObjYasi_Draw(Actor *thisx, GlobalContext *globalCtx) 
{
    ObjYasi* this = THIS;
    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0);

    if (this->dyna.actor.shape.rot.x != 0) 
    {
        Matrix_RotateY(this->dyna.actor.home.rot.y, 1);
        Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, 1);
        Matrix_RotateY((s16) (this->dyna.actor.shape.rot.y - this->dyna.actor.home.rot.y), 1);
    } 
    else 
    {
        Matrix_RotateY(this->dyna.actor.shape.rot.y, 1);
    }

    Matrix_Scale(0.1f, 0.1f, 0.1f, 1);
    Gfx_DrawDListOpa(globalCtx, object_obj_yasi_DL_000360);
}