//#include "../src/practice.c"
#include "testlib.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(int argc, char** argv){
    printf("Start of main%c\n", '!');
    /*fprintf(stderr, "atoi of 123 = %d\n", atoi("123")); 
    fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "abs of -12.3 = %f\n",fabs(-12.3));
    printf("arctan(1) =  %f\n", atan(( double)argc)); 
    printf("Hi\n"); */
    char* c[]= {"c1","c2"};
    //char c[2][10]= {"c1","c2"};
    //printf("%s\n",c[1] );
    //kylieannebogar('a',"bb",c,1,2,3,4.44,5.55);

    FILE *fptr = fopen("../test/random.txt","r");
    printf("heiewhfoih\n");
    fprintf(stderr, "og func ? ret val %p\n", fptr);
    if (fptr == NULL){
        fprintf(stderr, "null file pointer\n");
        return 0;
    }
     printf("heiewhfoih\n");
   /* fprintf(stderr, "file ptr %p\n",fptr);
    char buffer[100];
    //fprintf(stderr, "line %d\n",__LINE__);
    fgets(buffer, sizeof(buffer), fptr);
    
    fprintf(stderr,"line 1: %s", buffer);
    */
    int k = fgetc(fptr);
    fprintf(stderr, "line 3:%c.\n",k);
    fclose(fptr); 
    fprintf(stdout, "End of Main\n");
}
