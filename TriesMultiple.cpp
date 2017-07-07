#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM 10
#define MAX_STR 20
#define MAX_COUNT 50001

#define STRING_TRIE 27 //26 + @
#define NUM_TRIE 10
#define EMAILCNT 5

void sprintf(char *dst, char *src)
{
	while (src[0] != '\0')
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
}

typedef enum
{
	CMD_INIT,
	CMD_ADD,
	CMD_DELETE,
	CMD_CHANGE,
	CMD_SEARCH
} COMMAND;

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

int count;


typedef struct Node
{
	int id;
	char name[MAX_STR];
	char number[MAX_STR];
	char birthday[MAX_STR];
	char email[MAX_STR];
	char memo[MAX_STR];
	int email_length;
}node;

node list[MAX_COUNT];


typedef struct Dll_node
{
	int id;
	struct Dll_node *next;
}dll_node;

typedef struct trie_node
{
	struct trie_node* shash[STRING_TRIE];
	dll_node *dll;
}str_trie;

typedef struct ntrie_node
{
	struct ntrie_node* nhash[NUM_TRIE];
	dll_node *dll;
}num_trie;

str_trie* tname = NULL;
str_trie* temail = NULL;
str_trie* tmemo = NULL;
num_trie* tnumber = NULL;
num_trie* tbirthday = NULL;
int delete_count, change_count;

void reset_str_trie(str_trie *strnode)
{
	int i;
	for (i = 0; i < STRING_TRIE; i++)
	{
		if (strnode->shash[i])
			reset_str_trie(strnode->shash[i]);
	}
	dll_node* sdll = strnode->dll, *prev;

	while (sdll)
	{
		prev = sdll;
		sdll = sdll->next;
		free(prev);
	}
	strnode->dll = NULL;
}

void reset_num_trie(num_trie *numnode)
{
	int i;
	for (i = 0; i < MAX_NUM; i++)
	{
		if (numnode->nhash[i])
			reset_num_trie(numnode->nhash[i]);
	}
	dll_node* sdll = numnode->dll, *prev;

	while (sdll)
	{
		prev = sdll;
		sdll = sdll->next;
		free(prev);
	}
	numnode->dll = NULL;
}

void InitDB()
{
	int i;
	//printf ("=================INIT DB===========\n");
	count = 0;
	for (i = 0; i < count; i++)
		list[i].id = 0;

	
	if (tname)
		reset_str_trie(tname);
	else
	{
		tname = (str_trie *)malloc(sizeof(str_trie));
		tname->dll = NULL;
		for (int i = 0; i < STRING_TRIE; i++)
			tname->shash[i] = NULL;
	}
	if (temail)
		reset_str_trie(temail);
	else
	{
		temail = (str_trie *)malloc(sizeof(str_trie));
		temail->dll = NULL;
		for (int i = 0; i < STRING_TRIE; i++)
			temail->shash[i] = NULL;
	}
	if (tmemo)
		reset_str_trie(tmemo);
	else
	{
		tmemo = (str_trie *)malloc(sizeof(str_trie));
		tmemo->dll = NULL;
		for (int i = 0; i < STRING_TRIE; i++)
			tmemo->shash[i] = NULL;
	}
	if (tnumber)
		reset_num_trie(tnumber);
	else
	{
		tnumber = (num_trie *)malloc(sizeof(num_trie));
		tnumber->dll = NULL;
		for (int i = 0; i < MAX_NUM; i++)
			tnumber->nhash[i] = NULL;		
	}
	if (tbirthday)
		reset_num_trie(tbirthday);
	else
	{
		tbirthday = (num_trie *)malloc(sizeof(num_trie));
		tbirthday->dll = NULL;
		for (int i = 0; i < MAX_NUM; i++)
			tbirthday->nhash[i] = NULL;
	}
};

int mystrlen(char *str)
{
	int len = 0;
	while (str[len++]);
	return len;
}

