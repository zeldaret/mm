#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;
typedef signed char        s8;
typedef short              s16;
typedef long               s32;
typedef long long          s64;

typedef volatile unsigned char      vu8;
typedef volatile unsigned short     vu16;
typedef volatile unsigned long      vu32;
typedef volatile unsigned long long vu64;
typedef volatile signed char        vs8;
typedef volatile short              vs16;
typedef volatile long               vs32;
typedef volatile long long          vs64;

typedef float  f32;
typedef double f64;

typedef long int Mtx_t[4][4];
typedef union
{
    Mtx_t m;
    long long int forc_structure_alignment;
} Mtx;

#endif
