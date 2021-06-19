#include <ultra64.h>
#include <global.h>

// TODO move out
#define OS_CLOCK_RATE 62500000LL

void Fault_SleepImpl(u32 duration) {
    u64 value = (duration * OS_CPU_COUNTER) / 1000ull;
    Sleep_Cycles(value);
}

void Fault_AddClient(FaultClient* client, fault_client_func callback, void* param0, void* param1) {
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
        Fault_Log(D_800984B4, client);
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
        Fault_Log(D_800984EC, client);
    }
}

void Fault_AddAddrConvClient(FaultAddrConvClient* client, fault_address_converter_func callback, void* param) {
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
        Fault_Log(D_80098524, client);
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
        Fault_Log(D_8009856C, client);
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
    s32 v0 = ((raw & 0x7f800000) >> 0x17) - 0x7f;

    if ((v0 >= -0x7e && v0 < 0x80) || raw == 0) {
        FaultDrawer_Printf(D_800985B8, idx, *value);
    } else {
        FaultDrawer_Printf(D_800985C8, idx, raw);
    }
}

void Fault_LogFReg(s32 idx, f32* value) {
    u32 raw = *(u32*)value;
    s32 v0 = ((raw & 0x7F800000) >> 0x17) - 0x7F;

    if ((v0 >= -0x7E && v0 < 0x80) || raw == 0) {
        Fault_Log(D_800985DC, idx, *value);
    } else {
        Fault_Log(D_800985EC, idx, *(u32*)value);
    }
}

void Fault_PrintFPCR(u32 value) {
    s32 i;
    u32 flag = 0x20000;

    FaultDrawer_Printf(D_80098600, value);
    for (i = 0; i < ARRAY_COUNT(sExceptionNames); i++) {
        if (value & flag) {
            FaultDrawer_Printf(D_80098610, sExceptionNames[i]);
            break;
        }
        flag >>= 1;
    }
    FaultDrawer_Printf(D_80098618);
}

void Fault_LogFPCR(u32 value) {
    s32 i;
    u32 flag = 0x20000;

    Fault_Log(D_8009861C, value);
    for (i = 0; i < ARRAY_COUNT(sExceptionNames); i++) {
        if (value & flag) {
            Fault_Log(D_8009862C, sExceptionNames[i]);
            break;
        }
        flag >>= 1;
    }
}

