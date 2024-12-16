// binary tree test
// 12/01/20

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

Node* insert(Node *root, int data){

	if(root == NULL){
		return create_node(data);
	}

	if(data < root->data){
		root->left = insert(root->left, data);
	} else if (data > root->data) {
		root->right = insert(root->right, data);
	}
	return root;
}

void in_order_traversal(Node *root){
	if(root == NULL){
		return;
	}

	in_order_traversal(root->left);
	printf("%d ", root->data);
	in_order_traversal(root->right);
}



int main(void){
	Node *root = NULL;

	root = insert(root, 10);
	root = insert(root, 15);
	root = insert(root, 8);
	root = insert(root, 7);
	root = insert(root, 6);
	
	root = insert(root, 9);
	

	root = insert(root, 14);
	root = insert(root, 20);	

	in_order_traversal(root);
}