#ifndef MOVES_H
#define MOVES_H

#include "cybers.h"

static move_t moves[] = {
    {"blah", 10, 10, 0, -1, 0},
    {"blab", 10, 10, 0, -1, 0},
    {"ha", 10, 10, 0, -1, 0},
    {"oh no", 10, 10, 0, -1, 0},
    {"END", 0, 0, 0, 0, 0}
};

move_t* lookup_move(char* name);

#endif
