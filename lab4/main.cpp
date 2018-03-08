/*
 *
 * Coleman Lyski
 * Lab 4
 * 23 September 2017
 *
 */

#include <cstddef>
#include <iostream>
#include <ctime>


using namespace std;

// Set the maximum length
#define LEN 10


template <class T>
class orderedList {
protected:
    T *arr[LEN] = {};
    int length;
    int tick;

public:
    // Initiate values and array
    orderedList() : length(0), tick(0), arr() {}

    int getTicks();
    int getLength();
    void addItem(T item);
    void removeItem(T item);
    int getItem(int pos);
    bool isEmpty();
    bool isFull();
    void makeEmpty();
    void displayList();

    // Overloaded operators
    bool operator<(const orderedList &ol){
        return length < ol.length;
    }

    bool operator>(const orderedList &ol){
        return length > ol.length;
    }

    bool operator==(orderedList &ol){
        if(length != ol.length){
            return false;
        }
        for(int i = 0; i < LEN; i++){
            if(*arr[i] != ol.getItem(i)) {
                return false;
            }
        }
        return true;
    }
};

template <class T>
int orderedList<T>::getTicks()
{
    return tick;
}

template <class T>
int orderedList<T>::getLength()
{
    return length;
}

template <class T>
void orderedList<T>::addItem(T item)
{
    // Throw List Full
    if(length == LEN) throw invalid_argument("Add Item Error - List Full");

    // Create new array item
    T *cookies = new T;
    T *hold = new T;
    *cookies = item;

    // Loop through list, bump back everything after insertion
    for( int i = 0; i <= length; i++ ){
        if(arr[i] == NULL || *arr[i] > item){
            hold = arr[i];
            arr[i] = cookies;
            cookies = hold;
            tick = tick + 3;
        }
        tick = tick + 2;
    }

    length++;
}

template <class T>
void orderedList<T>::removeItem(T item)
{
    // Throw list empty
    if( length == 0 ) throw invalid_argument("Remove Item Error - List Empty");

    // Start from back, shift all items down after deletion
    for(int i = 0; i < length - 1; i++){
        if(*arr[i] == item){
            *arr[i] = item = *arr[i+1];
            tick++;
        }
        tick = tick + 2;
    }

    tick++;

    if(*arr[length-1] == item){
        // Delete duplicate pointer at the end
        delete arr[length-1];
        arr[length-1] = NULL;
        length--;
    }else{
        // Throw item not in list
        throw invalid_argument("Remove Item Error - Item not in List");
    }
}

template <class T>
int orderedList<T>::getItem(int pos)
{
    if( arr[pos] != NULL ){
        return *arr[pos];
    }else{
        throw invalid_argument("Get Item Error - Item not in List");
    }
}

template <class T>
bool orderedList<T>::isEmpty()
{
    for( int i = 0; i < LEN; i++ ){
        if( arr[i] != NULL )
            return false;
    }
    return true;
}

template <class T>
bool orderedList<T>::isFull()
{
    for( int i = LEN - 1; i >= 0; i-- ){
        if( arr[i] == NULL ){
            return false;
        }
    }
    return true;
}

template <class T>
void orderedList<T>::makeEmpty()
{
    for( int i = 0; i < LEN; i++ ){
        if( arr[i] != NULL ){
            delete arr[i];
            arr[i] = NULL;
        }
    }
}

template <class T>
void orderedList<T>::displayList(){
    for(int i = 0; i < length; i++){
        cout << "Position " << i+1 << ": " << *arr[i] << endl;
    }
}



//
// START AT END
//
class startEnd : public orderedList<int>{
public:
    void addItemEnd(int item) {
        // Throw list full
        if( length == LEN ) throw invalid_argument("Add Item Error - List Full");

        // Make a new int to go in arr and set to item
        int *cookies = new int, i;
        *cookies = item;

        // Start from back and bump every item back one until insertion
        for( i = length; i > 0; i-- ){
            if( *arr[i-1] > item ){
                arr[i] = arr[i-1];
                tick++;
            }else{
                break;
            }
            tick = tick + 2;
        }

        arr[i] = cookies;
        length++;
        tick = tick + 1;
    }
};



