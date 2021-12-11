#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "cybers.h"
#include "cyberlist.h"
#include "conv.h"

game_t initial_state; 

int player_n;

// Include global option output based on menu level here
char* options1[] = {"use move", "swap cyber", "guard"};

// Print a cyber
void print_cyber(cyber_t* cyber) {
    printf("%s: %d | %s\n", cyber->name, cyber->health, elements[cyber->element]);
}

// Print out the info that user needs to know when asked
void print_game() {
    print_cyber(&initial_state.p1[0]);
    print_cyber(&initial_state.p2[0]);
}

void restore_cyber(cyber_t* dest, t_cyber_t* src) {
    // Just copy over the relevant fields of the cyber
    dest->health = src->health;
    dest->attack = src->attack;
    dest->defense = src->defense;
    dest->sattack = src->sattack;
    dest->sdefense = src->sdefense;
    dest->agility = src->agility;
    dest->statmanip = src->statmanip;
}

void update_gamestate(t_game_t* m) {
    for (int i = 0; i < 3; i++) {
        // Copy the truncated data into local game state
        memcpy(&initial_state.p1[i].curr_stat, &m->elems[i], sizeof(t_cyber_t));
        memcpy(&initial_state.p2[i].curr_stat, &m->elems[i+3], sizeof(t_cyber_t));
    }
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

    // Wait for other player to connect
    printf("Waiting for opponent to connect...\n");
    
    // Read player number from server
    read(*serv_sock, &player_n, sizeof(int));

    // Notify player
    printf("You are player %d\n", player_n);
}


// Main function (crazy)
int main(int argc, char** args) {
    // Set the initial party
    for (int i = 0; i < 3; i++) {
        memcpy(&initial_state.p1[i], cybers, sizeof(cyber_t));
        memcpy(&initial_state.p2[i], cybers, sizeof(cyber_t));
        // initial_state.p1[i] = cybers[0];
        // initial_state.p2[i] = cybers[0];
    }

    // Set initial active as well
    initial_state.active_p1 = 0;
    initial_state.active_p2 = 0;

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
        // Action chosen flag
        int valid_choice = 0;
        int block = 0;

        // Death cases
        if (player_n == 0 && initial_state.p1[initial_state.active_p1].health <= 0) {
            printf("%s fucking died\n",
                    initial_state.p1[initial_state.active_p1].name);
            menu = 2;
        }
        if (player_n == 0 && initial_state.p2[initial_state.active_p2].health <= 0) {
            printf("%s fucking died\n",
                    initial_state.p2[initial_state.active_p2].name);
            menu = 2;
        }

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

        // Length of line
        int line_len;

        // Get line, quit if EOF
        if ((line_len = getline(&buffer, &len, stdin)) == -1) {
            exit(1);
        } 

        // Strip newline from buffer
        buffer[line_len-1] = '\0';


        // If they ask for options give them options
        if (strcmp(buffer, "?") == 0) {
            // Print
            printf("Here are your options\n");

            if (menu == 0) {
                // Print out main menu options
                for (int i = 0; i < 3; i++) {
                    printf("%s\n", options1[i]);
                }
            } else if (menu == 1) {
                // Print out moves of active cyber
                int i = 0;
                while (initial_state.p1[0].moves[i] != NULL && i < 4) {
                    printf("%s\n", initial_state.p1[0].moves[i++]);
                }
            } else if (menu == 2) {
                // Print out list of cybers to switch to
                for (int i = 0; i < 3; i++) {
                    printf("%s\n", initial_state.p1[i].name);
                }
            } 

            // Update flag
            valid_choice = 1;
        }

        // Quit if indicated
        if (strcmp(buffer, "q") == 0) {
            exit(0);
        }

        // Print out game state if indicated
        if (strcmp(buffer, "p") == 0) {
            // Print game then continue
            print_game();

            // Update flag
            valid_choice = 1;
        }

        // If they actually select an option
        // 0 = Top level menu
        // 1 = Move menu
        // 2 = Swap menu
        if (menu == 0) {
            if (strcmp(buffer, options1[0]) == 0) {
                menu++;

                // Update flag
                valid_choice = 1;
            } else if (strcmp(buffer, options1[1]) == 0) {
                menu += 2;

                // Update flag
                valid_choice = 1;
            } else if (strcmp(buffer, options1[2]) == 0) {
                // Create action
                action_t send;
                sprintf(send.specifier, "guard");
                sprintf(send.arg, "");

                // Send action
                write(serv_sock, &send, sizeof(action_t));

                // Update flag
                valid_choice = 1;
                block = 1;
            }
        } else if (menu == 1) {
            int i = 0;
            while (initial_state.p1[0].moves[i] != NULL && i < 4) {
                if (strcmp(buffer, initial_state.p1[0].moves[i]) == 0) {
                    // Create action
                    action_t send;
                    sprintf(send.specifier, "move");
                    sprintf(send.arg, "%s", initial_state.p1[0].moves[i]);

                    // Send action
                    write(serv_sock, &send, sizeof(action_t));

                    // Update flag
                    valid_choice = 1;
                    block = 1;

                    // Update back to top-level menu
                    menu = 0;

                    break;
                }
                i++;
            }
        } else if (menu == 2) {
            // Switch case
            for (int i = 0; i < 3; i++) {
                if (strcmp(buffer, initial_state.p1[i].name) == 0) {
                    // Create action
                    action_t send;
                    sprintf(send.specifier, "swap");
                    sprintf(send.arg, "%d", i);

                    // Send action
                    write(serv_sock, &send, sizeof(action_t));

                    // Update flag
                    valid_choice = 1;
                    block = 1;

                    // Update back to top-level menu
                    menu = 0;

                    break;
                }
                i++;
            }
        }



        // If they don't select an option
        if (valid_choice == 0) {
            printf("Use ? for a list of valid commands\n");
        } else if (block == 1) {
            // Wait for server response

            // Let user know
            printf("Waiting for other player...\n");

            // Buffer for holding t_game_t
            t_game_t temp;

            // Read server response
            read(serv_sock, &temp, sizeof(t_game_t));

            // Update the game state
            update_gamestate(&temp);

            // Get response message
            char response_mess[200];
            read(serv_sock, response_mess, sizeof(char) * 200);

            // Print response message
            printf("%s", response_mess);
            fflush(stdout);

            // Then end so game loop can continue
        }
    }

    return 0;
}
