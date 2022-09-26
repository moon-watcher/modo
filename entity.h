#pragma once

#include "state.h"


enum {
    ENTITY_ACTION_CREATE,
    ENTITY_ACTION_UPDATE,
    ENTITY_ACTION_CHANGE,
    ENTITY_ACTION_DELETE,
};


typedef struct {
    char  *name;
    State *state;     // debería tenerlo el manager? igual 
    State *prevState; // debería tenerlo el manager? igual sí
    void  *components;
    unsigned compsSize:10; // 1024 bytes
    unsigned action:3; // debería tenerlo el manager?

    void ( *Awake  ) ( );
    void ( *Update ) ( );
    void ( *Delete ) ( );
    
    void *exec;
    // void *next;  // debería tenerlo el manager!
    // void *COMPS[];
}
Entity;

Entity   *entity             ( Entity const* );
void      entityState        ( Entity *const, State const* );
unsigned  entityStateChanged ( Entity *const );
void      entityDelete       ( Entity *const );