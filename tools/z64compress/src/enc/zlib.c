#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>
#include "libdeflate/libdeflate.h"

#define  CAPACITY  (1024 * 1024 * 4)  /* output buffer max (4 mb) */

int
zlibenc(
	void *_src
	, unsigned src_sz
	, void *_dst
	, unsigned *dst_sz
	, void *_ctx
)
{
	unsigned char *src = _src;
	unsigned char *dst = _dst;
	unsigned result_sz;
	
	extern int g_hlen; /* header length */
	memset(dst, 0, g_hlen);
	memcpy(dst, "ZLIB", 4);
	dst[4] = (src_sz >> 24);
	dst[5] = (src_sz >> 16);
	dst[6] = (src_sz >>  8);
	dst[7] = (src_sz >>  0);
	
	/* zlib and gzip have different header lengths
	 * https://stackoverflow.com/a/68538037
	 */
#if 1
	
	#if 0 /* zlib */
	z_stream stream = {0};
	int r;
	stream.avail_in = src_sz;
	stream.next_in = src;
	stream.avail_out = CAPACITY;
	stream.next_out = dst + g_hlen;
	#define HEADER_LEN 2
	if ((r = deflateInit(&stream, Z_BEST_COMPRESSION)) != Z_OK)
	{
		fprintf(stderr, "[!] fatal compression error %d\n", r);
		exit(EXIT_FAILURE);
	}
	if ((r = deflate(&stream, Z_FINISH)) == Z_STREAM_ERROR)
	{
		fprintf(stderr, "[!] Z_STREAM_ERROR\n");
		exit(EXIT_FAILURE);
	}
	deflateEnd(&stream);
	
	result_sz = CAPACITY - stream.avail_out;
	#else /* libdeflate */
	#define HEADER_LEN 0
	int level = 12;
	struct libdeflate_compressor *compressor;
	compressor = libdeflate_alloc_compressor(level);
	result_sz = libdeflate_deflate_compress(
		compressor
		, src, src_sz
		, dst + g_hlen
		, CAPACITY
	);
	libdeflate_free_compressor(compressor);
	#endif
#else
	/* this gzip code was left in for testing purposes; it may
	 * be useful if matching ique recompression is ever revisited;
	 * ique matches (except for one byte...) when compressed using
	 * gzip 1.2.4 or 1.2.4a (they produce identical results),
	 * available here: https://ftp.gnu.org/gnu/gzip/
	 * this is not a compression error, because decompressing the
	 * recompressed rom produces a rom identical to the original
	 * decompressed ique rom;
	 * TODO: find out why that byte doesn't match on recompression;
	 * TODO: once that's working, add --codec ique for those wanting
	 * matching ique recompression; otherwise, modern zlib works great!
	 */
	#define HEADER_LEN 10
	FILE *fp = fopen("tmp.bin", "wb");
	fwrite(src, 1, src_sz, fp);
	fclose(fp);
	system("./gzip -c -9 -n tmp.bin > tmp.bin.gzip");
	fp = fopen("tmp.bin.gzip", "rb");
	fseek(fp, 0, SEEK_END);
	result_sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fread(dst, 1, result_sz, fp);
	fclose(fp);
#endif
	*dst_sz = result_sz + g_hlen;
	
	/* trim zlib/gzip header */
	memmove(dst + g_hlen, dst + g_hlen + HEADER_LEN, result_sz);
	*dst_sz -= HEADER_LEN;
	
	return 0;
	(void)_ctx; /* -Wunused-parameter */
}

