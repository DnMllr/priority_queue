#include <stdio.h>
#include "priority_queue.h"


int main ( void )
{

    int testsFailing = 0;
    char testChars[ 8 ] = { 'a', 'z', 'd', 'q',
                            'p', 'r', 'x', 'u' };
    char result[ 8 ];
    char prev;

    priority_queue * queue = priority_queue_new( 0 );

    for ( int i = 0 ; i < 8 ; i++ )
        priority_queue_push( queue, ( void * )&testChars[ i ], ( int )testChars[ i ] );

    for ( int i = 0 ; i < 8 ; i++ )
    {

       result[ i ] = *( char * )priority_queue_pop( queue );

       if ( !i ) prev = result[ i ];
       else
       {

           if ( prev > result[ i ] )
           {
               
               testsFailing = 1;
               break;

           }

           prev = result[ i ];

       }

    }

    if ( testsFailing )
    {

        fprintf( stderr, "tests failed, chars not in order: " );

        for ( int i = 0 ; i < 8 ; i++ )
            fprintf( stderr, "%c ", result[ i ] );


    } else printf( "tests succeeded!" );

    return testsFailing;

}
