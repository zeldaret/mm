#include <ultra64.h>
#include <global.h>

s32 func_80080790(void* a0, void* a1, s32 a2) {
    u32 spPad;
    OSIoMesg sp96;
    OSMesgQueue sp72;
    OSMesg sp68;
    s32 ret;
    u32 s0 = D_80096B50;

    osInvalDCache(a1, a2);
    osCreateMesgQueue(&sp72, &sp68, 1);

    if (s0 != 0) {
        while (s0 < a2) {
            sp96.hdr.pri = 0;
            sp96.hdr.retQueue = &sp72;
            sp96.devAddr = (u32)a0;
            sp96.dramAddr = a1;
            sp96.size = s0;
            ret = osEPiStartDma(D_80096B40, &sp96, 0);
            if (ret) goto END;

            osRecvMesg(&sp72, NULL, 1);
            a2 -= s0;
            a0 = (u8*)a0 + s0;
            a1 = (u8*)a1 + s0;
        }
    }
    sp96.hdr.pri = 0;
    sp96.hdr.retQueue = &sp72;
    sp96.devAddr = (u32)a0;
    sp96.dramAddr = a1;
    sp96.size = (u32)a2;
    ret = osEPiStartDma(D_80096B40, &sp96, 0);
    if (ret) goto END;

    osRecvMesg(&sp72, NULL, 1);

    osInvalDCache(a1, a2);

END:
    return ret;
}

void func_800808D4(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    osPiStartDma(pihandle, mb, direction);
}

DmadataEntry* func_800808F4(u32 a0) {
    DmadataEntry* curr;

    for (curr = dmadata; curr->vromEnd != 0; curr++) {
        if (a0 < curr->vromStart) continue;
        if (a0 >= curr->vromEnd) continue;

        return curr;
    }

    return NULL;
}

s32 func_80080950(u32 a0) {
    DmadataEntry* v0 = func_800808F4(a0);

    if (v0 != NULL) {
        if (v0->romEnd == 0) {
            return a0 + v0->romStart - v0->vromStart;
        }

        if (a0 == v0->vromStart) {
            return v0->romStart;
        }

        return -1;
    }

    return -1;
}

s32 func_800809BC(u32 a0) {
    DmadataEntry* v0 = func_800808F4(a0);

    if (v0 != NULL) {
		// TODO this uses t7 to shift instead of reusing v0
		return v0 - dmadata;
    }

    return -1;
}

UNK_TYPE* func_800809F4(u32 a0) {
    return &D_800981C0;
}

void func_80080A08(s80080A08* a0) {
    UNK_TYPE sp52;
    UNK_TYPE sp48;
    UNK_TYPE sp44;
    UNK_TYPE sp40;
    UNK_TYPE sp36;
    UNK_TYPE sp32;
    s32 sp28;
    UNK_TYPE sp24;

    sp52 = (UNK_TYPE)a0->unk0;
    sp48 = (UNK_TYPE)a0->unk4;
    sp44 = a0->unk8;

    sp28 = func_800809BC(sp52);

    if ((sp28 >= 0) && (sp28 < D_8009B2BC)) {
        if (dmadata[sp28].romEnd == 0) {
            if (dmadata[sp28].vromEnd < (sp44 + sp52)) {
                func_80083E4C(&D_800981C4, 499);
            }
            func_80080790((u8*)((dmadata[sp28].romStart + sp52) - dmadata[sp28].vromStart), (u8*)sp48, sp44);
            return;
        }

        // TODO this part is arranged slightly different is ASM
        sp36 = dmadata[sp28].romEnd - dmadata[sp28].romStart;
        sp40 = dmadata[sp28].romStart;

        if (sp52 != dmadata[sp28].vromStart) {
            func_80083E4C(&D_800981D4, 518);
        }

        if (sp44 != (dmadata[sp28].vromEnd - dmadata[sp28].vromStart)) {
            func_80083E4C(&D_800981E4, 525);
        }

        osSetThreadPri(NULL, 10);
        func_80081178(sp40, sp48, sp36);
        osSetThreadPri(NULL, 17);
    } else {
        func_80083E4C(&D_800981F4, 558);
    }
}

void func_80080B84(void* a0) {
    s80080A08* sp52;
	UNK_TYPE pad;
    s80080A08* s0;

    for (;;) {
        osRecvMesg(&D_8009B2C0, (OSMesg)&sp52, 1);
        if (sp52 == NULL) return;
        s0 = sp52;
        func_80080A08(s0);
        // TODO a0 isn't being used for this comparison
        if (s0->unk24 == 0) continue;
        osSendMesg(&D_8009B2C0, (OSMesg)s0->unk28, 0);
    }
}

s32 func_80080C04(s80080A08* a0, UNK_FUN_PTR(a1), UNK_PTR a2, UNK_TYPE a3, UNK_TYPE sp48, OSMesgQueue* sp52, UNK_TYPE sp56) {
    // TODO this isn't correct, it uses a lui, addiu to get the address of D_80096B60, then loads it,
	// meaning that this is likely just "if (*D_80096B60 >= 2)". However, I can not get it to not
	// produce the usual lui, lw combo to load from an address :/
    if (*D_80096B60 >= 2) {
        return -2;
    }

    a0->unk0 = a2;
    a0->unk4 = a1;
    a0->unk8 = a3;
    a0->unk20 = 0;
    a0->unk24 = sp52;
    a0->unk28 = sp56;

    osSendMesg(&D_8009B2C0, (OSMesg)a0, 1);

    return 0;
}

s32 func_80080C90(UNK_TYPE a0, UNK_PTR a1, UNK_TYPE a2) {
	s80080A08 sp72;
    OSMesgQueue sp48;
    OSMesg sp44;
	s32 ret;

    osCreateMesgQueue(&sp48, &sp44, 1);

	ret = func_80080C04(&sp72, (UNK_FUN_ARG)a0, a1, a2, 0, &sp48, 0);

	if (ret == -1) {
		return ret;
	} else {
		osRecvMesg(&sp48, NULL, 1);
	}

	return 0;
}

void func_80080D0C() {
	DmadataEntry* v0;
	u32 v1;
	// TODO register load ordering is wrong
	func_80080790(&dmadataRomStart, dmadata, (u8*)&dmadataRomEnd - (u8*)&dmadataRomStart);

	for (v0 = dmadata, v1 = 0; v0->vromEnd != 0; v0++, v1++);

	D_8009B2BC = (u16)v1;

	osCreateMesgQueue(&D_8009B2C0, (OSMesg)&D_8009B2D8, 32);

	func_80085320(&D_8009B2A0, &D_8009B508, &D_8009BA08, 0, 256, &D_80098204);

	osCreateThread(&D_8009B358, 18, func_80080B84, NULL, &D_8009BA08, 17);

	osStartThread(&D_8009B358);
}

void func_80080E00() {
    osSendMesg(&D_8009B2C0, NULL, 1);
}
