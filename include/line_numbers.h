#ifndef LINE_NUMBERS_H
#define LINE_NUMBERS_H

#include "versions.h"

// The macros in this file serve to reduce clutter from version differences that are only due to line numbers being different.

// The "LN" macros defined here are not meant to be used directly. See the wrapper macros below.
#if MM_VERSION == N64_JP_1_1
#define LN(n64_jp_1_1, n64_us) (n64_jp_1_1)
#elif MM_VERSION == N64_US
#define LN(n64_jp_1_1, n64_us) (n64_us)
#else
#error "Unsupported MM version"
#endif

/**
 * These wrappers exist to remove duplication of line numbers being passed to LN.
 * The wrappers have ambiguous names purposefully so they are short and don't add clutter.
 *
 * The groupings of different line numbers are difficult to name, as the exact grouping
 * depends on which versions happen to have changes in a given file.
 */

// N64 JP 1.1 and all other versions
#define LN1(n64_jp_1_1, other) \
    LN(n64_jp_1_1, other)

#endif
