
#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_

/**
 * The minimum size of the priority queue starts at 8
 *
 * if you would like to set a different minimum size you can #define
 * before the include like so
 * 
 *      #define PRIORITY_QUEUE_MINIMUM_SIZE 16
 *      #include "priority_queue.h"
 *
 */
#ifndef PRIORITY_QUEUE_MINIMUM_SIZE
#define PRIORITY_QUEUE_MINIMUM_SIZE 8
#endif

/**
 * Private struct that represents the element within the priority queue.
 * It has a void pointer member that points to some data as well as an int that 
 * represents the priority of this element.
 */
struct priority_queue_el_ {
    void * data;
    int priority;
};

/**
 * The priority queue type. Has two private members: el_buffer_, which 
 * is a binary heap of elements, and size_, which is the current size
 * of that buffer. There is also a public member length, which is the current
 * number of elements in the queue.
 */
typedef struct priority_queue_ {
    struct priority_queue_el_ * el_buffer_;
    int size_;
    int length;
} priority_queue;

/**
 * Allocates a priority queue and returns a pointer to that queue. In the case of
 * an allocation failure, returns a NULL pointer.
 */
priority_queue * priority_queue_new ( int size );

/**
 * Deallocates a priority queue.
 */
void priority_queue_delete ( priority_queue * queue );

/**
 * Pushes data into the priority queue. Pass a void pointer to the data along
 * with an int for the priority of the data. Returns -1 on failure and the new length
 * of the queue on success.
 */
int priority_queue_push ( priority_queue * queue, void * data, int priority );

/**
 * Pops a pointer to the current highest priority data out of the priority_queue.
 * Returns NULL if empty.
 */
void * priority_queue_pop ( priority_queue * queue );

#endif

