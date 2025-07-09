//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"
int passedTest = 0;
//int print_lib_path(char *path) { printf("%s\n", path); return 0; }
char* switchlib(char *path) {
     printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
   printfx("The original print statement was: %s\n", path);
    return "./libsneaky.so";
}

int tool_printf(char *format,...) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
    return 0;  
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


int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 

    og ogfunc = (og)get_wrappee("rand");
    printf("rand number from og %d\n",ogfunc());
    return 5;
   }

int testfunc1(lib_load_param* params){
    params->newPath = "./libsneaky";
  //  printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}


int  buildinit(){
    //blocklist test 
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
	LibLoadFuncs funcs[10] = {0};
    funcs[0] = testfunc1;
      //  funcs[1] = testfunc2;
        //funcs[2] = testfunc3;
    setloadlist(funcs);

}


	
	return 0;
}

/*tests from kylie
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
    LibLoadFuncs funcs[10] = {0};
    funcs[0] = &switchlib;
    setloadlist(funcs); 
#elif LIBTWO
    LibLoadFuncs funcs[10] = {0};
    funcs[0] = &switchlib;
    funcs[1] = &makelibnull; 
    setloadlist(funcs);
#elif LIBMAX
     LibLoadFuncs funcs[10] = {0};
     for (int i = 0; i<10; i+=2){
    funcs[i] = &switchlib;
    funcs[i+1] = &makelibnull;
     }
    setloadlist(funcs);
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
#endif //end of wrap tests
*/ 
