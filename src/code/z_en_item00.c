#include <ultra64.h>
#include <global.h>

#define THIS ((EnItem00*)thisx)

void EnItem00_UpdateForNewObjectId(EnItem00* this, GlobalContext* globalCtx, f32* shadowOffset, f32* shadowScale) {
    Actor_SetObjectSegment(globalCtx, &this->actor);
    Actor_SetScale(&this->actor, 0.5f);
    this->unk154 = 0.5f;
    *shadowOffset = 0.0f;
    *shadowScale = 0.6f;
    this->actor.world.rot.x = 0x4000;
}

void EnItem00_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* this = THIS;
    s32 pad;
    f32 shadowOffset = 980.0f;
    f32 shadowScale = 6.0f;
    s32 getItemId = 0;
    s32 sp30 = (this->actor.params & 0x8000) ? 1 : 0;

    this->collectibleFlag = (this->actor.params & 0x7F00) >> 8;

    thisx->params &= 0xFF; // Has to be thisx to match

    if (Actor_GetCollectibleFlag(globalCtx, this->collectibleFlag) != 0) {
        if (this->actor.params == 6) {
            sp30 = 0;
            this->collectibleFlag = 0;
            this->actor.params = 3;
        } else {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }
    if (this->actor.params == 0x15) {
        this->actor.params = 3;
    }

    Actor_ProcessInitChain(&this->actor, enItem00InitVars);
    Collision_InitCylinder(globalCtx, &this->collider, &this->actor, &enItem00CylinderInit);

    this->unk150 = 1;

    switch (this->actor.params) {
    case 0:
    case 1:
    case 2:
        Actor_SetScale(&this->actor, 0.015f);
        this->unk154 = 0.015f;
        shadowOffset = 750.0f;
        break;
    case 17:
        this->unk150 = 0;
        Actor_SetScale(&this->actor, 0.03f);
        this->unk154 = 0.03f;
        shadowOffset = 350.0f;
        break;
    case 6:
    case 7:
        this->unk150 = 0;
        Actor_SetScale(&this->actor, 0.02f);
        this->unk154 = 0.02f;
        shadowOffset = 650.0f;
        if (this->actor.params == 7) {
            sp30 = -1;
        }
        break;
    case 3:
        this->actor.home.rot.z = randPlusMinusPoint5Scaled(65535.0f);
        shadowOffset = 430.0f;
        Actor_SetScale(&this->actor, 0.02f);
        this->unk154 = 0.02f;
        break;
    case 5:
    case 8:
    case 9:
    case 10:
        Actor_SetScale(&this->actor, 0.035f);
        this->unk154 = 0.035f;
        shadowOffset = 250.0f;
        break;
    case 4:
    case 11:
    case 12:
    case 13:
    case 15:
    case 23:
    case 25:
        Actor_SetScale(&this->actor, 0.03f);
        this->unk154 = 0.03f;
        shadowOffset = 320.0f;
        break;
    case 14:
        Actor_SetScale(&this->actor, 0.044999998f);
        this->unk154 = 0.044999998f;
        shadowOffset = 320.0f;
        break;
    case 19:
        Actor_SetScale(&this->actor, 0.044999998f);
        this->unk154 = 0.044999998f;
        shadowOffset = 750.0f;
        break;
    case 20:
        Actor_SetScale(&this->actor, 0.03f);
        this->unk154 = 0.03f;
        shadowOffset = 750.0f;
        break;
    case 18:
    case 26:
        shadowOffset = 500.0f;
        Actor_SetScale(&this->actor, 0.01f);
        this->unk154 = 0.01f;
        break;
    case 22:
        this->actor.objBankIndex = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0xB3);
        EnItem00_UpdateForNewObjectId(this, globalCtx, &shadowOffset, &shadowScale);
        break;
    case 27:
        this->actor.objBankIndex = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0xA0);
        EnItem00_UpdateForNewObjectId(this, globalCtx, &shadowOffset, &shadowScale);
        break;
    case 28:
        this->actor.objBankIndex = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0x91);
        EnItem00_UpdateForNewObjectId(this, globalCtx, &shadowOffset, &shadowScale);
        break;
    default:
        break;
    }

    this->unk14E = 0;
    Actor_SetDrawParams(&this->actor.shape, shadowOffset, func_800B3FC0, shadowScale);
    this->actor.shape.shadowAlpha = 180;
    this->actor.focus.pos = this->actor.world.pos;
    this->unk14A = 0;

    if (sp30 < 0) {
        this->actionFunc = func_800A63A8;
        this->unk152 = -1;
        return;
    }
    if (sp30 == 0) {
        this->actionFunc = func_800A640C;
        this->unk152 = -1;
        return;
    }

    this->unk152 = 15;
    this->unk14C = 35;

    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;

    switch (this->actor.params) {
    case 0:
        func_80112E80(globalCtx, 0x84);
        break;
    case 1:
        func_80112E80(globalCtx, 0x85);
        break;
    case 2:
        func_80112E80(globalCtx, 0x87);
        break;
    case 20:
        func_80112E80(globalCtx, 0x88);
        break;
    case 19:
        func_80112E80(globalCtx, 0x8A);
        break;
    case 3:
        func_80112E80(globalCtx, 0x83);
        break;
    case 18:
    case 26:
        func_80115908(globalCtx, 0x70);
        break;
    case 4:
    case 11:
        func_80112E80(globalCtx, 0x8F);
        break;
    case 5:
        func_80112E80(globalCtx, 0x93);
        break;
    case 8:
        func_80112E80(globalCtx, 0x94);
        break;
    case 9:
        func_80112E80(globalCtx, 0x95);
        break;
    case 10:
        func_80112E80(globalCtx, 0x96);
        break;
    case 14:
        func_80112E80(globalCtx, 0x7A);
        break;
    case 15:
        func_80112E80(globalCtx, 0x79);
        break;
    case 17:
        func_80112E80(globalCtx, 0x78);
        break;
    case 12:
        getItemId = 0x28;
        break;
    case 23:
        getItemId = 0x2A;
        break;
    default:
        break;
    }

    if ((getItemId != 0) && (Actor_HasParent(&this->actor, globalCtx) == 0)) {
        func_800B8A1C(&this->actor, globalCtx, getItemId, 50.0f, 20.0f);
    }

    this->actionFunc = EnItem00_Update1;
    this->actionFunc(this, globalCtx);
}

