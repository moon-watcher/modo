#include <genesis.h>
#include "entity.h"


static void nullf ( Entity *e ) { }


Entity *entity ( Entity const* template ) {
    Entity *entity = malloc ( sizeof ( Entity ) );
    memcpy ( entity, template, sizeof ( Entity ) );

    entity->components = malloc ( template->compsSize );
    memcpy ( entity->components, template->components, template->compsSize );

    entity->action = ENTITY_ACTION_CREATE;

    if ( !entity->Awake  ) entity->Awake  = nullf;
    if ( !entity->Update ) entity->Update = nullf;
    if ( !entity->Delete ) entity->Delete = nullf;

    return entity;
}


void entityState ( Entity *const entity, State const* newState ) {
    if ( newState == entity->state )
        return;

    entity->prevState = entity->state;
    entity->state     = (State*) newState;
    entity->action    = ENTITY_ACTION_CHANGE;

    // use when copy state just like the entity
    // if ( !entity->state->enter  ) entity->state->enter  = nullf;
    // if ( !entity->state->update ) entity->state->update = nullf;
    // if ( !entity->state->exit   ) entity->state->exit   = nullf;
}


void entityDelete ( Entity *const entity ) {
    entity->action = ENTITY_ACTION_DELETE;
}


unsigned entityStateChanged ( Entity *const entity ) {
    return (int) entity->action == ENTITY_ACTION_CHANGE;
}