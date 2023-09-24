typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk_144;
    /* 0x188 */ void (*actionFunc)(EnAn*, PlayState*);
    /* 0x18C */ s8 unk_18C[4];
    /* 0x190 */ ColliderCylinder unk_190;
    /* 0x1DC */ Path* unk_1DC;                      /* inferred */
    /* 0x1E0 */ char pad_1E0[0x10];                 /* maybe part of unk_1DC[5]? */
    /* 0x1F0 */ s32 unk_1F0;                        /* inferred */
    /* 0x1F4 */ s32 unk_1F4;                        /* inferred */
    /* 0x1F8 */ s32 unk_1F8;                        /* inferred */
    /* 0x1FC */ s32 unk_1FC;                        /* inferred */
    /* 0x200 */ u8 unk_200;
    /* 0x201 */ char pad_201[3];                    /* maybe part of unk_200[4]? */
    /* 0x204 */ void* unk_204;
    /* 0x208 */ s8 unk_208;
    /* 0x209 */ s8 unk_209;
    /* 0x20A */ s8 unk_20A;
    /* 0x20B */ s8 unk_20B;
    /* 0x20C */ s8 unk_20C;
    /* 0x20D */ char pad_20D[3];                    /* maybe part of unk_20C[4]? */
    /* 0x210 */ s32 unk_210;
    /* 0x214 */ s8 unk_214;
    /* 0x215 */ s8 unk_215;                         /* inferred */
    /* 0x216 */ char pad_216[2];                    /* maybe part of unk_215[3]? */
    /* 0x218 */ Actor* unk_218;
    /* 0x21C */ s8 unk_21C[0x24];
    /* 0x240 */ Vec3f unk_240;
    /* 0x24C */ s8 unk_24C[0xC];
    /* 0x258 */ Vec3s unk_258;
    /* 0x25E */ s8 unk_25E[2];
    /* 0x260 */ s8 unk_260[4];
    /* 0x264 */ Vec3s unk_264[0x15];
    /* 0x2E2 */ Vec3s unk_2E2[0x15];
    /* 0x360 */ u16 unk_360;
    /* 0x362 */ u16 unk_362;                        /* inferred */
    /* 0x364 */ s8 unk_364;
    /* 0x365 */ char pad_365[3];                    /* maybe part of unk_364[4]? */
    /* 0x368 */ f32 unk_368;
    /* 0x36C */ char pad_36C[8];                    /* maybe part of unk_368[3]? */
    /* 0x374 */ f32 unk_374;
    /* 0x378 */ s16 unk_378;                        /* inferred */
    /* 0x37A */ s16 unk_37A;                        /* inferred */
    /* 0x37C */ s16 unk_37C;
    /* 0x37E */ s16 unk_37E;
    /* 0x380 */ char pad_380[4];                    /* maybe part of unk_37E[3]? */
    /* 0x384 */ s16 unk_384;
    /* 0x386 */ char pad_386[2];
    /* 0x388 */ s16 unk_388;
    /* 0x38A */ s16 unk_38A;
    /* 0x38C */ s16 unk_38C;
    /* 0x38E */ s16 unk_38E;
    /* 0x390 */ s16 unk_390;
    /* 0x392 */ s16 unk_392;
    /* 0x394 */ s16 unk_394;                        /* inferred */
    /* 0x396 */ s16 unk_396;                        /* inferred */
    /* 0x398 */ void* unk_398;
    /* 0x39C */ s32 unk_39C;
    /* 0x3A0 */ char pad_3A0[8];                    /* maybe part of unk_39C[3]? */
    /* 0x3A8 */ u32 unk_3A8;
    /* 0x3AC */ u32 unk_3AC;
    /* 0x3B0 */ s32 unk_3B0;
    /* 0x3B4 */ s32 unk_3B4;
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ char pad_3BC[4];
    /* 0x3C0 */ s32 unk_3C0;
    /* 0x3C4 */ s32 unk_3C4;                        /* inferred */
} EnAn;                                             /* size = 0x3C8 */

Actor* func_80B539CC(EnAn* arg0, PlayState* arg1, u8 arg2, s16 arg3); /* static */
struct EnDoor* func_80B53B3C(PlayState* arg0, u8 arg1); /* static */
s32 func_80B54678(Actor* arg0, s16 arg1, s32);      /* static */
s16 func_80B546F4(Actor* arg0, s32 arg1);           /* static */
s16 func_80B54750(Actor* arg0, s32 arg1);           /* static */
s32 func_80B547C8(Actor* arg0, PlayState* arg1);    /* static */
s32 func_80B5492C(Actor* arg0, PlayState* arg1);    /* static */
s32 func_80B54A94(Actor* arg0, PlayState* arg1);    /* static */
s32 func_80B54BC4(Actor* arg0, PlayState* arg1);    /* static */
s32 func_80B54C5C(EnAn* arg0, PlayState* arg1);     /* static */
s32 func_80B54D18(EnAn* arg0, PlayState* arg1);     /* static */
?* func_80B54DF4(EnAn* arg0, PlayState* arg1);      /* static */
void func_80B553AC(void* arg0);                     /* static */
? func_80B555C8(EnAn* arg0, PlayState* arg1);       /* static */
void func_80B556F8(EnAn* arg0, PlayState* arg1);    /* static */
void func_80B557AC(EnAn* arg0, PlayState* arg1);    /* static */
void func_80B55860(EnAn* arg0, PlayState* arg1);    /* static */
Actor* func_80B55D20(EnAn* arg0, PlayState* arg1);  /* static */
s32 func_80B55D98(EnAn* arg0, PlayState* arg1, u8* arg2, u8 arg3, s16 arg4); /* static */
s32 func_80B55ECC(Actor* arg0);                     /* static */
s32 func_80B55F8C(PlayState* arg0);                 /* static */
s32 func_80B5600C(EnAn* arg0, PlayState* arg1);     /* static */
s32 func_80B56094(EnAn* arg0, PlayState* arg1);     /* static */
s32 func_80B5611C(EnAn* arg0, PlayState* arg1);     /* static */
s32 func_80B561A4(EnAn* arg0, PlayState* arg1, void* arg2); /* static */
s32 func_80B56418(EnAn* arg0, PlayState* arg1, void* arg2); /* static */
s32 func_80B56744(EnAn* arg0, PlayState* arg1, u8* arg2); /* static */
s32 func_80B56880(EnAn* arg0, PlayState* arg1, u8* arg2); /* static */
s32 func_80B56B00(EnAn* arg0, PlayState* arg1, u8* arg2); /* static */
s32 func_80B56BC0(EnAn* arg0, PlayState* arg1, u8* arg2); /* static */
s32 func_80B56CAC(EnAn* arg0, PlayState* arg1, ? arg2); /* static */
s32 func_80B56D28(EnAn* arg0, u8* arg2, u8*);       /* static */
? func_80B56E44(EnAn* arg0, ? arg1);                /* static */
? func_80B56EB4(Actor* arg0, PlayState* arg1);      /* static */
? func_80B5702C(Actor* arg0, PlayState* arg1);      /* static */
? func_80B572D4(Actor* arg0, PlayState* arg1);      /* static */
? func_80B573F4(EnAn* arg0, PlayState* arg1);       /* static */
? func_80B575BC(Actor* arg0, ? arg1);               /* static */
? func_80B57674(EnAn* arg0, ? arg1);                /* static */
void func_80B57718(EnAn* arg0, PlayState*);         /* static */
extern u8 D_80B581D0;
extern ? D_80B58618;
extern ? D_80B58718;
extern ? D_80B58784;
extern ? D_80B58808;
extern ? D_80B5885C;
extern ? D_80B58938;
extern ? D_80B58944;
extern ? D_80B5894C;
extern ? D_80B58954;
extern ? D_80B58980;
extern ? D_80B58988;
extern ? D_80B58994;
extern ? D_80B5899C;
extern ? D_80B589AC;
extern ? D_80B589FC;
extern ? D_80B58A04;
extern ? D_80B58A24;
extern ? D_80B58A3C;
extern ? D_80B58A44;
extern ? D_80B58ABC;
extern ? D_80B58AC4;
extern ? D_80B58AE8;
extern ? D_80B58AF4;
extern ? D_80B58B3C;
extern ? D_80B58B7C;
extern ? D_80B58B88;
extern ? D_80B58B90;
extern Vec3f D_80B58E34;
extern ? D_80B58E40;
extern Vec3f D_80B58E7C;
extern Vec3s D_80B58E88;
extern Vec3f D_80B58E90;
extern Vec3s D_80B58E9C;
extern Vec3s D_80B58EA4;
extern ? D_80B58EAC;

void EnAn_Destroy(Actor* thisx, PlayState* play) {
    EnAn* this = (EnAn* ) thisx;
    Collider_DestroyCylinder(play, &this->unk_190);
}

void EnAn_Init(Actor* thisx, PlayState* play) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v1;
    EnAn* this = (EnAn* ) thisx;

    if (play->sceneId != 0x61) {
        this->actor.params &= 0x7FFF;
    }
    temp_v0 = gSaveContext.save.saveInfo.weekEventReg[0x33] & 0x40;
    temp_v1 = (s32) (this->actor.params & 0x8000) >> 0xF;
    if (((temp_v0 == 0) && (temp_v1 == 1)) || ((temp_v0 != 0) && (temp_v1 == 0))) {
        Actor_Kill(&this->actor);
        return;
    }
    if (temp_v1 == 0) {
        sp1C = temp_v1;
        if (func_80B53A7C(this, play, 4U, 0x202) != NULL) {
            Actor_Kill(&this->actor);
            return;
        }
    }
    this->unk_214 = -0x80;
    this->unk_3B8 = 0;
    if (temp_v1 == 0) {
        this->actor.room = -1;
    }
    this->actionFunc = func_80B577F0;
}

void EnAn_Update(Actor* thisx, PlayState* play) {
    EnAn* this = (EnAn* ) thisx;
    if (func_80B53840(this, play) == 0) {
        if ((func_80B577F0 != this->actionFunc) && (func_80B55180(this, play) == 0) && (func_80B552E4(this, play) != 0)) {
            func_80B57B48(this, play);
            func_80B53BA8(this, play);
            func_80B53F84(this);
            return;
        }
        this->actionFunc(this, play);
        if (this->unk_200 != 0) {
            func_80B55914(this, play);
            func_80B53BA8(this, play);
            func_80B53F84(this);
            func_80B554E8(this);
            SubS_Offer(&this->actor, play, this->unk_374, 30.0f, 0, this->unk_360 & 7);
            if (!(this->unk_360 & 0x40)) {
                Actor_MoveWithGravity(&this->actor);
                Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4U);
            }
            func_80B53ED4(this, play);
        }
    }
}

s32 func_80B53840(EnAn* this, PlayState* play) {
    s32 sp24;
    void* sp20;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_3;
    s8 temp_a0_4;
    s8 temp_a0_5;

    sp24 = 0;
    if ((play->roomCtx.curRoom.num != this->unk_214) && (play->roomCtx.status == 0) && (this->unk_3B8 == 0)) {
        sp20 = play + 0x18000;
        this->unk_20C = SubS_GetObjectIndex(0x16, play);
        this->unk_20B = SubS_GetObjectIndex(0x1A, play);
        this->unk_20A = SubS_GetObjectIndex(0x1FF, play);
        this->unk_209 = SubS_GetObjectIndex(0xDD, play);
        this->unk_208 = SubS_GetObjectIndex(0xE0, play);
        this->actor.draw = NULL;
        this->unk_3B8 = 1;
        this->unk_214 = sp20->unk_6E0;
    }
    if (this->unk_3B8 == 0) {
        return 0;
    }
    temp_a0 = this->unk_208;
    if (((temp_a0 >= 0) && (SubS_IsObjectLoaded(temp_a0, play) == 0)) || ((temp_a0_2 = this->unk_209, (temp_a0_2 >= 0)) && (SubS_IsObjectLoaded(temp_a0_2, play) == 0)) || ((temp_a0_3 = this->unk_20A, (temp_a0_3 >= 0)) && (SubS_IsObjectLoaded(temp_a0_3, play) == 0)) || ((temp_a0_4 = this->unk_20B, (temp_a0_4 >= 0)) && (SubS_IsObjectLoaded(temp_a0_4, play) == 0)) || ((temp_a0_5 = this->unk_20C, (temp_a0_5 >= 0)) && (SubS_IsObjectLoaded(temp_a0_5, play) == 0))) {
        sp24 = 1;
    } else {
        this->actor.draw = EnAn_Draw;
        this->unk_3B8 = 0;
    }
    return sp24;
}

