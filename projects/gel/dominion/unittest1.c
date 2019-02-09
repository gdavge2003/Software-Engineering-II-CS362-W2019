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

    printf("\n** Test 2: coins and bonus correctly calculated **\n");
    // arrange mock data
    state->hand[player][0] = copper;
    state->hand[player][1] = silver;
    state->hand[player][2] = gold;
    int bonus = 5;

    // act
    updateCoins(player, state, bonus);

    // assert
    printf("Expected coins: %d, Actual coins: %d\n", 1+2+3+bonus, state->coins);
    assert(state->coins == (1+2+3+bonus));

    printf("\n** Test 3: multiple iterations on same coin correctly calculated **\n");
    // arrange mock data
    state->hand[player][0] = gold;
    state->hand[player][1] = gold;
    state->hand[player][2] = gold;

    // act
    updateCoins(player, state, 0);

    // assert
    printf("Expected coins: %d, Actual coins: %d\n", 3+3+3, state->coins);
    assert(state->coins == 9);

    printf("\n** Test 4: hand size should remain the same **\n");
    // arrange mock data
    state->hand[player][0] = gold;
    state->hand[player][1] = province;
    state->hand[player][2] = steward;

    // act
    updateCoins(player, state, 0);

    // assert
    printf("Expected coins: %d, Actual coins: %d\n", 3, state->coins);
    assert(state->coins == 3);
    printf("Expected hand size: %d, Actual hand size: %d\n", 3, state->handCount[player]);

    free(state);
    return 0;
}