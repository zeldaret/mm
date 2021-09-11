#ifndef ULTRA64_RSP_H
#define ULTRA64_RSP_H

/* SP Status Flags */
#define SP_STATUS_HALT        (1 <<  0)
#define SP_STATUS_BROKE       (1 <<  1)
#define SP_STATUS_DMA_BUSY    (1 <<  2)
#define SP_STATUS_DMA_FULL    (1 <<  3)
#define SP_STATUS_IO_FULL     (1 <<  4)
#define SP_STATUS_SSTEP       (1 <<  5)
#define SP_STATUS_INTR_BREAK  (1 <<  6)
#define SP_STATUS_YIELD       (1 <<  7) // SIG0
#define SP_STATUS_YIELDED     (1 <<  8) // SIG1
#define SP_STATUS_TASKDONE    (1 <<  9) // SIG2
#define SP_STATUS_SIG3        (1 << 10)
#define SP_STATUS_SIG4        (1 << 11)
#define SP_STATUS_SIG5        (1 << 12)
#define SP_STATUS_SIG6        (1 << 13)
#define SP_STATUS_SIG7        (1 << 14)

#define SP_CLR_HALT        (1 <<  0)
#define SP_SET_HALT        (1 <<  1)
#define SP_CLR_BROKE       (1 <<  2)
#define SP_CLR_INTR        (1 <<  3)
#define SP_SET_INTR        (1 <<  4)
#define SP_CLR_SSTEP       (1 <<  5)
#define SP_SET_SSTEP       (1 <<  6)
#define SP_CLR_INTR_BREAK  (1 <<  7)
#define SP_SET_INTR_BREAK  (1 <<  8)
#define SP_CLR_SIG0        (1 <<  9)
#define SP_SET_SIG0        (1 << 10)
#define SP_CLR_SIG1        (1 << 11)
#define SP_SET_SIG1        (1 << 12)
#define SP_CLR_SIG2        (1 << 13)
#define SP_SET_SIG2        (1 << 14)
#define SP_CLR_SIG3        (1 << 15)
#define SP_SET_SIG3        (1 << 16)
#define SP_CLR_SIG4        (1 << 17)
#define SP_SET_SIG4        (1 << 18)
#define SP_CLR_SIG5        (1 << 19)
#define SP_SET_SIG5        (1 << 20)
#define SP_CLR_SIG6        (1 << 21)
#define SP_SET_SIG6        (1 << 22)
#define SP_CLR_SIG7        (1 << 23)
#define SP_SET_SIG7        (1 << 24)

#endif
