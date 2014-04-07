#ifndef _BST_H
#define _BST_H

typedef struct Node {
	int id;
	char *name;
	struct Node *lchild;
	struct Node *rchild;
} Node;

Node *make_node(int, char*);
Node *add_node(Node*, int, char*);
Node *search_tree(Node*, int);
void print_tree(Node*, int);
void _print_tree_padding(char, int);

#endif