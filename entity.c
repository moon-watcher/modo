#include <genesis.h>
#include "entity.h"

static const int Entity_s = sizeof ( Entity );


static void _nullf ( /* Entity *const e */ );
static void _init  ( Entity *const e );


Entity *entity ( Entity const* template ) {
    Entity *entity;
    
    entity = malloc ( Entity_s );
    memcpy ( entity, template, Entity_s );

    entity->components = malloc ( template->compsSize );
    memcpy ( entity->components, template->components, template->compsSize );

    _init ( entity );

    return entity;
}


void entityInit ( Entity *const entity, Entity const* template ) {
    memcpy ( entity, template, Entity_s );
    memcpy ( entity->components, template->components, template->compsSize );

    _init ( entity );
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




static void _nullf ( /* Entity *const e */ ) {
    //
}

static void _init ( Entity *const e ) {
    e->action = ENTITY_ACTION_CREATE;

    if ( !e->Awake  ) e->Awake  = _nullf;
    if ( !e->Update ) e->Update = _nullf;
    if ( !e->Delete ) e->Delete = _nullf;
}
