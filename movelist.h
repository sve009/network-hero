#ifndef MOVES_H
#define MOVES_H

#include "cybers.h"

static move_t moves[] = {
    {"bite", 10 ,10, 0, -1, 0},
    {"intimidate", 10, 0, 0, 2, 0},
    {"rally", 10, 0, 0, 1, 1},
    {"hypnotize", 10, 0, 0, 0, 0},
    {"fireball", 10, 5, 5, -1, 0},
    {"kick", 10, 10 , 0, -1, 0},
    {"barbeque", 5, 0, 15, -1, 0},
    {"lightning bolt", 10, 3, 10, 0, 0},
    {"thunder gun", 2, 10, 15, -1, 0},
    {"tail whip", 10, 11, 2, -1, 0},
    {"rock slide", 5, 10, 10, -1, 0},
    {"crush", 10, 10, 0, -1, 0},
    {"slam", 10, 5, 5, -1, 0},
    {"harden", 10, 0, 0, 3, 1},
    {"water pistol", 15, 10, 5, -1, 0},
    {"freeze", 10, 0, 5, 4, 0},
    {"ice armor", 10, 0, 0, 3, 1},
    {"roost", 10, 0, 0, 1, 1},
    {"aeroblast", 10, 10, 10, -1, 0},
    {"peck", 10, 15, 0, -1, 0},
    {"shock", 15, 15, 10, 2, 0},
    {"charge", 15, 0, 0, 1, 1},
    {"pyrosplosion", 20, 20, 10, 0, 1},
    {"wave", 10, 5, 5, 0, 0},
    {"puff", 15, 0, 0, 1, 1},
    {"pound", 10, 10, 0, 0, 0},
    {"slash", 5, 10, 0, -1, 0},
    {"heavy slash", 15, 20, 5, 2, 1},
    {"torrent", 25, 20, 10, 1, 0},
    {"plague", 10, 5, 0, 2, 0},
    {"gun", 10, 10, 4, 3, 1},
    {"pen", 5, 30, 1, 1, 0},
    {"sword", 5, 5, 5, 0, 0},
    {"knife", 15, 10, 10, -1, 0},
    {"END", 0, 0, 0, 0, 0}
};

move_t* lookup_move(char* name);

#endif
