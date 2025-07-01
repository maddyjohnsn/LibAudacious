//#include "../src/practice.c"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int main(){
    printf("hello world!\n", "double check");
    
    //printf("second print!"); 
    fprintf(stderr, "atoi of 123 = %d\n", atoi("123")); 
    
    //math.abs doesnt run trhough symbind ? 
    fprintf(stderr, "rand %d\n", rand());
    fprintf(stderr, "rand %d\n", rand());
    
    return 0;
}
