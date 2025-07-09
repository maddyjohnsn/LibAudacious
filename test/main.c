#include "../src/practice.c"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
//#include "buildfile.c"

int main(){
	
    	printf("Hello World!\n");
	if(MY_MACRO==3){
    fprintf(stderr, "atoi of 123 = %d\n", atoi("123"));
		fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "rand %d\n", rand());
	}
    return 0;
}
