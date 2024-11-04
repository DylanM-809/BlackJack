
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

const int ARRAY_SIZE = 52;

const string cardDeck[ARRAY_SIZE] = {
"spadeAce",   "diamondAce",   "heartAce",   "clubAce",		// (0, 1, 2, 3)
"spadeTwo",   "diamondTwo",   "heartTwo",   "clubTwo",		// (4, 5, 6, 7)
"spadeThree", "diamondThree", "heartThree", "clubThree",	// (8, 9, 10, 11)
"spadeFour",  "diamondFour",  "heartFour",  "clubFour",		// (12, 13, 14, 15)
"spadeFive",  "diamondFive",  "heartFive",  "clubFive",		// (16, 17, 18, 19)
"spadeSix",   "diamondSix",   "heartSix",   "clubSix",		// (20, 21, 22, 23)
"spadeSeven", "diamondSeven", "heartSeven", "clubSeven",	// (24, 25, 26, 27)
"spadeEight", "diamondEight", "heartEight", "clubEight",	// (28, 29, 30, 31)
"spadeNine",  "diamondNine",  "heartNine",  "clubNine",		// (32, 33, 34, 35)
"spadeTen",   "diamondTen",   "heartTen",   "clubTen",		// (36, 37, 38, 39)
"spadeJack",  "diamondJack",  "heartJack",  "clubJack",		// (40, 41, 42, 43)
"spadeQueen", "diamondQueen", "heartQueen", "clubQueen",	// (44, 45, 46, 47)
"spadeKing",  "diamondKing",  "heartKing",  "clubKing" };	// (48, 49, 50, 51)

int cardValue(string);
int sum(string[], int);
int winningHand(int, int);
void cardDraw(string[], int&);

int main()
{
    bool test = true; // Test boolean to keep loop going

    while(test)
    {
        int chipStack = 1000;

        while (chipStack > 0)
        {
            string playerHand[12] = {" "};
            string dealerHand[12] = {" "};
            int playerBet = 0;
			int playerSize = 0;
			int dealerSize = 0;
			int playerSum = 0;
			int dealerSum = 0;

			srand(time(NULL));

			cout << "Chipstack amount: " << chipStack << endl;
            cout << "Place a bet (1) (5) (10) (50) (100): ";
            cin >> playerBet;
			cin.ignore();
            cout << endl;

			for (int i = 0; i < 2; i++) // Player draws two intial cards
            {
				cardDraw(playerHand, playerSize);
				cout << "Player card " << i + 1 << ": " << playerHand[i] << endl;
            }

			playerSum = sum(playerHand, playerSize);

			cout << "Value of your hand: " << playerSum << "\n\n";

			for (int i = 0; i < 1; i++)  // Dealer draws one intial card
			{
				cardDraw(dealerHand, dealerSize);
				cout << "Dealer card " << i + 1 << ": " << dealerHand[i] << endl;
			}

			dealerSum = sum(dealerHand, dealerSize);

			cout << "Value of dealer's hand: " << dealerSum << "\n\n";

			bool winner = false; // Temp boolean for loop

			while (!winner)
			{
				string playerChoice;
				playerSum = sum(playerHand, playerSize);

				cout << "Hit or Stand\n\n";
				getline(cin, playerChoice);


				if (playerChoice == "Hit" || playerChoice == "hit")
				{
					cardDraw(playerHand, playerSize);
					cout << "Player card " << playerSize << ": " << playerHand[playerSize - 1] << endl; // Temp hand display
					playerSum = sum(playerHand, playerSize);
					cout << "Value of your hand: " << playerSum << "\n\n";

					if (playerSum > 21)
					{
						cout << "Bust! You lose." << endl;
						chipStack -= playerBet;
						break;
					}
				}
				else if (playerChoice == "Stand" || playerChoice == "stand")
				{
					while (dealerSum < 17)
					{
						cardDraw(dealerHand, dealerSize);
						cout << "Dealer card " << dealerSize << ": " << dealerHand[dealerSize - 1] << endl; // Temp hand display

						dealerSum = sum(dealerHand, dealerSize); // Display sum each draw
						cout << "Value of dealer's hand: " << dealerSum << "\n\n";
					}

					if (dealerSum > 21)
					{
						cout << "Dealer Bust. You win!" << endl;
						chipStack += playerBet;
						break;
					}

					int declareWinner = winningHand(playerSum, dealerSum);

					if (declareWinner == 1)
					{
						chipStack += playerBet;
						break;
					}
					else if (declareWinner == 2)
					{
						chipStack -= playerBet;
						break;
					}
					else
					{
						break;
					}
				}
			}

        }
    }
}

void cardDraw(string hand[], int& handSize)
{
	hand[handSize] = cardDeck[rand() % 52];
	handSize++;
}

int sum(string hand[], int handSize)
{
	int sum = 0;
	int aceNumber = 0; // Counts the number of aces

	for (int i = 0; i < handSize; i++)
	{
		sum += cardValue(hand[i]);
		for (int j = 0; j < 4; j++)
		{
			if (hand[i] == cardDeck[j])
			{
				aceNumber++;
			}
		}
	}
	if (sum > 21) // Checks if player's hand is a bust
	{
		for (int i = 1; i <= aceNumber; i++) // Loop for each ace
		{
			sum -= 10; // Drops value of an ace in hand
			if (sum < 21) // Breaks loop if hand is playable
			{
				return sum;
			}
		}
	}
	return sum;
}

int cardValue(string card)
{
	int value = 0;
	int counter = 0;
	for (string i : cardDeck)
	{
		if (card == i)
		{
			if (counter < 4) // Ace cards
				value = 11;
			else if (counter < 8) // Two cards
				value = 2;
			else if (counter < 12) // Three cards
				value = 3;
			else if (counter < 16) // Four cards
				value = 4;
			else if (counter < 20) // Five cards
				value = 5;
			else if (counter < 24) // Six cards
				value = 6;
			else if (counter < 28) // Seven cards
				value = 7;
			else if (counter < 32) // Eight cards
				value = 8;
			else if (counter < 36) // Nine cards
				value = 9;
			else// Tens, Jacks, Queens and Kings
				value = 10;
		}
		counter++;
	}
	return value;
}

int winningHand(int playerSum, int dealerSum)
{
	if (playerSum > dealerSum)
	{
		cout << "You win!\n\n";
		cout << playerSum << endl;
		cout << dealerSum << endl;
		return 1;
	}
	else if (dealerSum > playerSum)
	{
		cout << "You lose.\n\n";
		cout << playerSum << endl;
		cout << dealerSum << endl;
		return 2;
	}
	else
	{
		cout << "The game is a push.\n\n";
		return 3;
	}
}
