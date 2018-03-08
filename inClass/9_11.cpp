/*
Insert a node at the beginning of a linked list
*/

void insertAtBeginning(node **head, node **tail, int item){
	node *ptr;
	ptr = (node*) malloc(sizeofnode());
	ptr->info = item;
	if( *head == NULL ){
		ptr->next = ptr->prev = NULL;
		*head = *tail = ptr;
	}else{
		ptr->prev = NULL;
		ptr->next = *head;
		(*head)->prev = ptr;
		*head = ptr;
	}
}

/* 
Look up why doubly linked lists are better than singly linked lists -- good interview question.
Quicker for massive lists? Saves time? 
PDA vs. TM
*/

