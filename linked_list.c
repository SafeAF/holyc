#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_end(Node **head, int data) {
    Node *new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("Data: %d\n", temp->data);
        temp = temp->next;
    }
}

Node* search(Node *head, int target) {
    Node *temp = head;
    while (temp != NULL && temp->data != target) {
        temp = temp->next;
    }
    return temp;
}

void delete_node(Node **head, int target) {
    if (*head == NULL) return;

    Node *temp = *head;
    Node *prev = NULL;

    // If the target is in the head node
    if (temp != NULL && temp->data == target) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Search for the node to delete
    while (temp != NULL && temp->data != target) {
        prev = temp;
        temp = temp->next;
    }

    // If target not found
    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *list = NULL;

    insert_at_end(&list, 10);
    insert_at_end(&list, 20);
    insert_at_end(&list, 30);

    printf("Initial list:\n");
    print_list(list);

    int target = 30;
    Node *result = search(list, target);
    if (result != NULL) {
        printf("Found target %d\n", target);
    } else {
        printf("Target %d not found\n", target);
    }

    printf("\nDeleting %d...\n", target);
    delete_node(&list, target);

    printf("List after deletion:\n");
    print_list(list);

    free_list(list);
    return 0;
}
