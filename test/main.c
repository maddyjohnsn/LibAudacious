//#include "../src/practice.c"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
    	printf("hello world %s!\n", "tests passed");

	fprintf(stderr, "atoi of 123 = %d\n", atoi("123"));
	if(MY_MACRO==3){
    fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "rand %d\n", rand());
	}
    return 0;
}