Actor* func_80B539CC(EnAn* arg0, PlayState* arg1, u8 arg2, s16 arg3) {
    Actor* temp_v0;
    Actor* temp_v1;
    Actor* var_s0;
    Actor* var_s0_2;

    var_s0_2 = NULL;
loop_1:
    temp_v0 = SubS_FindActor(arg1, var_s0_2, arg2 & 0xFF & 0xFF, arg3);
    var_s0 = temp_v0;
    if ((temp_v0 != NULL) && ((temp_v0 == arg0) || (temp_v0->update == NULL))) {
        temp_v1 = temp_v0->next;
        if (temp_v1 == NULL) {
            var_s0 = NULL;
        } else {
            var_s0_2 = temp_v1;
            goto loop_1;
        }
    }
    return var_s0;
}

Actor* func_80B53A7C(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* temp_v0;
    Actor* temp_v1;
    Actor* var_s0;
    Actor* var_s0_2;

    var_s0_2 = NULL;
loop_1:
    temp_v0 = SubS_FindActor(play, var_s0_2, actorCategory & 0xFF & 0xFF, actorId);
    var_s0 = temp_v0;
    if ((temp_v0 != NULL) && ((temp_v0 == this) || (temp_v0->update == NULL) || (temp_v0->params & 0x8000))) {
        temp_v1 = temp_v0->next;
        if (temp_v1 == NULL) {
            var_s0 = NULL;
        } else {
            var_s0_2 = temp_v1;
            goto loop_1;
        }
    }
    return var_s0;
}

struct EnDoor* func_80B53B3C(PlayState* arg0, u8 arg1) {
    s32 var_a1;

    switch (arg1) {
        case 0x1A:
        case 0x1B:
            var_a1 = 0xD;
block_7:
            return SubS_FindDoor(arg0, var_a1);
        case 0x21:
        case 0x22:
        case 0x25:
        case 0x26:
            var_a1 = 0xB;
            goto block_7;
        case 0x24:
            var_a1 = 0x10;
            goto block_7;
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x23:
        case 0x27:
            var_a1 = 0xE;
            goto block_7;
        default:
            return NULL;
    }
}

s32 func_80B53BA8(EnAn* this, PlayState* play) {
    s8 sp1F;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v1;
    s32 var_v1_2;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_3;
    s8 temp_a3;

    temp_v0 = this->unk_39C;
    temp_a3 = this->actor.objBankIndex;
    var_v1 = -1;
    var_t0 = 0;
    if (temp_v0 >= 0x19) {
        temp_a0 = this->unk_20B;
        if (temp_a0 >= 0) {
            var_v1_2 = temp_a0 << 0x18;
            goto block_11;
        }
    }
    if (temp_v0 >= 0x15) {
        temp_a0_2 = this->unk_209;
        if (temp_a0_2 >= 0) {
            var_v1_2 = temp_a0_2 << 0x18;
            goto block_11;
        }
    }
    if (temp_v0 >= 0x11) {
        temp_a0_3 = this->unk_208;
        if (temp_a0_3 >= 0) {
            var_v1_2 = temp_a0_3 << 0x18;
            goto block_11;
        }
    }
    if (temp_v0 < 0x11) {
        var_v1_2 = temp_a3 << 0x18;
block_11:
        var_v1 = var_v1_2 >> 0x18;
    }
    if (var_v1 < 0) {
        return 0;
    }
    if (var_v1 >= 0) {
        *(gSegments + 0x18) = (u32) (play->objectCtx.status[var_v1].segment + 0x80000000);
        this->unk_144.playSpeed = this->unk_368;
        sp1F = temp_a3;
        var_t0 = SkelAnime_Update(&this->unk_144);
        *(gSegments + 0x18) = (u32) (play->objectCtx.status[temp_a3].segment + 0x80000000);
    }
    return var_t0;
}

s32 func_80B53CE8(EnAn* this, PlayState* play, s32 arg2) {
    s8 sp1F;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_t0;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    s8 temp_t1;
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;

    temp_t1 = this->actor.objBankIndex;
    var_v1 = -1;
    var_t0 = 0;
    var_t2 = 0;
    if (arg2 >= 0x19) {
        temp_v0 = this->unk_20B;
        if (temp_v0 >= 0) {
            var_v1_2 = temp_v0 << 0x18;
            goto block_11;
        }
    }
    if (arg2 >= 0x15) {
        temp_v0_2 = this->unk_209;
        if (temp_v0_2 >= 0) {
            var_v1_2 = temp_v0_2 << 0x18;
            goto block_11;
        }
    }
    if (arg2 >= 0x11) {
        temp_v0_3 = this->unk_208;
        if (temp_v0_3 >= 0) {
            var_v1_2 = temp_v0_3 << 0x18;
            goto block_11;
        }
    }
    if (arg2 < 0x11) {
        var_v1_2 = temp_t1 << 0x18;
block_11:
        var_v1 = var_v1_2 >> 0x18;
    }
    if (var_v1 < 0) {
        return 0;
    }
    switch (arg2) {
        case 0x1:
        case 0x2:
            temp_v0_4 = this->unk_39C;
            if ((temp_v0_4 != 1) && (temp_v0_4 != 2)) {
block_26:
                var_t0 = 1;
            }
            break;
        case 0x7:
        case 0x8:
            temp_v0_5 = this->unk_39C;
            if ((temp_v0_5 != 7) && (temp_v0_5 != 8)) {
                goto block_26;
            }
            break;
        case 0x9:
        case 0xA:
            temp_v0_6 = this->unk_39C;
            if ((temp_v0_6 != 9) && (temp_v0_6 != 0xA)) {
                goto block_26;
            }
            break;
        default:
            if (arg2 != this->unk_39C) {
                goto block_26;
            }
            break;
    }
    if ((var_t0 != 0) && (var_v1 >= 0)) {
        *(gSegments + 0x18) = (u32) (play->objectCtx.status[var_v1].segment + 0x80000000);
        this->unk_39C = arg2;
        sp1F = temp_t1;
        temp_v0_7 = SubS_ChangeAnimationByInfoS(&this->unk_144, D_80B58BF4, arg2);
        this->unk_368 = this->unk_144.playSpeed;
        var_t2 = temp_v0_7;
        *(gSegments + 0x18) = (u32) (play->objectCtx.status[temp_t1].segment + 0x80000000);
    }
    return var_t2;
}

void func_80B53ED4(EnAn* this, PlayState* play) {
    Vec3f sp24;
    ColliderCylinder* sp20;
    ColliderCylinder* temp_a2;

    temp_a2 = &this->unk_190;
    if (this->unk_200 == 0x19) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B58E34, &sp24);
        this->unk_190.dim.radius = 0x14;
        Math_Vec3f_ToVec3s(&this->unk_190.dim.pos, &sp24);
    } else {
        sp20 = temp_a2;
        Collider_UpdateCylinder(&this->actor, temp_a2);
    }
    this->unk_190.dim.height = (s16) (s32) (this->actor.focus.pos.y - this->actor.world.pos.y);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_190.base);
}

void func_80B53F84(EnAn* this) {
    s16 temp_t9;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 var_v1;
    s32 var_a1;

    var_a1 = 0;
    if (this->unk_360 & 0x100) {
        temp_v0 = this->unk_38E;
        if (temp_v0 == 0) {
            var_v1 = 0;
        } else {
            this->unk_38E = temp_v0 - 1;
            var_v1 = this->unk_38E;
        }
        if (var_v1 == 0) {
            temp_t9 = this->unk_38C;
            switch (temp_t9) {
                case 0x2:
                case 0x4:
                case 0x6:
                    temp_v0_2 = this->unk_390;
                    if ((temp_v0_2 == 5) || (temp_v0_2 == 2)) {
                        var_a1 = 1;
                        this->unk_390 = 5;
                    }
                    break;
                case 0x5:
                case 0x7:
                    temp_v0_3 = this->unk_390;
                    if ((temp_v0_3 == 6) || (temp_v0_3 == 1)) {
                        var_a1 = 1;
                        this->unk_390 = 6;
                    }
                    break;
                case 0x8:
                    temp_v0_4 = this->unk_390;
                    if ((temp_v0_4 == 4) || (temp_v0_4 == 2)) {
                        var_a1 = 1;
                        this->unk_390 = 4;
                    }
                    break;
            }
            if (var_a1 == 0) {
                temp_v0_5 = this->unk_390;
                if ((temp_v0_5 == 4) || (temp_v0_5 == 5)) {
                    this->unk_390 = 0;
                } else if (temp_v0_5 == 6) {
                    this->unk_390 = 1;
                }
            }
            if (var_a1 == 0) {
                this->unk_390 += 1;
                if (this->unk_390 >= 4) {
                    temp_v0_6 = this->unk_38C;
                    if ((temp_v0_6 == 0) || (temp_v0_6 == 1) || (temp_v0_6 == 3)) {
                        this->unk_38E = Rand_S16Offset(0x1E, 0x1E);
                    } else {
                        this->unk_38E = 8;
                    }
                    this->unk_390 = 0;
                }
            }
        }
    }
    this->unk_392 = *(&D_80B58E40 + (this->unk_38C * 2));
}

void func_80B54124(EnAn* this, PlayState* play, u32 arg2) {
    s8 sp53;
    s8 sp52;
    GraphicsContext* sp4C;
    Gfx* sp44;
    Gfx* sp40;
    Gfx* temp_v0;
    Gfx* temp_v0_10;
    Gfx* temp_v0_11;
    Gfx* temp_v0_12;
    Gfx* temp_v0_13;
    Gfx* temp_v0_14;
    Gfx* temp_v0_15;
    Gfx* temp_v0_16;
    Gfx* temp_v0_17;
    Gfx* temp_v0_18;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    Gfx* temp_v0_4;
    Gfx* temp_v0_5;
    Gfx* temp_v0_6;
    Gfx* temp_v0_7;
    Gfx* temp_v0_8;
    Gfx* temp_v0_9;
    GraphicsContext* temp_t0;
    s8 temp_a2;
    s8 temp_a2_2;
    s8 temp_a2_3;
    s8 temp_a2_4;

    sp53 = this->actor.objBankIndex;
    temp_t0 = play->state.gfxCtx;
    sp4C = temp_t0;
    Matrix_Push();
    switch (arg2) {
        case 0x0:
            if ((this->unk_360 & 0x800) && (this->unk_3B0 == 0)) {
                this->unk_3A8 += 1;
                this->unk_3AC -= 2;
                sp4C = temp_t0;
                Gfx_SetupDL25_Xlu(play->state.gfxCtx);
                temp_v0 = temp_t0->polyXlu.p;
                temp_t0->polyXlu.p = temp_v0 + 8;
                temp_v0->words.w0 = 0xDA380003;
                sp4C = temp_t0;
                sp44 = temp_v0;
                sp44->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                temp_v0_2 = temp_t0->polyXlu.p;
                temp_t0->polyXlu.p = temp_v0_2 + 8;
                temp_v0_2->words.w0 = 0xDB060020;
                sp4C = temp_t0;
                sp40 = temp_v0_2;
                sp40->words.w1 = Gfx_TwoTexScroll(play->state.gfxCtx, 0, this->unk_3A8, 0U, 0x10, 0x10, 1, 0U, this->unk_3AC, 0x10, 0x10);
                temp_v0_3 = temp_t0->polyXlu.p;
                temp_t0->polyXlu.p = temp_v0_3 + 8;
                temp_v0_3->words.w0 = 0xDE000000;
                temp_v0_3->words.w1 = (u32) D_060111E8;
                Gfx_SetupDL25_Opa(play->state.gfxCtx);
            }
            break;
        case 0x1:
            temp_a2 = this->unk_20A;
            if ((this->unk_360 & 0x4000) && (this->unk_3B0 == 0) && (temp_a2 >= 0)) {
                temp_v0_4 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_4 + 8;
                temp_v0_4->words.w0 = 0xDB060028;
                temp_v0_4->words.w1 = (u32) play->objectCtx.status[temp_a2].segment;
                sp4C = temp_t0;
                Matrix_TranslateRotateZYX(&D_80B58E54, &D_80B58E60);
                temp_v0_5 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_5 + 8;
                temp_v0_5->words.w0 = 0xDA380003;
                sp4C = temp_t0;
                temp_v0_5->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                temp_v0_6 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_6 + 8;
                temp_v0_6->words.w0 = 0xDE000000;
                temp_v0_6->words.w1 = (u32) D_0A000D40;
                temp_v0_7 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_7 + 8;
                temp_v0_7->words.w0 = 0xDB060018;
                temp_v0_7->words.w1 = (u32) play->objectCtx.status[sp53].segment;
            }
            break;
        case 0x2:
            temp_a2_2 = this->unk_208;
            if ((this->unk_360 & 0x1000) && (this->unk_3B0 == 0) && (temp_a2_2 >= 0)) {
                temp_v0_8 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_8 + 8;
                temp_v0_8->words.w0 = 0xDB060018;
                temp_v0_8->words.w1 = (u32) play->objectCtx.status[temp_a2_2].segment;
                temp_v0_9 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_9 + 8;
                temp_v0_9->words.w1 = (u32) D_06000378;
                temp_v0_9->words.w0 = 0xDE000000;
                temp_v0_10 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_10 + 8;
                temp_v0_10->words.w0 = 0xDB060018;
                temp_v0_10->words.w1 = (u32) play->objectCtx.status[sp53].segment;
            }
            break;
        case 0x3:
            temp_a2_3 = this->unk_209;
            if ((this->unk_360 & 0x2000) && (this->unk_3B0 == 0) && (temp_a2_3 >= 0)) {
                temp_v0_11 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_11 + 8;
                temp_v0_11->words.w0 = 0xDB060018;
                temp_v0_11->words.w1 = (u32) play->objectCtx.status[temp_a2_3].segment;
                temp_v0_12 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_12 + 8;
                temp_v0_12->words.w1 = (u32) D_06000308;
                temp_v0_12->words.w0 = 0xDE000000;
                temp_v0_13 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_13 + 8;
                temp_v0_13->words.w0 = 0xDB060018;
                temp_v0_13->words.w1 = (u32) play->objectCtx.status[sp53].segment;
            }
            break;
        case 0x4:
            if ((this->unk_360 & 0x8000) && (this->unk_3B0 == 0)) {
                temp_v0_14 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_14 + 8;
                temp_v0_14->words.w1 = (u32) D_06012478;
                temp_v0_14->words.w0 = 0xDE000000;
            }
            break;
        case 0x5:
            temp_a2_4 = this->unk_20C;
            if ((this->unk_3B4 != 0) && (temp_a2_4 >= 0)) {
                sp52 = temp_a2_4;
                sp4C = temp_t0;
                Matrix_TranslateRotateZYX(&D_80B58E68, &D_80B58E74);
                temp_v0_15 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_15 + 8;
                temp_v0_15->words.w0 = 0xDA380003;
                sp4C = temp_t0;
                sp52 = temp_a2_4;
                temp_v0_15->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
                temp_v0_16 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_16 + 8;
                temp_v0_16->words.w0 = 0xDB060018;
                temp_v0_16->words.w1 = (u32) play->objectCtx.status[temp_a2_4].segment;
                temp_v0_17 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_17 + 8;
                temp_v0_17->words.w1 = (u32) D_06000E70;
                temp_v0_17->words.w0 = 0xDE000000;
                temp_v0_18 = temp_t0->polyOpa.p;
                temp_t0->polyOpa.p = temp_v0_18 + 8;
                temp_v0_18->words.w0 = 0xDB060018;
                temp_v0_18->words.w1 = (u32) play->objectCtx.status[sp53].segment;
            }
            break;
    }
    Matrix_Pop();
}

