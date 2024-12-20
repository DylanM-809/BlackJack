
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
void cardDraw(string[], int&);
void dealerCpu(string[], int&, int&);
void playerCpu(string[], int&, int&);
void winningHand(int, int, int&, int);
bool bust(int, int, int&, int);
//bool splitCheck(string[]); NOT COMPLETE


int main()
{
    bool test = true; // Test boolean to keep loop going

    while (test)
    {
        int chipStack = 1000;

        while (chipStack > 0)
        {
            string playerHand[12] = { " " };
            string dealerHand[12] = { " " };
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

            //Player initlaly draws two cards
            playerCpu(playerHand, playerSize, playerSum);

            //Dealer intially draws one card
            dealerCpu(dealerHand, dealerSize, dealerSum);

            bool winner = false; // Temp bool for testing
            bool firstTurn = true;
            while (!winner) // Loop for player choice each turn
            {
                string playerChoice;

                cout << "[Hit][Stand]";

                if (firstTurn) // Display double option only on the first turn
                {
                    cout << "[Double]";
                    firstTurn = false;
                }

                cout << endl;
                getline(cin, playerChoice);
                cout << endl;

                if (playerChoice == "Double" || playerChoice == "double")
                {
                    playerBet *= 2;
                    playerCpu(playerHand, playerSize, playerSum); // Player draws only one card

                    if (bust(playerSum, dealerSum, chipStack, playerBet)) // End game if player busts
                    {
                        break;
                    }

                    dealerCpu(dealerHand, dealerSize, dealerSum); // Dealer draw phase

                    if (bust(playerSum, dealerSum, chipStack, playerBet)) // End game if dealer busts
                    {
                        break;
                    }
                    else
                    {
                        winningHand(playerSum, dealerSum, chipStack, playerBet); // Determine the winner
                        break;
                    }
                }
                else if (playerChoice == "Hit" || playerChoice == "hit")
                {
                    playerCpu(playerHand, playerSize, playerSum); // Player draws once

                    if (bust(playerSum, dealerSum, chipStack, playerBet)) // End game if player busts
                    {
                        break;
                    }
                }
                else if (playerChoice == "Stand" || playerChoice == "stand")
                {
                    dealerCpu(dealerHand, dealerSize, dealerSum); // Dealer draw phase

                    if (bust(playerSum, dealerSum, chipStack, playerBet)) // End game if dealer busts
                    {
                        break;
                    }
                    else
                    {
                        winningHand(playerSum, dealerSum, chipStack, playerBet); // Determine the winner
                        break;
                    }
                }
            }
        }
    }
}


//******************************************************************
// Definition of function cardDraw.
// Uses parameters to add cards to hand array and increment hand size
//******************************************************************
void cardDraw(string hand[], int& handSize)
{
    hand[handSize] = cardDeck[rand() % 52];
    handSize++;
}

//******************************************************************
// Definition of function sum.
// Uses parameters to return total sum of card values in hand
//******************************************************************
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

//******************************************************************
// Definition of function cardValue.
// Uses parameters to return value of single cards
//******************************************************************
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

//******************************************************************
// Definition of function winningHand.
// Uses parameters to determine winning hand
//******************************************************************
void winningHand(int playerSum, int dealerSum, int& chipStack, int playerBet)
{
    if (playerSum > dealerSum)
    {
        cout << "You win!\n\n";
        chipStack += playerBet;
    }
    else if (dealerSum > playerSum)
    {
        cout << "You lose.\n\n";
        chipStack -= playerBet;
    }
    else
    {
        cout << "The game is a push.\n\n";
    }
}

//******************************************************************
// Definition of function bust.
// Uses parameters to check if total hand value is a bust.
//******************************************************************
bool bust(int playerSum, int dealerSum, int& chipStack, int playerBet)
{

    if (dealerSum > 21)
    {
        cout << "Dealer Bust. You win!" << endl;
        chipStack += playerBet;
        return true;
    }
    else if (playerSum > 21)
    {
        cout << "Bust! You lose." << endl;
        chipStack -= playerBet;
        return true;
    }
    else
        return false;
}

//******************************************************************
// Definition of function dealerCpu.
// Uses parameters to automate dealers drawing phases.
//******************************************************************
void dealerCpu(string dealerHand[], int& dealerSize, int& dealerSum)
{
    if (dealerSize == 0) // If dealer hasn't drawn before
    {
        cardDraw(dealerHand, dealerSize);
        dealerSum = sum(dealerHand, dealerSize);

        //Temp Dealer Display
        cout << "Dealer card " << dealerSize << ": " << dealerHand[dealerSize - 1] << endl;
        cout << "Value of dealer's hand: " << dealerSum << "\n\n";
        return;
    }

    while (dealerSum < 17)
    {
        cardDraw(dealerHand, dealerSize);
        dealerSum = sum(dealerHand, dealerSize);

        // Temp Dealer Display
        cout << "Dealer card " << dealerSize << ": " << dealerHand[dealerSize - 1] << endl;
        cout << "Value of dealer's hand: " << dealerSum << "\n\n";
    }
    return;
}

//******************************************************************
// Definition of function playerCPU.
// Uses parameters to automate player drawing phases.
//******************************************************************
void playerCpu(string playerHand[], int& playerSize, int& playerSum)
{
    if (playerSize == 0) // If player hasn't drawn before
    {
        for (int i = 0; i < 2; i++) // Player draws two intial cards
        {
            cardDraw(playerHand, playerSize);

            //Temp Player Display
            cout << "Player card " << i + 1 << ": " << playerHand[i] << endl;
        }
        playerSum = sum(playerHand, playerSize);

        //Temp Player Display
        cout << "Value of your hand: " << playerSum << "\n\n";

        return;
    }
    else
    {
        cardDraw(playerHand, playerSize);
        playerSum = sum(playerHand, playerSize);

        //Temp Player Display
        cout << "Player card " << playerSize << ": " << playerHand[playerSize - 1] << endl;
        cout << "Value of your hand: " << playerSum << "\n\n";

        return;
    }
}

/*
//******************************************************************
// Definition of function splitCheck.
// Uses parameters to check if player can split
//******************************************************************
bool splitCheck(string hand[])
{
    int firstCard = cardValue(hand[0]);
    int secondCard = cardValue(hand[1]);

    if (firstCard == secondCard)
    {
        return true;
    }
    else
        return false;
} */ //NOT COMPLETE

