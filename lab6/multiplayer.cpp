/*

   _____       _                              _               _    _
  /  __ \     | |                            | |             | |  (_)
  | /  \/ ___ | | ___ _ __ ___   __ _ _ __   | |    _   _ ___| | ___
  | |    / _ \| |/ _ \ '_ ` _ \ / _` | '_ \  | |   | | | / __| |/ / |
  | \__/\ (_) | |  __/ | | | | | (_| | | | | | |___| |_| \__ \   <| |
   \____/\___/|_|\___|_| |_| |_|\__,_|_| |_| \_____/\__, |___/_|\_\_|
                                                     __/ |
                                                    |___/

  Lab 6
  24 October, 2017



 */


#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "stack.cpp"
#include "queue.cpp"

using namespace std;

const int numTowers = 5;
const char players[2] = {'C', 'X'};

class Hanoi {
private:
    int disks;
    stack<string>* towers[numTowers];
    queue<Move> moves;
public:
    // Constructor
    Hanoi(int disks) : disks(disks) {
        for(int i = 0; i < numTowers; i++) towers[i] = new stack<string>(2*disks);
        for(int i = disks; i > 0; i--){
            string *temp1 = new string, *temp2 = new string;
            *temp1 = players[0] + to_string(i);
            *temp2 = players[1] + to_string(i);
            towers[0]->push(temp1);
            towers[numTowers-1]->push(temp2);
        }
    }

    void moveDisk(char player, int f, int t){
        stack<string> *from = towers[f], *to = towers[t];
        if(!from->getTop()){
            cout << "You cannot move a disk from an empty tower..." << endl;
            return;
        }

        string disk = *from->getTop();

        if(to->getTop() && (*to->getTop())[1] < (*from->getTop())[1]){
            cout << "You cannot move a bigger disk onto a smaller one..." << endl;
            return;
        }

        to->push(from->pop());
        Move* current_move = new Move(player, f, t, disk);
        moves.enqueue(current_move);
    }

    void display(){
        for(int i = 0; i < numTowers; i++){
            cout << i+1 << ":";
            displayStack(*towers[i]);
            cout << endl;
        }
    }

    bool checkTower(stack<string>* tower, char player){
        if(tower->length() != disks) return false;
        bool result = true;
        stack<string> tempT(disks);
        for(int i = 0; i < disks; i++){
            string disc = *tower->getTop();
            if(disc[0] != player){
                result = false;
                break;
            }
            tempT.push(tower->pop());
        }
        int disks_removed = tempT.length();
        for(int i = 0; i < disks_removed; i++) tower->push(tempT.pop());
        return result;
    }

    bool gameOver(){
        int both = 0;
        for(int i = 0; i < 2; i++){
            if(checkTower(towers[i], players[1])){
                both++;
            }
        }
        for(int i = 3; i < 5; i++){
            if(checkTower(towers[i], players[0])){
                both++;
            }
        }
        if(both == 2){
            return true;
        } else {
            return false;
        }
    }

    void showMoves(){
        moves.display();
    }

    // Deconstructor
    ~Hanoi(){
        for(int i = 0; i < numTowers; i++){
            delete towers[i];
        }
    }
};

int main(){
    string input;
    int disks;

    // INTRO
    cout << " _______  _______  _     _  _______  ______      _______  _______    __   __  _______  __    _  _______  ___  \n"
            "|       ||       || | _ | ||       ||    _ |    |       ||       |  |  | |  ||   _   ||  |  | ||       ||   | \n"
            "|_     _||   _   || || || ||    ___||   | ||    |   _   ||    ___|  |  |_|  ||  |_|  ||   |_| ||   _   ||   | \n"
            "  |   |  |  | |  ||       ||   |___ |   |_||_   |  | |  ||   |___   |       ||       ||       ||  | |  ||   | \n"
            "  |   |  |  |_|  ||       ||    ___||    __  |  |  |_|  ||    ___|  |       ||       ||  _    ||  |_|  ||   | \n"
            "  |   |  |       ||   _   ||   |___ |   |  | |  |       ||   |      |   _   ||   _   || | |   ||       ||   | \n"
            "  |___|  |_______||__| |__||_______||___|  |_|  |_______||___|      |__| |__||__| |__||_|  |__||_______||___|" << endl << endl;
    cout << "                                                                                       \n"
            "                     .---.          .---.          .---.          .---.          .---. \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     |   |          |   |          |   |          |   |          |   | \n"
            "                     ==================================================================\n";

    do {
        cout << "Enter the number of disks: ";
        getline(cin, input);
        stringstream(input) >> disks;
        if(disks < 2){
            cout << "Number of disks must be greater than or equal to 2..." << endl;
        }
    } while(disks < 2);

    cout << endl << "Rules: " << endl
         << "1. Move all this disks from Tower 1 on to Tower 5" << endl
         << "2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack." << endl
         << "3. No disk may be placed on top of a smaller disk." << endl
         << "4. Only one disk can be moved at a time." << endl << endl;

    // Create new Hanoi object game
    Hanoi game(disks);
    int from;  // Pop from
    int to;    // Push to
    int turnCount = 0;

    bool isGameOver = true;
    while(isGameOver){
        turnCount++;
        for(int i = 0; i < 2; i++){
            cout << endl << "------ Turn " << turnCount << " ------" << endl;
            cout << "Player " << players[i] << "'s Turn" << endl;
            game.display();
            cout << "--------------------" << endl;

            do {
                cout << "Enter the tower to move from: ";
                getline(cin, input);
                stringstream(input) >> from;
            } while(from < 1 || from > numTowers);

            do {
                cout << "Enter the tower to move to:  ";
                getline(cin, input);
                stringstream(input) >> to;
            } while(to < 1 || to > numTowers);

            game.moveDisk(players[i], from-1, to-1);

            if(game.gameOver()){
                isGameOver = false;
                break;
            }
        }
    }

    cout << endl;
    game.display();
    cout << " _______  _______  __   __  _______    _______  __   __  _______  ______   \n"
            "|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  \n"
            "|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  \n"
            "|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ \n"
            "|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |\n"
            "|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |\n"
            "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|\n\n";
    cout << endl << "Game Moves:" << endl;
    game.showMoves();
    cout << endl;

    getchar();
    return 0;
}
