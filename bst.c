#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
	Node *root = make_node(50, "John");

	root = add_node(root, 25, "Jake");
	root = add_node(root, 75, "Susan");
	root = add_node(root, 35, "Debbie");

	print_tree(root, 0);

	printf("Finding ID 75... ");
	Node *found = search_tree(root, 75);
	printf("%s\n", found->name);

	printf("Finding ID 35... ");
	Node *found2 = search_tree(root, 35);
	printf("%s\n", found2->name);
	return 0;
}

/**
 * Create a node.
 */
Node *make_node(int value, char *name) {
	Node *node = malloc(sizeof(Node));
	node->id = value;
	node->name = name;
	node->lchild = NULL;
	return node;
}

/**
 * Add a node to the tree.
 */
Node *add_node(Node *node, int id, char *name) {
	if (node == NULL) {
		return make_node(id, name);
	} else {
		if (id < node->id) node->lchild = add_node(node->lchild, id, name);
		else if (id > node->id) node->rchild = add_node(node->rchild, id, name);
	}

	return node;
}

/**
 * Find a node by id.
 */
Node *search_tree(Node *root, int id) {
	if (id == root->id) return root;
	else if (id > root->id) return search_tree(root->rchild, id);
	else if (id < root->id) return search_tree(root->lchild, id);
	else return NULL;
}

/**
 * Print a tree. Code taken from http://www.daniweb.com/software-development/c/threads/146112/printing-a-binary-tree
 * because I didn't want to bother writing it.
 */
void print_tree(Node *root, int level) {
	int i;
	if (root == NULL) {
		_print_tree_padding('\t', level);
		puts("   ~");
	}
	else {
		print_tree(root->rchild, level + 1);
		_print_tree_padding('\t', level);
		printf("[%d] %s\n", root->id, root->name);
		print_tree(root->lchild, level + 1);
	}
}

void _print_tree_padding(char ch, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		putchar(ch);
	}
}