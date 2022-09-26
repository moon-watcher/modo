#pragma once

#include "entity.h"
#include "mlist.h"

typedef struct {
    char *name;
	mlist entities;
	mlist trash;
}
Manager;

Manager *manager       ( );
Entity  *managerAdd    ( Manager *const, Entity const* );
void     managerUpdate ( Manager *const );
void     managerEnd    ( Manager *const );

// void     managerEntityUpdate ( Manager *const, Entity *const );
// void     managerEntityDelete ( Manager *const, Entity *const );