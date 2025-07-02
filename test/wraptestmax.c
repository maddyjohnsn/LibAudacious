//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"

int tool_printf(char *format,...) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
    return 0;  
}


int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 

    og ogfunc = (og)get_wrappee("rand");
    printf("rand number from og %d\n",ogfunc());
    return 5;
   }

int tool_atoi(char* r){
    printf("super fun atoi that i will amke negative\n");
    typedef int (*og)(char*);
    og ogfunc = (og)get_wrappee("atoi");
    int k = ogfunc(r);
    printf("number from std atoi %d", ogfunc(r)); 
     if(k > 0){
         return -1 * k;
     }
     return k;
}

FILE tool_fopen(const char *pathname, const char *mode){
    printf("in %s, just observing\n",__func__);    
    typedef FILE (*og)(const char, const char); 
    og ogfunc = (og)get_wrappee("fopen");
    return ogfunc(pathname,mode); 
}




int  buildinit(){
    fprintf(stderr, "test: %s  ", __FILE__);
    wrap("printf",(fptr_t)&tool_printf);   
    wrap("rand", (fptr_t)&tool_rand);
    wrap("atoi", (fptr_t)&tool_atoi);
    //wrap("fopen",(fptr_t)&tool_fopen); 
    return 0;
}

