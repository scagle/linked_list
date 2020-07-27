#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdbool.h>
#include "linked_list.h"

typedef char*(*UnitTest)(void);

// Unit Test Helper Functions
int run_unit_tests();
static char* run_unit_test(UnitTest test);
ListHead* create_simple_linked_list(int elements);
static char* test_linked_list_depth(ListHead* head, int expected_size);

// Unit Tests:
//     Legend of suffixes:
//         Defined:
//             null = container/item is NULL
//         Positional:
//             begin = index 0
//             middle = index 1 to (max-2)
//             end = (max-1) 
//             after = max to infinite
//         Size:
//             empty = container has no elements
//             not_empty = container has elements
//
static char* run_test_create_linked_list_header();
static char* run_test_free_linked_list_null();
static char* run_test_free_linked_list_empty();
static char* run_test_free_linked_list_not_empty();
static char* run_test_append_link_null_head();
static char* run_test_append_link_empty();
static char* run_test_append_link_not_empty();
static char* run_test_insert_link_null();
static char* run_test_insert_link_begin_empty();
static char* run_test_insert_link_begin_non_empty();
static char* run_test_insert_link_middle();
static char* run_test_insert_link_end();
static char* run_test_insert_link_after_empty();
static char* run_test_insert_link_after_non_empty();
static char* run_test_remove_link_null();
static char* run_test_remove_link_empty();
static char* run_test_remove_link_begin();
static char* run_test_remove_link_middle();
static char* run_test_remove_link_end();
static char* run_test_remove_link_after_empty();
static char* run_test_remove_link_after_non_empty();

#endif
