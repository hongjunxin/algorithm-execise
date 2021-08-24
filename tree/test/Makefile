SRC_POOL_DIR=../../pool
SRC= \
	$(SRC_POOL_DIR)/ngx_alloc.c \
	$(SRC_POOL_DIR)/ngx_buf.c \
	$(SRC_POOL_DIR)/ngx_palloc.c \
	../ngx_radix_tree.c \

INC= -I$(SRC_POOL_DIR) -I../

all:
	gcc $(INC) $(SRC) radix_tree_test.c -o radix_tree_test
