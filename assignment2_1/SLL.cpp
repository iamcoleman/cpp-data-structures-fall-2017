#include <iostream>
#include <ctime>
#include <sstream>
#include "studentClass.cpp"

using namespace std;

struct Node {
    studentClass* info;

    Node* next;

    ~Node(){
        delete info;
    }
};

// Linked List Class
class LL {
    Node *head;
    Node *tail;
public:
    LL() : head() {}

    void addItem(studentClass* new_student){
        Node* new_node = new Node;
        new_node->info = new_student;
        new_node->next = head;
        head = new_node;
    }

    void display(){
        Node* curr_node = head;
        while(curr_node){
            curr_node->info->display();
            curr_node = curr_node->next;
        }
    }

    Node** getHead(){
        return &head;
    }

    // Deconstructor
    ~LL(){
        while(head){
            Node* tempo = head;
            head = head->next;
            delete tempo;
        }
    }
};

Node* getTail(Node* head){
    while(head->next){
        head = head->next;
    }
    return head;
}

// partitioning function
// used for recursive quick sort
Node *partition(Node *head, Node *end, Node **newHead, Node **newEnd, int order){
    struct Node *pivot = end;
    struct Node *prev = NULL, *cur = head, *tail = pivot;
    if(order == 0){
        while(cur != pivot){
            if(cur->info->lnamemore(pivot->info)){
                if(prev) prev->next = cur->next;
                Node *tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            } else {
                if(*newHead == NULL) *newHead = cur;
                prev = cur;
                cur = cur->next;
            }
        }
    } else {
        while(cur != pivot){
            if(cur->info->lnamemore(pivot->info)){
                if(*newHead == NULL) *newHead = cur;
                prev = cur;
                cur = cur->next;
            } else {
                if(prev) prev->next = cur->next;
                Node *tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }
    }
    if(*newHead == NULL){
        *newHead = pivot;
    }
    *newEnd = tail;
    return pivot;
}

// recursize quicksort function
Node* qs_recursive(Node *head, Node *end, int order){
    if(!head || head == end)
        return head;
    Node *newHead = NULL, *newEnd = NULL;
    Node *pivot = partition(head, end, &newHead, &newEnd, order);
    if(newHead != pivot){
        Node *tmp = newHead;
        while(tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = qs_recursive(newHead, tmp, order);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = qs_recursive(pivot->next, newEnd, order);
    return newHead;
}
// Quick Sort Method
// Used for last name sorting
// this is the quick sort wrapper function
void quick_sort(Node **headRef, int order=0){
    *headRef = qs_recursive(*headRef, getTail(*headRef), order);
    return;
}

// merge and sort the two halves
Node* merge_sorted(Node* a, Node* b, int order=0){
    Node* result = NULL;
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    if(order == 0){
        if (a->info->fnamemore(b->info)){
            result = b;
            result->next = merge_sorted(a, b->next);
        } else {
            result = a;
            result->next = merge_sorted(a->next, b);
        }
    } else {
        if (a->info->fnamemore(b->info)){
            result = a;
            result->next = merge_sorted(a->next, b, order);
        } else {
            result = b;
            result->next = merge_sorted(a, b->next, order);
        }
    }
    return result;
}

// Halving function used for merge sort
void halve(Node* source, Node** frontRef, Node** backRef){
    // fast node 2x as fast
    // when fast reaches the end, slow is at half way point
    Node* fast;
    Node* slow;
    if(source == NULL || source->next == NULL){
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;
        while(fast != NULL){
            fast = fast->next;
            if(fast != NULL){
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}
// Merge Sort Method
// Used for first name sorting
void merge_sort(Node** headRef, int order=0){
    Node* head = *headRef;
    Node* a;
    Node* b;
    if((head == NULL) || (head->next == NULL)){
        return;
    }
    // halve the list
    halve(head, &a, &b);
    // sort the halves
    merge_sort(&a, order);
    merge_sort(&b, order);
    // combine back and sort
    *headRef = merge_sorted(a, b, order);
}

// Insertion Sort Method
// Used for GPA sorting
void ins_sorted(Node** head, Node* curr, int order=0){
    if(order == 0){
        if(!(*head) || (*head)->info->gpamore(curr->info)){
            curr->next = *head;
            *head = curr;
        } else {
            Node* tempo = *head;
            while(tempo->next && curr->info->gpamore(tempo->next->info)){
                tempo = tempo->next;
            }
            curr->next = tempo->next;
            tempo->next = curr;
        }
    } else {
        if(!(*head) || curr->info->gpamore((*head)->info)){
            curr->next = *head;
            *head = curr;
        } else {
            Node* tempo = *head;
            while(tempo->next && tempo->next->info->gpamore(curr->info)){
                tempo = tempo->next;
            }
            curr->next = tempo->next;
            tempo->next = curr;
        }
    }
}

void insertion_sort(Node** head, int order=0){
    Node *current = *head;
    Node *sorted = NULL;
    while(current){
        Node* next = current->next;
        ins_sorted(&sorted, current, order);
        current = next;
    }
    *head = sorted;
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
LL genStudent(int num){
    int numOfStudents = num;
    int i = 0;
    LL dir;

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
        studentClass* new_student = new studentClass(fname, lname, fullM, gpa);
        //new_student->display();
        dir.addItem(new_student);
        i++;
    } while(i < numOfStudents);
    return dir;
}

int main(){
    // Randeez
    srand((unsigned)time(0));

    cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl
         << "~       Student Linked List Sorter      ~" << endl
         << "~     By Coleman Lyski and Jeet Shah    ~" << endl
         << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;

    // Generate Students
    cout << endl << endl << "Enter number of students to generate: ";
    string input;
    int num;
    getline(cin, input);
    stringstream(input) >> num;
    LL students = genStudent(num);

    while(true){
        cout << endl
             << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl
             << "~   1. Display the List     ~" << endl
             << "~   2. Sort by First Name   ~" << endl
             << "~   3. Sort by Last Name    ~" << endl
             << "~   4. Sort by GPA          ~" << endl
             << "~   5. Exit                 ~" << endl
             << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;

        do {
            cin.clear();
            cout << "Enter your choice: ";
            getline(cin, input);
            stringstream(input) >> num;
        } while(num < 1 || num > 5);

        if(num == 1){
            students.display();
        } else if(num == 5){
            break;
        } else {
            int order;
            cout << "Ascending  -- Enter 1" << endl
                 << "Descending -- Enter 2" << endl
                 << "Enter your choice: ";
            getline(cin, input);
            stringstream(input) >> order;
            if(num == 2){
                merge_sort(students.getHead(), order-1);
            }else if(num == 3){
                quick_sort(students.getHead(), order-1);
            }else{
                insertion_sort(students.getHead(), order-1);
            }
            cout << endl << "The list has been sorted in ";
            if(order==1){
                cout << "ascending order." << endl;
            }else{
                cout << "descending order." << endl;
            }
        }
    }
}