#include <genesis.h>
#include "mlist.h"


static int const mlistNode_s = sizeof ( mlistNode );


void mlist_init ( mlist *list, mlistFn freeFn ) {
    list->length = 0;
    list->head   = ((void*)0);
    list->tail   = ((void*)0);
    list->freeFn = freeFn;
}


void mlist_destroy ( mlist *list ) {
    mlist_foreach ( list, node )
		mlist_remove ( list, node );
}


int mlist_size ( mlist *list ) {
	return list->length;
}


mlistNode *mlist_add ( mlist *list, void *element ) {
	mlistNode *node = malloc ( mlistNode_s );

    node->data = element;
    node->next = NULL;

    if ( list->head == NULL ) {
        list->head       = node;
        list->tail       = node;
        list->head->prev = NULL;
    }
    else {
        node->prev       = list->tail;
        list->tail->next = node;
        list->tail       = node;
    }
}


void mlist_remove ( mlist *list, mlistNode *node ) {
    if ( !(list->length && list->head && node) )
        return;

    if ( list->freeFn )
        list->freeFn ( node->data );

    if ( list->head == node )
        list->head = node->next;

    if ( node->next )
        node->next->prev = node->prev;

    if ( node->prev )
        node->prev->next = node->next;
 
    --list->length;
    free ( node );
}


void mlist_iterate ( mlist *list, mlistFn iterator ) {
    mlist_foreach ( list, node )
        iterator ( node->data );
}


// mlistNode *node = list->head;
// while ( node )
// {
//     iterator ( node->data );
//     node = node->next;
// }