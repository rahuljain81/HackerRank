#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char source[100];
int qrc[100][100];
char decoded[100];
int fullimage[200][200];
extern void encode(char source[],int encoded[][100]);
extern void decode(int full[][200],char cdecoded[]);
int main()
{
    srand(3);

    int offset_x =0;
    int offset_y =0;

    char finalcopy[100] ={0};
    
    int m_pPassCount = 0;
    //iterator
    int i,x,y ;
    for(i=0;i<1000;i++)
    {
        for(x=0;x<100;x++)
        {
            source[x] = rand()%26 +'A';
        }
        encode(source,qrc);
        for(x=0;x<200;x++)
        {
            for(y=0;y<200;y++)
            {
                fullimage[x][y] =0;
            }
        }
        offset_x = rand()%100;
        offset_y = rand()%100;
        for(x=0;x<100;x++)
        {
            for(y=0;y<100;y++)
            {
                fullimage[offset_x+x][offset_y+y] = (qrc[x][y]==0)?0:1;
            }
        }
        for(x=0;x<13000;x++)
        {
            offset_x = rand()%200;
            offset_y = rand()%200;

            fullimage[offset_x][offset_y] = 1;
        }     
        decode(fullimage,finalcopy);
        if(memcmp(source,finalcopy,100) ==0)
        {
            m_pPassCount++;
        }
    }
	printf("%d",m_pPassCount);
	return 0;
}
