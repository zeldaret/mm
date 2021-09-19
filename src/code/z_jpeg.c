#include "global.h"
#include "vt.h"

#define MARKER_ESCAPE 0x00
#define MARKER_SOI 0xD8
#define MARKER_SOF 0xC0
#define MARKER_DHT 0xC4
#define MARKER_DQT 0xDB
#define MARKER_DRI 0xDD
#define MARKER_SOS 0xDA
#define MARKER_APP0 0xE0
#define MARKER_APP1 0xE1
#define MARKER_APP2 0xE2
#define MARKER_COM 0xFE
#define MARKER_EOI 0xD9

void func_800F42A0(JpegContext* ctx);

#if 0
extern OSTask_t sJpegTask;
// Jpeg_ScheduleDecoderTask
void func_800F42A0(JpegContext* ctx) {
    // static OSTask_t sJpegTask = {
    //     M_NJPEGTASK,          // type
    //     0,                    // flags
    //     NULL,                 // ucode_boot
    //     0,                    // ucode_boot_size
    //     gJpegUCode,           // ucode
    //     0x1000,               // ucode_size
    //     gJpegUCodeData,       // ucode_data
    //     0x800,                // ucode_data_size
    //     NULL,                 // dram_stack
    //     0,                    // dram_stack_size
    //     NULL,                 // output_buff
    //     NULL,                 // output_buff_size
    //     NULL,                 // data_ptr
    //     sizeof(JpegTaskData), // data_size
    //     NULL,                 // yield_data_ptr
    //     0x200,                // yield_data_size
    // };

    JpegWork* workBuf = ctx->workBuf;
    s32 pad[2];

    workBuf->taskData.address = PHYSICAL_TO_VIRTUAL(&workBuf->data);
    workBuf->taskData.mode = ctx->mode;
    workBuf->taskData.mbCount = 4;
    workBuf->taskData.qTableYPtr = PHYSICAL_TO_VIRTUAL(&workBuf->qTableY);
    workBuf->taskData.qTableUPtr = PHYSICAL_TO_VIRTUAL(&workBuf->qTableU);
    workBuf->taskData.qTableVPtr = PHYSICAL_TO_VIRTUAL(&workBuf->qTableV);

    sJpegTask.flags = 0;
    sJpegTask.ucode_boot = SysUcode_GetUCodeBoot();
    sJpegTask.ucode_boot_size = SysUcode_GetUCodeBootSize();
    sJpegTask.yield_data_ptr = (u64*)&workBuf->yieldData;
    sJpegTask.data_ptr = (u64*)&workBuf->taskData;

    ctx->scTask.next = NULL;
    ctx->scTask.flags = OS_SC_NEEDS_RSP;
    ctx->scTask.msgQ = &ctx->mq;
    ctx->scTask.msg = NULL;
    ctx->scTask.framebuffer = NULL;
    ctx->scTask.list.t = sJpegTask;

    osSendMesg(&gSchedContext.cmdQ, (OSMesg)&ctx->scTask, OS_MESG_BLOCK);
    Sched_SendEntryMsg(&gSchedContext); // osScKickEntryMsg
    osRecvMesg(&ctx->mq, NULL, OS_MESG_BLOCK);
}
#else
//#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F42A0.s")
#endif

#if 0
extern s32 D_801BDAC0;
extern s32 D_801BDAC4;
extern s32 D_801BDAC8;
extern s32 D_801BDACC;
extern s8* D_801BDAF0;