void EnItem00_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* this = THIS;

    Collision_FiniCylinder(globalCtx, &this->collider);
}

void func_800A63A8(EnItem00* this, GlobalContext* globalCtx) {
    s32 sp1C;

    sp1C = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0x96);
    if (Scene_IsObjectLoaded(&globalCtx->sceneContext, sp1C)) {
        this->actor.objBankIndex = sp1C;
        this->actionFunc = func_800A640C;
    }
}

void func_800A640C(EnItem00* this, GlobalContext* ctxt) {
    if ((this->actor.params <= 2) || ((this->actor.params == 3) && (this->unk152 < 0)) || (this->actor.params == 6) || (this->actor.params == 7)) {
        this->actor.shape.rot.y = this->actor.shape.rot.y + 960;
    } else if ((this->actor.params >= 0x16) && (this->actor.params != 0x17) && (this->actor.params < 0x19)) {
        if (this->unk152 == -1) {
            if (!Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, this->actor.world.rot.x - 0x4000, 2, 3000, 1500)) {
                this->unk152 = -2;
            }
        } else if (!Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, -0x4000 - this->actor.world.rot.x, 2, 3000, 1500)) {
            this->unk152 = -1;
        }

        Math_SmoothScaleMaxMinS(&this->actor.world.rot.x, 0, 2, 2500, 500);
    } else if ((this->actor.params == 0x1B) || (this->actor.params == 0x1C)) {
        this->unk152 = -1;
        this->actor.shape.rot.y = this->actor.shape.rot.y + 960;
    }

    if ((this->actor.params == 6) || (this->actor.params == 7)) {
        this->actor.shape.yOffset = (Math_Sins(this->actor.shape.rot.y) * 150.0f) + 850.0f;
    }

    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);

    if (this->unk14C == 0) {
        if ((this->actor.params != 0x11) && (this->actor.params != 6) && (this->actor.params != 7)) {
            this->unk14C = -1;
        }
    }

    if (this->unk152 == 0) {
        if ((this->actor.params != 0x11) && (this->actor.params != 6) && (this->actor.params != 7)) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    if ((this->actor.gravity != 0.0f) && ((this->actor.bgCheckFlags & 1) == 0)) {
        this->actionFunc = func_800A6650;
    }
}

