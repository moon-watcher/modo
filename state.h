#pragma once

typedef struct {
    void ( *enter  ) ( );
    void ( *update ) ( );
    void ( *exit   ) ( );
    char *name;
}
State;