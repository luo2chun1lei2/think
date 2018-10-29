#include "console.h"

#include <stdio.h>
#include <string.h>

#include "lang.h"

static void show_help(void)
{
	printf("help/h: show help information.\n");
	printf("quit/q: quit from console.\n");
}

static int do_inner_cmd(const char *line)
{
	if (strcmp("quit", line) == 0 || strcmp("q", line) == 0 ) {
		return true;
	} else if(strcmp("help", line) == 0 || strcmp("h", line) == 0 ) {
		show_help();
	} else {
		printf("Unkown commnd: \"%s\"\n", line);
	}
	
	return false;
}

/**
 * parse the input line.
 * @return isquit ?
 */
static int parse_input(const char *line)
{
	//printf("line:%s\n", line);
	// 所有以 “!" 开始的单词都是内部的命令。
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
        is_quit = parse_input(line);
    } while(!is_quit);

}