void func_800A6650(EnItem00* this, GlobalContext* globalCtx) {
    u32 pad;
    Vec3f pos;

    if (this->actor.params < 3) {
        this->actor.shape.rot.y = this->actor.shape.rot.y + 960;
    }
    if ((globalCtx->unk18840 & 1) != 0) {
        pos.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(10.0f);
        pos.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(10.0f);
        pos.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(10.0f);
        func_800B16B8(globalCtx, &pos, &D_801ADF18, &D_801ADF24, &D_801ADF10, &D_801ADF14);
    }
    if ((this->actor.bgCheckFlags & 3) != 0) {
        if (this->actor.velocity.y > -2.0f) {
            this->actionFunc = func_800A640C;
            return;
        }

        this->actor.velocity.y = this->actor.velocity.y * -0.8f;
        this->actor.bgCheckFlags = this->actor.bgCheckFlags & 0xFFFE;
    }
}

void func_800A6780(EnItem00* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f pos;
    s32 var1;

    this->unk152++;

    if (this->actor.params == 3) {
        if (this->actor.velocity.y < 0.0f) {
            this->actor.speedXZ = 0.0f;
            this->actor.gravity = -0.4f;
            if (this->actor.velocity.y < -1.5f) {
                this->actor.velocity.y = -1.5f;
            }
            this->actor.home.rot.z += (s16)((this->actor.velocity.y + 3.0f) * 1000.0f);
            this->actor.world.pos.x += (Math_Coss(this->actor.yawTowardsPlayer) * (-3.0f * Math_Coss(this->actor.home.rot.z)));
            this->actor.world.pos.z += (Math_Sins(this->actor.yawTowardsPlayer) * (-3.0f * Math_Coss(this->actor.home.rot.z)));
        }
    }

    if (this->actor.params < 3) {
        this->actor.shape.rot.y += 960;
    } else if ((this->actor.params >= 0x16) && (this->actor.params != 0x17) && (this->actor.params != 0x19)) {
        this->actor.world.rot.x -= 700;
        this->actor.shape.rot.y += 400;
        this->actor.shape.rot.x = this->actor.world.rot.x - 0x4000;
    }

    if (this->actor.velocity.y <= 2.0f) {
        var1 = (u16)this->actor.shape.rot.z + 10000;
        if (var1 < 65535) {
            this->actor.shape.rot.z += 10000;
        } else {
            this->actor.shape.rot.z = -1;
        }
    }

    if ((globalCtx->unk18840 & 1) == 0) {
        pos.x = this->actor.world.pos.x + ((randZeroOne() - 0.5f) * 10.0f);
        pos.y = this->actor.world.pos.y + ((randZeroOne() - 0.5f) * 10.0f);
        pos.z = this->actor.world.pos.z + ((randZeroOne() - 0.5f) * 10.0f);
        func_800B16B8(globalCtx, &pos, &D_801ADF18, &D_801ADF24, &D_801ADF10, &D_801ADF14);
    }

    if (this->actor.bgCheckFlags & 0x0003) {
        this->actionFunc = func_800A640C;
        this->actor.shape.rot.z = 0;
        this->actor.speedXZ = 0.0f;
    }
}

