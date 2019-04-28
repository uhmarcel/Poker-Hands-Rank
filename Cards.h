
/*---------------------------------------------------------------------------*\

     File name:  Cards.h
        Author:  Marcel Riera

   Description:  Header file containing constant declarations along with
                 function prototypes required for the program.

                 This file is required for compilation of cardsShuffle.out, and
                 must be in the same folder with MainCards.c, CardsValidation.c,
                 CardsFunctions.c and CardsFunctions.c

\*---------------------------------------------------------------------------*/

#include <stdio.h>               // Required for input and output
#include <stdlib.h>              // Required for rand() and exit()

    /* Constants Declaration */

#define CARD_NUMBERS_AMOUNT 13   // Number of cars of one type
#define CARD_TYPE_AMOUNT 4       // Number of types in a deck

#define HEART_SYMBOL 0x2665      // UNICODE heart representation
#define DIAMOND_SYMBOL 0x2666    // UNICODE diamond representation
#define CLUBS_SYMBOL 0x2663      // UNICODE clubs representation
#define SPADES_SYMBOL 0x2660     // UNICODE spades representation

#define VALID_ARGUMENTS_AMOUNT 3 // Expected valid argument amount
#define MIN_ARGV_LEN 1           // Minimum string length for a valid argument
#define MAX_ARG_LEN 2            // Maximum string length for a valid argument
#define MIN_INPUT_RANGE 1        // Minimum numeric value for valid input
#define MAX_INPUT_RANGE 13       // Maximum numeric value for valid input

#define CARDS_PER_HAND_INDEX 1   // Hand size argument index for argv
#define PLAYER_AMOUNT_INDEX 2    // Player amount argument index for argv

#define END_OF_STRING '\0'       // End of string character
#define FIRST_CHAR_INTEGER '0'   // First char number representation
#define LAST_CHAR_INTEGER '9'    // Last char number representation

#define DECK_SIZE 52             // Size of a full deck of cards
#define POKER_HAND_SIZE 5        // Standard size for poker game
#define TEST_HANDS_SIZE 9        // Size of hands array for testing

#define DEFAULT -1               // Parameter to display hands
#define WITH_RANK -2             // Parameter to display hands with rank
#define TESTING -3               // Parameter to display testing hands

#define TRUE 1                   // True for boolean functions
#define FALSE 0                  // False for boolean functions

#define VALID_INPUT 1            // For succesful validation
#define INVALID_INPUT -1         // For unsuccesful validation

#define NO_ERRORS 0              // Exit successful

    /* Enum & Struct Definitions */

typedef enum suit {HEART, DIAMOND, CLUBS, SPADES} Suit;

typedef enum rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                   JACK, QUEEN, KING} Rank;

typedef enum pokerRank {HIGH_CARD, ONE_PAIR, TWO_PAIRS,
                        THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE,
                        FOUR_OF_A_KIND, STRAIGHT_FLUSH} PokerRank;

enum handIndex {FIRST_CARD, SECOND_CARD, THIRD_CARD, FOURTH_CARD, FIFTH_CARD};

typedef struct card {
    Rank rank;
    Suit suit;
} Card;

typedef struct hand {
    Card cards[POKER_HAND_SIZE];
    PokerRank handRank;
} Hand;

    /* Card Display Representation */

static const char CARD_NUM_SYMBOL[] = {'A', '2', '3', '4', '5', '6', '7',
                                       '8', '9', 'T', 'J', 'Q', 'K'};

static const int CARD_TYPE_SYMBOL[] = {HEART_SYMBOL, DIAMOND_SYMBOL,
                                        CLUBS_SYMBOL, SPADES_SYMBOL};

static const wchar_t *POKER_RANK_STRING[] = {L"High Card", L"One Pair",
               L"Two Pairs", L"Three of a Kind", L"Straight", L"Flush",
               L"Full House", L"Four of a Kind", L"Straight Flush"};

static Hand TEST_HANDS[TEST_HANDS_SIZE] = {
    {{{TWO, DIAMOND}, {THREE, CLUBS}, {FOUR, DIAMOND}, {SIX, SPADES},
    {QUEEN, HEART}}, 0},    // Test hand no. 1
    {{{FOUR, HEART}, {FIVE, HEART}, {FIVE, DIAMOND}, {SEVEN, HEART},
    {TEN, SPADES}}, 0},     // Test hand no. 2
    {{{THREE, DIAMOND}, {THREE, HEART}, {TEN, CLUBS}, {TEN, DIAMOND},
    {QUEEN, CLUBS}}, 0},    // Test hand no. 3
    {{{THREE, DIAMOND}, {THREE, HEART}, {THREE, SPADES}, {TEN, DIAMOND},
    {QUEEN, CLUBS}}, 0},    // Test hand no. 4
    {{{ACE, SPADES}, {TWO, DIAMOND}, {THREE, CLUBS}, {FOUR, DIAMOND},
    {FIVE, DIAMOND}}, 0},   // Test hand no. 5
    {{{TWO, CLUBS}, {THREE, CLUBS}, {FOUR, CLUBS}, {SIX, CLUBS},
    {QUEEN, CLUBS}}, 0},    // Test hand no. 6
    {{{THREE, DIAMOND}, {THREE, HEART}, {THREE, SPADES}, {TEN, DIAMOND},
    {TEN, CLUBS}}, 0},      // Test hand no. 7
    {{{THREE, DIAMOND}, {THREE, HEART}, {THREE, SPADES}, {THREE, CLUBS},
    {QUEEN, CLUBS}}, 0},    // Test hand no. 8
    {{{ACE, DIAMOND}, {TEN, DIAMOND}, {JACK, DIAMOND}, {QUEEN, DIAMOND},
    {KING, DIAMOND}}, 0},   // Test hand no. 9
};

    /* Function Prototypes */

// Input Validation
int validateArguments();
int validateArgumentsAmount(int argumentAmount);
int validateArgument(char *argument);
int isCharValidInteger(char charToTest);
int validateInputCombination(int cardsPerHand, int players);
int stringToInt(char *string);
void invalidInputTerminate();

// Process
void initializeDeck(Card *deck);
void shuffleDeck(Card *deck);
void swapCards(Card *deck, int index1, int index2);
void drawHands(const Card deck[], Hand hands[], int players);
void sortHands(Hand hands[], int players);
int getComparable(Card card);
void rankHands(Hand hands[], int players);
int checkHandFor(Hand hand, PokerRank rank);
PokerRank calcPokerRank(Hand hand);
PokerRank getWinningRank(const Hand hands[], int players);
int isFlush(const Card cards[]);
int isStraight(const Card cards[]);
int isStraightFlush(const Card cards[]);
int isFourOfAKind(const Card cards[]);
int isFullHouse(const Card cards[]);
int isThreeOfAKind(const Card cards[]);
int isTwoPairs(const Card cards[]);
int isOnePair(const Card cards[]);

// Display
void setUnicodeMode();
void displayCard(Card card);
void displayDeck(const Card deck[], wchar_t *message);
void displayHands(const Hand hands[], int players, int mode, wchar_t *message);
