/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the supplyCount function 
*/

#include <stdio.h>
#include "dominion.h"

int failed = 0;

void myAssert(int bool,char* msg) 
{
	if (bool == 46)
	{
		printf("TEST SUCCEED: %s",msg);
	} 
	else if(bool == 40) 
	{
		printf("TEST SUCCEED: %s",msg);
	}
	else if(bool == 30) 
	{
		printf("TEST SUCCEED: %s",msg);
	}
	else 
	{
		printf("TEST FAILED: %s",msg);
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

// Testing the supplyCount function 
int main()
{
	struct gameState game;
	struct gameState *gamePointer = &game;

	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,
						mine,ambassador,outpost,baron,tribute};

	initializeGame(numberOfPlayer, kingdomCards, randomSeed, gamePointer);

    printf("Testing the supplyCount function \n");
    int result = supplyCount(copper, gamePointer);
    myAssert(result, "Correct Copper Card Supply \n");

    result = supplyCount(silver, gamePointer);
    myAssert(result, "Correct Silver Card Supply \n");

    result = supplyCount(gold, gamePointer);
    myAssert(result, "Correct Gold Card Supply \n");

    checkAsserts();
	return 0;
}