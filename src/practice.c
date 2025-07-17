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
fopenwrapped one;
fclosewrapped two; 
int wrapfclose(char* wrappee_name, fclose_t  wrapper){
    two.wrappee = wrappee_name;
    two.fptr = wrapper; 
    printf("wrapped fclose\n");
}
int wrapfopen(char* wrappee_name, fileopen_t  wrapper){
    one.wrappee = wrappee_name;
    one.fptr = wrapper;
    printf("wrapped fopen\n");
}
fclose_t getfclosewrapee(char* wrappee_name){
     fclose_t ret = (fclose_t)dlsym(RTLD_NEXT, wrappee_name);
     return ret; 
}
fileopen_t getfopenwrapee(char* wrappee_name){
     fileopen_t ret = (fileopen_t)dlsym(RTLD_NEXT, wrappee_name);
     return ret;
}

int wrap(char* wrappee_name, fptr_t  wrapper){
  //  fprintf(stderr,"top of wrap %s %d\n", __func__, __LINE__); //DEBUG
    //error checking 
    if(!wrapper){
       fprintf(stderr,"func: %s: Func pointer(%p) or name(%s) is null.\n",__func__,wrapper,wrappee_name); 
       return 2;
    }
    //checks if name is null, and then populates it. 
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){

            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper; 
//            fprintf(stderr,"wrapped %s.\n",wrappedarray[i].wrappee);
            return 0; 
        }
        if(strcmp (wrappedarray[i].wrappee, wrappee_name)==0){
             fprintf(stderr, "%s Duplicate name! %s\n",wrappedarray[i].wrappee, wrappee_name);
             return 3; 
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
    fprintf(stderr, "DEBUG: func: %s line: %d wrap name: %s\n", __func__, __LINE__,wrappee_name);
    return  ret; 
}

unsigned int la_version(unsigned int version) {
     return version;
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}



uintptr_t la_symbind64(Elf64_Sym *sym,unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
     // fprintf(stderr,"symname: %s\n",symname);
    //fprintf(stderr, "start0: %s synmnae: %s\n", start[0].wrappee,symname);
    if(one.fptr != NULL && strcmp("fopen",symname)==0){
        return (uintptr_t)one.fptr;
    }
    if(two.fptr != NULL &&strcmp("fclose",symname)==0){
        return (uintptr_t)two.fptr;
    }
    for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, symname) == 0){
            return (uintptr_t)wrappedarray[i].fptr; 
        }
    }
    //fprintf(stderr, "end of %s line: %d\n", __func__, __LINE__);
    return sym->st_value; 
}




