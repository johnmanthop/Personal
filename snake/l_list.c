#include <stdlib.h>
#include <string.h>

#include "l_list.h"

struct List_Node *init_list(unsigned int data_size)
{
    struct List_Node *head = malloc(sizeof(struct List_Node));
    head->data = malloc(data_size);
    head->next = 0;
    return head;
}

void add_node(struct List_Node **node)
{
    (*node)->next = malloc(sizeof(struct List_Node));
    (*node) = (*node)->next;
    (*node)->next = 0;
}

void reserve_node(struct List_Node **node)
{
    (*node)->next = malloc(sizeof(struct List_Node));
    (*node)->next->next = 0;
}

int traverse_forward(struct List_Node **node)
{
    if ((*node)->next)
    {
        (*node) = (*node)->next;
        return 0;
    }
    return -1;
}

int set_data(struct List_Node **node, void *data, unsigned int data_size)
{
    if ((*node))
    {
        (*node)->data = malloc(data_size);
        memcpy((*node)->data, data, data_size);
        return 0;
    }
    return -1;
}