void EnItem00_Update1(EnItem00* this, GlobalContext* globalCtx) {
    ActorPlayer* sp2C = globalCtx->actorCtx.actorList[2].first;
    // TODO PLAYER macro

    if (this->unk14A != 0) {
        if (Actor_HasParent(&this->actor, globalCtx) == 0) {
            func_800B8A1C(&this->actor, globalCtx, this->unk14A, 50.0f, 80.0f);
            this->unk152 = this->unk152 + 1;
        } else {
            this->unk14A = 0;
        }
    }

    if (this->unk152 == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.world.pos = sp2C->base.world.pos;

    if (this->actor.params < 3) {
        this->actor.shape.rot.y = this->actor.shape.rot.y + 960;
    } else if (this->actor.params == 3) {
        this->actor.shape.rot.y = 0;
    }

    this->actor.world.pos.y += (40.0f + (Math_Sins(this->unk152 * 15000) * (this->unk152 * 0.3f)));

    // TODO LINK_IS_ADULT macro
    if (gSaveContext.perm.linkAge == 0) {
        this->actor.world.pos.y = this->actor.world.pos.y + 20.0f;
    }
}

/*
void EnItem00_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* this = THIS;
    s32 pad;
    ActorPlayer* player = globalCtx->actorCtx.actorList[2].first;
    s32 sp38 = player->unkA74 & 0x1000;
    s32 getItemId = 0;
    s32 pad2;

    if (this->unk152 > 0) {
        this->unk152--;
    }

    if ((this->unk152 > 0) && (this->unk152 < 0x29) && (this->unk14C <= 0)) {
        this->unk14E = this->unk152;
    }

    this->actionFunc(this, globalCtx);

    Math_SmoothScaleMaxMinF(&this->actor.scale.x, this->unk154, 0.1f, this->unk154 * 0.1f, 0.0f);
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;

    if (this->actor.gravity != 0.0f) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        func_800B78B8(globalCtx, &this->actor, 20.0f, 15.0f, 15.0f, 0x1D);

        if (this->actor.floorHeight <= -32000.0f) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }

    Collision_CylinderMoveToActor(&this->actor, &this->collider);
    Collision_AddAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);

    if ((this->actor.params == 0x16) || (this->actor.params == 0x1B) || (this->actor.params == 0x1C)) {
        this->actor.shape.yOffset = fabsf(Math_Coss(this->actor.shape.rot.x) * 37.0f);
    }

    if (this->unk14C > 0) {
        return;
    }

    if (!((sp38 != 0) && (this->actor.xzDistToPlayer <= 60.0f) && (this->actor.yDistToPlayer >= -100.0f) && (this->actor.yDistToPlayer <= 100.0f)) &&
        !((sp38 == 0) && (this->actor.xzDistToPlayer <= 30.0f) && (this->actor.yDistToPlayer >= -50.0f) && (this->actor.yDistToPlayer <= 50.0f))) {
        if (!Actor_HasParent(&this->actor, globalCtx)) {
            return;
        }
    }

    if (globalCtx->unk17000 != 0) {
        return;
    }

    switch (this->actor.params) {
    case 0:
        this->unk1A4 = 1;
        func_80112E80(globalCtx, 0x84);
        break;
    case 1:
        this->unk1A4 = 1;
        func_80112E80(globalCtx, 0x85);
        break;
    case 2:
        this->unk1A4 = 1;
        func_80112E80(globalCtx, 0x87);
        break;
    case 20:
        this->unk1A4 = 1;
        func_80112E80(globalCtx, 0x88);
        break;
    case 19:
        this->unk1A4 = 1;
        func_80112E80(globalCtx, 0x8A);
        break;
    case 13:
        getItemId = 0x19;
        break;
    case 12:
        getItemId = 0x28;
        break;
    case 23:
        getItemId = 0x2A;
        break;
    case 3:
        func_80112E80(globalCtx, 0x83);
        break;
    case 18:
    case 26:
        func_80115908(globalCtx, 0x70);
        break;
    case 4:
    case 11:
        func_80112E80(globalCtx, 0x8F);
        break;
    case 5:
        func_80112E80(globalCtx, 0x93);
        break;
    case 8:
        func_80112E80(globalCtx, 0x94);
        break;
    case 9:
        func_80112E80(globalCtx, 0x95);
        break;
    case 10:
        func_80112E80(globalCtx, 0x96);
        break;
    case 17:
        getItemId = 0x3C;
        break;
    case 6:
        getItemId = 0xC;
        break;
    case 7:
        getItemId = 0xD;
        break;
    case 14:
        func_80112E80(globalCtx, 0x7A);
        break;
    case 15:
        func_80112E80(globalCtx, 0x79);
        break;
    case 22:
        getItemId = 0x32;
        break;
    case 27:
        getItemId = 0x3E;
        break;
    case 28:
        getItemId = 0x3F;
    default:
        break;
    }

    if (getItemId != 0) {
        if (!Actor_HasParent(&this->actor, globalCtx)) {
            func_800B8A1C(&this->actor, globalCtx, getItemId, 50.0f, 20.0f);
        }
    }

    switch (this->actor.params) {
    case 6:
    case 7:
    case 17:
    case 22:
    case 27:
    case 28:
        if (Actor_HasParent(&this->actor, globalCtx)) {
            Actor_SetCollectibleFlag(globalCtx, this->collectibleFlag);
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    if ((this->actor.params < 3) || (this->actor.params == 0x13)) {
        play_sound(0x4803);
    } else if (getItemId != 0) {
        if (Actor_HasParent(&this->actor, globalCtx)) {
            Actor_SetCollectibleFlag(globalCtx, this->collectibleFlag);
            Actor_MarkForDeath(&this->actor);
        }
        return;
    } else {
        play_sound(0x4824);
    }

    Actor_SetCollectibleFlag(globalCtx, this->collectibleFlag);

    this->unk152 = 15;
    this->unk14C = 35;
    this->actor.shape.rot.z = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;

    Actor_SetScale(&this->actor, this->unk154);

    this->unk14A = 0;
    this->actionFunc = EnItem00_Update1;
}
*/

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_en_item00/EnItem00_Update.asm")

void EnItem00_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnItem00* this = THIS;

    if (!(this->unk14E & this->unk150)) {
        switch (this->actor.params) {
        case 0:
        case 1:
        case 2:
        case 19:
        case 20:
            EnItem00_DrawRupee(this, globalCtx);
            break;
        case 6:
            EnItem00_DrawHeartPiece(this, globalCtx);
            break;
        case 7:
            EnItem00_DrawHeartContainer(this, globalCtx);
            break;
        case 3:
            if (this->unk152 < 0) {
                if (this->unk152 == -1) {
                    s8 bankIndex = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0x90);
                    if (Scene_IsObjectLoaded(&globalCtx->sceneContext, bankIndex) != 0) {
                        this->actor.objBankIndex = bankIndex;
                        Actor_SetObjectSegment(globalCtx, &this->actor);
                        this->unk152 = -2;
                    }
                } else {
                    SysMatrix_InsertScale(16.0f, 16.0f, 16.0f, 1);
                    func_800EE320(globalCtx, 8);
                }
                break;
            }
        case 4:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
        case 23:
        case 25:
            EnItem00_DrawSprite(this, globalCtx);
            break;
        case 22:
            func_800EE320(globalCtx, 0x27);
            break;
        case 27:
            func_800EE320(globalCtx, 0x1B);
            break;
        case 28:
            func_800EE320(globalCtx, 0xA);
        case 16:
        case 18:
        case 21:
        case 24:
        case 26:
            break;
        }
    }
}

