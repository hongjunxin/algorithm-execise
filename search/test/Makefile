INCLUDE=-I../ -I../../stack -I../../queue -I../../list
SRC_EXT=../../stack/stack.c ../../queue/queue.c

all:
	gcc $(INCLUDE) $(SRC_EXT) ../graph.c graph_test.c -o graph_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c graph_matrix_test.c -o graph_matrix_test.out
	
clean:
	@rm *.out

