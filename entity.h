#pragma once

#include "state.h"


enum {
    ENTITY_CREATE,
    ENTITY_UPDATE,
    ENTITY_CHANGE,
    ENTITY_DELETE,
};


typedef struct {
    char     *name;
    State    *state;         // debería tenerlo el manager? igual 
    State    *prevState;     // debería tenerlo el manager? igual sí
    void     *components;
    unsigned  compsSize:10;  // 1024 bytes
    unsigned  action:3;
    void     *exec;
}
Entity;

Entity   *entity             ( Entity const* );
void      entityInit         ( Entity *const, Entity const* );
void      entityState        ( Entity *const, State const* );
unsigned  entityStateChanged ( Entity *const );
void      entityDelete       ( Entity *const );