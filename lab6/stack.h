//
//  Coleman Lyski
//  Lab 6
//  24 October 2017
//  Stack Class
//

#ifndef LAB6_STACK_H
#define LAB6_STACK_H

#include <iostream>
#include <exception>

using namespace std;

template <class T>
class stack {
private:
    T** arr;
    int top;    // empty = -1
    int size;
public:
    stack(int size) : arr(new T*[size]), top(-1), size(size) {}

    // friend class so we can create an object with this class
    template <class U> friend void displayStack(stack<U>& disp);

    void push(T* item){
        if(top == size-1) throw invalid_argument("Stack Overflow");
        arr[++top] = item;
    }

    T* pop(){
        if(top == -1) throw invalid_argument("Stack Underflow");
        return arr[top--];
    }

    T* getTop(){
        if(top == -1){
            return NULL;
        }
        return arr[top];
    }

    int length(){
        return top + 1;
    }

    void empty(){
        for(int i = 0; i <= top; i++){
            delete arr[i];
        }
        top = -1;
    }

    // Deconstructor
    ~stack(){
        empty();
        delete [] arr;
    }

};

template <class T>
void displayStack(stack<T>& disp){
    //cout << "top";
    for(int i = 0; i <= disp.top; i++){
        cout << " " << *disp.arr[i];
    }
}


#endif //LAB6_STACK_H
