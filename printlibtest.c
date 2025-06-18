
#include "practice.c"
#include <stdio.h> 
int print_lib_path(char *path) { printf("%s\n", path); return 0; }
int main(){
    char* yup = "merry christams"; 
    int (*fptr)(char*); 
    fptr = &print_lib_path; 
    
    doit(fptr, yup);  


    return 0;
}

