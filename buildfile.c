#define _GNU_SOURCE
#include "practice.c"
#include <stdio.h> 
#include "setup.h"
int print_lib_path(char *path) { printf("%s\n", path); return 0; }
char* switchlib(char *path) {
    return "./libsneaky.so";  
}
char* switchlib2(char *path) {
       return "./liy.so";
   }
int main(){
    char* yup = "merry christams"; 
    /*int (*fptr)(char*); 
    fptr = &print_lib_path; 
    char* (*pt2)(char*);
    pt2 = &switchlib; 
    //callOneParam(fptr, yup);  
    //callOneParamChar(pt2, yup); 
*/
    CallFuncChar switc; 
    switc.flag = 3;
    switc.fptr =&switchlib; 
    switc.next = NULL; 
    firstaddlib(&switc); 
    


    CallFuncChar second; 
    second.flag = 1;
    second.fptr = &switchlib2; 
    switc.next = &second; 
    second.next = 0; 
    tester("hello");
        



    return 0;
}

