#include "string.h"
#include "stdarg.h"
#include "stdint.h"
#include "PR/xstdio.h"

#define LDSIGN(x) (((unsigned short*)&(x))[0] & 0x8000)

char spaces[] = "                                ";
char zeroes[] = "00000000000000000000000000000000";
#define MAX_PAD ((sizeof(spaces) - 1))

#define ATOI(i, a)                               \
    for (i = 0; (*a >= '0') && (*a <= '9'); a++) \
        if (i < 999)                             \
            i = *a + i * 10 - '0';

#define PUT(fmt, _size)                    \
    if (_size > 0) {                       \
        arg = (void*)pfn(arg, fmt, _size); \
        if (arg != NULL)                   \
            x.nchar += _size;              \
        else                               \
            return x.nchar;                \
    }

#define PAD(m, src, extracond)             \
    if ((extracond) && (m > 0)) {          \
        int i;                             \
        int j;                             \
        for (j = m; j > 0; j -= i) {       \
            if ((unsigned int)j > MAX_PAD) \
                i = (int)MAX_PAD;          \
            else                           \
                i = j;                     \
            PUT(src, i);                   \
        }                                  \
    }

void _Putfld(_Pft* px, va_list* pap, char code, char* ac);

int _Printf(PrintCallback pfn, void* arg, const char* fmt, va_list ap) {
    _Pft x;
    x.nchar = 0;
    while (1) {
        const char* s;
        char c;
        const char* t;

        static const char fchar[] = " +-#0";
        static const int fbit[] = { FLAGS_SPACE, FLAGS_PLUS, FLAGS_MINUS, FLAGS_HASH, FLAGS_ZERO, 0 };

        char ac[0x20];

        s = fmt;
        for (c = *s; c != 0 && c != '%';) {
            c = *++s;
        }

        PUT((char*)fmt, s - fmt);

        if (c == 0) {
            return x.nchar;
        }

        fmt = ++s;
        for (x.flags = 0; (t = strchr(fchar, *s)) != NULL; s++) {
            x.flags |= fbit[t - fchar];
        }

        if (*s == '*') {
            x.width = va_arg(ap, int);
            if (x.width < 0) {
                x.width = -x.width;
                x.flags |= FLAGS_MINUS;
            }
            s++;
        } else {
            ATOI(x.width, s);
        }

        if (*s != '.') {
            x.prec = -1;
        } else if (*++s == '*') {
            x.prec = va_arg(ap, int);
            s++;
        } else {
            ATOI(x.prec, s);
        }

        x.qual = (strchr("hlL", *s) != NULL) ? *s++ : '\0';
        if ((x.qual == 'l') && (*s == 'l')) {
            x.qual = 'L';
            s++;
        }

        _Putfld(&x, &ap, *s, ac);

        x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;

        PAD(x.width, spaces, !(x.flags & FLAGS_MINUS));
        PUT((char*)ac, x.n0);
        PAD(x.nz0, zeroes, 1);
        PUT(x.s, x.n1);
        PAD(x.nz1, zeroes, 1);
        PUT((char*)(&x.s[x.n1]), x.n2)
        PAD(x.nz2, zeroes, 1);
        PAD(x.width, spaces, x.flags & FLAGS_MINUS);

        fmt = (char*)s + 1;
    }
}

void _Putfld(_Pft* px, va_list* pap, char code, char* ac) {
    px->n0 = px->nz0 = px->n1 = px->nz1 = px->n2 = px->nz2 = 0;

    switch (code) {
        case 'c':
            ac[px->n0++] = va_arg(*pap, unsigned int);
            break;

        case 'd':
        case 'i':
            if (px->qual == 'l') {
                px->v.ll = va_arg(*pap, long);
            } else if (px->qual == 'L') {
                px->v.ll = va_arg(*pap, long long);
            } else {
                px->v.ll = va_arg(*pap, int);
            }

            if (px->qual == 'h') {
                px->v.ll = (short)px->v.ll;
            }

            if (px->v.ll < 0) {
                ac[px->n0++] = '-';
            } else if (px->flags & FLAGS_PLUS) {
                ac[px->n0++] = '+';
            } else if (px->flags & FLAGS_SPACE) {
                ac[px->n0++] = ' ';
            }

            px->s = (char*)&ac[px->n0];

            _Litob(px, code);
            break;

        case 'x':
        case 'X':
        case 'u':
        case 'o':
            if (px->qual == 'l') {
                px->v.ll = va_arg(*pap, long);
            } else if (px->qual == 'L') {
                px->v.ll = va_arg(*pap, long long);
            } else {
                px->v.ll = va_arg(*pap, int);
            }

            if (px->qual == 'h') {
                px->v.ll = (unsigned short)px->v.ll;
            } else if (px->qual == 0) {
                px->v.ll = (unsigned int)px->v.ll;
            }

            if (px->flags & FLAGS_HASH) {
                ac[px->n0++] = '0';
                if ((code == 'x') || (code == 'X')) {

                    ac[px->n0++] = code;
                }
            }
            px->s = (char*)&ac[px->n0];
            _Litob(px, code);
            break;

        case 'e':
        case 'f':
        case 'g':
        case 'E':
        case 'G':
            px->v.ld = (px->qual == 'L') ? va_arg(*pap, LONG_DOUBLE_TYPE) : va_arg(*pap, double);

            if (LDSIGN(px->v.ll)) {
                ac[px->n0++] = '-';
            } else if (px->flags & FLAGS_PLUS) {
                ac[px->n0++] = '+';
            } else if (px->flags & FLAGS_SPACE) {
                ac[px->n0++] = ' ';
            }

            px->s = (char*)&ac[px->n0];
            _Ldtob(px, code);
            break;

        case 'n':
            if (px->qual == 'h') {
                *(va_arg(*pap, unsigned short*)) = px->nchar;
            } else if (px->qual == 'l') {
                *va_arg(*pap, unsigned long*) = px->nchar;
            } else if (px->qual == 'L') {
                *va_arg(*pap, unsigned long long*) = px->nchar;
            } else {
                *va_arg(*pap, unsigned int*) = px->nchar;
            }
            break;

        case 'p':
            px->v.ll = (intptr_t)va_arg(*pap, void*);
            px->s = &ac[px->n0];
            _Litob(px, 'x');
            break;

        case 's':
            px->s = va_arg(*pap, char*);
            px->n1 = strlen(px->s);
            if ((px->prec >= 0) && (px->n1 > px->prec)) {
                px->n1 = px->prec;
            }
            break;

        case '%':
            ac[px->n0++] = '%';
            break;

        default:
            ac[px->n0++] = code;
            break;
    }
}
