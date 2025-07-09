//#include "../src/practice.c"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	
    	printf("Hello World!\n");
	if(MY_MACRO==3){
    fprintf(stderr, "atoi of 123 = %d\n", atoi("123"));
		fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "rand %d\n", rand());
	}
    
if(MY_MACRO==3){	
    FILE *fptr = fopen("../test/random.txt","r");
   // fprintf(stderr, "og func ? ret val %p\n", fptr);
    if (fptr == NULL){
        fprintf(stderr, "null file pointer\n");
        return 0;
    }
   // fprintf(stderr, "og func ? ret val\n");
    char buffer[100];
    //fprintf(stderr, "line %d\n",__LINE__);
    fgets(buffer, sizeof(buffer), fptr);
    fprintf(stderr,"line 1: %s", buffer);
    int k = fgetc(fptr);
    fprintf(stderr, "line 2:%c.\n",k);
    fclose(fptr); 
    //fprintf(stderr, "line %d\n",__LINE__);
    return 0;
	}
}
