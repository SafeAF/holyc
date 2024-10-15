// node structure header file
// ll.h
#ifndef LL_H
#define LL_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function prototypes
void insert_at_end(Node **head, int data);
Node* search(Node **head, int target);
void delete(Node **head, int target);
void print_list(Node **head);

#endif