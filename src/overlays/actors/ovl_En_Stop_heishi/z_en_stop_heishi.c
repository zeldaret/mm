/*
 * File: z_en_stop_heishi.c
 * Overlay: ovl_En_Stop_heishi
 * Description: Clock Town - Gate-Blocking Soldier
 */

#include "z_en_stop_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnStopheishi*)thisx)

void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE85C4(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE7E9C(EnStopheishi* this);

extern AnimationHeader D_06004AC0;
extern AnimationHeader D_06005320;
extern AnimationHeader D_06006C18;
extern AnimationHeader D_0600DC7C;
extern AnimationHeader D_060057BC;
extern AnimationHeader D_06005D28;
extern AnimationHeader D_060064C0;
extern AnimationHeader D_06000A54;

const ActorInit En_Stop_heishi_InitVars = {
    ACTOR_EN_STOP_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStopheishi),
    (ActorFunc)EnStopheishi_Init,
    (ActorFunc)EnStopheishi_Destroy,
    (ActorFunc)EnStopheishi_Update,
    (ActorFunc)EnStopheishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AE88B0 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 50, 260, 0, { 0, 0, 0 } },
};

typedef struct struct_80AE88DC {
    u16 textId;
    u16 unk_02;
} struct_80AE88DC;

struct_80AE88DC D_80AE88DC[] = {
    { 0x0516, 0x0517 }, { 0x051A, 0x0000 }, { 0x051C, 0x0000 }, { 0x051E, 0x0000 }, { 0x0520, 0x0521 },
    { 0x0524, 0x0000 }, { 0x0526, 0x0000 }, { 0x0528, 0x0000 }, { 0x052A, 0x052B }, { 0x052E, 0x0000 },
    { 0x0530, 0x0000 }, { 0x0532, 0x0000 }, { 0x0534, 0x0535 }, { 0x0538, 0x0000 }, { 0x053A, 0x0000 },
    { 0x053C, 0x0000 }, { 0x0518, 0x0519 }, { 0x051B, 0x0000 }, { 0x051D, 0x0000 }, { 0x051F, 0x0000 },
    { 0x0522, 0x0523 }, { 0x0525, 0x0000 }, { 0x0527, 0x0000 }, { 0x0529, 0x0000 }, { 0x052C, 0x052D },
    { 0x052F, 0x0000 }, { 0x0531, 0x0000 }, { 0x0533, 0x0000 }, { 0x0536, 0x0537 }, { 0x0539, 0x0000 },
    { 0x053B, 0x0000 }, { 0x053D, 0x0000 }, { 0x0514, 0x0000 }, { 0x0560, 0x0000 }, { 0x0562, 0x0000 },
    { 0x0564, 0x0000 }, { 0x0515, 0x0000 }, { 0x0561, 0x0000 }, { 0x0563, 0x0000 }, { 0x0565, 0x0000 },
};

typedef struct struct_80AE897C {
    u16 textId;
    u16 unk_02;
} struct_80AE897C;

struct_80AE897C D_80AE897C[] = {
    { 0x0540, 0x0541 }, { 0x0542, 0x0000 }, { 0x0543, 0x0000 }, { 0x0543, 0x0000 }, { 0x0547, 0x0548 },
    { 0x0549, 0x0000 }, { 0x054A, 0x0000 }, { 0x054B, 0x0000 }, { 0x054F, 0x0550 }, { 0x0551, 0x0000 },
    { 0x0552, 0x0000 }, { 0x0553, 0x0000 }, { 0x0557, 0x0558 }, { 0x0559, 0x0000 }, { 0x055A, 0x0000 },
    { 0x055A, 0x0000 }, { 0x0544, 0x0545 }, { 0x0546, 0x0000 }, { 0x0546, 0x0000 }, { 0x0546, 0x0000 },
    { 0x054C, 0x054D }, { 0x054E, 0x0000 }, { 0x054E, 0x0000 }, { 0x054E, 0x0000 }, { 0x0554, 0x0555 },
    { 0x0556, 0x0000 }, { 0x0556, 0x0000 }, { 0x0556, 0x0000 }, { 0x055B, 0x055C }, { 0x055D, 0x0000 },
    { 0x055D, 0x0000 }, { 0x055D, 0x0000 }, { 0x053E, 0x0000 }, { 0x053E, 0x0000 }, { 0x053E, 0x0000 },
    { 0x053E, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 },
};

