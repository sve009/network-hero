#ifndef CYBER
#define CYBER

// Element lookup table
const char* elements[] = {"Fire", "Water", "Rock", "Electric", "Air"};

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

/**
 * The game state is purely two lists of three cybers,
 *   making up both players cybers.
 */
typedef struct game {
    cyber_t p1[3];
    cyber_t p2[3];
} game_t;

#endif
