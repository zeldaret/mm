#ifndef _STDLIB_H_
#define _STDLIB_H_

typedef struct {
    /* 0x0 */ int quot;
    /* 0x4 */ int rem;
} div_t;


typedef struct {
    /* 0x0 */ long quot;
    /* 0x4 */ long rem;
} ldiv_t;


typedef struct {
    /* 0x0 */ long long quot;
    /* 0x8 */ long long rem;
} lldiv_t;

typedef unsigned int size_t;

typedef int ssize_t;

typedef long wchar_t;

#endif
