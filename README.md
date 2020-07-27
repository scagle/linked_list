# Linked List Practice
Taking a udemy course on C Pointers in my spare time, and it goes over lots of Linked List implementations. 

# linked_list/
An implementation of a doubly linked list complete with unit tests. Intending to include this implementation into future lessons dealing with Queues, Stacks, and Function Pointers.

# Requirements
- C Compiler
- CMake 3.10

# Usage
```bash
# Either go into build/, or point cmake/make at the build/ directory
cd linked_list/build

# if not debugging
cmake ..
# if debugging
cmake .. -DCMAKE_BUILD_TYPE=Debug

make        # Creates an output exectuable named 'main' in the build/ directory
./main      # Run the boilerplate example
./main test # Run just the unit tests
```
