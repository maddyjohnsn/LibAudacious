
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
<<<<<<< HEAD

   //fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
=======
   fprintf(stderr,"%s hello%d %s\n", __FILE__, __LINE__, __func__);
   
>>>>>>> 6352dda2086fb52cacf5eae7040b565a4fb97e1e
}
__attribute__((destructor))void tini(void){}

<<<<<<< HEAD
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

=======
typedef struct expir{
    char* wrappee; 
    fptr_t fptr; 
    struct expir* next; 
}rap; 
//tyring 
rap start[10];
size_t funcsize = 10; 
int wrap(char* wrappee_name, fptr_t  wrapper){
  //  fprintf(stderr,"top of wrap %s %d\n", __func__, __LINE__);
    for(int i= 0; i<10; i++){
        if (start[i].wrappee == NULL){
            start[i].wrappee = wrappee_name;
            start[i].fptr = wrapper; 
            fprintf(stderr,"wrapped %s %p\n",start[i].wrappee,start[i].fptr);
            return 0; 
        }
    }
    fprintf(stderr, "should not get herefunc: %s line: %d\n", __func__, __LINE__);
>>>>>>> 6352dda2086fb52cacf5eae7040b565a4fb97e1e
}

fptr_t get_wrappee(char *wrappee_name)
{
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
            //if symbol can't be found (should be the needed function I'm replacing)
      //      fprintf(stderr, "func: %s line: %d Error: %s\n",__func__,__LINE__, dlerror());
            return 0;
    }
<<<<<<< HEAD
    //fprintf(stderr, "func: %s line: %d\n", __func__, __LINE__);
=======
    fprintf(stderr, "DEBUG: func: %s line: %d wrap name: %s\n", __func__, __LINE__,wrappee_name);
>>>>>>> 6352dda2086fb52cacf5eae7040b565a4fb97e1e
    return  ret; 
}


//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 
int libloadsize = 10; 
int loader = 0;
//perhaps the real one ?  
LibLoadFuncs funcs[10];
<<<<<<< HEAD
//TODO either delete this if we dont end up needing it OR 
//get rid of the int numFuncs 

void setloadlist(LibLoadFuncs* funcstoset, int numFuncs){
=======
void setloadlist(LibLoadFuncs* funcstoset){
   // fprintf(stderr, "start of %s line: %d\n", __func__, __LINE__);  
>>>>>>> 6352dda2086fb52cacf5eae7040b565a4fb97e1e
    loader = 1;  
    for(int i = 0; i < 10; i++){
		funcs[i] = *funcstoset[i];
	}
<<<<<<< HEAD
    
    //fprintf(stderr, "%s\n",__func__);
=======
   // fprintf(stderr, "end of %s\n",__func__);
>>>>>>> 6352dda2086fb52cacf5eae7040b565a4fb97e1e
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
    //fprintf(stderr, "start0: %s synmnae: %s\n", start[0].wrappee,symname);
    //fprintf(stderr, "top of %s line: %d\n", __func__, __LINE__); 
    //checks for a match with any of the wrappee names
   // fprintf(stderr,"%s\n",symname); 
    for(int i = 0;start[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(start[i].wrappee, symname) == 0){

            fprintf(stderr, "\nDEBUG: wrappee: %s synmnae: %s\n\n",start[i].wrappee,symname);
    
            return (uintptr_t)start[i].fptr; 
        }
    }
    //fprintf(stderr, "end of %s line: %d\n", __func__, __LINE__);
    return sym->st_value; 
}




