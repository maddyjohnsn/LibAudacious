

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>
#include <elf.h>
#include <stdio.h> 
#include "setup.h" 
#include "buildfile.c"
//#include "committee.h"

 __attribute__((constructor))
 void init(void) {
   buildinit();
   fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
   
}
__attribute__((destructor))void tini(void){printf("hello\n");} 
//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 

int loader = 0;
//perhaps the real one ?  
LibLoadFuncs funcs[10];
void setloadlist(LibLoadFuncs* funcstoset){
    printf("%s\n",__func__);
    loader = 1;  
    for(int i = 0; i < libloadsize ; i++){
        if(*funcstoset[i] == 0){
             funcs[i] = 0;
        }
        else{
            funcs[i] = *funcstoset[i];
        }
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
char DONOTLOADLIST[100][100];
int DONOTLOADLENGTH = 0;
void set_block_list(char* blockArray[], int arrLength){
	//DONOTLOADLIST = (char **)malloc(arrLength * sizeof(char*));
	for (int i = 0; i<arrLength ; i++){
	    printf("%s\n", blockArray[i]);
	strcpy(DONOTLOADLIST[i], blockArray[i]);
	printf("%s\n", DONOTLOADLIST[i]); 
	}
	DONOTLOADLENGTH = arrLength;
}



void on_library_load_real( lib_load_param *params){
    int i = 0;
   fprintf(stderr, "%s\n",__func__); 
   //potench problem: funcs not sequatial in func list  
    while(i < libloadsize && funcs[i] != 0){ 
        funcs[i](params);
        i++; 
    }  
}


int toolPrint(lib_load_param *params){
        printf("Printing library path name: C%s\n", params->libName);
	return 0;
	}



char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    //debug statement
    //fprintf(stderr,"la_objsearch:%s %s\n",name,
      //    flag & LA_SER_ORIG    ? "ORIG"    :   
        //  flag & LA_SER_LIBPATH ? "LIBPATH" :
         // flag & LA_SER_RUNPATH ? "RUNPATH" :
          //flag & LA_SER_CONFIG  ? "CONFIG"  :
          //flag & LA_SER_DEFAULT ? "DEFAULT" :
          //flag & LA_SER_SECURE  ? "SECURE"  :
           //"UNKNOWN_FLAG");


	//iff boolean is true- which we got from user calling lbirary load
	//	inside of if statement now do REAL callback library load function
    lib_load_param practiceStruct;
    practiceStruct.libName = (char *) name;
    if(loader == 1){
        //do we even need it to take in funcs[0] ? kylie took it out
		on_library_load_real( &practiceStruct);
	}

		for(int i = 0; i < DONOTLOADLENGTH; i++){
        		if(strcmp(name, (char*) DONOTLOADLIST[i])==0){
				return NULL;
        		}

		}
    /*and also perhaps restore_pathpatch() should be implemented in here in totatlity 
    in the future this will probably switch to just returning the callback fx 
    spindle also checks if theres a '/' so perhaps that aswell. or add that 
    to the method that finds the lib*/ 

    return (char*)name; 
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){

    //debugging 
    fprintf(stderr, "la_objopen: loading %s, link_map = %p, lmid = %s, cookie = %p\n",
                 map->l_name, map,
                 (lmid == LM_ID_BASE) ?  "LM_ID_BASE" :
                 (lmid == LM_ID_NEWLM) ? "LM_ID_NEWLM" : 
                 "???", 
                 cookie);

    return 0; 
}
