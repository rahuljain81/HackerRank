#define MAXLENGTH 128
#define MAXCHAR		'z'

//#define DEBUG

#define MAX 36

static int multiple[MAXCHAR*MAXCHAR];

int once = 0;

#define decimal_to_base36(a) ((a<=9)?(a+'0'):(a+'A'-10))
#define base36_to_decimal(a) (((a-'0')<=9)?(a-'0'):(a-'A'+10))
void init()
{
	register int i, j;

	for (i = 0; i < MAXCHAR; i++)
	{
		if ((i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9'))
		{			
			for (j = 0; j < MAXCHAR; j++)
			{
				if ((j >= 'A' && j <= 'Z') || (j >= '0' && j <= '9'))
				{					
					multiple[i* MAXCHAR + j] = base36_to_decimal(i) * base36_to_decimal(j);
				}
			}
		}
	}
}

void multiply(char *result, char *A, char *B)
{
	char out1[MAXLENGTH * 2 + 2];
	char AA[MAXLENGTH + 1], BB[MAXLENGTH + 1];
	register int carry, tmp1, tmp2;
	register int maxlength, acount, bcount;

	register int count1 = 0, i, j, K, x, y, index, carry_current_index;

	if (!once)
	{
		init();
		//dump();
		once = 1;
	}

	//Strlen Input array A
	i = 0;
	while (A[i++]);
	i--;
	acount=i;

	//Reverse Input array A
	for (j = 0; j < i; j++)
	{
		AA[j] = A[i - j - 1];	
	}	
	AA[j] = '\0';
	

	//Strlen Input array B
	i = 0;
	while (B[i++]);
	if (maxlength < i)
		maxlength = i;
	i--;
	bcount = i;

	//Reverse Input array B
	for (j = 0; j < i; j++)
	{
		BB[j] = B[i - j - 1];
	}
	BB[j] = '\0';

	//Reset Output Arrays
	for (i = 0; i <  (acount+bcount+1+1); i++)
		out1[i] = '\0';

	//Update A & B Pointers to reversed arrays
	A = AA;
	B = BB;
	index = 0; //To keep track of '0' to be added on right
	{
		int a, b;
		maxlength = acount + bcount + 1 + 1;
		for (b=0; b < bcount; b++)
		{
			//Reset carry to 0 for next digit of 'B'
			carry = 0;
			count1 = maxlength - 1; // 1 left for '\0'
			// Shift to left Ouput Array
			for (j = 0; j < index; j++)
				count1 --;
			
			for (a=0; a < acount; a++)
			{
				//Step 1) Multiply X*Y + previous carry		
				tmp1 = multiple[(*B) * MAXCHAR + (*A)] + carry + out1[count1];
				//output in array
				out1[count1] = tmp1 % MAX;
				count1--;
				//New Carry
				carry = tmp1 / MAX;
				//Move to next index of A.
				A++;
			}
			//Save carry (if any)
			if (carry != 0)
				out1[count1] = carry;
			else
				count1++;
			//EOF
			//out1[maxlength] = '\0';
#ifdef DEBUG
			for (i = count1; i < maxlength; i++)
				printf("%c", decimal_to_base36(out1[i]));
			printf("\n");
#endif
			A = AA;
			B++;
			index++;
		}
		//Skip starting zereos: 0001*1 = 1 & not 0001
		while (out1[count1] == 0)
			count1++;
		for (i = count1, j = 0; i < maxlength; i++, j++)
			result[j] = decimal_to_base36(out1[i]);
		result[j] = '\0';
	}
}
