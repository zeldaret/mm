#include "CIC6105.h"

#include "build.h"
#include "fault.h"
#include "macros.h"
#include "regs.h"
#include "scheduler.h"

#pragma increment_block_number "n64-us:188"

// TODO: Consider moving to a header file.
extern u64 cic6105TextStart[];
extern u64 cic6105TextEnd[];

s32 gCICAddr1Val;
s32 gCICAddr2Val;
FaultClient sRomInfoFaultClient;
#if MM_VERSION <= N64_JP_1_1
s32 gCICValue1;
s32 gCICValue2;

s32 CIC6105_ILoveYou(void);
#endif

void CIC6105_Noop1(void) {
#if MM_VERSION < N64_US
    SREG(20) = 1;
#endif
}

void CIC6105_Noop2(void) {
#if MM_VERSION < N64_US
    SREG(20) = 0;
#endif
}

void CIC6105_PrintRomInfo(void) {
#if MM_VERSION >= N64_US
    FaultDrawer_DrawText(80, 200, "SP_STATUS %08x", IO_READ(SP_STATUS_REG));
    FaultDrawer_DrawText(40, 184, "ROM_F [Creator:%s]", gBuildCreator);
    FaultDrawer_DrawText(56, 192, "[Date:%s]", gBuildDate);
#else
    u32 status = IO_READ(SP_STATUS_REG);

    FaultDrawer_SetCursor(48, 200);
    if (status & SP_STATUS_SIG7) {
        FaultDrawer_Printf("OCARINA %08x %08x", gCICValue1, gCICValue2);
    } else {
        FaultDrawer_Printf("LEGEND %08x %08x", gCICValue1, gCICValue2);
    }
    FaultDrawer_SetCursor(40, 184);
    FaultDrawer_Printf("ROM_F");
    FaultDrawer_Printf(" [Creator:%s]", gBuildCreator);
    FaultDrawer_SetCursor(56, 192);
    FaultDrawer_Printf("[Date:%s]", gBuildDate);
    FaultDrawer_SetCursor(96, 32);
    FaultDrawer_Printf("I LOVE YOU %08x", CIC6105_ILoveYou());

    {
        // TODO: where to put this?
        static const char unused[] = "flag:%08x data:%08x\n";
    }
#endif
}

void CIC6105_AddRomInfoFaultPage(void) {
    Fault_AddClient(&sRomInfoFaultClient, (void*)CIC6105_PrintRomInfo, NULL, NULL);
}

void CIC6105_Destroy(void) {
    Fault_RemoveClient(&sRomInfoFaultClient);
}

#if MM_VERSION <= N64_JP_1_1
void CIC6105_ScheduleCICTask(void) {
    // TODO: do something with the hardcoded sizes
    static OSTask D_80097AA0_unknown = {
        M_CICTASK,           // type
        0,                   // flags
        rspbootTextStart,    // ucode_boot
        0x000003E8,          // ucode_boot_size
        cic6105TextStart,    // ucode
        0x00000020,          // ucode_size
        (u64*)gBuildCreator, // ucode_data
        0x00000008,          // ucode_data_size
        NULL,                // dram_stack
        0x00000000,          // dram_stack_size
        NULL,                // output_buff
        NULL,                // output_buff_size
        NULL,                // data_ptr
        0x00000000,          // data_size
        NULL,                // yield_data_ptr
        0x00000000,          // yield_data_size
    };

    OSScTask task;
    OSMesgQueue queue;
    OSMesg msg[1];

    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    task.next = NULL;
    task.flags = OS_SC_NEEDS_RSP;
    task.msgQ = &queue;
    task.msg = (OSMesg)0;
    task.framebuffer = NULL;
    task.list = D_80097AA0_unknown;
    osSendMesg(&gScheduler.cmdQueue, &task, OS_MESG_BLOCK);

    Sched_SendNotifyMsg(&gScheduler);
    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);

    gCICValue1 = IO_READ(SP_DMEM_START + 0xFF4);
    gCICValue2 = IO_READ(SP_DMEM_START + 0xFFC);
    CIC6105_ILoveYou();
}

s32 CIC6105_ILoveYou(void) {
    return 0;
}
#endif

void CIC6105_Init(void) {
    gCICAddr1Val = IO_READ(CIC_ADDRESS_1);
    gCICAddr2Val = IO_READ(CIC_ADDRESS_2);
}
