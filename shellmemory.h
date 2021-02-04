#include "interpreter.h"

struct MEM {
    char* var;
    char* value;
};

typedef struct MEM MEM_t;

MEM_t shellmemory[32];