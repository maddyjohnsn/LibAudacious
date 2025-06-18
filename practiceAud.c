#include <stdio.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>
#include <inttypes.h>
//#include "practiceAud.h"

struct libList {
        char path[100];
        int size;
    } ;
//struct libList libList1;
//can hold 100 libs
struct libList myLibs[100];
int count = 0;
struct libList * getLibList(){
	printf("in get  %s\n", myLibs[0].path);
	return myLibs;
}


unsigned int la_version(unsigned int version){
	
	return version;

}

char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag) {  
//	return NULL;
	return (char *) name;
}	
void la_activity( uintptr_t *cookie, unsigned int flag){
	//flag 1 is la_act_ADD
	  if(flag == 1){
		printf("yes!\n");	
	  }
}

void la_preinit(uintptr_t *cookie) {
        printf("la_preinit called with cookie: %p\n", cookie);
}

unsigned int la_objopen(struct link_map *l, Lmid_t lmid, uintptr_t *cookie) {
        printf("la_objopen called for %s\n", l->l_name);
	int length = strlen(l->l_name);
	if(length != 0){
		strcpy(myLibs[count].path, l->l_name);
		printf("in objopen  %s\n", myLibs[count].path);
		count = count +1;
	}
	*cookie = (uintptr_t)l; // store link_map as cookie
        printf("\n");
	return LA_FLG_BINDTO | LA_FLG_BINDFROM;
}

Elf64_Addr la_x86_64_gnu_pltenter (Elf64_Sym *__sym ,unsigned int __ndx,uintptr_t *__refcook,uintptr_t *__defcook,La_x86_64_regs *__regs,unsigned int *__flags,const char *__symname,long int *__framesizep){
//	printf("in plt\n");
  //   	printf("%s\n",__func__);
    return __sym->st_value;
}


uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname){
	printf("in symbind\n");
//	printf(PRIxPTR, sym->st_value);
	return sym->st_value;
}

unsigned int la_objclose(uintptr_t *cookie){
	printf("Object Closing\n");
	struct libList* myPracStruct;
       myPracStruct = getLibList();
       printf("path is: %s\n", myPracStruct[0].path);
}
