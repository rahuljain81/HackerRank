#include<stdio.h>

#define MAX_FILESIZE 1000000
#define MAX_SUB 1000
#define ORIGINAL 1
#define MODIFIED 2
#define PENALTY 100000000

struct RESULT{
	int count;
	int diff[MAX_SUB];
};

int o_file[MAX_FILESIZE];
int m_file[MAX_FILESIZE];
int deleteFlag[MAX_FILESIZE];
int delNumbers[MAX_SUB];

int o_filesize, m_filesize, sub;
int get_count=0;
unsigned int mSeed;
RESULT res;


extern RESULT diff();

unsigned int srand(){
	mSeed = (mSeed*1616161+3331)%o_filesize;
	return mSeed;
}


void makefile(){
	int temp, j, k;
	scanf("%d %d %d", &o_filesize, &sub, &mSeed);
	for(int i=0;i<o_filesize;i++){
		o_file[i]=i+1;
		deleteFlag[i]=0;
	}
	for(int i=0;i<o_filesize;i++){
		j = srand();
		temp = o_file[j];
		o_file[j] = o_file[i];
		o_file[i] = temp;
	}
	for(int i=0;i<sub;i++){
		scanf("%d", &temp);
		deleteFlag[temp-1]=1;
	}
	j = 0;
	k = 0;
	for (int i = 0; i < o_filesize; ++i){
		if(deleteFlag[i]==0){
			m_file[j++] = o_file[i];
		}else{
			delNumbers[k++] = o_file[i];
		}
	}
	m_filesize = j;
}

extern int get(int file, int index){
	if(get_count++<2*o_filesize){
		if(file==ORIGINAL){
			if(0<=index && index<o_filesize){
				return o_file[index];
			}else{
				return 0;
			}
		}else{
			if(0<=index && index<m_filesize){
				return m_file[index];
			}else{
				return 0;
			}
		}
	}else{
		return -1;
	}
}

int verification(){
	//printf("Delete count %d",res.count);
	if(res.count!=sub){
		printf("Delete count %d, sub %d",res.count, sub);
		return false;
	}
	for(int i=0;i<sub;i++){
		if(res.diff[i]!=delNumbers[i]){
			printf ("%d) res %d del %d\n", i, res.diff[i], delNumbers[i]);
			return false;
		}
	}
	return true;
}

void run(){
	get_count=0;
	makefile();
	res = diff();
}

int main(){
	int tests, totalScore=0, score;
	freopen ("prof23_input.txt", "r", stdin);
	scanf("%d", &tests);
	for(int t=0;t<tests;t++){
		run();
		if(verification()){
			score = get_count;
		}else{
			score = PENALTY;
		}
		printf("get count %d\n",get_count);
		if( score < 4000 )
		{
			printf("#%d PASS\n", t+1);
		}
		else
		{
			printf("#%d FAIL\n", t+1);
		}
		//printf("#%d %d\n", t+1, score);
		totalScore+=score;
	}
	if( totalScore < 20000 )
	{
		printf("#FinalResult: PASS\n");
	}
	else
	{
		printf("#FinalResult: FAIL\n");
	}
	printf("Total Score : %d\n", totalScore);
	return 0;
}
