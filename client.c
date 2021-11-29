#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "cybers.h"

// Include global option output based on menu level here
char* options1[] = {"use move\n", "swap cyber\n", "guard\n"};

// Print a cyber
void print_cyber(cyber_t* cyber) {
    printf("%s: %d | %s\n", cyber->name, cyber->health, elements[cyber->element]);
}

// Connect to server
void server_connect(int* serv_sock, struct sockaddr_in* info) {
    // Create socket
    *serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    // Error check
    if (*serv_sock < 0) {
        perror("Creating socket failed");
        exit(2);
    }

    // Connect to server using info
    if (connect(*serv_sock, (struct sockaddr*)info, sizeof(*info)) < 0) {
        perror("Failed to connect to server");
        exit(2);
    }
}


// Main function (crazy)
int main(int argc, char** args) {
    // Handle arguments
    if (argc != 3) {
        printf("USAGE: ./client [SERVER] [PORT]\n");
        exit(0);
    }

    // Declare connection variables
    int serv_sock;
    struct sockaddr_in server;

    // Set properties
    server.sin_addr.s_addr = inet_addr(args[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(8008); // Temp, read from args eventually

    // Connect to server
    server_connect(&serv_sock, &server);

    // Menu selector, keeps track of what menu we're in
    int menu = 0;

    // Buffer for user input
    char* buffer = NULL; // input buffer
    size_t len = 0;         // len of input

    game_t* state = NULL;

    // Loop forever
    while (true) {
        // Add prompt
        if (menu == 0) {
            printf("Choose an action:\n");
        } else if (menu == 1) {
            printf("Choose a move:\n");
        } else if (menu == 2) {
            printf("Choose a cyber to swap in:\n");
        }
        printf("> ");
        fflush(stdout);

        // Get line, quit if EOF
        if (getline(&buffer, &len, stdin) == -1) {
            exit(1);
        } 


        // If they ask for options give them options
        if (strcmp(buffer, "?\n") == 0) {
            // Print
            printf("Here are your options\n");

            if (menu == 0) {
                for (int i = 0; i < 3; i++) {
                    printf("%s", options1[i]);
                }
            }

            continue;
        }

        if (strcmp(buffer, "q\n") == 0) {
            exit(0);
        }

        // If they actually select an option
        if (menu == 0) {
            if (strcmp(buffer, options1[0]) == 0) {
                menu++;
                continue;
            } else if (strcmp(buffer, options1[1]) == 0) {
                menu += 2;
                continue;
            } else if (strcmp(buffer, options1[2]) == 0) {
                printf("Do the guard thing here\n");
                continue;
            }
        }


        // If they don't select an option
        printf("Use ? for a list of valid commands\n");
    }

    return 0;
}
