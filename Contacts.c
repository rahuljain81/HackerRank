
//https://www.hackerrank.com/challenges/contacts
#include <stdio.h>
#include <stdlib.h>
#define MAX 26

typedef struct Node
{
	struct Node* n[MAX];
	int count;
} node;

node * trie = NULL;

node * newnode(node *parent, char ch)
{
	node* temp = (node *) malloc (sizeof (node));
	parent->n[ch - 'a'] = temp;
	temp->count = 1;
	return temp;
}

void add (node* parent, char *str, int index)
{
	if (str[index] == '\0')
		return;
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
		temp->count++;
		add (temp, str, index+1);
	}
}

int find (node* parent, char *str, int index)
{
	if (str[index] == '\0')
	{
		if (parent == NULL)
			return 0;
		else
			return parent->count;
	}
	if (parent == NULL)
		return 0;

	if (parent->n[str[index] - 'a'])
		return find (parent->n[str[index] - 'a'], str, index+1);
	return 0;
}


int main()
{
	int t,T;
	char opr[21], str[21];

	scanf ("%d", &T);

	for (t=0; t < T; t++)
	{
		scanf ("%s %s", opr, str);

		if (opr[0] == 'a')
			add (trie, str, 0);
		else
			printf ("%d\n", find(trie, str, 0));
	}
	return 0;
}


