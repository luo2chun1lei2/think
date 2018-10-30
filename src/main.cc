#include <cstdio>
#include <stdlib.h>
#include <getopt.h>

#include "console.h"
#include "test.h"

static const struct option long_options[] = {
		{"console", 0, NULL, 'c'},
		{"test", 0, NULL, 't'}
};

void usage(void)
{
	printf("think [--test/-t] [--console/-c]\n");
	printf("  --test, -t : run test cases.\n");
	printf("  --console, -c : go into console mode.\n");
}

int main(int argc, char *argv[])
{
	// 分析参数，调用具体的功能。
	int opt=0;
	opterr=0;//关闭getopt错误信息
	while((opt = getopt_long(argc, argv, "tc", long_options, NULL))!=-1) {
		switch(opt) {
		case 't':
			//printf("The number is %s\n", optarg);
			// 进入测试模式。
			test();
			break;
		case 'c':
			//printf("The clients is %s\n", optarg);
			// 进入控制台模式。
			console_loop();
			break;
		default:
			usage();
			exit(1);
			break;
		}
	}
	return 0;
}
