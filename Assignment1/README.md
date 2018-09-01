## Assignment 1: Circularly Linked Lists

Although the concepts of linked lists, stacks, queues, etc. are quite simple, they actually require you to have a good programming skill and a great deal of knowledge about OOP and templates in C++ in order to come up with a good implementation that is safe, easy to use, and high performance. In this assignment, you are given the opportunities to implement a circularly linked list with available space lists. In addition, you will use the data structure to implement a stack-based algorithm for evaluating a numerical expression by converting the expression into postfix notation. Hopefully you can gain further insights into these data structures while implementing them in C++.

All parts of the assignment were implemented and I think everything works fine.

### assignment1.cpp:

- getPriority function:
The getPriority function takes the token of the operator and returns its priority. Also, the function throws errors when token is not operator or ')'. The higher the priority of an operator is, the smaller the number this function returns.

- getInStackPriority function:
The getInStackPriority function takes the token of the operator and returns its priority. Also, the function throws errors when token is not operator or ')'. It returns the in-stack priority, which gives '(' lowest priority.

- postfix function:
The postfix function takes the expression and convert it from infix notation into an expression in postfix notation. The expressions are stored as a vector of tokens.

- eval function:
The eval function takes the expression (vector of tokens) in the postfix notation and evaluates it to integer.

### CircularList.h:

- pointer cursor:
Pointer to the last element in the Circular list.

- pointer av:
Pointer to the first element in the available space list.

- variable count:
Used to count the number of elements in the Circular list.

- variable av_count;
Used to count the length of available space list.

- CircularList():
Constructor of the Circular list, initiates values to zero.

- ~CircularList():
Destructor of the Circular list, passes everything to available space list and delete the available space list.

- empty() function:
Check whether the circular list is empty.

- front() function:
Return a reference to the first element in the circular list.

- back() function:
Return a reference to the last element in the circular list.

- advance() function:
Advance the cursor to the next element in the circular list.

- add() function:
Add an element after the cursor. If possible use available space.

- remove() function:
Remove the node after the cursor and add to available space list.

- size() function:
Return the size of the circular list.

- reverse() function:
Reserve the circular list.

- cleanup() function:
Free the memory all unused nodes in the available space list.