//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include "../include/committee.h"
FILE* tool_fopen(const char *pathname, const char *mode){
  printf("pathanme %s\n",pathname);
    
   printf("in %s, just observing\n",__func__);
  //  typedef FILE* (*og)(const char*, const char*);
    fileopen_t ogfunc = (fileopen_t)getfopenwrapee("fopen"); 
       // ogfunc = get_wrappee("fopen");
   // printf("Have fptr\n"); 
     if(!ogfunc){
        printf("fptr is null ?? \n");
    }
     FILE* ret = ogfunc(pathname,mode);
   // printf("Have file ptr\n");
    // char buffer[100];
   //fprintf(stderr, "line %d\n",__LINE__);
 // fgets(buffer, sizeof(buffer), ret);
    fprintf(stderr,"%p\n",ret);
    //fprintf(stderr,"line 1: %s%p", buffer,ret);
    
    return ret; 
}
int tool_fclose(FILE* stream){
    printf("in %s, just observing\n",__func__);
    //typedef int (*og)(FILE*);
    //fclose_t ogfunc = NULL:
    fclose_t ogfunc = getfclosewrapee("fclose");
    //fclose_t  ogfunc = get_wrappee("fclose");
    //did that really just fiz that are u kidding
    //printf("have og function ptr\n"); 
    if(!ogfunc||!stream){
        printf("fptr is null ?? \n"); 
    
    }
    int k = ogfunc(stream);
   // fprintf(stderr,"%p\n",stream);
    printf("retval fclose: %d\n",k);
   return k;  
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
