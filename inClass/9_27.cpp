#define MAX 1000

class stack
{
	int top;
public:
	int a[MAX];

	// Constructor
	stack() {top = -1};

	// Functions
	bool push(int x);
	int pop();
	bool inEmpty();
};

bool stack::push(int x){
	if(top >= MAX){
		cout << "Stack Overflow";
		return false;
	} else {
		a[++top] = x;
		return true;
	}
}

int stack::pop(){
	if(top < 0){
		cout << "Stack Overflow";
		return 0;
	} else {
		int x = a[top--];
		return x;
	}
}

bool stack::isEmpty(){
	return (top < 0);
}