void EnItem00_DrawRupee(EnItem00* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 iconNb;

    // OPEN_DISP macro
    {
        GraphicsContext* gfx = globalCtx->state.gfxCtx;
        s32 pad;

        func_8012C28C(globalCtx->state.gfxCtx);
        func_800B8050(&this->actor, globalCtx, 0);

        if (this->actor.params <= 2) {
            iconNb = this->actor.params;
        } else {
            iconNb = this->actor.params - 0x10;
        }

        gSPMatrix(gfx->polyOpa.p++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);

        gSPSegment(gfx->polyOpa.p++, 0x08, Lib_PtrSegToVirt(D_801ADF30[iconNb]));

        gSPDisplayList(gfx->polyOpa.p++, &D_040622C0); // TODO symbol
    }
}

void EnItem00_DrawSprite(EnItem00* this, GlobalContext* globalCtx) {
    s32 iconNb = this->actor.params - 3;

    // OPEN_DISP macro
    {
        GraphicsContext* gfx = globalCtx->state.gfxCtx;
        s32 pad;

        gfx->polyOpa.p = func_801660B8(globalCtx, gfx->polyOpa.p);

        if (this->actor.params == 0x17) {
            iconNb = 6;
        } else if (this->actor.params == 0x19) {
            iconNb = 1;
        } else if (this->actor.params >= 8) {
            iconNb -= 3;
            if (this->actor.params < 0xA) {
                iconNb++;
            }
        }

        gfx->polyOpa.p = func_8012C724(gfx->polyOpa.p);

        gSPSegment(gfx->polyOpa.p++, 0x08, Lib_PtrSegToVirt(D_801ADF44[iconNb]));

        gSPMatrix(gfx->polyOpa.p++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);

        gSPDisplayList(gfx->polyOpa.p++, D_0405F6F0);

    }
}