void func_800F42A0(JpegContext* ctx) {
    JpegWork* sp24;
    OSMesgQueue* sp18;
    JpegContext* temp_t8;
    JpegWork* temp_v1;
    OSMesgQueue* temp_t0;
    s32* temp_t5;
    s32* phi_t5;
    JpegContext* phi_t8;

    temp_v1 = ctx->workBuf;
    temp_v1->taskData.address = (u32) temp_v1->data;
    temp_v1->taskData.mbCount = 4;
    temp_v1->taskData.qTableYPtr = (u32) &temp_v1->qTableY;
    temp_v1->taskData.qTableUPtr = (u32) &temp_v1->qTableU;
    temp_v1->taskData.qTableVPtr = (u32) &temp_v1->qTableV;
    temp_v1->taskData.mode = (u32) ctx->mode;
    D_801BDAC4 = 0;
    ctx = ctx;
    sp24 = temp_v1;
    D_801BDAC8 = func_80182C90();
    D_801BDACC = func_80182CA0();
    D_801BDAF0 = (s8* ) temp_v1->yieldData;
    D_801BDAF0 = (s8* ) temp_v1;
    temp_t0 = &ctx->mq;
    ctx->scTask.next = NULL;
    ctx->scTask.flags = 2;
    ctx->scTask.msgQ = temp_t0;
    ctx->scTask.msg = NULL;
    ctx->scTask.framebuffer = NULL;
    phi_t5 = &D_801BDAC0;
    phi_t8 = ctx;
    do {
        temp_t5 = phi_t5 + 0xC;
        temp_t8 = phi_t8 + 0xC;
        temp_t8->scTask.state = *phi_t5;
        temp_t8->scTask.flags = temp_t5->unk_-8;
        temp_t8->scTask.framebuffer = temp_t5->unk_-4;
        phi_t5 = temp_t5;
        phi_t8 = temp_t8;
    } while (temp_t5 != (&D_801BDAC0 + 0x3C));
    temp_t8->scTask.list.t.type = temp_t5->unk_0;
    sp18 = temp_t0;
    osSendMesg(&gSchedContext.cmdQ, (void* ) &ctx->scTask, 1);
    Sched_SendEntryMsg(&gSchedContext);
    osRecvMesg(sp18, NULL, 1);
}
#endif

extern u64 D_801AD370[];
extern u64 D_801E3F40[];


void func_800F42A0(JpegContext* ctx) {
    static OSTask_t sJpegTask = {
        M_NJPEGTASK,          // type
        0,                    // flags
        NULL,                 // ucode_boot
        0,                    // ucode_boot_size
        //gJpegUCode,           // ucode
        D_801AD370,
        0x1000,               // ucode_size
        //gJpegUCodeData,       // ucode_data
        D_801E3F40,
        0x800,                // ucode_data_size
        NULL,                 // dram_stack
        0,                    // dram_stack_size
        NULL,                 // output_buff
        NULL,                 // output_buff_size
        NULL,                 // data_ptr
        sizeof(JpegTaskData), // data_size
        NULL,                 // yield_data_ptr
        0x200,                // yield_data_size
    };

    JpegWork* workBuf = ctx->workBuf;
    s32 pad[2];

    workBuf->taskData.address = &workBuf->data;
    workBuf->taskData.mode = ctx->mode;
    workBuf->taskData.mbCount = 4;
    workBuf->taskData.qTableYPtr = &workBuf->qTableY;
    workBuf->taskData.qTableUPtr = &workBuf->qTableU;
    workBuf->taskData.qTableVPtr = &workBuf->qTableV;

    sJpegTask.flags = 0;
    sJpegTask.ucode_boot = func_80182C90();//SysUcode_GetUCodeBoot();
    sJpegTask.ucode_boot_size = func_80182CA0();//SysUcode_GetUCodeBootSize();
    sJpegTask.yield_data_ptr = (u64*)&workBuf->yieldData;
    sJpegTask.data_ptr = (u64*)&workBuf->taskData;

    ctx->scTask.next = NULL;
    ctx->scTask.flags = OS_SC_NEEDS_RSP;
    ctx->scTask.msgQ = &ctx->mq;
    ctx->scTask.msg = NULL;
    ctx->scTask.framebuffer = NULL;
    ctx->scTask.list.t = sJpegTask;

    osSendMesg(&gSchedContext.cmdQ, (OSMesg)&ctx->scTask, OS_MESG_BLOCK);
    Sched_SendEntryMsg(&gSchedContext); // osScKickEntryMsg
    osRecvMesg(&ctx->mq, NULL, OS_MESG_BLOCK);
}


void Jpeg_CopyToZbuffer(u16* src, u16* zbuffer, s32 x, s32 y) {
    u16* dst = zbuffer + (((y * SCREEN_WIDTH) + x) * 16);
    s32 i;

    for (i = 0; i < 16; i++) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        dst[8] = src[8];
        dst[9] = src[9];
        dst[10] = src[10];
        dst[11] = src[11];
        dst[12] = src[12];
        dst[13] = src[13];
        dst[14] = src[14];
        dst[15] = src[15];

        src += 16;
        dst += SCREEN_WIDTH;
    }
}

u16 Jpeg_GetUnalignedU16(u8* ptr) {
    if (((u32)ptr & 1) == 0) {
        // Read the value normally if it's aligned to a 16-bit address.
        return *(u16*)ptr;
    } else {
        // Read unaligned values using two separate aligned memory accesses when it's not.
        return *(u16*)(ptr - 1) << 8 | (*(u16*)(ptr + 1) >> 8);
    }
}

