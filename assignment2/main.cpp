#include <iostream>
#include <ctime>
#include <sstream>
#include "LL.cpp"
#include "StudentList.cpp"

using namespace std;

void addStudent(LL<StudentList>& S){
    string input;
    string fname;
    string lname;
    string mnum;
    float gpa = 0;

    cout << endl << "----- Add Student -----" << endl;
    cout << "Enter first name: ";
    getline(cin, fname);
    cout << "Enter last name: ";
    getline(cin, lname);

    // MNumber
    bool flag;
    do {
        flag = false;
        cout << "Enter MNumber (include the M): ";
        getline(cin, mnum);
        if (mnum.length() != 9) {
            cout << endl << "MNumber must be 9 characters long" << endl;
            flag = true;
        }
        if (mnum[0] != 'M') {
            cout << endl << "MNumber must begin with 'M'" << endl;
            flag = true;
        }
        for (int i = 1; i < 9; i++) {
            if (!isdigit(mnum[i])) {
                cout << endl << "The last 8 characters must be numbers" << endl;
                flag = true;
                break;
            }
        }
    } while (flag);

    // GPA
    do {
        cout << "Enter student's GPA (0-4): ";
        getline(cin, input);
        try {
            gpa = stof(input);
        } catch (...) {
            gpa = -1;
        }
        if (gpa < 0 || gpa > 4) cout << endl << "GPA must be 0-4" << endl;
    } while (gpa < 0 || gpa > 4);

    // Add the student to the directory
    StudentList new_student(fname, lname, mnum, gpa);
    new_student.display();
    S.addItem(new_student);
}

// Name Generator Functions
static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
int stringLength = sizeof(alphanum) - 1;
char genChar(){
    return alphanum[rand() % stringLength];
}
string genName(){
    string name;
    for(int i = 0; i < rand() % 5 + 3; ++i){
        name += genChar();
    }
    return name;
}

// Student Generator
void genStudent(LL<StudentList>& S){
    int numOfStudents;
    cout << "How many students do you want to generate: ";
    cin >> numOfStudents;
    int i = 0;

    do {
        // MNumber
        int mnum = rand() % 10000000 + 10000000;
        stringstream s;
        s << "M" << mnum;
        string fullM = s.str();

        // Name
        string fname = genName();
        string lname = genName();

        // GPA
        float gpa = 1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0 - 1.0)));

        // Add student to dir
        StudentList new_student(fname, lname, fullM, gpa);
        cout << endl << "Student " << i+1 << endl;
        new_student.display();
        S.addItem(new_student);
        i++;
    } while(i < numOfStudents);
}

void swap(LL<StudentList>& S, int x, int y) {
    // Nothing to do if x and y are same
    if (x == y) return;

    // Search for x (keep track of prevX and currX
    StudentList *currX = NULL;
    StudentList *prevX = NULL;
    currX = S.seeAt(x);


    while (currX && currX->info != x)
    {
        prevX = currX;
        currX = currX->next;
    }

    // Search for y (keep track of prevY and currY
    struct Node *prevY = NULL, *currY = *S;
    while (currY && currY->data != y)
    {
        prevY = currY;
        currY = currY->next;
    }

    // If either x or y is not present, nothing to do
    if (currX == NULL || currY == NULL)
        return;

    // If x is not head of linked list
    if (prevX != NULL)
        prevX->next = currY;
    else // Else make y as new head
        *head_ref = currY;

    // If y is not head of linked list
    if (prevY != NULL)
        prevY->next = currX;
    else  // Else make x as new head
        *head_ref = currX;

    // Swap next pointers
    struct Node *temp = currY->next;
    currY->next = currX->next;
    currX->next  = temp;
}



int main() {
    // Randeez
    srand((unsigned)time(0));

    LL<StudentList> dir;

    cout << "----- Generate Students -----" << endl;
    genStudent(dir);

    /*
    cout << endl << "----- Display Students -----" << endl;
    node<StudentList> *curr_node = dir.start();
    for(int i = 0; i < dir.size(); i++){
        cout << endl << "Location " << i << ":" << endl;
        curr_node->info.display();
        curr_node = curr_node->next;
    }
     */

    /*
    int size = dir.size();
    bubbleSort(dir, size);
     */

    swap(dir, 0, 2);

    getchar();
    getchar();
    return 0;
}