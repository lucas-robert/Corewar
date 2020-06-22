#include "my_lib.h"

void push(t_node **head, void *data)
{
    t_node *new_node = init_node();
	new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void *pop(t_node **head)
{
    if (!(*head)->data)
        return NULL;
    t_node *temp = *head;
    *head = (*head)->next;
    void *popped = temp->data;
    free(temp);
    return popped;
}
