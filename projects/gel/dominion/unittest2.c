/* -----------------------------------------------------------------------
 * Unit Test 2 - testing isGameOver()
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
    int result, i;

    printf("\n** Unit Testing for isGameOver() **\n");

    // Test --------------------------------------------------
    printf("\n** Test 1: game ends w/ no Provinces **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    state->supplyCount[province] = 0;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 1, Actual game result: %d\n", result);
    assert(result == 1);

    // Test --------------------------------------------------
    printf("\n** Test 2: game ends w/ 3 empty supply piles **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    for (i = 0; i < 25; i++)
        state->supplyCount[i] = 1;
    state->supplyCount[steward] = 0;
    state->supplyCount[estate] = 0;
    state->supplyCount[smithy] = 0;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 1, Actual game result: %d\n", result);
    assert(result == 1);

    // Test --------------------------------------------------
    printf("\n** Test 3: game continues with 2 supply piles empty **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    for (i = 0; i < 25; i++)
        state->supplyCount[i] = 1;
    state->supplyCount[duchy] = 0;
    state->supplyCount[estate] = 0;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 0, Actual game result: %d\n", result);
    assert(result == 0);

    free(state);
    return 0;
}