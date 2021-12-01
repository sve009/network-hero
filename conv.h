#ifndef CONV_H
#define CONV_H

/**
 * File for converting various types of data.
 *
 * Generally used to convert structures to strings
 *  to send over the network, or parse a structure
 *  back from the string
 */

/**
 * String -> Action
 */
void parse_action(action_t* dest, char* src);

/**
 * Action -> String
 */
void stringify_action(char* dest, action_t* src);

/**
 * Cyber -> String
 */
void stringify_cyber(char* dest, cyber_t* src);

/**
 * String -> Cyber
 */
void parse_cyber(cyber_t* dest, char* src);

/**
 * Game -> String
 */
void stringify_game(char* dest, game_t* src);

/**
 * String -> Game
 */
void parse_game(game_t* dest, char* src);

#endif
