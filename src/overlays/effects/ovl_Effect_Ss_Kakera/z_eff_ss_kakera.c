/*
 * File: z_eff_ss_kakera.c
 * Overlay: ovl_Effect_Ss_Kakera
 * Description:
 */

#include "z_eff_ss_kakera.h"

#define PARAMS ((EffectSsKakeraInitParams*)initParamsx)

u32 EffectSsKakera_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsKakera_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsKakera_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

void func_8097E130(EffectSs* this, GlobalContext* globalCtx);
f32 func_8097E368(f32, s32);
f32 func_8097E384(f32, s32);
f32 func_8097E3C0(f32, s32);
f32 func_8097E400(f32, s32);

const EffectSsInit Effect_Ss_Kakera_InitVars = {
    EFFECT_SS_KAKERA,
    EffectSsKakera_Init,
};
KakeraColorStruct D_8097EAD8[] = { { 0, { 255, 255, 255 } }, { 0, { 235, 170, 130 } }, { 1, { 210, 190, 170 } } };
f32 D_8097EAE4[] = { 1.0f, 100.0f, 40.0f, 5.0f, 100.0f, 40.0f, 5.0f, 100.0f, 40.0f, 5.0f };
f32 D_8097EB0C[] = { 0.05f, 1.0f };
f32 D_8097EB14[] = { 4.0f, 0.1f, 0.3f, 0.9f, -0.1f, -0.3f, -0.9f };
f32 D_8097EB30[] = { 0.1f, 1.0f, 6.0f };
f32 (*D_8097EB3C[])(f32, s32) = { func_8097E368, func_8097E384, func_8097E384, func_8097E384, func_8097E3C0,
                                  func_8097E3C0, func_8097E3C0, func_8097E400, func_8097E400, func_8097E400 };
f32 D_8097EB64[] = { 10.0f, 20.0f, 40.0f };

u32 EffectSsKakera_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsKakeraInitParams* params = PARAMS;

    this->pos = params->pos;
    this->velocity = params->velocity;
    this->life = params->life;
    this->priority = 101;
    if (params->dList != NULL) {
        this->gfx = params->dList;
        switch (params->objId) {
            case GAMEPLAY_KEEP:
            case GAMEPLAY_FIELD_KEEP:
            case GAMEPLAY_DANGEON_KEEP:
                this->regs[10] = KAKERA_OBJECT_DEFAULT;
                break;
            default:
                this->regs[10] = params->objId;
                func_8097E130(this, globalCtx);
                break;
        }
    } else {
        __assert("../z_eff_kakera.c", 193);
    }
    this->draw = EffectSsKakera_Draw;
    this->update = EffectSsKakera_Update;
    this->vec = params->unk_18;
    this->regs[0] = params->unk_2C;
    this->regs[1] = params->gravity;
    this->regs[2] = Rand_ZeroOne() * 32768.0f;
    this->regs[3] = Rand_ZeroOne() * 32768.0f;
    this->regs[4] = params->unk_26;
    this->regs[5] = params->unk_28;
    this->regs[6] = params->unk_2A;
    this->regs[7] = params->scale;
    this->regs[8] = params->unk_30;
    this->regs[9] = params->unk_32;
    this->regs[12] = params->colorIdx;
    return 1;
}

f32 func_8097DE30(f32 center, f32 range) {
    return (2.0f * (Rand_ZeroOne() * range) - range) + center;
}

void EffectSsKakera_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s16 pad;
    f32 scale = this->regs[7] / 256.0f;
    s32 colorIndex = this->regs[12];

    OPEN_DISPS(gfxCtx);
    if (this->regs[10] != KAKERA_OBJECT_DEFAULT) {
        if ((((this->regs[4] >> 7) & 1) << 7) == 0x80) {
            gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[this->regs[11]].segment);
        } else {
            gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->regs[11]].segment);
        }
    }

    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->regs[3], MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->regs[2], MTXMODE_APPLY);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

    if ((((this->regs[4] >> 7) & 1) << 7) == 0x80) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(globalCtx->state.gfxCtx);
        if (colorIndex >= 0) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, D_8097EAD8[colorIndex].lod, D_8097EAD8[colorIndex].color.r,
                            D_8097EAD8[colorIndex].color.g, D_8097EAD8[colorIndex].color.b, 255);
        }
        gSPDisplayList(POLY_XLU_DISP++, this->gfx);
    } else {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C28C(globalCtx->state.gfxCtx);
        if (colorIndex >= 0) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, D_8097EAD8[colorIndex].lod, D_8097EAD8[colorIndex].color.r,
                            D_8097EAD8[colorIndex].color.g, D_8097EAD8[colorIndex].color.b, 255);
        }
        gSPDisplayList(POLY_OPA_DISP++, this->gfx);
    }
    CLOSE_DISPS(gfxCtx);
}

