#include <stdio.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>

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
        *cookie = (uintptr_t)l; // store link_map as cookie
        printf("\n");
	return LA_FLG_BINDTO | LA_FLG_BINDFROM;
}

//Elf64_Addr la_x86_64_gnu_pltenter (Elf64_Sym *__sym,unsigned int __ndx,uintptr_t *__refcook,uintptr_t *__defcook,La_x86_64_regs *__regs,unsigned int *__flags,const char *__symname,long int *__framesizep){
	//printf("in plt\n");
//     	printf("%s\n",__func__);
  //  return 0;
//}

//unsigned int la_x86_64_gnu_pltexit (Elf64_Sym *__sym,unsigned int __ndx,uintptr_t *__refcook,uintptr_t *__defcook,La_x86_64_regs *inregs,La_x86_64_retval *outregs,const char *__symname){
  //      printf("in pltex\n");
//      printf("%s\n",__func__);
   // return 0;
//}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname){
	printf("in symbind\n");
	return sym->st_value;
}

//Elf64_Addr la_i86_gnu_pltenter(Elf32_Sym *sym, unsigned int ndx,uintptr_t *refcook, uintptr_t *defcook, La_x32_regs *regs, unsigned int *flags,const char *symname, long int *framesizep){
  //  printf("in plt\n");
//	return 0;
//}
