#define _GNU_SOURCE
#include <stdio.h> 
#include "../include/committee.h"
#include <string.h>
int print_lib_path(char *path) { printf("%s\n", path); return 0; }

char* switchlib(char *path) {
     printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("scanf");
   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("og print%s\n", path);
}
char* tool_printf(char *format,...) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
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

//FILE tool_fopen(const char *pathname, const char *mode){
    

//blank wrap example 
/*int tool_fucwrapname(int param){
    //type def cause its easier for my brain 
    typedef int (*og)(char*);
    //get the orginal func ptr 
    //your code of somekind can go anywhere tbh 
    og ogfunc = (og)get_wrappee("wrappeefuncname");
    int k = ogfunc(param); 
    return 0; 
} */


int testfunc1(lib_load_param* params){
    if(strcmp(params->libName, "./libfake.so")==0){ 
    params->newPath = "./libsneaky.so"; }
 //   printf("current name %s new name %s\n", params->libName, params->newPath); 
    return 0; 
} 



int testfunc2(lib_load_param* params){
    char* oldname = params->newPath; 
    params->newPath = "./diffentnewone"; 
   // printf("current name %s old name %s new name %s\n", params->libName,oldname,  params->newPath); 
    return 0;  
} 
int  buildinit(){
    fprintf(stderr, "%s  %s\n", __FILE__, __func__);
    
	//funcs[1] = testfunc2;
	//funcs[2] = testfunc3;
   // fprintf(stderr, "func: %s line: %dbefore setload\n", __func__, __LINE__);  
        setloadlist(&testfunc1); 
    //    setloadlist(&testfunc2); 
   // fprintf(stderr, "func: %s line: %dafter\n", __func__, __LINE__);  
  // printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

