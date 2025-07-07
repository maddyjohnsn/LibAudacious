//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"
//function graveyard 

//i think this is another memory thing 
int tool_fclose(FILE *stream){

     printf("in %s, just observing\n",__func__);
    typedef int (*og)( FILE *stream);
    og ogfunc = (og)get_wrappee("fclose");
    int ret = ogfunc(stream);
    fprintf(stderr, "line %d\n",__LINE__);
    return ret;
}

//theres something funky happening with the memory here.. idk what tho
//#giving up for now
//Fatal error: glibc detected an invalid stdio handle
//^when using fgets()
//... maybe i could try fgets in here to see if its a cross file problem 
//okay it kinda works when i do that but tthen fails on close
//literally what 
//i wonder if its smth to do w the changing type of the func ptr/signature
FILE* tool_fopen(const char *pathname, const char* mode){
    printf("in %s, just observing\n",__func__);
    typedef FILE* (*og)(const char*, const char*);
    og ogfunc = (og)get_wrappee("fopen");
    //  this did not work (below) 
  //  FILE* fptr = malloc(sizeof(FILE*));

   FILE* fptr = ogfunc(pathname,mode);
   char buffer[100];
     fprintf(stderr, "line %d\n",__LINE__);
    fgets(buffer, sizeof(buffer), fptr);
fgets(buffer, sizeof(buffer), fptr);
    fprintf(stderr,"line 1: %s\n", buffer);
   fprintf(stderr, "eo fopen tool  ret val %p\n", fptr);
    return fptr;
}
// END FUNCTION GRAVEYARD 
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
int  buildinit(){
    fprintf(stderr, "test: %s  ", __FILE__);
    wrap("printf",(fptr_t)&tool_printf);   
    wrap("rand", (fptr_t)&tool_rand);
    wrap("atoi", (fptr_t)&tool_atoi);
    //wrap("fopen",(fptr_t)&tool_fopen); 
    wrap("fgets",(fptr_t)&tool_fgets); 
    wrap("fgetc", (fptr_t)&tool_fgetc);
//    wrap("fclose",(fptr_t)&tool_fclose);
   // wrap("fabs",(fptr_t)&tool_fabs); 
    return 0;
}

