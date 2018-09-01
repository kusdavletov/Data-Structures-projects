## Assignment 3: Heap-based Priority Queues and Hash Maps

Priority queues and associative arrays are among the most common data structures in computer science. Some programming languages natively support these data structures even at the language level as well as in their built-in libraries. The strong support from programming languages make these data structures very easy to use—a programmer does not need to know much about their actual implementation before using them. However, the ignorance of the actual implementation of these data structures can cause inefficiency in the programs, especially when the performance of your programs depends on the running time of these data structures. In fact, a good programmer should possess the knowledge about the pros and cons of different implementations of these data structures in order to choose the right implementation for their applications.

In this exercise, you will gain the hand-on experience of two implementations of priority queues and associative arrays: heap-based priority queues and hash maps. Priority queues are often implemented by binary heaps, which offers O(log n) running time in most operations. Moreover, there is an array implementation of heaps that are space efficient. However, a proper implementation of heaps is not trivial—there are several tricks to make it works in practice. You will implement a priority queue with the following features:

- Array-based complete binary trees as the underlying implementation of the heap.
- The doubling strategy for increasing the size of the array when the heap is full.
- The support for the deletion of any element that is not the minimum element in the
priority queue.
- Location-aware entries such that the position object always refers to the same
element in the priority queue.