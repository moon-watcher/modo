#include <genesis.h>
#include "modo/system.h"
#include "components/Movement.h"
#include "components/Position.h"


inline static void _update ( ComponentMovement *const cm ) {
    fix32 v            = cm->vel;
    fix32 acceleration = cm->acceleration;
    fix32 deceleration = cm->deceleration;
    fix32 maximum      = cm->maximum;
    int   dir          = cm->dir;

         if ( dir > 0 ) v += acceleration;
    else if ( dir < 0 ) v -= acceleration;
    else if ( v > 0 && (v -= deceleration) < 0 ) v = 0;
    else if ( v < 0 && (v += deceleration) > 0 ) v = 0;

    cm->vel = clamp ( v, -maximum, +maximum );
}


systemFnDefine ( system_movement, {
    systemFnGet ( ComponentPosition2D, p );
    systemFnGet ( ComponentMovement2D, v );
    
    _update ( &v->x );
    _update ( &v->y );

    p->x.rounded = fix32ToInt ( p->x.pos += v->x.vel );
    p->y.rounded = fix32ToInt ( p->y.pos += v->y.vel );
});