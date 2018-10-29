#include "console.h"

#include <stdio.h>
#include <string.h>

#include "lang.h"

static int do_inner_cmd(const char *line)
{
	return false;
}

/**
 * parse the input line.
 * @return isquit ?
 */
static int parse_input(const char *line)
{
	//printf("line:%s\n", line);
	if (line[0] == '!') {
		return do_inner_cmd(&line[1]);
	}

	lang();
	return false;
}

void console_loop()
{
    printf("input rthink's console:\n");
        
    char line[1024];
    bool is_quit = false;
    do {
    	memset(line, 0, sizeof(line));
    	scanf("%s", line);
        parse_input(line);
    } while(!is_quit);

}