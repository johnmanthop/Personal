#ifndef L_LIST_H_INCLUDED
#define L_LIST_H_INCLUDED

struct List_Node
{
    void *data;
    struct List_Node *next;
};

struct List_Node *init_list(unsigned int data_size);

void reserve_node(struct List_Node **node);

void add_node(struct List_Node **node);

int traverse_forward(struct List_Node **node);

int set_data(struct List_Node **node, void *data, unsigned int data_size);

#endif // L_LIST_H_INCLUDED
