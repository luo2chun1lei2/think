// misc functions.
#pragma once

#include <stdio.h>

#define LOGE(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