void insert_str_trie(str_trie *head, char *str, int id)
{
	int index;

	if (str[0] == '\0')
	{
		dll_node* dll = (dll_node*) malloc(sizeof(dll_node));
		dll->id = id;
		dll->next = head->dll;
		head->dll = dll;
		return;
	}
	if (str[0] == '@')
	{
		index = STRING_TRIE;
	}
	else if (str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';
	}
	if (head->shash[index])
		insert_str_trie(head->shash[index], str + 1, id);
	else
	{
		head->shash[index] = (str_trie *)malloc(sizeof(str_trie));
		head->shash[index]->dll = NULL;
		for (int i = 0; i < STRING_TRIE; i++)
			head->shash[index]->shash[i] = NULL;
		insert_str_trie(head->shash[index], str + 1, id);
	}
}

void delete_str_trie_id(str_trie *head, char *str, int id)
{
	int index, local_id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll, *prev;
		while (sdll)
		{
			local_id = sdll->id;
			if (list[local_id].id == id)
			{
				/*if (head->dll == sdll)
					head->dll = sdll->next;
				else
					prev->next = sdll->next;
				free(sdll);*/
				sdll->id = 0;
				return;
			}
			prev = sdll;
			sdll = sdll->next;
		};
		return;
	}

	if (str[0] == '@')
	{
		index = STRING_TRIE;
	}
	else if (str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';
	}
	if (head->shash[index])
		delete_str_trie_id(head->shash[index], str + 1, id);
}


void delete_str_trie(str_trie *head, char *str)
{
	int index, id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll, *prev;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				delete_count++;
				list[id].id = 0;
			}
			prev = sdll;
			sdll = sdll->next;
			free(prev);
		};
		head->dll = NULL;
		return;
	}

	if (str[0] == '@')
	{
		index = STRING_TRIE;
	}
	else if (str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';
	}
	if (head->shash[index])
		delete_str_trie(head->shash[index], str + 1);
}

void delete_num_trie_id(num_trie *head, char *str, int id)
{
	int index, local_id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll, *prev;
		while (sdll)
		{
			local_id = sdll->id;
			if (list[local_id].id == id)
			{
				/*prev->next = sdll->next;
				free(sdll);*/
				sdll->id = 0;
				return;
			}			
			sdll = sdll->next;
		};		
		return;
	}

	if (str[0] >= '0' && str[0] <= '9')
		index = str[0] - '0';

	if (head->nhash[index])
		delete_num_trie_id(head->nhash[index], str + 1, id);
}

void delete_num_trie(num_trie *head, char *str)
{
	int index, id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll, *prev;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				delete_count++;
				list[id].id = 0;
			}
			prev = sdll;
			sdll = sdll->next;
			free(prev);
		};
		head->dll = NULL;
		return;
	}

	if (str[0] >= '0' && str[0] <= '9')
		index = str[0] - '0';

	if (head->nhash[index])
		delete_num_trie(head->nhash[index], str + 1);
}

void insert_num_trie(num_trie *head, char *str, int id)
{
	int index;

	if (str[0] == '\0')
	{
		dll_node* dll = (dll_node*)malloc(sizeof(dll_node));
		dll->id = id;
		dll->next = head->dll;
		head->dll = dll;
		return;
	}
	else if (str[0] >= '0' && str[0] <= '9')
	{
		index = str[0] - '0';
	}
	if (head->nhash[index])
		insert_num_trie(head->nhash[index], str + 1, id);
	else
	{
		head->nhash[index] = (num_trie *)malloc(sizeof(num_trie));
		head->nhash[index]->dll = NULL;
		for (int i = 0; i < MAX_NUM; i++)
			head->nhash[index]->nhash[i] = NULL;
		insert_num_trie(head->nhash[index], str + 1, id);
	}
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	count++;

	//printf ("[%d, %s, %s, %s, %s, %s]\n", count, name, number, birthday, email, memo);
	list[count].id = count;
	sprintf(list[count].name, name);
	sprintf(list[count].number, number);
	sprintf(list[count].birthday, birthday);
	sprintf(list[count].email, email);
	sprintf(list[count].memo, memo);

	if (number[0] == '0' && number[1] == '1' && number[0] == '0')
		number = number + 3;
	if (birthday[0] == '1' && birthday[1] == '9')
		birthday = birthday + 2;

	list[count].email_length = mystrlen(email);
	list[count].email_length -= EMAILCNT;
	email[list[count].email_length] = '\0';

	insert_str_trie(tname, name, count);
	insert_str_trie(temail, email, count);
	insert_str_trie(tmemo, memo, count);

	insert_num_trie(tnumber, number, count);
	insert_num_trie(tbirthday, birthday, count);
}
int Delete(FIELD field, char* str)
{
	int i;
	//printf ("Delete [%d, %s]\n", field, str);
	delete_count = 0;
	switch (field)
	{
	case NAME:
		delete_str_trie(tname, str);
		break;
	case NUMBER:
		if (str[0] == '0' && str[1] == '1' && str[0] == '0')
			str = str + 3;
		delete_num_trie(tnumber, str);
		break;
	case BIRTHDAY:
		if (str[0] == '1' && str[1] == '9')
			str = str + 2;
		delete_num_trie(tbirthday, str);
		break;
	case EMAIL:
		i = mystrlen(str);
		str[i - EMAILCNT] = '\0';
		delete_str_trie(temail, str);
		break;
	case MEMO:
		delete_str_trie(tmemo, str);
		break;
	}
	return delete_count;
}

