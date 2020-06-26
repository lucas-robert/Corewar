#include <my_lib.h>

t_node *init_node()
{
    t_node *new_node;

    if (!(new_node = (t_node *)malloc(sizeof(t_node))))
    {
        return NULL;
    }
    new_node->data = NULL;
    new_node->next = NULL;

    return new_node;
}

// Delete the entire list of nodes (helper function)
void delete_list(t_node **head)
{
    t_node *tmp = *head;
    t_node *cur;

    while (tmp)
    {
        cur = tmp;
        tmp = tmp->next;

        if (cur->data)
        {
            free(cur->data);
        }

        free(cur);
    }
    *head = NULL;
    return;
}

// Add node to the end of the linked list
t_node *add_node(t_node **head, void *data)
{
    t_node *new_node;
    t_node *tmp = *head;

    if (tmp->data == NULL)
    {
        tmp->data = data;
        return tmp;
    }

    if ((new_node = init_node()) == NULL) return NULL;
    new_node->data = data;

    while (tmp->next) tmp = tmp->next;

    tmp->next = new_node;

    return new_node;
}

void delete_node(t_node **head, void *data)
{

    t_node *tmp = *head;
    t_node *previous;

    if (tmp && tmp->data == data){
        *head = tmp->next;
		free(tmp->data);
        free(tmp);
        return;
    }

    while(tmp && tmp->data != data){
        previous = tmp;
        tmp = tmp->next;
    }

    if (tmp){
        previous->next = tmp->next;
        free(tmp);
        return;
    }

    return;
}
