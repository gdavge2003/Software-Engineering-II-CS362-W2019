/* -----------------------------------------------------------------------
 * Unit Card Test 2 - testing village
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include "assert.h"


int main () {
    // setup mock data needed for test
    struct gameState *state = malloc(sizeof(struct gameState));
    int numPlayers = 2;
    int *k = kingdomCards(adventurer, smithy, gardens, tribute, council_room, cutpurse, mine, embargo, village,
                          sea_hag);
    int result, i;

    initializeGame(numPlayers, k, 10, state);

    int player = 0;
    int opponent = 1;

    state->whoseTurn = player;
    state->hand[player][0] = village;
    state->handCount[player]++; // note: as of this assignment initialize game doesn't draw cards
    int handPos = 0;

    printf("\nCard Test Suite for Village\n");

    // before data for assertions
    int beforeHandCount = state->handCount[player];
    int beforeDeckCount = state->deckCount[player];
    int beforeDiscardCount = state->discardCount[player];
    int beforeActionCount = state->numActions;

    int beforeHandCountOpponent = state->handCount[opponent];
    int beforeDeckCountOpponent = state->deckCount[opponent];
    int beforeDiscardCountOpponent = state->discardCount[opponent];

    int beforeSupplyCount[10];
    for (i = 0; i < 10; i++)
        beforeSupplyCount[i] = state->supplyCount[k[i]];



    // act
    result = cardEffect(village, 0, 0, 0, state, handPos, 0);

    // assert
    //test ---------------------------
    printf("\n** Test 1: function returns correct value **\n");
    printf("Expected result: 0. Actual result: %d\n", result);
    assert(result == 0);

    //test ---------------------------
    printf("\n** Test 2: player draws 1 card to hand and discards played card **\n");
    printf("Expected hand size: %d. Actual hand size: %d\n", beforeHandCount+1-1, state->handCount[player]);
    assert(beforeHandCount+1-1 == state->handCount[player]);

    //test ---------------------------
    printf("\n** Test 3: player draws 1 card from deck **\n");
    printf("Expected deck size: %d. Actual deck size: %d\n", beforeDeckCount-1, state->deckCount[player]);
    assert(beforeDeckCount-1 == state->deckCount[player]);

    //test ---------------------------
    printf("\n** Test 4: player discard pile now has played card **\n");
    printf("Expected discard size: %d. Actual discard size: %d\n", beforeDiscardCount+1, state->discardCount[player]);
    assert(beforeDiscardCount+1 == state->discardCount[player]);

    //test ---------------------------
    printf("\n** Test 5: player uses an action to play card and gains 2 actions **\n");
    printf("Expected player action(s): %d. Actual action(s): %d\n", state->numActions-1+2, state->numActions);
    assert(state->numActions-1+2 == state->numActions);

    //test ---------------------------
    printf("\n** Test 6: kingdom cards are not affected **\n");
    for (i = 0; i < 10; i++) {
        printf("Kingdom card #%d expected count: %d. Actual count: %d\n", k[i], beforeSupplyCount[i], state->supplyCount[k[i]]);
        assert(beforeSupplyCount[i] == state->supplyCount[k[i]]);
    }

    //test ---------------------------
    printf("\n** Test 7: opponent state does not change **\n");
    printf("Expected opponent hand size: %d. Actual hand size: %d\n", beforeHandCountOpponent, state->handCount[opponent]);
    assert(beforeHandCountOpponent == state->handCount[player]);

    printf("Expected opponent deck size: %d. Actual deck size: %d\n", beforeDeckCountOpponent, state->deckCount[opponent]);
    assert(beforeDeckCountOpponent == state->deckCount[player]);

    printf("Expected opponent size: %d. Actual discard size: %d\n", beforeDiscardCountOpponent, state->discardCount[opponent]);
    assert(beforeDiscardCountOpponent == state->discardCount[player]);
}