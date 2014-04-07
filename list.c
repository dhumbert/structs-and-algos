#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
	List *list = new_list();
	list_push(list, 1);
	list_append(list, 2);
	list_push(list, 3);
	list_append(list, 4);
	list_push(list, 5);
	list_append(list, 6);
	
	list_print(list);

	printf("List length is %d\n", list_length(list));
	int headvalue = list_head(list);
	printf("Head is: %d\n", headvalue);

	int popped;
	int poppedSuccesfully = list_pop(list, &popped);
	while (poppedSuccesfully) {
		printf("Popped: %d\n", popped);
		printf("List length is %d\n", list_length(list));
		poppedSuccesfully = list_pop(list, &popped);
	}

	return 0;
}

/**
 * Allocate and initialize a new list.
 */
List *new_list() {
	List *list = malloc(sizeof(List));
	list->head = NULL;
	list->last = NULL;
	list->length = 0;
	return list;
}

/**
 * Push a value onto the front of a list.
 */
void list_push(List *list, const int value) {
	Node *node = malloc(sizeof(Node));
	node->value = value;
	node->prev = NULL;
	node->next = list->head;
	
	if (list->head != NULL) {
		list->head->prev = node;
	}

	if (list->last == NULL) {
		list->last = node;
	}

	list->head = node;
	list->length++;
}

/**
 * Append a value to the back of a list.
 */
void list_append(List *list, const int value) {
	Node *node = malloc(sizeof(Node));
	node->value = value;
	node->prev = list->last;

	if (list->head == NULL) {
		list->head = node;
	}

	if (list->last != NULL) {
		list->last->next = node;
	}

	node->next = NULL;
	list->last = node;
	list->length++;
}

/**
 * Get the length of a list.
 */
int list_length(List *list) {
	return list->length;
}

/**
 * Get the first value of a list.
 */
int list_head(List* list) {
	if (list->head != NULL) {
		return list->head->value;
	} else {
		return -1;
	}
}

/**
 * Pop a value of the front of a list.
 */ 
int list_pop(List *list, int *value) {
	if (list->head == NULL) {
		return 0;
	} else {
		*value = list->head->value;
		list_remove(list, list->head);
		return 1;
	}
}

/**
 * Remove a node from a list.
 */
void list_remove(List *list, Node *node) {
	if (node == list->head && node == list->last) {
		list->head = NULL;
		list->last = NULL;
	} else if (node == list->head) {
		list->head = node->next;
		list->head->prev = NULL;
	} else if (node == list->last) {
		list->last = node->prev;
		list->last->next = NULL;
	} else {
		Node *after = node->next;
		Node *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	free(node);
	list->length--;
}

/**
 * Print a list. For debugging purposes.
 */
void list_print(List *list) {
	Node *current = list->head;
	Node *last = NULL;

	printf("Forwards...\n");
	int i = 1;
	while (current != NULL) {
		printf("%d. %d\n", i, current->value);
		last = current;
		current = current->next;
		i++;
	}

	printf("... and backwards\n");
	int j = 1;
	Node *currentBackwards = last;
	while (currentBackwards != NULL) {
		printf("%d. %d\n", j, currentBackwards->value);
		currentBackwards = currentBackwards->prev;
		j++;
	}
}