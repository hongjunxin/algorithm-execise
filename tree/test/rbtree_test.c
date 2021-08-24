#include "ngx_rbtree.h"

typedef struct {
    ngx_rbtree_node_t  node;
    ngx_uint_t num;
} wrap_node_t;

int main(int argc, char **argv)
{
    ngx_rbtree_t  rbtree;
    ngx_rbtree_node_t  sentinel;
    wrap_node_t  nodes[10], *min;
    ngx_uint_t  i;

    ngx_rbtree_init(&rbtree, &sentinel, ngx_rbtree_insert_value);

    for (i = 0; i < 10; ++i) {
        nodes[i].num = i;
        nodes[i].node.key = i;
        ngx_rbtree_insert(&rbtree, &nodes[i].node);
    }

    min = (wrap_node_t*) ngx_rbtree_min(rbtree.root, &sentinel);

    if (min->num != 0) {
        printf("test failed, should be 0\n");
        exit(-1);
    }

    ngx_rbtree_delete(&rbtree, &nodes[0].node);
    
    min = (wrap_node_t*) ngx_rbtree_min(rbtree.root, &sentinel);
    if (min->num != 1) {
        printf("test failed, should be 1\n");
        exit(-1);
    }

    printf("test passed\n");

    return 0;
}
