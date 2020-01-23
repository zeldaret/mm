#include <ultra64.h>
#include <global.h>

s32 Dmamgr_DoDmaTransfer(u32 a0, void* a1, u32 a2) {
    OSIoMesg sp60;
    OSMesgQueue sp48;
    OSMesg sp44;
    s32 ret;
    u32 s0 = dmamgrChunkSize;

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
            a0 = a0 + s0;
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

DmadataEntry* Dmamgr_FindDmaEntry(u32 a0) {
    DmadataEntry* curr;

    for (curr = dmadata; curr->vromEnd != 0; curr++) {
        if (a0 < curr->vromStart) continue;
        if (a0 >= curr->vromEnd) continue;

        return curr;
    }

    return NULL;
}

u32 Dmamgr_TranslateVromToRom(u32 a0) {
    DmadataEntry* v0 = Dmamgr_FindDmaEntry(a0);

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
    DmadataEntry* v0 = Dmamgr_FindDmaEntry(a0);

    if (v0 != NULL) {
		return v0 - dmadata;
    }

    return -1;
}

// TODO this should be a string
char* func_800809F4(u32 a0) {
    return &D_800981C0[0];
}

#ifdef NON_MATCHING
void Dmamgr_HandleRequest(DmaRequest* a0) {
    u32 sp34;
    u32 sp30;
    UNK_TYPE sp2C;
    UNK_TYPE sp28;
    UNK_TYPE sp24;
    UNK_TYPE sp20;
    s32 sp1C;
    UNK_TYPE sp18;

    sp34 = a0->vromStart;
    sp30 = a0->vramStart;
    sp2C = a0->size;

    sp1C = Dmamgr_FindDmaIndex(sp34);

    if ((sp1C >= 0) && (sp1C < numDmaEntries)) {
        if (dmadata[sp1C].romEnd == 0) {
            if (dmadata[sp1C].vromEnd < (sp2C + sp34)) {
                Fault_AddHungupAndCrash(dmamgrString800981C4, 499);
            }
            Dmamgr_DoDmaTransfer((dmadata[sp1C].romStart + sp34) - dmadata[sp1C].vromStart, (u8*)sp30, sp2C);
            return;
        }

        // TODO this part is arranged slightly different is ASM
        sp24 = dmadata[sp1C].romEnd - dmadata[sp1C].romStart;
        sp28 = dmadata[sp1C].romStart;

        if (sp34 != dmadata[sp1C].vromStart) {
            Fault_AddHungupAndCrash(dmamgrString800981D4, 518);
        }

        if (sp2C != (dmadata[sp1C].vromEnd - dmadata[sp1C].vromStart)) {
            Fault_AddHungupAndCrash(dmamgrString800981E4, 525);
        }

        osSetThreadPri(NULL, 10);
        Yaz0_LoadAndDecompressFile(sp28, sp30, sp24);
        osSetThreadPri(NULL, 17);
    } else {
        Fault_AddHungupAndCrash(dmamgrString800981F4, 558);
    }
}
#else
GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_HandleRequest.asm")
#endif

void Dmamgr_ThreadEntry(void* a0) {
    OSMesg sp34;
	u32 pad;
    DmaRequest* s0;

    for (;;) {
        osRecvMesg(&dmamgrMsq, &sp34, 1);
        if (sp34 == NULL) return;
        s0 = (DmaRequest*)sp34;
        Dmamgr_HandleRequest(s0);
        if (s0->callback == NULL) continue;
        osSendMesg(s0->callback, s0->callbackMesg, 0);
    }
}

s32 Dmamgr_SendRequest(DmaRequest* request, u32 vramStart, u32 vromStart, u32 size, UNK_TYPE4 unused, OSMesgQueue* callback, void* callbackMesg) {
    if (gPrenmiStage >= 2) {
        return -2;
    }

    request->vromStart = vromStart;
    request->vramStart = vramStart;
    request->size = size;
    request->unk14 = 0;
    request->callback = callback;
    request->callbackMesg = callbackMesg;

    osSendMesg(&dmamgrMsq, request, 1);

    return 0;
}

s32 Dmamgr_SendRequestAndWait(u32 a0, u32 a1, u32 a2) {
	DmaRequest sp48;
    OSMesgQueue sp30;
    OSMesg sp2C;
	s32 ret;

    osCreateMesgQueue(&sp30, &sp2C, 1);

	ret = Dmamgr_SendRequest(&sp48, a0, a1, a2, 0, &sp30, 0);

	if (ret == -1) {
		return ret;
	} else {
		osRecvMesg(&sp30, NULL, 1);
	}

	return 0;
}

#ifdef NON_MATCHING
// TODO missing a useless move initializing v0, and some reorderings
void Dmamgr_Start() {
	DmadataEntry* v0;
	u32 v1;
	Dmamgr_DoDmaTransfer((u32)&dmadata_vrom_start, dmadata, (u32)&dmadata_vrom_end - (u32)&dmadata_vrom_start);

	for (v0 = dmadata, v1 = 0; v0->vromEnd != 0; v0++, v1++);

	numDmaEntries = v1;

	osCreateMesgQueue(&dmamgrMsq, dmamgrMsqMessages, 32);

	StackCheck_Init(&dmamgrStackEntry, (u32)&dmamgrStack, (u32)&dmamgrStack[1280], 0, 256, dmamgrThreadName);

	osCreateThread(&dmamgrOSThread, 18, Dmamgr_ThreadEntry, NULL, &dmamgrStack[1280], 17);

	osStartThread(&dmamgrOSThread);
}
#else
GLOBAL_ASM("./asm/nonmatching/z_std_dma/Dmamgr_Start.asm")
#endif

void Dmamgr_Stop() {
    osSendMesg(&dmamgrMsq, NULL, 1);
}
