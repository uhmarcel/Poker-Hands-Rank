
/*---------------------------------------------------------------------------*\

   Source code:  CardsFunctions.c
        Author:  Marcel Riera

   Description:  Source code containing a collection of functions required for
                 processing and output display of the program.

                 This file is required for compilation of cardsShuffle.out, and
                 must be in the same folder with MainCards.c, CardsValidation.c,
                 pokerFunctions.c and Cards.h

\*---------------------------------------------------------------------------*/

#include "Cards.h"      // Required source code header
#include <locale.h>     // Required to set Unicode mode

                    /* Functions */
/**
 * Function setUnicodeMode
 * Function required to display UNICODE graphics in console programs.
 * Retrieved from: https://stackoverflow.com/questions/2231211/c-programming
 * -unicode-and-the-linux-terminal
 */

void setUnicodeMode() {
    setlocale(LC_ALL, "");
} // end function

/**
 * Function initializeDeck
 * Initializes a deck array of 52 elements by arranging all cards in order
 * (initializing cards from 0 to 52).
 * @param deck     Pointer for the deck of arrays
 */

void initializeDeck(Card *deck) {
    int index = 0;
    for (index = 0; index < DECK_SIZE; index++) {
        Card currentCard = {};
        currentCard.rank = index % CARD_NUMBERS_AMOUNT;
        currentCard.suit = index / CARD_NUMBERS_AMOUNT;
        deck[index] = currentCard;
    } // endfor
} // end function

/**
 * Function displayDeck
 * Displays a formatted representation of the current state of the deck.
 *
 * FORMULAS:
 * index % CARD_NUMBERS_AMOUNT == 0
 *    Use of the mod operator to display a line break every 13 cards.
 *
 * NOTE: wprintf is used instead of conventional print as display mode is set
 * to Unicode long char.
 * @param deck[]  Integer array deck of cards to be displayed
 */

void displayDeck(const Card deck[], wchar_t *message) {
    int index = 0;

    wprintf(L"%ls", message);
    for (index = 0; index < DECK_SIZE; index++) {
        if (index % CARD_NUMBERS_AMOUNT == 0) {
            wprintf(L"\n");
        } // endif
        displayCard(deck[index]);
    } // endfor
    wprintf(L"\n\n");
} // end function

/**
 * Function displayCard
 * Displays a formatted representation of the current card.
 *
 * NOTE: wprintf is used instead of conventional print in order to print
 * Unicode characters with long char format.
 * @param card  Integer from 0-51 representing a deck's card
 */

void displayCard(Card card) {
    wprintf(L"[ %c-%lc ] ", CARD_NUM_SYMBOL[card.rank],
                            CARD_TYPE_SYMBOL[card.suit]);
} // end function

/**
 * Function shuffleDeck
 * Shuffles the current configuration of a deck in accordance with the Knuth
 * (or Fisher-Yates) shuffle algorithm.
 *
 * FORMULAS:
 *   "To shuffle an array a of n elements (indices 0..n-1):
 *    for i from n−1 downto 1 do
 *      j ← random integer such that 0 ≤ j ≤ i
 *      exchange a[j] and a[i]"
 * Retrieved from: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
 *
 * @param *deck  Pointer to an array deck of cards to be shuffled
 */

void shuffleDeck(Card *deck) {
    int index = 0;
    int randomIndex = 0;

    for (index = DECK_SIZE - 1; index > 0; index--) {  //
        randomIndex = rand() % (index + 1);            // Knuth Algorithm
        swapCards(deck, index, randomIndex);           //
    } // endfor
} // end function

/**
 * Function swapElements
 * Swaps two elements at given indexes from an input array.
 * @param *array  Pointer to the array for the swap.
 * @param index1  Index of first element to be swapped.
 * @param index2  Index of second element to be swapped.
 */

void swapCards(Card *array, int index1, int index2) {
    Card *firstPtr = array + index1;
    Card *secondPtr = array + index2;
    Card tmp = *firstPtr;
    *firstPtr = *secondPtr;
    *secondPtr = tmp;
} // end function

