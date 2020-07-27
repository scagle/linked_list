#include <stdio.h>
#include <stdlib.h>
#include "unit_tests.h"
#include "external/minunit.h"

/* Local helper function headers */
static char* test_free_linked_list(ListHead** head);
static char* test_linked_list_depth(ListHead* head, int expected_size);
static char* test_data_sequence(ListHead* head, int *sequence, int sequence_length);
static char* evaluate_operation_result(ListHead** head, int* sequence, int sequence_length, bool want, bool got);

int tests_run = 0; // incremented by minunit.h macros

static UnitTest unit_tests[] = {
    run_test_create_linked_list_header,
    run_test_free_linked_list_null,
    run_test_free_linked_list_empty,
    run_test_free_linked_list_not_empty,
    run_test_append_link_null_head,
    run_test_append_link_empty,
    run_test_append_link_not_empty,
    run_test_insert_link_null,
    run_test_insert_link_begin_empty,
    run_test_insert_link_begin_non_empty,
    run_test_insert_link_middle,
    run_test_insert_link_end,
    run_test_insert_link_after_empty,
    run_test_insert_link_after_non_empty,
    run_test_remove_link_null,
    run_test_remove_link_empty,
    run_test_remove_link_begin,
    run_test_remove_link_middle,
    run_test_remove_link_end,
    run_test_remove_link_after_empty,
    run_test_remove_link_after_non_empty,
};

int run_unit_tests() {
    printf("Unit Tests:\n");
    const size_t num_unit_tests = sizeof(unit_tests) / sizeof(unit_tests[0]);
    if (num_unit_tests == 0) {
        printf("*** Warning: No Unit Tests!\n");
        return 1;
    }

    int failed = 0;
    for (int i = 0; i < num_unit_tests; i++) {
        char* message = run_unit_test(unit_tests[i]);
        if (message != 0) {
            printf("unit_tests[%d] failed:\n'%s'\n\n", i, message);
            failed++;
        }
    }

    printf("Ran '%d' Unit Tests!\n'%d' Passes, '%d' Failures\n", tests_run, tests_run-failed, failed);
    return (failed);
}

static char* run_unit_test(UnitTest test) {
    mu_run_test(test);
    return 0;
}

ListHead* create_simple_linked_list(int elements) {
    ListHead* head = create_linked_list_header();
    ListItem* temp = NULL;
    int i;
    for (i = 0; i < elements; i++) {
        ListItem* link = (ListItem*)malloc(sizeof(ListItem));
        link->data = i;
        link->next = temp;
        link->prev = NULL;
        if (i == 0) {
            head->first = link;
        } else {
            temp->prev = link;
        }        
        temp = link;
    }
    head->last = temp;
    head->size = i;
    return head;
}

/* Local helper functions */
static char* test_free_linked_list(ListHead** head) {
    // Test if free did it's job
    if (head == NULL || *head == NULL) {
        free_linked_list(head);
        return 0;
    }
    int linked_list_size = (*head)->size;
    int links_freed = free_linked_list(head);
    mu_assert("links_freed != linked_list_size", links_freed == linked_list_size);
    mu_assert("head was not set to NULL after free", (*head) == NULL);
    return 0;
}


static char* test_linked_list_depth(ListHead* head, int expected_size) {
    // Test depth of linked_list (deprecated to test_data_sequence)
    mu_assert("Running test_linked_list_depth on NULL head", head != NULL);
    int actual_size = 0;
    ListItem* link = head->first;
    while (link != NULL) {
        link = link->prev;
        actual_size++;
    }
    mu_assert("linked list actual size doesn't equal expected size", actual_size == expected_size);
    return 0;
}

static char* test_data_sequence(ListHead* head, int *sequence, int sequence_length) {
    // Test if the linked list exactly matches a sequence of integers
    mu_assert("Running test_data_sequence on NULL head", head != NULL);
    int index = 0;
    ListItem* link = head->first;
    while (link != NULL) {
        if (index < sequence_length) {
            mu_assert_format("linked_list['%d'] != sequence['%d']\n(%d != %d)", // format message
                link->data == sequence[index],                                  // test
                link->data, sequence[index], link->data, sequence[index]        // inputs to format message
            );
        }
        link = link->prev;
        index++;
    }
    mu_assert_format("linked list size was %d, and sequence length was %d", 
        index == sequence_length, 
        index, sequence_length
    );
    return 0;
}

static char* evaluate_operation_result(ListHead** head, int* sequence, int sequence_length, bool result, bool desired_result) {
    // Evaluates the output from a linked list data operation, checks values and expected operation success/failure.
    // Also frees at the end
    mu_assert_format("Expected linked list operation to be %s, result %s", 
        desired_result == result, 
        desired_result ? "Successful" : "Failure", 
        result ? "Successful" : "Failure"
    );
    mu_assert_format("Head size doesn't match up: (%d != %d)", 
        (*head)->size == sequence_length, 
        (*head)->size, 
        sequence_length
    );
    char* message = test_data_sequence(*head, sequence, sequence_length);
    return test_free_linked_list(head);
}

