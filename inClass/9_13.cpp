/*

#######################
#   Data Structures   #
#      In Class       #
#     09/13/2017      #
#######################

*/

// Traverse from head to tail
void traverseInOrder(node *head){
	while(head != NULL){
		cout << head->info;
		head = head->next;
	}
}

// Traverse from tail to head
void traverseReverseOrder(node *tail){
	while(tail != NULL){
		cout << tail->info;
		tail = tail->prev;
	}
}


// Search linked list for an item
node *search(node *head, int item){
	while( head != NULL ){
		if( head->info == item ){
			return head;
		}
		head = head->next;
	}
}