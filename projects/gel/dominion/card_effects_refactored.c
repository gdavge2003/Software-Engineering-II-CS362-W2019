#include "card_effects_refactored.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// adventurer card effect
int adventurerEffect(struct gameState *state, int currentPlayer, int handPos) {
    int drawntreasure = 0;
    int cardDrawn;
    int temphand[MAX_HAND];
    int temphandCounter = 0;

    // keep drawing cards til get 2 treasure
    // treasures are recorded in hand, while nontreasure are counted in temphand and not recorded in hand
    while (drawntreasure < 2) {
        drawCard(currentPlayer, state);

        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; // top of hand is most recent draw
        if (cardDrawn == copper || cardDrawn == silver) {
            drawntreasure++;
        }
        else {
            temphand[temphandCounter] = cardDrawn;
            state->handCount[currentPlayer]--; // not treasure; don't count as adding tot hand
            temphandCounter++;
        }
    }

    // discard all cards that were recorded in temphand
    while (temphandCounter-1 >= 0) {
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[temphandCounter-1];
        temphandCounter--;
    }

    // discard this played card
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

// smithy card effect
int smithyEffect(struct gameState *state, int currentPlayer, int handPos) {
    int i;

    // draw 3 cards
    for (i = 0; i < 4; i++) {
        drawCard(currentPlayer, state);
    }

    // discard this played card
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

// village card effect
int villageEffect(struct gameState *state, int currentPlayer, int handPos) {
    // +1 card, +2 actions
    drawCard(currentPlayer, state);
    state->numActions = state->numBuys+2;

    // discard this played card
    discardCard(handPos+1, currentPlayer, state, 0);

    return 0;
}

// council room effect
int council_roomEffect(struct gameState *state, int currentPlayer, int handPos) {
    int i;
    // +4 cards, +1 buy
    for (i = 0; i < 4; i++) {
        drawCard(currentPlayer, state);
    }

    state->numBuys++;

    // +1 card for other players
    for (i = 0; i < state->numPlayers; i++) {
        if (i != currentPlayer)
            drawCard(i, state);
    }

    // discard this played card
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

// remodel card effect
int remodelEffect(struct gameState *state, int currentPlayer, int handPos, int trashChoice, int gainChoice) {
    int i;
    int trashingCard = state->hand[currentPlayer][trashChoice];

    // if trying to gain a card that costs more than +2 of trashed card, refuse action
    if (getCost(gainChoice)+2 > getCost(trashChoice))
        return -1;

    // gain chosen card
    gainCard(gainChoice, state, 0, currentPlayer);

    // discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}