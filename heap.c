#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX 10000000

int heap_size = 0;
int heap[MAX] = {0, };

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MinHeapify(int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;
    if (l < heap_size && heap[l] < heap[smallest])
        smallest = l;
    if (r < heap_size && heap[r] < heap[smallest])
        smallest = r;
    if (smallest != i)
    {
       int tmp = heap[i];
       heap[i] = heap[smallest];
       heap[smallest] = tmp; 
       MinHeapify(smallest);
    }
}

void display()
{
	int i;
	printf ("\n heap size %d\n", heap_size);
	for (i=0; i < heap_size; i++)
		printf ("%d ", heap[i]);
	printf ("\n");
}

// Inserts a new key 'k'
void insert(int k)
{
    int tmp;
//	printf ("INSERT %d\n", k);
    if (heap_size == MAX)
    {
        return;
    }
 
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    heap[i] = k;
 
    // Fix the min heap property if it is violated
    while (i != 0 && heap[(i-1)/2] > heap[i])
    {
       tmp = heap[i];
       heap[i] = heap[(i-1)/2];
       heap[(i-1)/2] = tmp; 

       i = (i-1)/2;
    }
}

void delete (int num)
{
    int left, right, i, temp, parentnode;
 
    for (i = 0; i < heap_size; i++) {
        if (num == heap[i])
            break;
    }
    if (num != heap[i])
    {
        printf("%d not found in heap list\n", num);
        return;
    }
    
    heap[i] = heap[heap_size - 1];
    heap_size = heap_size - 1;
    parentnode = (i - 1) / 2; /*find parentnode of node i */
   
    MinHeapify(i);
}

int main() 
{
    
    int Q, q, req, val;
    
    scanf ("%d", &Q);
    
    for (q=0; q < Q; q++)
    {
        scanf ("%d", &req);
        switch (req)
        {
            case 1: scanf ("%d\n", &val); insert (val); break;
            case 2: scanf ("%d\n", &val); delete (val); break;
            case 3: printf ("%d\n", heap[0]); break;
        }
		//display();
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
