/*
 * Coleman Lyski
 * Data Structures
 * Lab 3
 * 9/13/2017
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
#include <sstream>

#define MAX_PLAYERS 10

using namespace std;

// Forward declaration
//class Knockout;
//class Boston;

/*
	Class representing an N-sided die
*/
class Dice{
private:
    int numSides;

public:
    // Constructor
    Dice(int n){
        numSides = n;
    }

    // Get the number of sides
    int getSides() {
        return numSides;
    }

    // Perform a single roll of the die
    int roll() {
        int rando = 0;
        rando = rand() % numSides + 1;
        return rando;
    }
};

/*
	Class representing a Game Player
*/
class Player{

private:
    string name;
    int score;

public:
    // Constructor
    Player(){
        setName();
        score = 0;
    };

    // Constructor 2
    Player(string namer, int scorer){
        name = namer;
        score = scorer;
    }

    // Getter : Player Name
    string getName() {
        return name;
    }

    // Getter : Score
    int getScore() {
        return score;
    }

    // Set Player Name
    void setName() {
        cout << "Enter your name: ";
        cin >> name;
    }

    // Increases the player's score by a specified value
    void addToScore(int val){
        score = score + val;
    }
};

/*
	Abstract class DiceGame
*/
class DiceGame{

protected:
    Player *players[MAX_PLAYERS];
    Dice *dice;
    int numPlayers, numDice;

public:
    //	Pure virtual function
    virtual void play() = 0;

    // Accept the name and score of each player from the user
    void initPlayers(){
        do {
            cout << "Enter the number of players: ";
            cin >> numPlayers;
        } while( numPlayers > 10 || numPlayers < 1 );
        for( int i = 0; i < numPlayers; i++ ){
            string name;
            cout << "Player " << i+1 << " enter your name: ";
            cin >> name;
            players[i] = new Player(name,0);
        }
    }

    void displayScores(){
        for( int i = 0; i < numPlayers; i++ ){
            cout << players[i]->getName() << " : " << players[i]->getScore() << endl;
        }
    }

    // Write the round scores to scores.txt
    void writeScoresToFile(){
        ofstream myfile ("scores.txt", fstream::app);
        if (myfile.is_open())
        {
            string line1;
            int line2;
            for( int i = 0; i < numPlayers; i++ ){
                line1 = players[i]->getName();
                line2 = players[i]->getScore();
                myfile << line1 << " : " << line2 << endl;
            }
            myfile.close();
        } else {
            cout << "Unable to open file";
        }
    }

    // Print the player with the highest score
    void getHighestScore(){
        string line;
        int score;
        string b,name,highName;
        int max = 0;
        ifstream myfile ("scores.txt");
        if (myfile.is_open()) {
            while (getline (myfile, line)){
                // Parse the lines
                stringstream ss(line);
                ss >> name >> b >> score;

                // Save highest score and name
                if( score > max ){
                    max = score;
                    highName = name;
                }
            }
            myfile.close();
        } else {
            cout << "Unable to open file";
        }
        cout << "High Score: " << highName << " : " << max << endl;
    }
};

class Knockout : public DiceGame{
     virtual void play(){
        // Intro
        cout << "~*~*~ KNOCKOUT DICE GAME ~*~*~" << endl << endl;
        //initPlayers();
        int numSides;
        cout << "Enter sides on the die: ";
        cin >> numSides;
        dice = new Dice(numSides);
        cout << "Enter the number of die: ";
        cin >> numDice;
        cout << endl << "The Knockout score will now be rolled..." << endl;

        // Get Knockout Score
        int knockoutScore = 0;
        int rolls[numDice] = {};
        for( int i = 0; i < numDice; i++ ){
            rolls[i] = dice->roll();
            cout << "Roll " << i+1 << ": " << rolls[i] << endl;
        }
        for( int i = 0; i < numDice; i++ ){
            knockoutScore = knockoutScore + rolls[i];
        }
        cout << "The Knockout Score is " << knockoutScore << endl << endl;

        // The Juicy Game
        int alive[numPlayers] = {};
        std::fill_n(alive, numPlayers, 1);
        int sumAlive = numPlayers;

        // Knockout all the playaz
        do{
            for( int i = 0; i < numPlayers; i++ ){
                if( alive[i] == 1 ) {
                    int total = 0;
                    int rolls[numDice] = {};
                    cout << players[i]->getName() << "'s Roll:" << endl;

                    // Roll the Dice
                    for (int i = 0; i < numDice; i++) {
                        rolls[i] = dice->roll();
                        cout << "Roll " << i + 1 << ": " << rolls[i] << endl;
                    }

                    // Total the Rolls
                    for (int i = 0; i < numDice; i++) {
                        total = total + rolls[i];
                    }
                    cout << players[i]->getName() << " rolled " << total << endl;

                    // Check if the knockout score was rolled
                    if (total == knockoutScore) {
                        alive[i] = 0;
                        sumAlive--;
                        cout << players[i]->getName() << " is knocked out, haha" << endl;
                    }

                    // Next
                    getchar();
                }
            }
        }while( sumAlive != 1 );

        // One player left, winner and points
        for( int i = 0; i < numPlayers; i++ ){
            if( alive[i] == 1 ){
                cout << endl << players[i]->getName() << " is the winner!" << endl;
                cout << players[i]->getName() << " gets 5 points" << endl;
                players[i]->addToScore(5);
                cout << players[i]->getName() << "'s score is " << players[i]->getScore();
            }
        }

         // Keep Open
         getchar();
    }
};

