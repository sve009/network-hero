#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../cybers.h"

int main(int argc, char** args) {
    // Check to ensure there are two args:
    if (argc != 3) {
        fprintf(stderr, "Usage: ./cyperparser SOURCE DEST\n");
        exit(1);
    }

    // Grab the args
    char* source = args[1];
    char* dest   = args[2];

    // Open file handles
    FILE* s = fopen(source, "r");
    FILE* d = fopen(dest, "w");

    // Error check
    if (s == NULL || d == NULL) {
        fprintf(stderr, "There was an error opening those files\n");
        exit(1);
    }

    // Create buffer
    char* buffer = NULL;
    size_t len = 0;
    ssize_t rlen = 0;

    // Create array to hold cybers
    int capacity = 5;
    cyber_t* cybers[capacity];
    int num_cybers = 0;

    // Read in each cyber
    while ((rlen = getline(&buffer, &len, s)) != -1) {
        // Allocate space for cyber
        cybers[num_cybers] = malloc(sizeof(cyber_t));

        printf("%lu %c\n", len, buffer[rlen - 1]);

        // Strip newline
        buffer[rlen - 1] = '\0';

        // Store the name
        cybers[num_cybers]->name = strdup(buffer);

        // Move on to health
        getline(&buffer, &len, s);

        // Scan health into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->health);

        // Move on to attack
        getline(&buffer, &len, s);

        // Scan attack into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->attack);

        // Move on to defense
        getline(&buffer, &len, s);

        // Scan defense into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->defense);

        // Move on to special attack
        getline(&buffer, &len, s);

        // Scan special attack into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->sattack);

        // Move on to special defense
        getline(&buffer, &len, s);

        // Scan special defense into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->sdefense);

        // Move on to agility
        getline(&buffer, &len, s);

        // Scan agility into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->agility);

        // Move on to stat manip
        getline(&buffer, &len, s);

        // Scan stat manip into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->statmanip);

        // Move on to element
        getline(&buffer, &len, s);

        // Scan element into structure
        sscanf(buffer, "%d", &cybers[num_cybers]->element);

        // Make space for moves
        cybers[num_cybers]->moves = malloc(sizeof(char*) * 4);
        int i = 0;

        // Run through the move list
        while (i < 4 && (rlen = getline(&buffer, &len, s)) != -1 && len > 0) {
            // Strip newline
            buffer[rlen - 1] = '\0';

            // Stick in move list
            cybers[num_cybers]->moves[i++] = strdup(buffer);
        }

        // Get extra line:
        rlen = getline(&buffer, &len, s);

        // Repeats here, extra line after cyber captured in
        //   while loop
        
        // Increment number of cybers
        num_cybers++;
    }

    // Close source file
    fclose(s);

    // Print initial segment
    fprintf(d, "#ifndef CYBERLIST\n");
    fprintf(d, "#define CYBERLIST\n");

    // Print number of cybers
    fprintf(d, "static int num_cybers = %d;\n", num_cybers);

    // Write each moveset
    for (int i = 0; i < num_cybers; i++) {
        fprintf(d, "char* moves%d[] = {\"%s\", \"%s\", \"%s\", \"%s\"};\n",
                i,
                cybers[i]->moves[0],
                cybers[i]->moves[1],
                cybers[i]->moves[2],
                cybers[i]->moves[3]);
    }

    // Write cyber header
    fprintf(d, "cyber_t cybers[] = {");

    // Write each cyber
    for (int i = 0; i < num_cybers; i++) {
        // Print cyber
        fprintf(d, "{\"%s\", 0, 0, %d, %d, %d, %d, %d, %d, %d, %d, moves%d}",
                cybers[i]->name,
                cybers[i]->health,
                cybers[i]->attack,
                cybers[i]->defense,
                cybers[i]->sattack,
                cybers[i]->sdefense,
                cybers[i]->agility,
                cybers[i]->statmanip,
                cybers[i]->element,
                i);

        // Print the comma if not the last element
        if (i < num_cybers - 1) {
            fprintf(d, ", ");
        }
    }


    // Print closing segment
    fprintf(d, "};\n");
    fprintf(d, "#endif\n");

    // Close destination
    fclose(d);

    return 0;
}

