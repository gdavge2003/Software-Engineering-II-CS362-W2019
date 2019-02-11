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


void assertValues(int a, int b) {
    if (a == b)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
}

int main() {
    // setup mocked data needed for each test
    struct gameState *state = malloc(sizeof(struct gameState));
    int result, i;

    printf("\n** Unit Testing for isGameOver() **\n");

    // Test --------------------------------------------------
    printf("\n** Test 1: game ends w/ no Provinces **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    for (i = 0; i < 25; i++)
        state->supplyCount[i] = 1;
    state->supplyCount[province] = 0;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 1, Actual game result: %d\n", result);
    assertValues(result, 1);

    // Test --------------------------------------------------
    printf("\n** Test 2: game continues with 1 Province remaining **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    for (i = 0; i < 25; i++)
        state->supplyCount[i] = 1;
    state->supplyCount[province] = 1;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 0, Actual game result: %d\n", result);
    assertValues(result, 0);

    // Test --------------------------------------------------
    printf("\n** Test 3: game ends w/ 3 empty supply piles **\n");
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
    assertValues(result, 1);

    // Test --------------------------------------------------
    printf("\n** Test 4: game continues with 2 supply piles empty **\n");
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
    assertValues(result, 0);

    // Test --------------------------------------------------
    printf("\n** Test 5: game continues with 0 supply piles empty **\n");
    // arrange mock data
    memset(state->supplyCount, '\0', sizeof(state->supplyCount));
    for (i = 0; i < 25; i++)
        state->supplyCount[i] = 1;

    // act
    result = isGameOver(state);

    // assert
    printf("Expected game result: 0, Actual game result: %d\n", result);
    assertValues(result, 0);

    free(state);
    return 0;
}