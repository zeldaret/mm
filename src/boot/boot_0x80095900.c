#include <ultra64.h>
#include <global.h>

void func_80095900(f32 f12) {
	u32 oldInt;
	
	oldInt = __osDisableInt();
	
	*((f32*)__osViNext + 36 / 4) = f12;
	
	*(u16*)__osViNext |= 0x4;
	
	__osRestoreInt(oldInt);
}
