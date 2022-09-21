#include <genesis.h>
#include "modo.h"
#include "manager.h"

void modo ( Entity const* entity_tpl ) {
    Manager *const m = manager ( );
    managerAdd ( m, entity_tpl );

    while ( 1 )
        managerUpdate ( m );
}