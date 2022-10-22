#pragma once

#include "entity.h"

typedef struct ManagerNode {
	Entity *entity;
	struct ManagerNode *next;
}
ManagerNode;

typedef struct {
    ManagerNode *head;
    ManagerNode *tail;
    ManagerNode *prev;
    int count;
}
ManagerList;

typedef struct {
    char *name;
	
    ManagerList entities;
    ManagerList cache;
}
Manager;

Manager *manager           ( );
Entity  *managerAdd        ( Manager *const, Entity const* );
void     managerUpdate     ( Manager *const );
void     managerEnd        ( Manager *const );
int      managerCount      ( Manager *const );
int      managerCountCache ( Manager *const );

// void     managerEntityUpdate ( Manager *const, Entity *const );
// void     managerEntityDelete ( Manager *const, Entity *const );

// ahora no tiene sentido. habría que pasar ManagerNodo en lugar de Entity
// void managerEntityUpdate ( Manager *const manager, Entity *const entity ) {
//     update ( manager, entity );
// }
// void managerEntityDelete ( Manager *const manager, Entity *const entity ) {
//     cached ( manager, entity );
// }




// typedef struct {
//     char *name;
//     struct ManagerList {
//         struct ManagerNode {
//             Entity *entity;
//             struct ManagerNode *next;
//         }
//         *head,
//         *tail,
//         *prev;
//         int count;
//     }
//     entities,
//     cache;
// }
// Manager;