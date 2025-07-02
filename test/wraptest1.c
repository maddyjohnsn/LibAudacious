//tests if wrap can work with a 1 wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"

int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 

    og ogfunc = (og)get_wrappee("rand");
    printf("rand number from og %d\n",ogfunc());
    return 5;
   }

int  buildinit(){
    fprintf(stderr, "1 WRAP FUNC TEST\n");
    wrap("rand", (fptr_t)&tool_rand);
    return 0;
}

