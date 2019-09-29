#ifndef _XSTDIO_H_
#define _XSTDIO_H_

typedef double ldouble;


typedef struct {
    /* 0x0 */ union {
        /* 0x0 */ long long ll;
        /* 0x0 */ ldouble ld;
    } v;
    /* 0x8 */ unsigned char* s;
    /* 0xC */ int n0;
    /* 0x10 */ int nz0;
    /* 0x14 */ int n1;
    /* 0x18 */ int nz1;
    /* 0x1C */ int n2;
    /* 0x20 */ int nz2;
    /* 0x24 */ int prec;
    /* 0x28 */ int width;
    /* 0x2C */ size_t nchar;
    /* 0x30 */ unsigned int flags;
    /* 0x34 */ unsigned char qual;
} _Pft;

#endif
