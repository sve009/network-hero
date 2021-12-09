#ifndef CYBER_H
#define CYBER_H

// Element lookup table
static const char* elements[] = {"Fire", "Water", "Rock", "Electric", "Air"};

// Status lookup table
static const char* statuses[] = {"Dizzy", "Enraged", "Weakened", "Hardened"};

/**
 * This struct holds the necessary information to calculate
 * outcomes of the move when attacking.
**/
typedef struct move {
    char * name;
    int move_pp;
    int damage;
    int sdamage;
    int status_eff; //-1 if no status effect
    int status_target; //0 = opponent, 1 == self
} move_t;

/**
 * The main data structure used to hold each Cyber
 * Holds stats and moves
 * That's about it
*/
typedef struct cyber {
    //char * curr_stat could be added in to make it so that we can have status effects last longer
    //int stat_dur could also be added in to count the amount of turns the status lingers for
    char* name;    // Name
    int curr_stat; // Stores active status effect on cyber
    int stat_durr; // Stores amount of turns left for status effect
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
    int curr_stat; // Stores active status effect on cyber
    int stat_durr; // Stores amount of turns left for status effect
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
