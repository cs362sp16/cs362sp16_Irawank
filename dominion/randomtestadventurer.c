#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define MAX_TEST 20

int main (int argc, char* argv[]) 
{
	int numberOfPlayer = 2; 
	int randomSeed, handCounts, deckCounts, discardCounts, cardPositions;
	int initTreasure, curTreasure;
	int i, j;
	int player;
	int card;
	time_t t;
	
	if (argc == 2) 
	{
		printf ("TAKE INPUT SEED\n");
		randomSeed = atoi(argv[1]);
	}
	else 
	{
		printf ("TAKE RANDOMIZED SEED\n");
		randomSeed = rand()%20 + 1;
	}
	
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};
	cardPositions = 0;
	srand((unsigned) time(&t));
	struct gameState *game;
	for (i = 0; i < MAX_TEST; i++) 
	{
		initTreasure = 0;
		curTreasure = 0;	
		game = newGame();
		
		// Initialize the game
		initializeGame(numberOfPlayer, kingdomCards, randomSeed, game);
		player = game->whoseTurn;
		handCounts = rand()%20;
		game->handCount[player] = handCounts;
		
		// Put the Adventurer Card to hand 
		game->hand[player][0] = adventurer;
		for (j = 1; j < handCounts; j++)
		{
			card = rand()%27;
			// Calculate the number of treasure 
			if (card == copper || card == silver || card == gold) 
			{
				initTreasure++;
			}
			game->hand[player][j] = card;
		}
		deckCounts = rand()%30 + 1;
		printf ("DECK COUNTS: %d\n",deckCounts);
		game->deckCount[player] = deckCounts;
		for (j = 0; j < (deckCounts - 2); j++)
		{
			card = rand() % 27;
			game->deck[player][j] = card;
		}
		discardCounts = rand()%10;
		game->discardCount[player] = discardCounts;
		game->discard[player][0] = gold;
		game->discard[player][1] = silver;
		for (j = 2; j < (discardCounts -1); j++)
		{
			card = rand() % 27;
			game->discard[player][j] = card;
		}
		// Use the Adventurer Card 
		cardEffect(adventurer, 0, 0, 0, game, cardPositions, 0);
		for (j = 0; j< game->handCount[player]; j++) 
		{
			// Calculate the number of treasure in hand
			if (game->hand[player][j] == copper || game->hand[player][j] == silver || game->hand[player][j] == gold) 
			{
				curTreasure++;
			}
		}
		
		// Check if we are be able to get two treasure card 
		if (curTreasure == (initTreasure + 2))
		{
			printf("TEST SUCCESSFUL: GET TWO TREASURE CARDS\n");
		}
		else {
			printf("TEST FAILED: CANNOT GET TWO TREASURE CARDS\n");
		}
		
		// Check if we got the right hand counts 
		if (game->handCount[player] == (handCounts + 2 - 1)) 
		{
			printf("TEST SUCCESSFUL: GET THE RIGHT HAND COUNTS\n");
		}
		else 
		{
			printf("TEST FAILED: GET THE WRONG HAND COUNTS\n");
		}
		
		// Check if we got the right played card counts 
		if (game->playedCardCount == 1) 
		{
			printf("TEST SUCCESSFUL: GET THE RIGHT PLAYED CARD COUNTS\n");
		}
		else 
		{
			printf("TEST FAILED: GET THE WRONG PLAYED CARD COUNTS\n");
		}
		// Free the memory 
		free(game);
	}	
	return 0;
}