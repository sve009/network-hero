#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "cybers.h"


void attack(cyber_t * attacker, cyber_t * defender, char * attack){
    //things that need to be accounted for on the attackers side:
        //Attack, S. Attack, Element, Status Effect/Efficacy, Agility (ability to hit an agile opponent)
    int attack = attacker->attack;
    int sattack = attacker->sattack;
    int att_element = attacker->element;
    char * status_att = NULL; //this will be determined by the attack, if left NULL then no status effect
    int status_eff = attacker->statmanip;
    int att_agil = attacker->agility;

    //things that need to be account for on the defender's side:
        //health, defense, S. defense, agility(dodge), Status Effect Resistance, element
    int health = defender->health;
    int defense = defender->defense;
    int sdefense = defender->sdefense;
    int def_agil = defender->agility;
    int status_res = defender->statmanip;
    int def_element = defender->element;

    //so I assume that we'll need like attack rolls, so random and time are probably going to be necessary
    srand(time());
    
    //I think some checks in order could go like: dodge? elemental weakness or strength? special attack? regular attack? status effect?
    
    if (((att_agil - def_agil) * (rand() % 10)) > 50) { 
        //this is the first option that came to my mind for dodge rolls, there is probably a better way
        //attack successful
    } else {
        //attack dodged/missed/etc.
    }

    int elemental_mod = 0; //-1 if defender weak, 0 if neutral, 1 if defender strong
    //fire = 0, water = 1, air = 2, rock = 3, electric = 4
    if ((def_element == 0 && att_element == 1) ||
        (def_element == 0 && att_element == 3) ||
        (def_element == 1 && att_element == 4) ||
        (def_element == 1 && att_element == 2) ||
        (def_element == 2 && att_element == 0) ||
        (def_element == 2 && att_element == 4) ||
        (def_element == 3 && att_element == 2) ||
        (def_element == 3 && att_element == 1) ||
        (def_element == 4 && att_element == 0) ||
        (def_element == 4 && att_element == 3)) {
            elemental_mod = -1;
    } else if (
        (def_element == 0 && att_element == 2) ||
        (def_element == 0 && att_element == 4) ||
        (def_element == 1 && att_element == 0) ||
        (def_element == 1 && att_element == 3) ||
        (def_element == 2 && att_element == 1) ||
        (def_element == 2 && att_element == 3) ||
        (def_element == 3 && att_element == 4) ||
        (def_element == 3 && att_element == 0) ||
        (def_element == 4 && att_element == 2) ||
        (def_element == 4 && att_element == 1)) {
            elemental_mod = 1;
    }

    //we will need to define attacks and special attacks to procede
}
