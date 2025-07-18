//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include "../include/committee.h"
/*
extern fclose_t getfclosewrapee(char* wrappee_name);
extern fileopen_t getfopenwrapee(char* wrappee_name);
extern fptr_t get_wrappee(char *wrappee_name);
*/
FILE* tool_fopen(const char *pathname, const char *mode){
  printf("pathanme %s\n",pathname);
   printf("in %s, just observing\n",__func__);
    fileopen_t ogfunc = (fileopen_t)getfopenwrapee("fopen"); 
    //fileopen_t ogfunc = (fileopen_t)dlsym(RTLD_NEXT, "fopen");
    printf("hello %p\n", ogfunc);
     if(!ogfunc){
        printf("fptr is null ?? \n");
    }
    // FILE* ret = ogfunc(pathname,mode);
    //fprintf(stderr,"file pointer in %s = %p\n",__func__,ret);
    return fopen(pathname, mode); 
}
int tool_fclose(FILE* stream){
    printf("in %s, just observing\n",__func__);
    fclose_t ogfunc = getfclosewrapee("fclose");
    fprintf(stderr,"file pointer in %s = %p\n",__func__,stream);
    if(!ogfunc||!stream){
        printf("fptr is null ?? \n"); 
    }
    fprintf(stderr,"file pointer in %s = %p\n",__func__,stream);
    int k = ogfunc(stream);
    printf("retval fclose: %d\n",k);
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
    wrap("fputs",(fptr_t)&tool_fputs); 
#ifdef TOOLFOPEN

    wrapfopen("fopen",&tool_fopen);
#endif
#ifdef TOOLFCLOSE
    wrapfclose("fclose",&tool_fclose);
#endif
#ifdef TOOLFGETC
    wrap("fgetc",(fptr_t) &tool_fgetc);
#endif

#ifdef WRAPONE
    wrap("rand", (fptr_t)&tool_rand);
#endif //end of wrap tests
    return 0;
}
