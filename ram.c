#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RAM_BUFFER 1000
#define RAM_LINE_BUFFER 64

char *ram[RAM_BUFFER];
char* buffer;

FILE* script;

int limit = RAM_LINE_BUFFER;
int next_available_ram = 0;
int current_file_index = 0;
int start_of_file[1000];

int copy_script_to_ram(char* filename) {
    
    script = fopen(filename, "r");
    buffer = malloc(RAM_LINE_BUFFER * sizeof(char));
   
    // check if script exists
    if (script == NULL) {
        fprintf(stderr, "ERROR: no such file or directory '%s\n'\n", filename);
        return 1;
    }
    
    // save starting index of file in `start_of_file` at index corresponding
    // to current file index (eg. if this is first file, save at `start_of_file[0]`,
    // if 10th, then `start_of_file[9]`, etc...). Ending indices will be inferred from 
    // start of subsequent files.
    start_of_file[current_file_index] = next_available_ram;

    while (fgets(buffer, limit, script) != NULL) {
         
        ram[next_available_ram] = strdup(buffer);
        next_available_ram++;
    }
    
    // no leakies
    free(buffer);

    current_file_index++;
    return 0;
}

