Node *nthToLast( Node *head, int n )
{
    Node *ptr;
    Node *back;
    ptr = head;
    for( int i = 0; i < n; i++ ) {
        if( ptr->next != NULL ) {
            ptr = ptr->next;
        } else {
            return NULL;
        }
    }
    back = head;
    while( ptr->next ) {
        ptr = ptr->next;
        back = back->next;
    }
    if( n == 0 ){
        return ptr;
    } else {
        return back;
    }
}