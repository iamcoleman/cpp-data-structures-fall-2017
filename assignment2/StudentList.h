#ifndef ASSIGNMENT2_STUDENTLIST_H
#define ASSIGNMENT2_STUDENTLIST_H

#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;


class StudentList {
private:
    string FirstName;
    string LastName;
    string MNumber;
    float GPA;

public:
    // Blank Constructor
    StudentList() {}
    // Constructor
    StudentList(string fname, string lname, string mnum, float gpa=0)
            : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}

    // The good stuff...
    string getName(){
        return FirstName + " " + LastName;
    }

    string getMNumber(){
        return MNumber;
    }

    float getGPA(){
        return GPA;
    }

    void display(){
        cout << "Name: "     << getName()     << endl
             << "GPA: "      << GPA           << endl
             << "MNumber: "  << getMNumber()  << endl;
    }


    // Overloaded Operators
    bool operator>(const StudentList &s){
        return MNumber > s.MNumber;
    }
    bool operator<(const StudentList &s){
        return MNumber < s.MNumber;
    }
    bool operator==(const StudentList &s){
        return MNumber == s.MNumber;
    }
    bool operator==(string id){
        return MNumber == id;
    }
};


#endif //ASSIGNMENT2_STUDENTLIST_H
