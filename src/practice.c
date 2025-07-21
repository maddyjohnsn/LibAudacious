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



//set up wrapped function structs
//1 = too many 
//2 = null name or pointer
WrappedFunctions wrappedarray[4];
size_t funcsize = 4;
int wrap(char* wrappee_name, fptr_t  wrapper){
    printf("funC %s  NAME%s\n",__func__, wrappee_name);
  //  fprintf(stderr,"top of wrap %s %d\n", __func__, __LINE__); //DEBUG
    //error checking 
    if(!wrapper){
       fprintf(stderr,"func: %s: Func pointer(%p) or name(%s) is null.\n",__func__,wrapper,wrappee_name); 
       return 2;
    }
    //checks if name is null, and then populates it. 
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){
            printf("in %s, fptr = %p\n", __func__,wrapper); 
            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper; 
            fprintf(stderr,"wrapped %s.\n",wrappedarray[i].wrappee);
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

   for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, wrappee_name) == 0){
            return (fptr_t)wrappedarray[i].ogfptr; 
        }
    }
    printf("smth wrong\n"); 
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
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
