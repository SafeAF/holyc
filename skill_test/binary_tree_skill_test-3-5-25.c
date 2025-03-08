// bin tree 3-5-25 skill test

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	int value;
	struct Node *left;
	struct Node *right;
} Node;

Node* create_node(int value){
	Node *new_node = malloc(sizeof(Node));
	if(!new_node){
		exit(1);
	}

	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Node* insert(Node *root, int value){
	if(root == NULL){
		return create_node(value);
	}
	
	if(value < root->value){
		root->left = insert(root->left, value);
	}
	else if(value > root->value) {
		root->right = insert(root->right, value);
	}
	return root;
}



int main(){
	Node *root = create_node(20);
	insert(root, 10);
}
