#ifndef _NGX_CORE_H_
#define _NGX_CORE_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef long            ngx_int_t;
typedef unsigned long   ngx_uint_t;

typedef unsigned int uint32_t;
typedef unsigned long  uintptr_t;

typedef unsigned char  u_char;
typedef int  ngx_fd_t;

#define  NGX_OK          0
#define  NGX_ERROR      -1
#define  NGX_AGAIN      -2
#define  NGX_BUSY       -3
#define  NGX_DONE       -4
#define  NGX_DECLINED   -5
#define  NGX_ABORT      -6


typedef struct ngx_chain_s  ngx_chain_t;
typedef struct ngx_buf_s   ngx_buf_t;
typedef struct ngx_pool_s  ngx_pool_t;

#define NGX_ALIGNMENT   sizeof(unsigned long)    /* platform word */

#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ngx_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#endif
