
/**
 * Priority Queue
 * Author: Dan Miller
 */

#include <stdlib.h>
#include <stdio.h>
#include "./priority_queue.h"



priority_queue * priority_queue_new ( int size )
{

    // set the size to the minimum size
    if ( size < 8 ) size = PRIORITY_QUEUE_MINIMUM_SIZE;

    // malloc the priority_queue
    priority_queue * queue = ( priority_queue * ) malloc( sizeof( priority_queue ) );

    // malloc the inner buffer
    queue->el_buffer_ = ( struct priority_queue_el_ * ) malloc( sizeof( struct priority_queue_el_ ) * size );

    // set the size
    queue->size_ = size;
    queue->length = 0;

    return queue;

}



void priority_queue_delete ( priority_queue * queue )
{

    // first free the inner buffer
    free( queue->el_buffer_ );

    // then free the queue itself
    free( queue );

}



/**
 * realloc takes a queue and reallocates its buffer such that the size of the buffer matches the size_
 * member of the queue. This function is private and assumes the the size of the queue was set
 * prior to being called.
 */
static int buffer_realloc_ ( priority_queue * queue )
{

    struct priority_queue_el_ * temp_buffer;

    temp_buffer = realloc( queue->el_buffer_, sizeof( struct priority_queue_el_ ) * queue->size_ );

    if ( temp_buffer == NULL ) return -1;

    queue->el_buffer_ = temp_buffer;

    return 0;

}



/**
 * Private function which inserts data into the buffer
 */
static void buffer_insert_ ( struct priority_queue_el_ * buffer, int length, void * data, int priority )
{

    int current_position;
    int current_parent;

    // set the current_position to the last item
    // The "1 +" is because the array is 1-indexed
    current_position = 1 + length;

    // that positions parent is at is the current_position / 2
    // because this is a binary tree
    current_parent = current_position / 2;

    while ( current_parent && priority <= buffer[ current_parent ].priority )
    {

        buffer[ current_position ] = buffer[ current_parent ];
        current_position = current_parent;
        current_parent /= 2;

    }

    buffer[ current_position ].data = data;
    buffer[ current_position ].priority = priority;

}



/**
 * Private function that repairs the buffer after removal
 */
static void buffer_repair_ ( struct priority_queue_el_ * buffer, int length )
{
    
    struct priority_queue_el_ * last_item;
    int current_position;
    int current_descendent;
    
    // decrement the length because an item is going to be removed
    last_item = buffer + length;
    current_position = 1;
    current_descendent = 2;

    while ( current_descendent < length )
    {

        // current_descendent is whichever of the two children has the highest priority,
        // assuming both children exist
        if (
                current_descendent + 1 < length &&
                buffer[ current_descendent + 1 ].priority < buffer[ current_descendent ].priority
           ) current_descendent++;


        if ( last_item->priority <= buffer[ current_descendent ].priority ) break;

        buffer[ current_position ] = buffer[ current_descendent ];
        current_position = current_descendent;
        current_descendent *= 2;

    }

    // set the last item to its proper position in the heap
    buffer[ current_position ] = *last_item;

}



int priority_queue_push ( priority_queue * queue, void * data, int priority )
{

    // if it is necessary... 
    if ( queue->length >= queue->size_ )
    {

        // double the size of the queue
        queue->size_ *= 2;
        
        // on allocation failure return -1
        if ( buffer_realloc_( queue ) ) return -1;

    }

    // insert the data into the buffer
    buffer_insert_( queue->el_buffer_, queue->length, data, priority );

    return ++queue->length;

}



void * priority_queue_pop ( priority_queue * queue )
{
    
    struct priority_queue_el_ * buffer;
    void * data;

    if ( queue->length == 0 ) return NULL;

    buffer = queue->el_buffer_;
    data = buffer[ 1 ].data; // buffer[ 1 ] is about to be overwritten

    buffer_repair_( buffer, queue->length-- );

    // when the queue shrinks past half the allocated size realloc the queue
    // unless the queue is already equal to the minimum size
    if ( queue->length < queue->size_ / 2 && queue->size_ > PRIORITY_QUEUE_MINIMUM_SIZE )
    {

        queue->size_ /= 2;
        if ( buffer_realloc_( queue ) ) return NULL;

    }

    return data;

}


