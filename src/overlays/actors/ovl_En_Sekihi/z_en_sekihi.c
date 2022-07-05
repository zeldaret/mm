/*
 * File: z_en_sekihi.c
 * Overlay: ovl_En_Sekihi
 * Description: Mikau's Grave & Song Pedestals
 */

#include "z_en_sekihi.h"
#include "objects/object_sekihil/object_sekihil.h"
#include "objects/object_sekihig/object_sekihig.h"
#include "objects/object_sekihin/object_sekihin.h"
#include "objects/object_sekihiz/object_sekihiz.h"
#include "objects/object_zog/object_zog.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnSekihi*)thisx)

void EnSekihi_Init(Actor* thisx, PlayState* play);
void EnSekihi_Destroy(Actor* thisx, PlayState* play);
void EnSekihi_Update(Actor* thisx, PlayState* play);

void func_80A44DE8(EnSekihi* this, PlayState* play);
void func_80A44F40(EnSekihi* this, PlayState* play);
void func_80A450B0(EnSekihi* this, PlayState* play);
void func_80A45130(EnSekihi* this, PlayState* play);
void func_80A45164(EnSekihi* this, GraphicsContext** gfxCtx);
#if 0
const ActorInit En_Sekihi_InitVars = {
    ACTOR_EN_SEKIHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSekihi),
    (ActorFunc)EnSekihi_Init,
    (ActorFunc)EnSekihi_Destroy,
    (ActorFunc)EnSekihi_Update,
    (ActorFunc)NULL,
};

static s16 D_80A45270[6] = { 0x173, 0x174, 0x175, 0x176, 0x206, 0 };
static s32 D_80A4527C[5] = { 0x060005E0, 0x060005C8, 0x060005C8, 0x06000518, 0x06006AA0 };
static s32 D_80A45290[5] = { 0x060004C0, 0x060004A8, 0x060004A8, 0x06000510, 0x060069F0 };
static u16 D_80A452A4[6] = { 0, 0, 0, 0, 0x1018, 0 };
s32 D_80A452B0 = 0x060033F8;

#endif
extern s16 D_80A45270[];
extern s32 D_80A4527C[];
extern s32 D_80A45290[];
extern u16 D_80A452A4[];
extern CollisionHeader D_80A452B0[];

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Init.s")
void EnSekihi_Init(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;
    s32 params = this->dyna.actor.params & 0xF;
    s32* temp_t0;
    s32 objectIndex;

    if (((params < 0) || (params >= 5)) || ((temp_t0 = &D_80A4527C[params], (*temp_t0) == 0))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    if ((params == 4) && (((u32)(gSaveContext.save.skullTokenCount & 0xFFFF)) >= 0x1EU)) {
        gSaveContext.save.weekEventReg[13] |= 0x20;
    }
    objectIndex = Object_GetIndex(&play->objectCtx, D_80A45270[params]);
    if (objectIndex >= 0) {
        this->unk164 = objectIndex;
    }
    this->actionFunc = func_80A44DE8;
    this->unk15C = *temp_t0;
    this->unk160 = D_80A45290[params];
    this->dyna.actor.textId = D_80A452A4[params];
    this->dyna.actor.focus.pos.y = this->dyna.actor.world.pos.y + 60.0f;
    Actor_SetScale(&this->dyna.actor, 0.1f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Destroy.s")

void EnSekihi_Destroy(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A44DE8.s")

void func_80A44DE8(EnSekihi* this, PlayState* play) {
    s32 params;
    //CollisionHeader sp2C;
    // CollisionHeader **sp28;
    CollisionHeader** temp_v1;
    // CollisionHeader *temp_a0;
    // CollisionHeader **phi_v1;
    CollisionHeader* D_80A452B0[] = { &object_sekihil_Colheader_0033F8, &object_sekihig_Colheader_0033D8,
                                             &object_sekihin_Colheader_0033D8, &object_sekihiz_Colheader_001010,
                                             &object_zog_Colheader_008670 };
    


    params = this->dyna.actor.params & 0xF;

    if (Object_IsLoaded(&play->objectCtx, (s32)this->unk164) != 0) {

        this->dyna.actor.draw = (void (*)(Actor*, PlayState*))func_80A45164;
        this->dyna.actor.objBankIndex = this->unk164;

        if (params == 4) {
            this->actionFunc = func_80A450B0;
        } else {
            this->actionFunc = func_80A45130;
        }
        Actor_SetObjectDependency(play, &this->dyna.actor);
        DynaPolyActor_Init(&this->dyna, 0);
        temp_v1 = &D_80A452B0[params];

        if (*temp_v1 != NULL) {
            CollisionHeader_GetVirtual(*temp_v1, NULL);
        }

        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, NULL);

        if ((temp_v1 == D_80A452B0) && (gSaveContext.save.inventory.items[gItemSlots[0x34]] != 0x34)) {
            Actor_MarkForDeath(&this->dyna.actor);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A44F40.s")

void func_80A44F40(EnSekihi* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if ((Message_ShouldAdvance(play) != 0) && (play->msgCtx.currentTextId == 0x1019)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x101AU);
                        return;
                    case 1:
                        func_8019F208();
                        func_80151938(play, 0x101BU);
                        return;
                    case 2:
                        func_8019F230();
                        func_801477B4(play);
                        this->actionFunc = func_80A450B0;
                        return;
                }
            } else {
                return;
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1018:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                    case 0x101A:
                    case 0x101B:
                        func_801477B4(play);
                        this->actionFunc = func_80A450B0;
                        break;
                }
            }
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A450B0.s")

void func_80A450B0(EnSekihi* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->dyna.actor, &play->state) != 0) {
        this->actionFunc = func_80A44F40;
    } else if ((this->dyna.actor.xzDistToPlayer < 100.0f) &&
               (Player_IsFacingActor(&this->dyna.actor, 0x2600, play) != 0)) {
        func_800B8614(&this->dyna.actor, play, 120.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A45130.s")

void func_80A45130(EnSekihi* this, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Update.s")

void EnSekihi_Update(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;

    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A45164.s")

void func_80A45164(EnSekihi* this, GraphicsContext** gfxCtx) {
    s32 pad;

    OPEN_DISPS(*gfxCtx);

    if (this->unk160 != 0) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(*gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(*gfxCtx);
        gSPDisplayList(POLY_XLU_DISP++, this->unk160);
    }
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(*gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(*gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->unk15C);

    CLOSE_DISPS(*gfxCtx);
}
