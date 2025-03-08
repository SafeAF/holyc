// bintree test 1/4/25

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
} Node;


Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));
	// check if allocated

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

Node* insert(Node* root, int data){
	// check if root is NULL then its the first element set root to new_node
	if(root == NULL){
	 	return create_node(data);
	}

	if(data < root->data){
		root->left = insert(root->left, data);
	}
	else if(data > root->data){
		root->right = insert(root->right, data);
	}

	return root;
}

int search(Node* root, int target){
	if(root == NULL){
		return 0; // value not found
	}

	if(target == root->data){
		return 0;
	}
	else if(target < root->data){
		return search(root->left, target);
	}
	else{
		return search(root->right, target);
	}	
	
}







int main(){
	Node *tree = NULL;

	insert(tree, 10);
	insert(tree, 50);
	insert(tree, 70);
}