void func_8097E130(EffectSs* this, GlobalContext* globalCtx) {
    this->regs[11] = Object_GetIndex(&globalCtx->objectCtx, this->regs[10]);
    if ((this->regs[11] < 0) || (!Object_IsLoaded(&globalCtx->objectCtx, this->regs[11]))) {
        this->life = 0;
        this->draw = NULL;
    }
}

void func_8097E19C(EffectSs* this) {
    f32 range;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f18;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2_2;

    temp_f18 = this->regs[5] / 1024.0f;
    temp_f20 = this->regs[6] / 1024.0f;
    range = (this->regs[9] / 1024.0f) * 4.0f;
    temp_f2 = this->velocity.x - func_8097DE30(0.0f, range);
    temp_f16 = this->velocity.y - func_8097DE30(0.0f, range);
    temp_f12 = this->velocity.z - func_8097DE30(0.0f, range);
    temp_f0 = temp_f2 * temp_f18;
    temp_f2_2 = SQ(temp_f2) * temp_f20;
    if (temp_f2 > 0.0f) {
        this->velocity.x -= (temp_f0 + temp_f2_2);
    } else {
        this->velocity.x -= (temp_f0 - temp_f2_2);
    }
    temp_f0 = temp_f16 * temp_f18;
    temp_f2_2 = SQ(temp_f16) * temp_f20;
    if (temp_f16 > 0.0f) {
        this->velocity.y -= (temp_f0 + temp_f2_2);
    } else {
        this->velocity.y -= (temp_f0 - temp_f2_2);
    }
    if (temp_f12 > 0.0f) {
        this->velocity.z -= (temp_f0 + temp_f2_2);
    } else {
        this->velocity.z -= (temp_f0 - temp_f2_2);
    }
}

void func_8097E34C(EffectSs* this) {
    this->accel.x = this->accel.y = this->accel.z = 0.0f;
}

f32 func_8097E368(f32 arg0, s32 arg1) {
    return 1.0f;
}

f32 func_8097E384(f32 arg0, s32 index) {
    if (D_8097EAE4[index] < arg0) {
        return D_8097EAE4[index] / arg0;
    } else {
        return 1.0f;
    }
}

f32 func_8097E3C0(f32 arg0, s32 index) {
    f32 square = SQ(arg0);

    if (D_8097EAE4[index] < square) {
        return D_8097EAE4[index] / square;
    } else {
        return 1.0f;
    }
}

f32 func_8097E400(f32 arg0, s32 index) {
    return func_8097E3C0(arg0, index);
}

s32 func_8097E420(EffectSs* this, Vec3f* diff, f32 distance) {
    f32 phi_f0;
    s32 index = this->regs[0] & 3;

    if (index != 0) {
        if (distance > 1.0f) {
            phi_f0 = 1.0f / distance;
        } else {
            phi_f0 = 1.0f;
        }
        this->accel.x += D_8097EB0C[index - 1] * diff->z * phi_f0;
        this->accel.z -= D_8097EB0C[index - 1] * diff->x * phi_f0;
    }
    return 1;
}

s32 func_8097E4B0(EffectSs* this, Vec3f* diff, f32 distance) {
    s32 index = (this->regs[0] >> 2) & 7;

    if (index != 0) {
        this->accel.y += D_8097EB14[index];
    }
    return 1;
}

s32 func_8097E4F0(EffectSs* this, Vec3f* diff, f32 distance) {
    f32 phi_f0;
    s32 index = (this->regs[0] >> 5) & 3;

    if (index != 0) {
        if (distance > 1.0f) {
            phi_f0 = 1.0f / distance;
        } else {
            phi_f0 = 1.0f;
        }
        this->accel.x -= diff->x * D_8097EB30[index - 1] * phi_f0;
        this->accel.z -= diff->z * D_8097EB30[index - 1] * phi_f0;
    }
    return 1;
}

