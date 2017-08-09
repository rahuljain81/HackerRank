#include <stdio.h>

#define MAX_N 20000
#define MAX_M 128
#define MAX_BLOCKCOUNT 1250
#define MAX_DATALENGTH 5120000
#define FRAMESIZE 256
#define MAXHUFF	22
#define MAX_F	16

struct huffman
{
	int symbol, codeword, codewordlength;
};

unsigned char huff_code [MAX_M][MAXHUFF];
int huff_len [MAX_M];
int codeword [MAX_M];
unsigned char huff_symbol[MAX_M];

unsigned char decoded[MAX_BLOCKCOUNT][FRAMESIZE * MAX_F * 8];
unsigned char frame[MAX_BLOCKCOUNT * FRAMESIZE * MAX_F];


int strcmp(unsigned char *s, unsigned char *d, int len)
{
	int i=0;

	while (i < len)
	{
		if (s[i] == d[i])
			i++;
		else
			return 1;
	}
	return 0;
}
int currentframe = 0;
int TotalFrame = 0;

void Init(int N,int* size, unsigned char *data, int M, struct huffman* code)
{
	TotalFrame = N;
	int k;

	// Generate the huffman code
	for (int i=0; i < M; i++)
	{
		huff_len[i] = code[i].codewordlength;
		huff_symbol[i] = code[i].symbol;

		codeword[i] = code[i].codeword;
		int code = codeword[i];

		for (k=0; k < huff_len[i]; k++)
		{
			if (code & 0x1)
				huff_code[i][huff_len[i]-k-1] = '1';
			else
				huff_code[i][huff_len[i]-k-1] = '0';

			code = code >> 1;
		}
		huff_code[i][huff_len[i]] = '\0';
	}
#if 0
	//print
	for (int i=0; i < M; i++)
	{
		printf ("%d: symbol %d len %d code %d=[%s]\n", i, huff_symbol[i], huff_len[i], codeword[i], huff_code[i]);
	}
#endif

	int sz = 0;
	int blocks =  N/MAX_F;	

	//For each block, decode the data
	for (int i=0; i < blocks; i++)
	{
		//For each encoded data byte, split it to 8 bytes.
		k =0;
		for (int j=sz; j < (sz + size[i]); j++) 
		{
			unsigned char ch = data[j];
			for (int index = 0; index < 8; index++)
			{
				if (ch & 0x1) //LSB is 1
					decoded[i][k + 8 - index -1] = '1';
				else
					decoded[i][k + 8 - index -1] = '0';
				ch = ch >> 1;
			}
			k += 8;
		}

		//Compare the decoded data against huffman code and generate frame data with huffman symbols
		int offset = 0;
		for(int j=0; j < MAX_F * FRAMESIZE; j++)
		{
			int found = 0;
			unsigned char *str = decoded[i];
			for (k=0; k < M && !found; k++)
			{
				if (strcmp(str + offset, huff_code[k], huff_len[k]) == 0)
				{
					found = 1;
					break;
				}
			}

			if (found == 0)
			{
				printf ("SHOULD NOT HAPPEN j%d offset %d\n", j, offset);
				return ;
			}

			offset += huff_len[k];
			frame[i * MAX_F * FRAMESIZE + j] = (unsigned char)huff_symbol[k];
		}

		for(int j=FRAMESIZE; j < MAX_F * FRAMESIZE; j++)
			frame[i * MAX_F * FRAMESIZE + j] = frame[i * MAX_F * FRAMESIZE + j] + frame[i * MAX_F * FRAMESIZE + j - FRAMESIZE] - 128;

		sz = sz + size[i];
	}
}

void Goto(int frame)
{
	currentframe = frame;
}
int Tick(unsigned char* screen)
{
	int retframe = currentframe;
	for (int i=0; i < FRAMESIZE; i++)
	{
		screen[i] = frame [ currentframe * FRAMESIZE + i];
	}

	if(TotalFrame != (currentframe+1))
		currentframe++;
	return retframe;
}

