#include <genesis.h>
#include "entity.h"

static const int Entity_s = sizeof ( Entity );


Entity *entity ( Entity const* template ) {
    Entity *entity;
    
    entity = malloc ( Entity_s );
    memcpy ( entity, template, Entity_s );

    entity->components = malloc ( template->compsSize );
    memcpy ( entity->components, template->components, template->compsSize );

    entity->action = ENTITY_CREATE;

    return entity;
}


void entityInit ( Entity *const entity, Entity const* template ) {
    memcpy ( entity, template, Entity_s );
    memcpy ( entity->components, template->components, template->compsSize );

    entity->action = ENTITY_CREATE;
}


void entityState ( Entity *const entity, State const* newState ) {
    if ( newState == entity->state )
        return;

    entity->prevState = entity->state;
    entity->state     = /* (State*) */ newState;
    entity->action    = ENTITY_CHANGE;
}


void entityDelete ( Entity *const entity ) {
    entity->action = ENTITY_DELETE;
}


unsigned entityStateChanged ( Entity *const entity ) {
    return (unsigned) entity->action == ENTITY_CHANGE;
}