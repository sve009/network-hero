#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Include global option output based on menu level here
char* options1[] = {"use move\n", "swap cyber\n", "guard\n"};

// Main function (crazy)
int main(int argc, char** args) {
    // Menu selector, keeps track of what menu we're in
    int menu = 0;

    // Buffer for user input
    char* buffer = NULL; // input buffer
    size_t len = 0;         // len of input

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
