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

   fprintf(stderr,"change?%s %d %s\n", __FILE__, __LINE__, __func__);
}
__attribute__((destructor))void tini(void){}

//size vars ? <- do we want organize like that? or initialize right before theyre used?
//set up wrapped function structs
//1 = too many 
//2 = null name or pointer
WrappedFunctions wrappedarray[4];
size_t funcsize = 4;
int wrap(char* wrappee_name, fptr_t  wrapper){
    //fprintf(stderr,"top of wrap %s name: %s\n", __func__, wrappee_name); //DEBUG
    if(!wrapper||!wrappee_name){
       fprintf(stderr,"func: %s: Func pointer(%p) or name(%s) is null.\n",__func__,wrapper,wrappee_name);
       return 2;
    }
    //checks if name is null, and then populates it.
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){
            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper;
            fprintf(stderr,"wrapped %s.\n",wrappedarray[i].wrappee);
            return 0;
        }
        if(strcmp (wrappedarray[i].wrappee, wrappee_name)==0){
             fprintf(stderr, "%s Youve already wrapped a function with this name! %s\n",wrappedarray[i].wrappee, wrappee_name);
             return 3;
        }
    }

    fprintf(stderr, "Reached max amount of %sped funcs, cannot add %s\n", __func__,wrappee_name);
    return 1;
}
fptr_t get_wrappee(char *wrappee_name){

   for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, wrappee_name) == 0){
             if (!wrappedarray[i].ogfptr) {
                 fprintf(stderr, "func: %s orignial fptr is null for %s\n",__func__,wrappee_name);
                 return 0;
             }
            return (fptr_t)wrappedarray[i].ogfptr; 
        }
    }
    printf("func:%s:%s not in wrapped list.\n", __func__, wrappee_name); 
    return  0; 
}


//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 
int libloadsize = 10; 
int loader = 0;
LibLoadFuncs funcs[10];
int setloadlist(LibLoadFuncs functoset){
    //fprintf(stderr, "start of %s line: %d\n", __func__, __LINE__);  
    for(int i = 0; i < libloadsize; i++){
        if(funcs[i] == 0){
	    	funcs[i] = functoset;
            fprintf(stderr,"func: %s: Added to loadlist.\n",__func__);
            return 0;
        }

    }
     fprintf(stderr, "func: %s: Exceeded max libload. Cannot add %p\n", __func__,functoset);
     return 1;
   // fprintf(stderr, "end of %s\n",__func__);
}

int on_library_load(lib_load_param *params){
    int i = 0;
   //fprintf(stderr, "%s\n",__func__); 
    while(i < libloadsize && funcs[i] != 0){
    //printf("Debug Statement: user function number %d is loading\n", i);
        funcs[i](params);
        i++;
    }
}

//BLOCK LIST 
char DONOTLOADLIST[100][4096];
int DONOTLOADLENGTH = 0;
void set_block_list(char* blockArray[], int arrLength){
    printf("what\n");	
	for (int i = 2; i<arrLength ; i++){
		strcpy(DONOTLOADLIST[i], blockArray[i]);
	}
	DONOTLOADLENGTH = arrLength;
}


unsigned int la_version(unsigned int version) {
     return version;
}
char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    //fprintf(stderr, "top of %s line: %d\n", __func__, __LINE__); 
    lib_load_param libparams;
    libparams.libName = (char *) name;
    on_library_load(&libparams);
    libparams.newPath = 0; 
	for(int i = 0; i < DONOTLOADLENGTH; i++){
        	if(strcmp(name, (char*) DONOTLOADLIST[i])==0){
			    printf("Debug Statement: A file was blocked from loading based on client's blocklist\n");
			    return NULL;
        	}

	}
   if(!libparams.newPath){ 
    return (char*)name; 
   }
   return libparams.newPath;
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}



uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx,uintptr_t *refcook, uintptr_t *defcook,
        unsigned int *flags, const char *symname ){
    //fprintf(stderr,"symname: %s\n",symname);
      for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, symname) == 0){
              printf("symname:%s, ogfptr: %p, new: %p\n", symname,wrappedarray[0].ogfptr, wrappedarray[0].fptr);
            wrappedarray[i].ogfptr = ( fptr_t )sym->st_value;
            return (uintptr_t)wrappedarray[i].fptr;
        }
    }
    return sym->st_value;
}

