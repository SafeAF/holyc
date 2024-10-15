// simple data structure server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "node.h"

#define PORT 8081
#define BUFFER_SIZE 1024



// globally defined linked list
Node *head = NULL;

void handle_request(const char *request, char *response);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        printf("Waiting for a connection...\n");

        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Read the HTTP request
        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received request:\n%s\n", buffer);

        // Parse and handle the request
        char response[BUFFER_SIZE] = {0};
        handle_request(buffer, response);

        // Send the HTTP response
        write(new_socket, response, strlen(response));
        printf("Response sent\n");

        // Close the connection
        close(new_socket);
    }

    return 0;
}

void handle_request(const char *request, char *response) {
    char operation[16];
    int value;
    
    // Parse the request to extract the operation and value
    if (sscanf(request, "%15[^:]:%d", operation, &value) == 2) {
        if (strcmp(operation, "insert") == 0) {
            insert_at_end(&head, value);
            snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nInserted %d into the list.", value);
        } else if (strcmp(operation, "search") == 0) {
            Node *result = search(&head, value);
            if (result) {
                snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFound %d in the list.", value);
            } else {
                snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%d not found in the list.", value);
            }
        } else if (strcmp(operation, "delete") == 0) {
            delete(&head, value);
            snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nDeleted %d from the list.", value);
        } else {
            snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nUnknown operation.");
        }
    } else if (strcmp(request, "print") == 0) {
        // Handle the print operation
        char list_contents[BUFFER_SIZE] = {0};
        Node *current = head;
        while (current) {
            char temp[32];
            snprintf(temp, sizeof(temp), "%d ", current->data);
            strcat(list_contents, temp);
            current = current->next;
        }
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nList: %s", list_contents);
    } else {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nInvalid request.");
    }
}
