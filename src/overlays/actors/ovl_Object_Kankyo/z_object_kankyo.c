/*
 * File: z_object_kankyo.c
 * Overlay: ovl_Object_Kankyo
 * Description: Snow, rain in Skull Kid backstory cutscene, and bubbles deep in Pinnacle Rock
 */

#include "z_object_kankyo.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((ObjectKankyo*)thisx)

void ObjectKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjectKankyo_SetupAction(ObjectKankyo* this, ObjectKankyoActionFunc actionFunc);
void func_808DC18C(ObjectKankyo* this, GlobalContext* globalCtx);
void func_808DCB7C(ObjectKankyo* this, GlobalContext* globalCtx);
void func_808DCBF8(ObjectKankyo* this, GlobalContext* globalCtx);
void func_808DCDB4(ObjectKankyo* this, GlobalContext* globalCtx);
void func_808DD3C8(Actor* thisx, GlobalContext* globalCtx2);
void func_808DD970(Actor* thisx, GlobalContext* globalCtx2);
void func_808DDE9C(Actor* thisx, GlobalContext* globalCtx2);

static f32 D_808DE5B0;

const ActorInit Object_Kankyo_InitVars = {
    ACTOR_OBJECT_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjectKankyo),
    (ActorFunc)ObjectKankyo_Init,
    (ActorFunc)ObjectKankyo_Destroy,
    (ActorFunc)ObjectKankyo_Update,
    (ActorFunc)ObjectKankyo_Draw,
};

static u16 D_808DE340 = 0;

void ObjectKankyo_SetupAction(ObjectKankyo* this, ObjectKankyoActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_808DBE8C(ObjectKankyo* this) {
    ObjectKankyo_SetupAction(this, func_808DC18C);
}

void func_808DBEB0(ObjectKankyo* this, GlobalContext* globalCtx) {
    s32 i;

    D_808DE5B0 = 0.0f;
    this->unk_144 = Rand_ZeroOne() * 360.0f;
    this->unk_148 = Rand_ZeroOne() * 360.0f;
    if (globalCtx->envCtx.unk_F2[2] == 128) {
        D_808DE5B0 = 1.0f;
        this->unk_114E = 1;

        for (i = 0; i < globalCtx->envCtx.unk_F2[2]; i++) {
            this->unk_14C[i].unk_10 = Rand_ZeroOne() * -200.0f;
        }
    } else {
        this->unk_114E = 0;
    }
    ObjectKankyo_SetupAction(this, func_808DCB7C);
}

void func_808DBFB0(ObjectKankyo* this, GlobalContext* globalCtx) {
    D_808DE5B0 = 0.0f;
    this->unk_114E = 0;
    this->unk_144 = Rand_ZeroOne() * 360.0f;
    this->unk_148 = Rand_ZeroOne() * 360.0f;
    this->unk_114C = D_808DE340;
    D_808DE340++;
    ObjectKankyo_SetupAction(this, func_808DCBF8);
}

void func_808DC038(ObjectKankyo* this, GlobalContext* globalCtx) {
    s16 i;

    this->unk_144 = Rand_ZeroOne() * 360.0f;
    this->unk_148 = Rand_ZeroOne() * 360.0f;
    this->unk_114C = 0;

    for (i = 0; i < ARRAY_COUNT(this->unk_14C); i++) {
        this->unk_14C[i].unk_1C = 0;
    }

    ObjectKankyo_SetupAction(this, func_808DCDB4);
}

void ObjectKankyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjectKankyo* this = THIS;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_14C); i++) {
        this->unk_14C[i].unk_1C = 0;
    }

    this->actor.room = -1;
    switch (this->actor.params) {
        case 0:
            func_808DBE8C(this);
            break;

        case 2:
            globalCtx->envCtx.unk_F2[2] = 0x80;
            func_808DBFB0(this, globalCtx);
            break;

        case 1:
        case 3:
            func_808DBEB0(this, globalCtx);
            break;

        case 4:
            func_808DC038(this, globalCtx);
            break;
    }
}

void ObjectKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjectKankyo* this = THIS;

    Actor_MarkForDeath(&this->actor);
}

void func_808DC18C(ObjectKankyo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    s32 pad3;
    f32 magnitude;
    f32 y;
    f32 z;
    f32 temp_f18;
    Vec3f sp30;
    f32 x;
    f32 sp1C;

    x = globalCtx->view.at.x - globalCtx->view.eye.x;
    y = globalCtx->view.at.y - globalCtx->view.eye.y;
    z = globalCtx->view.at.z - globalCtx->view.eye.z;
    magnitude = sqrtf(SQ(x) + SQ(y) + SQ(z));

    temp_f18 = x / magnitude;
    x = z / magnitude;
    sp1C = (y / magnitude) * 120.0f;

    this->unk_14C[0].unk_00 = globalCtx->view.eye.x + (temp_f18 * 50.0f);
    this->unk_14C[0].unk_04 = globalCtx->view.eye.y + sp1C;
    this->unk_14C[0].unk_08 = globalCtx->view.eye.z + (x * 50.0f);
    this->unk_14C[1].unk_00 = globalCtx->view.eye.x + (temp_f18 * 220.0f);
    this->unk_14C[1].unk_08 = globalCtx->view.eye.z + (x * 220.0f);
    this->unk_114C = 0;
    this->unk_144 = 100.0f;

    if ((this->unk_14C[0].unk_00 < -252.0f) && (this->unk_14C[0].unk_00 > -500.0f)) {
        if ((this->unk_14C[0].unk_08 > 3820.0f) && (this->unk_14C[0].unk_08 < 4150.0f)) {
            this->unk_114C = 1;
            this->unk_144 = 400.0f;
            if (x < 0.0f) {
                this->unk_14C[0].unk_00 = -350.0f;
                this->unk_14C[0].unk_04 = globalCtx->view.eye.y + sp1C;
                this->unk_14C[0].unk_08 = 3680.0f;
                this->unk_14C[1].unk_00 = -350.0f;
                this->unk_14C[1].unk_08 = 3680.0f;
            } else {
                this->unk_14C[0].unk_00 = -350.0f;
                this->unk_14C[0].unk_04 = globalCtx->view.eye.y + sp1C;
                this->unk_14C[0].unk_08 = 4280.0f;
                this->unk_14C[1].unk_00 = -350.0f;
                this->unk_14C[1].unk_08 = 4280.0f;
            }
        }
    }

    magnitude = globalCtx->envCtx.windSpeed / 60.0f;
    magnitude = CLAMP(magnitude, 0.0f, 1.0f);

    sp30.x = globalCtx->envCtx.windDir.x * magnitude;
    sp30.y = globalCtx->envCtx.windDir.y + 100.0f;
    sp30.z = globalCtx->envCtx.windDir.z * magnitude;
    this->unk_14C[2].unk_00 = 0x4000 - Math_Vec3f_Pitch(&gZeroVec3f, &sp30);
    this->unk_14C[2].unk_04 = Math_Vec3f_Yaw(&gZeroVec3f, &sp30) + 0x8000;
}