void Fault_PrintThreadContext(OSThread* t) {
    __OSThreadContext* ctx;
    s32 causeStrIdx = (s32)((((u32)t->context.cause >> 2) & 0x1f) << 0x10) >> 0x10;
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
    FaultDrawer_Printf(D_80098634, t->id, causeStrIdx, D_80096B80[causeStrIdx]);
    FaultDrawer_SetCharPad(-1, 0);

    FaultDrawer_Printf(D_80098648, (u32)ctx->pc, (u32)ctx->sr, (u32)ctx->badvaddr);
    FaultDrawer_Printf(D_80098664, (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    FaultDrawer_Printf(D_80098680, (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    FaultDrawer_Printf(D_8009869C, (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    FaultDrawer_Printf(D_800986B8, (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    FaultDrawer_Printf(D_800986D4, (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    FaultDrawer_Printf(D_800986F0, (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    FaultDrawer_Printf(D_8009870C, (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    FaultDrawer_Printf(D_80098728, (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    FaultDrawer_Printf(D_80098744, (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    FaultDrawer_Printf(D_80098760, (u32)ctx->s8, (u32)ctx->ra, (u32)ctx->lo);

    Fault_PrintFPCR(ctx->fpcsr);
    FaultDrawer_Printf(D_80098780);
    Fault_PrintFReg(0, &ctx->fp0.f.f_even);
    Fault_PrintFReg(2, &ctx->fp2.f.f_even);
    FaultDrawer_Printf(D_80098784);
    Fault_PrintFReg(4, &ctx->fp4.f.f_even);
    Fault_PrintFReg(6, &ctx->fp6.f.f_even);
    FaultDrawer_Printf(D_80098788);
    Fault_PrintFReg(8, &ctx->fp8.f.f_even);
    Fault_PrintFReg(0xA, &ctx->fp10.f.f_even);
    FaultDrawer_Printf(D_8009878C);
    Fault_PrintFReg(0xC, &ctx->fp12.f.f_even);
    Fault_PrintFReg(0xE, &ctx->fp14.f.f_even);
    FaultDrawer_Printf(D_80098790);
    Fault_PrintFReg(0x10, &ctx->fp16.f.f_even);
    Fault_PrintFReg(0x12, &ctx->fp18.f.f_even);
    FaultDrawer_Printf(D_80098794);
    Fault_PrintFReg(0x14, &ctx->fp20.f.f_even);
    Fault_PrintFReg(0x16, &ctx->fp22.f.f_even);
    FaultDrawer_Printf(D_80098798);
    Fault_PrintFReg(0x18, &ctx->fp24.f.f_even);
    Fault_PrintFReg(0x1A, &ctx->fp26.f.f_even);
    FaultDrawer_Printf(D_8009879C);
    Fault_PrintFReg(0x1C, &ctx->fp28.f.f_even);
    Fault_PrintFReg(0x1E, &ctx->fp30.f.f_even);
    FaultDrawer_Printf(D_800987A0);
    FaultDrawer_SetCharPad(0, 0);

    if (D_8009BE54 != 0) {
        FaultDrawer_DrawText(0xA0, 0xD8, D_800987A4, D_8009BE54);
    }
}

void Fault_LogThreadContext(OSThread* t) {
    __OSThreadContext* ctx;
    s32 causeStrIdx = (s32)((((u32)t->context.cause >> 2) & 0x1f) << 0x10) >> 0x10;
    if (causeStrIdx == 0x17) {
        causeStrIdx = 0x10;
    }
    if (causeStrIdx == 0x1f) {
        causeStrIdx = 0x11;
    }

    ctx = &t->context;
    Fault_Log(D_800987B0);
    Fault_Log(D_800987B4, t->id, causeStrIdx, D_80096B80[causeStrIdx]);

    Fault_Log(D_800987CC, (u32)ctx->pc, (u32)ctx->sr, (u32)ctx->badvaddr);
    Fault_Log(D_800987EC, (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    Fault_Log(D_8009880C, (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    Fault_Log(D_8009882C, (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    Fault_Log(D_8009884C, (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    Fault_Log(D_8009886C, (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    Fault_Log(D_8009888C, (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    Fault_Log(D_800988AC, (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    Fault_Log(D_800988CC, (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    Fault_Log(D_800988EC, (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    Fault_Log(D_8009890C, (u32)ctx->s8, (u32)ctx->ra, (u32)ctx->lo);
    Fault_Log(D_8009892C);
    Fault_LogFPCR(ctx->fpcsr);
    Fault_Log(D_80098930);
    Fault_LogFReg(0, &ctx->fp0.f.f_even);
    Fault_LogFReg(2, &ctx->fp2.f.f_even);
    Fault_Log(D_80098934);
    Fault_LogFReg(4, &ctx->fp4.f.f_even);
    Fault_LogFReg(6, &ctx->fp6.f.f_even);
    Fault_Log(D_80098938);
    Fault_LogFReg(8, &ctx->fp8.f.f_even);
    Fault_LogFReg(0xa, &ctx->fp10.f.f_even);
    Fault_Log(D_8009893C);
    Fault_LogFReg(0xc, &ctx->fp12.f.f_even);
    Fault_LogFReg(0xe, &ctx->fp14.f.f_even);
    Fault_Log(D_80098940);
    Fault_LogFReg(0x10, &ctx->fp16.f.f_even);
    Fault_LogFReg(0x12, &ctx->fp18.f.f_even);
    Fault_Log(D_80098944);
    Fault_LogFReg(0x14, &ctx->fp20.f.f_even);
    Fault_LogFReg(0x16, &ctx->fp22.f.f_even);
    Fault_Log(D_80098948);
    Fault_LogFReg(0x18, &ctx->fp24.f.f_even);
    Fault_LogFReg(0x1a, &ctx->fp26.f.f_even);
    Fault_Log(D_8009894C);
    Fault_LogFReg(0x1c, &ctx->fp28.f.f_even);
    Fault_LogFReg(0x1e, &ctx->fp30.f.f_even);
    Fault_Log(D_80098950);
}

OSThread* Fault_FindFaultedThread() {
    OSThread* iter = __osGetActiveQueue();
    while (iter->priority != -1) {
        if (iter->priority > 0 && iter->priority < 0x7f && (iter->flags & 3)) {
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

    FaultDrawer_SetForeColor(0xffff);
    FaultDrawer_SetBackColor(1);
    do {
        do {
            Fault_Sleep(0x10);
            Fault_UpdatePadImpl();
        } while (!CHECK_BTN_ALL(input->press.button, 0x80));
    } while (!CHECK_BTN_ALL(input->cur.button, BTN_DLEFT | BTN_L | BTN_R | BTN_CRIGHT));
}

void Fault_DrawMemDumpPage(char* title, u32* addr, u32 param_3) {
    u32* alignedAddr;
    u32* writeAddr;
    s32 y;
    s32 x;

    alignedAddr = addr;

    if (alignedAddr < (u32*)0x80000000) {
        alignedAddr = (u32*)0x80000000;
    }
    if (alignedAddr > (u32*)0x807fff00) {
        alignedAddr = (u32*)0x807fff00;
    }

    alignedAddr = (u32*)((u32)alignedAddr & ~3);
    writeAddr = alignedAddr;
    Fault_FillScreenBlack();
    FaultDrawer_SetCharPad(-2, 0);

    FaultDrawer_DrawText(0x24, 0x12, D_80098954, title ? title : D_8009895C, alignedAddr);
    if (alignedAddr >= (u32*)0x80000000 && alignedAddr < (u32*)0xC0000000) {
        for (y = 0x1C; y != 0xE2; y += 9) {
            FaultDrawer_DrawText(0x18, y, D_80098968, writeAddr);
            for (x = 0x52; x != 0x122; x += 0x34) {
                FaultDrawer_DrawText(x, y, D_80098970, *writeAddr++);
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
        if (addr > 0x807fff00) {
            addr = 0x807fff00;
        }

        addr &= ~0xF;
        Fault_DrawMemDumpPage(D_80098978, (u32*)addr, 0);

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

#ifdef NON_MATCHING
// This function still needs a bit of work
void Fault_FindNextStackCall(u32** sp, u32** pc, u32** ra) {
    u32* currentSp;
    u32* currentPc;
    u32* currentRa;
    u32 lastInst;
    u32 currInst;

    currentSp = *sp;
    currentPc = *pc;
    currentRa = *ra;

    if ((((u32)currentSp & 3) != 0) || (currentSp < (u32*)0x80000000) || (currentSp >= (u32*)0xC0000000) ||
        (((u32)currentRa & 3) != 0) || (currentRa < (u32*)0x80000000) || (currentRa >= (u32*)0xC0000000)) {
        *sp = NULL;
        *pc = NULL;
        *ra = NULL;
        return;
    }

    if ((((u32)currentPc & 3) != 0) || (currentPc < (u32*)0x80000000) || (currentPc >= (u32*)0xC0000000)) {
        *pc = currentRa;
        return;
    }

    lastInst = 0;
    while (1) {
        currInst = *currentPc;
        if (((currInst >> 0x10) & 0xFFFF) == 0x8FBF) {
            currentRa = *(u32**)((u32)currentSp + (s16)currInst);
        } else if (((currInst >> 0x10) & 0xFFFF) == 0x27BD) {
            currentSp = (u32*)((u32)currentSp + (s16)currInst);
        } else if (currInst == 0x42000018) {
            currentSp = NULL;
            currentPc = NULL;
            currentRa = NULL;
            break;
        }

        if (lastInst == 0x03E00008) {
            break;
        }

        if ((lastInst >> 0x1A) == 2) {
            currentPc = (u32*)((((u32)currentPc >> 0x1C) << 0x1C) | ((lastInst << 6) >> 4));
            break;
        }

        lastInst = currInst;
        currentPc++;
    }

    *sp = currentSp;
    *pc = currentPc;
    *ra = currentRa;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/fault/Fault_FindNextStackCall.asm")
#endif

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
    FaultDrawer_DrawText(0x78, 0x10, D_80098980);
    FaultDrawer_DrawText(0x24, 0x18, D_8009898C);

    for (y = 1; (y < 22) && (((ra != 0) || (sp != 0)) && (pc != (u32)__osCleanupThread)); y++) {
        FaultDrawer_DrawText(0x24, y * 8 + 24, D_800989A4, sp, pc);

        if (flags & 1) {
            convertedPc = (u32)Fault_ConvertAddress((void*)pc);
            if (convertedPc != 0) {
                FaultDrawer_Printf(D_800989B0, convertedPc);
            }
        } else {
            FaultDrawer_Printf(D_800989BC);
        }

        Fault_FindNextStackCall((u32**)&sp, (u32**)&pc, (u32**)&ra);
    }
}

void Fault_LogStackTrace(OSThread* t, u32 flags) {
    s32 y;
    u32 sp;
    u32 ra;
    u32 pc;
    u32 convertedPc;

    sp = t->context.sp;
    ra = t->context.ra;
    pc = t->context.pc;

    Fault_Log(D_800989CC);
    Fault_Log(D_800989D8);

    for (y = 1; (y < 22) && (((ra != 0) || (sp != 0)) && (pc != (u32)__osCleanupThread)); y++) {
        Fault_Log(D_800989F4, sp, pc);

        if (flags & 1) {
            convertedPc = (u32)Fault_ConvertAddress((void*)pc);
            if (convertedPc != 0) {
                Fault_Log(D_80098A00, convertedPc);
            }
        } else {
            Fault_Log(D_80098A0C);
        }
        Fault_Log(D_80098A1C);

        Fault_FindNextStackCall((u32**)&sp, (u32**)&pc, (u32**)&ra);
    }
}

void Fault_ResumeThread(OSThread* t) {
    t->context.cause = 0;
    t->context.fpcsr = 0;
    t->context.pc += 4;
    *(u32*)t->context.pc = 0xd;
    osWritebackDCache((void*)t->context.pc, 4);
    osInvalICache((void*)t->context.pc, 4);
    osStartThread(t);
}

void Fault_CommitFB() {
    u16* fb;
    osViSetYScale(1.0f);
    osViSetMode(&osViModeNtscLan1);
    osViSetSpecialFeatures(0x42); // gama_disable|dither_fliter_enable_aa_mode3_disable
    osViBlack(0);

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
            FaultDrawer_Printf(D_80098A20, idx++, iter, iter->param0, iter->param1);
            FaultDrawer_SetCharPad(0, 0);
            iter->callback(iter->param0, iter->param1);
            Fault_WaitForInput();
            Fault_CommitFB();
        }
        iter = iter->next;
    }
}

#ifdef NON_MATCHING
// regalloc and ordering differences around the two bool variables (faultCustomOptions and faultCopyToLog)
void Fault_SetOptionsFromController3(void) {
    Input* input3;
    u32 pad;
    u32 graphPC;
    u32 graphRA;
    u32 graphSP;

    input3 = &sFaultContext->padInput[3];

    if (CHECK_BTN_ALL(input3->press.button, 0x80)) {
        faultCustomOptions = faultCustomOptions == 0;
    }

    if (faultCustomOptions) {
        graphPC = graphOSThread.context.pc;
        graphRA = graphOSThread.context.ra;
        graphSP = graphOSThread.context.sp;
        if (CHECK_BTN_ALL(input3->press.button, BTN_R)) {
            faultCopyToLog = !faultCopyToLog;
            FaultDrawer_SetOsSyncPrintfEnabled(faultCopyToLog);
        }
        if (CHECK_BTN_ALL(input3->press.button, BTN_A)) {
            Fault_Log(D_80098A44, graphPC, graphRA, graphSP);
        }
        if (CHECK_BTN_ALL(input3->press.button, BTN_B)) {
            FaultDrawer_SetDrawerFB(osViGetNextFramebuffer(), 0x140, 0xF0);
            Fault_DrawRec(0, 0xD7, 0x140, 9, 1);
            FaultDrawer_SetCharPad(-2, 0);
            FaultDrawer_DrawText(0x20, 0xD8, D_80098A68, graphPC, graphRA, graphSP);
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/fault/Fault_SetOptionsFromController3.asm")
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
            osRecvMesg(&sFaultContext->queue, &msg, 1);

            if (msg == (OSMesg)1) {
                sFaultContext->msgId = 1;
                Fault_Log(D_80098A88);
            } else if (msg == (OSMesg)2) {
                sFaultContext->msgId = 2;
                Fault_Log(D_80098AC0);
            } else if (msg == (OSMesg)3) {
                Fault_SetOptions();
                faultedThread = NULL;
                continue;
            } else {
                sFaultContext->msgId = 3;
                Fault_Log(D_80098AF4);
            }

            faultedThread = __osGetCurrFaultedThread();
            Fault_Log(D_80098B28, faultedThread);
            if (!faultedThread) {
                faultedThread = Fault_FindFaultedThread();
                Fault_Log(D_80098B4C, faultedThread);
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
            Fault_LogThreadContext(faultedThread);
            Fault_WaitForInput();
            Fault_DrawStackTrace(faultedThread, 0);
            Fault_LogStackTrace(faultedThread, 0);
            Fault_WaitForInput();
            Fault_ProcessClients();
            Fault_DrawMemDump((u32)(faultedThread->context.pc - 0x100), (u32)faultedThread->context.sp, 0, 0);
            Fault_DrawStackTrace(faultedThread, 1);
            Fault_LogStackTrace(faultedThread, 1);
            Fault_WaitForInput();
            Fault_FillScreenRed();
            FaultDrawer_DrawText(0x40, 0x50, D_80098B68);
            FaultDrawer_DrawText(0x40, 0x5A, D_80098B84);
            FaultDrawer_DrawText(0x40, 0x64, D_80098BA0);
            FaultDrawer_DrawText(0x40, 0x6E, D_80098BBC);
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
    osCreateMesgQueue(&sFaultContext->queue, sFaultContext->msg, 1);
    StackCheck_Init(&sFaultThreadInfo, sFaultStack, sFaultStack + sizeof(sFaultStack), 0, 0x100, faultThreadName);
    osCreateThread(&sFaultContext->thread, 2, Fault_ThreadEntry, NULL, sFaultStack + sizeof(sFaultStack), 0x7F);
    osStartThread(&sFaultContext->thread);
}

void Fault_HangupFaultClient(const char* arg0, char* arg1) {
    Fault_Log(D_80098BE0, osGetThreadId(NULL));
    Fault_Log(D_80098BF8, arg0 ? arg0 : D_80098BFC);
    Fault_Log(D_80098C04, arg1 ? arg1 : D_80098C08);
    FaultDrawer_Printf(D_80098C10, osGetThreadId(NULL));
    FaultDrawer_Printf(D_80098C28, arg0 ? arg0 : D_80098C2C);
    FaultDrawer_Printf(D_80098C34, arg1 ? arg1 : D_80098C38);
}

void Fault_AddHungupAndCrashImpl(const char* arg0, char* arg1) {
    FaultClient client;
    char padd[4];
    Fault_AddClient(&client, (fault_client_func)Fault_HangupFaultClient, (void*)arg0, arg1);
    *(u32*)0x11111111 = 0; // trigger an exception
}

void Fault_AddHungupAndCrash(const char* filename, u32 line) {
    char msg[256];
    sprintf(msg, D_80098C40, filename, line);
    Fault_AddHungupAndCrashImpl(msg, NULL);
}
