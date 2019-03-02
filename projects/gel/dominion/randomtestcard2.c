/* -----------------------------------------------------------------------
 * Automated Random Test Generator for smithy
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define TESTRUNCOUNT 100000
#define NUMPLAYERS 2


int main() {
    srand(time(NULL));
    int i;

    // variables for game state
    struct gameState *state = malloc(sizeof(struct gameState));
    long seed = rand();
    int *k = kingdomCards(smithy, great_hall, village, mine, cutpurse,
            tribute, feast, council_room, gardens, adventurer);
    int player = 0;

    // variables for tracking values for testing
    int handPos;
    int initdeckCount;

    int handBefore;
    int handAfter;
    int deckBefore;
    int deckAfter;
    int playedBefore;
    int playedAfter;
    int actionBefore;
    int actionAfter;

    // variables for test analysis
    int handMiscount = 0;
    int deckMiscount = 0;
    int playedMiscount = 0;
    int actionMiscount = 0;
    int passingTestCount = 0;
    int isPassing;

    // test generator
    printf("\nRunning random generator tests for smithy...\n");
    for (i = 0; i < TESTRUNCOUNT; i++) {

        // setup game state with some random variance
        initializeGame(NUMPLAYERS, k, seed, state);
        state->whoseTurn = player;
        state->hand[player][0] = smithy;
        state->handCount[player]++;
        handPos = 0;

        initdeckCount = rand() % (MAX_DECK + 1);
        state->deckCount[0] = initdeckCount;

        // record state before action is played
        handBefore = state->handCount[0];
        deckBefore = state->deckCount[0];
        playedBefore = state->playedCardCount;
        actionBefore = state->numActions;

        // action
        cardEffect(smithy, 0, 0, 0, state, handPos, 0);

        // record state after action is played
        deckAfter = state->deckCount[0];
        handAfter = state->handCount[0];
        playedAfter = state->playedCardCount;
        actionAfter = state->numActions;

        // generate and record test results
        // hand assertion
        isPassing = 1;
        if (handAfter != (handBefore + 3 - 1)) {
            handMiscount++;
            isPassing = 0;
        }

        // deck assertion
        if (deckBefore < 3) {
            if (deckAfter != 0) {
                deckMiscount++;
                isPassing = 0;
            }
        }
        else {
            if (deckAfter != (deckBefore - 3)) {
                deckMiscount++;
                isPassing = 0;
            }
        }

        // played assertion
        if (playedAfter != (playedBefore + 1)) {
            playedMiscount++;
            isPassing = 0;
        }

        // action assertion
        if (actionAfter != (actionBefore - 1)) {
            actionMiscount++;
            isPassing = 0;
        }

        if (isPassing == 1)
            passingTestCount++;
    }

    // print summary of test results
    printf("# of Tests Ran: %d\n", i);
    printf("# of Tests Passed: %d\n", passingTestCount);
    printf("# of Cards Drawn Miscount: %d\n", handMiscount);
    printf("# of Deck Size Miscount: %d\n", deckMiscount);
    printf("# of Played Cards Miscount: %d\n", playedMiscount);
    printf("# of Action Miscount: %d\n\n", actionMiscount);

    free(state);

    return 0;
}