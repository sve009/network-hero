#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "cybers.h"
#include "conv.h"

// Function for listening to clients
void* listen_client(void* sock_fd) {
    // Buffer for reading action
    char buffer[2000];

    // Action to pass into parser
    action_t* a = malloc(sizeof(action_t));

    // Grab the socket fd
    int fd = *(int*)sock_fd;

    // Wait to receive action
    read(fd, buffer, 2000);

    // Get the action
    parse_action(a, buffer);
    
    return (void*)a;
}


int main(int argc, char** args) {
    // Create socket
    int connect_sock;

    connect_sock = socket(AF_INET, SOCK_STREAM, 0);

    // Error check
    if (connect_sock < 0) {
        perror("Creating socket failed");
        exit(2);
    }

    // Create socket descriptor
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8008);

    // Bind socket
    if (bind(connect_sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Binding socket failed");
        exit(2);
    }

    // Listen on socket
    listen(connect_sock, 0);

    // Store clients
    int clients[2];
    int num_clients = 0;
    struct sockaddr_in client_info[2];

    int c = sizeof(struct sockaddr_in);

    // Accept connections
    while (num_clients < 2) {
        clients[num_clients] = accept(connect_sock, (struct sockaddr*) &client_info[num_clients], (socklen_t*)&c);
        if (clients[num_clients++] < 0) {
            perror("Accepting connection failed");
            exit(2);
        }
        printf("Connected!\n");
    }

    // Spawn threads to listen to connections
    pthread_t threads[2];

    // Get two actions every turn
    action_t* actions[2];

    // Main game loop
    while (1) {
        // Spawn threads to listen for actions
        for (int i = 0; i < 2; i++) {
            // Create thread
            pthread_create(&threads[i], NULL, listen_client, (void*)&clients[i]);

            // Error check
            if (threads[i] == NULL) {
                perror("Thread creation failed");
                exit(2);
            }
        }

        // Get actions
        for (int i = 0; i < 2; i++) {
            // Join threads
            int r = pthread_join(threads[i], (void*)&actions[i]);

            // Error check
            if (r != 0) {
                perror("Join threads failed");
                exit(2);
            }
        }

        // We should now have both actions, put game math here
    }
    return 0;
}

