
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <link.h>
#include <elf.h>
#include <stdio.h> 
#include "buildfile.c"
#include <string.h>
#include "../include/committee.h"

__attribute__((constructor))
 void init(void) {
	 
//dlopen("functionOverride.so", RTLD_NOW);
	 /*
	 void *handle;

        handle = dlopen("functionOverride.so", RTLD_LAZY);
        if (!handle){
                //if failed to load the library
                fprintf(stderr, "Error: %s\n", dlerror());
        }

      */
	 buildinit();
   fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
   
}
__attribute__((destructor))void tini(void){printf("hello\n");} 
//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 

int loader = 0;
//perhaps the real one ?  
LibLoadFuncs funcs[10];
void setloadlist(LibLoadFuncs* funcstoset, int numFuncs){
    loader = 1;  

    for(int i = 0; i < numFuncs; i++){
		funcs[i] = *funcstoset[i];
	}
    
    fprintf(stderr, "%s\n",__func__);
}


char* preloaded; 
unsigned int la_version(unsigned int version) {
      //get env returns null or what the variable contains
     preloaded = getenv("LD_PRELOAD");
     return version;
}


/* currently unused 
int (*libloader)(lib_load_param*); 
int loader = 0;

void on_library_load(int(*fptr)(lib_load_param*)){

//trying to model it after what it looks like in spindle 
//void on_libray_load(int (*userFunc) (struct library_load_params *params)){
//	userFunc(params);
//}
*/


char DONOTLOADLIST[100][4096];
int DONOTLOADLENGTH = 0;
void set_block_list(char* blockArray[], int arrLength){
	
	for (int i = 0; i<arrLength ; i++){
		strcpy(DONOTLOADLIST[i], blockArray[i]);
	}
	DONOTLOADLENGTH = arrLength;
}



void on_library_load_real( lib_load_param *params){
    int i = 0;
   //fprintf(stderr, "%s\n",__func__); 
   //potench problem: funcs not sequatial in func list  
    while(i < libloadsize && funcs[i] != 0){ 
	printf("Debug Statement: user function number %d is loading\n", i);
	printf("\n");

    	    funcs[i](params);
	    i++;
    }  
}


int toolPrint(lib_load_param *params){
        printf("Printing library path name: C%s\n", params->libName);
	return 0;
	}



char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){

	//iff boolean is true- which we got from user calling lbirary load
	//	inside of if statement now do REAL callback library load function
    lib_load_param practiceStruct;
    practiceStruct.libName = (char *) name;
    if(loader == 1){
		on_library_load_real( &practiceStruct);
	}

	for(int i = 0; i < DONOTLOADLENGTH; i++){
        	if(strcmp(name, (char*) DONOTLOADLIST[i])==0){
			printf("Debug Statement: A file was blocked from loading based on client's blocklist\n");
			printf("\n");
			return NULL;
        	}

	}

    return (char*)name; 
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){


    return 0; 
}
