#pragma once

#include "entity.h"


typedef struct {
	Entity *entities;
	Entity *prevEntity;
    char *name;
}
Manager;


Manager *manager       ( );
Entity  *managerAdd    ( Manager *const, Entity const* );
void     managerUpdate ( Manager *const );
void     managerEnd    ( Manager *const );


#define managerForeach( M, E ) \
    M->prevEntity = NULL; \
    for ( Entity *E = M->entities; E; E = E->next )


void managerEntityUpdate ( Manager  *const, Entity  *const );
void managerEntityDelete ( Manager  *const, Entity  *const );