s32 func_80B54678(Actor* arg0, s16 arg1) {
    s32 sp1C;

    sp1C = 0;
    if (CutsceneManager_GetCurrentCsId() == 0x7C) {
        CutsceneManager_Stop(0x7C);
        CutsceneManager_Queue(arg1);
    } else if (CutsceneManager_IsNext(arg1) != 0) {
        CutsceneManager_StartWithPlayerCs(arg1, arg0);
        sp1C = 1;
    } else {
        CutsceneManager_Queue(arg1);
    }
    return sp1C;
}

s16 func_80B546F4(Actor* arg0, s32 arg1) {
    s32 var_s0;
    s8 var_s1;

    var_s1 = arg0->csId;
    var_s0 = 0;
    if (arg1 > 0) {
        do {
            var_s0 += 1;
            var_s1 = (s8) CutsceneManager_GetAdditionalCsId((s16) var_s1);
        } while (var_s0 != arg1);
    }
    return (s16) var_s1;
}

s16 func_80B54750(Actor* arg0, s32 arg1) {
    Actor* temp_v0;
    s32 var_s0;
    s8 var_s1;

    temp_v0 = arg0->child;
    var_s1 = -1;
    if (temp_v0 != NULL) {
        var_s0 = 0;
        if (temp_v0->update != NULL) {
            var_s1 = temp_v0->csId;
            if (arg1 > 0) {
                do {
                    var_s0 += 1;
                    var_s1 = (s8) CutsceneManager_GetAdditionalCsId((s16) var_s1);
                } while (var_s0 != arg1);
            }
        }
    }
    return (s16) var_s1;
}

s32 func_80B547C8(Actor* arg0, PlayState* arg1) {
    s16 sp2A;
    s32 sp24;
    Actor* temp_v0;
    s16 temp_a0;
    s16 temp_a1;
    s32 var_v1;

    temp_a0 = arg0->unk_394;
    temp_a1 = func_80B546F4(arg0, 0);
    var_v1 = 0;
    switch (temp_a0) {
        case 0x0:
            sp24 = 0;
            sp2A = temp_a1;
            var_v1 = 0;
            if (func_80B54678(arg0, temp_a1) != 0) {
            case 0x2:
            case 0x4:
            case 0x6:
                Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0);
                var_v1 = 1;
                arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            }
            break;
        case 0x1:
        case 0x3:
        case 0x5:
            if ((gSaveContext.save.saveInfo.weekEventReg[0x56] & 8) && (temp_a0 == 3)) {
                CutsceneManager_Stop(temp_a1);
            } else {
                temp_v0 = arg0->child;
                if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
                    Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0->child);
                }
            }
            arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            var_v1 = 1;
            break;
        case 0x7:
            CutsceneManager_Stop(temp_a1);
            var_v1 = 1;
            arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            break;
    }
    return var_v1;
}

s32 func_80B5492C(Actor* arg0, PlayState* arg1) {
    s16 sp2A;
    s32 sp24;
    Actor* temp_v0;
    s16 temp_a1;
    s16 temp_v1;
    s32 var_a2;

    temp_v1 = arg0->unk_394;
    temp_a1 = func_80B546F4(arg0, 0);
    var_a2 = 0;
    switch (temp_v1) {
        case 0x0:
            sp2A = temp_a1;
            sp24 = 0;
            var_a2 = 0;
            if (func_80B54678(arg0, temp_a1, 0) != 0) {
            case 0x2:
            case 0x4:
                Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0);
                var_a2 = 1;
                arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            }
            break;
        case 0x1:
        case 0x3:
            if (!(gSaveContext.save.saveInfo.weekEventReg[0x4B] & 0x10) && (temp_v1 == 3)) {
                CutsceneManager_Stop(temp_a1);
                arg0->unk_394 = 5;
            } else {
                temp_v0 = arg0->child;
                if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
                    Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0->child);
                }
            }
            arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            var_a2 = 1;
            break;
        case 0x5:
            CutsceneManager_Stop(temp_a1);
            var_a2 = 1;
            arg0->unk_394 = (s16) (arg0->unk_394 + 1);
            break;
    }
    return var_a2;
}

s32 func_80B54A94(Actor* arg0, PlayState* arg1) {
    s16 sp2A;
    s32 sp24;
    Actor* temp_v0;
    s16 temp_a1;
    s32 var_v1;
    u16 temp_t6;

    temp_t6 = arg0->unk_394;
    temp_a1 = func_80B54750(arg0, 0);
    var_v1 = 0;
    switch (temp_t6) {
        case 0x0:
            sp24 = 0;
            sp2A = temp_a1;
            var_v1 = 0;
            if (func_80B54678(arg0, temp_a1) != 0) {
            case 0x2:
            case 0x4:
            case 0x6:
            case 0x8:
                temp_v0 = arg0->child;
                if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
                    Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0->child);
                }
                var_v1 = 1;
                arg0->unk_394 = (u16) ((s16) arg0->unk_394 + 1);
            }
            break;
        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            Camera_SetTargetActor(Play_GetCamera(arg1, CutsceneManager_GetCurrentSubCamId(temp_a1)), arg0);
            var_v1 = 1;
            arg0->unk_394 = (u16) ((s16) arg0->unk_394 + 1);
            break;
        case 0x9:
            CutsceneManager_Stop(temp_a1);
            var_v1 = 1;
            arg0->unk_394 = (u16) ((s16) arg0->unk_394 + 1);
            break;
    }
    return var_v1;
}

s32 func_80B54BC4(Actor* arg0, PlayState* arg1) {
    if (arg0->unk_394 == 0) {
        func_800B7298(arg1, arg0, 7U);
        arg1->nextEntrance = 0xBC30;
        gSaveContext.nextCutsceneIndex = 0;
        arg1->transitionTrigger = 0x14;
        arg1->transitionType = 2;
        gSaveContext.nextTransitionType = 6;
        arg0->unk_394 = (s16) (arg0->unk_394 + 1);
    }
    return 0;
}

s32 func_80B54C5C(EnAn* arg0, PlayState* arg1) {
    s32 sp20;
    s16 temp_v0;

    sp20 = 0;
    temp_v0 = arg0->unk_394;
    switch (temp_v0) {                              /* irregular */
        case 0x0:
            func_80B53CE8(arg0, arg1, 0xD);
            arg0->unk_394 += 1;
            break;
        case 0x1:
        case 0x3:
            if (Animation_OnFrame(arg0 + 0x144, arg0->unk_144.endFrame) != 0) {
                arg0->unk_394 += 1;
                sp20 = 1;
            }
            break;
        case 0x2:
            func_80B53CE8(arg0, arg1, 0xE);
            arg0->unk_394 += 1;
            break;
    }
    return sp20;
}

s32 func_80B54D18(EnAn* arg0, PlayState* arg1) {
    s16 temp_v0;
    s32 var_v1;
    u16 temp_t6;

    temp_v0 = arg0->unk_394;
    var_v1 = 0;
    switch (temp_v0) {                              /* irregular */
        case 0x0:
            if ((Player_GetMask(arg1) == 2) || (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20)) {
                arg0->unk_394 += 1;
            case 0x1:
                temp_t6 = arg0->unk_360 & 0xBFDF;
                arg0->unk_360 = temp_t6;
                arg0->unk_360 = temp_t6 | 0x200;
                func_80B53CE8(arg0, arg1, 0x14);
                var_v1 = 1;
                arg0->unk_394 += 1;
            } else {
                var_v1 = 1;
                arg0->unk_360 |= 0x4000;
                arg0->unk_394 += 1;
            }
            break;
    }
    return var_v1;
}

?* func_80B54DF4(EnAn* arg0, PlayState* arg1) {
    Actor* sp1C;
    Actor* temp_v1;
    u8 temp_a0;
    u8 temp_t3;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    temp_v0 = arg0->unk_200;
    temp_v1 = arg1->actorCtx.actorLists[2].first;
    switch (temp_v0) {                              /* switch 1 */
        case 0x15:                                  /* switch 1 */
            arg0->unk_398 = func_80B54A94;
            return &D_80B58808;
        case 0x10:                                  /* switch 1 */
            arg0->unk_398 = func_80B547C8;
            return &D_80B58718;
        case 0x11:                                  /* switch 1 */
            arg0->unk_398 = func_80B5492C;
            return &D_80B58784;
        case 0xE:                                   /* switch 1 */
            arg0->unk_398 = (s32 (*)(Actor*, PlayState*)) func_80B54C5C;
            return &D_80B58954;
        case 0xC:                                   /* switch 1 */
            return &D_80B5899C;
        case 0x19:                                  /* switch 1 */
            return &D_80B58B90;
        default:                                    /* switch 1 */
            if (temp_v1->unk_14B == 3) {
                if ((s32) temp_v0 >= 4) {
                    switch (temp_v0) {              /* switch 2 */
                        case 0x28:                  /* switch 2 */
                        case 0x2A:                  /* switch 2 */
                        case 0x2B:                  /* switch 2 */
                        case 0x2C:                  /* switch 2 */
                        case 0x2D:                  /* switch 2 */
                        case 0x2F:                  /* switch 2 */
                            return &D_80B58B7C;
                        case 0x31:                  /* switch 2 */
                            return &D_80B589FC;
                        default:                    /* switch 2 */
                            return &D_80B58A04;
                    }
                } else {
                    switch (temp_v0) {              /* switch 4; irregular */
                        case 0x1:                   /* switch 4 */
                            return &D_80B58AE8;
                        case 0x3:                   /* switch 4 */
                            return &D_80B58A24;
                        default:                    /* switch 4 */
                            return &D_80B58A04;
                    }
                }
            } else {
                sp1C = temp_v1;
                if (Player_GetMask(arg1) == 2) {
                    temp_v0_2 = arg0->unk_200;
                    if (temp_v0_2 == 0x31) {
                        return &D_80B58B88;
                    }
                    if (temp_v0_2 == 0x17) {
                        arg0->unk_398 = func_80B54BC4;
                        return &D_80B589AC;
                    }
                    if (temp_v0_2 == 3) {
                        arg0->unk_398 = (s32 (*)(Actor*, PlayState*)) func_80B54D18;
                        return &D_80B58B3C;
                    }
                    if (gSaveContext.save.day >= 2) {
                        return &D_80B58A44;
                    }
                    if ((gSaveContext.save.time - 0x3FFC) < 0x5883) {
                        return &D_80B58ABC;
                    }
                    return &D_80B58AC4;
                }
                temp_a0 = temp_v1->unk_14B;
                if ((temp_a0 == 4) && (gSaveContext.save.saveInfo.weekEventReg[0x32] & 8)) {
                    temp_v0_3 = arg0->unk_200;
                    if (temp_v0_3 == 0x17) {
                        arg0->unk_398 = func_80B54BC4;
                        return &D_80B589AC;
                    }
                    if (temp_v0_3 == 3) {
                        arg0->unk_398 = (s32 (*)(Actor*, PlayState*)) func_80B54D18;
                        return &D_80B58AF4;
                    }
                    if (gSaveContext.save.day >= 2) {
                        return &D_80B58A44;
                    }
                    goto block_40;
                }
block_40:
                temp_t3 = arg0->unk_200;
                switch (temp_t3) {                  /* switch 3 */
                    case 0x1:                       /* switch 3 */
                        return &D_80B58AE8;
                    case 0x28:                      /* switch 3 */
                        return &D_80B5894C;
                    case 0x2A:                      /* switch 3 */
                    case 0x2B:                      /* switch 3 */
                    case 0x2C:                      /* switch 3 */
                    case 0x2D:                      /* switch 3 */
                        return &D_80B58980;
                    case 0x3:                       /* switch 3 */
                        arg0->unk_398 = (s32 (*)(Actor*, PlayState*)) func_80B54D18;
                        return &D_80B58AF4;
                    case 0x12:                      /* switch 3 */
                        if (gSaveContext.save.day >= 2) {
                            return &D_80B58A3C;
                        }
                        return &D_80B5885C;
                    case 0x13:                      /* switch 3 */
                    case 0x2F:                      /* switch 3 */
                        return &D_80B58938;
                    case 0x16:                      /* switch 3 */
                        return &D_80B58988;
                    case 0x17:                      /* switch 3 */
                        return &D_80B589FC;
                    case 0x30:                      /* switch 3 */
                        return &D_80B58944;
                    case 0x31:                      /* switch 3 */
                        if (temp_a0 == 4) {
                            return &D_80B58B88;
                        }
                        return &D_80B589FC;
                    case 0x34:                      /* switch 3 */
                    case 0x35:                      /* switch 3 */
                        return &D_80B58994;
                    default:                        /* switch 3 */
                        return NULL;
                }
            }
            break;
    }
}

