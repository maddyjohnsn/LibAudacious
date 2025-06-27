#include "../include/committee.h"
#include "../src/funcwrapper.c"
#include <stdio.h>
int tool_printf(const char* format, ...){
    printf("Inside of tool_printf\n"); 
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
   //fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("Original printf function\n"); 
} 

int main(){
    
    wrap("printf",&tool_printf);  
    printf("hello world!\n");
    tool_printf("test %s", "beep");  
    return 0;
}