void func_808DC454(ObjectKankyo* this, GlobalContext* globalCtx) {
    s16 i;
    u32 tempI;
    f32 phi_f20;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 temp_f0_4;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f28;
    f32 x = globalCtx->view.at.x - globalCtx->view.eye.x;
    f32 y = globalCtx->view.at.y - globalCtx->view.eye.y;
    f32 z = globalCtx->view.at.z - globalCtx->view.eye.z;
    f32 magnitude = sqrtf(SQ(x) + SQ(y) + SQ(z));
    f32 temp_120 = 120.0f;
    f32 temp_f30;
    Vec3f sp88;
    s32 pad;

    spD0 = x / magnitude;
    spCC = y / magnitude;
    spC8 = z / magnitude;

    for (i = 0; i < globalCtx->envCtx.unk_F2[2]; i++) {
        switch (this->unk_14C[i].unk_1C) {
            case 0:
                this->unk_14C[i].unk_00 = globalCtx->view.eye.x + (spD0 * 120.0f);
                this->unk_14C[i].unk_04 = globalCtx->view.eye.y + (spCC * 120.0f);
                this->unk_14C[i].unk_08 = globalCtx->view.eye.z + (spC8 * 120.0f);
                this->unk_14C[i].unk_0C = (Rand_ZeroOne() - 0.5f) * (2.0f * temp_120);

                temp_f22 = (Camera_GetCamDirPitch(GET_ACTIVE_CAM(globalCtx)) * 0.004f) + 60.0f;
                if (temp_f22 < 20.0f) {
                    temp_f22 = 20.0f;
                }

                if (this->unk_114E == 0) {
                    this->unk_14C[i].unk_10 = temp_f22;
                } else {
                    this->unk_14C[i].unk_10 += temp_f22;
                    tempI = i;
                    if (globalCtx->envCtx.unk_F2[2] == (tempI + 1)) {
                        this->unk_114E = 0;
                    }
                }

                this->unk_14C[i].unk_14 = (Rand_ZeroOne() - 0.5f) * (2.0f * temp_120);
                if (globalCtx->envCtx.unk_F2[4] == 0) {
                    this->unk_14C[i].unk_18 = (Rand_ZeroOne() * 3.0f) + 1.0f;
                } else {
                    this->unk_14C[i].unk_18 = (Rand_ZeroOne() * 3.0f) + 8.0f;
                }
                this->unk_14C[i].unk_1C++;
                break;

            case 1:
                temp_f24 = globalCtx->view.eye.x + (spD0 * 120.0f);
                temp_f28 = globalCtx->view.eye.y + (spCC * 120.0f);
                temp_f30 = globalCtx->view.eye.z + (spC8 * 120.0f);

                magnitude = sqrtf((f32)SQ(globalCtx->envCtx.windDir.x) + SQ(globalCtx->envCtx.windDir.y) +
                                  SQ(globalCtx->envCtx.windDir.z));
                if (magnitude == 0.0f) {
                    magnitude = 0.001f;
                }
                spC4 = -globalCtx->envCtx.windDir.x / magnitude;
                spC0 = -globalCtx->envCtx.windDir.y / magnitude;
                spBC = -globalCtx->envCtx.windDir.z / magnitude;

                if (i == 0) {
                    this->unk_144 += 0.049999997f * Rand_ZeroOne();
                    this->unk_148 += 0.049999997f * Rand_ZeroOne();
                }

                phi_f20 = globalCtx->envCtx.windSpeed / 120.0f;
                phi_f20 = CLAMP(phi_f20, 0.0f, 1.0f);

                this->unk_14C[i].unk_0C += __sinf((this->unk_144 + (i * 100.0f)) * 0.01f) + (spC4 * 10.0f * phi_f20);
                this->unk_14C[i].unk_14 += __cosf((this->unk_148 + (i * 100.0f)) * 0.01f) + (spBC * 10.0f * phi_f20);
                this->unk_14C[i].unk_10 -=
                    this->unk_14C[i].unk_18 - (spC0 * 3.0f * (globalCtx->envCtx.windSpeed / 100.0f));

                temp_f22 = (-Camera_GetCamDirPitch(GET_ACTIVE_CAM(globalCtx)) * 0.012f) + 40.0f;
                if (temp_f22 < -40.0f) {
                    temp_f22 = -40.0f;
                }

                if (((this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C) - temp_f24) > temp_120) {
                    this->unk_14C[i].unk_00 = temp_f24 - temp_120;
                }

                if (((this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C) - temp_f24) < -temp_120) {
                    this->unk_14C[i].unk_00 = temp_f24 + temp_120;
                }

                sp88.x = this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C;
                sp88.y = this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10;
                sp88.z = this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14;

                phi_f20 = Math_Vec3f_DistXZ(&sp88, &globalCtx->view.eye) / 200.0f;
                phi_f20 = CLAMP(phi_f20, 0.0f, 1.0f);
                temp_f0_4 = 100.0f + phi_f20 + 60.0f;

                if (temp_f0_4 < (this->unk_14C[i].unk_04 + (this->unk_14C[i].unk_10) - temp_f28)) {
                    this->unk_14C[i].unk_04 = temp_f28 - temp_f0_4;
                }

                if (((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) - temp_f28) < -temp_f0_4) {
                    this->unk_14C[i].unk_04 = temp_f28 + temp_f0_4;
                }

                if (((this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14) - temp_f30) > temp_120) {
                    this->unk_14C[i].unk_08 = temp_f30 - temp_120;
                }

                if (((this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14) - temp_f30) < -temp_120) {
                    this->unk_14C[i].unk_08 = temp_f30 + temp_120;
                }

                if ((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) <
                    ((globalCtx->view.eye.y - temp_f22) - 40.0f)) {
                    this->unk_14C[i].unk_1C = 0;
                }
                break;
        }
    }
}

