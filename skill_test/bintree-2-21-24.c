// bin tree skill test

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node* create_node(int data){
	Node* new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

Node* insert(Node* root, int data){
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

void inorderIterative(Node* root){
	Node *stack[100];
	int top = -1; 
	Node *current = root; // temp variable

	while(current != NULL || top != -1){
		while(current != NULL){
			stack[++top] = current;
			current = current->left;
		}
		current = stack[top--];
		printf("%d ", current->data);

		current = current->right;
	}

}




int main(void){
	Node* tree = NULL;
	tree = insert(tree, 6);
	tree = insert(tree, 12);
	tree = insert(tree, 3);

	inorderIterative(tree);

	
}