#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 102

int arr[MAX][MAX];
int visited[MAX][MAX];

int moves[MAX][2];

int headx, heady;
int tailx, taily;
int len;
int currentdir;
int dirx, diry;
int R, C;
int globallen;
int collision;

void newdirection(char dir)
{
	if (currentdir == 'R' && dir == 'R')	
		currentdir = 'D';
	else if (currentdir == 'D' && dir == 'R')
		currentdir = 'L';
	else if (currentdir == 'L' && dir == 'R')
		currentdir = 'U';
	else if (currentdir == 'U' && dir == 'R')
		currentdir = 'R';
	else if (currentdir == 'R' && dir == 'L')
		currentdir = 'U';
	else if (currentdir == 'U' && dir == 'L')
		currentdir = 'L';
	else if (currentdir == 'L' && dir == 'L')
		currentdir = 'D';
	else if (currentdir == 'D' && dir == 'L')
		currentdir = 'R';

	switch (currentdir)
	{
	case 'R':
		dirx = 0;
		diry = +1;
		break;
	case 'U':
		dirx = -1;
		diry = 0;
		break;
	case 'D':
		dirx = +1;
		diry = 0;
		break;
	case 'L':
		dirx = 0;
		diry = -1;
		break;
	}
}

int directions [4][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

void dump_visited()
{
	int a=0;
	for (int i=1; i <= R; i++)
	{
		for (int j = 1; j <= R; j++)
		{
			printf ("%3d ", visited[i][j]);
			if (visited[i][j])
				a++;
		}
		printf ("\n");
	}
	printf ("globallen %d\n", globallen);
	printf ("tail %d len %d\n", visited[headx][heady], a);
}

void process_move(int steps, char dir)
{
	int newheadx = headx, newheady = heady;
	int newtailx = tailx, newtaily = taily;

	int minx, miny, x, y;

	for (int i = 0; i < steps; i++)
	{
		globallen++;
		newheadx = newheadx + dirx;
		newheady = newheady + diry;

		switch (currentdir)
		{
		case 'R':
			if ((newheady - 1) == C)
				newheady = 1;
			break;
		case 'U':
			if (newheadx == 0)
				newheadx = R;
			break;			
		case 'D':
			if ((newheadx - 1) == R)
				newheadx = 1;
			break;
		case 'L':
			if (newheady == 0)
				newheady = C;
			break;
		}

		if (arr[newheadx][newheady] == 1)
		{
			len++;
			arr[newheadx][newheady] = 0;
		}
		else
		{			
			minx = miny = -1;
			for (int i = 0; i < 4; i++)
			{
				x = newtailx + directions[i][0];
				y = newtaily + directions[i][1];
				//Cyclic Handling
				switch (i)
				{
				case 0:
					if ((y - 1) == C)
						y = 1;
					break;
				case 1:
					if (y == 0)
						y = C;
					break;
				case 2:
					if ((x - 1) == R)
						x = 1;
					break;
				case 3:
					if (x == 0)
						x = R;
					break;				
				}				

				if (visited[x][y] == (visited[newtailx][newtaily] + 1))
				{
					minx = x;
					miny = y;
				}
			}
			visited[newtailx][newtaily] = 0;
			if (len == 1)
			{				
				newtailx = newheadx;
				newtaily = newheady;
			}
			else
			{			
				if (minx == -1 || miny == -1)
				{
					dump_visited();
					printf ("========+SHOULD NOT HAPPED====\n");
					collision = 1;
				}
				newtailx = minx;
				newtaily = miny;
			}			
		}
		if (visited[newheadx][newheady])
		{			
			headx = newheadx;
			heady = newheady;
			collision = 1;
			return;
		}		
		visited[newheadx][newheady] = globallen;
	}
	headx = newheadx;
	heady = newheady;
	tailx = newtailx;
	taily = newtaily;
	newdirection(dir);
}

int main()
{
	int T, S;

	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf("%d %d %d", &S, &R, &C);

		for (int i=1; i <= R; i++)
			for (int j = 1; j <= R; j++)
			{
				arr[i][j] = (((i + j) % 2 != 0) ? 1 : 0);
				visited[i][j] = 0;
			}

		headx = heady = 1;
		tailx = taily = 1;
		len = 1;
		currentdir = 'R';
		dirx = 0;
		diry = 1;
		visited[headx][heady] = 1;
		globallen = 1;
		collision = 0;

		for (int move = 0; move < S; move++)
			scanf("%d %c", &moves[move][0], &moves[move][1]);

		for (int move = 0; move < S && !collision; move++)
		{
			if (move == 0)
				process_move(moves[move][0], moves[move][1]);
			else
				process_move(moves[move][0] - moves[move - 1][0], moves[move][1]);
		}
		if (!collision)
			process_move((R>C)?R:C, 'R');

		//dump_visited();


		printf("Case #%d: %d\n", t + 1, len);
	}
	return 0;
}