AnimationHeader* D_80AE8A1C[] = {
    &D_06004AC0, &D_06005320,
    //};
    //
    // AnimationHeader* D_80AE8A24[] = {
    &D_06006C18, &D_0600DC7C, &D_060057BC, &D_06005D28, &D_060064C0, &D_06000A54,
    //};

    // AnimationHeader* D_80AE8A2C = &D_060057BC;

    // AnimationHeader* D_80AE8A30[] = {
    //    &D_06005D28,
    //    &D_060064C0,
    //    &D_06000A54,
    //    0x00000000,
};

extern ColliderCylinderInit D_80AE88B0;
extern FlexSkeletonHeader D_0600D640;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Init.s")
void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = THIS;
    f32 temp_f10;
    s16 zRot;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600D640, &D_06006C18, this->limbDrawTable,
                     this->transitionDrawTable, 17);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_276 = ((this->actor.params >> 0xC) & 0xF);
    this->unk_27A = (this->actor.params & 0x3F);
    this->unk_288 = (this->actor.world.rot.z * 40.0f) + 50.0f;
    this->actor.world.rot.z = 0;
    if (this->unk_27A == 0x7F) {
        this->unk_27A = -1;
    }
    if ((this->unk_27A >= 0) && (Flags_GetSwitch(globalCtx, this->unk_27A) != 0)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actor.targetMode = 0;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80AE88B0);
    this->unk_280 = this->actor.world.rot.y;
    this->unk_284 = 6;
    func_80AE7E9C(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Destroy.s")

void func_80AE750C(EnStopheishi* this, s32 arg1) { // Set anim?
    s32 phi_t0;
    f32 phi_f0;

    this->unk_268 = arg1;
    this->unk_26C = SkelAnime_GetFrameCount(D_80AE8A1C[arg1]);
    phi_t0 = 2;
    phi_f0 = -10.0f;
    if ((arg1 >= 2) && (arg1 != 4)) {
        phi_t0 = 0;
    }
    if (arg1 == 5) {
        phi_f0 = 0.0f;
    }
    SkelAnime_ChangeAnim(&this->skelAnime, D_80AE8A1C[arg1], 1.0f, 0.0f, this->unk_26C, phi_t0, phi_f0);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE75C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE77D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE795C.s")

void func_80AE7E9C(EnStopheishi* this) {
    func_80AE750C(this, 2);
    if ((gSaveContext.day != 3) && (gSaveContext.isNight != 0)) {
        func_80AE750C(this, 3);
    }
    if (gSaveContext.day == 3) {
        func_80AE750C(this, 7);
    }
    this->unk_274 = 0;
    this->unk_278 = 0;
    this->actionFunc = func_80AE7F34;
    this->actor.speedXZ = 0.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7F34.s")
void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx) {
    Player* player;
    s16 sp32;
    f32 zDistToPlayer;
    f32 xDistToPlayer;
    s16 yawDiff;
    s32 yawDiffAbs;
    u32 temp_v0;
    u32 temp_v0_1;
    u32 temp_v1;
    s16 phi_a2;
    u16 phi_t8;

    player = PLAYER;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->unk_268 == 5) && (((s32)this->skelAnime.animCurrentFrame & 1) != 0)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SOLDIER_WALK);
    }
    if (gSaveContext.day != 3) {
        func_80AE75C8(this, globalCtx);
    } else {
        func_80AE7718(this);
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_280, 1, 0x1388, 0);
    sp32 = 0;
    if (gSaveContext.isNight != 0) {
        sp32 = 0x20;
    }

    phi_a2 = 0;
    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            // temp_v1 = gSaveContext.roomInf[126][5];
            temp_v0_1 = (u32)(gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18;
            temp_v0 = (u32)(gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10;
            if ((temp_v0_1 == 0x10) || (temp_v0_1 == 0x4D) || (temp_v0_1 == 0x4E) || (temp_v0_1 == 0x4F) ||
                ((temp_v0 == 0x10)) || (temp_v0 == 0x4D) || (temp_v0 == 0x4E) || (temp_v0 == 0x4F)) {
                if (this->unk_265 != 0) {
                    phi_a2 = 1;
                }
            } else if ((gSaveContext.weekEventReg[0xC] & 0x20) != 0) {
                phi_a2 = 1;
            }
            break;
        case PLAYER_FORM_GORON:
            phi_a2 = 2;
            break;
        case PLAYER_FORM_ZORA:
            phi_a2 = 3;
            break;
        case PLAYER_FORM_DEKU:
            phi_a2 = 4;
            break;
    }

    if (((phi_a2 == 1) || (phi_a2 == 2) || (phi_a2 == 3)) &&
        (((this->unk_268 == 4)) || (this->unk_268 == 5) || (this->unk_268 == 6))) {
        func_80AE750C(this, 2);

        if ((gSaveContext.day != 3) && (gSaveContext.isNight != 0)) {
            func_80AE750C(this, 3);
        }
        if (gSaveContext.day == 3) {
            func_80AE750C(this, 7);
        }
    }
    if ((phi_a2 == 0) || (phi_a2 == 4)) {
        xDistToPlayer = this->actor.home.pos.x - player->actor.world.pos.x;
        zDistToPlayer = this->actor.home.pos.z - player->actor.world.pos.z;
        this->collider.dim.radius = 0x32;
        this->collider.dim.height = 0x104;
        if (sqrtf((xDistToPlayer * xDistToPlayer) + (zDistToPlayer * zDistToPlayer)) < 240.0f) {
            func_80AE795C(this, globalCtx);
        } else {
            func_80AE77D4(this, globalCtx);
        }
    } else {
        this->collider.dim.radius = 0xF;
        this->collider.dim.height = 0x3C;
    }
    if (phi_a2 != 4) {
        this->unk_27C = this->unk_276 * 8;
        this->unk_27C = this->unk_27C + sp32;
        this->unk_27C = this->unk_27C + (phi_a2 * 2);
    } else {
         this->unk_27C = 0x40;
         if (sp32 != 0) {
            this->unk_27C = 0x48;
        }
        //this->unk_27C = sp32 != 0 ? 0x48 : 0x40;
        this->unk_27C = this->unk_27C + (this->unk_276 * 2);
    }
    if (gSaveContext.day != 3) {
        this->actor.textId = D_80AE88DC[this->unk_27C].textId;
        this->unk_27E = D_80AE88DC[this->unk_27C].unk_02;
    } else {
        this->actor.textId = D_80AE897C[this->unk_27C].textId;
        this->unk_27E = D_80AE897C[this->unk_27C].unk_02;
    }
    if (this->unk_27E != 0) {
        temp_v1 = gSaveContext.roomInf[126][5];
        temp_v0 = (u32)(temp_v1 & 0xFF000000) >> 0x18;
        if ((temp_v0 == 0x10) || (temp_v0 == 0x4D) || (temp_v0 == 0x4E) || (temp_v0 == 0x4F) ||
            (temp_v0_1 = (u32)(temp_v1 & 0xFF0000) >> 0x10, (temp_v0_1 == 0x10)) || (temp_v0_1 == 0x4D) ||
            (temp_v0_1 == 0x4E) || (temp_v0_1 == 0x4F)) {
            this->actor.textId = this->actor.textId;
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x56C;
            } else {
                phi_t8 = 0x56EU;
                if (this->actor.textId == 0x520) {
                    this->actor.textId = phi_t8;
                }
                if (this->actor.textId == 0x52A) {
                    this->actor.textId = 0x570;
                } else if (this->actor.textId == 0x534) {
                    this->actor.textId = 0x572;
                } else if (this->actor.textId == 0x518) {
                    this->actor.textId = 0x56D;
                } else if (this->actor.textId == 0x522) {
                    this->actor.textId = 0x56F;
                } else if (this->actor.textId == 0x52C) {
                    this->actor.textId = 0x571;
                } else if (this->actor.textId == 0x536) {
                    this->actor.textId = 0x573;
                }
            }
        } else if (CUR_EQUIP_VALUE(EQUIP_SWORD) == 0) {
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x55E;
            } else if (this->actor.textId == 0x520) {
                this->actor.textId = 0x566;
            } else if (this->actor.textId == 0x52A) {
                this->actor.textId = 0x568;
            } else if (this->actor.textId == 0x534) {
                this->actor.textId = 0x56A;
            } else if (this->actor.textId == 0x518) {
                this->actor.textId = 0x55F;
            } else if (this->actor.textId == 0x522) {
                this->actor.textId = 0x567;
            } else if (this->actor.textId == 0x52C) {
                this->actor.textId = 0x569;
            } else {
                phi_t8 = 0x56BU;
                if (this->actor.textId == 0x536) {
                    this->actor.textId = phi_t8;
                }
            }
        }
    }
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    yawDiffAbs = ABS(yawDiff);

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->skelAnime.animPlaybackSpeed = 1.0f;
        func_80AE854C(&this->actor, globalCtx);
        return;
    }
    if (yawDiffAbs < 0x4BB9) {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE85C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Draw.s")
