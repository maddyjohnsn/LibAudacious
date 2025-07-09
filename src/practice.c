#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <link.h>
#include <elf.h>
#include <stdio.h>
#include "../test/buildfile.c"
#include <string.h>
#include "../include/committee.h"

//first thing prgm does is call buildinit where all the wrappers are called
__attribute__((constructor))
 void init(void) { 
    buildinit();

   //fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
   
}
__attribute__((destructor))void tini(void){}
//size vars ? <- do we want organize like that? or initialize right before theyre used?
//set up wrapped function structs
WrappedFunctions wrappedarray[4];
size_t funcsize = 4; 
int wrap(char* wrappee_name, fptr_t wrapper){
    //checks if name is null, and then populates it.
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){
            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper; 
            fprintf(stderr,"wrapped %s.\n",wrappedarray[i].wrappee);
            return 0; 
        }
    }

    fprintf(stderr, "%sshould not get here wrappee: %s\n", __func__,wrappee_name);
    //TODO error handling 
    return 1; 
}


fptr_t get_wrappee(char *wrappee_name)
{
    //gets next occurance of wrappeename and its ptr 
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
        //TODO the error handling 
        //if symbol can't be found (should be the needed function I'm replacing)
        fprintf(stderr, "func: %s line: %d Error: %s\n",__func__,__LINE__, dlerror());
        return 0;
    }
  //  fprintf(stderr, "DEBUG: func: %s line: %d wrap name: %s\n", __func__, __LINE__,wrappee_name);
    return  ret; 
}


//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 
int libloadsize = 10; 
int loader = 0;
//perhaps the real one ?  
LibLoadFuncs funcs[10];

void setloadlist(LibLoadFuncs* funcstoset){
   // fprintf(stderr, "start of %s line: %d\n", __func__, __LINE__);  
    loader = 1;  
    for(int i = 0; i < 10; i++){
		funcs[i] = *funcstoset[i];
	}
    
}

void on_library_load(lib_load_param *params){
    int i = 0;
   //fprintf(stderr, "%s\n",__func__); 
   //TODO potench problem: funcs not sequatial in func list  
    while(i < libloadsize && funcs[i] != 0){
    //printf("Debug Statement: user function number %d is loading\n", i);
        funcs[i](params);
        i++;
    }
}

//BLOCK LIST 
char DONOTLOADLIST[100][4096];
int DONOTLOADLENGTH = 0;
int set_block_list(char* blockArray[], int arrLength){
	if(arrLength < 1 ){
                printf("TOO FEW LIBRARIES\n");
                return 1;
        }
	if(arrLength >99 ){
		printf("TOO MANY LIBRARIES\n");
		return 1;
	}

	for (int i = 0; i<arrLength ; i++){
		strcpy(DONOTLOADLIST[i], blockArray[i]);
	}

		
	DONOTLOADLENGTH = arrLength;
	return 0;
}

char* preloaded;
unsigned int la_version(unsigned int version) {
      //get env returns null or what the variable contains
     preloaded = getenv("LD_PRELOAD");
     return version;
}
char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    //fprintf(stderr, "top of %s line: %d\n", __func__, __LINE__); 
	//iff boolean is true- which we got from user calling lbirary load
	//	inside of if statement now do REAL callback library load function
    //TODO perhaps a better name for this ? 
    lib_load_param libparams;
    libparams.libName = (char *) name;
    if(loader == 1){
		on_library_load(&libparams);
	}

	for(int i = 0; i < DONOTLOADLENGTH; i++){
		int comp = strcmp(name, (char*) DONOTLOADLIST[i]);
        	if(strcmp(name, (char*) DONOTLOADLIST[i])==0){
		     	return NULL;
        	}

	}
    //TODO should we be returning libparams.libName/newName ? 
    return (char*)name; 
}


unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
    //TODO figure out if we can selectively do this or if its fine as is  
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}

unsigned int la_objclose(uintptr_t *cookie){
}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {

     // fprintf(stderr,"symname: %s\n",symname);
    //fprintf(stderr, "start0: %s synmnae: %s\n", start[0].wrappee,symname);
    //checks for a match with any of the wrappee names
    for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, symname) == 0){
            fprintf(stderr,"DEBUG: wrappee: %s symname: %s\n",wrappedarray[i].wrappee,symname);
            return (uintptr_t)wrappedarray[i].fptr; 
        }
    }
    //fprintf(stderr, "end of %s line: %d\n", __func__, __LINE__);
    return sym->st_value; 

}