s32 func_80B55180(EnAn* this, PlayState* play) {
    s32 sp1C;
    s32 var_v1;
    u8 temp_v1;

    var_v1 = 0;
    if (this->unk_360 & 7) {
        sp1C = 0;
        var_v1 = sp1C;
        if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
            SubS_SetOfferMode(&this->unk_360, 0U, 7U);
            this->unk_3C4 = 0;
            this->unk_394 = 0;
            this->unk_398 = NULL;
            this->actor.child = this->unk_218;
            temp_v1 = this->unk_200;
            this->unk_204 = func_80B54DF4(this, play);
            if ((temp_v1 == 1) || (temp_v1 == 3) || (temp_v1 == 0x12) || (temp_v1 == 0x13) || (temp_v1 == 0x17) || (temp_v1 == 0x16) || (temp_v1 == 0x28) || (temp_v1 == 0x2A) || (temp_v1 == 0x2B) || (temp_v1 == 0x2C) || (temp_v1 == 0x2D) || (temp_v1 == 0x2F) || (temp_v1 == 0x30) || (temp_v1 == 0x31) || (temp_v1 == 0x34) || (temp_v1 == 0x35)) {
                this->unk_360 |= 0x20;
            }
            if ((this->unk_200 == 3) && (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20)) {
                this->unk_360 &= 0xFFDF;
            }
            this->actionFunc = func_80B57A44;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 func_80B552E4(EnAn* this, PlayState* play) {
    s32 var_v1;
    u16 temp_v0;

    temp_v0 = play->csCtx.scriptIndex;
    var_v1 = 0;
    if ((play->csCtx.state != 0) && (play->sceneId == 0x61) && (gSaveContext.sceneLayer == 0) && ((temp_v0 == 0) || (temp_v0 == 1))) {
        if (this->unk_3B0 == 0) {
            this->unk_38A = 0;
            this->unk_38C = 0;
            this->unk_360 |= 0x300;
            this->unk_38E = 8;
            this->unk_364 = -1;
            this->unk_3B0 = 1;
            this->unk_3B4 = 0;
        }
        var_v1 = 1;
    } else if (this->unk_3B0 != 0) {
        this->unk_3B0 = 0;
        this->unk_3B4 = 0;
        this->unk_3C0 = 1;
        this->actionFunc = func_80B578F8;
        this->actor.room = play->roomCtx.curRoom.num;
    }
    return var_v1;
}

void func_80B553AC(void* arg0) {
    Vec3f sp40;
    Vec3f sp34;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 var_v1;
    s16 var_v1_2;
    void* temp_v0_2;

    Math_Vec3f_Copy(&sp40, arg0->unk_218 + 0x24);
    Math_Vec3f_Copy(&sp34, arg0 + 0x24);
    Math_ApproachS(arg0 + 0x37E, (s16) (Math_Vec3f_Yaw(&sp34, &sp40) - arg0->unk_BE), 4, 0x2AA8);
    temp_v0 = arg0->unk_37E;
    if (temp_v0 < -0x1FFE) {
        arg0->unk_37E = -0x1FFE;
    } else {
        var_v1 = temp_v0;
        if (temp_v0 >= 0x1FFF) {
            var_v1 = 0x1FFE;
        }
        arg0->unk_37E = var_v1;
    }
    Math_Vec3f_Copy(&sp34, arg0 + 0x3C);
    temp_v0_2 = arg0->unk_218;
    if (temp_v0_2->unk_0 == 0) {
        sp40.y = temp_v0_2->unk_C44 + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, temp_v0_2 + 0x3C);
    }
    Math_ApproachS(arg0 + 0x37C, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    temp_v0_3 = arg0->unk_37C;
    if (temp_v0_3 < -0x1554) {
        arg0->unk_37C = -0x1554;
        return;
    }
    var_v1_2 = temp_v0_3;
    if (temp_v0_3 >= 0x1555) {
        var_v1_2 = 0x1554;
    }
    arg0->unk_37C = var_v1_2;
}

void func_80B554E8(EnAn* this) {
    Actor* temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 var_v1;
    s16 var_v1_2;
    u16 temp_t2;
    u16 temp_v0_3;

    if (this->unk_360 & 0x20) {
        temp_v0 = this->unk_218;
        if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
            temp_v0_2 = this->unk_388;
            if (temp_v0_2 == 0) {
                var_v1 = 0;
            } else {
                this->unk_388 = temp_v0_2 - 1;
                var_v1 = this->unk_388;
            }
            if (var_v1 == 0) {
                func_80B553AC();
                temp_t2 = this->unk_360 & 0xFDFF;
                this->unk_360 = temp_t2;
                this->unk_360 = temp_t2 | 0x80;
                return;
            }
            goto block_8;
        }
    }
block_8:
    temp_v0_3 = this->unk_360;
    if (temp_v0_3 & 0x80) {
        this->unk_360 = temp_v0_3 & 0xFF7F;
        this->unk_37C = 0;
        this->unk_37E = 0;
        this->unk_388 = 0x14;
        return;
    }
    temp_v0_4 = this->unk_388;
    if (temp_v0_4 == 0) {
        var_v1_2 = 0;
    } else {
        this->unk_388 = temp_v0_4 - 1;
        var_v1_2 = this->unk_388;
    }
    if (var_v1_2 == 0) {
        this->unk_360 |= 0x200;
    }
}

? func_80B555C8(EnAn* arg0, PlayState* arg1) {
    s32 var_v0;
    u8 temp_t6;

    temp_t6 = arg0->unk_200;
    switch (temp_t6) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x17:
            func_80B53CE8(arg0, arg1, 1);
            break;
        case 0x16:
            func_80B53CE8(arg0, arg1, 0x17);
            arg0->unk_360 |= 0x2000;
            break;
        case 0xE:
            func_80B53CE8(arg0, arg1, 0xC);
            break;
        case 0x15:
            func_80B53CE8(arg0, arg1, 0xF);
            break;
        case 0x2F:
        case 0x31:
            func_80B53CE8(arg0, arg1, 7);
            break;
        case 0x34:
        case 0x35:
            func_80B53CE8(arg0, arg1, 0x16);
            arg0->unk_360 |= 0x2000;
            break;
        default:
            var_v0 = arg0->unk_39C;
            if (var_v0 == 0xF) {
                func_80B53CE8(arg0, arg1, 0x10);
                var_v0 = arg0->unk_39C;
            }
            if (var_v0 == 0x11) {
                func_80B53CE8(arg0, arg1, 0x12);
                var_v0 = arg0->unk_39C;
            }
            if ((var_v0 == 1) || (var_v0 == 2)) {
                func_80B53CE8(arg0, arg1, 8);
            }
            break;
    }
    return 0;
}

void func_80B556F8(EnAn* arg0, PlayState* arg1) {
    s16 temp_v0;
    u16 temp_t4;
    u16 temp_t8;

    temp_v0 = arg0->unk_396;
    if (temp_v0 == 0) {
        func_80B53CE8(arg0, arg1, 6);
        temp_t8 = arg0->unk_360 & 0xFFDF;
        arg0->unk_360 = temp_t8;
        arg0->unk_360 = temp_t8 | 0x200;
        arg0->unk_396 += 1;
        return;
    }
    if ((temp_v0 == 1) && (Animation_OnFrame(&arg0->unk_144, arg0->unk_144.endFrame) != 0)) {
        func_80B53CE8(arg0, arg1, 2);
        temp_t4 = arg0->unk_360 & 0xFDFF;
        arg0->unk_360 = temp_t4;
        arg0->unk_360 = temp_t4 | 0x20;
        arg0->unk_396 += 1;
    }
}

void func_80B557AC(EnAn* arg0, PlayState* arg1) {
    s16 temp_v0;
    u16 temp_t4;
    u16 temp_t8;

    temp_v0 = arg0->unk_396;
    if (temp_v0 == 0) {
        func_80B53CE8(arg0, arg1, 3);
        temp_t8 = arg0->unk_360 & 0xFFDF;
        arg0->unk_360 = temp_t8;
        arg0->unk_360 = temp_t8 | 0x200;
        arg0->unk_396 += 1;
        return;
    }
    if ((temp_v0 == 1) && (Animation_OnFrame(&arg0->unk_144, arg0->unk_144.endFrame) != 0)) {
        func_80B53CE8(arg0, arg1, 2);
        temp_t4 = arg0->unk_360 & 0xFDFF;
        arg0->unk_360 = temp_t4;
        arg0->unk_360 = temp_t4 | 0x20;
        arg0->unk_396 += 1;
    }
}

void func_80B55860(EnAn* arg0, PlayState* arg1) {
    s16 temp_v0;
    u16 temp_t4;
    u16 temp_t8;

    temp_v0 = arg0->unk_396;
    if (temp_v0 == 0) {
        func_80B53CE8(arg0, arg1, 4);
        temp_t8 = arg0->unk_360 | 0x200;
        arg0->unk_360 = temp_t8;
        arg0->unk_360 = temp_t8 & 0xFFDF;
        arg0->unk_396 += 1;
        return;
    }
    if ((temp_v0 == 1) && (Animation_OnFrame(&arg0->unk_144, arg0->unk_144.endFrame) != 0)) {
        func_80B53CE8(arg0, arg1, 2);
        temp_t4 = arg0->unk_360 & 0xFDFF;
        arg0->unk_360 = temp_t4;
        arg0->unk_360 = temp_t4 | 0x20;
        arg0->unk_396 += 1;
    }
}