extern Gfx D_06001290[];
extern Gfx D_06001470[];

void EnItem00_DrawHeartContainer(EnItem00* actor, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;

    if (Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 0x96) == actor->actor.objBankIndex) {
        // OPEN_DISP macro
        {
            GraphicsContext* gfx = globalCtx->state.gfxCtx;
            s32 pad;

            func_8012C2DC(globalCtx->state.gfxCtx);
            SysMatrix_InsertScale(20.0f, 20.0f, 20.0f, 1);

            gSPMatrix(gfx->polyXlu.p++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);

            gSPDisplayList(gfx->polyXlu.p++, D_06001290);
            gSPDisplayList(gfx->polyXlu.p++, D_06001470);
        }
    }
}

void EnItem00_DrawHeartPiece(EnItem00* this, GlobalContext* globalCtx) {
    s32 pad;

    // OPEN_DISP macro
    {
        GraphicsContext* gfx = globalCtx->state.gfxCtx;
        s32 pad;

        func_8012C2DC(globalCtx->state.gfxCtx);
        func_800B8118(&this->actor, globalCtx, 0);

        gSPMatrix(gfx->polyXlu.p++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);

        gSPDisplayList(gfx->polyXlu.p++, D_0405AAB0);
    }
}

s16 func_800A7650(s16 dropId) {
    s16 maxLife;

    if ((((dropId == 4) || (dropId == 0x19) || (dropId == 0xB)) && (gSaveContext.perm.inv.items[D_801C207E] == 0xFF)) ||
        (((dropId == 5) || (dropId == 8) || (dropId == 9) || (dropId == 0xA)) && (gSaveContext.perm.inv.items[D_801C2079] == 0xFF)) ||
        (((dropId == 0xE) || (dropId == 0xF)) && (gSaveContext.perm.unk24.unk14 == 0))) {
        return -1;
    }

    ;

    if (dropId == 3) {
        maxLife = gSaveContext.perm.unk24.maxLife;
        if (maxLife == gSaveContext.perm.unk24.currentLife) {
            return 0;
        }
    }

    return dropId;
}

/*
EnItem00* func_800A7730(GlobalContext* globalCtx, Vec3f* spawnPos, u32 params) {
    s32 pad;
    EnItem00* spawnedActor = NULL;
    s32 pad2;
    s32 param10000;
    s16 param8000;
    s16 param7F00;
    s32 param20000;
    s32 paramFF;
    s32 i;

    param10000 = params & 0x10000;
    param8000 = params & 0x8000;
    param7F00 = params & 0x7F00;
    param20000 = params & 0x20000;
    paramFF = params & 0xFF;

    params &= 0x7FFF;

    if (paramFF == 0x15) {
        for (i = 0; i != 3; i++) {
            spawnedActor = func_800A7730(globalCtx, spawnPos, param7F00 | 3 | param8000);
        }
    } else if (paramFF == 0x1D) {
        param7F00 >>= 8;
        if (!Actor_GetCollectibleFlag(globalCtx, param7F00)) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x23B, spawnPos->x, spawnPos->y, spawnPos->z, 0, 0, 0, param7F00);
        }
    } else if (((paramFF == 0x12) || ((params & 0xFF) == 0x1A)) && (param10000 == 0)) {
        if ((params & 0xFF) == 0x12) {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x10, spawnPos->x, spawnPos->y + 40.0f, spawnPos->z, 0, 0, 0, ((((param7F00 >> 8) & 0x7F) << 9) & 0xFE00) | 0x102);
            if (!Actor_GetCollectibleFlag(globalCtx, (param7F00 >> 8) & 0x7F)) {
                func_800F0568(globalCtx, spawnPos, 0x28, 0x28E7);
            }
        } else {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x1B0, spawnPos->x, spawnPos->y + 40.0f, spawnPos->z, 0, 0, 0, ((((param7F00 >> 8) & 0x7F) & 0x7F) << 9) | 7);
            if (param20000 == 0) {
                if (Actor_GetCollectibleFlag(globalCtx, (param7F00 >> 8) & 0x7F) == 0) {
                    func_800F0568(globalCtx, spawnPos, 0x28, 0x28E7);
                }
            }
        }
    } else {
        if (param8000 == 0) {
            params = func_800A7650(params & 0xFF);
        }
        if (params != -1) {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, spawnPos->x, spawnPos->y, spawnPos->z, 0, 0, 0, params | param8000 | param7F00);
            if ((spawnedActor != NULL) && (param8000 == 0)) {
                if (param10000 == 0) {
                    spawnedActor->actor.velocity.y = 8.0f;
                } else {
                    spawnedActor->actor.velocity.y = -2.0f;
                }
                spawnedActor->actor.speedXZ = 2.0f;
                spawnedActor->actor.gravity = -0.9f;
                spawnedActor->actor.world.rot.y = randPlusMinusPoint5Scaled(65536.0f);
                Actor_SetScale(spawnedActor, 0.0f);
                spawnedActor->actionFunc = func_800A6780;
                spawnedActor->unk152 = 0xDC;
                if ((spawnedActor->actor.params != 0x11) && (spawnedActor->actor.params != 6) && (spawnedActor->actor.params != 7)) {
                    spawnedActor->actor.room = -1;
                }
                spawnedActor->actor.flags |= 0x0010;
            }
        }
    }

    return spawnedActor;
}
*/

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_en_item00/func_800A7730.asm")

