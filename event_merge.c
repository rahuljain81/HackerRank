#include <stdio.h>

typedef struct
{
	int start;
	int end;
}event;

event e [] = {
				{1,2},
				{4,5},
				{2,4},
				{2,4},
				{0,10},
				{12,15},
				{13,14},
				{12,16},
				{10,11}
};

int size;
int main()
{
	int i, j, merge;
	size = sizeof (e)/sizeof (event);
	printf ("size %d\n", size);
	for (i=0; i < size; i++)
		printf ("[%d, %d]", e[i].start, e[i].end);
	printf ("\n");

	merge = 0;
	while (!merge)
	{
label:
		//for (i=0; i < size; i++)
		//	printf ("[%d, %d]", e[i].start, e[i].end);
		//printf ("\n");
		for (i = 0; i < size; i++)
		{
			for (j = i + 1; j < size; j++)
			{
				//if a>d or b<c the lines don't overlap. provided a<b and c<d.
				if(!(e[j].start > e[i].end || e[i].start > e[j].end))
				{
					//Merge
					//printf ("i %d j %d\n", i, j);
					if (e[j].start < e[i].start)
						e[i].start = e[j].start;
					if (e[j].end > e[i].end)
						e[i].end = e[j].end;

					//now index j needs to replaced with index (size-1)
					if (j+1 != size)
					{
						e[j].start = e[size-1].start;
						e[j].end = e[size-1].end;
					}
					size--;
					goto label;
				}
			}
		}
		merge = 1;
	}

	for (i=0; i < size; i++)
		printf ("[%d, %d]", e[i].start, e[i].end);
	printf ("\n");


	return 0;
}
