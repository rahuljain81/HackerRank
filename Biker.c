//https://www.hackerrank.com/challenges/bike-racers

#include <stdio.h>

#define MAX 250

int N, M, K, max;

typedef struct
{
	unsigned long long int x, y;
}point;

point biker[MAX], bike[MAX];

int mat[MAX][MAX];

int visited[MAX];

unsigned long long int dist (point biker, point bike)
{
	return (biker.x - bike.x) *  (biker.x - bike.x) +  (biker.y - bike.y) *  (biker.y - bike.y) ;
}

int bpm (int biker, int used[], int visited[])
{
	int i, j;
	for (j=0; j < M; j++)
	{
		//Biker wants to use jth bike, so mat[biker][j] should be 1 and jth bike is
		//not used
		if (mat[biker][j] && !used[j])
		{
			used[j] = 1; //now, jth bike is used

			//Now, lets check whether jth bike is already blocked by other biker or
			//not
			// If blocked, then move try moving that person to other bike

			if (visited[j] < 0 || bpm (visited[j], used, visited))
			{
				visited[j] = biker;
				return 1;
			}

		}
	}
	return 0;
}

void dump()
{
	int i, j;

	for (i=0; i < N; i++)
	{
		for (j=0; j < M; j++)
			printf ("%d ", mat[i][j]);
		printf ("\n");
	}
}

int check (unsigned long long int mid)
{
	int result = 0; // Count of bikes assigned to bikers
	int i, j, used[MAX];
	unsigned long long int tmp;

	for (i=0; i < M; i++)
		visited[i] = -1;

	for (i=0; i < N; i++)
		for (j=0; j < M; j++)
		{
			tmp  = dist (biker[i], bike[j]);
			if (tmp <= mid)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}

	//dump();

	for (i=0; i < N; i++)
	{
		for (j=0; j < M; j++)
			used[j] = 0;
		if (bpm (i, used, visited))
		   result++;	
	}
	
	return result;
}

int main()
{

	int i, j;
	unsigned long long int	low, high, mid, ans, tmp;

	scanf ("%d %d %d", &N, &M, &K);

	for (i=0; i < N; i++)
			scanf ("%llu %llu", &biker[i].x, &biker[i].y);
	for (i=0; i < M; i++)
			scanf ("%llu %llu", &bike[i].x, &bike[i].y);

	//Find the time of visit of each one to each bike and calculate max
	max = 0;
	for (i=0; i < N; i++)
	{
		for (j=0; j < M; j++)
		{
			tmp  = dist (biker[i], bike[j]);
			if (tmp > max)
				max = tmp;
		}
	}


	//start BST
	low = 0;
	high = max;
	while (low <= high)
	{
		mid = low + (high - low)/2;

		if (check (mid) >= K)
		{
			ans = mid;
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	printf ("%llu\n", ans);

	return 0;
}


