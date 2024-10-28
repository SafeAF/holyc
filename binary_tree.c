// binary tree

#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));

	if(new_node == NULL){
		return NULL;
	}

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
	}
	else if(data > root->data){
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

// In-order traversal that stores values in an array
void in_order_traversal_returned(Node *root, int* arr, int* index) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    in_order_traversal(root->left, arr, index);

    // Store the current node's data in the array
    arr[*index] = root->data;
    (*index)++;  // Increment the index for the next element

    // Traverse the right subtree
    in_order_traversal(root->right, arr, index);
}

int count_nodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Function to create an array large enough to hold the in-order traversal
int* in_order_to_array(Node* root, int num_nodes) {
    // Allocate memory for an array to hold the traversal (size based on number of nodes)
    int* arr = (int*)malloc(sizeof(int) * num_nodes);

    // Initialize an index to track the current position in the array
    int index = 0;

    // Perform in-order traversal and store the values in the array
    in_order_traversal(root, arr, &index);

    return arr;  // Return the array containing the in-order traversal
}


int main(){
    // Create a simple binary search tree
    Node* root = create_node(50);
    root->left = create_node(30);
    root->right = create_node(70);
    root->left->left = create_node(20);
    root->left->right = create_node(40);
    root->right->left = create_node(60);
    root->right->right = create_node(80);

    // Count the number of nodes in the tree
    int num_nodes = count_nodes(root);

    // Get the in-order traversal as an array
    int* arr = in_order_to_array(root, num_nodes);

    // Print the in-order traversal stored in the array
    printf("In-order traversal: ");
    for (int i = 0; i < num_nodes; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated array
    free(arr);
	return 0;	
}