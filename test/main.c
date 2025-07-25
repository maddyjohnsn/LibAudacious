//#include "../src/practice.c"
#include "testlib.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(){
#ifdef MY_MACRO
    	printf("Hello World!\n");
	if(MY_MACRO==3){
    fprintf(stderr, "atoi of 123 = %d\n", atoi("123"));
		fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "rand %d\n", rand());
	}
    
if(MY_MACRO==3){	
}
#endif

#ifdef IFDEFTEST
    printf("Start of main%c\n", '!');
    /*fprintf(stderr, "atoi of 123 = %d\n", atoi("123")); 
    fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "abs of -12.3 = %f\n",fabs(-12.3));
    printf("arctan(1) =  %f\n", atan(( double)argc)); 
    printf("Hi\n"); */
    char* c[]= {"c1","c2"};
    //char c[2][10]= {"c1","c2"};
    //printf("%s\n",c[1] );
#ifdef kab
    kylieannebogar('a',"bb",c,1,2,3,4.44,5.55);
#endif
    FILE* fptr = fopen("random.txt", "r");
    if (fptr == NULL){
        fprintf(stderr, "null file pointer\n");
        return 0;
    }
#ifdef USEGETC
    int k = fgetc(fptr);
    printf( "The char:%c.\n",k);
#endif
    fclose(fptr); 
#endif //of ifdeftest
    fprintf(stdout, "End of Main\n"); 
    //fprintf(stderr, "line %d\n",__LINE__);
    return 0;
	}
}
