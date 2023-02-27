#include "global.h"

typedef struct {
    u8 colorIndex;
    char text[11];
} TextInfo;

typedef struct {
    u8 x;
    u8 y;
    u8 colorIndex;
    char text[41];
} TextInfo2;


s32 D_801BB090 = 0;

TextInfo D_801BB094[6] = {
    { 0, "          " },
    { 0, "          " },
    { 0, "          " },
    { 0, "          " },
    { 0, "          " },
    { 0, "          " },
};

Color_RGBA8 D_801BB0DC[8] = {
    { 0, 0, 0, 64 },
    { 0, 0, 255, 64 },
    { 255, 0, 0, 64 },
    { 255, 0, 255, 64 },
    { 0, 255, 0, 64 },
    { 0, 255, 255, 64 },
    { 255, 255, 0, 64 },
    { 255, 255, 255, 64 },
};

s16 D_801BB0FC = 0;

Color_RGBA8 D_801BB100[8] = {
    { 255, 255, 32, 192 },
    { 255, 150, 128, 192 },
    { 128, 96, 0, 64 },
    { 192, 128, 16, 128 },
    { 255, 192, 32, 128 },
    { 230, 230, 220, 64 },
    { 128, 150, 255, 128 },
    { 128, 255, 32, 128 },
};

TextInfo2 D_801F3F80[80];

void func_800E9C90(void) {
    D_801BB090 = 0;
}

void func_800E9CA0(s32 arg0, s32 arg1, const char* arg2) {
    TextInfo* textInfo = &D_801BB094[arg0];
    char* text = textInfo->text;

    D_801BB090 |= 1;
    textInfo->colorIndex = arg1;

    do {
        *text++ = *arg2;
    } while (*arg2++ != 0);
}

void func_800E9CFC(GfxPrint* arg0) {
    Color_RGBA8* temp_v0;
    TextInfo* var_s0;
    s32 var_s1;

    var_s0 = D_801BB094;
    for (var_s1= 0x14; var_s1 < 0x1A; var_s1++) {
        GfxPrint_SetPos(arg0, 0x1A, var_s1);
        temp_v0 = &D_801BB0DC[var_s0->colorIndex];
        GfxPrint_SetColor(arg0, temp_v0->r, temp_v0->g, temp_v0->b, temp_v0->a);
        GfxPrint_Printf(arg0, "%s", var_s0->text);
        *var_s0->text = '\0';
        var_s0++;
    };
}

void func_800E9DBC(u8 arg0, u8 arg1, u8 arg2, const char* arg3) {
    TextInfo2* temp_v0 = &D_801F3F80[D_801BB0FC];
    char* text;
    s16 var_v1;
    char tmp;

    D_801BB090 |= 2;
    if (D_801BB0FC < ARRAY_COUNT(D_801F3F80)) {
        temp_v0->x = arg0;
        temp_v0->y = arg1;
        temp_v0->colorIndex = arg2;

        var_v1 = 0;
        text = temp_v0->text;

        while((*text++ = *arg3++) != '\0') {
            if (var_v1++ >= ARRAY_COUNT(temp_v0->text)) {
                break;
            }
        }
        *text = '\0';
        
        D_801BB0FC++;
    }
}

void func_800E9E94(GfxPrint* arg0) {
    Color_RGBA8* temp_v0;
    TextInfo2* var_s0;
    char* text;
    s32 var_s2;

    for(var_s2 = 0; var_s2 < D_801BB0FC; var_s2++) {
        var_s0 = &D_801F3F80[var_s2];
        temp_v0 = &D_801BB100[var_s0->colorIndex];
        GfxPrint_SetColor(arg0, temp_v0->r, temp_v0->g, temp_v0->b, temp_v0->a);
        GfxPrint_SetPos(arg0, var_s0->x, var_s0->y);
        GfxPrint_Printf(arg0, "%s", var_s0->text);
    };
}

void func_800E9F78(GraphicsContext* gfxCtx) {
    Gfx* sp64;
    Gfx* sp60;
    GfxPrint sp30;
    Gfx* temp_v0;

    if (THGA_GetSize(&gfxCtx->polyOpa) >= 0x2800) {
        GfxPrint_Init(&sp30);

        OPEN_DISPS(gfxCtx);

        sp60 = POLY_OPA_DISP;
        temp_v0 = Graph_GfxPlusOne(sp60);
        gSPDisplayList(DEBUG_DISP++, temp_v0);

        GfxPrint_Open(&sp30, temp_v0);

        if (D_801BB090 & 2) {
            func_800E9E94(&sp30);
        }
        D_801BB0FC = 0;

        if (D_801BB090 & 1) {
            func_800E9CFC(&sp30);
        }

        sp64 = GfxPrint_Close(&sp30);
        gSPEndDisplayList(sp64++);
        Graph_BranchDlist(sp60, sp64);
        POLY_OPA_DISP = sp64;

        CLOSE_DISPS(gfxCtx);

        GfxPrint_Destroy(&sp30);
    }
}