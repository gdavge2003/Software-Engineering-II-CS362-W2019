/* -----------------------------------------------------------------------
 * Unit Test 1 - testing updateCoins()
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main() {
    // setup mocked data needed for each test
    struct gameState *state = malloc(sizeof(struct gameState));
    int player = 1;
    memset(state->hand[player], '\0', sizeof(state->hand[player]));
    state->handCount[player] = 3;

    printf("\n** Unit Testing for updateCoins() **\n");

    printf("\n** Test 1: correctly resets & no coins **\n");
    // arrange mock data
    state->coins = 5;
    state->hand[player][0] = curse;
    state->hand[player][1] = cutpurse;
    state->hand[player][2] = province;

    // act
    updateCoins(player, state, 0);

    // assert
    printf("Expected coins: 0, Actual coins: %d\n", state->coins);
    assert(state->coins == 0);



    free(state);
    return 0;
}