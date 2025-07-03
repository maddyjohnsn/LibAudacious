
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <link.h>
#include <elf.h>
#include <stdio.h> 
#include "../test/buildfile.c"
#include <string.h>
#include "../include/committee.h"

__attribute__((constructor))
 void init(void) { 
    buildinit();

   //fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
   
}
__attribute__((destructor))void tini(void){}

WrappedFunctions wrappedarray[10];
size_t funcsize = 10;

int wrap(char* wrappee_name, fptr_t wrapper){


    //checks if name is null, and then populates it.
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){
            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper;
            fprintf(stderr,"wrapped %s %p\n",wrappedarray[i].wrappee,wrappedarray[i].fptr);
            return 0;
        }
    }

    fprintf(stderr, "should not get herefunc: %s line: %d\n", __func__, __LINE__);
    //TODO error handling
    return 1;
}

//tyring 

fptr_t get_wrappee(char *wrappee_name)
{
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
            //if symbol can't be found (should be the needed function I'm replacing)
      //      fprintf(stderr, "func: %s line: %d Error: %s\n",__func__,__LINE__, dlerror());
            return 0;
    }
    //fprintf(stderr, "func: %s line: %d\n", __func__, __LINE__);
    return  ret; 
}


//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 
int libloadsize = 10; 
int loader = 0;
//perhaps the real one ?  
LibLoadFuncs funcs[10];
//TODO either delete this if we dont end up needing it OR 
//get rid of the int numFuncs 

void setloadlist(LibLoadFuncs* funcstoset){
   // fprintf(stderr, "start of %s line: %d\n", __func__, __LINE__);  
    loader = 1;  
    for(int i = 0; i < 10; i++){
		funcs[i] = *funcstoset[i];
	}
    
}


char* preloaded; 
unsigned int la_version(unsigned int version) {
      //get env returns null or what the variable contains
     preloaded = getenv("LD_PRELOAD");
     return version;
}


char DONOTLOADLIST[100][4096];
int DONOTLOADLENGTH = 0;
void set_block_list(char* blockArray[], int arrLength){
	
	for (int i = 2; i<arrLength ; i++){
		strcpy(DONOTLOADLIST[i], blockArray[i]);
	}
	DONOTLOADLENGTH = arrLength;
}


void on_library_load_real( lib_load_param *params){
    int i = 0;
   //fprintf(stderr, "%s\n",__func__); 
   //potench problem: funcs not sequatial in func list  
    while(i < libloadsize && funcs[i] != 0){ 
	//printf("Debug Statement: user function number %d is loading\n", i);
    	funcs[i](params);
	    i++;
    }  
}


char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    //fprintf(stderr, "top of %s line: %d\n", __func__, __LINE__); 
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
			    return NULL;
        	}

	}

    return (char*)name; 
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
     //from the code i have....
     //it seems like that one checks if its a prelaoded lib and the returns falsg 
     //
    //if((justice.wrappee 
    //fprintf(stderr, "top of %s line: %d\n", __func__, __LINE__); 
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}



uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {

for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, symname) == 0){
            fprintf(stderr,"DEBUG: wrappee: %s symname: %s\n",wrappedarray[i].wrappee,symname);
            return (uintptr_t)wrappedarray[i].fptr; 
        }
    }
    //fprintf(stderr, "end of %s line: %d\n", __func__, __LINE__);
    return sym->st_value; 

}




