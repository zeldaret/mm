#include "ultra64.h"
#include "global.h"
#include "vt.h"

// data
const char* sCpuExceptions[] = {
    "Interrupt",
    "TLB modification",
    "TLB exception on load",
    "TLB exception on store",
    "Address error on load",
    "Address error on store",
    "Bus error on inst.",
    "Bus error on data",
    "System call exception",
    "Breakpoint exception",
    "Reserved instruction",
    "Coprocessor unusable",
    "Arithmetic overflow",
    "Trap exception",
    "Virtual coherency on inst.",
    "Floating point exception",
    "Watchpoint exception",
    "Virtual coherency on data",
};

const char* sFpuExceptions[] = {
    "Unimplemented operation", "Invalid operation", "Division by zero", "Overflow", "Underflow", "Inexact operation",
};

void Fault_SleepImpl(u32 duration) {
    u64 value = (duration * OS_CPU_COUNTER) / 1000ULL;
    Sleep_Cycles(value);
}

void Fault_AddClient(FaultClient* client, void* callback, void* param0, void* param1) {
    OSIntMask mask;
    u32 alreadyExists = 0;

    mask = osSetIntMask(1);

    {

        FaultClient* iter = sFaultContext->clients;

        while (iter) {
            if (iter == client) {
                alreadyExists = 1;
                goto end;
            }
            iter = iter->next;
        }
    }

    client->callback = callback;
    client->param0 = param0;
    client->param1 = param1;
    client->next = sFaultContext->clients;
    sFaultContext->clients = client;

end:
    osSetIntMask(mask);

    if (alreadyExists) {
        osSyncPrintf(VT_COL(RED, WHITE) "fault_AddClient: %08x は既にリスト中にある\n" VT_RST, client);
    }
}

void Fault_RemoveClient(FaultClient* client) {
    FaultClient* iter;
    FaultClient* lastIter;
    OSIntMask mask;
    u32 listIsEmpty;

    iter = sFaultContext->clients;
    listIsEmpty = 0;
    lastIter = NULL;

    mask = osSetIntMask(1);

    while (iter) {
        if (iter == client) {
            if (lastIter) {
                lastIter->next = client->next;
            } else {
                sFaultContext->clients = client;
                if (sFaultContext->clients) {
                    sFaultContext->clients = client->next;
                } else {
                    listIsEmpty = 1;
                }
            }
            break;
        }

        lastIter = iter;
        iter = iter->next;
    }

    osSetIntMask(mask);

    if (listIsEmpty) {
        osSyncPrintf(VT_COL(RED, WHITE) "fault_RemoveClient: %08x リスト不整合です\n" VT_RST, client);
    }
}

void Fault_AddAddrConvClient(FaultAddrConvClient* client, void* callback, void* param) {
    OSIntMask mask;
    u32 alreadyExists = 0;

    mask = osSetIntMask(1);

    {

        FaultAddrConvClient* iter = sFaultContext->addrConvClients;
        while (iter) {
            if (iter == client) {
                alreadyExists = 1;
                goto end;
            }
            iter = iter->next;
        }
    }
    client->callback = callback;
    client->param = param;
    client->next = sFaultContext->addrConvClients;
    sFaultContext->addrConvClients = client;

end:
    osSetIntMask(mask);

    if (alreadyExists) {
        osSyncPrintf(VT_COL(RED, WHITE) "fault_AddressConverterAddClient: %08x は既にリスト中にある\n" VT_RST, client);
    }
}

void Fault_RemoveAddrConvClient(FaultAddrConvClient* client) {
    FaultAddrConvClient* iter;
    FaultAddrConvClient* lastIter;
    OSIntMask mask;
    u32 listIsEmpty;

    iter = sFaultContext->addrConvClients;
    listIsEmpty = 0;
    lastIter = NULL;

    mask = osSetIntMask(1);

    while (iter) {
        if (iter == client) {
            if (lastIter) {
                lastIter->next = client->next;
            } else {
                sFaultContext->addrConvClients = client;
                if (sFaultContext->addrConvClients) {
                    sFaultContext->addrConvClients = client->next;
                } else {
                    listIsEmpty = 1;
                }
            }
            break;
        }

        lastIter = iter;
        iter = iter->next;
    }

    osSetIntMask(mask);

    if (listIsEmpty) {
        osSyncPrintf(VT_COL(RED, WHITE) "fault_AddressConverterRemoveClient: %08x は既にリスト中にある\n" VT_RST,
                     client);
    }
}

