#ifndef _LIST_H

typedef enum {
	list_type_string
} ListType;

/**
 * Nodes for a doubly-linked list.
 */
typedef struct Node {
	void *data;
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
	ListType type;
} List;


List *new_list(ListType);
void list_push(List*, void*);
void list_append(List*, void*);
int list_length(List*);
void *list_get(List*, int);
int list_pop(List*, void**);
void list_remove(List*, Node*);
void list_print(List*);
void list_delete(List*);
#define _LIST_H
#endif