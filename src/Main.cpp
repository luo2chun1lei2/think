#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <Misc.hpp>

static const char *_sopts = "his:";
extern char *optarg; 
static const struct option _lopts[] = {
	{"help", no_argument, 0, 'h'},
	{"script", required_argument, 0, 's'},
	{"interactive", no_argument, 0, 'i'},
	{0, 0, 0, 0}
};

static const char *usage =
    "Usage: %s [options]\n"
    "options:\n"
    "  -h, --help            prints this message and exit.\n"
    "  -s, --script <path>   execute script at start.\n"
    "  -i, --interactive     run into interactive mode.\n"
    "\n";

static void print_usage_and_exit(const char *prog, int code)
{
	LOGE(usage, prog);
	exit(code);
}

int main(int argc, char* argv[])
{
	LOGI("start think...\n");

	int c;
	int oidx = 0;
	
	bool enter_interactive = false;
	const char *script_path = NULL;

	while (1) {
		c = getopt_long(argc, argv, _sopts, _lopts, &oidx);
		if (c == -1)
			break;	/* done */

		switch (c) {
		case 'h':
			print_usage_and_exit(argv[0], EXIT_SUCCESS);
			break;
		case 'i':
			enter_interactive = true;
			break;
		case 's':
			script_path = optarg;
			break;
		default:
			print_usage_and_exit(argv[0], EXIT_FAILURE);
			break;
		}
	}

	//printf("%d %s.\n", enter_interactive, script_path);

	return 0;
}