void* Fault_ConvertAddress(void* addr) {
    void* ret;
    FaultAddrConvClient* iter = sFaultContext->addrConvClients;

    while (iter) {
        if (iter->callback) {
            ret = iter->callback(addr, iter->param);
            if (ret != NULL) {
                return ret;
            }
        }
        iter = iter->next;
    }

    return NULL;
}

void Fault_Sleep(u32 duration) {
    Fault_SleepImpl(duration);
}

void Fault_PadCallback(Input* input) {
    Padmgr_GetInput2(input, 0);
}

void Fault_UpdatePadImpl() {
    sFaultContext->padCallback(sFaultContext->padInput);
}

u32 Fault_WaitForInputImpl() {
    Input* curInput = &sFaultContext->padInput[0];
    s32 count = 600;
    u32 kDown;

    while (1) {
        Fault_Sleep(0x10);
        Fault_UpdatePadImpl();

        kDown = curInput->press.button;

        if (kDown == BTN_L) {
            sFaultContext->faultActive = !sFaultContext->faultActive;
        }

        if (sFaultContext->faultActive) {
            if (count-- < 1) {
                return 0;
            }
        } else {
            if (kDown == BTN_A || kDown == BTN_DRIGHT) {
                return 0;
            }

            if (kDown == BTN_DLEFT) {
                return 1;
            }

            if (kDown == BTN_DUP) {
                FaultDrawer_SetOsSyncPrintfEnabled(1);
            }

            if (kDown == BTN_DDOWN) {
                FaultDrawer_SetOsSyncPrintfEnabled(0);
            }
        }
    }
}

void Fault_WaitForInput() {
    Fault_WaitForInputImpl();
}

void Fault_DrawRec(s32 x, s32 y, s32 w, s32 h, u16 color) {
    FaultDrawer_DrawRecImpl(x, y, x + w - 1, y + h - 1, color);
}

void Fault_FillScreenBlack() {
    FaultDrawer_SetForeColor(0xFFFF);
    FaultDrawer_SetBackColor(1);
    FaultDrawer_FillScreen();
    FaultDrawer_SetBackColor(0);
}

void Fault_FillScreenRed() {
    FaultDrawer_SetForeColor(0xFFFF);
    FaultDrawer_SetBackColor(0xF001);
    FaultDrawer_FillScreen();
    FaultDrawer_SetBackColor(0);
}

void Fault_DrawCornerRec(u16 color) {
    Fault_DrawRec(0x16, 0x10, 8, 1, color);
}

void Fault_PrintFReg(s32 idx, f32* value) {
    u32 raw = *(u32*)value;
    s32 v0 = ((raw & 0x7F800000) >> 0x17) - 0x7F;

    if ((v0 >= -0x7E && v0 < 0x80) || raw == 0) {
        FaultDrawer_Printf("F%02d:%14.7e ", idx, *value);
    } else {
        FaultDrawer_Printf("F%02d:  %08x(16) ", idx, raw);
    }
}

void osSyncPrintfFReg(s32 idx, f32* value) {
    u32 raw = *(u32*)value;
    s32 v0 = ((raw & 0x7F800000) >> 0x17) - 0x7F;

    if ((v0 >= -0x7E && v0 < 0x80) || raw == 0) {
        osSyncPrintf("F%02d:%14.7e ", idx, *value);
    } else {
        osSyncPrintf("F%02d:  %08x(16) ", idx, *(u32*)value);
    }
}

