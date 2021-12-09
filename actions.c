#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "cybers.h"


int attack(t_cyber_t * attacker, t_cyber_t * defender, move_t * move, int guard) {
    //function will return 0 on unsuccessful attack, and 1 on successful attack
    
    
    //might be best to check move_pp before calling attack function
    if (move->move_pp == 0) {
        printf("cannot use this move\n");
        return 0;
    }

    //checking and getting rid of expired status attacks before attack begins
    //stat_durr should be decremented by the server at the end of every turn
    if (attacker->curr_stat != -1 && attacker->stat_durr == 0) {
        attacker->curr_stat = -1;
    }
    if (defender->curr_stat != -1 && defender->stat_durr == 0) {
        defender->curr_stat = -1;
    }

    //so I assume that we'll need like attack rolls, so random and time are probably going to be necessary
    srand(time());
    
    //calculating dodge roll with status effects considered
    int dodge_roll = (attacker->agility - defender->agility) + (rand() % 20);
    if (defender->curr_stat == 0) {
        dodge_roll -= 5;
    } else if (attacker->curr_stat == 0) {
        dodge_roll += 5;
    }
    if (dodge_roll < 20) {
        //attack unsuccessful
        return 0;
    }
    

    //need to caculate attack modifiers incorporating elemental comparison, status effects
    //and the difference between the cyber's attack and defense stats
    int att_mod = 0;
    int satt_mod = 0;

    //elemental comparison
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
            att_mod++;
            satt_mod++;            
    } else if (
        (def_element == 0 && att_element == 2) ||
        (def_element == 0 && att_element == 4) ||
        (def_element == 1 && att_element == 0) ||
        (def_element == 1 && att_element == 3) ||
        (def_element == 2 && att_element == 1) ||
        (def_element == 2 && att_element == 3) ||
        (def_element == 3 && att_element == 4) ||
        (def_element== 3 && att_element == 0) ||
        (def_element == 4 && att_element == 2) ||
        (def_element == 4 && att_element == 1)) {
            att_mod--;
            satt_mod--;
    }

    //status effect checks
    if (attacker->curr_stat == 1) {
        att_mod++;
        satt_mod++;
    } else if (attacker->curr_stat == 2) {
        att_mod--;
        satt_mod--;
    }
    if (defender->curr_stat == 2) {
        att_mod++;
        satt_mod++;
    } else if (defender->curr_stat == 3) {
        att_mod--;
        satt_mod--;
    }

    //attack defense stat comparisons, maybe this just functions at bonus damage
    int bonus_damage = attacker->attack - defender->defense;
    int bonus_sdamage = attacker->sattack - defender->sdefense;
    
    //damage calculation will be a combination of additive and multiplicative damage mods
    int damage = (move->damage + bonus_damage) * att_mod;
    damabe += (move->sdamage + bonus_sdamage) * satt_mod;

    //guarding results in less damage for defender
    if (guard) {
        damage = damage / 2;
    }
    //update cyber's health, status, and the move's pp
    defender->health -= damage;
    
    //check status effect durations at the beginning of attack
    //calculating new status rolls now
    if (move->stat_eff > -1) { 
        if (stat_target == 0){
            if (((attacker->statmanip - defender->statmanip) + (rand() % 20)) > 20) {
                defender->curr_stat = move->stat_eff;
                defender->stat_durr = 1;
            }
        } else {
            attacker->curr_stat = move->stat_eff;
            attacker->stat_durr = 1;
        }
    }
    
}