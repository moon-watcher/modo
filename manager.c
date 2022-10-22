#include <genesis.h>
#include "manager.h"


static void         _removeAll      ( ManagerNode *const );
static int          _count          ( ManagerNode *const );
static ManagerNode* _findInCache    ( ManagerList *const, unsigned );
static void         _addToList      ( ManagerList *const, ManagerNode *const );
static void         _removeFromList ( ManagerList *const, ManagerNode *const );

inline static void create ( Manager *const, ManagerNode *const );
inline static void update ( Manager *const, ManagerNode *const );
inline static void change ( Manager *const, ManagerNode *const );
inline static void delete ( Manager *const, ManagerNode *const );

static void ( *actions [ ] ) ( ) = { create, update, change, delete };



Manager *manager ( ) {
    Manager *manager = malloc ( sizeof ( Manager ) );
    memset ( &manager->entities, 0, sizeof ( ManagerList ) );
    memset ( &manager->cache,    0, sizeof ( ManagerList ) );

    return manager;
}


Entity *managerAdd ( Manager *const manager, Entity const* template ) {
    ManagerNode *node = _findInCache ( &manager->cache, template->compsSize );
    
    if ( node ){
        entityInit ( node->entity, template );
        _removeFromList ( &manager->cache, node );
    }
    else {
        node = malloc ( sizeof ( ManagerNode ) );
        node->entity = entity ( template );
    }    

    _addToList ( &manager->entities, node );

	return node->entity;
}


void managerUpdate ( Manager *const manager ) {
    for ( ManagerNode *n = manager->entities.head; n; n = n->next )
        actions [ n->entity->action ] ( &manager, n );

    // ManagerNode *node = manager->entities.head;
    
    // while ( node ) {
    //     actions [ node->entity->action ] ( &manager, node );
    //     node = node->next;
    // }
}


void managerEnd ( Manager *const manager ) {
    _removeAll ( manager->entities.head );
    _removeAll ( manager->cache.head    );

    free ( manager );
}


int managerCount ( Manager *const manager ) {
    return manager->entities.count;
}


int managerCountCache ( Manager *const manager ) {
    return manager->cache.count;
}



#define XE( F, E )            F ( E )
#define XS( F, E )   if ( F ) F ( E )

inline static void create ( Manager *const manager, ManagerNode *const node ) {
    Entity *const entity = node->entity;

    XE ( entity->Awake,        entity );
    XS ( entity->state->enter, entity );

    entity->action = ENTITY_ACTION_UPDATE;
        
    update ( manager, node );
}


inline static void update ( Manager *const manager, ManagerNode *const node ) {
    Entity *const entity = node->entity;
    
    XE ( entity->Update,        entity );
    XS ( entity->state->update, entity );

    manager->entities.prev = node;
}


inline static void change ( Manager *const manager, ManagerNode *const node ) {
    Entity *const entity = node->entity;

    XS ( entity->prevState->exit, entity );
    XS ( entity->state->enter,    entity );

    entity->action = ENTITY_ACTION_UPDATE;
    update ( manager, node );
}


inline static void delete ( Manager *const manager, ManagerNode *const node ) {
    Entity *const entity = node->entity;

    XS ( entity->state->exit, entity );
    XE ( entity->Delete,      entity );

    // remove node from entities list
    if ( manager->entities.prev->next )
        manager->entities.prev->next = node->next;
    
    // move node to cache list
    //if ( manager->cache.head )
    manager->cache.head->next = manager->cache.head;
    manager->cache.head = node;
}


static void _removeAll ( ManagerNode *const head ) {
    ManagerNode *node = head;
    
    while ( node ) {
        Entity      *const entity = node->entity;
        ManagerNode *const next   = node->next;

        free ( entity->components );
        free ( entity );
        free ( node );

        node = next;
    }
}


static ManagerNode *_findInCache ( ManagerList *const mh, unsigned compsSize ) {
    mh->prev = NULL;
    ManagerNode *node = mh->head;

    while ( node ) {
        if ( node->entity->compsSize == compsSize )
            return node;

        mh->prev = node;
        node = node->next;
    }

    return NULL;
}


static void _addToList ( ManagerList *const mh, ManagerNode *const node ) {
    ++mh->count;

    if ( mh->head )
        mh->tail->next = node;
    else
        mh->head = node;
        
    mh->tail = node;
    node->next = NULL;
}


static void _removeFromList ( ManagerList *const mh, ManagerNode *const node ) {
    --mh->count;

    if ( mh->prev )
        mh->prev->next = node->next;
    else
        mh->head = node->next;

    node->next = NULL;
}