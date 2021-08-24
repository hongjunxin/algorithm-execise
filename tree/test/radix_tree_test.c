#include <stdio.h>
#include "ngx_radix_tree.h"
#include "ngx_palloc.h"

int main(int argc, char **argv)
{
    ngx_radix_tree_t *tree;
    ngx_pool_t *pool;

    ngx_uint_t k1 = 0x20000000;  // 0010
    ngx_uint_t k2 = 0x40000000;  // 0100
    ngx_uint_t k3 = 0x80000000;  // 1000
    ngx_uint_t k4 = 0xa0000000;  // 1010
    
    ngx_uint_t mask = 0xe0000000;  // 1110
    ngx_uint_t mask2 = 0x80000000; // 1000
    ngx_uint_t _2k1 = 0x00000000;

    ngx_uint_t *found;
    ngx_int_t  rc;

    pool = ngx_create_pool(4096);

    tree = ngx_radix_tree_create(pool, -1);
    if (tree == NULL) {
        printf("ngx_radix_tree_create() failed\n");
        exit(-1);
    }

    ngx_radix32tree_insert(tree, k1, mask, (uintptr_t) &k1);
    ngx_radix32tree_insert(tree, k2, mask, (uintptr_t) &k2);
    ngx_radix32tree_insert(tree, k3, mask, (uintptr_t) &k3);
    ngx_radix32tree_insert(tree, k4, mask, (uintptr_t) &k4);

    ngx_radix32tree_insert(tree, _2k1, mask, (uintptr_t) &k1);     // mask:  1110
    ngx_radix32tree_insert(tree, _2k1, mask2, (uintptr_t) &_2k1);  // mask2: 1000

    /* find方法会一直往下找，并返回最后那个值不为NGX_RADIX_NO_VALUE的值
       所以这里返回的肯定是k1。为什么find方法不使用mask作为参数 */
    found = (ngx_uint_t*) ngx_radix32tree_find(tree, _2k1);
    if ((uintptr_t) found == NGX_RADIX_NO_VALUE || *found != k1) {
        printf("find _2k1 failed\n");
        exit(-1);
    }

    found = (ngx_uint_t*) ngx_radix32tree_find(tree, k1);
    if ((uintptr_t) found == NGX_RADIX_NO_VALUE || *found != k1) {
        printf("find failed\n");
        exit(-1);
    }

    rc = ngx_radix32tree_delete(tree, k4, mask);
    if (rc != NGX_OK) {
        printf("delete failed\n");
        exit(-1);
    }

    found = (ngx_uint_t*) ngx_radix32tree_find(tree, k4);
    if ((uintptr_t) found != NGX_RADIX_NO_VALUE) {
        printf("found the deleted? test failed\n");
        exit(-1);
    }

    printf("radix_tree test passed\n");

    return 0;
}
