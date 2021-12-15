#ifndef CYBERLIST
#define CYBERLIST
static int num_cybers = 10;
char* moves0[] = {"fireball", "kick", "rally", "barbeque"};
char* moves1[] = {"lightning bolt", "thunder gun", "tail whip", "bite"};
char* moves2[] = {"rock slide", "crush", "slam", "harden"};
char* moves3[] = {"water pistol", "freeze", "ice Armor", "slam"};
char* moves4[] = {"roost", "intimidate", "aeroblast", "peck"};
char* moves5[] = {"lightning bolt", "shock", "charge", "aeroblast"};
char* moves6[] = {"fireball", "pyrosplosion", "charge", "rock slide"};
char* moves7[] = {"water pistol", "wave", "bite", "puff"};
char* moves8[] = {"slash", "heavy slash", "pound", "harden"};
char* moves9[] = {"peck", "plague", "torrent", "roost"};
char* moves10[] = {"gun", "knife", "pen", "sword"};
cyber_t cybers[] = {{"Cyndakwill", -1, 0, 80, 30, 20, 20, 30, 30, 10, 0, moves0},
       {"Peekahchew", -1, 0, 80, 40, 15, 30, 10, 30, 10, 3, moves1},
       {"Geoguy", -1, 0, 140, 20, 40, 10, 40, 15, 30, 2, moves2},
       {"Pipluhp", -1, 0, 80, 30, 30, 15, 30, 30, 30, 1, moves3},
       {"Ho-Oh-No", -1, 0, 60, 25, 30, 20, 20, 40, 20, 4, moves4},
       {"Static", -1, 0, 65, 35, 5, 20, 10, 50, 20, 3, moves5},
       {"Infiirno", -1, 0, 105, 35, 5, 10, 10, 10, 20, 0, moves6},
       {"Fiiish", -1, 0, 70, 20, 15, 20, 20, 40, 20, 1, moves7},
       {"Stoneknife", -1, 0, 80, 20, 20, 20, 20, 30, 10, 2, moves8},
       {"Ravyn", -1, 0, 55, 20, 10, 20, 15, 50, 20, 4, moves9},
       {"Regular guy", -1, 0, 80, 20, 20, 20, 20, 20, 20, 0, moves10}};
#endif
