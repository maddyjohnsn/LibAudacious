//https://www.sentinelone.com/labs/leveraging-ld_audit-to-beat-the-traditional-linux-library-preloading-technique/#include <stdio.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>
#include <elf.h>
__attribute__((constructor))
//to show which loads first,audit or preload 
static void init(void) {
    printf("I'm loaded from LD_AUDIT\n");
}

const char* preloaded; 

unsigned int la_version(unsigned int version) {  
    //get env returns null or what the variable contains 
    preloaded = getenv("LD_PRELOAD"); 
    return version;
}

//testing differnt things i can do! 
const char* evil = "./libsneaky.so";
int option = 3; //if option doesnt match any the og will happen
char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag) {  
    printf( "%s flag:%d%s\n", __func__,flag,
          flag & LA_SER_ORIG    ? "ORIG"    :
          flag & LA_SER_LIBPATH ? "LIBPATH" :
          flag & LA_SER_RUNPATH ? "RUNPATH" :
          flag & LA_SER_CONFIG  ? "CONFIG"  :
          flag & LA_SER_DEFAULT ? "DEFAULT" :
          flag & LA_SER_SECURE  ? "SECURE"  :
           "UNKNOWN_FLAG");
    printf("%s\n", name);     
    //add my own lib on sneakily... 
    if(option == 2 && preloaded != NULL && strcmp(name,preloaded)== 0){
        printf("appending %s...\n", evil);
        void* handle = dlopen(evil, RTLD_LAZY); 
      
        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
        }
        printf("%d\n", rand()%100);
        return (char*)name;
     }
    
    //I can swap the library with my own!
    if (option == 1 && NULL != preloaded && strcmp(name, preloaded) == 0) {
         printf( "%s swapping with %s :)\n",name, evil);
        return (char*)evil;
    } 

    //original ! 
    if (option == 0 && NULL != preloaded && strcmp(name, preloaded) == 0) {
        fprintf(stderr, "Disabling the loading of a 'preload' library: %s\n", name);
        return NULL;
   }   
   return (char *)name;
}
/*
void la_activity( uintptr_t *cookie, unsigned int flag){
    
    printf( "%s:%s flag:%d%s\n", __FILE__, __func__,flag,
        flag & LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT"  :
        flag & LA_ACT_DELETE  ? "LA_ACT_DELETE"  :
        flag & LA_ACT_ADD  ? "LA_ACT_ADD"  :
        "UNKNOWN_FLAG");
    //printf("%d\n", LA_ACT_CONSISTENT);//=0. i think this is the unknown
}*/

uintptr_t* precookie = NULL; 
unsigned int la_objopen(struct link_map *map, Lmid_t lmid,uintptr_t *cookie){
    
    printf( "\n%s%p name: %s\n",__func__,cookie, map->l_name);
    printf("prelo:%s map:%s\n", preloaded, map->l_name);

    if (NULL != preloaded && strcmp(map->l_name, preloaded) == 0) {
        fprintf(stderr, "A 'preload' library is about to load: %s. Following its function binding\n", map->l_name);
        precookie = cookie;
        return LA_FLG_BINDTO | LA_FLG_BINDFROM;
    }
    return 0;
}
void la_preinit(uintptr_t *cookie){
    printf("%s %p\n",__func__,cookie); 
}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
    //printf("%s %s\n",__func__,symname);
    printf( "%s %sflag:%s\n", __func__,symname);/* fix later to actually say flags
            flag & LA_SYMB_NOPLTENTER  ? "LA_SYMB_NOPLTENTER"  :
          flag & LA_SYMB_NOPLTEXIT  ? "LA_SYMB_NOPLTEXIT"  :
          flag & LA_SYMB_DLSYM  ? "LA_SYMB_DLSYM"  :
          flag & LA_SYMB_ALTVALUE  ? "LA_SYMB_ALTVALUE"  :
           "UNKNOWN_FLAG");*/
    //mr krabs i have an idea 
    //potench somehow swap my rand func and the libc version here? like
    //straight up only the functiopns??????
    //
  if (refcook == precookie) {    
      fprintf(stderr, "Function '%s' is intercepted\n", symname);
  }
  return sym->st_value;
}

Elf64_Addr la_x86_64_gnu_pltenter (Elf64_Sym *__sym,
                      unsigned int __ndx,
                      uintptr_t *__refcook,
                      uintptr_t *__defcook,
                      La_x86_64_regs *__regs,
                      unsigned int *__flags,
                      const char *__symname,
                      long int *__framesizep){
    printf("%s\n",__func__);
    return 0;
}


unsigned int la_x86_64_gnu_pltexit (Elf64_Sym *__sym,
                       unsigned int __ndx,
                       uintptr_t *__refcook,
                       uintptr_t *__defcook,
                       const La_x86_64_regs *__inregs,
                       La_x86_64_retval *__outregs,
                       const char *__symname){
    printf("%s\n",__func__);
    return 0;
}







/*
unsigned int la_objclose(uintptr_t *cookie){
    printf( "%s%p\n", __func__, cookie);
    return 0; 
}*/
/* idc abt this rn :) 
   printf( "%s:%s flag:%d%s\n", __FILE__, __func__,flag,
 58          flag & LA_SER_ORIG    ? "LA_SER_ORIG"    :
 59         flag & LA_SER_LIBPATH ? "LA_SER_LIBPATH" :
 60         flag & LA_SER_RUNPATH ? "LA_SER_RUNPATH" :
 61         flag & LA_SER_CONFIG  ? "LA_SER_CONFIG"  :
 62         flag & LA_SER_DEFAULT ? "LA_SER_DEFAULT" :
 63         flag & LA_SER_SECURE  ? "LA_SER_SECURE"  :
 64         flag & LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT"  :
 65         flag & LA_ACT_DELETE  ? "LA_ACT_DELETE"  :
 66         flag & LA_ACT_ADD  ? "LA_ACT_ADD"  :
 67         flag & LA_FLG_BINDTO  ? "LA_FLG_BINDTO"  :
 68         flag & LA_FLG_BINDFROM  ? "LA_FLG_BINDFROM"  :
 69         flag & LA_SYMB_NOPLTENTER  ? "LA_SYMB_NOPLTENTER"  :
 70         flag & LA_SYMB_NOPLTEXIT  ? "LA_SYMB_NOPLTEXIT"  :
 71         flag & LA_SYMB_STRUCTCALL ? "LA_SYMB_STRUCTCALL"  :
 72         flag & LA_SYMB_DLSYM  ? "LA_SYMB_DLSYM"  :
 73         flag & LA_SYMB_ALTVALUE  ? "LA_SYMB_ALTVALUE"  :
 74
 75         "UNKNOWN_FLAG");
}*/ 
