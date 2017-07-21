#include <stdio.h>

#define MAX 100000

int arr[MAX];
int rmq[MAX * 3];


void build_minimal_tree(int start, int end, int index)
{
	if (start == end)
	{
		rmq[index] = arr[start];
		return ;
	}

	if (start > end)
		return;

	int mid = start + (end - start)/2;
	build_minimal_tree (start, mid, 2 * index + 1); //left
	build_minimal_tree (mid + 1, end, 2 * index + 2); //right

	if (rmq[2*index + 1] < rmq[2*index +2])
		rmq[index] = rmq[2*index + 1];
	else
		rmq[index] = rmq[2*index + 2];

	return;
}

int query_tree (int l, int r, int start, int end, int index)
{
	if (l <= start && end <= r)
		return rmq[index];

	if (start > r || end < l)
		return 999999;

	int mid = start + (end - start)/2;
	int left = query_tree (l, r, start, mid, 2 * index + 1);
	int right = query_tree (l, r, mid + 1, end, 2 * index + 2);

	if (left > right)
		return right;
	else
		return left;
}



int main()
{
	int N, M, i, l, r;

	setbuf (stdout, NULL);

	scanf ("%d %d", &N, &M);

	for (i=0; i < N; i++)
		scanf ("%d", &arr[i]);

	build_minimal_tree (0, N-1, 0);
#if 0
	for (i=0; i < (N*N); i++)
		printf ("%d ", rmq[i]);
	printf ("\n");
#endif

	for (i=0; i < M; i++)
	{
		scanf ("%d %d", &l, &r);
		printf ("%d\n", query_tree (l+1, r+1, 1, N, 0));
	}
	return 0;
}