void func_80B55914(EnAn* this, PlayState* play) {
    u16 sp22;
    s32 sp18;
    s32 var_v0;
    u16 temp_t3;
    u16 temp_v0;
    void (*temp_v0_2)(EnAn*, PlayState*);

    sp22 = play->msgCtx.currentTextId;
    if (play->actorCtx.actorLists[2].first->unk_A6C & 0x40) {
        this->unk_360 |= 0x400;
        sp18 = (s32) sp22;
        if (sp22 != this->unk_362) {
            if ((s32) sp22 >= 0x28F9) {
                if (sp22 != 0x295E) {
                    goto block_23;
                }
                goto block_20;
            }
            switch (sp18) {                         /* switch 3; irregular */
                case 0x28E5:                        /* switch 3 */
                    func_80B53CE8(this, play, 5);
                    this->unk_360 &= 0xDFFF;
                    break;
                case 0x28BA:                        /* switch 3 */
                case 0x28D1:                        /* switch 3 */
                    func_80B53CE8(this, play, 5);
                    break;
                case 0x28AF:                        /* switch 3 */
                case 0x28C1:                        /* switch 3 */
                    func_80B53CE8(this, play, 1);
                    break;
                case 0x28BC:                        /* switch 3 */
                    func_80B53CE8(this, play, 2);
                    break;
                case 0x28C6:                        /* switch 3 */
                    func_80B53CE8(this, play, 0xF);
                    break;
                case 0x28F5:                        /* switch 3 */
                    func_80B53CE8(this, play, 0xA);
                    break;
                case 0x28F7:                        /* switch 3 */
                case 0x28F8:                        /* switch 3 */
                    func_80B53CE8(this, play, 0x15);
                    break;
                case 0x28EB:                        /* switch 3 */
                    if (this->unk_39C != 0x14) {
                        temp_t3 = this->unk_360 & 0xBFDF;
                        this->unk_360 = temp_t3;
                        this->unk_360 = temp_t3 | 0x200;
                        func_80B53CE8(this, play, 0x14);
                    }
                    break;
                case 0x28A4:                        /* switch 3 */
                case 0x28A9:                        /* switch 3 */
                case 0x28BE:                        /* switch 3 */
                case 0x28C0:                        /* switch 3 */
block_20:
                    this->unk_18C = func_80B556F8;
                    this->unk_396 = 0;
                    break;
                case 0x28E6:                        /* switch 3 */
                    this->unk_360 &= 0xDFFF;
                    this->unk_18C = func_80B55860;
                    this->unk_396 = 0;
                    break;
                case 0x1885:                        /* switch 3 */
                case 0x28A0:                        /* switch 3 */
                case 0x28A3:                        /* switch 3 */
                case 0x28A5:                        /* switch 3 */
                case 0x28B1:                        /* switch 3 */
                case 0x28D2:                        /* switch 3 */
                case 0x28D9:                        /* switch 3 */
                case 0x28DC:                        /* switch 3 */
                case 0x28DE:                        /* switch 3 */
                    this->unk_18C = func_80B557AC;
                    this->unk_396 = 0;
                    break;
                case 0x28A1:                        /* switch 3 */
                case 0x28A2:                        /* switch 3 */
                case 0x28A6:                        /* switch 3 */
                case 0x28A7:                        /* switch 3 */
                case 0x28A8:                        /* switch 3 */
                case 0x28AA:                        /* switch 3 */
                case 0x28AB:                        /* switch 3 */
                case 0x28AC:                        /* switch 3 */
                case 0x28AD:                        /* switch 3 */
                case 0x28AE:                        /* switch 3 */
                case 0x28B0:                        /* switch 3 */
                case 0x28B2:                        /* switch 3 */
                case 0x28B3:                        /* switch 3 */
                case 0x28B4:                        /* switch 3 */
                case 0x28B5:                        /* switch 3 */
                case 0x28B6:                        /* switch 3 */
                case 0x28B7:                        /* switch 3 */
                case 0x28B8:                        /* switch 3 */
                case 0x28B9:                        /* switch 3 */
                case 0x28BB:                        /* switch 3 */
                case 0x28BD:                        /* switch 3 */
                case 0x28BF:                        /* switch 3 */
                case 0x28C2:                        /* switch 3 */
                case 0x28C3:                        /* switch 3 */
                case 0x28C4:                        /* switch 3 */
                case 0x28C5:                        /* switch 3 */
                case 0x28C7:                        /* switch 3 */
                case 0x28C8:                        /* switch 3 */
                case 0x28C9:                        /* switch 3 */
                case 0x28CA:                        /* switch 3 */
                case 0x28CB:                        /* switch 3 */
                case 0x28CC:                        /* switch 3 */
                case 0x28CD:                        /* switch 3 */
                case 0x28CE:                        /* switch 3 */
                case 0x28CF:                        /* switch 3 */
                case 0x28D0:                        /* switch 3 */
                case 0x28D3:                        /* switch 3 */
                case 0x28D4:                        /* switch 3 */
                case 0x28D5:                        /* switch 3 */
                case 0x28D6:                        /* switch 3 */
                case 0x28D7:                        /* switch 3 */
                case 0x28D8:                        /* switch 3 */
                case 0x28DA:                        /* switch 3 */
                case 0x28DB:                        /* switch 3 */
                case 0x28DD:                        /* switch 3 */
                case 0x28DF:                        /* switch 3 */
                case 0x28E0:                        /* switch 3 */
                case 0x28E1:                        /* switch 3 */
                case 0x28E2:                        /* switch 3 */
                case 0x28E3:                        /* switch 3 */
                case 0x28E4:                        /* switch 3 */
                case 0x28E7:                        /* switch 3 */
                case 0x28E8:                        /* switch 3 */
                case 0x28E9:                        /* switch 3 */
                case 0x28EA:                        /* switch 3 */
                case 0x28EC:                        /* switch 3 */
                case 0x28ED:                        /* switch 3 */
                case 0x28EE:                        /* switch 3 */
                case 0x28EF:                        /* switch 3 */
                case 0x28F0:                        /* switch 3 */
                case 0x28F1:                        /* switch 3 */
                case 0x28F2:                        /* switch 3 */
                case 0x28F3:                        /* switch 3 */
                case 0x28F4:                        /* switch 3 */
                case 0x28F6:                        /* switch 3 */
block_23:
                    var_v0 = this->unk_39C;
                    if (var_v0 == 0x10) {
                        func_80B53CE8(this, play, 0xF);
                        var_v0 = this->unk_39C;
                    }
                    if (var_v0 == 0x12) {
                        func_80B53CE8(this, play, 0x11);
                        var_v0 = this->unk_39C;
                    }
                    if ((var_v0 == 0x16) || (var_v0 == 0x17)) {
                        func_80B53CE8(this, play, 0x15);
                        var_v0 = this->unk_39C;
                    }
                    if ((var_v0 == 7) || (var_v0 == (s32) 8)) {
                        func_80B53CE8(this, play, 2);
                    }
                    break;
            }
            switch (sp18) {                         /* switch 4; irregular */
                case 0x28F5:                        /* switch 4 */
                    this->unk_38A = 0;
                    /* fallthrough */
                case 0x28A5:                        /* switch 4 */
                case 0x28AA:                        /* switch 4 */
                case 0x28F8:                        /* switch 4 */
                    this->unk_38C = 0;
block_50:
                    this->unk_38E = 8;
                    break;
                case 0x1885:                        /* switch 4 */
                case 0x28A0:                        /* switch 4 */
                case 0x28A6:                        /* switch 4 */
                case 0x28AF:                        /* switch 4 */
                case 0x28C1:                        /* switch 4 */
                    this->unk_38C = 3;
                    goto block_50;
                case 0x28A2:                        /* switch 4 */
                case 0x28B3:                        /* switch 4 */
                case 0x28B6:                        /* switch 4 */
                case 0x28BA:                        /* switch 4 */
                case 0x28BE:                        /* switch 4 */
                case 0x28CE:                        /* switch 4 */
                case 0x28D0:                        /* switch 4 */
                case 0x28D6:                        /* switch 4 */
                case 0x28E5:                        /* switch 4 */
                case 0x28E7:                        /* switch 4 */
                case 0x28ED:                        /* switch 4 */
                    this->unk_38C = 1;
                    goto block_50;
                case 0x28AD:                        /* switch 4 */
                    this->unk_38C = 8;
                    goto block_50;
                case 0x28C0:                        /* switch 4 */
                case 0x28D7:                        /* switch 4 */
                case 0x28DE:                        /* switch 4 */
                    this->unk_38C = 2;
                    goto block_50;
                case 0x28E6:                        /* switch 4 */
                case 0x28F7:                        /* switch 4 */
                    this->unk_38C = 6;
                    goto block_50;
                case 0x28A3:                        /* switch 4 */
                case 0x28B1:                        /* switch 4 */
                case 0x28B8:                        /* switch 4 */
                case 0x28C6:                        /* switch 4 */
                case 0x28CA:                        /* switch 4 */
                case 0x28CC:                        /* switch 4 */
                case 0x28D5:                        /* switch 4 */
                case 0x28E2:                        /* switch 4 */
                case 0x28E3:                        /* switch 4 */
                case 0x28E4:                        /* switch 4 */
                    this->unk_38C = 4;
                    goto block_50;
                case 0x28EC:                        /* switch 4 */
                    this->unk_38A = 5;
                    /* fallthrough */
                case 0x28DC:                        /* switch 4 */
                case 0x28EB:                        /* switch 4 */
                case 0x28F2:                        /* switch 4 */
                case 0x28F9:                        /* switch 4 */
                    this->unk_38C = 5;
                    goto block_50;
                case 0x28F6:                        /* switch 4 */
                    this->unk_38C = 9;
                    goto block_50;
                case 0x28A4:                        /* switch 4 */
                case 0x28A9:                        /* switch 4 */
                    this->unk_38C = 7;
                    goto block_50;
            }
        }
        this->unk_362 = sp22;
    } else {
        temp_v0 = this->unk_360;
        if (temp_v0 & 0x400) {
            this->unk_18C = NULL;
            this->unk_362 = 0;
            this->unk_360 = temp_v0 & 0xFBFF;
            this->unk_38E = 4;
            this->unk_38C = this->unk_38A;
            func_80B555C8((EnAn* ) play);
        }
    }
    temp_v0_2 = this->unk_18C;
    if (temp_v0_2 != NULL) {
        temp_v0_2(this, play);
    }
}

Actor* func_80B55D20(EnAn* arg0, PlayState* arg1) {
    Actor* var_v0;
    Actor* var_v1;
    u8 temp_v0;

    temp_v0 = arg0->unk_200;
    switch (temp_v0) {                              /* irregular */
        default:
            var_v1 = arg1->actorCtx.actorLists[2].first;
            break;
        case 0x15:
            var_v0 = func_80B539CC((EnAn* )4, (PlayState* )0x243);
block_7:
            var_v1 = var_v0;
            break;
        case 0x10:
            var_v0 = func_80B539CC((EnAn* )4, (PlayState* )0x1D5);
            goto block_7;
        case 0x11:
            var_v0 = func_80B539CC((EnAn* )4, (PlayState* )0x276);
            goto block_7;
    }
    return var_v1;
}

s32 func_80B55D98(EnAn* arg0, PlayState* arg1, u8* arg2, u8 arg3, s16 arg4) {
    u8 sp4F;
    void* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* sp2C;
    s32 sp24;
    Actor* temp_v0;
    Actor* var_v1;
    Path* temp_v0_2;
    s32 temp_a2;
    void* temp_v0_3;

    sp24 = 0;
    sp4F = (u8) arg0->actor.params;
    temp_v0 = func_80B539CC(arg0, arg1, arg3, arg4);
    arg0->unk_1DC = NULL;
    var_v1 = temp_v0;
    temp_a2 = *(&D_80B58618 + (*arg2 * 4));
    if (temp_a2 >= 0) {
        sp2C = temp_v0;
        var_v1 = sp2C;
        arg0->unk_1DC = SubS_GetAdditionalPath(arg1, sp4F, temp_a2);
    }
    if ((var_v1 != NULL) && (var_v1->update != NULL)) {
        temp_v0_2 = arg0->unk_1DC;
        if (temp_v0_2 != NULL) {
            temp_v0_3 = Lib_SegmentedToVirtual(temp_v0_2->points);
            sp48 = temp_v0_3;
            Math_Vec3s_ToVec3f(&sp3C, ((arg0->unk_1DC->count * 6) + temp_v0_3) - 0xC);
            Math_Vec3s_ToVec3f(&sp30, ((arg0->unk_1DC->count * 6) + sp48) - 6);
            arg0->actor.shape.shadowDraw = NULL;
            arg0->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&arg0->actor.world.pos, &sp30);
            sp24 = 1;
        }
    }
    return sp24;
}

s32 func_80B55ECC(Actor* arg0) {
    s32 sp1C;
    f32 var_fv0;
    s16 temp_v0;
    s16 var_v1;
    s32 var_t0;

    if (arg0->unk_3BC != 0) {
        var_fv0 = 150.0f;
    } else {
        var_fv0 = 100.0f;
    }
    sp1C = 0;
    var_t0 = 0;
    if (Actor_IsFacingAndNearPlayer(arg0, var_fv0, 0x2800) != 0) {
        var_t0 = 1;
    }
    temp_v0 = arg0->unk_386;
    if (temp_v0 == 0) {
        var_v1 = 0;
    } else {
        arg0->unk_386 = (s16) (temp_v0 - 1);
        var_v1 = arg0->unk_386;
    }
    if (var_v1 == 0) {
        arg0->unk_3BC = (s32) (arg0->unk_3BC ^ 1);
        sp1C = var_t0;
        arg0->unk_386 = Rand_S16Offset(0x3C, 0x3C);
    }
    return var_t0;
}

