#ifndef ASSIGNMENT2_LL_H
#define ASSIGNMENT2_LL_H

#include <iostream>
#include <ctime>

#define LEN 1000

using namespace std;

template <class T>
struct node{
    T info;
    node<T> *next;
};

template <class T>
class LL {
protected:
    int length;
    node<T> *head;
    node<T> **next;

public:
    // Constructor
    LL() : length(0), head(), next(&head) {};

    // Overloaded operators
    bool operator<(const LL<T> &oll){
        return length < oll.length;
    }
    bool operator>(const LL<T> &oll){
        return length > oll.length;
    }
    bool operator==(const LL<T> &oll){
        if(length != oll.length){
            return false;
        }
        node<T> *l1 = head;
        node<T> *l2 = oll.head;
        while(l1){
            if(l1->info != l2->info){
                return false;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        return true;
    }

    // Return head
    node<T>* start(){
        return head;
    }

    // Linked List Functions
    int size();
    void addItem(T &item);
    T* getItem(string item);
    bool isInList(string item);
    bool isEmpty();
    T* seeNext();
    T* seeAt(int pos);
    void reset();
    void display();
};


template <class T>
int LL<T>::size()
{
    return length;
}

template <class T>
void LL<T>::addItem(T &item){
    node<T> *new_node = new node<T>;
    new_node->info = item;
    node<T> *temp1 = head, **temp2 = &head;
    while(temp1 && temp1->info < new_node->info){
        temp2 = &temp1->next;
        temp1 = temp1->next;
    }
    *temp2 = new_node;
    new_node->next = temp1;
    length++;
}

template <class T>
T* LL<T>::getItem(string item)  // String used for user input
{
    node<T> *current = head;
    while(current){
        if(current->info == item){
            return &current->info;
        }
        current = current->next;
    }
    return NULL;
}

template <class T>
bool LL<T>::isInList(string item)  // String used for user input
{
    node<T> *current = head;
    while(current){
        if(current->info == item){
            return true;
        }
        current = current->next;
    }
    return false;
}

template <class T>
bool LL<T>::isEmpty()
{
    if(head == NULL){
        return true;
    }
    return false;
}

template <class T>
T* LL<T>::seeNext()
{
    // List is empty error
    if(length == 0) throw invalid_argument("See Next Error - List is empty");

    if(*next == NULL){
        return NULL;
    }
    T* temp = &(*next)->info;
    next = &(*next)->next;
    return temp;
}

template <class T>
T* LL<T>::seeAt(int pos)
{
    // Position not in list error
    if(pos >= length || pos < 0) throw invalid_argument("Position is not in list");

    node<T> *current = head;
    for(int i = 0; i < pos; i++){
        current = current->next;
    }
    next = &current->next;
    return &current->info;
}

template <class T>
void LL<T>::reset()
{
    next = &head;
}

template <class T>
void LL<T>::display(){
    node<T> *curr_node = head;
    int i = 0;
    while(curr_node){
        cout << i << ": " << curr_node->info << endl;
        curr_node = curr_node->next;
        i++;
    }
}


#endif //ASSIGNMENT2_LL_H
