
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ngx_alloc.h"

ngx_uint_t  ngx_pagesize = 4096;
ngx_uint_t  ngx_pagesize_shift;
ngx_uint_t  ngx_cacheline_size;


void* ngx_alloc(size_t size)
{
    void  *p;

    p = malloc(size);
    if (p == NULL) {
        printf("malloc(%ld) failed\n", size);
    }

    return p;
}


void* ngx_calloc(size_t size)
{
    void  *p;

    p = ngx_alloc(size);

    if (p) {
        memset(p, 0, size);
    }

    return p;
}

#if (NGX_HAVE_POSIX_MEMALIGN)

void* ngx_memalign(size_t alignment, size_t size)
{
    void  *p;
    int    err;

    err = posix_memalign(&p, alignment, size);

    if (err) {
        printf("posix_memalign(%ld, %ld) failed\n", alignment, size);
        p = NULL;
    }

    return p;
}

#elif (NGX_HAVE_MEMALIGN)

void* ngx_memalign(size_t alignment, size_t size)
{
    void  *p;

    p = memalign(alignment, size);
    if (p == NULL) {
        printf("posix_memalign(%ld, %ld) failed\n", alignment, size);
    }

    return p;
}

#endif
