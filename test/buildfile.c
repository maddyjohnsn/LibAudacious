//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include "../include/committee.h"

FILE* tool_fopen(const char *pathname, const char *mode){
  printf("pathanme %s\n",pathname);
   printf("in %s, just observing\n",__func__);
    typedef FILE* (*og)(const char*, const char*); 
    og ogfunc = (og)get_wrappee("fopen"); 
    printf("hello %p\n", ogfunc);
     if(!ogfunc){
        printf("fptr is null ?? \n");
    }
    FILE* ret = ogfunc(pathname,mode);
    return ret; 
}
int tool_fclose(FILE* stream){
    printf("in %s, just observing\n",__func__);
    typedef int (*og)(FILE*);
    og ogfunc = (og)get_wrappee("fclose");
    if(!ogfunc||!stream){
        printf("fptr is null ?? \n"); 
    }
    int k = ogfunc(stream);
   return k;  
}


int tool_fputs(const char *restrict s, FILE *restrict stream){
    printf("In %s\n",__func__);
    typedef int (*og)(const char *restrict s, FILE *restrict stream);
    og ogfunc = (og)get_wrappee("fputs");
    return ogfunc(s,stream); 

}
int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 
    og ogfunc = (og)get_wrappee("rand");
    return 5;
   }
int tool_fgetc(FILE *stream){
    printf("in %s, just observing\n",__func__);
    typedef int (*og)( FILE *stream);
    og ogfunc = (og)get_wrappee("fgetc");
    int ret = ogfunc(stream);
    return ret;
}


int  buildinit(){
    printf("tool_rand ptrr %p\n", &tool_rand);
    wrap("rand",(fptr_t)&tool_rand); 
#ifdef TOOLFOPEN
    wrap("fopen", (fptr_t)&tool_fopen);
#endif
#ifdef TOOLFCLOSE
    wrap("fclose",(fptr_t)&tool_fclose);
#endif
#ifdef TOOLFGETC
    wrap("fgetc",(fptr_t) &tool_fgetc);
#endif

#ifdef WRAPONE
    wrap("rand", (fptr_t)&tool_rand);
#endif //end of wrap tests
    return 0;
}
