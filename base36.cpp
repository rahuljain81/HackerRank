#include <stdio.h>

#define MAXLENGTH 128

//#define DEBUG

#define MAX 36

typedef struct
{
	char val, carry;
}node;

node add[MAX][MAX];
node multiple[MAX][MAX];

int once = 0;

char decimal_to_base36(int a)
{
	if (a <= 9) 
	{
		return a + '0';
	}
	else 
	{
		return a + 'A' - 10;
	}
}

int base36_to_decimal(char a)
{
	if ((a - '0') <= 9) 
	{
		return a - '0';
	}
	else 
	{
		return a - 'A' + 10;
	}
}

void init()
{
	int i, j, out, questionent, remainder;

	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			out = i * j;
			questionent = out / MAX;
			remainder = out % MAX;

			multiple[i][j].val = decimal_to_base36(remainder);
			multiple[i][j].carry = decimal_to_base36(questionent);

			out = i + j;
			questionent = out / MAX;
			remainder = out % MAX;

			add[i][j].val = decimal_to_base36(remainder);
			add[i][j].carry = decimal_to_base36(questionent);
		}
	}
}

void dump()
{
	int i, j;
	printf("Multiply\n");
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			printf("[(%c, %c) %c,%c] ", decimal_to_base36 (i), decimal_to_base36 (j), multiple[i][j].val, multiple[i][j].carry);
		}
		printf("\n");
	}

	printf("Add\n");
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			printf("[(%c, %c) %c,%c] ", decimal_to_base36(i), decimal_to_base36(j), add[i][j].val, add[i][j].carry);
		}
		printf("\n");
	}
}

void multiply(char *result, char *A, char *B) 
{
	char *C, out1 [MAXLENGTH*2+2], out2[MAXLENGTH * 2 + 2];
	char AA[MAXLENGTH * 2 + 2], BB[MAXLENGTH * 2 + 2];
	char carry, tmp1, tmp2;

	int count1 = 0, count2 = 0, i, j, x, y, index, carry_current_index;

	if (!once)
	{
		init();
		//dump();
		once = 1;
	}

	//Reverse Input array A
	i = 0;
	while (A[i++]);
	i--;

	for (j = 0; j < i; j++)
	{
		AA[j] = A[i - j - 1];
	}
	AA[j] = '\0';

	//Reverse Input array B
	i = 0;
	while (B[i++]);
	i--;

	for (j = 0; j < i; j++)
	{
		BB[j] = B[i - j - 1];
	}
	BB[j] = '\0';


	//Reset Output Arrays
	for (i = 0; i < MAXLENGTH * 2 + 1; i++)
	{
		out2[i] = '0';
		out1[i] = '0';
	}

	//Update A & B Pointers to reversed arrays
	A = AA;
	B = BB;
	index = 0; //To keep track of '0' to be added on right
	while (*B)
	{		
		//Reset carry to 0 for next Index
		carry = '0';
		count2 = count1 = MAXLENGTH * 2;

		//Reset Ouput Array
		for (j = 0; j < index; j++)
			out1[count1--] = '0';

		while (*A)
		{
			//Step 1) Multiply X*Y
			x = base36_to_decimal(*B);
			y = base36_to_decimal(*A);
			tmp1 = multiple[x][y].val;

			//Step 2) Add X*Y+Previous Carry
			x = base36_to_decimal(tmp1);
			y = base36_to_decimal(carry);
			tmp2 = add[x][y].val;

			//Save Step 2 output in array
			out1[count1--] = tmp2;

			//Step 3) new carry with Step 2.
			carry_current_index = add[x][y].carry;

			//Step 4) Carry of Step 1.
			x = base36_to_decimal(*B);
			y = base36_to_decimal(*A);
			carry = multiple[x][y].carry;

			//Final Carry: Sum of Step 3 & Step 4
			x = base36_to_decimal(carry_current_index);
			y = base36_to_decimal(carry);
			carry = add[x][y].val;

			//Move to next index of A.
			A++;
		}
		//Save carry (if any)
		if (base36_to_decimal(carry) != 0)
			out1[count1] = carry;
		//EOF
		out1[MAXLENGTH*2+1] = '\0';

#ifdef DEBUG
		for (i=count1; i < (MAXLENGTH*2+2); i++)
			printf ("%c", out1[i]);
		printf ("\n");
#endif

		//As multiplication is done, now we add it to previous multiplication output
		carry = '0';
		for (i = MAXLENGTH * 2; i >= 0; i--)
		{
			//Step1) Add out2[i] + out1[i]
			x = base36_to_decimal(out2[i]);
			y = base36_to_decimal(out1[i]);
			tmp1 = add[x][y].val;

			//Step2) Add tmp output with previous carry
			x = base36_to_decimal(tmp1);
			y = base36_to_decimal(carry);
			tmp2 = add[x][y].val;

			//Step 3) new carry with Step 2.
			carry_current_index = add[x][y].carry;

			//Step 4) Carry of Step 1.
			x = base36_to_decimal(out2[i]);
			y = base36_to_decimal(out1[i]);
			carry = add[x][y].carry;

			//Final Carry: Sum of Step 3 & Step 4
			x = base36_to_decimal(carry_current_index);
			y = base36_to_decimal(carry);
			carry = add[x][y].val;

			//Save Step 2 output in array
			out2[count2--] = tmp2;
		}
		//Save carry (if any)
		if (base36_to_decimal(carry) != 0)
			out2[count2--] = carry;
		//EOF
		out2[MAXLENGTH*2+1] = '\0';

#ifdef DEBUG
		printf ("==\n");
		for (i=count1; i < (MAXLENGTH*2+2); i++)
			printf ("%c", out2[i]);
		printf ("\n");
#endif

		A = AA;
		B++;
		index++;
	}
	for (i=count1,j = 0; i < (MAXLENGTH*2+2); i++, j++)
		result[j] = out2[i];
	result[j] = '\0';	
}
