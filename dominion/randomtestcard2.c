/* 
* Krisna Irawan 
* CS 362 
* Assignment 3  
* Random Testing the Council Room Card Function
*/

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
		game = newGame();
		
		// Initialize the game
		initializeGame(numberOfPlayer, kingdomCards, randomSeed, game);
		player = game->whoseTurn;
		handCounts = rand()%20 + 2;
		game->handCount[player] = handCounts;
		
		// Put the Council Room Card to hand 
		game->hand[player][cardPositions] = council_room;
		for (j = 1; j < handCounts; j++) 
		{
			card = rand() % 27;
			game->hand[player][j] = card;
		}
		deckCounts = rand() % 30 + 5;
		printf ("DECK COUNTS: %d\n",deckCounts);
		game->deckCount[player] = deckCounts;
		for (j = 0; j < deckCounts; j++) 
		{
			card = rand() % 27;
			game->deck[player][j] = card;
		}
		discardCounts = rand() % 10;
		game->discardCount[player] = discardCounts;
		for (j = 0; j < discardCounts; j++) 
		{
			card = rand() % 27;
			game->discard[player][j] = card;
		}
		
		// Use the Council Room Card 
		cardEffect(council_room, 0, 0, 0, game, cardPositions, 0);
		
		// Check if we got the right hand counts 
		if (game->handCount[player] == (handCounts + 4))
		{
			printf("TEST SUCCESSFUL: GET THE RIGHT HAND COUNTS\n");
		}
		else
		{
			printf("TEST FAILED: GET THE WRONG HAND COUNTS\n");
		}
		
		// Check if we got the right deck counts 
		if (game->deckCount[player] == (deckCounts - 6))
		{
			printf("TEST SUCCESSFUL: GET THE RIGHT DECK COUNTS\n");
		}
		else
		{
			printf("TEST FAILED: GET THE WRONG DECK COUNTS\n");
		}
		
		// Check if we got the right discard counts 
		if (game->discardCount[player] == (discardCounts + 1))
		{
			printf("TEST SUCCESSFUL: GET THE RIGHT DISCARD COUNTS\n");
		}
		else
		{
			printf("TEST FAILED: GET THE WRONG DISCARD COUNTS\n");
		}
		
		// Free the memory 
		free(game);
	}
	return 0;
}