void func_808DCB7C(ObjectKankyo* this, GlobalContext* globalCtx) {
    if (globalCtx->envCtx.unk_F2[2] < globalCtx->envCtx.unk_F2[3]) {
        if ((globalCtx->state.frames % 16) == 0) {
            globalCtx->envCtx.unk_F2[2] += 2;
        }
    } else if (globalCtx->envCtx.unk_F2[3] < globalCtx->envCtx.unk_F2[2]) {
        if ((globalCtx->state.frames % 16) == 0) {
            globalCtx->envCtx.unk_F2[2] -= 2;
        }
    }
    func_808DC454(this, globalCtx);
}

void func_808DCBF8(ObjectKankyo* this, GlobalContext* globalCtx) {
    f32 temp_f0;

    if ((globalCtx->envCtx.unk_F2[2] > 0) && (this->unk_114C == 0)) {
        if ((globalCtx->state.frames % 16) == 0) {
            globalCtx->envCtx.unk_F2[2] -= 9;
            if ((s8)globalCtx->envCtx.unk_F2[2] < 0) {
                globalCtx->envCtx.unk_F2[2] = 0;
            }
        }
    }

    temp_f0 = (f32)globalCtx->envCtx.unk_F2[2] / 128;
    temp_f0 = CLAMP(temp_f0, 0.0f, 1.0f);

    if (temp_f0 > 0.01f) {
        D_801F4E30 = 155.0f * temp_f0;
        globalCtx->envCtx.sandstormState = 10;
    } else {
        D_801F4E30 = 0;
        globalCtx->envCtx.sandstormState = 10;
    }
    func_808DC454(this, globalCtx);
}

