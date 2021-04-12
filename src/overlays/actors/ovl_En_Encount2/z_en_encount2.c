#include "z_en_encount2.h"

#define FLAGS 0x00000010

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
//void EnEncount2_Init(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

//actionfunc
void func_808E1714(EnEncount2* this, GlobalContext* globalCtx);
void func_808E17C4(EnEncount2* this, GlobalContext* globalCtx);
void func_808E18A8(EnEncount2* this, GlobalContext* globalCtx);

void func_808E16FC(EnEncount2 *this);
void func_808E1A24(EnEncount2* this, Vec3f* vec, s16 arg2);
void func_808E1B4C(EnEncount2 *this, GlobalContext *globalCtx);
void func_808E1C9C(EnEncount2 *this, GlobalContext *globalCtx);

const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw
};

static ColliderJntSphElementInit D_808E1EF0[1] = {
//static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

/*
//glabel D_808E1F14 collider init
static ColliderJntSphInit D_808E1F14 = {
//static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_808E1EF0,
    //1, sJntSphElementsInit,
};
*/

DamageTable D_808E1F24[] = {
    0xF0, 0xF0, 0x00, 0xF0, 0xE1, 0xE1, 0x00, 0xE1, 0xF0, 0xF0, 0xF0, 0xE1, 0xE1, 0xE1, 0xF0, 0xF0, 
    0xE1, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0xE1, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
};

UNK_TYPE1 unkpadding[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

///*
//issue: collider init is confused
void EnEncount2_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    s8 pad[4];
    BgMeshHeader* bgMeshHeader = NULL;

    BcCheck3_BgActorInit(&this->actor, 0);
    BgCheck_RelocateMeshHeader(&D_06002420, &bgMeshHeader);
    this->unk144 = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->actor, bgMeshHeader);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    this->actor.colChkInfo.mass = 0xFF;
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_808E1F14, &this->colElement);
    //Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, &this->colElement);

    this->actor.targetMode = 6;
    this->actor.colChkInfo.health = 1;
    //this->unk168 = D_808E1F50;
    this->unk168 = 0.1;
    this->unk164 = (s16) (this->actor.params & 0x7F);

    if (this->unk164 == 0x7F) {
        this->unk164 = -1;
    }

    if ((this->unk164 >= 0) && (Actor_GetSwitchFlag(globalCtx, this->unk164) != 0)) {
        Actor_MarkForDeath(this);
        return;
    }

    this->collider.elements->dim.modelSphere.radius = 0x39;
    this->collider.elements->dim.scale = 1.0f;
    this->collider.elements->dim.modelSphere.center.x = 0;
    this->collider.elements->dim.modelSphere.center.y = -4;
    this->collider.elements->dim.modelSphere.center.z = 0;

    this->actor.colChkInfo.damageTable = &D_808E1F24;
    func_808E16FC(this);
} // */
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/EnEncount2_Init.asm")

void EnEncount2_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->unk144);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

// init extension func
void func_808E16FC(EnEncount2 *this) {
    this->unk162 = 0;
    this->actionFunc = &func_808E1714;
}

//actionfunc
void func_808E1714(EnEncount2 *this, GlobalContext *globalCtx) {
    // is this rodata? its not in the asm file as late rodata... extern for now
    this->unk16C += D_808E1F54;
    this->actor.velocity.y = Math_SinS((s16) (s32) this->unk16C);
    Math_SmoothScaleMaxF(&this->unk168, 0.1f, 0.3f, 0.01f);
    if (((this->collider.base.acFlags & 2) != 0) && (this->actor.colChkInfo.damageEffect == 0xE)) {
        this->actor.colChkInfo.health = 0;
        this->unk162 = 1;
        this->actionFunc = func_808E17C4;
    }
}

