
//https://www.hackerrank.com/challenges/no-prefix-set?h_r=next-challenge&h_v=zen
#include <stdio.h>
#include <stdlib.h>
#define MAX 26

typedef struct Node
{
	struct Node* n[MAX];
	int flag;
} node;

int flag=0;
int new_node = 0;

node * trie = NULL;

node * newnode(node *parent, char ch)
{
	node* temp = (node *) malloc (sizeof (node));
	parent->n[ch - 'a'] = temp;
	temp->flag = 0;
	new_node = 1;
	return temp;
}

void add (node* parent, char *str, int index)
{
	if (str[index] == '\0')
	{
		parent->flag = 1;
		return;
	}

	if (trie == NULL)
	{
		trie = (node *) malloc (sizeof (node));
		node *temp = newnode (trie, str[index]); 
		add (temp, str, index+1);
		return;
	}

	if (parent->n[str[index] - 'a'] == NULL)
	{
		node *temp = newnode (parent, str[index]); 
		add (temp, str, index+1);
	}
	else
	{
		node* temp = parent->n[str[index] - 'a'];
		if (temp->flag == 1)
		{
			flag = 1;
			return;
		}
		add (temp, str, index+1);
	}
}


int main()
{
	int t,T;
	char str[61];

	scanf ("%d", &T);

	for (t=0; t < T; t++)
	{
		new_node = 0;
		scanf ("%s", str);

		add (trie, str, 0);
		if (flag || new_node == 0)
		{
			printf ("BAD SET\n%s\n", str);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		printf ("GOOD SET\n");
	return 0;
}