s32 func_8097E584(EffectSs* this, Vec3f* diff, f32 distance) {
    f32 center;
    f32 rand;
    s32 index;

    index = (this->regs[0] >> 7) & 0xF;
    center = D_8097EB3C[index](distance, index);
    rand = func_8097DE30(center, (this->regs[9] * center) / 1024.0f);
    this->accel.x *= rand;
    this->accel.y *= rand;
    this->accel.z *= rand;
    this->accel.x += rand * 0.01f;
    this->accel.y += rand * 0.01f;
    this->accel.z += rand * 0.01f;
    return 1;
}

s32 func_8097E660(EffectSs* this, Vec3f* diff, f32 distance) {
    this->accel.y += this->regs[1] / 256.0f;
    return 1;
}

s32 func_8097E698(EffectSs* this) {
    Vec3f diff;
    f32 distance;

    func_8097E34C(this);
    diff.x = this->pos.x - this->vec.x;
    diff.y = this->pos.y - this->vec.y;
    diff.z = this->pos.z - this->vec.z;
    distance = sqrtf(SQXYZ(diff));
    if (distance > 1000.0f) {
        return 0;
    }
    if (this->regs[0] != 0) {
        if (func_8097E420(this, &diff, distance) == 0) {
            return 0;
        }
        if (func_8097E4B0(this, &diff, distance) == 0) {
            return 0;
        }
        if (func_8097E4F0(this, &diff, distance) == 0) {
            return 0;
        }
        if (func_8097E584(this, &diff, distance) == 0) {
            return 0;
        }
    }
    if (func_8097E660(this, &diff, distance) == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_8097E7E0(EffectSs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->regs[8] == 0) {
        if ((((this->regs[4] >> 4) & 1) * 0x10) == 0x10) {
            if (this->pos.y <= (player->actor.floorHeight - ((this->regs[4] >> 2) & 3))) {
                this->regs[9] = 0;
                this->regs[0] = 0;
                this->regs[4] &= ~0x60;
                this->accel.x = this->accel.y = this->accel.z = 0.0f;
                this->velocity.x = this->velocity.y = this->velocity.z = 0.0f;
                this->regs[5] = this->regs[9];
                this->regs[1] = this->regs[9];
            }
        } else {
            if (this->pos.y <= ((player->actor.floorHeight - ((this->regs[4] >> 2) & 3)) - 600.0f)) {
                this->life = 0;
            }
        }
    } else {
        switch (this->regs[4] & 3) {
            case 0:
                this->regs[8] = 0;
                break;
            case 1:
                if ((this->velocity.y < 0.0f) &&
                    (func_800C5A20(&globalCtx->colCtx, &this->pos, D_8097EB64[(this->regs[4] >> 2) & 3]))) {
                    this->velocity.x *= func_8097DE30(0.9f, 0.2f);
                    this->velocity.y *= -0.8f;
                    this->velocity.z *= func_8097DE30(0.9f, 0.2f);
                    if (this->regs[8] > 0) {
                        this->regs[8] -= 1;
                    }
                }
                break;
            case 2:
                if (func_800C5A20(&globalCtx->colCtx, &this->pos, D_8097EB64[(this->regs[4] >> 2) & 3])) {
                    this->regs[8] = 0;
                }
                break;
        }
    }
}

void EffectSsKakera_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    switch (((this->regs[4] >> 5) & 3) << 5) {
        case 0x20:
            this->regs[2] += 0x47B;
            this->regs[3] += 0x139;
            break;
        case 0x40:
            this->regs[2] += 0x1A7C;
            this->regs[3] += 0x47B;
            break;
        case 0x60:
            this->regs[2] += 0x3F27;
            this->regs[3] += 0xCA1;
            break;
    }
    func_8097E19C(this);
    if (func_8097E698(this) == 0) {
        this->life = 0;
    }
    func_8097E7E0(this, globalCtx);
    if (this->regs[10] != KAKERA_OBJECT_DEFAULT) {
        func_8097E130(this, globalCtx);
    }
}
