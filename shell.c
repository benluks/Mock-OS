#include "interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_BUFFER 32
char * read_line() {
    char c;
    char* line = malloc(READ_BUFFER * sizeof(int));
    int i = 0;

    while ((c = getchar()) != '\n') {
        line[i] = c;
        i++;
    }
    line[i+1] = '\n';

return line;
}

int main(void) {
    
    printf("\n");
    printf("Welcome to benShell\n");
    printf("version 0.0.1 released January 2021\n");
    printf("\n");
    
    while (!feof(stdin)) {    
        // don't print prompt if coming from external file
        if (isatty(0)) printf("$ ");
        int g;
        char * line = NULL;
        size_t linecap = 0;
        
        if ((g = getline(&line, &linecap, stdin)) == -1)
            break;

        else if (g > 1) {
            // only interpret non-empty input
            interpret(line);
            free(line);
        }
   
    }   

    return 0;
}