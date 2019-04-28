
/*---------------------------------------------------------------------------*\

   Source code:  MainCards.c
        Author:  Marcel Riera

      Language:  C
   Compile/Run: make build
                ./PokerHands.out *[NUMBER] **[NUMBER]

                NOTE: Items with asterisk correspond to user input:
                *: Integer from 1-13 to define cards per hand
                **: Integer from 1-13 to define amount of players

   Alternative: gcc MainCards.c CardsValidation.c CardsFunctions.c
                PokerFunctions.c -o PokerHands.out

  Dependencies: This program requires the following files in the same
                directory for proper compilation
                - MainCards.c
                - CardsValidation.c
                - CardsFunctions.c
                - PokerFunctions.c
                - Cards.h

  --------------------------------------------------------------------

  Description:  This program creates an ordered deck, then shuffles the
                deck, and finally draws hands for all players indicated
                in the input.

        Input:  Input is retrieved by console arguments.
                Arg1 - Integer from 1-13 to define cards per hand
                Arg2 - Integer from 1-13 to define amount of players
                Where Arg1 x Arg2 <= DECK_SIZE (52)

       Output:  The program outputs the initially ordered deck of cards,
                the deck after being shuffled, and finally each players
                hands after drawing cards.

      Process:  The program's steps are as follows
                1. Validate input arguments
                2. Initialize deck of cards
                3. Display deck of cards
                4. Shuffle deck of cards
                5. Display deck of cards
                6. Draw cards for each hand
                7. Display hands
                8. Sort hands
                9. Display hands
                10. Rank hands
                11. Display hands
                12. Find winner
                13. Display hands
                14. Rank test hands
                15. Display hands
                16. Terminate

       *Notes:  Main uses wprintf to print in Unicode mode.

                Variable length array hands[][] can not be initialized to
                zero when declared.

                HAND_SIZE, PLAYERS and hands[][] are not initialized at
                the beginning of main due to dependencies.

                Program returns INVALID INPUT or -1 if it started with
                invalid arguments

\*---------------------------------------------------------------------------*/

#include "Cards.h"    // Required program header
#include <time.h>     // Required for seed randomization

int main(int argc, char *argv[]) {
    /* Input Validation*/
    if (validateArguments(argc, argv) == INVALID_INPUT) {
        invalidInputTerminate();
        return INVALID_INPUT;
    } // endif
    /* Variable Initialization */
    const int PLAYERS = stringToInt(argv[PLAYER_AMOUNT_INDEX]);
    Card deck[DECK_SIZE] = {};
    Hand hands[PLAYERS]; // Cant initialize variable length array
    PokerRank winningRank = 0;

    /* Process and Display */
    srand(time(NULL));
    setUnicodeMode();

    initializeDeck(deck);
    displayDeck(deck, L"Original Ordered Deck:");
    shuffleDeck(deck);
    displayDeck(deck, L"Random Shuffled Deck:");
    drawHands(deck, hands, PLAYERS);
    displayHands(hands, PLAYERS, DEFAULT, L"(dealt from top/front of deck)");
    sortHands(hands, PLAYERS);
    displayHands(hands, PLAYERS, DEFAULT, L"sorted");
    rankHands(hands, PLAYERS);
    displayHands(hands, PLAYERS, WITH_RANK, L"ranked");
    winningRank = getWinningRank(hands, PLAYERS);
    displayHands(hands, PLAYERS, winningRank, L"winner(s)");
    rankHands(TEST_HANDS, TEST_HANDS_SIZE);
    displayHands(TEST_HANDS, TEST_HANDS_SIZE, TESTING, L"test");

    return NO_ERRORS;
} // end main
