#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "movelist.h"

move_t* lookup_move(char* name) {
    // Loop through moves until one with name
    //   is found
    int i = 0;
    while (strcmp(name, moves[i].name) != 0
            && strcmp("END", moves[i].name) != 0) {
        i++;
    }

    // Not found case
    if (strcmp("END", moves[i].name) == 0) {
        perror("Move not in list");
        exit(1);
    }

    // Found case
    return &moves[i];
}

