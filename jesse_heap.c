//https://www.hackerrank.com/challenges/jesse-and-cookies

#include <stdio.h>

#define MAX 1000000

int heap[MAX] = {0, };
int heap_size = 0;


void MinHeapify(int index)
{
	int smallest = index;

	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < heap_size && heap[l] < heap[smallest])
		smallest = l;
	if (r < heap_size && heap[r] < heap[smallest])
		smallest = r;

	if (smallest != index)
	{
		int tmp = heap[smallest];
		heap[smallest] = heap[index];
		heap[index] = tmp;
		MinHeapify(smallest);
	}
}
void delete (int val)
{
	int i;

	for (i=0; i < heap_size; i++)
		if (val == heap[i])
			break;

	heap [i] = heap[heap_size - 1];
	heap_size--;
	MinHeapify (i);
}
void display()
{
	int i;
	printf ("\n heap size %d\n", heap_size);
	for (i=0; i < heap_size; i++)
		printf ("%d ", heap[i]);
	printf ("\n");
}


void insert(int val)
{
	int i = heap_size;
	heap_size++;
	heap[i] = val;

	while (i != 0  && heap[i] < heap[(i-1)/2])
	{
		int tmp = heap[i];
		heap[i] = heap[(i-1)/2];
		heap[(i-1)/2] = tmp;

		i = (i-1)/2;
	}
}


int main()
{
	int N, K, n, count, least, second_least, val;
	scanf ("%d %d", &N, &K);

	for (n=0; n < N; n++)
	{
		scanf ("%d", &val);
		insert (val);
	}

	count = 0;
	while (heap[0] < K)
	{
		least = heap[0];
		delete (least);
		second_least = heap[0];
		delete (second_least);
		val = least + 2 * second_least;
		insert (val);
		count++;
		if (heap_size == 1 && heap[0] < K)
		{
            count = -1;
			break;
		}
	}
	printf ("%d\n", count);
	return 0;
}