void change_str_trie(str_trie *head, char *str, FIELD changefield, char* changestr)
{
	int index, id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				change_count++;
				switch (changefield)
				{
				case NAME:
					delete_str_trie_id(tname, list[id].name, id);
					sprintf(list[id].name, changestr);
					insert_str_trie(tname, changestr, id);
					break;
				case NUMBER:
					//if (str[0] == '0' && str[1] == '1' && str[0] == '0')
					//	str = str + 3;
					delete_num_trie_id(tnumber, list[id].number + 3, id);
					sprintf(list[id].number, changestr);
					insert_num_trie(tnumber, changestr+3, id);
					break;
				case BIRTHDAY:
					if (str[0] == '1' && str[1] == '9')
						str = str + 2;
					delete_num_trie_id(tbirthday, list[id].birthday + 2, id);
					sprintf(list[id].birthday, changestr);
					insert_num_trie(tbirthday, changestr + 2, id);
					break;
				case EMAIL:
					
					list[id].email[list[id].email_length] = '\0';
					delete_str_trie_id(temail, list[id].email, id);
					sprintf(list[id].email, changestr);
					list[id].email_length = mystrlen(changestr);
					list[id].email_length -= EMAILCNT;
					changestr[list[id].email_length] = '\0';
					insert_str_trie(temail, changestr, id);
					sprintf(changestr, list[id].email);//Reset back for next linklist node
					break;
				case MEMO:
					delete_str_trie_id(tmemo, list[id].memo, id);
					sprintf(list[id].memo, changestr);
					insert_str_trie(tmemo, changestr, id);
					break;
				}
			}
			sdll = sdll->next;
		}
		return;
	}
	if (str[0] == '@')
	{
		index = STRING_TRIE;
	}
	else if (str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';
	}
	if (head->shash[index])
		change_str_trie(head->shash[index], str + 1, changefield, changestr);
}

