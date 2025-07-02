//tests if code works with 0 code in build. 
#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"

int  buildinit(){
    fprintf(stderr, "NO CODE TEST\n");
    return 0;
}

