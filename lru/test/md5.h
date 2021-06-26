#ifndef _MD5_H_
#define _MD5_H_

#include <stdio.h>
#include <string.h>

typedef unsigned char u_char;
typedef unsigned long uint64_t;
typedef unsigned int uint32_t;

/*
* The basic MD5 functions.
*
* F and G are optimized compared to their RFC 1321 definitions for
* architectures that lack an AND-NOT instruction, just like in
* Colin Plumb's implementation.
*/
#define F(x, y, z)  ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)  ((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)  ((x) ^ (y) ^ (z))
#define I(x, y, z)  ((y) ^ ((x) | ~(z)))

/*
* The MD5 transformation for all four rounds.
*/
#define STEP(f, a, b, c, d, x, t, s)                                          \
    (a) += f((b), (c), (d)) + (x) + (t);                                      \
    (a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s))));                \
    (a) += (b)


/*
* SET() reads 4 input bytes in little-endian byte order and stores them
* in a properly aligned word in host byte order.
*
* The check for little-endian architectures that tolerate unaligned
* memory accesses is just an optimization.  Nothing will break if it
* does not work.
*/

#if (NGX_HAVE_LITTLE_ENDIAN && NGX_HAVE_NONALIGNED)

#define SET(n)      (*(uint32_t *) &p[n * 4])
#define GET(n)      (*(uint32_t *) &p[n * 4])

#else

#define SET(n)                                                                \
    (block[n] =                                                               \
    (uint32_t) p[n * 4] |                                                     \
    ((uint32_t) p[n * 4 + 1] << 8) |                                          \
    ((uint32_t) p[n * 4 + 2] << 16) |                                         \
    ((uint32_t) p[n * 4 + 3] << 24))


#define GET(n)      block[n]

#endif

#define ngx_memcpy(dst, src, n)   (void) memcpy(dst, src, n)
#define ngx_memzero(buf, n)       (void) memset(buf, 0, n)
#define ngx_memset(buf, c, n)     (void) memset(buf, c, n)
#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

typedef struct {
    uint64_t  bytes;
    uint32_t  a, b, c, d;
    u_char    buffer[64];
} ngx_md5_t;

static void ngx_md5_init(ngx_md5_t *ctx);
static void ngx_md5_update(ngx_md5_t *ctx, const void *data, size_t size);
static void ngx_md5_final(u_char result[16], ngx_md5_t *ctx);
static u_char *ngx_hex_dump(u_char *dst, u_char *src, size_t len);
static const u_char *ngx_md5_body(ngx_md5_t *ctx, const u_char *data, size_t size);

void md5(u_char *dst, size_t dst_len, u_char *src, size_t src_len);

#endif
