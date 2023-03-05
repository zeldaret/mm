#ifndef FAULT_H
#define FAULT_H

#include "ultra64.h"
#include "libc/stdarg.h"
#include "libc/stdint.h"
#include "io/controller.h"

// These are the same as the 3-bit ansi color codes
#define FAULT_COLOR_BLACK      0
#define FAULT_COLOR_RED        1
#define FAULT_COLOR_GREEN      2
#define FAULT_COLOR_YELLOW     3
#define FAULT_COLOR_BLUE       4
#define FAULT_COLOR_MAGENTA    5
#define FAULT_COLOR_CYAN       6
#define FAULT_COLOR_WHITE      7
// Additional color codes
#define FAULT_COLOR_DARK_GRAY  8
#define FAULT_COLOR_LIGHT_GRAY 9

#define FAULT_COLOR_STRINGIFY(s) #s
#define FAULT_COLOR_EXPAND_AND_STRINGIFY(s) FAULT_COLOR_STRINGIFY(s)

#define FAULT_ESC '\x1A'
#define FAULT_COLOR(n) "\x1A" FAULT_COLOR_EXPAND_AND_STRINGIFY(FAULT_COLOR_ ## n)


#define NORMAL_RDRAM_END 0x80400000
// Address at the end of normal RDRAM after which is room for a screen buffer
#define FAULT_FB_ADDRESS (NORMAL_RDRAM_END - sizeof(u16[SCREEN_HEIGHT][SCREEN_WIDTH]))


typedef struct FaultClient {
    /* 0x0 */ struct FaultClient* next;
    /* 0x4 */ void (*callback)(void*, void*);
    /* 0x8 */ void* arg0;
    /* 0xC */ void* arg1;
} FaultClient; // size = 0x10

typedef struct FaultAddrConvClient {
    /* 0x0 */ struct FaultAddrConvClient* next;
    /* 0x4 */ uintptr_t (*callback)(uintptr_t, void*);
    /* 0x8 */ void* arg;
} FaultAddrConvClient; // size = 0xC


typedef void (*FaultDrawerCallback)(void);

typedef void(*FaultPadCallback)(Input* input);


void Fault_SleepImpl(u32 duration);
void Fault_AddClient(FaultClient* client, void* callback, void* param0, void* param1);
void Fault_RemoveClient(FaultClient* client);
void Fault_AddAddrConvClient(FaultAddrConvClient* client, void* callback, void* param);
void Fault_RemoveAddrConvClient(FaultAddrConvClient* client);
void* Fault_ConvertAddress(void* addr);
void Fault_Sleep(u32 duration);
void Fault_PadCallback(Input* input);
void Fault_UpdatePadImpl(void);
u32 Fault_WaitForInputImpl(void);
void Fault_WaitForInput(void);
void Fault_DrawRec(s32 x, s32 y, s32 w, s32 h, u16 color);
void Fault_FillScreenBlack(void);
void Fault_FillScreenRed(void);
void Fault_DrawCornerRec(u16 color);
void Fault_PrintFReg(s32 idx, f32* value);
void Fault_LogFReg(s32 idx, f32* value);
void Fault_PrintFPCR(u32 value);
void Fault_LogFPCSR(u32 value);
void Fault_PrintThreadContext(OSThread* t);
void osSyncPrintfThreadContext(OSThread* t);
OSThread* Fault_FindFaultedThread(void);
void Fault_Wait5Seconds(void);
void Fault_WaitForButtonCombo(void);
void Fault_DrawMemDumpPage(const char* title, u32* addr, u32 param_3);
void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1);
void Fault_FindNextStackCall(uintptr_t* spPtr, uintptr_t* pcPtr, uintptr_t* raPtr);
void Fault_DrawStackTrace(OSThread* t, u32 flags);
void osSyncPrintfStackTrace(OSThread* t, u32 flags);
void Fault_ResumeThread(OSThread* t);
void Fault_CommitFB(void);
void Fault_ProcessClients(void);
void Fault_SetOptionsFromController3(void);
void Fault_SetOptions(void);
void Fault_ThreadEntry(void* arg);
void Fault_SetFB(void* fb, u16 w, u16 h);
void Fault_Start(void);
void Fault_HangupFaultClient(const char* arg0, char* arg1);
void Fault_AddHungupAndCrashImpl(const char* arg0, char* arg1);
void Fault_AddHungupAndCrash(const char* filename, u32 line);


void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled);
void FaultDrawer_DrawRecImpl(s32 xStart, s32 yStart, s32 xEnd, s32 yEnd, u16 color);
void FaultDrawer_DrawChar(char c);
s32 FaultDrawer_ColorToPrintColor(u16 color);
void FaultDrawer_UpdatePrintColor(void);
void FaultDrawer_SetForeColor(u16 color);
void FaultDrawer_SetBackColor(u16 color);
void FaultDrawer_SetFontColor(u16 color);
void FaultDrawer_SetCharPad(s8 padW, s8 padH);
void FaultDrawer_SetCursor(s32 x, s32 y);
void FaultDrawer_FillScreen(void);
void* FaultDrawer_FormatStringFunc(void* arg, const char* str, size_t count);
void FaultDrawer_VPrintf(const char* fmt, va_list ap);
void FaultDrawer_Printf(const char* fmt, ...);
void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...);
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h);
void FaultDrawer_SetInputCallback(FaultDrawerCallback callback);
void FaultDrawer_Init(void);


typedef struct FaultMgr {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ u8 stack[1536]; // Seems leftover from an earlier version. The thread actually uses a stack of this size at 0x8009BE60
    /* 0x7B0 */ OSMesgQueue queue;
    /* 0x7C8 */ OSMesg msg[1];
    /* 0x7CC */ u8 exitDebugger;
    /* 0x7CD */ u8 msgId; // 1 - CPU Break; 2 - Fault; 3 - Unknown
    /* 0x7CE */ u8 faultHandlerEnabled;
    /* 0x7CF */ u8 autoScroll;
    /* 0x7D0 */ OSThread* faultedThread;
    /* 0x7D4 */ FaultPadCallback padCallback;
    /* 0x7D8 */ FaultClient* clients;
    /* 0x7DC */ FaultAddrConvClient* addrConvClients;
    /* 0x7E0 */ UNK_TYPE1 pad7E0[0x4];
    /* 0x7E4 */ Input padInput[4];
    /* 0x844 */ void* fb;
} FaultMgr; // size = 0x848

extern FaultMgr gFaultMgr;


#endif
