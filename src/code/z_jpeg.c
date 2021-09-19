#include "global.h"
#include "z64jpeg.h"
#include "vt.h"

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
#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F42A0.s")
#endif

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F43BC.s")
// Jpeg_CopyToZbuffer
void func_800F43BC(u16* src, u16* zbuffer, s32 x, s32 y) {
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


#define Jpeg_GetUnalignedU16 func_800F44F4
//#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F44F4.s")
u16 func_800F44F4(u8* ptr) {
    if (((u32)ptr & 1) == 0) {
        // Read the value normally if it's aligned to a 16-bit address.
        return *(u16*)ptr;
    } else {
        // Read unaligned values using two separate aligned memory accesses when it's not.
        return *(u16*)(ptr - 1) << 8 | (*(u16*)(ptr + 1) >> 8);
    }
}


//#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F4540.s")
// Jpeg_ParseMarkers
void func_800F4540(u8* ptr, JpegContext* ctx) {
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
                  // osSyncPrintf("MARKER_SOI\n");
                    break;
                }
                case MARKER_APP0: {
                    // Application marker for JFIF
                  // osSyncPrintf("MARKER_APP0 %d\n", Jpeg_GetUnalignedU16(ptr));
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_APP1: {
                    // Application marker for EXIF
                  // osSyncPrintf("MARKER_APP1 %d\n", Jpeg_GetUnalignedU16(ptr));
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_APP2: {
                  // osSyncPrintf("MARKER_APP2 %d\n", Jpeg_GetUnalignedU16(ptr));
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DQT: {
                    // Define Quantization Table, stored for later processing
                  // osSyncPrintf("MARKER_DQT %d %d %02x\n", ctx->dqtCount, Jpeg_GetUnalignedU16(ptr), ptr[2]);
                    ctx->dqtPtr[ctx->dqtCount++] = ptr + 2;
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DHT: {
                    // Define Huffman Table, stored for later processing
                  // osSyncPrintf("MARKER_DHT %d %d %02x\n", ctx->dhtCount, Jpeg_GetUnalignedU16(ptr), ptr[2]);
                    ctx->dhtPtr[ctx->dhtCount++] = ptr + 2;
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_DRI: {
                    // Define Restart Interval
                  // osSyncPrintf("MARKER_DRI %d\n", Jpeg_GetUnalignedU16(ptr));
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
                case MARKER_SOF: {
                    // Start of Frame, stores important metadata of the image.
                    // Only used for extracting the sampling factors (ctx->mode).
                  // osSyncPrintf("MARKER_SOF   %d "
                  //               "精度%02x " // accuracy
                  //               "垂直%d "   // vertical
                  //               "水平%d "   // horizontal
                  //               "compo%02x "
                  //               "(1:Y)%d (H0=2,V0=1(422) or 2(420))%02x (量子化テーブル)%02x "
                  //               "(2:Cb)%d (H1=1,V1=1)%02x (量子化テーブル)%02x "
                  //               "(3:Cr)%d (H2=1,V2=1)%02x (量子化テーブル)%02x\n",
                  //               Jpeg_GetUnalignedU16(ptr),
                  //               ptr[2],                        // precision
                  //               Jpeg_GetUnalignedU16(ptr + 3), // height
                  //               Jpeg_GetUnalignedU16(ptr + 5), // width
                  //               ptr[7],                        // component count (assumed to be 3)
                  //               ptr[8], ptr[9], ptr[10],       // Y component
                  //               ptr[11], ptr[12], ptr[13],     // Cb component
                  //               ptr[14], ptr[15], ptr[16]      // Cr component
                  //  );


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
                  // osSyncPrintf("MARKER_SOS %d\n", Jpeg_GetUnalignedU16(ptr));
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    ctx->imageData = ptr;
                    break;
                }
                case MARKER_EOI: {
                    // End of Image
                  // osSyncPrintf("MARKER_EOI\n");
                    exit = true;
                    break;
                }
                default: {
                  // osSyncPrintf("マーカー不明 %02x\n", ptr[-1]); // "Unknown marker"
                    ptr += Jpeg_GetUnalignedU16(ptr);
                    break;
                }
            }
        }
    }
}


#if 0
// #ifdef MIPS2C_OUTPUT
// ? func_800F42A0(u8*); // extern
// ? func_800F43BC(s32, ?, s32, s32); // extern
// ? func_800F4540(s32, u8*); // extern
// ? func_8010C1B0(); // extern
// ? func_801A9B10(s32, s32, ?); // extern
// s32 func_801A9DCC(s32, ?*, s32, s32, s32); // extern
// s32 func_801AA020(s32*, s32, ?, s32, ?*); // extern

s32 func_800F470C(s32 arg0, void* arg1, s32 arg2, u32 arg3) {
    // s32 sp27C;
    // void* sp278;
    // OSMesgQueue sp260;
    // u8 sp1D8;

    JpegContext ctx;

    // UNK_TYPE1 sp184[0x54];
    // UNK_TYPE1 sp130[0x54];
    // UNK_TYPE1 spDC[0x54];
    // UNK_TYPE1 sp88[0x54];
    JpegHuffmanTable hTables[4];

    // s8 sp84;
    // UNK_PTR sp80;
    // UNK_PTR sp7C;
    // UNK_PTR sp78;
    // UNK_PTR sp74;
    // s8 sp71;
    // u8 sp70;
    JpegDecoder decoder;

    s32 sp6C;
    UNK_TYPE1 sp58[0x14];
    s32 sp44;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s6;
    s32 phi_s6;
    s32 phi_s1;
    s32 phi_s2;
    s32 phi_s3;
    s32 phi_s0;
    s32 phi_s2_2;
    s32 phi_s2_3;
    s32 phi_s3_2;
    s32 phi_s3_3;

    if (arg3 < 0x12C0U) {
        return -1;
    }

    //osCreateMesgQueue(&sp260, &sp278, 1);
    osCreateMesgQueue(&ctx.mq, &ctx.msg, 1);

    func_8010C1B0();
    sp27C = arg2;
    func_800F4540(arg0, &sp1D8);
    if (sp1D8 != 1) {
        if (sp1D8 != 2) {
            if (sp1D8 != 3) {
                return -1;
            }
            func_801A9B10(sp1DC, arg2 + 0x220, 1);
            func_801A9B10(sp1E0, arg2 + 0x2A0, 1);
            func_801A9B10(sp1E4, arg2 + 0x320, 1);
            goto block_10;
        }
        func_801A9B10(sp1DC, arg2 + 0x220, 1);
        func_801A9B10(sp1E0, arg2 + 0x2A0, 1);
        func_801A9B10(sp1E0, arg2 + 0x320, 1);
        goto block_10;
    }
    func_801A9B10(sp1DC, arg2 + 0x220, 3);
block_10:
    if (sp1E8 != 1) {
        if (sp1E8 != 4) {
            return -1;
        }
        temp_s0 = arg2 + 0x3A0;
        temp_s1 = arg2 + 0x4B0;
        if ((func_801A9DCC(sp1EC, &sp88, temp_s0, temp_s1, 1) != 0) || (func_801A9DCC(sp1F0, &spDC, temp_s0, temp_s1, 1) != 0) || (func_801A9DCC(sp1F4, &sp130, temp_s0, temp_s1, 1) != 0) || (func_801A9DCC(sp1F8, &sp184, temp_s0, temp_s1, 1) != 0)) {
            return -1;
        }
        goto block_21;
    }
    if (func_801A9DCC(sp1EC, &sp88, arg2 + 0x3A0, arg2 + 0x4B0, 4) != 0) {
        return -1;
    }
block_21:
    sp74 = &sp88;
    sp71 = 2;
    sp78 = &spDC;
    sp7C = &sp130;
    sp80 = &sp184;
    sp84 = 0;
    sp44 = arg2 + 0x6C0;
    sp6C = sp1FC;
    sp70 = sp200;
    phi_s6 = 0;
    phi_s2_2 = 0;
    phi_s2_3 = 0;
    phi_s3_2 = 0;
    do {
        phi_s2 = phi_s2_2;
        phi_s3 = phi_s3_2;
        if (func_801AA020(&sp6C, sp44, 4, (phi_s6 != 0) & 0xFF, &sp58) == 0) {
            func_800F42A0(&sp1D8);
            phi_s1 = arg2 + 0x6C0;
            phi_s0 = 0;
            do {
                func_800F43BC(phi_s1, arg1, phi_s2, phi_s3);
                temp_s2 = phi_s2 + 1;
                temp_s0_2 = phi_s0 + 0x300;
                phi_s0 = temp_s0_2;
                phi_s2_3 = temp_s2;
                phi_s3_3 = phi_s3;
                if (temp_s2 >= 0x14) {
                    phi_s3_3 = phi_s3 + 1;
                }
                phi_s1 += 0x300;
                phi_s2 = phi_s2_3;
                phi_s3 = phi_s3_3;
                phi_s2_2 = phi_s2_3;
                phi_s3_2 = phi_s3_3;
            } while (temp_s0_2 != 0xC00);
        }
        temp_s6 = phi_s6 + 4;
        phi_s6 = temp_s6;
    } while (temp_s6 != 0x12C);
    return 0;
}
//#else
//#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F470C.s")
//#endif
#endif
#pragma GLOBAL_ASM("asm/non_matchings/code/z_jpeg/func_800F470C.s")

#if 0
// Jpeg_Decode
s32 func_800F470C(void* data, void* zbuffer, void* work, u32 workSize) {
    s32 y;
    s32 x;
    u32 j;
    u32 i;
    JpegContext ctx;
    JpegHuffmanTable hTables[4];
    JpegDecoder decoder;
    JpegDecoderState state;
    JpegWork* workBuff;
    // OSTime diff;
    // OSTime time;
    // OSTime curTime;

    workBuff = work;

    //time = osGetTime();
    // (?) I guess MB_SIZE=0x180, PROC_OF_MBS=5 which means data is not a part of JpegWork
    // ASSERT(workSize >= sizeof(JpegWork), "worksize >= sizeof(JPEGWork) + MB_SIZE * (PROC_OF_MBS - 1)", "../z_jpeg.c",
    //        527);

    osCreateMesgQueue(&ctx.mq, &ctx.msg, 1);
    MsgEvent_SendNullTask();

    //curTime = osGetTime();
    //diff = curTime - time;
    //time = curTime;
    // "Wait for synchronization of fifo buffer"
    // osSyncPrintf("*** fifoバッファの同期待ち time = %6.3f ms ***\n", OS_CYCLES_TO_USEC(diff) / 1000.0f);

    ctx.workBuf = workBuff;
    Jpeg_ParseMarkers(data, &ctx);

    // curTime = osGetTime();
    // diff = curTime - time;
    // time = curTime;
    // "Check markers for each segment"
    // osSyncPrintf("*** 各セグメントのマーカーのチェック time = %6.3f ms ***\n", OS_CYCLES_TO_USEC(diff) / 1000.0f);

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

    // curTime = osGetTime();
    // diff = curTime - time;
    // time = curTime;
    // "Create quantization table"
    //osSyncPrintf("*** 量子化テーブル作成 time = %6.3f ms ***\n", OS_CYCLES_TO_USEC(diff) / 1000.0f);

    switch (ctx.dhtCount) {
        case 1:
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[0], &hTables[0], workBuff->codesLengths, workBuff->codes, 4)) {
                //osSyncPrintf("Error : Cant' make huffman table.\n");
            }
            break;
        case 4:
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[0], &hTables[0], workBuff->codesLengths, workBuff->codes, 1)) {
                //osSyncPrintf("Error : Cant' make huffman table.\n");
            }
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[1], &hTables[1], workBuff->codesLengths, workBuff->codes, 1)) {
                //osSyncPrintf("Error : Cant' make huffman table.\n");
            }
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[2], &hTables[2], workBuff->codesLengths, workBuff->codes, 1)) {
                //osSyncPrintf("Error : Cant' make huffman table.\n");
            }
            if (JpegUtils_ProcessHuffmanTable(ctx.dhtPtr[3], &hTables[3], workBuff->codesLengths, workBuff->codes, 1)) {
                //osSyncPrintf("Error : Cant' make huffman table.\n");
            }
            break;
        default:
            return -1;
    }

    // curTime = osGetTime();
    // diff = curTime - time;
    // time = curTime;
    // "Huffman table creation"
    // osSyncPrintf("*** ハフマンテーブル作成 time = %6.3f ms ***\n", OS_CYCLES_TO_USEC(diff) / 1000.0f);

    decoder.imageData = ctx.imageData;
    decoder.mode = ctx.mode;
    decoder.unk_05 = 2;
    decoder.hTablePtrs[0] = &hTables[0];
    decoder.hTablePtrs[1] = &hTables[1];
    decoder.hTablePtrs[2] = &hTables[2];
    decoder.hTablePtrs[3] = &hTables[3];
    decoder.unk_18 = 0;

    x = y = 0;
    for (i = 0; i < 300; i += 4) {
        if (JpegDecoder_Decode(&decoder, (u16*)workBuff->data, 4, i != 0, &state)) {
            //osSyncPrintf(VT_FGCOL(RED));
            //osSyncPrintf("Error : Can't decode jpeg\n");
            //osSyncPrintf(VT_RST);
        } else {
            Jpeg_ScheduleDecoderTask(&ctx);
            // osInvalDCache(&workBuff->data, sizeof(workBuff->data[0]));

            for (j = 0; j < ARRAY_COUNT(workBuff->data); j++) {
                Jpeg_CopyToZbuffer(workBuff->data[j], zbuffer, x, y);
                x++;

                if (x >= 20) {
                    x = 0;
                    y++;
                }
            }
        }
    }

    //curTime = osGetTime();
    //diff = curTime - time;
    //time = curTime;
    // "Unfold & draw"
    //osSyncPrintf("*** 展開 & 描画 time = %6.3f ms ***\n", OS_CYCLES_TO_USEC(diff) / 1000.0f);

    return 0;
}
#endif
