//Skyler: got the code working with the display.
// 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

const int ARRAY_SIZE = 52;

const string cardDeck[ARRAY_SIZE] = {
"spadeAce",   "diamondAce",   "heartAce",   "clubAce",		// (0, 1, 2, 3)
"spade2",     "diamond2",     "heart2",     "club2",		// (4, 5, 6, 7)
"spade3",     "diamond3",     "heart3",     "club3",	    // (8, 9, 10, 11)
"spade4",     "diamond4",     "heart4",     "club4",		// (12, 13, 14, 15)
"spade5",     "diamond5",     "heart5",     "club5",		// (16, 17, 18, 19)
"spade6",     "diamond6",     "heart6",     "club6",		// (20, 21, 22, 23)
"spade7",     "diamond7",     "heart7",     "club7",	    // (24, 25, 26, 27)
"spade8",     "diamond8",     "heart8",     "club8",	    // (28, 29, 30, 31)
"spade9",     "diamond9",     "heart9",     "club9",		// (32, 33, 34, 35)
"spade10",    "diamond10",    "heart10",    "club10",		// (36, 37, 38, 39)
"spadeJack",  "diamondJack",  "heartJack",  "clubJack",		// (40, 41, 42, 43)
"spadeQueen", "diamondQueen", "heartQueen", "clubQueen",	// (44, 45, 46, 47)
"spadeKing",  "diamondKing",  "heartKing",  "clubKing" };	// (48, 49, 50, 51)

// Rylan Menu Functions
void displayMenu();
void startGame();
void gameInstructions();
void exitGame();
void Menu();

//Skyler functions
char getSuit(int, vector<string>&);
string getCardValue(int, vector<string>&, char&);
void displayCards(vector<string>&, vector<string>&, int&);


bool hitChoice(vector<string>&, vector<string>&, int&, int);
bool doubleChoice(vector<string>&, vector<string>&, int&, int);
bool standChoice(vector<string>&, vector<string>&, int&, int);
bool splitChoice(vector<string>&, vector<string>&, int&, int&);
bool splitOptions(vector<string>&, vector<string>&, int&, int&);
string turnOptions(vector<string>&, int, int, bool priorSplit = false);
void winningHand(vector<string>, vector<string>, int&, int);
bool bust(vector<string>, vector<string>, int&, int);
int cardValue(string);
int sum(vector<string>&);
void cardDraw(vector<string>&);
void dealerCpu(vector<string>&);
void playerCpu(vector<string>&);
void betOptions(int, int&);
bool splitCheck(vector<string>&);
void blackJack();

int main()
{
    Menu();
    return 0;
}