void func_808DCDB4(ObjectKankyo* this, GlobalContext* globalCtx) {
    s16 i;
    f32 magnitude;
    f32 temp_80;
    f32 temp_120;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 x;
    f32 y;
    f32 z;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f26;
    f32 temp_f28;

    if (this->unk_114C < 0x80) {
        this->unk_114C++;
    }

    x = globalCtx->view.at.x - globalCtx->view.eye.x;
    y = globalCtx->view.at.y - globalCtx->view.eye.y;
    z = globalCtx->view.at.z - globalCtx->view.eye.z;

    magnitude = sqrtf(SQ(x) + SQ(y) + SQ(z));

    spAC = x / magnitude;
    spA8 = y / magnitude;
    spA4 = z / magnitude;

    temp_80 = 80.0f;
    temp_120 = 120.0f;

    for (i = 0; i < this->unk_114C; i++) {
        switch (this->unk_14C[i].unk_1C) {
            case 0:
                this->unk_14C[i].unk_00 = globalCtx->view.eye.x + (spAC * 120.0f);
                this->unk_14C[i].unk_04 = globalCtx->view.eye.y + (spA8 * 120.0f);
                this->unk_14C[i].unk_08 = globalCtx->view.eye.z + (spA4 * 120.0f);
                this->unk_14C[i].unk_0C = (Rand_ZeroOne() - 0.5f) * (temp_120 * 2.0f);
                if ((i % 2) == 0) {
                    this->unk_14C[i].unk_10 = -100.0f;
                } else {
                    this->unk_14C[i].unk_10 = 100.0f;
                }
                this->unk_14C[i].unk_14 = (Rand_ZeroOne() - 0.5f) * (temp_120 * 2.0f);
                this->unk_14C[i].unk_18 = Rand_ZeroOne() + 0.2f;
                this->unk_14C[i].unk_1C++;
                break;

            case 1:

                temp_f26 = globalCtx->view.eye.x + (spAC * 120.0f);
                temp_f28 = globalCtx->view.eye.y + (spA8 * 120.0f);
                temp_f18 = globalCtx->view.eye.z + (spA4 * 120.0f);

                magnitude = sqrtf((f32)SQ(globalCtx->envCtx.windDir.x) + SQ(globalCtx->envCtx.windDir.y) +
                                  SQ(globalCtx->envCtx.windDir.z));
                if (magnitude == 0.0f) {
                    magnitude = 0.001f;
                }

                spA0 = -globalCtx->envCtx.windDir.x / magnitude;
                sp9C = -globalCtx->envCtx.windDir.z / magnitude;

                if (i == 0) {
                    this->unk_144 += 0.049999997f * Rand_ZeroOne();
                    this->unk_148 += 0.049999997f * Rand_ZeroOne();
                }
                temp_f20 = globalCtx->envCtx.windSpeed / 120.0f;
                temp_f20 = CLAMP(temp_f20, 0.0f, 1.0f);

                this->unk_14C[i].unk_0C += __sinf((this->unk_144 + i) * 0.01f) + (spA0 * 10.0f * temp_f20);
                this->unk_14C[i].unk_14 += __cosf((this->unk_148 + i) * 0.01f) + (sp9C * 10.0f * temp_f20);

                if ((i % 2) == 0) {
                    this->unk_14C[i].unk_10 += this->unk_14C[i].unk_18;
                    if ((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) > (globalCtx->view.eye.y + 100.0f)) {
                        this->unk_14C[i].unk_1C = 0;
                    }
                } else {
                    this->unk_14C[i].unk_10 -= this->unk_14C[i].unk_18;
                    if ((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) < (globalCtx->view.eye.y - 100.0f)) {
                        this->unk_14C[i].unk_1C = 0;
                    }
                }

                if (((this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C) - temp_f26) > temp_80) {
                    this->unk_14C[i].unk_00 = temp_f26 - temp_80;
                }

                if (((this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C) - temp_f26) < -temp_80) {
                    this->unk_14C[i].unk_00 = temp_f26 + temp_80;
                }

                if (((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) - temp_f28) > temp_80) {
                    this->unk_14C[i].unk_04 = temp_f28 - temp_80;
                }

                if (((this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10) - temp_f28) < -temp_80) {
                    this->unk_14C[i].unk_04 = temp_f28 + temp_80;
                }

                if (((this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14) - temp_f18) > temp_80) {
                    this->unk_14C[i].unk_08 = temp_f18 - temp_80;
                }

                if (((this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14) - temp_f18) < -temp_80) {
                    this->unk_14C[i].unk_08 = temp_f18 + temp_80;
                }
                break;
        }
    }
}

void ObjectKankyo_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjectKankyo* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjectKankyo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjectKankyo* this = THIS;

    switch (this->actor.params) {
        case 0:
            func_808DDE9C(thisx, globalCtx);
            break;

        case 1:
        case 2:
        case 3:
            func_808DD3C8(thisx, globalCtx);
            break;

        case 4:
            func_808DD970(thisx, globalCtx);
            break;
    }
}

