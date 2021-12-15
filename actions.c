#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "cybers.h"
#include "actions.h"

/**
 * Note: Assume rand is already seeded
 */
int attack(cyber_t * attacker, cyber_t * defender, move_t * move, int guard, char* log) {
    //function will return 0 on unsuccessful attack, and 1 on successful attack
    
    // Log
    char temp[100];
    memset(temp, 0, sizeof(char)*100);
    sprintf(temp, "%s used %s\n", attacker -> name, move->name);
    strcat(log, temp);
    
    
    //might be best to check move_pp before calling attack function
    if (move->move_pp == 0) {
        // Log message
        strcat(temp, "But it failed due to lack of pp\n");
        strcat(log, temp);

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
    
    //calculating dodge roll with status effects considered
    int mult = round(((float)attacker->agility) / ((float)defender->agility));
    int dodge_roll = mult * (rand() % 20);
    if (defender->curr_stat == 0 || defender->curr_stat == 4) {
        dodge_roll -= 5;
    } else if (attacker->curr_stat == 0 || attacker->curr_stat == 4) {
        dodge_roll += 5;
    }
    if (dodge_roll < 4) {
        //attack unsuccessful

        // Log
        strcat(log, "But it missed\n");

        return 0;
    }
    

    //need to caculate attack modifiers incorporating elemental comparison, status effects
    //and the difference between the cyber's attack and defense stats
    int att_mod = 2;
    int satt_mod = 2;

    //elemental comparison
    //fire = 0, water = 1, air = 2, rock = 3, electric = 4
    if ((defender->element == 0 && attacker->element == 1) ||
        (defender->element == 0 && attacker->element == 3) ||
        (defender->element == 1 && attacker->element == 4) ||
        (defender->element == 1 && attacker->element == 2) ||
        (defender->element == 2 && attacker->element == 0) ||
        (defender->element == 2 && attacker->element == 4) ||
        (defender->element == 3 && attacker->element == 2) ||
        (defender->element == 3 && attacker->element == 1) ||
        (defender->element == 4 && attacker->element == 0) ||
        (defender->element == 4 && attacker->element == 3)) {
            att_mod++;
            satt_mod++;            
            strcat(log, "It was super effective!\n");
    } else if (
        (defender->element == 0 && attacker->element == 2) ||
        (defender->element == 0 && attacker->element == 4) ||
        (defender->element == 1 && attacker->element == 0) ||
        (defender->element == 1 && attacker->element == 3) ||
        (defender->element == 2 && attacker->element == 1) ||
        (defender->element == 2 && attacker->element == 3) ||
        (defender->element == 3 && attacker->element == 4) ||
        (defender->element == 3 && attacker->element == 0) ||
        (defender->element == 4 && attacker->element == 2) ||
        (defender->element == 4 && attacker->element == 1)) {
            att_mod--;
            satt_mod--;
            strcat(log, "It wasn't very effective!\n");
    }

    //status effect checks
    if (attacker->curr_stat == 1) {
        att_mod++;
        satt_mod++;
    } else if (attacker->curr_stat == 2) {
        att_mod--;
        satt_mod--;
    } else if (attacker->curr_stat == 4) {
	att_mod--;
	satt_mod--;
    }
    if (defender->curr_stat == 2) {
        att_mod++;
        satt_mod++;
    } else if (defender->curr_stat == 3) {
        att_mod--;
        satt_mod--;
    } else if (defender->curr_stat == 4) {
	att_mod--;
	satt_mod--;
    }

    //attack defense stat comparisons, maybe this just functions at bonus damage
    int bonus_damage = attacker->attack - defender->defense;
    int bonus_sdamage = attacker->sattack - defender->sdefense;
    if (bonus_damage < 0) bonus_damage = 0;
    if (bonus_sdamage < 0) bonus_sdamage = 0;
    
    //damage calculation will be a combination of additive and multiplicative damage mods
    printf("Attack mod: %d\n", att_mod);
    printf("SAttack mod: %d\n", satt_mod);
    printf("Bonus_damage: %d\n", bonus_damage);
    printf("Bonus SDamage: %d\n", bonus_sdamage);
    if (move->damage != 0) {
        int damage = (move->damage + bonus_damage) * att_mod;
    } else {
        int damage = 0;
    }
    if (move->sdamage != 0) {
        damage += (move->sdamage + bonus_sdamage) * satt_mod;
    }
    

    //guarding results in less damage for defender
    if (guard) {
        damage = damage / 2;
    }
    //update cyber's health, status, and the move's pp
    defender->health -= damage;

    // Log
    char dmg[50];
    memset(dmg, 0, sizeof(char)*50);
    sprintf(dmg, "It did %d damage\n", damage);
    strcat(log, dmg);

    // Log death cases
    if (defender->health <= 0) {
        char death[50];
        sprintf(death, "%s died\n", defender->name);
        strcat(log, death);
    }
    
    //check status effect durations at the beginning of attack
    //calculating new status rolls now
    if (move->status_eff > -1) { 
        if (move->status_target == 0){
            if (((attacker->statmanip - defender->statmanip) + (rand() % 20)) > 20) {
                defender->curr_stat = move->status_eff;
                defender->stat_durr = 2;
            }
        } else {
            attacker->curr_stat = move->status_eff;
            attacker->stat_durr = 2;
        }
    }
    
    return 1;
}
