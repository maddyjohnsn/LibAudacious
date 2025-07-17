



#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <link.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>



unsigned int la_version(unsigned int version) {
      //get env returns null or what the variable contains
     return version;
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
    
    //fprintf(stderr, "%p %p %p\n", &map, &lmid, cookie);
    //TODO figure out if we can selectively do this or if its fine as is  
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
    //fprintf(stdout, "%d %p %p\n",ndx,refcook,defcook);
      printf( "%s %s%dflag:%s\n", __func__,symname,*flags,
            *flags & LA_SYMB_NOPLTENTER  ? "LA_SYMB_NOPLTENTER"  :
          *flags & LA_SYMB_NOPLTEXIT  ? "LA_SYMB_NOPLTEXIT"  :
          *flags & LA_SYMB_DLSYM  ? "LA_SYMB_DLSYM"  :
          *flags & LA_SYMB_ALTVALUE  ? "LA_SYMB_ALTVALUE"  :
           "UNKNOWN_FLAG");
    *flags |= LA_SYMB_NOPLTENTER | LA_SYMB_NOPLTEXIT; 
    fprintf(stdout,"%s: symname=%s\n", __func__, symname); 
    return sym->st_value;
}