/*
Actor* func_800A7AD4(GlobalContext* globalCtx, Vec3f* spawnPos, u32 params) {
    Actor* spawnedActor = NULL;
    u32 pad;
    u32 temp_t1;
    s16 sp42;
    s16 temp_t0;

    temp_t1 = params & 0x10000;
    sp42 = params & 0x8000;
    temp_t0 = params & 0x7F00;
    params &= 0xFF;

    if (params == 0x15) {
        return NULL;
    }

    if (((params == 0x12) || (params == 0x1A)) && (temp_t1 == 0)) {
        if (params == 0x12) {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x10, spawnPos->x, spawnPos->y + 40.0f, spawnPos->z, 0, 0, 0, ((((temp_t0 >> 8) & 0x7F) << 9) & 0xFE00) | 0x102);
        } else {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x1B0, spawnPos->x, spawnPos->y + 40.0f, spawnPos->z, 0, 0, 0, ((((temp_t0 >> 8) & 0x7F) & 0x7F) << 9) | 7);
        }
        if (Actor_GetCollectibleFlag(globalCtx, (temp_t0 >> 8) & 0x7F) == 0) {
            func_800F0568(globalCtx, spawnPos, 0x28, 0x28E7);
        }
    } else {
        params = func_800A7650(params);
        if (params != -1) {
            spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, spawnPos->x, spawnPos->y, spawnPos->z, 0, 0, 0, params | sp42 | temp_t0);
            if (spawnedActor != NULL) {
                if (sp42 == 0) {
                    spawnedActor->velocity.y = 0.0f;
                    spawnedActor->speedXZ = 0.0f;
                    if (temp_t1 != 0) {
                        spawnedActor->gravity = 0.0f;
                    } else {
                        spawnedActor->gravity = -0.9f;
                    }
                    spawnedActor->world.rot.y = randPlusMinusPoint5Scaled(65536.0f);
                    spawnedActor->flags |= 0x10;
                }
            }
        }
    }

    return spawnedActor;
}
*/

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_en_item00/func_800A7AD4.asm")

