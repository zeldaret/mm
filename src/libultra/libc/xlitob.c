#include "stdlib.h"
#include "string.h"
#include "PR/xstdio.h"

#define BUFF_LEN 0x18

char ldigs[] = "0123456789abcdef";
char udigs[] = "0123456789ABCDEF";

void _Litob(_Pft* args, char code) {
    char buff[BUFF_LEN];
    const char* digs;
    int base;
    int i;
    unsigned long long ullval;

    digs = (code == 'X') ? udigs : ldigs;

    base = (code == 'o') ? 8 : (((code != 'x') && (code != 'X')) ? 10 : 16);
    i = BUFF_LEN;
    ullval = args->v.ll;

    if (((code == 'd') || (code == 'i')) && (args->v.ll < 0)) {
        ullval = -ullval;
    }

    if ((ullval != 0) || (args->prec != 0)) {
        buff[--i] = digs[ullval % base];
    }

    args->v.ll = ullval / base;

    while ((args->v.ll > 0) && (i > 0)) {
        lldiv_t qr;
        qr = lldiv(args->v.ll, base);
        args->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    args->n1 = BUFF_LEN - i;

    memcpy(args->s, buff + i, args->n1);

    if (args->n1 < args->prec) {
        args->nz0 = args->prec - args->n1;
    }

    if ((args->prec < 0) && ((args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO)) {
        i = args->width - args->n0 - args->nz0 - args->n1;
        if (i > 0) {
            args->nz0 += i;
        }
    }
}
