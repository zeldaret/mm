#include "z_obj_boyo.h"

#define FLAGS 0x00000010

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoyo_Destroy(Actor* thisx, GlobalContext* globalCtx2);
void ObjBoyo_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoyo_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Boyo_InitVars = {
    ACTOR_OBJ_BOYO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOYO,
    sizeof(ObjBoyo),
    (ActorFunc)ObjBoyo_Init,
    (ActorFunc)ObjBoyo_Destroy,
    (ActorFunc)ObjBoyo_Update,
    (ActorFunc)ObjBoyo_Draw
};

u32 D_809A6170[] = {
    0x0A000D39, 0x20010000, 0x00000000, 0x00000000, 0x00000000, 0x01CBFFBE,
    0x00000000, 0x00010100, 0x003C008C, 0x00000000, 0x00000000,
};

u32 sInitChain[] = {
    0xB0FC0FA0, 0xB100012C, 0xB104012C, 0x48580064, 0x00000000,
};

u32 D_809A61B0[] = {
    0x809A5DC0,
};

u32 D_809A61B4[] = {
    0x021D0000, 0x809A5DE0, 0x00090000, 0x809A5E14, 0x00000000, 0x00000000, 0x00000000,
};

extern Gfx D_06000300[];
extern AnimatedTexture D_06000E88;

void ObjBoyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoyo* this = THIS;

    Actor_ProcessInitChain(&this->actor, &sInitChain);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_809A6170);
    Collider_UpdateCylinder(this, &this->collider);
    this->actor.colChkInfo.mass = 0xFF;
    this->unk_190 = Lib_SegmentedToVirtual(&D_06000E88);
}

void ObjBoyo_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjBoyo* this = THIS;
    
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boyo_0x809A5D10/func_809A5DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boyo_0x809A5D10/func_809A5DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boyo_0x809A5D10/func_809A5E14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boyo_0x809A5D10/func_809A5E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boyo_0x809A5D10/ObjBoyo_Update.asm")

void ObjBoyo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoyo* this = THIS;
    
    SceneProc_DrawAllSceneAnimatedTextures(globalCtx, this->unk_190);
    func_800BDFC0(globalCtx, D_06000300);
}
