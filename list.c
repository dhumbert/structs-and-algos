#include <stdio.h>
#include <stdlib.h>
#include <string.h> // only for main() debugging
#include "list.h"

int main() {
	List *list = new_list(list_type_string);
	char *val1 = "Hello";
	char *val2 = "World!";

	int val1len = strlen(val1);
	char *valPtr1 = malloc(val1len + 1);
	memcpy(valPtr1, val1, val1len);

	int val2len = strlen(val2);
	char *valPtr2 = malloc(val2len + 1);
	memcpy(valPtr2, val2, val2len);

	list_push(list, valPtr1);
	list_append(list, valPtr2);
	
	list_print(list);

	printf("List length is %d\n", list_length(list));
	char *value0 = (char*) list_get(list, 0);
	char *value1 = (char*) list_get(list, 1);
	printf("Value at index 0 is: %s\n", value0);
	printf("Value at index 1 is: %s\n", value1);

	void *popped;
	int poppedSuccesfully = list_pop(list, &popped);
	while (poppedSuccesfully) {
		printf("Popped: %s\n", (char*) popped);
		//free(popped);
		printf("List length is %d\n", list_length(list));
		poppedSuccesfully = list_pop(list, &popped);
	}

	list_push(list, valPtr1);
	list_append(list, valPtr2);

	printf("Deleting the list...\n");
	list_delete(list);

	list_print(list);

	return 0;
}

/**
 * Allocate and initialize a new list.
 */
List *new_list(ListType type) {
	List *list = malloc(sizeof(List));
	list->head = NULL;
	list->last = NULL;
	list->length = 0;
	list->type = type;
	return list;
}

/**
 * Push a value onto the front of a list.
 */
void list_push(List *list, void *data) {
	Node *node = malloc(sizeof(Node));
	node->data = data;
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
void list_append(List *list, void *data) {
	Node *node = malloc(sizeof(Node));
	node->data = data;
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
 * Access list elements by index, like an array.
 */
void *list_get(List* list, int idx) {
	if (list == NULL || list_length(list) == 0) {
		return NULL;
	} else {
		int i = 0;
		Node *current = list->head;
		while (current != NULL) {
			if (i == idx) {
				return current->data;
			}

			current = current->next;
			i++;
		}
	}

	return NULL;
}

/**
 * Pop a value off the front of a list.
 */ 
int list_pop(List *list, void **data) {
	if (list->head == NULL) {
		return 0;
	} else {
		*data = list->head->data;
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

void list_delete(List *list) {
	if (list == NULL) {
		return;
	}

	if (list_length(list) > 0) {
		Node *current, *next;
		current = list->head;
		while (current != NULL) {
			next = current->next;

			if (current->data != NULL) {
				free(current->data);
				current->data = NULL;
			}

			free(current);
			list->length--;
			current = next;
		}
	}
}

/**
 * Print a list. For debugging purposes.
 */
void list_print(List *list) {
	if (list == NULL) {
		printf("Null list!\n");
		return;
	} else if (list_length(list) == 0) {
		printf("Empty list!\n");
		return;
	}

	Node *current = list->head;
	Node *last = NULL;

	printf("Forwards...\n");
	int i = 1;
	while (current != NULL) {
		printf("%d. %s\n", i, (char*) current->data);
		last = current;
		current = current->next;
		i++;
	}

	printf("... and backwards\n");
	int j = 1;
	Node *currentBackwards = last;
	while (currentBackwards != NULL) {
		printf("%d. %s\n", j, (char*) currentBackwards->data);
		currentBackwards = currentBackwards->prev;
		j++;
	}
}