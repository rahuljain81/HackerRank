#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define GOTO 0
#define TICK 1

#define MAX_N 20000
#define MAX_M 128
#define MAX_BLOCKCOUNT 1250
#define MAX_DATALENGTH 5120000
#define FRAMESIZE 256

struct huffman
{
	int symbol, codeword, codewordlength;
};

extern void Init(int N,int* size, unsigned char *data, int M, struct huffman* code);
extern void Goto(int frame);
extern int Tick(unsigned char* screen);

static int size[MAX_BLOCKCOUNT];
static unsigned char data[MAX_DATALENGTH];
static struct huffman code[MAX_M];
static int point, expected;

#define THRESHOLD 0x07FFFFFF;

static int calcHash(unsigned char* screen, int len)
{
	int ret = 0, p = 1;

	for(int x=0;x<len;++x)
	{
		ret += screen[x] * p++;
		ret = ret & THRESHOLD;
	}
	return ret;
}

static void LoadData(int *N, int *sizeArray, unsigned char *dataArray, int *M, struct huffman *code) 
{
	int i, t, count;
	scanf("%d", N);
	scanf("%d", M);
	for (int i = 0; i < *M; i++)
	{
		scanf("%d %d %d", &code[i].symbol, &code[i].codeword, &code[i].codewordlength);
	}

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		scanf("%d", &sizeArray[i]);
	}

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		scanf("%d", &t);
		dataArray[i] = (unsigned char)t;
	}
	point = 0;
}

static void run()
{
	int lineN, t = 0, frame, hash;
	int command, resultHash;
	unsigned char screen[FRAMESIZE];

	scanf("%d %d", &lineN,&expected);

	for (int line=0;line<lineN;++line)
	{
		scanf("%d", &command);

		switch (command)
		{
		case GOTO:
			scanf("%d", &frame);
			Goto(frame);
			break;
		case TICK:
			scanf("%d %d", &hash,&frame);
			t = Tick(screen);
			resultHash = calcHash(screen,FRAMESIZE);
			if (t == frame && resultHash == hash)
			{
				point++;
			}
			else
				printf ("res %d hash %d\n", resultHash, hash);

			break;
		default:
			break;
		}
	}
}

int main() {
	int T, N, M, totalScore;
	setbuf(stdout, NULL);

	//freopen("sample_input.txt", "r", stdin);

	scanf("%d", &T);
	totalScore = 0;

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		LoadData(&N,size,data,&M,code);

		Init(N, size, data, M, code);
		run();

		printf("#%d %d\n", testcase, point);

		if (point == expected)
			totalScore++;
	}
	printf("total score = %d\n", totalScore * 100 / T);
	return 0;
}