void Jpeg_ParseMarkers(u8* ptr, JpegContext* ctx) {
    u32 exit = false;

    ctx->dqtCount = 0;
    ctx->dhtCount = 0;

    while (true) {
        if (exit) {
            break;
        }

        // 0xFF indicates the start of a JPEG marker, so look for the next.
        if (*ptr++ == 0xFF) {
            switch (*ptr++) {
                case MARKER_ESCAPE: {
                    // Compressed value 0xFF is stored as 0xFF00 to escape it, so ignore it.
                    break;
                }
                case MARKER_SOI: {
                    // Start of Image
                    break;
                }
                case MARKER_APP0: {
                    // Application marker for JFIF
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_APP1: {
                    // Application marker for EXIF
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_APP2: {
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DQT: {
                    // Define Quantization Table, stored for later processing
                    ctx->dqtPtr[ctx->dqtCount++] = ptr + 2;
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DHT: {
                    // Define Huffman Table, stored for later processing
                    ctx->dhtPtr[ctx->dhtCount++] = ptr + 2;
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DRI: {
                    // Define Restart Interval
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_SOF: {
                    // Start of Frame, stores important metadata of the image.
                    // Only used for extracting the sampling factors (ctx->mode).

                    if (ptr[9] == 0x21) {
                        // component Y : V0 == 1
                        ctx->mode = 0;
                    } else if (ptr[9] == 0x22) {
                        // component Y : V0 == 2
                        ctx->mode = 2;
                    }
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_SOS: {
                    // Start of Scan marker, indicates the start of the image data.
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    ctx->imageData = ptr;
                    break;
                }
                case MARKER_EOI: {
                    // End of Image
                    exit = true;
                    break;
                }
                default: {
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
            }
        }
    }
}

s32 Jpeg_Decode(void* data, void* zbuffer, void* work, u32 workSize) {
    s32 y;
    s32 x;
    s32 j;
    s32 i;
    JpegContext ctx;
    JpegHuffmanTable hTables[4];
    JpegDecoder decoder;
    JpegDecoderState state;
    JpegWork* workBuff = work;

    if (workSize < sizeof(JpegWork)) {
        return -1;
    }

    osCreateMesgQueue(&ctx.mq, &ctx.msg, 1);
    MsgEvent_SendNullTask();

    ctx.workBuf = workBuff;

    Jpeg_ParseMarkers(data, &ctx);

    switch (ctx.dqtCount) {
        case 1:
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[0], &workBuff->qTableY, 3);
            break;

        case 2:
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[0], &workBuff->qTableY, 1);
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[1], &workBuff->qTableU, 1);
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[1], &workBuff->qTableV, 1);
            break;

        case 3:
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[0], &workBuff->qTableY, 1);
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[1], &workBuff->qTableU, 1);
            JpegUtils_ProcessQuantizationTable(ctx.dqtPtr[2], &workBuff->qTableV, 1);
            break;


        default:
            return -1;
    }

    switch (ctx.dhtCount) {
        case 1:
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[0], &hTables[0], workBuff->codesLengths, workBuff->codes, 4) != 0) {
                return -1;
            }
            break;

        case 4:
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[0], &hTables[0], workBuff->codesLengths, workBuff->codes, 1)) {
            } else if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[1], &hTables[1], workBuff->codesLengths, workBuff->codes, 1)){
            } else if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[2], &hTables[2], workBuff->codesLengths, workBuff->codes, 1)) {
            } else if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[3], &hTables[3], workBuff->codesLengths, workBuff->codes, 1)==0) {
                break;
            }
            return -1;

        default:
            return -1;
    }

    decoder.imageData = ctx.imageData;
    decoder.mode = ctx.mode;
    decoder.unk_05 = 2;

    decoder.hTablePtrs[0] = &hTables[0];
    decoder.hTablePtrs[1] = &hTables[1];
    decoder.hTablePtrs[2] = &hTables[2];
    decoder.hTablePtrs[3] = &hTables[3];
    decoder.unk_18 = 0;

    x = y = 0;
    for (i = 0; i < 300; i+=4) {
        if (!JpegDecoder_Decode(&decoder, (u16*)workBuff->data, 4, (i != 0), &state)) {
            func_800F42A0(&ctx);

            for (j = 0; j < 4; j++) {
               Jpeg_CopyToZbuffer(workBuff->data[j], zbuffer, x, y);
               x++;

               if (x >= 20) {
                   x = 0;
                   y++;
               }
           }
        }
    }

    return 0;
}
