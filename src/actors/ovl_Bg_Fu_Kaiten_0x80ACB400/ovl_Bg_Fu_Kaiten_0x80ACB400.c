#include <ultra64.h>
#include <global.h>

typedef struct z_ActorBgFuKaiten_s {
    /* 0x000 */ z_Actor baseActor;
    /* 0x144 */ UNK_TYPE unk144;
    /* 0x148 */ u8 pad0[0x18];
    /* 0x160 */ f32 unk160;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ s16 unk16A;
    /* 0x16C */ s16 unk16C;
    /* 0x16E */ u8 pad1[0x2];
} z_ActorBgFuKaiten;

void z_bg_fu_kaiten_init(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt);
void z_bg_fu_kaiten_fini(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt);
UNK_RET func_80ACB4B4(z_ActorBgFuKaiten* this);
UNK_RET func_80ACB50C(z_ActorBgFuKaiten* this);
void z_bg_fu_kaiten_main(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt);
void func_80ACB5A0(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt);

z_ActorInitData bgBgFuKaitenInitVar = {
    0x01AE,
    1,
    0,
    0x30,
    0x01A0,
    sizeof(z_ActorBgFuKaiten),
    (actor_func)z_bg_fu_kaiten_init,
    (actor_func)z_bg_fu_kaiten_fini,
    (actor_func)z_bg_fu_kaiten_main,
    (actor_func)func_80ACB5A0
};

f32 D_80ACB650 = 0.002;


// Overlay info
GLOBAL_ASM(
.data
glabel D_80ACB654
/* 000149 0x80ACB654 */ .word    0x00000000
/* 000150 0x80ACB658 */ .word    0x00000000
/* 000151 0x80ACB65C */ .word    0x00000000
/* 000152 0x80ACB660 */ .word    0x00000230
/* 000153 0x80ACB664 */ .word    0x00000020
/* 000154 0x80ACB668 */ .word    0x00000010
/* 000155 0x80ACB66C */ .word    0x00000000
/* 000156 0x80ACB670 */ .word    0x00000008
/* 000157 0x80ACB674 */ .word    0x450000D8
/* 000158 0x80ACB678 */ .word    0x460000DC
/* 000159 0x80ACB67C */ .word    0x44000180
/* 000160 0x80ACB680 */ .word    0x44000188
/* 000161 0x80ACB684 */ .word    0x82000010
/* 000162 0x80ACB688 */ .word    0x82000014
/* 000163 0x80ACB68C */ .word    0x82000018
/* 000164 0x80ACB690 */ .word    0x8200001C
/* 000165 0x80ACB694 */ .word    0x00000000
/* 000166 0x80ACB698 */ .word    0x00000000
/* 000167 0x80ACB69C */ .word    0x00000040
)

void z_bg_fu_kaiten_init(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt) {
    UNK_TYPE pad0;
    UNK_TYPE pad1;
    UNK_TYPE sp24 = 0;

    func_800B67E0((z_Actor*)this, 1.0);
    func_800CAE10((z_Actor*)this, 3);
    func_800C9564((UNK_TYPE)&D_06002D30, &sp24); // XXX: D_06002D30 is probably a constant
    this->unk144 = func_800C6188(ctxt, &ctxt->unk880, (z_Actor*)this, sp24);

    this->unk164 = 0.0;
    this->unk168 = 0;
    this->unk16A = 0;
    this->unk16C = 0;
}

void z_bg_fu_kaiten_fini(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt) {
    func_800C64CC(ctxt, &ctxt->unk880, this->unk144);
}

UNK_RET func_80ACB4B4(z_ActorBgFuKaiten* this) {
    s16 v0 = this->unk168;
    f32 f0;
    this->baseActor.unkBE += v0;
    if (v0 > 0)
    {
        f0 = (f32)v0 * D_80ACB650;
        func_8019FAD8(&this->baseActor.unkEC, 8310, f0);
    }
}

UNK_RET func_80ACB50C(z_ActorBgFuKaiten* this) {
    this->unk16C += this->unk16A;
    this->baseActor.unk24.y = this->baseActor.unk8.y + this->unk160 + this->unk164;

    this->baseActor.unk24.y -= this->unk164 * func_800FED44(this->unk16C);
}

void z_bg_fu_kaiten_main(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt) {
    func_80ACB4B4(this);
    func_80ACB50C(this);
}

#ifdef NON_MATCHING

void func_80ACB5A0(z_ActorBgFuKaiten* this, z_GlobalContext* ctxt) {
    z_GraphicsContext* sp24 = ctxt->unk0;
    UNK_TYPE pad;

    // XXX: register allocation is wrong here

    func_8012C28C(sp24);

    {
    Gfx* v0 = sp24->unk2B0++;
    v0->words.w0 = 0xDA380003;
    v0->words.w1 = func_80181A40(ctxt->unk0);
    }

    {
    Gfx* v0 = sp24->unk2B0++;
    v0->words.w0 = 0xDE000000; v0->words.w1 = (u32)&D_060005D0; // XXX: D_060005D0 is probably a constant
    }
}

#else

GLOBAL_ASM("./asm/nonmatching/ovl_Bg_Fu_Kaiten_0x80ACB400/func_80ACB5A0.asm")

#endif
