#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "unit_tests.h"

int main(int argc, char** argv) {
    int pos = 0;
    if (argc >= 2) {
        if (strcmp("test", argv[1]) == 0) {
            return run_unit_tests();
        }
        pos = atoi(argv[1]);
    }

    printf("Running an example with random parameters...\n");
    ListHead* head = create_linked_list_header();
    int i = 0;
    for (i = 0; i < 10; i++) {
        append_link(head, i);
    }
    insert_link(head, 0, ++i);
    insert_link(head, head->size, ++i);
    insert_link(head, 10000, ++i);
    remove_link(head, pos);

    print_all_links(head);
    free_linked_list(&head);

    return 0;
}
