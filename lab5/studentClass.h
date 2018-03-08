/*
 *   #######################
 *   #    Coleman Lyski    #
 *   #        Lab 5        #
 *   #   7 October  2017   #
 *   #######################
 */

#ifndef LAB5_STUDENTCLASS_H
#define LAB5_STUDENTCLASS_H

#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;


class studentClass {
private:
    string FirstName;
    string LastName;
    string MNumber;
    float GPA;
    time_t Birthday;

public:
    // Blank Constructor
    studentClass() {}
    // Constructor
    studentClass(string fname, string lname, string mnum, float gpa=0)
            : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}

    // My functions baby!!!
    string getName(){
        return FirstName + " " + LastName;
    }

    string getMNumber(){
        return MNumber;
    }

    void setBirthday(tm *bday){
        // Unix Timestamp Birthday
        Birthday = mktime(bday);
    }

    char* getBirthday(){
        // Unix Timestamp -> Text
        return ctime(&Birthday);
    }

    int getAge(){
        // Current Time - Birthday = Age in Years
        return (time(0) - Birthday)/(31536000);  // Seconds -> Years = 31536000
    }

    void display(){
        cout << "Name: "     << getName()     << endl
             << "Age: "      << getAge()      << endl
             << "GPA: "      << GPA           << endl
             << "MNumber: "  << getMNumber()  << endl
             << "Birthday: " << getBirthday() << endl;
    }

    // Overloaded Operators
    bool operator>(const studentClass &s){
        return MNumber > s.MNumber;
    }
    bool operator<(const studentClass &s){
        return MNumber < s.MNumber;
    }
    bool operator==(const studentClass &s){
        return MNumber == s.MNumber;
    }
    bool operator==(string id){
        return MNumber == id;
    }

};


#endif //LAB5_STUDENTCLASS_H
