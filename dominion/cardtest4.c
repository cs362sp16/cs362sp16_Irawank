/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the Adventurer Card Function 
*/

#include "dominion.h"
#include "interface.h"
#include <stdio.h>

int failed = 0;

void myAssert(int bool) 
{
	if (bool == 7)
	{
		printf("TEST SUCCEED: Correct Adventurer Card Function \n");
	} 
	else if(bool != 7) 
	{
		printf("TEST FAILED: Incorrect Adventurer Card Function \n");
		failed = 1;
	}
}

void checkAsserts() 
{
  if (!failed) 
  {
    printf ("TEST SUCCESSFULLY COMPLETED\n\n");
  }
}

// Testing the Adventurer Card Function 
int main() 
{
	struct gameState game;
	
	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};
	initializeGame(numberOfPlayer, kingdomCards, randomSeed, &game);

	addCardToHand(0, 7, &game);
	playCard(5, 0, 0, 0, &game);

	int result = numHandCards(&game);
	
	printf("Number Of Card: %d\n", result);
  
	myAssert(result);

	checkAsserts();
	return 0;
}