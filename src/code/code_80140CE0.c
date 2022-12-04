#include "global.h"
#include "code/z_vimode/z_vimode.c"

extern Gfx D_0E0001C8[];

void func_80140CE0(struct_801F8010* arg0) {
    arg0->type = 0;
    arg0->setScissor = false;
    arg0->color.r = 255;
    arg0->color.g = 255;
    arg0->color.b = 255;
    arg0->color.a = 255;
}

void func_80140D04(struct_801F8010* arg0) {
}

void func_80140D10(struct_801F8010* arg0, Gfx** _gfx) {
    Gfx* gfx = *_gfx;

    gDPPipeSync(gfx++);
    gDPSetPrimDepth(gfx++, -1, -1);

    if (arg0->setScissor == true) {
        gSPDisplayList(gfx++, D_0E0001C8);
    }

    switch (arg0->type) {
        case 1:
            gSPDisplayList(gfx++, sz_vimode_3DL);
            break;
        case 2:
            gDPSetColor(gfx++, G_SETPRIMCOLOR, arg0->color.rgba);
            gSPDisplayList(gfx++, sz_vimode_4DL);
            break;
        case 3:
            gDPSetColor(gfx++, G_SETBLENDCOLOR, arg0->color.rgba);
            gSPDisplayList(gfx++, sz_vimode_1DL);
            break;
        case 4:
            gDPSetColor(gfx++, G_SETFOGCOLOR, arg0->color.rgba);
            gSPDisplayList(gfx++, sz_vimode_2DL);
            break;
    }

    gDPPipeSync(gfx++);
    *_gfx = gfx;
}
