#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <structs.h>

void start(void); // func_80080060
void Idle_ClearMemory(void* begin, void* end); // func_80080150
void Idle_InitFramebuffer(u32* ptr, u32 numBytes, u32 value); // func_80080180
void Idle_InitScreen(void); // func_8008019C
void Idle_InitMemory(void); // func_800801EC
void Idle_InitCodeAndMemory(void); // func_80080250
void Idle_MainThreadEntry(void* arg); // func_80080300
void func_8008038C(void); // func_8008038C
void Idle_ThreadEntry(void* arg); // func_80080514
void func_800805E0(s32 param_1); // func_800805E0
void func_80080748(void); // func_80080748
s32 Dmamgr_DoDmaTransfer(u32 src, void* dst, u32 size); // func_80080790
void Dmamgr_osEPiStartDmaWrapper(OSPiHandle* pOParm1, OSIoMesg* pOParm2, s32 OParm3); // func_800808D4
DmadataEntry* Dmamgr_FindDmaEntry(u32 vromAddr); // func_800808F4
u32 Dmamgr_TranslateVromToRom(u32 vromAddr); // func_80080950
s32 Dmamgr_FindDmaIndex(u32 vromAddr); // func_800809BC
char* func_800809F4(u32 param_1); // func_800809F4
void Dmamgr_HandleRequest(DmaRequest* request); // func_80080A08
void Dmamgr_ThreadEntry(void* arg); // func_80080B84
s32 Dmamgr_SendRequest(DmaRequest* request, u32 vramStart, u32 vromStart, u32 size, UNK_TYPE4 unused, OSMesgQueue* callback, void* callbackMesg); // func_80080C04
s32 Dmamgr_SendRequestAndWait(u32 vramStart, u32 vromStart, u32 size); // func_80080C90
void Dmamgr_Start(void); // func_80080D0C
void Dmamgr_Stop(void); // func_80080E00
u8* Yaz0_LoadFirstChunk(void); // func_80080E30
u8* Yaz0_LoadNextChunk(void* currDecompPos); // func_80080ED0
s32 Yaz0_Decompress(u8* src, u8* dest); // func_80080FF0
void Yaz0_LoadAndDecompressFile(u32 romStart, u32 vramStart, u32 size); // func_80081178
void Irqmgr_AddCallback(Irqmgr* irqmgr, OSMesgQueueListNode* param_2, OSMesgQueue* param_3); // func_80081250
void Irqmgr_RemoveCallback(Irqmgr* irqmgr, OSMesgQueueListNode* puParm2); // func_800812DC
void Irqmgr_NotifyAllCallbacks(Irqmgr* irqmgr, s16* msg); // func_80081368
void Irqmgr_NotifyAllCallbacksWithCapacity(Irqmgr* irqmgr, OSMesg msg); // func_800813B8
void Irqmgr_HandlePrenmi1(Irqmgr* irqmgr); // func_8008141C
void Irqmgr_CheckThreadStatus2(void); // func_800814B4
void Irqmgr_HandlePrenmi2(Irqmgr* irqmgr); // func_800814D4
void Irqmgr_HandlePrenmi3(Irqmgr* irqmgr); // func_80081550
void Irqmgr_CheckThreadStatus(Irqmgr* irqmgr); // func_800815A8
void Irqmgr_HandleFrame(Irqmgr* irqmgr); // func_800815CC
void Irqmgr_ThreadEntry(Irqmgr* irqmgr); // func_80081684
void Irqmgr_Start(Irqmgr* irqmgr, void* stack, OSPri pri, u8 retraceCount); // func_80081754
void CIC6105_Nop80081820(void); // func_80081820
void CIC6105_Nop80081828(void); // func_80081828
void CIC6105_PrintRomInfo(void); // func_80081830
void CIC6105_AddRomInfoFaultPage(void); // func_8008189C
void CIC6105_RemoveRomInfoFaultPage(void); // func_800818D0
void func_800818F4(void); // func_800818F4
void Fault_Nop80081920(UNK_TYPE4 param_1, ...); // func_80081920
void Fault_Log(char* str, ...); // func_8008193C
void Fault_Nop80081958(UNK_TYPE4 param_1, ...); // func_80081958
void Fault_SleepImpl(u32 duration); // func_80081980
void Fault_AddClient(FaultClient* client, fault_client_func callback, void* param0, void* param1); // func_800819F0
void Fault_RemoveClient(FaultClient* client); // func_80081AD4
void Fault_AddAddrConvClient(FaultAddrConvClient* client, fault_address_converter_func callback, void* param); // func_80081BCC
void Fault_RemoveAddrConvClient(FaultAddrConvClient* client); // func_80081CA4
void* Fault_ConvertAddress(void* addr); // func_80081D9C
void Fault_Sleep(u32 duration); // func_80081E2C
void Fault_PadCallback(Input* input); // func_80081E68
void Fault_UpdatePadImpl(void); // func_80081EA4
s32 Fault_WaitForInputImpl(void); // func_80081EF0
void Fault_WaitForInput(void); // func_8008203C
void Fault_DrawRec(s32 x, s32 y, s32 w, s32 h, u16 color); // func_80082078
void Fault_FillScreenBlack(void); // func_800820D8
void Fault_FillScreenRed(void); // func_8008212C
void Fault_DrawCornerRec(u16 color); // func_80082180
void Fault_PrintFReg(s32 idx, f32* value); // func_800821D4
void Fault_LogFReg(s32 idx, f32* value); // func_80082280
void Fault_PrintFPCR(u32 value); // func_80082330
void Fault_LogFPCR(u32 value); // func_800823D4
void Fault_PrintThreadContext(OSThread* t); // func_8008246C
void Fault_LogThreadContext(OSThread* t); // func_800827BC
OSThread* Fault_FindFaultedThread(void); // func_80082AB8
void Fault_Wait5Seconds(void); // func_80082B40
void Fault_WaitForButtonCombo(void); // func_80082BD0
void Fault_DrawMemDumpPage(char* title, u32* addr, u32 param_3); // func_80082C6C
void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1); // func_80082DD8
void Fault_FindNextStackCall(u32** sp, u32** pc, u32** ra); // func_80082FD0
void Fault_DrawStackTrace(OSThread* t, u32 flags); // func_80083144
void Fault_LogStackTrace(OSThread* t, u32 flags); // func_800832D4
void Fault_ResumeThread(OSThread* t); // func_80083450
void Fault_CommitFB(void); // func_800834CC
void Fault_ProcessClients(void); // func_8008358C
void Fault_SetOptionsFromController3(void); // func_80083670
void Fault_SetOptions(void); // func_800837E4
void Fault_ThreadEntry(void* arg); // func_80083828
void Fault_SetFB(void* fb, u16 w, u16 h); // func_80083B70
void Fault_Start(void); // func_80083BC4
void Fault_HangupFaultClient(char* arg0, char* arg1); // func_80083CF8
void Fault_AddHungupAndCrashImpl(char* arg0, char* arg1); // func_80083DF4
void Fault_AddHungupAndCrash(char* filename, u32 line); // func_80083E4C
void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled); // func_80083EB0
void FaultDrawer_DrawRecImpl(s32 xstart, s32 ystart, s32 xend, s32 yend, u16 color); // func_80083EC4
void FaultDrawer_DrawChar(char c); // func_80083FE4
s32 FaultDrawer_ColorToPrintColor(u16 color); // func_80084160
void FaultDrawer_UpdatePrintColor(void); // func_80084210
void FaultDrawer_SetForeColor(u16 color); // func_800842BC
void FaultDrawer_SetBackColor(u16 color); // func_80084308
void FaultDrawer_SetFontColor(u16 color); // func_80084354
void FaultDrawer_SetCharPad(s8 padW, s8 padH); // func_8008439C
void FaultDrawer_SetCursor(s32 x, s32 y); // func_800843D4
void FaultDrawer_FillScreen(void); // func_800844D8
FaultDrawer* FaultDrawer_FormatStringFunc(FaultDrawer* arg, char* str, s32 count); // func_80084568
void FaultDrawer_VPrintf(char* str, char* args); // func_8008477C
void FaultDrawer_Printf(char* fmt, ...); // func_800847CC
void FaultDrawer_DrawText(s32 x, s32 y, char* fmt, ...); // func_8008481C
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h); // func_8008486C
void FaultDrawer_SetInputCallback(func_ptr func); // func_800848A4
void FaultDrawer_Init(void); // func_800848B8
void func_80084940(void); // func_80084940
void func_80084968(void); // func_80084968
void func_800849A0(void); // func_800849A0
void func_80084C0C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80084C0C
void func_80084CD0(void); // func_80084CD0
void handle_overlay_relocations(u32 allocatedVRamAddr, OverlayBlockSizes* overlayInfo, u32 vRamStart); // func_80084DB0
s32 load_and_relocate_overlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, u32 allocatedVRamAddr); // func_8008501C
void* load_game_state_overlay(u32 vromStart, u32 vromEnd, u32 vramStart, u32 vramEnd); // func_800850C8
void func_80085130(void); // func_80085130
void func_80085150(void); // func_80085150
void func_80085158(s32 param_1); // func_80085158
u32 func_80085164(s16* param_1, s16 param_2); // func_80085164
u32 func_8008517C(u16* param_1, u16 param_2); // func_8008517C
u32 func_80085198(s32 param_1, u16 param_2); // func_80085198
u32 func_800851B4(s32 param_1, u16 param_2); // func_800851B4
u32 func_800851D0(u16* param_1); // func_800851D0
u32 func_800851D8(s32 param_1); // func_800851D8
void func_800851E0(void); // func_800851E0
void func_800851E8(void); // func_800851E8
void func_800851F0(void); // func_800851F0
void func_800851FC(void); // func_800851FC
void func_80085204(void); // func_80085204
void func_8008520C(void); // func_8008520C
void func_8008522C(void); // func_8008522C
void func_8008524C(void); // func_8008524C
void StackCheck_Init(StackEntry* entry, u32 stackTop, u32 stackBottom, u32 initValue, s32 minSpace, char* name); // func_80085320
void StackCheck_Cleanup(StackEntry* entry); // func_800853F8
s32 StackCheck_GetState(StackEntry* entry); // func_80085468
u32 StackCheck_CheckAll(void); // func_800854E0
u32 StackCheck_Check(StackEntry* entry); // func_80085538
void func_80085570(void); // func_80085570
void func_800859BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800859BC
void func_80085A08(void); // func_80085A08
void func_80085A2C(void); // func_80085A2C
void func_80085A54(int param_1, int param_2, int param_3); // func_80085A54
void func_80085A68(void); // func_80085A68
void func_80085D74(void); // func_80085D74
void func_80085F30(void); // func_80085F30
void func_80085F8C(void); // func_80085F8C
void func_80085FE4(void); // func_80085FE4
void func_80086010(void); // func_80086010
void func_80086064(void); // func_80086064
void func_8008606C(void); // func_8008606C
void func_800860A0(void); // func_800860A0
void func_800860B8(void); // func_800860B8
void func_800860D8(void); // func_800860D8
void func_80086110(void); // func_80086110
void func_80086258(void); // func_80086258
void assert_fail(char* file, u32 lineNum); // func_80086280
void func_800862B4(void); // func_800862B4
void* StartHeap_AllocMin1(u32 size); // func_800862E0
void StartHeap_FreeNull(void* pvParm1); // func_80086310
void func_8008633C(unsigned int param_1, int param_2, int param_3, UNK_PTR param_4); // func_8008633C
void func_800863AC(unsigned int param_1, int param_2, int param_3, UNK_PTR param_4); // func_800863AC
void func_8008641C(void); // func_8008641C
void func_800864EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800864EC
void func_80086588(void); // func_80086588
void StartHeap_Init(u32 base, u32 size); // func_800865F8
int func_80086620(OSMesgQueue* param_1, PadmgrThreadStruct* param_2, OSContStatus* param_3); // func_80086620
void func_80086760(void); // func_80086760
void func_80086794(void); // func_80086794
void func_800867B4(void); // func_800867B4
void func_800867D4(void); // func_800867D4
void func_800867F4(void); // func_800867F4
void func_80086814(void); // func_80086814
void func_80086834(void); // func_80086834
void func_80086880(void); // func_80086880
void func_800869A4(void); // func_800869A4
void func_80086AF0(void); // func_80086AF0
void func_80086B30(void); // func_80086B30
void func_80086C18(void); // func_80086C18
void func_80086C48(void); // func_80086C48
void func_80086C70(void); // func_80086C70
f64 func_80086C7C(f64 param_1); // func_80086C7C
s32 func_80086C88(f32 param_1); // func_80086C88
s32 func_80086C98(f64 param_1); // func_80086C98
void func_80086CA8(void); // func_80086CA8
f64 func_80086CB4(f64 param_1); // func_80086CB4
s32 func_80086CC0(f32 param_1); // func_80086CC0
s32 func_80086CD0(f64 param_1); // func_80086CD0
void func_80086CE0(void); // func_80086CE0
f64 func_80086CEC(f64 param_1); // func_80086CEC
s32 func_80086CF8(f32 param_1); // func_80086CF8
s32 func_80086D08(f64 param_1); // func_80086D08
void func_80086D18(void); // func_80086D18
void func_80086D24(void); // func_80086D24
s32 func_80086D30(f32 param_1); // func_80086D30
s32 func_80086D40(f64 param_1); // func_80086D40
void func_80086D50(void); // func_80086D50
f64 func_80086D6C(f64 param_1); // func_80086D6C
s32 func_80086D8C(f32 param_1); // func_80086D8C
s32 func_80086DAC(f64 param_1); // func_80086DAC
void* StartHeap_Alloc(u32 size); // func_80086DD0
void* StartHeap_AllocR(u32 size); // func_80086DF8
void* StartHeap_Realloc(void* oldPtr, u32 newSize); // func_80086E20
void StartHeap_Free(void* ptr); // func_80086E50
void* StartHeap_Calloc(s32 param_1, s32 param_2); // func_80086E78
void StartHeap_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated); // func_80086ECC
s32 StartHeap_CheckArena(void); // func_80086F04
void StartHeap_InitArena(u32 base, u32 size); // func_80086F28
void StartHeap_Cleanup(void); // func_80086F58
u32 StartHeap_IsInitialized(void); // func_80086F7C
u32 rand(void); // func_80086FA0
void randSetSeed(u32 seed); // func_80086FD0
f32 randZeroOne(void); // func_80086FDC
f32 randPlusMinusPoint5(void); // func_80087030
void func_80087088(UNK_PTR param_1, UNK_TYPE4 param_2); // func_80087088
void func_80087090(s32* param_1); // func_80087090
f32 func_800870B8(u32* param_1); // func_800870B8
f32 func_80087104(u32* param_1); // func_80087104
void arena_lock_init(Heap* heap); // func_80087160
void arena_lock(Heap* heap); // func_8008718C
void arena_unlock(Heap* heap); // func_800871B4
HeapNode* heap_get_tail(Heap* param_1); // func_800871DC
void __osMallocInit(Heap* heap, u32 heapBase, u32 heapSize); // func_8008720C
void __osMallocAddBlock(Heap* heap, u32 start, u32 size); // func_8008725C
void __osMallocCleanup(Heap* heap); // func_800872FC
u32 __osMallocIsInitalized(Heap* heap); // func_8008731C
void* __osMalloc(Heap* heap, u32 size); // func_80087324
void* __osMallocR(Heap* heap, u32 size); // func_80087408
void __osFree(Heap* heap, void* ptr); // func_800874EC
void* __osRealloc(Heap* heap, void* oldPtr, u32 newSize); // func_800875E4
void __osAnalyzeArena(Heap* heap, u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated); // func_80087714
s32 __osCheckArena(Heap* heap); // func_800877C4
void* proutSprintf(void* s, char* buf, size_t n); // func_80087830
void func_80087854(void); // func_80087854
int sprintf(char* s, char* fmt, ...); // func_800878A4
void func_80087900(void); // func_80087900
void func_80087934(void); // func_80087934
void wait_cycles(OSTime uParm1); // func_80087960
void func_800879CC(void); // func_800879CC
void func_80087A1C(void); // func_80087A1C
void func_80087A6C(u32 param_1); // func_80087A6C
void func_80087AC0(void); // func_80087AC0
void __osSetCause(void); // func_80087B00
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags); // func_80087B10
void func_80087C60(void); // func_80087C60
void func_80087E00(u32 param_1); // func_80087E00
void osStopThread(OSThread* t); // func_80087E10
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags); // func_80087ED0
OSIntMask osSetIntMask(OSIntMask im); // func_80088010
OSIntMask osGetIntMask(void); // func_800880B0
void func_80088110(void); // func_80088110
void func_800882A0(void); // func_800882A0
f32 __sinf(f32 __x); // func_80088350
s32 sins(u16 angle); // func_80088510
OSTask* _VirtualToPhysicalTask(OSTask* intp); // func_80088580
void osSpTaskLoad(OSTask* intp); // func_8008868C
void osSpTaskStartGo(OSTask* tp); // func_800887F4
void __ull_rshift(void); // func_80088840
void __ull_rem(void); // func_8008886C
u64 __ull_div(u64 param_1, u64 param_2); // func_800888A8
void __ll_lshift(void); // func_800888E4
void __ll_rem(void); // func_80088910
void __ll_div(void); // func_8008894C
u64 __ll_mul(u64 param_1, u64 param_2); // func_800889A8
void __ull_divremi(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800889D8
void __ll_mod(void); // func_80088A38
void __ll_rshift(void); // func_80088AD4
void __osExceptionPreamble(void); // func_80088B00
void __osException(void); // func_80088B10
void func_80088D48(void); // func_80088D48
void func_80088D54(void); // func_80088D54
void func_80088D60(void); // func_80088D60
void func_80088D80(void); // func_80088D80
void func_80088DC4(void); // func_80088DC4
void func_80088F2C(void); // func_80088F2C
void func_80088F88(void); // func_80088F88
void func_80088FA8(void); // func_80088FA8
void func_80088FE0(void); // func_80088FE0
void send_mesg(void); // func_8008905C
void handle_CpU(void); // func_80089110
void __osEnqueueAndYield(OSThread** param_1); // func_80089144
void __osEnqueueThread(OSThread** param_1, OSThread* param_2); // func_80089244
OSThread* __osPopThread(OSThread** param_1); // func_8008928C
void func_8008929c(void); // func_8008929C
void __osDispatchThread(void); // func_800892A4
void __osCleanupThread(void); // func_80089420
void __osDequeueThread(OSThread** param_1, OSThread* param_2); // func_80089430
void osDestroyThread(OSThread* puParm1); // func_80089470
void func_80089580(void); // func_80089580
void bzero(void* begin, s32 length); // func_80089630
void func_800896D0(void); // func_800896D0
void func_80089838(void); // func_80089838
void func_80089944(void); // func_80089944
void __osSiCreateAccessQueue(void); // func_80089AA0
void __osSiGetAccess(void); // func_80089AF0
void __osSiRelAccess(void); // func_80089B34
s32 osContInit(OSMesgQueue* mq, u8* bitpattern, OSContStatus* data); // func_80089B60
void __osContGetInitData(u8* pattern, OSContStatus* data); // func_80089CBC
void __osPackRequestData(u8 cmd); // func_80089D68
void osCreateThread(OSThread* t, OSId id, osCreateThread_func entry, void* arg, void* sp, OSPri p); // func_80089E40
void osContStartReadData(void); // func_80089F90
void osContGetReadData(void); // func_8008A014
void __osPackReadData(void); // func_8008A0A0
void func_8008A170(void); // func_8008A170
u32 osVirtualToPhysical(void* vaddr); // func_8008A540
u32 __osGetSR(void); // func_8008A5C0
void __osSetSR(u32 value); // func_8008A5D0
void osWritebackDCache(void* vaddr, s32 nbytes); // func_8008A5E0
void func_8008A660(void); // func_8008A660
void osInitialize(void); // func_8008A6FC
void func_8008A9A8(void); // func_8008A9A8
void* osViGetNextFramebuffer(void); // func_8008AA10
void guPerspectiveF(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8008AA50
void guPerspective(Mtx* m, u16* perspNorm, float fovy, float aspect, float near, float far, float scale); // func_8008AC80
s32 __osSpRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size); // func_8008ACE0
s32 __osSiRawStartDma(s32 direction, void* dramAddr); // func_8008AD70
void func_8008AE20(void); // func_8008AE20
void osViRepeatLine(u8 active); // func_8008AE70
s32 __osSiRawReadIo(u32 devAddr, u32* data); // func_8008AEE0
OSId osGetThreadId(OSThread* t); // func_8008AF30
void osSpTaskYield(void); // func_8008AF50
void func_8008AF70(void); // func_8008AF70
void func_8008B044(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8008B044
void func_8008B3C0(void); // func_8008B3C0
void func_8008B490(void); // func_8008B490
void func_8008B554(void); // func_8008B554
void guMtxIdentF(f32* mf); // func_8008B600
void osViSetMode(OSViMode* modep); // func_8008B650
void __osGetConfig(void); // func_8008B6B0
void __osSetConfig(void); // func_8008B6C0
void guLookAtF(float* mf, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp); // func_8008B6D0
void guLookAt(Mtx* m, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp); // func_8008B974
void func_8008B9F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8008B9F0
void func_8008BD24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8008BD24
s32 osStopTimer(OSTimer* t); // func_8008BE70
u32 __osProbeTLB(void* param_1); // func_8008BF60
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt); // func_8008C020
void __osPiCreateAccessQueue(void); // func_8008C190
void __osPiGetAccess(void); // func_8008C1E0
void __osPiRelAccess(void); // func_8008C224
void func_8008C260(s32 param_1); // func_8008C260
void func_8008C670(void); // func_8008C670
void func_8008C740(void); // func_8008C740
void func_8008C7B4(void); // func_8008C7B4
void func_8008C8B0(void); // func_8008C8B0
void func_8008CC00(void); // func_8008CC00
void func_8008CD64(void); // func_8008CD64
void func_8008CF10(void); // func_8008CF10
void func_8008CFE4(void); // func_8008CFE4
void osGetCount(void); // func_8008D2C0
void func_8008D2E0(void); // func_8008D2E0
u32 calculate_mem_size(void); // func_8008D350
void func_8008D470(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8008D470
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m); // func_8008D640
f32 sqrtf(f32 __x); // func_8008D700
void func_8008D710(void); // func_8008D710
s32 osContStartQuery(OSMesgQueue* mq); // func_8008D730
void osContGetQuery(OSContStatus* data); // func_8008D7AC
void guLookAtHiliteF(f32* mf, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight); // func_8008D7D0
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight); // func_8008DF90
int _Printf(printf_func pfn, void* arg, char* fmt, char* ap); // func_8008E050
void func_8008E698(void); // func_8008E698
void func_8008ED30(void); // func_8008ED30
void osUnmapTLBAll(void); // func_8008EDE0
s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction); // func_8008EE30
void func_8008EED0(void); // func_8008EED0
void func_8008F100(void); // func_8008F100
unsigned char* strchr(unsigned char* __s, int __c); // func_8008F1A0
size_t strlen(unsigned char* __s); // func_8008F1E0
void* memcpy(void* __dest, void* __src, size_t __n); // func_8008F208
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count); // func_8008F240
void osInvalICache(void* vaddr, s32 nbytes); // func_8008F270
void osInvalDCache(void* vaddr, s32 nbytes); // func_8008F2F0
void __osTimerServicesInit(void); // func_8008F3A0
void __osTimerInterrupt(void); // func_8008F42C
void __osSetTimerIntr(OSTime tim); // func_8008F5A4
void __osInsertTimer(OSTimer* t); // func_8008F644
void func_8008F7D0(void); // func_8008F7D0
int __osSpDeviceBusy(void); // func_8008FA00
int __osSiDeviceBusy(void); // func_8008FA30
void func_8008FA60(void); // func_8008FA60
s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag); // func_8008FAB0
void osSetThreadPri(OSThread* t, OSPri pri); // func_8008FC00
OSPri osGetThreadPri(OSThread* t); // func_8008FCE0
void func_8008FD00(void); // func_8008FD00
void osViSwapBuffer(void* frameBufPtr); // func_8008FE60
void func_8008FEB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8008FEB0
void func_80090058(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80090058
void func_800900C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800900C0
void osSpTaskYielded(void); // func_800902A0
s32 memcmp(void* __s1, void* __s2, size_t __n); // func_80090300
OSTime osGetTime(void); // func_80090420
void guRotateF(float* mf, float a, float x, float y, float z); // func_800904B0
void guRotate(Mtx* m, float a, float x, float y, float z); // func_80090634
void __osSetGlobalIntMask(void); // func_80090680
void func_800906D0(void); // func_800906D0
void func_80090810(void); // func_80090810
void func_80090900(void); // func_80090900
s32 osAiSetFrequency(u32 frequency); // func_80090AF0
void func_80090C40(void); // func_80090C40
void func_80090E70(void); // func_80090E70
void func_800910A0(void); // func_800910A0
void func_80091170(void); // func_80091170
OSThread* __osGetActiveQueue(void); // func_80091210
void guNormalize(float* x, float* y, float* z); // func_80091220
void __osSetCompare(u32 value); // func_80091280
u32 __osGetCompare(void); // func_80091290
u32 osDpGetStatus(void); // func_800912A0
void osDpSetStatus(u32 status); // func_800912B0
void _bcopy(void* __src, void* __dest, size_t __n); // func_800912C0
void __osResetGlobalIntMask(void); // func_800915D0
void func_80091630(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80091630
void func_80091808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80091808
void guOrthoF(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800918A0
void guOrtho(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800919F4
OSIntMask __osDisableInt(void); // func_80091A60
void __osRestoreInt(OSIntMask im); // func_80091AD0
void __osViInit(void); // func_80091AF0
void __osViSwapContext(void); // func_80091C10
void osPiGetCmdQueue(void); // func_80091F10
f32 __cosf(f32 __x); // func_80091F40
void func_800920B0(void); // func_800920B0
void osViSetSpecialFeatures(u32 func); // func_80092100
s32 coss(u16 angle); // func_80092260
void osSetTime(void); // func_80092290
void func_800922C0(void); // func_800922C0
void osViSetEvent(OSMesgQueue* param_1, OSMesg param_2, u32 retraceCount); // func_800923E0
void func_80092440(void); // func_80092440
void func_800925CC(void); // func_800925CC
void func_80092680(void); // func_80092680
void func_80092730(void); // func_80092730
OSPiHandle* func_80092920(void); // func_80092920
void func_80092A80(void); // func_80092A80
void func_80092C00(void); // func_80092C00
void osContSetCh(void); // func_80092C80
u32 __osSetFpcCsr(u32 value); // func_80092CE0
u32 __osGetFpcCsr(void); // func_80092CF0
void func_80092D00(void); // func_80092D00
void func_80092EE0(void); // func_80092EE0
void func_800930E8(void); // func_800930E8
void func_800931F0(void); // func_800931F0
void func_80093728(void); // func_80093728
void func_80093A00(void); // func_80093A00
void osAiGetLength(void); // func_80093BA0
void func_80093BB0(void); // func_80093BB0
void osMapTLBRdb(void); // func_80093C00
void osYieldThread(void); // func_80093C60
void func_80093CC0(void); // func_80093CC0
u32 __osGetCause(void); // func_80093D90
void func_80093DA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80093DA0
void func_80093FF0(void); // func_80093FF0
s32 osSetTimer(OSTimer* t, OSTime value, OSTime interval, OSMesgQueue* mq, OSMesg msg); // func_80094150
void _Ldtob(void); // func_800942E0
void func_80094770(void); // func_80094770
void func_80094828(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80094828
ldiv_t ldiv(s32 __numer, s32 __denom); // func_80094DF0
lldiv_t* lldiv(s64 __numer, s64 __denom); // func_80094E74
void _Litob(void); // func_80094F80
s32 __osSiRawWriteIo(u32 devAddr, u32 data); // func_80095220
u32 __osSpGetStatus(void); // func_80095270
void __osSpSetStatus(u32 value); // func_80095280
void osCreateViManager(OSPri pri); // func_800952A0
void viMgrMain(OSDevMgr* iParm1); // func_80095420
__OSViContext* __osViGetCurrentContext(void); // func_800955B0
void osWritebackDCacheAll(void); // func_800955C0
OSThread* __osGetCurrFaultedThread(void); // func_800955F0
void func_80095600(void); // func_80095600
void guMtxF2L(void); // func_80095740
void osStartThread(OSThread* param_1); // func_800957B0
void osViSetYScale(f32 param_1); // func_80095900
void osViSetXScale(f32 xscale); // func_80095950
void __d_to_ll(void); // func_80095A60
void __f_to_ll(void); // func_80095A7C
void __d_to_ull(void); // func_80095A98
void __f_to_ull(void); // func_80095B38
void __ll_to_d(void); // func_80095BD4
void __ll_to_f(void); // func_80095BEC
void __ull_to_d(void); // func_80095C04
void __ull_to_f(void); // func_80095C38
void func_80095C70(void); // func_80095C70
void func_80096360(void); // func_80096360
void func_80096410(void); // func_80096410
void func_800964D0(void); // func_800964D0
s32 __osSpSetPc(u32 data); // func_80096510
void func_80096540(void); // func_80096540
// UNK_RET func_80096770(UNK_ARGS);
void func_800967A0(void); // func_800967A0
u32 __osGetWatchLo(void); // func_80096810
void __osSetWatchLo(u32 value); // func_80096820
f32 func_80096830(f32 param_1, f32 param_2); // func_80096830
void* func_80096880(void* param_1, u8 param_2, s32 param_3); // func_80096880
void func_800968B0(void); // func_800968B0
char* func_800968f0(char* param_1, char* param_2); // func_800968F0
void func_80096930(void); // func_80096930
void EnAObj_Init(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5AC0
void EnAObj_Fini(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5B6C
void EnAObj_Update1(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5B98
void EnAObj_Update2(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5C28
void EnAObj_Main(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5C60
void EnAObj_Draw(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5CB8
void EnItem00_UpdateForNewObjectId(ActorEnItem00* this, GlobalContext* ctxt, f32* puParm3, f32* pfParm4); // func_800A5D00
void EnItem00_Init(ActorEnItem00* this, GlobalContext* ctxt); // func_800A5D70
void EnItem00_Fini(ActorEnItem00* this, GlobalContext* ctxt); // func_800A637C
void func_800A63A8(ActorEnItem00* this, GlobalContext* ctxt); // func_800A63A8
void func_800A640C(ActorEnItem00* this); // func_800A640C
void func_800A6650(void); // func_800A6650
void func_800A6780(void); // func_800A6780
void EnItem00_Update(ActorEnItem00* this, GlobalContext* ctxt); // func_800A6A40
void EnItem00_Main(ActorEnItem00* this, GlobalContext* ctxt); // func_800A6B98
void EnItem00_Draw(ActorEnItem00* this, GlobalContext* ctxt); // func_800A7128
void EnItem00_DrawRupee(ActorEnItem00* this, GlobalContext* ctxt); // func_800A72AC
void EnItem00_DrawSprite(ActorEnItem00* actor, GlobalContext* ctxt); // func_800A73A0
void EnItem00_DrawHeartContainer(ActorEnItem00* actor, GlobalContext* ctxt); // func_800A74D8
void EnItem00_DrawHeartPiece(void); // func_800A75B8
void func_800A7650(void); // func_800A7650
void func_800A7730(void); // func_800A7730
void func_800A7AD4(void); // func_800A7AD4
void func_800A7D28(void); // func_800A7D28
void func_800A8150(void); // func_800A8150
void func_800A817C(void); // func_800A817C
void func_800A81A4(void); // func_800A81A4
void func_800A81F0(void); // func_800A81F0
void func_800A8514(void); // func_800A8514
void func_800A8558(void); // func_800A8558
void func_800A8610(void); // func_800A8610
void func_800A8720(void); // func_800A8720
void func_800A8854(void); // func_800A8854
void func_800A8860(void); // func_800A8860
void func_800A8C78(void); // func_800A8C78
void func_800A8DE8(void); // func_800A8DE8
void func_800A92FC(void); // func_800A92FC
void func_800A9330(void); // func_800A9330
void func_800A9804(void); // func_800A9804
void func_800AA190(void); // func_800AA190
void func_800AA460(void); // func_800AA460
void func_800AA498(void); // func_800AA498
void func_800AA700(void); // func_800AA700
void func_800AABE0(void); // func_800AABE0
void func_800AB0EC(void); // func_800AB0EC
void func_800AB5D0(void); // func_800AB5D0
void func_800AB808(void); // func_800AB808
void func_800AB894(void); // func_800AB894
void func_800AB9F8(void); // func_800AB9F8
void func_800AC718(void); // func_800AC718
void func_800ACBF0(void); // func_800ACBF0
void func_800ACFCC(void); // func_800ACFCC
void func_800ACFD8(void); // func_800ACFD8
void func_800AD09C(void); // func_800AD09C
void func_800AE2A0(void); // func_800AE2A0
void func_800AE434(GlobalContext* ctxt, ColorRGBA8* color, short sParm3, short sParm4); // func_800AE434
void func_800AE5A0(GlobalContext* ctxt); // func_800AE5A0
void func_800AE5E4(void); // func_800AE5E4
void func_800AE778(GlobalContext* ctxt, ColorRGBA8* color, short param_3, short param_4); // func_800AE778
void func_800AE8EC(GlobalContext* ctxt); // func_800AE8EC
void func_800AE930(BgCheckContext* bgCtxt, int param_2, float* param_3, float param_4, short param_5, int param_6, int param_7); // func_800AE930
void func_800AEF44(void); // func_800AEF44
void func_800AEF70(void); // func_800AEF70
void func_800AEFA0(void); // func_800AEFA0
void func_800AF044(void); // func_800AF044
void func_800AF050(void); // func_800AF050
void func_800AF284(void); // func_800AF284
void func_800AF310(void); // func_800AF310
void func_800AF710(void); // func_800AF710
void func_800AF720(void); // func_800AF720
void func_800AF87C(void); // func_800AF87C
void func_800AF890(GlobalContext* ctxt); // func_800AF890
void func_800AF960(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_800AF960
void func_800AFB24(void); // func_800AFB24
void func_800AFC60(GlobalContext* ctxt); // func_800AFC60
void func_800AFDCC(GlobalContext* ctxt, int param_2); // func_800AFDCC
void func_800AFF24(void); // func_800AFF24
void EffectSS_Init(GlobalContext* ctxt, s32 numEntries); // func_800B0050
void EffectSS_Fini(GlobalContext* ctxt); // func_800B0140
LoadedParticleEntry* EffectSS_GetTable(void); // func_800B0200
void EffectSS_Delete(LoadedParticleEntry* param_1); // func_800B0210
void EffectSS_ResetLoadedParticleEntry(LoadedParticleEntry* particle); // func_800B0270
s32 EffectSS_FindFreeSpace(u32 priority, u32* tableEntry); // func_800B0304
void EffectSS_Copy(GlobalContext* ctxt, LoadedParticleEntry* particle); // func_800B043C
void EffectSS_LoadParticle(UNK_TYPE4 param_1, EffectSSType type, u32 priority, void* particleInitData); // func_800B04D4
void EffectSS_UpdateParticle(GlobalContext* ctxt, s32 index); // func_800B067C
void EffectSS_UpdateAllParticles(GlobalContext* ctxt); // func_800B071C
void EffectSS_DrawParticle(GlobalContext* ctxt, s32 index); // func_800B07D8
void EffectSS_DrawAllParticles(GlobalContext* ctxt); // func_800B081C
s32 func_800B096C(s16 param_1, s16 param_2, s32 param_3); // func_800B096C
s16 func_800B09D0(s16 a0, s16 a1, f32 a2); // func_800B09D0
u8 func_800B0A24(u8 a0, u8 a1, f32 a2); // func_800B0A24
void func_800B0B10(GlobalContext* ctxt, LoadedParticleEntry* particle, u32 uParm3); // func_800B0B10
void EffectSS_LoadDust(GlobalContext* ctxt, u16 flags, Vector3f* position, Vector3f* velocity, Vector3f* acceleration, ColorRGBA8* color1, ColorRGBA8* color2, s16 scale, s16 scaleChangePerFrame, s16 life, u8 type); // func_800B0D2C
void func_800B0DE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B0DE0
void func_800B0E48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B0E48
void func_800B0EB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B0EB0
void func_800B0F18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B0F18
void func_800B0F80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B0F80
void func_800B0FE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B0FE8
void func_800B1054(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B1054
void func_800B10C0(void); // func_800B10C0
void func_800B1130(void); // func_800B1130
void func_800B11A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B11A0
void func_800B1210(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B1210
void func_800B1280(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B1280
void func_800B12F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B12F0
void func_800B1360(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B1360
void func_800B139C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B139C
void func_800B13D8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800B13D8
void func_800B14D4(void); // func_800B14D4
void func_800B1598(void); // func_800B1598
void func_800B165C(void); // func_800B165C
void func_800B16B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B16B8
void EffectSS_LoadSparkle(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_PTR param_5, UNK_PTR param_6, UNK_TYPE2 param_7, int param_8); // func_800B16F4
void func_800B1830(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800B1830
void EffectSS_LoadBomb2(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4); // func_800B1908
void func_800B1970(UNK_TYPE4 param_1, Vector3f* param_2, Vector3f* param_3, Vector3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B1970
void EffectSS_LoadBlast(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, ColorRGBA8* param_5, ColorRGBA8* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); // func_800B19E0
void func_800B1A70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B1A70
void func_800B1AC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_800B1AC4
void func_800B1B10(void); // func_800B1B10
void EffectSS_LoadGSpark(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vector3f* pzParm3, Vector3f* pzParm4, Vector3f* param_5, ColorRGBA8* param_6, ColorRGBA8* param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B1B4C
void func_800B1BDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B1BDC
void func_800B1C70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800B1C70
void func_800B1CC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B1CC4
void func_800B1DC8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800B1DC8
void EffectSS_LoadDodongoFire(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B1E0C
void EffectSS_LoadBubble(UNK_TYPE4 uParm1, Vector3f* pzParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B1E94
void EffectSS_LoadGRipple(UNK_TYPE4 uParm1, Vector3f* pzParm2, UNK_TYPE2 uParm3, UNK_TYPE2 uParm4, UNK_TYPE2 param_5); // func_800B1EF4
void EffectSS_LoadGSplash(UNK_TYPE4 uParm1, Vector3f* pzParm2, UNK_PTR puParm3, UNK_PTR puParm4, UNK_TYPE1 uParm5, UNK_TYPE2 param_6); // func_800B1F4C
void EffectSS_LoadGFire(UNK_TYPE4 uParm1, Vector3f* pzParm2); // func_800B1FE0
void EffectSS_LoadLightning(UNK_TYPE4 uParm1, Vector3f* pzParm2, ColorRGBA8* pzParm3, ColorRGBA8* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B2018
void func_800B2090(UNK_TYPE4 param_1, Vector3f* param_2, Vector3f* param_3, Vector3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B2090
void EffectSS_LoadBigOctoBubble2(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B210C
void EffectSS_LoadFragment(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE4 param_9); // func_800B219C
void func_800B221C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B221C
void func_800B2364(void); // func_800B2364
void EffectSS_LoadStick(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE2 uParm3); // func_800B23D8
void EffectSS_LoadSplash(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B242C
void func_800B249C(void); // func_800B249C
void EffectSS_LoadStone1(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE4 uParm3); // func_800B25D8
void EffectSS_LoadHitMark(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, UNK_TYPE2 uParm3, Vector3f* pzParm4); // func_800B262C
void func_800B2684(void); // func_800B2684
void func_800B26A8(void); // func_800B26A8
void EffectSS_LoadPhantomGanonFlash(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vector3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE1 param_5); // func_800B26D4
void EffectSS_LoadKakarikoFire(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE1 param_6); // func_800B2738
void EffectSS_LoadSoldierSearchBall(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_800B27A0
void EffectSS_LoadShard(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE4 param_13, UNK_TYPE2 param_14, UNK_TYPE2 param_15, UNK_TYPE4 param_16); // func_800B2810
void EffectSS_LoadIcePiece(UNK_TYPE4 uParm1, Vector3f* pzParm2, UNK_TYPE4 uParm3, Vector3f* pzParm4, Vector3f* param_5, UNK_TYPE4 param_6); // func_800B28C8
void func_800B2930(void); // func_800B2930
void EffectSS_LoadEnemyIce(UNK_TYPE4 uParm1, Actor* pzParm2, Vector3f* pzParm3, ColorRGBA8* pzParm4, ColorRGBA8* param_5, UNK_TYPE4 param_6); // func_800B2AC4
void func_800B2B44(void); // func_800B2B44
void func_800B2B7C(void); // func_800B2B7C
void func_800B2BC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800B2BC0
void EffectSS_LoadFireTail(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vector3f* pzParm3, UNK_TYPE4 uParm4, Vector3f* param_5, UNK_TYPE2 param_6, ColorRGBA8* param_7, ColorRGBA8* param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE4 param_11); // func_800B2C48
void func_800B2CE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_800B2CE0
void func_800B2DA4(void); // func_800B2DA4
void EffectSS_LoadEnemyFire(UNK_TYPE4 uParm1, Actor* pzParm2, Vector3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B2DF4
void func_800B2E6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B2E6C
void EffectSS_LoadExtra(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B2F18
void EffectSS_LoadDeadDekuBaba(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_PTR param_5, UNK_PTR param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE4 param_9); // func_800B2F80
void func_800B3030(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE4 param_7); // func_800B3030
void EffectSS_LoadDeadDodongo(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_PTR param_5, UNK_PTR param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B3088
void EffectSS_LoadDeadDekuScrub(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800B3144
void func_800B31BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_800B31BC
void EffectSS_LoadIceSmoke(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5); // func_800B320C
void EffectSS_LoadIceBlock(UNK_TYPE4 uParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, UNK_TYPE2 param_5); // func_800B326C
void func_800B32D0(ContextCommon* ctxt); // func_800B32D0
void func_800B3644(void); // func_800B3644
void DLF_LoadGameState(GameStateMetaInfo* gameState); // func_800B3880
void DLF_FreeGameState(GameStateMetaInfo* gameState); // func_800B39A4
void Actor_PrintLists(ActorContext* actCtxt); // func_800B3AD0
void Actor_SetDrawParams(ActorDrawParams* iParm1, f32 yDisplacement, actor_post_draw_func func, f32 scale); // func_800B3BA4
void Actor_PostDraw(Actor* actor, LightMapper* mapper, GlobalContext* ctxt, u32 displayList, ColorRGBA8* color); // func_800B3BC8
void func_800B3FC0(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B3FC0
void func_800B4024(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B4024
void func_800B4088(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B4088
void func_800B40B8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B40B8
void func_800B40E0(GlobalContext* ctxt, int iParm2, z_Matrix* pzParm3, int iParm4, float param_5, float param_6, float param_7); // func_800B40E0
void func_800B42F8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B42F8
void func_800B4A98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B4A98
void func_800B4AEC(GlobalContext* ctxt, Actor* actor, f32 param_3); // func_800B4AEC
void func_800B4B50(Actor* iParm1, int iParm2, GlobalContext* pzParm3); // func_800B4B50
void func_800B4EDC(GlobalContext* ctxt, Vector3f* pzParm2, Vector3f* pzParm3, f32* pfParm4); // func_800B4EDC
void func_800B4F40(TargetContext* targetContext, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5); // func_800B4F40
void func_800B4F78(TargetContext* targetContext, u8 type, GlobalContext* ctxt); // func_800B4F78
void func_800B5040(TargetContext* targetContext, Actor* actor, u8 type, GlobalContext* ctxt); // func_800B5040
void Actor_TargetContextInit(TargetContext* targetCtxt, Actor* actor, GlobalContext* ctxt); // func_800B51A4
void func_800B5208(TargetContext* targetCtxt, GlobalContext* ctxt); // func_800B5208
void func_800B5814(TargetContext* targetContext, ActorPlayer* player, Actor* param_3, GlobalContext* ctxt); // func_800B5814
u32 Actor_GetSwitchFlag(GlobalContext* ctxt, u32 flag); // func_800B5BB0
void Actor_SetSwitchFlag(GlobalContext* ctxt, u32 flag); // func_800B5BF4
void Actor_UnsetSwitchFlag(GlobalContext* ctxt, u32 flag); // func_800B5C34
u32 Actor_GetChestFlag(GlobalContext* ctxt, u32 flag); // func_800B5C78
void Actor_SetChestFlag(GlobalContext* ctxt, u32 flag); // func_800B5C90
void Actor_SetAllChestFlag(GlobalContext* ctxt, u32 flags); // func_800B5CAC
u32 Actor_GetAllChestFlag(GlobalContext* ctxt); // func_800B5CB8
u32 Actor_GetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CC4
void Actor_SetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CDC
void Actor_UnsetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CF8
u32 Actor_GetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber); // func_800B5D18
void Actor_SetRoomClearedTemp(GlobalContext* ctxt, unsigned int roomNumber); // func_800B5D30
void Actor_UnsetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber); // func_800B5D4C
u32 Actor_GetCollectibleFlag(GlobalContext* ctxt, u32 index); // func_800B5D6C
u32 Actor_SetCollectibleFlag(GlobalContext* ctxt, u32 index); // func_800B5DB0
void Actor_TitleCardContextInit(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5DF0
void Actor_TitleCardCreate(GlobalContext* ctxt, TitleCardContext* titleCtxt, UNK_TYPE4 param_3, UNK_TYPE2 param_4, UNK_TYPE2 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7); // func_800B5E0C
void Actor_Nop800B5E50(UNK_TYPE4 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4); // func_800B5E50
void Actor_TitleCardUpdate(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5E68
void Actor_TitleCardDraw(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5F24
UNK_TYPE4 func_800B6434(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B6434
UNK_TYPE4 func_800B645C(void); // func_800B645C
void func_800B6468(GlobalContext* ctxt); // func_800B6468
void func_800B6474(GlobalContext* ctxt); // func_800B6474
UNK_TYPE4 func_800B648C(GlobalContext* ctxt, UNK_TYPE1 param_2, UNK_TYPE1 param_3, float param_4, Vector3f* param_5); // func_800B648C
f32 func_800B64FC(GlobalContext* ctxt, f32 fParm2, Vector3f* pzParm3, u32* puParm4); // func_800B64FC
void* func_800B6584(GlobalContext* ctxt, s16 sParm2, void* pvParm3, u32 uParm4); // func_800B6584
UNK_TYPE4 func_800B6608(int iParm1, short sParm2); // func_800B6608
void func_800B6680(void); // func_800B6680
void Actor_MarkForDeath(Actor* actor); // func_800B670C
void Actor_InitCurrPosition(Actor* actor); // func_800B672C
void Actor_SetHeight(Actor* actor, f32 height); // func_800B675C
void Actor_SetRotationFromDrawRotation(Actor* actor); // func_800B67A0
void Actor_InitDrawRotation(Actor* actor); // func_800B67C0
void Actor_SetScale(Actor* actor, f32 scale); // func_800B67E0
void Actor_SetObjectSegment(GlobalContext* ctxt, Actor* actor); // func_800B67FC
void Actor_InitToDefaultValues(Actor* actor, GlobalContext* ctxt); // func_800B6834
void Actor_FiniActor(Actor* actor, GlobalContext* ctxt); // func_800B6948
void Actor_SetMovementScale(s32 scale); // func_800B6988
void Actor_ApplyMovement(Actor* actor); // func_800B69AC
void Actor_SetVelocityYRotationAndGravity(Actor* iParm1); // func_800B6A10
void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor); // func_800B6A88
void Actor_SetVelocityXYRotation(Actor* actor); // func_800B6AB4
void Actor_SetVelocityAndMoveXYRotation(Actor* actor); // func_800B6B24
void Actor_SetVelocityXYRotationReverse(Actor* actor); // func_800B6B50
void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor); // func_800B6BD8
void func_800B6C04(Actor* actor, float fParm2); // func_800B6C04
void func_800B6C58(Actor* actor, UNK_TYPE4 param_2); // func_800B6C58
s32 Actor_YawBetweenActors(Actor* from, Actor* to); // func_800B6CD4
s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to); // func_800B6D00
s32 Actor_YawToPoint(Actor* actor, Vector3f* point); // func_800B6D2C
s32 Actor_PitchBetweenActors(Actor* from, Actor* to); // func_800B6D50
s32 Actor_PitchBetweenActorsTop(Actor* from, Actor* to); // func_800B6D7C
s32 Actor_PitchToPoint(Actor* actor, Vector3f* point); // func_800B6DA8
f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2); // func_800B6DCC
f32 Actor_DistanceToPoint(Actor* actor, Vector3f* point); // func_800B6DF8
f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2); // func_800B6E1C
f32 Actor_XZDistanceToPoint(Actor* actor, Vector3f* point); // func_800B6E48
void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vector3f* offset, Vector3f* point); // func_800B6E6C
f32 Actor_YDistance(Actor* actor1, Actor* actor2); // func_800B6F0C
void func_800B6F20(GlobalContext* ctxt, int param_2, float param_3, short param_4); // func_800B6F20
float func_800B6FC8(ActorPlayer* player); // func_800B6FC8
void func_800B7090(void); // func_800B7090
void func_800B7118(void); // func_800B7118
void func_800B7128(void); // func_800B7128
void func_800B715C(void); // func_800B715C
void func_800B7170(void); // func_800B7170
void func_800B71DC(void); // func_800B71DC
u32 func_800B7200(s32 param_1); // func_800B7200
void func_800B722C(void); // func_800B722C
UNK_TYPE4 func_800B724C(GlobalContext* ctxt, UNK_TYPE4 param_2, u8 param_3); // func_800B724C
unsigned int func_800B7298(GlobalContext* ctxt, UNK_TYPE4 param_2, u8 param_3); // func_800B7298
void func_800B72E0(s32 param_1); // func_800B72E0
void func_800B72F8(void); // func_800B72F8
s32 Actor_IsLinkFacingActor(Actor* actor, s16 tolerance, GlobalContext* ctxt); // func_800B7320
s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance); // func_800B7378
s32 Actor_IsActorFacingLink(Actor* actor, s16 angle); // func_800B73E0
s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance); // func_800B742C
s32 Actor_IsActorFacingLinkAndWithinRange(Actor* actor, f32 range, s16 tolerance); // func_800B748C
s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance); // func_800B750C
void func_800B75A0(BgPolygon* param_1, Vector3f* param_2, s16* param_3); // func_800B75A0
UNK_TYPE4 func_800B761C(Actor* param_1, UNK_TYPE4 param_2, unsigned int param_3); // func_800B761C
UNK_TYPE4 func_800B7678(GlobalContext* ctxt, Actor* param_2, int param_3, unsigned int param_4); // func_800B7678
void func_800B78B8(GlobalContext* ctxt, Actor* actor, f32 uParm3, f32 uParm4, f32 param_5, u32 param_6); // func_800B78B8
void func_800B7E04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B7E04
s32 func_800B7FE0(f32* param_1, f32* param_2, f32* param_3, GraphicsContext* gCtxt); // func_800B7FE0
void func_800B8018(void); // func_800B8018
void func_800B8050(Actor* actor, GlobalContext* ctxt, s32 iParm3); // func_800B8050
void func_800B8118(void); // func_800B8118
void func_800B81E0(void); // func_800B81E0
UNK_PTR func_800B8214(PosRot* param_1, Actor* param_2); // func_800B8214
f32* func_800B8248(PosRot* param_1, Actor* param_2); // func_800B8248
void func_800B82EC(void); // func_800B82EC
void func_800B83BC(void); // func_800B83BC
void func_800B83F8(void); // func_800B83F8
int func_800B84D0(Actor* actor, GlobalContext* ctxt); // func_800B84D0
UNK_TYPE4 func_800B8500(Actor* actor, GlobalContext* ctxt, float fParm3, float fParm4, int param_5); // func_800B8500
void func_800B85E0(Actor* actor, GlobalContext* ctxt, f32 uParm3, s32 uParm4); // func_800B85E0
void func_800B8614(Actor* actor, GlobalContext* ctxt, f32 uParm3); // func_800B8614
void func_800B863C(Actor* actor, GlobalContext* ctxt); // func_800B863C
u32 func_800B867C(Actor* actor, GlobalContext* ctxt); // func_800B867C
UNK_TYPE4 func_800B86C8(UNK_TYPE4 param_1, GlobalContext* ctxt, UNK_TYPE4 param_3); // func_800B86C8
int func_800B8708(GlobalContext* ctxt); // func_800B8708
void func_800B8718(void); // func_800B8718
void func_800B874C(void); // func_800B874C
void func_800B8804(void); // func_800B8804
void func_800B882C(void); // func_800B882C
void func_800B886C(void); // func_800B886C
void func_800B8898(GlobalContext* ctxt, Actor* actor, UNK_PTR param_3, UNK_PTR param_4); // func_800B8898
void func_800B8934(void); // func_800B8934
u32 Actor_HasParent(Actor* actor, GlobalContext* ctxt); // func_800B89F8
UNK_TYPE4 func_800B8A1C(Actor* iParm1, GlobalContext* ctxt, int iParm3, float fParm4, float param_5); // func_800B8A1C
void func_800B8B84(void); // func_800B8B84
void func_800B8BB0(void); // func_800B8BB0
void func_800B8BD0(void); // func_800B8BD0
void func_800B8BFC(void); // func_800B8BFC
void func_800B8C20(void); // func_800B8C20
void func_800B8C50(void); // func_800B8C50
void func_800B8C78(void); // func_800B8C78
void func_800B8C9C(void); // func_800B8C9C
void func_800B8CEC(void); // func_800B8CEC
void func_800B8D10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800B8D10
void func_800B8D50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B8D50
void func_800B8D98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800B8D98
void func_800B8DD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B8DD4
void func_800B8E1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800B8E1C
void func_800B8E58(void); // func_800B8E58
void func_800B8EC8(Actor* iParm1, u32 uParm2); // func_800B8EC8
void func_800B8EF4(void); // func_800B8EF4
void func_800B8F98(void); // func_800B8F98
void func_800B8FC0(void); // func_800B8FC0
void func_800B8FE8(void); // func_800B8FE8
void func_800B9010(Actor* actor, UNK_TYPE2 uParm2); // func_800B9010
void func_800B9038(void); // func_800B9038
void func_800B9084(void); // func_800B9084
void func_800B9098(Actor* actor); // func_800B9098
void func_800B90AC(void); // func_800B90AC
void func_800B90F4(void); // func_800B90F4
void func_800B9120(ActorContext* actCtxt); // func_800B9120
void Actor_Init(GlobalContext* ctxt, ActorContext* actCtxt, UNK_TYPE4 uParm3); // func_800B9170
void func_800B9334(GlobalContext* ctxt, ActorContext* actCtxt); // func_800B9334
Actor* Actor_UpdateActor(s800B948C* params); // func_800B948C
void Actor_UpdateAll(GlobalContext* ctxt, ActorContext* actCtxt); // func_800B9780
void Actor_DrawActor(GlobalContext* ctxt, Actor* actor); // func_800B9A04
void func_800B9D1C(Actor* actor); // func_800B9D1C
void Actor_DrawAllSetup(GlobalContext* ctxt); // func_800B9E3C
s32 Actor_RecordUndrawnActor(GlobalContext* ctxt, Actor* actor); // func_800B9E4C
void func_800B9E84(void); // func_800B9E84
void func_800B9EF4(GlobalContext* ctxt, int numActors, Actor** actors); // func_800B9EF4
s32 func_800BA2D8(GlobalContext* ctxt, Actor* actor); // func_800BA2D8
s32 func_800BA2FC(GlobalContext* ctxt, Actor* actor, Vector3f* param_3, f32 param_4); // func_800BA2FC
void Actor_DrawAll(GlobalContext* ctxt, ActorContext* aCtxt); // func_800BA42C
void func_800BA6FC(void); // func_800BA6FC
void func_800BA798(GlobalContext* ctxt, ActorContext* aCtxt); // func_800BA798
void func_800BA8B8(GlobalContext* ctxt, ActorContext* actCtxt); // func_800BA8B8
void func_800BA9B4(void); // func_800BA9B4
void Actor_InsertIntoTypeList(ActorContext* actCtxt, Actor* actor, u8 type); // func_800BAAB4
Actor* Actor_RemoveFromTypeList(GlobalContext* ctxt, ActorContext* actCtxt, Actor* actor); // func_800BAB24
void Actor_FreeOverlay(ActorOverlayTableEntry* entry); // func_800BABFC
void Actor_Spawn(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 sParm10); // func_800BAC60
ActorInitData* Actor_LoadOverlay(ActorContext* actCtxt, s16 index); // func_800BACD4
Actor* Actor_SpawnWithParentAndCutscene(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 variable, u32 cutscene, s32 param_12, Actor* parent); // func_800BAE14
void Actor_SpawnWithParent(ActorContext* actCtxt, Actor* parent, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s32 variable); // func_800BB0C0
void Actor_SpawnTransitionActors(GlobalContext* ctxt, ActorContext* actCtxt); // func_800BB140
void func_800BB2D0(ActorContext* aCtxt, unsigned short* param_2, GlobalContext* ctxt); // func_800BB2D0
Actor* func_800BB498(ActorContext* actCtxt, Actor* actor, GlobalContext* ctxt); // func_800BB498
void func_800BB59C(void); // func_800BB59C
void func_800BB604(void); // func_800BB604
void func_800BB8EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800BB8EC
void func_800BBA88(GlobalContext* ctxt, Actor* iParm2); // func_800BBA88
void func_800BBAC0(void); // func_800BBAC0
void func_800BBB74(void); // func_800BBB74
void func_800BBC20(void); // func_800BBC20
void func_800BBCEC(void); // func_800BBCEC
void func_800BBDAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE1 param_9); // func_800BBDAC
void func_800BBFB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE1 param_7); // func_800BBFB0
void func_800BC154(void); // func_800BC154
void func_800BC188(void); // func_800BC188
void func_800BC1B4(void); // func_800BC1B4
void func_800BC270(void); // func_800BC270
void func_800BC444(void); // func_800BC444
void func_800BC4EC(void); // func_800BC4EC
void func_800BC5B8(void); // func_800BC5B8
void func_800BC5EC(void); // func_800BC5EC
void func_800BC620(void); // func_800BC620
void func_800BC770(void); // func_800BC770
void func_800BC7D8(void); // func_800BC7D8
void func_800BC848(void); // func_800BC848
void func_800BC8B8(void); // func_800BC8B8
void func_800BCB50(void); // func_800BCB50
void func_800BCB70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800BCB70
void func_800BCBF4(Vector3f* uParm1, GlobalContext* ctxt); // func_800BCBF4
void func_800BCC68(Vector3f* param_1, GlobalContext* ctxt); // func_800BCC68
void func_800BCCDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800BCCDC
void func_800BD2B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800BD2B4
void func_800BD384(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE1 param_9); // func_800BD384
void func_800BD6E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800BD6E4
void func_800BD888(void); // func_800BD888
void func_800BD9A0(void); // func_800BD9A0
void func_800BD9E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800BD9E0
void func_800BDAA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800BDAA0
void func_800BDB6C(void); // func_800BDB6C
void func_800BDC5C(void); // func_800BDC5C
void func_800BDCF4(void); // func_800BDCF4
void func_800BDFB0(void); // func_800BDFB0
void func_800BDFC0(GlobalContext* ctxt, UNK_TYPE4 uParm2); // func_800BDFC0
void func_800BE03C(GlobalContext* ctxt, Gfx* dl); // func_800BE03C
void func_800BE0B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800BE0B8
void func_800BE184(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800BE184
void func_800BE22C(void); // func_800BE22C
void func_800BE258(void); // func_800BE258
void func_800BE2B8(void); // func_800BE2B8
void func_800BE33C(void); // func_800BE33C
void func_800BE3D0(void); // func_800BE3D0
void func_800BE504(void); // func_800BE504
void func_800BE568(void); // func_800BE568
void func_800BE5CC(void); // func_800BE5CC
void func_800BE63C(void); // func_800BE63C
void func_800BE680(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8); // func_800BE680
void func_800BF7CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800BF7CC
void func_800BF9A0(s32 a0, s32 a1); // func_800BF9A0
s32 func_800BFA78(s32 param_1, s32 param_2); // func_800BFA78
void func_800BFAE8(void); // func_800BFAE8
void func_800BFB40(void); // func_800BFB40
void BgCheck_PolygonLinkedListNodeInit(BgPolygonLinkedListNode* node, s16* next, s16 polyIndex); // func_800BFB80
void BgCheck_PolygonLinkedListResetHead(s16* head); // func_800BFB9C
void BgCheck_ScenePolygonListsNodeInsert(BgScenePolygonLists* list, u16* head, s32 polyIndex); // func_800BFBAC
void BgCheck_PolygonLinkedListNodeInsert(BgPolygonLinkedList* list, s16* head, s32 polyIndex); // func_800BFC04
void BgCheck_PolygonLinkedListInit(GlobalContext* ctxt, BgPolygonLinkedList* list); // func_800BFC5C
void BgCheck_PolygonLinkedListAlloc(GlobalContext* ctxt, BgPolygonLinkedList* list, u32 numNodes); // func_800BFC70
void BgCheck_PolygonLinkedListReset(BgPolygonLinkedList* list); // func_800BFCC0
s16 BgCheck_AllocPolygonLinkedListNode(BgPolygonLinkedList* attributes); // func_800BFCCC
void BgCheck_CreateVec3fFromVertex(BgVertex* vertex, Vector3f* vector); // func_800BFCFC
void BgCheck_CreateVertexFromVec3f(BgVertex* vertex, Vector3f* vector); // func_800BFD40
void func_800BFD84(void); // func_800BFD84
void func_800BFDEC(void); // func_800BFDEC
s32 BgCheck_PolygonGetMinY(BgPolygon* polygons, BgVertex* vertices); // func_800BFFC4
void func_800C003C(void); // func_800C003C
void func_800C0094(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C0094
void func_800C01B8(void); // func_800C01B8
void BgCheck_CreateColTriParamsFromPolygon(BgPolygon* polygon, BgVertex* vertices, ColTriParams* tri); // func_800C0220
void func_800C02C0(BgPolygon* poly, s32 index, BgCheckContext* bgCtxt, ColTriParams* tri); // func_800C02C0
void func_800C0340(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C0340
void func_800C0474(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C0474
void func_800C0668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C0668
void func_800C06A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C06A8
void func_800C074C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C074C
void func_800C07F0(void); // func_800C07F0
void func_800C0AF0(void); // func_800C0AF0
void BgCheck_ScenePolygonListsInsertSorted(BgCheckContext* bgCtxt, u16* head, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C0BC0
void BgCheck_ScenePolygonListsInsert(BgMeshSubdivision* subdivision, BgCheckContext* bgCtxt, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C0DE0
void func_800C0E74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C0E74
void func_800C10FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C10FC
void func_800C1238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C1238
void func_800C12A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C12A4
void func_800C1B68(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800C1B68
void func_800C1D7C(void); // func_800C1D7C
void func_800C2008(void); // func_800C2008
void func_800C20F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800C20F4
void func_800C2310(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800C2310
void func_800C2460(void); // func_800C2460
void func_800C2514(void); // func_800C2514
void func_800C25E0(void); // func_800C25E0
void BgCheck_GetPolyMinSubdivisions(BgCheckContext* bgCtxt, Vector3f* min, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision); // func_800C26C0
void BgCheck_GetPolyMaxSubdivisions(BgCheckContext* bgCtxt, Vector3f* max, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision); // func_800C2864
void BgCheck_GetPolyMinMaxSubdivisions(BgCheckContext* bgCtxt, BgVertex* vertices, BgPolygon* polygons, s32* minX, s32* minY, s32* minZ, s32* maxX, s32* maxY, s32* maxZ, s16 index); // func_800C2A30
UNK_TYPE4 func_800C2BE0(Vector3f* param_1, Vector3f* param_2, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C2BE0
u32 BgCheck_SplitScenePolygonsIntoSubdivisions(BgCheckContext* bgCtxt, GlobalContext* ctxt, BgMeshSubdivision* subdivisions); // func_800C3334
s32 BgCheck_GetIsDefaultSpecialScene(GlobalContext* ctxt); // func_800C3734
s32 BgCheck_GetSpecialSceneMaxMemory(s32 sceneId, u32* maxMemory); // func_800C3778
void BgCheck_CalcSubdivisionSize(f32 min, s32 subdivisions, f32* max, f32* subdivisionSize, f32* inverseSubdivisionSize); // func_800C37BC
s32 BgCheck_GetSpecialSceneMaxObjects(GlobalContext* ctxt, u32* maxNodes, u32* maxPolygons, u32* maxVertices); // func_800C3844
void BgCheck_Init(BgCheckContext* bgCtxt, GlobalContext* ctxt, BgMeshHeader* mesh); // func_800C389C
void func_800C3C00(BgCheckContext* bgCtxt, unsigned int param_2); // func_800C3C00
void func_800C3C14(BgCheckContext* bgCtxt, unsigned int param_2); // func_800C3C14
BgMeshHeader* BgCheck_GetActorMeshHeader(BgCheckContext* bgCtxt, s32 index); // func_800C3C2C
void func_800C3C94(void); // func_800C3C94
float func_800C3D50(UNK_TYPE4 param_1, BgCheckContext* bgCtxt, unsigned int param_3, UNK_PTR param_4, UNK_PTR param_5, UNK_PTR param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, unsigned int param_9, unsigned int param_10); // func_800C3D50
void func_800C3F40(void); // func_800C3F40
void func_800C3FA0(void); // func_800C3FA0
void func_800C4000(void); // func_800C4000
void func_800C4058(void); // func_800C4058
void func_800C40B4(void); // func_800C40B4
void func_800C411C(BgCheckContext* param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5); // func_800C411C
void func_800C4188(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C4188
void func_800C41E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C41E4
void func_800C4240(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C4240
void func_800C42A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C42A8
void func_800C4314(void); // func_800C4314
void func_800C43CC(void); // func_800C43CC
void func_800C4488(void); // func_800C4488
void func_800C44F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C44F0
void func_800C455C(void); // func_800C455C
s32 func_800C45C4(BgCheckContext* bgCtxt, unsigned int param_2, Vector3f* param_3, Vector3f* param_4, Vector3f* param_5, float param_6, int* param_7, int* param_8, BgActor* param_9, float param_10, u8 param_11); // func_800C45C4
void func_800C4C74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800C4C74
void func_800C4CD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800C4CD8
void func_800C4D3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C4D3C
void func_800C4DA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C4DA4
void func_800C4E10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800C4E10
void func_800C4F38(void); // func_800C4F38
void func_800C4F84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800C4F84
void func_800C4FD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C4FD4
void func_800C5464(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C5464
void func_800C54AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C54AC
void func_800C5538(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C5538
void func_800C55C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C55C4
void func_800C5650(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C5650
void func_800C56E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_800C56E0
void func_800C576C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C576C
void func_800C57F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C57F8
void func_800C583C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C583C
void func_800C58C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_800C58C8
void func_800C5954(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); // func_800C5954
void func_800C5A20(void); // func_800C5A20
void func_800C5A64(void); // func_800C5A64
void BgCheck_ScenePolygonListsInit(BgScenePolygonLists* param_1); // func_800C5AAC
void BgCheck_ScenePolygonListsAlloc(GlobalContext* ctxt, BgScenePolygonLists* lists, s32 numNodes, u32 numPolygons); // func_800C5AC4
int func_800C5B80(unsigned short* param_1); // func_800C5B80
u16 BgCheck_ScenePolygonListsReserveNode(BgScenePolygonLists* lists); // func_800C5BBC
void BgCheck_ActorMeshParamsInit(ActorMeshParams* params); // func_800C5BD0
void BgCheck_SetActorMeshParams(ActorMeshParams* params, Vector3f* scale, Vector3s* rotation, Vector3f* position); // func_800C5C0C
s32 BgCheck_AreActorMeshParamsEqual(ActorMeshParams* param_1, ActorMeshParams* param_2); // func_800C5C5C
void BgCheck_ActorMeshPolyListsHeadsInit(ActorMeshPolyLists* lists); // func_800C5D30
void BgCheck_ActorMeshPolyListsInit(ActorMeshPolyLists* lists); // func_800C5D70
void BgCheck_ActorMeshVerticesIndexInit(s16* index); // func_800C5D90
void BgCheck_ActorMeshWaterboxesIndexInit(s16* index); // func_800C5D9C
void BgCheck_ActorMeshInit(GlobalContext* ctxt, ActorMesh* mesh); // func_800C5DA8
void BgCheck_ActorMeshInitFromActor(ActorMesh* actorMesh, BgActor* actor, BgMeshHeader* header); // func_800C5E10
s32 BgCheck_HasActorMeshChanged(ActorMesh* mesh); // func_800C5EC8
void BgCheck_PolygonsInit(BgPolygon** polygons); // func_800C5EF0
void BgCheck_PolygonsAlloc(GlobalContext* ctxt, BgPolygon* polygons, u32 numPolygons); // func_800C5EFC
void BgCheck_VerticesInit(BgVertex** vertices); // func_800C5F38
void BgCheck_VerticesListAlloc(GlobalContext* ctxt, BgVertex** vertices, u32 numVertices); // func_800C5F44
void BgCheck_WaterboxListInit(BgWaterboxList* waterboxList); // func_800C5F8C
void BgCheck_WaterboxListAlloc(GlobalContext* ctxt, BgWaterboxList* waterboxList, u32 numWaterboxes); // func_800C5F9C
void BgCheck_ActorMeshUpdateParams(GlobalContext* ctxt, ActorMesh* mesh); // func_800C5FD8
s32 BgCheck_IsActorMeshIndexValid(s32 index); // func_800C6024
void BgCheck_DynaInit(GlobalContext* ctxt, BgDynaCollision* param_2); // func_800C6044
void BgCheck_DynaAlloc(GlobalContext* ctxt, BgDynaCollision* dyna); // func_800C6098
s32 BgCheck_AddActorMesh(GlobalContext* ctxt, BgDynaCollision* dyna, BgActor* actor, BgMeshHeader* header); // func_800C6188
BgActor* BgCheck_GetActorOfMesh(BgCheckContext* bgCtxt, s32 index); // func_800C6248
void func_800C62BC(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C62BC
void func_800C6314(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C6314
void func_800C636C(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C636C
void func_800C63C4(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C63C4
void func_800C641C(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C641C
void func_800C6474(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C6474
void BgCheck_RemoveActorMesh(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index); // func_800C64CC
void func_800C6554(void); // func_800C6554
void BgCheck_CalcWaterboxDimensions(Vector3f* minPos, Vector3f* maxXPos, Vector3f* maxZPos, Vector3s* minPosOut, s16* xLength, s16* zLength); // func_800C656C
void BgCheck_AddActorMeshToLists(GlobalContext* ctxt, BgDynaCollision* dyna, s32 index, s32* currVertices, s32* currPolygons, s32* currWaterboxes); // func_800C6838
void BgCheck_ResetFlagsIfLoadedActor(GlobalContext* ctxt, BgDynaCollision* dyna, Actor* actor); // func_800C734C
void BgCheck_Update(GlobalContext* ctxt, BgDynaCollision* dyna); // func_800C73E4
void func_800C756C(s32 param_1, s32* param_2, s32* param_3, s32* param_4); // func_800C756C
void BgCheck_UpdateAllActorMeshes(GlobalContext* ctxt, BgDynaCollision* dyna); // func_800C765C
void func_800C76EC(void); // func_800C76EC
void func_800C7974(void); // func_800C7974
void func_800C7E40(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_800C7E40
void func_800C8580(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C8580
void func_800C87D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_800C87D0
void func_800C8A60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800C8A60
void func_800C8BD0(void); // func_800C8BD0
void func_800C8DC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C8DC0
void func_800C8EEC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C8EEC
void func_800C90AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800C90AC
void func_800C921C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800C921C
void func_800C9380(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); // func_800C9380
void BgCheck_RelocateMeshHeaderPointers(BgMeshHeader* header); // func_800C94E0
void BgCheck_RelocateMeshHeader(BgMeshHeader* meshSegPtr, BgMeshHeader** param_2); // func_800C9564
void BgCheck_RelocateAllMeshHeaders(BgCheckContext* bgCtxt, GlobalContext* ctxt); // func_800C9598
void func_800C9640(void); // func_800C9640
u32 BgCheck_GetPolygonAttributes(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index, s32 attributeIndex); // func_800C9694
u32 func_800C9704(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9704
void func_800C9728(void); // func_800C9728
UNK_TYPE4 func_800C9770(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9770
void func_800C97F8(void); // func_800C97F8
UNK_TYPE4 func_800C9844(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9844
void func_800C98CC(void); // func_800C98CC
UNK_TYPE4 func_800C9924(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9924
u32 func_800C99AC(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99AC
u32 func_800C99D4(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99D4
u32 func_800C99FC(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99FC
u32 func_800C9A24(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A24
u32 func_800C9A4C(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A4C
u32 func_800C9A7C(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A7C
u32 func_800C9AB0(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9AB0
u32 func_800C9AE4(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9AE4
u32 func_800C9B18(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B18
u32 func_800C9B40(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B40
u32 func_800C9B68(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B68
u32 func_800C9B90(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B90
u32 func_800C9BB8(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9BB8
u32 func_800C9BDC(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9BDC
u32 func_800C9C24(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index, UNK_TYPE4 param_4); // func_800C9C24
u32 func_800C9C74(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9C74
u32 func_800C9C9C(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9C9C
u32 func_800C9CC4(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9CC4
void func_800C9CEC(void); // func_800C9CEC
void func_800C9D14(void); // func_800C9D14
void func_800C9D50(void); // func_800C9D50
void func_800C9D8C(void); // func_800C9D8C
void func_800C9DDC(void); // func_800C9DDC
u32 func_800C9E18(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E18
u32 func_800C9E40(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E40
u32 func_800C9E88(BgCheckContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E88
void func_800C9EBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800C9EBC
void func_800CA1AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800CA1AC
void func_800CA1E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800CA1E8
void func_800CA22C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800CA22C
void func_800CA568(void); // func_800CA568
void func_800CA634(void); // func_800CA634
void func_800CA648(void); // func_800CA648
void func_800CA6B8(void); // func_800CA6B8
void func_800CA6D8(void); // func_800CA6D8
void func_800CA6F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800CA6F0
void func_800CA9D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800CA9D0
void func_800CAA14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800CAA14
void BgCheck2_UpdateActorPosition(BgCheckContext* bgCtxt, s32 index, Actor* actor); // func_800CAAD0
void BgCheck2_UpdateActorYRotation(BgCheckContext* bgCtxt, s32 index, Actor* actor); // func_800CAC0C
void BgCheck2_AttachToMesh(BgCheckContext* bgCtxt, Actor* actor, s32 index); // func_800CACA0
u32 BgCheck2_UpdateActorAttachedToMesh(BgCheckContext* bgCtxt, s32 index, Actor* actor); // func_800CAD2C
void BcCheck3_BgActorInit(BgActor* actor, UNK_TYPE4 param_2); // func_800CAE10
void BgCheck3_LoadMesh(GlobalContext* ctxt, BgActor* actor, BgMeshHeader* meshHeader); // func_800CAE34
void BgCheck3_ResetFlags(BgActor* actor); // func_800CAE7C
void func_800CAE88(BgActor* actor); // func_800CAE88
void func_800CAE9C(BgActor* actor); // func_800CAE9C
void func_800CAEB0(void); // func_800CAEB0
void func_800CAEE0(BgActor* actor); // func_800CAEE0
void func_800CAEF4(void); // func_800CAEF4
void func_800CAF24(BgActor* actor); // func_800CAF24
void func_800CAF38(BgActor* actor); // func_800CAF38
s32 func_800CAF4C(BgActor* actor); // func_800CAF4C
s32 func_800CAF70(BgActor* actor); // func_800CAF70
s32 func_800CAF94(BgActor* actor); // func_800CAF94
s32 func_800CAFB8(BgActor* actor); // func_800CAFB8
s32 func_800CAFDC(BgActor* actor); // func_800CAFDC
void func_800CB000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CB000
f32 Camera_fabsf(f32 f); // func_800CB210
f32 Camera_LengthVec3f(Vector3f* v); // func_800CB240
void func_800CB270(void); // func_800CB270
f32 Camera_Lerpf(f32 b, f32 a, f32 t, f32 minDist); // func_800CB330
s16 Camera_Lerps(s16 b, s16 a, f32 t, s16 minDist); // func_800CB398
void func_800CB42C(void); // func_800CB42C
void Camera_LerpVec3f(Vector3f* b, Vector3f* a, f32 tXZ, f32 tY, f32 minDist); // func_800CB4C0
void func_800CB544(Camera* camera); // func_800CB544
void func_800CB584(void); // func_800CB584
void func_800CB5DC(void); // func_800CB5DC
void func_800CB60C(void); // func_800CB60C
void func_800CB674(void); // func_800CB674
void func_800CB6C8(void); // func_800CB6C8
f32 func_800CB700(Camera* camera); // func_800CB700
void func_800CB780(void); // func_800CB780
void func_800CB7CC(void); // func_800CB7CC
void func_800CB7F8(void); // func_800CB7F8
void func_800CB828(void); // func_800CB828
void func_800CB854(void); // func_800CB854
void func_800CB880(void); // func_800CB880
void func_800CB8C8(void); // func_800CB8C8
void func_800CB8F4(void); // func_800CB8F4
void func_800CB924(void); // func_800CB924
void func_800CB950(void); // func_800CB950
void func_800CBA08(void); // func_800CBA08
void func_800CBA34(void); // func_800CBA34
void func_800CBA7C(void); // func_800CBA7C
void func_800CBAAC(void); // func_800CBAAC
void func_800CBAD4(void); // func_800CBAD4
void func_800CBB58(void); // func_800CBB58
void func_800CBB88(void); // func_800CBB88
void func_800CBC00(void); // func_800CBC00
void func_800CBC30(void); // func_800CBC30
void func_800CBC84(void); // func_800CBC84
void func_800CBFA4(void); // func_800CBFA4
void func_800CC000(void); // func_800CC000
void func_800CC128(void); // func_800CC128
void func_800CC1C4(void); // func_800CC1C4
void func_800CC260(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800CC260
void func_800CC488(void); // func_800CC488
void func_800CC56C(void); // func_800CC56C
void func_800CC5C8(void); // func_800CC5C8
void func_800CC740(void); // func_800CC740
void func_800CC7A8(void); // func_800CC7A8
void func_800CC804(void); // func_800CC804
void func_800CC874(void); // func_800CC874
void func_800CC938(void); // func_800CC938
void func_800CC958(void); // func_800CC958
void func_800CC9C0(void); // func_800CC9C0
void func_800CCCEC(void); // func_800CCCEC
void func_800CD04C(void); // func_800CD04C
void func_800CD288(void); // func_800CD288
void func_800CD2E0(void); // func_800CD2E0
void func_800CD2F0(void); // func_800CD2F0
void func_800CD3E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800CD3E4
void func_800CD44C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CD44C
void func_800CD634(void); // func_800CD634
void func_800CD6CC(void); // func_800CD6CC
void func_800CD6F8(void); // func_800CD6F8
void func_800CD834(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800CD834
void func_800CDA14(void); // func_800CDA14
void func_800CDB6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800CDB6C
void func_800CDE6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); // func_800CDE6C
void func_800CE2B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE2 param_9); // func_800CE2B8
void func_800CE5E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CE5E0
void func_800CE79C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CE79C
void func_800CE930(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CE930
void func_800CEAD8(void); // func_800CEAD8
void func_800CEC38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800CEC38
void func_800CED90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800CED90
s32 Camera_ModeNop(Camera* camera); // func_800CF3A4
s32 Camera_ModeNORM1(Camera* camera); // func_800CF3B4
s32 Camera_ModeNORM2(Camera* camera); // func_800D0874
s32 Camera_ModeNORM3(Camera* camera); // func_800D0894
s32 Camera_ModeNORM4(Camera* camera); // func_800D1228
s32 Camera_ModeNORM0(Camera* camera); // func_800D12B8
s32 Camera_ModePARA1(Camera* camera); // func_800D1A78
s32 Camera_ModePARA2(Camera* camera); // func_800D2AA8
s32 Camera_ModePARA3(Camera* camera); // func_800D2AC8
s32 Camera_ModePARA4(Camera* camera); // func_800D2AE8
s32 Camera_ModePARA0(Camera* camera); // func_800D2B08
s32 Camera_ModeJUMP1(Camera* camera); // func_800D2B28
s32 Camera_ModeJUMP2(Camera* camera); // func_800D2B48
s32 Camera_ModeJUMP3(Camera* camera); // func_800D3520
s32 Camera_ModeJUMP4(Camera* camera); // func_800D41E0
s32 Camera_ModeJUMP0(Camera* camera); // func_800D4200
s32 Camera_ModeBATT1(Camera* camera); // func_800D4220
s32 Camera_ModeBATT2(Camera* camera); // func_800D55A8
s32 Camera_ModeBATT3(Camera* camera); // func_800D55C8
s32 Camera_ModeBATT4(Camera* camera); // func_800D55E8
s32 Camera_ModeBATT0(Camera* camera); // func_800D5608
s32 Camera_ModeKEEP1(Camera* camera); // func_800D5628
s32 Camera_ModeKEEP2(Camera* camera); // func_800D67DC
s32 Camera_ModeKEEP3(Camera* camera); // func_800D67FC
s32 Camera_ModeKEEP4(Camera* camera); // func_800D73C8
void func_800D7C44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12); // func_800D7C44
s32 Camera_ModeKEEP0(Camera* camera); // func_800D7FA4
s32 Camera_ModeFIXD1(Camera* camera); // func_800D7FC4
s32 Camera_ModeFIXD2(Camera* camera); // func_800D83C8
s32 Camera_ModeFIXD3(Camera* camera); // func_800D8E08
s32 Camera_ModeFIXD4(Camera* camera); // func_800D8E28
s32 Camera_ModeFIXD0(Camera* camera); // func_800D8E48
s32 Camera_ModeSUBJ1(Camera* camera); // func_800D8E68
s32 Camera_ModeSUBJ2(Camera* camera); // func_800D947C
s32 Camera_ModeSUBJ3(Camera* camera); // func_800D949C
s32 Camera_ModeSUBJ4(Camera* camera); // func_800D94BC
s32 Camera_ModeSUBJ0(Camera* camera); // func_800D94DC
s32 Camera_ModeDATA0(Camera* camera); // func_800D94FC
s32 Camera_ModeDATA1(Camera* camera); // func_800D951C
s32 Camera_ModeDATA2(Camera* camera); // func_800D953C
s32 Camera_ModeDATA3(Camera* camera); // func_800D955C
s32 Camera_ModeDATA4(Camera* camera); // func_800D957C
s32 Camera_ModeUNIQ1(Camera* camera); // func_800D959C
s32 Camera_ModeUNIQ2(Camera* camera); // func_800D95BC
s32 Camera_ModeUNIQ3(Camera* camera); // func_800D99D0
s32 Camera_ModeUNIQ4(Camera* camera); // func_800D9A2C
s32 Camera_ModeUNIQ5(Camera* camera); // func_800D9A88
s32 Camera_ModeUNIQ0(Camera* camera); // func_800D9AE4
s32 Camera_ModeUNIQ6(Camera* camera); // func_800DA3B8
s32 Camera_ModeUNIQ7(Camera* camera); // func_800DA4EC
s32 Camera_ModeUNIQ8(Camera* camera); // func_800DA50C
s32 Camera_ModeUNIQ9(Camera* camera); // func_800DA52C
s32 Camera_ModeDEMO1(Camera* camera); // func_800DA54C
s32 Camera_ModeDEMO2(Camera* camera); // func_800DAD10
s32 Camera_ModeDEMO3(Camera* camera); // func_800DB804
s32 Camera_ModeDEMO4(Camera* camera); // func_800DBB14
s32 Camera_ModeDEMO5(Camera* camera); // func_800DC270
s32 Camera_ModeDEMO6(Camera* camera); // func_800DC718
s32 Camera_ModeDEMO7(Camera* camera); // func_800DC738
s32 Camera_ModeDEMO8(Camera* camera); // func_800DC758
s32 Camera_ModeDEMO9(Camera* camera); // func_800DC778
s32 Camera_ModeDEMO0(Camera* camera); // func_800DC798
s32 Camera_ModeSPEC0(Camera* camera); // func_800DCC90
s32 Camera_ModeSPEC1(Camera* camera); // func_800DCCB0
s32 Camera_ModeSPEC2(Camera* camera); // func_800DCCD0
s32 Camera_ModeSPEC3(Camera* camera); // func_800DCCF0
s32 Camera_ModeSPEC4(Camera* camera); // func_800DCD10
s32 Camera_ModeSPEC5(Camera* camera); // func_800DCD30
s32 Camera_ModeSPEC6(Camera* camera); // func_800DD0FC
s32 Camera_ModeSPEC7(Camera* camera); // func_800DD11C
s32 Camera_ModeSPEC8(Camera* camera); // func_800DD13C
s32 Camera_ModeSPEC9(Camera* camera); // func_800DD5B8
Camera* Camera_Alloc(View* view, BgCheckContext* bg, GlobalContext* ctxt); // func_800DDD58
void Camera_Free(Camera* camera); // func_800DDDA8
void Camera_Init(Camera* camera, View* view, BgCheckContext* bg, GlobalContext* ctxt); // func_800DDDD0
void func_800DDFE0(void); // func_800DDFE0
void func_800DE0EC(Camera* camera, Actor* actor); // func_800DE0EC
s32 func_800DE308(Camera* camera, UNK_TYPE2 uParm2); // func_800DE308
void func_800DE324(void); // func_800DE324
void func_800DE62C(void); // func_800DE62C
void func_800DE840(void); // func_800DE840
void func_800DE890(void); // func_800DE890
UNK_TYPE4 func_800DE954(Camera* camera); // func_800DE954
Vector3s* Camera_Update(Vector3s* param_1, Camera* camera); // func_800DE9B0
void func_800DF498(void); // func_800DF498
unsigned int Camera_SetMode(Camera* camera, s16 mode, char param_3); // func_800DF4D0
void func_800DF840(void); // func_800DF840
void func_800DF86C(void); // func_800DF86C
void func_800DF8EC(void); // func_800DF8EC
int func_800DFAC8(Camera* camera, short param_2); // func_800DFAC8
unsigned int func_800DFB14(Camera* camera, unsigned int param_2); // func_800DFB14
void func_800DFC1C(void); // func_800DFC1C
void func_800DFC40(void); // func_800DFC40
int func_800DFC68(Camera* camera); // func_800DFC68
void func_800DFC90(void); // func_800DFC90
void func_800DFCB4(void); // func_800DFCB4
void func_800DFCDC(void); // func_800DFCDC
void func_800DFD04(void); // func_800DFD04
void func_800DFD78(void); // func_800DFD78
UNK_TYPE4 func_800DFEF0(s32 param_1, u16 param_2); // func_800DFEF0
UNK_TYPE4 func_800DFF18(Camera* iParm1, UNK_TYPE2 uParm2); // func_800DFF18
UNK_TYPE4 func_800DFF34(s32 param_1); // func_800DFF34
UNK_TYPE4 func_800DFF44(void); // func_800DFF44
s16 Camera_SetFlags(Camera* iParm1, s16 flags); // func_800DFF60
s16 Camera_ClearFlags(Camera* camera, s16 flags); // func_800DFF84
void func_800DFFAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800DFFAC
UNK_TYPE4 func_800E007C(Camera* param_1, Camera* param_2); // func_800E007C
UNK_TYPE4 func_800E01AC(void); // func_800E01AC
void func_800E01B8(void); // func_800E01B8
void func_800E01DC(s32 param_1, u32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800E01DC
UNK_TYPE4 func_800E0228(void); // func_800E0228
void func_800E0238(void); // func_800E0238
void func_800E02AC(void); // func_800E02AC
void func_800E0308(void); // func_800E0308
void func_800E031C(void); // func_800E031C
void func_800E0348(Camera* camera); // func_800E0348
s800E03A0* func_800E03A0(s32 a0); // func_800E03A0
void func_800E03CC(u8* param_1); // func_800E03CC
f32 Collision_GetDamageAndEffectOnBumper(ColCommon* toucher, ColBodyInfo* toucherBody, ColCommon* bumper, ColBodyInfo* bumperBody, u32* effect); // func_800E0410
void func_800E04BC(void); // func_800E04BC
u32 Collision_GetToucherDamage(ColCommon* toucher, ColBodyInfo* toucherBody, ColCommon* bumper); // func_800E04EC
s32 Collision_InitCommonDefault(GlobalContext* ctxt, ColCommon* shape); // func_800E0538
s32 Collision_FiniCommon(GlobalContext* ctxt, ColCommon* shape); // func_800E0580
void func_800E0594(void); // func_800E0594
void func_800E05D4(void); // func_800E05D4
s32 Collision_InitCommonWithData(GlobalContext* ctxt, ColCommon* shape, Actor* actor, ColCommonInit* init); // func_800E0618
void Collision_ResetCommonForAT(GlobalContext* ctxt, ColCommon* shape); // func_800E065C
void Collision_ResetCommonForAC(GlobalContext* ctxt, ColCommon* shape); // func_800E0678
void Collision_ResetCommonForOT(GlobalContext* ctxt, ColCommon* shape); // func_800E0694
s32 Collision_InitTouchDefault(GlobalContext* ctxt, ColTouch* touch); // func_800E06BC
s32 Collision_FiniTouch(GlobalContext* ctxt, ColTouch* touch); // func_800E06E4
s32 Collision_InitTouchWithData(GlobalContext* ctxt, ColTouch* touch, ColTouchInit* init); // func_800E06F8
void Collision_nop800E0720(GlobalContext* ctxt, ColBodyInfo* body); // func_800E0720
s32 Collision_InitBumpDefault(GlobalContext* ctxt, ColBump* bump); // func_800E0730
s32 Collision_FiniBump(GlobalContext* ctxt, ColBump* bump); // func_800E0760
s32 Collision_InitBumpWithData(GlobalContext* ctxt, ColBump* bump, ColBumpInit* init); // func_800E0774
s32 Collision_InitBodyDefault(GlobalContext* ctxt, ColBodyInfo* body); // func_800E079C
s32 Collision_FiniBody(GlobalContext* ctxt, ColBodyInfo* body); // func_800E081C
s32 Collision_InitBodyWithData(GlobalContext* ctxt, ColBodyInfo* body, ColBodyInfoInit* init); // func_800E085C
void Collision_ResetBodyForAT(GlobalContext* ctxt, ColBodyInfo* body); // func_800E08D4
void Collision_ResetBodyForAC(GlobalContext* ctxt, ColBodyInfo* body); // func_800E090C
void Collision_ResetBodyForOT(GlobalContext* ctxt, ColBodyInfo* body); // func_800E0944
s32 Collision_InitSphereParamsDefault(GlobalContext* ctxt, ColSphereParams* params); // func_800E095C
s32 Collision_FiniSphereParams(GlobalContext* ctxt, ColSphereParams* params); // func_800E09A4
s32 Collision_InitSphereParamsWithData(GlobalContext* ctxt, ColSphereParams* params, ColSphereParamsInit* init); // func_800E09B8
s32 Collision_InitSphereGroupElemDefault(GlobalContext* pzParm1, ColSphereGroupElement* elem); // func_800E0A10
s32 Collision_FiniSphereGroupElem(GlobalContext* ctxt, ColSphereGroupElement* elem); // func_800E0A50
s32 Collision_InitSphereGroupElemWithData(GlobalContext* ctxt, ColSphereGroupElement* elem, ColSphereGroupElementInit* init); // func_800E0A90
s32 Collision_ResetSphereGroupElemForAT(GlobalContext* ctxt, ColSphereGroupElement* elem); // func_800E0AE0
s32 Collision_ResetSphereGroupElemForAC(GlobalContext* ctxt, ColSphereGroupElement* elem); // func_800E0B04
s32 Collision_ResetSphereGroupElemForOT(GlobalContext* ctxt, ColSphereGroupElement* elem); // func_800E0B28
s32 Collision_InitSphereGroupDefault(GlobalContext* ctxt, ColSphereGroup* sphereGroup); // func_800E0B4C
void func_800E0B78(void); // func_800E0B78
s32 Collision_FiniSphereGroup(GlobalContext* ctxt, ColSphereGroup* sphereGroup); // func_800E0C18
void func_800E0CA8(void); // func_800E0CA8
void func_800E0D84(void); // func_800E0D84
s32 Collision_InitSphereGroupWithData(GlobalContext* ctxt, ColSphereGroup* sphereGroup, Actor* actor, ColSphereGroupInit* init, ColSphereGroupElement* spheres); // func_800E0E60
s32 Collision_InitSphereGroup(GlobalContext* ctxt, ColSphereGroup* sphereGroup, Actor* actor, ColSphereGroupInit* init, ColSphereGroupElement* spheres); // func_800E0F14
s32 Collision_ResetSphereGroupForAT(GlobalContext* ctxt, ColSphereGroup* spheres); // func_800E0F68
s32 Collision_ResetSphereGroupForAC(GlobalContext* ctxt, ColSphereGroup* spheres); // func_800E0FF4
s32 Collision_ResetSphereGroupForOT(GlobalContext* ctst, ColSphereGroup* spheres); // func_800E1080
s32 Collision_InitCylinderParamsDefault(GlobalContext* ctxt, ColCylinderParams* params); // func_800E110C
s32 Collision_FiniCylinderParams(GlobalContext* ctxt, ColCylinderParams* params); // func_800E1148
s32 Collision_InitCylinderParamsWithData(GlobalContext* ctxt, ColCylinderParams* info, ColCylinderParams* init); // func_800E115C
s32 Collision_InitCylinderDefault(GlobalContext* ctxt, ColCylinder* cylinder); // func_800E119C
s32 Collision_FiniCylinder(GlobalContext* ctxt, ColCylinder* cylinder); // func_800E11EC
void func_800E123C(void); // func_800E123C
void func_800E12A4(void); // func_800E12A4
s32 Collision_InitCylinderWithData(GlobalContext* ctxt, ColCylinder* cylinder, Actor* actor, ColCylinderInit* init); // func_800E130C
s32 Collision_InitCylinder(GlobalContext* ctxt, ColCylinder* cylinder, Actor* actor, ColCylinderInit* init); // func_800E1374
s32 Collision_ResetCylinderForAT(GlobalContext* ctxt, ColCylinder* cylinder); // func_800E13C0
s32 Collision_ResetCylinderForAC(GlobalContext* ctxt, ColCylinder* cylinder); // func_800E1400
s32 Collision_ReseCylinderForOT(GlobalContext* ctxt, ColCylinder* cylinder); // func_800E1440
s32 Collision_InitTriParamsDefault(GlobalContext* ctxt, ColTriParams* coords); // func_800E1480
s32 Collision_FiniTriParams(GlobalContext* ctxt, ColTriParams* params); // func_800E14CC
s32 Collision_InitTriParamsWithData(GlobalContext* ctxt, ColTriParams* params, ColTriParamsInit* init); // func_800E14E0
s32 Collision_InitTriDefault(GlobalContext* ctxt, ColTri* elem); // func_800E1594
s32 Collision_FiniTri(GlobalContext* ctxt, ColTri* elem); // func_800E15D4
s32 Collision_InitTriWithData(GlobalContext* ctxt, ColTri* elem, ColTriInit* init); // func_800E1614
s32 Collision_ResetTriForAT(GlobalContext* ctxt, ColTri* tri); // func_800E1664
s32 Collision_ResetTriForAC(GlobalContext* ctxt, ColTri* tri); // func_800E1688
s32 func_800E16AC(GlobalContext* ctxt, ColTri* tri); // func_800E16AC
s32 Collision_InitTriGroupDefault(GlobalContext* ctxt, ColTriGroup* quadGroup); // func_800E16D0
void func_800E16FC(void); // func_800E16FC
s32 Collision_FiniTriGroup(GlobalContext* ctxt, ColTriGroup* triGroup); // func_800E17B4
void func_800E1858(void); // func_800E1858
s32 Collision_InitTriGroupWithData(GlobalContext* ctxt, ColTriGroup* triGroup, Actor* actor, ColTriGroupInit* init, ColTri* tris); // func_800E1958
s32 Collision_InitTriGroup(GlobalContext* ctxt, ColTriGroup* triGroup, Actor* actor, ColTriGroupInit* init, ColTri* tris); // func_800E1A24
s32 Collision_ResetTriGroupForAT(GlobalContext* ctxt, ColTriGroup* tris); // func_800E1A78
s32 Collision_ResetTriGroupForAC(GlobalContext* ctxt, ColTriGroup* tris); // func_800E1B18
s32 Collision_ResetTriGroupForOT(GlobalContext* ctxt, ColTriGroup* tris); // func_800E1BB8
s32 Collision_InitQuadParamsDefault(GlobalContext* ctxt, ColQuadParams* params); // func_800E1C58
s32 Collision_FiniQuadParams(GlobalContext* ctxt, ColQuadParams* params); // func_800E1CA4
s32 Collision_ResetQuadParamsForAT(GlobalContext* ctxt, ColQuadParams* params); // func_800E1CB8
void Collision_QuadCalcMidpoints(ColQuadParams* params); // func_800E1CD4
s32 Collision_InitQuadParamsWithData(GlobalContext* ctxt, ColQuadParams* params, ColQuadParams* init); // func_800E1D90
s32 Collision_InitQuadDefault(GlobalContext* ctxt, ColQuad* quad); // func_800E1E18
s32 Collision_FiniQuad(GlobalContext* ctxt, ColQuad* quad); // func_800E1E68
void func_800E1EB8(void); // func_800E1EB8
s32 Collision_InitQuadWithData(GlobalContext* ctxt, ColQuad* quad, Actor* actor, ColQuadInit* init); // func_800E1F20
s32 Collision_InitQuad(GlobalContext* ctxt, ColQuad* quad, Actor* actor, ColQuadInit* init); // func_800E1F88
s32 Collision_ResetQuadForAT(GlobalContext* ctxt, ColQuad* quad); // func_800E1FD4
s32 Collision_ResetQuadForAC(GlobalContext* param_1, ColQuad* quad); // func_800E2024
s32 Collision_ResetQuadForOT(GlobalContext* ctxt, ColCommon* quad); // func_800E2064
void func_800E20A4(void); // func_800E20A4
s32 Collision_InitSphereDefault(GlobalContext* ctxt, ColSphere* sphere); // func_800E2154
s32 Collision_FiniSphere(GlobalContext* pzParm1, ColSphere* sphere); // func_800E21A4
s32 Collision_InitSphereWithData(GlobalContext* ctxt, ColSphere* sphere, Actor* actor, ColSphereInit* info); // func_800E21F4
s32 Collision_InitSphere(GlobalContext* ctxt, ColSphere* sphere, Actor* actor, ColSphereInit* init); // func_800E225C
s32 Collision_ResetSphereForAT(GlobalContext* ctxt, ColSphere* sphere); // func_800E22A8
s32 Collision_ResetSphereForAC(GlobalContext* ctxt, ColSphere* sphere); // func_800E22E8
s32 Collision_ResetSphereForOT(GlobalContext* ctxt, ColSphere* sphere); // func_800E2328
void func_800E2368(void); // func_800E2368
UNK_TYPE4 func_800E23B0(void); // func_800E23B0
void func_800E23C4(void); // func_800E23C4
void func_800E2408(void); // func_800E2408
s32 func_800E2434(GlobalContext* ctxt, int param_2); // func_800E2434
void Collision_Init(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E2450
void Collision_Fini(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E2470
void Collision_Reset(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E2480
void Collision_EnableEditMode(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E2528
void Collision_EnableAppendMode(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E2540
s32 Collision_AddAT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape); // func_800E2558
s32 Collision_AddIndexAT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape, s32 index); // func_800E2634
s32 Collision_AddAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape); // func_800E2740
s32 collision_AddIndexAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape, s32 index); // func_800E281C
s32 Collision_AddOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape); // func_800E2928
s32 Collision_AddIndexOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape, s32 index); // func_800E2A04
s32 Collision_AddGroup4(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* shape); // func_800E2B10
s32 Collision_CantBeToucherAC(ColBodyInfo* iParm1); // func_800E2B98
s32 Collision_CantBeBumperAC(ColBodyInfo* iParm1); // func_800E2BBC
s32 Collision_ToucherIsExcluded(ColBodyInfo* toucher, ColBodyInfo* bumper); // func_800E2BE0
void func_800E2C08(void); // func_800E2C08
void func_800E2C1C(void); // func_800E2C1C
void func_800E2D88(void); // func_800E2D88
void func_800E2EF4(void); // func_800E2EF4
void func_800E2F30(void); // func_800E2F30
void func_800E2F54(void); // func_800E2F54
void func_800E2F78(void); // func_800E2F78
void func_800E30C8(void); // func_800E30C8
void func_800E3168(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, ColCommon* bumper, ColBodyInfo* bumperBody, Vector3f* param_6); // func_800E3168
void func_800E3304(ColCommon* toucher, ColCommon* bumper); // func_800E3304
s32 Collision_HandleCollisionATWithAC(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, Vector3f* toucherLoc, ColCommon* bumper, ColBodyInfo* bumperBody, Vector3f* bumperLoc, Vector3f* param_8); // func_800E3324
void Collision_TriCalcAvgPoint(ColTri* tri, Vector3f* avg); // func_800E35C8
void collision_quad_cal_avg_point(ColQuadParams* quad, Vector3f* avg); // func_800E362C
void Collision_SphereGroupWithSphereGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColSphereGroup* bumpee); // func_800E36AC
void Collision_SphereGroupWithCylinderAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColCylinder* bumpee); // func_800E38F8
void Collision_SphereGroupWithTriGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColTriGroup* bumpee); // func_800E3B18
void Collision_SphereGroupWithQuadAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColQuad* bumpee); // func_800E3CC0
void Collision_SphereGroupWithSphereAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColSphere* bumpee); // func_800E3E6C
void Collision_CylinderWithSphereGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColSphereGroup* bumpee); // func_800E4058
void Collision_CylinderWithCylinderAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColCylinder* bumpee); // func_800E4298
void Collision_CylinderWithTriGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColTriGroup* bumpee); // func_800E44C0
void Collision_CylinderWithQuadAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColQuad* bumpee); // func_800E4628
void Collision_CylinderWithSphereAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColSphere* bumpee); // func_800E47B8
void Collision_TriGroupWithSphereGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColTriGroup* toucher, ColSphereGroup* bumpee); // func_800E494C
void Collision_TriGroupWithCylinderAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColTriGroup* toucher, ColCylinder* bumpee); // func_800E4B08
void Collision_TriGroupWithTriGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColTriGroup* toucher, ColTriGroup* bumpee); // func_800E4C70
void Collision_TriGroupWithQuad(GlobalContext* ctxt, CollisionContext* colCtxt, ColTriGroup* toucher, ColQuad* bumpee); // func_800E4E24
void Collision_TriGroupWithSphereAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColTriGroup* toucher, ColSphere* bumpee); // func_800E4FE4
void Collision_QuadWithSphereGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColQuad* toucher, ColSphereGroup* bumpee); // func_800E5154
void Collision_QuadWithCylinderAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColQuad* toucher, ColCylinder* bumpee); // func_800E531C
void Collision_QuadWithTriGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColQuad* toucher, ColTriGroup* bumpee); // func_800E54DC
void Collision_QuadWithQuadAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColQuad* toucher, ColQuad* bumpee); // func_800E56B8
void Collision_QuadWithSphereAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColQuad* toucher, ColSphere* bumpee); // func_800E5874
void Collision_SphereWithSphereGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColSphereGroup* bumpee); // func_800E59A4
void Collision_SphereWithCylinderAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColCylinder* bumpee); // func_800E5B94
void Collision_SphereWithTriGroupAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColTriGroup* bumpee); // func_800E5D10
void Collision_SphereWithQuadAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColQuad* bumpee); // func_800E5E54
void Collision_SphereWithSphereAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColSphere* bumpee); // func_800E5F6C
void func_800E60C0(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* spheres); // func_800E60C0
void func_800E61A0(void); // func_800E61A0
void func_800E6238(void); // func_800E6238
void func_800E6320(void); // func_800E6320
void func_800E63B8(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* sphere); // func_800E63B8
void func_800E6450(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E6450
void Collision_CollideWithAC(GlobalContext* ctxt, CollisionContext* colCtxt, ColCommon* colObj); // func_800E6524
void Collision_DoATWithAC(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E6654
void func_800E6724(void); // func_800E6724
void Collision_HandleCollisionOTWithOT(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, Vector3f* toucherLoc, ColCommon* bumper, ColBodyInfo* bumperBody, Vector3f* bumperLoc, f32 param_8); // func_800E6760
void Collision_SphereGroupWithSphereGroupOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColSphereGroup* bumpee); // func_800E6A9C
void Collision_SphereGroupWithCylinderOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColCylinder* bumpee); // func_800E6C84
void Collision_SphereGroupWithSphereOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphereGroup* toucher, ColSphere* bumpee); // func_800E6DF4
void Collision_CylinderWithSphereGroupOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColSphereGroup* bumpee); // func_800E6F64
void Collision_CylinderWithCylinderOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColCylinder* bumpee); // func_800E6F90
void Collision_CylinderWithSphereOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColCylinder* toucher, ColSphere* bumpee); // func_800E7060
void Collision_SphereWithSphereGroupOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColSphereGroup* bumpee); // func_800E7130
void Collision_SphereWithCylinderOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColCylinder* bumpee); // func_800E715C
void Collision_SphereWithSphereOT(GlobalContext* ctxt, CollisionContext* colCtxt, ColSphere* toucher, ColSphere* bumpee); // func_800E7188
UNK_TYPE4 func_800E7264(ColCommon* iParm1); // func_800E7264
UNK_TYPE4 func_800E7288(ColCommon* piParm1, ColCommon* piParm2); // func_800E7288
void Collision_DoOTWithOT(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E7308
void func_800E7494(ActorA0* param_1); // func_800E7494
void func_800E74DC(ActorA0* param_1); // func_800E74DC
void func_800E7508(s32 param_1, UNK_PTR param_2); // func_800E7508
void func_800E7530(ActorA0* param_1, ActorDamageChart* param_2, UNK_PTR param_3); // func_800E7530
void func_800E755C(ActorA0* puParm1, ActorDamageChart* uParm2, UNK_PTR puParm3); // func_800E755C
void func_800E7590(void); // func_800E7590
void func_800E75C8(void); // func_800E75C8
void func_800E77EC(void); // func_800E77EC
void func_800E7894(void); // func_800E7894
void func_800E78B4(void); // func_800E78B4
void func_800E7948(void); // func_800E7948
void func_800E7968(void); // func_800E7968
void func_800E7988(GlobalContext* ctxt, CollisionContext* colCtxt); // func_800E7988
void func_800E7A48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7A48
void func_800E7B54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7B54
void func_800E7BCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7BCC
void func_800E7C64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800E7C64
void func_800E7DA8(void); // func_800E7DA8
void func_800E7DCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800E7DCC
void Collision_CylinderMoveToActor(Actor* actor, ColCylinder* cylinder); // func_800E7DF8
void Collision_CylinderSetLoc(ColCylinder* cylinder, Vector3s* loc); // func_800E7E3C
void Collision_QuadSetCoords(ColQuad* iParm1, Vector3f* pzParm2, Vector3f* pzParm3, Vector3f* pzParm4, Vector3f* param_5); // func_800E7E5C
void Collision_TriGroupSetCoordsAtIndex(ColTriGroup* tris, s32 index, Vector3f* pzParm3, Vector3f* pzParm4, Vector3f* param_5); // func_800E7ECC
void Collision_InitTriParamsAtIndex(GlobalContext* ctxt, ColTriGroup* tris, s32 index, ColTriParamsInit* init); // func_800E7F8C
void func_800E7FDC(void); // func_800E7FDC
void func_800E8160(void); // func_800E8160
void func_800E823C(void); // func_800E823C
void func_800E8318(void); // func_800E8318
void func_800E8478(void); // func_800E8478
void func_800E85D4(void); // func_800E85D4
void func_800E8668(void); // func_800E8668
void func_800E8690(void); // func_800E8690
void func_800E86C0(void); // func_800E86C0
void func_800E86E0(void); // func_800E86E0
void func_800E8784(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800E8784
void func_800E8EA0(GlobalContext* ctxt, Actor* actor, u16 param_3); // func_800E8EA0
s32 nop_800E8ED0(UNK_TYPE4 param_1); // func_800E8ED0
void nop_800E8EE0(UNK_TYPE4 param_1); // func_800E8EE0
s32 nop_800E8EEC(UNK_TYPE4 param_1); // func_800E8EEC
void nop_800E8EFC(UNK_TYPE4 param_1); // func_800E8EFC
s32 func_800E8F08(Vector3s* param_1, Vector3s* param_2); // func_800E8F08
s32 func_800E8FA4(Actor* actor, Vector3f* param_2, Vector3s* param_3, Vector3s* param_4); // func_800E8FA4
s32 func_800E9138(GlobalContext* ctxt, Actor* actor, Vector3s* param_3, Vector3s* param_4, f32 param_5); // func_800E9138
s32 func_800E9250(GlobalContext* ctxt, Actor* actor, Vector3s* param_3, Vector3s* param_4, Vector3f param_5); // func_800E9250
void func_800E9360(void); // func_800E9360
void static_context_init(void); // func_800E93E0
void func_800E9470(void); // func_800E9470
void func_800E9488(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE1 param_10, UNK_TYPE1 param_11, UNK_TYPE1 param_12, UNK_TYPE1 param_13, UNK_TYPE2 param_14, UNK_TYPE4 param_15); // func_800E9488
void func_800E9564(void); // func_800E9564
void func_800E95F4(void); // func_800E95F4
void func_800E97D8(void); // func_800E97D8
void func_800E992C(void); // func_800E992C
void func_800E99B0(void); // func_800E99B0
void func_800E9C90(void); // func_800E9C90
void func_800E9CA0(s32 param_1, UNK_TYPE1 param_2, s8* param_3); // func_800E9CA0
void func_800E9CFC(void); // func_800E9CFC
void func_800E9DBC(void); // func_800E9DBC
void func_800E9E94(void); // func_800E9E94
void func_800E9F78(GraphicsContext* gCtxt); // func_800E9F78
void Demo_Init(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA060
void func_800EA0D4(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA0D4
void func_800EA0EC(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA0EC
void Demo_StepCutscene1(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA110
void Demo_StepCutscene2(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA15C
void Demo_Nop800EA210(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA210
s32 func_800EA220(GlobalContext* ctxt, CutsceneContext* cCtxt, f32 fParm3); // func_800EA220
void func_800EA258(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA258
void func_800EA2B8(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EA2B8
void func_800EA324(GlobalContext* ctxt, CutsceneContext* cCtxt, UNK_PTR puParm3); // func_800EA324
void func_800EABAC(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EABAC
void func_800EAC08(GlobalContext* ctxt, CutsceneContext* cCtxt, unsigned short* puParm3); // func_800EAC08
void func_800EAC44(GlobalContext* ctxt, CutsceneContext* cCtxt, unsigned short* puParm3); // func_800EAC44
void func_800EAC94(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EAC94
void func_800EAD14(GlobalContext* ctxt, CutsceneContext* cCtxt, int iParm3); // func_800EAD14
void func_800EAD48(GlobalContext* ctxt, CutsceneContext* cCtxt, int iParm3); // func_800EAD48
void func_800EAD7C(GlobalContext* ctxt, CutsceneContext* cCtxt, int iParm3); // func_800EAD7C
void func_800EADB0(GlobalContext* ctxt, CutsceneContext* cCtxt, UNK_PTR puParm3); // func_800EADB0
void func_800EAECC(GlobalContext* ctxt, CutsceneContext* cCtxt, int iParm3); // func_800EAECC
void func_800EAF20(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EAF20
void func_800EAFE0(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EAFE0
void func_800EB1DC(GlobalContext* ctxt, CutsceneContext* cCtxt, int iParm3); // func_800EB1DC
void func_800EB364(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EB364
void func_800EB4B4(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EB4B4
void func_800EB6F8(GlobalContext* ctxt, CutsceneContext* cCtxt, UNK_PTR puParm3); // func_800EB6F8
void func_800EBB68(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EBB68
void func_800EBCD0(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EBCD0
void func_800EBD60(GlobalContext* ctxt, CutsceneContext* cCtxt, short* psParm3); // func_800EBD60
s32 func_800EC678(GlobalContext* ctxt, void* pvParm2); // func_800EC678
void func_800EC6D4(void); // func_800EC6D4
void func_800EC924(GlobalContext* ctxt, CutsceneContext* cCtxt, unsigned short* puParm3); // func_800EC924
void func_800ECD7C(CutsceneContext* cCtxt, void** param_2, short param_3); // func_800ECD7C
void Demo_ProcessData(GlobalContext* ctxt, CutsceneContext* cCtxt, u16* data, unsigned short* commandReadHead); // func_800ECE40
void func_800ED980(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800ED980
void func_800ED9C4(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800ED9C4
void func_800EDA04(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EDA04
void func_800EDA84(GlobalContext* ctxt, CutsceneContext* cCtxt); // func_800EDA84
void func_800EDBE0(GlobalContext* ctxt); // func_800EDBE0
void nop_800EDDB0(GlobalContext* ctxt); // func_800EDDB0
void func_800EDDBC(void); // func_800EDDBC
void func_800EDDCC(GlobalContext* ctxt, unsigned int uParm2); // func_800EDDCC
void func_800EDE34(Actor* actor, GlobalContext* ctxt, int param_3); // func_800EDE34
void func_800EDF24(void); // func_800EDF24
void func_800EDF78(Actor* actor, GlobalContext* ctxt, int iParm3); // func_800EDF78
void func_800EE0CC(Actor* actor, GlobalContext* ctxt, int iParm3); // func_800EE0CC
void func_800EE1D8(void); // func_800EE1D8
void func_800EE200(void); // func_800EE200
u32 func_800EE29C(GlobalContext* ctxt, u32 uParm2); // func_800EE29C
u32 func_800EE2F4(GlobalContext* ctxt); // func_800EE2F4
void func_800EE320(GlobalContext* ctxt, s16 index); // func_800EE320
void func_800EE364(GlobalContext* ctxt, s16 index); // func_800EE364
void func_800EE400(GlobalContext* ctxt, s16 index); // func_800EE400
void func_800EE5FC(GlobalContext* ctxt, s16 index); // func_800EE5FC
void func_800EE7D8(GlobalContext* ctxt, s16 index); // func_800EE7D8
void func_800EE940(GlobalContext* ctxt, s16 index); // func_800EE940
void func_800EEA48(GlobalContext* ctxt, s16 index); // func_800EEA48
void func_800EEC18(GlobalContext* ctxt, s16 index); // func_800EEC18
void func_800EED20(GlobalContext* ctxt, s16 index); // func_800EED20
void func_800EEE34(GlobalContext* ctxt, s16 index); // func_800EEE34
void func_800EEF4C(GlobalContext* ctxt, s16 index); // func_800EEF4C
void func_800EF054(GlobalContext* ctxt, s16 index); // func_800EF054
void func_800EF0F0(GlobalContext* ctxt, s16 index); // func_800EF0F0
void func_800EF1F4(GlobalContext* ctxt, s16 index); // func_800EF1F4
void func_800EF2AC(GlobalContext* ctxt, s16 index); // func_800EF2AC
void func_800EF364(GlobalContext* ctxt, s16 index); // func_800EF364
void func_800EF4D4(GlobalContext* ctxt, s16 index); // func_800EF4D4
void func_800EF65C(GlobalContext* ctxt, s16 index); // func_800EF65C
void func_800EF780(GlobalContext* ctxt, s16 index); // func_800EF780
void func_800EF89C(GlobalContext* ctxt, s16 index); // func_800EF89C
void func_800EF984(GlobalContext* ctxt, s16 index); // func_800EF984
void func_800EFAB8(GlobalContext* ctxt, s16 index); // func_800EFAB8
void func_800EFBFC(GlobalContext* ctxt, s16 index); // func_800EFBFC
void func_800EFD44(GlobalContext* ctxt, s16 index); // func_800EFD44
void EffFootmark_Init(GlobalContext* ctxt); // func_800EFE60
void EffFootmark_Add(GlobalContext* ctxt, z_Matrix* displayMatrix, Actor* actor, u8 id, Vector3f* location, u16 size, u8 red, u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay); // func_800EFF04
void EffFootmark_Update(GlobalContext* ctxt); // func_800F00BC
void EffFootmark_Draw(GlobalContext* ctxt); // func_800F01C8
void func_800F0390(GlobalContext* ctxt); // func_800F0390
void func_800F03C0(GlobalContext* ctxt); // func_800F03C0
void func_800F048C(GlobalContext* ctxt, Vector3f* param_2, u8 param_3, u16 param_4, u8 param_5); // func_800F048C
void func_800F0568(void); // func_800F0568
void func_800F0590(void); // func_800F0590
void func_800F05C0(void); // func_800F05C0
void func_800F07C0(void); // func_800F07C0
void func_800F0888(void); // func_800F0888
void func_800F0944(void); // func_800F0944
void func_800F09B4(void); // func_800F09B4
void func_800F0A20(void); // func_800F0A20
void func_800F0A94(void); // func_800F0A94
void func_800F0BB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800F0BB4
void func_800F0CE4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_800F0CE4
void func_800F0DD4(void); // func_800F0DD4
void func_800F0E94(void); // func_800F0E94
void func_800F0EEC(void); // func_800F0EEC
void func_800F0F28(void); // func_800F0F28
void func_800F0FF0(void); // func_800F0FF0
void func_800F10AC(void); // func_800F10AC
void func_800F112C(void); // func_800F112C
void func_800F1250(void); // func_800F1250
void func_800F12D0(GlobalContext* ctxt); // func_800F12D0
void func_800F1304(void); // func_800F1304
void func_800F1374(int param_1, short param_2); // func_800F1374
void func_800F13E8(void); // func_800F13E8
s16 func_800F1460(s16 param_1); // func_800F1460
ActorCutscene* ActorCutscene_GetCutsceneImpl(s16 index); // func_800F14F8
void ActorCutscene_Init(GlobalContext* ctxt, ActorCutscene* cutscenes, s32 num); // func_800F1544
void func_800F15D8(Camera* camera); // func_800F15D8
void ActorCutscene_ClearWaiting(void); // func_800F1648
void ActorCutscene_ClearNextCutscenes(void); // func_800F1678
void ActorCutscene_MarkNextCutscenes(void); // func_800F16A8
void ActorCutscene_End(void); // func_800F17FC
void ActorCutscene_Update(void); // func_800F1A7C
void ActorCutscene_SetIntentToPlay(s16 index); // func_800F1BA4
s16 ActorCutscene_GetCanPlayNext(s16 index); // func_800F1BE4
s16 ActorCutscene_StartAndSetUnkLinkFields(s16 index, Actor* actor); // func_800F1C68
s16 ActorCutscene_StartAndSetFlag(s16 index, Actor* actor); // func_800F1CE0
s16 ActorCutscene_Start(s16 index, Actor* actor); // func_800F1D84
s16 ActorCutscene_Stop(s16 index); // func_800F1FBC
s16 ActorCutscene_GetCurrentIndex(void); // func_800F207C
ActorCutscene* ActorCutscene_GetCutscene(s16 index); // func_800F208C
s16 ActorCutscene_GetAdditionalCutscene(s16 index); // func_800F20B8
s16 ActorCutscene_GetLength(s16 index); // func_800F20F8
void func_800F2138(void); // func_800F2138
void func_800F2178(void); // func_800F2178
s16 ActorCutscene_GetCurrentCamera(void); // func_800F21B8
void func_800F21CC(void); // func_800F21CC
UNK_TYPE4 func_800F22C4(short param_1, Actor* actor); // func_800F22C4
void ActorCutscene_SetReturnCamera(s16 index); // func_800F23C4
void func_800F23E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800F23E0
void func_800F2478(void); // func_800F2478
void func_800F2620(void); // func_800F2620
void func_800F2650(void); // func_800F2650
void func_800F26C0(void); // func_800F26C0
void func_800F26F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800F26F0
void func_800F2728(void); // func_800F2728
void func_800F29A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800F29A0
void func_800F2CD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800F2CD8
void FireObj_InitWithParams(GlobalContext* ctxt, FireObj* fire, FireObjInitParams* init); // func_800F2D30
void FireObj_SetState(FireObj* fire, f32 dynamicSizeStep, u8 newState); // func_800F2E48
void FireObj_SetPosition(FireObj* fire, Vector3f* pos); // func_800F2EAC
void FireObj_StepSize(FireObj* fire); // func_800F2ECC
void FireObj_UpdateStateTransitions(GlobalContext* ctxt, FireObj* fire); // func_800F2FFC
void FireObj_Draw(GlobalContext* ctxt, FireObj* fire); // func_800F31EC
void FireObj_InitLight(GlobalContext* ctxt, FireObjLight* light, u8* param_3, Vector3f* pos); // func_800F33F4
void FireObj_FiniLight(GlobalContext* ctxt, FireObjLight* light); // func_800F34C4
void FireObj_UpdateLight(GlobalContext* ctxt, FireObjLight* light, FireObj* fire); // func_800F34EC
void FireObj_Init(GlobalContext* ctxt, FireObj* fire, FireObjInitParams* init, Actor* actor); // func_800F36CC
void FireObj_Fini(GlobalContext* ctxt, FireObj* fire); // func_800F37B0
void FireObj_SetState2(FireObj* fire, f32 dynamicSizeStep, u8 newState); // func_800F37F0
void FireObj_Update(GlobalContext* ctxt, FireObj* fire); // func_800F3820
void func_800F3940(void); // func_800F3940
void func_800F39B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800F39B4
void func_800F3A64(void); // func_800F3A64
void func_800F3B2C(void); // func_800F3B2C
void func_800F3B68(void); // func_800F3B68
void func_800F3C44(void); // func_800F3C44
void func_800F3ED4(void); // func_800F3ED4
void func_800F40A0(GlobalContext* ctxt, int param_2); // func_800F40A0
void func_800F415C(void); // func_800F415C
void func_800F41E4(void); // func_800F41E4
void func_800F42A0(void); // func_800F42A0
void func_800F43BC(void); // func_800F43BC
void func_800F44F4(void); // func_800F44F4
void func_800F4540(void); // func_800F4540
s32 func_800F470C(UNK_TYPE4 param_1, UNK_TYPE4 param_2, int param_3, unsigned int param_4); // func_800F470C
void func_800F4A10(GlobalContext* ctxt); // func_800F4A10
void func_800F4C0C(GlobalContext* ctxt); // func_800F4C0C
void func_800F4E20(GlobalContext* ctxt); // func_800F4E20
void func_800F4F28(GlobalContext* ctxt); // func_800F4F28
void Kanfont_Nop800F4F40(GlobalContext* ctxt, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_800F4F40
void Kanfont_LoadAsciiChar(GlobalContext* ctxt, u8 character, s32 iParm3); // func_800F4F54
void Kanfont_LoadMessageBoxEnd(Font* font, u16 type); // func_800F4FC0
void Kanfont_LoadOrderedFont(Font* font); // func_800F5004
void func_800F5090(void); // func_800F5090
void func_800F50D4(void); // func_800F50D4
void Kankyo_Init(GlobalContext* ctxt, KankyoContext* kanCtxt); // func_800F510C
u32 func_800F5954(u8* param_1, u32 param_2, u32 param_3, u8 param_4, u8 param_5); // func_800F5954
void func_800F5A8C(void); // func_800F5A8C
void func_800F5B10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800F5B10
void func_800F5CD0(void); // func_800F5CD0
void func_800F6834(void); // func_800F6834
void func_800F694C(void); // func_800F694C
void func_800F6A04(void); // func_800F6A04
void func_800F6A40(void); // func_800F6A40
void func_800F6AB8(void); // func_800F6AB8
void func_800F6B44(GlobalContext* ctxt, KankyoContext* kanCtxt, int iParm3, int iParm4, short* param_5); // func_800F6B44
void func_800F6CEC(void); // func_800F6CEC
void func_800F6EA4(void); // func_800F6EA4
UNK_TYPE4 Kankyo_IsSceneUpsideDown(GlobalContext* ctxt); // func_800F6FCC
void func_800F6FF8(GlobalContext* ctxt, KankyoContext* kanCtxt, LightingContext* lCtxt); // func_800F6FF8
void func_800F8554(void); // func_800F8554
void func_800F88C4(void); // func_800F88C4
void func_800F8970(void); // func_800F8970
void func_800F8A9C(void); // func_800F8A9C
void func_800F8CD4(GlobalContext* ctxt, KankyoContext* kanCtxt, LightingContext* lCtxt, int param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800F8CD4
void func_800F8D84(void); // func_800F8D84
void func_800F9728(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800F9728
void func_800F9824(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE2 param_10, UNK_TYPE1 param_11); // func_800F9824
void func_800FA39C(void); // func_800FA39C
void func_800FA3C4(void); // func_800FA3C4
void func_800FA9FC(void); // func_800FA9FC
void func_800FAAB4(void); // func_800FAAB4
void func_800FAC20(void); // func_800FAC20
void func_800FAF74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_800FAF74
void func_800FB010(void); // func_800FB010
void func_800FB320(void); // func_800FB320
void func_800FB388(void); // func_800FB388
void func_800FB758(void); // func_800FB758
void func_800FB9B4(void); // func_800FB9B4
void func_800FBCBC(void); // func_800FBCBC
void func_800FBDEC(void); // func_800FBDEC
void func_800FBF3C(GlobalContext* ctxt); // func_800FBF3C
void func_800FC158(void); // func_800FC158
void func_800FC3DC(void); // func_800FC3DC
void func_800FC444(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6); // func_800FC444
void func_800FC64C(void); // func_800FC64C
void func_800FD2B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800FD2B4
void func_800FD538(RGB* param_1, RGB* param_2, f32 param_3, Vector3s* param_4); // func_800FD538
void func_800FD59C(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD59C
void func_800FD5E0(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD5E0
void func_800FD654(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD654
void func_800FD698(void); // func_800FD698
u32 get_days_elapsed(void); // func_800FD720
void reset_days_elapsed(void); // func_800FD730
u32 get_current_day(void); // func_800FD740
void func_800FD750(void); // func_800FD750
void func_800FD768(void); // func_800FD768
void func_800FD78C(void); // func_800FD78C
void func_800FD858(GlobalContext* ctxt); // func_800FD858
void func_800FD928(int param_1); // func_800FD928
void func_800FD980(void); // func_800FD980
void func_800FDAF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800FDAF8
void func_800FDC94(void); // func_800FDC94
void func_800FE390(void); // func_800FE390
void func_800FE3E0(void); // func_800FE3E0
void func_800FE484(void); // func_800FE484
void func_800FE498(void); // func_800FE498
void func_800FE4A8(void); // func_800FE4A8
u32 func_800FE4B8(GlobalContext* ctxt); // func_800FE4B8
void func_800FE590(void); // func_800FE590
void func_800FE5D0(void); // func_800FE5D0
UNK_TYPE4 func_800FE610(void); // func_800FE610
void func_800FE620(void); // func_800FE620
void func_800FE658(void); // func_800FE658
UNK_TYPE4 func_800FE6F8(UNK_TYPE4 param_1, s16 param_2, s16 param_3); // func_800FE6F8
void func_800FE778(void); // func_800FE778
void func_800FE788(void); // func_800FE788
void func_800FE798(void); // func_800FE798
void func_800FE7A8(void); // func_800FE7A8
void func_800FE9B4(void); // func_800FE9B4
void func_800FEA50(void); // func_800FEA50
void func_800FEAB0(void); // func_800FEAB0
void func_800FEAC0(void); // func_800FEAC0
void func_800FEAF4(void); // func_800FEAF4
void* Lib_bcopy(void* dst, void* src, size_t n); // func_800FEC90
s32* Lib_memset(s32* buffer, s32 value, u32 size); // func_800FECC0
f32 Lib_cos(s16 angle); // func_800FED44
f32 Lib_sin(s16 angle); // func_800FED84
s32 Lib_StepTowardsGet_i(s32 start, s32 value, s32 step); // func_800FEDC4
void Lib_StepTowards_i(s32* start, s32 value, s32 step); // func_800FEE08
s32 Lib_StepTowardsCheck_i(s32* start, s32 value, s32 step); // func_800FEE34
s32 Lib_StepTowardsCheckFramerateScaled_s(s16* start, s16 target, s16 step); // func_800FEE70
s32 Lib_StepTowardsCheck_s(s16* start, s16 target, s16 step); // func_800FEF2C
s32 Lib_StepTowardsCheck_c(s8* start, s8 target, s8 step); // func_800FEFB4
s32 Lib_StepTowardsCheck_f(f32* start, f32 target, f32 step); // func_800FF03C
void func_800FF0D0(void); // func_800FF0D0
void func_800FF138(void); // func_800FF138
void func_800FF1FC(void); // func_800FF1FC
void func_800FF2A8(void); // func_800FF2A8
void func_800FF2F8(void); // func_800FF2F8
void func_800FF3A0(void); // func_800FF3A0
s16 Lib_rand_s(s16 base, s16 range); // func_800FF450
s16 Lib_randStride_s(s16 base, s16 stride, s16 range); // func_800FF4A4
void Lib_CopyVec3f(Vector3f* dest, Vector3f* src); // func_800FF50C
void Lib_CopyVec3s(Vector3s* dest, Vector3s* src); // func_800FF52C
void Lib_ToVec3f(Vector3f* dest, Vector3s* src); // func_800FF54C
void Lib_ToVec3s(Vector3s* dest, Vector3f* src); // func_800FF584
void Lib_AddVec3f(Vector3f* l, Vector3f* r, Vector3f* dest); // func_800FF5BC
void Lib_SubVec3f(Vector3f* l, Vector3f* r, Vector3f* dest); // func_800FF5F4
void Lib_SubVec3sToVec3f(Vector3f* dest, Vector3s* l, Vector3s* r); // func_800FF62C
void Lib_ScaleInPlaceVec3f(Vector3f* vec, f32 scale); // func_800FF688
void Lib_ScaleVec3f(Vector3f* vec, f32 scale, Vector3f* dest); // func_800FF6C4
void Lib_LerpVec3f(Vector3f* a, Vector3f* b, f32 t, Vector3f* dest); // func_800FF6F8
void Lib_AddScaledVec3f(Vector3f* a, Vector3f* b, f32 scale, Vector3f* dest); // func_800FF750
void Lib_ModifyRandScaled(Vector3f* orig, f32 scale, Vector3f* dest); // func_800FF79C
void Lib_ScaledNormalizedDifferenceVec3f(Vector3f* a, Vector3f* b, f32 scale, Vector3f* dest); // func_800FF810
f32 Lib_DistanceVec3f(Vector3f* a, Vector3f* b); // func_800FF884
f32 Lib_DistanceAndDifferenceVec3f(Vector3f* a, Vector3f* b, Vector3f* difference); // func_800FF8D4
f32 Lib_DistanceXZVec3f(Vector3f* a, Vector3f* b); // func_800FF92C
f32 Lib_DistanceAndDifferenceXZVec3f(Vector3f* a, Vector3f* b, f32* xDiff, f32* zDiff); // func_800FF960
f32 Lib_PushAwayXZVec3f(Vector3f* start, Vector3f* pusher, f32 distanceToApproach); // func_800FF9A4
f32 Lib_DistanceYVec3f(Vector3f* a, Vector3f* b); // func_800FFA4C
s16 Lib_YawVec3f(Vector3f* from, Vector3f* to); // func_800FFA60
s16 Lib_PitchVec3f(Vector3f* from, Vector3f* to); // func_800FFA94
void Lib_ApplyActorInitVars(Actor* actor, ActorInitVar* init); // func_800FFADC
void Lib_ApplyActorInitVarByte1(u8* actor, ActorInitVar* init); // func_800FFB54
void Lib_ApplyActorInitVarByte2(u8* actor, ActorInitVar* init); // func_800FFB70
void Lib_ApplyActorInitVarShort1(u8* actor, ActorInitVar* init); // func_800FFB8C
void Lib_ApplyActorInitVarShort2(u8* actor, ActorInitVar* init); // func_800FFBA8
void Lib_ApplyActorInitVarWord1(u8* actor, ActorInitVar* init); // func_800FFBC4
void Lib_ApplyActorInitVarWord2(u8* actor, ActorInitVar* init); // func_800FFBE0
void Lib_ApplyActorInitVarFloat(u8* actor, ActorInitVar* init); // func_800FFBFC
void Lib_ApplyActorInitVarFloat1000th(u8* actor, ActorInitVar* init); // func_800FFC20
void Lib_ApplyActorInitVarVector3f(u8* actor, ActorInitVar* init); // func_800FFC50
void Lib_ApplyActorInitVarVector3f1000th(u8* actor, ActorInitVar* init); // func_800FFC7C
void Lib_ApplyActorInitVarVector3s(u8* actor, ActorInitVar* init); // func_800FFCB4
f32 func_800FFCD8(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4); // func_800FFCD8
void Lib_ScaleMax_f(f32* start, f32 target, f32 scale, f32 maxStep); // func_800FFDF8
void Lib_Scale_f(f32* start, f32 scale, f32 maxStep); // func_800FFE68
s32 Lib_ScaleMaxMin_s(s16* start, s16 target, s16 scale, s16 maxStep, s16 minStep); // func_800FFEBC
void Lib_ScaleMax_s(s16* start, s16 target, s16 scale, s16 maxStep); // func_800FFFD8
void Lib_CopyColor(ColorRGBA8* dst, ColorRGBA8* src); // func_8010007C
void func_801000A4(u16 param_1); // func_801000A4
void func_801000CC(u16 param_1); // func_801000CC
void func_801000F4(UNK_TYPE4 param_1, u16 param_2); // func_801000F4
void Lib_TranslateAndRotateYVec3f(Vector3f* translation, s16 rotation, Vector3f* src, Vector3f* dst); // func_8010011C
void Lib_LerpRGB(RGB* a, RGB* b, f32 t, RGB* dst); // func_801001B8
f32 Lib_PushAwayVec3f(Vector3f* start, Vector3f* pusher, f32 distanceToApproach); // func_80100448
void Lib_Nop801004FC(void); // func_801004FC
u32 Lib_PtrSegToVirt(void* ptr); // func_80100504
u32 Lib_PtrSegToVirtNull(void* ptr); // func_8010053C
u32 Lib_PtrSegToK0(void* ptr); // func_80100584
u32 Lib_PtrSegToK0Null(void* ptr); // func_801005A0
void LifeMeter_Init(GlobalContext* ctxt); // func_801005C0
void LifeMeter_UpdateColors(GlobalContext* ctxt); // func_8010069C
UNK_TYPE4 func_80100A80(GlobalContext* ctxt); // func_80100A80
UNK_TYPE4 func_80100AA0(GlobalContext* ctxt); // func_80100AA0
UNK_TYPE4 func_80100AF0(GlobalContext* ctxt); // func_80100AF0
void LifeMeter_Draw(GlobalContext* ctxt); // func_80100B8C
void LifeMeter_UpdateSizeAndBeep(GlobalContext* ctxt); // func_80101844
s32 LifeMeter_IsCritical(void); // func_80101930
void Lights_InitPositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius, u32 type); // func_801019A0
void Lights_InitType0PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius); // func_801019FC
void Lights_InitType2PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius); // func_80101A60
void Lights_SetPositionalLightColorAndRadius(LightInfoPositional* info, u8 red, u8 green, u8 blue, s16 radius); // func_80101AC8
void Lights_SetPositionalLightPosition(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ); // func_80101AFC
void Lights_InitDirectional(LightInfoDirectional* info, s8 dirX, s8 dirY, s8 dirZ, u8 red, u8 green, u8 blue); // func_80101B34
void Lights_MapperInit(LightMapper* mapper, u8 red, u8 green, u8 blue); // func_80101B8C
void Lights_UploadLights(LightMapper* mapper, GraphicsContext* gCtxt); // func_80101BC8
Light* Lights_MapperGetNextFreeSlot(LightMapper* mapper); // func_80101D0C
void Lights_MapPositionalWithReference(LightMapper* mapper, LightInfoPositionalParams* params, Vector3f* pos); // func_80101D3C
void Lights_MapPositional(LightMapper* mapper, LightInfoPositionalParams* params, GlobalContext* ctxt); // func_801020A0
void Lights_MapDirectional(LightMapper* mapper, LightInfoDirectionalParams* params, GlobalContext* ctxt); // func_80102284
void Lights_MapLights(LightMapper* mapper, z_Light* lights, Vector3f* refPos, GlobalContext* ctxt); // func_801022F0
z_Light* Lights_FindFreeSlot(void); // func_801023D8
void Lights_Free(z_Light* light); // func_80102464
void Lights_Init(GlobalContext* ctxt, LightingContext* lCtxt); // func_801024AC
void Lights_SetAmbientColor(LightingContext* lCtxt, u8 red, u8 green, u8 blue); // func_80102518
void func_80102544(LightingContext* lCtxt, u8 a1, u8 a2, u8 a3, s16 sp12, s16 sp16); // func_80102544
LightMapper* Lights_CreateMapper(LightingContext* lCtxt, GraphicsContext* gCtxt); // func_80102580
void Lights_ClearHead(GlobalContext* ctxt, LightingContext* lCtxt); // func_801025B8
void Lights_RemoveAll(GlobalContext* ctxt, LightingContext* lCtxt); // func_801025C8
z_Light* Lights_Insert(GlobalContext* ctxt, LightingContext* lCtxt, LightInfo* info); // func_80102624
void Lights_Remove(GlobalContext* ctxt, LightingContext* lCtxt, z_Light* light); // func_80102684
LightMapper* func_801026E8(GraphicsContext* gCtxt, u8 ambientRed, u8 ambientGreen, u8 ambientBlue, u8 numLights, u8 red, u8 green, u8 blue, s8 dirX, s8 dirY, s8 dirZ); // func_801026E8
LightMapper* Lights_MapperAllocateAndInit(GraphicsContext* gCtxt, u8 red, u8 green, u8 blue); // func_80102834
void func_80102880(GlobalContext* ctxt); // func_80102880
void func_80102A64(GlobalContext* ctxt); // func_80102A64
void* zelda_malloc(u32 size); // func_80102C60
void* zelda_mallocR(u32 size); // func_80102C88
void* zelda_realloc(void* oldPtr, u32 newSize); // func_80102CB0
void zelda_free(void* param_1); // func_80102CE0
void* zelda_calloc(u32 num, u32 size); // func_80102D08
void MainHeap_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated); // func_80102D60
s32 MainHeap_Check(void); // func_80102D98
void MainHeap_Init(u32 base, u32 size); // func_80102DBC
void MainHeap_Cleanup(void); // func_80102DEC
u32 MainHeap_IsInitialized(void); // func_80102E10
void func_80102E40(void); // func_80102E40
void func_80102E90(void); // func_80102E90
void func_80102EA4(void); // func_80102EA4
void func_80102EB4(u32 param_1); // func_80102EB4
void func_80102ED0(u32 param_1); // func_80102ED0
void func_80102EF0(void); // func_80102EF0
void func_80102F9C(void); // func_80102F9C
void func_80103090(void); // func_80103090
void func_801030B4(void); // func_801030B4
void func_801030F4(void); // func_801030F4
void func_801031D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801031D0
void func_801039EC(void); // func_801039EC
void func_80103A10(void); // func_80103A10
void func_80103A58(void); // func_80103A58
void func_8010439C(void); // func_8010439C
void func_801045AC(void); // func_801045AC
void func_80104AE8(void); // func_80104AE8
void func_80104C80(void); // func_80104C80
void func_80104CF4(void); // func_80104CF4
void func_80104F34(void); // func_80104F34
void func_80105294(void); // func_80105294
void func_80105318(void); // func_80105318
void func_80105328(void); // func_80105328
void func_8010534C(void); // func_8010534C
void func_8010549C(void); // func_8010549C
void func_8010565C(void); // func_8010565C
void func_80105818(GlobalContext* ctxt, unsigned int uParm2, TransitionActorInit* puParm3); // func_80105818
void func_80105A40(void); // func_80105A40
void func_80105B34(void); // func_80105B34
void func_80105C40(void); // func_80105C40
void func_80105FE0(void); // func_80105FE0
void func_80106408(void); // func_80106408
void func_80106450(void); // func_80106450
void func_801064CC(void); // func_801064CC
void func_80106530(void); // func_80106530
void func_8010657C(void); // func_8010657C
void func_80106644(void); // func_80106644
void func_8010683C(void); // func_8010683C
void func_801068B4(void); // func_801068B4
void func_801068D8(void); // func_801068D8
void func_801068FC(void); // func_801068FC
void func_80106BEC(void); // func_80106BEC
void func_80106D08(void); // func_80106D08
void func_80106D5C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80106D5C
void func_80107B78(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80107B78
void func_80108124(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80108124
void func_80108558(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80108558
void func_80108A10(void); // func_80108A10
void func_80108A64(void); // func_80108A64
void func_80108AF8(void); // func_80108AF8
void func_801090B0(void); // func_801090B0
void func_80109124(void); // func_80109124
void func_801091F0(void); // func_801091F0
void func_80109428(void); // func_80109428
void func_801094A0(void); // func_801094A0
void func_801094C8(void); // func_801094C8
void func_801094F8(void); // func_801094F8
void func_80109528(void); // func_80109528
void func_8010954C(void); // func_8010954C
void func_8010956C(void); // func_8010956C
void func_8010958C(void); // func_8010958C
void func_801095AC(void); // func_801095AC
void func_801095DC(void); // func_801095DC
void func_8010960C(void); // func_8010960C
void func_80109630(void); // func_80109630
void func_80109650(void); // func_80109650
void func_80109670(void); // func_80109670
void func_801096D4(void); // func_801096D4
void func_80109714(void); // func_80109714
void func_80109754(void); // func_80109754
void func_801097C8(void); // func_801097C8
void func_8010983C(void); // func_8010983C
void func_801098A0(void); // func_801098A0
void func_80109908(void); // func_80109908
UNK_TYPE4 func_80109964(s32 param_1); // func_80109964
void func_8010997C(void); // func_8010997C
void func_801099AC(void); // func_801099AC
void func_801099DC(void); // func_801099DC
void func_80109A00(void); // func_80109A00
void func_80109A20(void); // func_80109A20
void func_80109A40(void); // func_80109A40
void func_80109A98(void); // func_80109A98
void func_80109AD8(void); // func_80109AD8
void func_80109B38(void); // func_80109B38
void func_80109BA0(void); // func_80109BA0
void func_80109BF4(void); // func_80109BF4
void func_80109C38(void); // func_80109C38
void func_80109CBC(void); // func_80109CBC
void func_80109D40(void); // func_80109D40
void func_80109DD8(void); // func_80109DD8
void func_80109E70(void); // func_80109E70
void func_80109EF8(void); // func_80109EF8
void func_80109F78(void); // func_80109F78
int func_8010A000(GlobalContext* ctxt); // func_8010A000
void func_8010A074(void); // func_8010A074
void func_8010A0A4(void); // func_8010A0A4
void func_8010A0F0(void); // func_8010A0F0
void func_8010A164(void); // func_8010A164
void func_8010A194(void); // func_8010A194
void func_8010A208(void); // func_8010A208
void func_8010A238(void); // func_8010A238
void func_8010A2AC(void); // func_8010A2AC
void func_8010A2DC(GlobalContext* ctxt); // func_8010A2DC
void func_8010A33C(GlobalContext* ctxt, s16 param_2); // func_8010A33C
void func_8010A410(void); // func_8010A410
void func_8010A430(void); // func_8010A430
void func_8010A54C(void); // func_8010A54C
void func_8010A580(void); // func_8010A580
void func_8010A760(void); // func_8010A760
void func_8010A7CC(void); // func_8010A7CC
void func_8010A814(void); // func_8010A814
void func_8010A85C(void); // func_8010A85C
void func_8010A8A4(void); // func_8010A8A4
void func_8010A8EC(void); // func_8010A8EC
void func_8010A990(void); // func_8010A990
void func_8010AA54(void); // func_8010AA54
void func_8010AB30(void); // func_8010AB30
void func_8010AB94(void); // func_8010AB94
void func_8010AC00(void); // func_8010AC00
void func_8010AD24(void); // func_8010AD24
void func_8010ADD4(void); // func_8010ADD4
void func_8010AE48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8010AE48
UNK_TYPE4 func_8010AECC(UNK_TYPE4 param_1, s32 param_2, s32* param_3); // func_8010AECC
void func_8010AF20(void); // func_8010AF20
void func_8010AF6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8010AF6C
void func_8010AF94(void); // func_8010AF94
void func_8010AFE0(void); // func_8010AFE0
void func_8010B010(void); // func_8010B010
void func_8010B06C(void); // func_8010B06C
void func_8010B0B4(void); // func_8010B0B4
void func_8010B0DC(void); // func_8010B0DC
void func_8010B108(void); // func_8010B108
void func_8010B140(void); // func_8010B140
void func_8010B180(void); // func_8010B180
void func_8010B1BC(void); // func_8010B1BC
void func_8010B22C(void); // func_8010B22C
void func_8010B284(void); // func_8010B284
void func_8010B2C0(void); // func_8010B2C0
void func_8010B300(void); // func_8010B300
void func_8010B434(void); // func_8010B434
void func_8010B4A4(void); // func_8010B4A4
void func_8010B520(void); // func_8010B520
void func_8010B664(void); // func_8010B664
void func_8010B7A8(void); // func_8010B7A8
void func_8010B828(void); // func_8010B828
void func_8010B878(void); // func_8010B878
void func_8010B8E4(void); // func_8010B8E4
void func_8010BB0C(void); // func_8010BB0C
void func_8010BB6C(void); // func_8010BB6C
void func_8010BBCC(void); // func_8010BBCC
void func_8010BC28(void); // func_8010BC28
void func_8010BC7C(void); // func_8010BC7C
void func_8010BD48(void); // func_8010BD48
void func_8010BD90(void); // func_8010BD90
void func_8010BDDC(void); // func_8010BDDC
void func_8010BE78(void); // func_8010BE78
void func_8010BEBC(void); // func_8010BEBC
void func_8010BEF0(void); // func_8010BEF0
void func_8010BF24(void); // func_8010BF24
void func_8010BF58(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8010BF58
void Nmi_Init(void); // func_8010C0C0
void Nmi_SetPrenmiStart(void); // func_8010C164
s32 Nmi_GetPrenmiHasStarted(void); // func_8010C19C
void func_8010C1B0(void); // func_8010C1B0
f32 CamMath_Distance(Vector3f* a, Vector3f* b); // func_8010C230
f32 CamMath_DistanceAndDiff(Vector3f* a, Vector3f* b, Vector3f* diff); // func_8010C274
f32 CamMath_DistanceXZ(Vector3f* a, Vector3f* b); // func_8010C2D0
f32 func_8010C304(f32 a, f32 b); // func_8010C304
f32 func_8010C36C(f32 a, f32 b); // func_8010C36C
void func_8010C3D4(void); // func_8010C3D4
void func_8010C484(void); // func_8010C484
void func_8010C530(void); // func_8010C530
void func_8010C574(void); // func_8010C574
void func_8010C6C8(void); // func_8010C6C8
void func_8010C710(void); // func_8010C710
void func_8010C764(void); // func_8010C764
void func_8010C7B8(void); // func_8010C7B8
void func_8010C838(void); // func_8010C838
void func_8010C8C8(void); // func_8010C8C8
void func_8010C930(void); // func_8010C930
void func_8010C9C8(void); // func_8010C9C8
void func_8010CAA0(void); // func_8010CAA0
void func_8010CB80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); // func_8010CB80
void func_8010CD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); // func_8010CD98
void func_8010CFBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE2 param_13, UNK_TYPE2 param_14); // func_8010CFBC
void func_8010D2D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11); // func_8010D2D4
void func_8010D480(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE2 param_13, UNK_TYPE2 param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16); // func_8010D480
void func_8010D7D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); // func_8010D7D0
void func_8010D9F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE2 param_13, UNK_TYPE2 param_14); // func_8010D9F4
void func_8010DC58(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_8010DC58
void func_8010DE38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_8010DE38
void func_8010E028(void); // func_8010E028
void func_8010E968(void); // func_8010E968
void func_8010E9F0(void); // func_8010E9F0
void func_8010EA9C(void); // func_8010EA9C
void func_8010EB50(void); // func_8010EB50
void func_8010EBA0(void); // func_8010EBA0
void func_8010EC54(void); // func_8010EC54
void func_8010EE74(void); // func_8010EE74
void func_8010EF68(u16 param_1); // func_8010EF68
void func_8010EF9C(void); // func_8010EF9C
void func_8010F0D4(void); // func_8010F0D4
void func_8010F1A8(void); // func_8010F1A8
void func_80110038(void); // func_80110038
void func_80111CB4(void); // func_80111CB4
void func_801129E4(void); // func_801129E4
void func_80112AFC(void); // func_80112AFC
void func_80112B40(void); // func_80112B40
void func_80112BE4(void); // func_80112BE4
void func_80112C0C(void); // func_80112C0C
unsigned int func_80112E80(GlobalContext* ctxt, u8 param_2); // func_80112E80
void func_801143CC(void); // func_801143CC
void func_80114978(void); // func_80114978
void func_801149A0(void); // func_801149A0
void func_80114A9C(void); // func_80114A9C
void func_80114B84(void); // func_80114B84
void func_80114CA0(void); // func_80114CA0
void func_80114E90(void); // func_80114E90
void func_80114F2C(void); // func_80114F2C
void func_80114FD0(void); // func_80114FD0
void func_80115130(void); // func_80115130
void func_801152B8(void); // func_801152B8
void func_801153C8(void); // func_801153C8
void func_80115428(void); // func_80115428
void func_8011552C(void); // func_8011552C
void func_801155B4(void); // func_801155B4
void func_80115764(void); // func_80115764
void func_80115844(GlobalContext* ctxt, short param_2); // func_80115844
void func_80115908(void); // func_80115908
void func_801159c0(short param_1); // func_801159C0
void func_801159EC(void); // func_801159EC
void func_80115A14(void); // func_80115A14
void Parameter_AddMagic(void); // func_80115D14
void func_80115D5C(void); // func_80115D5C
void func_80115DB4(void); // func_80115DB4
void func_80116088(void); // func_80116088
void func_80116114(void); // func_80116114
void func_80116348(void); // func_80116348
void func_80116918(void); // func_80116918
void func_80116FD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80116FD8
void func_801170B8(void); // func_801170B8
void func_80117100(void); // func_80117100
void func_80117A20(void); // func_80117A20
void func_80117BD0(void); // func_80117BD0
void func_80118084(void); // func_80118084
void func_80118890(void); // func_80118890
void func_80118BA4(void); // func_80118BA4
void func_80119030(void); // func_80119030
void func_80119610(void); // func_80119610
void func_8011B4E0(void); // func_8011B4E0
void func_8011B5C0(void); // func_8011B5C0
void func_8011B9E0(void); // func_8011B9E0
void func_8011BF70(void); // func_8011BF70
void func_8011C4C4(void); // func_8011C4C4
void func_8011C808(GlobalContext* ctxt); // func_8011C808
void func_8011C898(void); // func_8011C898
void func_8011CA64(void); // func_8011CA64
void func_8011E3B4(void); // func_8011E3B4
void func_8011E730(void); // func_8011E730
void func_8011F0E0(UNK_TYPE4 ctxt); // func_8011F0E0
void func_80120F90(void); // func_80120F90
void func_80121000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); // func_80121000
void func_80121064(void); // func_80121064
void func_801210E0(void); // func_801210E0
void func_80121F94(void); // func_80121F94
void func_80121FC4(GlobalContext* ctxt); // func_80121FC4
s32 func_801224E0(s32 param_1, s16 param_2, s16 param_3); // func_801224E0
void func_80122524(void); // func_80122524
void func_801225CC(void); // func_801225CC
void func_80122660(void); // func_80122660
UNK_TYPE4 func_80122670(int* param_1, Input* input); // func_80122670
void func_801226E0(void); // func_801226E0
void func_80122744(void); // func_80122744
void func_80122760(void); // func_80122760
void func_80122868(void); // func_80122868
void func_801229A0(void); // func_801229A0
void func_801229EC(void); // func_801229EC
void func_801229FC(void); // func_801229FC
void func_80122BA4(void); // func_80122BA4
void func_80122C20(void); // func_80122C20
void func_80122D44(void); // func_80122D44
void func_80122ED8(void); // func_80122ED8
void func_80122EEC(void); // func_80122EEC
void func_80122F28(void); // func_80122F28
void func_80122F9C(void); // func_80122F9C
void func_80122FCC(void); // func_80122FCC
void func_8012300C(void); // func_8012300C
void func_8012301C(int iParm1, GlobalContext* ctxt); // func_8012301C
void func_80123140(GlobalContext* ctxt, ActorPlayer* param_2); // func_80123140
unsigned int func_80123358(GlobalContext* ctxt, ActorPlayer* player); // func_80123358
unsigned int func_801233E4(GlobalContext* ctxt); // func_801233E4
void func_80123420(void); // func_80123420
void func_80123434(void); // func_80123434
void func_80123448(void); // func_80123448
void func_801234B0(void); // func_801234B0
void func_801234D4(void); // func_801234D4
s32 func_80123590(GlobalContext* ctxt, Actor* actor); // func_80123590
void func_8012364C(void); // func_8012364C
void func_80123810(void); // func_80123810
void func_80123960(void); // func_80123960
void func_801239AC(void); // func_801239AC
void func_80123AA4(void); // func_80123AA4
void func_80123BD4(void); // func_80123BD4
void func_80123C58(void); // func_80123C58
void func_80123C90(void); // func_80123C90
void func_80123D50(void); // func_80123D50
void func_80123DA4(ActorPlayer* player); // func_80123DA4
void func_80123DC0(void); // func_80123DC0
void func_80123E90(void); // func_80123E90
void func_80123F2C(void); // func_80123F2C
void func_80123F48(void); // func_80123F48
void func_80124020(void); // func_80124020
u32 func_8012403C(GlobalContext* ctxt); // func_8012403C
void func_8012404C(GlobalContext* ctxt); // func_8012404C
void func_8012405C(void); // func_8012405C
void func_80124088(void); // func_80124088
void func_801240C8(void); // func_801240C8
void func_801240DC(void); // func_801240DC
void func_80124110(void); // func_80124110
void func_80124148(void); // func_80124148
void func_80124168(void); // func_80124168
void func_80124190(void); // func_80124190
void func_801241B4(void); // func_801241B4
void func_801241E0(void); // func_801241E0
void func_8012420C(void); // func_8012420C
void func_8012422C(void); // func_8012422C
void func_80124258(void); // func_80124258
void func_80124278(void); // func_80124278
void func_801242B4(void); // func_801242B4
void func_801242DC(void); // func_801242DC
void func_80124420(void); // func_80124420
void func_80124618(void); // func_80124618
void func_801246F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE1 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_801246F4
void func_80124870(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80124870
void func_80124CC4(void); // func_80124CC4
void func_80124F18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80124F18
void func_80124FF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE2 param_10); // func_80124FF0
void func_801251C4(void); // func_801251C4
void func_80125318(void); // func_80125318
void func_80125340(void); // func_80125340
void func_8012536C(void); // func_8012536C
void func_801253A4(void); // func_801253A4
void func_80125500(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80125500
void func_80125580(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80125580
void func_80125CE0(void); // func_80125CE0
void func_80125D4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80125D4C
void func_801262C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801262C8
void func_801263FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801263FC
void func_80126440(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80126440
void func_801265C8(void); // func_801265C8
void func_8012669C(void); // func_8012669C
void func_80126808(void); // func_80126808
void func_8012697C(void); // func_8012697C
void func_80126AB4(void); // func_80126AB4
void func_80126B8C(void); // func_80126B8C
void func_80126BD0(void); // func_80126BD0
void func_801271B0(void); // func_801271B0
void func_80127438(void); // func_80127438
void func_80127488(void); // func_80127488
void func_8012754C(void); // func_8012754C
void func_80127594(void); // func_80127594
void func_801278F8(void); // func_801278F8
void func_80127A60(void); // func_80127A60
void func_80127B64(void); // func_80127B64
void func_80127BE8(void); // func_80127BE8
void func_80127DA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80127DA4
void func_80128388(void); // func_80128388
void func_801284A0(void); // func_801284A0
void func_80128640(void); // func_80128640
void func_80128B74(void); // func_80128B74
void func_80128BD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80128BD0
void Prenmi_Stop(PrenmiContext* ctxt); // func_80129EF0
void Prenmi_Update(PrenmiContext* ctxt); // func_80129F04
void Prenmi_Draw(PrenmiContext* ctxt); // func_80129F4C
void Prenmi_Main(PrenmiContext* ctxt); // func_80129FF8
void Prenmi_Fini(PrenmiContext* ctxt); // func_8012A02C
void Prenmi_Init(PrenmiContext* ctxt); // func_8012A038
void func_8012A080(void); // func_8012A080
void func_8012A0AC(void); // func_8012A0AC
void func_8012A2B8(void); // func_8012A2B8
void func_8012A340(void); // func_8012A340
void func_8012A3B4(void); // func_8012A3B4
void func_8012A438(void); // func_8012A438
void func_8012A4D0(void); // func_8012A4D0
void func_8012A540(void); // func_8012A540
void func_8012A5D8(void); // func_8012A5D8
void func_8012A638(void); // func_8012A638
void func_8012A6F0(void); // func_8012A6F0
void func_8012A718(void); // func_8012A718
void func_8012A774(void); // func_8012A774
void func_8012A8A8(void); // func_8012A8A8
void func_8012A8F0(void); // func_8012A8F0
void func_8012A940(void); // func_8012A940
void func_8012A978(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_8012A978
void func_8012A9E0(void); // func_8012A9E0
void func_8012AA48(void); // func_8012AA48
void func_8012AA9C(void); // func_8012AA9C
void func_8012AAC0(void); // func_8012AAC0
void func_8012AB08(void); // func_8012AB08
void func_8012AE68(GlobalContext* ctxt); // func_8012AE68
void func_8012AEAC(void); // func_8012AEAC
int func_8012aed4(void); // func_8012AED4
void func_8012AEE4(void); // func_8012AEE4
void func_8012AEF4(void); // func_8012AEF4
void func_8012AF18(void); // func_8012AF18
void func_8012AF38(void); // func_8012AF38
void func_8012AF9C(void); // func_8012AF9C
void func_8012BBE8(void); // func_8012BBE8
void func_8012BC50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8012BC50
void func_8012BD8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8012BD8C
void func_8012BF08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8012BF08
void func_8012BF3C(void); // func_8012BF3C
void func_8012BF78(void); // func_8012BF78
void func_8012BF98(void); // func_8012BF98
void func_8012BFC4(void); // func_8012BFC4
void func_8012C014(void); // func_8012C014
void func_8012C080(void); // func_8012C080
void func_8012C148(void); // func_8012C148
void func_8012C198(void); // func_8012C198
void func_8012C1C0(void); // func_8012C1C0
void func_8012C1EC(void); // func_8012C1EC
void func_8012C214(void); // func_8012C214
void func_8012C240(void); // func_8012C240
void func_8012C268(GlobalContext* ctxt); // func_8012C268
void func_8012C28C(GraphicsContext* gCtxt); // func_8012C28C
void func_8012C2B4(void); // func_8012C2B4
void func_8012C2DC(GraphicsContext* gCtxt); // func_8012C2DC
void func_8012C304(void); // func_8012C304
void func_8012C3A4(void); // func_8012C3A4
void func_8012C3CC(void); // func_8012C3CC
void func_8012C3F4(void); // func_8012C3F4
void func_8012C448(GraphicsContext* gCtxt); // func_8012C448
void func_8012C470(void); // func_8012C470
void func_8012C4C0(void); // func_8012C4C0
void func_8012C560(void); // func_8012C560
void func_8012C588(void); // func_8012C588
void func_8012C5B0(void); // func_8012C5B0
void func_8012C600(void); // func_8012C600
void func_8012C628(GraphicsContext* gCtxt); // func_8012C628
void func_8012C654(void); // func_8012C654
void func_8012C680(void); // func_8012C680
void func_8012C6AC(void); // func_8012C6AC
void func_8012C6FC(void); // func_8012C6FC
void func_8012C724(void); // func_8012C724
Gfx* func_8012C7FC(Gfx* puParm1); // func_8012C7FC
void func_8012C868(void); // func_8012C868
void func_8012C8AC(GraphicsContext* gCtxt); // func_8012C8AC
void func_8012C8D4(void); // func_8012C8D4
void func_8012C94C(void); // func_8012C94C
void func_8012C974(void); // func_8012C974
void func_8012C9BC(void); // func_8012C9BC
void func_8012CA0C(void); // func_8012CA0C
void func_8012CA60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8012CA60
void func_8012CB04(void); // func_8012CB04
void func_8012CB28(void); // func_8012CB28
Gfx* Rcp_GenerateSetTileSizeDl(GraphicsContext* gCtxt, u32 upperS, u32 upperT, u32 lengthS, u32 lengthT); // func_8012CB4C
Gfx* Rcp_GenerateSetTileSize2Dl(GraphicsContext* gCtxt, u32 tile1, u32 upperS1, u32 upperT1, u32 lengthS1, u32 lengthT1, u32 tile2, u32 upperS2, u32 upperT2, u32 lengthS2, u32 lengthT2); // func_8012CBD0
void func_8012CCF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE4 param_15); // func_8012CCF0
void func_8012CE50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8012CE50
void func_8012CEA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8012CEA8
void func_8012CF0C(GraphicsContext* gCtxt, int iParm2, int iParm3, unsigned int uParm4, u8 param_5, u8 param_6); // func_8012CF0C
void func_8012D374(void); // func_8012D374
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3); // func_8012D40C
void Room_nop8012D510(GlobalContext* ctxt, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4); // func_8012D510
void Room_DrawType3Mesh(GlobalContext* ctxt, Room* room, u32 flags); // func_8012D528
void Room_DrawType0Mesh(GlobalContext* ctxt, Room* room, u32 flags); // func_8012D53C
void Room_DrawType2Mesh(GlobalContext* ctxt, Room* room, u32 flags); // func_8012D750
void func_8012DEE8(GlobalContext* ctxt, Room* room, u32 flags); // func_8012DEE8
u32 func_8012E254(int param_1, GlobalContext* ctxt); // func_8012E254
void func_8012E32C(GlobalContext* ctxt, Room* room, u32 flags); // func_8012E32C
void Room_DrawType1Mesh(GlobalContext* ctxt, Room* room, u32 flags); // func_8012E6A8
void Room_Init(GlobalContext* ctxt, RoomContext* roomCtxt); // func_8012E710
u32 Room_AllocateAndLoad(GlobalContext* ctxt, RoomContext* roomCtxt); // func_8012E750
s32 Room_StartRoomTransition(GlobalContext* ctxt, RoomContext* roomCtxt, s32 index); // func_8012E96C
s32 Room_HandleLoadCallbacks(GlobalContext* ctxt, RoomContext* roomCtxt); // func_8012EAA8
void Room_Draw(GlobalContext* ctxt, Room* room, u32 flags); // func_8012EBA8
void func_8012EBF8(GlobalContext* ctxt, RoomContext* roomCtxt); // func_8012EBF8
unsigned int func_8012EC80(GlobalContext* ctxt); // func_8012EC80
void func_8012ED34(s16 param_1); // func_8012ED34
void func_8012ED78(void); // func_8012ED78
void func_8012EDE8(void); // func_8012EDE8
void func_8012EE34(void); // func_8012EE34
void func_8012EF0C(void); // func_8012EF0C
void func_8012F0EC(void); // func_8012F0EC
void func_8012F1BC(void); // func_8012F1BC
void func_8012F22C(void); // func_8012F22C
void func_8012F278(void); // func_8012F278
s32 Scene_LoadObject(SceneContext* sceneCtxt, short id); // func_8012F2E0
void Scene_Init(GlobalContext* ctxt, SceneContext* sceneCtxt); // func_8012F3D0
void Scene_ReloadUnloadedObjects(SceneContext* sceneCtxt); // func_8012F4FC
s32 Scene_FindSceneObjectIndex(SceneContext* sceneCtxt, short id); // func_8012F608
s32 Scene_IsObjectLoaded(SceneContext* iParm1, s32 index); // func_8012F668
void Scene_DmaAllObjects(SceneContext* sceneCtxt); // func_8012F698
u32 func_8012F73C(SceneContext* sceneCtxt, s32 iParm2, s16 id); // func_8012F73C
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012F79C
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012F90C
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012F954
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012F984
void Scene_HeaderCommand04(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FA24
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FA68
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FA98
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FB60
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FBE8
void Scene_HeaderCommand0B(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FC18
void Scene_HeaderCommand0C(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FDA4
void Scene_HeaderCommand0D(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FE2C
void Scene_HeaderCommand0E(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FE5C
void func_8012FEBC(void); // func_8012FEBC
void Scene_HeaderCommand0F(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FECC
void func_8012FF10(GlobalContext* ctxt, int iParm2); // func_8012FF10
void Scene_HeaderCommand11(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FF8C
void Scene_HeaderCommand12(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8012FFF0
void Scene_HeaderCommand10(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130018
void Scene_HeaderCommand05(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8013033C
void Scene_HeaderCommand13(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_801303A0
void Scene_HeaderCommand09(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_801303D0
void Scene_HeaderCommand15(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_801303E0
void Scene_HeaderCommand16(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_8013043C
void Scene_HeaderCommand18(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130454
void Scene_HeaderCommand17(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_801304CC
void Scene_HeaderCommand1B(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130500
void Scene_HeaderCommand1C(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130540
void Scene_HeaderCommand1D(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130578
void Scene_HeaderCommand1E(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130588
void Scene_HeaderCommand19(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_801305B0
void Scene_HeaderCommand1A(GlobalContext* ctxt, SceneHeaderEntry* entry); // func_80130674
void func_801306A4(GlobalContext* ctxt); // func_801306A4
s32 Scene_ProcessHeader(GlobalContext* ctxt, SceneHeaderEntry* header); // func_801306E8
u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset); // func_80130768
void func_80130784(void); // func_80130784
void SceneProc_DrawCurrentSceneAnimatedTextures(GlobalContext* ctxt); // func_801307C0
void SceneProc_DrawSceneConfig0(GlobalContext* ctxt); // func_801307F4
Gfx* SceneProc_SetTile1Layer(GlobalContext* ctxt, ScrollingTextureParams* params); // func_80130834
void SceneProc_DrawType0Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params); // func_801308A0
Gfx* SceneProc_SetTile2Layers(GlobalContext* ctxt, ScrollingTextureParams* params); // func_80130940
void SceneProc_DrawType1Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params); // func_801309F4
void SceneProc_DrawFlashingTexture(GlobalContext* ctxt, u32 segment, FlashingTexturePrimColor* primColor, RGBA8* envColor); // func_80130A94
void SceneProc_DrawType2Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params); // func_80130C5C
s32 SceneProc_Lerp(s32 a, s32 b, f32 t); // func_80130D0C
void SceneProc_DrawType3Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params); // func_80130D3C
f32 SceneProc_Interpolate(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame); // func_80130F58
u8 SceneProc_InterpolateClamped(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame); // func_8013115C
void SceneProc_DrawType4Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params); // func_801311B4
void SceneProc_DrawType5Texture(GlobalContext* ctxt, u32 segment, CyclingTextureParams* params); // func_80131580
void SceneProc_DrawAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, f32 flashingAlpha, u32 step, u32 flags); // func_80131690
void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures); // func_80131758
void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures); // func_8013178C
void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures); // func_801317C0
void SceneProc_DrawAllSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha); // func_801317F4
void SceneProc_DrawOpaqueSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha); // func_8013182C
void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha); // func_80131864
void SceneProc_DrawAllAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step); // func_8013189C
void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step); // func_801318C8
void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step); // func_801318F4
void SceneProc_DrawAllAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step); // func_80131920
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step); // func_8013194C
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step); // func_80131978
void SceneProc_DrawSceneConfig1(GlobalContext* ctxt); // func_801319A4
void SceneProc_DrawSceneConfig3(GlobalContext* ctxt); // func_801319CC
void SceneProc_DrawSceneConfig4(GlobalContext* ctxt); // func_80131CDC
void SceneProc_DrawSceneConfig2(GlobalContext* ctxt); // func_80131DE4
void func_80131DF0(GlobalContext* ctxt, u32 param_2, u32 flags); // func_80131DF0
void func_80131E58(GlobalContext* ctxt, u32 param_2, u32 flags); // func_80131E58
void SceneProc_DrawSceneConfig5(GlobalContext* ctxt); // func_80131EC0
void SceneProc_DrawSceneConfig7(GlobalContext* ctxt); // func_80131F90
void SceneProc_DrawSceneConfig6(GlobalContext* ctxt); // func_80131FC0
EntranceRecord* SceneTable_LookupEntrance(u32 entrance); // func_801322C0
s32 SceneTable_LookupEntranceScene(u32 entrance); // func_8013230C
s32 SceneTable_LookupEntranceAbsoluteScene(u32 entrance); // func_80132338
void func_80132374(void); // func_80132374
void func_801323A0(void); // func_801323A0
void func_801323D0(void); // func_801323D0
void func_80132428(void); // func_80132428
void func_80132494(void); // func_80132494
void func_801326B8(void); // func_801326B8
void func_801328F0(void); // func_801328F0
void func_80132920(void); // func_80132920
void func_80132938(void); // func_80132938
void func_80132954(void); // func_80132954
void func_8013296C(void); // func_8013296C
void func_80132A18(void); // func_80132A18
void func_80132A3C(void); // func_80132A3C
void func_80132A80(void); // func_80132A80
void func_80132AD8(void); // func_80132AD8
void func_80132B24(void); // func_80132B24
void func_80132B84(void); // func_80132B84
void func_80132D70(void); // func_80132D70
void func_80132E9C(void); // func_80132E9C
void func_80132FDC(void); // func_80132FDC
void func_80133000(void); // func_80133000
void func_80133038(void); // func_80133038
void func_801330E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_801330E0
void func_801332F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801332F0
void func_801334A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_801334A0
void func_80133710(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80133710
void func_80133948(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80133948
void func_80133B3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80133B3C
void func_80133CDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80133CDC
void func_80133F28(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80133F28
void func_80134148(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_80134148
void func_801343C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_801343C0
void func_80134600(void); // func_80134600
void func_80134724(void); // func_80134724
void func_80134748(void); // func_80134748
void func_80134774(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80134774
void func_80134990(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80134990
void func_80134B54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_80134B54
void func_80134DBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80134DBC
void func_80134FFC(void); // func_80134FFC
void func_801353D4(void); // func_801353D4
void func_801353F8(void); // func_801353F8
void func_8013541C(void); // func_8013541C
void func_80135448(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80135448
void func_801358C8(UNK_PTR param_1); // func_801358C8
void func_801358D4(void); // func_801358D4
void func_801358F4(void); // func_801358F4
void func_8013591C(void); // func_8013591C
void func_80135954(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80135954
void func_80135A28(void); // func_80135A28
void func_80135A90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80135A90
void func_80135B00(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80135B00
void func_80135B70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80135B70
void func_80135BE0(void); // func_80135BE0
void func_80135C3C(void); // func_80135C3C
void func_80135C6C(void); // func_80135C6C
void func_80135CDC(void); // func_80135CDC
void func_80135D38(void); // func_80135D38
void func_80135DB8(void); // func_80135DB8
void func_80135E3C(void); // func_80135E3C
void func_80135EE8(void); // func_80135EE8
void func_80135F88(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80135F88
void func_801360A8(void); // func_801360A8
void func_801360E0(void); // func_801360E0
void func_80136104(void); // func_80136104
void func_801361BC(void); // func_801361BC
void func_80136288(void); // func_80136288
void func_8013631C(void); // func_8013631C
void func_801363F0(void); // func_801363F0
void func_80136414(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE1 param_7, UNK_TYPE4 param_8); // func_80136414
void func_8013658C(void); // func_8013658C
void func_801365EC(void); // func_801365EC
void func_80136650(void); // func_80136650
void func_801366AC(void); // func_801366AC
void func_8013670C(void); // func_8013670C
void func_8013673C(void); // func_8013673C
void func_8013676C(void); // func_8013676C
void func_801367B0(void); // func_801367B0
void func_801367F4(void); // func_801367F4
void func_8013682C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8013682C
void func_801368CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_801368CC
void func_8013696C(void); // func_8013696C
void func_80136990(void); // func_80136990
void func_80136A48(void); // func_80136A48
void func_80136A7C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80136A7C
void func_80136B30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80136B30
void func_80136BEC(void); // func_80136BEC
void func_80136C84(void); // func_80136C84
void func_80136CD0(void); // func_80136CD0
void func_80136CF4(void); // func_80136CF4
void func_80136D98(void); // func_80136D98
void func_80136F04(void); // func_80136F04
void func_8013702C(void); // func_8013702C
void func_801370B0(void); // func_801370B0
void func_8013713C(void); // func_8013713C
void func_8013722C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8); // func_8013722C
void func_801373E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7); // func_801373E8
void func_80137430(void); // func_80137430
void func_80137488(void); // func_80137488
void func_801374E4(void); // func_801374E4
void func_80137540(void); // func_80137540
void func_80137594(void); // func_80137594
void func_801375CC(void); // func_801375CC
void func_80137624(void); // func_80137624
void func_80137650(void); // func_80137650
void func_80137674(void); // func_80137674
void func_801376DC(void); // func_801376DC
void func_80137748(void); // func_80137748
void func_801378B8(void); // func_801378B8
void func_801378E0(void); // func_801378E0
void func_8013792C(void); // func_8013792C
void func_80137970(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80137970
void func_80137B34(void); // func_80137B34
void func_80137EBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80137EBC
void func_80137F58(void); // func_80137F58
void func_80138050(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80138050
void func_80138228(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80138228
void func_80138258(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80138258
void func_8013828C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013828C
void func_801382C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_801382C4
void func_80138300(void); // func_80138300
void func_8013835C(void); // func_8013835C
void func_80138410(void); // func_80138410
void func_80138424(void); // func_80138424
void func_8013859C(void); // func_8013859C
void func_80138700(void); // func_80138700
void func_801387D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_801387D4
void func_801388E4(void); // func_801388E4
void Matrix_MultiplyByVectorXYZW(z_Matrix* matrix, Vector3f* vector, Vector3f* resultXYZ, f32* resultW); // func_80138BA0
void Matrix_MultiplyByVectorXYZ(z_Matrix* matrix, Vector3f* vector, Vector3f* result); // func_80138C88
void Matrix_Multiply(z_Matrix* l, z_Matrix* r, z_Matrix* dst); // func_80138D38
void Matrix_GetIdentity(z_Matrix** puParm1); // func_80139094
void Matrix_MakeIdentity(z_Matrix* matrix); // func_801390A8
void Matrix_Copy(z_Matrix* src, z_Matrix* dst); // func_80139100
s32 Matrix_Invert(z_Matrix* matrix, z_Matrix* invert); // func_80139188
void Matrix_MakeScale(z_Matrix* matrix, f32 x, f32 y, f32 z); // func_80139428
void Matrix_MakeRotationZYX(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation); // func_8013948C
void Matrix_MakeRotationYXZ(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation); // func_8013961C
void Matrix_MakeTranslation(z_Matrix* matrix, f32 x, f32 y, f32 z); // func_801397AC
void Matrix_MakeTranslationRotationZYXScale(z_Matrix* matrix, f32 xScale, f32 yScale, f32 zScale, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation); // func_80139810
void Matrix_MakeTranslationRotationYXZScale(z_Matrix* matrix, f32 xScale, f32 yScale, f32 zScale, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation); // func_80139894
void Matrix_MakeTranslationRotationZYX(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation); // func_80139918
void Matrix_ToVec3s(Vector3f* vec3f, Vector3s* vec3s); // func_80139978
void Matrix_ToVec3f(Vector3s* vec3s, Vector3f* vec3f); // func_801399BC
void Matrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst); // func_80139A00
RSPMatrix* Matrix_AppendToPloyOpaDisp(GraphicsContext* gCtxt, z_Matrix* matrix); // func_80139C18
void Matrix_MakeRotationAroundUnitVector(z_Matrix* matrix, s16 rotation, f32 x, f32 y, f32 z); // func_80139C60
void Matrix_MakeXRotation(z_Matrix* matrix, s16 rotation); // func_80139DD0
void Matrix_XRotation(z_Matrix* matrix, s16 rotation); // func_80139E98
void Matrix_MakeYRotation(z_Matrix* matrix, s16 rotation); // func_80139FA0
void Matrix_YRotation(z_Matrix* matrix, s16 rotation); // func_8013A068
void Matrix_MakeZRotation(z_Matrix* matrix, s16 rotation); // func_8013A174
void func_8013A240(void); // func_8013A240
void func_8013A41C(void); // func_8013A41C
void func_8013A4C4(void); // func_8013A4C4
void func_8013A504(void); // func_8013A504
void func_8013A530(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); // func_8013A530
void func_8013A7C0(void); // func_8013A7C0
void func_8013A860(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_8013A860
void func_8013AB00(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_8013AB00
void func_8013AD6C(void); // func_8013AD6C
void func_8013AD9C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8013AD9C
void func_8013AED4(u16* param_1, u16 param_2, u16 param_3); // func_8013AED4
void func_8013AF00(void); // func_8013AF00
void func_8013B010(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013B010
void func_8013B0C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8013B0C8
void func_8013B350(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013B350
void func_8013B6B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_8013B6B0
void func_8013B878(void); // func_8013B878
void func_8013BB34(void); // func_8013BB34
void func_8013BB7C(void); // func_8013BB7C
void func_8013BC6C(void); // func_8013BC6C
void func_8013BD40(void); // func_8013BD40
void func_8013BEDC(void); // func_8013BEDC
void func_8013C068(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8013C068
void func_8013C624(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8013C624
void func_8013C8B8(void); // func_8013C8B8
void func_8013C964(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8013C964
void func_8013CC2C(void); // func_8013CC2C
void func_8013CD64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013CD64
void func_8013CF04(void); // func_8013CF04
void func_8013D0E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8013D0E0
void func_8013D2E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013D2E0
void func_8013D5E8(void); // func_8013D5E8
void func_8013D648(void); // func_8013D648
void func_8013D68C(void); // func_8013D68C
void func_8013D720(void); // func_8013D720
void func_8013D768(void); // func_8013D768
void func_8013D83C(void); // func_8013D83C
void func_8013D8DC(void); // func_8013D8DC
void func_8013D924(void); // func_8013D924
void func_8013D960(void); // func_8013D960
void func_8013D9C8(void); // func_8013D9C8
void func_8013DB90(void); // func_8013DB90
void func_8013DC40(void); // func_8013DC40
void func_8013DCE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE1 param_10); // func_8013DCE0
void func_8013DE04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8013DE04
void func_8013DF3C(void); // func_8013DF3C
void func_8013E054(void); // func_8013E054
void func_8013E07C(void); // func_8013E07C
void func_8013E0A4(void); // func_8013E0A4
void func_8013E1C8(s32 iParm1, s32 iParm2, s32 iParm3, s32* piParm4); // func_8013E1C8
void func_8013E2D4(void); // func_8013E2D4
void func_8013E3B8(void); // func_8013E3B8
void func_8013E4B0(void); // func_8013E4B0
void func_8013E5CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8013E5CC
void func_8013E640(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013E640
void func_8013E748(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8013E748
void func_8013E7C0(void); // func_8013E7C0
void func_8013E8F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_8013E8F8
void func_8013E950(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE2 param_13); // func_8013E950
void func_8013EC10(void); // func_8013EC10
void func_8013EC44(void); // func_8013EC44
void func_8013ECE0(void); // func_8013ECE0
void func_8013ED9C(void); // func_8013ED9C
void func_8013EDD0(void); // func_8013EDD0
void func_8013EE04(void); // func_8013EE04
void func_8013EE24(void); // func_8013EE24
void func_8013EE38(void); // func_8013EE38
void func_8013EE48(void); // func_8013EE48
void View_MapViewportToGfxVp(Vp* gfxVp, Viewport* viewport); // func_8013EE60
void View_InitView(View* view, GraphicsContext* gCtxt); // func_8013EEF4
void View_SetViewOrientation(View* view, Vector3f* eye, Vector3f* focalPoint, Vector3f* upDir); // func_8013EF9C
void func_8013F050(View* view, Vector3f* param_2, Vector3f* param_3, Vector3f* param_4); // func_8013F050
void func_8013F0A0(View* view, UNK_TYPE4 param_2); // func_8013F0A0
void func_8013F0C0(View* view, UNK_PTR param_2); // func_8013F0C0
void func_8013F0D0(View* view, f32 uParm2, f32 uParm3, f32 uParm4); // func_8013F0D0
void func_8013F100(View* view, UNK_PTR param_2, UNK_PTR param_3, UNK_PTR param_4); // func_8013F100
void func_8013F120(View* view, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4); // func_8013F120
void func_8013F15C(View* view, UNK_PTR param_2, UNK_PTR param_3, UNK_PTR param_4); // func_8013F15C
void func_8013F17C(View* view, Viewport* viewport); // func_8013F17C
void View_GetViewport(View* view, Viewport* viewport); // func_8013F1B0
void View_WriteScissor(Gfx** gfx, s32 leftX, s32 upperY, s32 rightX, s32 lowerY); // func_8013F1D8
void View_WriteBlackFillColorAndScissor(View* view, Gfx** gfx); // func_8013F28C
void View_SetScissorForLetterbox(View* view); // func_8013F2F8
s32 View_SetQuakeRotation(View* view, f32 x, f32 y, f32 z); // func_8013F3F8
s32 View_SetQuakeScale(View* view, f32 x, f32 y, f32 z); // func_8013F420
s32 View_SetQuakeSpeed(View* view, f32 speed); // func_8013F448
s32 View_InitCameraQuake(View* view); // func_8013F45C
s32 View_ClearQuake(View* view); // func_8013F4C0
s32 View_SetQuake(View* view, f32 rotX, f32 rotY, f32 rotZ, f32 scaleX, f32 scaleY, f32 scaleZ, f32 speed); // func_8013F4F4
s32 View_StepQuake(View* view, RSPMatrix* matrix); // func_8013F54C
void View_RenderView(View* view, u32 uParm2); // func_8013F6FC
s32 View_RenderToPerspectiveMatrix(View* view); // func_8013F748
s32 View_RenderToOrthographicMatrix(View* view); // func_8013FA1C
s32 func_8013FBC8(View* view); // func_8013FBC8
s32 func_8013FD74(View* view); // func_8013FD74
s32 func_80140024(View* view); // func_80140024
s32 func_801400CC(View* view, Gfx** param_2); // func_801400CC
void func_80140260(void); // func_80140260
void func_8014026C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE1 param_9, UNK_TYPE4 param_10, UNK_TYPE2 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13); // func_8014026C
void func_80140730(void); // func_80140730
void func_80140810(void); // func_80140810
void func_80140898(void); // func_80140898
void func_80140900(void); // func_80140900
void func_8014090C(void); // func_8014090C
void func_80140970(void); // func_80140970
void func_80140CE0(void); // func_80140CE0
void func_80140D04(void); // func_80140D04
void func_80140D10(void); // func_80140D10
void func_80140E80(void* param_1); // func_80140E80
void func_80140EA0(void); // func_80140EA0
void func_80140EAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80140EAC
void func_80141008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80141008
void func_8014116C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8014116C
void func_801411B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_801411B4
void func_80141200(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80141200
void func_8014151C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8014151C
void func_80141678(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80141678
void func_80141778(void); // func_80141778
void func_801418B0(void); // func_801418B0
void func_80141900(void); // func_80141900
void func_80141924(void); // func_80141924
void func_80141C34(void); // func_80141C34
void func_80141E60(void); // func_80141E60
void func_8014204C(void); // func_8014204C
void func_801420C0(void); // func_801420C0
void func_801420F4(void); // func_801420F4
void func_80142100(void); // func_80142100
void func_80142440(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9); // func_80142440
void func_80143148(void); // func_80143148
void func_801431E8(void); // func_801431E8
void func_80143324(void); // func_80143324
void func_801434E4(ContextCommon* ctxt, int iParm2, short sParm3); // func_801434E4
void func_801435A0(void); // func_801435A0
void func_80143624(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7); // func_80143624
void func_80143668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80143668
void func_80143A04(void); // func_80143A04
void func_80143A10(void); // func_80143A10
void func_80143A54(void); // func_80143A54
void func_80143AC4(void); // func_80143AC4
void func_80143B0C(GlobalContext* ctxt); // func_80143B0C
void Sram_IncrementDay(void); // func_80144574
u32 Sram_CalcChecksum(u8* data, u32 length); // func_801445E4
void func_80144628(void); // func_80144628
void Sram_GenerateRandomSaveFields(void); // func_80144684
void func_80144890(void); // func_80144890
void func_80144968(void); // func_80144968
void func_80144A94(void); // func_80144A94
void func_80144E78(void); // func_80144E78
void func_8014546C(void); // func_8014546C
void func_80145698(void); // func_80145698
void func_801457CC(ContextCommon* ctxt, SramContext* param_2); // func_801457CC
void func_80146580(int param_1, SramContext* param_2, int param_3); // func_80146580
void func_80146628(void); // func_80146628
void func_80146AA0(void); // func_80146AA0
void func_80146DF8(void); // func_80146DF8
void func_80146E40(void); // func_80146E40
void Sram_Alloc(ContextCommon* ctxt, SramContext* iParm2); // func_80146E70
void func_80146EBC(SramContext* param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_80146EBC
void func_80146EE8(void); // func_80146EE8
void func_80146F5C(void); // func_80146F5C
void func_80147008(void); // func_80147008
void func_80147020(SramContext* param_1); // func_80147020
void func_80147068(SramContext* param_1); // func_80147068
void func_80147138(SramContext* param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_80147138
void func_80147150(SramContext* param_1); // func_80147150
void func_80147198(SramContext* param_1); // func_80147198
void func_80147314(void); // func_80147314
void func_80147414(void); // func_80147414
void Sram_nop8014750C(UNK_TYPE4 param_1); // func_8014750C
void func_80147520(void); // func_80147520
void func_80147564(GlobalContext* ctxt); // func_80147564
u32 func_80147624(GlobalContext* ctxt); // func_80147624
u32 func_80147734(GlobalContext* ctxt); // func_80147734
void func_801477B4(GlobalContext* ctxt); // func_801477B4
void func_80147818(GlobalContext* ctxt, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4); // func_80147818
void func_80147F18(GlobalContext* ctxt, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4); // func_80147F18
void func_80148558(GlobalContext* ctxt, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4); // func_80148558
void func_80148B98(GlobalContext* ctxt, u8 bParm2); // func_80148B98
void func_80148CBC(void); // func_80148CBC
void func_80148D64(void); // func_80148D64
void func_80149048(void); // func_80149048
void func_801491DC(void); // func_801491DC
void func_80149454(void); // func_80149454
void func_801496C8(void); // func_801496C8
void func_8014995C(void); // func_8014995C
void func_80149C18(void); // func_80149C18
void func_80149EBC(void); // func_80149EBC
void func_80149F74(GlobalContext* iParm1, unsigned int** ppuParm2); // func_80149F74
void func_8014AAD0(void); // func_8014AAD0
void func_8014ADBC(GlobalContext* iParm1, UNK_PTR puParm2); // func_8014ADBC
void func_8014C70C(void); // func_8014C70C
void func_8014CC14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_8014CC14
void func_8014CCB4(void); // func_8014CCB4
void func_8014CDF0(void); // func_8014CDF0
void func_8014CFDC(void); // func_8014CFDC
void func_8014D304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8014D304
void func_8014D62C(void); // func_8014D62C
void func_8014D7B4(void); // func_8014D7B4
void func_80150A84(void); // func_80150A84
void func_80150D08(GlobalContext* ctxt, unsigned int uParm2); // func_80150D08
void func_801514B0(void); // func_801514B0
void func_801518B0(GlobalContext* ctxt, u32 uParm2, UNK_TYPE4 uParm3); // func_801518B0
void func_80151938(GlobalContext* ctxt, u16 param_2); // func_80151938
void func_80151A68(void); // func_80151A68
void func_80151BB4(s32 iParm1, u32 uParm2); // func_80151BB4
void func_80151C9C(void); // func_80151C9C
void func_80151DA4(void); // func_80151DA4
void func_80152434(void); // func_80152434
void func_80152464(void); // func_80152464
UNK_TYPE4 func_80152498(MessageContext* iParm1); // func_80152498
void func_8015268C(void); // func_8015268C
void func_80152C64(void); // func_80152C64
void func_80152CAC(void); // func_80152CAC
void func_80152EC0(void); // func_80152EC0
void func_80152FB8(void); // func_80152FB8
void func_80153750(void); // func_80153750
void func_80153E7C(void); // func_80153E7C
void func_80153EF0(void); // func_80153EF0
void func_801541D4(void); // func_801541D4
void func_80156758(void); // func_80156758
void func_8015680C(GlobalContext* param_1); // func_8015680C
void func_801586A4(GlobalContext* ctxt); // func_801586A4
void Message_Init(GlobalContext* ctxt); // func_801586D4
void func_801588D0(GlobalContext* ctxt, short param_2); // func_801588D0
void func_80158988(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80158988
void func_80158A24(void); // func_80158A24
void func_80158C04(void); // func_80158C04
void func_80158D98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80158D98
void func_80158FB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80158FB0
void func_8015926C(void); // func_8015926C
void func_80159438(void); // func_80159438
void func_8015966C(void); // func_8015966C
void func_8015A144(void); // func_8015A144
void func_8015B198(void); // func_8015B198
void func_8015E750(void); // func_8015E750
void func_8015E7EC(GlobalContext* iParm1, UNK_PTR puParm2); // func_8015E7EC
void func_8015F8A8(UNK_TYPE4 ctxt); // func_8015F8A8
void func_80160A90(void); // func_80160A90
void func_80160AF8(void); // func_80160AF8
void func_80160B40(void); // func_80160B40
void func_80160B80(void); // func_80160B80
void func_80160BC0(void); // func_80160BC0
void ShrinkWindow_SetLetterboxTarget(s8 target); // func_80160C00
int ShrinkWindow_GetLetterboxTarget(void); // func_80160C14
void ShrinkWindow_SetLetterboxMagnitude(s8 magnitude); // func_80160C28
s32 ShrinkWindow_GetLetterboxMagnitude(void); // func_80160C3C
void ShrinkWindow_SetPillarboxTarget(s8 target); // func_80160C50
s32 ShrinkWindow_GetPillarboxTarget(void); // func_80160C64
void ShrinkWindow_SetPillarboxMagnitude(u8 magnitude); // func_80160C78
s32 ShrinkWindow_GetPillarboxMagnitude(void); // func_80160C8C
void ShrinkWindow_Init(void); // func_80160CA0
void ShrinkWindow_Fini(void); // func_80160CD4
void ShrinkWindow_Step(s32 framerateDivisor); // func_80160CE4
void ShrinkWindow_Draw(GlobalContext* ctxt); // func_80160D98
void func_80161180(void); // func_80161180
void func_8016119C(void); // func_8016119C
void func_8016122C(void); // func_8016122C
void func_801612B8(void); // func_801612B8
void func_80161998(void); // func_80161998
s32 func_80161BAC(void); // func_80161BAC
void func_80161BE0(void); // func_80161BE0
void func_80161C0C(void); // func_80161C0C
void func_80161C20(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80161C20
void func_80161E4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80161E4C
void func_801620CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801620CC
void func_8016237C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8016237C
void func_801623E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801623E4
void func_801624EC(void); // func_801624EC
void func_8016253C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8016253C
void func_801629BC(void); // func_801629BC
void func_80162A50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80162A50
void func_80162FF8(void); // func_80162FF8
void func_801631DC(void); // func_801631DC
void func_80163334(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80163334
void func_80163660(void); // func_80163660
void func_80163700(void); // func_80163700
void func_80163758(void); // func_80163758
void func_801637B4(void); // func_801637B4
void func_80163804(GlobalContext* ctxt); // func_80163804
void func_8016388C(void); // func_8016388C
void func_801638D8(void); // func_801638D8
void func_801639A0(void); // func_801639A0
void func_801639EC(GlobalContext* ctxt); // func_801639EC
void func_80163A38(GlobalContext* ctxt); // func_80163A38
void func_80163A58(void); // func_80163A58
void func_80163C0C(void); // func_80163C0C
void func_80163C90(void); // func_80163C90
void func_80163D80(void); // func_80163D80
void func_80163DC0(void); // func_80163DC0
void func_8016418C(void); // func_8016418C
void func_8016424C(void); // func_8016424C
void func_801642D8(void); // func_801642D8
void func_80164438(void); // func_80164438
void func_8016454C(void); // func_8016454C
void func_80164678(void); // func_80164678
void func_801647AC(void); // func_801647AC
UNK_TYPE4 func_801647B8(void); // func_801647B8
void func_801647D0(void); // func_801647D0
void* func_8016482C(void* param_1); // func_8016482C
void func_80164858(void); // func_80164858
void func_80164864(void); // func_80164864
void func_801649F4(void); // func_801649F4
void func_80164A80(void); // func_80164A80
void func_80164A8C(void); // func_80164A8C
void func_80164A98(void); // func_80164A98
void func_80164AF0(void); // func_80164AF0
void func_80164B40(void); // func_80164B40
void func_80164B94(void); // func_80164B94
void func_80164BA0(void); // func_80164BA0
void func_80164BD4(void); // func_80164BD4
void func_80164BE0(void); // func_80164BE0
void func_80164C14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80164C14
void func_80165044(void); // func_80165044
void func_80165198(void); // func_80165198
void func_801651B0(void); // func_801651B0
void func_80165224(void); // func_80165224
void func_80165288(void); // func_80165288
void func_8016537C(void); // func_8016537C
void func_80165438(UNK_PTR param_1); // func_80165438
void func_80165444(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5); // func_80165444
void func_80165460(void); // func_80165460
void func_80165608(void); // func_80165608
void func_80165630(void); // func_80165630
void func_80165658(void); // func_80165658
void func_8016566C(void); // func_8016566C
void func_80165690(void); // func_80165690
void func_801656A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_801656A4
void func_80165DCC(void); // func_80165DCC
void func_80165DF0(void); // func_80165DF0
void func_80165E1C(void); // func_80165E1C
void func_80165E7C(void); // func_80165E7C
void func_80165EC0(void); // func_80165EC0
void func_80166060(void); // func_80166060
void func_801660B8(GlobalContext* ctxt, UNK_TYPE4 param_2); // func_801660B8
void Play_Fini(GlobalContext* ctxt); // func_8016613C
void func_801663C4(void); // func_801663C4
void func_80166644(void); // func_80166644
void func_801668B4(void); // func_801668B4
void func_80166968(GlobalContext* ctxt, Camera* camera); // func_80166968
void func_80166B30(GlobalContext* param_1); // func_80166B30
void func_80167814(GlobalContext* ctxt); // func_80167814
void func_80167DE4(GlobalContext* ctxt); // func_80167DE4
void func_80167F0C(void); // func_80167F0C
void func_80168090(GlobalContext* ctxt); // func_80168090
void func_80168DAC(GlobalContext* ctxt); // func_80168DAC
void Play_Update(GlobalContext* ctxt); // func_80168F64
void func_801690CC(void); // func_801690CC
void func_80169100(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80169100
void func_801691F0(void); // func_801691F0
void* Play_LoadScene(GlobalContext* ctxt, SceneTableEntry* entry); // func_80169220
void func_8016927C(GlobalContext* ctxt, short sParm2); // func_8016927C
void func_801692C4(GlobalContext* ctxt, UNK_TYPE1 uParm2); // func_801692C4
void Play_SceneInit(GlobalContext* ctxt, int sceneIndex, UNK_TYPE1 param_3); // func_801693D4
void func_80169474(void); // func_80169474
s32 func_801694DC(GlobalContext* ctxt); // func_801694DC
int Play_GetActiveCameraIndex(GlobalContext* ctxt); // func_80169584
void func_80169590(GlobalContext* ctxt, short param_2, short param_3); // func_80169590
void func_80169600(GlobalContext* ctxt, s16 param_2); // func_80169600
void func_80169668(void); // func_80169668
Camera* Play_GetCamera(GlobalContext* ctxt, s16 index); // func_801696D4
void func_8016970C(void); // func_8016970C
void func_8016981C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8016981C
void func_80169940(void); // func_80169940
void func_80169988(void); // func_80169988
void func_801699D4(GlobalContext* ctxt, short param_2, short param_3); // func_801699D4
void func_80169A50(void); // func_80169A50
void func_80169AC0(void); // func_80169AC0
void func_80169AFC(void); // func_80169AFC
void func_80169C64(void); // func_80169C64
void func_80169C84(void); // func_80169C84
void convert_scene_number_among_shared_scenes(void); // func_80169CBC
void func_80169D40(GlobalContext* ctxt); // func_80169D40
void func_80169DCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_80169DCC
void func_80169E6C(void); // func_80169E6C
void func_80169ECC(void); // func_80169ECC
void func_80169EFC(void); // func_80169EFC
void func_80169F78(void); // func_80169F78
void func_80169FDC(void); // func_80169FDC
void func_80169FFC(void); // func_80169FFC
u32 func_8016A01C(GlobalContext* ctxt); // func_8016A01C
UNK_TYPE4 func_8016A02C(s32 param_1, s32 param_2, s16* param_3); // func_8016A02C
void func_8016A0AC(void); // func_8016A0AC
void func_8016A168(void); // func_8016A168
void func_8016A178(void); // func_8016A178
void func_8016A268(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6); // func_8016A268
void Play_Init(GlobalContext* ctxt); // func_8016A2C8
void func_8016AC10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_8016AC10
void func_8016AE1C(void); // func_8016AE1C
void func_8016B278(void); // func_8016B278
void func_8016B4B0(void); // func_8016B4B0
void func_8016C344(void); // func_8016C344
void func_8016CD4C(void); // func_8016CD4C
void func_8016E40C(void); // func_8016E40C
void func_8016EA90(void); // func_8016EA90
void func_8016F1A8(void); // func_8016F1A8
void func_8016F4EC(void); // func_8016F4EC
void func_8016F5A8(GlobalContext* ctxt, s8* pcParm2, Input* iParm3); // func_8016F5A8
void func_8016FC78(void); // func_8016FC78
void func_8016FC98(void); // func_8016FC98
void func_8016FCF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8016FCF0
void func_8016FD2C(void* param_1); // func_8016FD2C
void func_8016FD60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8016FD60
void func_8016FD94(void); // func_8016FD94
void func_8016FDB8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8016FDB8
void func_8016FF70(void); // func_8016FF70
void func_8016FF90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8016FF90
void func_80170200(void); // func_80170200
void func_8017023C(void); // func_8017023C
void func_8017057C(void); // func_8017057C
void func_801705B4(void); // func_801705B4
void func_801705EC(void); // func_801705EC
void func_80170730(void); // func_80170730
void func_80170774(void); // func_80170774
void func_80170798(void); // func_80170798
void func_80170AE0(void); // func_80170AE0
void func_80170B28(void); // func_80170B28
void func_80170B4C(void); // func_80170B4C
void func_8017160C(void); // func_8017160C
void func_801716C4(void); // func_801716C4
void func_801717F8(void); // func_801717F8
void func_80171F4C(int param_1); // func_80171F4C
void func_80171FA8(void); // func_80171FA8
void func_80172078(void); // func_80172078
void func_801720C4(void); // func_801720C4
void func_801720FC(void); // func_801720FC
void func_80172758(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); // func_80172758
void func_801727F0(GameStateHeap* heap, void* memoryBlock, u32 size); // func_801727F0
void func_80172810(void); // func_80172810
s32 func_80172830(GameStateHeap* pzParm1); // func_80172830
void func_80172850(void); // func_80172850
void func_80172870(void); // func_80172870
void func_80172890(void); // func_80172890
void func_801728B0(void); // func_801728B0
void func_801728D0(void); // func_801728D0
void func_801728F0(GameStateHeap* heap, int iParm2); // func_801728F0
void func_80172914(void); // func_80172914
void func_80172934(void); // func_80172934
void func_80172954(void); // func_80172954
void func_80172974(void); // func_80172974
void func_80172998(void); // func_80172998
void func_801729B8(void); // func_801729B8
void func_801729DC(void); // func_801729DC
void* GameStateHeap_GetStart(GameStateHeap* heap); // func_80172A00
void GameStateHeap_SetStart(GameStateHeap* heap, void* start); // func_80172A0C
void* GameStateHeap_GetEnd(GameStateHeap* heap); // func_80172A18
void* GameStateHeap_Alloc(GameStateHeap* heap, int iParm2); // func_80172A24
void* GameStateHeap_AllocByte(GameStateHeap* pzParm1); // func_80172A38
void* GameStateHeap_AllocFromEndAlignedTo(GameStateHeap* heap, void* ptr); // func_80172A58
void* GameStateHeap_AllocFromEnd(GameStateHeap* heap, u32 size); // func_80172AC8
void* GameStateHeap_AllocFromEndAligned(GameStateHeap* heap, u32 size, u32 allignment); // func_80172AE8
s32 GameStateHeap_GetFreeSize(GameStateHeap* iParm1); // func_80172B04
s32 GameStateHeap_GetHasOverflowed(GameStateHeap* pzParm1); // func_80172B18
void GameStateHeap_InitAppend(GameStateHeap* heap); // func_80172B3C
void GameStateHeap_Init(GameStateHeap* heap, void* memoryBlock, u32 size); // func_80172B58
void GameStateHeap_Clear(GameStateHeap* pvParm1); // func_80172B9C
void func_80172BC0(void); // func_80172BC0
void func_80172C30(AudioThreadStruct* audio); // func_80172C30
void func_80172C68(AudioThreadStruct* audio); // func_80172C68
void Audio_Stop(void); // func_80172EAC
void Audio_ThreadEntry(AudioThreadStruct* audio); // func_80172ED0
void Audio_WaitForInit(AudioThreadStruct* param_1); // func_80173048
void Audio_Start(AudioThreadStruct* audio, s32* audioThreadStackEnd, OSPri pri, OSId id, SchedThreadStruct* sched, Irqmgr* irq); // func_80173074
void func_80173130(void); // func_80173130
void Initial_Init2(ContextCommon* ctxt); // func_801732DC
void Initial_Fini(void); // func_8017332C
void Initial_Init(ContextCommon* ctxt); // func_80173338
void Game_UpdateFramerateVariables(s32 divisor); // func_80173360
void Game_SetFramerateDivisor(ContextCommon* iParm1, u32 divisor); // func_801733A8
void func_801733DC(void); // func_801733DC
void Game_Nop80173534(ContextCommon* ctxt); // func_80173534
void func_80173540(ContextCommon* ctxt, GraphicsContext* gCtxt); // func_80173540
void Game_ResetSegments(GraphicsContext* gCtxt); // func_80173644
void func_801736DC(GraphicsContext* gCtxt); // func_801736DC
void Game_UpdateInput(ContextCommon* ctxt); // func_80173754
void Game_Update(ContextCommon* ctxt); // func_8017377C
void Game_IncrementFrameCount(ContextCommon* ctxt); // func_801737E4
void Game_InitHeap(ContextCommon* ctxt, u32 size); // func_80173810
void Game_ResizeHeap(ContextCommon* ctxt, u32 size); // func_80173880
void Game_StateInit(ContextCommon* ctxt, func_ptr gameStateInit, GraphicsContext* gCtxt); // func_80173950
void Game_StateFini(ContextCommon* ctxt); // func_80173A50
UNK_TYPE4 Game_GetNextStateInit(ContextCommon* ctxt); // func_80173B00
u32 Game_GetNextStateSize(ContextCommon* ctxt); // func_80173B0C
u32 Game_GetShouldContinue(ContextCommon* ctxt); // func_80173B18
void Game_GetHeapFreeSize(ContextCommon* ctxt); // func_80173B24
int func_80173B48(ContextCommon* ctxt); // func_80173B48
GameAllocNode* func_80173BF0(GameAllocNode* heap); // func_80173BF0
void* Gamealloc_Alloc(GameAllocNode* heap, u32 size); // func_80173C10
void Gamealloc_Free(GameAllocNode* heap, void* ptr); // func_80173C7C
void Gamealloc_FreeAll(GameAllocNode* heap); // func_80173CC8
void Gamealloc_Init(GameAllocNode* iParm1); // func_80173D18
void Graph_FaultDrawFunc(void); // func_80173D30
void Graph_DlAlloc(DisplayList* dl, void* memoryBlock, u32 size); // func_80173DAC
void Graph_RenderSetup(GraphicsContext* gCtxt); // func_80173DCC
GameStateMetaInfo* Graph_GetNextGameStateMetaInfo(ContextCommon* ctxt); // func_80173F98
void* Graph_FaultAddrConvFunc(void* addr); // func_80174060
void Graph_ContextInit(GraphicsContext* gCtxt); // func_801740D0
void Graph_Fini(void); // func_80174174
void Graph_Render(GraphicsContext* gCtxt, ContextCommon* ctxt); // func_801741A8
void Graph_FrameSetup(ContextCommon* ctxt); // func_801744AC
void Graph_RenderFrame(GraphicsContext* gCtxt, ContextCommon* ctxt); // func_801744F8
void Graph_DoFrame(GraphicsContext* gCtxt, ContextCommon* ctxt); // func_80174868
void Graph_ThreadEntry(void* arg); // func_801748A0
void func_80174A40(void); // func_80174A40
void func_80174A4C(void); // func_80174A4C
void func_80174A64(void); // func_80174A64
void func_80174AA0(void); // func_80174AA0
void func_80174AB4(void); // func_80174AB4
void func_80174B20(void); // func_80174B20
void func_80174BA0(void); // func_80174BA0
void main(void* arg); // func_80174BF0
u32 Padmgr_GetControllerBitmask(void); // func_80174F10
void func_80174F24(void); // func_80174F24
void func_80174F44(void); // func_80174F44
void func_80174F7C(void); // func_80174F7C
void func_80174F9C(void); // func_80174F9C
OSMesgQueue* Padmgr_GetEventCallback(void); // func_80174FD4
void func_80175008(void); // func_80175008
void Padmgr_SetEventCallback(OSMesg pvParm1); // func_8017503C
void func_8017506C(void); // func_8017506C
void Padmgr_Lock(void); // func_8017509C
void Padmgr_Unlock(void); // func_801750CC
void func_801750FC(void); // func_801750FC
void func_80175364(void); // func_80175364
void func_80175434(void); // func_80175434
void func_8017544C(void); // func_8017544C
void func_80175474(void); // func_80175474
void func_801754C0(void); // func_801754C0
void Padmgr_CalcStickEdges(Input* input); // func_801754E0
void Padmgr_ParseState(void); // func_801757A4
void func_801759BC(void); // func_801759BC
void func_80175AE0(void); // func_80175AE0
void Padmgr_Update(void); // func_80175C80
void Padmgr_Stop(void); // func_80175E3C
void func_80175E68(Input* input, int param_2); // func_80175E68
void Padmgr_GetInput(Input* input, int param_2); // func_80175F98
void Padmgr_GetInput2(Input* input, int param_2); // func_80175FD4
void Padmgr_ThreadEntry(PadmgrThreadStruct* padmgr); // func_80176010
void Padmgr_Start(OSMesgQueue* siEventCallbackQueue, Irqmgr* irqmgr, OSId threadId, OSPri threadPri, void* stack); // func_80176194
void func_80176280(void); // func_80176280
void func_80176314(void); // func_80176314
void Sched_Nop80176364(SchedThreadStruct* sched); // func_80176364
void func_80176370(SchedThreadStruct* sched); // func_80176370
void func_80176394(SchedThreadStruct* sched); // func_80176394
void func_801764F0(SchedThreadStruct* sched); // func_801764F0
void func_8017668C(SchedThreadStruct* sched, UNK_PTR puParm2); // func_8017668C
void func_801766F0(void); // func_801766F0
void func_80176748(void); // func_80176748
void func_801767B8(void); // func_801767B8
void func_801768E0(void); // func_801768E0
void func_8017691C(void); // func_8017691C
void func_80176988(void); // func_80176988
void func_80176B34(SchedThreadStruct* sched); // func_80176B34
void func_80176C24(SchedThreadStruct* sched); // func_80176C24
void func_80176CF4(SchedThreadStruct* sched); // func_80176CF4
void func_80176F2C(SchedThreadStruct* sched); // func_80176F2C
void func_80177018(SchedThreadStruct* sched); // func_80177018
void func_8017703C(SchedThreadStruct* sched); // func_8017703C
void func_80177060(SchedThreadStruct* sched); // func_80177060
void func_80177084(SchedThreadStruct* sched); // func_80177084
void Sched_ThreadEntry(SchedThreadStruct* sched); // func_8017715C
void func_80177280(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_80177280
void Sched_Start(SchedThreadStruct* sched, void* stack, OSPri pri, UNK_TYPE4 param_4, UNK_TYPE4 param_5, Irqmgr* irqmgrStruct); // func_801772A0
void func_80177390(void); // func_80177390
void func_801773A0(void); // func_801773A0
void func_801773C4(void); // func_801773C4
void func_801773D0(void); // func_801773D0
void func_80177A84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_80177A84
void func_80177AC8(void); // func_80177AC8
void func_80177E58(void); // func_80177E58
void func_801780F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801780F0
void func_801781EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801781EC
void func_8017842C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017842C
void func_80178750(void); // func_80178750
void func_80178818(void); // func_80178818
void func_80178978(void); // func_80178978
void func_801789D4(void); // func_801789D4
u32* get_framebuffer(s32 index); // func_801789EC
void func_80178A14(void); // func_80178A14
UNK_TYPE4 func_80178A24(void); // func_80178A24
void func_80178A34(void); // func_80178A34
s32 func_80178A94(s32 param_1, s32 param_2); // func_80178A94
void func_80178AC0(void); // func_80178AC0
void func_80178C80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80178C80
void func_80178D7C(void); // func_80178D7C
void func_80178DAC(void); // func_80178DAC
void func_80178E3C(void); // func_80178E3C
void func_80178E7C(void); // func_80178E7C
void Check_WriteRGB5A1Pixel(u16* buffer, u32 x, u32 y, u16 value); // func_80178F30
void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value); // func_80178F60
void Check_DrawI4Texture(u16* buffer, u32 x, u32 y, u32 width, u32 height, u8* texture); // func_80178FA0
void Check_ClearRGB5A1(s16* buffer); // func_80179090
void Check_DrawExpansionPakErrorMessage(void); // func_8017910C
void Check_DrawRegionLockErrorMessage(void); // func_801791CC
void Check_ExpansionPak(void); // func_80179260
void Check_RegionIsSupported(void); // func_801792A4
f32 func_80179300(f32 param_1); // func_80179300
f32 func_80179400(s32 param_1); // func_80179400
f32 pow_int(f32 x, s32 pow); // func_801794C4
f32 sin_rad(f32 rad); // func_801794EC
f32 cos_rad(f32 rad); // func_80179540
f32 randZeroOneScaled(f32 scale); // func_80179594
f32 randPlusMinusPoint5Scaled(f32 scale); // func_801795C0
f32 Math3D_Normalize(Vector3f* vec); // func_801795F0
UNK_TYPE4 func_80179678(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_80179678
UNK_TYPE4 func_80179798(Vector3f* param_1, Vector3f* param_2, Vector3f* param_3, Vector3f* param_4, Vector3f* param_5, Vector3f* param_6); // func_80179798
void func_80179A44(void); // func_80179A44
void func_80179B34(float fParm1, float fParm2, float fParm5, float fParm6, float param_5, float param_6, float param_7, float* param_8, float* param_9); // func_80179B34
UNK_TYPE4 func_80179B94(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, f32 param_8, Vector3f* param_9); // func_80179B94
void func_80179D74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80179D74
void Math3D_ScaleAndAdd(Vector3f* a, Vector3f* b, f32 scale, Vector3f* dst); // func_80179DF0
void Math3D_Lerp(Vector3f* a, Vector3f* b, f32 t, Vector3f* dst); // func_80179E3C
s32 Math3D_Parallel(Vector3f* a, Vector3f* b); // func_80179E88
s32 Math3D_AngleBetweenVectors(Vector3f* a, Vector3f* b, f32* angle); // func_80179EAC
void func_80179F64(Vector3f* param_1, Vector3f* param_2, Vector3f* param_3); // func_80179F64
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z); // func_8017A038
void func_8017A09C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A09C
void func_8017A1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A1D0
void func_8017A304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A304
UNK_TYPE4 func_8017A438(Vector3f* pfParm1, Vector3f* pfParm2, Vector3f* pfParm3, Vector3f* pfParm4, f32 param_5); // func_8017A438
f32 Math3D_XZLengthSquared(f32 x, f32 z); // func_8017A5F8
f32 Math3D_XZLength(f32 x, f32 z); // func_8017A610
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2); // func_8017A634
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2); // func_8017A678
f32 Math3D_LengthSquared(Vector3f* vec); // func_8017A6A8
f32 Math3D_Length(Vector3f* vec); // func_8017A6D4
f32 Math3D_DistanceSquared(Vector3f* a, Vector3f* b); // func_8017A6F8
f32 Math3D_Distance(Vector3f* a, Vector3f* b); // func_8017A720
f32 Math3D_DistanceS(Vector3s* s, Vector3f* f); // func_8017A740
f32 func_8017A7B8(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A7B8
f32 func_8017A7F8(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A7F8
f32 func_8017A838(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A838
void Math3D_CrossProduct(Vector3f* a, Vector3f* b, Vector3f* res); // func_8017A878
void Math3D_NormalVector(Vector3f* a, Vector3f* b, Vector3f* c, Vector3f* res); // func_8017A8EC
unsigned int func_8017A954(Vector3f* param_1, Vector3f* param_2, Vector3f* param_3); // func_8017A954
unsigned int func_8017AA0C(Vector3f* param_1, Vector3f* param_2, Vector3f* param_3); // func_8017AA0C
unsigned int func_8017ABBC(Vector3f* param_1, Vector3f* param_2, Vector3f* param_3); // func_8017ABBC
void func_8017AD38(void); // func_8017AD38
void func_8017B68C(void); // func_8017B68C
void func_8017B7F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017B7F8
void Math3D_UnitNormalVector(Vector3f* a, Vector3f* b, Vector3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7); // func_8017B884
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vector3f* position); // func_8017B998
void func_8017B9D8(void); // func_8017B9D8
f32 Math3D_NormalizedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vector3f* position); // func_8017BA14
f32 Math3D_NormalizedSignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vector3f* position); // func_8017BA4C
void func_8017BAD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8017BAD0
void func_8017BD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017BD98
void func_8017BDE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017BDE0
void func_8017BE30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017BE30
void func_8017BEE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017BEE0
void func_8017BF8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017BF8C
void func_8017C008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_8017C008
void func_8017C17C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017C17C
void func_8017C1F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8017C1F0
void func_8017C494(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017C494
void func_8017C540(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8017C540
void func_8017C808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017C808
void func_8017C850(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_8017C850
void func_8017C904(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017C904
void func_8017C980(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_8017C980
void func_8017CB08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017CB08
void func_8017CB7C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8017CB7C
void func_8017CEA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017CEA8
void func_8017CEF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_8017CEF0
void func_8017CFA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017CFA4
void func_8017D020(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_8017D020
void func_8017D1AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017D1AC
void func_8017D220(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017D220
void func_8017D2FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8017D2FC
void func_8017D404(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017D404
void Math3D_TriSetCoords(ColTriParams* tri, Vector3f* pointA, Vector3f* pointB, Vector3f* pointC); // func_8017D568
u32 Math3D_IsPointInSphere(ColSphereCollisionInfo* sphere, Vector3f* point); // func_8017D618
void func_8017D668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_8017D668
void func_8017D7C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017D7C0
void func_8017D814(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017D814
void func_8017D91C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017D91C
void func_8017DA24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017DA24
s32 Math3D_ColSphereLineSeg(ColSphereCollisionInfo* sphere, LineSegment* line); // func_8017DB2C
void func_8017DD34(ColSphereCollisionInfo* sphere, ColTriParams* tri, Vector3f* pfParm3); // func_8017DD34
s32 Math3D_ColSphereTri(ColSphereCollisionInfo* sphere, ColTriParams* tri, Vector3f* uParm3); // func_8017DE74
void func_8017E294(void); // func_8017E294
void func_8017E350(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017E350
s32 Math3D_ColCylinderTri(ColCylinderParams* cylinder, ColTriParams* tri, Vector3f* pzParm3); // func_8017ED20
void func_8017F1A0(void); // func_8017F1A0
s32 Math3D_ColSphereSphere(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2); // func_8017F1C0
s32 Math3D_ColSphereSphereIntersect(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2, f32* intersectAmount); // func_8017F1E0
s32 Math3D_ColSphereSphereIntersectAndDistance(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2, f32* intersectAmount, f32* dist); // func_8017F200
s32 Math3D_ColSphereCylinderDistance(ColSphereCollisionInfo* sphere, ColCylinderParams* cylinder, f32* dist); // func_8017F2CC
s32 Math3D_ColSphereCylinderDistanceAndAmount(ColSphereCollisionInfo* sphere, ColCylinderParams* cylinder, f32* dist, f32* intersectAmount); // func_8017F2EC
s32 Math3D_ColCylinderCylinderAmount(ColCylinderParams* cylinder1, ColCylinderParams* cylinder2, f32* intersectAmount); // func_8017F45C
s32 Math3D_ColCylinderCylinderAmountAndDistance(ColCylinderParams* cylinder1, ColCylinderParams* cylinder2, f32* intersectAmount, f32* dist); // func_8017F47C
s32 Math3d_ColTriTri(ColTriParams* tri1, ColTriParams* tri2, Vector3f* uParm3); // func_8017F64C
void func_8017F9C0(void); // func_8017F9C0
void func_8017FA34(void); // func_8017FA34
void func_8017FAA8(void); // func_8017FAA8
void func_8017FB1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017FB1C
void func_8017FD44(void); // func_8017FD44
s16 atans_first_8th(f32 opposite, f32 adjacent); // func_8017FEB0
s16 atans(f32 opposite, f32 adjacent); // func_8017FEE4
f32 atan(f32 opposite, f32 adjacent); // func_801800CC
s16 atans_flip(f32 adjacent, f32 opposite); // func_80180100
void atan_flip(f32 adjacent, f32 opposite); // func_8018012C
void SysMatrix_StateAlloc(ContextCommon* ctxt); // func_80180160
void SysMatrix_StatePush(void); // func_8018019C
void SysMatrix_StatePop(void); // func_801801CC
void SysMatrix_CopyCurrentState(z_Matrix* matrix); // func_801801E8
void SysMatrix_SetCurrentState(z_Matrix* matrix); // func_8018020C
z_Matrix* SysMatrix_GetCurrentState(void); // func_80180234
void SysMatrix_InsertMatrix(z_Matrix* matrix, s32 appendToState); // func_80180244
void SysMatrix_InsertTranslation(f32 x, f32 y, f32 z, s32 appendToState); // func_8018029C
void SysMatrix_InsertScale(f32 xScale, f32 yScale, f32 zScale, s32 appendToState); // func_8018039C
void SysMatrix_InsertXRotation_s(s16 rotation, s32 appendToState); // func_80180478
void SysMatrix_InsertXRotation_f(f32 rotation, s32 appendToState); // func_80180610
void SysMatrix_RotateStateAroundXAxis(f32 rotation); // func_801807B8
void SysMatrix_SetStateXRotation(f32 rotation); // func_80180900
void SysMatrix_InsertYRotation_s(s16 rotation, s32 appendToState); // func_801809AC
void SysMatrix_InsertYRotation_f(f32 rotation, s32 appendToState); // func_80180B48
void SysMatrix_InsertZRotation_s(s16 rotation, s32 appendToState); // func_80180CF8
void SysMatrix_InsertZRotation_f(f32 rotation, s32 appendToState); // func_80180E90
void SysMatrix_InsertRotation(s16 xRotation, s16 yRotation, s16 zRotation, s32 appendToState); // func_8018103C
void SysMatrix_RotateAndTranslateState(Vector3f* translation, Vector3s* rotation); // func_801812FC
void SysMatrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vector3s* rotation); // func_80181650
RSPMatrix* SysMatrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst); // func_801817FC
RSPMatrix* SysMatrix_GetStateAsRSPMatrix(RSPMatrix* matrix); // func_80181A18
RSPMatrix* SysMatrix_AppendStateToPolyOpaDisp(GraphicsContext* gCtxt); // func_80181A40
void SysMatrix_AppendToPolyOpaDisp(z_Matrix* ctxt, GraphicsContext* gCtxt); // func_80181A6C
void SysMatrix_MultiplyVector3fByState(Vector3f* src, Vector3f* dst); // func_80181A98
void SysMatrix_GetStateTranslation(Vector3f* dst); // func_80181B50
void SysMatrix_GetStateTranslationAndScaledX(f32 scale, Vector3f* dst); // func_80181B78
void SysMatrix_GetStateTranslationAndScaledY(f32 scale, Vector3f* dst); // func_80181BC4
void SysMatrix_GetStateTranslationAndScaledZ(f32 scale, Vector3f* dst); // func_80181C10
void SysMatrix_MultiplyVector3fXZByCurrentState(Vector3f* src, Vector3f* dst); // func_80181C5C
void SysMatrix_Copy(z_Matrix* dst, z_Matrix* src); // func_80181CDC
void SysMatrix_FromRSPMatrix(RSPMatrix* src, z_Matrix* dst); // func_80181D64
void SysMatrix_MultiplyVector3fByMatrix(Vector3f* src, Vector3f* dst, z_Matrix* matrix); // func_80181FB8
void SysMatrix_TransposeXYZ(z_Matrix* matrix); // func_80182068
void SysMatrix_NormalizeXYZ(z_Matrix* matrix); // func_801820A0
void func_8018219C(z_Matrix* pfParm1, Vector3s* psParm2, s32 iParm3); // func_8018219C
void func_801822C4(void); // func_801822C4
void SysMatrix_InsertRotationAroundUnitVector_f(f32 rotation, Vector3f* vector, s32 appendToState); // func_801823EC
void SysMatrix_InsertRotationAroundUnitVector_s(s16 rotation, Vector3f* vector, s32 appendToState); // func_8018284C
void func_80182C90(void); // func_80182C90
void func_80182CA0(void); // func_80182CA0
void func_80182CBC(void); // func_80182CBC
void func_80182CCC(void); // func_80182CCC
void func_80182CE0(void); // func_80182CE0
void func_80183020(void); // func_80183020
void func_80183058(void); // func_80183058
void func_80183070(void); // func_80183070
void func_801830A0(void); // func_801830A0
void func_801830C8(void); // func_801830C8
void func_801830E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801830E8
void func_80183148(void); // func_80183148
void func_80183224(void); // func_80183224
void func_801832B0(void); // func_801832B0
void func_8018332C(void); // func_8018332C
void func_8018340C(void); // func_8018340C
void func_80183430(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80183430
void func_8018349C(void); // func_8018349C
void func_801834A8(void); // func_801834A8
void func_80183510(void); // func_80183510
void func_80183580(void); // func_80183580
void func_801835EC(void); // func_801835EC
void func_80183658(void); // func_80183658
void func_801836CC(void); // func_801836CC
void func_8018373C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_8018373C
void func_801837CC(void); // func_801837CC
void func_80183808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80183808
void func_80183880(void); // func_80183880
void func_80183A3C(void); // func_80183A3C
void func_80183B08(void); // func_80183B08
void func_80183B68(void); // func_80183B68
void func_80183DE0(void); // func_80183DE0
void func_8018410C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8018410C
void func_8018450C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8018450C
void func_801845A4(void); // func_801845A4
void func_801845C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801845C8
void func_80184638(void); // func_80184638
void func_801846AC(void); // func_801846AC
void func_80184728(void); // func_80184728
void func_801847A0(void); // func_801847A0
void func_80184818(void); // func_80184818
void func_80184898(void); // func_80184898
void func_80184914(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80184914
void func_801849A0(void); // func_801849A0
void func_801849DC(void); // func_801849DC
void func_80184C48(void); // func_80184C48
void func_801850A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801850A0
void func_801853C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801853C8
void func_80185460(void); // func_80185460
void Slowly_Main(s8018571C* iParm1); // func_80185660
void Slowly_ThreadEntry(s8018571C* param_1); // func_801856FC
void Slowly_Start(s8018571C* param_1, s32* stack, UNK_TYPE4 param_3, s32 param_4, s32 param_5); // func_8018571C
void func_801857A0(void); // func_801857A0
void func_801857C0(void); // func_801857C0
char* func_801857D0(void); // func_801857D0
void func_80185864(void); // func_80185864
void func_80185908(void); // func_80185908
void func_80185968(void); // func_80185968
void func_801859F0(void); // func_801859F0
void func_80185A2C(void); // func_80185A2C
void func_80185B1C(void); // func_80185B1C
void func_80185BE4(void); // func_80185BE4
void func_80185C24(void); // func_80185C24
void SysFlashrom_ThreadEntry(s80185D40* param_1); // func_80185D40
void func_80185DDC(void); // func_80185DDC
void func_80185EC4(void); // func_80185EC4
void func_80185F04(void); // func_80185F04
void func_80185F64(void); // func_80185F64
s32 func_80185F90(u32 param_1); // func_80185F90
void func_80186A70(void); // func_80186A70
void func_80186B78(void); // func_80186B78
void func_80186CAC(void); // func_80186CAC
void func_80186D60(void); // func_80186D60
void func_80186E64(void); // func_80186E64
void func_80186EC8(void); // func_80186EC8
void func_80187018(void); // func_80187018
void func_80187080(void); // func_80187080
void func_80187124(void); // func_80187124
void func_80187284(void); // func_80187284
void func_801872FC(void); // func_801872FC
void func_801873BC(void); // func_801873BC
void func_8018752C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8018752C
void func_801877D0(void); // func_801877D0
void func_80187B64(void); // func_80187B64
void func_80187BEC(void); // func_80187BEC
void func_80187DE8(void); // func_80187DE8
void func_80187E58(void); // func_80187E58
void func_80187F00(void); // func_80187F00
void func_80187FB0(void); // func_80187FB0
void func_80187FE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80187FE8
void func_80188034(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80188034
void func_80188078(void); // func_80188078
void func_801880C4(void); // func_801880C4
void func_801880E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801880E8
void func_80188124(void); // func_80188124
void func_8018814C(void); // func_8018814C
void func_80188174(void); // func_80188174
void func_801881A8(void); // func_801881A8
void func_801881C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801881C4
void func_801881F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801881F8
void func_80188264(void); // func_80188264
void func_80188288(void); // func_80188288
void func_801882A0(void); // func_801882A0
void func_80188304(void); // func_80188304
void func_801884A0(void); // func_801884A0
void func_80188698(void); // func_80188698
void func_8018883C(void); // func_8018883C
void func_801888E4(void); // func_801888E4
void func_801889A4(void); // func_801889A4
void func_80188A50(void); // func_80188A50
void func_80188AFC(void); // func_80188AFC
void func_80188C48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80188C48
void func_80188CB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80188CB4
void func_80188D28(void); // func_80188D28
void func_80188D68(void); // func_80188D68
void func_80188DDC(void); // func_80188DDC
void func_80188FBC(void); // func_80188FBC
void func_80189064(void); // func_80189064
void func_80189620(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80189620
void func_8018A4B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8018A4B4
void func_8018A768(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_8018A768
void func_8018A808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_8018A808
void func_8018ACC4(void); // func_8018ACC4
void func_8018AE34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8018AE34
void func_8018B0F0(void); // func_8018B0F0
void func_8018B10C(void); // func_8018B10C
void func_8018B250(void); // func_8018B250
void func_8018B318(void); // func_8018B318
void func_8018B474(void); // func_8018B474
void func_8018B4F8(void); // func_8018B4F8
void func_8018B520(void); // func_8018B520
void func_8018B578(void); // func_8018B578
void func_8018B5D0(void); // func_8018B5D0
void func_8018B608(void); // func_8018B608
void func_8018B640(void); // func_8018B640
void func_8018B69C(void); // func_8018B69C
void func_8018B6E8(void); // func_8018B6E8
void func_8018B740(void); // func_8018B740
void func_8018B768(void); // func_8018B768
void func_8018B77C(void); // func_8018B77C
void func_8018B7BC(void); // func_8018B7BC
void func_8018B8FC(void); // func_8018B8FC
void func_8018B95C(void); // func_8018B95C
void func_8018B9E0(void); // func_8018B9E0
void func_8018BA64(void); // func_8018BA64
void func_8018BB28(void); // func_8018BB28
void func_8018BBEC(void); // func_8018BBEC
void func_8018C380(void); // func_8018C380
void func_8018C3D8(void); // func_8018C3D8
void func_8018C8E8(void); // func_8018C8E8
void func_8018C93C(void); // func_8018C93C
void func_8018C994(void); // func_8018C994
void func_8018CB70(void); // func_8018CB70
void func_8018CB78(void); // func_8018CB78
void func_8018CC3C(void); // func_8018CC3C
void func_8018CCA8(void); // func_8018CCA8
void func_8018CFAC(void); // func_8018CFAC
void func_8018D57C(void); // func_8018D57C
void func_8018D5D4(void); // func_8018D5D4
void func_8018D658(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8018D658
void func_8018D6C8(void); // func_8018D6C8
void func_8018D760(void); // func_8018D760
void func_8018DA50(void); // func_8018DA50
void func_8018DBC4(void); // func_8018DBC4
void func_8018DCB4(void); // func_8018DCB4
void func_8018DCF8(void); // func_8018DCF8
void func_8018DD98(void); // func_8018DD98
void func_8018DDD4(void); // func_8018DDD4
void func_8018DF24(void); // func_8018DF24
void func_8018DFE0(void); // func_8018DFE0
void func_8018E00C(void); // func_8018E00C
void func_8018E03C(void); // func_8018E03C
void func_8018E2A8(void); // func_8018E2A8
void func_8018E344(void); // func_8018E344
void func_8018E8C8(void); // func_8018E8C8
void func_8018EB60(void); // func_8018EB60
void func_8018EC4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8018EC4C
void func_8018EF88(void); // func_8018EF88
void func_8018F220(void); // func_8018F220
void func_8018F298(void); // func_8018F298
void func_8018F310(void); // func_8018F310
void func_8018F388(void); // func_8018F388
void func_8018F3B8(void); // func_8018F3B8
void func_8018F3E8(void); // func_8018F3E8
void func_8018F448(void); // func_8018F448
void func_8018F478(void); // func_8018F478
void func_8018F4D8(void); // func_8018F4D8
void func_8018F588(void); // func_8018F588
void func_8018F604(void); // func_8018F604
void func_8018F6F0(void); // func_8018F6F0
void func_8018F7C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8018F7C0
void func_8018F7F8(void); // func_8018F7F8
void func_8018F83C(void); // func_8018F83C
void func_8018F880(void); // func_8018F880
void func_8018F8C4(void); // func_8018F8C4
void func_8018F908(void); // func_8018F908
void func_8018F9B8(void); // func_8018F9B8
void func_8018FA60(void); // func_8018FA60
void func_8018FAD0(void); // func_8018FAD0
void func_8018FB20(void); // func_8018FB20
void func_8018FB78(void); // func_8018FB78
void func_8018FCCC(void); // func_8018FCCC
void func_8018FD20(void); // func_8018FD20
void func_8018FD40(void); // func_8018FD40
void func_8018FE5C(void); // func_8018FE5C
void func_8018FF60(void); // func_8018FF60
void func_80190204(void); // func_80190204
void func_80190240(void); // func_80190240
void func_80190294(void); // func_80190294
void func_801902D8(void); // func_801902D8
void func_80190544(void); // func_80190544
void func_80190668(void); // func_80190668
void func_8019067C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8019067C
void func_8019075C(void); // func_8019075C
void func_8019077C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8019077C
void func_80190B08(void); // func_80190B08
void func_80190B38(void); // func_80190B38
void func_80190B50(void); // func_80190B50
void func_80190BB0(void); // func_80190BB0
void func_80190F50(void); // func_80190F50
void func_80190F64(void); // func_80190F64
void func_80191134(void); // func_80191134
void func_801911CC(void); // func_801911CC
void func_80191240(void); // func_80191240
void func_801913C8(void); // func_801913C8
void func_8019144C(void); // func_8019144C
void func_80191460(void); // func_80191460
void func_80191568(void); // func_80191568
void func_80191598(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80191598
void func_8019161C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8019161C
void func_80191740(void); // func_80191740
void func_80191864(void); // func_80191864
void func_80191870(void); // func_80191870
void func_801919AC(void); // func_801919AC
void func_80191B40(void); // func_80191B40
void func_80191BD0(void); // func_80191BD0
void func_80191C40(void); // func_80191C40
void func_80191C54(void); // func_80191C54
void func_80191D94(void); // func_80191D94
void func_8019218C(void); // func_8019218C
void func_80192340(void); // func_80192340
void func_80192388(void); // func_80192388
void func_801924BC(void); // func_801924BC
void func_80192514(void); // func_80192514
void func_80192990(void); // func_80192990
void func_80192AE8(void); // func_80192AE8
void func_80192B54(void); // func_80192B54
void func_80192BAC(void); // func_80192BAC
void func_80192BE0(void); // func_80192BE0
void func_80192C00(void); // func_80192C00
void func_8019319C(void); // func_8019319C
void func_801936D8(void); // func_801936D8
void func_8019372C(void); // func_8019372C
void func_80193774(void); // func_80193774
void func_8019380C(void); // func_8019380C
void func_80193858(void); // func_80193858
void func_8019387C(void); // func_8019387C
void func_801938A0(void); // func_801938A0
void func_801938D0(void); // func_801938D0
void func_80193900(void); // func_80193900
void func_80193990(void); // func_80193990
void func_801939A8(void); // func_801939A8
void func_80193AEC(void); // func_80193AEC
void func_80193BA0(void); // func_80193BA0
void func_80193C04(void); // func_80193C04
void func_80193C5C(void); // func_80193C5C
void func_80193CB4(void); // func_80193CB4
void func_80193D08(void); // func_80193D08
void func_80193DA4(void); // func_80193DA4
void func_80193E6C(void); // func_80193E6C
void func_80193EA8(void); // func_80193EA8
void func_80194080(void); // func_80194080
void func_80194304(void); // func_80194304
void func_80194328(void); // func_80194328
void func_8019435C(void); // func_8019435C
void func_8019439C(void); // func_8019439C
void func_801943D0(void); // func_801943D0
void func_8019440C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8019440C
void func_80194528(void); // func_80194528
void func_80194548(void); // func_80194548
void func_80194568(void); // func_80194568
void func_80194668(void); // func_80194668
void func_801946E4(void); // func_801946E4
void func_80194710(void); // func_80194710
void func_80194750(void); // func_80194750
void func_80194790(void); // func_80194790
void func_80194840(void); // func_80194840
void func_801948B0(void); // func_801948B0
void func_80194930(void); // func_80194930
void func_80194DB0(void); // func_80194DB0
void func_80194E60(void); // func_80194E60
void func_80194F20(void); // func_80194F20
void func_80194F84(void); // func_80194F84
void func_801954CC(void); // func_801954CC
void func_80195508(void); // func_80195508
void func_801955DC(void); // func_801955DC
void func_801956C0(void); // func_801956C0
void func_801957B4(void); // func_801957B4
void func_801958F8(void); // func_801958F8
void func_80195C40(void); // func_80195C40
void func_80195C60(void); // func_80195C60
void func_80195C80(void); // func_80195C80
void func_80195D84(void); // func_80195D84
void func_80195DDC(void); // func_80195DDC
void func_80195DEC(void); // func_80195DEC
void func_80195E3C(void); // func_80195E3C
void func_80195EE0(void); // func_80195EE0
void func_80196040(void); // func_80196040
void func_8019617C(void); // func_8019617C
void func_801961BC(void); // func_801961BC
void func_801961E8(void); // func_801961E8
void func_80196268(void); // func_80196268
void func_801963E8(void); // func_801963E8
void func_8019641C(void); // func_8019641C
void func_80196448(void); // func_80196448
void func_80196494(void); // func_80196494
void func_801964F8(void); // func_801964F8
void func_801965F0(void); // func_801965F0
void func_801968C4(void); // func_801968C4
void func_80196A00(void); // func_80196A00
void func_80196BC8(void); // func_80196BC8
void func_80196D20(void); // func_80196D20
void func_80196D7C(void); // func_80196D7C
void func_80196DB4(void); // func_80196DB4
void func_80196FEC(void); // func_80196FEC
void func_80197048(void); // func_80197048
void func_80197138(void); // func_80197138
void func_80197164(void); // func_80197164
void func_80197188(void); // func_80197188
void func_801974D0(void); // func_801974D0
void func_80197538(void); // func_80197538
void func_80197714(void); // func_80197714
void func_80197880(void); // func_80197880
void func_801979D8(void); // func_801979D8
void func_80197A54(void); // func_80197A54
void func_80197AA4(void); // func_80197AA4
void func_80197B14(void); // func_80197B14
void func_80197C0C(void); // func_80197C0C
void func_80197C8C(void); // func_80197C8C
void func_80197D24(void); // func_80197D24
void func_80197D4C(void); // func_80197D4C
void func_80197E08(void); // func_80197E08
void func_80197E48(void); // func_80197E48
void func_80197E88(void); // func_80197E88
void func_80197F28(void); // func_80197F28
void func_80197F3C(void); // func_80197F3C
void func_80197F74(void); // func_80197F74
void func_80197FB4(void); // func_80197FB4
void func_801980D0(void); // func_801980D0
void func_8019815C(void); // func_8019815C
void func_8019825C(void); // func_8019825C
void func_80198640(void); // func_80198640
void func_80198CE0(void); // func_80198CE0
void func_801990F4(void); // func_801990F4
void func_80199124(void); // func_80199124
void func_80199198(void); // func_80199198
void func_80199244(void); // func_80199244
void func_80199268(int* param_1); // func_80199268
void func_8019A0BC(void); // func_8019A0BC
void func_8019AA3C(void); // func_8019AA3C
void func_8019AAF0(void); // func_8019AAF0
void func_8019AB40(void); // func_8019AB40
void func_8019AC10(void); // func_8019AC10
void func_8019ACEC(void); // func_8019ACEC
void func_8019ADBC(void); // func_8019ADBC
// UNK_RET func_8019AE40(UNK_ARGS);
// UNK_RET func_8019AEC0(UNK_ARGS);
void func_8019AF00(void); // func_8019AF00
void func_8019AF58(void); // func_8019AF58
void func_8019AFE8(void); // func_8019AFE8
void func_8019B02C(void); // func_8019B02C
void func_8019B074(void); // func_8019B074
void func_8019B144(void); // func_8019B144
void func_8019B378(void); // func_8019B378
void func_8019B38C(void); // func_8019B38C
void func_8019B3D0(void); // func_8019B3D0
void func_8019B4B8(void); // func_8019B4B8
void func_8019B544(void); // func_8019B544
void func_8019B568(void); // func_8019B568
void func_8019B5AC(void); // func_8019B5AC
void func_8019B5EC(void); // func_8019B5EC
void func_8019B618(void); // func_8019B618
void func_8019B654(void); // func_8019B654
void func_8019B6B4(void); // func_8019B6B4
void func_8019BC44(void); // func_8019BC44
void func_8019BE98(void); // func_8019BE98
void func_8019C1D0(void); // func_8019C1D0
void func_8019C268(void); // func_8019C268
void func_8019C2E4(void); // func_8019C2E4
void func_8019C300(void); // func_8019C300
void func_8019C398(void); // func_8019C398
void func_8019C5A0(void); // func_8019C5A0
void func_8019C8D8(void); // func_8019C8D8
void func_8019CD08(void); // func_8019CD08
void func_8019CE34(void); // func_8019CE34
void func_8019CE6C(void); // func_8019CE6C
void func_8019CEBC(void); // func_8019CEBC
void func_8019CF6C(void); // func_8019CF6C
void func_8019CF78(void); // func_8019CF78
void func_8019CF9C(void); // func_8019CF9C
void func_8019CFA8(void); // func_8019CFA8
void func_8019D134(void); // func_8019D134
void func_8019D26C(void); // func_8019D26C
void func_8019D488(void); // func_8019D488
void func_8019D4F8(void); // func_8019D4F8
void func_8019D600(void); // func_8019D600
void func_8019D758(void); // func_8019D758
void func_8019D864(void); // func_8019D864
void func_8019D8B4(void); // func_8019D8B4
void func_8019D8E4(void); // func_8019D8E4
void func_8019DF28(void); // func_8019DF28
void func_8019DF64(void); // func_8019DF64
void func_8019E014(void); // func_8019E014
void func_8019E110(void); // func_8019E110
void func_8019E14C(void); // func_8019E14C
void func_8019E324(void); // func_8019E324
void func_8019E4B0(void); // func_8019E4B0
void func_8019E634(void); // func_8019E634
void func_8019E864(void); // func_8019E864
void func_8019EA40(void); // func_8019EA40
void func_8019EB2C(void); // func_8019EB2C
void func_8019F024(void); // func_8019F024
void func_8019F05C(void); // func_8019F05C
void play_sound(u16 param_1); // func_8019F0C8
void func_8019F128(u16 param_1); // func_8019F128
void func_8019F170(void); // func_8019F170
void func_8019F1C0(UNK_TYPE4 param_1, u16 param_2); // func_8019F1C0
void func_8019F208(void); // func_8019F208
void func_8019F230(void); // func_8019F230
void func_8019F258(void); // func_8019F258
void func_8019F300(void); // func_8019F300
void func_8019F420(void); // func_8019F420
void func_8019F4AC(void); // func_8019F4AC
void func_8019F540(void); // func_8019F540
void func_8019F570(void); // func_8019F570
void func_8019F5AC(void); // func_8019F5AC
void func_8019F638(void); // func_8019F638
void func_8019F780(void); // func_8019F780
void func_8019F7D8(void); // func_8019F7D8
void func_8019F830(void); // func_8019F830
void func_8019F88C(void); // func_8019F88C
void func_8019F900(void); // func_8019F900
void func_8019FA18(void); // func_8019FA18
void func_8019FAD8(Vector3f* param_1, u16 param_2, f32 param_3); // func_8019FAD8
void func_8019FB0C(void); // func_8019FB0C
void func_8019FC20(void); // func_8019FC20
void func_8019FCB8(void); // func_8019FCB8
void func_8019FD90(void); // func_8019FD90
void func_8019FDC8(void); // func_8019FDC8
void func_8019FE1C(void); // func_8019FE1C
void func_8019FE74(void); // func_8019FE74
void func_8019FEDC(void); // func_8019FEDC
void func_8019FF38(void); // func_8019FF38
void func_8019FF9C(void); // func_8019FF9C
void func_801A0048(void); // func_801A0048
void func_801A00EC(void); // func_801A00EC
void func_801A0124(void); // func_801A0124
void func_801A0184(void); // func_801A0184
void func_801A01C4(void); // func_801A01C4
void func_801A0204(void); // func_801A0204
void func_801A0238(void); // func_801A0238
void func_801A026C(void); // func_801A026C
void func_801A0318(void); // func_801A0318
void func_801A046C(void); // func_801A046C
void func_801A0554(void); // func_801A0554
void func_801A05F0(void); // func_801A05F0
void func_801A0654(void); // func_801A0654
void func_801A0810(void); // func_801A0810
void func_801A0868(void); // func_801A0868
void func_801A09D4(void); // func_801A09D4
void func_801A0CB0(void); // func_801A0CB0
void func_801A0E44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801A0E44
void func_801A1290(void); // func_801A1290
void func_801A1348(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801A1348
void func_801A13BC(void); // func_801A13BC
void func_801A153C(void); // func_801A153C
void func_801A17F4(void); // func_801A17F4
void func_801A1904(void); // func_801A1904
void func_801A1A10(void); // func_801A1A10
void func_801A1A8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801A1A8C
void func_801A1D44(void); // func_801A1D44
void func_801A1DB8(void); // func_801A1DB8
void func_801A1E0C(void); // func_801A1E0C
void func_801A1F00(void); // func_801A1F00
void func_801A1F88(void); // func_801A1F88
void func_801A1FB4(void); // func_801A1FB4
void func_801A2090(void); // func_801A2090
void func_801A246C(void); // func_801A246C
void func_801A2544(void); // func_801A2544
void func_801A257C(void); // func_801A257C
void func_801A25E4(void); // func_801A25E4
void func_801A2670(void); // func_801A2670
void func_801A2778(void); // func_801A2778
void func_801A27E8(void); // func_801A27E8
void func_801A281C(void); // func_801A281C
void func_801A29D4(void); // func_801A29D4
void func_801A2BB8(void); // func_801A2BB8
void func_801A2C20(void); // func_801A2C20
void func_801A2C44(void); // func_801A2C44
void func_801A2C88(void); // func_801A2C88
void func_801A2D54(void); // func_801A2D54
void func_801A2DE0(void); // func_801A2DE0
void func_801A2E54(void); // func_801A2E54
void func_801A2ED8(void); // func_801A2ED8
void func_801A2F88(void); // func_801A2F88
void func_801A3000(void); // func_801A3000
void func_801A3038(void); // func_801A3038
void func_801A3098(void); // func_801A3098
void func_801A312C(void); // func_801A312C
void func_801A31EC(void); // func_801A31EC
void func_801A3238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_801A3238
void func_801A32CC(void); // func_801A32CC
void func_801A3590(void); // func_801A3590
void func_801A3950(void); // func_801A3950
void func_801A39F8(void); // func_801A39F8
void func_801A3A7C(void); // func_801A3A7C
void func_801A3AC0(void); // func_801A3AC0
void func_801A3AEC(void); // func_801A3AEC
void func_801A3B48(void); // func_801A3B48
void func_801A3B90(void); // func_801A3B90
void func_801A3CD8(s8 param_1); // func_801A3CD8
void func_801A3CF4(void); // func_801A3CF4
void func_801A3D98(void); // func_801A3D98
void func_801A3E38(void); // func_801A3E38
void func_801A3EC0(void); // func_801A3EC0
void func_801A3F54(void); // func_801A3F54
void func_801A3F6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801A3F6C
void func_801A3FB4(void); // func_801A3FB4
void func_801A400C(void); // func_801A400C
void func_801A4058(void); // func_801A4058
void func_801A41C8(void); // func_801A41C8
void func_801A41F8(void); // func_801A41F8
void func_801A429C(void); // func_801A429C
void func_801A42C8(void); // func_801A42C8
void func_801A4324(void); // func_801A4324
void func_801A4348(void); // func_801A4348
void func_801A4380(void); // func_801A4380
void func_801A4428(void); // func_801A4428
void func_801A44A4(void); // func_801A44A4
void func_801A44C4(void); // func_801A44C4
void func_801A44D4(void); // func_801A44D4
void func_801A46F8(void); // func_801A46F8
void func_801A4748(void); // func_801A4748
void func_801A479C(void); // func_801A479C
void func_801A47DC(void); // func_801A47DC
void func_801A48E0(void); // func_801A48E0
void func_801A4A28(void); // func_801A4A28
void func_801A4B80(void); // func_801A4B80
void func_801A4C30(void); // func_801A4C30
void func_801A4C54(void); // func_801A4C54
void func_801A4D00(void); // func_801A4D00
void func_801A4D50(void); // func_801A4D50
void func_801A4DA4(void); // func_801A4DA4
void func_801A4DF4(void); // func_801A4DF4
void func_801A4E64(void); // func_801A4E64
void func_801A4EB0(void); // func_801A4EB0
void func_801A4EB8(void); // func_801A4EB8
void func_801A4FD8(void); // func_801A4FD8
void func_801A5080(void); // func_801A5080
void func_801A5100(void); // func_801A5100
void func_801A5118(void); // func_801A5118
void func_801A51F0(void); // func_801A51F0
void func_801A5228(void); // func_801A5228
void func_801A5390(void); // func_801A5390
void func_801A53E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_801A53E8
void func_801A541C(void); // func_801A541C
void func_801A5488(void); // func_801A5488
void func_801A54C4(void); // func_801A54C4
void func_801A54D0(void); // func_801A54D0
void func_801A5680(void); // func_801A5680
void func_801A5808(void); // func_801A5808
void func_801A5A10(void); // func_801A5A10
void func_801A5A1C(void); // func_801A5A1C
void func_801A5BD0(void); // func_801A5BD0
void func_801A5C28(void); // func_801A5C28
void func_801A5C8C(void); // func_801A5C8C
void func_801A5CFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_801A5CFC
void func_801A5DDC(void); // func_801A5DDC
void func_801A5F7C(void); // func_801A5F7C
void func_801A6430(void); // func_801A6430
void func_801A65C8(void); // func_801A65C8
void func_801A6D0C(void); // func_801A6D0C
void func_801A7084(void); // func_801A7084
void func_801A7168(void); // func_801A7168
void func_801A7284(void); // func_801A7284
void func_801A72CC(Vector3f* uParm1); // func_801A72CC
void func_801A7328(void); // func_801A7328
void func_801A7484(void); // func_801A7484
void func_801A75E8(void); // func_801A75E8
void func_801A7720(void); // func_801A7720
void func_801A7794(unsigned int param_1, unsigned int param_2, unsigned int param_3); // func_801A7794
void func_801A7828(void); // func_801A7828
void func_801A787C(void); // func_801A787C
void func_801A78E4(void); // func_801A78E4
void func_801A794C(void); // func_801A794C
void func_801A7B10(void); // func_801A7B10
void func_801A7D04(void); // func_801A7D04
void func_801A7D84(void); // func_801A7D84
void func_801A89A8(void); // func_801A89A8
void func_801A89D0(void); // func_801A89D0
void func_801A8A50(void); // func_801A8A50
void func_801A8ABC(void); // func_801A8ABC
void func_801A8BD0(void); // func_801A8BD0
void func_801A8D5C(void); // func_801A8D5C
void func_801A8E90(void); // func_801A8E90
void func_801A9768(void); // func_801A9768
void func_801A982C(void); // func_801A982C
void func_801A99B8(void); // func_801A99B8
void func_801A9A74(void); // func_801A9A74
void func_801A9B10(void); // func_801A9B10
void func_801A9B78(void); // func_801A9B78
void func_801A9BFC(void); // func_801A9BFC
void func_801A9C68(void); // func_801A9C68
void func_801A9D10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_801A9D10
void func_801A9DCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_801A9DCC
void func_801A9EA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE1 param_6); // func_801A9EA4
void func_801A9F4C(void); // func_801A9F4C
void func_801AA020(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801AA020
void func_801AA248(void); // func_801AA248
void func_801AA3E4(void); // func_801AA3E4
void func_801AA520(void); // func_801AA520
void func_801AA610(GlobalContext* ctxt); // func_801AA610
void func_801AA624(GlobalContext* ctxt); // func_801AA624
void func_801AA68C(UNK_TYPE4 ctxt); // func_801AA68C
void nop_801AAAA0(GlobalContext* ctxt); // func_801AAAA0
void Title_UpdateCounters(TitleContext* ctxt); // func_80800000
void Title_RenderView(TitleContext* ctxt, f32 eyeX, f32 eyeY, f32 eyeZ); // func_8080009C
void Title_Render(TitleContext* ctxt); // func_80800134
void Title_Update(TitleContext* ctxt); // func_8080066C
void Title_Fini(TitleContext* ctxt); // func_8080071C
void Title_Init(TitleContext* ctxt); // func_8080074C
void func_80800910(void); // func_80800910
void func_80800930(void); // func_80800930
void func_80800A44(void); // func_80800A44
void func_808013B8(void); // func_808013B8
void func_80801594(void); // func_80801594
void func_80801620(void); // func_80801620
void func_808016E8(void); // func_808016E8
void func_8080194C(void); // func_8080194C
void func_808019FC(void); // func_808019FC
void func_80801A64(void); // func_80801A64
void func_80801AFC(void); // func_80801AFC
void func_80801B28(void); // func_80801B28
void func_80801B4C(void); // func_80801B4C
void Opening_SetupForTitleCutscene(OpeningContext* ctxt); // func_80803DF0
void func_80803EA0(OpeningContext* ctxt); // func_80803EA0
void Opening_Update(OpeningContext* ctxt); // func_80803EC0
void Opening_Fini(OpeningContext* ctxt); // func_80803F0C
void Opening_Init(OpeningContext* ctxt); // func_80803F30
void func_80804010(void); // func_80804010
void func_808041A0(void); // func_808041A0
void func_80804654(void); // func_80804654
void func_808047D8(void); // func_808047D8
void func_8080489C(void); // func_8080489C
void func_80804DAC(void); // func_80804DAC
void func_80804E74(void); // func_80804E74
void func_80804F98(void); // func_80804F98
void func_8080525C(void); // func_8080525C
void func_808052B0(void); // func_808052B0
void func_808054A4(void); // func_808054A4
void func_808055D0(void); // func_808055D0
void func_808058A4(void); // func_808058A4
void func_80805918(void); // func_80805918
void func_80805A58(void); // func_80805A58
void func_80805B30(void); // func_80805B30
void func_80805C1C(void); // func_80805C1C
void func_80806014(void); // func_80806014
void func_80806148(void); // func_80806148
void func_80806310(void); // func_80806310
void func_808067E0(void); // func_808067E0
void func_80806BC8(void); // func_80806BC8
void func_80806CA0(void); // func_80806CA0
void func_80806E84(void); // func_80806E84
void func_80806F30(void); // func_80806F30
void func_808071E4(void); // func_808071E4
void func_80807390(void); // func_80807390
void func_8080742C(void); // func_8080742C
void func_808074B4(void); // func_808074B4
void func_808077AC(void); // func_808077AC
void func_80807940(void); // func_80807940
void func_80807C58(void); // func_80807C58
void func_80808000(void); // func_80808000
void func_80808080(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80808080
void func_80808214(void); // func_80808214
void func_80808D30(void); // func_80808D30
void func_80808F1C(void); // func_80808F1C
void func_80809DF0(void); // func_80809DF0
void func_80809EA0(void); // func_80809EA0
void func_8080A3CC(void); // func_8080A3CC
void func_8080A418(void); // func_8080A418
void func_8080A4A0(void); // func_8080A4A0
void func_8080A6BC(void); // func_8080A6BC
void func_8080A708(void); // func_8080A708
void func_8080BBFC(void); // func_8080BBFC
void func_8080BC20(FileChooseContext* ctxt); // func_8080BC20
void FileChoose_nop8080bc44(void); // func_8080BC44
void FileChoose_nop8080BC4C(FileChooseContext* ctxt); // func_8080BC4C
void func_8080BC58(FileChooseContext* ctxt); // func_8080BC58
void func_8080BDAC(FileChooseContext* ctxt); // func_8080BDAC
void FileChoose_RenderView(FileChooseContext* ctxt, f32 eyeX, f32 eyeY, f32 eyeZ); // func_8080BDDC
void func_8080BE60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_8080BE60
void func_8080C040(FileChooseContext* ctxt); // func_8080C040
void func_8080C228(void); // func_8080C228
void func_8080C29C(FileChooseContext* ctxt); // func_8080C29C
void func_8080C324(void); // func_8080C324
void func_8080C3A8(FileChooseContext* ctxt); // func_8080C3A8
void func_8080D164(void); // func_8080D164
void func_8080D170(void); // func_8080D170
void func_8080D1BC(void); // func_8080D1BC
void func_8080D220(void); // func_8080D220
void func_8080D284(void); // func_8080D284
void func_8080D2EC(FileChooseContext* ctxt); // func_8080D2EC
void func_8080D3D0(FileChooseContext* ctxt); // func_8080D3D0
void func_8080D40C(FileChooseContext* ctxt); // func_8080D40C
void func_8080D6D4(FileChooseContext* ctxt); // func_8080D6D4
void func_8080F25C(void); // func_8080F25C
void func_808108DC(FileChooseContext* ctxt); // func_808108DC
void func_80811CB8(FileChooseContext* ctxt); // func_80811CB8
void func_80812460(void); // func_80812460
void func_80812668(void); // func_80812668
void func_80812760(void); // func_80812760
void func_80812840(void); // func_80812840
void func_80812980(void); // func_80812980
void func_80812A6C(void); // func_80812A6C
void func_80812D44(void); // func_80812D44
void func_80812D94(void); // func_80812D94
void func_80812E94(FileChooseContext* ctxt); // func_80812E94
void func_80812ED0(void); // func_80812ED0
void FileChoose_UpdateAndDrawSkybox(FileChooseContext* ctxt); // func_8081313C
void FileChoose_Update(FileChooseContext* ctxt); // func_80813268
void func_80813908(FileChooseContext* ctxt); // func_80813908
void FileChoose_Fini(FileChooseContext* ctxt); // func_80813C74
void FileChoose_Init(FileChooseContext* ctxt); // func_80813C98
void Daytelop_UpdateState(DaytelopContext* ctxt); // func_80814EB0
void Daytelop_Render(DaytelopContext* ctxt); // func_80814FE8
void Daytelop_Update(DaytelopContext* ctxt); // func_808156B4
void Daytelop_Fini(DaytelopContext* ctxt); // func_8081574C
void Daytelop_nop80815770(DaytelopContext* ctxt); // func_80815770
void Daytelop_LoadGraphics(DaytelopContext* ctxt); // func_8081577C
void Daytelop_Init(DaytelopContext* ctxt); // func_80815820
void func_808160A0(void); // func_808160A0
void func_80817B5C(void); // func_80817B5C
void func_80818904(void); // func_80818904
void func_80818920(void); // func_80818920
void func_808190C4(void); // func_808190C4
void func_80819238(void); // func_80819238
void func_80819F04(void); // func_80819F04
void func_8081B240(void); // func_8081B240
void func_8081B6BC(void); // func_8081B6BC
void func_8081B6EC(void); // func_8081B6EC
void func_8081BCA8(void); // func_8081BCA8
void func_8081C684(void); // func_8081C684
void func_8081D240(void); // func_8081D240
void func_8081D6DC(void); // func_8081D6DC
void func_8081E118(void); // func_8081E118
void func_8081E7D8(void); // func_8081E7D8
void func_8081FB1C(void); // func_8081FB1C
void func_8081FF80(void); // func_8081FF80
void func_808204AC(void); // func_808204AC
void func_80820FA4(void); // func_80820FA4
void func_80821730(void); // func_80821730
void func_80821900(void); // func_80821900
void func_8082192C(void); // func_8082192C
void func_80821958(void); // func_80821958
void func_80821984(void); // func_80821984
void func_80821A04(void); // func_80821A04
void func_80821AD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80821AD4
void func_80821CC4(void); // func_80821CC4
void func_80821D84(void); // func_80821D84
void func_80821F30(void); // func_80821F30
void func_808221DC(void); // func_808221DC
void func_80823350(void); // func_80823350
void func_80824738(void); // func_80824738
void func_808248D0(void); // func_808248D0
void func_80824B90(void); // func_80824B90
void func_808256E4(void); // func_808256E4
void func_8082585C(void); // func_8082585C
void func_808259D4(void); // func_808259D4
void func_80825A50(void); // func_80825A50
void func_80825E28(void); // func_80825E28
void func_808274DC(void); // func_808274DC
void func_80827A8C(void); // func_80827A8C
void func_80827E08(void); // func_80827E08
void func_808283D8(void); // func_808283D8
void func_808286D8(void); // func_808286D8
void func_80828788(void); // func_80828788
void func_8082895C(void); // func_8082895C
void func_8082DA90(void); // func_8082DA90
void func_8082DABC(void); // func_8082DABC
void func_8082DAD4(void); // func_8082DAD4
void func_8082DAFC(void); // func_8082DAFC
void func_8082DB18(void); // func_8082DB18
void func_8082DB3C(void); // func_8082DB3C
void func_8082DB60(void); // func_8082DB60
void func_8082DB90(void); // func_8082DB90
void func_8082DBC0(void); // func_8082DBC0
void func_8082DC28(void); // func_8082DC28
void func_8082DC38(void); // func_8082DC38
void func_8082DC64(void); // func_8082DC64
void func_8082DCA0(void); // func_8082DCA0
void func_8082DD2C(void); // func_8082DD2C
void func_8082DE14(void); // func_8082DE14
void func_8082DE50(void); // func_8082DE50
void func_8082DE88(void); // func_8082DE88
void func_8082DF2C(void); // func_8082DF2C
void func_8082DF48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8082DF48
void func_8082DF8C(void); // func_8082DF8C
void func_8082E00C(void); // func_8082E00C
void func_8082E078(void); // func_8082E078
void func_8082E094(void); // func_8082E094
void func_8082E0CC(void); // func_8082E0CC
void func_8082E0F4(void); // func_8082E0F4
void func_8082E12C(void); // func_8082E12C
void func_8082E188(void); // func_8082E188
void func_8082E1BC(void); // func_8082E1BC
void func_8082E1F0(void); // func_8082E1F0
void func_8082E224(void); // func_8082E224
void func_8082E438(void); // func_8082E438
void func_8082E4A4(void); // func_8082E4A4
void func_8082E514(void); // func_8082E514
void func_8082E55C(void); // func_8082E55C
void func_8082E5A8(void); // func_8082E5A8
void func_8082E5EC(void); // func_8082E5EC
void func_8082E634(void); // func_8082E634
void func_8082E67C(void); // func_8082E67C
void func_8082E6D0(void); // func_8082E6D0
void func_8082E6F8(void); // func_8082E6F8
void func_8082E784(void); // func_8082E784
void func_8082E794(void); // func_8082E794
void func_8082E820(void); // func_8082E820
void func_8082E920(void); // func_8082E920
void func_8082E9C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8082E9C8
void func_8082EA10(void); // func_8082EA10
void func_8082EA38(void); // func_8082EA38
void func_8082EA60(void); // func_8082EA60
void func_8082EA80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8082EA80
void func_8082EAC8(void); // func_8082EAC8
void func_8082EAF0(void); // func_8082EAF0
void func_8082EB18(void); // func_8082EB18
void func_8082EB38(void); // func_8082EB38
void func_8082EC9C(void); // func_8082EC9C
void func_8082ECCC(void); // func_8082ECCC
void func_8082ECE0(void); // func_8082ECE0
void func_8082ED20(void); // func_8082ED20
void func_8082ED94(void); // func_8082ED94
void func_8082EEA4(void); // func_8082EEA4
void func_8082EEE0(void); // func_8082EEE0
void func_8082EF20(void); // func_8082EF20
void func_8082EF54(void); // func_8082EF54
void func_8082EF9C(void); // func_8082EF9C
void func_8082EFE4(void); // func_8082EFE4
void func_8082F02C(void); // func_8082F02C
void func_8082F09C(void); // func_8082F09C
void func_8082F0E4(void); // func_8082F0E4
void func_8082F164(void); // func_8082F164
void func_8082F1AC(void); // func_8082F1AC
void func_8082F43C(void); // func_8082F43C
void func_8082F470(void); // func_8082F470
void func_8082F524(void); // func_8082F524
void func_8082F594(void); // func_8082F594
void func_8082F5A4(void); // func_8082F5A4
void func_8082F5C0(void); // func_8082F5C0
void func_8082F5FC(void); // func_8082F5FC
void func_8082F62C(void); // func_8082F62C
void func_8082F7F4(void); // func_8082F7F4
void func_8082F8A0(void); // func_8082F8A0
void func_8082F8BC(void); // func_8082F8BC
void func_8082F938(void); // func_8082F938
void func_8082FA5C(void); // func_8082FA5C
void func_8082FB68(void); // func_8082FB68
void func_8082FBE8(void); // func_8082FBE8
void func_8082FC24(void); // func_8082FC24
void func_8082FC60(void); // func_8082FC60
void func_8082FC78(void); // func_8082FC78
void func_8082FCC4(void); // func_8082FCC4
void func_8082FD0C(void); // func_8082FD0C
void func_8082FDC4(void); // func_8082FDC4
void func_8082FE0C(void); // func_8082FE0C
void func_808302CC(void); // func_808302CC
void func_808304BC(void); // func_808304BC
void func_808305BC(void); // func_808305BC
void func_808306F8(void); // func_808306F8
void func_808308DC(void); // func_808308DC
void func_808309CC(void); // func_808309CC
void func_80830A58(void); // func_80830A58
void func_80830AE8(void); // func_80830AE8
void func_80830B38(void); // func_80830B38
void func_80830B88(void); // func_80830B88
void func_80830CE8(void); // func_80830CE8
void func_80830D40(void); // func_80830D40
void func_80830DF0(void); // func_80830DF0
void func_80830E30(void); // func_80830E30
void func_80830F9C(void); // func_80830F9C
void func_80830FD4(void); // func_80830FD4
void func_80831010(void); // func_80831010
void func_80831094(void); // func_80831094
void func_80831124(void); // func_80831124
void func_80831194(void); // func_80831194
void func_8083133C(void); // func_8083133C
void func_808313A8(void); // func_808313A8
void func_808313F0(void); // func_808313F0
void func_80831454(void); // func_80831454
void func_80831494(void); // func_80831494
void func_8083172C(void); // func_8083172C
void func_80831760(void); // func_80831760
void func_808317C4(void); // func_808317C4
void func_80831814(void); // func_80831814
void func_808318C0(void); // func_808318C0
void func_80831944(void); // func_80831944
void func_80831990(void); // func_80831990
void func_80831F34(void); // func_80831F34
void func_80832090(void); // func_80832090
void func_8083213C(void); // func_8083213C
void func_8083216C(void); // func_8083216C
void func_808323C0(void); // func_808323C0
void func_80832444(void); // func_80832444
void func_8083249C(void); // func_8083249C
void func_808324EC(void); // func_808324EC
void func_80832558(void); // func_80832558
void func_80832578(void); // func_80832578
void func_80832660(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_80832660
void func_80832754(void); // func_80832754
void func_80832888(void); // func_80832888
void func_80832CAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80832CAC
void func_80832F24(void); // func_80832F24
void func_80832F78(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80832F78
void func_80833058(void); // func_80833058
void func_808331FC(void); // func_808331FC
void func_808332A0(void); // func_808332A0
void func_808333CC(void); // func_808333CC
void func_808334D4(void); // func_808334D4
void func_808335B0(void); // func_808335B0
void func_808335F4(void); // func_808335F4
void func_80833728(void); // func_80833728
void func_8083375C(void); // func_8083375C
void func_80833864(void); // func_80833864
void func_80833998(void); // func_80833998
void func_808339B4(void); // func_808339B4
void func_808339D4(void); // func_808339D4
void func_80833A64(void); // func_80833A64
void func_80833AA0(void); // func_80833AA0
void func_80833B18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE4 param_7); // func_80833B18
void func_808340AC(void); // func_808340AC
void func_808340D4(void); // func_808340D4
void func_80834104(void); // func_80834104
void func_80834140(void); // func_80834140
void func_808341F4(void); // func_808341F4
void func_808344C0(void); // func_808344C0
void func_80834534(void); // func_80834534
void func_8083456C(void); // func_8083456C
void func_808345A8(void); // func_808345A8
void func_808345C8(void); // func_808345C8
void func_80834600(void); // func_80834600
void func_80834CD0(void); // func_80834CD0
void func_80834D50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80834D50
void func_80834DB8(void); // func_80834DB8
void func_80834DFC(void); // func_80834DFC
void func_80835324(void); // func_80835324
void func_808353DC(void); // func_808353DC
void func_80835428(void); // func_80835428
void func_808354A4(void); // func_808354A4
void func_808355D8(void); // func_808355D8
void func_8083562C(void); // func_8083562C
void func_80835BC8(void); // func_80835BC8
void func_80835BF8(void); // func_80835BF8
void func_80835C64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80835C64
void func_80835CD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80835CD8
void func_80835D2C(void); // func_80835D2C
void func_80835D58(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80835D58
void func_80835DF8(void); // func_80835DF8
void func_80835EAC(void); // func_80835EAC
void func_8083604C(void); // func_8083604C
void func_80836258(void); // func_80836258
void func_808365DC(void); // func_808365DC
void func_80836888(void); // func_80836888
void func_8083692C(void); // func_8083692C
void func_80836988(void); // func_80836988
void func_808369F4(void); // func_808369F4
void func_80836A5C(void); // func_80836A5C
void func_80836A98(void); // func_80836A98
void func_80836AD8(void); // func_80836AD8
void func_80836B3C(void); // func_80836B3C
void func_80836C70(void); // func_80836C70
void func_80836D8C(void); // func_80836D8C
void func_80836DC0(void); // func_80836DC0
void func_80836EA0(void); // func_80836EA0
void func_80836F10(void); // func_80836F10
void func_808370D4(void); // func_808370D4
void func_80837134(void); // func_80837134
void func_808373A4(void); // func_808373A4
void func_808373F8(void); // func_808373F8
void func_80837730(void); // func_80837730
void func_8083784C(void); // func_8083784C
void func_808378FC(void); // func_808378FC
void func_8083798C(void); // func_8083798C
void func_808379C0(void); // func_808379C0
void func_80837B60(void); // func_80837B60
void func_80837BD0(void); // func_80837BD0
void func_80837BF8(void); // func_80837BF8
void func_80837C20(void); // func_80837C20
void func_80837C78(void); // func_80837C78
void func_80837CEC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80837CEC
void func_80837DEC(void); // func_80837DEC
void func_808381A0(void); // func_808381A0
void func_808381F8(void); // func_808381F8
void func_8083827C(void); // func_8083827C
void func_8083868C(void); // func_8083868C
void func_80838760(void); // func_80838760
void func_808387A0(void); // func_808387A0
void func_80838830(void); // func_80838830
void func_808388B8(void); // func_808388B8
void func_808389BC(void); // func_808389BC
void func_80838A20(void); // func_80838A20
void func_80838A90(void); // func_80838A90
void func_808391D8(void); // func_808391D8
void func_80839518(void); // func_80839518
void func_808395F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808395F0
void func_808396B8(void); // func_808396B8
void func_80839770(void); // func_80839770
void func_80839800(void); // func_80839800
void func_80839860(void); // func_80839860
void func_80839978(void); // func_80839978
void func_80839A10(void); // func_80839A10
void func_80839A84(void); // func_80839A84
void func_80839B18(void); // func_80839B18
void func_80839CD8(void); // func_80839CD8
void func_80839E3C(void); // func_80839E3C
void func_80839E74(void); // func_80839E74
void func_80839ED0(void); // func_80839ED0
void func_80839F98(void); // func_80839F98
void func_8083A04C(void); // func_8083A04C
void func_8083A0CC(void); // func_8083A0CC
void func_8083A114(void); // func_8083A114
void func_8083A274(void); // func_8083A274
void func_8083A4A4(void); // func_8083A4A4
void func_8083A548(void); // func_8083A548
void func_8083A580(void); // func_8083A580
void func_8083A658(void); // func_8083A658
void func_8083A6C0(void); // func_8083A6C0
void func_8083A794(void); // func_8083A794
void func_8083A844(void); // func_8083A844
void func_8083A878(void); // func_8083A878
void func_8083A98C(void); // func_8083A98C
void func_8083AD04(void); // func_8083AD04
void func_8083AD8C(void); // func_8083AD8C
void func_8083ADB8(void); // func_8083ADB8
void func_8083ADF0(void); // func_8083ADF0
void func_8083AE38(void); // func_8083AE38
void func_8083AECC(void); // func_8083AECC
void func_8083AF30(void); // func_8083AF30
void func_8083AF8C(void); // func_8083AF8C
void func_8083B030(void); // func_8083B030
void func_8083B090(void); // func_8083B090
void func_8083B0E4(void); // func_8083B0E4
void func_8083B1A0(void); // func_8083B1A0
void func_8083B23C(void); // func_8083B23C
void func_8083B29C(void); // func_8083B29C
void func_8083B2E4(void); // func_8083B2E4
void func_8083B32C(void); // func_8083B32C
void func_8083B3B4(void); // func_8083B3B4
void func_8083B73C(void); // func_8083B73C
void func_8083B798(void); // func_8083B798
void func_8083B850(void); // func_8083B850
void func_8083B8D0(void); // func_8083B8D0
void func_8083B930(void); // func_8083B930
void func_8083BB4C(void); // func_8083BB4C
void func_8083BF54(void); // func_8083BF54
void func_8083C62C(void); // func_8083C62C
void func_8083C6E8(void); // func_8083C6E8
void func_8083C85C(void); // func_8083C85C
void func_8083C8E8(void); // func_8083C8E8
void func_8083CB04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_8083CB04
void func_8083CB58(void); // func_8083CB58
void func_8083CBC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_8083CBC4
void func_8083CCB4(void); // func_8083CCB4
void func_8083CF68(void); // func_8083CF68
void func_8083D168(void); // func_8083D168
void func_8083D23C(void); // func_8083D23C
void func_8083D6DC(void); // func_8083D6DC
void func_8083D738(void); // func_8083D738
void func_8083D78C(void); // func_8083D78C
void func_8083D860(void); // func_8083D860
void func_8083DCC4(void); // func_8083DCC4
void func_8083DD1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8083DD1C
void func_8083DEE4(void); // func_8083DEE4
void func_8083DF38(void); // func_8083DF38
void func_8083DFC4(void); // func_8083DFC4
void func_8083E14C(void); // func_8083E14C
void func_8083E234(void); // func_8083E234
void func_8083E28C(void); // func_8083E28C
void func_8083E2F4(void); // func_8083E2F4
void func_8083E354(void); // func_8083E354
void func_8083E404(void); // func_8083E404
void func_8083E514(void); // func_8083E514
void func_8083E758(void); // func_8083E758
void func_8083E7F8(void); // func_8083E7F8
void func_8083E8E0(void); // func_8083E8E0
void func_8083E958(void); // func_8083E958
void func_8083E9C4(void); // func_8083E9C4
void func_8083EA44(void); // func_8083EA44
void func_8083EBD0(void); // func_8083EBD0
void func_8083EE60(void); // func_8083EE60
void func_8083F144(void); // func_8083F144
void func_8083F190(void); // func_8083F190
void func_8083F230(void); // func_8083F230
void func_8083F27C(void); // func_8083F27C
void func_8083F358(void); // func_8083F358
void func_8083F57C(void); // func_8083F57C
void func_8083F828(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8083F828
void func_8083F8A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_8083F8A8
void func_8083FBC4(void); // func_8083FBC4
void func_8083FCF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8083FCF0
void func_8083FD80(void); // func_8083FD80
void func_8083FE38(void); // func_8083FE38
void func_8083FE90(void); // func_8083FE90
void func_8083FEF4(void); // func_8083FEF4
void func_8083FF30(void); // func_8083FF30
void func_8083FFEC(void); // func_8083FFEC
void func_80840094(void); // func_80840094
void func_808400CC(void); // func_808400CC
void func_808401F4(void); // func_808401F4
void func_80840770(void); // func_80840770
void func_80840980(void); // func_80840980
void func_808409A8(void); // func_808409A8
void func_80840A30(void); // func_80840A30
void func_80840CD4(void); // func_80840CD4
void func_80840DEC(void); // func_80840DEC
void func_80840E24(void); // func_80840E24
void func_80840E5C(void); // func_80840E5C
void func_80840EC0(void); // func_80840EC0
void func_80840F34(void); // func_80840F34
void func_80840F90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_80840F90
void func_808411D4(void); // func_808411D4
void func_808412A0(void); // func_808412A0
void func_808412BC(void); // func_808412BC
void func_80841358(void); // func_80841358
void func_80841408(void); // func_80841408
void func_808414E0(void); // func_808414E0
void func_80841528(void); // func_80841528
void func_808415A0(void); // func_808415A0
void func_808415E4(void); // func_808415E4
void func_80841624(void); // func_80841624
void func_80841744(void); // func_80841744
void func_8084182C(void); // func_8084182C
void func_80841A50(void); // func_80841A50
void func_80841AC4(ActorPlayer* this, GlobalContext* ctxt); // func_80841AC4
void func_80842510(void); // func_80842510
void func_808425B4(void); // func_808425B4
void func_808426F0(void); // func_808426F0
void func_808430E0(void); // func_808430E0
void func_80843178(void); // func_80843178
void func_80843EC0(void); // func_80843EC0
void func_808442D8(void); // func_808442D8
void func_808445C4(void); // func_808445C4
void func_808446F4(void); // func_808446F4
void func_80844784(void); // func_80844784
void func_80844D80(void); // func_80844D80
void func_80844EF8(void); // func_80844EF8
void func_808460B8(void); // func_808460B8
void func_808463C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808463C0
void func_80846460(void); // func_80846460
void func_80846528(void); // func_80846528
void func_808470D4(void); // func_808470D4
void func_80847190(void); // func_80847190
void func_8084748C(void); // func_8084748C
void func_808475B4(void); // func_808475B4
void func_808477D0(void); // func_808477D0
void func_80847880(void); // func_80847880
void func_80847994(void); // func_80847994
void func_808479F4(void); // func_808479F4
void func_80847A50(void); // func_80847A50
void func_80847A94(void); // func_80847A94
void func_80847BF0(void); // func_80847BF0
void func_80847E2C(void); // func_80847E2C
void func_80847ED4(void); // func_80847ED4
void func_80847F1C(void); // func_80847F1C
void func_80847FF8(void); // func_80847FF8
void func_80848048(void); // func_80848048
void func_80848094(void); // func_80848094
void func_808481CC(void); // func_808481CC
void func_80848250(void); // func_80848250
void func_80848294(void); // func_80848294
void func_808482E0(void); // func_808482E0
void func_808484CC(void); // func_808484CC
void func_808484F0(void); // func_808484F0
void func_80848570(void); // func_80848570
void func_80848640(void); // func_80848640
void func_80848780(void); // func_80848780
void func_808487B8(void); // func_808487B8
void func_80848808(void); // func_80848808
void func_8084894C(void); // func_8084894C
void func_80848A0C(void); // func_80848A0C
void func_80848AB0(void); // func_80848AB0
void func_80848B6C(void); // func_80848B6C
void func_80848BF4(void); // func_80848BF4
void func_80848E4C(void); // func_80848E4C
void func_80849054(void); // func_80849054
void func_808490B4(void); // func_808490B4
void func_808491B4(void); // func_808491B4
void func_8084923C(void); // func_8084923C
void func_808492C4(void); // func_808492C4
void func_8084933C(void); // func_8084933C
void func_80849570(void); // func_80849570
void func_80849620(void); // func_80849620
void func_808496AC(void); // func_808496AC
void func_808497A0(void); // func_808497A0
void func_80849A9C(void); // func_80849A9C
void func_80849DD0(void); // func_80849DD0
void func_80849FE0(void); // func_80849FE0
void func_8084A26C(void); // func_8084A26C
void func_8084A5C0(void); // func_8084A5C0
void func_8084A794(void); // func_8084A794
void func_8084A884(void); // func_8084A884
void func_8084A8E8(void); // func_8084A8E8
void func_8084AB4C(void); // func_8084AB4C
void func_8084AC84(void); // func_8084AC84
void func_8084AEEC(void); // func_8084AEEC
void func_8084AF9C(void); // func_8084AF9C
void func_8084B0EC(void); // func_8084B0EC
void func_8084B288(void); // func_8084B288
void func_8084B3B8(void); // func_8084B3B8
void func_8084B4A8(void); // func_8084B4A8
void func_8084B5C0(void); // func_8084B5C0
void func_8084BAA4(void); // func_8084BAA4
void func_8084BBF0(void); // func_8084BBF0
void func_8084BC64(void); // func_8084BC64
void func_8084BE40(void); // func_8084BE40
void func_8084BF28(void); // func_8084BF28
void func_8084BFDC(void); // func_8084BFDC
void func_8084C124(void); // func_8084C124
void func_8084C16C(void); // func_8084C16C
void func_8084C6EC(void); // func_8084C6EC
void func_8084C94C(void); // func_8084C94C
void func_8084CA24(void); // func_8084CA24
void func_8084CB58(void); // func_8084CB58
void func_8084CCEC(void); // func_8084CCEC
void func_8084CE84(void); // func_8084CE84
void func_8084D18C(void); // func_8084D18C
void func_8084D2FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE2 param_15, UNK_TYPE4 param_16, UNK_TYPE4 param_17, UNK_TYPE4 param_18, UNK_TYPE4 param_19); // func_8084D2FC
void func_8084D4EC(void); // func_8084D4EC
void func_8084D770(void); // func_8084D770
void func_8084D820(void); // func_8084D820
void func_8084E034(void); // func_8084E034
void func_8084E25C(void); // func_8084E25C
void func_8084E334(void); // func_8084E334
void func_8084E434(void); // func_8084E434
void func_8084E4E4(void); // func_8084E4E4
void func_8084E58C(void); // func_8084E58C
void func_8084E65C(void); // func_8084E65C
void func_8084E724(void); // func_8084E724
void func_8084E980(void); // func_8084E980
void func_8084ED9C(void); // func_8084ED9C
void func_8084EE50(void); // func_8084EE50
void func_8084EF9C(void); // func_8084EF9C
void func_8084F1B8(void); // func_8084F1B8
void func_8084F3DC(void); // func_8084F3DC
void func_8084F4E8(void); // func_8084F4E8
void func_8084FC0C(void); // func_8084FC0C
void func_8084FD7C(void); // func_8084FD7C
void func_8084FE48(void); // func_8084FE48
void func_8084FE7C(void); // func_8084FE7C
void func_808505D0(void); // func_808505D0
void func_80850734(void); // func_80850734
void func_80850854(void); // func_80850854
void func_808508C8(void); // func_808508C8
void func_80850B18(void); // func_80850B18
void func_80850BA8(void); // func_80850BA8
void func_80850BF8(void); // func_80850BF8
void func_80850D20(void); // func_80850D20
void func_80850D68(void); // func_80850D68
void func_808513EC(void); // func_808513EC
void func_80851588(void); // func_80851588
void func_808516B4(void); // func_808516B4
void func_808519FC(void); // func_808519FC
void func_80851B58(void); // func_80851B58
void func_80851BD4(void); // func_80851BD4
void func_80851C40(void); // func_80851C40
void func_80851D30(void); // func_80851D30
void func_80851EAC(void); // func_80851EAC
void func_80851EC8(void); // func_80851EC8
void func_80851F18(void); // func_80851F18
void func_808521E0(void); // func_808521E0
void func_80852290(void); // func_80852290
void func_8085255C(void); // func_8085255C
void func_808525C4(void); // func_808525C4
void func_8085269C(void); // func_8085269C
void func_80852B28(void); // func_80852B28
void func_80852C04(void); // func_80852C04
void func_80852FD4(void); // func_80852FD4
void func_808530E0(void); // func_808530E0
void func_80853194(void); // func_80853194
void func_808534C0(void); // func_808534C0
void func_80853754(void); // func_80853754
void func_80853850(void); // func_80853850
void func_80853A5C(void); // func_80853A5C
void func_80853CC0(void); // func_80853CC0
void func_80853D68(void); // func_80853D68
void func_80854010(void); // func_80854010
void func_808540A0(void); // func_808540A0
void func_80854118(void); // func_80854118
void func_8085421C(void); // func_8085421C
void func_8085437C(void); // func_8085437C
void func_8085439C(void); // func_8085439C
void func_80854430(void); // func_80854430
void func_80854614(void); // func_80854614
void func_808546D0(void); // func_808546D0
void func_80854800(void); // func_80854800
void func_808548B8(void); // func_808548B8
void func_80854C70(void); // func_80854C70
void func_80854CD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13); // func_80854CD0
void func_80854EFC(void); // func_80854EFC
void func_808550D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808550D0
void func_80855218(void); // func_80855218
void func_808553F4(void); // func_808553F4
void func_80855818(void); // func_80855818
void func_80855A7C(void); // func_80855A7C
void func_80855AF4(void); // func_80855AF4
void func_80855B9C(void); // func_80855B9C
void func_80855C28(void); // func_80855C28
void func_80855E08(void); // func_80855E08
void func_80855F9C(void); // func_80855F9C
void func_80856000(void); // func_80856000
void func_80856074(void); // func_80856074
void func_80856110(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_80856110
void func_808561B0(void); // func_808561B0
void func_808566C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_808566C0
void func_8085687C(void); // func_8085687C
void func_80856888(void); // func_80856888
void func_80856918(void); // func_80856918
void func_808573A4(void); // func_808573A4
void func_80857640(void); // func_80857640
void func_808576BC(void); // func_808576BC
void func_808577E0(void); // func_808577E0
void func_80857950(void); // func_80857950
void func_80857A44(void); // func_80857A44
void func_80857AEC(void); // func_80857AEC
void func_80857BE8(void); // func_80857BE8
void func_80858C84(void); // func_80858C84
void func_80858CC8(void); // func_80858CC8
void func_80858D48(void); // func_80858D48
void func_80858DB4(void); // func_80858DB4
void func_80858DDC(void); // func_80858DDC
void func_80858DFC(void); // func_80858DFC
void func_80858E40(void); // func_80858E40
void func_80858E60(void); // func_80858E60
void func_80858E80(void); // func_80858E80
void func_80858EA0(void); // func_80858EA0
void func_80858EC0(void); // func_80858EC0
void func_80858EFC(void); // func_80858EFC
void func_80858F1C(void); // func_80858F1C
void func_80858F3C(void); // func_80858F3C
void func_80858F5C(void); // func_80858F5C
void func_80858F7C(void); // func_80858F7C
void func_80858F9C(void); // func_80858F9C
void func_80858FBC(void); // func_80858FBC
void func_80858FE8(void); // func_80858FE8
void func_80859028(void); // func_80859028
void func_80859168(void); // func_80859168
void func_808591BC(void); // func_808591BC
void func_80859210(void); // func_80859210
void func_80859248(void); // func_80859248
void func_8085929C(void); // func_8085929C
void func_80859300(void); // func_80859300
void func_80859414(void); // func_80859414
void func_808594D0(void); // func_808594D0
void func_808595B8(void); // func_808595B8
void func_8085968C(void); // func_8085968C
void func_80859708(void); // func_80859708
void func_8085978C(void); // func_8085978C
void func_80859890(void); // func_80859890
void func_80859990(void); // func_80859990
void func_808599DC(void); // func_808599DC
void func_80859A10(void); // func_80859A10
void func_80859A44(void); // func_80859A44
void func_80859AD0(void); // func_80859AD0
void func_80859AF8(void); // func_80859AF8
void func_80859B28(void); // func_80859B28
void func_80859B54(void); // func_80859B54
void func_80859BA8(void); // func_80859BA8
void func_80859C60(void); // func_80859C60
void func_80859CA0(void); // func_80859CA0
void func_80859CE0(void); // func_80859CE0
void func_80859CFC(void); // func_80859CFC
void func_80859D44(void); // func_80859D44
void func_80859D70(void); // func_80859D70
void func_80859EBC(void); // func_80859EBC
void func_80859F4C(void); // func_80859F4C
void func_80859FCC(void); // func_80859FCC
void func_80859FF4(void); // func_80859FF4
void func_8085A04C(void); // func_8085A04C
void func_8085A120(void); // func_8085A120
void func_8085A144(void); // func_8085A144
void func_8085A19C(void); // func_8085A19C
void func_8085A1D4(void); // func_8085A1D4
void func_8085A24C(void); // func_8085A24C
void func_8085A2AC(void); // func_8085A2AC
void func_8085A330(void); // func_8085A330
void func_8085A364(void); // func_8085A364
void func_8085A40C(void); // func_8085A40C
void func_8085A4A4(void); // func_8085A4A4
void func_8085A530(void); // func_8085A530
void func_8085A5DC(void); // func_8085A5DC
void func_8085A66C(void); // func_8085A66C
void func_8085A6C0(void); // func_8085A6C0
void func_8085A710(void); // func_8085A710
void func_8085A768(void); // func_8085A768
void func_8085A7C0(void); // func_8085A7C0
void func_8085A8C4(void); // func_8085A8C4
void func_8085A940(void); // func_8085A940
void func_8085AA10(void); // func_8085AA10
void func_8085AA60(void); // func_8085AA60
void func_8085AA84(void); // func_8085AA84
void func_8085AACC(void); // func_8085AACC
void func_8085AB58(void); // func_8085AB58
void func_8085ABA8(void); // func_8085ABA8
void func_8085AC9C(void); // func_8085AC9C
void func_8085AD5C(void); // func_8085AD5C
void func_8085ADA0(void); // func_8085ADA0
void func_8085B08C(void); // func_8085B08C
void func_8085B134(void); // func_8085B134
void func_8085B170(void); // func_8085B170
void func_8085B1F0(void); // func_8085B1F0
void func_8085B28C(void); // func_8085B28C
void func_8085B384(void); // func_8085B384
void func_8085B3E0(void); // func_8085B3E0
void func_8085B460(void); // func_8085B460
void func_8085B74C(void); // func_8085B74C
void func_8085B820(void); // func_8085B820
void func_8085B854(void); // func_8085B854
void func_8085B930(void); // func_8085B930
void D_8085DA08(void); // func_8085DA08
void func_80862B70(void); // func_80862B70
void func_80862CBC(void); // func_80862CBC
void func_80862EDC(void); // func_80862EDC
void func_80863048(void); // func_80863048
void EnTest_Init(ActorEnTest* this, GlobalContext* ctxt); // func_80863188
void EnTest_Fini(ActorEnTest* this, GlobalContext* ctxt); // func_80863310
void EnTest_Main(ActorEnTest* this, GlobalContext* ctxt); // func_8086333C
void func_808634B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808634B8
void EnTest_Draw(ActorEnTest* this, GlobalContext* ctxt); // func_808636A8
void func_80863870(void); // func_80863870
void func_8086387C(void); // func_8086387C
void func_80863920(void); // func_80863920
void func_80863940(void); // func_80863940
void func_80863950(void); // func_80863950
void func_808639B0(void); // func_808639B0
void func_80863A10(void); // func_80863A10
void func_80863AAC(void); // func_80863AAC
void func_80863B4C(void); // func_80863B4C
void func_80863C08(void); // func_80863C08
void func_80863C6C(void); // func_80863C6C
void func_80863D28(void); // func_80863D28
void func_80863D60(void); // func_80863D60
void func_80863DC8(void); // func_80863DC8
void func_80863E48(void); // func_80863E48
void func_80863EC8(void); // func_80863EC8
void func_80863F94(void); // func_80863F94
void func_80864034(void); // func_80864034
void func_8086406C(void); // func_8086406C
void func_808640A4(void); // func_808640A4
void func_80864108(void); // func_80864108
void func_80864168(void); // func_80864168
void func_80864210(void); // func_80864210
void func_8086425C(void); // func_8086425C
void func_808642D4(void); // func_808642D4
void func_80864320(void); // func_80864320
void func_8086436C(void); // func_8086436C
void func_808643B8(void); // func_808643B8
void func_8086444C(void); // func_8086444C
void func_808644A4(void); // func_808644A4
void func_80864558(void); // func_80864558
void func_808645A4(void); // func_808645A4
void func_80864658(void); // func_80864658
void func_808646A4(void); // func_808646A4
void func_808646E4(void); // func_808646E4
void func_808646F4(void); // func_808646F4
void func_8086472C(void); // func_8086472C
void func_80864744(void); // func_80864744
void func_80864760(void); // func_80864760
void func_80864774(void); // func_80864774
void func_808648F8(void); // func_808648F8
void func_808649A4(void); // func_808649A4
void func_808649C8(void); // func_808649C8
void func_80865370(void); // func_80865370
void func_80865380(void); // func_80865380
void func_80865390(void); // func_80865390
void func_808654C4(void); // func_808654C4
void func_808657A0(void); // func_808657A0
void func_808657E8(void); // func_808657E8
void func_80865990(void); // func_80865990
void func_80865BBC(void); // func_80865BBC
void func_80865BF8(void); // func_80865BF8
void func_80865C74(void); // func_80865C74
void func_80865F38(void); // func_80865F38
void func_80866398(void); // func_80866398
void func_80866800(void); // func_80866800
void func_808669E0(void); // func_808669E0
void func_80866A5C(void); // func_80866A5C
void func_80866B20(void); // func_80866B20
void func_80866F94(void); // func_80866F94
void func_8086704C(void); // func_8086704C
void func_80867080(void); // func_80867080
void func_808670F0(void); // func_808670F0
void func_80867144(void); // func_80867144
void func_8086732C(void); // func_8086732C
void func_80867350(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80867350
void func_808674B0(void); // func_808674B0
void func_80867BD0(void); // func_80867BD0
void func_80867BDC(void); // func_80867BDC
void func_80867C14(void); // func_80867C14
void func_80867C8C(void); // func_80867C8C
void func_80867FBC(void); // func_80867FBC
void func_80867FE4(void); // func_80867FE4
void func_8086800C(void); // func_8086800C
void func_808680AC(void); // func_808680AC
void func_808685FC(void); // func_808685FC
void func_80868630(void); // func_80868630
void func_80868734(void); // func_80868734
void func_808687E8(void); // func_808687E8
void func_80868944(void); // func_80868944
void func_808689E8(void); // func_808689E8
void func_80868A6C(void); // func_80868A6C
void func_80868AFC(void); // func_80868AFC
void func_80868B74(void); // func_80868B74
void func_80868CC8(void); // func_80868CC8
void func_80869020(void); // func_80869020
void func_808692E0(void); // func_808692E0
void func_808694A0(void); // func_808694A0
void func_80869600(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80869600
void func_80869850(void); // func_80869850
void func_80869874(void); // func_80869874
void func_808698B4(void); // func_808698B4
void func_808698F4(void); // func_808698F4
void func_80869D90(void); // func_80869D90
void func_80869F90(void); // func_80869F90
void func_80869FBC(void); // func_80869FBC
void func_8086A024(void); // func_8086A024
void func_8086A068(void); // func_8086A068
void func_8086A0F4(void); // func_8086A0F4
void func_8086A1A0(void); // func_8086A1A0
void func_8086A238(void); // func_8086A238
void func_8086A2CC(void); // func_8086A2CC
void func_8086A428(void); // func_8086A428
void func_8086A4E4(void); // func_8086A4E4
void func_8086A554(void); // func_8086A554
void func_8086A6B0(void); // func_8086A6B0
void func_8086A724(void); // func_8086A724
void func_8086A80C(void); // func_8086A80C
void func_8086A878(void); // func_8086A878
void func_8086A8C0(void); // func_8086A8C0
void func_8086A964(void); // func_8086A964
void func_8086AA60(void); // func_8086AA60
void func_8086AAA8(void); // func_8086AAA8
void func_8086AB04(void); // func_8086AB04
void func_8086AB68(void); // func_8086AB68
void func_8086AC0C(void); // func_8086AC0C
void func_8086AD34(void); // func_8086AD34
void func_8086AE48(void); // func_8086AE48
void func_8086AEC8(void); // func_8086AEC8
void func_8086AFC8(void); // func_8086AFC8
void func_8086B140(void); // func_8086B140
void func_8086B478(void); // func_8086B478
void func_8086B570(void); // func_8086B570
void func_8086B66C(void); // func_8086B66C
void func_8086B794(void); // func_8086B794
void func_8086B864(void); // func_8086B864
void func_8086B8CC(void); // func_8086B8CC
void func_8086B9D0(void); // func_8086B9D0
void func_8086BA6C(void); // func_8086BA6C
void func_8086BB4C(void); // func_8086BB4C
void func_8086BB9C(void); // func_8086BB9C
void func_8086BBE0(void); // func_8086BBE0
void func_8086BDA8(void); // func_8086BDA8
void func_8086BE60(void); // func_8086BE60
void func_8086BEEC(void); // func_8086BEEC
void func_8086BF90(void); // func_8086BF90
void func_8086C088(void); // func_8086C088
void func_8086C0CC(void); // func_8086C0CC
void func_8086C1AC(void); // func_8086C1AC
void func_8086C274(void); // func_8086C274
void func_8086C4B8(void); // func_8086C4B8
void func_8086C5A8(void); // func_8086C5A8
void func_8086C618(void); // func_8086C618
void func_8086C6D0(void); // func_8086C6D0
void func_8086C72C(void); // func_8086C72C
void func_8086C7C8(void); // func_8086C7C8
void func_8086C81C(void); // func_8086C81C
void func_8086C94C(void); // func_8086C94C
void func_8086C99C(void); // func_8086C99C
void func_8086CB4C(void); // func_8086CB4C
void func_8086CC04(void); // func_8086CC04
void func_8086CC84(void); // func_8086CC84
void func_8086CD04(void); // func_8086CD04
void func_8086CD6C(void); // func_8086CD6C
void func_8086CEB4(void); // func_8086CEB4
void func_8086CEF0(void); // func_8086CEF0
void func_8086D084(void); // func_8086D084
void func_8086D140(void); // func_8086D140
void func_8086D1E8(void); // func_8086D1E8
void func_8086D230(void); // func_8086D230
void func_8086D4C0(void); // func_8086D4C0
void func_8086D730(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8086D730
void func_8086D898(void); // func_8086D898
void func_8086DE20(void); // func_8086DE20
void func_8086E058(void); // func_8086E058
void func_8086E084(void); // func_8086E084
void func_8086E0F0(void); // func_8086E0F0
void func_8086E168(void); // func_8086E168
void func_8086E214(void); // func_8086E214
void func_8086E27C(void); // func_8086E27C
void func_8086E2C0(void); // func_8086E2C0
void func_8086E378(void); // func_8086E378
void func_8086E3B8(void); // func_8086E3B8
void func_8086E4FC(void); // func_8086E4FC
void func_8086E52C(void); // func_8086E52C
void func_8086E5E8(void); // func_8086E5E8
void func_8086E658(void); // func_8086E658
void func_8086E7A8(void); // func_8086E7A8
void func_8086E7E8(void); // func_8086E7E8
void func_8086E8E8(void); // func_8086E8E8
void func_8086E948(void); // func_8086E948
void func_8086EAE0(void); // func_8086EAE0
void func_8086EC00(void); // func_8086EC00
void func_8086EE8C(void); // func_8086EE8C
void func_8086EF14(void); // func_8086EF14
void func_8086EF90(void); // func_8086EF90
void func_8086EFE8(void); // func_8086EFE8
void func_8086F2FC(void); // func_8086F2FC
void func_8086F434(void); // func_8086F434
void func_8086F4B0(void); // func_8086F4B0
void func_8086F4F4(void); // func_8086F4F4
void func_8086F57C(void); // func_8086F57C
void func_8086F694(void); // func_8086F694
void func_8086F8FC(void); // func_8086F8FC
void func_8086FCA4(void); // func_8086FCA4
void func_8086FDE0(void); // func_8086FDE0
void func_808700C0(void); // func_808700C0
void func_80870254(void); // func_80870254
void func_808704DC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808704DC
void func_808705C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808705C8
void func_808706E0(void); // func_808706E0
void EnBom_Init(ActorEnBom* this, GlobalContext* ctxt); // func_80870DB0
void EnBom_Fini(ActorEnBom* this, GlobalContext* ctxt); // func_80870FF8
void func_80871058(void); // func_80871058
void func_808714D4(void); // func_808714D4
void func_808715B8(void); // func_808715B8
void EnBom_Main(ActorEnBom* this, GlobalContext* ctxt); // func_808719A8
void EnBom_Draw(ActorEnBom* this, GlobalContext* ctxt); // func_808722F4
void func_80872648(GlobalContext* ctxt, Vector3f* pzParm2); // func_80872648
void func_808726DC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808726DC
void func_80872BC0(void); // func_80872BC0
void func_80874810(void); // func_80874810
void func_80874A28(void); // func_80874A28
void func_80874A88(void); // func_80874A88
void func_80874B04(void); // func_80874B04
void func_80874B88(void); // func_80874B88
void func_80874BE4(void); // func_80874BE4
void func_80874D1C(void); // func_80874D1C
void func_80874DE8(void); // func_80874DE8
void func_80874F14(void); // func_80874F14
void func_80874FD8(void); // func_80874FD8
void func_80875014(void); // func_80875014
void func_80875054(void); // func_80875054
void func_808750B8(void); // func_808750B8
void func_80875108(void); // func_80875108
void func_808751C4(void); // func_808751C4
void func_8087520C(void); // func_8087520C
void func_80875248(void); // func_80875248
void func_808752CC(void); // func_808752CC
void func_808753F0(void); // func_808753F0
void func_80875484(void); // func_80875484
void func_80875518(void); // func_80875518
void func_8087556C(void); // func_8087556C
void func_808755A8(void); // func_808755A8
void func_80875638(void); // func_80875638
void func_808756AC(void); // func_808756AC
void func_8087571C(void); // func_8087571C
void func_808758C8(void); // func_808758C8
void func_80875910(void); // func_80875910
void func_8087596C(void); // func_8087596C
void func_808759B8(void); // func_808759B8
void func_80875A0C(void); // func_80875A0C
void func_80875A74(void); // func_80875A74
void func_80875CF4(void); // func_80875CF4
void func_80875F04(void); // func_80875F04
void func_808760A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808760A4
void func_80876118(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80876118
void func_80876268(void); // func_80876268
void func_80876670(void); // func_80876670
void func_808768D0(void); // func_808768D0
void func_80876930(void); // func_80876930
void func_80876B08(void); // func_80876B08
void func_80876BD0(void); // func_80876BD0
void func_80876CAC(void); // func_80876CAC
void func_80876D28(void); // func_80876D28
void func_80876DC4(void); // func_80876DC4
void func_8087721C(void); // func_8087721C
void func_80877278(void); // func_80877278
void func_808773C4(void); // func_808773C4
void func_80877424(void); // func_80877424
void func_80877494(void); // func_80877494
void func_80877500(void); // func_80877500
void func_808777A8(void); // func_808777A8
void func_8087784C(void); // func_8087784C
void func_80877D50(void); // func_80877D50
void func_80877D90(void); // func_80877D90
void func_80877DE0(void); // func_80877DE0
void func_80877E60(void); // func_80877E60
void func_80878354(void); // func_80878354
void func_80878424(void); // func_80878424
void func_80878594(void); // func_80878594
void func_808785B0(void); // func_808785B0
void func_8087864C(void); // func_8087864C
void func_808786C8(void); // func_808786C8
void func_80878724(void); // func_80878724
void func_808787B0(void); // func_808787B0
void func_80878910(void); // func_80878910
void func_80878C4C(void); // func_80878C4C
void func_80878E44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80878E44
void func_80878EB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80878EB4
void func_80879008(void); // func_80879008
void EnFirefly_Init(ActorEnFirefly* this, UNK_TYPE4 ctxt); // func_808796F0
void EnFirefly_Fini(ActorEnFirefly* this, GlobalContext* ctxt); // func_80879898
void func_808798C4(ActorEnFirefly* this, GlobalContext* ctxt); // func_808798C4
void func_80879930(ActorEnFirefly* this); // func_80879930
void func_80879950(void); // func_80879950
void func_8087997C(void); // func_8087997C
void func_80879A98(void); // func_80879A98
void func_80879C14(ActorEnFirefly* this); // func_80879C14
void func_80879CC0(void); // func_80879CC0
void func_80879F28(ActorEnFirefly* this, GlobalContext* ctxt); // func_80879F28
void func_8087A110(void); // func_8087A110
void func_8087A1C8(void); // func_8087A1C8
void func_8087A1EC(void); // func_8087A1EC
void func_8087A268(void); // func_8087A268
void func_8087A2D8(void); // func_8087A2D8
void func_8087A50C(ActorEnFirefly* this); // func_8087A50C
void func_8087A548(void); // func_8087A548
void func_8087A5DC(void); // func_8087A5DC
void func_8087A60C(void); // func_8087A60C
void func_8087A774(ActorEnFirefly* this); // func_8087A774
void func_8087A818(void); // func_8087A818
void func_8087A8FC(void); // func_8087A8FC
void func_8087A920(void); // func_8087A920
void func_8087A9E0(void); // func_8087A9E0
void func_8087AA1C(void); // func_8087AA1C
void func_8087AAF4(ActorEnFirefly* this, GlobalContext* ctxt); // func_8087AAF4
void EnFirefly_Main(ActorEnFirefly* this, GlobalContext* ctxt); // func_8087AC0C
void func_8087AF48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8087AF48
void func_8087AF98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8087AF98
void EnFirefly_Draw(ActorEnFirefly* this, GlobalContext* ctxt); // func_8087B320
void func_8087B730(void); // func_8087B730
void func_8087B784(void); // func_8087B784
void func_8087B7C0(void); // func_8087B7C0
void func_8087C0AC(void); // func_8087C0AC
void func_8087C178(void); // func_8087C178
void func_8087C1C0(void); // func_8087C1C0
void func_8087C208(void); // func_8087C208
void func_8087C288(void); // func_8087C288
void func_8087C2B8(void); // func_8087C2B8
void func_8087C38C(void); // func_8087C38C
void func_8087C43C(void); // func_8087C43C
void func_8087C590(void); // func_8087C590
void func_8087C8B8(void); // func_8087C8B8
void func_8087C8D0(void); // func_8087C8D0
void func_8087C8E0(void); // func_8087C8E0
void func_8087C9D4(void); // func_8087C9D4
void func_8087C9EC(void); // func_8087C9EC
void func_8087C9F8(void); // func_8087C9F8
void func_8087CA04(void); // func_8087CA04
void func_8087CA14(void); // func_8087CA14
void func_8087D540(void); // func_8087D540
void func_8087D69C(void); // func_8087D69C
void func_8087D70C(void); // func_8087D70C
void func_8087D75C(void); // func_8087D75C
void func_8087D814(void); // func_8087D814
void func_8087D988(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); // func_8087D988
void func_8087DDEC(void); // func_8087DDEC
void func_8087DE28(void); // func_8087DE28
void func_8087DF64(void); // func_8087DF64
void func_8087E080(void); // func_8087E080
void func_8087E0A4(void); // func_8087E0A4
void func_8087E18C(void); // func_8087E18C
void func_8087E2A8(void); // func_8087E2A8
void func_8087E350(void); // func_8087E350
void func_8087E564(void); // func_8087E564
void func_8087E5B4(void); // func_8087E5B4
void func_8087E5D8(void); // func_8087E5D8
void func_8087E684(void); // func_8087E684
void func_8087E6D8(void); // func_8087E6D8
void func_8087E92C(void); // func_8087E92C
void func_8087E9D0(void); // func_8087E9D0
void func_8087EA1C(void); // func_8087EA1C
void func_8087EB54(void); // func_8087EB54
void func_8087EB78(void); // func_8087EB78
void func_8087EC20(void); // func_8087EC20
void func_8087EC78(void); // func_8087EC78
void func_8087ED10(void); // func_8087ED10
void func_8087EEC4(void); // func_8087EEC4
void func_8087F078(void); // func_8087F078
void func_8087F1FC(void); // func_8087F1FC
void func_8087F39C(void); // func_8087F39C
void func_8087F590(void); // func_8087F590
void func_8087F5B4(void); // func_8087F5B4
void func_8087F658(void); // func_8087F658
void func_8087F9A0(void); // func_8087F9A0
void func_8087F9C4(void); // func_8087F9C4
void func_8087FB08(void); // func_8087FB08
void func_8087FB14(void); // func_8087FB14
void func_8087FD94(void); // func_8087FD94
void func_8087FDB8(void); // func_8087FDB8
void func_8087FF08(void); // func_8087FF08
void func_8087FF14(void); // func_8087FF14
void func_808801A8(void); // func_808801A8
void func_808801F8(void); // func_808801F8
void func_808802D0(void); // func_808802D0
void func_808804A4(void); // func_808804A4
void func_808804CC(void); // func_808804CC
void func_80880500(void); // func_80880500
void func_80880534(void); // func_80880534
void func_808806DC(void); // func_808806DC
void func_80880844(void); // func_80880844
void func_80880978(void); // func_80880978
void func_80880D50(void); // func_80880D50
void func_80880DA8(void); // func_80880DA8
void func_80880E00(void); // func_80880E00
void func_80881128(void); // func_80881128
void func_8088126C(void); // func_8088126C
void func_80881290(void); // func_80881290
void func_80881398(void); // func_80881398
void func_8088159C(void); // func_8088159C
void func_80881634(void); // func_80881634
void func_8088168C(void); // func_8088168C
void func_808819D8(void); // func_808819D8
void func_80881BDC(void); // func_80881BDC
void func_80881C54(void); // func_80881C54
void func_80881DA4(void); // func_80881DA4
void func_80881DC8(void); // func_80881DC8
void func_80881F10(void); // func_80881F10
void func_80881F48(void); // func_80881F48
void func_808821C8(void); // func_808821C8
void func_808822CC(void); // func_808822CC
void func_8088247C(void); // func_8088247C
void func_80882564(void); // func_80882564
void func_808826B4(void); // func_808826B4
void func_80882820(void); // func_80882820
void func_808829D0(void); // func_808829D0
void func_808829F4(void); // func_808829F4
void func_80882A44(void); // func_80882A44
void func_80882B9C(void); // func_80882B9C
void func_80882D8C(void); // func_80882D8C
void func_80882DC0(void); // func_80882DC0
void func_80883104(void); // func_80883104
void func_80883308(void); // func_80883308
void func_80883B70(void); // func_80883B70
void func_80883BEC(void); // func_80883BEC
void func_80883CB0(void); // func_80883CB0
void func_80883D64(void); // func_80883D64
void func_80883DE0(void); // func_80883DE0
void func_80883E10(void); // func_80883E10
void func_80883EA0(void); // func_80883EA0
void func_80883F18(void); // func_80883F18
void func_80883F98(void); // func_80883F98
void func_80884010(void); // func_80884010
void func_808840C4(void); // func_808840C4
void func_80884194(void); // func_80884194
void func_8088424C(void); // func_8088424C
void func_80884314(void); // func_80884314
void func_808843B4(void); // func_808843B4
void func_80884444(void); // func_80884444
void func_808844E0(void); // func_808844E0
void func_80884564(void); // func_80884564
void func_80884604(void); // func_80884604
void func_808846B4(void); // func_808846B4
void func_808846DC(void); // func_808846DC
void func_808846F0(void); // func_808846F0
void func_80884718(void); // func_80884718
void func_80884868(void); // func_80884868
void func_808848C8(void); // func_808848C8
void func_80884994(void); // func_80884994
void func_80884A40(void); // func_80884A40
void func_80884D04(void); // func_80884D04
void func_80884E0C(void); // func_80884E0C
void func_80885060(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80885060
void func_808850DC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808850DC
void func_80885220(void); // func_80885220
void func_808853E0(void); // func_808853E0
void func_8088598C(void); // func_8088598C
void func_80885A80(void); // func_80885A80
void func_80885AF4(void); // func_80885AF4
void func_80885B4C(void); // func_80885B4C
void func_80885C90(void); // func_80885C90
void func_80885DA4(void); // func_80885DA4
void func_80886C00(void); // func_80886C00
void func_80886DC4(void); // func_80886DC4
void func_80886FA8(void); // func_80886FA8
void func_808870A4(void); // func_808870A4
void func_808871A0(void); // func_808871A0
void func_80887270(void); // func_80887270
void func_808872A4(void); // func_808872A4
void func_80887D20(void); // func_80887D20
void func_80887D60(void); // func_80887D60
void func_80887E64(void); // func_80887E64
void func_80887EBC(void); // func_80887EBC
void func_80887F58(void); // func_80887F58
void func_80888C48(void); // func_80888C48
void func_80888D18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80888D18
void func_80888D78(void); // func_80888D78
void func_8088A240(void); // func_8088A240
void func_8088A464(void); // func_8088A464
void func_8088A514(void); // func_8088A514
void func_8088A594(void); // func_8088A594
void func_8088A7D8(void); // func_8088A7D8
void func_8088A894(void); // func_8088A894
void func_8088AA98(void); // func_8088AA98
void func_8088ACE0(void); // func_8088ACE0
void func_8088B630(void); // func_8088B630
void func_8088B6B0(void); // func_8088B6B0
void func_8088B720(void); // func_8088B720
void func_8088B88C(void); // func_8088B88C
void func_8088BA34(void); // func_8088BA34
void func_8088C510(void); // func_8088C510
void func_8088C51C(void); // func_8088C51C
void func_8088C804(void); // func_8088C804
void func_8088C858(void); // func_8088C858
void func_8088C920(void); // func_8088C920
void func_8088C9CC(void); // func_8088C9CC
void func_8088CBAC(void); // func_8088CBAC
void func_8088CC48(void); // func_8088CC48
void func_8088CD3C(void); // func_8088CD3C
void func_8088CDAC(void); // func_8088CDAC
void func_8088D39C(void); // func_8088D39C
void func_8088D3EC(void); // func_8088D3EC
void func_8088D470(void); // func_8088D470
void func_8088D504(void); // func_8088D504
void func_8088D5A0(void); // func_8088D5A0
void func_8088D660(void); // func_8088D660
void func_8088D7F8(void); // func_8088D7F8
void func_8088D864(void); // func_8088D864
void func_8088D8D0(void); // func_8088D8D0
void func_8088D9BC(void); // func_8088D9BC
void func_8088DB4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8088DB4C
void func_8088DCA4(void); // func_8088DCA4
void func_8088DD34(void); // func_8088DD34
void func_8088E018(void); // func_8088E018
void func_8088E0E0(void); // func_8088E0E0
void func_8088E0F0(void); // func_8088E0F0
void func_8088E304(void); // func_8088E304
void func_8088E484(void); // func_8088E484
void func_8088E5A8(void); // func_8088E5A8
void func_8088E60C(void); // func_8088E60C
void func_8088E850(void); // func_8088E850
void func_8088EF18(void); // func_8088EF18
void func_8088EFA4(void); // func_8088EFA4
void func_8088F214(void); // func_8088F214
void func_8088F5F4(void); // func_8088F5F4
void func_8088F9E4(void); // func_8088F9E4
void func_8088FA38(void); // func_8088FA38
void func_8088FC34(void); // func_8088FC34
void func_8088FD04(void); // func_8088FD04
void func_8088FDCC(void); // func_8088FDCC
void func_8088FE64(void); // func_8088FE64
void func_8089010C(void); // func_8089010C
void func_80890438(void); // func_80890438
void func_80890494(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80890494
void func_808905B8(void); // func_808905B8
void func_808908D0(void); // func_808908D0
void func_80891060(void); // func_80891060
void func_808912E8(void); // func_808912E8
void func_80891320(void); // func_80891320
void func_808916B0(void); // func_808916B0
void func_808917F8(void); // func_808917F8
void func_80891974(void); // func_80891974
void func_808919E8(void); // func_808919E8
void func_80891D78(void); // func_80891D78
void func_80891F60(void); // func_80891F60
void func_808920A0(void); // func_808920A0
void func_80892248(void); // func_80892248
void func_80892274(void); // func_80892274
void func_808922D0(void); // func_808922D0
void func_80892390(void); // func_80892390
void func_80892414(void); // func_80892414
void func_808924B0(void); // func_808924B0
void func_808925F8(void); // func_808925F8
void func_8089262C(void); // func_8089262C
void func_808927CC(void); // func_808927CC
void func_80892E70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80892E70
void func_80892FA0(void); // func_80892FA0
void func_80893008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80893008
void func_808930FC(void); // func_808930FC
void func_808932B0(void); // func_808932B0
void func_808937F0(void); // func_808937F0
void func_808939EC(void); // func_808939EC
void func_80893A18(void); // func_80893A18
void func_80893A34(void); // func_80893A34
void func_80893A9C(void); // func_80893A9C
void func_80893ADC(void); // func_80893ADC
void func_80893B10(void); // func_80893B10
void func_80893B70(void); // func_80893B70
void func_80893BCC(void); // func_80893BCC
void func_80893DD4(void); // func_80893DD4
void func_80893E54(void); // func_80893E54
void func_80893ED4(void); // func_80893ED4
void func_80893F30(void); // func_80893F30
void func_80893FD0(void); // func_80893FD0
void func_80894024(void); // func_80894024
void func_8089408C(void); // func_8089408C
void func_808942B4(void); // func_808942B4
void func_80894414(void); // func_80894414
void func_80894454(void); // func_80894454
void func_8089452C(void); // func_8089452C
void func_808945B4(void); // func_808945B4
void func_808945EC(void); // func_808945EC
void func_80894638(void); // func_80894638
void func_8089484C(void); // func_8089484C
void func_80894910(void); // func_80894910
void func_80894B2C(void); // func_80894B2C
void func_80894BC8(void); // func_80894BC8
void func_80894DD0(void); // func_80894DD0
void func_80894E0C(void); // func_80894E0C
void func_80895020(void); // func_80895020
void func_808951B8(void); // func_808951B8
void func_808952EC(void); // func_808952EC
void func_80895424(void); // func_80895424
void func_808955E4(void); // func_808955E4
void func_80895640(void); // func_80895640
void func_808956B8(void); // func_808956B8
void func_808956FC(void); // func_808956FC
void func_80895738(void); // func_80895738
void func_8089595C(void); // func_8089595C
void func_80895A10(void); // func_80895A10
void func_80895AC0(void); // func_80895AC0
void func_80895CB0(void); // func_80895CB0
void func_80895D08(void); // func_80895D08
void func_80895DE8(void); // func_80895DE8
void func_80895E28(void); // func_80895E28
void func_80895FF8(void); // func_80895FF8
void func_808963B4(void); // func_808963B4
void func_808964E8(void); // func_808964E8
UNK_TYPE4 func_80896750(UNK_TYPE4 param_1, UNK_TYPE4 param_2, UNK_PTR param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, s32 param_6); // func_80896750
void func_80896788(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80896788
void func_8089695C(void); // func_8089695C
void func_80896F30(void); // func_80896F30
void func_808970F4(void); // func_808970F4
void func_80897170(void); // func_80897170
void func_808971DC(void); // func_808971DC
void func_80897258(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80897258
void func_80897390(void); // func_80897390
void func_80897498(void); // func_80897498
void func_80897520(void); // func_80897520
void func_80897648(void); // func_80897648
void func_808976DC(void); // func_808976DC
void func_80897864(void); // func_80897864
void func_80897910(void); // func_80897910
void func_80897A34(void); // func_80897A34
void func_80897A94(void); // func_80897A94
void func_80897D00(void); // func_80897D00
void func_80897D48(void); // func_80897D48
void func_80897EAC(void); // func_80897EAC
void func_80897F44(void); // func_80897F44
void func_80898124(void); // func_80898124
void func_80898144(void); // func_80898144
void func_808982E0(void); // func_808982E0
void func_80898338(void); // func_80898338
void func_80898414(void); // func_80898414
void func_80898454(void); // func_80898454
void func_808984E0(void); // func_808984E0
void func_80898594(void); // func_80898594
void func_80898654(void); // func_80898654
void func_808986A4(void); // func_808986A4
void func_8089874C(void); // func_8089874C
void func_80898A28(void); // func_80898A28
void func_80898E74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80898E74
void func_80899024(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80899024
void func_80899218(void); // func_80899218
void func_80899960(void); // func_80899960
void func_808999B0(void); // func_808999B0
void func_80899A20(void); // func_80899A20
void func_80899A78(void); // func_80899A78
void func_80899ACC(void); // func_80899ACC
void func_80899B88(void); // func_80899B88
void func_80899F30(void); // func_80899F30
void func_8089A0C0(void); // func_8089A0C0
void func_8089A238(void); // func_8089A238
void func_8089A330(void); // func_8089A330
void func_8089A3A0(void); // func_8089A3A0
void func_8089A3FC(void); // func_8089A3FC
void func_8089A6E0(void); // func_8089A6E0
void func_8089A8B0(void); // func_8089A8B0
void func_8089A900(void); // func_8089A900
void func_8089A968(void); // func_8089A968
void func_8089A9B0(void); // func_8089A9B0
void func_8089ABF4(void); // func_8089ABF4
void func_8089AC70(void); // func_8089AC70
void func_8089ACEC(void); // func_8089ACEC
void func_8089AD70(void); // func_8089AD70
void func_8089AE00(void); // func_8089AE00
void func_8089B100(void); // func_8089B100
void func_8089B288(void); // func_8089B288
void func_8089B320(void); // func_8089B320
void func_8089B3D4(void); // func_8089B3D4
void func_8089B4A4(void); // func_8089B4A4
void func_8089B580(void); // func_8089B580
void func_8089B6E8(void); // func_8089B6E8
void func_8089B72C(void); // func_8089B72C
void func_8089B7B0(void); // func_8089B7B0
void func_8089B834(void); // func_8089B834
void func_8089B8B0(void); // func_8089B8B0
void func_8089B98C(void); // func_8089B98C
void func_8089BAC0(void); // func_8089BAC0
void func_8089BB60(void); // func_8089BB60
void func_8089BBB4(void); // func_8089BBB4
void func_8089BD28(void); // func_8089BD28
void func_8089C024(void); // func_8089C024
void func_8089C0DC(void); // func_8089C0DC
void func_8089C164(void); // func_8089C164
void func_8089C1F8(void); // func_8089C1F8
void func_8089C244(void); // func_8089C244
void func_8089C2A8(void); // func_8089C2A8
void func_8089C398(void); // func_8089C398
void func_8089C44C(void); // func_8089C44C
void func_8089C4F8(void); // func_8089C4F8
void func_8089C56C(void); // func_8089C56C
void func_8089C690(void); // func_8089C690
void func_8089C724(void); // func_8089C724
void func_8089C784(void); // func_8089C784
void func_8089C7B8(void); // func_8089C7B8
void func_8089C87C(void); // func_8089C87C
void func_8089C938(void); // func_8089C938
void func_8089CA14(void); // func_8089CA14
void func_8089CA74(void); // func_8089CA74
void func_8089CB10(void); // func_8089CB10
void func_8089CBEC(void); // func_8089CBEC
void func_8089CF00(void); // func_8089CF00
void func_8089CF70(void); // func_8089CF70
void func_8089CFAC(void); // func_8089CFAC
void func_8089D018(void); // func_8089D018
void func_8089D11C(void); // func_8089D11C
void func_8089D1E0(void); // func_8089D1E0
void func_8089D2E0(void); // func_8089D2E0
void func_8089D318(void); // func_8089D318
void func_8089D42C(void); // func_8089D42C
void func_8089D60C(void); // func_8089D60C
void func_8089D960(void); // func_8089D960
void func_8089DC4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8089DC4C
void func_8089DC84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8089DC84
void func_8089DF54(void); // func_8089DF54
void func_8089E8E0(void); // func_8089E8E0
void func_8089E9DC(void); // func_8089E9DC
void func_8089EA10(void); // func_8089EA10
void func_8089EC68(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8089EC68
void func_8089ECBC(void); // func_8089ECBC
void EnZl1_Init(void); // func_8089ED90
void EnZl1_Fini(void); // func_8089EDA0
void EnZl1_Main(void); // func_8089EDB0
void EnZl1_Draw(void); // func_8089EDC0
void func_8089EE20(void); // func_8089EE20
void func_8089EE2C(void); // func_8089EE2C
void func_8089EFF0(void); // func_8089EFF0
void func_8089F014(void); // func_8089F014
void func_8089F0A0(void); // func_8089F0A0
void func_8089F17C(void); // func_8089F17C
void func_8089F218(void); // func_8089F218
void func_8089F2C4(void); // func_8089F2C4
void func_8089F380(void); // func_8089F380
void func_8089F3C8(void); // func_8089F3C8
void func_8089F4E0(void); // func_8089F4E0
void func_8089F59C(void); // func_8089F59C
void func_8089F5D0(void); // func_8089F5D0
void func_8089F5F4(void); // func_8089F5F4
void func_8089F660(void); // func_8089F660
void func_8089F8BC(void); // func_8089F8BC
void func_8089F908(void); // func_8089F908
void func_8089F95C(void); // func_8089F95C
void func_8089F9E4(void); // func_8089F9E4
void func_8089FA54(void); // func_8089FA54
void func_8089FF30(void); // func_8089FF30
void func_8089FFCC(void); // func_8089FFCC
void func_808A005C(void); // func_808A005C
void func_808A0170(void); // func_808A0170
void func_808A0270(void); // func_808A0270
void func_808A029C(void); // func_808A029C
void func_808A0350(void); // func_808A0350
void func_808A03A0(void); // func_808A03A0
void func_808A03E8(void); // func_808A03E8
void func_808A0458(void); // func_808A0458
void func_808A04D4(void); // func_808A04D4
void func_808A08F0(void); // func_808A08F0
void func_808A0900(void); // func_808A0900
void func_808A0974(void); // func_808A0974
void func_808A0B10(void); // func_808A0B10
void func_808A0CD0(void); // func_808A0CD0
void func_808A0D0C(void); // func_808A0D0C
void func_808A0D90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808A0D90
void func_808A0E28(void); // func_808A0E28
void func_808A0F88(void); // func_808A0F88
void func_808A1080(void); // func_808A1080
void func_808A1090(void); // func_808A1090
void func_808A1288(void); // func_808A1288
void func_808A1340(void); // func_808A1340
void func_808A1478(void); // func_808A1478
void func_808A1548(void); // func_808A1548
void func_808A1618(void); // func_808A1618
void func_808A1684(void); // func_808A1684
void func_808A1784(void); // func_808A1784
void func_808A1884(void); // func_808A1884
void func_808A1A70(void); // func_808A1A70
void func_808A1B48(void); // func_808A1B48
void func_808A1C50(void); // func_808A1C50
void func_808A1CC4(void); // func_808A1CC4
void func_808A1D68(void); // func_808A1D68
void func_808A1E14(void); // func_808A1E14
void func_808A24D0(void); // func_808A24D0
void func_808A24DC(void); // func_808A24DC
void func_808A2700(void); // func_808A2700
void func_808A2868(void); // func_808A2868
void func_808A2918(void); // func_808A2918
void func_808A2D94(void); // func_808A2D94
void func_808A2E6C(void); // func_808A2E6C
void func_808A31B0(void); // func_808A31B0
void func_808A323C(void); // func_808A323C
void func_808A32B0(void); // func_808A32B0
void func_808A3428(void); // func_808A3428
void func_808A3458(void); // func_808A3458
void func_808A34B8(void); // func_808A34B8
void func_808A3670(void); // func_808A3670
void func_808A38E4(void); // func_808A38E4
void func_808A3930(void); // func_808A3930
void func_808A3980(void); // func_808A3980
void func_808A39EC(void); // func_808A39EC
void func_808A3A44(void); // func_808A3A44
void func_808A3B04(void); // func_808A3B04
void func_808A3B3C(void); // func_808A3B3C
void func_808A3B74(void); // func_808A3B74
void func_808A3DA8(void); // func_808A3DA8
void func_808A3F88(void); // func_808A3F88
void func_808A4040(void); // func_808A4040
void func_808A410C(void); // func_808A410C
void func_808A41A0(void); // func_808A41A0
void func_808A4214(void); // func_808A4214
void func_808A42D8(void); // func_808A42D8
void func_808A4328(void); // func_808A4328
void func_808A43A4(void); // func_808A43A4
void func_808A44BC(void); // func_808A44BC
void func_808A45A8(void); // func_808A45A8
void func_808A4634(void); // func_808A4634
void func_808A46E8(void); // func_808A46E8
void func_808A4914(void); // func_808A4914
void func_808A4A30(void); // func_808A4A30
void func_808A4AC8(s32 param_1); // func_808A4AC8
void func_808A4AF8(void); // func_808A4AF8
void func_808A4B3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808A4B3C
void func_808A4C14(void); // func_808A4C14
void func_808A5050(void); // func_808A5050
void func_808A52A8(void); // func_808A52A8
void func_808A54B0(void); // func_808A54B0
void func_808A576C(void); // func_808A576C
void func_808A5988(void); // func_808A5988
void func_808A5AF8(void); // func_808A5AF8
void func_808A5BEC(void); // func_808A5BEC
void func_808A5CCC(void); // func_808A5CCC
void func_808A5D7C(void); // func_808A5D7C
void func_808A5DCC(void); // func_808A5DCC
void func_808A5F28(void); // func_808A5F28
void func_808A6064(void); // func_808A6064
void func_808A60E0(void); // func_808A60E0
void func_808A61F4(void); // func_808A61F4
void func_808A6220(void); // func_808A6220
void func_808A63E8(void); // func_808A63E8
void func_808A6468(void); // func_808A6468
void func_808A650C(void); // func_808A650C
void func_808A6580(void); // func_808A6580
void func_808A6A3C(void); // func_808A6A3C
void func_808A6A78(void); // func_808A6A78
void func_808A6C04(void); // func_808A6C04
void func_808A6D70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_808A6D70
void func_808A6D84(void); // func_808A6D84
void func_808A6E24(void); // func_808A6E24
void func_808A701C(void); // func_808A701C
void func_808A7138(void); // func_808A7138
void func_808A71D0(void); // func_808A71D0
void func_808A7230(void); // func_808A7230
void func_808A73E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_808A73E8
void func_808A7478(void); // func_808A7478
void func_808A7930(void); // func_808A7930
void func_808A7954(void); // func_808A7954
void func_808A7968(void); // func_808A7968
void func_808A7A24(void); // func_808A7A24
void func_808A7A5C(void); // func_808A7A5C
void func_808A7AAC(void); // func_808A7AAC
void func_808A7BA0(void); // func_808A7BA0
void func_808A7C04(void); // func_808A7C04
void func_808A7C78(void); // func_808A7C78
void func_808A7D74(void); // func_808A7D74
void func_808A7E30(void); // func_808A7E30
void func_808A7EB8(void); // func_808A7EB8
void func_808A7FD0(void); // func_808A7FD0
void func_808A80A0(void); // func_808A80A0
void func_808A80AC(void); // func_808A80AC
void func_808A812C(void); // func_808A812C
void func_808A8218(void); // func_808A8218
void func_808A82F4(void); // func_808A82F4
void func_808A83BC(void); // func_808A83BC
void func_808A8470(void); // func_808A8470
void func_808A849C(void); // func_808A849C
void func_808A8500(void); // func_808A8500
void func_808A85FC(void); // func_808A85FC
void func_808A8644(void); // func_808A8644
void func_808A86A8(void); // func_808A86A8
void func_808A8708(void); // func_808A8708
void func_808A875C(void); // func_808A875C
void func_808A8798(void); // func_808A8798
void func_808A890C(void); // func_808A890C
void func_808A8B74(void); // func_808A8B74
void func_808A8CC0(void); // func_808A8CC0
void func_808A8DF8(void); // func_808A8DF8
void func_808A8E84(void); // func_808A8E84
void func_808A8EEC(void); // func_808A8EEC
void func_808A90A4(void); // func_808A90A4
void func_808A91B4(void); // func_808A91B4
void func_808A935C(void); // func_808A935C
void func_808A9400(void); // func_808A9400
void func_808A94FC(void); // func_808A94FC
void func_808A95F8(void); // func_808A95F8
void func_808A980C(void); // func_808A980C
void func_808A98E4(void); // func_808A98E4
void func_808A9AB8(void); // func_808A9AB8
void func_808A9C8C(void); // func_808A9C8C
void func_808A9D64(void); // func_808A9D64
void func_808A9E20(void); // func_808A9E20
void func_808A9E5C(void); // func_808A9E5C
void func_808A9E98(void); // func_808A9E98
void func_808AA0C8(void); // func_808AA0C8
void func_808AA1B0(void); // func_808AA1B0
void func_808AA224(void); // func_808AA224
void func_808AA2C8(void); // func_808AA2C8
void func_808AA33C(void); // func_808AA33C
void func_808AA404(void); // func_808AA404
void func_808AA5E8(void); // func_808AA5E8
void func_808AA6D8(void); // func_808AA6D8
void func_808AA79C(void); // func_808AA79C
void func_808AA7C0(void); // func_808AA7C0
void func_808AA85C(void); // func_808AA85C
void func_808AA8E8(void); // func_808AA8E8
void func_808AAA64(void); // func_808AAA64
void func_808AAB30(void); // func_808AAB30
void func_808AACE0(void); // func_808AACE0
void func_808AAD14(void); // func_808AAD14
void func_808AADB4(void); // func_808AADB4
void func_808AAE1C(void); // func_808AAE1C
void func_808AAE84(void); // func_808AAE84
void func_808AAFB0(void); // func_808AAFB0
void func_808AB0B0(void); // func_808AB0B0
void func_808AB16C(void); // func_808AB16C
void func_808AB404(void); // func_808AB404
void func_808AB458(void); // func_808AB458
void func_808AB52C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6); // func_808AB52C
void func_808AB78C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_808AB78C
void func_808AB928(void); // func_808AB928
void func_808ABCD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808ABCD0
void func_808ABD10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808ABD10
void func_808ABD60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808ABD60
void func_808ABE18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808ABE18
void func_808ABE58(void); // func_808ABE58
void func_808ABF30(void); // func_808ABF30
void func_808AC920(void); // func_808AC920
void func_808ACB08(void); // func_808ACB08
void func_808ACB58(void); // func_808ACB58
void func_808ACD2C(void); // func_808ACD2C
void func_808ACF1C(void); // func_808ACF1C
void func_808ACF98(void); // func_808ACF98
void func_808AD05C(void); // func_808AD05C
void func_808AD170(void); // func_808AD170
void func_808AD18C(void); // func_808AD18C
void func_808AD1F0(void); // func_808AD1F0
void func_808AD294(void); // func_808AD294
void func_808AD31C(void); // func_808AD31C
void func_808AD378(void); // func_808AD378
void func_808AD3E8(void); // func_808AD3E8
void func_808AD42C(void); // func_808AD42C
void func_808AD54C(void); // func_808AD54C
void func_808AD5B0(void); // func_808AD5B0
void func_808AD66C(void); // func_808AD66C
void func_808AD68C(void); // func_808AD68C
void func_808AD7EC(void); // func_808AD7EC
void func_808AD840(void); // func_808AD840
void func_808AD888(void); // func_808AD888
void func_808AD8B8(void); // func_808AD8B8
void func_808ADA74(void); // func_808ADA74
void func_808ADAE8(void); // func_808ADAE8
void func_808ADB4C(void); // func_808ADB4C
void func_808ADB70(void); // func_808ADB70
void func_808ADC40(void); // func_808ADC40
void func_808ADC64(void); // func_808ADC64
void func_808ADD20(void); // func_808ADD20
void func_808ADDA8(void); // func_808ADDA8
void func_808ADE00(void); // func_808ADE00
void func_808ADE74(void); // func_808ADE74
void func_808ADFA4(void); // func_808ADFA4
void func_808ADFF0(void); // func_808ADFF0
void func_808AE030(void); // func_808AE030
void func_808AE0EC(void); // func_808AE0EC
void func_808AE304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808AE304
void func_808AE3A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808AE3A8
void func_808AE3FC(void); // func_808AE3FC
void func_808AE530(void); // func_808AE530
void func_808AE8C0(void); // func_808AE8C0
void func_808AE8CC(void); // func_808AE8CC
void func_808AEA78(void); // func_808AEA78
void func_808AEAB8(void); // func_808AEAB8
void func_808AEAE0(void); // func_808AEAE0
void func_808AEE3C(void); // func_808AEE3C
void func_808AEF68(void); // func_808AEF68
void func_808AEFD4(void); // func_808AEFD4
void func_808AF120(void); // func_808AF120
void func_808AF86C(void); // func_808AF86C
void func_808AF8F8(void); // func_808AF8F8
void func_808AFCD0(void); // func_808AFCD0
void func_808AFDF8(void); // func_808AFDF8
void func_808AFE38(void); // func_808AFE38
void func_808AFF9C(void); // func_808AFF9C
void func_808B0040(void); // func_808B0040
void func_808B00D8(void); // func_808B00D8
void func_808B0124(void); // func_808B0124
void func_808B0208(void); // func_808B0208
void func_808B0358(void); // func_808B0358
void func_808B03C0(void); // func_808B03C0
void func_808B0460(void); // func_808B0460
void func_808B04A8(void); // func_808B04A8
void func_808B04E4(void); // func_808B04E4
void func_808B0508(void); // func_808B0508
void func_808B057C(void); // func_808B057C
void func_808B05C8(void); // func_808B05C8
void func_808B0640(void); // func_808B0640
void func_808B066C(void); // func_808B066C
void func_808B06D0(void); // func_808B06D0
void func_808B07A8(void); // func_808B07A8
void func_808B0820(void); // func_808B0820
void func_808B0894(void); // func_808B0894
void func_808B0AD0(void); // func_808B0AD0
void func_808B0B4C(void); // func_808B0B4C
void func_808B0B9C(void); // func_808B0B9C
void func_808B0CC8(void); // func_808B0CC8
void func_808B0EA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808B0EA4
void func_808B0F98(void); // func_808B0F98
void func_808B1330(void); // func_808B1330
void func_808B1504(void); // func_808B1504
void func_808B1530(void); // func_808B1530
void func_808B15B8(void); // func_808B15B8
void func_808B16BC(void); // func_808B16BC
void func_808B1798(void); // func_808B1798
void func_808B1814(void); // func_808B1814
void func_808B18A8(void); // func_808B18A8
void func_808B1B14(void); // func_808B1B14
void func_808B1BC0(void); // func_808B1BC0
void func_808B1CF0(void); // func_808B1CF0
void func_808B2158(void); // func_808B2158
void func_808B2240(void); // func_808B2240
void func_808B2608(void); // func_808B2608
void func_808B2660(void); // func_808B2660
void func_808B2890(void); // func_808B2890
void func_808B28B4(void); // func_808B28B4
void func_808B2980(void); // func_808B2980
void func_808B29C4(void); // func_808B29C4
void func_808B2C40(void); // func_808B2C40
void func_808B2CB8(void); // func_808B2CB8
void func_808B3044(void); // func_808B3044
void func_808B3078(void); // func_808B3078
void func_808B3170(void); // func_808B3170
void func_808B3280(void); // func_808B3280
void func_808B3390(void); // func_808B3390
void func_808B3404(void); // func_808B3404
void func_808B3768(void); // func_808B3768
void func_808B37E8(void); // func_808B37E8
void func_808B39AC(void); // func_808B39AC
void func_808B3B48(void); // func_808B3B48
void func_808B3BE4(void); // func_808B3BE4
void func_808B3C50(void); // func_808B3C50
void func_808B3D74(void); // func_808B3D74
void func_808B3DA8(void); // func_808B3DA8
void func_808B3E40(void); // func_808B3E40
void func_808B3EE8(void); // func_808B3EE8
void func_808B3F50(void); // func_808B3F50
void func_808B42FC(void); // func_808B42FC
void func_808B4548(void); // func_808B4548
void func_808B465C(void); // func_808B465C
void func_808B48FC(void); // func_808B48FC
void func_808B49C8(void); // func_808B49C8
void func_808B4ABC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808B4ABC
void func_808B4AF8(void); // func_808B4AF8
void func_808B5230(void); // func_808B5230
void func_808B5294(void); // func_808B5294
void func_808B52C0(void); // func_808B52C0
void func_808B53C0(void); // func_808B53C0
void func_808B545C(void); // func_808B545C
void func_808B5820(void); // func_808B5820
void func_808B5890(void); // func_808B5890
void func_808B58CC(void); // func_808B58CC
void func_808B5984(void); // func_808B5984
void func_808B5EEC(void); // func_808B5EEC
void func_808B5F68(void); // func_808B5F68
void func_808B60D4(void); // func_808B60D4
void func_808B6310(void); // func_808B6310
void func_808B63E8(void); // func_808B63E8
void func_808B65BC(void); // func_808B65BC
void func_808B677C(void); // func_808B677C
void func_808B7360(void); // func_808B7360
void func_808B736C(void); // func_808B736C
void func_808B7380(void); // func_808B7380
void func_808B73C4(void); // func_808B73C4
void func_808B73FC(void); // func_808B73FC
void func_808B7410(void); // func_808B7410
void func_808B7460(void); // func_808B7460
void func_808B74A8(void); // func_808B74A8
void func_808B74D8(void); // func_808B74D8
void func_808B751C(void); // func_808B751C
void func_808B75B0(void); // func_808B75B0
void func_808B767C(void); // func_808B767C
void func_808B76CC(void); // func_808B76CC
void func_808B77D0(void); // func_808B77D0
void func_808B77E0(void); // func_808B77E0
void func_808B782C(void); // func_808B782C
void func_808B78A4(void); // func_808B78A4
void func_808B78DC(void); // func_808B78DC
void func_808B7914(void); // func_808B7914
void func_808B7A10(void); // func_808B7A10
void func_808B7A6C(void); // func_808B7A6C
void func_808B7A90(void); // func_808B7A90
void func_808B7B54(void); // func_808B7B54
void func_808B7D34(void); // func_808B7D34
void func_808B7FE4(void); // func_808B7FE4
void func_808B8490(void); // func_808B8490
void func_808B849C(void); // func_808B849C
void func_808B8568(void); // func_808B8568
void func_808B866C(void); // func_808B866C
void func_808B86D8(void); // func_808B86D8
void func_808B8774(void); // func_808B8774
void func_808B8878(void); // func_808B8878
void func_808B8924(void); // func_808B8924
void func_808B8A7C(void); // func_808B8A7C
void func_808B8C48(void); // func_808B8C48
void func_808B8E78(void); // func_808B8E78
void func_808B900C(void); // func_808B900C
void func_808B9094(void); // func_808B9094
void func_808B90CC(void); // func_808B90CC
void func_808B921C(void); // func_808B921C
void func_808B93A0(void); // func_808B93A0
void func_808B94A4(void); // func_808B94A4
void func_808B9524(void); // func_808B9524
void func_808B958C(void); // func_808B958C
void func_808B96A0(void); // func_808B96A0
void func_808B96B0(void); // func_808B96B0
void func_808B977C(void); // func_808B977C
void func_808B9840(void); // func_808B9840
void func_808B98A8(void); // func_808B98A8
void func_808B9B30(void); // func_808B9B30
void func_808B9BE8(void); // func_808B9BE8
void func_808B9CE8(void); // func_808B9CE8
void func_808B9E94(void); // func_808B9E94
void func_808B9ED8(void); // func_808B9ED8
void func_808B9F10(void); // func_808B9F10
void func_808B9FD0(void); // func_808B9FD0
void func_808BA10C(void); // func_808BA10C
void func_808BA550(void); // func_808BA550
void func_808BAAF4(void); // func_808BAAF4
void func_808BABF4(void); // func_808BABF4
void func_808BAC04(void); // func_808BAC04
void func_808BACCC(void); // func_808BACCC
void func_808BAE9C(void); // func_808BAE9C
void func_808BB4C4(void); // func_808BB4C4
void func_808BB4F4(void); // func_808BB4F4
void func_808BB84C(void); // func_808BB84C
void func_808BB8D4(void); // func_808BB8D4
void func_808BC010(void); // func_808BC010
void func_808BC270(void); // func_808BC270
void func_808BC2C4(void); // func_808BC2C4
void func_808BC9D4(void); // func_808BC9D4
void func_808BCDF0(void); // func_808BCDF0
void func_808BCEA8(void); // func_808BCEA8
void func_808BCEB8(void); // func_808BCEB8
void func_808BCF54(void); // func_808BCF54
void func_808BCFC4(void); // func_808BCFC4
void func_808BD1E0(void); // func_808BD1E0
void func_808BD31C(void); // func_808BD31C
void func_808BD348(void); // func_808BD348
void func_808BD3B4(void); // func_808BD3B4
void func_808BD428(void); // func_808BD428
void func_808BD49C(void); // func_808BD49C
void func_808BD78C(void); // func_808BD78C
void func_808BD7D4(void); // func_808BD7D4
void func_808BD870(void); // func_808BD870
void func_808BD8D8(void); // func_808BD8D8
void func_808BDA08(void); // func_808BDA08
void func_808BDA4C(void); // func_808BDA4C
void func_808BDC9C(void); // func_808BDC9C
void func_808BDCF0(void); // func_808BDCF0
void func_808BDD54(void); // func_808BDD54
void func_808BDE7C(void); // func_808BDE7C
void func_808BDEF8(void); // func_808BDEF8
void func_808BDF60(void); // func_808BDF60
void func_808BDFB8(void); // func_808BDFB8
void func_808BE1CC(void); // func_808BE1CC
void func_808BE22C(void); // func_808BE22C
void func_808BE294(void); // func_808BE294
void func_808BE358(void); // func_808BE358
void func_808BE3A8(void); // func_808BE3A8
void func_808BE3FC(void); // func_808BE3FC
void func_808BE484(void); // func_808BE484
void func_808BE4D4(void); // func_808BE4D4
void func_808BE680(void); // func_808BE680
void func_808BE6C4(void); // func_808BE6C4
void func_808BE73C(void); // func_808BE73C
void func_808BEA48(void); // func_808BEA48
void func_808BEBD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808BEBD0
void func_808BED30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808BED30
void func_808BEE38(void); // func_808BEE38
void func_808BF220(void); // func_808BF220
void func_808BF318(void); // func_808BF318
void func_808BF344(void); // func_808BF344
void func_808BF3B8(void); // func_808BF3B8
void func_808BF438(void); // func_808BF438
void func_808BF4B4(void); // func_808BF4B4
void func_808BF514(void); // func_808BF514
void func_808BF578(void); // func_808BF578
void func_808BF5AC(void); // func_808BF5AC
void func_808BF5E0(void); // func_808BF5E0
void func_808BF734(void); // func_808BF734
void func_808BF7A0(void); // func_808BF7A0
void func_808BF830(void); // func_808BF830
void func_808BF894(void); // func_808BF894
void func_808BF8DC(void); // func_808BF8DC
void func_808BFA18(void); // func_808BFA18
void func_808BFA3C(void); // func_808BFA3C
void func_808BFAB4(void); // func_808BFAB4
void func_808BFB4C(void); // func_808BFB4C
void func_808BFCCC(void); // func_808BFCCC
void func_808BFE58(void); // func_808BFE58
void func_808BFF8C(void); // func_808BFF8C
void func_808C00A0(void); // func_808C00A0
void func_808C013C(void); // func_808C013C
void func_808C0178(void); // func_808C0178
void func_808C01E0(void); // func_808C01E0
void func_808C03EC(void); // func_808C03EC
void func_808C07D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808C07D4
void func_808C080C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808C080C
void func_808C0A04(void); // func_808C0A04
void func_808C1030(void); // func_808C1030
void func_808C103C(void); // func_808C103C
void func_808C10B0(void); // func_808C10B0
void func_808C10F8(void); // func_808C10F8
void func_808C1154(void); // func_808C1154
void func_808C1168(void); // func_808C1168
void func_808C1198(void); // func_808C1198
void func_808C11C0(void); // func_808C11C0
void func_808C125C(void); // func_808C125C
void func_808C12A4(void); // func_808C12A4
void func_808C18D8(void); // func_808C18D8
void func_808C1918(void); // func_808C1918
void func_808C1D40(void); // func_808C1D40
void func_808C1E68(void); // func_808C1E68
void func_808C1E94(void); // func_808C1E94
void func_808C1F00(void); // func_808C1F00
void func_808C1F74(void); // func_808C1F74
void func_808C1FF4(void); // func_808C1FF4
void func_808C20D4(void); // func_808C20D4
void func_808C2238(void); // func_808C2238
void func_808C2344(void); // func_808C2344
void func_808C23EC(void); // func_808C23EC
void func_808C254C(void); // func_808C254C
void func_808C25E0(void); // func_808C25E0
void func_808C272C(void); // func_808C272C
void func_808C28CC(void); // func_808C28CC
void func_808C2A00(void); // func_808C2A00
void func_808C2B1C(void); // func_808C2B1C
void func_808C2B94(void); // func_808C2B94
void func_808C2BD0(void); // func_808C2BD0
void func_808C2C38(void); // func_808C2C38
void func_808C2CB4(void); // func_808C2CB4
void func_808C2CF0(void); // func_808C2CF0
void func_808C2D78(void); // func_808C2D78
void func_808C2E34(void); // func_808C2E34
void func_808C30A0(void); // func_808C30A0
void func_808C32EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808C32EC
void func_808C3324(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808C3324
void func_808C351C(void); // func_808C351C
void func_808C3A50(void); // func_808C3A50
void func_808C3A78(void); // func_808C3A78
void func_808C3A88(void); // func_808C3A88
void func_808C3A98(void); // func_808C3A98
void func_808C3C00(void); // func_808C3C00
void func_808C3D28(void); // func_808C3D28
void func_808C3F30(void); // func_808C3F30
void func_808C4414(void); // func_808C4414
void func_808C4458(void); // func_808C4458
void func_808C4584(void); // func_808C4584
void func_808C4A3C(void); // func_808C4A3C
void func_808C4F80(void); // func_808C4F80
void func_808C52A0(void); // func_808C52A0
void func_808C5310(void); // func_808C5310
void func_808C5394(void); // func_808C5394
void func_808C5428(void); // func_808C5428
void func_808C54F0(void); // func_808C54F0
void func_808C566C(void); // func_808C566C
void func_808C571C(void); // func_808C571C
void func_808C589C(void); // func_808C589C
void func_808C597C(void); // func_808C597C
void func_808C5AB8(void); // func_808C5AB8
void func_808C5C0C(void); // func_808C5C0C
void func_808C5CB4(void); // func_808C5CB4
void func_808C5D6C(void); // func_808C5D6C
void func_808C5E90(void); // func_808C5E90
void func_808C5F58(void); // func_808C5F58
void func_808C6070(void); // func_808C6070
void func_808C645C(void); // func_808C645C
void func_808C64DC(void); // func_808C64DC
void func_808C6620(void); // func_808C6620
void func_808C66A8(void); // func_808C66A8
void func_808C67C8(void); // func_808C67C8
void func_808C682C(void); // func_808C682C
void func_808C68B8(void); // func_808C68B8
void func_808C692C(void); // func_808C692C
void func_808C6A08(void); // func_808C6A08
void func_808C6AB0(void); // func_808C6AB0
void func_808C6C5C(void); // func_808C6C5C
void func_808C6CDC(void); // func_808C6CDC
void func_808C6D40(void); // func_808C6D40
void func_808C6F6C(void); // func_808C6F6C
void func_808C70D8(void); // func_808C70D8
void func_808C72AC(void); // func_808C72AC
void func_808C74A4(void); // func_808C74A4
void func_808C74F8(void); // func_808C74F8
void func_808C7800(void); // func_808C7800
void func_808C7888(void); // func_808C7888
void func_808C7A30(void); // func_808C7A30
void func_808C7AAC(void); // func_808C7AAC
void func_808C7AEC(void); // func_808C7AEC
void func_808C7B88(void); // func_808C7B88
void func_808C7C04(void); // func_808C7C04
void func_808C7C88(void); // func_808C7C88
void func_808C7CFC(void); // func_808C7CFC
void func_808C7D34(void); // func_808C7D34
void func_808C7DB8(void); // func_808C7DB8
void func_808C7DCC(void); // func_808C7DCC
void func_808C7E24(void); // func_808C7E24
void func_808C7EDC(void); // func_808C7EDC
void func_808C8170(void); // func_808C8170
void func_808C84A4(void); // func_808C84A4
void func_808C8690(void); // func_808C8690
void func_808C882C(void); // func_808C882C
void func_808C8D18(void); // func_808C8D18
void func_808C9160(void); // func_808C9160
void func_808C9220(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808C9220
void func_808C9340(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808C9340
void func_808C96C8(void); // func_808C96C8
void func_808CA0B0(void); // func_808CA0B0
void func_808CA23C(void); // func_808CA23C
void func_808CA268(void); // func_808CA268
void func_808CA308(void); // func_808CA308
void func_808CA34C(void); // func_808CA34C
void func_808CA458(void); // func_808CA458
void func_808CA7D4(void); // func_808CA7D4
void func_808CA860(void); // func_808CA860
void func_808CA8E0(void); // func_808CA8E0
void func_808CA8F4(void); // func_808CA8F4
void func_808CAAC8(void); // func_808CAAC8
void func_808CAAEC(void); // func_808CAAEC
void func_808CAB90(void); // func_808CAB90
void func_808CABB0(void); // func_808CABB0
void func_808CAC54(void); // func_808CAC54
void func_808CACD8(void); // func_808CACD8
void func_808CAE00(void); // func_808CAE00
void func_808CAE18(void); // func_808CAE18
void func_808CAF08(void); // func_808CAF08
void func_808CAF68(void); // func_808CAF68
void func_808CB07C(void); // func_808CB07C
void func_808CB094(void); // func_808CB094
void func_808CB0C8(void); // func_808CB0C8
void func_808CB22C(void); // func_808CB22C
void func_808CB418(void); // func_808CB418
void func_808CB454(void); // func_808CB454
void func_808CB524(void); // func_808CB524
void func_808CB59C(void); // func_808CB59C
void func_808CB6A8(void); // func_808CB6A8
void func_808CB6D4(void); // func_808CB6D4
void func_808CB7B8(void); // func_808CB7B8
void func_808CB7CC(void); // func_808CB7CC
void func_808CB810(void); // func_808CB810
void func_808CB8F4(void); // func_808CB8F4
void func_808CBB18(void); // func_808CBB18
void func_808CC260(void); // func_808CC260
void func_808CC3E0(void); // func_808CC3E0
void func_808CC420(void); // func_808CC420
void func_808CC490(void); // func_808CC490
void func_808CC5C4(void); // func_808CC5C4
void func_808CC610(void); // func_808CC610
void func_808CC788(void); // func_808CC788
void func_808CC820(void); // func_808CC820
void func_808CCA10(void); // func_808CCA10
void func_808CCAA4(void); // func_808CCAA4
void func_808CCB08(void); // func_808CCB08
void func_808CCB50(void); // func_808CCB50
void func_808CCBE4(void); // func_808CCBE4
void func_808CCCF0(void); // func_808CCCF0
void func_808CCDE4(void); // func_808CCDE4
void func_808CCEE4(void); // func_808CCEE4
UNK_TYPE4 func_808CD020(UNK_TYPE4 param_1, int param_2, UNK_PTR param_3, UNK_TYPE4 param_4, short* param_5, int param_6); // func_808CD020
void func_808CD08C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808CD08C
void func_808CD238(void); // func_808CD238
void func_808CD740(void); // func_808CD740
void func_808CD8E8(void); // func_808CD8E8
void func_808CD940(void); // func_808CD940
void func_808CD998(void); // func_808CD998
void func_808CDAD0(void); // func_808CDAD0
void func_808CDBDC(void); // func_808CDBDC
void func_808CDCEC(void); // func_808CDCEC
void func_808CDD70(void); // func_808CDD70
void func_808CDDE0(void); // func_808CDDE0
void func_808CDE54(void); // func_808CDE54
void func_808CDE78(void); // func_808CDE78
void func_808CDFF8(void); // func_808CDFF8
void func_808CE078(void); // func_808CE078
void func_808CE450(void); // func_808CE450
void func_808CE45C(void); // func_808CE45C
void func_808CF06C(void); // func_808CF06C
void func_808CF0CC(void); // func_808CF0CC
void func_808CF808(void); // func_808CF808
void func_808CF928(void); // func_808CF928
void func_808CF94C(void); // func_808CF94C
void func_808CF970(void); // func_808CF970
void func_808CFE04(void); // func_808CFE04
void func_808D035C(void); // func_808D035C
void func_808D0680(void); // func_808D0680
void func_808D08A4(void); // func_808D08A4
void func_808D08D0(void); // func_808D08D0
void func_808D0908(void); // func_808D0908
void func_808D0930(void); // func_808D0930
void func_808D09CC(void); // func_808D09CC
void func_808D0A48(void); // func_808D0A48
void func_808D0B08(void); // func_808D0B08
void func_808D0B50(void); // func_808D0B50
void func_808D0C14(void); // func_808D0C14
void func_808D0C58(void); // func_808D0C58
void func_808D0CE4(void); // func_808D0CE4
void func_808D0D70(void); // func_808D0D70
void func_808D0ECC(void); // func_808D0ECC
void func_808D0F14(void); // func_808D0F14
void func_808D0F50(void); // func_808D0F50
void func_808D0F80(void); // func_808D0F80
void func_808D108C(void); // func_808D108C
void func_808D11BC(void); // func_808D11BC
void func_808D1380(void); // func_808D1380
void func_808D1458(void); // func_808D1458
void func_808D14DC(void); // func_808D14DC
void func_808D161C(void); // func_808D161C
void func_808D1650(void); // func_808D1650
void func_808D1740(void); // func_808D1740
void func_808D17EC(void); // func_808D17EC
void func_808D19D4(void); // func_808D19D4
void func_808D1B44(void); // func_808D1B44
void func_808D1BCC(void); // func_808D1BCC
void func_808D1C1C(void); // func_808D1C1C
void func_808D1D0C(void); // func_808D1D0C
void func_808D1D6C(void); // func_808D1D6C
void func_808D1ED4(void); // func_808D1ED4
void func_808D1F7C(void); // func_808D1F7C
void func_808D1FD4(void); // func_808D1FD4
void func_808D2040(void); // func_808D2040
void func_808D217C(void); // func_808D217C
void func_808D22C8(void); // func_808D22C8
void func_808D2484(void); // func_808D2484
void func_808D24F0(void); // func_808D24F0
void func_808D2700(void); // func_808D2700
void func_808D2764(void); // func_808D2764
void func_808D2A20(void); // func_808D2A20
void func_808D2AA8(void); // func_808D2AA8
void func_808D2AB8(void); // func_808D2AB8
void func_808D2AF4(void); // func_808D2AF4
void func_808D2B18(void); // func_808D2B18
void func_808D2C08(void); // func_808D2C08
void func_808D2CDC(void); // func_808D2CDC
void func_808D2D30(void); // func_808D2D30
void func_808D2D6C(void); // func_808D2D6C
void func_808D2DC0(void); // func_808D2DC0
void func_808D2E34(void); // func_808D2E34
void func_808D316C(void); // func_808D316C
void func_808D3488(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808D3488
void func_808D34C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808D34C4
void func_808D3630(void); // func_808D3630
void func_808D3754(void); // func_808D3754
void func_808D3E20(void); // func_808D3E20
void func_808D414C(void); // func_808D414C
void func_808D4190(void); // func_808D4190
void func_808D41FC(void); // func_808D41FC
void func_808D4260(void); // func_808D4260
void func_808D4308(void); // func_808D4308
void func_808D43AC(void); // func_808D43AC
void func_808D45D4(void); // func_808D45D4
void func_808D4660(void); // func_808D4660
void func_808D47DC(void); // func_808D47DC
void func_808D4868(void); // func_808D4868
void func_808D49E4(void); // func_808D49E4
void func_808D4A90(void); // func_808D4A90
void func_808D4B20(void); // func_808D4B20
void func_808D4CA8(void); // func_808D4CA8
void func_808D4DC4(void); // func_808D4DC4
void func_808D4E60(void); // func_808D4E60
void func_808D4FE0(void); // func_808D4FE0
void func_808D506C(void); // func_808D506C
void func_808D53C0(void); // func_808D53C0
void func_808D5440(void); // func_808D5440
void func_808D5660(void); // func_808D5660
void func_808D56E4(void); // func_808D56E4
void func_808D586C(void); // func_808D586C
void func_808D58CC(void); // func_808D58CC
void func_808D5C54(void); // func_808D5C54
void func_808D5CCC(void); // func_808D5CCC
void func_808D5D88(void); // func_808D5D88
void func_808D5DF4(void); // func_808D5DF4
void func_808D5E98(void); // func_808D5E98
void func_808D5F18(void); // func_808D5F18
void func_808D6008(void); // func_808D6008
void func_808D6054(void); // func_808D6054
void func_808D60B0(void); // func_808D60B0
void func_808D6130(void); // func_808D6130
void func_808D616C(void); // func_808D616C
void func_808D6200(void); // func_808D6200
void func_808D6310(void); // func_808D6310
void func_808D6388(void); // func_808D6388
void func_808D64D0(void); // func_808D64D0
void func_808D65BC(void); // func_808D65BC
void func_808D66A0(void); // func_808D66A0
void func_808D6814(void); // func_808D6814
void func_808D6A94(void); // func_808D6A94
void func_808D6B64(void); // func_808D6B64
void func_808D6C10(void); // func_808D6C10
UNK_TYPE4 func_808D6DA0(UNK_TYPE4 param_1, s32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, s32 param_5, s32 param_6); // func_808D6DA0
void func_808D6DFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808D6DFC
void func_808D6ED8(void); // func_808D6ED8
void func_808D7550(void); // func_808D7550
void func_808D75BC(void); // func_808D75BC
void func_808D75F0(void); // func_808D75F0
void func_808D7714(void); // func_808D7714
void func_808D77B8(void); // func_808D77B8
void func_808D77DC(void); // func_808D77DC
UNK_TYPE4 func_808D78D0(Actor* param_1); // func_808D78D0
unsigned int func_808D7928(Actor* param_1); // func_808D7928
void func_808D7954(Actor* param_1); // func_808D7954
void func_808D7A04(void); // func_808D7A04
int func_808D7A14(int param_1); // func_808D7A14
void func_808D7A40(UNK_PTR param_1, UNK_PTR param_2); // func_808D7A40
void func_808D7A68(int param_1, GlobalContext* param_2); // func_808D7A68
void func_808D7C64(int param_1, GlobalContext* param_2); // func_808D7C64
void func_808D7DC4(int param_1, GlobalContext* param_2); // func_808D7DC4
void func_808D7E14(unsigned int param_1, GlobalContext* param_2); // func_808D7E14
void func_808D7F0C(unsigned int param_1, GlobalContext* param_2); // func_808D7F0C
void func_808D7F2C(int param_1); // func_808D7F2C
void func_808D7FFC(int param_1); // func_808D7FFC
void func_808D8014(int param_1, GlobalContext* param_2); // func_808D8014
void func_808D8074(int param_1, unsigned int param_2); // func_808D8074
void func_808D814C(int param_1, int param_2); // func_808D814C
void func_808D82CC(int param_1); // func_808D82CC
void func_808D84F4(unsigned int param_1); // func_808D84F4
void func_808D8678(unsigned int param_1, GlobalContext* param_2); // func_808D8678
void func_808D8720(int param_1); // func_808D8720
void func_808D8940(void); // func_808D8940
void func_808D8B58(void); // func_808D8B58
void func_808D8D60(void); // func_808D8D60
void func_808D8ED0(void); // func_808D8ED0
void func_808D8FC4(void); // func_808D8FC4
void func_808D90C4(void); // func_808D90C4
void func_808D90F0(void); // func_808D90F0
void func_808D91C4(void); // func_808D91C4
void func_808D93BC(void); // func_808D93BC
void func_808D9440(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808D9440
void func_808D94D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_808D94D0
void func_808D9894(void); // func_808D9894
void func_808D9968(void); // func_808D9968
void func_808D99C8(void); // func_808D99C8
void func_808D9A70(void); // func_808D9A70
void func_808D9C18(void); // func_808D9C18
void func_808D9DA0(void); // func_808D9DA0
void func_808D9E44(void); // func_808D9E44
void func_808D9F08(void); // func_808D9F08
void func_808D9F78(void); // func_808D9F78
void func_808DA024(void); // func_808DA024
void func_808DA08C(void); // func_808DA08C
void func_808DA350(void); // func_808DA350
void func_808DA3F4(void); // func_808DA3F4
void func_808DA578(void); // func_808DA578
void func_808DA6FC(void); // func_808DA6FC
void func_808DA89C(void); // func_808DA89C
void func_808DAA60(void); // func_808DAA60
void func_808DACF4(void); // func_808DACF4
void func_808DAEB4(void); // func_808DAEB4
void func_808DB100(void); // func_808DB100
void func_808DB25C(void); // func_808DB25C
void func_808DB2E0(void); // func_808DB2E0
void func_808DB454(void); // func_808DB454
void func_808DB70C(void); // func_808DB70C
void func_808DB738(void); // func_808DB738
void func_808DB7F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_808DB7F4
void func_808DB8DC(void); // func_808DB8DC
void func_808DBE80(void); // func_808DBE80
void func_808DBE8C(void); // func_808DBE8C
void func_808DBEB0(void); // func_808DBEB0
void func_808DBFB0(void); // func_808DBFB0
void func_808DC038(void); // func_808DC038
void func_808DC0BC(void); // func_808DC0BC
void func_808DC168(void); // func_808DC168
void func_808DC18C(void); // func_808DC18C
void func_808DC454(void); // func_808DC454
void func_808DCB7C(void); // func_808DCB7C
void func_808DCBF8(void); // func_808DCBF8
void func_808DCDB4(void); // func_808DCDB4
void func_808DD340(void); // func_808DD340
void func_808DD364(void); // func_808DD364
void func_808DD3C8(void); // func_808DD3C8
void func_808DD970(void); // func_808DD970
void func_808DDE74(void); // func_808DDE74
void func_808DDE9C(void); // func_808DDE9C
void func_808DE5C0(void); // func_808DE5C0
void func_808DE660(void); // func_808DE660
void func_808DE728(void); // func_808DE728
void func_808DE7F0(void); // func_808DE7F0
void func_808DE958(void); // func_808DE958
void func_808DE9A8(void); // func_808DE9A8
void func_808DEA0C(void); // func_808DEA0C
void func_808DEA54(void); // func_808DEA54
void func_808DEB14(void); // func_808DEB14
void func_808DECA0(void); // func_808DECA0
void func_808DED40(void); // func_808DED40
void func_808DEFE8(void); // func_808DEFE8
void func_808DF088(void); // func_808DF088
void func_808DF194(void); // func_808DF194
void func_808DF560(void); // func_808DF560
void func_808DF620(void); // func_808DF620
void func_808DF788(void); // func_808DF788
void func_808DF838(void); // func_808DF838
void func_808DFB14(void); // func_808DFB14
void func_808DFC3C(void); // func_808DFC3C
void func_808DFDC8(void); // func_808DFDC8
void func_808DFE3C(void); // func_808DFE3C
void func_808E01A0(void); // func_808E01A0
void func_808E01AC(void); // func_808E01AC
void func_808E0264(void); // func_808E0264
void func_808E02A4(void); // func_808E02A4
void func_808E03B8(void); // func_808E03B8
void func_808E05C4(void); // func_808E05C4
void func_808E06B0(void); // func_808E06B0
void func_808E0704(void); // func_808E0704
void func_808E0830(void); // func_808E0830
void func_808E0954(void); // func_808E0954
void func_808E0DA8(void); // func_808E0DA8
void func_808E0E40(void); // func_808E0E40
void func_808E0EBC(void); // func_808E0EBC
void func_808E0EE8(void); // func_808E0EE8
void func_808E0EF4(void); // func_808E0EF4
void func_808E0F4C(void); // func_808E0F4C
void func_808E0FE0(void); // func_808E0FE0
void func_808E1270(void); // func_808E1270
void func_808E12A4(void); // func_808E12A4
void func_808E13FC(void); // func_808E13FC
void func_808E1560(void); // func_808E1560
void func_808E16B4(void); // func_808E16B4
void func_808E16FC(void); // func_808E16FC
void func_808E1714(void); // func_808E1714
void func_808E17C4(void); // func_808E17C4
void func_808E18A8(void); // func_808E18A8
void func_808E18F8(void); // func_808E18F8
void func_808E19C4(void); // func_808E19C4
void func_808E1A24(void); // func_808E1A24
void func_808E1B4C(void); // func_808E1B4C
void func_808E1C9C(void); // func_808E1C9C
void func_808E1FE0(void); // func_808E1FE0
void func_808E1FF0(void); // func_808E1FF0
void func_808E2000(void); // func_808E2000
void func_808E2010(void); // func_808E2010
void func_808E2070(void); // func_808E2070
void func_808E21C8(void); // func_808E21C8
void func_808E21FC(void); // func_808E21FC
void func_808E22DC(void); // func_808E22DC
void func_808E22EC(void); // func_808E22EC
void func_808E23D0(void); // func_808E23D0
void func_808E2444(void); // func_808E2444
void func_808E24B4(void); // func_808E24B4
void func_808E24D8(void); // func_808E24D8
void func_808E2600(void); // func_808E2600
void func_808E26C8(void); // func_808E26C8
void func_808E286C(void); // func_808E286C
void func_808E2B04(void); // func_808E2B04
void func_808E2B7C(void); // func_808E2B7C
void func_808E2C68(void); // func_808E2C68
void func_808E2E1C(void); // func_808E2E1C
void func_808E2FF8(void); // func_808E2FF8
void func_808E30FC(void); // func_808E30FC
void func_808E36A4(void); // func_808E36A4
void func_808E3984(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_808E3984
void func_808E3EF0(void); // func_808E3EF0
void func_808E3FF0(void); // func_808E3FF0
void func_808E401C(void); // func_808E401C
void func_808E40CC(void); // func_808E40CC
void func_808E4144(void); // func_808E4144
void func_808E41C0(void); // func_808E41C0
void func_808E4234(void); // func_808E4234
void func_808E42DC(void); // func_808E42DC
void func_808E4354(void); // func_808E4354
void func_808E4458(void); // func_808E4458
void func_808E44D4(void); // func_808E44D4
void func_808E45A0(void); // func_808E45A0
void func_808E4654(void); // func_808E4654
void func_808E4740(void); // func_808E4740
void func_808E47E8(void); // func_808E47E8
void func_808E491C(int param_1); // func_808E491C
void func_808E4984(void); // func_808E4984
void func_808E4AC8(void); // func_808E4AC8
void func_808E4C18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808E4C18
void func_808E4CB0(void); // func_808E4CB0
void func_808E4FC0(void); // func_808E4FC0
void func_808E530C(void); // func_808E530C
void func_808E5388(void); // func_808E5388
void func_808E5430(void); // func_808E5430
void func_808E5484(void); // func_808E5484
void func_808E574C(void); // func_808E574C
void func_808E5988(void); // func_808E5988
void func_808E5A00(void); // func_808E5A00
void func_808E5BB0(void); // func_808E5BB0
void func_808E5ED4(void); // func_808E5ED4
void func_808E601C(void); // func_808E601C
void func_808E616C(void); // func_808E616C
void func_808E62B8(void); // func_808E62B8
void func_808E64D4(void); // func_808E64D4
void func_808E6538(void); // func_808E6538
void func_808E6570(void); // func_808E6570
void func_808E670C(void); // func_808E670C
void func_808E6828(void); // func_808E6828
void func_808E68AC(void); // func_808E68AC
void func_808E69AC(void); // func_808E69AC
void func_808E69F4(void); // func_808E69F4
void func_808E6A70(void); // func_808E6A70
void func_808E6B08(void); // func_808E6B08
void func_808E6B68(void); // func_808E6B68
void func_808E6C18(void); // func_808E6C18
void func_808E6C44(void); // func_808E6C44
void func_808E6C70(void); // func_808E6C70
void func_808E6CC8(void); // func_808E6CC8
void func_808E6D58(void); // func_808E6D58
void func_808E6E80(void); // func_808E6E80
void func_808E6F08(void); // func_808E6F08
void func_808E6F50(void); // func_808E6F50
void func_808E6FE0(void); // func_808E6FE0
void func_808E7048(void); // func_808E7048
void func_808E7154(void); // func_808E7154
void func_808E71FC(void); // func_808E71FC
void func_808E732C(void); // func_808E732C
void func_808E7354(void); // func_808E7354
void func_808E75D8(void); // func_808E75D8
void func_808E7770(void); // func_808E7770
void func_808E7AF8(void); // func_808E7AF8
void func_808E7B80(void); // func_808E7B80
void func_808E7D68(void); // func_808E7D68
void func_808E8064(void); // func_808E8064
void func_808E836C(void); // func_808E836C
void func_808E844C(void); // func_808E844C
void func_808E84DC(void); // func_808E84DC
void func_808E88B8(void); // func_808E88B8
void func_808E89CC(void); // func_808E89CC
void func_808E8C38(void); // func_808E8C38
void func_808E8CCC(void); // func_808E8CCC
void func_808E90A4(void); // func_808E90A4
void func_808E91EC(void); // func_808E91EC
void func_808E9778(void); // func_808E9778
void func_808E97D0(void); // func_808E97D0
void func_808E994C(void); // func_808E994C
void func_808E9AE0(void); // func_808E9AE0
void func_808E9DA8(void); // func_808E9DA8
void func_808E9DD0(void); // func_808E9DD0
void func_808E9F38(void); // func_808E9F38
void func_808E9FC0(void); // func_808E9FC0
void func_808EA14C(void); // func_808EA14C
void func_808EA1C8(void); // func_808EA1C8
void func_808EA264(void); // func_808EA264
void func_808EA2D0(void); // func_808EA2D0
void func_808EA538(void); // func_808EA538
void func_808EA5E8(void); // func_808EA5E8
void func_808EA748(void); // func_808EA748
void func_808EA7A4(void); // func_808EA7A4
void func_808EA80C(void); // func_808EA80C
void func_808EA860(void); // func_808EA860
void func_808EA8FC(void); // func_808EA8FC
void func_808EA9B8(void); // func_808EA9B8
void func_808EAA40(void); // func_808EAA40
void func_808EAA8C(void); // func_808EAA8C
void func_808EAAF8(void); // func_808EAAF8
void func_808EAB74(void); // func_808EAB74
void func_808EABCC(void); // func_808EABCC
void func_808EACEC(void); // func_808EACEC
void func_808EAEBC(void); // func_808EAEBC
void func_808EB0A8(void); // func_808EB0A8
void func_808EB178(void); // func_808EB178
void func_808EB24C(void); // func_808EB24C
void func_808EB328(void); // func_808EB328
void func_808EB574(void); // func_808EB574
void func_808EB690(void); // func_808EB690
void func_808EB708(void); // func_808EB708
void func_808EB7F0(void); // func_808EB7F0
void func_808EB804(void); // func_808EB804
void func_808EB83C(void); // func_808EB83C
void func_808EB8B4(void); // func_808EB8B4
void func_808EB9E8(void); // func_808EB9E8
void func_808EBBE4(void); // func_808EBBE4
void func_808EBED0(void); // func_808EBED0
void func_808EC158(void); // func_808EC158
void func_808EC354(void); // func_808EC354
void func_808EC4E4(void); // func_808EC4E4
void func_808EC708(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_808EC708
void func_808EC990(void); // func_808EC990
void func_808ECD14(void); // func_808ECD14
void func_808ED07C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808ED07C
void func_808ED138(void); // func_808ED138
void func_808ED3F4(void); // func_808ED3F4
void func_808F1200(void); // func_808F1200
void func_808F1334(void); // func_808F1334
void func_808F1374(void); // func_808F1374
void func_808F13FC(void); // func_808F13FC
void func_808F152C(void); // func_808F152C
void func_808F155C(void); // func_808F155C
void func_808F15B0(void); // func_808F15B0
void func_808F1648(void); // func_808F1648
void func_808F169C(void); // func_808F169C
void func_808F16FC(void); // func_808F16FC
void func_808F1778(void); // func_808F1778
void func_808F1878(void); // func_808F1878
void func_808F190C(void); // func_808F190C
void func_808F1A3C(void); // func_808F1A3C
void func_808F1A58(void); // func_808F1A58
void func_808F1BF8(void); // func_808F1BF8
void func_808F1C84(void); // func_808F1C84
void func_808F1FAC(void); // func_808F1FAC
void func_808F200C(void); // func_808F200C
void func_808F20FC(void); // func_808F20FC
void func_808F21A4(void); // func_808F21A4
void func_808F220C(void); // func_808F220C
void func_808F228C(void); // func_808F228C
void func_808F238C(void); // func_808F238C
void func_808F241C(void); // func_808F241C
void func_808F24F8(void); // func_808F24F8
void func_808F254C(void); // func_808F254C
void func_808F25A4(void); // func_808F25A4
void func_808F280C(void); // func_808F280C
void func_808F28F8(void); // func_808F28F8
void func_808F30B0(void); // func_808F30B0
void func_808F3178(void); // func_808F3178
void func_808F322C(void); // func_808F322C
void func_808F32A0(void); // func_808F32A0
void func_808F3310(void); // func_808F3310
void func_808F3334(void); // func_808F3334
void func_808F33B8(void); // func_808F33B8
void func_808F3414(void); // func_808F3414
void func_808F35AC(void); // func_808F35AC
void func_808F35D8(void); // func_808F35D8
void func_808F3608(void); // func_808F3608
void func_808F3618(void); // func_808F3618
void func_808F3690(void); // func_808F3690
void func_808F374C(void); // func_808F374C
void func_808F38F8(void); // func_808F38F8
void func_808F395C(void); // func_808F395C
void func_808F39DC(void); // func_808F39DC
void func_808F3AD4(void); // func_808F3AD4
void func_808F3B40(void); // func_808F3B40
void func_808F3BD4(void); // func_808F3BD4
void func_808F3C40(void); // func_808F3C40
void func_808F3CD4(void); // func_808F3CD4
void func_808F3D40(void); // func_808F3D40
void func_808F3DD4(void); // func_808F3DD4
void func_808F4054(void); // func_808F4054
void func_808F4108(void); // func_808F4108
void func_808F4150(void); // func_808F4150
void func_808F4270(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808F4270
void func_808F43E0(void); // func_808F43E0
void func_808F4414(void); // func_808F4414
void func_808F5674(void); // func_808F5674
void func_808F5728(void); // func_808F5728
void func_808F5994(void); // func_808F5994
void func_808F5A34(void); // func_808F5A34
void func_808F5A94(void); // func_808F5A94
void func_808F5B58(void); // func_808F5B58
void func_808F5C98(void); // func_808F5C98
void func_808F5DA4(void); // func_808F5DA4
void func_808F621C(void); // func_808F621C
void func_808F6248(void); // func_808F6248
void func_808F6334(void); // func_808F6334
void func_808F64A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808F64A0
void func_808F67F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_808F67F8
void func_808F69B4(void); // func_808F69B4
void func_808F74B0(void); // func_808F74B0
void func_808F7580(void); // func_808F7580
void func_808F75D0(void); // func_808F75D0
void func_808F77E4(void); // func_808F77E4
void func_808F7868(void); // func_808F7868
void func_808F7944(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_808F7944
void func_808F79D4(void); // func_808F79D4
void func_808F7A84(void); // func_808F7A84
void func_808F7E74(void); // func_808F7E74
void func_808F7FA0(void); // func_808F7FA0
void func_808F7FD0(void); // func_808F7FD0
void func_808F8080(void); // func_808F8080
void func_808F818C(void); // func_808F818C
void func_808F83B8(void); // func_808F83B8
void func_808F8714(void); // func_808F8714
void D_808F890C(void); // func_808F890C
void func_808F8AA0(void); // func_808F8AA0
void func_808F8C24(void); // func_808F8C24
void func_808F8C5C(void); // func_808F8C5C
void func_808F8C70(void); // func_808F8C70
void func_808F8CCC(void); // func_808F8CCC
void func_808F8E94(void); // func_808F8E94
void func_808F8EB0(void); // func_808F8EB0
void func_808F8FAC(void); // func_808F8FAC
void func_808F96E4(void); // func_808F96E4
void func_808F9830(void); // func_808F9830
void func_808F9868(void); // func_808F9868
void func_808F987C(void); // func_808F987C
void func_808F990C(void); // func_808F990C
void func_808F9944(void); // func_808F9944
void func_808F9958(void); // func_808F9958
void func_808F999C(void); // func_808F999C
void func_808F99B0(void); // func_808F99B0
void func_808F99C4(void); // func_808F99C4
void func_808F99D8(void); // func_808F99D8
void func_808F99EC(void); // func_808F99EC
void func_808F9A4C(void); // func_808F9A4C
void func_808F9A88(void); // func_808F9A88
void func_808F9AC4(void); // func_808F9AC4
void func_808F9E00(void); // func_808F9E00
void func_808F9FDC(void); // func_808F9FDC
void func_808FA01C(void); // func_808FA01C
void func_808FA11C(void); // func_808FA11C
void func_808FA19C(void); // func_808FA19C
void func_808FA238(void); // func_808FA238
void func_808FA260(void); // func_808FA260
void func_808FA344(void); // func_808FA344
void func_808FA3F8(void); // func_808FA3F8
void func_808FA4F4(void); // func_808FA4F4
void func_808FA6B8(void); // func_808FA6B8
void func_808FA7AC(void); // func_808FA7AC
void func_808FA870(void); // func_808FA870
void func_808FA910(void); // func_808FA910
void func_808FA9CC(void); // func_808FA9CC
void func_808FAA94(void); // func_808FAA94
void func_808FAC80(void); // func_808FAC80
void func_808FAD1C(void); // func_808FAD1C
void func_808FAE50(void); // func_808FAE50
void func_808FAF94(void); // func_808FAF94
void func_808FB088(void); // func_808FB088
void func_808FB1C0(void); // func_808FB1C0
void func_808FB2C0(void); // func_808FB2C0
void func_808FB398(void); // func_808FB398
void func_808FB42C(void); // func_808FB42C
void func_808FB680(void); // func_808FB680
void func_808FB710(void); // func_808FB710
void func_808FB794(void); // func_808FB794
void func_808FB888(void); // func_808FB888
void func_808FBD54(void); // func_808FBD54
void func_808FC550(void); // func_808FC550
void func_808FC5AC(void); // func_808FC5AC
void func_808FC5BC(void); // func_808FC5BC
void func_808FC6C0(int param_1, int param_2, float* param_3, float param_4); // func_808FC6C0
void func_808FC770(UNK_TYPE4 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_808FC770
f32 func_808FC790(void); // func_808FC790
int func_808FC8B8(short* param_1, short param_2, short param_3, short param_4); // func_808FC8B8
void func_808FC964(int param_1, UNK_PTR param_2, UNK_PTR param_3, float param_4, float param_5, UNK_TYPE2 param_6, short param_7); // func_808FC964
void func_808FCABC(int param_1, UNK_PTR param_2, UNK_PTR param_3, UNK_PTR param_4, UNK_TYPE4 param_5); // func_808FCABC
void func_808FCC0C(int param_1, UNK_PTR param_2, UNK_PTR param_3, float param_4); // func_808FCC0C
void func_808FCDBC(int param_1, UNK_PTR param_2, UNK_PTR param_3, UNK_TYPE4 param_4, u8 param_5); // func_808FCDBC
void func_808FCF60(int param_1, UNK_PTR param_2, f32* param_3); // func_808FCF60
void func_808FD054(void); // func_808FD054
void func_808FD368(Actor* param_1, GlobalContext* param_2); // func_808FD368
void func_808FDC64(int param_1, GlobalContext* param_2); // func_808FDC64
void func_808FDCDC(float* param_1, GlobalContext* param_2); // func_808FDCDC
void func_808FE3F8(f32* param_1, GraphicsContext** param_2); // func_808FE3F8
void func_808FEE1C(GraphicsContext** param_1); // func_808FEE1C
UNK_TYPE4 func_808FEF70(float* param_1); // func_808FEF70
void func_808FF064(int param_1, float* param_2, int param_3, int param_4); // func_808FF064
void func_808FF5E0(int param_1); // func_808FF5E0
void func_808FF750(GraphicsContext** param_1, float* param_2, float* param_3, u8 param_4); // func_808FF750
void func_808FFC44(int param_1); // func_808FFC44
void func_808FFF3C(GraphicsContext** param_1); // func_808FFF3C
void func_80900228(GraphicsContext** param_1, int param_2, int param_3); // func_80900228
void func_80900A04(GraphicsContext** param_1); // func_80900A04
void func_80901480(Actor* param_1, GlobalContext* param_2); // func_80901480
UNK_TYPE4 func_809033F0(int param_1, int param_2, char param_3); // func_809033F0
void func_809036BC(int param_1, int param_2); // func_809036BC
void func_809038A4(int param_1, unsigned short* param_2); // func_809038A4
void func_80903C60(Actor* param_1, char param_2); // func_80903C60
void func_80903E20(Actor* param_1, GlobalContext* param_2); // func_80903E20
void func_80903FE0(Actor* param_1, GlobalContext* param_2); // func_80903FE0
UNK_TYPE4 func_80908554(UNK_TYPE4 param_1, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, int param_5, int param_6); // func_80908554
void func_80908674(UNK_TYPE4 param_1, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, int param_5); // func_80908674
UNK_TYPE4 func_809086B4(UNK_TYPE4 param_1, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, int param_5, int param_6); // func_809086B4
void func_80908734(UNK_TYPE4 param_1, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, int param_5); // func_80908734
void func_80908774(int param_1, GraphicsContext** param_2); // func_80908774
void func_809089B8(float* param_1, float* param_2); // func_809089B8
void func_80908A64(float* param_1, float* param_2, u8 param_3); // func_80908A64
void func_80908B4C(GlobalContext* param_1); // func_80908B4C
void func_80908E08(GraphicsContext** param_1); // func_80908E08
void func_80909234(int param_1); // func_80909234
void func_80909AD0(GraphicsContext** param_1); // func_80909AD0
void func_80909CC0(Actor* param_1, GlobalContext* param_2); // func_80909CC0
void func_8090AB6C(Actor* param_1, GlobalContext* param_2); // func_8090AB6C
UNK_TYPE4 func_8090C884(UNK_TYPE4 param_1, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, short* param_5, int param_6); // func_8090C884
void func_8090C8BC(int* param_1, int param_2); // func_8090C8BC
void func_8090C96C(int param_1, GraphicsContext** param_2); // func_8090C96C
void func_80917290(void); // func_80917290
void func_809172E4(void); // func_809172E4
void func_8091734C(void); // func_8091734C
void func_80917378(void); // func_80917378
void func_80917408(void); // func_80917408
void func_80917538(void); // func_80917538
void func_80917604(void); // func_80917604
void func_8091763C(void); // func_8091763C
void func_8091768C(void); // func_8091768C
void func_809176D0(void); // func_809176D0
void func_8091780C(void); // func_8091780C
void func_80917840(void); // func_80917840
void func_809179A0(void); // func_809179A0
void func_80917AEC(void); // func_80917AEC
void func_80917B44(void); // func_80917B44
void func_80917B9C(void); // func_80917B9C
void func_80917C14(void); // func_80917C14
void func_80917E8C(void); // func_80917E8C
void func_80917F88(void); // func_80917F88
void func_80917FC0(void); // func_80917FC0
void func_809180C8(void); // func_809180C8
void func_80918108(void); // func_80918108
void func_80918314(void); // func_80918314
void func_8091834C(void); // func_8091834C
void func_8091851C(void); // func_8091851C
void func_80918574(void); // func_80918574
void func_80918678(void); // func_80918678
void func_80918700(void); // func_80918700
void func_80918B40(void); // func_80918B40
void func_80918BB8(void); // func_80918BB8
void func_80918D54(void); // func_80918D54
void func_80918D64(void); // func_80918D64
void func_80918FE4(void); // func_80918FE4
void func_80919230(void); // func_80919230
void func_80919744(void); // func_80919744
void func_80919768(void); // func_80919768
void func_809199FC(void); // func_809199FC
void func_80919D68(void); // func_80919D68
void func_80919F30(void); // func_80919F30
void func_80919FC8(void); // func_80919FC8
void func_8091A044(void); // func_8091A044
void func_8091A0B8(void); // func_8091A0B8
void func_8091A124(void); // func_8091A124
void func_8091A2D8(void); // func_8091A2D8
void func_8091A30C(void); // func_8091A30C
void func_8091A5A0(void); // func_8091A5A0
void func_8091A7B0(void); // func_8091A7B0
void func_8091A8A0(void); // func_8091A8A0
void func_8091A8C4(void); // func_8091A8C4
void func_8091A8F4(void); // func_8091A8F4
void func_8091A9E4(void); // func_8091A9E4
void func_8091AA78(void); // func_8091AA78
void func_8091AC4C(void); // func_8091AC4C
void func_8091AC78(void); // func_8091AC78
void func_8091ACC4(void); // func_8091ACC4
void func_8091AE10(void); // func_8091AE10
void func_8091AE5C(void); // func_8091AE5C
void func_8091B030(void); // func_8091B030
void func_8091B07C(void); // func_8091B07C
void func_8091B274(void); // func_8091B274
void func_8091B2D8(void); // func_8091B2D8
void func_8091B3D0(void); // func_8091B3D0
void func_8091B440(void); // func_8091B440
void func_8091B618(void); // func_8091B618
void func_8091B670(void); // func_8091B670
void func_8091B928(void); // func_8091B928
void func_8091B984(void); // func_8091B984
void func_8091BAB4(void); // func_8091BAB4
void func_8091BD04(void); // func_8091BD04
void func_8091C0A0(void); // func_8091C0A0
void func_8091C124(void); // func_8091C124
void func_8091C140(void); // func_8091C140
void func_8091C178(void); // func_8091C178
void func_8091C33C(void); // func_8091C33C
void func_8091C4F8(void); // func_8091C4F8
void func_8091C524(void); // func_8091C524
void func_8091C5EC(void); // func_8091C5EC
void func_8091C6B4(void); // func_8091C6B4
void func_8091C748(void); // func_8091C748
void func_8091C794(void); // func_8091C794
void func_8091CB68(void); // func_8091CB68
void func_8091CBB4(void); // func_8091CBB4
void func_8091CF64(void); // func_8091CF64
void func_8091CFB4(void); // func_8091CFB4
void func_8091D070(void); // func_8091D070
void func_8091D090(void); // func_8091D090
void func_8091D0C0(void); // func_8091D0C0
void func_8091D240(void); // func_8091D240
void func_8091D630(void); // func_8091D630
void func_8091D660(void); // func_8091D660
void func_8091D6C4(void); // func_8091D6C4
void func_8091D728(void); // func_8091D728
void func_8091D7C4(void); // func_8091D7C4
void func_8091D840(void); // func_8091D840
void func_8091D904(void); // func_8091D904
void func_8091D944(void); // func_8091D944
void func_8091DA14(void); // func_8091DA14
void func_8091DA4C(void); // func_8091DA4C
void func_8091DD1C(void); // func_8091DD1C
void func_8091DD48(void); // func_8091DD48
void func_8091DDF4(void); // func_8091DDF4
void func_8091DEE4(void); // func_8091DEE4
void func_8091DF68(void); // func_8091DF68
void func_8091E070(void); // func_8091E070
void func_8091E128(void); // func_8091E128
void func_8091E2E0(void); // func_8091E2E0
void func_8091E34C(void); // func_8091E34C
void func_8091E5EC(void); // func_8091E5EC
void func_8091E658(void); // func_8091E658
void func_8091E810(void); // func_8091E810
void func_8091E880(void); // func_8091E880
void func_8091E9A4(void); // func_8091E9A4
void func_8091EAF0(void); // func_8091EAF0
void func_8091ECF4(void); // func_8091ECF4
void func_8091ED70(void); // func_8091ED70
void func_8091EF30(void); // func_8091EF30
void func_8091EFE8(void); // func_8091EFE8
void func_8091F344(void); // func_8091F344
void func_8091F3BC(void); // func_8091F3BC
void func_8091F5A4(void); // func_8091F5A4
void func_8091F830(void); // func_8091F830
void func_8091F940(void); // func_8091F940
void func_8091F994(void); // func_8091F994
void func_8091F9A4(void); // func_8091F9A4
void func_8091FEF0(void); // func_8091FEF0
void func_8091FEFC(void); // func_8091FEFC
void func_80920034(void); // func_80920034
void func_80920044(void); // func_80920044
void func_8092009C(void); // func_8092009C
void func_809200F8(void); // func_809200F8
void func_80920140(void); // func_80920140
void func_80920164(void); // func_80920164
void func_809201BC(void); // func_809201BC
void FireArrow_SetUpdateFunc(ActorArrowFire* this, actor_func update); // func_80920340
void ArrowFire_Init(ActorArrowFire* this, GlobalContext* ctxt); // func_8092034C
void ArrowFire_Fini(ActorArrowFire* this, GlobalContext* ctxt); // func_809203F8
void FireArrow_Update1(ActorArrowFire* pzParm1); // func_80920440
void FireArrow_Lerp(Vector3f* a, Vector3f* b, f32 t); // func_80920534
void FireArrow_Update3(ActorArrowFire* this, GlobalContext* ctxt); // func_8092058C
void FireArrow_Update2(ActorArrowFire* param_1); // func_809207A0
void ArrowFire_Main(ActorArrowFire* this, GlobalContext* ctxt); // func_809208F4
void func_80920948(ActorArrowFire* this); // func_80920948
void ArrowFire_Draw(ActorArrowFire* this, GlobalContext* ctxt); // func_80920A24
void func_80922430(void); // func_80922430
void func_8092243C(void); // func_8092243C
void func_809224B8(void); // func_809224B8
void func_809224DC(void); // func_809224DC
void func_809225D0(void); // func_809225D0
void func_80922628(void); // func_80922628
void func_809227F4(void); // func_809227F4
void func_80922948(void); // func_80922948
void func_8092299C(void); // func_8092299C
void func_80924300(void); // func_80924300
void func_8092430C(void); // func_8092430C
void func_80924388(void); // func_80924388
void func_809243AC(void); // func_809243AC
void func_809244A0(void); // func_809244A0
void func_809244F8(void); // func_809244F8
void func_809246C4(void); // func_809246C4
void func_80924818(void); // func_80924818
void func_8092486C(void); // func_8092486C
void func_809261B0(void); // func_809261B0
void func_80926224(void); // func_80926224
void func_809262BC(void); // func_809262BC
void func_80926318(void); // func_80926318
void func_80926394(void); // func_80926394
void func_809263C8(void); // func_809263C8
void func_809264E0(void); // func_809264E0
void func_8092650C(void); // func_8092650C
void func_809267EC(void); // func_809267EC
void func_80926B40(void); // func_80926B40
void func_80926B54(void); // func_80926B54
void func_80926BE0(void); // func_80926BE0
void func_80926BF4(void); // func_80926BF4
void func_80926EF4(void); // func_80926EF4
void func_80926F08(void); // func_80926F08
void func_8092703C(void); // func_8092703C
void func_809270F8(void); // func_809270F8
void func_80927304(void); // func_80927304
void func_80927334(void); // func_80927334
void func_809275C0(void); // func_809275C0
void func_8092762C(void); // func_8092762C
void func_80927690(void); // func_80927690
void func_80927714(void); // func_80927714
void func_8092776C(void); // func_8092776C
void func_80927818(void); // func_80927818
void func_80927864(void); // func_80927864
void func_8092788C(void); // func_8092788C
void func_809278C0(void); // func_809278C0
void func_80927A4C(void); // func_80927A4C
void func_80927A78(void); // func_80927A78
void func_80927D2C(void); // func_80927D2C
void func_80927FCC(void); // func_80927FCC
void func_809282F0(void); // func_809282F0
void func_8092860C(void); // func_8092860C
void func_80928904(void); // func_80928904
void func_80928914(void); // func_80928914
void func_80928928(void); // func_80928928
void func_809289B4(void); // func_809289B4
void func_809289E4(void); // func_809289E4
void func_80928D6C(void); // func_80928D6C
void func_80928D80(void); // func_80928D80
void func_80928E74(void); // func_80928E74
void func_80928F18(void); // func_80928F18
void func_809291DC(void); // func_809291DC
void func_8092926C(void); // func_8092926C
void func_8092932C(void); // func_8092932C
void func_809294B0(void); // func_809294B0
void func_80929910(void); // func_80929910
void func_80929A98(void); // func_80929A98
void func_80929AF8(void); // func_80929AF8
void func_80929B6C(void); // func_80929B6C
void func_80929BEC(void); // func_80929BEC
void func_80929C80(void); // func_80929C80
void func_80929D04(void); // func_80929D04
void func_80929E2C(void); // func_80929E2C
void func_80929E88(void); // func_80929E88
void func_80929F20(void); // func_80929F20
void func_80929FC8(void); // func_80929FC8
void func_8092A020(void); // func_8092A020
void func_8092A124(void); // func_8092A124
void func_8092A188(void); // func_8092A188
void func_8092A28C(void); // func_8092A28C
void func_8092A33C(void); // func_8092A33C
void func_8092A570(void); // func_8092A570
void func_8092A5BC(void); // func_8092A5BC
void func_8092A680(void); // func_8092A680
void func_8092A754(void); // func_8092A754
void func_8092A8D8(void); // func_8092A8D8
void func_8092A994(void); // func_8092A994
void func_8092AA6C(void); // func_8092AA6C
void func_8092AB14(void); // func_8092AB14
void func_8092AB50(void); // func_8092AB50
void func_8092ABD8(void); // func_8092ABD8
void func_8092AC4C(void); // func_8092AC4C
void func_8092ACFC(void); // func_8092ACFC
void func_8092ADB4(void); // func_8092ADB4
void func_8092AE14(void); // func_8092AE14
void func_8092AFB4(void); // func_8092AFB4
void func_8092AFD4(void); // func_8092AFD4
void func_8092B03C(void); // func_8092B03C
void func_8092B098(void); // func_8092B098
void func_8092B1B4(void); // func_8092B1B4
void func_8092B46C(void); // func_8092B46C
void func_8092B5FC(void); // func_8092B5FC
void func_8092B900(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8092B900
void func_8092B93C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8092B93C
void func_8092BC6C(void); // func_8092BC6C
void func_8092BE14(void); // func_8092BE14
void func_8092C530(void); // func_8092C530
void func_8092C540(void); // func_8092C540
void func_8092C550(void); // func_8092C550
void func_8092C560(void); // func_8092C560
void func_8092C5C0(void); // func_8092C5C0
void func_8092C63C(void); // func_8092C63C
void func_8092C6FC(void); // func_8092C6FC
void func_8092C740(void); // func_8092C740
void func_8092C86C(void); // func_8092C86C
void func_8092C934(void); // func_8092C934
void func_8092C9BC(void); // func_8092C9BC
void func_8092CA74(void); // func_8092CA74
UNK_TYPE4 func_8092CAD0(s32 param_1, UNK_TYPE4 param_2); // func_8092CAD0
UNK_TYPE4 func_8092CB98(s32 param_1, s32 param_2); // func_8092CB98
void func_8092CC68(void); // func_8092CC68
void func_8092CCEC(void); // func_8092CCEC
void func_8092CE38(void); // func_8092CE38
void func_8092D068(void); // func_8092D068
void func_8092D108(void); // func_8092D108
void func_8092D1B8(s32 param_1, s32 param_2); // func_8092D1B8
void func_8092D320(void); // func_8092D320
void func_8092D330(void); // func_8092D330
void func_8092D4D8(s32 param_1, UNK_TYPE4 param_2); // func_8092D4D8
void func_8092D5E8(void); // func_8092D5E8
void func_8092D6C0(Actor* param_1, UNK_TYPE4 param_2); // func_8092D6C0
void func_8092D820(void); // func_8092D820
void func_8092D84C(void); // func_8092D84C
void func_8092D954(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8092D954
void func_8092DA68(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_8092DA68
void func_8092DA94(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8092DA94
void func_8092DBE0(void); // func_8092DBE0
void func_8092DF90(void); // func_8092DF90
void func_8092DF9C(void); // func_8092DF9C
void func_8092E0D4(void); // func_8092E0D4
void func_8092E1C0(void); // func_8092E1C0
void func_8092E1D0(void); // func_8092E1D0
void func_8092E1FC(void); // func_8092E1FC
void func_8092E284(void); // func_8092E284
void func_8092E38C(void); // func_8092E38C
void func_8092E510(void); // func_8092E510
void func_8092E5A4(void); // func_8092E5A4
void func_8092E638(void); // func_8092E638
void func_8092E840(void); // func_8092E840
void func_8092E988(void); // func_8092E988
void func_8092EA98(void); // func_8092EA98
void func_8092EB6C(void); // func_8092EB6C
void func_8092EBC0(void); // func_8092EBC0
void func_8092EBDC(void); // func_8092EBDC
void func_8092EC9C(void); // func_8092EC9C
void func_8092ECF0(void); // func_8092ECF0
void func_8092EDC0(void); // func_8092EDC0
void func_8092EDD8(void); // func_8092EDD8
void func_8092EE08(void); // func_8092EE08
void func_8092EE1C(void); // func_8092EE1C
void func_8092EE68(void); // func_8092EE68
void func_8092EE90(void); // func_8092EE90
void func_8092EF3C(void); // func_8092EF3C
void func_8092EF98(void); // func_8092EF98
void func_8092F05C(void); // func_8092F05C
void func_8092F074(void); // func_8092F074
void func_8092F0A4(void); // func_8092F0A4
void func_8092F0B8(void); // func_8092F0B8
void func_8092F0F8(void); // func_8092F0F8
void func_8092F10C(void); // func_8092F10C
void func_8092F1A0(void); // func_8092F1A0
void func_8092F208(void); // func_8092F208
void func_8092F34C(void); // func_8092F34C
void func_8092F3D8(void); // func_8092F3D8
void func_8092F5AC(void); // func_8092F5AC
void func_8092F5EC(void); // func_8092F5EC
void func_8092F7A8(void); // func_8092F7A8
void func_8092F7BC(void); // func_8092F7BC
void func_8092F854(void); // func_8092F854
void func_8092F878(void); // func_8092F878
void func_8092FD6C(void); // func_8092FD6C
void func_8092FE44(void); // func_8092FE44
void func_8092FEFC(void); // func_8092FEFC
void func_8092FF70(void); // func_8092FF70
void func_80930030(void); // func_80930030
void func_80930190(void); // func_80930190
void func_809307E0(void); // func_809307E0
void func_80930870(void); // func_80930870
void func_8093089C(void); // func_8093089C
void func_809308F4(void); // func_809308F4
void func_80930B60(void); // func_80930B60
void func_80930DDC(void); // func_80930DDC
void func_80931004(void); // func_80931004
void func_80931138(void); // func_80931138
void func_809311C4(void); // func_809311C4
void func_80931290(void); // func_80931290
void func_809313D8(void); // func_809313D8
void func_80931560(void); // func_80931560
void func_809317A4(void); // func_809317A4
void func_80931828(void); // func_80931828
void func_80931A38(void); // func_80931A38
void func_80931E58(void); // func_80931E58
void func_80931EEC(void); // func_80931EEC
void func_80932198(void); // func_80932198
void func_809321BC(void); // func_809321BC
void func_80932490(void); // func_80932490
void func_809326F4(void); // func_809326F4
void func_80932784(void); // func_80932784
void func_809328A4(void); // func_809328A4
void func_809328F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809328F4
void func_80932AE8(void); // func_80932AE8
void func_80932AF4(void); // func_80932AF4
void func_80932BD4(void); // func_80932BD4
void func_80932C98(void); // func_80932C98
void func_80933014(void); // func_80933014
void func_809330D4(void); // func_809330D4
void func_80933104(void); // func_80933104
void func_80933184(void); // func_80933184
void func_809331F8(void); // func_809331F8
void func_80933248(void); // func_80933248
void func_80933274(void); // func_80933274
void func_80933324(void); // func_80933324
void func_80933368(void); // func_80933368
void func_809333A4(void); // func_809333A4
void func_809333D8(void); // func_809333D8
void func_80933414(void); // func_80933414
void func_80933444(void); // func_80933444
void func_80933480(void); // func_80933480
void func_809334B8(void); // func_809334B8
void func_809336C0(void); // func_809336C0
void func_80933760(void); // func_80933760
void func_80933790(void); // func_80933790
void func_809337D4(void); // func_809337D4
void func_8093389C(void); // func_8093389C
void func_809338E0(void); // func_809338E0
void func_80933AF4(void); // func_80933AF4
void func_80933B38(void); // func_80933B38
void func_80933B48(void); // func_80933B48
void func_80933BFC(void); // func_80933BFC
void func_80933D98(void); // func_80933D98
void func_80934018(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80934018
void func_809340BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE1 param_8); // func_809340BC
void func_80934178(void); // func_80934178
void func_80934464(void); // func_80934464
void func_809349E0(void); // func_809349E0
void func_80934AB4(void); // func_80934AB4
void func_80934F58(void); // func_80934F58
void func_80934FFC(void); // func_80934FFC
void func_809350C4(void); // func_809350C4
void func_809350F8(void); // func_809350F8
void func_8093517C(void); // func_8093517C
void func_809351A0(void); // func_809351A0
void func_809354F8(void); // func_809354F8
void func_809355A4(void); // func_809355A4
void func_8093561C(void); // func_8093561C
void func_80935674(void); // func_80935674
void func_80935898(void); // func_80935898
void func_809358C4(void); // func_809358C4
void func_809358D8(void); // func_809358D8
void func_80935988(void); // func_80935988
void func_809359AC(void); // func_809359AC
void func_80935B94(void); // func_80935B94
void func_80935BBC(void); // func_80935BBC
void func_80935CE8(void); // func_80935CE8
void func_80935D64(void); // func_80935D64
void func_80936120(void); // func_80936120
void func_80936168(void); // func_80936168
void func_809361A4(void); // func_809361A4
void func_809361B4(void); // func_809361B4
void func_80936220(void); // func_80936220
void func_80936290(void); // func_80936290
void func_809362D8(void); // func_809362D8
void func_80936370(void); // func_80936370
void func_80936414(void); // func_80936414
void func_809365CC(void); // func_809365CC
void func_80936CF0(void); // func_80936CF0
void func_80936D58(void); // func_80936D58
void func_80936F04(void); // func_80936F04
void func_80936F24(void); // func_80936F24
void func_80937130(void); // func_80937130
void func_80937160(void); // func_80937160
void func_80937238(void); // func_80937238
void func_80937268(void); // func_80937268
void func_809372A8(void); // func_809372A8
void func_809372D0(void); // func_809372D0
void func_80937468(void); // func_80937468
void func_809374F8(void); // func_809374F8
void func_809375C8(void); // func_809375C8
void func_809375F4(void); // func_809375F4
void func_80937864(void); // func_80937864
void func_80937B0C(void); // func_80937B0C
void func_80937B54(void); // func_80937B54
void func_80937C10(void); // func_80937C10
void func_80937C24(void); // func_80937C24
void func_80937C30(void); // func_80937C30
void func_80937CA0(void); // func_80937CA0
void func_80937CE4(void); // func_80937CE4
void func_80937D54(void); // func_80937D54
void func_80937DD8(void); // func_80937DD8
void func_80937DEC(void); // func_80937DEC
void func_80937FB0(void); // func_80937FB0
void func_80937FC8(void); // func_80937FC8
void func_809381B0(void); // func_809381B0
void func_809381C4(void); // func_809381C4
void func_80938284(void); // func_80938284
void func_80938298(void); // func_80938298
void func_8093833C(void); // func_8093833C
void func_80938358(void); // func_80938358
void func_809383B4(void); // func_809383B4
void func_809383D0(void); // func_809383D0
void func_80938408(void); // func_80938408
void func_80938444(void); // func_80938444
void func_809384E8(void); // func_809384E8
void func_80938504(void); // func_80938504
void func_80938588(void); // func_80938588
void func_809385A8(void); // func_809385A8
void func_80938670(void); // func_80938670
void func_8093868C(void); // func_8093868C
void func_80938704(void); // func_80938704
void func_80938728(void); // func_80938728
void func_8093876C(void); // func_8093876C
void func_80938780(void); // func_80938780
void func_80938804(void); // func_80938804
void func_80938834(void); // func_80938834
void func_80938874(void); // func_80938874
void func_809388A8(void); // func_809388A8
void func_8093892C(void); // func_8093892C
void func_80938958(void); // func_80938958
void func_80938998(void); // func_80938998
void func_809389BC(void); // func_809389BC
void func_80938A14(void); // func_80938A14
void func_80938A5C(void); // func_80938A5C
void func_80938AA4(void); // func_80938AA4
void func_80938AD8(void); // func_80938AD8
void func_80938C1C(void); // func_80938C1C
void func_80938C8C(void); // func_80938C8C
void func_80938E00(void); // func_80938E00
void func_80938F50(void); // func_80938F50
void func_809393B0(void); // func_809393B0
void func_80939470(void); // func_80939470
void func_8093951C(void); // func_8093951C
void func_80939594(void); // func_80939594
void func_809395FC(void); // func_809395FC
void func_80939768(void); // func_80939768
void func_80939794(void); // func_80939794
void func_80939994(void); // func_80939994
void func_80939C50(void); // func_80939C50
void func_80939EE0(void); // func_80939EE0
void func_80939EF4(void); // func_80939EF4
void func_8093A080(void); // func_8093A080
void func_8093A1F0(void); // func_8093A1F0
void func_8093A3F4(void); // func_8093A3F4
void func_8093A418(void); // func_8093A418
void func_8093A608(void); // func_8093A608
void func_8093ABD0(void); // func_8093ABD0
void func_8093AC6C(void); // func_8093AC6C
void func_8093ADA8(void); // func_8093ADA8
void func_8093AE1C(void); // func_8093AE1C
void func_8093AE74(void); // func_8093AE74
void func_8093AE88(void); // func_8093AE88
void func_8093AEC4(void); // func_8093AEC4
void func_8093AEF0(void); // func_8093AEF0
void func_8093AF1C(void); // func_8093AF1C
void func_8093AF54(void); // func_8093AF54
void func_8093B084(void); // func_8093B084
void func_8093B59C(void); // func_8093B59C
void func_8093B648(void); // func_8093B648
void func_8093B668(void); // func_8093B668
void func_8093B6F4(void); // func_8093B6F4
void func_8093B710(void); // func_8093B710
void func_8093B92C(void); // func_8093B92C
void func_8093B940(void); // func_8093B940
void func_8093B9C0(void); // func_8093B9C0
void func_8093B9E4(void); // func_8093B9E4
void func_8093BB5C(void); // func_8093BB5C
void func_8093BB70(void); // func_8093BB70
void func_8093BBD0(void); // func_8093BBD0
void func_8093BCC8(void); // func_8093BCC8
void func_8093BCDC(void); // func_8093BCDC
void func_8093BD34(void); // func_8093BD34
void func_8093BD4C(void); // func_8093BD4C
void func_8093BDAC(void); // func_8093BDAC
void func_8093BDC0(void); // func_8093BDC0
void func_8093BE10(void); // func_8093BE10
void func_8093BE2C(void); // func_8093BE2C
void func_8093BEF0(void); // func_8093BEF0
void func_8093BF04(void); // func_8093BF04
void func_8093BF50(void); // func_8093BF50
void func_8093BF70(void); // func_8093BF70
void func_8093C0A4(void); // func_8093C0A4
void func_8093C0B8(void); // func_8093C0B8
void func_8093C138(void); // func_8093C138
void func_8093C15C(void); // func_8093C15C
void func_8093C23C(void); // func_8093C23C
void func_8093C250(void); // func_8093C250
void func_8093C2B4(void); // func_8093C2B4
void func_8093C2D4(void); // func_8093C2D4
void func_8093C3C8(void); // func_8093C3C8
void func_8093C3DC(void); // func_8093C3DC
void func_8093C460(void); // func_8093C460
void func_8093C488(void); // func_8093C488
void func_8093C584(void); // func_8093C584
void func_8093C598(void); // func_8093C598
void func_8093C5FC(void); // func_8093C5FC
void func_8093C778(void); // func_8093C778
void func_8093C888(void); // func_8093C888
void func_8093C8B8(void); // func_8093C8B8
void func_8093C99C(void); // func_8093C99C
void func_8093CA80(void); // func_8093CA80
void func_8093CAC4(void); // func_8093CAC4
void func_8093CC24(void); // func_8093CC24
void func_8093D3C0(void); // func_8093D3C0
void func_8093D628(void); // func_8093D628
void func_8093D72C(void); // func_8093D72C
void func_8093D760(void); // func_8093D760
void func_8093D7A0(void); // func_8093D7A0
void func_8093D88C(void); // func_8093D88C
void func_8093D8B4(void); // func_8093D8B4
void func_8093D9C0(void); // func_8093D9C0
void func_8093DA48(void); // func_8093DA48
void func_8093DB70(void); // func_8093DB70
void func_8093DB90(void); // func_8093DB90
void func_8093DC2C(void); // func_8093DC2C
void func_8093DC60(void); // func_8093DC60
void func_8093DC90(void); // func_8093DC90
void func_8093DEA0(void); // func_8093DEA0
void func_8093DEAC(void); // func_8093DEAC
void func_8093DF30(void); // func_8093DF30
void func_8093E008(void); // func_8093E008
void func_8093E03C(void); // func_8093E03C
void func_8093E05C(void); // func_8093E05C
void func_8093E0A0(void); // func_8093E0A0
void func_8093E0E8(void); // func_8093E0E8
void func_8093E10C(void); // func_8093E10C
void func_8093E1B4(void); // func_8093E1B4
void func_8093E200(void); // func_8093E200
void func_8093E420(void); // func_8093E420
void func_8093E430(void); // func_8093E430
void func_8093E518(void); // func_8093E518
void func_8093E68C(void); // func_8093E68C
void func_8093E7E4(void); // func_8093E7E4
void func_8093E8A0(void); // func_8093E8A0
void func_8093E91C(void); // func_8093E91C
void func_8093E938(void); // func_8093E938
void func_8093E9B0(void); // func_8093E9B0
void func_8093EAB0(void); // func_8093EAB0
void func_8093EAD4(void); // func_8093EAD4
void func_8093EB58(void); // func_8093EB58
void func_8093EB74(void); // func_8093EB74
void func_8093EC50(void); // func_8093EC50
void func_8093ECD4(void); // func_8093ECD4
void func_8093ED80(void); // func_8093ED80
void func_8093EDB0(void); // func_8093EDB0
void func_8093EDD8(void); // func_8093EDD8
void func_8093EE18(void); // func_8093EE18
void func_8093EE64(void); // func_8093EE64
void func_8093EEBC(void); // func_8093EEBC
void func_8093EEDC(void); // func_8093EEDC
void func_8093EF54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8093EF54
void func_8093F198(void); // func_8093F198
void func_8093F34C(void); // func_8093F34C
void func_8093F498(void); // func_8093F498
void func_8093F5EC(void); // func_8093F5EC
void func_8093F6F8(void); // func_8093F6F8
void func_8093FAA4(void); // func_8093FAA4
void func_8093FC00(void); // func_8093FC00
void func_8093FC6C(void); // func_8093FC6C
void func_80940090(void); // func_80940090
void func_80940588(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80940588
void func_80940A1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80940A1C
void func_80940E38(void); // func_80940E38
void func_80941060(void); // func_80941060
void func_80941274(void); // func_80941274
void func_809412AC(void); // func_809412AC
void func_8094152C(void); // func_8094152C
void func_8094156C(void); // func_8094156C
void func_809419D0(void); // func_809419D0
void func_80941A10(void); // func_80941A10
void func_80941DB4(void); // func_80941DB4
void func_80941E28(void); // func_80941E28
void func_80941EB4(void); // func_80941EB4
void func_80941F10(void); // func_80941F10
void func_80941F54(void); // func_80941F54
void func_80941FA4(void); // func_80941FA4
void func_80942084(void); // func_80942084
void func_809420F0(void); // func_809420F0
void func_809421E0(void); // func_809421E0
void func_8094220C(void); // func_8094220C
void func_809425CC(void); // func_809425CC
void func_80942604(void); // func_80942604
void func_80942668(void); // func_80942668
void func_80942B1C(void); // func_80942B1C
void func_80942D34(void); // func_80942D34
void func_809434B0(void); // func_809434B0
void func_80943710(void); // func_80943710
void func_8094373C(void); // func_8094373C
void func_809437C8(void); // func_809437C8
void func_80943820(void); // func_80943820
void func_809438F8(void); // func_809438F8
void func_80943BC0(void); // func_80943BC0
void func_80943BDC(void); // func_80943BDC
void func_80943CA4(void); // func_80943CA4
void func_80943E18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80943E18
void func_80943E60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80943E60
void func_80943EE4(void); // func_80943EE4
void func_809441E0(void); // func_809441E0
void func_80944310(void); // func_80944310
void func_80944320(void); // func_80944320
void func_80944554(void); // func_80944554
void func_80944590(void); // func_80944590
void func_809445D4(void); // func_809445D4
void func_80944630(void); // func_80944630
void func_809447A8(void); // func_809447A8
void func_80944818(void); // func_80944818
void func_809448A4(void); // func_809448A4
void func_809449D0(void); // func_809449D0
void func_80944A50(void); // func_80944A50
void func_80944E44(void); // func_80944E44
void func_80944EFC(void); // func_80944EFC
void func_80944FA8(void); // func_80944FA8
void func_8094506C(void); // func_8094506C
void func_809450C0(void); // func_809450C0
void func_809451D8(void); // func_809451D8
void func_8094529C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8094529C
void func_80945310(void); // func_80945310
void func_809454F0(void); // func_809454F0
void func_80945524(void); // func_80945524
void func_80945534(void); // func_80945534
void func_8094557C(void); // func_8094557C
void func_809455A0(void); // func_809455A0
void func_80945650(void); // func_80945650
void func_809457C0(void); // func_809457C0
void func_809457EC(void); // func_809457EC
void func_80945924(void); // func_80945924
void func_80945A00(void); // func_80945A00
void func_80945A9C(void); // func_80945A9C
void func_80945B60(void); // func_80945B60
void func_80945C50(void); // func_80945C50
void func_80945CAC(void); // func_80945CAC
void func_80945CE4(void); // func_80945CE4
void func_8094607C(void); // func_8094607C
void func_80946190(void); // func_80946190
void func_80946238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80946238
void func_80946368(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80946368
void func_80946400(void); // func_80946400
void func_809466A0(void); // func_809466A0
void func_809466F0(void); // func_809466F0
void func_809467E8(void); // func_809467E8
void func_8094685C(void); // func_8094685C
void func_809468D0(void); // func_809468D0
void func_809468E0(void); // func_809468E0
void func_809468F0(void); // func_809468F0
void func_8094692C(void); // func_8094692C
void func_809469C0(void); // func_809469C0
void func_8094702C(void); // func_8094702C
void func_80947668(void); // func_80947668
void func_80947F60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80947F60
void func_809480C8(void); // func_809480C8
void func_80948264(void); // func_80948264
void func_809484EC(void); // func_809484EC
void func_809485A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_809485A8
void func_80948788(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_80948788
void func_8094899C(void); // func_8094899C
void func_80948A54(void); // func_80948A54
void func_80948BB4(void); // func_80948BB4
void func_80948BC4(void); // func_80948BC4
void func_80949288(void); // func_80949288
void func_80949570(void); // func_80949570
void func_809495D8(void); // func_809495D8
void func_809495F8(void); // func_809495F8
void func_80949BD4(void); // func_80949BD4
void func_8094DEE0(void); // func_8094DEE0
void func_8094DF90(void); // func_8094DF90
void func_8094DFF8(void); // func_8094DFF8
void func_8094E054(void); // func_8094E054
void func_8094E0F8(void); // func_8094E0F8
void func_8094E1DC(void); // func_8094E1DC
void func_8094E278(void); // func_8094E278
void func_8094E2D0(void); // func_8094E2D0
void func_8094E454(void); // func_8094E454
void func_8094E4D0(void); // func_8094E4D0
void func_8094E52C(void); // func_8094E52C
void func_8094E69C(void); // func_8094E69C
void func_8094EA34(void); // func_8094EA34
void func_8094EB1C(void); // func_8094EB1C
void func_8094EDBC(void); // func_8094EDBC
UNK_TYPE4 func_8094EE84(s32 param_1, UNK_TYPE4 param_2); // func_8094EE84
void func_8094EFC4(void); // func_8094EFC4
void func_8094F074(void); // func_8094F074
void func_8094F0E0(void); // func_8094F0E0
void func_8094F2E8(void); // func_8094F2E8
void func_8094F3D0(void); // func_8094F3D0
void func_8094F4EC(void); // func_8094F4EC
void func_8094F53C(void); // func_8094F53C
void func_8094F7D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_8094F7D0
void func_8094F904(void); // func_8094F904
UNK_TYPE4 func_8094FAC4(s32 param_1, UNK_TYPE4 param_2, u8* param_3); // func_8094FAC4
UNK_TYPE4 func_8094FCC4(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_8094FCC4
u32 func_8094FD88(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_8094FD88
UNK_TYPE4 func_8094FE10(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3); // func_8094FE10
UNK_TYPE4 func_8094FF04(s32 param_1, UNK_TYPE4 param_2, u8* param_3); // func_8094FF04
UNK_TYPE4 func_80950088(s32 param_1, UNK_TYPE4 param_2); // func_80950088
UNK_TYPE4 func_80950120(s32 param_1, UNK_TYPE4 param_2); // func_80950120
void func_809501B8(void); // func_809501B8
void func_80950280(void); // func_80950280
void func_80950388(void); // func_80950388
UNK_TYPE4 func_809503F8(s32 param_1, UNK_TYPE4 param_2); // func_809503F8
void func_80950490(void); // func_80950490
void func_80950690(void); // func_80950690
void func_80950804(void); // func_80950804
void func_8095097C(void); // func_8095097C
void func_80950C24(void); // func_80950C24
void func_80950CDC(void); // func_80950CDC
void func_80950DB8(void); // func_80950DB8
void func_80950F2C(void); // func_80950F2C
void func_809510E4(void); // func_809510E4
void func_80951224(void); // func_80951224
void func_80951264(void); // func_80951264
void func_809513AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809513AC
void func_809514BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809514BC
void func_80951594(void); // func_80951594
void func_80951748(void); // func_80951748
void func_80952620(void); // func_80952620
void func_80952708(void); // func_80952708
void func_80952734(void); // func_80952734
void func_809527F8(void); // func_809527F8
void func_809529AC(void); // func_809529AC
void func_80952A1C(void); // func_80952A1C
void func_80952A8C(void); // func_80952A8C
void func_80952B24(void); // func_80952B24
void func_80952C50(void); // func_80952C50
void func_80952CC8(void); // func_80952CC8
void func_80952DD0(void); // func_80952DD0
void func_80952DFC(void); // func_80952DFC
void func_80952E50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80952E50
void func_80952F00(void); // func_80952F00
void func_80952FE0(void); // func_80952FE0
void func_80953098(void); // func_80953098
void func_80953180(void); // func_80953180
void func_809532C0(void); // func_809532C0
void func_809532D0(void); // func_809532D0
void func_80953354(void); // func_80953354
void func_809533A0(void); // func_809533A0
void func_8095345C(void); // func_8095345C
void func_8095359C(void); // func_8095359C
void func_8095376C(void); // func_8095376C
void func_80953848(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80953848
void func_80953888(void); // func_80953888
void func_80953A90(void); // func_80953A90
void func_80953B40(void); // func_80953B40
void func_80953BEC(void); // func_80953BEC
void func_80953DA8(void); // func_80953DA8
void func_80953E38(void); // func_80953E38
void func_80953EA4(void); // func_80953EA4
void func_80953F14(void); // func_80953F14
void func_80953F8C(void); // func_80953F8C
void func_80953F9C(void); // func_80953F9C
void func_809541B8(void); // func_809541B8
void func_809542A0(void); // func_809542A0
void func_80954340(void); // func_80954340
void func_809543D4(void); // func_809543D4
void func_809545A0(void); // func_809545A0
void func_809547A8(void); // func_809547A8
void func_809547E4(void); // func_809547E4
void func_80954808(void); // func_80954808
void func_80954960(void); // func_80954960
void func_80954A1C(void); // func_80954A1C
void func_80954BB0(void); // func_80954BB0
void func_80954BE8(void); // func_80954BE8
void func_80954CA0(void); // func_80954CA0
void func_80956954(void); // func_80956954
void func_809580C0(void); // func_809580C0
void func_809581F4(void); // func_809581F4
void func_80958228(void); // func_80958228
void func_809585B0(void); // func_809585B0
void func_80958634(void); // func_80958634
void func_80958974(void); // func_80958974
void func_80958BE4(void); // func_80958BE4
void func_80958CA8(void); // func_80958CA8
void func_80958F6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80958F6C
void func_8095909C(void); // func_8095909C
void func_809592E0(void); // func_809592E0
void func_80959390(void); // func_80959390
void func_809594F8(void); // func_809594F8
void func_80959524(void); // func_80959524
void func_8095954C(void); // func_8095954C
void func_809595D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_809595D0
void func_80959624(void); // func_80959624
void func_809596A0(void); // func_809596A0
void func_80959774(void); // func_80959774
void func_80959844(void); // func_80959844
void func_80959A24(void); // func_80959A24
void func_80959C94(void); // func_80959C94
void func_80959D28(void); // func_80959D28
void func_80959E18(void); // func_80959E18
void func_8095A028(void); // func_8095A028
void func_8095A150(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8095A150
void func_8095A198(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8095A198
void func_8095A1D8(void); // func_8095A1D8
void func_8095A510(void); // func_8095A510
void func_8095A560(void); // func_8095A560
void func_8095A8DC(void); // func_8095A8DC
void func_8095A920(void); // func_8095A920
void func_8095A978(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8095A978
void func_8095A9FC(void); // func_8095A9FC
void func_8095AA70(void); // func_8095AA70
void func_8095AAD0(void); // func_8095AAD0
void func_8095AB1C(void); // func_8095AB1C
void func_8095AB4C(void); // func_8095AB4C
void func_8095ABA8(void); // func_8095ABA8
void func_8095ABF0(void); // func_8095ABF0
void func_8095AC50(void); // func_8095AC50
void func_8095ACEC(void); // func_8095ACEC
void func_8095AD54(void); // func_8095AD54
void func_8095AE00(void); // func_8095AE00
void func_8095AE60(void); // func_8095AE60
void func_8095AEC0(void); // func_8095AEC0
void func_8095AF2C(void); // func_8095AF2C
void func_8095AFEC(void); // func_8095AFEC
void func_8095B06C(void); // func_8095B06C
void func_8095B0C8(void); // func_8095B0C8
void func_8095B158(void); // func_8095B158
void func_8095B1E4(void); // func_8095B1E4
void func_8095B254(void); // func_8095B254
void func_8095B2F8(void); // func_8095B2F8
void func_8095B3DC(void); // func_8095B3DC
void func_8095B480(void); // func_8095B480
void func_8095B574(void); // func_8095B574
void func_8095B650(void); // func_8095B650
void func_8095B6C8(void); // func_8095B6C8
void func_8095B76C(void); // func_8095B76C
void func_8095B960(void); // func_8095B960
void func_8095B9FC(void); // func_8095B9FC
void func_8095BA84(void); // func_8095BA84
void func_8095BE0C(void); // func_8095BE0C
void func_8095BF20(void); // func_8095BF20
void func_8095BF58(void); // func_8095BF58
void func_8095BF78(void); // func_8095BF78
void func_8095C09C(void); // func_8095C09C
void func_8095C1C8(void); // func_8095C1C8
void func_8095C258(void); // func_8095C258
void func_8095C328(void); // func_8095C328
void func_8095C408(void); // func_8095C408
void func_8095C484(void); // func_8095C484
void func_8095C510(void); // func_8095C510
void func_8095C568(void); // func_8095C568
void func_8095C654(void); // func_8095C654
void func_8095CCF4(void); // func_8095CCF4
void func_8095CE18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8095CE18
void func_8095CF44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8095CF44
void func_8095CFC8(void); // func_8095CFC8
void func_8095D074(void); // func_8095D074
void func_8095D24C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8095D24C
void func_8095D6E0(void); // func_8095D6E0
void func_8095D758(void); // func_8095D758
void func_8095D804(void); // func_8095D804
void func_8095DABC(void); // func_8095DABC
void func_8095DDA8(void); // func_8095DDA8
void func_8095DE9C(void); // func_8095DE9C
void func_8095DF90(void); // func_8095DF90
void func_8095DFF0(void); // func_8095DFF0
void func_8095E14C(void); // func_8095E14C
void func_8095E180(void); // func_8095E180
void func_8095E204(void); // func_8095E204
void func_8095E2B0(void); // func_8095E2B0
void func_8095E328(void); // func_8095E328
void func_8095E580(void); // func_8095E580
void func_8095E5AC(void); // func_8095E5AC
void func_8095E5C0(void); // func_8095E5C0
void func_8095E64C(void); // func_8095E64C
void func_8095E660(void); // func_8095E660
void func_8095E8CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_8095E8CC
void func_8095E934(void); // func_8095E934
void func_8095E95C(void); // func_8095E95C
void func_8095EA70(void); // func_8095EA70
void func_8095EBDC(void); // func_8095EBDC
void func_8095F060(void); // func_8095F060
void func_8095F0A4(void); // func_8095F0A4
void func_8095F180(void); // func_8095F180
void func_8095F194(void); // func_8095F194
void func_8095F1EC(void); // func_8095F1EC
void func_8095F210(void); // func_8095F210
void func_8095F36C(void); // func_8095F36C
void func_8095F61C(void); // func_8095F61C
void func_8095F654(void); // func_8095F654
void func_8095FB10(void); // func_8095FB10
void func_8095FB38(void); // func_8095FB38
void func_8095FB48(void); // func_8095FB48
void func_8095FB58(void); // func_8095FB58
void func_8095FBF0(void); // func_8095FBF0
void func_8095FC94(void); // func_8095FC94
void func_8095FCEC(void); // func_8095FCEC
void func_8095FEEC(void); // func_8095FEEC
void func_8095FFCC(void); // func_8095FFCC
void func_8095FFF8(void); // func_8095FFF8
void func_80960014(void); // func_80960014
void func_80960088(void); // func_80960088
void func_809600BC(void); // func_809600BC
void func_8096012C(s32 param_1); // func_8096012C
void func_80960148(void); // func_80960148
void func_80960224(void); // func_80960224
void func_80960260(void); // func_80960260
void func_8096034C(void); // func_8096034C
void func_80960370(void); // func_80960370
void func_80960424(void); // func_80960424
void func_80960440(void); // func_80960440
void func_80960494(void); // func_80960494
void func_809605F4(void); // func_809605F4
void func_80960880(void); // func_80960880
void func_80960B0C(void); // func_80960B0C
void func_80960CF0(void); // func_80960CF0
void func_80960E0C(void); // func_80960E0C
void func_80960F0C(void); // func_80960F0C
void func_80961018(void); // func_80961018
void func_8096104C(void); // func_8096104C
void func_809611BC(void); // func_809611BC
void func_809612BC(void); // func_809612BC
void func_80961350(void); // func_80961350
void func_809613B0(void); // func_809613B0
void func_809613C4(void); // func_809613C4
void func_809613E8(void); // func_809613E8
void func_809613FC(void); // func_809613FC
void func_8096147C(void); // func_8096147C
void func_80961490(void); // func_80961490
void func_80961520(void); // func_80961520
void func_809616E0(void); // func_809616E0
void func_809619D0(void); // func_809619D0
void func_80961AD0(void); // func_80961AD0
void func_80961CC4(void); // func_80961CC4
void func_80961D10(void); // func_80961D10
void func_80961D7C(void); // func_80961D7C
void func_80961E88(void); // func_80961E88
void func_80961EC8(void); // func_80961EC8
void func_80961F00(void); // func_80961F00
void func_80961F38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_80961F38
void func_8096209C(void); // func_8096209C
void func_809622FC(void); // func_809622FC
void func_80962340(void); // func_80962340
void func_80962588(void); // func_80962588
void func_80962660(void); // func_80962660
void func_809628BC(void); // func_809628BC
void func_809628D0(void); // func_809628D0
void func_809629F8(void); // func_809629F8
void func_80962A10(void); // func_80962A10
void func_80962BA8(void); // func_80962BA8
void func_80962BCC(void); // func_80962BCC
void func_80962D48(void); // func_80962D48
void func_80962D60(void); // func_80962D60
void func_80962EBC(void); // func_80962EBC
void func_80962F10(void); // func_80962F10
void func_80962F4C(void); // func_80962F4C
void func_80963258(void); // func_80963258
void func_8096326C(void); // func_8096326C
void func_809632D0(void); // func_809632D0
void func_80963350(void); // func_80963350
void func_80963540(void); // func_80963540
void func_80963560(void); // func_80963560
void func_80963610(void); // func_80963610
void func_80963630(void); // func_80963630
void func_80963810(void); // func_80963810
void func_809638F8(void); // func_809638F8
void func_809639D0(void); // func_809639D0
void func_80963DE4(void); // func_80963DE4
void func_80963EAC(void); // func_80963EAC
void func_80963F44(void); // func_80963F44
void func_80963F88(void); // func_80963F88
void func_80963FF8(void); // func_80963FF8
void func_80964034(void); // func_80964034
void func_809640D8(void); // func_809640D8
void func_8096413C(void); // func_8096413C
void func_80964190(void); // func_80964190
void func_8096426C(void); // func_8096426C
void func_809642E0(void); // func_809642E0
void func_80964350(void); // func_80964350
void func_809643FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_809643FC
void func_8096450C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8096450C
void func_80964570(void); // func_80964570
void func_80964694(void); // func_80964694
void func_809647EC(void); // func_809647EC
void func_80964950(void); // func_80964950
void func_80965650(void); // func_80965650
void func_8096565C(void); // func_8096565C
void func_809656C4(void); // func_809656C4
void func_809656D4(void); // func_809656D4
void func_809657F4(void); // func_809657F4
void func_8096597C(void); // func_8096597C
void func_809659D0(void); // func_809659D0
void func_80965A04(void); // func_80965A04
void func_80965BB0(void); // func_80965BB0
void func_80965BBC(void); // func_80965BBC
void func_80965C0C(void); // func_80965C0C
void func_80965D10(void); // func_80965D10
void func_80965D3C(void); // func_80965D3C
void func_80965DB4(void); // func_80965DB4
void func_8096611C(void); // func_8096611C
void func_809661BC(void); // func_809661BC
void func_80966238(void); // func_80966238
void func_80966410(void); // func_80966410
void func_8096641C(void); // func_8096641C
void func_8096642C(void); // func_8096642C
void func_80966608(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE2 param_7, UNK_TYPE1 param_8); // func_80966608
void func_80966758(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE2 param_7); // func_80966758
void func_8096689C(void); // func_8096689C
void func_80966A08(void); // func_80966A08
void func_80966A68(void); // func_80966A68
void func_80966AE4(void); // func_80966AE4
void func_80966B08(void); // func_80966B08
void func_80966BF4(void); // func_80966BF4
void func_80966D20(void); // func_80966D20
void func_80966E0C(void); // func_80966E0C
void func_80966E84(void); // func_80966E84
void func_80966EF0(void); // func_80966EF0
void func_80966F74(void); // func_80966F74
void func_80966FEC(void); // func_80966FEC
void func_80967060(void); // func_80967060
void func_80967148(void); // func_80967148
void func_809671A8(void); // func_809671A8
void func_809671B8(void); // func_809671B8
void func_80967250(void); // func_80967250
void func_809672DC(void); // func_809672DC
void func_809674C8(void); // func_809674C8
void func_80967608(void); // func_80967608
void func_809676A4(void); // func_809676A4
void func_80967784(void); // func_80967784
void func_809679D0(void); // func_809679D0
void func_80967A48(void); // func_80967A48
void func_80967AB4(void); // func_80967AB4
void func_80967B1C(void); // func_80967B1C
void func_80967CE0(void); // func_80967CE0
void func_80967D20(void); // func_80967D20
void func_80967DA0(void); // func_80967DA0
void func_80967DCC(void); // func_80967DCC
void func_80967E34(void); // func_80967E34
void func_80967E90(void); // func_80967E90
void func_80967F20(void); // func_80967F20
void func_80967FA4(void); // func_80967FA4
void func_809680B0(void); // func_809680B0
void func_80968164(void); // func_80968164
void func_809682A8(void); // func_809682A8
void func_80968504(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80968504
void func_8096854C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8096854C
void func_8096858C(void); // func_8096858C
void func_809687B0(void); // func_809687B0
void func_809689D4(void); // func_809689D4
void func_80968A5C(void); // func_80968A5C
void func_80968B18(void); // func_80968B18
void func_80968B8C(void); // func_80968B8C
void func_80968CB8(void); // func_80968CB8
void func_80968DD0(void); // func_80968DD0
void func_80968E38(void); // func_80968E38
void func_80968F48(void); // func_80968F48
void func_809691B8(void); // func_809691B8
void func_809692A8(void); // func_809692A8
void func_8096933C(void); // func_8096933C
void func_80969400(void); // func_80969400
void func_80969494(void); // func_80969494
void func_809694E8(void); // func_809694E8
void func_80969530(void); // func_80969530
void func_809695FC(void); // func_809695FC
void func_80969688(void); // func_80969688
void func_809696EC(void); // func_809696EC
void func_8096971C(void); // func_8096971C
void func_80969748(void); // func_80969748
void func_80969898(void); // func_80969898
void func_80969AA0(void); // func_80969AA0
void func_80969B5C(void); // func_80969B5C
void func_80969C54(void); // func_80969C54
void func_80969DA4(void); // func_80969DA4
void func_8096A080(void); // func_8096A080
void func_8096A104(void); // func_8096A104
void func_8096A184(void); // func_8096A184
void func_8096A1E8(void); // func_8096A1E8
void func_8096A2C0(void); // func_8096A2C0
void func_8096A38C(void); // func_8096A38C
void func_8096A6F4(void); // func_8096A6F4
void func_8096A8A4(void); // func_8096A8A4
void func_8096A9F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8096A9F4
void func_8096AB20(void); // func_8096AB20
void func_8096B0A0(void); // func_8096B0A0
void func_8096B0AC(void); // func_8096B0AC
void func_8096B0BC(void); // func_8096B0BC
void func_8096B104(void); // func_8096B104
void func_8096B174(void); // func_8096B174
void func_8096B1FC(void); // func_8096B1FC
void func_8096B260(void); // func_8096B260
void func_8096B310(void); // func_8096B310
void func_8096B5F4(void); // func_8096B5F4
void func_8096B604(void); // func_8096B604
void func_8096B94C(void); // func_8096B94C
void func_8096C998(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_8096C998
void func_8096CBB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_8096CBB0
void func_8096CDC8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE4 param_13); // func_8096CDC8
void func_8096D230(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8096D230
void func_8096D60C(void); // func_8096D60C
void func_8096D74C(void); // func_8096D74C
void func_8096E868(void); // func_8096E868
void func_8096EC40(void); // func_8096EC40
void func_8096EC4C(void); // func_8096EC4C
void func_8096ED84(void); // func_8096ED84
void func_8096EE40(void); // func_8096EE40
void func_8096EE50(void); // func_8096EE50
void func_8096EE64(void); // func_8096EE64
void func_8096EF98(void); // func_8096EF98
void func_8096EFD0(void); // func_8096EFD0
void func_8096F04C(void); // func_8096F04C
void func_8096F160(void); // func_8096F160
void func_8096F22C(void); // func_8096F22C
void func_8096F260(void); // func_8096F260
void func_8096F4DC(void); // func_8096F4DC
void func_8096F5E0(void); // func_8096F5E0
void func_8096F60C(void); // func_8096F60C
void func_8096F800(void); // func_8096F800
void func_8096F88C(void); // func_8096F88C
void func_8096F8D8(void); // func_8096F8D8
void func_8096FA18(void); // func_8096FA18
void func_8096FAAC(void); // func_8096FAAC
void func_8096FBB8(void); // func_8096FBB8
void func_8096FC8C(void); // func_8096FC8C
void func_8096FCC4(void); // func_8096FCC4
void func_8096FDE8(void); // func_8096FDE8
void func_8096FE00(void); // func_8096FE00
void func_8096FF80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_8096FF80
void func_80970008(void); // func_80970008
void func_8097006C(void); // func_8097006C
void func_809705E4(void); // func_809705E4
void func_80970658(void); // func_80970658
void func_80970740(void); // func_80970740
void func_80970978(void); // func_80970978
void func_80970A10(void); // func_80970A10
void func_80970A9C(void); // func_80970A9C
void func_80970F20(void); // func_80970F20
void func_80970FF8(void); // func_80970FF8
void func_80971064(void); // func_80971064
void func_80971430(void); // func_80971430
void func_80971440(void); // func_80971440
void func_809714BC(void); // func_809714BC
void func_80971794(void); // func_80971794
void func_809717D0(void); // func_809717D0
void func_8097185C(void); // func_8097185C
void func_8097193C(void); // func_8097193C
void func_80971A38(void); // func_80971A38
void func_80971A64(void); // func_80971A64
void func_80971AD4(void); // func_80971AD4
void func_80971B48(void); // func_80971B48
void func_80971CE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80971CE0
void func_80971D20(void); // func_80971D20
void func_80972350(void); // func_80972350
void func_809723C4(void); // func_809723C4
void func_80972454(void); // func_80972454
void func_80972548(void); // func_80972548
void func_80972680(void); // func_80972680
void func_8097268C(void); // func_8097268C
void func_809727EC(void); // func_809727EC
void func_80972844(void); // func_80972844
void func_809728F8(void); // func_809728F8
void func_80972934(void); // func_80972934
void func_80972998(void); // func_80972998
void func_80972C54(void); // func_80972C54
void func_80973550(Actor* param_1, s32 param_2); // func_80973550
void func_80973640(void); // func_80973640
void func_809736FC(void); // func_809736FC
void func_80973740(void); // func_80973740
void func_80973804(void); // func_80973804
void func_809738D0(void); // func_809738D0
void func_80973960(void); // func_80973960
void func_80973B5C(void); // func_80973B5C
void func_80973C50(void); // func_80973C50
void func_80973CA4(void); // func_80973CA4
void func_80973CD8(void); // func_80973CD8
void func_80973D3C(void); // func_80973D3C
void func_80973DE0(void); // func_80973DE0
void func_80973E60(void); // func_80973E60
void func_80973EF0(void); // func_80973EF0
void func_80973EFC(void); // func_80973EFC
void func_80973F84(void); // func_80973F84
void func_80974080(void); // func_80974080
void func_80974118(void); // func_80974118
void func_80974220(void); // func_80974220
void func_8097424C(void); // func_8097424C
void func_80974374(void); // func_80974374
void func_809744A8(void); // func_809744A8
void func_809744C8(void); // func_809744C8
void func_809744FC(void); // func_809744FC
void func_80974540(void); // func_80974540
void func_80974590(void); // func_80974590
void func_809745BC(void); // func_809745BC
void func_80974730(void); // func_80974730
void func_8097480C(void); // func_8097480C
void func_809748DC(void); // func_809748DC
void func_8097497C(void); // func_8097497C
void func_809749B8(void); // func_809749B8
void func_80974A24(void); // func_80974A24
void func_80974B0C(void); // func_80974B0C
void func_80974B44(void); // func_80974B44
void func_80974B84(void); // func_80974B84
void func_80974CC8(void); // func_80974CC8
void func_80974D3C(void); // func_80974D3C
void func_80974E44(void); // func_80974E44
void func_80974EA0(void); // func_80974EA0
void func_80974F78(void); // func_80974F78
void func_8097502C(void); // func_8097502C
void func_80975070(void); // func_80975070
void func_80975128(void); // func_80975128
void func_80975300(void); // func_80975300
void func_809753C8(void); // func_809753C8
void func_80975540(void); // func_80975540
void func_809755C0(void); // func_809755C0
void func_8097561C(void); // func_8097561C
void func_809756D0(void); // func_809756D0
void func_80975720(void); // func_80975720
void func_809758B0(void); // func_809758B0
void func_80975998(void); // func_80975998
void func_80975A98(void); // func_80975A98
void func_80975B6C(void); // func_80975B6C
void func_80975C14(void); // func_80975C14
void func_80975C9C(void); // func_80975C9C
void func_80975DBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80975DBC
void func_80975EB8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80975EB8
void func_80975F38(void); // func_80975F38
void func_809764B0(void); // func_809764B0
void func_8097650C(void); // func_8097650C
void func_80976540(void); // func_80976540
void func_809765A0(void); // func_809765A0
u32 EffectDust_Init(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle, EffectDustInit* init); // func_80977210
void EffectDust_Draw(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle); // func_80977394
void EffectDust_Update0(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle); // func_809776BC
void EffectDust_Update1(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle); // func_809777B4
UNK_TYPE4 EffectSparkle_Init(GlobalContext* ctxt, u32 index, LoadedParticleEntry* param_3, u32* init); // func_80977A00
void func_80977B5C(GraphicsContext** param_1, UNK_TYPE4 param_2, LoadedParticleEntry* param_3); // func_80977B5C
void func_80977DB4(void); // func_80977DB4
void func_80977E6C(void); // func_80977E6C
void func_80977F28(void); // func_80977F28
void func_80978070(void); // func_80978070
void func_80978138(void); // func_80978138
void func_80978304(void); // func_80978304
void func_80978628(void); // func_80978628
void func_809788D0(void); // func_809788D0
void func_809789FC(void); // func_809789FC
void func_80978B68(void); // func_80978B68
void func_80978C30(void); // func_80978C30
void func_80978D70(void); // func_80978D70
void func_80978F40(void); // func_80978F40
void func_80979068(void); // func_80979068
void func_809791B0(void); // func_809791B0
void func_80979228(void); // func_80979228
void func_8097930C(void); // func_8097930C
void func_809794D4(void); // func_809794D4
void func_809795C0(void); // func_809795C0
void func_80979738(void); // func_80979738
void func_8097985C(void); // func_8097985C
void func_80979B30(void); // func_80979B30
void func_80979C38(void); // func_80979C38
void func_80979E48(void); // func_80979E48
void func_80979E80(void); // func_80979E80
void func_8097A050(void); // func_8097A050
void func_8097A208(void); // func_8097A208
void func_8097A310(void); // func_8097A310
void func_8097A470(void); // func_8097A470
void func_8097A548(void); // func_8097A548
void func_8097A5F0(void); // func_8097A5F0
void func_8097A680(void); // func_8097A680
void func_8097A794(void); // func_8097A794
void func_8097A838(void); // func_8097A838
void func_8097AA98(void); // func_8097AA98
void func_8097AD60(void); // func_8097AD60
void func_8097AF50(void); // func_8097AF50
void func_8097B160(void); // func_8097B160
void func_8097B270(void); // func_8097B270
void func_8097B2E4(void); // func_8097B2E4
void func_8097B424(void); // func_8097B424
void func_8097B504(void); // func_8097B504
void func_8097B5E4(void); // func_8097B5E4
void func_8097B708(void); // func_8097B708
void func_8097B810(void); // func_8097B810
void func_8097B924(void); // func_8097B924
void func_8097BA58(void); // func_8097BA58
void func_8097BAD0(void); // func_8097BAD0
void func_8097BC4C(void); // func_8097BC4C
void func_8097BDCC(void); // func_8097BDCC
void func_8097C130(void); // func_8097C130
void func_8097C1BC(void); // func_8097C1BC
void func_8097C394(void); // func_8097C394
void func_8097C490(void); // func_8097C490
void func_8097C560(void); // func_8097C560
void func_8097C74C(void); // func_8097C74C
void func_8097C990(void); // func_8097C990
void func_8097CAE8(void); // func_8097CAE8
void func_8097CCAC(void); // func_8097CCAC
void func_8097D410(void); // func_8097D410
void func_8097D4E8(void); // func_8097D4E8
void func_8097D750(void); // func_8097D750
void func_8097D850(void); // func_8097D850
void func_8097D8F4(void); // func_8097D8F4
void func_8097DAEC(void); // func_8097DAEC
void func_8097DCA0(void); // func_8097DCA0
void func_8097DE30(void); // func_8097DE30
void func_8097DE6C(void); // func_8097DE6C
void func_8097E130(void); // func_8097E130
void func_8097E19C(void); // func_8097E19C
void func_8097E34C(void); // func_8097E34C
void func_8097E368(void); // func_8097E368
void func_8097E384(void); // func_8097E384
void func_8097E3C0(void); // func_8097E3C0
void func_8097E400(void); // func_8097E400
void func_8097E420(void); // func_8097E420
void func_8097E4B0(void); // func_8097E4B0
void func_8097E4F0(void); // func_8097E4F0
void func_8097E584(void); // func_8097E584
void func_8097E660(void); // func_8097E660
void func_8097E698(void); // func_8097E698
void func_8097E7E0(void); // func_8097E7E0
void func_8097E9D8(void); // func_8097E9D8
void func_8097ECD0(void); // func_8097ECD0
void func_8097EE1C(void); // func_8097EE1C
void func_8097F020(void); // func_8097F020
void func_8097F0D0(void); // func_8097F0D0
void func_8097F2F0(void); // func_8097F2F0
void func_8097F62C(void); // func_8097F62C
void func_8097F7EC(void); // func_8097F7EC
void func_8097F880(void); // func_8097F880
void func_8097F99C(void); // func_8097F99C
void func_8097FE8C(void); // func_8097FE8C
void func_8097FF60(void); // func_8097FF60
void func_809800CC(void); // func_809800CC
void func_809803BC(void); // func_809803BC
void func_809805D0(void); // func_809805D0
void func_80980714(void); // func_80980714
void func_8098087C(void); // func_8098087C
void func_80980940(void); // func_80980940
void func_80980A24(void); // func_80980A24
void func_80980BD4(void); // func_80980BD4
void func_80980D50(void); // func_80980D50
void func_80981018(void); // func_80981018
void func_809811E8(void); // func_809811E8
void func_809812E0(void); // func_809812E0
void func_809813C8(void); // func_809813C8
void func_80981698(void); // func_80981698
void func_80981760(void); // func_80981760
void func_8098176C(void); // func_8098176C
void func_809817E4(void); // func_809817E4
void func_80981904(void); // func_80981904
void func_80981928(void); // func_80981928
void func_80981B48(void); // func_80981B48
void func_80981B68(void); // func_80981B68
void func_80981BB8(void); // func_80981BB8
void func_80981D68(void); // func_80981D68
void func_80983520(void); // func_80983520
void func_80983634(void); // func_80983634
void func_80983678(void); // func_80983678
void func_80983704(void); // func_80983704
void func_80983824(void); // func_80983824
void func_809838F0(void); // func_809838F0
void func_80983970(void); // func_80983970
void func_8098399C(void); // func_8098399C
void func_80983B38(void); // func_80983B38
void func_80983DBC(void); // func_80983DBC
void func_80983E9C(void); // func_80983E9C
void func_80983EB4(void); // func_80983EB4
void func_80983F1C(void); // func_80983F1C
void func_80984030(void); // func_80984030
void func_809840A8(void); // func_809840A8
void func_8098419C(void); // func_8098419C
void func_8098420C(void); // func_8098420C
void func_80984248(void); // func_80984248
void func_80984410(void); // func_80984410
void func_80984450(void); // func_80984450
void func_809844FC(void); // func_809844FC
void func_809845A4(void); // func_809845A4
void func_8098470C(void); // func_8098470C
void func_80984748(void); // func_80984748
void func_80984964(void); // func_80984964
void func_809849C4(void); // func_809849C4
void func_80984B34(void); // func_80984B34
void func_80984C28(void); // func_80984C28
void func_80984CA8(void); // func_80984CA8
void func_80984D08(void); // func_80984D08
void func_80984E38(void); // func_80984E38
void func_80984ECC(void); // func_80984ECC
void func_80985018(void); // func_80985018
void func_80985088(void); // func_80985088
void func_80985154(void); // func_80985154
void func_80985168(void); // func_80985168
void func_8098518C(void); // func_8098518C
void func_809851E8(void); // func_809851E8
void func_809852DC(void); // func_809852DC
void func_8098537C(void); // func_8098537C
void func_80985480(void); // func_80985480
void func_80985538(void); // func_80985538
void func_80985C40(void); // func_80985C40
void func_80985D10(void); // func_80985D10
void func_80985D3C(void); // func_80985D3C
void func_80985D68(void); // func_80985D68
void func_80986120(void); // func_80986120
void func_80986270(void); // func_80986270
void func_809862CC(void); // func_809862CC
void func_80986300(void); // func_80986300
void func_80986360(void); // func_80986360
void func_809879E0(void); // func_809879E0
void func_80987A3C(void); // func_80987A3C
void func_80987A70(void); // func_80987A70
void func_80987AD0(void); // func_80987AD0
void func_80989140(void); // func_80989140
void func_80989204(void); // func_80989204
void func_8098933C(void); // func_8098933C
void func_80989418(void); // func_80989418
void func_809895B4(void); // func_809895B4
void func_80989674(void); // func_80989674
void func_80989864(void); // func_80989864
void func_80989974(void); // func_80989974
void func_809899C8(void); // func_809899C8
void func_80989A08(void); // func_80989A08
void func_80989A48(void); // func_80989A48
void func_80989A9C(void); // func_80989A9C
void func_80989ADC(void); // func_80989ADC
void func_80989BF8(void); // func_80989BF8
void func_80989D38(void); // func_80989D38
void func_80989E18(void); // func_80989E18
void func_80989FC8(void); // func_80989FC8
void func_8098A064(void); // func_8098A064
void func_8098A1B4(void); // func_8098A1B4
void func_8098A234(void); // func_8098A234
void func_8098A468(void); // func_8098A468
void func_8098A55C(void); // func_8098A55C
void func_8098A618(void); // func_8098A618
void func_8098A70C(void); // func_8098A70C
void func_8098A89C(void); // func_8098A89C
void func_8098A938(void); // func_8098A938
void func_8098AAAC(void); // func_8098AAAC
void func_8098AB48(void); // func_8098AB48
void func_8098AC34(void); // func_8098AC34
void func_8098AE58(void); // func_8098AE58
void func_8098AF44(void); // func_8098AF44
void func_8098AF98(void); // func_8098AF98
void func_8098B004(void); // func_8098B004
void func_8098B198(void); // func_8098B198
void func_8098B28C(void); // func_8098B28C
void func_8098B390(void); // func_8098B390
void func_8098B464(void); // func_8098B464
void func_8098B560(void); // func_8098B560
void func_8098B88C(void); // func_8098B88C
void func_8098BA64(void); // func_8098BA64
void func_8098BB10(void); // func_8098BB10
void func_8098BBEC(void); // func_8098BBEC
void func_8098BC54(void); // func_8098BC54
void func_8098BCA8(void); // func_8098BCA8
void func_8098BE18(void); // func_8098BE18
void func_8098BE44(void); // func_8098BE44
void func_8098BFB8(void); // func_8098BFB8
void func_8098BFD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8098BFD4
void func_8098C06C(void); // func_8098C06C
void func_8098CA20(void); // func_8098CA20
void func_8098CAD0(void); // func_8098CAD0
void func_8098CB70(void); // func_8098CB70
void func_8098CBDC(void); // func_8098CBDC
void func_8098CC18(void); // func_8098CC18
void func_8098CC98(void); // func_8098CC98
void func_8098CCC4(void); // func_8098CCC4
void func_8098CD0C(void); // func_8098CD0C
void func_8098CE40(void); // func_8098CE40
void func_8098CEAC(void); // func_8098CEAC
void func_8098D19C(void); // func_8098D19C
void func_8098D47C(void); // func_8098D47C
void func_8098D6E0(void); // func_8098D6E0
void func_8098D870(void); // func_8098D870
void func_8098D8C8(void); // func_8098D8C8
void func_8098D99C(void); // func_8098D99C
void func_8098DA74(void); // func_8098DA74
void func_8098DAE0(void); // func_8098DAE0
void func_8098DC18(void); // func_8098DC18
void func_8098DC44(void); // func_8098DC44
void func_8098DC60(void); // func_8098DC60
void func_8098DE58(void); // func_8098DE58
void func_8098DEA0(void); // func_8098DEA0
void func_8098E098(void); // func_8098E098
void func_8098E0B8(void); // func_8098E0B8
void func_8098E15C(void); // func_8098E15C
void func_8098E2F8(void); // func_8098E2F8
void func_8098E5C0(void); // func_8098E5C0
void func_8098E62C(void); // func_8098E62C
void func_8098E8A8(void); // func_8098E8A8
void func_8098E900(void); // func_8098E900
void func_8098E9C4(void); // func_8098E9C4
void func_8098EA08(void); // func_8098EA08
void func_8098EB30(void); // func_8098EB30
void func_8098EB78(void); // func_8098EB78
void func_8098EC68(void); // func_8098EC68
void func_8098ED20(void); // func_8098ED20
void func_8098ED4C(void); // func_8098ED4C
void func_8098EE0C(void); // func_8098EE0C
void func_8098EF60(void); // func_8098EF60
void func_8098EF9C(void); // func_8098EF9C
void func_8098EFAC(void); // func_8098EFAC
void func_8098EFBC(void); // func_8098EFBC
void func_8098EFE0(void); // func_8098EFE0
void func_8098F040(void); // func_8098F040
void func_8098F110(void); // func_8098F110
void func_8098F220(void); // func_8098F220
void func_8098F364(void); // func_8098F364
void func_8098F438(void); // func_8098F438
void func_8098F528(void); // func_8098F528
void func_8098F588(void); // func_8098F588
void func_8098F598(void); // func_8098F598
void func_8098F5AC(void); // func_8098F5AC
void func_8098F5D0(void); // func_8098F5D0
void func_8098F5E4(void); // func_8098F5E4
void func_8098F66C(void); // func_8098F66C
void func_8098F680(void); // func_8098F680
void func_8098F6FC(void); // func_8098F6FC
void func_8098F800(void); // func_8098F800
void func_8098F8A8(void); // func_8098F8A8
void func_8098F928(void); // func_8098F928
void func_8098F954(void); // func_8098F954
void func_8098FA44(void); // func_8098FA44
void func_8098FA70(void); // func_8098FA70
void func_8098FB28(void); // func_8098FB28
UNK_TYPE4 func_8098FBB4(void); // func_8098FBB4
void func_8098FBD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8098FBD0
void func_8098FC2C(void); // func_8098FC2C
void func_8098FD50(void); // func_8098FD50
void func_8098FEA8(void); // func_8098FEA8
void func_8099000C(void); // func_8099000C
void func_80990310(void); // func_80990310
void func_80990784(void); // func_80990784
void func_809907D4(void); // func_809907D4
void func_80990854(void); // func_80990854
void func_809908E0(void); // func_809908E0
void func_80990948(void); // func_80990948
void func_80990C6C(void); // func_80990C6C
void func_80990E4C(void); // func_80990E4C
void func_80990EAC(void); // func_80990EAC
void func_80990ED4(void); // func_80990ED4
void func_80990F0C(void); // func_80990F0C
void func_80990F50(void); // func_80990F50
void func_80990FC8(void); // func_80990FC8
void func_80991040(void); // func_80991040
void func_809910F0(void); // func_809910F0
void func_80991174(void); // func_80991174
void func_80991200(void); // func_80991200
void func_80991280(void); // func_80991280
void func_80991438(void); // func_80991438
void func_8099149C(void); // func_8099149C
void func_80991738(void); // func_80991738
void func_8099177C(void); // func_8099177C
void func_80991948(void); // func_80991948
void func_809919F4(void); // func_809919F4
void func_80991C04(void); // func_80991C04
void func_80991C80(void); // func_80991C80
void func_80991FD8(void); // func_80991FD8
void func_80992068(void); // func_80992068
void func_8099223C(void); // func_8099223C
void func_809922B4(void); // func_809922B4
void func_809923B0(void); // func_809923B0
void func_809923E4(void); // func_809923E4
void func_8099245C(void); // func_8099245C
void func_809924EC(void); // func_809924EC
void func_809926D0(void); // func_809926D0
void func_80992784(void); // func_80992784
void func_8099282C(void); // func_8099282C
void func_809928CC(void); // func_809928CC
void func_80992A74(void); // func_80992A74
void func_80992B8C(void); // func_80992B8C
void func_80992D6C(void); // func_80992D6C
void func_80992E0C(void); // func_80992E0C
void func_80992FD4(void); // func_80992FD4
void func_80993018(void); // func_80993018
void func_80993148(void); // func_80993148
void func_80993194(void); // func_80993194
void func_80993350(void); // func_80993350
void func_809933A0(void); // func_809933A0
void func_80993524(void); // func_80993524
void func_8099357C(void); // func_8099357C
void func_80993738(void); // func_80993738
void func_8099386C(void); // func_8099386C
void func_80993BC0(void); // func_80993BC0
void func_80993E50(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80993E50
void func_80993E94(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80993E94
void func_80993F68(void); // func_80993F68
void func_8099408C(void); // func_8099408C
void func_809947B0(void); // func_809947B0
void func_8099495C(void); // func_8099495C
void func_809949C4(void); // func_809949C4
void func_80994A30(void); // func_80994A30
void func_80994A9C(void); // func_80994A9C
void func_80994B08(void); // func_80994B08
void func_80994D18(void); // func_80994D18
void func_80994DA8(void); // func_80994DA8
void func_80994E2C(void); // func_80994E2C
void func_80994E94(void); // func_80994E94
void func_80994F7C(void); // func_80994F7C
void func_8099504C(void); // func_8099504C
void func_80995068(void); // func_80995068
void func_80995190(void); // func_80995190
void func_80995244(void); // func_80995244
void func_809952D8(void); // func_809952D8
void func_8099533C(void); // func_8099533C
void func_809953E8(void); // func_809953E8
void func_8099544C(void); // func_8099544C
void func_809954F8(void); // func_809954F8
void func_8099556C(void); // func_8099556C
void func_8099571C(void); // func_8099571C
void func_80995818(void); // func_80995818
void func_809958F4(void); // func_809958F4
void func_8099599C(void); // func_8099599C
void func_80995A30(void); // func_80995A30
void func_80995A8C(void); // func_80995A8C
void func_80995C24(void); // func_80995C24
void func_80995C84(void); // func_80995C84
void func_80995D3C(void); // func_80995D3C
void func_80995DC4(void); // func_80995DC4
void func_80995E08(void); // func_80995E08
void func_80995E64(void); // func_80995E64
void func_80995F98(void); // func_80995F98
void func_809960AC(void); // func_809960AC
void func_809961E4(void); // func_809961E4
void func_80996284(void); // func_80996284
void func_809962D4(void); // func_809962D4
void func_8099630C(void); // func_8099630C
void func_809963C4(void); // func_809963C4
void func_809963D8(void); // func_809963D8
void func_80996474(void); // func_80996474
void func_809964A0(void); // func_809964A0
void func_809964DC(void); // func_809964DC
void func_80996544(void); // func_80996544
void func_80996594(void); // func_80996594
void func_8099672C(void); // func_8099672C
void func_80996AD0(void); // func_80996AD0
void func_80996BEC(void); // func_80996BEC
void func_80996D68(void); // func_80996D68
void func_80996E5C(void); // func_80996E5C
void func_80996F78(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80996F78
void func_809970D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809970D0
void func_80997278(void); // func_80997278
void func_80997A90(void); // func_80997A90
void func_80997AFC(void); // func_80997AFC
void func_80997B30(void); // func_80997B30
void func_80997CE0(void); // func_80997CE0
void func_80997D14(void); // func_80997D14
void func_80997D38(void); // func_80997D38
void func_80997DEC(void); // func_80997DEC
void func_80997E4C(void); // func_80997E4C
void func_80997FF0(void); // func_80997FF0
void func_80998040(void); // func_80998040
void func_8099807C(void); // func_8099807C
void func_80998300(void); // func_80998300
void func_80998334(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80998334
void func_809984F4(void); // func_809984F4
void func_809985B8(void); // func_809985B8
void func_80998704(void); // func_80998704
void func_8099874C(void); // func_8099874C
void func_809989B4(void); // func_809989B4
void func_809989F4(void); // func_809989F4
void func_80998A48(void); // func_80998A48
void func_80998BBC(void); // func_80998BBC
void func_80998D44(void); // func_80998D44
void func_80998F9C(void); // func_80998F9C
void func_80999584(void); // func_80999584
void func_809995A4(void); // func_809995A4
void func_80999A8C(void); // func_80999A8C
void func_80999AC0(void); // func_80999AC0
void func_80999B34(void); // func_80999B34
void func_80999BC8(void); // func_80999BC8
void func_80999E38(void); // func_80999E38
void func_8099A094(void); // func_8099A094
void func_8099A920(void); // func_8099A920
void func_8099A96C(void); // func_8099A96C
void func_8099A9A4(void); // func_8099A9A4
void func_8099AA84(void); // func_8099AA84
void func_8099AB30(void); // func_8099AB30
void func_8099AC2C(void); // func_8099AC2C
void func_8099AC58(void); // func_8099AC58
void func_8099AC8C(void); // func_8099AC8C
void func_8099B098(void); // func_8099B098
void func_8099B0CC(void); // func_8099B0CC
void func_8099B318(void); // func_8099B318
void func_8099B384(void); // func_8099B384
void func_8099B584(void); // func_8099B584
void func_8099B6AC(void); // func_8099B6AC
void func_8099B6C4(void); // func_8099B6C4
void func_8099B778(void); // func_8099B778
void func_8099B838(void); // func_8099B838
void func_8099B8EC(void); // func_8099B8EC
void func_8099B9E8(void); // func_8099B9E8
void func_8099BAB4(void); // func_8099BAB4
void func_8099BB84(void); // func_8099BB84
void func_8099BE48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8099BE48
void func_8099BF20(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8099BF20
void func_8099BFA4(void); // func_8099BFA4
void func_8099C290(void); // func_8099C290
void func_8099C328(void); // func_8099C328
void func_8099C41C(void); // func_8099C41C
void func_8099C498(void); // func_8099C498
void func_8099C834(void); // func_8099C834
void func_8099C880(void); // func_8099C880
void func_8099CAA8(void); // func_8099CAA8
void func_8099CB20(void); // func_8099CB20
void func_8099CB68(void); // func_8099CB68
void func_8099CBCC(void); // func_8099CBCC
void func_8099CC68(void); // func_8099CC68
void func_8099CCF8(void); // func_8099CCF8
void func_8099CDA0(void); // func_8099CDA0
void func_8099CFAC(void); // func_8099CFAC
void func_8099D144(void); // func_8099D144
void func_8099D3C0(void); // func_8099D3C0
void func_8099D4AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8099D4AC
void func_8099D4FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8099D4FC
void func_8099D53C(void); // func_8099D53C
void func_8099D59C(void); // func_8099D59C
void func_8099D780(void); // func_8099D780
void func_8099D7DC(void); // func_8099D7DC
void func_8099D810(void); // func_8099D810
void func_8099D870(void); // func_8099D870
void func_8099E790(void); // func_8099E790
void func_8099E858(void); // func_8099E858
void func_8099E96C(void); // func_8099E96C
void func_8099E9E0(void); // func_8099E9E0
void func_8099EA60(void); // func_8099EA60
void func_8099EBD8(void); // func_8099EBD8
void func_8099EC50(void); // func_8099EC50
void func_8099ED4C(void); // func_8099ED4C
void func_8099EE24(void); // func_8099EE24
void func_8099EE34(void); // func_8099EE34
void func_8099EF40(void); // func_8099EF40
void func_8099EF6C(void); // func_8099EF6C
void func_8099EFF4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8099EFF4
void func_8099F15C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8099F15C
void func_8099F268(void); // func_8099F268
void func_8099F730(void); // func_8099F730
void func_8099F7F4(void); // func_8099F7F4
void func_8099F980(void); // func_8099F980
void func_8099FA40(void); // func_8099FA40
void func_8099FAB0(void); // func_8099FAB0
void func_8099FB20(void); // func_8099FB20
void func_8099FB64(void); // func_8099FB64
void func_8099FCC0(void); // func_8099FCC0
void func_8099FD7C(void); // func_8099FD7C
void func_8099FEB0(void); // func_8099FEB0
void func_809A0044(void); // func_809A0044
void func_809A0070(void); // func_809A0070
void func_809A00F8(void); // func_809A00F8
void func_809A020C(void); // func_809A020C
void func_809A024C(void); // func_809A024C
void func_809A0350(void); // func_809A0350
void func_809A03AC(void); // func_809A03AC
void func_809A03FC(void); // func_809A03FC
void func_809A04D0(void); // func_809A04D0
void func_809A0820(void); // func_809A0820
void func_809A08A4(void); // func_809A08A4
void func_809A0920(void); // func_809A0920
void func_809A096C(void); // func_809A096C
void func_809A0A14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809A0A14
void func_809A0C60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809A0C60
void func_809A0CBC(void); // func_809A0CBC
void func_809A0F20(void); // func_809A0F20
void func_809A0F78(void); // func_809A0F78
void func_809A10F4(void); // func_809A10F4
void func_809A13A0(void); // func_809A13A0
void func_809A1408(void); // func_809A1408
void func_809A1480(void); // func_809A1480
void func_809A15A0(void); // func_809A15A0
void func_809A15CC(void); // func_809A15CC
void func_809A17BC(void); // func_809A17BC
void func_809A1BB0(void); // func_809A1BB0
void func_809A1C4C(void); // func_809A1C4C
void func_809A1CFC(void); // func_809A1CFC
void func_809A1D0C(void); // func_809A1D0C
void func_809A1D1C(void); // func_809A1D1C
void func_809A1D60(void); // func_809A1D60
void func_809A1DA4(void); // func_809A1DA4
void func_809A1DBC(void); // func_809A1DBC
void func_809A1DD0(void); // func_809A1DD0
void func_809A1E28(void); // func_809A1E28
void func_809A1E60(void); // func_809A1E60
void func_809A2030(void); // func_809A2030
void func_809A2070(void); // func_809A2070
void func_809A2080(void); // func_809A2080
void func_809A20FC(void); // func_809A20FC
void func_809A2194(void); // func_809A2194
void func_809A21B8(void); // func_809A21B8
void func_809A2B60(void); // func_809A2B60
void func_809A2B70(void); // func_809A2B70
void func_809A2BF8(void); // func_809A2BF8
void func_809A2C78(void); // func_809A2C78
void func_809A2D80(void); // func_809A2D80
void func_809A2DB0(void); // func_809A2DB0
void func_809A2E08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809A2E08
void func_809A2EA0(void); // func_809A2EA0
void func_809A2FF8(void); // func_809A2FF8
void func_809A3098(void); // func_809A3098
void func_809A30E0(void); // func_809A30E0
void func_809A3134(void); // func_809A3134
void func_809A33E0(void); // func_809A33E0
void func_809A3448(void); // func_809A3448
void func_809A34E0(void); // func_809A34E0
void func_809A35EC(void); // func_809A35EC
void func_809A376C(void); // func_809A376C
void func_809A3818(void); // func_809A3818
void func_809A3A14(void); // func_809A3A14
void func_809A3A48(void); // func_809A3A48
void func_809A3A74(void); // func_809A3A74
void func_809A3BA4(void); // func_809A3BA4
void func_809A3BC0(void); // func_809A3BC0
void func_809A3D1C(void); // func_809A3D1C
void func_809A3D38(void); // func_809A3D38
void func_809A3D7C(void); // func_809A3D7C
void func_809A3E58(void); // func_809A3E58
void func_809A3F0C(void); // func_809A3F0C
void func_809A41C0(void); // func_809A41C0
void func_809A42A0(void); // func_809A42A0
void func_809A43A8(void); // func_809A43A8
void func_809A43EC(void); // func_809A43EC
void func_809A448C(void); // func_809A448C
void func_809A4718(void); // func_809A4718
void func_809A4744(void); // func_809A4744
void func_809A477C(void); // func_809A477C
void func_809A4804(void); // func_809A4804
void func_809A481C(void); // func_809A481C
void func_809A488C(void); // func_809A488C
void func_809A48AC(void); // func_809A48AC
void func_809A4ACC(void); // func_809A4ACC
void func_809A4C50(void); // func_809A4C50
void func_809A4E00(void); // func_809A4E00
void func_809A4E68(void); // func_809A4E68
void func_809A4F00(void); // func_809A4F00
void func_809A500C(void); // func_809A500C
void func_809A518C(void); // func_809A518C
void func_809A5238(void); // func_809A5238
void func_809A5480(void); // func_809A5480
void func_809A54B4(void); // func_809A54B4
void func_809A54E0(void); // func_809A54E0
void func_809A5610(void); // func_809A5610
void func_809A562C(void); // func_809A562C
void func_809A57D8(void); // func_809A57D8
void func_809A57F4(void); // func_809A57F4
void func_809A5838(void); // func_809A5838
void func_809A5960(void); // func_809A5960
void func_809A5A3C(void); // func_809A5A3C
void func_809A5B50(void); // func_809A5B50
void func_809A5D10(void); // func_809A5D10
void func_809A5D94(void); // func_809A5D94
void func_809A5DC0(void); // func_809A5DC0
void func_809A5DE0(void); // func_809A5DE0
void func_809A5E14(void); // func_809A5E14
void func_809A5E24(void); // func_809A5E24
void func_809A5E98(void); // func_809A5E98
void func_809A610C(void); // func_809A610C
void func_809A6280(void); // func_809A6280
void func_809A64E0(void); // func_809A64E0
void func_809A6524(void); // func_809A6524
void func_809A65D8(void); // func_809A65D8
void func_809A6628(void); // func_809A6628
void func_809A6668(void); // func_809A6668
void func_809A6754(void); // func_809A6754
void func_809A67A4(void); // func_809A67A4
void func_809A6B6C(void); // func_809A6B6C
void func_809A6E18(void); // func_809A6E18
void func_809A6E74(void); // func_809A6E74
void func_809A6F8C(void); // func_809A6F8C
void func_809A700C(void); // func_809A700C
void func_809A7134(void); // func_809A7134
void func_809A71CC(void); // func_809A71CC
void func_809A7494(void); // func_809A7494
void func_809A753C(void); // func_809A753C
void func_809A7844(void); // func_809A7844
void func_809A78EC(void); // func_809A78EC
void func_809A797C(void); // func_809A797C
void func_809A7A8C(void); // func_809A7A8C
void func_809A7AE4(void); // func_809A7AE4
void func_809A7BBC(void); // func_809A7BBC
void func_809A7C98(void); // func_809A7C98
void func_809A7CE0(void); // func_809A7CE0
void func_809A8044(void); // func_809A8044
void func_809A8224(void); // func_809A8224
void func_809A847C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809A847C
void func_809A8640(void); // func_809A8640
void func_809A8870(void); // func_809A8870
void func_809A8924(void); // func_809A8924
void func_809A8A64(void); // func_809A8A64
void func_809A9110(void); // func_809A9110
void func_809A91FC(void); // func_809A91FC
void func_809A92D0(void); // func_809A92D0
void func_809A9314(void); // func_809A9314
void func_809A961C(void); // func_809A961C
void func_809A96FC(void); // func_809A96FC
void func_809A9790(void); // func_809A9790
void func_809A983C(void); // func_809A983C
void func_809A9DB8(void); // func_809A9DB8
void func_809AA238(void); // func_809AA238
void func_809AA278(void); // func_809AA278
void func_809AA54C(void); // func_809AA54C
void func_809AA798(void); // func_809AA798
void func_809AA9A8(void); // func_809AA9A8
void func_809AAE60(void); // func_809AAE60
void func_809AAE94(void); // func_809AAE94
void func_809AAF18(void); // func_809AAF18
void func_809AAF58(void); // func_809AAF58
void func_809AAF9C(void); // func_809AAF9C
void func_809AAFE8(void); // func_809AAFE8
void func_809AB2F0(void); // func_809AB2F0
void func_809AB360(void); // func_809AB360
void func_809AB3C4(void); // func_809AB3C4
void func_809AB3D8(void); // func_809AB3D8
void func_809AB428(void); // func_809AB428
void func_809AB43C(void); // func_809AB43C
void func_809AB474(void); // func_809AB474
void func_809AB4A8(void); // func_809AB4A8
void func_809AB5FC(void); // func_809AB5FC
void func_809AB610(void); // func_809AB610
void func_809AB6FC(void); // func_809AB6FC
void func_809AB77C(void); // func_809AB77C
void func_809ABB1C(void); // func_809ABB1C
void func_809ABB7C(void); // func_809ABB7C
void func_809ABDE0(void); // func_809ABDE0
void func_809ABE54(void); // func_809ABE54
void func_809ABEC4(void); // func_809ABEC4
void func_809ABF38(void); // func_809ABF38
void func_809ABFA8(void); // func_809ABFA8
void func_809AC4B0(void); // func_809AC4B0
void func_809AC594(void); // func_809AC594
void func_809AC5C0(void); // func_809AC5C0
void func_809AC638(void); // func_809AC638
void func_809AC68C(void); // func_809AC68C
void func_809AC6C0(void); // func_809AC6C0
void func_809AC760(void); // func_809AC760
void func_809AC7F8(void); // func_809AC7F8
void func_809AC970(void); // func_809AC970
void func_809AC9B8(void); // func_809AC9B8
void func_809ACB28(void); // func_809ACB28
void func_809ACD90(void); // func_809ACD90
void func_809ACDA8(void); // func_809ACDA8
void func_809ACDB8(void); // func_809ACDB8
void func_809ACDC8(void); // func_809ACDC8
void func_809ACE00(void); // func_809ACE00
void func_809ACF40(void); // func_809ACF40
void func_809AD048(void); // func_809AD048
void func_809AD058(void); // func_809AD058
void func_809AD084(void); // func_809AD084
void func_809AD194(void); // func_809AD194
void func_809AD1EC(void); // func_809AD1EC
void func_809AD230(void); // func_809AD230
void func_809AD614(void); // func_809AD614
void func_809AD8E0(void); // func_809AD8E0
void func_809ADB24(void); // func_809ADB24
void func_809ADBC8(void); // func_809ADBC8
void func_809ADC7C(void); // func_809ADC7C
void func_809ADCB8(void); // func_809ADCB8
void func_809AE754(void); // func_809AE754
void func_809AE87C(void); // func_809AE87C
void func_809AE9B0(void); // func_809AE9B0
void func_809AEA08(void); // func_809AEA08
void func_809AECA8(void); // func_809AECA8
void func_809AED00(void); // func_809AED00
void func_809AED54(void); // func_809AED54
void func_809AEDAC(void); // func_809AEDAC
void func_809AEE44(void); // func_809AEE44
void func_809AEEC0(void); // func_809AEEC0
void func_809AF064(void); // func_809AF064
void func_809AF110(void); // func_809AF110
void func_809AF28C(void); // func_809AF28C
void func_809AF2F8(void); // func_809AF2F8
void func_809AF368(void); // func_809AF368
void func_809AF3C0(void); // func_809AF3C0
void func_809AF3FC(void); // func_809AF3FC
void func_809AF440(void); // func_809AF440
void func_809AF470(void); // func_809AF470
void func_809AF53C(void); // func_809AF53C
void func_809AF5F8(void); // func_809AF5F8
void func_809AF714(void); // func_809AF714
void func_809AF76C(void); // func_809AF76C
void func_809AF7F4(void); // func_809AF7F4
void func_809AF8D0(void); // func_809AF8D0
void func_809AF99C(void); // func_809AF99C
void func_809AFA58(void); // func_809AFA58
void func_809AFAF4(void); // func_809AFAF4
void func_809AFC10(void); // func_809AFC10
void func_809AFE38(void); // func_809AFE38
void func_809B0034(void); // func_809B0034
void func_809B02CC(void); // func_809B02CC
void func_809B0734(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809B0734
void func_809B0820(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809B0820
void func_809B0B70(void); // func_809B0B70
void func_809B0BB0(void); // func_809B0BB0
void func_809B1550(void); // func_809B1550
void func_809B162C(void); // func_809B162C
void func_809B179C(void); // func_809B179C
void func_809B17D0(void); // func_809B17D0
void func_809B1AA0(void); // func_809B1AA0
void func_809B1BE8(void); // func_809B1BE8
void func_809B1D90(void); // func_809B1D90
void func_809B20F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_809B20F0
void func_809B21F4(void); // func_809B21F4
void func_809B22CC(void); // func_809B22CC
void func_809B2510(void); // func_809B2510
void func_809B2DC0(void); // func_809B2DC0
void func_809B2DD0(void); // func_809B2DD0
void func_809B2F54(void); // func_809B2F54
void func_809B316C(void); // func_809B316C
void func_809B31E8(void); // func_809B31E8
void func_809B329C(void); // func_809B329C
void func_809B331C(void); // func_809B331C
void func_809B3394(void); // func_809B3394
void func_809B33F0(void); // func_809B33F0
void func_809B35BC(void); // func_809B35BC
void func_809B3618(void); // func_809B3618
void func_809B37C8(void); // func_809B37C8
void func_809B3834(void); // func_809B3834
void func_809B389C(void); // func_809B389C
void func_809B3958(void); // func_809B3958
void func_809B3A7C(void); // func_809B3A7C
void func_809B3B94(void); // func_809B3B94
void func_809B3CD0(void); // func_809B3CD0
void func_809B3DAC(void); // func_809B3DAC
void func_809B3E9C(void); // func_809B3E9C
void func_809B3F0C(void); // func_809B3F0C
void func_809B4024(void); // func_809B4024
void func_809B40E8(void); // func_809B40E8
void func_809B41D8(void); // func_809B41D8
void func_809B41F8(void); // func_809B41F8
void func_809B42B8(void); // func_809B42B8
void func_809B4308(void); // func_809B4308
void func_809B47EC(void); // func_809B47EC
void func_809B4880(void); // func_809B4880
void func_809B4BFC(void); // func_809B4BFC
void func_809B4C58(void); // func_809B4C58
void func_809B4E84(void); // func_809B4E84
void func_809B4ED8(void); // func_809B4ED8
void func_809B4F90(void); // func_809B4F90
void func_809B5058(void); // func_809B5058
void func_809B51DC(void); // func_809B51DC
void func_809B52E8(void); // func_809B52E8
void func_809B5634(void); // func_809B5634
void func_809B5698(void); // func_809B5698
void func_809B58D4(void); // func_809B58D4
void func_809B592C(void); // func_809B592C
void func_809B59FC(void); // func_809B59FC
void func_809B5B08(void); // func_809B5B08
void func_809B5D38(void); // func_809B5D38
void func_809B5D54(void); // func_809B5D54
void func_809B5E90(void); // func_809B5E90
void func_809B5ED0(void); // func_809B5ED0
void func_809B5FA8(void); // func_809B5FA8
void func_809B601C(void); // func_809B601C
void func_809B631C(void); // func_809B631C
void func_809B638C(void); // func_809B638C
void func_809B6528(void); // func_809B6528
void func_809B6574(void); // func_809B6574
void func_809B6764(void); // func_809B6764
void func_809B6C04(void); // func_809B6C04
void func_809B6C54(void); // func_809B6C54
void func_809B6D38(void); // func_809B6D38
void func_809B6D94(void); // func_809B6D94
void func_809B6EC8(void); // func_809B6EC8
void func_809B6F40(void); // func_809B6F40
void func_809B7190(void); // func_809B7190
void func_809B71DC(void); // func_809B71DC
void func_809B7708(void); // func_809B7708
void func_809B7778(void); // func_809B7778
void func_809B78A4(void); // func_809B78A4
void func_809B7950(void); // func_809B7950
void func_809B842C(void); // func_809B842C
void func_809B8458(void); // func_809B8458
void func_809B9A18(void); // func_809B9A18
void func_809B9D24(void); // func_809B9D24
void func_809B9E00(void); // func_809B9E00
void func_809B9F8C(void); // func_809B9F8C
void func_809BA058(void); // func_809BA058
void func_809BA0CC(void); // func_809BA0CC
void func_809BA940(void); // func_809BA940
void func_809BA978(void); // func_809BA978
void func_809BB0BC(void); // func_809BB0BC
void func_809BC2C4(void); // func_809BC2C4
void func_809BC67C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809BC67C
void func_809BC720(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809BC720
void func_809BC8B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809BC8B4
void func_809BCA80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809BCA80
void func_809BCAD8(void); // func_809BCAD8
void func_809BCB54(void); // func_809BCB54
void func_809BCB78(void); // func_809BCB78
void func_809BCC2C(void); // func_809BCC2C
void func_809BD1AC(void); // func_809BD1AC
void func_809BD260(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_809BD260
void func_809BD29C(void); // func_809BD29C
void func_809BD490(void); // func_809BD490
void func_809BD858(void); // func_809BD858
void func_809C0760(void); // func_809C0760
void func_809C0824(void); // func_809C0824
void func_809C085C(void); // func_809C085C
void func_809C08E0(void); // func_809C08E0
void func_809C09A0(void); // func_809C09A0
void func_809C0A20(void); // func_809C0A20
void func_809C0AB4(void); // func_809C0AB4
void func_809C0E30(void); // func_809C0E30
void func_809C0F18(void); // func_809C0F18
void func_809C0F3C(void); // func_809C0F3C
void func_809C10B0(void); // func_809C10B0
void func_809C1124(void); // func_809C1124
void func_809C1158(void); // func_809C1158
void func_809C11EC(void); // func_809C11EC
void func_809C1304(void); // func_809C1304
void func_809C1424(void); // func_809C1424
void func_809C14D0(void); // func_809C14D0
void func_809C15BC(void); // func_809C15BC
void func_809C165C(void); // func_809C165C
void func_809C16DC(void); // func_809C16DC
void func_809C1C9C(void); // func_809C1C9C
void func_809C1D64(void); // func_809C1D64
void func_809C1EC8(void); // func_809C1EC8
void func_809C2060(void); // func_809C2060
void func_809C21E0(void); // func_809C21E0
void func_809C2504(void); // func_809C2504
void func_809C2594(void); // func_809C2594
void func_809C25E4(void); // func_809C25E4
void func_809C2680(void); // func_809C2680
void func_809C26E4(void); // func_809C26E4
void func_809C2730(void); // func_809C2730
void func_809C2788(void); // func_809C2788
void func_809C2824(void); // func_809C2824
void func_809C28B8(void); // func_809C28B8
void func_809C2A64(void); // func_809C2A64
void func_809C2BE4(void); // func_809C2BE4
void func_809C2C9C(void); // func_809C2C9C
void func_809C2D0C(void); // func_809C2D0C
void func_809C2EC4(void); // func_809C2EC4
void func_809C2F34(void); // func_809C2F34
void func_809C2FA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE1 param_11); // func_809C2FA0
void func_809C3190(void); // func_809C3190
void func_809C3350(void); // func_809C3350
void func_809C339C(void); // func_809C339C
void func_809C33D8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809C33D8
void func_809C35B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809C35B4
void func_809C35F4(void); // func_809C35F4
void func_809C3608(void); // func_809C3608
void func_809C3D80(void); // func_809C3D80
void func_809C3D90(void); // func_809C3D90
void func_809C3DA0(void); // func_809C3DA0
void func_809C3DB0(void); // func_809C3DB0
void func_809C3E10(void); // func_809C3E10
void func_809C3E20(void); // func_809C3E20
void func_809C3E30(void); // func_809C3E30
void func_809C3E40(void); // func_809C3E40
void func_809C3EA0(void); // func_809C3EA0
void func_809C3EB0(void); // func_809C3EB0
void func_809C3EC0(void); // func_809C3EC0
void func_809C3ED0(void); // func_809C3ED0
void func_809C3F30(void); // func_809C3F30
void func_809C3FC8(void); // func_809C3FC8
void func_809C3FD8(void); // func_809C3FD8
void func_809C4078(void); // func_809C4078
void func_809C42A8(void); // func_809C42A8
void func_809C4598(void); // func_809C4598
void func_809C464C(void); // func_809C464C
void func_809C467C(void); // func_809C467C
void func_809C4790(void); // func_809C4790
void func_809C492C(void); // func_809C492C
void func_809C493C(void); // func_809C493C
void func_809C49CC(void); // func_809C49CC
void func_809C4B50(void); // func_809C4B50
void func_809C4B6C(void); // func_809C4B6C
void func_809C4BC4(void); // func_809C4BC4
void func_809C4DA4(void); // func_809C4DA4
void func_809C51B4(void); // func_809C51B4
void func_809C52B4(void); // func_809C52B4
void func_809C5310(void); // func_809C5310
void func_809C53A4(void); // func_809C53A4
void func_809C5408(void); // func_809C5408
void func_809C5524(void); // func_809C5524
void func_809C5598(void); // func_809C5598
void func_809C5738(void); // func_809C5738
void func_809C59A4(void); // func_809C59A4
void func_809C59F0(void); // func_809C59F0
void func_809C5AA4(void); // func_809C5AA4
void func_809C5B1C(void); // func_809C5B1C
void func_809C5BA0(void); // func_809C5BA0
void func_809C5BF4(void); // func_809C5BF4
void func_809C5E14(void); // func_809C5E14
void func_809C5F44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809C5F44
void func_809C5FC4(void); // func_809C5FC4
void func_809C64C0(void); // func_809C64C0
void func_809C6578(void); // func_809C6578
void func_809C66FC(void); // func_809C66FC
void func_809C6720(void); // func_809C6720
void func_809C6810(void); // func_809C6810
void func_809C6848(void); // func_809C6848
void func_809C6A04(void); // func_809C6A04
void func_809C6C2C(void); // func_809C6C2C
void func_809C6E30(void); // func_809C6E30
void func_809C6F98(void); // func_809C6F98
void func_809C72D8(void); // func_809C72D8
void func_809C7380(void); // func_809C7380
void func_809C7620(void); // func_809C7620
void func_809C7990(void); // func_809C7990
void func_809C7A90(void); // func_809C7A90
void func_809C7C14(void); // func_809C7C14
void func_809C7D14(void); // func_809C7D14
void func_809C7EB4(void); // func_809C7EB4
void func_809C7FFC(void); // func_809C7FFC
void func_809C80C0(void); // func_809C80C0
void func_809C81D0(void); // func_809C81D0
void func_809C8488(void); // func_809C8488
void func_809C8610(void); // func_809C8610
void func_809C8710(void); // func_809C8710
void func_809C8808(void); // func_809C8808
void func_809C898C(void); // func_809C898C
void func_809C8BF0(void); // func_809C8BF0
void func_809C8DE8(void); // func_809C8DE8
void func_809C8E44(void); // func_809C8E44
void func_809C8EE4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_809C8EE4
void func_809C8FAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809C8FAC
void func_809C9008(void); // func_809C9008
void func_809C9A60(void); // func_809C9A60
void func_809C9B54(void); // func_809C9B54
void func_809C9B9C(void); // func_809C9B9C
void func_809C9D7C(void); // func_809C9D7C
void func_809C9D8C(void); // func_809C9D8C
void func_809C9DC4(void); // func_809C9DC4
void func_809C9F28(void); // func_809C9F28
void func_809CA06C(void); // func_809CA06C
void func_809CA0BC(void); // func_809CA0BC
void func_809CA1F8(void); // func_809CA1F8
void func_809CA27C(void); // func_809CA27C
void func_809CA3F0(void); // func_809CA3F0
void func_809CA5A8(void); // func_809CA5A8
void func_809CA5D4(void); // func_809CA5D4
void func_809CA67C(void); // func_809CA67C
void func_809CA71C(void); // func_809CA71C
void func_809CA840(void); // func_809CA840
void func_809CA8E4(void); // func_809CA8E4
void func_809CAAF8(void); // func_809CAAF8
void func_809CABC0(void); // func_809CABC0
void func_809CACD0(void); // func_809CACD0
void func_809CADE8(void); // func_809CADE8
void func_809CAE5C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809CAE5C
void func_809CAF2C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809CAF2C
void func_809CAFEC(void); // func_809CAFEC
void func_809CB200(void); // func_809CB200
void func_809CB210(void); // func_809CB210
void func_809CB220(void); // func_809CB220
void func_809CB230(void); // func_809CB230
void func_809CB290(void); // func_809CB290
void func_809CB404(void); // func_809CB404
void func_809CB4A0(void); // func_809CB4A0
void func_809CB520(void); // func_809CB520
void func_809CB5A0(void); // func_809CB5A0
void func_809CB5D8(void); // func_809CB5D8
void func_809CB5FC(void); // func_809CB5FC
void func_809CB72C(void); // func_809CB72C
void func_809CB86C(void); // func_809CB86C
void func_809CB898(void); // func_809CB898
void func_809CB920(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809CB920
void func_809CBBC8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809CBBC8
void func_809CBCA0(void); // func_809CBCA0
void func_809CBCB4(void); // func_809CBCB4
void func_809CC060(void); // func_809CC060
void func_809CC1D4(void); // func_809CC1D4
void func_809CC270(void); // func_809CC270
void func_809CC2F0(void); // func_809CC2F0
void func_809CC370(void); // func_809CC370
void func_809CC3A8(void); // func_809CC3A8
void func_809CC3CC(void); // func_809CC3CC
void func_809CC4FC(void); // func_809CC4FC
void func_809CC63C(void); // func_809CC63C
void func_809CC668(void); // func_809CC668
void func_809CC6F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809CC6F0
void func_809CC984(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809CC984
void func_809CCA5C(void); // func_809CCA5C
void func_809CCA70(void); // func_809CCA70
void func_809CCDE0(void); // func_809CCDE0
void func_809CCE98(ActorEnBji01* this, GlobalContext* ctxt); // func_809CCE98
void func_809CCEE8(void); // func_809CCEE8
void func_809CD028(void); // func_809CD028
void func_809CD328(void); // func_809CD328
void func_809CD634(void); // func_809CD634
void func_809CD6B0(void); // func_809CD6B0
void func_809CD6C0(void); // func_809CD6C0
void func_809CD70C(void); // func_809CD70C
void func_809CD77C(void); // func_809CD77C
void func_809CD7AC(ActorEnBji01* this, GlobalContext* ctxt); // func_809CD7AC
void func_809CD914(void); // func_809CD914
void func_809CD940(void); // func_809CD940
void func_809CDA4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809CDA4C
void func_809CDB04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809CDB04
void func_809CDB88(void); // func_809CDB88
void func_809CDEC0(void); // func_809CDEC0
void func_809CE020(void); // func_809CE020
void func_809CE068(void); // func_809CE068
void func_809CE15C(void); // func_809CE15C
void func_809CE1D0(void); // func_809CE1D0
void func_809CE234(void); // func_809CE234
void func_809CE4C8(void); // func_809CE4C8
void func_809CE830(void); // func_809CE830
void func_809CEBC0(void); // func_809CEBC0
void func_809CEE74(void); // func_809CEE74
void func_809CEEAC(void); // func_809CEEAC
void func_809CEF0C(void); // func_809CEF0C
void func_809CEF30(void); // func_809CEF30
void func_809CF350(void); // func_809CF350
void func_809CF394(void); // func_809CF394
void func_809CF444(void); // func_809CF444
void func_809CF4EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809CF4EC
void func_809CF67C(void); // func_809CF67C
void func_809CF848(void); // func_809CF848
void func_809CF8EC(void); // func_809CF8EC
void func_809CF950(void); // func_809CF950
void func_809CF9A0(void); // func_809CF9A0
void func_809CFA00(void); // func_809CFA00
void func_809CFA54(void); // func_809CFA54
void func_809CFBC4(void); // func_809CFBC4
void func_809CFC38(void); // func_809CFC38
void func_809CFD98(void); // func_809CFD98
void func_809CFE28(void); // func_809CFE28
void func_809CFF94(void); // func_809CFF94
void func_809D0090(void); // func_809D0090
void func_809D0138(void); // func_809D0138
void func_809D0168(void); // func_809D0168
void func_809D0530(void); // func_809D0530
void func_809D0550(void); // func_809D0550
void func_809D0678(void); // func_809D0678
void func_809D082C(void); // func_809D082C
void func_809D089C(void); // func_809D089C
void func_809D092C(void); // func_809D092C
void func_809D0AA4(void); // func_809D0AA4
void func_809D0CE8(void); // func_809D0CE8
void func_809D118C(void); // func_809D118C
void func_809D119C(void); // func_809D119C
void func_809D1258(void); // func_809D1258
void func_809D12B4(void); // func_809D12B4
void func_809D1AB8(void); // func_809D1AB8
void func_809D1B2C(void); // func_809D1B2C
void func_809D1E5C(void); // func_809D1E5C
void func_809D1E74(void); // func_809D1E74
void func_809D1EA4(void); // func_809D1EA4
void func_809D20D0(void); // func_809D20D0
void func_809D24EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); // func_809D24EC
void func_809D2544(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_809D2544
void func_809D2574(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_809D2574
void func_809D2588(void); // func_809D2588
void func_809D25E8(void); // func_809D25E8
void func_809D2664(void); // func_809D2664
void func_809D26B8(void); // func_809D26B8
void func_809D2780(void); // func_809D2780
void func_809D27D4(void); // func_809D27D4
void func_809D2858(void); // func_809D2858
void func_809D2914(void); // func_809D2914
void func_809D2A44(void); // func_809D2A44
void func_809D2AA0(void); // func_809D2AA0
void func_809D2BCC(void); // func_809D2BCC
void func_809D2CDC(void); // func_809D2CDC
void func_809D2DE8(void); // func_809D2DE8
void func_809D2E4C(void); // func_809D2E4C
void func_809D3074(void); // func_809D3074
void func_809D30D0(void); // func_809D30D0
void func_809D32B4(void); // func_809D32B4
void func_809D3374(void); // func_809D3374
void func_809D3400(void); // func_809D3400
void func_809D345C(void); // func_809D345C
void func_809D34D4(void); // func_809D34D4
void func_809D3530(void); // func_809D3530
void func_809D35A8(void); // func_809D35A8
void func_809D365C(void); // func_809D365C
void func_809D370C(void); // func_809D370C
void func_809D3A7C(void); // func_809D3A7C
void func_809D3ADC(void); // func_809D3ADC
void func_809D3C10(void); // func_809D3C10
void func_809D3CD0(void); // func_809D3CD0
void func_809D441C(void); // func_809D441C
void func_809D4464(void); // func_809D4464
void func_809D44C0(void); // func_809D44C0
void func_809D4668(void); // func_809D4668
void func_809D46E4(void); // func_809D46E4
void func_809D519C(void); // func_809D519C
void func_809D5584(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809D5584
void func_809D55CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809D55CC
void func_809D5988(void); // func_809D5988
void func_809D5B0C(void); // func_809D5B0C
void func_809D5BC4(void); // func_809D5BC4
void func_809D5FB4(void); // func_809D5FB4
void func_809D606C(void); // func_809D606C
void func_809D62D4(void); // func_809D62D4
void func_809D6314(void); // func_809D6314
void func_809D6424(void); // func_809D6424
void func_809D6488(void); // func_809D6488
void func_809D64E0(void); // func_809D64E0
void func_809D6540(void); // func_809D6540
void func_809D6588(void); // func_809D6588
void func_809D65E0(void); // func_809D65E0
void func_809D670C(void); // func_809D670C
void func_809D694C(void); // func_809D694C
void func_809D6B08(void); // func_809D6B08
void func_809D6BB4(void); // func_809D6BB4
void func_809D6C98(void); // func_809D6C98
void func_809D6E7C(void); // func_809D6E7C
void func_809D73D4(void); // func_809D73D4
void func_809DA1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_809DA1D0
void func_809DA22C(void); // func_809DA22C
void func_809DA24C(void); // func_809DA24C
void func_809DA264(void); // func_809DA264
void func_809DA344(void); // func_809DA344
void func_809DA460(void); // func_809DA460
void func_809DA50C(void); // func_809DA50C
void func_809DA5AC(void); // func_809DA5AC
void func_809DAA64(void); // func_809DAA64
void func_809DAA74(void); // func_809DAA74
void func_809DAA98(void); // func_809DAA98
void func_809DAAA8(void); // func_809DAAA8
void func_809DAB78(void); // func_809DAB78
void func_809DBFB4(void); // func_809DBFB4
void func_809DC218(void); // func_809DC218
void func_809DC320(void); // func_809DC320
void func_809DC78C(void); // func_809DC78C
void func_809DCA00(void); // func_809DCA00
void func_809DD0A8(void); // func_809DD0A8
void func_809DD0CC(void); // func_809DD0CC
void func_809DD2F8(void); // func_809DD2F8
void func_809DD934(void); // func_809DD934
void func_809DEAC4(void); // func_809DEAC4
void func_809E2760(void); // func_809E2760
void func_809E2788(void); // func_809E2788
void func_809E2880(void); // func_809E2880
void func_809E299C(void); // func_809E299C
void func_809E2AB4(void); // func_809E2AB4
void func_809E2B8C(void); // func_809E2B8C
void func_809E2C1C(void); // func_809E2C1C
void func_809E2C3C(void); // func_809E2C3C
void func_809E2D64(void); // func_809E2D64
void func_809E2DA0(void); // func_809E2DA0
void func_809E2F7C(void); // func_809E2F7C
void func_809E343C(void); // func_809E343C
void func_809E344C(void); // func_809E344C
void func_809E34B8(void); // func_809E34B8
void func_809E38EC(void); // func_809E38EC
void func_809E3968(void); // func_809E3968
void func_809E3D34(void); // func_809E3D34
void func_809E3D98(void); // func_809E3D98
void func_809E4180(void); // func_809E4180
void func_809E421C(void); // func_809E421C
void func_809E4674(void); // func_809E4674
void func_809E475C(void); // func_809E475C
void func_809E4910(void); // func_809E4910
void func_809E497C(void); // func_809E497C
void func_809E4C34(void); // func_809E4C34
void func_809E4C90(void); // func_809E4C90
void func_809E4E2C(void); // func_809E4E2C
void func_809E4E80(void); // func_809E4E80
void func_809E5ADC(void); // func_809E5ADC
void func_809E5B64(void); // func_809E5B64
void func_809E65F4(void); // func_809E65F4
void func_809E6640(void); // func_809E6640
void func_809E69A4(void); // func_809E69A4
void func_809E6A38(void); // func_809E6A38
void func_809E6B70(void); // func_809E6B70
void func_809E6BC0(void); // func_809E6BC0
void func_809E6CB4(void); // func_809E6CB4
void func_809E70EC(void); // func_809E70EC
void func_809E7920(void); // func_809E7920
void func_809E79C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809E79C4
void func_809E7AA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809E7AA8
void func_809E7C0C(void); // func_809E7C0C
void func_809E7D00(void); // func_809E7D00
void func_809E81E4(void); // func_809E81E4
void func_809E8810(void); // func_809E8810
void func_809E8BEC(void); // func_809E8BEC
void func_809EC040(void); // func_809EC040
void func_809EC0D0(void); // func_809EC0D0
void func_809EC534(void); // func_809EC534
void func_809EC544(void); // func_809EC544
void func_809EC568(void); // func_809EC568
void func_809EC618(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13); // func_809EC618
void func_809EC7C0(void); // func_809EC7C0
void func_809EC830(void); // func_809EC830
void func_809EC858(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_809EC858
void func_809EC88C(void); // func_809EC88C
void func_809EC958(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_809EC958
void func_809ECA30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13); // func_809ECA30
void func_809ECBE4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16, UNK_TYPE4 param_17, UNK_TYPE4 param_18); // func_809ECBE4
void func_809ECD00(void); // func_809ECD00
void func_809ECD18(void); // func_809ECD18
void func_809ECEF4(void); // func_809ECEF4
void func_809ECF58(void); // func_809ECF58
void func_809ED224(void); // func_809ED224
void func_809ED2A0(void); // func_809ED2A0
void func_809ED45C(void); // func_809ED45C
void func_809ED50C(void); // func_809ED50C
void func_809ED8BC(void); // func_809ED8BC
void func_809EDCCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809EDCCC
void func_809EDECC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809EDECC
void func_809EDF58(void); // func_809EDF58
void func_809EE4E0(void); // func_809EE4E0
void func_809EE668(void); // func_809EE668
void func_809EE6F8(void); // func_809EE6F8
void func_809EEC70(void); // func_809EEC70
void func_809EECBC(void); // func_809EECBC
void func_809EEDD0(void); // func_809EEDD0
void func_809EEDE8(void); // func_809EEDE8
void func_809EF9BC(void); // func_809EF9BC
void func_809EFAB4(void); // func_809EFAB4
void func_809EFE50(void); // func_809EFE50
void func_809F0014(void); // func_809F0014
void func_809F0058(void); // func_809F0058
void func_809F00CC(void); // func_809F00CC
void func_809F010C(void); // func_809F010C
void func_809F01CC(void); // func_809F01CC
void func_809F0244(void); // func_809F0244
void func_809F02D0(void); // func_809F02D0
void func_809F0374(void); // func_809F0374
void func_809F0474(void); // func_809F0474
void func_809F04C0(void); // func_809F04C0
void func_809F0538(void); // func_809F0538
void func_809F0590(void); // func_809F0590
void func_809F0650(void); // func_809F0650
void func_809F06B8(void); // func_809F06B8
void func_809F0708(void); // func_809F0708
void func_809F0780(void); // func_809F0780
void func_809F0A0C(void); // func_809F0A0C
void func_809F0A64(void); // func_809F0A64
void func_809F0ABC(void); // func_809F0ABC
void func_809F0B0C(void); // func_809F0B0C
void func_809F0CCC(void); // func_809F0CCC
void func_809F1050(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809F1050
void func_809F1170(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809F1170
void func_809F1284(void); // func_809F1284
void func_809F12A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809F12A0
void func_809F135C(void); // func_809F135C
void func_809F1404(void); // func_809F1404
void func_809F1430(void); // func_809F1430
void func_809F1464(void); // func_809F1464
void func_809F14AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809F14AC
void func_809F1550(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809F1550
void func_809F159C(void); // func_809F159C
void func_809F2120(void); // func_809F2120
void func_809F2140(void); // func_809F2140
void func_809F2268(void); // func_809F2268
void func_809F23BC(void); // func_809F23BC
void func_809F23CC(void); // func_809F23CC
void func_809F24A8(void); // func_809F24A8
void func_809F24C8(void); // func_809F24C8
void func_809F2B64(void); // func_809F2B64
void func_809F2C44(void); // func_809F2C44
void func_809F2E14(void); // func_809F2E14
void func_809F2E34(void); // func_809F2E34
void func_809F2ED0(void); // func_809F2ED0
void func_809F2EE8(void); // func_809F2EE8
void func_809F2F0C(void); // func_809F2F0C
void func_809F334C(void); // func_809F334C
void func_809F4980(void); // func_809F4980
void func_809F49A0(void); // func_809F49A0
void func_809F49C0(void); // func_809F49C0
void func_809F4AE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809F4AE8
void func_809F4BB0(void); // func_809F4BB0
void func_809F4C40(void); // func_809F4C40
void func_809F4CBC(void); // func_809F4CBC
void func_809F4D10(void); // func_809F4D10
void func_809F4D54(void); // func_809F4D54
void func_809F4FAC(void); // func_809F4FAC
void func_809F4FF8(void); // func_809F4FF8
void func_809F51E8(void); // func_809F51E8
void func_809F52CC(void); // func_809F52CC
void func_809F536C(void); // func_809F536C
void func_809F5494(void); // func_809F5494
void func_809F552C(void); // func_809F552C
void func_809F5DA0(void); // func_809F5DA0
void func_809F5E14(void); // func_809F5E14
void func_809F5E88(void); // func_809F5E88
void func_809F64F4(void); // func_809F64F4
void func_809F65F4(void); // func_809F65F4
void func_809F7400(void); // func_809F7400
void func_809F748C(void); // func_809F748C
void func_809F7688(void); // func_809F7688
void func_809F76D0(void); // func_809F76D0
void func_809F77A8(void); // func_809F77A8
void func_809F783C(void); // func_809F783C
void func_809F7968(void); // func_809F7968
void func_809F7AB4(void); // func_809F7AB4
void func_809F7BC4(void); // func_809F7BC4
void func_809F7D2C(void); // func_809F7D2C
void func_809F805C(void); // func_809F805C
void func_809F8658(void); // func_809F8658
void func_809F86B8(void); // func_809F86B8
void func_809F87C8(void); // func_809F87C8
void func_809F8908(void); // func_809F8908
void func_809F8AB0(void); // func_809F8AB0
void func_809F8B1C(void); // func_809F8B1C
void func_809F8D04(void); // func_809F8D04
void func_809F8DEC(void); // func_809F8DEC
void func_809F8E68(void); // func_809F8E68
void func_809F8EC8(void); // func_809F8EC8
void func_809F91D4(void); // func_809F91D4
void func_809F9280(void); // func_809F9280
void func_809F93DC(void); // func_809F93DC
void func_809F94AC(void); // func_809F94AC
void func_809F99C4(void); // func_809F99C4
void func_809F9CEC(void); // func_809F9CEC
void func_809F9E94(void); // func_809F9E94
void func_809FA1B4(void); // func_809FA1B4
void func_809FAA44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE2 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); // func_809FAA44
void func_809FB114(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809FB114
void func_809FB504(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809FB504
void func_809FB55C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809FB55C
void func_809FB728(void); // func_809FB728
void func_809FB7D4(void); // func_809FB7D4
void func_809FBB9C(void); // func_809FBB9C
void func_809FBF94(void); // func_809FBF94
void func_809FC1C8(void); // func_809FC1C8
void func_809FC4C0(void); // func_809FC4C0
void func_809FC8B0(void); // func_809FC8B0
void func_809FC960(void); // func_809FC960
void func_809FCBC8(void); // func_809FCBC8
void func_809FCC70(void); // func_809FCC70
void func_809FCCCC(void); // func_809FCCCC
void func_809FD5F8(void); // func_809FD5F8
void func_809FD710(void); // func_809FD710
void func_809FD818(void); // func_809FD818
void func_809FD89C(void); // func_809FD89C
void func_809FD984(void); // func_809FD984
void func_809FDAB0(void); // func_809FDAB0
void func_809FDB2C(void); // func_809FDB2C
void func_809FDBA0(void); // func_809FDBA0
void func_809FDEDC(void); // func_809FDEDC
void func_809FDF54(void); // func_809FDF54
void func_809FE068(void); // func_809FE068
void func_809FE0E4(void); // func_809FE0E4
void func_809FE2D4(void); // func_809FE2D4
void func_809FE348(void); // func_809FE348
void func_809FE4B0(void); // func_809FE4B0
void func_809FE524(void); // func_809FE524
void func_809FE6B0(void); // func_809FE6B0
void func_809FE734(void); // func_809FE734
void func_809FEE70(void); // func_809FEE70
void func_809FF0E4(void); // func_809FF0E4
void func_809FF12C(void); // func_809FF12C
void func_809FF5CC(void); // func_809FF5CC
void func_809FF678(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_809FF678
void func_809FF6B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_809FF6B0
void func_809FF810(void); // func_809FF810
void func_809FF900(void); // func_809FF900
void func_809FFA04(void); // func_809FFA04
void func_809FFA80(void); // func_809FFA80
void func_809FFE64(void); // func_809FFE64
void func_809FFEAC(void); // func_809FFEAC
void func_80A0021C(void); // func_80A0021C
void func_80A00274(void); // func_80A00274
void func_80A00484(void); // func_80A00484
void func_80A00554(void); // func_80A00554
void func_80A006D0(void); // func_80A006D0
void func_80A006F4(void); // func_80A006F4
void func_80A00720(void); // func_80A00720
void func_80A016E4(void); // func_80A016E4
void func_80A01750(void); // func_80A01750
void func_80A025AC(void); // func_80A025AC
void func_80A0264C(void); // func_80A0264C
void func_80A02B30(void); // func_80A02B30
void func_80A02C54(void); // func_80A02C54
void func_80A03238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE1 param_9, UNK_TYPE4 param_10); // func_80A03238
void func_80A036C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A036C4
void func_80A03868(void); // func_80A03868
void func_80A03F18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A03F18
void func_80A03F5C(void); // func_80A03F5C
void func_80A0434C(void); // func_80A0434C
void func_80A045A8(void); // func_80A045A8
void func_80A04768(void); // func_80A04768
void func_80A04878(void); // func_80A04878
void func_80A04890(void); // func_80A04890
void func_80A04DE0(void); // func_80A04DE0
void func_80A04E5C(void); // func_80A04E5C
void func_80A055E0(void); // func_80A055E0
void func_80A05608(void); // func_80A05608
void func_80A05694(void); // func_80A05694
void func_80A057A0(void); // func_80A057A0
void func_80A05AF8(void); // func_80A05AF8
void func_80A05B50(void); // func_80A05B50
void func_80A05C88(void); // func_80A05C88
void func_80A05DDC(void); // func_80A05DDC
void func_80A06500(void); // func_80A06500
void func_80A06990(void); // func_80A06990
void func_80A06C64(void); // func_80A06C64
void func_80A06E24(void); // func_80A06E24
void func_80A06F48(void); // func_80A06F48
void func_80A07604(void); // func_80A07604
void func_80A07638(void); // func_80A07638
void func_80A07740(void); // func_80A07740
void func_80A0A8A0(void); // func_80A0A8A0
void func_80A0A95C(void); // func_80A0A95C
void func_80A0A96C(void); // func_80A0A96C
void func_80A0A9E4(void); // func_80A0A9E4
void func_80A0AA40(void); // func_80A0AA40
void func_80A0AD50(void); // func_80A0AD50
void func_80A0AE1C(void); // func_80A0AE1C
void func_80A0AFDC(void); // func_80A0AFDC
void func_80A0B078(void); // func_80A0B078
void func_80A0B184(void); // func_80A0B184
void func_80A0B290(void); // func_80A0B290
void func_80A0B35C(void); // func_80A0B35C
void func_80A0B500(void); // func_80A0B500
void func_80A0B5F0(void); // func_80A0B5F0
void func_80A0B75C(void); // func_80A0B75C
void func_80A0B834(void); // func_80A0B834
void func_80A0B8CC(void); // func_80A0B8CC
void func_80A0BB08(void); // func_80A0BB08
void func_80A0BC84(void); // func_80A0BC84
void func_80A0BCD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A0BCD8
void func_80A0BD40(void); // func_80A0BD40
void func_80A0BE60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_80A0BE60
void func_80A0BF70(void); // func_80A0BF70
void func_80A0C270(void); // func_80A0C270
void func_80A0C780(void); // func_80A0C780
void func_80A0C790(void); // func_80A0C790
void func_80A0C7A0(void); // func_80A0C7A0
void func_80A0C7B0(void); // func_80A0C7B0
void func_80A0C810(void); // func_80A0C810
void func_80A0C8AC(void); // func_80A0C8AC
void func_80A0C8B8(void); // func_80A0C8B8
void func_80A0C938(void); // func_80A0C938
void func_80A0CA38(void); // func_80A0CA38
void func_80A0CC88(void); // func_80A0CC88
void func_80A0CCEC(void); // func_80A0CCEC
void func_80A0CD48(void); // func_80A0CD48
void func_80A0CE10(void); // func_80A0CE10
void func_80A0CED4(void); // func_80A0CED4
void func_80A0D008(void); // func_80A0D008
void func_80A0D034(void); // func_80A0D034
void func_80A0D0B8(void); // func_80A0D0B8
void func_80A0D188(void); // func_80A0D188
void func_80A0D1F4(void); // func_80A0D1F4
void func_80A0D258(void); // func_80A0D258
void func_80A0D2B8(void); // func_80A0D2B8
void func_80A0D320(void); // func_80A0D320
void func_80A0D388(void); // func_80A0D388
void func_80A0D3C4(void); // func_80A0D3C4
void func_80A0D414(void); // func_80A0D414
void func_80A0D4A0(void); // func_80A0D4A0
void func_80A0D628(void); // func_80A0D628
void func_80A0D74C(void); // func_80A0D74C
void func_80A0D77C(void); // func_80A0D77C
void func_80A0D850(void); // func_80A0D850
void func_80A0D904(void); // func_80A0D904
void func_80A0DA5C(void); // func_80A0DA5C
void func_80A0DAAC(void); // func_80A0DAAC
void func_80A0DB78(void); // func_80A0DB78
void func_80A0DCC4(void); // func_80A0DCC4
void func_80A0DD40(void); // func_80A0DD40
void func_80A0DE64(void); // func_80A0DE64
void func_80A0DFD0(void); // func_80A0DFD0
void func_80A0E0C0(void); // func_80A0E0C0
void func_80A0E1B8(void); // func_80A0E1B8
void func_80A0E258(void); // func_80A0E258
void func_80A0E330(void); // func_80A0E330
void func_80A0E420(void); // func_80A0E420
void func_80A0E4DC(void); // func_80A0E4DC
void func_80A0E518(void); // func_80A0E518
void func_80A0E554(void); // func_80A0E554
void func_80A0E884(void); // func_80A0E884
void func_80A0E96C(void); // func_80A0E96C
void func_80A0E9E0(void); // func_80A0E9E0
void func_80A0EA84(void); // func_80A0EA84
void func_80A0EAF8(void); // func_80A0EAF8
void func_80A0EBC0(void); // func_80A0EBC0
void func_80A0EC98(void); // func_80A0EC98
void func_80A0ED7C(void); // func_80A0ED7C
void func_80A0EDA0(void); // func_80A0EDA0
void func_80A0EE3C(void); // func_80A0EE3C
void func_80A0EEC8(void); // func_80A0EEC8
void func_80A0EF48(void); // func_80A0EF48
void func_80A0F014(void); // func_80A0F014
void func_80A0F1C4(void); // func_80A0F1C4
void func_80A0F284(void); // func_80A0F284
void func_80A0F2C8(void); // func_80A0F2C8
void func_80A0F2FC(void); // func_80A0F2FC
void func_80A0F39C(void); // func_80A0F39C
void func_80A0F3D4(void); // func_80A0F3D4
void func_80A0F470(void); // func_80A0F470
void func_80A0F554(void); // func_80A0F554
void func_80A0F638(void); // func_80A0F638
void func_80A0F6B0(void); // func_80A0F6B0
void func_80A0FA0C(void); // func_80A0FA0C
void func_80A0FADC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6); // func_80A0FADC
void func_80A0FD4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_80A0FD4C
void func_80A0FEE8(void); // func_80A0FEE8
void func_80A10290(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A10290
void func_80A102C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A102C8
void func_80A10308(void); // func_80A10308
void func_80A10344(void); // func_80A10344
void func_80A10368(void); // func_80A10368
void func_80A104E4(void); // func_80A104E4
void func_80A10608(void); // func_80A10608
void func_80A10FD0(void); // func_80A10FD0
void func_80A11000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16, UNK_TYPE4 param_17, UNK_TYPE4 param_18, UNK_TYPE4 param_19); // func_80A11000
void func_80A11144(void); // func_80A11144
void func_80A1143C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); // func_80A1143C
void func_80A115B4(void); // func_80A115B4
void func_80A118F8(void); // func_80A118F8
void func_80A11BF8(void); // func_80A11BF8
void func_80A11EC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_80A11EC0
void func_80A1203C(void); // func_80A1203C
void func_80A1213C(void); // func_80A1213C
void func_80A121F4(void); // func_80A121F4
void func_80A1222C(void); // func_80A1222C
void func_80A122EC(void); // func_80A122EC
void func_80A123A0(void); // func_80A123A0
void func_80A124A0(void); // func_80A124A0
void func_80A124FC(void); // func_80A124FC
void func_80A125BC(void); // func_80A125BC
void func_80A12660(void); // func_80A12660
void func_80A126BC(void); // func_80A126BC
UNK_TYPE4 func_80A12774(s32 param_1); // func_80A12774
void func_80A12868(void); // func_80A12868
UNK_TYPE4 func_80A12954(s32 param_1, s32 param_2); // func_80A12954
void func_80A12A64(void); // func_80A12A64
void func_80A12B78(void); // func_80A12B78
void func_80A12C48(void); // func_80A12C48
void func_80A12D6C(void); // func_80A12D6C
void func_80A12DF4(void); // func_80A12DF4
void func_80A12E80(void); // func_80A12E80
void func_80A12FE8(void); // func_80A12FE8
void func_80A131F8(void); // func_80A131F8
void func_80A132C8(s32 param_1, s32 param_2); // func_80A132C8
void func_80A133A8(void); // func_80A133A8
void func_80A13400(void); // func_80A13400
void func_80A134B0(void); // func_80A134B0
void func_80A134F4(void); // func_80A134F4
void func_80A13564(void); // func_80A13564
void func_80A136B8(void); // func_80A136B8
void func_80A13728(void); // func_80A13728
void func_80A137C0(void); // func_80A137C0
void func_80A139E4(void); // func_80A139E4
void func_80A13B1C(void); // func_80A13B1C
void func_80A13E80(void); // func_80A13E80
void func_80A14018(void); // func_80A14018
void func_80A14104(void); // func_80A14104
void func_80A141D4(void); // func_80A141D4
void func_80A1428C(void); // func_80A1428C
void func_80A14324(void); // func_80A14324
void func_80A143A8(Actor* param_1, UNK_TYPE4 param_2); // func_80A143A8
void func_80A14430(void); // func_80A14430
void func_80A1449C(void); // func_80A1449C
void func_80A144F4(void); // func_80A144F4
void func_80A145AC(void); // func_80A145AC
void func_80A14668(void); // func_80A14668
void func_80A146CC(void); // func_80A146CC
void func_80A14798(void); // func_80A14798
void func_80A149B0(Actor* param_1, s32 param_2); // func_80A149B0
void func_80A14B30(void); // func_80A14B30
void func_80A14E14(void); // func_80A14E14
void func_80A14E74(void); // func_80A14E74
void func_80A14EB0(Actor* param_1, UNK_TYPE4 param_2); // func_80A14EB0
void func_80A14FC8(void); // func_80A14FC8
void func_80A153FC(void); // func_80A153FC
void func_80A15684(void); // func_80A15684
void func_80A157C4(void); // func_80A157C4
void func_80A1590C(void); // func_80A1590C
void func_80A15960(void); // func_80A15960
void func_80A159B0(void); // func_80A159B0
void func_80A15B80(void); // func_80A15B80
void func_80A15D04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A15D04
void func_80A15E38(void); // func_80A15E38
void func_80A15FEC(void); // func_80A15FEC
void func_80A16D40(void); // func_80A16D40
void func_80A16D6C(void); // func_80A16D6C
void func_80A16D90(void); // func_80A16D90
void func_80A17018(void); // func_80A17018
void func_80A17060(void); // func_80A17060
void func_80A1712C(void); // func_80A1712C
void func_80A171D8(void); // func_80A171D8
void func_80A17414(void); // func_80A17414
void func_80A17464(void); // func_80A17464
void func_80A17530(void); // func_80A17530
void func_80A175E4(void); // func_80A175E4
void func_80A17848(void); // func_80A17848
void func_80A178A0(void); // func_80A178A0
void func_80A179C8(void); // func_80A179C8
void func_80A17C6C(void); // func_80A17C6C
void func_80A17D14(void); // func_80A17D14
void func_80A17D54(void); // func_80A17D54
void func_80A17DDC(void); // func_80A17DDC
void func_80A17E1C(void); // func_80A17E1C
void func_80A18080(void); // func_80A18080
void func_80A180B4(void); // func_80A180B4
void func_80A181B4(void); // func_80A181B4
void func_80A1859C(void); // func_80A1859C
void func_80A18A08(void); // func_80A18A08
void func_80A18A90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80A18A90
void func_80A18B8C(void); // func_80A18B8C
void func_80A18DA0(void); // func_80A18DA0
void func_80A19740(void); // func_80A19740
void func_80A19778(void); // func_80A19778
void func_80A19910(void); // func_80A19910
void func_80A1994C(void); // func_80A1994C
void func_80A19B64(void); // func_80A19B64
void func_80A19B98(void); // func_80A19B98
void func_80A19BA8(void); // func_80A19BA8
void func_80A19E84(void); // func_80A19E84
void func_80A19EE0(void); // func_80A19EE0
void func_80A19F18(void); // func_80A19F18
void func_80A19F78(void); // func_80A19F78
void func_80A19FE0(void); // func_80A19FE0
void func_80A1A220(void); // func_80A1A220
void func_80A1A330(void); // func_80A1A330
void func_80A1A360(void); // func_80A1A360
void func_80A1A500(void); // func_80A1A500
void func_80A1A56C(void); // func_80A1A56C
void func_80A1A750(void); // func_80A1A750
void func_80A1A7CC(void); // func_80A1A7CC
void func_80A1A9AC(void); // func_80A1A9AC
void func_80A1AA14(void); // func_80A1AA14
void func_80A1AA28(void); // func_80A1AA28
void func_80A1AA38(void); // func_80A1AA38
void func_80A1AA4C(void); // func_80A1AA4C
void func_80A1AAE8(void); // func_80A1AAE8
void func_80A1AB00(void); // func_80A1AB00
void func_80A1ABD8(void); // func_80A1ABD8
void func_80A1ABF0(void); // func_80A1ABF0
void func_80A1ACCC(void); // func_80A1ACCC
void func_80A1ACE0(void); // func_80A1ACE0
void func_80A1AE08(void); // func_80A1AE08
void func_80A1AE1C(void); // func_80A1AE1C
void func_80A1AE6C(void); // func_80A1AE6C
void func_80A1AF68(void); // func_80A1AF68
void func_80A1B3D0(void); // func_80A1B3D0
void func_80A1B840(void); // func_80A1B840
void func_80A1B914(void); // func_80A1B914
void func_80A1B994(void); // func_80A1B994
void func_80A1B9CC(void); // func_80A1B9CC
void func_80A1BA04(void); // func_80A1BA04
void func_80A1BA44(void); // func_80A1BA44
void func_80A1BD80(void); // func_80A1BD80
void func_80A1C0FC(void); // func_80A1C0FC
void func_80A1C328(void); // func_80A1C328
void func_80A1C554(void); // func_80A1C554
void func_80A1C5E8(void); // func_80A1C5E8
void func_80A1C62C(void); // func_80A1C62C
void func_80A1C664(void); // func_80A1C664
void func_80A1C7EC(void); // func_80A1C7EC
void func_80A1C818(void); // func_80A1C818
void func_80A1C838(void); // func_80A1C838
void func_80A1CBF8(void); // func_80A1CBF8
void func_80A1CC0C(void); // func_80A1CC0C
void func_80A1CD10(void); // func_80A1CD10
void func_80A1CEF4(void); // func_80A1CEF4
void func_80A1D14C(void); // func_80A1D14C
void func_80A1D1CC(void); // func_80A1D1CC
void func_80A1DA50(void); // func_80A1DA50
void func_80A1DAAC(void); // func_80A1DAAC
void func_80A1DB2C(void); // func_80A1DB2C
void func_80A1DC5C(void); // func_80A1DC5C
void func_80A1DCCC(void); // func_80A1DCCC
void func_80A1DD18(void); // func_80A1DD18
void func_80A1DE10(void); // func_80A1DE10
void func_80A1DE58(void); // func_80A1DE58
void func_80A1DE84(void); // func_80A1DE84
void func_80A1DEB8(void); // func_80A1DEB8
void func_80A1DFA0(void); // func_80A1DFA0
void func_80A1E074(void); // func_80A1E074
void func_80A1E2D8(void); // func_80A1E2D8
void func_80A1E334(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A1E334
void func_80A1E394(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A1E394
void func_80A1E3D8(void); // func_80A1E3D8
void func_80A1E648(void); // func_80A1E648
void func_80A1E694(void); // func_80A1E694
void func_80A1E6D4(void); // func_80A1E6D4
void func_80A1E728(void); // func_80A1E728
void func_80A1E97C(void); // func_80A1E97C
void func_80A1E9C4(void); // func_80A1E9C4
void func_80A1E9E0(void); // func_80A1E9E0
void func_80A1EA10(void); // func_80A1EA10
void func_80A1EA4C(void); // func_80A1EA4C
void func_80A1EAAC(void); // func_80A1EAAC
void func_80A1EAE0(void); // func_80A1EAE0
void func_80A1EB40(void); // func_80A1EB40
void func_80A1EB54(void); // func_80A1EB54
void func_80A1EC24(void); // func_80A1EC24
void func_80A1EC38(void); // func_80A1EC38
void func_80A1ECC0(void); // func_80A1ECC0
void func_80A1ECD4(void); // func_80A1ECD4
void func_80A1ED70(void); // func_80A1ED70
void func_80A1EE1C(void); // func_80A1EE1C
void func_80A1F410(void); // func_80A1F410
void func_80A1F460(void); // func_80A1F460
void func_80A1F470(void); // func_80A1F470
void func_80A1F56C(void); // func_80A1F56C
void func_80A1F5AC(void); // func_80A1F5AC
void func_80A1F63C(void); // func_80A1F63C
void func_80A1F75C(void); // func_80A1F75C
void func_80A1F970(void); // func_80A1F970
void func_80A1F9AC(void); // func_80A1F9AC
void func_80A1FC50(void); // func_80A1FC50
void func_80A1FE50(void); // func_80A1FE50
void func_80A200A0(void); // func_80A200A0
void func_80A200E0(void); // func_80A200E0
void func_80A201CC(void); // func_80A201CC
void func_80A20284(void); // func_80A20284
void func_80A2030C(void); // func_80A2030C
void func_80A20320(void); // func_80A20320
void func_80A20378(void); // func_80A20378
void func_80A203DC(void); // func_80A203DC
void func_80A20670(void); // func_80A20670
void func_80A206DC(void); // func_80A206DC
void func_80A20710(void); // func_80A20710
void func_80A2075C(void); // func_80A2075C
void func_80A2079C(void); // func_80A2079C
void func_80A20800(void); // func_80A20800
void func_80A20858(void); // func_80A20858
void func_80A208F8(void); // func_80A208F8
void func_80A20A50(void); // func_80A20A50
void func_80A20CF4(void); // func_80A20CF4
void func_80A20D10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A20D10
void func_80A20DA4(void); // func_80A20DA4
void func_80A21150(void); // func_80A21150
void func_80A211F4(void); // func_80A211F4
void func_80A212F0(void); // func_80A212F0
void func_80A21370(void); // func_80A21370
void func_80A21548(void); // func_80A21548
void func_80A216D4(void); // func_80A216D4
void func_80A21934(void); // func_80A21934
void func_80A21990(void); // func_80A21990
void func_80A21C30(void); // func_80A21C30
void func_80A21C88(void); // func_80A21C88
void func_80A21CB4(void); // func_80A21CB4
void func_80A21CD8(void); // func_80A21CD8
void func_80A21D1C(void); // func_80A21D1C
void func_80A21E9C(void); // func_80A21E9C
void func_80A21F68(void); // func_80A21F68
void func_80A21F74(void); // func_80A21F74
void func_80A22230(void); // func_80A22230
void func_80A222D4(void); // func_80A222D4
void func_80A22308(void); // func_80A22308
void func_80A22334(void); // func_80A22334
void func_80A2244C(void); // func_80A2244C
void func_80A224A4(void); // func_80A224A4
void func_80A22628(void); // func_80A22628
void func_80A2264C(void); // func_80A2264C
void func_80A22728(void); // func_80A22728
void func_80A2273C(void); // func_80A2273C
void func_80A227A4(void); // func_80A227A4
void func_80A227C0(void); // func_80A227C0
void func_80A22880(void); // func_80A22880
void func_80A228D8(void); // func_80A228D8
void func_80A22D40(void); // func_80A22D40
void func_80A22DB8(void); // func_80A22DB8
void func_80A22E94(void); // func_80A22E94
void func_80A22FE4(void); // func_80A22FE4
void func_80A23090(void); // func_80A23090
void func_80A2311C(void); // func_80A2311C
void func_80A2319C(void); // func_80A2319C
void func_80A232C4(void); // func_80A232C4
void func_80A23370(void); // func_80A23370
void func_80A2339C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A2339C
void func_80A23690(void); // func_80A23690
void func_80A236D4(void); // func_80A236D4
void func_80A237A4(void); // func_80A237A4
void func_80A23938(void); // func_80A23938
void func_80A23B88(void); // func_80A23B88
void func_80A23D08(void); // func_80A23D08
void func_80A23F90(void); // func_80A23F90
void func_80A24118(void); // func_80A24118
void func_80A24384(void); // func_80A24384
void func_80A243E0(void); // func_80A243E0
void func_80A24680(void); // func_80A24680
void func_80A246D8(void); // func_80A246D8
void func_80A2491C(void); // func_80A2491C
void func_80A24954(void); // func_80A24954
void func_80A24A48(void); // func_80A24A48
void func_80A24AA8(void); // func_80A24AA8
void func_80A24B74(void); // func_80A24B74
void func_80A24BDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A24BDC
void func_80A24DC4(void); // func_80A24DC4
void func_80A24DD0(void); // func_80A24DD0
void func_80A2508C(void); // func_80A2508C
void func_80A25238(void); // func_80A25238
void func_80A252DC(void); // func_80A252DC
void func_80A25404(void); // func_80A25404
void func_80A2541C(void); // func_80A2541C
void func_80A25440(void); // func_80A25440
void func_80A25598(void); // func_80A25598
void func_80A25758(void); // func_80A25758
void func_80A257A0(void); // func_80A257A0
void func_80A257B4(void); // func_80A257B4
void func_80A25824(void); // func_80A25824
void func_80A2586C(void); // func_80A2586C
void func_80A25978(void); // func_80A25978
void func_80A25994(void); // func_80A25994
void func_80A25A8C(void); // func_80A25A8C
void func_80A25AA8(void); // func_80A25AA8
void func_80A25BA0(void); // func_80A25BA0
void func_80A25BBC(void); // func_80A25BBC
void func_80A25C5C(void); // func_80A25C5C
void func_80A25C70(void); // func_80A25C70
void func_80A25CF4(void); // func_80A25CF4
void func_80A25D28(void); // func_80A25D28
void func_80A25E3C(void); // func_80A25E3C
void func_80A25E50(void); // func_80A25E50
void func_80A25FA0(void); // func_80A25FA0
void func_80A25FD4(void); // func_80A25FD4
void func_80A260E8(void); // func_80A260E8
void func_80A26144(void); // func_80A26144
void func_80A262BC(void); // func_80A262BC
void func_80A262EC(void); // func_80A262EC
void func_80A26574(void); // func_80A26574
void func_80A265C0(void); // func_80A265C0
void func_80A266C4(void); // func_80A266C4
void func_80A266E0(void); // func_80A266E0
void func_80A26850(void); // func_80A26850
void func_80A26B64(void); // func_80A26B64
void func_80A26B74(void); // func_80A26B74
void func_80A26BF8(void); // func_80A26BF8
void func_80A26DD8(void); // func_80A26DD8
void func_80A27520(void); // func_80A27520
void func_80A27660(void); // func_80A27660
void func_80A2768C(void); // func_80A2768C
void func_80A276F4(void); // func_80A276F4
void func_80A2778C(void); // func_80A2778C
void func_80A27970(void); // func_80A27970
void func_80A27B58(void); // func_80A27B58
void func_80A27DD8(void); // func_80A27DD8
void func_80A27FE8(void); // func_80A27FE8
void func_80A2811C(void); // func_80A2811C
void func_80A281B4(void); // func_80A281B4
void func_80A281DC(void); // func_80A281DC
void func_80A28274(void); // func_80A28274
void func_80A282C8(void); // func_80A282C8
void func_80A28378(void); // func_80A28378
void func_80A283A0(void); // func_80A283A0
void func_80A283F0(void); // func_80A283F0
void func_80A2844C(void); // func_80A2844C
void func_80A284E4(void); // func_80A284E4
void func_80A2855C(void); // func_80A2855C
void func_80A28618(void); // func_80A28618
void func_80A2866C(void); // func_80A2866C
void func_80A286C0(void); // func_80A286C0
void func_80A28708(void); // func_80A28708
void func_80A28760(void); // func_80A28760
void func_80A287E8(void); // func_80A287E8
void func_80A28970(void); // func_80A28970
void func_80A289C8(void); // func_80A289C8
void func_80A28A28(void); // func_80A28A28
void func_80A28A98(void); // func_80A28A98
void func_80A28B98(void); // func_80A28B98
void func_80A28D0C(void); // func_80A28D0C
void func_80A28D80(void); // func_80A28D80
void func_80A28DC0(void); // func_80A28DC0
void func_80A28E40(void); // func_80A28E40
void func_80A28E98(void); // func_80A28E98
void func_80A28ED4(void); // func_80A28ED4
void func_80A28EE8(void); // func_80A28EE8
void func_80A29028(void); // func_80A29028
void func_80A29094(void); // func_80A29094
void func_80A29150(void); // func_80A29150
void func_80A292A8(void); // func_80A292A8
void func_80A293E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A293E4
void func_80A29494(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A29494
void func_80A294D8(void); // func_80A294D8
void func_80A29580(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A29580
void func_80A29628(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A29628
void func_80A2966C(void); // func_80A2966C
void func_80A29A80(void); // func_80A29A80
void func_80A29C18(void); // func_80A29C18
void func_80A2A0D0(void); // func_80A2A0D0
void func_80A2A128(void); // func_80A2A128
void func_80A2A1E0(void); // func_80A2A1E0
void func_80A2A32C(void); // func_80A2A32C
void func_80A2A444(void); // func_80A2A444
void func_80A2A670(void); // func_80A2A670
void func_80A2A688(void); // func_80A2A688
void func_80A2A714(void); // func_80A2A714
void func_80A2A7F8(void); // func_80A2A7F8
void func_80A2AAB8(void); // func_80A2AAB8
void func_80A2ABD0(void); // func_80A2ABD0
void func_80A2AED0(void); // func_80A2AED0
void func_80A2B1A0(void); // func_80A2B1A0
void func_80A2B210(void); // func_80A2B210
void func_80A2B274(void); // func_80A2B274
void func_80A2B308(void); // func_80A2B308
void func_80A2B390(void); // func_80A2B390
void func_80A2BC00(void); // func_80A2BC00
void func_80A2BE28(void); // func_80A2BE28
void func_80A2BE54(void); // func_80A2BE54
void func_80A2BF18(void); // func_80A2BF18
void func_80A2BFC4(void); // func_80A2BFC4
void func_80A2C0F8(void); // func_80A2C0F8
void func_80A2C150(void); // func_80A2C150
void func_80A2C168(void); // func_80A2C168
void func_80A2C1AC(void); // func_80A2C1AC
void func_80A2C208(void); // func_80A2C208
void func_80A2C27C(void); // func_80A2C27C
void func_80A2C2E0(void); // func_80A2C2E0
void func_80A2C33C(void); // func_80A2C33C
void func_80A2C3AC(void); // func_80A2C3AC
void func_80A2C3F0(void); // func_80A2C3F0
void func_80A2C478(void); // func_80A2C478
void func_80A2C48C(void); // func_80A2C48C
void func_80A2C4D0(void); // func_80A2C4D0
void func_80A2C5DC(void); // func_80A2C5DC
void func_80A2C78C(void); // func_80A2C78C
void func_80A2C8A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A2C8A0
void func_80A2C8E8(void); // func_80A2C8E8
void func_80A2CD10(void); // func_80A2CD10
void func_80A2CD1C(void); // func_80A2CD1C
void func_80A2CE54(void); // func_80A2CE54
void func_80A2CF40(void); // func_80A2CF40
void func_80A2CF50(void); // func_80A2CF50
void func_80A2CF7C(void); // func_80A2CF7C
void func_80A2D0FC(void); // func_80A2D0FC
void func_80A2D280(void); // func_80A2D280
void func_80A2D348(void); // func_80A2D348
void func_80A2D3D4(void); // func_80A2D3D4
void func_80A2D400(void); // func_80A2D400
void func_80A2D42C(void); // func_80A2D42C
void func_80A2D4B8(void); // func_80A2D4B8
void func_80A2D778(void); // func_80A2D778
void func_80A2D9CC(void); // func_80A2D9CC
void func_80A2D9DC(void); // func_80A2D9DC
void func_80A2DAF4(void); // func_80A2DAF4
void func_80A2DBE8(void); // func_80A2DBE8
void func_80A2DC14(void); // func_80A2DC14
void func_80A2DCE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A2DCE0
void func_80A2DD34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A2DD34
void func_80A2DE34(void); // func_80A2DE34
void func_80A2DFC4(void); // func_80A2DFC4
void func_80A2E0A0(void); // func_80A2E0A0
void func_80A2E268(void); // func_80A2E268
void func_80A2E7A0(void); // func_80A2E7A0
void func_80A2E828(void); // func_80A2E828
void func_80A2E838(void); // func_80A2E838
void func_80A2E848(void); // func_80A2E848
void func_80A2E8F4(void); // func_80A2E8F4
void func_80A2E960(void); // func_80A2E960
void func_80A2E9FC(void); // func_80A2E9FC
void func_80A2EAAC(void); // func_80A2EAAC
void func_80A2EABC(void); // func_80A2EABC
void func_80A2EACC(void); // func_80A2EACC
void func_80A2EB10(void); // func_80A2EB10
void func_80A2EB2C(void); // func_80A2EB2C
void func_80A2EB44(void); // func_80A2EB44
void func_80A2EB58(void); // func_80A2EB58
void func_80A2EBB0(void); // func_80A2EBB0
void func_80A2EBE8(void); // func_80A2EBE8
void func_80A2EDA0(void); // func_80A2EDA0
void func_80A2EF80(void); // func_80A2EF80
void func_80A2EFAC(void); // func_80A2EFAC
void func_80A2F028(void); // func_80A2F028
void func_80A2F0A8(void); // func_80A2F0A8
void func_80A2F110(void); // func_80A2F110
void func_80A2F140(void); // func_80A2F140
void func_80A2F180(void); // func_80A2F180
void func_80A2F1A4(void); // func_80A2F1A4
void func_80A2F354(void); // func_80A2F354
void func_80A2F418(void); // func_80A2F418
void func_80A2F684(void); // func_80A2F684
void func_80A2F6CC(void); // func_80A2F6CC
void func_80A2F8B4(void); // func_80A2F8B4
void func_80A2F8E0(void); // func_80A2F8E0
void func_80A2F9A0(void); // func_80A2F9A0
void func_80A2FA88(void); // func_80A2FA88
void func_80A2FB60(void); // func_80A2FB60
void func_80A2FBA0(void); // func_80A2FBA0
void func_80A2FD94(void); // func_80A2FD94
void func_80A2FE38(void); // func_80A2FE38
void func_80A30018(void); // func_80A30018
void func_80A30344(void); // func_80A30344
void func_80A30454(void); // func_80A30454
void func_80A304B8(void); // func_80A304B8
void func_80A3072C(void); // func_80A3072C
void func_80A30778(void); // func_80A30778
void func_80A30820(void); // func_80A30820
void func_80A30924(void); // func_80A30924
void func_80A30944(void); // func_80A30944
void func_80A309C8(void); // func_80A309C8
void func_80A30A20(void); // func_80A30A20
void func_80A30A90(void); // func_80A30A90
void func_80A30AE4(void); // func_80A30AE4
void func_80A30BE0(void); // func_80A30BE0
void func_80A30C2C(void); // func_80A30C2C
void func_80A30C68(void); // func_80A30C68
void func_80A30CEC(void); // func_80A30CEC
void func_80A30F98(void); // func_80A30F98
void func_80A311E8(void); // func_80A311E8
void func_80A3148C(void); // func_80A3148C
void func_80A32210(void); // func_80A32210
void func_80A32400(void); // func_80A32400
void func_80A3242C(void); // func_80A3242C
void func_80A324E0(void); // func_80A324E0
void func_80A325E4(void); // func_80A325E4
void func_80A326F0(void); // func_80A326F0
void func_80A32740(void); // func_80A32740
void func_80A32854(void); // func_80A32854
void func_80A3289C(void); // func_80A3289C
void func_80A3295C(void); // func_80A3295C
void func_80A32984(void); // func_80A32984
void func_80A32A40(void); // func_80A32A40
void func_80A32AF8(void); // func_80A32AF8
void func_80A32B20(void); // func_80A32B20
void func_80A32CDC(void); // func_80A32CDC
void func_80A32D28(void); // func_80A32D28
void func_80A32E60(void); // func_80A32E60
void func_80A32EA4(void); // func_80A32EA4
void func_80A32F48(void); // func_80A32F48
void func_80A33098(void); // func_80A33098
void func_80A331C4(void); // func_80A331C4
void func_80A3357C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A3357C
void func_80A335B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A335B4
void func_80A336C0(void); // func_80A336C0
void func_80A33B00(void); // func_80A33B00
void func_80A33BB4(void); // func_80A33BB4
void func_80A342F4(void); // func_80A342F4
void func_80A34438(void); // func_80A34438
void func_80A3446C(void); // func_80A3446C
void func_80A3447C(void); // func_80A3447C
void func_80A34538(void); // func_80A34538
void func_80A34700(void); // func_80A34700
void func_80A349C0(void); // func_80A349C0
void func_80A34A44(void); // func_80A34A44
void func_80A34B28(void); // func_80A34B28
void func_80A3532C(void); // func_80A3532C
void func_80A35378(void); // func_80A35378
void func_80A35388(void); // func_80A35388
void func_80A353AC(void); // func_80A353AC
s32 func_80A35510(ActorObjBell* this, s32 iParm2); // func_80A35510
UNK_TYPE4 func_80A356D8(ActorObjBell* this); // func_80A356D8
UNK_TYPE4 func_80A357A8(ActorObjBell* this, GlobalContext* ctxt); // func_80A357A8
void func_80A358FC(ActorObjBell* this, GlobalContext* ctxt); // func_80A358FC
void func_80A359B4(ActorObjBell* this, GlobalContext* ctxt); // func_80A359B4
void func_80A35B18(ActorObjBell* this, GlobalContext* ctxt); // func_80A35B18
void func_80A35BD4(ActorObjBell* this, GlobalContext* ctxt); // func_80A35BD4
void ObjBell_Init(ActorObjBell* this, GlobalContext* ctxt); // func_80A35C98
void ObjBell_Fini(ActorObjBell* this, GlobalContext* ctxt); // func_80A35D38
void ObjBell_Main(ActorObjBell* this, GlobalContext* ctxt); // func_80A35D90
void ObjBell_Draw(ActorObjBell* this, GlobalContext* ctxt); // func_80A35DDC
void func_80A35FF0(void); // func_80A35FF0
void func_80A3611C(void); // func_80A3611C
void func_80A36148(void); // func_80A36148
void func_80A361B0(void); // func_80A361B0
void func_80A361F4(void); // func_80A361F4
void func_80A36260(void); // func_80A36260
void func_80A362A8(void); // func_80A362A8
void func_80A362F8(void); // func_80A362F8
void func_80A36350(void); // func_80A36350
void func_80A36360(void); // func_80A36360
void func_80A363B4(void); // func_80A363B4
void func_80A36444(void); // func_80A36444
void func_80A36488(void); // func_80A36488
void func_80A364C0(void); // func_80A364C0
void func_80A36504(void); // func_80A36504
void func_80A3657C(void); // func_80A3657C
void func_80A365EC(void); // func_80A365EC
void func_80A368E0(void); // func_80A368E0
void func_80A36A90(void); // func_80A36A90
void func_80A36AF8(void); // func_80A36AF8
void func_80A36B9C(void); // func_80A36B9C
void func_80A36CB0(void); // func_80A36CB0
void func_80A370EC(void); // func_80A370EC
void func_80A37294(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A37294
void func_80A3735C(void); // func_80A3735C
void func_80A37ED0(void); // func_80A37ED0
void func_80A37EE0(void); // func_80A37EE0
void func_80A37EF0(void); // func_80A37EF0
void func_80A3803C(void); // func_80A3803C
void func_80A38190(void); // func_80A38190
void func_80A3822C(void); // func_80A3822C
void func_80A382EC(void); // func_80A382EC
void func_80A382FC(void); // func_80A382FC
void func_80A3830C(void); // func_80A3830C
void func_80A38468(void); // func_80A38468
void func_80A385D4(void); // func_80A385D4
void func_80A3862C(void); // func_80A3862C
void func_80A38648(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A38648
void func_80A3869C(void); // func_80A3869C
void func_80A389A0(void); // func_80A389A0
void func_80A38A68(void); // func_80A38A68
void func_80A38B7C(void); // func_80A38B7C
void func_80A38BF0(void); // func_80A38BF0
void func_80A38C70(void); // func_80A38C70
void func_80A38DF4(void); // func_80A38DF4
void func_80A38E04(void); // func_80A38E04
void func_80A38F10(void); // func_80A38F10
void func_80A38F3C(void); // func_80A38F3C
void func_80A38FB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A38FB4
void func_80A390F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A390F8
void func_80A39204(void); // func_80A39204
void func_80A396B0(void); // func_80A396B0
void func_80A3970C(void); // func_80A3970C
void func_80A39BC0(void); // func_80A39BC0
void func_80A39BD0(void); // func_80A39BD0
void func_80A39C1C(void); // func_80A39C1C
void func_80A39CD4(void); // func_80A39CD4
void func_80A39DC8(void); // func_80A39DC8
void func_80A39F50(void); // func_80A39F50
void func_80A39FBC(void); // func_80A39FBC
void func_80A3A044(void); // func_80A3A044
void func_80A3A0AC(void); // func_80A3A0AC
void func_80A3A0F4(void); // func_80A3A0F4
void func_80A3A210(void); // func_80A3A210
void func_80A3A274(void); // func_80A3A274
void func_80A3A398(void); // func_80A3A398
void func_80A3A484(void); // func_80A3A484
void func_80A3A4AC(void); // func_80A3A4AC
void func_80A3A520(void); // func_80A3A520
void func_80A3A600(void); // func_80A3A600
void func_80A3A610(void); // func_80A3A610
void func_80A3A6F4(void); // func_80A3A6F4
void func_80A3A77C(void); // func_80A3A77C
void func_80A3A7FC(void); // func_80A3A7FC
void func_80A3A8F8(void); // func_80A3A8F8
void func_80A3AA70(void); // func_80A3AA70
void func_80A3AC60(void); // func_80A3AC60
void func_80A3AD38(void); // func_80A3AD38
void func_80A3AD48(void); // func_80A3AD48
void func_80A3AEC8(void); // func_80A3AEC8
void func_80A3B080(void); // func_80A3B080
void func_80A3B1F4(void); // func_80A3B1F4
void func_80A3B220(void); // func_80A3B220
void func_80A3B2CC(void); // func_80A3B2CC
void func_80A3B3E0(void); // func_80A3B3E0
void func_80A3B5E0(void); // func_80A3B5E0
void func_80A3B794(void); // func_80A3B794
void func_80A3B7B8(void); // func_80A3B7B8
void func_80A3B8F8(void); // func_80A3B8F8
void func_80A3B958(void); // func_80A3B958
void func_80A3BC88(void); // func_80A3BC88
void func_80A3BE24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A3BE24
void func_80A3BE60(void); // func_80A3BE60
void func_80A3BF0C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80A3BF0C
void func_80A3C008(void); // func_80A3C008
void func_80A3C17C(void); // func_80A3C17C
void func_80A3C4E0(void); // func_80A3C4E0
void func_80A3C560(void); // func_80A3C560
void func_80A3C658(void); // func_80A3C658
void func_80A3C6A0(void); // func_80A3C6A0
void func_80A3C6CC(void); // func_80A3C6CC
void func_80A3C700(void); // func_80A3C700
void func_80A3C7E8(void); // func_80A3C7E8
void func_80A3C8D8(void); // func_80A3C8D8
void func_80A3CB94(void); // func_80A3CB94
void func_80A3CBF0(void); // func_80A3CBF0
void func_80A3CC30(void); // func_80A3CC30
void func_80A3CC84(void); // func_80A3CC84
void func_80A3CCB4(void); // func_80A3CCB4
void func_80A3CE7C(void); // func_80A3CE7C
void func_80A3CEC4(void); // func_80A3CEC4
void func_80A3CEE0(void); // func_80A3CEE0
void func_80A3CF10(void); // func_80A3CF10
void func_80A3CF4C(void); // func_80A3CF4C
void func_80A3CFAC(void); // func_80A3CFAC
void func_80A3CFE0(void); // func_80A3CFE0
void func_80A3D024(void); // func_80A3D024
void func_80A3D038(void); // func_80A3D038
void func_80A3D0E8(void); // func_80A3D0E8
void func_80A3D0FC(void); // func_80A3D0FC
void func_80A3D184(void); // func_80A3D184
void func_80A3D210(void); // func_80A3D210
void func_80A3D2C0(void); // func_80A3D2C0
void func_80A3D680(void); // func_80A3D680
void func_80A3D940(void); // func_80A3D940
void func_80A3D9C4(void); // func_80A3D9C4
void func_80A3E1C8(void); // func_80A3E1C8
void func_80A3E214(void); // func_80A3E214
void func_80A3E224(void); // func_80A3E224
void func_80A3E248(void); // func_80A3E248
void func_80A3E390(void); // func_80A3E390
void func_80A3E3E4(void); // func_80A3E3E4
void func_80A3E4EC(void); // func_80A3E4EC
void func_80A3E524(void); // func_80A3E524
void func_80A3E7E0(void); // func_80A3E7E0
void func_80A3E80C(void); // func_80A3E80C
void func_80A3E870(void); // func_80A3E870
void func_80A3E884(void); // func_80A3E884
void func_80A3E898(void); // func_80A3E898
void func_80A3E960(void); // func_80A3E960
void func_80A3E97C(void); // func_80A3E97C
void func_80A3E9DC(void); // func_80A3E9DC
void func_80A3EA30(void); // func_80A3EA30
void func_80A3EAC4(void); // func_80A3EAC4
void func_80A3EAF8(void); // func_80A3EAF8
void func_80A3EB8C(void); // func_80A3EB8C
void func_80A3EBFC(void); // func_80A3EBFC
void func_80A3EC30(void); // func_80A3EC30
void func_80A3EC44(void); // func_80A3EC44
void func_80A3ECEC(void); // func_80A3ECEC
void func_80A3ED24(void); // func_80A3ED24
void func_80A3ED94(void); // func_80A3ED94
void func_80A3EFE4(void); // func_80A3EFE4
void func_80A3F080(void); // func_80A3F080
void func_80A3F09C(void); // func_80A3F09C
void func_80A3F0B0(void); // func_80A3F0B0
void func_80A3F114(void); // func_80A3F114
void func_80A3F15C(void); // func_80A3F15C
void func_80A3F2BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A3F2BC
void func_80A3F384(void); // func_80A3F384
void func_80A3F4A4(void); // func_80A3F4A4
void func_80A3F534(void); // func_80A3F534
void func_80A3F5A4(void); // func_80A3F5A4
void func_80A3F62C(void); // func_80A3F62C
void func_80A3F73C(void); // func_80A3F73C
void func_80A3F8D4(void); // func_80A3F8D4
void func_80A3F9A4(void); // func_80A3F9A4
void func_80A3F9E4(void); // func_80A3F9E4
void func_80A3FA58(void); // func_80A3FA58
void func_80A3FBCC(void); // func_80A3FBCC
void func_80A3FBE8(void); // func_80A3FBE8
void func_80A3FDE4(void); // func_80A3FDE4
void func_80A3FE20(void); // func_80A3FE20
void func_80A3FF10(void); // func_80A3FF10
void func_80A3FFD0(void); // func_80A3FFD0
void func_80A40098(void); // func_80A40098
void func_80A40230(void); // func_80A40230
void func_80A40678(void); // func_80A40678
void func_80A40824(void); // func_80A40824
void func_80A4084C(void); // func_80A4084C
void func_80A40908(void); // func_80A40908
void func_80A409D4(void); // func_80A409D4
void func_80A40A6C(void); // func_80A40A6C
void func_80A40A90(void); // func_80A40A90
void func_80A40CF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A40CF0
void func_80A40F34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A40F34
void func_80A4129C(void); // func_80A4129C
void func_80A41D70(ActorEnTest4* this, GlobalContext* ctxt); // func_80A41D70
void func_80A41FA4(ActorEnTest4* this, GlobalContext* ctxt); // func_80A41FA4
void func_80A42198(ActorEnTest4* this); // func_80A42198
void func_80A425E4(ActorEnTest4* this, GlobalContext* ctxt); // func_80A425E4
void EnTest4_Init(ActorEnTest4* this, GlobalContext* ctxt); // func_80A427E8
void EnTest4_Fini(ActorEnTest4* this, GlobalContext* ctxt); // func_80A42AA8
void func_80A42AB8(ActorEnTest4* this, GlobalContext* ctxt); // func_80A42AB8
void func_80A42F20(ActorEnTest4* this, GlobalContext* ctxt); // func_80A42F20
void func_80A430C8(ActorEnTest4* this, GlobalContext* ctxt); // func_80A430C8
void func_80A431C8(ActorEnTest4* this, GlobalContext* ctxt); // func_80A431C8
void func_80A4323C(ActorEnTest4* this, GlobalContext* ctxt); // func_80A4323C
void EnTest4_Main(ActorEnTest4* this, GlobalContext* ctxt); // func_80A43274
void func_80A434E0(void); // func_80A434E0
void func_80A437A0(void); // func_80A437A0
void func_80A437CC(void); // func_80A437CC
void func_80A43810(void); // func_80A43810
void func_80A43870(void); // func_80A43870
void func_80A438D4(void); // func_80A438D4
void func_80A438F8(void); // func_80A438F8
void func_80A4392C(void); // func_80A4392C
void func_80A43CA0(void); // func_80A43CA0
void func_80A43CE8(void); // func_80A43CE8
void func_80A43F60(void); // func_80A43F60
void func_80A44114(void); // func_80A44114
void func_80A44294(void); // func_80A44294
void func_80A4431C(void); // func_80A4431C
void func_80A443D8(void); // func_80A443D8
void func_80A444B8(void); // func_80A444B8
void func_80A44818(void); // func_80A44818
void func_80A44C80(void); // func_80A44C80
void func_80A44DB4(void); // func_80A44DB4
void func_80A44DE8(void); // func_80A44DE8
void func_80A44F40(void); // func_80A44F40
void func_80A450B0(void); // func_80A450B0
void func_80A45130(void); // func_80A45130
void func_80A45140(void); // func_80A45140
void func_80A45164(void); // func_80A45164
void func_80A45360(void); // func_80A45360
void func_80A45568(void); // func_80A45568
void func_80A455C4(void); // func_80A455C4
void func_80A456A0(void); // func_80A456A0
void func_80A45CD8(void); // func_80A45CD8
void func_80A460A4(void); // func_80A460A4
void func_80A46280(void); // func_80A46280
void func_80A462F8(void); // func_80A462F8
void func_80A46414(void); // func_80A46414
void func_80A4668C(void); // func_80A4668C
void func_80A46764(void); // func_80A46764
void func_80A468CC(void); // func_80A468CC
void func_80A46990(void); // func_80A46990
void func_80A46C88(void); // func_80A46C88
void func_80A46CC4(void); // func_80A46CC4
void func_80A46DDC(void); // func_80A46DDC
void func_80A46E24(void); // func_80A46E24
void func_80A47000(void); // func_80A47000
void func_80A470D8(void); // func_80A470D8
void func_80A47298(void); // func_80A47298
void func_80A473B8(void); // func_80A473B8
void func_80A4767C(void); // func_80A4767C
void func_80A476C8(void); // func_80A476C8
void func_80A477E8(void); // func_80A477E8
void func_80A47C6C(void); // func_80A47C6C
void func_80A47FCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A47FCC
void func_80A48138(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A48138
void func_80A483B4(void); // func_80A483B4
void func_80A48FE0(void); // func_80A48FE0
void func_80A490B0(void); // func_80A490B0
void func_80A490E4(void); // func_80A490E4
void func_80A490FC(void); // func_80A490FC
void func_80A492E4(void); // func_80A492E4
void func_80A49308(void); // func_80A49308
void func_80A496A0(void); // func_80A496A0
void func_80A497D4(void); // func_80A497D4
void func_80A4984C(void); // func_80A4984C
void func_80A49A44(void); // func_80A49A44
void func_80A49F38(void); // func_80A49F38
void func_80A49FD8(void); // func_80A49FD8
void func_80A4A11C(void); // func_80A4A11C
void func_80A4A608(void); // func_80A4A608
void func_80A4A698(void); // func_80A4A698
void func_80A4B0C8(void); // func_80A4B0C8
void func_80A4B33C(void); // func_80A4B33C
void func_80A4B804(void); // func_80A4B804
void func_80A4BAB4(void); // func_80A4BAB4
void func_80A4BC74(void); // func_80A4BC74
void func_80A4BDDC(void); // func_80A4BDDC
void func_80A4BF78(void); // func_80A4BF78
void func_80A4C490(void); // func_80A4C490
void func_80A4C54C(void); // func_80A4C54C
void func_80A4C578(void); // func_80A4C578
void func_80A4C5CC(void); // func_80A4C5CC
void func_80A4C78C(void); // func_80A4C78C
void func_80A4C7B0(void); // func_80A4C7B0
void func_80A4C9B0(void); // func_80A4C9B0
void func_80A4C9D4(void); // func_80A4C9D4
void func_80A4C9E4(void); // func_80A4C9E4
void func_80A4C9F4(void); // func_80A4C9F4
void func_80A4CA90(void); // func_80A4CA90
void func_80A4CABC(void); // func_80A4CABC
void func_80A4CB7C(void); // func_80A4CB7C
void func_80A4CC54(void); // func_80A4CC54
void func_80A4CCBC(void); // func_80A4CCBC
void func_80A4CD28(void); // func_80A4CD28
void func_80A4CD34(void); // func_80A4CD34
void func_80A4CE28(void); // func_80A4CE28
void func_80A4D174(void); // func_80A4D174
void func_80A4D1CC(void); // func_80A4D1CC
void func_80A4D1EC(void); // func_80A4D1EC
void func_80A4D370(void); // func_80A4D370
void func_80A4D39C(void); // func_80A4D39C
void func_80A4D6A4(void); // func_80A4D6A4
void func_80A4D9F0(void); // func_80A4D9F0
void func_80A4DB54(void); // func_80A4DB54
void func_80A4DB88(void); // func_80A4DB88
void func_80A4DBD8(void); // func_80A4DBD8
void func_80A4DC48(void); // func_80A4DC48
void func_80A4DCCC(void); // func_80A4DCCC
void func_80A4DCDC(void); // func_80A4DCDC
void func_80A4DD00(void); // func_80A4DD00
void func_80A4DED0(void); // func_80A4DED0
void func_80A4E0A0(void); // func_80A4E0A0
void func_80A4E0CC(void); // func_80A4E0CC
void func_80A4E100(void); // func_80A4E100
void func_80A4E190(void); // func_80A4E190
void func_80A4E1F0(void); // func_80A4E1F0
void func_80A4E22C(void); // func_80A4E22C
void func_80A4E2B8(void); // func_80A4E2B8
void func_80A4E2E8(void); // func_80A4E2E8
void func_80A4E58C(void); // func_80A4E58C
void func_80A4E60C(void); // func_80A4E60C
void func_80A4E67C(void); // func_80A4E67C
void func_80A4E72C(void); // func_80A4E72C
void func_80A4E84C(void); // func_80A4E84C
void func_80A4EBBC(void); // func_80A4EBBC
void func_80A4EC14(void); // func_80A4EC14
void func_80A4EDF0(void); // func_80A4EDF0
void func_80A4EE48(void); // func_80A4EE48
void func_80A4EEF4(void); // func_80A4EEF4
void func_80A4EF74(void); // func_80A4EF74
void func_80A4F16C(void); // func_80A4F16C
void func_80A4F190(void); // func_80A4F190
void func_80A4F4C8(void); // func_80A4F4C8
void func_80A4FA40(void); // func_80A4FA40
void func_80A4FB00(void); // func_80A4FB00
void func_80A4FB10(void); // func_80A4FB10
void func_80A4FB68(void); // func_80A4FB68
void func_80A4FCCC(void); // func_80A4FCCC
void func_80A4FCF0(void); // func_80A4FCF0
void func_80A4FDD0(void); // func_80A4FDD0
void func_80A4FEBC(void); // func_80A4FEBC
void func_80A4FFE8(void); // func_80A4FFE8
void func_80A500F8(void); // func_80A500F8
void func_80A502A0(void); // func_80A502A0
void func_80A5034C(void); // func_80A5034C
void func_80A50380(void); // func_80A50380
void func_80A50510(void); // func_80A50510
void func_80A5063C(void); // func_80A5063C
void func_80A50768(void); // func_80A50768
void func_80A507C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80A507C0
void func_80A5086C(void); // func_80A5086C
void func_80A50950(void); // func_80A50950
void func_80A50D40(void); // func_80A50D40
void func_80A50DF8(void); // func_80A50DF8
UNK_TYPE4 func_80A50E40(s32 param_1, UNK_TYPE4 param_2); // func_80A50E40
void func_80A50EC0(void); // func_80A50EC0
void func_80A50F38(void); // func_80A50F38
void func_80A50F9C(void); // func_80A50F9C
void func_80A50FAC(s32 param_1, UNK_TYPE4 param_2); // func_80A50FAC
void func_80A510D0(void); // func_80A510D0
void func_80A510E0(void); // func_80A510E0
void func_80A51168(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A51168
void func_80A511B4(void); // func_80A511B4
void func_80A514F0(void); // func_80A514F0
void func_80A515C4(void); // func_80A515C4
void func_80A51648(void); // func_80A51648
void func_80A51890(void); // func_80A51890
void func_80A518DC(void); // func_80A518DC
void func_80A518EC(void); // func_80A518EC
void func_80A519A8(void); // func_80A519A8
void func_80A519D4(void); // func_80A519D4
UNK_TYPE4 func_80A51A78(UNK_TYPE4 param_1, s32 param_2, UNK_PTR param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, s32 param_6); // func_80A51A78
void func_80A51AA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A51AA4
void func_80A51CB8(void); // func_80A51CB8
void func_80A51D78(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A51D78
void func_80A51DA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A51DA4
void func_80A51FC0(void); // func_80A51FC0
void func_80A52018(void); // func_80A52018
void func_80A52074(void); // func_80A52074
void func_80A52134(void); // func_80A52134
void func_80A52530(void); // func_80A52530
void func_80A5257C(void); // func_80A5257C
void func_80A52604(void); // func_80A52604
UNK_TYPE4 func_80A52648(s32 param_1, s32 param_2); // func_80A52648
void func_80A526F8(void); // func_80A526F8
void func_80A52944(void); // func_80A52944
void func_80A52A78(void); // func_80A52A78
void func_80A52B68(void); // func_80A52B68
void func_80A52C6C(void); // func_80A52C6C
void func_80A52CF8(void); // func_80A52CF8
void func_80A52D44(void); // func_80A52D44
void func_80A52DC8(s32 param_1, s32 param_2); // func_80A52DC8
void func_80A52FB8(void); // func_80A52FB8
void func_80A53038(void); // func_80A53038
void func_80A5313C(void); // func_80A5313C
void func_80A53258(void); // func_80A53258
void func_80A53284(void); // func_80A53284
void func_80A533A4(void); // func_80A533A4
void func_80A537D0(void); // func_80A537D0
void func_80A53868(void); // func_80A53868
void func_80A5389C(void); // func_80A5389C
void func_80A538E0(void); // func_80A538E0
void func_80A53994(void); // func_80A53994
void func_80A539B8(void); // func_80A539B8
void func_80A53ABC(void); // func_80A53ABC
void func_80A53BE0(void); // func_80A53BE0
void func_80A53E60(void); // func_80A53E60
void func_80A541F4(void); // func_80A541F4
void func_80A54600(void); // func_80A54600
void func_80A54980(void); // func_80A54980
void func_80A54A0C(void); // func_80A54A0C
void func_80A54AC0(void); // func_80A54AC0
void func_80A54BC4(void); // func_80A54BC4
void func_80A54BF0(void); // func_80A54BF0
void func_80A54C04(void); // func_80A54C04
void func_80A54CD8(void); // func_80A54CD8
void func_80A54CEC(void); // func_80A54CEC
void func_80A54E10(void); // func_80A54E10
void func_80A55064(void); // func_80A55064
void func_80A55310(void); // func_80A55310
void func_80A55564(void); // func_80A55564
void func_80A557FC(void); // func_80A557FC
void func_80A55820(void); // func_80A55820
void func_80A55B34(void); // func_80A55B34
void func_80A560C0(void); // func_80A560C0
void func_80A560D0(void); // func_80A560D0
void func_80A560E0(void); // func_80A560E0
void func_80A560F0(void); // func_80A560F0
void func_80A56150(void); // func_80A56150
void func_80A56370(void); // func_80A56370
void func_80A563CC(void); // func_80A563CC
void func_80A56444(void); // func_80A56444
void func_80A5665C(void); // func_80A5665C
void func_80A566E0(void); // func_80A566E0
void func_80A56994(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A56994
void func_80A56AFC(void); // func_80A56AFC
void func_80A56EB8(void); // func_80A56EB8
void func_80A56F68(void); // func_80A56F68
void func_80A57010(void); // func_80A57010
void func_80A57118(void); // func_80A57118
void func_80A57180(void); // func_80A57180
void func_80A5723C(void); // func_80A5723C
void func_80A57330(void); // func_80A57330
void func_80A57384(void); // func_80A57384
void func_80A57488(void); // func_80A57488
void func_80A574E8(void); // func_80A574E8
void func_80A57570(void); // func_80A57570
void func_80A575F4(void); // func_80A575F4
void func_80A5764C(void); // func_80A5764C
void func_80A57918(void); // func_80A57918
void func_80A57984(void); // func_80A57984
void func_80A57A08(void); // func_80A57A08
void func_80A57A9C(void); // func_80A57A9C
void func_80A57AE0(void); // func_80A57AE0
void func_80A57F10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A57F10
void func_80A57F4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A57F4C
void func_80A58354(void); // func_80A58354
void func_80A587A0(void); // func_80A587A0
void func_80A58908(void); // func_80A58908
void func_80A58A94(void); // func_80A58A94
void func_80A58CE8(void); // func_80A58CE8
void func_80A58CF8(void); // func_80A58CF8
void func_80A59420(void); // func_80A59420
void func_80A599E8(void); // func_80A599E8
void func_80A59C04(void); // func_80A59C04
void func_80A5A184(void); // func_80A5A184
void func_80A5A534(void); // func_80A5A534
void func_80A5A6B8(void); // func_80A5A6B8
void func_80A5B160(void); // func_80A5B160
void func_80A5B334(void); // func_80A5B334
void func_80A5B3BC(void); // func_80A5B3BC
void func_80A5B490(void); // func_80A5B490
void func_80A5B508(void); // func_80A5B508
void func_80A5B954(void); // func_80A5B954
void func_80A5BA58(void); // func_80A5BA58
void func_80A5BAFC(void); // func_80A5BAFC
void func_80A5BB40(void); // func_80A5BB40
void func_80A5BD14(void); // func_80A5BD14
void func_80A5BD94(void); // func_80A5BD94
void func_80A5BDB0(void); // func_80A5BDB0
void func_80A5BF38(void); // func_80A5BF38
void func_80A5BF60(void); // func_80A5BF60
void func_80A5BF84(void); // func_80A5BF84
void func_80A5BFD8(void); // func_80A5BFD8
void func_80A5C074(void); // func_80A5C074
void func_80A5C0B8(void); // func_80A5C0B8
void func_80A5C104(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_80A5C104
void func_80A5C2FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A5C2FC
void func_80A5C410(void); // func_80A5C410
void func_80A5C70C(void); // func_80A5C70C
void func_80A5C718(void); // func_80A5C718
void func_80A5C7F0(void); // func_80A5C7F0
void func_80A5C918(void); // func_80A5C918
void func_80A5CAD4(void); // func_80A5CAD4
void func_80A5CAF4(void); // func_80A5CAF4
void func_80A5CB74(void); // func_80A5CB74
void func_80A5CCD4(void); // func_80A5CCD4
void func_80A5CD0C(void); // func_80A5CD0C
void func_80A5CF44(void); // func_80A5CF44
void func_80A5D178(void); // func_80A5D178
void func_80A5D3EC(void); // func_80A5D3EC
void func_80A5D5A0(void); // func_80A5D5A0
void func_80A5D5E0(void); // func_80A5D5E0
void func_80A5D5F4(void); // func_80A5D5F4
void func_80A5D618(void); // func_80A5D618
void func_80A5D62C(void); // func_80A5D62C
void func_80A5D6B0(void); // func_80A5D6B0
void func_80A5D6C4(void); // func_80A5D6C4
void func_80A5D754(void); // func_80A5D754
void func_80A5D794(void); // func_80A5D794
void func_80A5D7A4(void); // func_80A5D7A4
void func_80A5D7C4(void); // func_80A5D7C4
void func_80A5D964(void); // func_80A5D964
void func_80A5D9C8(void); // func_80A5D9C8
void func_80A5DC70(void); // func_80A5DC70
void func_80A5DC98(void); // func_80A5DC98
void func_80A5DE18(void); // func_80A5DE18
void func_80A5DEB4(void); // func_80A5DEB4
void func_80A5E1D8(void); // func_80A5E1D8
void func_80A5E210(void); // func_80A5E210
void func_80A5E418(void); // func_80A5E418
void func_80A5E4BC(void); // func_80A5E4BC
void func_80A5E604(void); // func_80A5E604
void func_80A5E6A4(void); // func_80A5E6A4
void func_80A5E6F0(void); // func_80A5E6F0
void func_80A5E80C(void); // func_80A5E80C
void func_80A5E8C0(void); // func_80A5E8C0
void func_80A5E9B4(void); // func_80A5E9B4
void func_80A5EA48(void); // func_80A5EA48
void func_80A60B20(void); // func_80A60B20
void func_80A60BF8(void); // func_80A60BF8
void func_80A60C24(void); // func_80A60C24
void func_80A60C94(void); // func_80A60C94
void func_80A60CDC(void); // func_80A60CDC
void func_80A60D10(void); // func_80A60D10
void func_80A60DA0(void); // func_80A60DA0
void func_80A60E08(void); // func_80A60E08
void func_80A60F68(void); // func_80A60F68
void func_80A61040(void); // func_80A61040
void func_80A612B0(void); // func_80A612B0
void func_80A612C0(void); // func_80A612C0
void func_80A61334(void); // func_80A61334
void func_80A613C8(void); // func_80A613C8
void func_80A61470(void); // func_80A61470
void func_80A614C4(void); // func_80A614C4
void func_80A61810(void); // func_80A61810
void func_80A619EC(void); // func_80A619EC
void func_80A61A18(void); // func_80A61A18
void func_80A61A44(void); // func_80A61A44
void func_80A61A6C(void); // func_80A61A6C
void func_80A61ADC(void); // func_80A61ADC
void func_80A61B5C(void); // func_80A61B5C
void func_80A61C9C(void); // func_80A61C9C
void func_80A61CE4(void); // func_80A61CE4
void func_80A61DF8(void); // func_80A61DF8
void func_80A61E5C(void); // func_80A61E5C
void func_80A62128(void); // func_80A62128
void func_80A621C4(void); // func_80A621C4
void func_80A62260(void); // func_80A62260
void func_80A622A0(void); // func_80A622A0
void func_80A623CC(void); // func_80A623CC
void func_80A624DC(void); // func_80A624DC
void func_80A62818(void); // func_80A62818
void func_80A62830(void); // func_80A62830
void func_80A629C4(void); // func_80A629C4
void func_80A62AC4(void); // func_80A62AC4
void func_80A62B30(void); // func_80A62B30
void func_80A62B78(void); // func_80A62B78
void func_80A62CF0(void); // func_80A62CF0
void func_80A62DCC(void); // func_80A62DCC
void func_80A62ED0(void); // func_80A62ED0
void func_80A62FAC(void); // func_80A62FAC
void func_80A63158(void); // func_80A63158
void func_80A634B4(void); // func_80A634B4
void func_80A634C8(void); // func_80A634C8
void func_80A635DC(void); // func_80A635DC
void func_80A635F0(void); // func_80A635F0
void func_80A636AC(void); // func_80A636AC
void func_80A637FC(void); // func_80A637FC
void func_80A63884(void); // func_80A63884
void func_80A63914(void); // func_80A63914
void func_80A63A10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A63A10
void func_80A63B94(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A63B94
void func_80A63BEC(void); // func_80A63BEC
void func_80A644A0(void); // func_80A644A0
void func_80A64544(void); // func_80A64544
void func_80A64554(void); // func_80A64554
void func_80A645A4(void); // func_80A645A4
void func_80A646F4(void); // func_80A646F4
void func_80A64DC4(void); // func_80A64DC4
void func_80A65364(void); // func_80A65364
void func_80A65490(void); // func_80A65490
void func_80A654A4(void); // func_80A654A4
void func_80A6557C(void); // func_80A6557C
void func_80A65590(void); // func_80A65590
void func_80A656C4(void); // func_80A656C4
void func_80A656D8(void); // func_80A656D8
void func_80A65800(void); // func_80A65800
void func_80A65844(void); // func_80A65844
void func_80A65988(void); // func_80A65988
void func_80A65A5C(void); // func_80A65A5C
void func_80A65ADC(void); // func_80A65ADC
void func_80A65B44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A65B44
void func_80A65C18(void); // func_80A65C18
void func_80A65C30(void); // func_80A65C30
void func_80A66180(void); // func_80A66180
void func_80A661DC(void); // func_80A661DC
void func_80A66208(void); // func_80A66208
void func_80A66278(void); // func_80A66278
void func_80A66384(void); // func_80A66384
void func_80A663E8(void); // func_80A663E8
void func_80A663F8(void); // func_80A663F8
void func_80A66468(void); // func_80A66468
void func_80A66570(void); // func_80A66570
void func_80A665AC(void); // func_80A665AC
void func_80A665EC(void); // func_80A665EC
void func_80A667F0(void); // func_80A667F0
void func_80A66930(void); // func_80A66930
void func_80A66C4C(void); // func_80A66C4C
void func_80A66E30(void); // func_80A66E30
void func_80A66F94(void); // func_80A66F94
void func_80A67174(void); // func_80A67174
void func_80A671A8(void); // func_80A671A8
void func_80A671BC(void); // func_80A671BC
void func_80A671CC(void); // func_80A671CC
void func_80A671E0(void); // func_80A671E0
void func_80A6743C(void); // func_80A6743C
void func_80A67450(void); // func_80A67450
void func_80A674A8(void); // func_80A674A8
void func_80A674C4(void); // func_80A674C4
void func_80A674FC(void); // func_80A674FC
void func_80A675C4(void); // func_80A675C4
void func_80A678B0(void); // func_80A678B0
void func_80A67A08(void); // func_80A67A08
void func_80A67A34(void); // func_80A67A34
void func_80A67AA8(void); // func_80A67AA8
void func_80A67C48(void); // func_80A67C48
void func_80A67D0C(void); // func_80A67D0C
void func_80A67F30(void); // func_80A67F30
void func_80A67FC4(void); // func_80A67FC4
void func_80A68080(void); // func_80A68080
void func_80A680FC(void); // func_80A680FC
void func_80A681C4(void); // func_80A681C4
void func_80A68540(void); // func_80A68540
void func_80A687A0(void); // func_80A687A0
void func_80A68808(void); // func_80A68808
void func_80A68860(void); // func_80A68860
void func_80A68910(void); // func_80A68910
void func_80A68A78(void); // func_80A68A78
void func_80A68B3C(void); // func_80A68B3C
void func_80A68B6C(void); // func_80A68B6C
void func_80A68BA0(void); // func_80A68BA0
void func_80A68BC8(void); // func_80A68BC8
void func_80A68C5C(void); // func_80A68C5C
void func_80A68CE4(void); // func_80A68CE4
void func_80A68DD4(void); // func_80A68DD4
void func_80A68ED8(void); // func_80A68ED8
void func_80A68F24(void); // func_80A68F24
void func_80A68F9C(void); // func_80A68F9C
void func_80A690C4(void); // func_80A690C4
void func_80A691EC(void); // func_80A691EC
void func_80A69388(void); // func_80A69388
void func_80A69424(void); // func_80A69424
void func_80A69468(void); // func_80A69468
void func_80A6958C(void); // func_80A6958C
void func_80A6969C(void); // func_80A6969C
void func_80A697C4(void); // func_80A697C4
void func_80A699E4(void); // func_80A699E4
void func_80A69AA8(void); // func_80A69AA8
void func_80A69ADC(void); // func_80A69ADC
void func_80A69CE0(void); // func_80A69CE0
void func_80A69D3C(void); // func_80A69D3C
void func_80A69EE4(void); // func_80A69EE4
void func_80A69F5C(void); // func_80A69F5C
void func_80A6A024(void); // func_80A6A024
void func_80A6A058(void); // func_80A6A058
void func_80A6A094(void); // func_80A6A094
void func_80A6A0D8(void); // func_80A6A0D8
void func_80A6A0F0(void); // func_80A6A0F0
void func_80A6A2C8(void); // func_80A6A2C8
void func_80A6A300(void); // func_80A6A300
void func_80A6A36C(void); // func_80A6A36C
void func_80A6A508(void); // func_80A6A508
void func_80A6A5C0(void); // func_80A6A5C0
void func_80A6A794(void); // func_80A6A794
void func_80A6A824(void); // func_80A6A824
void func_80A6A984(void); // func_80A6A984
void func_80A6A9E4(void); // func_80A6A9E4
void func_80A6AAA4(void); // func_80A6AAA4
void func_80A6AB08(void); // func_80A6AB08
void func_80A6AE14(void); // func_80A6AE14
void func_80A6AE7C(void); // func_80A6AE7C
void func_80A6B078(void); // func_80A6B078
void func_80A6B0D8(void); // func_80A6B0D8
void func_80A6B3F8(void); // func_80A6B3F8
void func_80A6B8D0(void); // func_80A6B8D0
void func_80A6BF90(void); // func_80A6BF90
void func_80A6C1DC(void); // func_80A6C1DC
void func_80A6C22C(void); // func_80A6C22C
void func_80A6C39C(void); // func_80A6C39C
void func_80A6C3AC(void); // func_80A6C3AC
void func_80A6C3FC(void); // func_80A6C3FC
void func_80A6C7C0(void); // func_80A6C7C0
void func_80A6C9A8(void); // func_80A6C9A8
void func_80A6CA9C(void); // func_80A6CA9C
void func_80A6CB74(void); // func_80A6CB74
void func_80A6CD38(void); // func_80A6CD38
void func_80A6CD74(void); // func_80A6CD74
void func_80A6CECC(void); // func_80A6CECC
void func_80A6CF60(void); // func_80A6CF60
void func_80A6CF70(void); // func_80A6CF70
void func_80A6D0DC(void); // func_80A6D0DC
void func_80A6D100(void); // func_80A6D100
void func_80A6D220(void); // func_80A6D220
void func_80A6D444(void); // func_80A6D444
void func_80A6D504(void); // func_80A6D504
void func_80A6D698(void); // func_80A6D698
void func_80A6D75C(void); // func_80A6D75C
void func_80A6D88C(void); // func_80A6D88C
void func_80A6D98C(void); // func_80A6D98C
void func_80A6DA7C(void); // func_80A6DA7C
void func_80A6DC20(void); // func_80A6DC20
void func_80A6DC40(void); // func_80A6DC40
void func_80A6DD3C(void); // func_80A6DD3C
void func_80A6E07C(void); // func_80A6E07C
void func_80A6E214(void); // func_80A6E214
void func_80A6E37C(void); // func_80A6E37C
void func_80A6F0A0(void); // func_80A6F0A0
void func_80A6F1EC(void); // func_80A6F1EC
void func_80A6F22C(void); // func_80A6F22C
void func_80A6F270(void); // func_80A6F270
void func_80A6F2C8(void); // func_80A6F2C8
void func_80A6F3B4(void); // func_80A6F3B4
void func_80A6F5E4(void); // func_80A6F5E4
void func_80A6F9C8(void); // func_80A6F9C8
void func_80A6F9DC(void); // func_80A6F9DC
void func_80A6FBA0(void); // func_80A6FBA0
void func_80A6FBFC(void); // func_80A6FBFC
void func_80A6FE1C(void); // func_80A6FE1C
void func_80A6FE30(void); // func_80A6FE30
void func_80A6FED8(void); // func_80A6FED8
void func_80A6FEEC(void); // func_80A6FEEC
void func_80A6FFAC(void); // func_80A6FFAC
void func_80A70084(void); // func_80A70084
void func_80A70134(void); // func_80A70134
void func_80A701E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A701E0
void func_80A702B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A702B0
void func_80A702F0(void); // func_80A702F0
void func_80A706F0(void); // func_80A706F0
void func_80A7090C(void); // func_80A7090C
void func_80A70970(void); // func_80A70970
void func_80A7099C(void); // func_80A7099C
void func_80A709E4(void); // func_80A709E4
void func_80A70A08(void); // func_80A70A08
void func_80A70A84(void); // func_80A70A84
void func_80A70A9C(void); // func_80A70A9C
void func_80A70AAC(void); // func_80A70AAC
void func_80A70B60(void); // func_80A70B60
void func_80A70C04(void); // func_80A70C04
void func_80A70D74(void); // func_80A70D74
void func_80A70DA8(void); // func_80A70DA8
void func_80A70E2C(void); // func_80A70E2C
void func_80A70E70(void); // func_80A70E70
void func_80A70F14(void); // func_80A70F14
void func_80A70F2C(void); // func_80A70F2C
void func_80A70FF4(void); // func_80A70FF4
void func_80A71040(void); // func_80A71040
void func_80A71050(void); // func_80A71050
void func_80A711D0(void); // func_80A711D0
void func_80A71424(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_80A71424
void func_80A714B4(void); // func_80A714B4
void func_80A7153C(void); // func_80A7153C
void func_80A715DC(void); // func_80A715DC
void func_80A71788(void); // func_80A71788
void func_80A717F4(void); // func_80A717F4
void func_80A71ABC(void); // func_80A71ABC
void func_80A71B04(void); // func_80A71B04
void func_80A71B58(void); // func_80A71B58
void func_80A71B68(void); // func_80A71B68
void func_80A71C3C(void); // func_80A71C3C
void func_80A71E54(void); // func_80A71E54
void func_80A71F18(void); // func_80A71F18
void func_80A72438(void); // func_80A72438
void func_80A724B8(void); // func_80A724B8
void func_80A7256C(void); // func_80A7256C
void func_80A72598(void); // func_80A72598
void func_80A725E0(void); // func_80A725E0
void func_80A725F8(void); // func_80A725F8
void func_80A72AE4(void); // func_80A72AE4
void func_80A72B3C(void); // func_80A72B3C
void func_80A72B84(void); // func_80A72B84
void func_80A72BA4(void); // func_80A72BA4
void func_80A72C04(void); // func_80A72C04
void func_80A72CF8(void); // func_80A72CF8
void func_80A72D8C(void); // func_80A72D8C
void func_80A72FAC(void); // func_80A72FAC
void func_80A730A0(void); // func_80A730A0
void func_80A73244(void); // func_80A73244
void func_80A732C8(void); // func_80A732C8
void func_80A73408(void); // func_80A73408
void func_80A73508(void); // func_80A73508
void func_80A735C8(void); // func_80A735C8
void func_80A7361C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A7361C
void func_80A73654(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A73654
void func_80A73FA0(void); // func_80A73FA0
void func_80A7422C(void); // func_80A7422C
void func_80A7429C(void); // func_80A7429C
void func_80A7436C(void); // func_80A7436C
void func_80A74510(void); // func_80A74510
void func_80A745C4(void); // func_80A745C4
void func_80A745FC(void); // func_80A745FC
void func_80A74888(void); // func_80A74888
void func_80A748E8(void); // func_80A748E8
void func_80A74DEC(void); // func_80A74DEC
void func_80A74E90(void); // func_80A74E90
void func_80A751B4(void); // func_80A751B4
void func_80A75310(void); // func_80A75310
void func_80A755D8(void); // func_80A755D8
void func_80A756A8(void); // func_80A756A8
void func_80A758E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A758E8
void func_80A75950(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A75950
void func_80A759D8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A759D8
void func_80A75A40(void); // func_80A75A40
void func_80A75DC0(void); // func_80A75DC0
void func_80A75F08(void); // func_80A75F08
void func_80A75F18(void); // func_80A75F18
void func_80A75FA4(void); // func_80A75FA4
void func_80A76070(void); // func_80A76070
void func_80A762C0(void); // func_80A762C0
void func_80A76388(void); // func_80A76388
void func_80A763E8(void); // func_80A763E8
void func_80A76604(void); // func_80A76604
void func_80A76634(void); // func_80A76634
void func_80A76748(void); // func_80A76748
void func_80A767A8(void); // func_80A767A8
void func_80A76A1C(void); // func_80A76A1C
void func_80A76B14(void); // func_80A76B14
void func_80A76D48(void); // func_80A76D48
void func_80A76F70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A76F70
void func_80A76FCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A76FCC
void func_80A77040(void); // func_80A77040
void func_80A773C0(void); // func_80A773C0
void func_80A77664(void); // func_80A77664
void func_80A776E0(void); // func_80A776E0
void func_80A77790(void); // func_80A77790
void func_80A77880(void); // func_80A77880
void func_80A778D8(void); // func_80A778D8
void func_80A778F8(void); // func_80A778F8
void func_80A78588(void); // func_80A78588
void func_80A785E4(void); // func_80A785E4
void func_80A787FC(void); // func_80A787FC
void func_80A78868(void); // func_80A78868
void func_80A78A70(void); // func_80A78A70
void func_80A78ACC(void); // func_80A78ACC
void func_80A78B04(void); // func_80A78B04
void func_80A78B70(void); // func_80A78B70
void func_80A78C08(void); // func_80A78C08
void func_80A78C7C(void); // func_80A78C7C
void func_80A78E8C(void); // func_80A78E8C
void func_80A78F04(void); // func_80A78F04
void func_80A78F80(void); // func_80A78F80
void func_80A79038(void); // func_80A79038
void func_80A790E4(void); // func_80A790E4
void func_80A7919C(void); // func_80A7919C
void func_80A79300(void); // func_80A79300
void func_80A79364(void); // func_80A79364
void func_80A79450(void); // func_80A79450
void func_80A794C8(void); // func_80A794C8
void func_80A79524(void); // func_80A79524
void func_80A79600(void); // func_80A79600
void func_80A796BC(void); // func_80A796BC
void func_80A7980C(void); // func_80A7980C
void func_80A79864(void); // func_80A79864
void func_80A798C8(void); // func_80A798C8
void func_80A7998C(void); // func_80A7998C
void func_80A79A84(void); // func_80A79A84
void func_80A79B60(void); // func_80A79B60
void func_80A79BA0(void); // func_80A79BA0
void func_80A7A0D0(void); // func_80A7A0D0
void func_80A7A124(void); // func_80A7A124
void func_80A7A2EC(void); // func_80A7A2EC
void func_80A7A360(void); // func_80A7A360
void func_80A7A61C(void); // func_80A7A61C
void func_80A7AA48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A7AA48
void func_80A7AA9C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A7AA9C
void func_80A7AFA8(void); // func_80A7AFA8
void func_80A7BC70(void); // func_80A7BC70
void func_80A7BD80(void); // func_80A7BD80
void func_80A7BDC8(void); // func_80A7BDC8
void func_80A7BE8C(void); // func_80A7BE8C
void func_80A7BF08(void); // func_80A7BF08
void func_80A7C168(void); // func_80A7C168
void func_80A7C1F0(void); // func_80A7C1F0
void func_80A7C308(void); // func_80A7C308
void func_80A7C5EC(void); // func_80A7C5EC
void func_80A7C690(void); // func_80A7C690
void func_80A7C718(void); // func_80A7C718
void func_80A7C990(void); // func_80A7C990
void func_80A7CA18(void); // func_80A7CA18
void func_80A7CBC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80A7CBC4
void func_80A7CD08(void); // func_80A7CD08
void func_80A7CD60(void); // func_80A7CD60
void func_80A7D0F0(void); // func_80A7D0F0
void func_80A7D140(void); // func_80A7D140
void func_80A7D168(void); // func_80A7D168
void func_80A7D1E4(void); // func_80A7D1E4
void func_80A7D240(void); // func_80A7D240
void func_80A7D27C(void); // func_80A7D27C
void func_80A7D2C4(void); // func_80A7D2C4
void func_80A7D710(void); // func_80A7D710
void func_80A7D780(void); // func_80A7D780
void func_80A7DAAC(void); // func_80A7DAAC
void func_80A7DAF0(void); // func_80A7DAF0
void func_80A7E2E8(void); // func_80A7E2E8
void func_80A7E344(void); // func_80A7E344
void func_80A7E478(void); // func_80A7E478
void func_80A7E4B4(void); // func_80A7E4B4
void func_80A7E7EC(void); // func_80A7E7EC
void func_80A7E820(void); // func_80A7E820
void func_80A7E924(void); // func_80A7E924
void func_80A7E970(void); // func_80A7E970
void func_80A7E9D0(void); // func_80A7E9D0
void func_80A7EA28(void); // func_80A7EA28
void func_80A7EA88(void); // func_80A7EA88
void func_80A7EAD8(void); // func_80A7EAD8
void func_80A7EB14(void); // func_80A7EB14
void func_80A7EB54(void); // func_80A7EB54
void func_80A7EB90(void); // func_80A7EB90
void func_80A7EBDC(void); // func_80A7EBDC
void func_80A7EC84(void); // func_80A7EC84
void func_80A7ED14(void); // func_80A7ED14
void func_80A7EFB8(void); // func_80A7EFB8
void func_80A7F354(void); // func_80A7F354
void func_80A7F8E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A7F8E8
void func_80A7FAFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A7FAFC
void func_80A7FFB8(void); // func_80A7FFB8
void func_80A80508(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80A80508
void func_80A80750(void); // func_80A80750
void func_80A80904(void); // func_80A80904
void func_80A811D0(void); // func_80A811D0
void func_80A8120C(void); // func_80A8120C
void func_80A81288(void); // func_80A81288
void func_80A8131C(void); // func_80A8131C
void func_80A81384(void); // func_80A81384
void func_80A8140C(void); // func_80A8140C
void func_80A8146C(void); // func_80A8146C
void func_80A81544(void); // func_80A81544
void func_80A81640(void); // func_80A81640
void func_80A8164C(void); // func_80A8164C
void func_80A81684(void); // func_80A81684
void func_80A81714(void); // func_80A81714
void func_80A81818(void); // func_80A81818
void func_80A81868(void); // func_80A81868
void func_80A819A4(void); // func_80A819A4
void func_80A81A00(void); // func_80A81A00
void func_80A81AA4(void); // func_80A81AA4
void func_80A81B14(void); // func_80A81B14
void func_80A81B7C(void); // func_80A81B7C
void func_80A81D70(void); // func_80A81D70
void func_80A81DEC(void); // func_80A81DEC
void func_80A81E7C(void); // func_80A81E7C
void func_80A81FFC(void); // func_80A81FFC
void func_80A828A8(void); // func_80A828A8
void func_80A82C28(void); // func_80A82C28
void func_80A82C5C(void); // func_80A82C5C
void func_80A82F58(void); // func_80A82F58
void func_80A82F84(void); // func_80A82F84
void func_80A82F98(void); // func_80A82F98
void func_80A82FA8(void); // func_80A82FA8
void func_80A82FC8(void); // func_80A82FC8
void func_80A83214(void); // func_80A83214
void func_80A83258(void); // func_80A83258
void func_80A832BC(void); // func_80A832BC
void func_80A832D0(void); // func_80A832D0
void func_80A83A74(void); // func_80A83A74
void func_80A83A88(void); // func_80A83A88
void func_80A83B14(void); // func_80A83B14
void func_80A83B28(void); // func_80A83B28
void func_80A83CEC(void); // func_80A83CEC
void func_80A83D00(void); // func_80A83D00
void func_80A83D8C(void); // func_80A83D8C
void func_80A83E7C(void); // func_80A83E7C
void func_80A83EA0(void); // func_80A83EA0
void func_80A83FBC(void); // func_80A83FBC
void func_80A84088(void); // func_80A84088
void func_80A84338(void); // func_80A84338
void func_80A84CD0(void); // func_80A84CD0
void func_80A84CF8(void); // func_80A84CF8
void func_80A84D68(void); // func_80A84D68
void func_80A84E68(void); // func_80A84E68
void func_80A84EAC(void); // func_80A84EAC
void func_80A84EC0(void); // func_80A84EC0
void func_80A84FA0(void); // func_80A84FA0
void func_80A84FB4(void); // func_80A84FB4
void func_80A84FEC(void); // func_80A84FEC
void func_80A85010(void); // func_80A85010
void func_80A85048(void); // func_80A85048
void func_80A85074(void); // func_80A85074
void func_80A850B0(void); // func_80A850B0
void func_80A850E8(void); // func_80A850E8
void func_80A8515C(void); // func_80A8515C
void func_80A85194(void); // func_80A85194
void func_80A851A4(void); // func_80A851A4
void func_80A851C8(void); // func_80A851C8
void func_80A85304(void); // func_80A85304
void func_80A85620(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A85620
void func_80A85788(void); // func_80A85788
void func_80A85AA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A85AA4
void func_80A85BCC(void); // func_80A85BCC
void func_80A85E2C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8); // func_80A85E2C
void func_80A85F84(void); // func_80A85F84
void func_80A86384(void); // func_80A86384
void func_80A86460(void); // func_80A86460
void func_80A86674(void); // func_80A86674
void func_80A86770(void); // func_80A86770
void func_80A868F8(void); // func_80A868F8
void func_80A86924(void); // func_80A86924
void func_80A8697C(void); // func_80A8697C
void func_80A869DC(void); // func_80A869DC
void func_80A86B0C(void); // func_80A86B0C
void func_80A86BAC(void); // func_80A86BAC
void func_80A86DB8(void); // func_80A86DB8
void func_80A871E0(void); // func_80A871E0
void func_80A872AC(void); // func_80A872AC
void func_80A873B8(void); // func_80A873B8
void func_80A87400(void); // func_80A87400
void func_80A875AC(void); // func_80A875AC
void func_80A8777C(void); // func_80A8777C
void func_80A87880(void); // func_80A87880
void func_80A87B48(void); // func_80A87B48
void func_80A87DC0(void); // func_80A87DC0
void func_80A87FD0(void); // func_80A87FD0
void func_80A881E0(void); // func_80A881E0
void func_80A88334(void); // func_80A88334
void func_80A884BC(void); // func_80A884BC
void func_80A884E8(void); // func_80A884E8
void func_80A885B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A885B8
void func_80A88698(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A88698
void func_80A886D4(void); // func_80A886D4
void func_80A887E4(void); // func_80A887E4
void func_80A8B770(void); // func_80A8B770
void func_80A8B80C(void); // func_80A8B80C
void func_80A8B88C(void); // func_80A8B88C
void func_80A8B964(void); // func_80A8B964
void func_80A8B9B8(void); // func_80A8B9B8
void func_80A8BA3C(void); // func_80A8BA3C
void func_80A8BAF8(void); // func_80A8BAF8
void func_80A8BB3C(void); // func_80A8BB3C
void func_80A8BB8C(void); // func_80A8BB8C
void func_80A8BC8C(void); // func_80A8BC8C
void func_80A8BCD4(void); // func_80A8BCD4
void func_80A8BD28(void); // func_80A8BD28
void func_80A8BD7C(void); // func_80A8BD7C
void func_80A8BDD0(void); // func_80A8BDD0
void func_80A8BEF4(void); // func_80A8BEF4
void func_80A8BF24(void); // func_80A8BF24
void func_80A8BFE0(void); // func_80A8BFE0
void func_80A8C168(void); // func_80A8C168
void func_80A8C1E8(void); // func_80A8C1E8
void func_80A8C288(void); // func_80A8C288
void func_80A8C488(void); // func_80A8C488
void func_80A8C564(void); // func_80A8C564
void func_80A8C64C(void); // func_80A8C64C
void func_80A8C6CC(void); // func_80A8C6CC
void func_80A8C74C(void); // func_80A8C74C
void func_80A8C8A0(void); // func_80A8C8A0
void func_80A8C98C(void); // func_80A8C98C
void func_80A8CA2C(void); // func_80A8CA2C
void func_80A8CB0C(void); // func_80A8CB0C
void func_80A8CBFC(void); // func_80A8CBFC
void func_80A8CCB4(void); // func_80A8CCB4
void func_80A8CCF0(void); // func_80A8CCF0
void func_80A8CD2C(void); // func_80A8CD2C
void func_80A8CEE8(void); // func_80A8CEE8
void func_80A8D094(void); // func_80A8D094
void func_80A8D380(void); // func_80A8D380
void func_80A8D5C8(void); // func_80A8D5C8
void func_80A8D880(void); // func_80A8D880
void func_80A8D9CC(void); // func_80A8D9CC
void func_80A8DAAC(void); // func_80A8DAAC
void func_80A8DBBC(void); // func_80A8DBBC
void func_80A8DD10(void); // func_80A8DD10
void func_80A8DD60(void); // func_80A8DD60
void func_80A8DEBC(void); // func_80A8DEBC
void func_80A8DF20(void); // func_80A8DF20
void func_80A8DFBC(void); // func_80A8DFBC
void func_80A8E02C(void); // func_80A8E02C
void func_80A8E0D0(void); // func_80A8E0D0
void func_80A8E26C(void); // func_80A8E26C
void func_80A8E30C(void); // func_80A8E30C
void func_80A8E330(void); // func_80A8E330
void func_80A8E3CC(void); // func_80A8E3CC
void func_80A8E458(void); // func_80A8E458
void func_80A8E4D8(void); // func_80A8E4D8
void func_80A8E5A4(void); // func_80A8E5A4
void func_80A8E754(void); // func_80A8E754
void func_80A8E774(void); // func_80A8E774
void func_80A8E79C(void); // func_80A8E79C
void func_80A8E830(s32 param_1); // func_80A8E830
void func_80A8E890(void); // func_80A8E890
void func_80A8E91C(void); // func_80A8E91C
void func_80A8E92C(void); // func_80A8E92C
void func_80A8E94C(void); // func_80A8E94C
void func_80A8E9A4(void); // func_80A8E9A4
void func_80A8EB4C(void); // func_80A8EB4C
void func_80A8EB9C(void); // func_80A8EB9C
void func_80A8EBD8(void); // func_80A8EBD8
void func_80A8ECA4(void); // func_80A8ECA4
void func_80A8ED3C(void); // func_80A8ED3C
void func_80A8EFA4(void); // func_80A8EFA4
void func_80A8EFF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6); // func_80A8EFF8
void func_80A8F268(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_80A8F268
void func_80A8F404(void); // func_80A8F404
void func_80A8F7AC(void); // func_80A8F7AC
void func_80A8F7E8(void); // func_80A8F7E8
void func_80A8F828(void); // func_80A8F828
void func_80A8F8C4(void); // func_80A8F8C4
void func_80A8FA00(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A8FA00
void func_80A8FB34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80A8FB34
void func_80A8FBB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A8FBB4
void func_80A8FC64(void); // func_80A8FC64
void func_80A8FCE0(void); // func_80A8FCE0
void func_80A903B0(void); // func_80A903B0
void func_80A903BC(void); // func_80A903BC
void func_80A90468(void); // func_80A90468
void func_80A90478(void); // func_80A90478
void func_80A905A4(void); // func_80A905A4
void func_80A90730(void); // func_80A90730
void func_80A90C08(void); // func_80A90C08
void func_80A90C34(void); // func_80A90C34
void func_80A90C54(void); // func_80A90C54
void func_80A90D20(void); // func_80A90D20
void func_80A90D34(void); // func_80A90D34
void func_80A90FC0(void); // func_80A90FC0
void func_80A91324(void); // func_80A91324
void func_80A91330(void); // func_80A91330
void func_80A9149C(void); // func_80A9149C
void func_80A9156C(void); // func_80A9156C
void func_80A91690(void); // func_80A91690
void func_80A916F0(void); // func_80A916F0
void func_80A91760(void); // func_80A91760
void func_80A920C8(void); // func_80A920C8
void func_80A92118(void); // func_80A92118
void func_80A92188(void); // func_80A92188
void func_80A9292C(void); // func_80A9292C
void func_80A92950(void); // func_80A92950
void func_80A93298(void); // func_80A93298
void func_80A9369C(void); // func_80A9369C
void func_80A939E8(void); // func_80A939E8
void func_80A93DE8(void); // func_80A93DE8
void func_80A94A30(void); // func_80A94A30
void func_80A94A64(void); // func_80A94A64
void func_80A94A90(void); // func_80A94A90
void func_80A94AB8(void); // func_80A94AB8
void func_80A94B20(void); // func_80A94B20
void func_80A94B98(void); // func_80A94B98
void func_80A94C2C(void); // func_80A94C2C
void func_80A95464(void); // func_80A95464
void func_80A954AC(void); // func_80A954AC
void func_80A95534(void); // func_80A95534
void func_80A9565C(void); // func_80A9565C
void func_80A95730(void); // func_80A95730
void func_80A958B0(void); // func_80A958B0
void func_80A95B34(void); // func_80A95B34
void func_80A95C5C(void); // func_80A95C5C
void func_80A95CEC(void); // func_80A95CEC
void func_80A95DA0(void); // func_80A95DA0
void func_80A95E88(void); // func_80A95E88
void func_80A95F94(void); // func_80A95F94
void func_80A95FE8(void); // func_80A95FE8
void func_80A9617C(void); // func_80A9617C
void func_80A97114(void); // func_80A97114
void func_80A97274(void); // func_80A97274
void func_80A973B4(void); // func_80A973B4
void func_80A97410(void); // func_80A97410
void func_80A979DC(void); // func_80A979DC
void func_80A979F4(void); // func_80A979F4
void func_80A97A28(void); // func_80A97A28
void func_80A97A40(void); // func_80A97A40
void func_80A97A9C(void); // func_80A97A9C
void func_80A97AB4(void); // func_80A97AB4
void func_80A97C0C(void); // func_80A97C0C
void func_80A97C24(void); // func_80A97C24
void func_80A97C4C(void); // func_80A97C4C
void func_80A97D5C(void); // func_80A97D5C
void func_80A97E48(void); // func_80A97E48
void func_80A97EAC(void); // func_80A97EAC
void func_80A97F9C(void); // func_80A97F9C
void func_80A982E0(void); // func_80A982E0
void func_80A98414(void); // func_80A98414
void func_80A984CC(void); // func_80A984CC
void func_80A98734(void); // func_80A98734
void func_80A98DA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80A98DA4
void func_80A98E48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A98E48
void func_80A98EFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80A98EFC
void func_80A98F94(void); // func_80A98F94
void func_80A99000(void); // func_80A99000
void func_80A99EA0(void); // func_80A99EA0
void func_80A9A1B0(void); // func_80A9A1B0
void func_80A9A1DC(void); // func_80A9A1DC
void func_80A9A4B0(void); // func_80A9A4B0
void func_80A9A4E0(void); // func_80A9A4E0
void func_80A9A600(void); // func_80A9A600
void func_80A9A774(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80A9A774
void func_80A9A870(void); // func_80A9A870
void func_80A9A9C0(void); // func_80A9A9C0
void func_80A9ACD0(void); // func_80A9ACD0
void func_80A9ACF0(void); // func_80A9ACF0
void func_80A9AD18(void); // func_80A9AD18
void func_80A9AE3C(void); // func_80A9AE3C
void func_80A9AEB8(void); // func_80A9AEB8
void func_80A9AFB4(void); // func_80A9AFB4
void func_80A9B160(void); // func_80A9B160
void func_80A9B244(void); // func_80A9B244
void func_80A9B2B8(void); // func_80A9B2B8
void func_80A9B32C(void); // func_80A9B32C
void func_80A9B384(void); // func_80A9B384
void func_80A9B3BC(void); // func_80A9B3BC
void func_80A9B46C(void); // func_80A9B46C
void func_80A9B554(void); // func_80A9B554
void func_80A9BC0C(void); // func_80A9BC0C
void func_80A9BD24(void); // func_80A9BD24
void func_80A9C058(void); // func_80A9C058
void func_80A9C18C(void); // func_80A9C18C
void func_80A9C228(void); // func_80A9C228
void func_80A9C634(void); // func_80A9C634
void func_80A9C854(void); // func_80A9C854
void func_80A9C96C(void); // func_80A9C96C
void func_80A9CA44(void); // func_80A9CA44
void func_80A9CA94(void); // func_80A9CA94
void func_80A9CAA8(void); // func_80A9CAA8
void func_80A9CC84(void); // func_80A9CC84
void func_80A9CCA0(void); // func_80A9CCA0
void func_80A9CD00(void); // func_80A9CD00
void func_80A9CD14(void); // func_80A9CD14
void func_80A9CE00(void); // func_80A9CE00
void func_80A9CE1C(void); // func_80A9CE1C
void func_80A9D0A0(void); // func_80A9D0A0
void func_80A9D0B4(void); // func_80A9D0B4
void func_80A9D1E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80A9D1E0
void func_80A9D260(void); // func_80A9D260
void func_80A9D2C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80A9D2C4
void func_80A9D360(void); // func_80A9D360
void func_80A9D3E4(void); // func_80A9D3E4
void func_80A9D434(void); // func_80A9D434
void func_80A9D498(void); // func_80A9D498
void func_80A9D61C(void); // func_80A9D61C
void func_80A9F950(void); // func_80A9F950
void func_80A9F95C(void); // func_80A9F95C
void func_80A9FA1C(void); // func_80A9FA1C
void func_80A9FA58(void); // func_80A9FA58
void func_80A9FB54(void); // func_80A9FB54
void func_80A9FBB8(void); // func_80A9FBB8
void func_80A9FDB0(void); // func_80A9FDB0
void func_80A9FE3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80A9FE3C
void func_80A9FED8(void); // func_80A9FED8
void func_80AA00CC(void); // func_80AA00CC
void func_80AA0100(void); // func_80AA0100
void func_80AA0158(void); // func_80AA0158
void func_80AA01C0(void); // func_80AA01C0
void func_80AA0264(void); // func_80AA0264
void func_80AA0420(void); // func_80AA0420
void func_80AA05F0(void); // func_80AA05F0
void func_80AA0634(void); // func_80AA0634
void func_80AA066C(void); // func_80AA066C
void func_80AA071C(void); // func_80AA071C
void func_80AA076C(void); // func_80AA076C
void func_80AA09DC(void); // func_80AA09DC
void func_80AA0B08(void); // func_80AA0B08
void func_80AA0DA8(void); // func_80AA0DA8
void func_80AA0E1C(void); // func_80AA0E1C
void func_80AA0E90(void); // func_80AA0E90
void func_80AA1234(void); // func_80AA1234
void func_80AA16E4(void); // func_80AA16E4
void func_80AA16F4(void); // func_80AA16F4
void func_80AA1704(void); // func_80AA1704
void func_80AA1714(void); // func_80AA1714
void func_80AA17F8(void); // func_80AA17F8
void func_80AA18D8(void); // func_80AA18D8
void func_80AA192C(void); // func_80AA192C
void func_80AA1998(void); // func_80AA1998
void func_80AA19EC(void); // func_80AA19EC
void func_80AA1A50(void); // func_80AA1A50
void func_80AA1AC8(void); // func_80AA1AC8
void func_80AA1AF8(void); // func_80AA1AF8
void func_80AA1B9C(void); // func_80AA1B9C
void func_80AA1C64(void); // func_80AA1C64
void func_80AA1D1C(void); // func_80AA1D1C
void func_80AA26CC(void); // func_80AA26CC
void func_80AA2720(void); // func_80AA2720
void func_80AA27EC(void); // func_80AA27EC
void func_80AA2884(void); // func_80AA2884
void func_80AA2B14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AA2B14
void func_80AA2BC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AA2BC0
void func_80AA33A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AA33A4
void func_80AA33CC(void); // func_80AA33CC
void func_80AA5580(void); // func_80AA5580
void func_80AA561C(void); // func_80AA561C
void func_80AA5720(void); // func_80AA5720
void func_80AA575C(void); // func_80AA575C
void func_80AA5890(void); // func_80AA5890
void func_80AA58CC(void); // func_80AA58CC
void func_80AA5950(void); // func_80AA5950
void func_80AA5960(void); // func_80AA5960
void func_80AA59E4(void); // func_80AA59E4
void func_80AA5A6C(void); // func_80AA5A6C
void func_80AA5AF4(void); // func_80AA5AF4
void func_80AA5BF8(void); // func_80AA5BF8
void func_80AA5CD4(void); // func_80AA5CD4
void func_80AA5D10(void); // func_80AA5D10
void func_80AA5D6C(void); // func_80AA5D6C
void func_80AA5DC8(void); // func_80AA5DC8
void func_80AA5E2C(void); // func_80AA5E2C
void func_80AA5EBC(void); // func_80AA5EBC
void func_80AA6178(void); // func_80AA6178
void func_80AA62EC(void); // func_80AA62EC
void func_80AA62FC(void); // func_80AA62FC
void func_80AA67F8(void); // func_80AA67F8
void func_80AA695C(void); // func_80AA695C
void func_80AA6A04(void); // func_80AA6A04
void func_80AA6A6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AA6A6C
void func_80AA6B34(void); // func_80AA6B34
void func_80AA81E0(void); // func_80AA81E0
void func_80AA8660(void); // func_80AA8660
void func_80AA8698(void); // func_80AA8698
void func_80AA884C(void); // func_80AA884C
void func_80AA88A8(void); // func_80AA88A8
void func_80AA892C(void); // func_80AA892C
void func_80AA8C28(void); // func_80AA8C28
void func_80AA8F0C(void); // func_80AA8F0C
void func_80AA8F1C(void); // func_80AA8F1C
void func_80AA8F2C(void); // func_80AA8F2C
void func_80AA9020(void); // func_80AA9020
void func_80AA90AC(void); // func_80AA90AC
void func_80AA90F4(void); // func_80AA90F4
void func_80AA9140(void); // func_80AA9140
void func_80AA922C(void); // func_80AA922C
void func_80AAAE30(void); // func_80AAAE30
void func_80AAAECC(void); // func_80AAAECC
void func_80AAAF2C(void); // func_80AAAF2C
void func_80AAAF78(void); // func_80AAAF78
void func_80AAB03C(void); // func_80AAB03C
void func_80AAB04C(void); // func_80AAB04C
void func_80AAB19C(void); // func_80AAB19C
void func_80AAB23C(void); // func_80AAB23C
void func_80AAB258(void); // func_80AAB258
void func_80AAB270(void); // func_80AAB270
void func_80AAB284(void); // func_80AAB284
void func_80AAB4A0(void); // func_80AAB4A0
void func_80AAB53C(void); // func_80AAB53C
void func_80AAB5E8(void); // func_80AAB5E8
void func_80AAB5F8(void); // func_80AAB5F8
void func_80AAB644(void); // func_80AAB644
void func_80AAB700(void); // func_80AAB700
void func_80AAB710(void); // func_80AAB710
void func_80AAB838(void); // func_80AAB838
void func_80AAB8DC(void); // func_80AAB8DC
void func_80AAB974(void); // func_80AAB974
void func_80AAB990(void); // func_80AAB990
void func_80AAB9A8(void); // func_80AAB9A8
void func_80AAB9BC(void); // func_80AAB9BC
void func_80AABA84(void); // func_80AABA84
void func_80AABC40(void); // func_80AABC40
void func_80AABCDC(void); // func_80AABCDC
void func_80AABE24(void); // func_80AABE24
void func_80AABE34(void); // func_80AABE34
void func_80AABF28(void); // func_80AABF28
void func_80AABF74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AABF74
void func_80AAC03C(void); // func_80AAC03C
void func_80AAC5A0(void); // func_80AAC5A0
void func_80AAC63C(void); // func_80AAC63C
void func_80AAC6E4(void); // func_80AAC6E4
void func_80AAC770(void); // func_80AAC770
void func_80AAC7FC(void); // func_80AAC7FC
void func_80AAC888(void); // func_80AAC888
void func_80AAC8A0(void); // func_80AAC8A0
void func_80AAC980(void); // func_80AAC980
void func_80AAC990(void); // func_80AAC990
void func_80AAC9DC(void); // func_80AAC9DC
void func_80AACA98(void); // func_80AACA98
void func_80AACAE4(void); // func_80AACAE4
void func_80AACBE4(void); // func_80AACBE4
void func_80AACC48(void); // func_80AACC48
void func_80AACC6C(void); // func_80AACC6C
void func_80AACCD4(void); // func_80AACCD4
void func_80AACD0C(void); // func_80AACD0C
void func_80AACD1C(void); // func_80AACD1C
void func_80AACD68(void); // func_80AACD68
void func_80AACE10(void); // func_80AACE10
void func_80AACE5C(void); // func_80AACE5C
void func_80AACF04(void); // func_80AACF04
void func_80AAD3F8(void); // func_80AAD3F8
void func_80AAD450(void); // func_80AAD450
void func_80AAD4A8(void); // func_80AAD4A8
void func_80AAD78C(void); // func_80AAD78C
void func_80AAD964(void); // func_80AAD964
void func_80AAD980(void); // func_80AAD980
void func_80AAD998(void); // func_80AAD998
void func_80AADA90(void); // func_80AADA90
void func_80AADB4C(void); // func_80AADB4C
void func_80AADC00(void); // func_80AADC00
void func_80AADCE8(void); // func_80AADCE8
void func_80AADD9C(void); // func_80AADD9C
void func_80AADE78(void); // func_80AADE78
void func_80AADF54(void); // func_80AADF54
void func_80AAE030(void); // func_80AAE030
void func_80AAE114(void); // func_80AAE114
void func_80AAE1E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AAE1E4
void func_80AAE680(void); // func_80AAE680
void func_80AAE68C(void); // func_80AAE68C
void func_80AAE6E0(void); // func_80AAE6E0
void func_80AAE6F0(void); // func_80AAE6F0
void func_80AAE854(void); // func_80AAE854
void func_80AAE878(void); // func_80AAE878
void func_80AAE9C0(void); // func_80AAE9C0
void func_80AAE9CC(void); // func_80AAE9CC
void func_80AAEA84(void); // func_80AAEA84
void func_80AAEABC(void); // func_80AAEABC
void func_80AAEACC(void); // func_80AAEACC
void func_80AAEAF0(void); // func_80AAEAF0
void func_80AAF050(void); // func_80AAF050
void func_80AAF15C(void); // func_80AAF15C
void func_80AAF1F8(void); // func_80AAF1F8
void func_80AAF5D8(void); // func_80AAF5D8
void func_80AAF610(void); // func_80AAF610
void func_80AAF79C(void); // func_80AAF79C
void func_80AAF884(void); // func_80AAF884
void func_80AAF8F4(void); // func_80AAF8F4
void func_80AAFA18(void); // func_80AAFA18
void func_80AAFAC4(void); // func_80AAFAC4
void func_80AAFAE4(void); // func_80AAFAE4
void func_80AAFB04(void); // func_80AAFB04
void func_80AAFB94(void); // func_80AAFB94
void func_80AAFBA4(void); // func_80AAFBA4
void func_80AAFCCC(void); // func_80AAFCCC
void func_80AAFE78(void); // func_80AAFE78
void func_80AAFE88(void); // func_80AAFE88
void func_80AB01E8(void); // func_80AB01E8
void func_80AB023C(void); // func_80AB023C
void func_80AB032C(void); // func_80AB032C
void func_80AB096C(void); // func_80AB096C
void func_80AB0A10(void); // func_80AB0A10
void func_80AB0CC8(void); // func_80AB0CC8
void func_80AB0E3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AB0E3C
void func_80AB0E7C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AB0E7C
void func_80AB0F90(void); // func_80AB0F90
void func_80AB1124(void); // func_80AB1124
void func_80AB1E10(void); // func_80AB1E10
void func_80AB1EAC(void); // func_80AB1EAC
void func_80AB1F90(void); // func_80AB1F90
void func_80AB1FA0(void); // func_80AB1FA0
void func_80AB1FDC(void); // func_80AB1FDC
void func_80AB2258(void); // func_80AB2258
void func_80AB2268(void); // func_80AB2268
void func_80AB24BC(void); // func_80AB24BC
void func_80AB2544(void); // func_80AB2544
void func_80AB25D8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AB25D8
void func_80AB261C(void); // func_80AB261C
void func_80AB2790(void); // func_80AB2790
void func_80AB27B4(void); // func_80AB27B4
void func_80AB2834(void); // func_80AB2834
void func_80AB28C8(void); // func_80AB28C8
void func_80AB29F8(void); // func_80AB29F8
void func_80AB2BBC(void); // func_80AB2BBC
void func_80AB2DEC(void); // func_80AB2DEC
void func_80AB3000(void); // func_80AB3000
void func_80AB3010(void); // func_80AB3010
void func_80AB319C(void); // func_80AB319C
void func_80AB3240(void); // func_80AB3240
void func_80AB32F0(void); // func_80AB32F0
void func_80AB3370(void); // func_80AB3370
void func_80AB34CC(void); // func_80AB34CC
void func_80AB3544(void); // func_80AB3544
void func_80AB3598(void); // func_80AB3598
void func_80AB363C(void); // func_80AB363C
void func_80AB365C(void); // func_80AB365C
void func_80AB36C4(void); // func_80AB36C4
void func_80AB3808(void); // func_80AB3808
void func_80AB3880(void); // func_80AB3880
void func_80AB38B0(void); // func_80AB38B0
void func_80AB39BC(void); // func_80AB39BC
void func_80AB3A7C(void); // func_80AB3A7C
void func_80AB3B34(void); // func_80AB3B34
void func_80AB3BB0(void); // func_80AB3BB0
void func_80AB3BD8(void); // func_80AB3BD8
void func_80AB3BE8(void); // func_80AB3BE8
void func_80AB3C50(void); // func_80AB3C50
void func_80AB3CCC(void); // func_80AB3CCC
void func_80AB3ED0(void); // func_80AB3ED0
void func_80AB4040(void); // func_80AB4040
void func_80AB4080(void); // func_80AB4080
void func_80AB4160(void); // func_80AB4160
void func_80AB4278(void); // func_80AB4278
void func_80AB429C(void); // func_80AB429C
void func_80AB4394(void); // func_80AB4394
void func_80AB4664(void); // func_80AB4664
void func_80AB4894(void); // func_80AB4894
void func_80AB4D10(void); // func_80AB4D10
void func_80AB4E34(void); // func_80AB4E34
void func_80AB4E58(void); // func_80AB4E58
void func_80AB4E88(void); // func_80AB4E88
void func_80AB4F68(void); // func_80AB4F68
void func_80AB4F8C(void); // func_80AB4F8C
void func_80AB50B0(void); // func_80AB50B0
void func_80AB50D4(void); // func_80AB50D4
void func_80AB5148(void); // func_80AB5148
void func_80AB51C8(void); // func_80AB51C8
void func_80AB52E8(void); // func_80AB52E8
void func_80AB53DC(void); // func_80AB53DC
void func_80AB57E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AB57E0
void func_80AB57F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AB57F4
void func_80AB5830(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AB5830
void func_80AB585C(void); // func_80AB585C
void func_80AB58B0(void); // func_80AB58B0
void func_80AB58D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AB58D0
void func_80AB58E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11); // func_80AB58E4
void func_80AB58F8(void); // func_80AB58F8
void func_80AB5958(void); // func_80AB5958
void func_80AB596C(void); // func_80AB596C
void func_80AB5994(void); // func_80AB5994
void func_80AB59E8(void); // func_80AB59E8
void func_80AB5A64(void); // func_80AB5A64
void func_80AB5B38(void); // func_80AB5B38
void func_80AB5B84(void); // func_80AB5B84
void func_80AB5BCC(void); // func_80AB5BCC
void func_80AB5C14(void); // func_80AB5C14
void func_80AB5C74(void); // func_80AB5C74
void func_80AB5CD8(void); // func_80AB5CD8
void func_80AB5F6C(void); // func_80AB5F6C
void func_80AB60FC(void); // func_80AB60FC
void func_80AB61E8(void); // func_80AB61E8
void func_80AB6304(void); // func_80AB6304
void func_80AB63CC(void); // func_80AB63CC
void func_80AB64B8(void); // func_80AB64B8
void func_80AB65F4(void); // func_80AB65F4
void func_80AB675C(void); // func_80AB675C
void func_80AB6870(void); // func_80AB6870
void func_80AB6920(void); // func_80AB6920
void func_80AB69C8(void); // func_80AB69C8
void func_80AB6AF8(void); // func_80AB6AF8
void func_80AB6B78(void); // func_80AB6B78
void func_80AB6BE4(void); // func_80AB6BE4
void func_80AB6E08(void); // func_80AB6E08
void func_80AB6EB0(void); // func_80AB6EB0
void func_80AB6F98(void); // func_80AB6F98
void func_80AB7108(void); // func_80AB7108
void func_80AB7204(void); // func_80AB7204
void func_80AB72BC(void); // func_80AB72BC
void func_80AB7354(void); // func_80AB7354
void func_80AB740C(void); // func_80AB740C
void func_80AB7488(void); // func_80AB7488
void func_80AB7504(void); // func_80AB7504
void func_80AB75A4(void); // func_80AB75A4
void func_80AB7620(void); // func_80AB7620
void func_80AB76B0(void); // func_80AB76B0
void func_80AB794C(void); // func_80AB794C
void func_80AB7AC8(void); // func_80AB7AC8
void func_80AB7B20(void); // func_80AB7B20
void func_80AB7DCC(void); // func_80AB7DCC
void func_80AB7E50(void); // func_80AB7E50
void func_80AB8040(void); // func_80AB8040
void func_80AB80BC(void); // func_80AB80BC
void func_80AB81D8(void); // func_80AB81D8
void func_80AB8478(void); // func_80AB8478
void func_80AB852C(void); // func_80AB852C
void func_80AB85C8(void); // func_80AB85C8
void func_80AB8644(void); // func_80AB8644
void func_80AB86AC(void); // func_80AB86AC
void func_80AB8750(void); // func_80AB8750
void func_80AB8878(void); // func_80AB8878
void func_80AB8968(void); // func_80AB8968
void func_80AB89F8(void); // func_80AB89F8
void func_80AB8A74(void); // func_80AB8A74
void func_80AB8B18(void); // func_80AB8B18
void func_80AB8BD4(void); // func_80AB8BD4
void func_80AB8C60(void); // func_80AB8C60
void func_80AB8CFC(void); // func_80AB8CFC
void func_80AB8E4C(void); // func_80AB8E4C
void func_80AB8EF4(void); // func_80AB8EF4
void func_80AB8FD8(void); // func_80AB8FD8
void func_80AB9084(void); // func_80AB9084
void func_80AB92CC(void); // func_80AB92CC
void func_80AB94E4(void); // func_80AB94E4
void func_80AB94F4(void); // func_80AB94F4
void func_80AB96A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AB96A0
void func_80AB96E8(void); // func_80AB96E8
void func_80AB9708(void); // func_80AB9708
void func_80AB973C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AB973C
void func_80AB977C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AB977C
void func_80AB97B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AB97B4
void func_80AB99D4(void); // func_80AB99D4
void func_80AB9B48(void); // func_80AB9B48
void func_80AB9BAC(void); // func_80AB9BAC
void func_80AB9C4C(void); // func_80AB9C4C
void func_80ABA7A0(void); // func_80ABA7A0
void func_80ABA868(void); // func_80ABA868
void func_80ABA8A4(void); // func_80ABA8A4
void func_80ABA988(void); // func_80ABA988
void func_80ABA9B8(void); // func_80ABA9B8
void func_80ABA9C8(void); // func_80ABA9C8
void func_80ABAA14(void); // func_80ABAA14
void func_80ABAAF4(void); // func_80ABAAF4
void func_80ABACB4(void); // func_80ABACB4
void func_80ABAE64(void); // func_80ABAE64
void func_80ABB0E0(void); // func_80ABB0E0
void func_80ABB1E4(void); // func_80ABB1E4
void func_80ABB210(void); // func_80ABB210
void func_80ABB29C(void); // func_80ABB29C
void func_80ABB2D4(void); // func_80ABB2D4
void func_80ABB540(void); // func_80ABB540
void func_80ABB590(void); // func_80ABB590
void func_80ABB854(void); // func_80ABB854
void func_80ABB91C(void); // func_80ABB91C
void func_80ABB990(void); // func_80ABB990
void func_80ABBACC(void); // func_80ABBACC
void func_80ABBC60(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80ABBC60
void func_80ABBCB8(void); // func_80ABBCB8
void func_80ABBFC0(void); // func_80ABBFC0
void func_80ABC2E0(void); // func_80ABC2E0
void func_80ABC58C(void); // func_80ABC58C
void func_80ABC7FC(void); // func_80ABC7FC
void func_80ABCA00(void); // func_80ABCA00
void func_80ABCB14(void); // func_80ABCB14
void func_80ABCB5C(void); // func_80ABCB5C
void func_80ABCC00(void); // func_80ABCC00
void func_80ABCCE4(void); // func_80ABCCE4
void func_80ABCD98(void); // func_80ABCD98
void func_80ABCE60(void); // func_80ABCE60
void func_80ABCEE8(void); // func_80ABCEE8
void func_80ABCF0C(void); // func_80ABCF0C
void func_80ABD1D0(void); // func_80ABD1D0
void func_80ABD37C(void); // func_80ABD37C
void func_80ABD3B0(void); // func_80ABD3B0
void func_80ABD424(void); // func_80ABD424
void func_80ABD6F0(void); // func_80ABD6F0
void func_80ABD830(void); // func_80ABD830
void func_80ABD8F8(void); // func_80ABD8F8
void func_80ABD92C(void); // func_80ABD92C
void func_80ABDB98(void); // func_80ABDB98
void func_80ABDBBC(void); // func_80ABDBBC
void func_80ABDCA0(void); // func_80ABDCA0
void func_80ABDD2C(void); // func_80ABDD2C
void func_80ABDD9C(void); // func_80ABDD9C
void func_80ABDE60(void); // func_80ABDE60
void func_80ABDF70(void); // func_80ABDF70
void func_80ABE188(void); // func_80ABE188
void func_80ABE1C4(void); // func_80ABE1C4
void func_80ABE4A4(void); // func_80ABE4A4
void func_80ABE560(void); // func_80ABE560
void func_80ABE6C8(void); // func_80ABE6C8
void func_80ABEB6C(void); // func_80ABEB6C
void func_80ABEF34(void); // func_80ABEF34
void func_80ABEF8C(void); // func_80ABEF8C
void func_80ABF070(void); // func_80ABF070
void func_80ABF084(void); // func_80ABF084
void func_80ABF0D8(void); // func_80ABF0D8
void func_80ABF160(void); // func_80ABF160
void func_80ABF198(void); // func_80ABF198
void func_80ABF218(void); // func_80ABF218
void func_80ABF254(void); // func_80ABF254
void func_80ABF2FC(void); // func_80ABF2FC
void func_80ABF354(void); // func_80ABF354
void func_80ABF494(void); // func_80ABF494
void func_80ABF4A8(void); // func_80ABF4A8
void func_80ABF51C(void); // func_80ABF51C
void func_80ABF534(void); // func_80ABF534
void func_80ABF69C(void); // func_80ABF69C
void func_80ABF6B0(void); // func_80ABF6B0
void func_80ABF760(void); // func_80ABF760
void func_80ABF774(void); // func_80ABF774
void func_80ABF7C8(void); // func_80ABF7C8
void func_80ABFCAC(void); // func_80ABFCAC
void func_80ABFCD4(void); // func_80ABFCD4
void func_80ABFD18(void); // func_80ABFD18
void func_80ABFD9C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80ABFD9C
void func_80ABFE48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80ABFE48
void func_80ABFEF4(void); // func_80ABFEF4
void func_80AC0830(void); // func_80AC0830
void func_80AC0A20(void); // func_80AC0A20
void func_80AC0A54(void); // func_80AC0A54
void func_80AC0A6C(void); // func_80AC0A6C
void func_80AC0A7C(void); // func_80AC0A7C
void func_80AC0AC8(void); // func_80AC0AC8
void func_80AC0CC4(void); // func_80AC0CC4
void func_80AC0D2C(void); // func_80AC0D2C
void func_80AC100C(void); // func_80AC100C
void func_80AC1030(void); // func_80AC1030
void func_80AC1270(void); // func_80AC1270
void func_80AC1424(void); // func_80AC1424
void func_80AC1450(void); // func_80AC1450
void func_80AC14A4(void); // func_80AC14A4
void func_80AC1574(void); // func_80AC1574
void func_80AC158C(void); // func_80AC158C
void func_80AC18EC(void); // func_80AC18EC
void func_80AC192C(void); // func_80AC192C
void func_80AC19B0(void); // func_80AC19B0
void func_80AC19DC(void); // func_80AC19DC
void func_80AC1A1C(void); // func_80AC1A1C
void func_80AC1A68(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AC1A68
void func_80AC1CE8(void); // func_80AC1CE8
void func_80AC1D00(void); // func_80AC1D00
void func_80AC1D14(void); // func_80AC1D14
void func_80AC1ED0(void); // func_80AC1ED0
void func_80AC2018(void); // func_80AC2018
void func_80AC2044(void); // func_80AC2044
void func_80AC20A8(void); // func_80AC20A8
void func_80AC2118(void); // func_80AC2118
void func_80AC2154(void); // func_80AC2154
void func_80AC21A0(void); // func_80AC21A0
void func_80AC2354(void); // func_80AC2354
void func_80AC2430(void); // func_80AC2430
void func_80AC24A8(void); // func_80AC24A8
void func_80AC26F0(void); // func_80AC26F0
void func_80AC2874(void); // func_80AC2874
void func_80AC28B4(void); // func_80AC28B4
void func_80AC299C(void); // func_80AC299C
void func_80AC2A1C(void); // func_80AC2A1C
void func_80AC2A7C(void); // func_80AC2A7C
void func_80AC2B4C(void); // func_80AC2B4C
void func_80AC2B98(void); // func_80AC2B98
void func_80AC2C30(void); // func_80AC2C30
void func_80AC2C84(void); // func_80AC2C84
void func_80AC2CE8(void); // func_80AC2CE8
void func_80AC2DAC(void); // func_80AC2DAC
void func_80AC2EBC(void); // func_80AC2EBC
void func_80AC2F20(void); // func_80AC2F20
void func_80AC2F64(void); // func_80AC2F64
void func_80AC3054(void); // func_80AC3054
void func_80AC30EC(void); // func_80AC30EC
void func_80AC31EC(void); // func_80AC31EC
void func_80AC33A4(void); // func_80AC33A4
void func_80AC33C0(void); // func_80AC33C0
void func_80AC3460(void); // func_80AC3460
void func_80AC34A8(void); // func_80AC34A8
void func_80AC35E8(void); // func_80AC35E8
void func_80AC3650(void); // func_80AC3650
void func_80AC3930(void); // func_80AC3930
void func_80AC39A0(void); // func_80AC39A0
void func_80AC3B2C(void); // func_80AC3B2C
void func_80AC3D48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80AC3D48
void func_80AC4204(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AC4204
void func_80AC42F8(void); // func_80AC42F8
void func_80AC48F0(void); // func_80AC48F0
void func_80AC4A04(void); // func_80AC4A04
void func_80AC4A80(void); // func_80AC4A80
void func_80AC4AE8(void); // func_80AC4AE8
void func_80AC4C18(void); // func_80AC4C18
void func_80AC4C34(void); // func_80AC4C34
void func_80AC4CF0(void); // func_80AC4CF0
void func_80AC4D2C(void); // func_80AC4D2C
void func_80AC4E98(void); // func_80AC4E98
void func_80AC4ED8(void); // func_80AC4ED8
void func_80AC5070(void); // func_80AC5070
void func_80AC50A8(void); // func_80AC50A8
void func_80AC5148(void); // func_80AC5148
void func_80AC5154(void); // func_80AC5154
void func_80AC5268(void); // func_80AC5268
void func_80AC5274(void); // func_80AC5274
void func_80AC528C(void); // func_80AC528C
void func_80AC559C(void); // func_80AC559C
void func_80AC57B0(void); // func_80AC57B0
void func_80AC5868(void); // func_80AC5868
void func_80AC5894(void); // func_80AC5894
void func_80AC58A0(void); // func_80AC58A0
void func_80AC5980(void); // func_80AC5980
void func_80AC5BBC(void); // func_80AC5BBC
void func_80AC5BC8(void); // func_80AC5BC8
void func_80AC5C08(void); // func_80AC5C08
void func_80AC5C14(void); // func_80AC5C14
void func_80AC6740(void); // func_80AC6740
void func_80AC687C(void); // func_80AC687C
void func_80AC68A8(void); // func_80AC68A8
void func_80AC68E0(void); // func_80AC68E0
void func_80AC69F8(void); // func_80AC69F8
void func_80AC6BE4(void); // func_80AC6BE4
void func_80AC6BF0(void); // func_80AC6BF0
void func_80AC6C3C(void); // func_80AC6C3C
void func_80AC6C48(void); // func_80AC6C48
void func_80AC8430(void); // func_80AC8430
void func_80AC84B4(void); // func_80AC84B4
void func_80AC84E0(void); // func_80AC84E0
void func_80AC84EC(void); // func_80AC84EC
void func_80AC8544(void); // func_80AC8544
void func_80AC85E0(void); // func_80AC85E0
void func_80AC85EC(void); // func_80AC85EC
void func_80AC862C(void); // func_80AC862C
void func_80AC8638(void); // func_80AC8638
void func_80AC86F0(void); // func_80AC86F0
void func_80AC8774(void); // func_80AC8774
void func_80AC87A0(void); // func_80AC87A0
void func_80AC87AC(void); // func_80AC87AC
void func_80AC881C(void); // func_80AC881C
void func_80AC8A50(void); // func_80AC8A50
void func_80AC8A5C(void); // func_80AC8A5C
void func_80AC8A94(void); // func_80AC8A94
void func_80AC8AA0(void); // func_80AC8AA0
void func_80AC8B50(void); // func_80AC8B50
void func_80AC8ECC(void); // func_80AC8ECC
void func_80AC9164(void); // func_80AC9164
void func_80AC933C(void); // func_80AC933C
void func_80AC94C0(void); // func_80AC94C0
void func_80AC94FC(void); // func_80AC94FC
void func_80AC964C(void); // func_80AC964C
void func_80AC9680(void); // func_80AC9680
void func_80AC96A4(void); // func_80AC96A4
void func_80AC96B4(void); // func_80AC96B4
void func_80AC96D0(void); // func_80AC96D0
void func_80AC99C0(void); // func_80AC99C0
void func_80AC99D4(void); // func_80AC99D4
void func_80AC9A68(void); // func_80AC9A68
void func_80AC9A7C(void); // func_80AC9A7C
void func_80AC9AB8(void); // func_80AC9AB8
void func_80AC9AE0(void); // func_80AC9AE0
void func_80AC9B48(void); // func_80AC9B48
void func_80AC9B5C(void); // func_80AC9B5C
void func_80AC9C20(void); // func_80AC9C20
void func_80AC9C48(void); // func_80AC9C48
void func_80AC9CAC(void); // func_80AC9CAC
void func_80AC9D10(void); // func_80AC9D10
void func_80AC9EA0(void); // func_80AC9EA0
void func_80AC9FC4(void); // func_80AC9FC4
void func_80AC9FD4(void); // func_80AC9FD4
void func_80AC9FE4(void); // func_80AC9FE4
void func_80ACA0A8(void); // func_80ACA0A8
void func_80ACA12C(void); // func_80ACA12C
void func_80ACA184(void); // func_80ACA184
void func_80ACA208(void); // func_80ACA208
void func_80ACA268(void); // func_80ACA268
void func_80ACA348(void); // func_80ACA348
void func_80ACA3C0(void); // func_80ACA3C0
void func_80ACA418(void); // func_80ACA418
void func_80ACA5F8(void); // func_80ACA5F8
void func_80ACA714(void); // func_80ACA714
void func_80ACA724(void); // func_80ACA724
void func_80ACA7C4(void); // func_80ACA7C4
void func_80ACA840(void); // func_80ACA840
void func_80ACA9AC(void); // func_80ACA9AC
void func_80ACAB10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80ACAB10
void func_80ACABA8(void); // func_80ACABA8
void func_80ACACC8(void); // func_80ACACC8
void func_80ACAD28(void); // func_80ACAD28
void func_80ACAD88(void); // func_80ACAD88
void func_80ACAE5C(void); // func_80ACAE5C
void func_80ACAEF0(void); // func_80ACAEF0
void func_80ACB004(void); // func_80ACB004
void func_80ACB0E8(void); // func_80ACB0E8
void func_80ACB1E0(void); // func_80ACB1E0
void func_80ACB220(void); // func_80ACB220
void func_80ACB230(void); // func_80ACB230
void func_80ACB2B0(void); // func_80ACB2B0
void BgFuKaiten_Init(ActorBgFuKaiten* this, GlobalContext* ctxt); // func_80ACB400
void BgFuKaiten_Fini(ActorBgFuKaiten* this, GlobalContext* ctxt); // func_80ACB480
void BgFuKaiten_UpdateRotation(ActorBgFuKaiten* this); // func_80ACB4B4
void BgFuKaiten_UpdateHeight(ActorBgFuKaiten* this); // func_80ACB50C
void BgFuKaiten_Main(ActorBgFuKaiten* this, GlobalContext* ctxt); // func_80ACB570
void BgFuKaiten_Draw(ActorBgFuKaiten* this, GlobalContext* ctxt); // func_80ACB5A0
void func_80ACB6A0(void); // func_80ACB6A0
void func_80ACB7F4(void); // func_80ACB7F4
void func_80ACB940(void); // func_80ACB940
void func_80ACBA10(void); // func_80ACBA10
void func_80ACBA60(void); // func_80ACBA60
void func_80ACBAD8(void); // func_80ACBAD8
void func_80ACBC44(void); // func_80ACBC44
void func_80ACBC70(void); // func_80ACBC70
void func_80ACBC8C(void); // func_80ACBC8C
void func_80ACBD34(void); // func_80ACBD34
void func_80ACBD48(void); // func_80ACBD48
void func_80ACBDCC(void); // func_80ACBDCC
void func_80ACBDFC(void); // func_80ACBDFC
void func_80ACBEE0(void); // func_80ACBEE0
void func_80ACC048(void); // func_80ACC048
void func_80ACC470(void); // func_80ACC470
void func_80ACC50C(void); // func_80ACC50C
void func_80ACC7A4(void); // func_80ACC7A4
void func_80ACC7E4(void); // func_80ACC7E4
void func_80ACC8D4(void); // func_80ACC8D4
void func_80ACC934(void); // func_80ACC934
void func_80ACC994(void); // func_80ACC994
void func_80ACCAC0(void); // func_80ACCAC0
void func_80ACCBB8(void); // func_80ACCBB8
void func_80ACCBD0(void); // func_80ACCBD0
void func_80ACCC98(void); // func_80ACCC98
void func_80ACCE4C(void); // func_80ACCE4C
void func_80ACCEB0(void); // func_80ACCEB0
void func_80ACD088(void); // func_80ACD088
void func_80ACD164(void); // func_80ACD164
void func_80ACD1B0(void); // func_80ACD1B0
void func_80ACD1F0(void); // func_80ACD1F0
void func_80ACD2E4(void); // func_80ACD2E4
void func_80ACD59C(void); // func_80ACD59C
void func_80ACD610(void); // func_80ACD610
void func_80ACD6A8(void); // func_80ACD6A8
void func_80ACD6EC(void); // func_80ACD6EC
void func_80ACD798(void); // func_80ACD798
void func_80ACD878(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80ACD878
void func_80ACD8C0(void); // func_80ACD8C0
void func_80ACDCD0(void); // func_80ACDCD0
void func_80ACDE34(void); // func_80ACDE34
void func_80ACDE60(void); // func_80ACDE60
void func_80ACE030(void); // func_80ACE030
void func_80ACE0E8(void); // func_80ACE0E8
void func_80ACE130(void); // func_80ACE130
void func_80ACE330(void); // func_80ACE330
void func_80ACE46C(void); // func_80ACE46C
void func_80ACE4B4(void); // func_80ACE4B4
void func_80ACE4C8(void); // func_80ACE4C8
void func_80ACE508(void); // func_80ACE508
void func_80ACE51C(void); // func_80ACE51C
void func_80ACE680(void); // func_80ACE680
void func_80ACE718(void); // func_80ACE718
void func_80ACE850(void); // func_80ACE850
void func_80ACEB2C(void); // func_80ACEB2C
void func_80ACECFC(void); // func_80ACECFC
void func_80ACEFC4(void); // func_80ACEFC4
void func_80ACEFD8(void); // func_80ACEFD8
void func_80ACF04C(void); // func_80ACF04C
void func_80ACF19C(void); // func_80ACF19C
void func_80ACF1F4(void); // func_80ACF1F4
void func_80ACF3F4(void); // func_80ACF3F4
void func_80ACF504(void); // func_80ACF504
void func_80ACF780(void); // func_80ACF780
void func_80ACF884(void); // func_80ACF884
void func_80ACF8B8(void); // func_80ACF8B8
void func_80ACF994(void); // func_80ACF994
void func_80ACF9A8(void); // func_80ACF9A8
void func_80ACF9DC(void); // func_80ACF9DC
void func_80ACF9FC(void); // func_80ACF9FC
void func_80ACFA78(void); // func_80ACFA78
void func_80ACFDAC(void); // func_80ACFDAC
void func_80AD0028(void); // func_80AD0028
void func_80AD0274(void); // func_80AD0274
void func_80AD0288(void); // func_80AD0288
void func_80AD02FC(void); // func_80AD02FC
void func_80AD0340(void); // func_80AD0340
void func_80AD04A4(void); // func_80AD04A4
void func_80AD0830(void); // func_80AD0830
void func_80AD08B0(void); // func_80AD08B0
void func_80AD0998(void); // func_80AD0998
void func_80AD0A24(void); // func_80AD0A24
void func_80AD0AB0(void); // func_80AD0AB0
void func_80AD0B38(void); // func_80AD0B38
void func_80AD0E10(void); // func_80AD0E10
void func_80AD10FC(void); // func_80AD10FC
void func_80AD1398(void); // func_80AD1398
void func_80AD144C(void); // func_80AD144C
void func_80AD14C8(void); // func_80AD14C8
void func_80AD1634(void); // func_80AD1634
void func_80AD16A8(void); // func_80AD16A8
void func_80AD19A0(void); // func_80AD19A0
void func_80AD1A4C(void); // func_80AD1A4C
void func_80AD1A5C(void); // func_80AD1A5C
void func_80AD1C88(void); // func_80AD1C88
void func_80AD1CC8(void); // func_80AD1CC8
void func_80AD1DA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AD1DA8
void func_80AD1E28(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AD1E28
void func_80AD1F88(void); // func_80AD1F88
void func_80AD2B70(void); // func_80AD2B70
void func_80AD2E84(void); // func_80AD2E84
void func_80AD2F8C(void); // func_80AD2F8C
void func_80AD2FD8(void); // func_80AD2FD8
void func_80AD3054(void); // func_80AD3054
void func_80AD3124(void); // func_80AD3124
void func_80AD3164(void); // func_80AD3164
void func_80AD3380(void); // func_80AD3380
void func_80AD341C(void); // func_80AD341C
void func_80AD349C(void); // func_80AD349C
void func_80AD3530(void); // func_80AD3530
void func_80AD3664(void); // func_80AD3664
void func_80AD36EC(void); // func_80AD36EC
void func_80AD381C(void); // func_80AD381C
void func_80AD38B8(void); // func_80AD38B8
void func_80AD3A24(void); // func_80AD3A24
void func_80AD3AE4(void); // func_80AD3AE4
void func_80AD3B6C(void); // func_80AD3B6C
void func_80AD3BE4(void); // func_80AD3BE4
void func_80AD3C94(void); // func_80AD3C94
void func_80AD3CEC(void); // func_80AD3CEC
void func_80AD3DA4(void); // func_80AD3DA4
void func_80AD3E34(void); // func_80AD3E34
void func_80AD3EF0(void); // func_80AD3EF0
void func_80AD3FF4(void); // func_80AD3FF4
void func_80AD40AC(void); // func_80AD40AC
void func_80AD4110(void); // func_80AD4110
void func_80AD417C(void); // func_80AD417C
void func_80AD4298(void); // func_80AD4298
void func_80AD431C(void); // func_80AD431C
void func_80AD434C(void); // func_80AD434C
void func_80AD4550(void); // func_80AD4550
void func_80AD4608(void); // func_80AD4608
void func_80AD469C(void); // func_80AD469C
void func_80AD46F8(void); // func_80AD46F8
void func_80AD475C(void); // func_80AD475C
void func_80AD48F8(void); // func_80AD48F8
void func_80AD49B8(void); // func_80AD49B8
void func_80AD4A78(void); // func_80AD4A78
void func_80AD4B08(void); // func_80AD4B08
void func_80AD4B4C(void); // func_80AD4B4C
void func_80AD4C4C(void); // func_80AD4C4C
void func_80AD4CCC(void); // func_80AD4CCC
void func_80AD4DB4(void); // func_80AD4DB4
void func_80AD4FE4(void); // func_80AD4FE4
void func_80AD508C(void); // func_80AD508C
void func_80AD5110(void); // func_80AD5110
void func_80AD5150(void); // func_80AD5150
void func_80AD5234(void); // func_80AD5234
void func_80AD5394(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AD5394
void func_80AD54C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AD54C8
void func_80AD5584(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AD5584
void func_80AD566C(void); // func_80AD566C
void func_80AD56E8(void); // func_80AD56E8
void func_80AD5BB0(void); // func_80AD5BB0
void func_80AD5BE8(void); // func_80AD5BE8
void func_80AD5C70(void); // func_80AD5C70
void func_80AD5DFC(void); // func_80AD5DFC
void func_80AD5EB8(void); // func_80AD5EB8
void func_80AD5F70(void); // func_80AD5F70
void func_80AD5FB0(void); // func_80AD5FB0
void func_80AD61EC(void); // func_80AD61EC
void func_80AD6314(void); // func_80AD6314
void func_80AD6348(void); // func_80AD6348
void func_80AD635C(void); // func_80AD635C
void func_80AD63D4(void); // func_80AD63D4
void func_80AD63E8(void); // func_80AD63E8
void func_80AD63F8(void); // func_80AD63F8
void func_80AD642C(void); // func_80AD642C
void func_80AD6480(void); // func_80AD6480
void func_80AD64A4(void); // func_80AD64A4
void func_80AD64B4(void); // func_80AD64B4
void func_80AD64D8(void); // func_80AD64D8
void func_80AD6508(void); // func_80AD6508
void func_80AD6760(void); // func_80AD6760
void func_80AD67FC(void); // func_80AD67FC
void func_80AD6830(void); // func_80AD6830
void func_80AD68DC(void); // func_80AD68DC
void func_80AD6A88(void); // func_80AD6A88
void func_80AD6B68(void); // func_80AD6B68
void func_80AD6C5C(void); // func_80AD6C5C
void func_80AD6CBC(void); // func_80AD6CBC
void func_80AD6DD0(void); // func_80AD6DD0
void func_80AD6F08(void); // func_80AD6F08
void func_80AD6F34(void); // func_80AD6F34
void func_80AD6F9C(void); // func_80AD6F9C
void func_80AD7018(void); // func_80AD7018
void func_80AD70A0(void); // func_80AD70A0
void func_80AD70EC(void); // func_80AD70EC
void func_80AD71B4(void); // func_80AD71B4
void func_80AD7254(void); // func_80AD7254
void func_80AD73A8(void); // func_80AD73A8
void func_80AD7424(void); // func_80AD7424
void func_80AD7568(void); // func_80AD7568
void func_80AD75A8(void); // func_80AD75A8
void func_80AD76CC(void); // func_80AD76CC
void func_80AD7798(void); // func_80AD7798
void func_80AD792C(void); // func_80AD792C
void func_80AD7948(void); // func_80AD7948
void func_80AD7B18(void); // func_80AD7B18
void func_80AD7B90(void); // func_80AD7B90
void func_80AD7C54(void); // func_80AD7C54
void func_80AD7D40(void); // func_80AD7D40
void func_80AD7DA4(void); // func_80AD7DA4
void func_80AD7E0C(void); // func_80AD7E0C
void func_80AD7EC0(void); // func_80AD7EC0
void func_80AD7F10(void); // func_80AD7F10
void func_80AD7FA4(void); // func_80AD7FA4
void func_80AD7FF8(void); // func_80AD7FF8
void func_80AD8060(void); // func_80AD8060
void func_80AD810C(void); // func_80AD810C
void func_80AD8148(void); // func_80AD8148
void func_80AD825C(void); // func_80AD825C
void func_80AD8364(void); // func_80AD8364
void func_80AD8388(void); // func_80AD8388
void func_80AD84C0(void); // func_80AD84C0
void func_80AD881C(void); // func_80AD881C
void func_80AD8A48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AD8A48
void func_80AD8AF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AD8AF8
void func_80AD8BC0(void); // func_80AD8BC0
void func_80AD8CEC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AD8CEC
void func_80AD8D64(void); // func_80AD8D64
void func_80AD9240(void); // func_80AD9240
void func_80AD92FC(void); // func_80AD92FC
void func_80AD9358(void); // func_80AD9358
void func_80AD9488(void); // func_80AD9488
void func_80AD97DC(void); // func_80AD97DC
void func_80AD9A6C(void); // func_80AD9A6C
void func_80AD9B04(void); // func_80AD9B04
void func_80AD9F90(void); // func_80AD9F90
void func_80AD9FF8(void); // func_80AD9FF8
void func_80ADAAF0(void); // func_80ADAAF0
void func_80ADAB70(void); // func_80ADAB70
void func_80ADABA4(void); // func_80ADABA4
void func_80ADABF8(void); // func_80ADABF8
void func_80ADACDC(void); // func_80ADACDC
void func_80ADADD0(void); // func_80ADADD0
void func_80ADAE64(void); // func_80ADAE64
void func_80ADAFC0(void); // func_80ADAFC0
void func_80ADB040(void); // func_80ADB040
void func_80ADB08C(void); // func_80ADB08C
void func_80ADB0D8(void); // func_80ADB0D8
void func_80ADB254(void); // func_80ADB254
void func_80ADB4F4(void); // func_80ADB4F4
void func_80ADB544(void); // func_80ADB544
void func_80ADB924(void); // func_80ADB924
void func_80ADBAB8(void); // func_80ADBAB8
void func_80ADBBEC(void); // func_80ADBBEC
void func_80ADBC60(void); // func_80ADBC60
void func_80ADBCE4(void); // func_80ADBCE4
void func_80ADBD64(void); // func_80ADBD64
void func_80ADBE80(void); // func_80ADBE80
void func_80ADBFA0(void); // func_80ADBFA0
void func_80ADC034(void); // func_80ADC034
void func_80ADC118(void); // func_80ADC118
void func_80ADC2CC(void); // func_80ADC2CC
void func_80ADC37C(void); // func_80ADC37C
void func_80ADC580(void); // func_80ADC580
void func_80ADC5A4(void); // func_80ADC5A4
void func_80ADC6D0(void); // func_80ADC6D0
void func_80ADC7B4(void); // func_80ADC7B4
void func_80ADC8C4(void); // func_80ADC8C4
void func_80ADCA64(void); // func_80ADCA64
void func_80ADCC04(void); // func_80ADCC04
void func_80ADCD3C(void); // func_80ADCD3C
void func_80ADCE4C(void); // func_80ADCE4C
void func_80ADCFE8(void); // func_80ADCFE8
void func_80ADD0A8(void); // func_80ADD0A8
void func_80ADD3D4(void); // func_80ADD3D4
void func_80ADD400(void); // func_80ADD400
void func_80ADD4E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80ADD4E0
void func_80ADD7B4(void); // func_80ADD7B4
void func_80ADD7CC(void); // func_80ADD7CC
void func_80ADD8A4(void); // func_80ADD8A4
void func_80ADE230(void); // func_80ADE230
void func_80ADE5A4(void); // func_80ADE5A4
void func_80ADE664(void); // func_80ADE664
void func_80ADE6AC(void); // func_80ADE6AC
void func_80ADE6C0(void); // func_80ADE6C0
void func_80ADE734(void); // func_80ADE734
void func_80ADE748(void); // func_80ADE748
void func_80ADE7E0(void); // func_80ADE7E0
void func_80ADE7F4(void); // func_80ADE7F4
void func_80ADE850(void); // func_80ADE850
void func_80ADE874(void); // func_80ADE874
void func_80ADEA70(void); // func_80ADEA70
void func_80ADEAC0(void); // func_80ADEAC0
void func_80ADEAF4(void); // func_80ADEAF4
void func_80ADEB90(void); // func_80ADEB90
void func_80ADED34(void); // func_80ADED34
void func_80ADED8C(void); // func_80ADED8C
void func_80ADEDF8(void); // func_80ADEDF8
void func_80ADEE4C(void); // func_80ADEE4C
void func_80ADEF74(void); // func_80ADEF74
void func_80ADF03C(void); // func_80ADF03C
void func_80ADF050(void); // func_80ADF050
void func_80ADF2D4(void); // func_80ADF2D4
void func_80ADF338(void); // func_80ADF338
void func_80ADF4E0(void); // func_80ADF4E0
void func_80ADF520(void); // func_80ADF520
void func_80ADF608(void); // func_80ADF608
void func_80ADF654(void); // func_80ADF654
void func_80ADF6DC(void); // func_80ADF6DC
void func_80ADF730(void); // func_80ADF730
void func_80ADF7B8(void); // func_80ADF7B8
void func_80ADF7CC(void); // func_80ADF7CC
void func_80ADF8DC(void); // func_80ADF8DC
void func_80ADF94C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80ADF94C
void func_80ADF984(void); // func_80ADF984
void func_80ADF9E0(void); // func_80ADF9E0
void func_80ADFCA0(void); // func_80ADFCA0
void func_80ADFCEC(void); // func_80ADFCEC
void func_80ADFE3C(void); // func_80ADFE3C
void func_80ADFF58(void); // func_80ADFF58
void func_80ADFF84(UNK_TYPE4 param_1, s32 param_2); // func_80ADFF84
void func_80AE0010(void); // func_80AE0010
void func_80AE0304(void); // func_80AE0304
void func_80AE0418(void); // func_80AE0418
void func_80AE0460(void); // func_80AE0460
void func_80AE04C4(void); // func_80AE04C4
void func_80AE04FC(void); // func_80AE04FC
void func_80AE0698(void); // func_80AE0698
void func_80AE0704(void); // func_80AE0704
void func_80AE0C88(void); // func_80AE0C88
void func_80AE0D10(void); // func_80AE0D10
void func_80AE0D78(void); // func_80AE0D78
void func_80AE0DDC(void); // func_80AE0DDC
void func_80AE0F84(void); // func_80AE0F84
void func_80AE0FA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AE0FA8
void func_80AE1024(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AE1024
void func_80AE1080(void); // func_80AE1080
void func_80AE1650(void); // func_80AE1650
void func_80AE16A0(void); // func_80AE16A0
void func_80AE16D8(void); // func_80AE16D8
void func_80AE1760(void); // func_80AE1760
void func_80AE17D0(void); // func_80AE17D0
void func_80AE17F4(void); // func_80AE17F4
void func_80AE1874(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AE1874
void func_80AE18B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AE18B4
void func_80AE19B8(void); // func_80AE19B8
void func_80AE1B70(void); // func_80AE1B70
void func_80AE1BF0(void); // func_80AE1BF0
void func_80AE1C54(void); // func_80AE1C54
void func_80AE1E58(void); // func_80AE1E58
void func_80AE1EF4(void); // func_80AE1EF4
void func_80AE1F5C(void); // func_80AE1F5C
void func_80AE2028(void); // func_80AE2028
void func_80AE2074(void); // func_80AE2074
void func_80AE21C8(void); // func_80AE21C8
void func_80AE2234(void); // func_80AE2234
void func_80AE2298(void); // func_80AE2298
void func_80AE2340(void); // func_80AE2340
void func_80AE2438(void); // func_80AE2438
void func_80AE2524(void); // func_80AE2524
void func_80AE25D4(void); // func_80AE25D4
void func_80AE2670(void); // func_80AE2670
void func_80AE26D4(void); // func_80AE26D4
void func_80AE2760(void); // func_80AE2760
void func_80AE28B0(void); // func_80AE28B0
void func_80AE2974(void); // func_80AE2974
void func_80AE2A98(void); // func_80AE2A98
void func_80AE2B44(void); // func_80AE2B44
void func_80AE2BE0(void); // func_80AE2BE0
void func_80AE2C6C(void); // func_80AE2C6C
void func_80AE2CFC(void); // func_80AE2CFC
void func_80AE2DC8(void); // func_80AE2DC8
void func_80AE2F78(void); // func_80AE2F78
void func_80AE30F8(void); // func_80AE30F8
void func_80AE32D4(void); // func_80AE32D4
void func_80AE3474(void); // func_80AE3474
void func_80AE352C(void); // func_80AE352C
void func_80AE3644(void); // func_80AE3644
void func_80AE3880(void); // func_80AE3880
void func_80AE38E0(void); // func_80AE38E0
void func_80AE3A68(void); // func_80AE3A68
void func_80AE3BC4(void); // func_80AE3BC4
void func_80AE3CF0(void); // func_80AE3CF0
void func_80AE3D50(void); // func_80AE3D50
void func_80AE3E4C(void); // func_80AE3E4C
void func_80AE3F40(void); // func_80AE3F40
void func_80AE4028(void); // func_80AE4028
void func_80AE4120(void); // func_80AE4120
void func_80AE41FC(void); // func_80AE41FC
void func_80AE4424(void); // func_80AE4424
void func_80AE44DC(void); // func_80AE44DC
void func_80AE45C4(void); // func_80AE45C4
void func_80AE4638(void); // func_80AE4638
void func_80AE4828(void); // func_80AE4828
void func_80AE4A1C(void); // func_80AE4A1C
void func_80AE4B20(void); // func_80AE4B20
void func_80AE4B70(void); // func_80AE4B70
void func_80AE4BF4(void); // func_80AE4BF4
void func_80AE4CD8(void); // func_80AE4CD8
void func_80AE4D28(void); // func_80AE4D28
void func_80AE4DB0(void); // func_80AE4DB0
void func_80AE4F10(void); // func_80AE4F10
void func_80AE4F3C(void); // func_80AE4F3C
void func_80AE502C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6); // func_80AE502C
void func_80AE52A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_80AE52A4
void func_80AE5440(void); // func_80AE5440
void func_80AE57E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AE57E8
void func_80AE5910(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AE5910
void func_80AE5990(void); // func_80AE5990
void func_80AE6130(void); // func_80AE6130
void func_80AE615C(void); // func_80AE615C
void func_80AE61C0(void); // func_80AE61C0
void func_80AE625C(void); // func_80AE625C
void func_80AE626C(void); // func_80AE626C
void func_80AE63A8(void); // func_80AE63A8
void func_80AE6488(void); // func_80AE6488
void func_80AE65F4(void); // func_80AE65F4
void func_80AE6704(void); // func_80AE6704
void func_80AE6880(void); // func_80AE6880
void func_80AE68F0(void); // func_80AE68F0
void func_80AE69E8(void); // func_80AE69E8
void func_80AE6A64(void); // func_80AE6A64
void func_80AE6B30(void); // func_80AE6B30
void func_80AE6C4C(void); // func_80AE6C4C
void func_80AE6C5C(void); // func_80AE6C5C
void func_80AE6CF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AE6CF0
void func_80AE6D40(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AE6D40
void func_80AE6D90(void); // func_80AE6D90
void func_80AE6E8C(void); // func_80AE6E8C
void D_80AE7258(void); // func_80AE7258
void func_80AE73A0(void); // func_80AE73A0
void func_80AE74E0(void); // func_80AE74E0
void func_80AE750C(void); // func_80AE750C
void func_80AE75C8(void); // func_80AE75C8
void func_80AE7718(void); // func_80AE7718
void func_80AE77D4(void); // func_80AE77D4
void func_80AE795C(void); // func_80AE795C
void func_80AE7E9C(void); // func_80AE7E9C
void func_80AE7F34(void); // func_80AE7F34
void func_80AE854C(void); // func_80AE854C
void func_80AE85C4(void); // func_80AE85C4
void func_80AE8680(void); // func_80AE8680
void func_80AE87A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AE87A4
void func_80AE87EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AE87EC
void func_80AE882C(void); // func_80AE882C
void func_80AE8B70(void); // func_80AE8B70
void func_80AE8DA4(void); // func_80AE8DA4
void func_80AE8DE4(void); // func_80AE8DE4
void func_80AE8FD4(void); // func_80AE8FD4
void func_80AE9090(void); // func_80AE9090
void func_80AE9180(void); // func_80AE9180
void func_80AE9258(void); // func_80AE9258
void func_80AE939C(void); // func_80AE939C
void func_80AE9574(void); // func_80AE9574
void func_80AE9780(void); // func_80AE9780
void func_80AE9A20(void); // func_80AE9A20
void func_80AE9A80(void); // func_80AE9A80
void func_80AE9AC4(void); // func_80AE9AC4
void func_80AE9B4C(void); // func_80AE9B4C
void func_80AE9B8C(void); // func_80AE9B8C
void func_80AE9BCC(void); // func_80AE9BCC
void func_80AE9CA8(void); // func_80AE9CA8
void func_80AE9EEC(void); // func_80AE9EEC
void func_80AE9F28(void); // func_80AE9F28
void func_80AE9F70(void); // func_80AE9F70
void func_80AE9FC8(void); // func_80AE9FC8
void func_80AEA044(void); // func_80AEA044
void func_80AEA0B4(void); // func_80AEA0B4
void func_80AEA128(void); // func_80AEA128
void func_80AEA1A0(void); // func_80AEA1A0
void func_80AEA66C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_80AEA66C
void func_80AEA7A4(void); // func_80AEA7A4
void func_80AEA910(void); // func_80AEA910
void func_80AEABF0(void); // func_80AEABF0
void func_80AEAC64(void); // func_80AEAC64
void func_80AEACF8(void); // func_80AEACF8
void func_80AEAEAC(void); // func_80AEAEAC
void func_80AEAF14(void); // func_80AEAF14
void func_80AEAF8C(void); // func_80AEAF8C
void func_80AEAFA0(void); // func_80AEAFA0
void func_80AEB114(void); // func_80AEB114
void func_80AEB148(void); // func_80AEB148
void func_80AEB1C8(void); // func_80AEB1C8
void func_80AEB230(void); // func_80AEB230
void func_80AEB280(void); // func_80AEB280
void func_80AEB294(void); // func_80AEB294
void func_80AEB3E0(void); // func_80AEB3E0
void func_80AEB428(void); // func_80AEB428
void func_80AEB584(void); // func_80AEB584
void func_80AEB598(void); // func_80AEB598
void func_80AEB684(void); // func_80AEB684
void func_80AEB698(void); // func_80AEB698
void func_80AEB828(void); // func_80AEB828
void func_80AEB8A4(void); // func_80AEB8A4
void func_80AEB934(void); // func_80AEB934
void func_80AEB974(void); // func_80AEB974
void func_80AEB9E0(void); // func_80AEB9E0
void func_80AEBB30(void); // func_80AEBB30
void func_80AEBB74(void); // func_80AEBB74
void func_80AEBC18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AEBC18
void func_80AEBC90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AEBC90
void func_80AEBCD0(void); // func_80AEBCD0
void func_80AEC460(void); // func_80AEC460
void func_80AEC524(void); // func_80AEC524
void func_80AEC658(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AEC658
void func_80AEC750(void); // func_80AEC750
void func_80AECA10(void); // func_80AECA10
void func_80AECA3C(void); // func_80AECA3C
void func_80AECA90(void); // func_80AECA90
void func_80AECB0C(void); // func_80AECB0C
void func_80AECB6C(void); // func_80AECB6C
void func_80AECE0C(void); // func_80AECE0C
void func_80AECE60(void); // func_80AECE60
void func_80AED354(void); // func_80AED354
void func_80AED38C(void); // func_80AED38C
void func_80AED4F8(void); // func_80AED4F8
void func_80AED544(void); // func_80AED544
void func_80AED610(void); // func_80AED610
void func_80AED898(void); // func_80AED898
void func_80AED940(void); // func_80AED940
void func_80AEDBEC(void); // func_80AEDBEC
void func_80AEDC4C(void); // func_80AEDC4C
void func_80AEDCBC(void); // func_80AEDCBC
void func_80AEDD4C(void); // func_80AEDD4C
void func_80AEDDA0(void); // func_80AEDDA0
void func_80AEDE10(void); // func_80AEDE10
void func_80AEDF5C(void); // func_80AEDF5C
void func_80AEE2A8(void); // func_80AEE2A8
void func_80AEE2C0(void); // func_80AEE2C0
void func_80AEE300(void); // func_80AEE300
void func_80AEE374(void); // func_80AEE374
void func_80AEE414(void); // func_80AEE414
void func_80AEE478(void); // func_80AEE478
void func_80AEE4D0(void); // func_80AEE4D0
void func_80AEE650(void); // func_80AEE650
void func_80AEE6B8(void); // func_80AEE6B8
void func_80AEE784(void); // func_80AEE784
void func_80AEE7E0(void); // func_80AEE7E0
void func_80AEE86C(void); // func_80AEE86C
void func_80AEE9B0(void); // func_80AEE9B0
void func_80AEEA4C(void); // func_80AEEA4C
void func_80AEEAD4(void); // func_80AEEAD4
void func_80AEEB88(void); // func_80AEEB88
void func_80AEED38(void); // func_80AEED38
void func_80AEF048(void); // func_80AEF048
void func_80AEF094(void); // func_80AEF094
void func_80AEF15C(void); // func_80AEF15C
void func_80AEF1B4(void); // func_80AEF1B4
void func_80AEF1C4(void); // func_80AEF1C4
void func_80AEF210(void); // func_80AEF210
void func_80AEF220(void); // func_80AEF220
void func_80AEF278(void); // func_80AEF278
void func_80AEF2C8(void); // func_80AEF2C8
void func_80AEF2D8(void); // func_80AEF2D8
void func_80AEF3E8(void); // func_80AEF3E8
void func_80AEF5F4(void); // func_80AEF5F4
void func_80AEF65C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AEF65C
void func_80AEF6A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AEF6A4
void func_80AEF734(void); // func_80AEF734
void func_80AF0060(void); // func_80AF0060
void func_80AF0088(void); // func_80AF0088
void func_80AF0170(void); // func_80AF0170
void func_80AF0360(void); // func_80AF0360
void func_80AF0394(void); // func_80AF0394
void func_80AF04BC(void); // func_80AF04BC
void func_80AF04D8(void); // func_80AF04D8
void func_80AF0514(void); // func_80AF0514
void func_80AF0530(void); // func_80AF0530
void func_80AF06CC(void); // func_80AF06CC
void func_80AF06F0(void); // func_80AF06F0
void func_80AF0820(void); // func_80AF0820
void func_80AF082C(void); // func_80AF082C
void func_80AF0838(void); // func_80AF0838
void func_80AF0984(void); // func_80AF0984
void func_80AF0C30(void); // func_80AF0C30
void func_80AF0CDC(void); // func_80AF0CDC
void func_80AF10D8(void); // func_80AF10D8
void func_80AF118C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80AF118C
void func_80AF14FC(void); // func_80AF14FC
void func_80AF1730(void); // func_80AF1730
void func_80AF175C(void); // func_80AF175C
void func_80AF1960(void); // func_80AF1960
void func_80AF19A8(void); // func_80AF19A8
void func_80AF1A2C(void); // func_80AF1A2C
void func_80AF1B68(void); // func_80AF1B68
void func_80AF1CA0(void); // func_80AF1CA0
void func_80AF1E44(void); // func_80AF1E44
void func_80AF1F48(void); // func_80AF1F48
void func_80AF2030(void); // func_80AF2030
void func_80AF21E8(void); // func_80AF21E8
void func_80AF2318(void); // func_80AF2318
void func_80AF2350(void); // func_80AF2350
void func_80AF24D8(void); // func_80AF24D8
void func_80AF2654(void); // func_80AF2654
void func_80AF2808(void); // func_80AF2808
void func_80AF2854(void); // func_80AF2854
void func_80AF2938(void); // func_80AF2938
void func_80AF29C0(void); // func_80AF29C0
void func_80AF2AE8(void); // func_80AF2AE8
void func_80AF2BAC(void); // func_80AF2BAC
void func_80AF2C48(void); // func_80AF2C48
void func_80AF2DB4(void); // func_80AF2DB4
void func_80AF2EC8(void); // func_80AF2EC8
void func_80AF2F98(void); // func_80AF2F98
void func_80AF30F4(void); // func_80AF30F4
void func_80AF3144(void); // func_80AF3144
void func_80AF31D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AF31D0
void func_80AF3248(void); // func_80AF3248
void func_80AF3910(void); // func_80AF3910
void func_80AF397C(void); // func_80AF397C
void func_80AF3A80(void); // func_80AF3A80
void func_80AF3AC8(void); // func_80AF3AC8
void func_80AF3ADC(void); // func_80AF3ADC
void func_80AF3B8C(void); // func_80AF3B8C
void func_80AF3BA0(void); // func_80AF3BA0
void func_80AF3C18(void); // func_80AF3C18
void func_80AF3C34(void); // func_80AF3C34
void func_80AF3CC0(void); // func_80AF3CC0
void func_80AF3CE4(void); // func_80AF3CE4
void func_80AF3F70(void); // func_80AF3F70
void func_80AF3FE0(void); // func_80AF3FE0
void func_80AF40B4(void); // func_80AF40B4
void func_80AF4200(void); // func_80AF4200
void func_80AF4248(void); // func_80AF4248
void func_80AF4320(void); // func_80AF4320
void func_80AF43F0(void); // func_80AF43F0
void func_80AF45DC(void); // func_80AF45DC
void func_80AF4608(void); // func_80AF4608
void func_80AF4670(void); // func_80AF4670
void func_80AF46F0(void); // func_80AF46F0
void func_80AF488C(void); // func_80AF488C
void func_80AF48D0(void); // func_80AF48D0
void func_80AF4964(void); // func_80AF4964
void func_80AF4A88(void); // func_80AF4A88
void func_80AF4C18(void); // func_80AF4C18
void func_80AF4C64(void); // func_80AF4C64
void func_80AF4ED0(void); // func_80AF4ED0
void func_80AF4F30(void); // func_80AF4F30
void func_80AF4F6C(void); // func_80AF4F6C
void func_80AF4FF8(void); // func_80AF4FF8
void func_80AF5130(void); // func_80AF5130
void func_80AF520C(void); // func_80AF520C
void func_80AF5650(void); // func_80AF5650
void func_80AF56A0(void); // func_80AF56A0
void func_80AF5820(void); // func_80AF5820
void func_80AF5E3C(void); // func_80AF5E3C
void func_80AF5F2C(void); // func_80AF5F2C
void func_80AF5FE4(void); // func_80AF5FE4
void func_80AF6094(void); // func_80AF6094
void func_80AF6760(void); // func_80AF6760
void func_80AF6828(void); // func_80AF6828
void func_80AF6854(void); // func_80AF6854
void func_80AF6944(void); // func_80AF6944
void func_80AF6958(void); // func_80AF6958
void func_80AF6994(void); // func_80AF6994
void func_80AF69A8(void); // func_80AF69A8
void func_80AF6A38(void); // func_80AF6A38
void func_80AF6A78(void); // func_80AF6A78
void func_80AF6B40(void); // func_80AF6B40
void func_80AF6B84(void); // func_80AF6B84
void func_80AF6BF8(void); // func_80AF6BF8
void func_80AF6DE0(void); // func_80AF6DE0
void func_80AF6E2C(void); // func_80AF6E2C
void func_80AF6EA8(void); // func_80AF6EA8
void func_80AF6FF0(void); // func_80AF6FF0
void func_80AF7024(void); // func_80AF7024
void func_80AF705C(void); // func_80AF705C
void func_80AF70FC(void); // func_80AF70FC
void func_80AF71FC(void); // func_80AF71FC
void func_80AF72F8(void); // func_80AF72F8
void func_80AF7354(void); // func_80AF7354
void func_80AF746C(void); // func_80AF746C
void func_80AF74CC(void); // func_80AF74CC
void func_80AF7640(void); // func_80AF7640
void func_80AF76C4(void); // func_80AF76C4
void func_80AF76F0(void); // func_80AF76F0
void func_80AF798C(void); // func_80AF798C
void func_80AF79B0(void); // func_80AF79B0
void func_80AF7B40(void); // func_80AF7B40
void func_80AF7BAC(void); // func_80AF7BAC
void func_80AF7CB0(void); // func_80AF7CB0
void func_80AF7D60(void); // func_80AF7D60
void func_80AF7DC4(void); // func_80AF7DC4
void func_80AF7E6C(void); // func_80AF7E6C
void func_80AF7E98(void); // func_80AF7E98
void func_80AF7F68(void); // func_80AF7F68
void func_80AF8040(void); // func_80AF8040
void func_80AF80F4(void); // func_80AF80F4
void func_80AF8170(void); // func_80AF8170
void func_80AF81E8(void); // func_80AF81E8
void func_80AF8348(void); // func_80AF8348
void func_80AF8478(void); // func_80AF8478
void func_80AF8540(void); // func_80AF8540
void func_80AF86F0(void); // func_80AF86F0
void func_80AF87C4(void); // func_80AF87C4
void func_80AF8890(void); // func_80AF8890
void func_80AF898C(void); // func_80AF898C
void func_80AF8AC8(void); // func_80AF8AC8
void func_80AF8BA8(void); // func_80AF8BA8
void func_80AF8C68(void); // func_80AF8C68
void func_80AF8D84(void); // func_80AF8D84
void func_80AF8DD4(void); // func_80AF8DD4
void func_80AF8ED4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80AF8ED4
void func_80AF9008(void); // func_80AF9008
void func_80AF91E8(void); // func_80AF91E8
void func_80AF94AC(void); // func_80AF94AC
void func_80AF95E8(void); // func_80AF95E8
void func_80AF98A0(void); // func_80AF98A0
void func_80AF992C(void); // func_80AF992C
void func_80AF9A0C(void); // func_80AF9A0C
void func_80AF9AB0(void); // func_80AF9AB0
void func_80AF9B54(void); // func_80AF9B54
void func_80AF9BF8(void); // func_80AF9BF8
void func_80AF9D04(void); // func_80AF9D04
void func_80AF9E7C(void); // func_80AF9E7C
void func_80AFA170(void); // func_80AFA170
void func_80AFA334(void); // func_80AFA334
void func_80AFA438(void); // func_80AFA438
void func_80AFA4D0(void); // func_80AFA4D0
void func_80AFA5FC(void); // func_80AFA5FC
void func_80AFA724(void); // func_80AFA724
void func_80AFA7A8(void); // func_80AFA7A8
void func_80AFA8B0(void); // func_80AFA8B0
void func_80AFA8F0(void); // func_80AFA8F0
void func_80AFAA04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80AFAA04
void func_80AFAA44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80AFAA44
void func_80AFABAC(void); // func_80AFABAC
void func_80AFACAC(void); // func_80AFACAC
void func_80AFC960(void); // func_80AFC960
void func_80AFCA94(void); // func_80AFCA94
void func_80AFCB64(void); // func_80AFCB64
void func_80AFCB94(void); // func_80AFCB94
void func_80AFCBD4(void); // func_80AFCBD4
void func_80AFCC14(void); // func_80AFCC14
void func_80AFCC24(void); // func_80AFCC24
void func_80AFCC58(void); // func_80AFCC58
void func_80AFCD44(void); // func_80AFCD44
void func_80AFCDC8(void); // func_80AFCDC8
void func_80AFCE70(void); // func_80AFCE70
void func_80AFCE94(void); // func_80AFCE94
void func_80AFD380(void); // func_80AFD380
void func_80AFD4B8(void); // func_80AFD4B8
void func_80AFD5A4(void); // func_80AFD5A4
void func_80AFD5B4(void); // func_80AFD5B4
void func_80AFD5E0(void); // func_80AFD5E0
void func_80AFD668(void); // func_80AFD668
void func_80AFD770(void); // func_80AFD770
void func_80AFD7DC(void); // func_80AFD7DC
void func_80AFD990(void); // func_80AFD990
void func_80AFDAC8(void); // func_80AFDAC8
void func_80AFDB28(void); // func_80AFDB28
void func_80AFDB38(void); // func_80AFDB38
void func_80AFDB48(void); // func_80AFDB48
void func_80AFDC40(void); // func_80AFDC40
void func_80AFDD34(void); // func_80AFDD34
void func_80AFDD60(void); // func_80AFDD60
void func_80AFDE00(void); // func_80AFDE00
void func_80AFDF00(void); // func_80AFDF00
void func_80AFDF60(void); // func_80AFDF60
void func_80AFDFB4(void); // func_80AFDFB4
void func_80AFE234(void); // func_80AFE234
void func_80AFE25C(void); // func_80AFE25C
void func_80AFE370(void); // func_80AFE370
void func_80AFE414(void); // func_80AFE414
void func_80AFE4AC(void); // func_80AFE4AC
void func_80AFE584(void); // func_80AFE584
void func_80AFE650(void); // func_80AFE650
void func_80AFE8A0(void); // func_80AFE8A0
void func_80AFEB0C(void); // func_80AFEB0C
void func_80AFEB38(void); // func_80AFEB38
void func_80AFEB7C(void); // func_80AFEB7C
void func_80AFEC08(void); // func_80AFEC08
void func_80AFEC4C(void); // func_80AFEC4C
void func_80AFED08(void); // func_80AFED08
void func_80AFED7C(void); // func_80AFED7C
void func_80AFEFD4(void); // func_80AFEFD4
void func_80AFF030(void); // func_80AFF030
void func_80AFF22C(void); // func_80AFF22C
void func_80AFF288(void); // func_80AFF288
void func_80AFF330(void); // func_80AFF330
void func_80AFF378(void); // func_80AFF378
void func_80AFF45C(void); // func_80AFF45C
void func_80AFF4AC(void); // func_80AFF4AC
void func_80AFF618(void); // func_80AFF618
void func_80AFF6A0(void); // func_80AFF6A0
void func_80AFF700(void); // func_80AFF700
void func_80AFF76C(void); // func_80AFF76C
void func_80AFF880(void); // func_80AFF880
void func_80AFF8E4(void); // func_80AFF8E4
void func_80AFF9CC(void); // func_80AFF9CC
void func_80AFFA68(void); // func_80AFFA68
void func_80AFFAB0(void); // func_80AFFAB0
void func_80AFFC10(void); // func_80AFFC10
void func_80AFFC9C(void); // func_80AFFC9C
void func_80AFFD3C(void); // func_80AFFD3C
void func_80AFFE3C(void); // func_80AFFE3C
void func_80AFFE94(void); // func_80AFFE94
void func_80AFFFA4(void); // func_80AFFFA4
void func_80AFFFBC(void); // func_80AFFFBC
void func_80B000FC(void); // func_80B000FC
void func_80B00158(void); // func_80B00158
void func_80B00384(void); // func_80B00384
void func_80B0040C(void); // func_80B0040C
void func_80B00484(void); // func_80B00484
void func_80B004D0(void); // func_80B004D0
void func_80B005EC(void); // func_80B005EC
void func_80B00760(void); // func_80B00760
void func_80B008BC(void); // func_80B008BC
void func_80B008FC(void); // func_80B008FC
void func_80B0094C(void); // func_80B0094C
void func_80B00B8C(void); // func_80B00B8C
void func_80B00C94(void); // func_80B00C94
void func_80B00D9C(void); // func_80B00D9C
void func_80B00E48(void); // func_80B00E48
UNK_TYPE4 func_80B00F08(UNK_TYPE4 param_1, s32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, s32 param_5, s32 param_6); // func_80B00F08
void func_80B00F64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B00F64
void func_80B01040(void); // func_80B01040
void func_80B01990(void); // func_80B01990
void func_80B01A74(void); // func_80B01A74
void func_80B01B30(void); // func_80B01B30
void func_80B01E74(void); // func_80B01E74
void func_80B01E84(void); // func_80B01E84
void func_80B01EE8(void); // func_80B01EE8
void func_80B020A0(void); // func_80B020A0
void func_80B0211C(void); // func_80B0211C
void func_80B02234(void); // func_80B02234
void func_80B02354(void); // func_80B02354
void func_80B023D0(void); // func_80B023D0
void func_80B024AC(void); // func_80B024AC
void func_80B024D8(void); // func_80B024D8
void func_80B025CC(void); // func_80B025CC
void func_80B02688(void); // func_80B02688
void func_80B026C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B026C4
void func_80B026FC(void); // func_80B026FC
void func_80B02CD0(void); // func_80B02CD0
void func_80B02D58(void); // func_80B02D58
void func_80B02DB0(void); // func_80B02DB0
void func_80B02E54(void); // func_80B02E54
void func_80B02EE4(void); // func_80B02EE4
void func_80B030F8(void); // func_80B030F8
void func_80B03688(void); // func_80B03688
void func_80B03A80(void); // func_80B03A80
void func_80B03E2C(void); // func_80B03E2C
void func_80B03FF8(void); // func_80B03FF8
void func_80B04084(void); // func_80B04084
void func_80B0430C(void); // func_80B0430C
void func_80B04338(void); // func_80B04338
void func_80B04350(void); // func_80B04350
void func_80B04540(void); // func_80B04540
void func_80B0457C(void); // func_80B0457C
void func_80B04608(void); // func_80B04608
void func_80B04648(void); // func_80B04648
void func_80B046E4(void); // func_80B046E4
void func_80B047C0(void); // func_80B047C0
void func_80B04B48(void); // func_80B04B48
void func_80B04B60(void); // func_80B04B60
void func_80B04B70(void); // func_80B04B70
void func_80B04D04(void); // func_80B04D04
void func_80B04D34(void); // func_80B04D34
void func_80B05290(void); // func_80B05290
void func_80B05690(void); // func_80B05690
void func_80B0573C(void); // func_80B0573C
void func_80B057A4(void); // func_80B057A4
void func_80B058C0(void); // func_80B058C0
void func_80B05A64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80B05A64
void func_80B05B04(void); // func_80B05B04
void func_80B05CBC(void); // func_80B05CBC
void func_80B05D4C(void); // func_80B05D4C
void func_80B05EE0(void); // func_80B05EE0
void func_80B0607C(void); // func_80B0607C
void func_80B06558(void); // func_80B06558
void func_80B06600(void); // func_80B06600
void func_80B0696C(void); // func_80B0696C
void func_80B06B20(void); // func_80B06B20
void func_80B06C08(void); // func_80B06C08
void func_80B06D38(void); // func_80B06D38
void func_80B06F48(void); // func_80B06F48
void func_80B0728C(void); // func_80B0728C
void func_80B07450(void); // func_80B07450
void func_80B07700(void); // func_80B07700
void func_80B0791C(void); // func_80B0791C
void func_80B07B88(void); // func_80B07B88
void func_80B07BFC(void); // func_80B07BFC
void func_80B07DA4(void); // func_80B07DA4
void func_80B07EEC(void); // func_80B07EEC
void func_80B08018(void); // func_80B08018
void func_80B08124(void); // func_80B08124
void func_80B0813C(void); // func_80B0813C
void func_80B0825C(void); // func_80B0825C
void func_80B082AC(void); // func_80B082AC
void func_80B08550(void); // func_80B08550
void func_80B0863C(void); // func_80B0863C
void func_80B08848(void); // func_80B08848
void func_80B08960(void); // func_80B08960
void func_80B08C1C(void); // func_80B08C1C
void func_80B08CB8(void); // func_80B08CB8
void func_80B09178(void); // func_80B09178
void func_80B091D8(void); // func_80B091D8
void func_80B093C0(void); // func_80B093C0
void func_80B094E0(void); // func_80B094E0
void func_80B09840(void); // func_80B09840
void func_80B098BC(void); // func_80B098BC
void func_80B09A94(void); // func_80B09A94
void func_80B09C78(void); // func_80B09C78
void func_80B09DFC(void); // func_80B09DFC
void func_80B09E20(void); // func_80B09E20
void func_80B09E84(void); // func_80B09E84
void func_80B09EDC(void); // func_80B09EDC
void func_80B09F7C(void); // func_80B09F7C
void func_80B0A2A4(void); // func_80B0A2A4
void func_80B0A5EC(void); // func_80B0A5EC
void func_80B0A638(void); // func_80B0A638
void func_80B0A87C(void); // func_80B0A87C
void func_80B0A8C4(void); // func_80B0A8C4
void func_80B0AC30(void); // func_80B0AC30
void func_80B0ADFC(void); // func_80B0ADFC
void func_80B0B238(void); // func_80B0B238
void func_80B0B34C(void); // func_80B0B34C
void func_80B0B3F4(void); // func_80B0B3F4
void func_80B0B548(void); // func_80B0B548
void func_80B0B660(void); // func_80B0B660
void func_80B0BAE0(void); // func_80B0BAE0
void func_80B0C000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B0C000
void func_80B0C1BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B0C1BC
void func_80B0C398(void); // func_80B0C398
void func_80B0C570(void); // func_80B0C570
void func_80B0C7B0(void); // func_80B0C7B0
void func_80B0CAF0(void); // func_80B0CAF0
void func_80B0CCD8(void); // func_80B0CCD8
void func_80B0CF24(void); // func_80B0CF24
void func_80B0D0D4(void); // func_80B0D0D4
void func_80B0D2B8(void); // func_80B0D2B8
void func_80B0D69C(void); // func_80B0D69C
void func_80B0D750(void); // func_80B0D750
void func_80B0D9CC(void); // func_80B0D9CC
void func_80B0DFA8(void); // func_80B0DFA8
void func_80B0E548(void); // func_80B0E548
void func_80B0E5A4(void); // func_80B0E5A4
void func_80B0F5E0(void); // func_80B0F5E0
void func_80B0F660(void); // func_80B0F660
void func_80B0F6DC(void); // func_80B0F6DC
void func_80B0F728(void); // func_80B0F728
void func_80B0F7FC(void); // func_80B0F7FC
void func_80B0F8F8(void); // func_80B0F8F8
void func_80B0F97C(void); // func_80B0F97C
void func_80B0FA04(void); // func_80B0FA04
void func_80B0FA48(void); // func_80B0FA48
void func_80B0FB24(void); // func_80B0FB24
void func_80B0FBF0(void); // func_80B0FBF0
void func_80B0FD8C(void); // func_80B0FD8C
void func_80B0FE18(void); // func_80B0FE18
void func_80B0FE7C(void); // func_80B0FE7C
void func_80B0FEBC(void); // func_80B0FEBC
void func_80B0FFA8(void); // func_80B0FFA8
void func_80B10240(void); // func_80B10240
void func_80B10344(void); // func_80B10344
void func_80B10584(void); // func_80B10584
void func_80B10634(void); // func_80B10634
void func_80B10868(void); // func_80B10868
void func_80B10924(void); // func_80B10924
void func_80B109DC(void); // func_80B109DC
void func_80B10A48(void); // func_80B10A48
void func_80B10B5C(void); // func_80B10B5C
void func_80B10DAC(void); // func_80B10DAC
void func_80B10E98(void); // func_80B10E98
void func_80B11048(void); // func_80B11048
void func_80B110F8(void); // func_80B110F8
void func_80B111AC(void); // func_80B111AC
void func_80B11268(void); // func_80B11268
void func_80B11344(void); // func_80B11344
void func_80B1137C(void); // func_80B1137C
void func_80B116E4(void); // func_80B116E4
void func_80B11710(void); // func_80B11710
void func_80B1179C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B1179C
void func_80B117FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B117FC
void func_80B11858(void); // func_80B11858
void func_80B11E60(void); // func_80B11E60
void func_80B11F18(void); // func_80B11F18
void func_80B11F44(void); // func_80B11F44
void func_80B11F78(void); // func_80B11F78
void func_80B1202C(void); // func_80B1202C
void func_80B1217C(void); // func_80B1217C
void func_80B121D8(void); // func_80B121D8
void func_80B122D8(void); // func_80B122D8
void func_80B12430(void); // func_80B12430
void func_80B1268C(void); // func_80B1268C
void func_80B12710(void); // func_80B12710
void func_80B12744(void); // func_80B12744
void func_80B12768(void); // func_80B12768
void func_80B12870(void); // func_80B12870
void func_80B12880(void); // func_80B12880
void func_80B12890(void); // func_80B12890
void func_80B12980(void); // func_80B12980
void func_80B12A1C(void); // func_80B12A1C
void func_80B12A50(void); // func_80B12A50
void func_80B12A88(void); // func_80B12A88
void func_80B12B38(void); // func_80B12B38
void func_80B12D78(void); // func_80B12D78
void func_80B12E7C(void); // func_80B12E7C
void func_80B13170(void); // func_80B13170
void func_80B13474(void); // func_80B13474
void func_80B13724(void); // func_80B13724
void func_80B13908(void); // func_80B13908
void func_80B1391C(void); // func_80B1391C
void func_80B1392C(void); // func_80B1392C
void func_80B13940(void); // func_80B13940
void func_80B139D8(void); // func_80B139D8
void func_80B139F4(void); // func_80B139F4
void func_80B13BB4(void); // func_80B13BB4
void func_80B13BD8(void); // func_80B13BD8
void func_80B13C08(void); // func_80B13C08
void func_80B13E40(void); // func_80B13E40
void func_80B14180(void); // func_80B14180
void func_80B1440C(void); // func_80B1440C
void func_80B1444C(void); // func_80B1444C
void func_80B14460(void); // func_80B14460
void func_80B14510(void); // func_80B14510
void func_80B14524(void); // func_80B14524
void func_80B14558(void); // func_80B14558
void func_80B1456C(void); // func_80B1456C
void func_80B145F4(void); // func_80B145F4
void func_80B14648(void); // func_80B14648
void func_80B149A8(void); // func_80B149A8
void func_80B149C0(void); // func_80B149C0
void func_80B14A24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B14A24
void func_80B14B6C(void); // func_80B14B6C
void func_80B14CF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE4 param_7); // func_80B14CF8
void func_80B14F4C(void); // func_80B14F4C
void func_80B1503C(void); // func_80B1503C
void func_80B15060(void); // func_80B15060
void func_80B151E0(void); // func_80B151E0
void func_80B15254(void); // func_80B15254
void func_80B15264(void); // func_80B15264
void func_80B15330(void); // func_80B15330
void func_80B1544C(void); // func_80B1544C
void func_80B154A0(void); // func_80B154A0
void func_80B15790(void); // func_80B15790
void func_80B157C4(void); // func_80B157C4
void func_80B157F8(void); // func_80B157F8
void func_80B15A04(void); // func_80B15A04
void func_80B15A4C(void); // func_80B15A4C
void func_80B15A68(void); // func_80B15A68
void func_80B15B1C(void); // func_80B15B1C
void func_80B15B74(void); // func_80B15B74
void func_80B15E0C(void); // func_80B15E0C
void func_80B15E78(void); // func_80B15E78
void func_80B15F3C(void); // func_80B15F3C
void func_80B15F88(void); // func_80B15F88
void func_80B1606C(void); // func_80B1606C
void func_80B160DC(void); // func_80B160DC
void func_80B16180(void); // func_80B16180
void func_80B161A0(void); // func_80B161A0
void func_80B16244(void); // func_80B16244
void func_80B162AC(void); // func_80B162AC
void func_80B163C4(void); // func_80B163C4
void func_80B16400(void); // func_80B16400
void func_80B16494(void); // func_80B16494
void func_80B16520(void); // func_80B16520
void func_80B165A0(void); // func_80B165A0
void func_80B165E0(void); // func_80B165E0
void func_80B16628(void); // func_80B16628
void func_80B16808(void); // func_80B16808
void func_80B16B00(void); // func_80B16B00
void func_80B16F94(void); // func_80B16F94
void func_80B16FC0(void); // func_80B16FC0
void func_80B17144(void); // func_80B17144
void func_80B173D0(void); // func_80B173D0
void func_80B1746C(void); // func_80B1746C
void func_80B177EC(void); // func_80B177EC
void func_80B178B8(void); // func_80B178B8
void func_80B179D0(void); // func_80B179D0
void func_80B17A58(void); // func_80B17A58
void func_80B17CE8(void); // func_80B17CE8
void func_80B17D78(void); // func_80B17D78
void func_80B17EB4(void); // func_80B17EB4
void func_80B17EFC(void); // func_80B17EFC
void func_80B17F4C(void); // func_80B17F4C
void func_80B17FE0(void); // func_80B17FE0
void func_80B180A4(void); // func_80B180A4
void func_80B18124(void); // func_80B18124
void func_80B18380(void); // func_80B18380
void func_80B183A4(void); // func_80B183A4
void func_80B183C4(void); // func_80B183C4
void func_80B1848C(void); // func_80B1848C
void func_80B18600(void); // func_80B18600
void func_80B1861C(void); // func_80B1861C
void func_80B18908(void); // func_80B18908
void func_80B189C4(void); // func_80B189C4
void func_80B189D4(void); // func_80B189D4
void func_80B18A04(void); // func_80B18A04
void func_80B18A28(void); // func_80B18A28
void func_80B18B30(void); // func_80B18B30
void func_80B18BB4(void); // func_80B18BB4
void func_80B18C7C(void); // func_80B18C7C
void func_80B18F50(void); // func_80B18F50
void func_80B1918C(void); // func_80B1918C
void func_80B19474(void); // func_80B19474
void func_80B19718(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B19718
void func_80B198B0(void); // func_80B198B0
void func_80B19948(void); // func_80B19948
void func_80B19998(void); // func_80B19998
void func_80B19F60(void); // func_80B19F60
void func_80B1A008(void); // func_80B1A008
void func_80B1A15C(void); // func_80B1A15C
void func_80B1A17C(void); // func_80B1A17C
void func_80B1A18C(void); // func_80B1A18C
void func_80B1A1B0(void); // func_80B1A1B0
void func_80B1A3B0(void); // func_80B1A3B0
void func_80B1A600(void); // func_80B1A600
void func_80B1A648(void); // func_80B1A648
void func_80B1A768(void); // func_80B1A768
void func_80B1A894(void); // func_80B1A894
void func_80B1A9B0(void); // func_80B1A9B0
void func_80B1AA88(void); // func_80B1AA88
void func_80B1AAE8(void); // func_80B1AAE8
void func_80B1AB5C(void); // func_80B1AB5C
void func_80B1ABB8(void); // func_80B1ABB8
void func_80B1AC40(void); // func_80B1AC40
void func_80B1ACB8(void); // func_80B1ACB8
void func_80B1AE28(void); // func_80B1AE28
void func_80B1AE3C(void); // func_80B1AE3C
void func_80B1AF8C(void); // func_80B1AF8C
void func_80B1B020(void); // func_80B1B020
void func_80B1B0E0(void); // func_80B1B0E0
void func_80B1B168(void); // func_80B1B168
void func_80B1B280(void); // func_80B1B280
void func_80B1B2F0(void); // func_80B1B2F0
void func_80B1B3A8(void); // func_80B1B3A8
void func_80B1B444(void); // func_80B1B444
void func_80B1B5B4(void); // func_80B1B5B4
void func_80B1B628(void); // func_80B1B628
void func_80B1B70C(void); // func_80B1B70C
void func_80B1B7BC(void); // func_80B1B7BC
void func_80B1B860(void); // func_80B1B860
void func_80B1B940(void); // func_80B1B940
void func_80B1BA3C(void); // func_80B1BA3C
void func_80B1BA90(void); // func_80B1BA90
void func_80B1BC4C(void); // func_80B1BC4C
void func_80B1BCA0(void); // func_80B1BCA0
void func_80B1BCF0(void); // func_80B1BCF0
void func_80B1BE4C(void); // func_80B1BE4C
void func_80B1BF2C(void); // func_80B1BF2C
void func_80B1C030(void); // func_80B1C030
void func_80B1C0A4(void); // func_80B1C0A4
void func_80B1C2E8(void); // func_80B1C2E8
void func_80B1C340(void); // func_80B1C340
void func_80B1C408(void); // func_80B1C408
void func_80B1C61C(void); // func_80B1C61C
void func_80B1C974(void); // func_80B1C974
void func_80B1CB44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80B1CB44
void func_80B1CD34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B1CD34
void func_80B1D484(void); // func_80B1D484
void func_80B1DEB0(void); // func_80B1DEB0
void func_80B1E234(void); // func_80B1E234
void func_80B1E29C(void); // func_80B1E29C
void func_80B1E3D4(void); // func_80B1E3D4
void func_80B1E5A8(void); // func_80B1E5A8
void func_80B1E680(void); // func_80B1E680
void func_80B1E778(void); // func_80B1E778
void func_80B1E958(void); // func_80B1E958
void func_80B1E970(void); // func_80B1E970
void func_80B1EBD8(void); // func_80B1EBD8
void func_80B1EC24(void); // func_80B1EC24
void func_80B1EFFC(void); // func_80B1EFFC
void func_80B1F048(void); // func_80B1F048
void func_80B1F0A4(void); // func_80B1F0A4
void func_80B1F188(void); // func_80B1F188
void func_80B1F244(void); // func_80B1F244
void func_80B1F29C(void); // func_80B1F29C
void func_80B1F4A0(void); // func_80B1F4A0
void func_80B1F560(void); // func_80B1F560
void func_80B1F664(void); // func_80B1F664
void func_80B1F6B4(void); // func_80B1F6B4
void func_80B1F770(void); // func_80B1F770
void func_80B1F940(void); // func_80B1F940
void func_80B1FAD0(void); // func_80B1FAD0
void func_80B1FC7C(void); // func_80B1FC7C
void func_80B1FF20(void); // func_80B1FF20
void func_80B20030(void); // func_80B20030
void func_80B202B8(void); // func_80B202B8
void func_80B203BC(void); // func_80B203BC
void func_80B20668(void); // func_80B20668
void func_80B20B40(void); // func_80B20B40
void func_80B20E6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B20E6C
void func_80B20F70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B20F70
void func_80B21344(void); // func_80B21344
void func_80B21B00(void); // func_80B21B00
void func_80B21BB4(void); // func_80B21BB4
void func_80B21BE0(void); // func_80B21BE0
void func_80B21EA4(void); // func_80B21EA4
void func_80B21FFC(void); // func_80B21FFC
void func_80B22040(void); // func_80B22040
void func_80B220A8(void); // func_80B220A8
void func_80B221E8(void); // func_80B221E8
void func_80B222AC(void); // func_80B222AC
void func_80B2242C(void); // func_80B2242C
void func_80B224C0(void); // func_80B224C0
void func_80B22500(void); // func_80B22500
void func_80B226AC(void); // func_80B226AC
void func_80B22750(void); // func_80B22750
void func_80B2278C(void); // func_80B2278C
void func_80B228F4(void); // func_80B228F4
void func_80B229A4(void); // func_80B229A4
void func_80B22C00(void); // func_80B22C00
void func_80B22C2C(void); // func_80B22C2C
void func_80B22C80(void); // func_80B22C80
void func_80B22E0C(void); // func_80B22E0C
void func_80B22F34(void); // func_80B22F34
void func_80B22FA8(void); // func_80B22FA8
void func_80B23318(void); // func_80B23318
void func_80B23450(void); // func_80B23450
void func_80B234C8(void); // func_80B234C8
void func_80B235CC(void); // func_80B235CC
void func_80B236C8(void); // func_80B236C8
void func_80B23894(void); // func_80B23894
void func_80B238D4(void); // func_80B238D4
void func_80B23910(void); // func_80B23910
void func_80B23934(void); // func_80B23934
void func_80B239FC(void); // func_80B239FC
void func_80B23A38(void); // func_80B23A38
void func_80B23D50(void); // func_80B23D50
void func_80B23DD0(void); // func_80B23DD0
void func_80B23E10(void); // func_80B23E10
void func_80B23E30(void); // func_80B23E30
void func_80B23E40(void); // func_80B23E40
void func_80B23ED0(void); // func_80B23ED0
void func_80B23F50(void); // func_80B23F50
void func_80B23F60(void); // func_80B23F60
void func_80B243C0(void); // func_80B243C0
void func_80B24630(void); // func_80B24630
void func_80B246F4(void); // func_80B246F4
void func_80B2478C(void); // func_80B2478C
void func_80B248B8(void); // func_80B248B8
void func_80B24930(void); // func_80B24930
void func_80B24BE8(void); // func_80B24BE8
void func_80B24C14(void); // func_80B24C14
void func_80B24CB4(void); // func_80B24CB4
void func_80B24E14(void); // func_80B24E14
void func_80B24F08(void); // func_80B24F08
void func_80B251EC(void); // func_80B251EC
void func_80B252F8(void); // func_80B252F8
void func_80B2538C(void); // func_80B2538C
void func_80B25448(void); // func_80B25448
void func_80B25490(void); // func_80B25490
void func_80B255AC(void); // func_80B255AC
void func_80B256BC(void); // func_80B256BC
void func_80B25708(void); // func_80B25708
void func_80B2583C(void); // func_80B2583C
void func_80B258D8(void); // func_80B258D8
void func_80B25A74(void); // func_80B25A74
void func_80B25A90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B25A90
void func_80B25B14(void); // func_80B25B14
void func_80B262A0(void); // func_80B262A0
void func_80B264FC(void); // func_80B264FC
void func_80B26538(void); // func_80B26538
void func_80B2654C(void); // func_80B2654C
void func_80B26758(void); // func_80B26758
void func_80B269A4(void); // func_80B269A4
void func_80B26AE8(void); // func_80B26AE8
void func_80B26AFC(void); // func_80B26AFC
void func_80B26BF8(void); // func_80B26BF8
void func_80B26EB4(void); // func_80B26EB4
void func_80B26F14(void); // func_80B26F14
void func_80B26F6C(void); // func_80B26F6C
void func_80B2701C(void); // func_80B2701C
void func_80B27030(void); // func_80B27030
void func_80B2714C(void); // func_80B2714C
void func_80B27188(void); // func_80B27188
void func_80B273D0(void); // func_80B273D0
void func_80B2740C(void); // func_80B2740C
void func_80B274BC(void); // func_80B274BC
void func_80B276C4(void); // func_80B276C4
void func_80B276D8(void); // func_80B276D8
void func_80B27760(void); // func_80B27760
void func_80B27774(void); // func_80B27774
void func_80B2783C(void); // func_80B2783C
void func_80B27880(void); // func_80B27880
void func_80B278C4(void); // func_80B278C4
void func_80B279AC(void); // func_80B279AC
void func_80B279F0(void); // func_80B279F0
void func_80B27A90(void); // func_80B27A90
void func_80B27ACC(void); // func_80B27ACC
void func_80B27B54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B27B54
void func_80B27B8C(void); // func_80B27B8C
void func_80B27BA4(void); // func_80B27BA4
void func_80B28080(void); // func_80B28080
void func_80B28124(void); // func_80B28124
void func_80B2815C(void); // func_80B2815C
void func_80B2816C(void); // func_80B2816C
void func_80B28240(void); // func_80B28240
void func_80B28370(void); // func_80B28370
void func_80B28478(void); // func_80B28478
void func_80B28538(void); // func_80B28538
void func_80B287B8(void); // func_80B287B8
void func_80B287F4(void); // func_80B287F4
void func_80B288E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B288E8
void func_80B2899C(void); // func_80B2899C
void func_80B289DC(void); // func_80B289DC
void func_80B28B5C(void); // func_80B28B5C
void func_80B28C14(void); // func_80B28C14
void func_80B29128(void); // func_80B29128
void func_80B2913C(void); // func_80B2913C
void func_80B29194(void); // func_80B29194
void func_80B29250(void); // func_80B29250
void func_80B2938C(void); // func_80B2938C
void func_80B293C4(void); // func_80B293C4
void func_80B2951C(void); // func_80B2951C
void func_80B295A4(void); // func_80B295A4
void func_80B29778(void); // func_80B29778
void func_80B297FC(void); // func_80B297FC
void func_80B29E5C(void); // func_80B29E5C
void func_80B29EE4(void); // func_80B29EE4
void func_80B2A01C(void); // func_80B2A01C
void func_80B2A094(void); // func_80B2A094
void func_80B2A23C(void); // func_80B2A23C
void func_80B2A448(void); // func_80B2A448
void func_80B2A498(void); // func_80B2A498
void func_80B2A738(void); // func_80B2A738
void func_80B2ABF4(void); // func_80B2ABF4
void func_80B2AC20(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B2AC20
void func_80B2AD34(void); // func_80B2AD34
void func_80B2ADB0(void); // func_80B2ADB0
void func_80B2AF80(void); // func_80B2AF80
void func_80B2B180(void); // func_80B2B180
void func_80B2B830(void); // func_80B2B830
void func_80B2B874(void); // func_80B2B874
void func_80B2B8F4(void); // func_80B2B8F4
void func_80B2B974(void); // func_80B2B974
void func_80B2BAA4(void); // func_80B2BAA4
void func_80B2BBFC(void); // func_80B2BBFC
void func_80B2BCF8(void); // func_80B2BCF8
void func_80B2BD30(void); // func_80B2BD30
void func_80B2BD88(void); // func_80B2BD88
void func_80B2BD98(void); // func_80B2BD98
void func_80B2BE54(void); // func_80B2BE54
void func_80B2BF3C(void); // func_80B2BF3C
void func_80B2C04C(void); // func_80B2C04C
void func_80B2C078(void); // func_80B2C078
void func_80B2C11C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B2C11C
void func_80B2C18C(void); // func_80B2C18C
void func_80B2C6F0(void); // func_80B2C6F0
void func_80B2C8B8(void); // func_80B2C8B8
void func_80B2C910(void); // func_80B2C910
void func_80B2C9B8(void); // func_80B2C9B8
void func_80B2CA4C(void); // func_80B2CA4C
void func_80B2CAA4(void); // func_80B2CAA4
void func_80B2CB60(void); // func_80B2CB60
void func_80B2CBBC(void); // func_80B2CBBC
void func_80B2CD14(void); // func_80B2CD14
void func_80B2CD64(void); // func_80B2CD64
void func_80B2CEC8(void); // func_80B2CEC8
void func_80B2CF28(void); // func_80B2CF28
void func_80B2CFF8(void); // func_80B2CFF8
void func_80B2D07C(void); // func_80B2D07C
void func_80B2D0E8(void); // func_80B2D0E8
void func_80B2D140(void); // func_80B2D140
void func_80B2D2C0(void); // func_80B2D2C0
void func_80B2D300(void); // func_80B2D300
void func_80B2D5DC(void); // func_80B2D5DC
void func_80B2D628(void); // func_80B2D628
void func_80B2D694(void); // func_80B2D694
void func_80B2D6EC(void); // func_80B2D6EC
void func_80B2D76C(void); // func_80B2D76C
void func_80B2D7D4(void); // func_80B2D7D4
void func_80B2D924(void); // func_80B2D924
void func_80B2D980(void); // func_80B2D980
void func_80B2DAD0(void); // func_80B2DAD0
void func_80B2DB44(void); // func_80B2DB44
void func_80B2DC50(void); // func_80B2DC50
void func_80B2DD2C(void); // func_80B2DD2C
void func_80B2DDF8(void); // func_80B2DDF8
void func_80B2E0B0(void); // func_80B2E0B0
void func_80B2E180(void); // func_80B2E180
void func_80B2E1D8(void); // func_80B2E1D8
void func_80B2E230(void); // func_80B2E230
void func_80B2E3B0(void); // func_80B2E3B0
void func_80B2E3F8(void); // func_80B2E3F8
void func_80B2E438(void); // func_80B2E438
void func_80B2E55C(void); // func_80B2E55C
void func_80B2E6C0(void); // func_80B2E6C0
void func_80B2E8E0(void); // func_80B2E8E0
void func_80B2EACC(void); // func_80B2EACC
void func_80B2ED14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80B2ED14
void func_80B2EDD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B2EDD0
void func_80B2F0A4(void); // func_80B2F0A4
void func_80B2F328(void); // func_80B2F328
void func_80B2F37C(void); // func_80B2F37C
void func_80B2FB10(void); // func_80B2FB10
void func_80B2FB94(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B2FB94
void func_80B2FC98(void); // func_80B2FC98
void func_80B300F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B300F4
void func_80B30410(void); // func_80B30410
void func_80B30480(void); // func_80B30480
void func_80B3057C(void); // func_80B3057C
void func_80B30798(void); // func_80B30798
void func_80B307E0(void); // func_80B307E0
void func_80B30808(void); // func_80B30808
void func_80B30A2C(void); // func_80B30A2C
void func_80B30A4C(void); // func_80B30A4C
void func_80B30AD4(void); // func_80B30AD4
void func_80B30AF8(void); // func_80B30AF8
void func_80B30ED4(void); // func_80B30ED4
void func_80B30EF8(void); // func_80B30EF8
void func_80B31590(void); // func_80B31590
void func_80B3161C(void); // func_80B3161C
void func_80B31998(void); // func_80B31998
void func_80B319A8(void); // func_80B319A8
void func_80B319D0(void); // func_80B319D0
void func_80B31A34(void); // func_80B31A34
void func_80B31C40(void); // func_80B31C40
void func_80B31CB4(void); // func_80B31CB4
void func_80B31D14(void); // func_80B31D14
void func_80B31D64(void); // func_80B31D64
void func_80B31E00(void); // func_80B31E00
void func_80B32084(void); // func_80B32084
void func_80B32094(void); // func_80B32094
void func_80B320E0(void); // func_80B320E0
void func_80B321D0(void); // func_80B321D0
void func_80B32228(void); // func_80B32228
void func_80B322BC(void); // func_80B322BC
void func_80B32390(void); // func_80B32390
void func_80B324B0(void); // func_80B324B0
void func_80B32644(void); // func_80B32644
void func_80B326F4(void); // func_80B326F4
void func_80B32820(void); // func_80B32820
void func_80B32928(void); // func_80B32928
void func_80B32A88(void); // func_80B32A88
void func_80B32B10(void); // func_80B32B10
void func_80B32B3C(void); // func_80B32B3C
void func_80B32B70(void); // func_80B32B70
void func_80B32BB8(void); // func_80B32BB8
void func_80B32C34(void); // func_80B32C34
void func_80B32D08(void); // func_80B32D08
void func_80B32E74(void); // func_80B32E74
void func_80B32F04(void); // func_80B32F04
void func_80B331C8(void); // func_80B331C8
void func_80B3336C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B3336C
void func_80B333DC(void); // func_80B333DC
void func_80B33480(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B33480
void func_80B33818(void); // func_80B33818
void func_80B338C0(void); // func_80B338C0
void func_80B33D30(void); // func_80B33D30
void func_80B33E54(void); // func_80B33E54
void func_80B33E64(void); // func_80B33E64
void func_80B33E8C(void); // func_80B33E8C
void func_80B33EF0(void); // func_80B33EF0
void func_80B3403C(void); // func_80B3403C
void func_80B34078(void); // func_80B34078
void func_80B3415C(void); // func_80B3415C
void func_80B34314(void); // func_80B34314
void func_80B34574(void); // func_80B34574
void func_80B34598(void); // func_80B34598
void func_80B349A4(void); // func_80B349A4
UNK_TYPE4 func_80B349C8(UNK_TYPE4 param_1, s32 param_2, UNK_PTR param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, s32 param_6); // func_80B349C8
void func_80B34A00(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B34A00
void func_80B34A40(void); // func_80B34A40
void func_80B34F70(void); // func_80B34F70
void func_80B34FB4(void); // func_80B34FB4
void func_80B35108(void); // func_80B35108
void func_80B351A4(void); // func_80B351A4
void func_80B35250(void); // func_80B35250
void func_80B352A4(void); // func_80B352A4
void func_80B35450(void); // func_80B35450
void func_80B3556C(void); // func_80B3556C
void func_80B35634(void); // func_80B35634
void func_80B357F0(void); // func_80B357F0
void func_80B3584C(void); // func_80B3584C
void func_80B358D8(void); // func_80B358D8
void func_80B35968(void); // func_80B35968
void func_80B359DC(void); // func_80B359DC
void func_80B35B24(void); // func_80B35B24
void func_80B35B44(void); // func_80B35B44
void func_80B35C84(void); // func_80B35C84
void func_80B3610C(void); // func_80B3610C
void func_80B363E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B363E8
void func_80B364D4(void); // func_80B364D4
void func_80B364F8(void); // func_80B364F8
void func_80B36660(void); // func_80B36660
void func_80B36670(void); // func_80B36670
void func_80B368B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B368B0
void func_80B368F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B368F0
void func_80B36A34(void); // func_80B36A34
void func_80B37080(void); // func_80B37080
void func_80B37280(void); // func_80B37280
void func_80B372B8(void); // func_80B372B8
void func_80B372CC(void); // func_80B372CC
void func_80B37364(void); // func_80B37364
void func_80B3738C(void); // func_80B3738C
void func_80B373F4(void); // func_80B373F4
void func_80B37428(void); // func_80B37428
void func_80B374B8(void); // func_80B374B8
void func_80B374FC(void); // func_80B374FC
void func_80B37590(void); // func_80B37590
void func_80B37950(void); // func_80B37950
void func_80B37998(void); // func_80B37998
void func_80B379C0(void); // func_80B379C0
void func_80B37A14(void); // func_80B37A14
void func_80B37A64(void); // func_80B37A64
void func_80B37A8C(void); // func_80B37A8C
void func_80B37AA0(void); // func_80B37AA0
void func_80B37B78(void); // func_80B37B78
void func_80B37C04(void); // func_80B37C04
void func_80B37C60(void); // func_80B37C60
void func_80B37CA0(void); // func_80B37CA0
void func_80B37EC0(void); // func_80B37EC0
void func_80B38028(void); // func_80B38028
void func_80B38060(void); // func_80B38060
void func_80B3828C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80B3828C
void func_80B382E4(void); // func_80B382E4
void func_80B38454(void); // func_80B38454
void func_80B38498(void); // func_80B38498
void func_80B38E20(void); // func_80B38E20
void func_80B38E88(void); // func_80B38E88
void func_80B38EFC(void); // func_80B38EFC
void func_80B39108(void); // func_80B39108
void func_80B39470(void); // func_80B39470
void func_80B395C4(void); // func_80B395C4
void func_80B395EC(void); // func_80B395EC
void func_80B39638(void); // func_80B39638
void func_80B39834(void); // func_80B39834
void func_80B39908(void); // func_80B39908
void func_80B39B28(void); // func_80B39B28
void func_80B39B5C(void); // func_80B39B5C
void func_80B39B94(void); // func_80B39B94
void func_80B39C4C(void); // func_80B39C4C
void func_80B39C78(void); // func_80B39C78
void func_80B39C9C(void); // func_80B39C9C
void func_80B39F60(void); // func_80B39F60
void func_80B39FA8(void); // func_80B39FA8
void func_80B3A0D8(void); // func_80B3A0D8
void func_80B3A13C(void); // func_80B3A13C
void func_80B3A498(void); // func_80B3A498
void func_80B3A500(void); // func_80B3A500
void func_80B3A7C8(void); // func_80B3A7C8
void func_80B3A888(void); // func_80B3A888
void func_80B3AC50(void); // func_80B3AC50
void func_80B3AC94(void); // func_80B3AC94
void func_80B3ADD8(void); // func_80B3ADD8
void func_80B3AE60(void); // func_80B3AE60
void func_80B3AFB0(void); // func_80B3AFB0
void func_80B3B05C(void); // func_80B3B05C
void func_80B3B0A0(void); // func_80B3B0A0
void func_80B3B120(void); // func_80B3B120
void func_80B3B21C(void); // func_80B3B21C
void func_80B3B294(void); // func_80B3B294
void func_80B3B4B0(void); // func_80B3B4B0
void func_80B3B5D4(void); // func_80B3B5D4
void func_80B3B648(void); // func_80B3B648
void func_80B3B7E4(void); // func_80B3B7E4
void func_80B3B8A4(void); // func_80B3B8A4
void func_80B3B958(void); // func_80B3B958
void func_80B3BBE0(void); // func_80B3BBE0
void func_80B3BBF0(void); // func_80B3BBF0
void func_80B3BD44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B3BD44
void func_80B3BDC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B3BDC0
void func_80B3BE00(void); // func_80B3BE00
void func_80B3C260(void); // func_80B3C260
void func_80B3C29C(void); // func_80B3C29C
void func_80B3C2B0(void); // func_80B3C2B0
void func_80B3C2C4(void); // func_80B3C2C4
void func_80B3C39C(void); // func_80B3C39C
void func_80B3C4E0(void); // func_80B3C4E0
void func_80B3C624(void); // func_80B3C624
void func_80B3C6F8(void); // func_80B3C6F8
void func_80B3C7D8(void); // func_80B3C7D8
void func_80B3C80C(void); // func_80B3C80C
void func_80B3C858(void); // func_80B3C858
void func_80B3CA20(void); // func_80B3CA20
void func_80B3CC38(void); // func_80B3CC38
void func_80B3CC80(void); // func_80B3CC80
void func_80B3CD1C(void); // func_80B3CD1C
void func_80B3CDA4(void); // func_80B3CDA4
void func_80B3CEC0(void); // func_80B3CEC0
void func_80B3CF60(void); // func_80B3CF60
void func_80B3D044(void); // func_80B3D044
void func_80B3D11C(void); // func_80B3D11C
void func_80B3D2D4(void); // func_80B3D2D4
void func_80B3D338(void); // func_80B3D338
void func_80B3D3F8(void); // func_80B3D3F8
void func_80B3D47C(void); // func_80B3D47C
void func_80B3D558(void); // func_80B3D558
void func_80B3D5B8(void); // func_80B3D5B8
void func_80B3D7B8(void); // func_80B3D7B8
void func_80B3D7E4(void); // func_80B3D7E4
void func_80B3D974(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B3D974
void func_80B3DA88(void); // func_80B3DA88
void func_80B3DAA0(void); // func_80B3DAA0
void func_80B3DB98(void); // func_80B3DB98
void func_80B3DFF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13); // func_80B3DFF0
void func_80B3E168(void); // func_80B3E168
void func_80B3E460(void); // func_80B3E460
void func_80B3E5B4(void); // func_80B3E5B4
void func_80B3E5DC(void); // func_80B3E5DC
void func_80B3E69C(void); // func_80B3E69C
void func_80B3E7C8(void); // func_80B3E7C8
void func_80B3E834(void); // func_80B3E834
void func_80B3E8BC(void); // func_80B3E8BC
void func_80B3E96C(void); // func_80B3E96C
void func_80B3EC10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80B3EC10
void func_80B3EC84(void); // func_80B3EC84
void func_80B3ED88(void); // func_80B3ED88
void func_80B3EE8C(void); // func_80B3EE8C
void func_80B3EEDC(void); // func_80B3EEDC
void func_80B3EF90(void); // func_80B3EF90
void func_80B3F00C(void); // func_80B3F00C
void func_80B3F044(void); // func_80B3F044
void func_80B3F318(void); // func_80B3F318
void func_80B3F494(void); // func_80B3F494
void func_80B3F4A4(void); // func_80B3F4A4
void func_80B3F598(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B3F598
void func_80B3F614(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B3F614
void func_80B3F6EC(void); // func_80B3F6EC
void func_80B3F78C(void); // func_80B3F78C
void func_80B3F920(void); // func_80B3F920
void func_80B3FB84(void); // func_80B3FB84
void func_80B40080(void); // func_80B40080
void func_80B4009C(void); // func_80B4009C
void func_80B400C8(void); // func_80B400C8
void func_80B40100(void); // func_80B40100
void func_80B40160(void); // func_80B40160
void func_80B401F8(void); // func_80B401F8
void func_80B40308(void); // func_80B40308
void func_80B40394(void); // func_80B40394
void func_80B4056C(void); // func_80B4056C
void func_80B40628(void); // func_80B40628
void func_80B4065C(void); // func_80B4065C
void func_80B40698(void); // func_80B40698
void func_80B40800(void); // func_80B40800
void func_80B40B04(void); // func_80B40B04
void func_80B40B38(void); // func_80B40B38
void func_80B40BC0(void); // func_80B40BC0
void func_80B40BFC(void); // func_80B40BFC
void func_80B40C38(void); // func_80B40C38
void func_80B40C74(void); // func_80B40C74
void func_80B40D00(void); // func_80B40D00
void func_80B40D30(void); // func_80B40D30
void func_80B40D64(void); // func_80B40D64
void func_80B40D8C(void); // func_80B40D8C
void func_80B40DB4(void); // func_80B40DB4
void func_80B40E18(void); // func_80B40E18
void func_80B40E38(void); // func_80B40E38
void func_80B40E54(void); // func_80B40E54
void func_80B40E74(void); // func_80B40E74
void func_80B40EBC(void); // func_80B40EBC
void func_80B40EE8(void); // func_80B40EE8
void func_80B411DC(void); // func_80B411DC
void func_80B41368(void); // func_80B41368
void func_80B413C8(void); // func_80B413C8
void func_80B41460(void); // func_80B41460
void func_80B41528(void); // func_80B41528
void func_80B415A8(void); // func_80B415A8
void func_80B4163C(void); // func_80B4163C
void func_80B417B8(void); // func_80B417B8
void func_80B41858(void); // func_80B41858
void func_80B418C4(void); // func_80B418C4
void func_80B419B0(void); // func_80B419B0
void func_80B41A48(void); // func_80B41A48
void func_80B41ACC(void); // func_80B41ACC
void func_80B41C30(void); // func_80B41C30
void func_80B41C54(void); // func_80B41C54
void func_80B41CBC(void); // func_80B41CBC
void func_80B41D64(void); // func_80B41D64
void func_80B41E18(void); // func_80B41E18
void func_80B42508(void); // func_80B42508
void func_80B425A0(void); // func_80B425A0
void func_80B42660(void); // func_80B42660
void func_80B42714(void); // func_80B42714
void func_80B427C8(void); // func_80B427C8
void func_80B4296C(void); // func_80B4296C
void func_80B42A8C(void); // func_80B42A8C
void func_80B42D28(void); // func_80B42D28
void func_80B42EE0(void); // func_80B42EE0
void func_80B42FA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B42FA0
void func_80B43008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B43008
void func_80B43074(void); // func_80B43074
void func_80B431D0(void); // func_80B431D0
void func_80B439B0(void); // func_80B439B0
void func_80B43A24(void); // func_80B43A24
void func_80B43A74(void); // func_80B43A74
void func_80B43A9C(void); // func_80B43A9C
void func_80B43AB0(void); // func_80B43AB0
void func_80B43AF0(void); // func_80B43AF0
void func_80B43B80(void); // func_80B43B80
void func_80B43BC8(void); // func_80B43BC8
void func_80B43DD4(void); // func_80B43DD4
void func_80B43E6C(void); // func_80B43E6C
void func_80B43F0C(void); // func_80B43F0C
void func_80B43F70(void); // func_80B43F70
void func_80B44024(void); // func_80B44024
void func_80B4407C(void); // func_80B4407C
void func_80B440B8(void); // func_80B440B8
void func_80B44234(void); // func_80B44234
void func_80B442E4(void); // func_80B442E4
void func_80B443A0(void); // func_80B443A0
void func_80B444BC(void); // func_80B444BC
void func_80B444F4(void); // func_80B444F4
void func_80B44514(void); // func_80B44514
void func_80B44540(void); // func_80B44540
void func_80B44570(void); // func_80B44570
void func_80B44620(void); // func_80B44620
void func_80B44640(void); // func_80B44640
void func_80B44664(void); // func_80B44664
void func_80B44690(void); // func_80B44690
void func_80B446D0(void); // func_80B446D0
void func_80B44700(void); // func_80B44700
void func_80B447C0(void); // func_80B447C0
void func_80B44A90(void); // func_80B44A90
void func_80B44B78(void); // func_80B44B78
void func_80B44B84(void); // func_80B44B84
void func_80B44C24(void); // func_80B44C24
void func_80B44C80(void); // func_80B44C80
void func_80B44E90(void); // func_80B44E90
void func_80B44EFC(void); // func_80B44EFC
void func_80B44F58(void); // func_80B44F58
void func_80B44FEC(void); // func_80B44FEC
void func_80B45080(void); // func_80B45080
void func_80B450C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B450C0
void func_80B4516C(void); // func_80B4516C
void func_80B451A0(void); // func_80B451A0
void func_80B452EC(void); // func_80B452EC
void func_80B453F4(void); // func_80B453F4
void func_80B45460(void); // func_80B45460
void func_80B454BC(void); // func_80B454BC
void func_80B45518(void); // func_80B45518
void func_80B45550(void); // func_80B45550
void func_80B4560C(void); // func_80B4560C
void func_80B45648(void); // func_80B45648
void func_80B456A8(void); // func_80B456A8
void func_80B457A0(void); // func_80B457A0
void func_80B458D8(void); // func_80B458D8
void func_80B45980(void); // func_80B45980
void func_80B459E8(void); // func_80B459E8
void func_80B45A4C(void); // func_80B45A4C
void func_80B45A94(void); // func_80B45A94
void func_80B45B1C(void); // func_80B45B1C
void func_80B45BB8(void); // func_80B45BB8
void func_80B45C04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80B45C04
void func_80B45CE0(void); // func_80B45CE0
void func_80B45EC8(void); // func_80B45EC8
void func_80B46118(void); // func_80B46118
void func_80B46184(void); // func_80B46184
void func_80B461DC(void); // func_80B461DC
void func_80B4627C(void); // func_80B4627C
void func_80B46414(void); // func_80B46414
void func_80B46520(void); // func_80B46520
void func_80B465CC(void); // func_80B465CC
void func_80B46644(void); // func_80B46644
void func_80B468B4(void); // func_80B468B4
void func_80B469C4(void); // func_80B469C4
void func_80B46A80(void); // func_80B46A80
void func_80B46B74(void); // func_80B46B74
void func_80B46BB0(void); // func_80B46BB0
void func_80B46BC0(void); // func_80B46BC0
void func_80B46C08(void); // func_80B46C08
void func_80B46C34(void); // func_80B46C34
void func_80B46C50(void); // func_80B46C50
void func_80B46C7C(void); // func_80B46C7C
void func_80B46C94(void); // func_80B46C94
void func_80B46CC0(void); // func_80B46CC0
void func_80B46CF4(void); // func_80B46CF4
void func_80B46D28(void); // func_80B46D28
void func_80B46D6C(void); // func_80B46D6C
void func_80B46DA8(void); // func_80B46DA8
void func_80B46DC8(void); // func_80B46DC8
void func_80B46E20(void); // func_80B46E20
void func_80B46E44(void); // func_80B46E44
void func_80B46EC0(void); // func_80B46EC0
void func_80B46EE8(void); // func_80B46EE8
void func_80B46F88(void); // func_80B46F88
void func_80B46FA8(void); // func_80B46FA8
void func_80B47064(void); // func_80B47064
void func_80B47084(void); // func_80B47084
void func_80B470E0(void); // func_80B470E0
void func_80B47108(void); // func_80B47108
void func_80B471C0(void); // func_80B471C0
void func_80B471E0(void); // func_80B471E0
void func_80B47248(void); // func_80B47248
void func_80B47268(void); // func_80B47268
void func_80B47278(void); // func_80B47278
void func_80B47298(void); // func_80B47298
void func_80B47304(void); // func_80B47304
void func_80B47324(void); // func_80B47324
void func_80B47334(void); // func_80B47334
void func_80B47380(void); // func_80B47380
void func_80B473E4(void); // func_80B473E4
void func_80B47478(void); // func_80B47478
void func_80B474DC(void); // func_80B474DC
void func_80B47568(void); // func_80B47568
void func_80B47600(void); // func_80B47600
void func_80B4770C(void); // func_80B4770C
void func_80B477B4(void); // func_80B477B4
void func_80B47830(void); // func_80B47830
void func_80B478F4(void); // func_80B478F4
void func_80B47938(void); // func_80B47938
void func_80B479E8(void); // func_80B479E8
void func_80B47BAC(void); // func_80B47BAC
void func_80B47D30(void); // func_80B47D30
void func_80B47FA8(void); // func_80B47FA8
void func_80B48060(void); // func_80B48060
void func_80B481C4(void); // func_80B481C4
void func_80B4827C(void); // func_80B4827C
void func_80B482D4(void); // func_80B482D4
void func_80B48324(void); // func_80B48324
void func_80B48374(void); // func_80B48374
void func_80B483CC(void); // func_80B483CC
void func_80B4843C(void); // func_80B4843C
void func_80B484EC(void); // func_80B484EC
void func_80B48588(void); // func_80B48588
void func_80B48610(void); // func_80B48610
void func_80B48620(void); // func_80B48620
void func_80B4873C(void); // func_80B4873C
void func_80B487B4(void); // func_80B487B4
void func_80B48848(void); // func_80B48848
void func_80B48948(void); // func_80B48948
void func_80B48AD4(void); // func_80B48AD4
void func_80B48DE4(void); // func_80B48DE4
void func_80B48E4C(void); // func_80B48E4C
void func_80B48FB0(void); // func_80B48FB0
void func_80B490F0(void); // func_80B490F0
void func_80B491EC(void); // func_80B491EC
void func_80B49228(void); // func_80B49228
void func_80B492FC(void); // func_80B492FC
void func_80B4934C(void); // func_80B4934C
void func_80B49404(void); // func_80B49404
void func_80B49454(void); // func_80B49454
void func_80B49628(void); // func_80B49628
void func_80B49670(void); // func_80B49670
void func_80B497A4(void); // func_80B497A4
void func_80B497EC(void); // func_80B497EC
void func_80B49904(void); // func_80B49904
void func_80B4994C(void); // func_80B4994C
void func_80B499BC(void); // func_80B499BC
void func_80B49A00(void); // func_80B49A00
void func_80B49B1C(void); // func_80B49B1C
void func_80B49BD0(void); // func_80B49BD0
void func_80B49C38(void); // func_80B49C38
void func_80B49DA0(void); // func_80B49DA0
void func_80B49DFC(void); // func_80B49DFC
void func_80B49F88(void); // func_80B49F88
void func_80B4A168(void); // func_80B4A168
void func_80B4A1B8(void); // func_80B4A1B8
void func_80B4A2C0(void); // func_80B4A2C0
void func_80B4A350(void); // func_80B4A350
void func_80B4A570(void); // func_80B4A570
void func_80B4A5E4(void); // func_80B4A5E4
void func_80B4A614(void); // func_80B4A614
void func_80B4A67C(void); // func_80B4A67C
void func_80B4A7C0(void); // func_80B4A7C0
void func_80B4A81C(void); // func_80B4A81C
void func_80B4A9C8(void); // func_80B4A9C8
void func_80B4AB8C(void); // func_80B4AB8C
void func_80B4ABDC(void); // func_80B4ABDC
void func_80B4ACDC(void); // func_80B4ACDC
void func_80B4ACF0(void); // func_80B4ACF0
void func_80B4AD3C(void); // func_80B4AD3C
void func_80B4AD60(void); // func_80B4AD60
void func_80B4ADB8(void); // func_80B4ADB8
void func_80B4ADCC(void); // func_80B4ADCC
void func_80B4AEC0(void); // func_80B4AEC0
void func_80B4AEDC(void); // func_80B4AEDC
void func_80B4AF80(void); // func_80B4AF80
void func_80B4AF94(void); // func_80B4AF94
void func_80B4B024(void); // func_80B4B024
void func_80B4B048(void); // func_80B4B048
void func_80B4B0C4(void); // func_80B4B0C4
void func_80B4B218(void); // func_80B4B218
void func_80B4B3DC(void); // func_80B4B3DC
void func_80B4B430(void); // func_80B4B430
void func_80B4B484(void); // func_80B4B484
void func_80B4B510(void); // func_80B4B510
void func_80B4B564(void); // func_80B4B564
void func_80B4B724(void); // func_80B4B724
void func_80B4B768(void); // func_80B4B768
void func_80B4B820(void); // func_80B4B820
void func_80B4B864(void); // func_80B4B864
void func_80B4B8BC(void); // func_80B4B8BC
void func_80B4BA30(void); // func_80B4BA30
void func_80B4BA84(void); // func_80B4BA84
void func_80B4BBE0(void); // func_80B4BBE0
void func_80B4BC4C(void); // func_80B4BC4C
void func_80B4BFFC(void); // func_80B4BFFC
void func_80B4C058(void); // func_80B4C058
void func_80B4C1BC(void); // func_80B4C1BC
void func_80B4C218(void); // func_80B4C218
void func_80B4C3A0(void); // func_80B4C3A0
void func_80B4C568(void); // func_80B4C568
void func_80B4C5C0(void); // func_80B4C5C0
void func_80B4C6C8(void); // func_80B4C6C8
void func_80B4C730(void); // func_80B4C730
void func_80B4CAB0(void); // func_80B4CAB0
void func_80B4CB0C(void); // func_80B4CB0C
void func_80B4CC70(void); // func_80B4CC70
void func_80B4CCCC(void); // func_80B4CCCC
void func_80B4CE54(void); // func_80B4CE54
void func_80B4CFFC(void); // func_80B4CFFC
void func_80B4D054(void); // func_80B4D054
void func_80B4D15C(void); // func_80B4D15C
void func_80B4D290(void); // func_80B4D290
void func_80B4D3E4(void); // func_80B4D3E4
void func_80B4D480(void); // func_80B4D480
void func_80B4D670(void); // func_80B4D670
void func_80B4D760(void); // func_80B4D760
void func_80B4D7B8(void); // func_80B4D7B8
void func_80B4D9B4(void); // func_80B4D9B4
void func_80B4D9D8(void); // func_80B4D9D8
void func_80B4D9F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B4D9F4
void func_80B4DB14(void); // func_80B4DB14
void func_80B4E120(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B4E120
void func_80B4E158(void); // func_80B4E158
void func_80B4E1B0(void); // func_80B4E1B0
void func_80B4E200(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B4E200
void func_80B4E2AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B4E2AC
void func_80B4E324(void); // func_80B4E324
void func_80B4E3F0(void); // func_80B4E3F0
void func_80B4E5B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B4E5B0
void func_80B4E61C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B4E61C
void func_80B4E660(void); // func_80B4E660
void func_80B4E6E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B4E6E4
void func_80B4E784(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B4E784
void func_80B4E7BC(void); // func_80B4E7BC
void func_80B50410(void); // func_80B50410
void func_80B50710(void); // func_80B50710
void func_80B507A0(void); // func_80B507A0
void func_80B50854(void); // func_80B50854
void func_80B50954(void); // func_80B50954
void func_80B509A8(void); // func_80B509A8
void func_80B50B38(void); // func_80B50B38
void func_80B50C78(void); // func_80B50C78
void func_80B50E14(void); // func_80B50E14
void func_80B50ED4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B50ED4
void func_80B5100C(void); // func_80B5100C
void func_80B5123C(void); // func_80B5123C
void func_80B51308(void); // func_80B51308
void func_80B51398(void); // func_80B51398
void func_80B51410(void); // func_80B51410
void func_80B51510(void); // func_80B51510
void func_80B51698(void); // func_80B51698
void func_80B51760(void); // func_80B51760
void func_80B51970(void); // func_80B51970
void func_80B51B40(void); // func_80B51B40
void func_80B51D9C(void); // func_80B51D9C
void func_80B51EA4(void); // func_80B51EA4
void func_80B51FD0(void); // func_80B51FD0
void func_80B5202C(void); // func_80B5202C
void func_80B5216C(void); // func_80B5216C
void func_80B521E8(void); // func_80B521E8
void func_80B5227C(void); // func_80B5227C
void func_80B52340(void); // func_80B52340
void func_80B52430(void); // func_80B52430
void func_80B5253C(void); // func_80B5253C
void func_80B525E0(void); // func_80B525E0
void func_80B52654(void); // func_80B52654
void func_80B526FC(void); // func_80B526FC
void func_80B529B8(void); // func_80B529B8
void func_80B529E4(void); // func_80B529E4
void func_80B52AD4(void); // func_80B52AD4
void func_80B52AF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B52AF0
void func_80B52D8C(void); // func_80B52D8C
void func_80B52F74(void); // func_80B52F74
void func_80B53840(void); // func_80B53840
void func_80B539CC(void); // func_80B539CC
void func_80B53A7C(void); // func_80B53A7C
void func_80B53B3C(void); // func_80B53B3C
void func_80B53BA8(void); // func_80B53BA8
void func_80B53CE8(void); // func_80B53CE8
void func_80B53ED4(void); // func_80B53ED4
void func_80B53F84(void); // func_80B53F84
void func_80B54124(void); // func_80B54124
void func_80B54678(void); // func_80B54678
void func_80B546F4(void); // func_80B546F4
void func_80B54750(void); // func_80B54750
void func_80B547C8(void); // func_80B547C8
void func_80B5492C(void); // func_80B5492C
void func_80B54A94(void); // func_80B54A94
void func_80B54BC4(void); // func_80B54BC4
void func_80B54C5C(void); // func_80B54C5C
void func_80B54D18(void); // func_80B54D18
void func_80B54DF4(void); // func_80B54DF4
void func_80B55180(void); // func_80B55180
void func_80B552E4(void); // func_80B552E4
void func_80B553AC(void); // func_80B553AC
void func_80B554E8(void); // func_80B554E8
void func_80B555C8(void); // func_80B555C8
void func_80B556F8(void); // func_80B556F8
void func_80B557AC(void); // func_80B557AC
void func_80B55860(void); // func_80B55860
void func_80B55914(void); // func_80B55914
void func_80B55D20(void); // func_80B55D20
void func_80B55D98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80B55D98
void func_80B55ECC(void); // func_80B55ECC
void func_80B55F8C(void); // func_80B55F8C
void func_80B5600C(void); // func_80B5600C
void func_80B56094(void); // func_80B56094
void func_80B5611C(void); // func_80B5611C
void func_80B561A4(void); // func_80B561A4
void func_80B56418(void); // func_80B56418
void func_80B56744(void); // func_80B56744
void func_80B56880(void); // func_80B56880
void func_80B56B00(void); // func_80B56B00
void func_80B56BC0(void); // func_80B56BC0
void func_80B56CAC(void); // func_80B56CAC
void func_80B56D28(void); // func_80B56D28
void func_80B56E44(void); // func_80B56E44
void func_80B56EB4(void); // func_80B56EB4
void func_80B5702C(void); // func_80B5702C
void func_80B572D4(void); // func_80B572D4
UNK_TYPE4 func_80B573F4(s32 param_1, UNK_TYPE4 param_2); // func_80B573F4
void func_80B575BC(void); // func_80B575BC
void func_80B57674(void); // func_80B57674
void func_80B57718(void); // func_80B57718
void func_80B577F0(void); // func_80B577F0
void func_80B578F8(void); // func_80B578F8
void func_80B57A44(void); // func_80B57A44
void func_80B57B48(void); // func_80B57B48
void func_80B57C9C(void); // func_80B57C9C
void func_80B57D70(void); // func_80B57D70
void func_80B57D9C(void); // func_80B57D9C
void func_80B57EE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B57EE8
void func_80B57FC4(void); // func_80B57FC4
void func_80B580C0(void); // func_80B580C0
void func_80B5A720(void); // func_80B5A720
void func_80B5A828(void); // func_80B5A828
void func_80B5A854(void); // func_80B5A854
void func_80B5A9E8(void); // func_80B5A9E8
void func_80B5ABC4(void); // func_80B5ABC4
void func_80B5AC3C(void); // func_80B5AC3C
void func_80B5AF80(void); // func_80B5AF80
void func_80B5B060(void); // func_80B5B060
void func_80B5B194(void); // func_80B5B194
void func_80B5B2E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B5B2E0
void func_80B5B3E4(void); // func_80B5B3E4
void func_80B5BA64(void); // func_80B5BA64
void func_80B5BAAC(void); // func_80B5BAAC
void func_80B5BB38(void); // func_80B5BB38
void func_80B5BDA8(void); // func_80B5BDA8
void func_80B5BE04(void); // func_80B5BE04
void func_80B5BE88(void); // func_80B5BE88
void func_80B5BED4(void); // func_80B5BED4
void func_80B5BF60(void); // func_80B5BF60
void func_80B5BFB8(void); // func_80B5BFB8
void func_80B5C154(void); // func_80B5C154
void func_80B5C1CC(void); // func_80B5C1CC
void func_80B5C244(void); // func_80B5C244
void func_80B5C25C(void); // func_80B5C25C
void func_80B5C3B8(void); // func_80B5C3B8
void func_80B5C3D8(void); // func_80B5C3D8
void func_80B5C634(void); // func_80B5C634
void func_80B5C64C(void); // func_80B5C64C
void func_80B5C684(void); // func_80B5C684
void func_80B5C6DC(void); // func_80B5C6DC
void func_80B5C910(void); // func_80B5C910
void func_80B5C950(void); // func_80B5C950
void func_80B5C9A8(void); // func_80B5C9A8
void func_80B5C9C0(void); // func_80B5C9C0
void func_80B5C9D0(void); // func_80B5C9D0
void func_80B5CA30(void); // func_80B5CA30
void func_80B5CAD0(void); // func_80B5CAD0
void func_80B5CB0C(void); // func_80B5CB0C
void func_80B5CBA0(void); // func_80B5CBA0
void func_80B5CBEC(void); // func_80B5CBEC
void func_80B5CC88(void); // func_80B5CC88
void func_80B5CCA0(void); // func_80B5CCA0
void func_80B5CCF4(void); // func_80B5CCF4
void func_80B5CD40(void); // func_80B5CD40
void func_80B5CE6C(void); // func_80B5CE6C
void func_80B5CEC8(void); // func_80B5CEC8
void func_80B5D114(void); // func_80B5D114
void func_80B5D160(void); // func_80B5D160
void func_80B5D37C(void); // func_80B5D37C
void func_80B5D470(void); // func_80B5D470
void func_80B5D648(void); // func_80B5D648
void func_80B5D750(void); // func_80B5D750
void func_80B5D8AC(void); // func_80B5D8AC
void func_80B5DAEC(void); // func_80B5DAEC
void func_80B5DB6C(void); // func_80B5DB6C
void func_80B5DD20(void); // func_80B5DD20
void func_80B5DECC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B5DECC
void func_80B5DF58(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B5DF58
void func_80B5E078(void); // func_80B5E078
void func_80B5E1D8(void); // func_80B5E1D8
void func_80B5E890(void); // func_80B5E890
void func_80B5EA74(void); // func_80B5EA74
void func_80B5EAA0(void); // func_80B5EAA0
void func_80B5EB40(void); // func_80B5EB40
void func_80B5ED90(void); // func_80B5ED90
void func_80B5EDF0(void); // func_80B5EDF0
void func_80B5EE3C(void); // func_80B5EE3C
void func_80B5EF88(void); // func_80B5EF88
void func_80B5EFD0(void); // func_80B5EFD0
void func_80B5F3A4(void); // func_80B5F3A4
void func_80B5F418(void); // func_80B5F418
void func_80B5F508(void); // func_80B5F508
void func_80B5F888(void); // func_80B5F888
void func_80B5F8D8(void); // func_80B5F8D8
void func_80B5FCC0(void); // func_80B5FCC0
void func_80B5FD68(void); // func_80B5FD68
void func_80B60138(void); // func_80B60138
void func_80B6031C(void); // func_80B6031C
void func_80B6043C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B6043C
void func_80B60494(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B60494
void func_80B60564(void); // func_80B60564
void func_80B60AD0(void); // func_80B60AD0
void func_80B60C70(void); // func_80B60C70
void func_80B60C9C(void); // func_80B60C9C
void func_80B60CB0(void); // func_80B60CB0
void func_80B60CC0(void); // func_80B60CC0
void func_80B60D34(void); // func_80B60D34
void func_80B60E54(void); // func_80B60E54
void func_80B60EE8(void); // func_80B60EE8
void func_80B6107C(void); // func_80B6107C
void func_80B610B8(void); // func_80B610B8
void func_80B615E0(void); // func_80B615E0
void func_80B6186C(void); // func_80B6186C
void func_80B61914(void); // func_80B61914
void func_80B619B4(void); // func_80B619B4
void func_80B619FC(void); // func_80B619FC
void func_80B61AC8(void); // func_80B61AC8
void func_80B61AF8(void); // func_80B61AF8
void func_80B61B38(void); // func_80B61B38
void func_80B61B70(void); // func_80B61B70
void func_80B61C04(void); // func_80B61C04
void func_80B61CFC(void); // func_80B61CFC
void func_80B61D74(void); // func_80B61D74
void func_80B61DA4(void); // func_80B61DA4
void func_80B61E9C(void); // func_80B61E9C
void func_80B61F04(void); // func_80B61F04
void func_80B62034(void); // func_80B62034
void func_80B62084(void); // func_80B62084
void func_80B62154(void); // func_80B62154
void func_80B621CC(void); // func_80B621CC
void func_80B622E4(void); // func_80B622E4
void func_80B623BC(void); // func_80B623BC
void func_80B624F4(void); // func_80B624F4
void func_80B6259C(void); // func_80B6259C
void func_80B6275C(void); // func_80B6275C
void func_80B627B4(void); // func_80B627B4
void func_80B62814(void); // func_80B62814
void func_80B62830(void); // func_80B62830
void func_80B62900(void); // func_80B62900
void func_80B62920(void); // func_80B62920
void func_80B629E4(void); // func_80B629E4
void func_80B62A68(void); // func_80B62A68
void func_80B62AD4(void); // func_80B62AD4
void func_80B62B10(void); // func_80B62B10
void func_80B62E38(void); // func_80B62E38
void func_80B62F10(void); // func_80B62F10
void func_80B62FCC(void); // func_80B62FCC
void func_80B631F8(void); // func_80B631F8
void func_80B63264(void); // func_80B63264
void func_80B632BC(void); // func_80B632BC
void func_80B6330C(void); // func_80B6330C
void func_80B633E8(void); // func_80B633E8
void func_80B63410(void); // func_80B63410
void func_80B63450(void); // func_80B63450
void func_80B63474(void); // func_80B63474
void func_80B636D0(void); // func_80B636D0
void func_80B636E4(void); // func_80B636E4
void func_80B63758(void); // func_80B63758
void func_80B6382C(void); // func_80B6382C
void func_80B6383C(void); // func_80B6383C
void func_80B63854(void); // func_80B63854
void func_80B63888(void); // func_80B63888
void func_80B638AC(void); // func_80B638AC
void func_80B638D4(void); // func_80B638D4
void func_80B63964(void); // func_80B63964
void func_80B63980(void); // func_80B63980
void func_80B63A18(void); // func_80B63A18
void func_80B63AC4(void); // func_80B63AC4
void func_80B63C28(void); // func_80B63C28
void func_80B63D0C(void); // func_80B63D0C
void func_80B63D88(void); // func_80B63D88
void func_80B63ED4(void); // func_80B63ED4
void func_80B64190(void); // func_80B64190
void func_80B641E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B641E8
void func_80B64240(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B64240
void func_80B64470(void); // func_80B64470
void func_80B6467C(void); // func_80B6467C
void func_80B64880(void); // func_80B64880
void func_80B64B08(void); // func_80B64B08
void func_80B64DFC(void); // func_80B64DFC
void func_80B654C0(void); // func_80B654C0
void func_80B65840(void); // func_80B65840
void func_80B65880(void); // func_80B65880
void func_80B65894(void); // func_80B65894
void func_80B658A4(void); // func_80B658A4
void func_80B65CE0(void); // func_80B65CE0
void func_80B65D54(void); // func_80B65D54
void func_80B65D68(void); // func_80B65D68
void func_80B65DA8(void); // func_80B65DA8
void func_80B6618C(void); // func_80B6618C
void func_80B66304(void); // func_80B66304
void func_80B66418(void); // func_80B66418
void func_80B66454(void); // func_80B66454
void func_80B66A20(void); // func_80B66A20
void func_80B66A6C(void); // func_80B66A6C
void func_80B66A7C(void); // func_80B66A7C
void func_80B66A90(void); // func_80B66A90
void func_80B66AA0(void); // func_80B66AA0
void func_80B66AC4(void); // func_80B66AC4
void func_80B66B78(void); // func_80B66B78
void func_80B66BAC(void); // func_80B66BAC
void func_80B66BDC(void); // func_80B66BDC
void func_80B66D30(void); // func_80B66D30
void func_80B67010(void); // func_80B67010
void func_80B6703C(void); // func_80B6703C
void func_80B670A4(void); // func_80B670A4
void func_80B67148(void); // func_80B67148
void func_80B671A0(void); // func_80B671A0
void func_80B67208(void); // func_80B67208
void func_80B672A4(void); // func_80B672A4
void func_80B67348(void); // func_80B67348
void func_80B67458(void); // func_80B67458
void func_80B67540(void); // func_80B67540
void func_80B677BC(void); // func_80B677BC
void func_80B67838(void); // func_80B67838
void func_80B678A8(void); // func_80B678A8
void func_80B67958(void); // func_80B67958
void func_80B67984(void); // func_80B67984
void func_80B67AB4(void); // func_80B67AB4
void func_80B67B50(void); // func_80B67B50
void func_80B67C1C(void); // func_80B67C1C
void func_80B67DA0(void); // func_80B67DA0
void func_80B67E20(void); // func_80B67E20
void func_80B67E78(void); // func_80B67E78
void func_80B680A8(void); // func_80B680A8
void func_80B681E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B681E8
void func_80B68310(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B68310
void func_80B6849C(void); // func_80B6849C
void func_80B6D660(void); // func_80B6D660
void func_80B6D9EC(void); // func_80B6D9EC
void func_80B6DA20(void); // func_80B6DA20
void func_80B6DB20(void); // func_80B6DB20
void func_80B6DBE0(void); // func_80B6DBE0
void func_80B6DC64(void); // func_80B6DC64
void func_80B6DC98(void); // func_80B6DC98
void func_80B6DCAC(void); // func_80B6DCAC
void func_80B6DCEC(void); // func_80B6DCEC
void func_80B6DD00(void); // func_80B6DD00
void func_80B6DD5C(void); // func_80B6DD5C
void func_80B6DD70(void); // func_80B6DD70
void func_80B6DD80(void); // func_80B6DD80
void func_80B6DD9C(void); // func_80B6DD9C
void func_80B6DE80(void); // func_80B6DE80
void func_80B6DEA8(void); // func_80B6DEA8
void func_80B6DEB8(void); // func_80B6DEB8
void func_80B6DF44(void); // func_80B6DF44
void func_80B6E020(void); // func_80B6E020
void func_80B6E090(void); // func_80B6E090
void func_80B6E3AC(void); // func_80B6E3AC
void func_80B6E470(void); // func_80B6E470
void func_80B6E4B8(void); // func_80B6E4B8
void func_80B6E4CC(void); // func_80B6E4CC
void func_80B6E544(void); // func_80B6E544
void func_80B6E558(void); // func_80B6E558
void func_80B6E5F8(void); // func_80B6E5F8
void func_80B6E614(void); // func_80B6E614
void func_80B6E664(void); // func_80B6E664
void func_80B6E688(void); // func_80B6E688
void func_80B6E820(void); // func_80B6E820
void func_80B6E890(void); // func_80B6E890
void func_80B6E980(void); // func_80B6E980
void func_80B6EA94(void); // func_80B6EA94
void func_80B6EADC(void); // func_80B6EADC
void func_80B6EAF4(void); // func_80B6EAF4
void func_80B6EBF4(void); // func_80B6EBF4
void func_80B6EC08(void); // func_80B6EC08
void func_80B6EC70(void); // func_80B6EC70
void func_80B6EC8C(void); // func_80B6EC8C
void func_80B6ECC4(void); // func_80B6ECC4
void func_80B6ECD8(void); // func_80B6ECD8
void func_80B6ED30(void); // func_80B6ED30
void func_80B6ED58(void); // func_80B6ED58
void func_80B6ED68(void); // func_80B6ED68
void func_80B6ED8C(void); // func_80B6ED8C
void func_80B6EFA0(void); // func_80B6EFA0
void func_80B6EFEC(void); // func_80B6EFEC
void func_80B6F098(void); // func_80B6F098
void func_80B6F2DC(void); // func_80B6F2DC
void func_80B6F478(void); // func_80B6F478
void func_80B6F4C0(void); // func_80B6F4C0
void func_80B6F4D4(void); // func_80B6F4D4
void func_80B6F5A4(void); // func_80B6F5A4
void func_80B6F5B8(void); // func_80B6F5B8
void func_80B6F61C(void); // func_80B6F61C
void func_80B6F640(void); // func_80B6F640
void func_80B6F708(void); // func_80B6F708
void func_80B6F72C(void); // func_80B6F72C
void func_80B6F8F8(void); // func_80B6F8F8
void func_80B6F90C(void); // func_80B6F90C
void func_80B6F91C(void); // func_80B6F91C
void func_80B6F940(void); // func_80B6F940
void func_80B6FB30(void); // func_80B6FB30
void func_80B6FCA4(void); // func_80B6FCA4
void func_80B6FE08(void); // func_80B6FE08
void func_80B6FE48(void); // func_80B6FE48
void func_80B6FEBC(void); // func_80B6FEBC
void func_80B6FF28(void); // func_80B6FF28
void func_80B6FF90(void); // func_80B6FF90
void func_80B70074(void); // func_80B70074
void func_80B700A8(void); // func_80B700A8
void func_80B700C0(void); // func_80B700C0
void func_80B70214(void); // func_80B70214
void func_80B70230(void); // func_80B70230
void func_80B70498(void); // func_80B70498
void func_80B704B4(void); // func_80B704B4
void func_80B706C4(void); // func_80B706C4
void func_80B706E8(void); // func_80B706E8
void func_80B708C0(void); // func_80B708C0
void func_80B70AB4(void); // func_80B70AB4
void func_80B70B04(void); // func_80B70B04
void func_80B70D24(void); // func_80B70D24
void func_80B70DEC(void); // func_80B70DEC
void func_80B70F74(void); // func_80B70F74
void func_80B70FA0(void); // func_80B70FA0
void func_80B70FF8(void); // func_80B70FF8
void func_80B710AC(void); // func_80B710AC
void func_80B710E4(void); // func_80B710E4
void func_80B71114(void); // func_80B71114
void func_80B7114C(void); // func_80B7114C
void func_80B71228(void); // func_80B71228
void func_80B7123C(void); // func_80B7123C
void func_80B712FC(void); // func_80B712FC
void func_80B71314(void); // func_80B71314
void func_80B71354(void); // func_80B71354
void func_80B713A4(void); // func_80B713A4
void func_80B71488(void); // func_80B71488
void func_80B714D8(void); // func_80B714D8
void func_80B7151C(void); // func_80B7151C
void func_80B715AC(void); // func_80B715AC
void func_80B71650(void); // func_80B71650
void func_80B716A8(void); // func_80B716A8
void func_80B717C8(void); // func_80B717C8
void func_80B717E0(void); // func_80B717E0
void func_80B718B0(void); // func_80B718B0
void func_80B718C4(void); // func_80B718C4
void func_80B71910(void); // func_80B71910
void func_80B71954(void); // func_80B71954
void func_80B71A08(void); // func_80B71A08
void func_80B71A58(void); // func_80B71A58
void func_80B71B6C(void); // func_80B71B6C
void func_80B71BB8(void); // func_80B71BB8
void func_80B71D8C(void); // func_80B71D8C
void func_80B71DF0(void); // func_80B71DF0
void func_80B71EA8(void); // func_80B71EA8
void func_80B71F3C(void); // func_80B71F3C
void func_80B72100(void); // func_80B72100
void func_80B72190(void); // func_80B72190
void func_80B723F8(void); // func_80B723F8
void func_80B72430(void); // func_80B72430
void func_80B725C0(void); // func_80B725C0
void func_80B726B4(void); // func_80B726B4
void func_80B72830(void); // func_80B72830
void func_80B7285C(void); // func_80B7285C
void func_80B72880(void); // func_80B72880
void func_80B72970(void); // func_80B72970
void func_80B72DBC(void); // func_80B72DBC
void func_80B72E88(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B72E88
void func_80B7302C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B7302C
void func_80B731EC(void); // func_80B731EC
void func_80B73A90(void); // func_80B73A90
void func_80B73AE4(void); // func_80B73AE4
void func_80B73B98(void); // func_80B73B98
void func_80B73C58(void); // func_80B73C58
void func_80B73DF4(void); // func_80B73DF4
void func_80B73E3C(void); // func_80B73E3C
void func_80B73F1C(void); // func_80B73F1C
void func_80B7406C(void); // func_80B7406C
void func_80B7408C(void); // func_80B7408C
void func_80B74134(void); // func_80B74134
void func_80B741F8(void); // func_80B741F8
void func_80B742F8(void); // func_80B742F8
void func_80B74440(void); // func_80B74440
void func_80B74550(void); // func_80B74550
void func_80B747C8(void); // func_80B747C8
void func_80B74840(void); // func_80B74840
void func_80B749D0(void); // func_80B749D0
void func_80B74AD8(void); // func_80B74AD8
void func_80B74B54(void); // func_80B74B54
void func_80B74BC8(void); // func_80B74BC8
void func_80B74E5C(void); // func_80B74E5C
void func_80B750A0(void); // func_80B750A0
void func_80B7517C(void); // func_80B7517C
void func_80B751F8(void); // func_80B751F8
void func_80B753A0(void); // func_80B753A0
void func_80B75564(void); // func_80B75564
void func_80B75590(void); // func_80B75590
void func_80B75658(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B75658
void func_80B75708(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B75708
void func_80B757AC(void); // func_80B757AC
void func_80B76030(void); // func_80B76030
void func_80B76110(void); // func_80B76110
void func_80B76188(void); // func_80B76188
void func_80B761FC(void); // func_80B761FC
void func_80B76368(void); // func_80B76368
void func_80B763C4(void); // func_80B763C4
void func_80B76440(void); // func_80B76440
void func_80B76540(void); // func_80B76540
void func_80B76600(void); // func_80B76600
void func_80B7679C(void); // func_80B7679C
void func_80B768F0(void); // func_80B768F0
void func_80B76924(void); // func_80B76924
void func_80B76980(void); // func_80B76980
void func_80B76A64(void); // func_80B76A64
void func_80B76BB8(void); // func_80B76BB8
void func_80B76C38(void); // func_80B76C38
void func_80B76C84(void); // func_80B76C84
void func_80B76E1C(void); // func_80B76E1C
void func_80B76E48(void); // func_80B76E48
void func_80B76ED4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B76ED4
void func_80B77008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80B77008
void func_80B77078(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B77078
void func_80B77354(void); // func_80B77354
void func_80B773D0(void); // func_80B773D0
void func_80B77770(void); // func_80B77770
void func_80B77FA4(void); // func_80B77FA4
void func_80B781DC(void); // func_80B781DC
void func_80B783E0(void); // func_80B783E0
void func_80B78764(void); // func_80B78764
void func_80B78A54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B78A54
void func_80B78C18(void); // func_80B78C18
void func_80B78D08(void); // func_80B78D08
void func_80B78DF0(void); // func_80B78DF0
void func_80B78E2C(void); // func_80B78E2C
void func_80B78E38(void); // func_80B78E38
void func_80B78E88(void); // func_80B78E88
void func_80B78EBC(void); // func_80B78EBC
void func_80B78EFC(void); // func_80B78EFC
void func_80B78F24(void); // func_80B78F24
void func_80B7949C(void); // func_80B7949C
void func_80B79524(void); // func_80B79524
void func_80B79560(void); // func_80B79560
void func_80B795A0(void); // func_80B795A0
void func_80B79734(void); // func_80B79734
void func_80B797EC(void); // func_80B797EC
void func_80B7984C(void); // func_80B7984C
void func_80B79A24(void); // func_80B79A24
void func_80B79A50(void); // func_80B79A50
void func_80B79BA0(void); // func_80B79BA0
void func_80B79F10(void); // func_80B79F10
void func_80B79FFC(void); // func_80B79FFC
void func_80B7A070(void); // func_80B7A070
void func_80B7A0E0(void); // func_80B7A0E0
void func_80B7A144(void); // func_80B7A144
void func_80B7A1B4(void); // func_80B7A1B4
void func_80B7A240(void); // func_80B7A240
void func_80B7A2AC(void); // func_80B7A2AC
void func_80B7A394(void); // func_80B7A394
void func_80B7A400(void); // func_80B7A400
void func_80B7A494(void); // func_80B7A494
void func_80B7A614(void); // func_80B7A614
void func_80B7A7AC(void); // func_80B7A7AC
void func_80B7A860(void); // func_80B7A860
void func_80B7AB78(void); // func_80B7AB78
void func_80B7ABE4(void); // func_80B7ABE4
void func_80B7AC94(void); // func_80B7AC94
void func_80B7AD34(void); // func_80B7AD34
void func_80B7AE58(void); // func_80B7AE58
void func_80B7AEFC(void); // func_80B7AEFC
void func_80B7AF30(void); // func_80B7AF30
void func_80B7B154(void); // func_80B7B154
void func_80B7B18C(void); // func_80B7B18C
void func_80B7B368(void); // func_80B7B368
void func_80B7B598(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B7B598
void func_80B7B93C(void); // func_80B7B93C
void func_80B7BABC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B7BABC
void func_80B7BEA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B7BEA4
void func_80B7C03C(void); // func_80B7C03C
void func_80B7C890(void); // func_80B7C890
void func_80B7CA08(void); // func_80B7CA08
void func_80B7CA34(void); // func_80B7CA34
void func_80B7CA70(void); // func_80B7CA70
void func_80B7CB3C(void); // func_80B7CB3C
void func_80B7CB88(void); // func_80B7CB88
void func_80B7CCE0(void); // func_80B7CCE0
void func_80B7CD28(void); // func_80B7CD28
void func_80B7CE34(void); // func_80B7CE34
void func_80B7CE94(void); // func_80B7CE94
void func_80B7CFA0(void); // func_80B7CFA0
void func_80B7CFFC(void); // func_80B7CFFC
void func_80B7D130(void); // func_80B7D130
void func_80B7D150(void); // func_80B7D150
void func_80B7D254(void); // func_80B7D254
void func_80B7D2E4(void); // func_80B7D2E4
void func_80B7D360(void); // func_80B7D360
void func_80B7D398(void); // func_80B7D398
void func_80B7D3EC(void); // func_80B7D3EC
void func_80B7D47C(void); // func_80B7D47C
void func_80B7D4FC(void); // func_80B7D4FC
void func_80B7D5A4(void); // func_80B7D5A4
void func_80B7D6D0(void); // func_80B7D6D0
void func_80B7D788(void); // func_80B7D788
void func_80B7D9B8(void); // func_80B7D9B8
void func_80B7DC80(void); // func_80B7DC80
void func_80B7DD7C(void); // func_80B7DD7C
void func_80B7DF34(void); // func_80B7DF34
void func_80B7E0BC(void); // func_80B7E0BC
void func_80B7E260(void); // func_80B7E260
void func_80B7E2C4(void); // func_80B7E2C4
void func_80B7E378(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B7E378
void func_80B7E424(void); // func_80B7E424
void BgMbarChair_Init(ActorBgMbarChair* this, GlobalContext* ctxt); // func_80B7E930
void BgMbarChair_Fini(ActorBgMbarChair* this, GlobalContext* ctxt); // func_80B7E980
void BgMbarChair_Main(ActorBgMbarChair* this, GlobalContext* ctxt); // func_80B7E9B4
void BgMbarChair_Draw(ActorBgMbarChair* this, GlobalContext* ctxt); // func_80B7E9C4
void func_80B7EA60(void); // func_80B7EA60
void func_80B7EB30(void); // func_80B7EB30
void func_80B7EB64(void); // func_80B7EB64
void func_80B7EB7C(void); // func_80B7EB7C
void func_80B7EB94(void); // func_80B7EB94
void func_80B7ECFC(void); // func_80B7ECFC
void func_80B7ED54(void); // func_80B7ED54
void func_80B7EDC4(void); // func_80B7EDC4
void func_80B7EE70(void); // func_80B7EE70
void func_80B7EEB4(void); // func_80B7EEB4
void func_80B7EF38(void); // func_80B7EF38
void func_80B7EFD8(void); // func_80B7EFD8
void func_80B7F00C(void); // func_80B7F00C
void func_80B7F034(void); // func_80B7F034
void func_80B7F0A4(void); // func_80B7F0A4
void func_80B7F0D0(void); // func_80B7F0D0
void func_80B7F1A8(void); // func_80B7F1A8
void func_80B7F290(void); // func_80B7F290
void func_80B7F360(void); // func_80B7F360
void func_80B7F398(void); // func_80B7F398
void func_80B7F474(void); // func_80B7F474
void func_80B7F564(void); // func_80B7F564
void func_80B7F730(void); // func_80B7F730
void func_80B7F850(void); // func_80B7F850
void func_80B7FA00(void); // func_80B7FA00
void func_80B7FA84(void); // func_80B7FA84
void func_80B7FA9C(void); // func_80B7FA9C
void func_80B7FB84(void); // func_80B7FB84
void func_80B7FBA4(void); // func_80B7FBA4
void func_80B7FCB8(void); // func_80B7FCB8
void func_80B7FCDC(void); // func_80B7FCDC
void func_80B802E0(void); // func_80B802E0
void func_80B80358(void); // func_80B80358
void func_80B80440(void); // func_80B80440
void func_80B80550(void); // func_80B80550
void func_80B80778(void); // func_80B80778
void func_80B80894(void); // func_80B80894
void func_80B80C88(void); // func_80B80C88
void func_80B80F08(void); // func_80B80F08
void func_80B81010(void); // func_80B81010
void func_80B81234(void); // func_80B81234
void func_80B814B8(void); // func_80B814B8
void func_80B81570(void); // func_80B81570
void func_80B816A4(void); // func_80B816A4
void func_80B816F8(void); // func_80B816F8
void func_80B8186C(void); // func_80B8186C
void func_80B818B4(void); // func_80B818B4
void func_80B818C8(void); // func_80B818C8
void func_80B81978(void); // func_80B81978
void func_80B8198C(void); // func_80B8198C
void func_80B819DC(void); // func_80B819DC
void func_80B819F0(void); // func_80B819F0
void func_80B81A64(void); // func_80B81A64
void func_80B81A80(void); // func_80B81A80
void func_80B81B84(void); // func_80B81B84
void func_80B81BA0(void); // func_80B81BA0
void func_80B81DAC(void); // func_80B81DAC
void func_80B81DC8(void); // func_80B81DC8
void func_80B81EA8(void); // func_80B81EA8
void func_80B82030(void); // func_80B82030
void func_80B823B0(void); // func_80B823B0
void func_80B82454(void); // func_80B82454
void func_80B8259C(void); // func_80B8259C
void func_80B8264C(void); // func_80B8264C
void func_80B828E4(void); // func_80B828E4
void func_80B8296C(void); // func_80B8296C
void func_80B82B00(void); // func_80B82B00
void func_80B82B60(void); // func_80B82B60
void func_80B82D10(void); // func_80B82D10
void func_80B82DC4(void); // func_80B82DC4
void func_80B82DE0(void); // func_80B82DE0
void func_80B832C8(void); // func_80B832C8
void func_80B8330C(void); // func_80B8330C
void func_80B83344(void); // func_80B83344
void func_80B8335C(void); // func_80B8335C
void func_80B833A8(void); // func_80B833A8
void func_80B833C4(void); // func_80B833C4
void func_80B83518(void); // func_80B83518
void func_80B835E4(void); // func_80B835E4
void func_80B83758(void); // func_80B83758
void func_80B83C80(void); // func_80B83C80
void func_80B83D04(void); // func_80B83D04
void func_80B83D58(void); // func_80B83D58
void func_80B83D94(void); // func_80B83D94
void func_80B83E1C(void); // func_80B83E1C
void func_80B83EA4(void); // func_80B83EA4
void func_80B841A0(void); // func_80B841A0
void func_80B84348(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_80B84348
void func_80B84568(void); // func_80B84568
void func_80B84610(void); // func_80B84610
void func_80B84778(void); // func_80B84778
void func_80B84820(void); // func_80B84820
void func_80B8484C(void); // func_80B8484C
void func_80B84928(void); // func_80B84928
void func_80B84AD4(void); // func_80B84AD4
void func_80B84AEC(void); // func_80B84AEC
void func_80B84B9C(void); // func_80B84B9C
void func_80B84BCC(void); // func_80B84BCC
void func_80B84EF0(void); // func_80B84EF0
void func_80B84F20(void); // func_80B84F20
void func_80B85028(void); // func_80B85028
void func_80B8504C(void); // func_80B8504C
void func_80B85590(void); // func_80B85590
void func_80B85800(void); // func_80B85800
void func_80B85858(void); // func_80B85858
void func_80B85900(void); // func_80B85900
void func_80B85A00(void); // func_80B85A00
void func_80B85E18(void); // func_80B85E18
void func_80B85EA0(void); // func_80B85EA0
void func_80B85F48(void); // func_80B85F48
void func_80B85FA8(void); // func_80B85FA8
void func_80B86804(void); // func_80B86804
void func_80B868B8(void); // func_80B868B8
void func_80B86B58(void); // func_80B86B58
void func_80B86B74(void); // func_80B86B74
void func_80B872A4(void); // func_80B872A4
void func_80B872F4(void); // func_80B872F4
void func_80B874D8(void); // func_80B874D8
void func_80B8760C(void); // func_80B8760C
void func_80B87900(void); // func_80B87900
void func_80B8798C(void); // func_80B8798C
void func_80B87C7C(void); // func_80B87C7C
void func_80B87CF8(void); // func_80B87CF8
void func_80B87D3C(void); // func_80B87D3C
void func_80B87E28(void); // func_80B87E28
void func_80B87E9C(void); // func_80B87E9C
void func_80B87F70(void); // func_80B87F70
void func_80B87FDC(void); // func_80B87FDC
void func_80B88214(void); // func_80B88214
void func_80B88278(void); // func_80B88278
void func_80B8833C(void); // func_80B8833C
void func_80B88378(void); // func_80B88378
void func_80B88770(void); // func_80B88770
void func_80B887AC(void); // func_80B887AC
void func_80B88910(void); // func_80B88910
void func_80B88964(void); // func_80B88964
void func_80B88CD8(void); // func_80B88CD8
void func_80B88D6C(void); // func_80B88D6C
void func_80B891B8(void); // func_80B891B8
void func_80B89280(void); // func_80B89280
void func_80B893CC(void); // func_80B893CC
void func_80B894C0(void); // func_80B894C0
void func_80B8960C(void); // func_80B8960C
void func_80B8971C(void); // func_80B8971C
void func_80B89A08(void); // func_80B89A08
void func_80B8A0A0(void); // func_80B8A0A0
void func_80B8A318(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B8A318
void func_80B8A468(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B8A468
void func_80B8A6B0(void); // func_80B8A6B0
void func_80B8A718(void); // func_80B8A718
void func_80B8B2D0(void); // func_80B8B2D0
void func_80B8B504(void); // func_80B8B504
void func_80B8B514(void); // func_80B8B514
void func_80B8B5AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80B8B5AC
void func_80B8B6B4(void); // func_80B8B6B4
void func_80B8B7A8(void); // func_80B8B7A8
void func_80B8B848(void); // func_80B8B848
void func_80B8B90C(void); // func_80B8B90C
void func_80B8BA40(void); // func_80B8BA40
void func_80B8BB3C(void); // func_80B8BB3C
void func_80B8BC1C(void); // func_80B8BC1C
void func_80B8BC78(void); // func_80B8BC78
void func_80B8BCEC(void); // func_80B8BCEC
void func_80B8BD38(void); // func_80B8BD38
void func_80B8BD90(void); // func_80B8BD90
void func_80B8BE08(void); // func_80B8BE08
void func_80B8BF04(void); // func_80B8BF04
void func_80B8BFC8(void); // func_80B8BFC8
void func_80B8C048(void); // func_80B8C048
void func_80B8C0B0(void); // func_80B8C0B0
void func_80B8C13C(void); // func_80B8C13C
void func_80B8C45C(void); // func_80B8C45C
void func_80B8C59C(void); // func_80B8C59C
void func_80B8C644(void); // func_80B8C644
void func_80B8C9B8(void); // func_80B8C9B8
void func_80B8CAA8(void); // func_80B8CAA8
void func_80B8CC0C(void); // func_80B8CC0C
void func_80B8CCB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B8CCB4
void func_80B8CCFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B8CCFC
void func_80B8CD3C(void); // func_80B8CD3C
void func_80B8D030(void); // func_80B8D030
void func_80B8D0BC(void); // func_80B8D0BC
void func_80B8D12C(void); // func_80B8D12C
void func_80B8D1E8(void); // func_80B8D1E8
void func_80B8D2D8(void); // func_80B8D2D8
void func_80B8D3F8(void); // func_80B8D3F8
void func_80B8D66C(void); // func_80B8D66C
void func_80B8D698(void); // func_80B8D698
void func_80B8D6AC(void); // func_80B8D6AC
void func_80B8D6BC(void); // func_80B8D6BC
void func_80B8D6F8(void); // func_80B8D6F8
void func_80B8D95C(void); // func_80B8D95C
void func_80B8D970(void); // func_80B8D970
void func_80B8D9E4(void); // func_80B8D9E4
void func_80B8DA28(void); // func_80B8DA28
void func_80B8DBB8(void); // func_80B8DBB8
void func_80B8DD88(void); // func_80B8DD88
void func_80B8DDC0(void); // func_80B8DDC0
void func_80B8DE44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B8DE44
void func_80B8DF18(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B8DF18
void func_80B8DF9C(void); // func_80B8DF9C
void func_80B8E0BC(void); // func_80B8E0BC
void func_80B8E520(void); // func_80B8E520
void func_80B8E6E0(void); // func_80B8E6E0
void func_80B8E84C(void); // func_80B8E84C
void func_80B8E938(void); // func_80B8E938
void func_80B8EA38(void); // func_80B8EA38
void func_80B8EABC(void); // func_80B8EABC
void func_80B8EBB0(void); // func_80B8EBB0
void func_80B8EBDC(void); // func_80B8EBDC
void func_80B8EBF0(void); // func_80B8EBF0
void func_80B8EC30(void); // func_80B8EC30
void func_80B8ECAC(void); // func_80B8ECAC
void func_80B8ED8C(void); // func_80B8ED8C
void func_80B8EDC8(void); // func_80B8EDC8
void func_80B8EEAC(void); // func_80B8EEAC
void func_80B8EF4C(void); // func_80B8EF4C
void func_80B8F074(void); // func_80B8F074
void func_80B8F108(void); // func_80B8F108
void func_80B8F254(void); // func_80B8F254
void func_80B8F2D8(void); // func_80B8F2D8
void func_80B8F360(void); // func_80B8F360
void func_80B8F400(void); // func_80B8F400
void func_80B8F744(void); // func_80B8F744
void func_80B8F7F4(void); // func_80B8F7F4
void func_80B8F918(void); // func_80B8F918
void func_80B8F998(void); // func_80B8F998
void func_80B8FA14(void); // func_80B8FA14
void func_80B8FE04(void); // func_80B8FE04
void func_80B8FE74(void); // func_80B8FE74
void func_80B8FF80(void); // func_80B8FF80
void func_80B8FF94(void); // func_80B8FF94
void func_80B9000C(void); // func_80B9000C
void func_80B900AC(void); // func_80B900AC
void func_80B900C0(void); // func_80B900C0
void func_80B90170(void); // func_80B90170
void func_80B90184(void); // func_80B90184
void func_80B902B8(void); // func_80B902B8
void func_80B902CC(void); // func_80B902CC
void func_80B90340(void); // func_80B90340
void func_80B9037C(void); // func_80B9037C
void func_80B904D0(void); // func_80B904D0
void func_80B904E4(void); // func_80B904E4
void func_80B9059C(void); // func_80B9059C
void func_80B905B0(void); // func_80B905B0
void func_80B9061C(void); // func_80B9061C
void func_80B9083C(void); // func_80B9083C
void func_80B90A78(void); // func_80B90A78
void func_80B90C08(void); // func_80B90C08
void func_80B90C78(void); // func_80B90C78
void func_80B90D98(void); // func_80B90D98
void func_80B90DF0(void); // func_80B90DF0
void func_80B90E50(void); // func_80B90E50
void func_80B90E84(void); // func_80B90E84
void func_80B90EC8(void); // func_80B90EC8
void func_80B90EF0(void); // func_80B90EF0
void func_80B90F84(void); // func_80B90F84
void func_80B91014(void); // func_80B91014
void func_80B9109C(void); // func_80B9109C
void func_80B9110C(void); // func_80B9110C
void func_80B91154(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B91154
void func_80B91250(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B91250
void func_80B91288(void); // func_80B91288
void func_80B91CC0(void); // func_80B91CC0
void func_80B91D80(void); // func_80B91D80
void func_80B91DB4(void); // func_80B91DB4
void func_80B91DC4(void); // func_80B91DC4
void func_80B91F20(void); // func_80B91F20
void func_80B91F74(void); // func_80B91F74
void func_80B922C0(void); // func_80B922C0
void func_80B922FC(void); // func_80B922FC
void func_80B923A4(void); // func_80B923A4
void func_80B924A8(void); // func_80B924A8
void func_80B924DC(void); // func_80B924DC
void func_80B924F8(void); // func_80B924F8
void func_80B9257C(void); // func_80B9257C
void func_80B925B8(void); // func_80B925B8
void func_80B92644(void); // func_80B92644
void func_80B92660(void); // func_80B92660
void func_80B928E0(void); // func_80B928E0
void func_80B92904(void); // func_80B92904
void func_80B92B10(void); // func_80B92B10
void func_80B92B1C(void); // func_80B92B1C
void func_80B92BD4(void); // func_80B92BD4
void func_80B92C00(void); // func_80B92C00
void func_80B92C48(void); // func_80B92C48
void func_80B92CD0(void); // func_80B92CD0
void func_80B92DC4(void); // func_80B92DC4
void func_80B92DDC(void); // func_80B92DDC
void func_80B92F40(void); // func_80B92F40
void func_80B93310(void); // func_80B93310
void func_80B93468(void); // func_80B93468
void func_80B93538(void); // func_80B93538
void func_80B93994(void); // func_80B93994
void func_80B939C0(void); // func_80B939C0
void func_80B93A48(void); // func_80B93A48
void func_80B93B44(void); // func_80B93B44
void func_80B93BA8(void); // func_80B93BA8
void func_80B93BE0(void); // func_80B93BE0
void func_80B93D2C(void); // func_80B93D2C
void func_80B93DE8(void); // func_80B93DE8
void func_80B93EA0(void); // func_80B93EA0
void func_80B943A0(void); // func_80B943A0
void func_80B943C0(void); // func_80B943C0
void func_80B943EC(void); // func_80B943EC
void func_80B94470(void); // func_80B94470
void func_80B9451C(void); // func_80B9451C
void func_80B9461C(void); // func_80B9461C
void func_80B946B4(void); // func_80B946B4
void func_80B946FC(void); // func_80B946FC
void func_80B948A8(void); // func_80B948A8
void func_80B94A00(void); // func_80B94A00
void func_80B94C5C(void); // func_80B94C5C
void func_80B94D0C(void); // func_80B94D0C
void func_80B94E34(void); // func_80B94E34
void func_80B95128(void); // func_80B95128
void func_80B95240(void); // func_80B95240
void func_80B95260(void); // func_80B95260
void func_80B954C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B954C4
void func_80B95598(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B95598
void func_80B95668(void); // func_80B95668
void func_80B95E20(void); // func_80B95E20
void func_80B95F10(void); // func_80B95F10
void func_80B96054(void); // func_80B96054
void func_80B96088(void); // func_80B96088
void func_80B960E0(void); // func_80B960E0
void func_80B961E0(void); // func_80B961E0
void func_80B96320(void); // func_80B96320
void func_80B9634C(void); // func_80B9634C
void func_80B96378(void); // func_80B96378
void func_80B96410(void); // func_80B96410
void func_80B9649C(void); // func_80B9649C
void func_80B964D0(void); // func_80B964D0
void func_80B965D0(void); // func_80B965D0
void func_80B966BC(void); // func_80B966BC
void func_80B96B90(void); // func_80B96B90
void func_80B96BEC(void); // func_80B96BEC
void func_80B96CE4(void); // func_80B96CE4
void func_80B96D4C(void); // func_80B96D4C
void func_80B96DF0(void); // func_80B96DF0
void func_80B96E5C(void); // func_80B96E5C
void func_80B96FB0(void); // func_80B96FB0
void func_80B97100(void); // func_80B97100
void func_80B97110(void); // func_80B97110
void func_80B97194(void); // func_80B97194
void func_80B97240(void); // func_80B97240
void func_80B972E8(void); // func_80B972E8
void func_80B973BC(void); // func_80B973BC
void func_80B975F8(void); // func_80B975F8
void func_80B9765C(void); // func_80B9765C
void func_80B97708(void); // func_80B97708
void func_80B9787C(void); // func_80B9787C
void func_80B979DC(void); // func_80B979DC
void func_80B97A44(void); // func_80B97A44
void func_80B97B5C(void); // func_80B97B5C
void func_80B97BF8(void); // func_80B97BF8
void func_80B97C40(void); // func_80B97C40
void func_80B97CC8(void); // func_80B97CC8
void func_80B97D6C(void); // func_80B97D6C
void func_80B97E0C(void); // func_80B97E0C
void func_80B97E4C(void); // func_80B97E4C
void func_80B97FD0(void); // func_80B97FD0
void func_80B980FC(void); // func_80B980FC
void func_80B98178(void); // func_80B98178
void func_80B98348(void); // func_80B98348
void func_80B9849C(void); // func_80B9849C
void func_80B9854C(void); // func_80B9854C
void func_80B985EC(void); // func_80B985EC
void func_80B98728(void); // func_80B98728
void func_80B98998(void); // func_80B98998
void func_80B98A4C(void); // func_80B98A4C
void func_80B98AD0(void); // func_80B98AD0
void func_80B98BF4(void); // func_80B98BF4
void func_80B98CA8(void); // func_80B98CA8
void func_80B98E10(void); // func_80B98E10
void func_80B98F30(void); // func_80B98F30
void func_80B98F94(void); // func_80B98F94
void func_80B990A4(void); // func_80B990A4
void func_80B99160(void); // func_80B99160
void func_80B991E4(void); // func_80B991E4
void func_80B992C0(void); // func_80B992C0
void func_80B99384(void); // func_80B99384
void func_80B99394(void); // func_80B99394
void func_80B99580(void); // func_80B99580
void func_80B995A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80B995A4
void func_80B99758(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80B99758
void func_80B99798(void); // func_80B99798
void func_80B9A0B0(void); // func_80B9A0B0
void func_80B9A1BC(void); // func_80B9A1BC
void func_80B9A20C(void); // func_80B9A20C
void func_80B9A220(void); // func_80B9A220
void func_80B9A230(void); // func_80B9A230
void func_80B9A27C(void); // func_80B9A27C
void func_80B9A348(void); // func_80B9A348
void func_80B9A3E8(void); // func_80B9A3E8
void func_80B9A424(void); // func_80B9A424
void func_80B9A650(void); // func_80B9A650
void func_80B9A6A0(void); // func_80B9A6A0
void func_80B9A6D4(void); // func_80B9A6D4
void func_80B9A8E8(void); // func_80B9A8E8
void func_80B9A980(void); // func_80B9A980
void func_80B9A9EC(void); // func_80B9A9EC
void func_80B9AA20(void); // func_80B9AA20
void func_80B9AA54(void); // func_80B9AA54
void func_80B9AE00(void); // func_80B9AE00
void func_80B9AF50(void); // func_80B9AF50
void func_80B9AFE0(void); // func_80B9AFE0
void func_80B9B0F0(void); // func_80B9B0F0
void func_80B9B124(void); // func_80B9B124
void func_80B9B1B8(void); // func_80B9B1B8
void func_80B9B428(void); // func_80B9B428
void func_80B9B628(void); // func_80B9B628
void func_80B9B6E0(void); // func_80B9B6E0
void func_80B9B74C(void); // func_80B9B74C
void func_80B9B9C8(void); // func_80B9B9C8
void func_80B9BC64(void); // func_80B9BC64
void func_80B9BCBC(void); // func_80B9BCBC
void func_80B9BD84(void); // func_80B9BD84
void func_80B9BDC8(void); // func_80B9BDC8
void func_80B9BF28(void); // func_80B9BF28
void func_80B9BF7C(void); // func_80B9BF7C
void func_80B9C07C(void); // func_80B9C07C
void func_80B9C174(void); // func_80B9C174
void func_80B9C1A0(void); // func_80B9C1A0
void func_80B9C208(void); // func_80B9C208
void func_80B9C2D8(void); // func_80B9C2D8
void func_80B9C450(void); // func_80B9C450
void func_80B9C5E8(void); // func_80B9C5E8
void func_80B9CA04(void); // func_80B9CA04
void func_80B9CAEC(void); // func_80B9CAEC
void func_80B9CD88(void); // func_80B9CD88
void func_80B9CDBC(void); // func_80B9CDBC
void func_80B9CE64(void); // func_80B9CE64
void func_80B9D094(void); // func_80B9D094
void func_80B9D0FC(void); // func_80B9D0FC
void func_80B9D120(void); // func_80B9D120
void func_80B9D288(void); // func_80B9D288
void func_80B9D2BC(void); // func_80B9D2BC
void func_80B9D334(void); // func_80B9D334
void func_80B9D4D0(void); // func_80B9D4D0
void func_80B9D508(void); // func_80B9D508
void func_80B9D714(void); // func_80B9D714
void func_80B9D9C4(void); // func_80B9D9C4
void func_80B9DA60(void); // func_80B9DA60
void func_80B9DEE0(void); // func_80B9DEE0
void func_80B9DFC8(void); // func_80B9DFC8
void func_80B9DFDC(void); // func_80B9DFDC
void func_80B9E030(void); // func_80B9E030
void func_80B9E0D0(void); // func_80B9E0D0
void func_80B9E0FC(void); // func_80B9E0FC
void func_80B9E14C(void); // func_80B9E14C
void func_80B9E2C0(void); // func_80B9E2C0
void func_80B9E3D8(void); // func_80B9E3D8
void func_80B9E418(void); // func_80B9E418
void func_80B9E544(void); // func_80B9E544
void func_80B9E5F4(void); // func_80B9E5F4
void func_80B9E7D0(void); // func_80B9E7D0
void func_80B9E8D4(void); // func_80B9E8D4
void func_80B9EF70(void); // func_80B9EF70
void func_80B9F570(void); // func_80B9F570
void func_80B9F7B8(void); // func_80B9F7B8
void func_80B9F7E4(void); // func_80B9F7E4
void func_80B9F86C(void); // func_80B9F86C
void func_80B9FA3C(void); // func_80B9FA3C
void func_80B9FC0C(void); // func_80B9FC0C
void func_80B9FC70(void); // func_80B9FC70
void func_80B9FCA0(void); // func_80B9FCA0
void func_80B9FD24(void); // func_80B9FD24
void func_80B9FDDC(void); // func_80B9FDDC
void func_80B9FE1C(void); // func_80B9FE1C
void func_80B9FE5C(void); // func_80B9FE5C
void func_80B9FF20(void); // func_80B9FF20
void func_80B9FF80(void); // func_80B9FF80
void func_80BA005C(void); // func_80BA005C
void func_80BA00BC(void); // func_80BA00BC
void func_80BA0318(void); // func_80BA0318
void func_80BA0374(void); // func_80BA0374
void func_80BA0610(void); // func_80BA0610
void func_80BA06BC(void); // func_80BA06BC
void func_80BA0728(void); // func_80BA0728
void func_80BA08E8(void); // func_80BA08E8
void func_80BA09E0(void); // func_80BA09E0
void func_80BA0A04(void); // func_80BA0A04
void func_80BA0AD8(void); // func_80BA0AD8
void func_80BA0BB4(void); // func_80BA0BB4
void func_80BA0C14(void); // func_80BA0C14
void func_80BA0CF4(void); // func_80BA0CF4
void func_80BA0D64(void); // func_80BA0D64
void func_80BA0F64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BA0F64
void func_80BA0FAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BA0FAC
void func_80BA0FEC(void); // func_80BA0FEC
void func_80BA15A0(void); // func_80BA15A0
void func_80BA165C(void); // func_80BA165C
void func_80BA16F4(void); // func_80BA16F4
void func_80BA1854(void); // func_80BA1854
void func_80BA1BF0(void); // func_80BA1BF0
void func_80BA1C00(void); // func_80BA1C00
void func_80BA1C88(void); // func_80BA1C88
void func_80BA1CF8(void); // func_80BA1CF8
void func_80BA1E30(void); // func_80BA1E30
void func_80BA1F80(void); // func_80BA1F80
void func_80BA2038(void); // func_80BA2038
void func_80BA2048(void); // func_80BA2048
void func_80BA215C(void); // func_80BA215C
void func_80BA21C4(void); // func_80BA21C4
void func_80BA22B0(void); // func_80BA22B0
void func_80BA2420(void); // func_80BA2420
void func_80BA242C(void); // func_80BA242C
void func_80BA24DC(void); // func_80BA24DC
void func_80BA2514(void); // func_80BA2514
void func_80BA26A8(void); // func_80BA26A8
void func_80BA2708(void); // func_80BA2708
void func_80BA2790(void); // func_80BA2790
void func_80BA27C4(void); // func_80BA27C4
void func_80BA28DC(void); // func_80BA28DC
void func_80BA2AB4(void); // func_80BA2AB4
void func_80BA2B64(void); // func_80BA2B64
void func_80BA2BA4(void); // func_80BA2BA4
void func_80BA2C28(void); // func_80BA2C28
void func_80BA2C94(void); // func_80BA2C94
void func_80BA3044(void); // func_80BA3044
void func_80BA311C(void); // func_80BA311C
void func_80BA3230(void); // func_80BA3230
void func_80BA3344(void); // func_80BA3344
void func_80BA3410(void); // func_80BA3410
void func_80BA3434(void); // func_80BA3434
void func_80BA36C0(void); // func_80BA36C0
void func_80BA36FC(void); // func_80BA36FC
void func_80BA3810(void); // func_80BA3810
void func_80BA383C(void); // func_80BA383C
void func_80BA3930(void); // func_80BA3930
void func_80BA397C(void); // func_80BA397C
void func_80BA39C8(void); // func_80BA39C8
void func_80BA3BFC(void); // func_80BA3BFC
void func_80BA3C88(void); // func_80BA3C88
void func_80BA3CC4(void); // func_80BA3CC4
void func_80BA3D38(void); // func_80BA3D38
void func_80BA3DBC(void); // func_80BA3DBC
void func_80BA3EC0(void); // func_80BA3EC0
void func_80BA3ED4(void); // func_80BA3ED4
void func_80BA3EE8(void); // func_80BA3EE8
void func_80BA3F2C(void); // func_80BA3F2C
void func_80BA3FB0(void); // func_80BA3FB0
void func_80BA3FCC(void); // func_80BA3FCC
void func_80BA402C(void); // func_80BA402C
void func_80BA407C(void); // func_80BA407C
void func_80BA40D4(void); // func_80BA40D4
void func_80BA4128(void); // func_80BA4128
void func_80BA415C(void); // func_80BA415C
void func_80BA4204(void); // func_80BA4204
void func_80BA42BC(void); // func_80BA42BC
void func_80BA43F4(void); // func_80BA43F4
void func_80BA445C(void); // func_80BA445C
void func_80BA44A0(void); // func_80BA44A0
void func_80BA44D4(void); // func_80BA44D4
void func_80BA4530(void); // func_80BA4530
void func_80BA46D8(void); // func_80BA46D8
void func_80BA4740(void); // func_80BA4740
void func_80BA47E0(void); // func_80BA47E0
void func_80BA49A4(void); // func_80BA49A4
void func_80BA4A00(void); // func_80BA4A00
void func_80BA4B24(void); // func_80BA4B24
void func_80BA4C0C(void); // func_80BA4C0C
void func_80BA4C44(void); // func_80BA4C44
void func_80BA4CB4(void); // func_80BA4CB4
void func_80BA4E2C(void); // func_80BA4E2C
void func_80BA4EFC(void); // func_80BA4EFC
void func_80BA5400(void); // func_80BA5400
void func_80BA5620(void); // func_80BA5620
void func_80BA577C(void); // func_80BA577C
void func_80BA57A8(void); // func_80BA57A8
void func_80BA57F8(void); // func_80BA57F8
void func_80BA59F0(void); // func_80BA59F0
void func_80BA5A34(void); // func_80BA5A34
void func_80BA5AF0(void); // func_80BA5AF0
void func_80BA5B64(void); // func_80BA5B64
void func_80BA5DBC(void); // func_80BA5DBC
void func_80BA5E18(void); // func_80BA5E18
void func_80BA6054(void); // func_80BA6054
void func_80BA60B0(void); // func_80BA60B0
void func_80BA6158(void); // func_80BA6158
void func_80BA61A0(void); // func_80BA61A0
void func_80BA6284(void); // func_80BA6284
void func_80BA62D4(void); // func_80BA62D4
void func_80BA6440(void); // func_80BA6440
void func_80BA64AC(void); // func_80BA64AC
void func_80BA6584(void); // func_80BA6584
void func_80BA6604(void); // func_80BA6604
void func_80BA6664(void); // func_80BA6664
void func_80BA66C8(void); // func_80BA66C8
void func_80BA6800(void); // func_80BA6800
void func_80BA6974(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_80BA6974
void func_80BA6B30(void); // func_80BA6B30
void func_80BA6B9C(void); // func_80BA6B9C
void func_80BA6D10(void); // func_80BA6D10
void func_80BA6DAC(void); // func_80BA6DAC
void func_80BA6DF8(void); // func_80BA6DF8
void func_80BA7088(void); // func_80BA7088
void func_80BA71E4(void); // func_80BA71E4
void func_80BA7234(void); // func_80BA7234
void func_80BA7388(void); // func_80BA7388
void func_80BA7434(void); // func_80BA7434
void func_80BA7578(void); // func_80BA7578
void func_80BA76C4(void); // func_80BA76C4
void func_80BA77A0(void); // func_80BA77A0
void func_80BA7878(void); // func_80BA7878
UNK_TYPE4 func_80BA789C(UNK_TYPE4 param_1, s32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, s32 param_5, s32 param_6); // func_80BA789C
void func_80BA78F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BA78F8
void func_80BA79D4(void); // func_80BA79D4
void func_80BA7B6C(void); // func_80BA7B6C
void func_80BA7C78(void); // func_80BA7C78
void func_80BA7CF0(void); // func_80BA7CF0
void func_80BA7D04(void); // func_80BA7D04
void func_80BA7D14(void); // func_80BA7D14
void func_80BA7D30(void); // func_80BA7D30
void func_80BA7DC8(void); // func_80BA7DC8
void func_80BA8050(void); // func_80BA8050
void func_80BA8820(void); // func_80BA8820
void func_80BA886C(void); // func_80BA886C
void func_80BA8C4C(void); // func_80BA8C4C
void func_80BA8C90(void); // func_80BA8C90
void func_80BA8D2C(void); // func_80BA8D2C
void func_80BA8DF4(void); // func_80BA8DF4
void func_80BA8F88(void); // func_80BA8F88
void func_80BA9110(void); // func_80BA9110
void func_80BA9160(void); // func_80BA9160
void func_80BA93AC(void); // func_80BA93AC
void func_80BA9480(void); // func_80BA9480
void func_80BA9758(void); // func_80BA9758
void func_80BA9848(void); // func_80BA9848
void func_80BA98EC(void); // func_80BA98EC
void func_80BA9AB8(void); // func_80BA9AB8
void func_80BA9B24(void); // func_80BA9B24
void func_80BA9B80(void); // func_80BA9B80
void func_80BA9CD4(void); // func_80BA9CD4
void func_80BA9E00(void); // func_80BA9E00
void func_80BA9E10(void); // func_80BA9E10
void func_80BA9E48(void); // func_80BA9E48
void func_80BA9E6C(void); // func_80BA9E6C
void func_80BA9F24(void); // func_80BA9F24
void func_80BA9F50(void); // func_80BA9F50
void func_80BA9FB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BA9FB0
void func_80BAA198(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BAA198
void func_80BAA20C(void); // func_80BAA20C
void func_80BAA220(void); // func_80BAA220
void func_80BAA6D0(void); // func_80BAA6D0
void func_80BAA848(void); // func_80BAA848
void func_80BAA88C(void); // func_80BAA88C
void func_80BAA8D0(void); // func_80BAA8D0
void func_80BAA904(void); // func_80BAA904
void func_80BAA9B4(void); // func_80BAA9B4
void func_80BAAA34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80BAAA34
void func_80BAAA94(void); // func_80BAAA94
void func_80BAAB78(void); // func_80BAAB78
void func_80BAAF1C(void); // func_80BAAF1C
void func_80BAAFDC(void); // func_80BAAFDC
void func_80BAB1A0(void); // func_80BAB1A0
void func_80BAB374(void); // func_80BAB374
void func_80BAB434(void); // func_80BAB434
void func_80BAB490(void); // func_80BAB490
void func_80BAB4F0(void); // func_80BAB4F0
void func_80BAB698(void); // func_80BAB698
void func_80BAB758(void); // func_80BAB758
void func_80BAB8F4(void); // func_80BAB8F4
void func_80BABA90(void); // func_80BABA90
void func_80BABB90(void); // func_80BABB90
void func_80BABC48(void); // func_80BABC48
void func_80BABDD8(void); // func_80BABDD8
void func_80BABF64(void); // func_80BABF64
void func_80BABFD4(void); // func_80BABFD4
void func_80BAC220(void); // func_80BAC220
void func_80BAC2FC(void); // func_80BAC2FC
void func_80BAC6E8(void); // func_80BAC6E8
void func_80BACA14(void); // func_80BACA14
void func_80BACBB0(void); // func_80BACBB0
void func_80BACD2C(void); // func_80BACD2C
void func_80BACE4C(void); // func_80BACE4C
void func_80BACEE0(void); // func_80BACEE0
void func_80BAD004(void); // func_80BAD004
void func_80BAD130(void); // func_80BAD130
void func_80BAD230(void); // func_80BAD230
void func_80BAD2B4(void); // func_80BAD2B4
void func_80BAD380(void); // func_80BAD380
void func_80BAD5F8(void); // func_80BAD5F8
void func_80BAD7F8(void); // func_80BAD7F8
void func_80BADA08(void); // func_80BADA08
void func_80BADA9C(void); // func_80BADA9C
void func_80BADD0C(void); // func_80BADD0C
void func_80BADDB4(void); // func_80BADDB4
void func_80BADE14(void); // func_80BADE14
void func_80BADE8C(void); // func_80BADE8C
void func_80BADF3C(void); // func_80BADF3C
void func_80BADFD0(void); // func_80BADFD0
void func_80BAE0A0(void); // func_80BAE0A0
void func_80BAE108(void); // func_80BAE108
void func_80BAE250(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BAE250
void func_80BAE3C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BAE3C4
void func_80BAE524(void); // func_80BAE524
void func_80BAE538(void); // func_80BAE538
void func_80BAEF70(void); // func_80BAEF70
void func_80BAF1C0(void); // func_80BAF1C0
void func_80BAF1EC(void); // func_80BAF1EC
void func_80BAF2B4(void); // func_80BAF2B4
void func_80BAF338(void); // func_80BAF338
void func_80BAF3E0(void); // func_80BAF3E0
void func_80BAF4D8(void); // func_80BAF4D8
void func_80BAF7CC(void); // func_80BAF7CC
void func_80BAF99C(void); // func_80BAF99C
void func_80BAFA44(void); // func_80BAFA44
void func_80BAFADC(void); // func_80BAFADC
void func_80BAFB84(void); // func_80BAFB84
void func_80BAFC00(void); // func_80BAFC00
void func_80BAFC10(void); // func_80BAFC10
void func_80BAFD00(void); // func_80BAFD00
void func_80BAFDB4(void); // func_80BAFDB4
void func_80BAFE34(void); // func_80BAFE34
void func_80BAFF14(void); // func_80BAFF14
void func_80BAFF84(void); // func_80BAFF84
void func_80BB0128(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BB0128
void func_80BB0170(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BB0170
void func_80BB01B0(void); // func_80BB01B0
void func_80BB03E8(void); // func_80BB03E8
void func_80BB08E0(void); // func_80BB08E0
void func_80BB0998(void); // func_80BB0998
void func_80BB09A8(void); // func_80BB09A8
void func_80BB09BC(void); // func_80BB09BC
void func_80BB0B28(void); // func_80BB0B28
void func_80BB0BF8(void); // func_80BB0BF8
void func_80BB0E44(void); // func_80BB0E44
void func_80BB0E58(void); // func_80BB0E58
void func_80BB0F24(void); // func_80BB0F24
void func_80BB0F38(void); // func_80BB0F38
void func_80BB0F94(void); // func_80BB0F94
void func_80BB0FA8(void); // func_80BB0FA8
void func_80BB0FF8(void); // func_80BB0FF8
void func_80BB1088(void); // func_80BB1088
void func_80BB10F8(void); // func_80BB10F8
void func_80BB1168(void); // func_80BB1168
void func_80BB1180(void); // func_80BB1180
void func_80BB1250(void); // func_80BB1250
void func_80BB1268(void); // func_80BB1268
void func_80BB1338(void); // func_80BB1338
void func_80BB135C(void); // func_80BB135C
void func_80BB16D0(void); // func_80BB16D0
void func_80BB178C(void); // func_80BB178C
void func_80BB18FC(void); // func_80BB18FC
void func_80BB19C0(void); // func_80BB19C0
void func_80BB1B14(void); // func_80BB1B14
void func_80BB1C1C(void); // func_80BB1C1C
void func_80BB1C8C(void); // func_80BB1C8C
void func_80BB1D04(void); // func_80BB1D04
void func_80BB1D64(void); // func_80BB1D64
void func_80BB1FCC(void); // func_80BB1FCC
void func_80BB2020(void); // func_80BB2020
void func_80BB2088(void); // func_80BB2088
void func_80BB217C(void); // func_80BB217C
void func_80BB221C(void); // func_80BB221C
void func_80BB2520(void); // func_80BB2520
void func_80BB26EC(void); // func_80BB26EC
void func_80BB27D4(void); // func_80BB27D4
void func_80BB2944(void); // func_80BB2944
void func_80BB2A54(void); // func_80BB2A54
void func_80BB2B1C(void); // func_80BB2B1C
void func_80BB2E00(void); // func_80BB2E00
void func_80BB2F7C(void); // func_80BB2F7C
void func_80BB30B4(void); // func_80BB30B4
void func_80BB31B8(void); // func_80BB31B8
void func_80BB32AC(void); // func_80BB32AC
void func_80BB3318(void); // func_80BB3318
void func_80BB347C(void); // func_80BB347C
void func_80BB34BC(void); // func_80BB34BC
void func_80BB3650(void); // func_80BB3650
void func_80BB36A0(void); // func_80BB36A0
void func_80BB3728(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BB3728
void func_80BB3860(void); // func_80BB3860
void func_80BB387C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BB387C
void func_80BB39F8(void); // func_80BB39F8
void func_80BB3BE0(void); // func_80BB3BE0
void func_80BB3CB4(void); // func_80BB3CB4
void func_80BB3E0C(void); // func_80BB3E0C
void func_80BB4700(void); // func_80BB4700
void func_80BB4720(void); // func_80BB4720
void func_80BB4730(void); // func_80BB4730
void func_80BB48E4(void); // func_80BB48E4
void func_80BB4AF0(void); // func_80BB4AF0
void func_80BB4B6C(void); // func_80BB4B6C
void func_80BB4BA0(void); // func_80BB4BA0
void func_80BB4CB0(void); // func_80BB4CB0
void func_80BB4E00(void); // func_80BB4E00
void func_80BB4E40(void); // func_80BB4E40
void func_80BB4E50(void); // func_80BB4E50
void func_80BB4F28(void); // func_80BB4F28
void func_80BB52F8(void); // func_80BB52F8
void func_80BB5318(void); // func_80BB5318
void func_80BB5AAC(void); // func_80BB5AAC
void func_80BB67D0(void); // func_80BB67D0
void func_80BB69B0(void); // func_80BB69B0
void func_80BB69C0(void); // func_80BB69C0
void func_80BB69FC(void); // func_80BB69FC
void func_80BB6B80(void); // func_80BB6B80
void func_80BB6BD8(void); // func_80BB6BD8
void func_80BB6F64(void); // func_80BB6F64
void func_80BB6F78(void); // func_80BB6F78
void func_80BB71C8(void); // func_80BB71C8
void func_80BB7398(void); // func_80BB7398
void func_80BB7408(void); // func_80BB7408
void func_80BB7578(void); // func_80BB7578
void func_80BB7800(void); // func_80BB7800
void func_80BB7B90(void); // func_80BB7B90
void func_80BB7C14(void); // func_80BB7C14
void func_80BB85A0(void); // func_80BB85A0
void func_80BB86BC(void); // func_80BB86BC
void func_80BB87B0(void); // func_80BB87B0
void func_80BB87D4(void); // func_80BB87D4
void func_80BB897C(void); // func_80BB897C
void func_80BB8A48(void); // func_80BB8A48
void func_80BB91D4(void); // func_80BB91D4
void func_80BB9288(void); // func_80BB9288
void func_80BB9308(void); // func_80BB9308
void func_80BB93EC(void); // func_80BB93EC
void func_80BB95FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BB95FC
void func_80BB9670(void); // func_80BB9670
void func_80BB98E0(void); // func_80BB98E0
void func_80BB99F0(void); // func_80BB99F0
void func_80BB9A1C(void); // func_80BB9A1C
void func_80BB9B40(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80BB9B40
void func_80BB9C08(void); // func_80BB9C08
void func_80BB9F24(void); // func_80BB9F24
void func_80BBA2FC(void); // func_80BBA2FC
void func_80BBA314(void); // func_80BBA314
void func_80BBA488(void); // func_80BBA488
void func_80BBA738(void); // func_80BBA738
void func_80BBA78C(void); // func_80BBA78C
void func_80BBA894(void); // func_80BBA894
void func_80BBA930(void); // func_80BBA930
void func_80BBACA0(void); // func_80BBACA0
void func_80BBAE60(void); // func_80BBAE60
void func_80BBAE84(void); // func_80BBAE84
void func_80BBAF5C(void); // func_80BBAF5C
void func_80BBAFFC(void); // func_80BBAFFC
void func_80BBB0D4(void); // func_80BBB0D4
void func_80BBB15C(void); // func_80BBB15C
void func_80BBB2C4(void); // func_80BBB2C4
void func_80BBB354(void); // func_80BBB354
void func_80BBB414(void); // func_80BBB414
void func_80BBB4CC(void); // func_80BBB4CC
void func_80BBB574(void); // func_80BBB574
void func_80BBB718(void); // func_80BBB718
void func_80BBB8AC(void); // func_80BBB8AC
void func_80BBBB84(void); // func_80BBBB84
void func_80BBBCBC(void); // func_80BBBCBC
void func_80BBBD5C(void); // func_80BBBD5C
void func_80BBBDE0(void); // func_80BBBDE0
void func_80BBBFBC(void); // func_80BBBFBC
void func_80BBC070(void); // func_80BBC070
void func_80BBC14C(void); // func_80BBC14C
void func_80BBC22C(void); // func_80BBC22C
void func_80BBC24C(void); // func_80BBC24C
void func_80BBC298(void); // func_80BBC298
void func_80BBC37C(void); // func_80BBC37C
void func_80BBC3F0(void); // func_80BBC3F0
void func_80BBC4E4(void); // func_80BBC4E4
void func_80BBC500(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BBC500
void func_80BBC540(void); // func_80BBC540
void func_80BBCA80(void); // func_80BBCA80
void func_80BBD348(void); // func_80BBD348
void func_80BBD8F0(void); // func_80BBD8F0
void func_80BBD93C(void); // func_80BBD93C
void func_80BBD98C(void); // func_80BBD98C
void func_80BBDACC(void); // func_80BBDACC
void func_80BBDC34(void); // func_80BBDC34
void func_80BBDCFC(void); // func_80BBDCFC
void func_80BBDDF8(void); // func_80BBDDF8
void func_80BBDE78(void); // func_80BBDE78
void func_80BBDF28(void); // func_80BBDF28
void func_80BBDFA8(void); // func_80BBDFA8
void func_80BBE05C(void); // func_80BBE05C
void func_80BBE0E4(void); // func_80BBE0E4
void func_80BBE144(void); // func_80BBE144
void func_80BBE374(void); // func_80BBE374
void func_80BBE498(void); // func_80BBE498
void func_80BBE73C(void); // func_80BBE73C
void func_80BBE844(void); // func_80BBE844
void func_80BBE904(void); // func_80BBE904
void func_80BBE9F8(void); // func_80BBE9F8
void func_80BBEAD8(void); // func_80BBEAD8
void func_80BBEBF8(void); // func_80BBEBF8
void func_80BBECBC(void); // func_80BBECBC
void func_80BBEEB4(void); // func_80BBEEB4
void func_80BBEF34(void); // func_80BBEF34
void func_80BBEFA0(void); // func_80BBEFA0
void func_80BBF01C(void); // func_80BBF01C
void func_80BBF09C(void); // func_80BBF09C
void func_80BBF198(void); // func_80BBF198
void func_80BBF1C4(void); // func_80BBF1C4
void func_80BBF298(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BBF298
void func_80BBF3D0(void); // func_80BBF3D0
void func_80BBF3EC(void); // func_80BBF3EC
void func_80BBF5F0(void); // func_80BBF5F0
void func_80BBF6BC(void); // func_80BBF6BC
void func_80BBF7BC(void); // func_80BBF7BC
void func_80BBFDB0(void); // func_80BBFDB0
void func_80BBFE60(void); // func_80BBFE60
void func_80BBFE8C(void); // func_80BBFE8C
void func_80BBFF24(void); // func_80BBFF24
void func_80BBFF90(void); // func_80BBFF90
void func_80BBFFD4(void); // func_80BBFFD4
void func_80BC0050(void); // func_80BC0050
void func_80BC00AC(void); // func_80BC00AC
void func_80BC01DC(void); // func_80BC01DC
void func_80BC045C(void); // func_80BC045C
void func_80BC04FC(void); // func_80BC04FC
void func_80BC05A8(void); // func_80BC05A8
void func_80BC06C4(void); // func_80BC06C4
void func_80BC0800(void); // func_80BC0800
void func_80BC08E0(void); // func_80BC08E0
void func_80BC0978(void); // func_80BC0978
void func_80BC0A18(void); // func_80BC0A18
void func_80BC0B98(void); // func_80BC0B98
void func_80BC0C0C(void); // func_80BC0C0C
void func_80BC0C80(void); // func_80BC0C80
void func_80BC0D08(void); // func_80BC0D08
void func_80BC0D1C(void); // func_80BC0D1C
void func_80BC0D84(void); // func_80BC0D84
void func_80BC0EAC(void); // func_80BC0EAC
void func_80BC0F60(void); // func_80BC0F60
void func_80BC1080(void); // func_80BC1080
void func_80BC10C0(void); // func_80BC10C0
void func_80BC1174(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80BC1174
void func_80BC11B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BC11B4
void func_80BC1278(void); // func_80BC1278
void func_80BC1374(void); // func_80BC1374
void func_80BC1900(void); // func_80BC1900
void func_80BC192C(void); // func_80BC192C
void func_80BC1984(void); // func_80BC1984
void func_80BC19FC(void); // func_80BC19FC
void func_80BC1A68(void); // func_80BC1A68
void func_80BC1AE0(void); // func_80BC1AE0
void func_80BC1B50(void); // func_80BC1B50
void func_80BC1B60(void); // func_80BC1B60
void func_80BC1D70(void); // func_80BC1D70
void func_80BC1E40(void); // func_80BC1E40
void func_80BC1FC8(void); // func_80BC1FC8
void func_80BC203C(void); // func_80BC203C
void func_80BC20D0(void); // func_80BC20D0
void func_80BC213C(void); // func_80BC213C
void func_80BC2150(void); // func_80BC2150
void func_80BC21A8(void); // func_80BC21A8
void func_80BC2274(void); // func_80BC2274
void func_80BC22F4(void); // func_80BC22F4
void func_80BC2388(void); // func_80BC2388
void func_80BC2498(void); // func_80BC2498
void func_80BC24C4(void); // func_80BC24C4
void func_80BC25E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80BC25E0
void func_80BC2620(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BC2620
void func_80BC2B30(void); // func_80BC2B30
void func_80BC2CE4(void); // func_80BC2CE4
void func_80BC2EA4(void); // func_80BC2EA4
void func_80BC3154(void); // func_80BC3154
void func_80BC32D8(void); // func_80BC32D8
void func_80BC33C0(void); // func_80BC33C0
void func_80BC3594(void); // func_80BC3594
void func_80BC3980(void); // func_80BC3980
void func_80BC3A2C(void); // func_80BC3A2C
void func_80BC3B00(void); // func_80BC3B00
void func_80BC3CA4(void); // func_80BC3CA4
void func_80BC3D08(void); // func_80BC3D08
void func_80BC4038(void); // func_80BC4038
void func_80BC4058(void); // func_80BC4058
void func_80BC4178(void); // func_80BC4178
void func_80BC41AC(void); // func_80BC41AC
void func_80BC4228(Actor* param_1, UNK_TYPE4 param_2); // func_80BC4228
void func_80BC4344(void); // func_80BC4344
void func_80BC4380(void); // func_80BC4380
void func_80BC43CC(void); // func_80BC43CC
void func_80BC4448(void); // func_80BC4448
void func_80BC44F4(void); // func_80BC44F4
void func_80BC4530(void); // func_80BC4530
void func_80BC457C(void); // func_80BC457C
void func_80BC458C(void); // func_80BC458C
void func_80BC45CC(void); // func_80BC45CC
void func_80BC47B0(void); // func_80BC47B0
void func_80BC4A3C(void); // func_80BC4A3C
void func_80BC4AEC(void); // func_80BC4AEC
void func_80BC4B20(void); // func_80BC4B20
void func_80BC4B94(void); // func_80BC4B94
void func_80BC4BB8(void); // func_80BC4BB8
void func_80BC4C68(void); // func_80BC4C68
void func_80BC4D30(void); // func_80BC4D30
void func_80BC4D54(void); // func_80BC4D54
void func_80BC4D90(void); // func_80BC4D90
void func_80BC4F30(void); // func_80BC4F30
void func_80BC51F8(void); // func_80BC51F8
void func_80BC5250(void); // func_80BC5250
void func_80BC5294(void); // func_80BC5294
void func_80BC52D4(void); // func_80BC52D4
void func_80BC52F0(void); // func_80BC52F0
void func_80BC538C(void); // func_80BC538C
void func_80BC53A0(void); // func_80BC53A0
void func_80BC53B0(void); // func_80BC53B0
void func_80BC5404(void); // func_80BC5404
void func_80BC552C(void); // func_80BC552C
void func_80BC5570(void); // func_80BC5570
void func_80BC5580(void); // func_80BC5580
void func_80BC55E0(void); // func_80BC55E0
void func_80BC562C(void); // func_80BC562C
void func_80BC5670(void); // func_80BC5670
void func_80BC5680(void); // func_80BC5680
void func_80BC56D0(void); // func_80BC56D0
void func_80BC5738(void); // func_80BC5738
void func_80BC5780(void); // func_80BC5780
void func_80BC57E8(void); // func_80BC57E8
void func_80BC5830(void); // func_80BC5830
void func_80BC5898(void); // func_80BC5898
void func_80BC58E0(void); // func_80BC58E0
void func_80BC59BC(void); // func_80BC59BC
void func_80BC59EC(void); // func_80BC59EC
void func_80BC5CC8(void); // func_80BC5CC8
void func_80BC5D34(void); // func_80BC5D34
void func_80BC5DEC(void); // func_80BC5DEC
void func_80BC5FE8(void); // func_80BC5FE8
void func_80BC6048(void); // func_80BC6048
void func_80BC60BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_80BC60BC
void func_80BC617C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BC617C
void func_80BC61D0(void); // func_80BC61D0
void func_80BC6BF0(void); // func_80BC6BF0
void func_80BC6D28(void); // func_80BC6D28
void func_80BC6D64(void); // func_80BC6D64
void func_80BC6E00(void); // func_80BC6E00
void func_80BC6E10(void); // func_80BC6E10
void func_80BC6F14(void); // func_80BC6F14
void func_80BC701C(void); // func_80BC701C
void func_80BC7068(void); // func_80BC7068
void func_80BC73F4(void); // func_80BC73F4
void func_80BC7440(void); // func_80BC7440
void func_80BC7520(void); // func_80BC7520
void func_80BC7590(void); // func_80BC7590
void func_80BC77EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BC77EC
void func_80BC7834(void); // func_80BC7834
void func_80BC7AD0(void); // func_80BC7AD0
void func_80BC7B28(void); // func_80BC7B28
void func_80BC7B5C(void); // func_80BC7B5C
void func_80BC7BBC(void); // func_80BC7BBC
void func_80BC9270(void); // func_80BC9270
void func_80BC9330(void); // func_80BC9330
void func_80BC935C(void); // func_80BC935C
void func_80BC941C(void); // func_80BC941C
void func_80BC94B0(void); // func_80BC94B0
void func_80BC9560(void); // func_80BC9560
void func_80BC9660(void); // func_80BC9660
void func_80BC9680(void); // func_80BC9680
void func_80BC98EC(void); // func_80BC98EC
void func_80BC9908(void); // func_80BC9908
void func_80BC9A10(void); // func_80BC9A10
void func_80BC9A2C(void); // func_80BC9A2C
void func_80BC9C88(void); // func_80BC9C88
void func_80BC9D28(void); // func_80BC9D28
void func_80BC9E50(void); // func_80BC9E50
void func_80BC9EE4(void); // func_80BC9EE4
void func_80BCA0AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BCA0AC
void func_80BCA104(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BCA104
void func_80BCA2AC(void); // func_80BCA2AC
void func_80BCA5A0(void); // func_80BCA5A0
void func_80BCA5F8(void); // func_80BCA5F8
void func_80BCA62C(void); // func_80BCA62C
void func_80BCA68C(void); // func_80BCA68C
void func_80BCABF0(void); // func_80BCABF0
void func_80BCAC40(void); // func_80BCAC40
void func_80BCAD64(void); // func_80BCAD64
void func_80BCAE78(void); // func_80BCAE78
void func_80BCAF0C(void); // func_80BCAF0C
void func_80BCAFA8(void); // func_80BCAFA8
void func_80BCB078(void); // func_80BCB078
void func_80BCB1C8(void); // func_80BCB1C8
void func_80BCB230(void); // func_80BCB230
void func_80BCB4DC(void); // func_80BCB4DC
void func_80BCB52C(void); // func_80BCB52C
void func_80BCB6D0(void); // func_80BCB6D0
void func_80BCB90C(void); // func_80BCB90C
void func_80BCB980(void); // func_80BCB980
void func_80BCBA00(void); // func_80BCBA00
void func_80BCBC60(void); // func_80BCBC60
void func_80BCBD28(void); // func_80BCBD28
void func_80BCBF0C(void); // func_80BCBF0C
void func_80BCBFFC(void); // func_80BCBFFC
void func_80BCC288(void); // func_80BCC288
void func_80BCC2AC(void); // func_80BCC2AC
void func_80BCC448(void); // func_80BCC448
void func_80BCC508(void); // func_80BCC508
void func_80BCC77C(void); // func_80BCC77C
void func_80BCC7A8(void); // func_80BCC7A8
UNK_TYPE4 func_80BCC828(UNK_TYPE4 param_1, s32 param_2, UNK_PTR param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, s32 param_6); // func_80BCC828
void func_80BCC9CC(void); // func_80BCC9CC
void func_80BCC9E4(void); // func_80BCC9E4
void func_80BCCAAC(void); // func_80BCCAAC
void func_80BCD000(void); // func_80BCD000
void func_80BCD09C(void); // func_80BCD09C
void func_80BCD1AC(void); // func_80BCD1AC
void func_80BCD2BC(void); // func_80BCD2BC
void func_80BCD334(void); // func_80BCD334
void func_80BCD4D0(void); // func_80BCD4D0
void func_80BCD590(void); // func_80BCD590
void func_80BCD640(void); // func_80BCD640
void func_80BCD7A0(void); // func_80BCD7A0
void func_80BCDA8C(void); // func_80BCDA8C
void func_80BCDAB8(void); // func_80BCDAB8
void func_80BCDB00(void); // func_80BCDB00
void func_80BCDCB0(void); // func_80BCDCB0
void func_80BCDD08(void); // func_80BCDD08
void func_80BCDD3C(void); // func_80BCDD3C
void func_80BCDD9C(void); // func_80BCDD9C
void func_80BCEB20(void); // func_80BCEB20
void func_80BCEBB0(void); // func_80BCEBB0
void func_80BCEBC0(void); // func_80BCEBC0
void func_80BCEC6C(void); // func_80BCEC6C
void func_80BCED34(void); // func_80BCED34
void func_80BCEDE0(void); // func_80BCEDE0
void func_80BCEE98(void); // func_80BCEE98
void func_80BCEEBC(void); // func_80BCEEBC
void func_80BCEF0C(void); // func_80BCEF0C
void func_80BCF1D0(void); // func_80BCF1D0
void func_80BCF328(void); // func_80BCF328
void func_80BCF354(void); // func_80BCF354
void func_80BCF398(void); // func_80BCF398
void func_80BCF468(void); // func_80BCF468
void func_80BCF4AC(void); // func_80BCF4AC
void func_80BCF5F0(void); // func_80BCF5F0
void func_80BCF634(void); // func_80BCF634
void func_80BCF68C(void); // func_80BCF68C
void func_80BCF6D0(void); // func_80BCF6D0
void func_80BCF710(void); // func_80BCF710
void func_80BCF778(void); // func_80BCF778
void func_80BCF7D8(void); // func_80BCF7D8
void func_80BCF88C(void); // func_80BCF88C
void func_80BCF8A0(void); // func_80BCF8A0
void func_80BCF93C(void); // func_80BCF93C
void func_80BCF95C(void); // func_80BCF95C
void func_80BCFC0C(void); // func_80BCFC0C
void func_80BCFDC4(void); // func_80BCFDC4
void func_80BCFE54(void); // func_80BCFE54
void func_80BCFE70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BCFE70
void func_80BCFEC4(void); // func_80BCFEC4
void func_80BD02B0(void); // func_80BD02B0
void func_80BD03C0(void); // func_80BD03C0
void func_80BD03EC(void); // func_80BD03EC
void func_80BD0410(void); // func_80BD0410
void func_80BD0420(void); // func_80BD0420
void func_80BD0434(void); // func_80BD0434
void func_80BD049C(void); // func_80BD049C
void func_80BD04E0(void); // func_80BD04E0
void func_80BD064C(void); // func_80BD064C
void func_80BD0660(void); // func_80BD0660
void func_80BD06FC(void); // func_80BD06FC
void func_80BD0898(void); // func_80BD0898
void func_80BD0B8C(void); // func_80BD0B8C
void func_80BD0C30(void); // func_80BD0C30
void func_80BD0CF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BD0CF0
void func_80BD0D38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BD0D38
void func_80BD0D7C(void); // func_80BD0D7C
void func_80BD11E0(void); // func_80BD11E0
void func_80BD13B0(void); // func_80BD13B0
void func_80BD13DC(void); // func_80BD13DC
void func_80BD1440(void); // func_80BD1440
void func_80BD1470(void); // func_80BD1470
void func_80BD1570(void); // func_80BD1570
void func_80BD15A4(void); // func_80BD15A4
void func_80BD160C(void); // func_80BD160C
void func_80BD1764(void); // func_80BD1764
void func_80BD187C(void); // func_80BD187C
void func_80BD19FC(void); // func_80BD19FC
void func_80BD1AE0(void); // func_80BD1AE0
void func_80BD1BF0(void); // func_80BD1BF0
void func_80BD1C38(void); // func_80BD1C38
void func_80BD1C84(void); // func_80BD1C84
void func_80BD1D30(void); // func_80BD1D30
void func_80BD1D94(void); // func_80BD1D94
void func_80BD1DB8(void); // func_80BD1DB8
void func_80BD1F1C(void); // func_80BD1F1C
void func_80BD1FC8(void); // func_80BD1FC8
void func_80BD20B4(void); // func_80BD20B4
UNK_TYPE4 func_80BD2380(UNK_TYPE4 param_1, s32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, s16* param_5, s32 param_6); // func_80BD2380
void func_80BD2404(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BD2404
void func_80BD24B4(void); // func_80BD24B4
void func_80BD2A30(void); // func_80BD2A30
void func_80BD2AE0(void); // func_80BD2AE0
void func_80BD2B0C(void); // func_80BD2B0C
void func_80BD2BA4(void); // func_80BD2BA4
void func_80BD2BE8(void); // func_80BD2BE8
void func_80BD2C6C(void); // func_80BD2C6C
void func_80BD2DA0(void); // func_80BD2DA0
void func_80BD2DC8(void); // func_80BD2DC8
void func_80BD2FD0(void); // func_80BD2FD0
void func_80BD30C0(void); // func_80BD30C0
void func_80BD3118(void); // func_80BD3118
void func_80BD3198(void); // func_80BD3198
void func_80BD3294(void); // func_80BD3294
void func_80BD3320(void); // func_80BD3320
void func_80BD3374(void); // func_80BD3374
void func_80BD33FC(void); // func_80BD33FC
void func_80BD3484(void); // func_80BD3484
void func_80BD3548(void); // func_80BD3548
void func_80BD35BC(void); // func_80BD35BC
void func_80BD3658(void); // func_80BD3658
void func_80BD36B8(void); // func_80BD36B8
void func_80BD3768(void); // func_80BD3768
void func_80BD3854(void); // func_80BD3854
void func_80BD396C(void); // func_80BD396C
void func_80BD3998(void); // func_80BD3998
void func_80BD3AA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BD3AA8
void func_80BD3AF8(void); // func_80BD3AF8
void func_80BD3CAC(void); // func_80BD3CAC
void func_80BD4090(void); // func_80BD4090
void func_80BD40D0(void); // func_80BD40D0
void func_80BD4108(void); // func_80BD4108
void func_80BD41B4(void); // func_80BD41B4
void func_80BD41E8(void); // func_80BD41E8
void func_80BD41FC(void); // func_80BD41FC
void func_80BD42AC(void); // func_80BD42AC
void func_80BD42C0(void); // func_80BD42C0
void func_80BD433C(void); // func_80BD433C
void func_80BD4358(void); // func_80BD4358
void func_80BD4460(void); // func_80BD4460
void func_80BD4478(void); // func_80BD4478
void func_80BD44D0(void); // func_80BD44D0
void func_80BD4500(void); // func_80BD4500
void func_80BD4540(void); // func_80BD4540
void func_80BD4570(void); // func_80BD4570
void func_80BD4720(void); // func_80BD4720
void func_80BD4A14(void); // func_80BD4A14
void func_80BD4CF4(void); // func_80BD4CF4
void func_80BD4DFC(void); // func_80BD4DFC
void func_80BD4E44(void); // func_80BD4E44
void func_80BD4EAC(void); // func_80BD4EAC
void func_80BD4F18(void); // func_80BD4F18
void func_80BD4F2C(void); // func_80BD4F2C
void func_80BD4F88(void); // func_80BD4F88
void func_80BD4F9C(void); // func_80BD4F9C
void func_80BD4FF8(void); // func_80BD4FF8
void func_80BD503C(void); // func_80BD503C
void func_80BD5118(void); // func_80BD5118
void func_80BD5134(void); // func_80BD5134
void func_80BD51DC(void); // func_80BD51DC
void func_80BD5200(void); // func_80BD5200
void BgIkanaRay_Init(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD53C0
void BgIkanaRay_Fini(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD546C
void BgIkanaRay_SetDeactivated(ActorBgIkanaRay* this); // func_80BD5498
void BgIkanaRay_UpdateCheckForActivation(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD54BC
void BgIkanaRay_SetActivated(ActorBgIkanaRay* this); // func_80BD5500
void BgIkanaRay_UpdateActivated(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD5530
void BgIkanaRay_Main(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD556C
void BgIkanaRay_Draw(ActorBgIkanaRay* this, GlobalContext* ctxt); // func_80BD5590
void func_80BD5690(void); // func_80BD5690
void func_80BD5728(void); // func_80BD5728
void func_80BD57F4(void); // func_80BD57F4
void func_80BD5828(void); // func_80BD5828
void func_80BD5844(void); // func_80BD5844
void func_80BD5878(void); // func_80BD5878
void func_80BD5894(void); // func_80BD5894
void func_80BD58F0(void); // func_80BD58F0
void func_80BD5910(void); // func_80BD5910
void func_80BD599C(void); // func_80BD599C
void func_80BD59C4(void); // func_80BD59C4
void func_80BD59F8(void); // func_80BD59F8
void func_80BD5A18(void); // func_80BD5A18
void func_80BD5AE8(void); // func_80BD5AE8
void func_80BD5B04(void); // func_80BD5B04
void func_80BD5B44(void); // func_80BD5B44
void func_80BD5B60(void); // func_80BD5B60
void func_80BD5BC4(void); // func_80BD5BC4
void func_80BD5BD8(void); // func_80BD5BD8
void func_80BD5C64(void); // func_80BD5C64
void func_80BD5C8C(void); // func_80BD5C8C
void func_80BD5C9C(void); // func_80BD5C9C
void func_80BD5CC0(void); // func_80BD5CC0
void func_80BD5E00(void); // func_80BD5E00
void func_80BD5E6C(void); // func_80BD5E6C
void func_80BD6160(void); // func_80BD6160
void func_80BD6218(void); // func_80BD6218
void func_80BD6260(void); // func_80BD6260
void func_80BD6274(void); // func_80BD6274
void func_80BD62D0(void); // func_80BD62D0
void func_80BD6314(void); // func_80BD6314
void func_80BD63B4(void); // func_80BD63B4
void func_80BD63D0(void); // func_80BD63D0
void func_80BD6420(void); // func_80BD6420
void func_80BD6444(void); // func_80BD6444
void func_80BD6580(void); // func_80BD6580
void func_80BD65F0(void); // func_80BD65F0
void func_80BD6624(void); // func_80BD6624
void func_80BD6638(void); // func_80BD6638
void func_80BD66AC(void); // func_80BD66AC
void func_80BD6754(void); // func_80BD6754
void func_80BD6768(void); // func_80BD6768
void func_80BD67A8(void); // func_80BD67A8
void func_80BD67BC(void); // func_80BD67BC
void func_80BD67CC(void); // func_80BD67CC
void func_80BD6844(void); // func_80BD6844
void func_80BD6910(void); // func_80BD6910
void func_80BD697C(void); // func_80BD697C
void func_80BD6A8C(void); // func_80BD6A8C
void func_80BD6B18(void); // func_80BD6B18
void func_80BD6BE8(void); // func_80BD6BE8
void func_80BD6CB0(void); // func_80BD6CB0
void func_80BD6CDC(void); // func_80BD6CDC
void func_80BD6D18(void); // func_80BD6D18
void func_80BD6F10(void); // func_80BD6F10
void func_80BD7120(void); // func_80BD7120
void func_80BD716C(void); // func_80BD716C
void func_80BD71BC(void); // func_80BD71BC
void func_80BD7250(void); // func_80BD7250
void func_80BD72BC(void); // func_80BD72BC
void func_80BD7360(void); // func_80BD7360
void func_80BD73D0(void); // func_80BD73D0
void func_80BD73E0(void); // func_80BD73E0
void func_80BD7404(void); // func_80BD7404
void func_80BD7538(void); // func_80BD7538
void func_80BD7768(void); // func_80BD7768
void func_80BD7820(void); // func_80BD7820
void func_80BD78C4(void); // func_80BD78C4
void BgIknvObj_Init(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7AB0
void BgIknvObj_Fini(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7C7C
UNK_TYPE4 func_80BD7CEC(ActorBgIknvObj* this); // func_80BD7CEC
void BgIknvObj_UpdateType0(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7D6C
void func_80BD7E0C(void); // func_80BD7E0C
void func_80BD7ED8(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7ED8
void func_80BD7F4C(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7F4C
void func_80BD7FDC(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD7FDC
void func_80BD8040(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD8040
void BgIknvObj_UpdateType2(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD8098
void BgIknvObj_UpdateType1(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD80FC
void BgIknvObj_UpdateDefault(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD810C
void BgIknvObj_Main(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD811C
void BgIknvObj_Draw(ActorBgIknvObj* this, GlobalContext* ctxt); // func_80BD8140
void func_80BD82B0(void); // func_80BD82B0
void func_80BD84F0(void); // func_80BD84F0
void func_80BD8588(void); // func_80BD8588
void func_80BD8658(void); // func_80BD8658
void func_80BD86D4(void); // func_80BD86D4
void func_80BD8700(void); // func_80BD8700
void func_80BD8758(void); // func_80BD8758
void func_80BD8908(void); // func_80BD8908
void func_80BD8964(void); // func_80BD8964
void func_80BD8A38(void); // func_80BD8A38
void func_80BD8A7C(void); // func_80BD8A7C
void func_80BD8B50(void); // func_80BD8B50
void func_80BD8B70(void); // func_80BD8B70
void func_80BD8CCC(void); // func_80BD8CCC
void func_80BD8D1C(void); // func_80BD8D1C
void func_80BD8D80(void); // func_80BD8D80
void func_80BD8DB0(void); // func_80BD8DB0
void func_80BD8F0C(void); // func_80BD8F0C
void func_80BD8F60(void); // func_80BD8F60
void func_80BD8FF0(void); // func_80BD8FF0
void func_80BD909C(void); // func_80BD909C
void func_80BD90AC(void); // func_80BD90AC
void func_80BD9234(void); // func_80BD9234
void func_80BD92D0(void); // func_80BD92D0
void func_80BD9338(void); // func_80BD9338
void func_80BD9384(void); // func_80BD9384
void func_80BD93CC(void); // func_80BD93CC
void func_80BD93F4(void); // func_80BD93F4
void func_80BD94E0(void); // func_80BD94E0
void func_80BD95A4(void); // func_80BD95A4
void func_80BD9648(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BD9648
void func_80BD9690(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BD9690
void func_80BD96D0(void); // func_80BD96D0
void func_80BD9840(void); // func_80BD9840
void func_80BD9904(void); // func_80BD9904
void func_80BD9928(void); // func_80BD9928
void func_80BD9938(void); // func_80BD9938
void func_80BD994C(void); // func_80BD994C
void func_80BD9A9C(void); // func_80BD9A9C
void func_80BD9AB0(void); // func_80BD9AB0
void func_80BD9B4C(void); // func_80BD9B4C
void func_80BD9C70(void); // func_80BD9C70
void func_80BD9CB8(void); // func_80BD9CB8
void func_80BD9E60(void); // func_80BD9E60
void func_80BD9E78(void); // func_80BD9E78
void func_80BD9E88(void); // func_80BD9E88
void func_80BD9ED0(void); // func_80BD9ED0
void func_80BD9EE0(void); // func_80BD9EE0
void func_80BD9F3C(void); // func_80BD9F3C
void func_80BDA038(void); // func_80BDA038
void func_80BDA090(void); // func_80BDA090
void func_80BDA0A0(void); // func_80BDA0A0
void func_80BDA0FC(void); // func_80BDA0FC
void func_80BDA170(void); // func_80BDA170
void func_80BDA1C8(void); // func_80BDA1C8
void func_80BDA288(void); // func_80BDA288
void func_80BDA2E0(void); // func_80BDA2E0
void func_80BDA344(void); // func_80BDA344
void func_80BDAA30(void); // func_80BDAA30
void func_80BDAB00(void); // func_80BDAB00
void func_80BDAB18(void); // func_80BDAB18
void func_80BDAB6C(void); // func_80BDAB6C
void func_80BDABCC(void); // func_80BDABCC
void func_80BDAECC(void); // func_80BDAECC
void func_80BDAF00(void); // func_80BDAF00
void func_80BDAF24(void); // func_80BDAF24
void func_80BDB040(void); // func_80BDB040
void func_80BDB188(void); // func_80BDB188
void func_80BDB1B4(void); // func_80BDB1B4
void func_80BDB268(void); // func_80BDB268
void func_80BDB2B8(void); // func_80BDB2B8
void func_80BDB580(void); // func_80BDB580
void func_80BDB59C(void); // func_80BDB59C
void func_80BDB788(void); // func_80BDB788
void func_80BDB7E8(void); // func_80BDB7E8
void func_80BDB8F4(void); // func_80BDB8F4
void func_80BDB930(void); // func_80BDB930
void func_80BDB978(void); // func_80BDB978
void func_80BDBA28(void); // func_80BDBA28
void func_80BDBB48(void); // func_80BDBB48
void func_80BDBE70(void); // func_80BDBE70
void func_80BDBED4(void); // func_80BDBED4
void func_80BDBF7C(void); // func_80BDBF7C
void func_80BDC064(void); // func_80BDC064
void func_80BDC270(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_80BDC270
void func_80BDC2D8(void); // func_80BDC2D8
void func_80BDC3C0(void); // func_80BDC3C0
void func_80BDC50C(void); // func_80BDC50C
void func_80BDC5C8(void); // func_80BDC5C8
void func_80BDC6F8(void); // func_80BDC6F8
void func_80BDC830(void); // func_80BDC830
void func_80BDC9DC(void); // func_80BDC9DC
void func_80BDCB84(void); // func_80BDCB84
void func_80BDCD38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); // func_80BDCD38
void func_80BDCDA8(void); // func_80BDCDA8
void func_80BDCF28(void); // func_80BDCF28
void func_80BDD020(void); // func_80BDD020
void func_80BDD04C(void); // func_80BDD04C
void func_80BDD154(void); // func_80BDD154
void func_80BDD1E0(void); // func_80BDD1E0
void func_80BDD350(void); // func_80BDD350
void func_80BDD490(void); // func_80BDD490
void func_80BDD570(void); // func_80BDD570
void func_80BDD634(void); // func_80BDD634
void func_80BDD6BC(void); // func_80BDD6BC
void func_80BDD79C(void); // func_80BDD79C
void func_80BDD830(void); // func_80BDD830
void func_80BDDA7C(void); // func_80BDDA7C
void func_80BDDAA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BDDAA0
void func_80BDDAE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BDDAE0
void func_80BDDB04(void); // func_80BDDB04
void func_80BDDFE0(void); // func_80BDDFE0
void func_80BDE048(void); // func_80BDE048
void func_80BDE058(void); // func_80BDE058
void func_80BDE090(void); // func_80BDE090
void func_80BDE11C(void); // func_80BDE11C
void func_80BDE1A0(void); // func_80BDE1A0
void func_80BDE250(void); // func_80BDE250
void func_80BDE27C(void); // func_80BDE27C
void func_80BDE318(void); // func_80BDE318
void func_80BDE384(void); // func_80BDE384
void func_80BDE408(void); // func_80BDE408
void func_80BDE484(void); // func_80BDE484
void func_80BDE4E0(void); // func_80BDE4E0
void func_80BDE678(void); // func_80BDE678
void func_80BDE7FC(void); // func_80BDE7FC
void func_80BDE92C(void); // func_80BDE92C
void func_80BDEA14(void); // func_80BDEA14
void func_80BDEABC(void); // func_80BDEABC
void func_80BDEC2C(void); // func_80BDEC2C
void func_80BDED20(void); // func_80BDED20
void func_80BDEE5C(void); // func_80BDEE5C
void func_80BDEF3C(void); // func_80BDEF3C
void func_80BDEFE4(void); // func_80BDEFE4
void func_80BDF064(void); // func_80BDF064
void func_80BDF244(void); // func_80BDF244
void func_80BDF308(void); // func_80BDF308
void func_80BDF390(void); // func_80BDF390
void func_80BDF414(void); // func_80BDF414
void func_80BDF500(void); // func_80BDF500
void func_80BDF568(void); // func_80BDF568
void func_80BDF578(void); // func_80BDF578
void func_80BDF5E8(void); // func_80BDF5E8
void func_80BDF6C4(void); // func_80BDF6C4
void func_80BDF75C(void); // func_80BDF75C
void func_80BDF840(void); // func_80BDF840
void func_80BDF86C(void); // func_80BDF86C
void func_80BDF914(void); // func_80BDF914
void func_80BDF950(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BDF950
void func_80BDFA34(void); // func_80BDFA34
void func_80BDFB30(void); // func_80BDFB30
void func_80BE04E0(void); // func_80BE04E0
void func_80BE0590(void); // func_80BE0590
void func_80BE05BC(void); // func_80BE05BC
void func_80BE0620(void); // func_80BE0620
void func_80BE0664(void); // func_80BE0664
void func_80BE06DC(void); // func_80BE06DC
void func_80BE0778(void); // func_80BE0778
void func_80BE07A0(void); // func_80BE07A0
void func_80BE09A8(void); // func_80BE09A8
void func_80BE0A98(void); // func_80BE0A98
void func_80BE0C04(void); // func_80BE0C04
void func_80BE0D38(void); // func_80BE0D38
void func_80BE0D60(void); // func_80BE0D60
void func_80BE0E04(void); // func_80BE0E04
void func_80BE0F04(void); // func_80BE0F04
void func_80BE0FC4(void); // func_80BE0FC4
void func_80BE1060(void); // func_80BE1060
void func_80BE10BC(void); // func_80BE10BC
void func_80BE1224(void); // func_80BE1224
void func_80BE127C(void); // func_80BE127C
void func_80BE1348(void); // func_80BE1348
void func_80BE1424(void); // func_80BE1424
void func_80BE1524(void); // func_80BE1524
void func_80BE1550(void); // func_80BE1550
void func_80BE1648(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80BE1648
void func_80BE16B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BE16B4
void func_80BE1704(void); // func_80BE1704
void func_80BE1810(void); // func_80BE1810
void func_80BE1C80(void); // func_80BE1C80
void func_80BE1CEC(void); // func_80BE1CEC
void func_80BE1D5C(void); // func_80BE1D5C
void func_80BE1D88(void); // func_80BE1D88
void func_80BE1E9C(void); // func_80BE1E9C
void func_80BE2030(void); // func_80BE2030
void func_80BE20BC(void); // func_80BE20BC
void func_80BE20E8(void); // func_80BE20E8
void func_80BE21A0(void); // func_80BE21A0
void func_80BE2260(void); // func_80BE2260
void func_80BE2330(void); // func_80BE2330
void func_80BE24CC(void); // func_80BE24CC
void func_80BE2668(void); // func_80BE2668
void func_80BE2728(void); // func_80BE2728
void func_80BE2794(void); // func_80BE2794
void func_80BE2808(void); // func_80BE2808
void func_80BE2874(void); // func_80BE2874
void func_80BE2B80(void); // func_80BE2B80
void func_80BE2D4C(void); // func_80BE2D4C
void func_80BE2E18(void); // func_80BE2E18
void func_80BE2F6C(void); // func_80BE2F6C
void func_80BE30F4(void); // func_80BE30F4
void func_80BE3178(void); // func_80BE3178
void func_80BE32DC(void); // func_80BE32DC
void func_80BE3354(void); // func_80BE3354
void func_80BE348C(void); // func_80BE348C
void func_80BE35A4(void); // func_80BE35A4
void func_80BE3754(void); // func_80BE3754
void func_80BE3894(void); // func_80BE3894
void func_80BE38C0(void); // func_80BE38C0
void func_80BE393C(void); // func_80BE393C
void func_80BE3B80(void); // func_80BE3B80
void func_80BE3DB0(void); // func_80BE3DB0
void func_80BE3DC0(void); // func_80BE3DC0
void func_80BE3DFC(void); // func_80BE3DFC
void func_80BE4268(void); // func_80BE4268
void func_80BE42A4(void); // func_80BE42A4
void func_80BE4734(void); // func_80BE4734
void func_80BE4804(void); // func_80BE4804
void func_80BE4930(void); // func_80BE4930
void func_80BE4A2C(void); // func_80BE4A2C
void func_80BE4B1C(void); // func_80BE4B1C
void func_80BE4F24(void); // func_80BE4F24
void func_80BE4F54(void); // func_80BE4F54
void func_80BE5818(void); // func_80BE5818
void func_80BE5B58(void); // func_80BE5B58
void func_80BE5C10(void); // func_80BE5C10
void func_80BE6040(void); // func_80BE6040
void func_80BE60AC(void); // func_80BE60AC
void func_80BE60BC(void); // func_80BE60BC
void func_80BE60D0(void); // func_80BE60D0
void func_80BE60E0(void); // func_80BE60E0
void func_80BE6140(void); // func_80BE6140
void func_80BE61D0(void); // func_80BE61D0
void func_80BE6228(void); // func_80BE6228
void func_80BE63DC(void); // func_80BE63DC
void func_80BE6408(void); // func_80BE6408
void func_80BE64C0(void); // func_80BE64C0
void func_80BE65B4(void); // func_80BE65B4
void func_80BE66E4(void); // func_80BE66E4
void func_80BE6B40(void); // func_80BE6B40
void func_80BE6BC0(void); // func_80BE6BC0
void func_80BE6CFC(void); // func_80BE6CFC
void func_80BE6D40(void); // func_80BE6D40
void func_80BE6EB0(void); // func_80BE6EB0
void func_80BE6EF0(void); // func_80BE6EF0
void func_80BE71A0(void); // func_80BE71A0
void func_80BE71D8(void); // func_80BE71D8
void func_80BE72A8(void); // func_80BE72A8
void func_80BE738C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BE738C
void func_80BE7474(void); // func_80BE7474
void func_80BE7504(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80BE7504
void func_80BE7600(void); // func_80BE7600
void func_80BE7718(void); // func_80BE7718
void func_80BE7B00(void); // func_80BE7B00
void func_80BE7C68(void); // func_80BE7C68
void func_80BE7C94(void); // func_80BE7C94
void func_80BE7D20(void); // func_80BE7D20
void func_80BE7DB4(void); // func_80BE7DB4
void func_80BE7DEC(void); // func_80BE7DEC
void func_80BE7F88(void); // func_80BE7F88
void func_80BE7FEC(void); // func_80BE7FEC
void func_80BE81A4(void); // func_80BE81A4
void func_80BE8328(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BE8328
void func_80BE8390(void); // func_80BE8390
void func_80BE84F0(void); // func_80BE84F0
void func_80BE8664(void); // func_80BE8664
void func_80BE8690(void); // func_80BE8690
void func_80BE871C(void); // func_80BE871C
void func_80BE87B0(void); // func_80BE87B0
void func_80BE87FC(void); // func_80BE87FC
void func_80BE887C(void); // func_80BE887C
void func_80BE895C(void); // func_80BE895C
void func_80BE89D8(void); // func_80BE89D8
void func_80BE8AAC(void); // func_80BE8AAC
void func_80BE8BE0(void); // func_80BE8BE0
void func_80BE8D3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BE8D3C
void func_80BE8D94(void); // func_80BE8D94
void func_80BE8F20(void); // func_80BE8F20
void func_80BE9090(void); // func_80BE9090
void func_80BE90BC(void); // func_80BE90BC
void func_80BE9148(void); // func_80BE9148
void func_80BE91DC(void); // func_80BE91DC
void func_80BE9214(void); // func_80BE9214
void func_80BE9224(void); // func_80BE9224
void func_80BE9380(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BE9380
void func_80BE93D8(void); // func_80BE93D8
void func_80BE9510(void); // func_80BE9510
void func_80BE95C0(void); // func_80BE95C0
void func_80BE95EC(void); // func_80BE95EC
void func_80BE9678(void); // func_80BE9678
void func_80BE970C(void); // func_80BE970C
void func_80BE975C(void); // func_80BE975C
void func_80BE97F0(void); // func_80BE97F0
void func_80BE980C(void); // func_80BE980C
void func_80BE9864(void); // func_80BE9864
void func_80BE9974(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BE9974
void func_80BE99CC(void); // func_80BE99CC
void func_80BE9B20(void); // func_80BE9B20
void func_80BE9C48(void); // func_80BE9C48
void func_80BE9C74(void); // func_80BE9C74
void func_80BE9CE8(void); // func_80BE9CE8
void func_80BE9D9C(void); // func_80BE9D9C
void func_80BE9DF8(void); // func_80BE9DF8
void func_80BE9E94(void); // func_80BE9E94
void func_80BE9EF8(void); // func_80BE9EF8
void func_80BEA088(void); // func_80BEA088
void func_80BEA254(void); // func_80BEA254
void func_80BEA394(void); // func_80BEA394
void func_80BEA8F0(void); // func_80BEA8F0
void func_80BEAAF8(void); // func_80BEAAF8
void func_80BEAB44(void); // func_80BEAB44
void func_80BEABF8(void); // func_80BEABF8
void func_80BEAC84(void); // func_80BEAC84
void func_80BEAD2C(void); // func_80BEAD2C
void func_80BEADB8(void); // func_80BEADB8
void func_80BEADD4(void); // func_80BEADD4
void func_80BEAE94(void); // func_80BEAE94
void func_80BEB06C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BEB06C
void func_80BEB0A8(void); // func_80BEB0A8
void func_80BEB520(void); // func_80BEB520
void func_80BEB5B0(void); // func_80BEB5B0
void func_80BEB5DC(void); // func_80BEB5DC
void func_80BEB654(void); // func_80BEB654
void func_80BEB76C(void); // func_80BEB76C
void func_80BEB7F4(void); // func_80BEB7F4
void func_80BEB940(void); // func_80BEB940
void func_80BEB9BC(void); // func_80BEB9BC
void func_80BEB9CC(void); // func_80BEB9CC
void func_80BEB9DC(void); // func_80BEB9DC
void func_80BEBAC0(void); // func_80BEBAC0
void func_80BEBCFC(void); // func_80BEBCFC
void func_80BEBD0C(void); // func_80BEBD0C
void func_80BEBDF8(void); // func_80BEBDF8
void func_80BEBEB8(void); // func_80BEBEB8
void func_80BEBF78(void); // func_80BEBF78
void func_80BEC080(void); // func_80BEC080
void func_80BEC0A4(void); // func_80BEC0A4
void func_80BEC0DC(void); // func_80BEC0DC
void func_80BEC240(void); // func_80BEC240
void func_80BEC3F4(void); // func_80BEC3F4
void func_80BEC560(void); // func_80BEC560
void func_80BEC5C4(void); // func_80BEC5C4
void func_80BEC5E0(void); // func_80BEC5E0
void func_80BEC758(void); // func_80BEC758
void func_80BEC790(void); // func_80BEC790
void func_80BEC7EC(void); // func_80BEC7EC
void func_80BEC808(void); // func_80BEC808
void func_80BEC8C0(void); // func_80BEC8C0
void func_80BECA80(void); // func_80BECA80
void func_80BECBE0(void); // func_80BECBE0
void func_80BECC7C(void); // func_80BECC7C
void func_80BECD10(void); // func_80BECD10
void func_80BECEAC(void); // func_80BECEAC
void func_80BECF6C(void); // func_80BECF6C
void func_80BECFBC(void); // func_80BECFBC
void func_80BED034(void); // func_80BED034
void func_80BED090(void); // func_80BED090
void func_80BED140(void); // func_80BED140
void func_80BED208(void); // func_80BED208
void func_80BED27C(void); // func_80BED27C
void func_80BED2FC(void); // func_80BED2FC
void func_80BED35C(void); // func_80BED35C
void func_80BED3BC(void); // func_80BED3BC
void func_80BED680(void); // func_80BED680
void func_80BED8A4(void); // func_80BED8A4
void func_80BEDB88(void); // func_80BEDB88
void func_80BEDDAC(void); // func_80BEDDAC
void func_80BEE070(void); // func_80BEE070
void func_80BEE274(void); // func_80BEE274
void func_80BEE530(void); // func_80BEE530
void func_80BEE73C(void); // func_80BEE73C
void func_80BEE938(void); // func_80BEE938
void func_80BEEB20(void); // func_80BEEB20
void func_80BEEDC0(void); // func_80BEEDC0
void func_80BEEE10(void); // func_80BEEE10
void func_80BEEFA8(void); // func_80BEEFA8
void func_80BEF18C(void); // func_80BEF18C
void func_80BEF20C(void); // func_80BEF20C
void func_80BEF360(void); // func_80BEF360
void func_80BEF450(void); // func_80BEF450
void func_80BEF4B8(void); // func_80BEF4B8
void func_80BEF518(void); // func_80BEF518
void func_80BEF770(void); // func_80BEF770
void func_80BEF83C(void); // func_80BEF83C
void func_80BEF9F0(void); // func_80BEF9F0
void func_80BEFAF0(void); // func_80BEFAF0
void func_80BEFD74(void); // func_80BEFD74
void func_80BEFD98(void); // func_80BEFD98
void func_80BEFF08(void); // func_80BEFF08
void func_80BEFF34(void); // func_80BEFF34
UNK_TYPE4 func_80BEFFB4(UNK_TYPE4 param_1, s32 param_2, UNK_PTR param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, s32 param_6); // func_80BEFFB4
void func_80BF0178(void); // func_80BF0178
void func_80BF0190(void); // func_80BF0190
void func_80BF0258(void); // func_80BF0258
void func_80BF0D90(void); // func_80BF0D90
void func_80BF0DD0(void); // func_80BF0DD0
void func_80BF0DE0(void); // func_80BF0DE0
void func_80BF0EEC(void); // func_80BF0EEC
void func_80BF0F10(void); // func_80BF0F10
void func_80BF1150(void); // func_80BF1150
void func_80BF1200(void); // func_80BF1200
void func_80BF1258(void); // func_80BF1258
void func_80BF1284(void); // func_80BF1284
void func_80BF1354(void); // func_80BF1354
void func_80BF13E4(void); // func_80BF13E4
void func_80BF146C(void); // func_80BF146C
void func_80BF14B0(void); // func_80BF14B0
void func_80BF15EC(void); // func_80BF15EC
void func_80BF16C8(void); // func_80BF16C8
void func_80BF1744(void); // func_80BF1744
void func_80BF17BC(void); // func_80BF17BC
void func_80BF1920(void); // func_80BF1920
void func_80BF19A0(void); // func_80BF19A0
void func_80BF1A60(void); // func_80BF1A60
void func_80BF1AE0(void); // func_80BF1AE0
void func_80BF1B40(void); // func_80BF1B40
void func_80BF1C44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_80BF1C44
void func_80BF1D78(void); // func_80BF1D78
void func_80BF1DF4(void); // func_80BF1DF4
void func_80BF1FA8(void); // func_80BF1FA8
void func_80BF219C(void); // func_80BF219C
void func_80BF2368(void); // func_80BF2368
void func_80BF2400(void); // func_80BF2400
void func_80BF2470(void); // func_80BF2470
void func_80BF25E8(void); // func_80BF25E8
void func_80BF2890(void); // func_80BF2890
void func_80BF293C(void); // func_80BF293C
void func_80BF2A50(void); // func_80BF2A50
void func_80BF2AF8(void); // func_80BF2AF8
void func_80BF2BD4(void); // func_80BF2BD4
void func_80BF2CC0(void); // func_80BF2CC0
void func_80BF2DC4(void); // func_80BF2DC4
void func_80BF2E04(void); // func_80BF2E04
void func_80BF2EDC(void); // func_80BF2EDC
void func_80BF2EFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BF2EFC
void func_80BF302C(void); // func_80BF302C
void func_80BF312C(void); // func_80BF312C
void func_80BF3920(void); // func_80BF3920
void func_80BF3C64(void); // func_80BF3C64
void func_80BF3DA0(void); // func_80BF3DA0
void func_80BF3DC4(void); // func_80BF3DC4
void func_80BF3E88(void); // func_80BF3E88
void func_80BF3ED4(void); // func_80BF3ED4
void func_80BF3F14(void); // func_80BF3F14
void func_80BF3FF8(void); // func_80BF3FF8
void func_80BF4024(void); // func_80BF4024
void func_80BF409C(void); // func_80BF409C
void func_80BF40F4(void); // func_80BF40F4
void func_80BF416C(void); // func_80BF416C
void func_80BF4220(void); // func_80BF4220
void func_80BF42BC(void); // func_80BF42BC
void func_80BF43FC(void); // func_80BF43FC
void func_80BF4560(void); // func_80BF4560
void func_80BF45B4(void); // func_80BF45B4
void func_80BF47AC(void); // func_80BF47AC
void func_80BF4934(void); // func_80BF4934
void func_80BF4964(void); // func_80BF4964
void func_80BF4AB8(void); // func_80BF4AB8
void func_80BF4D64(void); // func_80BF4D64
void func_80BF4DA8(void); // func_80BF4DA8
void func_80BF4EBC(void); // func_80BF4EBC
void func_80BF4FC4(void); // func_80BF4FC4
void func_80BF5188(void); // func_80BF5188
void func_80BF5340(void); // func_80BF5340
void func_80BF5390(void); // func_80BF5390
void func_80BF547C(void); // func_80BF547C
void func_80BF5588(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80BF5588
void func_80BF5670(void); // func_80BF5670
void func_80BF5C20(void); // func_80BF5C20
void func_80BF5DF0(void); // func_80BF5DF0
void func_80BF5E00(void); // func_80BF5E00
void func_80BF5E68(void); // func_80BF5E68
void func_80BF5EBC(void); // func_80BF5EBC
void func_80BF5F60(void); // func_80BF5F60
void func_80BF5F70(void); // func_80BF5F70
void func_80BF609C(void); // func_80BF609C
void func_80BF61EC(void); // func_80BF61EC
void func_80BF6314(void); // func_80BF6314
void func_80BF6478(void); // func_80BF6478
void func_80BF656C(void); // func_80BF656C
void func_80BF67A8(void); // func_80BF67A8
void func_80BF68E0(void); // func_80BF68E0
void func_80BF6A20(void); // func_80BF6A20
void func_80BF6C30(void); // func_80BF6C30
void func_80BF6C54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BF6C54
void func_80BF6C94(void); // func_80BF6C94
void func_80BF74E0(void); // func_80BF74E0
void func_80BF7590(void); // func_80BF7590
void func_80BF75A0(void); // func_80BF75A0
void func_80BF75CC(void); // func_80BF75CC
void func_80BF7688(void); // func_80BF7688
void func_80BF76AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BF76AC
void func_80BF77AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BF77AC
void func_80BF7814(void); // func_80BF7814
void func_80BFA100(void); // func_80BFA100
void func_80BFA2D0(void); // func_80BFA2D0
void func_80BFA2FC(void); // func_80BFA2FC
void func_80BFA350(void); // func_80BFA350
void func_80BFA444(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BFA444
void func_80BFA5CC(void); // func_80BFA5CC
void func_80BFA634(void); // func_80BFA634
void func_80BFA67C(void); // func_80BFA67C
void func_80BFA6E0(void); // func_80BFA6E0
void func_80BFA710(void); // func_80BFA710
void func_80BFA730(void); // func_80BFA730
void func_80BFA868(void); // func_80BFA868
void func_80BFA91C(void); // func_80BFA91C
void func_80BFA9D4(void); // func_80BFA9D4
void func_80BFAB4C(void); // func_80BFAB4C
void func_80BFABF0(void); // func_80BFABF0
void func_80BFAC88(void); // func_80BFAC88
void func_80BFAE80(void); // func_80BFAE80
void func_80BFAEFC(void); // func_80BFAEFC
void func_80BFB074(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BFB074
void func_80BFB0E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BFB0E0
void func_80BFB14C(void); // func_80BFB14C
void func_80BFB480(void); // func_80BFB480
void func_80BFB780(void); // func_80BFB780
void func_80BFB864(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BFB864
void func_80BFB9E4(void); // func_80BFB9E4
void func_80BFBA1C(void); // func_80BFBA1C
void func_80BFBA50(void); // func_80BFBA50
void func_80BFBB44(void); // func_80BFBB44
void func_80BFBC78(void); // func_80BFBC78
void func_80BFBCEC(void); // func_80BFBCEC
void func_80BFBD54(void); // func_80BFBD54
void func_80BFBDA0(void); // func_80BFBDA0
void func_80BFBDFC(void); // func_80BFBDFC
void func_80BFBE44(void); // func_80BFBE44
void func_80BFBE70(void); // func_80BFBE70
void func_80BFBFAC(void); // func_80BFBFAC
void func_80BFC058(void); // func_80BFC058
void func_80BFC078(void); // func_80BFC078
void func_80BFC19C(void); // func_80BFC19C
void func_80BFC214(void); // func_80BFC214
void func_80BFC270(void); // func_80BFC270
void func_80BFC2F4(void); // func_80BFC2F4
void func_80BFC36C(void); // func_80BFC36C
void func_80BFC3F8(void); // func_80BFC3F8
void func_80BFC608(void); // func_80BFC608
void func_80BFC674(void); // func_80BFC674
void func_80BFC728(void); // func_80BFC728
void func_80BFC7E0(void); // func_80BFC7E0
void func_80BFC8AC(void); // func_80BFC8AC
void func_80BFC8F8(void); // func_80BFC8F8
void func_80BFC9E4(void); // func_80BFC9E4
void func_80BFCAD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80BFCAD0
void func_80BFCB3C(void); // func_80BFCB3C
void func_80BFCFA0(void); // func_80BFCFA0
void func_80BFCFB8(void); // func_80BFCFB8
void func_80BFD010(void); // func_80BFD010
void func_80BFD148(void); // func_80BFD148
void func_80BFD158(void); // func_80BFD158
void func_80BFD17C(void); // func_80BFD17C
void func_80BFD2E0(void); // func_80BFD2E0
void func_80BFD30C(void); // func_80BFD30C
void func_80BFD3A4(void); // func_80BFD3A4
void func_80BFD434(void); // func_80BFD434
void func_80BFD4FC(void); // func_80BFD4FC
void func_80BFD5E4(void); // func_80BFD5E4
void func_80BFD6BC(void); // func_80BFD6BC
void func_80BFD8F0(void); // func_80BFD8F0
void func_80BFD984(void); // func_80BFD984
void func_80BFDA48(void); // func_80BFDA48
void func_80BFDAE8(void); // func_80BFDAE8
void func_80BFDC98(void); // func_80BFDC98
void func_80BFDD80(void); // func_80BFDD80
void func_80BFDD90(void); // func_80BFDD90
void func_80BFDE38(void); // func_80BFDE38
void func_80BFE170(void); // func_80BFE170
void func_80BFE300(void); // func_80BFE300
void func_80BFE32C(void); // func_80BFE32C
void func_80BFE494(void); // func_80BFE494
void func_80BFE524(void); // func_80BFE524
void func_80BFE65C(void); // func_80BFE65C
void func_80BFE67C(void); // func_80BFE67C
void func_80BFEA94(void); // func_80BFEA94
void func_80BFEB1C(void); // func_80BFEB1C
void func_80BFEB64(void); // func_80BFEB64
void func_80BFEFF0(void); // func_80BFEFF0
void func_80BFF03C(void); // func_80BFF03C
void func_80BFF120(void); // func_80BFF120
void func_80BFF174(void); // func_80BFF174
void func_80BFF3F0(void); // func_80BFF3F0
void func_80BFF430(void); // func_80BFF430
void func_80BFF4F4(void); // func_80BFF4F4
void func_80BFF52C(void); // func_80BFF52C
void func_80BFF6CC(void); // func_80BFF6CC
void func_80BFF754(void); // func_80BFF754
void func_80BFF9B0(void); // func_80BFF9B0
void func_80BFFB40(void); // func_80BFFB40
void func_80BFFBC4(void); // func_80BFFBC4
void func_80BFFCFC(void); // func_80BFFCFC
void func_80BFFD48(void); // func_80BFFD48
void func_80BFFE48(void); // func_80BFFE48
void func_80BFFF54(void); // func_80BFFF54
void func_80C0011C(void); // func_80C0011C
void func_80C00168(void); // func_80C00168
void func_80C00234(void); // func_80C00234
void func_80C00284(void); // func_80C00284
void func_80C00644(void); // func_80C00644
void func_80C007F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C007F4
void func_80C008B4(void); // func_80C008B4
void func_80C00EA0(void); // func_80C00EA0
void func_80C01110(void); // func_80C01110
void func_80C0113C(void); // func_80C0113C
void func_80C011CC(void); // func_80C011CC
void func_80C012E0(void); // func_80C012E0
void func_80C012FC(void); // func_80C012FC
void func_80C013B4(void); // func_80C013B4
void func_80C013F0(void); // func_80C013F0
void func_80C01494(void); // func_80C01494
void func_80C014E4(void); // func_80C014E4
void func_80C01984(void); // func_80C01984
void func_80C01A24(void); // func_80C01A24
void func_80C01B40(void); // func_80C01B40
void func_80C01B74(void); // func_80C01B74
void func_80C01C18(void); // func_80C01C18
void func_80C01CD0(void); // func_80C01CD0
void func_80C01FD4(void); // func_80C01FD4
void func_80C0201C(void); // func_80C0201C
void func_80C02108(void); // func_80C02108
void func_80C0217C(void); // func_80C0217C
void func_80C0250C(void); // func_80C0250C
void func_80C02570(void); // func_80C02570
void func_80C0267C(void); // func_80C0267C
void func_80C02704(void); // func_80C02704
void func_80C02740(void); // func_80C02740
void func_80C02A14(void); // func_80C02A14
void func_80C02BCC(void); // func_80C02BCC
void func_80C02CA4(void); // func_80C02CA4
void func_80C02DAC(void); // func_80C02DAC
void func_80C02DC4(void); // func_80C02DC4
void func_80C02FA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C02FA8
void func_80C03034(void); // func_80C03034
void func_80C03530(void); // func_80C03530
void func_80C037F8(void); // func_80C037F8
void func_80C03824(void); // func_80C03824
void func_80C038B4(void); // func_80C038B4
void func_80C039A8(void); // func_80C039A8
void func_80C03ACC(void); // func_80C03ACC
void func_80C03AF4(void); // func_80C03AF4
void func_80C03F64(void); // func_80C03F64
void func_80C03FAC(void); // func_80C03FAC
void func_80C042F8(void); // func_80C042F8
void func_80C04354(void); // func_80C04354
void func_80C043C8(void); // func_80C043C8
void func_80C0443C(void); // func_80C0443C
void func_80C045B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C045B4
void func_80C04614(void); // func_80C04614
void func_80C04930(void); // func_80C04930
void func_80C04A80(void); // func_80C04A80
void func_80C04AAC(void); // func_80C04AAC
void func_80C04B40(void); // func_80C04B40
void func_80C04BA0(void); // func_80C04BA0
void func_80C04D00(void); // func_80C04D00
void func_80C04D8C(void); // func_80C04D8C
void func_80C050B8(void); // func_80C050B8
void func_80C0520C(void); // func_80C0520C
void func_80C053F8(void); // func_80C053F8
void func_80C056D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C056D4
void func_80C05758(void); // func_80C05758
void func_80C05A70(void); // func_80C05A70
void func_80C05AF8(void); // func_80C05AF8
void func_80C05B24(void); // func_80C05B24
void func_80C05B3C(void); // func_80C05B3C
void func_80C05C44(void); // func_80C05C44
void func_80C05DE8(void); // func_80C05DE8
void func_80C05E7C(void); // func_80C05E7C
void func_80C05F30(void); // func_80C05F30
void func_80C05F90(void); // func_80C05F90
void func_80C060B8(void); // func_80C060B8
void func_80C06208(void); // func_80C06208
void func_80C06510(void); // func_80C06510
void func_80C0661C(void); // func_80C0661C
void func_80C0662C(void); // func_80C0662C
void func_80C06640(void); // func_80C06640
void func_80C066F8(void); // func_80C066F8
void func_80C0670C(void); // func_80C0670C
void func_80C0673C(void); // func_80C0673C
void func_80C06768(void); // func_80C06768
void func_80C0685C(void); // func_80C0685C
void func_80C06870(void); // func_80C06870
void func_80C068D0(void); // func_80C068D0
void func_80C06910(void); // func_80C06910
void func_80C06AA0(void); // func_80C06AA0
void func_80C06B4C(void); // func_80C06B4C
void func_80C06B5C(void); // func_80C06B5C
void func_80C06B70(void); // func_80C06B70
void func_80C06C54(void); // func_80C06C54
void func_80C06C68(void); // func_80C06C68
void func_80C06CC4(void); // func_80C06CC4
void func_80C06CD8(void); // func_80C06CD8
void func_80C06D90(void); // func_80C06D90
void func_80C06DC8(void); // func_80C06DC8
void func_80C06E88(void); // func_80C06E88
void func_80C06FAC(void); // func_80C06FAC
void func_80C06FD0(void); // func_80C06FD0
void func_80C07110(void); // func_80C07110
void func_80C071D8(void); // func_80C071D8
void func_80C07220(void); // func_80C07220
void func_80C07230(void); // func_80C07230
void func_80C072D0(void); // func_80C072D0
void func_80C075C4(void); // func_80C075C4
void func_80C075E8(void); // func_80C075E8
void func_80C07740(void); // func_80C07740
void func_80C07780(void); // func_80C07780
void func_80C07790(void); // func_80C07790
void func_80C07898(void); // func_80C07898
void func_80C078BC(void); // func_80C078BC
void func_80C07B20(void); // func_80C07B20
void func_80C07BA0(void); // func_80C07BA0
void func_80C07BD4(void); // func_80C07BD4
void func_80C07BE4(void); // func_80C07BE4
void func_80C07C80(void); // func_80C07C80
void func_80C07CD0(void); // func_80C07CD0
void func_80C07DC4(void); // func_80C07DC4
void func_80C07DFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_80C07DFC
void func_80C07F30(void); // func_80C07F30
void func_80C081C8(void); // func_80C081C8
void func_80C082CC(void); // func_80C082CC
void func_80C082E0(void); // func_80C082E0
void func_80C0836C(void); // func_80C0836C
void func_80C08428(void); // func_80C08428
void func_80C0845C(void); // func_80C0845C
void func_80C08480(void); // func_80C08480
void func_80C08760(void); // func_80C08760
void func_80C087FC(void); // func_80C087FC
void func_80C08828(void); // func_80C08828
void func_80C0883C(void); // func_80C0883C
void func_80C088A4(void); // func_80C088A4
void func_80C088B8(void); // func_80C088B8
void func_80C088EC(void); // func_80C088EC
void func_80C08950(void); // func_80C08950
void func_80C08A80(void); // func_80C08A80
void func_80C08B2C(void); // func_80C08B2C
void func_80C08B60(void); // func_80C08B60
void func_80C08B7C(void); // func_80C08B7C
void func_80C08BBC(void); // func_80C08BBC
void func_80C08BD0(void); // func_80C08BD0
void func_80C08C84(void); // func_80C08C84
void func_80C08CB0(void); // func_80C08CB0
void func_80C08D20(void); // func_80C08D20
void func_80C08D44(void); // func_80C08D44
void func_80C08E40(void); // func_80C08E40
void func_80C08EC8(void); // func_80C08EC8
void func_80C08EF4(void); // func_80C08EF4
void func_80C08FEC(void); // func_80C08FEC
void func_80C090D0(void); // func_80C090D0
void func_80C09210(void); // func_80C09210
void func_80C0923C(void); // func_80C0923C
void func_80C09390(void); // func_80C09390
void func_80C09418(void); // func_80C09418
void func_80C094A8(void); // func_80C094A8
void func_80C09518(void); // func_80C09518
void func_80C095C8(void); // func_80C095C8
void func_80C09648(void); // func_80C09648
void func_80C09708(void); // func_80C09708
void func_80C09990(void); // func_80C09990
void func_80C09AA4(void); // func_80C09AA4
void func_80C09B50(void); // func_80C09B50
void func_80C09BC8(void); // func_80C09BC8
void func_80C09C74(void); // func_80C09C74
void func_80C09C90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C09C90
void func_80C09CD0(void); // func_80C09CD0
void func_80C09ED0(void); // func_80C09ED0
void func_80C09FEC(void); // func_80C09FEC
void func_80C0A0EC(void); // func_80C0A0EC
void func_80C0A120(void); // func_80C0A120
void func_80C0A378(void); // func_80C0A378
void func_80C0A38C(void); // func_80C0A38C
void func_80C0A400(void); // func_80C0A400
void func_80C0A418(void); // func_80C0A418
void func_80C0A458(void); // func_80C0A458
void func_80C0A4BC(void); // func_80C0A4BC
void func_80C0A4CC(void); // func_80C0A4CC
void func_80C0A4F0(void); // func_80C0A4F0
void func_80C0A740(void); // func_80C0A740
void func_80C0A804(void); // func_80C0A804
void func_80C0A838(void); // func_80C0A838
void func_80C0A86C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C0A86C
void func_80C0A95C(void); // func_80C0A95C
void func_80C0AA70(void); // func_80C0AA70
void func_80C0AAE0(void); // func_80C0AAE0
void func_80C0AB14(void); // func_80C0AB14
void func_80C0AB44(void); // func_80C0AB44
void func_80C0AB88(void); // func_80C0AB88
void func_80C0ABA8(void); // func_80C0ABA8
void func_80C0AC74(void); // func_80C0AC74
void func_80C0AC90(void); // func_80C0AC90
void func_80C0ACD4(void); // func_80C0ACD4
void func_80C0ACE8(void); // func_80C0ACE8
void func_80C0AD44(void); // func_80C0AD44
void func_80C0AD64(void); // func_80C0AD64
void func_80C0AE3C(void); // func_80C0AE3C
void func_80C0AE5C(void); // func_80C0AE5C
void func_80C0AF18(void); // func_80C0AF18
void func_80C0B080(void); // func_80C0B080
void func_80C0B290(void); // func_80C0B290
void func_80C0B31C(void); // func_80C0B31C
void func_80C0B62C(void); // func_80C0B62C
void func_80C0B820(void); // func_80C0B820
void func_80C0B888(void); // func_80C0B888
void func_80C0B970(void); // func_80C0B970
void func_80C0BA58(void); // func_80C0BA58
void func_80C0BC30(void); // func_80C0BC30
void func_80C0BE1C(void); // func_80C0BE1C
void func_80C0BF2C(void); // func_80C0BF2C
void func_80C0BFE8(void); // func_80C0BFE8
void func_80C0C0F4(void); // func_80C0C0F4
void func_80C0C238(void); // func_80C0C238
void func_80C0C32C(void); // func_80C0C32C
void func_80C0C364(void); // func_80C0C364
void func_80C0C430(void); // func_80C0C430
void func_80C0C484(void); // func_80C0C484
void func_80C0C610(void); // func_80C0C610
void func_80C0C6A8(void); // func_80C0C6A8
void func_80C0C86C(void); // func_80C0C86C
void func_80C0C8EC(void); // func_80C0C8EC
void func_80C0CA28(void); // func_80C0CA28
void func_80C0CB3C(void); // func_80C0CB3C
void func_80C0CCCC(void); // func_80C0CCCC
void func_80C0CD04(void); // func_80C0CD04
void func_80C0CD90(void); // func_80C0CD90
void func_80C0CDE4(void); // func_80C0CDE4
void func_80C0CF4C(void); // func_80C0CF4C
void func_80C0CFDC(void); // func_80C0CFDC
void func_80C0D00C(void); // func_80C0D00C
void func_80C0D10C(void); // func_80C0D10C
void func_80C0D214(void); // func_80C0D214
void func_80C0D27C(void); // func_80C0D27C
void func_80C0D334(void); // func_80C0D334
void func_80C0D384(void); // func_80C0D384
void func_80C0D3C0(void); // func_80C0D3C0
void func_80C0D51C(void); // func_80C0D51C
void func_80C0D964(void); // func_80C0D964
void func_80C0D9B4(void); // func_80C0D9B4
void func_80C0DA58(void); // func_80C0DA58
void func_80C0DB18(void); // func_80C0DB18
void func_80C0E178(void); // func_80C0E178
void func_80C0E1C0(void); // func_80C0E1C0
void func_80C0E3B8(void); // func_80C0E3B8
void func_80C0E480(void); // func_80C0E480
void func_80C0E4FC(void); // func_80C0E4FC
void func_80C0E618(void); // func_80C0E618
void func_80C0E9CC(void); // func_80C0E9CC
void func_80C0EB8C(void); // func_80C0EB8C
void func_80C0EEA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C0EEA0
void func_80C0F078(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C0F078
void func_80C0F170(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C0F170
void func_80C0F308(void); // func_80C0F308
void func_80C0F544(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_80C0F544
void func_80C0F640(void); // func_80C0F640
void func_80C0F758(void); // func_80C0F758
void func_80C0FFD0(void); // func_80C0FFD0
void func_80C100CC(void); // func_80C100CC
void func_80C100DC(void); // func_80C100DC
void func_80C10148(void); // func_80C10148
void func_80C1019C(void); // func_80C1019C
void func_80C10290(void); // func_80C10290
void func_80C102D4(void); // func_80C102D4
void func_80C104E8(void); // func_80C104E8
void func_80C10558(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C10558
void func_80C10590(void); // func_80C10590
void func_80C105EC(void); // func_80C105EC
void func_80C10770(void); // func_80C10770
void func_80C10958(void); // func_80C10958
void func_80C10984(void); // func_80C10984
void func_80C10B0C(void); // func_80C10B0C
void func_80C10DE8(void); // func_80C10DE8
void func_80C10E98(void); // func_80C10E98
void func_80C11338(void); // func_80C11338
void func_80C11454(void); // func_80C11454
void func_80C114C0(void); // func_80C114C0
void func_80C11538(void); // func_80C11538
void func_80C11590(void); // func_80C11590
void func_80C118E4(void); // func_80C118E4
void func_80C1193C(void); // func_80C1193C
void func_80C11C60(void); // func_80C11C60
void func_80C11D14(void); // func_80C11D14
void func_80C11DC0(void); // func_80C11DC0
void func_80C11DF0(void); // func_80C11DF0
void func_80C11F6C(void); // func_80C11F6C
void func_80C1215C(void); // func_80C1215C
void func_80C12308(void); // func_80C12308
void func_80C12378(void); // func_80C12378
void func_80C1242C(void); // func_80C1242C
void func_80C124B0(void); // func_80C124B0
void func_80C126A8(void); // func_80C126A8
void func_80C126D8(void); // func_80C126D8
void func_80C12744(void); // func_80C12744
void func_80C127F4(void); // func_80C127F4
void func_80C12B1C(void); // func_80C12B1C
void func_80C12D00(void); // func_80C12D00
void func_80C12ED4(void); // func_80C12ED4
void func_80C130EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C130EC
void func_80C1315C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C1315C
void func_80C13354(void); // func_80C13354
void func_80C134D0(void); // func_80C134D0
void func_80C13930(void); // func_80C13930
void func_80C13A2C(void); // func_80C13A2C
void func_80C13B38(void); // func_80C13B38
void func_80C13B74(void); // func_80C13B74
void func_80C13BB8(void); // func_80C13BB8
void func_80C13E6C(void); // func_80C13E6C
void func_80C13E90(void); // func_80C13E90
void func_80C13F88(void); // func_80C13F88
void func_80C13F9C(void); // func_80C13F9C
void func_80C14030(void); // func_80C14030
void func_80C14044(void); // func_80C14044
void func_80C1410C(void); // func_80C1410C
void func_80C1418C(void); // func_80C1418C
void func_80C141DC(void); // func_80C141DC
void func_80C14230(void); // func_80C14230
void func_80C144E4(void); // func_80C144E4
void func_80C144F8(void); // func_80C144F8
void func_80C14540(void); // func_80C14540
void func_80C14554(void); // func_80C14554
void func_80C145FC(void); // func_80C145FC
void func_80C14610(void); // func_80C14610
void func_80C14684(void); // func_80C14684
void func_80C1476C(void); // func_80C1476C
void func_80C147B4(void); // func_80C147B4
void func_80C14960(void); // func_80C14960
void func_80C149B0(void); // func_80C149B0
void func_80C14BCC(void); // func_80C14BCC
void func_80C14D14(void); // func_80C14D14
void func_80C14D58(void); // func_80C14D58
void func_80C14E08(void); // func_80C14E08
void func_80C14E64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_80C14E64
void func_80C14EE4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C14EE4
void func_80C14F1C(void); // func_80C14F1C
void func_80C152F0(void); // func_80C152F0
void func_80C1542C(void); // func_80C1542C
void func_80C15474(void); // func_80C15474
void func_80C156C4(void); // func_80C156C4
void func_80C15718(void); // func_80C15718
void func_80C157D4(void); // func_80C157D4
void func_80C15828(void); // func_80C15828
void func_80C161E0(void); // func_80C161E0
void func_80C16234(void); // func_80C16234
void func_80C16244(void); // func_80C16244
void func_80C1625C(void); // func_80C1625C
void func_80C16480(void); // func_80C16480
void func_80C16724(void); // func_80C16724
void func_80C16760(void); // func_80C16760
void func_80C16818(void); // func_80C16818
void func_80C168D0(void); // func_80C168D0
void func_80C16974(void); // func_80C16974
void func_80C16A64(void); // func_80C16A64
void func_80C16A74(void); // func_80C16A74
void func_80C16BD4(void); // func_80C16BD4
void func_80C16DD4(void); // func_80C16DD4
void func_80C16EAC(void); // func_80C16EAC
void func_80C17008(void); // func_80C17008
void func_80C170D4(void); // func_80C170D4
void func_80C170F8(void); // func_80C170F8
void func_80C173B4(void); // func_80C173B4
void func_80C17468(void); // func_80C17468
void func_80C17528(void); // func_80C17528
void func_80C17690(void); // func_80C17690
void func_80C17A10(void); // func_80C17A10
void func_80C17B10(void); // func_80C17B10
void func_80C17B50(void); // func_80C17B50
void func_80C17B60(void); // func_80C17B60
void func_80C17C48(void); // func_80C17C48
void func_80C17E4C(void); // func_80C17E4C
void func_80C17E70(void); // func_80C17E70
void func_80C17EE0(void); // func_80C17EE0
void func_80C17F1C(void); // func_80C17F1C
void func_80C17FCC(void); // func_80C17FCC
void func_80C18120(void); // func_80C18120
void func_80C1817C(void); // func_80C1817C
void func_80C181B0(void); // func_80C181B0
void func_80C18240(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C18240
void func_80C1838C(void); // func_80C1838C
void func_80C184B8(void); // func_80C184B8
void func_80C184EC(void); // func_80C184EC
void func_80C187E4(void); // func_80C187E4
void func_80C187F8(void); // func_80C187F8
void func_80C1886C(void); // func_80C1886C
void func_80C18884(void); // func_80C18884
void func_80C188C4(void); // func_80C188C4
void func_80C18928(void); // func_80C18928
void func_80C18938(void); // func_80C18938
void func_80C1895C(void); // func_80C1895C
void func_80C18B90(void); // func_80C18B90
void func_80C18BD8(void); // func_80C18BD8
void func_80C18C50(void); // func_80C18C50
void func_80C18DC8(void); // func_80C18DC8
void func_80C18E84(void); // func_80C18E84
void func_80C18E94(void); // func_80C18E94
void func_80C18ED0(void); // func_80C18ED0
void func_80C19084(void); // func_80C19084
void func_80C192A0(void); // func_80C192A0
void func_80C192B0(void); // func_80C192B0
void func_80C19334(void); // func_80C19334
void func_80C193A8(void); // func_80C193A8
void func_80C19454(void); // func_80C19454
void func_80C19498(void); // func_80C19498
void func_80C1950C(void); // func_80C1950C
void func_80C19548(void); // func_80C19548
void func_80C19564(void); // func_80C19564
void func_80C19590(void); // func_80C19590
void func_80C1965C(void); // func_80C1965C
void func_80C19688(void); // func_80C19688
void func_80C19754(void); // func_80C19754
void func_80C1985C(void); // func_80C1985C
void func_80C1987C(void); // func_80C1987C
void func_80C199BC(void); // func_80C199BC
void func_80C199EC(void); // func_80C199EC
void func_80C19AB4(void); // func_80C19AB4
void func_80C19D00(void); // func_80C19D00
void func_80C19D48(void); // func_80C19D48
void func_80C19E04(void); // func_80C19E04
void func_80C19EC0(void); // func_80C19EC0
void func_80C19F7C(void); // func_80C19F7C
void func_80C1A038(void); // func_80C1A038
void func_80C1A070(void); // func_80C1A070
void func_80C1A168(void); // func_80C1A168
void func_80C1A244(void); // func_80C1A244
void func_80C1A590(void); // func_80C1A590
void func_80C1A650(void); // func_80C1A650
void func_80C1A670(void); // func_80C1A670
void func_80C1A6C8(void); // func_80C1A6C8
void func_80C1A854(void); // func_80C1A854
void func_80C1A8A4(void); // func_80C1A8A4
void func_80C1A98C(void); // func_80C1A98C
void func_80C1A9C0(void); // func_80C1A9C0
void func_80C1A9E4(void); // func_80C1A9E4
void func_80C1ADC0(void); // func_80C1ADC0
void func_80C1ADFC(void); // func_80C1ADFC
void func_80C1AF50(void); // func_80C1AF50
void func_80C1AF84(void); // func_80C1AF84
void func_80C1AF94(void); // func_80C1AF94
void func_80C1B210(void); // func_80C1B210
void func_80C1B26C(void); // func_80C1B26C
void func_80C1B2A4(void); // func_80C1B2A4
void func_80C1B4E4(void); // func_80C1B4E4
void func_80C1B640(void); // func_80C1B640
void func_80C1B6F8(void); // func_80C1B6F8
void func_80C1B724(void); // func_80C1B724
void func_80C1B8A4(void); // func_80C1B8A4
void func_80C1B8B4(void); // func_80C1B8B4
void func_80C1B8F0(void); // func_80C1B8F0
void func_80C1B9D4(void); // func_80C1B9D4
void func_80C1BAC8(void); // func_80C1BAC8
void func_80C1BAEC(void); // func_80C1BAEC
void func_80C1BD90(void); // func_80C1BD90
void func_80C1BDD8(void); // func_80C1BDD8
void func_80C1BF08(void); // func_80C1BF08
void func_80C1BFB8(void); // func_80C1BFB8
void func_80C1BFC8(void); // func_80C1BFC8
void func_80C1C028(void); // func_80C1C028
void func_80C1C064(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C1C064
void func_80C1C11C(void); // func_80C1C11C
void func_80C1C130(void); // func_80C1C130
void func_80C1C410(void); // func_80C1C410
void func_80C1C4D8(void); // func_80C1C4D8
void func_80C1C5B4(void); // func_80C1C5B4
void func_80C1C62C(void); // func_80C1C62C
void func_80C1C83C(void); // func_80C1C83C
void func_80C1C8E8(void); // func_80C1C8E8
void func_80C1C958(void); // func_80C1C958
void func_80C1CAB0(void); // func_80C1CAB0
void func_80C1CC80(void); // func_80C1CC80
void func_80C1CC90(void); // func_80C1CC90
void func_80C1CCE4(void); // func_80C1CCE4
void func_80C1CCF4(void); // func_80C1CCF4
void func_80C1CD80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C1CD80
void func_80C1CEFC(void); // func_80C1CEFC
void func_80C1D0B0(void); // func_80C1D0B0
void func_80C1D410(void); // func_80C1D410
void func_80C1D458(void); // func_80C1D458
void func_80C1D4D0(void); // func_80C1D4D0
void func_80C1D6E0(void); // func_80C1D6E0
void func_80C1D78C(void); // func_80C1D78C
void func_80C1D7FC(void); // func_80C1D7FC
void func_80C1D92C(void); // func_80C1D92C
void func_80C1D93C(void); // func_80C1D93C
void func_80C1DA48(void); // func_80C1DA48
void func_80C1DA58(void); // func_80C1DA58
void func_80C1DAD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C1DAD4
void func_80C1DB24(void); // func_80C1DB24
void func_80C1DCD8(void); // func_80C1DCD8
void func_80C1DED0(void); // func_80C1DED0
void func_80C1DF18(void); // func_80C1DF18
void func_80C1E048(void); // func_80C1E048
void func_80C1E0F8(void); // func_80C1E0F8
void func_80C1E108(void); // func_80C1E108
void func_80C1E168(void); // func_80C1E168
void func_80C1E17C(void); // func_80C1E17C
void func_80C1E290(void); // func_80C1E290
void func_80C1E2D4(void); // func_80C1E2D4
void func_80C1E3DC(void); // func_80C1E3DC
void func_80C1E3EC(void); // func_80C1E3EC
void func_80C1E424(void); // func_80C1E424
void func_80C1E450(void); // func_80C1E450
void func_80C1E4B0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C1E4B0
void func_80C1E568(void); // func_80C1E568
void func_80C1E690(void); // func_80C1E690
void func_80C1E738(void); // func_80C1E738
void func_80C1E748(void); // func_80C1E748
void func_80C1E764(void); // func_80C1E764
void func_80C1E790(void); // func_80C1E790
void func_80C1E84C(void); // func_80C1E84C
void func_80C1E9E0(void); // func_80C1E9E0
void func_80C1EAB4(void); // func_80C1EAB4
void func_80C1EAC4(void); // func_80C1EAC4
void func_80C1EAD8(void); // func_80C1EAD8
void func_80C1EAE8(void); // func_80C1EAE8
void func_80C1EC60(void); // func_80C1EC60
void func_80C1ED0C(void); // func_80C1ED0C
void func_80C1ED64(void); // func_80C1ED64
void func_80C1EDE4(void); // func_80C1EDE4
void func_80C1EF80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80C1EF80
void func_80C1F060(void); // func_80C1F060
void func_80C1F078(void); // func_80C1F078
void func_80C1F3D0(void); // func_80C1F3D0
void func_80C1F45C(void); // func_80C1F45C
void func_80C1F46C(void); // func_80C1F46C
void func_80C1F480(void); // func_80C1F480
void func_80C1F4E8(void); // func_80C1F4E8
void func_80C1F4FC(void); // func_80C1F4FC
void func_80C1F55C(void); // func_80C1F55C
void func_80C1F6E0(void); // func_80C1F6E0
void func_80C1F87C(void); // func_80C1F87C
void func_80C1F97C(void); // func_80C1F97C
void func_80C1F9D0(void); // func_80C1F9D0
void func_80C1FCF0(void); // func_80C1FCF0
void func_80C1FDE0(void); // func_80C1FDE0
void func_80C1FE0C(void); // func_80C1FE0C
void func_80C1FE20(void); // func_80C1FE20
void func_80C1FE30(void); // func_80C1FE30
void func_80C1FE80(void); // func_80C1FE80
void func_80C1FF30(void); // func_80C1FF30
void func_80C1FF88(void); // func_80C1FF88
void func_80C2003C(void); // func_80C2003C
void func_80C200B8(void); // func_80C200B8
void func_80C2011C(void); // func_80C2011C
void func_80C2016C(void); // func_80C2016C
void func_80C20274(void); // func_80C20274
void func_80C20334(void); // func_80C20334
void func_80C20484(void); // func_80C20484
void func_80C204F0(void); // func_80C204F0
void func_80C20540(void); // func_80C20540
void func_80C20590(void); // func_80C20590
void func_80C2066C(void); // func_80C2066C
void func_80C2069C(void); // func_80C2069C
void func_80C2075C(void); // func_80C2075C
void func_80C2077C(void); // func_80C2077C
void func_80C208BC(void); // func_80C208BC
void func_80C208D0(void); // func_80C208D0
void func_80C20A74(void); // func_80C20A74
void func_80C20B88(void); // func_80C20B88
void func_80C20C24(void); // func_80C20C24
void func_80C20D64(void); // func_80C20D64
void func_80C20E90(void); // func_80C20E90
void func_80C21250(void); // func_80C21250
void func_80C21320(void); // func_80C21320
void func_80C21414(void); // func_80C21414
void func_80C21468(void); // func_80C21468
void func_80C215E4(void); // func_80C215E4
void func_80C21790(void); // func_80C21790
void func_80C21858(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80C21858
void func_80C219D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C219D4
void func_80C21B9C(void); // func_80C21B9C
void func_80C22350(void); // func_80C22350
void func_80C22400(void); // func_80C22400
void func_80C2247C(void); // func_80C2247C
void func_80C224D8(void); // func_80C224D8
void func_80C227E8(void); // func_80C227E8
void func_80C22880(void); // func_80C22880
void func_80C2291C(void); // func_80C2291C
void func_80C229AC(void); // func_80C229AC
void func_80C229EC(void); // func_80C229EC
void func_80C229FC(void); // func_80C229FC
void func_80C22A40(void); // func_80C22A40
void func_80C22B30(void); // func_80C22B30
void func_80C22B40(void); // func_80C22B40
void func_80C22D40(void); // func_80C22D40
void func_80C22DDC(void); // func_80C22DDC
void func_80C22DEC(void); // func_80C22DEC
void func_80C230DC(void); // func_80C230DC
void func_80C23154(void); // func_80C23154
void func_80C23230(void); // func_80C23230
void func_80C232D8(void); // func_80C232D8
void func_80C232E8(void); // func_80C232E8
void func_80C23304(void); // func_80C23304
void func_80C23330(void); // func_80C23330
void func_80C23398(void); // func_80C23398
void func_80C23460(void); // func_80C23460
void func_80C23508(void); // func_80C23508
void func_80C23518(void); // func_80C23518
void func_80C23534(void); // func_80C23534
void func_80C23560(void); // func_80C23560
void func_80C235C8(void); // func_80C235C8
void func_80C23690(void); // func_80C23690
void func_80C23738(void); // func_80C23738
void func_80C23748(void); // func_80C23748
void func_80C23764(void); // func_80C23764
void func_80C23790(void); // func_80C23790
void func_80C237F8(void); // func_80C237F8
void func_80C238C0(void); // func_80C238C0
void func_80C23970(void); // func_80C23970
void func_80C23980(void); // func_80C23980
void func_80C2399C(void); // func_80C2399C
void func_80C239C8(void); // func_80C239C8
void func_80C23A30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C23A30
void func_80C23A7C(void); // func_80C23A7C
void func_80C23C90(void); // func_80C23C90
void func_80C23D50(void); // func_80C23D50
void func_80C23D60(void); // func_80C23D60
void func_80C23DDC(void); // func_80C23DDC
void func_80C23E18(void); // func_80C23E18
void func_80C23E44(void); // func_80C23E44
void func_80C23F14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C23F14
void func_80C23F6C(void); // func_80C23F6C
void func_80C24360(void); // func_80C24360
void func_80C24428(void); // func_80C24428
void func_80C24504(void); // func_80C24504
void func_80C2457C(void); // func_80C2457C
void func_80C2478C(void); // func_80C2478C
void func_80C24838(void); // func_80C24838
void func_80C248A8(void); // func_80C248A8
void func_80C24A00(void); // func_80C24A00
void func_80C24BD0(void); // func_80C24BD0
void func_80C24BE0(void); // func_80C24BE0
void func_80C24C34(void); // func_80C24C34
void func_80C24C44(void); // func_80C24C44
void func_80C24CD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C24CD0
void func_80C24E4C(void); // func_80C24E4C
void func_80C25000(void); // func_80C25000
void func_80C25360(void); // func_80C25360
void func_80C253D0(void); // func_80C253D0
void func_80C255DC(void); // func_80C255DC
void func_80C25630(void); // func_80C25630
void func_80C25640(void); // func_80C25640
void func_80C25654(void); // func_80C25654
void func_80C25698(void); // func_80C25698
void func_80C256AC(void); // func_80C256AC
void func_80C25710(void); // func_80C25710
void func_80C2572C(void); // func_80C2572C
void func_80C25780(void); // func_80C25780
void func_80C25794(void); // func_80C25794
void func_80C257A4(void); // func_80C257A4
void func_80C258A0(void); // func_80C258A0
void func_80C2590C(void); // func_80C2590C
void func_80C259E8(void); // func_80C259E8
void func_80C25A0C(void); // func_80C25A0C
void func_80C25ABC(void); // func_80C25ABC
void func_80C25AE8(void); // func_80C25AE8
void func_80C25BC0(void); // func_80C25BC0
void func_80C25C34(void); // func_80C25C34
void func_80C25C44(void); // func_80C25C44
void func_80C25D40(void); // func_80C25D40
void func_80C25D84(void); // func_80C25D84
void func_80C25D94(void); // func_80C25D94
void func_80C25E14(void); // func_80C25E14
void func_80C25E38(void); // func_80C25E38
void func_80C25EB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); // func_80C25EB0
void func_80C25EF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80C25EF0
void func_80C25F4C(void); // func_80C25F4C

#endif
