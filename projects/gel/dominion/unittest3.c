/* -----------------------------------------------------------------------
 * Unit Test 3 - testing whoseTurn()
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
    int result;

    printf("\n** Unit Testing for whoseTurn() **\n");

    // Test --------------------------------------------------
    printf("\n** Test 1: returns correct value in state **\n");
    // arrange mock data
    state->whoseTurn = 0;

    // act
    result = whoseTurn(state);

    // assert
    printf("Expected whoseTurn: 0, Actual whoseTurn result: %d\n", result);
    assert(result == 1);

    free(state);
    return 0;
}