#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

ListHead* create_linked_list_header() {
    ListHead* head = (ListHead*)malloc(sizeof(ListHead));
    head->first = NULL;
    head->last = NULL;
    head->size = 0;
    return head;
}

bool append_link(ListHead* head, int data) {
    if (head == NULL) {
        return false;
    }
    ListItem* link = (ListItem*)malloc(sizeof(ListItem));
    // Check initial case
    link->next = head->last;
    head->last = link;
    link->prev = NULL;
    if (link->next != NULL) {
        link->next->prev = link;
    }
    if (head->first == NULL) {
        head->first = link;
    }
    if (head->last == NULL) {
        head->last = link;
    }
    link->data = data;
    head->size++;

    return true;
}

bool insert_link(ListHead* head, int index, int data) {
    // Case 1: No elements in linked-list, just append 
    if (head == NULL || head->first == NULL) {
        return append_link(head, data);
    }

    // Grab the link at index
    int i = 0;
    ListItem* anchor = head->first;
    while ((i < index) && (anchor != NULL)) {
        anchor = anchor->prev;
        // Case 2: index out of range, just append
        if ((i > 0) && (anchor == NULL)) { 
            return append_link(head, data);
        }
        i++;   
    }
    ListItem* link = (ListItem*)malloc(sizeof(ListItem));
    link->data = data;
    link->next = anchor->next;
    link->prev = anchor;
    // Case 3: insert at beginning
    if (index == 0) {
        head->first = link;
    } else {
        anchor->next->prev = link;
    }
    anchor->next = link;

    head->size++;
    return true;
}

bool remove_link(ListHead* head, int index) {
    // Case 1: No elements in linked-list
    if (head == NULL || head->first == NULL) {
        return false;
    }

    // Grab the link at index
    int i = 0;
    ListItem* anchor = head->first;
    while (i < index) {
        anchor = anchor->prev;
        // Case 2: index out of range
        if (anchor == NULL) { 
            return false;
        }
        i++;   
    }
    if (anchor->next == NULL) {
        head->first = anchor->prev;
    } else {
        anchor->next->prev = anchor->prev;
    }
    if (anchor->prev == NULL) {
        head->last = anchor->next;
    } else {
        anchor->prev->next = anchor->next;
    }

    free(anchor);
    head->size--;

    return true;
}

void print_all_links(ListHead* head) {
    if (head == NULL || head->size == 0) {
        return;
    }
    printf("Head: %p\n\tfirst = %p\n\tlast = %p\n\tsize = %d\n", head, head->first, head->last, head->size);
    ListItem* current = head->first;
    while (current != NULL) {
        print_link(current);
        current = current->prev;
    }
}

void print_link(ListItem* link) {
    if (link == NULL) {
        return;
    }
    printf("Link: %p\n\tdata = %d\n\tnext = %p\n\tprev = %p\n", link, link->data, link->next, link->prev);
}

int free_linked_list(ListHead** head) {
    int links_freed = 0;
    if (head == NULL || *head == NULL) {
        return links_freed;
    }

    if ((*head)->first != NULL) {
        ListItem* current = (*head)->first;
        while (current != NULL)
        {
            ListItem* temp = current->prev;
            free(current);
            current = temp;
            links_freed++;
        }
    }
    free(*head);
    *head = NULL;
    return links_freed;
}
