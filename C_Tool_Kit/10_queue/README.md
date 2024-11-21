# Queue
There are two basic ways to craete a queue in C.

_Array based_ that will require using fixed size, increasing the size will force us to move all the elements in the queue.

The implementation will need 3 pointers - head, tail and size. We will use the array as cyclic buffer.

_Linked List_ which obviously will require more memory for each node, because of the pointer for next and prev values.

The implemenation will need each struct to hold 3 variable, the data himself, and two pointers, next and prev.
If we can't remove from the tail than we can use only one pointer.