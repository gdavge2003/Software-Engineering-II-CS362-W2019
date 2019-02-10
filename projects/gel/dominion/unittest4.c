/* -----------------------------------------------------------------------
 * Unit Test 4 - testing kingdomCards()
 * Note: personally, I feel this method itself should have more
 * functionality to try & catch errors, but given the implementation,
 * the UNIT testing of this function provides complete coverage.
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
    int *result;
    int i;

    printf("\n** Unit Testing for kingdomCards() **\n");

    // Test --------------------------------------------------
    printf("\n** Test 1: kingdom cards stored correctly **\n");
    // arrange mock data
    int k1 = adventurer;
    int k2 = smithy;
    int k3 = council_room;
    int k4 = feast;
    int k5 = gardens;
    int k6 = mine;
    int k7 = village;
    int k8 = ambassador;
    int k9 = sea_hag;
    int k10 = salvager;

    int* k = malloc(10 * sizeof(int));
    k[0] = k1;
    k[1] = k2;
    k[2] = k3;
    k[3] = k4;
    k[4] = k5;
    k[5] = k6;
    k[6] = k7;
    k[7] = k8;
    k[8] = k9;
    k[9] = k10;

    // act
    result = kingdomCards(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10);

    // assert
    for (i = 0; i < 10; i++) {
        printf("Expected card id: %d, Actual card id: %d\n", k[i], result[i]);
        assert(k[i] == result[i]);
    }

    // cleanup
    free k;
    free result;


    // Test --------------------------------------------------
    printf("\n** Test 2: sets correct number of kingdom cards **\n");
    // arrange mock data
    int k1 = adventurer;
    int k2 = smithy;
    int k3 = council_room;
    int k4 = feast;
    int k5 = gardens;
    int k6 = mine;
    int k7 = village;
    int k8 = ambassador;
    int k9 = sea_hag;
    int k10 = salvager;

    // act
    result = kingdomCards(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10);

    // assert
    printf("Expected 10 kingdom cards, Actual kingdom cards: %d\n", sizeof(result)/sizeof(int))
    assert(10 == sizeof(result)/sizeof(int));

    // clean up
    free result;

    free(state);
    return 0;
}