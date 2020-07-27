#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct sListItem ListItem;
typedef struct sListHead ListHead;

struct sListItem {
    ListItem* next;
    ListItem* prev;
    int data;
};

struct sListHead {
    ListItem* first;
    ListItem* last;
    int size;
};


ListHead* create_linked_list_header();
bool append_link(ListHead* head, int data);
bool insert_link(ListHead* head, int index, int data);
bool remove_link(ListHead* head, int index);

void print_all_links(ListHead* head);
void print_link(ListItem* link);

int free_linked_list(ListHead** head);

#endif
