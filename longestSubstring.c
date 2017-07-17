#include <stdio.h>

#define MAX 100000
#define MAX_CHAR 26

char str [MAX+1];

int len, max;

int hash[MAX_CHAR][MAX+1];

int main()
{
	int T, t, i, j, k;
	int ch;
	int count, first, second, tmp;

	scanf ("%d", &T);

	while (T--)
	{
		scanf ("%s", str);

		max = 0;
		len = 0;
		while (str[len] != '\0')
		{
			ch = str[len] - 'a';
			count = hash[ch][0];
			count++;
			hash[ch][count] = len;
			hash[ch][0] = count;
			len++;
		}
		//len++;

		for (i=0; i < MAX_CHAR; i++)
		{
			count = hash[i][0];
			for (j=1; j <= count; j++)
			{
				if ((len - hash[i][j]) < max)
					break;
				for (k=j+1; k <= count; k++)
				{
					if ((len - hash[i][k]) < max)
						break;

					first = hash[i][j];
					second = hash[i][k]; 

					tmp = 0;
					while (str[second] != '\0')
					{
						if (str[first] != str[second])
							break;
						first++;
						second++;
						tmp++;
					}
					if (tmp > max)
						max = tmp;
				}
			}
		}
		printf ("%d\n", max);
		for (i=0; i < MAX_CHAR; i++)
			hash[i][0] = 0;
	}
	return 0;
}