class Boston : public DiceGame {
     virtual void play(){
        // Intro
        cout << "~*~*~ BOSTON DICE GAME ~*~*~" << endl << endl;
        //initPlayers();
        int numSides;
        cout << "Enter sides on the die: ";
        cin >> numSides;
        dice = new Dice(numSides);
        cout << "Enter the number of die: ";
        cin >> numDice;

        // Player's Totals
        int playerTotals[numPlayers] = {};
        std::fill_n(playerTotals, numPlayers, 0);

        for( int i = 0; i < numPlayers; i++ ){
            int highest[numDice] = {};
            int keep;
            cout << players[i]->getName() << "'s Roll:" << endl;

            // Roll the Dice
            for (int n = 0; n < numDice; n++){
                int rolls[numDice-n] = {};

                // Get the rolls
                for (int i = 0; i < numDice-n; i++){
                    rolls[i] = dice->roll();
                    cout << "Roll " << i + 1 << ": " << rolls[i] << endl;
                }

                // Find the highest roll
                int temp = 0;
                for (int i = 0; i < numDice-n; i++){
                    if(rolls[i] > temp)
                        temp = rolls[i];
                }
                highest[n] = temp;
                cout << "Highest: " << highest[n] << endl;
            }

            // Total the highest rolls
            for( int j = 0; j < numDice; j++ ){
                playerTotals[i] = playerTotals[i] + highest[j];
            }
            cout << players[i]->getName() << "'s total is " << playerTotals[i] << endl;

            getchar();
        }

        // Find the winner
        int winner;
        int tempPos = 0;
        int tempScore = 0;
        for( int i = 0; i < numPlayers; i++ ){
            if( playerTotals[i] > tempScore ){
                tempPos = i;
                tempScore = playerTotals[i];
            }
            winner = tempPos;
        }

        cout << endl << players[winner]->getName() << " is the winner!" << endl;
        cout << players[winner]->getName() << " gets 5 points" << endl;
        players[winner]->addToScore(5);
        cout << players[winner]->getName() << "'s score is " << players[winner]->getScore();

        getchar();
    }

};

int main() {
    // Randeez
    srand((unsigned)time(0));

    char playAgain;
    do {
        // Dice Game initPlayers
        int choice;
        cout << "Coleman's Dice Games" << endl
             << "--------------------" << endl
             << "1. Knockout" << endl
             << "2. Boston" << endl
             << "3. Highscores" << endl
             << "4. Exit" << endl << endl;
        cout << "Enter what you want to play: ";
        cin >> choice;

        if (choice == 1) {
            DiceGame *game = new Knockout();
            game->initPlayers();
            game->play();
            game->writeScoresToFile();
        } else if (choice == 2) {
            DiceGame *game = new Boston();
            game->initPlayers();
            game->play();
            game->writeScoresToFile();
        } else if (choice == 3) {
            DiceGame *game = new Knockout;
            game->getHighestScore();
        } else {
            return 0;
        }

        cout << endl << "Do you want to play again? (y/n) ";
        cin >> playAgain;
    } while( playAgain == 'Y' || playAgain == 'y');
}