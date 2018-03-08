/*
 *   #######################
 *   #    Coleman Lyski    #
 *   #        Lab 5        #
 *   #   7 October  2017   #
 *   #######################
 */

#include <iostream>
#include <ctime>
#include <sstream>
#include "OLL.cpp"
#include "studentClass.cpp"

using namespace std;

int main(){
    OLL<studentClass> dir;
    string input;
    int choice;
    bool return_to_menu = true;

    do {
        cout << endl
             << "~~~~~~~~~~ Student Directory ~~~~~~~~~~" << endl
             << "1. Add Student to Directory           ~" << endl
             << "2. Find Student by MNumber            ~" << endl
             << "3. Find Student in Directory          ~" << endl
             << "4. Is Directory Empty                 ~" << endl
             << "5. Check size of Directory            ~" << endl
             << "6. Student at a location              ~" << endl
             << "7. Next Student                       ~" << endl
             << "8. Reset See Next                     ~" << endl
             << "9. Display Directory                  ~" << endl
             << "10. Exit                              ~" << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
             << "Enter your selection: ";
        getline(cin, input);
        stringstream(input) >> choice;

        if(choice == 1){
            string fname;
            string lname;
            string mnum;
            float gpa = 0;
            cout << endl << "~~~ Add Student ~~~" << endl
                 << "Enter first name: ";
            getline(cin, fname);
            cout << "Enter last name: ";
            getline(cin, lname);
            bool flag;
            do {
                flag = false;
                cout << endl << "Enter MNumber (include the M): ";
                getline(cin, mnum);
                if(mnum.length() != 9){
                    cout << endl << "MNumber must be 9 characters long" << endl;
                    flag = true;
                }
                if(mnum[0] != 'M'){
                    cout << endl << "MNumber must begin with 'M'" << endl;
                    flag = true;
                }
                for(int i = 1; i < 9; i++){
                    if(!isdigit(mnum[i])){
                        cout << endl << "The last 8 characters must be numbers" << endl;
                        flag = true;
                        break;
                    }
                }
            } while(flag);

            // GPA
            cout << "Enter GPA? (y/n): ";
            getline(cin, input);
            if(input == "y" || input == "Y"){
                do {
                    cout << endl << "Enter student's GPA (0-4): ";
                    getline(cin, input);
                    try {
                        gpa = stof(input);
                    } catch(...) {
                        gpa = -1;
                    }
                    if(gpa < 0 || gpa > 4) cout << endl << "GPA must be 0-4" << endl;
                } while(gpa < 0 || gpa > 4);
            }

            // Birthday
            //
            // Can't get time structure to work correctly, might store birthday in
            // a 8 int long array [y,y,y,y,m,m,d,d]
            //
            int m, d, y;
            tm bd;
            do {
                cout << "Enter student's birth month (1-12): ";
                getline(cin, input);
                stringstream(input) >> m;
                if(m < 1 || m > 12) cout << "Birth month must be 1-12\n";
            } while(m < 1 || m > 12);

            do {
                cout << "Enter student's birth day (1-31): ";
                getline(cin, input);
                stringstream(input) >> d;
                if(d < 1 || d > 31) cout << "Birth day must be 1-31\n";
            } while(d < 1 || d > 31);

            time_t now = time(0);
            tm *curr_date = localtime(&now);
            int curr_year = curr_date->tm_year + 1969;
            do {
                cout << "Enter student's birth year (1900-" << curr_year << "): ";
                getline(cin, input);
                stringstream(input) >> y;
                if(y < 1900 || y > curr_year) cout << "Birth year must be 1900-" << curr_year << "\n";
            } while(y < 1900 || y > curr_year);
            cout << endl;
            bd.tm_mon = m - 1;
            bd.tm_mday = d;
            bd.tm_year = y - 1969;
            //cout << "month: " << bd.tm_mon << endl;
            //cout << "day: " << bd.tm_mday << endl;
            //cout << "year: " << bd.tm_year << endl;
            //time_t now = time(0);
            //cout << now << endl;
            studentClass new_student(fname, lname, mnum, gpa);
            //new_student.setBirthday(&bd);
            new_student.display();
            dir.addItem(new_student);

        } else if(choice == 2){
            cout << endl << "~~~ Find Student by MNumber ~~~" << endl;
            cout << endl << "Enter student's MNumber: ";
            getline(cin, input);
            studentClass* student = dir.getItem(input);
            if(student){
                cout << endl;
                student->display();
            } else {
                cout << endl << "This student is not in the directory" << endl;
            }

        } else if(choice == 3){
            cout << endl << "~~~ Find Student in Directory ~~~" << endl;
            cout << "Enter student's MNumber: ";
            getline(cin, input);
            if(dir.isInList(input)){
                cout << "This student is in the directory" << endl;
            } else {
                cout << "This student is not in the directory" << endl;
            }

        } else if(choice == 4){
            cout << endl << "~~~ Is Directory Empty ~~~" << endl;
            if(dir.isEmpty()){
                cout << "Directory is empty..." << endl;
            } else {
                cout << "Directory is not empty..." << endl;
            }

        } else if(choice == 5){
            cout << endl << "~~~ Size of Directory ~~~" << endl;
            cout << "The directory contains " << dir.size() << " students" << endl;

        } else if(choice == 6){
            cout << endl << "~~~ Student at Location ~~~" << endl;
            if(dir.isEmpty()){
                cout << "There are currently no students in the directory" << endl;
                break;
            }
            studentClass *student = NULL;
            int index;
            cout << endl << "Enter the location of the student: ";
            getline(cin, input);
            stringstream(input) >> index;
            try {
                student = dir.seeAt(index);
            } catch(...) {
                cout << endl << "Invalid Location" << endl;
            }
            if(student){
                cout << endl << student->getName() << " is at location " << index << endl;
                student->display();
            }

        } else if(choice == 7){
            cout << endl << "~~~ Next Student ~~~" << endl;
            studentClass *student = NULL;
            try {
                student = dir.seeNext();
                if(student){
                    cout << "The next student is " << student->getName() << endl;
                    student->display();
                } else {
                    cout << endl << "Reset See Next" << endl;
                }
            } catch(...) {
                cout << endl << "The list is empty" << endl;
            }

        } else if(choice == 8){
            cout << endl << "~~~ Reset See Next ~~~" << endl;
            dir.reset();
            cout << endl << "See Next has been reset" << endl;

        } else if(choice == 9){
            cout << endl << "~~~ Display Directory ~~~" << endl;
            node<studentClass> *curr_node = dir.start();
            for(int i = 0; i < dir.size(); i++){
                cout << endl << "Location " << i << ":" << endl;
                curr_node->info.display();
                curr_node = curr_node->next;
            }

        } else {
            return_to_menu = false;
        }

    } while(return_to_menu);

}