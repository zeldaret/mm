#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <z64.h>

float fabsf(float f);
#pragma intrinsic(fabsf)
float sqrtf(float f);
#pragma intrinsic(sqrtf)
double sqrt(double d);
#pragma intrinsic(sqrt)

void bootproc(void); // func_80080060
void Idle_ClearMemory(void* begin, void* end); // func_80080150
void Idle_InitFramebuffer(u32* ptr, u32 numBytes, u32 value); // func_80080180
void Idle_InitScreen(void); // func_8008019C
void Idle_InitMemory(void); // func_800801EC
void Idle_InitCodeAndMemory(void); // func_80080250
void Main_ThreadEntry(void* arg); // func_80080300
void func_8008038C(void); // func_8008038C
void Idle_ThreadEntry(void* arg); // func_80080514
void ViConfig_UpdateVi(u32 arg0); // func_800805E0
void ViConfig_UpdateBlack(void); // func_80080748
s32 DmaMgr_DMARomToRam(u32 src, void* dst, u32 size); // func_80080790
void DmaMgr_DmaCallback0(OSPiHandle* pOParm1, OSIoMesg* pOParm2, s32 OParm3); // func_800808D4
DmaEntry* Dmamgr_FindDmaEntry(u32 vromAddr); // func_800808F4
u32 Dmamgr_TranslateVromToRom(u32 vromAddr); // func_80080950
s32 Dmamgr_FindDmaIndex(u32 vromAddr); // func_800809BC
char* func_800809F4(u32 param_1); // func_800809F4
void DmaMgr_ProcessMsg(DmaRequest* request); // func_80080A08
void Dmamgr_ThreadEntry(void* arg); // func_80080B84
s32 DmaMgr_SendRequestImpl(DmaRequest* request, void* vramStart, u32 vromStart, u32 size, UNK_TYPE4 unused, OSMesgQueue* callback, void* callbackMesg); // func_80080C04
s32 DmaMgr_SendRequest0(void* vramStart, u32 vromStart, u32 size); // func_80080C90
void Dmamgr_Start(void); // func_80080D0C
void Dmamgr_Stop(void); // func_80080E00
u8* Yaz0_LoadFirstChunk(void); // func_80080E30
u8* Yaz0_LoadNextChunk(void* currDecompPos); // func_80080ED0
s32 Yaz0_Decompress(u8* src, u8* dest); // func_80080FF0
void Yaz0_LoadAndDecompressFile(u32 romStart, u32 vramStart, u32 size); // func_80081178
void IrqMgr_AddClient(IrqMgr* irqmgr, OSMesgQueueListNode* param_2, OSMesgQueue* param_3); // func_80081250
void IrqMgr_RemoveClient(IrqMgr* irqmgr, OSMesgQueueListNode* remove); // func_800812DC
void IrqMgr_SendMesgForClient(IrqMgr* irqmgr, OSMesg msg); // func_80081368
void IrqMgr_JamMesgForClient(IrqMgr* irqmgr, OSMesg msg); // func_800813B8
void IrqMgr_HandlePreNMI(IrqMgr* irqmgr); // func_8008141C
void IrqMgr_CheckStack(void); // func_800814B4
void IrqMgr_HandlePRENMI450(IrqMgr* irqmgr); // func_800814D4
void IrqMgr_HandlePRENMI480(IrqMgr* irqmgr); // func_80081550
void IrqMgr_HandlePRENMI500(IrqMgr* irqmgr); // func_800815A8
void IrqMgr_HandleRetrace(IrqMgr* irqmgr); // func_800815CC
void IrqMgr_ThreadEntry(IrqMgr* irqmgr); // func_80081684
void IrqMgr_Create(IrqMgr* irqmgr, void* stack, OSPri pri, u8 retraceCount); // func_80081754
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
void Load_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart); // func_800849A0
s32 Load_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 allocatedVRamAddr, u32 allocatedBytes); // func_80084C0C
void* Load_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart); // func_80084CD0
void Load2_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart); // func_80084DB0
s32 Load2_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, u32 allocatedVRamAddr); // func_8008501C
void* Load2_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd); // func_800850C8
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
void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace, const char* name); // func_80085320
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
s32 rand(void); // func_80086FA0
void randSetSeed(u32 seed); // func_80086FD0
f32 randZeroOne(void); // func_80086FDC
f32 randPlusMinusPoint5(void); // func_80087030
void func_80087088(UNK_PTR param_1, UNK_TYPE4 param_2); // func_80087088
void func_80087090(s32* param_1); // func_80087090
f32 func_800870B8(u32* param_1); // func_800870B8
f32 func_80087104(u32* param_1); // func_80087104
void arena_lock_init(Arena* heap); // func_80087160
void arena_lock(Arena* heap); // func_8008718C
void arena_unlock(Arena* heap); // func_800871B4
ArenaNode* heap_get_tail(Arena* param_1); // func_800871DC
void __osMallocInit(Arena* heap, u32 heapBase, u32 heapSize); // func_8008720C
void __osMallocAddBlock(Arena* heap, u32 start, u32 size); // func_8008725C
void __osMallocCleanup(Arena* heap); // func_800872FC
u32 __osMallocIsInitalized(Arena* heap); // func_8008731C
void* __osMalloc(Arena* heap, u32 size); // func_80087324
void* __osMallocR(Arena* heap, u32 size); // func_80087408
void __osFree(Arena* heap, void* ptr); // func_800874EC
void* __osRealloc(Arena* heap, void* oldPtr, u32 newSize); // func_800875E4
void __osAnalyzeArena(Arena* heap, u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated); // func_80087714
s32 __osCheckArena(Arena* heap); // func_800877C4
void* proutSprintf(void* s, char* buf, size_t n); // func_80087830
int vsprintf(char* dst, char* fmt, va_list args); // func_80087854
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
short sins(unsigned short x); // func_80088510
OSTask* _VirtualToPhysicalTask(OSTask* intp); // func_80088580
void osSpTaskLoad(OSTask* intp); // func_8008868C
void osSpTaskStartGo(OSTask* tp); // func_800887F4
long long __ull_rshift(unsigned long long left, unsigned long long right); // func_80088840
unsigned long long __ull_rem(unsigned long long left, unsigned long long right); // func_8008886C
unsigned long long __ull_div(unsigned long long left, unsigned long long right); // func_800888A8
long long __ll_lshift(long long left, long long right); // func_800888E4
long long __ll_rem(long long left, unsigned long long right); // func_80088910
long long __ll_div(long long left, long long right); // func_8008894C
long long __ll_mul(long long left, long long right); // func_800889A8
void __ull_divremi(unsigned long long* quotient, unsigned long long* remainder, unsigned long long dividend, unsigned short divisor); // func_800889D8
long long __ll_mod(long long left, long long right); // func_80088A38
long long __ll_rshift(long long left, long long right); // func_80088AD4
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
s32 osContStartReadData(OSMesgQueue* mq); // func_80089F90
void osContGetReadData(OSContPad* data); // func_8008A014
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
void guPerspectiveF(float mf[4][4], u16* perspNorm, float fovy, float aspect, float near, float far, float scale); // func_8008AA50
void guPerspective(Mtx* m, u16* perspNorm, float fovy, float aspect, float near, float far, float scale); // func_8008AC80
s32 __osSpRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size); // func_8008ACE0
s32 __osSiRawStartDma(s32 direction, void* dramAddr); // func_8008AD70
void func_8008AE20(void); // func_8008AE20
void osViBlack(u8 active); // func_8008AE70
s32 __osSiRawReadIo(u32 devAddr, u32* data); // func_8008AEE0
OSId osGetThreadId(OSThread* t); // func_8008AF30
void osSpTaskYield(void); // func_8008AF50
s32 __osPfsRWInode(OSPfs* param_1, __OSInode* param_2, u8 param_3, u8 param_4); // func_8008AF70
s32 osPfsReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer); // func_8008B044
void func_8008B3C0(void); // func_8008B3C0
void func_8008B490(void); // func_8008B490
void func_8008B554(void); // func_8008B554
void guMtxIdentF(float mf[4][4]); // func_8008B600
void osViSetMode(OSViMode* modep); // func_8008B650
void __osGetConfig(void); // func_8008B6B0
void __osSetConfig(void); // func_8008B6C0
void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp); // func_8008B6D0
void guLookAt(Mtx* m, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp); // func_8008B974
void func_8008B9F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8008B9F0
void func_8008BD24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8008BD24
s32 osStopTimer(OSTimer* t); // func_8008BE70
u32 __osProbeTLB(void* param_1); // func_8008BF60
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt); // func_8008C020
void __osPiCreateAccessQueue(void); // func_8008C190
void __osPiGetAccess(void); // func_8008C1E0
void __osPiRelAccess(void); // func_8008C224
void __osDevMgrMain(void* arg); // func_8008C260
void func_8008C640(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16, UNK_TYPE4 param_17, UNK_TYPE4 param_18); // func_8008C640
s32 osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size); // func_8008C670
void func_8008C740(void); // func_8008C740
void func_8008C7B4(void); // func_8008C7B4
void func_8008C8B0(void); // func_8008C8B0
void func_8008CC00(void); // func_8008CC00
void func_8008CD64(void); // func_8008CD64
void func_8008CF10(void); // func_8008CF10
void func_8008CFE4(void); // func_8008CFE4
u32 osGetCount(void); // func_8008D2C0
void func_8008D2E0(void); // func_8008D2E0
u32 osGetMemSize(void); // func_8008D350
void func_8008D470(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8008D470
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m); // func_8008D640
f32 sqrtf(f32 __x); // func_8008D700
s32 osAfterPreNMI(void); // func_8008D710
s32 osContStartQuery(OSMesgQueue* mq); // func_8008D730
void osContGetQuery(OSContStatus* data); // func_8008D7AC
void guLookAtHiliteF(float mf[4][4], UNK_PTR l, int* h, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp, float xl1, float yl1, float zl1, float xl2, float yl2, float zl2, int twidth, int theight); // func_8008D7D0
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight); // func_8008DF90
int _Printf(printf_func pfn, void* arg, char* fmt, va_list ap); // func_8008E050
void _Putfld(_Pft* px, va_list* pap, unsigned char code, unsigned char* ac); // func_8008E698
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
OSTime __osInsertTimer(OSTimer* t); // func_8008F644
void func_8008F7D0(void); // func_8008F7D0
int __osSpDeviceBusy(void); // func_8008FA00
int __osSiDeviceBusy(void); // func_8008FA30
void func_8008FA60(void); // func_8008FA60
s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag); // func_8008FAB0
void osSetThreadPri(OSThread* t, OSPri pri); // func_8008FC00
OSPri osGetThreadPri(OSThread* t); // func_8008FCE0
void func_8008FD00(void); // func_8008FD00
void osViSwapBuffer(void* frameBufPtr); // func_8008FE60
void guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z); // func_8008FEB0
void guPosition(Mtx* m, float r, float p, float h, float s, float x, float y, float z); // func_80090058
void func_800900C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800900C0
OSYieldResult osSpTaskYielded(OSTask* task); // func_800902A0
s32 memcmp(void* __s1, void* __s2, size_t __n); // func_80090300
OSTime osGetTime(void); // func_80090420
void guRotateF(float mf[4][4], float a, float x, float y, float z); // func_800904B0
void guRotate(Mtx* m, float a, float x, float y, float z); // func_80090634
void __osSetGlobalIntMask(void); // func_80090680
void func_800906D0(void); // func_800906D0
void func_80090810(void); // func_80090810
void func_80090900(void); // func_80090900
s32 osAiSetFrequency(u32 frequency); // func_80090AF0
s32 __osContRamRead(OSMesgQueue* mq, int channel, u16 address, u8* buffer); // func_80090C40
void func_80090E70(void); // func_80090E70
u8 __osContAddressCrc(u16 addr); // func_800910A0
u8 __osContDataCrc(u8* data); // func_80091170
OSThread* __osGetActiveQueue(void); // func_80091210
void guNormalize(float* x, float* y, float* z); // func_80091220
void __osSetCompare(u32 value); // func_80091280
u32 __osGetCompare(void); // func_80091290
u32 osDpGetStatus(void); // func_800912A0
void osDpSetStatus(u32 data); // func_800912B0
void _bcopy(void* __src, void* __dest, size_t __n); // func_800912C0
void __osResetGlobalIntMask(void); // func_800915D0
void func_80091630(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80091630
void func_80091808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_80091808
void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale); // func_800918A0
void guOrtho(Mtx* m, float l, float r, float b, float t, float n, float f, float scale); // func_800919F4
OSIntMask __osDisableInt(void); // func_80091A60
void __osRestoreInt(OSIntMask im); // func_80091AD0
void __osViInit(void); // func_80091AF0
void __osViSwapContext(void); // func_80091C10
OSMesgQueue* osPiGetCmdQueue(void); // func_80091F10
f32 __cosf(f32 __x); // func_80091F40
void func_800920B0(void); // func_800920B0
void osViSetSpecialFeatures(u32 func); // func_80092100
short coss(unsigned short x); // func_80092260
void osSetTime(OSTime ticks); // func_80092290
void func_800922C0(void); // func_800922C0
void osViSetEvent(OSMesgQueue* mq, OSMesg m, u32 retraceCount); // func_800923E0
s32 osPfsIsPlug(OSMesgQueue* queue, u8* pattern); // func_80092440
void func_800925CC(void); // func_800925CC
void func_80092680(void); // func_80092680
void func_80092730(void); // func_80092730
OSPiHandle* osCartRomInit(void); // func_80092920
void func_80092A80(void); // func_80092A80
s32 __osPfsSelectBank(OSPfs* pfs, UNK_TYPE4 param_2); // func_80092C00
s32 osContSetCh(u8 ch); // func_80092C80
u32 __osSetFpcCsr(u32 value); // func_80092CE0
u32 __osGetFpcCsr(void); // func_80092CF0
void func_80092D00(void); // func_80092D00
void func_80092EE0(void); // func_80092EE0
void func_800930E8(void); // func_800930E8
void func_800931F0(void); // func_800931F0
void func_80093728(void); // func_80093728
void func_80093A00(void); // func_80093A00
u32 osAiGetLength(void); // func_80093BA0
void func_80093BB0(void); // func_80093BB0
void osMapTLBRdb(void); // func_80093C00
void osYieldThread(void); // func_80093C60
void func_80093CC0(void); // func_80093CC0
u32 __osGetCause(void); // func_80093D90
s32 __osContRamWrite(OSMesgQueue* mq, int channel, u16 address, u8* buffer, int force); // func_80093DA0
void func_80093FF0(void); // func_80093FF0
int osSetTimer(OSTimer* t, OSTime value, OSTime interval, OSMesgQueue* mq, OSMesg msg); // func_80094150
void _Ldtob(_Pft* px, unsigned char code); // func_800942E0
void _Ldunscale(void); // func_80094770
void _Genld(_Pft* px, unsigned char code, unsigned char* p, short nsig, short xexp); // func_80094828
ldiv_t ldiv(long numer, long denom); // func_80094DF0
lldiv_t lldiv(long long numer, long long denom); // func_80094E74
void _Litob(_Pft* px, unsigned char code); // func_80094F80
s32 __osSiRawWriteIo(u32 devAddr, u32 data); // func_80095220
u32 __osSpGetStatus(void); // func_80095270
void __osSpSetStatus(u32 value); // func_80095280
void osCreateViManager(OSPri pri); // func_800952A0
void viMgrMain(OSDevMgr* iParm1); // func_80095420
__OSViContext* __osViGetCurrentContext(void); // func_800955B0
void osWritebackDCacheAll(void); // func_800955C0
OSThread* __osGetCurrFaultedThread(void); // func_800955F0
void func_80095600(void); // func_80095600
void guMtxF2L(float mf[4][4], Mtx* m); // func_80095740
void osStartThread(OSThread* param_1); // func_800957B0
void osViSetYScale(f32 value); // func_80095900
void osViSetXScale(f32 value); // func_80095950
long long __d_to_ll(double d); // func_80095A60
long long __f_to_ll(float f); // func_80095A7C
unsigned long long __d_to_ull(double d); // func_80095A98
unsigned long long __f_to_ull(float f); // func_80095B38
double __ll_to_d(long long l); // func_80095BD4
float __ll_to_f(long long l); // func_80095BEC
double __ull_to_d(unsigned long long l); // func_80095C04
float __ull_to_f(unsigned long long l); // func_80095C38
void func_80095C70(void); // func_80095C70
void func_80096360(void); // func_80096360
void func_80096410(void); // func_80096410
void func_800964D0(void); // func_800964D0
s32 __osSpSetPc(u32 data); // func_80096510
void func_80096540(void); // func_80096540
void func_80096770(int param_1, UNK_PTR param_2, UNK_PTR param_3); // func_80096770
void func_800967A0(void); // func_800967A0
u32 __osGetWatchLo(void); // func_80096810
void __osSetWatchLo(u32 value); // func_80096820
f32 func_80096830(f32 param_1, f32 param_2); // func_80096830
void* func_80096880(void* param_1, u8 param_2, s32 param_3); // func_80096880
s32 func_800968B0(const char* str1, const char* str2); // func_800968B0
char* func_800968f0(char* param_1, char* param_2); // func_800968F0
void func_80096930(void); // func_80096930
void EnAObj_Init(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5AC0
void EnAObj_Destroy(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5B6C
void EnAObj_Update1(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5B98
void EnAObj_Update2(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5C28
void EnAObj_Update(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5C60
void EnAObj_Draw(ActorEnAObj* this, GlobalContext* ctxt); // func_800A5CB8
void EnItem00_UpdateForNewObjectId(ActorEnItem00* this, GlobalContext* ctxt, f32* puParm3, f32* pfParm4); // func_800A5D00
void EnItem00_Init(ActorEnItem00* this, GlobalContext* ctxt); // func_800A5D70
void EnItem00_Destroy(ActorEnItem00* this, GlobalContext* ctxt); // func_800A637C
void func_800A63A8(ActorEnItem00* this, GlobalContext* ctxt); // func_800A63A8
void func_800A640C(ActorEnItem00* this); // func_800A640C
void func_800A6650(void); // func_800A6650
void func_800A6780(void); // func_800A6780
void EnItem00_Update1(ActorEnItem00* this, GlobalContext* ctxt); // func_800A6A40
void EnItem00_Update(ActorEnItem00* this, GlobalContext* ctxt); // func_800A6B98
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
void EffectBlure_Initcommon(EffBlureParams* params); // func_800A8558
void EffectBlure_Init1(EffBlureParams* params, EffBlureInit1* init); // func_800A8610
void EffectBlure_Init2(EffBlureParams* params, EffBlureInit2* init); // func_800A8720
void EffectBlure_Destroy(EffBlureParams* params); // func_800A8854
s32 EffectBlure_Update(EffBlureParams* params); // func_800A8860
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
void EffectBlure_Draw(EffBlureParams* params, GraphicsContext* gCtxt); // func_800AB0EC
void EffectShieldParticle_Init(EffShieldParticleParams* params, EffShieldParticleInit* init); // func_800AB5D0
void EffectShieldParticle_Destroy(EffShieldParticleParams* params); // func_800AB808
s32 EffectShieldParticle_Update(EffShieldParticleParams* params); // func_800AB894
void EffectShieldParticle_CalculateColors(EffShieldParticleParams* params, ColorRGBA8* primColor, ColorRGBA8* envColor); // func_800AB9F8
void EffectShieldParticle_Draw(EffShieldParticleParams* params, GraphicsContext* gCtxt); // func_800AC718
void EffectSpark_Init(EffSparkParams* params, EffSparkParams* init); // func_800ACBF0
void EffectSpark_Destroy(EffSparkParams* params); // func_800ACFCC
s32 EffectSpark_Update(EffSparkParams* params); // func_800ACFD8
void EffectSpark_Draw(EffSparkParams* params, GraphicsContext* gCtxt); // func_800AD09C
void func_800AE2A0(void); // func_800AE2A0
void func_800AE434(GlobalContext* ctxt, ColorRGBA8* color, short sParm3, short sParm4); // func_800AE434
void func_800AE5A0(GlobalContext* ctxt); // func_800AE5A0
void func_800AE5E4(void); // func_800AE5E4
void func_800AE778(GlobalContext* ctxt, ColorRGBA8* color, short param_3, short param_4); // func_800AE778
void func_800AE8EC(GlobalContext* ctxt); // func_800AE8EC
void func_800AE930(CollisionContext* bgCtxt, int param_2, float* param_3, float param_4, short param_5, BgPolygon* param_6, int param_7); // func_800AE930
void func_800AEF44(void); // func_800AEF44
void EffectTireMark_InitParticle(EffTireMarkParticle* particle); // func_800AEF70
void EffectTireMark_Init(EffTireMarkParams* params, EffTireMarkInit* init); // func_800AEFA0
void EffectTireMark_Destroy(EffTireMarkParams* params); // func_800AF044
s32 EffectTireMark_Update(EffTireMarkParams* params); // func_800AF050
void EffectTireMark_InitVertices(F3DVertexColor* vertices, EffTireMarkParticle* particle, s32 index, s32 alpha); // func_800AF284
void EffectTireMark_Draw(EffTireMarkParams* params, GraphicsContext* gCtxt); // func_800AF310
GlobalContext* Effect_GetContext(void); // func_800AF710
void* Effect_GetParams(s32 index); // func_800AF720
void Effect_InitCommon(EffCommon* common); // func_800AF87C
void Effect_Init(GlobalContext* ctxt); // func_800AF890
void Effect_Add(GlobalContext* ctxt, s32* index, s32 type, u8 param_4, u8 param_5, void* initParams); // func_800AF960
void Effect_DrawAll(GraphicsContext* gCtxt); // func_800AFB24
void Effect_UpdateAll(GlobalContext* ctxt); // func_800AFC60
void Effect_Destroy(GlobalContext* ctxt, s32 index); // func_800AFDCC
void Effect_DestroyAll(GlobalContext* ctxt); // func_800AFF24
void EffectSS_Init(GlobalContext* ctxt, s32 numEntries); // func_800B0050
void EffectSS_Clear(GlobalContext* ctxt); // func_800B0140
LoadedParticleEntry* EffectSS_GetTable(void); // func_800B0200
void EffectSS_Delete(LoadedParticleEntry* param_1); // func_800B0210
void EffectSS_ResetEntry(LoadedParticleEntry* particle); // func_800B0270
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
void EffectSS_SpawnDust(GlobalContext* ctxt, u16 flags, Vec3f* position, Vec3f* velocity, Vec3f* acceleration, ColorRGBA8* color1, ColorRGBA8* color2, s16 scale, s16 scaleChangePerFrame, s16 life, u8 type); // func_800B0D2C
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
void EffectSS_SpawnSparkle(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE4* param_5, UNK_TYPE4* param_6, UNK_TYPE2 param_7, int param_8); // func_800B16F4
void func_800B1830(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800B1830
void EffectSS_SpawnBomb2(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4); // func_800B1908
void func_800B1970(UNK_TYPE4 param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B1970
void EffectSS_SpawnBlast(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, ColorRGBA8* param_5, ColorRGBA8* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); // func_800B19E0
void func_800B1A70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B1A70
void func_800B1AC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_800B1AC4
void func_800B1B10(void); // func_800B1B10
void EffectSS_SpawnGSpark(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, Vec3f* pzParm4, Vec3f* param_5, ColorRGBA8* param_6, ColorRGBA8* param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B1B4C
void func_800B1BDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B1BDC
void func_800B1C70(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800B1C70
void func_800B1CC4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B1CC4
void func_800B1DC8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_800B1DC8
void EffectSS_SpawnDodongoFire(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B1E0C
void EffectSS_SpawnBubble(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B1E94
void EffectSS_SpawnGRipple(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE2 uParm3, UNK_TYPE2 uParm4, UNK_TYPE2 param_5); // func_800B1EF4
void EffectSS_SpawnGSplash(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE4* puParm3, UNK_TYPE4* puParm4, UNK_TYPE1 uParm5, UNK_TYPE2 param_6); // func_800B1F4C
void EffectSS_SpawnGFire(UNK_TYPE4 uParm1, Vec3f* pzParm2); // func_800B1FE0
void EffectSS_SpawnLightning(UNK_TYPE4 uParm1, Vec3f* pzParm2, ColorRGBA8* pzParm3, ColorRGBA8* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B2018
void func_800B2090(UNK_TYPE4 param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); // func_800B2090
void EffectSS_SpawnBigOctoBubble2(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); // func_800B210C
void EffectSS_SpawnFragment(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE4 param_9); // func_800B219C
void func_800B221C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B221C
void func_800B2364(void); // func_800B2364
void EffectSS_SpawnStick(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE2 uParm3); // func_800B23D8
void EffectSS_SpawnSplash(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B242C
void func_800B249C(void); // func_800B249C
void EffectSS_SpawnStone1(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE4 uParm3); // func_800B25D8
void EffectSS_SpawnHitMark(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, UNK_TYPE2 uParm3, Vec3f* pzParm4); // func_800B262C
void func_800B2684(void); // func_800B2684
void func_800B26A8(void); // func_800B26A8
void EffectSS_SpawnPhantomGanonFlash(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE1 param_5); // func_800B26D4
void EffectSS_SpawnKakarikoFire(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE1 param_6); // func_800B2738
void EffectSS_SpawnSoldierSearchBall(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7); // func_800B27A0
void EffectSS_SpawnShard(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE4 param_13, UNK_TYPE2 param_14, UNK_TYPE2 param_15, UNK_TYPE4 param_16); // func_800B2810
void EffectSS_SpawnIcePiece(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE4 uParm3, Vec3f* pzParm4, Vec3f* param_5, UNK_TYPE4 param_6); // func_800B28C8
void func_800B2930(void); // func_800B2930
void EffectSS_SpawnEnemyIce(UNK_TYPE4 uParm1, Actor* pzParm2, Vec3f* pzParm3, ColorRGBA8* pzParm4, ColorRGBA8* param_5, UNK_TYPE4 param_6); // func_800B2AC4
void func_800B2B44(void); // func_800B2B44
void func_800B2B7C(void); // func_800B2B7C
void func_800B2BC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800B2BC0
void EffectSS_SpawnFireTail(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE4 uParm4, Vec3f* param_5, UNK_TYPE2 param_6, ColorRGBA8* param_7, ColorRGBA8* param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE4 param_11); // func_800B2C48
void func_800B2CE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_800B2CE0
void func_800B2DA4(void); // func_800B2DA4
void EffectSS_SpawnEnemyFire(UNK_TYPE4 uParm1, Actor* pzParm2, Vec3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B2DF4
void func_800B2E6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); // func_800B2E6C
void EffectSS_SpawnExtra(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); // func_800B2F18
void EffectSS_SpawnDeadDekuBaba(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE1* param_5, UNK_TYPE1* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE4 param_9); // func_800B2F80
void func_800B3030(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE4 param_7); // func_800B3030
void EffectSS_SpawnDeadDodongo(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE1* param_5, UNK_TYPE1* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); // func_800B3088
void EffectSS_SpawnDeadDekuScrub(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); // func_800B3144
void func_800B31BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); // func_800B31BC
void EffectSS_SpawnIceSmoke(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5); // func_800B320C
void EffectSS_SpawnIceBlock(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5); // func_800B326C
void func_800B32D0(GameState* ctxt); // func_800B32D0
void func_800B3644(void); // func_800B3644
void DLF_LoadGameState(GameStateOverlay* gameState); // func_800B3880
void DLF_FreeGameState(GameStateOverlay* gameState); // func_800B39A4
void Actor_PrintLists(ActorContext* actCtxt); // func_800B3AD0
void Actor_SetDrawParams(ActorShape* actorShape, f32 yOffset, ActorShadowFunc func, f32 scale); // func_800B3BA4
void Actor_PostDraw(Actor* actor, LightMapper* mapper, GlobalContext* ctxt, u32 displayList, ColorRGBA8* color); // func_800B3BC8
void func_800B3FC0(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B3FC0
void func_800B4024(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B4024
void func_800B4088(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B4088
void func_800B40B8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B40B8
void func_800B40E0(GlobalContext* ctxt, int iParm2, z_Matrix* pzParm3, int iParm4, float param_5, float param_6, float param_7); // func_800B40E0
void func_800B42F8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt); // func_800B42F8
void func_800B4A98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800B4A98
void func_800B4AEC(GlobalContext* ctxt, Actor* actor, f32 param_3); // func_800B4AEC
void func_800B4B50(Actor* actor, int iParm2, GlobalContext* pzParm3); // func_800B4B50
void func_800B4EDC(GlobalContext* ctxt, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4); // func_800B4EDC
void func_800B4F40(TargetContext* targetContext, int param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5); // func_800B4F40
void func_800B4F78(TargetContext* targetContext, u8 type, GlobalContext* ctxt); // func_800B4F78
void func_800B5040(TargetContext* targetContext, Actor* actor, u8 type, GlobalContext* ctxt); // func_800B5040
void Actor_TargetContextInit(TargetContext* targetCtxt, Actor* actor, GlobalContext* ctxt); // func_800B51A4
void func_800B5208(TargetContext* targetCtxt, GlobalContext* ctxt); // func_800B5208
void func_800B5814(TargetContext* targetContext, ActorPlayer* player, Actor* param_3, GlobalContext* ctxt); // func_800B5814
u32 Actor_GetSwitchFlag(GlobalContext* ctxt, s32 flag); // func_800B5BB0
void Actor_SetSwitchFlag(GlobalContext* ctxt, s32 flag); // func_800B5BF4
void Actor_UnsetSwitchFlag(GlobalContext* ctxt, s32 flag); // func_800B5C34
u32 Actor_GetChestFlag(GlobalContext* ctxt, u32 flag); // func_800B5C78
void Actor_SetChestFlag(GlobalContext* ctxt, u32 flag); // func_800B5C90
void Actor_SetAllChestFlag(GlobalContext* ctxt, u32 flags); // func_800B5CAC
u32 Actor_GetAllChestFlag(GlobalContext* ctxt); // func_800B5CB8
u32 Actor_GetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CC4
void Actor_SetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CDC
void Actor_UnsetRoomCleared(GlobalContext* ctxt, u32 roomNumber); // func_800B5CF8
u32 Actor_GetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber); // func_800B5D18
void Actor_SetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber); // func_800B5D30
void Actor_UnsetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber); // func_800B5D4C
u32 Actor_GetCollectibleFlag(GlobalContext* ctxt, s32 index); // func_800B5D6C
void Actor_SetCollectibleFlag(GlobalContext* ctxt, s32 index); // func_800B5DB0
void Actor_TitleCardContextInit(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5DF0
void Actor_TitleCardCreate(GlobalContext* ctxt, TitleCardContext* titleCtxt, u32 texture, s16 param_4, s16 param_5, u8 param_6, u8 param_7); // func_800B5E0C
void Actor_Nop800B5E50(UNK_TYPE4 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4); // func_800B5E50
void Actor_TitleCardUpdate(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5E68
void Actor_TitleCardDraw(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B5F24
UNK_TYPE4 func_800B6434(GlobalContext* ctxt, TitleCardContext* titleCtxt); // func_800B6434
UNK_TYPE4 func_800B645C(void); // func_800B645C
void func_800B6468(GlobalContext* ctxt); // func_800B6468
void func_800B6474(GlobalContext* ctxt); // func_800B6474
UNK_TYPE4 func_800B648C(GlobalContext* ctxt, UNK_TYPE1 param_2, UNK_TYPE1 param_3, float param_4, Vec3f* param_5); // func_800B648C
f32 func_800B64FC(GlobalContext* ctxt, f32 fParm2, Vec3f* pzParm3, u32* puParm4); // func_800B64FC
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
void Actor_SetVelocityYRotationAndGravity(Actor* actor); // func_800B6A10
void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor); // func_800B6A88
void Actor_SetVelocityXYRotation(Actor* actor); // func_800B6AB4
void Actor_SetVelocityAndMoveXYRotation(Actor* actor); // func_800B6B24
void Actor_SetVelocityXYRotationReverse(Actor* actor); // func_800B6B50
void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor); // func_800B6BD8
void func_800B6C04(Actor* actor, float fParm2); // func_800B6C04
void func_800B6C58(Actor* actor, UNK_TYPE4 param_2); // func_800B6C58
s16 Actor_YawBetweenActors(Actor* from, Actor* to); // func_800B6CD4
s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to); // func_800B6D00
s16 Actor_YawToPoint(Actor* actor, Vec3f* point); // func_800B6D2C
s16 Actor_PitchBetweenActors(Actor* from, Actor* to); // func_800B6D50
s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to); // func_800B6D7C
s16 Actor_PitchToPoint(Actor* actor, Vec3f* point); // func_800B6DA8
f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2); // func_800B6DCC
f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point); // func_800B6DF8
f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2); // func_800B6E1C
f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point); // func_800B6E48
void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point); // func_800B6E6C
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
void func_800B72F8(DynaPolyActor* dpactor, f32 a1, s16 a2); // func_800B72F8
s32 Actor_IsLinkFacingActor(Actor* actor, s16 tolerance, GlobalContext* ctxt); // func_800B7320
s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance); // func_800B7378
s32 Actor_IsActorFacingLink(Actor* actor, s16 angle); // func_800B73E0
s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance); // func_800B742C
s32 Actor_IsActorFacingLinkAndWithinRange(Actor* actor, f32 range, s16 tolerance); // func_800B748C
s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance); // func_800B750C
void func_800B75A0(BgPolygon* param_1, Vec3f* param_2, s16* param_3); // func_800B75A0
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
f32* func_800B8248(PosRot* param_1, ActorPlayer* param_2); // func_800B8248
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
UNK_TYPE4 func_800B8A1C(Actor* actor, GlobalContext* ctxt, int iParm3, float fParm4, float param_5); // func_800B8A1C
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
void func_800B8EC8(Actor* actor, u32 uParm2); // func_800B8EC8
void func_800B8EF4(void); // func_800B8EF4
void func_800B8F98(Actor* actor, u16 sfxId); // func_800B8F98
void func_800B8FC0(void); // func_800B8FC0
void func_800B8FE8(void); // func_800B8FE8
void func_800B9010(Actor* actor, UNK_TYPE2 uParm2); // func_800B9010
void func_800B9038(void); // func_800B9038
void func_800B9084(void); // func_800B9084
void func_800B9098(Actor* actor); // func_800B9098
s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, UNK_TYPE arg2, UNK_TYPE arg3, UNK_TYPE arg4); // func_800B90AC
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
s32 func_800BA2FC(GlobalContext* ctxt, Actor* actor, Vec3f* param_3, f32 param_4); // func_800BA2FC
void Actor_DrawAll(GlobalContext* ctxt, ActorContext* aCtxt); // func_800BA42C
void func_800BA6FC(GlobalContext* ctxt, ActorContext* aCtxt); // func_800BA6FC
void func_800BA798(GlobalContext* ctxt, ActorContext* aCtxt); // func_800BA798
void func_800BA8B8(GlobalContext* ctxt, ActorContext* actCtxt); // func_800BA8B8
void func_800BA9B4(void); // func_800BA9B4
void Actor_InsertIntoTypeList(ActorContext* actCtxt, Actor* actor, u8 type); // func_800BAAB4
Actor* Actor_RemoveFromTypeList(GlobalContext* ctxt, ActorContext* actCtxt, Actor* actor); // func_800BAB24
void Actor_FreeOverlay(ActorOverlay* entry); // func_800BABFC
Actor* Actor_Spawn(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 sParm10); // func_800BAC60
ActorInit* Actor_LoadOverlay(ActorContext* actCtxt, s16 index); // func_800BACD4
Actor* Actor_SpawnWithParentAndCutscene(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 variable, u32 cutscene, s32 param_12, Actor* parent); // func_800BAE14
void Actor_SpawnWithParent(ActorContext* actCtxt, Actor* parent, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 variable); // func_800BB0C0
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
void func_800BCBF4(Vec3f* uParm1, GlobalContext* ctxt); // func_800BCBF4
void func_800BCC68(Vec3f* param_1, GlobalContext* ctxt); // func_800BCC68
void func_800BCCDC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800BCCDC
void func_800BD2B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800BD2B4
void func_800BD384(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE1 param_9); // func_800BD384
void func_800BD6E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800BD6E4
void func_800BD888(void); // func_800BD888
void func_800BD9A0(void); // func_800BD9A0
void func_800BD9E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800BD9E0
void func_800BDAA0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); // func_800BDAA0
void func_800BDB6C(void); // func_800BDB6C
void func_800BDC5C(SkelAnime* skelAnime, UNK_PTR animation, UNK_TYPE param_3); // func_800BDC5C
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
void ActorOverlayTable_FaultPrint(void* arg0, void* arg1); // ActorOverlayTable_FaultPrint
void* ActorOverlayTable_FaultAddrConv(void* arg0, void* arg1); // ActorOverlayTable_FaultAddrConv
void ActorOverlayTable_Init(void); // ActorOverlayTable_Init
void ActorOverlayTable_Cleanup(void); // ActorOverlayTable_Cleanup
void BgCheck_PolygonLinkedListNodeInit(BgPolygonLinkedListNode* node, s16* polyIndex, u16 next); // func_800BFB80
void BgCheck_PolygonLinkedListResetHead(u16* head); // func_800BFB9C
void BgCheck_ScenePolygonListsNodeInsert(BgScenePolygonLists* list, u16* head, s16* polyIndex); // func_800BFBAC
void BgCheck_PolygonLinkedListNodeInsert(BgPolygonLinkedList* list, u16* head, s16* polyIndex); // func_800BFC04
void BgCheck_PolygonLinkedListInit(GlobalContext* ctxt, BgPolygonLinkedList* list); // func_800BFC5C
void BgCheck_PolygonLinkedListAlloc(GlobalContext* ctxt, BgPolygonLinkedList* list, u32 numNodes); // func_800BFC70
void BgCheck_PolygonLinkedListReset(BgPolygonLinkedList* list); // func_800BFCC0
u16 BgCheck_AllocPolygonLinkedListNode(BgPolygonLinkedList* list); // func_800BFCCC
void BgCheck_CreateVec3fFromVertex(BgVertex* vertex, Vec3f* vector); // func_800BFCFC
void BgCheck_CreateVertexFromVec3f(BgVertex* vertex, Vec3f* vector); // func_800BFD40
float func_800BFD84(BgPolygon* polygon, float param_2, float param_3); // func_800BFD84
int func_800BFDEC(BgPolygon* param_1, BgPolygon* param_2, unsigned int* param_3, unsigned int* param_4); // func_800BFDEC
s32 BgCheck_PolygonGetMinY(BgPolygon* polygons, BgVertex* vertices); // func_800BFFC4
void BgCheck_PolygonGetNormal(BgPolygon* polygon, f32* normalX, f32* normalY, f32* normalZ); // func_800C003C
void func_800C0094(BgPolygon* param_1, f32 xOffset, f32 yOffset, f32 zOffset, z_Matrix* matrix); // func_800C0094
f32 func_800C01B8(BgPolygon* param_1, Vec3f* param_2); // func_800C01B8
void BgCheck_CreateColTriParamsFromPolygon(BgPolygon* polygon, BgVertex* vertices, ColTriParams* tri); // func_800C0220
void func_800C02C0(BgPolygon* poly, s32 index, CollisionContext* bgCtxt, ColTriParams* tri); // func_800C02C0
void func_800C0340(BgPolygon* param_1, BgVertex* param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C0340
UNK_TYPE4 func_800C0474(BgPolygon* param_1, BgVertex* param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C0474
void func_800C0668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C0668
void func_800C06A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C06A8
void func_800C074C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C074C
void func_800C07F0(void); // func_800C07F0
void BgCheck_PolygonCollidesWithSphere(BgPolygon* polygon, BgVertex* verticies, Vec3f* pos, f32 readius); // func_800C0AF0
void BgCheck_ScenePolygonListsInsertSorted(CollisionContext* bgCtxt, u16* head, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C0BC0
void BgCheck_ScenePolygonListsInsert(BgMeshSubdivision* subdivision, CollisionContext* bgCtxt, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C0DE0
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
void BgCheck_GetPolyMinSubdivisions(CollisionContext* bgCtxt, Vec3f* min, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision); // func_800C26C0
void BgCheck_GetPolyMaxSubdivisions(CollisionContext* bgCtxt, Vec3f* max, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision); // func_800C2864
void BgCheck_GetPolyMinMaxSubdivisions(CollisionContext* bgCtxt, BgVertex* vertices, BgPolygon* polygons, s32* minX, s32* minY, s32* minZ, s32* maxX, s32* maxY, s32* maxZ, s16 index); // func_800C2A30
UNK_TYPE4 func_800C2BE0(Vec3f* param_1, Vec3f* param_2, BgPolygon* polygons, BgVertex* vertices, s16 index); // func_800C2BE0
u32 BgCheck_SplitScenePolygonsIntoSubdivisions(CollisionContext* bgCtxt, GlobalContext* ctxt, BgMeshSubdivision* subdivisions); // func_800C3334
s32 BgCheck_GetIsDefaultSpecialScene(GlobalContext* ctxt); // func_800C3734
s32 BgCheck_GetSpecialSceneMaxMemory(s32 sceneId, u32* maxMemory); // func_800C3778
void BgCheck_CalcSubdivisionSize(f32 min, s32 subdivisions, f32* max, f32* subdivisionSize, f32* inverseSubdivisionSize); // func_800C37BC
s32 BgCheck_GetSpecialSceneMaxObjects(GlobalContext* ctxt, u32* maxNodes, u32* maxPolygons, u32* maxVertices); // func_800C3844
void BgCheck_Init(CollisionContext* bgCtxt, GlobalContext* ctxt, BgMeshHeader* mesh); // func_800C389C
void func_800C3C00(CollisionContext* bgCtxt, unsigned int param_2); // func_800C3C00
void func_800C3C14(CollisionContext* bgCtxt, unsigned int param_2); // func_800C3C14
BgMeshHeader* BgCheck_GetActorMeshHeader(CollisionContext* bgCtxt, s32 index); // func_800C3C2C
void func_800C3C94(void); // func_800C3C94
f32 func_800C3D50(s32 arg0, CollisionContext* bgCtxt, s32 arg2, f32* arg3, void* arg4, Vec3f* pos, Actor* actor, s32 arg7, f32 arg8, s32 arg9); // func_800C3D50
void func_800C3F40(void); // func_800C3F40
void func_800C3FA0(void); // func_800C3FA0
void func_800C4000(void); // func_800C4000
void func_800C4058(void); // func_800C4058
void func_800C40B4(void); // func_800C40B4
f32 func_800C411C(CollisionContext* bgCtxt, f32* arg1, void* arg2, Actor* actor, Vec3f* pos); // func_800C411C
void func_800C4188(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C4188
void func_800C41E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C41E4
void func_800C4240(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800C4240
void func_800C42A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C42A8
void func_800C4314(void); // func_800C4314
void func_800C43CC(void); // func_800C43CC
void func_800C4488(void); // func_800C4488
void func_800C44F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800C44F0
void func_800C455C(void); // func_800C455C
s32 func_800C45C4(CollisionContext* bgCtxt, unsigned int param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, float param_6, int* param_7, int* param_8, DynaPolyActor* param_9, float param_10, u8 param_11); // func_800C45C4
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
s32 func_800C55C4(CollisionContext*, Vec3f*, Vec3f*, Vec3f*, BgPolygon**, u32, u32, u32, u32, u32*); // func_800C55C4
void func_800C5650(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_800C5650
void func_800C56E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); // func_800C56E0
s32 func_800C576C(CollisionContext*, Vec3f*, Vec3f*, Vec3f*, BgPolygon**, u32, u32, u32, u32, u32*); // func_800C576C
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
void BgCheck_SetActorMeshParams(ActorMeshParams* params, Vec3f* scale, Vec3s* rotation, Vec3f* position); // func_800C5C0C
s32 BgCheck_AreActorMeshParamsEqual(ActorMeshParams* param_1, ActorMeshParams* param_2); // func_800C5C5C
void BgCheck_ActorMeshPolyListsHeadsInit(ActorMeshPolyLists* lists); // func_800C5D30
void BgCheck_ActorMeshPolyListsInit(ActorMeshPolyLists* lists); // func_800C5D70
void BgCheck_ActorMeshVerticesIndexInit(s16* index); // func_800C5D90
void BgCheck_ActorMeshWaterboxesIndexInit(s16* index); // func_800C5D9C
void BgCheck_ActorMeshInit(GlobalContext* ctxt, ActorMesh* mesh); // func_800C5DA8
void BgCheck_ActorMeshInitFromActor(ActorMesh* actorMesh, DynaPolyActor* actor, BgMeshHeader* header); // func_800C5E10
s32 BgCheck_HasActorMeshChanged(ActorMesh* mesh); // func_800C5EC8
void BgCheck_PolygonsInit(BgPolygon** polygons); // func_800C5EF0
void BgCheck_PolygonsAlloc(GlobalContext* ctxt, BgPolygon* polygons, u32 numPolygons); // func_800C5EFC
void BgCheck_VerticesInit(BgVertex** vertices); // func_800C5F38
void BgCheck_VerticesListAlloc(GlobalContext* ctxt, BgVertex** vertices, u32 numVertices); // func_800C5F44
void BgCheck_WaterboxListInit(BgWaterboxList* waterboxList); // func_800C5F8C
void BgCheck_WaterboxListAlloc(GlobalContext* ctxt, BgWaterboxList* waterboxList, u32 numWaterboxes); // func_800C5F9C
void BgCheck_ActorMeshUpdateParams(GlobalContext* ctxt, ActorMesh* mesh); // func_800C5FD8
s32 BgCheck_IsActorMeshIndexValid(s32 index); // func_800C6024
void BgCheck_DynaInit(GlobalContext* ctxt, DynaCollisionContext* param_2); // func_800C6044
void BgCheck_DynaAlloc(GlobalContext* ctxt, DynaCollisionContext* dyna); // func_800C6098
s32 BgCheck_AddActorMesh(GlobalContext* ctxt, DynaCollisionContext* dyna, DynaPolyActor* actor, BgMeshHeader* header); // func_800C6188
DynaPolyActor* BgCheck_GetActorOfMesh(CollisionContext* bgCtxt, s32 index); // func_800C6248
void func_800C62BC(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C62BC
void func_800C6314(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C6314
void func_800C636C(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C636C
void func_800C63C4(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C63C4
void func_800C641C(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C641C
void func_800C6474(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C6474
void BgCheck_RemoveActorMesh(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index); // func_800C64CC
void func_800C6554(void); // func_800C6554
void BgCheck_CalcWaterboxDimensions(Vec3f* minPos, Vec3f* maxXPos, Vec3f* maxZPos, Vec3s* minPosOut, s16* xLength, s16* zLength); // func_800C656C
void BgCheck_AddActorMeshToLists(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index, s32* currVertices, s32* currPolygons, s32* currWaterboxes); // func_800C6838
void BgCheck_ResetFlagsIfLoadedActor(GlobalContext* ctxt, DynaCollisionContext* dyna, Actor* actor); // func_800C734C
void BgCheck_Update(GlobalContext* ctxt, DynaCollisionContext* dyna); // func_800C73E4
void func_800C756C(s32 param_1, s32* param_2, s32* param_3, s32* param_4); // func_800C756C
void BgCheck_UpdateAllActorMeshes(GlobalContext* ctxt, DynaCollisionContext* dyna); // func_800C765C
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
void BgCheck_RelocateAllMeshHeaders(CollisionContext* bgCtxt, GlobalContext* ctxt); // func_800C9598
void func_800C9640(void); // func_800C9640
u32 BgCheck_GetPolygonAttributes(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index, s32 attributeIndex); // func_800C9694
u32 func_800C9704(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9704
void func_800C9728(void); // func_800C9728
UNK_TYPE4 func_800C9770(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9770
void func_800C97F8(void); // func_800C97F8
UNK_TYPE4 func_800C9844(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9844
void func_800C98CC(void); // func_800C98CC
UNK_TYPE4 func_800C9924(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9924
u32 func_800C99AC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99AC
u32 func_800C99D4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99D4
u32 func_800C99FC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C99FC
u32 func_800C9A24(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A24
u32 func_800C9A4C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A4C
u32 func_800C9A7C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9A7C
u32 func_800C9AB0(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9AB0
u32 func_800C9AE4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9AE4
u32 func_800C9B18(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B18
u32 func_800C9B40(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B40
u32 func_800C9B68(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B68
u32 func_800C9B90(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9B90
u32 func_800C9BB8(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9BB8
u32 func_800C9BDC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9BDC
u32 func_800C9C24(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index, UNK_TYPE4 param_4); // func_800C9C24
u32 func_800C9C74(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9C74
u32 func_800C9C9C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9C9C
u32 func_800C9CC4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9CC4
u32 func_800C9CEC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9CEC
void func_800C9D14(void); // func_800C9D14
void func_800C9D50(void); // func_800C9D50
unsigned int func_800C9D8C(CollisionContext* param_1, BgPolygon* param_2, s32 param_3); // func_800C9D8C
void func_800C9DDC(void); // func_800C9DDC
u32 func_800C9E18(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E18
u32 func_800C9E40(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E40
u32 func_800C9E88(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index); // func_800C9E88
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
void BgCheck2_UpdateActorPosition(CollisionContext* bgCtxt, s32 index, Actor* actor); // func_800CAAD0
void BgCheck2_UpdateActorYRotation(CollisionContext* bgCtxt, s32 index, Actor* actor); // func_800CAC0C
void BgCheck2_AttachToMesh(CollisionContext* bgCtxt, Actor* actor, s32 index); // func_800CACA0
u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* bgCtxt, s32 index, Actor* actor); // func_800CAD2C
void BcCheck3_BgActorInit(DynaPolyActor* actor, UNK_TYPE4 param_2); // func_800CAE10
void BgCheck3_LoadMesh(GlobalContext* ctxt, DynaPolyActor* actor, BgMeshHeader* meshHeader); // func_800CAE34
void BgCheck3_ResetFlags(DynaPolyActor* actor); // func_800CAE7C
void func_800CAE88(DynaPolyActor* actor); // func_800CAE88
void func_800CAE9C(DynaPolyActor* actor); // func_800CAE9C
void func_800CAEB0(CollisionContext* bgCtxt, s32 index); // func_800CAEB0
void func_800CAEE0(DynaPolyActor* actor); // func_800CAEE0
void func_800CAEF4(CollisionContext* bgCtxt, s32 index); // func_800CAEF4
void func_800CAF24(DynaPolyActor* actor); // func_800CAF24
void func_800CAF38(DynaPolyActor* actor); // func_800CAF38
s32 func_800CAF4C(DynaPolyActor* actor); // func_800CAF4C
s32 func_800CAF70(DynaPolyActor* actor); // func_800CAF70
s32 func_800CAF94(DynaPolyActor* actor); // func_800CAF94
s32 func_800CAFB8(DynaPolyActor* actor); // func_800CAFB8
s32 func_800CAFDC(DynaPolyActor* actor); // func_800CAFDC
void func_800CB000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); // func_800CB000
f32 Camera_fabsf(f32 f); // func_800CB210
f32 Camera_LengthVec3f(Vec3f* v); // func_800CB240
void func_800CB270(void); // func_800CB270
f32 Camera_Lerpf(f32 b, f32 a, f32 t, f32 minDist); // func_800CB330
s16 Camera_Lerps(s16 b, s16 a, f32 t, s16 minDist); // func_800CB398
void func_800CB42C(void); // func_800CB42C
void Camera_LerpVec3f(Vec3f* b, Vec3f* a, f32 tXZ, f32 tY, f32 minDist); // func_800CB4C0
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
Camera* Camera_Alloc(View* view, CollisionContext* bg, GlobalContext* ctxt); // func_800DDD58
void Camera_Free(Camera* camera); // func_800DDDA8
void Camera_Init(Camera* camera, View* view, CollisionContext* bg, GlobalContext* ctxt); // func_800DDDD0
void func_800DDFE0(void); // func_800DDFE0
void func_800DE0EC(Camera* camera, Actor* actor); // func_800DE0EC
s32 func_800DE308(Camera* camera, UNK_TYPE2 uParm2); // func_800DE308
void func_800DE324(void); // func_800DE324
void func_800DE62C(void); // func_800DE62C
void func_800DE840(void); // func_800DE840
void func_800DE890(void); // func_800DE890
UNK_TYPE4 func_800DE954(Camera* camera); // func_800DE954
Vec3s* Camera_Update(Vec3s* param_1, Camera* camera); // func_800DE9B0
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
s16 func_800DFCB4(Camera* camera); // func_800DFCB4
s16 func_800DFCDC(Camera* camera); // func_800DFCDC
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
void Collision_Init(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E2450
void Collision_Fini(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E2470
void Collision_Reset(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E2480
void Collision_EnableEditMode(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E2528
void Collision_EnableAppendMode(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E2540
s32 Collision_AddAT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape); // func_800E2558
s32 Collision_AddIndexAT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape, s32 index); // func_800E2634
s32 Collision_AddAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape); // func_800E2740
s32 collision_AddIndexAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape, s32 index); // func_800E281C
s32 Collision_AddOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape); // func_800E2928
s32 Collision_AddIndexOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape, s32 index); // func_800E2A04
s32 Collision_AddGroup4(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape); // func_800E2B10
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
void func_800E3168(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, ColCommon* bumper, ColBodyInfo* bumperBody, Vec3f* param_6); // func_800E3168
void func_800E3304(ColCommon* toucher, ColCommon* bumper); // func_800E3304
s32 Collision_HandleCollisionATWithAC(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, Vec3f* toucherLoc, ColCommon* bumper, ColBodyInfo* bumperBody, Vec3f* bumperLoc, Vec3f* param_8); // func_800E3324
void Collision_TriCalcAvgPoint(ColTri* tri, Vec3f* avg); // func_800E35C8
void collision_quad_cal_avg_point(ColQuadParams* quad, Vec3f* avg); // func_800E362C
void Collision_SphereGroupWithSphereGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColSphereGroup* bumpee); // func_800E36AC
void Collision_SphereGroupWithCylinderAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColCylinder* bumpee); // func_800E38F8
void Collision_SphereGroupWithTriGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColTriGroup* bumpee); // func_800E3B18
void Collision_SphereGroupWithQuadAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColQuad* bumpee); // func_800E3CC0
void Collision_SphereGroupWithSphereAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColSphere* bumpee); // func_800E3E6C
void Collision_CylinderWithSphereGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColSphereGroup* bumpee); // func_800E4058
void Collision_CylinderWithCylinderAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColCylinder* bumpee); // func_800E4298
void Collision_CylinderWithTriGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColTriGroup* bumpee); // func_800E44C0
void Collision_CylinderWithQuadAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColQuad* bumpee); // func_800E4628
void Collision_CylinderWithSphereAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColSphere* bumpee); // func_800E47B8
void Collision_TriGroupWithSphereGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColTriGroup* toucher, ColSphereGroup* bumpee); // func_800E494C
void Collision_TriGroupWithCylinderAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColTriGroup* toucher, ColCylinder* bumpee); // func_800E4B08
void Collision_TriGroupWithTriGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColTriGroup* toucher, ColTriGroup* bumpee); // func_800E4C70
void Collision_TriGroupWithQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColTriGroup* toucher, ColQuad* bumpee); // func_800E4E24
void Collision_TriGroupWithSphereAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColTriGroup* toucher, ColSphere* bumpee); // func_800E4FE4
void Collision_QuadWithSphereGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColQuad* toucher, ColSphereGroup* bumpee); // func_800E5154
void Collision_QuadWithCylinderAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColQuad* toucher, ColCylinder* bumpee); // func_800E531C
void Collision_QuadWithTriGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColQuad* toucher, ColTriGroup* bumpee); // func_800E54DC
void Collision_QuadWithQuadAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColQuad* toucher, ColQuad* bumpee); // func_800E56B8
void Collision_QuadWithSphereAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColQuad* toucher, ColSphere* bumpee); // func_800E5874
void Collision_SphereWithSphereGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColSphereGroup* bumpee); // func_800E59A4
void Collision_SphereWithCylinderAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColCylinder* bumpee); // func_800E5B94
void Collision_SphereWithTriGroupAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColTriGroup* bumpee); // func_800E5D10
void Collision_SphereWithQuadAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColQuad* bumpee); // func_800E5E54
void Collision_SphereWithSphereAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColSphere* bumpee); // func_800E5F6C
void func_800E60C0(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* spheres); // func_800E60C0
void func_800E61A0(void); // func_800E61A0
void func_800E6238(void); // func_800E6238
void func_800E6320(void); // func_800E6320
void func_800E63B8(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* sphere); // func_800E63B8
void func_800E6450(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E6450
void Collision_CollideWithAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* colObj); // func_800E6524
void Collision_DoATWithAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E6654
void func_800E6724(void); // func_800E6724
void Collision_HandleCollisionOTWithOT(GlobalContext* ctxt, ColCommon* toucher, ColBodyInfo* toucherBody, Vec3f* toucherLoc, ColCommon* bumper, ColBodyInfo* bumperBody, Vec3f* bumperLoc, f32 param_8); // func_800E6760
void Collision_SphereGroupWithSphereGroupOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColSphereGroup* bumpee); // func_800E6A9C
void Collision_SphereGroupWithCylinderOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColCylinder* bumpee); // func_800E6C84
void Collision_SphereGroupWithSphereOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphereGroup* toucher, ColSphere* bumpee); // func_800E6DF4
void Collision_CylinderWithSphereGroupOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColSphereGroup* bumpee); // func_800E6F64
void Collision_CylinderWithCylinderOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColCylinder* bumpee); // func_800E6F90
void Collision_CylinderWithSphereOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCylinder* toucher, ColSphere* bumpee); // func_800E7060
void Collision_SphereWithSphereGroupOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColSphereGroup* bumpee); // func_800E7130
void Collision_SphereWithCylinderOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColCylinder* bumpee); // func_800E715C
void Collision_SphereWithSphereOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColSphere* toucher, ColSphere* bumpee); // func_800E7188
UNK_TYPE4 func_800E7264(ColCommon* iParm1); // func_800E7264
UNK_TYPE4 func_800E7288(ColCommon* piParm1, ColCommon* piParm2); // func_800E7288
void Collision_DoOTWithOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E7308
void func_800E7494(CollisionCheckInfo* param_1); // func_800E7494
void func_800E74DC(CollisionCheckInfo* param_1); // func_800E74DC
void func_800E7508(s32 param_1, UNK_PTR param_2); // func_800E7508
void func_800E7530(CollisionCheckInfo* param_1, DamageTable* param_2, UNK_PTR param_3); // func_800E7530
void func_800E755C(CollisionCheckInfo* puParm1, DamageTable* uParm2, UNK_PTR puParm3); // func_800E755C
void func_800E7590(void); // func_800E7590
void func_800E75C8(void); // func_800E75C8
void func_800E77EC(void); // func_800E77EC
void func_800E7894(void); // func_800E7894
void func_800E78B4(void); // func_800E78B4
void func_800E7948(void); // func_800E7948
void func_800E7968(void); // func_800E7968
void func_800E7988(GlobalContext* ctxt, CollisionCheckContext* colCtxt); // func_800E7988
void func_800E7A48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7A48
void func_800E7B54(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7B54
void func_800E7BCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_800E7BCC
void func_800E7C64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_800E7C64
void func_800E7DA8(void); // func_800E7DA8
s32 func_800E7DCC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Vec3f* param_3, Vec3f* param_4, Actor** param_5, s32 param_6); // func_800E7DCC
void Collision_CylinderMoveToActor(Actor* actor, ColCylinder* cylinder); // func_800E7DF8
void Collision_CylinderSetLoc(ColCylinder* cylinder, Vec3s* loc); // func_800E7E3C
void Collision_QuadSetCoords(ColQuad* iParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, Vec3f* param_5); // func_800E7E5C
void Collision_TriGroupSetCoordsAtIndex(ColTriGroup* tris, s32 index, Vec3f* pzParm3, Vec3f* pzParm4, Vec3f* param_5); // func_800E7ECC
void Collision_InitTriParamsAtIndex(GlobalContext* ctxt, ColTriGroup* tris, s32 index, ColTriParamsInit* init); // func_800E7F8C
void func_800E7FDC(void); // func_800E7FDC
void func_800E8160(void); // func_800E8160
void func_800E823C(void); // func_800E823C
void func_800E8318(void); // func_800E8318
void func_800E8478(void); // func_800E8478
void func_800E85D4(UNK_TYPE4 param_1, Vec3f* param_2); // func_800E85D4
void func_800E8668(GlobalContext* globalCtx, Vec3f* arg2); // func_800E8668
void func_800E8690(void); // func_800E8690
void func_800E86C0(void); // func_800E86C0
void func_800E86E0(UNK_TYPE4 param_1, Vec3f* param_2, UNK_TYPE4 param_3); // func_800E86E0
void func_800E8784(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); // func_800E8784
void func_800E8EA0(GlobalContext* ctxt, Actor* actor, u16 param_3); // func_800E8EA0
s32 nop_800E8ED0(UNK_TYPE4 param_1); // func_800E8ED0
void nop_800E8EE0(UNK_TYPE4 param_1); // func_800E8EE0
s32 nop_800E8EEC(UNK_TYPE4 param_1); // func_800E8EEC
void nop_800E8EFC(UNK_TYPE4 param_1); // func_800E8EFC
s32 func_800E8F08(Vec3s* param_1, Vec3s* param_2); // func_800E8F08
s32 func_800E8FA4(Actor* actor, Vec3f* param_2, Vec3s* param_3, Vec3s* param_4); // func_800E8FA4
s32 func_800E9138(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, f32 param_5); // func_800E9138
s32 func_800E9250(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, Vec3f param_5); // func_800E9250
u8 func_800E9360(void); // func_800E9360
void static_context_init(void); // func_800E93E0
void func_800E9470(void); // func_800E9470
void DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX, f32 scaleY, f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type, GraphicsContext* gfxCtx); // func_800E9488
void DebugDisplay_DrawObjects(GlobalContext* globalCtx); // func_800E9564
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
void Cutscene_Init(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA060
void func_800EA0D4(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA0D4
void func_800EA0EC(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA0EC
void Cutscene_StepCutscene1(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA110
void Cutscene_StepCutscene2(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA15C
void Cutscene_Nop800EA210(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA210
s32 func_800EA220(GlobalContext* ctxt, CutsceneContext* csCtx, f32 target); // func_800EA220
void func_800EA258(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA258
void func_800EA2B8(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EA2B8
void func_800EA324(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EA324
void func_800EABAC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdEnvLighting* cmd); // func_800EABAC
void func_800EAC08(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicChange* cmd); // func_800EAC08
void func_800EAC44(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicChange* cmd); // func_800EAC44
void func_800EAC94(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicFade* cmd); // func_800EAC94
void func_800EAD14(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EAD14
void func_800EAD48(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EAD48
void func_800EAD7C(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EAD7C
void func_800EADB0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EADB0
void func_800EAECC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EAECC
void func_800EAF20(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdUnk190* cmd); // func_800EAF20
void func_800EAFE0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdUnk9B* cmd); // func_800EAFE0
void func_800EB1DC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdDayTime* cmd); // func_800EB1DC
void func_800EB364(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EB364
void func_800EB4B4(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EB4B4
void func_800EB6F8(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EB6F8
void func_800EBB68(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EBB68
void func_800EBCD0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EBCD0
void func_800EBD60(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd); // func_800EBD60
s32 func_800EC678(GlobalContext* ctxt, CsCmdUnk5A* cmd); // func_800EC678
u32 func_800EC6D4(void); // func_800EC6D4
void func_800EC924(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdTextbox* cmd); // func_800EC924
void func_800ECD7C(CutsceneContext* csCtx, u8** cutscenePtr, s16 index); // func_800ECD7C
void Cutscene_ProcessCommands(GlobalContext* ctxt, CutsceneContext* csCtx, u8* cutscenePtr, unsigned short* commandReadHead); // func_800ECE40
void func_800ED980(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800ED980
void func_800ED9C4(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800ED9C4
void func_800EDA04(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EDA04
void func_800EDA84(GlobalContext* ctxt, CutsceneContext* csCtx); // func_800EDA84
void func_800EDBE0(GlobalContext* ctxt); // func_800EDBE0
void nop_800EDDB0(GlobalContext* ctxt); // func_800EDDB0
void func_800EDDBC(void); // func_800EDDBC
void func_800EDDCC(GlobalContext* ctxt, unsigned int uParm2); // func_800EDDCC
void func_800EDE34(Actor* actor, GlobalContext* ctxt, int param_3); // func_800EDE34
void func_800EDF24(void); // func_800EDF24
void func_800EDF78(Actor* actor, GlobalContext* ctxt, int iParm3); // func_800EDF78
void func_800EE0CC(Actor* actor, GlobalContext* ctxt, int iParm3); // func_800EE0CC
void func_800EE1D8(void); // func_800EE1D8
u32 func_800EE200(GlobalContext* ctxt, u32 uParm2); // func_800EE200
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
void EffFootmark_Add(GlobalContext* ctxt, z_Matrix* displayMatrix, Actor* actor, u8 id, Vec3f* location, u16 size, u8 red, u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay); // func_800EFF04
void EffFootmark_Update(GlobalContext* ctxt); // func_800F00BC
void EffFootmark_Draw(GlobalContext* ctxt); // func_800F01C8
void func_800F0390(GlobalContext* ctxt); // func_800F0390
void func_800F03C0(GlobalContext* ctxt); // func_800F03C0
void func_800F048C(GlobalContext* ctxt, Vec3f* param_2, u8 param_3, u16 param_4, u8 param_5); // func_800F048C
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
void func_800F1304(GlobalContext* ctxt, short param_2); // func_800F1304
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
void FireObj_SetPosition(FireObj* fire, Vec3f* pos); // func_800F2EAC
void FireObj_StepSize(FireObj* fire); // func_800F2ECC
void FireObj_UpdateStateTransitions(GlobalContext* ctxt, FireObj* fire); // func_800F2FFC
void FireObj_Draw(GlobalContext* ctxt, FireObj* fire); // func_800F31EC
void FireObj_InitLight(GlobalContext* ctxt, FireObjLight* light, u8* param_3, Vec3f* pos); // func_800F33F4
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
void func_800FB320(GlobalContext* ctxt, u8 param_2); // func_800FB320
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
void func_800FD538(RGB* param_1, RGB* param_2, f32 param_3, Vec3s* param_4); // func_800FD538
void func_800FD59C(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD59C
void func_800FD5E0(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD5E0
void func_800FD654(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3); // func_800FD654
void func_800FD698(void); // func_800FD698
u32 get_days_elapsed(void); // func_800FD720
void reset_days_elapsed(void); // func_800FD730
u32 get_current_day(void); // func_800FD740
void func_800FD750(void); // func_800FD750
void func_800FD768(void); // func_800FD768
void func_800FD78C(GlobalContext* ctxt); // func_800FD78C
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
s32* Lib_MemSet(s32* buffer, s32 value, u32 size); // func_800FECC0
f32 Math_Coss(s16 angle); // func_800FED44
f32 Math_Sins(s16 angle); // func_800FED84
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
s16 Math_Rand_S16Offset(s16 base, s16 range); // func_800FF450
s16 Math_Rand_S16OffsetStride(s16 base, s16 stride, s16 range); // func_800FF4A4
void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src); // func_800FF50C
void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src); // func_800FF52C
void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src); // func_800FF54C
void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src); // func_800FF584
void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest); // func_800FF5BC
void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest); // func_800FF5F4
void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r); // func_800FF62C
void Math_Vec3f_Scale(Vec3f* vec, f32 scale); // func_800FF688
void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest); // func_800FF6C4
void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest); // func_800FF6F8
void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest); // func_800FF750
void Math_Vec3f_ModifyRand(Vec3f* orig, f32 scale, Vec3f* dest); // func_800FF79C
void Math_Vec3f_DistXYZAndStoreNormalizedDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest); // func_800FF810
f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b); // func_800FF884
f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* difference); // func_800FF8D4
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b); // func_800FF92C
f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* xDiff, f32* zDiff); // func_800FF960
f32 Math_Vec3f_PushAwayXZ(Vec3f* start, Vec3f* pusher, f32 distanceToApproach); // func_800FF9A4
f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b); // func_800FFA4C
s16 Math_Vec3f_Yaw(Vec3f* from, Vec3f* to); // func_800FFA60
s16 Math_Vec3f_Pitch(Vec3f* from, Vec3f* to); // func_800FFA94
void Actor_ProcessInitChain(Actor* actor, InitChainEntry* init); // func_800FFADC
void IChain_Apply_u8(u8* actor, InitChainEntry* init); // func_800FFB54
void IChain_Apply_s8(u8* actor, InitChainEntry* init); // func_800FFB70
void IChain_Apply_u16(u8* actor, InitChainEntry* init); // func_800FFB8C
void IChain_Apply_s16(u8* actor, InitChainEntry* init); // func_800FFBA8
void IChain_Apply_u32(u8* actor, InitChainEntry* init); // func_800FFBC4
void IChain_Apply_s32(u8* actor, InitChainEntry* init); // func_800FFBE0
void IChain_Apply_f32(u8* actor, InitChainEntry* init); // func_800FFBFC
void IChain_Apply_f32div1000(u8* actor, InitChainEntry* init); // func_800FFC20
void IChain_Apply_Vec3f(u8* actor, InitChainEntry* init); // func_800FFC50
void IChain_Apply_Vec3fdiv1000(u8* actor, InitChainEntry* init); // func_800FFC7C
void IChain_Apply_Vec3s(u8* actor, InitChainEntry* init); // func_800FFCB4
f32 Math_SmoothScaleMaxMinF(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4); // func_800FFCD8
void Math_SmoothScaleMaxF(f32* start, f32 target, f32 scale, f32 maxStep); // func_800FFDF8
void Math_SmoothDownscaleMaxF(f32* start, f32 scale, f32 maxStep); // func_800FFE68
s32 Math_SmoothScaleMaxMinS(s16* start, s16 target, s16 scale, s16 maxStep, s16 minStep); // func_800FFEBC
void Math_SmoothScaleMaxS(s16* start, s16 target, s16 scale, s16 maxStep); // func_800FFFD8
void Color_RGBA8_Copy(ColorRGBA8* dst, ColorRGBA8* src); // func_8010007C
void func_801000A4(u16 param_1); // func_801000A4
void func_801000CC(u16 param_1); // func_801000CC
void func_801000F4(UNK_TYPE4 param_1, u16 param_2); // func_801000F4
void Lib_TranslateAndRotateYVec3f(Vec3f* translation, s16 rotation, Vec3f* src, Vec3f* dst); // func_8010011C
void Lib_LerpRGB(RGB* a, RGB* b, f32 t, RGB* dst); // func_801001B8
f32 Lib_PushAwayVec3f(Vec3f* start, Vec3f* pusher, f32 distanceToApproach); // func_80100448
void Lib_Nop801004FC(void); // func_801004FC
void* Lib_PtrSegToVirt(void* ptr); // func_80100504
void* Lib_PtrSegToVirtNull(void* ptr); // func_8010053C
void* Lib_PtrSegToK0(void* ptr); // func_80100584
void* Lib_PtrSegToK0Null(void* ptr); // func_801005A0
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
void Lights_MapPositionalWithReference(LightMapper* mapper, LightInfoPositionalParams* params, Vec3f* pos); // func_80101D3C
void Lights_MapPositional(LightMapper* mapper, LightInfoPositionalParams* params, GlobalContext* ctxt); // func_801020A0
void Lights_MapDirectional(LightMapper* mapper, LightInfoDirectionalParams* params, GlobalContext* ctxt); // func_80102284
void Lights_MapLights(LightMapper* mapper, z_Light* lights, Vec3f* refPos, GlobalContext* ctxt); // func_801022F0
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
void func_80104CF4(GlobalContext* ctxt); // func_80104CF4
void func_80104F34(void); // func_80104F34
void func_80105294(void); // func_80105294
void func_80105318(void); // func_80105318
void func_80105328(void); // func_80105328
void func_8010534C(void); // func_8010534C
void func_8010549C(GlobalContext* ctxt, void* segmentAddress); // func_8010549C
void func_8010565C(GlobalContext* ctxt, u8 num, void* segmentAddress); // func_8010565C
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
f32 CamMath_Distance(Vec3f* a, Vec3f* b); // func_8010C230
f32 CamMath_DistanceAndDiff(Vec3f* a, Vec3f* b, Vec3f* diff); // func_8010C274
f32 CamMath_DistanceXZ(Vec3f* a, Vec3f* b); // func_8010C2D0
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
void Interface_ChangeAlpha(u16 param_1); // func_8010EF68
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
void func_80122868(GlobalContext* globalCtx, ActorPlayer* player); // func_80122868
void func_801229A0(GlobalContext* globalCtx, ActorPlayer* player); // func_801229A0
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
s32 func_801240C8(ActorPlayer* player); // func_801240C8
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
void func_80126440(GlobalContext* globalCtx, ColCommon* param_2, s32* param_3, Vec3f* param_4, Vec3f* param_5); // func_80126440
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
void PreNMI_Stop(PreNMIContext* prenmiCtx); // func_80129EF0
void PreNMI_Update(PreNMIContext* prenmiCtx); // func_80129F04
void PreNMI_Draw(PreNMIContext* prenmiCtx); // func_80129F4C
void PreNMI_Main(PreNMIContext* prenmiCtx); // func_80129FF8
void PreNMI_Destroy(PreNMIContext* prenmiCtx); // func_8012A02C
void PreNMI_Init(PreNMIContext* prenmiCtx); // func_8012A038
f32 Quake_Random(void); // func_8012A080
void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 y, f32 x); // func_8012A0AC
s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake); // func_8012A2B8
s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake); // func_8012A340
s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake); // func_8012A3B4
s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake); // func_8012A438
s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake); // func_8012A4D0
s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake); // func_8012A540
s16 Quake_GetFreeIndex(void); // func_8012A5D8
QuakeRequest* Quake_AddImpl(Camera* cam, u32 callbackIdx); // func_8012A638
void Quake_Remove(QuakeRequest* req); // func_8012A6F0
QuakeRequest* Quake_GetRequest(s16 idx); // func_8012A718
QuakeRequest* Quake_SetValue(s16 idx, s16 valueType, s16 value); // func_8012A774
u32 Quake_SetSpeed(s16 idx, s16 value); // func_8012A8A8
u32 Quake_SetCountdown(s16 idx, s16 value); // func_8012A8F0
s16 Quake_GetCountdown(s16 idx); // func_8012A940
u32 Quake_SetQuakeValues(s16 idx, s16 y, s16 x, s16 zoom, s16 rotZ); // func_8012A978
u32 Quake_SetUnkValues(s16 idx, s16 arg1); // func_8012A9E0
void Quake_Init(void); // func_8012AA48
s16 Quake_Add(Camera* cam, u32 callbackIdx); // func_8012AA9C
u32 Quake_RemoveFromIdx(s16 idx); // func_8012AAC0
s16 Quake_Calc(Camera* camera, UnkQuakeCalcStruct* camData); // func_8012AB08
void Quake2_Init(GlobalContext* ctxt); // func_8012AE68
void Quake2_SetCountdown(s16 countdown); // func_8012AEAC
int Quake2_GetCountdown(void); // func_8012AED4
s16 Quake2_GetType(void); // func_8012AEE4
void Quake2_SetType(s16 type); // func_8012AEF4
void Quake2_ClearType(s16 type); // func_8012AF18
u32 Quake2_GetFloorQuake(ActorPlayer* player); // func_8012AF38
void Quake2_Update(void); // func_8012AF9C
void Quake_NumActiveQuakes(void); // func_8012BBE8
Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f); // func_8012BC50
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f); // func_8012BD8C
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f); // func_8012BF08
Gfx* Gfx_CallSetupDLImpl(Gfx* gfx, u32 i); // func_8012BF3C
Gfx* Gfx_CallSetupDL(Gfx* gfx, u32 i); // func_8012BF78
void Gfx_CallSetupDLAtPtr(Gfx** gfxp, u32 i); // func_8012BF98
Gfx* func_8012BFC4(Gfx* gfx); // func_8012BFC4
Gfx* func_8012BFEC(Gfx* gfx); // func_8012BFEC
Gfx* func_8012C014(Gfx* gfx); // func_8012C014
void func_8012C058(GraphicsContext* gCtxt); // func_8012C058
void func_8012C080(GraphicsContext* gCtxt); // func_8012C080
void func_8012C0A8(GraphicsContext* gCtxt); // func_8012C0A8
void func_8012C0D0(GraphicsContext* gCtxt); // func_8012C0D0
void func_8012C0F8(GraphicsContext* gCtxt); // func_8012C0F8
void func_8012C120(GraphicsContext* gCtxt); // func_8012C120
void func_8012C148(GraphicsContext* gCtxt); // func_8012C148
void func_8012C170(GraphicsContext* gCtxt); // func_8012C170
Gfx* func_8012C198(Gfx* gfx); // func_8012C198
void func_8012C1C0(GraphicsContext* gCtxt); // func_8012C1C0
Gfx* func_8012C1EC(Gfx* gfx); // func_8012C1EC
void func_8012C214(GraphicsContext* gCtxt); // func_8012C214
void func_8012C240(GraphicsContext* gCtxt); // func_8012C240
void func_8012C268(GlobalContext* ctxt); // func_8012C268
void func_8012C28C(GraphicsContext* gCtxt); // func_8012C28C
Gfx* func_8012C2B4(Gfx* gfx); // func_8012C2B4
void func_8012C2DC(GraphicsContext* gCtxt); // func_8012C2DC
Gfx* func_8012C304(Gfx* gfx); // func_8012C304
void func_8012C32C(GraphicsContext* gCtxt); // func_8012C32C
void func_8012C354(GraphicsContext* gCtxt); // func_8012C354
void func_8012C37C(GraphicsContext* gCtxt); // func_8012C37C
Gfx* func_8012C3A4(Gfx* gfx); // func_8012C3A4
Gfx* func_8012C3CC(Gfx* gfx); // func_8012C3CC
void func_8012C3F4(GraphicsContext* gCtxt); // func_8012C3F4
void func_8012C420(GraphicsContext* gCtxt); // func_8012C420
void func_8012C448(GraphicsContext* gCtxt); // func_8012C448
void func_8012C470(GraphicsContext* gCtxt); // func_8012C470
Gfx* func_8012C498(Gfx* gfx); // func_8012C498
void func_8012C4C0(GraphicsContext* gCtxt); // func_8012C4C0
void func_8012C4E8(GraphicsContext* gCtxt); // func_8012C4E8
void func_8012C510(GraphicsContext* gCtxt); // func_8012C510
void func_8012C538(GraphicsContext* gCtxt); // func_8012C538
void func_8012C560(GraphicsContext* gCtxt); // func_8012C560
void func_8012C588(GraphicsContext* gCtxt); // func_8012C588
void func_8012C5B0(GraphicsContext* gCtxt); // func_8012C5B0
void func_8012C5D8(GraphicsContext* gCtxt); // func_8012C5D8
Gfx* func_8012C600(Gfx* gfx); // func_8012C600
void func_8012C628(GraphicsContext* gCtxt); // func_8012C628
void func_8012C654(GraphicsContext* gCtxt); // func_8012C654
void func_8012C680(Gfx** gfxp); // func_8012C680
void func_8012C6AC(GraphicsContext* gCtxt); // func_8012C6AC
void func_8012C6D4(GraphicsContext* gCtxt); // func_8012C6D4
void func_8012C6FC(GraphicsContext* gCtxt); // func_8012C6FC
Gfx* func_8012C724(Gfx* gfx); // func_8012C724
Gfx* func_8012C74C(Gfx* gfx); // func_8012C74C
Gfx* func_8012C774(Gfx* gfx); // func_8012C774
Gfx* func_8012C7B8(Gfx* gfx); // func_8012C7B8
Gfx* func_8012C7FC(Gfx* gfx); // func_8012C7FC
Gfx* func_8012C840(Gfx* gfx); // func_8012C840
Gfx* func_8012C868(Gfx* gfx); // func_8012C868
void func_8012C8AC(GraphicsContext* gCtxt); // func_8012C8AC
void func_8012C8D4(GraphicsContext* gCtxt); // func_8012C8D4
void func_8012C8FC(GraphicsContext* gCtxt); // func_8012C8FC
void func_8012C924(GraphicsContext* gCtxt); // func_8012C924
void func_8012C94C(GraphicsContext* gCtxt); // func_8012C94C
void func_8012C974(GraphicsContext* gCtxt); // func_8012C974
void func_8012C9BC(GraphicsContext* gCtxt); // func_8012C9BC
void func_8012C9E4(GraphicsContext* gCtxt); // func_8012C9E4
void func_8012CA0C(Gfx** gfxp); // func_8012CA0C
void func_8012CA38(GraphicsContext* gCtxt); // func_8012CA38
Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height); // func_8012CA60
void func_8012CB04(Gfx** gfxp, u32 x, u32 y); // func_8012CB04
Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y); // func_8012CB28
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height); // func_8012CB4C
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2); // func_8012CBD0
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a); // func_8012CCF0
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a); // func_8012CE50
Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a); // func_8012CEA8
void func_8012CF0C(GraphicsContext* gCtxt, s32 iParm2, s32 iParm3, u8 r, u8 g, u8 b); // func_8012CF0C
void func_8012D374(GraphicsContext* gCtxt, u8 r, u8 g, u8 b); // func_8012D374
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
s32 Scene_LoadObject(SceneContext* sceneCtxt, s16 id); // func_8012F2E0
void Scene_Init(GlobalContext* ctxt, SceneContext* sceneCtxt); // func_8012F3D0
void Scene_ReloadUnloadedObjects(SceneContext* sceneCtxt); // func_8012F4FC
s32 Scene_FindSceneObjectIndex(SceneContext* sceneCtxt, s16 id); // func_8012F608
s32 Scene_IsObjectLoaded(SceneContext* sceneCtxt, s32 index); // func_8012F668
void Scene_DmaAllObjects(SceneContext* sceneCtxt); // func_8012F698
void* func_8012F73C(SceneContext* sceneCtxt, s32 iParm2, s16 id); // func_8012F73C
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneCmd* entry); // func_8012F79C
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneCmd* entry); // func_8012F90C
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneCmd* entry); // func_8012F954
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneCmd* entry); // func_8012F984
void Scene_HeaderCommand04(GlobalContext* ctxt, SceneCmd* entry); // func_8012FA24
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneCmd* entry); // func_8012FA68
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneCmd* entry); // func_8012FA98
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneCmd* entry); // func_8012FB60
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneCmd* entry); // func_8012FBE8
void Scene_HeaderCommand0B(GlobalContext* ctxt, SceneCmd* entry); // func_8012FC18
void Scene_HeaderCommand0C(GlobalContext* ctxt, SceneCmd* entry); // func_8012FDA4
void Scene_HeaderCommand0D(GlobalContext* ctxt, SceneCmd* entry); // func_8012FE2C
void Scene_HeaderCommand0E(GlobalContext* ctxt, SceneCmd* entry); // func_8012FE5C
void func_8012FEBC(GlobalContext* ctxt, u8* nbTransitionActors); // func_8012FEBC
void Scene_HeaderCommand0F(GlobalContext* ctxt, SceneCmd* entry); // func_8012FECC
s32 func_8012FF10(GlobalContext* ctxt, s32 fileIndex); // func_8012FF10
void Scene_HeaderCommand11(GlobalContext* ctxt, SceneCmd* entry); // func_8012FF8C
void Scene_HeaderCommand12(GlobalContext* ctxt, SceneCmd* entry); // func_8012FFF0
void Scene_HeaderCommand10(GlobalContext* ctxt, SceneCmd* entry); // func_80130018
void Scene_HeaderCommand05(GlobalContext* ctxt, SceneCmd* entry); // func_8013033C
void Scene_HeaderCommand13(GlobalContext* ctxt, SceneCmd* entry); // func_801303A0
void Scene_HeaderCommand09(GlobalContext* ctxt, SceneCmd* entry); // func_801303D0
void Scene_HeaderCommand15(GlobalContext* ctxt, SceneCmd* entry); // func_801303E0
void Scene_HeaderCommand16(GlobalContext* ctxt, SceneCmd* entry); // func_8013043C
void Scene_HeaderCommand18(GlobalContext* ctxt, SceneCmd* entry); // func_80130454
void Scene_HeaderCommand17(GlobalContext* ctxt, SceneCmd* entry); // func_801304CC
void Scene_HeaderCommand1B(GlobalContext* ctxt, SceneCmd* entry); // func_80130500
void Scene_HeaderCommand1C(GlobalContext* ctxt, SceneCmd* entry); // func_80130540
void Scene_HeaderCommand1D(GlobalContext* ctxt, SceneCmd* entry); // func_80130578
void Scene_HeaderCommand1E(GlobalContext* ctxt, SceneCmd* entry); // func_80130588
void Scene_HeaderCommand19(GlobalContext* ctxt, SceneCmd* entry); // func_801305B0
void Scene_HeaderCommand1A(GlobalContext* ctxt, SceneCmd* entry); // func_80130674
void func_801306A4(GlobalContext* ctxt); // func_801306A4
s32 Scene_ProcessHeader(GlobalContext* ctxt, SceneCmd* header); // func_801306E8
u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset); // func_80130768
void func_80130784(u32 spawnIndex); // func_80130784
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
s16 func_801323A0(u32 entrance); // func_801323A0
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
void SkelAnime_LodDrawLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDraw(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                       OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                             OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex,
                             RSPMatrix** mtx);