//
// Leave blank spaces
//
class leaveBlanks : public orderedList<int> {
public:
    void addItemBlanks(int item) {
        // Throw list full
        if (length == LEN) throw invalid_argument("Add Item Error - List Full");

        // Create all ints
        int prev = 0;
        int next = 0;
        int *cookies = new int;
        int blank = LEN;
        *cookies = item;

        // Find the item below and item above
        for (int i = 0; i < LEN; i++) {
            if (arr[i] && *arr[i] >= item) {
                next = i;
                tick = tick + 2;
                break;
            } else if (arr[i] && *arr[i] < item) {
                prev = i;
                tick = tick + 3;
            } else {
                next = i;
                blank = i;
                tick = tick + 3;
            }
            tick = tick + 1;
        }

        // Set the half way point
        int halfer = (next - prev) / 2 + prev;

        // Check to see if any spaces are filled
        if (arr[halfer]) {
            int i = halfer;
            int *hold1 = arr[i];
            int *hold2;
            tick = tick + 1;

            if (blank < halfer) {
                // Shift items down
                while (hold1) {
                    hold2 = arr[i - 1];
                    arr[i - 1] = hold1;
                    hold1 = hold2;
                    i--;
                    tick = tick + 3;
                }
            } else {
                if (*arr[i] < item) {
                    halfer++;
                    tick = tick + 1;
                }
                // shift items up
                while (hold1) {
                    hold2 = arr[i + 1];
                    arr[i + 1] = hold1;
                    hold1 = hold2;
                    i++;
                    tick = tick + 3;
                }
            }
        }

        arr[halfer] = cookies;
        length++;
        tick = tick + 1;
    }

    void removeItemBlanks(int item) {
        if(length == 0) throw invalid_argument("Remove Item Error - List is Empty");
        for(int i = 0; i < LEN; i++){
            if(arr[i] && *arr[i] == item){
                delete arr[i];
                arr[i] = NULL;
                length--;
                return;
            }
            tick = tick + 2;
        }
        cout << "Item not in list" << endl;
        return;
    }

    void displayListBlanks() {
        for (int i = 0; i < LEN; i++) {
            if (arr[i]) {
                cout << "Position " << i+1 << ": " << *arr[i] << endl;
            } else {
                cout << "Position " << i+1 << ": " << "Empty" << endl;
            }
        }
    }
};



/*
 * Testing Main Function
 */


int main() {
    const int items_to_be_removed = 5, trials = 100;

    srand((unsigned)time(0));
    unsigned int temp;
    int tot1 = 0;
    int tot2 = 0;
    int tot3 = 0;

    for(int x = 0; x < trials; x++){
        orderedList<int> t1;
        startEnd t2;
        leaveBlanks t3;

        // Fill the lists
        for(int i = 0; i < LEN; i++){
            temp = rand() % LEN + 1;
            t1.addItem(temp);
            t2.addItemEnd(temp);
            t3.addItemBlanks(temp);
        }

        // Remove a random item
        for(int i = 0; i < items_to_be_removed; i++){
            temp = rand() % t1.getLength();
            temp = t1.getItem(temp);
            t1.removeItem(temp);
            t2.removeItem(temp);
            t3.removeItemBlanks(temp);
        }

        // Add to the totals
        tot1 += t1.getTicks();
        tot2 += t2.getTicks();
        tot3 += t3.getTicks();
    }

    // Display all the averages
    cout << endl << "Added: " << LEN << endl;
    cout << "Deleted: " << items_to_be_removed << endl;
    cout << "Trials: " << trials << endl;
    cout << "Starting from Front - Averaged " << tot1/trials << " operations" << endl;
    cout << "Starting from Back - Averaged " << tot2/trials << " operations" << endl;
    cout << "Leaving Blanks - Averaged " << tot3/trials << " operations" << endl;

    getchar();
}