void blackJack()
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

        //skyler display card call added
        displayCards(playerHand, dealerHand, chipStack);

        bool gameOver = false; // Temp bool for testing
        while (!gameOver) // Loop for player choice each turn
        {
            string playerChoice;

            playerChoice = turnOptions(playerHand, chipStack, playerBet);

            if (playerChoice == "Double" || playerChoice == "double")
            {
                gameOver = doubleChoice(playerHand, dealerHand, chipStack, playerBet);
            }
            else if (playerChoice == "Hit" || playerChoice == "hit")
            {

                gameOver = hitChoice(playerHand, dealerHand, chipStack, playerBet);
            }
            else if (playerChoice == "Stand" || playerChoice == "stand")
            {

                gameOver = standChoice(playerHand, dealerHand, chipStack, playerBet);
            }
            else if (playerChoice == "Split" || playerChoice == "split")
            {
                gameOver = splitChoice(playerHand, dealerHand, chipStack, playerBet);
            }
        }
    }
    return;
}
//******************************************************************
// Menu Function
// Calls displayMenu, startGame, gameInstructions, 
// and exitGame functions.
//******************************************************************
void Menu() {
    int choice;
    bool running = true;

    while(running) {
        displayMenu();
        cin >> choice;
        cout << endl;

        // Input Validation
        if(cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (choice) {
            case 1:
                startGame();
                break;
            case 2: 
                gameInstructions();
                break;
            case 3:
                exitGame();
                running = false;
                break;
            default:
                cout << "Invalid choice! Please choose again.\n";
                break;
        }
    }
}

//******************************************************************
// Function to display menu.
// Called by Menu function.
//******************************************************************
void displayMenu() {
    cout << "===== gamble.exe =====\n";
    cout << "1. Start Game\n";
    cout << "2. How to play\n";
    cout << "3. Exit Game\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

//******************************************************************
// Function to start game.
// Called by Menu function.
//******************************************************************
void startGame() {
    cout << "Starting a new game...\n";
    blackJack();
}

//******************************************************************
// Function to display game instructions.
// Called by Menu function.
//******************************************************************
void gameInstructions() {
    cout << "Welcome to the game gamble.exe!\n";
    cout << "1. This game is pretty much Blackjack with a few twists.\n";
    cout << "2. The goal of this game is to get as close to 21 as possible without going over.\n";
    cout << "3. Aces are worth 1 or 11 points, face cards are worth 10 points, and all other cards are worth their face value.\n";
    cout << "4. On your turn, you can choose to \"Hit\" to draw a card or \"Stand\" to stop drawing cards.\n";
    cout << "5. The dealer must draw until their total is 17 or higher.\n";
    cout << "6. The player with the higher total wins, unless they bust by going over 21.\n";
    cout << endl;
    cout << "Good Luck and Have Fun Playing!\n";
    cout << "\nPress Enter to return to the menu screen.";
    cin.ignore();
    cin.get();
    cout << endl;
}

//******************************************************************
// Function to exit game.
// Called by Menu function.
//******************************************************************
void exitGame() {
    cout << "Exiting Game...\n";
    exit(0);
}

//******************************************************************
// Definition of function stand.
// Play the game out if player choice is stand.
//******************************************************************
bool standChoice(vector<string>& playerHand, vector<string>& dealerHand, int& chipStack, int playerBet)
{
    dealerCpu(dealerHand); // Dealer draw phase

    //skyler display card call added
    displayCards(playerHand, dealerHand, chipStack);
    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if dealer busts
    {
        return true;
    }
    else
    {
        winningHand(playerHand, dealerHand, chipStack, playerBet); // Determine the winner
        return true;
    }
}

//******************************************************************
// Definition of function doubleUp.
// Doubles player bet and draws a single card.
//******************************************************************
bool doubleChoice(vector<string>& playerHand, vector<string>& dealerHand, int& chipStack, int playerBet)
{
    playerBet *= 2;
    playerCpu(playerHand); // Player draws only one card

    //skyler display card call added
    displayCards(playerHand, dealerHand, chipStack);
    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if player busts
    {
        return true;
    }

    dealerCpu(dealerHand); // Dealer draw phase

    //skyler display card call added
    displayCards(playerHand, dealerHand, chipStack);
    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if dealer busts
    {
        return true;
    }
    else
    {
        winningHand(playerHand, dealerHand, chipStack, playerBet); // Determine the winner
        return true;
    }
}

//******************************************************************
// Definition of function hit.
// Draws a single card and checks if player busts.
//******************************************************************
bool hitChoice(vector<string>& playerHand, vector<string>& dealerHand, int& chipStack, int playerBet)
{
    playerCpu(playerHand); // Player draws once

    //skyler display card call added
    displayCards(playerHand, dealerHand, chipStack);
    if (bust(playerHand, dealerHand, chipStack, playerBet)) // End game if player busts
    {
        return true;
    }
    else
        return false;
}

//******************************************************************
// Definition of function splitHand.
// Display options during player's turn.
//******************************************************************
bool splitChoice(vector<string>& intialHand, vector<string>& dealerHand, int& chipStack, int& playerBet)
{
    vector<string> splitHand;

    splitHand.push_back(intialHand[1]);
    intialHand.pop_back();

    int firstBet = playerBet;
    bool handBust = splitOptions(intialHand, dealerHand, chipStack, firstBet);
   
    int secondBet = playerBet;
    bool splitBust = splitOptions(splitHand, dealerHand, chipStack, secondBet);

    if (!handBust)
    {
        standChoice(intialHand, dealerHand, chipStack, firstBet);
    }
    cout << "Press enter to continue.";
    cin.get();
    if (!splitBust)
    {
        standChoice(splitHand, dealerHand, chipStack, secondBet);
    }

    return true;
}

//******************************************************************
// Definition of function splitOptions.
// Display options while playing each split hand.
//******************************************************************
bool splitOptions(vector<string>& hand, vector<string>& dealerHand, int& chipStack, int& bet)
{
    bool endTurn = false;
    bool bust = false;
    playerCpu(hand);

    while (!endTurn)
    {
        string playerChoice;

        displayCards(hand, dealerHand, chipStack);

        playerChoice = turnOptions(hand, chipStack, bet, true);

        if (playerChoice == "Double" || playerChoice == "double")
        {
            bet *= 2;
            bust = hitChoice(hand, dealerHand, chipStack, bet);
            endTurn = true;
        }
        else if (playerChoice == "Hit" || playerChoice == "hit")
        {
            bust = hitChoice(hand, dealerHand, chipStack, bet);
            if (bust)
            {
                endTurn = true;
            }
        }
        else if (playerChoice == "Stand" || playerChoice == "stand")
        {
            endTurn = true;
        }
    }
    return bust;
}

//******************************************************************
// Definition of function turnOptions.
// Display options during player's turn.
//******************************************************************
string turnOptions(vector<string>& playerHand, int chipStack, int playerBet, bool priorSplit)
{
    string playerChoice;
    bool doubleUp = false;
    bool split = splitCheck(playerHand);

    cout << "Current bet: " << playerBet << endl;

    cout << "[Hit][Stand]";
    if (priorSplit)
    {
        split = false;
    }

    if (playerHand.size() == 2 && playerBet * 2 < chipStack) // Display double option
    {
        cout << "[Double]";
        doubleUp = true;
    }

    if (split) // Display split option
    {
        cout << "[Split]";
    }

    cout << "\nYour choice: ";
    getline(cin, playerChoice);

    if (!doubleUp && !split)
    {
        while (playerChoice != "Hit" && playerChoice != "hit" && playerChoice != "Stand" && playerChoice != "stand")
        {
            if (playerChoice == "split" || playerChoice == "Split")
            {
                cout << "Unable to split. Choose again: ";
                getline(cin, playerChoice);
            }
            else if (playerChoice == "double" || playerChoice == "Double")
            {
                cout << "Unable to double. Choose again: ";
                getline(cin, playerChoice);
            }
            else
            {
                cout << "Invalid Option. Choose again: ";
                getline(cin, playerChoice);
            }
        }
        return playerChoice;
    }
    else if (!doubleUp)
    {
        while (playerChoice != "Hit" && playerChoice != "hit" && playerChoice != "Stand" && playerChoice != "stand" && playerChoice != "Split" && playerChoice != "split")
        {
            if (playerChoice == "Double" || playerChoice == "double")
            {
                cout << "Unable to double. Choose again: ";
                getline(cin, playerChoice);
            }
            else
            {
                cout << "Invalid Option. Choose again: ";
                getline(cin, playerChoice);
            }
        }
        return playerChoice;
    }
    else if (!split)
    {
        while (playerChoice != "Double" && playerChoice != "double" && playerChoice != "Hit" && playerChoice != "hit" && playerChoice != "Stand" && playerChoice != "stand")
        {
            if (playerChoice == "Split" || playerChoice == "split")
            {
                cout << "Unable to split. Choose again: ";
                getline(cin, playerChoice);
            }
            else
            {
                cout << "Invalid Option. Choose again: ";
                getline(cin, playerChoice);
            }
        }
        return playerChoice;
    }
    else
    {
        while (playerChoice != "Double" && playerChoice != "double" && playerChoice != "Hit" && playerChoice != "hit" && playerChoice != "Stand" && playerChoice != "stand" && playerChoice != "split" && playerChoice != "Split")
        {
            cout << "Invalid Option. Choose again: ";
            getline(cin, playerChoice);
        }
        return playerChoice;
    }
}

//******************************************************************
// Definition of function betOptions.
// Display options during betting phase
//******************************************************************
void betOptions(int chipStack, int& playerBet)
{
    cout << "Chips: " << chipStack << endl;
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

     while (playerBet > chipStack)
     {
         cout << "Invalid bet." << endl;
         cout << "Chips: " << chipStack;
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
        cout << "Dealer Bust. You win!\n\n";
        chipStack += playerBet;
        return true;
    }
    else if (sum(playerHand) > 21)
    {
        cout << "Bust! You lose.\n\n";
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
        return;
    }

    while (sum(dealerHand) < 17)
    {
        cardDraw(dealerHand);
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
        }
        return;
    }
    else
    {
        cardDraw(playerHand);
        return;
    }
}

//******************************************************************
// Definition of function splitCheck.
// Uses parameters to check if player can split
//******************************************************************
bool splitCheck(vector<string>& hand)
{
    if (hand.size() == 2)
    {
        if (cardValue(hand[0]) == cardValue(hand[1]))
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        return false;
    }
}

//prints the value and suit of player and dealers hands. updates the display when a card is drawn. also prints each hands total value and amount of chips.
void displayCards(vector<string>& playerHand, vector<string>& pcHand, int& chips)
{
    char suit = '0';
    string cardValue = " ";
    int currentCard = 0;
    int currentCardValue = 0;
    int userChips = 0;
    string baseCard[7][9] = {
        {"_", "-", "-","-","-","-","-","-", "_"},
        {"|", " ", " ", " ", " ", " ", " ", " ", "|"},
        { "|", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", "_", "_", "_", "_", "_", "_", "_", "|" },
    };




    //prints Pc hand, number of cards based on pcHand var. stop at predetermind points in the baseCard template to insert cards suit and value.
    cout << "\n\n\n\n\n\n" << "Chips: " << chips << endl;
    cout << "Opponents hand value: " << sum(pcHand) << endl;
    for (int i = 0; i < 7; i++)
    {
        for (int h = 0; h < pcHand.size(); h++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (i == 3 && j == 1)
                {
                    //currentCard is a counting var to keep track of what card we are printing. getSuit copies the first letter of the card string
                    // to find suit. prints the suit in the middle of the card and sets the loop var to skip the spaces used for suit. 

                    suit = getSuit(currentCard, pcHand);
                    switch (suit)
                    {
                    case('h'):
                        cout << " heart";
                        currentCard++;
                        j = 6;
                        break;
                    case('s'):
                        cout << " spade";
                        currentCard++;
                        j = 6;
                        break;
                    case('d'):
                        cout << "diamond";
                        currentCard++;
                        j = 7;
                        break;
                    case('c'):
                        cout << " club";
                        currentCard++;
                        j = 5;
                        break;
                    }

                }
                //if not the spots for suit or value it prints the baseCard templet as is.
                else {
                    cout << baseCard[i][j];
                }
                //stops code at bottom left of card to add card value
                if (i == 5 && j == 5) {
                    //cards are stored like this "heartAce" so each suits card value is a different amount of letters after the suit.
                    //so i need to call my suit function to send to the value function to allow it to grab only the card value from the string.
                    suit = getSuit(currentCardValue, pcHand);
                    cardValue = getCardValue(currentCardValue, pcHand, suit);
                    // counting var to keep track of what card we are looping so it can convert the cards value correctly.
                    currentCardValue++;
                    //print formatting for 10 cards to fit in card template
                    if (cardValue == "10")
                    {
                        cout << (cardValue);
                    }
                    else
                    {
                        cout << (cardValue) << " ";
                    }
                    j = 7;
                }

            }
        }
        cout << endl;
    }
    //seperation for formatting
    cout << "\n\n\n";
    //reset var for player hand
    suit = '0';
    cardValue = " ";
    currentCard = 0;
    currentCardValue = 0;
    //prints players hand number of cards based on playerHand var. does the same as the other half just for the player hand.
    cout << "Players hand" << endl;
    for (int i = 0; i < 7; i++)
    {
        for (int h = 0; h < playerHand.size(); h++)
        {

            for (int j = 0; j < 9; j++)
            {
                if (i == 3 && j == 1)
                {
                    suit = getSuit(currentCard, playerHand);
                    switch (suit)
                    {
                    case('h'):
                        cout << " heart";
                        currentCard++;
                        j = 6;
                        break;
                    case('s'):
                        cout << " spade";
                        currentCard++;
                        j = 6;
                        break;
                    case('d'):
                        cout << "diamond";
                        currentCard++;
                        j = 7;
                        break;
                    case('c'):
                        cout << " club";
                        currentCard++;
                        j = 5;
                        break;
                    }

                }
                else {
                    cout << baseCard[i][j];
                }
                if (i == 5 && j == 5) {
                    suit = getSuit(currentCardValue, playerHand);
                    cardValue = getCardValue(currentCardValue, playerHand, suit);
                    currentCardValue++;
                    //print formatting for 10 cards to fit in card template
                    if (cardValue == "10")
                    {
                        cout << (cardValue);
                    }
                    else
                    {
                        cout << (cardValue) << " ";
                    }
                    j = 7;
                }

            }
        }
        cout << endl;
    }
    //prints cards in hands value for player.
    cout << "Value of your hand: " << sum(playerHand) << endl << endl;
}

char getSuit(int cardIndex, vector<string>& hand)
{
    //cards are stored in string vector like "spadeAce" this takes the first letter and returns it to identify suit.
    char suit = hand[cardIndex][0];

    return suit;
}

string getCardValue(int cardIndex, vector<string>& hand, char& suit)
{
    string cardValue = " ";
    char value = ' ';
    int k = 0;
    //cards are stored in string vector like "spadeAce" this takes the suit to know what index to start for the value and takes the first char of
    // the value in a var. if the char taken is a 1 then the value is 10 and the if statement adds the 0.
    switch (suit)
    {
    case('d'):
        if (hand[cardIndex][7] == '1')
        {
            cardValue = "10";
        }
        else {
            cardValue = hand[cardIndex][7];
        }
        break;
    case('c'):
        if (hand[cardIndex][4] == '1')
        {
            cardValue = "10";
        }
        else {
            cardValue = hand[cardIndex][4];
        }
        break;
    case('h'):
        if (hand[cardIndex][5] == '1')
        {
            cardValue = "10";
        }
        else {
            cardValue = hand[cardIndex][5];
        }
        break;
    case('s'):
        if (hand[cardIndex][5] == '1')
        {
            cardValue = "10";
        }
        else {
            cardValue = hand[cardIndex][5];
        }
        break;
    }
    return cardValue;
}