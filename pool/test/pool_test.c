#include <stdio.h>
#include "ngx_palloc.h"

int main(int argc, char **argv)
{
    ngx_pool_t *pool;
    char *c;

    pool = ngx_create_pool(4096);
    if (pool == NULL) {
        printf("ngx_create_pool() failed\n");
        exit(-1);
    }

    c = ngx_pcalloc(pool, 1);
    *c = 'B';

    printf("char: %c, sizeof(ngx_pool_t)=%d unused=%d\n", 
        *c, sizeof(ngx_pool_t), 4096 - 1 - sizeof(ngx_pool_t));

    ngx_destroy_pool(pool);

    return 0;
}
