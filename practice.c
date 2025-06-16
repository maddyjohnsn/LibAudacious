

#include <stdio.h> 

void doit(int (*userFunc) (char*), char * path){
    printf("hello!\n");
    userFunc(path);
}
