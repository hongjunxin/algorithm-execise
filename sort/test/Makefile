INCLUDE=-I../ -I../../search -I../../stack -I../../queue
SRC_EXT=../../search/graph.c ../../stack/stack.c ../../queue/queue.c

all:
	gcc $(INCLUDE) $(SRC_EXT) ../topo_sort.c topo_sort_test.c -o topo.out
clean:
	@rm *.out
