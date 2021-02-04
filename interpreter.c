#include "interpreter.h"
#include "shellmemory.h"

// #include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SPLIT_BUFFER 64
#define DELIM " \n\t\r\a"
char** parse_input(char * line) {

    int i = 0;

    char* token = strtok(line, DELIM);
    char** split = malloc(SPLIT_BUFFER * sizeof(int));
    
    while (token) {
        split[i] = token;
        i++;
        token = strtok(NULL, DELIM);
        }
    free(token);
    return split;
    }

void help(void) {
    printf("\n\n");

    printf("COMMAND:            DESCRIPTION:\n");
    printf("-------             -----------\n");
    printf("help                Displays all the commands\n");
    printf("quit                Exits / terminates the shell with a goodbye message\n");
    printf("set VAR STRING      Assigns a value to shell memory\n");
    printf("print VAR           Displays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT      Executes the file SCRIPT.TXT\n");
    printf("\n");
}

int set(const char* var, const char* string) {
    int i=0;
    
    while (shellmemory[i].var != NULL) {
        if (strcmp(shellmemory[i].var, var) == 0) {
            free(shellmemory[i].value);
            shellmemory[i].value = strdup(string);
            return 0;
        }
        i++;
    }
    shellmemory[i].var = strdup(var);
    shellmemory[i].value = strdup(string);
    return 0;
}

void print(char* var) {
    
    int i=0;
    
    while ((shellmemory[i].value) != NULL) {
        if (strcmp(shellmemory[i].var, var) == 0){
            printf("%s\n", shellmemory[i].value);
            return;
        }
        i++;
    }
    fprintf(stderr, "Error: No such variable '%s'\n", var);
}

#define FILE_IN_BUFFER 1024
void run(char* filename) {
    
    FILE* fp = fopen(filename, "r");
    while (!feof(fp)) {
        int g;
        char *line = NULL;
        size_t linecap = 0;
        g = getline(&line, &linecap, fp);
        if (g > 1) {
            interpret(line);
            free(line);
        }
    }
    fclose(fp);
   
    
}

 

int interpret(char * line) {
    char** words = parse_input(line);
    
    if (strcmp(words[0], "quit") == 0) {
        printf("It was fun while it lasted!\n");
        exit(EXIT_SUCCESS);
    } 
    else if (strcmp(words[0], "help") == 0) {
        help();
    } 
    else if (strcmp(words[0], "set") == 0) 
    // reconstruct broken string 
    {
        
        char * temp = malloc(64 * sizeof(char));
        strcpy(temp, words[2]);
        char space[2] = {' '};

        int i = 3;

        while (words[i] != NULL) {
            strcat(temp, space);
            strcat(temp, words[i]);
            i++;
        }
        
        set(words[1], temp);
        free(temp);
     
    } 
    
    else if (strcmp(words[0], "print") == 0) {
        print(words[1]);
    } 
    else if (strcmp(words[0], "run") == 0) {
        run(words[1]);
    } else if (strcmp(words[0], "exec") == 0) {
        return 0;
    } else {
        printf("Command '%s' does not exist.\n", words[0]);
        return 1;
    }
    free(words);
    return 0;
}
