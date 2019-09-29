#include <ultra64.h>
#include <global.h>

s32 Dmamgr_DoDmaTransfer(void* a0, void* a1, s32 a2) {
    u32 spPad;
    OSIoMesg sp60;
    OSMesgQueue sp48;
    OSMesg sp44;
    s32 ret;
    u32 s0 = D_80096B50;

    osInvalDCache(a1, a2);
    osCreateMesgQueue(&sp48, &sp44, 1);

    if (s0 != 0) {
        while (s0 < a2) {
            sp60.hdr.pri = 0;
            sp60.hdr.retQueue = &sp48;
            sp60.devAddr = (u32)a0;
            sp60.dramAddr = a1;
            sp60.size = s0;
            ret = osEPiStartDma(D_80096B40, &sp60, 0);
            if (ret) goto END;

            osRecvMesg(&sp48, NULL, 1);
            a2 -= s0;
            a0 = (u8*)a0 + s0;
            a1 = (u8*)a1 + s0;
        }
    }
    sp60.hdr.pri = 0;
    sp60.hdr.retQueue = &sp48;
    sp60.devAddr = (u32)a0;
    sp60.dramAddr = a1;
    sp60.size = (u32)a2;
    ret = osEPiStartDma(D_80096B40, &sp60, 0);
    if (ret) goto END;

    osRecvMesg(&sp48, NULL, 1);

    osInvalDCache(a1, a2);

END:
    return ret;
}

void Dmamgr_osEPiStartDmaWrapper(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    osEPiStartDma(pihandle, mb, direction);
}

z_DmadataEntry* Dmamgr_FindDmaEntry(u32 a0) {
    z_DmadataEntry* curr;

    for (curr = dmadata; curr->vromEnd != 0; curr++) {
        if (a0 < curr->vromStart) continue;
        if (a0 >= curr->vromEnd) continue;

        return curr;
    }

    return NULL;
}

s32 Dmamgr_TranslateVromToRom(u32 a0) {
    z_DmadataEntry* v0 = Dmamgr_FindDmaEntry(a0);

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

s32 Dmamgr_FindDmaIndex(u32 a0) {
    z_DmadataEntry* v0 = Dmamgr_FindDmaEntry(a0);

    if (v0 != NULL) {
		return v0 - dmadata;
    }

    return -1;
}

UNK_TYPE* func_800809F4(u32 a0) {
    return &D_800981C0;
}

#ifdef NONMATCHING

void Dmamgr_HandleRequest(z_DmaRequest* a0) {
    UNK_TYPE sp34;
    UNK_TYPE sp30;
    UNK_TYPE sp2C;
    UNK_TYPE sp28;
    UNK_TYPE sp24;
    UNK_TYPE sp20;
    s32 sp1C;
    UNK_TYPE sp18;

    sp34 = (UNK_TYPE)a0->unk0;
    sp30 = (UNK_TYPE)a0->unk4;
    sp2C = a0->unk8;

    sp1C = Dmamgr_FindDmaIndex(sp34);

    if ((sp1C >= 0) && (sp1C < D_8009B2BC)) {
        if (dmadata[sp1C].romEnd == 0) {
            if (dmadata[sp1C].vromEnd < (sp2C + sp34)) {
                func_80083E4C(&D_800981C4, 499);
            }
            Dmamgr_DoDmaTransfer((u8*)((dmadata[sp1C].romStart + sp34) - dmadata[sp1C].vromStart), (u8*)sp30, sp2C);
            return;
        }

        // TODO this part is arranged slightly different is ASM
        sp24 = dmadata[sp1C].romEnd - dmadata[sp1C].romStart;
        sp28 = dmadata[sp1C].romStart;

        if (sp34 != dmadata[sp1C].vromStart) {
            func_80083E4C(&D_800981D4, 518);
        }

        if (sp2C != (dmadata[sp1C].vromEnd - dmadata[sp1C].vromStart)) {
            func_80083E4C(&D_800981E4, 525);
        }

        osSetThreadPri(NULL, 10);
        Yaz0_LoadAndDecompressFile(sp28, sp30, sp24);
        osSetThreadPri(NULL, 17);
    } else {
        func_80083E4C(&D_800981F4, 558);
    }
}

#else

GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_HandleRequest.asm")

#endif

#ifdef NONMATCHING

void Dmamgr_ThreadEntry(void* a0) {
    z_DmaRequest* sp34;
	UNK_TYPE pad;
    z_DmaRequest* s0;

    for (;;) {
        osRecvMesg(&D_8009B2C0, (OSMesg)&sp34, 1);
        if (sp34 == NULL) return;
        s0 = sp34;
        Dmamgr_HandleRequest(s0);
        // TODO a0 isn't being used for this comparison
        if (s0->unk18 == NULL) continue;
        osSendMesg(&D_8009B2C0, (OSMesg)s0->unk1C, 0);
    }
}

#else

GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_ThreadEntry.asm")

#endif

#ifdef NONMATCHING

s32 Dmamgr_SendRequest(z_DmaRequest* a0, UNK_FUN_PTR(a1), UNK_PTR a2, UNK_TYPE a3, UNK_TYPE sp30, OSMesgQueue* sp34, UNK_TYPE sp38) {
    // TODO this isn't correct, it uses a lui, addiu to get the address of D_80096B60, then loads it,
	// meaning that this is likely just "if (*D_80096B60 >= 2)". However, I can not get it to not
	// produce the usual lui, lw combo to load from an address :/
    if (*D_80096B60 >= 2) {
        return -2;
    }

    a0->unk0 = a2;
    a0->unk4 = a1;
    a0->unk8 = a3;
    a0->unk14 = 0;
    a0->unk18 = sp34;
    a0->unk1C = sp38;

    osSendMesg(&D_8009B2C0, (OSMesg)a0, 1);

    return 0;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_SendRequest.asm")

#endif

s32 Dmamgr_SendRequestAndWait(UNK_TYPE a0, UNK_PTR a1, UNK_TYPE a2) {
	z_DmaRequest sp48;
    OSMesgQueue sp30;
    OSMesg sp2C;
	s32 ret;

    osCreateMesgQueue(&sp30, &sp2C, 1);

	ret = Dmamgr_SendRequest(&sp48, (UNK_FUN_ARG)a0, a1, a2, 0, &sp30, 0);

	if (ret == -1) {
		return ret;
	} else {
		osRecvMesg(&sp30, NULL, 1);
	}

	return 0;
}

#ifdef NONMATCHING

void Dmamgr_Start() {
	z_DmadataEntry* v0;
	u32 v1;
	// TODO register load ordering is wrong
	Dmamgr_DoDmaTransfer(&dmadataRomStart, dmadata, (u8*)&dmadataRomEnd - (u8*)&dmadataRomStart);

	for (v0 = dmadata, v1 = 0; v0->vromEnd != 0; v0++, v1++);

	D_8009B2BC = (u16)v1;

	osCreateMesgQueue(&D_8009B2C0, (OSMesg)&D_8009B2D8, 32);

	thread_info_init(&D_8009B2A0, &D_8009B508, &D_8009BA08, 0, 256, &D_80098204);

	osCreateThread(&D_8009B358, 18, Dmamgr_ThreadEntry, NULL, &D_8009BA08, 17);

	osStartThread(&D_8009B358);
}

#else

GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_Start.asm")

#endif

void Dmamgr_Stop() {
    osSendMesg(&D_8009B2C0, NULL, 1);
}
