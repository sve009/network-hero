#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cybers.h"
#include "conv.h"

void parse_action(action_t* dest, char* src) {
    // You better have formatted this correctly
    sscanf(src, "%9s\n%14s", &dest->specifier, &dest->arg);    
}

void stringify_action(char** dest, action_t* src) {
   // Print into dest
   sprintf(*dest, "%s\n%s", src->specifier, src->arg);
} 

void stringify_cyber(char* dest, cyber_t* src) {
    // Print into dest
    sprintf(dest, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
            src->name,
            src->health,
            src->attack,
            src->defense,
            src->sattack,
            src->sdefense,
            src->agility,
            src->statmanip,
            src->element);
    
    // Append move list
    int i = 0;
    while (src->moves[i] != NULL) {
        strcat(dest, "\n");
        strcat(dest, src->moves[i]);
        i++;
    }

    // Add end of cyber signifier
    strcat(dest, "\n");
}

void parse_cyber(cyber_t* dest, char* src) {
    // Move string
    char* mov_s;

    // Scan first fields
    sscanf(src, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n",
            dest->name,
            &dest->health,
            &dest->attack,
            &dest->defense,
            &dest->sattack,
            &dest->sdefense,
            &dest->agility,
            &dest->statmanip,
            &dest->element,
            mov_s);

    // Get the move list
    char** moves = malloc(sizeof(char*) * 4);

    // Copy each move into list
    int i = 0;
    while (sscanf(mov_s, "%s\n", &moves[i++])) {}; 

    // Set field
    dest->moves = moves;
}
