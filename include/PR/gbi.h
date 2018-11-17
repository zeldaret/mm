#ifndef _GBI_H_
#define _GBI_H_

typedef struct {
    /* 0x0 */ short ob[3];
    /* 0x6 */ unsigned short flag;
    /* 0x8 */ short tc[2];
    /* 0xC */ unsigned char cn[4];
} Vtx_t;


typedef struct {
    /* 0x0 */ short ob[3];
    /* 0x6 */ unsigned short flag;
    /* 0x8 */ short tc[2];
    /* 0xC */ signed char n[3];
    /* 0xF */ unsigned char a;
} Vtx_tn;


typedef union {
    /* 0x0 */ Vtx_t v;
    /* 0x0 */ Vtx_tn n;
    /* 0x0 */ long long force_structure_alignment;
} Vtx;


typedef struct {
    /* 0x0 */ unsigned char flag;
    /* 0x1 */ unsigned char v[3];
} Tri;

typedef long Mtx_t[4][4];


typedef union {
    /* 0x0 */ Mtx_t m;
    /* 0x0 */ long long force_structure_alignment;
} Mtx;


typedef struct {
    /* 0x0 */ short vscale[4];
    /* 0x8 */ short vtrans[4];
} Vp_t;


typedef union {
    /* 0x0 */ Vp_t vp;
    /* 0x0 */ long long force_structure_alignment;
} Vp;


typedef struct {
    /* 0x0 */ unsigned char col[3];
    /* 0x3 */ unsigned char pad1;
    /* 0x4 */ unsigned char colc[3];
    /* 0x7 */ unsigned char pad2;
    /* 0x8 */ signed char dir[3];
    /* 0xB */ unsigned char pad3;
} Light_t;


typedef struct {
    /* 0x0 */ unsigned char col[3];
    /* 0x3 */ unsigned char pad1;
    /* 0x4 */ unsigned char colc[3];
    /* 0x7 */ unsigned char pad2;
} Ambient_t;


typedef struct {
    /* 0x0 */ int x1;
    /* 0x4 */ int y1;
    /* 0x8 */ int x2;
    /* 0xC */ int y2;
} Hilite_t;


typedef union {
    /* 0x0 */ Light_t l;
    /* 0x0 */ long long force_structure_alignment[2];
} Light;


typedef union {
    /* 0x0 */ Ambient_t l;
    /* 0x0 */ long long force_structure_alignment[1];
} Ambient;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[7];
} Lightsn;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[1];
} Lights0;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[1];
} Lights1;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[2];
} Lights2;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[3];
} Lights3;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[4];
} Lights4;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[5];
} Lights5;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[6];
} Lights6;


typedef struct {
    /* 0x0 */ Ambient a;
    /* 0x8 */ Light l[7];
} Lights7;


typedef struct {
    /* 0x0 */ Light l[2];
} LookAt;


typedef union {
    /* 0x0 */ Hilite_t h;
    /* 0x0 */ long force_structure_alignment[4];
} Hilite;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int par : 8;
    /* 0x2 */ unsigned int len : 16;
    /* 0x4 */ unsigned int addr;
} Gdma;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad : 24;
    /* 0x4 */ Tri tri;
} Gtri;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad1 : 24;
    /* 0x4 */ int pad2 : 24;
    /* 0x7 */ unsigned char param : 8;
} Gpopmtx;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad0 : 8;
    /* 0x2 */ int mw_index : 8;
    /* 0x3 */ int number : 8;
    /* 0x4 */ int pad1 : 8;
    /* 0x5 */ int base : 24;
} Gsegment;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad0 : 8;
    /* 0x2 */ int sft : 8;
    /* 0x3 */ int len : 8;
    /* 0x4 */ unsigned int data : 32;
} GsetothermodeL;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad0 : 8;
    /* 0x2 */ int sft : 8;
    /* 0x3 */ int len : 8;
    /* 0x4 */ unsigned int data : 32;
} GsetothermodeH;


