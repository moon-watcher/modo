#include <genesis.h>
#include "system.h"


System *system ( System const *template ) {
    System *s = malloc ( sizeof ( System ) );
    
    s->update = template->update;
    s->max    = template->max * template->params;
    s->params = template->params;
    s->name   = template->name;
    s->list   = malloc ( sizeof ( void* ) * s->max );
    s->length = 0;

    return s;
}


void systemUpdate ( System *const s ) {
    if ( !s->length /* || !s->update || !s */ )
        return;

    if ( s->length > s->max )
        systemInfo ( s );

    s->update ( s );
    s->length = 0;
}


void systemEnd ( System *const s ) {
    free ( s->list );
    free ( s );
}


void systemInfo ( System *const s ) {
    VDP_resetScreen();

    drawText ( "=SYSTEM=", 0, 0 );
    drawText ( "NAME:   ", 0, 1 ); drawText ( s->name,   9, 1 );
    drawText ( "MAX:    ", 0, 2 ); drawUInt ( s->max,    9, 2, 4 );
    drawText ( "LENGTH: ", 0, 3 ); drawUInt ( s->length, 9, 3, 4 );
    
    waitMs(20000);
}


// void systemAdd ( System *const system, void *const array[] ) {
//     // int t = sizeof (array) / sizeof ( void*const );
// 	while ( *array ) {
//         system->list [ system->length++ ] = *array;
//         ++array;
//     }
// }