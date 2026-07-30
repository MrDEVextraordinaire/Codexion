#include <stdio.h>

typedef struct
{
	int	coder_id;
	long priority; // timestamp (fifo) or deadline (edf)
}		t_entry;

typedef struct
{
	t_entry slots[256]; // the array that represents the tree
	int count;          // how many entries are currently in the heap
}		t_heap;

// after inserting at the end, bubble the new entry UP
// until its parent is smaller (or it reaches the root)
void	heap_push(t_heap *heap, int coder_id, long priority)
{
	int		child;
	t_entry	tmp;
	int		parent;

	child = heap->count++;
	heap->slots[child] = (t_entry){coder_id, priority};
	while (child > 0)
	{
		parent = (child - 1) / 2;
		if (heap->slots[parent].priority <= heap->slots[child].priority)
			break ; // heap property satisfied, stop
		// swap child with parent
		tmp = heap->slots[parent];
		heap->slots[parent] = heap->slots[child];
		heap->slots[child] = tmp;
		child = parent; // move up
	}
}

// remove the root (minimum), replace it with the last entry,
// then sink that entry DOWN until both children are larger
t_entry	heap_pop(t_heap *heap)
{
	t_entry	tmp;
	int		parent;
	int		left;
	int		right;
	int		index_of_smallest_priority_node;

	t_entry min = heap->slots[0]; // save the minimum
	parent = 0;
	heap->slots[0] = heap->slots[--heap->count]; // move last entry to root
	while (1)
	{
		left = 2 * parent + 1;
		right = 2 * parent + 2;
		index_of_smallest_priority_node = parent;
		// find the index_of_smallest_priority_node among parent and its two children
		if (left < heap->count
			&& heap->slots[left].priority < heap->slots[index_of_smallest_priority_node].priority)
			index_of_smallest_priority_node = left;
		if (right < heap->count
			&& heap->slots[right].priority < heap->slots[index_of_smallest_priority_node].priority)
			index_of_smallest_priority_node = right;
		if (index_of_smallest_priority_node == parent)
			break ; // heap property satisfied, stop
		// swap parent with the smaller child
		tmp = heap->slots[index_of_smallest_priority_node];
		heap->slots[index_of_smallest_priority_node] = heap->slots[parent];
		heap->slots[parent] = tmp;
		parent = index_of_smallest_priority_node; // move down
	}
	return (min);
}

int	main(void)
{
	t_heap heap = {.count = 0};

	// simulate 3 coders requesting the same dongle with different deadlines
	heap_push(&heap, 3, 900); // coder 3, deadline at 900ms
	heap_push(&heap, 1, 300); // coder 1, deadline at 300ms  <-- most urgent
	heap_push(&heap, 2, 600); // coder 2, deadline at 600ms

	printf("Serving in order of urgency (earliest deadline first):\n");
	while (heap.count > 0)
	{
		t_entry next = heap_pop(&heap);
		printf("  coder %d  (deadline %ldms)\n", next.coder_id, next.priority);
	}
	return (0);
}