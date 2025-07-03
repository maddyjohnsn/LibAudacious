#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"

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
     
 printf("Variable from Makefile build test: %d\n", MY_MACRO);

 if(MY_MACRO == 2){
/* 
	 int passed;
//	 passed = wrap("printf",switchlib);
	if(passed == 0){

		printf("wrap test PASSED\n");
		printf("\n");
	}
	else{
		printf("wrap test FAILED\n");
                printf("\n");

		}
*/
	}


 if(MY_MACRO==3){
wrap("printf",(fptr_t)&tool_printf);   
    wrap("rand", (fptr_t)&tool_rand);
    wrap("atoi", (fptr_t)&tool_atoi);

}

if(MY_MACRO == 4){
	char *toBlockList[] = {"./libfake.so", "two", "three"};
    char* toBlock = "./libfake.so";

}

if(MY_MACRO == 5){
	LibLoadFuncs funcs[10] = {0};
    funcs[0] = testfunc1;
      //  funcs[1] = testfunc2;
        //funcs[2] = testfunc3;
    setloadlist(funcs, 10);

}


//        on_library_load();

 //   set_block_list(toBlockList, 3);

//    fprintf(stderr, "%s  %s\n", __FILE__, __func__);
 //       on_library_load();


/*

   LibLoadFuncs funcs[10] = {0};
    funcs[0] = testfunc1;
      //  funcs[1] = testfunc2;
        //funcs[2] = testfunc3;
    setloadlist(funcs, 10);

*/

	
	return 0;
}

