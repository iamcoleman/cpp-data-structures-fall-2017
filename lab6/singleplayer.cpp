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
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>
#include "stack.cpp"


using namespace std;

const int numTowers = 3;



template <class T>
class Queue {
private:
    vector<T*> q;

public:
    void addQueue(T* item){
        q.push_back(item);
    }

    T* remQueue(){
        T* temp = q[0];
        q.erase(q.begin());
        return temp;
    }

    void display(){
        for(int i = 0; i < q.size(); i++){
            cout << i+1 << ": " << *q[i] << endl;
        }
    }

    int getLenTurns(){
        return q.size();
    }

    // Deconstructor
    ~Queue(){
        for(int i = 0; i < q.size(); i++){
            delete q[i];
        }
    }
};



struct Move {
    int from, to, disk;
    Move(int from, int to, int disk) : from(from), to(to), disk(disk) {}
};

ostream& operator<<(ostream& os, const Move& mv){
    os << "Moved disk " << mv.disk << " from TOWER " << mv.from+1 << " to TOWER " << mv.to+1;
    return os;
}



class Hanoi {
private:
    int disks;
    stack<int>* towers[numTowers];
    Queue<Move> moves;

public:
    Hanoi(int disks) : disks(disks) {
        for(int i = 0; i < numTowers; i++) towers[i] = new stack<int>(disks);
        for(int i = disks; i > 0; i--){
            int* temp = new int;
            *temp = i;
            towers[0]->push(temp);
        }
    }

    void moveDisk(int f, int t){
        stack<int> *from = towers[f], *to = towers[t];
        if(!from->getTop()){
            cout << "You cannot move a disc from an empty tower..." << endl;
            return;
        } else if(to->getTop() && *to->getTop() < *from->getTop()){
            cout << "You cannot move a bigger disc onto a smaller one..." << endl;
            return;
        }

        Move* current_move = new Move(f, t, *from->getTop());
        moves.addQueue(current_move);
        to->push(from->pop());
    }

    bool gameOver(){
        return towers[2]->length() == disks;
    }

    void showMoves(){
        moves.display();
    }

    void display(){
        for(int i = 0; i < numTowers; i++){
            cout << "TOWER " << i+1 << ": ";
            displayStack(*towers[i]);
            cout << endl;
        }
    }

    int getLen(){
        return moves.getLenTurns();
    }

    // Code taken from Wikipedia
    void autoSolve(int n, int from, int to, int aux){
        if(n == 1){
            moveDisk(from, to);
            return;
        }
        autoSolve(n-1, from, aux, to);
        moveDisk(from, to);
        autoSolve(n-1, aux, to, from);
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
    cout << "                                                                       \n"
            "                                   .---.          .---.          .---. \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                   |   |          |   |          |   | \n"
            "                                  =====================================\n";

    do {
        cout << "Enter the number of disks: ";
        getline(cin, input);
        stringstream(input) >> disks;
        if(disks < 2){
            cout << "Number of disks must be greater than or equal to 2..." << endl;
        }
    } while(disks < 2);

    cout << endl << "Rules: " << endl
         << "1. Move all this disks from Tower 1 on to Tower 3" << endl
         << "2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack." << endl
         << "3. No disk may be placed on top of a smaller disk." << endl
         << "4. Only one disk can be moved at a time." << endl << endl;

    // Create new Hanoi object game
    Hanoi game(disks);
    game.display();

    int from;   // Pop from
    int to;     // Push to
    int turnCount = 0;

    cout << endl << "Auto Solve? (y/n) ";
    getline(cin, input);
    if(input == "y" || input == "Y" || input == "yes" || input == "YES"){
        game.autoSolve(disks, 0, 2, 1);
    } else {
        while(!game.gameOver()){
            turnCount++;
            cout << endl << "------ Turn " << turnCount << " ------" << endl;
            game.display();
            cout << "--------------------" << endl;
            do {
                cout << "Enter the tower to move from: ";
                getline(cin, input);
                stringstream(input) >> from;
            } while(from < 1 || from > numTowers);
            do {
                cout << "Enter the tower to move to: ";
                getline(cin, input);
                stringstream(input) >> to;
            } while(to < 1 || to > numTowers);
            game.moveDisk(from-1, to-1);
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

    // Perfect game, 2^n - 1
    int perfGame;
    perfGame = pow(2.0, disks) - 1;
    if(game.getLen() == perfGame){
        cout << "Number of Moves: " << game.getLen() << endl;
        cout << "You had a perfect game!" << endl << "Congrats!" << endl;
    } else {
        cout << "Number of Moves: " << game.getLen() << endl;
        cout << "You did not have a perfect game..." << endl
             << "A perfect game would have been " << perfGame << " moves." << endl
             << "Better luck next time!" << endl;
    }

    getchar();
    return 0;
}






/*  Stack Testing Main

 int main() {
    int size = 5;
    srand(time(0));
    stack<int> test(size);

    for(int i = 0; i < size; i++){
        int* temp = new int;
        *temp = rand() % 100;
        test.push(temp);
    }

    cout << "Current Stack: " << endl;
    displayStack(test);

    cout << endl << "Pop the Stack: " << endl;
    for(int i = 0; i < size; i++){
        int* temp = test.pop();
        cout << " " << *temp;
    }

    getchar();

    return 0;
}

 */