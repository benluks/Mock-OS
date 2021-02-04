#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_BUFFER_SIZE 256
char* _read_line(int fd, char* buf) {
	int i = 0;
	char* dump = malloc(FILE_BUFFER_SIZE * sizeof(char));
	int chars_read;	
	do {
		chars_read = read(fd, buf, 1);
		dump[i] = *buf;
		i++;			
		} while (*buf != '\n' && chars_read != 0); 
	return dump;		
	}


char** read_file(char* filename) {
	char* buf = malloc(sizeof(int));
	char** lines = malloc(FILE_BUFFER_SIZE * sizeof(int));
	int fd = open(filename, O_RDONLY, 0);
	int i = 0;
	
	while (*buf != 's') {
		char * line = _read_line(fd, buf);
		lines[i] = line;
		i++;
	}
    return lines;
}