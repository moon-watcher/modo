#include <genesis.h>
#include "manager.h"


static void _appendToCache ( Manager *const manager, ManagerNode *const node ) {
    if ( manager->cache.head )
        manager->cache.head->next = manager->cache.head;

    manager->cache.head = node;
}


static void _removeFromCache ( Manager *const manager, ManagerNode *const node ) {
    --manager->cache.count;

    if ( manager->prevNode )
        manager->prevNode->next = node->next;
    else
        manager->cache.head = node->next;

    node->next = NULL;
}


static ManagerNode *_findInCache ( Manager *const manager, unsigned compsSize ) {
    ManagerNode *node = manager->cache.head;
    manager->prevNode = NULL;

    while ( node ) {
        if ( node->entity->compsSize == compsSize )
            return node;

        manager->prevNode = node;
        node = node->next;
    }

    return NULL;
}


static void _appendToEntities ( Manager *const manager, ManagerNode *const node ) {
    ++manager->entities.count;

    if ( manager->entities.head )
        manager->entities.tail->next = node;
    else
        manager->entities.head = node;
        
    manager->entities.tail = node;
    node->next = NULL;
}


static void _removeFromEntities ( Manager *const manager, ManagerNode *const node ) {
    if ( manager->prevNode->next )
        manager->prevNode->next = node->next;
}


static void _removeAll ( ManagerNode *const headNode ) {
    ManagerNode *node = headNode;
    
    while ( node ) {
        Entity      *const entity = node->entity;
        ManagerNode *const next   = node->next;

        free ( entity->components );
        free ( entity );
        free ( node );

        node = next;
    }
}




Manager *manager ( ) {
    Manager *manager = malloc ( sizeof ( Manager ) );
    memset ( &manager->entities, 0, sizeof ( ManagerList ) );
    memset ( &manager->cache,    0, sizeof ( ManagerList ) );

    return manager;
}


Entity *managerAdd ( Manager *const manager, Entity const* template ) {
    ManagerNode *node = _findInCache ( manager, template->compsSize );
    
    if ( node ) {
        entityInit ( node->entity, template );
        _removeFromCache ( manager, node );
    }
    else {
        node = malloc ( sizeof ( ManagerNode ) );
        node->entity = entity ( template );
    }    

    _appendToEntities ( manager, node );

	return node->entity;
}


void managerUpdate ( Manager *const manager ) {
    ManagerNode *node = manager->entities.head;

    while ( node ) {
        Entity *const entity = node->entity;
        State  *const state  = entity->state;

        switch ( entity->action ) {
            case ENTITY_CHANGE:
                entity->prevState->exit ( entity );

            case ENTITY_CREATE:
                state->enter ( entity );
                entity->action = ENTITY_UPDATE;

            case ENTITY_UPDATE:
                state->update ( entity );            
                break;

            default: // case ENTITY_DELETE:
                state->exit ( entity );

                _removeFromEntities ( manager, node );
                _appendToCache ( manager, node );
        }
        
        manager->prevNode = node;
        node = node->next;
    }
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