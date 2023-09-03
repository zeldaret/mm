#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#if (!defined(__GNUC__) && !defined(__clang__)) || defined(M2CTX) || defined(__sgi)
    #ifndef __attribute__
        #define __attribute__(x)
    #endif
#endif

#endif
