/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the numHandCards function 
*/

#include <stdio.h>
#include "dominion.h"

int failed = 0;

void myAssert(int bool,char* msg) 
{
	if (bool == 5)
	{
		printf("TEST SUCCEED: %s",msg);
	} 
	else if(bool != 5) 
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

// Testing the numHandCards function 
int main()
{
	struct gameState game;
	struct gameState *gamePointer = &game;

	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,
						mine,ambassador,outpost,baron,tribute};

	initializeGame(numberOfPlayer, kingdomCards, randomSeed, gamePointer);

    int result = numHandCards(gamePointer);
	printf ("Testing the numHandCards function \n");
	printf ("TRYING COUNT THE NUMBER OF CARDS IN HAND \n");
	printf("Number Of Card: %d\n",result);
	
    myAssert(result, "Player Have 5 Cards \n");

    checkAsserts();
	return 0;
}