typedef struct {
    /* 0x0 */ unsigned char cmd;
    /* 0x1 */ unsigned char lodscale;
    /* 0x2 */ unsigned char tile;
    /* 0x3 */ unsigned char on;
    /* 0x4 */ unsigned short s;
    /* 0x6 */ unsigned short t;
} Gtexture;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad : 24;
    /* 0x4 */ Tri line;
} Gline3D;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int pad1 : 24;
    /* 0x4 */ short pad2;
    /* 0x6 */ short scale;
} Gperspnorm;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int fmt : 3;
    /* 0x1 */ unsigned int siz : 2;
    /* 0x1 */ unsigned int pad : 7;
    /* 0x2 */ unsigned int wd : 12;
    /* 0x4 */ unsigned int dram;
} Gsetimg;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int muxs0 : 24;
    /* 0x4 */ unsigned int muxs1 : 32;
} Gsetcombine;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned char pad;
    /* 0x2 */ unsigned char prim_min_level;
    /* 0x3 */ unsigned char prim_level;
    /* 0x4 */ unsigned long color;
} Gsetcolor;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ int x0 : 10;
    /* 0x2 */ int x0frac : 2;
    /* 0x2 */ int y0 : 10;
    /* 0x3 */ int y0frac : 2;
    /* 0x4 */ unsigned int pad : 8;
    /* 0x5 */ int x1 : 10;
    /* 0x6 */ int x1frac : 2;
    /* 0x6 */ int y1 : 10;
    /* 0x7 */ int y1frac : 2;
} Gfillrect;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int fmt : 3;
    /* 0x1 */ unsigned int siz : 2;
    /* 0x1 */ unsigned int pad0 : 1;
    /* 0x1 */ unsigned int line : 9;
    /* 0x2 */ unsigned int tmem : 9;
    /* 0x4 */ unsigned int pad1 : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int palette : 4;
    /* 0x5 */ unsigned int ct : 1;
    /* 0x5 */ unsigned int mt : 1;
    /* 0x5 */ unsigned int maskt : 4;
    /* 0x6 */ unsigned int shiftt : 4;
    /* 0x6 */ unsigned int cs : 1;
    /* 0x6 */ unsigned int ms : 1;
    /* 0x7 */ unsigned int masks : 4;
    /* 0x7 */ unsigned int shifts : 4;
} Gsettile;


typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int sl : 12;
    /* 0x2 */ unsigned int tl : 12;
    /* 0x4 */ int pad : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int sh : 12;
    /* 0x6 */ unsigned int th : 12;
} Gloadtile;

typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int sl : 12;
    /* 0x2 */ unsigned int tl : 12;
    /* 0x4 */ int pad : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int sh : 12;
    /* 0x6 */ unsigned int th : 12;
} Gloadblock;

typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int sl : 12;
    /* 0x2 */ unsigned int tl : 12;
    /* 0x4 */ int pad : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int sh : 12;
    /* 0x6 */ unsigned int th : 12;
} Gsettilesize;

typedef struct {
    /* 0x0 */ int cmd : 8;
    /* 0x1 */ unsigned int sl : 12;
    /* 0x2 */ unsigned int tl : 12;
    /* 0x4 */ int pad : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int sh : 12;
    /* 0x6 */ unsigned int th : 12;
} Gloadtlut;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int xl : 12;
    /* 0x2 */ unsigned int yl : 12;
    /* 0x4 */ unsigned int pad1 : 5;
    /* 0x4 */ unsigned int tile : 3;
    /* 0x5 */ unsigned int xh : 12;
    /* 0x6 */ unsigned int yh : 12;
    /* 0x8 */ unsigned int s : 16;
    /* 0xA */ unsigned int t : 16;
    /* 0xC */ unsigned int dsdx : 16;
    /* 0xE */ unsigned int dtdy : 16;
} Gtexrect;


typedef struct {
    /* 0x0 */ unsigned long w0;
    /* 0x4 */ unsigned long w1;
    /* 0x8 */ unsigned long w2;
    /* 0xC */ unsigned long w3;
} TexRect;


typedef struct {
    /* 0x0 */ unsigned int w0;
    /* 0x4 */ unsigned int w1;
} Gwords;


typedef union {
    /* 0x0 */ Gwords words;
    /* 0x0 */ Gdma dma;
    /* 0x0 */ Gtri tri;
    /* 0x0 */ Gline3D line;
    /* 0x0 */ Gpopmtx popmtx;
    /* 0x0 */ Gsegment segment;
    /* 0x0 */ GsetothermodeH setothermodeH;
    /* 0x0 */ GsetothermodeL setothermodeL;
    /* 0x0 */ Gtexture texture;
    /* 0x0 */ Gperspnorm perspnorm;
    /* 0x0 */ Gsetimg setimg;
    /* 0x0 */ Gsetcombine setcombine;
    /* 0x0 */ Gsetcolor setcolor;
    /* 0x0 */ Gfillrect fillrect;
    /* 0x0 */ Gsettile settile;
    /* 0x0 */ Gloadtile loadtile;
    /* 0x0 */ Gloadtile settilesize;
    /* 0x0 */ Gloadtile loadtlut;
    /* 0x0 */ long long force_structure_alignment;
} Gfx;

#endif