s32 func_80B55F8C(PlayState* arg0) {
    Actor* sp1C;
    s32 sp18;
    s32 var_v1;

    sp18 = 0;
    sp1C = arg0->actorCtx.actorLists[2].first;
    var_v1 = sp18;
    if ((Player_GetMask(arg0) == 2) && (gSaveContext.save.saveInfo.weekEventReg[0x32] & 8)) {
        goto block_5;
    }
    if ((sp1C->unk_14B == 4) && (gSaveContext.save.saveInfo.weekEventReg[0x32] & 8)) {
block_5:
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80B5600C(EnAn* arg0, PlayState* arg1) {
    s32 sp2C;
    s32 var_v1;
    u16 temp_t9;

    sp2C = 0;
    var_v1 = sp2C;
    if (func_80B55D98(arg0, arg1, (u8* )4, (u8) 0x1D5) != 0) {
        func_80B53CE8(arg0, arg1, 1);
        SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
        var_v1 = 1;
        temp_t9 = arg0->unk_360 | 0x120;
        arg0->unk_360 = temp_t9;
        arg0->unk_360 = temp_t9 | 0x200;
    }
    return var_v1;
}

s32 func_80B56094(EnAn* arg0, PlayState* arg1) {
    s32 sp2C;
    s32 var_v1;
    u16 temp_t9;

    sp2C = 0;
    var_v1 = sp2C;
    if (func_80B55D98(arg0, arg1, (u8* )4, (u8) 0x276) != 0) {
        func_80B53CE8(arg0, arg1, 1);
        SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
        var_v1 = 1;
        temp_t9 = arg0->unk_360 | 0x120;
        arg0->unk_360 = temp_t9;
        arg0->unk_360 = temp_t9 | 0x200;
    }
    return var_v1;
}

s32 func_80B5611C(EnAn* arg0, PlayState* arg1) {
    s32 sp2C;
    s32 var_v1;
    u16 temp_t9;

    sp2C = 0;
    var_v1 = sp2C;
    if (func_80B55D98(arg0, arg1, (u8* )4, (u8) 0x243) != 0) {
        func_80B53CE8(arg0, arg1, 0xF);
        SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
        var_v1 = 1;
        temp_t9 = arg0->unk_360 | 0x120;
        arg0->unk_360 = temp_t9;
        arg0->unk_360 = temp_t9 | 0xA00;
    }
    return var_v1;
}

s32 func_80B561A4(EnAn* arg0, PlayState* arg1, void* arg2) {
    u16 sp56;
    u8 sp55;
    struct EnDoor* sp50;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s32 sp2C;
    Path* temp_v0;
    Vec3s* temp_v0_2;
    s16 temp_v0_3;
    s16 var_v1;
    s32 temp_a2;
    u8 temp_v0_4;

    sp56 = gSaveContext.save.time - 0x3FFC;
    sp2C = 0;
    sp55 = (u8) arg0->actor.params;
    arg0->unk_1DC = NULL;
    sp50 = func_80B53B3C(arg1, arg2->unk_0);
    temp_a2 = *(&D_80B58618 + (arg2->unk_0 * 4));
    if (temp_a2 >= 0) {
        arg0->unk_1DC = SubS_GetAdditionalPath(arg1, sp55, temp_a2);
    }
    if ((sp50 != NULL) && (sp50->unk_138 != 0)) {
        temp_v0 = arg0->unk_1DC;
        if (temp_v0 != NULL) {
            temp_v0_2 = Lib_SegmentedToVirtual(temp_v0->points);
            sp4C = temp_v0_2;
            Math_Vec3s_ToVec3f(&sp40, temp_v0_2);
            Math_Vec3s_ToVec3f(&sp34, sp4C + 6);
            Math_Vec3f_Copy(arg0 + 0x228, &sp40);
            Math_Vec3f_Copy(arg0 + 0x234, &sp34);
            arg0->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(arg0 + 0x24, &sp40);
            temp_v0_3 = arg0->actor.world.rot.y - sp50->unk_BE;
            var_v1 = temp_v0_3;
            if (temp_v0_3 < 0) {
                var_v1 = -temp_v0_3;
            }
            if (var_v1 < 0x4001) {
                arg0->unk_215 = -0x4B;
            } else {
                arg0->unk_215 = 0x4B;
            }
            arg0->unk_378 = arg2->unk_8 - arg2->unk_4;
            arg0->unk_37A = sp56 - arg2->unk_4;
            temp_v0_4 = arg2->unk_0;
            switch (temp_v0_4) {                    /* switch 1 */
                case 0x1B:                          /* switch 1 */
                case 0x1C:                          /* switch 1 */
                case 0x20:                          /* switch 1 */
                case 0x21:                          /* switch 1 */
                case 0x22:                          /* switch 1 */
                case 0x23:                          /* switch 1 */
                case 0x25:                          /* switch 1 */
                case 0x26:                          /* switch 1 */
                    arg0->unk_38A = 2;
                    arg0->unk_38C = 2;
                    arg0->unk_38E = 8;
                    break;
            }
            switch (arg2->unk_0) {                  /* switch 2 */
                case 0x1A:                          /* switch 2 */
                case 0x1B:                          /* switch 2 */
                case 0x1C:                          /* switch 2 */
                    arg0->unk_360 |= 0x900;
                    func_80B53CE8(arg0, arg1, 0x10);
                    break;
                case 0x24:                          /* switch 2 */
                case 0x27:                          /* switch 2 */
                    arg0->unk_360 |= 0x2100;
                    func_80B53CE8(arg0, arg1, 0x16);
                    break;
                default:                            /* switch 2 */
                    arg0->unk_360 |= 0x100;
                    func_80B53CE8(arg0, arg1, 7);
                    break;
            }
            arg0->actor.flags &= ~1;
            arg0->unk_360 |= 0x200;
            arg0->actor.gravity = 0.0f;
            sp2C = 1;
        }
    }
    return sp2C;
}

s32 func_80B56418(EnAn* arg0, PlayState* arg1, void* arg2) {
    u16 sp2E;
    u8 sp2B;
    s32 sp20;
    Path* var_v0;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_v0_2;
    s32 var_v1;
    u16 temp_t0;
    u16 temp_t3;
    u16 temp_t7;
    u16 temp_t8;
    u16 temp_t9;
    u16 var_v1_2;
    u8 temp_v0;
    u8 var_a1;

    sp2B = arg0->actor.params & 0xFF;
    arg0->unk_1DC = NULL;
    temp_t0 = (gSaveContext.save.time - 0x3FFC) & 0xFFFF;
    var_v1 = 0;
    temp_a3 = *(&D_80B58618 + (arg2->unk_0 * 4));
    if (temp_a3 >= 0) {
        sp20 = 0;
        sp2E = temp_t0;
        var_v1 = 0;
        arg0->unk_1DC = SubS_GetAdditionalPath(arg1, sp2B, temp_a3);
    }
    var_v0 = arg0->unk_1DC;
    if ((var_v0 != NULL) && ((s32) var_v0->count < 3)) {
        arg0->unk_1DC = NULL;
        var_v0 = NULL;
    }
    if (var_v0 != NULL) {
        temp_v0 = arg0->unk_200;
        if (((s32) temp_v0 < 0x28) && (temp_v0 != 0) && (arg0->unk_384 >= 0)) {
            var_v1_2 = temp_t0 & 0xFFFF;
        } else {
            var_v1_2 = arg2->unk_6;
        }
        temp_v0_2 = arg2->unk_8;
        if (temp_v0_2 < (s32) var_v1_2) {
            arg0->unk_1F0 = (var_v1_2 - temp_v0_2) + 0xFFFF;
        } else {
            arg0->unk_1F0 = temp_v0_2 - var_v1_2;
        }
        arg0->unk_1FC = temp_t0 - var_v1_2;
        temp_lo = (s32) arg0->unk_1F0 / (s32) ((arg0->unk_1DC->count - 2) & 0xFFFF);
        arg0->unk_1F4 = temp_lo;
        temp_t7 = arg0->unk_360 & ~8;
        arg0->unk_360 = temp_t7;
        arg0->unk_1F8 = ((s32) arg0->unk_1FC / temp_lo) + 2;
        arg0->unk_360 = temp_t7 & 0xFFFF & ~0x10;
        var_a1 = arg2->unk_0;
        switch (var_a1) {                           /* switch 1 */
            case 0x2C:                              /* switch 1 */
            case 0x2D:                              /* switch 1 */
            case 0x32:                              /* switch 1 */
            case 0x33:                              /* switch 1 */
            case 0x36:                              /* switch 1 */
            case 0x37:                              /* switch 1 */
            case 0x38:                              /* switch 1 */
            case 0x39:                              /* switch 1 */
            case 0x3A:                              /* switch 1 */
            case 0x3B:                              /* switch 1 */
            case 0x3C:                              /* switch 1 */
            case 0x3D:                              /* switch 1 */
            case 0x3E:                              /* switch 1 */
            case 0x3F:                              /* switch 1 */
                arg0->unk_38A = 2;
                arg0->unk_38C = 2;
                arg0->unk_38E = 8;
                var_a1 = arg2->unk_0;
                break;
        }
        switch (var_a1) {                           /* switch 2 */
            case 0x2A:                              /* switch 2 */
            case 0x2B:                              /* switch 2 */
                SubS_SetOfferMode(arg0 + 0x360, 3U, 7U);
                /* fallthrough */
            case 0x2C:                              /* switch 2 */
            case 0x2D:                              /* switch 2 */
                func_80B53CE8(arg0, arg1, 0x10);
                temp_t8 = arg0->unk_360 | 0x300;
                arg0->unk_360 = temp_t8;
                arg0->unk_360 = temp_t8 | 0x800;
                break;
            case 0x34:                              /* switch 2 */
            case 0x35:                              /* switch 2 */
                func_80B53CE8(arg0, arg1, 0x16);
                SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
                temp_t3 = arg0->unk_360 | 0x300;
                arg0->unk_360 = temp_t3;
                arg0->unk_360 = temp_t3 | 0x2000;
                break;
            case 0x32:                              /* switch 2 */
            case 0x33:                              /* switch 2 */
                func_80B53CE8(arg0, arg1, 7);
                arg0->unk_360 |= 0x300;
                break;
            case 0x36:                              /* switch 2 */
            case 0x37:                              /* switch 2 */
            case 0x38:                              /* switch 2 */
            case 0x39:                              /* switch 2 */
            case 0x3A:                              /* switch 2 */
            case 0x3B:                              /* switch 2 */
            case 0x3C:                              /* switch 2 */
            case 0x3D:                              /* switch 2 */
            case 0x3E:                              /* switch 2 */
            case 0x3F:                              /* switch 2 */
                func_80B53CE8(arg0, arg1, 0x12);
                temp_t9 = arg0->unk_360 | 0x300;
                arg0->unk_360 = temp_t9;
                arg0->unk_360 = temp_t9 | 0x1000;
                break;
            case 0x28:                              /* switch 2 */
            case 0x2F:                              /* switch 2 */
            case 0x30:                              /* switch 2 */
            case 0x31:                              /* switch 2 */
                SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
                arg0->unk_360 |= 0x300;
                /* fallthrough */
            default:                                /* switch 2 */
                func_80B53CE8(arg0, arg1, 7);
                break;
        }
        var_v1 = 1;
        arg0->actor.gravity = -1.0f;
    }
    return var_v1;
}

s32 func_80B56744(EnAn* arg0, PlayState* arg1, u8* arg2) {
    u8 sp4F;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 sp28;
    Path* temp_v0;
    Vec3s* temp_v0_2;
    s32 temp_a3;
    s32 var_v1;
    u16 temp_t6;

    var_v1 = 0;
    sp4F = (u8) arg0->actor.params;
    arg0->unk_1DC = NULL;
    temp_a3 = *(&D_80B58618 + (*arg2 * 4));
    if (temp_a3 >= 0) {
        sp28 = 0;
        var_v1 = sp28;
        arg0->unk_1DC = SubS_GetAdditionalPath(arg1, sp4F, temp_a3);
    }
    temp_v0 = arg0->unk_1DC;
    if ((temp_v0 != NULL) && ((s32) temp_v0->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(temp_v0->points);
        sp30 = temp_v0_2;
        Math_Vec3s_ToVec3f(&sp40, temp_v0_2);
        Math_Vec3s_ToVec3f(&sp34, sp30 + 6);
        arg0->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(arg0 + 0xBC, arg0 + 0x30);
        Math_Vec3f_Copy(arg0 + 0x24, &sp40);
        Math_Vec3f_Copy(arg0 + 0x108, &sp40);
        if (*arg2 == 0x16) {
            func_80B53CE8(arg0, arg1, 0x17);
            SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
            temp_t6 = arg0->unk_360 | 0x300;
            arg0->unk_360 = temp_t6;
            arg0->unk_360 = temp_t6 | 0x2000;
        }
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80B56880(EnAn* arg0, PlayState* arg1, u8* arg2) {
    u8 sp4F;
    Vec3f sp40;
    Vec3f sp34;
    void* sp30;
    s32 sp28;
    Vec3s* sp24;
    Path* temp_v0;
    Vec3s* temp_a1;
    s32 temp_a3;
    s32 var_v1;
    u16 temp_t0_2;
    u16 temp_t3;
    u8 temp_t0;
    void* temp_v0_2;

    var_v1 = 0;
    sp4F = (u8) arg0->actor.params;
    arg0->unk_1DC = NULL;
    temp_a3 = *(&D_80B58618 + (*arg2 * 4));
    if (temp_a3 >= 0) {
        sp28 = 0;
        var_v1 = sp28;
        arg0->unk_1DC = SubS_GetAdditionalPath(arg1, sp4F, temp_a3);
    }
    temp_v0 = arg0->unk_1DC;
    if ((temp_v0 != NULL) && ((s32) temp_v0->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(temp_v0->points);
        sp30 = temp_v0_2;
        Math_Vec3s_ToVec3f(&sp40, ((arg0->unk_1DC->count * 6) + temp_v0_2) - 6);
        Math_Vec3s_ToVec3f(&sp34, ((arg0->unk_1DC->count * 6) + sp30) - 0xC);
        arg0->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);
        temp_a1 = arg0 + 0x30;
        sp24 = temp_a1;
        Math_Vec3s_Copy(arg0 + 0xBC, temp_a1);
        Math_Vec3s_Copy(arg0 + 0x14, temp_a1);
        Math_Vec3f_Copy(arg0 + 0x24, &sp40);
        Math_Vec3f_Copy(arg0 + 0x108, &sp40);
        temp_t0 = *arg2;
        switch (temp_t0) {
            case 0x13:
                arg0->actor.world.rot.y += 0x7FF8;
                /* fallthrough */
            case 0x12:
            case 0x17:
                func_80B53CE8(arg0, arg1, 1);
                SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
                arg0->unk_37A = 0;
                arg0->unk_360 |= 0x300;
                if (*arg2 == 0x12) {
                    arg0->unk_374 = 70.0f;
                }
                break;
            case 0x3:
                temp_t0_2 = arg0->unk_360 | 0x300;
                arg0->unk_360 = temp_t0_2;
                arg0->unk_360 = temp_t0_2 | 0x1000;
                if (gSaveContext.save.saveInfo.weekEventReg[0x37] & 0x20) {
                    func_80B53CE8(arg0, arg1, 0x14);
                    arg0->actor.world.rot.y += 0x7FF8;
                    arg0->unk_360 |= 0x40;
                    arg0->unk_37A = 4;
                    arg0->actor.shape.rot.y = arg0->actor.world.rot.y;
                } else {
                    func_80B53CE8(arg0, arg1, 0x12);
                    arg0->unk_37A = 0;
                }
                arg0->unk_38A = 2;
                arg0->unk_38C = 2;
                arg0->unk_38E = 8;
                break;
            case 0xE:
                func_80B53CE8(arg0, arg1, 0xC);
                SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
                temp_t3 = arg0->unk_360 | 0x300;
                arg0->unk_360 = temp_t3;
                arg0->unk_360 = temp_t3 | 0x8000;
                break;
        }
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80B56B00(EnAn* arg0, PlayState* arg1, u8* arg2) {
    Vec3s* sp20;
    Vec3s* temp_a2;
    u16 temp_t0;

    Math_Vec3f_Copy(arg0 + 0x24, &D_80B58E7C);
    temp_a2 = arg0 + 0xBC;
    sp20 = temp_a2;
    Math_Vec3s_Copy(temp_a2, &D_80B58E88);
    Math_Vec3s_Copy(arg0 + 0x30, sp20);
    if (*arg2 == 0xC) {
        func_80B53CE8(arg0, arg1, 0xB);
        SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
        temp_t0 = arg0->unk_360 | 0x300;
        arg0->unk_360 = temp_t0;
        arg0->unk_360 = temp_t0 | 0x40;
        arg0->unk_38A = 5;
        arg0->unk_38C = 5;
        arg0->unk_38E = 8;
    }
    return 1;
}

s32 func_80B56BC0(EnAn* arg0, PlayState* arg1, u8* arg2) {
    Vec3s* sp24;
    Vec3s* temp_a2;
    u16 temp_t0;
    u8 temp_v0;

    Math_Vec3f_Copy(arg0 + 0x24, &D_80B58E90);
    temp_a2 = arg0 + 0xBC;
    sp24 = temp_a2;
    Math_Vec3s_Copy(temp_a2, &D_80B58E9C);
    Math_Vec3s_Copy(arg0 + 0x30, sp24);
    temp_v0 = *arg2;
    switch (temp_v0) {                              /* irregular */
        case 0x1:
            SubS_SetOfferMode(arg0 + 0x360, 3U, 7U);
            func_80B53CE8(arg0, arg1, 9);
            break;
        case 0x18:
            func_80B53CE8(arg0, arg1, 0xB);
            arg0->unk_38A = 5;
            arg0->unk_38C = 5;
            arg0->unk_38E = 8;
            break;
    }
    temp_t0 = arg0->unk_360 | 0x300;
    arg0->unk_360 = temp_t0;
    arg0->unk_360 = temp_t0 | 0x40;
    arg0->actor.gravity = 0.0f;
    return 1;
}

s32 func_80B56CAC(EnAn* arg0, PlayState* arg1, ? arg2) {
    Vec3s* sp20;
    Vec3s* temp_a2;

    temp_a2 = arg0 + 0xBC;
    sp20 = temp_a2;
    Math_Vec3s_Copy(temp_a2, &D_80B58EA4);
    Math_Vec3s_Copy(arg0 + 0x30, sp20);
    func_80B53CE8(arg0, arg1, 0);
    SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
    arg0->unk_360 |= 0x300;
    return 1;
}

s32 func_80B56D28(EnAn* arg0, u8* arg2) {
    s32 var_v1;
    u8 temp_t0;

    arg0->actor.flags |= 1;
    arg0->actor.targetMode = 6;
    arg0->unk_360 = 0;
    arg0->unk_38A = 0;
    arg0->unk_38C = 0;
    arg0->unk_38E = 8;
    arg0->unk_374 = 40.0f;
    temp_t0 = *arg2;
    switch (temp_t0) {
        case 0x10:
            var_v1 = func_80B5600C();
            break;
        case 0x11:
            var_v1 = func_80B56094();
            break;
        case 0x15:
            var_v1 = func_80B5611C();
            break;
        case 0xC:
            var_v1 = func_80B56B00();
            break;
        case 0x1:
        case 0x18:
            var_v1 = func_80B56BC0();
            break;
        case 0x3:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x17:
            var_v1 = func_80B56880();
            break;
        case 0x16:
            var_v1 = func_80B56744();
            break;
        case 0x19:
            var_v1 = func_80B56CAC();
            break;
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
            var_v1 = func_80B561A4();
            break;
        case 0x28:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            var_v1 = func_80B56418();
            break;
        default:
            var_v1 = 0;
            break;
    }
    return var_v1;
}

? func_80B56E44(EnAn* arg0, ? arg1) {
    Vec3f sp2C;
    Vec3f sp20;
    Actor* temp_v0;

    temp_v0 = arg0->unk_218;
    if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
        Math_Vec3f_Copy(&sp2C, temp_v0 + 0x24);
        Math_Vec3f_Copy(&sp20, arg0 + 0x24);
        arg0->actor.world.rot.y = Math_Vec3f_Yaw(&sp20, &sp2C);
    }
    return 1;
}

? func_80B56EB4(Actor* arg0, PlayState* arg1) {
    struct EnDoor* sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    Vec3f* sp28;                                    /* compiler-managed */
    SkelAnime* temp_a0_2;
    Vec3f* temp_a0;
    f32 temp_fv0;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_a0;

    sp44 = func_80B53B3C(arg1, arg0->unk_200);
    if ((SubS_InCsMode(arg1) == 0) && (arg0->unk_384 != 0)) {
        if ((sp44 != NULL) && (sp44->unk_138 != 0)) {
            if (((f32) arg0->unk_37A / (f32) arg0->unk_378) <= 0.9f) {
                sp44->unk_1A7 = (s8) arg0->unk_215;
            } else {
                sp44->unk_1A7 = 0;
            }
        }
        temp_v0 = arg0->unk_37A;
        if (temp_v0 < 0) {
            arg0->unk_37A = 0;
        } else {
            temp_v1 = arg0->unk_378;
            var_a0 = temp_v0;
            if (temp_v1 < temp_v0) {
                var_a0 = temp_v1;
            }
            arg0->unk_37A = var_a0;
        }
        temp_a0 = arg0 + 0x228;
        sp28 = temp_a0;
        temp_fv0 = Math_Vec3f_DistXZ(temp_a0, arg0 + 0x234);
        sp38 = 0.0f;
        sp3C = 0.0f;
        sp40 = (f32) arg0->unk_37A * (temp_fv0 / (f32) arg0->unk_378);
        Lib_Vec3f_TranslateAndRotateY(temp_a0, arg0->world.rot.y, (Vec3f* ) &sp38, arg0 + 0x24);
        temp_a0_2 = arg0 + 0x144;
        arg0->unk_37A = (s16) (arg0->unk_37A + arg0->unk_384);
        sp28 = temp_a0_2;
        if ((Animation_OnFrame(temp_a0_2, 3.0f) != 0) || (Animation_OnFrame(temp_a0_2, 15.0f) != 0)) {
            Actor_PlaySfx(arg0, 0x2971U);
        }
    }
    return 0;
}

? func_80B5702C(Actor* arg0, PlayState* arg1) {
    f32 sp7C;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54;
    s32 sp50;
    f32* sp48;                                      /* compiler-managed */
    s32* sp44;
    s32* sp40;
    Vec3f* sp3C;
    SkelAnime* temp_a0;
    Vec3f* var_v1;
    f32* temp_a1;
    s32* temp_a2;
    s32* temp_v0;

    sp50 = 0;
    sp54 = 0;
    SubS_TimePathing_FillKnots(&sp7C, 3, arg0->unk_1DC->count + 3);
    var_v1 = arg0 + 0x1E0;
    if (!(arg0->unk_360 & 8)) {
        temp_v0 = arg0 + 0x1F8;
        sp58.x = gZeroVec3f.x;
        temp_a1 = arg0 + 0x1EC;
        sp58.y = gZeroVec3f.y;
        temp_a2 = arg0 + 0x1FC;
        sp58.z = gZeroVec3f.z;
        sp44 = temp_a2;
        sp48 = temp_a1;
        sp40 = temp_v0;
        SubS_TimePathing_Update(arg0->unk_1DC, temp_a1, temp_a2, arg0->unk_1F4, arg0->unk_1F0, temp_v0, &sp7C, &sp58, (s32) arg0->unk_384);
        SubS_TimePathing_ComputeInitialY(arg1, arg0->unk_1DC, arg0->unk_1F8, &sp58);
        var_v1 = arg0 + 0x1E0;
        arg0->unk_360 = (u16) (arg0->unk_360 | 8);
        arg0->world.pos.y = sp58.y;
    } else {
        sp58.x = var_v1->x;
        sp58.y = var_v1->y;
        sp58.z = var_v1->z;
        sp40 = arg0 + 0x1F8;
        sp44 = arg0 + 0x1FC;
        sp48 = arg0 + 0x1EC;
    }
    arg0->world.pos.x = (bitwise f32) sp58;
    arg0->world.pos.z = sp58.z;
    sp3C = var_v1;
    if (SubS_InCsMode(arg1) != 0) {
        sp54 = arg0->unk_1FC;
        sp50 = arg0->unk_1F8;
        sp58.x = arg0->world.pos.x;
        sp58.y = arg0->world.pos.y;
        sp58.z = arg0->world.pos.z;
    }
    var_v1->x = gZeroVec3f.x;
    var_v1->y = gZeroVec3f.y;
    var_v1->z = gZeroVec3f.z;
    sp3C = var_v1;
    if (SubS_TimePathing_Update(arg0->unk_1DC, sp48, sp44, arg0->unk_1F4, arg0->unk_1F0, sp40, &sp7C, var_v1, (s32) arg0->unk_384) != 0) {
        arg0->unk_360 = (u16) (arg0->unk_360 | 0x10);
    } else {
        sp70.x = arg0->world.pos.x;
        sp70.y = arg0->world.pos.y;
        sp70.z = arg0->world.pos.z;
        sp64.x = sp3C->x;
        sp64.y = sp3C->y;
        sp64.z = sp3C->z;
        arg0->world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }
    if (SubS_InCsMode(arg1) != 0) {
        arg0->unk_1FC = sp54;
        arg0->unk_1F8 = sp50;
        sp3C->x = sp58.x;
        sp3C->y = sp58.y;
        sp3C->z = sp58.z;
    } else {
        temp_a0 = arg0 + 0x144;
        sp48 = temp_a0;
        if ((Animation_OnFrame(temp_a0, 3.0f) != 0) || (Animation_OnFrame(temp_a0, 15.0f) != 0)) {
            Actor_PlaySfx(arg0, 0x2971U);
        }
    }
    return 0;
}

? func_80B572D4(Actor* arg0, PlayState* arg1) {
    u8 temp_t6;

    temp_t6 = arg0->unk_200;
    switch (temp_t6) {
        case 0x17:
            if ((func_80B55F8C(arg1) != 0) && (func_80B55ECC(arg0) != 0)) {
                arg0->unk_360 = (u16) (arg0->unk_360 | 0x20);
            } else {
                arg0->unk_360 = (u16) (arg0->unk_360 & 0xFFDF);
            }
            break;
        case 0x1:
            if (func_80B55ECC(arg0) != 0) {
                arg0->unk_360 = (u16) (arg0->unk_360 | 0x20);
            } else {
                arg0->unk_360 = (u16) (arg0->unk_360 & 0xFFDF);
            }
            break;
        case 0x12:
        case 0x13:
            if (func_80B55ECC(arg0) != 0) {
                arg0->unk_360 = (u16) (arg0->unk_360 | 0x20);
            } else {
                arg0->unk_360 = (u16) (arg0->unk_360 & 0xFFDF);
            }
            break;
        case 0x16:
            if ((Animation_OnFrame((SkelAnime* ) (arg0 + 0x144), 6.0f) != 0) && (arg0->unk_39C == 0x17)) {
                Actor_PlaySfx(arg0, 0x2899U);
            }
            break;
    }
    return 0;
}

? func_80B573F4(EnAn* arg0, PlayState* arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_v1;

    temp_v0 = arg0->unk_37A;
    switch (temp_v0) {
        case 0x0:
            arg0->unk_37A = temp_v0 + 1;
            arg0->actor.world.rot.y += 0x7FF8;
            break;
        case 0x1:
            if ((s16) (((s16) arg0->actor.world.rot.y / 182) * 0xB6) == (s16) (((s16) arg0->actor.shape.rot.y / 182) * 0xB6)) {
                Math_Vec3s_Copy(arg0 + 0xBC, arg0 + 0x30);
                func_80B53CE8(arg0, arg1, 0x13);
                arg0->unk_360 |= 0x40;
                arg0->unk_37A += 1;
            }
            break;
        case 0x2:
            if (Animation_OnFrame(&arg0->unk_144, arg0->unk_144.endFrame) != 0) {
                arg0->unk_37A += 1;
            }
            break;
        case 0x3:
            temp_v0_2 = arg0->actor.yawTowardsPlayer - arg0->actor.shape.rot.y;
            var_v1 = temp_v0_2;
            if (temp_v0_2 < 0) {
                var_v1 = -temp_v0_2;
            }
            if (var_v1 < 0x3000) {
                SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
            } else {
                SubS_SetOfferMode(&arg0->unk_360, 0U, 7U);
            }
            break;
        case 0x4:
            SubS_SetOfferMode(&arg0->unk_360, 3U, 7U);
            arg0->unk_37A += 1;
            break;
    }
    return 0;
}

? func_80B575BC(Actor* arg0, ? arg1) {
    s16 temp_v1;
    s32 var_v0;

    temp_v1 = arg0->yawTowardsPlayer - arg0->shape.rot.y;
    var_v0 = temp_v1 << 0x10;
    if (temp_v1 < 0) {
        var_v0 = temp_v1 * -0x10000;
    }
    if ((var_v0 >> 0x10) < 0x4000) {
        SubS_SetOfferMode(arg0 + 0x360, 3U, 7U);
    } else {
        SubS_SetOfferMode(arg0 + 0x360, 0U, 7U);
    }
    if (func_80B55ECC(arg0) != 0) {
        arg0->unk_360 = (u16) (arg0->unk_360 | 0x20);
    } else {
        arg0->unk_360 = (u16) (arg0->unk_360 & 0xFFDF);
    }
    return 1;
}

? func_80B57674(EnAn* arg0, ? arg1) {
    s16 temp_v1;
    s32 var_v0;

    temp_v1 = arg0->actor.yawTowardsPlayer - (s16) (arg0->actor.shape.rot.y + 0x3000);
    var_v0 = temp_v1 << 0x10;
    if (temp_v1 < 0) {
        var_v0 = temp_v1 * -0x10000;
    }
    if ((var_v0 >> 0x10) < 0x3000) {
        SubS_SetOfferMode(arg0 + 0x360, 3U, 7U);
    } else {
        SubS_SetOfferMode(arg0 + 0x360, 0U, 7U);
    }
    arg0->unk_360 &= 0xFFDF;
    return 1;
}

void func_80B57718(EnAn* arg0) {
    u8 temp_t7;

    temp_t7 = arg0->unk_200;
    switch (temp_t7) {
        case 0x10:
        case 0x11:
        case 0x15:
            func_80B56E44(arg0);
            break;
        case 0x3:
            func_80B573F4(arg0);
            break;
        case 0x1:
            func_80B575BC(&arg0->actor);
            break;
        case 0x19:
            func_80B57674(arg0);
            break;
        case 0xC:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x16:
        case 0x18:
            func_80B572D4(&arg0->actor);
            break;
        case 0x17:
            func_80B572D4(&arg0->actor);
            break;
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
            func_80B56EB4(&arg0->actor);
            break;
        case 0x28:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            func_80B5702C(&arg0->actor);
            break;
    }
    Math_ApproachS(&arg0->actor.shape.rot.y, arg0->actor.world.rot.y, 3, 0x2AA8);
}

void func_80B577F0(EnAn* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->unk_144, &D_06012618, NULL, this->unk_264, this->unk_2E2, 0x15);
    this->unk_39C = -1;
    func_80B53CE8(this, play, 1);
    Collider_InitAndSetCylinder(play, &this->unk_190, &this->actor, &D_80B58BBC);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B58BE8);
    if (this->actor.params & 0x8000) {
        this->unk_3C0 = 1;
    }
    this->actor.draw = EnAn_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_360 = 0;
    this->unk_200 = 0;
    this->actionFunc = func_80B578F8;
    func_80B578F8(this, play);
}

void func_80B578F8(EnAn* this, PlayState* play) {
    u8 sp20;

    this->unk_384 = gSaveContext.save.timeSpeedOffset + gRegEditor->data[0xF];
    if (!(this->actor.params & 0x8000) && (this->unk_3C0 == 0) && (gSaveContext.save.saveInfo.weekEventReg[0x33] & 0x40)) {
        Actor_Kill(&this->actor);
        return;
    }
    if (this->unk_3C0 != 0) {
        sp20 = 0x19;
        if (this->unk_200 != 0x19) {
            func_80B56D28(this, (u8* ) play, &sp20);
        }
    } else if ((Schedule_RunScript(play, &D_80B581D0, (ScheduleOutput* ) &sp20) == 0) || ((sp20 != this->unk_200) && (func_80B56D28(this, (u8* ) play, &sp20) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~1;
        sp20 = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= 1;
    }
    this->unk_200 = sp20;
    this->unk_218 = func_80B55D20(this, play);
    func_80B57718(this, play);
}

void func_80B57A44(EnAn* this, PlayState* play) {
    Vec3f sp38;
    Vec3f sp2C;
    Actor* temp_v0_2;
    u16 temp_t9;
    u8 temp_v0;

    if (func_8010BF58(&this->actor, play, this->unk_204, this->unk_398, &this->unk_210) != 0) {
        SubS_SetOfferMode(&this->unk_360, 3U, 7U);
        temp_t9 = this->unk_360 & 0xFFDF;
        this->unk_360 = temp_t9;
        this->unk_360 = temp_t9 | 0x200;
        this->unk_388 = 0x14;
        this->unk_210 = 0;
        this->actionFunc = func_80B578F8;
        return;
    }
    temp_v0 = this->unk_200;
    if ((temp_v0 != 1) && (temp_v0 != 3) && (temp_v0 != 0xC) && (temp_v0 != 0xE) && (temp_v0 != 0x19)) {
        temp_v0_2 = this->unk_218;
        if ((temp_v0_2 != NULL) && (temp_v0_2->update != NULL)) {
            Math_Vec3f_Copy(&sp38, &temp_v0_2->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp2C, &sp38), 4, 0x2AA8);
        }
    }
}

void func_80B57B48(EnAn* this, PlayState* play) {
    ? sp30;
    s32 sp28;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v1;
    u8 var_v0;

    M2C_MEMCPY_ALIGNED(&sp30, &D_80B58EAC, 0x28);
    if (Cutscene_IsCueInChannel(play, 0x22DU) != 0) {
        temp_v0 = Cutscene_GetCueChannel(play, 0x22DU);
        sp28 = temp_v0;
        temp_v1 = play->csCtx.actorCues[temp_v0]->id;
        var_v0 = temp_v1 & 0xFF;
        if ((temp_v1 & 0xFF) != (u8) this->unk_364) {
            this->unk_364 = (s8) temp_v1;
            if (var_v0 == 3) {
                gSaveContext.save.saveInfo.weekEventReg[0x57] |= 2;
                var_v0 = (u8) this->unk_364;
                this->unk_3B4 = 1;
            }
            if (var_v0 == 9) {
                this->unk_3B4 = 0;
            }
            func_80B53CE8(this, play, (sp + (temp_v1 * 4))->unk_30);
        }
        temp_v0_2 = this->unk_39C;
        if (((temp_v0_2 == 0x1A) || (temp_v0_2 == 0x1C) || (temp_v0_2 == 0x1E) || (temp_v0_2 == 0x22)) && (Animation_OnFrame(&this->unk_144, this->unk_144.endFrame) != 0)) {
            func_80B53CE8(this, play, this->unk_39C + 1);
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, sp28);
    }
}

void func_80B57EE8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80B58ED4, &thisx->focus.pos);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
        func_80B54124((EnAn* ) thisx, play, 1U);
        return;
    }
    if (limbIndex == 8) {
        func_80B54124((EnAn* ) thisx, play, 0U);
        func_80B54124((EnAn* ) thisx, play, 4U);
        func_80B54124((EnAn* ) thisx, play, 2U);
        func_80B54124((EnAn* ) thisx, play, 3U);
        return;
    }
    if (limbIndex == 5) {
        func_80B54124((EnAn* ) thisx, play, 5U);
    }
}

void func_80B57FC4(PlayState* play, s32 limbIndex, Actor* thisx) {
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0;

    temp_v0 = thisx->unk_360;
    var_v1 = 0;
    if (!(temp_v0 & 0x200)) {
        var_v1 = 0;
        if (temp_v0 & 0x80) {
            var_v1 = 1;
            var_v0 = 1;
        } else {
            var_v0 = 1;
        }
    } else {
        var_v0 = 0;
    }
    if (limbIndex == 9) {
        SubS_UpdateLimb((s16) (thisx->unk_37C + 0x4000), (s16) (thisx->unk_37E + thisx->shape.rot.y + 0x4000), thisx + 0x240, thisx + 0x258, var_v0, var_v1);
        Matrix_Pop();
        Matrix_Translate(thisx->unk_240, thisx->unk_244, thisx->unk_248, MTXMODE_NEW);
        Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(thisx->unk_25A, MTXMODE_APPLY);
        Matrix_RotateXS(thisx->unk_258, MTXMODE_APPLY);
        Matrix_RotateZS(thisx->unk_25C, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnAn_Draw(Actor* thisx, PlayState* play) {
    GraphicsContext* sp40;
    Gfx* sp38;
    Gfx* sp34;
    Gfx* temp_v0;
    Gfx* temp_v0_2;
    GraphicsContext* temp_a0;
    EnAn* this = (EnAn* ) thisx;

    if ((this->unk_200 != 0) || (this->unk_3B0 != 0)) {
        temp_a0 = play->state.gfxCtx;
        sp40 = temp_a0;
        Gfx_SetupDL25_Opa(temp_a0);
        temp_v0 = sp40->polyOpa.p;
        sp40->polyOpa.p = temp_v0 + 8;
        temp_v0->words.w0 = 0xDB060020;
        sp38 = temp_v0;
        sp38->words.w1 = Lib_SegmentedToVirtual(D_80B58EEC[this->unk_390]);
        temp_v0_2 = sp40->polyOpa.p;
        sp40->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w0 = 0xDB060024;
        sp34 = temp_v0_2;
        sp34->words.w1 = Lib_SegmentedToVirtual(D_80B58EE0[this->unk_392]);
        SkelAnime_DrawTransformFlexOpa(play, this->unk_144.skeleton, this->unk_144.jointTable, (s32) this->unk_144.dListCount, NULL, func_80B57EE8, func_80B57FC4, &this->actor);
    }
}
/* Warning: struct EnTorch2 is not defined (only forward-declared) */
/* Warning: struct EnDoor is not defined (only forward-declared) */
