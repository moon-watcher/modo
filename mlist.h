#pragma once

typedef void (*mlistFn) (void*);


typedef struct mlistNode {
	void             *data;
	struct mlistNode *next;
	struct mlistNode *prev;
}
mlistNode;


typedef struct {
    unsigned   length;
	mlistNode *head;
	mlistNode *tail;
	mlistFn    freeFn;
}
mlist;


#define mlist_foreach( l, n ) \
    for ( mlistNode *n = l->head; n; n = n->next )


void       mlist_init    ( mlist *const, mlistFn );
void       mlist_destroy ( mlist *const );
int        mlist_size    ( mlist *const );
mlistNode *mlist_add     ( mlist *const, void* );
void       mlist_remove  ( mlist *const, mlistNode* );
void       mlist_iterate ( mlist *const, mlistFn  );
