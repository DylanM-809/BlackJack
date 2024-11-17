
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
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
int sum(vector<string>&);
void cardDraw(vector<string>&);
void dealerCpu(vector<string>&);
void playerCpu(vector<string>&);
void winningHand(vector<string>, vector<string>, int&, int);
bool bust(vector<string>, vector<string>, int&, int);
void betOptions(int, int&);
string turnOptions(vector<string>&, bool&); // NOT COMPLETE
//bool splitCheck(vector<string>&); NOT COMPLETE (CHECK IF SPLIT IS POSSIBLE)
//void blackJack(); NOT COMPLETE (BODY OF THE GAME)


int main()
{
    bool test = true; // Test boolean to keep loop going

    while (test)
    {
        int chipStack = 1000;

        while (chipStack > 0)
        {
            vector<string> playerHand;
            vector<string> dealerHand;
            int playerBet = 0;

            srand(time(NULL));

            // Display betting options
            betOptions(chipStack, playerBet);

            //Player initlaly draws two cards
            playerCpu(playerHand);

            //Dealer intially draws one card
            dealerCpu(dealerHand);

            bool winner = false; // Temp bool for testing
            bool firstTurn = true;
            while (!winner) // Loop for player choice each turn
            {
                string playerChoice;

                playerChoice = turnOptions(playerHand, firstTurn);

                if (playerChoice == "Double" || playerChoice == "double")
                {
                    playerBet *= 2;
                    playerCpu(playerHand); // Player draws only one card

                    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if player busts
                    {
                        break;
                    }

                    dealerCpu(dealerHand); // Dealer draw phase

                    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if dealer busts
                    {
                        break;
                    }
                    else
                    {
                        winningHand(playerHand, dealerHand, chipStack, playerBet); // Determine the winner
                        break;
                    }
                }
                else if (playerChoice == "Hit" || playerChoice == "hit")
                {
                    playerCpu(playerHand); // Player draws once

                    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if player busts
                    {
                        break;
                    }
                }
                else if (playerChoice == "Stand" || playerChoice == "stand")
                {
                    dealerCpu(dealerHand); // Dealer draw phase

                    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if dealer busts
                    {
                        break;
                    }
                    else
                    {
                        winningHand(playerHand, dealerHand, chipStack, playerBet); // Determine the winner
                        break;
                    }
                }
            }
        }
    }
}

//void blackJack()
//{
//    
//}


//******************************************************************
// Definition of function turnOptions.
// Display options during player's turn.
//******************************************************************
string turnOptions(vector<string>& playerHand, bool& firstTurn)
{
    string playerChoice;

    cout << "[Hit][Stand]";

    if (firstTurn) // Display double option only on the first turn
    {
        cout << "[Double]";
        firstTurn = false;
    }

    cout << "\nYour choice: ";
    getline(cin, playerChoice);

    while (playerChoice != "Double" && playerChoice != "Hit" && playerChoice != "Stand" && playerChoice != "Split")
    {
        cout << "Invalid Choice.\n";
        getline(cin, playerChoice);
    }
    return playerChoice;
}

//******************************************************************
// Definition of function betOptions.
// Display options during betting phase
//******************************************************************
void betOptions(int chipStack, int& playerBet)
{
    cout << "Chipstack: $" << chipStack << endl;
    if (chipStack >= 1)
        cout << "(1)";
    if (chipStack >= 5)
        cout << "(5)";
    if (chipStack >= 10)
        cout << "(10)";
    if (chipStack >= 50)
        cout << "(50)";
    if (chipStack >= 100)
        cout << "(100)";

    cout << "\nPlace your bet: ";
    cin >> playerBet;
    cin.ignore();
    cout << endl;

    if (playerBet)

        while (playerBet > chipStack)
        {
            cout << "Invalid bet." << endl;
            cout << "Chipstack: $" << chipStack;
            cout << "\nPlace your bet: ";
            cin >> playerBet;
            cout << endl;
        }
}

//******************************************************************
// Definition of function cardDraw.
// Adds a card to hand and increment hand size
//******************************************************************
void cardDraw(vector<string>& hand)
{
    hand.push_back(cardDeck[rand() % 52]);
}

//******************************************************************
// Definition of function sum.
// Return sum of card values in hand
//******************************************************************
int sum(vector<string>& hand)
{
    int sum = 0;
    int aceNumber = 0; // Counts the number of aces
    for (int i = 0; i < hand.size(); i++)
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
// Returns the card value of a single card
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
// Compare player vs dealer to determine winning hand
//******************************************************************
void winningHand(vector<string> playerHand, vector<string> dealerHand, int& chipStack, int playerBet)
{
    if (sum(playerHand) > sum(dealerHand))
    {
        cout << "You win!\n\n";
        chipStack += playerBet;
    }
    else if (sum(dealerHand) > sum(playerHand))
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
// Checks hands for total sum over 21
//******************************************************************
bool bust(vector<string> playerHand, vector<string> dealerHand, int& chipStack, int playerBet)
{

    if (sum(dealerHand) > 21)
    {
        cout << "Dealer Bust. You win!" << endl;
        chipStack += playerBet;
        return true;
    }
    else if (sum(playerHand) > 21)
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
// Automate dealers drawing phases.
//******************************************************************
void dealerCpu(vector<string>& dealerHand)
{
    if (dealerHand.size() == 0) // If dealer hasn't drawn before
    {
        cardDraw(dealerHand);

        //Temp Dealer Display
        cout << "Dealer card " << size(dealerHand) << ": " << dealerHand[size(dealerHand) - 1] << endl;
        cout << "Value of dealer's hand: " << sum(dealerHand) << "\n\n";
        return;
    }

    while (sum(dealerHand) < 17)
    {
        cardDraw(dealerHand);

        // Temp Dealer Display
        cout << "Dealer card " << size(dealerHand) << ": " << dealerHand[size(dealerHand) - 1] << endl;
        cout << "Value of dealer's hand: " << sum(dealerHand) << "\n\n";
    }
    return;
}

//******************************************************************
// Definition of function playerCPU.
// Automate players drawing phases.
//******************************************************************
void playerCpu(vector<string>& playerHand)
{
    if (playerHand.size() == 0) // If player hasn't drawn before
    {
        for (int i = 0; i < 2; i++) // Player draws two intial cards
        {
            cardDraw(playerHand);

            //Temp Player Display
            cout << "Player card " << i + 1 << ": " << playerHand[size(playerHand) - 1] << endl;
        }

        //Temp Player Display
        cout << "Value of your hand: " << sum(playerHand) << "\n\n";

        return;
    }
    else
    {
        cardDraw(playerHand);

        //Temp Player Display
        cout << "Player card " << size(playerHand) << ": " << playerHand[size(playerHand) - 1] << endl;
        cout << "Value of your hand: " << sum(playerHand) << "\n\n";

        return;
    }
}

//******************************************************************
// Definition of function splitCheck.
// Uses parameters to check if player can split
//******************************************************************
bool splitCheck(vector<string>& hand)
{
    int firstCard = cardValue(hand[0]);
    int secondCard = cardValue(hand[1]);

    if (firstCard == secondCard)
    {
        return true;
    }
    else
    {
        return false;
    }
}
