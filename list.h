#ifndef _LIST_H
/**
 * Nodes for a doubly-linked list.
 */
typedef struct Node {
	int value;
	struct Node *prev;
	struct Node *next;
} Node;

/**
 * Data type to abstract a list.
 */
typedef struct List {
	Node *head;
	Node *last;
	int length;
} List;


List *new_list();
void list_push(List*, const int);
void list_append(List*, const int);
int list_length(List*);
int list_head(List*);
int list_pop(List*, int*);
void list_remove(List*, Node*);
void list_print(List*);
#define _LIST_H
#endif