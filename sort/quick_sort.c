#include "sort.h"
#include "../stack/stack.h"

static void swap(int x, int y, int *a) 
{
    int tmp;

	tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}

static int do_part(int begin, int end, int *a) 
{
    int i = begin - 1;
    int j;
	int pivot = a[end]; /* use rightest element as pivot */
	
    for (j=begin; j<end; j++)
        if (a[j] < pivot)  
            swap(++i, j, a);
    swap(++i, end, a);
    return i;
}

static void quicksort(int begin, int end, int *a)
{
    int done_point;
    
    if (begin >= end)
        return;
    done_point = do_part(begin, end, a);
    quicksort(begin, done_point-1, a);
    quicksort(done_point+1, end, a);
}

void quick_sort_rec(int *a, unsigned int size)
{
    quicksort(0, size-1, a);
}

void quick_sort_notrec(int *a, unsigned int size)
{
	stack_t *s = init_stack();
	int done_point, begin, end;

	begin = 0;
	end = size - 1;
	done_point = do_part(0, size-1, a);	
	
	if (done_point-1 > begin) {
		s->push(s, begin);
		s->push(s, done_point-1);
	}
	if (done_point+1 < end) {
		s->push(s, done_point+1);
		s->push(s, end);
	}
	while (!s->empty(s)) {
		end = s->pop(s);
		begin = s->pop(s);
		done_point = do_part(begin, end, a);
		if (done_point-1 > begin) {
			s->push(s, begin);
			s->push(s, done_point-1);
		}
		if (done_point+1 < end) {
			s->push(s, done_point+1);
			s->push(s, end);
		}
	}
}

