//
//  Coleman Lyski
//  Lab 6
//  24 October 2017
//  Queue Class
//

/*
 *
 * Used for Multiplayer
 * Singleplayer has its own Queue class
 *
 */

#ifndef LAB6_QUEUE_H
#define LAB6_QUEUE_H

#include <iostream>
#include <vector>


template <class T>
class queue {
    std::vector<T*> q;
public:
    void enqueue(T* item){
        q.push_back(item);
    }

    T* dequeue(){
        T* temp = q[0];
        q.erase(q.begin());
        return temp;
    }

    void display(){
        for(int i = 0; i < q.size(); i++) std::cout << i+1 << ": " << *q[i] << std::endl;
    }

    ~queue(){
        for(int i = 0; i < q.size(); i++) delete q[i];
    }
};

struct Move {
    char player;
    int from, to;
    std::string disc;
    Move(char player, int from, int to, std::string disc) : player(player), from(from), to(to), disc(disc) {}
};

inline std::ostream& operator<<(std::ostream& os, const Move& mv){
    os << "Player " << mv.player << " moved " << mv.disc << " from TOWER " << mv.from+1 << " to TOWER " << mv.to+1;
    return os;
}



#endif //LAB6_QUEUE_H
