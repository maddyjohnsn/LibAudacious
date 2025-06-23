#define _GNU_SOURCE
#include <stdio.h> 
#include "setup.h"

int print_lib_path(char *path) { printf("%s\n", path); return 0; }
char* switchlib(char *path) {
    return "./libsneaky.so";  
}
char* switchlib2(char *path) {
       return "./liy.so";
   }





int testerFunc(struct library_load_params *params){
	printf("testing user func\n");
	return 0;
}

CallFuncChar* buildinit(){
 	char *toBlockList[] = {"one", "two", "three"};
     	char* yup = "merry christams"; 
	char* toBlock = "./libfake.so";
    set_block_list(toBlock, toBlockList, 3);

	on_library_load(&testerFunc);

   //printf("%s %d %s\n", __FILE__, __LINE__, __func__); 
    CallFuncChar *first = malloc(sizeof(CallFuncChar)); 
    first->flag = 2;
    first->fptr =&switchlib2; 
    CallFuncChar *second = malloc(sizeof(CallFuncChar)); 
   second->flag = 3;
   second->fptr =&switchlib; 
   second->next = NULL; 
   first->next = second; 
  // printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return first;
}

void destroy(CallFuncChar* first){
     printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    while(!first){
        CallFuncChar* temp = first->next; 
        free(first); 
       first = temp;
    }
} 
