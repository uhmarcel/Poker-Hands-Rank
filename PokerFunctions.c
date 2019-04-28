
/*---------------------------------------------------------------------------*\

   Source code:  PokerFunctions.c
        Author:  Marcel Riera

   Description:  Source code containing a collection of functions required for
                 testing and assigning poker ranks.

                 This file is required for compilation of cardsShuffle.out, and
                 must be in the same folder with MainCards.c, CardsValidation.c,
                 CardsFunctions.c and Cards.h

\*---------------------------------------------------------------------------*/

#include "Cards.h"

/**
 * Function rankHands
 * Main function in charge of calculating and assigning ranking values
 * to each hand given by input array hands.
 *
 * @param hands     array of hands to calculate rankings from
 * @param players   amount of players, also the array size
 */

void rankHands(Hand hands[], int players) {
    int playerIndex = 0;

    for (playerIndex = 0; playerIndex < players; playerIndex++) {
        PokerRank foundRank = calcPokerRank(hands[playerIndex]);
        hands[playerIndex].handRank = foundRank;
    } // endfor
} // end function

/**
 * Function calcPokerRank
 * Calculates and returns the poker hand rank of a hand.
 *
 * FORMULAS
 *  PokerRank currentPokerRank = STRAIGHT_FLUSH + 1
 *  Used in a loop to test rankings by decrement, starting from the highest
 *  rank plus one, as at the start of the iteration gets decremented by one.
 *
 * @param hand   hand of cards to calculate the ranking from
 * @return       poker rank calculated from the hand
 */

PokerRank calcPokerRank(Hand hand) {
    PokerRank currentPokerRank = STRAIGHT_FLUSH + 1;
    int found = FALSE;

    while (!found && currentPokerRank != HIGH_CARD) {
        currentPokerRank--;
        found = checkHandFor(hand, currentPokerRank);
    } // endwhile
    return currentPokerRank;
} // end function


/**
 * Function getWinningRank
 * Calculates the winning rank from an array of hands with their ranks
 * already calculated.
 *
 * @param hands     array of hands to calculate winning rank from
 * @param players   amount of players, also the array's size
 * @return          winning poker hand rank
 */

PokerRank getWinningRank(const Hand hands[], int players) {
    PokerRank currentBestRank = 0;
    int playerIndex = 0;

    for (playerIndex = 0; playerIndex < players; playerIndex++) {
        if (hands[playerIndex].handRank > currentBestRank) {
            currentBestRank = hands[playerIndex].handRank;
        } // endif
    } // endfor
    return currentBestRank;
} // end function

/**
 * Function checkHandFor
 * Helper function to calculate a hand ranking by redirecting to the different
 * specific rank testers given by the user.
 *
 * @param hand    hand to calculate ranking from
 * @param rank    desired poker rank to test
 * @return        TRUE(1) if the hand has the rank, FALSE(0) otherwise
 */

int checkHandFor(Hand hand, PokerRank rank) {
    if (rank == STRAIGHT_FLUSH) {
        return isStraightFlush(hand.cards);
    } // endif
    else if (rank == FOUR_OF_A_KIND) {
        return isFourOfAKind(hand.cards);
    } // endif
    else if (rank == FULL_HOUSE) {
        return isFullHouse(hand.cards);
    } // endif
    else if (rank == FLUSH) {
        return isFlush(hand.cards);
    } // endif
    else if (rank == STRAIGHT) {
        return isStraight(hand.cards);
    } // endif
    else if (rank == THREE_OF_A_KIND) {
        return isThreeOfAKind(hand.cards);
    } // endif
    else if (rank == TWO_PAIRS) {
        return isTwoPairs(hand.cards);
    } // endif
    else if (rank == ONE_PAIR) {
        return isOnePair(hand.cards);
    } // endif
    return FALSE;
} // end function

/**
 * Function isFlush
 * Test an array of cards to determine if it contains a flush.
 * NOTE: cardIndex started as 1, as the first card was used as reference.
 *
 * @param cards    array of cards to test if contains a flush
 * @return         TRUE if hand has a flush, FALSE otherwise
 */

int isFlush(const Card cards[]) {
    Suit flushSuit = cards[FIRST_CARD].suit;
    int cardIndex = 0;

    for (cardIndex = SECOND_CARD; cardIndex < POKER_HAND_SIZE; cardIndex++) {
        if (cards[cardIndex].suit != flushSuit) {
            return FALSE;
        } // endif
    } // endfor
    return TRUE;
} // end function

/**
 * Function isStraight
 * Test an array of cards to determine if it contains a straight.
 *
 * @param cards    array of cards to test if contains a straight
 * @return         TRUE if hand has a straight, FALSE otherwise
 */

int isStraight(const Card cards[]) {
    Rank currentRank = 0;
    int cardIndex = 0;

    if (cards[FIRST_CARD].rank == ACE) {
        if (cards[SECOND_CARD].rank == TWO) { // If ACE is used as a low value
            currentRank = ACE;   // 1 then check considering first card as a 1.
        } // endif
        else if (cards[SECOND_CARD].rank == TEN) { // If ACE is used as high
            currentRank = NINE;          // value (14) then consider as a 9.
        } // endif                       // (as it would check for T, J, Q, K)
        else {
            return FALSE;
        } // endelse
    } // endif
    else {                              // If not an ACE, then consider the
        currentRank = cards[FIRST_CARD].rank;    // initial card as the start
    } // endelse

    for (cardIndex = SECOND_CARD; cardIndex < POKER_HAND_SIZE; cardIndex++) {
        currentRank++;
        if (cards[cardIndex].rank != currentRank) {
            return FALSE;
        } // endif
    } // endfor
    return TRUE;
} // end function

