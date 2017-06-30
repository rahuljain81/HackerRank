#include <iostream>
#include <stdio.h>
#include <malloc/malloc.h>
#include <string.h>
#include <cstdlib>

#define MAXLENGTH 128

char getChar(int a) {
	if (a <= 9) {
		return a + '0';
	}
	else {
		return a + 'A' - 10;
	}
}


void multiply(char *result, char *A, char *B);


int getRandomString(char *A) {
	int i, j, k, l;
	l = rand() % MAXLENGTH;
	if (l<10)
		l = l + 10;

	for (i = 0; i<l; i++) {
		k = rand() % 36;
		A[i] = getChar(k);
	}
	A[i] = '\0';
	return l;
}

int main() {
	int tc, i, l1, l2;
	int ANSWER;
	char *result;
	char *A, *B;
	result = (char *)malloc(sizeof(char)* ((MAXLENGTH * 2) + 2));
	A = (char *)malloc(sizeof(char)* MAXLENGTH + 1);
	B = (char *)malloc(sizeof(char)* MAXLENGTH + 1);
	srand(3);

	//for (tc = 1; tc<21; tc++) 
	{

		ANSWER = 0;
		//for (i = 0; i<10000; i++) 
		{
			l1 = getRandomString(A);
			l2 = getRandomString(B);
			multiply(result, "4ABCD", "EFG"); //stringA * string B = 1PUM48WS
			//multiply(result, A, B);
			printf ("result %s\n", result);
			ANSWER += strlen(result) + result[rand() % (l1 + l2 - 1)];

		}

		printf("CASE#%d %d\n", tc, ANSWER);
	}

	return 0;
}
