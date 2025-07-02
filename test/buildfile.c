#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"

//int print_lib_path(char *path) { printf("%s\n", path); return 0; }
char* switchli2b(char *path) {
     printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("scanf");
   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("og print%s\n", path);
    return "./libsneaky.so";
}
/*
int testfunc1(lib_load_param* params){
    params->newPath = "./libsneaky";
  //  printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

*/
int  buildinit(){
     
 printf("Variable from Makefile build test: %d\n", MY_MACRO);

	 
//printf("Variable from Makefile: %d\n", MY_MESSAGE);	


	//   char *toBlockList[] = {"./libfake.so", "two", "three"};
   // char* toBlock = "./libfake.so";

//        on_library_load();

 //   set_block_list(toBlockList, 3);

//    fprintf(stderr, "%s  %s\n", __FILE__, __func__);
 //       on_library_load();

    //wrap("scanf",switchli2b);

/*

   LibLoadFuncs funcs[10] = {0};
    funcs[0] = testfunc1;
      //  funcs[1] = testfunc2;
        //funcs[2] = testfunc3;
    setloadlist(funcs, 10);

*/

	
	return 0;
}

