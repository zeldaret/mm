#include <ultra64.h>
#include <global.h>

void func_80081820(void) {}

void func_80081828(void) {}

void func_80081830(void) {
	func_8008481C(80, 200, &D_80098280, (UNK_PTR)(*(u32*)0xA4040010));
	func_8008481C(40, 184, &D_80098290, &D_800994D0);
	func_8008481C(56, 192, &D_800982A4, &D_800994DC);
}

void func_8008189C(void) {
	func_800819F0(&D_8009BE38, (void(*)(UNK_TYPE, UNK_TYPE))func_80081830, 0, 0);
}

void func_800818D0(void) {
	func_80081AD4(&D_8009BE38);
}

void func_800818F4(void) {
	D_8009BE30 = *(u32*)0xA02FB1F4;
	D_8009BE34 = *(u32*)0xA02FE1C0;
}