void func_808DD3C8(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjectKankyo* this = THIS;
    Vec3f spC4;
    Vec3f spB8;
    s16 i;
    u8 pad2;
    u8 spB4;
    f32 temp_f0;
    u8 sp68;
    s32 pad;
    f32 temp_f2;
    f32 tempf;

    if ((globalCtx->cameraPtrs[CAM_ID_MAIN]->flags2 & 0x100) || ((u8)globalCtx->envCtx.unk_E2 == 0)) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);
    spB4 = false;

    if (this->actor.params == 3) {
        temp_f0 = func_80173B48(&globalCtx->state) / 1.4e7f;
        temp_f0 = CLAMP(temp_f0, 0.0f, 1.0f);
        Math_SmoothStepToF(&D_808DE5B0, temp_f0, 0.2f, 0.1f, 0.001f);

        sp68 = globalCtx->envCtx.unk_F2[2];
        sp68 *= D_808DE5B0;

        if ((globalCtx->envCtx.unk_F2[2] >= 32) && (sp68 < 32)) {
            sp68 = 32;
        }
    } else {
        sp68 = globalCtx->envCtx.unk_F2[2];
    }

    for (i = 0; i < sp68; i++) {
        spC4.x = this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C;
        spC4.y = this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10;
        spC4.z = this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14;
        func_80169474(globalCtx, &spC4, &spB8);

        if ((spB8.x >= 0.0f) && (spB8.x < 320.0f) && (spB8.y >= 0.0f) && (spB8.y < 240.0f)) {
            if (!spB4) {
                spB4 = true;

                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 255);
                gSPClearGeometryMode(POLY_XLU_DISP++, G_LIGHTING);

                POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);

                gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2);
                gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG);
                gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gDust5Tex));
            }

            Matrix_InsertTranslation(spC4.x, spC4.y, spC4.z, MTXMODE_NEW);
            tempf = (i & 7) * 0.008f;
            Matrix_Scale(0.05f + tempf, 0.05f + tempf, 0.05f + tempf, MTXMODE_APPLY);
            temp_f2 = Math_Vec3f_DistXYZ(&spC4, &globalCtx->view.eye) / 300.0f;
            temp_f2 = ((1.0f < temp_f2) ? 0.0f : (((1.0f - temp_f2) > 1.0f) ? 1.0f : 1.0f - temp_f2));

            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)(160.0f * temp_f2));

            Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_023130);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808DD970(Actor* thisx, GlobalContext* globalCtx2) {
    f32 temp_f0;
    f32 temp_f20;
    Vec3f spBC;
    Vec3f spB0;
    f32 tempf;
    s16 i;
    f32 phi_f26;
    GlobalContext* globalCtx = globalCtx2;
    ObjectKankyo* this = THIS;
    f32 tempA;

    if (globalCtx->sceneNum == SCENE_KYOJINNOMA) {
        phi_f26 = 1.0f;
    } else {
        tempA = Camera_GetWaterYPos(GET_ACTIVE_CAM(globalCtx));
        if (tempA != BGCHECK_Y_MIN) {
            tempA -= globalCtx->view.eye.y;
            phi_f26 = tempA / 4000.0f;
        } else {
            phi_f26 = 0.0f;
        }

        phi_f26 = CLAMP_MAX(phi_f26, 1.0f);

        if (!(globalCtx->cameraPtrs[CAM_ID_MAIN]->flags2 & 0x100) || (phi_f26 == 0.0f)) {
            return;
        }
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    for (i = 0; i < this->unk_114C; i++) {
        spBC.x = this->unk_14C[i].unk_00 + this->unk_14C[i].unk_0C;
        spBC.y = this->unk_14C[i].unk_04 + this->unk_14C[i].unk_10;
        spBC.z = this->unk_14C[i].unk_08 + this->unk_14C[i].unk_14;
        func_80169474(globalCtx, &spBC, &spB0);

        if ((spB0.x >= 0.0f) && (spB0.x < 320.0f) && (spB0.y >= 0.0f) && (spB0.y < 240.0f)) {
            Matrix_InsertTranslation(spBC.x, spBC.y, spBC.z, MTXMODE_NEW);
            Matrix_Scale(0.03f, 0.03f, 0.03f, MTXMODE_APPLY);
            temp_f0 = Math_Vec3f_DistXYZ(&spBC, &globalCtx->view.eye);
            temp_f0 = (u8)(255.0f * phi_f26) * (1.0f - (temp_f0 / 300.0f));

            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 55, temp_f0);
            gDPSetEnvColor(POLY_XLU_DISP++, 55, 50, 255, temp_f0);

            Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gDust5Tex));
            gSPClearGeometryMode(POLY_XLU_DISP++, G_LIGHTING);

            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);

            gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2);
            gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_023130);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

