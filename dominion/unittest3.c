/* 
* Krisna Irawan 
* CS 362 
* Assignment 2  
* Testing the buyCard function 
*/

#include <stdio.h>
#include "dominion.h"

int failed = 0;

void myAssert(int bool,char* msg) 
{
	if (bool == 0)
	{
		printf("TEST SUCCEED: %s",msg);
	} 
	else if(bool != 0) 
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

// Testing the buyCard function 
int main()
{
	struct gameState game;
	int numberOfPlayer = 2; 
	int randomSeed = 17;
	int kingdomCards[10] = {smithy,adventurer,gardens,embargo,cutpurse,
						mine,ambassador,outpost,baron,tribute};

	initializeGame(numberOfPlayer, kingdomCards, randomSeed, &game);
	
	printf("Testing the buyCard function \n");
	printf("TRYING TO BUY VALID CARD \n");
	int result = buyCard(3, &game);
	myAssert(result, "Successfully Buying Card \n");
	
	printf("TRYING TO BUY INVALID CARD \n");
	int result2 = buyCard(77, &game);
	myAssert(result2, "Card Is Invalid \n\n");
	
    checkAsserts();
	return 0;
}