INCLUDE=-I.. \
        -I../../stack \
        -I../../queue \
        -I../../list

SRC_EXT=../../stack/stack.c \
        ../../queue/queue.c \
        ../../queue/priority_queue.c

all:
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph.c graph_test.c -o graph_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c graph_matrix_test.c -o graph_matrix_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c generate_mst_test.c -o generate_mst_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c dijkstra_test.c -o dijkstra_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c floyd_test.c -o floyd_test.out
	gcc -g $(INCLUDE) $(SRC_EXT) ../graph_matrix.c warshall_test.c -o warshall_test.out
	
clean:
	@rm *.out

