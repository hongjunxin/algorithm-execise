SRC_POOL_DIR=../../pool
SRC= \
	$(SRC_POOL_DIR)/ngx_alloc.c \
	$(SRC_POOL_DIR)/ngx_buf.c \
	$(SRC_POOL_DIR)/ngx_palloc.c \
	../ngx_radix_tree.c \

INC= -I$(SRC_POOL_DIR) -I../

all: radix_tree_test  rbtree_test

radix_tree_test: radix_tree_test.c $(SRC)
	gcc $(INC) $(SRC) radix_tree_test.c -o radix_tree_test

rbtree_test: rbtree_test.c ../ngx_rbtree.c
	gcc $(INC) ../ngx_rbtree.c rbtree_test.c -o rbtree_test