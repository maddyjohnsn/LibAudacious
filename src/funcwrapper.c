#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h> 
#include "../include/committee.h" 

fptr_t saved_func_ptr;  
int wrap(char* wrappee_name, fptr_t wrapper){
    //fprintf(stderr,"top of wrap %s %d\n", __func__, __LINE__);
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
            //if symbol can't be found (should be the needed function I'm replacing)
            fprintf(stderr, "Error: %s\n", dlerror());
            return 0;
    }
    fprintf(stderr,"post dlsym %s %d\n", __func__, __LINE__);
    saved_func_ptr  = ret ;

}

fptr_t get_wrappee(char *wrappee_name)
{
    fprintf(stderr, "func: %s line: %d\n", __func__, __LINE__);
    return  saved_func_ptr; 
}



