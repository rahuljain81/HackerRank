#include <stdio.h>

int mat[3][3] = {
	{0,0,0},
	{0,0,0},
	{1,1,1}
};

int out[3][3];

void copy()
{
	int i, j;
	for (i=0; i <3; i++)
	{
		for (j=0; j <3; j++)
		{
			mat[i][j] = out[i][j];
		}
	}
}
void print()
{
	int i, j;
	for (i=0; i <3; i++)
	{
		for (j=0; j <3; j++)
		{
			printf ("%d ", mat[i][j]);
		}
		printf ("\n");
	}
	printf ("====\n");
}

void trim()
{
	int i, j;

	int flag = 0;

	j = 0;
	while (1)
	{
		for (i=0; i < 3; i++)
			if (mat[i][j])
				return;

		for (i=0; i < 3; i++)
			for (j=1; j < 3; j++)
				out[i][j-1] = mat[i][j];
		for (i=0; i < 3; i++)
			out[i][2] = 0;
		copy();
		printf ("After Trimming \n");
	}
}

void rotate90()
{
	int i, j;
	for (i=0; i <3; i++)
		for (j=0; j <3; j++)
		{
			out[j][2-i] = mat[i][j];
		}
	printf ("Rotation 90\n");
	copy();
	trim();
	print();
}

int main()
{
	print();
	rotate90();
	rotate90();
	rotate90();

	return 0;
}
