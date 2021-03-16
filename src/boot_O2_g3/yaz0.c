#include <ultra64.h>
#include <global.h>

extern u8 sYaz0DataBuffer[0x400];
extern u8* sYaz0CurDataEnd;
extern u32 sYaz0CurRomStart;
extern u32 sYaz0CurSize;
extern u8* sYaz0MaxPtr;

u8* Yaz0_LoadFirstChunk(void) {
    u32 pad;
    u32 dmaSize;
    u32 curSize;

    sYaz0MaxPtr = sYaz0CurDataEnd - 0x19;

    curSize = sYaz0CurDataEnd - (u32)sYaz0DataBuffer;
    dmaSize = (curSize > sYaz0CurSize) ? sYaz0CurSize : curSize;

    DmaMgr_DMARomToRam(sYaz0CurRomStart, sYaz0DataBuffer, dmaSize);
    sYaz0CurRomStart += dmaSize;
    sYaz0CurSize -= dmaSize;
    return sYaz0DataBuffer;
}

u8* Yaz0_LoadNextChunk(u8* curSrcPos) {
    u8* dst;
    u32 restSize;
    u32 dmaSize;

    restSize = sYaz0CurDataEnd - (u32)curSrcPos;
    dst = (restSize & 7) ? (sYaz0DataBuffer - (restSize & 7)) + 8 : sYaz0DataBuffer;

    _bcopy(curSrcPos, dst, restSize);
    dmaSize = (sYaz0CurDataEnd - (u32)dst) - restSize;
    if (sYaz0CurSize < dmaSize) {
        dmaSize = sYaz0CurSize;
    }

    if (dmaSize != 0) {
        DmaMgr_DMARomToRam(sYaz0CurRomStart, dst + restSize, dmaSize);
        sYaz0CurRomStart += dmaSize;
        sYaz0CurSize -= dmaSize;    
        if (sYaz0CurSize == 0) {
            sYaz0MaxPtr = (dst + restSize + dmaSize);
        }
    } else {
        OSPri pri = osGetThreadPri(NULL);
        osSetThreadPri(NULL, 0x7F);
        Fault_Log(D_80098210);
        osSetThreadPri(NULL, pri);
    }

    return dst;
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/yaz0/Yaz0_Decompress.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/yaz0/Yaz0_LoadAndDecompressFile.asm")
