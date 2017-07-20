//http://poj.org/problem?id=1376

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#define MAX 52 //5= for 2 sides
#define MAX_STACK (MAX*MAX*4)

int arr[MAX][MAX];
int visited[MAX][MAX][4];
int sx, sy, ex, ey;

enum direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};
#define MAXPATH 20
typedef struct
{
	int x, y;
	int dir;
	int time;
	int addid;
	int id;
}node;

node bfsarray[MAX_STACK];
long long count, head;
int N, M;

int check_end(node n)
{
	if (n.x == ex && n.y == ey)
		return 1;
	return 0;
}

int check_go(node n, int jump)
{
	int x, y;

	switch (n.dir)
	{
	case NORTH: //up
		x = n.x - jump;
		y = n.y;
		break;
	case SOUTH:
		x = n.x + jump;
		y = n.y;
		break;
	case WEST:
		x = n.x;
		y = n.y - jump;
		break;
	case EAST:
		x = n.x;
		y = n.y + jump;
		break;
	}
	if (x < 0 || x > (N-1) || y < 0 || y > (M-1))
		return 0;
	if (visited[x][y][n.dir])
	{
		if (bfsarray[visited[x][y][n.dir]].time > (n.time + 1))
			bfsarray[visited[x][y][n.dir]].time = n.time + 1;
		return 1;
	}
	if (arr[x][y] || arr[x - 1][y - 1] || arr[x - 1][y] || arr[x][y - 1])
		return 0;

	bfsarray[count].x = x;
	bfsarray[count].y = y;
	bfsarray[count].dir = n.dir;
	bfsarray[count].time = n.time + 1;
	bfsarray[count].addid = n.id;
	bfsarray[count].id = count;
	visited[x][y][n.dir] = count+1;
	count++;

	return 1;
}

int bfs()
{
	while (head < count)
	{
		node n = bfsarray[head++];

		//printf ("%d) %d, %d, %d, %d, %d==\n", n.id, n.x , n.y , n.dir, n.time, n.addid);

		//check end pos
		if (check_end(n))
		{
#if 0
			int count;
			printf ("%d, %d, %d, %d, %d\n", n.id, n.x , n.y, n.dir, n.time);
			do
			{
				n = bfsarray[n.addid];
				count = n.id;
				printf ("%d, %d, %d, %d, %d\n", n.id, n.x , n.y , n.dir, n.time);
			}
			while (count!= 0);
			n = bfsarray[head - 1];
			printf ("\n\n\n");
#endif
			return n.time;
		}
		if (check_go(n, 1))
			if (check_go(n, 2))
				check_go(n, 3);


		switch (n.dir)
		{
		case NORTH:
		case SOUTH:
			if (!visited[n.x][n.y][EAST])
			{
				bfsarray[count].x = n.x;
				bfsarray[count].y = n.y;
				bfsarray[count].dir = EAST;
				bfsarray[count].time = n.time + 1;
				visited[n.x][n.y][EAST] = count+1;
				bfsarray[count].addid = n.id;
				bfsarray[count].id = count;
				count++;
			}
			else
			{
				if (bfsarray[visited[n.x][n.y][EAST]].time > (n.time + 1))
					bfsarray[visited[n.x][n.y][EAST]].time = n.time + 1;
			}
			if (!visited[n.x][n.y][WEST])
			{
				bfsarray[count].x = n.x;
				bfsarray[count].y = n.y;
				bfsarray[count].dir = WEST;
				bfsarray[count].time = n.time + 1;
				visited[n.x][n.y][WEST] = count+1;
				bfsarray[count].addid = n.id;
				bfsarray[count].id = count;
				count++;
			}
			else
			{
				if (bfsarray[visited[n.x][n.y][WEST]].time > (n.time + 1))
					bfsarray[visited[n.x][n.y][WEST]].time = n.time + 1;
			}
			break;
		case EAST:
		case WEST:
			if (!visited[n.x][n.y][SOUTH])
			{
				bfsarray[count].x = n.x;
				bfsarray[count].y = n.y;
				bfsarray[count].dir = SOUTH;
				bfsarray[count].time = n.time + 1;
				visited[n.x][n.y][SOUTH] = count+1;
				bfsarray[count].addid = n.id;
				bfsarray[count].id = count;
				count++;
			}
			else
			{
				if (bfsarray[visited[n.x][n.y][SOUTH]].time > (n.time + 1))
					bfsarray[visited[n.x][n.y][SOUTH]].time = n.time + 1;
			}
			if (!visited[n.x][n.y][NORTH])
			{
				bfsarray[count].x = n.x;
				bfsarray[count].y = n.y;
				bfsarray[count].dir = NORTH;
				bfsarray[count].time = n.time + 1;
				visited[n.x][n.y][NORTH] = count+1;
				bfsarray[count].addid = n.id;
				bfsarray[count].id = count;
				count++;
			}
			else
			{
				if (bfsarray[visited[n.x][n.y][NORTH]].time > (n.time + 1))
					bfsarray[visited[n.x][n.y][NORTH]].time = n.time + 1;
			}
			break;
		}
	}

	return -1;
}

int main()
{
	//setbuf(stdout, NULL);
	while (1)
	{
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0)
			break;

		count = 0;
		head = 0;
		int i, j;
		for (i = 0; i < N; i++)
			for (j = 0; j < M; j++)
				scanf("%d", &arr[i][j]);

#if 0
		//dump
		for (i = 0; i < N + 2; i++)
		{
			for (j = 0; j < M + 2; j++)
				printf("%d ", arr[i][j]);
			printf("\n");
		}
#endif		
		for (i = 1; i < (N + 2); i++)
			for (j = 1; j < (M + 2); j++)
				for (int k = 0; k < 4; k++)
					visited[i][j][k] = 0;

		char dir[20];
		scanf("%d %d %d %d %s", &sx, &sy, &ex, &ey, dir);

		bfsarray[count].x = sx;
		bfsarray[count].y = sy;
		bfsarray[count].time = 0;
		switch (dir[0])
		{
		case 'n':	bfsarray[count].dir = NORTH; break;
		case 's':	bfsarray[count].dir = SOUTH; break;
		case 'e':	bfsarray[count].dir = EAST; break;
		case 'w':	bfsarray[count].dir = WEST; break;
		}
		visited[sx][sy][bfsarray[count].dir] = 1;
		bfsarray[count].addid = 0;
		bfsarray[count].id = count;
		count++;

		printf("%d\n", bfs());
	};
	return 0;
}
