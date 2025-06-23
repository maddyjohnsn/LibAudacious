#include <stdio.h>

__attribute__((constructor))

static void init(void) {
    printf("in fake lib\n");
}

