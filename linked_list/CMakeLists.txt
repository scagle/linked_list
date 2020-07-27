cmake_minimum_required(VERSION 3.10)

project(Queue_scagle LANGUAGES C)

set(PROJECT_SOURCES
    src/main.c
    src/linked_list.c
    src/unit_tests.c
)

set(PROJECT_INCLUDES
    src/linked_list.h
    src/unit_tests.h
)

set(EXTERNAL_INCLUDES
    src/external/minunit.h
)


add_executable(Queue_scagle ${PROJECT_SOURCES} ${PROJECT_INCLUDES} ${EXTERNAL_INCLUDES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
