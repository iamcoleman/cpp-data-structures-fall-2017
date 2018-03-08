void deleteNode( node *head, int n ){
	Node *ptr, *loc;
	loc = search(head, n);
	if( loc == (*node) NULL ){
		return;
	}
	ptr = loc->next;
	loc->next = ptr->next;
	free(ptr);
}