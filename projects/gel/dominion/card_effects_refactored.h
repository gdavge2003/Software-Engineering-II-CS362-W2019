#ifndef GEL_CARD_EFFECTS_REFACTORED_H
#define GEL_CARD_EFFECTS_REFACTORED_H

#include "dominion.h"

int adventurerEffect(struct gameState *state, int currentPlayer, int handPos);
int smithyEffect(struct gameState *state, int currentPlayer, int handPos);
int villageEffect(struct gameState *state, int currentPlayer, int handPos);
int council_roomEffect(struct gameState *state, int currentPlayer, int handPos);
int remodelEffect(struct gameState *state, int currentPlayer, int handPos, int trashChoice, int gainChoice);

#endif //GEL_CARD_EFFECTS_REFACTORED_H