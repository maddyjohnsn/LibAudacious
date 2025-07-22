//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"
FILE* tool_fopen(const char *pathname, const char *mode){
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


int tool_fgetc(FILE *stream){
    printf("in %s, just observing\n",__func__);
    typedef int (*og)( FILE *stream);
    og ogfunc = (og)get_wrappee("fgetc");
    int ret = ogfunc(stream);
    return ret;
}
double tool_atan(double k){
    printf("observing ! %s\n", __func__); 
    typedef double (*og)(double);
    og ogfunc = (og)get_wrappee("atan");
    return ogfunc(k); 
}
int switchlib(lib_load_param* params){
    if(strcmp(params->libName, "./libfake.so")==0){
       params->newPath = "./libsneaky.so"; 
   }
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}
//for this one to actually work it qould need to change to params->libName = NULL
int makelibnull(lib_load_param* params){
    params->newPath = NULL;
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

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
    printf("in %s, just observing\n",__func__);
    typedef int (*og)(char*);
    og ogfunc = (og)get_wrappee("atoi");
    int k = ogfunc(r);
     return k;
}


char* tool_fgets(char *s, int size, FILE *stream){
    printf("in %s, just observing\n",__func__);
    typedef char* (*og)(char *s, int size, FILE *stream); 
    og ogfunc = (og)get_wrappee("fgets"); 
    char* ret = ogfunc(s,size,stream);
    return ret; 
}


double tool_fabs(double k){
    printf("always negative\n");
    typedef double (*og)(double);
    og ogfunc = (og)get_wrappee("fabs");
    k = ogfunc(k);
    return -1 * k;
}
int tool_kab(char a, char* b, char** c, int d, short e, long f, float g, double h){
    printf("in %s\n",__func__);
     printf("a=a:%c\nb=bb:%s\nc=c1:%s c2:%s\nd=1:%d\ne=2:%d\nf=3:%d\ng=4.44:%f\nh=5.55:%f\n",a,b,c[0],c[1],d,e,f,g,h);
     typedef int (*og)(char , char* , char** , int, short , long , float , double );
    og func = (og)get_wrappee("kylieannebogar");
    func(a,b,c,d,e,f,g,h);
    return 1;
}


int  buildinit(){
    wrap("kylieannebogar",(fptr_t)&tool_kab);
#ifdef TOOLFOPEN
    wrap("fopen", (fptr_t)&tool_fopen);
#endif
#ifdef TOOLFCLOSE
    wrap("fclose",(fptr_t)&tool_fclose);
#endif
#ifdef TOOLFGETC
    wrap("fgetc",(fptr_t) &tool_fgetc);
#endif
#ifdef BLOCKONE
    char *toBlockList[] = {"./libfake.so"};
    set_block_list(toBlockList, 1); 
#elif BLOCKTWO
    char *toBlockList[] = {"./libfake.so","one"};
    set_block_list(toBlockList, 2);
#elif BLOCKMAX
    printf("test not created. BLOCKMAX\n");
#elif BLOCKOVER
    printf("test not created. BLOCKOVER\n");
#endif

    //On library load tests this strcuture should be changed 
#ifdef LIBONE
    setloadlist(&switchlib);
#elif LIBTWO
    setloadlist(&switchlib);
    setloadlist(&makelibnull);
#elif LIBMAX
     for (int i = 0; i<10; i+=2){
        setloadlist(&switchlib);
        setloadlist(&makelibnull);
     }
#endif
    //WRAP TESTTTSSS
#ifdef WRAPONE
    wrap("rand", (fptr_t)&tool_rand);
    //if theres 2
#elif WRAPTWO
    wrap("printf",(fptr_t)&tool_printf);
    //    wrap("rand", (fptr_t)&tool_rand);
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
#elif WRAPNULLPTR
     wrap("rand", (fptr_t)0);
#elif WRAPBADNAME
     wrap("badname",(fptr_t)&tool_rand); 
#endif //end of wrap tests
    return 0;
}
