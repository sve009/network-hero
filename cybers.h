#ifndef CYBER_H
#define CYBER_H

// Element lookup table
static const char* elements[] = {"Fire", "Water", "Rock", "Electric", "Air"};

/**
 * The main data structure used to hold each Cyber
 * Holds stats and moves
 * That's about it
*/
typedef struct __attribute__((packed)) cyber {
    char* name;    // Name
    int health;    // Health
    int attack;    // Physical attack
    int defense;   // Physical defense
    int sattack;   // Special attack
    int sdefense;  // Special defense
    int agility;   // Agility (Speed, acc, dodge)
    int statmanip; // Resistance + competency in stat blights
    int element;   // What element is the cyber
    char** moves;  // List of move names
} cyber_t;

/**
 * Truncated cyber for sending elements that change
 */
typedef struct __attribute__((packed)) t_cyber {
    int health;    // Health
    int attack;    // Physical attack
    int defense;   // Physical defense
    int sattack;   // Special attack
    int sdefense;  // Special defense
    int agility;   // Agility (Speed, acc, dodge)
    int statmanip; // Resistance + competency in stat blights
} t_cyber_t;

typedef struct t_game {
    int active_p1;
    int active_p2;
    t_cyber_t elems[6];
} t_game_t;


/**
 * The game state is purely two lists of three cybers,
 *   making up both players cybers.
 */
typedef struct game {
    int active_p1;
    int active_p2;

    cyber_t p1[3];
    cyber_t p2[3];
} game_t;

/**
 * An action that a player takes. Clients send
 *   actions to the server, which uses the two
 *   to update the game state.
 */
typedef struct action {
    char specifier[25];
    char arg[25];
} action_t;

#endif