void change_num_trie(num_trie *head, char *str, FIELD changefield, char* changestr)
{
	int index, id;

	if (str[0] == '\0')
	{		
		dll_node* sdll = head->dll;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				change_count++;
				switch (changefield)
				{
				case NAME:
					delete_str_trie_id(tname, list[id].name, id);
					sprintf(list[id].name, changestr);
					insert_str_trie(tname, changestr, id);
					break;
				case NUMBER:
					//if (str[0] == '0' && str[1] == '1' && str[2] == '0')
					//	str = str + 3;
					delete_num_trie_id(tnumber, list[id].number+3, id);
					sprintf(list[id].number, changestr);
					insert_num_trie(tnumber, changestr+3, id);
					break;
				case BIRTHDAY:
					if (str[0] == '1' && str[1] == '9')
						str = str + 2;
					delete_num_trie_id(tbirthday, list[id].birthday + 2, id);
					sprintf(list[id].birthday, changestr);
					insert_num_trie(tbirthday, changestr+2, id);
					break;
				case EMAIL:					
					list[id].email[list[id].email_length] = '\0';
					delete_str_trie_id(temail, list[id].email, id);					
					sprintf(list[id].email, changestr);
					list[id].email_length = mystrlen(changestr);
					list[id].email_length -= EMAILCNT;
					changestr[list[id].email_length] = '\0';
					insert_str_trie(temail, changestr, id);
					sprintf(changestr, list[id].email);//Reset back for next linklist node
					break;
				case MEMO:
					delete_str_trie_id(tmemo, list[id].memo, id);
					sprintf(list[id].memo, changestr);
					insert_str_trie(tmemo, changestr, id);
					break;
				}
			}
			sdll = sdll->next;
		};		
		return;
	}
	else if (str[0] >= '0' && str[0] <= '9')
	{
		index = str[0] - '0';
	}
	if (head->nhash[index])
		change_num_trie(head->nhash[index], str + 1, changefield, changestr);
}
int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int i;
	change_count = 0;
	//printf ("Change [%d, %s, %d, %s]\n", field, str, changefield, changestr);

	switch (field)
	{
	case NAME:
		change_str_trie(tname, str ,changefield, changestr);
		break;
	case NUMBER:
		if (str[0] == '0' && str[1] == '1' && str[2] == '0')
			str = str + 3;
		change_num_trie(tnumber, str, changefield, changestr);
		break;
	case BIRTHDAY:
		if (str[0] == '1' && str[1] == '9')
			str = str + 2;
		change_num_trie(tbirthday, str, changefield, changestr);
		break;
	case EMAIL:
		i = mystrlen(str);
		str[i - EMAILCNT] = '\0';
		change_str_trie(temail, str, changefield, changestr);
		break;
	case MEMO:
		change_str_trie(tmemo, str, changefield, changestr);
		break;
	}
	return change_count;
}

int search_count, search_id;

void search_str_trie(str_trie *head, char *str)
{
	int index, id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				search_count++;
				search_id = id;
			}
			sdll = sdll->next;
		}
		return;
	}
	if (str[0] == '@')
	{
		index = STRING_TRIE;
	}
	else if (str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';
	}
	if (head->shash[index])
		search_str_trie(head->shash[index], str + 1);
}

void search_num_trie(num_trie *head, char *str)
{
	int index, id;

	if (str[0] == '\0')
	{
		dll_node* sdll = head->dll;
		while (sdll)
		{
			id = sdll->id;
			if (list[id].id)
			{
				search_count++;
				search_id = id;
			}
			sdll = sdll->next;
		}
		return;
	}
	else if (str[0] >= '0' && str[0] <= '9')
	{
		index = str[0] - '0';
	}
	if (head->nhash[index])
		search_num_trie(head->nhash[index], str + 1);
}
typedef struct
{
	int count;
	char str[20];
} RESULT;
RESULT Search(FIELD field, char* str, FIELD returnfield)
{
	int i;
	RESULT r;
	//printf ("Search [%d, %s]\n", field, str);
	search_count = search_id  = 0;
	switch (field)
	{
	case NAME:
		search_str_trie(tname, str);
		break;
	case NUMBER:
		if (str[0] == '0' && str[1] == '1' && str[2] == '0')
			str = str + 3;
		search_num_trie(tnumber, str);
		break;
	case BIRTHDAY:
		if (str[0] == '1' && str[1] == '9')
			str = str + 2;
		search_num_trie(tbirthday, str);
		break;
	case EMAIL:
		i = mystrlen(str);
		str[i - EMAILCNT] = '\0';
		search_str_trie(temail, str);
		break;
	case MEMO:
		search_str_trie(tmemo, str);
		break;
	}
	r.count = search_count;
	if (search_count > 1)
		r.str[0] = '\0';
	else
	{
		switch (returnfield)
		{
		case NAME:
			sprintf(r.str, list[search_id].name);			
			break;
		case NUMBER:
			sprintf(r.str, list[search_id].number);
			break;
		case BIRTHDAY:
			sprintf(r.str, list[search_id].birthday);
			break;
		case EMAIL:
			sprintf(r.str, list[search_id].email);
			break;
		case MEMO:
			sprintf(r.str, list[search_id].memo);
			break;			
		}
	}
	//printf ("%d %s\n", r.count, r.str);
	return r;

}
