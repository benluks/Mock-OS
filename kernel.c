#include "shell.h"
#include "ram.h"

#include <stdlib.h>
#include <stdio.h>


int main(void) {
    copy_script_to_ram("./testfile.txt");
    shellUI();
}