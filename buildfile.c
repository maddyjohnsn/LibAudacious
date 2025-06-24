#define _GNU_SOURCE
#include <stdio.h> 
#include "setup.h"

int print_lib_path(char *path) { printf("%s\n", path); return 0; }
char* switchlib(char *path) {
    printf("%s please pleas eplase please please\n",path);
    return "./libsneaky.so";  
}
char* switchlib2(char *path) {
    printf("%s please i beg\n",path); 
       return "./liy.so";
   }

int testfunc1(lib_load_param* params){
    params->newPath = "./libsneaky"; 
    printf("current name %s new name %s\n", params->libName, params->newPath); 
    return 0; 
} 

int testfunc2(lib_load_param* params){
    char* oldname = params->newPath; 
    params->newPath = "./diffentnewone"; 
    printf("current name %s old name %s new name %s\n", params->libName,oldname,  params->newPath); 
    return 0;  
} 

int testfunc3(lib_load_param* params){
    params->newPath = "./evenmodiffentnewone"; 
    printf("current name %s new name %s\n", params->libName, params->newPath); 
    return 0;  
} 



CallFuncChar* buildinit(){
    char* yup = "merry christams"; 
    fprintf(stderr, "%s  %s\n", __FILE__, __func__);
	//on_library_load();
    /*tester stuff
    LibLoad funcs[3];
    funcs[0] = &switchlib;
    funcs[1] = &switchlib2;
    funcs[2] = 0; */ 
    //trying the real one 
    //know the size from the librarbu ? 
    LibLoadFuncs funcs[10]; 
    funcs[0] = testfunc1; 
    funcs[1] = testfunc2; 
    funcs[2] = testfunc3; 
    setloadlist(funcs); 


  // printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

void destroy(CallFuncChar* first){
     printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    while(!first){
        CallFuncChar* temp = first->next; 
        free(first); 
       first = temp;
    }
} 