void SkelAnime_LodDrawSV(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_Draw(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                    OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_DrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                          OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor,
                          RSPMatrix** limbMatricies);
void SkelAnime_DrawSV(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void func_80134148(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, 
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor,
                      RSPMatrix** mtx);
void func_801343C0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor);
void SkelAnime_AnimateFrame(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst);
s16 SkelAnime_GetTotalFrames(GenericAnimationHeader *animationSeg);
s16 SkelAnime_GetFrameCount(GenericAnimationHeader* animationSeg);
Gfx* SkelAnime_Draw2Limb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                         OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_Draw2(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                     OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_DrawLimbSV2(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, RSPMatrix** mtx,
                           Gfx* gfx);
Gfx* SkelAnime_DrawSV2(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                       OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
s32 func_80134FFC(s32 arg0, s32 arg1, Vec3s* dst);
s16 func_801353D4(GenericAnimationHeader* animationSeg);
s16 SkelAnime_GetTotalFrames2(GenericAnimationHeader* animationSeg);
s16 SkelAnime_GetFrameCount2(GenericAnimationHeader* animationSeg);
void SkelAnime_InterpolateVec3s(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf);
void SkelAnime_AnimationCtxReset(AnimationContext* animationCtx);
void func_801358D4(GlobalContext *globalCtx);
void func_801358F4(GlobalContext *globalCtx);
AnimationEntry* SkelAnime_NextEntry(AnimationContext* animationCtx, AnimationType type);
void SkelAnime_LoadLinkAnimetion(GlobalContext* globalCtx, LinkAnimetionEntry* linkAnimetionSeg, s32 frame,
                                 s32 limbCount, void* ram);
void SkelAnime_LoadAnimationType1(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src);
void SkelAnime_LoadAnimationType2(GlobalContext* globalCtx, s32 limbCount, Vec3s* arg2, Vec3s* arg3, f32 arg4);
void SkelAnime_LoadAnimationType3(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType4(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType5(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3);
void SkelAnime_LinkAnimetionLoaded(GlobalContext* globalCtx, AnimationEntryType0* entry);
void SkelAnime_AnimationType1Loaded(GlobalContext* globalCtx, AnimationEntryType1* entry);
void SkelAnime_AnimationType2Loaded(GlobalContext* globalCtx, AnimationEntryType2* entry);
void SkelAnime_AnimationType3Loaded(GlobalContext* globalCtx, AnimationEntryType3* entry);
void SkelAnime_AnimationType4Loaded(GlobalContext* globalCtx, AnimationEntryType4* entry);
void SkelAnime_AnimationType5Loaded(GlobalContext* globalCtx, AnimationEntryType5* entry);
void func_80135EE8(GlobalContext* globalCtx, AnimationContext* animationCtx);
void SkelAnime_InitLinkAnimetion(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimetionEntry* linkAnimetionEntrySeg, s32 flags, Vec3s* limbDrawTbl,
                                 Vec3s* transitionDrawTbl, s32 limbBufCount);
void func_801360A8(SkelAnime* skelAnime);
s32 func_801360E0(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136104(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_801361BC(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void SkelAnime_SetTransition(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 transitionRate);
void SkelAnime_ChangeLinkAnim(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                              f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate);
void SkelAnime_ChangeLinkAnimDefaultStop(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg);
void SkelAnime_ChangeLinkAnimPlaybackStop(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed);
void SkelAnime_ChangeLinkAnimDefaultRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg);
void SkelAnime_ChangeLinkAnimPlaybackRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed);
void func_8013670C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013673C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013676C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 frame);
void func_801367B0(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 frame);
void func_801367F4(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 frame);
void func_8013682C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl);
void func_801368CC(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl);
void SkelAnime_SetModeStop(SkelAnime* skelAnime);
s32 func_80136990(SkelAnime* skelAnime, f32 arg1, f32 updateRate);
s32 func_80136A48(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Init(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSV(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                      AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSkin(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg);
void func_80136C84(SkelAnime* skelAnime);
s32 SkelAnime_FrameUpdateMatrix(SkelAnime* skelAnime);
s32 func_80136CF4(SkelAnime* skelAnime);
s32 func_80136D98(SkelAnime* skelAnime);
void func_80136F04(SkelAnime* skelAnime);
s32 func_8013702C(SkelAnime* skelAnime);
s32 func_801370B0(SkelAnime* skelAnime);
s32 func_8013713C(SkelAnime* skelAnime);
void SkelAnime_ChangeAnimImpl(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                              f32 frameCount, u8 animationType, f32 transitionRate, s8 unk2);
void SkelAnime_ChangeAnim(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                          f32 frameCount, u8 mode, f32 transitionRate);
void SkelAnime_ChangeAnimDefaultStop(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_ChangeAnimDefaultRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_AnimSetStop(SkelAnime* skelAnime);
void SkelAnime_AnimReverse(SkelAnime* skelAnime);
void func_80137674(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* index);
void func_801376DC(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* arg3);
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
s32 func_801378B8(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx);
void SkelAnime_CopyVec3s(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
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
void Matrix_MultiplyByVectorXYZW(z_Matrix* matrix, Vec3f* vector, Vec3f* resultXYZ, f32* resultW); // func_80138BA0
void Matrix_MultiplyByVectorXYZ(z_Matrix* matrix, Vec3f* vector, Vec3f* result); // func_80138C88
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
void Matrix_ToVec3s(Vec3f* vec3f, Vec3s* vec3s); // func_80139978
void Matrix_ToVec3f(Vec3s* vec3s, Vec3f* vec3f); // func_801399BC
void Matrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst); // func_80139A00
RSPMatrix* Matrix_AppendToPloyOpaDisp(GraphicsContext* gCtxt, z_Matrix* matrix); // func_80139C18
void Matrix_MakeRotationAroundUnitVector(z_Matrix* matrix, s16 rotation, f32 x, f32 y, f32 z); // func_80139C60
void Matrix_MakeXRotation(z_Matrix* matrix, s16 rotation); // func_80139DD0
void Matrix_XRotation(z_Matrix* matrix, s16 rotation); // func_80139E98
void Matrix_MakeYRotation(z_Matrix* matrix, s16 rotation); // func_80139FA0
void Matrix_YRotation(z_Matrix* matrix, s16 rotation); // func_8013A068
void Matrix_MakeZRotation(z_Matrix* matrix, s16 rotation); // func_8013A174
s32 func_8013A240(GlobalContext* ctxt); // func_8013A240
void func_8013A41C(s32 flag); // func_8013A41C
void func_8013A46C(s32 flag); // func_8013A46C
u32 func_8013A4C4(s32 flag); // func_8013A4C4
s16 func_8013A504(s16 val); // func_8013A504
s32 func_8013A530(GlobalContext* ctxt, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin, f32 distanceMax, s16 angleError); // func_8013A530
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
Actor* func_ActorCategoryIterateById(GlobalContext* globalCtx, struct Actor* actorListStart, s32 actorCategory, s32 actorId); // func_8013D960
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
void func_8013ECE0(f32 param_1, u8 param_2, u8 param_3, u8 param_4); // func_8013ECE0
void func_8013ED9C(void); // func_8013ED9C
void func_8013EDD0(void); // func_8013EDD0
void func_8013EE04(void); // func_8013EE04
void func_8013EE24(void); // func_8013EE24
void func_8013EE38(void); // func_8013EE38
void func_8013EE48(void); // func_8013EE48
void View_ViewportToVp(Vp* dest, Viewport* src); // func_8013EE60
void View_Init(View* view, GraphicsContext* gCtxt); // func_8013EEF4
void View_SetViewOrientation(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir); // func_8013EF9C
void func_8013F050(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir); // func_8013F050
void View_SetScale(View* view, f32 scale); // func_8013F0A0
void View_GetScale(View* view, f32* scale); // func_8013F0C0
void func_8013F0D0(View* view, f32 fovy, f32 zNear, f32 zFar); // func_8013F0D0
void func_8013F100(View* view, f32* fovy, f32* zNear, f32* zFar); // func_8013F100
void func_8013F120(View* view, f32 fovy, f32 zNear, f32 zFar); // func_8013F120
void func_8013F15C(View* view, f32* fovy, f32* zNear, f32* zFar); // func_8013F15C
void View_SetViewport(View* view, Viewport* viewport); // func_8013F17C
void View_GetViewport(View* view, Viewport* viewport); // func_8013F1B0
void View_WriteScissor(Gfx** gfx, s32 ulx, s32 uly, s32 lrx, s32 lry); // func_8013F1D8
void View_SyncAndWriteScissor(View* view, Gfx** gfx); // func_8013F28C
void View_SetScissorForLetterbox(View* view); // func_8013F2F8
s32 View_SetQuakeRotation(View* view, f32 x, f32 y, f32 z); // func_8013F3F8
s32 View_SetQuakeScale(View* view, f32 x, f32 y, f32 z); // func_8013F420
s32 View_SetQuakeSpeed(View* view, f32 speed); // func_8013F448
s32 View_InitCameraQuake(View* view); // func_8013F45C
s32 View_ClearQuake(View* view); // func_8013F4C0
s32 View_SetQuake(View* view, Vec3f rot, Vec3f scale, f32 speed); // func_8013F4F4
s32 View_StepQuake(View* view, RSPMatrix* matrix); // func_8013F54C
void View_RenderView(View* view, s32 uParm2); // func_8013F6FC
s32 View_RenderToPerspectiveMatrix(View* view); // func_8013F748
s32 View_RenderToOrthographicMatrix(View* view); // func_8013FA1C
s32 func_8013FBC8(View* view); // func_8013FBC8
s32 func_8013FD74(View* view); // func_8013FD74
s32 func_80140024(View* view); // func_80140024
s32 func_801400CC(View* view, Gfx** gfxp); // func_801400CC
void func_80140260(OSViMode* vimode); // func_80140260
void func_8014026C(OSViMode* param_1, UNK_TYPE1 param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, UNK_TYPE4 param_9, int param_10, short param_11, unsigned int param_12, UNK_TYPE4 param_13); // func_8014026C
void func_80140730(void); // func_80140730
void func_80140810(void); // func_80140810
void func_80140898(void* arg0); // func_80140898
void func_80140900(void* arg0); // func_80140900
void func_8014090C(void); // func_8014090C
void func_80140970(void); // func_80140970
void func_80140CE0(void* arg0); // func_80140CE0
void func_80140D04(void* arg0); // func_80140D04
void func_80140D10(void* arg0, Gfx** gfx, u32 arg2); // func_80140D10
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
void func_801418B0(void* arg0); // func_801418B0
void func_80141900(void* arg0); // func_80141900
void func_80141924(void); // func_80141924
void func_80141C34(void); // func_80141C34
void VisMono_Draw(void* arg0, Gfx** gfx, u32 arg2); // VisMono_Draw
void func_8014204C(void); // func_8014204C
void func_801420C0(void* arg0); // func_801420C0
void func_801420F4(void* arg0); // func_801420F4
void func_80142100(void* arg0, Gfx** gfx, u32 arg2); // func_80142100
void func_80142440(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9); // func_80142440
void func_80143148(void); // func_80143148
void func_801431E8(void); // func_801431E8
void func_80143324(void); // func_80143324
void func_801434E4(GameState* ctxt, int iParm2, short sParm3); // func_801434E4
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
void func_801457CC(GameState* ctxt, SramContext* param_2); // func_801457CC
void func_80146580(int param_1, SramContext* param_2, int param_3); // func_80146580
void func_80146628(void); // func_80146628
void func_80146AA0(void); // func_80146AA0
void func_80146DF8(void); // func_80146DF8
void func_80146E40(void); // func_80146E40
void Sram_Alloc(GameState* ctxt, SramContext* iParm2); // func_80146E70
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
void func_80149F74(GlobalContext* globalCtx, unsigned int** ppuParm2); // func_80149F74
void func_8014AAD0(void); // func_8014AAD0
void func_8014ADBC(GlobalContext* globalCtx, UNK_PTR puParm2); // func_8014ADBC
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
void func_801518B0(GlobalContext* ctxt, u32 uParm2, Actor* uParm3); // func_801518B0
void func_80151938(GlobalContext* ctxt, u16 param_2); // func_80151938
void func_80151A68(GlobalContext* ctxt, u16 param_2); // func_80151A68
void func_80151BB4(s32 iParm1, u32 uParm2); // func_80151BB4
void func_80151C9C(void); // func_80151C9C
void func_80151DA4(void); // func_80151DA4
void func_80152434(void); // func_80152434
void func_80152464(void); // func_80152464
UNK_TYPE4 func_80152498(MessageContext* msgCtx); // func_80152498
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
void func_8015E7EC(GlobalContext* globalCtx, UNK_PTR puParm2); // func_8015E7EC
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
void* Play_LoadScene(GlobalContext* ctxt, ObjectFileTableEntry* entry); // func_80169220
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
void Audio_Start(AudioThreadStruct* audio, s32* audioThreadStackEnd, OSPri pri, OSId id, SchedThreadStruct* sched, IrqMgr* irq); // func_80173074
void TitleSetup_GameStateResetContext(void); // func_80173130
void TitleSetup_InitImpl(GameState* gameState); // func_801732DC
void TitleSetup_Destroy(GameState* gameState); // func_8017332C
void TitleSetup_Init(GameState* gameState); // func_80173338
void Game_UpdateFramerateVariables(s32 divisor); // func_80173360
void Game_SetFramerateDivisor(GameState* gameState, s32 divisor); // func_801733A8
void GameState_SetFBFilter(Gfx** gfx, u32 arg1); // func_801733DC
void Game_Nop80173534(GameState* ctxt); // func_80173534
void GameState_Draw(GameState* ctxt, GraphicsContext* gCtxt); // func_80173540
void Game_ResetSegments(GraphicsContext* gCtxt); // func_80173644
void func_801736DC(GraphicsContext* gCtxt); // func_801736DC
void Game_UpdateInput(GameState* ctxt); // func_80173754
void Game_Update(GameState* ctxt); // func_8017377C
void Game_IncrementFrameCount(GameState* ctxt); // func_801737E4
void Game_InitHeap(GameState* ctxt, u32 size); // func_80173810
void Game_ResizeHeap(GameState* ctxt, u32 size); // func_80173880
void Game_StateInit(GameState* ctxt, GameStateFunc gameStateInit, GraphicsContext* gCtxt); // func_80173950
void Game_StateFini(GameState* ctxt); // func_80173A50
GameStateFunc Game_GetNextStateInit(GameState* ctxt); // func_80173B00
u32 Game_GetNextStateSize(GameState* ctxt); // func_80173B0C
u32 Game_GetShouldContinue(GameState* ctxt); // func_80173B18
s32 Game_GetHeapFreeSize(GameState* ctxt); // func_80173B24
s32 func_80173B48(GameState* ctxt); // func_80173B48
GameAlloc* func_80173BF0(GameAlloc* heap); // func_80173BF0
void* Gamealloc_Alloc(GameAlloc* heap, u32 size); // func_80173C10
void Gamealloc_Free(GameAlloc* heap, void* ptr); // func_80173C7C
void Gamealloc_FreeAll(GameAlloc* heap); // func_80173CC8
void Gamealloc_Init(GameAlloc* iParm1); // func_80173D18
void Graph_FaultClient(void); // func_80173D30
void Graph_DlAlloc(DispBuf* dl, void* memoryBlock, u32 size); // func_80173DAC
void Graph_InitTHGA(GraphicsContext* gCtxt); // func_80173DCC
GameStateOverlay* Graph_GetNextGameState(GameState* ctxt); // func_80173F98
void* Graph_FaultAddrConvFunc(void* addr); // func_80174060
void Graph_Init(GraphicsContext* gCtxt); // func_801740D0
void Graph_Destroy(void); // func_80174174
void Graph_Render(GraphicsContext* gCtxt, GameState* ctxt); // func_801741A8
void Graph_FrameSetup(GameState* ctxt); // func_801744AC
void Graph_RenderFrame(GraphicsContext* gCtxt, GameState* ctxt); // func_801744F8
void Graph_DoFrame(GraphicsContext* gCtxt, GameState* ctxt); // func_80174868
void Graph_ThreadEntry(void* arg); // func_801748A0
Gfx* Graph_GfxPlusOne(Gfx* gfx); // func_80174A40
Gfx* Graph_BranchDlist(Gfx* gfx, Gfx* dst); // func_80174A4C
void* Graph_DlistAlloc(Gfx** gfx, u32 size); // func_80174A64
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
void Padmgr_Start(OSMesgQueue* siEventCallbackQueue, IrqMgr* irqmgr, OSId threadId, OSPri threadPri, void* stack); // func_80176194
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
void Sched_Start(SchedThreadStruct* sched, void* stack, OSPri pri, UNK_TYPE4 param_4, UNK_TYPE4 param_5, IrqMgr* irqmgrStruct); // func_801772A0
void func_80177390(void); // func_80177390
void func_801773A0(void* arg0); // func_801773A0
void func_801773C4(void* arg0); // func_801773C4
void SpeedMeter_DrawTimeEntries(void* displayList, GraphicsContext* gCtx); // func_801773D0
void func_80177A84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_80177A84
void func_80177AC8(void); // func_80177AC8
void SpeedMeter_DrawAllocEntries(void* displayList, GraphicsContext *gCtx, GameState *ctx); // func_80177E58
void func_801780F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_801780F0
void func_801781EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_801781EC
void func_8017842C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017842C
void func_80178750(void); // func_80178750
void func_80178818(void); // func_80178818
void func_80178978(void); // func_80178978
void func_801789D4(void); // func_801789D4
u32* get_framebuffer(s32 index); // func_801789EC
u16* get_zbuffer(void); // func_80178A14
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
f32 Math3D_Normalize(Vec3f* vec); // func_801795F0
UNK_TYPE4 func_80179678(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_80179678
UNK_TYPE4 func_80179798(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, Vec3f* param_6); // func_80179798
void func_80179A44(void); // func_80179A44
void func_80179B34(float fParm1, float fParm2, float fParm5, float fParm6, float param_5, float param_6, float param_7, float* param_8, float* param_9); // func_80179B34
UNK_TYPE4 func_80179B94(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, f32 param_8, Vec3f* param_9); // func_80179B94
void func_80179D74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); // func_80179D74
void Math3D_ScaleAndAdd(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dst); // func_80179DF0
void Math3D_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dst); // func_80179E3C
s32 Math3D_Parallel(Vec3f* a, Vec3f* b); // func_80179E88
s32 Math3D_AngleBetweenVectors(Vec3f* a, Vec3f* b, f32* angle); // func_80179EAC
void func_80179F64(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3); // func_80179F64
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z); // func_8017A038
void func_8017A09C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A09C
void func_8017A1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A1D0
void func_8017A304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); // func_8017A304
UNK_TYPE4 func_8017A438(Vec3f* pfParm1, Vec3f* pfParm2, Vec3f* pfParm3, Vec3f* pfParm4, f32 param_5); // func_8017A438
f32 Math3D_XZLengthSquared(f32 x, f32 z); // func_8017A5F8
f32 Math3D_XZLength(f32 x, f32 z); // func_8017A610
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2); // func_8017A634
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2); // func_8017A678
f32 Math3D_LengthSquared(Vec3f* vec); // func_8017A6A8
f32 Math3D_Length(Vec3f* vec); // func_8017A6D4
f32 Math3D_DistanceSquared(Vec3f* a, Vec3f* b); // func_8017A6F8
f32 Math3D_Distance(Vec3f* a, Vec3f* b); // func_8017A720
f32 Math3D_DistanceS(Vec3s* s, Vec3f* f); // func_8017A740
f32 func_8017A7B8(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A7B8
f32 func_8017A7F8(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A7F8
f32 func_8017A838(f32* param_1, f32* param_2, f32 param_3, f32 param_4); // func_8017A838
void Math3D_CrossProduct(Vec3f* a, Vec3f* b, Vec3f* res); // func_8017A878
void Math3D_NormalVector(Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* res); // func_8017A8EC
unsigned int func_8017A954(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3); // func_8017A954
unsigned int func_8017AA0C(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3); // func_8017AA0C
unsigned int func_8017ABBC(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3); // func_8017ABBC
void func_8017AD38(void); // func_8017AD38
void func_8017B68C(void); // func_8017B68C
void func_8017B7F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017B7F8
void Math3D_UnitNormalVector(Vec3f* a, Vec3f* b, Vec3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7); // func_8017B884
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position); // func_8017B998
void func_8017B9D8(void); // func_8017B9D8
f32 Math3D_NormalizedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position); // func_8017BA14
f32 Math3D_NormalizedSignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position); // func_8017BA4C
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
void Math3D_TriSetCoords(ColTriParams* tri, Vec3f* pointA, Vec3f* pointB, Vec3f* pointC); // func_8017D568
u32 Math3D_IsPointInSphere(ColSphereCollisionInfo* sphere, Vec3f* point); // func_8017D618
void func_8017D668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); // func_8017D668
void func_8017D7C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); // func_8017D7C0
void func_8017D814(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017D814
void func_8017D91C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017D91C
void func_8017DA24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017DA24
s32 Math3D_ColSphereLineSeg(ColSphereCollisionInfo* sphere, LineSegment* line); // func_8017DB2C
void func_8017DD34(ColSphereCollisionInfo* sphere, ColTriParams* tri, Vec3f* pfParm3); // func_8017DD34
s32 Math3D_ColSphereTri(ColSphereCollisionInfo* sphere, ColTriParams* tri, Vec3f* uParm3); // func_8017DE74
void func_8017E294(void); // func_8017E294
void func_8017E350(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); // func_8017E350
s32 Math3D_ColCylinderTri(ColCylinderParams* cylinder, ColTriParams* tri, Vec3f* pzParm3); // func_8017ED20
void func_8017F1A0(void); // func_8017F1A0
s32 Math3D_ColSphereSphere(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2); // func_8017F1C0
s32 Math3D_ColSphereSphereIntersect(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2, f32* intersectAmount); // func_8017F1E0
s32 Math3D_ColSphereSphereIntersectAndDistance(ColSphereCollisionInfo* sphere1, ColSphereCollisionInfo* sphere2, f32* intersectAmount, f32* dist); // func_8017F200
s32 Math3D_ColSphereCylinderDistance(ColSphereCollisionInfo* sphere, ColCylinderParams* cylinder, f32* dist); // func_8017F2CC
s32 Math3D_ColSphereCylinderDistanceAndAmount(ColSphereCollisionInfo* sphere, ColCylinderParams* cylinder, f32* dist, f32* intersectAmount); // func_8017F2EC
s32 Math3D_ColCylinderCylinderAmount(ColCylinderParams* cylinder1, ColCylinderParams* cylinder2, f32* intersectAmount); // func_8017F45C
s32 Math3D_ColCylinderCylinderAmountAndDistance(ColCylinderParams* cylinder1, ColCylinderParams* cylinder2, f32* intersectAmount, f32* dist); // func_8017F47C
s32 Math3d_ColTriTri(ColTriParams* tri1, ColTriParams* tri2, Vec3f* uParm3); // func_8017F64C
void func_8017F9C0(void); // func_8017F9C0
void func_8017FA34(void); // func_8017FA34
void func_8017FAA8(void); // func_8017FAA8
void func_8017FB1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); // func_8017FB1C
void func_8017FD44(void); // func_8017FD44
s16 atans_first_8th(f32 opposite, f32 adjacent); // func_8017FEB0
s16 atans(f32 opposite, f32 adjacent); // func_8017FEE4
f32 atan(f32 opposite, f32 adjacent); // func_801800CC
s16 atans_flip(f32 adjacent, f32 opposite); // func_80180100
s16 atan_flip(f32 adjacent, f32 opposite); // func_8018012C
void SysMatrix_StateAlloc(GameState* ctxt); // func_80180160
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
void SysMatrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rotation); // func_801812FC
void SysMatrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* rotation); // func_80181650
RSPMatrix* SysMatrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst); // func_801817FC
RSPMatrix* SysMatrix_GetStateAsRSPMatrix(RSPMatrix* matrix); // func_80181A18
RSPMatrix* SysMatrix_AppendStateToPolyOpaDisp(GraphicsContext* gCtxt); // func_80181A40
void SysMatrix_AppendToPolyOpaDisp(z_Matrix* ctxt, GraphicsContext* gCtxt); // func_80181A6C
void SysMatrix_MultiplyVector3fByState(Vec3f* src, Vec3f* dst); // func_80181A98
void SysMatrix_GetStateTranslation(Vec3f* dst); // func_80181B50
void SysMatrix_GetStateTranslationAndScaledX(f32 scale, Vec3f* dst); // func_80181B78
void SysMatrix_GetStateTranslationAndScaledY(f32 scale, Vec3f* dst); // func_80181BC4
void SysMatrix_GetStateTranslationAndScaledZ(f32 scale, Vec3f* dst); // func_80181C10
void SysMatrix_MultiplyVector3fXZByCurrentState(Vec3f* src, Vec3f* dst); // func_80181C5C
void SysMatrix_Copy(z_Matrix* dst, z_Matrix* src); // func_80181CDC
void SysMatrix_FromRSPMatrix(RSPMatrix* src, z_Matrix* dst); // func_80181D64
void SysMatrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dst, z_Matrix* matrix); // func_80181FB8
void SysMatrix_TransposeXYZ(z_Matrix* matrix); // func_80182068
void SysMatrix_NormalizeXYZ(z_Matrix* matrix); // func_801820A0
void func_8018219C(z_Matrix* pfParm1, Vec3s* psParm2, s32 iParm3); // func_8018219C
void func_801822C4(void); // func_801822C4
void SysMatrix_InsertRotationAroundUnitVector_f(f32 rotation, Vec3f* vector, s32 appendToState); // func_801823EC
void SysMatrix_InsertRotationAroundUnitVector_s(s16 rotation, Vec3f* vector, s32 appendToState); // func_8018284C
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
u32 func_80185908(void); // func_80185908
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
void func_8019AE40(int param_1, int param_2, unsigned int param_3, int param_4); // func_8019AE40
void func_8019AEC0(UNK_PTR param_1, UNK_PTR param_2); // func_8019AEC0
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
void func_8019FAD8(Vec3f* param_1, u16 param_2, f32 param_3); // func_8019FAD8
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
void func_801A246C(u8 param_1, u8 param_2); // func_801A246C
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
void func_801A3FFC(UNK_TYPE1 param_1); // func_801A3FFC
void audio_setBGM(u32 bgmID); // func_801A400C
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
void func_801A72CC(Vec3f* uParm1); // func_801A72CC
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
s32 func_801A8A50(s32 param1); // func_801A8A50
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

#endif