/*
void func_800A7D28(GlobalContext* globalCtx, Actor* fromActor, Vec3f* spawnPos, s16 params) {
    EnItem00* spawnedActor;
    u8 dropId;
    s32 dropQuantity;
    s16 dropTableIndex;
    s16 param8000;

    dropTableIndex = randZeroOne() * 16.0f;
    param8000 = params & 0x8000;
    params &= 0x1F0;

    if (params < 0x101) {
        dropId = D_801ADF74[params + dropTableIndex];
        dropQuantity = D_801AE084[params + dropTableIndex];

        if (dropId == 0x10) {
            dropId = 0xF;
            dropQuantity = 1;
            if (gSaveContext.perm.unk20 != 1) {
                if (gSaveContext.perm.unk20 != 2) {
                    if (gSaveContext.perm.unk20 != 4) {
                        dropId = 0;
                    } else {
                        dropId = 5;
                    }
                } else {
                    dropId = 3;
                }
            }
        }

        if (fromActor != NULL) {
            if (fromActor->dropFlag != 0) {
                if ((fromActor->dropFlag & 1) != 0) {
                    dropId = 8;
                    params = 0x10;
                } else if ((fromActor->dropFlag & 2) != 0) {
                    dropId = 3;
                    params = 0x10;
                } else  if ((fromActor->dropFlag & 0x20) != 0) {
                    dropId = 0x14;
                }
                dropQuantity = 1;
            }
        }

        if (dropId == 0x12) {
            if (gSaveContext.perm.unk24.currentLife < 0x11) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x10, spawnPos->x, spawnPos->y + 40.0f, spawnPos->z, 0, 0, 0, 2);
                func_800F0568(globalCtx, spawnPos, 0x28, 0x28E7);
                return;
            }

            if (gSaveContext.perm.unk24.currentLife < 0x31) {
                params = 0x10;
                dropId = 3;
                dropQuantity = 3;
            } else if (gSaveContext.perm.unk24.currentLife < 0x51) {
                params = 0x10;
                dropId = 3;
                dropQuantity = 1;
            } else  if ((gSaveContext.perm.unk24.unk14 != 0) && (gSaveContext.perm.unk24.currentMagic == 0)) {
                params = 0xD0;
                dropId = 0xE;
                dropQuantity = 1;
            } else if ((gSaveContext.perm.unk24.unk14 != 0) && ((gSaveContext.perm.unk24.unk14 >> 1) >= gSaveContext.perm.unk24.currentMagic)) {
                params = 0xD0;
                dropId = 0xE;
                dropQuantity = 1;
            } else if (gSaveContext.perm.inv.quantities[D_801C2078[1]] < 6) {
                params = 0xA0;
                dropId = 8;
                dropQuantity = 1;
            } else if (gSaveContext.perm.inv.quantities[D_801C2078[6]] < 6) {
                params = 0xB0;
                dropId = 4;
                dropQuantity = 1;
            } else if (gSaveContext.perm.unk24.unk16 < 0xB) {
                params = 0xA0;
                dropId = 2;
                dropQuantity = 1;
            }
        }

        if (dropId != 0xFF) {
            while (dropQuantity > 0) {
                if (param8000 == 0) {
                    dropId = func_800A7650(dropId);
                    if (dropId != 0xFF) {
                        spawnedActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, spawnPos->x, spawnPos->y, spawnPos->z, 0, 0, 0, dropId);
                        if ((spawnedActor != 0) && (dropId != 0xFF)) {
                            spawnedActor->actor.velocity.y = 8.0f;
                            spawnedActor->actor.speedXZ = 2.0f;
                            spawnedActor->actor.gravity = -0.9f;
                            spawnedActor->actor.world.rot.y = randZeroOne() * 40000.0f;
                            Actor_SetScale(spawnedActor, 0.0f);
                            spawnedActor->actionFunc = func_800A6780;
                            spawnedActor->actor.flags = spawnedActor->actor.flags | 0x10;
                            if ((spawnedActor->actor.params != 0x11) && (spawnedActor->actor.params != 6) && (spawnedActor->actor.params != 7)) {
                                spawnedActor->actor.room = -1;
                            }
                            spawnedActor->unk152 = 220;
                        }
                    }
                } else {
                    func_800A7730(globalCtx, spawnPos, params | 0x8000);
                }

                dropQuantity--;
            }
        }
    }
}
*/

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_en_item00/func_800A7D28.asm")

s32 func_800A8150(s32 index) {
    if ((index < 0) || (index >= 32)) {
        return -1;
    }

    return D_801AE194[index];
}

s32 func_800A817C(s32 index) {
    if ((index < 0) || (index >= 32)) {
        return 0;
    }

    return D_801AE214[index];
}

s32 func_800A81A4(GlobalContext* globalCtx, s32 a1, s32 a2) {
    return (func_800A8150(a1) == 0x1A) && (Actor_GetCollectibleFlag(globalCtx, a2) == 0);
}
