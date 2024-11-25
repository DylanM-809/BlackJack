/***************************************************
Rylan Willis
Game Menu
Date Completed:
Description: A program that creates an interactable
menu for the blackjack game.
***************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Function Prototypes
void displayMenu();
void startGame();
void gameInstructions();
void exitGame();
void Menu(); // Prototype for the Menu function

int main() 
{
    Menu(); // Call the Menu function
    return 0;
}

// Function to display Game Menu.
void displayMenu() {
    cout << "===== gamble.exe =====\n";
    cout << "1. Start Game\n";
    cout << "2. How to play\n";
    cout << "3. Exit Game\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

// Function to start game.
void startGame() {
    cout << "Starting a new game...\n";
    // Add your game code here
    cout << "The game has started!\n";
}

// Function to show how to play.
void gameInstructions() {
    cout << "Welcome to the game gamble.exe!\n";
    cout << "1. This game is pretty much Blackjack with a few twists.\n";
    cout << "2. The goal of this game is to get as close to 21 as possible without going over.\n";
    cout << "3. Each player starts with a chipset and places a bet before the round. \n";
    cout << "4. Aces are worth 1 or 11 points, face cards are worth 10 points, and all other cards are worth their face value.\n";
    cout << "5. On your turn, you can choose to \"Hit\" to draw a card \"Stand\" to stop drawing cards or to \"Double\" where you double your bet and draw one card before being forced to stand.\n";
    cout << "6. The dealer must draw until their total is 17 or higher.\n";
    cout << "7. The player with the higher total wins, unless they bust by going over 21.\n";
    cout << endl;
    cout << "Good Luck and Have Fun Playing!\n";
    cout << "\nPress Enter to return to the menu screen.";
    cin.ignore();
    cin.get();
    cout << endl;
}

// Function to exit game.
void exitGame() {
    cout << "Exiting Game...\n";
}

// Function to display the menu and handle user choices.
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
