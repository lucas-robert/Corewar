#include <my_lib.h>

t_readline_node *create_node(t_readline_node *node, int fd)
{
    if (!(node = (t_readline_node *)malloc(sizeof(t_readline_node))))
        return NULL;

    node->next = NULL;
    node->fd = fd;
    node->current_line = NULL;
    return node;
}

t_readline_node *find_node(t_readline_node **head, int fd)
{
    t_readline_node *traverse;
    t_readline_node *node;

    node = NULL;
    if (*head != NULL)
    {
        traverse = *head;
        while (traverse)
        {
            if (traverse->fd == fd)
                return traverse;

            else
                traverse = traverse->next;
        }
    }

    node = create_node(node, fd);
    node->next = *head;
    *head = node;
    return node;
}

void remove_node(int fd, t_readline_node *node, t_readline_node **head)
{
    t_readline_node *before = NULL;
    node = *head;
    while (node->fd != fd)
    {
        before = node;
        node = node->next;
    }

    if (node->next)
    {
        before->next = node->next;
        *head = before;
    }
    else if (before)
    {
        before->next = NULL;
    }
    else
    {
        *head = NULL;
    }
    free(node);
    return;
}

char *my_readline(int fd)
{
    char *res = NULL;
    char buffer[READLINE_READ_SIZE + 1];
    int reader = 0;
    static t_readline_node *head = NULL;
    t_readline_node *node;

    if (fd < 0) return NULL;
    node = find_node(&head, fd);

    if (!(node->current_line))
    {
        while ((reader = read(fd, buffer, READLINE_READ_SIZE)))
        {
            buffer[reader] = '\0';
            node->current_line = concat(node->current_line, buffer);
        }
    }

    if (node && node->current_line)
    {
        res = my_strtok(node->current_line, '\n');
        node->current_line = my_strchr(node->current_line, '\n');
        return res;
    }

    if (reader == 0 && node->current_line == NULL)
    {
        free(node->current_line);
        remove_node(fd, node, &head);
    }

    return NULL;
}