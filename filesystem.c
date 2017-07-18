#include <stdlib.h>
#define MAX_CHILD 200
#define MAX_NODES 10000
#define D_DIR 1
#define D_FILE 0


typedef struct node
{
	int id;
	struct node* pid;
	struct node* cid[MAX_CHILD];
	int cid_count;

	int file_or_dir;
	int is_infected;
	int size;
	int orig_size;
}node;

int count;
int filecount;
int size;

node *list = NULL;

void init(void)
{
	count = 0;
	size = 0;
	filecount = 0;

	if (list == NULL)
		list = (node*)malloc(MAX_NODES * sizeof(node));

	list[count].id = 10000;
	list[count].cid_count = 0;
	list[count].file_or_dir = D_DIR;
	list[count].is_infected = 0;
	list[count].pid = NULL;
	list[count].size = 0;

	count++;
}

int find(int id)
{
	int i = 0;

	while (list[i].id != id && i < count)
		i++;

	return i;
}

void dump(int id, int depth)
{
	return;//INTENTIONAL
}


void update_parent (node *n, int size)
{
	node* parent = n->pid;
	while (parent)
	{
		parent->size += size;
		parent = parent->pid;
	}
}

int add(int id, int pid, int fileSize)
{

	//printf (" ADD pid %d id %d size %d\n", pid, id, fileSize);
	node* parent = &list[find(pid)];
	node* child = &list[count++];
	size += fileSize;

	parent->cid[parent->cid_count++] = child;

	child->id = id;
	child->pid = parent;
	child->size = fileSize;
	child->orig_size = fileSize;
	child->cid_count = 0;

	child->file_or_dir = !fileSize;
	if (child->file_or_dir == D_FILE)
		filecount++;
	child->is_infected = 0;

	update_parent (child, fileSize);

	dump(10000, 0);

	return parent->size;
}

int move(int id, int pid)
{
	//printf (" Move new pid %d id %d \n", pid, id);
	int i;

	node* child = &list[find(id)];
	node* new_parent = &list[find(pid)];
	node* old_parent = child->pid;

	update_parent (child, child->size * -1);

	//remove from old parent list
	for (i = 0; i < old_parent->cid_count; i++)
	{
		if (old_parent->cid[i]->id == id)
			break;
	}

	if (i + 1 != old_parent->cid_count) //not last child
		old_parent->cid[i] = old_parent->cid[old_parent->cid_count - 1];
	old_parent->cid_count--;

	//Add in new parent list
	new_parent->cid[new_parent->cid_count++] = child;
	new_parent = &list[find(pid)];

	//update parent
	child->pid = new_parent;
	update_parent (child, child->size);

	dump(10000, 0);
	return new_parent->size;
}

int infected;
void rec_infect(node *n)
{
	//printf (" Rec Infect %d \n", id);

	if (n->file_or_dir == D_FILE)
	{
		n->is_infected = 1;
		n->size += size / filecount;
		infected += size / filecount;
		update_parent (n, size/filecount);

		return;
	}
	else
	{
		for (int i = 0; i < n->cid_count; i++)
		{
			node* child = n->cid[i];

			child->is_infected = 1;

			if (child->file_or_dir == D_DIR)
				rec_infect(child);
			else
			{
				child->size += size / filecount;
				infected += size / filecount;
				update_parent (child, size/filecount);
			}
		}
		return;
	}
}

int infect(int id)
{
	node* n = &list[find(id)];
	if (filecount)
	{
		//	printf (" Infect %d size %d\n", id, size/filecount);
		infected = 0;
		rec_infect(n);
		size += infected;
		dump(10000, 0);
	}
	return n->size;
}

void rec_recover(node *n)
{
	//printf ("Rec Recover %d \n", id);
	//node* n = &list[find(id)];

	if (n->file_or_dir == D_FILE)
	{
		n->is_infected = 0;
		infected += n->size - n->orig_size;
		update_parent (n, (n->size - n->orig_size) * -1);
		n->size = n->orig_size;
		return;
	}
	else
	{
		for (int i = 0; i < n->cid_count; i++)
		{
			node* child = n->cid[i];

			child->is_infected = 0;

			if (child->file_or_dir == D_DIR)
				rec_recover(child);
			else
			{
				infected += child->size - child->orig_size;
				update_parent (child, (child->size - child->orig_size) * -1);
				child->size = child->orig_size;
			}
		}
		return;
	}
}

int recover(int id)
{
	//	printf (" Recover %d \n", id);
	node* n = &list[find(id)];
	infected = 0;
	rec_recover(n);
	dump(10000, 0);
	size -= infected;
	return n->size;
}

void rec_remove(node *n)
{
	//	printf ("Rec Remove %d \n", id);
	n->id = -1;

	if (n->file_or_dir == D_FILE)
	{
		infected += n->size;
		update_parent (n, n->size  * -1);
		filecount--;
		return;
	}
	else
	{
		for (int i = 0; i < n->cid_count; i++)
		{
			node* child = n->cid[i];

			child->is_infected = 0;

			if (child->file_or_dir == D_DIR)
			{
				rec_remove(child);
			}
			else
			{
				infected += child->size;
				update_parent (child, child->size  * -1);
				filecount--;
			}
			child->id = -1;
		}
		n->cid_count = 0;
		return;
	}
}


int fremove(int id)
{
	//	printf (" Remove %d \n", id);
	int i, ret;
	node* child = &list[find(id)];
	node* parent = child->pid;

	ret = child->size;

	//remove from old parent list
	for (i = 0; i < parent->cid_count; i++)
	{
		if (parent->cid[i]->id == id)
			break;
	}

	if (i + 1 != parent->cid_count) //not last child
		parent->cid[i] = parent->cid[parent->cid_count - 1];
	parent->cid_count--;

	if (child->file_or_dir == D_FILE)
	{
		filecount--;
		size -= child->size;
		update_parent (child, child->size  * -1);
	}
	else
	{
		infected = 0;
		rec_remove(child);
		size -= infected;
	}

	child->id = -1;

	dump(10000, 0);
	return ret;
}
