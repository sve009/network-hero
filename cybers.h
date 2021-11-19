#ifndef CYBER
#define CYBER

/**
 * The main data structure used to hold each Cyber
 * Holds stats and moves
 * That's about it
*/
typedef struct cyber {
    char* name;    // Name
    int health;    // Health
    int attack;    // Physical attack
    int defense;   // Physical defense
    int sattack;   // Special attack
    int sdefense;  // Special defense
    int agility;   // Agility (Speed, acc, dodge)
    int statmanip; // Resistance + competency in stat blights
    int element;   // What element is the cyber
    char** moves;
} cyber_t;

#endif
