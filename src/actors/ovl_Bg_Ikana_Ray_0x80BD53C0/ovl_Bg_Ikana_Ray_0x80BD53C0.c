#include <ultra64.h>
#include <global.h>

typedef struct z_ActorBgIkanaRay_s {
	/* 000 */ z_Actor baseActor;
	/* 324 */ UNK_TYPE unk324;
	/* 328 */ u8 pad5[72];
	/* 400 */ UNK_TYPE unk400;
	/* 404 */ void(*unk404)(struct z_ActorBgIkanaRay_s*, z_GlobalContext*);
} z_ActorBgIkanaRay;

void z_bg_ikana_ray_init(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);
void z_bg_ikana_ray_fini(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);
void z_bg_ikana_ray_main(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);
void z_bg_ikana_ray_draw(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);
void func_80BD5498(z_ActorBgIkanaRay* this);
void func_80BD54BC(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);
void func_80BD5500(z_ActorBgIkanaRay* this);
void func_80BD5530(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt);

z_ActorInit bgIkanaRayInitVar = {
	0x0256,
	6,
	0,
	0,
	0x0203,
	sizeof(z_ActorBgIkanaRay),
	(z_ActorFunc)z_bg_ikana_ray_init,
	(z_ActorFunc)z_bg_ikana_ray_fini,
	(z_ActorFunc)z_bg_ikana_ray_main,
	(z_ActorFunc)z_bg_ikana_ray_draw
};

GLOBAL_ASM(
.data
glabel D_80BD55F0
/* 000140 0x80BD55F0 */ .word	0x0A210000
/* 000141 0x80BD55F4 */ .word	0x00010000
/* 000142 0x80BD55F8 */ .word	0x00000000
/* 000143 0x80BD55FC */ .word	0x00200000
/* 000144 0x80BD5600 */ .word	0x00000000
/* 000145 0x80BD5604 */ .word	0x00000000
/* 000146 0x80BD5608 */ .word	0x00000000
/* 000147 0x80BD560C */ .word	0x19000100
/* 000148 0x80BD5610 */ .word	0x005A01A4
/* 000149 0x80BD5614 */ .word	0xFE5C0000
/* 000150 0x80BD5618 */ .word	0x00000000
)

// TODO macro
z_ActorCompInitEntry  bgIkanaRayCompInit[] = {
	{1, 6, 0x0FC, 4000},
	{1, 6, 0x100, 1000},
	{1, 6, 0x104, 1000},
	{0, 9, 0x058, 100}
};

// Unused?
GLOBAL_ASM(
.data
glabel D_80BD562C
/* 000155 0x80BD562C */ .word	0x00000000
/* 000156 0x80BD5630 */ .word	0x00000210
/* 000157 0x80BD5634 */ .word	0x00000060
/* 000158 0x80BD5638 */ .word	0x00000000
/* 000159 0x80BD563C */ .word	0x00000000
/* 000160 0x80BD5640 */ .word	0x00000011
/* 000161 0x80BD5644 */ .word	0x45000014
/* 000162 0x80BD5648 */ .word	0x46000018
/* 000163 0x80BD564C */ .word	0x45000034
/* 000164 0x80BD5650 */ .word	0x46000038
/* 000165 0x80BD5654 */ .word	0x44000080
/* 000166 0x80BD5658 */ .word	0x44000090
/* 000167 0x80BD565C */ .word	0x450000DC
/* 000168 0x80BD5660 */ .word	0x460000E0
/* 000169 0x80BD5664 */ .word	0x44000128
/* 000170 0x80BD5668 */ .word	0x45000144
/* 000171 0x80BD566C */ .word	0x46000150
/* 000172 0x80BD5670 */ .word	0x4500014C
/* 000173 0x80BD5674 */ .word	0x46000154
/* 000174 0x80BD5678 */ .word	0x82000010
/* 000175 0x80BD567C */ .word	0x82000014
/* 000176 0x80BD5680 */ .word	0x82000018
/* 000177 0x80BD5684 */ .word	0x8200001C
)

void z_bg_ikana_ray_init(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	UNK_TYPE* sp36 = &this->unk324;
	u32 pad;

	func_800FFADC((z_Actor*)this, bgIkanaRayCompInit);
	func_800E119C(ctxt, sp36);
	func_800E130C(ctxt, sp36, (z_Actor*)this, &D_80BD55F0);
	func_800E7DF8((z_Actor*)this, &this->unk324);
	this->unk400 = func_80100504((UNK_TYPE)&D_06001228); // XXX: D_06001228 is probably a constant

	if (func_800B5BB0(ctxt, this->baseActor.unk28 & 0x7F) != 0) {
		func_80BD5500(this);
	} else {
		func_80BD5498(this);
	}
}

void z_bg_ikana_ray_fini(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	UNK_TYPE* a1 = &this->unk324;
	func_800E11EC(ctxt, a1);
}

void func_80BD5498(z_ActorBgIkanaRay* this) {
	this->baseActor.drawFunc = NULL;
	this->baseActor.unk4 |= 0x10;
	this->unk404 = func_80BD54BC;
}

void func_80BD54BC(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	if (func_800B5BB0(ctxt, this->baseActor.unk28 & 0x7F) != 0) {
		func_80BD5500(this);
	}
}

void func_80BD5500(z_ActorBgIkanaRay* this) {
	this->baseActor.drawFunc = (z_ActorFunc)z_bg_ikana_ray_draw;
	this->baseActor.unk4 &= 0xFFFFFFEF;
	this->unk404 = func_80BD5530;
}

void func_80BD5530(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	func_800E2558(ctxt, &ctxt->unk100484, &this->unk324);
}

void z_bg_ikana_ray_main(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	this->unk404(this, ctxt);
}

void z_bg_ikana_ray_draw(z_ActorBgIkanaRay* this, z_GlobalContext* ctxt) {
	func_80131758(ctxt, this->unk400);
	func_800BE03C(ctxt, (UNK_TYPE)&D_06001100); // XXX: D_06001100 is probably a constant
}
