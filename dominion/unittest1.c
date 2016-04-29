/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the initializeGame function 
*/

#include <stdio.h>
#include "dominion.h"

int failed = 0;

void myAssert(int bool,char* msg) 
{
  if (bool == 0) 
  {
	printf("TEST FAILED: %s\n\n",msg);
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

// Testing the initializeGame function
int main()
{
	struct gameState game;
	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};
	printf ("Testing the initializeGame function \n");
	printf ("TRYING TO INITIALIZE THE GAME FOR THE FIRST PLAYER \n");
	int result = initializeGame(numberOfPlayer, kingdomCards, randomSeed, &game);

	myAssert(result == 0, "Game Initialization Succeed");

	int kingdomCards2[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,adventurer};

	printf ("TRYING TO INITIALIZE THE GAME FOR THE SECOND PLAYER \n");
	result = initializeGame(numberOfPlayer, kingdomCards2, randomSeed, &game);
	
	myAssert(result == 0,"Game Initialize With Duplicate Card");
	
	checkAsserts();
	return 0;
}