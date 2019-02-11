/* -----------------------------------------------------------------------
 * Unit Card Test 4 - testing adventurer
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
    state->hand[player][0] = adventurer;
    state->handCount[player]++; // note: as of this assignment initialize game doesn't draw cards
    int handPos = 0;

    printf("\nCard Test Suite for Adventurer\n");

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
    assert(result == 0);

    //test ---------------------------
    printf("\n** Test 2: player should end with 2 more cards in their hands and discards the played card **\n");
    printf("Expected hand size: %d. Actual hand size: %d\n", beforeHandCount+2-1, state->handCount[player]);
    assert(beforeHandCount+2-1 == state->handCount[player]);

    //test ---------------------------
    printf("\n** Test 3: player should have 2 more treasure cards in hand than before **\n");
    int treasures = 0;
    int cardid;
    for (i = 0; i < 2; i++)
        cardid = state->hand[player][i];
        if (cardid == copper || cardid == silver || cardid == gold)
            treasures++;

    printf("Expected treasures in hand: 2. Actual treasures: %d\n", treasures);
    assert(2 == treasures);

    //test ---------------------------
    printf("\n** Test 4: player discard pile now has played card **\n");
    printf("Expected discard size: %d. Actual discard size: %d\n", beforeDiscardCount+1, state->discardCount[player]);
    assert(beforeDiscardCount+1 == state->discardCount[player]);

    //test ---------------------------
    printf("\n** Test 5: player gains a buy **\n");
    printf("Expected player buy(s): %d. Actual buy(s): %d\n", beforeBuyCount+1, state->numBuys);
    assert(beforeBuyCount+1 == state->numActions);

    //test ---------------------------
    printf("\n** Test 6: player total cards should not change **\n");
    printf("Expected player cards: %d. Actual player cards: %d\n",
            beforeDeckCount+beforeHandCount+beforeDiscardCount, state->handCount[player]+state->deckCount[player]+state->discardCount[player]);
    assert(beforeDeckCount+beforeHandCount+beforeDiscardCount == state->handCount[player]+state->deckCount[player]+state->discardCount[player]);

    //test ---------------------------
    printf("\n** Test 7: kingdom cards are not affected **\n");
    for (i = 0; i < 10; i++) {
        printf("Kingdom card #%d expected count: %d. Actual count: %d\n", k[i], beforeSupplyCount[i], state->supplyCount[k[i]]);
        assert(beforeSupplyCount[i] == state->supplyCount[k[i]]);
    }

    //test ---------------------------
    printf("\n** Test 8: opponent draws a card **\n");
    printf("Expected opponent hand size: %d. Actual hand size: %d\n", beforeHandCountOpponent+1, state->handCount[opponent]);
    assert(beforeHandCountOpponent+1 == state->handCount[opponent]);

    printf("Expected opponent deck size: %d. Actual deck size: %d\n", beforeDeckCountOpponent-1, state->deckCount[opponent]);
    assert(beforeDeckCountOpponent-1 == state->deckCount[opponent]);

    //test ---------------------------
    printf("\n** Test 9: opponent does not discard a card **\n");
    printf("Expected opponent discard size: %d. Actual discard size: %d\n", beforeDiscardCountOpponent, state->discardCount[opponent]);
    assert(beforeDiscardCountOpponent == state->discardCount[opponent]);
}