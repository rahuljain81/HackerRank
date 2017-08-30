#include <stdio.h>
#if 0
typedef struct
{
	unsigned int a:5;
	unsigned int b:5;
	unsigned int c:5;
	unsigned int d:5;
	unsigned int e:5;
	unsigned int f:5;
	unsigned int x:2;
}encode;

int main()
{
	int i = 29 << 25 | 25 << 20 | 20 << 15 | 14 << 10 | 23 << 5 | 7;

	encode *f = (encode *) &i;
	encode e = *f;
	printf ("size %d\n", (int) sizeof (encode));
	printf ("a %d b %d c %d d %d e %d f %d x %d\n", e.a, e.b, e.c, e.d, e.e, e.f, e.x);
	return 0;
}

#endif
typedef struct
{
	unsigned int a:5;
	unsigned int b:5;
	unsigned int c:5;
	unsigned int d:5;
	unsigned int e:5;
	unsigned int f:5;
	unsigned int x:2;
}encode;

#define MAX 6

static char gg(char i)
{
	switch (i)
	{
		case 26: return '+'; break;
		case 27: return '-'; break;
		case 28: return '/'; break;
		case 29: return '*'; break;
		case 30: return ' '; break;
		case 31: return 31; break;
		default:  return 'a' +  i; break;
	}
	printf ("SHOULD NOT\n");
	return 0;
}

#define MAXVAL 999996 


/*this function should decrypt the data in ‘input’ buffer and store decrypted data to ‘output’ buffer. Update the size of output buffer in ‘outputLength’*/
void decrypt(const int *input, char *output, int *outputLength)
{
	int x = 0;
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int ee;
	unsigned int f;
	int flag = 0;
	int len = 0;

	for (int i = 0; ; i++)
	{
		x = input[i];
		encode* ff = (encode *) &x;
		encode e = *ff;
		x = 0;
	
		if (len+1 >  MAXVAL)
			break;

		f = gg (e.f);
		if (f == 31) break;
		output[len++] = f;

		ee = gg (e.e);
		if (ee == 31) break;
		output[len++] = ee;

		d = gg (e.d);
		if (d == 31) break;
		output[len++] = d;

		c = gg (e.c);
		if (c == 31) break;
		output[len++] = c;

		b = gg (e.b);
		if (b == 31) break;
		output[len++] = b;

		a = gg (e.a); 
		if (a == 31) break;
		output[len++] = a;

#if 0	
		printf ("ad0 a %d b %d c %d d %d e %d f %d\n", output[len-5-1],
				output[len-4-1],
					output[len-3-1], output[len-2-1], output[len-1-1], output[len-1]);

		printf ("ad1 %d b %d c %d d %d e %d f %d x %d\n", e.a, e.b, e.c, e.d, e.e, e.f, e.x);
		printf ("ad2 %d b %d c %d d %d e %d f %d \n", a, b, c, d, ee, f );
#endif
	}

	*outputLength = len;
}

static char ff(char i)
{
	switch (i)
	{
		case '+': return 26; break;
		case '-': return 27; break;
		case '/': return 28; break;
		case '*': return 29; break;
		case ' ': return 30; break;
		default:  return i - 'a'; break;
	}
	printf ("SHOULD NOT\n");
	return 0;
}


/* this function should encrypt the data in ‘input’ buffer and store to ‘output’ buffer. size of input buffer is ‘inputLength’ bytes*/
void encrypt(const char *input, int inputLength, int *output)
{
	int x = 0;
	int remainder = inputLength%MAX;
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char e;
	unsigned char f;
	int j = 0;

	for (int i = 0; i < (inputLength - remainder); i = i + MAX, j++)
	{
		x = 0;
		a = ff (input[i]);
		b = ff (input[i+1]);
		c = ff (input[i+2]);
		d = ff (input[i+3]);
		e = ff (input[i+4]);
		f = ff (input[i+5]);

		x = a << 25 | b << 20 | c << 15 | d << 10 | e << 5 | f;
		output[j] = x;
#if 0	
	//	if (i==0)
		{
			printf ("a1 %d b %d c %d d %d e %d f %d\n", input[i], input[i+1],
					input[i+2], input[i+3], input[i+4], input[i+5]);
			printf ("a2 %d b %d c %d d %d e %d f %d \n", a, b, c, d, e, f);
			encode *f = (encode *) &x;
			encode e = *f;
			printf ("a %d b %d c %d d %d e %d f %d x %d\n", e.a, e.b, e.c, e.d, e.e, e.f, e.x);
		}
#endif
	}

	x = 0;
	for (int i = 0; i < remainder; i++)
	{
		a = ff (input[inputLength - remainder + i]);
		x = x << 5 | a;
	}
	for (int i = 0; i < (MAX - remainder); i++)
	{
		a = 31;
		x = x << 5 | a;
	}

	output[j] = x;
//	printf ("ENCRYPT DONE %d %d\n", inputLength, j);
	return ;

}	


/*this function is called at the start of test case*/
void Init()
{
}

