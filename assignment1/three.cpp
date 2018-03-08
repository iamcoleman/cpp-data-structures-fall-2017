void reverse(struct Node **head)
{
    if( head == NULL ){
        return;
    }

    Node *prev = NULL, *ptr = NULL, *next = NULL;
    ptr = head;

    while (ptr != NULL)
    {
        next = ptr->next;  
        ptr->next = prev;   
        prev = ptr;
        ptr = next;
    }

    head = prev;
}