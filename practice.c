#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>
#include <elf.h>
#include <stdio.h> 
#include "buildfile.c" 
#include "setup.h" 

//holds the pointer to the first call back func  
CallFuncChar* firstlib;

 __attribute__((constructor))
static void init(void) {
   firstlib = buildinit();
   fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
}
/* find item 
 * param flag - one to look for 
 *      current - the struct we are on 
 * returns the pointer to the correct struct or a -1 for an error 
 */ 
CallFuncChar* find(int flag){
    CallFuncChar* current = firstlib; 
    fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
    while(1) {
        if(current->flag == flag){
            return current ;
        }
        if( current->next == 0){
            return 0; 
        }
        current = current->next; 
    }
}
char* preloaded; 
unsigned int la_version(unsigned int version) {
      //get env returns null or what the variable contains
     preloaded = getenv("LD_PRELOAD");
     return version;
}

//trying to model it after what it looks like in spindle 
char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    //debug statement
    fprintf(stderr,"la_objsearch:%s %s\n",name,
          flag & LA_SER_ORIG    ? "ORIG"    :   
          flag & LA_SER_LIBPATH ? "LIBPATH" :
          flag & LA_SER_RUNPATH ? "RUNPATH" :
          flag & LA_SER_CONFIG  ? "CONFIG"  :
          flag & LA_SER_DEFAULT ? "DEFAULT" :
          flag & LA_SER_SECURE  ? "SECURE"  :
           "UNKNOWN_FLAG");


	

	



    /*and also perhaps restore_pathpatch() should be implemented in here in totatlity 
    in the future this will probably switch to just returning the callback fx 
    but currently it checks for the preloaded llib and swaps it for libsneaky
    spindle also checks if theres a '/' so perhaps that aswell. or add that 
    to the method that finds the lib*/ 
      if(preloaded != 0 &&  strcmp(name,preloaded)== 0){
          CallFuncChar* pt2 = find(3);
          if (pt2 == 0) {
              printf("there was a problem :/\n");
              return "nope";
          }
          return pt2->fptr((char*)name); 
      }

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
void bye(){
    destroy(firstlib);
}
void tester(char* path){
    if(firstlib == NULL){
        printf("uh oh"); 
        return; 
    }
    printf("incoming: %s, outgoing: %s\n",path,firstlib->fptr(path));

    CallFuncChar* pt2 = find(3);
    if (pt2 == 0) {
        printf("there was a problem :/\n");
        return; 
    }
    printf("incoming: %s, outgoing: %s\n",path,pt2->fptr(path));


}
