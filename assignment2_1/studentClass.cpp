#include <iostream>

using namespace std;

class studentClass {
private:
    string FirstName;
    string LastName;
    string MNumber;
    float GPA;

public:
    // Blank Constructor
    studentClass() {}
    // Constructor
    studentClass(string fname, string lname, string mnum, float gpa=0)
            : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}

    // The good stuff...
    string getName(){
        return FirstName + " " + LastName;
    }
    string getfname(){
        return FirstName;
    }
    string getlname(){
        return LastName;
    }

    string getMNumber(){
        return MNumber;
    }

    float getGPA(){
        return GPA;
    }

    void display(){
        cout << "Name: "     << getName()     << endl
             << "GPA: "      << getGPA()      << endl
             << "MNumber: "  << getMNumber()  << endl;
    }

    // Overloaded Operators
    bool fnamemore(studentClass* s){return FirstName > s->getfname();}
    bool lnamemore(studentClass* s){return LastName > s->getlname();}
    bool mnummore(studentClass* s){return MNumber > s->getMNumber();}
    bool gpamore(studentClass* s){return GPA > s->getGPA();}
};

