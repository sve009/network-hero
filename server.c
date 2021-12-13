#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "cybers.h"
#include "conv.h"
#include "cyberlist.h"
#include "movelist.h"
#include "actions.h"

// Main game state
game_t state;

typedef struct client_data {
    int client;
    int player_no;
} client_data_t;

// Prep cyber_t into t_cyber_t
void prep_cyber(t_cyber_t* dest, cyber_t* src) {
    // Just copy over the relevant fields of the cyber
    dest->health = src->health;
    dest->attack = src->attack;
    dest->defense = src->defense;
    dest->sattack = src->sattack;
    dest->sdefense = src->sdefense;
    dest->agility = src->agility;
    dest->statmanip = src->statmanip;
}

// Prep game_t into t_game_t to send to client
void prep_game(t_game_t* dest, game_t* src) {
    // Set actives
    dest->active_p1 = src->active_p1;
    dest->active_p2 = src->active_p2;

    // Set cybers
    for (int i = 0; i < 3; i++) {
        // Copy p1[i]
        prep_cyber(&dest->elems[i], &state.p1[i]);
        // Copy p2[i]
        prep_cyber(&dest->elems[i+3], &state.p2[i]);
    }
}

// Function for listening to clients
void* listen_client(void* sock_fd) {
    // Action to pass into parser
    action_t* a = malloc(sizeof(action_t));

    // Grab the socket fd
    int fd = *(int*)sock_fd;

    // Wait to receive action
    read(fd, a, sizeof(action_t));

    // Return the action
    return (void*)a;
}

void* client_setup(void* sock_fd) {
    // Accumulator to see how many messages client has sent
    int n = 0;

    // Socket
    client_data_t* data = sock_fd;

    printf("Client: %d\n", data->client);
    printf("Player: %d\n", data->player_no);

    // Buffer for message
    char buffer[50];
    memset(buffer, 0, sizeof(char) * 50);

    // Loop until all three chosen
    while (n < 3) {
        // Read in cyber name
        read(data->client, buffer, sizeof(char) * 50);

        // Debug
        printf("%s\n", buffer);

        // Look up cyber (Client checks validity)
        int i;
        for (i = 0; i < num_cybers; i++) {
            if (strcmp(cybers[i].name, buffer) == 0) {
                break;
            }
        }

        // Set cyber
        if (data->player_no == 0) {
            memcpy(&state.p1[n], &cybers[i], sizeof(cyber_t));
        } else {
            memcpy(&state.p2[n], &cybers[i], sizeof(cyber_t));
        }

        // Increment n
        n++;
    }
    return NULL;
}



void setup_clients(int clients[]) {
    // thread holders
    pthread_t threads[2];

    // Arguments
    client_data_t args[2];

    // Get initial state from clients
    for (int i = 0; i < 2; i++) {
        // Set argument
        args[i].client = clients[i];
        args[i].player_no = i;

        // Create thread
        pthread_create(&threads[i], NULL, client_setup, (void*)&args[i]);
    }

    // Wait for inputs
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Send initial opponent choices back to client
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0) {
                printf("Sending: %s\n", state.p2[j].name);
                write(clients[i], state.p2[j].name, sizeof(char)*50);
            } else {
                printf("Sending: %s\n", state.p1[j].name);
                write(clients[i], state.p1[j].name, sizeof(char)*50);
            }
        }
    }
}


int main(int argc, char** args) {
    // Seed rand
    srand(time(NULL));

    // Set the initial party
    for (int i = 0; i < 3; i++) {
        memcpy(&state.p1[i], cybers, sizeof(cyber_t));
        memcpy(&state.p2[i], cybers, sizeof(cyber_t));
        // initial_state.p1[i] = cybers[0];
        // initial_state.p2[i] = cybers[0];
    }

    // Set initial active as well
    state.active_p1 = 0;
    state.active_p2 = 0;

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

    // Notify clients that game is starting
    for (int i = 0; i < 2; i++) {
        write(clients[i], &i, sizeof(int));
    }

    // Setup initial game state
    setup_clients(clients);

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
        // ---------------------------
        //          MATH
        // ---------------------------
        
        // Response message
        char resp_mess[200];
        memset(resp_mess, 0, sizeof(char) * 200);

        // Swap code
        for (int i = 0; i < 2; i++) {
            if (strcmp(actions[i]->specifier, "swap") == 0) {
                char swap_msg[50];
                int choice = atoi(actions[i]->arg);
                if (i == 0) {
                    state.active_p1 = choice;

                    // Add description to response message
                    sprintf(swap_msg, "Player 0 swapped to %s\n", state.p1[state.active_p1].name);
                    strcat(resp_mess, swap_msg); 
                } else {
                    state.active_p2 = choice;

                    // Add description to response message
                    sprintf(swap_msg, "Player 1 swapped to %s\n", state.p2[state.active_p2].name);
                    strcat(resp_mess, swap_msg); 
                }
            }
        }

        // Guard code
        int p1_guard = 0;
        int p2_guard = 0;
        for (int i = 0; i < 2; i++) {
            if (strcmp(actions[i]->specifier, "guard") == 0) {
                // Add description to response message
                char guard_mess[20];
                sprintf(guard_mess, "Player %d guarded\n", i);
                strcat(resp_mess, guard_mess);

                // Set guard flags
                if (i == 0) {
                    p1_guard = 1;
                } else {
                    p2_guard = 1;
                }
            }
        }

        // Attack code

        for (int i = 0; i < 2; i++) {
            if (strcmp(actions[i]->specifier, "move") == 0) {
                char move_mess[300];
                memset(move_mess, 0, sizeof(char)*300);

                // Debug:
                printf("%s\n", actions[i]->arg);

                // Move lookup to turn move name into struct
                move_t* m = lookup_move(actions[i]->arg);

                if (i == 0) {
                    attack(&state.p1[state.active_p1], &state.p2[state.active_p2], m, p2_guard, move_mess);
                } else {
                    attack(&state.p2[state.active_p2], &state.p1[state.active_p1], m, p1_guard, move_mess);
                }

                // Add log message
                strcat(resp_mess, move_mess);
            }
        }

        
        // Prep game state to send
        t_game_t message;
        prep_game(&message, &state);

        // Debug
        printf("%s\n", resp_mess);
        
        // Response to release clients
        for (int i = 0; i < 2; i++) {
            // Current gamestate
            write(clients[i], &message, sizeof(t_game_t));
            // Log messages
            write(clients[i], resp_mess, sizeof(char)*200);
        }

        // Cleanup
        // --------------------
        free(actions[0]);
        free(actions[1]);

    }
    return 0;
}

