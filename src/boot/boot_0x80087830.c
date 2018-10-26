#include <ultra64.h>
#include <global.h>

UNK_TYPE func_80087830(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
	return func_8008F208(a0, a1) + a2;
}

UNK_TYPE func_80087854(u8* a0, UNK_TYPE a1, UNK_PTR a2) {
	UNK_TYPE v0 = func_8008E050(func_80087830, a0, a1, a2);
	
	if (v0 >= 0) {
		a0[v0] = 0;
	}
	
	return v0;
}

UNK_TYPE func_800878A4(u8* a0, UNK_TYPE a1, UNK_TYPE a2, UNK_TYPE a3) {
	UNK_TYPE v0 = func_8008E050(func_80087830, a0, a1, &a2);
	
	if (v0 >= 0) {
		a0[v0] = 0;
	}
	
	return v0;
}