/**
 * Function isStraightFlush
 * Test an array of cards to determine if it contains a straight flush.
 * It uses isStraight() and isFlush() to determine result.
 *
 * @param cards    array of cards to test if contains a straight flush
 * @return         TRUE if hand has a straight flush, FALSE otherwise
 */

int isStraightFlush(const Card cards[]) {
    return (isStraight(cards) && isFlush(cards));
} // end function

/**
 * Function isFourOfAKind
 * Test an array of cards to determine if it contains a four of a kind.
 *
 * FORMULAS
 *  POKER_HAND_SIZE - 1
 *   The loop ends at the size - 1 as the case considers the last card
 *   to not be part of the four of a kind
 *
 * @param cards    array of cards to test if contains a four of a kind
 * @return         TRUE if hand has a four of a kind, FALSE otherwise
 */

int isFourOfAKind(const Card cards[]) {
    int caseFourTop = TRUE;
    int caseFourBottom = TRUE;
    int cardIndex = 0;

    // Check considering four of a kind starting at beginning
    Rank testRank = cards[FIRST_CARD].rank;
    for (cardIndex = 0; cardIndex < POKER_HAND_SIZE - 1; cardIndex++) {
        if (cards[cardIndex].rank != testRank) {
            caseFourBottom = FALSE;
        } // endif
    } // endfor

    // Check considering four of a kind starting one after beginning
    testRank = cards[SECOND_CARD].rank;
    for (cardIndex = SECOND_CARD; cardIndex < POKER_HAND_SIZE; cardIndex++) {
        if (cards[cardIndex].rank != testRank) {
            caseFourTop = FALSE;
        } // endif
    } // endfor
    return (caseFourBottom || caseFourTop);
} // end function

/**
 * Function isFullHouse
 * Test an array of cards to determine if it contains a full house
 *
 * @param cards    array of cards to test if contains a full house
 * @return         TRUE if hand has a full house, FALSE otherwise
 */

int isFullHouse(const Card cards[]) {
    int caseTop = FALSE;  // Case where pair is at top AAABB
    int caseBottom = FALSE; // Case where pair is at bottom AABBB

    caseTop = (((cards[FIRST_CARD].rank == cards[SECOND_CARD].rank) &&
                (cards[FIRST_CARD].rank == cards[THIRD_CARD].rank)) &&
               (cards[FOURTH_CARD].rank == cards[FIFTH_CARD].rank));

    caseBottom = (((cards[THIRD_CARD].rank == cards[FOURTH_CARD].rank) &&
                   (cards[THIRD_CARD].rank == cards[FIFTH_CARD].rank)) &&
                   (cards[FIRST_CARD].rank == cards[SECOND_CARD].rank));

    return (caseTop || caseBottom);
} // end function

/**
 * Function isThreeOfAKind
 * Test an array of cards to determine if it contains a three of a kind.
 *
 * FORMULAS
 *  for (index = 0; index < 3; index++)
 *   Loop cards up to number less than 3, as each iteration also checks too
 *   values in front, hence at index = 2 it would have checked last possible
 *   combination.
 *
 *  cards[index + 1].rank
 *   To calculate the card next to the current selection, hence +1 in the array.
 *
 *  cards[index + 2].rank
 *   To calculate the card two spots next to the current selection, hence +2 in
 *   the array, for comparison.
 *
 * @param cards    array of cards to test if contains a three of a kind
 * @return         TRUE if hand has a three of a kind, FALSE otherwise
 */

int isThreeOfAKind(const Card cards[]) {
    Rank currentRank = 0;
    int index = 0;

    for (index = 0; index < 3; index++) {
        currentRank = cards[index].rank;
        if ((currentRank == cards[index + 1].rank) &&
            (currentRank == cards[index + 2].rank)) {
            return TRUE;
        } // endif
    } // endfor
    return FALSE;
} // endfunction


/**
 * Function isTwoPairs
 * Test an array of cards to determine if it contains two pairs.
 *
 * @param cards    array of cards to test if contains two pairs
 * @return         TRUE if hand has two pairs, FALSE otherwise
 */

int isTwoPairs(const Card cards[]) {
    int caseTop = FALSE;    // Case non pair card at the top AABBX
    int caseMid = FALSE;    // Case non pair card at middle AAXBB
    int caseBottom = FALSE; // Case non pair card at bottom XAABB

    caseTop = (cards[FIRST_CARD].rank == cards[SECOND_CARD].rank) &&
              (cards[THIRD_CARD].rank == cards[FOURTH_CARD].rank);

    caseMid = (cards[FIRST_CARD].rank == cards[SECOND_CARD].rank) &&
              (cards[FOURTH_CARD].rank == cards[FIFTH_CARD].rank);

    caseBottom = (cards[SECOND_CARD].rank == cards[THIRD_CARD].rank) &&
                 (cards[FOURTH_CARD].rank == cards[FIFTH_CARD].rank);

    return (caseTop || caseMid || caseBottom);
} // end function

/**
 * Function isOnePair
 * Test an array of cards to determine if it contains a pair.
 * NOTE: loop started at 1 as first card is the reference.
 *
 * @param cards    array of cards to test if contains a pair
 * @return         TRUE if hand has a pair, FALSE otherwise
 */

int isOnePair(const Card cards[]) {
    Rank previousRank = cards[FIRST_CARD].rank;
    int cardIndex = 0;

    for (cardIndex = SECOND_CARD; cardIndex < POKER_HAND_SIZE; cardIndex++) {
        if (cards[cardIndex].rank == previousRank) {
            return TRUE;
        } // endif
        previousRank = cards[cardIndex].rank;
    } // endfor
    return FALSE;
} // end function
