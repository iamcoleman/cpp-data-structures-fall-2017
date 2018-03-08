struct Node* findMiddle(struct Node *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
    {
        return NULL;
    }
 
    struct Node *slow_ptr = head;
    struct Node *fast_ptr = head;
 
    while (fast_ptr != NULL && fast_ptr->next != NULL)
    {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }

    return slow_ptr;
}