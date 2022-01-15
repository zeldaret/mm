#if 0
#include "zx7/zx7.h"
#include "zx7/optimize.c"
#include "zx7/compress.c"
#include "zx7/zx7.c"

int
zx7enc(
	void *_src
	, unsigned src_sz
	, void *_dst
	, unsigned *dst_sz
	, void *_ctx
)
{
	unsigned char *src = _src;
	unsigned char *dst = _dst;
	
	extern int g_hlen; /* header length */
	memset(dst, 0, g_hlen);
	memcpy(dst, "ZX70", 4);
	dst[4] = (src_sz >> 24);
	dst[5] = (src_sz >> 16);
	dst[6] = (src_sz >>  8);
	dst[7] = (src_sz >>  0);
	
	*dst_sz = ZX7Compress(src, src_sz, dst + g_hlen);
	
	if (!*dst_sz)
		return 1;
	
	*dst_sz += g_hlen;
	
	return 0;
}
#endif