f32 func_808DDE74(void) {
    return Rand_ZeroOne() - 0.5f;
}

#ifdef NON_MATCHING
// globalCtx->envCtx.unk_F2[1] needs to be laoded into s0 and then copied to s7
void func_808DDE9C(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjectKankyo* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    s16 temp;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    u8 phi_s5;
    s32 end = globalCtx->envCtx.unk_F2[1];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (end != 0) {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 150, 255, 255, 25);
        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
    }

    for (i = 0; i < end; i++) {
        temp_f20 = this->unk_14C[0].unk_00 + ((Rand_ZeroOne() - 0.7f) * this->unk_144);
        temp_f22 = this->unk_14C[0].unk_04 + ((Rand_ZeroOne() - 0.7f) * this->unk_144);
        temp_f2 = this->unk_14C[0].unk_08 + ((Rand_ZeroOne() - 0.7f) * this->unk_144);

        if ((temp_f20 < -252.0f) && (temp_f20 > -500.0f) && (temp_f2 > 3820.0f) && (temp_f2 < 4150.0f)) {
            continue;
        }

        Matrix_InsertTranslation(temp_f20, temp_f22, temp_f2, MTXMODE_NEW);

        gSPMatrix(POLY_XLU_DISP++, &D_01000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        Matrix_RotateY((s16)this->unk_14C[2].unk_04 + (s16)(i << 5), MTXMODE_APPLY);
        Matrix_InsertXRotation_s((s16)this->unk_14C[2].unk_00 + (s16)(i << 5), MTXMODE_APPLY);

        if (this->unk_114C == 0) {
            Matrix_Scale(0.5f, 1.0f, 0.5f, MTXMODE_APPLY);
        } else {
            Matrix_Scale(2.0f, 4.0f, 2.0f, MTXMODE_APPLY);
        }

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_0706E0);
    }

    phi_s5 = false;
    if (player->actor.floorHeight < globalCtx->view.eye.y) {
        for (i = 0; i < end; i++) {
            if (!phi_s5) {
                func_8012C2DC(globalCtx->state.gfxCtx);

                gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 255);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 100);
                phi_s5++;
            }

            temp_f20 = this->unk_14C[1].unk_00 + (func_808DDE74() * 220.0f);
            temp_f22 = player->actor.floorHeight + 2.0f;
            temp_f2 = this->unk_14C[1].unk_08 + (func_808DDE74() * 220.0f);

            if ((temp_f20 < -252.0f) && (temp_f20 > -500.0f) && (temp_f2 > 3820.0f) && (temp_f2 < 4150.0f)) {
                continue;
            }

            Matrix_InsertTranslation(temp_f20, temp_f22, temp_f2, MTXMODE_NEW);
            temp_f12 = (Rand_ZeroOne() * 0.05f) + 0.05f;
            Matrix_Scale(temp_f12, temp_f12, temp_f12, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_030100);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DDE9C.s")
#endif
