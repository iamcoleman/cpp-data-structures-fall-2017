bool listLoop(struct Node *list)
{
    struct Node *slow_ptr = list;
    struct Node *fast_ptr = list;
  
    while( slow_ptr && fast_ptr && fast_ptr->next ) {
        slow_ptr = slow_ptr->next;
        fast_ptr  = fast_ptr->next->next;
        if( slow_ptr == fast_ptr )
        {
           return true;
        }
    }

    return false;
}