//actionfunc
void func_808E17C4(EnEncount2 *this, GlobalContext *globalCtx) {
    s32 i;
    Vec3f curPos;

    Math_Vec3f_Copy(&curPos, &this->actor.world.pos);
    curPos.y += 60.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xA2, curPos.x, curPos.y, curPos.z, 0xFF, 0xFF, 0xC8, 1);

    for(i = 0; i != 100; i++){
        func_808E1A24(this, &curPos, 10);
    }

    Audio_PlayActorSound2(this, 0x2949);
    this->unk160 = 0x1E; // timer?
    this->actionFunc = func_808E18A8;
}

//actionfunc
void func_808E18A8(EnEncount2 *this, GlobalContext *globalCtx) {
    if (this->unk160 == 0) {
        if (this->unk164 >= 0) {
            Actor_SetSwitchFlag(globalCtx, this->unk164);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void EnEncount2_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    s8 pad[4];

    if (this->unk160 != 0) {
        this->unk160--;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetHeight(&this->actor, 30.0f);
    Actor_SetScale(&this->actor, this->unk168);
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_808E1B4C(this, globalCtx);

    if (this->unk162 == 0) {
        Collider_UpdateSpheresElement(&this->collider, 0, &this->actor);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

void EnEncount2_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    if (this->unk162 != 1) {
        func_800BDFC0(globalCtx, &D_06000A00);
        func_800BDFC0(globalCtx, &D_06000D78);
    }
    func_808E1C9C(&this->actor, globalCtx);
}

//arg2 is always 10??
// init all particles
void func_808E1A24(EnEncount2 *this, Vec3f *vec, s16 arg2) {
    s16 i;
    unkEnE2Struct *sPtr = &this->unkStructs;

    for (i = 0; i < 200; ++i) { //loop_1:
        if (sPtr->unk0 == 0) {
            sPtr->unk0 = 1;
            sPtr->unk4 = *vec;
            sPtr->unk16 = arg2;
            sPtr->unk14 = 0xFF;

            sPtr->unk24.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->unk24.y = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->unk24.z = (Rand_ZeroOne() - 0.5f) * 10.0f;

            sPtr->unk18.x = Rand_ZeroOne() - 0.5f;
            sPtr->unk18.y = Rand_ZeroOne() - 0.5f;
            sPtr->unk18.z = Rand_ZeroOne() - 0.5f;

            sPtr->unk30 = (Rand_ZeroFloat(1.0f) * 0.5f) + 2.0f;
            return;
        }
        sPtr++;
    }
}

// update extension
// updates all effect structs
void func_808E1B4C(EnEncount2 *this, GlobalContext *globalCtx) {
    s32 i;
    unkEnE2Struct *sPtr = &this->unkStructs;

    for(i = 0 ; i < 200; i += 2) {
        if (sPtr->unk0 != 0) {
            sPtr->unk4.x += sPtr->unk18.x;
            sPtr->unk4.y += sPtr->unk18.y;
            sPtr->unk4.z += sPtr->unk18.z;
            sPtr->unk18.x += sPtr->unk24.x;
            sPtr->unk18.y += sPtr->unk24.y;
            sPtr->unk18.z += sPtr->unk24.z;
            if (sPtr->unk16 != 0) {
                sPtr->unk16--;
            } else {
                sPtr->unk14 -= 10;
                if (sPtr->unk14 < 10) {
                    sPtr->unk0 = 0;
                }
            }
        }
        sPtr++;

        if (sPtr->unk0 != 0) {
            sPtr->unk4.x += sPtr->unk18.x;
            sPtr->unk4.y += sPtr->unk18.y;
            sPtr->unk4.z += sPtr->unk18.z;
            sPtr->unk18.x += sPtr->unk24.x;
            sPtr->unk18.y += sPtr->unk24.y;
            sPtr->unk18.z += sPtr->unk24.z;
            if (sPtr->unk16 != 0) {
                sPtr->unk16--;
            } else {
                sPtr->unk14 -= 10;
                if (sPtr->unk14 < 10) {
                    sPtr->unk0 = 0;
                }
            }
        }
        sPtr++;
    }
}

//xlu draw func extension
void func_808E1C9C(EnEncount2* this, GlobalContext* globalCtx) {
    //GraphicsContext *tempGfxC;
    unkEnE2Struct *sPtr;
    //MtxF *temp_s6;
    f32 tempFramesFloat;
    //u32 tempFrames;
    s16 i;
    f32 tmpD_808E1F58;// = D_808E1F58;
    //f32 phi_f6;
    //s16 phi_s4;

    OPEN_DISPS(globalCtx->state.gfxCtx);


    //tempGfxC = globalCtx->state.gfxCtx;
    //func_8012C28C(tempGfxC);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    tmpD_808E1F58 = D_808E1F58; //unk value
    sPtr = this->unkStructs;

    for (i = 0; i < 200; ++i) { //loop_1:
        if (sPtr->unk0 != 0) {
            //temp_s6 = &globalCtx->mf_187FC;
            //temp_f12 = sPtr->unk30;

            // bunch wrong right here
            SysMatrix_InsertTranslation(sPtr->unk4.x, sPtr->unk4.y, sPtr->unk4.z, 0);
            Matrix_Scale(sPtr->unk30, sPtr->unk30, sPtr->unk30, 1);

    
            globalCtx->state.gfxCtx->polyXlu.p = Gfx_CallSetupDL(globalCtx->state.gfxCtx->polyXlu.p, 0x14);

            //temp_v0 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0 + 8;
            //temp_v0->words.w0 = 0xDB060020;
            //temp_v0->words.w1 = Lib_PtrSegToVirt((void *)0x4079B10);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_PtrSegToVirt(0x4079B10));

            //temp_v0_2 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_2 + 8;
            //temp_v0_2->words.w1 = 0x407AB10;
            //temp_v0_2->words.w0 = 0xDE000000;
            gSPDisplayList(POLY_XLU_DISP++, 0x407AB10);

            //temp_v0_3 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_3 + 8;
            //temp_v0_3->words.w1 = 0;
            //temp_v0_3->words.w0 = 0xE7000000;
            gDPPipeSync(POLY_XLU_DISP++); // maybe not

            //temp_v0_4 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_4 + 8;
            //temp_v0_4->words.w1 = -1;
            //temp_v0_4->words.w0 = 0xFA000000;
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);

            //temp_v0_5 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_5 + 8;
            //temp_v0_5->words.w0 = 0xFB000000;
            //temp_v0_5->words.w1 = (sPtr->unk14 & 0xFF) | 0xFAB4FF00;
            gDPSetEnvColor(POLY_XLU_DISP++, 0xFA, 0xB4, 0xFF, (sPtr->unk14 & 0xFF));

            SysMatrix_InsertMatrix((z_Matrix *) &globalCtx->mf_187FC, 1);
            //tempFrames = globalCtx->state.frames;
            //tempFramesFloat = (f32) tempFrames;
            tempFramesFloat = globalCtx->state.frames;
            if (globalCtx->state.frames < 0) {
                tempFramesFloat += 4294967296.0f;
            }
            SysMatrix_InsertZRotation_f(tempFramesFloat * 20.0f * tmpD_808E1F58, 1);
            //SysMatrix_InsertZRotation_f(tempFramesFloat * 20.0f * D_808E1F58, 1);

            //temp_v0_6 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_6 + 8;
            //temp_v0_6->words.w0 = 0xDA380003;
            //temp_v0_6->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            //temp_v0_7 = tempGfxC->polyXlu.p;
            //tempGfxC->polyXlu.p = temp_v0_7 + 8;
            //temp_v0_7->words.w1 = 0x407AB58;
            //temp_v0_7->words.w0 = 0xDE000000;
            gSPDisplayList(POLY_XLU_DISP++, 0x407AB508);

        }
        //i = phi_s4 + 1;
        sPtr += 1;
        //phi_s4 = i;
        //if ((s32) i < 0xC8) {
            //goto loop_1;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1C9C.asm")
