//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"


//lowkey might just leave these out? cause a bunch use them?? or should i not...

int tool_printf(char *format,...) {
    fprintf(stderr,"Inside of tool_printf\n");
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


char* tool_fgets(char *s, int size, FILE *stream){
    printf("in %s, just observing\n",__func__);
    typedef char* (*og)(char *s, int size, FILE *stream); 
    og ogfunc = (og)get_wrappee("fgets"); 
    char* ret = ogfunc(s,size,stream);
    return ret; 
}

int tool_fgetc(FILE *stream){

     printf("in %s, just observing\n",__func__);
    typedef int (*og)( FILE *stream);
    og ogfunc = (og)get_wrappee("fgetc");
    int ret = ogfunc(stream);
    return ret;
}

double tool_fabs(double k){
    printf("always negative\n");
    typedef double (*og)(double);
    og ogfunc = (og)get_wrappee("fabs");
    k = ogfunc(k);
    return -1 * k;
}
//if theres one wrap function 
int  buildinit(){
    
   #ifdef WRAPONE
        wrap("rand", (fptr_t)&tool_rand);
    //if theres 2
    #elif WRAPTWO
        wrap("printf",(fptr_t)&tool_printf);
        wrap("rand", (fptr_t)&tool_rand);
    //if there the max(four right now) 
    #elif WRAPMAX
        wrap("atoi", (fptr_t)&tool_atoi);
        wrap("fgets",(fptr_t)&tool_fgets); 
        wrap("fgetc", (fptr_t)&tool_fgetc);
        wrap("rand", (fptr_t)&tool_rand);

    //if theres more than the max
    #elif WRAPOVER
        wrap("rand", (fptr_t)&tool_rand);
        wrap("printf",(fptr_t)&tool_printf);   
        wrap("atoi", (fptr_t)&tool_atoi);
        wrap("fgets",(fptr_t)&tool_fgets); 
        wrap("fgetc", (fptr_t)&tool_fgetc);
    #endif //end of wrap tests
    return 0;
}
