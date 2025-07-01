#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"

int print_lib_path(char *path) { printf("%s\n", path); return 0; }

char* tool_printf(char *path) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",path);
    return "./libsneaky.so";  
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
int testfunc1(lib_load_param* params){
    params->newPath = "./libsneaky"; 
  //  printf("current name %s new name %s\n", params->libName, params->newPath); 
    return 0; 
} 



int testfunc2(lib_load_param* params){
    char* oldname = params->newPath; 
    params->newPath = "./diffentnewone"; 
    printf("current name %s old name %s new name %s\n", params->libName,oldname,  params->newPath); 
    return 0;  
} 
int  buildinit(){
	//for some reason yup is a necessary variable
    //i wonder if its a condional jump memory thing....
	char* yup = "merry christams"; 
	char *toBlockList[] = {"./libfake.so", "two", "three"};
    char* toBlock = "./libfake.so";
    set_block_list(toBlockList, 3);

    fprintf(stderr, "%s  %s\n", __FILE__, __func__);
	//on_library_load();
    
    wrap("printf",(fptr_t)&tool_printf);   
    wrap("rand", (fptr_t)&tool_rand);
    wrap("atoi", (fptr_t)&tool_atoi);
    
  // fprintf(stderr, "func: %s line: %d\n", __func__, __LINE__);   
    LibLoadFuncs funcs[10] = {0}; 
    //fprintf(stderr, "func: %s line: %d post libliad fun\n", __func__, __LINE__);  
    funcs[0] = testfunc1;
    
	//funcs[1] = testfunc2;
	//funcs[2] = testfunc3;
   // fprintf(stderr, "func: %s line: %dbefore setload\n", __func__, __LINE__);  
    setloadlist(funcs ); 
   // fprintf(stderr, "func: %s line: %dafter\n", __func__, __LINE__);  
  // printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