/* Unit Tests */
static char* run_test_create_linked_list_header() {
    printf("Running run_test_create_linked_list_header()\n");
    ListHead* head = create_linked_list_header();
    mu_assert("head == NULL", head != NULL);
    mu_assert("head->first != NULL", head->first == NULL);
    mu_assert("head->last != NULL", head->last == NULL);
    mu_assert("head->size != 0", head->size == 0);
    free_linked_list(&head);
    return 0;
}

static char* run_test_free_linked_list_null() {
    printf("Running run_test_free_linked_list_null()\n");
    return test_free_linked_list(NULL);
}

static char* run_test_free_linked_list_empty() {
    printf("Running run_test_free_linked_list_empty()\n");
    ListHead* head = create_linked_list_header();
    free_linked_list(&head);
    return test_free_linked_list(&head);
}

static char* run_test_free_linked_list_not_empty() {
    printf("Running run_test_free_linked_list_not_empty()\n");
    ListHead* head = create_simple_linked_list(3);
    free_linked_list(&head);
    return test_free_linked_list(&head);
}

static char* run_test_append_link_null_head() {
    printf("Running run_test_append_link_null_head()\n");
    bool result = append_link(NULL, 5);
    mu_assert("append_link is successful on NULL head (it shouldn't be)", result == false);
    return 0;
}

static char* run_test_append_link_empty() {
    printf("Running run_test_append_link_empty()\n");
    ListHead* head = create_linked_list_header();
    bool result = append_link(head, 5);
    int sequence[] = {5};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_append_link_not_empty() {
    printf("Running run_test_append_link_not_empty()\n");
    ListHead* head = create_simple_linked_list(3);
    bool result = append_link(head, 3);
    int sequence[] = {0, 1, 2, 3};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_insert_link_null() {
    printf("Running run_test_insert_link_null()\n");
    bool result = insert_link(NULL, 0, 5);
    mu_assert("insert_link is successful on NULL head (it shouldn't be)", result == false);
    return 0;
}

static char* run_test_insert_link_begin_empty() {
    printf("Running run_test_insert_link_begin_empty()\n");
    ListHead* head = create_linked_list_header();
    bool result = insert_link(head, 0, 2);
    int sequence[] = {2};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_insert_link_begin_non_empty() {
    printf("Running run_test_insert_link_begin_non_empty()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = insert_link(head, 0, 13);
    int sequence[] = {13, 0, 1, 2, 3, 4};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_insert_link_middle() {
    printf("Running run_test_insert_link_middle()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = insert_link(head, 2, 14);
    int sequence[] = {0, 1, 14, 2, 3, 4};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_insert_link_end() {
    printf("Running run_test_insert_link_end()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = insert_link(head, 5, 15);
    int sequence[] = {0, 1, 2, 3, 4, 15};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_insert_link_after_empty() {
    printf("Running run_test_insert_link_after_empty()\n");
    ListHead* head = create_linked_list_header();
    bool result = insert_link(head, 5, 16);
    int sequence[] = {16};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);

}

static char* run_test_insert_link_after_non_empty() {
    printf("Running run_test_insert_link_after_non_empty()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = insert_link(head, 100, 16);
    int sequence[] = {0, 1, 2, 3, 4, 16};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_remove_link_null() {
    printf("Running run_test_remove_link_null()\n");
    bool result = remove_link(NULL, 0);
    mu_assert("remove_link is successful on NULL head (it shouldn't be)", result == false);
    return 0;
}

static char* run_test_remove_link_empty() {
    printf("Running run_test_remove_link_empty()\n");
    ListHead* head = create_linked_list_header();
    bool result = remove_link(head, 0);
    int sequence[] = {};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, false);
}

static char* run_test_remove_link_begin() {
    printf("Running run_test_remove_link_begin()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = remove_link(head, 0);
    int sequence[] = {1, 2, 3, 4};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_remove_link_middle() {
    printf("Running run_test_remove_link_middle()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = remove_link(head, 2);
    int sequence[] = {0, 1, 3, 4};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_remove_link_end() {
    printf("Running run_test_remove_link_end()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = remove_link(head, 4);
    int sequence[] = {0, 1, 2, 3};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, true);
}

static char* run_test_remove_link_after_empty() {
    printf("Running run_test_remove_link_after_empty()\n");
    ListHead* head = create_linked_list_header();
    bool result = remove_link(head, 100);
    int sequence[] = {};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, false);
}

static char* run_test_remove_link_after_non_empty() {
    printf("Running run_test_remove_link_after_non_empty()\n");
    ListHead* head = create_simple_linked_list(5);
    bool result = remove_link(head, 100);
    int sequence[] = {0, 1, 2, 3, 4};
    int length = sizeof(sequence)/sizeof(sequence[0]);
    return evaluate_operation_result(&head, sequence, length, result, false);
}

