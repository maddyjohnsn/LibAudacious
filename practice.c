#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>
#include <elf.h>
#include <stdio.h> 

#include "setup.h" 
CallFuncChar* addlib; 
void firstaddlib(CallFuncChar *hi){
    addlib = hi; 
}
/* find item 
 * param flag - one to look for 
 *      current - the struct we are on 
 * returns the pointer to the correct struct or a -1 for an error 
 */ 
CallFuncChar* find(int flag){
    CallFuncChar* current = addlib; 
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

char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){

    //currenlty only ever swaps/ does this function w flag 3 
    CallFuncChar* pt2 = find(3);
    printf("hello"); 
      if (pt2 == 0) {
        printf("there was a problem :/\n");
          return "nope";
      }
      return pt2->fptr((char*)name); 
    //decide what library is sent off 
    //maybe a loop? that goes through all the ones in tha struct that has to do with adding libra?
    //and checks those flags for swap ?  

  //  return (char*)name; 
}
void callOneParam(int (*userFunc) (char*), char * path){
    printf("hello!\n");
    userFunc(path);
}

void tester(char* path){
    if( firstaddlib == NULL){
        printf("uh oh"); 
        return; 
    }
    printf("incoming: %s, outgoing: %s\n",path,addlib->fptr(path));

    CallFuncChar* pt2 = find(3);
    if (pt2 == 0) {
        printf("there was a problem :/\n");
        return; 
    }
    printf("incoming: %s, outgoing: %s\n",path,pt2->fptr(path));


}
    
void callOneParamChar(char*(*userFunc)(char*),char *path){
    printf( "swapping %s with %s\n", path, userFunc(path));

}
