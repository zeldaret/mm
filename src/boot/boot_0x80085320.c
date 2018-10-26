#include <ultra64.h>
#include <global.h>

void func_80085320(struct s80085320* a0, UNK_PTR a1, UNK_PTR a2, UNK_TYPE a3, UNK_TYPE sp16, UNK_PTR sp20) {
	UNK_TYPE* i;
	struct s80085320* v0;
	
	if (a0 == NULL) {
		g_s80085320_ListHead = NULL;
		return;
	}
	
	a0->unk8 = a1;
	a0->unk12 = a2;
	a0->unk16 = a3;
	a0->unk20 = sp16;
	a0->unk24 = sp20;
	
	v0 = g_s80085320_ListHead;
	while (v0 != NULL) {
		if (v0 == a0) return;
		v0 = v0->next;
	}
	
	a0->prev = g_s80085320_ListTail;
	a0->next = NULL;
	
	if (g_s80085320_ListTail != NULL) {
		g_s80085320_ListTail->next = a0;
	}
	
	g_s80085320_ListTail = a0;
	
	if (g_s80085320_ListHead == NULL) {
		g_s80085320_ListHead = a0;
	}
	
	if (a0->unk20 != -1) {
		for (i = a0->unk8; i < a0->unk12; i++) {
			*i = a0->unk16;
		}
	}
}

UNK_RET func_800853F8(struct s80085320* a0) {
	if (a0->prev == NULL) {
		if (g_s80085320_ListHead == a0) {
			g_s80085320_ListHead = a0->next;
		}
	} else {
		a0->prev->next = a0->next;
	}
	
	if (a0->next == NULL) {
		if (g_s80085320_ListTail == a0) {
			g_s80085320_ListTail = a0->prev;
		}
	}
}

UNK_TYPE func_80085468(struct s80085320* a0) {
	UNK_TYPE* v1 = a0->unk8;
	UNK_TYPE* a1 = a0->unk12;
	UNK_TYPE* v0 = v1;
	u32 x; // ptr_diff
	
	while (v0 < a1) {
		if (*v0++ != a0->unk16) break;
		a1 = (UNK_TYPE*)((u32)v0 - (u32)v1);
	}
	
	x = v0 - v1;
	
	if (x == 0) {
		return 2;
	}
	
	if ((x < a0->unk20) && (a0->unk20 != -1)) {
		return 1;
	}
	
	return 0;
}

UNK_TYPE func_800854E0(UNK_ARGS) {
	struct s80085320* s0 = g_s80085320_ListHead;
	UNK_TYPE ret = 0;
	while (s0 != NULL) {
		if (func_80085468(s0) != 0) {
			ret = 1;
		}
		s0 = s0->next;
	}
	
	return ret;
}

UNK_RET func_80085538(struct s80085320* a0) {
	if (a0 == NULL) {
		func_800854E0();
	} else {
		func_80085468(a0);
	}
}
