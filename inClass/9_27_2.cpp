/*

///_.

*/
void push(node *& head, node *& tail, int data){
	if(head == NULL){
		node *n = new node;
		n->data = data;
		n->next = NULL;
		head = n;
		tail = n;
	} else {
		node *n = new node;
		n->data = data;
		n->next = next;
		head = n;
	}
}

void pop(node *& head, node *& tail){
	if(head == NULL){
		cout << "Stack is Empty";
	} else if (head == tail) {
		delete head;
		head = NULL;
		tail = NULL;
	} else {
		node *n = new node;
		n = head;
		head = head->next;
		cout << n->data;
		delete n	}
};





struct node{
	int data;
	node *next;
};

{
    node *head;
    node *tail;
}