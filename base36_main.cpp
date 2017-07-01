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
	l = rand() %  MAXLENGTH;
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
	int tc, i, l1, l2, j;
	int ANSWER;
	char *result, *result1;
	char *A, *B;
	result = (char *)malloc(sizeof(char)* ((MAXLENGTH * 2) + 2));
	result1 = (char *)malloc(sizeof(char)* ((MAXLENGTH * 2) + 2));
	A = (char *)malloc(sizeof(char)* MAXLENGTH + 1);
	B = (char *)malloc(sizeof(char)* MAXLENGTH + 1);
	srand(3);

	for (tc = 1; tc<21; tc++) 
	{

		ANSWER = 0;
		for (i = 0; i<10000; i++) 
		{
			l1 = getRandomString(A);
			l2 = getRandomString(B);
			//multiply(result, "123", "210"); //stringA * string B = 1PUM48WS
			//multiply(result, "4ABCD", "1FG", 0); //stringA * string B = 1PUM48WS
			//multiply(result1, "4ABCD", "1FG", 1); //stringA * string B = 1PUM48WS
			//multiply (result, "H3BNPVYBP9OI2GV","2EQJ4FQBTE5LMEH", 0); //156JBXYQ8RCYTH86DLV8LT32Z8VO0N
			//multiply (result1, "H3BNPVYBP9OI2GV","2EQJ4FQBTE5LMEH", 1); //156JBXYQ8RCYTH86DLV8LT32Z8VO0N
			multiply(result, A, B);
			//printf ("result %s\n", result);
			ANSWER += strlen(result) + result[rand() % (l1 + l2 - 1)];
#if 0
			if (strlen(result) == strlen(result1)) 
			{
				for (j=0; j < strlen(result); j++)
					if (result[j] != result1[j])
					{
						printf ("NOT MATCHING\n");
						break;
					}
			}
			else
			{
				printf ("Length Not matching [%d %d]\n", (int) strlen(result),
						(int)strlen(result1));
				printf ("result [%s]\nresult1[%s]\n", result, result1);
				printf ("A[%s] B[%s]\n", A, B);
			}
#endif
		}

		printf("CASE#%d %d\n", tc, ANSWER);
	}

	return 0;
}
