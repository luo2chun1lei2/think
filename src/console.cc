#include "console.h"

#include <stdio.h>

#include "lang.h"

void console_loop()
{
    printf("input rthink's console:\n");
        
    char line[1024];
    bool is_quit = true;
    do {
        lang();
    } while(!is_quit);
    
    //return 0;
}