void Fault_PrintFPCR(u32 value) {
    s32 i;
    u32 flag = 0x20000;

    FaultDrawer_Printf("FPCSR:%08xH ", value);
    for (i = 0; i < ARRAY_COUNT(sFpuExceptions); i++) {
        if (value & flag) {
            FaultDrawer_Printf("(%s)", sFpuExceptions[i]);
            break;
        }
        flag >>= 1;
    }
    FaultDrawer_Printf("\n");
}

void osSyncPrintfFPCR(u32 value) {
    s32 i;
    u32 flag = 0x20000;

    osSyncPrintf("FPCSR:%08xH  ", value);
    for (i = 0; i < ARRAY_COUNT(sFpuExceptions); i++) {
        if (value & flag) {
            osSyncPrintf("(%s)\n", sFpuExceptions[i]);
            break;
        }
        flag >>= 1;
    }
}

void Fault_PrintThreadContext(OSThread* t) {
    __OSThreadContext* ctx;
    s32 causeStrIdx = (s32)((((u32)t->context.cause >> 2) & 0x1F) << 0x10) >> 0x10;
    if (causeStrIdx == 0x17) {
        causeStrIdx = 0x10;
    }
    if (causeStrIdx == 0x1F) {
        causeStrIdx = 0x11;
    }

    FaultDrawer_FillScreen();
    FaultDrawer_SetCharPad(-2, 4);
    FaultDrawer_SetCursor(0x16, 0x14);

    ctx = &t->context;
    FaultDrawer_Printf("THREAD:%d (%d:%s)\n", t->id, causeStrIdx, sCpuExceptions[causeStrIdx]);
    FaultDrawer_SetCharPad(-1, 0);

    FaultDrawer_Printf("PC:%08xH SR:%08xH VA:%08xH\n", (u32)ctx->pc, (u32)ctx->sr, (u32)ctx->badvaddr);
    FaultDrawer_Printf("AT:%08xH V0:%08xH V1:%08xH\n", (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    FaultDrawer_Printf("A0:%08xH A1:%08xH A2:%08xH\n", (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    FaultDrawer_Printf("A3:%08xH T0:%08xH T1:%08xH\n", (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    FaultDrawer_Printf("T2:%08xH T3:%08xH T4:%08xH\n", (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    FaultDrawer_Printf("T5:%08xH T6:%08xH T7:%08xH\n", (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    FaultDrawer_Printf("S0:%08xH S1:%08xH S2:%08xH\n", (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    FaultDrawer_Printf("S3:%08xH S4:%08xH S5:%08xH\n", (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    FaultDrawer_Printf("S6:%08xH S7:%08xH T8:%08xH\n", (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    FaultDrawer_Printf("T9:%08xH GP:%08xH SP:%08xH\n", (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    FaultDrawer_Printf("S8:%08xH RA:%08xH LO:%08xH\n\n", (u32)ctx->s8, (u32)ctx->ra, (u32)ctx->lo);

    Fault_PrintFPCR(ctx->fpcsr);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0, &ctx->fp0.f.f_even);
    Fault_PrintFReg(2, &ctx->fp2.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(4, &ctx->fp4.f.f_even);
    Fault_PrintFReg(6, &ctx->fp6.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(8, &ctx->fp8.f.f_even);
    Fault_PrintFReg(0xA, &ctx->fp10.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0xC, &ctx->fp12.f.f_even);
    Fault_PrintFReg(0xE, &ctx->fp14.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0x10, &ctx->fp16.f.f_even);
    Fault_PrintFReg(0x12, &ctx->fp18.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0x14, &ctx->fp20.f.f_even);
    Fault_PrintFReg(0x16, &ctx->fp22.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0x18, &ctx->fp24.f.f_even);
    Fault_PrintFReg(0x1A, &ctx->fp26.f.f_even);
    FaultDrawer_Printf("\n");
    Fault_PrintFReg(0x1C, &ctx->fp28.f.f_even);
    Fault_PrintFReg(0x1E, &ctx->fp30.f.f_even);
    FaultDrawer_Printf("\n");
    FaultDrawer_SetCharPad(0, 0);

    if (D_8009BE54 != 0) {
        FaultDrawer_DrawText(0xA0, 0xD8, "%5.2f sec\n", D_8009BE54);
    }
}

void osSyncPrintfThreadContext(OSThread* t) {
    __OSThreadContext* ctx;
    s32 causeStrIdx = (s32)((((u32)t->context.cause >> 2) & 0x1F) << 0x10) >> 0x10;
    if (causeStrIdx == 0x17) {
        causeStrIdx = 0x10;
    }
    if (causeStrIdx == 0x1F) {
        causeStrIdx = 0x11;
    }

    ctx = &t->context;
    osSyncPrintf("\n");
    osSyncPrintf("THREAD ID:%d (%d:%s)\n", t->id, causeStrIdx, sCpuExceptions[causeStrIdx]);

    osSyncPrintf("PC:%08xH   SR:%08xH   VA:%08xH\n", (u32)ctx->pc, (u32)ctx->sr, (u32)ctx->badvaddr);
    osSyncPrintf("AT:%08xH   V0:%08xH   V1:%08xH\n", (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    osSyncPrintf("A0:%08xH   A1:%08xH   A2:%08xH\n", (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    osSyncPrintf("A3:%08xH   T0:%08xH   T1:%08xH\n", (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    osSyncPrintf("T2:%08xH   T3:%08xH   T4:%08xH\n", (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    osSyncPrintf("T5:%08xH   T6:%08xH   T7:%08xH\n", (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    osSyncPrintf("S0:%08xH   S1:%08xH   S2:%08xH\n", (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    osSyncPrintf("S3:%08xH   S4:%08xH   S5:%08xH\n", (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    osSyncPrintf("S6:%08xH   S7:%08xH   T8:%08xH\n", (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    osSyncPrintf("T9:%08xH   GP:%08xH   SP:%08xH\n", (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    osSyncPrintf("S8:%08xH   RA:%08xH   LO:%08xH\n", (u32)ctx->s8, (u32)ctx->ra, (u32)ctx->lo);
    osSyncPrintf("\n");
    osSyncPrintfFPCR(ctx->fpcsr);
    osSyncPrintf("\n");
    osSyncPrintfFReg(0, &ctx->fp0.f.f_even);
    osSyncPrintfFReg(2, &ctx->fp2.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(4, &ctx->fp4.f.f_even);
    osSyncPrintfFReg(6, &ctx->fp6.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(8, &ctx->fp8.f.f_even);
    osSyncPrintfFReg(10, &ctx->fp10.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(12, &ctx->fp12.f.f_even);
    osSyncPrintfFReg(14, &ctx->fp14.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(16, &ctx->fp16.f.f_even);
    osSyncPrintfFReg(18, &ctx->fp18.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(20, &ctx->fp20.f.f_even);
    osSyncPrintfFReg(22, &ctx->fp22.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(24, &ctx->fp24.f.f_even);
    osSyncPrintfFReg(26, &ctx->fp26.f.f_even);
    osSyncPrintf("\n");
    osSyncPrintfFReg(28, &ctx->fp28.f.f_even);
    osSyncPrintfFReg(30, &ctx->fp30.f.f_even);
    osSyncPrintf("\n");
}

OSThread* Fault_FindFaultedThread() {
    OSThread* iter = __osGetActiveQueue();
    while (iter->priority != -1) {
        if (iter->priority > 0 && iter->priority < 0x7F && (iter->flags & 3)) {
            return iter;
        }
        iter = iter->tlnext;
    }
    return NULL;
}
void Fault_Wait5Seconds(void) {
    u32 pad;
    OSTime start;
    start = osGetTime();
    do {
        Fault_Sleep(0x10);
    } while ((osGetTime() - start) <= OS_USEC_TO_CYCLES(5000000));

    sFaultContext->faultActive = 1;
}

void Fault_WaitForButtonCombo(void) {
    Input* input = &sFaultContext->padInput[0];

    FaultDrawer_SetForeColor(0xFFFF);
    FaultDrawer_SetBackColor(1);
    do {
        do {
            Fault_Sleep(0x10);
            Fault_UpdatePadImpl();
        } while (!CHECK_BTN_ALL(input->press.button, 0x80));
    } while (!CHECK_BTN_ALL(input->cur.button, BTN_DLEFT | BTN_L | BTN_R | BTN_CRIGHT));
}

void Fault_DrawMemDumpPage(const char* title, u32* addr, u32 param_3) {
    u32* alignedAddr;
    u32* writeAddr;
    s32 y;
    s32 x;

    alignedAddr = addr;

    if (alignedAddr < (u32*)0x80000000) {
        alignedAddr = (u32*)0x80000000;
    }
    if (alignedAddr > (u32*)0x807FFF00) {
        alignedAddr = (u32*)0x807FFF00;
    }

    alignedAddr = (u32*)((u32)alignedAddr & ~3);
    writeAddr = alignedAddr;
    Fault_FillScreenBlack();
    FaultDrawer_SetCharPad(-2, 0);

    FaultDrawer_DrawText(0x24, 0x12, "%s %08x", title ? title : "PrintDump", alignedAddr);
    if (alignedAddr >= (u32*)0x80000000 && alignedAddr < (u32*)0xC0000000) {
        for (y = 0x1C; y != 0xE2; y += 9) {
            FaultDrawer_DrawText(0x18, y, "%06x", writeAddr);
            for (x = 0x52; x != 0x122; x += 0x34) {
                FaultDrawer_DrawText(x, y, "%08x", *writeAddr++);
            }
        }
    }

    FaultDrawer_SetCharPad(0, 0);
}

void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1) {
    s32 count;
    s32 off;
    Input* input = &sFaultContext->padInput[0];
    u32 addr = pc;

    do {
        count = 0;
        if (addr < 0x80000000) {
            addr = 0x80000000;
        }
        if (addr > 0x807FFF00) {
            addr = 0x807FFF00;
        }

        addr &= ~0xF;
        Fault_DrawMemDumpPage("Dump", (u32*)addr, 0);

        count = 600;
        while (sFaultContext->faultActive) {
            if (count == 0) {
                return;
            }

            count--;

            Fault_Sleep(0x10);
            Fault_UpdatePadImpl();

            if (CHECK_BTN_ALL(input->press.button, BTN_L)) {
                sFaultContext->faultActive = 0;
            }
        }
        do {
            Fault_Sleep(0x10);
            Fault_UpdatePadImpl();
        } while (input->press.button == 0);

        if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
            return;
        }

        off = 0x10;
        if (CHECK_BTN_ALL(input->cur.button, BTN_A)) {
            off = 0x100;
        }
        if (CHECK_BTN_ALL(input->cur.button, BTN_B)) {
            off <<= 8;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
            addr -= off;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
            addr += off;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
            addr = pc;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
            addr = sp;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_CLEFT)) {
            addr = unk0;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_CRIGHT)) {
            addr = unk1;
        }

    } while (!CHECK_BTN_ALL(input->press.button, BTN_L));

    sFaultContext->faultActive = 1;
}

void Fault_FindNextStackCall(uintptr_t* spPtr, uintptr_t* pcPtr, uintptr_t* raPtr) {
    uintptr_t sp = *spPtr;
    uintptr_t pc = *pcPtr;
    uintptr_t ra = *raPtr;
    u32 lastOpc;
    u16 opcHi;
    s16 opcLo;
    u32 imm;

    if (sp & 3 || sp < 0x80000000 || sp >= 0xC0000000 || ra & 3 || ra < 0x80000000 || ra >= 0xC0000000) {
        *spPtr = 0;
        *pcPtr = 0;
        *raPtr = 0;
        return;
    }

    if (pc & 3 || pc < 0x80000000 || pc >= 0xC0000000) {
        *pcPtr = ra;
        return;
    }

    lastOpc = 0;
    while (true) {
        opcHi = *(uintptr_t*)pc >> 16;
        opcLo = *(uintptr_t*)pc & 0xFFFF;
        imm = opcLo;

        if (opcHi == 0x8FBF) {
            ra = *(uintptr_t*)(sp + imm);
        } else if (opcHi == 0x27BD) {
            sp += imm;
        } else if (*(uintptr_t*)pc == 0x42000018) {
            sp = 0;
            pc = 0;
            ra = 0;
            goto end;
        }
        if (lastOpc == 0x3E00008) {
            pc = ra;
            goto end;
        } else if ((lastOpc >> 26) == 2) {
            pc = pc >> 28 << 28 | lastOpc << 6 >> 4;
            goto end;
        }
        lastOpc = *(uintptr_t*)pc;
        pc += 4;
    }

end:
    *spPtr = sp;
    *pcPtr = pc;
    *raPtr = ra;
}

void Fault_DrawStackTrace(OSThread* t, u32 flags) {
    s32 y;
    u32 sp;
    u32 ra;
    u32 pc;
    u32 pad;
    u32 convertedPc;

    sp = t->context.sp;
    ra = t->context.ra;
    pc = t->context.pc;

    Fault_FillScreenBlack();
    FaultDrawer_DrawText(0x78, 0x10, "STACK TRACE");
    FaultDrawer_DrawText(0x24, 0x18, "SP       PC       (VPC)");

    for (y = 1; (y < 22) && (((ra != 0) || (sp != 0)) && (pc != (u32)__osCleanupThread)); y++) {
        FaultDrawer_DrawText(0x24, y * 8 + 24, "%08x %08x", sp, pc);

        if (flags & 1) {
            convertedPc = (u32)Fault_ConvertAddress((void*)pc);
            if (convertedPc != 0) {
                FaultDrawer_Printf(" -> %08x", convertedPc);
            }
        } else {
            FaultDrawer_Printf(" -> ????????");
        }

        Fault_FindNextStackCall(&sp, &pc, &ra);
    }
}

void osSyncPrintfStackTrace(OSThread* t, u32 flags) {
    s32 y;
    u32 sp;
    u32 ra;
    u32 pc;
    u32 convertedPc;

    sp = t->context.sp;
    ra = t->context.ra;
    pc = t->context.pc;

    osSyncPrintf("STACK TRACE");
    osSyncPrintf("SP       PC       (VPC)\n");

    for (y = 1; (y < 22) && (((ra != 0) || (sp != 0)) && (pc != (u32)__osCleanupThread)); y++) {
        osSyncPrintf("%08x %08x", sp, pc);

        if (flags & 1) {
            convertedPc = (u32)Fault_ConvertAddress((void*)pc);
            if (convertedPc != 0) {
                osSyncPrintf(" -> %08x", convertedPc);
            }
        } else {
            osSyncPrintf(" -> ????????");
        }
        osSyncPrintf("\n");

        Fault_FindNextStackCall(&sp, &pc, &ra);
    }
}

void Fault_ResumeThread(OSThread* t) {
    t->context.cause = 0;
    t->context.fpcsr = 0;
    t->context.pc += 4;
    *(u32*)t->context.pc = 0x0000000D; // write in a break instruction
    osWritebackDCache((void*)t->context.pc, 4);
    osInvalICache((void*)t->context.pc, 4);
    osStartThread(t);
}

void Fault_CommitFB(void) {
    u16* fb;

    osViSetYScale(1.0f);
    osViSetMode(&osViModeNtscLan1);
    osViSetSpecialFeatures(0x42); // gama_disable|dither_fliter_enable_aa_mode3_disable
    osViBlack(false);

    if (sFaultContext->fb) {
        fb = sFaultContext->fb;
    } else {
        fb = (u16*)osViGetNextFramebuffer();
        if ((u32)fb == 0x80000000) {
            fb = (u16*)((osMemSize | 0x80000000) - 0x25800);
        }
    }

    osViSwapBuffer(fb);
    FaultDrawer_SetDrawerFB(fb, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Fault_ProcessClients(void) {
    FaultClient* iter = sFaultContext->clients;
    s32 idx = 0;

    while (iter != NULL) {
        if (iter->callback) {
            Fault_FillScreenBlack();
            FaultDrawer_SetCharPad(-2, 0);
            FaultDrawer_Printf("\x1A\x38"
                               "CallBack (%d) %08x %08x %08x\n"
                               "\x1A\x37",
                               idx++, iter, iter->param0, iter->param1);
            FaultDrawer_SetCharPad(0, 0);
            iter->callback(iter->param0, iter->param1);
            Fault_WaitForInput();
            Fault_CommitFB();
        }
        iter = iter->next;
    }
}

#ifdef NON_MATCHING
// needs in-function static bss
void Fault_SetOptionsFromController3(void) {
    static u32 faultCustomOptions;
    Input* input3 = &sFaultContext->padInput[3];
    u32 pad;
    u32 graphPC;
    u32 graphRA;
    u32 graphSP;

    if (CHECK_BTN_ALL(input3->press.button, 0x80)) {
        faultCustomOptions = !faultCustomOptions;
    }

    if (faultCustomOptions) {
        graphPC = sGraphThread.context.pc;
        graphRA = sGraphThread.context.ra;
        graphSP = sGraphThread.context.sp;
        if (CHECK_BTN_ALL(input3->cur.button, BTN_R)) {
            static u32 faultCopyToLog;

            faultCopyToLog = !faultCopyToLog;
            FaultDrawer_SetOsSyncPrintfEnabled(faultCopyToLog);
        }
        if (CHECK_BTN_ALL(input3->cur.button, BTN_A)) {
            osSyncPrintf("GRAPH PC=%08x RA=%08x STACK=%08x\n", graphPC, graphRA, graphSP);
        }
        if (CHECK_BTN_ALL(input3->cur.button, BTN_B)) {
            FaultDrawer_SetDrawerFB(osViGetNextFramebuffer(), 0x140, 0xF0);
            Fault_DrawRec(0, 0xD7, 0x140, 9, 1);
            FaultDrawer_SetCharPad(-2, 0);
            FaultDrawer_DrawText(0x20, 0xD8, "GRAPH PC %08x RA %08x SP %08x", graphPC, graphRA, graphSP);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/fault/Fault_SetOptionsFromController3.s")
#endif

void Fault_SetOptions(void) {
    Fault_UpdatePadImpl();
    Fault_SetOptionsFromController3();
}

void Fault_ThreadEntry(void* arg) {
    OSMesg msg;
    u32 pad;
    OSThread* faultedThread;

    osSetEventMesg(10, &sFaultContext->queue, (OSMesg)1);
    osSetEventMesg(12, &sFaultContext->queue, (OSMesg)2);
    while (1) {
        do {
            osRecvMesg(&sFaultContext->queue, &msg, OS_MESG_BLOCK);

            if (msg == (OSMesg)1) {
                sFaultContext->msgId = 1;
                osSyncPrintf("フォルトマネージャ:OS_EVENT_CPU_BREAKを受信しました\n");
            } else if (msg == (OSMesg)2) {
                sFaultContext->msgId = 2;
                osSyncPrintf("フォルトマネージャ:OS_EVENT_FAULTを受信しました\n");
            } else if (msg == (OSMesg)3) {
                Fault_SetOptions();
                faultedThread = NULL;
                continue;
            } else {
                sFaultContext->msgId = 3;
                osSyncPrintf("フォルトマネージャ:不明なメッセージを受信しました\n");
            }

            faultedThread = __osGetCurrFaultedThread();
            osSyncPrintf("__osGetCurrFaultedThread()=%08x\n", faultedThread);
            if (!faultedThread) {
                faultedThread = Fault_FindFaultedThread();
                osSyncPrintf("FindFaultedThread()=%08x\n", faultedThread);
            }
        } while (faultedThread == NULL);

        __osSetFpcCsr(__osGetFpcCsr() & 0xFFFFF07F);
        sFaultContext->faultedThread = faultedThread;
        while (!sFaultContext->faultHandlerEnabled) {
            Fault_Sleep(1000);
        }
        Fault_Sleep(500);
        Fault_CommitFB();

        if (sFaultContext->faultActive) {
            Fault_Wait5Seconds();
        } else {
            Fault_DrawCornerRec(0xF801);
            Fault_WaitForButtonCombo();
        }

        sFaultContext->faultActive = 1;
        FaultDrawer_SetForeColor(0xFFFF);
        FaultDrawer_SetBackColor(0);

        do {
            Fault_PrintThreadContext(faultedThread);
            osSyncPrintfThreadContext(faultedThread);
            Fault_WaitForInput();
            Fault_DrawStackTrace(faultedThread, 0);
            osSyncPrintfStackTrace(faultedThread, 0);
            Fault_WaitForInput();
            Fault_ProcessClients();
            Fault_DrawMemDump((u32)(faultedThread->context.pc - 0x100), (u32)faultedThread->context.sp, 0, 0);
            Fault_DrawStackTrace(faultedThread, 1);
            osSyncPrintfStackTrace(faultedThread, 1);
            Fault_WaitForInput();
            Fault_FillScreenRed();
            FaultDrawer_DrawText(0x40, 0x50, "    CONGRATURATIONS!    ");
            FaultDrawer_DrawText(0x40, 0x5A, "All Pages are displayed.");
            FaultDrawer_DrawText(0x40, 0x64, "       THANK YOU!       ");
            FaultDrawer_DrawText(0x40, 0x6E, " You are great debugger!");
            Fault_WaitForInput();

        } while (!sFaultContext->exitDebugger);

        while (!sFaultContext->exitDebugger) {
            ;
        }

        Fault_ResumeThread(faultedThread);
    }
}

void Fault_SetFB(void* fb, u16 w, u16 h) {
    sFaultContext->fb = fb;
    FaultDrawer_SetDrawerFB(fb, w, h);
}

void Fault_Start(void) {
    sFaultContext = &gFaultStruct;
    bzero(sFaultContext, sizeof(FaultThreadStruct));
    FaultDrawer_Init();
    FaultDrawer_SetInputCallback(Fault_WaitForInput);
    sFaultContext->exitDebugger = 0;
    sFaultContext->msgId = 0;
    sFaultContext->faultHandlerEnabled = 0;
    sFaultContext->faultedThread = NULL;
    sFaultContext->padCallback = &Fault_PadCallback;
    sFaultContext->clients = NULL;
    sFaultContext->faultActive = 0;
    gFaultStruct.faultHandlerEnabled = 1;
    osCreateMesgQueue(&sFaultContext->queue, sFaultContext->msg, ARRAY_COUNT(sFaultContext->msg));
    StackCheck_Init(&sFaultThreadInfo, sFaultStack, sFaultStack + sizeof(sFaultStack), 0, 0x100, "fault");
    osCreateThread(&sFaultContext->thread, 2, Fault_ThreadEntry, NULL, sFaultStack + sizeof(sFaultStack), 0x7F);
    osStartThread(&sFaultContext->thread);
}

void Fault_HangupFaultClient(const char* arg0, char* arg1) {
    osSyncPrintf("HungUp on Thread %d\n", osGetThreadId(NULL));
    osSyncPrintf("%s\n", arg0 ? arg0 : "(NULL)");
    osSyncPrintf("%s\n", arg1 ? arg1 : "(NULL)");
    FaultDrawer_Printf("HungUp on Thread %d\n", osGetThreadId(NULL));
    FaultDrawer_Printf("%s\n", arg0 ? arg0 : "(NULL)");
    FaultDrawer_Printf("%s\n", arg1 ? arg1 : "(NULL)");
}

void Fault_AddHungupAndCrashImpl(const char* arg0, char* arg1) {
    FaultClient client;
    u32 pad;
    Fault_AddClient(&client, Fault_HangupFaultClient, (void*)arg0, arg1);
    *(u32*)0x11111111 = 0; // trigger an exception
}

void Fault_AddHungupAndCrash(const char* filename, u32 line) {
    char msg[256];
    sprintf(msg, "HungUp %s:%d", filename, line);
    Fault_AddHungupAndCrashImpl(msg, NULL);
}
