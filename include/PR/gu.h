#ifndef GU_H
#define GU_H

typedef struct {
    /* 0x0 */ unsigned char* base;
    /* 0x4 */ int fmt;
    /* 0x8 */ int siz;
    /* 0xC */ int xsize;
    /* 0x10 */ int ysize;
    /* 0x14 */ int lsize;
    /* 0x18 */ int addr;
    /* 0x1C */ int w;
    /* 0x20 */ int h;
    /* 0x24 */ int s;
    /* 0x28 */ int t;
} Image;


typedef struct {
    /* 0x0 */ float col[3];
    /* 0xC */ float pos[3];
    /* 0x18 */ float a1;
    /* 0x1C */ float a2;
} PositionalLight;

#endif
