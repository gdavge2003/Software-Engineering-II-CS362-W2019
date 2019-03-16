/* -----------------------------------------------------------------------
 * Unit Card Test 3 - testing council_room
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include "assert.h"


void assertValues(int a, int b) {
    if (a == b)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
}

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
    state->hand[player][0] = council_room;
    state->handCount[player]++; // note: as of this assignment initialize game doesn't draw cards
    int handPos = 0;

    printf("\nCard Test Suite for Council Room\n");

    // before data for assertions
    int beforeHandCount = state->handCount[player]; // player should have 10 cards after initialization
    int beforeDeckCount = state->deckCount[player];
    int beforeDiscardCount = state->discardCount[player];
    int beforeBuyCount = state->numBuys = 1;

    int beforeHandCountOpponent = state->handCount[opponent];
    int beforeDeckCountOpponent = state->deckCount[opponent];
    int beforeDiscardCountOpponent = state->discardCount[opponent];

    int beforeSupplyCount[10];
    for (i = 0; i < 10; i++)
        beforeSupplyCount[i] = state->supplyCount[k[i]];

    // act
    result = cardEffect(council_room, 0, 0, 0, state, handPos, 0);

    // assert
    //test ---------------------------
    printf("\n** Test 1: function returns correct value **\n");
    printf("Expected result: 0. Actual result: %d\n", result);
    assertValues(result, 0);

    //test ---------------------------
    printf("\n** Test 2: player draws 4 card to hand and discards played card **\n");
    printf("Expected hand size: %d. Actual hand size: %d\n", beforeHandCount+4-1, state->handCount[player]);
    assertValues(beforeHandCount+4-1, state->handCount[player]);

    //test ---------------------------
    printf("\n** Test 3: player draws 4 card from deck **\n");
    printf("Expected deck size: %d. Actual deck size: %d\n", beforeDeckCount-4, state->deckCount[player]);
    assertValues(beforeDeckCount-4, state->deckCount[player]);

    //test ---------------------------
    printf("\n** Test 4: player discard pile now has played card **\n");
    printf("Expected discard size: %d. Actual discard size: %d\n", beforeDiscardCount+1, state->discardCount[player]);
    assertValues(beforeDiscardCount+1, state->discardCount[player]);

    //test ---------------------------
    printf("\n** Test 5: player gains a buy **\n");
    printf("Expected player buy(s): %d. Actual buy(s): %d\n", beforeBuyCount+1, state->numBuys);
    assertValues(beforeBuyCount+1, state->numBuys);

    //test ---------------------------
    printf("\n** Test 6: kingdom cards are not affected **\n");
    for (i = 0; i < 10; i++) {
        printf("Kingdom card #%d expected count: %d. Actual count: %d\n", k[i], beforeSupplyCount[i], state->supplyCount[k[i]]);
        assertValues(beforeSupplyCount[i], state->supplyCount[k[i]]);
    }

    //test ---------------------------
    printf("\n** Test 7: opponent draws a card and state changes **\n");
    printf("Expected opponent hand size: %d. Actual hand size: %d\n", beforeHandCountOpponent+1, state->handCount[opponent]);
    assertValues(beforeHandCountOpponent+1, state->handCount[opponent]);

    printf("Expected opponent deck size: %d. Actual deck size: %d\n", beforeDeckCountOpponent-1, state->deckCount[opponent]);
    assertValues(beforeDeckCountOpponent-1, state->deckCount[opponent]);

    //test ---------------------------
    printf("\n** Test 8: opponent does not discard any card **\n");
    printf("Expected opponent discard size: %d. Actual discard size: %d\n", beforeDiscardCountOpponent, state->discardCount[opponent]);
    assertValues(beforeDiscardCountOpponent, state->discardCount[opponent]);
}