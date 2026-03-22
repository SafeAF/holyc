#include <stdio.h>
#include <stdlib.h>


typedef Node {
    int data;
    struct Node next;
} Node;

Node* create_node(int data){
    Node *temp = malloc(sizeof(Node));

    if(!temp){
        perror("Failed to create node");
        exit(1);
    }
    temp->data = data;
    temp->next = NULL;

    return temp;
}

void insert(Node **head, int data){
    Node new_node = create_node(data);

    // error check

    Node *temp = *head;
    
    while(temp->next != NULL){
        temp = temp->next;
    }
  
    temp->next = new_node;
    
}

int main(void){

    Node *list = NULL;
    insert(&list, 10);


    return 0;
}

