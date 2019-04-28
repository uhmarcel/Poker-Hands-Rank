
/*---------------------------------------------------------------------------*\

   Source code:  CardsValidation.c
        Author:  Marcel Riera

   Description:  Source code containing a collection of functions required for
                 input validation of the program.

                 This file is required for compilation of cardsShuffle.out, and
                 must be in the same folder with MainCards.c, CardsFunctions.c,
                 pokerFunctions.c and Cards.h

\*---------------------------------------------------------------------------*/

#include "Cards.h"      // Required program header
#include <string.h>     // Required for validation strlen()

/**
 * Function validateArguments
 * Validates argc and argv for the poker game.
 *
 * @param argc   parameter argc from main execution
 * @param argv   parameter argv from main execution
 * @return       0 if valid, -1 if invalid
 */

int validateArguments(int argc, char *argv[]) {
    if (validateArgumentsAmount(argc) == INVALID_INPUT) {
        return INVALID_INPUT;
    } // endif

    int argCards = validateArgument(argv[CARDS_PER_HAND_INDEX]);
    int argHands = validateArgument(argv[PLAYER_AMOUNT_INDEX]);

    if (argCards == INVALID_INPUT || argHands == INVALID_INPUT ||
        validateInputCombination(argCards, argHands) == INVALID_INPUT) {
        return INVALID_INPUT;
    } // endif
    return VALID_INPUT;
} // end function

/**
 * Function validateArgumentsAmount
 * Checks if the input contains the correct number of arguments, or else
 * terminates the program.
 * @param argc  Input argument count of the program.
 * @return      Returns -1 if invalid, else 0 if valid.
 */

int validateArgumentsAmount(int argc) {
    if (argc != VALID_ARGUMENTS_AMOUNT) {
        return INVALID_INPUT;
    } // endif
    return VALID_INPUT;
} // end function

/**
 * Function validateArgument
 * Checks if the given string argument has the correct input format, or else
 * terminates the program.
 * Proper argument must represent a number between range 1 - 13.
 *
 * @param argument  String argument input from argv.
 * @return          Returns the integer representation of the argument
 */

int validateArgument(char *argument) {
    int argumentLength = strlen(argument);

    if ((argumentLength < MIN_ARGV_LEN) || (argumentLength > MAX_ARG_LEN)) {
        return INVALID_INPUT;
    } // endif

    int argToInteger = stringToInt(argument);

    if (argToInteger < MIN_INPUT_RANGE || argToInteger > MAX_INPUT_RANGE) {
        return INVALID_INPUT;
    } // endif
    return argToInteger;
} // end function

/**
 * Function stringToInt
 * Parses a string of characters to its integer representation.
 *
 * FORMULAS:
 *  argToInteger = (argToInteger * 10) + (*argument - FIRST_CHAR_INTEGER)
 *     To transform from single digits to a complete integer, each iteration
 *     multiplies by 10 its content to add space for next digit to the right.
 *     Argument - FIRST_CHAR_INTEGER (or '0') transforms a char to its numeric
 *     value.
 *
 * @param string    input string to be parsed
 * @return          integer representation of string
 */

int stringToInt(char *string) {
    int toInteger = 0;

    for (; *string != END_OF_STRING; string++) { // Navigates string
        if (!isCharValidInteger(*string)) {
            invalidInputTerminate();
        } // endif
        toInteger = (toInteger * 10) + (*string - FIRST_CHAR_INTEGER);
    } // endfor
    return toInteger;
} // end function

/**
 * Function isCharValidInteger
 * Checks whether the input char represents a numeric digit.
 * @param testChar  Character to test if represents a digit.
 * @return          True(1) if character represents a digits, else false(1)
 */

int isCharValidInteger(char testChar) {
    if ((testChar < FIRST_CHAR_INTEGER) || (testChar > LAST_CHAR_INTEGER)) {
        return FALSE;
    } // endif
    return TRUE;
} // end function

/**
 * Function validateInputCombination
 * Checks if the current combination of inputs is valid for the amount of
 * cards in a deck. Terminates the program if (input1 * input2) > 52.
 * @param cardsPerHand  input size of hands.
 * @param players       input amount of players.
 * @return              returns -1 if invalid, else 0 if valid.
 */

int validateInputCombination(int cardsPerHand, int players) {
    if (POKER_HAND_SIZE * players > DECK_SIZE) {
        return INVALID_INPUT;
    } // endif
    return VALID_INPUT;
} // end function

/**
 * Function invalidInputTerminate
 * Called due to invalid input, it displays specifications to enter a valid
 * input before termination.
 */

void invalidInputTerminate() {
    printf("Cards Shuffle\n");
    printf("The program initiated with invalid input arguments.\n\n");
    printf("The program expects two arguments: [Cards per hand] and [Players]\n");
    printf("[Cards per hand] must be an integer between the range ");
    printf("%d-%d.\n", MIN_INPUT_RANGE, MAX_INPUT_RANGE);
    printf("[Players] must also be an integer between the range ");
    printf("%d-%d.\n", MIN_INPUT_RANGE, MAX_INPUT_RANGE);
    printf("The amount of players in combination with each hands size must not\n");
    printf("result up to more than %d cards, as is the decks limit.\n", DECK_SIZE);
    printf("(Cards per hand x Players must be less than %d)\n\n", DECK_SIZE);
    printf("Program will terminate.");
} // end function

