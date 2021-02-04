#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MEM {
    char* var;
    char* value;
};

typedef struct MEM MEM_t;

MEM_t shellmemory[64];

