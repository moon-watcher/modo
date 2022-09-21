#pragma once


typedef struct {
    void (*update) ();
    unsigned max;
    unsigned params:3;
    char *name;
	void const **list;
    unsigned length;
}
System;


System *system       ( System const * );
void    systemUpdate ( System *const );
void    systemEnd    ( System *const );
void    systemInfo   ( System *const );
