/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the Council Room Card Function
*/

#include "dominion.h"
#include "interface.h"
#include <stdio.h>

int failed = 0;

void myAssert(int bool) 
{
	if (bool == 9)
	{
		printf("TEST SUCCEED: Correct Council Room Card Function \n");
	} 
	else if(bool != 9) 
	{
		printf("TEST FAILED: Incorrect Council Room Card Function \n");
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

// Testing the Council Room Card Function
int main() 
{
	struct gameState game;
	
	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};
	initializeGame(numberOfPlayer, kingdomCards, randomSeed, &game);

	addCardToHand(0, 8, &game);
	playCard(5, 0, 0, 0, &game);

	int result = numHandCards(&game);
  
	printf("Number Of Card: %d\n", result);
  
	myAssert(result);

	checkAsserts();
	return 0;
}