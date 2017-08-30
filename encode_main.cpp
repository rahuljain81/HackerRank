#if 0
A client has specific requirements for a display device. In order to get the customized device built, he approaches Samsung vd division.
Samsung smart TV division has set up a new development lab at client's location for the development purpose. 
There are thousands of log files generated when test cases related to requirements are executed. 
These log files are required to be sent over network for analysis to development center. 
Since sending too much of data on raw form can cause many security and network consumption related problems, there is an encryption decryption mechanism applied on the data. 
Before sending data encryption algorithm is applied over it.
After receiving data decryption algorithm is applied to convert it back to original.
Help development team in encrypting and decrypting the data. 
Data will only consist of 'a'-'z' , '+',  '-',  '*' , '/' , ' '

Encryption:
You will get a data of size N bytes to compress.
You will be given a maximum (4*N)/6 bytes space to store the encrypted data. 
Decryption:
encrypted input data size can be maximum of size (4*N)/6 bytes to decrypt 
Sufficient space is available to store the decrypted data. [Sufficient means it will be at least the size of original unencrypted data]


Please investigate main.cpp for detailed logic
You need to implement the following APIs.

/*this function should decrypt the data in ‘input’ buffer and store decrypted data to ‘output’ buffer. Update the size of output buffer in ‘outputLength’*/
void decrypt(const int *input, char *output, int *outputLength); 

/* this function should encrypt the data in ‘input’ buffer and store to ‘output’ buffer. size of input buffer is ‘inputLength’ bytes*/
void encrypt(const char *input, int inputLength, int *output); 


/*this function is called at the start of test case*/
void Init();
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)

#define T 50
#define MAXVAL 999996 
#define MAXS 166666

static char TC[T][MAXVAL]; 
static int OP[T][MAXS]; 
static char ANS[T][MAXVAL]; 
static int length[T];
static int Anslength[T];
static int N;

static char c[31]  = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n', 'o','p','q','r','s','t','u','v','w','x','y','z','+','-','/','*',' '
};


extern void encrypt(const char *input, int inputLength, int *output); 
extern void decrypt(const int *input, char *output, int *outputLength); 
extern void Init();


void generateTC()
{
    {
        N = MAXVAL;
        length[0] = N;
        for(int j=0;j<N;j++)
            TC[0][j] = c[rand()%31];
    }

    for(int i = 1; i < T-1;i++)
    {
        N = 500000 + rand() % 500000; 
        N = N - N % 6;

        length[i] = N; 
        for(int j = 0; j < N; j++)
            TC[i][j] = c[rand() % 31];
    }

    {
        N = 20;
        length[T-1] = N;
        for(int j = 0;j < N;j++)
            TC[T-1][j] = c[rand()%31];
    }
}


int tcorder[T] = {0,}; 
int visited[T] = {0,};

int main()
{
    int t = 0,i,j; 
    srand(31);

    while(t != T)
    {
        i = rand() % T; 
        if(visited[i] == 0)
        {
            tcorder[t] = i; 
            visited[i] = 1; 
            t++;
        }
    }

    generateTC(); 
    Init();

    for(i = 0;i < T; i++)
        encrypt(TC[tcorder[i]], length[tcorder[i]], OP[tcorder[i]]);

    for(i=0;i<T;i++)
        decrypt(OP[i], ANS[i], &Anslength[i]);

    for(i = 0; i < 50; i++) 
    {
        int lim = length[i]; 

        if(length[i] != Anslength[i])
        {
            printf("0 failed Ex%d Got%d\n", length[i], Anslength[i]); 
            continue;
        }


        for(j = 0;j < lim;j++) 
        {
            if(TC[i][j] != ANS[i][j])
            {
                printf("0 %d lim %d TC%d GOT%d\n", j, lim, TC[i][j], ANS[i][j]); 
                break;
            }
        }
        if(j == lim)
            printf("1\n");
    }
    return 0;
}

