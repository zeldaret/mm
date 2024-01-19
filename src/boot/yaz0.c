#include "fault.h"
#include "libc64/sprintf.h"
#include "libc64/sleep.h"
#include "z64dma.h"

// Variables are put before most headers as a hacky way to bypass bss reordering
u8 sYaz0DataBuffer[0x400] ALIGNED(16);
u8* sYaz0DataBufferEnd;
uintptr_t sYaz0CurRomStart;
size_t sYaz0CurSize;
u8* sYaz0MaxPtr;

void* gYaz0DecompressDstEnd;

#include "yaz0.h"

void* Yaz0_FirstDMA(void) {
    s32 pad;
    size_t dmaSize;
    size_t bufferSize;

    sYaz0MaxPtr = sYaz0DataBufferEnd - 0x19;

    bufferSize = sYaz0DataBufferEnd - sYaz0DataBuffer;
    dmaSize = (bufferSize > sYaz0CurSize) ? sYaz0CurSize : bufferSize;

    DmaMgr_DmaRomToRam(sYaz0CurRomStart, sYaz0DataBuffer, dmaSize);
    sYaz0CurRomStart += dmaSize;
    sYaz0CurSize -= dmaSize;
    return sYaz0DataBuffer;
}

void* Yaz0_NextDMA(u8* curSrcPos) {
    u8* dst;
    size_t restSize;
    size_t dmaSize;
    OSPri oldPri;

    restSize = sYaz0DataBufferEnd - curSrcPos;
    dst = (restSize & 7) ? (sYaz0DataBuffer - (restSize & 7)) + 8 : sYaz0DataBuffer;

    bcopy(curSrcPos, dst, restSize);
    dmaSize = sYaz0DataBufferEnd - dst - restSize;
    if (sYaz0CurSize < dmaSize) {
        dmaSize = sYaz0CurSize;
    }

    if (dmaSize != 0) {
        DmaMgr_DmaRomToRam(sYaz0CurRomStart, dst + restSize, dmaSize);
        sYaz0CurRomStart += dmaSize;
        sYaz0CurSize -= dmaSize;
        if (sYaz0CurSize == 0) {
            sYaz0MaxPtr = dst + restSize + dmaSize;
        }
    } else {
        oldPri = osGetThreadPri(NULL);
        osSetThreadPri(NULL, OS_PRIORITY_APPMAX);
        // Compression/decompression error
        osSyncPrintf("圧縮展開異常\n");
        osSetThreadPri(NULL, oldPri);
    }

    return dst;
}

#define YAZ0_MAGIC 0x59617A30 // 'Yaz0'

typedef struct {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 decSize;
    /* 0x8 */ u32 compInfoOffset;   // only used in mio0
    /* 0xC */ u32 uncompDataOffset; // only used in mio0
} Yaz0Header;                       // size = 0x10

s32 Yaz0_DecompressImpl(u8* src, u8* dst) {
    u32 bitIndex = 0;
    u8* dstEnd;
    u32 chunkHeader = 0;
    u32 nibble;
    u8* backPtr;
    size_t chunkSize;
    u32 off;
    u32 magic = ((Yaz0Header*)src)->magic;

    if (magic != YAZ0_MAGIC) {
        return -1;
    }

    dstEnd = dst + ((Yaz0Header*)src)->decSize;
    src += sizeof(Yaz0Header);

    do {
        if (bitIndex == 0) {
            if ((sYaz0MaxPtr < src) && (sYaz0CurSize != 0)) {
                src = Yaz0_NextDMA(src);
            }

            chunkHeader = *src++;
            bitIndex = 8;
        }

        if (chunkHeader & (1 << 7)) { // uncompressed
            *dst = *src;
            dst++;
            src++;
        } else { // compressed
            off = ((*src & 0xF) << 8) | *(src + 1);
            nibble = *src >> 4;
            backPtr = dst - off;
            src += 2;

            // N = chunkSize; B = back offset
            // 3 bytes 0B BB NN
            // 2 bytes NB BB
            chunkSize = (nibble == 0) ? *src++ + 0x12 : nibble + 2;

            do {
                *dst++ = *(backPtr++ - 1);
                chunkSize--;
            } while (chunkSize != 0);
        }
        chunkHeader <<= 1;
        bitIndex--;
    } while (dst != dstEnd);

    gYaz0DecompressDstEnd = dstEnd;

    return 0;
}

void Yaz0_Decompress(uintptr_t romStart, void* dst, size_t size) {
    s32 status;
    s32 pad;
    char exp1[80];
    char exp2[80];

    if (sYaz0DataBufferEnd != NULL) {
        while (sYaz0DataBufferEnd != NULL) {
            usleep(10);
        }
    }

    sYaz0DataBufferEnd = sYaz0DataBuffer + sizeof(sYaz0DataBuffer);
    sYaz0CurRomStart = romStart;
    sYaz0CurSize = size;
    status = Yaz0_DecompressImpl(Yaz0_FirstDMA(), dst);

    if (status != 0) {
        sprintf(exp1, "slidma slidstart_szs ret=%d", status);
        sprintf(exp2, "src:%08lx dst:%08lx siz:%08lx", romStart, dst, size);
        Fault_AddHungupAndCrashImpl(exp1, exp2);
    }

    sYaz0DataBufferEnd = NULL;
}