/**
 * Function drawHands
 * Draw cards from an array deck to each player's hand.
 *
 * FORMULAS
 *  currentPlayer = deckIndex % players
 *     Use of the mod operator to switch which player gets the current card
 *     being drawn from the deck. Every new card is drawn to a different
 *     player.
 *  handIndex = deckIndex / players
 *     The complement operation, results in the current card position being
 *     drawn. Every time all player get one card, increases by one.
 *
 * @param deck[]    Integer array deck of cards to be drawn from
 * @param hands     Array of hands to draw to
 * @param players   Integer amount of players
 */

void drawHands(const Card deck[], Hand hands[], int players) {
    int cardsToDraw = players * POKER_HAND_SIZE;
    int deckIndex = 0;
    int currentPlayer = 0;
    int handIndex = 0;

    for (deckIndex = 0; deckIndex < cardsToDraw; deckIndex++) {
        currentPlayer = deckIndex % players;
        handIndex = deckIndex / players;
        hands[currentPlayer].cards[handIndex] = deck[deckIndex];
    } // endfor
} // end function

/**
 * Function displayHands
 * Displays cards from all player's hands in a formatted representation.
 * argument mode can be set to DEFAULT, WITH_RANGE, TESTING or can be used
 * to display the winning hand by specifying the winning rank number in the
 * slot.
 *
 * NOTE: wprintf is used instead of conventional print as display mode is set
 * to Unicode long char.
 * @param *hands    Pointer to beginning of players hands
 * @param players   Integer amount of players
 * @param mode      Determines how to display the output
 * @param msg       Header string to print before display
 */

void displayHands(const Hand hands[], int players, int mode, wchar_t *msg) {
    int playerIndex = 0;
    int handIndex = 0;

    wprintf(L"Player Hands: %ls", msg);
    for (playerIndex = 0; playerIndex < players; playerIndex++) {
        if (mode == TESTING) {
            wprintf(L"\nHand: ");
        } // endif
        else {
            wprintf(L"\nPlayer  %d] - ", playerIndex + 1);
        } // endelse

        for (handIndex = 0; handIndex < POKER_HAND_SIZE; handIndex++) {
            displayCard(hands[playerIndex].cards[handIndex]);
        } // endfor

        if (mode != DEFAULT) {
            wprintf(L" - %ls", POKER_RANK_STRING[hands[playerIndex].handRank]);
            if (mode != WITH_RANK && mode != TESTING) {
                PokerRank winningRank = mode;
                if (hands[playerIndex].handRank == winningRank) {
                    wprintf(L" - winner");
                } // endif
            } // endif
        } // endif
    } // endfor
    wprintf(L"\n\n");
} // end function

/**
 * Function sortHands
 * Sorts cards in each hand given by input array hands in increasing order.
 * It sorts the cards in acordance with a comparable value given by function
 * getComparable()
 * Based of http://www.geeksforgeeks.org/sorting-algorithms/
 *
 * FORMULA
 *  handSize - handIdx - 1
 *   maximum position to travel, as remaining elements are already sorted
 *
 *  sortIdx + 1
 *   to get the next card in the array and use for comparison
 *
 * @param hands     array of hands to be sorted
 * @param players   amount of players, also size of the array
 */

void sortHands(Hand hands[], int players) {
    int handSize = POKER_HAND_SIZE;
    int playerIdx = 0;
    int handIdx = 0;
    int sortIdx = 0;

    for (playerIdx = 0; playerIdx < players; playerIdx++) {
        for (handIdx = 0; handIdx < handSize - 1; handIdx++) {
            for (sortIdx = 0; sortIdx < handSize - handIdx - 1; sortIdx++) {
                int cardA = getComparable(hands[playerIdx].cards[sortIdx]);
                int cardB = getComparable(hands[playerIdx].cards[sortIdx + 1]);
                if (cardA > cardB) {
                    swapCards(hands[playerIdx].cards, sortIdx, sortIdx + 1);
                } // endif
            } // endfor
        } // endfor
    } // endfor
} // end function

/**
 * Function getComparable
 * Returns an integer value for a given card to be used as comparison for
 * sorting.
 *
 * @param card   card from which to calculate comparable value
 */

int getComparable(Card card) {
    return (card.rank * CARD_TYPE_AMOUNT) + card.suit;
} // end function
