/* 
* Krisna Irawan 
* CS 362 
* Assignment 4 
* Random test dominion 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *comLogic(int array[10], struct gameState *state, int k, int position)
{
   int i, tmp, *choice,  cnt = 0;

   choice = malloc(3 * sizeof(int));
   choice[0] = choice[1] = choice[2] = -1;
   
   // If action card minion is selected 
   if(k == minion)
   {
      choice[0] = rand() % 2;
      choice[1] = 1 - choice[0];
   }

   // If action card baron is selected 
   else if(k == baron)
   {
	   choice[0] = rand() % 2;
   }

   // If action card mine is selected 
   else if(k == mine)
   {
      for(i = 0; i < state->handCount[state->whoseTurn]; i++)
	  {
		  if(state->hand[state->whoseTurn][i] <= gold && state->hand[state->whoseTurn][i] >= copper)
		  {
			  choice[0] = i;
			  break;
		  }
      }
	  
		if(choice[0] == -1)
		{	
			return 0;
		}
		choice[1] = rand() % copper + (state->hand[state->whoseTurn][choice[0]] + 2 - copper);
   }

   // If action card remodel is selected 
   else if(k == remodel)
   {
      choice[0] = position;

      do
	  {
		  choice[1] = cardSelection(array, rand() % 17, state);
      } 
	  while(getCost(choice[1]) > getCost(choice[0]) + 2 && state->supplyCount[choice[1]] > 0);
   }

    // If action card embargo is selected 
   else if(k == embargo)
   {
	   choice[0] = cardSelection(array, rand() % 17, state);
   }

   // If action card salvager is selected 
   else if(k == salvager)
   {
      choice[0] = position;
   }

   // If action card steward is selected 
   else if(k == steward)
   {
      choice[0] = rand() % 4;
      if(choice[0] < 1 && choice[0] > 2)
	  {
		  choice[1] = position;
	 	  choice[2] = position;
      }
   }

    // If action card ambassador is selected 
   else if(k == ambassador)
   {
	  choice[0] = position;
	  tmp = handCard(position, state);
      for(i = 0; i < state->handCount[state->whoseTurn]; i++)
	  {
		   if(handCard(i,state) == tmp)
		   {
			    cnt++;
		   }
	  }
	  if(cnt > 2)
	  {
		   choice[1] = 2;
	  }
      else
	  {
		   choice[1] = cnt;
	  }	  
   }
   return choice;
}

int cardSelection(int array[10], int position, struct gameState *state)
{
   int i;
   if(position < 10)
   {
	   i = array[position];
   }
   else
   {
	   if(position == 10)
	   {
		   i = copper;
	   }
	   else if(position == 11)
	   {
		   i = silver;
	   }
       else if(position == 12)
	   {
		  i = gold;
	   }
       else if(position == 13)
	   {
		   i = estate;
	   }
	   else if(position == 14)
	   {
		   i = duchy;  
	   }
	   else if(position == 15)
	   {
		   i = province;
	   }
      else if(position == 16)
	  {
		  i = curse;
	  }
   }
   return i;
}


int main (int argc, char** argv) 
{
 //List of the name of the card 
  const char* cardNames[] = {
           "curse", "estate", "duchy", "province", "copper", "silver",
           "gold", "adventurer", "council_room", "feast", "gardens",
           "mine", "remodel", "smithy", "village", "baron", "great_hall",
           "minion", "steward", "tribute", "ambassador", "cutpurse", 
           "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

  struct gameState state;
  struct gameState *p = &state;

  int numberOfPlayer = 0;
  int seed;
  int k[10];
  printf ("Start The Test\n");

  // Set random number of players between 2 and 4
  numberOfPlayer = rand() % 3 + 2;

  if (argc == 2)
  {
    seed = atoi(argv[1]);
    srand(atoi(argv[1]));
  }
  else 
  {
    srand(time(NULL));
    seed = rand();
  } 

  int money = 0;
  int actionPos = -1;
  int i=0;
  int kingdomCard[treasure_map] = {0};
  int card;
  int turn = 0;

  printf("List of Kingdom Cards\n");

  // Assign the kingdom cards on the deck 
  for (i = 0; i < 10; i++)
  {
    card = rand() % (treasure_map - adventurer + 1) + adventurer;
    if (kingdomCard[card])
	{
		i--;
        continue;
    }
    kingdomCard[card] = 1;
    k[i] = card;
    printf("%s, ", cardNames[card]);
  }
  printf("\n");

  // Initialize the game 
  initializeGame(numberOfPlayer, k, seed, p);
  
  for (i = 0; i < numberOfPlayer; i++)
  {
	  printf("Cuurent score for player %d : %d\n", i+1, scoreFor(i, p));
  }

  // Logic for the game 
  while (!isGameOver(p))
  {
	  printf("Turn#: %d\n", ++turn);
      money = 0;
      actionPos = -1;
      int *a;
      for (i = 0; i < numHandCards(p); i++) 
	  {   
		  if (handCard(i, p) == copper)
		  {
			  money++;
		  }
		  else if (handCard(i, p) == silver)
		  {
			  money += 2; 
		  }
		  else if (handCard(i, p) == gold)
		  {
			  money += 3;		  
		  }
		  else if (handCard(i,p) <= treasure_map && handCard(i,p) >= adventurer)
		  {
			  actionPos = i;
		  }
      }

    // Play an action card 
    if (actionPos != -1) 
	{
    	a = comLogic(kingdomCard,p,p->hand[whoseTurn(p)][actionPos],actionPos);
		printf("Player %d attempts to play %s from hand with choice1 = %d, choice2 = %d, choice3 = %d\n", 
						  p->whoseTurn+1, cardNames[p->hand[whoseTurn(p)][actionPos]], a[0], a[1], a[2]);
      
      if(playCard(actionPos, a[0], a[1], a[2], p) == -1)
	  {
		  printf("Play failed or the choice can't be handle\n");
      }
      else
	  {
		  printf("Play succeeded\n");
      }

      money = 0;
      i=0;
	  
      // Count the amount of money that the players have
      while(i<numHandCards(p))
	  {
		  if (handCard(i, p) == copper)
		  {
			money++;
          }
          else if (handCard(i, p) == silver)
		  {
			money += 2;
          }
          else if (handCard(i, p) == gold)
		  {
			money += 3;
          }
		  i++;
      }
    }

    // If player have the money, buy province 
    if (money >= 8)
	{
		printf("player %d : bought province\n", p->whoseTurn+1);
		buyCard(province, p);
    }
    // Player can buy treasure or action card 
    else if(rand() % 2)
	{                                 
      // Buy the most expensive treasure card they can afford
      if (money >= 6)
	  {
        printf("player %d : bought gold\n", p->whoseTurn+1); 
        buyCard(gold, p);
      }
      else if (money >= 3)
	  {
        printf("player %d : bought silver\n", p->whoseTurn+1); 
        buyCard(silver, p);
      }
      else
	  {
        printf("player %d: bought copper\n", p->whoseTurn+1); 
        buyCard(copper, p);
      }
    }
    else
	{
      for (i = 0; i < 10; i++)
	  {
        card = k[rand() % 10];
        if (buyCard(card,p) != -1)
		{
          i = -1;
          break;
        }
      }
      
      if (i == -1)
	  {
        printf("Player %d bought %s\n", p->whoseTurn+1, cardNames[card]);
      }
      else
	  {
        printf("Player %d did not have enough money to buy a card...\n", p->whoseTurn+1);
      }
    }

    printf("player%d: end turn\n", p->whoseTurn+1);
    endTurn(p);

    // Scores for each players
    for (i = 0; i < numberOfPlayer; i++)
	{
      printf("Score for player %d : %d\n", i+1, scoreFor(i, p));
    }
  } 

  printf ("Game end \n");
  // Final game score 
  for (i = 0; i < numberOfPlayer; i++)
  {
	  printf("Final score for player %d : %d\n", i+1, scoreFor(i, p));
  }
  
  printf ("Test successfull \n");
  return 0;
}