//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"
int passedTest = 0;

int tool_printf(char *format,...) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
    return 0;  
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

int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 

    og ogfunc = (og)get_wrappee("rand");
    printf("rand number from og %d\n",ogfunc());
    return 5;
   }
int switchlib(lib_load_param* params){
    if(strcmp(params->libName, "./libfake.so")==0){
    params->newPath = "./libsneaky.so"; }
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

//for this one to actually work it qould need to change to params->libName = NULL
int makelibnull(lib_load_param* params){
    params->newPath = NULL;
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

int  buildinit(){
#ifndef MY_MACRO
   int MY_MACRO = 0;
#endif
	if(MY_MACRO == 0){
		printf("Testing blocklist with preloaded library: \n");
		char *toBlockList[] = {"./libfake.so", "two", "three"};
		passedTest = set_block_list(toBlockList, 3);
		if(passedTest == 0){
                        printf("Test Passed\n");
                }
                else{
                        printf("Test Failed\n");
                }
	}

	if(MY_MACRO == 1){
		printf("Testing blocklist with too many libraries: \n");
		char *toBlockList[] = {"./libfake.so", "two", "three"};
		passedTest = set_block_list(toBlockList, 100);
		if(passedTest == 1){
			printf("Test Passed\n");
		}
		else{
			printf("Test Failed\n");
		}

	}
    if(MY_MACRO == 2){
        printf("Testing blocklist with one library: \n");
        char *toBlockList[] = {"./lib.so.6"};
        passedTest = set_block_list(toBlockList, 1);
		if(passedTest == 0){
			printf("Test Passed\n");
		}
		else{
            printf("Test Failed\n");
        }
    }
    if(MY_MACRO==3){
        wrap("printf",(fptr_t)&tool_printf);   
        wrap("rand", (fptr_t)&tool_rand);
        wrap("atoi", (fptr_t)&tool_atoi);
    }

    if(MY_MACRO == 4){

    }

    if(MY_MACRO == 5){
        setloadlist(&switchlib);
        setloadlist(&makelibnull);
    }

	return 0;
}


/*
int  buildinit(){
        //Blocklist tests 
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
    setloadlist( &switchlib);
    setloadlist((&makelibnull);
#elif LIBMAX
     for (int i = 0; i<10; i+=2){
        setloadlist( &switchlib);
        setloadlisti(&makelibnull);
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
*/
