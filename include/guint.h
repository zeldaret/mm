#ifndef _GUINT_H_
#define _GUINT_H_

// TODO should be in libultra/gu

#include <PR/gbi.h>
#include <PR/abi.h>
#include <PR/ultratypes.h>
#include <sptask.h> // TODO the load path for this is actually PR/sptask.h, why?
#include <PR/gu.h>

typedef union {
    /* 0x0 */ struct {
        /* 0x0 */ unsigned int hi;
        /* 0x4 */ unsigned int lo;
    } word;
    /* 0x0 */ double d;
} du;


typedef union {
    /* 0x0 */ unsigned int i;
    /* 0x0 */ float f;
} fu;

typedef float Matrix[4][4];

#endif
