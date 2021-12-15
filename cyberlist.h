#ifndef CYBERLIST
#define CYBERLIST
static int num_cybers = 3;
char* moves0[] = {"fireball", "kick", "rally", "barbeque"};
char* moves1[] = {"lightning bolt", "thunder gun", "tail whip", "bite"};
char* moves2[] = {"rock slide", "crush", "slam", "harden"};
char* moves3[] = {"water pistol", "freeze", "ice Armor", "slam"};
char* moves4[] = {"roost", "intimidate", "aeroblast", "peck"};
cyber_t cybers[] = {{"Cyndakwill", -1, 0, 80, 30, 20, 20, 30, 30, 10, 0, moves0}, {"Peekahchew", -1, 0, 80, 40, 15, 30, 10, 30, 10, 3, moves1}, {"Geoguy", -1, 0, 140, 20, 40, 10, 40, 15, 30, 2, moves2}, {"Pipluhp", -1, 0, 80, 30, 30, 15, 30, 30, 30, 1, moves3}, {"Ho-Oh-No", -1, 0, 60, 25, 30, 20, 20, 40, 20, 4, moves4}};
#endif
